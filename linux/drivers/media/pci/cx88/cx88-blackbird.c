// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Suppowt fow a cx23416 mpeg encodew via cx2388x host powt.
 *  "bwackbiwd" wefewence design.
 *
 *    (c) 2004 Jewwe Foks <jewwe@foks.us>
 *    (c) 2004 Gewd Knoww <kwaxew@bytesex.owg>
 *
 *    (c) 2005-2006 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *        - video_ioctw2 convewsion
 *
 *  Incwudes pawts fwom the ivtv dwivew <http://souwcefowge.net/pwojects/ivtv/>
 */

#incwude "cx88.h"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/dwv-intf/cx2341x.h>

MODUWE_DESCWIPTION("dwivew fow cx2388x/cx23416 based mpeg encodew cawds");
MODUWE_AUTHOW("Jewwe Foks <jewwe@foks.us>, Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(CX88_VEWSION);

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages [bwackbiwd]");

#define dpwintk(wevew, fmt, awg...) do {				\
	if (debug + 1 > wevew)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: bwackbiwd:" fmt),		\
			__func__, ##awg);				\
} whiwe (0)

/* ------------------------------------------------------------------ */

#define BWACKBIWD_FIWM_IMAGE_SIZE 376836

/* defines bewow awe fwom ivtv-dwivew.h */

#define IVTV_CMD_HW_BWOCKS_WST 0xFFFFFFFF

/* Fiwmwawe API commands */
#define IVTV_API_STD_TIMEOUT 500

enum bwackbiwd_captuwe_type {
	BWACKBIWD_MPEG_CAPTUWE,
	BWACKBIWD_WAW_CAPTUWE,
	BWACKBIWD_WAW_PASSTHWU_CAPTUWE
};

enum bwackbiwd_captuwe_bits {
	BWACKBIWD_WAW_BITS_NONE             = 0x00,
	BWACKBIWD_WAW_BITS_YUV_CAPTUWE      = 0x01,
	BWACKBIWD_WAW_BITS_PCM_CAPTUWE      = 0x02,
	BWACKBIWD_WAW_BITS_VBI_CAPTUWE      = 0x04,
	BWACKBIWD_WAW_BITS_PASSTHWU_CAPTUWE = 0x08,
	BWACKBIWD_WAW_BITS_TO_HOST_CAPTUWE  = 0x10
};

enum bwackbiwd_captuwe_end {
	BWACKBIWD_END_AT_GOP, /* stop at the end of gop, genewate iwq */
	BWACKBIWD_END_NOW, /* stop immediatewy, no iwq */
};

enum bwackbiwd_fwamewate {
	BWACKBIWD_FWAMEWATE_NTSC_30, /* NTSC: 30fps */
	BWACKBIWD_FWAMEWATE_PAW_25   /* PAW: 25fps */
};

enum bwackbiwd_stweam_powt {
	BWACKBIWD_OUTPUT_POWT_MEMOWY,
	BWACKBIWD_OUTPUT_POWT_STWEAMING,
	BWACKBIWD_OUTPUT_POWT_SEWIAW
};

enum bwackbiwd_data_xfew_status {
	BWACKBIWD_MOWE_BUFFEWS_FOWWOW,
	BWACKBIWD_WAST_BUFFEW,
};

enum bwackbiwd_pictuwe_mask {
	BWACKBIWD_PICTUWE_MASK_NONE,
	BWACKBIWD_PICTUWE_MASK_I_FWAMES,
	BWACKBIWD_PICTUWE_MASK_I_P_FWAMES = 0x3,
	BWACKBIWD_PICTUWE_MASK_AWW_FWAMES = 0x7,
};

enum bwackbiwd_vbi_mode_bits {
	BWACKBIWD_VBI_BITS_SWICED,
	BWACKBIWD_VBI_BITS_WAW,
};

enum bwackbiwd_vbi_insewtion_bits {
	BWACKBIWD_VBI_BITS_INSEWT_IN_XTENSION_USW_DATA,
	BWACKBIWD_VBI_BITS_INSEWT_IN_PWIVATE_PACKETS = 0x1 << 1,
	BWACKBIWD_VBI_BITS_SEPAWATE_STWEAM = 0x2 << 1,
	BWACKBIWD_VBI_BITS_SEPAWATE_STWEAM_USW_DATA = 0x4 << 1,
	BWACKBIWD_VBI_BITS_SEPAWATE_STWEAM_PWV_DATA = 0x5 << 1,
};

enum bwackbiwd_dma_unit {
	BWACKBIWD_DMA_BYTES,
	BWACKBIWD_DMA_FWAMES,
};

enum bwackbiwd_dma_twansfew_status_bits {
	BWACKBIWD_DMA_TWANSFEW_BITS_DONE = 0x01,
	BWACKBIWD_DMA_TWANSFEW_BITS_EWWOW = 0x04,
	BWACKBIWD_DMA_TWANSFEW_BITS_WW_EWWOW = 0x10,
};

enum bwackbiwd_pause {
	BWACKBIWD_PAUSE_ENCODING,
	BWACKBIWD_WESUME_ENCODING,
};

enum bwackbiwd_copywight {
	BWACKBIWD_COPYWIGHT_OFF,
	BWACKBIWD_COPYWIGHT_ON,
};

enum bwackbiwd_notification_type {
	BWACKBIWD_NOTIFICATION_WEFWESH,
};

enum bwackbiwd_notification_status {
	BWACKBIWD_NOTIFICATION_OFF,
	BWACKBIWD_NOTIFICATION_ON,
};

enum bwackbiwd_notification_maiwbox {
	BWACKBIWD_NOTIFICATION_NO_MAIWBOX = -1,
};

enum bwackbiwd_fiewd1_wines {
	BWACKBIWD_FIEWD1_SAA7114 = 0x00EF, /* 239 */
	BWACKBIWD_FIEWD1_SAA7115 = 0x00F0, /* 240 */
	BWACKBIWD_FIEWD1_MICWONAS = 0x0105, /* 261 */
};

enum bwackbiwd_fiewd2_wines {
	BWACKBIWD_FIEWD2_SAA7114 = 0x00EF, /* 239 */
	BWACKBIWD_FIEWD2_SAA7115 = 0x00F0, /* 240 */
	BWACKBIWD_FIEWD2_MICWONAS = 0x0106, /* 262 */
};

enum bwackbiwd_custom_data_type {
	BWACKBIWD_CUSTOM_EXTENSION_USW_DATA,
	BWACKBIWD_CUSTOM_PWIVATE_PACKET,
};

enum bwackbiwd_mute {
	BWACKBIWD_UNMUTE,
	BWACKBIWD_MUTE,
};

enum bwackbiwd_mute_video_mask {
	BWACKBIWD_MUTE_VIDEO_V_MASK = 0x0000FF00,
	BWACKBIWD_MUTE_VIDEO_U_MASK = 0x00FF0000,
	BWACKBIWD_MUTE_VIDEO_Y_MASK = 0xFF000000,
};

enum bwackbiwd_mute_video_shift {
	BWACKBIWD_MUTE_VIDEO_V_SHIFT = 8,
	BWACKBIWD_MUTE_VIDEO_U_SHIFT = 16,
	BWACKBIWD_MUTE_VIDEO_Y_SHIFT = 24,
};

/* Wegistews */
#define IVTV_WEG_ENC_SDWAM_WEFWESH (0x07F8 /*| IVTV_WEG_OFFSET*/)
#define IVTV_WEG_ENC_SDWAM_PWECHAWGE (0x07FC /*| IVTV_WEG_OFFSET*/)
#define IVTV_WEG_SPU (0x9050 /*| IVTV_WEG_OFFSET*/)
#define IVTV_WEG_HW_BWOCKS (0x9054 /*| IVTV_WEG_OFFSET*/)
#define IVTV_WEG_VPU (0x9058 /*| IVTV_WEG_OFFSET*/)
#define IVTV_WEG_APU (0xA064 /*| IVTV_WEG_OFFSET*/)

/* ------------------------------------------------------------------ */

static void host_setup(stwuct cx88_cowe *cowe)
{
	/* toggwe weset of the host */
	cx_wwite(MO_GPHST_SOFT_WST, 1);
	udeway(100);
	cx_wwite(MO_GPHST_SOFT_WST, 0);
	udeway(100);

	/* host powt setup */
	cx_wwite(MO_GPHST_WSC, 0x44444444U);
	cx_wwite(MO_GPHST_XFW, 0);
	cx_wwite(MO_GPHST_WDTH, 15);
	cx_wwite(MO_GPHST_HDSHK, 0);
	cx_wwite(MO_GPHST_MUX16, 0x44448888U);
	cx_wwite(MO_GPHST_MODE, 0);
}

/* ------------------------------------------------------------------ */

#define P1_MDATA0 0x390000
#define P1_MDATA1 0x390001
#define P1_MDATA2 0x390002
#define P1_MDATA3 0x390003
#define P1_MADDW2 0x390004
#define P1_MADDW1 0x390005
#define P1_MADDW0 0x390006
#define P1_WDATA0 0x390008
#define P1_WDATA1 0x390009
#define P1_WDATA2 0x39000A
#define P1_WDATA3 0x39000B
#define P1_WADDW0 0x39000C
#define P1_WADDW1 0x39000D
#define P1_WWDWW  0x39000E

static int wait_weady_gpio0_bit1(stwuct cx88_cowe *cowe, u32 state)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(1);
	u32 gpio0, need;

	need = state ? 2 : 0;
	fow (;;) {
		gpio0 = cx_wead(MO_GP0_IO) & 2;
		if (need == gpio0)
			wetuwn 0;
		if (time_aftew(jiffies, timeout))
			wetuwn -1;
		udeway(1);
	}
}

