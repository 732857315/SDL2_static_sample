/*//
//
//
//
*///

/*标准库*/
#include <stdio.h>
/*SDL2*/
#include <SDL.h>
#include <SDL_opengl.h>
/*imgui*/
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"

/*宏定义*/
//#define OSISLINUX //linux系统

#define SCREEN_WIDTH  1280 //横向像素个数
#define SCREEN_HEIGHT 720 //纵向像素个数

//将printf重定向到stderr
//#define printf(...) fprintf(stderr,__VA_ARGS__)

/*全局变量*/
SDL_Window* my_sdl_window = NULL;
SDL_Surface* my_sdl_screenSurface = NULL;
SDL_GLContext my_sdl_gl_context = NULL;

/// <summary>
/// SDL初始化
/// </summary>
/// <returns></returns>
bool MY_SDL_Init()
{
	//初始化SDL（视频）并判断是否成功
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//若失败，输出错误信息
		printf("SDL_Init error: %s\n", SDL_GetError());
		//直接退出整个程序
		return false;
	}
	//printf("SDL_Init OK!\n");
	//创建窗口
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	my_sdl_window = SDL_CreateWindow(
		"SDL2范例",//窗口标题（支持UTF-8无bom，但是必须将你的源文件也保存为UTF-8 无bom）
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,//SDL窗口默认位置（指定一个偏移量或居中）
		SCREEN_WIDTH, SCREEN_HEIGHT,//窗口大小 
		SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL //SDL_WINDOW_BORDERLESS
	);

	//判断窗口是否创建成功
	if (my_sdl_window == NULL)
	{
		printf("SDL_CreateWindow error: %s\n", SDL_GetError());
		return false;
	}

	printf("SDL初始化完成\n");



	return true;
}

/// <summary>
/// SDL关闭
/// </summary>
void MY_SDL_Close()
{

	//销毁窗口
	SDL_DestroyWindow(my_sdl_window);
	my_sdl_window = NULL;
	//退出SDL
	SDL_Quit();
	
	// 检查错误
	//SDL_SetError("test");
	const char* sdlError = SDL_GetError();
	if (sdlError !=NULL && *sdlError !=NULL) {
		printf("SDL_Quit error: %s\n", sdlError); //读出最后一个错误 //如果未处理
	}
}

//class DisplaySurface
//{
//public:
//	DisplaySurface(SDL_Surface* displaySurface = NULL)
//	{
//
//	}
//	~DisplaySurface()
//	{
//	}
//
//private:
//
//};

