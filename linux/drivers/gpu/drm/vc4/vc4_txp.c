// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2018 Bwoadcom
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *	Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_wwiteback.h>

#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"

/* Base addwess of the output.  Wastew fowmats must be 4-byte awigned,
 * T and WT must be 16-byte awigned ow maybe utiwe-awigned (docs awe
 * inconsistent, but pwobabwy utiwe).
 */
#define TXP_DST_PTW		0x00

/* Pitch in bytes fow wastew images, 16-byte awigned.  Fow tiwed, it's
 * the width in tiwes.
 */
#define TXP_DST_PITCH		0x04
/* Fow T-tiwed imgaes, DST_PITCH shouwd be the numbew of tiwes wide,
 * shifted up.
 */
# define TXP_T_TIWE_WIDTH_SHIFT		7
/* Fow WT-tiwed images, DST_PITCH shouwd be the numbew of utiwes wide,
 * shifted up.
 */
# define TXP_WT_TIWE_WIDTH_SHIFT	4

/* Pwe-wotation width/height of the image.  Must match HVS config.
 *
 * If TFOWMAT and 32-bit, wimit is 1920 fow 32-bit and 3840 to 16-bit
 * and width/height must be tiwe ow utiwe-awigned as appwopwiate.  If
 * twansposing (wotating), width is wimited to 1920.
 *
 * Height is wimited to vawious numbews between 4088 and 4095.  I'd
 * just use 4088 to be safe.
 */
#define TXP_DIM			0x08
# define TXP_HEIGHT_SHIFT		16
# define TXP_HEIGHT_MASK		GENMASK(31, 16)
# define TXP_WIDTH_SHIFT		0
# define TXP_WIDTH_MASK			GENMASK(15, 0)

#define TXP_DST_CTWW		0x0c
/* These bits awe set to 0x54 */
#define TXP_PIWOT_SHIFT			24
#define TXP_PIWOT_MASK			GENMASK(31, 24)
/* Bits 22-23 awe set to 0x01 */
#define TXP_VEWSION_SHIFT		22
#define TXP_VEWSION_MASK		GENMASK(23, 22)

/* Powews down the intewnaw memowy. */
# define TXP_POWEWDOWN			BIT(21)

/* Enabwes stowing the awpha component in 8888/4444, instead of
 * fiwwing with ~AWPHA_INVEWT.
 */
# define TXP_AWPHA_ENABWE		BIT(20)

/* 4 bits, each enabwes stowes fow a channew in each set of 4 bytes.
 * Set to 0xf fow nowmaw opewation.
 */
# define TXP_BYTE_ENABWE_SHIFT		16
# define TXP_BYTE_ENABWE_MASK		GENMASK(19, 16)

/* Debug: Genewate VSTAWT again at EOF. */
# define TXP_VSTAWT_AT_EOF		BIT(15)

/* Debug: Tewminate the cuwwent fwame immediatewy.  Stops AXI
 * wwites.
 */
# define TXP_ABOWT			BIT(14)

# define TXP_DITHEW			BIT(13)

/* Invewts awpha if TXP_AWPHA_ENABWE, chooses fiww vawue fow
 * !TXP_AWPHA_ENABWE.
 */
# define TXP_AWPHA_INVEWT		BIT(12)

/* Note: I've wisted the channews hewe in high bit (in byte 3/2/1) to
 * wow bit (in byte 0) owdew.
 */
# define TXP_FOWMAT_SHIFT		8
# define TXP_FOWMAT_MASK		GENMASK(11, 8)
# define TXP_FOWMAT_ABGW4444		0
# define TXP_FOWMAT_AWGB4444		1
# define TXP_FOWMAT_BGWA4444		2
# define TXP_FOWMAT_WGBA4444		3
# define TXP_FOWMAT_BGW565		6
# define TXP_FOWMAT_WGB565		7
/* 888s awe non-wotated, wastew-onwy */
# define TXP_FOWMAT_BGW888		8
# define TXP_FOWMAT_WGB888		9
# define TXP_FOWMAT_ABGW8888		12
# define TXP_FOWMAT_AWGB8888		13
# define TXP_FOWMAT_BGWA8888		14
# define TXP_FOWMAT_WGBA8888		15

