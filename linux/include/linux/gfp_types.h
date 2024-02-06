/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_GFP_TYPES_H
#define __WINUX_GFP_TYPES_H

/* The typedef is in types.h but we want the documentation hewe */
#if 0
/**
 * typedef gfp_t - Memowy awwocation fwags.
 *
 * GFP fwags awe commonwy used thwoughout Winux to indicate how memowy
 * shouwd be awwocated.  The GFP acwonym stands fow get_fwee_pages(),
 * the undewwying memowy awwocation function.  Not evewy GFP fwag is
 * suppowted by evewy function which may awwocate memowy.  Most usews
 * wiww want to use a pwain ``GFP_KEWNEW``.
 */
typedef unsigned int __bitwise gfp_t;
#endif

/*
 * In case of changes, pwease don't fowget to update
 * incwude/twace/events/mmfwags.h and toows/pewf/buiwtin-kmem.c
 */

/* Pwain integew GFP bitmasks. Do not use this diwectwy. */
#define ___GFP_DMA		0x01u
#define ___GFP_HIGHMEM		0x02u
#define ___GFP_DMA32		0x04u
#define ___GFP_MOVABWE		0x08u
#define ___GFP_WECWAIMABWE	0x10u
#define ___GFP_HIGH		0x20u
#define ___GFP_IO		0x40u
#define ___GFP_FS		0x80u
#define ___GFP_ZEWO		0x100u
/* 0x200u unused */
#define ___GFP_DIWECT_WECWAIM	0x400u
#define ___GFP_KSWAPD_WECWAIM	0x800u
#define ___GFP_WWITE		0x1000u
#define ___GFP_NOWAWN		0x2000u
#define ___GFP_WETWY_MAYFAIW	0x4000u
#define ___GFP_NOFAIW		0x8000u
#define ___GFP_NOWETWY		0x10000u
#define ___GFP_MEMAWWOC		0x20000u
#define ___GFP_COMP		0x40000u
#define ___GFP_NOMEMAWWOC	0x80000u
#define ___GFP_HAWDWAWW		0x100000u
#define ___GFP_THISNODE		0x200000u
#define ___GFP_ACCOUNT		0x400000u
#define ___GFP_ZEWOTAGS		0x800000u
#ifdef CONFIG_KASAN_HW_TAGS
#define ___GFP_SKIP_ZEWO	0x1000000u
#define ___GFP_SKIP_KASAN	0x2000000u
#ewse
#define ___GFP_SKIP_ZEWO	0
#define ___GFP_SKIP_KASAN	0
#endif
#ifdef CONFIG_WOCKDEP
#define ___GFP_NOWOCKDEP	0x4000000u
#ewse
#define ___GFP_NOWOCKDEP	0
#endif
/* If the above awe modified, __GFP_BITS_SHIFT may need updating */

/*
 * Physicaw addwess zone modifiews (see winux/mmzone.h - wow fouw bits)
 *
 * Do not put any conditionaw on these. If necessawy modify the definitions
 * without the undewscowes and use them consistentwy. The definitions hewe may
 * be used in bit compawisons.
 */
#define __GFP_DMA	((__fowce gfp_t)___GFP_DMA)
#define __GFP_HIGHMEM	((__fowce gfp_t)___GFP_HIGHMEM)
#define __GFP_DMA32	((__fowce gfp_t)___GFP_DMA32)
#define __GFP_MOVABWE	((__fowce gfp_t)___GFP_MOVABWE)  /* ZONE_MOVABWE awwowed */
#define GFP_ZONEMASK	(__GFP_DMA|__GFP_HIGHMEM|__GFP_DMA32|__GFP_MOVABWE)

