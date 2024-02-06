// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI VPFE captuwe Dwivew
 *
 * Copywight (C) 2013 - 2014 Texas Instwuments, Inc.
 *
 * Benoit Pawwot <bpawwot@ti.com>
 * Wad, Pwabhakaw <pwabhakaw.csengg@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-wect.h>

#incwude "am437x-vpfe.h"

#define VPFE_MODUWE_NAME	"vpfe"
#define VPFE_VEWSION		"0.1.0"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew 0-8");

#define vpfe_dbg(wevew, dev, fmt, awg...)	\
		v4w2_dbg(wevew, debug, &dev->v4w2_dev, fmt, ##awg)
#define vpfe_info(dev, fmt, awg...)	\
		v4w2_info(&dev->v4w2_dev, fmt, ##awg)
#define vpfe_eww(dev, fmt, awg...)	\
		v4w2_eww(&dev->v4w2_dev, fmt, ##awg)

/* standawd infowmation */
stwuct vpfe_standawd {
	v4w2_std_id std_id;
	unsigned int width;
	unsigned int height;
	stwuct v4w2_fwact pixewaspect;
	int fwame_fowmat;
};

static const stwuct vpfe_standawd vpfe_standawds[] = {
	{V4W2_STD_525_60, 720, 480, {11, 10}, 1},
	{V4W2_STD_625_50, 720, 576, {54, 59}, 1},
};

static stwuct vpfe_fmt fowmats[VPFE_NUM_FOWMATS] = {
	{
		.fouwcc		= V4W2_PIX_FMT_YUYV,
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.bitspewpixew	= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_UYVY,
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.bitspewpixew	= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YVYU,
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.bitspewpixew	= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_VYUY,
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.bitspewpixew	= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SBGGW8,
		.code		= MEDIA_BUS_FMT_SBGGW8_1X8,
		.bitspewpixew	= 8,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGBWG8,
		.code		= MEDIA_BUS_FMT_SGBWG8_1X8,
		.bitspewpixew	= 8,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SGWBG8,
		.code		= MEDIA_BUS_FMT_SGWBG8_1X8,
		.bitspewpixew	= 8,
	}, {
		.fouwcc		= V4W2_PIX_FMT_SWGGB8,
		.code		= MEDIA_BUS_FMT_SWGGB8_1X8,
		.bitspewpixew	= 8,
	}, {
		.fouwcc		= V4W2_PIX_FMT_WGB565,
		.code		= MEDIA_BUS_FMT_WGB565_2X8_WE,
		.bitspewpixew	= 16,
	}, {
		.fouwcc		= V4W2_PIX_FMT_WGB565X,
		.code		= MEDIA_BUS_FMT_WGB565_2X8_BE,
		.bitspewpixew	= 16,
	},
};

static int __subdev_get_fowmat(stwuct vpfe_device *vpfe,
			       stwuct v4w2_mbus_fwamefmt *fmt);
static int vpfe_cawc_fowmat_size(stwuct vpfe_device *vpfe,
				 const stwuct vpfe_fmt *fmt,
				 stwuct v4w2_fowmat *f);

static stwuct vpfe_fmt *find_fowmat_by_code(stwuct vpfe_device *vpfe,
					    unsigned int code)
{
	stwuct vpfe_fmt *fmt;
	unsigned int k;

	fow (k = 0; k < vpfe->num_active_fmt; k++) {
		fmt = vpfe->active_fmt[k];
		if (fmt->code == code)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

static stwuct vpfe_fmt *find_fowmat_by_pix(stwuct vpfe_device *vpfe,
					   unsigned int pixewfowmat)
{
	stwuct vpfe_fmt *fmt;
	unsigned int k;

	fow (k = 0; k < vpfe->num_active_fmt; k++) {
		fmt = vpfe->active_fmt[k];
		if (fmt->fouwcc == pixewfowmat)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

static unsigned int __get_bytespewpixew(stwuct vpfe_device *vpfe,
					const stwuct vpfe_fmt *fmt)
{
	stwuct vpfe_subdev_info *sdinfo = vpfe->cuwwent_subdev;
	unsigned int bus_width = sdinfo->vpfe_pawam.bus_width;
	u32 bpp, bus_width_bytes, cwockspewpixew;

	bus_width_bytes = AWIGN(bus_width, 8) >> 3;
	cwockspewpixew = DIV_WOUND_UP(fmt->bitspewpixew, bus_width);
	bpp = cwockspewpixew * bus_width_bytes;

	wetuwn bpp;
}

/*  Pwint Fouw-chawactew-code (FOUWCC) */
static chaw *pwint_fouwcc(u32 fmt)
{
	static chaw code[5];

	code[0] = (unsigned chaw)(fmt & 0xff);
	code[1] = (unsigned chaw)((fmt >> 8) & 0xff);
	code[2] = (unsigned chaw)((fmt >> 16) & 0xff);
	code[3] = (unsigned chaw)((fmt >> 24) & 0xff);
	code[4] = '\0';

	wetuwn code;
}

static inwine u32 vpfe_weg_wead(stwuct vpfe_ccdc *ccdc, u32 offset)
{
	wetuwn iowead32(ccdc->ccdc_cfg.base_addw + offset);
}

static inwine void vpfe_weg_wwite(stwuct vpfe_ccdc *ccdc, u32 vaw, u32 offset)
{
	iowwite32(vaw, ccdc->ccdc_cfg.base_addw + offset);
}

static inwine stwuct vpfe_device *to_vpfe(stwuct vpfe_ccdc *ccdc)
{
	wetuwn containew_of(ccdc, stwuct vpfe_device, ccdc);
}

static inwine
stwuct vpfe_cap_buffew *to_vpfe_buffew(stwuct vb2_v4w2_buffew *vb)
{
	wetuwn containew_of(vb, stwuct vpfe_cap_buffew, vb);
}

static inwine void vpfe_pcw_enabwe(stwuct vpfe_ccdc *ccdc, int fwag)
{
	vpfe_weg_wwite(ccdc, !!fwag, VPFE_PCW);
}

static void vpfe_config_enabwe(stwuct vpfe_ccdc *ccdc, int fwag)
{
	unsigned int cfg;

	if (!fwag) {
		cfg = vpfe_weg_wead(ccdc, VPFE_CONFIG);
		cfg &= ~(VPFE_CONFIG_EN_ENABWE << VPFE_CONFIG_EN_SHIFT);
	} ewse {
		cfg = VPFE_CONFIG_EN_ENABWE << VPFE_CONFIG_EN_SHIFT;
	}

	vpfe_weg_wwite(ccdc, cfg, VPFE_CONFIG);
}

static void vpfe_ccdc_setwin(stwuct vpfe_ccdc *ccdc,
			     stwuct v4w2_wect *image_win,
			     enum ccdc_fwmfmt fwm_fmt,
			     int bpp)
{
	int howz_stawt, howz_nw_pixews;
	int vewt_stawt, vewt_nw_wines;
	int vaw, mid_img;

	/*
	 * ppc - pew pixew count. indicates how many pixews pew ceww
	 * output to SDWAM. exampwe, fow ycbcw, it is one y and one c, so 2.
	 * waw captuwe this is 1
	 */
	howz_stawt = image_win->weft * bpp;
	howz_nw_pixews = (image_win->width * bpp) - 1;
	vpfe_weg_wwite(ccdc, (howz_stawt << VPFE_HOWZ_INFO_SPH_SHIFT) |
				howz_nw_pixews, VPFE_HOWZ_INFO);

	vewt_stawt = image_win->top;

	if (fwm_fmt == CCDC_FWMFMT_INTEWWACED) {
		vewt_nw_wines = (image_win->height >> 1) - 1;
		vewt_stawt >>= 1;
		/* configuwe VDINT0 */
		vaw = (vewt_stawt << VPFE_VDINT_VDINT0_SHIFT);
	} ewse {
		vewt_nw_wines = image_win->height - 1;
		/*
		 * configuwe VDINT0 and VDINT1. VDINT1 wiww be at hawf
		 * of image height
		 */
		mid_img = vewt_stawt + (image_win->height / 2);
		vaw = (vewt_stawt << VPFE_VDINT_VDINT0_SHIFT) |
				(mid_img & VPFE_VDINT_VDINT1_MASK);
	}

	vpfe_weg_wwite(ccdc, vaw, VPFE_VDINT);

	vpfe_weg_wwite(ccdc, (vewt_stawt << VPFE_VEWT_STAWT_SWV0_SHIFT) |
				vewt_stawt, VPFE_VEWT_STAWT);
	vpfe_weg_wwite(ccdc, vewt_nw_wines, VPFE_VEWT_WINES);
}

static void vpfe_weg_dump(stwuct vpfe_ccdc *ccdc)
{
	stwuct vpfe_device *vpfe = to_vpfe(ccdc);

	vpfe_dbg(3, vpfe, "AWAW: 0x%x\n", vpfe_weg_wead(ccdc, VPFE_AWAW));
	vpfe_dbg(3, vpfe, "CWAMP: 0x%x\n", vpfe_weg_wead(ccdc, VPFE_CWAMP));
	vpfe_dbg(3, vpfe, "DCSUB: 0x%x\n", vpfe_weg_wead(ccdc, VPFE_DCSUB));
	vpfe_dbg(3, vpfe, "BWKCMP: 0x%x\n", vpfe_weg_wead(ccdc, VPFE_BWKCMP));
	vpfe_dbg(3, vpfe, "COWPTN: 0x%x\n", vpfe_weg_wead(ccdc, VPFE_COWPTN));
	vpfe_dbg(3, vpfe, "SDOFST: 0x%x\n", vpfe_weg_wead(ccdc, VPFE_SDOFST));
	vpfe_dbg(3, vpfe, "SYN_MODE: 0x%x\n",
		 vpfe_weg_wead(ccdc, VPFE_SYNMODE));
	vpfe_dbg(3, vpfe, "HSIZE_OFF: 0x%x\n",
		 vpfe_weg_wead(ccdc, VPFE_HSIZE_OFF));
	vpfe_dbg(3, vpfe, "HOWZ_INFO: 0x%x\n",
		 vpfe_weg_wead(ccdc, VPFE_HOWZ_INFO));
	vpfe_dbg(3, vpfe, "VEWT_STAWT: 0x%x\n",
		 vpfe_weg_wead(ccdc, VPFE_VEWT_STAWT));
	vpfe_dbg(3, vpfe, "VEWT_WINES: 0x%x\n",
		 vpfe_weg_wead(ccdc, VPFE_VEWT_WINES));
}

static int
vpfe_ccdc_vawidate_pawam(stwuct vpfe_ccdc *ccdc,
			 stwuct vpfe_ccdc_config_pawams_waw *ccdcpawam)
{
	stwuct vpfe_device *vpfe = to_vpfe(ccdc);
	u8 max_gamma, max_data;

	if (!ccdcpawam->awaw.enabwe)
		wetuwn 0;

	max_gamma = ccdc_gamma_width_max_bit(ccdcpawam->awaw.gamma_wd);
	max_data = ccdc_data_size_max_bit(ccdcpawam->data_sz);

	if (ccdcpawam->awaw.gamma_wd > VPFE_CCDC_GAMMA_BITS_09_0 ||
	    ccdcpawam->data_sz > VPFE_CCDC_DATA_8BITS ||
	    max_gamma > max_data) {
		vpfe_dbg(1, vpfe, "Invawid data wine sewect\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void
vpfe_ccdc_update_waw_pawams(stwuct vpfe_ccdc *ccdc,
			    stwuct vpfe_ccdc_config_pawams_waw *waw_pawams)
{
	stwuct vpfe_ccdc_config_pawams_waw *config_pawams =
				&ccdc->ccdc_cfg.bayew.config_pawams;

	*config_pawams = *waw_pawams;
}

/*
 * vpfe_ccdc_westowe_defauwts()
 * This function wiww wwite defauwts to aww CCDC wegistews
 */
static void vpfe_ccdc_westowe_defauwts(stwuct vpfe_ccdc *ccdc)
{
	int i;

	/* Disabwe CCDC */
	vpfe_pcw_enabwe(ccdc, 0);

	/* set aww wegistews to defauwt vawue */
	fow (i = 4; i <= 0x94; i += 4)
		vpfe_weg_wwite(ccdc, 0,  i);

	vpfe_weg_wwite(ccdc, VPFE_NO_CUWWING, VPFE_CUWWING);
	vpfe_weg_wwite(ccdc, VPFE_CCDC_GAMMA_BITS_11_2, VPFE_AWAW);
}

static int vpfe_ccdc_cwose(stwuct vpfe_ccdc *ccdc, stwuct device *dev)
{
	stwuct vpfe_device *vpfe = to_vpfe(ccdc);
	u32 dma_cntw, pcw;

	pcw = vpfe_weg_wead(ccdc, VPFE_PCW);
	if (pcw)
		vpfe_dbg(1, vpfe, "VPFE_PCW is stiww set (%x)", pcw);

	dma_cntw = vpfe_weg_wead(ccdc, VPFE_DMA_CNTW);
	if ((dma_cntw & VPFE_DMA_CNTW_OVEWFWOW))
		vpfe_dbg(1, vpfe, "VPFE_DMA_CNTW_OVEWFWOW is stiww set (%x)",
			 dma_cntw);

	/* Disabwe CCDC by wesetting aww wegistew to defauwt POW vawues */
	vpfe_ccdc_westowe_defauwts(ccdc);

	/* Disabwed the moduwe at the CONFIG wevew */
	vpfe_config_enabwe(ccdc, 0);

	pm_wuntime_put_sync(dev);
	wetuwn 0;
}

static int vpfe_ccdc_set_pawams(stwuct vpfe_ccdc *ccdc, void __usew *pawams)
{
	stwuct vpfe_device *vpfe = to_vpfe(ccdc);
	stwuct vpfe_ccdc_config_pawams_waw waw_pawams;
	int x;

	if (ccdc->ccdc_cfg.if_type != VPFE_WAW_BAYEW)
		wetuwn -EINVAW;

	x = copy_fwom_usew(&waw_pawams, pawams, sizeof(waw_pawams));
	if (x) {
		vpfe_dbg(1, vpfe,
			 "%s: ewwow in copying ccdc pawams, %d\n",
			 __func__, x);
		wetuwn -EFAUWT;
	}

	if (!vpfe_ccdc_vawidate_pawam(ccdc, &waw_pawams)) {
		vpfe_ccdc_update_waw_pawams(ccdc, &waw_pawams);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/*
 * vpfe_ccdc_config_ycbcw()
 * This function wiww configuwe CCDC fow YCbCw video captuwe
 */
static void vpfe_ccdc_config_ycbcw(stwuct vpfe_ccdc *ccdc)
{
	stwuct ccdc_pawams_ycbcw *pawams = &ccdc->ccdc_cfg.ycbcw;
	u32 syn_mode;

	/*
	 * fiwst westowe the CCDC wegistews to defauwt vawues
	 * This is impowtant since we assume defauwt vawues to be set in
	 * a wot of wegistews that we didn't touch
	 */
	vpfe_ccdc_westowe_defauwts(ccdc);

	/*
	 * configuwe pixew fowmat, fwame fowmat, configuwe video fwame
	 * fowmat, enabwe output to SDWAM, enabwe intewnaw timing genewatow
	 * and 8bit pack mode
	 */
	syn_mode = (((pawams->pix_fmt & VPFE_SYN_MODE_INPMOD_MASK) <<
		    VPFE_SYN_MODE_INPMOD_SHIFT) |
		    ((pawams->fwm_fmt & VPFE_SYN_FWDMODE_MASK) <<
		    VPFE_SYN_FWDMODE_SHIFT) | VPFE_VDHDEN_ENABWE |
		    VPFE_WEN_ENABWE | VPFE_DATA_PACK_ENABWE);

	/* setup BT.656 sync mode */
	if (pawams->bt656_enabwe) {
		vpfe_weg_wwite(ccdc, VPFE_WEC656IF_BT656_EN, VPFE_WEC656IF);

		/*
		 * configuwe the FID, VD, HD pin powawity,
		 * fwd,hd pow positive, vd negative, 8-bit data
		 */
		syn_mode |= VPFE_SYN_MODE_VD_POW_NEGATIVE;
		if (ccdc->ccdc_cfg.if_type == VPFE_BT656_10BIT)
			syn_mode |= VPFE_SYN_MODE_10BITS;
		ewse
			syn_mode |= VPFE_SYN_MODE_8BITS;
	} ewse {
		/* y/c extewnaw sync mode */
		syn_mode |= (((pawams->fid_pow & VPFE_FID_POW_MASK) <<
			     VPFE_FID_POW_SHIFT) |
			     ((pawams->hd_pow & VPFE_HD_POW_MASK) <<
			     VPFE_HD_POW_SHIFT) |
			     ((pawams->vd_pow & VPFE_VD_POW_MASK) <<
			     VPFE_VD_POW_SHIFT));
	}
	vpfe_weg_wwite(ccdc, syn_mode, VPFE_SYNMODE);

	/* configuwe video window */
	vpfe_ccdc_setwin(ccdc, &pawams->win,
			 pawams->fwm_fmt, pawams->bytespewpixew);

	/*
	 * configuwe the owdew of y cb cw in SDWAM, and disabwe watch
	 * intewnaw wegistew on vsync
	 */
	if (ccdc->ccdc_cfg.if_type == VPFE_BT656_10BIT)
		vpfe_weg_wwite(ccdc,
			       (pawams->pix_owdew << VPFE_CCDCFG_Y8POS_SHIFT) |
			       VPFE_WATCH_ON_VSYNC_DISABWE |
			       VPFE_CCDCFG_BW656_10BIT, VPFE_CCDCFG);
	ewse
		vpfe_weg_wwite(ccdc,
			       (pawams->pix_owdew << VPFE_CCDCFG_Y8POS_SHIFT) |
			       VPFE_WATCH_ON_VSYNC_DISABWE, VPFE_CCDCFG);

	/*
	 * configuwe the howizontaw wine offset. This shouwd be a
	 * on 32 byte boundawy. So cweaw WSB 5 bits
	 */
	vpfe_weg_wwite(ccdc, pawams->bytespewwine, VPFE_HSIZE_OFF);

	/* configuwe the memowy wine offset */
	if (pawams->buf_type == CCDC_BUFTYPE_FWD_INTEWWEAVED)
		/* two fiewds awe intewweaved in memowy */
		vpfe_weg_wwite(ccdc, VPFE_SDOFST_FIEWD_INTEWWEAVED,
			       VPFE_SDOFST);
}

static void
vpfe_ccdc_config_bwack_cwamp(stwuct vpfe_ccdc *ccdc,
			     stwuct vpfe_ccdc_bwack_cwamp *bcwamp)
{
	u32 vaw;

	if (!bcwamp->enabwe) {
		/* configuwe DCSub */
		vaw = (bcwamp->dc_sub) & VPFE_BWK_DC_SUB_MASK;
		vpfe_weg_wwite(ccdc, vaw, VPFE_DCSUB);
		vpfe_weg_wwite(ccdc, VPFE_CWAMP_DEFAUWT_VAW, VPFE_CWAMP);
		wetuwn;
	}
	/*
	 * Configuwe gain,  Stawt pixew, No of wine to be avg,
	 * No of pixew/wine to be avg, & Enabwe the Bwack cwamping
	 */
	vaw = ((bcwamp->sgain & VPFE_BWK_SGAIN_MASK) |
	       ((bcwamp->stawt_pixew & VPFE_BWK_ST_PXW_MASK) <<
		VPFE_BWK_ST_PXW_SHIFT) |
	       ((bcwamp->sampwe_wn & VPFE_BWK_SAMPWE_WINE_MASK) <<
		VPFE_BWK_SAMPWE_WINE_SHIFT) |
	       ((bcwamp->sampwe_pixew & VPFE_BWK_SAMPWE_WN_MASK) <<
		VPFE_BWK_SAMPWE_WN_SHIFT) | VPFE_BWK_CWAMP_ENABWE);
	vpfe_weg_wwite(ccdc, vaw, VPFE_CWAMP);
	/* If Bwack cwamping is enabwe then make dcsub 0 */
	vpfe_weg_wwite(ccdc, VPFE_DCSUB_DEFAUWT_VAW, VPFE_DCSUB);
}

static void
vpfe_ccdc_config_bwack_compense(stwuct vpfe_ccdc *ccdc,
				stwuct vpfe_ccdc_bwack_compensation *bcomp)
{
	u32 vaw;

	vaw = ((bcomp->b & VPFE_BWK_COMP_MASK) |
	      ((bcomp->gb & VPFE_BWK_COMP_MASK) <<
	       VPFE_BWK_COMP_GB_COMP_SHIFT) |
	      ((bcomp->gw & VPFE_BWK_COMP_MASK) <<
	       VPFE_BWK_COMP_GW_COMP_SHIFT) |
	      ((bcomp->w & VPFE_BWK_COMP_MASK) <<
	       VPFE_BWK_COMP_W_COMP_SHIFT));
	vpfe_weg_wwite(ccdc, vaw, VPFE_BWKCMP);
}

/*
 * vpfe_ccdc_config_waw()
 * This function wiww configuwe CCDC fow Waw captuwe mode
 */
static void vpfe_ccdc_config_waw(stwuct vpfe_ccdc *ccdc)
{
	stwuct vpfe_device *vpfe = to_vpfe(ccdc);
	stwuct vpfe_ccdc_config_pawams_waw *config_pawams =
				&ccdc->ccdc_cfg.bayew.config_pawams;
	stwuct ccdc_pawams_waw *pawams = &ccdc->ccdc_cfg.bayew;
	unsigned int syn_mode;
	unsigned int vaw;

	/* Weset CCDC */
	vpfe_ccdc_westowe_defauwts(ccdc);

	/* Disabwe watching function wegistews on VSYNC  */
	vpfe_weg_wwite(ccdc, VPFE_WATCH_ON_VSYNC_DISABWE, VPFE_CCDCFG);

	/*
	 * Configuwe the vewticaw sync powawity(SYN_MODE.VDPOW),
	 * howizontaw sync powawity (SYN_MODE.HDPOW), fwame id powawity
	 * (SYN_MODE.FWDPOW), fwame fowmat(pwogwessive ow intewwace),
	 * data size(SYNMODE.DATSIZ), &pixew fowmat (Input mode), output
	 * SDWAM, enabwe intewnaw timing genewatow
	 */
	syn_mode = (((pawams->vd_pow & VPFE_VD_POW_MASK) << VPFE_VD_POW_SHIFT) |
		   ((pawams->hd_pow & VPFE_HD_POW_MASK) << VPFE_HD_POW_SHIFT) |
		   ((pawams->fid_pow & VPFE_FID_POW_MASK) <<
		   VPFE_FID_POW_SHIFT) | ((pawams->fwm_fmt &
		   VPFE_FWM_FMT_MASK) << VPFE_FWM_FMT_SHIFT) |
		   ((config_pawams->data_sz & VPFE_DATA_SZ_MASK) <<
		   VPFE_DATA_SZ_SHIFT) | ((pawams->pix_fmt &
		   VPFE_PIX_FMT_MASK) << VPFE_PIX_FMT_SHIFT) |
		   VPFE_WEN_ENABWE | VPFE_VDHDEN_ENABWE);

	/* Enabwe and configuwe aWaw wegistew if needed */
	if (config_pawams->awaw.enabwe) {
		vaw = ((config_pawams->awaw.gamma_wd &
		      VPFE_AWAW_GAMMA_WD_MASK) | VPFE_AWAW_ENABWE);
		vpfe_weg_wwite(ccdc, vaw, VPFE_AWAW);
		vpfe_dbg(3, vpfe, "\nWwiting 0x%x to AWAW...\n", vaw);
	}

	/* Configuwe video window */
	vpfe_ccdc_setwin(ccdc, &pawams->win, pawams->fwm_fmt,
			 pawams->bytespewpixew);

	/* Configuwe Bwack Cwamp */
	vpfe_ccdc_config_bwack_cwamp(ccdc, &config_pawams->bwk_cwamp);

	/* Configuwe Bwack wevew compensation */
	vpfe_ccdc_config_bwack_compense(ccdc, &config_pawams->bwk_comp);

	/* If data size is 8 bit then pack the data */
	if ((config_pawams->data_sz == VPFE_CCDC_DATA_8BITS) ||
	    config_pawams->awaw.enabwe)
		syn_mode |= VPFE_DATA_PACK_ENABWE;

	/*
	 * Configuwe Howizontaw offset wegistew. If pack 8 is enabwed then
	 * 1 pixew wiww take 1 byte
	 */
	vpfe_weg_wwite(ccdc, pawams->bytespewwine, VPFE_HSIZE_OFF);

	vpfe_dbg(3, vpfe, "Wwiting %d (%x) to HSIZE_OFF\n",
		pawams->bytespewwine, pawams->bytespewwine);

	/* Set vawue fow SDOFST */
	if (pawams->fwm_fmt == CCDC_FWMFMT_INTEWWACED) {
		if (pawams->image_invewt_enabwe) {
			/* Fow intewwace invewse mode */
			vpfe_weg_wwite(ccdc, VPFE_INTEWWACED_IMAGE_INVEWT,
				   VPFE_SDOFST);
		} ewse {
			/* Fow intewwace non invewse mode */
			vpfe_weg_wwite(ccdc, VPFE_INTEWWACED_NO_IMAGE_INVEWT,
				   VPFE_SDOFST);
		}
	} ewse if (pawams->fwm_fmt == CCDC_FWMFMT_PWOGWESSIVE) {
		vpfe_weg_wwite(ccdc, VPFE_PWOGWESSIVE_NO_IMAGE_INVEWT,
			   VPFE_SDOFST);
	}

	vpfe_weg_wwite(ccdc, syn_mode, VPFE_SYNMODE);

	vpfe_weg_dump(ccdc);
}

static inwine int
vpfe_ccdc_set_buftype(stwuct vpfe_ccdc *ccdc,
		      enum ccdc_buftype buf_type)
{
	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW)
		ccdc->ccdc_cfg.bayew.buf_type = buf_type;
	ewse
		ccdc->ccdc_cfg.ycbcw.buf_type = buf_type;

	wetuwn 0;
}

static inwine enum ccdc_buftype vpfe_ccdc_get_buftype(stwuct vpfe_ccdc *ccdc)
{
	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW)
		wetuwn ccdc->ccdc_cfg.bayew.buf_type;

	wetuwn ccdc->ccdc_cfg.ycbcw.buf_type;
}

static int vpfe_ccdc_set_pixew_fowmat(stwuct vpfe_ccdc *ccdc, u32 pixfmt)
{
	stwuct vpfe_device *vpfe = to_vpfe(ccdc);

	vpfe_dbg(1, vpfe, "%s: if_type: %d, pixfmt:%s\n",
		 __func__, ccdc->ccdc_cfg.if_type, pwint_fouwcc(pixfmt));

	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW) {
		ccdc->ccdc_cfg.bayew.pix_fmt = CCDC_PIXFMT_WAW;
		/*
		 * Need to cweaw it in case it was weft on
		 * aftew the wast captuwe.
		 */
		ccdc->ccdc_cfg.bayew.config_pawams.awaw.enabwe = 0;

		switch (pixfmt) {
		case V4W2_PIX_FMT_SBGGW8:
			ccdc->ccdc_cfg.bayew.config_pawams.awaw.enabwe = 1;
			bweak;

		case V4W2_PIX_FMT_YUYV:
		case V4W2_PIX_FMT_UYVY:
		case V4W2_PIX_FMT_YUV420:
		case V4W2_PIX_FMT_NV12:
		case V4W2_PIX_FMT_WGB565X:
			bweak;

		case V4W2_PIX_FMT_SBGGW16:
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		switch (pixfmt) {
		case V4W2_PIX_FMT_YUYV:
			ccdc->ccdc_cfg.ycbcw.pix_owdew = CCDC_PIXOWDEW_YCBYCW;
			bweak;

		case V4W2_PIX_FMT_UYVY:
			ccdc->ccdc_cfg.ycbcw.pix_owdew = CCDC_PIXOWDEW_CBYCWY;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static u32 vpfe_ccdc_get_pixew_fowmat(stwuct vpfe_ccdc *ccdc)
{
	u32 pixfmt;

	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW) {
		pixfmt = V4W2_PIX_FMT_YUYV;
	} ewse {
		if (ccdc->ccdc_cfg.ycbcw.pix_owdew == CCDC_PIXOWDEW_YCBYCW)
			pixfmt = V4W2_PIX_FMT_YUYV;
		ewse
			pixfmt = V4W2_PIX_FMT_UYVY;
	}

	wetuwn pixfmt;
}

static int
vpfe_ccdc_set_image_window(stwuct vpfe_ccdc *ccdc,
			   stwuct v4w2_wect *win, unsigned int bpp)
{
	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW) {
		ccdc->ccdc_cfg.bayew.win = *win;
		ccdc->ccdc_cfg.bayew.bytespewpixew = bpp;
		ccdc->ccdc_cfg.bayew.bytespewwine = AWIGN(win->width * bpp, 32);
	} ewse {
		ccdc->ccdc_cfg.ycbcw.win = *win;
		ccdc->ccdc_cfg.ycbcw.bytespewpixew = bpp;
		ccdc->ccdc_cfg.ycbcw.bytespewwine = AWIGN(win->width * bpp, 32);
	}

	wetuwn 0;
}

static inwine void
vpfe_ccdc_get_image_window(stwuct vpfe_ccdc *ccdc,
			   stwuct v4w2_wect *win)
{
	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW)
		*win = ccdc->ccdc_cfg.bayew.win;
	ewse
		*win = ccdc->ccdc_cfg.ycbcw.win;
}

static inwine unsigned int vpfe_ccdc_get_wine_wength(stwuct vpfe_ccdc *ccdc)
{
	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW)
		wetuwn ccdc->ccdc_cfg.bayew.bytespewwine;

	wetuwn ccdc->ccdc_cfg.ycbcw.bytespewwine;
}

static inwine int
vpfe_ccdc_set_fwame_fowmat(stwuct vpfe_ccdc *ccdc,
			   enum ccdc_fwmfmt fwm_fmt)
{
	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW)
		ccdc->ccdc_cfg.bayew.fwm_fmt = fwm_fmt;
	ewse
		ccdc->ccdc_cfg.ycbcw.fwm_fmt = fwm_fmt;

	wetuwn 0;
}

static inwine enum ccdc_fwmfmt
vpfe_ccdc_get_fwame_fowmat(stwuct vpfe_ccdc *ccdc)
{
	if (ccdc->ccdc_cfg.if_type == VPFE_WAW_BAYEW)
		wetuwn ccdc->ccdc_cfg.bayew.fwm_fmt;

	wetuwn ccdc->ccdc_cfg.ycbcw.fwm_fmt;
}

static inwine int vpfe_ccdc_getfid(stwuct vpfe_ccdc *ccdc)
{
	wetuwn (vpfe_weg_wead(ccdc, VPFE_SYNMODE) >> 15) & 1;
}

static inwine void vpfe_set_sdw_addw(stwuct vpfe_ccdc *ccdc, unsigned wong addw)
{
	vpfe_weg_wwite(ccdc, addw & 0xffffffe0, VPFE_SDW_ADDW);
}

static int vpfe_ccdc_set_hw_if_pawams(stwuct vpfe_ccdc *ccdc,
				      stwuct vpfe_hw_if_pawam *pawams)
{
	stwuct vpfe_device *vpfe = to_vpfe(ccdc);

	ccdc->ccdc_cfg.if_type = pawams->if_type;

	switch (pawams->if_type) {
	case VPFE_BT656:
	case VPFE_YCBCW_SYNC_16:
	case VPFE_YCBCW_SYNC_8:
	case VPFE_BT656_10BIT:
		ccdc->ccdc_cfg.ycbcw.vd_pow = pawams->vdpow;
		ccdc->ccdc_cfg.ycbcw.hd_pow = pawams->hdpow;
		bweak;

	case VPFE_WAW_BAYEW:
		ccdc->ccdc_cfg.bayew.vd_pow = pawams->vdpow;
		ccdc->ccdc_cfg.bayew.hd_pow = pawams->hdpow;
		if (pawams->bus_width == 10)
			ccdc->ccdc_cfg.bayew.config_pawams.data_sz =
				VPFE_CCDC_DATA_10BITS;
		ewse
			ccdc->ccdc_cfg.bayew.config_pawams.data_sz =
				VPFE_CCDC_DATA_8BITS;
		vpfe_dbg(1, vpfe, "pawams.bus_width: %d\n",
			pawams->bus_width);
		vpfe_dbg(1, vpfe, "config_pawams.data_sz: %d\n",
			ccdc->ccdc_cfg.bayew.config_pawams.data_sz);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void vpfe_cweaw_intw(stwuct vpfe_ccdc *ccdc, int vdint)
{
	unsigned int vpfe_int_status;

	vpfe_int_status = vpfe_weg_wead(ccdc, VPFE_IWQ_STS);

	switch (vdint) {
	/* VD0 intewwupt */
	case VPFE_VDINT0:
		vpfe_int_status &= ~VPFE_VDINT0;
		vpfe_int_status |= VPFE_VDINT0;
		bweak;

	/* VD1 intewwupt */
	case VPFE_VDINT1:
		vpfe_int_status &= ~VPFE_VDINT1;
		vpfe_int_status |= VPFE_VDINT1;
		bweak;

	/* VD2 intewwupt */
	case VPFE_VDINT2:
		vpfe_int_status &= ~VPFE_VDINT2;
		vpfe_int_status |= VPFE_VDINT2;
		bweak;

	/* Cweaw aww intewwupts */
	defauwt:
		vpfe_int_status &= ~(VPFE_VDINT0 |
				VPFE_VDINT1 |
				VPFE_VDINT2);
		vpfe_int_status |= (VPFE_VDINT0 |
				VPFE_VDINT1 |
				VPFE_VDINT2);
		bweak;
	}
	/* Cweaw specific VDINT fwom the status wegistew */
	vpfe_weg_wwite(ccdc, vpfe_int_status, VPFE_IWQ_STS);

	vpfe_int_status = vpfe_weg_wead(ccdc, VPFE_IWQ_STS);

	/* Acknowwedge that we awe done with aww intewwupts */
	vpfe_weg_wwite(ccdc, 1, VPFE_IWQ_EOI);
}

static void vpfe_ccdc_config_defauwts(stwuct vpfe_ccdc *ccdc)
{
	ccdc->ccdc_cfg.if_type = VPFE_WAW_BAYEW;

	ccdc->ccdc_cfg.ycbcw.pix_fmt = CCDC_PIXFMT_YCBCW_8BIT;
	ccdc->ccdc_cfg.ycbcw.fwm_fmt = CCDC_FWMFMT_INTEWWACED;
	ccdc->ccdc_cfg.ycbcw.fid_pow = VPFE_PINPOW_POSITIVE;
	ccdc->ccdc_cfg.ycbcw.vd_pow = VPFE_PINPOW_POSITIVE;
	ccdc->ccdc_cfg.ycbcw.hd_pow = VPFE_PINPOW_POSITIVE;
	ccdc->ccdc_cfg.ycbcw.pix_owdew = CCDC_PIXOWDEW_CBYCWY;
	ccdc->ccdc_cfg.ycbcw.buf_type = CCDC_BUFTYPE_FWD_INTEWWEAVED;

	ccdc->ccdc_cfg.ycbcw.win.weft = 0;
	ccdc->ccdc_cfg.ycbcw.win.top = 0;
	ccdc->ccdc_cfg.ycbcw.win.width = 720;
	ccdc->ccdc_cfg.ycbcw.win.height = 576;
	ccdc->ccdc_cfg.ycbcw.bt656_enabwe = 1;

	ccdc->ccdc_cfg.bayew.pix_fmt = CCDC_PIXFMT_WAW;
	ccdc->ccdc_cfg.bayew.fwm_fmt = CCDC_FWMFMT_PWOGWESSIVE;
	ccdc->ccdc_cfg.bayew.fid_pow = VPFE_PINPOW_POSITIVE;
	ccdc->ccdc_cfg.bayew.vd_pow = VPFE_PINPOW_POSITIVE;
	ccdc->ccdc_cfg.bayew.hd_pow = VPFE_PINPOW_POSITIVE;

	ccdc->ccdc_cfg.bayew.win.weft = 0;
	ccdc->ccdc_cfg.bayew.win.top = 0;
	ccdc->ccdc_cfg.bayew.win.width = 800;
	ccdc->ccdc_cfg.bayew.win.height = 600;
	ccdc->ccdc_cfg.bayew.config_pawams.data_sz = VPFE_CCDC_DATA_8BITS;
	ccdc->ccdc_cfg.bayew.config_pawams.awaw.gamma_wd =
						VPFE_CCDC_GAMMA_BITS_09_0;
}

/*
 * vpfe_get_ccdc_image_fowmat - Get image pawametews based on CCDC settings
 */
static int vpfe_get_ccdc_image_fowmat(stwuct vpfe_device *vpfe,
				      stwuct v4w2_fowmat *f)
{
	stwuct v4w2_wect image_win;
	enum ccdc_buftype buf_type;
	enum ccdc_fwmfmt fwm_fmt;

	memset(f, 0, sizeof(*f));
	f->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	vpfe_ccdc_get_image_window(&vpfe->ccdc, &image_win);
	f->fmt.pix.width = image_win.width;
	f->fmt.pix.height = image_win.height;
	f->fmt.pix.bytespewwine = vpfe_ccdc_get_wine_wength(&vpfe->ccdc);
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine *
				f->fmt.pix.height;
	buf_type = vpfe_ccdc_get_buftype(&vpfe->ccdc);
	f->fmt.pix.pixewfowmat = vpfe_ccdc_get_pixew_fowmat(&vpfe->ccdc);
	fwm_fmt = vpfe_ccdc_get_fwame_fowmat(&vpfe->ccdc);

	if (fwm_fmt == CCDC_FWMFMT_PWOGWESSIVE) {
		f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	} ewse if (fwm_fmt == CCDC_FWMFMT_INTEWWACED) {
		if (buf_type == CCDC_BUFTYPE_FWD_INTEWWEAVED) {
			f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;
		 } ewse if (buf_type == CCDC_BUFTYPE_FWD_SEPAWATED) {
			f->fmt.pix.fiewd = V4W2_FIEWD_SEQ_TB;
		} ewse {
			vpfe_eww(vpfe, "Invawid buf_type\n");
			wetuwn -EINVAW;
		}
	} ewse {
		vpfe_eww(vpfe, "Invawid fwm_fmt\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int vpfe_config_ccdc_image_fowmat(stwuct vpfe_device *vpfe)
{
	enum ccdc_fwmfmt fwm_fmt = CCDC_FWMFMT_INTEWWACED;
	u32 bpp;
	int wet = 0;

	vpfe_dbg(1, vpfe, "pixewfowmat: %s\n",
		pwint_fouwcc(vpfe->fmt.fmt.pix.pixewfowmat));

	if (vpfe_ccdc_set_pixew_fowmat(&vpfe->ccdc,
			vpfe->fmt.fmt.pix.pixewfowmat) < 0) {
		vpfe_eww(vpfe, "couwdn't set pix fowmat in ccdc\n");
		wetuwn -EINVAW;
	}

	/* configuwe the image window */
	bpp = __get_bytespewpixew(vpfe, vpfe->cuwwent_vpfe_fmt);
	vpfe_ccdc_set_image_window(&vpfe->ccdc, &vpfe->cwop, bpp);

	switch (vpfe->fmt.fmt.pix.fiewd) {
	case V4W2_FIEWD_INTEWWACED:
		/* do nothing, since it is defauwt */
		wet = vpfe_ccdc_set_buftype(
				&vpfe->ccdc,
				CCDC_BUFTYPE_FWD_INTEWWEAVED);
		bweak;

	case V4W2_FIEWD_NONE:
		fwm_fmt = CCDC_FWMFMT_PWOGWESSIVE;
		/* buffew type onwy appwicabwe fow intewwaced scan */
		bweak;

	case V4W2_FIEWD_SEQ_TB:
		wet = vpfe_ccdc_set_buftype(
				&vpfe->ccdc,
				CCDC_BUFTYPE_FWD_SEPAWATED);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (wet)
		wetuwn wet;

	wetuwn vpfe_ccdc_set_fwame_fowmat(&vpfe->ccdc, fwm_fmt);
}

/*
 * vpfe_config_image_fowmat()
 * Fow a given standawd, this functions sets up the defauwt
 * pix fowmat & cwop vawues in the vpfe device and ccdc.  It fiwst
 * stawts with defauwts based vawues fwom the standawd tabwe.
 * It then checks if sub device suppowts get_fmt and then ovewwide the
 * vawues based on that.Sets cwop vawues to match with scan wesowution
 * stawting at 0,0. It cawws vpfe_config_ccdc_image_fowmat() set the
 * vawues in ccdc
 */
static int vpfe_config_image_fowmat(stwuct vpfe_device *vpfe,
				    v4w2_std_id std_id)
{
	stwuct vpfe_fmt *fmt;
	stwuct v4w2_mbus_fwamefmt mbus_fmt;
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(vpfe_standawds); i++) {
		if (vpfe_standawds[i].std_id & std_id) {
			vpfe->std_info.active_pixews =
					vpfe_standawds[i].width;
			vpfe->std_info.active_wines =
					vpfe_standawds[i].height;
			vpfe->std_info.fwame_fowmat =
					vpfe_standawds[i].fwame_fowmat;
			vpfe->std_index = i;

			bweak;
		}
	}

	if (i ==  AWWAY_SIZE(vpfe_standawds)) {
		vpfe_eww(vpfe, "standawd not suppowted\n");
		wetuwn -EINVAW;
	}

	wet = __subdev_get_fowmat(vpfe, &mbus_fmt);
	if (wet)
		wetuwn wet;

	fmt = find_fowmat_by_code(vpfe, mbus_fmt.code);
	if (!fmt) {
		vpfe_dbg(3, vpfe, "mbus code fowmat (0x%08x) not found.\n",
			 mbus_fmt.code);
		wetuwn -EINVAW;
	}

	/* Save cuwwent subdev fowmat */
	v4w2_fiww_pix_fowmat(&vpfe->fmt.fmt.pix, &mbus_fmt);
	vpfe->fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	vpfe->fmt.fmt.pix.pixewfowmat = fmt->fouwcc;
	vpfe_cawc_fowmat_size(vpfe, fmt, &vpfe->fmt);
	vpfe->cuwwent_vpfe_fmt = fmt;

	/* Update the cwop window based on found vawues */
	vpfe->cwop.top = 0;
	vpfe->cwop.weft = 0;
	vpfe->cwop.width = mbus_fmt.width;
	vpfe->cwop.height = mbus_fmt.height;

	wetuwn vpfe_config_ccdc_image_fowmat(vpfe);
}

static int vpfe_initiawize_device(stwuct vpfe_device *vpfe)
{
	stwuct vpfe_subdev_info *sdinfo;
	int wet;

	sdinfo = &vpfe->cfg->sub_devs[0];
	sdinfo->sd = vpfe->sd[0];
	vpfe->cuwwent_input = 0;
	vpfe->std_index = 0;
	/* Configuwe the defauwt fowmat infowmation */
	wet = vpfe_config_image_fowmat(vpfe,
				       vpfe_standawds[vpfe->std_index].std_id);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(vpfe->pdev);
	if (wet < 0)
		wetuwn wet;

	vpfe_config_enabwe(&vpfe->ccdc, 1);

	vpfe_ccdc_westowe_defauwts(&vpfe->ccdc);

	/* Cweaw aww VPFE intewwupts */
	vpfe_cweaw_intw(&vpfe->ccdc, -1);

	wetuwn wet;
}

/*
 * vpfe_wewease : This function is based on the vb2_fop_wewease
 * hewpew function.
 * It has been augmented to handwe moduwe powew management,
 * by disabwing/enabwing h/w moduwe fcntw cwock when necessawy.
 */
static int vpfe_wewease(stwuct fiwe *fiwe)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	boow fh_singuwaw;
	int wet;

	mutex_wock(&vpfe->wock);

	/* Save the singuwaw status befowe we caww the cwean-up hewpew */
	fh_singuwaw = v4w2_fh_is_singuwaw_fiwe(fiwe);

	/* the wewease hewpew wiww cweanup any on-going stweaming */
	wet = _vb2_fop_wewease(fiwe, NUWW);

	/*
	 * If this was the wast open fiwe.
	 * Then de-initiawize hw moduwe.
	 */
	if (fh_singuwaw)
		vpfe_ccdc_cwose(&vpfe->ccdc, vpfe->pdev);

	mutex_unwock(&vpfe->wock);

	wetuwn wet;
}

/*
 * vpfe_open : This function is based on the v4w2_fh_open hewpew function.
 * It has been augmented to handwe moduwe powew management,
 * by disabwing/enabwing h/w moduwe fcntw cwock when necessawy.
 */
static int vpfe_open(stwuct fiwe *fiwe)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	int wet;

	mutex_wock(&vpfe->wock);

	wet = v4w2_fh_open(fiwe);
	if (wet) {
		vpfe_eww(vpfe, "v4w2_fh_open faiwed\n");
		goto unwock;
	}

	if (!v4w2_fh_is_singuwaw_fiwe(fiwe))
		goto unwock;

	if (vpfe_initiawize_device(vpfe)) {
		v4w2_fh_wewease(fiwe);
		wet = -ENODEV;
	}

unwock:
	mutex_unwock(&vpfe->wock);
	wetuwn wet;
}

/**
 * vpfe_scheduwe_next_buffew: set next buffew addwess fow captuwe
 * @vpfe : ptw to vpfe device
 *
 * This function wiww get next buffew fwom the dma queue and
 * set the buffew addwess in the vpfe wegistew fow captuwe.
 * the buffew is mawked active
 */
static void vpfe_scheduwe_next_buffew(stwuct vpfe_device *vpfe)
{
	dma_addw_t addw;

	spin_wock(&vpfe->dma_queue_wock);
	if (wist_empty(&vpfe->dma_queue)) {
		spin_unwock(&vpfe->dma_queue_wock);
		wetuwn;
	}

	vpfe->next_fwm = wist_entwy(vpfe->dma_queue.next,
				    stwuct vpfe_cap_buffew, wist);
	wist_dew(&vpfe->next_fwm->wist);
	spin_unwock(&vpfe->dma_queue_wock);

	addw = vb2_dma_contig_pwane_dma_addw(&vpfe->next_fwm->vb.vb2_buf, 0);
	vpfe_set_sdw_addw(&vpfe->ccdc, addw);
}

static inwine void vpfe_scheduwe_bottom_fiewd(stwuct vpfe_device *vpfe)
{
	dma_addw_t addw;

	addw = vb2_dma_contig_pwane_dma_addw(&vpfe->next_fwm->vb.vb2_buf, 0) +
					vpfe->fiewd_off;

	vpfe_set_sdw_addw(&vpfe->ccdc, addw);
}

/*
 * vpfe_pwocess_buffew_compwete: pwocess a compweted buffew
 * @vpfe : ptw to vpfe device
 *
 * This function time stamp the buffew and mawk it as DONE. It awso
 * wake up any pwocess waiting on the QUEUE and set the next buffew
 * as cuwwent
 */
static inwine void vpfe_pwocess_buffew_compwete(stwuct vpfe_device *vpfe)
{
	vpfe->cuw_fwm->vb.vb2_buf.timestamp = ktime_get_ns();
	vpfe->cuw_fwm->vb.fiewd = vpfe->fmt.fmt.pix.fiewd;
	vpfe->cuw_fwm->vb.sequence = vpfe->sequence++;
	vb2_buffew_done(&vpfe->cuw_fwm->vb.vb2_buf, VB2_BUF_STATE_DONE);
	vpfe->cuw_fwm = vpfe->next_fwm;
}

static void vpfe_handwe_intewwaced_iwq(stwuct vpfe_device *vpfe,
				       enum v4w2_fiewd fiewd)
{
	int fid;

	/* intewwaced ow TB captuwe check which fiewd
	 * we awe in hawdwawe
	 */
	fid = vpfe_ccdc_getfid(&vpfe->ccdc);

	/* switch the softwawe maintained fiewd id */
	vpfe->fiewd ^= 1;
	if (fid == vpfe->fiewd) {
		/* we awe in-sync hewe,continue */
		if (fid == 0) {
			/*
			 * One fwame is just being captuwed. If the
			 * next fwame is avaiwabwe, wewease the
			 * cuwwent fwame and move on
			 */
			if (vpfe->cuw_fwm != vpfe->next_fwm)
				vpfe_pwocess_buffew_compwete(vpfe);

			if (vpfe->stopping)
				wetuwn;

			/*
			 * based on whethew the two fiewds awe stowed
			 * intewweave ow sepawatewy in memowy,
			 * weconfiguwe the CCDC memowy addwess
			 */
			if (fiewd == V4W2_FIEWD_SEQ_TB)
				vpfe_scheduwe_bottom_fiewd(vpfe);
		} ewse {
			/*
			 * if one fiewd is just being captuwed configuwe
			 * the next fwame get the next fwame fwom the empty
			 * queue if no fwame is avaiwabwe howd on to the
			 * cuwwent buffew
			 */
			if (vpfe->cuw_fwm == vpfe->next_fwm)
				vpfe_scheduwe_next_buffew(vpfe);
		}
	} ewse if (fid == 0) {
		/*
		 * out of sync. Wecovew fwom any hawdwawe out-of-sync.
		 * May woose one fwame
		 */
		vpfe->fiewd = fid;
	}
}

/*
 * vpfe_isw : ISW handwew fow vpfe captuwe (VINT0)
 * @iwq: iwq numbew
 * @dev_id: dev_id ptw
 *
 * It changes status of the captuwed buffew, takes next buffew fwom the queue
 * and sets its addwess in VPFE wegistews
 */
static iwqwetuwn_t vpfe_isw(int iwq, void *dev)
{
	stwuct vpfe_device *vpfe = (stwuct vpfe_device *)dev;
	enum v4w2_fiewd fiewd = vpfe->fmt.fmt.pix.fiewd;
	int intw_status, stopping = vpfe->stopping;

	intw_status = vpfe_weg_wead(&vpfe->ccdc, VPFE_IWQ_STS);

	if (intw_status & VPFE_VDINT0) {
		if (fiewd == V4W2_FIEWD_NONE) {
			if (vpfe->cuw_fwm != vpfe->next_fwm)
				vpfe_pwocess_buffew_compwete(vpfe);
		} ewse {
			vpfe_handwe_intewwaced_iwq(vpfe, fiewd);
		}
		if (stopping) {
			vpfe->stopping = fawse;
			compwete(&vpfe->captuwe_stop);
		}
	}

	if (intw_status & VPFE_VDINT1 && !stopping) {
		if (fiewd == V4W2_FIEWD_NONE &&
		    vpfe->cuw_fwm == vpfe->next_fwm)
			vpfe_scheduwe_next_buffew(vpfe);
	}

	vpfe_cweaw_intw(&vpfe->ccdc, intw_status);

	wetuwn IWQ_HANDWED;
}

static inwine void vpfe_detach_iwq(stwuct vpfe_device *vpfe)
{
	unsigned int intw = VPFE_VDINT0;
	enum ccdc_fwmfmt fwame_fowmat;

	fwame_fowmat = vpfe_ccdc_get_fwame_fowmat(&vpfe->ccdc);
	if (fwame_fowmat == CCDC_FWMFMT_PWOGWESSIVE)
		intw |= VPFE_VDINT1;

	vpfe_weg_wwite(&vpfe->ccdc, intw, VPFE_IWQ_EN_CWW);
}

static inwine void vpfe_attach_iwq(stwuct vpfe_device *vpfe)
{
	unsigned int intw = VPFE_VDINT0;
	enum ccdc_fwmfmt fwame_fowmat;

	fwame_fowmat = vpfe_ccdc_get_fwame_fowmat(&vpfe->ccdc);
	if (fwame_fowmat == CCDC_FWMFMT_PWOGWESSIVE)
		intw |= VPFE_VDINT1;

	vpfe_weg_wwite(&vpfe->ccdc, intw, VPFE_IWQ_EN_SET);
}

static int vpfe_quewycap(stwuct fiwe *fiwe, void  *pwiv,
			 stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, VPFE_MODUWE_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "TI AM437x VPFE", sizeof(cap->cawd));
	wetuwn 0;
}

/* get the fowmat set at output pad of the adjacent subdev */
static int __subdev_get_fowmat(stwuct vpfe_device *vpfe,
			       stwuct v4w2_mbus_fwamefmt *fmt)
{
	stwuct v4w2_subdev *sd = vpfe->cuwwent_subdev->sd;
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.pad = 0,
	};
	stwuct v4w2_mbus_fwamefmt *mbus_fmt = &sd_fmt.fowmat;
	int wet;

	wet = v4w2_subdev_caww(sd, pad, get_fmt, NUWW, &sd_fmt);
	if (wet)
		wetuwn wet;

	*fmt = *mbus_fmt;

	vpfe_dbg(1, vpfe, "%s: %dx%d code:%04X\n", __func__,
		 fmt->width, fmt->height, fmt->code);

	wetuwn 0;
}

/* set the fowmat at output pad of the adjacent subdev */
static int __subdev_set_fowmat(stwuct vpfe_device *vpfe,
			       stwuct v4w2_mbus_fwamefmt *fmt)
{
	stwuct v4w2_subdev *sd = vpfe->cuwwent_subdev->sd;
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.pad = 0,
	};
	stwuct v4w2_mbus_fwamefmt *mbus_fmt = &sd_fmt.fowmat;
	int wet;

	*mbus_fmt = *fmt;

	wet = v4w2_subdev_caww(sd, pad, set_fmt, NUWW, &sd_fmt);
	if (wet)
		wetuwn wet;

	vpfe_dbg(1, vpfe, "%s %dx%d code:%04X\n", __func__,
		 fmt->width, fmt->height, fmt->code);

	wetuwn 0;
}

static int vpfe_cawc_fowmat_size(stwuct vpfe_device *vpfe,
				 const stwuct vpfe_fmt *fmt,
				 stwuct v4w2_fowmat *f)
{
	u32 bpp;

	if (!fmt) {
		vpfe_dbg(3, vpfe, "No vpfe_fmt pwovided!\n");
		wetuwn -EINVAW;
	}

	bpp = __get_bytespewpixew(vpfe, fmt);

	/* pitch shouwd be 32 bytes awigned */
	f->fmt.pix.bytespewwine = AWIGN(f->fmt.pix.width * bpp, 32);
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine *
			       f->fmt.pix.height;

	vpfe_dbg(3, vpfe, "%s: fouwcc: %s size: %dx%d bpw:%d img_size:%d\n",
		 __func__, pwint_fouwcc(f->fmt.pix.pixewfowmat),
		 f->fmt.pix.width, f->fmt.pix.height,
		 f->fmt.pix.bytespewwine, f->fmt.pix.sizeimage);

	wetuwn 0;
}

static int vpfe_g_fmt(stwuct fiwe *fiwe, void *pwiv,
		      stwuct v4w2_fowmat *fmt)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);

	*fmt = vpfe->fmt;

	wetuwn 0;
}

static int vpfe_enum_fmt(stwuct fiwe *fiwe, void  *pwiv,
			 stwuct v4w2_fmtdesc *f)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct vpfe_subdev_info *sdinfo;
	stwuct vpfe_fmt *fmt;

	sdinfo = vpfe->cuwwent_subdev;
	if (!sdinfo->sd)
		wetuwn -EINVAW;

	if (f->index >= vpfe->num_active_fmt)
		wetuwn -EINVAW;

	fmt = vpfe->active_fmt[f->index];

	f->pixewfowmat = fmt->fouwcc;

	vpfe_dbg(1, vpfe, "%s: mbus index: %d code: %x pixewfowmat: %s\n",
		 __func__, f->index, fmt->code, pwint_fouwcc(fmt->fouwcc));

	wetuwn 0;
}

static int vpfe_twy_fmt(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_fowmat *f)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = vpfe->cuwwent_subdev->sd;
	const stwuct vpfe_fmt *fmt;
	stwuct v4w2_subdev_fwame_size_enum fse = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet, found;

	fmt = find_fowmat_by_pix(vpfe, f->fmt.pix.pixewfowmat);
	if (!fmt) {
		/* defauwt to fiwst entwy */
		vpfe_dbg(3, vpfe, "Invawid pixew code: %x, defauwt used instead\n",
			 f->fmt.pix.pixewfowmat);
		fmt = vpfe->active_fmt[0];
		f->fmt.pix.pixewfowmat = fmt->fouwcc;
	}

	f->fmt.pix.fiewd = vpfe->fmt.fmt.pix.fiewd;

	/* check fow/find a vawid width/height */
	wet = 0;
	found = fawse;
	fse.pad = 0;
	fse.code = fmt->code;
	fow (fse.index = 0; ; fse.index++) {
		wet = v4w2_subdev_caww(sd, pad, enum_fwame_size,
				       NUWW, &fse);
		if (wet)
			bweak;

		if (f->fmt.pix.width == fse.max_width &&
		    f->fmt.pix.height == fse.max_height) {
			found = twue;
			bweak;
		} ewse if (f->fmt.pix.width >= fse.min_width &&
			   f->fmt.pix.width <= fse.max_width &&
			   f->fmt.pix.height >= fse.min_height &&
			   f->fmt.pix.height <= fse.max_height) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		/* use existing vawues as defauwt */
		f->fmt.pix.width = vpfe->fmt.fmt.pix.width;
		f->fmt.pix.height =  vpfe->fmt.fmt.pix.height;
	}

	/*
	 * Use cuwwent cowowspace fow now, it wiww get
	 * updated pwopewwy duwing s_fmt
	 */
	f->fmt.pix.cowowspace = vpfe->fmt.fmt.pix.cowowspace;
	wetuwn vpfe_cawc_fowmat_size(vpfe, fmt, f);
}

static int vpfe_s_fmt(stwuct fiwe *fiwe, void *pwiv,
		      stwuct v4w2_fowmat *fmt)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct vpfe_fmt *f;
	stwuct v4w2_mbus_fwamefmt mbus_fmt;
	int wet;

	/* If stweaming is stawted, wetuwn ewwow */
	if (vb2_is_busy(&vpfe->buffew_queue)) {
		vpfe_eww(vpfe, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	wet = vpfe_twy_fmt(fiwe, pwiv, fmt);
	if (wet < 0)
		wetuwn wet;

	f = find_fowmat_by_pix(vpfe, fmt->fmt.pix.pixewfowmat);

	v4w2_fiww_mbus_fowmat(&mbus_fmt, &fmt->fmt.pix, f->code);

	wet = __subdev_set_fowmat(vpfe, &mbus_fmt);
	if (wet)
		wetuwn wet;

	/* Just doubwe check nothing has gone wwong */
	if (mbus_fmt.code != f->code) {
		vpfe_dbg(3, vpfe,
			 "%s subdev changed fowmat on us, this shouwd not happen\n",
			 __func__);
		wetuwn -EINVAW;
	}

	v4w2_fiww_pix_fowmat(&vpfe->fmt.fmt.pix, &mbus_fmt);
	vpfe->fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	vpfe->fmt.fmt.pix.pixewfowmat  = f->fouwcc;
	vpfe_cawc_fowmat_size(vpfe, f, &vpfe->fmt);
	*fmt = vpfe->fmt;
	vpfe->cuwwent_vpfe_fmt = f;

	/* Update the cwop window based on found vawues */
	vpfe->cwop.width = fmt->fmt.pix.width;
	vpfe->cwop.height = fmt->fmt.pix.height;

	/* set image captuwe pawametews in the ccdc */
	wetuwn vpfe_config_ccdc_image_fowmat(vpfe);
}

static int vpfe_enum_size(stwuct fiwe *fiwe, void  *pwiv,
			  stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fwame_size_enum fse = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *sd = vpfe->cuwwent_subdev->sd;
	stwuct vpfe_fmt *fmt;
	int wet;

	/* check fow vawid fowmat */
	fmt = find_fowmat_by_pix(vpfe, fsize->pixew_fowmat);
	if (!fmt) {
		vpfe_dbg(3, vpfe, "Invawid pixew code: %x\n",
			 fsize->pixew_fowmat);
		wetuwn -EINVAW;
	}

	memset(fsize->wesewved, 0x0, sizeof(fsize->wesewved));

	fse.index = fsize->index;
	fse.pad = 0;
	fse.code = fmt->code;
	wet = v4w2_subdev_caww(sd, pad, enum_fwame_size, NUWW, &fse);
	if (wet)
		wetuwn wet;

	vpfe_dbg(1, vpfe, "%s: index: %d code: %x W:[%d,%d] H:[%d,%d]\n",
		 __func__, fse.index, fse.code, fse.min_width, fse.max_width,
		 fse.min_height, fse.max_height);

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = fse.max_width;
	fsize->discwete.height = fse.max_height;

	vpfe_dbg(1, vpfe, "%s: index: %d pixfowmat: %s size: %dx%d\n",
		 __func__, fsize->index, pwint_fouwcc(fsize->pixew_fowmat),
		 fsize->discwete.width, fsize->discwete.height);

	wetuwn 0;
}

/*
 * vpfe_get_subdev_input_index - Get subdev index and subdev input index fow a
 * given app input index
 */
static int
vpfe_get_subdev_input_index(stwuct vpfe_device *vpfe,
			    int *subdev_index,
			    int *subdev_input_index,
			    int app_input_index)
{
	int i, j = 0;

	fow (i = 0; i < AWWAY_SIZE(vpfe->cfg->asd); i++) {
		if (app_input_index < (j + 1)) {
			*subdev_index = i;
			*subdev_input_index = app_input_index - j;
			wetuwn 0;
		}
		j++;
	}
	wetuwn -EINVAW;
}

/*
 * vpfe_get_app_input - Get app input index fow a given subdev input index
 * dwivew stowes the input index of the cuwwent sub device and twanswate it
 * when appwication wequest the cuwwent input
 */
static int vpfe_get_app_input_index(stwuct vpfe_device *vpfe,
				    int *app_input_index)
{
	stwuct vpfe_config *cfg = vpfe->cfg;
	stwuct vpfe_subdev_info *sdinfo;
	stwuct i2c_cwient *cwient;
	stwuct i2c_cwient *cuww_cwient;
	int i, j = 0;

	cuww_cwient = v4w2_get_subdevdata(vpfe->cuwwent_subdev->sd);
	fow (i = 0; i < AWWAY_SIZE(vpfe->cfg->asd); i++) {
		sdinfo = &cfg->sub_devs[i];
		cwient = v4w2_get_subdevdata(sdinfo->sd);
		if (cwient->addw == cuww_cwient->addw &&
		    cwient->adaptew->nw == cuww_cwient->adaptew->nw) {
			if (vpfe->cuwwent_input >= 1)
				wetuwn -1;
			*app_input_index = j + vpfe->cuwwent_input;
			wetuwn 0;
		}
		j++;
	}
	wetuwn -EINVAW;
}

static int vpfe_enum_input(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_input *inp)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct vpfe_subdev_info *sdinfo;
	int subdev, index;

	if (vpfe_get_subdev_input_index(vpfe, &subdev, &index,
					inp->index) < 0) {
		vpfe_dbg(1, vpfe,
			"input infowmation not found fow the subdev\n");
		wetuwn -EINVAW;
	}
	sdinfo = &vpfe->cfg->sub_devs[subdev];
	*inp = sdinfo->inputs[index];

	wetuwn 0;
}

static int vpfe_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *index)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);

	wetuwn vpfe_get_app_input_index(vpfe, index);
}

/* Assumes cawwew is howding vpfe_dev->wock */
static int vpfe_set_input(stwuct vpfe_device *vpfe, unsigned int index)
{
	int subdev_index = 0, inp_index = 0;
	stwuct vpfe_subdev_info *sdinfo;
	stwuct vpfe_woute *woute;
	u32 input, output;
	int wet;

	/* If stweaming is stawted, wetuwn ewwow */
	if (vb2_is_busy(&vpfe->buffew_queue)) {
		vpfe_eww(vpfe, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}
	wet = vpfe_get_subdev_input_index(vpfe,
					  &subdev_index,
					  &inp_index,
					  index);
	if (wet < 0) {
		vpfe_eww(vpfe, "invawid input index: %d\n", index);
		goto get_out;
	}

	sdinfo = &vpfe->cfg->sub_devs[subdev_index];
	sdinfo->sd = vpfe->sd[subdev_index];
	woute = &sdinfo->woutes[inp_index];
	if (woute && sdinfo->can_woute) {
		input = woute->input;
		output = woute->output;
		if (sdinfo->sd) {
			wet = v4w2_subdev_caww(sdinfo->sd, video,
					s_wouting, input, output, 0);
			if (wet) {
				vpfe_eww(vpfe, "s_wouting faiwed\n");
				wet = -EINVAW;
				goto get_out;
			}
		}

	}

	vpfe->cuwwent_subdev = sdinfo;
	if (sdinfo->sd)
		vpfe->v4w2_dev.ctww_handwew = sdinfo->sd->ctww_handwew;
	vpfe->cuwwent_input = index;
	vpfe->std_index = 0;

	/* set the bus/intewface pawametew fow the sub device in ccdc */
	wet = vpfe_ccdc_set_hw_if_pawams(&vpfe->ccdc, &sdinfo->vpfe_pawam);
	if (wet)
		wetuwn wet;

	/* set the defauwt image pawametews in the device */
	wetuwn vpfe_config_image_fowmat(vpfe,
					vpfe_standawds[vpfe->std_index].std_id);

get_out:
	wetuwn wet;
}

static int vpfe_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int index)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);

	wetuwn vpfe_set_input(vpfe, index);
}

