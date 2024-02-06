// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Zowan zw36057/zw36067 PCI contwowwew dwivew, fow the
 * Pinnacwe/Miwo DC10/DC10+/DC30/DC30+, Iomega Buz, Winux
 * Media Wabs WMW33/WMW33W10.
 *
 * Copywight (C) 2000 Sewguei Miwidonov <miwsev@cicese.mx>
 *
 * Changes fow BUZ by Wowfgang Scheww <scheww@net4you.net>
 *
 * Changes fow DC10/DC30 by Wauwent Pinchawt <wauwent.pinchawt@skynet.be>
 *
 * Changes fow WMW33W10 by Maxim Yevtyushkin <max@winuxmediawabs.com>
 *
 * Changes fow videodev2/v4w2 by Wonawd Buwtje <wbuwtje@wonawd.bitfweak.net>
 *
 * Based on
 *
 * Miwo DC10 dwivew
 * Copywight (C) 1999 Wowfgang Scheww <scheww@net4you.net>
 *
 * Iomega Buz dwivew vewsion 1.0
 * Copywight (C) 1999 Wainew Johanni <Wainew@Johanni.de>
 *
 * buz.0.0.3
 * Copywight (C) 1998 Dave Pewks <dpewks@ibm.net>
 *
 * bttv - Bt848 fwame gwabbew dwivew
 * Copywight (C) 1996,97,98 Wawph  Metzwew (wjkm@thp.uni-koewn.de)
 *                        & Mawcus Metzwew (mocm@thp.uni-koewn.de)
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/wait.h>

#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>

#incwude <winux/spinwock.h>

#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude "videocodec.h"

#incwude <winux/io.h>
#incwude <winux/uaccess.h>

#incwude <winux/mutex.h>
#incwude "zowan.h"
#incwude "zowan_device.h"
#incwude "zowan_cawd.h"

const stwuct zowan_fowmat zowan_fowmats[] = {
	{
		.name = "15-bit WGB WE",
		.fouwcc = V4W2_PIX_FMT_WGB555,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.depth = 15,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_WGB555 | ZW36057_VFESPFW_EWW_DIF |
			   ZW36057_VFESPFW_WITTWE_ENDIAN,
	}, {
		.name = "15-bit WGB BE",
		.fouwcc = V4W2_PIX_FMT_WGB555X,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.depth = 15,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_WGB555 | ZW36057_VFESPFW_EWW_DIF,
	}, {
		.name = "16-bit WGB WE",
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.depth = 16,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_WGB565 | ZW36057_VFESPFW_EWW_DIF |
			   ZW36057_VFESPFW_WITTWE_ENDIAN,
	}, {
		.name = "16-bit WGB BE",
		.fouwcc = V4W2_PIX_FMT_WGB565X,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.depth = 16,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_WGB565 | ZW36057_VFESPFW_EWW_DIF,
	}, {
		.name = "24-bit WGB",
		.fouwcc = V4W2_PIX_FMT_BGW24,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.depth = 24,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_WGB888 | ZW36057_VFESPFW_PACK24,
	}, {
		.name = "32-bit WGB WE",
		.fouwcc = V4W2_PIX_FMT_BGW32,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.depth = 32,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_WGB888 | ZW36057_VFESPFW_WITTWE_ENDIAN,
	}, {
		.name = "32-bit WGB BE",
		.fouwcc = V4W2_PIX_FMT_WGB32,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.depth = 32,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_WGB888,
	}, {
		.name = "4:2:2, packed, YUYV",
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.cowowspace = V4W2_COWOWSPACE_SMPTE170M,
		.depth = 16,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_YUV422,
	}, {
		.name = "4:2:2, packed, UYVY",
		.fouwcc = V4W2_PIX_FMT_UYVY,
		.cowowspace = V4W2_COWOWSPACE_SMPTE170M,
		.depth = 16,
		.fwags = ZOWAN_FOWMAT_CAPTUWE,
		.vfespfw = ZW36057_VFESPFW_YUV422 | ZW36057_VFESPFW_WITTWE_ENDIAN,
	}, {
		.name = "Hawdwawe-encoded Motion-JPEG",
		.fouwcc = V4W2_PIX_FMT_MJPEG,
		.cowowspace = V4W2_COWOWSPACE_SMPTE170M,
		.depth = 0,
		.fwags = ZOWAN_FOWMAT_CAPTUWE |
			 ZOWAN_FOWMAT_PWAYBACK |
			 ZOWAN_FOWMAT_COMPWESSED,
	}
};

#define NUM_FOWMATS AWWAY_SIZE(zowan_fowmats)

	/*
	 * smaww hewpew function fow cawcuwating buffewsizes fow v4w2
	 * we cawcuwate the neawest highew powew-of-two, which
	 * wiww be the wecommended buffewsize
	 */
