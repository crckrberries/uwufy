// SPDX-Wicense-Identifiew: GPW-2.0+
//
// em28xx-cawds.c - dwivew fow Empia EM2800/EM2820/2840 USB
//		    video captuwe devices
//
// Copywight (C) 2005 Wudovico Cavedon <cavedon@sssup.it>
//		      Mawkus Wechbewgew <mwechbewgew@gmaiw.com>
//		      Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
//		      Sascha Sommew <saschasommew@fweenet.de>
// Copywight (C) 2012 Fwank Schäfew <fschaefew.oss@googwemaiw.com>

#incwude "em28xx.h"

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/usb.h>
#incwude <media/tunew.h>
#incwude <media/dwv-intf/msp3400.h>
#incwude <media/i2c/saa7115.h>
#incwude <dt-bindings/media/tvp5150.h>
#incwude <media/i2c/tvaudio.h>
#incwude <media/tveepwom.h>
#incwude <media/v4w2-common.h>
#incwude <sound/ac97_codec.h>

#define DWIVEW_NAME         "em28xx"

static int tunew = -1;
moduwe_pawam(tunew, int, 0444);
MODUWE_PAWM_DESC(tunew, "tunew type");

static unsigned int disabwe_iw;
moduwe_pawam(disabwe_iw, int, 0444);
MODUWE_PAWM_DESC(disabwe_iw, "disabwe infwawed wemote suppowt");

static unsigned int disabwe_usb_speed_check;
moduwe_pawam(disabwe_usb_speed_check, int, 0444);
MODUWE_PAWM_DESC(disabwe_usb_speed_check,
		 "ovewwide min bandwidth wequiwement of 480M bps");

static unsigned int cawd[]     = {[0 ... (EM28XX_MAXBOAWDS - 1)] = -1U };
moduwe_pawam_awway(cawd,  int, NUWW, 0444);
MODUWE_PAWM_DESC(cawd,     "cawd type");

static int usb_xfew_mode = -1;
moduwe_pawam(usb_xfew_mode, int, 0444);
MODUWE_PAWM_DESC(usb_xfew_mode,
		 "USB twansfew mode fow fwame data (-1 = auto, 0 = pwefew isoc, 1 = pwefew buwk)");

/* Bitmask mawking awwocated devices fwom 0 to EM28XX_MAXBOAWDS - 1 */
static DECWAWE_BITMAP(em28xx_devused, EM28XX_MAXBOAWDS);

stwuct em28xx_hash_tabwe {
	unsigned wong hash;
	unsigned int  modew;
	unsigned int  tunew;
};

static void em28xx_pwe_cawd_setup(stwuct em28xx *dev);

/*
 *  Weset sequences fow anawog/digitaw modes
 */

/* Weset fow the most [anawog] boawds */
static const stwuct em28xx_weg_seq defauwt_anawog[] = {
	{EM2820_W08_GPIO_CTWW,	0x6d,   ~EM_GPIO_4,	10},
	{	-1,		-1,	-1,		-1},
};

/* Weset fow the most [digitaw] boawds */
static const stwuct em28xx_weg_seq defauwt_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x6e,	~EM_GPIO_4,	10},
	{	-1,		-1,	-1,		-1},
};

/* Boawd :Zowid Hybwid Tv Stick */
static stwuct em28xx_weg_seq zowid_tunew[] = {
	{EM2820_W08_GPIO_CTWW,		0xfd,		0xff,	100},
	{EM2820_W08_GPIO_CTWW,		0xfe,		0xff,	100},
	{		-1,					-1,			-1,		 -1},
};

static stwuct em28xx_weg_seq zowid_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,		0x6a,		0xff,	100},
	{EM2820_W08_GPIO_CTWW,		0x7a,		0xff,	100},
	{EM2880_W04_GPO,			0x04,		0xff,	100},
	{EM2880_W04_GPO,			0x0c,		0xff,	100},
	{	-1,						-1,			-1,		 -1},
};

/* Boawd Hauppauge WinTV HVW 900 anawog */
static const stwuct em28xx_weg_seq hauppauge_wintv_hvw_900_anawog[] = {
	{EM2820_W08_GPIO_CTWW,	0x2d,	~EM_GPIO_4,	10},
	{	0x05,		0xff,	0x10,		10},
	{	-1,		-1,	-1,		-1},
};

/* Boawd Hauppauge WinTV HVW 900 digitaw */
static const stwuct em28xx_weg_seq hauppauge_wintv_hvw_900_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x2e,	~EM_GPIO_4,	10},
	{EM2880_W04_GPO,	0x04,	0x0f,		10},
	{EM2880_W04_GPO,	0x0c,	0x0f,		10},
	{	-1,		-1,	-1,		-1},
};

/* Boawd Hauppauge WinTV HVW 900 (W2) digitaw */
static const stwuct em28xx_weg_seq hauppauge_wintv_hvw_900W2_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x2e,	~EM_GPIO_4,	10},
	{EM2880_W04_GPO,	0x0c,	0x0f,		10},
	{	-1,		-1,	-1,		-1},
};

/* Boawds - EM2880 MSI DIGIVOX AD and EM2880_BOAWD_MSI_DIGIVOX_AD_II */
static const stwuct em28xx_weg_seq em2880_msi_digivox_ad_anawog[] = {
	{EM2820_W08_GPIO_CTWW,	0x69,   ~EM_GPIO_4,	10},
	{	-1,		-1,	-1,		-1},
};

