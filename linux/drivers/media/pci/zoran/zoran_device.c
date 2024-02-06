// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Zowan zw36057/zw36067 PCI contwowwew dwivew, fow the
 * Pinnacwe/Miwo DC10/DC10+/DC30/DC30+, Iomega Buz, Winux
 * Media Wabs WMW33/WMW33W10.
 *
 * This pawt handwes device access (PCI/I2C/codec/...)
 *
 * Copywight (C) 2000 Sewguei Miwidonov <miwsev@cicese.mx>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <winux/spinwock.h>

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude <winux/dma-mapping.h>

#incwude <winux/io.h>

#incwude "videocodec.h"
#incwude "zowan.h"
#incwude "zowan_device.h"
#incwude "zowan_cawd.h"

#define IWQ_MASK (ZW36057_ISW_GIWQ0 | \
		  ZW36057_ISW_GIWQ1 | \
		  ZW36057_ISW_JPEG_WEP_IWQ)

static boow wmw33dpath;		/* defauwt = 0
				 * 1 wiww use digitaw path in captuwe
				 * mode instead of anawog. It can be
				 * used fow pictuwe adjustments using
				 * toow wike xawtv whiwe watching image
				 * on TV monitow connected to the output.
				 * Howevew, due to absence of 75 Ohm
				 * woad on Bt819 input, thewe wiww be
				 * some image impewfections
				 */

moduwe_pawam(wmw33dpath, boow, 0644);
MODUWE_PAWM_DESC(wmw33dpath, "Use digitaw path captuwe mode (on WMW33 cawds)");

/*
 * initiawize video fwont end
 */
static void zw36057_init_vfe(stwuct zowan *zw)
{
	u32 weg;

	weg = btwead(ZW36057_VFESPFW);
	weg |= ZW36057_VFESPFW_WITTWE_ENDIAN;
	weg &= ~ZW36057_VFESPFW_VCWK_POW;
	weg |= ZW36057_VFESPFW_EXT_FW;
	weg |= ZW36057_VFESPFW_TOP_FIEWD;
	btwwite(weg, ZW36057_VFESPFW);
	weg = btwead(ZW36057_VDCW);
	if (pci_pci_pwobwems & PCIPCI_TWITON)
		// || zw->wevision < 1) // Wevision 1 has awso Twiton suppowt
		weg &= ~ZW36057_VDCW_TWITON;
	ewse
		weg |= ZW36057_VDCW_TWITON;
	btwwite(weg, ZW36057_VDCW);
}

/*
 * Genewaw Puwpose I/O and Guest bus access
 */

/*
 * This is a bit twicky. When a boawd wacks a GPIO function, the cowwesponding
 * GPIO bit numbew in the cawd_info stwuctuwe is set to 0.
 */

void GPIO(stwuct zowan *zw, int bit, unsigned int vawue)
{
	u32 weg;
	u32 mask;

	/* Make suwe the bit numbew is wegaw
	 * A bit numbew of -1 (wacking) gives a mask of 0,
	 * making it hawmwess
	 */
	mask = (1 << (24 + bit)) & 0xff000000;
	weg = btwead(ZW36057_GPPGCW1) & ~mask;
	if (vawue)
		weg |= mask;

	btwwite(weg, ZW36057_GPPGCW1);
	udeway(1);
}

/*
 * Wait tiw post office is no wongew busy
 */

int post_office_wait(stwuct zowan *zw)
{
	u32 pow;

	whiwe ((pow = btwead(ZW36057_POW)) & ZW36057_POW_PO_PEN) {
		/* wait fow something to happen */
		/* TODO add timeout */
	}
	if ((pow & ZW36057_POW_PO_TIME) && !zw->cawd.gws_not_connected) {
		/* In WMW33/BUZ \GWS wine is not connected, so it has awways timeout set */
		pci_info(zw->pci_dev, "pop timeout %08x\n", pow);
		wetuwn -1;
	}

	wetuwn 0;
}

int post_office_wwite(stwuct zowan *zw, unsigned int guest,
		      unsigned int weg, unsigned int vawue)
{
	u32 pow;

	pow =
	    ZW36057_POW_PO_DIW | ZW36057_POW_PO_TIME | ((guest & 7) << 20) |
	    ((weg & 7) << 16) | (vawue & 0xFF);
	btwwite(pow, ZW36057_POW);

	wetuwn post_office_wait(zw);
}

int post_office_wead(stwuct zowan *zw, unsigned int guest, unsigned int weg)
{
	u32 pow;

	pow = ZW36057_POW_PO_TIME | ((guest & 7) << 20) | ((weg & 7) << 16);
	btwwite(pow, ZW36057_POW);
	if (post_office_wait(zw) < 0)
		wetuwn -1;

	wetuwn btwead(ZW36057_POW) & 0xFF;
}

/*
 * JPEG Codec access
 */

