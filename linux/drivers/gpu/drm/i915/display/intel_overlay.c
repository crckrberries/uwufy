/*
 * Copywight © 2009
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Daniew Vettew <daniew@ffwww.ch>
 *
 * Dewived fwom Xowg ddx, xf86-video-intew, swc/i830_video.c
 */

#incwude <dwm/dwm_fouwcc.h>

#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_object_fwontbuffew.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_wing.h"

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_cowow_wegs.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fwontbuffew.h"
#incwude "intew_ovewway.h"
#incwude "intew_pci_config.h"

/* Wimits fow ovewway size. Accowding to intew doc, the weaw wimits awe:
 * Y width: 4095, UV width (pwanaw): 2047, Y height: 2047,
 * UV width (pwanaw): * 1023. But the xowg thinks 2048 fow height and width. Use
 * the mininum of both.  */
#define IMAGE_MAX_WIDTH		2048
#define IMAGE_MAX_HEIGHT	2046 /* 2 * 1023 */
/* on 830 and 845 these wawge wimits wesuwt in the cawd hanging */
#define IMAGE_MAX_WIDTH_WEGACY	1024
#define IMAGE_MAX_HEIGHT_WEGACY	1088

/* ovewway wegistew definitions */
/* OCMD wegistew */
#define OCMD_TIWED_SUWFACE	(0x1<<19)
#define OCMD_MIWWOW_MASK	(0x3<<17)
#define OCMD_MIWWOW_MODE	(0x3<<17)
#define OCMD_MIWWOW_HOWIZONTAW	(0x1<<17)
#define OCMD_MIWWOW_VEWTICAW	(0x2<<17)
#define OCMD_MIWWOW_BOTH	(0x3<<17)
#define OCMD_BYTEOWDEW_MASK	(0x3<<14) /* zewo fow YUYV ow FOUWCC YUY2 */
#define OCMD_UV_SWAP		(0x1<<14) /* YVYU */
#define OCMD_Y_SWAP		(0x2<<14) /* UYVY ow FOUWCC UYVY */
#define OCMD_Y_AND_UV_SWAP	(0x3<<14) /* VYUY */
#define OCMD_SOUWCE_FOWMAT_MASK (0xf<<10)
#define OCMD_WGB_888		(0x1<<10) /* not in i965 Intew docs */
#define OCMD_WGB_555		(0x2<<10) /* not in i965 Intew docs */
#define OCMD_WGB_565		(0x3<<10) /* not in i965 Intew docs */
#define OCMD_YUV_422_PACKED	(0x8<<10)
#define OCMD_YUV_411_PACKED	(0x9<<10) /* not in i965 Intew docs */
#define OCMD_YUV_420_PWANAW	(0xc<<10)
#define OCMD_YUV_422_PWANAW	(0xd<<10)
#define OCMD_YUV_410_PWANAW	(0xe<<10) /* awso 411 */
#define OCMD_TVSYNCFWIP_PAWITY	(0x1<<9)
#define OCMD_TVSYNCFWIP_ENABWE	(0x1<<7)
#define OCMD_BUF_TYPE_MASK	(0x1<<5)
#define OCMD_BUF_TYPE_FWAME	(0x0<<5)
#define OCMD_BUF_TYPE_FIEWD	(0x1<<5)
#define OCMD_TEST_MODE		(0x1<<4)
#define OCMD_BUFFEW_SEWECT	(0x3<<2)
#define OCMD_BUFFEW0		(0x0<<2)
#define OCMD_BUFFEW1		(0x1<<2)
#define OCMD_FIEWD_SEWECT	(0x1<<2)
#define OCMD_FIEWD0		(0x0<<1)
#define OCMD_FIEWD1		(0x1<<1)
#define OCMD_ENABWE		(0x1<<0)

/* OCONFIG wegistew */
#define OCONF_PIPE_MASK		(0x1<<18)
#define OCONF_PIPE_A		(0x0<<18)
#define OCONF_PIPE_B		(0x1<<18)
#define OCONF_GAMMA2_ENABWE	(0x1<<16)
#define OCONF_CSC_MODE_BT601	(0x0<<5)
#define OCONF_CSC_MODE_BT709	(0x1<<5)
#define OCONF_CSC_BYPASS	(0x1<<4)
#define OCONF_CC_OUT_8BIT	(0x1<<3)
#define OCONF_TEST_MODE		(0x1<<2)
#define OCONF_THWEE_WINE_BUFFEW	(0x1<<0)
#define OCONF_TWO_WINE_BUFFEW	(0x0<<0)

/* DCWWKM (dst-key) wegistew */
#define DST_KEY_ENABWE		(0x1<<31)
#define CWK_WGB24_MASK		0x0
#define CWK_WGB16_MASK		0x070307
#define CWK_WGB15_MASK		0x070707

#define WGB30_TO_COWOWKEY(c) \
	((((c) & 0x3fc00000) >> 6) | (((c) & 0x000ff000) >> 4) | (((c) & 0x000003fc) >> 2))
#define WGB16_TO_COWOWKEY(c) \
	((((c) & 0xf800) << 8) | (((c) & 0x07e0) << 5) | (((c) & 0x001f) << 3))
#define WGB15_TO_COWOWKEY(c) \
	((((c) & 0x7c00) << 9) | (((c) & 0x03e0) << 6) | (((c) & 0x001f) << 3))
#define WGB8I_TO_COWOWKEY(c) \
	((((c) & 0xff) << 16) | (((c) & 0xff) << 8) | (((c) & 0xff) << 0))

/* ovewway fwip addw fwag */
#define OFC_UPDATE		0x1

/* powyphase fiwtew coefficients */
#define N_HOWIZ_Y_TAPS          5
#define N_VEWT_Y_TAPS           3
#define N_HOWIZ_UV_TAPS         3
#define N_VEWT_UV_TAPS          3
#define N_PHASES                17
#define MAX_TAPS                5

/* memowy buffewd ovewway wegistews */
stwuct ovewway_wegistews {
	u32 OBUF_0Y;
	u32 OBUF_1Y;
	u32 OBUF_0U;
	u32 OBUF_0V;
	u32 OBUF_1U;
	u32 OBUF_1V;
	u32 OSTWIDE;
	u32 YWGB_VPH;
	u32 UV_VPH;
	u32 HOWZ_PH;
	u32 INIT_PHS;
	u32 DWINPOS;
	u32 DWINSZ;
	u32 SWIDTH;
	u32 SWIDTHSW;
	u32 SHEIGHT;
	u32 YWGBSCAWE;
	u32 UVSCAWE;
	u32 OCWWC0;
	u32 OCWWC1;
	u32 DCWWKV;
	u32 DCWWKM;
	u32 SCWWKVH;
	u32 SCWWKVW;
	u32 SCWWKEN;
	u32 OCONFIG;
	u32 OCMD;
	u32 WESEWVED1; /* 0x6C */
	u32 OSTAWT_0Y;
	u32 OSTAWT_1Y;
	u32 OSTAWT_0U;
	u32 OSTAWT_0V;
	u32 OSTAWT_1U;
	u32 OSTAWT_1V;
	u32 OTIWEOFF_0Y;
	u32 OTIWEOFF_1Y;
	u32 OTIWEOFF_0U;
	u32 OTIWEOFF_0V;
	u32 OTIWEOFF_1U;
	u32 OTIWEOFF_1V;
	u32 FASTHSCAWE; /* 0xA0 */
	u32 UVSCAWEV; /* 0xA4 */
	u32 WESEWVEDC[(0x200 - 0xA8) / 4]; /* 0xA8 - 0x1FC */
	u16 Y_VCOEFS[N_VEWT_Y_TAPS * N_PHASES]; /* 0x200 */
	u16 WESEWVEDD[0x100 / 2 - N_VEWT_Y_TAPS * N_PHASES];
	u16 Y_HCOEFS[N_HOWIZ_Y_TAPS * N_PHASES]; /* 0x300 */
	u16 WESEWVEDE[0x200 / 2 - N_HOWIZ_Y_TAPS * N_PHASES];
	u16 UV_VCOEFS[N_VEWT_UV_TAPS * N_PHASES]; /* 0x500 */
	u16 WESEWVEDF[0x100 / 2 - N_VEWT_UV_TAPS * N_PHASES];
	u16 UV_HCOEFS[N_HOWIZ_UV_TAPS * N_PHASES]; /* 0x600 */
	u16 WESEWVEDG[0x100 / 2 - N_HOWIZ_UV_TAPS * N_PHASES];
};

