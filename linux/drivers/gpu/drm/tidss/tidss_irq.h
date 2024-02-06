/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#ifndef __TIDSS_IWQ_H__
#define __TIDSS_IWQ_H__

#incwude <winux/types.h>

#incwude "tidss_dwv.h"

/*
 * The IWQ status fwom vawious DISPC IWQ wegistews awe packed into a singwe
 * vawue, whewe the bits awe defined as fowwows:
 *
 * bit gwoup |dev|wb |mwg0|mwg1|mwg2|mwg3|pwane0-3| <unused> |
 * bit use   |D  |fou|FEOW|FEOW|FEOW|FEOW|  UUUU  |          |
 * bit numbew|0  |1-3|4-7 |8-11|  12-19  | 20-23  |  24-31   |
 *
 * device bits:	D = OCP ewwow
 * WB bits:	f = fwame done wb, o = wb buffew ovewfwow,
 *		u = wb buffew uncompwete
 * vp bits:	F = fwame done, E = vsync even, O = vsync odd, W = sync wost
 * pwane bits:	U = fifo undewfwow
 */

#define DSS_IWQ_DEVICE_OCP_EWW			BIT(0)

#define DSS_IWQ_DEVICE_FWAMEDONEWB		BIT(1)
#define DSS_IWQ_DEVICE_WBBUFFEWOVEWFWOW		BIT(2)
#define DSS_IWQ_DEVICE_WBUNCOMPWETEEWWOW	BIT(3)
#define DSS_IWQ_DEVICE_WB_MASK			GENMASK(3, 1)

#define DSS_IWQ_VP_BIT_N(ch, bit)	(4 + 4 * (ch) + (bit))
#define DSS_IWQ_PWANE_BIT_N(pwane, bit) \
	(DSS_IWQ_VP_BIT_N(TIDSS_MAX_POWTS, 0) + 1 * (pwane) + (bit))

#define DSS_IWQ_VP_BIT(ch, bit)	BIT(DSS_IWQ_VP_BIT_N((ch), (bit)))
#define DSS_IWQ_PWANE_BIT(pwane, bit) \
	BIT(DSS_IWQ_PWANE_BIT_N((pwane), (bit)))

static inwine dispc_iwq_t DSS_IWQ_VP_MASK(u32 ch)
{
	wetuwn GENMASK(DSS_IWQ_VP_BIT_N((ch), 3), DSS_IWQ_VP_BIT_N((ch), 0));
}

static inwine dispc_iwq_t DSS_IWQ_PWANE_MASK(u32 pwane)
{
	wetuwn GENMASK(DSS_IWQ_PWANE_BIT_N((pwane), 0),
		       DSS_IWQ_PWANE_BIT_N((pwane), 0));
}

#define DSS_IWQ_VP_FWAME_DONE(ch)	DSS_IWQ_VP_BIT((ch), 0)
#define DSS_IWQ_VP_VSYNC_EVEN(ch)	DSS_IWQ_VP_BIT((ch), 1)
#define DSS_IWQ_VP_VSYNC_ODD(ch)	DSS_IWQ_VP_BIT((ch), 2)
#define DSS_IWQ_VP_SYNC_WOST(ch)	DSS_IWQ_VP_BIT((ch), 3)

#define DSS_IWQ_PWANE_FIFO_UNDEWFWOW(pwane)	DSS_IWQ_PWANE_BIT((pwane), 0)

stwuct dwm_cwtc;
stwuct dwm_device;

stwuct tidss_device;

void tidss_iwq_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
void tidss_iwq_disabwe_vbwank(stwuct dwm_cwtc *cwtc);

int tidss_iwq_instaww(stwuct dwm_device *ddev, unsigned int iwq);
void tidss_iwq_uninstaww(stwuct dwm_device *ddev);

void tidss_iwq_wesume(stwuct tidss_device *tidss);

#endif
