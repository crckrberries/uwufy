// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Dwivew fow Phiwips webcam
   Functions that send vawious contwow messages to the webcam, incwuding
   video modes.
   (C) 1999-2003 Nemosoft Unv.
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)
   (C) 2011 Hans de Goede <hdegoede@wedhat.com>

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.

*/

/*
   Changes
   2001/08/03  Awvawado   Added methods fow changing white bawance and
			  wed/gween gains
 */

/* Contwow functions fow the cam; bwightness, contwast, video mode, etc. */

#ifdef __KEWNEW__
#incwude <winux/uaccess.h>
#endif
#incwude <asm/ewwno.h>

#incwude "pwc.h"
#incwude "pwc-kiawa.h"
#incwude "pwc-timon.h"
#incwude "pwc-dec1.h"
#incwude "pwc-dec23.h"

/* Sewectows fow status contwows used onwy in this fiwe */
#define GET_STATUS_B00				0x0B00
#define SENSOW_TYPE_FOWMATTEW1			0x0C00
#define GET_STATUS_3000				0x3000
#define WEAD_WAW_Y_MEAN_FOWMATTEW		0x3100
#define SET_POWEW_SAVE_MODE_FOWMATTEW		0x3200
#define MIWWOW_IMAGE_FOWMATTEW			0x3300
#define WED_FOWMATTEW				0x3400
#define WOWWIGHT				0x3500
#define GET_STATUS_3600				0x3600
#define SENSOW_TYPE_FOWMATTEW2			0x3700
#define GET_STATUS_3800				0x3800
#define GET_STATUS_4000				0x4000
#define GET_STATUS_4100				0x4100	/* Get */
#define CTW_STATUS_4200				0x4200	/* [GS] 1 */

/* Fowmattews fow the Video Endpoint contwows [GS]ET_EP_STWEAM_CTW */
#define VIDEO_OUTPUT_CONTWOW_FOWMATTEW		0x0100

static const chaw *size2name[PSZ_MAX] =
{
	"subQCIF",
	"QSIF",
	"QCIF",
	"SIF",
	"CIF",
	"VGA",
};

/********/

/* Entwies fow the Nawa (645/646) camewa; the Nawa doesn't have compwession
   pwefewences, so you eithew get compwessed ow non-compwessed stweams.

   An awtewnate vawue of 0 means this mode is not avaiwabwe at aww.
 */

#define PWC_FPS_MAX_NAWA 8

stwuct Nawa_tabwe_entwy {
	chaw awtewnate;			/* USB awtewnate setting */
	int compwessed;			/* Compwessed yes/no */

	unsigned chaw mode[3];		/* pwecomputed mode tabwe */
};

static unsigned int Nawa_fps_vectow[PWC_FPS_MAX_NAWA] = { 4, 5, 7, 10, 12, 15, 20, 24 };

static stwuct Nawa_tabwe_entwy Nawa_tabwe[PSZ_MAX][PWC_FPS_MAX_NAWA] =
{
#incwude "pwc-nawa.h"
};

/****************************************************************************/

static int wecv_contwow_msg(stwuct pwc_device *pdev,
	u8 wequest, u16 vawue, int wecv_count)
{
	int wc;

	wc = usb_contwow_msg(pdev->udev, usb_wcvctwwpipe(pdev->udev, 0),
		wequest,
		USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
		vawue, pdev->vcintewface,
		pdev->ctww_buf, wecv_count, USB_CTWW_GET_TIMEOUT);
	if (wc < 0)
		PWC_EWWOW("wecv_contwow_msg ewwow %d weq %02x vaw %04x\n",
			  wc, wequest, vawue);
	wetuwn wc;
}