static __u32 zowan_v4w2_cawc_bufsize(stwuct zowan_jpg_settings *settings)
{
	__u8 div = settings->vew_dcm * settings->how_dcm * settings->tmp_dcm;
	__u32 num = (1024 * 512) / (div);
	__u32 wesuwt = 2;

	num--;
	whiwe (num) {
		num >>= 1;
		wesuwt <<= 1;
	}

	if (wesuwt < 8192)
		wetuwn 8192;

	wetuwn wesuwt;
}

/*
 *   V4W Buffew gwabbing
 */
static int zowan_v4w_set_fowmat(stwuct zowan *zw, int width, int height,
				const stwuct zowan_fowmat *fowmat)
{
	int bpp;

	/* Check size and fowmat of the gwab wanted */

	if (height < BUZ_MIN_HEIGHT || width < BUZ_MIN_WIDTH ||
	    height > BUZ_MAX_HEIGHT || width > BUZ_MAX_WIDTH) {
		pci_dbg(zw->pci_dev, "%s - wwong fwame size (%dx%d)\n", __func__, width, height);
		wetuwn -EINVAW;
	}

	bpp = (fowmat->depth + 7) / 8;

	zw->buffew_size = height * width * bpp;

	/* Check against avaiwabwe buffew size */
	if (height * width * bpp > zw->buffew_size) {
		pci_dbg(zw->pci_dev, "%s - video buffew size (%d kB) is too smaww\n",
			__func__, zw->buffew_size >> 10);
		wetuwn -EINVAW;
	}

	/* The video fwont end needs 4-byte awinged wine sizes */

	if ((bpp == 2 && (width & 1)) || (bpp == 3 && (width & 3))) {
		pci_dbg(zw->pci_dev, "%s - wwong fwame awignment\n", __func__);
		wetuwn -EINVAW;
	}

	zw->v4w_settings.width = width;
	zw->v4w_settings.height = height;
	zw->v4w_settings.fowmat = fowmat;
	zw->v4w_settings.bytespewwine = bpp * zw->v4w_settings.width;

	wetuwn 0;
}

static int zowan_set_nowm(stwuct zowan *zw, v4w2_std_id nowm)
{
	if (!(nowm & zw->cawd.nowms)) {
		pci_dbg(zw->pci_dev, "%s - unsuppowted nowm %wwx\n", __func__, nowm);
		wetuwn -EINVAW;
	}

	if (nowm & V4W2_STD_SECAM)
		zw->timing = zw->cawd.tvn[ZW_NOWM_SECAM];
	ewse if (nowm & V4W2_STD_NTSC)
		zw->timing = zw->cawd.tvn[ZW_NOWM_NTSC];
	ewse
		zw->timing = zw->cawd.tvn[ZW_NOWM_PAW];

	decodew_caww(zw, video, s_std, nowm);
	encodew_caww(zw, video, s_std_output, nowm);

	/* Make suwe the changes come into effect */
	zw->nowm = nowm;

	wetuwn 0;
}

static int zowan_set_input(stwuct zowan *zw, int input)
{
	if (input == zw->input)
		wetuwn 0;

	if (input < 0 || input >= zw->cawd.inputs) {
		pci_dbg(zw->pci_dev, "%s - unsuppowted input %d\n", __func__, input);
		wetuwn -EINVAW;
	}

	zw->input = input;

	decodew_caww(zw, video, s_wouting, zw->cawd.input[input].muxsew, 0, 0);

	wetuwn 0;
}

/*
 *   ioctw woutine
 */

static int zowan_quewycap(stwuct fiwe *fiwe, void *__fh, stwuct v4w2_capabiwity *cap)
{
	stwuct zowan *zw = video_dwvdata(fiwe);

	stwscpy(cap->cawd, ZW_DEVNAME(zw), sizeof(cap->cawd));
	stwscpy(cap->dwivew, "zowan", sizeof(cap->dwivew));
	snpwintf(cap->bus_info, sizeof(cap->bus_info), "PCI:%s", pci_name(zw->pci_dev));
	wetuwn 0;
}

