#pragma once
#include "SYDEWindowGame.h"
#include "ConsoleWindow.h"
#include "SYDETime.h"
#include <windows.h>
#include <iostream>
#include <string>
#include "Artwork.h"
#include "AssetsClass.h"
#include "CustomAnimationAsset.h"
#include "SYDEScreenshot.h"
#include "CustomAsset.h"
#include "Activation.h"
#include "SYDECredits.h"
#include "Settings.h"
#include <vector>
#include <gdiplus.h>
#include "SYDEFPS.h"
using namespace std;
using namespace Gdiplus;
class SYDEGamePlay {
public:
	/// <summary>
	/// Initialize window to the size windows class created with
	/// </summary>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	static void initialize_window(const HANDLE hOut, ConsoleWindow& window);
	/// <summary>
	/// Add FPS counter to main play function call
	/// </summary>
	/// <param name="b"></param>
	static void showFPS(bool b) { FPS_Counter = b; }

	/// <summary>
	/// Change if scrollbar is removed on window init
	/// </summary>
	/// <param name="remove"></param>
	static void Remove_Scrollbar_On_Init(bool remove) { remove_scrollbar = remove; }

	/// <summary>
	/// Change if the window is resized on window init
	/// </summary>
	/// <param name="resize"></param>
	static void Resize_Window_On_Init(bool resize) { resize_window_on_init = resize; }

	/// <summary>
	/// Opening splashscreens (optional for starting up the program)
	/// </summary>
	/// <param name="chimePath"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="artVars"></param>
	static void opening_splashscreens(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);
	/// <summary>
	/// quick startup, splashscreens required for play_game function
	/// </summary>
	/// <param name="chimePath"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="artVars"></param>
	static void activate_bySplashscreen(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);

	static void hidden_splashsceen_001(LPCWSTR chimePath, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, AssetsClass astVars);
	/// <summary>
	/// reset the window to initialize settings, useful if window starts to mess up
	/// </summary>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	static void reset_void(COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight);
	/// <summary>
	/// OLDER VERSION OF THE PLAY_GAME LOOP FUNCTION
	/// AS OF 5/10/2020 THIS FUNCTION IS LEFT IN FOR LEGACY
	/// </summary>
	/// <param name="SYDE_GAME"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="deltaTime"></param>
	/// <returns></returns>
	static ConsoleWindow play_game(SYDEWindowGame* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow window, int windowWidth, int windowHeight, SYDETIME& deltaTime);
	/// <summary>
	/// Core game loop for running SYDEWindow games
	/// </summary>
	/// <param name="SYDE_GAME"></param>
	/// <param name="start"></param>
	/// <param name="hOut"></param>
	/// <param name="window"></param>
	/// <param name="windowWidth"></param>
	/// <param name="windowHeight"></param>
	/// <param name="deltaTime"></param>
	/// <returns></returns>
	static ConsoleWindow play(SYDEWindowGame* SYDE_GAME, COORD start, const HANDLE hOut, ConsoleWindow window, int windowWidth, int windowHeight, SYDETIME& deltaTime);
	/// <summary>
	/// shutdown gdiplus
	/// </summary>
	static void exit() {
		GdiplusShutdown(gdiplusToken);
	}
private:
	static void _introductionScript();
	static void _introCreditsScript(ConsoleWindow& window);
	static void _drawBee(int baseY, int baseX, bool setUp, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);
	static void _poweredBySYDEEngine(int baseY, int baseX, bool setUp, COORD start, const HANDLE hOut, ConsoleWindow& window, int windowWidth, int windowHeight, Artwork artVars);

	static bool _activated;
	static bool FPS_Counter;

	static string _returnRandomNonsense();
	static Settings config;
	static vector<string> cheatCodes;

	//GDI VALUES
	static ULONG_PTR gdiplusToken;
	static GdiplusStartupInput startupInput;

	//OTHER SETTINGS
	static bool resize_window_on_init;
	static bool remove_scrollbar;
};