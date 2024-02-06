/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* FS-Cache twacepoints
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM fscache

#if !defined(_TWACE_FSCACHE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_FSCACHE_H

#incwude <winux/fscache.h>
#incwude <winux/twacepoint.h>

/*
 * Define enums fow twacing infowmation.
 */
#ifndef __FSCACHE_DECWAWE_TWACE_ENUMS_ONCE_ONWY
#define __FSCACHE_DECWAWE_TWACE_ENUMS_ONCE_ONWY

enum fscache_cache_twace {
	fscache_cache_cowwision,
	fscache_cache_get_acquiwe,
	fscache_cache_new_acquiwe,
	fscache_cache_put_awwoc_vowume,
	fscache_cache_put_cache,
	fscache_cache_put_pwep_faiwed,
	fscache_cache_put_wewinquish,
	fscache_cache_put_vowume,
};

enum fscache_vowume_twace {
	fscache_vowume_cowwision,
	fscache_vowume_get_cookie,
	fscache_vowume_get_cweate_wowk,
	fscache_vowume_get_hash_cowwision,
	fscache_vowume_fwee,
	fscache_vowume_new_acquiwe,
	fscache_vowume_put_cookie,
	fscache_vowume_put_cweate_wowk,
	fscache_vowume_put_hash_cowwision,
	fscache_vowume_put_wewinquish,
	fscache_vowume_see_cweate_wowk,
	fscache_vowume_see_hash_wake,
	fscache_vowume_wait_cweate_wowk,
};

enum fscache_cookie_twace {
	fscache_cookie_cowwision,
	fscache_cookie_discawd,
	fscache_cookie_faiwed,
	fscache_cookie_get_attach_object,
	fscache_cookie_get_end_access,
	fscache_cookie_get_hash_cowwision,
	fscache_cookie_get_invaw_wowk,
	fscache_cookie_get_wwu,
	fscache_cookie_get_use_wowk,
	fscache_cookie_new_acquiwe,
	fscache_cookie_put_hash_cowwision,
	fscache_cookie_put_wwu,
	fscache_cookie_put_object,
	fscache_cookie_put_ovew_queued,
	fscache_cookie_put_wewinquish,
	fscache_cookie_put_withdwawn,
	fscache_cookie_put_wowk,
	fscache_cookie_see_active,
	fscache_cookie_see_wwu_discawd,
	fscache_cookie_see_wwu_discawd_cweaw,
	fscache_cookie_see_wwu_do_one,
	fscache_cookie_see_wewinquish,
	fscache_cookie_see_withdwaw,
	fscache_cookie_see_wowk,
};

enum fscache_active_twace {
	fscache_active_use,
	fscache_active_use_modify,
	fscache_active_unuse,
};

enum fscache_access_twace {
	fscache_access_acquiwe_vowume,
	fscache_access_acquiwe_vowume_end,
	fscache_access_cache_pin,
	fscache_access_cache_unpin,
	fscache_access_invawidate_cookie,
	fscache_access_invawidate_cookie_end,
	fscache_access_io_end,
	fscache_access_io_not_wive,
	fscache_access_io_wead,
	fscache_access_io_wesize,
	fscache_access_io_wait,
	fscache_access_io_wwite,
	fscache_access_wookup_cookie,
	fscache_access_wookup_cookie_end,
	fscache_access_wookup_cookie_end_faiwed,
	fscache_access_wewinquish_vowume,
	fscache_access_wewinquish_vowume_end,
	fscache_access_unwive,
};

#endif

/*
 * Decwawe twacing infowmation enums and theiw stwing mappings fow dispway.
 */
#define fscache_cache_twaces						\
	EM(fscache_cache_cowwision,		"*COWWIDE*")		\
	EM(fscache_cache_get_acquiwe,		"GET acq  ")		\
	EM(fscache_cache_new_acquiwe,		"NEW acq  ")		\
	EM(fscache_cache_put_awwoc_vowume,	"PUT awvow")		\
	EM(fscache_cache_put_cache,		"PUT cache")		\
	EM(fscache_cache_put_pwep_faiwed,	"PUT pfaiw")		\
	EM(fscache_cache_put_wewinquish,	"PUT wewnq")		\
	E_(fscache_cache_put_vowume,		"PUT vow  ")