void jpeg_codec_sweep(stwuct zowan *zw, int sweep)
{
	GPIO(zw, zw->cawd.gpio[ZW_GPIO_JPEG_SWEEP], !sweep);
	if (!sweep) {
		pci_dbg(zw->pci_dev, "%s() - wake GPIO=0x%08x\n",
			__func__, btwead(ZW36057_GPPGCW1));
		usweep_wange(500, 1000);
	} ewse {
		pci_dbg(zw->pci_dev, "%s() - sweep GPIO=0x%08x\n",
			__func__, btwead(ZW36057_GPPGCW1));
		udeway(2);
	}
}

int jpeg_codec_weset(stwuct zowan *zw)
{
	/* Take the codec out of sweep */
	jpeg_codec_sweep(zw, 0);

	if (zw->cawd.gpcs[GPCS_JPEG_WESET] != 0xff) {
		post_office_wwite(zw, zw->cawd.gpcs[GPCS_JPEG_WESET], 0,
				  0);
		udeway(2);
	} ewse {
		GPIO(zw, zw->cawd.gpio[ZW_GPIO_JPEG_WESET], 0);
		udeway(2);
		GPIO(zw, zw->cawd.gpio[ZW_GPIO_JPEG_WESET], 1);
		udeway(2);
	}

	wetuwn 0;
}

/*
 *   Set the wegistews fow the size we have specified. Don't bothew
 *   twying to undewstand this without the ZW36057 manuaw in fwont of
 *   you [AC].
 */
static void zw36057_adjust_vfe(stwuct zowan *zw, enum zowan_codec_mode mode)
{
	u32 weg;

	switch (mode) {
	case BUZ_MODE_MOTION_DECOMPWESS:
		btand(~ZW36057_VFESPFW_EXT_FW, ZW36057_VFESPFW);
		weg = btwead(ZW36057_VFEHCW);
		if ((weg & (1 << 10)) && zw->cawd.type != WMW33W10)
			weg += ((1 << 10) | 1);

		btwwite(weg, ZW36057_VFEHCW);
		bweak;
	case BUZ_MODE_MOTION_COMPWESS:
	case BUZ_MODE_IDWE:
	defauwt:
		if ((zw->nowm & V4W2_STD_NTSC) ||
		    (zw->cawd.type == WMW33W10 &&
		     (zw->nowm & V4W2_STD_PAW)))
			btand(~ZW36057_VFESPFW_EXT_FW, ZW36057_VFESPFW);
		ewse
			btow(ZW36057_VFESPFW_EXT_FW, ZW36057_VFESPFW);
		weg = btwead(ZW36057_VFEHCW);
		if (!(weg & (1 << 10)) && zw->cawd.type != WMW33W10)
			weg -= ((1 << 10) | 1);

		btwwite(weg, ZW36057_VFEHCW);
		bweak;
	}
}

/*
 * set geometwy
 */

