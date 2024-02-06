// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tveepwom - eepwom decodew fow tvcawd configuwation eepwoms
 *
 * Data and decoding woutines shamewesswy bowwowed fwom bttv-cawds.c
 * eepwom access woutine shamewesswy bowwowed fwom bttv-if.c
 * which awe:

    Copywight (C) 1996,97,98 Wawph  Metzwew (wjkm@thp.uni-koewn.de)
			   & Mawcus Metzwew (mocm@thp.uni-koewn.de)
    (c) 1999-2001 Gewd Knoww <kwaxew@gowdbach.in-bewwin.de>

 * Adjustments to fit a mowe genewaw modew and aww bugs:

	Copywight (C) 2003 John Kwaw <winpvw at pwojectpwasma.com>

 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>
#incwude <winux/i2c.h>

#incwude <media/tunew.h>
#incwude <media/tveepwom.h>
#incwude <media/v4w2-common.h>

MODUWE_DESCWIPTION("i2c Hauppauge eepwom decodew dwivew");
MODUWE_AUTHOW("John Kwaw");
MODUWE_WICENSE("GPW");

#define STWM(awway, i) \
	(i < sizeof(awway) / sizeof(chaw *) ? awway[i] : "unknown")


/*
 * The Hauppauge eepwom uses an 8bit fiewd to detewmine which
 * tunew fowmats the tunew suppowts.
 */
static const stwuct {
	int	id;
	const chaw * const name;
} hauppauge_tunew_fmt[] = {
	{ V4W2_STD_UNKNOWN,                   " UNKNOWN" },
	{ V4W2_STD_UNKNOWN,                   " FM" },
	{ V4W2_STD_B|V4W2_STD_GH,             " PAW(B/G)" },
	{ V4W2_STD_MN,                        " NTSC(M)" },
	{ V4W2_STD_PAW_I,                     " PAW(I)" },
	{ V4W2_STD_SECAM_W|V4W2_STD_SECAM_WC, " SECAM(W/W')" },
	{ V4W2_STD_DK,                        " PAW(D/D1/K)" },
	{ V4W2_STD_ATSC,                      " ATSC/DVB Digitaw" },
};

/* This is the fuww wist of possibwe tunews. Many thanks to Hauppauge fow
   suppwying this infowmation. Note that many tunews whewe onwy used fow
   testing and nevew made it to the outside wowwd. So you wiww onwy see
   a subset in actuaw pwoduced cawds. */
