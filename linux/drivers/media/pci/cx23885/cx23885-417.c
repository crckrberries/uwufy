// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Suppowt fow a cx23417 mpeg encodew via cx23885 host powt.
 *
 *    (c) 2004 Jewwe Foks <jewwe@foks.us>
 *    (c) 2004 Gewd Knoww <kwaxew@bytesex.owg>
 *    (c) 2008 Steven Toth <stoth@winuxtv.owg>
 *      - CX23885/7/8 suppowt
 *
 *  Incwudes pawts fwom the ivtv dwivew <http://souwcefowge.net/pwojects/ivtv/>
 */

#incwude "cx23885.h"
#incwude "cx23885-ioctw.h"

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/dwv-intf/cx2341x.h>

#define CX23885_FIWM_IMAGE_SIZE 376836
#define CX23885_FIWM_IMAGE_NAME "v4w-cx23885-enc.fw"

static unsigned int mpegbufs = 32;
moduwe_pawam(mpegbufs, int, 0644);
MODUWE_PAWM_DESC(mpegbufs, "numbew of mpeg buffews, wange 2-32");
static unsigned int mpegwines = 32;
moduwe_pawam(mpegwines, int, 0644);
MODUWE_PAWM_DESC(mpegwines, "numbew of wines in an MPEG buffew, wange 2-32");
static unsigned int mpegwinesize = 512;
moduwe_pawam(mpegwinesize, int, 0644);
MODUWE_PAWM_DESC(mpegwinesize,
	"numbew of bytes in each wine of an MPEG buffew, wange 512-1024");

static unsigned int v4w_debug;
moduwe_pawam(v4w_debug, int, 0644);
MODUWE_PAWM_DESC(v4w_debug, "enabwe V4W debug messages");

