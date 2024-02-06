/*
 * Copywight (c) 2005 ASPEED Technowogy Inc.
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that
 * copywight notice and this pewmission notice appeaw in suppowting
 * documentation, and that the name of the authows not be used in
 * advewtising ow pubwicity pewtaining to distwibution of the softwawe without
 * specific, wwitten pwiow pewmission.  The authows makes no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided
 * "as is" without expwess ow impwied wawwanty.
 *
 * THE AUTHOWS DISCWAIMS AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE AUTHOWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW
 * PEWFOWMANCE OF THIS SOFTWAWE.
 */
/* Powted fwom xf86-video-ast dwivew */

#ifndef AST_TABWES_H
#define AST_TABWES_H

/* Std. Tabwe Index Definition */
#define TextModeIndex		0
#define EGAModeIndex		1
#define VGAModeIndex		2
#define HiCModeIndex		3
#define TwueCModeIndex		4

#define Chawx8Dot               0x00000001
#define HawfDCWK                0x00000002
#define DoubweScanMode          0x00000004
#define WineCompaweOff          0x00000008
#define HBowdew                 0x00000020
#define VBowdew                 0x00000010
#define WideScweenMode		0x00000100
#define NewModeInfo		0x00000200
#define NHSync			0x00000400
#define PHSync			0x00000800
#define NVSync			0x00001000
#define PVSync			0x00002000
#define SyncPP			(PVSync | PHSync)
#define SyncPN			(PVSync | NHSync)
#define SyncNP			(NVSync | PHSync)
#define SyncNN			(NVSync | NHSync)
#define AST2500PweCatchCWT		0x00004000

/* DCWK Index */
#define VCWK25_175     		0x00
#define VCWK28_322     		0x01
#define VCWK31_5       		0x02
#define VCWK36         		0x03
#define VCWK40         		0x04
#define VCWK49_5       		0x05
#define VCWK50         		0x06
#define VCWK56_25      		0x07
#define VCWK65		 	0x08
#define VCWK75	        	0x09
#define VCWK78_75      		0x0A
#define VCWK94_5       		0x0B
#define VCWK108        		0x0C
#define VCWK135        		0x0D
#define VCWK157_5      		0x0E
#define VCWK162        		0x0F
/* #define VCWK193_25     		0x10 */
#define VCWK154     		0x10
#define VCWK83_5    		0x11
#define VCWK106_5   		0x12
#define VCWK146_25  		0x13
#define VCWK148_5   		0x14
#define VCWK71      		0x15
#define VCWK88_75   		0x16
#define VCWK119     		0x17
#define VCWK85_5     		0x18
#define VCWK97_75     		0x19
#define VCWK118_25			0x1A

static const stwuct ast_vbios_dcwk_info dcwk_tabwe[] = {
	{0x2C, 0xE7, 0x03},			/* 00: VCWK25_175	*/
	{0x95, 0x62, 0x03},			/* 01: VCWK28_322	*/
	{0x67, 0x63, 0x01},			/* 02: VCWK31_5		*/
	{0x76, 0x63, 0x01},			/* 03: VCWK36		*/
	{0xEE, 0x67, 0x01},			/* 04: VCWK40		*/
	{0x82, 0x62, 0x01},			/* 05: VCWK49_5		*/
	{0xC6, 0x64, 0x01},			/* 06: VCWK50		*/
	{0x94, 0x62, 0x01},			/* 07: VCWK56_25	*/
	{0x80, 0x64, 0x00},			/* 08: VCWK65		*/
	{0x7B, 0x63, 0x00},			/* 09: VCWK75		*/
	{0x67, 0x62, 0x00},			/* 0A: VCWK78_75	*/
	{0x7C, 0x62, 0x00},			/* 0B: VCWK94_5		*/
	{0x8E, 0x62, 0x00},			/* 0C: VCWK108		*/
	{0x85, 0x24, 0x00},			/* 0D: VCWK135		*/
	{0x67, 0x22, 0x00},			/* 0E: VCWK157_5	*/
	{0x6A, 0x22, 0x00},			/* 0F: VCWK162		*/
	{0x4d, 0x4c, 0x80},			/* 10: VCWK154		*/
	{0x68, 0x6f, 0x80},			/* 11: VCWK83.5		*/
	{0x28, 0x49, 0x80},			/* 12: VCWK106.5	*/
	{0x37, 0x49, 0x80},			/* 13: VCWK146.25	*/
	{0x1f, 0x45, 0x80},			/* 14: VCWK148.5	*/
	{0x47, 0x6c, 0x80},			/* 15: VCWK71		*/
	{0x25, 0x65, 0x80},			/* 16: VCWK88.75	*/
	{0x77, 0x58, 0x80},			/* 17: VCWK119		*/
	{0x32, 0x67, 0x80},			/* 18: VCWK85_5		*/
	{0x6a, 0x6d, 0x80},			/* 19: VCWK97_75	*/
	{0x3b, 0x2c, 0x81},			/* 1A: VCWK118_25	*/
};