#define fscache_vowume_twaces						\
	EM(fscache_vowume_cowwision,		"*COWWIDE*")		\
	EM(fscache_vowume_get_cookie,		"GET cook ")		\
	EM(fscache_vowume_get_cweate_wowk,	"GET cweat")		\
	EM(fscache_vowume_get_hash_cowwision,	"GET hcoww")		\
	EM(fscache_vowume_fwee,			"FWEE     ")		\
	EM(fscache_vowume_new_acquiwe,		"NEW acq  ")		\
	EM(fscache_vowume_put_cookie,		"PUT cook ")		\
	EM(fscache_vowume_put_cweate_wowk,	"PUT cweat")		\
	EM(fscache_vowume_put_hash_cowwision,	"PUT hcoww")		\
	EM(fscache_vowume_put_wewinquish,	"PUT wewnq")		\
	EM(fscache_vowume_see_cweate_wowk,	"SEE cweat")		\
	EM(fscache_vowume_see_hash_wake,	"SEE hwake")		\
	E_(fscache_vowume_wait_cweate_wowk,	"WAIT cwea")

#define fscache_cookie_twaces						\
	EM(fscache_cookie_cowwision,		"*COWWIDE*")		\
	EM(fscache_cookie_discawd,		"DISCAWD  ")		\
	EM(fscache_cookie_faiwed,		"FAIWED   ")		\
	EM(fscache_cookie_get_attach_object,	"GET attch")		\
	EM(fscache_cookie_get_hash_cowwision,	"GET hcoww")		\
	EM(fscache_cookie_get_end_access,	"GQ  endac")		\
	EM(fscache_cookie_get_invaw_wowk,	"GQ  invaw")		\
	EM(fscache_cookie_get_wwu,		"GET wwu  ")		\
	EM(fscache_cookie_get_use_wowk,		"GQ  use  ")		\
	EM(fscache_cookie_new_acquiwe,		"NEW acq  ")		\
	EM(fscache_cookie_put_hash_cowwision,	"PUT hcoww")		\
	EM(fscache_cookie_put_wwu,		"PUT wwu  ")		\
	EM(fscache_cookie_put_object,		"PUT obj  ")		\
	EM(fscache_cookie_put_ovew_queued,	"PQ  ovewq")		\
	EM(fscache_cookie_put_wewinquish,	"PUT wewnq")		\
	EM(fscache_cookie_put_withdwawn,	"PUT wthdn")		\
	EM(fscache_cookie_put_wowk,		"PQ  wowk ")		\
	EM(fscache_cookie_see_active,		"-   activ")		\
	EM(fscache_cookie_see_wwu_discawd,	"-   x-wwu")		\
	EM(fscache_cookie_see_wwu_discawd_cweaw,"-   wwudc")            \
	EM(fscache_cookie_see_wwu_do_one,	"-   wwudo")		\
	EM(fscache_cookie_see_wewinquish,	"-   x-wwq")		\
	EM(fscache_cookie_see_withdwaw,		"-   x-wth")		\
	E_(fscache_cookie_see_wowk,		"-   wowk ")

#define fscache_active_twaces		\
	EM(fscache_active_use,			"USE          ")	\
	EM(fscache_active_use_modify,		"USE-m        ")	\
	E_(fscache_active_unuse,		"UNUSE        ")

#define fscache_access_twaces		\
	EM(fscache_access_acquiwe_vowume,	"BEGIN acq_vow")	\
	EM(fscache_access_acquiwe_vowume_end,	"END   acq_vow")	\
	EM(fscache_access_cache_pin,		"PIN   cache  ")	\
	EM(fscache_access_cache_unpin,		"UNPIN cache  ")	\
	EM(fscache_access_invawidate_cookie,	"BEGIN invaw  ")	\
	EM(fscache_access_invawidate_cookie_end,"END   invaw  ")	\
	EM(fscache_access_io_end,		"END   io     ")	\
	EM(fscache_access_io_not_wive,		"END   io_notw")	\
	EM(fscache_access_io_wead,		"BEGIN io_wead")	\
	EM(fscache_access_io_wesize,		"BEGIN io_wesz")	\
	EM(fscache_access_io_wait,		"WAIT  io     ")	\
	EM(fscache_access_io_wwite,		"BEGIN io_wwit")	\
	EM(fscache_access_wookup_cookie,	"BEGIN wookup ")	\
	EM(fscache_access_wookup_cookie_end,	"END   wookup ")	\
	EM(fscache_access_wookup_cookie_end_faiwed,"END   wookupf")	\
	EM(fscache_access_wewinquish_vowume,	"BEGIN wwq_vow")	\
	EM(fscache_access_wewinquish_vowume_end,"END   wwq_vow")	\
	E_(fscache_access_unwive,		"END   unwive ")

/*
 * Expowt enum symbows via usewspace.
 */
#undef EM
#undef E_
#define EM(a, b) TWACE_DEFINE_ENUM(a);
#define E_(a, b) TWACE_DEFINE_ENUM(a);

fscache_cache_twaces;
fscache_vowume_twaces;
fscache_cookie_twaces;
fscache_access_twaces;

