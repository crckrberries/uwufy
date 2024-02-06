/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* exynos_dwm_dwv.h
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Authows:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#ifndef _EXYNOS_DWM_DWV_H_
#define _EXYNOS_DWM_DWV_H_

#incwude <winux/moduwe.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwane.h>

#define MAX_CWTC	3
#define MAX_PWANE	5
#define MAX_FB_BUFFEW	4

#define DEFAUWT_WIN	0

stwuct dwm_cwtc_state;
stwuct dwm_dispway_mode;

#define to_exynos_cwtc(x)	containew_of(x, stwuct exynos_dwm_cwtc, base)
#define to_exynos_pwane(x)	containew_of(x, stwuct exynos_dwm_pwane, base)

/* this enumewates dispway type. */
enum exynos_dwm_output_type {
	EXYNOS_DISPWAY_TYPE_NONE,
	/* WGB ow CPU Intewface. */
	EXYNOS_DISPWAY_TYPE_WCD,
	/* HDMI Intewface. */
	EXYNOS_DISPWAY_TYPE_HDMI,
	/* Viwtuaw Dispway Intewface. */
	EXYNOS_DISPWAY_TYPE_VIDI,
};

stwuct exynos_dwm_wect {
	unsigned int x, y;
	unsigned int w, h;
};

/*
 * Exynos dwm pwane state stwuctuwe.
 *
 * @base: pwane_state object (contains dwm_fwamebuffew pointew)
 * @swc: wectangwe of the souwce image data to be dispwayed (cwipped to
 *       visibwe pawt).
 * @cwtc: wectangwe of the tawget image position on hawdwawe scween
 *       (cwipped to visibwe pawt).
 * @h_watio: howizontaw scawing watio, 16.16 fixed point
 * @v_watio: vewticaw scawing watio, 16.16 fixed point
 *
 * this stwuctuwe consists pwane state data that wiww be appwied to hawdwawe
 * specific ovewway info.
 */

stwuct exynos_dwm_pwane_state {
	stwuct dwm_pwane_state base;
	stwuct exynos_dwm_wect cwtc;
	stwuct exynos_dwm_wect swc;
	unsigned int h_watio;
	unsigned int v_watio;
};

static inwine stwuct exynos_dwm_pwane_state *
to_exynos_pwane_state(stwuct dwm_pwane_state *state)
{
	wetuwn containew_of(state, stwuct exynos_dwm_pwane_state, base);
}

/*
 * Exynos dwm common ovewway stwuctuwe.
 *
 * @base: pwane object
 * @index: hawdwawe index of the ovewway wayew
 *
 * this stwuctuwe is common to exynos SoC and its contents wouwd be copied
 * to hawdwawe specific ovewway info.
 */

stwuct exynos_dwm_pwane {
	stwuct dwm_pwane base;
	const stwuct exynos_dwm_pwane_config *config;
	unsigned int index;
};

#define EXYNOS_DWM_PWANE_CAP_DOUBWE	(1 << 0)
#define EXYNOS_DWM_PWANE_CAP_SCAWE	(1 << 1)
#define EXYNOS_DWM_PWANE_CAP_ZPOS	(1 << 2)
#define EXYNOS_DWM_PWANE_CAP_TIWE	(1 << 3)
#define EXYNOS_DWM_PWANE_CAP_PIX_BWEND	(1 << 4)
#define EXYNOS_DWM_PWANE_CAP_WIN_BWEND	(1 << 5)

/*
 * Exynos DWM pwane configuwation stwuctuwe.
 *
 * @zpos: initiaw z-position of the pwane.
 * @type: type of the pwane (pwimawy, cuwsow ow ovewway).
 * @pixew_fowmats: suppowted pixew fowmats.
 * @num_pixew_fowmats: numbew of ewements in 'pixew_fowmats'.
 * @capabiwities: suppowted featuwes (see EXYNOS_DWM_PWANE_CAP_*)
 */

stwuct exynos_dwm_pwane_config {
	unsigned int zpos;
	enum dwm_pwane_type type;
	const uint32_t *pixew_fowmats;
	unsigned int num_pixew_fowmats;
	unsigned int capabiwities;
};

/*
 * Exynos dwm cwtc ops
 *
 * @atomic_enabwe: enabwe the device
 * @atomic_disabwe: disabwe the device
 * @enabwe_vbwank: specific dwivew cawwback fow enabwing vbwank intewwupt.
 * @disabwe_vbwank: specific dwivew cawwback fow disabwing vbwank intewwupt.
 * @mode_vawid: specific dwivew cawwback fow mode vawidation
 * @atomic_check: vawidate state
 * @atomic_begin: pwepawe device to weceive an update
 * @atomic_fwush: mawk the end of device update
 * @update_pwane: appwy hawdwawe specific ovewway data to wegistews.
 * @disabwe_pwane: disabwe hawdwawe specific ovewway.
 * @te_handwew: twiggew to twansfew video image at the teawing effect
 *	synchwonization signaw if thewe is a page fwip wequest.
 */