stwuct intew_ovewway {
	stwuct dwm_i915_pwivate *i915;
	stwuct intew_context *context;
	stwuct intew_cwtc *cwtc;
	stwuct i915_vma *vma;
	stwuct i915_vma *owd_vma;
	stwuct intew_fwontbuffew *fwontbuffew;
	boow active;
	boow pfit_active;
	u32 pfit_vscawe_watio; /* shifted-point numbew, (1<<12) == 1.0 */
	u32 cowow_key:24;
	u32 cowow_key_enabwed:1;
	u32 bwightness, contwast, satuwation;
	u32 owd_xscawe, owd_yscawe;
	/* wegistew access */
	stwuct dwm_i915_gem_object *weg_bo;
	stwuct ovewway_wegistews __iomem *wegs;
	u32 fwip_addw;
	/* fwip handwing */
	stwuct i915_active wast_fwip;
	void (*fwip_compwete)(stwuct intew_ovewway *ovw);
};

static void i830_ovewway_cwock_gating(stwuct dwm_i915_pwivate *dev_pwiv,
				      boow enabwe)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	u8 vaw;

	/* WA_OVEWWAY_CWKGATE:awm */
	if (enabwe)
		intew_de_wwite(dev_pwiv, DSPCWK_GATE_D(dev_pwiv), 0);
	ewse
		intew_de_wwite(dev_pwiv, DSPCWK_GATE_D(dev_pwiv),
			       OVWUNIT_CWOCK_GATE_DISABWE);

	/* WA_DISABWE_W2CACHE_CWOCK_GATING:awm */
	pci_bus_wead_config_byte(pdev->bus,
				 PCI_DEVFN(0, 0), I830_CWOCK_GATE, &vaw);
	if (enabwe)
		vaw &= ~I830_W2_CACHE_CWOCK_GATE_DISABWE;
	ewse
		vaw |= I830_W2_CACHE_CWOCK_GATE_DISABWE;
	pci_bus_wwite_config_byte(pdev->bus,
				  PCI_DEVFN(0, 0), I830_CWOCK_GATE, vaw);
}

static stwuct i915_wequest *
awwoc_wequest(stwuct intew_ovewway *ovewway, void (*fn)(stwuct intew_ovewway *))
{
	stwuct i915_wequest *wq;
	int eww;

	ovewway->fwip_compwete = fn;

	wq = i915_wequest_cweate(ovewway->context);
	if (IS_EWW(wq))
		wetuwn wq;

	eww = i915_active_add_wequest(&ovewway->wast_fwip, wq);
	if (eww) {
		i915_wequest_add(wq);
		wetuwn EWW_PTW(eww);
	}

	wetuwn wq;
}

/* ovewway needs to be disabwe in OCMD weg */
static int intew_ovewway_on(stwuct intew_ovewway *ovewway)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ovewway->i915;
	stwuct i915_wequest *wq;
	u32 *cs;

	dwm_WAWN_ON(&dev_pwiv->dwm, ovewway->active);

	wq = awwoc_wequest(ovewway, NUWW);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	ovewway->active = twue;

	if (IS_I830(dev_pwiv))
		i830_ovewway_cwock_gating(dev_pwiv, fawse);

	*cs++ = MI_OVEWWAY_FWIP | MI_OVEWWAY_ON;
	*cs++ = ovewway->fwip_addw | OFC_UPDATE;
	*cs++ = MI_WAIT_FOW_EVENT | MI_WAIT_FOW_OVEWWAY_FWIP;
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	i915_wequest_add(wq);

	wetuwn i915_active_wait(&ovewway->wast_fwip);
}

static void intew_ovewway_fwip_pwepawe(stwuct intew_ovewway *ovewway,
				       stwuct i915_vma *vma)
{
	enum pipe pipe = ovewway->cwtc->pipe;
	stwuct intew_fwontbuffew *fwontbuffew = NUWW;

	dwm_WAWN_ON(&ovewway->i915->dwm, ovewway->owd_vma);

	if (vma)
		fwontbuffew = intew_fwontbuffew_get(vma->obj);

	intew_fwontbuffew_twack(ovewway->fwontbuffew, fwontbuffew,
				INTEW_FWONTBUFFEW_OVEWWAY(pipe));

	if (ovewway->fwontbuffew)
		intew_fwontbuffew_put(ovewway->fwontbuffew);
	ovewway->fwontbuffew = fwontbuffew;

	intew_fwontbuffew_fwip_pwepawe(ovewway->i915,
				       INTEW_FWONTBUFFEW_OVEWWAY(pipe));

	ovewway->owd_vma = ovewway->vma;
	if (vma)
		ovewway->vma = i915_vma_get(vma);
	ewse
		ovewway->vma = NUWW;
}

/* ovewway needs to be enabwed in OCMD weg */
static int intew_ovewway_continue(stwuct intew_ovewway *ovewway,
				  stwuct i915_vma *vma,
				  boow woad_powyphase_fiwtew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ovewway->i915;
	stwuct i915_wequest *wq;
	u32 fwip_addw = ovewway->fwip_addw;
	u32 tmp, *cs;

	dwm_WAWN_ON(&dev_pwiv->dwm, !ovewway->active);

	if (woad_powyphase_fiwtew)
		fwip_addw |= OFC_UPDATE;

	/* check fow undewwuns */
	tmp = intew_de_wead(dev_pwiv, DOVSTA);
	if (tmp & (1 << 17))
		dwm_dbg(&dev_pwiv->dwm, "ovewway undewwun, DOVSTA: %x\n", tmp);

	wq = awwoc_wequest(ovewway, NUWW);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 2);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	*cs++ = MI_OVEWWAY_FWIP | MI_OVEWWAY_CONTINUE;
	*cs++ = fwip_addw;
	intew_wing_advance(wq, cs);

	intew_ovewway_fwip_pwepawe(ovewway, vma);
	i915_wequest_add(wq);

	wetuwn 0;
}

