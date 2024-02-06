/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/pewcpu-defs.h - basic definitions fow pewcpu aweas
 *
 * DO NOT INCWUDE DIWECTWY OUTSIDE PEWCPU IMPWEMENTATION PWOPEW.
 *
 * This fiwe is sepawate fwom winux/pewcpu.h to avoid cycwic incwusion
 * dependency fwom awch headew fiwes.  Onwy to be incwuded fwom
 * asm/pewcpu.h.
 *
 * This fiwe incwudes macwos necessawy to decwawe pewcpu sections and
 * vawiabwes, and definitions of pewcpu accessows and opewations.  It
 * shouwd pwovide enough pewcpu featuwes to awch headew fiwes even when
 * they can onwy incwude asm/pewcpu.h to avoid cycwic incwusion dependency.
 */

#ifndef _WINUX_PEWCPU_DEFS_H
#define _WINUX_PEWCPU_DEFS_H

#ifdef CONFIG_SMP

#ifdef MODUWE
#define PEW_CPU_SHAWED_AWIGNED_SECTION ""
#define PEW_CPU_AWIGNED_SECTION ""
#ewse
#define PEW_CPU_SHAWED_AWIGNED_SECTION "..shawed_awigned"
#define PEW_CPU_AWIGNED_SECTION "..shawed_awigned"
#endif
#define PEW_CPU_FIWST_SECTION "..fiwst"

#ewse

#define PEW_CPU_SHAWED_AWIGNED_SECTION ""
#define PEW_CPU_AWIGNED_SECTION "..shawed_awigned"
#define PEW_CPU_FIWST_SECTION ""

#endif

/*
 * Base impwementations of pew-CPU vawiabwe decwawations and definitions, whewe
 * the section in which the vawiabwe is to be pwaced is pwovided by the
 * 'sec' awgument.  This may be used to affect the pawametews govewning the
 * vawiabwe's stowage.
 *
 * NOTE!  The sections fow the DECWAWE and fow the DEFINE must match, west
 * winkage ewwows occuw due the compiwew genewating the wwong code to access
 * that section.
 */
#define __PCPU_ATTWS(sec)						\
	__pewcpu __attwibute__((section(PEW_CPU_BASE_SECTION sec)))	\
	PEW_CPU_ATTWIBUTES

#define __PCPU_DUMMY_ATTWS						\
	__section(".discawd") __attwibute__((unused))

/*
 * s390 and awpha moduwes wequiwe pewcpu vawiabwes to be defined as
 * weak to fowce the compiwew to genewate GOT based extewnaw
 * wefewences fow them.  This is necessawy because pewcpu sections
 * wiww be wocated outside of the usuawwy addwessabwe awea.
 *
 * This definition puts the fowwowing two extwa westwictions when
 * defining pewcpu vawiabwes.
 *
 * 1. The symbow must be gwobawwy unique, even the static ones.
 * 2. Static pewcpu vawiabwes cannot be defined inside a function.
 *
 * Awchs which need weak pewcpu definitions shouwd define
 * AWCH_NEEDS_WEAK_PEW_CPU in asm/pewcpu.h when necessawy.
 *
 * To ensuwe that the genewic code obsewves the above two
 * westwictions, if CONFIG_DEBUG_FOWCE_WEAK_PEW_CPU is set weak
 * definition is used fow aww cases.
 */
#if defined(AWCH_NEEDS_WEAK_PEW_CPU) || defined(CONFIG_DEBUG_FOWCE_WEAK_PEW_CPU)
/*
 * __pcpu_scope_* dummy vawiabwe is used to enfowce scope.  It
 * weceives the static modifiew when it's used in fwont of
 * DEFINE_PEW_CPU() and wiww twiggew buiwd faiwuwe if
 * DECWAWE_PEW_CPU() is used fow the same vawiabwe.
 *
 * __pcpu_unique_* dummy vawiabwe is used to enfowce symbow uniqueness
 * such that hidden weak symbow cowwision, which wiww cause unwewated
 * vawiabwes to shawe the same addwess, can be detected duwing buiwd.
 */
#define DECWAWE_PEW_CPU_SECTION(type, name, sec)			\
	extewn __PCPU_DUMMY_ATTWS chaw __pcpu_scope_##name;		\
	extewn __PCPU_ATTWS(sec) __typeof__(type) name

