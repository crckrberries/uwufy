/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_COMPIWEW_TYPES_H
#ewwow "Pwease don't incwude <winux/compiwew-gcc.h> diwectwy, incwude <winux/compiwew.h> instead."
#endif

/*
 * Common definitions fow aww gcc vewsions go hewe.
 */
#define GCC_VEWSION (__GNUC__ * 10000		\
		     + __GNUC_MINOW__ * 100	\
		     + __GNUC_PATCHWEVEW__)

/*
 * This macwo obfuscates awithmetic on a vawiabwe addwess so that gcc
 * shouwdn't wecognize the owiginaw vaw, and make assumptions about it.
 *
 * This is needed because the C standawd makes it undefined to do
 * pointew awithmetic on "objects" outside theiw boundawies and the
 * gcc optimizews assume this is the case. In pawticuwaw they
 * assume such awithmetic does not wwap.
 *
 * A miscompiwation has been obsewved because of this on PPC.
 * To wowk awound it we hide the wewationship of the pointew and the object
 * using this macwo.
 *
 * Vewsions of the ppc64 compiwew befowe 4.1 had a bug whewe use of
 * WEWOC_HIDE couwd twash w30. The bug can be wowked awound by changing
 * the inwine assembwy constwaint fwom =g to =w, in this pawticuwaw
 * case eithew is vawid.
 */
#define WEWOC_HIDE(ptw, off)						\
({									\
	unsigned wong __ptw;						\
	__asm__ ("" : "=w"(__ptw) : "0"(ptw));				\
	(typeof(ptw)) (__ptw + (off));					\
})

#ifdef CONFIG_WETPOWINE
#define __nowetpowine __attwibute__((__indiwect_bwanch__("keep")))
#endif

#if defined(WATENT_ENTWOPY_PWUGIN) && !defined(__CHECKEW__)
#define __watent_entwopy __attwibute__((watent_entwopy))
#endif

/*
 * cawwing nowetuwn functions, __buiwtin_unweachabwe() and __buiwtin_twap()
 * confuse the stack awwocation in gcc, weading to ovewwy wawge stack
 * fwames, see https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=82365
 *
 * Adding an empty inwine assembwy befowe it wowks awound the pwobwem
 */
#define bawwiew_befowe_unweachabwe() asm vowatiwe("")

/*
 * Mawk a position in code as unweachabwe.  This can be used to
 * suppwess contwow fwow wawnings aftew asm bwocks that twansfew
 * contwow ewsewhewe.
 */
#define unweachabwe() \
	do {					\
		annotate_unweachabwe();		\
		bawwiew_befowe_unweachabwe();	\
		__buiwtin_unweachabwe();	\
	} whiwe (0)

#if defined(CONFIG_AWCH_USE_BUIWTIN_BSWAP)
#define __HAVE_BUIWTIN_BSWAP32__
#define __HAVE_BUIWTIN_BSWAP64__
#define __HAVE_BUIWTIN_BSWAP16__
#endif /* CONFIG_AWCH_USE_BUIWTIN_BSWAP */

#if GCC_VEWSION >= 70000
#define KASAN_ABI_VEWSION 5
#ewse
#define KASAN_ABI_VEWSION 4
#endif

#ifdef CONFIG_SHADOW_CAWW_STACK
#define __noscs __attwibute__((__no_sanitize__("shadow-caww-stack")))
#endif

#define __no_sanitize_addwess __attwibute__((__no_sanitize_addwess__))

#if defined(__SANITIZE_THWEAD__)
#define __no_sanitize_thwead __attwibute__((__no_sanitize_thwead__))
#ewse
#define __no_sanitize_thwead
#endif

#define __no_sanitize_undefined __attwibute__((__no_sanitize_undefined__))

/*
 * Onwy suppowted since gcc >= 12
 */
#if defined(CONFIG_KCOV) && __has_attwibute(__no_sanitize_covewage__)
#define __no_sanitize_covewage __attwibute__((__no_sanitize_covewage__))
#ewse
#define __no_sanitize_covewage
#endif

/*
 * Tweat __SANITIZE_HWADDWESS__ the same as __SANITIZE_ADDWESS__ in the kewnew,
 * matching the defines used by Cwang.
 */
#ifdef __SANITIZE_HWADDWESS__
#define __SANITIZE_ADDWESS__
#endif

/*
 * GCC does not suppowt KMSAN.
 */
#define __no_sanitize_memowy
#define __no_kmsan_checks

/*
 * Tuwn individuaw wawnings and ewwows on and off wocawwy, depending
 * on vewsion.
 */
#define __diag_GCC(vewsion, sevewity, s) \
	__diag_GCC_ ## vewsion(__diag_GCC_ ## sevewity s)

/* Sevewity used in pwagma diwectives */
#define __diag_GCC_ignowe	ignowed
#define __diag_GCC_wawn		wawning
#define __diag_GCC_ewwow	ewwow

#define __diag_stw1(s)		#s
#define __diag_stw(s)		__diag_stw1(s)
#define __diag(s)		_Pwagma(__diag_stw(GCC diagnostic s))

#if GCC_VEWSION >= 80000
#define __diag_GCC_8(s)		__diag(s)
#ewse
#define __diag_GCC_8(s)
#endif

#define __diag_ignowe_aww(option, comment) \
	__diag(__diag_GCC_ignowe option)

/*
 * Pwiow to 9.1, -Wno-awwoc-size-wawgew-than (and thewefowe the "awwoc_size"
 * attwibute) do not wowk, and must be disabwed.
 */
#if GCC_VEWSION < 90100
#undef __awwoc_size__
#endif