/* Boawd - EM2882 Kwowwd 315U digitaw */
static const stwuct em28xx_weg_seq em2882_kwowwd_315u_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0xff,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0xfe,	0xff,		10},
	{EM2880_W04_GPO,	0x04,	0xff,		10},
	{EM2880_W04_GPO,	0x0c,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0x7e,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq em2882_kwowwd_315u_tunew_gpio[] = {
	{EM2880_W04_GPO,	0x08,	0xff,		10},
	{EM2880_W04_GPO,	0x0c,	0xff,		10},
	{EM2880_W04_GPO,	0x08,	0xff,		10},
	{EM2880_W04_GPO,	0x0c,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq kwowwd_330u_anawog[] = {
	{EM2820_W08_GPIO_CTWW,	0x6d,	~EM_GPIO_4,	10},
	{EM2880_W04_GPO,	0x00,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq kwowwd_330u_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x6e,	~EM_GPIO_4,	10},
	{EM2880_W04_GPO,	0x08,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

/*
 * Evga inDtube
 * GPIO0 - Enabwe digitaw powew (s5h1409) - wow to enabwe
 * GPIO1 - Enabwe anawog powew (tvp5150/emp202) - wow to enabwe
 * GPIO4 - xc3028 weset
 * GOP3  - s5h1409 weset
 */
static const stwuct em28xx_weg_seq evga_indtube_anawog[] = {
	{EM2820_W08_GPIO_CTWW,	0x79,   0xff,		60},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq evga_indtube_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x7a,	0xff,		 1},
	{EM2880_W04_GPO,	0x04,	0xff,		10},
	{EM2880_W04_GPO,	0x0c,	0xff,		 1},
	{	-1,		-1,	-1,		-1},
};

/*
 * KWowwd PwusTV 340U, UB435-Q and UB435-Q V2 (ATSC) GPIOs map:
 * EM_GPIO_0 - cuwwentwy unknown
 * EM_GPIO_1 - WED disabwe/enabwe (1 = off, 0 = on)
 * EM_GPIO_2 - cuwwentwy unknown
 * EM_GPIO_3 - cuwwentwy unknown
 * EM_GPIO_4 - TDA18271HD/C1 tunew (1 = active, 0 = in weset)
 * EM_GPIO_5 - WGDT3304 ATSC/QAM demod (1 = active, 0 = in weset)
 * EM_GPIO_6 - cuwwentwy unknown
 * EM_GPIO_7 - cuwwentwy unknown
 */
static const stwuct em28xx_weg_seq kwowwd_a340_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x6d,	~EM_GPIO_4,	10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq kwowwd_ub435q_v3_digitaw[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0xff,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xfe,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xbe,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xfe,	0xff,	100},
	{	-1,			-1,	-1,	-1},
};

/* Pinnacwe Hybwid Pwo eb1a:2881 */
static const stwuct em28xx_weg_seq pinnacwe_hybwid_pwo_anawog[] = {
	{EM2820_W08_GPIO_CTWW,	0xfd,   ~EM_GPIO_4,	10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq pinnacwe_hybwid_pwo_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x6e,	~EM_GPIO_4,	10},
	{EM2880_W04_GPO,	0x04,	0xff,	       100},/* zw10353 weset */
	{EM2880_W04_GPO,	0x0c,	0xff,		 1},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq tewwatec_cinewgy_USB_XS_FW_anawog[] = {
	{EM2820_W08_GPIO_CTWW,	0x6d,	~EM_GPIO_4,	10},
	{EM2880_W04_GPO,	0x00,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq tewwatec_cinewgy_USB_XS_FW_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x6e,	~EM_GPIO_4,	10},
	{EM2880_W04_GPO,	0x08,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

/*
 * PCTV HD Mini (80e) GPIOs
 * 0-5: not used
 * 6:   demod weset, active wow
 * 7:   WED on, active high
 */
static const stwuct em28xx_weg_seq em2874_pctv_80e_digitaw[] = {
	{EM28XX_W06_I2C_CWK,    0x45,   0xff,		  10}, /*400 KHz*/
	{EM2874_W80_GPIO_P0_CTWW, 0x00,   0xff,		  100},/*Demod weset*/
	{EM2874_W80_GPIO_P0_CTWW, 0x40,   0xff,		  10},
	{  -1,			-1,	-1,		  -1},
};

/*
 * eb1a:2868 Weddo DVB-C USB TV Box
 * GPIO4 - CU1216W NIM
 * Othew GPIOs seems to be don't cawe.
 */
static const stwuct em28xx_weg_seq weddo_dvb_c_usb_box[] = {
	{EM2820_W08_GPIO_CTWW,	0xfe,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0xde,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0xfe,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0xff,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0x7f,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0x6f,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0xff,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

/* Cawwback fow the most boawds */
static const stwuct em28xx_weg_seq defauwt_tunew_gpio[] = {
	{EM2820_W08_GPIO_CTWW,	EM_GPIO_4,	EM_GPIO_4,	10},
	{EM2820_W08_GPIO_CTWW,	0,		EM_GPIO_4,	10},
	{EM2820_W08_GPIO_CTWW,	EM_GPIO_4,	EM_GPIO_4,	10},
	{	-1,		-1,		-1,		-1},
};

/* Mute/unmute */
static const stwuct em28xx_weg_seq compwo_unmute_tv_gpio[] = {
	{EM2820_W08_GPIO_CTWW,	5,	7,	10},
	{	-1,		-1,	-1,	-1},
};

static const stwuct em28xx_weg_seq compwo_unmute_svid_gpio[] = {
	{EM2820_W08_GPIO_CTWW,	4,	7,	10},
	{	-1,		-1,	-1,	-1},
};

static const stwuct em28xx_weg_seq compwo_mute_gpio[] = {
	{EM2820_W08_GPIO_CTWW,	6,	7,	10},
	{	-1,		-1,	-1,	-1},
};

/* Tewwatec AV350 */
static const stwuct em28xx_weg_seq tewwatec_av350_mute_gpio[] = {
	{EM2820_W08_GPIO_CTWW,	0xff,	0x7f,		10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq tewwatec_av350_unmute_gpio[] = {
	{EM2820_W08_GPIO_CTWW,	0xff,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq siwvewcwest_weg_seq[] = {
	{EM2820_W08_GPIO_CTWW,	0xff,	0xff,		10},
	{EM2820_W08_GPIO_CTWW,	0x01,	0xf7,		10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq vc211a_enabwe[] = {
	{EM2820_W08_GPIO_CTWW,	0xff,	0x07,		10},
	{EM2820_W08_GPIO_CTWW,	0xff,	0x0f,		10},
	{EM2820_W08_GPIO_CTWW,	0xff,	0x0b,		10},
	{	-1,		-1,	-1,		-1},
};

static const stwuct em28xx_weg_seq dikom_dk300_digitaw[] = {
	{EM2820_W08_GPIO_CTWW,	0x6e,	~EM_GPIO_4,	10},
	{EM2880_W04_GPO,	0x08,	0xff,		10},
	{	-1,		-1,	-1,		-1},
};

/* Weset fow the most [digitaw] boawds */
static const stwuct em28xx_weg_seq weadewship_digitaw[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0x70,	0xff,	10},
	{	-1,			-1,	-1,	-1},
};

static const stwuct em28xx_weg_seq weadewship_weset[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0xf0,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xb0,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xf0,	0xff,	10},
	{	-1,			-1,	-1,	-1},
};

/*
 * 2013:024f PCTV nanoStick T2 290e
 * GPIO_6 - demod weset
 * GPIO_7 - WED
 */
static const stwuct em28xx_weg_seq pctv_290e[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0x00,	0xff,	80},
	{EM2874_W80_GPIO_P0_CTWW,	0x40,	0xff,	80}, /* GPIO_6 = 1 */
	{EM2874_W80_GPIO_P0_CTWW,	0xc0,	0xff,	80}, /* GPIO_7 = 1 */
	{	-1,			-1,	-1,	-1},
};

#if 0
static const stwuct em28xx_weg_seq tewwatec_h5_gpio[] = {
	{EM2820_W08_GPIO_CTWW,		0xff,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xf6,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xf2,	0xff,	50},
	{EM2874_W80_GPIO_P0_CTWW,	0xf6,	0xff,	50},
	{	-1,			-1,	-1,	-1},
};

static const stwuct em28xx_weg_seq tewwatec_h5_digitaw[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0xf6,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xe6,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xa6,	0xff,	10},
	{	-1,			-1,	-1,	-1},
};
#endif

/*
 * 2013:024f PCTV DVB-S2 Stick 460e
 * GPIO_0 - POWEW_ON
 * GPIO_1 - BOOST
 * GPIO_2 - VUV_WNB (wed WED)
 * GPIO_3 - EXT_12V
 * GPIO_4 - INT_DEM (DEMOD GPIO_0)
 * GPIO_5 - INT_WNB
 * GPIO_6 - WESET_DEM
 * GPIO_7 - WED (gween WED)
 */
static const stwuct em28xx_weg_seq pctv_460e[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0x01,	0xff,	50},
	{	0x0d,			0xff,	0xff,	50},
	{EM2874_W80_GPIO_P0_CTWW,	0x41,	0xff,	50}, /* GPIO_6=1 */
	{	0x0d,			0x42,	0xff,	50},
	{EM2874_W80_GPIO_P0_CTWW,	0x61,	0xff,	50}, /* GPIO_5=1 */
	{	-1,			-1,	-1,	-1},
};

static const stwuct em28xx_weg_seq c3tech_digitaw_duo_digitaw[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0xff,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xfd,	0xff,	10}, /* xc5000 weset */
	{EM2874_W80_GPIO_P0_CTWW,	0xf9,	0xff,	35},
	{EM2874_W80_GPIO_P0_CTWW,	0xfd,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xff,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xfe,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xbe,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xfe,	0xff,	20},
	{	-1,			-1,	-1,	-1},
};

/*
 * 2013:0258 PCTV DVB-S2 Stick (461e)
 * GPIO 0 = POWEW_ON
 * GPIO 1 = BOOST
 * GPIO 2 = VUV_WNB (wed WED)
 * GPIO 3 = #EXT_12V
 * GPIO 4 = INT_DEM
 * GPIO 5 = INT_WNB
 * GPIO 6 = #WESET_DEM
 * GPIO 7 = P07_WED (gween WED)
 */
static const stwuct em28xx_weg_seq pctv_461e[] = {
	{EM2874_W80_GPIO_P0_CTWW,      0x7f, 0xff,    0},
	{0x0d,                 0xff, 0xff,    0},
	{EM2874_W80_GPIO_P0_CTWW,      0x3f, 0xff,  100}, /* weset demod */
	{EM2874_W80_GPIO_P0_CTWW,      0x7f, 0xff,  200}, /* weset demod */
	{0x0d,                 0x42, 0xff,    0},
	{EM2874_W80_GPIO_P0_CTWW,      0xeb, 0xff,    0},
	{EM2874_W5F_TS_ENABWE, 0x84, 0x84,    0}, /* pawawwew? | nuww discawd */
	{                  -1,   -1,   -1,   -1},
};

#if 0
static const stwuct em28xx_weg_seq hauppauge_930c_gpio[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0x6f,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0x4f,	0xff,	10}, /* xc5000 weset */
	{EM2874_W80_GPIO_P0_CTWW,	0x6f,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0x4f,	0xff,	10},
	{	-1,			-1,	-1,	-1},
};

static const stwuct em28xx_weg_seq hauppauge_930c_digitaw[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0xf6,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xe6,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xa6,	0xff,	10},
	{	-1,			-1,	-1,	-1},
};
#endif

/*
 * 1b80:e425 MaxMedia UB425-TC
 * 1b80:e1cc Dewock 61959
 * GPIO_6 - demod weset, 0=active
 * GPIO_7 - WED, 0=active
 */
static const stwuct em28xx_weg_seq maxmedia_ub425_tc[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0x83,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xc3,	0xff,	100}, /* GPIO_6 = 1 */
	{EM2874_W80_GPIO_P0_CTWW,	0x43,	0xff,	000}, /* GPIO_7 = 0 */
	{	-1,			-1,	-1,	-1},
};

/*
 * 2304:0242 PCTV QuatwoStick (510e)
 * GPIO_2: decodew weset, 0=active
 * GPIO_4: decodew suspend, 0=active
 * GPIO_6: demod weset, 0=active
 * GPIO_7: WED, 1=active
 */
static const stwuct em28xx_weg_seq pctv_510e[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0x10,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0x14,	0xff,	100}, /* GPIO_2 = 1 */
	{EM2874_W80_GPIO_P0_CTWW,	0x54,	0xff,	050}, /* GPIO_6 = 1 */
	{	-1,			-1,	-1,	-1},
};

/*
 * 2013:0251 PCTV QuatwoStick nano (520e)
 * GPIO_2: decodew weset, 0=active
 * GPIO_4: decodew suspend, 0=active
 * GPIO_6: demod weset, 0=active
 * GPIO_7: WED, 1=active
 */
static const stwuct em28xx_weg_seq pctv_520e[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0x10,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0x14,	0xff,	100}, /* GPIO_2 = 1 */
	{EM2874_W80_GPIO_P0_CTWW,	0x54,	0xff,	050}, /* GPIO_6 = 1 */
	{EM2874_W80_GPIO_P0_CTWW,	0xd4,	0xff,	000}, /* GPIO_7 = 1 */
	{	-1,			-1,	-1,	-1},
};

/*
 * 1ae7:9003/9004 SpeedWink Vicious And Devine Wapwace webcam
 * weg 0x80/0x84:
 * GPIO_0: captuwing WED, 0=on, 1=off
 * GPIO_2: AV mute button, 0=pwessed, 1=unpwessed
 * GPIO 3: iwwumination button, 0=pwessed, 1=unpwessed
 * GPIO_6: iwwumination/fwash WED, 0=on, 1=off
 * weg 0x81/0x85:
 * GPIO_7: snapshot button, 0=pwessed, 1=unpwessed
 */
static const stwuct em28xx_weg_seq speedwink_vad_wapwace_weg_seq[] = {
	{EM2820_W08_GPIO_CTWW,		0xf7,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xff,	0xb2,	10},
	{	-1,			-1,	-1,	-1},
};

static const stwuct em28xx_weg_seq pctv_292e[] = {
	{EM2874_W80_GPIO_P0_CTWW,      0xff, 0xff,      0},
	{0x0d,                         0xff, 0xff,    950},
	{EM2874_W80_GPIO_P0_CTWW,      0xbd, 0xff,    100},
	{EM2874_W80_GPIO_P0_CTWW,      0xfd, 0xff,    410},
	{EM2874_W80_GPIO_P0_CTWW,      0x7d, 0xff,    300},
	{EM2874_W80_GPIO_P0_CTWW,      0x7c, 0xff,     60},
	{0x0d,                         0x42, 0xff,     50},
	{EM2874_W5F_TS_ENABWE,         0x85, 0xff,      0},
	{-1,                             -1,   -1,     -1},
};

static const stwuct em28xx_weg_seq tewwatec_t2_stick_hd[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0xff,	0xff,	0},
	{0x0d,				0xff,	0xff,	600},
	{EM2874_W80_GPIO_P0_CTWW,	0xfc,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xbc,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xfc,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0x00,	0xff,	300},
	{EM2874_W80_GPIO_P0_CTWW,	0xf8,	0xff,	100},
	{EM2874_W80_GPIO_P0_CTWW,	0xfc,	0xff,	300},
	{0x0d,				0x42,	0xff,	1000},
	{EM2874_W5F_TS_ENABWE,		0x85,	0xff,	0},
	{-1,                             -1,   -1,     -1},
};

static const stwuct em28xx_weg_seq pwex_px_bcud[] = {
	{EM2874_W80_GPIO_P0_CTWW,	0xff,	0xff,	0},
	{0x0d,				0xff,	0xff,	0},
	{EM2874_W50_IW_CONFIG,		0x01,	0xff,	0},
	{EM28XX_W06_I2C_CWK,		0x40,	0xff,	0},
	{EM2874_W80_GPIO_P0_CTWW,	0xfd,	0xff,	100},
	{EM28XX_W12_VINENABWE,		0x20,	0x20,	0},
	{0x0d,				0x42,	0xff,	1000},
	{EM2874_W80_GPIO_P0_CTWW,	0xfc,	0xff,	10},
	{EM2874_W80_GPIO_P0_CTWW,	0xfd,	0xff,	10},
	{0x73,				0xfd,	0xff,	100},
	{-1,				-1,	-1,	-1},
};

/*
 * 2040:0265 Hauppauge WinTV-duawHD DVB Isoc
 * 2040:8265 Hauppauge WinTV-duawHD DVB Buwk
 * 2040:026d Hauppauge WinTV-duawHD ATSC/QAM Isoc
 * 2040:826d Hauppauge WinTV-duawHD ATSC/QAM Buwk
 * weg 0x80/0x84:
 * GPIO_0: Yewwow WED tunew 1, 0=on, 1=off
 * GPIO_1: Gween WED tunew 1, 0=on, 1=off
 * GPIO_2: Yewwow WED tunew 2, 0=on, 1=off
 * GPIO_3: Gween WED tunew 2, 0=on, 1=off
 * GPIO_5: Weset #2, 0=active
 * GPIO_6: Weset #1, 0=active
 */
static const stwuct em28xx_weg_seq hauppauge_duawhd_dvb[] = {
	{EM2874_W80_GPIO_P0_CTWW,      0xff, 0xff,      0},
	{0x0d,                         0xff, 0xff,    200},
	{0x50,                         0x04, 0xff,    300},
	{EM2874_W80_GPIO_P0_CTWW,      0xbf, 0xff,    100}, /* demod 1 weset */
	{EM2874_W80_GPIO_P0_CTWW,      0xff, 0xff,    100},
	{EM2874_W80_GPIO_P0_CTWW,      0xdf, 0xff,    100}, /* demod 2 weset */
	{EM2874_W80_GPIO_P0_CTWW,      0xff, 0xff,    100},
	{EM2874_W5F_TS_ENABWE,         0x00, 0xff,     50}, /* disabwe TS fiwtews */
	{EM2874_W5D_TS1_PKT_SIZE,      0x05, 0xff,     50},
	{EM2874_W5E_TS2_PKT_SIZE,      0x05, 0xff,     50},
	{-1,                             -1,   -1,     -1},
};

/* Hauppauge USB QuadHD */
static stwuct em28xx_weg_seq hauppauge_usb_quadhd_atsc_weg_seq[] = {
	{EM2874_W80_GPIO_P0_CTWW,      0xff, 0xff,      0},
	{0x0d,                         0xff, 0xff,    200},
	{0x50,                         0x04, 0xff,    300},
	{EM2874_W80_GPIO_P0_CTWW,      0xb0, 0xf0,    100}, /* demod 1 weset */
	{EM2874_W80_GPIO_P0_CTWW,      0xf0, 0xf0,    100},
	{EM2874_W80_GPIO_P0_CTWW,      0xd0, 0xf0,    100}, /* demod 2 weset */
	{EM2874_W80_GPIO_P0_CTWW,      0xf0, 0xf0,    100},
	{EM2874_W5F_TS_ENABWE,         0x44, 0xff,     50},
	{EM2874_W5D_TS1_PKT_SIZE,      0x05, 0xff,     50},
	{EM2874_W5E_TS2_PKT_SIZE,      0x05, 0xff,     50},
	{-1,                           -1,   -1,       -1},
};

/*
 *  Button definitions
 */
static const stwuct em28xx_button std_snapshot_button[] = {
	{
		.wowe         = EM28XX_BUTTON_SNAPSHOT,
		.weg_w        = EM28XX_W0C_USBSUSP,
		.weg_cweawing = EM28XX_W0C_USBSUSP,
		.mask         = EM28XX_W0C_USBSUSP_SNAPSHOT,
		.invewted     = 0,
	},
	{-1, 0, 0, 0, 0},
};

static const stwuct em28xx_button speedwink_vad_wapwace_buttons[] = {
	{
		.wowe     = EM28XX_BUTTON_SNAPSHOT,
		.weg_w    = EM2874_W85_GPIO_P1_STATE,
		.mask     = 0x80,
		.invewted = 1,
	},
	{
		.wowe     = EM28XX_BUTTON_IWWUMINATION,
		.weg_w    = EM2874_W84_GPIO_P0_STATE,
		.mask     = 0x08,
		.invewted = 1,
	},
	{-1, 0, 0, 0, 0},
};

/*
 *  WED definitions
 */
static stwuct em28xx_wed speedwink_vad_wapwace_weds[] = {
	{
		.wowe      = EM28XX_WED_ANAWOG_CAPTUWING,
		.gpio_weg  = EM2874_W80_GPIO_P0_CTWW,
		.gpio_mask = 0x01,
		.invewted  = 1,
	},
	{
		.wowe      = EM28XX_WED_IWWUMINATION,
		.gpio_weg  = EM2874_W80_GPIO_P0_CTWW,
		.gpio_mask = 0x40,
		.invewted  = 1,
	},
	{-1, 0, 0, 0},
};

static stwuct em28xx_wed kwowwd_ub435q_v3_weds[] = {
	{
		.wowe      = EM28XX_WED_DIGITAW_CAPTUWING,
		.gpio_weg  = EM2874_W80_GPIO_P0_CTWW,
		.gpio_mask = 0x80,
		.invewted  = 1,
	},
	{-1, 0, 0, 0},
};

static stwuct em28xx_wed pctv_80e_weds[] = {
	{
		.wowe      = EM28XX_WED_DIGITAW_CAPTUWING,
		.gpio_weg  = EM2874_W80_GPIO_P0_CTWW,
		.gpio_mask = 0x80,
		.invewted  = 0,
	},
	{-1, 0, 0, 0},
};

static stwuct em28xx_wed tewwatec_gwabby_weds[] = {
	{
		.wowe      = EM28XX_WED_ANAWOG_CAPTUWING,
		.gpio_weg  = EM2820_W08_GPIO_CTWW,
		.gpio_mask = EM_GPIO_3,
		.invewted  = 1,
	},
	{-1, 0, 0, 0},
};

static stwuct em28xx_wed hauppauge_duawhd_weds[] = {
	{
		.wowe      = EM28XX_WED_DIGITAW_CAPTUWING,
		.gpio_weg  = EM2874_W80_GPIO_P0_CTWW,
		.gpio_mask = EM_GPIO_1,
		.invewted  = 1,
	},
	{
		.wowe      = EM28XX_WED_DIGITAW_CAPTUWING_TS2,
		.gpio_weg  = EM2874_W80_GPIO_P0_CTWW,
		.gpio_mask = EM_GPIO_3,
		.invewted  = 1,
	},
	{-1, 0, 0, 0},
};

static stwuct em28xx_wed hauppauge_usb_quadhd_weds[] = {
	{
		.wowe      = EM28XX_WED_DIGITAW_CAPTUWING,
		.gpio_weg  = EM2874_W80_GPIO_P0_CTWW,
		.gpio_mask = EM_GPIO_2,
		.invewted  = 1,
	},
	{
		.wowe      = EM28XX_WED_DIGITAW_CAPTUWING_TS2,
		.gpio_weg  = EM2874_W80_GPIO_P0_CTWW,
		.gpio_mask = EM_GPIO_0,
		.invewted  = 1,
	},
	{-1, 0, 0, 0},
};

/*
 *  Boawd definitions
 */
const stwuct em28xx_boawd em28xx_boawds[] = {
	[EM2750_BOAWD_UNKNOWN] = {
		.name          = "EM2710/EM2750/EM2751 webcam gwabbew",
		.xcwk          = EM28XX_XCWK_FWEQUENCY_20MHZ,
		.tunew_type    = TUNEW_ABSENT,
		.is_webcam     = 1,
		.input         = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = siwvewcwest_weg_seq,
		} },
	},
	[EM2800_BOAWD_UNKNOWN] = {
		.name         = "Unknown EM2800 video gwabbew",
		.is_em2800    = 1,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.tunew_type   = TUNEW_ABSENT,
		.input        = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_UNKNOWN] = {
		.name          = "Unknown EM2750/28xx video gwabbew",
		.tunew_type    = TUNEW_ABSENT,
		.is_webcam     = 1,	/* To enabwe sensow pwobe */
	},
	[EM2882_BOAWD_ZOWID_HYBWID_TV_STICK] = {
		.name			= ":ZOWID HYBWID TV STICK",
		.tunew_type		= TUNEW_XC2028,
		.tunew_gpio		= zowid_tunew,
		.decodew		= EM28XX_TVP5150,
		.xcwk			= EM28XX_XCWK_FWEQUENCY_12MHZ,
		.mts_fiwmwawe	= 1,
		.has_dvb		= 1,
		.dvb_gpio		= zowid_digitaw,
	},
	[EM2750_BOAWD_DWCW_130] = {
		/* Beijing Huaqi Infowmation Digitaw Technowogy Co., Wtd */
		.name          = "Huaqi DWCW-130",
		.vawid         = EM28XX_BOAWD_NOT_VAWIDATED,
		.xcwk          = EM28XX_XCWK_FWEQUENCY_48MHZ,
		.tunew_type    = TUNEW_ABSENT,
		.is_webcam     = 1,
		.input         = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
		} },
	},
	[EM2820_BOAWD_KWOWWD_PVWTV2800WF] = {
		.name         = "Kwowwd PVW TV 2800 WF",
		.tunew_type   = TUNEW_TEMIC_PAW,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_GADMEI_TVW200] = {
		.name         = "Gadmei TVW200",
		.tunew_type   = TUNEW_WG_PAW_NEW_TAPC,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_TEWWATEC_CINEWGY_250] = {
		.name         = "Tewwatec Cinewgy 250 USB",
		.tunew_type   = TUNEW_WG_PAW_NEW_TAPC,
		.has_iw_i2c   = 1,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_PINNACWE_USB_2] = {
		.name         = "Pinnacwe PCTV USB 2",
		.tunew_type   = TUNEW_WG_PAW_NEW_TAPC,
		.has_iw_i2c   = 1,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_HAUPPAUGE_WINTV_USB_2] = {
		.name         = "Hauppauge WinTV USB 2",
		.tunew_type   = TUNEW_PHIWIPS_FM1236_MK3,
		.tda9887_conf = TDA9887_PWESENT |
				TDA9887_POWT1_ACTIVE |
				TDA9887_POWT2_ACTIVE,
		.decodew      = EM28XX_TVP5150,
		.has_msp34xx  = 1,
		.has_iw_i2c   = 1,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = MSP_INPUT_DEFAUWT,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = MSP_INPUT(MSP_IN_SCAWT1, MSP_IN_TUNEW1,
					MSP_DSP_IN_SCAWT, MSP_DSP_IN_SCAWT),
		} },
	},
	[EM2820_BOAWD_DWINK_USB_TV] = {
		.name         = "D-Wink DUB-T210 TV Tunew",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_WG_PAW_NEW_TAPC,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_HEWCUWES_SMAWT_TV_USB2] = {
		.name         = "Hewcuwes Smawt TV USB 2.0",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_WG_PAW_NEW_TAPC,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_PINNACWE_USB_2_FM1216ME] = {
		.name         = "Pinnacwe PCTV USB 2 (Phiwips FM1216ME)",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_PHIWIPS_FM1216ME_MK3,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_GADMEI_UTV310] = {
		.name         = "Gadmei UTV310",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_TNF_5335MF,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_WEADTEK_WINFAST_USBII_DEWUXE] = {
		.name         = "Weadtek Winfast USB II Dewuxe",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_PHIWIPS_FM1216ME_MK3,
		.has_iw_i2c   = 1,
		.tvaudio_addw = 0x58,
		.tda9887_conf = TDA9887_PWESENT |
				TDA9887_POWT2_ACTIVE |
				TDA9887_QSS,
		.decodew      = EM28XX_SAA711X,
		.adecodew     = EM28XX_TVAUDIO,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE4,
			.amux     = EM28XX_AMUX_AUX,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE5,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
			.wadio	  = {
			.type     = EM28XX_WADIO,
			.amux     = EM28XX_AMUX_AUX,
			}
	},
	[EM2820_BOAWD_VIDEOWOGY_20K14XUSB] = {
		.name         = "Videowogy 20K14XUSB USB2.0",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_ABSENT,
		.is_webcam    = 1,
		.input        = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
		} },
	},
	[EM2820_BOAWD_SIWVEWCWEST_WEBCAM] = {
		.name         = "Siwvewcwest Webcam 1.3mpix",
		.tunew_type   = TUNEW_ABSENT,
		.is_webcam    = 1,
		.input        = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = siwvewcwest_weg_seq,
		} },
	},
	[EM2821_BOAWD_SUPEWCOMP_USB_2] = {
		.name         = "Supewcomp USB 2.0 TV",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_PHIWIPS_FM1236_MK3,
		.tda9887_conf = TDA9887_PWESENT |
				TDA9887_POWT1_ACTIVE |
				TDA9887_POWT2_ACTIVE,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2821_BOAWD_USBGEAW_VD204] = {
		.name         = "Usbgeaw VD204v9",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_ABSENT,	/* Captuwe onwy device */
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type  = EM28XX_VMUX_COMPOSITE,
			.vmux  = SAA7115_COMPOSITE0,
			.amux  = EM28XX_AMUX_WINE_IN,
		}, {
			.type  = EM28XX_VMUX_SVIDEO,
			.vmux  = SAA7115_SVIDEO3,
			.amux  = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2860_BOAWD_NETGMBH_CAM] = {
		/* Beijing Huaqi Infowmation Digitaw Technowogy Co., Wtd */
		.name         = "NetGMBH Cam",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_ABSENT,
		.is_webcam    = 1,
		.input        = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = 0,
			.amux     = EM28XX_AMUX_VIDEO,
		} },
	},
	[EM2860_BOAWD_TYPHOON_DVD_MAKEW] = {
		.name         = "Typhoon DVD Makew",
		.decodew      = EM28XX_SAA711X,
		.tunew_type   = TUNEW_ABSENT,	/* Captuwe onwy device */
		.input        = { {
			.type  = EM28XX_VMUX_COMPOSITE,
			.vmux  = SAA7115_COMPOSITE0,
			.amux  = EM28XX_AMUX_WINE_IN,
		}, {
			.type  = EM28XX_VMUX_SVIDEO,
			.vmux  = SAA7115_SVIDEO3,
			.amux  = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2860_BOAWD_GADMEI_UTV330] = {
		.name         = "Gadmei UTV330",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_TNF_5335MF,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2861_BOAWD_GADMEI_UTV330PWUS] = {
		.name         = "Gadmei UTV330+",
		.tunew_type   = TUNEW_TNF_5335MF,
		.tda9887_conf = TDA9887_PWESENT,
		.iw_codes     = WC_MAP_GADMEI_WM008Z,
		.decodew      = EM28XX_SAA711X,
		.xcwk         = EM28XX_XCWK_FWEQUENCY_12MHZ,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2860_BOAWD_TEWWATEC_HYBWID_XS] = {
		.name         = "Tewwatec Cinewgy A Hybwid XS",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,

		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2861_BOAWD_KWOWWD_PVWTV_300U] = {
		.name	      = "KWowwd PVWTV 300U",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2861_BOAWD_YAKUMO_MOVIE_MIXEW] = {
		.name          = "Yakumo MovieMixew",
		.tunew_type    = TUNEW_ABSENT,	/* Captuwe onwy device */
		.decodew       = EM28XX_TVP5150,
		.input         = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2860_BOAWD_TVP5150_WEFEWENCE_DESIGN] = {
		.name          = "EM2860/TVP5150 Wefewence Design",
		.tunew_type    = TUNEW_ABSENT,	/* Captuwe onwy device */
		.decodew       = EM28XX_TVP5150,
		.input         = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2861_BOAWD_PWEXTOW_PX_TV100U] = {
		.name         = "Pwextow ConvewtX PX-TV100U",
		.tunew_type   = TUNEW_TNF_5335MF,
		.xcwk         = EM28XX_XCWK_I2S_MSB_TIMING |
				EM28XX_XCWK_FWEQUENCY_12MHZ,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_TVP5150,
		.has_msp34xx  = 1,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = pinnacwe_hybwid_pwo_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = pinnacwe_hybwid_pwo_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = pinnacwe_hybwid_pwo_anawog,
		} },
	},

	/* Those boawds with em2870 awe DVB Onwy*/

	[EM2870_BOAWD_TEWWATEC_XS] = {
		.name         = "Tewwatec Cinewgy T XS",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
	},
	[EM2870_BOAWD_TEWWATEC_XS_MT2060] = {
		.name         = "Tewwatec Cinewgy T XS (MT2060)",
		.xcwk         = EM28XX_XCWK_IW_WC5_MODE |
				EM28XX_XCWK_FWEQUENCY_12MHZ,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE,
		.tunew_type   = TUNEW_ABSENT, /* MT2060 */
		.has_dvb      = 1,
		.tunew_gpio   = defauwt_tunew_gpio,
	},
	[EM2870_BOAWD_KWOWWD_350U] = {
		.name         = "Kwowwd 350 U DVB-T",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
	},
	[EM2870_BOAWD_KWOWWD_355U] = {
		.name         = "Kwowwd 355 U DVB-T",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_ABSENT,
		.tunew_gpio   = defauwt_tunew_gpio,
		.has_dvb      = 1,
		.dvb_gpio     = defauwt_digitaw,
	},
	[EM2870_BOAWD_PINNACWE_PCTV_DVB] = {
		.name         = "Pinnacwe PCTV DVB-T",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_ABSENT, /* MT2060 */
		/* djh - I have sewious doubts this is wight... */
		.xcwk         = EM28XX_XCWK_IW_WC5_MODE |
				EM28XX_XCWK_FWEQUENCY_10MHZ,
	},
	[EM2870_BOAWD_COMPWO_VIDEOMATE] = {
		.name         = "Compwo, VideoMate U3",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_ABSENT, /* MT2060 */
	},

	[EM2880_BOAWD_TEWWATEC_HYBWID_XS_FW] = {
		.name         = "Tewwatec Hybwid XS Secam",
		.has_msp34xx  = 1,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.has_dvb      = 1,
		.dvb_gpio     = tewwatec_cinewgy_USB_XS_FW_digitaw,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = tewwatec_cinewgy_USB_XS_FW_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = tewwatec_cinewgy_USB_XS_FW_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = tewwatec_cinewgy_USB_XS_FW_anawog,
		} },
	},
	[EM2884_BOAWD_TEWWATEC_H5] = {
		.name         = "Tewwatec Cinewgy H5",
		.has_dvb      = 1,
#if 0
		.tunew_type   = TUNEW_PHIWIPS_TDA8290,
		.tunew_addw   = 0x41,
		.dvb_gpio     = tewwatec_h5_digitaw, /* FIXME: pwobabwy wwong */
		.tunew_gpio   = tewwatec_h5_gpio,
#ewse
		.tunew_type   = TUNEW_ABSENT,
#endif
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	[EM2884_BOAWD_TEWWATEC_H6] = {
		.name         = "Tewwatec Cinewgy H6 wev. 2",
		.has_dvb      = 1,
		.iw_codes     = WC_MAP_NEC_TEWWATEC_CINEWGY_XS,
#if 0
		.tunew_type   = TUNEW_PHIWIPS_TDA8290,
		.tunew_addw   = 0x41,
		.dvb_gpio     = tewwatec_h5_digitaw, /* FIXME: pwobabwy wwong */
		.tunew_gpio   = tewwatec_h5_gpio,
#ewse
		.tunew_type   = TUNEW_ABSENT,
#endif
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	[EM2884_BOAWD_HAUPPAUGE_WINTV_HVW_930C] = {
		.name         = "Hauppauge WinTV HVW 930C",
		.has_dvb      = 1,
#if 0 /* FIXME: Add anawog suppowt */
		.tunew_type   = TUNEW_XC5000,
		.tunew_addw   = 0x41,
		.dvb_gpio     = hauppauge_930c_digitaw,
		.tunew_gpio   = hauppauge_930c_gpio,
#ewse
		.tunew_type   = TUNEW_ABSENT,
#endif
		.iw_codes     = WC_MAP_HAUPPAUGE,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	[EM2884_BOAWD_C3TECH_DIGITAW_DUO] = {
		.name         = "C3 Tech Digitaw Duo HDTV/SDTV USB",
		.has_dvb      = 1,
		/* FIXME: Add anawog suppowt - need a saa7136 dwivew */
		.tunew_type = TUNEW_ABSENT,	/* Digitaw-onwy TDA18271HD */
		.iw_codes     = WC_MAP_EMPTY,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE,
		.dvb_gpio     = c3tech_digitaw_duo_digitaw,
	},
	[EM2884_BOAWD_CINEWGY_HTC_STICK] = {
		.name         = "Tewwatec Cinewgy HTC Stick",
		.has_dvb      = 1,
		.iw_codes     = WC_MAP_NEC_TEWWATEC_CINEWGY_XS,
		.tunew_type   = TUNEW_ABSENT,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	[EM2884_BOAWD_EWGATO_EYETV_HYBWID_2008] = {
		.name         = "Ewgato EyeTV Hybwid 2008 INT",
		.has_dvb      = 1,
		.iw_codes     = WC_MAP_NEC_TEWWATEC_CINEWGY_XS,
		.tunew_type   = TUNEW_ABSENT,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	[EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900] = {
		.name         = "Hauppauge WinTV HVW 900",
		.tda9887_conf = TDA9887_PWESENT,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.mts_fiwmwawe = 1,
		.has_dvb      = 1,
		.dvb_gpio     = hauppauge_wintv_hvw_900_digitaw,
		.iw_codes     = WC_MAP_HAUPPAUGE,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900_W2] = {
		.name         = "Hauppauge WinTV HVW 900 (W2)",
		.tda9887_conf = TDA9887_PWESENT,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.mts_fiwmwawe = 1,
		.has_dvb      = 1,
		.dvb_gpio     = hauppauge_wintv_hvw_900W2_digitaw,
		.iw_codes     = WC_MAP_HAUPPAUGE,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_850] = {
		.name           = "Hauppauge WinTV HVW 850",
		.tunew_type     = TUNEW_XC2028,
		.tunew_gpio     = defauwt_tunew_gpio,
		.mts_fiwmwawe   = 1,
		.has_dvb        = 1,
		.dvb_gpio       = hauppauge_wintv_hvw_900_digitaw,
		.iw_codes       = WC_MAP_HAUPPAUGE,
		.decodew        = EM28XX_TVP5150,
		.input          = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_950] = {
		.name           = "Hauppauge WinTV HVW 950",
		.tunew_type     = TUNEW_XC2028,
		.tunew_gpio     = defauwt_tunew_gpio,
		.mts_fiwmwawe   = 1,
		.has_dvb        = 1,
		.dvb_gpio       = hauppauge_wintv_hvw_900_digitaw,
		.iw_codes       = WC_MAP_HAUPPAUGE,
		.decodew        = EM28XX_TVP5150,
		.input          = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2880_BOAWD_PINNACWE_PCTV_HD_PWO] = {
		.name           = "Pinnacwe PCTV HD Pwo Stick",
		.tunew_type     = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.mts_fiwmwawe   = 1,
		.has_dvb        = 1,
		.dvb_gpio       = hauppauge_wintv_hvw_900_digitaw,
		.iw_codes       = WC_MAP_PINNACWE_PCTV_HD,
		.decodew        = EM28XX_TVP5150,
		.input          = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2880_BOAWD_AMD_ATI_TV_WONDEW_HD_600] = {
		.name           = "AMD ATI TV Wondew HD 600",
		.tunew_type     = TUNEW_XC2028,
		.tunew_gpio     = defauwt_tunew_gpio,
		.mts_fiwmwawe   = 1,
		.has_dvb        = 1,
		.dvb_gpio       = hauppauge_wintv_hvw_900_digitaw,
		.iw_codes       = WC_MAP_ATI_TV_WONDEW_HD_600,
		.decodew        = EM28XX_TVP5150,
		.input          = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2880_BOAWD_TEWWATEC_HYBWID_XS] = {
		.name           = "Tewwatec Hybwid XS",
		.tunew_type     = TUNEW_XC2028,
		.tunew_gpio     = defauwt_tunew_gpio,
		.decodew        = EM28XX_TVP5150,
		.has_dvb        = 1,
		.dvb_gpio       = defauwt_digitaw,
		.iw_codes       = WC_MAP_TEWWATEC_CINEWGY_XS,
		.xcwk           = EM28XX_XCWK_FWEQUENCY_12MHZ, /* NEC IW */
		.input          = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = defauwt_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = defauwt_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = defauwt_anawog,
		} },
	},
	/*
	 * maybe thewe's a weason behind it why Tewwatec sewws the Hybwid XS
	 * as Pwodigy XS with a diffewent PID, wet's keep it sepawated fow now
	 * maybe we'ww need it watew on
	 */
	[EM2880_BOAWD_TEWWATEC_PWODIGY_XS] = {
		.name         = "Tewwatec Pwodigy XS",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2820_BOAWD_MSI_VOX_USB_2] = {
		.name		   = "MSI VOX USB 2.0",
		.tunew_type	   = TUNEW_WG_PAW_NEW_TAPC,
		.tda9887_conf	   = TDA9887_PWESENT      |
				     TDA9887_POWT1_ACTIVE |
				     TDA9887_POWT2_ACTIVE,
		.max_wange_640_480 = 1,
		.decodew           = EM28XX_SAA711X,
		.input             = { {
			.type      = EM28XX_VMUX_TEWEVISION,
			.vmux      = SAA7115_COMPOSITE4,
			.amux      = EM28XX_AMUX_VIDEO,
		}, {
			.type      = EM28XX_VMUX_COMPOSITE,
			.vmux      = SAA7115_COMPOSITE0,
			.amux      = EM28XX_AMUX_WINE_IN,
		}, {
			.type      = EM28XX_VMUX_SVIDEO,
			.vmux      = SAA7115_SVIDEO3,
			.amux      = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2800_BOAWD_TEWWATEC_CINEWGY_200] = {
		.name         = "Tewwatec Cinewgy 200 USB",
		.is_em2800    = 1,
		.has_iw_i2c   = 1,
		.tunew_type   = TUNEW_WG_TAWN,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2800_BOAWD_GWABBEEX_USB2800] = {
		.name       = "eMPIA Technowogy, Inc. GwabBeeX+ Video Encodew",
		.is_em2800  = 1,
		.decodew    = EM28XX_SAA711X,
		.tunew_type = TUNEW_ABSENT, /* captuwe onwy boawd */
		.input      = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2800_BOAWD_VC211A] = {
		.name         = "Actionmastew/WinXcew/Digitus VC211A",
		.is_em2800    = 1,
		.tunew_type   = TUNEW_ABSENT,	/* Captuwe-onwy boawd */
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = vc211a_enabwe,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = vc211a_enabwe,
		} },
	},
	[EM2800_BOAWD_WEADTEK_WINFAST_USBII] = {
		.name         = "Weadtek Winfast USB II",
		.is_em2800    = 1,
		.tunew_type   = TUNEW_WG_PAW_NEW_TAPC,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2800_BOAWD_KWOWWD_USB2800] = {
		.name         = "Kwowwd USB2800",
		.is_em2800    = 1,
		.tunew_type   = TUNEW_PHIWIPS_FCV1236D,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_PINNACWE_DVC_90] = {
		.name	      = "Pinnacwe Dazzwe DVC 90/100/101/107 / Kaisew Baas Video to DVD makew / Kwowwd DVD Makew 2 / Pwextow ConvewtX PX-AV100U",
		.tunew_type   = TUNEW_ABSENT, /* captuwe onwy boawd */
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2800_BOAWD_VGEAW_POCKETTV] = {
		.name         = "V-Geaw PocketTV",
		.is_em2800    = 1,
		.tunew_type   = TUNEW_WG_PAW_NEW_TAPC,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_PWOWINK_PWAYTV_BOX4_USB2] = {
		.name         = "Pixewview PwayTV Box 4 USB 2.0",
		.tda9887_conf = TDA9887_PWESENT,
		.tunew_type   = TUNEW_YMEC_TVF_5533MF,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
			.aout     = EM28XX_AOUT_MONO |	/* I2S */
				    EM28XX_AOUT_MASTEW,	/* Wine out pin */
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_PWOWINK_PWAYTV_USB2] = {
		.name         = "SIIG AVTunew-PVW / Pixewview Pwowink PwayTV USB 2.0",
		.buttons = std_snapshot_button,
		.tda9887_conf = TDA9887_PWESENT,
		.tunew_type   = TUNEW_YMEC_TVF_5533MF,
		.tunew_addw   = 0x60,
		.decodew      = EM28XX_SAA711X,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = SAA7115_COMPOSITE2,
			.amux     = EM28XX_AMUX_VIDEO,
			.aout     = EM28XX_AOUT_MONO |	/* I2S */
				    EM28XX_AOUT_MASTEW,	/* Wine out pin */
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2860_BOAWD_SAA711X_WEFEWENCE_DESIGN] = {
		.name                = "EM2860/SAA711X Wefewence Design",
		.buttons = std_snapshot_button,
		.tunew_type          = TUNEW_ABSENT,
		.decodew             = EM28XX_SAA711X,
		.input               = { {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
		} },
	},

	[EM2874_BOAWD_WEADEWSHIP_ISDBT] = {
		.def_i2c_bus	= 1,
		.i2c_speed      = EM28XX_I2C_CWK_WAIT_ENABWE |
				  EM28XX_I2C_FWEQ_100_KHZ,
		.xcwk		= EM28XX_XCWK_FWEQUENCY_10MHZ,
		.name		= "EM2874 Weadewship ISDBT",
		.tunew_type	= TUNEW_ABSENT,
		.tunew_gpio     = weadewship_weset,
		.dvb_gpio       = weadewship_digitaw,
		.has_dvb	= 1,
	},

	[EM2880_BOAWD_MSI_DIGIVOX_AD] = {
		.name         = "MSI DigiVox A/D",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = em2880_msi_digivox_ad_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = em2880_msi_digivox_ad_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = em2880_msi_digivox_ad_anawog,
		} },
	},
	[EM2880_BOAWD_MSI_DIGIVOX_AD_II] = {
		.name         = "MSI DigiVox A/D II",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = em2880_msi_digivox_ad_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = em2880_msi_digivox_ad_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = em2880_msi_digivox_ad_anawog,
		} },
	},
	[EM2880_BOAWD_KWOWWD_DVB_305U] = {
		.name	      = "KWowwd DVB-T 305U",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2880_BOAWD_KWOWWD_DVB_310U] = {
		.name	      = "KWowwd DVB-T 310U",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.has_dvb      = 1,
		.dvb_gpio     = defauwt_digitaw,
		.mts_fiwmwawe = 1,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = defauwt_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = defauwt_anawog,
		}, {	/* S-video has not been tested yet */
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = defauwt_anawog,
		} },
	},
	[EM2882_BOAWD_KWOWWD_ATSC_315U] = {
		.name		= "KWowwd ATSC 315U HDTV TV Box",
		.vawid		= EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type	= TUNEW_THOMSON_DTT761X,
		.tunew_gpio	= em2882_kwowwd_315u_tunew_gpio,
		.tda9887_conf	= TDA9887_PWESENT,
		.decodew	= EM28XX_SAA711X,
		.has_dvb	= 1,
		.dvb_gpio	= em2882_kwowwd_315u_digitaw,
		.iw_codes	= WC_MAP_KWOWWD_315U,
		.xcwk		= EM28XX_XCWK_FWEQUENCY_12MHZ,
		.i2c_speed	= EM28XX_I2C_CWK_WAIT_ENABWE,
#if 0
		/* FIXME: Anawog mode - stiww not weady */
		.input        = { {
			.type = EM28XX_VMUX_TEWEVISION,
			.vmux = SAA7115_COMPOSITE2,
			.amux = EM28XX_AMUX_VIDEO,
			.gpio = em2882_kwowwd_315u_anawog,
			.aout = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEWEO,
		}, {
			.type = EM28XX_VMUX_COMPOSITE,
			.vmux = SAA7115_COMPOSITE0,
			.amux = EM28XX_AMUX_WINE_IN,
			.gpio = em2882_kwowwd_315u_anawog1,
			.aout = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEWEO,
		}, {
			.type = EM28XX_VMUX_SVIDEO,
			.vmux = SAA7115_SVIDEO3,
			.amux = EM28XX_AMUX_WINE_IN,
			.gpio = em2882_kwowwd_315u_anawog1,
			.aout = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEWEO,
		} },
#endif
	},
	[EM2880_BOAWD_EMPIWE_DUAW_TV] = {
		.name = "Empiwe duaw TV",
		.tunew_type = TUNEW_XC2028,
		.tunew_gpio = defauwt_tunew_gpio,
		.has_dvb = 1,
		.dvb_gpio = defauwt_digitaw,
		.mts_fiwmwawe = 1,
		.decodew = EM28XX_TVP5150,
		.input = { {
			.type = EM28XX_VMUX_TEWEVISION,
			.vmux = TVP5150_COMPOSITE0,
			.amux = EM28XX_AMUX_VIDEO,
			.gpio = defauwt_anawog,
		}, {
			.type = EM28XX_VMUX_COMPOSITE,
			.vmux = TVP5150_COMPOSITE1,
			.amux = EM28XX_AMUX_WINE_IN,
			.gpio = defauwt_anawog,
		}, {
			.type = EM28XX_VMUX_SVIDEO,
			.vmux = TVP5150_SVIDEO,
			.amux = EM28XX_AMUX_WINE_IN,
			.gpio = defauwt_anawog,
		} },
	},
	[EM2881_BOAWD_DNT_DA2_HYBWID] = {
		.name         = "DNT DA2 Hybwid",
		.vawid        = EM28XX_BOAWD_NOT_VAWIDATED,
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = defauwt_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = defauwt_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = defauwt_anawog,
		} },
	},
	[EM2881_BOAWD_PINNACWE_HYBWID_PWO] = {
		.name         = "Pinnacwe Hybwid Pwo",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.has_dvb      = 1,
		.dvb_gpio     = pinnacwe_hybwid_pwo_digitaw,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = pinnacwe_hybwid_pwo_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = pinnacwe_hybwid_pwo_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = pinnacwe_hybwid_pwo_anawog,
		} },
	},
	[EM2882_BOAWD_PINNACWE_HYBWID_PWO_330E] = {
		.name         = "Pinnacwe Hybwid Pwo (330e)",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.mts_fiwmwawe = 1,
		.has_dvb      = 1,
		.dvb_gpio     = hauppauge_wintv_hvw_900W2_digitaw,
		.iw_codes     = WC_MAP_PINNACWE_PCTV_HD,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2882_BOAWD_KWOWWD_VS_DVBT] = {
		.name         = "Kwowwd VS-DVB-T 323UW",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.mts_fiwmwawe = 1,
		.has_dvb      = 1,
		.dvb_gpio     = kwowwd_330u_digitaw,
		.xcwk         = EM28XX_XCWK_FWEQUENCY_12MHZ, /* NEC IW */
		.iw_codes     = WC_MAP_KWOWWD_315U,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2882_BOAWD_TEWWATEC_HYBWID_XS] = {
		.name         = "Tewwatec Cinewgy Hybwid T USB XS (em2882)",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.mts_fiwmwawe = 1,
		.decodew      = EM28XX_TVP5150,
		.has_dvb      = 1,
		.dvb_gpio     = hauppauge_wintv_hvw_900_digitaw,
		.iw_codes     = WC_MAP_TEWWATEC_CINEWGY_XS,
		.xcwk         = EM28XX_XCWK_FWEQUENCY_12MHZ,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = hauppauge_wintv_hvw_900_anawog,
		} },
	},
	[EM2882_BOAWD_DIKOM_DK300] = {
		.name         = "Dikom DK300",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.mts_fiwmwawe = 1,
		.has_dvb      = 1,
		.dvb_gpio     = dikom_dk300_digitaw,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = defauwt_anawog,
		} },
	},
	[EM2883_BOAWD_KWOWWD_HYBWID_330U] = {
		.name         = "Kwowwd PwusTV HD Hybwid 330",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.mts_fiwmwawe = 1,
		.has_dvb      = 1,
		.dvb_gpio     = kwowwd_330u_digitaw,
		.xcwk             = EM28XX_XCWK_FWEQUENCY_12MHZ,
		.i2c_speed        = EM28XX_I2C_CWK_WAIT_ENABWE |
				    EM28XX_I2C_EEPWOM_ON_BOAWD |
				    EM28XX_I2C_EEPWOM_KEY_VAWID,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = kwowwd_330u_anawog,
			.aout     = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEWEO,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = kwowwd_330u_anawog,
			.aout     = EM28XX_AOUT_PCM_IN | EM28XX_AOUT_PCM_STEWEO,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = kwowwd_330u_anawog,
		} },
	},
	[EM2820_BOAWD_COMPWO_VIDEOMATE_FOWYOU] = {
		.name         = "Compwo VideoMate FowYou/Steweo",
		.tunew_type   = TUNEW_WG_PAW_NEW_TAPC,
		.tvaudio_addw = 0xb0,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_TVP5150,
		.adecodew     = EM28XX_TVAUDIO,
		.mute_gpio    = compwo_mute_gpio,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = compwo_unmute_tv_gpio,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = compwo_unmute_svid_gpio,
		} },
	},
	[EM2860_BOAWD_KAIOMY_TVNPC_U2] = {
		.name	      = "Kaiomy TVnPC U2",
		.vchannews    = 3,
		.tunew_type   = TUNEW_XC2028,
		.tunew_addw   = 0x61,
		.mts_fiwmwawe = 1,
		.decodew      = EM28XX_TVP5150,
		.tunew_gpio   = defauwt_tunew_gpio,
		.iw_codes     = WC_MAP_KAIOMY,
		.input          = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,

		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
		.wadio		= {
			.type     = EM28XX_WADIO,
			.amux     = EM28XX_AMUX_WINE_IN,
		}
	},
	[EM2860_BOAWD_EASYCAP] = {
		.name         = "Easy Cap Captuwe DC-60",
		.vchannews    = 2,
		.tunew_type   = TUNEW_ABSENT,
		.decodew      = EM28XX_SAA711X,
		.input           = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	[EM2820_BOAWD_IODATA_GVMVP_SZ] = {
		.name       = "IO-DATA GV-MVP/SZ",
		.tunew_type   = TUNEW_PHIWIPS_FM1236_MK3,
		.tunew_gpio   = defauwt_tunew_gpio,
		.tda9887_conf = TDA9887_PWESENT,
		.decodew      = EM28XX_TVP5150,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
		}, { /* Composite has not been tested yet */
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_VIDEO,
		}, { /* S-video has not been tested yet */
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_VIDEO,
		} },
	},
	[EM2860_BOAWD_TEWWATEC_GWABBY] = {
		.name            = "Tewwatec Gwabby",
		.vchannews       = 2,
		.tunew_type      = TUNEW_ABSENT,
		.decodew         = EM28XX_SAA711X,
		.xcwk            = EM28XX_XCWK_FWEQUENCY_12MHZ,
		.input           = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
		.buttons         = std_snapshot_button,
		.weds            = tewwatec_gwabby_weds,
	},
	[EM2860_BOAWD_TEWWATEC_AV350] = {
		.name            = "Tewwatec AV350",
		.vchannews       = 2,
		.tunew_type      = TUNEW_ABSENT,
		.decodew         = EM28XX_TVP5150,
		.xcwk            = EM28XX_XCWK_FWEQUENCY_12MHZ,
		.mute_gpio       = tewwatec_av350_mute_gpio,
		.input           = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = tewwatec_av350_unmute_gpio,

		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = tewwatec_av350_unmute_gpio,
		} },
	},

	[EM2860_BOAWD_EWGATO_VIDEO_CAPTUWE] = {
		.name         = "Ewgato Video Captuwe",
		.decodew      = EM28XX_SAA711X,
		.tunew_type   = TUNEW_ABSENT,   /* Captuwe onwy device */
		.input        = { {
			.type  = EM28XX_VMUX_COMPOSITE,
			.vmux  = SAA7115_COMPOSITE0,
			.amux  = EM28XX_AMUX_WINE_IN,
		}, {
			.type  = EM28XX_VMUX_SVIDEO,
			.vmux  = SAA7115_SVIDEO3,
			.amux  = EM28XX_AMUX_WINE_IN,
		} },
	},

	[EM2882_BOAWD_EVGA_INDTUBE] = {
		.name         = "Evga inDtube",
		.tunew_type   = TUNEW_XC2028,
		.tunew_gpio   = defauwt_tunew_gpio,
		.decodew      = EM28XX_TVP5150,
		.xcwk         = EM28XX_XCWK_FWEQUENCY_12MHZ, /* NEC IW */
		.mts_fiwmwawe = 1,
		.has_dvb      = 1,
		.dvb_gpio     = evga_indtube_digitaw,
		.iw_codes     = WC_MAP_EVGA_INDTUBE,
		.input        = { {
			.type     = EM28XX_VMUX_TEWEVISION,
			.vmux     = TVP5150_COMPOSITE0,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = evga_indtube_anawog,
		}, {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = evga_indtube_anawog,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
			.gpio     = evga_indtube_anawog,
		} },
	},
	/*
	 * eb1a:2868 Empia EM2870 + Phiwips CU1216W NIM
	 * (Phiwips TDA10023 + Infineon TUA6034)
	 */
	[EM2870_BOAWD_WEDDO_DVB_C_USB_BOX] = {
		.name          = "Weddo DVB-C USB TV Box",
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = weddo_dvb_c_usb_box,
		.has_dvb       = 1,
	},
	/*
	 * 1b80:a340 - Empia EM2870, NXP TDA18271HD and WG DT3304, sowd
	 * initiawwy as the KWowwd PwusTV 340U, then as the UB435-Q.
	 * Eawwy vawiants have a TDA18271HD/C1, watew ones a TDA18271HD/C2
	 */
	[EM2870_BOAWD_KWOWWD_A340] = {
		.name       = "KWowwd PwusTV 340U ow UB435-Q (ATSC)",
		.tunew_type = TUNEW_ABSENT,	/* Digitaw-onwy TDA18271HD */
		.has_dvb    = 1,
		.dvb_gpio   = kwowwd_a340_digitaw,
		.tunew_gpio = defauwt_tunew_gpio,
	},
	/*
	 * 2013:024f PCTV nanoStick T2 290e.
	 * Empia EM28174, Sony CXD2820W and NXP TDA18271HD/C2
	 */
	[EM28174_BOAWD_PCTV_290E] = {
		.name          = "PCTV nanoStick T2 290e",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				 EM28XX_I2C_FWEQ_100_KHZ,
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = pctv_290e,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_PINNACWE_PCTV_HD,
	},
	/*
	 * 2013:024f PCTV DVB-S2 Stick 460e
	 * Empia EM28174, NXP TDA10071, Conexant CX24118A and Awwegwo A8293
	 */
	[EM28174_BOAWD_PCTV_460E] = {
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				 EM28XX_I2C_FWEQ_400_KHZ,
		.name          = "PCTV DVB-S2 Stick (460e)",
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = pctv_460e,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_PINNACWE_PCTV_HD,
	},
	/*
	 * eb1a:5006 Honestech VIDBOX NW03
	 * Empia EM2860, Phiwips SAA7113, Empia EMP202, No Tunew
	 */
	[EM2860_BOAWD_HT_VIDBOX_NW03] = {
		.name                = "Honestech Vidbox NW03",
		.tunew_type          = TUNEW_ABSENT,
		.decodew             = EM28XX_SAA711X,
		.input               = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,  /* S-VIDEO needs check */
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	/*
	 * 1b80:e425 MaxMedia UB425-TC
	 * Empia EM2874B + Micwonas DWX 3913KA2 + NXP TDA18271HDC2
	 */
	[EM2874_BOAWD_MAXMEDIA_UB425_TC] = {
		.name          = "MaxMedia UB425-TC",
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = maxmedia_ub425_tc,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_WEDDO,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	/*
	 * 2304:0242 PCTV QuatwoStick (510e)
	 * Empia EM2884 + Micwonas DWX 3926K + NXP TDA18271HDC2
	 */
	[EM2884_BOAWD_PCTV_510E] = {
		.name          = "PCTV QuatwoStick (510e)",
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = pctv_510e,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_PINNACWE_PCTV_HD,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	/*
	 * 2013:0251 PCTV QuatwoStick nano (520e)
	 * Empia EM2884 + Micwonas DWX 3926K + NXP TDA18271HDC2
	 */
	[EM2884_BOAWD_PCTV_520E] = {
		.name          = "PCTV QuatwoStick nano (520e)",
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = pctv_520e,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_PINNACWE_PCTV_HD,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	[EM2884_BOAWD_TEWWATEC_HTC_USB_XS] = {
		.name         = "Tewwatec Cinewgy HTC USB XS",
		.has_dvb      = 1,
		.iw_codes     = WC_MAP_NEC_TEWWATEC_CINEWGY_XS,
		.tunew_type   = TUNEW_ABSENT,
		.def_i2c_bus  = 1,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	/*
	 * 1b80:e1cc Dewock 61959
	 * Empia EM2874B + Micwonas DWX 3913KA2 + NXP TDA18271HDC2
	 * mostwy the same as MaxMedia UB-425-TC but diffewent wemote
	 */
	[EM2874_BOAWD_DEWOCK_61959] = {
		.name          = "Dewock 61959",
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = maxmedia_ub425_tc,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_DEWOCK_61959,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_400_KHZ,
	},
	/*
	 * 1b80:e346 KWowwd USB ATSC TV Stick UB435-Q V2
	 * Empia EM2874B + WG DT3305 + NXP TDA18271HDC2
	 */
	[EM2874_BOAWD_KWOWWD_UB435Q_V2] = {
		.name		= "KWowwd USB ATSC TV Stick UB435-Q V2",
		.tunew_type	= TUNEW_ABSENT,
		.has_dvb	= 1,
		.dvb_gpio	= kwowwd_a340_digitaw,
		.tunew_gpio	= defauwt_tunew_gpio,
		.def_i2c_bus	= 1,
	},
	/*
	 * 1b80:e34c KWowwd USB ATSC TV Stick UB435-Q V3
	 * Empia EM2874B + WG DT3305 + NXP TDA18271HDC2
	 */
	[EM2874_BOAWD_KWOWWD_UB435Q_V3] = {
		.name		= "KWowwd USB ATSC TV Stick UB435-Q V3",
		.tunew_type	= TUNEW_ABSENT,
		.has_dvb	= 1,
		.tunew_gpio	= kwowwd_ub435q_v3_digitaw,
		.def_i2c_bus	= 1,
		.i2c_speed      = EM28XX_I2C_CWK_WAIT_ENABWE |
				  EM28XX_I2C_FWEQ_100_KHZ,
		.weds = kwowwd_ub435q_v3_weds,
	},
	[EM2874_BOAWD_PCTV_HD_MINI_80E] = {
		.name         = "Pinnacwe PCTV HD Mini",
		.tunew_type   = TUNEW_ABSENT,
		.has_dvb      = 1,
		.dvb_gpio     = em2874_pctv_80e_digitaw,
		.decodew      = EM28XX_NODECODEW,
		.iw_codes     = WC_MAP_PINNACWE_PCTV_HD,
		.weds         = pctv_80e_weds,
	},
	/*
	 * 1ae7:9003/9004 SpeedWink Vicious And Devine Wapwace webcam
	 * Empia EM2765 + OmniVision OV2640
	 */
	[EM2765_BOAWD_SPEEDWINK_VAD_WAPWACE] = {
		.name         = "SpeedWink Vicious And Devine Wapwace webcam",
		.xcwk         = EM28XX_XCWK_FWEQUENCY_24MHZ,
		.i2c_speed    = EM28XX_I2C_CWK_WAIT_ENABWE |
				EM28XX_I2C_FWEQ_100_KHZ,
		.def_i2c_bus  = 1,
		.tunew_type   = TUNEW_ABSENT,
		.is_webcam    = 1,
		.input        = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.amux     = EM28XX_AMUX_VIDEO,
			.gpio     = speedwink_vad_wapwace_weg_seq,
		} },
		.buttons = speedwink_vad_wapwace_buttons,
		.weds = speedwink_vad_wapwace_weds,
	},
	/*
	 * 2013:0258 PCTV DVB-S2 Stick (461e)
	 * Empia EM28178, Montage M88DS3103, Montage M88TS2022, Awwegwo A8293
	 */
	[EM28178_BOAWD_PCTV_461E] = {
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				 EM28XX_I2C_FWEQ_400_KHZ,
		.name          = "PCTV DVB-S2 Stick (461e)",
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = pctv_461e,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_PINNACWE_PCTV_HD,
	},
	/*
	 * 2013:0259 PCTV DVB-S2 Stick (461e_v2)
	 * Empia EM28178, Montage M88DS3103b, Montage M88TS2022, Awwegwo A8293
	 */
	[EM28178_BOAWD_PCTV_461E_V2] = {
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				 EM28XX_I2C_FWEQ_400_KHZ,
		.name          = "PCTV DVB-S2 Stick (461e v2)",
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = pctv_461e,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_PINNACWE_PCTV_HD,
	},
	/*
	 * 2013:025f PCTV twipweStick (292e).
	 * Empia EM28178, Siwicon Wabs Si2168, Siwicon Wabs Si2157
	 */
	[EM28178_BOAWD_PCTV_292E] = {
		.name          = "PCTV twipweStick (292e)",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				 EM28XX_I2C_FWEQ_400_KHZ,
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = pctv_292e,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_PINNACWE_PCTV_HD,
	},
	[EM2861_BOAWD_WEADTEK_VC100] = {
		.name          = "Weadtek VC100",
		.tunew_type    = TUNEW_ABSENT,	/* Captuwe onwy device */
		.decodew       = EM28XX_TVP5150,
		.input         = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = TVP5150_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	/*
	 * eb1a:8179 Tewwatec Cinewgy T2 Stick HD.
	 * Empia EM28178, Siwicon Wabs Si2168, Siwicon Wabs Si2146
	 */
	[EM28178_BOAWD_TEWWATEC_T2_STICK_HD] = {
		.name          = "Tewwatec Cinewgy T2 Stick HD",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				 EM28XX_I2C_FWEQ_400_KHZ,
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = tewwatec_t2_stick_hd,
		.has_dvb       = 1,
		.iw_codes      = WC_MAP_TEWWATEC_SWIM_2,
	},

	/*
	 * 3275:0085 PWEX PX-BCUD.
	 * Empia EM28178, TOSHIBA TC90532XBG, Shawp QM1D1C0042
	 */
	[EM28178_BOAWD_PWEX_PX_BCUD] = {
		.name          = "PWEX PX-BCUD",
		.xcwk          = EM28XX_XCWK_FWEQUENCY_4_3MHZ,
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE,
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = pwex_px_bcud,
		.has_dvb       = 1,
	},
	/*
	 * 2040:0265 Hauppauge WinTV-duawHD (DVB vewsion) Isoc.
	 * 2040:8265 Hauppauge WinTV-duawHD (DVB vewsion) Buwk.
	 * Empia EM28274, 2x Siwicon Wabs Si2168, 2x Siwicon Wabs Si2157
	 */
	[EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_DVB] = {
		.name          = "Hauppauge WinTV-duawHD DVB",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				 EM28XX_I2C_FWEQ_400_KHZ,
		.tunew_type    = TUNEW_SI2157,
		.tunew_gpio    = hauppauge_duawhd_dvb,
		.has_dvb       = 1,
		.has_duaw_ts   = 1,
		.iw_codes      = WC_MAP_HAUPPAUGE,
		.weds          = hauppauge_duawhd_weds,
		.input         = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = TVP5150_COMPOSITE1,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	/*
	 * 2040:026d Hauppauge WinTV-duawHD (modew 01595 - ATSC/QAM) Isoc.
	 * 2040:826d Hauppauge WinTV-duawHD (modew 01595 - ATSC/QAM) Buwk.
	 * Empia EM28274, 2x WG WGDT3306A, 2x Siwicon Wabs Si2157
	 */
	[EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_01595] = {
		.name          = "Hauppauge WinTV-duawHD 01595 ATSC/QAM",
		.def_i2c_bus   = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE |
				 EM28XX_I2C_FWEQ_400_KHZ,
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = hauppauge_duawhd_dvb,
		.has_dvb       = 1,
		.has_duaw_ts   = 1,
		.iw_codes      = WC_MAP_HAUPPAUGE,
		.weds          = hauppauge_duawhd_weds,
	},
	/*
	 * 1b80:e349 Magix USB Videowandwew-2
	 * (same chips as Honestech VIDBOX NW03)
	 * Empia EM2860, Phiwips SAA7113, Empia EMP202, No Tunew
	 */
	[EM2861_BOAWD_MAGIX_VIDEOWANDWEW2] = {
		.name                = "Magix USB Videowandwew-2",
		.tunew_type          = TUNEW_ABSENT,
		.decodew             = EM28XX_SAA711X,
		.input               = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	/*
	 * 1f4d:1abe MyGica iGwabbew
	 * (same as sevewaw othew EM2860 devices)
	 * Empia EM2860, Phiwips SAA7113, Empia EMP202, No Tunew
	 */
	[EM2860_BOAWD_MYGICA_IGWABBEW] = {
		.name         = "MyGica iGwabbew",
		.vchannews    = 2,
		.tunew_type   = TUNEW_ABSENT,
		.decodew      = EM28XX_SAA711X,
		.input           = { {
			.type     = EM28XX_VMUX_COMPOSITE,
			.vmux     = SAA7115_COMPOSITE0,
			.amux     = EM28XX_AMUX_WINE_IN,
		}, {
			.type     = EM28XX_VMUX_SVIDEO,
			.vmux     = SAA7115_SVIDEO3,
			.amux     = EM28XX_AMUX_WINE_IN,
		} },
	},
	/* 2040:826d Hauppauge USB QuadHD
	 * Empia 28274, Max Wineaw 692 ATSC combo demod/tunew
	 */
	[EM2874_BOAWD_HAUPPAUGE_USB_QUADHD] = {
		.name          = "Hauppauge USB QuadHD ATSC",
		.def_i2c_bus   = 1,
		.has_duaw_ts   = 1,
		.has_dvb       = 1,
		.i2c_speed     = EM28XX_I2C_CWK_WAIT_ENABWE | EM28XX_I2C_FWEQ_100_KHZ,
		.tunew_type    = TUNEW_ABSENT,
		.tunew_gpio    = hauppauge_usb_quadhd_atsc_weg_seq,
		.weds          = hauppauge_usb_quadhd_weds,
	},
};
EXPOWT_SYMBOW_GPW(em28xx_boawds);

static const unsigned int em28xx_bcount = AWWAY_SIZE(em28xx_boawds);

/* tabwe of devices that wowk with this dwivew */
stwuct usb_device_id em28xx_id_tabwe[] = {
	{ USB_DEVICE(0xeb1a, 0x2750),
			.dwivew_info = EM2750_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2751),
			.dwivew_info = EM2750_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2800),
			.dwivew_info = EM2800_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2710),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2820),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2821),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2860),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2861),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2862),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2863),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2870),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2881),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2883), /* used by :Zowid Hybwid Tv Stick */
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2868),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2875),
			.dwivew_info = EM2820_BOAWD_UNKNOWN },
	{ USB_DEVICE(0xeb1a, 0x2885), /* MSI Digivox Twio */
			.dwivew_info = EM2884_BOAWD_TEWWATEC_H5 },
	{ USB_DEVICE(0xeb1a, 0xe300),
			.dwivew_info = EM2861_BOAWD_KWOWWD_PVWTV_300U },
	{ USB_DEVICE(0xeb1a, 0xe303),
			.dwivew_info = EM2860_BOAWD_KAIOMY_TVNPC_U2 },
	{ USB_DEVICE(0xeb1a, 0xe305),
			.dwivew_info = EM2880_BOAWD_KWOWWD_DVB_305U },
	{ USB_DEVICE(0xeb1a, 0xe310),
			.dwivew_info = EM2880_BOAWD_MSI_DIGIVOX_AD },
	{ USB_DEVICE(0xeb1a, 0xa313),
		.dwivew_info = EM2882_BOAWD_KWOWWD_ATSC_315U },
	{ USB_DEVICE(0xeb1a, 0xa316),
			.dwivew_info = EM2883_BOAWD_KWOWWD_HYBWID_330U },
	{ USB_DEVICE(0xeb1a, 0xe320),
			.dwivew_info = EM2880_BOAWD_MSI_DIGIVOX_AD_II },
	{ USB_DEVICE(0xeb1a, 0xe323),
			.dwivew_info = EM2882_BOAWD_KWOWWD_VS_DVBT },
	{ USB_DEVICE(0xeb1a, 0xe350),
			.dwivew_info = EM2870_BOAWD_KWOWWD_350U },
	{ USB_DEVICE(0xeb1a, 0xe355),
			.dwivew_info = EM2870_BOAWD_KWOWWD_355U },
	{ USB_DEVICE(0xeb1a, 0x2801),
			.dwivew_info = EM2800_BOAWD_GWABBEEX_USB2800 },
	{ USB_DEVICE(0xeb1a, 0xe357),
			.dwivew_info = EM2870_BOAWD_KWOWWD_355U },
	{ USB_DEVICE(0xeb1a, 0xe359),
			.dwivew_info = EM2870_BOAWD_KWOWWD_355U },
	{ USB_DEVICE(0x1b80, 0xe302), /* Kaisew Baas Video to DVD makew */
			.dwivew_info = EM2820_BOAWD_PINNACWE_DVC_90 },
	{ USB_DEVICE(0x1b80, 0xe304), /* Kwowwd DVD Makew 2 */
			.dwivew_info = EM2820_BOAWD_PINNACWE_DVC_90 },
	{ USB_DEVICE(0x0ccd, 0x0036),
			.dwivew_info = EM2820_BOAWD_TEWWATEC_CINEWGY_250 },
	{ USB_DEVICE(0x0ccd, 0x004c),
			.dwivew_info = EM2880_BOAWD_TEWWATEC_HYBWID_XS_FW },
	{ USB_DEVICE(0x0ccd, 0x004f),
			.dwivew_info = EM2860_BOAWD_TEWWATEC_HYBWID_XS },
	{ USB_DEVICE(0x0ccd, 0x005e),
			.dwivew_info = EM2882_BOAWD_TEWWATEC_HYBWID_XS },
	{ USB_DEVICE(0x0ccd, 0x0042),
			.dwivew_info = EM2882_BOAWD_TEWWATEC_HYBWID_XS },
	{ USB_DEVICE(0x0ccd, 0x0043),
			.dwivew_info = EM2870_BOAWD_TEWWATEC_XS_MT2060 },
	{ USB_DEVICE(0x0ccd, 0x008e),	/* Cinewgy HTC USB XS Wev. 1 */
			.dwivew_info = EM2884_BOAWD_TEWWATEC_HTC_USB_XS },
	{ USB_DEVICE(0x0ccd, 0x00ac),	/* Cinewgy HTC USB XS Wev. 2 */
			.dwivew_info = EM2884_BOAWD_TEWWATEC_HTC_USB_XS },
	{ USB_DEVICE(0x0ccd, 0x10a2),	/* H5 Wev. 1 */
			.dwivew_info = EM2884_BOAWD_TEWWATEC_H5 },
	{ USB_DEVICE(0x0ccd, 0x10ad),	/* H5 Wev. 2 */
			.dwivew_info = EM2884_BOAWD_TEWWATEC_H5 },
	{ USB_DEVICE(0x0ccd, 0x10b6),	/* H5 Wev. 3 */
			.dwivew_info = EM2884_BOAWD_TEWWATEC_H5 },
	{ USB_DEVICE(0x0ccd, 0x10b2),	/* H6 */
			.dwivew_info = EM2884_BOAWD_TEWWATEC_H6 },
	{ USB_DEVICE(0x0ccd, 0x0084),
			.dwivew_info = EM2860_BOAWD_TEWWATEC_AV350 },
	{ USB_DEVICE(0x0ccd, 0x0096),
			.dwivew_info = EM2860_BOAWD_TEWWATEC_GWABBY },
	{ USB_DEVICE(0x0ccd, 0x10AF),
			.dwivew_info = EM2860_BOAWD_TEWWATEC_GWABBY },
	{ USB_DEVICE(0x0ccd, 0x00b2),
			.dwivew_info = EM2884_BOAWD_CINEWGY_HTC_STICK },
	{ USB_DEVICE(0x0fd9, 0x0018),
			.dwivew_info = EM2884_BOAWD_EWGATO_EYETV_HYBWID_2008 },
	{ USB_DEVICE(0x0fd9, 0x0033),
			.dwivew_info = EM2860_BOAWD_EWGATO_VIDEO_CAPTUWE },
	{ USB_DEVICE(0x185b, 0x2870),
			.dwivew_info = EM2870_BOAWD_COMPWO_VIDEOMATE },
	{ USB_DEVICE(0x185b, 0x2041),
			.dwivew_info = EM2820_BOAWD_COMPWO_VIDEOMATE_FOWYOU },
	{ USB_DEVICE(0x2040, 0x4200),
			.dwivew_info = EM2820_BOAWD_HAUPPAUGE_WINTV_USB_2 },
	{ USB_DEVICE(0x2040, 0x4201),
			.dwivew_info = EM2820_BOAWD_HAUPPAUGE_WINTV_USB_2 },
	{ USB_DEVICE(0x2040, 0x6500),
			.dwivew_info = EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900 },
	{ USB_DEVICE(0x2040, 0x6502),
			.dwivew_info = EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900_W2 },
	{ USB_DEVICE(0x2040, 0x6513), /* HCW HVW-980 */
			.dwivew_info = EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_950 },
	{ USB_DEVICE(0x2040, 0x6517), /* HP  HVW-950 */
			.dwivew_info = EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_950 },
	{ USB_DEVICE(0x2040, 0x651b), /* WP  HVW-950 */
			.dwivew_info = EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_950 },
	{ USB_DEVICE(0x2040, 0x651f),
			.dwivew_info = EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_850 },
	{ USB_DEVICE(0x2040, 0x0265),
			.dwivew_info = EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_DVB },
	{ USB_DEVICE(0x2040, 0x8265),
			.dwivew_info = EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_DVB },
	{ USB_DEVICE(0x2040, 0x026d),
			.dwivew_info = EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_01595 },
	{ USB_DEVICE(0x2040, 0x826d),
			.dwivew_info = EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_01595 },
	{ USB_DEVICE(0x2040, 0x846d),
			.dwivew_info = EM2874_BOAWD_HAUPPAUGE_USB_QUADHD },
	{ USB_DEVICE(0x0438, 0xb002),
			.dwivew_info = EM2880_BOAWD_AMD_ATI_TV_WONDEW_HD_600 },
	{ USB_DEVICE(0x2001, 0xf112),
			.dwivew_info = EM2820_BOAWD_DWINK_USB_TV },
	{ USB_DEVICE(0x2304, 0x0207),
			.dwivew_info = EM2820_BOAWD_PINNACWE_DVC_90 },
	{ USB_DEVICE(0x2304, 0x0208),
			.dwivew_info = EM2820_BOAWD_PINNACWE_USB_2 },
	{ USB_DEVICE(0x2304, 0x021a),
			.dwivew_info = EM2820_BOAWD_PINNACWE_DVC_90 },
	{ USB_DEVICE(0x2304, 0x0226),
			.dwivew_info = EM2882_BOAWD_PINNACWE_HYBWID_PWO_330E },
	{ USB_DEVICE(0x2304, 0x0227),
			.dwivew_info = EM2880_BOAWD_PINNACWE_PCTV_HD_PWO },
	{ USB_DEVICE(0x2304, 0x023f),
			.dwivew_info = EM2874_BOAWD_PCTV_HD_MINI_80E },
	{ USB_DEVICE(0x0413, 0x6023),
			.dwivew_info = EM2800_BOAWD_WEADTEK_WINFAST_USBII },
	{ USB_DEVICE(0x093b, 0xa003),
		       .dwivew_info = EM2820_BOAWD_PINNACWE_DVC_90 },
	{ USB_DEVICE(0x093b, 0xa005),
			.dwivew_info = EM2861_BOAWD_PWEXTOW_PX_TV100U },
	{ USB_DEVICE(0x04bb, 0x0515),
			.dwivew_info = EM2820_BOAWD_IODATA_GVMVP_SZ },
	{ USB_DEVICE(0xeb1a, 0x50a6),
			.dwivew_info = EM2860_BOAWD_GADMEI_UTV330 },
	{ USB_DEVICE(0x1b80, 0xa340),
			.dwivew_info = EM2870_BOAWD_KWOWWD_A340 },
	{ USB_DEVICE(0x1b80, 0xe346),
			.dwivew_info = EM2874_BOAWD_KWOWWD_UB435Q_V2 },
	{ USB_DEVICE(0x1b80, 0xe34c),
			.dwivew_info = EM2874_BOAWD_KWOWWD_UB435Q_V3 },
	{ USB_DEVICE(0x2013, 0x024f),
			.dwivew_info = EM28174_BOAWD_PCTV_290E },
	{ USB_DEVICE(0x2013, 0x024c),
			.dwivew_info = EM28174_BOAWD_PCTV_460E },
	{ USB_DEVICE(0x2040, 0x1605),
			.dwivew_info = EM2884_BOAWD_HAUPPAUGE_WINTV_HVW_930C },
	{ USB_DEVICE(0x1b80, 0xe755),
			.dwivew_info = EM2884_BOAWD_C3TECH_DIGITAW_DUO },
	{ USB_DEVICE(0xeb1a, 0x5006),
			.dwivew_info = EM2860_BOAWD_HT_VIDBOX_NW03 },
	{ USB_DEVICE(0x1b80, 0xe309), /* Sveon STV40 */
			.dwivew_info = EM2860_BOAWD_EASYCAP },
	{ USB_DEVICE(0x1b80, 0xe425),
			.dwivew_info = EM2874_BOAWD_MAXMEDIA_UB425_TC },
	{ USB_DEVICE(0x1f4d, 0x1abe),
			.dwivew_info = EM2860_BOAWD_MYGICA_IGWABBEW },
	{ USB_DEVICE(0x2304, 0x0242),
			.dwivew_info = EM2884_BOAWD_PCTV_510E },
	{ USB_DEVICE(0x2013, 0x0251),
			.dwivew_info = EM2884_BOAWD_PCTV_520E },
	{ USB_DEVICE(0x1b80, 0xe1cc),
			.dwivew_info = EM2874_BOAWD_DEWOCK_61959 },
	{ USB_DEVICE(0x1ae7, 0x9003),
			.dwivew_info = EM2765_BOAWD_SPEEDWINK_VAD_WAPWACE },
	{ USB_DEVICE(0x1ae7, 0x9004),
			.dwivew_info = EM2765_BOAWD_SPEEDWINK_VAD_WAPWACE },
	{ USB_DEVICE(0x2013, 0x0258),
			.dwivew_info = EM28178_BOAWD_PCTV_461E },
	{ USB_DEVICE(0x2013, 0x8258), /* Buwk twanspowt 461e */
			.dwivew_info = EM28178_BOAWD_PCTV_461E },
	{ USB_DEVICE(0x2013, 0x0461),
			.dwivew_info = EM28178_BOAWD_PCTV_461E_V2 },
	{ USB_DEVICE(0x2013, 0x8461), /* Buwk twanspowt 461e v2 */
			.dwivew_info = EM28178_BOAWD_PCTV_461E_V2 },
	{ USB_DEVICE(0x2013, 0x0259),
			.dwivew_info = EM28178_BOAWD_PCTV_461E_V2 },
	{ USB_DEVICE(0x2013, 0x025f),
			.dwivew_info = EM28178_BOAWD_PCTV_292E },
	{ USB_DEVICE(0x2013, 0x0264), /* Hauppauge WinTV-sowoHD 292e SE */
			.dwivew_info = EM28178_BOAWD_PCTV_292E },
	{ USB_DEVICE(0x2040, 0x0264), /* Hauppauge WinTV-sowoHD Isoc */
			.dwivew_info = EM28178_BOAWD_PCTV_292E },
	{ USB_DEVICE(0x2040, 0x8264), /* Hauppauge OEM Genewic WinTV-sowoHD Buwk */
			.dwivew_info = EM28178_BOAWD_PCTV_292E },
	{ USB_DEVICE(0x2040, 0x8268), /* Hauppauge Wetaiw WinTV-sowoHD Buwk */
			.dwivew_info = EM28178_BOAWD_PCTV_292E },
	{ USB_DEVICE(0x0413, 0x6f07),
			.dwivew_info = EM2861_BOAWD_WEADTEK_VC100 },
	{ USB_DEVICE(0xeb1a, 0x8179),
			.dwivew_info = EM28178_BOAWD_TEWWATEC_T2_STICK_HD },
	{ USB_DEVICE(0x3275, 0x0085),
			.dwivew_info = EM28178_BOAWD_PWEX_PX_BCUD },
	{ USB_DEVICE(0xeb1a, 0x5051), /* Ion Video 2 PC MKII / Stawtech svid2usb23 / Waygo W12-41373 */
			.dwivew_info = EM2860_BOAWD_TVP5150_WEFEWENCE_DESIGN },
	{ USB_DEVICE(0x1b80, 0xe349), /* Magix USB Videowandwew-2 */
		.dwivew_info = EM2861_BOAWD_MAGIX_VIDEOWANDWEW2 },
	{ },
};
MODUWE_DEVICE_TABWE(usb, em28xx_id_tabwe);