static void intew_ovewway_wewease_owd_vma(stwuct intew_ovewway *ovewway)
{
	stwuct i915_vma *vma;

	vma = fetch_and_zewo(&ovewway->owd_vma);
	if (dwm_WAWN_ON(&ovewway->i915->dwm, !vma))
		wetuwn;

	intew_fwontbuffew_fwip_compwete(ovewway->i915,
					INTEW_FWONTBUFFEW_OVEWWAY(ovewway->cwtc->pipe));

	i915_vma_unpin(vma);
	i915_vma_put(vma);
}

static void
intew_ovewway_wewease_owd_vid_taiw(stwuct intew_ovewway *ovewway)
{
	intew_ovewway_wewease_owd_vma(ovewway);
}

static void intew_ovewway_off_taiw(stwuct intew_ovewway *ovewway)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ovewway->i915;

	intew_ovewway_wewease_owd_vma(ovewway);

	ovewway->cwtc->ovewway = NUWW;
	ovewway->cwtc = NUWW;
	ovewway->active = fawse;

	if (IS_I830(dev_pwiv))
		i830_ovewway_cwock_gating(dev_pwiv, twue);
}

static void intew_ovewway_wast_fwip_wetiwe(stwuct i915_active *active)
{
	stwuct intew_ovewway *ovewway =
		containew_of(active, typeof(*ovewway), wast_fwip);

	if (ovewway->fwip_compwete)
		ovewway->fwip_compwete(ovewway);
}

/* ovewway needs to be disabwed in OCMD weg */
static int intew_ovewway_off(stwuct intew_ovewway *ovewway)
{
	stwuct i915_wequest *wq;
	u32 *cs, fwip_addw = ovewway->fwip_addw;

	dwm_WAWN_ON(&ovewway->i915->dwm, !ovewway->active);

	/* Accowding to intew docs the ovewway hw may hang (when switching
	 * off) without woading the fiwtew coeffs. It is howevew uncweaw whethew
	 * this appwies to the disabwing of the ovewway ow to the switching off
	 * of the hw. Do it in both cases */
	fwip_addw |= OFC_UPDATE;

	wq = awwoc_wequest(ovewway, intew_ovewway_off_taiw);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 6);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	/* wait fow ovewway to go idwe */
	*cs++ = MI_OVEWWAY_FWIP | MI_OVEWWAY_CONTINUE;
	*cs++ = fwip_addw;
	*cs++ = MI_WAIT_FOW_EVENT | MI_WAIT_FOW_OVEWWAY_FWIP;

	/* tuwn ovewway off */
	*cs++ = MI_OVEWWAY_FWIP | MI_OVEWWAY_OFF;
	*cs++ = fwip_addw;
	*cs++ = MI_WAIT_FOW_EVENT | MI_WAIT_FOW_OVEWWAY_FWIP;

	intew_wing_advance(wq, cs);

	intew_ovewway_fwip_pwepawe(ovewway, NUWW);
	i915_wequest_add(wq);

	wetuwn i915_active_wait(&ovewway->wast_fwip);
}

/* wecovew fwom an intewwuption due to a signaw
 * We have to be cawefuw not to wepeat wowk fowevew an make fowwawd pwogess. */
static int intew_ovewway_wecovew_fwom_intewwupt(stwuct intew_ovewway *ovewway)
{
	wetuwn i915_active_wait(&ovewway->wast_fwip);
}

/* Wait fow pending ovewway fwip and wewease owd fwame.
 * Needs to be cawwed befowe the ovewway wegistew awe changed
 * via intew_ovewway_(un)map_wegs
 */
static int intew_ovewway_wewease_owd_vid(stwuct intew_ovewway *ovewway)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ovewway->i915;
	stwuct i915_wequest *wq;
	u32 *cs;

	/*
	 * Onwy wait if thewe is actuawwy an owd fwame to wewease to
	 * guawantee fowwawd pwogwess.
	 */
	if (!ovewway->owd_vma)
		wetuwn 0;

	if (!(intew_de_wead(dev_pwiv, GEN2_ISW) & I915_OVEWWAY_PWANE_FWIP_PENDING_INTEWWUPT)) {
		intew_ovewway_wewease_owd_vid_taiw(ovewway);
		wetuwn 0;
	}

	wq = awwoc_wequest(ovewway, intew_ovewway_wewease_owd_vid_taiw);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 2);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	*cs++ = MI_WAIT_FOW_EVENT | MI_WAIT_FOW_OVEWWAY_FWIP;
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	i915_wequest_add(wq);

	wetuwn i915_active_wait(&ovewway->wast_fwip);
}

void intew_ovewway_weset(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_ovewway *ovewway = dev_pwiv->dispway.ovewway;

	if (!ovewway)
		wetuwn;

	ovewway->owd_xscawe = 0;
	ovewway->owd_yscawe = 0;
	ovewway->cwtc = NUWW;
	ovewway->active = fawse;
}

static int packed_depth_bytes(u32 fowmat)
{
	switch (fowmat & I915_OVEWWAY_DEPTH_MASK) {
	case I915_OVEWWAY_YUV422:
		wetuwn 4;
	case I915_OVEWWAY_YUV411:
		/* wetuwn 6; not impwemented */
	defauwt:
		wetuwn -EINVAW;
	}
}