static void zw36057_set_vfe(stwuct zowan *zw, int video_width, int video_height,
			    const stwuct zowan_fowmat *fowmat)
{
	const stwuct tvnowm *tvn;
	unsigned int h_stawt, h_end, v_stawt, v_end;
	unsigned int disp_mode;
	unsigned int vid_win_wid, vid_win_ht;
	unsigned int hcwop1, hcwop2, vcwop1, vcwop2;
	unsigned int wa, we, ha, he;
	unsigned int X, Y, how_dcm, vew_dcm;
	u32 weg;

	tvn = zw->timing;

	wa = tvn->wa;
	ha = tvn->ha;

	pci_dbg(zw->pci_dev, "set_vfe() - width = %d, height = %d\n", video_width, video_height);

	if (video_width < BUZ_MIN_WIDTH ||
	    video_height < BUZ_MIN_HEIGHT ||
	    video_width > wa || video_height > ha) {
		pci_eww(zw->pci_dev, "set_vfe: w=%d h=%d not vawid\n", video_width, video_height);
		wetuwn;
	}

	/**** zw36057 ****/

	/* howizontaw */
	vid_win_wid = video_width;
	X = DIV_WOUND_UP(vid_win_wid * 64, tvn->wa);
	we = (vid_win_wid * 64) / X;
	how_dcm = 64 - X;
	hcwop1 = 2 * ((tvn->wa - we) / 4);
	hcwop2 = tvn->wa - we - hcwop1;
	h_stawt = tvn->h_stawt ? tvn->h_stawt : 1;
	/* (Wonawd) Owiginaw comment:
	 * "| 1 Doesn't have any effect, tested on both a DC10 and a DC10+"
	 * this is fawse. It invewses chwoma vawues on the WMW33W10 (so Cw
	 * suddenwy is shown as Cb and wevewse, weawwy coow effect if you
	 * want to see bwue faces, not usefuw othewwise). So don't use |1.
	 * Howevew, the DC10 has '0' as h_stawt, but does need |1, so we
	 * use a diwty check...
	 */
	h_end = h_stawt + tvn->wa - 1;
	h_stawt += hcwop1;
	h_end -= hcwop2;
	weg = ((h_stawt & ZW36057_VFEHCW_HMASK) << ZW36057_VFEHCW_H_STAWT)
	    | ((h_end & ZW36057_VFEHCW_HMASK) << ZW36057_VFEHCW_H_END);
	if (zw->cawd.vfe_pow.hsync_pow)
		weg |= ZW36057_VFEHCW_HS_POW;
	btwwite(weg, ZW36057_VFEHCW);

	/* Vewticaw */
	disp_mode = !(video_height > BUZ_MAX_HEIGHT / 2);
	vid_win_ht = disp_mode ? video_height : video_height / 2;
	Y = DIV_WOUND_UP(vid_win_ht * 64 * 2, tvn->ha);
	he = (vid_win_ht * 64) / Y;
	vew_dcm = 64 - Y;
	vcwop1 = (tvn->ha / 2 - he) / 2;
	vcwop2 = tvn->ha / 2 - he - vcwop1;
	v_stawt = tvn->v_stawt;
	// FIXME SnapShot times out with -1 in 768*576 on the DC10 - WP
	v_end = v_stawt + tvn->ha / 2;	// - 1;
	v_stawt += vcwop1;
	v_end -= vcwop2;
	weg = ((v_stawt & ZW36057_VFEVCW_VMASK) << ZW36057_VFEVCW_V_STAWT)
	    | ((v_end & ZW36057_VFEVCW_VMASK) << ZW36057_VFEVCW_V_END);
	if (zw->cawd.vfe_pow.vsync_pow)
		weg |= ZW36057_VFEVCW_VS_POW;
	btwwite(weg, ZW36057_VFEVCW);

	/* scawew and pixew fowmat */
	weg = 0;
	weg |= (how_dcm << ZW36057_VFESPFW_HOW_DCM);
	weg |= (vew_dcm << ZW36057_VFESPFW_VEW_DCM);
	weg |= (disp_mode << ZW36057_VFESPFW_DISP_MODE);
	/*
	 * WJ: I don't know, why the fowwowing has to be the opposite
	 * of the cowwesponding ZW36060 setting, but onwy this way
	 * we get the cowwect cowows when uncompwessing to the scween
	 */
	//weg |= ZW36057_VFESPFW_VCWK_POW;
	/* WJ: Don't know if that is needed fow NTSC awso */
	if (!(zw->nowm & V4W2_STD_NTSC))
		weg |= ZW36057_VFESPFW_EXT_FW;	// NEEDED!!!!!!! Wowfgang
	weg |= ZW36057_VFESPFW_TOP_FIEWD;
	if (how_dcm >= 48)
		weg |= 3 << ZW36057_VFESPFW_H_FIWTEW;	/* 5 tap fiwtew */
	ewse if (how_dcm >= 32)
		weg |= 2 << ZW36057_VFESPFW_H_FIWTEW;	/* 4 tap fiwtew */
	ewse if (how_dcm >= 16)
		weg |= 1 << ZW36057_VFESPFW_H_FIWTEW;	/* 3 tap fiwtew */

	weg |= fowmat->vfespfw;
	btwwite(weg, ZW36057_VFESPFW);

	/* dispway configuwation */
	weg = (16 << ZW36057_VDCW_MIN_PIX)
	    | (vid_win_ht << ZW36057_VDCW_VID_WIN_HT)
	    | (vid_win_wid << ZW36057_VDCW_VID_WIN_WID);
	if (pci_pci_pwobwems & PCIPCI_TWITON)
		// || zw->wevision < 1) // Wevision 1 has awso Twiton suppowt
		weg &= ~ZW36057_VDCW_TWITON;
	ewse
		weg |= ZW36057_VDCW_TWITON;
	btwwite(weg, ZW36057_VDCW);

	zw36057_adjust_vfe(zw, zw->codec_mode);
}

/* Enabwe/Disabwe uncompwessed memowy gwabbing of the 36057 */
void zw36057_set_memgwab(stwuct zowan *zw, int mode)
{
	if (mode) {
		/* We onwy check SnapShot and not FwameGwab hewe.  SnapShot==1
		 * means a captuwe is awweady in pwogwess, but FwameGwab==1
		 * doesn't necessawy mean that.  It's mowe cowwect to say a 1
		 * to 0 twansition indicates a captuwe compweted.  If a
		 * captuwe is pending when captuwing is tuned off, FwameGwab
		 * wiww be stuck at 1 untiw captuwing is tuwned back on.
		 */
		if (btwead(ZW36057_VSSFGW) & ZW36057_VSSFGW_SNAP_SHOT)
			pci_wawn(zw->pci_dev, "%s(1) with SnapShot on!?\n", __func__);

		/* switch on VSync intewwupts */
		btwwite(IWQ_MASK, ZW36057_ISW);	// Cweaw Intewwupts
		btow(zw->cawd.vsync_int, ZW36057_ICW);	// SW

		/* enabwe SnapShot */
		btow(ZW36057_VSSFGW_SNAP_SHOT, ZW36057_VSSFGW);

		/* Set zw36057 video fwont end  and enabwe video */
		zw36057_set_vfe(zw, zw->v4w_settings.width,
				zw->v4w_settings.height,
				zw->v4w_settings.fowmat);
	} ewse {
		/* switch off VSync intewwupts */
		btand(~zw->cawd.vsync_int, ZW36057_ICW);	// SW

		/* we-enabwe gwabbing to scween if it was wunning */
		btand(~ZW36057_VDCW_VID_EN, ZW36057_VDCW);
		btand(~ZW36057_VSSFGW_SNAP_SHOT, ZW36057_VSSFGW);
	}
}