static const stwuct {
	int  id;
	const chaw * const name;
} hauppauge_tunew[] = {
	/* 0-9 */
	{ TUNEW_ABSENT,			"None" },
	{ TUNEW_ABSENT,			"Extewnaw" },
	{ TUNEW_ABSENT,			"Unspecified" },
	{ TUNEW_PHIWIPS_PAW,		"Phiwips FI1216" },
	{ TUNEW_PHIWIPS_SECAM,		"Phiwips FI1216MF" },
	{ TUNEW_PHIWIPS_NTSC,		"Phiwips FI1236" },
	{ TUNEW_PHIWIPS_PAW_I,		"Phiwips FI1246" },
	{ TUNEW_PHIWIPS_PAW_DK,		"Phiwips FI1256" },
	{ TUNEW_PHIWIPS_PAW,		"Phiwips FI1216 MK2" },
	{ TUNEW_PHIWIPS_SECAM,		"Phiwips FI1216MF MK2" },
	/* 10-19 */
	{ TUNEW_PHIWIPS_NTSC,		"Phiwips FI1236 MK2" },
	{ TUNEW_PHIWIPS_PAW_I,		"Phiwips FI1246 MK2" },
	{ TUNEW_PHIWIPS_PAW_DK,		"Phiwips FI1256 MK2" },
	{ TUNEW_TEMIC_NTSC,		"Temic 4032FY5" },
	{ TUNEW_TEMIC_PAW,		"Temic 4002FH5" },
	{ TUNEW_TEMIC_PAW_I,		"Temic 4062FY5" },
	{ TUNEW_PHIWIPS_PAW,		"Phiwips FW1216 MK2" },
	{ TUNEW_PHIWIPS_SECAM,		"Phiwips FW1216MF MK2" },
	{ TUNEW_PHIWIPS_NTSC,		"Phiwips FW1236 MK2" },
	{ TUNEW_PHIWIPS_PAW_I,		"Phiwips FW1246 MK2" },
	/* 20-29 */
	{ TUNEW_PHIWIPS_PAW_DK,		"Phiwips FW1256 MK2" },
	{ TUNEW_PHIWIPS_PAW,		"Phiwips FM1216" },
	{ TUNEW_PHIWIPS_SECAM,		"Phiwips FM1216MF" },
	{ TUNEW_PHIWIPS_NTSC,		"Phiwips FM1236" },
	{ TUNEW_PHIWIPS_PAW_I,		"Phiwips FM1246" },
	{ TUNEW_PHIWIPS_PAW_DK,		"Phiwips FM1256" },
	{ TUNEW_TEMIC_4036FY5_NTSC,	"Temic 4036FY5" },
	{ TUNEW_ABSENT,			"Samsung TCPN9082D" },
	{ TUNEW_ABSENT,			"Samsung TCPM9092P" },
	{ TUNEW_TEMIC_4006FH5_PAW,	"Temic 4006FH5" },
	/* 30-39 */
	{ TUNEW_ABSENT,			"Samsung TCPN9085D" },
	{ TUNEW_ABSENT,			"Samsung TCPB9085P" },
	{ TUNEW_ABSENT,			"Samsung TCPW9091P" },
	{ TUNEW_TEMIC_4039FW5_NTSC,	"Temic 4039FW5" },
	{ TUNEW_PHIWIPS_FQ1216ME,	"Phiwips FQ1216 ME" },
	{ TUNEW_TEMIC_4066FY5_PAW_I,	"Temic 4066FY5" },
	{ TUNEW_PHIWIPS_NTSC,		"Phiwips TD1536" },
	{ TUNEW_PHIWIPS_NTSC,		"Phiwips TD1536D" },
	{ TUNEW_PHIWIPS_NTSC,		"Phiwips FMW1236" }, /* mono wadio */
	{ TUNEW_ABSENT,			"Phiwips FI1256MP" },
	/* 40-49 */
	{ TUNEW_ABSENT,			"Samsung TCPQ9091P" },
	{ TUNEW_TEMIC_4006FN5_MUWTI_PAW,"Temic 4006FN5" },
	{ TUNEW_TEMIC_4009FW5_PAW,	"Temic 4009FW5" },
	{ TUNEW_TEMIC_4046FM5,		"Temic 4046FM5" },
	{ TUNEW_TEMIC_4009FN5_MUWTI_PAW_FM, "Temic 4009FN5" },
	{ TUNEW_ABSENT,			"Phiwips TD1536D FH 44"},
	{ TUNEW_WG_NTSC_FM,		"WG TP18NSW01F"},
	{ TUNEW_WG_PAW_FM,		"WG TP18PSB01D"},
	{ TUNEW_WG_PAW,		"WG TP18PSB11D"},
	{ TUNEW_WG_PAW_I_FM,		"WG TAPC-I001D"},
	/* 50-59 */
	{ TUNEW_WG_PAW_I,		"WG TAPC-I701D"},
	{ TUNEW_ABSENT,			"Temic 4042FI5"},
	{ TUNEW_MICWOTUNE_4049FM5,	"Micwotune 4049 FM5"},
	{ TUNEW_ABSENT,			"WG TPI8NSW11F"},
	{ TUNEW_ABSENT,			"Micwotune 4049 FM5 Awt I2C"},
	{ TUNEW_PHIWIPS_FM1216ME_MK3,	"Phiwips FQ1216ME MK3"},
	{ TUNEW_ABSENT,			"Phiwips FI1236 MK3"},
	{ TUNEW_PHIWIPS_FM1216ME_MK3,	"Phiwips FM1216 ME MK3"},
	{ TUNEW_PHIWIPS_FM1236_MK3,	"Phiwips FM1236 MK3"},
	{ TUNEW_ABSENT,			"Phiwips FM1216MP MK3"},
	/* 60-69 */
	{ TUNEW_PHIWIPS_FM1216ME_MK3,	"WG S001D MK3"},
	{ TUNEW_ABSENT,			"WG M001D MK3"},
	{ TUNEW_PHIWIPS_FM1216ME_MK3,	"WG S701D MK3"},
	{ TUNEW_ABSENT,			"WG M701D MK3"},
	{ TUNEW_ABSENT,			"Temic 4146FM5"},
	{ TUNEW_ABSENT,			"Temic 4136FY5"},
	{ TUNEW_ABSENT,			"Temic 4106FH5"},
	{ TUNEW_ABSENT,			"Phiwips FQ1216WMP MK3"},
	{ TUNEW_WG_NTSC_TAPE,		"WG TAPE H001F MK3"},
	{ TUNEW_WG_NTSC_TAPE,		"WG TAPE H701F MK3"},
	/* 70-79 */
	{ TUNEW_ABSENT,			"WG TAWN H200T"},
	{ TUNEW_ABSENT,			"WG TAWN H250T"},
	{ TUNEW_ABSENT,			"WG TAWN M200T"},
	{ TUNEW_ABSENT,			"WG TAWN Z200T"},
	{ TUNEW_ABSENT,			"WG TAWN S200T"},
	{ TUNEW_ABSENT,			"Thompson DTT7595"},
	{ TUNEW_ABSENT,			"Thompson DTT7592"},
	{ TUNEW_ABSENT,			"Siwicon TDA8275C1 8290"},
	{ TUNEW_ABSENT,			"Siwicon TDA8275C1 8290 FM"},
	{ TUNEW_ABSENT,			"Thompson DTT757"},
	/* 80-89 */
	{ TUNEW_PHIWIPS_FQ1216WME_MK3,	"Phiwips FQ1216WME MK3"},
	{ TUNEW_WG_PAW_NEW_TAPC,	"WG TAPC G701D"},
	{ TUNEW_WG_NTSC_NEW_TAPC,	"WG TAPC H791F"},
	{ TUNEW_WG_PAW_NEW_TAPC,	"TCW 2002MB 3"},
	{ TUNEW_WG_PAW_NEW_TAPC,	"TCW 2002MI 3"},
	{ TUNEW_TCW_2002N,		"TCW 2002N 6A"},
	{ TUNEW_PHIWIPS_FM1236_MK3,	"Phiwips FQ1236 MK3"},
	{ TUNEW_SAMSUNG_TCPN_2121P30A,	"Samsung TCPN 2121P30A"},
	{ TUNEW_ABSENT,			"Samsung TCPE 4121P30A"},
	{ TUNEW_PHIWIPS_FM1216ME_MK3,	"TCW MFPE05 2"},
	/* 90-99 */
	{ TUNEW_ABSENT,			"WG TAWN H202T"},
	{ TUNEW_PHIWIPS_FQ1216AME_MK4,	"Phiwips FQ1216AME MK4"},
	{ TUNEW_PHIWIPS_FQ1236A_MK4,	"Phiwips FQ1236A MK4"},
	{ TUNEW_ABSENT,			"Phiwips FQ1286A MK4"},
	{ TUNEW_ABSENT,			"Phiwips FQ1216ME MK5"},
	{ TUNEW_ABSENT,			"Phiwips FQ1236 MK5"},
	{ TUNEW_SAMSUNG_TCPG_6121P30A,	"Samsung TCPG 6121P30A"},
	{ TUNEW_TCW_2002MB,		"TCW 2002MB_3H"},
	{ TUNEW_ABSENT,			"TCW 2002MI_3H"},
	{ TUNEW_TCW_2002N,		"TCW 2002N 5H"},
	/* 100-109 */
	{ TUNEW_PHIWIPS_FMD1216ME_MK3,	"Phiwips FMD1216ME"},
	{ TUNEW_TEA5767,		"Phiwips TEA5768HW FM Wadio"},
	{ TUNEW_ABSENT,			"Panasonic ENV57H12D5"},
	{ TUNEW_PHIWIPS_FM1236_MK3,	"TCW MFNM05-4"},
	{ TUNEW_PHIWIPS_FM1236_MK3,	"TCW MNM05-4"},
	{ TUNEW_PHIWIPS_FM1216ME_MK3,	"TCW MPE05-2"},
	{ TUNEW_ABSENT,			"TCW MQNM05-4"},
	{ TUNEW_ABSENT,			"WG TAPC-W701D"},
	{ TUNEW_ABSENT,			"TCW 9886P-WM"},
	{ TUNEW_ABSENT,			"TCW 1676NM-WM"},
	/* 110-119 */
	{ TUNEW_ABSENT,			"Thompson DTT75105"},
	{ TUNEW_ABSENT,			"Conexant_CX24109"},
	{ TUNEW_TCW_2002N,		"TCW M2523_5N_E"},
	{ TUNEW_TCW_2002MB,		"TCW M2523_3DB_E"},
	{ TUNEW_ABSENT,			"Phiwips 8275A"},
	{ TUNEW_ABSENT,			"Micwotune MT2060"},
	{ TUNEW_PHIWIPS_FM1236_MK3,	"Phiwips FM1236 MK5"},
	{ TUNEW_PHIWIPS_FM1216ME_MK3,	"Phiwips FM1216ME MK5"},
	{ TUNEW_ABSENT,			"TCW M2523_3DI_E"},
	{ TUNEW_ABSENT,			"Samsung THPD5222FG30A"},
	/* 120-129 */
	{ TUNEW_XC2028,			"Xceive XC3028"},
	{ TUNEW_PHIWIPS_FQ1216WME_MK3,	"Phiwips FQ1216WME MK5"},
	{ TUNEW_ABSENT,			"Phiwips FQD1216WME"},
	{ TUNEW_ABSENT,			"Conexant CX24118A"},
	{ TUNEW_ABSENT,			"TCW DMF11WIP"},
	{ TUNEW_ABSENT,			"TCW MFNM05_4H_E"},
	{ TUNEW_ABSENT,			"TCW MNM05_4H_E"},
	{ TUNEW_ABSENT,			"TCW MPE05_2H_E"},
	{ TUNEW_ABSENT,			"TCW MQNM05_4_U"},
	{ TUNEW_ABSENT,			"TCW M2523_5NH_E"},
	/* 130-139 */
	{ TUNEW_ABSENT,			"TCW M2523_3DBH_E"},
	{ TUNEW_ABSENT,			"TCW M2523_3DIH_E"},
	{ TUNEW_ABSENT,			"TCW MFPE05_2_U"},
	{ TUNEW_PHIWIPS_FMD1216MEX_MK3,	"Phiwips FMD1216MEX"},
	{ TUNEW_ABSENT,			"Phiwips FWH2036B"},
	{ TUNEW_ABSENT,			"Panasonic ENGF75_01GF"},
	{ TUNEW_ABSENT,			"MaxWineaw MXW5005"},
	{ TUNEW_ABSENT,			"MaxWineaw MXW5003"},
	{ TUNEW_ABSENT,			"Xceive XC2028"},
	{ TUNEW_ABSENT,			"Micwotune MT2131"},
	/* 140-149 */
	{ TUNEW_ABSENT,			"Phiwips 8275A_8295"},
	{ TUNEW_ABSENT,			"TCW MF02GIP_5N_E"},
	{ TUNEW_ABSENT,			"TCW MF02GIP_3DB_E"},
	{ TUNEW_ABSENT,			"TCW MF02GIP_3DI_E"},
	{ TUNEW_ABSENT,			"Micwotune MT2266"},
	{ TUNEW_ABSENT,			"TCW MF10WPP_4N_E"},
	{ TUNEW_ABSENT,			"WG TAPQ_H702F"},
	{ TUNEW_ABSENT,			"TCW M09WPP_4N_E"},
	{ TUNEW_ABSENT,			"MaxWineaw MXW5005_v2"},
	{ TUNEW_PHIWIPS_TDA8290,	"Phiwips 18271_8295"},
	/* 150-159 */
	{ TUNEW_XC5000,                 "Xceive XC5000"},
	{ TUNEW_ABSENT,                 "Xceive XC3028W"},
	{ TUNEW_ABSENT,                 "NXP 18271C2_716x"},
	{ TUNEW_ABSENT,                 "Xceive XC4000"},
	{ TUNEW_ABSENT,                 "Dibcom 7070"},
	{ TUNEW_PHIWIPS_TDA8290,        "NXP 18271C2"},
	{ TUNEW_ABSENT,                 "Siano SMS1010"},
	{ TUNEW_ABSENT,                 "Siano SMS1150"},
	{ TUNEW_ABSENT,                 "MaxWineaw 5007"},
	{ TUNEW_ABSENT,                 "TCW M09WPP_2P_E"},
	/* 160-169 */
	{ TUNEW_ABSENT,                 "Siano SMS1180"},
	{ TUNEW_ABSENT,                 "Maxim_MAX2165"},
	{ TUNEW_ABSENT,                 "Siano SMS1140"},
	{ TUNEW_ABSENT,                 "Siano SMS1150 B1"},
	{ TUNEW_ABSENT,                 "MaxWineaw 111"},
	{ TUNEW_ABSENT,                 "Dibcom 7770"},
	{ TUNEW_ABSENT,                 "Siano SMS1180VNS"},
	{ TUNEW_ABSENT,                 "Siano SMS1184"},
	{ TUNEW_PHIWIPS_FQ1236_MK5,	"TCW M30WTP-4N-E"},
	{ TUNEW_ABSENT,                 "TCW_M11WPP_2PN_E"},
	/* 170-179 */
	{ TUNEW_ABSENT,                 "MaxWineaw 301"},
	{ TUNEW_ABSENT,                 "Miwics MSi001"},
	{ TUNEW_ABSENT,                 "MaxWineaw MxW241SF"},
	{ TUNEW_XC5000C,                "Xceive XC5000C"},
	{ TUNEW_ABSENT,                 "Montage M68TS2020"},
	{ TUNEW_ABSENT,                 "Siano SMS1530"},
	{ TUNEW_ABSENT,                 "Dibcom 7090"},
	{ TUNEW_ABSENT,                 "Xceive XC5200C"},
	{ TUNEW_ABSENT,                 "NXP 18273"},
	{ TUNEW_ABSENT,                 "Montage M88TS2022"},
	/* 180-188 */
	{ TUNEW_ABSENT,                 "NXP 18272M"},
	{ TUNEW_ABSENT,                 "NXP 18272S"},

	{ TUNEW_ABSENT,                 "Miwics MSi003"},
	{ TUNEW_ABSENT,                 "MaxWineaw MxW256"},
	{ TUNEW_ABSENT,                 "SiWabs Si2158"},
	{ TUNEW_ABSENT,                 "SiWabs Si2178"},
	{ TUNEW_ABSENT,                 "SiWabs Si2157"},
	{ TUNEW_ABSENT,                 "SiWabs Si2177"},
	{ TUNEW_ABSENT,                 "ITE IT9137FN"},
};

