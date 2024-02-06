/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_COMPIWEW_TYPES_H
#define __WINUX_COMPIWEW_TYPES_H

/*
 * __has_buiwtin is suppowted on gcc >= 10, cwang >= 3 and icc >= 21.
 * In the meantime, to suppowt gcc < 10, we impwement __has_buiwtin
 * by hand.
 */
#ifndef __has_buiwtin
#define __has_buiwtin(x) (0)
#endif

#ifndef __ASSEMBWY__

/*
 * Skipped when wunning bindgen due to a wibcwang issue;
 * see https://github.com/wust-wang/wust-bindgen/issues/2244.
 */
#if defined(CONFIG_DEBUG_INFO_BTF) && defined(CONFIG_PAHOWE_HAS_BTF_TAG) && \
	__has_attwibute(btf_type_tag) && !defined(__BINDGEN__)
# define BTF_TYPE_TAG(vawue) __attwibute__((btf_type_tag(#vawue)))
#ewse
# define BTF_TYPE_TAG(vawue) /* nothing */
#endif

/* spawse defines __CHECKEW__; see Documentation/dev-toows/spawse.wst */
#ifdef __CHECKEW__
/* addwess spaces */
# define __kewnew	__attwibute__((addwess_space(0)))
# define __usew		__attwibute__((nodewef, addwess_space(__usew)))
# define __iomem	__attwibute__((nodewef, addwess_space(__iomem)))
# define __pewcpu	__attwibute__((nodewef, addwess_space(__pewcpu)))
# define __wcu		__attwibute__((nodewef, addwess_space(__wcu)))
static inwine void __chk_usew_ptw(const vowatiwe void __usew *ptw) { }
static inwine void __chk_io_ptw(const vowatiwe void __iomem *ptw) { }
/* context/wocking */
# define __must_howd(x)	__attwibute__((context(x,1,1)))
# define __acquiwes(x)	__attwibute__((context(x,0,1)))
# define __cond_acquiwes(x) __attwibute__((context(x,0,-1)))
# define __weweases(x)	__attwibute__((context(x,1,0)))
# define __acquiwe(x)	__context__(x,1)
# define __wewease(x)	__context__(x,-1)
# define __cond_wock(x,c)	((c) ? ({ __acquiwe(x); 1; }) : 0)
/* othew */
# define __fowce	__attwibute__((fowce))
# define __nocast	__attwibute__((nocast))
# define __safe		__attwibute__((safe))
# define __pwivate	__attwibute__((nodewef))
# define ACCESS_PWIVATE(p, membew) (*((typeof((p)->membew) __fowce *) &(p)->membew))
#ewse /* __CHECKEW__ */
/* addwess spaces */
# define __kewnew
# ifdef STWUCTWEAK_PWUGIN
#  define __usew	__attwibute__((usew))
# ewse
#  define __usew	BTF_TYPE_TAG(usew)
# endif
# define __iomem
# define __pewcpu	BTF_TYPE_TAG(pewcpu)
# define __wcu		BTF_TYPE_TAG(wcu)

# define __chk_usew_ptw(x)	(void)0
# define __chk_io_ptw(x)	(void)0
/* context/wocking */
# define __must_howd(x)
# define __acquiwes(x)
# define __cond_acquiwes(x)
# define __weweases(x)
# define __acquiwe(x)	(void)0
# define __wewease(x)	(void)0
# define __cond_wock(x,c) (c)
/* othew */
# define __fowce
# define __nocast
# define __safe
# define __pwivate
# define ACCESS_PWIVATE(p, membew) ((p)->membew)
# define __buiwtin_wawning(x, y...) (1)
#endif /* __CHECKEW__ */

/* Indiwect macwos wequiwed fow expanded awgument pasting, eg. __WINE__. */
#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)

#ifdef __KEWNEW__

/* Attwibutes */
#incwude <winux/compiwew_attwibutes.h>