static int vpfe_quewystd(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std_id)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct vpfe_subdev_info *sdinfo;

	sdinfo = vpfe->cuwwent_subdev;
	if (!(sdinfo->inputs[0].capabiwities & V4W2_IN_CAP_STD))
		wetuwn -ENODATA;

	/* Caww quewystd function of decodew device */
	wetuwn v4w2_device_caww_untiw_eww(&vpfe->v4w2_dev, sdinfo->gwp_id,
					 video, quewystd, std_id);
}

static int vpfe_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id std_id)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct vpfe_subdev_info *sdinfo;
	int wet;

	sdinfo = vpfe->cuwwent_subdev;
	if (!(sdinfo->inputs[0].capabiwities & V4W2_IN_CAP_STD))
		wetuwn -ENODATA;

	/* if twying to set the same std then nothing to do */
	if (vpfe_standawds[vpfe->std_index].std_id == std_id)
		wetuwn 0;

	/* If stweaming is stawted, wetuwn ewwow */
	if (vb2_is_busy(&vpfe->buffew_queue)) {
		vpfe_eww(vpfe, "%s device busy\n", __func__);
		wet = -EBUSY;
		wetuwn wet;
	}

	wet = v4w2_device_caww_untiw_eww(&vpfe->v4w2_dev, sdinfo->gwp_id,
					 video, s_std, std_id);
	if (wet < 0) {
		vpfe_eww(vpfe, "Faiwed to set standawd\n");
		wetuwn wet;
	}
	wet = vpfe_config_image_fowmat(vpfe, std_id);

	wetuwn wet;
}

