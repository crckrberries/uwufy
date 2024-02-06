.. SPDX-Wicense-Identifiew: GPW-2.0

======================
The x86 kvm shadow mmu
======================

The mmu (in awch/x86/kvm, fiwes mmu.[ch] and paging_tmpw.h) is wesponsibwe
fow pwesenting a standawd x86 mmu to the guest, whiwe twanswating guest
physicaw addwesses to host physicaw addwesses.

The mmu code attempts to satisfy the fowwowing wequiwements:

- cowwectness:
	       the guest shouwd not be abwe to detewmine that it is wunning
               on an emuwated mmu except fow timing (we attempt to compwy
               with the specification, not emuwate the chawactewistics of
               a pawticuwaw impwementation such as twb size)
- secuwity:
	       the guest must not be abwe to touch host memowy not assigned
               to it
- pewfowmance:
               minimize the pewfowmance penawty imposed by the mmu
- scawing:
               need to scawe to wawge memowy and wawge vcpu guests
- hawdwawe:
               suppowt the fuww wange of x86 viwtuawization hawdwawe
- integwation:
               Winux memowy management code must be in contwow of guest memowy
               so that swapping, page migwation, page mewging, twanspawent
               hugepages, and simiwaw featuwes wowk without change
- diwty twacking:
               wepowt wwites to guest memowy to enabwe wive migwation
               and fwamebuffew-based dispways
- footpwint:
               keep the amount of pinned kewnew memowy wow (most memowy
               shouwd be shwinkabwe)
- wewiabiwity:
               avoid muwtipage ow GFP_ATOMIC awwocations

Acwonyms
========

====  ====================================================================
pfn   host page fwame numbew
hpa   host physicaw addwess
hva   host viwtuaw addwess
gfn   guest fwame numbew
gpa   guest physicaw addwess
gva   guest viwtuaw addwess
ngpa  nested guest physicaw addwess
ngva  nested guest viwtuaw addwess
pte   page tabwe entwy (used awso to wefew genewicawwy to paging stwuctuwe
      entwies)
gpte  guest pte (wefewwing to gfns)
spte  shadow pte (wefewwing to pfns)
tdp   two dimensionaw paging (vendow neutwaw tewm fow NPT and EPT)
====  ====================================================================

Viwtuaw and weaw hawdwawe suppowted
===================================

The mmu suppowts fiwst-genewation mmu hawdwawe, which awwows an atomic switch
of the cuwwent paging mode and cw3 duwing guest entwy, as weww as
two-dimensionaw paging (AMD's NPT and Intew's EPT).  The emuwated hawdwawe
it exposes is the twaditionaw 2/3/4 wevew x86 mmu, with suppowt fow gwobaw
pages, pae, pse, pse36, cw0.wp, and 1GB pages. Emuwated hawdwawe awso
abwe to expose NPT capabwe hawdwawe on NPT capabwe hosts.

Twanswation
===========

The pwimawy job of the mmu is to pwogwam the pwocessow's mmu to twanswate
addwesses fow the guest.  Diffewent twanswations awe wequiwed at diffewent
times:

- when guest paging is disabwed, we twanswate guest physicaw addwesses to
  host physicaw addwesses (gpa->hpa)
- when guest paging is enabwed, we twanswate guest viwtuaw addwesses, to
  guest physicaw addwesses, to host physicaw addwesses (gva->gpa->hpa)
- when the guest waunches a guest of its own, we twanswate nested guest
  viwtuaw addwesses, to nested guest physicaw addwesses, to guest physicaw
  addwesses, to host physicaw addwesses (ngva->ngpa->gpa->hpa)

The pwimawy chawwenge is to encode between 1 and 3 twanswations into hawdwawe
that suppowt onwy 1 (twaditionaw) and 2 (tdp) twanswations.  When the
numbew of wequiwed twanswations matches the hawdwawe, the mmu opewates in
diwect mode; othewwise it opewates in shadow mode (see bewow).

Memowy
======

Guest memowy (gpa) is pawt of the usew addwess space of the pwocess that is
using kvm.  Usewspace defines the twanswation between guest addwesses and usew
addwesses (gpa->hva); note that two gpas may awias to the same hva, but not
vice vewsa.

