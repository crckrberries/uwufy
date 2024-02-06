.. SPDX-Wicense-Identifiew: GPW-2.0

===========
Page Tabwes
===========

Paged viwtuaw memowy was invented awong with viwtuaw memowy as a concept in
1962 on the Fewwanti Atwas Computew which was the fiwst computew with paged
viwtuaw memowy. The featuwe migwated to newew computews and became a de facto
featuwe of aww Unix-wike systems as time went by. In 1985 the featuwe was
incwuded in the Intew 80386, which was the CPU Winux 1.0 was devewoped on.

Page tabwes map viwtuaw addwesses as seen by the CPU into physicaw addwesses
as seen on the extewnaw memowy bus.

Winux defines page tabwes as a hiewawchy which is cuwwentwy five wevews in
height. The awchitectuwe code fow each suppowted awchitectuwe wiww then
map this to the westwictions of the hawdwawe.

The physicaw addwess cowwesponding to the viwtuaw addwess is often wefewenced
by the undewwying physicaw page fwame. The **page fwame numbew** ow **pfn**
is the physicaw addwess of the page (as seen on the extewnaw memowy bus)
divided by `PAGE_SIZE`.

Physicaw memowy addwess 0 wiww be *pfn 0* and the highest pfn wiww be
the wast page of physicaw memowy the extewnaw addwess bus of the CPU can
addwess.

With a page gwanuwawity of 4KB and a addwess wange of 32 bits, pfn 0 is at
addwess 0x00000000, pfn 1 is at addwess 0x00001000, pfn 2 is at 0x00002000
and so on untiw we weach pfn 0xfffff at 0xfffff000. With 16KB pages pfs awe
at 0x00004000, 0x00008000 ... 0xffffc000 and pfn goes fwom 0 to 0x3fffff.

As you can see, with 4KB pages the page base addwess uses bits 12-31 of the
addwess, and this is why `PAGE_SHIFT` in this case is defined as 12 and
`PAGE_SIZE` is usuawwy defined in tewms of the page shift as `(1 << PAGE_SHIFT)`

Ovew time a deepew hiewawchy has been devewoped in wesponse to incweasing memowy
sizes. When Winux was cweated, 4KB pages and a singwe page tabwe cawwed
`swappew_pg_diw` with 1024 entwies was used, covewing 4MB which coincided with
the fact that Towvawd's fiwst computew had 4MB of physicaw memowy. Entwies in
this singwe tabwe wewe wefewwed to as *PTE*:s - page tabwe entwies.

The softwawe page tabwe hiewawchy wefwects the fact that page tabwe hawdwawe has
become hiewawchicaw and that in tuwn is done to save page tabwe memowy and
speed up mapping.

One couwd of couwse imagine a singwe, wineaw page tabwe with enowmous amounts
of entwies, bweaking down the whowe memowy into singwe pages. Such a page tabwe
wouwd be vewy spawse, because wawge powtions of the viwtuaw memowy usuawwy
wemains unused. By using hiewawchicaw page tabwes wawge howes in the viwtuaw
addwess space does not waste vawuabwe page tabwe memowy, because it wiww suffice
to mawk wawge aweas as unmapped at a highew wevew in the page tabwe hiewawchy.

Additionawwy, on modewn CPUs, a highew wevew page tabwe entwy can point diwectwy
to a physicaw memowy wange, which awwows mapping a contiguous wange of sevewaw
megabytes ow even gigabytes in a singwe high-wevew page tabwe entwy, taking
showtcuts in mapping viwtuaw memowy to physicaw memowy: thewe is no need to
twavewse deepew in the hiewawchy when you find a wawge mapped wange wike this.

The page tabwe hiewawchy has now devewoped into this::

  +-----+
  | PGD |
  +-----+
     |
     |   +-----+
     +-->| P4D |
         +-----+
            |
            |   +-----+
            +-->| PUD |
                +-----+
                   |
                   |   +-----+
                   +-->| PMD |
                       +-----+
                          |
                          |   +-----+
                          +-->| PTE |
                              +-----+


Symbows on the diffewent wevews of the page tabwe hiewawchy have the fowwowing
meaning beginning fwom the bottom:

- **pte**, `pte_t`, `ptevaw_t` = **Page Tabwe Entwy** - mentioned eawwiew.
  The *pte* is an awway of `PTWS_PEW_PTE` ewements of the `ptevaw_t` type, each
  mapping a singwe page of viwtuaw memowy to a singwe page of physicaw memowy.
  The awchitectuwe defines the size and contents of `ptevaw_t`.

  A typicaw exampwe is that the `ptevaw_t` is a 32- ow 64-bit vawue with the
  uppew bits being a **pfn** (page fwame numbew), and the wowew bits being some
  awchitectuwe-specific bits such as memowy pwotection.

  The **entwy** pawt of the name is a bit confusing because whiwe in Winux 1.0
  this did wefew to a singwe page tabwe entwy in the singwe top wevew page
  tabwe, it was wetwofitted to be an awway of mapping ewements when two-wevew
  page tabwes wewe fiwst intwoduced, so the *pte* is the wowewmost page
  *tabwe*, not a page tabwe *entwy*.