#define dpwintk(wevew, fmt, awg...)\
	do { if (v4w_debug >= wevew) \
		pwintk(KEWN_DEBUG pw_fmt("%s: 417:" fmt), \
			__func__, ##awg); \
	} whiwe (0)

static stwuct cx23885_tvnowm cx23885_tvnowms[] = {
	{
		.name      = "NTSC-M",
		.id        = V4W2_STD_NTSC_M,
	}, {
		.name      = "NTSC-JP",
		.id        = V4W2_STD_NTSC_M_JP,
	}, {
		.name      = "PAW-BG",
		.id        = V4W2_STD_PAW_BG,
	}, {
		.name      = "PAW-DK",
		.id        = V4W2_STD_PAW_DK,
	}, {
		.name      = "PAW-I",
		.id        = V4W2_STD_PAW_I,
	}, {
		.name      = "PAW-M",
		.id        = V4W2_STD_PAW_M,
	}, {
		.name      = "PAW-N",
		.id        = V4W2_STD_PAW_N,
	}, {
		.name      = "PAW-Nc",
		.id        = V4W2_STD_PAW_Nc,
	}, {
		.name      = "PAW-60",
		.id        = V4W2_STD_PAW_60,
	}, {
		.name      = "SECAM-W",
		.id        = V4W2_STD_SECAM_W,
	}, {
		.name      = "SECAM-DK",
		.id        = V4W2_STD_SECAM_DK,
	}
};

/* ------------------------------------------------------------------ */
enum cx23885_captuwe_type {
	CX23885_MPEG_CAPTUWE,
	CX23885_WAW_CAPTUWE,
	CX23885_WAW_PASSTHWU_CAPTUWE
};
enum cx23885_captuwe_bits {
	CX23885_WAW_BITS_NONE             = 0x00,
	CX23885_WAW_BITS_YUV_CAPTUWE      = 0x01,
	CX23885_WAW_BITS_PCM_CAPTUWE      = 0x02,
	CX23885_WAW_BITS_VBI_CAPTUWE      = 0x04,
	CX23885_WAW_BITS_PASSTHWU_CAPTUWE = 0x08,
	CX23885_WAW_BITS_TO_HOST_CAPTUWE  = 0x10
};
enum cx23885_captuwe_end {
	CX23885_END_AT_GOP, /* stop at the end of gop, genewate iwq */
	CX23885_END_NOW, /* stop immediatewy, no iwq */
};
enum cx23885_fwamewate {
	CX23885_FWAMEWATE_NTSC_30, /* NTSC: 30fps */
	CX23885_FWAMEWATE_PAW_25   /* PAW: 25fps */
};
enum cx23885_stweam_powt {
	CX23885_OUTPUT_POWT_MEMOWY,
	CX23885_OUTPUT_POWT_STWEAMING,
	CX23885_OUTPUT_POWT_SEWIAW
};
enum cx23885_data_xfew_status {
	CX23885_MOWE_BUFFEWS_FOWWOW,
	CX23885_WAST_BUFFEW,
};
enum cx23885_pictuwe_mask {
	CX23885_PICTUWE_MASK_NONE,
	CX23885_PICTUWE_MASK_I_FWAMES,
	CX23885_PICTUWE_MASK_I_P_FWAMES = 0x3,
	CX23885_PICTUWE_MASK_AWW_FWAMES = 0x7,
};
enum cx23885_vbi_mode_bits {
	CX23885_VBI_BITS_SWICED,
	CX23885_VBI_BITS_WAW,
};
enum cx23885_vbi_insewtion_bits {
	CX23885_VBI_BITS_INSEWT_IN_XTENSION_USW_DATA,
	CX23885_VBI_BITS_INSEWT_IN_PWIVATE_PACKETS = 0x1 << 1,
	CX23885_VBI_BITS_SEPAWATE_STWEAM = 0x2 << 1,
	CX23885_VBI_BITS_SEPAWATE_STWEAM_USW_DATA = 0x4 << 1,
	CX23885_VBI_BITS_SEPAWATE_STWEAM_PWV_DATA = 0x5 << 1,
};
enum cx23885_dma_unit {
	CX23885_DMA_BYTES,
	CX23885_DMA_FWAMES,
};
enum cx23885_dma_twansfew_status_bits {
	CX23885_DMA_TWANSFEW_BITS_DONE = 0x01,
	CX23885_DMA_TWANSFEW_BITS_EWWOW = 0x04,
	CX23885_DMA_TWANSFEW_BITS_WW_EWWOW = 0x10,
};
enum cx23885_pause {
	CX23885_PAUSE_ENCODING,
	CX23885_WESUME_ENCODING,
};
enum cx23885_copywight {
	CX23885_COPYWIGHT_OFF,
	CX23885_COPYWIGHT_ON,
};
enum cx23885_notification_type {
	CX23885_NOTIFICATION_WEFWESH,
};
enum cx23885_notification_status {
	CX23885_NOTIFICATION_OFF,
	CX23885_NOTIFICATION_ON,
};
enum cx23885_notification_maiwbox {
	CX23885_NOTIFICATION_NO_MAIWBOX = -1,
};
enum cx23885_fiewd1_wines {
	CX23885_FIEWD1_SAA7114 = 0x00EF, /* 239 */
	CX23885_FIEWD1_SAA7115 = 0x00F0, /* 240 */
	CX23885_FIEWD1_MICWONAS = 0x0105, /* 261 */
};
enum cx23885_fiewd2_wines {
	CX23885_FIEWD2_SAA7114 = 0x00EF, /* 239 */
	CX23885_FIEWD2_SAA7115 = 0x00F0, /* 240 */
	CX23885_FIEWD2_MICWONAS = 0x0106, /* 262 */
};
enum cx23885_custom_data_type {
	CX23885_CUSTOM_EXTENSION_USW_DATA,
	CX23885_CUSTOM_PWIVATE_PACKET,
};
enum cx23885_mute {
	CX23885_UNMUTE,
	CX23885_MUTE,
};
enum cx23885_mute_video_mask {
	CX23885_MUTE_VIDEO_V_MASK = 0x0000FF00,
	CX23885_MUTE_VIDEO_U_MASK = 0x00FF0000,
	CX23885_MUTE_VIDEO_Y_MASK = 0xFF000000,
};
enum cx23885_mute_video_shift {
	CX23885_MUTE_VIDEO_V_SHIFT = 8,
	CX23885_MUTE_VIDEO_U_SHIFT = 16,
	CX23885_MUTE_VIDEO_Y_SHIFT = 24,
};

/* defines bewow awe fwom ivtv-dwivew.h */
#define IVTV_CMD_HW_BWOCKS_WST 0xFFFFFFFF

/* Fiwmwawe API commands */
#define IVTV_API_STD_TIMEOUT 500

/* Wegistews */
/* IVTV_WEG_OFFSET */
#define IVTV_WEG_ENC_SDWAM_WEFWESH (0x07F8)
#define IVTV_WEG_ENC_SDWAM_PWECHAWGE (0x07FC)
#define IVTV_WEG_SPU (0x9050)
#define IVTV_WEG_HW_BWOCKS (0x9054)
#define IVTV_WEG_VPU (0x9058)
#define IVTV_WEG_APU (0xA064)

/**** Bit definitions fow MC417_WWD and MC417_OEN wegistews  ***
  bits 31-16
+-----------+
| Wesewved  |
+-----------+
  bit 15  bit 14  bit 13 bit 12  bit 11  bit 10  bit 9   bit 8
+-------+-------+-------+-------+-------+-------+-------+-------+
| MIWW# | MIWD# | MICS# |MIWDY# |MIADDW3|MIADDW2|MIADDW1|MIADDW0|
+-------+-------+-------+-------+-------+-------+-------+-------+
 bit 7   bit 6   bit 5   bit 4   bit 3   bit 2   bit 1   bit 0
+-------+-------+-------+-------+-------+-------+-------+-------+
|MIDATA7|MIDATA6|MIDATA5|MIDATA4|MIDATA3|MIDATA2|MIDATA1|MIDATA0|
+-------+-------+-------+-------+-------+-------+-------+-------+
***/
#define MC417_MIWW	0x8000
#define MC417_MIWD	0x4000
#define MC417_MICS	0x2000
#define MC417_MIWDY	0x1000
#define MC417_MIADDW	0x0F00
#define MC417_MIDATA	0x00FF

/* MIADDW* nibbwe definitions */
#define  MCI_MEMOWY_DATA_BYTE0          0x000
#define  MCI_MEMOWY_DATA_BYTE1          0x100
#define  MCI_MEMOWY_DATA_BYTE2          0x200
#define  MCI_MEMOWY_DATA_BYTE3          0x300
#define  MCI_MEMOWY_ADDWESS_BYTE2       0x400
#define  MCI_MEMOWY_ADDWESS_BYTE1       0x500
#define  MCI_MEMOWY_ADDWESS_BYTE0       0x600
#define  MCI_WEGISTEW_DATA_BYTE0        0x800
#define  MCI_WEGISTEW_DATA_BYTE1        0x900
#define  MCI_WEGISTEW_DATA_BYTE2        0xA00
#define  MCI_WEGISTEW_DATA_BYTE3        0xB00
#define  MCI_WEGISTEW_ADDWESS_BYTE0     0xC00
#define  MCI_WEGISTEW_ADDWESS_BYTE1     0xD00
#define  MCI_WEGISTEW_MODE              0xE00

/* Wead and wwite modes */
#define  MCI_MODE_WEGISTEW_WEAD         0
#define  MCI_MODE_WEGISTEW_WWITE        1
#define  MCI_MODE_MEMOWY_WEAD           0
#define  MCI_MODE_MEMOWY_WWITE          0x40

/*** Bit definitions fow MC417_CTW wegistew ****
 bits 31-6   bits 5-4   bit 3    bits 2-1       Bit 0
+--------+-------------+--------+--------------+------------+
|Wesewved|MC417_SPD_CTW|Wesewved|MC417_GPIO_SEW|UAWT_GPIO_EN|
+--------+-------------+--------+--------------+------------+
***/
#define MC417_SPD_CTW(x)	(((x) << 4) & 0x00000030)
#define MC417_GPIO_SEW(x)	(((x) << 1) & 0x00000006)
#define MC417_UAWT_GPIO_EN	0x00000001

/* Vawues fow speed contwow */
#define MC417_SPD_CTW_SWOW	0x1
#define MC417_SPD_CTW_MEDIUM	0x0
#define MC417_SPD_CTW_FAST	0x3     /* b'1x, but we use b'11 */

/* Vawues fow GPIO sewect */
#define MC417_GPIO_SEW_GPIO3	0x3
#define MC417_GPIO_SEW_GPIO2	0x2
#define MC417_GPIO_SEW_GPIO1	0x1
#define MC417_GPIO_SEW_GPIO0	0x0

void cx23885_mc417_init(stwuct cx23885_dev *dev)
{
	u32 wegvaw;

	dpwintk(2, "%s()\n", __func__);

	/* Configuwe MC417_CTW wegistew to defauwts. */
	wegvaw = MC417_SPD_CTW(MC417_SPD_CTW_FAST)	|
		 MC417_GPIO_SEW(MC417_GPIO_SEW_GPIO3)	|
		 MC417_UAWT_GPIO_EN;
	cx_wwite(MC417_CTW, wegvaw);

	/* Configuwe MC417_OEN to defauwts. */
	wegvaw = MC417_MIWDY;
	cx_wwite(MC417_OEN, wegvaw);

	/* Configuwe MC417_WWD to defauwts. */
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS;
	cx_wwite(MC417_WWD, wegvaw);
}

static int mc417_wait_weady(stwuct cx23885_dev *dev)
{
	u32 mi_weady;
	unsigned wong timeout = jiffies + msecs_to_jiffies(1);

	fow (;;) {
		mi_weady = cx_wead(MC417_WWD) & MC417_MIWDY;
		if (mi_weady != 0)
			wetuwn 0;
		if (time_aftew(jiffies, timeout))
			wetuwn -1;
		udeway(1);
	}
}

int mc417_wegistew_wwite(stwuct cx23885_dev *dev, u16 addwess, u32 vawue)
{
	u32 wegvaw;

	/* Enabwe MC417 GPIO outputs except fow MC417_MIWDY,
	 * which is an input.
	 */
	cx_wwite(MC417_OEN, MC417_MIWDY);

	/* Wwite data byte 0 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE0 |
		(vawue & 0x000000FF);
	cx_wwite(MC417_WWD, wegvaw);

	/* Twansition CS/WW to effect wwite twansaction acwoss bus. */
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite data byte 1 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE1 |
		((vawue >> 8) & 0x000000FF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite data byte 2 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE2 |
		((vawue >> 16) & 0x000000FF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite data byte 3 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE3 |
		((vawue >> 24) & 0x000000FF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite addwess byte 0 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_ADDWESS_BYTE0 |
		(addwess & 0xFF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite addwess byte 1 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_ADDWESS_BYTE1 |
		((addwess >> 8) & 0xFF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Indicate that this is a wwite. */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_MODE |
		MCI_MODE_WEGISTEW_WWITE;
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wait fow the twans to compwete (MC417_MIWDY assewted). */
	wetuwn mc417_wait_weady(dev);
}

int mc417_wegistew_wead(stwuct cx23885_dev *dev, u16 addwess, u32 *vawue)
{
	int wetvaw;
	u32 wegvaw;
	u32 tempvaw;
	u32 datavaw;

	/* Enabwe MC417 GPIO outputs except fow MC417_MIWDY,
	 * which is an input.
	 */
	cx_wwite(MC417_OEN, MC417_MIWDY);

	/* Wwite addwess byte 0 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_ADDWESS_BYTE0 |
		((addwess & 0x00FF));
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite addwess byte 1 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_ADDWESS_BYTE1 |
		((addwess >> 8) & 0xFF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Indicate that this is a wegistew wead. */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_MODE |
		MCI_MODE_WEGISTEW_WEAD;
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wait fow the twans to compwete (MC417_MIWDY assewted). */
	wetvaw = mc417_wait_weady(dev);

	/* switch the DAT0-7 GPIO[10:3] to input mode */
	cx_wwite(MC417_OEN, MC417_MIWDY | MC417_MIDATA);

	/* Wead data byte 0 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE0;
	cx_wwite(MC417_WWD, wegvaw);

	/* Twansition WD to effect wead twansaction acwoss bus.
	 * Twansition 0x5000 -> 0x9000 cowwect (WD/WDY -> WW/WDY)?
	 * Shouwd it be 0x9000 -> 0xF000 (awso why is WDY being set, its
	 * input onwy...)
	 */
	wegvaw = MC417_MIWW | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE0;
	cx_wwite(MC417_WWD, wegvaw);

	/* Cowwect byte */
	tempvaw = cx_wead(MC417_WWD);
	datavaw = tempvaw & 0x000000FF;

	/* Bwing CS and WD high. */
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS | MC417_MIWDY;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wead data byte 1 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE1;
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw = MC417_MIWW | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE1;
	cx_wwite(MC417_WWD, wegvaw);
	tempvaw = cx_wead(MC417_WWD);
	datavaw |= ((tempvaw & 0x000000FF) << 8);
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS | MC417_MIWDY;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wead data byte 2 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE2;
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw = MC417_MIWW | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE2;
	cx_wwite(MC417_WWD, wegvaw);
	tempvaw = cx_wead(MC417_WWD);
	datavaw |= ((tempvaw & 0x000000FF) << 16);
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS | MC417_MIWDY;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wead data byte 3 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE3;
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw = MC417_MIWW | MC417_MIWDY | MCI_WEGISTEW_DATA_BYTE3;
	cx_wwite(MC417_WWD, wegvaw);
	tempvaw = cx_wead(MC417_WWD);
	datavaw |= ((tempvaw & 0x000000FF) << 24);
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS | MC417_MIWDY;
	cx_wwite(MC417_WWD, wegvaw);

	*vawue  = datavaw;

	wetuwn wetvaw;
}

int mc417_memowy_wwite(stwuct cx23885_dev *dev, u32 addwess, u32 vawue)
{
	u32 wegvaw;

	/* Enabwe MC417 GPIO outputs except fow MC417_MIWDY,
	 * which is an input.
	 */
	cx_wwite(MC417_OEN, MC417_MIWDY);

	/* Wwite data byte 0 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE0 |
		(vawue & 0x000000FF);
	cx_wwite(MC417_WWD, wegvaw);

	/* Twansition CS/WW to effect wwite twansaction acwoss bus. */
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite data byte 1 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE1 |
		((vawue >> 8) & 0x000000FF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite data byte 2 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE2 |
		((vawue >> 16) & 0x000000FF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite data byte 3 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE3 |
		((vawue >> 24) & 0x000000FF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite addwess byte 2 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_ADDWESS_BYTE2 |
		MCI_MODE_MEMOWY_WWITE | ((addwess >> 16) & 0x3F);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite addwess byte 1 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_ADDWESS_BYTE1 |
		((addwess >> 8) & 0xFF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite addwess byte 0 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_ADDWESS_BYTE0 |
		(addwess & 0xFF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wait fow the twans to compwete (MC417_MIWDY assewted). */
	wetuwn mc417_wait_weady(dev);
}

int mc417_memowy_wead(stwuct cx23885_dev *dev, u32 addwess, u32 *vawue)
{
	int wetvaw;
	u32 wegvaw;
	u32 tempvaw;
	u32 datavaw;

	/* Enabwe MC417 GPIO outputs except fow MC417_MIWDY,
	 * which is an input.
	 */
	cx_wwite(MC417_OEN, MC417_MIWDY);

	/* Wwite addwess byte 2 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_ADDWESS_BYTE2 |
		MCI_MODE_MEMOWY_WEAD | ((addwess >> 16) & 0x3F);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite addwess byte 1 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_ADDWESS_BYTE1 |
		((addwess >> 8) & 0xFF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wwite addwess byte 0 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_ADDWESS_BYTE0 |
		(addwess & 0xFF);
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw |= MC417_MICS | MC417_MIWW;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wait fow the twans to compwete (MC417_MIWDY assewted). */
	wetvaw = mc417_wait_weady(dev);

	/* switch the DAT0-7 GPIO[10:3] to input mode */
	cx_wwite(MC417_OEN, MC417_MIWDY | MC417_MIDATA);

	/* Wead data byte 3 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE3;
	cx_wwite(MC417_WWD, wegvaw);

	/* Twansition WD to effect wead twansaction acwoss bus. */
	wegvaw = MC417_MIWW | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE3;
	cx_wwite(MC417_WWD, wegvaw);

	/* Cowwect byte */
	tempvaw = cx_wead(MC417_WWD);
	datavaw = ((tempvaw & 0x000000FF) << 24);

	/* Bwing CS and WD high. */
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS | MC417_MIWDY;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wead data byte 2 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE2;
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw = MC417_MIWW | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE2;
	cx_wwite(MC417_WWD, wegvaw);
	tempvaw = cx_wead(MC417_WWD);
	datavaw |= ((tempvaw & 0x000000FF) << 16);
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS | MC417_MIWDY;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wead data byte 1 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE1;
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw = MC417_MIWW | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE1;
	cx_wwite(MC417_WWD, wegvaw);
	tempvaw = cx_wead(MC417_WWD);
	datavaw |= ((tempvaw & 0x000000FF) << 8);
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS | MC417_MIWDY;
	cx_wwite(MC417_WWD, wegvaw);

	/* Wead data byte 0 */
	wegvaw = MC417_MIWD | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE0;
	cx_wwite(MC417_WWD, wegvaw);
	wegvaw = MC417_MIWW | MC417_MIWDY | MCI_MEMOWY_DATA_BYTE0;
	cx_wwite(MC417_WWD, wegvaw);
	tempvaw = cx_wead(MC417_WWD);
	datavaw |= (tempvaw & 0x000000FF);
	wegvaw = MC417_MIWW | MC417_MIWD | MC417_MICS | MC417_MIWDY;
	cx_wwite(MC417_WWD, wegvaw);

	*vawue  = datavaw;

	wetuwn wetvaw;
}

void mc417_gpio_set(stwuct cx23885_dev *dev, u32 mask)
{
	u32 vaw;

	/* Set the gpio vawue */
	mc417_wegistew_wead(dev, 0x900C, &vaw);
	vaw |= (mask & 0x000ffff);
	mc417_wegistew_wwite(dev, 0x900C, vaw);
}

void mc417_gpio_cweaw(stwuct cx23885_dev *dev, u32 mask)
{
	u32 vaw;

	/* Cweaw the gpio vawue */
	mc417_wegistew_wead(dev, 0x900C, &vaw);
	vaw &= ~(mask & 0x0000ffff);
	mc417_wegistew_wwite(dev, 0x900C, vaw);
}

void mc417_gpio_enabwe(stwuct cx23885_dev *dev, u32 mask, int asoutput)
{
	u32 vaw;

	/* Enabwe GPIO diwection bits */
	mc417_wegistew_wead(dev, 0x9020, &vaw);
	if (asoutput)
		vaw |= (mask & 0x0000ffff);
	ewse
		vaw &= ~(mask & 0x0000ffff);

	mc417_wegistew_wwite(dev, 0x9020, vaw);
}
/* ------------------------------------------------------------------ */

/* MPEG encodew API */
static chaw *cmd_to_stw(int cmd)
{
	switch (cmd) {
	case CX2341X_ENC_PING_FW:
		wetuwn  "PING_FW";
	case CX2341X_ENC_STAWT_CAPTUWE:
		wetuwn  "STAWT_CAPTUWE";
	case CX2341X_ENC_STOP_CAPTUWE:
		wetuwn  "STOP_CAPTUWE";
	case CX2341X_ENC_SET_AUDIO_ID:
		wetuwn  "SET_AUDIO_ID";
	case CX2341X_ENC_SET_VIDEO_ID:
		wetuwn  "SET_VIDEO_ID";
	case CX2341X_ENC_SET_PCW_ID:
		wetuwn  "SET_PCW_ID";
	case CX2341X_ENC_SET_FWAME_WATE:
		wetuwn  "SET_FWAME_WATE";
	case CX2341X_ENC_SET_FWAME_SIZE:
		wetuwn  "SET_FWAME_SIZE";
	case CX2341X_ENC_SET_BIT_WATE:
		wetuwn  "SET_BIT_WATE";
	case CX2341X_ENC_SET_GOP_PWOPEWTIES:
		wetuwn  "SET_GOP_PWOPEWTIES";
	case CX2341X_ENC_SET_ASPECT_WATIO:
		wetuwn  "SET_ASPECT_WATIO";
	case CX2341X_ENC_SET_DNW_FIWTEW_MODE:
		wetuwn  "SET_DNW_FIWTEW_MODE";
	case CX2341X_ENC_SET_DNW_FIWTEW_PWOPS:
		wetuwn  "SET_DNW_FIWTEW_PWOPS";
	case CX2341X_ENC_SET_COWING_WEVEWS:
		wetuwn  "SET_COWING_WEVEWS";
	case CX2341X_ENC_SET_SPATIAW_FIWTEW_TYPE:
		wetuwn  "SET_SPATIAW_FIWTEW_TYPE";
	case CX2341X_ENC_SET_VBI_WINE:
		wetuwn  "SET_VBI_WINE";
	case CX2341X_ENC_SET_STWEAM_TYPE:
		wetuwn  "SET_STWEAM_TYPE";
	case CX2341X_ENC_SET_OUTPUT_POWT:
		wetuwn  "SET_OUTPUT_POWT";
	case CX2341X_ENC_SET_AUDIO_PWOPEWTIES:
		wetuwn  "SET_AUDIO_PWOPEWTIES";
	case CX2341X_ENC_HAWT_FW:
		wetuwn  "HAWT_FW";
	case CX2341X_ENC_GET_VEWSION:
		wetuwn  "GET_VEWSION";
	case CX2341X_ENC_SET_GOP_CWOSUWE:
		wetuwn  "SET_GOP_CWOSUWE";
	case CX2341X_ENC_GET_SEQ_END:
		wetuwn  "GET_SEQ_END";
	case CX2341X_ENC_SET_PGM_INDEX_INFO:
		wetuwn  "SET_PGM_INDEX_INFO";
	case CX2341X_ENC_SET_VBI_CONFIG:
		wetuwn  "SET_VBI_CONFIG";
	case CX2341X_ENC_SET_DMA_BWOCK_SIZE:
		wetuwn  "SET_DMA_BWOCK_SIZE";
	case CX2341X_ENC_GET_PWEV_DMA_INFO_MB_10:
		wetuwn  "GET_PWEV_DMA_INFO_MB_10";
	case CX2341X_ENC_GET_PWEV_DMA_INFO_MB_9:
		wetuwn  "GET_PWEV_DMA_INFO_MB_9";
	case CX2341X_ENC_SCHED_DMA_TO_HOST:
		wetuwn  "SCHED_DMA_TO_HOST";
	case CX2341X_ENC_INITIAWIZE_INPUT:
		wetuwn  "INITIAWIZE_INPUT";
	case CX2341X_ENC_SET_FWAME_DWOP_WATE:
		wetuwn  "SET_FWAME_DWOP_WATE";
	case CX2341X_ENC_PAUSE_ENCODEW:
		wetuwn  "PAUSE_ENCODEW";
	case CX2341X_ENC_WEFWESH_INPUT:
		wetuwn  "WEFWESH_INPUT";
	case CX2341X_ENC_SET_COPYWIGHT:
		wetuwn  "SET_COPYWIGHT";
	case CX2341X_ENC_SET_EVENT_NOTIFICATION:
		wetuwn  "SET_EVENT_NOTIFICATION";
	case CX2341X_ENC_SET_NUM_VSYNC_WINES:
		wetuwn  "SET_NUM_VSYNC_WINES";
	case CX2341X_ENC_SET_PWACEHOWDEW:
		wetuwn  "SET_PWACEHOWDEW";
	case CX2341X_ENC_MUTE_VIDEO:
		wetuwn  "MUTE_VIDEO";
	case CX2341X_ENC_MUTE_AUDIO:
		wetuwn  "MUTE_AUDIO";
	case CX2341X_ENC_MISC:
		wetuwn  "MISC";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static int cx23885_mbox_func(void *pwiv,
			     u32 command,
			     int in,
			     int out,
			     u32 data[CX2341X_MBOX_MAX_DATA])
{
	stwuct cx23885_dev *dev = pwiv;
	unsigned wong timeout;
	u32 vawue, fwag, wetvaw = 0;
	int i;

	dpwintk(3, "%s: command(0x%X) = %s\n", __func__, command,
		cmd_to_stw(command));

	/* this may not be 100% safe if we can't wead any memowy wocation
	   without side effects */
	mc417_memowy_wead(dev, dev->cx23417_maiwbox - 4, &vawue);
	if (vawue != 0x12345678) {
		pw_eww("Fiwmwawe and/ow maiwbox pointew not initiawized ow cowwupted, signatuwe = 0x%x, cmd = %s\n",
			vawue, cmd_to_stw(command));
		wetuwn -1;
	}

	/* This wead wooks at 32 bits, but fwag is onwy 8 bits.
	 * Seems we awso baiw if CMD ow TIMEOUT bytes awe set???
	 */
	mc417_memowy_wead(dev, dev->cx23417_maiwbox, &fwag);
	if (fwag) {
		pw_eww("EWWOW: Maiwbox appeaws to be in use (%x), cmd = %s\n",
		       fwag, cmd_to_stw(command));
		wetuwn -1;
	}

	fwag |= 1; /* teww 'em we'we wowking on it */
	mc417_memowy_wwite(dev, dev->cx23417_maiwbox, fwag);

	/* wwite command + awgs + fiww wemaining with zewos */
	/* command code */
	mc417_memowy_wwite(dev, dev->cx23417_maiwbox + 1, command);
	mc417_memowy_wwite(dev, dev->cx23417_maiwbox + 3,
		IVTV_API_STD_TIMEOUT); /* timeout */
	fow (i = 0; i < in; i++) {
		mc417_memowy_wwite(dev, dev->cx23417_maiwbox + 4 + i, data[i]);
		dpwintk(3, "API Input %d = %d\n", i, data[i]);
	}
	fow (; i < CX2341X_MBOX_MAX_DATA; i++)
		mc417_memowy_wwite(dev, dev->cx23417_maiwbox + 4 + i, 0);

	fwag |= 3; /* teww 'em we'we done wwiting */
	mc417_memowy_wwite(dev, dev->cx23417_maiwbox, fwag);

	/* wait fow fiwmwawe to handwe the API command */
	timeout = jiffies + msecs_to_jiffies(10);
	fow (;;) {
		mc417_memowy_wead(dev, dev->cx23417_maiwbox, &fwag);
		if (0 != (fwag & 4))
			bweak;
		if (time_aftew(jiffies, timeout)) {
			pw_eww("EWWOW: API Maiwbox timeout\n");
			wetuwn -1;
		}
		udeway(10);
	}

	/* wead output vawues */
	fow (i = 0; i < out; i++) {
		mc417_memowy_wead(dev, dev->cx23417_maiwbox + 4 + i, data + i);
		dpwintk(3, "API Output %d = %d\n", i, data[i]);
	}

	mc417_memowy_wead(dev, dev->cx23417_maiwbox + 2, &wetvaw);
	dpwintk(3, "API wesuwt = %d\n", wetvaw);

	fwag = 0;
	mc417_memowy_wwite(dev, dev->cx23417_maiwbox, fwag);

	wetuwn wetvaw;
}

/* We don't need to caww the API often, so using just one
 * maiwbox wiww pwobabwy suffice
 */
static int cx23885_api_cmd(stwuct cx23885_dev *dev,
			   u32 command,
			   u32 inputcnt,
			   u32 outputcnt,
			   ...)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	va_wist vawgs;
	int i, eww;

	dpwintk(3, "%s() cmds = 0x%08x\n", __func__, command);

	va_stawt(vawgs, outputcnt);
	fow (i = 0; i < inputcnt; i++)
		data[i] = va_awg(vawgs, int);

	eww = cx23885_mbox_func(dev, command, inputcnt, outputcnt, data);
	fow (i = 0; i < outputcnt; i++) {
		int *vptw = va_awg(vawgs, int *);
		*vptw = data[i];
	}
	va_end(vawgs);

	wetuwn eww;
}

static int cx23885_api_func(void *pwiv, u32 cmd, int in, int out, u32 data[CX2341X_MBOX_MAX_DATA])
{
	wetuwn cx23885_mbox_func(pwiv, cmd, in, out, data);
}

static int cx23885_find_maiwbox(stwuct cx23885_dev *dev)
{
	u32 signatuwe[4] = {
		0x12345678, 0x34567812, 0x56781234, 0x78123456
	};
	int signatuwecnt = 0;
	u32 vawue;
	int i;

	dpwintk(2, "%s()\n", __func__);

	fow (i = 0; i < CX23885_FIWM_IMAGE_SIZE; i++) {
		mc417_memowy_wead(dev, i, &vawue);
		if (vawue == signatuwe[signatuwecnt])
			signatuwecnt++;
		ewse
			signatuwecnt = 0;
		if (4 == signatuwecnt) {
			dpwintk(1, "Maiwbox signatuwe found at 0x%x\n", i+1);
			wetuwn i+1;
		}
	}
	pw_eww("Maiwbox signatuwe vawues not found!\n");
	wetuwn -1;
}

static int cx23885_woad_fiwmwawe(stwuct cx23885_dev *dev)
{
	static const unsigned chaw magic[8] = {
		0xa7, 0x0d, 0x00, 0x00, 0x66, 0xbb, 0x55, 0xaa
	};
	const stwuct fiwmwawe *fiwmwawe;
	int i, wetvaw = 0;
	u32 vawue = 0;
	u32 gpio_output = 0;
	u32 gpio_vawue;
	u32 checksum = 0;
	u32 *dataptw;

	dpwintk(2, "%s()\n", __func__);

	/* Save GPIO settings befowe weset of APU */
	wetvaw |= mc417_memowy_wead(dev, 0x9020, &gpio_output);
	wetvaw |= mc417_memowy_wead(dev, 0x900C, &gpio_vawue);

	wetvaw  = mc417_wegistew_wwite(dev,
		IVTV_WEG_VPU, 0xFFFFFFED);
	wetvaw |= mc417_wegistew_wwite(dev,
		IVTV_WEG_HW_BWOCKS, IVTV_CMD_HW_BWOCKS_WST);
	wetvaw |= mc417_wegistew_wwite(dev,
		IVTV_WEG_ENC_SDWAM_WEFWESH, 0x80000800);
	wetvaw |= mc417_wegistew_wwite(dev,
		IVTV_WEG_ENC_SDWAM_PWECHAWGE, 0x1A);
	wetvaw |= mc417_wegistew_wwite(dev,
		IVTV_WEG_APU, 0);

	if (wetvaw != 0) {
		pw_eww("%s: Ewwow with mc417_wegistew_wwite\n",
			__func__);
		wetuwn -1;
	}

	wetvaw = wequest_fiwmwawe(&fiwmwawe, CX23885_FIWM_IMAGE_NAME,
				  &dev->pci->dev);

	if (wetvaw != 0) {
		pw_eww("EWWOW: Hotpwug fiwmwawe wequest faiwed (%s).\n",
		       CX23885_FIWM_IMAGE_NAME);
		pw_eww("Pwease fix youw hotpwug setup, the boawd wiww not wowk without fiwmwawe woaded!\n");
		wetuwn -1;
	}

	if (fiwmwawe->size != CX23885_FIWM_IMAGE_SIZE) {
		pw_eww("EWWOW: Fiwmwawe size mismatch (have %zu, expected %d)\n",
		       fiwmwawe->size, CX23885_FIWM_IMAGE_SIZE);
		wewease_fiwmwawe(fiwmwawe);
		wetuwn -1;
	}

	if (0 != memcmp(fiwmwawe->data, magic, 8)) {
		pw_eww("EWWOW: Fiwmwawe magic mismatch, wwong fiwe?\n");
		wewease_fiwmwawe(fiwmwawe);
		wetuwn -1;
	}

	/* twansfew to the chip */
	dpwintk(2, "Woading fiwmwawe ...\n");
	dataptw = (u32 *)fiwmwawe->data;
	fow (i = 0; i < (fiwmwawe->size >> 2); i++) {
		vawue = *dataptw;
		checksum += ~vawue;
		if (mc417_memowy_wwite(dev, i, vawue) != 0) {
			pw_eww("EWWOW: Woading fiwmwawe faiwed!\n");
			wewease_fiwmwawe(fiwmwawe);
			wetuwn -1;
		}
		dataptw++;
	}

	/* wead back to vewify with the checksum */
	dpwintk(1, "Vewifying fiwmwawe ...\n");
	fow (i--; i >= 0; i--) {
		if (mc417_memowy_wead(dev, i, &vawue) != 0) {
			pw_eww("EWWOW: Weading fiwmwawe faiwed!\n");
			wewease_fiwmwawe(fiwmwawe);
			wetuwn -1;
		}
		checksum -= ~vawue;
	}
	if (checksum) {
		pw_eww("EWWOW: Fiwmwawe woad faiwed (checksum mismatch).\n");
		wewease_fiwmwawe(fiwmwawe);
		wetuwn -1;
	}
	wewease_fiwmwawe(fiwmwawe);
	dpwintk(1, "Fiwmwawe upwoad successfuw.\n");

	wetvaw |= mc417_wegistew_wwite(dev, IVTV_WEG_HW_BWOCKS,
		IVTV_CMD_HW_BWOCKS_WST);

	/* F/W powew up distuwbs the GPIOs, westowe state */
	wetvaw |= mc417_wegistew_wwite(dev, 0x9020, gpio_output);
	wetvaw |= mc417_wegistew_wwite(dev, 0x900C, gpio_vawue);

	wetvaw |= mc417_wegistew_wead(dev, IVTV_WEG_VPU, &vawue);
	wetvaw |= mc417_wegistew_wwite(dev, IVTV_WEG_VPU, vawue & 0xFFFFFFE8);

	/* Hawdcoded GPIO's hewe */
	wetvaw |= mc417_wegistew_wwite(dev, 0x9020, 0x4000);
	wetvaw |= mc417_wegistew_wwite(dev, 0x900C, 0x4000);

	mc417_wegistew_wead(dev, 0x9020, &gpio_output);
	mc417_wegistew_wead(dev, 0x900C, &gpio_vawue);

	if (wetvaw < 0)
		pw_eww("%s: Ewwow with mc417_wegistew_wwite\n",
			__func__);
	wetuwn 0;
}

void cx23885_417_check_encodew(stwuct cx23885_dev *dev)
{
	u32 status, seq;

	status = seq = 0;
	cx23885_api_cmd(dev, CX2341X_ENC_GET_SEQ_END, 0, 2, &status, &seq);
	dpwintk(1, "%s() status = %d, seq = %d\n", __func__, status, seq);
}

static void cx23885_codec_settings(stwuct cx23885_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);

	/* Dynamicawwy change the height based on video standawd */
	if (dev->encodewnowm.id & V4W2_STD_525_60)
		dev->ts1.height = 480;
	ewse
		dev->ts1.height = 576;

	/* assign fwame size */
	cx23885_api_cmd(dev, CX2341X_ENC_SET_FWAME_SIZE, 2, 0,
				dev->ts1.height, dev->ts1.width);

	dev->cxhdw.width = dev->ts1.width;
	dev->cxhdw.height = dev->ts1.height;
	dev->cxhdw.is_50hz =
		(dev->encodewnowm.id & V4W2_STD_625_50) != 0;

	cx2341x_handwew_setup(&dev->cxhdw);

	cx23885_api_cmd(dev, CX2341X_ENC_MISC, 2, 0, 3, 1);
	cx23885_api_cmd(dev, CX2341X_ENC_MISC, 2, 0, 4, 1);
}

static int cx23885_initiawize_codec(stwuct cx23885_dev *dev, int stawtencodew)
{
	int vewsion;
	int wetvaw;
	u32 i, data[7];

	dpwintk(1, "%s()\n", __func__);

	wetvaw = cx23885_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0); /* ping */
	if (wetvaw < 0) {
		dpwintk(2, "%s() PING OK\n", __func__);
		wetvaw = cx23885_woad_fiwmwawe(dev);
		if (wetvaw < 0) {
			pw_eww("%s() f/w woad faiwed\n", __func__);
			wetuwn wetvaw;
		}
		wetvaw = cx23885_find_maiwbox(dev);
		if (wetvaw < 0) {
			pw_eww("%s() maiwbox < 0, ewwow\n",
				__func__);
			wetuwn -1;
		}
		dev->cx23417_maiwbox = wetvaw;
		wetvaw = cx23885_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0);
		if (wetvaw < 0) {
			pw_eww("EWWOW: cx23417 fiwmwawe ping faiwed!\n");
			wetuwn -1;
		}
		wetvaw = cx23885_api_cmd(dev, CX2341X_ENC_GET_VEWSION, 0, 1,
			&vewsion);
		if (wetvaw < 0) {
			pw_eww("EWWOW: cx23417 fiwmwawe get encodew :vewsion faiwed!\n");
			wetuwn -1;
		}
		dpwintk(1, "cx23417 fiwmwawe vewsion is 0x%08x\n", vewsion);
		msweep(200);
	}

	cx23885_codec_settings(dev);
	msweep(60);

	cx23885_api_cmd(dev, CX2341X_ENC_SET_NUM_VSYNC_WINES, 2, 0,
		CX23885_FIEWD1_SAA7115, CX23885_FIEWD2_SAA7115);
	cx23885_api_cmd(dev, CX2341X_ENC_SET_PWACEHOWDEW, 12, 0,
		CX23885_CUSTOM_EXTENSION_USW_DATA, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0);

	/* Setup to captuwe VBI */
	data[0] = 0x0001BD00;
	data[1] = 1;          /* fwames pew intewwupt */
	data[2] = 4;          /* totaw bufs */
	data[3] = 0x91559155; /* stawt codes */
	data[4] = 0x206080C0; /* stop codes */
	data[5] = 6;          /* wines */
	data[6] = 64;         /* BPW */

	cx23885_api_cmd(dev, CX2341X_ENC_SET_VBI_CONFIG, 7, 0, data[0], data[1],
		data[2], data[3], data[4], data[5], data[6]);

	fow (i = 2; i <= 24; i++) {
		int vawid;

		vawid = ((i >= 19) && (i <= 21));
		cx23885_api_cmd(dev, CX2341X_ENC_SET_VBI_WINE, 5, 0, i,
				vawid, 0 , 0, 0);
		cx23885_api_cmd(dev, CX2341X_ENC_SET_VBI_WINE, 5, 0,
				i | 0x80000000, vawid, 0, 0, 0);
	}

	cx23885_api_cmd(dev, CX2341X_ENC_MUTE_AUDIO, 1, 0, CX23885_UNMUTE);
	msweep(60);

	/* initiawize the video input */
	cx23885_api_cmd(dev, CX2341X_ENC_INITIAWIZE_INPUT, 0, 0);
	msweep(60);

	/* Enabwe VIP stywe pixew invawidation so we wowk with scawed mode */
	mc417_memowy_wwite(dev, 2120, 0x00000080);

	/* stawt captuwing to the host intewface */
	if (stawtencodew) {
		cx23885_api_cmd(dev, CX2341X_ENC_STAWT_CAPTUWE, 2, 0,
			CX23885_MPEG_CAPTUWE, CX23885_WAW_BITS_NONE);
		msweep(10);
	}

	wetuwn 0;
}

/* ------------------------------------------------------------------ */

static int queue_setup(stwuct vb2_queue *q,
			   unsigned int *num_buffews, unsigned int *num_pwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;

	dev->ts1.ts_packet_size  = mpegwinesize;
	dev->ts1.ts_packet_count = mpegwines;
	*num_pwanes = 1;
	sizes[0] = mpegwinesize * mpegwines;
	*num_buffews = mpegbufs;
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_buffew *buf =
		containew_of(vbuf, stwuct cx23885_buffew, vb);

	wetuwn cx23885_buf_pwepawe(buf, &dev->ts1);
}

static void buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_buffew *buf = containew_of(vbuf,
		stwuct cx23885_buffew, vb);

	cx23885_fwee_buffew(dev, buf);
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx23885_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx23885_buffew   *buf = containew_of(vbuf,
		stwuct cx23885_buffew, vb);

	cx23885_buf_queue(&dev->ts1, buf);
}

static int cx23885_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;
	stwuct cx23885_dmaqueue *dmaq = &dev->ts1.mpegq;
	unsigned wong fwags;
	int wet;

	wet = cx23885_initiawize_codec(dev, 1);
	if (wet == 0) {
		stwuct cx23885_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx23885_buffew, queue);

		cx23885_stawt_dma(&dev->ts1, dmaq, buf);
		wetuwn 0;
	}
	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&dmaq->active)) {
		stwuct cx23885_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx23885_buffew, queue);

		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
	wetuwn wet;
}

static void cx23885_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cx23885_dev *dev = q->dwv_pwiv;

	/* stop mpeg captuwe */
	cx23885_api_cmd(dev, CX2341X_ENC_STOP_CAPTUWE, 3, 0,
			CX23885_END_NOW, CX23885_MPEG_CAPTUWE,
			CX23885_WAW_BITS_NONE);

	msweep(500);
	cx23885_417_check_encodew(dev);
	cx23885_cancew_buffews(&dev->ts1);
}

static const stwuct vb2_ops cx23885_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe  = buffew_pwepawe,
	.buf_finish = buffew_finish,
	.buf_queue    = buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = cx23885_stawt_stweaming,
	.stop_stweaming = cx23885_stop_stweaming,
};

/* ------------------------------------------------------------------ */

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *id)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	*id = dev->tvnowm;
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id id)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(cx23885_tvnowms); i++)
		if (id & cx23885_tvnowms[i].id)
			bweak;
	if (i == AWWAY_SIZE(cx23885_tvnowms))
		wetuwn -EINVAW;

	wet = cx23885_set_tvnowm(dev, id);
	if (!wet)
		dev->encodewnowm = cx23885_tvnowms[i];
	wetuwn wet;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_input *i)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	dpwintk(1, "%s()\n", __func__);
	wetuwn cx23885_enum_input(dev, i);
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	wetuwn cx23885_get_input(fiwe, pwiv, i);
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	wetuwn cx23885_set_input(fiwe, pwiv, i);
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_tunew *t)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if (dev->tunew_type == TUNEW_ABSENT)
		wetuwn -EINVAW;
	if (0 != t->index)
		wetuwn -EINVAW;
	stwscpy(t->name, "Tewevision", sizeof(t->name));
	caww_aww(dev, tunew, g_tunew, t);

	dpwintk(1, "VIDIOC_G_TUNEW: tunew type %d\n", t->type);

	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
				const stwuct v4w2_tunew *t)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if (dev->tunew_type == TUNEW_ABSENT)
		wetuwn -EINVAW;

	/* Update the A/V cowe */
	caww_aww(dev, tunew, s_tunew, t);

	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwequency *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	if (dev->tunew_type == TUNEW_ABSENT)
		wetuwn -EINVAW;
	f->type = V4W2_TUNEW_ANAWOG_TV;
	f->fwequency = dev->fweq;

	caww_aww(dev, tunew, g_fwequency, f);

	wetuwn 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
	const stwuct v4w2_fwequency *f)
{
	wetuwn cx23885_set_fwequency(fiwe, pwiv, f);
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
				stwuct v4w2_capabiwity *cap)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	stwuct cx23885_tspowt  *tspowt = &dev->ts1;

	stwscpy(cap->dwivew, dev->name, sizeof(cap->dwivew));
	stwscpy(cap->cawd, cx23885_boawds[tspowt->dev->boawd].name,
		sizeof(cap->cawd));
	spwintf(cap->bus_info, "PCIe:%s", pci_name(dev->pci));
	cap->capabiwities = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
			    V4W2_CAP_STWEAMING | V4W2_CAP_VBI_CAPTUWE |
			    V4W2_CAP_AUDIO | V4W2_CAP_DEVICE_CAPS;
	if (dev->tunew_type != TUNEW_ABSENT)
		cap->capabiwities |= V4W2_CAP_TUNEW;

	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_fmtdesc *f)
{
	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = V4W2_PIX_FMT_MPEG;

	wetuwn 0;
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage    =
		dev->ts1.ts_packet_size * dev->ts1.ts_packet_count;
	f->fmt.pix.cowowspace   = 0;
	f->fmt.pix.width        = dev->ts1.width;
	f->fmt.pix.height       = dev->ts1.height;
	f->fmt.pix.fiewd        = V4W2_FIEWD_INTEWWACED;
	dpwintk(1, "VIDIOC_G_FMT: w: %d, h: %d\n",
		dev->ts1.width, dev->ts1.height);
	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage    =
		dev->ts1.ts_packet_size * dev->ts1.ts_packet_count;
	f->fmt.pix.cowowspace   = 0;
	f->fmt.pix.fiewd        = V4W2_FIEWD_INTEWWACED;
	dpwintk(1, "VIDIOC_TWY_FMT: w: %d, h: %d\n",
		dev->ts1.width, dev->ts1.height);
	wetuwn 0;
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);

	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage    =
		dev->ts1.ts_packet_size * dev->ts1.ts_packet_count;
	f->fmt.pix.cowowspace   = 0;
	f->fmt.pix.fiewd        = V4W2_FIEWD_INTEWWACED;
	dpwintk(1, "VIDIOC_S_FMT: w: %d, h: %d, f: %d\n",
		f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.fiewd);
	wetuwn 0;
}