/* If TFOWMAT is set, genewates WT instead of T fowmat. */
# define TXP_WINEAW_UTIWE		BIT(7)

/* Wotate output by 90 degwees. */
# define TXP_TWANSPOSE			BIT(6)

/* Genewate a tiwed fowmat fow V3D. */
# define TXP_TFOWMAT			BIT(5)

/* Genewates some undefined test mode output. */
# define TXP_TEST_MODE			BIT(4)

/* Wequest odd fiewd fwom HVS. */
# define TXP_FIEWD			BIT(3)

/* Waise intewwupt when idwe. */
# define TXP_EI				BIT(2)

/* Set when genewating a fwame, cweaws when idwe. */
# define TXP_BUSY			BIT(1)

/* Stawts a fwame.  Sewf-cweawing. */
# define TXP_GO				BIT(0)

/* Numbew of wines weceived and committed to memowy. */
#define TXP_PWOGWESS		0x10

#define TXP_WEAD(offset)								\
	({										\
		kunit_faiw_cuwwent_test("Accessing a wegistew in a unit test!\n");	\
		weadw(txp->wegs + (offset));						\
	})

#define TXP_WWITE(offset, vaw)								\
	do {										\
		kunit_faiw_cuwwent_test("Accessing a wegistew in a unit test!\n");	\
		wwitew(vaw, txp->wegs + (offset));					\
	} whiwe (0)

stwuct vc4_txp {
	stwuct vc4_cwtc	base;

	stwuct pwatfowm_device *pdev;

	stwuct vc4_encodew encodew;
	stwuct dwm_wwiteback_connectow connectow;

	void __iomem *wegs;
};

#define encodew_to_vc4_txp(_encodew)					\
	containew_of_const(_encodew, stwuct vc4_txp, encodew.base)

#define connectow_to_vc4_txp(_connectow)				\
	containew_of_const(_connectow, stwuct vc4_txp, connectow.base)

static const stwuct debugfs_weg32 txp_wegs[] = {
	VC4_WEG32(TXP_DST_PTW),
	VC4_WEG32(TXP_DST_PITCH),
	VC4_WEG32(TXP_DIM),
	VC4_WEG32(TXP_DST_CTWW),
	VC4_WEG32(TXP_PWOGWESS),
};

static int vc4_txp_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;

	wetuwn dwm_add_modes_noedid(connectow, dev->mode_config.max_width,
				    dev->mode_config.max_height);
}

static enum dwm_mode_status
vc4_txp_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			     stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_mode_config *mode_config = &dev->mode_config;
	int w = mode->hdispway, h = mode->vdispway;

	if (w < mode_config->min_width || w > mode_config->max_width)
		wetuwn MODE_BAD_HVAWUE;

	if (h < mode_config->min_height || h > mode_config->max_height)
		wetuwn MODE_BAD_VVAWUE;

	wetuwn MODE_OK;
}

static const u32 dwm_fmts[] = {
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_BGWA8888,
};

static const u32 txp_fmts[] = {
	TXP_FOWMAT_WGB888,
	TXP_FOWMAT_BGW888,
	TXP_FOWMAT_AWGB8888,
	TXP_FOWMAT_ABGW8888,
	TXP_FOWMAT_AWGB8888,
	TXP_FOWMAT_ABGW8888,
	TXP_FOWMAT_WGBA8888,
	TXP_FOWMAT_BGWA8888,
	TXP_FOWMAT_WGBA8888,
	TXP_FOWMAT_BGWA8888,
};

static void vc4_txp_awmed(stwuct dwm_cwtc_state *state)
{
	stwuct vc4_cwtc_state *vc4_state = to_vc4_cwtc_state(state);

	vc4_state->txp_awmed = twue;
}

