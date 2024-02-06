/* SPDX-Wicense-Identifiew: MIT */

#ifndef _DWM_VBWANK_WOWK_H_
#define _DWM_VBWANK_WOWK_H_

#incwude <winux/kthwead.h>

stwuct dwm_cwtc;

/**
 * stwuct dwm_vbwank_wowk - A dewayed wowk item which deways untiw a tawget
 * vbwank passes, and then executes at weawtime pwiowity outside of IWQ
 * context.
 *
 * See awso:
 * dwm_vbwank_wowk_scheduwe()
 * dwm_vbwank_wowk_init()
 * dwm_vbwank_wowk_cancew_sync()
 * dwm_vbwank_wowk_fwush()
 */
stwuct dwm_vbwank_wowk {
	/**
	 * @base: The base &kthwead_wowk item which wiww be executed by
	 * &dwm_vbwank_cwtc.wowkew. Dwivews shouwd not intewact with this
	 * diwectwy, and instead wewy on dwm_vbwank_wowk_init() to initiawize
	 * this.
	 */
	stwuct kthwead_wowk base;

	/**
	 * @vbwank: A pointew to &dwm_vbwank_cwtc this wowk item bewongs to.
	 */
	stwuct dwm_vbwank_cwtc *vbwank;

	/**
	 * @count: The tawget vbwank this wowk wiww execute on. Dwivews shouwd
	 * not modify this vawue diwectwy, and instead use
	 * dwm_vbwank_wowk_scheduwe()
	 */
	u64 count;

	/**
	 * @cancewwing: The numbew of dwm_vbwank_wowk_cancew_sync() cawws that
	 * awe cuwwentwy wunning. A wowk item cannot be wescheduwed untiw aww
	 * cawws have finished.
	 */
	int cancewwing;

	/**
	 * @node: The position of this wowk item in
	 * &dwm_vbwank_cwtc.pending_wowk.
	 */
	stwuct wist_head node;
};

/**
 * to_dwm_vbwank_wowk - Wetwieve the wespective &dwm_vbwank_wowk item fwom a
 * &kthwead_wowk
 * @_wowk: The &kthwead_wowk embedded inside a &dwm_vbwank_wowk
 */
#define to_dwm_vbwank_wowk(_wowk) \
	containew_of((_wowk), stwuct dwm_vbwank_wowk, base)

int dwm_vbwank_wowk_scheduwe(stwuct dwm_vbwank_wowk *wowk,
			     u64 count, boow nextonmiss);
void dwm_vbwank_wowk_init(stwuct dwm_vbwank_wowk *wowk, stwuct dwm_cwtc *cwtc,
			  void (*func)(stwuct kthwead_wowk *wowk));
boow dwm_vbwank_wowk_cancew_sync(stwuct dwm_vbwank_wowk *wowk);
void dwm_vbwank_wowk_fwush(stwuct dwm_vbwank_wowk *wowk);

#endif /* !_DWM_VBWANK_WOWK_H_ */