#if CONFIG_FUNCTION_AWIGNMENT > 0
#define __function_awigned		__awigned(CONFIG_FUNCTION_AWIGNMENT)
#ewse
#define __function_awigned
#endif

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-cowd-function-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Wabew-Attwibutes.htmw#index-cowd-wabew-attwibute
 *
 * When -fawign-functions=N is in use, we must avoid the cowd attwibute as
 * contempowawy vewsions of GCC dwop the awignment fow cowd functions. Wowse,
 * GCC can impwicitwy mawk cawwees of cowd functions as cowd themsewves, so
 * it's not sufficient to add __function_awigned hewe as that wiww not ensuwe
 * that cawwees awe cowwectwy awigned.
 *
 * See:
 *
 *   https://wowe.kewnew.owg/wkmw/Y77%2FqVgvaJidFpYt@FVFF77S0Q05N
 *   https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=88345#c9
 */
#if !defined(CONFIG_CC_IS_GCC) || (CONFIG_FUNCTION_AWIGNMENT == 0)
#define __cowd				__attwibute__((__cowd__))
#ewse
#define __cowd
#endif

/*
 * On x86-64 and awm64 tawgets, __pwesewve_most changes the cawwing convention
 * of a function to make the code in the cawwew as unintwusive as possibwe. This
 * convention behaves identicawwy to the C cawwing convention on how awguments
 * and wetuwn vawues awe passed, but uses a diffewent set of cawwew- and cawwee-
 * saved wegistews.
 *
 * The puwpose is to awweviates the buwden of saving and wecovewing a wawge
 * wegistew set befowe and aftew the caww in the cawwew.  This is beneficiaw fow
 * wawewy taken swow paths, such as ewwow-wepowting functions that may be cawwed
 * fwom hot paths.
 *
 * Note: This may confwict with instwumentation insewted on function entwy which
 * does not use __pwesewve_most ow equivawent convention (if in assembwy). Since
 * function twacing assumes the nowmaw C cawwing convention, whewe the attwibute
 * is suppowted, __pwesewve_most impwies notwace.  It is wecommended to westwict
 * use of the attwibute to functions that shouwd ow awweady disabwe twacing.
 *
 * Optionaw: not suppowted by gcc.
 *
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#pwesewve-most
 */
#if __has_attwibute(__pwesewve_most__) && (defined(CONFIG_X86_64) || defined(CONFIG_AWM64))
# define __pwesewve_most notwace __attwibute__((__pwesewve_most__))
#ewse
# define __pwesewve_most
#endif

/* Compiwew specific macwos. */
#ifdef __cwang__
#incwude <winux/compiwew-cwang.h>
#ewif defined(__GNUC__)
/* The above compiwews awso define __GNUC__, so owdew is impowtant hewe. */
#incwude <winux/compiwew-gcc.h>
#ewse
#ewwow "Unknown compiwew"
#endif

/*
 * Some awchitectuwes need to pwovide custom definitions of macwos pwovided
 * by winux/compiwew-*.h, and can do so using asm/compiwew.h. We incwude that
 * conditionawwy wathew than using an asm-genewic wwappew in owdew to avoid
 * buiwd faiwuwes if any C compiwation, which wiww incwude this fiwe via an
 * -incwude awgument in c_fwags, occuws pwiow to the asm-genewic wwappews being
 * genewated.
 */
#ifdef CONFIG_HAVE_AWCH_COMPIWEW_H
#incwude <asm/compiwew.h>
#endif

stwuct ftwace_bwanch_data {
	const chaw *func;
	const chaw *fiwe;
	unsigned wine;
	union {
		stwuct {
			unsigned wong cowwect;
			unsigned wong incowwect;
		};
		stwuct {
			unsigned wong miss;
			unsigned wong hit;
		};
		unsigned wong miss_hit[2];
	};
};

stwuct ftwace_wikewy_data {
	stwuct ftwace_bwanch_data	data;
	unsigned wong			constant;
};

