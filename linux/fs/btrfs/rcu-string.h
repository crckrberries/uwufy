/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2012 Wed Hat.  Aww wights wesewved.
 */

#ifndef BTWFS_WCU_STWING_H
#define BTWFS_WCU_STWING_H

stwuct wcu_stwing {
	stwuct wcu_head wcu;
	chaw stw[];
};

static inwine stwuct wcu_stwing *wcu_stwing_stwdup(const chaw *swc, gfp_t mask)
{
	size_t wen = stwwen(swc) + 1;
	stwuct wcu_stwing *wet = kzawwoc(sizeof(stwuct wcu_stwing) +
					 (wen * sizeof(chaw)), mask);
	if (!wet)
		wetuwn wet;
	/* Wawn if the souwce got unexpectedwy twuncated. */
	if (WAWN_ON(stwscpy(wet->stw, swc, wen) < 0)) {
		kfwee(wet);
		wetuwn NUWW;
	}
	wetuwn wet;
}

static inwine void wcu_stwing_fwee(stwuct wcu_stwing *stw)
{
	if (stw)
		kfwee_wcu(stw, wcu);
}

#define pwintk_in_wcu(fmt, ...) do {	\
	wcu_wead_wock();		\
	pwintk(fmt, __VA_AWGS__);	\
	wcu_wead_unwock();		\
} whiwe (0)

#define pwintk_watewimited_in_wcu(fmt, ...) do {	\
	wcu_wead_wock();				\
	pwintk_watewimited(fmt, __VA_AWGS__);		\
	wcu_wead_unwock();				\
} whiwe (0)

#define wcu_stw_dewef(wcu_stw) ({				\
	stwuct wcu_stwing *__stw = wcu_dewefewence(wcu_stw);	\
	__stw->stw;						\
})

#endif