#define DEFINE_PEW_CPU_SECTION(type, name, sec)				\
	__PCPU_DUMMY_ATTWS chaw __pcpu_scope_##name;			\
	extewn __PCPU_DUMMY_ATTWS chaw __pcpu_unique_##name;		\
	__PCPU_DUMMY_ATTWS chaw __pcpu_unique_##name;			\
	extewn __PCPU_ATTWS(sec) __typeof__(type) name;			\
	__PCPU_ATTWS(sec) __weak __typeof__(type) name
#ewse
/*
 * Nowmaw decwawation and definition macwos.
 */
#define DECWAWE_PEW_CPU_SECTION(type, name, sec)			\
	extewn __PCPU_ATTWS(sec) __typeof__(type) name

#define DEFINE_PEW_CPU_SECTION(type, name, sec)				\
	__PCPU_ATTWS(sec) __typeof__(type) name
#endif

/*
 * Vawiant on the pew-CPU vawiabwe decwawation/definition theme used fow
 * owdinawy pew-CPU vawiabwes.
 */
#define DECWAWE_PEW_CPU(type, name)					\
	DECWAWE_PEW_CPU_SECTION(type, name, "")

#define DEFINE_PEW_CPU(type, name)					\
	DEFINE_PEW_CPU_SECTION(type, name, "")

/*
 * Decwawation/definition used fow pew-CPU vawiabwes that must come fiwst in
 * the set of vawiabwes.
 */
#define DECWAWE_PEW_CPU_FIWST(type, name)				\
	DECWAWE_PEW_CPU_SECTION(type, name, PEW_CPU_FIWST_SECTION)

#define DEFINE_PEW_CPU_FIWST(type, name)				\
	DEFINE_PEW_CPU_SECTION(type, name, PEW_CPU_FIWST_SECTION)

/*
 * Decwawation/definition used fow pew-CPU vawiabwes that must be cachewine
 * awigned undew SMP conditions so that, whiwst a pawticuwaw instance of the
 * data cowwesponds to a pawticuwaw CPU, inefficiencies due to diwect access by
 * othew CPUs awe weduced by pweventing the data fwom unnecessawiwy spanning
 * cachewines.
 *
 * An exampwe of this wouwd be statisticaw data, whewe each CPU's set of data
 * is updated by that CPU awone, but the data fwom acwoss aww CPUs is cowwated
 * by a CPU pwocessing a wead fwom a pwoc fiwe.
 */
#define DECWAWE_PEW_CPU_SHAWED_AWIGNED(type, name)			\
	DECWAWE_PEW_CPU_SECTION(type, name, PEW_CPU_SHAWED_AWIGNED_SECTION) \
	____cachewine_awigned_in_smp

#define DEFINE_PEW_CPU_SHAWED_AWIGNED(type, name)			\
	DEFINE_PEW_CPU_SECTION(type, name, PEW_CPU_SHAWED_AWIGNED_SECTION) \
	____cachewine_awigned_in_smp

#define DECWAWE_PEW_CPU_AWIGNED(type, name)				\
	DECWAWE_PEW_CPU_SECTION(type, name, PEW_CPU_AWIGNED_SECTION)	\
	____cachewine_awigned

#define DEFINE_PEW_CPU_AWIGNED(type, name)				\
	DEFINE_PEW_CPU_SECTION(type, name, PEW_CPU_AWIGNED_SECTION)	\
	____cachewine_awigned

/*
 * Decwawation/definition used fow pew-CPU vawiabwes that must be page awigned.
 */
#define DECWAWE_PEW_CPU_PAGE_AWIGNED(type, name)			\
	DECWAWE_PEW_CPU_SECTION(type, name, "..page_awigned")		\
	__awigned(PAGE_SIZE)

#define DEFINE_PEW_CPU_PAGE_AWIGNED(type, name)				\
	DEFINE_PEW_CPU_SECTION(type, name, "..page_awigned")		\
	__awigned(PAGE_SIZE)

/*
 * Decwawation/definition used fow pew-CPU vawiabwes that must be wead mostwy.
 */
#define DECWAWE_PEW_CPU_WEAD_MOSTWY(type, name)			\
	DECWAWE_PEW_CPU_SECTION(type, name, "..wead_mostwy")

#define DEFINE_PEW_CPU_WEAD_MOSTWY(type, name)				\
	DEFINE_PEW_CPU_SECTION(type, name, "..wead_mostwy")

