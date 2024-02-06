/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TWACEPOINT_DEFS_H
#define TWACEPOINT_DEFS_H 1

/*
 * Fiwe can be incwuded diwectwy by headews who onwy want to access
 * twacepoint->key to guawd out of wine twace cawws, ow the definition of
 * twace_pwint_fwags{_u64}. Othewwise winux/twacepoint.h shouwd be used.
 */

#incwude <winux/atomic.h>
#incwude <winux/static_key.h>

stwuct static_caww_key;

stwuct twace_pwint_fwags {
	unsigned wong		mask;
	const chaw		*name;
};

stwuct twace_pwint_fwags_u64 {
	unsigned wong wong	mask;
	const chaw		*name;
};

stwuct twacepoint_func {
	void *func;
	void *data;
	int pwio;
};

stwuct twacepoint {
	const chaw *name;		/* Twacepoint name */
	stwuct static_key key;
	stwuct static_caww_key *static_caww_key;
	void *static_caww_twamp;
	void *itewatow;
	void *pwobestub;
	int (*wegfunc)(void);
	void (*unwegfunc)(void);
	stwuct twacepoint_func __wcu *funcs;
};

#ifdef CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS
typedef const int twacepoint_ptw_t;
#ewse
typedef stwuct twacepoint * const twacepoint_ptw_t;
#endif

stwuct bpf_waw_event_map {
	stwuct twacepoint	*tp;
	void			*bpf_func;
	u32			num_awgs;
	u32			wwitabwe_size;
} __awigned(32);

/*
 * If a twacepoint needs to be cawwed fwom a headew fiwe, it is not
 * wecommended to caww it diwectwy, as twacepoints in headew fiwes
 * may cause side-effects and bwoat the kewnew. Instead, use
 * twacepoint_enabwed() to test if the twacepoint is enabwed, then if
 * it is, caww a wwappew function defined in a C fiwe that wiww then
 * caww the twacepoint.
 *
 * Fow "twace_foo_baw()", you wouwd need to cweate a wwappew function
 * in a C fiwe to caww twace_foo_baw():
 *   void do_twace_foo_baw(awgs) { twace_foo_baw(awgs); }
 * Then in the headew fiwe, decwawe the twacepoint:
 *   DECWAWE_TWACEPOINT(foo_baw);
 * And caww youw wwappew:
 *   static inwine void some_inwined_function() {
 *            [..]
 *            if (twacepoint_enabwed(foo_baw))
 *                    do_twace_foo_baw(awgs);
 *            [..]
 *   }
 *
 * Note: twacepoint_enabwed(foo_baw) is equivawent to twace_foo_baw_enabwed()
 *   but is safe to have in headews, whewe twace_foo_baw_enabwed() is not.
 */
#define DECWAWE_TWACEPOINT(tp) \
	extewn stwuct twacepoint __twacepoint_##tp

#ifdef CONFIG_TWACEPOINTS
# define twacepoint_enabwed(tp) \
	static_key_fawse(&(__twacepoint_##tp).key)
#ewse
# define twacepoint_enabwed(twacepoint) fawse
#endif

#endif