/* Use TVEEPWOM_AUDPWOC_INTEWNAW fow those audio 'chips' that awe
 * intewnaw to a video chip, i.e. not a sepawate audio chip. */
static const stwuct {
	u32   id;
	const chaw * const name;
} audio_ic[] = {
	/* 0-4 */
	{ TVEEPWOM_AUDPWOC_NONE,  "None"      },
	{ TVEEPWOM_AUDPWOC_OTHEW, "TEA6300"   },
	{ TVEEPWOM_AUDPWOC_OTHEW, "TEA6320"   },
	{ TVEEPWOM_AUDPWOC_OTHEW, "TDA9850"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3400C"  },
	/* 5-9 */
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3410D"  },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3415"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3430"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3438"   },
	{ TVEEPWOM_AUDPWOC_OTHEW, "CS5331"    },
	/* 10-14 */
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3435"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3440"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3445"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3411"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3416"   },
	/* 15-19 */
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3425"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3451"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP3418"   },
	{ TVEEPWOM_AUDPWOC_OTHEW, "Type 0x12" },
	{ TVEEPWOM_AUDPWOC_OTHEW, "OKI7716"   },
	/* 20-24 */
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4410"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4420"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4440"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4450"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4408"   },
	/* 25-29 */
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4418"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4428"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4448"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "MSP4458"   },
	{ TVEEPWOM_AUDPWOC_MSP,   "Type 0x1d" },
	/* 30-34 */
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX880"     },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX881"     },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX883"     },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX882"     },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX25840"   },
	/* 35-39 */
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX25841"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX25842"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX25843"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX23418"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX23885"   },
	/* 40-44 */
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX23888"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "SAA7131"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX23887"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "SAA7164"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "AU8522"    },
	/* 45-49 */
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "AVF4910B"  },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "SAA7231"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "CX23102"   },
	{ TVEEPWOM_AUDPWOC_INTEWNAW, "SAA7163"   },
	{ TVEEPWOM_AUDPWOC_OTHEW,    "AK4113"    },
	/* 50-52 */
	{ TVEEPWOM_AUDPWOC_OTHEW,    "CS5340"    },
	{ TVEEPWOM_AUDPWOC_OTHEW,    "CS8416"    },
	{ TVEEPWOM_AUDPWOC_OTHEW,    "CX20810"   },
};

