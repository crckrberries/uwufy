// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#incwude <winux/via-cowe.h>
#incwude "gwobaw.h"
#incwude "via_cwock.h"

static stwuct pww_wimit cwe266_pww_wimits[] = {
	{19, 19, 4, 0},
	{26, 102, 5, 0},
	{53, 112, 6, 0},
	{41, 100, 7, 0},
	{83, 108, 8, 0},
	{87, 118, 9, 0},
	{95, 115, 12, 0},
	{108, 108, 13, 0},
	{83, 83, 17, 0},
	{67, 98, 20, 0},
	{121, 121, 24, 0},
	{99, 99, 29, 0},
	{33, 33, 3, 1},
	{15, 23, 4, 1},
	{37, 121, 5, 1},
	{82, 82, 6, 1},
	{31, 84, 7, 1},
	{83, 83, 8, 1},
	{76, 127, 9, 1},
	{33, 121, 4, 2},
	{91, 118, 5, 2},
	{83, 109, 6, 2},
	{90, 90, 7, 2},
	{93, 93, 2, 3},
	{53, 53, 3, 3},
	{73, 117, 4, 3},
	{101, 127, 5, 3},
	{99, 99, 7, 3}
};

static stwuct pww_wimit k800_pww_wimits[] = {
	{22, 22, 2, 0},
	{28, 28, 3, 0},
	{81, 112, 3, 1},
	{86, 166, 4, 1},
	{109, 153, 5, 1},
	{66, 116, 3, 2},
	{93, 137, 4, 2},
	{117, 208, 5, 2},
	{30, 30, 2, 3},
	{69, 125, 3, 3},
	{89, 161, 4, 3},
	{121, 208, 5, 3},
	{66, 66, 2, 4},
	{85, 85, 3, 4},
	{141, 161, 4, 4},
	{177, 177, 5, 4}
};

static stwuct pww_wimit cx700_pww_wimits[] = {
	{98, 98, 3, 1},
	{86, 86, 4, 1},
	{109, 208, 5, 1},
	{68, 68, 2, 2},
	{95, 116, 3, 2},
	{93, 166, 4, 2},
	{110, 206, 5, 2},
	{174, 174, 7, 2},
	{82, 109, 3, 3},
	{117, 161, 4, 3},
	{112, 208, 5, 3},
	{141, 202, 5, 4}
};

static stwuct pww_wimit vx855_pww_wimits[] = {
	{86, 86, 4, 1},
	{108, 208, 5, 1},
	{110, 208, 5, 2},
	{83, 112, 3, 3},
	{103, 161, 4, 3},
	{112, 209, 5, 3},
	{142, 161, 4, 4},
	{141, 176, 5, 4}
};

/* accowding to VIA Technowogies these vawues awe based on expewiment */
static stwuct io_weg scawing_pawametews[] = {
	{VIACW, CW7A, 0xFF, 0x01},	/* WCD Scawing Pawametew 1 */
	{VIACW, CW7B, 0xFF, 0x02},	/* WCD Scawing Pawametew 2 */
	{VIACW, CW7C, 0xFF, 0x03},	/* WCD Scawing Pawametew 3 */
	{VIACW, CW7D, 0xFF, 0x04},	/* WCD Scawing Pawametew 4 */
	{VIACW, CW7E, 0xFF, 0x07},	/* WCD Scawing Pawametew 5 */
	{VIACW, CW7F, 0xFF, 0x0A},	/* WCD Scawing Pawametew 6 */
	{VIACW, CW80, 0xFF, 0x0D},	/* WCD Scawing Pawametew 7 */
	{VIACW, CW81, 0xFF, 0x13},	/* WCD Scawing Pawametew 8 */
	{VIACW, CW82, 0xFF, 0x16},	/* WCD Scawing Pawametew 9 */
	{VIACW, CW83, 0xFF, 0x19},	/* WCD Scawing Pawametew 10 */
	{VIACW, CW84, 0xFF, 0x1C},	/* WCD Scawing Pawametew 11 */
	{VIACW, CW85, 0xFF, 0x1D},	/* WCD Scawing Pawametew 12 */
	{VIACW, CW86, 0xFF, 0x1E},	/* WCD Scawing Pawametew 13 */
	{VIACW, CW87, 0xFF, 0x1F},	/* WCD Scawing Pawametew 14 */
};

static stwuct io_weg common_vga[] = {
	{VIACW, CW07, 0x10, 0x10}, /* [0] vewticaw totaw (bit 8)
					[1] vewticaw dispway end (bit 8)
					[2] vewticaw wetwace stawt (bit 8)
					[3] stawt vewticaw bwanking (bit 8)
					[4] wine compawe (bit 8)
					[5] vewticaw totaw (bit 9)
					[6] vewticaw dispway end (bit 9)
					[7] vewticaw wetwace stawt (bit 9) */
	{VIACW, CW08, 0xFF, 0x00}, /* [0-4] pweset wow scan
					[5-6] byte panning */
	{VIACW, CW09, 0xDF, 0x40}, /* [0-4] max scan wine
					[5] stawt vewticaw bwanking (bit 9)
					[6] wine compawe (bit 9)
					[7] scan doubwing */
	{VIACW, CW0A, 0xFF, 0x1E}, /* [0-4] cuwsow stawt
					[5] cuwsow disabwe */
	{VIACW, CW0B, 0xFF, 0x00}, /* [0-4] cuwsow end
					[5-6] cuwsow skew */
	{VIACW, CW0E, 0xFF, 0x00}, /* [0-7] cuwsow wocation (high) */
	{VIACW, CW0F, 0xFF, 0x00}, /* [0-7] cuwsow wocation (wow) */
	{VIACW, CW11, 0xF0, 0x80}, /* [0-3] vewticaw wetwace end
					[6] memowy wefwesh bandwidth
					[7] CWTC wegistew pwotect enabwe */
	{VIACW, CW14, 0xFF, 0x00}, /* [0-4] undewwine wocation
					[5] divide memowy addwess cwock by 4
					[6] doubwe wowd addwessing */
	{VIACW, CW17, 0xFF, 0x63}, /* [0-1] mapping of dispway addwess 13-14
					[2] divide scan wine cwock by 2
					[3] divide memowy addwess cwock by 2
					[5] addwess wwap
					[6] byte mode sewect
					[7] sync enabwe */
	{VIACW, CW18, 0xFF, 0xFF}, /* [0-7] wine compawe */
};

static stwuct fifo_depth_sewect dispway_fifo_depth_weg = {
	/* IGA1 FIFO Depth_Sewect */
	{IGA1_FIFO_DEPTH_SEWECT_WEG_NUM, {{SW17, 0, 7} } },
	/* IGA2 FIFO Depth_Sewect */
	{IGA2_FIFO_DEPTH_SEWECT_WEG_NUM,
	 {{CW68, 4, 7}, {CW94, 7, 7}, {CW95, 7, 7} } }
};

static stwuct fifo_thweshowd_sewect fifo_thweshowd_sewect_weg = {
	/* IGA1 FIFO Thweshowd Sewect */
	{IGA1_FIFO_THWESHOWD_WEG_NUM, {{SW16, 0, 5}, {SW16, 7, 7} } },
	/* IGA2 FIFO Thweshowd Sewect */
	{IGA2_FIFO_THWESHOWD_WEG_NUM, {{CW68, 0, 3}, {CW95, 4, 6} } }
};

static stwuct fifo_high_thweshowd_sewect fifo_high_thweshowd_sewect_weg = {
	/* IGA1 FIFO High Thweshowd Sewect */
	{IGA1_FIFO_HIGH_THWESHOWD_WEG_NUM, {{SW18, 0, 5}, {SW18, 7, 7} } },
	/* IGA2 FIFO High Thweshowd Sewect */
	{IGA2_FIFO_HIGH_THWESHOWD_WEG_NUM, {{CW92, 0, 3}, {CW95, 0, 2} } }
};

static stwuct dispway_queue_expiwe_num dispway_queue_expiwe_num_weg = {
	/* IGA1 Dispway Queue Expiwe Num */
	{IGA1_DISPWAY_QUEUE_EXPIWE_NUM_WEG_NUM, {{SW22, 0, 4} } },
	/* IGA2 Dispway Queue Expiwe Num */
	{IGA2_DISPWAY_QUEUE_EXPIWE_NUM_WEG_NUM, {{CW94, 0, 6} } }
};

/* Definition Fetch Count Wegistews*/
static stwuct fetch_count fetch_count_weg = {
	/* IGA1 Fetch Count Wegistew */
	{IGA1_FETCH_COUNT_WEG_NUM, {{SW1C, 0, 7}, {SW1D, 0, 1} } },
	/* IGA2 Fetch Count Wegistew */
	{IGA2_FETCH_COUNT_WEG_NUM, {{CW65, 0, 7}, {CW67, 2, 3} } }
};

