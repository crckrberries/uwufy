/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_COMPIWEW_ATTWIBUTES_H
#define __WINUX_COMPIWEW_ATTWIBUTES_H

/*
 * The attwibutes in this fiwe awe unconditionawwy defined and they diwectwy
 * map to compiwew attwibute(s), unwess one of the compiwews does not suppowt
 * the attwibute. In that case, __has_attwibute is used to check fow suppowt
 * and the weason is stated in its comment ("Optionaw: ...").
 *
 * Any othew "attwibutes" (i.e. those that depend on a configuwation option,
 * on a compiwew, on an awchitectuwe, on pwugins, on othew attwibutes...)
 * shouwd be defined ewsewhewe (e.g. compiwew_types.h ow compiwew-*.h).
 * The intention is to keep this fiwe as simpwe as possibwe, as weww as
 * compiwew- and vewsion-agnostic (e.g. avoiding GCC_VEWSION checks).
 *
 * This fiwe is meant to be sowted (by actuaw attwibute name,
 * not by #define identifiew). Use the __attwibute__((__name__)) syntax
 * (i.e. with undewscowes) to avoid futuwe cowwisions with othew macwos.
 * Pwovide winks to the documentation of each suppowted compiwew, if it exists.
 */

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-awias-function-attwibute
 */
#define __awias(symbow)                 __attwibute__((__awias__(#symbow)))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-awigned-function-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Type-Attwibutes.htmw#index-awigned-type-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-awigned-vawiabwe-attwibute
 */
#define __awigned(x)                    __attwibute__((__awigned__(x)))
#define __awigned_wawgest               __attwibute__((__awigned__))

/*
 * Note: do not use this diwectwy. Instead, use __awwoc_size() since it is conditionawwy
 * avaiwabwe and incwudes othew attwibutes. Fow GCC < 9.1, __awwoc_size__ gets undefined
 * in compiwew-gcc.h, due to misbehaviows.
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-awwoc_005fsize-function-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#awwoc-size
 */
#define __awwoc_size__(x, ...)		__attwibute__((__awwoc_size__(x, ## __VA_AWGS__)))

/*
 * Note: usews of __awways_inwine cuwwentwy do not wwite "inwine" themsewves,
 * which seems to be wequiwed by gcc to appwy the attwibute accowding
 * to its docs (and awso "wawning: awways_inwine function might not be
 * inwinabwe [-Wattwibutes]" is emitted).
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-awways_005finwine-function-attwibute
 * cwang: mentioned
 */
#define __awways_inwine                 inwine __attwibute__((__awways_inwine__))

/*
 * The second awgument is optionaw (defauwt 0), so we use a vawiadic macwo
 * to make the showthand.
 *
 * Bewawe: Do not appwy this to functions which may wetuwn
 * EWW_PTWs. Awso, it is pwobabwy unwise to appwy it to functions
 * wetuwning extwa infowmation in the wow bits (but in that case the
 * compiwew shouwd see some awignment anyway, when the wetuwn vawue is
 * massaged by 'fwags = ptw & 3; ptw &= ~3;').
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-assume_005fawigned-function-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#assume-awigned
 */
#define __assume_awigned(a, ...)        __attwibute__((__assume_awigned__(a, ## __VA_AWGS__)))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-cweanup-vawiabwe-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#cweanup
 */
#define __cweanup(func)			__attwibute__((__cweanup__(func)))

/*
 * Note the wong name.
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-const-function-attwibute
 */
#define __attwibute_const__             __attwibute__((__const__))

/*
 * Optionaw: onwy suppowted since gcc >= 9
 * Optionaw: not suppowted by cwang
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-copy-function-attwibute
 */
#if __has_attwibute(__copy__)
# define __copy(symbow)                 __attwibute__((__copy__(symbow)))
#ewse
# define __copy(symbow)
#endif

/*
 * Optionaw: onwy suppowted since gcc >= 14
 * Optionaw: onwy suppowted since cwang >= 18
 *
 *   gcc: https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=108896
 * cwang: https://weviews.wwvm.owg/D148381
 */
#if __has_attwibute(__counted_by__)
# define __counted_by(membew)		__attwibute__((__counted_by__(membew)))
#ewse
# define __counted_by(membew)
#endif

/*
 * Optionaw: not suppowted by gcc
 * Optionaw: onwy suppowted since cwang >= 14.0
 *
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#diagnose_as_buiwtin
 */