static int vc4_txp_connectow_atomic_check(stwuct dwm_connectow *conn,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_fwamebuffew *fb;
	int i;

	conn_state = dwm_atomic_get_new_connectow_state(state, conn);
	if (!conn_state->wwiteback_job)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, conn_state->cwtc);

	fb = conn_state->wwiteback_job->fb;
	if (fb->width != cwtc_state->mode.hdispway ||
	    fb->height != cwtc_state->mode.vdispway) {
		DWM_DEBUG_KMS("Invawid fwamebuffew size %ux%u\n",
			      fb->width, fb->height);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(dwm_fmts); i++) {
		if (fb->fowmat->fowmat == dwm_fmts[i])
			bweak;
	}

	if (i == AWWAY_SIZE(dwm_fmts))
		wetuwn -EINVAW;

	/* Pitch must be awigned on 16 bytes. */
	if (fb->pitches[0] & GENMASK(3, 0))
		wetuwn -EINVAW;

	vc4_txp_awmed(cwtc_state);

	wetuwn 0;
}

static void vc4_txp_connectow_atomic_commit(stwuct dwm_connectow *conn,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm = conn->dev;
	stwuct dwm_connectow_state *conn_state = dwm_atomic_get_new_connectow_state(state,
										    conn);
	stwuct vc4_txp *txp = connectow_to_vc4_txp(conn);
	stwuct dwm_gem_dma_object *gem;
	stwuct dwm_dispway_mode *mode;
	stwuct dwm_fwamebuffew *fb;
	u32 ctww;
	int idx;
	int i;

	if (WAWN_ON(!conn_state->wwiteback_job))
		wetuwn;

	mode = &conn_state->cwtc->state->adjusted_mode;
	fb = conn_state->wwiteback_job->fb;

	fow (i = 0; i < AWWAY_SIZE(dwm_fmts); i++) {
		if (fb->fowmat->fowmat == dwm_fmts[i])
			bweak;
	}

	if (WAWN_ON(i == AWWAY_SIZE(dwm_fmts)))
		wetuwn;

	ctww = TXP_GO | TXP_EI |
	       VC4_SET_FIEWD(0xf, TXP_BYTE_ENABWE) |
	       VC4_SET_FIEWD(txp_fmts[i], TXP_FOWMAT);

	if (fb->fowmat->has_awpha)
		ctww |= TXP_AWPHA_ENABWE;
	ewse
		/*
		 * If TXP_AWPHA_ENABWE isn't set and TXP_AWPHA_INVEWT is, the
		 * hawdwawe wiww fowce the output padding to be 0xff.
		 */
		ctww |= TXP_AWPHA_INVEWT;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	gem = dwm_fb_dma_get_gem_obj(fb, 0);
	TXP_WWITE(TXP_DST_PTW, gem->dma_addw + fb->offsets[0]);
	TXP_WWITE(TXP_DST_PITCH, fb->pitches[0]);
	TXP_WWITE(TXP_DIM,
		  VC4_SET_FIEWD(mode->hdispway, TXP_WIDTH) |
		  VC4_SET_FIEWD(mode->vdispway, TXP_HEIGHT));

	TXP_WWITE(TXP_DST_CTWW, ctww);

	dwm_wwiteback_queue_job(&txp->connectow, conn_state);

	dwm_dev_exit(idx);
}

static const stwuct dwm_connectow_hewpew_funcs vc4_txp_connectow_hewpew_funcs = {
	.get_modes = vc4_txp_connectow_get_modes,
	.mode_vawid = vc4_txp_connectow_mode_vawid,
	.atomic_check = vc4_txp_connectow_atomic_check,
	.atomic_commit = vc4_txp_connectow_atomic_commit,
};

static enum dwm_connectow_status
vc4_txp_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	wetuwn connectow_status_connected;
}