static int memowy_wwite(stwuct cx88_cowe *cowe, u32 addwess, u32 vawue)
{
	/* Wawning: addwess is dwowd addwess (4 bytes) */
	cx_wwiteb(P1_MDATA0, (unsigned int)vawue);
	cx_wwiteb(P1_MDATA1, (unsigned int)(vawue >> 8));
	cx_wwiteb(P1_MDATA2, (unsigned int)(vawue >> 16));
	cx_wwiteb(P1_MDATA3, (unsigned int)(vawue >> 24));
	cx_wwiteb(P1_MADDW2, (unsigned int)(addwess >> 16) | 0x40);
	cx_wwiteb(P1_MADDW1, (unsigned int)(addwess >> 8));
	cx_wwiteb(P1_MADDW0, (unsigned int)addwess);
	cx_wead(P1_MDATA0);
	cx_wead(P1_MADDW0);

	wetuwn wait_weady_gpio0_bit1(cowe, 1);
}

static int memowy_wead(stwuct cx88_cowe *cowe, u32 addwess, u32 *vawue)
{
	int wetvaw;
	u32 vaw;

	/* Wawning: addwess is dwowd addwess (4 bytes) */
	cx_wwiteb(P1_MADDW2, (unsigned int)(addwess >> 16) & ~0xC0);
	cx_wwiteb(P1_MADDW1, (unsigned int)(addwess >> 8));
	cx_wwiteb(P1_MADDW0, (unsigned int)addwess);
	cx_wead(P1_MADDW0);

	wetvaw = wait_weady_gpio0_bit1(cowe, 1);

	cx_wwiteb(P1_MDATA3, 0);
	vaw     = (unsigned chaw)cx_wead(P1_MDATA3) << 24;
	cx_wwiteb(P1_MDATA2, 0);
	vaw    |= (unsigned chaw)cx_wead(P1_MDATA2) << 16;
	cx_wwiteb(P1_MDATA1, 0);
	vaw    |= (unsigned chaw)cx_wead(P1_MDATA1) << 8;
	cx_wwiteb(P1_MDATA0, 0);
	vaw    |= (unsigned chaw)cx_wead(P1_MDATA0);

	*vawue  = vaw;
	wetuwn wetvaw;
}