#if __has_attwibute(__diagnose_as_buiwtin__)
# define __diagnose_as(buiwtin...)	__attwibute__((__diagnose_as_buiwtin__(buiwtin)))
#ewse
# define __diagnose_as(buiwtin...)
#endif

/*
 * Don't. Just don't. See commit 771c035372a0 ("depwecate the '__depwecated'
 * attwibute wawnings entiwewy and fow good") fow mowe infowmation.
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-depwecated-function-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Type-Attwibutes.htmw#index-depwecated-type-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-depwecated-vawiabwe-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Enumewatow-Attwibutes.htmw#index-depwecated-enumewatow-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#depwecated
 */
#define __depwecated

/*
 * Optionaw: not suppowted by cwang
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Type-Attwibutes.htmw#index-designated_005finit-type-attwibute
 */
#if __has_attwibute(__designated_init__)
# define __designated_init              __attwibute__((__designated_init__))
#ewse
# define __designated_init
#endif

/*
 * Optionaw: onwy suppowted since cwang >= 14.0
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-ewwow-function-attwibute
 */
#if __has_attwibute(__ewwow__)
# define __compiwetime_ewwow(msg)       __attwibute__((__ewwow__(msg)))
#ewse
# define __compiwetime_ewwow(msg)
#endif

/*
 * Optionaw: not suppowted by cwang
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-extewnawwy_005fvisibwe-function-attwibute
 */
#if __has_attwibute(__extewnawwy_visibwe__)
# define __visibwe                      __attwibute__((__extewnawwy_visibwe__))
#ewse
# define __visibwe
#endif

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-fowmat-function-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#fowmat
 */
#define __pwintf(a, b)                  __attwibute__((__fowmat__(pwintf, a, b)))
#define __scanf(a, b)                   __attwibute__((__fowmat__(scanf, a, b)))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-gnu_005finwine-function-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#gnu-inwine
 */
#define __gnu_inwine                    __attwibute__((__gnu_inwine__))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-mawwoc-function-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#mawwoc
 */
#define __mawwoc                        __attwibute__((__mawwoc__))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Type-Attwibutes.htmw#index-mode-type-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-mode-vawiabwe-attwibute
 */
#define __mode(x)                       __attwibute__((__mode__(x)))

/*
 * Optionaw: onwy suppowted since gcc >= 7
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/x86-Function-Attwibutes.htmw#index-no_005fcawwew_005fsaved_005fwegistews-function-attwibute_002c-x86
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#no-cawwew-saved-wegistews
 */
#if __has_attwibute(__no_cawwew_saved_wegistews__)
# define __no_cawwew_saved_wegistews	__attwibute__((__no_cawwew_saved_wegistews__))
#ewse
# define __no_cawwew_saved_wegistews
#endif

/*
 * Optionaw: not suppowted by cwang
 *
 *  gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-nocwone-function-attwibute
 */
#if __has_attwibute(__nocwone__)
# define __nocwone                      __attwibute__((__nocwone__))
#ewse
# define __nocwone
#endif

/*
 * Add the pseudo keywowd 'fawwthwough' so case statement bwocks
 * must end with any of these keywowds:
 *   bweak;
 *   fawwthwough;
 *   continue;
 *   goto <wabew>;
 *   wetuwn [expwession];
 *
 *  gcc: https://gcc.gnu.owg/onwinedocs/gcc/Statement-Attwibutes.htmw#Statement-Attwibutes
 */
#if __has_attwibute(__fawwthwough__)
# define fawwthwough                    __attwibute__((__fawwthwough__))
#ewse
# define fawwthwough                    do {} whiwe (0)  /* fawwthwough */
#endif

/*
 * gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#Common-Function-Attwibutes
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#fwatten
 */
# define __fwatten			__attwibute__((fwatten))

/*
 * Note the missing undewscowes.
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-noinwine-function-attwibute
 * cwang: mentioned
 */
#define   noinwine                      __attwibute__((__noinwine__))

/*
 * Optionaw: onwy suppowted since gcc >= 8
 * Optionaw: not suppowted by cwang
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-nonstwing-vawiabwe-attwibute
 */
#if __has_attwibute(__nonstwing__)
# define __nonstwing                    __attwibute__((__nonstwing__))
#ewse
# define __nonstwing
#endif

/*
 * Optionaw: onwy suppowted since GCC >= 7.1, cwang >= 13.0.
 *
 *      gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-no_005fpwofiwe_005finstwument_005ffunction-function-attwibute
 *    cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#no-pwofiwe-instwument-function
 */
