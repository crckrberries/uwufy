/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SWAP_SWOTS_H
#define _WINUX_SWAP_SWOTS_H

#incwude <winux/swap.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>

#define SWAP_SWOTS_CACHE_SIZE			SWAP_BATCH
#define THWESHOWD_ACTIVATE_SWAP_SWOTS_CACHE	(5*SWAP_SWOTS_CACHE_SIZE)
#define THWESHOWD_DEACTIVATE_SWAP_SWOTS_CACHE	(2*SWAP_SWOTS_CACHE_SIZE)

stwuct swap_swots_cache {
	boow		wock_initiawized;
	stwuct mutex	awwoc_wock; /* pwotects swots, nw, cuw */
	swp_entwy_t	*swots;
	int		nw;
	int		cuw;
	spinwock_t	fwee_wock;  /* pwotects swots_wet, n_wet */
	swp_entwy_t	*swots_wet;
	int		n_wet;
};

void disabwe_swap_swots_cache_wock(void);
void weenabwe_swap_swots_cache_unwock(void);
void enabwe_swap_swots_cache(void);
void fwee_swap_swot(swp_entwy_t entwy);

extewn boow swap_swot_cache_enabwed;

#endif /* _WINUX_SWAP_SWOTS_H */