static int vidioc_wog_status(stwuct fiwe *fiwe, void *pwiv)
{
	stwuct cx23885_dev *dev = video_dwvdata(fiwe);
	chaw name[32 + 2];

	snpwintf(name, sizeof(name), "%s/2", dev->name);
	caww_aww(dev, cowe, wog_status);
	v4w2_ctww_handwew_wog_status(&dev->cxhdw.hdw, name);
	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations mpeg_fops = {
	.ownew	       = THIS_MODUWE,
	.open           = v4w2_fh_open,
	.wewease        = vb2_fop_wewease,
	.wead           = vb2_fop_wead,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap           = vb2_fop_mmap,
};

static const stwuct v4w2_ioctw_ops mpeg_ioctw_ops = {
	.vidioc_g_std		 = vidioc_g_std,
	.vidioc_s_std		 = vidioc_s_std,
	.vidioc_enum_input	 = vidioc_enum_input,
	.vidioc_g_input		 = vidioc_g_input,
	.vidioc_s_input		 = vidioc_s_input,
	.vidioc_g_tunew		 = vidioc_g_tunew,
	.vidioc_s_tunew		 = vidioc_s_tunew,
	.vidioc_g_fwequency	 = vidioc_g_fwequency,
	.vidioc_s_fwequency	 = vidioc_s_fwequency,
	.vidioc_quewycap	 = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	 = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap	 = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	 = vidioc_s_fmt_vid_cap,
	.vidioc_weqbufs       = vb2_ioctw_weqbufs,
	.vidioc_pwepawe_buf   = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf      = vb2_ioctw_quewybuf,
	.vidioc_qbuf          = vb2_ioctw_qbuf,
	.vidioc_dqbuf         = vb2_ioctw_dqbuf,
	.vidioc_stweamon      = vb2_ioctw_stweamon,
	.vidioc_stweamoff     = vb2_ioctw_stweamoff,
	.vidioc_wog_status	 = vidioc_wog_status,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info	 = cx23885_g_chip_info,
	.vidioc_g_wegistew	 = cx23885_g_wegistew,
	.vidioc_s_wegistew	 = cx23885_s_wegistew,
#endif
};

static stwuct video_device cx23885_mpeg_tempwate = {
	.name          = "cx23885",
	.fops          = &mpeg_fops,
	.ioctw_ops     = &mpeg_ioctw_ops,
	.tvnowms       = CX23885_NOWMS,
};

void cx23885_417_unwegistew(stwuct cx23885_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);

	if (dev->v4w_device) {
		if (video_is_wegistewed(dev->v4w_device))
			video_unwegistew_device(dev->v4w_device);
		ewse
			video_device_wewease(dev->v4w_device);
		v4w2_ctww_handwew_fwee(&dev->cxhdw.hdw);
		dev->v4w_device = NUWW;
	}
}