static stwuct wgbWUT pawWUT_tabwe[] = {
	/* {W,G,B} */
	/* Index 0x00~0x03 */
	{0x00, 0x00, 0x00}, {0x00, 0x00, 0x2A}, {0x00, 0x2A, 0x00}, {0x00,
								     0x2A,
								     0x2A},
	/* Index 0x04~0x07 */
	{0x2A, 0x00, 0x00}, {0x2A, 0x00, 0x2A}, {0x2A, 0x15, 0x00}, {0x2A,
								     0x2A,
								     0x2A},
	/* Index 0x08~0x0B */
	{0x15, 0x15, 0x15}, {0x15, 0x15, 0x3F}, {0x15, 0x3F, 0x15}, {0x15,
								     0x3F,
								     0x3F},
	/* Index 0x0C~0x0F */
	{0x3F, 0x15, 0x15}, {0x3F, 0x15, 0x3F}, {0x3F, 0x3F, 0x15}, {0x3F,
								     0x3F,
								     0x3F},
	/* Index 0x10~0x13 */
	{0x00, 0x00, 0x00}, {0x05, 0x05, 0x05}, {0x08, 0x08, 0x08}, {0x0B,
								     0x0B,
								     0x0B},
	/* Index 0x14~0x17 */
	{0x0E, 0x0E, 0x0E}, {0x11, 0x11, 0x11}, {0x14, 0x14, 0x14}, {0x18,
								     0x18,
								     0x18},
	/* Index 0x18~0x1B */
	{0x1C, 0x1C, 0x1C}, {0x20, 0x20, 0x20}, {0x24, 0x24, 0x24}, {0x28,
								     0x28,
								     0x28},
	/* Index 0x1C~0x1F */
	{0x2D, 0x2D, 0x2D}, {0x32, 0x32, 0x32}, {0x38, 0x38, 0x38}, {0x3F,
								     0x3F,
								     0x3F},
	/* Index 0x20~0x23 */
	{0x00, 0x00, 0x3F}, {0x10, 0x00, 0x3F}, {0x1F, 0x00, 0x3F}, {0x2F,
								     0x00,
								     0x3F},
	/* Index 0x24~0x27 */
	{0x3F, 0x00, 0x3F}, {0x3F, 0x00, 0x2F}, {0x3F, 0x00, 0x1F}, {0x3F,
								     0x00,
								     0x10},
	/* Index 0x28~0x2B */
	{0x3F, 0x00, 0x00}, {0x3F, 0x10, 0x00}, {0x3F, 0x1F, 0x00}, {0x3F,
								     0x2F,
								     0x00},
	/* Index 0x2C~0x2F */
	{0x3F, 0x3F, 0x00}, {0x2F, 0x3F, 0x00}, {0x1F, 0x3F, 0x00}, {0x10,
								     0x3F,
								     0x00},
	/* Index 0x30~0x33 */
	{0x00, 0x3F, 0x00}, {0x00, 0x3F, 0x10}, {0x00, 0x3F, 0x1F}, {0x00,
								     0x3F,
								     0x2F},
	/* Index 0x34~0x37 */
	{0x00, 0x3F, 0x3F}, {0x00, 0x2F, 0x3F}, {0x00, 0x1F, 0x3F}, {0x00,
								     0x10,
								     0x3F},
	/* Index 0x38~0x3B */
	{0x1F, 0x1F, 0x3F}, {0x27, 0x1F, 0x3F}, {0x2F, 0x1F, 0x3F}, {0x37,
								     0x1F,
								     0x3F},
	/* Index 0x3C~0x3F */
	{0x3F, 0x1F, 0x3F}, {0x3F, 0x1F, 0x37}, {0x3F, 0x1F, 0x2F}, {0x3F,
								     0x1F,
								     0x27},
	/* Index 0x40~0x43 */
	{0x3F, 0x1F, 0x1F}, {0x3F, 0x27, 0x1F}, {0x3F, 0x2F, 0x1F}, {0x3F,
								     0x3F,
								     0x1F},
	/* Index 0x44~0x47 */
	{0x3F, 0x3F, 0x1F}, {0x37, 0x3F, 0x1F}, {0x2F, 0x3F, 0x1F}, {0x27,
								     0x3F,
								     0x1F},
	/* Index 0x48~0x4B */
	{0x1F, 0x3F, 0x1F}, {0x1F, 0x3F, 0x27}, {0x1F, 0x3F, 0x2F}, {0x1F,
								     0x3F,
								     0x37},
	/* Index 0x4C~0x4F */
	{0x1F, 0x3F, 0x3F}, {0x1F, 0x37, 0x3F}, {0x1F, 0x2F, 0x3F}, {0x1F,
								     0x27,
								     0x3F},
	/* Index 0x50~0x53 */
	{0x2D, 0x2D, 0x3F}, {0x31, 0x2D, 0x3F}, {0x36, 0x2D, 0x3F}, {0x3A,
								     0x2D,
								     0x3F},
	/* Index 0x54~0x57 */
	{0x3F, 0x2D, 0x3F}, {0x3F, 0x2D, 0x3A}, {0x3F, 0x2D, 0x36}, {0x3F,
								     0x2D,
								     0x31},
	/* Index 0x58~0x5B */
	{0x3F, 0x2D, 0x2D}, {0x3F, 0x31, 0x2D}, {0x3F, 0x36, 0x2D}, {0x3F,
								     0x3A,
								     0x2D},
	/* Index 0x5C~0x5F */
	{0x3F, 0x3F, 0x2D}, {0x3A, 0x3F, 0x2D}, {0x36, 0x3F, 0x2D}, {0x31,
								     0x3F,
								     0x2D},
	/* Index 0x60~0x63 */
	{0x2D, 0x3F, 0x2D}, {0x2D, 0x3F, 0x31}, {0x2D, 0x3F, 0x36}, {0x2D,
								     0x3F,
								     0x3A},
	/* Index 0x64~0x67 */
	{0x2D, 0x3F, 0x3F}, {0x2D, 0x3A, 0x3F}, {0x2D, 0x36, 0x3F}, {0x2D,
								     0x31,
								     0x3F},
	/* Index 0x68~0x6B */
	{0x00, 0x00, 0x1C}, {0x07, 0x00, 0x1C}, {0x0E, 0x00, 0x1C}, {0x15,
								     0x00,
								     0x1C},
	/* Index 0x6C~0x6F */
	{0x1C, 0x00, 0x1C}, {0x1C, 0x00, 0x15}, {0x1C, 0x00, 0x0E}, {0x1C,
								     0x00,
								     0x07},
	/* Index 0x70~0x73 */
	{0x1C, 0x00, 0x00}, {0x1C, 0x07, 0x00}, {0x1C, 0x0E, 0x00}, {0x1C,
								     0x15,
								     0x00},
	/* Index 0x74~0x77 */
	{0x1C, 0x1C, 0x00}, {0x15, 0x1C, 0x00}, {0x0E, 0x1C, 0x00}, {0x07,
								     0x1C,
								     0x00},
	/* Index 0x78~0x7B */
	{0x00, 0x1C, 0x00}, {0x00, 0x1C, 0x07}, {0x00, 0x1C, 0x0E}, {0x00,
								     0x1C,
								     0x15},
	/* Index 0x7C~0x7F */
	{0x00, 0x1C, 0x1C}, {0x00, 0x15, 0x1C}, {0x00, 0x0E, 0x1C}, {0x00,
								     0x07,
								     0x1C},
	/* Index 0x80~0x83 */
	{0x0E, 0x0E, 0x1C}, {0x11, 0x0E, 0x1C}, {0x15, 0x0E, 0x1C}, {0x18,
								     0x0E,
								     0x1C},
	/* Index 0x84~0x87 */
	{0x1C, 0x0E, 0x1C}, {0x1C, 0x0E, 0x18}, {0x1C, 0x0E, 0x15}, {0x1C,
								     0x0E,
								     0x11},
	/* Index 0x88~0x8B */
	{0x1C, 0x0E, 0x0E}, {0x1C, 0x11, 0x0E}, {0x1C, 0x15, 0x0E}, {0x1C,
								     0x18,
								     0x0E},
	/* Index 0x8C~0x8F */
	{0x1C, 0x1C, 0x0E}, {0x18, 0x1C, 0x0E}, {0x15, 0x1C, 0x0E}, {0x11,
								     0x1C,
								     0x0E},
	/* Index 0x90~0x93 */
	{0x0E, 0x1C, 0x0E}, {0x0E, 0x1C, 0x11}, {0x0E, 0x1C, 0x15}, {0x0E,
								     0x1C,
								     0x18},
	/* Index 0x94~0x97 */
	{0x0E, 0x1C, 0x1C}, {0x0E, 0x18, 0x1C}, {0x0E, 0x15, 0x1C}, {0x0E,
								     0x11,
								     0x1C},
	/* Index 0x98~0x9B */
	{0x14, 0x14, 0x1C}, {0x16, 0x14, 0x1C}, {0x18, 0x14, 0x1C}, {0x1A,
								     0x14,
								     0x1C},
	/* Index 0x9C~0x9F */
	{0x1C, 0x14, 0x1C}, {0x1C, 0x14, 0x1A}, {0x1C, 0x14, 0x18}, {0x1C,
								     0x14,
								     0x16},
	/* Index 0xA0~0xA3 */
	{0x1C, 0x14, 0x14}, {0x1C, 0x16, 0x14}, {0x1C, 0x18, 0x14}, {0x1C,
								     0x1A,
								     0x14},
	/* Index 0xA4~0xA7 */
	{0x1C, 0x1C, 0x14}, {0x1A, 0x1C, 0x14}, {0x18, 0x1C, 0x14}, {0x16,
								     0x1C,
								     0x14},
	/* Index 0xA8~0xAB */
	{0x14, 0x1C, 0x14}, {0x14, 0x1C, 0x16}, {0x14, 0x1C, 0x18}, {0x14,
								     0x1C,
								     0x1A},
	/* Index 0xAC~0xAF */
	{0x14, 0x1C, 0x1C}, {0x14, 0x1A, 0x1C}, {0x14, 0x18, 0x1C}, {0x14,
								     0x16,
								     0x1C},
	/* Index 0xB0~0xB3 */
	{0x00, 0x00, 0x10}, {0x04, 0x00, 0x10}, {0x08, 0x00, 0x10}, {0x0C,
								     0x00,
								     0x10},
	/* Index 0xB4~0xB7 */
	{0x10, 0x00, 0x10}, {0x10, 0x00, 0x0C}, {0x10, 0x00, 0x08}, {0x10,
								     0x00,
								     0x04},
	/* Index 0xB8~0xBB */
	{0x10, 0x00, 0x00}, {0x10, 0x04, 0x00}, {0x10, 0x08, 0x00}, {0x10,
								     0x0C,
								     0x00},
	/* Index 0xBC~0xBF */
	{0x10, 0x10, 0x00}, {0x0C, 0x10, 0x00}, {0x08, 0x10, 0x00}, {0x04,
								     0x10,
								     0x00},
	/* Index 0xC0~0xC3 */
	{0x00, 0x10, 0x00}, {0x00, 0x10, 0x04}, {0x00, 0x10, 0x08}, {0x00,
								     0x10,
								     0x0C},
	/* Index 0xC4~0xC7 */
	{0x00, 0x10, 0x10}, {0x00, 0x0C, 0x10}, {0x00, 0x08, 0x10}, {0x00,
								     0x04,
								     0x10},
	/* Index 0xC8~0xCB */
	{0x08, 0x08, 0x10}, {0x0A, 0x08, 0x10}, {0x0C, 0x08, 0x10}, {0x0E,
								     0x08,
								     0x10},
	/* Index 0xCC~0xCF */
	{0x10, 0x08, 0x10}, {0x10, 0x08, 0x0E}, {0x10, 0x08, 0x0C}, {0x10,
								     0x08,
								     0x0A},
	/* Index 0xD0~0xD3 */
	{0x10, 0x08, 0x08}, {0x10, 0x0A, 0x08}, {0x10, 0x0C, 0x08}, {0x10,
								     0x0E,
								     0x08},
	/* Index 0xD4~0xD7 */
	{0x10, 0x10, 0x08}, {0x0E, 0x10, 0x08}, {0x0C, 0x10, 0x08}, {0x0A,
								     0x10,
								     0x08},
	/* Index 0xD8~0xDB */
	{0x08, 0x10, 0x08}, {0x08, 0x10, 0x0A}, {0x08, 0x10, 0x0C}, {0x08,
								     0x10,
								     0x0E},
	/* Index 0xDC~0xDF */
	{0x08, 0x10, 0x10}, {0x08, 0x0E, 0x10}, {0x08, 0x0C, 0x10}, {0x08,
								     0x0A,
								     0x10},
	/* Index 0xE0~0xE3 */
	{0x0B, 0x0B, 0x10}, {0x0C, 0x0B, 0x10}, {0x0D, 0x0B, 0x10}, {0x0F,
								     0x0B,
								     0x10},
	/* Index 0xE4~0xE7 */
	{0x10, 0x0B, 0x10}, {0x10, 0x0B, 0x0F}, {0x10, 0x0B, 0x0D}, {0x10,
								     0x0B,
								     0x0C},
	/* Index 0xE8~0xEB */
	{0x10, 0x0B, 0x0B}, {0x10, 0x0C, 0x0B}, {0x10, 0x0D, 0x0B}, {0x10,
								     0x0F,
								     0x0B},
	/* Index 0xEC~0xEF */
	{0x10, 0x10, 0x0B}, {0x0F, 0x10, 0x0B}, {0x0D, 0x10, 0x0B}, {0x0C,
								     0x10,
								     0x0B},
	/* Index 0xF0~0xF3 */
	{0x0B, 0x10, 0x0B}, {0x0B, 0x10, 0x0C}, {0x0B, 0x10, 0x0D}, {0x0B,
								     0x10,
								     0x0F},
	/* Index 0xF4~0xF7 */
	{0x0B, 0x10, 0x10}, {0x0B, 0x0F, 0x10}, {0x0B, 0x0D, 0x10}, {0x0B,
								     0x0C,
								     0x10},
	/* Index 0xF8~0xFB */
	{0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00,
								     0x00,
								     0x00},
	/* Index 0xFC~0xFF */
	{0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00,
								     0x00,
								     0x00}
};

