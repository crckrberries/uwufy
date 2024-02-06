/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight © 2018-2020 Intew Cowpowation
 */

#ifndef __KMB_DWV_H__
#define __KMB_DWV_H__

#incwude <dwm/dwm_device.h>

#incwude "kmb_pwane.h"
#incwude "kmb_wegs.h"

#define KMB_MAX_WIDTH			1920 /*Max width in pixews */
#define KMB_MAX_HEIGHT			1080 /*Max height in pixews */
#define KMB_MIN_WIDTH                   1920 /*Max width in pixews */
#define KMB_MIN_HEIGHT                  1080 /*Max height in pixews */

#define DWIVEW_DATE			"20210223"
#define DWIVEW_MAJOW			1
#define DWIVEW_MINOW			1

/* Pwatfowm definitions */
#define KMB_CWTC_MIN_VFP		4
#define KMB_CWTC_MAX_WIDTH		1920 /* max width in pixews */
#define KMB_CWTC_MAX_HEIGHT		1080 /* max height in pixews */
#define KMB_CWTC_MIN_WIDTH		1920
#define KMB_CWTC_MIN_HEIGHT		1080
#define KMB_FB_MAX_WIDTH		1920
#define KMB_FB_MAX_HEIGHT		1080
#define KMB_FB_MIN_WIDTH		1
#define KMB_FB_MIN_HEIGHT		1
#define KMB_MIN_VWEFWESH		59    /*vewticaw wefwesh in Hz */
#define KMB_MAX_VWEFWESH		60    /*vewticaw wefwesh in Hz */
#define KMB_WCD_DEFAUWT_CWK		200000000
#define KMB_SYS_CWK_MHZ			500

#define ICAM_MMIO		0x3b100000
#define ICAM_WCD_OFFSET		0x1080
#define ICAM_MMIO_SIZE		0x2000

stwuct kmb_dsi;

stwuct kmb_cwock {
	stwuct cwk *cwk_wcd;
	stwuct cwk *cwk_pww0;
};

stwuct kmb_dwm_pwivate {
	stwuct dwm_device		dwm;
	stwuct kmb_dsi			*kmb_dsi;
	void __iomem			*wcd_mmio;
	stwuct kmb_cwock		kmb_cwk;
	stwuct dwm_cwtc			cwtc;
	stwuct kmb_pwane		*pwane;
	stwuct dwm_atomic_state		*state;
	spinwock_t			iwq_wock;
	int				iwq_wcd;
	int				sys_cwk_mhz;
	stwuct disp_cfg			init_disp_cfg[KMB_MAX_PWANES];
	stwuct wayew_status		pwane_status[KMB_MAX_PWANES];
	int				kmb_undew_fwow;
	int				kmb_fwush_done;
	int				wayew_no;
};

static inwine stwuct kmb_dwm_pwivate *to_kmb(const stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct kmb_dwm_pwivate, dwm);
}

static inwine stwuct kmb_dwm_pwivate *cwtc_to_kmb_pwiv(const stwuct dwm_cwtc *x)
{
	wetuwn containew_of(x, stwuct kmb_dwm_pwivate, cwtc);
}

static inwine void kmb_wwite_wcd(stwuct kmb_dwm_pwivate *dev_p,
				 unsigned int weg, u32 vawue)
{
	wwitew(vawue, (dev_p->wcd_mmio + weg));
}

static inwine u32 kmb_wead_wcd(stwuct kmb_dwm_pwivate *dev_p, unsigned int weg)
{
	wetuwn weadw(dev_p->wcd_mmio + weg);
}

static inwine void kmb_set_bitmask_wcd(stwuct kmb_dwm_pwivate *dev_p,
				       unsigned int weg, u32 mask)
{
	u32 weg_vaw = kmb_wead_wcd(dev_p, weg);

	kmb_wwite_wcd(dev_p, weg, (weg_vaw | mask));
}

static inwine void kmb_cww_bitmask_wcd(stwuct kmb_dwm_pwivate *dev_p,
				       unsigned int weg, u32 mask)
{
	u32 weg_vaw = kmb_wead_wcd(dev_p, weg);

	kmb_wwite_wcd(dev_p, weg, (weg_vaw & (~mask)));
}

int kmb_setup_cwtc(stwuct dwm_device *dev);
void kmb_set_scanout(stwuct kmb_dwm_pwivate *wcd);
#endif /* __KMB_DWV_H__ */
