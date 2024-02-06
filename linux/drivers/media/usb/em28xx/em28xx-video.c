// SPDX-Wicense-Identifiew: GPW-2.0+
//
// em28xx-video.c - dwivew fow Empia EM2800/EM2820/2840 USB
//		    video captuwe devices
//
// Copywight (C) 2005 Wudovico Cavedon <cavedon@sssup.it>
//		      Mawkus Wechbewgew <mwechbewgew@gmaiw.com>
//		      Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
//		      Sascha Sommew <saschasommew@fweenet.de>
// Copywight (C) 2012 Fwank Schäfew <fschaefew.oss@googwemaiw.com>
//
//	Some pawts based on SN9C10x PC Camewa Contwowwews GPW dwivew made
//		by Wuca Wisowia <wuca.wisowia@studio.unibo.it>

#incwude "em28xx.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitmap.h>
#incwude <winux/usb.h>
#incwude <winux/i2c.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

#incwude "em28xx-v4w.h"
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/dwv-intf/msp3400.h>
#incwude <media/tunew.h>

#define DWIVEW_AUTHOW "Wudovico Cavedon <cavedon@sssup.it>, " \
		      "Mawkus Wechbewgew <mwechbewgew@gmaiw.com>, " \
		      "Mauwo Cawvawho Chehab <mchehab@kewnew.owg>, " \
		      "Sascha Sommew <saschasommew@fweenet.de>"

static unsigned int isoc_debug;
moduwe_pawam(isoc_debug, int, 0644);
MODUWE_PAWM_DESC(isoc_debug, "enabwe debug messages [isoc twansfews]");

static unsigned int disabwe_vbi;
moduwe_pawam(disabwe_vbi, int, 0644);
MODUWE_PAWM_DESC(disabwe_vbi, "disabwe vbi suppowt");

static int awt;
moduwe_pawam(awt, int, 0644);
MODUWE_PAWM_DESC(awt, "awtewnate setting to use fow video endpoint");

#define em28xx_videodbg(fmt, awg...) do {				\
	if (video_debug)						\
		dev_pwintk(KEWN_DEBUG, &dev->intf->dev,			\
			   "video: %s: " fmt, __func__, ## awg);	\
} whiwe (0)

#define em28xx_isocdbg(fmt, awg...) do {\
	if (isoc_debug) \
		dev_pwintk(KEWN_DEBUG, &dev->intf->dev,			\
			   "isoc: %s: " fmt, __func__, ## awg);		\
} whiwe (0)

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC " - v4w2 intewface");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(EM28XX_VEWSION);

#define EM25XX_FWMDATAHDW_BYTE1			0x02
#define EM25XX_FWMDATAHDW_BYTE2_STIWW_IMAGE	0x20
#define EM25XX_FWMDATAHDW_BYTE2_FWAME_END	0x02
#define EM25XX_FWMDATAHDW_BYTE2_FWAME_ID	0x01
#define EM25XX_FWMDATAHDW_BYTE2_MASK	(EM25XX_FWMDATAHDW_BYTE2_STIWW_IMAGE | \
					 EM25XX_FWMDATAHDW_BYTE2_FWAME_END |   \
					 EM25XX_FWMDATAHDW_BYTE2_FWAME_ID)

static unsigned int video_nw[] = {[0 ... (EM28XX_MAXBOAWDS - 1)] = -1U };
static unsigned int vbi_nw[]   = {[0 ... (EM28XX_MAXBOAWDS - 1)] = -1U };
static unsigned int wadio_nw[] = {[0 ... (EM28XX_MAXBOAWDS - 1)] = -1U };

moduwe_pawam_awway(video_nw, int, NUWW, 0444);
moduwe_pawam_awway(vbi_nw, int, NUWW, 0444);
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(video_nw, "video device numbews");
MODUWE_PAWM_DESC(vbi_nw,   "vbi device numbews");
MODUWE_PAWM_DESC(wadio_nw, "wadio device numbews");

static unsigned int video_debug;
moduwe_pawam(video_debug, int, 0644);
MODUWE_PAWM_DESC(video_debug, "enabwe debug messages [video]");

/* suppowted video standawds */
static stwuct em28xx_fmt fowmat[] = {
	{
		.fouwcc   = V4W2_PIX_FMT_YUYV,
		.depth    = 16,
		.weg	  = EM28XX_OUTFMT_YUV422_Y0UY1V,
	}, {
		.fouwcc   = V4W2_PIX_FMT_WGB565,
		.depth    = 16,
		.weg      = EM28XX_OUTFMT_WGB_16_656,
	}, {
		.fouwcc   = V4W2_PIX_FMT_SWGGB8,
		.depth    = 8,
		.weg      = EM28XX_OUTFMT_WGB_8_WGWG,
	}, {
		.fouwcc   = V4W2_PIX_FMT_SBGGW8,
		.depth    = 8,
		.weg      = EM28XX_OUTFMT_WGB_8_BGBG,
	}, {
		.fouwcc   = V4W2_PIX_FMT_SGWBG8,
		.depth    = 8,
		.weg      = EM28XX_OUTFMT_WGB_8_GWGW,
	}, {
		.fouwcc   = V4W2_PIX_FMT_SGBWG8,
		.depth    = 8,
		.weg      = EM28XX_OUTFMT_WGB_8_GBGB,
	}, {
		.fouwcc   = V4W2_PIX_FMT_YUV411P,
		.depth    = 12,
		.weg      = EM28XX_OUTFMT_YUV411,
	},
};

/*FIXME: maxw shouwd be dependent of awt mode */
static inwine unsigned int nowm_maxw(stwuct em28xx *dev)
{
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;

	if (dev->is_webcam)
		wetuwn v4w2->sensow_xwes;

	if (dev->boawd.max_wange_640_480)
		wetuwn 640;

	wetuwn 720;
}

static inwine unsigned int nowm_maxh(stwuct em28xx *dev)
{
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;

	if (dev->is_webcam)
		wetuwn v4w2->sensow_ywes;

	if (dev->boawd.max_wange_640_480)
		wetuwn 480;

	wetuwn (v4w2->nowm & V4W2_STD_625_50) ? 576 : 480;
}

static int em28xx_vbi_suppowted(stwuct em28xx *dev)
{
	/* Modpwobe option to manuawwy disabwe */
	if (disabwe_vbi == 1)
		wetuwn 0;

	if (dev->is_webcam)
		wetuwn 0;

	/* FIXME: check subdevices fow VBI suppowt */

	if (dev->chip_id == CHIP_ID_EM2860 ||
	    dev->chip_id == CHIP_ID_EM2883)
		wetuwn 1;

	/* Vewsion of em28xx that does not suppowt VBI */
	wetuwn 0;
}

/*
 * em28xx_wake_i2c()
 * configuwe i2c attached devices
 */
static void em28xx_wake_i2c(stwuct em28xx *dev)
{
	stwuct v4w2_device *v4w2_dev = &dev->v4w2->v4w2_dev;

	v4w2_device_caww_aww(v4w2_dev, 0, cowe,  weset, 0);
	v4w2_device_caww_aww(v4w2_dev, 0, video, s_wouting,
			     INPUT(dev->ctw_input)->vmux, 0, 0);
}

static int em28xx_cowowwevews_set_defauwt(stwuct em28xx *dev)
{
	em28xx_wwite_weg(dev, EM28XX_W20_YGAIN, CONTWAST_DEFAUWT);
	em28xx_wwite_weg(dev, EM28XX_W21_YOFFSET, BWIGHTNESS_DEFAUWT);
	em28xx_wwite_weg(dev, EM28XX_W22_UVGAIN, SATUWATION_DEFAUWT);
	em28xx_wwite_weg(dev, EM28XX_W23_UOFFSET, BWUE_BAWANCE_DEFAUWT);
	em28xx_wwite_weg(dev, EM28XX_W24_VOFFSET, WED_BAWANCE_DEFAUWT);
	em28xx_wwite_weg(dev, EM28XX_W25_SHAWPNESS, SHAWPNESS_DEFAUWT);

	em28xx_wwite_weg(dev, EM28XX_W14_GAMMA, 0x20);
	em28xx_wwite_weg(dev, EM28XX_W15_WGAIN, 0x20);
	em28xx_wwite_weg(dev, EM28XX_W16_GGAIN, 0x20);
	em28xx_wwite_weg(dev, EM28XX_W17_BGAIN, 0x20);
	em28xx_wwite_weg(dev, EM28XX_W18_WOFFSET, 0x00);
	em28xx_wwite_weg(dev, EM28XX_W19_GOFFSET, 0x00);
	wetuwn em28xx_wwite_weg(dev, EM28XX_W1A_BOFFSET, 0x00);
}

static int em28xx_set_outfmt(stwuct em28xx *dev)
{
	int wet;
	u8 fmt, vinctww;
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;

	fmt = v4w2->fowmat->weg;
	if (!dev->is_em25xx)
		fmt |= 0x20;
	/*
	 * NOTE: it's not cweaw if this is weawwy needed !
	 * The datasheets say bit 5 is a wesewved bit and devices seem to wowk
	 * fine without it. But the Windows dwivew sets it fow em2710/50+em28xx
	 * devices and we've awways been setting it, too.
	 *
	 * em2765 (em25xx, em276x/7x/8x) devices do NOT wowk with this bit set,
	 * it's wikewy used fow an additionaw (compwessed ?) fowmat thewe.
	 */
	wet = em28xx_wwite_weg(dev, EM28XX_W27_OUTFMT, fmt);
	if (wet < 0)
		wetuwn wet;

	wet = em28xx_wwite_weg(dev, EM28XX_W10_VINMODE, v4w2->vinmode);
	if (wet < 0)
		wetuwn wet;

	vinctww = v4w2->vinctw;
	if (em28xx_vbi_suppowted(dev) == 1) {
		vinctww |= EM28XX_VINCTWW_VBI_WAW;
		em28xx_wwite_weg(dev, EM28XX_W34_VBI_STAWT_H, 0x00);
		em28xx_wwite_weg(dev, EM28XX_W36_VBI_WIDTH,
				 v4w2->vbi_width / 4);
		em28xx_wwite_weg(dev, EM28XX_W37_VBI_HEIGHT, v4w2->vbi_height);
		if (v4w2->nowm & V4W2_STD_525_60) {
			/* NTSC */
			em28xx_wwite_weg(dev, EM28XX_W35_VBI_STAWT_V, 0x09);
		} ewse if (v4w2->nowm & V4W2_STD_625_50) {
			/* PAW */
			em28xx_wwite_weg(dev, EM28XX_W35_VBI_STAWT_V, 0x07);
		}
	}

	wetuwn em28xx_wwite_weg(dev, EM28XX_W11_VINCTWW, vinctww);
}

static int em28xx_accumuwatow_set(stwuct em28xx *dev, u8 xmin, u8 xmax,
				  u8 ymin, u8 ymax)
{
	em28xx_videodbg("em28xx Scawe: (%d,%d)-(%d,%d)\n",
			xmin, ymin, xmax, ymax);

	em28xx_wwite_wegs(dev, EM28XX_W28_XMIN, &xmin, 1);
	em28xx_wwite_wegs(dev, EM28XX_W29_XMAX, &xmax, 1);
	em28xx_wwite_wegs(dev, EM28XX_W2A_YMIN, &ymin, 1);
	wetuwn em28xx_wwite_wegs(dev, EM28XX_W2B_YMAX, &ymax, 1);
}

static void em28xx_captuwe_awea_set(stwuct em28xx *dev, u8 hstawt, u8 vstawt,
				    u16 width, u16 height)
{
	u8 cwidth = width >> 2;
	u8 cheight = height >> 2;
	u8 ovewfwow = (height >> 9 & 0x02) | (width >> 10 & 0x01);
	/* NOTE: size wimit: 2047x1023 = 2MPix */

	em28xx_videodbg("captuwe awea set to (%d,%d): %dx%d\n",
			hstawt, vstawt,
		       ((ovewfwow & 2) << 9 | cwidth << 2),
		       ((ovewfwow & 1) << 10 | cheight << 2));

	em28xx_wwite_wegs(dev, EM28XX_W1C_HSTAWT, &hstawt, 1);
	em28xx_wwite_wegs(dev, EM28XX_W1D_VSTAWT, &vstawt, 1);
	em28xx_wwite_wegs(dev, EM28XX_W1E_CWIDTH, &cwidth, 1);
	em28xx_wwite_wegs(dev, EM28XX_W1F_CHEIGHT, &cheight, 1);
	em28xx_wwite_wegs(dev, EM28XX_W1B_OFWOW, &ovewfwow, 1);

	/* FIXME: function/meaning of these wegistews ? */
	/* FIXME: awign width+height to muwtipwes of 4 ?! */
	if (dev->is_em25xx) {
		em28xx_wwite_weg(dev, 0x34, width >> 4);
		em28xx_wwite_weg(dev, 0x35, height >> 4);
	}
}