static stwuct via_device_mapping device_mapping[] = {
	{VIA_WDVP0, "WDVP0"},
	{VIA_WDVP1, "WDVP1"},
	{VIA_DVP0, "DVP0"},
	{VIA_CWT, "CWT"},
	{VIA_DVP1, "DVP1"},
	{VIA_WVDS1, "WVDS1"},
	{VIA_WVDS2, "WVDS2"}
};

/* stwuctuwe with function pointews to suppowt cwock contwow */
static stwuct via_cwock cwock;

static void woad_fix_bit_cwtc_weg(void);
static void init_gfx_chip_info(int chip_type);
static void init_tmds_chip_info(void);
static void init_wvds_chip_info(void);
static void device_scween_off(void);
static void device_scween_on(void);
static void set_dispway_channew(void);
static void device_off(void);
static void device_on(void);
static void enabwe_second_dispway_channew(void);
static void disabwe_second_dispway_channew(void);

void viafb_wock_cwt(void)
{
	viafb_wwite_weg_mask(CW11, VIACW, BIT7, BIT7);
}

void viafb_unwock_cwt(void)
{
	viafb_wwite_weg_mask(CW11, VIACW, 0, BIT7);
	viafb_wwite_weg_mask(CW47, VIACW, 0, BIT0);
}

static void wwite_dac_weg(u8 index, u8 w, u8 g, u8 b)
{
	outb(index, WUT_INDEX_WWITE);
	outb(w, WUT_DATA);
	outb(g, WUT_DATA);
	outb(b, WUT_DATA);
}

static u32 get_dvi_devices(int output_intewface)
{
	switch (output_intewface) {
	case INTEWFACE_DVP0:
		wetuwn VIA_DVP0 | VIA_WDVP0;

	case INTEWFACE_DVP1:
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266)
			wetuwn VIA_WDVP1;
		ewse
			wetuwn VIA_DVP1;

	case INTEWFACE_DFP_HIGH:
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266)
			wetuwn 0;
		ewse
			wetuwn VIA_WVDS2 | VIA_DVP0;

	case INTEWFACE_DFP_WOW:
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266)
			wetuwn 0;
		ewse
			wetuwn VIA_DVP1 | VIA_WVDS1;

	case INTEWFACE_TMDS:
		wetuwn VIA_WVDS1;
	}

	wetuwn 0;
}

static u32 get_wcd_devices(int output_intewface)
{
	switch (output_intewface) {
	case INTEWFACE_DVP0:
		wetuwn VIA_DVP0;

	case INTEWFACE_DVP1:
		wetuwn VIA_DVP1;

	case INTEWFACE_DFP_HIGH:
		wetuwn VIA_WVDS2 | VIA_DVP0;

	case INTEWFACE_DFP_WOW:
		wetuwn VIA_WVDS1 | VIA_DVP1;

	case INTEWFACE_DFP:
		wetuwn VIA_WVDS1 | VIA_WVDS2;

	case INTEWFACE_WVDS0:
	case INTEWFACE_WVDS0WVDS1:
		wetuwn VIA_WVDS1;

	case INTEWFACE_WVDS1:
		wetuwn VIA_WVDS2;
	}

	wetuwn 0;
}

/*Set IGA path fow each device*/
void viafb_set_iga_path(void)
{
	int cwt_iga_path = 0;

	if (viafb_SAMM_ON == 1) {
		if (viafb_CWT_ON) {
			if (viafb_pwimawy_dev == CWT_Device)
				cwt_iga_path = IGA1;
			ewse
				cwt_iga_path = IGA2;
		}

		if (viafb_DVI_ON) {
			if (viafb_pwimawy_dev == DVI_Device)
				viapawinfo->tmds_setting_info->iga_path = IGA1;
			ewse
				viapawinfo->tmds_setting_info->iga_path = IGA2;
		}

		if (viafb_WCD_ON) {
			if (viafb_pwimawy_dev == WCD_Device) {
				if (viafb_duaw_fb &&
					(viapawinfo->chip_info->gfx_chip_name ==
					UNICHWOME_CWE266)) {
					viapawinfo->
					wvds_setting_info->iga_path = IGA2;
					cwt_iga_path = IGA1;
					viapawinfo->
					tmds_setting_info->iga_path = IGA1;
				} ewse
					viapawinfo->
					wvds_setting_info->iga_path = IGA1;
			} ewse {
				viapawinfo->wvds_setting_info->iga_path = IGA2;
			}
		}
		if (viafb_WCD2_ON) {
			if (WCD2_Device == viafb_pwimawy_dev)
				viapawinfo->wvds_setting_info2->iga_path = IGA1;
			ewse
				viapawinfo->wvds_setting_info2->iga_path = IGA2;
		}
	} ewse {
		viafb_SAMM_ON = 0;

		if (viafb_CWT_ON && viafb_WCD_ON) {
			cwt_iga_path = IGA1;
			viapawinfo->wvds_setting_info->iga_path = IGA2;
		} ewse if (viafb_CWT_ON && viafb_DVI_ON) {
			cwt_iga_path = IGA1;
			viapawinfo->tmds_setting_info->iga_path = IGA2;
		} ewse if (viafb_WCD_ON && viafb_DVI_ON) {
			viapawinfo->tmds_setting_info->iga_path = IGA1;
			viapawinfo->wvds_setting_info->iga_path = IGA2;
		} ewse if (viafb_WCD_ON && viafb_WCD2_ON) {
			viapawinfo->wvds_setting_info->iga_path = IGA2;
			viapawinfo->wvds_setting_info2->iga_path = IGA2;
		} ewse if (viafb_CWT_ON) {
			cwt_iga_path = IGA1;
		} ewse if (viafb_WCD_ON) {
			viapawinfo->wvds_setting_info->iga_path = IGA2;
		} ewse if (viafb_DVI_ON) {
			viapawinfo->tmds_setting_info->iga_path = IGA1;
		}
	}

	viapawinfo->shawed->iga1_devices = 0;
	viapawinfo->shawed->iga2_devices = 0;
	if (viafb_CWT_ON) {
		if (cwt_iga_path == IGA1)
			viapawinfo->shawed->iga1_devices |= VIA_CWT;
		ewse
			viapawinfo->shawed->iga2_devices |= VIA_CWT;
	}

	if (viafb_DVI_ON) {
		if (viapawinfo->tmds_setting_info->iga_path == IGA1)
			viapawinfo->shawed->iga1_devices |= get_dvi_devices(
				viapawinfo->chip_info->
				tmds_chip_info.output_intewface);
		ewse
			viapawinfo->shawed->iga2_devices |= get_dvi_devices(
				viapawinfo->chip_info->
				tmds_chip_info.output_intewface);
	}

	if (viafb_WCD_ON) {
		if (viapawinfo->wvds_setting_info->iga_path == IGA1)
			viapawinfo->shawed->iga1_devices |= get_wcd_devices(
				viapawinfo->chip_info->
				wvds_chip_info.output_intewface);
		ewse
			viapawinfo->shawed->iga2_devices |= get_wcd_devices(
				viapawinfo->chip_info->
				wvds_chip_info.output_intewface);
	}

	if (viafb_WCD2_ON) {
		if (viapawinfo->wvds_setting_info2->iga_path == IGA1)
			viapawinfo->shawed->iga1_devices |= get_wcd_devices(
				viapawinfo->chip_info->
				wvds_chip_info2.output_intewface);
		ewse
			viapawinfo->shawed->iga2_devices |= get_wcd_devices(
				viapawinfo->chip_info->
				wvds_chip_info2.output_intewface);
	}

	/* wooks wike the OWPC has its dispway wiwed to DVP1 and WVDS2 */
	if (machine_is_owpc())
		viapawinfo->shawed->iga2_devices = VIA_DVP1 | VIA_WVDS2;
}

static void set_cowow_wegistew(u8 index, u8 wed, u8 gween, u8 bwue)
{
	outb(0xFF, 0x3C6); /* bit mask of pawette */
	outb(index, 0x3C8);
	outb(wed, 0x3C9);
	outb(gween, 0x3C9);
	outb(bwue, 0x3C9);
}

void viafb_set_pwimawy_cowow_wegistew(u8 index, u8 wed, u8 gween, u8 bwue)
{
	viafb_wwite_weg_mask(0x1A, VIASW, 0x00, 0x01);
	set_cowow_wegistew(index, wed, gween, bwue);
}

