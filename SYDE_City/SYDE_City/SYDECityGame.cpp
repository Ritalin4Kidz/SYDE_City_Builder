#include "SYDECityGame.h"

SYDECityGame::SYDECityGame()
{
	// ASSET LOADING
	m_bg = CustomAsset(60, 30, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 30, 30));
	m_Map = CustomAsset(2000, 1000, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\MainMapSQ.bmp", 1000, 1000));
	m_StructureOverlayLand = CustomAsset(2000, 1000, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Overlay.bmp", 1000, 1000));
	m_StructureOverlayBuildings = CustomAsset(2000, 1000, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Overlay.bmp", 1000, 1000));

	m_LandStructures = vector<SYDE_City_Structure>({
		SYDE_City_Structure(CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Landscape_Sprites\\Sand.bmp", 3, 3)), "Sand Small"),
		SYDE_City_Structure(CustomAsset(10, 5, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Landscape_Sprites\\SandLarge.bmp", 5, 5)), "Sand Large", Vector2(-2,-1)),
		SYDE_City_Structure(CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Landscape_Sprites\\Grass.bmp", 3, 3)), "Grass Small"),
		SYDE_City_Structure(CustomAsset(10, 5, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Landscape_Sprites\\GrassLarge.bmp", 5, 5)), "Grass Large", Vector2(-2,-1))
		});

	m_BuildingStructures = vector<SYDE_City_Structure>({
		SYDE_City_Structure(CustomAsset(18,9, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Building_Sprites\\NcDonalds.bmp", 9, 9)), "NcDonald's", Vector2(-6,-3)),
		});

	m_RoadStructures = vector<SYDE_City_Structure>({
		SYDE_City_Structure(CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Road_Sprites\\Road_Horizontal.bmp", 3, 3)), "Road Horizontal"),
		SYDE_City_Structure(CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Road_Sprites\\Road_T.bmp", 3, 3)), "Road T"),
		SYDE_City_Structure(CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Road_Sprites\\Road_Turn.bmp", 3, 3)), "Road Turn"),
		SYDE_City_Structure(CustomAsset(6, 3, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\\Road_Sprites\\Road_Cross.bmp", 3, 3)), "Road Cross")
		});

	m_Structure = m_LandStructures[0].getAsset();
	m_CurrentStructure = m_LandStructures[0].getName();
	m_PlacementStr = " LAND ";
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
	window = m_StructureOverlayLand.draw_asset(window, Vector2(camera_Pos.getX() - 20, camera_Pos.getY() - 10), windowWidth, windowHeight);
	window = m_StructureOverlayBuildings.draw_asset(window, Vector2(camera_Pos.getX() - 20, camera_Pos.getY() - 10), windowWidth, windowHeight);
	//window = DrawStructuresOnMap(window);
	window = DrawStructureAtCenter(window);
	window.setTextAtPoint(Vector2(0, 1), std::to_string((int)(camera_Pos.getX())/2) + "," + std::to_string((int)camera_Pos.getY()), RED_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 18), "TAB: " + m_PlacementStr, BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 19), "Z,X: " + m_CurrentStructure, BLACK_WHITE_BG);

	if (SYDEKeyCode::get_key('S')._CompareState(KEY) && camera_Pos.getY() < 985)
	{
		camera_Pos.addY(1);
	}
	if (SYDEKeyCode::get_key('W')._CompareState(KEY) && camera_Pos.getY() > 10)
	{
		camera_Pos.addY(-1);
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEY) && camera_Pos.getX() < 1970)
	{
		camera_Pos.addX(2);
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEY) && camera_Pos.getX() > 20)
	{
		camera_Pos.addX(-2);
	}
	return window;
}

ConsoleWindow SYDECityGame::DrawStructureAtCenter(ConsoleWindow window)
{
	if (SYDEKeyCode::get_key('Z')._CompareState(KEYDOWN))
	{
		m_SelectedItem_Index--;
		switch (m_PlacementType)
		{
		case Land:
			if (m_SelectedItem_Index < 0)
			{
				m_SelectedItem_Index = m_LandStructures.size() - 1;
			}
			m_Structure = m_LandStructures[m_SelectedItem_Index].getAsset();
			m_CurrentStructure = m_LandStructures[m_SelectedItem_Index].getName();
			m_PlacementOffset = m_LandStructures[m_SelectedItem_Index].getPlacementOffset();
			break;
		case Road:
			if (m_SelectedItem_Index < 0)
			{
				m_SelectedItem_Index = m_RoadStructures.size() - 1;
			}
			m_Structure = m_RoadStructures[m_SelectedItem_Index].getAsset();
			m_CurrentStructure = m_RoadStructures[m_SelectedItem_Index].getName();
			m_PlacementOffset = m_RoadStructures[m_SelectedItem_Index].getPlacementOffset();
			break;
		case Building:
			if (m_SelectedItem_Index < 0)
			{
				m_SelectedItem_Index = m_BuildingStructures.size() - 1;
			}
			m_Structure = m_BuildingStructures[m_SelectedItem_Index].getAsset();
			m_CurrentStructure = m_BuildingStructures[m_SelectedItem_Index].getName();
			m_PlacementOffset = m_BuildingStructures[m_SelectedItem_Index].getPlacementOffset();
			break;
		default:
			break;

		}
	}
	else if (SYDEKeyCode::get_key('X')._CompareState(KEYDOWN))
	{
		m_SelectedItem_Index++;
		switch (m_PlacementType)
		{
		case Land:
			if (m_SelectedItem_Index >= m_LandStructures.size())
			{
				m_SelectedItem_Index = 0;
			}
			m_Structure = m_LandStructures[m_SelectedItem_Index].getAsset();
			m_CurrentStructure = m_LandStructures[m_SelectedItem_Index].getName();
			m_PlacementOffset = m_LandStructures[m_SelectedItem_Index].getPlacementOffset();
			break;
		case Road:
			if (m_SelectedItem_Index >= m_RoadStructures.size())
			{
				m_SelectedItem_Index = 0;
			}
			m_Structure = m_RoadStructures[m_SelectedItem_Index].getAsset();
			m_CurrentStructure = m_RoadStructures[m_SelectedItem_Index].getName();
			m_PlacementOffset = m_RoadStructures[m_SelectedItem_Index].getPlacementOffset();
			break;
		case Building:
			if (m_SelectedItem_Index >= m_BuildingStructures.size())
			{
				m_SelectedItem_Index = 0;
			}
			m_Structure = m_BuildingStructures[m_SelectedItem_Index].getAsset();
			m_CurrentStructure = m_BuildingStructures[m_SelectedItem_Index].getName();
			m_PlacementOffset = m_BuildingStructures[m_SelectedItem_Index].getPlacementOffset();
			break;
		default:
			break;

		}
	}
	else if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		int i = static_cast<int>(m_PlacementType);
		i++;
		if (i > 2)
			i = 0;
		m_PlacementType = static_cast<_Placements>(i);
		switch (m_PlacementType)
		{
		case Land:
			m_Structure = m_LandStructures[0].getAsset();
			m_CurrentStructure = m_LandStructures[0].getName();
			m_SelectedItem_Index = 0;
			m_PlacementStr = " LAND ";
			m_PlacementOffset = m_LandStructures[0].getPlacementOffset();
			break;
		case Road:
			m_Structure = m_RoadStructures[0].getAsset();
			m_CurrentStructure = m_RoadStructures[0].getName();
			m_SelectedItem_Index = 0;
			m_PlacementStr = " ROADS ";
			m_PlacementOffset = m_RoadStructures[0].getPlacementOffset();
			break;
		case Building:
			m_Structure = m_BuildingStructures[0].getAsset();
			m_CurrentStructure = m_BuildingStructures[0].getName();
			m_SelectedItem_Index = 0;
			m_PlacementStr = " BUILDINGS ";
			m_PlacementOffset = m_BuildingStructures[0].getPlacementOffset();
			break;
		default:
			break;

		}
	}	
	window = m_Structure.draw_asset(window, Vector2(20 + m_PlacementOffset.getX() ,10 + m_PlacementOffset.getY()));
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN) && CanPlace())
	{
		if (m_PlacementType == Land)
		{
			m_StructureOverlayLand.AddAssetOnto(m_Structure, camera_Pos + m_PlacementOffset);
		}
		else
		{
			m_StructureOverlayBuildings.AddAssetOnto(m_Structure, camera_Pos + m_PlacementOffset);
		}
		//_structures.push_back(_SCB_Structure(Vector2(camera_Pos.getX() + 20, camera_Pos.getY() + 10), m_Structure));
	}
	return window;
}

bool SYDECityGame::CanPlace()
{
	if (m_PlacementType == Land)
	{
		//for (int i = 0; i < _structures.size(); i++)
		//{
		//	if (_structures[i].pos.distance(Vector2(camera_Pos.getX() + 20, camera_Pos.getY() + 10)) < 3)
		//	{
		//		return false;
		//	}
		//}
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