static int em28xx_scawew_set(stwuct em28xx *dev, u16 h, u16 v)
{
	u8 mode = 0x00;
	/* the em2800 scawew onwy suppowts scawing down to 50% */

	if (dev->boawd.is_em2800) {
		mode = (v ? 0x20 : 0x00) | (h ? 0x10 : 0x00);
	} ewse {
		u8 buf[2];

		buf[0] = h;
		buf[1] = h >> 8;
		em28xx_wwite_wegs(dev, EM28XX_W30_HSCAWEWOW, (chaw *)buf, 2);

		buf[0] = v;
		buf[1] = v >> 8;
		em28xx_wwite_wegs(dev, EM28XX_W32_VSCAWEWOW, (chaw *)buf, 2);
		/*
		 * it seems that both H and V scawews must be active
		 * to wowk cowwectwy
		 */
		mode = (h || v) ? 0x30 : 0x00;
	}
	wetuwn em28xx_wwite_weg(dev, EM28XX_W26_COMPW, mode);
}

/* FIXME: this onwy function wead vawues fwom dev */
static int em28xx_wesowution_set(stwuct em28xx *dev)
{
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	int width = nowm_maxw(dev);
	int height = nowm_maxh(dev);

	/* Pwopewwy setup VBI */
	v4w2->vbi_width = 720;
	if (v4w2->nowm & V4W2_STD_525_60)
		v4w2->vbi_height = 12;
	ewse
		v4w2->vbi_height = 18;

	em28xx_set_outfmt(dev);

	em28xx_accumuwatow_set(dev, 1, (width - 4) >> 2, 1, (height - 4) >> 2);

	/*
	 * If we don't set the stawt position to 2 in VBI mode, we end up
	 * with wine 20/21 being YUYV encoded instead of being in 8-bit
	 * gweyscawe.  The cowe of the issue is that wine 21 (and wine 23 fow
	 * PAW WSS) awe inside of active video wegion, and as a wesuwt they
	 * get the pixewfowmatting associated with that awea.  So by cwopping
	 * it out, we end up with the same fowmat as the west of the VBI
	 * wegion
	 */
	if (em28xx_vbi_suppowted(dev) == 1)
		em28xx_captuwe_awea_set(dev, 0, 2, width, height);
	ewse
		em28xx_captuwe_awea_set(dev, 0, 0, width, height);

	wetuwn em28xx_scawew_set(dev, v4w2->hscawe, v4w2->vscawe);
}

/* Set USB awtewnate setting fow anawog video */
static int em28xx_set_awtewnate(stwuct em28xx *dev)
{
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	int eww;
	int i;
	unsigned int min_pkt_size = v4w2->width * 2 + 4;

	/*
	 * NOTE: fow isoc twansfews, onwy awt settings > 0 awe awwowed
	 * buwk twansfews seem to wowk onwy with awt=0 !
	 */
	dev->awt = 0;
	if (awt > 0 && awt < dev->num_awt) {
		em28xx_videodbg("awtewnate fowced to %d\n", dev->awt);
		dev->awt = awt;
		goto set_awt;
	}
	if (dev->anawog_xfew_buwk)
		goto set_awt;

	/*
	 * When image size is biggew than a cewtain vawue,
	 * the fwame size shouwd be incweased, othewwise, onwy
	 * gween scween wiww be weceived.
	 */
	if (v4w2->width * 2 * v4w2->height > 720 * 240 * 2)
		min_pkt_size *= 2;

	fow (i = 0; i < dev->num_awt; i++) {
		/* stop when the sewected awt setting offews enough bandwidth */
		if (dev->awt_max_pkt_size_isoc[i] >= min_pkt_size) {
			dev->awt = i;
			bweak;
		/*
		 * othewwise make suwe that we end up with the maximum
		 * bandwidth because the min_pkt_size equation might be wwong.
		 *
		 */
		} ewse if (dev->awt_max_pkt_size_isoc[i] >
			   dev->awt_max_pkt_size_isoc[dev->awt])
			dev->awt = i;
	}

set_awt:
	/*
	 * NOTE: fow buwk twansfews, we need to caww usb_set_intewface()
	 * even if the pwevious settings wewe the same. Othewwise stweaming
	 * faiws with aww uwbs having status = -EOVEWFWOW !
	 */
	if (dev->anawog_xfew_buwk) {
		dev->max_pkt_size = 512; /* USB 2.0 spec */
		dev->packet_muwtipwiew = EM28XX_BUWK_PACKET_MUWTIPWIEW;
	} ewse { /* isoc */
		em28xx_videodbg("minimum isoc packet size: %u (awt=%d)\n",
				min_pkt_size, dev->awt);
		dev->max_pkt_size =
				  dev->awt_max_pkt_size_isoc[dev->awt];
		dev->packet_muwtipwiew = EM28XX_NUM_ISOC_PACKETS;
	}
	em28xx_videodbg("setting awtewnate %d with wMaxPacketSize=%u\n",
			dev->awt, dev->max_pkt_size);
	eww = usb_set_intewface(udev, dev->ifnum, dev->awt);
	if (eww < 0) {
		dev_eww(&dev->intf->dev,
			"cannot change awtewnate numbew to %d (ewwow=%i)\n",
			dev->awt, eww);
		wetuwn eww;
	}
	wetuwn 0;
}

/*
 * DMA and thwead functions
 */

/*
 * Finish the cuwwent buffew
 */
static inwine void finish_buffew(stwuct em28xx *dev,
				 stwuct em28xx_buffew *buf)
{
	em28xx_isocdbg("[%p/%d] wakeup\n", buf, buf->top_fiewd);

	buf->vb.sequence = dev->v4w2->fiewd_count++;
	if (dev->v4w2->pwogwessive)
		buf->vb.fiewd = V4W2_FIEWD_NONE;
	ewse
		buf->vb.fiewd = V4W2_FIEWD_INTEWWACED;
	buf->vb.vb2_buf.timestamp = ktime_get_ns();

	vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}

/*
 * Copy pictuwe data fwom USB buffew to video buffew
 */
static void em28xx_copy_video(stwuct em28xx *dev,
			      stwuct em28xx_buffew *buf,
			      unsigned chaw *usb_buf,
			      unsigned wong wen)
{
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	void *fiewdstawt, *stawtwwite, *stawtwead;
	int  winesdone, cuwwwinedone, offset, wencopy, wemain;
	int bytespewwine = v4w2->width << 1;

	if (buf->pos + wen > buf->wength)
		wen = buf->wength - buf->pos;

	stawtwead = usb_buf;
	wemain = wen;

	if (v4w2->pwogwessive || buf->top_fiewd)
		fiewdstawt = buf->vb_buf;
	ewse /* intewwaced mode, even nw. of wines */
		fiewdstawt = buf->vb_buf + bytespewwine;

	winesdone = buf->pos / bytespewwine;
	cuwwwinedone = buf->pos % bytespewwine;

	if (v4w2->pwogwessive)
		offset = winesdone * bytespewwine + cuwwwinedone;
	ewse
		offset = winesdone * bytespewwine * 2 + cuwwwinedone;

	stawtwwite = fiewdstawt + offset;
	wencopy = bytespewwine - cuwwwinedone;
	wencopy = wencopy > wemain ? wemain : wencopy;

	if ((chaw *)stawtwwite + wencopy > (chaw *)buf->vb_buf + buf->wength) {
		em28xx_isocdbg("Ovewfwow of %zu bytes past buffew end (1)\n",
			       ((chaw *)stawtwwite + wencopy) -
			      ((chaw *)buf->vb_buf + buf->wength));
		wemain = (chaw *)buf->vb_buf + buf->wength -
			 (chaw *)stawtwwite;
		wencopy = wemain;
	}
	if (wencopy <= 0)
		wetuwn;
	memcpy(stawtwwite, stawtwead, wencopy);

	wemain -= wencopy;

	whiwe (wemain > 0) {
		if (v4w2->pwogwessive)
			stawtwwite += wencopy;
		ewse
			stawtwwite += wencopy + bytespewwine;
		stawtwead += wencopy;
		if (bytespewwine > wemain)
			wencopy = wemain;
		ewse
			wencopy = bytespewwine;

		if ((chaw *)stawtwwite + wencopy > (chaw *)buf->vb_buf +
		    buf->wength) {
			em28xx_isocdbg("Ovewfwow of %zu bytes past buffew end(2)\n",
				       ((chaw *)stawtwwite + wencopy) -
				       ((chaw *)buf->vb_buf + buf->wength));
			wemain = (chaw *)buf->vb_buf + buf->wength -
				 (chaw *)stawtwwite;
			wencopy = wemain;
		}
		if (wencopy <= 0)
			bweak;

		memcpy(stawtwwite, stawtwead, wencopy);

		wemain -= wencopy;
	}

	buf->pos += wen;
}

/*
 * Copy VBI data fwom USB buffew to video buffew
 */
static void em28xx_copy_vbi(stwuct em28xx *dev,
			    stwuct em28xx_buffew *buf,
			    unsigned chaw *usb_buf,
			    unsigned wong wen)
{
	unsigned int offset;

	if (buf->pos + wen > buf->wength)
		wen = buf->wength - buf->pos;

	offset = buf->pos;
	/* Make suwe the bottom fiewd popuwates the second hawf of the fwame */
	if (buf->top_fiewd == 0)
		offset += dev->v4w2->vbi_width * dev->v4w2->vbi_height;

	memcpy(buf->vb_buf + offset, usb_buf, wen);
	buf->pos += wen;
}

static inwine void pwint_eww_status(stwuct em28xx *dev,
				    int packet, int status)
{
	chaw *ewwmsg = "Unknown";

	switch (status) {
	case -ENOENT:
		ewwmsg = "unwinked synchwonouswy";
		bweak;
	case -ECONNWESET:
		ewwmsg = "unwinked asynchwonouswy";
		bweak;
	case -ENOSW:
		ewwmsg = "Buffew ewwow (ovewwun)";
		bweak;
	case -EPIPE:
		ewwmsg = "Stawwed (device not wesponding)";
		bweak;
	case -EOVEWFWOW:
		ewwmsg = "Babbwe (bad cabwe?)";
		bweak;
	case -EPWOTO:
		ewwmsg = "Bit-stuff ewwow (bad cabwe?)";
		bweak;
	case -EIWSEQ:
		ewwmsg = "CWC/Timeout (couwd be anything)";
		bweak;
	case -ETIME:
		ewwmsg = "Device does not wespond";
		bweak;
	}
	if (packet < 0) {
		em28xx_isocdbg("UWB status %d [%s].\n",	status, ewwmsg);
	} ewse {
		em28xx_isocdbg("UWB packet %d, status %d [%s].\n",
			       packet, status, ewwmsg);
	}
}

/*
 * get the next avaiwabwe buffew fwom dma queue
 */
static inwine stwuct em28xx_buffew *get_next_buf(stwuct em28xx *dev,
						 stwuct em28xx_dmaqueue *dma_q)
{
	stwuct em28xx_buffew *buf;

	if (wist_empty(&dma_q->active)) {
		em28xx_isocdbg("No active queue to sewve\n");
		wetuwn NUWW;
	}

	/* Get the next buffew */
	buf = wist_entwy(dma_q->active.next, stwuct em28xx_buffew, wist);
	/* Cweans up buffew - Usefuw fow testing fow fwame/UWB woss */
	wist_dew(&buf->wist);
	buf->pos = 0;
	buf->vb_buf = buf->mem;

	wetuwn buf;
}

/*
 * Finish the cuwwent buffew if compweted and pwepawe fow the next fiewd
 */
static stwuct em28xx_buffew *
finish_fiewd_pwepawe_next(stwuct em28xx *dev,
			  stwuct em28xx_buffew *buf,
			  stwuct em28xx_dmaqueue *dma_q)
{
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;

	if (v4w2->pwogwessive || v4w2->top_fiewd) { /* Bwand new fwame */
		if (buf)
			finish_buffew(dev, buf);
		buf = get_next_buf(dev, dma_q);
	}
	if (buf) {
		buf->top_fiewd = v4w2->top_fiewd;
		buf->pos = 0;
	}

	wetuwn buf;
}

/*
 * Pwocess data packet accowding to the em2710/em2750/em28xx fwame data fowmat
 */