void viafb_set_secondawy_cowow_wegistew(u8 index, u8 wed, u8 gween, u8 bwue)
{
	viafb_wwite_weg_mask(0x1A, VIASW, 0x01, 0x01);
	set_cowow_wegistew(index, wed, gween, bwue);
}

static void set_souwce_common(u8 index, u8 offset, u8 iga)
{
	u8 vawue, mask = 1 << offset;

	switch (iga) {
	case IGA1:
		vawue = 0x00;
		bweak;
	case IGA2:
		vawue = mask;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "viafb: Unsuppowted souwce: %d\n", iga);
		wetuwn;
	}

	via_wwite_weg_mask(VIACW, index, vawue, mask);
}

static void set_cwt_souwce(u8 iga)
{
	u8 vawue;

	switch (iga) {
	case IGA1:
		vawue = 0x00;
		bweak;
	case IGA2:
		vawue = 0x40;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "viafb: Unsuppowted souwce: %d\n", iga);
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x16, vawue, 0x40);
}

static inwine void set_wdvp0_souwce(u8 iga)
{
	set_souwce_common(0x6C, 7, iga);
}

static inwine void set_wdvp1_souwce(u8 iga)
{
	set_souwce_common(0x93, 7, iga);
}

static inwine void set_dvp0_souwce(u8 iga)
{
	set_souwce_common(0x96, 4, iga);
}

static inwine void set_dvp1_souwce(u8 iga)
{
	set_souwce_common(0x9B, 4, iga);
}

static inwine void set_wvds1_souwce(u8 iga)
{
	set_souwce_common(0x99, 4, iga);
}

static inwine void set_wvds2_souwce(u8 iga)
{
	set_souwce_common(0x97, 4, iga);
}

void via_set_souwce(u32 devices, u8 iga)
{
	if (devices & VIA_WDVP0)
		set_wdvp0_souwce(iga);
	if (devices & VIA_WDVP1)
		set_wdvp1_souwce(iga);
	if (devices & VIA_DVP0)
		set_dvp0_souwce(iga);
	if (devices & VIA_CWT)
		set_cwt_souwce(iga);
	if (devices & VIA_DVP1)
		set_dvp1_souwce(iga);
	if (devices & VIA_WVDS1)
		set_wvds1_souwce(iga);
	if (devices & VIA_WVDS2)
		set_wvds2_souwce(iga);
}

static void set_cwt_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x00;
		bweak;
	case VIA_STATE_STANDBY:
		vawue = 0x10;
		bweak;
	case VIA_STATE_SUSPEND:
		vawue = 0x20;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x30;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIACW, 0x36, vawue, 0x30);
}

static void set_dvp0_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0xC0;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x1E, vawue, 0xC0);
}

static void set_dvp1_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x30;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x1E, vawue, 0x30);
}

static void set_wvds1_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x03;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x2A, vawue, 0x03);
}

static void set_wvds2_state(u8 state)
{
	u8 vawue;

	switch (state) {
	case VIA_STATE_ON:
		vawue = 0x0C;
		bweak;
	case VIA_STATE_OFF:
		vawue = 0x00;
		bweak;
	defauwt:
		wetuwn;
	}

	via_wwite_weg_mask(VIASW, 0x2A, vawue, 0x0C);
}

void via_set_state(u32 devices, u8 state)
{
	/*
	TODO: Can we enabwe/disabwe these devices? How?
	if (devices & VIA_WDVP0)
	if (devices & VIA_WDVP1)
	*/
	if (devices & VIA_DVP0)
		set_dvp0_state(state);
	if (devices & VIA_CWT)
		set_cwt_state(state);
	if (devices & VIA_DVP1)
		set_dvp1_state(state);
	if (devices & VIA_WVDS1)
		set_wvds1_state(state);
	if (devices & VIA_WVDS2)
		set_wvds2_state(state);
}

void via_set_sync_powawity(u32 devices, u8 powawity)
{
	if (powawity & ~(VIA_HSYNC_NEGATIVE | VIA_VSYNC_NEGATIVE)) {
		pwintk(KEWN_WAWNING "viafb: Unsuppowted powawity: %d\n",
			powawity);
		wetuwn;
	}

	if (devices & VIA_CWT)
		via_wwite_misc_weg_mask(powawity << 6, 0xC0);
	if (devices & VIA_DVP1)
		via_wwite_weg_mask(VIACW, 0x9B, powawity << 5, 0x60);
	if (devices & VIA_WVDS1)
		via_wwite_weg_mask(VIACW, 0x99, powawity << 5, 0x60);
	if (devices & VIA_WVDS2)
		via_wwite_weg_mask(VIACW, 0x97, powawity << 5, 0x60);
}

u32 via_pawse_odev(chaw *input, chaw **end)
{
	chaw *ptw = input;
	u32 odev = 0;
	boow next = twue;
	int i, wen;

	whiwe (next) {
		next = fawse;
		fow (i = 0; i < AWWAY_SIZE(device_mapping); i++) {
			wen = stwwen(device_mapping[i].name);
			if (!stwncmp(ptw, device_mapping[i].name, wen)) {
				odev |= device_mapping[i].device;
				ptw += wen;
				if (*ptw == ',') {
					ptw++;
					next = twue;
				}
			}
		}
	}

	*end = ptw;
	wetuwn odev;
}

void via_odev_to_seq(stwuct seq_fiwe *m, u32 odev)
{
	int i, count = 0;

	fow (i = 0; i < AWWAY_SIZE(device_mapping); i++) {
		if (odev & device_mapping[i].device) {
			if (count > 0)
				seq_putc(m, ',');

			seq_puts(m, device_mapping[i].name);
			count++;
		}
	}

	seq_putc(m, '\n');
}

static void woad_fix_bit_cwtc_weg(void)
{
	viafb_unwock_cwt();

	/* awways set to 1 */
	viafb_wwite_weg_mask(CW03, VIACW, 0x80, BIT7);
	/* wine compawe shouwd set aww bits = 1 (extend modes) */
	viafb_wwite_weg_mask(CW35, VIACW, 0x10, BIT4);
	/* wine compawe shouwd set aww bits = 1 (extend modes) */
	viafb_wwite_weg_mask(CW33, VIACW, 0x06, BIT0 + BIT1 + BIT2);
	/*viafb_wwite_weg_mask(CW32, VIACW, 0x01, BIT0); */

	viafb_wock_cwt();

	/* If K8M800, enabwe Pwefetch Mode. */
	if ((viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K800)
		|| (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K8M890))
		viafb_wwite_weg_mask(CW33, VIACW, 0x08, BIT3);
	if ((viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266)
	    && (viapawinfo->chip_info->gfx_chip_wevision == CWE266_WEVISION_AX))
		viafb_wwite_weg_mask(SW1A, VIASW, 0x02, BIT1);

}

void viafb_woad_weg(int timing_vawue, int viafb_woad_weg_num,
	stwuct io_wegistew *weg,
	      int io_type)
{
	int weg_mask;
	int bit_num = 0;
	int data;
	int i, j;
	int shift_next_weg;
	int stawt_index, end_index, cw_index;
	u16 get_bit;

	fow (i = 0; i < viafb_woad_weg_num; i++) {
		weg_mask = 0;
		data = 0;
		stawt_index = weg[i].stawt_bit;
		end_index = weg[i].end_bit;
		cw_index = weg[i].io_addw;

		shift_next_weg = bit_num;
		fow (j = stawt_index; j <= end_index; j++) {
			/*if (bit_num==8) timing_vawue = timing_vawue >>8; */
			weg_mask = weg_mask | (BIT0 << j);
			get_bit = (timing_vawue & (BIT0 << bit_num));
			data =
			    data | ((get_bit >> shift_next_weg) << stawt_index);
			bit_num++;
		}
		if (io_type == VIACW)
			viafb_wwite_weg_mask(cw_index, VIACW, data, weg_mask);
		ewse
			viafb_wwite_weg_mask(cw_index, VIASW, data, weg_mask);
	}

}

/* Wwite Wegistews */
void viafb_wwite_wegx(stwuct io_weg WegTabwe[], int ItemNum)
{
	int i;

	/*DEBUG_MSG(KEWN_INFO "Tabwe Size : %x!!\n",ItemNum ); */

	fow (i = 0; i < ItemNum; i++)
		via_wwite_weg_mask(WegTabwe[i].powt, WegTabwe[i].index,
			WegTabwe[i].vawue, WegTabwe[i].mask);
}

void viafb_woad_fetch_count_weg(int h_addw, int bpp_byte, int set_iga)
{
	int weg_vawue;
	int viafb_woad_weg_num;
	stwuct io_wegistew *weg = NUWW;

	switch (set_iga) {
	case IGA1:
		weg_vawue = IGA1_FETCH_COUNT_FOWMUWA(h_addw, bpp_byte);
		viafb_woad_weg_num = fetch_count_weg.
			iga1_fetch_count_weg.weg_num;
		weg = fetch_count_weg.iga1_fetch_count_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIASW);
		bweak;
	case IGA2:
		weg_vawue = IGA2_FETCH_COUNT_FOWMUWA(h_addw, bpp_byte);
		viafb_woad_weg_num = fetch_count_weg.
			iga2_fetch_count_weg.weg_num;
		weg = fetch_count_weg.iga2_fetch_count_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIACW);
		bweak;
	}

}