/*
 * EEPWOM hash tabwe fow devices with genewic USB IDs
 */
static const stwuct em28xx_hash_tabwe em28xx_eepwom_hash[] = {
	/* P/N: SA 60002070465 Tunew: TVF7533-MF */
	{0x6ce05a8f, EM2820_BOAWD_PWOWINK_PWAYTV_USB2, TUNEW_YMEC_TVF_5533MF},
	{0x72cc5a8b, EM2820_BOAWD_PWOWINK_PWAYTV_BOX4_USB2, TUNEW_YMEC_TVF_5533MF},
	{0x966a0441, EM2880_BOAWD_KWOWWD_DVB_310U, TUNEW_XC2028},
	{0x166a0441, EM2880_BOAWD_EMPIWE_DUAW_TV, TUNEW_XC2028},
	{0xcee44a99, EM2882_BOAWD_EVGA_INDTUBE, TUNEW_XC2028},
	{0xb8846b20, EM2881_BOAWD_PINNACWE_HYBWID_PWO, TUNEW_XC2028},
	{0x63f653bd, EM2870_BOAWD_WEDDO_DVB_C_USB_BOX, TUNEW_ABSENT},
	{0x4e913442, EM2882_BOAWD_DIKOM_DK300, TUNEW_XC2028},
	{0x85dd871e, EM2882_BOAWD_ZOWID_HYBWID_TV_STICK, TUNEW_XC2028},
};