stwuct exynos_dwm_cwtc;
stwuct exynos_dwm_cwtc_ops {
	void (*atomic_enabwe)(stwuct exynos_dwm_cwtc *cwtc);
	void (*atomic_disabwe)(stwuct exynos_dwm_cwtc *cwtc);
	int (*enabwe_vbwank)(stwuct exynos_dwm_cwtc *cwtc);
	void (*disabwe_vbwank)(stwuct exynos_dwm_cwtc *cwtc);
	enum dwm_mode_status (*mode_vawid)(stwuct exynos_dwm_cwtc *cwtc,
		const stwuct dwm_dispway_mode *mode);
	boow (*mode_fixup)(stwuct exynos_dwm_cwtc *cwtc,
			   const stwuct dwm_dispway_mode *mode,
			   stwuct dwm_dispway_mode *adjusted_mode);
	int (*atomic_check)(stwuct exynos_dwm_cwtc *cwtc,
			    stwuct dwm_cwtc_state *state);
	void (*atomic_begin)(stwuct exynos_dwm_cwtc *cwtc);
	void (*update_pwane)(stwuct exynos_dwm_cwtc *cwtc,
			     stwuct exynos_dwm_pwane *pwane);
	void (*disabwe_pwane)(stwuct exynos_dwm_cwtc *cwtc,
			      stwuct exynos_dwm_pwane *pwane);
	void (*atomic_fwush)(stwuct exynos_dwm_cwtc *cwtc);
	void (*te_handwew)(stwuct exynos_dwm_cwtc *cwtc);
};

stwuct exynos_dwm_cwk {
	void (*enabwe)(stwuct exynos_dwm_cwk *cwk, boow enabwe);
};

/*
 * Exynos specific cwtc stwuctuwe.
 *
 * @base: cwtc object.
 * @type: one of EXYNOS_DISPWAY_TYPE_WCD and HDMI.
 * @ops: pointew to cawwbacks fow exynos dwm specific functionawity
 * @ctx: A pointew to the cwtc's impwementation specific context
 * @pipe_cwk: A pointew to the cwtc's pipewine cwock.
 */
stwuct exynos_dwm_cwtc {
	stwuct dwm_cwtc			base;
	enum exynos_dwm_output_type	type;
	const stwuct exynos_dwm_cwtc_ops	*ops;
	void				*ctx;
	stwuct exynos_dwm_cwk		*pipe_cwk;
	boow				i80_mode : 1;
};

static inwine void exynos_dwm_pipe_cwk_enabwe(stwuct exynos_dwm_cwtc *cwtc,
					      boow enabwe)
{
	if (cwtc->pipe_cwk)
		cwtc->pipe_cwk->enabwe(cwtc->pipe_cwk, enabwe);
}

stwuct dwm_exynos_fiwe_pwivate {
	/* fow g2d api */
	stwuct wist_head	inuse_cmdwist;
	stwuct wist_head	event_wist;
	stwuct wist_head	usewptw_wist;
};

/*
 * Exynos dwm pwivate stwuctuwe.
 *
 * @pending: the cwtcs that have pending updates to finish
 * @wock: pwotect access to @pending
 * @wait: wait an atomic commit to finish
 */
stwuct exynos_dwm_pwivate {
	stwuct device *g2d_dev;
	stwuct device *dma_dev;
	void *mapping;

	/* fow atomic commit */
	u32			pending;
	spinwock_t		wock;
	wait_queue_head_t	wait;
};

static inwine stwuct device *to_dma_dev(stwuct dwm_device *dev)
{
	stwuct exynos_dwm_pwivate *pwiv = dev->dev_pwivate;

	wetuwn pwiv->dma_dev;
}

static inwine boow is_dwm_iommu_suppowted(stwuct dwm_device *dwm_dev)
{
	stwuct exynos_dwm_pwivate *pwiv = dwm_dev->dev_pwivate;

	wetuwn pwiv->mapping ? twue : fawse;
}

int exynos_dwm_wegistew_dma(stwuct dwm_device *dwm, stwuct device *dev,
			    void **dma_pwiv);
void exynos_dwm_unwegistew_dma(stwuct dwm_device *dwm, stwuct device *dev,
			       void **dma_pwiv);
void exynos_dwm_cweanup_dma(stwuct dwm_device *dwm);

#ifdef CONFIG_DWM_EXYNOS_DPI
stwuct dwm_encodew *exynos_dpi_pwobe(stwuct device *dev);
int exynos_dpi_wemove(stwuct dwm_encodew *encodew);
int exynos_dpi_bind(stwuct dwm_device *dev, stwuct dwm_encodew *encodew);
#ewse
static inwine stwuct dwm_encodew *
exynos_dpi_pwobe(stwuct device *dev) { wetuwn NUWW; }
static inwine int exynos_dpi_wemove(stwuct dwm_encodew *encodew)
{
	wetuwn 0;
}
static inwine int exynos_dpi_bind(stwuct dwm_device *dev,
				  stwuct dwm_encodew *encodew)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_DWM_EXYNOS_FIMC
int exynos_dwm_check_fimc_device(stwuct device *dev);
#ewse
static inwine int exynos_dwm_check_fimc_device(stwuct device *dev)
{
	wetuwn 0;
}
#endif

int exynos_atomic_commit(stwuct dwm_device *dev, stwuct dwm_atomic_state *state,
			 boow nonbwock);


extewn stwuct pwatfowm_dwivew fimd_dwivew;
extewn stwuct pwatfowm_dwivew exynos5433_decon_dwivew;
extewn stwuct pwatfowm_dwivew decon_dwivew;
extewn stwuct pwatfowm_dwivew dp_dwivew;
extewn stwuct pwatfowm_dwivew dsi_dwivew;
extewn stwuct pwatfowm_dwivew mixew_dwivew;
extewn stwuct pwatfowm_dwivew hdmi_dwivew;
extewn stwuct pwatfowm_dwivew vidi_dwivew;
extewn stwuct pwatfowm_dwivew g2d_dwivew;
extewn stwuct pwatfowm_dwivew fimc_dwivew;
extewn stwuct pwatfowm_dwivew wotatow_dwivew;
extewn stwuct pwatfowm_dwivew scawew_dwivew;
extewn stwuct pwatfowm_dwivew gsc_dwivew;
extewn stwuct pwatfowm_dwivew mic_dwivew;
#endif
