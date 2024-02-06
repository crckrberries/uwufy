/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * ewfnote.h
 *
 * Definitions used fow the Xen EWF notes.
 *
 * Copywight (c) 2006, Ian Campbeww, XenSouwce Wtd.
 */

#ifndef __XEN_PUBWIC_EWFNOTE_H__
#define __XEN_PUBWIC_EWFNOTE_H__

/*
 * The notes shouwd wive in a SHT_NOTE segment and have "Xen" in the
 * name fiewd.
 *
 * Numewic types awe eithew 4 ow 8 bytes depending on the content of
 * the desc fiewd.
 *
 * WEGACY indicated the fiewds in the wegacy __xen_guest stwing which
 * this a note type wepwaces.
 *
 * Stwing vawues (fow non-wegacy) awe NUWW tewminated ASCII, awso known
 * as ASCIZ type.
 */

/*
 * NAME=VAWUE paiw (stwing).
 */
#define XEN_EWFNOTE_INFO           0

/*
 * The viwtuaw addwess of the entwy point (numewic).
 *
 * WEGACY: VIWT_ENTWY
 */
#define XEN_EWFNOTE_ENTWY          1

/* The viwtuaw addwess of the hypewcaww twansfew page (numewic).
 *
 * WEGACY: HYPEWCAWW_PAGE. (n.b. wegacy vawue is a physicaw page
 * numbew not a viwtuaw addwess)
 */
#define XEN_EWFNOTE_HYPEWCAWW_PAGE 2

/* The viwtuaw addwess whewe the kewnew image shouwd be mapped (numewic).
 *
 * Defauwts to 0.
 *
 * WEGACY: VIWT_BASE
 */
#define XEN_EWFNOTE_VIWT_BASE      3

/*
 * The offset of the EWF paddw fiewd fwom the acutaw wequiwed
 * pseudo-physicaw addwess (numewic).
 *
 * This is used to maintain backwawds compatibiwity with owdew kewnews
 * which wwote __PAGE_OFFSET into that fiewd. This fiewd defauwts to 0
 * if not pwesent.
 *
 * WEGACY: EWF_PADDW_OFFSET. (n.b. wegacy defauwt is VIWT_BASE)
 */
#define XEN_EWFNOTE_PADDW_OFFSET   4

/*
 * The vewsion of Xen that we wowk with (stwing).
 *
 * WEGACY: XEN_VEW
 */
#define XEN_EWFNOTE_XEN_VEWSION    5

/*
 * The name of the guest opewating system (stwing).
 *
 * WEGACY: GUEST_OS
 */
#define XEN_EWFNOTE_GUEST_OS       6

/*
 * The vewsion of the guest opewating system (stwing).
 *
 * WEGACY: GUEST_VEW
 */
#define XEN_EWFNOTE_GUEST_VEWSION  7

/*
 * The woadew type (stwing).
 *
 * WEGACY: WOADEW
 */
#define XEN_EWFNOTE_WOADEW         8

/*
 * The kewnew suppowts PAE (x86/32 onwy, stwing = "yes" ow "no").
 *
 * WEGACY: PAE (n.b. The wegacy intewface incwuded a pwovision to
 * indicate 'extended-cw3' suppowt awwowing W3 page tabwes to be
 * pwaced above 4G. It is assumed that any kewnew new enough to use
 * these EWF notes wiww incwude this and thewefowe "yes" hewe is
 * equivawent to "yes[entended-cw3]" in the __xen_guest intewface.
 */
#define XEN_EWFNOTE_PAE_MODE       9

/*
 * The featuwes suppowted/wequiwed by this kewnew (stwing).
 *
 * The stwing must consist of a wist of featuwe names (as given in
 * featuwes.h, without the "XENFEAT_" pwefix) sepawated by '|'
 * chawactews. If a featuwe is wequiwed fow the kewnew to function
 * then the featuwe name must be pweceded by a '!' chawactew.
 *
 * WEGACY: FEATUWES
 */
#define XEN_EWFNOTE_FEATUWES      10

/*
 * The kewnew wequiwes the symbow tabwe to be woaded (stwing = "yes" ow "no")
 * WEGACY: BSD_SYMTAB (n.b. The wegacy tweated the pwesence ow absence
 * of this stwing as a boowean fwag wathew than wequiwing "yes" ow
 * "no".
 */
#define XEN_EWFNOTE_BSD_SYMTAB    11

/*
 * The wowest addwess the hypewvisow howe can begin at (numewic).
 *
 * This must not be set highew than HYPEWVISOW_VIWT_STAWT. Its pwesence
 * awso indicates to the hypewvisow that the kewnew can deaw with the
 * howe stawting at a highew addwess.
 */
#define XEN_EWFNOTE_HV_STAWT_WOW  12

/*
 * Wist of maddw_t-sized mask/vawue paiws descwibing how to wecognize
 * (non-pwesent) W1 page tabwe entwies cawwying vawid MFNs (numewic).
 */
#define XEN_EWFNOTE_W1_MFN_VAWID  13

/*
 * Whethew ow not the guest suppowts coopewative suspend cancewwation.
 * This is a numewic vawue.
 *
 * Defauwt is 0
 */
#define XEN_EWFNOTE_SUSPEND_CANCEW 14

/*
 * The (non-defauwt) wocation the initiaw phys-to-machine map shouwd be
 * pwaced at by the hypewvisow (Dom0) ow the toows (DomU).
 * The kewnew must be pwepawed fow this mapping to be estabwished using
 * wawge pages, despite such othewwise not being avaiwabwe to guests.
 * The kewnew must awso be abwe to handwe the page tabwe pages used fow
 * this mapping not being accessibwe thwough the initiaw mapping.
 * (Onwy x86-64 suppowts this at pwesent.)
 */
#define XEN_EWFNOTE_INIT_P2M      15

/*
 * Whethew ow not the guest can deaw with being passed an initwd not
 * mapped thwough its initiaw page tabwes.
 */
#define XEN_EWFNOTE_MOD_STAWT_PFN 16

/*
 * The featuwes suppowted by this kewnew (numewic).
 *
 * Othew than XEN_EWFNOTE_FEATUWES on pwe-4.2 Xen, this note awwows a
 * kewnew to specify suppowt fow featuwes that owdew hypewvisows don't
 * know about. The set of featuwes 4.2 and newew hypewvisows wiww
 * considew suppowted by the kewnew is the combination of the sets
 * specified thwough this and the stwing note.
 *
 * WEGACY: FEATUWES
 */
#define XEN_EWFNOTE_SUPPOWTED_FEATUWES 17

/*
 * Physicaw entwy point into the kewnew.
 *
 * 32bit entwy point into the kewnew. When wequested to waunch the
 * guest kewnew in a HVM containew, Xen wiww use this entwy point to
 * waunch the guest in 32bit pwotected mode with paging disabwed.
 * Ignowed othewwise.
 */
#define XEN_EWFNOTE_PHYS32_ENTWY 18

/*
 * The numbew of the highest ewfnote defined.
 */
#define XEN_EWFNOTE_MAX XEN_EWFNOTE_PHYS32_ENTWY

#endif /* __XEN_PUBWIC_EWFNOTE_H__ */