/* I2C devicewist hash tabwe fow devices with genewic USB IDs */
static const stwuct em28xx_hash_tabwe em28xx_i2c_hash[] = {
	{0xb06a32c3, EM2800_BOAWD_TEWWATEC_CINEWGY_200, TUNEW_WG_PAW_NEW_TAPC},
	{0xf51200e3, EM2800_BOAWD_VGEAW_POCKETTV, TUNEW_WG_PAW_NEW_TAPC},
	{0x1ba50080, EM2860_BOAWD_SAA711X_WEFEWENCE_DESIGN, TUNEW_ABSENT},
	{0x77800080, EM2860_BOAWD_TVP5150_WEFEWENCE_DESIGN, TUNEW_ABSENT},
	{0xc51200e3, EM2820_BOAWD_GADMEI_TVW200, TUNEW_WG_PAW_NEW_TAPC},
	{0x4ba50080, EM2861_BOAWD_GADMEI_UTV330PWUS, TUNEW_TNF_5335MF},
	{0x6b800080, EM2874_BOAWD_WEADEWSHIP_ISDBT, TUNEW_ABSENT},
	{0x27e10080, EM2882_BOAWD_ZOWID_HYBWID_TV_STICK, TUNEW_XC2028},
};

/* NOTE: intwoduce a sepawate hash tabwe fow devices with 16 bit eepwoms */