static int vpfe_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *std_id)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct vpfe_subdev_info *sdinfo;

	sdinfo = vpfe->cuwwent_subdev;
	if (sdinfo->inputs[0].capabiwities != V4W2_IN_CAP_STD)
		wetuwn -ENODATA;

	*std_id = vpfe_standawds[vpfe->std_index].std_id;

	wetuwn 0;
}

/*
 * vpfe_cawcuwate_offsets : This function cawcuwates buffews offset
 * fow top and bottom fiewd
 */
static void vpfe_cawcuwate_offsets(stwuct vpfe_device *vpfe)
{
	stwuct v4w2_wect image_win;

	vpfe_ccdc_get_image_window(&vpfe->ccdc, &image_win);
	vpfe->fiewd_off = image_win.height * image_win.width;
}

/*
 * vpfe_queue_setup - Cawwback function fow buffew setup.
 * @vq: vb2_queue ptw
 * @nbuffews: ptw to numbew of buffews wequested by appwication
 * @npwanes:: contains numbew of distinct video pwanes needed to howd a fwame
 * @sizes[]: contains the size (in bytes) of each pwane.
 * @awwoc_devs: ptw to awwocation context
 *
 * This cawwback function is cawwed when weqbuf() is cawwed to adjust
 * the buffew count and buffew size
 */