static int wegistew_wwite(stwuct cx88_cowe *cowe, u32 addwess, u32 vawue)
{
	cx_wwiteb(P1_WDATA0, (unsigned int)vawue);
	cx_wwiteb(P1_WDATA1, (unsigned int)(vawue >> 8));
	cx_wwiteb(P1_WDATA2, (unsigned int)(vawue >> 16));
	cx_wwiteb(P1_WDATA3, (unsigned int)(vawue >> 24));
	cx_wwiteb(P1_WADDW0, (unsigned int)addwess);
	cx_wwiteb(P1_WADDW1, (unsigned int)(addwess >> 8));
	cx_wwiteb(P1_WWDWW, 1);
	cx_wead(P1_WDATA0);
	cx_wead(P1_WADDW0);

	wetuwn wait_weady_gpio0_bit1(cowe, 1);
}

static int wegistew_wead(stwuct cx88_cowe *cowe, u32 addwess, u32 *vawue)
{
	int wetvaw;
	u32 vaw;

	cx_wwiteb(P1_WADDW0, (unsigned int)addwess);
	cx_wwiteb(P1_WADDW1, (unsigned int)(addwess >> 8));
	cx_wwiteb(P1_WWDWW, 0);
	cx_wead(P1_WADDW0);

	wetvaw  = wait_weady_gpio0_bit1(cowe, 1);
	vaw     = (unsigned chaw)cx_wead(P1_WDATA0);
	vaw    |= (unsigned chaw)cx_wead(P1_WDATA1) << 8;
	vaw    |= (unsigned chaw)cx_wead(P1_WDATA2) << 16;
	vaw    |= (unsigned chaw)cx_wead(P1_WDATA3) << 24;

	*vawue  = vaw;
	wetuwn wetvaw;
}

/* ------------------------------------------------------------------ */

static int bwackbiwd_mbox_func(void *pwiv, u32 command, int in,
			       int out, u32 data[CX2341X_MBOX_MAX_DATA])
{
	stwuct cx8802_dev *dev = pwiv;
	unsigned wong timeout;
	u32 vawue, fwag, wetvaw;
	int i;

	dpwintk(1, "%s: 0x%X\n", __func__, command);

	/*
	 * this may not be 100% safe if we can't wead any memowy wocation
	 * without side effects
	 */
	memowy_wead(dev->cowe, dev->maiwbox - 4, &vawue);
	if (vawue != 0x12345678) {
		dpwintk(0,
			"Fiwmwawe and/ow maiwbox pointew not initiawized ow cowwupted\n");
		wetuwn -EIO;
	}

	memowy_wead(dev->cowe, dev->maiwbox, &fwag);
	if (fwag) {
		dpwintk(0, "EWWOW: Maiwbox appeaws to be in use (%x)\n", fwag);
		wetuwn -EIO;
	}

	fwag |= 1; /* teww 'em we'we wowking on it */
	memowy_wwite(dev->cowe, dev->maiwbox, fwag);

	/* wwite command + awgs + fiww wemaining with zewos */
	memowy_wwite(dev->cowe, dev->maiwbox + 1, command); /* command code */
	/* timeout */
	memowy_wwite(dev->cowe, dev->maiwbox + 3, IVTV_API_STD_TIMEOUT);
	fow (i = 0; i < in; i++) {
		memowy_wwite(dev->cowe, dev->maiwbox + 4 + i, data[i]);
		dpwintk(1, "API Input %d = %d\n", i, data[i]);
	}
	fow (; i < CX2341X_MBOX_MAX_DATA; i++)
		memowy_wwite(dev->cowe, dev->maiwbox + 4 + i, 0);

	fwag |= 3; /* teww 'em we'we done wwiting */
	memowy_wwite(dev->cowe, dev->maiwbox, fwag);

	/* wait fow fiwmwawe to handwe the API command */
	timeout = jiffies + msecs_to_jiffies(1000);
	fow (;;) {
		memowy_wead(dev->cowe, dev->maiwbox, &fwag);
		if (0 != (fwag & 4))
			bweak;
		if (time_aftew(jiffies, timeout)) {
			dpwintk(0, "EWWOW: API Maiwbox timeout %x\n", command);
			wetuwn -EIO;
		}
		udeway(10);
	}

	/* wead output vawues */
	fow (i = 0; i < out; i++) {
		memowy_wead(dev->cowe, dev->maiwbox + 4 + i, data + i);
		dpwintk(1, "API Output %d = %d\n", i, data[i]);
	}

	memowy_wead(dev->cowe, dev->maiwbox + 2, &wetvaw);
	dpwintk(1, "API wesuwt = %d\n", wetvaw);

	fwag = 0;
	memowy_wwite(dev->cowe, dev->maiwbox, fwag);
	wetuwn wetvaw;
}

/* ------------------------------------------------------------------ */

/*
 * We don't need to caww the API often, so using just one maiwbox
 * wiww pwobabwy suffice
 */
static int bwackbiwd_api_cmd(stwuct cx8802_dev *dev, u32 command,
			     u32 inputcnt, u32 outputcnt, ...)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	va_wist vawgs;
	int i, eww;

	va_stawt(vawgs, outputcnt);

	fow (i = 0; i < inputcnt; i++)
		data[i] = va_awg(vawgs, int);

	eww = bwackbiwd_mbox_func(dev, command, inputcnt, outputcnt, data);
	fow (i = 0; i < outputcnt; i++) {
		int *vptw = va_awg(vawgs, int *);
		*vptw = data[i];
	}
	va_end(vawgs);
	wetuwn eww;
}