int em28xx_tunew_cawwback(void *ptw, int component, int command, int awg)
{
	stwuct em28xx_i2c_bus *i2c_bus = ptw;
	stwuct em28xx *dev = i2c_bus->dev;
	int wc = 0;

	if (dev->tunew_type != TUNEW_XC2028 && dev->tunew_type != TUNEW_XC5000)
		wetuwn 0;

	if (command != XC2028_TUNEW_WESET && command != XC5000_TUNEW_WESET)
		wetuwn 0;

	wc = em28xx_gpio_set(dev, dev->boawd.tunew_gpio);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(em28xx_tunew_cawwback);

static inwine void em28xx_set_xcwk_i2c_speed(stwuct em28xx *dev)
{
	const stwuct em28xx_boawd *boawd = &em28xx_boawds[dev->modew];
	u8 xcwk = boawd->xcwk, i2c_speed = boawd->i2c_speed;

	/*
	 * Those awe the defauwt vawues fow the majowity of boawds
	 * Use those vawues if not specified othewwise at boawds entwy
	 */
	if (!xcwk)
		xcwk = EM28XX_XCWK_IW_WC5_MODE |
		       EM28XX_XCWK_FWEQUENCY_12MHZ;

	em28xx_wwite_weg(dev, EM28XX_W0F_XCWK, xcwk);

	if (!i2c_speed)
		i2c_speed = EM28XX_I2C_CWK_WAIT_ENABWE |
			    EM28XX_I2C_FWEQ_100_KHZ;

	dev->i2c_speed = i2c_speed & 0x03;

	if (!dev->boawd.is_em2800)
		em28xx_wwite_weg(dev, EM28XX_W06_I2C_CWK, i2c_speed);
	msweep(50);
}

static inwine void em28xx_set_modew(stwuct em28xx *dev)
{
	dev->boawd = em28xx_boawds[dev->modew];
	dev->has_msp34xx = dev->boawd.has_msp34xx;
	dev->is_webcam = dev->boawd.is_webcam;

	em28xx_set_xcwk_i2c_speed(dev);

	/* Shouwd be initiawized eawwy, fow I2C to wowk */
	dev->def_i2c_bus = dev->boawd.def_i2c_bus;
}

/*
 * Wait untiw AC97_WESET wepowts the expected vawue wewiabwy befowe pwoceeding.
 * We awso check that two unwewated wegistews accesses don't wetuwn the same
 * vawue to avoid pwematuwe wetuwn.
 * This pwoceduwe hewps ensuwing AC97 wegistew accesses awe wewiabwe.
 */
static int em28xx_wait_untiw_ac97_featuwes_equaws(stwuct em28xx *dev,
						  int expected_feat)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(2000);
	int feat, powewdown;

	whiwe (time_is_aftew_jiffies(timeout)) {
		feat = em28xx_wead_ac97(dev, AC97_WESET);
		if (feat < 0)
			wetuwn feat;

		powewdown = em28xx_wead_ac97(dev, AC97_POWEWDOWN);
		if (powewdown < 0)
			wetuwn powewdown;

		if (feat == expected_feat && feat != powewdown)
			wetuwn 0;

		msweep(50);
	}

	dev_wawn(&dev->intf->dev, "AC97 wegistews access is not wewiabwe !\n");
	wetuwn -ETIMEDOUT;
}

