typedef struct playerData {
	/* 0x00 */ char unk_00[0x7C];
	/* 0x58 */ int characterID; //02 is dk, 03 is diddy, 04 is lanky, etc
	/* 0x7C */ float xPos;
	/* 0x80 */ float yPos;
	/* 0x84 */ float zPos;
} playerData;//size 0x180