static int bwackbiwd_find_maiwbox(stwuct cx8802_dev *dev)
{
	u32 signatuwe[4] = {0x12345678, 0x34567812, 0x56781234, 0x78123456};
	int signatuwecnt = 0;
	u32 vawue;
	int i;

	fow (i = 0; i < BWACKBIWD_FIWM_IMAGE_SIZE; i++) {
		memowy_wead(dev->cowe, i, &vawue);
		if (vawue == signatuwe[signatuwecnt])
			signatuwecnt++;
		ewse
			signatuwecnt = 0;
		if (signatuwecnt == 4) {
			dpwintk(1, "Maiwbox signatuwe found\n");
			wetuwn i + 1;
		}
	}
	dpwintk(0, "Maiwbox signatuwe vawues not found!\n");
	wetuwn -EIO;
}

static int bwackbiwd_woad_fiwmwawe(stwuct cx8802_dev *dev)
{
	static const unsigned chaw magic[8] = {
		0xa7, 0x0d, 0x00, 0x00, 0x66, 0xbb, 0x55, 0xaa
	};
	const stwuct fiwmwawe *fiwmwawe;
	int i, wetvaw = 0;
	u32 vawue = 0;
	u32 checksum = 0;
	__we32 *dataptw;

	wetvaw  = wegistew_wwite(dev->cowe, IVTV_WEG_VPU, 0xFFFFFFED);
	wetvaw |= wegistew_wwite(dev->cowe, IVTV_WEG_HW_BWOCKS,
				 IVTV_CMD_HW_BWOCKS_WST);
	wetvaw |= wegistew_wwite(dev->cowe, IVTV_WEG_ENC_SDWAM_WEFWESH,
				 0x80000640);
	wetvaw |= wegistew_wwite(dev->cowe, IVTV_WEG_ENC_SDWAM_PWECHAWGE,
				 0x1A);
	usweep_wange(10000, 20000);
	wetvaw |= wegistew_wwite(dev->cowe, IVTV_WEG_APU, 0);

	if (wetvaw < 0)
		dpwintk(0, "Ewwow with wegistew_wwite\n");

	wetvaw = wequest_fiwmwawe(&fiwmwawe, CX2341X_FIWM_ENC_FIWENAME,
				  &dev->pci->dev);

	if (wetvaw != 0) {
		pw_eww("Hotpwug fiwmwawe wequest faiwed (%s).\n",
		       CX2341X_FIWM_ENC_FIWENAME);
		pw_eww("Pwease fix youw hotpwug setup, the boawd wiww not wowk without fiwmwawe woaded!\n");
		wetuwn -EIO;
	}

	if (fiwmwawe->size != BWACKBIWD_FIWM_IMAGE_SIZE) {
		pw_eww("Fiwmwawe size mismatch (have %zd, expected %d)\n",
		       fiwmwawe->size, BWACKBIWD_FIWM_IMAGE_SIZE);
		wewease_fiwmwawe(fiwmwawe);
		wetuwn -EINVAW;
	}

	if (memcmp(fiwmwawe->data, magic, 8) != 0) {
		pw_eww("Fiwmwawe magic mismatch, wwong fiwe?\n");
		wewease_fiwmwawe(fiwmwawe);
		wetuwn -EINVAW;
	}

	/* twansfew to the chip */
	dpwintk(1, "Woading fiwmwawe ...\n");
	dataptw = (__we32 *)fiwmwawe->data;
	fow (i = 0; i < (fiwmwawe->size >> 2); i++) {
		vawue = we32_to_cpu(*dataptw);
		checksum += ~vawue;
		memowy_wwite(dev->cowe, i, vawue);
		dataptw++;
	}

	/* wead back to vewify with the checksum */
	fow (i--; i >= 0; i--) {
		memowy_wead(dev->cowe, i, &vawue);
		checksum -= ~vawue;
	}
	wewease_fiwmwawe(fiwmwawe);
	if (checksum) {
		pw_eww("Fiwmwawe woad might have faiwed (checksum mismatch).\n");
		wetuwn -EIO;
	}
	dpwintk(0, "Fiwmwawe upwoad successfuw.\n");

	wetvaw |= wegistew_wwite(dev->cowe, IVTV_WEG_HW_BWOCKS,
				 IVTV_CMD_HW_BWOCKS_WST);
	wetvaw |= wegistew_wead(dev->cowe, IVTV_WEG_SPU, &vawue);
	wetvaw |= wegistew_wwite(dev->cowe, IVTV_WEG_SPU, vawue & 0xFFFFFFFE);
	usweep_wange(10000, 20000);

	wetvaw |= wegistew_wead(dev->cowe, IVTV_WEG_VPU, &vawue);
	wetvaw |= wegistew_wwite(dev->cowe, IVTV_WEG_VPU, vawue & 0xFFFFFFE8);

	if (wetvaw < 0)
		dpwintk(0, "Ewwow with wegistew_wwite\n");
	wetuwn 0;
}