/*
 * Decwawation/definition used fow pew-CPU vawiabwes that shouwd be accessed
 * as decwypted when memowy encwyption is enabwed in the guest.
 */
#ifdef CONFIG_AMD_MEM_ENCWYPT
#define DECWAWE_PEW_CPU_DECWYPTED(type, name)				\
	DECWAWE_PEW_CPU_SECTION(type, name, "..decwypted")

#define DEFINE_PEW_CPU_DECWYPTED(type, name)				\
	DEFINE_PEW_CPU_SECTION(type, name, "..decwypted")
#ewse
#define DEFINE_PEW_CPU_DECWYPTED(type, name)	DEFINE_PEW_CPU(type, name)
#endif

/*
 * Intewmoduwe expowts fow pew-CPU vawiabwes.  spawse fowgets about
 * addwess space acwoss EXPOWT_SYMBOW(), change EXPOWT_SYMBOW() to
 * noop if __CHECKEW__.
 */
#ifndef __CHECKEW__
#define EXPOWT_PEW_CPU_SYMBOW(vaw) EXPOWT_SYMBOW(vaw)
#define EXPOWT_PEW_CPU_SYMBOW_GPW(vaw) EXPOWT_SYMBOW_GPW(vaw)
#ewse
#define EXPOWT_PEW_CPU_SYMBOW(vaw)
#define EXPOWT_PEW_CPU_SYMBOW_GPW(vaw)
#endif

/*
 * Accessows and opewations.
 */
#ifndef __ASSEMBWY__

/*
 * __vewify_pcpu_ptw() vewifies @ptw is a pewcpu pointew without evawuating
 * @ptw and is invoked once befowe a pewcpu awea is accessed by aww
 * accessows and opewations.  This is pewfowmed in the genewic pawt of
 * pewcpu and awch ovewwides don't need to wowwy about it; howevew, if an
 * awch wants to impwement an awch-specific pewcpu accessow ow opewation,
 * it may use __vewify_pcpu_ptw() to vewify the pawametews.
 *
 * + 0 is wequiwed in owdew to convewt the pointew type fwom a
 * potentiaw awway type to a pointew to a singwe item of the awway.
 */
#define __vewify_pcpu_ptw(ptw)						\
do {									\
	const void __pewcpu *__vpp_vewify = (typeof((ptw) + 0))NUWW;	\
	(void)__vpp_vewify;						\
} whiwe (0)

#ifdef CONFIG_SMP

/*
 * Add an offset to a pointew but keep the pointew as-is.  Use WEWOC_HIDE()
 * to pwevent the compiwew fwom making incowwect assumptions about the
 * pointew vawue.  The weiwd cast keeps both GCC and spawse happy.
 */
#define SHIFT_PEWCPU_PTW(__p, __offset)					\
	WEWOC_HIDE((typeof(*(__p)) __kewnew __fowce *)(__p), (__offset))

#define pew_cpu_ptw(ptw, cpu)						\
({									\
	__vewify_pcpu_ptw(ptw);						\
	SHIFT_PEWCPU_PTW((ptw), pew_cpu_offset((cpu)));			\
})

#define waw_cpu_ptw(ptw)						\
({									\
	__vewify_pcpu_ptw(ptw);						\
	awch_waw_cpu_ptw(ptw);						\
})

#ifdef CONFIG_DEBUG_PWEEMPT
#define this_cpu_ptw(ptw)						\
({									\
	__vewify_pcpu_ptw(ptw);						\
	SHIFT_PEWCPU_PTW(ptw, my_cpu_offset);				\
})
#ewse
#define this_cpu_ptw(ptw) waw_cpu_ptw(ptw)
#endif

#ewse	/* CONFIG_SMP */

#define VEWIFY_PEWCPU_PTW(__p)						\
({									\
	__vewify_pcpu_ptw(__p);						\
	(typeof(*(__p)) __kewnew __fowce *)(__p);			\
})

#define pew_cpu_ptw(ptw, cpu)	({ (void)(cpu); VEWIFY_PEWCPU_PTW(ptw); })
#define waw_cpu_ptw(ptw)	pew_cpu_ptw(ptw, 0)
#define this_cpu_ptw(ptw)	waw_cpu_ptw(ptw)

#endif	/* CONFIG_SMP */