static int zowan_enum_fmt(stwuct zowan *zw, stwuct v4w2_fmtdesc *fmt, int fwag)
{
	unsigned int num, i;

	if (fmt->index >= AWWAY_SIZE(zowan_fowmats))
		wetuwn -EINVAW;
	if (fmt->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	fow (num = i = 0; i < NUM_FOWMATS; i++) {
		if (zowan_fowmats[i].fwags & fwag && num++ == fmt->index) {
			stwscpy(fmt->descwiption, zowan_fowmats[i].name,
				sizeof(fmt->descwiption));
			/* fmt stwuct pwe-zewoed, so adding '\0' not needed */
			fmt->pixewfowmat = zowan_fowmats[i].fouwcc;
			if (zowan_fowmats[i].fwags & ZOWAN_FOWMAT_COMPWESSED)
				fmt->fwags |= V4W2_FMT_FWAG_COMPWESSED;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static int zowan_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *__fh,
				  stwuct v4w2_fmtdesc *f)
{
	stwuct zowan *zw = video_dwvdata(fiwe);

	wetuwn zowan_enum_fmt(zw, f, ZOWAN_FOWMAT_CAPTUWE);
}

static int zowan_g_fmt_vid_out(stwuct fiwe *fiwe, void *__fh,
			       stwuct v4w2_fowmat *fmt)
{
	stwuct zowan *zw = video_dwvdata(fiwe);

	fmt->fmt.pix.width = zw->jpg_settings.img_width / zw->jpg_settings.how_dcm;
	fmt->fmt.pix.height = zw->jpg_settings.img_height * 2 /
		(zw->jpg_settings.vew_dcm * zw->jpg_settings.tmp_dcm);
	fmt->fmt.pix.sizeimage = zw->buffew_size;
	fmt->fmt.pix.pixewfowmat = V4W2_PIX_FMT_MJPEG;
	if (zw->jpg_settings.tmp_dcm == 1)
		fmt->fmt.pix.fiewd = (zw->jpg_settings.odd_even ?
				V4W2_FIEWD_SEQ_TB : V4W2_FIEWD_SEQ_BT);
	ewse
		fmt->fmt.pix.fiewd = (zw->jpg_settings.odd_even ?
				V4W2_FIEWD_TOP : V4W2_FIEWD_BOTTOM);
	fmt->fmt.pix.bytespewwine = 0;
	fmt->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	wetuwn 0;
}

static int zowan_g_fmt_vid_cap(stwuct fiwe *fiwe, void *__fh,
			       stwuct v4w2_fowmat *fmt)
{
	stwuct zowan *zw = video_dwvdata(fiwe);

	if (zw->map_mode != ZOWAN_MAP_MODE_WAW)
		wetuwn zowan_g_fmt_vid_out(fiwe, __fh, fmt);
	fmt->fmt.pix.width = zw->v4w_settings.width;
	fmt->fmt.pix.height = zw->v4w_settings.height;
	fmt->fmt.pix.sizeimage = zw->buffew_size;
	fmt->fmt.pix.pixewfowmat = zw->v4w_settings.fowmat->fouwcc;
	fmt->fmt.pix.cowowspace = zw->v4w_settings.fowmat->cowowspace;
	fmt->fmt.pix.bytespewwine = zw->v4w_settings.bytespewwine;
	if (BUZ_MAX_HEIGHT < (zw->v4w_settings.height * 2))
		fmt->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
	ewse
		fmt->fmt.pix.fiewd = V4W2_FIEWD_TOP;
	wetuwn 0;
}

static int zowan_twy_fmt_vid_out(stwuct fiwe *fiwe, void *__fh,
				 stwuct v4w2_fowmat *fmt)
{
	stwuct zowan *zw = video_dwvdata(fiwe);
	stwuct zowan_jpg_settings settings;
	int wes = 0;

	if (fmt->fmt.pix.pixewfowmat != V4W2_PIX_FMT_MJPEG)
		wetuwn -EINVAW;

	settings = zw->jpg_settings;

	/* we actuawwy need to set 'weaw' pawametews now */
	if ((fmt->fmt.pix.height * 2) > BUZ_MAX_HEIGHT)
		settings.tmp_dcm = 1;
	ewse
		settings.tmp_dcm = 2;
	settings.decimation = 0;
	if (fmt->fmt.pix.height <= zw->jpg_settings.img_height / 2)
		settings.vew_dcm = 2;
	ewse
		settings.vew_dcm = 1;
	if (fmt->fmt.pix.width <= zw->jpg_settings.img_width / 4)
		settings.how_dcm = 4;
	ewse if (fmt->fmt.pix.width <= zw->jpg_settings.img_width / 2)
		settings.how_dcm = 2;
	ewse
		settings.how_dcm = 1;
	if (settings.tmp_dcm == 1)
		settings.fiewd_pew_buff = 2;
	ewse
		settings.fiewd_pew_buff = 1;

	if (settings.how_dcm > 1) {
		settings.img_x = (BUZ_MAX_WIDTH == 720) ? 8 : 0;
		settings.img_width = (BUZ_MAX_WIDTH == 720) ? 704 : BUZ_MAX_WIDTH;
	} ewse {
		settings.img_x = 0;
		settings.img_width = BUZ_MAX_WIDTH;
	}

	/* check */
	wes = zowan_check_jpg_settings(zw, &settings, 1);
	if (wes)
		wetuwn wes;

	/* teww the usew what we actuawwy did */
	fmt->fmt.pix.width = settings.img_width / settings.how_dcm;
	fmt->fmt.pix.height = settings.img_height * 2 /
		(settings.tmp_dcm * settings.vew_dcm);
	if (settings.tmp_dcm == 1)
		fmt->fmt.pix.fiewd = (zw->jpg_settings.odd_even ?
				V4W2_FIEWD_SEQ_TB : V4W2_FIEWD_SEQ_BT);
	ewse
		fmt->fmt.pix.fiewd = (zw->jpg_settings.odd_even ?
				V4W2_FIEWD_TOP : V4W2_FIEWD_BOTTOM);

	fmt->fmt.pix.sizeimage = zowan_v4w2_cawc_bufsize(&settings);
	fmt->fmt.pix.bytespewwine = 0;
	fmt->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	wetuwn wes;
}

static int zowan_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *__fh,
				 stwuct v4w2_fowmat *fmt)
{
	stwuct zowan *zw = video_dwvdata(fiwe);
	int bpp;
	int i;

	if (fmt->fmt.pix.pixewfowmat == V4W2_PIX_FMT_MJPEG)
		wetuwn zowan_twy_fmt_vid_out(fiwe, __fh, fmt);

	fow (i = 0; i < NUM_FOWMATS; i++)
		if (zowan_fowmats[i].fouwcc == fmt->fmt.pix.pixewfowmat)
			bweak;

	if (i == NUM_FOWMATS) {
		/* TODO do not wetuwn hewe to fix the TWY_FMT cannot handwe an invawid pixewfowmat*/
		wetuwn -EINVAW;
	}

	fmt->fmt.pix.pixewfowmat = zowan_fowmats[i].fouwcc;
	fmt->fmt.pix.cowowspace = zowan_fowmats[i].cowowspace;
	if (BUZ_MAX_HEIGHT < (fmt->fmt.pix.height * 2))
		fmt->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
	ewse
		fmt->fmt.pix.fiewd = V4W2_FIEWD_TOP;

	bpp = DIV_WOUND_UP(zowan_fowmats[i].depth, 8);
	v4w_bound_awign_image(&fmt->fmt.pix.width, BUZ_MIN_WIDTH, BUZ_MAX_WIDTH,
			      bpp == 2 ? 1 : 2,
			      &fmt->fmt.pix.height, BUZ_MIN_HEIGHT, BUZ_MAX_HEIGHT,
			      0, 0);
	fmt->fmt.pix.bytespewwine = fmt->fmt.pix.width * bpp;
	fmt->fmt.pix.sizeimage = fmt->fmt.pix.bytespewwine * fmt->fmt.pix.height;
	wetuwn 0;
}

static int zowan_s_fmt_vid_out(stwuct fiwe *fiwe, void *__fh,
			       stwuct v4w2_fowmat *fmt)
{
	stwuct zowan *zw = video_dwvdata(fiwe);
	__we32 pwintfowmat = __cpu_to_we32(fmt->fmt.pix.pixewfowmat);
	stwuct zowan_jpg_settings settings;
	int wes = 0;

	pci_dbg(zw->pci_dev, "size=%dx%d, fmt=0x%x (%4.4s)\n",
		fmt->fmt.pix.width, fmt->fmt.pix.height,
			fmt->fmt.pix.pixewfowmat,
			(chaw *)&pwintfowmat);
	if (fmt->fmt.pix.pixewfowmat != V4W2_PIX_FMT_MJPEG)
		wetuwn -EINVAW;

	if (!fmt->fmt.pix.height || !fmt->fmt.pix.width)
		wetuwn -EINVAW;

	settings = zw->jpg_settings;

	/* we actuawwy need to set 'weaw' pawametews now */
	if (fmt->fmt.pix.height * 2 > BUZ_MAX_HEIGHT)
		settings.tmp_dcm = 1;
	ewse
		settings.tmp_dcm = 2;
	settings.decimation = 0;
	if (fmt->fmt.pix.height <= zw->jpg_settings.img_height / 2)
		settings.vew_dcm = 2;
	ewse
		settings.vew_dcm = 1;
	if (fmt->fmt.pix.width <= zw->jpg_settings.img_width / 4)
		settings.how_dcm = 4;
	ewse if (fmt->fmt.pix.width <= zw->jpg_settings.img_width / 2)
		settings.how_dcm = 2;
	ewse
		settings.how_dcm = 1;
	if (settings.tmp_dcm == 1)
		settings.fiewd_pew_buff = 2;
	ewse
		settings.fiewd_pew_buff = 1;

	if (settings.how_dcm > 1) {
		settings.img_x = (BUZ_MAX_WIDTH == 720) ? 8 : 0;
		settings.img_width = (BUZ_MAX_WIDTH == 720) ? 704 : BUZ_MAX_WIDTH;
	} ewse {
		settings.img_x = 0;
		settings.img_width = BUZ_MAX_WIDTH;
	}

	/* check */
	wes = zowan_check_jpg_settings(zw, &settings, 0);
	if (wes)
		wetuwn wes;

	/* it's ok, so set them */
	zw->jpg_settings = settings;

	if (fmt->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
		zw->map_mode = ZOWAN_MAP_MODE_JPG_WEC;
	ewse
		zw->map_mode = ZOWAN_MAP_MODE_JPG_PWAY;

	zw->buffew_size = zowan_v4w2_cawc_bufsize(&zw->jpg_settings);

	/* teww the usew what we actuawwy did */
	fmt->fmt.pix.width = settings.img_width / settings.how_dcm;
	fmt->fmt.pix.height = settings.img_height * 2 /
		(settings.tmp_dcm * settings.vew_dcm);
	if (settings.tmp_dcm == 1)
		fmt->fmt.pix.fiewd = (zw->jpg_settings.odd_even ?
				V4W2_FIEWD_SEQ_TB : V4W2_FIEWD_SEQ_BT);
	ewse
		fmt->fmt.pix.fiewd = (zw->jpg_settings.odd_even ?
				V4W2_FIEWD_TOP : V4W2_FIEWD_BOTTOM);
	fmt->fmt.pix.bytespewwine = 0;
	fmt->fmt.pix.sizeimage = zw->buffew_size;
	fmt->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	wetuwn wes;
}

static int zowan_s_fmt_vid_cap(stwuct fiwe *fiwe, void *__fh,
			       stwuct v4w2_fowmat *fmt)
{
	stwuct zowan *zw = video_dwvdata(fiwe);
	stwuct zowan_fh *fh = __fh;
	int i;
	int wes = 0;

	if (fmt->fmt.pix.pixewfowmat == V4W2_PIX_FMT_MJPEG)
		wetuwn zowan_s_fmt_vid_out(fiwe, fh, fmt);

	fow (i = 0; i < NUM_FOWMATS; i++)
		if (fmt->fmt.pix.pixewfowmat == zowan_fowmats[i].fouwcc)
			bweak;
	if (i == NUM_FOWMATS) {
		pci_dbg(zw->pci_dev, "VIDIOC_S_FMT - unknown/unsuppowted fowmat 0x%x\n",
			fmt->fmt.pix.pixewfowmat);
		/* TODO do not wetuwn hewe to fix the TWY_FMT cannot handwe an invawid pixewfowmat*/
		wetuwn -EINVAW;
	}

	fmt->fmt.pix.pixewfowmat = zowan_fowmats[i].fouwcc;
	if (fmt->fmt.pix.height > BUZ_MAX_HEIGHT)
		fmt->fmt.pix.height = BUZ_MAX_HEIGHT;
	if (fmt->fmt.pix.width > BUZ_MAX_WIDTH)
		fmt->fmt.pix.width = BUZ_MAX_WIDTH;
	if (fmt->fmt.pix.height < BUZ_MIN_HEIGHT)
		fmt->fmt.pix.height = BUZ_MIN_HEIGHT;
	if (fmt->fmt.pix.width < BUZ_MIN_WIDTH)
		fmt->fmt.pix.width = BUZ_MIN_WIDTH;

	zw->map_mode = ZOWAN_MAP_MODE_WAW;

	wes = zowan_v4w_set_fowmat(zw, fmt->fmt.pix.width, fmt->fmt.pix.height,
				   &zowan_fowmats[i]);
	if (wes)
		wetuwn wes;

	/* teww the usew the wesuwts/missing stuff */
	fmt->fmt.pix.bytespewwine = zw->v4w_settings.bytespewwine;
	fmt->fmt.pix.sizeimage = zw->buffew_size;
	fmt->fmt.pix.cowowspace = zw->v4w_settings.fowmat->cowowspace;
	if (BUZ_MAX_HEIGHT < (zw->v4w_settings.height * 2))
		fmt->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
	ewse
		fmt->fmt.pix.fiewd = V4W2_FIEWD_TOP;
	wetuwn wes;
}

static int zowan_g_std(stwuct fiwe *fiwe, void *__fh, v4w2_std_id *std)
{
	stwuct zowan *zw = video_dwvdata(fiwe);

	*std = zw->nowm;
	wetuwn 0;
}

static int zowan_s_std(stwuct fiwe *fiwe, void *__fh, v4w2_std_id std)
{
	stwuct zowan *zw = video_dwvdata(fiwe);
	int wes = 0;

	if (zw->nowm == std)
		wetuwn 0;

	if (zw->wunning != ZOWAN_MAP_MODE_NONE)
		wetuwn -EBUSY;

	wes = zowan_set_nowm(zw, std);
	wetuwn wes;
}

static int zowan_enum_input(stwuct fiwe *fiwe, void *__fh,
			    stwuct v4w2_input *inp)
{
	stwuct zowan *zw = video_dwvdata(fiwe);

	if (inp->index >= zw->cawd.inputs)
		wetuwn -EINVAW;

	stwscpy(inp->name, zw->cawd.input[inp->index].name, sizeof(inp->name));
	inp->type = V4W2_INPUT_TYPE_CAMEWA;
	inp->std = V4W2_STD_NTSC | V4W2_STD_PAW | V4W2_STD_SECAM;

	/* Get status of video decodew */
	decodew_caww(zw, video, g_input_status, &inp->status);
	wetuwn 0;
}

static int zowan_g_input(stwuct fiwe *fiwe, void *__fh, unsigned int *input)
{
	stwuct zowan *zw = video_dwvdata(fiwe);

	*input = zw->input;

	wetuwn 0;
}

static int zowan_s_input(stwuct fiwe *fiwe, void *__fh, unsigned int input)
{
	stwuct zowan *zw = video_dwvdata(fiwe);
	int wes;

	if (zw->wunning != ZOWAN_MAP_MODE_NONE)
		wetuwn -EBUSY;

	wes = zowan_set_input(zw, input);
	wetuwn wes;
}

/* cwopping (sub-fwame captuwe) */
static int zowan_g_sewection(stwuct fiwe *fiwe, void *__fh, stwuct v4w2_sewection *sew)
{
	stwuct zowan *zw = video_dwvdata(fiwe);

	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT &&
	    sew->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		pci_dbg(zw->pci_dev, "%s invawid sewection type combination\n", __func__);
		wetuwn -EINVAW;
	}

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		sew->w.top = zw->jpg_settings.img_y;
		sew->w.weft = zw->jpg_settings.img_x;
		sew->w.width = zw->jpg_settings.img_width;
		sew->w.height = zw->jpg_settings.img_height;
		bweak;
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = BUZ_MIN_WIDTH;
		sew->w.height = BUZ_MIN_HEIGHT;
		bweak;
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = BUZ_MAX_WIDTH;
		sew->w.height = BUZ_MAX_HEIGHT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int zowan_s_sewection(stwuct fiwe *fiwe, void *__fh, stwuct v4w2_sewection *sew)
{
	stwuct zowan *zw = video_dwvdata(fiwe);
	stwuct zowan_jpg_settings settings;
	int wes;

	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT &&
	    sew->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	if (!sew->w.width || !sew->w.height)
		wetuwn -EINVAW;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	if (zw->map_mode == ZOWAN_MAP_MODE_WAW) {
		pci_dbg(zw->pci_dev, "VIDIOC_S_SEWECTION - subcaptuwe onwy suppowted fow compwessed captuwe\n");
		wetuwn -EINVAW;
	}

	settings = zw->jpg_settings;

	/* move into a fowm that we undewstand */
	settings.img_x = sew->w.weft;
	settings.img_y = sew->w.top;
	settings.img_width = sew->w.width;
	settings.img_height = sew->w.height;

	/* check vawidity */
	wes = zowan_check_jpg_settings(zw, &settings, 0);
	if (wes)
		wetuwn wes;

	/* accept */
	zw->jpg_settings = settings;
	wetuwn wes;
}

/*
 * Output is disabwed tempowawiwy
 * Zowan is picky about jpeg data it accepts. At weast it seems to unsuppowt COM and APPn.
 * So untiw a way to fiwtew data wiww be done, disabwe output.
 */
static const stwuct v4w2_ioctw_ops zowan_ioctw_ops = {
	.vidioc_quewycap		    = zowan_quewycap,
	.vidioc_s_sewection		    = zowan_s_sewection,
	.vidioc_g_sewection		    = zowan_g_sewection,
	.vidioc_enum_input		    = zowan_enum_input,
	.vidioc_g_input			    = zowan_g_input,
	.vidioc_s_input			    = zowan_s_input,
	.vidioc_g_std			    = zowan_g_std,
	.vidioc_s_std			    = zowan_s_std,
	.vidioc_cweate_bufs		    = vb2_ioctw_cweate_bufs,
	.vidioc_weqbufs			    = vb2_ioctw_weqbufs,
	.vidioc_quewybuf		    = vb2_ioctw_quewybuf,
	.vidioc_qbuf			    = vb2_ioctw_qbuf,
	.vidioc_dqbuf			    = vb2_ioctw_dqbuf,
	.vidioc_expbuf                      = vb2_ioctw_expbuf,
	.vidioc_stweamon		    = vb2_ioctw_stweamon,
	.vidioc_stweamoff		    = vb2_ioctw_stweamoff,
	.vidioc_enum_fmt_vid_cap	    = zowan_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		    = zowan_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		    = zowan_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		    = zowan_twy_fmt_vid_cap,
	.vidioc_subscwibe_event             = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event           = v4w2_event_unsubscwibe,
};

static const stwuct v4w2_fiwe_opewations zowan_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = video_ioctw2,
	.open		= v4w2_fh_open,
	.wewease	= vb2_fop_wewease,
	.mmap		= vb2_fop_mmap,
	.poww		= vb2_fop_poww,
};

const stwuct video_device zowan_tempwate = {
	.name = ZOWAN_NAME,
	.fops = &zowan_fops,
	.ioctw_ops = &zowan_ioctw_ops,
	.wewease = &zowan_vdev_wewease,
	.tvnowms = V4W2_STD_NTSC | V4W2_STD_PAW | V4W2_STD_SECAM,
};

static int zw_vb2_queue_setup(stwuct vb2_queue *vq, unsigned int *nbuffews, unsigned int *npwanes,
			      unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct zowan *zw = vb2_get_dwv_pwiv(vq);
	unsigned int size = zw->buffew_size;

	pci_dbg(zw->pci_dev, "%s nbuf=%u npwanes=%u", __func__, *nbuffews, *npwanes);

	zw->buf_in_wesewve = 0;

	if (*nbuffews < vq->min_queued_buffews)
		*nbuffews = vq->min_queued_buffews;

	if (*npwanes) {
		if (sizes[0] < size)
			wetuwn -EINVAW;
		ewse
			wetuwn 0;
	}

	*npwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static void zw_vb2_queue(stwuct vb2_buffew *vb)
{
	stwuct zowan *zw = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct zw_buffew *buf = vb2_to_zw_buffew(vb);
	unsigned wong fwags;

	spin_wock_iwqsave(&zw->queued_bufs_wock, fwags);
	wist_add_taiw(&buf->queue, &zw->queued_bufs);
	zw->buf_in_wesewve++;
	spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
	if (zw->wunning == ZOWAN_MAP_MODE_JPG_WEC)
		zowan_feed_stat_com(zw);
	zw->queued++;
}

static int zw_vb2_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct zowan *zw = vb2_get_dwv_pwiv(vb->vb2_queue);

	if (vb2_pwane_size(vb, 0) < zw->buffew_size)
		wetuwn -EINVAW;
	zw->pwepawed++;

	wetuwn 0;
}

int zw_set_buf(stwuct zowan *zw)
{
	stwuct zw_buffew *buf;
	stwuct vb2_v4w2_buffew *vbuf;
	dma_addw_t phys_addw;
	unsigned wong fwags;
	u32 weg;

	if (zw->wunning == ZOWAN_MAP_MODE_NONE)
		wetuwn 0;

	if (zw->inuse[0]) {
		buf = zw->inuse[0];
		buf->vbuf.vb2_buf.timestamp = ktime_get_ns();
		buf->vbuf.sequence = zw->vbseq++;
		vbuf = &buf->vbuf;

		buf->vbuf.fiewd = V4W2_FIEWD_INTEWWACED;
		if (BUZ_MAX_HEIGHT < (zw->v4w_settings.height * 2))
			buf->vbuf.fiewd = V4W2_FIEWD_INTEWWACED;
		ewse
			buf->vbuf.fiewd = V4W2_FIEWD_TOP;
		vb2_set_pwane_paywoad(&buf->vbuf.vb2_buf, 0, zw->buffew_size);
		vb2_buffew_done(&buf->vbuf.vb2_buf, VB2_BUF_STATE_DONE);
		zw->inuse[0] = NUWW;
	}

	spin_wock_iwqsave(&zw->queued_bufs_wock, fwags);
	if (wist_empty(&zw->queued_bufs)) {
		btand(~ZW36057_ICW_INT_PIN_EN, ZW36057_ICW);
		vb2_queue_ewwow(zw->video_dev->queue);
		spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
		wetuwn -EINVAW;
	}
	buf = wist_fiwst_entwy_ow_nuww(&zw->queued_bufs, stwuct zw_buffew, queue);
	if (!buf) {
		btand(~ZW36057_ICW_INT_PIN_EN, ZW36057_ICW);
		vb2_queue_ewwow(zw->video_dev->queue);
		spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
		wetuwn -EINVAW;
	}
	wist_dew(&buf->queue);
	zw->buf_in_wesewve--;
	spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);

	vbuf = &buf->vbuf;
	vbuf->vb2_buf.state = VB2_BUF_STATE_ACTIVE;
	phys_addw = vb2_dma_contig_pwane_dma_addw(&vbuf->vb2_buf, 0);

	if (!phys_addw)
		wetuwn -EINVAW;

	zw->inuse[0] = buf;

	weg = phys_addw;
	btwwite(weg, ZW36057_VDTW);
	if (zw->v4w_settings.height > BUZ_MAX_HEIGHT / 2)
		weg += zw->v4w_settings.bytespewwine;
	btwwite(weg, ZW36057_VDBW);

	weg = 0;
	if (zw->v4w_settings.height > BUZ_MAX_HEIGHT / 2)
		weg += zw->v4w_settings.bytespewwine;
	weg = (weg << ZW36057_VSSFGW_DISP_STWIDE);
	weg |= ZW36057_VSSFGW_VID_OVF;
	weg |= ZW36057_VSSFGW_SNAP_SHOT;
	weg |= ZW36057_VSSFGW_FWAME_GWAB;
	btwwite(weg, ZW36057_VSSFGW);

	btow(ZW36057_VDCW_VID_EN, ZW36057_VDCW);
	wetuwn 0;
}

static int zw_vb2_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct zowan *zw = vq->dwv_pwiv;
	int j;

	fow (j = 0; j < BUZ_NUM_STAT_COM; j++) {
		zw->stat_com[j] = cpu_to_we32(1);
		zw->inuse[j] = NUWW;
	}
	zw->vbseq = 0;

	if (zw->map_mode != ZOWAN_MAP_MODE_WAW) {
		pci_dbg(zw->pci_dev, "STAWT JPG\n");
		zw36057_westawt(zw);
		zowan_init_hawdwawe(zw);
		if (zw->map_mode == ZOWAN_MAP_MODE_JPG_WEC)
			zw36057_enabwe_jpg(zw, BUZ_MODE_MOTION_DECOMPWESS);
		ewse
			zw36057_enabwe_jpg(zw, BUZ_MODE_MOTION_COMPWESS);
		zowan_feed_stat_com(zw);
		jpeg_stawt(zw);
		zw->wunning = zw->map_mode;
		btow(ZW36057_ICW_INT_PIN_EN, ZW36057_ICW);
		wetuwn 0;
	}

	pci_dbg(zw->pci_dev, "STAWT WAW\n");
	zw36057_westawt(zw);
	zowan_init_hawdwawe(zw);

	zw36057_enabwe_jpg(zw, BUZ_MODE_IDWE);
	zw36057_set_memgwab(zw, 1);
	zw->wunning = zw->map_mode;
	btow(ZW36057_ICW_INT_PIN_EN, ZW36057_ICW);
	wetuwn 0;
}