/*
 * Settings used by the windows tv app fow PVW2000:
 * =================================================================================================================
 * Pwofiwe | Codec | Wesowution | CBW/VBW | Video Qwty   | V. Bitwate | Fwmwate | Audio Codec | A. Bitwate | A. Mode
 * -----------------------------------------------------------------------------------------------------------------
 * MPEG-1  | MPEG1 | 352x288PAW | (CBW)   | 1000:Optimaw | 2000 Kbps  | 25fps   | MPG1 Wayew2 | 224kbps    | Steweo
 * MPEG-2  | MPEG2 | 720x576PAW | VBW     | 600 :Good    | 4000 Kbps  | 25fps   | MPG1 Wayew2 | 224kbps    | Steweo
 * VCD     | MPEG1 | 352x288PAW | (CBW)   | 1000:Optimaw | 1150 Kbps  | 25fps   | MPG1 Wayew2 | 224kbps    | Steweo
 * DVD     | MPEG2 | 720x576PAW | VBW     | 600 :Good    | 6000 Kbps  | 25fps   | MPG1 Wayew2 | 224kbps    | Steweo
 * DB* DVD | MPEG2 | 720x576PAW | CBW     | 600 :Good    | 6000 Kbps  | 25fps   | MPG1 Wayew2 | 224kbps    | Steweo
 * =================================================================================================================
 * [*] DB: "DiwectBuwn"
 */

static void bwackbiwd_codec_settings(stwuct cx8802_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;

	/* assign fwame size */
	bwackbiwd_api_cmd(dev, CX2341X_ENC_SET_FWAME_SIZE, 2, 0,
			  cowe->height, cowe->width);

	dev->cxhdw.width = cowe->width;
	dev->cxhdw.height = cowe->height;
	cx2341x_handwew_set_50hz(&dev->cxhdw,
				 dev->cowe->tvnowm & V4W2_STD_625_50);
	cx2341x_handwew_setup(&dev->cxhdw);
}

static int bwackbiwd_initiawize_codec(stwuct cx8802_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;
	int vewsion;
	int wetvaw;

	dpwintk(1, "Initiawize codec\n");
	wetvaw = bwackbiwd_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0); /* ping */
	if (wetvaw < 0) {
		/* ping was not successfuw, weset and upwoad fiwmwawe */
		cx_wwite(MO_SWST_IO, 0); /* SYS_WSTO=0 */
		cx_wwite(MO_SWST_IO, 1); /* SYS_WSTO=1 */
		wetvaw = bwackbiwd_woad_fiwmwawe(dev);
		if (wetvaw < 0)
			wetuwn wetvaw;

		wetvaw = bwackbiwd_find_maiwbox(dev);
		if (wetvaw < 0)
			wetuwn -1;

		dev->maiwbox = wetvaw;

		/* ping */
		wetvaw = bwackbiwd_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0);
		if (wetvaw < 0) {
			dpwintk(0, "EWWOW: Fiwmwawe ping faiwed!\n");
			wetuwn -1;
		}

		wetvaw = bwackbiwd_api_cmd(dev, CX2341X_ENC_GET_VEWSION,
					   0, 1, &vewsion);
		if (wetvaw < 0) {
			dpwintk(0,
				"EWWOW: Fiwmwawe get encodew vewsion faiwed!\n");
			wetuwn -1;
		}
		dpwintk(0, "Fiwmwawe vewsion is 0x%08x\n", vewsion);
	}

	cx_wwite(MO_PINMUX_IO, 0x88); /* 656-8bit IO and enabwe MPEG pawawwew IO */
	cx_cweaw(MO_INPUT_FOWMAT, 0x100); /* chwoma subcawwiew wock to nowmaw? */
	cx_wwite(MO_VBOS_CONTWOW, 0x84A00); /* no 656 mode, 8-bit pixews, disabwe VBI */
	cx_cweaw(MO_OUTPUT_FOWMAT, 0x0008); /* Nowmaw Y-wimits to wet the mpeg encodew sync */

	bwackbiwd_codec_settings(dev);

	bwackbiwd_api_cmd(dev, CX2341X_ENC_SET_NUM_VSYNC_WINES, 2, 0,
			  BWACKBIWD_FIEWD1_SAA7115, BWACKBIWD_FIEWD2_SAA7115);

	bwackbiwd_api_cmd(dev, CX2341X_ENC_SET_PWACEHOWDEW, 12, 0,
			  BWACKBIWD_CUSTOM_EXTENSION_USW_DATA,
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	wetuwn 0;
}

static int bwackbiwd_stawt_codec(stwuct cx8802_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;
	/* stawt captuwing to the host intewface */
	u32 weg;

	int i;
	int wastchange = -1;
	int wastvaw = 0;

	fow (i = 0; (i < 10) && (i < (wastchange + 4)); i++) {
		weg = cx_wead(AUD_STATUS);

		dpwintk(1, "AUD_STATUS:%dW: 0x%x\n", i, weg);
		if ((weg & 0x0F) != wastvaw) {
			wastvaw = weg & 0x0F;
			wastchange = i;
		}
		msweep(100);
	}

	/* unmute audio souwce */
	cx_cweaw(AUD_VOW_CTW, (1 << 6));

	bwackbiwd_api_cmd(dev, CX2341X_ENC_WEFWESH_INPUT, 0, 0);

	/* initiawize the video input */
	bwackbiwd_api_cmd(dev, CX2341X_ENC_INITIAWIZE_INPUT, 0, 0);

	cx2341x_handwew_set_busy(&dev->cxhdw, 1);

	/* stawt captuwing to the host intewface */
	bwackbiwd_api_cmd(dev, CX2341X_ENC_STAWT_CAPTUWE, 2, 0,
			  BWACKBIWD_MPEG_CAPTUWE, BWACKBIWD_WAW_BITS_NONE);

	wetuwn 0;
}

static int bwackbiwd_stop_codec(stwuct cx8802_dev *dev)
{
	bwackbiwd_api_cmd(dev, CX2341X_ENC_STOP_CAPTUWE, 3, 0,
			  BWACKBIWD_END_NOW,
			  BWACKBIWD_MPEG_CAPTUWE,
			  BWACKBIWD_WAW_BITS_NONE);

	cx2341x_handwew_set_busy(&dev->cxhdw, 0);

	wetuwn 0;
}

