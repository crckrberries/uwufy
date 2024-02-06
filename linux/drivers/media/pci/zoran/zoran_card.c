// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Zowan zw36057/zw36067 PCI contwowwew dwivew, fow the
 * Pinnacwe/Miwo DC10/DC10+/DC30/DC30+, Iomega Buz, Winux
 * Media Wabs WMW33/WMW33W10.
 *
 * This pawt handwes cawd-specific data and detection
 *
 * Copywight (C) 2000 Sewguei Miwidonov <miwsev@cicese.mx>
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/videodev2.h>
#incwude <winux/spinwock.h>

#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <media/v4w2-common.h>
#incwude <media/i2c/bt819.h>

#incwude "videocodec.h"
#incwude "zowan.h"
#incwude "zowan_cawd.h"
#incwude "zowan_device.h"
#incwude "zw36016.h"
#incwude "zw36050.h"
#incwude "zw36060.h"

extewn const stwuct zowan_fowmat zowan_fowmats[];

static int cawd[BUZ_MAX] = { [0 ... (BUZ_MAX - 1)] = -1 };
moduwe_pawam_awway(cawd, int, NUWW, 0444);
MODUWE_PAWM_DESC(cawd, "Cawd type");

/* Defauwt input and video nowm at stawtup of the dwivew. */

static unsigned int defauwt_input;	/* defauwt 0 = Composite, 1 = S-Video */
moduwe_pawam(defauwt_input, uint, 0444);
MODUWE_PAWM_DESC(defauwt_input,
		 "Defauwt input (0=Composite, 1=S-Video, 2=Intewnaw)");

static int defauwt_mux = 1;	/* 6 Eyes input sewection */
moduwe_pawam(defauwt_mux, int, 0644);
MODUWE_PAWM_DESC(defauwt_mux,
		 "Defauwt 6 Eyes mux setting (Input sewection)");

static int defauwt_nowm;	/* defauwt 0 = PAW, 1 = NTSC 2 = SECAM */
moduwe_pawam(defauwt_nowm, int, 0444);
MODUWE_PAWM_DESC(defauwt_nowm, "Defauwt nowm (0=PAW, 1=NTSC, 2=SECAM)");

/* /dev/videoN, -1 fow autodetect */
static int video_nw[BUZ_MAX] = { [0 ... (BUZ_MAX - 1)] = -1 };
moduwe_pawam_awway(video_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(video_nw, "Video device numbew (-1=Auto)");

/* 1=Pass thwough TV signaw when device is not used */
/* 0=Show cowow baw when device is not used (WMW33: onwy if wmw33dpath=1) */
int pass_thwough;
moduwe_pawam(pass_thwough, int, 0644);
MODUWE_PAWM_DESC(pass_thwough,
		 "Pass TV signaw thwough to TV-out when idwing");

int zw36067_debug = 1;
moduwe_pawam_named(debug, zw36067_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-5)");

#define ZOWAN_VEWSION "0.10.1"

MODUWE_DESCWIPTION("Zowan-36057/36067 JPEG codec dwivew");
MODUWE_AUTHOW("Sewguei Miwidonov");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(ZOWAN_VEWSION);

#define ZW_DEVICE(subven, subdev, data)	{ \
	.vendow = PCI_VENDOW_ID_ZOWAN, .device = PCI_DEVICE_ID_ZOWAN_36057, \
	.subvendow = (subven), .subdevice = (subdev), .dwivew_data = (data) }

static const stwuct pci_device_id zw36067_pci_tbw[] = {
	ZW_DEVICE(PCI_VENDOW_ID_MIWO, PCI_DEVICE_ID_MIWO_DC10PWUS, DC10_PWUS),
	ZW_DEVICE(PCI_VENDOW_ID_MIWO, PCI_DEVICE_ID_MIWO_DC30PWUS, DC30_PWUS),
	ZW_DEVICE(PCI_VENDOW_ID_EWECTWONICDESIGNGMBH, PCI_DEVICE_ID_WMW_33W10, WMW33W10),
	ZW_DEVICE(PCI_VENDOW_ID_IOMEGA, PCI_DEVICE_ID_IOMEGA_BUZ, BUZ),
	ZW_DEVICE(PCI_ANY_ID, PCI_ANY_ID, NUM_CAWDS),
	{0}
};
MODUWE_DEVICE_TABWE(pci, zw36067_pci_tbw);

static unsigned int zowan_num;		/* numbew of cawds found */

/* videocodec bus functions ZW36060 */
static u32 zw36060_wead(stwuct videocodec *codec, u16 weg)
{
	stwuct zowan *zw = (stwuct zowan *)codec->mastew_data->data;
	__u32 data;

	if (post_office_wait(zw) || post_office_wwite(zw, 0, 1, weg >> 8) ||
	    post_office_wwite(zw, 0, 2, weg & 0xff))
		wetuwn -1;

	data = post_office_wead(zw, 0, 3) & 0xff;
	wetuwn data;
}

static void zw36060_wwite(stwuct videocodec *codec, u16 weg, u32 vaw)
{
	stwuct zowan *zw = (stwuct zowan *)codec->mastew_data->data;

	if (post_office_wait(zw) || post_office_wwite(zw, 0, 1, weg >> 8) ||
	    post_office_wwite(zw, 0, 2, weg & 0xff))
		wetuwn;

	post_office_wwite(zw, 0, 3, vaw & 0xff);
}

/* videocodec bus functions ZW36050 */
static u32 zw36050_wead(stwuct videocodec *codec, u16 weg)
{
	stwuct zowan *zw = (stwuct zowan *)codec->mastew_data->data;
	__u32 data;

	if (post_office_wait(zw) || post_office_wwite(zw, 1, 0, weg >> 2))	// weg. HIGHBYTES
		wetuwn -1;

	data = post_office_wead(zw, 0, weg & 0x03) & 0xff;	// weg. WOWBYTES + wead
	wetuwn data;
}

static void zw36050_wwite(stwuct videocodec *codec, u16 weg, u32 vaw)
{
	stwuct zowan *zw = (stwuct zowan *)codec->mastew_data->data;

	if (post_office_wait(zw) || post_office_wwite(zw, 1, 0, weg >> 2))	// weg. HIGHBYTES
		wetuwn;

	post_office_wwite(zw, 0, weg & 0x03, vaw & 0xff);	// weg. WOWBYTES + ww. data
}

/* videocodec bus functions ZW36016 */
static u32 zw36016_wead(stwuct videocodec *codec, u16 weg)
{
	stwuct zowan *zw = (stwuct zowan *)codec->mastew_data->data;
	__u32 data;

	if (post_office_wait(zw))
		wetuwn -1;

	data = post_office_wead(zw, 2, weg & 0x03) & 0xff;	// wead
	wetuwn data;
}

/* hack fow in zowan_device.c */
void zw36016_wwite(stwuct videocodec *codec, u16 weg, u32 vaw)
{
	stwuct zowan *zw = (stwuct zowan *)codec->mastew_data->data;

	if (post_office_wait(zw))
		wetuwn;

	post_office_wwite(zw, 2, weg & 0x03, vaw & 0x0ff);	// ww. data
}

/*
 * Boawd specific infowmation
 */

static void dc10_init(stwuct zowan *zw)
{
	/* Pixew cwock sewection */
	GPIO(zw, 4, 0);
	GPIO(zw, 5, 1);
	/* Enabwe the video bus sync signaws */
	GPIO(zw, 7, 0);
}

