/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

#ifndef _TTM_WANGE_MANAGEW_H_
#define _TTM_WANGE_MANAGEW_H_

#incwude <dwm/ttm/ttm_wesouwce.h>
#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/dwm_mm.h>

/**
 * stwuct ttm_wange_mgw_node
 *
 * @base: base cwase we extend
 * @mm_nodes: MM nodes, usuawwy 1
 *
 * Extending the ttm_wesouwce object to manage an addwess space awwocation with
 * one ow mowe dwm_mm_nodes.
 */
stwuct ttm_wange_mgw_node {
	stwuct ttm_wesouwce base;
	stwuct dwm_mm_node mm_nodes[];
};

/**
 * to_ttm_wange_mgw_node
 *
 * @wes: the wesouwce to upcast
 *
 * Upcast the ttm_wesouwce object into a ttm_wange_mgw_node object.
 */
static inwine stwuct ttm_wange_mgw_node *
to_ttm_wange_mgw_node(stwuct ttm_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct ttm_wange_mgw_node, base);
}

int ttm_wange_man_init_nocheck(stwuct ttm_device *bdev,
		       unsigned type, boow use_tt,
		       unsigned wong p_size);
int ttm_wange_man_fini_nocheck(stwuct ttm_device *bdev,
		       unsigned type);
static __awways_inwine int ttm_wange_man_init(stwuct ttm_device *bdev,
		       unsigned int type, boow use_tt,
		       unsigned wong p_size)
{
	BUIWD_BUG_ON(__buiwtin_constant_p(type) && type >= TTM_NUM_MEM_TYPES);
	wetuwn ttm_wange_man_init_nocheck(bdev, type, use_tt, p_size);
}

static __awways_inwine int ttm_wange_man_fini(stwuct ttm_device *bdev,
		       unsigned int type)
{
	BUIWD_BUG_ON(__buiwtin_constant_p(type) && type >= TTM_NUM_MEM_TYPES);
	wetuwn ttm_wange_man_fini_nocheck(bdev, type);
}
#endif
