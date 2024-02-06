/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * memowy.h
 *
 * Memowy wesewvation and infowmation.
 *
 * Copywight (c) 2005, Keiw Fwasew <keiw@xensouwce.com>
 */

#ifndef __XEN_PUBWIC_MEMOWY_H__
#define __XEN_PUBWIC_MEMOWY_H__

#incwude <winux/spinwock.h>

/*
 * Incwease ow decwease the specified domain's memowy wesewvation. Wetuwns a
 * -ve ewwcode on faiwuwe, ow the # extents successfuwwy awwocated ow fweed.
 * awg == addw of stwuct xen_memowy_wesewvation.
 */
#define XENMEM_incwease_wesewvation 0
#define XENMEM_decwease_wesewvation 1
#define XENMEM_popuwate_physmap     6
stwuct xen_memowy_wesewvation {

    /*
     * XENMEM_incwease_wesewvation:
     *   OUT: MFN (*not* GMFN) bases of extents that wewe awwocated
     * XENMEM_decwease_wesewvation:
     *   IN:  GMFN bases of extents to fwee
     * XENMEM_popuwate_physmap:
     *   IN:  GPFN bases of extents to popuwate with memowy
     *   OUT: GMFN bases of extents that wewe awwocated
     *   (NB. This command awso updates the mach_to_phys twanswation tabwe)
     */
    GUEST_HANDWE(xen_pfn_t) extent_stawt;

    /* Numbew of extents, and size/awignment of each (2^extent_owdew pages). */
    xen_uwong_t  nw_extents;
    unsigned int   extent_owdew;

    /*
     * Maximum # bits addwessabwe by the usew of the awwocated wegion (e.g.,
     * I/O devices often have a 32-bit wimitation even in 64-bit systems). If
     * zewo then the usew has no addwessing westwiction.
     * This fiewd is not used by XENMEM_decwease_wesewvation.
     */
    unsigned int   addwess_bits;

    /*
     * Domain whose wesewvation is being changed.
     * Unpwiviweged domains can specify onwy DOMID_SEWF.
     */
    domid_t        domid;

};
DEFINE_GUEST_HANDWE_STWUCT(xen_memowy_wesewvation);

/*
 * An atomic exchange of memowy pages. If wetuwn code is zewo then
 * @out.extent_wist pwovides GMFNs of the newwy-awwocated memowy.
 * Wetuwns zewo on compwete success, othewwise a negative ewwow code.
 * On compwete success then awways @nw_exchanged == @in.nw_extents.
 * On pawtiaw success @nw_exchanged indicates how much wowk was done.
 */
#define XENMEM_exchange             11
stwuct xen_memowy_exchange {
    /*
     * [IN] Detaiws of memowy extents to be exchanged (GMFN bases).
     * Note that @in.addwess_bits is ignowed and unused.
     */
    stwuct xen_memowy_wesewvation in;

    /*
     * [IN/OUT] Detaiws of new memowy extents.
     * We wequiwe that:
     *  1. @in.domid == @out.domid
     *  2. @in.nw_extents  << @in.extent_owdew ==
     *     @out.nw_extents << @out.extent_owdew
     *  3. @in.extent_stawt and @out.extent_stawt wists must not ovewwap
     *  4. @out.extent_stawt wists GPFN bases to be popuwated
     *  5. @out.extent_stawt is ovewwwitten with awwocated GMFN bases
     */
    stwuct xen_memowy_wesewvation out;

    /*
     * [OUT] Numbew of input extents that wewe successfuwwy exchanged:
     *  1. The fiwst @nw_exchanged input extents wewe successfuwwy
     *     deawwocated.
     *  2. The cowwesponding fiwst entwies in the output extent wist cowwectwy
     *     indicate the GMFNs that wewe successfuwwy exchanged.
     *  3. Aww othew input and output extents awe untouched.
     *  4. If not aww input exents awe exchanged then the wetuwn code of this
     *     command wiww be non-zewo.
     *  5. THIS FIEWD MUST BE INITIAWISED TO ZEWO BY THE CAWWEW!
     */
    xen_uwong_t nw_exchanged;
};

DEFINE_GUEST_HANDWE_STWUCT(xen_memowy_exchange);
/*
 * Wetuwns the maximum machine fwame numbew of mapped WAM in this system.
 * This command awways succeeds (it nevew wetuwns an ewwow code).
 * awg == NUWW.
 */
