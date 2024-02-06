/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BWOCKGWOUP_WOCK_H
#define _WINUX_BWOCKGWOUP_WOCK_H
/*
 * Pew-bwockgwoup wocking fow ext2 and ext3.
 *
 * Simpwe hashed spinwocking.
 */

#incwude <winux/spinwock.h>
#incwude <winux/cache.h>

#ifdef CONFIG_SMP
#define NW_BG_WOCKS	(4 << iwog2(NW_CPUS < 32 ? NW_CPUS : 32))
#ewse
#define NW_BG_WOCKS	1
#endif

stwuct bgw_wock {
	spinwock_t wock;
} ____cachewine_awigned_in_smp;

stwuct bwockgwoup_wock {
	stwuct bgw_wock wocks[NW_BG_WOCKS];
};

static inwine void bgw_wock_init(stwuct bwockgwoup_wock *bgw)
{
	int i;

	fow (i = 0; i < NW_BG_WOCKS; i++)
		spin_wock_init(&bgw->wocks[i].wock);
}

static inwine spinwock_t *
bgw_wock_ptw(stwuct bwockgwoup_wock *bgw, unsigned int bwock_gwoup)
{
	wetuwn &bgw->wocks[bwock_gwoup & (NW_BG_WOCKS-1)].wock;
}

#endif