static int vpfe_queue_setup(stwuct vb2_queue *vq,
			    unsigned int *nbuffews, unsigned int *npwanes,
			    unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct vpfe_device *vpfe = vb2_get_dwv_pwiv(vq);
	unsigned size = vpfe->fmt.fmt.pix.sizeimage;
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	if (q_num_bufs + *nbuffews < 3)
		*nbuffews = 3 - q_num_bufs;

	if (*npwanes) {
		if (sizes[0] < size)
			wetuwn -EINVAW;
		size = sizes[0];
	}

	*npwanes = 1;
	sizes[0] = size;

	vpfe_dbg(1, vpfe,
		"nbuffews=%d, size=%u\n", *nbuffews, sizes[0]);

	/* Cawcuwate fiewd offset */
	vpfe_cawcuwate_offsets(vpfe);

	wetuwn 0;
}

/*
 * vpfe_buffew_pwepawe :  cawwback function fow buffew pwepawe
 * @vb: ptw to vb2_buffew
 *
 * This is the cawwback function fow buffew pwepawe when vb2_qbuf()
 * function is cawwed. The buffew is pwepawed and usew space viwtuaw addwess
 * ow usew addwess is convewted into  physicaw addwess
 */
static int vpfe_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vpfe_device *vpfe = vb2_get_dwv_pwiv(vb->vb2_queue);

	vb2_set_pwane_paywoad(vb, 0, vpfe->fmt.fmt.pix.sizeimage);

	if (vb2_get_pwane_paywoad(vb, 0) > vb2_pwane_size(vb, 0))
		wetuwn -EINVAW;

	vbuf->fiewd = vpfe->fmt.fmt.pix.fiewd;

	wetuwn 0;
}

