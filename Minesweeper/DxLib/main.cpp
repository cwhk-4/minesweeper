#include "DxLib.h"
#include "Viewer.h"
#include "Boxes.h"
#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	ChangeWindowMode(true);

	SetGraphMode( MAP_SIZE * BOX_SIZE + BOX_DISTANCE, MAP_SIZE * BOX_SIZE + BOX_DISTANCE + Y_DISTANCE, 16 );

	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen( DX_SCREEN_BACK );

	Boxes* boxes = new Boxes;
	System* system = new System( boxes );
	Viewer* viewer = new Viewer( boxes, system );

	while ( ScreenFlip( ) == 0 && ProcessMessage( ) == 0 && ClearDrawScreen( ) == 0 ) {
		viewer->Draw( );

		if ( boxes->GetIsGameOver() || boxes->GetIsGameCleared( ) ) {
			system->Init( );
		}
		else {
			system->Update( );
			boxes->Update( );
		}

		if ( CheckHitKey( KEY_INPUT_SPACE ) ) {
			viewer->OpenAll( );
		}
	}

	DxLib_End();
	return 0;
}