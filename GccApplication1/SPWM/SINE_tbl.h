//-----------------------------------------------------------------------------
// Copyright:      www.Elasa.ir
// Author:         OZHAN KD modified by Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        1.0.0
// Description:    Sine Table ...
//-----------------------------------------------------------------------------

#ifndef _SINE_TBL_H_
	#define _SINE_TBL_H_
	PROGMEM unsigned char sine0[256] = {
			0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f, 0x92, 0x95, 0x98, 0x9c, 0x9f, 0xa2, 0xa5, 0xa8,
			0xab, 0xae,	0xb0, 0xb3, 0xb6, 0xb9, 0xbc, 0xbf, 0xc1, 0xc4, 0xc7, 0xc9, 0xcc, 0xce,
			0xd1, 0xd3, 0xd5, 0xd8,	0xda, 0xdc, 0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec,
			0xed, 0xef, 0xf0, 0xf2, 0xf3, 0xf5,	0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfc,
			0xfd, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,	0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xfe, 0xfe, 0xfd, 0xfc, 0xfc, 0xfb, 0xfa, 0xf9, 0xf8, 0xf7,	0xf6, 0xf5, 0xf3, 0xf2,
			
			0xf0, 0xef, 0xed, 0xec, 0xea, 0xe8, 0xe6, 0xe4, 0xe2, 0xe0, 0xde, 0xdc, 0xda, 0xd8,
			0xd5, 0xd3, 0xd1, 0xce, 0xcc, 0xc9, 0xc7, 0xc4, 0xc1, 0xbf, 0xbc, 0xb9, 0xb6, 0xb3,
			0xb0, 0xae, 0xab, 0xa8, 0xa5, 0xa2, 0x9f, 0x9c, 0x98, 0x95, 0x92, 0x8f, 0x8c, 0x89,
			0x86, 0x83,	0x80, 0x7c, 0x79, 0x76, 0x73, 0x70, 0x6d, 0x6a, 0x67, 0x63, 0x60, 0x5d,
			0x5a, 0x57, 0x54, 0x51,	0x4f, 0x4c, 0x49, 0x46, 0x43, 0x40, 0x3e, 0x3b, 0x38, 0x36,
			0x33, 0x31, 0x2e, 0x2c, 0x2a, 0x27,	0x25, 0x23, 0x21, 0x1f, 0x1d, 0x1b, 0x19, 0x17,
			0x15, 0x13, 0x12, 0x10, 0x0f, 0x0d,
			
			0x0c, 0x0a,	0x09, 0x08, 0x07, 0x06, 0x05, 0x04,	0x03, 0x03, 0x02, 0x01, 0x01, 0x00,
			0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x01, 0x01, 0x02, 0x03,
			0x03, 0x04, 0x05, 0x06, 0x07, 0x08,	0x09, 0x0a,	0x0c, 0x0d, 0x0f, 0x10, 0x12, 0x13,
			0x15, 0x17, 0x19, 0x1b, 0x1d, 0x1f, 0x21, 0x23,	0x25, 0x27, 0x2a, 0x2c, 0x2e, 0x31,
			0x33, 0x36, 0x38, 0x3b, 0x3e, 0x40, 0x43, 0x46,	0x49, 0x4c,	0x4f, 0x51, 0x54, 0x57,
			0x5a, 0x5d, 0x60, 0x63, 0x67, 0x6a, 0x6d, 0x70,	0x73, 0x76, 0x79, 0x7c
			}; 
			
	PROGMEM unsigned char sine[256] = {
			128,131,134,137,140,143,146,149,152,156,159,162,165,168,171,174,
176,179,182,185,188,191,193,196,199,201,204,206,209,211,213,216,
218,220,222,224,226,228,230,232,234,236,237,239,240,242,243,245,
246,247,248,249,250,251,252,252,253,254,254,255,255,255,255,255,
255,255,255,255,255,255,254,254,253,252,252,251,250,249,248,247,
246,245,243,242,240,239,237,236,234,232,230,228,226,224,222,220,
218,216,213,211,209,206,204,201,199,196,193,191,188,185,182,179,
176,174,171,168,165,162,159,156,152,149,146,143,140,137,134,131,
128,124,121,118,115,112,109,106,103,99, 96, 93, 90, 87, 84, 81,
79, 76, 73, 70, 67, 64, 62, 59, 56, 54, 51, 49, 46, 44, 42, 39,
37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10,
9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8,
9, 10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 29, 31, 33, 35,
37, 39, 42, 44, 46, 49, 51, 54, 56, 59, 62, 64, 67, 70, 73, 76,
79, 81, 84, 87, 90, 93, 96, 99, 103,106,109,112,115,118,121,124
			};
			
			PROGMEM unsigned char sine1[256] = {
			0, 5, 9, 14, 19, 23, 28, 33, 37, 42, 47, 51, 56, 60, 65, 70, 74, 79, 83, 87, 92, 96, 100, 105, 109, 113, 117, 122, 126, 130, 134, 138, 142, 146, 149, 153, 157, 161, 164, 168, 171, 175, 178, 181, 185, 188, 191, 194, 197, 200, 203, 206, 208, 211, 214, 216, 219, 221, 223, 226, 228, 230, 232, 234, 236, 237, 239, 241, 242, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247, 246, 244, 243, 242, 240, 238, 237, 235, 233, 231, 229, 227, 225, 223, 220, 218, 215, 213, 210, 208, 205, 202, 199, 196, 193, 190, 187, 184, 180, 177, 174, 170, 167, 163, 159, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112, 108, 103, 99, 95, 90, 86, 81, 77, 73, 68, 63, 59, 54, 50, 45, 41, 36, 31, 27, 22, 17, 13, 8, 3, -2, -6, -11, -16, -20, -25, -30, -34, -39, -44, -48, -53, -57, -62, -67, -71, -76, -80, -84, -89, -93, -98, -102, -106, -110, -115, -119, -123, -127, -131, -135, -139, -143, -147, -151, -154, -158, -162, -165, -169, -172, -176, -179, -183, -186, -189, -192, -195, -198, -201, -204, -207, -209, -212, -215, -217, -220, -222, -224, -226, -228, -231, -232, -234, -236, -238, -240, -241, -243, -244, -245, -247, -248, -249, -250, -251, -252, -252, -253, -253, -254, -254, -255, -255, -255			};


#endif	//_SINE_TBL_H_