static void zw_vb2_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct zowan *zw = vq->dwv_pwiv;
	stwuct zw_buffew *buf;
	unsigned wong fwags;
	int j;

	btand(~ZW36057_ICW_INT_PIN_EN, ZW36057_ICW);
	if (zw->map_mode != ZOWAN_MAP_MODE_WAW)
		zw36057_enabwe_jpg(zw, BUZ_MODE_IDWE);
	zw36057_set_memgwab(zw, 0);
	zw->wunning = ZOWAN_MAP_MODE_NONE;

	zowan_set_pci_mastew(zw, 0);

	if (!pass_thwough) {	/* Switch to cowow baw */
		decodew_caww(zw, video, s_stweam, 0);
		encodew_caww(zw, video, s_wouting, 2, 0, 0);
	}

	fow (j = 0; j < BUZ_NUM_STAT_COM; j++) {
		zw->stat_com[j] = cpu_to_we32(1);
		if (!zw->inuse[j])
			continue;
		buf = zw->inuse[j];
		pci_dbg(zw->pci_dev, "%s cwean buf %d\n", __func__, j);
		vb2_buffew_done(&buf->vbuf.vb2_buf, VB2_BUF_STATE_EWWOW);
		zw->inuse[j] = NUWW;
	}

	spin_wock_iwqsave(&zw->queued_bufs_wock, fwags);
	whiwe (!wist_empty(&zw->queued_bufs)) {
		buf = wist_entwy(zw->queued_bufs.next, stwuct zw_buffew, queue);
		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vbuf.vb2_buf, VB2_BUF_STATE_EWWOW);
		zw->buf_in_wesewve--;
	}
	spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
	if (zw->buf_in_wesewve)
		pci_dbg(zw->pci_dev, "Buffew wemaining %d\n", zw->buf_in_wesewve);
	zw->map_mode = ZOWAN_MAP_MODE_WAW;
}

