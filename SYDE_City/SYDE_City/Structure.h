#pragma once
#include "SYDEstdafx.h"

class SYDE_City_Structure {
public:
	SYDE_City_Structure(CustomAsset _a, string _s) { m_Name = _s, m_Structure = _a; }
	virtual ~SYDE_City_Structure() {}


	CustomAsset getAsset() { return m_Structure; }
	string getName() { return m_Name; }
private:

protected:
	CustomAsset m_Structure;
	string m_Name;
};