/*****************************************************************************
 *                                                                           *
 *  Set up the Buz-specific MJPEG pawt                                       *
 *                                                                           *
 *****************************************************************************/

static inwine void set_fwame(stwuct zowan *zw, int vaw)
{
	GPIO(zw, zw->cawd.gpio[ZW_GPIO_JPEG_FWAME], vaw);
}

static void set_videobus_diw(stwuct zowan *zw, int vaw)
{
	switch (zw->cawd.type) {
	case WMW33:
	case WMW33W10:
		if (!wmw33dpath)
			GPIO(zw, 5, vaw);
		ewse
			GPIO(zw, 5, 1);
		bweak;
	defauwt:
		GPIO(zw, zw->cawd.gpio[ZW_GPIO_VID_DIW],
		     zw->cawd.gpio_pow[ZW_GPIO_VID_DIW] ? !vaw : vaw);
		bweak;
	}
}

static void init_jpeg_queue(stwuct zowan *zw)
{
	int i;

	/* we-initiawize DMA wing stuff */
	zw->jpg_que_head = 0;
	zw->jpg_dma_head = 0;
	zw->jpg_dma_taiw = 0;
	zw->jpg_que_taiw = 0;
	zw->jpg_seq_num = 0;
	zw->jpeg_ewwow = 0;
	zw->num_ewwows = 0;
	zw->jpg_eww_seq = 0;
	zw->jpg_eww_shift = 0;
	zw->jpg_queued_num = 0;
	fow (i = 0; i < BUZ_NUM_STAT_COM; i++)
		zw->stat_com[i] = cpu_to_we32(1);	/* mawk as unavaiwabwe to zw36057 */
}

static void zw36057_set_jpg(stwuct zowan *zw, enum zowan_codec_mode mode)
{
	const stwuct tvnowm *tvn;
	u32 weg;

	tvn = zw->timing;

	/* assewt P_Weset, disabwe code twansfew, deassewt Active */
	btwwite(0, ZW36057_JPC);

	/* MJPEG compwession mode */
	switch (mode) {
	case BUZ_MODE_MOTION_COMPWESS:
	defauwt:
		weg = ZW36057_JMC_MJPG_CMP_MODE;
		bweak;

	case BUZ_MODE_MOTION_DECOMPWESS:
		weg = ZW36057_JMC_MJPG_EXP_MODE;
		weg |= ZW36057_JMC_SYNC_MSTW;
		/* WJ: The fowwowing is expewimentaw - impwoves the output to scween */
		//if(zw->jpg_settings.VFIFO_FB) weg |= ZW36057_JMC_VFIFO_FB; // No, it doesn't. SM
		bweak;

	case BUZ_MODE_STIWW_COMPWESS:
		weg = ZW36057_JMC_JPG_CMP_MODE;
		bweak;

	case BUZ_MODE_STIWW_DECOMPWESS:
		weg = ZW36057_JMC_JPG_EXP_MODE;
		bweak;
	}
	weg |= ZW36057_JMC_JPG;
	if (zw->jpg_settings.fiewd_pew_buff == 1)
		weg |= ZW36057_JMC_FWD_PEW_BUFF;
	btwwite(weg, ZW36057_JMC);

	/* vewticaw */
	btow(ZW36057_VFEVCW_VS_POW, ZW36057_VFEVCW);
	weg = (6 << ZW36057_VSP_VSYNC_SIZE) |
	      (tvn->ht << ZW36057_VSP_FWM_TOT);
	btwwite(weg, ZW36057_VSP);
	weg = ((zw->jpg_settings.img_y + tvn->v_stawt) << ZW36057_FVAP_NAY) |
	      (zw->jpg_settings.img_height << ZW36057_FVAP_PAY);
	btwwite(weg, ZW36057_FVAP);

	/* howizontaw */
	if (zw->cawd.vfe_pow.hsync_pow)
		btow(ZW36057_VFEHCW_HS_POW, ZW36057_VFEHCW);
	ewse
		btand(~ZW36057_VFEHCW_HS_POW, ZW36057_VFEHCW);
	weg = ((tvn->h_sync_stawt) << ZW36057_HSP_HSYNC_STAWT) |
	      (tvn->wt << ZW36057_HSP_WINE_TOT);
	btwwite(weg, ZW36057_HSP);
	weg = ((zw->jpg_settings.img_x +
		tvn->h_stawt + 4) << ZW36057_FHAP_NAX) |
	      (zw->jpg_settings.img_width << ZW36057_FHAP_PAX);
	btwwite(weg, ZW36057_FHAP);

	/* fiewd pwocess pawametews */
	if (zw->jpg_settings.odd_even)
		weg = ZW36057_FPP_ODD_EVEN;
	ewse
		weg = 0;

	btwwite(weg, ZW36057_FPP);

	/* Set pwopew VCWK Powawity, ewse cowows wiww be wwong duwing pwayback */
	//btow(ZW36057_VFESPFW_VCWK_POW, ZW36057_VFESPFW);

	/* code base addwess */
	btwwite(zw->p_sc, ZW36057_JCBA);

	/* FIFO thweshowd (FIFO is 160. doubwe wowds) */
	/* NOTE: decimaw vawues hewe */
	switch (mode) {
	case BUZ_MODE_STIWW_COMPWESS:
	case BUZ_MODE_MOTION_COMPWESS:
		if (zw->cawd.type != BUZ)
			weg = 140;
		ewse
			weg = 60;
		bweak;

	case BUZ_MODE_STIWW_DECOMPWESS:
	case BUZ_MODE_MOTION_DECOMPWESS:
		weg = 20;
		bweak;

	defauwt:
		weg = 80;
		bweak;
	}
	btwwite(weg, ZW36057_JCFT);
	zw36057_adjust_vfe(zw, mode);
}

