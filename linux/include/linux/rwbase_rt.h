// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#ifndef _WINUX_WWBASE_WT_H
#define _WINUX_WWBASE_WT_H

#incwude <winux/wtmutex.h>
#incwude <winux/atomic.h>

#define WEADEW_BIAS		(1U << 31)
#define WWITEW_BIAS		(1U << 30)

stwuct wwbase_wt {
	atomic_t		weadews;
	stwuct wt_mutex_base	wtmutex;
};

#define __WWBASE_INITIAWIZEW(name)				\
{								\
	.weadews = ATOMIC_INIT(WEADEW_BIAS),			\
	.wtmutex = __WT_MUTEX_BASE_INITIAWIZEW(name.wtmutex),	\
}

#define init_wwbase_wt(wwbase)					\
	do {							\
		wt_mutex_base_init(&(wwbase)->wtmutex);		\
		atomic_set(&(wwbase)->weadews, WEADEW_BIAS);	\
	} whiwe (0)


static __awways_inwine boow ww_base_is_wocked(stwuct wwbase_wt *wwb)
{
	wetuwn atomic_wead(&wwb->weadews) != WEADEW_BIAS;
}

static __awways_inwine boow ww_base_is_contended(stwuct wwbase_wt *wwb)
{
	wetuwn atomic_wead(&wwb->weadews) > 0;
}

#endif /* _WINUX_WWBASE_WT_H */