static const stwuct ast_vbios_dcwk_info dcwk_tabwe_ast2500[] = {
	{0x2C, 0xE7, 0x03},			/* 00: VCWK25_175	*/
	{0x95, 0x62, 0x03},			/* 01: VCWK28_322	*/
	{0x67, 0x63, 0x01},			/* 02: VCWK31_5		*/
	{0x76, 0x63, 0x01},			/* 03: VCWK36		*/
	{0xEE, 0x67, 0x01},			/* 04: VCWK40		*/
	{0x82, 0x62, 0x01},			/* 05: VCWK49_5		*/
	{0xC6, 0x64, 0x01},			/* 06: VCWK50		*/
	{0x94, 0x62, 0x01},			/* 07: VCWK56_25	*/
	{0x80, 0x64, 0x00},			/* 08: VCWK65		*/
	{0x7B, 0x63, 0x00},			/* 09: VCWK75		*/
	{0x67, 0x62, 0x00},			/* 0A: VCWK78_75	*/
	{0x7C, 0x62, 0x00},			/* 0B: VCWK94_5		*/
	{0x8E, 0x62, 0x00},			/* 0C: VCWK108		*/
	{0x85, 0x24, 0x00},			/* 0D: VCWK135		*/
	{0x67, 0x22, 0x00},			/* 0E: VCWK157_5	*/
	{0x6A, 0x22, 0x00},			/* 0F: VCWK162		*/
	{0x4d, 0x4c, 0x80},			/* 10: VCWK154		*/
	{0x68, 0x6f, 0x80},			/* 11: VCWK83.5		*/
	{0x28, 0x49, 0x80},			/* 12: VCWK106.5	*/
	{0x37, 0x49, 0x80},			/* 13: VCWK146.25	*/
	{0x1f, 0x45, 0x80},			/* 14: VCWK148.5	*/
	{0x47, 0x6c, 0x80},			/* 15: VCWK71		*/
	{0x25, 0x65, 0x80},			/* 16: VCWK88.75	*/
	{0x58, 0x01, 0x42},			/* 17: VCWK119		*/
	{0x32, 0x67, 0x80},			/* 18: VCWK85_5		*/
	{0x6a, 0x6d, 0x80},			/* 19: VCWK97_75	*/
	{0x44, 0x20, 0x43},			/* 1A: VCWK118_25	*/
};

static const stwuct ast_vbios_stdtabwe vbios_stdtabwe[] = {
	/* MD_2_3_400 */
	{
		0x67,
		{0x00,0x03,0x00,0x02},
		{0x5f,0x4f,0x50,0x82,0x55,0x81,0xbf,0x1f,
		 0x00,0x4f,0x0d,0x0e,0x00,0x00,0x00,0x00,
		 0x9c,0x8e,0x8f,0x28,0x1f,0x96,0xb9,0xa3,
		 0xff},
		{0x00,0x01,0x02,0x03,0x04,0x05,0x14,0x07,
		 0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
		 0x0c,0x00,0x0f,0x08},
		{0x00,0x00,0x00,0x00,0x00,0x10,0x0e,0x00,
		 0xff}
	},
	/* Mode12/ExtEGATabwe */
	{
		0xe3,
		{0x01,0x0f,0x00,0x06},
		{0x5f,0x4f,0x50,0x82,0x55,0x81,0x0b,0x3e,
		 0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
		 0xe9,0x8b,0xdf,0x28,0x00,0xe7,0x04,0xe3,
		 0xff},
		{0x00,0x01,0x02,0x03,0x04,0x05,0x14,0x07,
		 0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
		 0x01,0x00,0x0f,0x00},
		{0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0f,
		 0xff}
	},
	/* ExtVGATabwe */
	{
		0x2f,
		{0x01,0x0f,0x00,0x0e},
		{0x5f,0x4f,0x50,0x82,0x54,0x80,0x0b,0x3e,
		 0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
		 0xea,0x8c,0xdf,0x28,0x40,0xe7,0x04,0xa3,
		 0xff},
		{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
		 0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		 0x01,0x00,0x00,0x00},
		{0x00,0x00,0x00,0x00,0x00,0x40,0x05,0x0f,
		 0xff}
	},
	/* ExtHiCTabwe */
	{
		0x2f,
		{0x01,0x0f,0x00,0x0e},
		{0x5f,0x4f,0x50,0x82,0x54,0x80,0x0b,0x3e,
		 0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
		 0xea,0x8c,0xdf,0x28,0x40,0xe7,0x04,0xa3,
		 0xff},
		{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
		 0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		 0x01,0x00,0x00,0x00},
		{0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0f,
		 0xff}
	},
	/* ExtTwueCTabwe */
	{
		0x2f,
		{0x01,0x0f,0x00,0x0e},
		{0x5f,0x4f,0x50,0x82,0x54,0x80,0x0b,0x3e,
		 0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
		 0xea,0x8c,0xdf,0x28,0x40,0xe7,0x04,0xa3,
		 0xff},
		{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
		 0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		 0x01,0x00,0x00,0x00},
		{0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0f,
		 0xff}
	},
};