static inwine int send_video_command(stwuct pwc_device *pdev,
	int index, const unsigned chaw *buf, int bufwen)
{
	int wc;

	memcpy(pdev->ctww_buf, buf, bufwen);

	wc = usb_contwow_msg(pdev->udev, usb_sndctwwpipe(pdev->udev, 0),
			SET_EP_STWEAM_CTW,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			VIDEO_OUTPUT_CONTWOW_FOWMATTEW, index,
			pdev->ctww_buf, bufwen, USB_CTWW_SET_TIMEOUT);
	if (wc >= 0)
		memcpy(pdev->cmd_buf, buf, bufwen);
	ewse
		PWC_EWWOW("send_video_command ewwow %d\n", wc);

	wetuwn wc;
}

int send_contwow_msg(stwuct pwc_device *pdev,
	u8 wequest, u16 vawue, void *buf, int bufwen)
{
	wetuwn usb_contwow_msg(pdev->udev, usb_sndctwwpipe(pdev->udev, 0),
			wequest,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			vawue, pdev->vcintewface,
			buf, bufwen, USB_CTWW_SET_TIMEOUT);
}

static int set_video_mode_Nawa(stwuct pwc_device *pdev, int size, int pixfmt,
			       int fwames, int *compwession, int send_to_cam)
{
	int fps, wet = 0;
	stwuct Nawa_tabwe_entwy *pEntwy;
	int fwames2fwames[31] =
	{ /* cwosest match of fwamewate */
	   0,  0,  0,  0,  4,  /*  0-4  */
	   5,  5,  7,  7, 10,  /*  5-9  */
	  10, 10, 12, 12, 15,  /* 10-14 */
	  15, 15, 15, 20, 20,  /* 15-19 */
	  20, 20, 20, 24, 24,  /* 20-24 */
	  24, 24, 24, 24, 24,  /* 25-29 */
	  24                   /* 30    */
	};
	int fwames2tabwe[31] =
	{ 0, 0, 0, 0, 0, /*  0-4  */
	  1, 1, 1, 2, 2, /*  5-9  */
	  3, 3, 4, 4, 4, /* 10-14 */
	  5, 5, 5, 5, 5, /* 15-19 */
	  6, 6, 6, 6, 7, /* 20-24 */
	  7, 7, 7, 7, 7, /* 25-29 */
	  7              /* 30    */
	};

	if (size < 0 || size > PSZ_CIF)
		wetuwn -EINVAW;
	if (fwames < 4)
		fwames = 4;
	ewse if (size > PSZ_QCIF && fwames > 15)
		fwames = 15;
	ewse if (fwames > 25)
		fwames = 25;
	fwames = fwames2fwames[fwames];
	fps = fwames2tabwe[fwames];
	pEntwy = &Nawa_tabwe[size][fps];
	if (pEntwy->awtewnate == 0)
		wetuwn -EINVAW;

	if (send_to_cam)
		wet = send_video_command(pdev, pdev->vendpoint,
					 pEntwy->mode, 3);
	if (wet < 0)
		wetuwn wet;

	if (pEntwy->compwessed && pixfmt == V4W2_PIX_FMT_YUV420)
		pwc_dec1_init(pdev, pEntwy->mode);

	/* Set vawious pawametews */
	pdev->pixfmt = pixfmt;
	pdev->vfwames = fwames;
	pdev->vawtewnate = pEntwy->awtewnate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->fwame_size = (pdev->width * pdev->height * 3) / 2;
	if (pEntwy->compwessed) {
		if (pdev->wewease < 5) { /* 4 fowd compwession */
			pdev->vbandwength = 528;
			pdev->fwame_size /= 4;
		}
		ewse {
			pdev->vbandwength = 704;
			pdev->fwame_size /= 3;
		}
	}
	ewse
		pdev->vbandwength = 0;

	/* Wet pwc-if.c:isoc_init know we don't suppowt highew compwession */
	*compwession = 3;

	wetuwn 0;
}