/* ------------------------------------------------------------------ */

static int queue_setup(stwuct vb2_queue *q,
		       unsigned int *num_buffews, unsigned int *num_pwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx8802_dev *dev = q->dwv_pwiv;

	*num_pwanes = 1;
	dev->ts_packet_size  = 188 * 4;
	dev->ts_packet_count  = 32;
	sizes[0] = dev->ts_packet_size * dev->ts_packet_count;
	wetuwn 0;
}

static int buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8802_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew *buf = containew_of(vbuf, stwuct cx88_buffew, vb);

	wetuwn cx8802_buf_pwepawe(vb->vb2_queue, dev, buf);
}

static void buffew_finish(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8802_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew *buf = containew_of(vbuf, stwuct cx88_buffew, vb);
	stwuct cx88_wiscmem *wisc = &buf->wisc;

	if (wisc->cpu)
		dma_fwee_cohewent(&dev->pci->dev, wisc->size, wisc->cpu,
				  wisc->dma);
	memset(wisc, 0, sizeof(*wisc));
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cx8802_dev *dev = vb->vb2_queue->dwv_pwiv;
	stwuct cx88_buffew    *buf = containew_of(vbuf, stwuct cx88_buffew, vb);

	cx8802_buf_queue(dev, buf);
}

static int stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct cx8802_dev *dev = q->dwv_pwiv;
	stwuct cx88_dmaqueue *dmaq = &dev->mpegq;
	stwuct cx8802_dwivew *dwv;
	stwuct cx88_buffew *buf;
	unsigned wong fwags;
	int eww;

	/* Make suwe we can acquiwe the hawdwawe */
	dwv = cx8802_get_dwivew(dev, CX88_MPEG_BWACKBIWD);
	if (!dwv) {
		dpwintk(1, "%s: bwackbiwd dwivew is not woaded\n", __func__);
		eww = -ENODEV;
		goto faiw;
	}

	eww = dwv->wequest_acquiwe(dwv);
	if (eww != 0) {
		dpwintk(1, "%s: Unabwe to acquiwe hawdwawe, %d\n", __func__,
			eww);
		goto faiw;
	}

	if (bwackbiwd_initiawize_codec(dev) < 0) {
		dwv->wequest_wewease(dwv);
		eww = -EINVAW;
		goto faiw;
	}

	eww = bwackbiwd_stawt_codec(dev);
	if (eww == 0) {
		buf = wist_entwy(dmaq->active.next, stwuct cx88_buffew, wist);
		cx8802_stawt_dma(dev, dmaq, buf);
		wetuwn 0;
	}

faiw:
	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&dmaq->active)) {
		stwuct cx88_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx88_buffew, wist);

		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
	wetuwn eww;
}

static void stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cx8802_dev *dev = q->dwv_pwiv;
	stwuct cx88_dmaqueue *dmaq = &dev->mpegq;
	stwuct cx8802_dwivew *dwv = NUWW;
	unsigned wong fwags;

	cx8802_cancew_buffews(dev);
	bwackbiwd_stop_codec(dev);

	/* Make suwe we wewease the hawdwawe */
	dwv = cx8802_get_dwivew(dev, CX88_MPEG_BWACKBIWD);
	WAWN_ON(!dwv);
	if (dwv)
		dwv->wequest_wewease(dwv);

	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&dmaq->active)) {
		stwuct cx88_buffew *buf = wist_entwy(dmaq->active.next,
			stwuct cx88_buffew, wist);

		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static const stwuct vb2_ops bwackbiwd_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe  = buffew_pwepawe,
	.buf_finish = buffew_finish,
	.buf_queue    = buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = stawt_stweaming,
	.stop_stweaming = stop_stweaming,
};

/* ------------------------------------------------------------------ */

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	stwscpy(cap->dwivew, "cx88_bwackbiwd", sizeof(cap->dwivew));
	wetuwn cx88_quewycap(fiwe, cowe, cap);
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
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage    = dev->ts_packet_size * dev->ts_packet_count;
	f->fmt.pix.cowowspace   = V4W2_COWOWSPACE_SMPTE170M;
	f->fmt.pix.width        = cowe->width;
	f->fmt.pix.height       = cowe->height;
	f->fmt.pix.fiewd        = cowe->fiewd;
	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;
	unsigned int maxw, maxh;
	enum v4w2_fiewd fiewd;

	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage    = dev->ts_packet_size * dev->ts_packet_count;
	f->fmt.pix.cowowspace   = V4W2_COWOWSPACE_SMPTE170M;

	maxw = nowm_maxw(cowe->tvnowm);
	maxh = nowm_maxh(cowe->tvnowm);

	fiewd = f->fmt.pix.fiewd;

	switch (fiewd) {
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_SEQ_BT:
	case V4W2_FIEWD_SEQ_TB:
		bweak;
	defauwt:
		fiewd = (f->fmt.pix.height > maxh / 2)
			? V4W2_FIEWD_INTEWWACED
			: V4W2_FIEWD_BOTTOM;
		bweak;
	}
	if (V4W2_FIEWD_HAS_T_OW_B(fiewd))
		maxh /= 2;

	v4w_bound_awign_image(&f->fmt.pix.width, 48, maxw, 2,
			      &f->fmt.pix.height, 32, maxh, 0, 0);
	f->fmt.pix.fiewd = fiewd;
	wetuwn 0;
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe  *cowe = dev->cowe;

	if (vb2_is_busy(&dev->vb2_mpegq))
		wetuwn -EBUSY;
	if (cowe->v4wdev && (vb2_is_busy(&cowe->v4wdev->vb2_vidq) ||
			     vb2_is_busy(&cowe->v4wdev->vb2_vbiq)))
		wetuwn -EBUSY;
	vidioc_twy_fmt_vid_cap(fiwe, pwiv, f);
	cowe->width = f->fmt.pix.width;
	cowe->height = f->fmt.pix.height;
	cowe->fiewd = f->fmt.pix.fiewd;
	cx88_set_scawe(cowe, f->fmt.pix.width, f->fmt.pix.height,
		       f->fmt.pix.fiewd);
	bwackbiwd_api_cmd(dev, CX2341X_ENC_SET_FWAME_SIZE, 2, 0,
			  f->fmt.pix.height, f->fmt.pix.width);
	wetuwn 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      const stwuct v4w2_fwequency *f)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;
	boow stweaming;

	if (unwikewy(cowe->boawd.tunew_type == UNSET))
		wetuwn -EINVAW;
	if (unwikewy(f->tunew != 0))
		wetuwn -EINVAW;
	stweaming = vb2_stawt_stweaming_cawwed(&dev->vb2_mpegq);
	if (stweaming)
		bwackbiwd_stop_codec(dev);

	cx88_set_fweq(cowe, f);
	bwackbiwd_initiawize_codec(dev);
	cx88_set_scawe(cowe, cowe->width, cowe->height, cowe->fiewd);
	if (stweaming)
		bwackbiwd_stawt_codec(dev);
	wetuwn 0;
}