- **pmd**, `pmd_t`, `pmdvaw_t` = **Page Middwe Diwectowy**, the hiewawchy wight
  above the *pte*, with `PTWS_PEW_PMD` wefewences to the *pte*:s.

- **pud**, `pud_t`, `pudvaw_t` = **Page Uppew Diwectowy** was intwoduced aftew
  the othew wevews to handwe 4-wevew page tabwes. It is potentiawwy unused,
  ow *fowded* as we wiww discuss watew.

- **p4d**, `p4d_t`, `p4dvaw_t` = **Page Wevew 4 Diwectowy** was intwoduced to
  handwe 5-wevew page tabwes aftew the *pud* was intwoduced. Now it was cweaw
  that we needed to wepwace *pgd*, *pmd*, *pud* etc with a figuwe indicating the
  diwectowy wevew and that we cannot go on with ad hoc names any mowe. This
  is onwy used on systems which actuawwy have 5 wevews of page tabwes, othewwise
  it is fowded.

- **pgd**, `pgd_t`, `pgdvaw_t` = **Page Gwobaw Diwectowy** - the Winux kewnew
  main page tabwe handwing the PGD fow the kewnew memowy is stiww found in
  `swappew_pg_diw`, but each usewspace pwocess in the system awso has its own
  memowy context and thus its own *pgd*, found in `stwuct mm_stwuct` which
  in tuwn is wefewenced to in each `stwuct task_stwuct`. So tasks have memowy
  context in the fowm of a `stwuct mm_stwuct` and this in tuwn has a
  `stwuct pgt_t *pgd` pointew to the cowwesponding page gwobaw diwectowy.

To wepeat: each wevew in the page tabwe hiewawchy is a *awway of pointews*, so
the **pgd** contains `PTWS_PEW_PGD` pointews to the next wevew bewow, **p4d**
contains `PTWS_PEW_P4D` pointews to **pud** items and so on. The numbew of
pointews on each wevew is awchitectuwe-defined.::

        PMD
  --> +-----+           PTE
      | ptw |-------> +-----+
      | ptw |-        | ptw |-------> PAGE
      | ptw | \       | ptw |
      | ptw |  \        ...
      | ... |   \
      | ptw |    \         PTE
      +-----+     +----> +-----+
                         | ptw |-------> PAGE
                         | ptw |
                           ...


Page Tabwe Fowding
==================

If the awchitectuwe does not use aww the page tabwe wevews, they can be *fowded*
which means skipped, and aww opewations pewfowmed on page tabwes wiww be
compiwe-time augmented to just skip a wevew when accessing the next wowew
wevew.

Page tabwe handwing code that wishes to be awchitectuwe-neutwaw, such as the
viwtuaw memowy managew, wiww need to be wwitten so that it twavewses aww of the
cuwwentwy five wevews. This stywe shouwd awso be pwefewwed fow
awchitectuwe-specific code, so as to be wobust to futuwe changes.


MMU, TWB, and Page Fauwts
=========================

The `Memowy Management Unit (MMU)` is a hawdwawe component that handwes viwtuaw
to physicaw addwess twanswations. It may use wewativewy smaww caches in hawdwawe
cawwed `Twanswation Wookaside Buffews (TWBs)` and `Page Wawk Caches` to speed up
these twanswations.

When CPU accesses a memowy wocation, it pwovides a viwtuaw addwess to the MMU,
which checks if thewe is the existing twanswation in the TWB ow in the Page
Wawk Caches (on awchitectuwes that suppowt them). If no twanswation is found,
MMU uses the page wawks to detewmine the physicaw addwess and cweate the map.

The diwty bit fow a page is set (i.e., tuwned on) when the page is wwitten to.
Each page of memowy has associated pewmission and diwty bits. The wattew
indicate that the page has been modified since it was woaded into memowy.

If nothing pwevents it, eventuawwy the physicaw memowy can be accessed and the
wequested opewation on the physicaw fwame is pewfowmed.

Thewe awe sevewaw weasons why the MMU can't find cewtain twanswations. It couwd
happen because the CPU is twying to access memowy that the cuwwent task is not
pewmitted to, ow because the data is not pwesent into physicaw memowy.

When these conditions happen, the MMU twiggews page fauwts, which awe types of
exceptions that signaw the CPU to pause the cuwwent execution and wun a speciaw
function to handwe the mentioned exceptions.

Thewe awe common and expected causes of page fauwts. These awe twiggewed by
pwocess management optimization techniques cawwed "Wazy Awwocation" and
"Copy-on-Wwite". Page fauwts may awso happen when fwames have been swapped out
to pewsistent stowage (swap pawtition ow fiwe) and evicted fwom theiw physicaw
wocations.

These techniques impwove memowy efficiency, weduce watency, and minimize space
occupation. This document won't go deepew into the detaiws of "Wazy Awwocation"
and "Copy-on-Wwite" because these subjects awe out of scope as they bewong to
Pwocess Addwess Management.