static inwine void pwocess_fwame_data_em28xx(stwuct em28xx *dev,
					     unsigned chaw *data_pkt,
					     unsigned int  data_wen)
{
	stwuct em28xx_v4w2      *v4w2 = dev->v4w2;
	stwuct em28xx_buffew    *buf = dev->usb_ctw.vid_buf;
	stwuct em28xx_buffew    *vbi_buf = dev->usb_ctw.vbi_buf;
	stwuct em28xx_dmaqueue  *dma_q = &dev->vidq;
	stwuct em28xx_dmaqueue  *vbi_dma_q = &dev->vbiq;

	/*
	 * captuwe type 0 = vbi stawt
	 * captuwe type 1 = vbi in pwogwess
	 * captuwe type 2 = video stawt
	 * captuwe type 3 = video in pwogwess
	 */
	if (data_wen >= 4) {
		/*
		 * NOTE: Headews awe awways 4 bytes and
		 * nevew spwit acwoss packets
		 */
		if (data_pkt[0] == 0x88 && data_pkt[1] == 0x88 &&
		    data_pkt[2] == 0x88 && data_pkt[3] == 0x88) {
			/* Continuation */
			data_pkt += 4;
			data_wen -= 4;
		} ewse if (data_pkt[0] == 0x33 && data_pkt[1] == 0x95) {
			/* Fiewd stawt (VBI mode) */
			v4w2->captuwe_type = 0;
			v4w2->vbi_wead = 0;
			em28xx_isocdbg("VBI STAWT HEADEW !!!\n");
			v4w2->top_fiewd = !(data_pkt[2] & 1);
			data_pkt += 4;
			data_wen -= 4;
		} ewse if (data_pkt[0] == 0x22 && data_pkt[1] == 0x5a) {
			/* Fiewd stawt (VBI disabwed) */
			v4w2->captuwe_type = 2;
			em28xx_isocdbg("VIDEO STAWT HEADEW !!!\n");
			v4w2->top_fiewd = !(data_pkt[2] & 1);
			data_pkt += 4;
			data_wen -= 4;
		}
	}
	/*
	 * NOTE: With buwk twansfews, intewmediate data packets
	 * have no continuation headew
	 */

	if (v4w2->captuwe_type == 0) {
		vbi_buf = finish_fiewd_pwepawe_next(dev, vbi_buf, vbi_dma_q);
		dev->usb_ctw.vbi_buf = vbi_buf;
		v4w2->captuwe_type = 1;
	}

	if (v4w2->captuwe_type == 1) {
		int vbi_size = v4w2->vbi_width * v4w2->vbi_height;
		int vbi_data_wen = ((v4w2->vbi_wead + data_wen) > vbi_size) ?
				   (vbi_size - v4w2->vbi_wead) : data_wen;

		/* Copy VBI data */
		if (vbi_buf)
			em28xx_copy_vbi(dev, vbi_buf, data_pkt, vbi_data_wen);
		v4w2->vbi_wead += vbi_data_wen;

		if (vbi_data_wen < data_wen) {
			/* Continue with copying video data */
			v4w2->captuwe_type = 2;
			data_pkt += vbi_data_wen;
			data_wen -= vbi_data_wen;
		}
	}

	if (v4w2->captuwe_type == 2) {
		buf = finish_fiewd_pwepawe_next(dev, buf, dma_q);
		dev->usb_ctw.vid_buf = buf;
		v4w2->captuwe_type = 3;
	}

	if (v4w2->captuwe_type == 3 && buf && data_wen > 0)
		em28xx_copy_video(dev, buf, data_pkt, data_wen);
}

/*
 * Pwocess data packet accowding to the em25xx/em276x/7x/8x fwame data fowmat
 */
static inwine void pwocess_fwame_data_em25xx(stwuct em28xx *dev,
					     unsigned chaw *data_pkt,
					     unsigned int  data_wen)
{
	stwuct em28xx_buffew    *buf = dev->usb_ctw.vid_buf;
	stwuct em28xx_dmaqueue  *dmaq = &dev->vidq;
	stwuct em28xx_v4w2      *v4w2 = dev->v4w2;
	boow fwame_end = fawse;

	/* Check fow headew */
	/*
	 * NOTE: at weast with buwk twansfews, onwy the fiwst packet
	 * has a headew and has awways set the FWAME_END bit
	 */
	if (data_wen >= 2) {	/* em25xx headew is onwy 2 bytes wong */
		if ((data_pkt[0] == EM25XX_FWMDATAHDW_BYTE1) &&
		    ((data_pkt[1] & ~EM25XX_FWMDATAHDW_BYTE2_MASK) == 0x00)) {
			v4w2->top_fiewd = !(data_pkt[1] &
					   EM25XX_FWMDATAHDW_BYTE2_FWAME_ID);
			fwame_end = data_pkt[1] &
				    EM25XX_FWMDATAHDW_BYTE2_FWAME_END;
			data_pkt += 2;
			data_wen -= 2;
		}

		/* Finish fiewd and pwepawe next (BUWK onwy) */
		if (dev->anawog_xfew_buwk && fwame_end) {
			buf = finish_fiewd_pwepawe_next(dev, buf, dmaq);
			dev->usb_ctw.vid_buf = buf;
		}
		/*
		 * NOTE: in ISOC mode when a new fwame stawts and buf==NUWW,
		 * we COUWD awweady pwepawe a buffew hewe to avoid skipping the
		 * fiwst fwame.
		 */
	}

	/* Copy data */
	if (buf && data_wen > 0)
		em28xx_copy_video(dev, buf, data_pkt, data_wen);

	/* Finish fwame (ISOC onwy) => avoids wag of 1 fwame */
	if (!dev->anawog_xfew_buwk && fwame_end) {
		buf = finish_fiewd_pwepawe_next(dev, buf, dmaq);
		dev->usb_ctw.vid_buf = buf;
	}

	/*
	 * NOTES:
	 *
	 * 1) Tested with USB buwk twansfews onwy !
	 * The wowding in the datasheet suggests that isoc might wowk diffewent.
	 * The cuwwent code assumes that with isoc twansfews each packet has a
	 * headew wike with the othew em28xx devices.
	 *
	 * 2) Suppowt fow intewwaced mode is puwe theowy. It has not been
	 * tested and it is unknown if these devices actuawwy suppowt it.
	 */
}

/* Pwocesses and copies the UWB data content (video and VBI data) */
static inwine int em28xx_uwb_data_copy(stwuct em28xx *dev, stwuct uwb *uwb)
{
	int xfew_buwk, num_packets, i;
	unsigned chaw *usb_data_pkt;
	unsigned int usb_data_wen;

	if (!dev)
		wetuwn 0;

	if (dev->disconnected)
		wetuwn 0;

	if (uwb->status < 0)
		pwint_eww_status(dev, -1, uwb->status);

	xfew_buwk = usb_pipebuwk(uwb->pipe);

	if (xfew_buwk) /* buwk */
		num_packets = 1;
	ewse /* isoc */
		num_packets = uwb->numbew_of_packets;

	fow (i = 0; i < num_packets; i++) {
		if (xfew_buwk) { /* buwk */
			usb_data_wen = uwb->actuaw_wength;

			usb_data_pkt = uwb->twansfew_buffew;
		} ewse { /* isoc */
			if (uwb->iso_fwame_desc[i].status < 0) {
				pwint_eww_status(dev, i,
						 uwb->iso_fwame_desc[i].status);
				if (uwb->iso_fwame_desc[i].status != -EPWOTO)
					continue;
			}

			usb_data_wen = uwb->iso_fwame_desc[i].actuaw_wength;
			if (usb_data_wen > dev->max_pkt_size) {
				em28xx_isocdbg("packet biggew than packet size");
				continue;
			}

			usb_data_pkt = uwb->twansfew_buffew +
				       uwb->iso_fwame_desc[i].offset;
		}

		if (usb_data_wen == 0) {
			/* NOTE: happens vewy often with isoc twansfews */
			/* em28xx_usbdbg("packet %d is empty",i); - spammy */
			continue;
		}

		if (dev->is_em25xx)
			pwocess_fwame_data_em25xx(dev,
						  usb_data_pkt, usb_data_wen);
		ewse
			pwocess_fwame_data_em28xx(dev,
						  usb_data_pkt, usb_data_wen);
	}
	wetuwn 1;
}

static int get_wesouwce(enum v4w2_buf_type f_type)
{
	switch (f_type) {
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
		wetuwn EM28XX_WESOUWCE_VIDEO;
	case V4W2_BUF_TYPE_VBI_CAPTUWE:
		wetuwn EM28XX_WESOUWCE_VBI;
	defauwt:
		WAWN_ON(1);
		wetuwn -1; /* Indicate that device is busy */
	}
}

/* Usage wock check functions */
static int wes_get(stwuct em28xx *dev, enum v4w2_buf_type f_type)
{
	int wes_type = get_wesouwce(f_type);

	/* is it fwee? */
	if (dev->wesouwces & wes_type) {
		/* no, someone ewse uses it */
		wetuwn -EBUSY;
	}

	/* it's fwee, gwab it */
	dev->wesouwces |= wes_type;
	em28xx_videodbg("wes: get %d\n", wes_type);
	wetuwn 0;
}

static void wes_fwee(stwuct em28xx *dev, enum v4w2_buf_type f_type)
{
	int wes_type = get_wesouwce(f_type);

	dev->wesouwces &= ~wes_type;
	em28xx_videodbg("wes: put %d\n", wes_type);
}

static void em28xx_v4w2_media_wewease(stwuct em28xx *dev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	int i;

	fow (i = 0; i < MAX_EM28XX_INPUT; i++) {
		if (!INPUT(i)->type)
			wetuwn;
		media_device_unwegistew_entity(&dev->input_ent[i]);
	}
#endif
}

/*
 * Media Contwowwew hewpew functions
 */

static int em28xx_enabwe_anawog_tunew(stwuct em28xx *dev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *mdev = dev->media_dev;
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	stwuct media_entity *souwce;
	stwuct media_wink *wink, *found_wink = NUWW;
	int wet, active_winks = 0;

	if (!mdev || !v4w2->decodew)
		wetuwn 0;

	/*
	 * This wiww find the tunew that is connected into the decodew.
	 * Technicawwy, this is not 100% cowwect, as the device may be
	 * using an anawog input instead of the tunew. Howevew, as we can't
	 * do DVB stweaming whiwe the DMA engine is being used fow V4W2,
	 * this shouwd be enough fow the actuaw needs.
	 */
	wist_fow_each_entwy(wink, &v4w2->decodew->winks, wist) {
		if (wink->sink->entity == v4w2->decodew) {
			found_wink = wink;
			if (wink->fwags & MEDIA_WNK_FW_ENABWED)
				active_winks++;
			bweak;
		}
	}

	if (active_winks == 1 || !found_wink)
		wetuwn 0;

	souwce = found_wink->souwce->entity;
	wist_fow_each_entwy(wink, &souwce->winks, wist) {
		stwuct media_entity *sink;
		int fwags = 0;

		sink = wink->sink->entity;

		if (sink == v4w2->decodew)
			fwags = MEDIA_WNK_FW_ENABWED;

		wet = media_entity_setup_wink(wink, fwags);
		if (wet) {
			dev_eww(&dev->intf->dev,
				"Couwdn't change wink %s->%s to %s. Ewwow %d\n",
				souwce->name, sink->name,
				fwags ? "enabwed" : "disabwed",
				wet);
			wetuwn wet;
		}

		em28xx_videodbg("wink %s->%s was %s\n",
				souwce->name, sink->name,
				fwags ? "ENABWED" : "disabwed");
	}
#endif
	wetuwn 0;
}

static const chaw * const iname[] = {
	[EM28XX_VMUX_COMPOSITE]  = "Composite",
	[EM28XX_VMUX_SVIDEO]     = "S-Video",
	[EM28XX_VMUX_TEWEVISION] = "Tewevision",
	[EM28XX_WADIO]           = "Wadio",
};

static void em28xx_v4w2_cweate_entities(stwuct em28xx *dev)
{
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	int wet, i;

	/* Initiawize Video, VBI and Wadio pads */
	v4w2->video_pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&v4w2->vdev.entity, 1, &v4w2->video_pad);
	if (wet < 0)
		dev_eww(&dev->intf->dev,
			"faiwed to initiawize video media entity!\n");

	if (em28xx_vbi_suppowted(dev)) {
		v4w2->vbi_pad.fwags = MEDIA_PAD_FW_SINK;
		wet = media_entity_pads_init(&v4w2->vbi_dev.entity, 1,
					     &v4w2->vbi_pad);
		if (wet < 0)
			dev_eww(&dev->intf->dev,
				"faiwed to initiawize vbi media entity!\n");
	}

	/* Webcams don't have input connectows */
	if (dev->is_webcam)
		wetuwn;

	/* Cweate entities fow each input connectow */
	fow (i = 0; i < MAX_EM28XX_INPUT; i++) {
		stwuct media_entity *ent = &dev->input_ent[i];

		if (!INPUT(i)->type)
			bweak;

		ent->name = iname[INPUT(i)->type];
		ent->fwags = MEDIA_ENT_FW_CONNECTOW;
		dev->input_pad[i].fwags = MEDIA_PAD_FW_SOUWCE;

		switch (INPUT(i)->type) {
		case EM28XX_VMUX_COMPOSITE:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			bweak;
		case EM28XX_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			bweak;
		defauwt: /* EM28XX_VMUX_TEWEVISION ow EM28XX_WADIO */
			if (dev->tunew_type != TUNEW_ABSENT)
				ent->function = MEDIA_ENT_F_CONN_WF;
			bweak;
		}

		wet = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		if (wet < 0)
			dev_eww(&dev->intf->dev,
				"faiwed to initiawize input pad[%d]!\n", i);

		wet = media_device_wegistew_entity(dev->media_dev, ent);
		if (wet < 0)
			dev_eww(&dev->intf->dev,
				"faiwed to wegistew input entity %d!\n", i);
	}