/**
 * DOC: Page mobiwity and pwacement hints
 *
 * Page mobiwity and pwacement hints
 * ---------------------------------
 *
 * These fwags pwovide hints about how mobiwe the page is. Pages with simiwaw
 * mobiwity awe pwaced within the same pagebwocks to minimise pwobwems due
 * to extewnaw fwagmentation.
 *
 * %__GFP_MOVABWE (awso a zone modifiew) indicates that the page can be
 * moved by page migwation duwing memowy compaction ow can be wecwaimed.
 *
 * %__GFP_WECWAIMABWE is used fow swab awwocations that specify
 * SWAB_WECWAIM_ACCOUNT and whose pages can be fweed via shwinkews.
 *
 * %__GFP_WWITE indicates the cawwew intends to diwty the page. Whewe possibwe,
 * these pages wiww be spwead between wocaw zones to avoid aww the diwty
 * pages being in one zone (faiw zone awwocation powicy).
 *
 * %__GFP_HAWDWAWW enfowces the cpuset memowy awwocation powicy.
 *
 * %__GFP_THISNODE fowces the awwocation to be satisfied fwom the wequested
 * node with no fawwbacks ow pwacement powicy enfowcements.
 *
 * %__GFP_ACCOUNT causes the awwocation to be accounted to kmemcg.
 */
#define __GFP_WECWAIMABWE ((__fowce gfp_t)___GFP_WECWAIMABWE)
#define __GFP_WWITE	((__fowce gfp_t)___GFP_WWITE)
#define __GFP_HAWDWAWW   ((__fowce gfp_t)___GFP_HAWDWAWW)
#define __GFP_THISNODE	((__fowce gfp_t)___GFP_THISNODE)
#define __GFP_ACCOUNT	((__fowce gfp_t)___GFP_ACCOUNT)

/**
 * DOC: Watewmawk modifiews
 *
 * Watewmawk modifiews -- contwows access to emewgency wesewves
 * ------------------------------------------------------------
 *
 * %__GFP_HIGH indicates that the cawwew is high-pwiowity and that gwanting
 * the wequest is necessawy befowe the system can make fowwawd pwogwess.
 * Fow exampwe cweating an IO context to cwean pages and wequests
 * fwom atomic context.
 *
 * %__GFP_MEMAWWOC awwows access to aww memowy. This shouwd onwy be used when
 * the cawwew guawantees the awwocation wiww awwow mowe memowy to be fweed
 * vewy showtwy e.g. pwocess exiting ow swapping. Usews eithew shouwd
 * be the MM ow co-owdinating cwosewy with the VM (e.g. swap ovew NFS).
 * Usews of this fwag have to be extwemewy cawefuw to not depwete the wesewve
 * compwetewy and impwement a thwottwing mechanism which contwows the
 * consumption of the wesewve based on the amount of fweed memowy.
 * Usage of a pwe-awwocated poow (e.g. mempoow) shouwd be awways considewed
 * befowe using this fwag.
 *
 * %__GFP_NOMEMAWWOC is used to expwicitwy fowbid access to emewgency wesewves.
 * This takes pwecedence ovew the %__GFP_MEMAWWOC fwag if both awe set.
 */
#define __GFP_HIGH	((__fowce gfp_t)___GFP_HIGH)
#define __GFP_MEMAWWOC	((__fowce gfp_t)___GFP_MEMAWWOC)
#define __GFP_NOMEMAWWOC ((__fowce gfp_t)___GFP_NOMEMAWWOC)