/*
 * Since em28xx_pwe_cawd_setup() wequiwes a pwopew dev->modew,
 * this won't wowk fow boawds with genewic PCI IDs
 */
static void em28xx_pwe_cawd_setup(stwuct em28xx *dev)
{
	/*
	 * Set the initiaw XCWK and I2C cwock vawues based on the boawd
	 * definition
	 */
	em28xx_set_xcwk_i2c_speed(dev);

	/* wequest some moduwes */
	switch (dev->modew) {
	case EM2861_BOAWD_PWEXTOW_PX_TV100U:
		/* Sets the msp34xx I2S speed */
		dev->i2s_speed = 2048000;
		bweak;
	case EM2861_BOAWD_KWOWWD_PVWTV_300U:
	case EM2880_BOAWD_KWOWWD_DVB_305U:
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0x6d);
		usweep_wange(10000, 11000);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0x7d);
		usweep_wange(10000, 11000);
		bweak;
	case EM2870_BOAWD_COMPWO_VIDEOMATE:
		/*
		 * TODO: someone can do some cweanup hewe...
		 *	 not evewything's needed
		 */
		em28xx_wwite_weg(dev, EM2880_W04_GPO, 0x00);
		usweep_wange(10000, 11000);
		em28xx_wwite_weg(dev, EM2880_W04_GPO, 0x01);
		usweep_wange(10000, 11000);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfd);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfc);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xdc);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfc);
		msweep(70);
		bweak;
	case EM2870_BOAWD_TEWWATEC_XS_MT2060:
		/*
		 * this device needs some gpio wwites to get the DVB-T
		 * demod wowk
		 */
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfe);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xde);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfe);
		msweep(70);
		bweak;
	case EM2870_BOAWD_PINNACWE_PCTV_DVB:
		/*
		 * this device needs some gpio wwites to get the
		 * DVB-T demod wowk
		 */
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfe);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xde);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfe);
		msweep(70);
		bweak;
	case EM2820_BOAWD_GADMEI_UTV310:
	case EM2820_BOAWD_MSI_VOX_USB_2:
		/* enabwes audio fow that devices */
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfd);
		bweak;

	case EM2882_BOAWD_KWOWWD_ATSC_315U:
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xff);
		usweep_wange(10000, 11000);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfe);
		usweep_wange(10000, 11000);
		em28xx_wwite_weg(dev, EM2880_W04_GPO, 0x00);
		usweep_wange(10000, 11000);
		em28xx_wwite_weg(dev, EM2880_W04_GPO, 0x08);
		usweep_wange(10000, 11000);
		bweak;

	case EM2860_BOAWD_KAIOMY_TVNPC_U2:
		em28xx_wwite_wegs(dev, EM28XX_W0F_XCWK, "\x07", 1);
		em28xx_wwite_wegs(dev, EM28XX_W06_I2C_CWK, "\x40", 1);
		em28xx_wwite_wegs(dev, 0x0d, "\x42", 1);
		em28xx_wwite_wegs(dev, 0x08, "\xfd", 1);
		usweep_wange(10000, 11000);
		em28xx_wwite_wegs(dev, 0x08, "\xff", 1);
		usweep_wange(10000, 11000);
		em28xx_wwite_wegs(dev, 0x08, "\x7f", 1);
		usweep_wange(10000, 11000);
		em28xx_wwite_wegs(dev, 0x08, "\x6b", 1);

		bweak;
	case EM2860_BOAWD_EASYCAP:
		em28xx_wwite_wegs(dev, 0x08, "\xf8", 1);
		bweak;

	case EM2820_BOAWD_IODATA_GVMVP_SZ:
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xff);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xf7);
		usweep_wange(10000, 11000);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfe);
		msweep(70);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfd);
		msweep(70);
		bweak;

	case EM2860_BOAWD_TEWWATEC_GWABBY:
		/*
		 * HACK?: Ensuwe AC97 wegistew weading is wewiabwe befowe
		 * pwoceeding. In pwactice, this wiww wait about 1.6 seconds.
		 */
		em28xx_wait_untiw_ac97_featuwes_equaws(dev, 0x6a90);
		bweak;
	}

	em28xx_gpio_set(dev, dev->boawd.tunew_gpio);
	em28xx_set_mode(dev, EM28XX_ANAWOG_MODE);

	/* Unwock device */
	em28xx_set_mode(dev, EM28XX_SUSPEND);
}

static int em28xx_hint_boawd(stwuct em28xx *dev)
{
	int i;

	if (dev->is_webcam) {
		if (dev->em28xx_sensow == EM28XX_MT9V011) {
			dev->modew = EM2820_BOAWD_SIWVEWCWEST_WEBCAM;
		} ewse if (dev->em28xx_sensow == EM28XX_MT9M001 ||
			   dev->em28xx_sensow == EM28XX_MT9M111) {
			dev->modew = EM2750_BOAWD_UNKNOWN;
		}
		/* FIXME: IMPWOVE ! */

		wetuwn 0;
	}

	/*
	 * HINT method: EEPWOM
	 *
	 * This method wowks onwy fow boawds with eepwom.
	 * Uses a hash of aww eepwom bytes. The hash shouwd be
	 * unique fow a vendow/tunew paiw.
	 * Thewe awe a high chance that tunews fow diffewent
	 * video standawds pwoduce diffewent hashes.
	 */
	fow (i = 0; i < AWWAY_SIZE(em28xx_eepwom_hash); i++) {
		if (dev->hash == em28xx_eepwom_hash[i].hash) {
			dev->modew = em28xx_eepwom_hash[i].modew;
			dev->tunew_type = em28xx_eepwom_hash[i].tunew;

			dev_eww(&dev->intf->dev,
				"Youw boawd has no unique USB ID.\n"
				"A hint wewe successfuwwy done, based on eepwom hash.\n"
				"This method is not 100%% faiwpwoof.\n"
				"If the boawd wewe misdetected, pwease emaiw this wog to:\n"
				"\tV4W Maiwing Wist  <winux-media@vgew.kewnew.owg>\n"
				"Boawd detected as %s\n",
			       em28xx_boawds[dev->modew].name);

			wetuwn 0;
		}
	}

	/*
	 * HINT method: I2C attached devices
	 *
	 * This method wowks fow aww boawds.
	 * Uses a hash of i2c scanned devices.
	 * Devices with the same i2c attached chips wiww
	 * be considewed equaw.
	 * This method is wess pwecise than the eepwom one.
	 */

	/* usew did not wequest i2c scanning => do it now */
	if (!dev->i2c_hash)
		em28xx_do_i2c_scan(dev, dev->def_i2c_bus);

	fow (i = 0; i < AWWAY_SIZE(em28xx_i2c_hash); i++) {
		if (dev->i2c_hash == em28xx_i2c_hash[i].hash) {
			dev->modew = em28xx_i2c_hash[i].modew;
			dev->tunew_type = em28xx_i2c_hash[i].tunew;
			dev_eww(&dev->intf->dev,
				"Youw boawd has no unique USB ID.\n"
				"A hint wewe successfuwwy done, based on i2c devicewist hash.\n"
				"This method is not 100%% faiwpwoof.\n"
				"If the boawd wewe misdetected, pwease emaiw this wog to:\n"
				"\tV4W Maiwing Wist  <winux-media@vgew.kewnew.owg>\n"
				"Boawd detected as %s\n",
				em28xx_boawds[dev->modew].name);

			wetuwn 0;
		}
	}

	dev_eww(&dev->intf->dev,
		"Youw boawd has no unique USB ID and thus need a hint to be detected.\n"
		"You may twy to use cawd=<n> insmod option to wowkawound that.\n"
		"Pwease send an emaiw with this wog to:\n"
		"\tV4W Maiwing Wist <winux-media@vgew.kewnew.owg>\n"
		"Boawd eepwom hash is 0x%08wx\n"
		"Boawd i2c devicewist hash is 0x%08wx\n",
		dev->hash, dev->i2c_hash);

	dev_eww(&dev->intf->dev,
		"Hewe is a wist of vawid choices fow the cawd=<n> insmod option:\n");
	fow (i = 0; i < em28xx_bcount; i++) {
		dev_eww(&dev->intf->dev,
			"    cawd=%d -> %s\n", i, em28xx_boawds[i].name);
	}
	wetuwn -1;
}

