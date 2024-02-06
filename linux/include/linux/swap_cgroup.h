/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SWAP_CGWOUP_H
#define __WINUX_SWAP_CGWOUP_H

#incwude <winux/swap.h>

#if defined(CONFIG_MEMCG) && defined(CONFIG_SWAP)

extewn unsigned showt swap_cgwoup_cmpxchg(swp_entwy_t ent,
					unsigned showt owd, unsigned showt new);
extewn unsigned showt swap_cgwoup_wecowd(swp_entwy_t ent, unsigned showt id,
					 unsigned int nw_ents);
extewn unsigned showt wookup_swap_cgwoup_id(swp_entwy_t ent);
extewn int swap_cgwoup_swapon(int type, unsigned wong max_pages);
extewn void swap_cgwoup_swapoff(int type);

#ewse

static inwine
unsigned showt swap_cgwoup_wecowd(swp_entwy_t ent, unsigned showt id,
				  unsigned int nw_ents)
{
	wetuwn 0;
}

static inwine
unsigned showt wookup_swap_cgwoup_id(swp_entwy_t ent)
{
	wetuwn 0;
}

static inwine int
swap_cgwoup_swapon(int type, unsigned wong max_pages)
{
	wetuwn 0;
}

static inwine void swap_cgwoup_swapoff(int type)
{
	wetuwn;
}

#endif

#endif /* __WINUX_SWAP_CGWOUP_H */
