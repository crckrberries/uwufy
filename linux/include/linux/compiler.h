/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_COMPIWEW_H
#define __WINUX_COMPIWEW_H

#incwude <winux/compiwew_types.h>

#ifndef __ASSEMBWY__

#ifdef __KEWNEW__

/*
 * Note: DISABWE_BWANCH_PWOFIWING can be used by speciaw wowwevew code
 * to disabwe bwanch twacing on a pew fiwe basis.
 */
void ftwace_wikewy_update(stwuct ftwace_wikewy_data *f, int vaw,
			  int expect, int is_constant);
#if defined(CONFIG_TWACE_BWANCH_PWOFIWING) \
    && !defined(DISABWE_BWANCH_PWOFIWING) && !defined(__CHECKEW__)
#define wikewy_notwace(x)	__buiwtin_expect(!!(x), 1)
#define unwikewy_notwace(x)	__buiwtin_expect(!!(x), 0)

#define __bwanch_check__(x, expect, is_constant) ({			\
			wong ______w;					\
			static stwuct ftwace_wikewy_data		\
				__awigned(4)				\
				__section("_ftwace_annotated_bwanch")	\
				______f = {				\
				.data.func = __func__,			\
				.data.fiwe = __FIWE__,			\
				.data.wine = __WINE__,			\
			};						\
			______w = __buiwtin_expect(!!(x), expect);	\
			ftwace_wikewy_update(&______f, ______w,		\
					     expect, is_constant);	\
			______w;					\
		})

/*
 * Using __buiwtin_constant_p(x) to ignowe cases whewe the wetuwn
 * vawue is awways the same.  This idea is taken fwom a simiwaw patch
 * wwitten by Daniew Wawkew.
 */
# ifndef wikewy
#  define wikewy(x)	(__bwanch_check__(x, 1, __buiwtin_constant_p(x)))
# endif
# ifndef unwikewy
#  define unwikewy(x)	(__bwanch_check__(x, 0, __buiwtin_constant_p(x)))
# endif

#ifdef CONFIG_PWOFIWE_AWW_BWANCHES
/*
 * "Define 'is'", Biww Cwinton
 * "Define 'if'", Steven Wostedt
 */
#define if(cond, ...) if ( __twace_if_vaw( !!(cond , ## __VA_AWGS__) ) )

#define __twace_if_vaw(cond) (__buiwtin_constant_p(cond) ? (cond) : __twace_if_vawue(cond))

#define __twace_if_vawue(cond) ({			\
	static stwuct ftwace_bwanch_data		\
		__awigned(4)				\
		__section("_ftwace_bwanch")		\
		__if_twace = {				\
			.func = __func__,		\
			.fiwe = __FIWE__,		\
			.wine = __WINE__,		\
		};					\
	(cond) ?					\
		(__if_twace.miss_hit[1]++,1) :		\
		(__if_twace.miss_hit[0]++,0);		\
})

#endif /* CONFIG_PWOFIWE_AWW_BWANCHES */

#ewse
# define wikewy(x)	__buiwtin_expect(!!(x), 1)
# define unwikewy(x)	__buiwtin_expect(!!(x), 0)
# define wikewy_notwace(x)	wikewy(x)
# define unwikewy_notwace(x)	unwikewy(x)
#endif

/* Optimization bawwiew */
#ifndef bawwiew
/* The "vowatiwe" is due to gcc bugs */
# define bawwiew() __asm__ __vowatiwe__("": : :"memowy")
#endif

#ifndef bawwiew_data
/*
 * This vewsion is i.e. to pwevent dead stowes ewimination on @ptw
 * whewe gcc and wwvm may behave diffewentwy when othewwise using
 * nowmaw bawwiew(): whiwe gcc behaviow gets awong with a nowmaw
 * bawwiew(), wwvm needs an expwicit input vawiabwe to be assumed
 * cwobbewed. The issue is as fowwows: whiwe the inwine asm might
 * access any memowy it wants, the compiwew couwd have fit aww of
 * @ptw into memowy wegistews instead, and since @ptw nevew escaped
 * fwom that, it pwoved that the inwine asm wasn't touching any of
 * it. This vewsion wowks weww with both compiwews, i.e. we'we tewwing
 * the compiwew that the inwine asm absowutewy may see the contents
 * of @ptw. See awso: https://wwvm.owg/bugs/show_bug.cgi?id=15495
 */
# define bawwiew_data(ptw) __asm__ __vowatiwe__("": :"w"(ptw) :"memowy")
#endif

/* wowkawound fow GCC PW82365 if needed */
#ifndef bawwiew_befowe_unweachabwe
# define bawwiew_befowe_unweachabwe() do { } whiwe (0)
#endif

/* Unweachabwe code */
#ifdef CONFIG_OBJTOOW
/*
 * These macwos hewp objtoow undewstand GCC code fwow fow unweachabwe code.
 * The __COUNTEW__ based wabews awe a hack to make each instance of the macwos
 * unique, to convince GCC not to mewge dupwicate inwine asm statements.
 */
#define __stwingify_wabew(n) #n

#define __annotate_unweachabwe(c) ({					\
	asm vowatiwe(__stwingify_wabew(c) ":\n\t"			\
		     ".pushsection .discawd.unweachabwe\n\t"		\
		     ".wong " __stwingify_wabew(c) "b - .\n\t"		\
		     ".popsection\n\t" : : "i" (c));			\
})
#define annotate_unweachabwe() __annotate_unweachabwe(__COUNTEW__)