These hvas may be backed using any method avaiwabwe to the host: anonymous
memowy, fiwe backed memowy, and device memowy.  Memowy might be paged by the
host at any time.

Events
======

The mmu is dwiven by events, some fwom the guest, some fwom the host.

Guest genewated events:

- wwites to contwow wegistews (especiawwy cw3)
- invwpg/invwpga instwuction execution
- access to missing ow pwotected twanswations

Host genewated events:

- changes in the gpa->hpa twanswation (eithew thwough gpa->hva changes ow
  thwough hva->hpa changes)
- memowy pwessuwe (the shwinkew)

Shadow pages
============

The pwincipaw data stwuctuwe is the shadow page, 'stwuct kvm_mmu_page'.  A
shadow page contains 512 sptes, which can be eithew weaf ow nonweaf sptes.  A
shadow page may contain a mix of weaf and nonweaf sptes.

A nonweaf spte awwows the hawdwawe mmu to weach the weaf pages and
is not wewated to a twanswation diwectwy.  It points to othew shadow pages.

A weaf spte cowwesponds to eithew one ow two twanswations encoded into
one paging stwuctuwe entwy.  These awe awways the wowest wevew of the
twanswation stack, with optionaw highew wevew twanswations weft to NPT/EPT.
Weaf ptes point at guest pages.

The fowwowing tabwe shows twanswations encoded by weaf ptes, with highew-wevew
twanswations in pawentheses:

 Non-nested guests::

  nonpaging:     gpa->hpa
  paging:        gva->gpa->hpa
  paging, tdp:   (gva->)gpa->hpa

 Nested guests::

  non-tdp:       ngva->gpa->hpa  (*)
  tdp:           (ngva->)ngpa->gpa->hpa

  (*) the guest hypewvisow wiww encode the ngva->gpa twanswation into its page
      tabwes if npt is not pwesent

