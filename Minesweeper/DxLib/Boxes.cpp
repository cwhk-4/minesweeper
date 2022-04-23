#include "Boxes.h"

const std::array< int, 8 > NEARBY =
{
	-MAP_SIZE - 1,
	-MAP_SIZE,
	-MAP_SIZE + 1,
	-1,
	1,
	MAP_SIZE - 1,
	MAP_SIZE,
	MAP_SIZE + 1,
};

const std::array< int, 4 > DIR =
{
	-MAP_SIZE,
	-1,
	1,
	MAP_SIZE,
};

Boxes::Boxes( ) {
	Init( );
}

Boxes::~Boxes( ) {
}

void Boxes::Update( ) {

	if ( GetMouseInputLog2( &Button, &MouseX, &MouseY, &LogType, TRUE ) == 0 ) {
		if ( ( Button & MOUSE_INPUT_LEFT ) != 0 ) {
			if ( LogType == MOUSE_INPUT_LOG_UP ) {
				Clicked( );
			}
		}

		if ( ( Button & MOUSE_INPUT_RIGHT ) != 0 ) {
			if ( LogType == MOUSE_INPUT_LOG_UP ) {
				Flag( );
			}
		}

		CheckIfClear( );
	}

}

bool Boxes::GetBoxState( int num ) const {
	return IsOpen[ num ];
}

bool Boxes::GetIsBoxMine( int num ) const {
	return IsMine[ num ];
}

bool Boxes::GetIsGameOver( ) const {
	return GameOverFlag;
}

bool Boxes::GetIsGameCleared( ) const {
	return ClearFlag;
}

int Boxes::GetMineNum( int num ) const {
	return MineNum[ num ];
}

void Boxes::Init( ) {

	for ( int i = 0; i < MAP_SIZE * MAP_SIZE; i++ ) {
		IsOpen[ i ] = false;
		IsMine[ i ] = false;
		IsFlag[ i ] = false;
		MineNum[ i ] = 0;
	}

	for ( int i = 0; i < MINE_NUM; i++ ) {
		int rand = GetRand( MAP_SIZE * MAP_SIZE - 1 );

		while ( IsMine[ rand ] ) {
			rand = GetRand( MAP_SIZE * MAP_SIZE - 1 );
		}

		IsMine[ rand ] = true;
		CheckMineNum( rand );
	}

	GameOverFlag = false;
	MineNumLeft = MINE_NUM;
	BoxOpened = 0;
	ClearFlag = false; 
	MineFound = 0;

}

bool Boxes::GetIsFlagged( int num ) const {
	return IsFlag[ num ];
}

int Boxes::GetMineNumLeft( ) const {
	return MineNumLeft;
}

void Boxes::Clicked( ) {

	int x = -1;
	int y = -1;

	if ( MouseX % BOX_SIZE > BOX_DISTANCE ) {
		x = MouseX / BOX_SIZE;
	}

	if ( ( MouseY - Y_DISTANCE ) % BOX_SIZE > BOX_DISTANCE ) {
		y = ( MouseY - Y_DISTANCE ) / BOX_SIZE;
	}

	if ( x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE ) {
		OpenBox( y * MAP_SIZE + x , true);
		if ( !IsFlag[ y * MAP_SIZE + x ] ) { 
			CheckIsMine( y * MAP_SIZE + x );
		}
	}

}

void Boxes::CheckIsMine( int num ) {

	if ( IsMine[ num ] ) {
		GameOverFlag = true;
	}

}

void Boxes::CheckMineNum( int num ) {

	for ( int i = 0; i < 8; i++ ) {
		if(!( num + NEARBY[i] < 0 || num+ NEARBY[i]>=MAP_SIZE*MAP_SIZE )){
			MineNum[ num + NEARBY[ i ] ] += 1;
		}

		if ( num % MAP_SIZE == 0 ) {
			if ( i == 0 || i == 3 || i == 5 ) {
				if ( !( num + NEARBY[ i ] < 0 || num + NEARBY[ i ] >= MAP_SIZE * MAP_SIZE ) ) {
					MineNum[ num + NEARBY[ i ] ] -= 1;
				}
			}
		}

		if ( num % MAP_SIZE == MAP_SIZE - 1 ) {
			if ( i == 2 || i == 4 || i == 7 ) {
				if ( !( num + NEARBY[ i ] < 0 || num + NEARBY[ i ] >= MAP_SIZE * MAP_SIZE ) ) {
					MineNum[ num + NEARBY[ i ] ] -= 1;
				}
			}
		}
	}

}

void Boxes::OpenBox( int num, bool Open ) {

	if ( IsOpen[ num ] || IsFlag[ num ]) {
		Open = false;
	}

	if ( !Open ){
		return;
	}

	IsOpen[ num ] = true;
	BoxOpened++;

	if ( !IsMine[ num ] ) {
		for ( int i = 0; i < 4; i++ ) {
			if ( num + DIR[ i ] >= 0 && num + DIR[ i ] < MAP_SIZE * MAP_SIZE && !IsMine[ num + DIR[ i ] ] ) {
				bool OpenFlag = false;

				if ( MineNum[ num ] == 0 ) {
					OpenFlag = true;
				}

				if ( num % MAP_SIZE == 0 ) {
					if ( i == 1 ) {
						if ( !( num + DIR[ i ] < 0 || num + DIR[ i ] >= MAP_SIZE * MAP_SIZE ) ) {
							OpenFlag = false;
						}
					}
				}

				if ( num % MAP_SIZE == MAP_SIZE - 1 ) {
					if ( i == 2 ) {
						if ( !( num + DIR[ i ] < 0 || num + DIR[ i ] >= MAP_SIZE * MAP_SIZE ) ) {
							OpenFlag = false;
						}
					}
				}

				OpenBox( num + DIR[ i ], OpenFlag );
			}
		}
	}
}

void Boxes::Flag( ) {

	int x = -1;
	int y = -1;

	if ( MouseX % BOX_SIZE > BOX_DISTANCE ) {
		x = MouseX / BOX_SIZE;
	}

	if ( ( MouseY - Y_DISTANCE ) % BOX_SIZE > BOX_DISTANCE ) {
		y = ( MouseY - Y_DISTANCE ) / BOX_SIZE;
	}

	if ( x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE ) {
		int num = y * MAP_SIZE + x;

		if ( IsOpen[ num ] ) {
			return;
		}

		if ( IsFlag[ num ] ) {
			IsFlag[ num ] = false;
			MineNumLeft++;
		} else {
			IsFlag[ num ] = true;
			MineNumLeft--;
		}

		if ( IsFlag[ num ] && IsMine[ num ] ) {
			MineFound++;
		}
	}
}

void Boxes::CheckIfClear( ) {

	if ( MineNumLeft == 0 && MineFound == MINE_NUM) {
		ClearFlag = true;
	}
}