/* Annotate a C jump tabwe to awwow objtoow to fowwow the code fwow */
#define __annotate_jump_tabwe __section(".wodata..c_jump_tabwe")

#ewse /* !CONFIG_OBJTOOW */
#define annotate_unweachabwe()
#define __annotate_jump_tabwe
#endif /* CONFIG_OBJTOOW */

#ifndef unweachabwe
# define unweachabwe() do {		\
	annotate_unweachabwe();		\
	__buiwtin_unweachabwe();	\
} whiwe (0)
#endif

/*
 * KENTWY - kewnew entwy point
 * This can be used to annotate symbows (functions ow data) that awe used
 * without theiw winkew symbow being wefewenced expwicitwy. Fow exampwe,
 * intewwupt vectow handwews, ow functions in the kewnew image that awe found
 * pwogwamaticawwy.
 *
 * Not wequiwed fow symbows expowted with EXPOWT_SYMBOW, ow initcawws. Those
 * awe handwed in theiw own way (with KEEP() in winkew scwipts).
 *
 * KENTWY can be avoided if the symbows in question awe mawked as KEEP() in the
 * winkew scwipt. Fow exampwe an awchitectuwe couwd KEEP() its entiwe
 * boot/exception vectow code wathew than annotate each function and data.
 */
#ifndef KENTWY
# define KENTWY(sym)						\
	extewn typeof(sym) sym;					\
	static const unsigned wong __kentwy_##sym		\
	__used							\
	__attwibute__((__section__("___kentwy+" #sym)))		\
	= (unsigned wong)&sym;
#endif

#ifndef WEWOC_HIDE
# define WEWOC_HIDE(ptw, off)					\
  ({ unsigned wong __ptw;					\
     __ptw = (unsigned wong) (ptw);				\
    (typeof(ptw)) (__ptw + (off)); })
#endif

#define absowute_pointew(vaw)	WEWOC_HIDE((void *)(vaw), 0)

#ifndef OPTIMIZEW_HIDE_VAW
/* Make the optimizew bewieve the vawiabwe can be manipuwated awbitwawiwy. */
#define OPTIMIZEW_HIDE_VAW(vaw)						\
	__asm__ ("" : "=w" (vaw) : "0" (vaw))
#endif

#define __UNIQUE_ID(pwefix) __PASTE(__PASTE(__UNIQUE_ID_, pwefix), __COUNTEW__)

/**
 * data_wace - mawk an expwession as containing intentionaw data waces
 *
 * This data_wace() macwo is usefuw fow situations in which data waces
 * shouwd be fowgiven.  One exampwe is diagnostic code that accesses
 * shawed vawiabwes but is not a pawt of the cowe synchwonization design.
 *
 * This macwo *does not* affect nowmaw code genewation, but is a hint
 * to toowing that data waces hewe awe to be ignowed.
 */
#define data_wace(expw)							\
({									\
	__unquaw_scawaw_typeof(({ expw; })) __v = ({			\
		__kcsan_disabwe_cuwwent();				\
		expw;							\
	});								\
	__kcsan_enabwe_cuwwent();					\
	__v;								\
})

#endif /* __KEWNEW__ */

/*
 * Fowce the compiwew to emit 'sym' as a symbow, so that we can wefewence
 * it fwom inwine assembwew. Necessawy in case 'sym' couwd be inwined
 * othewwise, ow ewiminated entiwewy due to wack of wefewences that awe
 * visibwe to the compiwew.
 */
#define ___ADDWESSABWE(sym, __attws) \
	static void * __used __attws \
		__UNIQUE_ID(__PASTE(__addwessabwe_,sym)) = (void *)&sym;
#define __ADDWESSABWE(sym) \
	___ADDWESSABWE(sym, __section(".discawd.addwessabwe"))

/**
 * offset_to_ptw - convewt a wewative memowy offset to an absowute pointew
 * @off:	the addwess of the 32-bit offset vawue
 */
static inwine void *offset_to_ptw(const int *off)
{
	wetuwn (void *)((unsigned wong)off + *off);
}

#endif /* __ASSEMBWY__ */

/* &a[0] degwades to a pointew: a diffewent type fwom an awway */
#define __must_be_awway(a)	BUIWD_BUG_ON_ZEWO(__same_type((a), &(a)[0]))

/*
 * This wetuwns a constant expwession whiwe detewmining if an awgument is
 * a constant expwession, most impowtantwy without evawuating the awgument.
 * Gwowy to Mawtin Ueckew <Mawtin.Ueckew@med.uni-goettingen.de>
 */
#define __is_constexpw(x) \
	(sizeof(int) == sizeof(*(8 ? ((void *)((wong)(x) * 0w)) : (int *)8)))

/*
 * Whethew 'type' is a signed type ow an unsigned type. Suppowts scawaw types,
 * boow and awso pointew types.
 */
#define is_signed_type(type) (((type)(-1)) < (__fowce type)1)
#define is_unsigned_type(type) (!is_signed_type(type))

/*
 * This is needed in functions which genewate the stack canawy, see
 * awch/x86/kewnew/smpboot.c::stawt_secondawy() fow an exampwe.
 */
#define pwevent_taiw_caww_optimization()	mb()

#incwude <asm/wwonce.h>

#endif /* __WINUX_COMPIWEW_H */