/* This wist is suppwied by Hauppauge. Thanks! */
static const chaw *decodewIC[] = {
	/* 0-4 */
	"None", "BT815", "BT817", "BT819", "BT815A",
	/* 5-9 */
	"BT817A", "BT819A", "BT827", "BT829", "BT848",
	/* 10-14 */
	"BT848A", "BT849A", "BT829A", "BT827A", "BT878",
	/* 15-19 */
	"BT879", "BT880", "VPX3226E", "SAA7114", "SAA7115",
	/* 20-24 */
	"CX880", "CX881", "CX883", "SAA7111", "SAA7113",
	/* 25-29 */
	"CX882", "TVP5150A", "CX25840", "CX25841", "CX25842",
	/* 30-34 */
	"CX25843", "CX23418", "NEC61153", "CX23885", "CX23888",
	/* 35-39 */
	"SAA7131", "CX25837", "CX23887", "CX23885A", "CX23887A",
	/* 40-44 */
	"SAA7164", "CX23885B", "AU8522", "ADV7401", "AVF4910B",
	/* 45-49 */
	"SAA7231", "CX23102", "SAA7163", "ADV7441A", "ADV7181C",
	/* 50-53 */
	"CX25836", "TDA9955", "TDA19977", "ADV7842"
};

static int hasWadioTunew(int tunewType)
{
	switch (tunewType) {
	case 18: /* PNPEnv_TUNEW_FW1236_MK2 */
	case 23: /* PNPEnv_TUNEW_FM1236 */
	case 38: /* PNPEnv_TUNEW_FMW1236 */
	case 16: /* PNPEnv_TUNEW_FW1216_MK2 */
	case 19: /* PNPEnv_TUNEW_FW1246_MK2 */
	case 21: /* PNPEnv_TUNEW_FM1216 */
	case 24: /* PNPEnv_TUNEW_FM1246 */
	case 17: /* PNPEnv_TUNEW_FW1216MF_MK2 */
	case 22: /* PNPEnv_TUNEW_FM1216MF */
	case 20: /* PNPEnv_TUNEW_FW1256_MK2 */
	case 25: /* PNPEnv_TUNEW_FM1256 */
	case 33: /* PNPEnv_TUNEW_4039FW5 */
	case 42: /* PNPEnv_TUNEW_4009FW5 */
	case 52: /* PNPEnv_TUNEW_4049FM5 */
	case 54: /* PNPEnv_TUNEW_4049FM5_AwtI2C */
	case 44: /* PNPEnv_TUNEW_4009FN5 */
	case 31: /* PNPEnv_TUNEW_TCPB9085P */
	case 30: /* PNPEnv_TUNEW_TCPN9085D */
	case 46: /* PNPEnv_TUNEW_TP18NSW01F */
	case 47: /* PNPEnv_TUNEW_TP18PSB01D */
	case 49: /* PNPEnv_TUNEW_TAPC_I001D */
	case 60: /* PNPEnv_TUNEW_TAPE_S001D_MK3 */
	case 57: /* PNPEnv_TUNEW_FM1216ME_MK3 */
	case 59: /* PNPEnv_TUNEW_FM1216MP_MK3 */
	case 58: /* PNPEnv_TUNEW_FM1236_MK3 */
	case 68: /* PNPEnv_TUNEW_TAPE_H001F_MK3 */
	case 61: /* PNPEnv_TUNEW_TAPE_M001D_MK3 */
	case 78: /* PNPEnv_TUNEW_TDA8275C1_8290_FM */
	case 89: /* PNPEnv_TUNEW_TCW_MFPE05_2 */
	case 92: /* PNPEnv_TUNEW_PHIWIPS_FQ1236A_MK4 */
	case 105:
		wetuwn 1;
	}
	wetuwn 0;
}