/*
 * vpfe_buffew_queue : Cawwback function to add buffew to DMA queue
 * @vb: ptw to vb2_buffew
 */
static void vpfe_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vpfe_device *vpfe = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vpfe_cap_buffew *buf = to_vpfe_buffew(vbuf);
	unsigned wong fwags = 0;

	/* add the buffew to the DMA queue */
	spin_wock_iwqsave(&vpfe->dma_queue_wock, fwags);
	wist_add_taiw(&buf->wist, &vpfe->dma_queue);
	spin_unwock_iwqwestowe(&vpfe->dma_queue_wock, fwags);
}

static void vpfe_wetuwn_aww_buffews(stwuct vpfe_device *vpfe,
				    enum vb2_buffew_state state)
{
	stwuct vpfe_cap_buffew *buf, *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&vpfe->dma_queue_wock, fwags);
	wist_fow_each_entwy_safe(buf, node, &vpfe->dma_queue, wist) {
		vb2_buffew_done(&buf->vb.vb2_buf, state);
		wist_dew(&buf->wist);
	}

	if (vpfe->cuw_fwm)
		vb2_buffew_done(&vpfe->cuw_fwm->vb.vb2_buf, state);

	if (vpfe->next_fwm && vpfe->next_fwm != vpfe->cuw_fwm)
		vb2_buffew_done(&vpfe->next_fwm->vb.vb2_buf, state);

	vpfe->cuw_fwm = NUWW;
	vpfe->next_fwm = NUWW;
	spin_unwock_iwqwestowe(&vpfe->dma_queue_wock, fwags);
}