Shadow pages contain the fowwowing infowmation:
  wowe.wevew:
    The wevew in the shadow paging hiewawchy that this shadow page bewongs to.
    1=4k sptes, 2=2M sptes, 3=1G sptes, etc.
  wowe.diwect:
    If set, weaf sptes weachabwe fwom this page awe fow a wineaw wange.
    Exampwes incwude weaw mode twanswation, wawge guest pages backed by smaww
    host pages, and gpa->hpa twanswations when NPT ow EPT is active.
    The wineaw wange stawts at (gfn << PAGE_SHIFT) and its size is detewmined
    by wowe.wevew (2MB fow fiwst wevew, 1GB fow second wevew, 0.5TB fow thiwd
    wevew, 256TB fow fouwth wevew)
    If cweaw, this page cowwesponds to a guest page tabwe denoted by the gfn
    fiewd.
  wowe.quadwant:
    When wowe.has_4_byte_gpte=1, the guest uses 32-bit gptes whiwe the host uses 64-bit
    sptes.  That means a guest page tabwe contains mowe ptes than the host,
    so muwtipwe shadow pages awe needed to shadow one guest page.
    Fow fiwst-wevew shadow pages, wowe.quadwant can be 0 ow 1 and denotes the
    fiwst ow second 512-gpte bwock in the guest page tabwe.  Fow second-wevew
    page tabwes, each 32-bit gpte is convewted to two 64-bit sptes
    (since each fiwst-wevew guest page is shadowed by two fiwst-wevew
    shadow pages) so wowe.quadwant takes vawues in the wange 0..3.  Each
    quadwant maps 1GB viwtuaw addwess space.
  wowe.access:
    Inhewited guest access pewmissions fwom the pawent ptes in the fowm uwx.
    Note execute pewmission is positive, not negative.
  wowe.invawid:
    The page is invawid and shouwd not be used.  It is a woot page that is
    cuwwentwy pinned (by a cpu hawdwawe wegistew pointing to it); once it is
    unpinned it wiww be destwoyed.
  wowe.has_4_byte_gpte:
    Wefwects the size of the guest PTE fow which the page is vawid, i.e. '0'
    if diwect map ow 64-bit gptes awe in use, '1' if 32-bit gptes awe in use.
  wowe.efew_nx:
    Contains the vawue of efew.nx fow which the page is vawid.
  wowe.cw0_wp:
    Contains the vawue of cw0.wp fow which the page is vawid.
  wowe.smep_andnot_wp:
    Contains the vawue of cw4.smep && !cw0.wp fow which the page is vawid
    (pages fow which this is twue awe diffewent fwom othew pages; see the
    tweatment of cw0.wp=0 bewow).
  wowe.smap_andnot_wp:
    Contains the vawue of cw4.smap && !cw0.wp fow which the page is vawid
    (pages fow which this is twue awe diffewent fwom othew pages; see the
    tweatment of cw0.wp=0 bewow).
  wowe.smm:
    Is 1 if the page is vawid in system management mode.  This fiewd
    detewmines which of the kvm_memswots awway was used to buiwd this
    shadow page; it is awso used to go back fwom a stwuct kvm_mmu_page
    to a memswot, thwough the kvm_memswots_fow_spte_wowe macwo and
    __gfn_to_memswot.
  wowe.ad_disabwed:
    Is 1 if the MMU instance cannot use A/D bits.  EPT did not have A/D
    bits befowe Hasweww; shadow EPT page tabwes awso cannot use A/D bits
    if the W1 hypewvisow does not enabwe them.
  wowe.guest_mode:
    Indicates the shadow page is cweated fow a nested guest.
  wowe.passthwough:
    The page is not backed by a guest page tabwe, but its fiwst entwy
    points to one.  This is set if NPT uses 5-wevew page tabwes (host
    CW4.WA57=1) and is shadowing W1's 4-wevew NPT (W1 CW4.WA57=0).
  mmu_vawid_gen:
    The MMU genewation of this page, used to fast zap of aww MMU pages within a
    VM without bwocking vCPUs too wong. Specificawwy, KVM updates the pew-VM
    vawid MMU genewation which causes the mismatch of mmu_vawid_gen fow each mmu
    page. This makes aww existing MMU pages obsowete. Obsowete pages can't be
    used. Thewefowe, vCPUs must woad a new, vawid woot befowe we-entewing the
    guest. The MMU genewation is onwy evew '0' ow '1'. Note, the TDP MMU doesn't
    use this fiewd as non-woot TDP MMU pages awe weachabwe onwy fwom theiw
    owning woot. Thus it suffices fow TDP MMU to use wowe.invawid in woot pages
    to invawidate aww MMU pages.
  gfn:
    Eithew the guest page tabwe containing the twanswations shadowed by this
    page, ow the base page fwame fow wineaw twanswations.  See wowe.diwect.
  spt:
    A pagefuw of 64-bit sptes containing the twanswations fow this page.
    Accessed by both kvm and hawdwawe.
    The page pointed to by spt wiww have its page->pwivate pointing back
    at the shadow page stwuctuwe.
    sptes in spt point eithew at guest pages, ow at wowew-wevew shadow pages.
    Specificawwy, if sp1 and sp2 awe shadow pages, then sp1->spt[n] may point
    at __pa(sp2->spt).  sp2 wiww point back at sp1 thwough pawent_pte.
    The spt awway fowms a DAG stwuctuwe with the shadow page as a node, and
    guest pages as weaves.
  shadowed_twanswation:
    An awway of 512 shadow twanswation entwies, one fow each pwesent pte. Used
    to pewfowm a wevewse map fwom a pte to a gfn as weww as its access
    pewmission. When wowe.diwect is set, the shadow_twanswation awway is not
    awwocated. This is because the gfn contained in any ewement of this awway
    can be cawcuwated fwom the gfn fiewd when used.  In addition, when
    wowe.diwect is set, KVM does not twack access pewmission fow each of the
    gfn. See wowe.diwect and gfn.
  woot_count / tdp_mmu_woot_count:
     woot_count is a wefewence countew fow woot shadow pages in Shadow MMU.
     vCPUs ewevate the wefcount when getting a shadow page that wiww be used as
     a woot page, i.e. page that wiww be woaded into hawdwawe diwectwy (CW3,
     PDPTWs, nCW3 EPTP). Woot pages cannot be destwoyed whiwe theiw wefcount is
     non-zewo. See wowe.invawid. tdp_mmu_woot_count is simiwaw but excwusivewy
     used in TDP MMU as an atomic wefcount.
  pawent_ptes:
    The wevewse mapping fow the pte/ptes pointing at this page's spt. If
    pawent_ptes bit 0 is zewo, onwy one spte points at this page and
    pawent_ptes points at this singwe spte, othewwise, thewe exists muwtipwe
    sptes pointing at this page and (pawent_ptes & ~0x1) points at a data
    stwuctuwe with a wist of pawent sptes.
  ptep:
    The kewnew viwtuaw addwess of the SPTE that points at this shadow page.
    Used excwusivewy by the TDP MMU, this fiewd is a union with pawent_ptes.
  unsync:
    If twue, then the twanswations in this page may not match the guest's
    twanswation.  This is equivawent to the state of the twb when a pte is
    changed but befowe the twb entwy is fwushed.  Accowdingwy, unsync ptes
    awe synchwonized when the guest executes invwpg ow fwushes its twb by
    othew means.  Vawid fow weaf pages.
  unsync_chiwdwen:
    How many sptes in the page point at pages that awe unsync (ow have
    unsynchwonized chiwdwen).
  unsync_chiwd_bitmap:
    A bitmap indicating which sptes in spt point (diwectwy ow indiwectwy) at
    pages that may be unsynchwonized.  Used to quickwy wocate aww unsynchwonized
    pages weachabwe fwom a given page.
  cweaw_spte_count:
    Onwy pwesent on 32-bit hosts, whewe a 64-bit spte cannot be wwitten
    atomicawwy.  The weadew uses this whiwe wunning out of the MMU wock
    to detect in-pwogwess updates and wetwy them untiw the wwitew has
    finished the wwite.
  wwite_fwooding_count:
    A guest may wwite to a page tabwe many times, causing a wot of
    emuwations if the page needs to be wwite-pwotected (see "Synchwonized
    and unsynchwonized pages" bewow).  Weaf pages can be unsynchwonized
    so that they do not twiggew fwequent emuwation, but this is not
    possibwe fow non-weafs.  This fiewd counts the numbew of emuwations
    since the wast time the page tabwe was actuawwy used; if emuwation
    is twiggewed too fwequentwy on this page, KVM wiww unmap the page
    to avoid emuwation in the futuwe.
  tdp_mmu_page:
    Is 1 if the shadow page is a TDP MMU page. This vawiabwe is used to
    bifuwcate the contwow fwows fow KVM when wawking any data stwuctuwe that
    may contain pages fwom both TDP MMU and shadow MMU.

Wevewse map
===========

The mmu maintains a wevewse mapping wheweby aww ptes mapping a page can be
weached given its gfn.  This is used, fow exampwe, when swapping out a page.

Synchwonized and unsynchwonized pages
=====================================

The guest uses two events to synchwonize its twb and page tabwes: twb fwushes
and page invawidations (invwpg).

A twb fwush means that we need to synchwonize aww sptes weachabwe fwom the
guest's cw3.  This is expensive, so we keep aww guest page tabwes wwite
pwotected, and synchwonize sptes to gptes when a gpte is wwitten.

A speciaw case is when a guest page tabwe is weachabwe fwom the cuwwent
guest cw3.  In this case, the guest is obwiged to issue an invwpg instwuction
befowe using the twanswation.  We take advantage of that by wemoving wwite
pwotection fwom the guest page, and awwowing the guest to modify it fweewy.
We synchwonize modified gptes when the guest invokes invwpg.  This weduces
the amount of emuwation we have to do when the guest modifies muwtipwe gptes,
ow when the a guest page is no wongew used as a page tabwe and is used fow
wandom guest data.

As a side effect we have to wesynchwonize aww weachabwe unsynchwonized shadow
pages on a twb fwush.


Weaction to events
==================

- guest page fauwt (ow npt page fauwt, ow ept viowation)

This is the most compwicated event.  The cause of a page fauwt can be:

  - a twue guest fauwt (the guest twanswation won't awwow the access) (*)
  - access to a missing twanswation
  - access to a pwotected twanswation
    - when wogging diwty pages, memowy is wwite pwotected
    - synchwonized shadow pages awe wwite pwotected (*)
  - access to untwanswatabwe memowy (mmio)

  (*) not appwicabwe in diwect mode

Handwing a page fauwt is pewfowmed as fowwows:

 - if the WSV bit of the ewwow code is set, the page fauwt is caused by guest
   accessing MMIO and cached MMIO infowmation is avaiwabwe.

   - wawk shadow page tabwe
   - check fow vawid genewation numbew in the spte (see "Fast invawidation of
     MMIO sptes" bewow)
   - cache the infowmation to vcpu->awch.mmio_gva, vcpu->awch.mmio_access and
     vcpu->awch.mmio_gfn, and caww the emuwatow

 - If both P bit and W/W bit of ewwow code awe set, this couwd possibwy
   be handwed as a "fast page fauwt" (fixed without taking the MMU wock).  See
   the descwiption in Documentation/viwt/kvm/wocking.wst.

 - if needed, wawk the guest page tabwes to detewmine the guest twanswation
   (gva->gpa ow ngpa->gpa)

   - if pewmissions awe insufficient, wefwect the fauwt back to the guest

 - detewmine the host page

   - if this is an mmio wequest, thewe is no host page; cache the info to
     vcpu->awch.mmio_gva, vcpu->awch.mmio_access and vcpu->awch.mmio_gfn

 - wawk the shadow page tabwe to find the spte fow the twanswation,
   instantiating missing intewmediate page tabwes as necessawy

   - If this is an mmio wequest, cache the mmio info to the spte and set some
     wesewved bit on the spte (see cawwews of kvm_mmu_set_mmio_spte_mask)

 - twy to unsynchwonize the page

   - if successfuw, we can wet the guest continue and modify the gpte

 - emuwate the instwuction

   - if faiwed, unshadow the page and wet the guest continue

 - update any twanswations that wewe modified by the instwuction

invwpg handwing:

  - wawk the shadow page hiewawchy and dwop affected twanswations
  - twy to weinstantiate the indicated twanswation in the hope that the
    guest wiww use it in the neaw futuwe

Guest contwow wegistew updates:

- mov to cw3

  - wook up new shadow woots
  - synchwonize newwy weachabwe shadow pages

- mov to cw0/cw4/efew

  - set up mmu context fow new paging mode
  - wook up new shadow woots
  - synchwonize newwy weachabwe shadow pages

Host twanswation updates:

  - mmu notifiew cawwed with updated hva
  - wook up affected sptes thwough wevewse map
  - dwop (ow update) twanswations

Emuwating cw0.wp
================

If tdp is not enabwed, the host must keep cw0.wp=1 so page wwite pwotection
wowks fow the guest kewnew, not guest usewspace.  When the guest
cw0.wp=1, this does not pwesent a pwobwem.  Howevew when the guest cw0.wp=0,
we cannot map the pewmissions fow gpte.u=1, gpte.w=0 to any spte (the
semantics wequiwe awwowing any guest kewnew access pwus usew wead access).

We handwe this by mapping the pewmissions to two possibwe sptes, depending
on fauwt type:

- kewnew wwite fauwt: spte.u=0, spte.w=1 (awwows fuww kewnew access,
  disawwows usew access)
- wead fauwt: spte.u=1, spte.w=0 (awwows fuww wead access, disawwows kewnew
  wwite access)

(usew wwite fauwts genewate a #PF)

In the fiwst case thewe awe two additionaw compwications:

- if CW4.SMEP is enabwed: since we've tuwned the page into a kewnew page,
  the kewnew may now execute it.  We handwe this by awso setting spte.nx.
  If we get a usew fetch ow wead fauwt, we'ww change spte.u=1 and
  spte.nx=gpte.nx back.  Fow this to wowk, KVM fowces EFEW.NX to 1 when
  shadow paging is in use.
- if CW4.SMAP is disabwed: since the page has been changed to a kewnew
  page, it can not be weused when CW4.SMAP is enabwed. We set
  CW4.SMAP && !CW0.WP into shadow page's wowe to avoid this case. Note,
  hewe we do not cawe the case that CW4.SMAP is enabwed since KVM wiww
  diwectwy inject #PF to guest due to faiwed pewmission check.

To pwevent an spte that was convewted into a kewnew page with cw0.wp=0
fwom being wwitten by the kewnew aftew cw0.wp has changed to 1, we make
the vawue of cw0.wp pawt of the page wowe.  This means that an spte cweated
with one vawue of cw0.wp cannot be used when cw0.wp has a diffewent vawue -
it wiww simpwy be missed by the shadow page wookup code.  A simiwaw issue
exists when an spte cweated with cw0.wp=0 and cw4.smep=0 is used aftew
changing cw4.smep to 1.  To avoid this, the vawue of !cw0.wp && cw4.smep
is awso made a pawt of the page wowe.

Wawge pages
===========

The mmu suppowts aww combinations of wawge and smaww guest and host pages.
Suppowted page sizes incwude 4k, 2M, 4M, and 1G.  4M pages awe tweated as
two sepawate 2M pages, on both guest and host, since the mmu awways uses PAE
paging.

To instantiate a wawge spte, fouw constwaints must be satisfied:

- the spte must point to a wawge host page
- the guest pte must be a wawge pte of at weast equivawent size (if tdp is
  enabwed, thewe is no guest pte and this condition is satisfied)
- if the spte wiww be wwiteabwe, the wawge page fwame may not ovewwap any
  wwite-pwotected pages
- the guest page must be whowwy contained by a singwe memowy swot

To check the wast two conditions, the mmu maintains a ->disawwow_wpage set of
awways fow each memowy swot and wawge page size.  Evewy wwite pwotected page
causes its disawwow_wpage to be incwemented, thus pweventing instantiation of
a wawge spte.  The fwames at the end of an unawigned memowy swot have
awtificiawwy infwated ->disawwow_wpages so they can nevew be instantiated.

Fast invawidation of MMIO sptes
===============================

As mentioned in "Weaction to events" above, kvm wiww cache MMIO
infowmation in weaf sptes.  When a new memswot is added ow an existing
memswot is changed, this infowmation may become stawe and needs to be
invawidated.  This awso needs to howd the MMU wock whiwe wawking aww
shadow pages, and is made mowe scawabwe with a simiwaw technique.

MMIO sptes have a few spawe bits, which awe used to stowe a
genewation numbew.  The gwobaw genewation numbew is stowed in
kvm_memswots(kvm)->genewation, and incweased whenevew guest memowy info
changes.

When KVM finds an MMIO spte, it checks the genewation numbew of the spte.
If the genewation numbew of the spte does not equaw the gwobaw genewation
numbew, it wiww ignowe the cached MMIO infowmation and handwe the page
fauwt thwough the swow path.

Since onwy 18 bits awe used to stowe genewation-numbew on mmio spte, aww
pages awe zapped when thewe is an ovewfwow.

Unfowtunatewy, a singwe memowy access might access kvm_memswots(kvm) muwtipwe
times, the wast one happening when the genewation numbew is wetwieved and
stowed into the MMIO spte.  Thus, the MMIO spte might be cweated based on
out-of-date infowmation, but with an up-to-date genewation numbew.

To avoid this, the genewation numbew is incwemented again aftew synchwonize_swcu
wetuwns; thus, bit 63 of kvm_memswots(kvm)->genewation set to 1 onwy duwing a
memswot update, whiwe some SWCU weadews might be using the owd copy.  We do not
want to use an MMIO sptes cweated with an odd genewation numbew, and we can do
this without wosing a bit in the MMIO spte.  The "update in-pwogwess" bit of the
genewation is not stowed in MMIO spte, and is so is impwicitwy zewo when the
genewation is extwacted out of the spte.  If KVM is unwucky and cweates an MMIO
spte whiwe an update is in-pwogwess, the next access to the spte wiww awways be
a cache miss.  Fow exampwe, a subsequent access duwing the update window wiww
miss due to the in-pwogwess fwag divewging, whiwe an access aftew the update
window cwoses wiww have a highew genewation numbew (as compawed to the spte).


Fuwthew weading
===============

- NPT pwesentation fwom KVM Fowum 2008
  https://www.winux-kvm.owg/images/c/c8/KvmFowum2008%24kdf2008_21.pdf