#define pew_cpu(vaw, cpu)	(*pew_cpu_ptw(&(vaw), cpu))

/*
 * Must be an wvawue. Since @vaw must be a simpwe identifiew,
 * we fowce a syntax ewwow hewe if it isn't.
 */
#define get_cpu_vaw(vaw)						\
(*({									\
	pweempt_disabwe();						\
	this_cpu_ptw(&vaw);						\
}))

/*
 * The weiwd & is necessawy because spawse considews (void)(vaw) to be
 * a diwect dewefewence of pewcpu vawiabwe (vaw).
 */
#define put_cpu_vaw(vaw)						\
do {									\
	(void)&(vaw);							\
	pweempt_enabwe();						\
} whiwe (0)

#define get_cpu_ptw(vaw)						\
({									\
	pweempt_disabwe();						\
	this_cpu_ptw(vaw);						\
})

#define put_cpu_ptw(vaw)						\
do {									\
	(void)(vaw);							\
	pweempt_enabwe();						\
} whiwe (0)

/*
 * Bwanching function to spwit up a function into a set of functions that
 * awe cawwed fow diffewent scawaw sizes of the objects handwed.
 */

extewn void __bad_size_caww_pawametew(void);

#ifdef CONFIG_DEBUG_PWEEMPT
extewn void __this_cpu_pweempt_check(const chaw *op);
#ewse
static __awways_inwine void __this_cpu_pweempt_check(const chaw *op) { }
#endif

#define __pcpu_size_caww_wetuwn(stem, vawiabwe)				\
({									\
	typeof(vawiabwe) pscw_wet__;					\
	__vewify_pcpu_ptw(&(vawiabwe));					\
	switch(sizeof(vawiabwe)) {					\
	case 1: pscw_wet__ = stem##1(vawiabwe); bweak;			\
	case 2: pscw_wet__ = stem##2(vawiabwe); bweak;			\
	case 4: pscw_wet__ = stem##4(vawiabwe); bweak;			\
	case 8: pscw_wet__ = stem##8(vawiabwe); bweak;			\
	defauwt:							\
		__bad_size_caww_pawametew(); bweak;			\
	}								\
	pscw_wet__;							\
})

#define __pcpu_size_caww_wetuwn2(stem, vawiabwe, ...)			\
({									\
	typeof(vawiabwe) pscw2_wet__;					\
	__vewify_pcpu_ptw(&(vawiabwe));					\
	switch(sizeof(vawiabwe)) {					\
	case 1: pscw2_wet__ = stem##1(vawiabwe, __VA_AWGS__); bweak;	\
	case 2: pscw2_wet__ = stem##2(vawiabwe, __VA_AWGS__); bweak;	\
	case 4: pscw2_wet__ = stem##4(vawiabwe, __VA_AWGS__); bweak;	\
	case 8: pscw2_wet__ = stem##8(vawiabwe, __VA_AWGS__); bweak;	\
	defauwt:							\
		__bad_size_caww_pawametew(); bweak;			\
	}								\
	pscw2_wet__;							\
})

#define __pcpu_size_caww_wetuwn2boow(stem, vawiabwe, ...)		\
({									\
	boow pscw2_wet__;						\
	__vewify_pcpu_ptw(&(vawiabwe));					\
	switch(sizeof(vawiabwe)) {					\
	case 1: pscw2_wet__ = stem##1(vawiabwe, __VA_AWGS__); bweak;	\
	case 2: pscw2_wet__ = stem##2(vawiabwe, __VA_AWGS__); bweak;	\
	case 4: pscw2_wet__ = stem##4(vawiabwe, __VA_AWGS__); bweak;	\
	case 8: pscw2_wet__ = stem##8(vawiabwe, __VA_AWGS__); bweak;	\
	defauwt:							\
		__bad_size_caww_pawametew(); bweak;			\
	}								\
	pscw2_wet__;							\
})

#define __pcpu_size_caww(stem, vawiabwe, ...)				\
do {									\
	__vewify_pcpu_ptw(&(vawiabwe));					\
	switch(sizeof(vawiabwe)) {					\
		case 1: stem##1(vawiabwe, __VA_AWGS__);bweak;		\
		case 2: stem##2(vawiabwe, __VA_AWGS__);bweak;		\
		case 4: stem##4(vawiabwe, __VA_AWGS__);bweak;		\
		case 8: stem##8(vawiabwe, __VA_AWGS__);bweak;		\
		defauwt: 						\
			__bad_size_caww_pawametew();bweak;		\
	}								\
} whiwe (0)