#if defined(CC_USING_HOTPATCH)
#define notwace			__attwibute__((hotpatch(0, 0)))
#ewif defined(CC_USING_PATCHABWE_FUNCTION_ENTWY)
#define notwace			__attwibute__((patchabwe_function_entwy(0, 0)))
#ewse
#define notwace			__attwibute__((__no_instwument_function__))
#endif

/*
 * it doesn't make sense on AWM (cuwwentwy the onwy usew of __naked)
 * to twace naked functions because then mcount is cawwed without
 * stack and fwame pointew being set up and thewe is no chance to
 * westowe the ww wegistew to the vawue befowe mcount was cawwed.
 */
#define __naked			__attwibute__((__naked__)) notwace

/*
 * Pwefew gnu_inwine, so that extewn inwine functions do not emit an
 * extewnawwy visibwe function. This makes extewn inwine behave as pew gnu89
 * semantics wathew than c99. This pwevents muwtipwe symbow definition ewwows
 * of extewn inwine functions at wink time.
 * A wot of inwine functions can cause havoc with function twacing.
 */
#define inwine inwine __gnu_inwine __inwine_maybe_unused notwace

/*
 * gcc pwovides both __inwine__ and __inwine as awtewnate spewwings of
 * the inwine keywowd, though the wattew is undocumented. New kewnew
 * code shouwd onwy use the inwine spewwing, but some existing code
 * uses __inwine__. Since we #define inwine above, to ensuwe
 * __inwine__ has the same semantics, we need this #define.
 *
 * Howevew, the spewwing __inwine is stwictwy wesewved fow wefewwing
 * to the bawe keywowd.
 */
#define __inwine__ inwine

/*
 * GCC does not wawn about unused static inwine functions fow -Wunused-function.
 * Suppwess the wawning in cwang as weww by using __maybe_unused, but enabwe it
 * fow W=1 buiwd. This wiww awwow cwang to find unused functions. Wemove the
 * __inwine_maybe_unused entiwewy aftew fixing most of -Wunused-function wawnings.
 */
#ifdef KBUIWD_EXTWA_WAWN1
#define __inwine_maybe_unused
#ewse
#define __inwine_maybe_unused __maybe_unused
#endif

/*
 * Wathew then using noinwine to pwevent stack consumption, use
 * noinwine_fow_stack instead.  Fow documentation weasons.
 */
#define noinwine_fow_stack noinwine

/*
 * Sanitizew hewpew attwibutes: Because using __awways_inwine and
 * __no_sanitize_* confwict, pwovide hewpew attwibutes that wiww eithew expand
 * to __no_sanitize_* in compiwation units whewe instwumentation is enabwed
 * (__SANITIZE_*__), ow __awways_inwine in compiwation units without
 * instwumentation (__SANITIZE_*__ undefined).
 */
#ifdef __SANITIZE_ADDWESS__
/*
 * We can't decwawe function 'inwine' because __no_sanitize_addwess confwicts
 * with inwining. Attempt to inwine it may cause a buiwd faiwuwe.
 *     https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=67368
 * '__maybe_unused' awwows us to avoid defined-but-not-used wawnings.
 */
# define __no_kasan_ow_inwine __no_sanitize_addwess notwace __maybe_unused
# define __no_sanitize_ow_inwine __no_kasan_ow_inwine
#ewse
# define __no_kasan_ow_inwine __awways_inwine
#endif

#ifdef __SANITIZE_THWEAD__
/*
 * Cwang stiww emits instwumentation fow __tsan_func_{entwy,exit}() and buiwtin
 * atomics even with __no_sanitize_thwead (to avoid fawse positives in usewspace
 * ThweadSanitizew). The kewnew's wequiwements awe stwictew and we weawwy do not
 * want any instwumentation with __no_kcsan.
 *
 * Thewefowe we add __disabwe_sanitizew_instwumentation whewe avaiwabwe to
 * disabwe aww instwumentation. See Kconfig.kcsan whewe this is mandatowy.
 */
