#ifndef __TETRIS_HELPER_H__
#define __TETRIS_HELPER_H__

#include <Windows.h>
#include <cstdio>

KEY_EVENT_RECORD krec;
void putStringOnPosition(int x, int y, const char* content) {
	// Move Cursor
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	// Print string
	printf("%s", content);
}

void showConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void drawPosition(int x, int y, bool filled) {
	putStringOnPosition(x * 2, y, filled ? "■" : "□");
}

bool keyState(char c) {
	short ret;
	switch (c) {
	case 'a': ret = GetKeyState(0x41); break;
	case 'd': ret = GetKeyState(0x44); break;
	case 's': ret = GetKeyState(0x53); break;
	case 'w': ret = GetKeyState(0x57); break;
	default: return false;
	}
	return ret != 0 && ret != 1;
}

#endif // !__TETRIS_HELPER_H__

//위 전체는 미리 작성된 코드로, 윈도우에서 사용되는 콘솔에 원하는 위치에 텍스트를 출력하는 함수와
//사용자로부터 키보드를 입력받아서 키보드에 돌려져있는 상태를 받아오는 함수들이 포함되어 있습니다.

//60fps 게임의 경우 1초에 60번, 즉 0.016초마다 루프로서 게임이 갱신되게 됩니다.
//이때 60분의 1초를 델타타임이라고 부릅니다.

//때문에 우리는 게임의 모양새를 갖추기 위해
//1. 60분의 1초마다 갱신되는 무한 루프를 생성합니다.
//2. 60분의 1초 단위로 갱신되는 게임 데이터를 화면에 출력을 해주는 디스플레이 객체를 생성합니다.

//무한 루프는 메인 함수에서 동작합니다.
//루프가 끝날때마다 나오는 결과에 따라 게임의 지속을 결정합니다.