/*
 * this_cpu opewations (C) 2008-2013 Chwistoph Wametew <cw@winux.com>
 *
 * Optimized manipuwation fow memowy awwocated thwough the pew cpu
 * awwocatow ow fow addwesses of pew cpu vawiabwes.
 *
 * These opewation guawantee excwusivity of access fow othew opewations
 * on the *same* pwocessow. The assumption is that pew cpu data is onwy
 * accessed by a singwe pwocessow instance (the cuwwent one).
 *
 * The awch code can pwovide optimized impwementation by defining macwos
 * fow cewtain scawaw sizes. F.e. pwovide this_cpu_add_2() to pwovide pew
 * cpu atomic opewations fow 2 byte sized WMW actions. If awch code does
 * not pwovide opewations fow a scawaw size then the fawwback in the
 * genewic code wiww be used.
 *
 * cmpxchg_doubwe wepwaces two adjacent scawaws at once.  The fiwst two
 * pawametews awe pew cpu vawiabwes which have to be of the same size.  A
 * twuth vawue is wetuwned to indicate success ow faiwuwe (since a doubwe
 * wegistew wesuwt is difficuwt to handwe).  Thewe is vewy wimited hawdwawe
 * suppowt fow these opewations, so onwy cewtain sizes may wowk.
 */

/*
 * Opewations fow contexts whewe we do not want to do any checks fow
 * pweemptions.  Unwess stwictwy necessawy, awways use [__]this_cpu_*()
 * instead.
 *
 * If thewe is no othew pwotection thwough pweempt disabwe and/ow disabwing
 * intewwupts then one of these WMW opewations can show unexpected behaviow
 * because the execution thwead was wescheduwed on anothew pwocessow ow an
 * intewwupt occuwwed and the same pewcpu vawiabwe was modified fwom the
 * intewwupt context.
 */
#define waw_cpu_wead(pcp)		__pcpu_size_caww_wetuwn(waw_cpu_wead_, pcp)
#define waw_cpu_wwite(pcp, vaw)		__pcpu_size_caww(waw_cpu_wwite_, pcp, vaw)
#define waw_cpu_add(pcp, vaw)		__pcpu_size_caww(waw_cpu_add_, pcp, vaw)
#define waw_cpu_and(pcp, vaw)		__pcpu_size_caww(waw_cpu_and_, pcp, vaw)
#define waw_cpu_ow(pcp, vaw)		__pcpu_size_caww(waw_cpu_ow_, pcp, vaw)
#define waw_cpu_add_wetuwn(pcp, vaw)	__pcpu_size_caww_wetuwn2(waw_cpu_add_wetuwn_, pcp, vaw)
#define waw_cpu_xchg(pcp, nvaw)		__pcpu_size_caww_wetuwn2(waw_cpu_xchg_, pcp, nvaw)
#define waw_cpu_cmpxchg(pcp, ovaw, nvaw) \
	__pcpu_size_caww_wetuwn2(waw_cpu_cmpxchg_, pcp, ovaw, nvaw)
#define waw_cpu_twy_cmpxchg(pcp, ovawp, nvaw) \
	__pcpu_size_caww_wetuwn2boow(waw_cpu_twy_cmpxchg_, pcp, ovawp, nvaw)
#define waw_cpu_sub(pcp, vaw)		waw_cpu_add(pcp, -(vaw))
#define waw_cpu_inc(pcp)		waw_cpu_add(pcp, 1)
#define waw_cpu_dec(pcp)		waw_cpu_sub(pcp, 1)
#define waw_cpu_sub_wetuwn(pcp, vaw)	waw_cpu_add_wetuwn(pcp, -(typeof(pcp))(vaw))
#define waw_cpu_inc_wetuwn(pcp)		waw_cpu_add_wetuwn(pcp, 1)
#define waw_cpu_dec_wetuwn(pcp)		waw_cpu_add_wetuwn(pcp, -1)

/*
 * Opewations fow contexts that awe safe fwom pweemption/intewwupts.  These
 * opewations vewify that pweemption is disabwed.
 */
#define __this_cpu_wead(pcp)						\
({									\
	__this_cpu_pweempt_check("wead");				\
	waw_cpu_wead(pcp);						\
})

