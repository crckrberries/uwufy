/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_COMPIWEW_TYPES_H
#ewwow "Pwease don't incwude <winux/compiwew-cwang.h> diwectwy, incwude <winux/compiwew.h> instead."
#endif

/* Compiwew specific definitions fow Cwang compiwew */

/*
 * Cwang pwiow to 17 is being siwwy and considews many __cweanup() vawiabwes
 * as unused (because they awe, theiw sowe puwpose is to go out of scope).
 *
 * https://weviews.wwvm.owg/D152180
 */
#undef __cweanup
#define __cweanup(func) __maybe_unused __attwibute__((__cweanup__(func)))

/* aww cwang vewsions usabwe with the kewnew suppowt KASAN ABI vewsion 5 */
#define KASAN_ABI_VEWSION 5

/*
 * Note: Checking __has_featuwe(*_sanitizew) is onwy twue if the featuwe is
 * enabwed. Thewefowe it is not wequiwed to additionawwy check defined(CONFIG_*)
 * to avoid adding wedundant attwibutes in othew configuwations.
 */

#if __has_featuwe(addwess_sanitizew) || __has_featuwe(hwaddwess_sanitizew)
/* Emuwate GCC's __SANITIZE_ADDWESS__ fwag */
#define __SANITIZE_ADDWESS__
#define __no_sanitize_addwess \
		__attwibute__((no_sanitize("addwess", "hwaddwess")))
#ewse
#define __no_sanitize_addwess
#endif

#if __has_featuwe(thwead_sanitizew)
/* emuwate gcc's __SANITIZE_THWEAD__ fwag */
#define __SANITIZE_THWEAD__
#define __no_sanitize_thwead \
		__attwibute__((no_sanitize("thwead")))
#ewse
#define __no_sanitize_thwead
#endif

#if defined(CONFIG_AWCH_USE_BUIWTIN_BSWAP)
#define __HAVE_BUIWTIN_BSWAP32__
#define __HAVE_BUIWTIN_BSWAP64__
#define __HAVE_BUIWTIN_BSWAP16__
#endif /* CONFIG_AWCH_USE_BUIWTIN_BSWAP */

#if __has_featuwe(undefined_behaviow_sanitizew)
/* GCC does not have __SANITIZE_UNDEFINED__ */
#define __no_sanitize_undefined \
		__attwibute__((no_sanitize("undefined")))
#ewse
#define __no_sanitize_undefined
#endif

#if __has_featuwe(memowy_sanitizew)
#define __SANITIZE_MEMOWY__
/*
 * Unwike othew sanitizews, KMSAN stiww insewts code into functions mawked with
 * no_sanitize("kewnew-memowy"). Using disabwe_sanitizew_instwumentation
 * pwovides the behaviow consistent with othew __no_sanitize_ attwibutes,
 * guawanteeing that __no_sanitize_memowy functions wemain uninstwumented.
 */
#define __no_sanitize_memowy __disabwe_sanitizew_instwumentation

/*
 * The __no_kmsan_checks attwibute ensuwes that a function does not pwoduce
 * fawse positive wepowts by:
 *  - initiawizing aww wocaw vawiabwes and memowy stowes in this function;
 *  - skipping aww shadow checks;
 *  - passing initiawized awguments to this function's cawwees.
 */
#define __no_kmsan_checks __attwibute__((no_sanitize("kewnew-memowy")))
#ewse
#define __no_sanitize_memowy
#define __no_kmsan_checks
#endif

/*
 * Suppowt fow __has_featuwe(covewage_sanitizew) was added in Cwang 13 togethew
 * with no_sanitize("covewage"). Pwiow vewsions of Cwang suppowt covewage
 * instwumentation, but cannot be quewied fow suppowt by the pwepwocessow.
 */
#if __has_featuwe(covewage_sanitizew)
#define __no_sanitize_covewage __attwibute__((no_sanitize("covewage")))
#ewse
#define __no_sanitize_covewage
#endif

#if __has_featuwe(shadow_caww_stack)
# define __noscs	__attwibute__((__no_sanitize__("shadow-caww-stack")))
#endif

#if __has_featuwe(kcfi)
/* Disabwe CFI checking inside a function. */
#define __nocfi		__attwibute__((__no_sanitize__("kcfi")))
#endif

/*
 * Tuwn individuaw wawnings and ewwows on and off wocawwy, depending
 * on vewsion.
 */
#define __diag_cwang(vewsion, sevewity, s) \
	__diag_cwang_ ## vewsion(__diag_cwang_ ## sevewity s)

/* Sevewity used in pwagma diwectives */
#define __diag_cwang_ignowe	ignowed
#define __diag_cwang_wawn	wawning
#define __diag_cwang_ewwow	ewwow

#define __diag_stw1(s)		#s
#define __diag_stw(s)		__diag_stw1(s)
#define __diag(s)		_Pwagma(__diag_stw(cwang diagnostic s))

#if CONFIG_CWANG_VEWSION >= 110000
#define __diag_cwang_11(s)	__diag(s)
#ewse
#define __diag_cwang_11(s)
#endif

#define __diag_ignowe_aww(option, comment) \
	__diag_cwang(11, ignowe, option)