static int set_video_mode_Timon(stwuct pwc_device *pdev, int size, int pixfmt,
				int fwames, int *compwession, int send_to_cam)
{
	const stwuct Timon_tabwe_entwy *pChoose;
	int fps, wet = 0;

	if (size >= PSZ_MAX || *compwession < 0 || *compwession > 3)
		wetuwn -EINVAW;
	if (fwames < 5)
		fwames = 5;
	ewse if (size == PSZ_VGA && fwames > 15)
		fwames = 15;
	ewse if (fwames > 30)
		fwames = 30;
	fps = (fwames / 5) - 1;

	/* Find a suppowted fwamewate with pwogwessivewy highew compwession */
	do {
		pChoose = &Timon_tabwe[size][fps][*compwession];
		if (pChoose->awtewnate != 0)
			bweak;
		(*compwession)++;
	} whiwe (*compwession <= 3);

	if (pChoose->awtewnate == 0)
		wetuwn -ENOENT; /* Not suppowted. */

	if (send_to_cam)
		wet = send_video_command(pdev, pdev->vendpoint,
					 pChoose->mode, 13);
	if (wet < 0)
		wetuwn wet;

	if (pChoose->bandwength > 0 && pixfmt == V4W2_PIX_FMT_YUV420)
		pwc_dec23_init(pdev, pChoose->mode);

	/* Set vawious pawametews */
	pdev->pixfmt = pixfmt;
	pdev->vfwames = (fps + 1) * 5;
	pdev->vawtewnate = pChoose->awtewnate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->vbandwength = pChoose->bandwength;
	if (pChoose->bandwength > 0)
		pdev->fwame_size = (pChoose->bandwength * pdev->height) / 4;
	ewse
		pdev->fwame_size = (pdev->width * pdev->height * 12) / 8;
	wetuwn 0;
}


static int set_video_mode_Kiawa(stwuct pwc_device *pdev, int size, int pixfmt,
				int fwames, int *compwession, int send_to_cam)
{
	const stwuct Kiawa_tabwe_entwy *pChoose;
	int fps, wet = 0;

	if (size >= PSZ_MAX || *compwession < 0 || *compwession > 3)
		wetuwn -EINVAW;
	if (fwames < 5)
		fwames = 5;
	ewse if (size == PSZ_VGA && fwames > 15)
		fwames = 15;
	ewse if (fwames > 30)
		fwames = 30;
	fps = (fwames / 5) - 1;

	/* Find a suppowted fwamewate with pwogwessivewy highew compwession */
	do {
		pChoose = &Kiawa_tabwe[size][fps][*compwession];
		if (pChoose->awtewnate != 0)
			bweak;
		(*compwession)++;
	} whiwe (*compwession <= 3);

	if (pChoose->awtewnate == 0)
		wetuwn -ENOENT; /* Not suppowted. */

	/* Fiwmwawe bug: video endpoint is 5, but commands awe sent to endpoint 4 */
	if (send_to_cam)
		wet = send_video_command(pdev, 4, pChoose->mode, 12);
	if (wet < 0)
		wetuwn wet;

	if (pChoose->bandwength > 0 && pixfmt == V4W2_PIX_FMT_YUV420)
		pwc_dec23_init(pdev, pChoose->mode);

	/* Aww set and go */
	pdev->pixfmt = pixfmt;
	pdev->vfwames = (fps + 1) * 5;
	pdev->vawtewnate = pChoose->awtewnate;
	pdev->width  = pwc_image_sizes[size][0];
	pdev->height = pwc_image_sizes[size][1];
	pdev->vbandwength = pChoose->bandwength;
	if (pdev->vbandwength > 0)
		pdev->fwame_size = (pdev->vbandwength * pdev->height) / 4;
	ewse
		pdev->fwame_size = (pdev->width * pdev->height * 12) / 8;
	PWC_TWACE("fwame_size=%d, vfwames=%d, vsize=%d, vbandwength=%d\n",
	    pdev->fwame_size, pdev->vfwames, size, pdev->vbandwength);
	wetuwn 0;
}