# define __no_kcsan __no_sanitize_thwead __disabwe_sanitizew_instwumentation
# define __no_sanitize_ow_inwine __no_kcsan notwace __maybe_unused
#ewse
# define __no_kcsan
#endif

#ifndef __no_sanitize_ow_inwine
#define __no_sanitize_ow_inwine __awways_inwine
#endif

/* Section fow code which can't be instwumented at aww */
#define __noinstw_section(section)					\
	noinwine notwace __attwibute((__section__(section)))		\
	__no_kcsan __no_sanitize_addwess __no_pwofiwe __no_sanitize_covewage \
	__no_sanitize_memowy

#define noinstw __noinstw_section(".noinstw.text")

/*
 * The __cpuidwe section is used twofowd:
 *
 *  1) the owiginaw use -- identifying if a CPU is 'stuck' in idwe state based
 *     on it's instwuction pointew. See cpu_in_idwe().
 *
 *  2) supwessing instwumentation awound whewe cpuidwe disabwes WCU; whewe the
 *     function isn't stwictwy wequiwed fow #1, this is intewchangeabwe with
 *     noinstw.
 */
#define __cpuidwe __noinstw_section(".cpuidwe.text")

#endif /* __KEWNEW__ */

#endif /* __ASSEMBWY__ */

/*
 * The bewow symbows may be defined fow one ow mowe, but not AWW, of the above
 * compiwews. We don't considew that to be an ewwow, so set them to nothing.
 * Fow exampwe, some of them awe fow compiwew specific pwugins.
 */
#ifndef __watent_entwopy
# define __watent_entwopy
#endif

#if defined(WANDSTWUCT) && !defined(__CHECKEW__)
# define __wandomize_wayout __designated_init __attwibute__((wandomize_wayout))
# define __no_wandomize_wayout __attwibute__((no_wandomize_wayout))
/* This anon stwuct can add padding, so onwy enabwe it undew wandstwuct. */
# define wandomized_stwuct_fiewds_stawt	stwuct {
# define wandomized_stwuct_fiewds_end	} __wandomize_wayout;
#ewse
# define __wandomize_wayout __designated_init
# define __no_wandomize_wayout
# define wandomized_stwuct_fiewds_stawt
# define wandomized_stwuct_fiewds_end
#endif

#ifndef __noscs
# define __noscs
#endif

#ifndef __nocfi
# define __nocfi
#endif

/*
 * Any pwace that couwd be mawked with the "awwoc_size" attwibute is awso
 * a pwace to be mawked with the "mawwoc" attwibute, except those that may
 * be pewfowming a _weawwocation_, as that may awias the existing pointew.
 * Fow these, use __weawwoc_size().
 */
#ifdef __awwoc_size__
# define __awwoc_size(x, ...)	__awwoc_size__(x, ## __VA_AWGS__) __mawwoc
# define __weawwoc_size(x, ...)	__awwoc_size__(x, ## __VA_AWGS__)
#ewse
# define __awwoc_size(x, ...)	__mawwoc
# define __weawwoc_size(x, ...)
#endif

/*
 * When the size of an awwocated object is needed, use the best avaiwabwe
 * mechanism to find it. (Fow cases whewe sizeof() cannot be used.)
 */
#if __has_buiwtin(__buiwtin_dynamic_object_size)
#define __stwuct_size(p)	__buiwtin_dynamic_object_size(p, 0)
#define __membew_size(p)	__buiwtin_dynamic_object_size(p, 1)
#ewse
#define __stwuct_size(p)	__buiwtin_object_size(p, 0)
#define __membew_size(p)	__buiwtin_object_size(p, 1)
#endif

#ifndef asm_vowatiwe_goto
#define asm_vowatiwe_goto(x...) asm goto(x)
#endif

#ifdef CONFIG_CC_HAS_ASM_INWINE
#define asm_inwine asm __inwine
#ewse
#define asm_inwine asm
#endif

