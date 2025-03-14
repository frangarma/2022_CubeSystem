/*
 * TimesNewRomas_8x12.h
 *
 * Created: 23/09/2018 16:24:50
 *  Author: Fran
 */ 

// link: https://geoffg.net/Downloads/GLCD_Driver/glcd_library_1_0.h

#ifndef TIMESNEWROMAS_8X12_H_
#define TIMESNEWROMAS_8X12_H_

// Unidimentional array
//const uint8_t Ascii_2[21][12] PROGMEM={     // Refer to "Times New Roman" Font Database...

/*const uint8_t Ascii_2[] PROGMEM={     // Refer to "Times New Roman" Font Database...
		0,0,0,0,0,0,0,0,0,0,0,0,							// ' ' 32
		0,24,60,60,60,24,24,0,24,24,0,0,                // '!' 33
		54,54,54,20,0,0,0,0,0,0,0,0,                    // '"' 34
		0,108,108,108,254,108,108,254,108,108,0,0,      // '#' 35
		24,24,124,198,192,120,60,6,198,124,24,24,       // '$' 36
		0,0,0,98,102,12,24,48,102,198,0,0,              // '%' 37
		0,56,108,56,56,118,246,206,204,118,0,0,         // '&' 38
		12,12,12,24,0,0,0,0,0,0,0,0,                    // ''' 39
		0,12,24,48,48,48,48,48,24,12,0,0,               // '(' 40
		0,48,24,12,12,12,12,12,24,48,0,0,               // ')' 41
		0,0,0,108,56,254,56,108,0,0,0,0,                // '*' 42
		0,0,0,24,24,126,24,24,0,0,0,0,                  // '+' 43
		0,0,0,0,0,0,0,12,12,12,24,0,                    // ',' 44
		0,0,0,0,0,254,0,0,0,0,0,0,                      // '-' 45
		0,0,0,0,0,0,0,0,24,24,0,0,                      // '.' 46
		0,0,2,6,12,24,48,96,192,128,0,0,                // '/' 47
		//0,124,198,206,222,246,230,198,198,124,0,0,      // '0' 48
		0,0,248,3,252,7,6,12,6,12,252,7,248,3,0,0,	//	

		//0,24,120,24,24,24,24,24,24,126,0,0,            // '1' 49
		//0,0,4,2,4,2,254,3,254,3,0,2,0,2,0,0,			// 1 vertical 16 bytes
		//0x00,0X00,0x00,0X02,0x04,0X02,0x07,0XFE,0x07,0XFE,0x00,0X02,0x00,0X02,0x00,0X00, // 1 TEST
		//0x00,0x00,0x04,0x00,0x04,0x02,0x07,0xFE,0x07,0xFE,0x04,0x00,0x04,0x00,0x00,0x00, // 1 TEST_1
		//0x00,0x00,0x02,0x00,0x02,0x04,0xFE,0x07,0xFE,0x07,0x02,0x00,0x02,0x00,0x00,0x00,//1 TEST_2 -> lo dibuja al rev�s
		0,0,4,8,4,8,254,15,254,15,0,8,0,8,0,0, 	// 1 test 3
		0,124,198,198,12,24,48,96,198,254,0,0,          // '2' 50
		//0x00,0x00,0x01,0x86,0x01,0xC7,0x01,0x71,0x01,0x3F,0x01,0x0E,0x00,0x00,	// 0x32
		0,124,198,6,6,60,6,6,198,124,0,0,               // '3' 51
		0,12,28,60,108,204,254,12,12,12,0,0,             // '4' 52
		0,254,192,192,192,252,6,6,198,124,0,0,			// '5' 53
		0,124,198,192,192,252,198,198,198,124,0,0,      // '6' 54
		0,254,198,12,24,48,48,48,48,48,0,0,             // '7' 55
		0,124,198,198,198,124,198,198,198,124,0,0,      // '8' 56
		0,124,198,198,198,126,6,6,198,124,0,0,          // '9' 57
		//0x00,0x00,0x80,0x38,0x80,0x44,0x80,0x44,0x00,0x45,0x00,0x3E,0x00,0x00,	// 0x39
		0,0,0,12,12,0,0,12,12,0,0,0,                    // ':' 58
		0,0,0,12,12,0,0,12,12,12,24,0,                  // ';' 59
		0,12,24,48,96,192,96,48,24,12,0,0,              // '<' 60
		0,0,0,0,254,0,254,0,0,0,0,0,                    // '=' 61
		0,96,48,24,12,6,12,24,48,96,0,0,                // '>' 62
		0,124,198,198,12,24,24,0,24,24,0,0,             // '?' 63
		0,124,198,198,222,222,222,220,192,126,0,0,      // '@' 64
		0,56,108,198,198,198,254,198,198,198,0,0,       // 'A' 65
		0,252,102,102,102,124,102,102,102,252,0,0,      // 'B' 66
		0,60,102,192,192,192,192,192,102,60,0,0,        // 'C' 67
		0,248,108,102,102,102,102,102,108,248,0,0,      // 'D' 68
		0,254,102,96,96,124,96,96,102,254,0,0,          // 'E' 69
		0,254,102,96,96,124,96,96,96,240,0,0,           // 'F' 70
		0,124,198,198,192,192,206,198,198,124,0,0,      // 'G' 71
		0,198,198,198,198,254,198,198,198,198,0,0,      // 'H' 72
		0,60,24,24,24,24,24,24,24,60,0,0,               // 'I' 73
		0,60,24,24,24,24,24,216,216,112,0,0,			// 'J' 74
		0,198,204,216,240,240,216,204,198,198,0,0,      // 'K' 75
		0,240,96,96,96,96,96,98,102,254,0,0,            // 'L' 76
		0,198,198,238,254,214,214,214,198,198,0,0,      // 'M' 77
		0,198,198,230,230,246,222,206,206,198,0,0,      // 'N' 78
		0,124,198,198,198,198,198,198,198,124,0,0,      // 'O' 79
		0,252,102,102,102,124,96,96,96,240,0,0,         // 'P' 80
		0,124,198,198,198,198,198,198,214,124,6,0,      // 'Q' 81
		0,252,102,102,102,124,120,108,102,230,0,0,      // 'R' 82
		0,124,198,192,96,56,12,6,198,124,0,0,           // 'S' 83
		0,126,90,24,24,24,24,24,24,60,0,0,              // 'T' 84
		0,198,198,198,198,198,198,198,198,124,0,0,      // 'U' 85
		0,198,198,198,198,198,198,108,56,16,0,0,        // 'V' 86
		0,198,198,214,214,214,254,238,198,198,0,0,      // 'W' 87
		0,198,198,108,56,56,56,108,198,198,0,0,         // 'X' 88
		0,102,102,102,102,60,24,24,24,60,0,0,           // 'Y' 89
		0,254,198,140,24,48,96,194,198,254,0,0,         // 'Z' 90
		0,124,96,96,96,96,96,96,96,124,0,0,             // '[' 91
		0,0,128,192,96,48,24,12,6,2,0,0,                // '\' 92
		0,124,12,12,12,12,12,12,12,124,0,0,             // ']' 93
		16,56,108,198,0,0,0,0,0,0,0,0,                   // '^' 94
		0,0,0,0,0,0,0,0,0,0,0,255,						// '_' 95
		24,24,24,12,0,0,0,0,0,0,0,0,                    // '`' 96
		0,0,0,0,120,12,124,204,220,118,0,0,             // 'a' 97
		0,224,96,96,124,102,102,102,102,252,0,0,        // 'b' 98
		0,0,0,0,124,198,192,192,198,124,0,0,            // 'c' 99
		0,28,12,12,124,204,204,204,204,126,0,0,         // 'd' 100
		0,0,0,0,124,198,254,192,198,124,0,0,            // 'e' 101
		0,28,54,48,48,252,48,48,48,120,0,0,             // 'f' 102
		0,0,0,0,118,206,198,198,126,6,198,124,          // 'g' 103
		0,224,96,96,108,118,102,102,102,230,0,0,        // 'h' 104
		0,24,24,0,56,24,24,24,24,60,0,0,                // 'i' 105
		0,12,12,0,28,12,12,12,12,204,204,120,           // 'j' 106
		0,224,96,96,102,108,120,108,102,230,0,0,        // 'k' 107
		0,56,24,24,24,24,24,24,24,60,0,0,               // 'l' 108
		0,0,0,0,108,254,214,214,198,198,0,0,            // 'm' 109
		0,0,0,0,220,102,102,102,102,102,0,0,            // 'n' 110
		0,0,0,0,124,198,198,198,198,124,0,0,            // 'o' 111
		0,0,0,0,220,102,102,102,124,96,96,240,          // 'p' 112
		0,0,0,0,118,204,204,204,124,12,12,30,           // 'q' 113
		0,0,0,0,220,102,96,96,96,240,0,0,               // 'r' 114
		0,0,0,0,124,198,112,28,198,124,0,0,             // 's' 115
		0,48,48,48,252,48,48,48,54,28,0,0,				// 't' 116
		0,0,0,0,204,204,204,204,204,118,0,0,            // 'u' 117
		0,0,0,0,198,198,198,108,56,16,0,0,              // 'v' 118
		0,0,0,0,198,198,214,214,254,108,0,0,            // 'w' 119
		0,0,0,0,198,108,56,56,108,198,0,0,              // 'x' 120
		0,0,0,0,198,198,198,206,118,6,198,124,          // 'y' 121
		0,0,0,0,254,140,24,48,98,254,0,0,               // 'z' 122
		0,14,24,24,24,112,24,24,24,14,0,0,              // '{' 123
		0,24,24,24,24,0,24,24,24,24,0,0,                // '|' 124
		0,112,24,24,24,14,24,24,24,112,0,0,             // '}' 125
		0,70,169,168,72,8,9,6,0,0,0,0                   // Degree C symbol (oC) 126
		//                      0,118,220,0,0,0,0,0,0,0,0,0,                    // '~' 126
	};*/