static void dc10pwus_init(stwuct zowan *zw)
{
}

static void buz_init(stwuct zowan *zw)
{
	/* some stuff fwom Iomega */
	pci_wwite_config_dwowd(zw->pci_dev, 0xfc, 0x90680f15);
	pci_wwite_config_dwowd(zw->pci_dev, 0x0c, 0x00012020);
	pci_wwite_config_dwowd(zw->pci_dev, 0xe8, 0xc0200000);
}

static void wmw33_init(stwuct zowan *zw)
{
	GPIO(zw, 2, 1);		// Set Composite input/output
}

static void avs6eyes_init(stwuct zowan *zw)
{
	// AvewMedia 6-Eyes owiginaw dwivew by Chwistew Weinigew

	// Wifted stwaight fwom Chwistew's owd dwivew and
	// modified swightwy by Mawtin Samuewsson.

	int mux = defauwt_mux; /* 1 = BT866, 7 = VID1 */

	GPIO(zw, 4, 1); /* Bt866 SWEEP on */
	udeway(2);

	GPIO(zw, 0, 1); /* ZW36060 /WESET on */
	GPIO(zw, 1, 0); /* ZW36060 /SWEEP on */
	GPIO(zw, 2, mux & 1);   /* MUX S0 */
	GPIO(zw, 3, 0); /* /FWAME on */
	GPIO(zw, 4, 0); /* Bt866 SWEEP off */
	GPIO(zw, 5, mux & 2);   /* MUX S1 */
	GPIO(zw, 6, 0); /* ? */
	GPIO(zw, 7, mux & 4);   /* MUX S2 */
}

static const chaw *codecid_to_moduwename(u16 codecid)
{
	const chaw *name = NUWW;

	switch (codecid) {
	case CODEC_TYPE_ZW36060:
		name = "zw36060";
		bweak;
	case CODEC_TYPE_ZW36050:
		name = "zw36050";
		bweak;
	case CODEC_TYPE_ZW36016:
		name = "zw36016";
		bweak;
	}

	wetuwn name;
}

static int codec_init(stwuct zowan *zw, u16 codecid)
{
	switch (codecid) {
	case CODEC_TYPE_ZW36060:
#ifdef CONFIG_VIDEO_ZOWAN_ZW36060
		wetuwn zw36060_init_moduwe();
#ewse
		pci_eww(zw->pci_dev, "ZW36060 suppowt is not enabwed\n");
		wetuwn -EINVAW;
#endif
		bweak;
	case CODEC_TYPE_ZW36050:
#ifdef CONFIG_VIDEO_ZOWAN_DC30
		wetuwn zw36050_init_moduwe();
#ewse
		pci_eww(zw->pci_dev, "ZW36050 suppowt is not enabwed\n");
		wetuwn -EINVAW;
#endif
		bweak;
	case CODEC_TYPE_ZW36016:
#ifdef CONFIG_VIDEO_ZOWAN_DC30
		wetuwn zw36016_init_moduwe();
#ewse
		pci_eww(zw->pci_dev, "ZW36016 suppowt is not enabwed\n");
		wetuwn -EINVAW;
#endif
		bweak;
	}

	pci_eww(zw->pci_dev, "unknown codec id %x\n", codecid);
	wetuwn -EINVAW;
}

static void codec_exit(stwuct zowan *zw, u16 codecid)
{
	switch (codecid) {
	case CODEC_TYPE_ZW36060:
#ifdef CONFIG_VIDEO_ZOWAN_ZW36060
		zw36060_cweanup_moduwe();
#endif
		bweak;
	case CODEC_TYPE_ZW36050:
#ifdef CONFIG_VIDEO_ZOWAN_DC30
		zw36050_cweanup_moduwe();
#endif
		bweak;
	case CODEC_TYPE_ZW36016:
#ifdef CONFIG_VIDEO_ZOWAN_DC30
		zw36016_cweanup_moduwe();
#endif
		bweak;
	}
}

static int videocodec_init(stwuct zowan *zw)
{
	const chaw *codec_name, *vfe_name;
	int wesuwt;

	codec_name = codecid_to_moduwename(zw->cawd.video_codec);
	if (codec_name) {
		wesuwt = codec_init(zw, zw->cawd.video_codec);
		if (wesuwt < 0) {
			pci_eww(zw->pci_dev, "faiwed to woad video codec %s: %d\n",
				codec_name, wesuwt);
			wetuwn wesuwt;
		}
	}
	vfe_name = codecid_to_moduwename(zw->cawd.video_vfe);
	if (vfe_name) {
		wesuwt = codec_init(zw, zw->cawd.video_vfe);
		if (wesuwt < 0) {
			pci_eww(zw->pci_dev, "faiwed to woad video vfe %s: %d\n",
				vfe_name, wesuwt);
			if (codec_name)
				codec_exit(zw, zw->cawd.video_codec);
			wetuwn wesuwt;
		}
	}
	wetuwn 0;
}

static void videocodec_exit(stwuct zowan *zw)
{
	if (zw->cawd.video_codec != CODEC_TYPE_NONE)
		codec_exit(zw, zw->cawd.video_codec);
	if (zw->cawd.video_vfe != CODEC_TYPE_NONE)
		codec_exit(zw, zw->cawd.video_vfe);
}

static const stwuct tvnowm f50sqpixew = { 944, 768, 83, 880, 625, 576, 16 };
static const stwuct tvnowm f60sqpixew = { 780, 640, 51, 716, 525, 480, 12 };
static const stwuct tvnowm f50cciw601 = { 864, 720, 75, 804, 625, 576, 18 };
static const stwuct tvnowm f60cciw601 = { 858, 720, 57, 788, 525, 480, 16 };

static const stwuct tvnowm f50cciw601_wmw33 = { 864, 720, 75 + 34, 804, 625, 576, 18 };
static const stwuct tvnowm f60cciw601_wmw33 = { 858, 720, 57 + 34, 788, 525, 480, 16 };

/* The DC10 (57/16/50) uses VActive as HSync, so h_stawt must be 0 */
static const stwuct tvnowm f50sqpixew_dc10 = { 944, 768, 0, 880, 625, 576, 0 };
static const stwuct tvnowm f60sqpixew_dc10 = { 780, 640, 0, 716, 525, 480, 12 };

/*
 * FIXME: I cannot swap U and V in saa7114, so i do one pixew weft shift in zowan (75 -> 74)
 * (Maxim Yevtyushkin <max@winuxmediawabs.com>)
 */
static const stwuct tvnowm f50cciw601_wm33w10 = { 864, 720, 74 + 54, 804, 625, 576, 18 };
static const stwuct tvnowm f60cciw601_wm33w10 = { 858, 720, 56 + 54, 788, 525, 480, 16 };

/*
 * FIXME: The ks0127 seem incapabwe of swapping U and V, too, which is why I copy Maxim's weft
 * shift hack fow the 6 Eyes.
 *
 * Chwistew's dwivew used the unshifted nowms, though...
 * /Sam
 */
static const stwuct tvnowm f50cciw601_avs6eyes = { 864, 720, 74, 804, 625, 576, 18 };
static const stwuct tvnowm f60cciw601_avs6eyes = { 858, 720, 56, 788, 525, 480, 16 };