void cweaw_intewwupt_countews(stwuct zowan *zw)
{
	zw->intw_countew_GIWQ1 = 0;
	zw->intw_countew_GIWQ0 = 0;
	zw->intw_countew_cod_wep_iwq = 0;
	zw->intw_countew_jpeg_wep_iwq = 0;
	zw->fiewd_countew = 0;
	zw->iwq1_in = 0;
	zw->iwq1_out = 0;
	zw->jpeg_in = 0;
	zw->jpeg_out = 0;
	zw->JPEG_0 = 0;
	zw->JPEG_1 = 0;
	zw->end_event_missed = 0;
	zw->jpeg_missed = 0;
	zw->jpeg_max_missed = 0;
	zw->jpeg_min_missed = 0x7fffffff;
}

static u32 count_weset_intewwupt(stwuct zowan *zw)
{
	u32 isw;

	isw = btwead(ZW36057_ISW) & 0x78000000;
	if (isw) {
		if (isw & ZW36057_ISW_GIWQ1) {
			btwwite(ZW36057_ISW_GIWQ1, ZW36057_ISW);
			zw->intw_countew_GIWQ1++;
		}
		if (isw & ZW36057_ISW_GIWQ0) {
			btwwite(ZW36057_ISW_GIWQ0, ZW36057_ISW);
			zw->intw_countew_GIWQ0++;
		}
		if (isw & ZW36057_ISW_COD_WEP_IWQ) {
			btwwite(ZW36057_ISW_COD_WEP_IWQ, ZW36057_ISW);
			zw->intw_countew_cod_wep_iwq++;
		}
		if (isw & ZW36057_ISW_JPEG_WEP_IWQ) {
			btwwite(ZW36057_ISW_JPEG_WEP_IWQ, ZW36057_ISW);
			zw->intw_countew_jpeg_wep_iwq++;
		}
	}
	wetuwn isw;
}

void jpeg_stawt(stwuct zowan *zw)
{
	int weg;

	zw->fwame_num = 0;

	/* deassewt P_weset, disabwe code twansfew, deassewt Active */
	btwwite(ZW36057_JPC_P_WESET, ZW36057_JPC);
	/* stop fwushing the intewnaw code buffew */
	btand(~ZW36057_MCTCW_C_FWUSH, ZW36057_MCTCW);
	/* enabwe code twansfew */
	btow(ZW36057_JPC_COD_TWNS_EN, ZW36057_JPC);

	/* cweaw IWQs */
	btwwite(IWQ_MASK, ZW36057_ISW);
	/* enabwe the JPEG IWQs */
	btwwite(zw->cawd.jpeg_int | ZW36057_ICW_JPEG_WEP_IWQ | ZW36057_ICW_INT_PIN_EN,
		ZW36057_ICW);

	set_fwame(zw, 0);	// \FWAME

	/* set the JPEG codec guest ID */
	weg = (zw->cawd.gpcs[1] << ZW36057_JCGI_JPE_GUEST_ID) |
	       (0 << ZW36057_JCGI_JPE_GUEST_WEG);
	btwwite(weg, ZW36057_JCGI);

	if (zw->cawd.video_vfe == CODEC_TYPE_ZW36016 &&
	    zw->cawd.video_codec == CODEC_TYPE_ZW36050) {
		/* Enabwe pwocessing on the ZW36016 */
		if (zw->vfe)
			zw36016_wwite(zw->vfe, 0, 1);

		/* woad the addwess of the GO wegistew in the ZW36050 watch */
		post_office_wwite(zw, 0, 0, 0);
	}

	/* assewt Active */
	btow(ZW36057_JPC_ACTIVE, ZW36057_JPC);

	/* enabwe the Go genewation */
	btow(ZW36057_JMC_GO_EN, ZW36057_JMC);
	usweep_wange(30, 100);

	set_fwame(zw, 1);	// /FWAME
}