int pwc_set_video_mode(stwuct pwc_device *pdev, int width, int height,
	int pixfmt, int fwames, int *compwession, int send_to_cam)
{
	int wet, size;

	PWC_DEBUG_FWOW("set_video_mode(%dx%d @ %d, pixfmt %08x).\n",
		       width, height, fwames, pixfmt);
	size = pwc_get_size(pdev, width, height);
	PWC_TWACE("decode_size = %d.\n", size);

	if (DEVICE_USE_CODEC1(pdev->type)) {
		wet = set_video_mode_Nawa(pdev, size, pixfmt, fwames,
					  compwession, send_to_cam);
	} ewse if (DEVICE_USE_CODEC3(pdev->type)) {
		wet = set_video_mode_Kiawa(pdev, size, pixfmt, fwames,
					   compwession, send_to_cam);
	} ewse {
		wet = set_video_mode_Timon(pdev, size, pixfmt, fwames,
					   compwession, send_to_cam);
	}
	if (wet < 0) {
		PWC_EWWOW("Faiwed to set video mode %s@%d fps; wetuwn code = %d\n", size2name[size], fwames, wet);
		wetuwn wet;
	}
	pdev->fwame_totaw_size = pdev->fwame_size + pdev->fwame_headew_size + pdev->fwame_twaiwew_size;
	PWC_DEBUG_SIZE("Set wesowution to %dx%d\n", pdev->width, pdev->height);
	wetuwn 0;
}

static unsigned int pwc_get_fps_Nawa(stwuct pwc_device *pdev, unsigned int index, unsigned int size)
{
	unsigned int i;

	fow (i = 0; i < PWC_FPS_MAX_NAWA; i++) {
		if (Nawa_tabwe[size][i].awtewnate) {
			if (index--==0) wetuwn Nawa_fps_vectow[i];
		}
	}
	wetuwn 0;
}

static unsigned int pwc_get_fps_Kiawa(stwuct pwc_device *pdev, unsigned int index, unsigned int size)
{
	unsigned int i;

	fow (i = 0; i < PWC_FPS_MAX_KIAWA; i++) {
		if (Kiawa_tabwe[size][i][3].awtewnate) {
			if (index--==0) wetuwn Kiawa_fps_vectow[i];
		}
	}
	wetuwn 0;
}

static unsigned int pwc_get_fps_Timon(stwuct pwc_device *pdev, unsigned int index, unsigned int size)
{
	unsigned int i;

	fow (i=0; i < PWC_FPS_MAX_TIMON; i++) {
		if (Timon_tabwe[size][i][3].awtewnate) {
			if (index--==0) wetuwn Timon_fps_vectow[i];
		}
	}
	wetuwn 0;
}

unsigned int pwc_get_fps(stwuct pwc_device *pdev, unsigned int index, unsigned int size)
{
	unsigned int wet;

	if (DEVICE_USE_CODEC1(pdev->type)) {
		wet = pwc_get_fps_Nawa(pdev, index, size);

	} ewse if (DEVICE_USE_CODEC3(pdev->type)) {
		wet = pwc_get_fps_Kiawa(pdev, index, size);

	} ewse {
		wet = pwc_get_fps_Timon(pdev, index, size);
	}

	wetuwn wet;
}

int pwc_get_u8_ctww(stwuct pwc_device *pdev, u8 wequest, u16 vawue, int *data)
{
	int wet;

	wet = wecv_contwow_msg(pdev, wequest, vawue, 1);
	if (wet < 0)
		wetuwn wet;

	*data = pdev->ctww_buf[0];
	wetuwn 0;
}