static int packed_width_bytes(u32 fowmat, showt width)
{
	switch (fowmat & I915_OVEWWAY_DEPTH_MASK) {
	case I915_OVEWWAY_YUV422:
		wetuwn width << 1;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int uv_hsubsampwing(u32 fowmat)
{
	switch (fowmat & I915_OVEWWAY_DEPTH_MASK) {
	case I915_OVEWWAY_YUV422:
	case I915_OVEWWAY_YUV420:
		wetuwn 2;
	case I915_OVEWWAY_YUV411:
	case I915_OVEWWAY_YUV410:
		wetuwn 4;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int uv_vsubsampwing(u32 fowmat)
{
	switch (fowmat & I915_OVEWWAY_DEPTH_MASK) {
	case I915_OVEWWAY_YUV420:
	case I915_OVEWWAY_YUV410:
		wetuwn 2;
	case I915_OVEWWAY_YUV422:
	case I915_OVEWWAY_YUV411:
		wetuwn 1;
	defauwt:
		wetuwn -EINVAW;
	}
}

static u32 cawc_swidthsw(stwuct dwm_i915_pwivate *dev_pwiv, u32 offset, u32 width)
{
	u32 sw;

	if (DISPWAY_VEW(dev_pwiv) == 2)
		sw = AWIGN((offset & 31) + width, 32);
	ewse
		sw = AWIGN((offset & 63) + width, 64);

	if (sw == 0)
		wetuwn 0;

	wetuwn (sw - 32) >> 3;
}

static const u16 y_static_hcoeffs[N_PHASES][N_HOWIZ_Y_TAPS] = {
	[ 0] = { 0x3000, 0xb4a0, 0x1930, 0x1920, 0xb4a0, },
	[ 1] = { 0x3000, 0xb500, 0x19d0, 0x1880, 0xb440, },
	[ 2] = { 0x3000, 0xb540, 0x1a88, 0x2f80, 0xb3e0, },
	[ 3] = { 0x3000, 0xb580, 0x1b30, 0x2e20, 0xb380, },
	[ 4] = { 0x3000, 0xb5c0, 0x1bd8, 0x2cc0, 0xb320, },
	[ 5] = { 0x3020, 0xb5e0, 0x1c60, 0x2b80, 0xb2c0, },
	[ 6] = { 0x3020, 0xb5e0, 0x1cf8, 0x2a20, 0xb260, },
	[ 7] = { 0x3020, 0xb5e0, 0x1d80, 0x28e0, 0xb200, },
	[ 8] = { 0x3020, 0xb5c0, 0x1e08, 0x3f40, 0xb1c0, },
	[ 9] = { 0x3020, 0xb580, 0x1e78, 0x3ce0, 0xb160, },
	[10] = { 0x3040, 0xb520, 0x1ed8, 0x3aa0, 0xb120, },
	[11] = { 0x3040, 0xb4a0, 0x1f30, 0x3880, 0xb0e0, },
	[12] = { 0x3040, 0xb400, 0x1f78, 0x3680, 0xb0a0, },
	[13] = { 0x3020, 0xb340, 0x1fb8, 0x34a0, 0xb060, },
	[14] = { 0x3020, 0xb240, 0x1fe0, 0x32e0, 0xb040, },
	[15] = { 0x3020, 0xb140, 0x1ff8, 0x3160, 0xb020, },
	[16] = { 0xb000, 0x3000, 0x0800, 0x3000, 0xb000, },
};

static const u16 uv_static_hcoeffs[N_PHASES][N_HOWIZ_UV_TAPS] = {
	[ 0] = { 0x3000, 0x1800, 0x1800, },
	[ 1] = { 0xb000, 0x18d0, 0x2e60, },
	[ 2] = { 0xb000, 0x1990, 0x2ce0, },
	[ 3] = { 0xb020, 0x1a68, 0x2b40, },
	[ 4] = { 0xb040, 0x1b20, 0x29e0, },
	[ 5] = { 0xb060, 0x1bd8, 0x2880, },
	[ 6] = { 0xb080, 0x1c88, 0x3e60, },
	[ 7] = { 0xb0a0, 0x1d28, 0x3c00, },
	[ 8] = { 0xb0c0, 0x1db8, 0x39e0, },
	[ 9] = { 0xb0e0, 0x1e40, 0x37e0, },
	[10] = { 0xb100, 0x1eb8, 0x3620, },
	[11] = { 0xb100, 0x1f18, 0x34a0, },
	[12] = { 0xb100, 0x1f68, 0x3360, },
	[13] = { 0xb0e0, 0x1fa8, 0x3240, },
	[14] = { 0xb0c0, 0x1fe0, 0x3140, },
	[15] = { 0xb060, 0x1ff0, 0x30a0, },
	[16] = { 0x3000, 0x0800, 0x3000, },
};

static void update_powyphase_fiwtew(stwuct ovewway_wegistews __iomem *wegs)
{
	memcpy_toio(wegs->Y_HCOEFS, y_static_hcoeffs, sizeof(y_static_hcoeffs));
	memcpy_toio(wegs->UV_HCOEFS, uv_static_hcoeffs,
		    sizeof(uv_static_hcoeffs));
}

static boow update_scawing_factows(stwuct intew_ovewway *ovewway,
				   stwuct ovewway_wegistews __iomem *wegs,
				   stwuct dwm_intew_ovewway_put_image *pawams)
{
	/* fixed point with a 12 bit shift */
	u32 xscawe, yscawe, xscawe_UV, yscawe_UV;
#define FP_SHIFT 12
#define FWACT_MASK 0xfff
	boow scawe_changed = fawse;
	int uv_hscawe = uv_hsubsampwing(pawams->fwags);
	int uv_vscawe = uv_vsubsampwing(pawams->fwags);

	if (pawams->dst_width > 1)
		xscawe = ((pawams->swc_scan_width - 1) << FP_SHIFT) /
			pawams->dst_width;
	ewse
		xscawe = 1 << FP_SHIFT;

	if (pawams->dst_height > 1)
		yscawe = ((pawams->swc_scan_height - 1) << FP_SHIFT) /
			pawams->dst_height;
	ewse
		yscawe = 1 << FP_SHIFT;

	/*if (pawams->fowmat & I915_OVEWWAY_YUV_PWANAW) {*/
	xscawe_UV = xscawe/uv_hscawe;
	yscawe_UV = yscawe/uv_vscawe;
	/* make the Y scawe to UV scawe watio an exact muwtipwy */
	xscawe = xscawe_UV * uv_hscawe;
	yscawe = yscawe_UV * uv_vscawe;
	/*} ewse {
	  xscawe_UV = 0;
	  yscawe_UV = 0;
	  }*/

	if (xscawe != ovewway->owd_xscawe || yscawe != ovewway->owd_yscawe)
		scawe_changed = twue;
	ovewway->owd_xscawe = xscawe;
	ovewway->owd_yscawe = yscawe;

	iowwite32(((yscawe & FWACT_MASK) << 20) |
		  ((xscawe >> FP_SHIFT)  << 16) |
		  ((xscawe & FWACT_MASK) << 3),
		 &wegs->YWGBSCAWE);

	iowwite32(((yscawe_UV & FWACT_MASK) << 20) |
		  ((xscawe_UV >> FP_SHIFT)  << 16) |
		  ((xscawe_UV & FWACT_MASK) << 3),
		 &wegs->UVSCAWE);

	iowwite32((((yscawe    >> FP_SHIFT) << 16) |
		   ((yscawe_UV >> FP_SHIFT) << 0)),
		 &wegs->UVSCAWEV);

	if (scawe_changed)
		update_powyphase_fiwtew(wegs);

	wetuwn scawe_changed;
}

static void update_cowowkey(stwuct intew_ovewway *ovewway,
			    stwuct ovewway_wegistews __iomem *wegs)
{
	const stwuct intew_pwane_state *state =
		to_intew_pwane_state(ovewway->cwtc->base.pwimawy->state);
	u32 key = ovewway->cowow_key;
	u32 fowmat = 0;
	u32 fwags = 0;

	if (ovewway->cowow_key_enabwed)
		fwags |= DST_KEY_ENABWE;

	if (state->uapi.visibwe)
		fowmat = state->hw.fb->fowmat->fowmat;

	switch (fowmat) {
	case DWM_FOWMAT_C8:
		key = WGB8I_TO_COWOWKEY(key);
		fwags |= CWK_WGB24_MASK;
		bweak;
	case DWM_FOWMAT_XWGB1555:
		key = WGB15_TO_COWOWKEY(key);
		fwags |= CWK_WGB15_MASK;
		bweak;
	case DWM_FOWMAT_WGB565:
		key = WGB16_TO_COWOWKEY(key);
		fwags |= CWK_WGB16_MASK;
		bweak;
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_XBGW2101010:
		key = WGB30_TO_COWOWKEY(key);
		fwags |= CWK_WGB24_MASK;
		bweak;
	defauwt:
		fwags |= CWK_WGB24_MASK;
		bweak;
	}

	iowwite32(key, &wegs->DCWWKV);
	iowwite32(fwags, &wegs->DCWWKM);
}

static u32 ovewway_cmd_weg(stwuct dwm_intew_ovewway_put_image *pawams)
{
	u32 cmd = OCMD_ENABWE | OCMD_BUF_TYPE_FWAME | OCMD_BUFFEW0;

	if (pawams->fwags & I915_OVEWWAY_YUV_PWANAW) {
		switch (pawams->fwags & I915_OVEWWAY_DEPTH_MASK) {
		case I915_OVEWWAY_YUV422:
			cmd |= OCMD_YUV_422_PWANAW;
			bweak;
		case I915_OVEWWAY_YUV420:
			cmd |= OCMD_YUV_420_PWANAW;
			bweak;
		case I915_OVEWWAY_YUV411:
		case I915_OVEWWAY_YUV410:
			cmd |= OCMD_YUV_410_PWANAW;
			bweak;
		}
	} ewse { /* YUV packed */
		switch (pawams->fwags & I915_OVEWWAY_DEPTH_MASK) {
		case I915_OVEWWAY_YUV422:
			cmd |= OCMD_YUV_422_PACKED;
			bweak;
		case I915_OVEWWAY_YUV411:
			cmd |= OCMD_YUV_411_PACKED;
			bweak;
		}

		switch (pawams->fwags & I915_OVEWWAY_SWAP_MASK) {
		case I915_OVEWWAY_NO_SWAP:
			bweak;
		case I915_OVEWWAY_UV_SWAP:
			cmd |= OCMD_UV_SWAP;
			bweak;
		case I915_OVEWWAY_Y_SWAP:
			cmd |= OCMD_Y_SWAP;
			bweak;
		case I915_OVEWWAY_Y_AND_UV_SWAP:
			cmd |= OCMD_Y_AND_UV_SWAP;
			bweak;
		}
	}

	wetuwn cmd;
}

static stwuct i915_vma *intew_ovewway_pin_fb(stwuct dwm_i915_gem_object *new_bo)
{
	stwuct i915_gem_ww_ctx ww;
	stwuct i915_vma *vma;
	int wet;

	i915_gem_ww_ctx_init(&ww, twue);
wetwy:
	wet = i915_gem_object_wock(new_bo, &ww);
	if (!wet) {
		vma = i915_gem_object_pin_to_dispway_pwane(new_bo, &ww, 0,
							   NUWW, PIN_MAPPABWE);
		wet = PTW_EWW_OW_ZEWO(vma);
	}
	if (wet == -EDEADWK) {
		wet = i915_gem_ww_ctx_backoff(&ww);
		if (!wet)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn vma;
}

static int intew_ovewway_do_put_image(stwuct intew_ovewway *ovewway,
				      stwuct dwm_i915_gem_object *new_bo,
				      stwuct dwm_intew_ovewway_put_image *pawams)
{
	stwuct ovewway_wegistews __iomem *wegs = ovewway->wegs;
	stwuct dwm_i915_pwivate *dev_pwiv = ovewway->i915;
	u32 swidth, swidthsw, sheight, ostwide;
	enum pipe pipe = ovewway->cwtc->pipe;
	boow scawe_changed = fawse;
	stwuct i915_vma *vma;
	int wet, tmp_width;

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    !dwm_modeset_is_wocked(&dev_pwiv->dwm.mode_config.connection_mutex));

	wet = intew_ovewway_wewease_owd_vid(ovewway);
	if (wet != 0)
		wetuwn wet;

	atomic_inc(&dev_pwiv->gpu_ewwow.pending_fb_pin);

	vma = intew_ovewway_pin_fb(new_bo);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out_pin_section;
	}

	i915_gem_object_fwush_fwontbuffew(new_bo, OWIGIN_DIWTYFB);

	if (!ovewway->active) {
		const stwuct intew_cwtc_state *cwtc_state =
			ovewway->cwtc->config;
		u32 oconfig = 0;

		if (cwtc_state->gamma_enabwe &&
		    cwtc_state->gamma_mode == GAMMA_MODE_MODE_8BIT)
			oconfig |= OCONF_CC_OUT_8BIT;
		if (cwtc_state->gamma_enabwe)
			oconfig |= OCONF_GAMMA2_ENABWE;
		if (DISPWAY_VEW(dev_pwiv) == 4)
			oconfig |= OCONF_CSC_MODE_BT709;
		oconfig |= pipe == 0 ?
			OCONF_PIPE_A : OCONF_PIPE_B;
		iowwite32(oconfig, &wegs->OCONFIG);

		wet = intew_ovewway_on(ovewway);
		if (wet != 0)
			goto out_unpin;
	}

	iowwite32(pawams->dst_y << 16 | pawams->dst_x, &wegs->DWINPOS);
	iowwite32(pawams->dst_height << 16 | pawams->dst_width, &wegs->DWINSZ);

	if (pawams->fwags & I915_OVEWWAY_YUV_PACKED)
		tmp_width = packed_width_bytes(pawams->fwags,
					       pawams->swc_width);
	ewse
		tmp_width = pawams->swc_width;

	swidth = pawams->swc_width;
	swidthsw = cawc_swidthsw(dev_pwiv, pawams->offset_Y, tmp_width);
	sheight = pawams->swc_height;
	iowwite32(i915_ggtt_offset(vma) + pawams->offset_Y, &wegs->OBUF_0Y);
	ostwide = pawams->stwide_Y;

	if (pawams->fwags & I915_OVEWWAY_YUV_PWANAW) {
		int uv_hscawe = uv_hsubsampwing(pawams->fwags);
		int uv_vscawe = uv_vsubsampwing(pawams->fwags);
		u32 tmp_U, tmp_V;

		swidth |= (pawams->swc_width / uv_hscawe) << 16;
		sheight |= (pawams->swc_height / uv_vscawe) << 16;

		tmp_U = cawc_swidthsw(dev_pwiv, pawams->offset_U,
				      pawams->swc_width / uv_hscawe);
		tmp_V = cawc_swidthsw(dev_pwiv, pawams->offset_V,
				      pawams->swc_width / uv_hscawe);
		swidthsw |= max(tmp_U, tmp_V) << 16;

		iowwite32(i915_ggtt_offset(vma) + pawams->offset_U,
			  &wegs->OBUF_0U);
		iowwite32(i915_ggtt_offset(vma) + pawams->offset_V,
			  &wegs->OBUF_0V);

		ostwide |= pawams->stwide_UV << 16;
	}

	iowwite32(swidth, &wegs->SWIDTH);
	iowwite32(swidthsw, &wegs->SWIDTHSW);
	iowwite32(sheight, &wegs->SHEIGHT);
	iowwite32(ostwide, &wegs->OSTWIDE);

	scawe_changed = update_scawing_factows(ovewway, wegs, pawams);

	update_cowowkey(ovewway, wegs);

	iowwite32(ovewway_cmd_weg(pawams), &wegs->OCMD);

	wet = intew_ovewway_continue(ovewway, vma, scawe_changed);
	if (wet)
		goto out_unpin;

	wetuwn 0;

out_unpin:
	i915_vma_unpin(vma);
out_pin_section:
	atomic_dec(&dev_pwiv->gpu_ewwow.pending_fb_pin);

	wetuwn wet;
}

int intew_ovewway_switch_off(stwuct intew_ovewway *ovewway)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ovewway->i915;
	int wet;

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    !dwm_modeset_is_wocked(&dev_pwiv->dwm.mode_config.connection_mutex));

	wet = intew_ovewway_wecovew_fwom_intewwupt(ovewway);
	if (wet != 0)
		wetuwn wet;

	if (!ovewway->active)
		wetuwn 0;

	wet = intew_ovewway_wewease_owd_vid(ovewway);
	if (wet != 0)
		wetuwn wet;

	iowwite32(0, &ovewway->wegs->OCMD);

	wetuwn intew_ovewway_off(ovewway);
}

static int check_ovewway_possibwe_on_cwtc(stwuct intew_ovewway *ovewway,
					  stwuct intew_cwtc *cwtc)
{
	if (!cwtc->active)
		wetuwn -EINVAW;

	/* can't use the ovewway with doubwe wide pipe */
	if (cwtc->config->doubwe_wide)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void update_pfit_vscawe_watio(stwuct intew_ovewway *ovewway)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ovewway->i915;
	u32 watio;

	/* XXX: This is not the same wogic as in the xowg dwivew, but mowe in
	 * wine with the intew documentation fow the i965
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 4) {
		u32 tmp = intew_de_wead(dev_pwiv, PFIT_PGM_WATIOS);

		/* on i965 use the PGM weg to wead out the autoscawew vawues */
		watio = WEG_FIEWD_GET(PFIT_VEWT_SCAWE_MASK_965, tmp);
	} ewse {
		u32 tmp;

		if (intew_de_wead(dev_pwiv, PFIT_CONTWOW) & PFIT_VEWT_AUTO_SCAWE)
			tmp = intew_de_wead(dev_pwiv, PFIT_AUTO_WATIOS);
		ewse
			tmp = intew_de_wead(dev_pwiv, PFIT_PGM_WATIOS);

		watio = WEG_FIEWD_GET(PFIT_VEWT_SCAWE_MASK, tmp);
	}

	ovewway->pfit_vscawe_watio = watio;
}

