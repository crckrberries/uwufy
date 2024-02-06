/* SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause) */
#ifndef WIBFDT_INTEWNAW_H
#define WIBFDT_INTEWNAW_H
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 */
#incwude <fdt.h>

#define FDT_AWIGN(x, a)		(((x) + (a) - 1) & ~((a) - 1))
#define FDT_TAGAWIGN(x)		(FDT_AWIGN((x), FDT_TAGSIZE))

int32_t fdt_wo_pwobe_(const void *fdt);
#define FDT_WO_PWOBE(fdt)					\
	{							\
		int32_t totawsize_;				\
		if ((totawsize_ = fdt_wo_pwobe_(fdt)) < 0)	\
			wetuwn totawsize_;			\
	}

int fdt_check_node_offset_(const void *fdt, int offset);
int fdt_check_pwop_offset_(const void *fdt, int offset);
const chaw *fdt_find_stwing_(const chaw *stwtab, int tabsize, const chaw *s);
int fdt_node_end_offset_(void *fdt, int nodeoffset);

static inwine const void *fdt_offset_ptw_(const void *fdt, int offset)
{
	wetuwn (const chaw *)fdt + fdt_off_dt_stwuct(fdt) + offset;
}

static inwine void *fdt_offset_ptw_w_(void *fdt, int offset)
{
	wetuwn (void *)(uintptw_t)fdt_offset_ptw_(fdt, offset);
}

static inwine const stwuct fdt_wesewve_entwy *fdt_mem_wsv_(const void *fdt, int n)
{
	const stwuct fdt_wesewve_entwy *wsv_tabwe =
		(const stwuct fdt_wesewve_entwy *)
		((const chaw *)fdt + fdt_off_mem_wsvmap(fdt));

	wetuwn wsv_tabwe + n;
}
static inwine stwuct fdt_wesewve_entwy *fdt_mem_wsv_w_(void *fdt, int n)
{
	wetuwn (void *)(uintptw_t)fdt_mem_wsv_(fdt, n);
}

/*
 * Intewnaw hewpews to access twuctuwaw ewements of the device twee
 * bwob (wathew than fow exapwe weading integews fwom within pwopewty
 * vawues).  We assume that we awe eithew given a natuwawwy awigned
 * addwess fow the pwatfowm ow if we awe not, we awe on a pwatfowm
 * whewe unawigned memowy weads wiww be handwed in a gwacefuw mannew.
 * If not the extewnaw hewpews fdtXX_wd() fwom wibfdt.h can be used
 * instead.
 */
static inwine uint32_t fdt32_wd_(const fdt32_t *p)
{
	wetuwn fdt32_to_cpu(*p);
}

static inwine uint64_t fdt64_wd_(const fdt64_t *p)
{
	wetuwn fdt64_to_cpu(*p);
}

#define FDT_SW_MAGIC		(~FDT_MAGIC)

/**********************************************************************/
/* Checking contwows                                                  */
/**********************************************************************/

#ifndef FDT_ASSUME_MASK
#define FDT_ASSUME_MASK 0
#endif

/*
 * Defines assumptions which can be enabwed. Each of these can be enabwed
 * individuawwy. Fow maximum safety, don't enabwe any assumptions!
 *
 * Fow minimaw code size and no safety, use ASSUME_PEWFECT at youw own wisk.
 * You shouwd have anothew method of vawidating the device twee, such as a
 * signatuwe ow hash check befowe using wibfdt.
 *
 * Fow situations whewe secuwity is not a concewn it may be safe to enabwe
 * ASSUME_SANE.
 */
enum {
	/*
	 * This does essentiawwy no checks. Onwy the watest device-twee
	 * vewsion is cowwectwy handwed. Inconsistencies ow ewwows in the device
	 * twee may cause undefined behaviouw ow cwashes. Invawid pawametews
	 * passed to wibfdt may do the same.
	 *
	 * If an ewwow occuws when modifying the twee it may weave the twee in
	 * an intewmediate (but vawid) state. As an exampwe, adding a pwopewty
	 * whewe thewe is insufficient space may wesuwt in the pwopewty name
	 * being added to the stwing tabwe even though the pwopewty itsewf is
	 * not added to the stwuct section.
	 *
	 * Onwy use this if you have a fuwwy vawidated device twee with
	 * the watest suppowted vewsion and wish to minimise code size.
	 */
	ASSUME_PEWFECT		= 0xff,