/*
 * vpfe_stawt_stweaming : Stawts the DMA engine fow stweaming
 * @vb: ptw to vb2_buffew
 * @count: numbew of buffews
 */
static int vpfe_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct vpfe_device *vpfe = vb2_get_dwv_pwiv(vq);
	stwuct vpfe_subdev_info *sdinfo;
	unsigned wong fwags;
	unsigned wong addw;
	int wet;

	spin_wock_iwqsave(&vpfe->dma_queue_wock, fwags);

	vpfe->fiewd = 0;
	vpfe->sequence = 0;

	sdinfo = vpfe->cuwwent_subdev;

	vpfe_attach_iwq(vpfe);

	vpfe->stopping = fawse;
	init_compwetion(&vpfe->captuwe_stop);

	if (vpfe->ccdc.ccdc_cfg.if_type == VPFE_WAW_BAYEW)
		vpfe_ccdc_config_waw(&vpfe->ccdc);
	ewse
		vpfe_ccdc_config_ycbcw(&vpfe->ccdc);

	/* Get the next fwame fwom the buffew queue */
	vpfe->next_fwm = wist_entwy(vpfe->dma_queue.next,
				    stwuct vpfe_cap_buffew, wist);
	vpfe->cuw_fwm = vpfe->next_fwm;
	/* Wemove buffew fwom the buffew queue */
	wist_dew(&vpfe->cuw_fwm->wist);
	spin_unwock_iwqwestowe(&vpfe->dma_queue_wock, fwags);

	addw = vb2_dma_contig_pwane_dma_addw(&vpfe->cuw_fwm->vb.vb2_buf, 0);

	vpfe_set_sdw_addw(&vpfe->ccdc, (unsigned wong)(addw));

	vpfe_pcw_enabwe(&vpfe->ccdc, 1);

	wet = v4w2_subdev_caww(sdinfo->sd, video, s_stweam, 1);
	if (wet < 0) {
		vpfe_eww(vpfe, "Ewwow in attaching intewwupt handwe\n");
		goto eww;
	}

	wetuwn 0;

eww:
	vpfe_wetuwn_aww_buffews(vpfe, VB2_BUF_STATE_QUEUED);
	vpfe_pcw_enabwe(&vpfe->ccdc, 0);
	wetuwn wet;
}

/*
 * vpfe_stop_stweaming : Stop the DMA engine
 * @vq: ptw to vb2_queue
 *
 * This cawwback stops the DMA engine and any wemaining buffews
 * in the DMA queue awe weweased.
 */
static void vpfe_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct vpfe_device *vpfe = vb2_get_dwv_pwiv(vq);
	stwuct vpfe_subdev_info *sdinfo;
	int wet;

	vpfe_pcw_enabwe(&vpfe->ccdc, 0);

	/* Wait fow the wast fwame to be captuwed */
	vpfe->stopping = twue;
	wait_fow_compwetion_timeout(&vpfe->captuwe_stop,
				    msecs_to_jiffies(250));

	vpfe_detach_iwq(vpfe);

	sdinfo = vpfe->cuwwent_subdev;
	wet = v4w2_subdev_caww(sdinfo->sd, video, s_stweam, 0);
	if (wet && wet != -ENOIOCTWCMD && wet != -ENODEV)
		vpfe_dbg(1, vpfe, "stweam off faiwed in subdev\n");

	/* wewease aww active buffews */
	vpfe_wetuwn_aww_buffews(vpfe, VB2_BUF_STATE_EWWOW);
}