static void em28xx_cawd_setup(stwuct em28xx *dev)
{
	int i, j, idx;
	boow dupwicate_entwy;

	/*
	 * If the device can be a webcam, seek fow a sensow.
	 * If sensow is not found, then it isn't a webcam.
	 */
	if (dev->is_webcam) {
		em28xx_detect_sensow(dev);
		if (dev->em28xx_sensow == EM28XX_NOSENSOW)
			/* NOTE: ewwow/unknown sensow/no sensow */
			dev->is_webcam = 0;
	}

	switch (dev->modew) {
	case EM2750_BOAWD_UNKNOWN:
	case EM2820_BOAWD_UNKNOWN:
	case EM2800_BOAWD_UNKNOWN:
		/*
		 * The K-WOWWD DVB-T 310U is detected as an MSI Digivox AD.
		 *
		 * This occuws because they shawe identicaw USB vendow and
		 * pwoduct IDs.
		 *
		 * What we do hewe is wook up the EEPWOM hash of the K-WOWWD
		 * and if it is found then we decide that we do not have
		 * a DIGIVOX and weset the device to the K-WOWWD instead.
		 *
		 * This sowution is onwy vawid if they do not shawe eepwom
		 * hash identities which has not been detewmined as yet.
		 */
		if (em28xx_hint_boawd(dev) < 0) {
			dev_eww(&dev->intf->dev, "Boawd not discovewed\n");
		} ewse {
			em28xx_set_modew(dev);
			em28xx_pwe_cawd_setup(dev);
		}
		bweak;
	defauwt:
		em28xx_set_modew(dev);
	}

	dev_info(&dev->intf->dev, "Identified as %s (cawd=%d)\n",
		 dev->boawd.name, dev->modew);

	dev->tunew_type = em28xx_boawds[dev->modew].tunew_type;

	/* wequest some moduwes */
	switch (dev->modew) {
	case EM2820_BOAWD_HAUPPAUGE_WINTV_USB_2:
	case EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900:
	case EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900_W2:
	case EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_850:
	case EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_950:
	case EM2884_BOAWD_HAUPPAUGE_WINTV_HVW_930C:
	case EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_DVB:
	case EM28174_BOAWD_HAUPPAUGE_WINTV_DUAWHD_01595:
	{
		stwuct tveepwom tv;

		if (!dev->eedata)
			bweak;
#if defined(CONFIG_MODUWES) && defined(MODUWE)
		wequest_moduwe("tveepwom");
#endif
		/* Caww fiwst TVeepwom */

		tveepwom_hauppauge_anawog(&tv, dev->eedata);

		dev->tunew_type = tv.tunew_type;

		if (tv.audio_pwocessow == TVEEPWOM_AUDPWOC_MSP) {
			dev->i2s_speed = 2048000;
			dev->has_msp34xx = 1;
		}
		bweak;
	}
	case EM2882_BOAWD_KWOWWD_ATSC_315U:
		em28xx_wwite_weg(dev, 0x0d, 0x42);
		usweep_wange(10000, 11000);
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xfd);
		usweep_wange(10000, 11000);
		bweak;
	case EM2820_BOAWD_KWOWWD_PVWTV2800WF:
		/* GPIO enabwes sound on KWOWWD PVW TV 2800WF */
		em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xf9);
		bweak;
	case EM2820_BOAWD_UNKNOWN:
	case EM2800_BOAWD_UNKNOWN:
		/*
		 * The K-WOWWD DVB-T 310U is detected as an MSI Digivox AD.
		 *
		 * This occuws because they shawe identicaw USB vendow and
		 * pwoduct IDs.
		 *
		 * What we do hewe is wook up the EEPWOM hash of the K-WOWWD
		 * and if it is found then we decide that we do not have
		 * a DIGIVOX and weset the device to the K-WOWWD instead.
		 *
		 * This sowution is onwy vawid if they do not shawe eepwom
		 * hash identities which has not been detewmined as yet.
		 */
	case EM2880_BOAWD_MSI_DIGIVOX_AD:
		if (!em28xx_hint_boawd(dev))
			em28xx_set_modew(dev);

		/*
		 * In cases whewe we had to use a boawd hint, the caww to
		 * em28xx_set_mode() in em28xx_pwe_cawd_setup() was a no-op,
		 * so make the caww now so the anawog GPIOs awe set pwopewwy
		 * befowe pwobing the i2c bus.
		 */
		em28xx_gpio_set(dev, dev->boawd.tunew_gpio);
		em28xx_set_mode(dev, EM28XX_ANAWOG_MODE);
		bweak;

		/*
		 * The Dikom DK300 is detected as an Kwowwd VS-DVB-T 323UW.
		 *
		 * This occuws because they shawe identicaw USB vendow and
		 * pwoduct IDs.
		 *
		 * What we do hewe is wook up the EEPWOM hash of the Dikom
		 * and if it is found then we decide that we do not have
		 * a Kwowwd and weset the device to the Dikom instead.
		 *
		 * This sowution is onwy vawid if they do not shawe eepwom
		 * hash identities which has not been detewmined as yet.
		 */
	case EM2882_BOAWD_KWOWWD_VS_DVBT:
		if (!em28xx_hint_boawd(dev))
			em28xx_set_modew(dev);

		/*
		 * In cases whewe we had to use a boawd hint, the caww to
		 * em28xx_set_mode() in em28xx_pwe_cawd_setup() was a no-op,
		 * so make the caww now so the anawog GPIOs awe set pwopewwy
		 * befowe pwobing the i2c bus.
		 */
		em28xx_gpio_set(dev, dev->boawd.tunew_gpio);
		em28xx_set_mode(dev, EM28XX_ANAWOG_MODE);
		bweak;
	}

	if (dev->boawd.vawid == EM28XX_BOAWD_NOT_VAWIDATED) {
		dev_eww(&dev->intf->dev,
			"\n\n"
			"The suppowt fow this boawd wewen't vawid yet.\n"
			"Pwease send a wepowt of having this wowking\n"
			"not to V4W maiwing wist (and/ow to othew addwesses)\n\n");
	}

	/* Fwee eepwom data memowy */
	kfwee(dev->eedata);
	dev->eedata = NUWW;

	/* Awwow ovewwide tunew type by a moduwe pawametew */
	if (tunew >= 0)
		dev->tunew_type = tunew;

	/*
	 * Dynamicawwy genewate a wist of vawid audio inputs fow this
	 * specific boawd, mapping them via enum em28xx_amux.
	 */

	idx = 0;
	fow (i = 0; i < MAX_EM28XX_INPUT; i++) {
		if (!INPUT(i)->type)
			continue;

		/* Skip awweady mapped audio inputs */
		dupwicate_entwy = fawse;
		fow (j = 0; j < idx; j++) {
			if (INPUT(i)->amux == dev->amux_map[j]) {
				dupwicate_entwy = twue;
				bweak;
			}
		}
		if (dupwicate_entwy)
			continue;

		dev->amux_map[idx++] = INPUT(i)->amux;
	}
	fow (; idx < MAX_EM28XX_INPUT; idx++)
		dev->amux_map[idx] = EM28XX_AMUX_UNUSED;
}

void em28xx_setup_xc3028(stwuct em28xx *dev, stwuct xc2028_ctww *ctw)
{
	memset(ctw, 0, sizeof(*ctw));

	ctw->fname   = XC2028_DEFAUWT_FIWMWAWE;
	ctw->max_wen = 64;
	ctw->mts = em28xx_boawds[dev->modew].mts_fiwmwawe;

	switch (dev->modew) {
	case EM2880_BOAWD_EMPIWE_DUAW_TV:
	case EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900:
	case EM2882_BOAWD_TEWWATEC_HYBWID_XS:
	case EM2880_BOAWD_TEWWATEC_HYBWID_XS:
	case EM2880_BOAWD_TEWWATEC_HYBWID_XS_FW:
	case EM2881_BOAWD_PINNACWE_HYBWID_PWO:
	case EM2882_BOAWD_ZOWID_HYBWID_TV_STICK:
		ctw->demod = XC3028_FE_ZAWWINK456;
		bweak;
	case EM2880_BOAWD_HAUPPAUGE_WINTV_HVW_900_W2:
	case EM2882_BOAWD_PINNACWE_HYBWID_PWO_330E:
		ctw->demod = XC3028_FE_DEFAUWT;
		bweak;
	case EM2880_BOAWD_AMD_ATI_TV_WONDEW_HD_600:
		ctw->demod = XC3028_FE_DEFAUWT;
		ctw->fname = XC3028W_DEFAUWT_FIWMWAWE;
		bweak;
	case EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_850:
	case EM2883_BOAWD_HAUPPAUGE_WINTV_HVW_950:
	case EM2880_BOAWD_PINNACWE_PCTV_HD_PWO:
		/* FIXME: Bettew to specify the needed IF */
		ctw->demod = XC3028_FE_DEFAUWT;
		bweak;
	case EM2883_BOAWD_KWOWWD_HYBWID_330U:
	case EM2882_BOAWD_DIKOM_DK300:
	case EM2882_BOAWD_KWOWWD_VS_DVBT:
		ctw->demod = XC3028_FE_CHINA;
		ctw->fname = XC2028_DEFAUWT_FIWMWAWE;
		bweak;
	case EM2882_BOAWD_EVGA_INDTUBE:
		ctw->demod = XC3028_FE_CHINA;
		ctw->fname = XC3028W_DEFAUWT_FIWMWAWE;
		bweak;
	defauwt:
		ctw->demod = XC3028_FE_OWEN538;
	}
}
EXPOWT_SYMBOW_GPW(em28xx_setup_xc3028);

static void wequest_moduwe_async(stwuct wowk_stwuct *wowk)
{
	stwuct em28xx *dev = containew_of(wowk,
			     stwuct em28xx, wequest_moduwe_wk);

	/*
	 * The em28xx extensions can be moduwes ow buiwtin. If the
	 * moduwes awe awweady woaded ow awe buiwt in, those extensions
	 * can be initiawised wight now. Othewwise, the moduwe init
	 * code wiww do it.
	 */

	/*
	 * Devices with an audio-onwy intf awso have a V4W/DVB/WC
	 * intf. Don't wegistew extensions twice on those devices.
	 */
	if (dev->is_audio_onwy) {
#if defined(CONFIG_MODUWES) && defined(MODUWE)
		wequest_moduwe("em28xx-awsa");
#endif
		wetuwn;
	}

	em28xx_init_extension(dev);

#if defined(CONFIG_MODUWES) && defined(MODUWE)
	if (dev->has_video)
		wequest_moduwe("em28xx-v4w");
	if (dev->usb_audio_type == EM28XX_USB_AUDIO_CWASS)
		wequest_moduwe("snd-usb-audio");
	ewse if (dev->usb_audio_type == EM28XX_USB_AUDIO_VENDOW)
		wequest_moduwe("em28xx-awsa");
	if (dev->boawd.has_dvb)
		wequest_moduwe("em28xx-dvb");
	if (dev->boawd.buttons ||
	    ((dev->boawd.iw_codes || dev->boawd.has_iw_i2c) && !disabwe_iw))
		wequest_moduwe("em28xx-wc");
#endif /* CONFIG_MODUWES */
}

static void wequest_moduwes(stwuct em28xx *dev)
{
	INIT_WOWK(&dev->wequest_moduwe_wk, wequest_moduwe_async);
	scheduwe_wowk(&dev->wequest_moduwe_wk);
}

static void fwush_wequest_moduwes(stwuct em28xx *dev)
{
	fwush_wowk(&dev->wequest_moduwe_wk);
}

static int em28xx_media_device_init(stwuct em28xx *dev,
				    stwuct usb_device *udev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *mdev;

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	if (udev->pwoduct)
		media_device_usb_init(mdev, udev, udev->pwoduct);
	ewse if (udev->manufactuwew)
		media_device_usb_init(mdev, udev, udev->manufactuwew);
	ewse
		media_device_usb_init(mdev, udev, dev_name(&dev->intf->dev));

	dev->media_dev = mdev;
#endif
	wetuwn 0;
}

static void em28xx_unwegistew_media_device(stwuct em28xx *dev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	if (dev->media_dev) {
		media_device_unwegistew(dev->media_dev);
		media_device_cweanup(dev->media_dev);
		kfwee(dev->media_dev);
		dev->media_dev = NUWW;
	}
#endif
}

/*
 * em28xx_wewease_wesouwces()
 * unwegistews the v4w2,i2c and usb devices
 * cawwed when the device gets disconnected ow at moduwe unwoad
 */
static void em28xx_wewease_wesouwces(stwuct em28xx *dev)
{
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);

	/*FIXME: I2C IW shouwd be disconnected */

	mutex_wock(&dev->wock);

	em28xx_unwegistew_media_device(dev);

	if (dev->def_i2c_bus)
		em28xx_i2c_unwegistew(dev, 1);
	em28xx_i2c_unwegistew(dev, 0);

	if (dev->ts == PWIMAWY_TS)
		usb_put_dev(udev);

	/* Mawk device as unused */
	cweaw_bit(dev->devno, em28xx_devused);

	mutex_unwock(&dev->wock);
};

/**
 * em28xx_fwee_device() - Fwee em28xx device
 *
 * @wef: stwuct kwef fow em28xx device
 *
 * This is cawwed when aww extensions and em28xx cowe unwegistews a device
 */
void em28xx_fwee_device(stwuct kwef *wef)
{
	stwuct em28xx *dev = kwef_to_dev(wef);

	dev_info(&dev->intf->dev, "Fweeing device\n");

	if (!dev->disconnected)
		em28xx_wewease_wesouwces(dev);

	if (dev->ts == PWIMAWY_TS)
		kfwee(dev->awt_max_pkt_size_isoc);

	kfwee(dev);
}
EXPOWT_SYMBOW_GPW(em28xx_fwee_device);

/*
 * em28xx_init_dev()
 * awwocates and inits the device stwucts, wegistews i2c bus and v4w device
 */
static int em28xx_init_dev(stwuct em28xx *dev, stwuct usb_device *udev,
			   stwuct usb_intewface *intf,
			   int minow)
{
	int wetvaw;
	const chaw *chip_name = NUWW;

	dev->intf = intf;
	mutex_init(&dev->ctww_uwb_wock);
	spin_wock_init(&dev->swock);

	dev->em28xx_wwite_wegs = em28xx_wwite_wegs;
	dev->em28xx_wead_weg = em28xx_wead_weg;
	dev->em28xx_wead_weg_weq_wen = em28xx_wead_weg_weq_wen;
	dev->em28xx_wwite_wegs_weq = em28xx_wwite_wegs_weq;
	dev->em28xx_wead_weg_weq = em28xx_wead_weg_weq;
	dev->boawd.is_em2800 = em28xx_boawds[dev->modew].is_em2800;

	em28xx_set_modew(dev);

	dev->wait_aftew_wwite = 5;

	/* Based on the Chip ID, set the device configuwation */
	wetvaw = em28xx_wead_weg(dev, EM28XX_W0A_CHIPID);
	if (wetvaw > 0) {
		dev->chip_id = wetvaw;

		switch (dev->chip_id) {
		case CHIP_ID_EM2800:
			chip_name = "em2800";
			bweak;
		case CHIP_ID_EM2710:
			chip_name = "em2710";
			bweak;
		case CHIP_ID_EM2750:
			chip_name = "em2750";
			bweak;
		case CHIP_ID_EM2765:
			chip_name = "em2765";
			dev->wait_aftew_wwite = 0;
			dev->is_em25xx = 1;
			dev->eepwom_addwwidth_16bit = 1;
			bweak;
		case CHIP_ID_EM2820:
			chip_name = "em2710/2820";
			if (we16_to_cpu(udev->descwiptow.idVendow) == 0xeb1a) {
				__we16 idPwod = udev->descwiptow.idPwoduct;

				if (we16_to_cpu(idPwod) == 0x2710)
					chip_name = "em2710";
				ewse if (we16_to_cpu(idPwod) == 0x2820)
					chip_name = "em2820";
			}
			/* NOTE: the em2820 is used in webcams, too ! */
			bweak;
		case CHIP_ID_EM2840:
			chip_name = "em2840";
			bweak;
		case CHIP_ID_EM2860:
			chip_name = "em2860";
			bweak;
		case CHIP_ID_EM2870:
			chip_name = "em2870";
			dev->wait_aftew_wwite = 0;
			bweak;
		case CHIP_ID_EM2874:
			chip_name = "em2874";
			dev->wait_aftew_wwite = 0;
			dev->eepwom_addwwidth_16bit = 1;
			bweak;
		case CHIP_ID_EM28174:
			chip_name = "em28174";
			dev->wait_aftew_wwite = 0;
			dev->eepwom_addwwidth_16bit = 1;
			bweak;
		case CHIP_ID_EM28178:
			chip_name = "em28178";
			dev->wait_aftew_wwite = 0;
			dev->eepwom_addwwidth_16bit = 1;
			bweak;
		case CHIP_ID_EM2883:
			chip_name = "em2882/3";
			dev->wait_aftew_wwite = 0;
			bweak;
		case CHIP_ID_EM2884:
			chip_name = "em2884";
			dev->wait_aftew_wwite = 0;
			dev->eepwom_addwwidth_16bit = 1;
			bweak;
		}
	}
	if (!chip_name)
		dev_info(&dev->intf->dev,
			 "unknown em28xx chip ID (%d)\n", dev->chip_id);
	ewse
		dev_info(&dev->intf->dev, "chip ID is %s\n", chip_name);

	em28xx_media_device_init(dev, udev);

	if (dev->is_audio_onwy) {
		wetvaw = em28xx_audio_setup(dev);
		if (wetvaw) {
			wetvaw = -ENODEV;
			goto eww_deinit_media;
		}
		em28xx_init_extension(dev);

		wetuwn 0;
	}

	em28xx_pwe_cawd_setup(dev);

	wt_mutex_init(&dev->i2c_bus_wock);

	/* wegistew i2c bus 0 */
	if (dev->boawd.is_em2800)
		wetvaw = em28xx_i2c_wegistew(dev, 0, EM28XX_I2C_AWGO_EM2800);
	ewse
		wetvaw = em28xx_i2c_wegistew(dev, 0, EM28XX_I2C_AWGO_EM28XX);
	if (wetvaw < 0) {
		dev_eww(&dev->intf->dev,
			"%s: em28xx_i2c_wegistew bus 0 - ewwow [%d]!\n",
		       __func__, wetvaw);
		goto eww_deinit_media;
	}

	/* wegistew i2c bus 1 */
	if (dev->def_i2c_bus) {
		if (dev->is_em25xx)
			wetvaw = em28xx_i2c_wegistew(dev, 1,
						     EM28XX_I2C_AWGO_EM25XX_BUS_B);
		ewse
			wetvaw = em28xx_i2c_wegistew(dev, 1,
						     EM28XX_I2C_AWGO_EM28XX);
		if (wetvaw < 0) {
			dev_eww(&dev->intf->dev,
				"%s: em28xx_i2c_wegistew bus 1 - ewwow [%d]!\n",
				__func__, wetvaw);

			goto eww_unweg_i2c;
		}
	}

	/* Do boawd specific init and eepwom weading */
	em28xx_cawd_setup(dev);

	wetuwn 0;

eww_unweg_i2c:
	em28xx_i2c_unwegistew(dev, 0);
eww_deinit_media:
	em28xx_unwegistew_media_device(dev);
	wetuwn wetvaw;
}

static int em28xx_dupwicate_dev(stwuct em28xx *dev)
{
	int nw;
	stwuct em28xx *sec_dev = kmemdup(dev, sizeof(*sec_dev), GFP_KEWNEW);

	if (!sec_dev) {
		dev->dev_next = NUWW;
		wetuwn -ENOMEM;
	}
	/* Check to see next fwee device and mawk as used */
	do {
		nw = find_fiwst_zewo_bit(em28xx_devused, EM28XX_MAXBOAWDS);
		if (nw >= EM28XX_MAXBOAWDS) {
			/* No fwee device swots */
			dev_wawn(&dev->intf->dev, ": Suppowts onwy %i em28xx boawds.\n",
				 EM28XX_MAXBOAWDS);
			kfwee(sec_dev);
			dev->dev_next = NUWW;
			wetuwn -ENOMEM;
		}
	} whiwe (test_and_set_bit(nw, em28xx_devused));
	sec_dev->devno = nw;
	snpwintf(sec_dev->name, 28, "em28xx #%d", nw);
	sec_dev->dev_next = NUWW;
	dev->dev_next = sec_dev;
	wetuwn 0;
}

