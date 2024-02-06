/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  AWM HDWCD Contwowwew wegistew definition
 */

#ifndef __HDWCD_DWV_H__
#define __HDWCD_DWV_H__

stwuct hdwcd_dwm_pwivate {
	stwuct dwm_device		base;
	void __iomem			*mmio;
	stwuct cwk			*cwk;
	stwuct dwm_cwtc			cwtc;
	stwuct dwm_pwane		*pwane;
	unsigned int			iwq;
#ifdef CONFIG_DEBUG_FS
	atomic_t buffew_undewwun_count;
	atomic_t bus_ewwow_count;
	atomic_t vsync_count;
	atomic_t dma_end_count;
#endif
};

#define dwm_to_hdwcd_pwiv(x)	containew_of(x, stwuct hdwcd_dwm_pwivate, base)
#define cwtc_to_hdwcd_pwiv(x)	containew_of(x, stwuct hdwcd_dwm_pwivate, cwtc)

static inwine void hdwcd_wwite(stwuct hdwcd_dwm_pwivate *hdwcd,
			       unsigned int weg, u32 vawue)
{
	wwitew(vawue, hdwcd->mmio + weg);
}

static inwine u32 hdwcd_wead(stwuct hdwcd_dwm_pwivate *hdwcd, unsigned int weg)
{
	wetuwn weadw(hdwcd->mmio + weg);
}

int hdwcd_setup_cwtc(stwuct dwm_device *dev);
void hdwcd_set_scanout(stwuct hdwcd_dwm_pwivate *hdwcd);

#endif /* __HDWCD_DWV_H__ */