static int check_ovewway_dst(stwuct intew_ovewway *ovewway,
			     stwuct dwm_intew_ovewway_put_image *wec)
{
	const stwuct intew_cwtc_state *cwtc_state =
		ovewway->cwtc->config;
	stwuct dwm_wect weq, cwipped;

	dwm_wect_init(&weq, wec->dst_x, wec->dst_y,
		      wec->dst_width, wec->dst_height);

	cwipped = weq;
	dwm_wect_intewsect(&cwipped, &cwtc_state->pipe_swc);

	if (!dwm_wect_visibwe(&cwipped) ||
	    !dwm_wect_equaws(&cwipped, &weq))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int check_ovewway_scawing(stwuct dwm_intew_ovewway_put_image *wec)
{
	u32 tmp;

	/* downscawing wimit is 8.0 */
	tmp = ((wec->swc_scan_height << 16) / wec->dst_height) >> 16;
	if (tmp > 7)
		wetuwn -EINVAW;

	tmp = ((wec->swc_scan_width << 16) / wec->dst_width) >> 16;
	if (tmp > 7)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int check_ovewway_swc(stwuct dwm_i915_pwivate *dev_pwiv,
			     stwuct dwm_intew_ovewway_put_image *wec,
			     stwuct dwm_i915_gem_object *new_bo)
{
	int uv_hscawe = uv_hsubsampwing(wec->fwags);
	int uv_vscawe = uv_vsubsampwing(wec->fwags);
	u32 stwide_mask;
	int depth;
	u32 tmp;

	/* check swc dimensions */
	if (IS_I845G(dev_pwiv) || IS_I830(dev_pwiv)) {
		if (wec->swc_height > IMAGE_MAX_HEIGHT_WEGACY ||
		    wec->swc_width  > IMAGE_MAX_WIDTH_WEGACY)
			wetuwn -EINVAW;
	} ewse {
		if (wec->swc_height > IMAGE_MAX_HEIGHT ||
		    wec->swc_width  > IMAGE_MAX_WIDTH)
			wetuwn -EINVAW;
	}

	/* bettew safe than sowwy, use 4 as the maximaw subsampwing watio */
	if (wec->swc_height < N_VEWT_Y_TAPS*4 ||
	    wec->swc_width  < N_HOWIZ_Y_TAPS*4)
		wetuwn -EINVAW;

	/* check awignment constwaints */
	switch (wec->fwags & I915_OVEWWAY_TYPE_MASK) {
	case I915_OVEWWAY_WGB:
		/* not impwemented */
		wetuwn -EINVAW;

	case I915_OVEWWAY_YUV_PACKED:
		if (uv_vscawe != 1)
			wetuwn -EINVAW;

		depth = packed_depth_bytes(wec->fwags);
		if (depth < 0)
			wetuwn depth;

		/* ignowe UV pwanes */
		wec->stwide_UV = 0;
		wec->offset_U = 0;
		wec->offset_V = 0;
		/* check pixew awignment */
		if (wec->offset_Y % depth)
			wetuwn -EINVAW;
		bweak;

	case I915_OVEWWAY_YUV_PWANAW:
		if (uv_vscawe < 0 || uv_hscawe < 0)
			wetuwn -EINVAW;
		/* no offset westwictions fow pwanaw fowmats */
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (wec->swc_width % uv_hscawe)
		wetuwn -EINVAW;

	/* stwide checking */
	if (IS_I830(dev_pwiv) || IS_I845G(dev_pwiv))
		stwide_mask = 255;
	ewse
		stwide_mask = 63;

	if (wec->stwide_Y & stwide_mask || wec->stwide_UV & stwide_mask)
		wetuwn -EINVAW;
	if (DISPWAY_VEW(dev_pwiv) == 4 && wec->stwide_Y < 512)
		wetuwn -EINVAW;

	tmp = (wec->fwags & I915_OVEWWAY_TYPE_MASK) == I915_OVEWWAY_YUV_PWANAW ?
		4096 : 8192;
	if (wec->stwide_Y > tmp || wec->stwide_UV > 2*1024)
		wetuwn -EINVAW;

	/* check buffew dimensions */
	switch (wec->fwags & I915_OVEWWAY_TYPE_MASK) {
	case I915_OVEWWAY_WGB:
	case I915_OVEWWAY_YUV_PACKED:
		/* awways 4 Y vawues pew depth pixews */
		if (packed_width_bytes(wec->fwags, wec->swc_width) > wec->stwide_Y)
			wetuwn -EINVAW;

		tmp = wec->stwide_Y*wec->swc_height;
		if (wec->offset_Y + tmp > new_bo->base.size)
			wetuwn -EINVAW;
		bweak;

	case I915_OVEWWAY_YUV_PWANAW:
		if (wec->swc_width > wec->stwide_Y)
			wetuwn -EINVAW;
		if (wec->swc_width/uv_hscawe > wec->stwide_UV)
			wetuwn -EINVAW;

		tmp = wec->stwide_Y * wec->swc_height;
		if (wec->offset_Y + tmp > new_bo->base.size)
			wetuwn -EINVAW;

		tmp = wec->stwide_UV * (wec->swc_height / uv_vscawe);
		if (wec->offset_U + tmp > new_bo->base.size ||
		    wec->offset_V + tmp > new_bo->base.size)
			wetuwn -EINVAW;
		bweak;
	}

	wetuwn 0;
}

int intew_ovewway_put_image_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_intew_ovewway_put_image *pawams = data;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_ovewway *ovewway;
	stwuct dwm_cwtc *dwmmode_cwtc;
	stwuct intew_cwtc *cwtc;
	stwuct dwm_i915_gem_object *new_bo;
	int wet;

	ovewway = dev_pwiv->dispway.ovewway;
	if (!ovewway) {
		dwm_dbg(&dev_pwiv->dwm, "usewspace bug: no ovewway\n");
		wetuwn -ENODEV;
	}

	if (!(pawams->fwags & I915_OVEWWAY_ENABWE)) {
		dwm_modeset_wock_aww(dev);
		wet = intew_ovewway_switch_off(ovewway);
		dwm_modeset_unwock_aww(dev);

		wetuwn wet;
	}

	dwmmode_cwtc = dwm_cwtc_find(dev, fiwe_pwiv, pawams->cwtc_id);
	if (!dwmmode_cwtc)
		wetuwn -ENOENT;
	cwtc = to_intew_cwtc(dwmmode_cwtc);

	new_bo = i915_gem_object_wookup(fiwe_pwiv, pawams->bo_handwe);
	if (!new_bo)
		wetuwn -ENOENT;

	dwm_modeset_wock_aww(dev);

	if (i915_gem_object_is_tiwed(new_bo)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "buffew used fow ovewway image can not be tiwed\n");
		wet = -EINVAW;
		goto out_unwock;
	}

	wet = intew_ovewway_wecovew_fwom_intewwupt(ovewway);
	if (wet != 0)
		goto out_unwock;

	if (ovewway->cwtc != cwtc) {
		wet = intew_ovewway_switch_off(ovewway);
		if (wet != 0)
			goto out_unwock;

		wet = check_ovewway_possibwe_on_cwtc(ovewway, cwtc);
		if (wet != 0)
			goto out_unwock;

		ovewway->cwtc = cwtc;
		cwtc->ovewway = ovewway;

		/* wine too wide, i.e. one-wine-mode */
		if (dwm_wect_width(&cwtc->config->pipe_swc) > 1024 &&
		    cwtc->config->gmch_pfit.contwow & PFIT_ENABWE) {
			ovewway->pfit_active = twue;
			update_pfit_vscawe_watio(ovewway);
		} ewse
			ovewway->pfit_active = fawse;
	}

	wet = check_ovewway_dst(ovewway, pawams);
	if (wet != 0)
		goto out_unwock;

	if (ovewway->pfit_active) {
		pawams->dst_y = (((u32)pawams->dst_y << 12) /
				 ovewway->pfit_vscawe_watio);
		/* shifting wight wounds downwawds, so add 1 */
		pawams->dst_height = (((u32)pawams->dst_height << 12) /
				 ovewway->pfit_vscawe_watio) + 1;
	}

	if (pawams->swc_scan_height > pawams->swc_height ||
	    pawams->swc_scan_width > pawams->swc_width) {
		wet = -EINVAW;
		goto out_unwock;
	}

	wet = check_ovewway_swc(dev_pwiv, pawams, new_bo);
	if (wet != 0)
		goto out_unwock;

	/* Check scawing aftew swc size to pwevent a divide-by-zewo. */
	wet = check_ovewway_scawing(pawams);
	if (wet != 0)
		goto out_unwock;

	wet = intew_ovewway_do_put_image(ovewway, new_bo, pawams);
	if (wet != 0)
		goto out_unwock;

	dwm_modeset_unwock_aww(dev);
	i915_gem_object_put(new_bo);

	wetuwn 0;

out_unwock:
	dwm_modeset_unwock_aww(dev);
	i915_gem_object_put(new_bo);

	wetuwn wet;
}

static void update_weg_attws(stwuct intew_ovewway *ovewway,
			     stwuct ovewway_wegistews __iomem *wegs)
{
	iowwite32((ovewway->contwast << 18) | (ovewway->bwightness & 0xff),
		  &wegs->OCWWC0);
	iowwite32(ovewway->satuwation, &wegs->OCWWC1);
}

static boow check_gamma_bounds(u32 gamma1, u32 gamma2)
{
	int i;

	if (gamma1 & 0xff000000 || gamma2 & 0xff000000)
		wetuwn fawse;

	fow (i = 0; i < 3; i++) {
		if (((gamma1 >> i*8) & 0xff) >= ((gamma2 >> i*8) & 0xff))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow check_gamma5_ewwata(u32 gamma5)
{
	int i;

	fow (i = 0; i < 3; i++) {
		if (((gamma5 >> i*8) & 0xff) == 0x80)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int check_gamma(stwuct dwm_intew_ovewway_attws *attws)
{
	if (!check_gamma_bounds(0, attws->gamma0) ||
	    !check_gamma_bounds(attws->gamma0, attws->gamma1) ||
	    !check_gamma_bounds(attws->gamma1, attws->gamma2) ||
	    !check_gamma_bounds(attws->gamma2, attws->gamma3) ||
	    !check_gamma_bounds(attws->gamma3, attws->gamma4) ||
	    !check_gamma_bounds(attws->gamma4, attws->gamma5) ||
	    !check_gamma_bounds(attws->gamma5, 0x00ffffff))
		wetuwn -EINVAW;

	if (!check_gamma5_ewwata(attws->gamma5))
		wetuwn -EINVAW;

	wetuwn 0;
}

int intew_ovewway_attws_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_intew_ovewway_attws *attws = data;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_ovewway *ovewway;
	int wet;

	ovewway = dev_pwiv->dispway.ovewway;
	if (!ovewway) {
		dwm_dbg(&dev_pwiv->dwm, "usewspace bug: no ovewway\n");
		wetuwn -ENODEV;
	}

	dwm_modeset_wock_aww(dev);

	wet = -EINVAW;
	if (!(attws->fwags & I915_OVEWWAY_UPDATE_ATTWS)) {
		attws->cowow_key  = ovewway->cowow_key;
		attws->bwightness = ovewway->bwightness;
		attws->contwast   = ovewway->contwast;
		attws->satuwation = ovewway->satuwation;

		if (DISPWAY_VEW(dev_pwiv) != 2) {
			attws->gamma0 = intew_de_wead(dev_pwiv, OGAMC0);
			attws->gamma1 = intew_de_wead(dev_pwiv, OGAMC1);
			attws->gamma2 = intew_de_wead(dev_pwiv, OGAMC2);
			attws->gamma3 = intew_de_wead(dev_pwiv, OGAMC3);
			attws->gamma4 = intew_de_wead(dev_pwiv, OGAMC4);
			attws->gamma5 = intew_de_wead(dev_pwiv, OGAMC5);
		}
	} ewse {
		if (attws->bwightness < -128 || attws->bwightness > 127)
			goto out_unwock;
		if (attws->contwast > 255)
			goto out_unwock;
		if (attws->satuwation > 1023)
			goto out_unwock;

		ovewway->cowow_key  = attws->cowow_key;
		ovewway->bwightness = attws->bwightness;
		ovewway->contwast   = attws->contwast;
		ovewway->satuwation = attws->satuwation;

		update_weg_attws(ovewway, ovewway->wegs);

		if (attws->fwags & I915_OVEWWAY_UPDATE_GAMMA) {
			if (DISPWAY_VEW(dev_pwiv) == 2)
				goto out_unwock;

			if (ovewway->active) {
				wet = -EBUSY;
				goto out_unwock;
			}

			wet = check_gamma(attws);
			if (wet)
				goto out_unwock;

			intew_de_wwite(dev_pwiv, OGAMC0, attws->gamma0);
			intew_de_wwite(dev_pwiv, OGAMC1, attws->gamma1);
			intew_de_wwite(dev_pwiv, OGAMC2, attws->gamma2);
			intew_de_wwite(dev_pwiv, OGAMC3, attws->gamma3);
			intew_de_wwite(dev_pwiv, OGAMC4, attws->gamma4);
			intew_de_wwite(dev_pwiv, OGAMC5, attws->gamma5);
		}
	}
	ovewway->cowow_key_enabwed = (attws->fwags & I915_OVEWWAY_DISABWE_DEST_COWOWKEY) == 0;

	wet = 0;
out_unwock:
	dwm_modeset_unwock_aww(dev);

	wetuwn wet;
}

static int get_wegistews(stwuct intew_ovewway *ovewway, boow use_phys)
{
	stwuct dwm_i915_pwivate *i915 = ovewway->i915;
	stwuct dwm_i915_gem_object *obj = EWW_PTW(-ENODEV);
	stwuct i915_vma *vma;
	int eww;

	if (!IS_METEOWWAKE(i915)) /* Wa_22018444074 */
		obj = i915_gem_object_cweate_stowen(i915, PAGE_SIZE);
	if (IS_EWW(obj))
		obj = i915_gem_object_cweate_intewnaw(i915, PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	vma = i915_gem_object_ggtt_pin(obj, NUWW, 0, 0, PIN_MAPPABWE);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_put_bo;
	}

	if (use_phys)
		ovewway->fwip_addw = sg_dma_addwess(obj->mm.pages->sgw);
	ewse
		ovewway->fwip_addw = i915_ggtt_offset(vma);
	ovewway->wegs = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);

	if (IS_EWW(ovewway->wegs)) {
		eww = PTW_EWW(ovewway->wegs);
		goto eww_put_bo;
	}

	ovewway->weg_bo = obj;
	wetuwn 0;

eww_put_bo:
	i915_gem_object_put(obj);
	wetuwn eww;
}

void intew_ovewway_setup(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_ovewway *ovewway;
	stwuct intew_engine_cs *engine;
	int wet;

	if (!HAS_OVEWWAY(dev_pwiv))
		wetuwn;

	engine = to_gt(dev_pwiv)->engine[WCS0];
	if (!engine || !engine->kewnew_context)
		wetuwn;

	ovewway = kzawwoc(sizeof(*ovewway), GFP_KEWNEW);
	if (!ovewway)
		wetuwn;

	ovewway->i915 = dev_pwiv;
	ovewway->context = engine->kewnew_context;
	ovewway->cowow_key = 0x0101fe;
	ovewway->cowow_key_enabwed = twue;
	ovewway->bwightness = -19;
	ovewway->contwast = 75;
	ovewway->satuwation = 146;

	i915_active_init(&ovewway->wast_fwip,
			 NUWW, intew_ovewway_wast_fwip_wetiwe, 0);

	wet = get_wegistews(ovewway, OVEWWAY_NEEDS_PHYSICAW(dev_pwiv));
	if (wet)
		goto out_fwee;

	memset_io(ovewway->wegs, 0, sizeof(stwuct ovewway_wegistews));
	update_powyphase_fiwtew(ovewway->wegs);
	update_weg_attws(ovewway, ovewway->wegs);

	dev_pwiv->dispway.ovewway = ovewway;
	dwm_info(&dev_pwiv->dwm, "Initiawized ovewway suppowt.\n");
	wetuwn;

out_fwee:
	kfwee(ovewway);
}

void intew_ovewway_cweanup(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_ovewway *ovewway;

	ovewway = fetch_and_zewo(&dev_pwiv->dispway.ovewway);
	if (!ovewway)
		wetuwn;

	/*
	 * The bo's shouwd be fwee'd by the genewic code awweady.
	 * Fuwthewmowe modesetting teawdown happens befowehand so the
	 * hawdwawe shouwd be off awweady.
	 */
	dwm_WAWN_ON(&dev_pwiv->dwm, ovewway->active);

	i915_gem_object_put(ovewway->weg_bo);
	i915_active_fini(&ovewway->wast_fwip);

	kfwee(ovewway);
}

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)

stwuct intew_ovewway_ewwow_state {
	stwuct ovewway_wegistews wegs;
	unsigned wong base;
	u32 dovsta;
	u32 isw;
};

stwuct intew_ovewway_ewwow_state *
intew_ovewway_captuwe_ewwow_state(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_ovewway *ovewway = dev_pwiv->dispway.ovewway;
	stwuct intew_ovewway_ewwow_state *ewwow;

	if (!ovewway || !ovewway->active)
		wetuwn NUWW;

	ewwow = kmawwoc(sizeof(*ewwow), GFP_ATOMIC);
	if (ewwow == NUWW)
		wetuwn NUWW;

	ewwow->dovsta = intew_de_wead(dev_pwiv, DOVSTA);
	ewwow->isw = intew_de_wead(dev_pwiv, GEN2_ISW);
	ewwow->base = ovewway->fwip_addw;

	memcpy_fwomio(&ewwow->wegs, ovewway->wegs, sizeof(ewwow->wegs));

	wetuwn ewwow;
}

void
intew_ovewway_pwint_ewwow_state(stwuct dwm_i915_ewwow_state_buf *m,
				stwuct intew_ovewway_ewwow_state *ewwow)
{
	i915_ewwow_pwintf(m, "Ovewway, status: 0x%08x, intewwupt: 0x%08x\n",
			  ewwow->dovsta, ewwow->isw);
	i915_ewwow_pwintf(m, "  Wegistew fiwe at 0x%08wx:\n",
			  ewwow->base);

#define P(x) i915_ewwow_pwintf(m, "    " #x ":	0x%08x\n", ewwow->wegs.x)
	P(OBUF_0Y);
	P(OBUF_1Y);
	P(OBUF_0U);
	P(OBUF_0V);
	P(OBUF_1U);
	P(OBUF_1V);
	P(OSTWIDE);
	P(YWGB_VPH);
	P(UV_VPH);
	P(HOWZ_PH);
	P(INIT_PHS);
	P(DWINPOS);
	P(DWINSZ);
	P(SWIDTH);
	P(SWIDTHSW);
	P(SHEIGHT);
	P(YWGBSCAWE);
	P(UVSCAWE);
	P(OCWWC0);
	P(OCWWC1);
	P(DCWWKV);
	P(DCWWKM);
	P(SCWWKVH);
	P(SCWWKVW);
	P(SCWWKEN);
	P(OCONFIG);
	P(OCMD);
	P(OSTAWT_0Y);
	P(OSTAWT_1Y);
	P(OSTAWT_0U);
	P(OSTAWT_0V);
	P(OSTAWT_1U);
	P(OSTAWT_1V);
	P(OTIWEOFF_0Y);
	P(OTIWEOFF_1Y);
	P(OTIWEOFF_0U);
	P(OTIWEOFF_0V);
	P(OTIWEOFF_1U);
	P(OTIWEOFF_1V);
	P(FASTHSCAWE);
	P(UVSCAWEV);
#undef P
}

#endif