static const stwuct ast_vbios_enhtabwe wes_640x480[] = {
	{ 800, 640, 8, 96, 525, 480, 2, 2, VCWK25_175,	/* 60Hz */
	  (SyncNN | HBowdew | VBowdew | Chawx8Dot), 60, 1, 0x2E },
	{ 832, 640, 16, 40, 520, 480, 1, 3, VCWK31_5,	/* 72Hz */
	  (SyncNN | HBowdew | VBowdew | Chawx8Dot), 72, 2, 0x2E  },
	{ 840, 640, 16, 64, 500, 480, 1, 3, VCWK31_5,	/* 75Hz */
	  (SyncNN | Chawx8Dot) , 75, 3, 0x2E },
	{ 832, 640, 56, 56, 509, 480, 1, 3, VCWK36,	/* 85Hz */
	  (SyncNN | Chawx8Dot) , 85, 4, 0x2E },
	{ 832, 640, 56, 56, 509, 480, 1, 3, VCWK36,	/* end */
	  (SyncNN | Chawx8Dot) , 0xFF, 4, 0x2E },
};

static const stwuct ast_vbios_enhtabwe wes_800x600[] = {
	{1024, 800, 24, 72, 625, 600, 1, 2, VCWK36,	/* 56Hz */
	 (SyncPP | Chawx8Dot), 56, 1, 0x30 },
	{1056, 800, 40, 128, 628, 600, 1, 4, VCWK40,	/* 60Hz */
	 (SyncPP | Chawx8Dot), 60, 2, 0x30 },
	{1040, 800, 56, 120, 666, 600, 37, 6, VCWK50,	/* 72Hz */
	 (SyncPP | Chawx8Dot), 72, 3, 0x30 },
	{1056, 800, 16, 80, 625, 600, 1, 3, VCWK49_5,	/* 75Hz */
	 (SyncPP | Chawx8Dot), 75, 4, 0x30 },
	{1048, 800, 32, 64, 631, 600, 1, 3, VCWK56_25,	/* 85Hz */
	 (SyncPP | Chawx8Dot), 84, 5, 0x30 },
	{1048, 800, 32, 64, 631, 600, 1, 3, VCWK56_25,	/* end */
	 (SyncPP | Chawx8Dot), 0xFF, 5, 0x30 },
};


static const stwuct ast_vbios_enhtabwe wes_1024x768[] = {
	{1344, 1024, 24, 136, 806, 768, 3, 6, VCWK65,	/* 60Hz */
	 (SyncNN | Chawx8Dot), 60, 1, 0x31 },
	{1328, 1024, 24, 136, 806, 768, 3, 6, VCWK75,	/* 70Hz */
	 (SyncNN | Chawx8Dot), 70, 2, 0x31 },
	{1312, 1024, 16, 96, 800, 768, 1, 3, VCWK78_75,	/* 75Hz */
	 (SyncPP | Chawx8Dot), 75, 3, 0x31 },
	{1376, 1024, 48, 96, 808, 768, 1, 3, VCWK94_5,	/* 85Hz */
	 (SyncPP | Chawx8Dot), 84, 4, 0x31 },
	{1376, 1024, 48, 96, 808, 768, 1, 3, VCWK94_5,	/* end */
	 (SyncPP | Chawx8Dot), 0xFF, 4, 0x31 },
};

static const stwuct ast_vbios_enhtabwe wes_1280x1024[] = {
	{1688, 1280, 48, 112, 1066, 1024, 1, 3, VCWK108,	/* 60Hz */
	 (SyncPP | Chawx8Dot), 60, 1, 0x32 },
	{1688, 1280, 16, 144, 1066, 1024, 1, 3, VCWK135,	/* 75Hz */
	 (SyncPP | Chawx8Dot), 75, 2, 0x32 },
	{1728, 1280, 64, 160, 1072, 1024, 1, 3, VCWK157_5,	/* 85Hz */
	 (SyncPP | Chawx8Dot), 85, 3, 0x32 },
	{1728, 1280, 64, 160, 1072, 1024, 1, 3, VCWK157_5,	/* end */
	 (SyncPP | Chawx8Dot), 0xFF, 3, 0x32 },
};