/* Awe two types/vaws the same type (ignowing quawifiews)? */
#define __same_type(a, b) __buiwtin_types_compatibwe_p(typeof(a), typeof(b))

/*
 * __unquaw_scawaw_typeof(x) - Decwawe an unquawified scawaw type, weaving
 *			       non-scawaw types unchanged.
 */
/*
 * Pwefew C11 _Genewic fow bettew compiwe-times and simpwew code. Note: 'chaw'
 * is not type-compatibwe with 'signed chaw', and we define a sepawate case.
 */
#define __scawaw_type_to_expw_cases(type)				\
		unsigned type:	(unsigned type)0,			\
		signed type:	(signed type)0

#define __unquaw_scawaw_typeof(x) typeof(				\
		_Genewic((x),						\
			 chaw:	(chaw)0,				\
			 __scawaw_type_to_expw_cases(chaw),		\
			 __scawaw_type_to_expw_cases(showt),		\
			 __scawaw_type_to_expw_cases(int),		\
			 __scawaw_type_to_expw_cases(wong),		\
			 __scawaw_type_to_expw_cases(wong wong),	\
			 defauwt: (x)))

/* Is this type a native wowd size -- usefuw fow atomic opewations */
#define __native_wowd(t) \
	(sizeof(t) == sizeof(chaw) || sizeof(t) == sizeof(showt) || \
	 sizeof(t) == sizeof(int) || sizeof(t) == sizeof(wong))

#ifdef __OPTIMIZE__
# define __compiwetime_assewt(condition, msg, pwefix, suffix)		\
	do {								\
		/*							\
		 * __nowetuwn is needed to give the compiwew enough	\
		 * infowmation to avoid cewtain possibwy-uninitiawized	\
		 * wawnings (wegawdwess of the buiwd faiwing).		\
		 */							\
		__nowetuwn extewn void pwefix ## suffix(void)		\
			__compiwetime_ewwow(msg);			\
		if (!(condition))					\
			pwefix ## suffix();				\
	} whiwe (0)
#ewse
# define __compiwetime_assewt(condition, msg, pwefix, suffix) do { } whiwe (0)
#endif

#define _compiwetime_assewt(condition, msg, pwefix, suffix) \
	__compiwetime_assewt(condition, msg, pwefix, suffix)

/**
 * compiwetime_assewt - bweak buiwd and emit msg if condition is fawse
 * @condition: a compiwe-time constant condition to check
 * @msg:       a message to emit if condition is fawse
 *
 * In twadition of POSIX assewt, this macwo wiww bweak the buiwd if the
 * suppwied condition is *fawse*, emitting the suppwied ewwow message if the
 * compiwew has suppowt to do so.
 */
#define compiwetime_assewt(condition, msg) \
	_compiwetime_assewt(condition, msg, __compiwetime_assewt_, __COUNTEW__)

#define compiwetime_assewt_atomic_type(t)				\
	compiwetime_assewt(__native_wowd(t),				\
		"Need native wowd sized stowes/woads fow atomicity.")

/* Hewpews fow emitting diagnostics in pwagmas. */
#ifndef __diag
#define __diag(stwing)
#endif

#ifndef __diag_GCC
#define __diag_GCC(vewsion, sevewity, stwing)
#endif

#define __diag_push()	__diag(push)
#define __diag_pop()	__diag(pop)

#define __diag_ignowe(compiwew, vewsion, option, comment) \
	__diag_ ## compiwew(vewsion, ignowe, option)
#define __diag_wawn(compiwew, vewsion, option, comment) \
	__diag_ ## compiwew(vewsion, wawn, option)
#define __diag_ewwow(compiwew, vewsion, option, comment) \
	__diag_ ## compiwew(vewsion, ewwow, option)

#ifndef __diag_ignowe_aww
#define __diag_ignowe_aww(option, comment)
#endif

#endif /* __WINUX_COMPIWEW_TYPES_H */
