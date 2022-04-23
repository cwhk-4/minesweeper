#include "System.h"

System::System( Boxes* boxes ) :
	_boxes( boxes ) 
{
	StartingTime = GetNowCount( );
	IsCounting = true;
	_boxes->Init( );
}

System::~System( ) {
}

void System::Update( ) {
	if ( IsCounting ) {
		NowTime = ( GetNowCount( ) - StartingTime ) / 1000;
	}
}

float System::GetNowTime( ) {
	return NowTime;
}

void System::Init( ) {

	StopCounting( );
	
	if ( _boxes->GetIsGameOver( ) ) {
		DrawFormatString( 160, Y_DISTANCE / 2 + 20, GetColor( 255, 255, 255 ), "Click To Restart" );
	}

	if ( _boxes->GetIsGameCleared( ) ) {
		DrawFormatString( 180, Y_DISTANCE / 2 + 20, GetColor( 255, 255, 255 ), "Cleared! :D" );
	}

	if ( ( GetMouseInput( ) && MOUSE_INPUT_LEFT ) != 0 ) {
		StartingTime = GetNowCount( );
		_boxes->Init( );
		IsCounting = true;
	}

}

void System::StopCounting( ) {
	IsCounting = false;
}