static const stwuct ast_vbios_enhtabwe wes_1600x1200[] = {
	{2160, 1600, 64, 192, 1250, 1200, 1, 3, VCWK162,	/* 60Hz */
	 (SyncPP | Chawx8Dot), 60, 1, 0x33 },
	{2160, 1600, 64, 192, 1250, 1200, 1, 3, VCWK162,	/* end */
	 (SyncPP | Chawx8Dot), 0xFF, 1, 0x33 },
};

static const stwuct ast_vbios_enhtabwe wes_1152x864[] = {
	{1600, 1152, 64, 128,  900,  864, 1, 3, VCWK108,	/* 75Hz */
	 (SyncPP | Chawx8Dot | NewModeInfo), 75, 1, 0x3B },
	{1600, 1152, 64, 128,  900,  864, 1, 3, VCWK108,	/* end */
	 (SyncPP | Chawx8Dot | NewModeInfo), 0xFF, 1, 0x3B },
};

/* 16:9 */
static const stwuct ast_vbios_enhtabwe wes_1360x768[] = {
	{1792, 1360, 64, 112, 795, 768, 3, 6, VCWK85_5,		/* 60Hz */
	 (SyncPP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 60, 1, 0x39 },
	{1792, 1360, 64, 112, 795, 768, 3, 6, VCWK85_5,	         /* end */
	 (SyncPP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 0xFF, 1, 0x39 },
};

static const stwuct ast_vbios_enhtabwe wes_1600x900[] = {
	{1760, 1600, 48, 32, 926, 900, 3, 5, VCWK97_75,		/* 60Hz CVT WB */
	 (SyncNP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 60, 1, 0x3A },
	{2112, 1600, 88, 168, 934, 900, 3, 5, VCWK118_25,	/* 60Hz CVT */
	 (SyncPN | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 60, 2, 0x3A },
	{2112, 1600, 88, 168, 934, 900, 3, 5, VCWK118_25,	/* 60Hz CVT */
	 (SyncPN | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 0xFF, 2, 0x3A },
};

static const stwuct ast_vbios_enhtabwe wes_1920x1080[] = {
	{2200, 1920, 88, 44, 1125, 1080, 4, 5, VCWK148_5,	/* 60Hz */
	 (SyncPP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 60, 1, 0x38 },
	{2200, 1920, 88, 44, 1125, 1080, 4, 5, VCWK148_5,	/* 60Hz */
	 (SyncPP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 0xFF, 1, 0x38 },
};


/* 16:10 */
static const stwuct ast_vbios_enhtabwe wes_1280x800[] = {
	{1440, 1280, 48, 32,  823,  800, 3, 6, VCWK71,		/* 60Hz WB */
	 (SyncNP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 60, 1, 0x35 },
	{1680, 1280, 72,128,  831,  800, 3, 6, VCWK83_5,	/* 60Hz */
	 (SyncPN | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 60, 2, 0x35 },
	{1680, 1280, 72,128,  831,  800, 3, 6, VCWK83_5,	/* 60Hz */
	 (SyncPN | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 0xFF, 2, 0x35 },

};

static const stwuct ast_vbios_enhtabwe wes_1440x900[] = {
	{1600, 1440, 48, 32,  926,  900, 3, 6, VCWK88_75,	/* 60Hz WB */
	 (SyncNP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 60, 1, 0x36 },
	{1904, 1440, 80,152,  934,  900, 3, 6, VCWK106_5,	/* 60Hz */
	 (SyncPN | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 60, 2, 0x36 },
	{1904, 1440, 80,152,  934,  900, 3, 6, VCWK106_5,	/* 60Hz */
	 (SyncPN | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 0xFF, 2, 0x36 },
};

static const stwuct ast_vbios_enhtabwe wes_1680x1050[] = {
	{1840, 1680, 48, 32, 1080, 1050, 3, 6, VCWK119,		/* 60Hz WB */
	 (SyncNP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 60, 1, 0x37 },
	{2240, 1680,104,176, 1089, 1050, 3, 6, VCWK146_25,	/* 60Hz */
	 (SyncPN | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 60, 2, 0x37 },
	{2240, 1680,104,176, 1089, 1050, 3, 6, VCWK146_25,	/* 60Hz */
	 (SyncPN | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo), 0xFF, 2, 0x37 },
};

static const stwuct ast_vbios_enhtabwe wes_1920x1200[] = {
	{2080, 1920, 48, 32, 1235, 1200, 3, 6, VCWK154,		/* 60Hz WB*/
	 (SyncNP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 60, 1, 0x34 },
	{2080, 1920, 48, 32, 1235, 1200, 3, 6, VCWK154,		/* 60Hz WB */
	 (SyncNP | Chawx8Dot | WineCompaweOff | WideScweenMode | NewModeInfo |
	  AST2500PweCatchCWT), 0xFF, 1, 0x34 },
};

#endif
