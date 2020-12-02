#pragma once
#include "SYDEstdafx.h"
#include "Structure.h"
enum _SCScene {
	UnknownScene,
	MainMenu,
	MainMap,
	TestBuilding
};


enum _Placements {
	Building,
	Road,
	Land
};

struct _SCB_Structure
{
	_SCB_Structure(Vector2 v, CustomAsset a) { _a = a; pos = v; }
	CustomAsset _a;
	Vector2 pos;
};


class SYDECityGame : public SYDEWindowGame {
public:
	SYDECityGame();
	virtual ~SYDECityGame() {}

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;

	ConsoleWindow MainMap_Draw(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow DrawStructureAtCenter(ConsoleWindow window);

	bool CanPlace();

	AssetsClass astVars;
	Vector2 camera_Pos = Vector2(100,250);
	static vector<string> Split(string a_String, char splitter);
private:
	_SCScene m_Scene = MainMap;
	_Placements m_PlacementType = Land;

	CustomAsset m_bg;
	CustomAsset m_Map;
	CustomAsset m_StructureOverlayLand;
	CustomAsset m_StructureOverlayBuildings;
	CustomAsset m_Structure;

	int m_SelectedItem_Index = 0;
	vector<SYDE_City_Structure> m_LandStructures;
	vector<SYDE_City_Structure> m_RoadStructures;
	vector<SYDE_City_Structure> m_BuildingStructures;
	string m_CurrentStructure = "";
	string m_PlacementStr = "";
	Vector2 m_PlacementOffset = Vector2(0);
};