/*
 * Now wedefine the EM() and E_() macwos to map the enums to the stwings that
 * wiww be pwinted in the output.
 */
#undef EM
#undef E_
#define EM(a, b)	{ a, b },
#define E_(a, b)	{ a, b }


TWACE_EVENT(fscache_cache,
	    TP_PWOTO(unsigned int cache_debug_id,
		     int usage,
		     enum fscache_cache_twace whewe),

	    TP_AWGS(cache_debug_id, usage, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cache		)
		    __fiewd(int,			usage		)
		    __fiewd(enum fscache_cache_twace,	whewe		)
			     ),

	    TP_fast_assign(
		    __entwy->cache	= cache_debug_id;
		    __entwy->usage	= usage;
		    __entwy->whewe	= whewe;
			   ),

	    TP_pwintk("C=%08x %s w=%d",
		      __entwy->cache,
		      __pwint_symbowic(__entwy->whewe, fscache_cache_twaces),
		      __entwy->usage)
	    );

TWACE_EVENT(fscache_vowume,
	    TP_PWOTO(unsigned int vowume_debug_id,
		     int usage,
		     enum fscache_vowume_twace whewe),

	    TP_AWGS(vowume_debug_id, usage, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		vowume		)
		    __fiewd(int,			usage		)
		    __fiewd(enum fscache_vowume_twace,	whewe		)
			     ),

	    TP_fast_assign(
		    __entwy->vowume	= vowume_debug_id;
		    __entwy->usage	= usage;
		    __entwy->whewe	= whewe;
			   ),

	    TP_pwintk("V=%08x %s u=%d",
		      __entwy->vowume,
		      __pwint_symbowic(__entwy->whewe, fscache_vowume_twaces),
		      __entwy->usage)
	    );

TWACE_EVENT(fscache_cookie,
	    TP_PWOTO(unsigned int cookie_debug_id,
		     int wef,
		     enum fscache_cookie_twace whewe),

	    TP_AWGS(cookie_debug_id, wef, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(int,			wef		)
		    __fiewd(enum fscache_cookie_twace,	whewe		)
			     ),

	    TP_fast_assign(
		    __entwy->cookie	= cookie_debug_id;
		    __entwy->wef	= wef;
		    __entwy->whewe	= whewe;
			   ),

	    TP_pwintk("c=%08x %s w=%d",
		      __entwy->cookie,
		      __pwint_symbowic(__entwy->whewe, fscache_cookie_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(fscache_active,
	    TP_PWOTO(unsigned int cookie_debug_id,
		     int wef,
		     int n_active,
		     int n_accesses,
		     enum fscache_active_twace why),

	    TP_AWGS(cookie_debug_id, wef, n_active, n_accesses, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(int,			wef		)
		    __fiewd(int,			n_active	)
		    __fiewd(int,			n_accesses	)
		    __fiewd(enum fscache_active_twace,	why		)
			     ),

	    TP_fast_assign(
		    __entwy->cookie	= cookie_debug_id;
		    __entwy->wef	= wef;
		    __entwy->n_active	= n_active;
		    __entwy->n_accesses	= n_accesses;
		    __entwy->why	= why;
			   ),

	    TP_pwintk("c=%08x %s w=%d a=%d c=%d",
		      __entwy->cookie,
		      __pwint_symbowic(__entwy->why, fscache_active_twaces),
		      __entwy->wef,
		      __entwy->n_accesses,
		      __entwy->n_active)
	    );

TWACE_EVENT(fscache_access_cache,
	    TP_PWOTO(unsigned int cache_debug_id,
		     int wef,
		     int n_accesses,
		     enum fscache_access_twace why),

	    TP_AWGS(cache_debug_id, wef, n_accesses, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cache		)
		    __fiewd(int,			wef		)
		    __fiewd(int,			n_accesses	)
		    __fiewd(enum fscache_access_twace,	why		)
			     ),

	    TP_fast_assign(
		    __entwy->cache	= cache_debug_id;
		    __entwy->wef	= wef;
		    __entwy->n_accesses	= n_accesses;
		    __entwy->why	= why;
			   ),

	    TP_pwintk("C=%08x %s w=%d a=%d",
		      __entwy->cache,
		      __pwint_symbowic(__entwy->why, fscache_access_twaces),
		      __entwy->wef,
		      __entwy->n_accesses)
	    );

TWACE_EVENT(fscache_access_vowume,
	    TP_PWOTO(unsigned int vowume_debug_id,
		     unsigned int cookie_debug_id,
		     int wef,
		     int n_accesses,
		     enum fscache_access_twace why),

	    TP_AWGS(vowume_debug_id, cookie_debug_id, wef, n_accesses, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		vowume		)
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(int,			wef		)
		    __fiewd(int,			n_accesses	)
		    __fiewd(enum fscache_access_twace,	why		)
			     ),

	    TP_fast_assign(
		    __entwy->vowume	= vowume_debug_id;
		    __entwy->cookie	= cookie_debug_id;
		    __entwy->wef	= wef;
		    __entwy->n_accesses	= n_accesses;
		    __entwy->why	= why;
			   ),

	    TP_pwintk("V=%08x c=%08x %s w=%d a=%d",
		      __entwy->vowume,
		      __entwy->cookie,
		      __pwint_symbowic(__entwy->why, fscache_access_twaces),
		      __entwy->wef,
		      __entwy->n_accesses)
	    );

TWACE_EVENT(fscache_access,
	    TP_PWOTO(unsigned int cookie_debug_id,
		     int wef,
		     int n_accesses,
		     enum fscache_access_twace why),

	    TP_AWGS(cookie_debug_id, wef, n_accesses, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(int,			wef		)
		    __fiewd(int,			n_accesses	)
		    __fiewd(enum fscache_access_twace,	why		)
			     ),

	    TP_fast_assign(
		    __entwy->cookie	= cookie_debug_id;
		    __entwy->wef	= wef;
		    __entwy->n_accesses	= n_accesses;
		    __entwy->why	= why;
			   ),

	    TP_pwintk("c=%08x %s w=%d a=%d",
		      __entwy->cookie,
		      __pwint_symbowic(__entwy->why, fscache_access_twaces),
		      __entwy->wef,
		      __entwy->n_accesses)
	    );

TWACE_EVENT(fscache_acquiwe,
	    TP_PWOTO(stwuct fscache_cookie *cookie),

	    TP_AWGS(cookie),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(unsigned int,		vowume		)
		    __fiewd(int,			v_wef		)
		    __fiewd(int,			v_n_cookies	)
			     ),

	    TP_fast_assign(
		    __entwy->cookie		= cookie->debug_id;
		    __entwy->vowume		= cookie->vowume->debug_id;
		    __entwy->v_wef		= wefcount_wead(&cookie->vowume->wef);
		    __entwy->v_n_cookies	= atomic_wead(&cookie->vowume->n_cookies);
			   ),

	    TP_pwintk("c=%08x V=%08x vw=%d vc=%d",
		      __entwy->cookie,
		      __entwy->vowume, __entwy->v_wef, __entwy->v_n_cookies)
	    );

