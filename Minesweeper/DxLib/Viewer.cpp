#include "Viewer.h"

unsigned int BoxColor;
unsigned const int CLOSED_BOX_COLOR = GetColor( 150, 150, 150 );
unsigned const int OPENED_BOX_COLOR = GetColor( 240, 240, 240 );

Viewer::Viewer( Boxes* boxes, System* system ) :
	_boxes( boxes ),
	_system( system ) {
}

Viewer::~Viewer( ) {

}

void Viewer::Draw( ) {
	DrawBox( );
	DrawHeader( );
}

void Viewer::OpenAll( ) {
	for ( int i = 0; i < MAP_SIZE * MAP_SIZE; i++ ) {
		int x = i % MAP_SIZE * BOX_SIZE + 5 + BOX_SIZE / 2;
		int y = i / MAP_SIZE * BOX_SIZE + 5 + BOX_SIZE / 2 + Y_DISTANCE;

		if ( _boxes->GetIsBoxMine( i ) ) {
			DrawCircle( x, y, BOX_SIZE / 2 - 10, GetColor( 255, 0, 0 ), true );
		} else {
			DrawFormatString( x, y, GetColor( 0, 0, 0 ), "%d", _boxes->GetMineNum( i ) );
		}
	}
}

void Viewer::DrawBox( ) {
	for ( int i = 0; i < MAP_SIZE; i++ ) {
		for ( int j = 0; j < MAP_SIZE; j++ ) {

			BoxColor = _boxes->GetBoxState( i * MAP_SIZE + j ) ? OPENED_BOX_COLOR : CLOSED_BOX_COLOR;

			DrawBoxAA( j * BOX_SIZE + BOX_DISTANCE, i * BOX_SIZE + BOX_DISTANCE + Y_DISTANCE, ( j + 1 ) * BOX_SIZE, ( i + 1 ) * BOX_SIZE + Y_DISTANCE, BoxColor, TRUE );

			DrawContent( i * MAP_SIZE + j );
		}
	}
}

void Viewer::DrawContent( int num ) {

	int x = num % MAP_SIZE * BOX_SIZE + 5 + BOX_SIZE / 2;
	int y = num / MAP_SIZE * BOX_SIZE + 5 + BOX_SIZE / 2 + Y_DISTANCE;

	if ( _boxes->GetIsFlagged( num ) ) {
		DrawCircle( x, y, BOX_SIZE / 2 - 10, GetColor( 0, 255, 0 ), true );
	}

	if ( _boxes->GetBoxState( num ) ) {

		if ( _boxes->GetIsBoxMine( num ) ) {
			DrawCircle( x, y, BOX_SIZE / 2 - 10, GetColor( 255, 0, 0 ), true );
		} else {
			DrawFormatString( x, y, GetColor( 0, 0, 0 ), "%d", _boxes->GetMineNum( num ) );
		}

	}
}

void Viewer::DrawHeader( ) {
	float NowTime = _system->GetNowTime( );
	int MineNumLeft = _boxes->GetMineNumLeft( );
	DrawFormatString( 125, Y_DISTANCE / 2 - 10, GetColor( 255, 255, 255 ), "Time: %.1f", NowTime );
	DrawFormatString( 275, Y_DISTANCE / 2 - 10, GetColor( 255, 255, 255 ), "Mines: %d", MineNumLeft );
}