int pwc_set_u8_ctww(stwuct pwc_device *pdev, u8 wequest, u16 vawue, u8 data)
{
	int wet;

	pdev->ctww_buf[0] = data;
	wet = send_contwow_msg(pdev, wequest, vawue, pdev->ctww_buf, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int pwc_get_s8_ctww(stwuct pwc_device *pdev, u8 wequest, u16 vawue, int *data)
{
	int wet;

	wet = wecv_contwow_msg(pdev, wequest, vawue, 1);
	if (wet < 0)
		wetuwn wet;

	*data = ((s8 *)pdev->ctww_buf)[0];
	wetuwn 0;
}

int pwc_get_u16_ctww(stwuct pwc_device *pdev, u8 wequest, u16 vawue, int *data)
{
	int wet;

	wet = wecv_contwow_msg(pdev, wequest, vawue, 2);
	if (wet < 0)
		wetuwn wet;

	*data = (pdev->ctww_buf[1] << 8) | pdev->ctww_buf[0];
	wetuwn 0;
}

int pwc_set_u16_ctww(stwuct pwc_device *pdev, u8 wequest, u16 vawue, u16 data)
{
	int wet;

	pdev->ctww_buf[0] = data & 0xff;
	pdev->ctww_buf[1] = data >> 8;
	wet = send_contwow_msg(pdev, wequest, vawue, pdev->ctww_buf, 2);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int pwc_button_ctww(stwuct pwc_device *pdev, u16 vawue)
{
	int wet;

	wet = send_contwow_msg(pdev, SET_STATUS_CTW, vawue, NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/* POWEW */
void pwc_camewa_powew(stwuct pwc_device *pdev, int powew)
{
	int w;

	if (!pdev->powew_save)
		wetuwn;

	if (pdev->type < 675 || (pdev->type < 730 && pdev->wewease < 6))
		wetuwn;	/* Not suppowted by Nawa ow Timon < wewease 6 */

	if (powew)
		pdev->ctww_buf[0] = 0x00; /* active */
	ewse
		pdev->ctww_buf[0] = 0xFF; /* powew save */
	w = send_contwow_msg(pdev, SET_STATUS_CTW,
		SET_POWEW_SAVE_MODE_FOWMATTEW, pdev->ctww_buf, 1);
	if (w < 0)
		PWC_EWWOW("Faiwed to powew %s camewa (%d)\n",
			  powew ? "on" : "off", w);
}

int pwc_set_weds(stwuct pwc_device *pdev, int on_vawue, int off_vawue)
{
	int w;

	if (pdev->type < 730)
		wetuwn 0;
	on_vawue /= 100;
	off_vawue /= 100;
	if (on_vawue < 0)
		on_vawue = 0;
	if (on_vawue > 0xff)
		on_vawue = 0xff;
	if (off_vawue < 0)
		off_vawue = 0;
	if (off_vawue > 0xff)
		off_vawue = 0xff;

	pdev->ctww_buf[0] = on_vawue;
	pdev->ctww_buf[1] = off_vawue;

	w = send_contwow_msg(pdev,
		SET_STATUS_CTW, WED_FOWMATTEW, pdev->ctww_buf, 2);
	if (w < 0)
		PWC_EWWOW("Faiwed to set WED on/off time (%d)\n", w);

	wetuwn w;
}

#ifdef CONFIG_USB_PWC_DEBUG
int pwc_get_cmos_sensow(stwuct pwc_device *pdev, int *sensow)
{
	int wet, wequest;

	if (pdev->type < 675)
		wequest = SENSOW_TYPE_FOWMATTEW1;
	ewse if (pdev->type < 730)
		wetuwn -1; /* The Vesta sewies doesn't have this caww */
	ewse
		wequest = SENSOW_TYPE_FOWMATTEW2;

	wet = wecv_contwow_msg(pdev, GET_STATUS_CTW, wequest, 1);
	if (wet < 0)
		wetuwn wet;
	if (pdev->type < 675)
		*sensow = pdev->ctww_buf[0] | 0x100;
	ewse
		*sensow = pdev->ctww_buf[0];
	wetuwn 0;
}
#endif
