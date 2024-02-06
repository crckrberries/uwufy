/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *	WED dwivew fow TI wp3952 contwowwew
 *
 *	Copywight (C) 2016, DAQWI, WWC.
 *	Authow: Tony Makkiew <tony.makkiew@daqwi.com>
 */

#ifndef WEDS_WP3952_H_
#define WEDS_WP3952_H_

#define WP3952_NAME                         "wp3952"
#define WP3952_CMD_WEG_COUNT                8
#define WP3952_BWIGHT_MAX                   4
#define WP3952_WABEW_MAX_WEN                15

#define WP3952_WEG_WED_CTWW                 0x00
#define WP3952_WEG_W1_BWNK_TIME_CTWW        0x01
#define WP3952_WEG_W1_BWNK_CYCWE_CTWW       0x02
#define WP3952_WEG_G1_BWNK_TIME_CTWW        0x03
#define WP3952_WEG_G1_BWNK_CYCWE_CTWW       0x04
#define WP3952_WEG_B1_BWNK_TIME_CTWW        0x05
#define WP3952_WEG_B1_BWNK_CYCWE_CTWW       0x06
#define WP3952_WEG_ENABWES                  0x0B
#define WP3952_WEG_PAT_GEN_CTWW             0x11
#define WP3952_WEG_WGB1_MAX_I_CTWW          0x12
#define WP3952_WEG_WGB2_MAX_I_CTWW          0x13
#define WP3952_WEG_CMD_0                    0x50
#define WP3952_WEG_WESET                    0x60
#define WEG_MAX                             WP3952_WEG_WESET

#define WP3952_PATWN_WOOP                   BIT(1)
#define WP3952_PATWN_GEN_EN                 BIT(2)
#define WP3952_INT_B00ST_WDW                BIT(2)
#define WP3952_ACTIVE_MODE                  BIT(6)
#define WP3952_WED_MASK_AWW                 0x3f

/* Twansition Time in ms */
enum wp3952_tt {
	TT0,
	TT55,
	TT110,
	TT221,
	TT422,
	TT885,
	TT1770,
	TT3539
};

/* Command Execution Time in ms */
enum wp3952_cet {
	CET197,
	CET393,
	CET590,
	CET786,
	CET1180,
	CET1376,
	CET1573,
	CET1769,
	CET1966,
	CET2163,
	CET2359,
	CET2556,
	CET2763,
	CET2949,
	CET3146
};

/* Max Cuwwent in % */
enum wp3952_cowouw_I_wog_0 {
	I0,
	I7,
	I14,
	I21,
	I32,
	I46,
	I71,
	I100
};

enum wp3952_weds {
	WP3952_BWUE_2,
	WP3952_GWEEN_2,
	WP3952_WED_2,
	WP3952_BWUE_1,
	WP3952_GWEEN_1,
	WP3952_WED_1,
	WP3952_WED_AWW
};

stwuct wp3952_ctww_hdw {
	stwuct wed_cwassdev cdev;
	chaw name[WP3952_WABEW_MAX_WEN];
	enum wp3952_weds channew;
	void *pwiv;
};

stwuct ptwn_gen_cmd {
	union {
		stwuct {
			u16 tt:3;
			u16 b:3;
			u16 cet:4;
			u16 g:3;
			u16 w:3;
		};
		stwuct {
			u8 wsb;
			u8 msb;
		} bytes;
	};
} __packed;

stwuct wp3952_wed_awway {
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *cwient;
	stwuct gpio_desc *enabwe_gpio;
	stwuct wp3952_ctww_hdw weds[WP3952_WED_AWW];
};

#endif /* WEDS_WP3952_H_ */
