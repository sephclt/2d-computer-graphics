// Dear ImGui: standalone example application for SDL3 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows,
// inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/
// folder).
// - Introduction, links and more at the top of imgui.cpp

// Important to understand: SDL_Renderer is an _optional_ component of SDL3.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and
// SDL+OpenGL on Linux/OSX.

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_image/SDL_image.h"
#include "draw.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "structs.h"
#include "utils.h"
#include <SDL3/SDL.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <string>

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

// Main code
int main(int, char **) {
    // Setup SDL
    // [If using SDL_MAIN_USE_CALLBACKS: all code below until the main loop
    // starts would likely be your SDL_AppInit() function]
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return 1;
    }

    // Create window with SDL_Renderer graphics context
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN |
                                   SDL_WINDOW_HIGH_PIXEL_DENSITY;
    SDL_Window *window = SDL_CreateWindow(
        "Dear ImGui SDL3+SDL_Renderer example", (int)(1280 * main_scale),
        (int)(800 * main_scale), window_flags);
    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (renderer == nullptr) {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(
        main_scale); // Bake a fixed style scale. (until we have a solution for
                     // dynamic style scaling, changing this requires resetting
                     // Style + calling this again)
    style.FontScaleDpi =
        main_scale; // Set initial font scale. (in docking branch: using
                    // io.ConfigDpiScaleFonts=true automatically overrides this
                    // for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // Load Fonts
    // - If fonts are not explicitly loaded, Dear ImGui will select an embedded
    // font: either AddFontDefaultVector() or AddFontDefaultBitmap().
    //   This selection is based on (style.FontSizeBase * style.FontScaleMain *
    //   style.FontScaleDpi) reaching a small threshold.
    // - You can load multiple fonts and use ImGui::PushFont()/PopFont() to
    // select them.
    // - If a file cannot be loaded, AddFont functions will return a nullptr.
    // Please handle those errors in your code (e.g. use an assertion, display
    // an error and quit).
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use
    // FreeType for higher quality font rendering.
    // - Remember that in C/C++ if you want to include a backslash \ in a string
    // literal you need to write a double backslash \\ !
    // style.FontSizeBase = 20.0f;
    // io.Fonts->AddFontDefaultVector();
    // io.Fonts->AddFontDefaultBitmap();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
    // ImFont* font =
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
    // IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    bool image_window = true;
    bool image_generation = true;
    bool image_manipulation = true;

    float screen_width = io.DisplaySize.x;
    float screen_height = io.DisplaySize.y;
    int width, height;
    SDL_GetWindowSizeInPixels(window, &width, &height);
    float padding = 0.1f;

    float noise_slider_value = 0.0f;
    static char image_size[] = "500x500";

    static int current_selected_image_type_index = 0;
    const char *image_type_list[] = {"gradient", "cloud", "wood", "marble"};

    // SETUP IMAGE TEXTURE
    ImageTexture image_texture;
    image_texture.filename = "SampleImage.ppm";
    image_texture.width = 500;
    image_texture.height = 500;
    image_texture.noise_value = 0.0f;

    ImageTexture image_texture_cache = image_texture;

    SDL_Texture *sdl_image_texture =
        IMG_LoadTexture(renderer, image_texture.filename.c_str());

#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not
    // attempt to do a fopen() of the imgui.ini file. You may manually call
    // LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!done)
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
        // tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data
        // to your main application, or clear/overwrite your copy of the mouse
        // data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
        // data to your main application, or clear/overwrite your copy of the
        // keyboard data. Generally you may always pass all inputs to dear
        // imgui, and hide them from your application based on those two flags.
        // [If using SDL_MAIN_USE_CALLBACKS: call ImGui_ImplSDL3_ProcessEvent()
        // from your SDL_AppEvent() function]
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
                event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your
        // SDL_AppIterate() function]
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        if (image_texture != image_texture_cache) {
            std::cout << "Image Is Different\n";
            generate_image(
                image_texture,
                parseSampleImageTypeString(
                    image_type_list[current_selected_image_type_index]));
            sdl_image_texture = create_texture(renderer, image_texture);
            image_texture_cache = image_texture;
        }

        // Image Window
        ImGui::SetNextWindowPos(
            ImVec2(screen_width * padding, screen_height * padding));
        ImGui::SetNextWindowSize(
            ImVec2(screen_width * 0.5f, screen_height * 0.5f));
        ImGui::Begin("Image", &image_window);

        ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x - 500) * 0.5f,
                                   (ImGui::GetWindowSize().y - 500) * 0.5f));
        ImGui::Image((ImTextureID)(intptr_t)sdl_image_texture,
                     ImVec2(500, 500));

        ImGui::End();

        // Image Generation Window
        ImGui::SetNextWindowPos(
            ImVec2((screen_width + (width * 0.5f)) * padding,
                   screen_height * padding));
        ImGui::SetNextWindowSize(
            ImVec2(screen_width * 0.5f, screen_height * 0.5f));
        ImGui::Begin("Image Generation", &image_generation,
                     ImGuiWindowFlags_AlwaysAutoResize);

        if (ImGui::Button("Generate Image")) {
            std::cout << "Generating New Image: "
                      << image_type_list[current_selected_image_type_index]
                      << std::endl;
            generate_image(
                image_texture,
                parseSampleImageTypeString(
                    image_type_list[current_selected_image_type_index]));
            // generate_image(image_texture, SampleImageType::GRADIENT);
            // sdl_image_texture = IMG_LoadTexture(renderer,
            // image_texture.filename.c_str());
            sdl_image_texture = create_texture(renderer, image_texture);
            image_texture_cache = image_texture;
        }

        ImGui::Combo("Image Type", &current_selected_image_type_index,
                     image_type_list, IM_ARRAYSIZE(image_type_list));

        ImGui::End();

        // Image Manipulation Window
        ImGui::Begin("Image Manipulation", &image_manipulation,
                     ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::SliderFloat("Image Noise", &image_texture.noise_value, 0.0f,
                           100.0f);

        ImGui::InputText("Image Size", image_size, sizeof(image_size));

        ImGui::End();

        // Rendering
        ImGui::Render();
        SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x,
                           io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y,
                                    clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your
    // SDL_AppQuit() function]
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