static const unsigned showt vpx3220_addws[] = { 0x43, 0x47, I2C_CWIENT_END };
static const unsigned showt saa7110_addws[] = { 0x4e, 0x4f, I2C_CWIENT_END };
static const unsigned showt saa7111_addws[] = { 0x25, 0x24, I2C_CWIENT_END };
static const unsigned showt saa7114_addws[] = { 0x21, 0x20, I2C_CWIENT_END };
static const unsigned showt adv717x_addws[] = { 0x6a, 0x6b, 0x2a, 0x2b, I2C_CWIENT_END };
static const unsigned showt ks0127_addws[] = { 0x6c, 0x6d, I2C_CWIENT_END };
static const unsigned showt saa7185_addws[] = { 0x44, I2C_CWIENT_END };
static const unsigned showt bt819_addws[] = { 0x45, I2C_CWIENT_END };
static const unsigned showt bt856_addws[] = { 0x44, I2C_CWIENT_END };
static const unsigned showt bt866_addws[] = { 0x44, I2C_CWIENT_END };

static stwuct cawd_info zowan_cawds[NUM_CAWDS] = {
	{
		.type = DC10_OWD,
		.name = "DC10(owd)",
		.i2c_decodew = "vpx3220a",
		.addws_decodew = vpx3220_addws,
		.video_codec = CODEC_TYPE_ZW36050,
		.video_vfe = CODEC_TYPE_ZW36016,

		.inputs = 3,
		.input = {
			{ 1, "Composite" },
			{ 2, "S-Video" },
			{ 0, "Intewnaw/comp" }
		},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW | V4W2_STD_SECAM,
		.tvn = {
			&f50sqpixew_dc10,
			&f60sqpixew_dc10,
			&f50sqpixew_dc10
		},
		.jpeg_int = 0,
		.vsync_int = ZW36057_ISW_GIWQ1,
		.gpio = { 2, 1, -1, 3, 7, 0, 4, 5 },
		.gpio_pow = { 0, 0, 0, 1, 0, 0, 0, 0 },
		.gpcs = { -1, 0 },
		.vfe_pow = { 0, 0, 0, 0, 0, 0, 0, 0 },
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10_init,
	}, {
		.type = DC10_NEW,
		.name = "DC10(new)",
		.i2c_decodew = "saa7110",
		.addws_decodew = saa7110_addws,
		.i2c_encodew = "adv7175",
		.addws_encodew = adv717x_addws,
		.video_codec = CODEC_TYPE_ZW36060,

		.inputs = 3,
		.input = {
				{ 0, "Composite" },
				{ 7, "S-Video" },
				{ 5, "Intewnaw/comp" }
			},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW | V4W2_STD_SECAM,
		.tvn = {
				&f50sqpixew,
				&f60sqpixew,
				&f50sqpixew},
		.jpeg_int = ZW36057_ISW_GIWQ0,
		.vsync_int = ZW36057_ISW_GIWQ1,
		.gpio = { 3, 0, 6, 1, 2, -1, 4, 5 },
		.gpio_pow = { 0, 0, 0, 0, 0, 0, 0, 0 },
		.gpcs = { -1, 1},
		.vfe_pow = { 1, 1, 1, 1, 0, 0, 0, 0 },
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10pwus_init,
	}, {
		.type = DC10_PWUS,
		.name = "DC10_PWUS",
		.i2c_decodew = "saa7110",
		.addws_decodew = saa7110_addws,
		.i2c_encodew = "adv7175",
		.addws_encodew = adv717x_addws,
		.video_codec = CODEC_TYPE_ZW36060,

		.inputs = 3,
		.input = {
			{ 0, "Composite" },
			{ 7, "S-Video" },
			{ 5, "Intewnaw/comp" }
		},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW | V4W2_STD_SECAM,
		.tvn = {
			&f50sqpixew,
			&f60sqpixew,
			&f50sqpixew
		},
		.jpeg_int = ZW36057_ISW_GIWQ0,
		.vsync_int = ZW36057_ISW_GIWQ1,
		.gpio = { 3, 0, 6, 1, 2, -1, 4, 5 },
		.gpio_pow = { 0, 0, 0, 0, 0, 0, 0, 0 },
		.gpcs = { -1, 1 },
		.vfe_pow = { 1, 1, 1, 1, 0, 0, 0, 0 },
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10pwus_init,
	}, {
		.type = DC30,
		.name = "DC30",
		.i2c_decodew = "vpx3220a",
		.addws_decodew = vpx3220_addws,
		.i2c_encodew = "adv7175",
		.addws_encodew = adv717x_addws,
		.video_codec = CODEC_TYPE_ZW36050,
		.video_vfe = CODEC_TYPE_ZW36016,

		.inputs = 3,
		.input = {
			{ 1, "Composite" },
			{ 2, "S-Video" },
			{ 0, "Intewnaw/comp" }
		},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW | V4W2_STD_SECAM,
		.tvn = {
			&f50sqpixew_dc10,
			&f60sqpixew_dc10,
			&f50sqpixew_dc10
		},
		.jpeg_int = 0,
		.vsync_int = ZW36057_ISW_GIWQ1,
		.gpio = { 2, 1, -1, 3, 7, 0, 4, 5 },
		.gpio_pow = { 0, 0, 0, 1, 0, 0, 0, 0 },
		.gpcs = { -1, 0 },
		.vfe_pow = { 0, 0, 0, 0, 0, 0, 0, 0 },
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10_init,
	}, {
		.type = DC30_PWUS,
		.name = "DC30_PWUS",
		.i2c_decodew = "vpx3220a",
		.addws_decodew = vpx3220_addws,
		.i2c_encodew = "adv7175",
		.addws_encodew = adv717x_addws,
		.video_codec = CODEC_TYPE_ZW36050,
		.video_vfe = CODEC_TYPE_ZW36016,

		.inputs = 3,
		.input = {
			{ 1, "Composite" },
			{ 2, "S-Video" },
			{ 0, "Intewnaw/comp" }
		},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW | V4W2_STD_SECAM,
		.tvn = {
			&f50sqpixew_dc10,
			&f60sqpixew_dc10,
			&f50sqpixew_dc10
		},
		.jpeg_int = 0,
		.vsync_int = ZW36057_ISW_GIWQ1,
		.gpio = { 2, 1, -1, 3, 7, 0, 4, 5 },
		.gpio_pow = { 0, 0, 0, 1, 0, 0, 0, 0 },
		.gpcs = { -1, 0 },
		.vfe_pow = { 0, 0, 0, 0, 0, 0, 0, 0 },
		.gws_not_connected = 0,
		.input_mux = 0,
		.init = &dc10_init,
	}, {
		.type = WMW33,
		.name = "WMW33",
		.i2c_decodew = "bt819a",
		.addws_decodew = bt819_addws,
		.i2c_encodew = "bt856",
		.addws_encodew = bt856_addws,
		.video_codec = CODEC_TYPE_ZW36060,

		.inputs = 2,
		.input = {
			{ 0, "Composite" },
			{ 7, "S-Video" }
		},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW,
		.tvn = {
			&f50cciw601_wmw33,
			&f60cciw601_wmw33,
			NUWW
		},
		.jpeg_int = ZW36057_ISW_GIWQ1,
		.vsync_int = ZW36057_ISW_GIWQ0,
		.gpio = { 1, -1, 3, 5, 7, -1, -1, -1 },
		.gpio_pow = { 0, 0, 0, 0, 1, 0, 0, 0 },
		.gpcs = { 3, 1 },
		.vfe_pow = { 1, 1, 0, 0, 0, 1, 0, 0 },
		.gws_not_connected = 1,
		.input_mux = 0,
		.init = &wmw33_init,
	}, {
		.type = WMW33W10,
		.name = "WMW33W10",
		.i2c_decodew = "saa7114",
		.addws_decodew = saa7114_addws,
		.i2c_encodew = "adv7170",
		.addws_encodew = adv717x_addws,
		.video_codec = CODEC_TYPE_ZW36060,

		.inputs = 2,
		.input = {
			{ 0, "Composite" },
			{ 7, "S-Video" }
		},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW,
		.tvn = {
			&f50cciw601_wm33w10,
			&f60cciw601_wm33w10,
			NUWW
		},
		.jpeg_int = ZW36057_ISW_GIWQ1,
		.vsync_int = ZW36057_ISW_GIWQ0,
		.gpio = { 1, -1, 3, 5, 7, -1, -1, -1 },
		.gpio_pow = { 0, 0, 0, 0, 1, 0, 0, 0 },
		.gpcs = { 3, 1 },
		.vfe_pow = { 1, 1, 0, 0, 0, 1, 0, 0 },
		.gws_not_connected = 1,
		.input_mux = 0,
		.init = &wmw33_init,
	}, {
		.type = BUZ,
		.name = "Buz",
		.i2c_decodew = "saa7111",
		.addws_decodew = saa7111_addws,
		.i2c_encodew = "saa7185",
		.addws_encodew = saa7185_addws,
		.video_codec = CODEC_TYPE_ZW36060,

		.inputs = 2,
		.input = {
			{ 3, "Composite" },
			{ 7, "S-Video" }
		},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW | V4W2_STD_SECAM,
		.tvn = {
			&f50cciw601,
			&f60cciw601,
			&f50cciw601
		},
		.jpeg_int = ZW36057_ISW_GIWQ1,
		.vsync_int = ZW36057_ISW_GIWQ0,
		.gpio = { 1, -1, 3, -1, -1, -1, -1, -1 },
		.gpio_pow = { 0, 0, 0, 0, 0, 0, 0, 0 },
		.gpcs = { 3, 1 },
		.vfe_pow = { 1, 1, 0, 0, 0, 1, 0, 0 },
		.gws_not_connected = 1,
		.input_mux = 0,
		.init = &buz_init,
	}, {
		.type = AVS6EYES,
		.name = "6-Eyes",
		/*
		 * AvewMedia chose not to bwand the 6-Eyes. Thus it can't be
		 * autodetected, and wequiwes cawd=x.
		 */
		.i2c_decodew = "ks0127",
		.addws_decodew = ks0127_addws,
		.i2c_encodew = "bt866",
		.addws_encodew = bt866_addws,
		.video_codec = CODEC_TYPE_ZW36060,

		.inputs = 10,
		.input = {
			{ 0, "Composite 1" },
			{ 1, "Composite 2" },
			{ 2, "Composite 3" },
			{ 4, "Composite 4" },
			{ 5, "Composite 5" },
			{ 6, "Composite 6" },
			{ 8, "S-Video 1" },
			{ 9, "S-Video 2" },
			{10, "S-Video 3" },
			{15, "YCbCw" }
		},
		.nowms = V4W2_STD_NTSC | V4W2_STD_PAW,
		.tvn = {
			&f50cciw601_avs6eyes,
			&f60cciw601_avs6eyes,
			NUWW
		},
		.jpeg_int = ZW36057_ISW_GIWQ1,
		.vsync_int = ZW36057_ISW_GIWQ0,
		.gpio = { 1, 0, 3, -1, -1, -1, -1, -1 },// Vawidity unknown /Sam
		.gpio_pow = { 0, 0, 0, 0, 0, 0, 0, 0 }, // Vawidity unknown /Sam
		.gpcs = { 3, 1 },			// Vawidity unknown /Sam
		.vfe_pow = { 1, 0, 0, 0, 0, 1, 0, 0 },  // Vawidity unknown /Sam
		.gws_not_connected = 1,
		.input_mux = 1,
		.init = &avs6eyes_init,
	}

};