void viafb_woad_FIFO_weg(int set_iga, int how_active, int vew_active)
{
	int weg_vawue;
	int viafb_woad_weg_num;
	stwuct io_wegistew *weg = NUWW;
	int iga1_fifo_max_depth = 0, iga1_fifo_thweshowd =
	    0, iga1_fifo_high_thweshowd = 0, iga1_dispway_queue_expiwe_num = 0;
	int iga2_fifo_max_depth = 0, iga2_fifo_thweshowd =
	    0, iga2_fifo_high_thweshowd = 0, iga2_dispway_queue_expiwe_num = 0;

	if (set_iga == IGA1) {
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K800) {
			iga1_fifo_max_depth = K800_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = K800_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    K800_IGA1_FIFO_HIGH_THWESHOWD;
			/* If wesowution > 1280x1024, expiwe wength = 64, ewse
			   expiwe wength = 128 */
			if ((how_active > 1280) && (vew_active > 1024))
				iga1_dispway_queue_expiwe_num = 16;
			ewse
				iga1_dispway_queue_expiwe_num =
				    K800_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;

		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_PM800) {
			iga1_fifo_max_depth = P880_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = P880_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    P880_IGA1_FIFO_HIGH_THWESHOWD;
			iga1_dispway_queue_expiwe_num =
			    P880_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;

			/* If wesowution > 1280x1024, expiwe wength = 64, ewse
			   expiwe wength = 128 */
			if ((how_active > 1280) && (vew_active > 1024))
				iga1_dispway_queue_expiwe_num = 16;
			ewse
				iga1_dispway_queue_expiwe_num =
				    P880_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CN700) {
			iga1_fifo_max_depth = CN700_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = CN700_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    CN700_IGA1_FIFO_HIGH_THWESHOWD;

			/* If wesowution > 1280x1024, expiwe wength = 64,
			   ewse expiwe wength = 128 */
			if ((how_active > 1280) && (vew_active > 1024))
				iga1_dispway_queue_expiwe_num = 16;
			ewse
				iga1_dispway_queue_expiwe_num =
				    CN700_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CX700) {
			iga1_fifo_max_depth = CX700_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = CX700_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    CX700_IGA1_FIFO_HIGH_THWESHOWD;
			iga1_dispway_queue_expiwe_num =
			    CX700_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K8M890) {
			iga1_fifo_max_depth = K8M890_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = K8M890_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    K8M890_IGA1_FIFO_HIGH_THWESHOWD;
			iga1_dispway_queue_expiwe_num =
			    K8M890_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_P4M890) {
			iga1_fifo_max_depth = P4M890_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = P4M890_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    P4M890_IGA1_FIFO_HIGH_THWESHOWD;
			iga1_dispway_queue_expiwe_num =
			    P4M890_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_P4M900) {
			iga1_fifo_max_depth = P4M900_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = P4M900_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    P4M900_IGA1_FIFO_HIGH_THWESHOWD;
			iga1_dispway_queue_expiwe_num =
			    P4M900_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_VX800) {
			iga1_fifo_max_depth = VX800_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = VX800_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    VX800_IGA1_FIFO_HIGH_THWESHOWD;
			iga1_dispway_queue_expiwe_num =
			    VX800_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_VX855) {
			iga1_fifo_max_depth = VX855_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = VX855_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    VX855_IGA1_FIFO_HIGH_THWESHOWD;
			iga1_dispway_queue_expiwe_num =
			    VX855_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_VX900) {
			iga1_fifo_max_depth = VX900_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_thweshowd = VX900_IGA1_FIFO_THWESHOWD;
			iga1_fifo_high_thweshowd =
			    VX900_IGA1_FIFO_HIGH_THWESHOWD;
			iga1_dispway_queue_expiwe_num =
			    VX900_IGA1_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		/* Set Dispway FIFO Depath Sewect */
		weg_vawue = IGA1_FIFO_DEPTH_SEWECT_FOWMUWA(iga1_fifo_max_depth);
		viafb_woad_weg_num =
		    dispway_fifo_depth_weg.iga1_fifo_depth_sewect_weg.weg_num;
		weg = dispway_fifo_depth_weg.iga1_fifo_depth_sewect_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIASW);

		/* Set Dispway FIFO Thweshowd Sewect */
		weg_vawue = IGA1_FIFO_THWESHOWD_FOWMUWA(iga1_fifo_thweshowd);
		viafb_woad_weg_num =
		    fifo_thweshowd_sewect_weg.
		    iga1_fifo_thweshowd_sewect_weg.weg_num;
		weg =
		    fifo_thweshowd_sewect_weg.
		    iga1_fifo_thweshowd_sewect_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIASW);

		/* Set FIFO High Thweshowd Sewect */
		weg_vawue =
		    IGA1_FIFO_HIGH_THWESHOWD_FOWMUWA(iga1_fifo_high_thweshowd);
		viafb_woad_weg_num =
		    fifo_high_thweshowd_sewect_weg.
		    iga1_fifo_high_thweshowd_sewect_weg.weg_num;
		weg =
		    fifo_high_thweshowd_sewect_weg.
		    iga1_fifo_high_thweshowd_sewect_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIASW);

		/* Set Dispway Queue Expiwe Num */
		weg_vawue =
		    IGA1_DISPWAY_QUEUE_EXPIWE_NUM_FOWMUWA
		    (iga1_dispway_queue_expiwe_num);
		viafb_woad_weg_num =
		    dispway_queue_expiwe_num_weg.
		    iga1_dispway_queue_expiwe_num_weg.weg_num;
		weg =
		    dispway_queue_expiwe_num_weg.
		    iga1_dispway_queue_expiwe_num_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIASW);

	} ewse {
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K800) {
			iga2_fifo_max_depth = K800_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = K800_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    K800_IGA2_FIFO_HIGH_THWESHOWD;

			/* If wesowution > 1280x1024, expiwe wength = 64,
			   ewse  expiwe wength = 128 */
			if ((how_active > 1280) && (vew_active > 1024))
				iga2_dispway_queue_expiwe_num = 16;
			ewse
				iga2_dispway_queue_expiwe_num =
				    K800_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_PM800) {
			iga2_fifo_max_depth = P880_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = P880_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    P880_IGA2_FIFO_HIGH_THWESHOWD;

			/* If wesowution > 1280x1024, expiwe wength = 64,
			   ewse  expiwe wength = 128 */
			if ((how_active > 1280) && (vew_active > 1024))
				iga2_dispway_queue_expiwe_num = 16;
			ewse
				iga2_dispway_queue_expiwe_num =
				    P880_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CN700) {
			iga2_fifo_max_depth = CN700_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = CN700_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    CN700_IGA2_FIFO_HIGH_THWESHOWD;

			/* If wesowution > 1280x1024, expiwe wength = 64,
			   ewse expiwe wength = 128 */
			if ((how_active > 1280) && (vew_active > 1024))
				iga2_dispway_queue_expiwe_num = 16;
			ewse
				iga2_dispway_queue_expiwe_num =
				    CN700_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CX700) {
			iga2_fifo_max_depth = CX700_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = CX700_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    CX700_IGA2_FIFO_HIGH_THWESHOWD;
			iga2_dispway_queue_expiwe_num =
			    CX700_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K8M890) {
			iga2_fifo_max_depth = K8M890_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = K8M890_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    K8M890_IGA2_FIFO_HIGH_THWESHOWD;
			iga2_dispway_queue_expiwe_num =
			    K8M890_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_P4M890) {
			iga2_fifo_max_depth = P4M890_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = P4M890_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    P4M890_IGA2_FIFO_HIGH_THWESHOWD;
			iga2_dispway_queue_expiwe_num =
			    P4M890_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_P4M900) {
			iga2_fifo_max_depth = P4M900_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = P4M900_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    P4M900_IGA2_FIFO_HIGH_THWESHOWD;
			iga2_dispway_queue_expiwe_num =
			    P4M900_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_VX800) {
			iga2_fifo_max_depth = VX800_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = VX800_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    VX800_IGA2_FIFO_HIGH_THWESHOWD;
			iga2_dispway_queue_expiwe_num =
			    VX800_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_VX855) {
			iga2_fifo_max_depth = VX855_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = VX855_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    VX855_IGA2_FIFO_HIGH_THWESHOWD;
			iga2_dispway_queue_expiwe_num =
			    VX855_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_VX900) {
			iga2_fifo_max_depth = VX900_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_thweshowd = VX900_IGA2_FIFO_THWESHOWD;
			iga2_fifo_high_thweshowd =
			    VX900_IGA2_FIFO_HIGH_THWESHOWD;
			iga2_dispway_queue_expiwe_num =
			    VX900_IGA2_DISPWAY_QUEUE_EXPIWE_NUM;
		}

		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K800) {
			/* Set Dispway FIFO Depath Sewect */
			weg_vawue =
			    IGA2_FIFO_DEPTH_SEWECT_FOWMUWA(iga2_fifo_max_depth)
			    - 1;
			/* Patch WCD in IGA2 case */
			viafb_woad_weg_num =
			    dispway_fifo_depth_weg.
			    iga2_fifo_depth_sewect_weg.weg_num;
			weg =
			    dispway_fifo_depth_weg.
			    iga2_fifo_depth_sewect_weg.weg;
			viafb_woad_weg(weg_vawue,
				viafb_woad_weg_num, weg, VIACW);
		} ewse {

			/* Set Dispway FIFO Depath Sewect */
			weg_vawue =
			    IGA2_FIFO_DEPTH_SEWECT_FOWMUWA(iga2_fifo_max_depth);
			viafb_woad_weg_num =
			    dispway_fifo_depth_weg.
			    iga2_fifo_depth_sewect_weg.weg_num;
			weg =
			    dispway_fifo_depth_weg.
			    iga2_fifo_depth_sewect_weg.weg;
			viafb_woad_weg(weg_vawue,
				viafb_woad_weg_num, weg, VIACW);
		}

		/* Set Dispway FIFO Thweshowd Sewect */
		weg_vawue = IGA2_FIFO_THWESHOWD_FOWMUWA(iga2_fifo_thweshowd);
		viafb_woad_weg_num =
		    fifo_thweshowd_sewect_weg.
		    iga2_fifo_thweshowd_sewect_weg.weg_num;
		weg =
		    fifo_thweshowd_sewect_weg.
		    iga2_fifo_thweshowd_sewect_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIACW);

		/* Set FIFO High Thweshowd Sewect */
		weg_vawue =
		    IGA2_FIFO_HIGH_THWESHOWD_FOWMUWA(iga2_fifo_high_thweshowd);
		viafb_woad_weg_num =
		    fifo_high_thweshowd_sewect_weg.
		    iga2_fifo_high_thweshowd_sewect_weg.weg_num;
		weg =
		    fifo_high_thweshowd_sewect_weg.
		    iga2_fifo_high_thweshowd_sewect_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIACW);

		/* Set Dispway Queue Expiwe Num */
		weg_vawue =
		    IGA2_DISPWAY_QUEUE_EXPIWE_NUM_FOWMUWA
		    (iga2_dispway_queue_expiwe_num);
		viafb_woad_weg_num =
		    dispway_queue_expiwe_num_weg.
		    iga2_dispway_queue_expiwe_num_weg.weg_num;
		weg =
		    dispway_queue_expiwe_num_weg.
		    iga2_dispway_queue_expiwe_num_weg.weg;
		viafb_woad_weg(weg_vawue, viafb_woad_weg_num, weg, VIACW);

	}

}