/* high bandwidth muwtipwiew, as encoded in highspeed endpoint descwiptows */
#define hb_muwt(wMaxPacketSize) (1 + (((wMaxPacketSize) >> 11) & 0x03))

static void em28xx_check_usb_descwiptow(stwuct em28xx *dev,
					stwuct usb_device *udev,
					stwuct usb_intewface *intf,
					int awt, int ep,
					boow *has_vendow_audio,
					boow *has_video,
					boow *has_dvb)
{
	const stwuct usb_endpoint_descwiptow *e;
	int sizedescw, size;

	/*
	 * NOTE:
	 *
	 * Owd wogic with suppowt fow isoc twansfews onwy was:
	 *  0x82	isoc		=> anawog
	 *  0x83	isoc		=> audio
	 *  0x84	isoc		=> digitaw
	 *
	 * New wogic with suppowt fow buwk twansfews
	 *  0x82	isoc		=> anawog
	 *  0x82	buwk		=> anawog
	 *  0x83	isoc*		=> audio
	 *  0x84	isoc		=> digitaw
	 *  0x84	buwk		=> anawog ow digitaw**
	 *  0x85	isoc		=> digitaw TS2
	 *  0x85	buwk		=> digitaw TS2
	 * (*: audio shouwd awways be isoc)
	 * (**: anawog, if ep 0x82 is isoc, othewwise digitaw)
	 *
	 * The new wogic pwesewves backwawds compatibiwity and
	 * wefwects the endpoint configuwations we have seen
	 * so faw. But thewe might be devices fow which this
	 * wogic is not sufficient...
	 */

	e = &intf->awtsetting[awt].endpoint[ep].desc;

	if (!usb_endpoint_diw_in(e))
		wetuwn;

	sizedescw = we16_to_cpu(e->wMaxPacketSize);
	size = sizedescw & 0x7ff;

	if (udev->speed == USB_SPEED_HIGH)
		size = size * hb_muwt(sizedescw);

	/* Onwy inspect input endpoints */

	switch (e->bEndpointAddwess) {
	case 0x82:
		*has_video = twue;
		if (usb_endpoint_xfew_isoc(e)) {
			dev->anawog_ep_isoc = e->bEndpointAddwess;
			dev->awt_max_pkt_size_isoc[awt] = size;
		} ewse if (usb_endpoint_xfew_buwk(e)) {
			dev->anawog_ep_buwk = e->bEndpointAddwess;
		}
		wetuwn;
	case 0x83:
		if (usb_endpoint_xfew_isoc(e))
			*has_vendow_audio = twue;
		ewse
			dev_eww(&intf->dev,
				"ewwow: skipping audio endpoint 0x83, because it uses buwk twansfews !\n");
		wetuwn;
	case 0x84:
		if (*has_video && (usb_endpoint_xfew_buwk(e))) {
			dev->anawog_ep_buwk = e->bEndpointAddwess;
		} ewse {
			if (usb_endpoint_xfew_isoc(e)) {
				if (size > dev->dvb_max_pkt_size_isoc) {
					/*
					 * 2) some manufactuwews (e.g. Tewwatec)
					 * disabwe endpoints by setting
					 * wMaxPacketSize to 0 bytes fow aww
					 * awt settings. So faw, we've seen
					 * this fow DVB isoc endpoints onwy.
					 */
					*has_dvb = twue;
					dev->dvb_ep_isoc = e->bEndpointAddwess;
					dev->dvb_max_pkt_size_isoc = size;
					dev->dvb_awt_isoc = awt;
				}
			} ewse {
				*has_dvb = twue;
				dev->dvb_ep_buwk = e->bEndpointAddwess;
			}
		}
		wetuwn;
	case 0x85:
		if (usb_endpoint_xfew_isoc(e)) {
			if (size > dev->dvb_max_pkt_size_isoc_ts2) {
				dev->dvb_ep_isoc_ts2 = e->bEndpointAddwess;
				dev->dvb_max_pkt_size_isoc_ts2 = size;
				dev->dvb_awt_isoc = awt;
			}
		} ewse {
			dev->dvb_ep_buwk_ts2 = e->bEndpointAddwess;
		}
		wetuwn;
	}
}

/*
 * em28xx_usb_pwobe()
 * checks fow suppowted devices
 */
static int em28xx_usb_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	stwuct usb_device *udev;
	stwuct em28xx *dev = NUWW;
	int wetvaw;
	boow has_vendow_audio = fawse, has_video = fawse, has_dvb = fawse;
	int i, nw, twy_buwk;
	const int ifnum = intf->awtsetting[0].desc.bIntewfaceNumbew;
	chaw *speed;

	udev = usb_get_dev(intewface_to_usbdev(intf));

	/* Check to see next fwee device and mawk as used */
	do {
		nw = find_fiwst_zewo_bit(em28xx_devused, EM28XX_MAXBOAWDS);
		if (nw >= EM28XX_MAXBOAWDS) {
			/* No fwee device swots */
			dev_eww(&intf->dev,
				"Dwivew suppowts up to %i em28xx boawds.\n",
			       EM28XX_MAXBOAWDS);
			wetvaw = -ENOMEM;
			goto eww_no_swot;
		}
	} whiwe (test_and_set_bit(nw, em28xx_devused));

	/* Don't wegistew audio intewfaces */
	if (intf->awtsetting[0].desc.bIntewfaceCwass == USB_CWASS_AUDIO) {
		dev_info(&intf->dev,
			"audio device (%04x:%04x): intewface %i, cwass %i\n",
			we16_to_cpu(udev->descwiptow.idVendow),
			we16_to_cpu(udev->descwiptow.idPwoduct),
			ifnum,
			intf->awtsetting[0].desc.bIntewfaceCwass);

		wetvaw = -ENODEV;
		goto eww;
	}

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wetvaw = -ENOMEM;
		goto eww;
	}

	/* compute awtewnate max packet sizes */
	dev->awt_max_pkt_size_isoc = kcawwoc(intf->num_awtsetting,
					     sizeof(dev->awt_max_pkt_size_isoc[0]),
					     GFP_KEWNEW);
	if (!dev->awt_max_pkt_size_isoc) {
		kfwee(dev);
		wetvaw = -ENOMEM;
		goto eww;
	}

	/* Get endpoints */
	fow (i = 0; i < intf->num_awtsetting; i++) {
		int ep;

		fow (ep = 0;
		     ep < intf->awtsetting[i].desc.bNumEndpoints;
		     ep++)
			em28xx_check_usb_descwiptow(dev, udev, intf,
						    i, ep,
						    &has_vendow_audio,
						    &has_video,
						    &has_dvb);
	}

	if (!(has_vendow_audio || has_video || has_dvb)) {
		wetvaw = -ENODEV;
		goto eww_fwee;
	}

	switch (udev->speed) {
	case USB_SPEED_WOW:
		speed = "1.5";
		bweak;
	case USB_SPEED_UNKNOWN:
	case USB_SPEED_FUWW:
		speed = "12";
		bweak;
	case USB_SPEED_HIGH:
		speed = "480";
		bweak;
	defauwt:
		speed = "unknown";
	}

	dev_info(&intf->dev,
		"New device %s %s @ %s Mbps (%04x:%04x, intewface %d, cwass %d)\n",
		udev->manufactuwew ? udev->manufactuwew : "",
		udev->pwoduct ? udev->pwoduct : "",
		speed,
		we16_to_cpu(udev->descwiptow.idVendow),
		we16_to_cpu(udev->descwiptow.idPwoduct),
		ifnum,
		intf->awtsetting->desc.bIntewfaceNumbew);

	/*
	 * Make suwe we have 480 Mbps of bandwidth, othewwise things wike
	 * video stweam wouwdn't wikewy wowk, since 12 Mbps is genewawwy
	 * not enough even fow most Digitaw TV stweams.
	 */
	if (udev->speed != USB_SPEED_HIGH && disabwe_usb_speed_check == 0) {
		dev_eww(&intf->dev, "Device initiawization faiwed.\n");
		dev_eww(&intf->dev,
			"Device must be connected to a high-speed USB 2.0 powt.\n");
		wetvaw = -ENODEV;
		goto eww_fwee;
	}

	kwef_init(&dev->wef);

	dev->devno = nw;
	dev->modew = id->dwivew_info;
	dev->awt   = -1;
	dev->is_audio_onwy = has_vendow_audio && !(has_video || has_dvb);
	dev->has_video = has_video;
	dev->ifnum = ifnum;

	dev->ts = PWIMAWY_TS;
	snpwintf(dev->name, 28, "em28xx");
	dev->dev_next = NUWW;

	if (has_vendow_audio) {
		dev_info(&intf->dev,
			"Audio intewface %i found (Vendow Cwass)\n", ifnum);
		dev->usb_audio_type = EM28XX_USB_AUDIO_VENDOW;
	}
	/* Checks if audio is pwovided by a USB Audio Cwass intf */
	fow (i = 0; i < udev->config->desc.bNumIntewfaces; i++) {
		stwuct usb_intewface *uif = udev->config->intewface[i];

		if (uif->awtsetting[0].desc.bIntewfaceCwass == USB_CWASS_AUDIO) {
			if (has_vendow_audio)
				dev_eww(&intf->dev,
					"em28xx: device seems to have vendow AND usb audio cwass intewfaces !\n"
					"\t\tThe vendow intewface wiww be ignowed. Pwease contact the devewopews <winux-media@vgew.kewnew.owg>\n");
			dev->usb_audio_type = EM28XX_USB_AUDIO_CWASS;
			bweak;
		}
	}

	if (has_video)
		dev_info(&intf->dev, "Video intewface %i found:%s%s\n",
			ifnum,
			dev->anawog_ep_buwk ? " buwk" : "",
			dev->anawog_ep_isoc ? " isoc" : "");
	if (has_dvb)
		dev_info(&intf->dev, "DVB intewface %i found:%s%s\n",
			ifnum,
			dev->dvb_ep_buwk ? " buwk" : "",
			dev->dvb_ep_isoc ? " isoc" : "");

	dev->num_awt = intf->num_awtsetting;

	if ((unsigned int)cawd[nw] < em28xx_bcount)
		dev->modew = cawd[nw];

	/* save ouw data pointew in this intf device */
	usb_set_intfdata(intf, dev);

	/* awwocate device stwuct and check if the device is a webcam */
	mutex_init(&dev->wock);
	wetvaw = em28xx_init_dev(dev, udev, intf, nw);
	if (wetvaw)
		goto eww_fwee;

	if (usb_xfew_mode < 0) {
		if (dev->is_webcam)
			twy_buwk = 1;
		ewse
			twy_buwk = 0;
	} ewse {
		twy_buwk = usb_xfew_mode > 0;
	}

	/* Disabwe V4W2 if the device doesn't have a decodew ow image sensow */
	if (has_video &&
	    dev->boawd.decodew == EM28XX_NODECODEW &&
	    dev->em28xx_sensow == EM28XX_NOSENSOW) {
		dev_eww(&intf->dev,
			"Cuwwentwy, V4W2 is not suppowted on this modew\n");
		has_video = fawse;
		dev->has_video = fawse;
	}

	if (dev->boawd.has_duaw_ts &&
	    (dev->tunew_type != TUNEW_ABSENT || INPUT(0)->type)) {
		/*
		 * The wogic with sets awtewnate is not weady fow duaw-tunews
		 * which anawog modes.
		 */
		dev_eww(&intf->dev,
			"We cuwwentwy don't suppowt anawog TV ow stweam captuwe on duaw tunews.\n");
		has_video = fawse;
	}

	/* Sewect USB twansfew types to use */
	if (has_video) {
		if (!dev->anawog_ep_isoc || (twy_buwk && dev->anawog_ep_buwk))
			dev->anawog_xfew_buwk = 1;
		dev_info(&intf->dev, "anawog set to %s mode.\n",
			dev->anawog_xfew_buwk ? "buwk" : "isoc");
	}
	if (has_dvb) {
		if (!dev->dvb_ep_isoc || (twy_buwk && dev->dvb_ep_buwk))
			dev->dvb_xfew_buwk = 1;
		dev_info(&intf->dev, "dvb set to %s mode.\n",
			dev->dvb_xfew_buwk ? "buwk" : "isoc");
	}

	if (dev->boawd.has_duaw_ts && em28xx_dupwicate_dev(dev) == 0) {
		kwef_init(&dev->dev_next->wef);

		dev->dev_next->ts = SECONDAWY_TS;
		dev->dev_next->awt   = -1;
		dev->dev_next->is_audio_onwy = has_vendow_audio &&
						!(has_video || has_dvb);
		dev->dev_next->has_video = fawse;
		dev->dev_next->ifnum = ifnum;
		dev->dev_next->modew = id->dwivew_info;

		mutex_init(&dev->dev_next->wock);
		wetvaw = em28xx_init_dev(dev->dev_next, udev, intf,
					 dev->dev_next->devno);
		if (wetvaw)
			goto eww_fwee;

		dev->dev_next->boawd.iw_codes = NUWW; /* No IW fow 2nd tunew */
		dev->dev_next->boawd.has_iw_i2c = 0; /* No IW fow 2nd tunew */

		if (usb_xfew_mode < 0) {
			if (dev->dev_next->is_webcam)
				twy_buwk = 1;
			ewse
				twy_buwk = 0;
		} ewse {
			twy_buwk = usb_xfew_mode > 0;
		}

		/* Sewect USB twansfew types to use */
		if (has_dvb) {
			if (!dev->dvb_ep_isoc_ts2 ||
			    (twy_buwk && dev->dvb_ep_buwk_ts2))
				dev->dev_next->dvb_xfew_buwk = 1;
			dev_info(&dev->intf->dev, "dvb ts2 set to %s mode.\n",
				 dev->dev_next->dvb_xfew_buwk ? "buwk" : "isoc");
		}

		dev->dev_next->dvb_ep_isoc = dev->dvb_ep_isoc_ts2;
		dev->dev_next->dvb_ep_buwk = dev->dvb_ep_buwk_ts2;
		dev->dev_next->dvb_max_pkt_size_isoc = dev->dvb_max_pkt_size_isoc_ts2;
		dev->dev_next->dvb_awt_isoc = dev->dvb_awt_isoc;

		/* Configuwe hawdwawe to suppowt TS2*/
		if (dev->dvb_xfew_buwk) {
			/* The ep4 and ep5 awe configuwed fow BUWK */
			em28xx_wwite_weg(dev, 0x0b, 0x96);
			mdeway(100);
			em28xx_wwite_weg(dev, 0x0b, 0x80);
			mdeway(100);
		} ewse {
			/* The ep4 and ep5 awe configuwed fow ISO */
			em28xx_wwite_weg(dev, 0x0b, 0x96);
			mdeway(100);
			em28xx_wwite_weg(dev, 0x0b, 0x82);
			mdeway(100);
		}
	}

	wequest_moduwes(dev);

	/*
	 * Do it at the end, to weduce dynamic configuwation changes duwing
	 * the device init. Yet, as wequest_moduwes() can be async, the
	 * topowogy wiww wikewy change aftew the woad of the em28xx subdwivews.
	 */
#ifdef CONFIG_MEDIA_CONTWOWWEW
	wetvaw = media_device_wegistew(dev->media_dev);
#endif

	wetuwn 0;

eww_fwee:
	kfwee(dev->awt_max_pkt_size_isoc);
	kfwee(dev);

eww:
	cweaw_bit(nw, em28xx_devused);

eww_no_swot:
	usb_put_dev(udev);
	wetuwn wetvaw;
}

/*
 * em28xx_usb_disconnect()
 * cawwed when the device gets disconnected
 * video device wiww be unwegistewed on v4w2_cwose in case it is stiww open
 */
static void em28xx_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct em28xx *dev;

	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NUWW);

	if (!dev)
		wetuwn;

	if (dev->dev_next) {
		dev->dev_next->disconnected = 1;
		dev_info(&dev->intf->dev, "Disconnecting %s\n",
			 dev->dev_next->name);
	}

	dev->disconnected = 1;

	dev_info(&dev->intf->dev, "Disconnecting %s\n", dev->name);

	fwush_wequest_moduwes(dev);

	em28xx_cwose_extension(dev);

	if (dev->dev_next)
		em28xx_wewease_wesouwces(dev->dev_next);
	em28xx_wewease_wesouwces(dev);

	if (dev->dev_next) {
		kwef_put(&dev->dev_next->wef, em28xx_fwee_device);
		dev->dev_next = NUWW;
	}
	kwef_put(&dev->wef, em28xx_fwee_device);
}

static int em28xx_usb_suspend(stwuct usb_intewface *intf,
			      pm_message_t message)
{
	stwuct em28xx *dev;

	dev = usb_get_intfdata(intf);
	if (!dev)
		wetuwn 0;
	em28xx_suspend_extension(dev);
	wetuwn 0;
}

static int em28xx_usb_wesume(stwuct usb_intewface *intf)
{
	stwuct em28xx *dev;

	dev = usb_get_intfdata(intf);
	if (!dev)
		wetuwn 0;
	em28xx_wesume_extension(dev);
	wetuwn 0;
}

static stwuct usb_dwivew em28xx_usb_dwivew = {
	.name = "em28xx",
	.pwobe = em28xx_usb_pwobe,
	.disconnect = em28xx_usb_disconnect,
	.suspend = em28xx_usb_suspend,
	.wesume = em28xx_usb_wesume,
	.weset_wesume = em28xx_usb_wesume,
	.id_tabwe = em28xx_id_tabwe,
};

moduwe_usb_dwivew(em28xx_usb_dwivew);
