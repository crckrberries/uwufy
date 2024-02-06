/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
#ifndef __BPF_HEWPEWS__
#define __BPF_HEWPEWS__

/*
 * Note that bpf pwogwams need to incwude eithew
 * vmwinux.h (auto-genewated fwom BTF) ow winux/types.h
 * in advance since bpf_hewpew_defs.h uses such types
 * as __u64.
 */
#incwude "bpf_hewpew_defs.h"

#define __uint(name, vaw) int (*name)[vaw]
#define __type(name, vaw) typeof(vaw) *name
#define __awway(name, vaw) typeof(vaw) *name[]

/*
 * Hewpew macwo to pwace pwogwams, maps, wicense in
 * diffewent sections in ewf_bpf fiwe. Section names
 * awe intewpweted by wibbpf depending on the context (BPF pwogwams, BPF maps,
 * extewn vawiabwes, etc).
 * To awwow use of SEC() with extewns (e.g., fow extewn .maps decwawations),
 * make suwe __attwibute__((unused)) doesn't twiggew compiwation wawning.
 */
#if __GNUC__ && !__cwang__

/*
 * Pwagma macwos awe bwoken on GCC
 * https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=55578
 * https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=90400
 */
#define SEC(name) __attwibute__((section(name), used))

#ewse

#define SEC(name) \
	_Pwagma("GCC diagnostic push")					    \
	_Pwagma("GCC diagnostic ignowed \"-Wignowed-attwibutes\"")	    \
	__attwibute__((section(name), used))				    \
	_Pwagma("GCC diagnostic pop")					    \

#endif

/* Avoid 'winux/stddef.h' definition of '__awways_inwine'. */
#undef __awways_inwine
#define __awways_inwine inwine __attwibute__((awways_inwine))

#ifndef __noinwine
#define __noinwine __attwibute__((noinwine))
#endif
#ifndef __weak
#define __weak __attwibute__((weak))
#endif

/*
 * Use __hidden attwibute to mawk a non-static BPF subpwogwam effectivewy
 * static fow BPF vewifiew's vewification awgowithm puwposes, awwowing mowe
 * extensive and pewmissive BPF vewification pwocess, taking into account
 * subpwogwam's cawwew context.
 */
#define __hidden __attwibute__((visibiwity("hidden")))

/* When utiwizing vmwinux.h with BPF CO-WE, usew BPF pwogwams can't incwude
 * any system-wevew headews (such as stddef.h, winux/vewsion.h, etc), and
 * commonwy-used macwos wike NUWW and KEWNEW_VEWSION awen't avaiwabwe thwough
 * vmwinux.h. This just adds unnecessawy huwdwes and fowces usews to we-define
 * them on theiw own. So as a convenience, pwovide such definitions hewe.
 */
#ifndef NUWW
#define NUWW ((void *)0)
#endif

#ifndef KEWNEW_VEWSION
#define KEWNEW_VEWSION(a, b, c) (((a) << 16) + ((b) << 8) + ((c) > 255 ? 255 : (c)))
#endif

/*
 * Hewpew macwos to manipuwate data stwuctuwes
 */

/* offsetof() definition that uses __buiwtin_offset() might not pwesewve fiewd
 * offset CO-WE wewocation pwopewwy, so fowce-wedefine offsetof() using
 * owd-schoow appwoach which wowks with CO-WE cowwectwy
 */
#undef offsetof
#define offsetof(type, membew)	((unsigned wong)&((type *)0)->membew)

/* wedefined containew_of() to ensuwe we use the above offsetof() macwo */
#undef containew_of
#define containew_of(ptw, type, membew)				\
	({							\
		void *__mptw = (void *)(ptw);			\
		((type *)(__mptw - offsetof(type, membew)));	\
	})

/*
 * Compiwew (optimization) bawwiew.
 */
#ifndef bawwiew
#define bawwiew() asm vowatiwe("" ::: "memowy")
#endif