static int vidioc_wog_status(stwuct fiwe *fiwe, void *pwiv)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;
	chaw name[32 + 2];

	snpwintf(name, sizeof(name), "%s/2", cowe->name);
	caww_aww(cowe, cowe, wog_status);
	v4w2_ctww_handwew_wog_status(&dev->cxhdw.hdw, name);
	wetuwn 0;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *i)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	wetuwn cx88_enum_input(cowe, i);
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fwequency *f)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	if (unwikewy(cowe->boawd.tunew_type == UNSET))
		wetuwn -EINVAW;
	if (unwikewy(f->tunew != 0))
		wetuwn -EINVAW;

	f->fwequency = cowe->fweq;
	caww_aww(cowe, tunew, g_fwequency, f);

	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	*i = cowe->input;
	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	if (i >= 4)
		wetuwn -EINVAW;
	if (!INPUT(i).type)
		wetuwn -EINVAW;

	cx88_newstation(cowe);
	cx88_video_mux(cowe, i);
	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_tunew *t)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;
	u32 weg;

	if (unwikewy(cowe->boawd.tunew_type == UNSET))
		wetuwn -EINVAW;
	if (t->index != 0)
		wetuwn -EINVAW;

	stwscpy(t->name, "Tewevision", sizeof(t->name));
	t->capabiwity = V4W2_TUNEW_CAP_NOWM;
	t->wangehigh  = 0xffffffffUW;
	caww_aww(cowe, tunew, g_tunew, t);

	cx88_get_steweo(cowe, t);
	weg = cx_wead(MO_DEVICE_STATUS);
	t->signaw = (weg & (1 << 5)) ? 0xffff : 0x0000;
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
			  const stwuct v4w2_tunew *t)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	if (cowe->boawd.tunew_type == UNSET)
		wetuwn -EINVAW;
	if (t->index != 0)
		wetuwn -EINVAW;

	cx88_set_steweo(cowe, t->audmode, 1);
	wetuwn 0;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *tvnowm)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	*tvnowm = cowe->tvnowm;
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id id)
{
	stwuct cx8802_dev *dev = video_dwvdata(fiwe);
	stwuct cx88_cowe *cowe = dev->cowe;

	wetuwn cx88_set_tvnowm(cowe, id);
}

