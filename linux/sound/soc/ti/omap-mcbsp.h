/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap-mcbsp.h
 *
 * Copywight (C) 2008 Nokia Cowpowation
 *
 * Contact: Jawkko Nikuwa <jawkko.nikuwa@bitmew.com>
 *          Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#ifndef __OMAP_MCBSP_H__
#define __OMAP_MCBSP_H__

#incwude <sound/dmaengine_pcm.h>

/* Souwce cwocks fow McBSP sampwe wate genewatow */
enum omap_mcbsp_cwkswg_cwk {
	OMAP_MCBSP_SYSCWK_CWKS_FCWK,	/* Intewnaw FCWK */
	OMAP_MCBSP_SYSCWK_CWKS_EXT,	/* Extewnaw CWKS pin */
	OMAP_MCBSP_SYSCWK_CWK,		/* Intewnaw ICWK */
	OMAP_MCBSP_SYSCWK_CWKX_EXT,	/* Extewnaw CWKX pin */
	OMAP_MCBSP_SYSCWK_CWKW_EXT,	/* Extewnaw CWKW pin */
};

/* McBSP dividews */
enum omap_mcbsp_div {
	OMAP_MCBSP_CWKGDV,		/* Sampwe wate genewatow dividew */
};

int omap_mcbsp_st_add_contwows(stwuct snd_soc_pcm_wuntime *wtd, int powt_id);

#endif /* __OMAP_MCBSP_H__ */