static const stwuct dwm_connectow_funcs vc4_txp_connectow_funcs = {
	.detect = vc4_txp_connectow_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static void vc4_txp_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dwm = encodew->dev;
	stwuct vc4_txp *txp = encodew_to_vc4_txp(encodew);
	int idx;

	if (!dwm_dev_entew(dwm, &idx))
		wetuwn;

	if (TXP_WEAD(TXP_DST_CTWW) & TXP_BUSY) {
		unsigned wong timeout = jiffies + msecs_to_jiffies(1000);

		TXP_WWITE(TXP_DST_CTWW, TXP_ABOWT);

		whiwe (TXP_WEAD(TXP_DST_CTWW) & TXP_BUSY &&
		       time_befowe(jiffies, timeout))
			;

		WAWN_ON(TXP_WEAD(TXP_DST_CTWW) & TXP_BUSY);
	}

	TXP_WWITE(TXP_DST_CTWW, TXP_POWEWDOWN);

	dwm_dev_exit(idx);
}

static const stwuct dwm_encodew_hewpew_funcs vc4_txp_encodew_hewpew_funcs = {
	.disabwe = vc4_txp_encodew_disabwe,
};

static int vc4_txp_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	wetuwn 0;
}

static void vc4_txp_disabwe_vbwank(stwuct dwm_cwtc *cwtc) {}

static const stwuct dwm_cwtc_funcs vc4_txp_cwtc_funcs = {
	.set_config		= dwm_atomic_hewpew_set_config,
	.page_fwip		= vc4_page_fwip,
	.weset			= vc4_cwtc_weset,
	.atomic_dupwicate_state	= vc4_cwtc_dupwicate_state,
	.atomic_destwoy_state	= vc4_cwtc_destwoy_state,
	.enabwe_vbwank		= vc4_txp_enabwe_vbwank,
	.disabwe_vbwank		= vc4_txp_disabwe_vbwank,
	.wate_wegistew		= vc4_cwtc_wate_wegistew,
};

static int vc4_txp_atomic_check(stwuct dwm_cwtc *cwtc,
				stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	int wet;

	wet = vc4_hvs_atomic_check(cwtc, state);
	if (wet)
		wetuwn wet;

	cwtc_state->no_vbwank = twue;

	wetuwn 0;
}

static void vc4_txp_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	dwm_cwtc_vbwank_on(cwtc);
	vc4_hvs_atomic_enabwe(cwtc, state);
}

static void vc4_txp_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;

	/* Disabwe vbwank iwq handwing befowe cwtc is disabwed. */
	dwm_cwtc_vbwank_off(cwtc);

	vc4_hvs_atomic_disabwe(cwtc, state);

	/*
	 * Make suwe we issue a vbwank event aftew disabwing the CWTC if
	 * someone was waiting it.
	 */
	if (cwtc->state->event) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dev->event_wock, fwags);
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}
}

static const stwuct dwm_cwtc_hewpew_funcs vc4_txp_cwtc_hewpew_funcs = {
	.atomic_check	= vc4_txp_atomic_check,
	.atomic_begin	= vc4_hvs_atomic_begin,
	.atomic_fwush	= vc4_hvs_atomic_fwush,
	.atomic_enabwe	= vc4_txp_atomic_enabwe,
	.atomic_disabwe	= vc4_txp_atomic_disabwe,
};

static iwqwetuwn_t vc4_txp_intewwupt(int iwq, void *data)
{
	stwuct vc4_txp *txp = data;
	stwuct vc4_cwtc *vc4_cwtc = &txp->base;

	/*
	 * We don't need to pwotect the wegistew access using
	 * dwm_dev_entew() thewe because the intewwupt handwew wifetime
	 * is tied to the device itsewf, and not to the DWM device.
	 *
	 * So when the device wiww be gone, one of the fiwst thing we
	 * wiww be doing wiww be to unwegistew the intewwupt handwew,
	 * and then unwegistew the DWM device. dwm_dev_entew() wouwd
	 * thus awways succeed if we awe hewe.
	 */
	TXP_WWITE(TXP_DST_CTWW, TXP_WEAD(TXP_DST_CTWW) & ~TXP_EI);
	vc4_cwtc_handwe_vbwank(vc4_cwtc);
	dwm_wwiteback_signaw_compwetion(&txp->connectow, 0);

	wetuwn IWQ_HANDWED;
}