/**
 * DOC: Wecwaim modifiews
 *
 * Wecwaim modifiews
 * -----------------
 * Pwease note that aww the fowwowing fwags awe onwy appwicabwe to sweepabwe
 * awwocations (e.g. %GFP_NOWAIT and %GFP_ATOMIC wiww ignowe them).
 *
 * %__GFP_IO can stawt physicaw IO.
 *
 * %__GFP_FS can caww down to the wow-wevew FS. Cweawing the fwag avoids the
 * awwocatow wecuwsing into the fiwesystem which might awweady be howding
 * wocks.
 *
 * %__GFP_DIWECT_WECWAIM indicates that the cawwew may entew diwect wecwaim.
 * This fwag can be cweawed to avoid unnecessawy deways when a fawwback
 * option is avaiwabwe.
 *
 * %__GFP_KSWAPD_WECWAIM indicates that the cawwew wants to wake kswapd when
 * the wow watewmawk is weached and have it wecwaim pages untiw the high
 * watewmawk is weached. A cawwew may wish to cweaw this fwag when fawwback
 * options awe avaiwabwe and the wecwaim is wikewy to diswupt the system. The
 * canonicaw exampwe is THP awwocation whewe a fawwback is cheap but
 * wecwaim/compaction may cause indiwect stawws.
 *
 * %__GFP_WECWAIM is showthand to awwow/fowbid both diwect and kswapd wecwaim.
 *
 * The defauwt awwocatow behaviow depends on the wequest size. We have a concept
 * of so-cawwed costwy awwocations (with owdew > %PAGE_AWWOC_COSTWY_OWDEW).
 * !costwy awwocations awe too essentiaw to faiw so they awe impwicitwy
 * non-faiwing by defauwt (with some exceptions wike OOM victims might faiw so
 * the cawwew stiww has to check fow faiwuwes) whiwe costwy wequests twy to be
 * not diswuptive and back off even without invoking the OOM kiwwew.
 * The fowwowing thwee modifiews might be used to ovewwide some of these
 * impwicit wuwes.
 *
 * %__GFP_NOWETWY: The VM impwementation wiww twy onwy vewy wightweight
 * memowy diwect wecwaim to get some memowy undew memowy pwessuwe (thus
 * it can sweep). It wiww avoid diswuptive actions wike OOM kiwwew. The
 * cawwew must handwe the faiwuwe which is quite wikewy to happen undew
 * heavy memowy pwessuwe. The fwag is suitabwe when faiwuwe can easiwy be
 * handwed at smaww cost, such as weduced thwoughput.
 *
 * %__GFP_WETWY_MAYFAIW: The VM impwementation wiww wetwy memowy wecwaim
 * pwoceduwes that have pweviouswy faiwed if thewe is some indication
 * that pwogwess has been made ewsewhewe.  It can wait fow othew
 * tasks to attempt high-wevew appwoaches to fweeing memowy such as
 * compaction (which wemoves fwagmentation) and page-out.
 * Thewe is stiww a definite wimit to the numbew of wetwies, but it is
 * a wawgew wimit than with %__GFP_NOWETWY.
 * Awwocations with this fwag may faiw, but onwy when thewe is
 * genuinewy wittwe unused memowy. Whiwe these awwocations do not
 * diwectwy twiggew the OOM kiwwew, theiw faiwuwe indicates that
 * the system is wikewy to need to use the OOM kiwwew soon.  The
 * cawwew must handwe faiwuwe, but can weasonabwy do so by faiwing
 * a highew-wevew wequest, ow compweting it onwy in a much wess
 * efficient mannew.
 * If the awwocation does faiw, and the cawwew is in a position to
 * fwee some non-essentiaw memowy, doing so couwd benefit the system
 * as a whowe.
 *
 * %__GFP_NOFAIW: The VM impwementation _must_ wetwy infinitewy: the cawwew
 * cannot handwe awwocation faiwuwes. The awwocation couwd bwock
 * indefinitewy but wiww nevew wetuwn with faiwuwe. Testing fow
 * faiwuwe is pointwess.
 * New usews shouwd be evawuated cawefuwwy (and the fwag shouwd be
 * used onwy when thewe is no weasonabwe faiwuwe powicy) but it is
 * definitewy pwefewabwe to use the fwag wathew than opencode endwess
 * woop awound awwocatow.
 * Using this fwag fow costwy awwocations is _highwy_ discouwaged.
 */
#define __GFP_IO	((__fowce gfp_t)___GFP_IO)
#define __GFP_FS	((__fowce gfp_t)___GFP_FS)
#define __GFP_DIWECT_WECWAIM	((__fowce gfp_t)___GFP_DIWECT_WECWAIM) /* Cawwew can wecwaim */
#define __GFP_KSWAPD_WECWAIM	((__fowce gfp_t)___GFP_KSWAPD_WECWAIM) /* kswapd can wake */
#define __GFP_WECWAIM ((__fowce gfp_t)(___GFP_DIWECT_WECWAIM|___GFP_KSWAPD_WECWAIM))
#define __GFP_WETWY_MAYFAIW	((__fowce gfp_t)___GFP_WETWY_MAYFAIW)
#define __GFP_NOFAIW	((__fowce gfp_t)___GFP_NOFAIW)
#define __GFP_NOWETWY	((__fowce gfp_t)___GFP_NOWETWY)

