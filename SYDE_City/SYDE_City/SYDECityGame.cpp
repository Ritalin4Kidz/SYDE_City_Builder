#include "SYDECityGame.h"

SYDECityGame::SYDECityGame()
{
	// ASSET LOADING
	m_bg = CustomAsset(60, 30, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 30, 30));
	m_Map = CustomAsset(2000, 1000, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\MainMapSQ.bmp", 1000, 1000));
	m_Structure = CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Landscape_Sprites\\Sand.bmp", 3, 3));
}

ConsoleWindow SYDECityGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	switch (m_Scene)
	{
	case MainMenu:
		break;
	case MainMap:
		return MainMap_Draw(window, windowWidth, windowHeight);
	default:
		break;
	}
	return window;
}

ConsoleWindow SYDECityGame::MainMap_Draw(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_bg.draw_asset(window, Vector2(0, 0));
	window = m_Map.draw_asset(window, Vector2(camera_Pos.getX() - 20, camera_Pos.getY() - 10), windowWidth, windowHeight);
	window = DrawStructuresOnMap(window);
	window = DrawStructureAtCenter(window);
	window.setTextAtPoint(Vector2(0, 1), std::to_string((int)camera_Pos.getX()) + "," + std::to_string((int)camera_Pos.getY()), RED_WHITE_BG);

	if (SYDEKeyCode::get_key('S')._CompareState(KEY) && camera_Pos.getY() < 1000)
	{
		camera_Pos.addY(1);
	}
	if (SYDEKeyCode::get_key('W')._CompareState(KEY) && camera_Pos.getY() > 0)
	{
		camera_Pos.addY(-1);
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEY) && camera_Pos.getX() < 1000)
	{
		camera_Pos.addX(2);
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEY) && camera_Pos.getX() > 0)
	{
		camera_Pos.addX(-2);
	}
	return window;
}

ConsoleWindow SYDECityGame::DrawStructureAtCenter(ConsoleWindow window)
{
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		int i = static_cast<int>(m_PlacementType);
		i++;
		if (i > 2)
			i = 0;
		m_PlacementType = static_cast<_Placements>(i);
		switch (m_PlacementType)
		{
		case Land:
			m_Structure = CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Landscape_Sprites\\Sand.bmp", 3, 3));
			break;
		case Road:
			m_Structure = CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Landscape_Sprites\\Road_Horizontal.bmp", 3, 3));
			break;
		case Building:
			m_Structure = CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Landscape_Sprites\\Road_T.bmp", 3, 3));
			break;
		default:
			break;

		}
	}	
	window = m_Structure.draw_asset(window, Vector2(20,10));
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN) && CanPlace())
	{
		_structures.push_back(_SCB_Structure(Vector2(camera_Pos.getX() + 20, camera_Pos.getY() + 10), m_Structure));
	}
	return window;
}

ConsoleWindow SYDECityGame::DrawStructuresOnMap(ConsoleWindow window)
{
	for (int i = 0; i < _structures.size(); i++)
	{
		if (_structures[i].pos.distance(Vector2(camera_Pos)) < 50)
		{
			window = _structures[i]._a.draw_asset(window, _structures[i].pos - camera_Pos);
		}
	}
	return window;
}

bool SYDECityGame::CanPlace()
{
	if (m_PlacementType == Land)
	{
		for (int i = 0; i < _structures.size(); i++)
		{
			if (_structures[i].pos.distance(Vector2(camera_Pos.getX() + 20, camera_Pos.getY() + 10)) < 3)
			{
				return false;
			}
		}
	}
	return true;
}

vector<string> SYDECityGame::Split(string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	std::vector<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < a_String.length(); i++)
		{
			if (a_String[i] == splitter)
			{
				splitString[arrayNo] = a_String.substr(0, i);
				a_String = a_String.substr(i + 1, a_String.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = a_String;
	return splitString;
}