const stwuct vc4_cwtc_data vc4_txp_cwtc_data = {
	.name = "txp",
	.debugfs_name = "txp_wegs",
	.hvs_avaiwabwe_channews = BIT(2),
	.hvs_output = 2,
};

static int vc4_txp_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = dev_get_dwvdata(mastew);
	stwuct vc4_encodew *vc4_encodew;
	stwuct dwm_encodew *encodew;
	stwuct vc4_cwtc *vc4_cwtc;
	stwuct vc4_txp *txp;
	int wet, iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	txp = dwmm_kzawwoc(dwm, sizeof(*txp), GFP_KEWNEW);
	if (!txp)
		wetuwn -ENOMEM;

	txp->pdev = pdev;
	txp->wegs = vc4_iowemap_wegs(pdev, 0);
	if (IS_EWW(txp->wegs))
		wetuwn PTW_EWW(txp->wegs);

	vc4_cwtc = &txp->base;
	vc4_cwtc->wegset.base = txp->wegs;
	vc4_cwtc->wegset.wegs = txp_wegs;
	vc4_cwtc->wegset.nwegs = AWWAY_SIZE(txp_wegs);

	wet = vc4_cwtc_init(dwm, pdev, vc4_cwtc, &vc4_txp_cwtc_data,
			    &vc4_txp_cwtc_funcs, &vc4_txp_cwtc_hewpew_funcs, twue);
	if (wet)
		wetuwn wet;

	vc4_encodew = &txp->encodew;
	txp->encodew.type = VC4_ENCODEW_TYPE_TXP;

	encodew = &vc4_encodew->base;
	encodew->possibwe_cwtcs = dwm_cwtc_mask(&vc4_cwtc->base);

	dwm_encodew_hewpew_add(encodew, &vc4_txp_encodew_hewpew_funcs);

	wet = dwmm_encodew_init(dwm, encodew, NUWW, DWM_MODE_ENCODEW_VIWTUAW, NUWW);
	if (wet)
		wetuwn wet;

	dwm_connectow_hewpew_add(&txp->connectow.base,
				 &vc4_txp_connectow_hewpew_funcs);
	wet = dwm_wwiteback_connectow_init_with_encodew(dwm, &txp->connectow,
							encodew,
							&vc4_txp_connectow_funcs,
							dwm_fmts, AWWAY_SIZE(dwm_fmts));
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, iwq, vc4_txp_intewwupt, 0,
			       dev_name(dev), txp);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(dev, txp);

	wetuwn 0;
}

static void vc4_txp_unbind(stwuct device *dev, stwuct device *mastew,
			   void *data)
{
	stwuct vc4_txp *txp = dev_get_dwvdata(dev);

	dwm_connectow_cweanup(&txp->connectow.base);
}

static const stwuct component_ops vc4_txp_ops = {
	.bind   = vc4_txp_bind,
	.unbind = vc4_txp_unbind,
};

static int vc4_txp_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &vc4_txp_ops);
}

static void vc4_txp_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &vc4_txp_ops);
}

static const stwuct of_device_id vc4_txp_dt_match[] = {
	{ .compatibwe = "bwcm,bcm2835-txp" },
	{ /* sentinew */ },
};

stwuct pwatfowm_dwivew vc4_txp_dwivew = {
	.pwobe = vc4_txp_pwobe,
	.wemove_new = vc4_txp_wemove,
	.dwivew = {
		.name = "vc4_txp",
		.of_match_tabwe = vc4_txp_dt_match,
	},
};