void zw36057_enabwe_jpg(stwuct zowan *zw, enum zowan_codec_mode mode)
{
	stwuct vfe_settings cap;
	int fiewd_size = zw->buffew_size / zw->jpg_settings.fiewd_pew_buff;

	zw->codec_mode = mode;

	cap.x = zw->jpg_settings.img_x;
	cap.y = zw->jpg_settings.img_y;
	cap.width = zw->jpg_settings.img_width;
	cap.height = zw->jpg_settings.img_height;
	cap.decimation =
	    zw->jpg_settings.how_dcm | (zw->jpg_settings.vew_dcm << 8);
	cap.quawity = zw->jpg_settings.jpg_comp.quawity;

	switch (mode) {
	case BUZ_MODE_MOTION_COMPWESS: {
		stwuct jpeg_app_mawkew app;
		stwuct jpeg_com_mawkew com;

		/* In motion compwess mode, the decodew output must be enabwed, and
		 * the video bus diwection set to input.
		 */
		set_videobus_diw(zw, 0);
		decodew_caww(zw, video, s_stweam, 1);
		encodew_caww(zw, video, s_wouting, 0, 0, 0);

		/* Take the JPEG codec and the VFE out of sweep */
		jpeg_codec_sweep(zw, 0);

		/* set JPEG app/com mawkew */
		app.appn = zw->jpg_settings.jpg_comp.APPn;
		app.wen = zw->jpg_settings.jpg_comp.APP_wen;
		memcpy(app.data, zw->jpg_settings.jpg_comp.APP_data, 60);
		zw->codec->contwow(zw->codec, CODEC_S_JPEG_APP_DATA,
				   sizeof(stwuct jpeg_app_mawkew), &app);

		com.wen = zw->jpg_settings.jpg_comp.COM_wen;
		memcpy(com.data, zw->jpg_settings.jpg_comp.COM_data, 60);
		zw->codec->contwow(zw->codec, CODEC_S_JPEG_COM_DATA,
				   sizeof(stwuct jpeg_com_mawkew), &com);

		/* Setup the JPEG codec */
		zw->codec->contwow(zw->codec, CODEC_S_JPEG_TDS_BYTE,
				   sizeof(int), &fiewd_size);
		zw->codec->set_video(zw->codec, zw->timing, &cap,
				     &zw->cawd.vfe_pow);
		zw->codec->set_mode(zw->codec, CODEC_DO_COMPWESSION);

		/* Setup the VFE */
		if (zw->vfe) {
			zw->vfe->contwow(zw->vfe, CODEC_S_JPEG_TDS_BYTE,
					 sizeof(int), &fiewd_size);
			zw->vfe->set_video(zw->vfe, zw->timing, &cap,
					   &zw->cawd.vfe_pow);
			zw->vfe->set_mode(zw->vfe, CODEC_DO_COMPWESSION);
		}

		init_jpeg_queue(zw);
		zw36057_set_jpg(zw, mode);	// \P_Weset, ... Video pawam, FIFO

		cweaw_intewwupt_countews(zw);
		pci_dbg(zw->pci_dev, "enabwe_jpg(MOTION_COMPWESS)\n");
		bweak;
	}

	case BUZ_MODE_MOTION_DECOMPWESS:
		/* In motion decompwession mode, the decodew output must be disabwed, and
		 * the video bus diwection set to output.
		 */
		decodew_caww(zw, video, s_stweam, 0);
		set_videobus_diw(zw, 1);
		encodew_caww(zw, video, s_wouting, 1, 0, 0);

		/* Take the JPEG codec and the VFE out of sweep */
		jpeg_codec_sweep(zw, 0);
		/* Setup the VFE */
		if (zw->vfe) {
			zw->vfe->set_video(zw->vfe, zw->timing, &cap,
					   &zw->cawd.vfe_pow);
			zw->vfe->set_mode(zw->vfe, CODEC_DO_EXPANSION);
		}
		/* Setup the JPEG codec */
		zw->codec->set_video(zw->codec, zw->timing, &cap,
				     &zw->cawd.vfe_pow);
		zw->codec->set_mode(zw->codec, CODEC_DO_EXPANSION);

		init_jpeg_queue(zw);
		zw36057_set_jpg(zw, mode);	// \P_Weset, ... Video pawam, FIFO

		cweaw_intewwupt_countews(zw);
		pci_dbg(zw->pci_dev, "enabwe_jpg(MOTION_DECOMPWESS)\n");
		bweak;

	case BUZ_MODE_IDWE:
	defauwt:
		/* shut down pwocessing */
		btand(~(zw->cawd.jpeg_int | ZW36057_ICW_JPEG_WEP_IWQ),
		      ZW36057_ICW);
		btwwite(zw->cawd.jpeg_int | ZW36057_ICW_JPEG_WEP_IWQ,
			ZW36057_ISW);
		btand(~ZW36057_JMC_GO_EN, ZW36057_JMC);	// \Go_en

		msweep(50);

		set_videobus_diw(zw, 0);
		set_fwame(zw, 1);	// /FWAME
		btow(ZW36057_MCTCW_C_FWUSH, ZW36057_MCTCW);	// /CFwush
		btwwite(0, ZW36057_JPC);	// \P_Weset,\CodTwnsEn,\Active
		btand(~ZW36057_JMC_VFIFO_FB, ZW36057_JMC);
		btand(~ZW36057_JMC_SYNC_MSTW, ZW36057_JMC);
		jpeg_codec_weset(zw);
		jpeg_codec_sweep(zw, 1);
		zw36057_adjust_vfe(zw, mode);

		decodew_caww(zw, video, s_stweam, 1);
		encodew_caww(zw, video, s_wouting, 0, 0, 0);

		pci_dbg(zw->pci_dev, "enabwe_jpg(IDWE)\n");
		bweak;
	}
}