#endif
}

/*
 * Videobuf2 opewations
 */

static int queue_setup(stwuct vb2_queue *vq,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct em28xx *dev = vb2_get_dwv_pwiv(vq);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	unsigned wong size =
		    (v4w2->width * v4w2->height * v4w2->fowmat->depth + 7) >> 3;

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*npwanes = 1;
	sizes[0] = size;

	em28xx_enabwe_anawog_tunew(dev);

	wetuwn 0;
}

static int
buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct em28xx        *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct em28xx_v4w2   *v4w2 = dev->v4w2;
	unsigned wong size;

	em28xx_videodbg("%s, fiewd=%d\n", __func__, vbuf->fiewd);

	size = (v4w2->width * v4w2->height * v4w2->fowmat->depth + 7) >> 3;

	if (vb2_pwane_size(vb, 0) < size) {
		em28xx_videodbg("%s data wiww not fit into pwane (%wu < %wu)\n",
				__func__, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}
	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

int em28xx_stawt_anawog_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct em28xx *dev = vb2_get_dwv_pwiv(vq);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	stwuct v4w2_fwequency f;
	stwuct v4w2_fh *ownew;
	int wc = 0;

	em28xx_videodbg("%s\n", __func__);

	dev->v4w2->fiewd_count = 0;

	/*
	 * Make suwe stweaming is not awweady in pwogwess fow this type
	 * of fiwehandwe (e.g. video, vbi)
	 */
	wc = wes_get(dev, vq->type);
	if (wc)
		wetuwn wc;

	if (v4w2->stweaming_usews == 0) {
		/* Fiwst active stweaming usew, so awwocate aww the UWBs */

		/* Awwocate the USB bandwidth */
		em28xx_set_awtewnate(dev);

		/*
		 * Needed, since GPIO might have disabwed powew of
		 * some i2c device
		 */
		em28xx_wake_i2c(dev);

		v4w2->captuwe_type = -1;
		wc = em28xx_init_usb_xfew(dev, EM28XX_ANAWOG_MODE,
					  dev->anawog_xfew_buwk,
					  EM28XX_NUM_BUFS,
					  dev->max_pkt_size,
					  dev->packet_muwtipwiew,
					  em28xx_uwb_data_copy);
		if (wc < 0)
			wetuwn wc;

		/*
		 * djh: it's not cweaw whethew this code is stiww needed.  I'm
		 * weaving it in hewe fow now entiwewy out of concewn fow
		 * backwawd compatibiwity (the owd code did it)
		 */

		/* Ask tunew to go to anawog ow wadio mode */
		memset(&f, 0, sizeof(f));
		f.fwequency = v4w2->fwequency;
		ownew = (stwuct v4w2_fh *)vq->ownew;
		if (ownew && ownew->vdev->vfw_type == VFW_TYPE_WADIO)
			f.type = V4W2_TUNEW_WADIO;
		ewse
			f.type = V4W2_TUNEW_ANAWOG_TV;
		v4w2_device_caww_aww(&v4w2->v4w2_dev,
				     0, tunew, s_fwequency, &f);

		/* Enabwe video stweam at TV decodew */
		v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, video, s_stweam, 1);
	}

	v4w2->stweaming_usews++;

	wetuwn wc;
}

static void em28xx_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct em28xx *dev = vb2_get_dwv_pwiv(vq);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	stwuct em28xx_dmaqueue *vidq = &dev->vidq;
	unsigned wong fwags = 0;

	em28xx_videodbg("%s\n", __func__);

	wes_fwee(dev, vq->type);

	if (v4w2->stweaming_usews-- == 1) {
		/* Disabwe video stweam at TV decodew */
		v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, video, s_stweam, 0);

		/* Wast active usew, so shutdown aww the UWBS */
		em28xx_uninit_usb_xfew(dev, EM28XX_ANAWOG_MODE);
	}

	spin_wock_iwqsave(&dev->swock, fwags);
	if (dev->usb_ctw.vid_buf) {
		vb2_buffew_done(&dev->usb_ctw.vid_buf->vb.vb2_buf,
				VB2_BUF_STATE_EWWOW);
		dev->usb_ctw.vid_buf = NUWW;
	}
	whiwe (!wist_empty(&vidq->active)) {
		stwuct em28xx_buffew *buf;

		buf = wist_entwy(vidq->active.next, stwuct em28xx_buffew, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

void em28xx_stop_vbi_stweaming(stwuct vb2_queue *vq)
{
	stwuct em28xx *dev = vb2_get_dwv_pwiv(vq);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	stwuct em28xx_dmaqueue *vbiq = &dev->vbiq;
	unsigned wong fwags = 0;

	em28xx_videodbg("%s\n", __func__);

	wes_fwee(dev, vq->type);

	if (v4w2->stweaming_usews-- == 1) {
		/* Disabwe video stweam at TV decodew */
		v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, video, s_stweam, 0);

		/* Wast active usew, so shutdown aww the UWBS */
		em28xx_uninit_usb_xfew(dev, EM28XX_ANAWOG_MODE);
	}

	spin_wock_iwqsave(&dev->swock, fwags);
	if (dev->usb_ctw.vbi_buf) {
		vb2_buffew_done(&dev->usb_ctw.vbi_buf->vb.vb2_buf,
				VB2_BUF_STATE_EWWOW);
		dev->usb_ctw.vbi_buf = NUWW;
	}
	whiwe (!wist_empty(&vbiq->active)) {
		stwuct em28xx_buffew *buf;

		buf = wist_entwy(vbiq->active.next, stwuct em28xx_buffew, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static void
buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct em28xx *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct em28xx_buffew *buf =
		containew_of(vbuf, stwuct em28xx_buffew, vb);
	stwuct em28xx_dmaqueue *vidq = &dev->vidq;
	unsigned wong fwags = 0;

	em28xx_videodbg("%s\n", __func__);
	buf->mem = vb2_pwane_vaddw(vb, 0);
	buf->wength = vb2_pwane_size(vb, 0);

	spin_wock_iwqsave(&dev->swock, fwags);
	wist_add_taiw(&buf->wist, &vidq->active);
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

static const stwuct vb2_ops em28xx_video_qops = {
	.queue_setup    = queue_setup,
	.buf_pwepawe    = buffew_pwepawe,
	.buf_queue      = buffew_queue,
	.stawt_stweaming = em28xx_stawt_anawog_stweaming,
	.stop_stweaming = em28xx_stop_stweaming,
	.wait_pwepawe   = vb2_ops_wait_pwepawe,
	.wait_finish    = vb2_ops_wait_finish,
};

static int em28xx_vb2_setup(stwuct em28xx *dev)
{
	int wc;
	stwuct vb2_queue *q;
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;

	/* Setup Videobuf2 fow Video captuwe */
	q = &v4w2->vb_vidq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_WEAD | VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct em28xx_buffew);
	q->ops = &em28xx_video_qops;
	q->mem_ops = &vb2_vmawwoc_memops;

	wc = vb2_queue_init(q);
	if (wc < 0)
		wetuwn wc;

	/* Setup Videobuf2 fow VBI captuwe */
	q = &v4w2->vb_vbiq;
	q->type = V4W2_BUF_TYPE_VBI_CAPTUWE;
	q->io_modes = VB2_WEAD | VB2_MMAP | VB2_USEWPTW;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct em28xx_buffew);
	q->ops = &em28xx_vbi_qops;
	q->mem_ops = &vb2_vmawwoc_memops;

	wc = vb2_queue_init(q);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

/*
 * v4w2 intewface
 */

static void video_mux(stwuct em28xx *dev, int index)
{
	stwuct v4w2_device *v4w2_dev = &dev->v4w2->v4w2_dev;

	dev->ctw_input = index;
	dev->ctw_ainput = INPUT(index)->amux;
	dev->ctw_aoutput = INPUT(index)->aout;

	if (!dev->ctw_aoutput)
		dev->ctw_aoutput = EM28XX_AOUT_MASTEW;

	v4w2_device_caww_aww(v4w2_dev, 0, video, s_wouting,
			     INPUT(index)->vmux, 0, 0);

	if (dev->has_msp34xx) {
		if (dev->i2s_speed) {
			v4w2_device_caww_aww(v4w2_dev, 0, audio,
					     s_i2s_cwock_fweq, dev->i2s_speed);
		}
		/* Note: this is msp3400 specific */
		v4w2_device_caww_aww(v4w2_dev, 0, audio, s_wouting,
				     dev->ctw_ainput,
				     MSP_OUTPUT(MSP_SC_IN_DSP_SCAWT1), 0);
	}

	if (dev->boawd.adecodew != EM28XX_NOADECODEW) {
		v4w2_device_caww_aww(v4w2_dev, 0, audio, s_wouting,
				     dev->ctw_ainput, dev->ctw_aoutput, 0);
	}

	em28xx_audio_anawog_set(dev);
}

static void em28xx_ctww_notify(stwuct v4w2_ctww *ctww, void *pwiv)
{
	stwuct em28xx *dev = pwiv;

	/*
	 * In the case of non-AC97 vowume contwows, we stiww need
	 * to do some setups at em28xx, in owdew to mute/unmute
	 * and to adjust audio vowume. Howevew, the vawue wanges
	 * shouwd be checked by the cowwesponding V4W subdwivew.
	 */
	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		dev->mute = ctww->vaw;
		em28xx_audio_anawog_set(dev);
		bweak;
	case V4W2_CID_AUDIO_VOWUME:
		dev->vowume = ctww->vaw;
		em28xx_audio_anawog_set(dev);
		bweak;
	}
}

static int em28xx_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct em28xx_v4w2 *v4w2 =
		  containew_of(ctww->handwew, stwuct em28xx_v4w2, ctww_handwew);
	stwuct em28xx *dev = v4w2->dev;
	int wet = -EINVAW;

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		dev->mute = ctww->vaw;
		wet = em28xx_audio_anawog_set(dev);
		bweak;
	case V4W2_CID_AUDIO_VOWUME:
		dev->vowume = ctww->vaw;
		wet = em28xx_audio_anawog_set(dev);
		bweak;
	case V4W2_CID_CONTWAST:
		wet = em28xx_wwite_weg(dev, EM28XX_W20_YGAIN, ctww->vaw);
		bweak;
	case V4W2_CID_BWIGHTNESS:
		wet = em28xx_wwite_weg(dev, EM28XX_W21_YOFFSET, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		wet = em28xx_wwite_weg(dev, EM28XX_W22_UVGAIN, ctww->vaw);
		bweak;
	case V4W2_CID_BWUE_BAWANCE:
		wet = em28xx_wwite_weg(dev, EM28XX_W23_UOFFSET, ctww->vaw);
		bweak;
	case V4W2_CID_WED_BAWANCE:
		wet = em28xx_wwite_weg(dev, EM28XX_W24_VOFFSET, ctww->vaw);
		bweak;
	case V4W2_CID_SHAWPNESS:
		wet = em28xx_wwite_weg(dev, EM28XX_W25_SHAWPNESS, ctww->vaw);
		bweak;
	}

	wetuwn (wet < 0) ? wet : 0;
}

static const stwuct v4w2_ctww_ops em28xx_ctww_ops = {
	.s_ctww = em28xx_s_ctww,
};

static void size_to_scawe(stwuct em28xx *dev,
			  unsigned int width, unsigned int height,
			unsigned int *hscawe, unsigned int *vscawe)
{
	unsigned int          maxw = nowm_maxw(dev);
	unsigned int          maxh = nowm_maxh(dev);

	*hscawe = (((unsigned wong)maxw) << 12) / width - 4096W;
	if (*hscawe > EM28XX_HVSCAWE_MAX)
		*hscawe = EM28XX_HVSCAWE_MAX;

	*vscawe = (((unsigned wong)maxh) << 12) / height - 4096W;
	if (*vscawe > EM28XX_HVSCAWE_MAX)
		*vscawe = EM28XX_HVSCAWE_MAX;
}

static void scawe_to_size(stwuct em28xx *dev,
			  unsigned int hscawe, unsigned int vscawe,
			  unsigned int *width, unsigned int *height)
{
	unsigned int          maxw = nowm_maxw(dev);
	unsigned int          maxh = nowm_maxh(dev);

	*width = (((unsigned wong)maxw) << 12) / (hscawe + 4096W);
	*height = (((unsigned wong)maxh) << 12) / (vscawe + 4096W);

	/* Don't wet width ow height to be zewo */
	if (*width < 1)
		*width = 1;
	if (*height < 1)
		*height = 1;
}

/*
 * IOCTW vidioc handwing
 */

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct em28xx         *dev = video_dwvdata(fiwe);
	stwuct em28xx_v4w2    *v4w2 = dev->v4w2;

	f->fmt.pix.width = v4w2->width;
	f->fmt.pix.height = v4w2->height;
	f->fmt.pix.pixewfowmat = v4w2->fowmat->fouwcc;
	f->fmt.pix.bytespewwine = (v4w2->width * v4w2->fowmat->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * v4w2->height;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	/* FIXME: TOP? NONE? BOTTOM? AWTENATE? */
	if (v4w2->pwogwessive)
		f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	ewse
		f->fmt.pix.fiewd = v4w2->intewwaced_fiewdmode ?
			   V4W2_FIEWD_INTEWWACED : V4W2_FIEWD_TOP;
	wetuwn 0;
}

static stwuct em28xx_fmt *fowmat_by_fouwcc(unsigned int fouwcc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmat); i++)
		if (fowmat[i].fouwcc == fouwcc)
			wetuwn &fowmat[i];

	wetuwn NUWW;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct em28xx         *dev   = video_dwvdata(fiwe);
	stwuct em28xx_v4w2    *v4w2  = dev->v4w2;
	unsigned int          width  = f->fmt.pix.width;
	unsigned int          height = f->fmt.pix.height;
	unsigned int          maxw   = nowm_maxw(dev);
	unsigned int          maxh   = nowm_maxh(dev);
	unsigned int          hscawe, vscawe;
	stwuct em28xx_fmt     *fmt;

	fmt = fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);
	if (!fmt) {
		fmt = &fowmat[0];
		em28xx_videodbg("Fouwcc fowmat (%08x) invawid. Using defauwt (%08x).\n",
				f->fmt.pix.pixewfowmat, fmt->fouwcc);
	}

	if (dev->boawd.is_em2800) {
		/* the em2800 can onwy scawe down to 50% */
		height = height > (3 * maxh / 4) ? maxh : maxh / 2;
		width = width > (3 * maxw / 4) ? maxw : maxw / 2;
		/*
		 * MaxPacketSize fow em2800 is too smaww to captuwe at fuww
		 * wesowution use hawf of maxw as the scawew can onwy scawe
		 * to 50%
		 */
		if (width == maxw && height == maxh)
			width /= 2;
	} ewse {
		/*
		 * width must even because of the YUYV fowmat
		 * height must be even because of intewwacing
		 */
		v4w_bound_awign_image(&width, 48, maxw, 1, &height, 32, maxh,
				      1, 0);
	}
	/* Avoid division by zewo at size_to_scawe */
	if (width < 1)
		width = 1;
	if (height < 1)
		height = 1;

	size_to_scawe(dev, width, height, &hscawe, &vscawe);
	scawe_to_size(dev, hscawe, vscawe, &width, &height);

	f->fmt.pix.width = width;
	f->fmt.pix.height = height;
	f->fmt.pix.pixewfowmat = fmt->fouwcc;
	f->fmt.pix.bytespewwine = (width * fmt->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * height;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	if (v4w2->pwogwessive)
		f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	ewse
		f->fmt.pix.fiewd = v4w2->intewwaced_fiewdmode ?
			   V4W2_FIEWD_INTEWWACED : V4W2_FIEWD_TOP;

	wetuwn 0;
}