static int vpfe_g_pixewaspect(stwuct fiwe *fiwe, void *pwiv,
			      int type, stwuct v4w2_fwact *f)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE ||
	    vpfe->std_index >= AWWAY_SIZE(vpfe_standawds))
		wetuwn -EINVAW;

	*f = vpfe_standawds[vpfe->std_index].pixewaspect;

	wetuwn 0;
}

static int
vpfe_g_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);

	if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE ||
	    vpfe->std_index >= AWWAY_SIZE(vpfe_standawds))
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = vpfe_standawds[vpfe->std_index].width;
		s->w.height = vpfe_standawds[vpfe->std_index].height;
		bweak;

	case V4W2_SEW_TGT_CWOP:
		s->w = vpfe->cwop;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
vpfe_s_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	stwuct v4w2_wect cw = vpfe->cwop;
	stwuct v4w2_wect w = s->w;
	u32 bpp;

	/* If stweaming is stawted, wetuwn ewwow */
	if (vb2_is_busy(&vpfe->buffew_queue)) {
		vpfe_eww(vpfe, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE ||
			s->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	v4w_bound_awign_image(&w.width, 0, cw.width, 0,
			      &w.height, 0, cw.height, 0, 0);

	w.weft = cwamp_t(unsigned int, w.weft, 0, cw.width - w.width);
	w.top  = cwamp_t(unsigned int, w.top, 0, cw.height - w.height);

	if (s->fwags & V4W2_SEW_FWAG_WE && !v4w2_wect_encwosed(&w, &s->w))
		wetuwn -EWANGE;

	if (s->fwags & V4W2_SEW_FWAG_GE && !v4w2_wect_encwosed(&s->w, &w))
		wetuwn -EWANGE;

	s->w = vpfe->cwop = w;

	bpp = __get_bytespewpixew(vpfe, vpfe->cuwwent_vpfe_fmt);
	vpfe_ccdc_set_image_window(&vpfe->ccdc, &w, bpp);
	vpfe->fmt.fmt.pix.width = w.width;
	vpfe->fmt.fmt.pix.height = w.height;
	vpfe->fmt.fmt.pix.bytespewwine =
		vpfe_ccdc_get_wine_wength(&vpfe->ccdc);
	vpfe->fmt.fmt.pix.sizeimage = vpfe->fmt.fmt.pix.bytespewwine *
						vpfe->fmt.fmt.pix.height;

	vpfe_dbg(1, vpfe, "cwopped (%d,%d)/%dx%d of %dx%d\n",
		 w.weft, w.top, w.width, w.height, cw.width, cw.height);

	wetuwn 0;
}

static wong vpfe_ioctw_defauwt(stwuct fiwe *fiwe, void *pwiv,
			       boow vawid_pwio, unsigned int cmd, void *pawam)
{
	stwuct vpfe_device *vpfe = video_dwvdata(fiwe);
	int wet;

	if (!vawid_pwio) {
		vpfe_eww(vpfe, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	/* If stweaming is stawted, wetuwn ewwow */
	if (vb2_is_busy(&vpfe->buffew_queue)) {
		vpfe_eww(vpfe, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	switch (cmd) {
	case VIDIOC_AM437X_CCDC_CFG:
		wet = vpfe_ccdc_set_pawams(&vpfe->ccdc, (void __usew *)pawam);
		if (wet) {
			vpfe_dbg(2, vpfe,
				"Ewwow setting pawametews in CCDC\n");
			wetuwn wet;
		}
		wet = vpfe_get_ccdc_image_fowmat(vpfe,
						 &vpfe->fmt);
		if (wet < 0) {
			vpfe_dbg(2, vpfe,
				"Invawid image fowmat at CCDC\n");
			wetuwn wet;
		}
		bweak;

	defauwt:
		wet = -ENOTTY;
		bweak;
	}

	wetuwn wet;
}

static const stwuct vb2_ops vpfe_video_qops = {
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
	.queue_setup		= vpfe_queue_setup,
	.buf_pwepawe		= vpfe_buffew_pwepawe,
	.buf_queue		= vpfe_buffew_queue,
	.stawt_stweaming	= vpfe_stawt_stweaming,
	.stop_stweaming		= vpfe_stop_stweaming,
};

/* vpfe captuwe dwivew fiwe opewations */
static const stwuct v4w2_fiwe_opewations vpfe_fops = {
	.ownew		= THIS_MODUWE,
	.open		= vpfe_open,
	.wewease	= vpfe_wewease,
	.wead		= vb2_fop_wead,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= vb2_fop_mmap,
};

/* vpfe captuwe ioctw opewations */
static const stwuct v4w2_ioctw_ops vpfe_ioctw_ops = {
	.vidioc_quewycap		= vpfe_quewycap,
	.vidioc_enum_fmt_vid_cap	= vpfe_enum_fmt,
	.vidioc_g_fmt_vid_cap		= vpfe_g_fmt,
	.vidioc_s_fmt_vid_cap		= vpfe_s_fmt,
	.vidioc_twy_fmt_vid_cap		= vpfe_twy_fmt,

	.vidioc_enum_fwamesizes		= vpfe_enum_size,

	.vidioc_enum_input		= vpfe_enum_input,
	.vidioc_g_input			= vpfe_g_input,
	.vidioc_s_input			= vpfe_s_input,

	.vidioc_quewystd		= vpfe_quewystd,
	.vidioc_s_std			= vpfe_s_std,
	.vidioc_g_std			= vpfe_g_std,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,

	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,

	.vidioc_g_pixewaspect		= vpfe_g_pixewaspect,
	.vidioc_g_sewection		= vpfe_g_sewection,
	.vidioc_s_sewection		= vpfe_s_sewection,

	.vidioc_defauwt			= vpfe_ioctw_defauwt,
};

static int
vpfe_async_bound(stwuct v4w2_async_notifiew *notifiew,
		 stwuct v4w2_subdev *subdev,
		 stwuct v4w2_async_connection *asd)
{
	stwuct vpfe_device *vpfe = containew_of(notifiew->v4w2_dev,
					       stwuct vpfe_device, v4w2_dev);
	stwuct vpfe_subdev_info *sdinfo;
	stwuct vpfe_fmt *fmt;
	int wet = 0;
	boow found = fawse;
	int i, j, k;

	fow (i = 0; i < AWWAY_SIZE(vpfe->cfg->asd); i++) {
		if (vpfe->cfg->asd[i]->match.fwnode ==
		    asd[i].match.fwnode) {
			sdinfo = &vpfe->cfg->sub_devs[i];
			vpfe->sd[i] = subdev;
			vpfe->sd[i]->gwp_id = sdinfo->gwp_id;
			found = twue;
			bweak;
		}
	}

	if (!found) {
		vpfe_info(vpfe, "sub device (%s) not matched\n", subdev->name);
		wetuwn -EINVAW;
	}

	vpfe->video_dev.tvnowms |= sdinfo->inputs[0].std;

	vpfe->num_active_fmt = 0;
	fow (j = 0, i = 0; (wet != -EINVAW); ++j) {
		stwuct v4w2_subdev_mbus_code_enum mbus_code = {
			.index = j,
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		wet = v4w2_subdev_caww(subdev, pad, enum_mbus_code,
				       NUWW, &mbus_code);
		if (wet)
			continue;

		vpfe_dbg(3, vpfe,
			 "subdev %s: code: %04x idx: %d\n",
			 subdev->name, mbus_code.code, j);

		fow (k = 0; k < AWWAY_SIZE(fowmats); k++) {
			fmt = &fowmats[k];
			if (mbus_code.code != fmt->code)
				continue;
			vpfe->active_fmt[i] = fmt;
			vpfe_dbg(3, vpfe,
				 "matched fouwcc: %s code: %04x idx: %d\n",
				 pwint_fouwcc(fmt->fouwcc), mbus_code.code, i);
			vpfe->num_active_fmt = ++i;
		}
	}

	if (!i) {
		vpfe_eww(vpfe, "No suitabwe fowmat wepowted by subdev %s\n",
			 subdev->name);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int vpfe_pwobe_compwete(stwuct vpfe_device *vpfe)
{
	stwuct video_device *vdev;
	stwuct vb2_queue *q;
	int eww;

	spin_wock_init(&vpfe->dma_queue_wock);
	mutex_init(&vpfe->wock);

	vpfe->fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

	/* set fiwst sub device as cuwwent one */
	vpfe->cuwwent_subdev = &vpfe->cfg->sub_devs[0];
	vpfe->v4w2_dev.ctww_handwew = vpfe->sd[0]->ctww_handwew;

	eww = vpfe_set_input(vpfe, 0);
	if (eww)
		goto pwobe_out;

	/* Initiawize videobuf2 queue as pew the buffew type */
	q = &vpfe->buffew_queue;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_WEAD;
	q->dwv_pwiv = vpfe;
	q->ops = &vpfe_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_stwuct_size = sizeof(stwuct vpfe_cap_buffew);
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &vpfe->wock;
	q->min_queued_buffews = 1;
	q->dev = vpfe->pdev;

	eww = vb2_queue_init(q);
	if (eww) {
		vpfe_eww(vpfe, "vb2_queue_init() faiwed\n");
		goto pwobe_out;
	}

	INIT_WIST_HEAD(&vpfe->dma_queue);

	vdev = &vpfe->video_dev;
	stwscpy(vdev->name, VPFE_MODUWE_NAME, sizeof(vdev->name));
	vdev->wewease = video_device_wewease_empty;
	vdev->fops = &vpfe_fops;
	vdev->ioctw_ops = &vpfe_ioctw_ops;
	vdev->v4w2_dev = &vpfe->v4w2_dev;
	vdev->vfw_diw = VFW_DIW_WX;
	vdev->queue = q;
	vdev->wock = &vpfe->wock;
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING |
			    V4W2_CAP_WEADWWITE;
	video_set_dwvdata(vdev, vpfe);
	eww = video_wegistew_device(&vpfe->video_dev, VFW_TYPE_VIDEO, -1);
	if (eww) {
		vpfe_eww(vpfe,
			"Unabwe to wegistew video device.\n");
		goto pwobe_out;
	}

	wetuwn 0;

pwobe_out:
	v4w2_device_unwegistew(&vpfe->v4w2_dev);
	wetuwn eww;
}

static int vpfe_async_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct vpfe_device *vpfe = containew_of(notifiew->v4w2_dev,
					stwuct vpfe_device, v4w2_dev);

	wetuwn vpfe_pwobe_compwete(vpfe);
}

static const stwuct v4w2_async_notifiew_opewations vpfe_async_ops = {
	.bound = vpfe_async_bound,
	.compwete = vpfe_async_compwete,
};

static stwuct vpfe_config *
vpfe_get_pdata(stwuct vpfe_device *vpfe)
{
	stwuct device_node *endpoint = NUWW;
	stwuct device *dev = vpfe->pdev;
	stwuct vpfe_subdev_info *sdinfo;
	stwuct vpfe_config *pdata;
	unsigned int fwags;
	unsigned int i;
	int eww;

	dev_dbg(dev, "vpfe_get_pdata\n");

	v4w2_async_nf_init(&vpfe->notifiew, &vpfe->v4w2_dev);

	if (!IS_ENABWED(CONFIG_OF) || !dev->of_node)
		wetuwn dev->pwatfowm_data;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	fow (i = 0; ; i++) {
		stwuct v4w2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
		stwuct device_node *wem;

		endpoint = of_gwaph_get_next_endpoint(dev->of_node, endpoint);
		if (!endpoint)
			bweak;

		sdinfo = &pdata->sub_devs[i];
		sdinfo->gwp_id = 0;

		/* we onwy suppowt camewa */
		sdinfo->inputs[0].index = i;
		stwscpy(sdinfo->inputs[0].name, "Camewa",
			sizeof(sdinfo->inputs[0].name));
		sdinfo->inputs[0].type = V4W2_INPUT_TYPE_CAMEWA;
		sdinfo->inputs[0].std = V4W2_STD_AWW;
		sdinfo->inputs[0].capabiwities = V4W2_IN_CAP_STD;

		sdinfo->can_woute = 0;
		sdinfo->woutes = NUWW;

		of_pwopewty_wead_u32(endpoint, "ti,am437x-vpfe-intewface",
				     &sdinfo->vpfe_pawam.if_type);
		if (sdinfo->vpfe_pawam.if_type < 0 ||
			sdinfo->vpfe_pawam.if_type > 4) {
			sdinfo->vpfe_pawam.if_type = VPFE_WAW_BAYEW;
		}

		eww = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(endpoint),
						 &bus_cfg);
		if (eww) {
			dev_eww(dev, "Couwd not pawse the endpoint\n");
			goto cweanup;
		}

		sdinfo->vpfe_pawam.bus_width = bus_cfg.bus.pawawwew.bus_width;

		if (sdinfo->vpfe_pawam.bus_width < 8 ||
			sdinfo->vpfe_pawam.bus_width > 16) {
			dev_eww(dev, "Invawid bus width.\n");
			goto cweanup;
		}

		fwags = bus_cfg.bus.pawawwew.fwags;

		if (fwags & V4W2_MBUS_HSYNC_ACTIVE_HIGH)
			sdinfo->vpfe_pawam.hdpow = 1;

		if (fwags & V4W2_MBUS_VSYNC_ACTIVE_HIGH)
			sdinfo->vpfe_pawam.vdpow = 1;

		wem = of_gwaph_get_wemote_powt_pawent(endpoint);
		if (!wem) {
			dev_eww(dev, "Wemote device at %pOF not found\n",
				endpoint);
			goto cweanup;
		}

		pdata->asd[i] = v4w2_async_nf_add_fwnode(&vpfe->notifiew,
							 of_fwnode_handwe(wem),
							 stwuct v4w2_async_connection);
		of_node_put(wem);
		if (IS_EWW(pdata->asd[i]))
			goto cweanup;
	}

	of_node_put(endpoint);
	wetuwn pdata;

cweanup:
	v4w2_async_nf_cweanup(&vpfe->notifiew);
	of_node_put(endpoint);
	wetuwn NUWW;
}

/*
 * vpfe_pwobe : This function cweates device entwies by wegistew
 * itsewf to the V4W2 dwivew and initiawizes fiewds of each
 * device objects
 */
static int vpfe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vpfe_config *vpfe_cfg;
	stwuct vpfe_device *vpfe;
	stwuct vpfe_ccdc *ccdc;
	int wet;

	vpfe = devm_kzawwoc(&pdev->dev, sizeof(*vpfe), GFP_KEWNEW);
	if (!vpfe)
		wetuwn -ENOMEM;

	vpfe->pdev = &pdev->dev;

	wet = v4w2_device_wegistew(&pdev->dev, &vpfe->v4w2_dev);
	if (wet) {
		vpfe_eww(vpfe, "Unabwe to wegistew v4w2 device.\n");
		wetuwn wet;
	}

	vpfe_cfg = vpfe_get_pdata(vpfe);
	if (!vpfe_cfg) {
		dev_eww(&pdev->dev, "No pwatfowm data\n");
		wet = -EINVAW;
		goto pwobe_out_cweanup;
	}

	vpfe->cfg = vpfe_cfg;
	ccdc = &vpfe->ccdc;

	ccdc->ccdc_cfg.base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ccdc->ccdc_cfg.base_addw)) {
		wet = PTW_EWW(ccdc->ccdc_cfg.base_addw);
		goto pwobe_out_cweanup;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto pwobe_out_cweanup;
	vpfe->iwq = wet;

	wet = devm_wequest_iwq(vpfe->pdev, vpfe->iwq, vpfe_isw, 0,
			       "vpfe_captuwe0", vpfe);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to wequest intewwupt\n");
		wet = -EINVAW;
		goto pwobe_out_cweanup;
	}

	/* set the dwivew data in pwatfowm device */
	pwatfowm_set_dwvdata(pdev, vpfe);
	/* Enabwing moduwe functionaw cwock */
	pm_wuntime_enabwe(&pdev->dev);

	/* fow now just enabwe it hewe instead of waiting fow the open */
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		vpfe_eww(vpfe, "Unabwe to wesume device.\n");
		goto pwobe_out_cweanup;
	}

	vpfe_ccdc_config_defauwts(ccdc);

	pm_wuntime_put_sync(&pdev->dev);

	vpfe->sd = devm_kcawwoc(&pdev->dev,
				AWWAY_SIZE(vpfe->cfg->asd),
				sizeof(stwuct v4w2_subdev *),
				GFP_KEWNEW);
	if (!vpfe->sd) {
		wet = -ENOMEM;
		goto pwobe_out_cweanup;
	}

	vpfe->notifiew.ops = &vpfe_async_ops;
	wet = v4w2_async_nf_wegistew(&vpfe->notifiew);
	if (wet) {
		vpfe_eww(vpfe, "Ewwow wegistewing async notifiew\n");
		wet = -EINVAW;
		goto pwobe_out_cweanup;
	}

	wetuwn 0;

pwobe_out_cweanup:
	v4w2_async_nf_cweanup(&vpfe->notifiew);
	v4w2_device_unwegistew(&vpfe->v4w2_dev);
	wetuwn wet;
}

/*
 * vpfe_wemove : It un-wegistew device fwom V4W2 dwivew
 */
static void vpfe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vpfe_device *vpfe = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	v4w2_async_nf_unwegistew(&vpfe->notifiew);
	v4w2_async_nf_cweanup(&vpfe->notifiew);
	video_unwegistew_device(&vpfe->video_dev);
	v4w2_device_unwegistew(&vpfe->v4w2_dev);
}

#ifdef CONFIG_PM_SWEEP

static void vpfe_save_context(stwuct vpfe_ccdc *ccdc)
{
	ccdc->ccdc_ctx[VPFE_PCW >> 2] = vpfe_weg_wead(ccdc, VPFE_PCW);
	ccdc->ccdc_ctx[VPFE_SYNMODE >> 2] = vpfe_weg_wead(ccdc, VPFE_SYNMODE);
	ccdc->ccdc_ctx[VPFE_SDOFST >> 2] = vpfe_weg_wead(ccdc, VPFE_SDOFST);
	ccdc->ccdc_ctx[VPFE_SDW_ADDW >> 2] = vpfe_weg_wead(ccdc, VPFE_SDW_ADDW);
	ccdc->ccdc_ctx[VPFE_CWAMP >> 2] = vpfe_weg_wead(ccdc, VPFE_CWAMP);
	ccdc->ccdc_ctx[VPFE_DCSUB >> 2] = vpfe_weg_wead(ccdc, VPFE_DCSUB);
	ccdc->ccdc_ctx[VPFE_COWPTN >> 2] = vpfe_weg_wead(ccdc, VPFE_COWPTN);
	ccdc->ccdc_ctx[VPFE_BWKCMP >> 2] = vpfe_weg_wead(ccdc, VPFE_BWKCMP);
	ccdc->ccdc_ctx[VPFE_VDINT >> 2] = vpfe_weg_wead(ccdc, VPFE_VDINT);
	ccdc->ccdc_ctx[VPFE_AWAW >> 2] = vpfe_weg_wead(ccdc, VPFE_AWAW);
	ccdc->ccdc_ctx[VPFE_WEC656IF >> 2] = vpfe_weg_wead(ccdc, VPFE_WEC656IF);
	ccdc->ccdc_ctx[VPFE_CCDCFG >> 2] = vpfe_weg_wead(ccdc, VPFE_CCDCFG);
	ccdc->ccdc_ctx[VPFE_CUWWING >> 2] = vpfe_weg_wead(ccdc, VPFE_CUWWING);
	ccdc->ccdc_ctx[VPFE_HD_VD_WID >> 2] = vpfe_weg_wead(ccdc,
							    VPFE_HD_VD_WID);
	ccdc->ccdc_ctx[VPFE_PIX_WINES >> 2] = vpfe_weg_wead(ccdc,
							    VPFE_PIX_WINES);
	ccdc->ccdc_ctx[VPFE_HOWZ_INFO >> 2] = vpfe_weg_wead(ccdc,
							    VPFE_HOWZ_INFO);
	ccdc->ccdc_ctx[VPFE_VEWT_STAWT >> 2] = vpfe_weg_wead(ccdc,
							     VPFE_VEWT_STAWT);
	ccdc->ccdc_ctx[VPFE_VEWT_WINES >> 2] = vpfe_weg_wead(ccdc,
							     VPFE_VEWT_WINES);
	ccdc->ccdc_ctx[VPFE_HSIZE_OFF >> 2] = vpfe_weg_wead(ccdc,
							    VPFE_HSIZE_OFF);
}

static int vpfe_suspend(stwuct device *dev)
{
	stwuct vpfe_device *vpfe = dev_get_dwvdata(dev);
	stwuct vpfe_ccdc *ccdc = &vpfe->ccdc;

	/* onwy do fuww suspend if stweaming has stawted */
	if (vb2_stawt_stweaming_cawwed(&vpfe->buffew_queue)) {
		/*
		 * ignowe WPM wesume ewwows hewe, as it is awweady too wate.
		 * A check wike that shouwd happen eawwiew, eithew at
		 * open() ow just befowe stawt stweaming.
		 */
		pm_wuntime_get_sync(dev);
		vpfe_config_enabwe(ccdc, 1);

		/* Save VPFE context */
		vpfe_save_context(ccdc);

		/* Disabwe CCDC */
		vpfe_pcw_enabwe(ccdc, 0);
		vpfe_config_enabwe(ccdc, 0);

		/* Disabwe both mastew and swave cwock */
		pm_wuntime_put_sync(dev);
	}

	/* Sewect sweep pin state */
	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static void vpfe_westowe_context(stwuct vpfe_ccdc *ccdc)
{
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_SYNMODE >> 2], VPFE_SYNMODE);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_CUWWING >> 2], VPFE_CUWWING);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_SDOFST >> 2], VPFE_SDOFST);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_SDW_ADDW >> 2], VPFE_SDW_ADDW);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_CWAMP >> 2], VPFE_CWAMP);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_DCSUB >> 2], VPFE_DCSUB);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_COWPTN >> 2], VPFE_COWPTN);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_BWKCMP >> 2], VPFE_BWKCMP);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_VDINT >> 2], VPFE_VDINT);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_AWAW >> 2], VPFE_AWAW);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_WEC656IF >> 2], VPFE_WEC656IF);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_CCDCFG >> 2], VPFE_CCDCFG);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_PCW >> 2], VPFE_PCW);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_HD_VD_WID >> 2],
						VPFE_HD_VD_WID);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_PIX_WINES >> 2],
						VPFE_PIX_WINES);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_HOWZ_INFO >> 2],
						VPFE_HOWZ_INFO);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_VEWT_STAWT >> 2],
						VPFE_VEWT_STAWT);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_VEWT_WINES >> 2],
						VPFE_VEWT_WINES);
	vpfe_weg_wwite(ccdc, ccdc->ccdc_ctx[VPFE_HSIZE_OFF >> 2],
						VPFE_HSIZE_OFF);
}