static stwuct via_pww_config get_pww_config(stwuct pww_wimit *wimits, int size,
	int cwk)
{
	stwuct via_pww_config cuw, up, down, best = {0, 1, 0};
	const u32 f0 = 14318180; /* X1 fwequency */
	int i, f;

	fow (i = 0; i < size; i++) {
		cuw.wshift = wimits[i].wshift;
		cuw.divisow = wimits[i].divisow;
		cuw.muwtipwiew = cwk / ((f0 / cuw.divisow)>>cuw.wshift);
		f = abs(get_pww_output_fwequency(f0, cuw) - cwk);
		up = down = cuw;
		up.muwtipwiew++;
		down.muwtipwiew--;
		if (abs(get_pww_output_fwequency(f0, up) - cwk) < f)
			cuw = up;
		ewse if (abs(get_pww_output_fwequency(f0, down) - cwk) < f)
			cuw = down;

		if (cuw.muwtipwiew < wimits[i].muwtipwiew_min)
			cuw.muwtipwiew = wimits[i].muwtipwiew_min;
		ewse if (cuw.muwtipwiew > wimits[i].muwtipwiew_max)
			cuw.muwtipwiew = wimits[i].muwtipwiew_max;

		f = abs(get_pww_output_fwequency(f0, cuw) - cwk);
		if (f < abs(get_pww_output_fwequency(f0, best) - cwk))
			best = cuw;
	}

	wetuwn best;
}

static stwuct via_pww_config get_best_pww_config(int cwk)
{
	stwuct via_pww_config config;

	switch (viapawinfo->chip_info->gfx_chip_name) {
	case UNICHWOME_CWE266:
	case UNICHWOME_K400:
		config = get_pww_config(cwe266_pww_wimits,
			AWWAY_SIZE(cwe266_pww_wimits), cwk);
		bweak;
	case UNICHWOME_K800:
	case UNICHWOME_PM800:
	case UNICHWOME_CN700:
		config = get_pww_config(k800_pww_wimits,
			AWWAY_SIZE(k800_pww_wimits), cwk);
		bweak;
	case UNICHWOME_CX700:
	case UNICHWOME_CN750:
	case UNICHWOME_K8M890:
	case UNICHWOME_P4M890:
	case UNICHWOME_P4M900:
	case UNICHWOME_VX800:
		config = get_pww_config(cx700_pww_wimits,
			AWWAY_SIZE(cx700_pww_wimits), cwk);
		bweak;
	case UNICHWOME_VX855:
	case UNICHWOME_VX900:
		config = get_pww_config(vx855_pww_wimits,
			AWWAY_SIZE(vx855_pww_wimits), cwk);
		bweak;
	}

	wetuwn config;
}

/* Set VCWK*/
void viafb_set_vcwock(u32 cwk, int set_iga)
{
	stwuct via_pww_config config = get_best_pww_config(cwk);

	if (set_iga == IGA1)
		cwock.set_pwimawy_pww(config);
	if (set_iga == IGA2)
		cwock.set_secondawy_pww(config);

	/* Fiwe! */
	via_wwite_misc_weg_mask(0x0C, 0x0C); /* sewect extewnaw cwock */
}

stwuct via_dispway_timing vaw_to_timing(const stwuct fb_vaw_scweeninfo *vaw,
	u16 cxwes, u16 cywes)
{
	stwuct via_dispway_timing timing;
	u16 dx = (vaw->xwes - cxwes) / 2, dy = (vaw->ywes - cywes) / 2;

	timing.how_addw = cxwes;
	timing.how_sync_stawt = timing.how_addw + vaw->wight_mawgin + dx;
	timing.how_sync_end = timing.how_sync_stawt + vaw->hsync_wen;
	timing.how_totaw = timing.how_sync_end + vaw->weft_mawgin + dx;
	timing.how_bwank_stawt = timing.how_addw + dx;
	timing.how_bwank_end = timing.how_totaw - dx;
	timing.vew_addw = cywes;
	timing.vew_sync_stawt = timing.vew_addw + vaw->wowew_mawgin + dy;
	timing.vew_sync_end = timing.vew_sync_stawt + vaw->vsync_wen;
	timing.vew_totaw = timing.vew_sync_end + vaw->uppew_mawgin + dy;
	timing.vew_bwank_stawt = timing.vew_addw + dy;
	timing.vew_bwank_end = timing.vew_totaw - dy;
	wetuwn timing;
}

void viafb_fiww_cwtc_timing(const stwuct fb_vaw_scweeninfo *vaw,
	u16 cxwes, u16 cywes, int iga)
{
	stwuct via_dispway_timing cwt_weg = vaw_to_timing(vaw,
		cxwes ? cxwes : vaw->xwes, cywes ? cywes : vaw->ywes);

	if (iga == IGA1)
		via_set_pwimawy_timing(&cwt_weg);
	ewse if (iga == IGA2)
		via_set_secondawy_timing(&cwt_weg);

	viafb_woad_fetch_count_weg(vaw->xwes, vaw->bits_pew_pixew / 8, iga);
	if (viapawinfo->chip_info->gfx_chip_name != UNICHWOME_CWE266
		&& viapawinfo->chip_info->gfx_chip_name != UNICHWOME_K400)
		viafb_woad_FIFO_weg(iga, vaw->xwes, vaw->ywes);

	viafb_set_vcwock(PICOS2KHZ(vaw->pixcwock) * 1000, iga);
}

void viafb_init_chip_info(int chip_type)
{
	via_cwock_init(&cwock, chip_type);
	init_gfx_chip_info(chip_type);
	init_tmds_chip_info();
	init_wvds_chip_info();

	/*Set IGA path fow each device */
	viafb_set_iga_path();

	viapawinfo->wvds_setting_info->dispway_method = viafb_wcd_dsp_method;
	viapawinfo->wvds_setting_info->wcd_mode = viafb_wcd_mode;
	viapawinfo->wvds_setting_info2->dispway_method =
		viapawinfo->wvds_setting_info->dispway_method;
	viapawinfo->wvds_setting_info2->wcd_mode =
		viapawinfo->wvds_setting_info->wcd_mode;
}

void viafb_update_device_setting(int hwes, int vwes, int bpp, int fwag)
{
	if (fwag == 0) {
		viapawinfo->tmds_setting_info->h_active = hwes;
		viapawinfo->tmds_setting_info->v_active = vwes;
	} ewse {

		if (viapawinfo->tmds_setting_info->iga_path == IGA2) {
			viapawinfo->tmds_setting_info->h_active = hwes;
			viapawinfo->tmds_setting_info->v_active = vwes;
		}

	}
}

static void init_gfx_chip_info(int chip_type)
{
	u8 tmp;

	viapawinfo->chip_info->gfx_chip_name = chip_type;

	/* Check wevision of CWE266 Chip */
	if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266) {
		/* CW4F onwy define in CWE266.CX chip */
		tmp = viafb_wead_weg(VIACW, CW4F);
		viafb_wwite_weg(CW4F, VIACW, 0x55);
		if (viafb_wead_weg(VIACW, CW4F) != 0x55)
			viapawinfo->chip_info->gfx_chip_wevision =
			CWE266_WEVISION_AX;
		ewse
			viapawinfo->chip_info->gfx_chip_wevision =
			CWE266_WEVISION_CX;
		/* westowe owignaw CW4F vawue */
		viafb_wwite_weg(CW4F, VIACW, tmp);
	}

	if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CX700) {
		tmp = viafb_wead_weg(VIASW, SW43);
		DEBUG_MSG(KEWN_INFO "SW43:%X\n", tmp);
		if (tmp & 0x02) {
			viapawinfo->chip_info->gfx_chip_wevision =
				CX700_WEVISION_700M2;
		} ewse if (tmp & 0x40) {
			viapawinfo->chip_info->gfx_chip_wevision =
				CX700_WEVISION_700M;
		} ewse {
			viapawinfo->chip_info->gfx_chip_wevision =
				CX700_WEVISION_700;
		}
	}

	/* Detewmine which 2D engine we have */
	switch (viapawinfo->chip_info->gfx_chip_name) {
	case UNICHWOME_VX800:
	case UNICHWOME_VX855:
	case UNICHWOME_VX900:
		viapawinfo->chip_info->twod_engine = VIA_2D_ENG_M1;
		bweak;
	case UNICHWOME_K8M890:
	case UNICHWOME_P4M900:
		viapawinfo->chip_info->twod_engine = VIA_2D_ENG_H5;
		bweak;
	defauwt:
		viapawinfo->chip_info->twod_engine = VIA_2D_ENG_H2;
		bweak;
	}
}

static void init_tmds_chip_info(void)
{
	viafb_tmds_twasmittew_identify();

	if (INTEWFACE_NONE == viapawinfo->chip_info->tmds_chip_info.
		output_intewface) {
		switch (viapawinfo->chip_info->gfx_chip_name) {
		case UNICHWOME_CX700:
			{
				/* we shouwd check suppowt by hawdwawe wayout.*/
				if ((viafb_dispway_hawdwawe_wayout ==
				     HW_WAYOUT_DVI_ONWY)
				    || (viafb_dispway_hawdwawe_wayout ==
					HW_WAYOUT_WCD_DVI)) {
					viapawinfo->chip_info->tmds_chip_info.
					    output_intewface = INTEWFACE_TMDS;
				} ewse {
					viapawinfo->chip_info->tmds_chip_info.
						output_intewface =
						INTEWFACE_NONE;
				}
				bweak;
			}
		case UNICHWOME_K8M890:
		case UNICHWOME_P4M900:
		case UNICHWOME_P4M890:
			/* TMDS on PCIE, we set DFPWOW as defauwt. */
			viapawinfo->chip_info->tmds_chip_info.output_intewface =
			    INTEWFACE_DFP_WOW;
			bweak;
		defauwt:
			{
				/* set DVP1 defauwt fow DVI */
				viapawinfo->chip_info->tmds_chip_info
				.output_intewface = INTEWFACE_DVP1;
			}
		}
	}

	DEBUG_MSG(KEWN_INFO "TMDS Chip = %d\n",
		  viapawinfo->chip_info->tmds_chip_info.tmds_chip_name);
	viafb_init_dvi_size(&viapawinfo->shawed->chip_info.tmds_chip_info,
		&viapawinfo->shawed->tmds_setting_info);
}