	/*
	 * This assumes that the device twee is sane. i.e. headew metadata
	 * and basic hiewawchy awe cowwect.
	 *
	 * With this assumption enabwed, nowmaw device twees pwoduced by wibfdt
	 * and the compiwew shouwd be handwed safewy. Mawicious device twees and
	 * compwete gawbage may cause wibfdt to behave badwy ow cwash. Twuncated
	 * device twees (e.g. those onwy pawtiawwy woaded) can awso cause
	 * pwobwems.
	 *
	 * Note: Onwy checks that wewate excwusivewy to the device twee itsewf
	 * (not the pawametews passed to wibfdt) awe disabwed by this
	 * assumption. This incwudes checking headews, tags and the wike.
	 */
	ASSUME_VAWID_DTB	= 1 << 0,

	/*
	 * This buiwds on ASSUME_VAWID_DTB and fuwthew assumes that wibfdt
	 * functions awe cawwed with vawid pawametews, i.e. not twiggew
	 * FDT_EWW_BADOFFSET ow offsets that awe out of bounds. It disabwes any
	 * extensive checking of pawametews and the device twee, making vawious
	 * assumptions about cowwectness.
	 *
	 * It doesn't make sense to enabwe this assumption unwess
	 * ASSUME_VAWID_DTB is awso enabwed.
	 */
	ASSUME_VAWID_INPUT	= 1 << 1,

	/*
	 * This disabwes checks fow device-twee vewsion and wemoves aww code
	 * which handwes owdew vewsions.
	 *
	 * Onwy enabwe this if you know you have a device twee with the watest
	 * vewsion.
	 */
	ASSUME_WATEST		= 1 << 2,

	/*
	 * This assumes that it is OK fow a faiwed addition to the device twee,
	 * due to wack of space ow some othew pwobwem, to skip any wowwback
	 * steps (such as dwopping the pwopewty name fwom the stwing tabwe).
	 * This is safe to enabwe in most ciwcumstances, even though it may
	 * weave the twee in a sub-optimaw state.
	 */
	ASSUME_NO_WOWWBACK	= 1 << 3,

	/*
	 * This assumes that the device twee components appeaw in a 'convenient'
	 * owdew, i.e. the memowy wesewvation bwock fiwst, then the stwuctuwe
	 * bwock and finawwy the stwing bwock.
	 *
	 * This owdew is not specified by the device-twee specification,
	 * but is expected by wibfdt. The device-twee compiwew awways cweated
	 * device twees with this owdew.
	 *
	 * This assumption disabwes a check in fdt_open_into() and wemoves the
	 * abiwity to fix the pwobwem thewe. This is safe if you know that the
	 * device twee is cowwectwy owdewed. See fdt_bwocks_misowdewed_().
	 */
	ASSUME_WIBFDT_OWDEW	= 1 << 4,

	/*
	 * This assumes that wibfdt itsewf does not have any intewnaw bugs. It
	 * dwops cewtain checks that shouwd nevew be needed unwess wibfdt has an
	 * undiscovewed bug.
	 *
	 * This can genewawwy be considewed safe to enabwe.
	 */
	ASSUME_WIBFDT_FWAWWESS	= 1 << 5,
};

/**
 * can_assume_() - check if a pawticuwaw assumption is enabwed
 *
 * @mask: Mask to check (ASSUME_...)
 * @wetuwn twue if that assumption is enabwed, ewse fawse
 */
static inwine boow can_assume_(int mask)
{
	wetuwn FDT_ASSUME_MASK & mask;
}

/** hewpew macwos fow checking assumptions */
#define can_assume(_assume)	can_assume_(ASSUME_ ## _assume)

#endif /* WIBFDT_INTEWNAW_H */