/// <summary>
/// 加载bmp为SDL_Surface
/// </summary>
/// <param name="filepath"></param>
/// <returns></returns>
SDL_Surface* MY_SDL_Loadbmp(char* filepath)
{
	SDL_Surface* pictureSurface = SDL_LoadBMP(filepath);
	if (!pictureSurface)
	{
		printf("Unable to load image:%s SDL_LoadBMP Error: %s\n", filepath, SDL_GetError());
		return NULL;
	}
	return pictureSurface;
}
/// <summary>
/// imgui显示
/// </summary>
void showimgui()
{

	my_sdl_gl_context = SDL_GL_CreateContext(my_sdl_window);
    SDL_GL_MakeCurrent(my_sdl_window, my_sdl_gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync 开垂直同步 和显示器刷新一致

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(my_sdl_window, my_sdl_gl_context);
    ImGui_ImplOpenGL2_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    //IM_ASSERT(font != nullptr);
#define usechinese
#ifdef usechinese
	#define maxnumttf 1
	const char* ttffrees[maxnumttf] = {"./Fonts/ArialUni.ttf"};
	ImFont* font = nullptr;
	int i = 0;
	while (font == nullptr)
	{
		 
		//font = io.Fonts->AddFontFromFileTTF(ttffrees[i], 16.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull()); //21x MB 英文默认才 9x M
		font = io.Fonts->AddFontFromFileTTF(ttffrees[i], 16.0f, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon()); //13x MB 只有2500多中文 类似GB2312-80
		
		i++;
		if (i >= maxnumttf)
		{
			break;
		}
	}
	printf("fonts: %s\n", ttffrees[i-1]);
	IM_ASSERT(font != nullptr);
#endif

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
	bool closewindow = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE)
				{
					closewindow = true;

				}
			}
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(my_sdl_window))
                done = true;
        }
        if (SDL_GetWindowFlags(my_sdl_window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
		// 开启imgui的界面
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 1.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window|示例窗口", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window|另一窗口", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SetWindowFontScale(f); // 设置字体缩放比例

            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;

			

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
		if (closewindow) {
			ImGui::Begin("closewindow", &closewindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("是否关闭？");
			if (ImGui::Button("关闭")) {
				done = true;
			}
			if (ImGui::Button("取消")) {
				closewindow = false;
			}
			ImGui::End();
		}
        // Rendering
		// 显示
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(my_sdl_window);
    }

    // Cleanup 
	//清理
	io.Fonts->Clear();

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(my_sdl_gl_context);
}
/// <summary>
/// 测试界面
/// </summary>
void showtest()
{
    //这些代码是什么意思不需要了解
	SDL_DisplayMode displayMode;
	SDL_GetWindowDisplayMode(my_sdl_window, &displayMode);
	//获取屏幕刷新率，并求出延迟时间
	float SCREEN_REFRESH_INTERVAL = (float)(1000.0 / displayMode.refresh_rate - 1);

	printf("FPS : %d Refresh interval = %f ms\n", displayMode.refresh_rate, SCREEN_REFRESH_INTERVAL);

	//Event handler
	SDL_Event events;
	volatile bool RunState = true;
	//当程序一直运行时
	while (RunState)
	{
		//创建一个 surface，直接将整个屏幕当作一个 surface 处理
		my_sdl_screenSurface = SDL_GetWindowSurface(my_sdl_window);
		if (my_sdl_screenSurface == NULL)
		{
			printf("SDL_GetWindowSurface error: %s", SDL_GetError());
			return ;
		}
		//向 surface 填充颜色
		SDL_FillRect(
			my_sdl_screenSurface,
			NULL,
			SDL_MapRGB(
				my_sdl_screenSurface->format,//暂不研究
				0xFF, 0x00, 0x00//#FF0000 红色
			)
		);
		//刷新WindowSurface
		SDL_UpdateWindowSurface(my_sdl_window);
		//指针释放
		SDL_FreeSurface(my_sdl_screenSurface);
		my_sdl_screenSurface = NULL;
		//处理队列中的消息
		while (SDL_PollEvent(&events)!=0)
		{
			if (events.type == SDL_KEYDOWN)
			{
				if (events.key.keysym.sym <= 'z'&& events.key.keysym.sym >= 'a') {
					printf("keydown : %c\n", events.key.keysym.sym);
				}
				//SDL_KeyCode::SDLK_LCTRL
				if (events.key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE)
				{
					RunState = false;
					goto _quit;
				}
			}
			//如果触发了关闭窗口的事件
			if (events.type == SDL_QUIT)
			{
				RunState = false;
				goto _quit;
				
			}
		}
		SDL_GetWindowDisplayMode(my_sdl_window, &displayMode);
		//获取屏幕刷新率，并求出延迟时间
		SCREEN_REFRESH_INTERVAL = (float)(1000.0 / displayMode.refresh_rate - 1);
		//延迟一会，降低 CPU 占用
		SDL_Delay((Uint32)SCREEN_REFRESH_INTERVAL);
	}
_quit:
	return;

}

/// <summary>
/// main
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{
#ifndef OSISLINUX
	system("chcp 65001"); //更改编码utf8
#else
	system("export LANG=en_US.UTF-8");
#endif // !OSISLINUX

	if (!MY_SDL_Init()) //初始化失败则退出
	{
		return -1;
	}

    showimgui();//二选一
	//showtest(); //二选一

	printf("关闭 SDL2 window\n");

	MY_SDL_Close();

	return 0;
}