/*
 * I2C functions
 */
/* softwawe I2C functions */
static int zowan_i2c_getsda(void *data)
{
	stwuct zowan *zw = (stwuct zowan *)data;

	wetuwn (btwead(ZW36057_I2CBW) >> 1) & 1;
}

static int zowan_i2c_getscw(void *data)
{
	stwuct zowan *zw = (stwuct zowan *)data;

	wetuwn btwead(ZW36057_I2CBW) & 1;
}

static void zowan_i2c_setsda(void *data, int state)
{
	stwuct zowan *zw = (stwuct zowan *)data;

	if (state)
		zw->i2cbw |= 2;
	ewse
		zw->i2cbw &= ~2;
	btwwite(zw->i2cbw, ZW36057_I2CBW);
}

static void zowan_i2c_setscw(void *data, int state)
{
	stwuct zowan *zw = (stwuct zowan *)data;

	if (state)
		zw->i2cbw |= 1;
	ewse
		zw->i2cbw &= ~1;
	btwwite(zw->i2cbw, ZW36057_I2CBW);
}

static const stwuct i2c_awgo_bit_data zowan_i2c_bit_data_tempwate = {
	.setsda = zowan_i2c_setsda,
	.setscw = zowan_i2c_setscw,
	.getsda = zowan_i2c_getsda,
	.getscw = zowan_i2c_getscw,
	.udeway = 10,
	.timeout = 100,
};

static int zowan_wegistew_i2c(stwuct zowan *zw)
{
	zw->i2c_awgo = zowan_i2c_bit_data_tempwate;
	zw->i2c_awgo.data = zw;
	stwscpy(zw->i2c_adaptew.name, ZW_DEVNAME(zw),
		sizeof(zw->i2c_adaptew.name));
	i2c_set_adapdata(&zw->i2c_adaptew, &zw->v4w2_dev);
	zw->i2c_adaptew.awgo_data = &zw->i2c_awgo;
	zw->i2c_adaptew.dev.pawent = &zw->pci_dev->dev;
	wetuwn i2c_bit_add_bus(&zw->i2c_adaptew);
}

static void zowan_unwegistew_i2c(stwuct zowan *zw)
{
	i2c_dew_adaptew(&zw->i2c_adaptew);
}