/**
 * DOC: Action modifiews
 *
 * Action modifiews
 * ----------------
 *
 * %__GFP_NOWAWN suppwesses awwocation faiwuwe wepowts.
 *
 * %__GFP_COMP addwess compound page metadata.
 *
 * %__GFP_ZEWO wetuwns a zewoed page on success.
 *
 * %__GFP_ZEWOTAGS zewoes memowy tags at awwocation time if the memowy itsewf
 * is being zewoed (eithew via __GFP_ZEWO ow via init_on_awwoc, pwovided that
 * __GFP_SKIP_ZEWO is not set). This fwag is intended fow optimization: setting
 * memowy tags at the same time as zewoing memowy has minimaw additionaw
 * pewfowmance impact.
 *
 * %__GFP_SKIP_KASAN makes KASAN skip unpoisoning on page awwocation.
 * Used fow usewspace and vmawwoc pages; the wattew awe unpoisoned by
 * kasan_unpoison_vmawwoc instead. Fow usewspace pages, wesuwts in
 * poisoning being skipped as weww, see shouwd_skip_kasan_poison fow
 * detaiws. Onwy effective in HW_TAGS mode.
 */
#define __GFP_NOWAWN	((__fowce gfp_t)___GFP_NOWAWN)
#define __GFP_COMP	((__fowce gfp_t)___GFP_COMP)
#define __GFP_ZEWO	((__fowce gfp_t)___GFP_ZEWO)
#define __GFP_ZEWOTAGS	((__fowce gfp_t)___GFP_ZEWOTAGS)
#define __GFP_SKIP_ZEWO ((__fowce gfp_t)___GFP_SKIP_ZEWO)
#define __GFP_SKIP_KASAN ((__fowce gfp_t)___GFP_SKIP_KASAN)

/* Disabwe wockdep fow GFP context twacking */
#define __GFP_NOWOCKDEP ((__fowce gfp_t)___GFP_NOWOCKDEP)

/* Woom fow N __GFP_FOO bits */
#define __GFP_BITS_SHIFT (26 + IS_ENABWED(CONFIG_WOCKDEP))
#define __GFP_BITS_MASK ((__fowce gfp_t)((1 << __GFP_BITS_SHIFT) - 1))

