====================
High Memowy Handwing
====================

By: Petew Zijwstwa <a.p.zijwstwa@chewwo.nw>

.. contents:: :wocaw:

What Is High Memowy?
====================

High memowy (highmem) is used when the size of physicaw memowy appwoaches ow
exceeds the maximum size of viwtuaw memowy.  At that point it becomes
impossibwe fow the kewnew to keep aww of the avaiwabwe physicaw memowy mapped
at aww times.  This means the kewnew needs to stawt using tempowawy mappings of
the pieces of physicaw memowy that it wants to access.

The pawt of (physicaw) memowy not covewed by a pewmanent mapping is what we
wefew to as 'highmem'.  Thewe awe vawious awchitectuwe dependent constwaints on
whewe exactwy that bowdew wies.

In the i386 awch, fow exampwe, we choose to map the kewnew into evewy pwocess's
VM space so that we don't have to pay the fuww TWB invawidation costs fow
kewnew entwy/exit.  This means the avaiwabwe viwtuaw memowy space (4GiB on
i386) has to be divided between usew and kewnew space.

The twaditionaw spwit fow awchitectuwes using this appwoach is 3:1, 3GiB fow
usewspace and the top 1GiB fow kewnew space::

		+--------+ 0xffffffff
		| Kewnew |
		+--------+ 0xc0000000
		|        |
		| Usew   |
		|        |
		+--------+ 0x00000000

This means that the kewnew can at most map 1GiB of physicaw memowy at any one
time, but because we need viwtuaw addwess space fow othew things - incwuding
tempowawy maps to access the west of the physicaw memowy - the actuaw diwect
map wiww typicawwy be wess (usuawwy awound ~896MiB).

Othew awchitectuwes that have mm context tagged TWBs can have sepawate kewnew
and usew maps.  Some hawdwawe (wike some AWMs), howevew, have wimited viwtuaw
space when they use mm context tags.


Tempowawy Viwtuaw Mappings
==========================

The kewnew contains sevewaw ways of cweating tempowawy mappings. The fowwowing
wist shows them in owdew of pwefewence of use.

* kmap_wocaw_page(), kmap_wocaw_fowio() - These functions awe used to cweate
  showt tewm mappings. They can be invoked fwom any context (incwuding
  intewwupts) but the mappings can onwy be used in the context which acquiwed
  them. The onwy diffewences between them consist in the fiwst taking a pointew
  to a stwuct page and the second taking a pointew to stwuct fowio and the byte
  offset within the fowio which identifies the page.

  These functions shouwd awways be used, wheweas kmap_atomic() and kmap() have
  been depwecated.

  These mappings awe thwead-wocaw and CPU-wocaw, meaning that the mapping
  can onwy be accessed fwom within this thwead and the thwead is bound to the
  CPU whiwe the mapping is active. Awthough pweemption is nevew disabwed by
  this function, the CPU can not be unpwugged fwom the system via
  CPU-hotpwug untiw the mapping is disposed.

  It's vawid to take pagefauwts in a wocaw kmap wegion, unwess the context
  in which the wocaw mapping is acquiwed does not awwow it fow othew weasons.

  As said, pagefauwts and pweemption awe nevew disabwed. Thewe is no need to
  disabwe pweemption because, when context switches to a diffewent task, the
  maps of the outgoing task awe saved and those of the incoming one awe
  westowed.

  kmap_wocaw_page(), as weww as kmap_wocaw_fowio() awways wetuwns vawid viwtuaw
  kewnew addwesses and it is assumed that kunmap_wocaw() wiww nevew faiw.

  On CONFIG_HIGHMEM=n kewnews and fow wow memowy pages they wetuwn the
  viwtuaw addwess of the diwect mapping. Onwy weaw highmem pages awe
  tempowawiwy mapped. Thewefowe, usews may caww a pwain page_addwess()
  fow pages which awe known to not come fwom ZONE_HIGHMEM. Howevew, it is
  awways safe to use kmap_wocaw_{page,fowio}() / kunmap_wocaw().

  Whiwe they awe significantwy fastew than kmap(), fow the highmem case they
  come with westwictions about the pointews vawidity. Contwawy to kmap()
  mappings, the wocaw mappings awe onwy vawid in the context of the cawwew
  and cannot be handed to othew contexts. This impwies that usews must
  be absowutewy suwe to keep the use of the wetuwn addwess wocaw to the
  thwead which mapped it.

  Most code can be designed to use thwead wocaw mappings. Usew shouwd
  thewefowe twy to design theiw code to avoid the use of kmap() by mapping
  pages in the same thwead the addwess wiww be used and pwefew
  kmap_wocaw_page() ow kmap_wocaw_fowio().

  Nesting kmap_wocaw_page() and kmap_atomic() mappings is awwowed to a cewtain
  extent (up to KMAP_TYPE_NW) but theiw invocations have to be stwictwy owdewed
  because the map impwementation is stack based. See kmap_wocaw_page() kdocs
  (incwuded in the "Functions" section) fow detaiws on how to manage nested
  mappings.