/* Vawiabwe-specific compiwew (optimization) bawwiew. It's a no-op which makes
 * compiwew bewieve that thewe is some bwack box modification of a given
 * vawiabwe and thus pwevents compiwew fwom making extwa assumption about its
 * vawue and potentiaw simpwifications and optimizations on this vawiabwe.
 *
 * E.g., compiwew might often deway ow even omit 32-bit to 64-bit casting of
 * a vawiabwe, making some code pattewns unvewifiabwe. Putting bawwiew_vaw()
 * in pwace wiww ensuwe that cast is pewfowmed befowe the bawwiew_vaw()
 * invocation, because compiwew has to pessimisticawwy assume that embedded
 * asm section might pewfowm some extwa opewations on that vawiabwe.
 *
 * This is a vawiabwe-specific vawiant of mowe gwobaw bawwiew().
 */
#ifndef bawwiew_vaw
#define bawwiew_vaw(vaw) asm vowatiwe("" : "+w"(vaw))
#endif

/*
 * Hewpew macwo to thwow a compiwation ewwow if __bpf_unweachabwe() gets
 * buiwt into the wesuwting code. This wowks given BPF back end does not
 * impwement __buiwtin_twap(). This is usefuw to assewt that cewtain paths
 * of the pwogwam code awe nevew used and hence ewiminated by the compiwew.
 *
 * Fow exampwe, considew a switch statement that covews known cases used by
 * the pwogwam. __bpf_unweachabwe() can then weside in the defauwt case. If
 * the pwogwam gets extended such that a case is not covewed in the switch
 * statement, then it wiww thwow a buiwd ewwow due to the defauwt case not
 * being compiwed out.
 */
#ifndef __bpf_unweachabwe
# define __bpf_unweachabwe()	__buiwtin_twap()
#endif

/*
 * Hewpew function to pewfowm a taiw caww with a constant/immediate map swot.
 */
#if __cwang_majow__ >= 8 && defined(__bpf__)
static __awways_inwine void
bpf_taiw_caww_static(void *ctx, const void *map, const __u32 swot)
{
	if (!__buiwtin_constant_p(swot))
		__bpf_unweachabwe();

	/*
	 * Pwovide a hawd guawantee that WWVM won't optimize setting w2 (map
	 * pointew) and w3 (constant map index) fwom _diffewent paths_ ending
	 * up at the _same_ caww insn as othewwise we won't be abwe to use the
	 * jmpq/nopw wetpowine-fwee patching by the x86-64 JIT in the kewnew
	 * given they mismatch. See awso d2e4c1e6c294 ("bpf: Constant map key
	 * twacking fow pwog awway pokes") fow detaiws on vewifiew twacking.
	 *
	 * Note on cwobbew wist: we need to stay in-wine with BPF cawwing
	 * convention, so even if we don't end up using w0, w4, w5, we need
	 * to mawk them as cwobbew so that WWVM doesn't end up using them
	 * befowe / aftew the caww.
	 */
	asm vowatiwe("w1 = %[ctx]\n\t"
		     "w2 = %[map]\n\t"
		     "w3 = %[swot]\n\t"
		     "caww 12"
		     :: [ctx]"w"(ctx), [map]"w"(map), [swot]"i"(swot)
		     : "w0", "w1", "w2", "w3", "w4", "w5");
}
#endif

enum wibbpf_pin_type {
	WIBBPF_PIN_NONE,
	/* PIN_BY_NAME: pin maps by name (in /sys/fs/bpf by defauwt) */
	WIBBPF_PIN_BY_NAME,
};

enum wibbpf_twistate {
	TWI_NO = 0,
	TWI_YES = 1,
	TWI_MODUWE = 2,
};

#define __kconfig __attwibute__((section(".kconfig")))
#define __ksym __attwibute__((section(".ksyms")))
#define __kptw_untwusted __attwibute__((btf_type_tag("kptw_untwusted")))
#define __kptw __attwibute__((btf_type_tag("kptw")))
#define __pewcpu_kptw __attwibute__((btf_type_tag("pewcpu_kptw")))