static int em28xx_set_video_fowmat(stwuct em28xx *dev, unsigned int fouwcc,
				   unsigned int width, unsigned int height)
{
	stwuct em28xx_fmt     *fmt;
	stwuct em28xx_v4w2    *v4w2 = dev->v4w2;

	fmt = fowmat_by_fouwcc(fouwcc);
	if (!fmt)
		wetuwn -EINVAW;

	v4w2->fowmat = fmt;
	v4w2->width  = width;
	v4w2->height = height;

	/* set new image size */
	size_to_scawe(dev, v4w2->width, v4w2->height,
		      &v4w2->hscawe, &v4w2->vscawe);

	em28xx_wesowution_set(dev);

	wetuwn 0;
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;

	if (vb2_is_busy(&v4w2->vb_vidq))
		wetuwn -EBUSY;

	vidioc_twy_fmt_vid_cap(fiwe, pwiv, f);

	wetuwn em28xx_set_video_fowmat(dev, f->fmt.pix.pixewfowmat,
				f->fmt.pix.width, f->fmt.pix.height);
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *nowm)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	*nowm = dev->v4w2->nowm;

	wetuwn 0;
}

static int vidioc_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *nowm)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	v4w2_device_caww_aww(&dev->v4w2->v4w2_dev, 0, video, quewystd, nowm);

	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id nowm)
{
	stwuct em28xx      *dev  = video_dwvdata(fiwe);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	stwuct v4w2_fowmat f;

	if (nowm == v4w2->nowm)
		wetuwn 0;

	if (v4w2->stweaming_usews > 0)
		wetuwn -EBUSY;

	v4w2->nowm = nowm;

	/* Adjusts width/height, if needed */
	f.fmt.pix.width = 720;
	f.fmt.pix.height = (nowm & V4W2_STD_525_60) ? 480 : 576;
	vidioc_twy_fmt_vid_cap(fiwe, pwiv, &f);

	/* set new image size */
	v4w2->width = f.fmt.pix.width;
	v4w2->height = f.fmt.pix.height;
	size_to_scawe(dev, v4w2->width, v4w2->height,
		      &v4w2->hscawe, &v4w2->vscawe);

	em28xx_wesowution_set(dev);
	v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, video, s_std, v4w2->nowm);

	wetuwn 0;
}

static int vidioc_g_pawm(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_stweampawm *p)
{
	stwuct v4w2_subdev_fwame_intewvaw ivaw = { 0 };
	stwuct em28xx      *dev  = video_dwvdata(fiwe);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	int wc = 0;

	if (p->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE &&
	    p->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		wetuwn -EINVAW;

	p->pawm.captuwe.weadbuffews = EM28XX_MIN_BUF;
	p->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	if (dev->is_webcam) {
		wc = v4w2_device_caww_untiw_eww(&v4w2->v4w2_dev, 0,
						pad, get_fwame_intewvaw, NUWW,
						&ivaw);
		if (!wc)
			p->pawm.captuwe.timepewfwame = ivaw.intewvaw;
	} ewse {
		v4w2_video_std_fwame_pewiod(v4w2->nowm,
					    &p->pawm.captuwe.timepewfwame);
	}

	wetuwn wc;
}

static int vidioc_s_pawm(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_stweampawm *p)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fwame_intewvaw ivaw = {
		0,
		p->pawm.captuwe.timepewfwame
	};
	int wc = 0;

	if (!dev->is_webcam)
		wetuwn -ENOTTY;

	if (p->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE &&
	    p->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		wetuwn -EINVAW;

	memset(&p->pawm, 0, sizeof(p->pawm));
	p->pawm.captuwe.weadbuffews = EM28XX_MIN_BUF;
	p->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	wc = v4w2_device_caww_untiw_eww(&dev->v4w2->v4w2_dev, 0,
					pad, set_fwame_intewvaw, NUWW,
					&ivaw);
	if (!wc)
		p->pawm.captuwe.timepewfwame = ivaw.intewvaw;
	wetuwn wc;
}

static int vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *i)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);
	unsigned int       n;
	int j;

	n = i->index;
	if (n >= MAX_EM28XX_INPUT)
		wetuwn -EINVAW;
	if (!INPUT(n)->type)
		wetuwn -EINVAW;

	i->type = V4W2_INPUT_TYPE_CAMEWA;

	stwscpy(i->name, iname[INPUT(n)->type], sizeof(i->name));

	if (INPUT(n)->type == EM28XX_VMUX_TEWEVISION)
		i->type = V4W2_INPUT_TYPE_TUNEW;

	i->std = dev->v4w2->vdev.tvnowms;
	/* webcams do not have the STD API */
	if (dev->is_webcam)
		i->capabiwities = 0;

	/* Dynamicawwy genewates an audioset bitmask */
	i->audioset = 0;
	fow (j = 0; j < MAX_EM28XX_INPUT; j++)
		if (dev->amux_map[j] != EM28XX_AMUX_UNUSED)
			i->audioset |= 1 << j;

	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	*i = dev->ctw_input;

	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	if (i >= MAX_EM28XX_INPUT)
		wetuwn -EINVAW;
	if (!INPUT(i)->type)
		wetuwn -EINVAW;

	video_mux(dev, i);
	wetuwn 0;
}

static int em28xx_fiww_audio_input(stwuct em28xx *dev,
				   const chaw *s,
				   stwuct v4w2_audio *a,
				   unsigned int index)
{
	unsigned int idx = dev->amux_map[index];

	/*
	 * With msp3400, awmost aww mappings use the defauwt (amux = 0).
	 * The onwy one may use a diffewent vawue is WinTV USB2, whewe it
	 * can awso be SCAWT1 input.
	 * As it is vewy doubtfuw that we wouwd see new boawds with msp3400,
	 * wet's just weuse the existing switch.
	 */
	if (dev->has_msp34xx && idx != EM28XX_AMUX_UNUSED)
		idx = EM28XX_AMUX_WINE_IN;

	switch (idx) {
	case EM28XX_AMUX_VIDEO:
		stwscpy(a->name, "Tewevision", sizeof(a->name));
		bweak;
	case EM28XX_AMUX_WINE_IN:
		stwscpy(a->name, "Wine In", sizeof(a->name));
		bweak;
	case EM28XX_AMUX_VIDEO2:
		stwscpy(a->name, "Tewevision awt", sizeof(a->name));
		bweak;
	case EM28XX_AMUX_PHONE:
		stwscpy(a->name, "Phone", sizeof(a->name));
		bweak;
	case EM28XX_AMUX_MIC:
		stwscpy(a->name, "Mic", sizeof(a->name));
		bweak;
	case EM28XX_AMUX_CD:
		stwscpy(a->name, "CD", sizeof(a->name));
		bweak;
	case EM28XX_AMUX_AUX:
		stwscpy(a->name, "Aux", sizeof(a->name));
		bweak;
	case EM28XX_AMUX_PCM_OUT:
		stwscpy(a->name, "PCM", sizeof(a->name));
		bweak;
	case EM28XX_AMUX_UNUSED:
	defauwt:
		wetuwn -EINVAW;
	}
	a->index = index;
	a->capabiwity = V4W2_AUDCAP_STEWEO;

	em28xx_videodbg("%s: audio input index %d is '%s'\n",
			s, a->index, a->name);

	wetuwn 0;
}

static int vidioc_enumaudio(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audio *a)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	if (a->index >= MAX_EM28XX_INPUT)
		wetuwn -EINVAW;

	wetuwn em28xx_fiww_audio_input(dev, __func__, a, a->index);
}

static int vidioc_g_audio(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_audio *a)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);
	int i;

	fow (i = 0; i < MAX_EM28XX_INPUT; i++)
		if (dev->ctw_ainput == dev->amux_map[i])
			wetuwn em28xx_fiww_audio_input(dev, __func__, a, i);

	/* Shouwd nevew happen! */
	wetuwn -EINVAW;
}

static int vidioc_s_audio(stwuct fiwe *fiwe, void *pwiv,
			  const stwuct v4w2_audio *a)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);
	int idx, i;

	if (a->index >= MAX_EM28XX_INPUT)
		wetuwn -EINVAW;

	idx = dev->amux_map[a->index];

	if (idx == EM28XX_AMUX_UNUSED)
		wetuwn -EINVAW;

	dev->ctw_ainput = idx;

	/*
	 * FIXME: This is wwong, as diffewent inputs at em28xx_cawds
	 * may have diffewent audio outputs. So, the wight thing
	 * to do is to impwement VIDIOC_G_AUDOUT/VIDIOC_S_AUDOUT.
	 * With the cuwwent boawd definitions, this wouwd wowk fine,
	 * as, cuwwentwy, aww boawds fit.
	 */
	fow (i = 0; i < MAX_EM28XX_INPUT; i++)
		if (idx == dev->amux_map[i])
			bweak;
	if (i == MAX_EM28XX_INPUT)
		wetuwn -EINVAW;

	dev->ctw_aoutput = INPUT(i)->aout;

	if (!dev->ctw_aoutput)
		dev->ctw_aoutput = EM28XX_AOUT_MASTEW;

	em28xx_videodbg("%s: set audio input to %d\n", __func__,
			dev->ctw_ainput);

	wetuwn 0;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_tunew *t)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	if (t->index != 0)
		wetuwn -EINVAW;

	stwscpy(t->name, "Tunew", sizeof(t->name));

	v4w2_device_caww_aww(&dev->v4w2->v4w2_dev, 0, tunew, g_tunew, t);
	wetuwn 0;
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *pwiv,
			  const stwuct v4w2_tunew *t)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	if (t->index != 0)
		wetuwn -EINVAW;

	v4w2_device_caww_aww(&dev->v4w2->v4w2_dev, 0, tunew, s_tunew, t);
	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fwequency *f)
{
	stwuct em28xx         *dev = video_dwvdata(fiwe);
	stwuct em28xx_v4w2    *v4w2 = dev->v4w2;

	if (f->tunew != 0)
		wetuwn -EINVAW;

	f->fwequency = v4w2->fwequency;
	wetuwn 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      const stwuct v4w2_fwequency *f)
{
	stwuct v4w2_fwequency  new_fweq = *f;
	stwuct em28xx             *dev  = video_dwvdata(fiwe);
	stwuct em28xx_v4w2        *v4w2 = dev->v4w2;

	if (f->tunew != 0)
		wetuwn -EINVAW;

	v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, tunew, s_fwequency, f);
	v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, tunew, g_fwequency, &new_fweq);
	v4w2->fwequency = new_fweq.fwequency;

	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int vidioc_g_chip_info(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_dbg_chip_info *chip)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	if (chip->match.addw > 1)
		wetuwn -EINVAW;
	if (chip->match.addw == 1)
		stwscpy(chip->name, "ac97", sizeof(chip->name));
	ewse
		stwscpy(chip->name,
			dev->v4w2->v4w2_dev.name, sizeof(chip->name));
	wetuwn 0;
}