//Times New Romans 8x14 codificados /,0,1,2,3,4,5,6,7,8,9,:
const uint8_t Ascii_3[] PROGMEM={     // Refer to "Times New Roman" Font Database...
	0,0,0,12,0,7,192,3,248,0,60,0,6,0,0,0,				// '/'
	0,0,248,3,252,7,6,12,6,12,252,7,248,3,0,0,			//	'0'
	0,0,4,8,4,8,254,15,254,15,0,8,0,8,0,0,				//	'1'
	0,0,12,14,142,15,194,13,126,12,62,12,12,12,0,0,		//	'2'
	0,0,6,12,102,12,102,12,102,12,254,15,254,15,0,0, 	//	'3'
	224,0,240,0,216,0,204,0,198,0,254,15,254,15,0,0, 	//	'4'
	0,0,126,12,126,12,70,12,70,12,198,15,198,15,0,0, 	//	'5'
	0,0,254,15,254,15,70,12,70,12,198,15,198,15,0,0, 	//	'6'
	0,0,6,12,6,15,198,3,246,0,62,0,14,0,0,0,			//	'7'
	0,0,254,15,254,15,70,12,70,12,254,15,254,15,0,0,	//	'8'
	0,0,126,12,126,12,102,12,102,12,254,15,254,15,0,0,	//	'9'	
	0,0,0,0,0,0,152,1,152,1,0,0,0,0,0,0,				//	'0'
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                  // ';' 59
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                // '<' 60
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                      // '=' 61
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                  // '>' 62
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,               // '?' 63
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       // '@' 64
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,         // 'A' 65
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        // 'B' 66
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,         // 'C' 67
	254,15,254,15,6,12,6,12,14,14,252,7,248,3,0,0,	 // 'D' 68
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,           // 'E' 69
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,            // 'F' 70
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        // 'G' 71
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       // 'H' 72
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                 // 'I' 73
	0,0,6,7,6,15,6,12,6,12,254,15,254,15,0,0,  			// 'J' 74
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        // 'K' 75
	0,0,254,15,254,15,0,12,0,12,0,12,0,12,0,0,               // 'L' 76
	254,15,254,15,28,0,112,0,112,0,28,0,254,15,254,15,         // 'M' 77
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        // 'N' 78
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,      // 'O' 79
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          // 'P' 80
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        // 'Q' 81
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        // 'R' 82
	0,0,60,8,126,12,110,12,198,14,198,15,134,7,0,0,             // 'S' 83
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,               // 'T' 84
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       // 'U' 85
	6,0,126,0,248,3,128,15,128,15,248,3,766,0,6,0,	// 'V' 86
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,		 // 'W' 87
	6,12,14,15,152,3,240,0,240,0,152,3,14,15,6,12           // 'X' 88
	 
  };

 //Raw data grids:
 //
 //  47        48        49        50        51        52
 //  ........  ........  ........  ........  ........  ........
 //  ....X...  ....X...  ........  ........  ........  ........
 //  ...X....  ..XX.X..  ....X...  ..XXXX..  ..XXXX..  .....X..
 //  ...X....  ..X..XX.  .XXXX...  .X..XXX.  .X..XXX.  ....XX..
 //  ...X....  .XX..XX.  ...XX...  X....XX.  ....XX..  ...XXX..
 //  ..X.....  .XX..XX.  ...XX...  .....XX.  .....X..  ..X..X..
 //  ..X.....  XXX..XXX  ...XX...  .....X..  ..XXXX..  ..X..XX.
 //  ..X.....  .XX..XXX  ...XX...  ....X...  ....XXX.  .X..XX..
 //  .X......  .XX..XX.  ...XX...  ...X....  .....XX.  XXXXXXXX
 //  .X......  .XX..XX.  ...XX...  ..X....X  ......X.  .XXXXXX.
 //  .X......  ..X..XX.  ...XX...  ..XXXXX.  .X....X.  .....X..
 //  X.......  ..XXXX..  .XXXXXX.  XXXXXXX.  XXXXXX..  .....X..
 //  ........  ........  ........  ........  ........  ........
 //  ........  ........  ........  ........  ........  ........
 //
 //  53        54        55        56        57        58
 //  ........  ........  ........  ........  ........  ........
 //  ........  .......X  ........  ....X...  ...X....  ........
 //  ..XXXXXX  ....XXX.  .XXXXXXX  ..XX.X..  ..X.XX..  ........
 //  ..XXXXX.  ...X....  .XXXXXX.  .XX...XX  .XX..XX.  ........
 //  .X......  ..XX....  X.....X.  .XX...X.  .XX..XX.  ........
 //  .XXXX...  .XX.....  .....X..  .XXX..X.  XXX..XXX  ..XX....
 //  XXXXXXX.  .XXXXXX.  .....X..  ..XXXX..  .XX..XXX  .XXX....
 //  .....XX.  XXX..XX.  .....X..  ..X.XXX.  ..XXXXX.  ........
 //  ......XX  .XX..XXX  ....X...  .XX..XX.  .....XX.  ........
 //  ......X.  .XX...XX  ....X...  XXX...XX  .....X..  ........
 //  XX....X.  .XX...X.  ....X...  .X....X.  ....X...  ..XX....
 //  .XXXXX..  ..XXXX..  ...X....  ..XXXX..  .XXX....  .XXX....
 //  ........  ........  ........  ........  X.......  ........
 //  ........  ........  ........  ........  ........  ........


#endif /* TIMESNEWROMAS_8X12_H_ */