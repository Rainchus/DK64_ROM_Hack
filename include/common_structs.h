typedef struct playerData {
	/* 0x00 */ char unk_00[0x7C];
	/* 0x58 */ int characterID; //02 is dk, 03 is diddy, 04 is lanky, etc
	/* 0x7C */ float xPos;
	/* 0x80 */ float yPos;
	/* 0x84 */ float zPos;
} playerData;//size 0x180

typedef struct TextOverlay {
	/* 0x000 */ char unk_00[0x15F];
	/* 0x15F */ char opacity;
	/* 0x160 */ char unk_160[0x0A];
	/* 0x16A */ char red;
	/* 0x16B */ char green;
	/* 0x16C */ char blue;
	/* 0x16D */ char unk_16D[0x0B];
	/* 0x178 */ char* string;
} TextOverlay;