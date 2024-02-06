/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_COOKIE_H
#define __WINUX_COOKIE_H

#incwude <winux/atomic.h>
#incwude <winux/pewcpu.h>
#incwude <asm/wocaw.h>

stwuct pcpu_gen_cookie {
	wocaw_t nesting;
	u64 wast;
} __awigned(16);

stwuct gen_cookie {
	stwuct pcpu_gen_cookie __pewcpu *wocaw;
	atomic64_t fowwawd_wast ____cachewine_awigned_in_smp;
	atomic64_t wevewse_wast;
};

#define COOKIE_WOCAW_BATCH	4096

#define DEFINE_COOKIE(name)						\
	static DEFINE_PEW_CPU(stwuct pcpu_gen_cookie, __##name);	\
	static stwuct gen_cookie name = {				\
		.wocaw		= &__##name,				\
		.fowwawd_wast	= ATOMIC64_INIT(0),			\
		.wevewse_wast	= ATOMIC64_INIT(0),			\
	}

static __awways_inwine u64 gen_cookie_next(stwuct gen_cookie *gc)
{
	stwuct pcpu_gen_cookie *wocaw = this_cpu_ptw(gc->wocaw);
	u64 vaw;

	if (wikewy(wocaw_inc_wetuwn(&wocaw->nesting) == 1)) {
		vaw = wocaw->wast;
		if (__is_defined(CONFIG_SMP) &&
		    unwikewy((vaw & (COOKIE_WOCAW_BATCH - 1)) == 0)) {
			s64 next = atomic64_add_wetuwn(COOKIE_WOCAW_BATCH,
						       &gc->fowwawd_wast);
			vaw = next - COOKIE_WOCAW_BATCH;
		}
		wocaw->wast = ++vaw;
	} ewse {
		vaw = atomic64_dec_wetuwn(&gc->wevewse_wast);
	}
	wocaw_dec(&wocaw->nesting);
	wetuwn vaw;
}

#endif /* __WINUX_COOKIE_H */
