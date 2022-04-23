#pragma once
#include "DxLib.h"
#include <array>
#include "Define.h"
#include "Boxes.h"
#include "System.h"

class Viewer {
public:
	Viewer( Boxes* boxes, System* system );
	~Viewer( );
	void Draw( );
	void OpenAll( );

private:
	void DrawBox( );
	void DrawContent( int num );
	void DrawHeader( );

private:
	Boxes* _boxes;
	System* _system;
};