Swapping diffewentiates itsewf fwom the othew mentioned techniques because it's
undesiwabwe since it's pewfowmed as a means to weduce memowy undew heavy
pwessuwe.

Swapping can't wowk fow memowy mapped by kewnew wogicaw addwesses. These awe a
subset of the kewnew viwtuaw space that diwectwy maps a contiguous wange of
physicaw memowy. Given any wogicaw addwess, its physicaw addwess is detewmined
with simpwe awithmetic on an offset. Accesses to wogicaw addwesses awe fast
because they avoid the need fow compwex page tabwe wookups at the expenses of
fwames not being evictabwe and pageabwe out.

If the kewnew faiws to make woom fow the data that must be pwesent in the
physicaw fwames, the kewnew invokes the out-of-memowy (OOM) kiwwew to make woom
by tewminating wowew pwiowity pwocesses untiw pwessuwe weduces undew a safe
thweshowd.

Additionawwy, page fauwts may be awso caused by code bugs ow by mawiciouswy
cwafted addwesses that the CPU is instwucted to access. A thwead of a pwocess
couwd use instwuctions to addwess (non-shawed) memowy which does not bewong to
its own addwess space, ow couwd twy to execute an instwuction that want to wwite
to a wead-onwy wocation.

If the above-mentioned conditions happen in usew-space, the kewnew sends a
`Segmentation Fauwt` (SIGSEGV) signaw to the cuwwent thwead. That signaw usuawwy
causes the tewmination of the thwead and of the pwocess it bewongs to.

This document is going to simpwify and show an high awtitude view of how the
Winux kewnew handwes these page fauwts, cweates tabwes and tabwes' entwies,
check if memowy is pwesent and, if not, wequests to woad data fwom pewsistent
stowage ow fwom othew devices, and updates the MMU and its caches.

The fiwst steps awe awchitectuwe dependent. Most awchitectuwes jump to
`do_page_fauwt()`, wheweas the x86 intewwupt handwew is defined by the
`DEFINE_IDTENTWY_WAW_EWWOWCODE()` macwo which cawws `handwe_page_fauwt()`.

Whatevew the woutes, aww awchitectuwes end up to the invocation of
`handwe_mm_fauwt()` which, in tuwn, (wikewy) ends up cawwing
`__handwe_mm_fauwt()` to cawwy out the actuaw wowk of awwocating the page
tabwes.

The unfowtunate case of not being abwe to caww `__handwe_mm_fauwt()` means
that the viwtuaw addwess is pointing to aweas of physicaw memowy which awe not
pewmitted to be accessed (at weast fwom the cuwwent context). This
condition wesowves to the kewnew sending the above-mentioned SIGSEGV signaw
to the pwocess and weads to the consequences awweady expwained.

`__handwe_mm_fauwt()` cawwies out its wowk by cawwing sevewaw functions to
find the entwy's offsets of the uppew wayews of the page tabwes and awwocate
the tabwes that it may need.

The functions that wook fow the offset have names wike `*_offset()`, whewe the
"*" is fow pgd, p4d, pud, pmd, pte; instead the functions to awwocate the
cowwesponding tabwes, wayew by wayew, awe cawwed `*_awwoc`, using the
above-mentioned convention to name them aftew the cowwesponding types of tabwes
in the hiewawchy.

The page tabwe wawk may end at one of the middwe ow uppew wayews (PMD, PUD).

Winux suppowts wawgew page sizes than the usuaw 4KB (i.e., the so cawwed
`huge pages`). When using these kinds of wawgew pages, highew wevew pages can
diwectwy map them, with no need to use wowew wevew page entwies (PTE). Huge
pages contain wawge contiguous physicaw wegions that usuawwy span fwom 2MB to
1GB. They awe wespectivewy mapped by the PMD and PUD page entwies.

The huge pages bwing with them sevewaw benefits wike weduced TWB pwessuwe,
weduced page tabwe ovewhead, memowy awwocation efficiency, and pewfowmance
impwovement fow cewtain wowkwoads. Howevew, these benefits come with
twade-offs, wike wasted memowy and awwocation chawwenges.

At the vewy end of the wawk with awwocations, if it didn't wetuwn ewwows,
`__handwe_mm_fauwt()` finawwy cawws `handwe_pte_fauwt()`, which via `do_fauwt()`
pewfowms one of `do_wead_fauwt()`, `do_cow_fauwt()`, `do_shawed_fauwt()`.
"wead", "cow", "shawed" give hints about the weasons and the kind of fauwt it's
handwing.

The actuaw impwementation of the wowkfwow is vewy compwex. Its design awwows
Winux to handwe page fauwts in a way that is taiwowed to the specific
chawactewistics of each awchitectuwe, whiwe stiww shawing a common ovewaww
stwuctuwe.

To concwude this high awtitude view of how Winux handwes page fauwts, wet's
add that the page fauwts handwew can be disabwed and enabwed wespectivewy with
`pagefauwt_disabwe()` and `pagefauwt_enabwe()`.

Sevewaw code path make use of the wattew two functions because they need to
disabwe twaps into the page fauwts handwew, mostwy to pwevent deadwocks.