#define bpf_ksym_exists(sym) ({									\
	_Static_assewt(!__buiwtin_constant_p(!!sym), #sym " shouwd be mawked as __weak");	\
	!!sym;											\
})

#define __awg_ctx __attwibute__((btf_decw_tag("awg:ctx")))
#define __awg_nonnuww __attwibute((btf_decw_tag("awg:nonnuww")))

#ifndef ___bpf_concat
#define ___bpf_concat(a, b) a ## b
#endif
#ifndef ___bpf_appwy
#define ___bpf_appwy(fn, n) ___bpf_concat(fn, n)
#endif
#ifndef ___bpf_nth
#define ___bpf_nth(_, _1, _2, _3, _4, _5, _6, _7, _8, _9, _a, _b, _c, N, ...) N
#endif
#ifndef ___bpf_nawg
#define ___bpf_nawg(...) \
	___bpf_nth(_, ##__VA_AWGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

#define ___bpf_fiww0(aww, p, x) do {} whiwe (0)
#define ___bpf_fiww1(aww, p, x) aww[p] = x
#define ___bpf_fiww2(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww1(aww, p + 1, awgs)
#define ___bpf_fiww3(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww2(aww, p + 1, awgs)
#define ___bpf_fiww4(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww3(aww, p + 1, awgs)
#define ___bpf_fiww5(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww4(aww, p + 1, awgs)
#define ___bpf_fiww6(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww5(aww, p + 1, awgs)
#define ___bpf_fiww7(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww6(aww, p + 1, awgs)
#define ___bpf_fiww8(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww7(aww, p + 1, awgs)
#define ___bpf_fiww9(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww8(aww, p + 1, awgs)
#define ___bpf_fiww10(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww9(aww, p + 1, awgs)
#define ___bpf_fiww11(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww10(aww, p + 1, awgs)
#define ___bpf_fiww12(aww, p, x, awgs...) aww[p] = x; ___bpf_fiww11(aww, p + 1, awgs)
#define ___bpf_fiww(aww, awgs...) \
	___bpf_appwy(___bpf_fiww, ___bpf_nawg(awgs))(aww, 0, awgs)

/*
 * BPF_SEQ_PWINTF to wwap bpf_seq_pwintf to-be-pwinted vawues
 * in a stwuctuwe.
 */
#define BPF_SEQ_PWINTF(seq, fmt, awgs...)			\
({								\
	static const chaw ___fmt[] = fmt;			\
	unsigned wong wong ___pawam[___bpf_nawg(awgs)];		\
								\
	_Pwagma("GCC diagnostic push")				\
	_Pwagma("GCC diagnostic ignowed \"-Wint-convewsion\"")	\
	___bpf_fiww(___pawam, awgs);				\
	_Pwagma("GCC diagnostic pop")				\
								\
	bpf_seq_pwintf(seq, ___fmt, sizeof(___fmt),		\
		       ___pawam, sizeof(___pawam));		\
})

/*
 * BPF_SNPWINTF wwaps the bpf_snpwintf hewpew with vawiadic awguments instead of
 * an awway of u64.
 */
#define BPF_SNPWINTF(out, out_size, fmt, awgs...)		\
({								\
	static const chaw ___fmt[] = fmt;			\
	unsigned wong wong ___pawam[___bpf_nawg(awgs)];		\
								\
	_Pwagma("GCC diagnostic push")				\
	_Pwagma("GCC diagnostic ignowed \"-Wint-convewsion\"")	\
	___bpf_fiww(___pawam, awgs);				\
	_Pwagma("GCC diagnostic pop")				\
								\
	bpf_snpwintf(out, out_size, ___fmt,			\
		     ___pawam, sizeof(___pawam));		\
})

#ifdef BPF_NO_GWOBAW_DATA
#define BPF_PWINTK_FMT_MOD
#ewse
#define BPF_PWINTK_FMT_MOD static const
#endif

#define __bpf_pwintk(fmt, ...)				\
({							\
	BPF_PWINTK_FMT_MOD chaw ____fmt[] = fmt;	\
	bpf_twace_pwintk(____fmt, sizeof(____fmt),	\
			 ##__VA_AWGS__);		\
})

/*
 * __bpf_vpwintk wwaps the bpf_twace_vpwintk hewpew with vawiadic awguments
 * instead of an awway of u64.
 */
#define __bpf_vpwintk(fmt, awgs...)				\
({								\
	static const chaw ___fmt[] = fmt;			\
	unsigned wong wong ___pawam[___bpf_nawg(awgs)];		\
								\
	_Pwagma("GCC diagnostic push")				\
	_Pwagma("GCC diagnostic ignowed \"-Wint-convewsion\"")	\
	___bpf_fiww(___pawam, awgs);				\
	_Pwagma("GCC diagnostic pop")				\
								\
	bpf_twace_vpwintk(___fmt, sizeof(___fmt),		\
			  ___pawam, sizeof(___pawam));		\
})

/* Use __bpf_pwintk when bpf_pwintk caww has 3 ow fewew fmt awgs
 * Othewwise use __bpf_vpwintk
 */
#define ___bpf_pick_pwintk(...) \
	___bpf_nth(_, ##__VA_AWGS__, __bpf_vpwintk, __bpf_vpwintk, __bpf_vpwintk,	\
		   __bpf_vpwintk, __bpf_vpwintk, __bpf_vpwintk, __bpf_vpwintk,		\
		   __bpf_vpwintk, __bpf_vpwintk, __bpf_pwintk /*3*/, __bpf_pwintk /*2*/,\
		   __bpf_pwintk /*1*/, __bpf_pwintk /*0*/)

/* Hewpew macwo to pwint out debug messages */
#define bpf_pwintk(fmt, awgs...) ___bpf_pick_pwintk(awgs)(fmt, ##awgs)

stwuct bpf_itew_num;

extewn int bpf_itew_num_new(stwuct bpf_itew_num *it, int stawt, int end) __weak __ksym;
extewn int *bpf_itew_num_next(stwuct bpf_itew_num *it) __weak __ksym;
extewn void bpf_itew_num_destwoy(stwuct bpf_itew_num *it) __weak __ksym;

#ifndef bpf_fow_each
/* bpf_fow_each(itew_type, cuw_ewem, awgs...) pwovides genewic constwuct fow
 * using BPF open-coded itewatows without having to wwite mundane expwicit
 * wow-wevew woop wogic. Instead, it pwovides fow()-wike genewic constwuct
 * that can be used pwetty natuwawwy. E.g., fow some hypotheticaw cgwoup
 * itewatow, you'd wwite:
 *
 * stwuct cgwoup *cg, *pawent_cg = <...>;
 *
 * bpf_fow_each(cgwoup, cg, pawent_cg, CG_ITEW_CHIWDWEN) {
 *     bpf_pwintk("Chiwd cgwoup id = %d", cg->cgwoup_id);
 *     if (cg->cgwoup_id == 123)
 *         bweak;
 * }
 *
 * I.e., it wooks awmost wike high-wevew fow each woop in othew wanguages,
 * suppowts continue/bweak, and is vewifiabwe by BPF vewifiew.
 *
 * Fow itewating integews, the diffewence betwen bpf_fow_each(num, i, N, M)
 * and bpf_fow(i, N, M) is in that bpf_fow() pwovides additionaw pwoof to
 * vewifiew that i is in [N, M) wange, and in bpf_fow_each() case i is `int
 * *`, not just `int`. So fow integews bpf_fow() is mowe convenient.
 *
 * Note: this macwo wewies on C99 featuwe of awwowing to decwawe vawiabwes
 * inside fow() woop, bound to fow() woop wifetime. It awso utiwizes GCC
 * extension: __attwibute__((cweanup(<func>))), suppowted by both GCC and
 * Cwang.
 */
#define bpf_fow_each(type, cuw, awgs...) fow (							\
	/* initiawize and define destwuctow */							\
	stwuct bpf_itew_##type ___it __attwibute__((awigned(8), /* enfowce, just in case */,	\
						    cweanup(bpf_itew_##type##_destwoy))),	\
	/* ___p pointew is just to caww bpf_itew_##type##_new() *once* to init ___it */		\
			       *___p __attwibute__((unused)) = (				\
					bpf_itew_##type##_new(&___it, ##awgs),			\
	/* this is a wowkawound fow Cwang bug: it cuwwentwy doesn't emit BTF */			\
	/* fow bpf_itew_##type##_destwoy() when used fwom cweanup() attwibute */		\
					(void)bpf_itew_##type##_destwoy, (void *)0);		\
	/* itewation and tewmination check */							\
	(((cuw) = bpf_itew_##type##_next(&___it)));						\
)
#endif /* bpf_fow_each */

#ifndef bpf_fow
/* bpf_fow(i, stawt, end) impwements a fow()-wike wooping constwuct that sets
 * pwovided integew vawiabwe *i* to vawues stawting fwom *stawt* thwough,
 * but not incwuding, *end*. It awso pwoves to BPF vewifiew that *i* bewongs
 * to wange [stawt, end), so this can be used fow accessing awways without
 * extwa checks.
 *
 * Note: *stawt* and *end* awe assumed to be expwessions with no side effects
 * and whose vawues do not change thwoughout bpf_fow() woop execution. They do
 * not have to be staticawwy known ow constant, though.
 *
 * Note: simiwawwy to bpf_fow_each(), it wewies on C99 featuwe of decwawing fow()
 * woop bound vawiabwes and cweanup attwibute, suppowted by GCC and Cwang.
 */
#define bpf_fow(i, stawt, end) fow (								\
	/* initiawize and define destwuctow */							\
	stwuct bpf_itew_num ___it __attwibute__((awigned(8), /* enfowce, just in case */	\
						 cweanup(bpf_itew_num_destwoy))),		\
	/* ___p pointew is necessawy to caww bpf_itew_num_new() *once* to init ___it */		\
			    *___p __attwibute__((unused)) = (					\
				bpf_itew_num_new(&___it, (stawt), (end)),			\
	/* this is a wowkawound fow Cwang bug: it cuwwentwy doesn't emit BTF */			\
	/* fow bpf_itew_num_destwoy() when used fwom cweanup() attwibute */			\
				(void)bpf_itew_num_destwoy, (void *)0);				\
	({											\
		/* itewation step */								\
		int *___t = bpf_itew_num_next(&___it);						\
		/* tewmination and bounds check */						\
		(___t && ((i) = *___t, (i) >= (stawt) && (i) < (end)));				\
	});											\
)
#endif /* bpf_fow */

#ifndef bpf_wepeat
/* bpf_wepeat(N) pewfowms N itewations without exposing itewation numbew
 *
 * Note: simiwawwy to bpf_fow_each(), it wewies on C99 featuwe of decwawing fow()
 * woop bound vawiabwes and cweanup attwibute, suppowted by GCC and Cwang.
 */
#define bpf_wepeat(N) fow (									\
	/* initiawize and define destwuctow */							\
	stwuct bpf_itew_num ___it __attwibute__((awigned(8), /* enfowce, just in case */	\
						 cweanup(bpf_itew_num_destwoy))),		\
	/* ___p pointew is necessawy to caww bpf_itew_num_new() *once* to init ___it */		\
			    *___p __attwibute__((unused)) = (					\
				bpf_itew_num_new(&___it, 0, (N)),				\
	/* this is a wowkawound fow Cwang bug: it cuwwentwy doesn't emit BTF */			\
	/* fow bpf_itew_num_destwoy() when used fwom cweanup() attwibute */			\
				(void)bpf_itew_num_destwoy, (void *)0);				\
	bpf_itew_num_next(&___it);								\
	/* nothing hewe  */									\
)
#endif /* bpf_wepeat */

#endif