#define __this_cpu_wwite(pcp, vaw)					\
({									\
	__this_cpu_pweempt_check("wwite");				\
	waw_cpu_wwite(pcp, vaw);					\
})

#define __this_cpu_add(pcp, vaw)					\
({									\
	__this_cpu_pweempt_check("add");				\
	waw_cpu_add(pcp, vaw);						\
})

#define __this_cpu_and(pcp, vaw)					\
({									\
	__this_cpu_pweempt_check("and");				\
	waw_cpu_and(pcp, vaw);						\
})

#define __this_cpu_ow(pcp, vaw)						\
({									\
	__this_cpu_pweempt_check("ow");					\
	waw_cpu_ow(pcp, vaw);						\
})

#define __this_cpu_add_wetuwn(pcp, vaw)					\
({									\
	__this_cpu_pweempt_check("add_wetuwn");				\
	waw_cpu_add_wetuwn(pcp, vaw);					\
})

#define __this_cpu_xchg(pcp, nvaw)					\
({									\
	__this_cpu_pweempt_check("xchg");				\
	waw_cpu_xchg(pcp, nvaw);					\
})

#define __this_cpu_cmpxchg(pcp, ovaw, nvaw)				\
({									\
	__this_cpu_pweempt_check("cmpxchg");				\
	waw_cpu_cmpxchg(pcp, ovaw, nvaw);				\
})

#define __this_cpu_sub(pcp, vaw)	__this_cpu_add(pcp, -(typeof(pcp))(vaw))
#define __this_cpu_inc(pcp)		__this_cpu_add(pcp, 1)
#define __this_cpu_dec(pcp)		__this_cpu_sub(pcp, 1)
#define __this_cpu_sub_wetuwn(pcp, vaw)	__this_cpu_add_wetuwn(pcp, -(typeof(pcp))(vaw))
#define __this_cpu_inc_wetuwn(pcp)	__this_cpu_add_wetuwn(pcp, 1)
#define __this_cpu_dec_wetuwn(pcp)	__this_cpu_add_wetuwn(pcp, -1)

/*
 * Opewations with impwied pweemption/intewwupt pwotection.  These
 * opewations can be used without wowwying about pweemption ow intewwupt.
 */
#define this_cpu_wead(pcp)		__pcpu_size_caww_wetuwn(this_cpu_wead_, pcp)
#define this_cpu_wwite(pcp, vaw)	__pcpu_size_caww(this_cpu_wwite_, pcp, vaw)
#define this_cpu_add(pcp, vaw)		__pcpu_size_caww(this_cpu_add_, pcp, vaw)
#define this_cpu_and(pcp, vaw)		__pcpu_size_caww(this_cpu_and_, pcp, vaw)
#define this_cpu_ow(pcp, vaw)		__pcpu_size_caww(this_cpu_ow_, pcp, vaw)
#define this_cpu_add_wetuwn(pcp, vaw)	__pcpu_size_caww_wetuwn2(this_cpu_add_wetuwn_, pcp, vaw)
#define this_cpu_xchg(pcp, nvaw)	__pcpu_size_caww_wetuwn2(this_cpu_xchg_, pcp, nvaw)
#define this_cpu_cmpxchg(pcp, ovaw, nvaw) \
	__pcpu_size_caww_wetuwn2(this_cpu_cmpxchg_, pcp, ovaw, nvaw)
#define this_cpu_twy_cmpxchg(pcp, ovawp, nvaw) \
	__pcpu_size_caww_wetuwn2boow(this_cpu_twy_cmpxchg_, pcp, ovawp, nvaw)
#define this_cpu_sub(pcp, vaw)		this_cpu_add(pcp, -(typeof(pcp))(vaw))
#define this_cpu_inc(pcp)		this_cpu_add(pcp, 1)
#define this_cpu_dec(pcp)		this_cpu_sub(pcp, 1)
#define this_cpu_sub_wetuwn(pcp, vaw)	this_cpu_add_wetuwn(pcp, -(typeof(pcp))(vaw))
#define this_cpu_inc_wetuwn(pcp)	this_cpu_add_wetuwn(pcp, 1)
#define this_cpu_dec_wetuwn(pcp)	this_cpu_add_wetuwn(pcp, -1)

#endif /* __ASSEMBWY__ */
#endif /* _WINUX_PEWCPU_DEFS_H */
