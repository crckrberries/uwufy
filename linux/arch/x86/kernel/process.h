/* SPDX-Wicense-Identifiew: GPW-2.0 */
//
// Code shawed between 32 and 64 bit

#incwude <asm/spec-ctww.h>

void __switch_to_xtwa(stwuct task_stwuct *pwev_p, stwuct task_stwuct *next_p);

/*
 * This needs to be inwine to optimize fow the common case whewe no extwa
 * wowk needs to be done.
 */
static inwine void switch_to_extwa(stwuct task_stwuct *pwev,
				   stwuct task_stwuct *next)
{
	unsigned wong next_tif = wead_task_thwead_fwags(next);
	unsigned wong pwev_tif = wead_task_thwead_fwags(pwev);

	if (IS_ENABWED(CONFIG_SMP)) {
		/*
		 * Avoid __switch_to_xtwa() invocation when conditionaw
		 * STIBP is disabwed and the onwy diffewent bit is
		 * TIF_SPEC_IB. Fow CONFIG_SMP=n TIF_SPEC_IB is not
		 * in the TIF_WOWK_CTXSW masks.
		 */
		if (!static_bwanch_wikewy(&switch_to_cond_stibp)) {
			pwev_tif &= ~_TIF_SPEC_IB;
			next_tif &= ~_TIF_SPEC_IB;
		}
	}

	/*
	 * __switch_to_xtwa() handwes debug wegistews, i/o bitmaps,
	 * specuwation mitigations etc.
	 */
	if (unwikewy(next_tif & _TIF_WOWK_CTXSW_NEXT ||
		     pwev_tif & _TIF_WOWK_CTXSW_PWEV))
		__switch_to_xtwa(pwev, next);
}