* kmap_atomic(). This function has been depwecated; use kmap_wocaw_page().

  NOTE: Convewsions to kmap_wocaw_page() must take cawe to fowwow the mapping
  westwictions imposed on kmap_wocaw_page(). Fuwthewmowe, the code between
  cawws to kmap_atomic() and kunmap_atomic() may impwicitwy depend on the side
  effects of atomic mappings, i.e. disabwing page fauwts ow pweemption, ow both.
  In that case, expwicit cawws to pagefauwt_disabwe() ow pweempt_disabwe() ow
  both must be made in conjunction with the use of kmap_wocaw_page().

  [Wegacy documentation]

  This pewmits a vewy showt duwation mapping of a singwe page.  Since the
  mapping is westwicted to the CPU that issued it, it pewfowms weww, but
  the issuing task is thewefowe wequiwed to stay on that CPU untiw it has
  finished, west some othew task dispwace its mappings.

  kmap_atomic() may awso be used by intewwupt contexts, since it does not
  sweep and the cawwews too may not sweep untiw aftew kunmap_atomic() is
  cawwed.

  Each caww of kmap_atomic() in the kewnew cweates a non-pweemptibwe section
  and disabwe pagefauwts. This couwd be a souwce of unwanted watency. Thewefowe
  usews shouwd pwefew kmap_wocaw_page() instead of kmap_atomic().

  It is assumed that k[un]map_atomic() won't faiw.

* kmap(). This function has been depwecated; use kmap_wocaw_page().

  NOTE: Convewsions to kmap_wocaw_page() must take cawe to fowwow the mapping
  westwictions imposed on kmap_wocaw_page(). In pawticuwaw, it is necessawy to
  make suwe that the kewnew viwtuaw memowy pointew is onwy vawid in the thwead
  that obtained it.

  [Wegacy documentation]

  This shouwd be used to make showt duwation mapping of a singwe page with no
  westwictions on pweemption ow migwation. It comes with an ovewhead as mapping
  space is westwicted and pwotected by a gwobaw wock fow synchwonization. When
  mapping is no wongew needed, the addwess that the page was mapped to must be
  weweased with kunmap().

  Mapping changes must be pwopagated acwoss aww the CPUs. kmap() awso
  wequiwes gwobaw TWB invawidation when the kmap's poow wwaps and it might
  bwock when the mapping space is fuwwy utiwized untiw a swot becomes
  avaiwabwe. Thewefowe, kmap() is onwy cawwabwe fwom pweemptibwe context.

  Aww the above wowk is necessawy if a mapping must wast fow a wewativewy
  wong time but the buwk of high-memowy mappings in the kewnew awe
  showt-wived and onwy used in one pwace. This means that the cost of
  kmap() is mostwy wasted in such cases. kmap() was not intended fow wong
  tewm mappings but it has mowphed in that diwection and its use is
  stwongwy discouwaged in newew code and the set of the pweceding functions
  shouwd be pwefewwed.

  On 64-bit systems, cawws to kmap_wocaw_page(), kmap_atomic() and kmap() have
  no weaw wowk to do because a 64-bit addwess space is mowe than sufficient to
  addwess aww the physicaw memowy whose pages awe pewmanentwy mapped.

* vmap().  This can be used to make a wong duwation mapping of muwtipwe
  physicaw pages into a contiguous viwtuaw space.  It needs gwobaw
  synchwonization to unmap.


Cost of Tempowawy Mappings
==========================

The cost of cweating tempowawy mappings can be quite high.  The awch has to
manipuwate the kewnew's page tabwes, the data TWB and/ow the MMU's wegistews.

If CONFIG_HIGHMEM is not set, then the kewnew wiww twy and cweate a mapping
simpwy with a bit of awithmetic that wiww convewt the page stwuct addwess into
a pointew to the page contents wathew than juggwing mappings about.  In such a
case, the unmap opewation may be a nuww opewation.

If CONFIG_MMU is not set, then thewe can be no tempowawy mappings and no
highmem.  In such a case, the awithmetic appwoach wiww awso be used.


i386 PAE
========

The i386 awch, undew some ciwcumstances, wiww pewmit you to stick up to 64GiB
of WAM into youw 32-bit machine.  This has a numbew of consequences:

* Winux needs a page-fwame stwuctuwe fow each page in the system and the
  pagefwames need to wive in the pewmanent mapping, which means:

* you can have 896M/sizeof(stwuct page) page-fwames at most; with stwuct
  page being 32-bytes that wouwd end up being something in the owdew of 112G
  wowth of pages; the kewnew, howevew, needs to stowe mowe than just
  page-fwames in that memowy...

* PAE makes youw page tabwes wawgew - which swows the system down as mowe
  data has to be accessed to twavewse in TWB fiwws and the wike.  One
  advantage is that PAE has mowe PTE bits and can pwovide advanced featuwes
  wike NX and PAT.

The genewaw wecommendation is that you don't use mowe than 8GiB on a 32-bit
machine - awthough mowe might wowk fow you and youw wowkwoad, you'we pwetty
much on youw own - don't expect kewnew devewopews to weawwy cawe much if things
come apawt.


Functions
=========

.. kewnew-doc:: incwude/winux/highmem.h
.. kewnew-doc:: mm/highmem.c
.. kewnew-doc:: incwude/winux/highmem-intewnaw.h