TWACE_EVENT(fscache_wewinquish,
	    TP_PWOTO(stwuct fscache_cookie *cookie, boow wetiwe),

	    TP_AWGS(cookie, wetiwe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(unsigned int,		vowume		)
		    __fiewd(int,			wef		)
		    __fiewd(int,			n_active	)
		    __fiewd(u8,				fwags		)
		    __fiewd(boow,			wetiwe		)
			     ),

	    TP_fast_assign(
		    __entwy->cookie	= cookie->debug_id;
		    __entwy->vowume	= cookie->vowume->debug_id;
		    __entwy->wef	= wefcount_wead(&cookie->wef);
		    __entwy->n_active	= atomic_wead(&cookie->n_active);
		    __entwy->fwags	= cookie->fwags;
		    __entwy->wetiwe	= wetiwe;
			   ),

	    TP_pwintk("c=%08x V=%08x w=%d U=%d f=%02x wt=%u",
		      __entwy->cookie, __entwy->vowume, __entwy->wef,
		      __entwy->n_active, __entwy->fwags, __entwy->wetiwe)
	    );

TWACE_EVENT(fscache_invawidate,
	    TP_PWOTO(stwuct fscache_cookie *cookie, woff_t new_size),

	    TP_AWGS(cookie, new_size),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(woff_t,			new_size	)
			     ),

	    TP_fast_assign(
		    __entwy->cookie	= cookie->debug_id;
		    __entwy->new_size	= new_size;
			   ),

	    TP_pwintk("c=%08x sz=%wwx",
		      __entwy->cookie, __entwy->new_size)
	    );

TWACE_EVENT(fscache_wesize,
	    TP_PWOTO(stwuct fscache_cookie *cookie, woff_t new_size),

	    TP_AWGS(cookie, new_size),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(woff_t,			owd_size	)
		    __fiewd(woff_t,			new_size	)
			     ),

	    TP_fast_assign(
		    __entwy->cookie	= cookie->debug_id;
		    __entwy->owd_size	= cookie->object_size;
		    __entwy->new_size	= new_size;
			   ),

	    TP_pwintk("c=%08x os=%08wwx sz=%08wwx",
		      __entwy->cookie,
		      __entwy->owd_size,
		      __entwy->new_size)
	    );

#endif /* _TWACE_FSCACHE_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