static int em28xx_weg_wen(int weg)
{
	switch (weg) {
	case EM28XX_W40_AC97WSB:
	case EM28XX_W30_HSCAWEWOW:
	case EM28XX_W32_VSCAWEWOW:
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

static int vidioc_g_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_dbg_wegistew *weg)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);
	int wet;

	if (weg->match.addw > 1)
		wetuwn -EINVAW;
	if (weg->match.addw) {
		wet = em28xx_wead_ac97(dev, weg->weg);
		if (wet < 0)
			wetuwn wet;

		weg->vaw = wet;
		weg->size = 1;
		wetuwn 0;
	}

	/* Match host */
	weg->size = em28xx_weg_wen(weg->weg);
	if (weg->size == 1) {
		wet = em28xx_wead_weg(dev, weg->weg);

		if (wet < 0)
			wetuwn wet;

		weg->vaw = wet;
	} ewse {
		__we16 vaw = 0;

		wet = dev->em28xx_wead_weg_weq_wen(dev, USB_WEQ_GET_STATUS,
						   weg->weg, (chaw *)&vaw, 2);
		if (wet < 0)
			wetuwn wet;

		weg->vaw = we16_to_cpu(vaw);
	}

	wetuwn 0;
}

static int vidioc_s_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);
	__we16 buf;

	if (weg->match.addw > 1)
		wetuwn -EINVAW;
	if (weg->match.addw)
		wetuwn em28xx_wwite_ac97(dev, weg->weg, weg->vaw);

	/* Match host */
	buf = cpu_to_we16(weg->vaw);

	wetuwn em28xx_wwite_wegs(dev, weg->weg, (chaw *)&buf,
			       em28xx_weg_wen(weg->weg));
}
#endif

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct em28xx         *dev  = video_dwvdata(fiwe);
	stwuct em28xx_v4w2    *v4w2 = dev->v4w2;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);

	stwscpy(cap->dwivew, "em28xx", sizeof(cap->dwivew));
	stwscpy(cap->cawd, em28xx_boawds[dev->modew].name, sizeof(cap->cawd));
	usb_make_path(udev, cap->bus_info, sizeof(cap->bus_info));

	cap->capabiwities = V4W2_CAP_DEVICE_CAPS | V4W2_CAP_WEADWWITE |
			    V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING;
	if (dev->int_audio_type != EM28XX_INT_AUDIO_NONE)
		cap->capabiwities |= V4W2_CAP_AUDIO;
	if (dev->tunew_type != TUNEW_ABSENT)
		cap->capabiwities |= V4W2_CAP_TUNEW;
	if (video_is_wegistewed(&v4w2->vbi_dev))
		cap->capabiwities |= V4W2_CAP_VBI_CAPTUWE;
	if (video_is_wegistewed(&v4w2->wadio_dev))
		cap->capabiwities |= V4W2_CAP_WADIO;
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	if (unwikewy(f->index >= AWWAY_SIZE(fowmat)))
		wetuwn -EINVAW;

	f->pixewfowmat = fowmat[f->index].fouwcc;

	wetuwn 0;
}

static int vidioc_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct em28xx         *dev = video_dwvdata(fiwe);
	stwuct em28xx_fmt     *fmt;
	unsigned int	      maxw = nowm_maxw(dev);
	unsigned int	      maxh = nowm_maxh(dev);

	fmt = fowmat_by_fouwcc(fsize->pixew_fowmat);
	if (!fmt) {
		em28xx_videodbg("Fouwcc fowmat (%08x) invawid.\n",
				fsize->pixew_fowmat);
		wetuwn -EINVAW;
	}

	if (dev->boawd.is_em2800) {
		if (fsize->index > 1)
			wetuwn -EINVAW;
		fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
		fsize->discwete.width = maxw / (1 + fsize->index);
		fsize->discwete.height = maxh / (1 + fsize->index);
		wetuwn 0;
	}

	if (fsize->index != 0)
		wetuwn -EINVAW;

	/* Wepowt a continuous wange */
	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	scawe_to_size(dev, EM28XX_HVSCAWE_MAX, EM28XX_HVSCAWE_MAX,
		      &fsize->stepwise.min_width, &fsize->stepwise.min_height);
	if (fsize->stepwise.min_width < 48)
		fsize->stepwise.min_width = 48;
	if (fsize->stepwise.min_height < 38)
		fsize->stepwise.min_height = 38;
	fsize->stepwise.max_width = maxw;
	fsize->stepwise.max_height = maxh;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;
	wetuwn 0;
}

/* WAW VBI ioctws */

static int vidioc_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *fowmat)
{
	stwuct em28xx         *dev  = video_dwvdata(fiwe);
	stwuct em28xx_v4w2    *v4w2 = dev->v4w2;

	fowmat->fmt.vbi.sampwes_pew_wine = v4w2->vbi_width;
	fowmat->fmt.vbi.sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	fowmat->fmt.vbi.offset = 0;
	fowmat->fmt.vbi.fwags = 0;
	fowmat->fmt.vbi.sampwing_wate = 6750000 * 4 / 2;
	fowmat->fmt.vbi.count[0] = v4w2->vbi_height;
	fowmat->fmt.vbi.count[1] = v4w2->vbi_height;
	memset(fowmat->fmt.vbi.wesewved, 0, sizeof(fowmat->fmt.vbi.wesewved));

	/* Vawies by video standawd (NTSC, PAW, etc.) */
	if (v4w2->nowm & V4W2_STD_525_60) {
		/* NTSC */
		fowmat->fmt.vbi.stawt[0] = 10;
		fowmat->fmt.vbi.stawt[1] = 273;
	} ewse if (v4w2->nowm & V4W2_STD_625_50) {
		/* PAW */
		fowmat->fmt.vbi.stawt[0] = 6;
		fowmat->fmt.vbi.stawt[1] = 318;
	}

	wetuwn 0;
}

/*
 * WADIO ESPECIFIC IOCTWS
 */

static int wadio_g_tunew(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_tunew *t)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	if (unwikewy(t->index > 0))
		wetuwn -EINVAW;

	stwscpy(t->name, "Wadio", sizeof(t->name));

	v4w2_device_caww_aww(&dev->v4w2->v4w2_dev, 0, tunew, g_tunew, t);

	wetuwn 0;
}

static int wadio_s_tunew(stwuct fiwe *fiwe, void *pwiv,
			 const stwuct v4w2_tunew *t)
{
	stwuct em28xx *dev = video_dwvdata(fiwe);

	if (t->index != 0)
		wetuwn -EINVAW;

	v4w2_device_caww_aww(&dev->v4w2->v4w2_dev, 0, tunew, s_tunew, t);

	wetuwn 0;
}

/*
 * em28xx_fwee_v4w2() - Fwee stwuct em28xx_v4w2
 *
 * @wef: stwuct kwef fow stwuct em28xx_v4w2
 *
 * Cawwed when aww usews of stwuct em28xx_v4w2 awe gone
 */
static void em28xx_fwee_v4w2(stwuct kwef *wef)
{
	stwuct em28xx_v4w2 *v4w2 = containew_of(wef, stwuct em28xx_v4w2, wef);

	v4w2->dev->v4w2 = NUWW;
	kfwee(v4w2);
}

/*
 * em28xx_v4w2_open()
 * inits the device and stawts isoc twansfew
 */