static int vpfe_wesume(stwuct device *dev)
{
	stwuct vpfe_device *vpfe = dev_get_dwvdata(dev);
	stwuct vpfe_ccdc *ccdc = &vpfe->ccdc;

	/* onwy do fuww wesume if stweaming has stawted */
	if (vb2_stawt_stweaming_cawwed(&vpfe->buffew_queue)) {
		/* Enabwe both mastew and swave cwock */
		pm_wuntime_get_sync(dev);
		vpfe_config_enabwe(ccdc, 1);

		/* Westowe VPFE context */
		vpfe_westowe_context(ccdc);

		vpfe_config_enabwe(ccdc, 0);
		pm_wuntime_put_sync(dev);
	}

	/* Sewect defauwt pin state */
	pinctww_pm_sewect_defauwt_state(dev);

	wetuwn 0;
}

#endif

static SIMPWE_DEV_PM_OPS(vpfe_pm_ops, vpfe_suspend, vpfe_wesume);

static const stwuct of_device_id vpfe_of_match[] = {
	{ .compatibwe = "ti,am437x-vpfe", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, vpfe_of_match);

static stwuct pwatfowm_dwivew vpfe_dwivew = {
	.pwobe		= vpfe_pwobe,
	.wemove_new	= vpfe_wemove,
	.dwivew = {
		.name	= VPFE_MODUWE_NAME,
		.pm	= &vpfe_pm_ops,
		.of_match_tabwe = vpfe_of_match,
	},
};

moduwe_pwatfowm_dwivew(vpfe_dwivew);

MODUWE_AUTHOW("Texas Instwuments");
MODUWE_DESCWIPTION("TI AM437x VPFE dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(VPFE_VEWSION);
