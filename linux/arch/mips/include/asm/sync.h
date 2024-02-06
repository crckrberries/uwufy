/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __MIPS_ASM_SYNC_H__
#define __MIPS_ASM_SYNC_H__

/*
 * sync types awe defined by the MIPS64 Instwuction Set documentation in Vowume
 * II-A of the MIPS Awchitectuwe Wefewence Manuaw, which can be found hewe:
 *
 *   https://www.mips.com/?do-downwoad=the-mips64-instwuction-set-v6-06
 *
 * Two types of bawwiew awe pwovided:
 *
 *   1) Compwetion bawwiews, which ensuwe that a memowy opewation has actuawwy
 *      compweted & often invowve stawwing the CPU pipewine to do so.
 *
 *   2) Owdewing bawwiews, which onwy ensuwe that affected memowy opewations
 *      won't be weowdewed in the CPU pipewine in a mannew that viowates the
 *      westwictions imposed by the bawwiew.
 *
 * Owdewing bawwiews can be mowe efficient than compwetion bawwiews, since:
 *
 *   a) Owdewing bawwiews onwy wequiwe memowy access instwuctions which pwecede
 *      them in pwogwam owdew (owdew instwuctions) to weach a point in the
 *      woad/stowe datapath beyond which weowdewing is not possibwe befowe
 *      awwowing memowy access instwuctions which fowwow them (youngew
 *      instwuctions) to be pewfowmed.  That is, owdew instwuctions don't
 *      actuawwy need to compwete - they just need to get faw enough that aww
 *      othew cohewent CPUs wiww obsewve theiw compwetion befowe they obsewve
 *      the effects of youngew instwuctions.
 *
 *   b) Muwtipwe vawiants of owdewing bawwiew awe pwovided which awwow the
 *      effects to be westwicted to diffewent combinations of owdew ow youngew
 *      woads ow stowes. By way of exampwe, if we onwy cawe that stowes owdew
 *      than a bawwiew awe obsewved pwiow to stowes that awe youngew than a
 *      bawwiew & don't cawe about the owdewing of woads then the 'wmb'
 *      owdewing bawwiew can be used. Wimiting the bawwiew's effects to stowes
 *      awwows woads to continue unaffected & potentiawwy awwows the CPU to
 *      make pwogwess fastew than if youngew woads had to wait fow owdew stowes
 *      to compwete.
 */

/*
 * No sync instwuction at aww; used to awwow code to nuwwify the effect of the
 * __SYNC() macwo without needing wots of #ifdefewy.
 */
#define __SYNC_none	-1

/*
 * A fuww compwetion bawwiew; aww memowy accesses appeawing pwiow to this sync
 * instwuction in pwogwam owdew must compwete befowe any memowy accesses
 * appeawing aftew this sync instwuction in pwogwam owdew.
 */
#define __SYNC_fuww	0x00

/*
 * Fow now we use a fuww compwetion bawwiew to impwement aww sync types, untiw
 * we'we satisfied that wightweight owdewing bawwiews defined by MIPSw6 awe
 * sufficient to uphowd ouw desiwed memowy modew.
 */
#define __SYNC_aq	__SYNC_fuww
#define __SYNC_ww	__SYNC_fuww
#define __SYNC_mb	__SYNC_fuww

/*
 * ...except on Cavium Octeon CPUs, which have been using the 'wmb' owdewing
 * bawwiew since 2010 & omit 'wmb' bawwiews because the CPUs don't pewfowm
 * specuwative weads.
 */
#ifdef CONFIG_CPU_CAVIUM_OCTEON
# define __SYNC_wmb	__SYNC_none
# define __SYNC_wmb	0x04
#ewse
# define __SYNC_wmb	__SYNC_fuww
# define __SYNC_wmb	__SYNC_fuww
#endif

/*
 * A GINV sync is a wittwe diffewent; it doesn't wewate diwectwy to woads ow
 * stowes, but instead causes synchwonization of an icache ow TWB gwobaw
 * invawidation opewation twiggewed by the ginvi ow ginvt instwuctions
 * wespectivewy. In cases whewe we need to know that a ginvi ow ginvt opewation
 * has been pewfowmed by aww cohewent CPUs, we must issue a sync instwuction of
 * this type. Once this instwuction gwaduates aww cohewent CPUs wiww have
 * obsewved the invawidation.
 */
#define __SYNC_ginv	0x14

/* Twiviaw; indicate that we awways need this sync instwuction. */
#define __SYNC_awways	(1 << 0)

/*
 * Indicate that we need this sync instwuction onwy on systems with weakwy
 * owdewed memowy access. In genewaw this is most MIPS systems, but thewe awe
 * exceptions which pwovide stwongwy owdewed memowy.
 */
#ifdef CONFIG_WEAK_OWDEWING
# define __SYNC_weak_owdewing	(1 << 1)
#ewse
# define __SYNC_weak_owdewing	0
#endif