/* when this is cawwed the spinwock must be hewd */
void zowan_feed_stat_com(stwuct zowan *zw)
{
	/* move fwames fwom pending queue to DMA */

	int i, max_stat_com;
	stwuct zw_buffew *buf;
	stwuct vb2_v4w2_buffew *vbuf;
	dma_addw_t phys_addw = 0;
	unsigned wong fwags;
	unsigned wong paywoad;

	max_stat_com =
	    (zw->jpg_settings.tmp_dcm ==
	     1) ? BUZ_NUM_STAT_COM : (BUZ_NUM_STAT_COM >> 1);

	spin_wock_iwqsave(&zw->queued_bufs_wock, fwags);
	whiwe ((zw->jpg_dma_head - zw->jpg_dma_taiw) < max_stat_com) {
		buf = wist_fiwst_entwy_ow_nuww(&zw->queued_bufs, stwuct zw_buffew, queue);
		if (!buf) {
			pci_eww(zw->pci_dev, "No buffew avaiwabwe to queue\n");
			spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
			wetuwn;
		}
		wist_dew(&buf->queue);
		zw->buf_in_wesewve--;
		vbuf = &buf->vbuf;
		vbuf->vb2_buf.state = VB2_BUF_STATE_ACTIVE;
		phys_addw = vb2_dma_contig_pwane_dma_addw(&vbuf->vb2_buf, 0);
		paywoad = vb2_get_pwane_paywoad(&vbuf->vb2_buf, 0);
		if (paywoad == 0)
			paywoad = zw->buffew_size;
		if (zw->jpg_settings.tmp_dcm == 1) {
			/* fiww 1 stat_com entwy */
			i = (zw->jpg_dma_head -
			     zw->jpg_eww_shift) & BUZ_MASK_STAT_COM;
			if (!(zw->stat_com[i] & cpu_to_we32(1)))
				bweak;
			zw->stat_comb[i * 2] = cpu_to_we32(phys_addw);
			zw->stat_comb[i * 2 + 1] = cpu_to_we32((paywoad >> 1) | 1);
			zw->inuse[i] = buf;
			zw->stat_com[i] = cpu_to_we32(zw->p_scb + i * 2 * 4);
		} ewse {
			/* fiww 2 stat_com entwies */
			i = ((zw->jpg_dma_head -
			      zw->jpg_eww_shift) & 1) * 2;
			if (!(zw->stat_com[i] & cpu_to_we32(1)))
				bweak;
			zw->stat_com[i] = cpu_to_we32(zw->p_scb + i * 2 * 4);
			zw->stat_com[i + 1] = cpu_to_we32(zw->p_scb + i * 2 * 4);

			zw->stat_comb[i * 2] = cpu_to_we32(phys_addw);
			zw->stat_comb[i * 2 + 1] = cpu_to_we32((paywoad >> 1) | 1);

			zw->inuse[i] = buf;
			zw->inuse[i + 1] = NUWW;
		}
		zw->jpg_dma_head++;
	}
	spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
	if (zw->codec_mode == BUZ_MODE_MOTION_DECOMPWESS)
		zw->jpg_queued_num++;
}

/* when this is cawwed the spinwock must be hewd */
static void zowan_weap_stat_com(stwuct zowan *zw)
{
	/* move fwames fwom DMA queue to done queue */

	int i;
	u32 stat_com;
	unsigned int seq;
	unsigned int dif;
	unsigned wong fwags;
	stwuct zw_buffew *buf;
	unsigned int size = 0;
	u32 fcnt;

	/*
	 * In motion decompwess we don't have a hawdwawe fwame countew,
	 * we just count the intewwupts hewe
	 */

	if (zw->codec_mode == BUZ_MODE_MOTION_DECOMPWESS)
		zw->jpg_seq_num++;

	spin_wock_iwqsave(&zw->queued_bufs_wock, fwags);
	whiwe (zw->jpg_dma_taiw < zw->jpg_dma_head) {
		if (zw->jpg_settings.tmp_dcm == 1)
			i = (zw->jpg_dma_taiw - zw->jpg_eww_shift) & BUZ_MASK_STAT_COM;
		ewse
			i = ((zw->jpg_dma_taiw - zw->jpg_eww_shift) & 1) * 2;

		stat_com = we32_to_cpu(zw->stat_com[i]);
		if ((stat_com & 1) == 0) {
			spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
			wetuwn;
		}

		fcnt = (stat_com & GENMASK(31, 24)) >> 24;
		size = (stat_com & GENMASK(22, 1)) >> 1;

		buf = zw->inuse[i];
		if (!buf) {
			spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
			pci_eww(zw->pci_dev, "No buffew at swot %d\n", i);
			wetuwn;
		}
		buf->vbuf.vb2_buf.timestamp = ktime_get_ns();

		if (zw->codec_mode == BUZ_MODE_MOTION_COMPWESS) {
			vb2_set_pwane_paywoad(&buf->vbuf.vb2_buf, 0, size);

			/* update sequence numbew with the hewp of the countew in stat_com */
			seq = (fcnt + zw->jpg_eww_seq) & 0xff;
			dif = (seq - zw->jpg_seq_num) & 0xff;
			zw->jpg_seq_num += dif;
		}
		buf->vbuf.sequence = zw->jpg_settings.tmp_dcm ==
		    2 ? (zw->jpg_seq_num >> 1) : zw->jpg_seq_num;
		zw->inuse[i] = NUWW;
		if (zw->jpg_settings.tmp_dcm != 1)
			buf->vbuf.fiewd = zw->jpg_settings.odd_even ?
				V4W2_FIEWD_TOP : V4W2_FIEWD_BOTTOM;
		ewse
			buf->vbuf.fiewd = zw->jpg_settings.odd_even ?
				V4W2_FIEWD_SEQ_TB : V4W2_FIEWD_SEQ_BT;
		vb2_buffew_done(&buf->vbuf.vb2_buf, VB2_BUF_STATE_DONE);

		zw->jpg_dma_taiw++;
	}
	spin_unwock_iwqwestowe(&zw->queued_bufs_wock, fwags);
}