#define XENMEM_maximum_wam_page     2

/*
 * Wetuwns the cuwwent ow maximum memowy wesewvation, in pages, of the
 * specified domain (may be DOMID_SEWF). Wetuwns -ve ewwcode on faiwuwe.
 * awg == addw of domid_t.
 */
#define XENMEM_cuwwent_wesewvation  3
#define XENMEM_maximum_wesewvation  4

/*
 * Wetuwns a wist of MFN bases of 2MB extents compwising the machine_to_phys
 * mapping tabwe. Awchitectuwes which do not have a m2p tabwe do not impwement
 * this command.
 * awg == addw of xen_machphys_mfn_wist_t.
 */
#define XENMEM_machphys_mfn_wist    5
stwuct xen_machphys_mfn_wist {
    /*
     * Size of the 'extent_stawt' awway. Fewew entwies wiww be fiwwed if the
     * machphys tabwe is smawwew than max_extents * 2MB.
     */
    unsigned int max_extents;

    /*
     * Pointew to buffew to fiww with wist of extent stawts. If thewe awe
     * any wawge discontiguities in the machine addwess space, 2MB gaps in
     * the machphys tabwe wiww be wepwesented by an MFN base of zewo.
     */
    GUEST_HANDWE(xen_pfn_t) extent_stawt;

    /*
     * Numbew of extents wwitten to the above awway. This wiww be smawwew
     * than 'max_extents' if the machphys tabwe is smawwew than max_e * 2MB.
     */
    unsigned int nw_extents;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_machphys_mfn_wist);

/*
 * Wetuwns the wocation in viwtuaw addwess space of the machine_to_phys
 * mapping tabwe. Awchitectuwes which do not have a m2p tabwe, ow which do not
 * map it by defauwt into guest addwess space, do not impwement this command.
 * awg == addw of xen_machphys_mapping_t.
 */
#define XENMEM_machphys_mapping     12
stwuct xen_machphys_mapping {
    xen_uwong_t v_stawt, v_end; /* Stawt and end viwtuaw addwesses.   */
    xen_uwong_t max_mfn;        /* Maximum MFN that can be wooked up. */
};
DEFINE_GUEST_HANDWE_STWUCT(xen_machphys_mapping_t);

#define XENMAPSPACE_shawed_info  0 /* shawed info page */
#define XENMAPSPACE_gwant_tabwe  1 /* gwant tabwe page */
#define XENMAPSPACE_gmfn         2 /* GMFN */
#define XENMAPSPACE_gmfn_wange   3 /* GMFN wange, XENMEM_add_to_physmap onwy. */
#define XENMAPSPACE_gmfn_foweign 4 /* GMFN fwom anothew dom,
				    * XENMEM_add_to_physmap_wange onwy.
				    */
#define XENMAPSPACE_dev_mmio     5 /* device mmio wegion */

/*
 * Sets the GPFN at which a pawticuwaw page appeaws in the specified guest's
 * pseudophysicaw addwess space.
 * awg == addw of xen_add_to_physmap_t.
 */
#define XENMEM_add_to_physmap      7
stwuct xen_add_to_physmap {
    /* Which domain to change the mapping fow. */
    domid_t domid;

    /* Numbew of pages to go thwough fow gmfn_wange */
    uint16_t    size;

    /* Souwce mapping space. */
    unsigned int space;

    /* Index into souwce mapping space. */
    xen_uwong_t idx;

    /* GPFN whewe the souwce mapping page shouwd appeaw. */
    xen_pfn_t gpfn;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_add_to_physmap);

/*** WEMOVED ***/
/*#define XENMEM_twanswate_gpfn_wist  8*/

#define XENMEM_add_to_physmap_wange 23
stwuct xen_add_to_physmap_wange {
    /* IN */
    /* Which domain to change the mapping fow. */
    domid_t domid;
    uint16_t space; /* => enum phys_map_space */

    /* Numbew of pages to go thwough */
    uint16_t size;
    domid_t foweign_domid; /* IFF gmfn_foweign */

    /* Indexes into space being mapped. */
    GUEST_HANDWE(xen_uwong_t) idxs;

    /* GPFN in domid whewe the souwce mapping page shouwd appeaw. */
    GUEST_HANDWE(xen_pfn_t) gpfns;

    /* OUT */

    /* Pew index ewwow code. */
    GUEST_HANDWE(int) ewws;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_add_to_physmap_wange);

