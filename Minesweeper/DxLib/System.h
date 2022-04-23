#pragma once
#include "DxLib.h"
#include "Boxes.h"

class System {
public:
	System( Boxes* boxes );
	~System( );
	void Update( );
	float GetNowTime( );
	void Init( );
	void StopCounting( );

private:
	bool IsCounting;
	float StartingTime;
	float NowTime;

private:
	Boxes* _boxes;
};