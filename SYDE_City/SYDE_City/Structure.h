#pragma once
#include "SYDEstdafx.h"

class SYDE_City_Structure {
public:
	SYDE_City_Structure(CustomAsset _a, string _s) { m_Name = _s, m_Structure = _a; }
	SYDE_City_Structure(CustomAsset _a, string _s, Vector2 offset) { m_Name = _s, m_Structure = _a; PlacementOffset = offset; }
	virtual ~SYDE_City_Structure() {}


	CustomAsset getAsset() { return m_Structure; }
	string getName() { return m_Name; }
	Vector2 getPlacementOffset() { return PlacementOffset; }
private:

protected:
	Vector2 PlacementOffset = Vector2(0);
	CustomAsset m_Structure;
	string m_Name;
};
