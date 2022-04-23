#pragma once
#include "DxLib.h"
#include <array>
#include "Define.h"

class Boxes {
public:
	Boxes( );
	~Boxes( );
	void Update( );
	bool GetBoxState( int num ) const;
	bool GetIsBoxMine( int num ) const;
	bool GetIsGameOver( ) const;
	bool GetIsGameCleared( ) const;
	int GetMineNum( int num ) const;
	void Init( );
	bool GetIsFlagged( int num ) const;
	int GetMineNumLeft( ) const;

private:
	void Clicked( );
	void CheckIsMine( int num );
	void CheckMineNum( int num );
	void OpenBox( int num, bool Open );
	void Flag( );
	void CheckIfClear( );

private:
	std::array< bool, MAP_SIZE * MAP_SIZE > IsOpen;
	std::array< bool, MAP_SIZE * MAP_SIZE > IsMine;
	std::array< int, MAP_SIZE * MAP_SIZE > MineNum;
	std::array< bool, MAP_SIZE * MAP_SIZE > IsFlag;

private:
	bool GameOverFlag;
	int MouseX;
	int MouseY;
	int Button;
	int LogType;
	int MineNumLeft;
	int BoxOpened;
	bool ClearFlag;
	int MineFound;
};