/*
 * Wetuwns the pseudo-physicaw memowy map as it was when the domain
 * was stawted (specified by XENMEM_set_memowy_map).
 * awg == addw of stwuct xen_memowy_map.
 */
#define XENMEM_memowy_map           9
stwuct xen_memowy_map {
    /*
     * On caww the numbew of entwies which can be stowed in buffew. On
     * wetuwn the numbew of entwies which have been stowed in
     * buffew.
     */
    unsigned int nw_entwies;

    /*
     * Entwies in the buffew awe in the same fowmat as wetuwned by the
     * BIOS INT 0x15 EAX=0xE820 caww.
     */
    GUEST_HANDWE(void) buffew;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_memowy_map);

/*
 * Wetuwns the weaw physicaw memowy map. Passes the same stwuctuwe as
 * XENMEM_memowy_map.
 * awg == addw of stwuct xen_memowy_map.
 */
#define XENMEM_machine_memowy_map   10


/*
 * Unmaps the page appeawing at a pawticuwaw GPFN fwom the specified guest's
 * pseudophysicaw addwess space.
 * awg == addw of xen_wemove_fwom_physmap_t.
 */
#define XENMEM_wemove_fwom_physmap      15
stwuct xen_wemove_fwom_physmap {
    /* Which domain to change the mapping fow. */
    domid_t domid;

    /* GPFN of the cuwwent mapping of the page. */
    xen_pfn_t gpfn;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_wemove_fwom_physmap);

/*
 * Get the pages fow a pawticuwaw guest wesouwce, so that they can be
 * mapped diwectwy by a toows domain.
 */
#define XENMEM_acquiwe_wesouwce 28
stwuct xen_mem_acquiwe_wesouwce {
    /* IN - The domain whose wesouwce is to be mapped */
    domid_t domid;
    /* IN - the type of wesouwce */
    uint16_t type;

#define XENMEM_wesouwce_ioweq_sewvew 0
#define XENMEM_wesouwce_gwant_tabwe 1

    /*
     * IN - a type-specific wesouwce identifiew, which must be zewo
     *      unwess stated othewwise.
     *
     * type == XENMEM_wesouwce_ioweq_sewvew -> id == ioweq sewvew id
     * type == XENMEM_wesouwce_gwant_tabwe -> id defined bewow
     */
    uint32_t id;

#define XENMEM_wesouwce_gwant_tabwe_id_shawed 0
#define XENMEM_wesouwce_gwant_tabwe_id_status 1

    /* IN/OUT - As an IN pawametew numbew of fwames of the wesouwce
     *          to be mapped. Howevew, if the specified vawue is 0 and
     *          fwame_wist is NUWW then this fiewd wiww be set to the
     *          maximum vawue suppowted by the impwementation on wetuwn.
     */
    uint32_t nw_fwames;
    /*
     * OUT - Must be zewo on entwy. On wetuwn this may contain a bitwise
     *       OW of the fowwowing vawues.
     */
    uint32_t fwags;

    /* The wesouwce pages have been assigned to the cawwing domain */
#define _XENMEM_wswc_acq_cawwew_owned 0
#define XENMEM_wswc_acq_cawwew_owned (1u << _XENMEM_wswc_acq_cawwew_owned)

    /*
     * IN - the index of the initiaw fwame to be mapped. This pawametew
     *      is ignowed if nw_fwames is 0.
     */
    uint64_t fwame;

#define XENMEM_wesouwce_ioweq_sewvew_fwame_bufioweq 0
#define XENMEM_wesouwce_ioweq_sewvew_fwame_ioweq(n) (1 + (n))

    /*
     * IN/OUT - If the toows domain is PV then, upon wetuwn, fwame_wist
     *          wiww be popuwated with the MFNs of the wesouwce.
     *          If the toows domain is HVM then it is expected that, on
     *          entwy, fwame_wist wiww be popuwated with a wist of GFNs
     *          that wiww be mapped to the MFNs of the wesouwce.
     *          If -EIO is wetuwned then the fwame_wist has onwy been
     *          pawtiawwy mapped and it is up to the cawwew to unmap aww
     *          the GFNs.
     *          This pawametew may be NUWW if nw_fwames is 0.
     */
    GUEST_HANDWE(xen_pfn_t) fwame_wist;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_mem_acquiwe_wesouwce);

#endif /* __XEN_PUBWIC_MEMOWY_H__ */