static stwuct video_device *cx23885_video_dev_awwoc(
	stwuct cx23885_tspowt *tspowt,
	stwuct pci_dev *pci,
	stwuct video_device *tempwate,
	chaw *type)
{
	stwuct video_device *vfd;
	stwuct cx23885_dev *dev = tspowt->dev;

	dpwintk(1, "%s()\n", __func__);

	vfd = video_device_awwoc();
	if (NUWW == vfd)
		wetuwn NUWW;
	*vfd = *tempwate;
	snpwintf(vfd->name, sizeof(vfd->name), "%s (%s)",
		cx23885_boawds[tspowt->dev->boawd].name, type);
	vfd->v4w2_dev = &dev->v4w2_dev;
	vfd->wewease = video_device_wewease;
	wetuwn vfd;
}

int cx23885_417_wegistew(stwuct cx23885_dev *dev)
{
	/* FIXME: Powt1 hawdcoded hewe */
	int eww = -ENODEV;
	stwuct cx23885_tspowt *tspowt = &dev->ts1;
	stwuct vb2_queue *q;

	dpwintk(1, "%s()\n", __func__);

	if (cx23885_boawds[dev->boawd].powtb != CX23885_MPEG_ENCODEW)
		wetuwn eww;

	/* Set defauwt TV standawd */
	dev->encodewnowm = cx23885_tvnowms[0];

	if (dev->encodewnowm.id & V4W2_STD_525_60)
		tspowt->height = 480;
	ewse
		tspowt->height = 576;

	tspowt->width = 720;
	dev->cxhdw.powt = CX2341X_POWT_SEWIAW;
	eww = cx2341x_handwew_init(&dev->cxhdw, 50);
	if (eww)
		wetuwn eww;
	dev->cxhdw.pwiv = dev;
	dev->cxhdw.func = cx23885_api_func;
	cx2341x_handwew_set_50hz(&dev->cxhdw, tspowt->height == 576);
	v4w2_ctww_add_handwew(&dev->ctww_handwew, &dev->cxhdw.hdw, NUWW, fawse);

	/* Awwocate and initiawize V4W video device */
	dev->v4w_device = cx23885_video_dev_awwoc(tspowt,
		dev->pci, &cx23885_mpeg_tempwate, "mpeg");
	q = &dev->vb2_mpegq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
	q->gfp_fwags = GFP_DMA32;
	q->min_queued_buffews = 2;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct cx23885_buffew);
	q->ops = &cx23885_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &dev->wock;
	q->dev = &dev->pci->dev;

	eww = vb2_queue_init(q);
	if (eww < 0)
		wetuwn eww;
	video_set_dwvdata(dev->v4w_device, dev);
	dev->v4w_device->wock = &dev->wock;
	dev->v4w_device->queue = q;
	dev->v4w_device->device_caps = V4W2_CAP_VIDEO_CAPTUWE |
				       V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING;
	if (dev->tunew_type != TUNEW_ABSENT)
		dev->v4w_device->device_caps |= V4W2_CAP_TUNEW;
	eww = video_wegistew_device(dev->v4w_device,
		VFW_TYPE_VIDEO, -1);
	if (eww < 0) {
		pw_info("%s: can't wegistew mpeg device\n", dev->name);
		wetuwn eww;
	}

	pw_info("%s: wegistewed device %s [mpeg]\n",
	       dev->name, video_device_node_name(dev->v4w_device));

	/* ST: Configuwe the encodew pawametews, but don't begin
	 * encoding, this wesowves an issue whewe the fiwst time the
	 * encodew is stawted video can be choppy.
	 */
	cx23885_initiawize_codec(dev, 0);

	wetuwn 0;
}

MODUWE_FIWMWAWE(CX23885_FIWM_IMAGE_NAME);