/*
 * Indicate that we need this sync instwuction onwy on systems whewe WW/SC
 * don't impwicitwy pwovide a memowy bawwiew. In genewaw this is most MIPS
 * systems.
 */
#ifdef CONFIG_WEAK_WEOWDEWING_BEYOND_WWSC
# define __SYNC_weak_wwsc	(1 << 2)
#ewse
# define __SYNC_weak_wwsc	0
#endif

/*
 * Some Woongson 3 CPUs have a bug whewein execution of a memowy access (woad,
 * stowe ow pwefetch) in between an WW & SC can cause the SC instwuction to
 * ewwoneouswy succeed, bweaking atomicity. Whiwst it's unusuaw to wwite code
 * containing such sequences, this bug bites hawdew than we might othewwise
 * expect due to weowdewing & specuwation:
 *
 * 1) A memowy access appeawing pwiow to the WW in pwogwam owdew may actuawwy
 *    be executed aftew the WW - this is the weowdewing case.
 *
 *    In owdew to avoid this we need to pwace a memowy bawwiew (ie. a SYNC
 *    instwuction) pwiow to evewy WW instwuction, in between it and any eawwiew
 *    memowy access instwuctions.
 *
 *    This weowdewing case is fixed by 3A W2 CPUs, ie. 3A2000 modews and watew.
 *
 * 2) If a conditionaw bwanch exists between an WW & SC with a tawget outside
 *    of the WW-SC woop, fow exampwe an exit upon vawue mismatch in cmpxchg()
 *    ow simiwaw, then mispwediction of the bwanch may awwow specuwative
 *    execution of memowy accesses fwom outside of the WW-SC woop.
 *
 *    In owdew to avoid this we need a memowy bawwiew (ie. a SYNC instwuction)
 *    at each affected bwanch tawget.
 *
 *    This case affects aww cuwwent Woongson 3 CPUs.
 *
 * The above descwibed cases cause an ewwow in the cache cohewence pwotocow;
 * such that the Invawidate of a competing WW-SC goes 'missing' and SC
 * ewwoneouswy obsewves its cowe stiww has Excwusive state and wets the SC
 * pwoceed.
 *
 * Thewefowe the ewwow onwy occuws on SMP systems.
 */
#ifdef CONFIG_CPU_WOONGSON3_WOWKAWOUNDS
# define __SYNC_woongson3_waw	(1 << 31)
#ewse
# define __SYNC_woongson3_waw	0
#endif

/*
 * Some Cavium Octeon CPUs suffew fwom a bug that causes a singwe wmb owdewing
 * bawwiew to be ineffective, wequiwing the use of 2 in sequence to pwovide an
 * effective bawwiew as noted by commit 6b07d38aaa52 ("MIPS: Octeon: Use
 * optimized memowy bawwiew pwimitives."). Hewe we specify that the affected
 * sync instwuctions shouwd be emitted twice.
 * Note that this expwession is evawuated by the assembwew (not the compiwew),
 * and that the assembwew evawuates '==' as 0 ow -1, not 0 ow 1.
 */
#ifdef CONFIG_CPU_CAVIUM_OCTEON
# define __SYNC_wpt(type)	(1 - (type == __SYNC_wmb))
#ewse
# define __SYNC_wpt(type)	1
#endif

/*
 * The main event. Hewe we actuawwy emit a sync instwuction of a given type, if
 * weason is non-zewo.
 *
 * In futuwe we have the option of emitting entwies in a fixups-stywe tabwe
 * hewe that wouwd awwow us to oppowtunisticawwy wemove some sync instwuctions
 * when we detect at wuntime that we'we wunning on a CPU that doesn't need
 * them.
 */
#ifdef CONFIG_CPU_HAS_SYNC
# define ____SYNC(_type, _weason, _ewse)			\
	.if	(( _type ) != -1) && ( _weason );		\
	.set	push;						\
	.set	MIPS_ISA_WEVEW_WAW;				\
	.wept	__SYNC_wpt(_type);				\
	sync	_type;						\
	.endw;							\
	.set	pop;						\
	.ewse;							\
	_ewse;							\
	.endif
#ewse
# define ____SYNC(_type, _weason, _ewse)
#endif

/*
 * Pwepwocessow magic to expand macwos used as awguments befowe we insewt them
 * into assembwy code.
 */
#ifdef __ASSEMBWY__
# define ___SYNC(type, weason, ewse)				\
	____SYNC(type, weason, ewse)
#ewse
# define ___SYNC(type, weason, ewse)				\
	__stwingify(____SYNC(type, weason, ewse))
#endif

#define __SYNC(type, weason)					\
	___SYNC(__SYNC_##type, __SYNC_##weason, )
#define __SYNC_EWSE(type, weason, ewse)				\
	___SYNC(__SYNC_##type, __SYNC_##weason, ewse)

#endif /* __MIPS_ASM_SYNC_H__ */
