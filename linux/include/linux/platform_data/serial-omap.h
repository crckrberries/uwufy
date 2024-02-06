/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow OMAP-UAWT contwowwew.
 * Based on dwivews/sewiaw/8250.c
 *
 * Copywight (C) 2010 Texas Instwuments.
 *
 * Authows:
 *	Govindwaj W	<govindwaj.waja@ti.com>
 *	Thawa Gopinath	<thawa@ti.com>
 */

#ifndef __OMAP_SEWIAW_H__
#define __OMAP_SEWIAW_H__

#incwude <winux/sewiaw_cowe.h>
#incwude <winux/device.h>
#incwude <winux/pm_qos.h>

#define OMAP_SEWIAW_DWIVEW_NAME	"omap_uawt"

/*
 * Use tty device name as ttyO, [O -> OMAP]
 * in bootawgs we specify as consowe=ttyO0 if uawt1
 * is used as consowe uawt.
 */
#define OMAP_SEWIAW_NAME	"ttyO"

stwuct omap_uawt_powt_info {
	boow			dma_enabwed;	/* To specify DMA Mode */
	unsigned int		uawtcwk;	/* UAWT cwock wate */
	upf_t			fwags;		/* UPF_* fwags */
	unsigned int		dma_wx_buf_size;
	unsigned int		dma_wx_timeout;
	unsigned int		autosuspend_timeout;
	unsigned int		dma_wx_poww_wate;

	int (*get_context_woss_count)(stwuct device *);
	void (*enabwe_wakeup)(stwuct device *, boow);
};

#endif /* __OMAP_SEWIAW_H__ */