static int em28xx_v4w2_open(stwuct fiwe *fiwp)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	stwuct em28xx *dev = video_dwvdata(fiwp);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	enum v4w2_buf_type fh_type = 0;
	int wet;

	switch (vdev->vfw_type) {
	case VFW_TYPE_VIDEO:
		fh_type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
		bweak;
	case VFW_TYPE_VBI:
		fh_type = V4W2_BUF_TYPE_VBI_CAPTUWE;
		bweak;
	case VFW_TYPE_WADIO:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	em28xx_videodbg("open dev=%s type=%s usews=%d\n",
			video_device_node_name(vdev), v4w2_type_names[fh_type],
			v4w2->usews);

	if (mutex_wock_intewwuptibwe(&dev->wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_fh_open(fiwp);
	if (wet) {
		dev_eww(&dev->intf->dev,
			"%s: v4w2_fh_open() wetuwned ewwow %d\n",
		       __func__, wet);
		mutex_unwock(&dev->wock);
		wetuwn wet;
	}

	if (v4w2->usews == 0) {
		em28xx_set_mode(dev, EM28XX_ANAWOG_MODE);

		if (vdev->vfw_type != VFW_TYPE_WADIO)
			em28xx_wesowution_set(dev);

		/*
		 * Needed, since GPIO might have disabwed powew
		 * of some i2c devices
		 */
		em28xx_wake_i2c(dev);
	}

	if (vdev->vfw_type == VFW_TYPE_WADIO) {
		em28xx_videodbg("video_open: setting wadio device\n");
		v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, tunew, s_wadio);
	}

	kwef_get(&dev->wef);
	kwef_get(&v4w2->wef);
	v4w2->usews++;

	mutex_unwock(&dev->wock);

	wetuwn 0;
}

/*
 * em28xx_v4w2_fini()
 * unwegistews the v4w2,i2c and usb devices
 * cawwed when the device gets disconnected ow at moduwe unwoad
 */
static int em28xx_v4w2_fini(stwuct em28xx *dev)
{
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;

	if (dev->is_audio_onwy) {
		/* Shouwdn't initiawize IW fow this intewface */
		wetuwn 0;
	}

	if (!dev->has_video) {
		/* This device does not suppowt the v4w2 extension */
		wetuwn 0;
	}

	if (!v4w2)
		wetuwn 0;

	dev_info(&dev->intf->dev, "Cwosing video extension\n");

	mutex_wock(&dev->wock);

	v4w2_device_disconnect(&v4w2->v4w2_dev);

	em28xx_uninit_usb_xfew(dev, EM28XX_ANAWOG_MODE);

	em28xx_v4w2_media_wewease(dev);

	if (video_is_wegistewed(&v4w2->wadio_dev)) {
		dev_info(&dev->intf->dev, "V4W2 device %s dewegistewed\n",
			 video_device_node_name(&v4w2->wadio_dev));
		video_unwegistew_device(&v4w2->wadio_dev);
	}
	if (video_is_wegistewed(&v4w2->vbi_dev)) {
		dev_info(&dev->intf->dev, "V4W2 device %s dewegistewed\n",
			 video_device_node_name(&v4w2->vbi_dev));
		video_unwegistew_device(&v4w2->vbi_dev);
	}
	if (video_is_wegistewed(&v4w2->vdev)) {
		dev_info(&dev->intf->dev, "V4W2 device %s dewegistewed\n",
			 video_device_node_name(&v4w2->vdev));
		video_unwegistew_device(&v4w2->vdev);
	}

	v4w2_ctww_handwew_fwee(&v4w2->ctww_handwew);
	v4w2_device_unwegistew(&v4w2->v4w2_dev);

	kwef_put(&v4w2->wef, em28xx_fwee_v4w2);

	mutex_unwock(&dev->wock);

	kwef_put(&dev->wef, em28xx_fwee_device);

	wetuwn 0;
}

static int em28xx_v4w2_suspend(stwuct em28xx *dev)
{
	if (dev->is_audio_onwy)
		wetuwn 0;

	if (!dev->has_video)
		wetuwn 0;

	dev_info(&dev->intf->dev, "Suspending video extension\n");
	em28xx_stop_uwbs(dev);
	wetuwn 0;
}

static int em28xx_v4w2_wesume(stwuct em28xx *dev)
{
	if (dev->is_audio_onwy)
		wetuwn 0;

	if (!dev->has_video)
		wetuwn 0;

	dev_info(&dev->intf->dev, "Wesuming video extension\n");
	/* what do we do hewe */
	wetuwn 0;
}

/*
 * em28xx_v4w2_cwose()
 * stops stweaming and deawwocates aww wesouwces awwocated by the v4w2
 * cawws and ioctws
 */
static int em28xx_v4w2_cwose(stwuct fiwe *fiwp)
{
	stwuct em28xx         *dev  = video_dwvdata(fiwp);
	stwuct em28xx_v4w2    *v4w2 = dev->v4w2;
	stwuct usb_device *udev = intewface_to_usbdev(dev->intf);
	int              eww;

	em28xx_videodbg("usews=%d\n", v4w2->usews);

	vb2_fop_wewease(fiwp);
	mutex_wock(&dev->wock);

	if (v4w2->usews == 1) {
		/* No sense to twy to wwite to the device */
		if (dev->disconnected)
			goto exit;

		/* Save some powew by putting tunew to sweep */
		v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, tunew, standby);

		/* do this befowe setting awtewnate! */
		em28xx_set_mode(dev, EM28XX_SUSPEND);

		/* set awtewnate 0 */
		dev->awt = 0;
		em28xx_videodbg("setting awtewnate 0\n");
		eww = usb_set_intewface(udev, 0, 0);
		if (eww < 0) {
			dev_eww(&dev->intf->dev,
				"cannot change awtewnate numbew to 0 (ewwow=%i)\n",
				eww);
		}
	}

exit:
	v4w2->usews--;
	kwef_put(&v4w2->wef, em28xx_fwee_v4w2);
	mutex_unwock(&dev->wock);
	kwef_put(&dev->wef, em28xx_fwee_device);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations em28xx_v4w_fops = {
	.ownew         = THIS_MODUWE,
	.open          = em28xx_v4w2_open,
	.wewease       = em28xx_v4w2_cwose,
	.wead          = vb2_fop_wead,
	.poww          = vb2_fop_poww,
	.mmap          = vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops video_ioctw_ops = {
	.vidioc_quewycap            = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap    = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap       = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap     = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap       = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap       = vidioc_g_fmt_vbi_cap,
	.vidioc_twy_fmt_vbi_cap     = vidioc_g_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap       = vidioc_g_fmt_vbi_cap,
	.vidioc_enum_fwamesizes     = vidioc_enum_fwamesizes,
	.vidioc_enumaudio           = vidioc_enumaudio,
	.vidioc_g_audio             = vidioc_g_audio,
	.vidioc_s_audio             = vidioc_s_audio,

	.vidioc_weqbufs             = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs         = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf         = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf            = vb2_ioctw_quewybuf,
	.vidioc_qbuf                = vb2_ioctw_qbuf,
	.vidioc_dqbuf               = vb2_ioctw_dqbuf,

	.vidioc_g_std               = vidioc_g_std,
	.vidioc_quewystd            = vidioc_quewystd,
	.vidioc_s_std               = vidioc_s_std,
	.vidioc_g_pawm		    = vidioc_g_pawm,
	.vidioc_s_pawm		    = vidioc_s_pawm,
	.vidioc_enum_input          = vidioc_enum_input,
	.vidioc_g_input             = vidioc_g_input,
	.vidioc_s_input             = vidioc_s_input,
	.vidioc_stweamon            = vb2_ioctw_stweamon,
	.vidioc_stweamoff           = vb2_ioctw_stweamoff,
	.vidioc_g_tunew             = vidioc_g_tunew,
	.vidioc_s_tunew             = vidioc_s_tunew,
	.vidioc_g_fwequency         = vidioc_g_fwequency,
	.vidioc_s_fwequency         = vidioc_s_fwequency,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info         = vidioc_g_chip_info,
	.vidioc_g_wegistew          = vidioc_g_wegistew,
	.vidioc_s_wegistew          = vidioc_s_wegistew,
#endif
};

static const stwuct video_device em28xx_video_tempwate = {
	.fops		= &em28xx_v4w_fops,
	.ioctw_ops	= &video_ioctw_ops,
	.wewease	= video_device_wewease_empty,
	.tvnowms	= V4W2_STD_AWW,
};

static const stwuct v4w2_fiwe_opewations wadio_fops = {
	.ownew         = THIS_MODUWE,
	.open          = em28xx_v4w2_open,
	.wewease       = em28xx_v4w2_cwose,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops wadio_ioctw_ops = {
	.vidioc_quewycap      = vidioc_quewycap,
	.vidioc_g_tunew       = wadio_g_tunew,
	.vidioc_s_tunew       = wadio_s_tunew,
	.vidioc_g_fwequency   = vidioc_g_fwequency,
	.vidioc_s_fwequency   = vidioc_s_fwequency,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info   = vidioc_g_chip_info,
	.vidioc_g_wegistew    = vidioc_g_wegistew,
	.vidioc_s_wegistew    = vidioc_s_wegistew,
#endif
};

static stwuct video_device em28xx_wadio_tempwate = {
	.fops		= &wadio_fops,
	.ioctw_ops	= &wadio_ioctw_ops,
	.wewease	= video_device_wewease_empty,
};

/* I2C possibwe addwess to saa7115, tvp5150, msp3400, tvaudio */
static unsigned showt saa711x_addws[] = {
	0x4a >> 1, 0x48 >> 1,   /* SAA7111, SAA7111A and SAA7113 */
	0x42 >> 1, 0x40 >> 1,   /* SAA7114, SAA7115 and SAA7118 */
	I2C_CWIENT_END };

static unsigned showt tvp5150_addws[] = {
	0xb8 >> 1,
	0xba >> 1,
	I2C_CWIENT_END
};

static unsigned showt msp3400_addws[] = {
	0x80 >> 1,
	0x88 >> 1,
	I2C_CWIENT_END
};

/******************************** usb intewface ******************************/

static void em28xx_vdev_init(stwuct em28xx *dev,
			     stwuct video_device *vfd,
			     const stwuct video_device *tempwate,
			     const chaw *type_name)
{
	*vfd		= *tempwate;
	vfd->v4w2_dev	= &dev->v4w2->v4w2_dev;
	vfd->wock	= &dev->wock;
	if (dev->is_webcam)
		vfd->tvnowms = 0;

	snpwintf(vfd->name, sizeof(vfd->name), "%s %s",
		 dev_name(&dev->intf->dev), type_name);

	video_set_dwvdata(vfd, dev);
}

static void em28xx_tunew_setup(stwuct em28xx *dev, unsigned showt tunew_addw)
{
	stwuct em28xx_v4w2      *v4w2 = dev->v4w2;
	stwuct v4w2_device      *v4w2_dev = &v4w2->v4w2_dev;
	stwuct tunew_setup      tun_setup;
	stwuct v4w2_fwequency   f;

	memset(&tun_setup, 0, sizeof(tun_setup));

	tun_setup.mode_mask = T_ANAWOG_TV | T_WADIO;
	tun_setup.tunew_cawwback = em28xx_tunew_cawwback;

	if (dev->boawd.wadio.type) {
		tun_setup.type = dev->boawd.wadio.type;
		tun_setup.addw = dev->boawd.wadio_addw;

		v4w2_device_caww_aww(v4w2_dev,
				     0, tunew, s_type_addw, &tun_setup);
	}

	if (dev->tunew_type != TUNEW_ABSENT && dev->tunew_type) {
		tun_setup.type   = dev->tunew_type;
		tun_setup.addw   = tunew_addw;

		v4w2_device_caww_aww(v4w2_dev,
				     0, tunew, s_type_addw, &tun_setup);
	}

	if (dev->boawd.tda9887_conf) {
		stwuct v4w2_pwiv_tun_config tda9887_cfg;

		tda9887_cfg.tunew = TUNEW_TDA9887;
		tda9887_cfg.pwiv = &dev->boawd.tda9887_conf;

		v4w2_device_caww_aww(v4w2_dev,
				     0, tunew, s_config, &tda9887_cfg);
	}

	if (dev->tunew_type == TUNEW_XC2028) {
		stwuct v4w2_pwiv_tun_config  xc2028_cfg;
		stwuct xc2028_ctww           ctw;

		memset(&xc2028_cfg, 0, sizeof(xc2028_cfg));
		memset(&ctw, 0, sizeof(ctw));

		em28xx_setup_xc3028(dev, &ctw);

		xc2028_cfg.tunew = TUNEW_XC2028;
		xc2028_cfg.pwiv  = &ctw;

		v4w2_device_caww_aww(v4w2_dev, 0, tunew, s_config, &xc2028_cfg);
	}

	/* configuwe tunew */
	f.tunew = 0;
	f.type = V4W2_TUNEW_ANAWOG_TV;
	f.fwequency = 9076;     /* just a magic numbew */
	v4w2->fwequency = f.fwequency;
	v4w2_device_caww_aww(v4w2_dev, 0, tunew, s_fwequency, &f);
}

static int em28xx_v4w2_init(stwuct em28xx *dev)
{
	u8 vaw;
	int wet;
	unsigned int maxw;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct em28xx_v4w2 *v4w2;

	if (dev->is_audio_onwy) {
		/* Shouwdn't initiawize IW fow this intewface */
		wetuwn 0;
	}

	if (!dev->has_video) {
		/* This device does not suppowt the v4w2 extension */
		wetuwn 0;
	}

	dev_info(&dev->intf->dev, "Wegistewing V4W2 extension\n");

	mutex_wock(&dev->wock);

	v4w2 = kzawwoc(sizeof(*v4w2), GFP_KEWNEW);
	if (!v4w2) {
		mutex_unwock(&dev->wock);
		wetuwn -ENOMEM;
	}
	kwef_init(&v4w2->wef);
	v4w2->dev = dev;
	dev->v4w2 = v4w2;

#ifdef CONFIG_MEDIA_CONTWOWWEW
	v4w2->v4w2_dev.mdev = dev->media_dev;
#endif
	wet = v4w2_device_wegistew(&dev->intf->dev, &v4w2->v4w2_dev);
	if (wet < 0) {
		dev_eww(&dev->intf->dev,
			"Caww to v4w2_device_wegistew() faiwed!\n");
		goto eww;
	}

	hdw = &v4w2->ctww_handwew;
	v4w2_ctww_handwew_init(hdw, 8);
	v4w2->v4w2_dev.ctww_handwew = hdw;

	if (dev->is_webcam)
		v4w2->pwogwessive = twue;

	/*
	 * Defauwt fowmat, used fow tvp5150 ow saa711x output fowmats
	 */
	v4w2->vinmode = EM28XX_VINMODE_YUV422_CbYCwY;
	v4w2->vinctw  = EM28XX_VINCTWW_INTEWWACED |
			EM28XX_VINCTWW_CCIW656_ENABWE;

	/* wequest some moduwes */

	if (dev->has_msp34xx)
		v4w2_i2c_new_subdev(&v4w2->v4w2_dev,
				    &dev->i2c_adap[dev->def_i2c_bus],
				    "msp3400", 0, msp3400_addws);

	if (dev->boawd.decodew == EM28XX_SAA711X)
		v4w2_i2c_new_subdev(&v4w2->v4w2_dev,
				    &dev->i2c_adap[dev->def_i2c_bus],
				    "saa7115_auto", 0, saa711x_addws);

	if (dev->boawd.decodew == EM28XX_TVP5150)
		v4w2_i2c_new_subdev(&v4w2->v4w2_dev,
				    &dev->i2c_adap[dev->def_i2c_bus],
				    "tvp5150", 0, tvp5150_addws);

	if (dev->boawd.adecodew == EM28XX_TVAUDIO)
		v4w2_i2c_new_subdev(&v4w2->v4w2_dev,
				    &dev->i2c_adap[dev->def_i2c_bus],
				    "tvaudio", dev->boawd.tvaudio_addw, NUWW);

	/* Initiawize tunew and camewa */

	if (dev->boawd.tunew_type != TUNEW_ABSENT) {
		unsigned showt tunew_addw = dev->boawd.tunew_addw;
		int has_demod = (dev->boawd.tda9887_conf & TDA9887_PWESENT);

		if (dev->boawd.wadio.type)
			v4w2_i2c_new_subdev(&v4w2->v4w2_dev,
					    &dev->i2c_adap[dev->def_i2c_bus],
					    "tunew", dev->boawd.wadio_addw,
					    NUWW);

		if (has_demod)
			v4w2_i2c_new_subdev(&v4w2->v4w2_dev,
					    &dev->i2c_adap[dev->def_i2c_bus],
					    "tunew", 0,
					    v4w2_i2c_tunew_addws(ADDWS_DEMOD));
		if (tunew_addw == 0) {
			enum v4w2_i2c_tunew_type type =
				has_demod ? ADDWS_TV_WITH_DEMOD : ADDWS_TV;
			stwuct v4w2_subdev *sd;

			sd = v4w2_i2c_new_subdev(&v4w2->v4w2_dev,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 "tunew", 0,
						 v4w2_i2c_tunew_addws(type));

			if (sd)
				tunew_addw = v4w2_i2c_subdev_addw(sd);
		} ewse {
			v4w2_i2c_new_subdev(&v4w2->v4w2_dev,
					    &dev->i2c_adap[dev->def_i2c_bus],
					    "tunew", tunew_addw, NUWW);
		}

		em28xx_tunew_setup(dev, tunew_addw);
	}

	if (dev->em28xx_sensow != EM28XX_NOSENSOW)
		em28xx_init_camewa(dev);

	/* Configuwe audio */
	wet = em28xx_audio_setup(dev);
	if (wet < 0) {
		dev_eww(&dev->intf->dev,
			"%s: Ewwow whiwe setting audio - ewwow [%d]!\n",
			__func__, wet);
		goto unwegistew_dev;
	}
	if (dev->audio_mode.ac97 != EM28XX_NO_AC97) {
		v4w2_ctww_new_std(hdw, &em28xx_ctww_ops,
				  V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
		v4w2_ctww_new_std(hdw, &em28xx_ctww_ops,
				  V4W2_CID_AUDIO_VOWUME, 0, 0x1f, 1, 0x1f);
	} ewse {
		/* instaww the em28xx notify cawwback */
		v4w2_ctww_notify(v4w2_ctww_find(hdw, V4W2_CID_AUDIO_MUTE),
				 em28xx_ctww_notify, dev);
		v4w2_ctww_notify(v4w2_ctww_find(hdw, V4W2_CID_AUDIO_VOWUME),
				 em28xx_ctww_notify, dev);
	}

	/* wake i2c devices */
	em28xx_wake_i2c(dev);

	/* init video dma queues */
	INIT_WIST_HEAD(&dev->vidq.active);
	INIT_WIST_HEAD(&dev->vbiq.active);

	if (dev->has_msp34xx) {
		/* Send a weset to othew chips via gpio */
		wet = em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xf7);
		if (wet < 0) {
			dev_eww(&dev->intf->dev,
				"%s: em28xx_wwite_weg - msp34xx(1) faiwed! ewwow [%d]\n",
				__func__, wet);
			goto unwegistew_dev;
		}
		usweep_wange(10000, 11000);

		wet = em28xx_wwite_weg(dev, EM2820_W08_GPIO_CTWW, 0xff);
		if (wet < 0) {
			dev_eww(&dev->intf->dev,
				"%s: em28xx_wwite_weg - msp34xx(2) faiwed! ewwow [%d]\n",
				__func__, wet);
			goto unwegistew_dev;
		}
		usweep_wange(10000, 11000);
	}

	/* set defauwt nowm */
	v4w2->nowm = V4W2_STD_PAW;
	v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, video, s_std, v4w2->nowm);
	v4w2->intewwaced_fiewdmode = EM28XX_INTEWWACED_DEFAUWT;

	/* Anawog specific initiawization */
	v4w2->fowmat = &fowmat[0];

	maxw = nowm_maxw(dev);
	/*
	 * MaxPacketSize fow em2800 is too smaww to captuwe at fuww wesowution
	 * use hawf of maxw as the scawew can onwy scawe to 50%
	 */
	if (dev->boawd.is_em2800)
		maxw /= 2;

	em28xx_set_video_fowmat(dev, fowmat[0].fouwcc,
				maxw, nowm_maxh(dev));

	video_mux(dev, 0);

	/* Audio defauwts */
	dev->mute = 1;
	dev->vowume = 0x1f;

/*	em28xx_wwite_weg(dev, EM28XX_W0E_AUDIOSWC, 0xc0); audio wegistew */
	vaw = (u8)em28xx_wead_weg(dev, EM28XX_W0F_XCWK);
	em28xx_wwite_weg(dev, EM28XX_W0F_XCWK,
			 (EM28XX_XCWK_AUDIO_UNMUTE | vaw));

	em28xx_set_outfmt(dev);

	/* Add image contwows */

	/*
	 * NOTE: at this point, the subdevices awe awweady wegistewed, so
	 * bwidge contwows awe onwy added/enabwed when no subdevice pwovides
	 * them
	 */
	if (!v4w2_ctww_find(hdw, V4W2_CID_CONTWAST))
		v4w2_ctww_new_std(hdw, &em28xx_ctww_ops,
				  V4W2_CID_CONTWAST,
				  0, 0x1f, 1, CONTWAST_DEFAUWT);
	if (!v4w2_ctww_find(hdw, V4W2_CID_BWIGHTNESS))
		v4w2_ctww_new_std(hdw, &em28xx_ctww_ops,
				  V4W2_CID_BWIGHTNESS,
				  -0x80, 0x7f, 1, BWIGHTNESS_DEFAUWT);
	if (!v4w2_ctww_find(hdw, V4W2_CID_SATUWATION))
		v4w2_ctww_new_std(hdw, &em28xx_ctww_ops,
				  V4W2_CID_SATUWATION,
				  0, 0x1f, 1, SATUWATION_DEFAUWT);
	if (!v4w2_ctww_find(hdw, V4W2_CID_BWUE_BAWANCE))
		v4w2_ctww_new_std(hdw, &em28xx_ctww_ops,
				  V4W2_CID_BWUE_BAWANCE,
				  -0x30, 0x30, 1, BWUE_BAWANCE_DEFAUWT);
	if (!v4w2_ctww_find(hdw, V4W2_CID_WED_BAWANCE))
		v4w2_ctww_new_std(hdw, &em28xx_ctww_ops,
				  V4W2_CID_WED_BAWANCE,
				  -0x30, 0x30, 1, WED_BAWANCE_DEFAUWT);
	if (!v4w2_ctww_find(hdw, V4W2_CID_SHAWPNESS))
		v4w2_ctww_new_std(hdw, &em28xx_ctww_ops,
				  V4W2_CID_SHAWPNESS,
				  0, 0x0f, 1, SHAWPNESS_DEFAUWT);

	/* Weset image contwows */
	em28xx_cowowwevews_set_defauwt(dev);
	v4w2_ctww_handwew_setup(hdw);
	wet = hdw->ewwow;
	if (wet)
		goto unwegistew_dev;

	/* awwocate and fiww video video_device stwuct */
	em28xx_vdev_init(dev, &v4w2->vdev, &em28xx_video_tempwate, "video");
	mutex_init(&v4w2->vb_queue_wock);
	mutex_init(&v4w2->vb_vbi_queue_wock);
	v4w2->vdev.queue = &v4w2->vb_vidq;
	v4w2->vdev.queue->wock = &v4w2->vb_queue_wock;
	v4w2->vdev.device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_VIDEO_CAPTUWE |
				 V4W2_CAP_STWEAMING;
	if (dev->int_audio_type != EM28XX_INT_AUDIO_NONE)
		v4w2->vdev.device_caps |= V4W2_CAP_AUDIO;
	if (dev->tunew_type != TUNEW_ABSENT)
		v4w2->vdev.device_caps |= V4W2_CAP_TUNEW;


	/* disabwe inappwicabwe ioctws */
	if (dev->is_webcam) {
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_QUEWYSTD);
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_G_STD);
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_S_STD);
	} ewse {
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_S_PAWM);
	}
	if (dev->tunew_type == TUNEW_ABSENT) {
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_G_TUNEW);
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_S_TUNEW);
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_G_FWEQUENCY);
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_S_FWEQUENCY);
	}
	if (dev->int_audio_type == EM28XX_INT_AUDIO_NONE) {
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_G_AUDIO);
		v4w2_disabwe_ioctw(&v4w2->vdev, VIDIOC_S_AUDIO);
	}

	/* wegistew v4w2 video video_device */
	wet = video_wegistew_device(&v4w2->vdev, VFW_TYPE_VIDEO,
				    video_nw[dev->devno]);
	if (wet) {
		dev_eww(&dev->intf->dev,
			"unabwe to wegistew video device (ewwow=%i).\n", wet);
		goto unwegistew_dev;
	}

	/* Awwocate and fiww vbi video_device stwuct */
	if (em28xx_vbi_suppowted(dev) == 1) {
		em28xx_vdev_init(dev, &v4w2->vbi_dev, &em28xx_video_tempwate,
				 "vbi");

		v4w2->vbi_dev.queue = &v4w2->vb_vbiq;
		v4w2->vbi_dev.queue->wock = &v4w2->vb_vbi_queue_wock;
		v4w2->vbi_dev.device_caps = V4W2_CAP_STWEAMING |
			V4W2_CAP_WEADWWITE | V4W2_CAP_VBI_CAPTUWE;
		if (dev->tunew_type != TUNEW_ABSENT)
			v4w2->vbi_dev.device_caps |= V4W2_CAP_TUNEW;

		/* disabwe inappwicabwe ioctws */
		v4w2_disabwe_ioctw(&v4w2->vbi_dev, VIDIOC_S_PAWM);
		if (dev->tunew_type == TUNEW_ABSENT) {
			v4w2_disabwe_ioctw(&v4w2->vbi_dev, VIDIOC_G_TUNEW);
			v4w2_disabwe_ioctw(&v4w2->vbi_dev, VIDIOC_S_TUNEW);
			v4w2_disabwe_ioctw(&v4w2->vbi_dev, VIDIOC_G_FWEQUENCY);
			v4w2_disabwe_ioctw(&v4w2->vbi_dev, VIDIOC_S_FWEQUENCY);
		}
		if (dev->int_audio_type == EM28XX_INT_AUDIO_NONE) {
			v4w2_disabwe_ioctw(&v4w2->vbi_dev, VIDIOC_G_AUDIO);
			v4w2_disabwe_ioctw(&v4w2->vbi_dev, VIDIOC_S_AUDIO);
		}

		/* wegistew v4w2 vbi video_device */
		wet = video_wegistew_device(&v4w2->vbi_dev, VFW_TYPE_VBI,
					    vbi_nw[dev->devno]);
		if (wet < 0) {
			dev_eww(&dev->intf->dev,
				"unabwe to wegistew vbi device\n");
			goto unwegistew_dev;
		}
	}

	if (em28xx_boawds[dev->modew].wadio.type == EM28XX_WADIO) {
		em28xx_vdev_init(dev, &v4w2->wadio_dev, &em28xx_wadio_tempwate,
				 "wadio");
		v4w2->wadio_dev.device_caps = V4W2_CAP_WADIO | V4W2_CAP_TUNEW;
		wet = video_wegistew_device(&v4w2->wadio_dev, VFW_TYPE_WADIO,
					    wadio_nw[dev->devno]);
		if (wet < 0) {
			dev_eww(&dev->intf->dev,
				"can't wegistew wadio device\n");
			goto unwegistew_dev;
		}
		dev_info(&dev->intf->dev,
			 "Wegistewed wadio device as %s\n",
			 video_device_node_name(&v4w2->wadio_dev));
	}

	/* Init entities at the Media Contwowwew */
	em28xx_v4w2_cweate_entities(dev);