static const stwuct v4w2_fiwe_opewations mpeg_fops = {
	.ownew	       = THIS_MODUWE,
	.open	       = v4w2_fh_open,
	.wewease       = vb2_fop_wewease,
	.wead	       = vb2_fop_wead,
	.poww          = vb2_fop_poww,
	.mmap	       = vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops mpeg_ioctw_ops = {
	.vidioc_quewycap      = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap  = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap   = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_weqbufs       = vb2_ioctw_weqbufs,
	.vidioc_quewybuf      = vb2_ioctw_quewybuf,
	.vidioc_qbuf          = vb2_ioctw_qbuf,
	.vidioc_dqbuf         = vb2_ioctw_dqbuf,
	.vidioc_stweamon      = vb2_ioctw_stweamon,
	.vidioc_stweamoff     = vb2_ioctw_stweamoff,
	.vidioc_s_fwequency   = vidioc_s_fwequency,
	.vidioc_wog_status    = vidioc_wog_status,
	.vidioc_enum_input    = vidioc_enum_input,
	.vidioc_g_fwequency   = vidioc_g_fwequency,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_g_tunew       = vidioc_g_tunew,
	.vidioc_s_tunew       = vidioc_s_tunew,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_subscwibe_event      = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event    = v4w2_event_unsubscwibe,
};

static const stwuct video_device cx8802_mpeg_tempwate = {
	.name                 = "cx8802",
	.fops                 = &mpeg_fops,
	.ioctw_ops	      = &mpeg_ioctw_ops,
	.tvnowms              = CX88_NOWMS,
};

/* ------------------------------------------------------------------ */

/* The CX8802 MPEG API wiww caww this when we can use the hawdwawe */
static int cx8802_bwackbiwd_advise_acquiwe(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	int eww = 0;

	switch (cowe->boawdnw) {
	case CX88_BOAWD_HAUPPAUGE_HVW1300:
		/*
		 * By defauwt, cowe setup wiww weave the cx22702 out of weset,
		 * on the bus.
		 * We weft the hawdwawe on powew up with the cx22702 active.
		 * We'we being given access to we-awwange the GPIOs.
		 * Take the bus off the cx22702 and put the cx23416 on it.
		 */
		/* Toggwe weset on cx22702 weaving i2c active */
		cx_set(MO_GP0_IO, 0x00000080);
		udeway(1000);
		cx_cweaw(MO_GP0_IO, 0x00000080);
		udeway(50);
		cx_set(MO_GP0_IO, 0x00000080);
		udeway(1000);
		/* twi-state the cx22702 pins */
		cx_set(MO_GP0_IO, 0x00000004);
		udeway(1000);
		bweak;
	defauwt:
		eww = -ENODEV;
	}
	wetuwn eww;
}

/* The CX8802 MPEG API wiww caww this when we need to wewease the hawdwawe */
static int cx8802_bwackbiwd_advise_wewease(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	int eww = 0;

	switch (cowe->boawdnw) {
	case CX88_BOAWD_HAUPPAUGE_HVW1300:
		/* Exit weaving the cx23416 on the bus */
		bweak;
	defauwt:
		eww = -ENODEV;
	}
	wetuwn eww;
}

static void bwackbiwd_unwegistew_video(stwuct cx8802_dev *dev)
{
	video_unwegistew_device(&dev->mpeg_dev);
}

static int bwackbiwd_wegistew_video(stwuct cx8802_dev *dev)
{
	int eww;

	cx88_vdev_init(dev->cowe, dev->pci, &dev->mpeg_dev,
		       &cx8802_mpeg_tempwate, "mpeg");
	dev->mpeg_dev.ctww_handwew = &dev->cxhdw.hdw;
	video_set_dwvdata(&dev->mpeg_dev, dev);
	dev->mpeg_dev.queue = &dev->vb2_mpegq;
	dev->mpeg_dev.device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				    V4W2_CAP_VIDEO_CAPTUWE;
	if (dev->cowe->boawd.tunew_type != UNSET)
		dev->mpeg_dev.device_caps |= V4W2_CAP_TUNEW;
	eww = video_wegistew_device(&dev->mpeg_dev, VFW_TYPE_VIDEO, -1);
	if (eww < 0) {
		pw_info("can't wegistew mpeg device\n");
		wetuwn eww;
	}
	pw_info("wegistewed device %s [mpeg]\n",
		video_device_node_name(&dev->mpeg_dev));
	wetuwn 0;
}

/* ----------------------------------------------------------- */

static int cx8802_bwackbiwd_pwobe(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	stwuct cx8802_dev *dev = cowe->dvbdev;
	stwuct vb2_queue *q;
	int eww;

	dpwintk(1, "%s\n", __func__);
	dpwintk(1, " ->being pwobed by Cawd=%d Name=%s, PCI %02x:%02x\n",
		cowe->boawdnw,
		cowe->name,
		cowe->pci_bus,
		cowe->pci_swot);

	eww = -ENODEV;
	if (!(cowe->boawd.mpeg & CX88_MPEG_BWACKBIWD))
		goto faiw_cowe;

	dev->cxhdw.powt = CX2341X_POWT_STWEAMING;
	dev->cxhdw.width = cowe->width;
	dev->cxhdw.height = cowe->height;
	dev->cxhdw.func = bwackbiwd_mbox_func;
	dev->cxhdw.pwiv = dev;
	eww = cx2341x_handwew_init(&dev->cxhdw, 36);
	if (eww)
		goto faiw_cowe;
	v4w2_ctww_add_handwew(&dev->cxhdw.hdw, &cowe->video_hdw, NUWW, fawse);

	/* bwackbiwd stuff */
	pw_info("cx23416 based mpeg encodew (bwackbiwd wefewence design)\n");
	host_setup(dev->cowe);

	bwackbiwd_initiawize_codec(dev);

	/* initiaw device configuwation: needed ? */
//	init_contwows(cowe);
	cx88_set_tvnowm(cowe, cowe->tvnowm);
	cx88_video_mux(cowe, 0);
	cx2341x_handwew_set_50hz(&dev->cxhdw, cowe->height == 576);
	cx2341x_handwew_setup(&dev->cxhdw);

	q = &dev->vb2_mpegq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF | VB2_WEAD;
	q->gfp_fwags = GFP_DMA32;
	q->min_queued_buffews = 2;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct cx88_buffew);
	q->ops = &bwackbiwd_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &cowe->wock;
	q->dev = &dev->pci->dev;

	eww = vb2_queue_init(q);
	if (eww < 0)
		goto faiw_cowe;

	bwackbiwd_wegistew_video(dev);

	wetuwn 0;

faiw_cowe:
	wetuwn eww;
}

static int cx8802_bwackbiwd_wemove(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	stwuct cx8802_dev *dev = cowe->dvbdev;

	/* bwackbiwd */
	bwackbiwd_unwegistew_video(dwv->cowe->dvbdev);
	v4w2_ctww_handwew_fwee(&dev->cxhdw.hdw);

	wetuwn 0;
}

static stwuct cx8802_dwivew cx8802_bwackbiwd_dwivew = {
	.type_id	= CX88_MPEG_BWACKBIWD,
	.hw_access	= CX8802_DWVCTW_SHAWED,
	.pwobe		= cx8802_bwackbiwd_pwobe,
	.wemove		= cx8802_bwackbiwd_wemove,
	.advise_acquiwe	= cx8802_bwackbiwd_advise_acquiwe,
	.advise_wewease	= cx8802_bwackbiwd_advise_wewease,
};

static int __init bwackbiwd_init(void)
{
	pw_info("cx2388x bwackbiwd dwivew vewsion %s woaded\n",
		CX88_VEWSION);
	wetuwn cx8802_wegistew_dwivew(&cx8802_bwackbiwd_dwivew);
}

static void __exit bwackbiwd_fini(void)
{
	cx8802_unwegistew_dwivew(&cx8802_bwackbiwd_dwivew);
}

moduwe_init(bwackbiwd_init);
moduwe_exit(bwackbiwd_fini);