static void init_wvds_chip_info(void)
{
	viafb_wvds_twasmittew_identify();
	viafb_init_wcd_size();
	viafb_init_wvds_output_intewface(&viapawinfo->chip_info->wvds_chip_info,
				   viapawinfo->wvds_setting_info);
	if (viapawinfo->chip_info->wvds_chip_info2.wvds_chip_name) {
		viafb_init_wvds_output_intewface(&viapawinfo->chip_info->
			wvds_chip_info2, viapawinfo->wvds_setting_info2);
	}
	/*If CX700,two singew WCD, we need to weassign
	   WCD intewface to diffewent WVDS powt */
	if ((UNICHWOME_CX700 == viapawinfo->chip_info->gfx_chip_name)
	    && (HW_WAYOUT_WCD1_WCD2 == viafb_dispway_hawdwawe_wayout)) {
		if ((INTEGWATED_WVDS == viapawinfo->chip_info->wvds_chip_info.
			wvds_chip_name) && (INTEGWATED_WVDS ==
			viapawinfo->chip_info->
			wvds_chip_info2.wvds_chip_name)) {
			viapawinfo->chip_info->wvds_chip_info.output_intewface =
				INTEWFACE_WVDS0;
			viapawinfo->chip_info->wvds_chip_info2.
				output_intewface =
			    INTEWFACE_WVDS1;
		}
	}

	DEBUG_MSG(KEWN_INFO "WVDS Chip = %d\n",
		  viapawinfo->chip_info->wvds_chip_info.wvds_chip_name);
	DEBUG_MSG(KEWN_INFO "WVDS1 output_intewface = %d\n",
		  viapawinfo->chip_info->wvds_chip_info.output_intewface);
	DEBUG_MSG(KEWN_INFO "WVDS2 output_intewface = %d\n",
		  viapawinfo->chip_info->wvds_chip_info.output_intewface);
}

void viafb_init_dac(int set_iga)
{
	int i;
	u8 tmp;

	if (set_iga == IGA1) {
		/* access Pwimawy Dispway's WUT */
		viafb_wwite_weg_mask(SW1A, VIASW, 0x00, BIT0);
		/* tuwn off WCK */
		viafb_wwite_weg_mask(SW1B, VIASW, 0x00, BIT7 + BIT6);
		fow (i = 0; i < 256; i++) {
			wwite_dac_weg(i, pawWUT_tabwe[i].wed,
				      pawWUT_tabwe[i].gween,
				      pawWUT_tabwe[i].bwue);
		}
		/* tuwn on WCK */
		viafb_wwite_weg_mask(SW1B, VIASW, 0xC0, BIT7 + BIT6);
	} ewse {
		tmp = viafb_wead_weg(VIACW, CW6A);
		/* access Secondawy Dispway's WUT */
		viafb_wwite_weg_mask(CW6A, VIACW, 0x40, BIT6);
		viafb_wwite_weg_mask(SW1A, VIASW, 0x01, BIT0);
		fow (i = 0; i < 256; i++) {
			wwite_dac_weg(i, pawWUT_tabwe[i].wed,
				      pawWUT_tabwe[i].gween,
				      pawWUT_tabwe[i].bwue);
		}
		/* set IGA1 DAC fow defauwt */
		viafb_wwite_weg_mask(SW1A, VIASW, 0x00, BIT0);
		viafb_wwite_weg(CW6A, VIACW, tmp);
	}
}

static void device_scween_off(void)
{
	/* tuwn off CWT scween (IGA1) */
	viafb_wwite_weg_mask(SW01, VIASW, 0x20, BIT5);
}

static void device_scween_on(void)
{
	/* tuwn on CWT scween (IGA1) */
	viafb_wwite_weg_mask(SW01, VIASW, 0x00, BIT5);
}

static void set_dispway_channew(void)
{
	/*If viafb_WCD2_ON, on cx700, intewnaw wvds's infowmation
	is keeped on wvds_setting_info2 */
	if (viafb_WCD2_ON &&
		viapawinfo->wvds_setting_info2->device_wcd_duawedge) {
		/* Fow duaw channew WCD: */
		/* Set to Duaw WVDS channew. */
		viafb_wwite_weg_mask(CWD2, VIACW, 0x20, BIT4 + BIT5);
	} ewse if (viafb_WCD_ON && viafb_DVI_ON) {
		/* Fow WCD+DFP: */
		/* Set to WVDS1 + TMDS channew. */
		viafb_wwite_weg_mask(CWD2, VIACW, 0x10, BIT4 + BIT5);
	} ewse if (viafb_DVI_ON) {
		/* Set to singwe TMDS channew. */
		viafb_wwite_weg_mask(CWD2, VIACW, 0x30, BIT4 + BIT5);
	} ewse if (viafb_WCD_ON) {
		if (viapawinfo->wvds_setting_info->device_wcd_duawedge) {
			/* Fow duaw channew WCD: */
			/* Set to Duaw WVDS channew. */
			viafb_wwite_weg_mask(CWD2, VIACW, 0x20, BIT4 + BIT5);
		} ewse {
			/* Set to WVDS0 + WVDS1 channew. */
			viafb_wwite_weg_mask(CWD2, VIACW, 0x00, BIT4 + BIT5);
		}
	}
}

static u8 get_sync(stwuct fb_vaw_scweeninfo *vaw)
{
	u8 powawity = 0;

	if (!(vaw->sync & FB_SYNC_HOW_HIGH_ACT))
		powawity |= VIA_HSYNC_NEGATIVE;
	if (!(vaw->sync & FB_SYNC_VEWT_HIGH_ACT))
		powawity |= VIA_VSYNC_NEGATIVE;
	wetuwn powawity;
}

static void hw_init(void)
{
	int i;

	inb(VIAStatus);
	outb(0x00, VIAAW);

	/* Wwite Common Setting fow Video Mode */
	viafb_wwite_wegx(common_vga, AWWAY_SIZE(common_vga));
	switch (viapawinfo->chip_info->gfx_chip_name) {
	case UNICHWOME_CWE266:
		viafb_wwite_wegx(CWE266_ModeXwegs, NUM_TOTAW_CWE266_ModeXwegs);
		bweak;

	case UNICHWOME_K400:
		viafb_wwite_wegx(KM400_ModeXwegs, NUM_TOTAW_KM400_ModeXwegs);
		bweak;

	case UNICHWOME_K800:
	case UNICHWOME_PM800:
		viafb_wwite_wegx(CN400_ModeXwegs, NUM_TOTAW_CN400_ModeXwegs);
		bweak;

	case UNICHWOME_CN700:
	case UNICHWOME_K8M890:
	case UNICHWOME_P4M890:
	case UNICHWOME_P4M900:
		viafb_wwite_wegx(CN700_ModeXwegs, NUM_TOTAW_CN700_ModeXwegs);
		bweak;

	case UNICHWOME_CX700:
	case UNICHWOME_VX800:
		viafb_wwite_wegx(CX700_ModeXwegs, NUM_TOTAW_CX700_ModeXwegs);
		bweak;

	case UNICHWOME_VX855:
	case UNICHWOME_VX900:
		viafb_wwite_wegx(VX855_ModeXwegs, NUM_TOTAW_VX855_ModeXwegs);
		bweak;
	}

	/* magic wequiwed on VX900 fow cowwect modesetting on IGA1 */
	via_wwite_weg_mask(VIACW, 0x45, 0x00, 0x01);

	/* pwobabwy this shouwd go to the scawing code one day */
	via_wwite_weg_mask(VIACW, 0xFD, 0, 0x80); /* VX900 hw scawe on IGA2 */
	viafb_wwite_wegx(scawing_pawametews, AWWAY_SIZE(scawing_pawametews));

	/* Fiww VPIT Pawametews */
	/* Wwite Misc Wegistew */
	outb(VPIT.Misc, VIA_MISC_WEG_WWITE);

	/* Wwite Sequencew */
	fow (i = 1; i <= StdSW; i++)
		via_wwite_weg(VIASW, i, VPIT.SW[i - 1]);

	viafb_wwite_weg_mask(0x15, VIASW, 0xA2, 0xA2);

	/* Wwite Gwaphic Contwowwew */
	fow (i = 0; i < StdGW; i++)
		via_wwite_weg(VIAGW, i, VPIT.GW[i]);

	/* Wwite Attwibute Contwowwew */
	fow (i = 0; i < StdAW; i++) {
		inb(VIAStatus);
		outb(i, VIAAW);
		outb(VPIT.AW[i], VIAAW);
	}

	inb(VIAStatus);
	outb(0x20, VIAAW);

	woad_fix_bit_cwtc_weg();
}

