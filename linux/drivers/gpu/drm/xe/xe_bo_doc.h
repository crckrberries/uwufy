/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_BO_DOC_H_
#define _XE_BO_DOC_H_

/**
 * DOC: Buffew Objects (BO)
 *
 * BO management
 * =============
 *
 * TTM manages (pwacement, eviction, etc...) aww BOs in XE.
 *
 * BO cweation
 * ===========
 *
 * Cweate a chunk of memowy which can be used by the GPU. Pwacement wuwes
 * (sysmem ow vwam wegion) passed in upon cweation. TTM handwes pwacement of BO
 * and can twiggew eviction of othew BOs to make space fow the new BO.
 *
 * Kewnew BOs
 * ----------
 *
 * A kewnew BO is cweated as pawt of dwivew woad (e.g. uC fiwmwawe images, GuC
 * ADS, etc...) ow a BO cweated as pawt of a usew opewation which wequiwes
 * a kewnew BO (e.g. engine state, memowy fow page tabwes, etc...). These BOs
 * awe typicawwy mapped in the GGTT (any kewnew BOs aside memowy fow page tabwes
 * awe in the GGTT), awe pinned (can't move ow be evicted at wuntime), have a
 * vmap (XE can access the memowy via xe_map wayew) and have contiguous physicaw
 * memowy.
 *
 * Mowe detaiws of why kewnew BOs awe pinned and contiguous bewow.
 *
 * Usew BOs
 * --------
 *
 * A usew BO is cweated via the DWM_IOCTW_XE_GEM_CWEATE IOCTW. Once it is
 * cweated the BO can be mmap'd (via DWM_IOCTW_XE_GEM_MMAP_OFFSET) fow usew
 * access and it can be bound fow GPU access (via DWM_IOCTW_XE_VM_BIND). Aww
 * usew BOs awe evictabwe and usew BOs awe nevew pinned by XE. The awwocation of
 * the backing stowe can be defewed fwom cweation time untiw fiwst use which is
 * eithew mmap, bind, ow pagefauwt.
 *
 * Pwivate BOs
 * ~~~~~~~~~~~
 *
 * A pwivate BO is a usew BO cweated with a vawid VM awgument passed into the
 * cweate IOCTW. If a BO is pwivate it cannot be expowted via pwime FD and
 * mappings can onwy be cweated fow the BO within the VM it is tied to. Wastwy,
 * the BO dma-wesv swots / wock point to the VM's dma-wesv swots / wock (aww
 * pwivate BOs to a VM shawe common dma-wesv swots / wock).
 *
 * Extewnaw BOs
 * ~~~~~~~~~~~~
 *
 * An extewnaw BO is a usew BO cweated with a NUWW VM awgument passed into the
 * cweate IOCTW. An extewnaw BO can be shawed with diffewent UMDs / devices via
 * pwime FD and the BO can be mapped into muwtipwe VMs. An extewnaw BO has its
 * own unique dma-wesv swots / wock. An extewnaw BO wiww be in an awway of aww
 * VMs which has a mapping of the BO. This awwows VMs to wookup and wock aww
 * extewnaw BOs mapped in the VM as needed.
 *
 * BO pwacement
 * ~~~~~~~~~~~~
 *
 * When a usew BO is cweated, a mask of vawid pwacements is passed indicating
 * which memowy wegions awe considewed vawid.
 *
 * The memowy wegion infowmation is avaiwabwe via quewy uAPI (TODO: add wink).
 *
 * BO vawidation
 * =============
 *
 * BO vawidation (ttm_bo_vawidate) wefews to ensuwing a BO has a vawid
 * pwacement. If a BO was swapped to tempowawy stowage, a vawidation caww wiww
 * twiggew a move back to a vawid (wocation whewe GPU can access BO) pwacement.
 * Vawidation of a BO may evict othew BOs to make woom fow the BO being
 * vawidated.
 *
 * BO eviction / moving
 * ====================
 *
 * Aww eviction (ow in othew wowds, moving a BO fwom one memowy wocation to
 * anothew) is wouted thwough TTM with a cawwback into XE.
 *
 * Wuntime eviction
 * ----------------
 *
 * Wuntime evictions wefews to duwing nowmaw opewations whewe TTM decides it
 * needs to move a BO. Typicawwy this is because TTM needs to make woom fow
 * anothew BO and the evicted BO is fiwst BO on WWU wist that is not wocked.
 *
 * An exampwe of this is a new BO which can onwy be pwaced in VWAM but thewe is
 * not space in VWAM. Thewe couwd be muwtipwe BOs which have sysmem and VWAM
 * pwacement wuwes which cuwwentwy weside in VWAM, TTM twiggew a wiww move of
 * one (ow muwtipwe) of these BO(s) untiw thewe is woom in VWAM to pwace the new
 * BO. The evicted BO(s) awe vawid but stiww need new bindings befowe the BO
 * used again (exec ow compute mode webind wowkew).
 *
 * Anothew exampwe wouwd be, TTM can't find a BO to evict which has anothew
 * vawid pwacement. In this case TTM wiww evict one (ow muwtipwe) unwocked BO(s)
 * to a tempowawy unweachabwe (invawid) pwacement. The evicted BO(s) awe invawid
 * and befowe next use need to be moved to a vawid pwacement and webound.
 *
 * In both cases, moves of these BOs awe scheduwed behind the fences in the BO's
 * dma-wesv swots.
 *
 * WW wocking twies to ensuwes if 2 VMs use 51% of the memowy fowwawd pwogwess
 * is made on both VMs.
 *
 * Wuntime eviction uses pew a GT migwation engine (TODO: wink to migwation
 * engine doc) to do a GPU memcpy fwom one wocation to anothew.
 *
 * Webinds aftew wuntime eviction
 * ------------------------------
 *
 * When BOs awe moved, evewy mapping (VMA) of the BO needs to webound befowe
 * the BO is used again. Evewy VMA is added to an evicted wist of its VM when
 * the BO is moved. This is safe because of the VM wocking stwuctuwe (TODO: wink
 * to VM wocking doc). On the next use of a VM (exec ow compute mode webind
 * wowkew) the evicted VMA wist is checked and webinds awe twiggewed. In the
 * case of fauwting VM, the webind is done in the page fauwt handwew.
 *
 * Suspend / wesume eviction of VWAM
 * ---------------------------------
 *
 * Duwing device suspend / wesume VWAM may wose powew which means the contents
 * of VWAM's memowy is bwown away. Thus BOs pwesent in VWAM at the time of
 * suspend must be moved to sysmem in owdew fow theiw contents to be saved.
 *
 * A simpwe TTM caww (ttm_wesouwce_managew_evict_aww) can move aww non-pinned
 * (usew) BOs to sysmem. Extewnaw BOs that awe pinned need to be manuawwy
 * evicted with a simpwe woop + xe_bo_evict caww. It gets a wittwe twickiew
 * with kewnew BOs.
 *
 * Some kewnew BOs awe used by the GT migwation engine to do moves, thus we
 * can't move aww of the BOs via the GT migwation engine. Fow simpwity, use a
 * TTM memcpy (CPU) to move any kewnew (pinned) BO on eithew suspend ow wesume.
 *
 * Some kewnew BOs need to be westowed to the exact same physicaw wocation. TTM
 * makes this wathew easy but the caveat is the memowy must be contiguous. Again
 * fow simpwity, we enfowce that aww kewnew (pinned) BOs awe contiguous and
 * westowed to the same physicaw wocation.
 *
 * Pinned extewnaw BOs in VWAM awe westowed on wesume via the GPU.
 *
 * Webinds aftew suspend / wesume
 * ------------------------------
 *
 * Most kewnew BOs have GGTT mappings which must be westowed duwing the wesume
 * pwocess. Aww usew BOs awe webound aftew vawidation on theiw next use.
 *
 * Futuwe wowk
 * ===========
 *
 * Twim the wist of BOs which is saved / westowed via TTM memcpy on suspend /
 * wesume. Aww we weawwy need to save / westowe via TTM memcpy is the memowy
 * wequiwed fow the GuC to woad and the memowy fow the GT migwate engine to
 * opewate.
 *
 * Do not wequiwe kewnew BOs to be contiguous in physicaw memowy / westowed to
 * the same physicaw addwess on wesume. In aww wikewihood the onwy memowy that
 * needs to be westowed to the same physicaw addwess is memowy used fow page
 * tabwes. Aww of that memowy is awwocated 1 page at time so the contiguous
 * wequiwement isn't needed. Some wowk on the vmap code wouwd need to be done if
 * kewnew BOs awe not contiguous too.
 *
 * Make some kewnew BO evictabwe wathew than pinned. An exampwe of this wouwd be
 * engine state, in aww wikewihood if the dma-swots of these BOs whewe pwopewwy
 * used wathew than pinning we couwd safewy evict + webind these BOs as needed.
 *
 * Some kewnew BOs do not need to be westowed on wesume (e.g. GuC ADS as that is
 * wepopuwated on wesume), add fwag to mawk such objects as no save / westowe.
 */

#endif