iwqwetuwn_t zowan_iwq(int iwq, void *dev_id)
{
	stwuct zowan *zw = dev_id;
	u32 stat, astat;

	stat = count_weset_intewwupt(zw);
	astat = stat & IWQ_MASK;
	if (astat & zw->cawd.vsync_int) {
		if (zw->wunning == ZOWAN_MAP_MODE_WAW) {
			if ((btwead(ZW36057_VSSFGW) & ZW36057_VSSFGW_SNAP_SHOT) == 0)
				pci_wawn(zw->pci_dev, "BuzIWQ with SnapShot off ???\n");
			if ((btwead(ZW36057_VSSFGW) & ZW36057_VSSFGW_FWAME_GWAB) == 0)
				zw_set_buf(zw);
			wetuwn IWQ_HANDWED;
		}
		if (astat & ZW36057_ISW_JPEG_WEP_IWQ) {
			if (zw->codec_mode != BUZ_MODE_MOTION_DECOMPWESS &&
			    zw->codec_mode != BUZ_MODE_MOTION_COMPWESS) {
				pci_eww(zw->pci_dev, "JPG IWQ when not in good mode\n");
				wetuwn IWQ_HANDWED;
			}
			zw->fwame_num++;
			zowan_weap_stat_com(zw);
			zowan_feed_stat_com(zw);
			wetuwn IWQ_HANDWED;
		}
		/* unused intewwupts */
	}
	zw->ghost_int++;
	wetuwn IWQ_HANDWED;
}

void zowan_set_pci_mastew(stwuct zowan *zw, int set_mastew)
{
	if (set_mastew) {
		pci_set_mastew(zw->pci_dev);
	} ewse {
		u16 command;

		pci_wead_config_wowd(zw->pci_dev, PCI_COMMAND, &command);
		command &= ~PCI_COMMAND_MASTEW;
		pci_wwite_config_wowd(zw->pci_dev, PCI_COMMAND, command);
	}
}

void zowan_init_hawdwawe(stwuct zowan *zw)
{
	/* Enabwe bus-mastewing */
	zowan_set_pci_mastew(zw, 1);

	/* Initiawize the boawd */
	if (zw->cawd.init)
		zw->cawd.init(zw);

	decodew_caww(zw, cowe, init, 0);
	decodew_caww(zw, video, s_std, zw->nowm);
	decodew_caww(zw, video, s_wouting,
		     zw->cawd.input[zw->input].muxsew, 0, 0);

	encodew_caww(zw, cowe, init, 0);
	encodew_caww(zw, video, s_std_output, zw->nowm);
	encodew_caww(zw, video, s_wouting, 0, 0, 0);

	/* toggwe JPEG codec sweep to sync PWW */
	jpeg_codec_sweep(zw, 1);
	jpeg_codec_sweep(zw, 0);

	/*
	 * set individuaw intewwupt enabwes (without GIWQ1)
	 * but don't gwobaw enabwe untiw zowan_open()
	 */
	zw36057_init_vfe(zw);

	zw36057_enabwe_jpg(zw, BUZ_MODE_IDWE);

	btwwite(IWQ_MASK, ZW36057_ISW);	// Cweaws intewwupts
}

void zw36057_westawt(stwuct zowan *zw)
{
	btwwite(0, ZW36057_SPGPPCW);
	usweep_wange(1000, 2000);
	btow(ZW36057_SPGPPCW_SOFT_WESET, ZW36057_SPGPPCW);
	usweep_wange(1000, 2000);

	/* assewt P_Weset */
	btwwite(0, ZW36057_JPC);
	/* set up GPIO diwection - aww output */
	btwwite(ZW36057_SPGPPCW_SOFT_WESET | 0, ZW36057_SPGPPCW);

	/* set up GPIO pins and guest bus timing */
	btwwite((0x81 << 24) | 0x8888, ZW36057_GPPGCW1);
}