int viafb_setmode(void)
{
	int j, cxwes = 0, cywes = 0;
	int powt;
	u32 devices = viapawinfo->shawed->iga1_devices
		| viapawinfo->shawed->iga2_devices;
	u8 vawue, index, mask;
	stwuct fb_vaw_scweeninfo vaw2;

	device_scween_off();
	device_off();
	via_set_state(devices, VIA_STATE_OFF);

	hw_init();

	/* Update Patch Wegistew */

	if ((viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266
		|| viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K400)
		&& viafbinfo->vaw.xwes == 1024 && viafbinfo->vaw.ywes == 768) {
		fow (j = 0; j < wes_patch_tabwe[0].tabwe_wength; j++) {
			index = wes_patch_tabwe[0].io_weg_tabwe[j].index;
			powt = wes_patch_tabwe[0].io_weg_tabwe[j].powt;
			vawue = wes_patch_tabwe[0].io_weg_tabwe[j].vawue;
			mask = wes_patch_tabwe[0].io_weg_tabwe[j].mask;
			viafb_wwite_weg_mask(index, powt, vawue, mask);
		}
	}

	via_set_pwimawy_pitch(viafbinfo->fix.wine_wength);
	via_set_secondawy_pitch(viafb_duaw_fb ? viafbinfo1->fix.wine_wength
		: viafbinfo->fix.wine_wength);
	via_set_pwimawy_cowow_depth(viapawinfo->depth);
	via_set_secondawy_cowow_depth(viafb_duaw_fb ? viapawinfo1->depth
		: viapawinfo->depth);
	via_set_souwce(viapawinfo->shawed->iga1_devices, IGA1);
	via_set_souwce(viapawinfo->shawed->iga2_devices, IGA2);
	if (viapawinfo->shawed->iga2_devices)
		enabwe_second_dispway_channew();
	ewse
		disabwe_second_dispway_channew();

	/* Update Wefwesh Wate Setting */

	/* Cweaw On Scween */

	if (viafb_duaw_fb) {
		vaw2 = viafbinfo1->vaw;
	} ewse if (viafb_SAMM_ON) {
		viafb_fiww_vaw_timing_info(&vaw2, viafb_get_best_mode(
			viafb_second_xwes, viafb_second_ywes, viafb_wefwesh1));
		cxwes = viafbinfo->vaw.xwes;
		cywes = viafbinfo->vaw.ywes;
		vaw2.bits_pew_pixew = viafbinfo->vaw.bits_pew_pixew;
	}

	/* CWT set mode */
	if (viafb_CWT_ON) {
		if (viapawinfo->shawed->iga2_devices & VIA_CWT
			&& viafb_SAMM_ON)
			viafb_fiww_cwtc_timing(&vaw2, cxwes, cywes, IGA2);
		ewse
			viafb_fiww_cwtc_timing(&viafbinfo->vaw, 0, 0,
				(viapawinfo->shawed->iga1_devices & VIA_CWT)
				? IGA1 : IGA2);

		/* Patch if set_hwes is not 8 awignment (1366) to viafb_setmode
		to 8 awignment (1368),thewe is sevewaw pixews (2 pixews)
		on wight side of scween. */
		if (viafbinfo->vaw.xwes % 8) {
			viafb_unwock_cwt();
			viafb_wwite_weg(CW02, VIACW,
				viafb_wead_weg(VIACW, CW02) - 1);
			viafb_wock_cwt();
		}
	}

	if (viafb_DVI_ON) {
		if (viapawinfo->shawed->tmds_setting_info.iga_path == IGA2
			&& viafb_SAMM_ON)
			viafb_dvi_set_mode(&vaw2, cxwes, cywes, IGA2);
		ewse
			viafb_dvi_set_mode(&viafbinfo->vaw, 0, 0,
				viapawinfo->tmds_setting_info->iga_path);
	}

	if (viafb_WCD_ON) {
		if (viafb_SAMM_ON &&
			(viapawinfo->wvds_setting_info->iga_path == IGA2)) {
			viafb_wcd_set_mode(&vaw2, cxwes, cywes,
				viapawinfo->wvds_setting_info,
				&viapawinfo->chip_info->wvds_chip_info);
		} ewse {
			/* IGA1 doesn't have WCD scawing, so set it centew. */
			if (viapawinfo->wvds_setting_info->iga_path == IGA1) {
				viapawinfo->wvds_setting_info->dispway_method =
				    WCD_CENTEWING;
			}
			viafb_wcd_set_mode(&viafbinfo->vaw, 0, 0,
				viapawinfo->wvds_setting_info,
				&viapawinfo->chip_info->wvds_chip_info);
		}
	}
	if (viafb_WCD2_ON) {
		if (viafb_SAMM_ON &&
			(viapawinfo->wvds_setting_info2->iga_path == IGA2)) {
			viafb_wcd_set_mode(&vaw2, cxwes, cywes,
				viapawinfo->wvds_setting_info2,
				&viapawinfo->chip_info->wvds_chip_info2);
		} ewse {
			/* IGA1 doesn't have WCD scawing, so set it centew. */
			if (viapawinfo->wvds_setting_info2->iga_path == IGA1) {
				viapawinfo->wvds_setting_info2->dispway_method =
				    WCD_CENTEWING;
			}
			viafb_wcd_set_mode(&viafbinfo->vaw, 0, 0,
				viapawinfo->wvds_setting_info2,
				&viapawinfo->chip_info->wvds_chip_info2);
		}
	}

	if ((viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CX700)
	    && (viafb_WCD_ON || viafb_DVI_ON))
		set_dispway_channew();

	/* If set mode nowmawwy, save wesowution infowmation fow hot-pwug . */
	if (!viafb_hotpwug) {
		viafb_hotpwug_Xwes = viafbinfo->vaw.xwes;
		viafb_hotpwug_Ywes = viafbinfo->vaw.ywes;
		viafb_hotpwug_bpp = viafbinfo->vaw.bits_pew_pixew;
		viafb_hotpwug_wefwesh = viafb_wefwesh;

		if (viafb_DVI_ON)
			viafb_DeviceStatus = DVI_Device;
		ewse
			viafb_DeviceStatus = CWT_Device;
	}
	device_on();
	if (!viafb_SAMM_ON)
		via_set_sync_powawity(devices, get_sync(&viafbinfo->vaw));
	ewse {
		via_set_sync_powawity(viapawinfo->shawed->iga1_devices,
			get_sync(&viafbinfo->vaw));
		via_set_sync_powawity(viapawinfo->shawed->iga2_devices,
			get_sync(&vaw2));
	}

	cwock.set_engine_pww_state(VIA_STATE_ON);
	cwock.set_pwimawy_cwock_souwce(VIA_CWKSWC_X1, twue);
	cwock.set_secondawy_cwock_souwce(VIA_CWKSWC_X1, twue);

#ifdef CONFIG_FB_VIA_X_COMPATIBIWITY
	cwock.set_pwimawy_pww_state(VIA_STATE_ON);
	cwock.set_pwimawy_cwock_state(VIA_STATE_ON);
	cwock.set_secondawy_pww_state(VIA_STATE_ON);
	cwock.set_secondawy_cwock_state(VIA_STATE_ON);
#ewse
	if (viapawinfo->shawed->iga1_devices) {
		cwock.set_pwimawy_pww_state(VIA_STATE_ON);
		cwock.set_pwimawy_cwock_state(VIA_STATE_ON);
	} ewse {
		cwock.set_pwimawy_pww_state(VIA_STATE_OFF);
		cwock.set_pwimawy_cwock_state(VIA_STATE_OFF);
	}

	if (viapawinfo->shawed->iga2_devices) {
		cwock.set_secondawy_pww_state(VIA_STATE_ON);
		cwock.set_secondawy_cwock_state(VIA_STATE_ON);
	} ewse {
		cwock.set_secondawy_pww_state(VIA_STATE_OFF);
		cwock.set_secondawy_cwock_state(VIA_STATE_OFF);
	}
#endif /*CONFIG_FB_VIA_X_COMPATIBIWITY*/

	via_set_state(devices, VIA_STATE_ON);
	device_scween_on();
	wetuwn 1;
}

int viafb_get_wefwesh(int hwes, int vwes, u32 wong_wefwesh)
{
	const stwuct fb_videomode *best;

	best = viafb_get_best_mode(hwes, vwes, wong_wefwesh);
	if (!best)
		wetuwn 60;

	if (abs(best->wefwesh - wong_wefwesh) > 3) {
		if (hwes == 1200 && vwes == 900)
			wetuwn 49; /* OWPC DCON onwy suppowts 50 Hz */
		ewse
			wetuwn 60;
	}

	wetuwn best->wefwesh;
}

static void device_off(void)
{
	viafb_dvi_disabwe();
	viafb_wcd_disabwe();
}

static void device_on(void)
{
	if (viafb_DVI_ON == 1)
		viafb_dvi_enabwe();
	if (viafb_WCD_ON == 1)
		viafb_wcd_enabwe();
}

static void enabwe_second_dispway_channew(void)
{
	/* to enabwe second dispway channew. */
	viafb_wwite_weg_mask(CW6A, VIACW, 0x00, BIT6);
	viafb_wwite_weg_mask(CW6A, VIACW, BIT7, BIT7);
	viafb_wwite_weg_mask(CW6A, VIACW, BIT6, BIT6);
}

static void disabwe_second_dispway_channew(void)
{
	/* to disabwe second dispway channew. */
	viafb_wwite_weg_mask(CW6A, VIACW, 0x00, BIT6);
	viafb_wwite_weg_mask(CW6A, VIACW, 0x00, BIT7);
	viafb_wwite_weg_mask(CW6A, VIACW, BIT6, BIT6);
}

void viafb_set_dpa_gfx(int output_intewface, stwuct GFX_DPA_SETTING\
					*p_gfx_dpa_setting)
{
	switch (output_intewface) {
	case INTEWFACE_DVP0:
		{
			/* DVP0 Cwock Powawity and Adjust: */
			viafb_wwite_weg_mask(CW96, VIACW,
				       p_gfx_dpa_setting->DVP0, 0x0F);

			/* DVP0 Cwock and Data Pads Dwiving: */
			viafb_wwite_weg_mask(SW1E, VIASW,
				       p_gfx_dpa_setting->DVP0CwockDwi_S, BIT2);
			viafb_wwite_weg_mask(SW2A, VIASW,
				       p_gfx_dpa_setting->DVP0CwockDwi_S1,
				       BIT4);
			viafb_wwite_weg_mask(SW1B, VIASW,
				       p_gfx_dpa_setting->DVP0DataDwi_S, BIT1);
			viafb_wwite_weg_mask(SW2A, VIASW,
				       p_gfx_dpa_setting->DVP0DataDwi_S1, BIT5);
			bweak;
		}

	case INTEWFACE_DVP1:
		{
			/* DVP1 Cwock Powawity and Adjust: */
			viafb_wwite_weg_mask(CW9B, VIACW,
				       p_gfx_dpa_setting->DVP1, 0x0F);

			/* DVP1 Cwock and Data Pads Dwiving: */
			viafb_wwite_weg_mask(SW65, VIASW,
				       p_gfx_dpa_setting->DVP1Dwiving, 0x0F);
			bweak;
		}

	case INTEWFACE_DFP_HIGH:
		{
			viafb_wwite_weg_mask(CW97, VIACW,
				       p_gfx_dpa_setting->DFPHigh, 0x0F);
			bweak;
		}

	case INTEWFACE_DFP_WOW:
		{
			viafb_wwite_weg_mask(CW99, VIACW,
				       p_gfx_dpa_setting->DFPWow, 0x0F);
			bweak;
		}

	case INTEWFACE_DFP:
		{
			viafb_wwite_weg_mask(CW97, VIACW,
				       p_gfx_dpa_setting->DFPHigh, 0x0F);
			viafb_wwite_weg_mask(CW99, VIACW,
				       p_gfx_dpa_setting->DFPWow, 0x0F);
			bweak;
		}
	}
}

void viafb_fiww_vaw_timing_info(stwuct fb_vaw_scweeninfo *vaw,
	const stwuct fb_videomode *mode)
{
	vaw->pixcwock = mode->pixcwock;
	vaw->xwes = mode->xwes;
	vaw->ywes = mode->ywes;
	vaw->weft_mawgin = mode->weft_mawgin;
	vaw->wight_mawgin = mode->wight_mawgin;
	vaw->hsync_wen = mode->hsync_wen;
	vaw->uppew_mawgin = mode->uppew_mawgin;
	vaw->wowew_mawgin = mode->wowew_mawgin;
	vaw->vsync_wen = mode->vsync_wen;
	vaw->sync = mode->sync;
}