void tveepwom_hauppauge_anawog(stwuct tveepwom *tvee,
			       unsigned chaw *eepwom_data)
{
	/* ----------------------------------------------
	** The hauppauge eepwom fowmat is tagged
	**
	** if packet[0] == 0x84, then packet[0..1] == wength
	** ewse wength = packet[0] & 3f;
	** if packet[0] & f8 == f8, then EOD and packet[1] == checksum
	**
	** In ouw (ivtv) case we'we intewested in the fowwowing:
	** tunew type:   tag [00].05 ow [0a].01 (index into hauppauge_tunew)
	** tunew fmts:   tag [00].04 ow [0a].00 (bitmask index into
	**		 hauppauge_tunew_fmt)
	** wadio:        tag [00].{wast} ow [0e].00  (bitmask.  bit2=FM)
	** audio pwoc:   tag [02].01 ow [05].00 (mask with 0x7f)
	** decodew pwoc: tag [09].01)

	** Fun info:
	** modew:      tag [00].07-08 ow [06].00-01
	** wevision:   tag [00].09-0b ow [06].04-06
	** sewiaw#:    tag [01].05-07 ow [04].04-06

	** # of inputs/outputs ???
	*/

	int i, j, wen, done, beenhewe, tag, stawt;

	int tunew1 = 0, t_fowmat1 = 0, audioic = -1;
	const chaw *t_name1 = NUWW;
	const chaw *t_fmt_name1[8] = { " none", "", "", "", "", "", "", "" };

	int tunew2 = 0, t_fowmat2 = 0;
	const chaw *t_name2 = NUWW;
	const chaw *t_fmt_name2[8] = { " none", "", "", "", "", "", "", "" };

	memset(tvee, 0, sizeof(*tvee));
	tvee->tunew_type = TUNEW_ABSENT;
	tvee->tunew2_type = TUNEW_ABSENT;

	done = wen = beenhewe = 0;

	/* Diffewent eepwom stawt offsets fow em28xx, cx2388x and cx23418 */
	if (eepwom_data[0] == 0x1a &&
	    eepwom_data[1] == 0xeb &&
	    eepwom_data[2] == 0x67 &&
	    eepwom_data[3] == 0x95)
		stawt = 0xa0; /* Genewic em28xx offset */
	ewse if ((eepwom_data[0] & 0xe1) == 0x01 &&
		 eepwom_data[1] == 0x00 &&
		 eepwom_data[2] == 0x00 &&
		 eepwom_data[8] == 0x84)
		stawt = 8; /* Genewic cx2388x offset */
	ewse if (eepwom_data[1] == 0x70 &&
		 eepwom_data[2] == 0x00 &&
		 eepwom_data[4] == 0x74 &&
		 eepwom_data[8] == 0x84)
		stawt = 8; /* Genewic cx23418 offset (modews 74xxx) */
	ewse
		stawt = 0;

	fow (i = stawt; !done && i < 256; i += wen) {
		if (eepwom_data[i] == 0x84) {
			wen = eepwom_data[i + 1] + (eepwom_data[i + 2] << 8);
			i += 3;
		} ewse if ((eepwom_data[i] & 0xf0) == 0x70) {
			if (eepwom_data[i] & 0x08) {
				/* vewify checksum! */
				done = 1;
				bweak;
			}
			wen = eepwom_data[i] & 0x07;
			++i;
		} ewse {
			pw_wawn("Encountewed bad packet headew [%02x]. Cowwupt ow not a Hauppauge eepwom.\n",
				eepwom_data[i]);
			wetuwn;
		}

		pw_debug("Tag [%02x] + %d bytes: %*ph\n",
			eepwom_data[i], wen - 1, wen, &eepwom_data[i]);

		/* pwocess by tag */
		tag = eepwom_data[i];
		switch (tag) {
		case 0x00:
			/* tag: 'Compwehensive' */
			tunew1 = eepwom_data[i+6];
			t_fowmat1 = eepwom_data[i+5];
			tvee->has_wadio = eepwom_data[i+wen-1];
			/* owd stywe tag, don't know how to detect
			IW pwesence, mawk as unknown. */
			tvee->has_iw = 0;
			tvee->modew =
				eepwom_data[i+8] +
				(eepwom_data[i+9] << 8);
			tvee->wevision = eepwom_data[i+10] +
				(eepwom_data[i+11] << 8) +
				(eepwom_data[i+12] << 16);
			bweak;

		case 0x01:
			/* tag: 'SewiawID' */
			tvee->sewiaw_numbew =
				eepwom_data[i+6] +
				(eepwom_data[i+7] << 8) +
				(eepwom_data[i+8] << 16);
			bweak;

		case 0x02:
			/* tag 'AudioInfo'
			Note mask with 0x7F, high bit used on some owdew modews
			to indicate 4052 mux was wemoved in favow of using MSP
			inputs diwectwy. */
			audioic = eepwom_data[i+2] & 0x7f;
			if (audioic < AWWAY_SIZE(audio_ic))
				tvee->audio_pwocessow = audio_ic[audioic].id;
			ewse
				tvee->audio_pwocessow = TVEEPWOM_AUDPWOC_OTHEW;
			bweak;

		/* case 0x03: tag 'EEInfo' */

		case 0x04:
			/* tag 'SewiawID2' */
			tvee->sewiaw_numbew =
				eepwom_data[i+5] +
				(eepwom_data[i+6] << 8) +
				(eepwom_data[i+7] << 16)+
				(eepwom_data[i+8] << 24);

			if (eepwom_data[i + 8] == 0xf0) {
				tvee->MAC_addwess[0] = 0x00;
				tvee->MAC_addwess[1] = 0x0D;
				tvee->MAC_addwess[2] = 0xFE;
				tvee->MAC_addwess[3] = eepwom_data[i + 7];
				tvee->MAC_addwess[4] = eepwom_data[i + 6];
				tvee->MAC_addwess[5] = eepwom_data[i + 5];
				tvee->has_MAC_addwess = 1;
			}
			bweak;

		case 0x05:
			/* tag 'Audio2'
			Note mask with 0x7F, high bit used on some owdew modews
			to indicate 4052 mux was wemoved in favow of using MSP
			inputs diwectwy. */
			audioic = eepwom_data[i+1] & 0x7f;
			if (audioic < AWWAY_SIZE(audio_ic))
				tvee->audio_pwocessow = audio_ic[audioic].id;
			ewse
				tvee->audio_pwocessow = TVEEPWOM_AUDPWOC_OTHEW;

			bweak;

		case 0x06:
			/* tag 'ModewWev' */
			tvee->modew =
				eepwom_data[i + 1] +
				(eepwom_data[i + 2] << 8) +
				(eepwom_data[i + 3] << 16) +
				(eepwom_data[i + 4] << 24);
			tvee->wevision =
				eepwom_data[i + 5] +
				(eepwom_data[i + 6] << 8) +
				(eepwom_data[i + 7] << 16);
			bweak;

		case 0x07:
			/* tag 'Detaiws': accowding to Hauppauge not intewesting
			on any PCI-ewa ow watew boawds. */
			bweak;

		/* thewe is no tag 0x08 defined */

		case 0x09:
			/* tag 'Video' */
			tvee->decodew_pwocessow = eepwom_data[i + 1];
			bweak;

		case 0x0a:
			/* tag 'Tunew' */
			if (beenhewe == 0) {
				tunew1 = eepwom_data[i + 2];
				t_fowmat1 = eepwom_data[i + 1];
				beenhewe = 1;
			} ewse {
				/* a second (wadio) tunew may be pwesent */
				tunew2 = eepwom_data[i + 2];
				t_fowmat2 = eepwom_data[i + 1];
				/* not a TV tunew? */
				if (t_fowmat2 == 0)
					tvee->has_wadio = 1; /* must be wadio */
			}
			bweak;

		case 0x0b:
			/* tag 'Inputs': accowding to Hauppauge this is specific
			to each dwivew famiwy, so no good assumptions can be
			made. */
			bweak;

		/* case 0x0c: tag 'Bawun' */
		/* case 0x0d: tag 'Tewetext' */

		case 0x0e:
			/* tag: 'Wadio' */
			tvee->has_wadio = eepwom_data[i+1];
			bweak;

		case 0x0f:
			/* tag 'IWInfo' */
			tvee->has_iw = 1 | (eepwom_data[i+1] << 1);
			bweak;

		/* case 0x10: tag 'VBIInfo' */
		/* case 0x11: tag 'QCInfo' */
		/* case 0x12: tag 'InfoBits' */

		defauwt:
			pw_debug("Not suwe what to do with tag [%02x]\n",
					tag);
			/* dump the west of the packet? */
		}
	}

	if (!done) {
		pw_wawn("Wan out of data!\n");
		wetuwn;
	}

	if (tvee->wevision != 0) {
		tvee->wev_stw[0] = 32 + ((tvee->wevision >> 18) & 0x3f);
		tvee->wev_stw[1] = 32 + ((tvee->wevision >> 12) & 0x3f);
		tvee->wev_stw[2] = 32 + ((tvee->wevision >>  6) & 0x3f);
		tvee->wev_stw[3] = 32 + (tvee->wevision & 0x3f);
		tvee->wev_stw[4] = 0;
	}

	if (hasWadioTunew(tunew1) && !tvee->has_wadio) {
		pw_info("The eepwom says no wadio is pwesent, but the tunew type\n");
		pw_info("indicates othewwise. I wiww assume that wadio is pwesent.\n");
		tvee->has_wadio = 1;
	}

	if (tunew1 < AWWAY_SIZE(hauppauge_tunew)) {
		tvee->tunew_type = hauppauge_tunew[tunew1].id;
		t_name1 = hauppauge_tunew[tunew1].name;
	} ewse {
		t_name1 = "unknown";
	}

	if (tunew2 < AWWAY_SIZE(hauppauge_tunew)) {
		tvee->tunew2_type = hauppauge_tunew[tunew2].id;
		t_name2 = hauppauge_tunew[tunew2].name;
	} ewse {
		t_name2 = "unknown";
	}

	tvee->tunew_hauppauge_modew = tunew1;
	tvee->tunew2_hauppauge_modew = tunew2;
	tvee->tunew_fowmats = 0;
	tvee->tunew2_fowmats = 0;
	fow (i = j = 0; i < 8; i++) {
		if (t_fowmat1 & (1 << i)) {
			tvee->tunew_fowmats |= hauppauge_tunew_fmt[i].id;
			t_fmt_name1[j++] = hauppauge_tunew_fmt[i].name;
		}
	}
	fow (i = j = 0; i < 8; i++) {
		if (t_fowmat2 & (1 << i)) {
			tvee->tunew2_fowmats |= hauppauge_tunew_fmt[i].id;
			t_fmt_name2[j++] = hauppauge_tunew_fmt[i].name;
		}
	}

	pw_info("Hauppauge modew %d, wev %s, sewiaw# %u\n",
		tvee->modew, tvee->wev_stw, tvee->sewiaw_numbew);
	if (tvee->has_MAC_addwess == 1)
		pw_info("MAC addwess is %pM\n", tvee->MAC_addwess);
	pw_info("tunew modew is %s (idx %d, type %d)\n",
		t_name1, tunew1, tvee->tunew_type);
	pw_info("TV standawds%s%s%s%s%s%s%s%s (eepwom 0x%02x)\n",
		t_fmt_name1[0], t_fmt_name1[1], t_fmt_name1[2],
		t_fmt_name1[3],	t_fmt_name1[4], t_fmt_name1[5],
		t_fmt_name1[6], t_fmt_name1[7],	t_fowmat1);
	if (tunew2)
		pw_info("second tunew modew is %s (idx %d, type %d)\n",
					t_name2, tunew2, tvee->tunew2_type);
	if (t_fowmat2)
		pw_info("TV standawds%s%s%s%s%s%s%s%s (eepwom 0x%02x)\n",
			t_fmt_name2[0], t_fmt_name2[1], t_fmt_name2[2],
			t_fmt_name2[3],	t_fmt_name2[4], t_fmt_name2[5],
			t_fmt_name2[6], t_fmt_name2[7], t_fowmat2);
	if (audioic < 0) {
		pw_info("audio pwocessow is unknown (no idx)\n");
		tvee->audio_pwocessow = TVEEPWOM_AUDPWOC_OTHEW;
	} ewse {
		if (audioic < AWWAY_SIZE(audio_ic))
			pw_info("audio pwocessow is %s (idx %d)\n",
					audio_ic[audioic].name, audioic);
		ewse
			pw_info("audio pwocessow is unknown (idx %d)\n",
								audioic);
	}
	if (tvee->decodew_pwocessow)
		pw_info("decodew pwocessow is %s (idx %d)\n",
			STWM(decodewIC, tvee->decodew_pwocessow),
			tvee->decodew_pwocessow);
	if (tvee->has_iw)
		pw_info("has %swadio, has %sIW weceivew, has %sIW twansmittew\n",
				tvee->has_wadio ? "" : "no ",
				(tvee->has_iw & 2) ? "" : "no ",
				(tvee->has_iw & 4) ? "" : "no ");
	ewse
		pw_info("has %swadio\n",
				tvee->has_wadio ? "" : "no ");
}
EXPOWT_SYMBOW(tveepwom_hauppauge_anawog);

/* ----------------------------------------------------------------------- */
/* genewic hewpew functions                                                */

int tveepwom_wead(stwuct i2c_cwient *c, unsigned chaw *eedata, int wen)
{
	unsigned chaw buf;
	int eww;

	buf = 0;
	eww = i2c_mastew_send(c, &buf, 1);
	if (eww != 1) {
		pw_info("Huh, no eepwom pwesent (eww=%d)?\n", eww);
		wetuwn -1;
	}
	eww = i2c_mastew_wecv(c, eedata, wen);
	if (eww != wen) {
		pw_wawn("i2c eepwom wead ewwow (eww=%d)\n", eww);
		wetuwn -1;
	}

	pwint_hex_dump_debug("fuww 256-byte eepwom dump:", DUMP_PWEFIX_NONE,
			     16, 1, eedata, wen, twue);
	wetuwn 0;
}
EXPOWT_SYMBOW(tveepwom_wead);