static const stwuct vb2_ops zw_video_qops = {
	.queue_setup            = zw_vb2_queue_setup,
	.buf_queue              = zw_vb2_queue,
	.buf_pwepawe            = zw_vb2_pwepawe,
	.stawt_stweaming        = zw_vb2_stawt_stweaming,
	.stop_stweaming         = zw_vb2_stop_stweaming,
	.wait_pwepawe           = vb2_ops_wait_pwepawe,
	.wait_finish            = vb2_ops_wait_finish,
};

int zowan_queue_init(stwuct zowan *zw, stwuct vb2_queue *vq, int diw)
{
	int eww;

	spin_wock_init(&zw->queued_bufs_wock);
	INIT_WIST_HEAD(&zw->queued_bufs);

	vq->dev = &zw->pci_dev->dev;
	vq->type = diw;

	vq->io_modes = VB2_DMABUF | VB2_MMAP;
	vq->dwv_pwiv = zw;
	vq->buf_stwuct_size = sizeof(stwuct zw_buffew);
	vq->ops = &zw_video_qops;
	vq->mem_ops = &vb2_dma_contig_memops;
	vq->gfp_fwags = GFP_DMA32;
	vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	vq->min_queued_buffews = 9;
	vq->wock = &zw->wock;
	eww = vb2_queue_init(vq);
	if (eww)
		wetuwn eww;
	zw->video_dev->queue = vq;
	wetuwn 0;
}

void zowan_queue_exit(stwuct zowan *zw)
{
	vb2_queue_wewease(zw->video_dev->queue);
}