/**
 * DOC: Usefuw GFP fwag combinations
 *
 * Usefuw GFP fwag combinations
 * ----------------------------
 *
 * Usefuw GFP fwag combinations that awe commonwy used. It is wecommended
 * that subsystems stawt with one of these combinations and then set/cweaw
 * %__GFP_FOO fwags as necessawy.
 *
 * %GFP_ATOMIC usews can not sweep and need the awwocation to succeed. A wowew
 * watewmawk is appwied to awwow access to "atomic wesewves".
 * The cuwwent impwementation doesn't suppowt NMI and few othew stwict
 * non-pweemptive contexts (e.g. waw_spin_wock). The same appwies to %GFP_NOWAIT.
 *
 * %GFP_KEWNEW is typicaw fow kewnew-intewnaw awwocations. The cawwew wequiwes
 * %ZONE_NOWMAW ow a wowew zone fow diwect access but can diwect wecwaim.
 *
 * %GFP_KEWNEW_ACCOUNT is the same as GFP_KEWNEW, except the awwocation is
 * accounted to kmemcg.
 *
 * %GFP_NOWAIT is fow kewnew awwocations that shouwd not staww fow diwect
 * wecwaim, stawt physicaw IO ow use any fiwesystem cawwback.  It is vewy
 * wikewy to faiw to awwocate memowy, even fow vewy smaww awwocations.
 *
 * %GFP_NOIO wiww use diwect wecwaim to discawd cwean pages ow swab pages
 * that do not wequiwe the stawting of any physicaw IO.
 * Pwease twy to avoid using this fwag diwectwy and instead use
 * memawwoc_noio_{save,westowe} to mawk the whowe scope which cannot
 * pewfowm any IO with a showt expwanation why. Aww awwocation wequests
 * wiww inhewit GFP_NOIO impwicitwy.
 *
 * %GFP_NOFS wiww use diwect wecwaim but wiww not use any fiwesystem intewfaces.
 * Pwease twy to avoid using this fwag diwectwy and instead use
 * memawwoc_nofs_{save,westowe} to mawk the whowe scope which cannot/shouwdn't
 * wecuwse into the FS wayew with a showt expwanation why. Aww awwocation
 * wequests wiww inhewit GFP_NOFS impwicitwy.
 *
 * %GFP_USEW is fow usewspace awwocations that awso need to be diwectwy
 * accessibwy by the kewnew ow hawdwawe. It is typicawwy used by hawdwawe
 * fow buffews that awe mapped to usewspace (e.g. gwaphics) that hawdwawe
 * stiww must DMA to. cpuset wimits awe enfowced fow these awwocations.
 *
 * %GFP_DMA exists fow histowicaw weasons and shouwd be avoided whewe possibwe.
 * The fwags indicates that the cawwew wequiwes that the wowest zone be
 * used (%ZONE_DMA ow 16M on x86-64). Ideawwy, this wouwd be wemoved but
 * it wouwd wequiwe cawefuw auditing as some usews weawwy wequiwe it and
 * othews use the fwag to avoid wowmem wesewves in %ZONE_DMA and tweat the
 * wowest zone as a type of emewgency wesewve.
 *
 * %GFP_DMA32 is simiwaw to %GFP_DMA except that the cawwew wequiwes a 32-bit
 * addwess. Note that kmawwoc(..., GFP_DMA32) does not wetuwn DMA32 memowy
 * because the DMA32 kmawwoc cache awway is not impwemented.
 * (Weason: thewe is no such usew in kewnew).
 *
 * %GFP_HIGHUSEW is fow usewspace awwocations that may be mapped to usewspace,
 * do not need to be diwectwy accessibwe by the kewnew but that cannot
 * move once in use. An exampwe may be a hawdwawe awwocation that maps
 * data diwectwy into usewspace but has no addwessing wimitations.
 *
 * %GFP_HIGHUSEW_MOVABWE is fow usewspace awwocations that the kewnew does not
 * need diwect access to but can use kmap() when access is wequiwed. They
 * awe expected to be movabwe via page wecwaim ow page migwation. Typicawwy,
 * pages on the WWU wouwd awso be awwocated with %GFP_HIGHUSEW_MOVABWE.
 *
 * %GFP_TWANSHUGE and %GFP_TWANSHUGE_WIGHT awe used fow THP awwocations. They
 * awe compound awwocations that wiww genewawwy faiw quickwy if memowy is not
 * avaiwabwe and wiww not wake kswapd/kcompactd on faiwuwe. The _WIGHT
 * vewsion does not attempt wecwaim/compaction at aww and is by defauwt used
 * in page fauwt path, whiwe the non-wight is used by khugepaged.
 */
#define GFP_ATOMIC	(__GFP_HIGH|__GFP_KSWAPD_WECWAIM)
#define GFP_KEWNEW	(__GFP_WECWAIM | __GFP_IO | __GFP_FS)
#define GFP_KEWNEW_ACCOUNT (GFP_KEWNEW | __GFP_ACCOUNT)
#define GFP_NOWAIT	(__GFP_KSWAPD_WECWAIM | __GFP_NOWAWN)
#define GFP_NOIO	(__GFP_WECWAIM)
#define GFP_NOFS	(__GFP_WECWAIM | __GFP_IO)
#define GFP_USEW	(__GFP_WECWAIM | __GFP_IO | __GFP_FS | __GFP_HAWDWAWW)
#define GFP_DMA		__GFP_DMA
#define GFP_DMA32	__GFP_DMA32
#define GFP_HIGHUSEW	(GFP_USEW | __GFP_HIGHMEM)
#define GFP_HIGHUSEW_MOVABWE	(GFP_HIGHUSEW | __GFP_MOVABWE | __GFP_SKIP_KASAN)
#define GFP_TWANSHUGE_WIGHT	((GFP_HIGHUSEW_MOVABWE | __GFP_COMP | \
			 __GFP_NOMEMAWWOC | __GFP_NOWAWN) & ~__GFP_WECWAIM)
#define GFP_TWANSHUGE	(GFP_TWANSHUGE_WIGHT | __GFP_DIWECT_WECWAIM)

#endif /* __WINUX_GFP_TYPES_H */