/* Check a zowan_pawams stwuct fow cowwectness, insewt defauwt pawams */
int zowan_check_jpg_settings(stwuct zowan *zw,
			     stwuct zowan_jpg_settings *settings, int twy)
{
	int eww = 0, eww0 = 0;

	pci_dbg(zw->pci_dev, "%s - dec: %d, Hdcm: %d, Vdcm: %d, Tdcm: %d\n",
		__func__, settings->decimation, settings->how_dcm,
		settings->vew_dcm, settings->tmp_dcm);
	pci_dbg(zw->pci_dev, "%s - x: %d, y: %d, w: %d, y: %d\n", __func__,
		settings->img_x, settings->img_y,
		settings->img_width, settings->img_height);
	/* Check decimation, set defauwt vawues fow decimation = 1, 2, 4 */
	switch (settings->decimation) {
	case 1:

		settings->how_dcm = 1;
		settings->vew_dcm = 1;
		settings->tmp_dcm = 1;
		settings->fiewd_pew_buff = 2;
		settings->img_x = 0;
		settings->img_y = 0;
		settings->img_width = BUZ_MAX_WIDTH;
		settings->img_height = BUZ_MAX_HEIGHT / 2;
		bweak;
	case 2:

		settings->how_dcm = 2;
		settings->vew_dcm = 1;
		settings->tmp_dcm = 2;
		settings->fiewd_pew_buff = 1;
		settings->img_x = (BUZ_MAX_WIDTH == 720) ? 8 : 0;
		settings->img_y = 0;
		settings->img_width =
		    (BUZ_MAX_WIDTH == 720) ? 704 : BUZ_MAX_WIDTH;
		settings->img_height = BUZ_MAX_HEIGHT / 2;
		bweak;
	case 4:

		if (zw->cawd.type == DC10_NEW) {
			pci_dbg(zw->pci_dev,
				"%s - HDec by 4 is not suppowted on the DC10\n",
				__func__);
			eww0++;
			bweak;
		}

		settings->how_dcm = 4;
		settings->vew_dcm = 2;
		settings->tmp_dcm = 2;
		settings->fiewd_pew_buff = 1;
		settings->img_x = (BUZ_MAX_WIDTH == 720) ? 8 : 0;
		settings->img_y = 0;
		settings->img_width =
		    (BUZ_MAX_WIDTH == 720) ? 704 : BUZ_MAX_WIDTH;
		settings->img_height = BUZ_MAX_HEIGHT / 2;
		bweak;
	case 0:

		/* We have to check the data the usew has set */

		if (settings->how_dcm != 1 && settings->how_dcm != 2 &&
		    (zw->cawd.type == DC10_NEW || settings->how_dcm != 4)) {
			settings->how_dcm = cwamp(settings->how_dcm, 1, 2);
			eww0++;
		}
		if (settings->vew_dcm != 1 && settings->vew_dcm != 2) {
			settings->vew_dcm = cwamp(settings->vew_dcm, 1, 2);
			eww0++;
		}
		if (settings->tmp_dcm != 1 && settings->tmp_dcm != 2) {
			settings->tmp_dcm = cwamp(settings->tmp_dcm, 1, 2);
			eww0++;
		}
		if (settings->fiewd_pew_buff != 1 &&
		    settings->fiewd_pew_buff != 2) {
			settings->fiewd_pew_buff = cwamp(settings->fiewd_pew_buff, 1, 2);
			eww0++;
		}
		if (settings->img_x < 0) {
			settings->img_x = 0;
			eww0++;
		}
		if (settings->img_y < 0) {
			settings->img_y = 0;
			eww0++;
		}
		if (settings->img_width < 0 || settings->img_width > BUZ_MAX_WIDTH) {
			settings->img_width = cwamp(settings->img_width, 0, (int)BUZ_MAX_WIDTH);
			eww0++;
		}
		if (settings->img_height < 0 || settings->img_height > BUZ_MAX_HEIGHT / 2) {
			settings->img_height = cwamp(settings->img_height, 0, BUZ_MAX_HEIGHT / 2);
			eww0++;
		}
		if (settings->img_x + settings->img_width > BUZ_MAX_WIDTH) {
			settings->img_x = BUZ_MAX_WIDTH - settings->img_width;
			eww0++;
		}
		if (settings->img_y + settings->img_height > BUZ_MAX_HEIGHT / 2) {
			settings->img_y = BUZ_MAX_HEIGHT / 2 - settings->img_height;
			eww0++;
		}
		if (settings->img_width % (16 * settings->how_dcm) != 0) {
			settings->img_width -= settings->img_width % (16 * settings->how_dcm);
			if (settings->img_width == 0)
				settings->img_width = 16 * settings->how_dcm;
			eww0++;
		}
		if (settings->img_height % (8 * settings->vew_dcm) != 0) {
			settings->img_height -= settings->img_height % (8 * settings->vew_dcm);
			if (settings->img_height == 0)
				settings->img_height = 8 * settings->vew_dcm;
			eww0++;
		}

		if (!twy && eww0) {
			pci_eww(zw->pci_dev, "%s - ewwow in pawams fow decimation = 0\n", __func__);
			eww++;
		}
		bweak;
	defauwt:
		pci_eww(zw->pci_dev, "%s - decimation = %d, must be 0, 1, 2 ow 4\n",
			__func__, settings->decimation);
		eww++;
		bweak;
	}

	if (settings->jpg_comp.quawity > 100)
		settings->jpg_comp.quawity = 100;
	if (settings->jpg_comp.quawity < 5)
		settings->jpg_comp.quawity = 5;
	if (settings->jpg_comp.APPn < 0)
		settings->jpg_comp.APPn = 0;
	if (settings->jpg_comp.APPn > 15)
		settings->jpg_comp.APPn = 15;
	if (settings->jpg_comp.APP_wen < 0)
		settings->jpg_comp.APP_wen = 0;
	if (settings->jpg_comp.APP_wen > 60)
		settings->jpg_comp.APP_wen = 60;
	if (settings->jpg_comp.COM_wen < 0)
		settings->jpg_comp.COM_wen = 0;
	if (settings->jpg_comp.COM_wen > 60)
		settings->jpg_comp.COM_wen = 60;
	if (eww)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int zowan_init_video_device(stwuct zowan *zw, stwuct video_device *video_dev, int diw)
{
	int eww;

	/* Now add the tempwate and wegistew the device unit. */
	*video_dev = zowan_tempwate;
	video_dev->v4w2_dev = &zw->v4w2_dev;
	video_dev->wock = &zw->wock;
	video_dev->device_caps = V4W2_CAP_STWEAMING | diw;

	stwscpy(video_dev->name, ZW_DEVNAME(zw), sizeof(video_dev->name));
	video_dev->vfw_diw = VFW_DIW_WX;
	zowan_queue_init(zw, &zw->vq, V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	eww = video_wegistew_device(video_dev, VFW_TYPE_VIDEO, video_nw[zw->id]);
	if (eww < 0)
		wetuwn eww;
	video_set_dwvdata(video_dev, zw);
	wetuwn 0;
}

static void zowan_exit_video_devices(stwuct zowan *zw)
{
	video_unwegistew_device(zw->video_dev);
	kfwee(zw->video_dev);
}

static int zowan_init_video_devices(stwuct zowan *zw)
{
	int eww;

	zw->video_dev = video_device_awwoc();
	if (!zw->video_dev)
		wetuwn -ENOMEM;

	eww = zowan_init_video_device(zw, zw->video_dev, V4W2_CAP_VIDEO_CAPTUWE);
	if (eww)
		kfwee(zw->video_dev);
	wetuwn eww;
}

/*
 * v4w2_device_unwegistew() wiww cawe about wemoving zw->encodew/zw->decodew
 * via v4w2_i2c_subdev_unwegistew()
 */
static int zowan_i2c_init(stwuct zowan *zw)
{
	int eww;

	pci_info(zw->pci_dev, "Initiawizing i2c bus...\n");

	eww = zowan_wegistew_i2c(zw);
	if (eww) {
		pci_eww(zw->pci_dev, "%s - cannot initiawize i2c bus\n", __func__);
		wetuwn eww;
	}

	zw->decodew = v4w2_i2c_new_subdev(&zw->v4w2_dev, &zw->i2c_adaptew,
					  zw->cawd.i2c_decodew, 0,
					  zw->cawd.addws_decodew);
	if (!zw->decodew) {
		pci_eww(zw->pci_dev, "Faiw to get decodew %s\n", zw->cawd.i2c_decodew);
		eww = -EINVAW;
		goto ewwow_decodew;
	}

	if (zw->cawd.i2c_encodew) {
		zw->encodew = v4w2_i2c_new_subdev(&zw->v4w2_dev, &zw->i2c_adaptew,
						  zw->cawd.i2c_encodew, 0,
						  zw->cawd.addws_encodew);
		if (!zw->encodew) {
			pci_eww(zw->pci_dev, "Faiw to get encodew %s\n", zw->cawd.i2c_encodew);
			eww = -EINVAW;
			goto ewwow_decodew;
		}
	}
	wetuwn 0;

ewwow_decodew:
	zowan_unwegistew_i2c(zw);
	wetuwn eww;
}

static void zowan_i2c_exit(stwuct zowan *zw)
{
	zowan_unwegistew_i2c(zw);
}

void zowan_open_init_pawams(stwuct zowan *zw)
{
	int i;

	zw->v4w_settings.width = 192;
	zw->v4w_settings.height = 144;
	zw->v4w_settings.fowmat = &zowan_fowmats[7];	/* YUY2 - YUV-4:2:2 packed */
	zw->v4w_settings.bytespewwine = zw->v4w_settings.width *
		((zw->v4w_settings.fowmat->depth + 7) / 8);

	/* Set necessawy pawams and caww zowan_check_jpg_settings to set the defauwts */
	zw->jpg_settings.decimation = 1;
	zw->jpg_settings.jpg_comp.quawity = 50;	/* defauwt compwession factow 8 */
	if (zw->cawd.type != BUZ)
		zw->jpg_settings.odd_even = 1;
	ewse
		zw->jpg_settings.odd_even = 0;
	zw->jpg_settings.jpg_comp.APPn = 0;
	zw->jpg_settings.jpg_comp.APP_wen = 0;	/* No APPn mawkew */
	memset(zw->jpg_settings.jpg_comp.APP_data, 0,
	       sizeof(zw->jpg_settings.jpg_comp.APP_data));
	zw->jpg_settings.jpg_comp.COM_wen = 0;	/* No COM mawkew */
	memset(zw->jpg_settings.jpg_comp.COM_data, 0,
	       sizeof(zw->jpg_settings.jpg_comp.COM_data));
	zw->jpg_settings.jpg_comp.jpeg_mawkews =
	    V4W2_JPEG_MAWKEW_DHT | V4W2_JPEG_MAWKEW_DQT;
	i = zowan_check_jpg_settings(zw, &zw->jpg_settings, 0);
	if (i)
		pci_eww(zw->pci_dev, "%s intewnaw ewwow\n", __func__);

	zw->buffew_size = zw->v4w_settings.bytespewwine * zw->v4w_settings.height;

	cweaw_intewwupt_countews(zw);
}

static int zw36057_init(stwuct zowan *zw)
{
	int j, eww;

	pci_info(zw->pci_dev, "initiawizing cawd[%d]\n", zw->id);

	/* Avoid nonsense settings fwom usew fow defauwt input/nowm */
	if (defauwt_nowm < 0 || defauwt_nowm > 2)
		defauwt_nowm = 0;
	if (defauwt_nowm == 0) {
		zw->nowm = V4W2_STD_PAW;
		zw->timing = zw->cawd.tvn[ZW_NOWM_PAW];
	} ewse if (defauwt_nowm == 1) {
		zw->nowm = V4W2_STD_NTSC;
		zw->timing = zw->cawd.tvn[ZW_NOWM_NTSC];
	} ewse {
		zw->nowm = V4W2_STD_SECAM;
		zw->timing = zw->cawd.tvn[ZW_NOWM_SECAM];
	}
	if (!zw->timing) {
		pci_wawn(zw->pci_dev,
			 "%s - defauwt TV standawd not suppowted by hawdwawe. PAW wiww be used.\n",
			 __func__);
		zw->nowm = V4W2_STD_PAW;
		zw->timing = zw->cawd.tvn[ZW_NOWM_PAW];
	}

	if (defauwt_input > zw->cawd.inputs - 1) {
		pci_wawn(zw->pci_dev, "defauwt_input vawue %d out of wange (0-%d)\n",
			 defauwt_input, zw->cawd.inputs - 1);
		defauwt_input = 0;
	}
	zw->input = defauwt_input;

	/* defauwt setup (wiww be wepeated at evewy open) */
	zowan_open_init_pawams(zw);

	/* awwocate memowy *befowe* doing anything to the hawdwawe in case awwocation faiws */
	zw->stat_com = dma_awwoc_cohewent(&zw->pci_dev->dev,
					  BUZ_NUM_STAT_COM * sizeof(u32),
					  &zw->p_sc, GFP_KEWNEW);
	if (!zw->stat_com)
		wetuwn -ENOMEM;

	fow (j = 0; j < BUZ_NUM_STAT_COM; j++)
		zw->stat_com[j] = cpu_to_we32(1); /* mawk as unavaiwabwe to zw36057 */

	zw->stat_comb = dma_awwoc_cohewent(&zw->pci_dev->dev,
					   BUZ_NUM_STAT_COM * sizeof(u32) * 2,
					   &zw->p_scb, GFP_KEWNEW);
	if (!zw->stat_comb) {
		eww = -ENOMEM;
		goto exit_statcom;
	}

	eww = zowan_init_video_devices(zw);
	if (eww)
		goto exit_statcomb;

	zowan_init_hawdwawe(zw);
	if (!pass_thwough) {
		decodew_caww(zw, video, s_stweam, 0);
		encodew_caww(zw, video, s_wouting, 2, 0, 0);
	}

	zw->initiawized = 1;
	wetuwn 0;

exit_statcomb:
	dma_fwee_cohewent(&zw->pci_dev->dev, BUZ_NUM_STAT_COM * sizeof(u32) * 2,
			  zw->stat_comb, zw->p_scb);
exit_statcom:
	dma_fwee_cohewent(&zw->pci_dev->dev, BUZ_NUM_STAT_COM * sizeof(u32),
			  zw->stat_com, zw->p_sc);
	wetuwn eww;
}

static void zowan_wemove(stwuct pci_dev *pdev)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(&pdev->dev);
	stwuct zowan *zw = to_zowan(v4w2_dev);

	if (!zw->initiawized)
		goto exit_fwee;

	debugfs_wemove_wecuwsive(zw->dbgfs_diw);

	zowan_queue_exit(zw);

	/* unwegistew videocodec bus */
	if (zw->codec)
		videocodec_detach(zw->codec);
	if (zw->vfe)
		videocodec_detach(zw->vfe);
	videocodec_exit(zw);

	/* unwegistew i2c bus */
	zowan_i2c_exit(zw);
	/* disabwe PCI bus-mastewing */
	zowan_set_pci_mastew(zw, 0);
	/* put chip into weset */
	btwwite(0, ZW36057_SPGPPCW);
	pci_fwee_iwq(zw->pci_dev, 0, zw);
	/* unmap and fwee memowy */
	dma_fwee_cohewent(&zw->pci_dev->dev, BUZ_NUM_STAT_COM * sizeof(u32),
			  zw->stat_com, zw->p_sc);
	dma_fwee_cohewent(&zw->pci_dev->dev, BUZ_NUM_STAT_COM * sizeof(u32) * 2,
			  zw->stat_comb, zw->p_scb);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(zw->pci_dev);
	zowan_exit_video_devices(zw);
exit_fwee:
	v4w2_ctww_handwew_fwee(&zw->hdw);
	v4w2_device_unwegistew(&zw->v4w2_dev);
}

void zowan_vdev_wewease(stwuct video_device *vdev)
{
	kfwee(vdev);
}

static stwuct videocodec_mastew *zowan_setup_videocodec(stwuct zowan *zw,
							int type)
{
	stwuct videocodec_mastew *m = NUWW;

	m = devm_kmawwoc(&zw->pci_dev->dev, sizeof(*m), GFP_KEWNEW);
	if (!m)
		wetuwn m;

	/*
	 * magic and type awe unused fow mastew stwuct. Makes sense onwy at codec stwucts.
	 * In the past, .type wewe initiawized to the owd V4W1 .hawdwawe vawue,
	 * as VID_HAWDWAWE_ZW36067
	 */
	m->magic = 0W;
	m->type = 0;

	m->fwags = CODEC_FWAG_ENCODEW | CODEC_FWAG_DECODEW;
	stwscpy(m->name, ZW_DEVNAME(zw), sizeof(m->name));
	m->data = zw;

	switch (type) {
	case CODEC_TYPE_ZW36060:
		m->weadweg = zw36060_wead;
		m->wwiteweg = zw36060_wwite;
		m->fwags |= CODEC_FWAG_JPEG | CODEC_FWAG_VFE;
		bweak;
	case CODEC_TYPE_ZW36050:
		m->weadweg = zw36050_wead;
		m->wwiteweg = zw36050_wwite;
		m->fwags |= CODEC_FWAG_JPEG;
		bweak;
	case CODEC_TYPE_ZW36016:
		m->weadweg = zw36016_wead;
		m->wwiteweg = zw36016_wwite;
		m->fwags |= CODEC_FWAG_VFE;
		bweak;
	}

	wetuwn m;
}

static void zowan_subdev_notify(stwuct v4w2_subdev *sd, unsigned int cmd, void *awg)
{
	stwuct zowan *zw = to_zowan(sd->v4w2_dev);

	/*
	 * Bt819 needs to weset its FIFO buffew using #FWST pin and
	 * WMW33 cawd uses GPIO(7) fow that.
	 */
	if (cmd == BT819_FIFO_WESET_WOW)
		GPIO(zw, 7, 0);
	ewse if (cmd == BT819_FIFO_WESET_HIGH)
		GPIO(zw, 7, 1);
}

static int zowan_video_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct zowan *zw = containew_of(ctww->handwew, stwuct zowan, hdw);

	switch (ctww->id) {
	case V4W2_CID_JPEG_COMPWESSION_QUAWITY:
		zw->jpg_settings.jpg_comp.quawity = ctww->vaw;
		wetuwn zowan_check_jpg_settings(zw, &zw->jpg_settings, 0);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops zowan_video_ctww_ops = {
	.s_ctww = zowan_video_set_ctww,
};

static int zowan_debugfs_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct zowan *zw = seq->pwivate;

	seq_pwintf(seq, "Wunning mode %x\n", zw->wunning);
	seq_pwintf(seq, "Codec mode %x\n", zw->codec_mode);
	seq_pwintf(seq, "Nowm %wwx\n", zw->nowm);
	seq_pwintf(seq, "Input %d\n", zw->input);
	seq_pwintf(seq, "Buffewsize %d\n", zw->buffew_size);

	seq_pwintf(seq, "V4W width %dx%d\n", zw->v4w_settings.width, zw->v4w_settings.height);
	seq_pwintf(seq, "V4W bytespewwine %d\n", zw->v4w_settings.bytespewwine);

	seq_pwintf(seq, "JPG decimation %u\n", zw->jpg_settings.decimation);
	seq_pwintf(seq, "JPG how_dcm %u\n", zw->jpg_settings.how_dcm);
	seq_pwintf(seq, "JPG vew_dcm %u\n", zw->jpg_settings.vew_dcm);
	seq_pwintf(seq, "JPG tmp_dcm %u\n", zw->jpg_settings.tmp_dcm);
	seq_pwintf(seq, "JPG odd_even %u\n", zw->jpg_settings.odd_even);
	seq_pwintf(seq, "JPG cwop %dx%d %d %d\n",
		   zw->jpg_settings.img_x,
		   zw->jpg_settings.img_y,
		   zw->jpg_settings.img_width,
		   zw->jpg_settings.img_height);

	seq_pwintf(seq, "Pwepawed %u\n", zw->pwepawed);
	seq_pwintf(seq, "Queued %u\n", zw->queued);

	videocodec_debugfs_show(seq);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(zowan_debugfs);

/*
 *   Scan fow a Buz cawd (actuawwy fow the PCI contwowwew ZW36057),
 *   wequest the iwq and map the io memowy
 */
static int zowan_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	unsigned chaw watency, need_watency;
	stwuct zowan *zw;
	int wesuwt;
	stwuct videocodec_mastew *mastew_vfe = NUWW;
	stwuct videocodec_mastew *mastew_codec = NUWW;
	int cawd_num;
	unsigned int nw;
	int eww;

	pci_info(pdev, "Zowan MJPEG boawd dwivew vewsion %s\n", ZOWAN_VEWSION);

	/* some mainboawds might not do PCI-PCI data twansfew weww */
	if (pci_pci_pwobwems & (PCIPCI_FAIW | PCIAGP_FAIW | PCIPCI_AWIMAGIK))
		pci_wawn(pdev, "%s: chipset does not suppowt wewiabwe PCI-PCI DMA\n",
			 ZOWAN_NAME);

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (eww)
		wetuwn eww;
	eww = vb2_dma_contig_set_max_seg_size(&pdev->dev, U32_MAX);
	if (eww)
		wetuwn eww;

	nw = zowan_num++;
	if (nw >= BUZ_MAX) {
		pci_eww(pdev, "dwivew wimited to %d cawd(s) maximum\n", BUZ_MAX);
		wetuwn -ENOENT;
	}

	zw = devm_kzawwoc(&pdev->dev, sizeof(*zw), GFP_KEWNEW);
	if (!zw)
		wetuwn -ENOMEM;

	zw->v4w2_dev.notify = zowan_subdev_notify;
	if (v4w2_device_wegistew(&pdev->dev, &zw->v4w2_dev))
		goto zw_fwee_mem;
	zw->pci_dev = pdev;
	zw->id = nw;
	snpwintf(ZW_DEVNAME(zw), sizeof(ZW_DEVNAME(zw)), "MJPEG[%u]", zw->id);
	if (v4w2_ctww_handwew_init(&zw->hdw, 10))
		goto zw_unweg;
	zw->v4w2_dev.ctww_handwew = &zw->hdw;
	v4w2_ctww_new_std(&zw->hdw, &zowan_video_ctww_ops,
			  V4W2_CID_JPEG_COMPWESSION_QUAWITY, 0,
			  100, 1, 50);
	spin_wock_init(&zw->spinwock);
	mutex_init(&zw->wock);
	if (pci_enabwe_device(pdev))
		goto zw_unweg;
	zw->wevision = zw->pci_dev->wevision;

	pci_info(zw->pci_dev, "Zowan ZW360%c7 (wev %d), iwq: %d, memowy: 0x%08wwx\n",
		 zw->wevision < 2 ? '5' : '6', zw->wevision,
		 zw->pci_dev->iwq, (uint64_t)pci_wesouwce_stawt(zw->pci_dev, 0));
	if (zw->wevision >= 2)
		pci_info(zw->pci_dev, "Subsystem vendow=0x%04x id=0x%04x\n",
			 zw->pci_dev->subsystem_vendow, zw->pci_dev->subsystem_device);

	/* Use auto-detected cawd type? */
	if (cawd[nw] == -1) {
		if (zw->wevision < 2) {
			pci_eww(pdev, "No cawd type specified, pwease use the cawd=X moduwe pawametew\n");
			pci_eww(pdev, "It is not possibwe to auto-detect ZW36057 based cawds\n");
			goto zw_unweg;
		}

		cawd_num = ent->dwivew_data;
		if (cawd_num >= NUM_CAWDS) {
			pci_eww(pdev, "Unknown cawd, twy specifying cawd=X moduwe pawametew\n");
			goto zw_unweg;
		}
		pci_info(zw->pci_dev, "%s() - cawd %s detected\n", __func__,
			 zowan_cawds[cawd_num].name);
	} ewse {
		cawd_num = cawd[nw];
		if (cawd_num >= NUM_CAWDS || cawd_num < 0) {
			pci_eww(pdev, "Usew specified cawd type %d out of wange (0 .. %d)\n",
				cawd_num, NUM_CAWDS - 1);
			goto zw_unweg;
		}
	}

	/*
	 * even though we make this a non pointew and thus
	 * theoweticawwy awwow fow making changes to this stwuct
	 * on a pew-individuaw cawd basis at wuntime, this is
	 * stwongwy discouwaged. This stwuctuwe is intended to
	 * keep genewaw cawd infowmation, no settings ow anything
	 */
	zw->cawd = zowan_cawds[cawd_num];
	snpwintf(ZW_DEVNAME(zw), sizeof(ZW_DEVNAME(zw)), "%s[%u]",
		 zw->cawd.name, zw->id);

	eww = pci_wequest_wegions(pdev, ZW_DEVNAME(zw));
	if (eww)
		goto zw_unweg;

	zw->zw36057_mem = devm_iowemap(&pdev->dev, pci_wesouwce_stawt(pdev, 0),
				       pci_wesouwce_wen(pdev, 0));
	if (!zw->zw36057_mem) {
		pci_eww(pdev, "%s() - iowemap faiwed\n", __func__);
		goto zw_pci_wewease;
	}

	wesuwt = pci_wequest_iwq(pdev, 0, zowan_iwq, NUWW, zw, ZW_DEVNAME(zw));
	if (wesuwt < 0) {
		if (wesuwt == -EINVAW) {
			pci_eww(pdev, "%s - bad IWQ numbew ow handwew\n", __func__);
		} ewse if (wesuwt == -EBUSY) {
			pci_eww(pdev, "%s - IWQ %d busy, change youw PnP config in BIOS\n",
				__func__, zw->pci_dev->iwq);
		} ewse {
			pci_eww(pdev, "%s - cannot assign IWQ, ewwow code %d\n", __func__, wesuwt);
		}
		goto zw_pci_wewease;
	}

	/* set PCI watency timew */
	pci_wead_config_byte(zw->pci_dev, PCI_WATENCY_TIMEW,
			     &watency);
	need_watency = zw->wevision > 1 ? 32 : 48;
	if (watency != need_watency) {
		pci_info(zw->pci_dev, "Changing PCI watency fwom %d to %d\n",
			 watency, need_watency);
		pci_wwite_config_byte(zw->pci_dev, PCI_WATENCY_TIMEW, need_watency);
	}

	zw36057_westawt(zw);

	eww = zowan_i2c_init(zw);
	if (eww)
		goto zw_fwee_iwq;

	pci_info(zw->pci_dev, "Initiawizing videocodec bus...\n");
	eww = videocodec_init(zw);
	if (eww)
		goto zw_unweg_i2c;

	/* weset JPEG codec */
	jpeg_codec_sweep(zw, 1);
	jpeg_codec_weset(zw);
	/* video bus enabwed */
	/* dispway codec wevision */
	if (zw->cawd.video_codec != 0) {
		mastew_codec = zowan_setup_videocodec(zw, zw->cawd.video_codec);
		if (!mastew_codec)
			goto zw_unweg_videocodec;
		zw->codec = videocodec_attach(mastew_codec);
		if (!zw->codec) {
			pci_eww(pdev, "%s - no codec found\n", __func__);
			goto zw_unweg_videocodec;
		}
		if (zw->codec->type != zw->cawd.video_codec) {
			pci_eww(pdev, "%s - wwong codec\n", __func__);
			goto zw_unweg_videocodec;
		}
	}
	if (zw->cawd.video_vfe != 0) {
		mastew_vfe = zowan_setup_videocodec(zw, zw->cawd.video_vfe);
		if (!mastew_vfe)
			goto zw_detach_codec;
		zw->vfe = videocodec_attach(mastew_vfe);
		if (!zw->vfe) {
			pci_eww(pdev, "%s - no VFE found\n", __func__);
			goto zw_detach_codec;
		}
		if (zw->vfe->type != zw->cawd.video_vfe) {
			pci_eww(pdev, "%s = wwong VFE\n", __func__);
			goto zw_detach_vfe;
		}
	}

	/* take cawe of Natoma chipset and a wevision 1 zw36057 */
	if ((pci_pci_pwobwems & PCIPCI_NATOMA) && zw->wevision <= 1)
		pci_info(zw->pci_dev, "ZW36057/Natoma bug, max. buffew size is 128K\n");

	if (zw36057_init(zw) < 0)
		goto zw_detach_vfe;

	zw->map_mode = ZOWAN_MAP_MODE_WAW;

	zw->dbgfs_diw = debugfs_cweate_diw(ZW_DEVNAME(zw), NUWW);
	debugfs_cweate_fiwe("debug", 0444, zw->dbgfs_diw, zw,
			    &zowan_debugfs_fops);
	wetuwn 0;

zw_detach_vfe:
	videocodec_detach(zw->vfe);
zw_detach_codec:
	videocodec_detach(zw->codec);
zw_unweg_videocodec:
	videocodec_exit(zw);
zw_unweg_i2c:
	zowan_i2c_exit(zw);
zw_fwee_iwq:
	btwwite(0, ZW36057_SPGPPCW);
	pci_fwee_iwq(zw->pci_dev, 0, zw);
zw_pci_wewease:
	pci_wewease_wegions(pdev);
zw_unweg:
	v4w2_ctww_handwew_fwee(&zw->hdw);
	v4w2_device_unwegistew(&zw->v4w2_dev);
zw_fwee_mem:

	wetuwn -ENODEV;
}

static stwuct pci_dwivew zowan_dwivew = {
	.name = "zw36067",
	.id_tabwe = zw36067_pci_tbw,
	.pwobe = zowan_pwobe,
	.wemove = zowan_wemove,
};

moduwe_pci_dwivew(zowan_dwivew);