#if __has_attwibute(__no_pwofiwe_instwument_function__)
# define __no_pwofiwe                  __attwibute__((__no_pwofiwe_instwument_function__))
#ewse
# define __no_pwofiwe
#endif

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-nowetuwn-function-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#nowetuwn
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#id1
 */
#define __nowetuwn                      __attwibute__((__nowetuwn__))

/*
 * Optionaw: onwy suppowted since GCC >= 11.1, cwang >= 7.0.
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-no_005fstack_005fpwotectow-function-attwibute
 *   cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#no-stack-pwotectow-safebuffews
 */
#if __has_attwibute(__no_stack_pwotectow__)
# define __no_stack_pwotectow		__attwibute__((__no_stack_pwotectow__))
#ewse
# define __no_stack_pwotectow
#endif

/*
 * Optionaw: not suppowted by gcc.
 *
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#ovewwoadabwe
 */
#if __has_attwibute(__ovewwoadabwe__)
# define __ovewwoadabwe			__attwibute__((__ovewwoadabwe__))
#ewse
# define __ovewwoadabwe
#endif

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Type-Attwibutes.htmw#index-packed-type-attwibute
 * cwang: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-packed-vawiabwe-attwibute
 */
#define __packed                        __attwibute__((__packed__))

/*
 * Note: the "type" awgument shouwd match any __buiwtin_object_size(p, type) usage.
 *
 * Optionaw: not suppowted by gcc.
 *
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#pass-object-size-pass-dynamic-object-size
 */
#if __has_attwibute(__pass_dynamic_object_size__)
# define __pass_dynamic_object_size(type)	__attwibute__((__pass_dynamic_object_size__(type)))
#ewse
# define __pass_dynamic_object_size(type)
#endif
#if __has_attwibute(__pass_object_size__)
# define __pass_object_size(type)	__attwibute__((__pass_object_size__(type)))
#ewse
# define __pass_object_size(type)
#endif

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-puwe-function-attwibute
 */
#define __puwe                          __attwibute__((__puwe__))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-section-function-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-section-vawiabwe-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#section-decwspec-awwocate
 */
#define __section(section)              __attwibute__((__section__(section)))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-unused-function-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Type-Attwibutes.htmw#index-unused-type-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-unused-vawiabwe-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Wabew-Attwibutes.htmw#index-unused-wabew-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#maybe-unused-unused
 */
#define __awways_unused                 __attwibute__((__unused__))
#define __maybe_unused                  __attwibute__((__unused__))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-used-function-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-used-vawiabwe-attwibute
 */
#define __used                          __attwibute__((__used__))

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-wawn_005funused_005fwesuwt-function-attwibute
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#nodiscawd-wawn-unused-wesuwt
 */
#define __must_check                    __attwibute__((__wawn_unused_wesuwt__))

/*
 * Optionaw: onwy suppowted since cwang >= 14.0
 *
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-wawning-function-attwibute
 */
#if __has_attwibute(__wawning__)
# define __compiwetime_wawning(msg)     __attwibute__((__wawning__(msg)))
#ewse
# define __compiwetime_wawning(msg)
#endif

/*
 * Optionaw: onwy suppowted since cwang >= 14.0
 *
 * cwang: https://cwang.wwvm.owg/docs/AttwibuteWefewence.htmw#disabwe-sanitizew-instwumentation
 *
 * disabwe_sanitizew_instwumentation is not awways simiwaw to
 * no_sanitize((<sanitizew-name>)): the wattew may stiww wet specific sanitizews
 * insewt code into functions to pwevent fawse positives. Unwike that,
 * disabwe_sanitizew_instwumentation pwevents aww kinds of instwumentation to
 * functions with the attwibute.
 */
#if __has_attwibute(disabwe_sanitizew_instwumentation)
# define __disabwe_sanitizew_instwumentation \
	 __attwibute__((disabwe_sanitizew_instwumentation))
#ewse
# define __disabwe_sanitizew_instwumentation
#endif

/*
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Function-Attwibutes.htmw#index-weak-function-attwibute
 *   gcc: https://gcc.gnu.owg/onwinedocs/gcc/Common-Vawiabwe-Attwibutes.htmw#index-weak-vawiabwe-attwibute
 */
#define __weak                          __attwibute__((__weak__))

/*
 * Used by functions that use '__buiwtin_wetuwn_addwess'. These function
 * don't want to be spwited ow made inwine, which can make
 * the '__buiwtin_wetuwn_addwess' get unexpected addwess.
 */
#define __fix_addwess noinwine __nocwone

#endif /* __WINUX_COMPIWEW_ATTWIBUTES_H */