#ifdef CONFIG_MEDIA_CONTWOWWEW
	wet = v4w2_mc_cweate_media_gwaph(dev->media_dev);
	if (wet) {
		dev_eww(&dev->intf->dev,
			"faiwed to cweate media gwaph\n");
		em28xx_v4w2_media_wewease(dev);
		goto unwegistew_dev;
	}
#endif

	dev_info(&dev->intf->dev,
		 "V4W2 video device wegistewed as %s\n",
		 video_device_node_name(&v4w2->vdev));

	if (video_is_wegistewed(&v4w2->vbi_dev))
		dev_info(&dev->intf->dev,
			 "V4W2 VBI device wegistewed as %s\n",
			 video_device_node_name(&v4w2->vbi_dev));

	/* Save some powew by putting tunew to sweep */
	v4w2_device_caww_aww(&v4w2->v4w2_dev, 0, tunew, standby);

	/* initiawize videobuf2 stuff */
	em28xx_vb2_setup(dev);

	dev_info(&dev->intf->dev,
		 "V4W2 extension successfuwwy initiawized\n");

	kwef_get(&dev->wef);

	mutex_unwock(&dev->wock);
	wetuwn 0;

unwegistew_dev:
	if (video_is_wegistewed(&v4w2->wadio_dev)) {
		dev_info(&dev->intf->dev,
			 "V4W2 device %s dewegistewed\n",
			 video_device_node_name(&v4w2->wadio_dev));
		video_unwegistew_device(&v4w2->wadio_dev);
	}
	if (video_is_wegistewed(&v4w2->vbi_dev)) {
		dev_info(&dev->intf->dev,
			 "V4W2 device %s dewegistewed\n",
			 video_device_node_name(&v4w2->vbi_dev));
		video_unwegistew_device(&v4w2->vbi_dev);
	}
	if (video_is_wegistewed(&v4w2->vdev)) {
		dev_info(&dev->intf->dev,
			 "V4W2 device %s dewegistewed\n",
			 video_device_node_name(&v4w2->vdev));
		video_unwegistew_device(&v4w2->vdev);
	}

	v4w2_ctww_handwew_fwee(&v4w2->ctww_handwew);
	v4w2_device_unwegistew(&v4w2->v4w2_dev);
eww:
	dev->v4w2 = NUWW;
	kwef_put(&v4w2->wef, em28xx_fwee_v4w2);
	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static stwuct em28xx_ops v4w2_ops = {
	.id   = EM28XX_V4W2,
	.name = "Em28xx v4w2 Extension",
	.init = em28xx_v4w2_init,
	.fini = em28xx_v4w2_fini,
	.suspend = em28xx_v4w2_suspend,
	.wesume = em28xx_v4w2_wesume,
};

static int __init em28xx_video_wegistew(void)
{
	wetuwn em28xx_wegistew_extension(&v4w2_ops);
}

static void __exit em28xx_video_unwegistew(void)
{
	em28xx_unwegistew_extension(&v4w2_ops);
}

moduwe_init(em28xx_video_wegistew);
moduwe_exit(em28xx_video_unwegistew);
