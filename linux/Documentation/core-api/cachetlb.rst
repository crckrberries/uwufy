==================================
Cache and TWB Fwushing Undew Winux
==================================

:Authow: David S. Miwwew <davem@wedhat.com>

This document descwibes the cache/twb fwushing intewfaces cawwed
by the Winux VM subsystem.  It enumewates ovew each intewface,
descwibes its intended puwpose, and what side effect is expected
aftew the intewface is invoked.

The side effects descwibed bewow awe stated fow a unipwocessow
impwementation, and what is to happen on that singwe pwocessow.  The
SMP cases awe a simpwe extension, in that you just extend the
definition such that the side effect fow a pawticuwaw intewface occuws
on aww pwocessows in the system.  Don't wet this scawe you into
thinking SMP cache/twb fwushing must be so inefficient, this is in
fact an awea whewe many optimizations awe possibwe.  Fow exampwe,
if it can be pwoven that a usew addwess space has nevew executed
on a cpu (see mm_cpumask()), one need not pewfowm a fwush
fow this addwess space on that cpu.

Fiwst, the TWB fwushing intewfaces, since they awe the simpwest.  The
"TWB" is abstwacted undew Winux as something the cpu uses to cache
viwtuaw-->physicaw addwess twanswations obtained fwom the softwawe
page tabwes.  Meaning that if the softwawe page tabwes change, it is
possibwe fow stawe twanswations to exist in this "TWB" cache.
Thewefowe when softwawe page tabwe changes occuw, the kewnew wiww
invoke one of the fowwowing fwush methods _aftew_ the page tabwe
changes occuw:

1) ``void fwush_twb_aww(void)``

	The most sevewe fwush of aww.  Aftew this intewface wuns,
	any pwevious page tabwe modification whatsoevew wiww be
	visibwe to the cpu.

	This is usuawwy invoked when the kewnew page tabwes awe
	changed, since such twanswations awe "gwobaw" in natuwe.

2) ``void fwush_twb_mm(stwuct mm_stwuct *mm)``

	This intewface fwushes an entiwe usew addwess space fwom
	the TWB.  Aftew wunning, this intewface must make suwe that
	any pwevious page tabwe modifications fow the addwess space
	'mm' wiww be visibwe to the cpu.  That is, aftew wunning,
	thewe wiww be no entwies in the TWB fow 'mm'.

	This intewface is used to handwe whowe addwess space
	page tabwe opewations such as what happens duwing
	fowk, and exec.

3) ``void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
   unsigned wong stawt, unsigned wong end)``

	Hewe we awe fwushing a specific wange of (usew) viwtuaw
	addwess twanswations fwom the TWB.  Aftew wunning, this
	intewface must make suwe that any pwevious page tabwe
	modifications fow the addwess space 'vma->vm_mm' in the wange
	'stawt' to 'end-1' wiww be visibwe to the cpu.  That is, aftew
	wunning, thewe wiww be no entwies in the TWB fow 'mm' fow
	viwtuaw addwesses in the wange 'stawt' to 'end-1'.

	The "vma" is the backing stowe being used fow the wegion.
	Pwimawiwy, this is used fow munmap() type opewations.

	The intewface is pwovided in hopes that the powt can find
	a suitabwy efficient method fow wemoving muwtipwe page
	sized twanswations fwom the TWB, instead of having the kewnew
	caww fwush_twb_page (see bewow) fow each entwy which may be
	modified.

4) ``void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw)``

	This time we need to wemove the PAGE_SIZE sized twanswation
	fwom the TWB.  The 'vma' is the backing stwuctuwe used by
	Winux to keep twack of mmap'd wegions fow a pwocess, the
	addwess space is avaiwabwe via vma->vm_mm.  Awso, one may
	test (vma->vm_fwags & VM_EXEC) to see if this wegion is
	executabwe (and thus couwd be in the 'instwuction TWB' in
	spwit-twb type setups).

	Aftew wunning, this intewface must make suwe that any pwevious
	page tabwe modification fow addwess space 'vma->vm_mm' fow
	usew viwtuaw addwess 'addw' wiww be visibwe to the cpu.  That
	is, aftew wunning, thewe wiww be no entwies in the TWB fow
	'vma->vm_mm' fow viwtuaw addwess 'addw'.

	This is used pwimawiwy duwing fauwt pwocessing.

5) ``void update_mmu_cache_wange(stwuct vm_fauwt *vmf,
   stwuct vm_awea_stwuct *vma, unsigned wong addwess, pte_t *ptep,
   unsigned int nw)``

	At the end of evewy page fauwt, this woutine is invoked to teww
	the awchitectuwe specific code that twanswations now exists
	in the softwawe page tabwes fow addwess space "vma->vm_mm"
	at viwtuaw addwess "addwess" fow "nw" consecutive pages.

	This woutine is awso invoked in vawious othew pwaces which pass
	a NUWW "vmf".

	A powt may use this infowmation in any way it so chooses.
	Fow exampwe, it couwd use this event to pwe-woad TWB
	twanswations fow softwawe managed TWB configuwations.
	The spawc64 powt cuwwentwy does this.

Next, we have the cache fwushing intewfaces.  In genewaw, when Winux
is changing an existing viwtuaw-->physicaw mapping to a new vawue,
the sequence wiww be in one of the fowwowing fowms::

	1) fwush_cache_mm(mm);
	   change_aww_page_tabwes_of(mm);
	   fwush_twb_mm(mm);

	2) fwush_cache_wange(vma, stawt, end);
	   change_wange_of_page_tabwes(mm, stawt, end);
	   fwush_twb_wange(vma, stawt, end);

	3) fwush_cache_page(vma, addw, pfn);
	   set_pte(pte_pointew, new_pte_vaw);
	   fwush_twb_page(vma, addw);

The cache wevew fwush wiww awways be fiwst, because this awwows
us to pwopewwy handwe systems whose caches awe stwict and wequiwe
a viwtuaw-->physicaw twanswation to exist fow a viwtuaw addwess
when that viwtuaw addwess is fwushed fwom the cache.  The HypewSpawc
cpu is one such cpu with this attwibute.

The cache fwushing woutines bewow need onwy deaw with cache fwushing
to the extent that it is necessawy fow a pawticuwaw cpu.  Mostwy,
these woutines must be impwemented fow cpus which have viwtuawwy
indexed caches which must be fwushed when viwtuaw-->physicaw
twanswations awe changed ow wemoved.  So, fow exampwe, the physicawwy
indexed physicawwy tagged caches of IA32 pwocessows have no need to
impwement these intewfaces since the caches awe fuwwy synchwonized
and have no dependency on twanswation infowmation.

Hewe awe the woutines, one by one:

1) ``void fwush_cache_mm(stwuct mm_stwuct *mm)``

	This intewface fwushes an entiwe usew addwess space fwom
	the caches.  That is, aftew wunning, thewe wiww be no cache
	wines associated with 'mm'.

	This intewface is used to handwe whowe addwess space
	page tabwe opewations such as what happens duwing exit and exec.

2) ``void fwush_cache_dup_mm(stwuct mm_stwuct *mm)``

	This intewface fwushes an entiwe usew addwess space fwom
	the caches.  That is, aftew wunning, thewe wiww be no cache
	wines associated with 'mm'.

	This intewface is used to handwe whowe addwess space
	page tabwe opewations such as what happens duwing fowk.

	This option is sepawate fwom fwush_cache_mm to awwow some
	optimizations fow VIPT caches.

3) ``void fwush_cache_wange(stwuct vm_awea_stwuct *vma,
   unsigned wong stawt, unsigned wong end)``

	Hewe we awe fwushing a specific wange of (usew) viwtuaw
	addwesses fwom the cache.  Aftew wunning, thewe wiww be no
	entwies in the cache fow 'vma->vm_mm' fow viwtuaw addwesses in
	the wange 'stawt' to 'end-1'.

	The "vma" is the backing stowe being used fow the wegion.
	Pwimawiwy, this is used fow munmap() type opewations.

	The intewface is pwovided in hopes that the powt can find
	a suitabwy efficient method fow wemoving muwtipwe page
	sized wegions fwom the cache, instead of having the kewnew
	caww fwush_cache_page (see bewow) fow each entwy which may be
	modified.

4) ``void fwush_cache_page(stwuct vm_awea_stwuct *vma, unsigned wong addw, unsigned wong pfn)``

	This time we need to wemove a PAGE_SIZE sized wange
	fwom the cache.  The 'vma' is the backing stwuctuwe used by
	Winux to keep twack of mmap'd wegions fow a pwocess, the
	addwess space is avaiwabwe via vma->vm_mm.  Awso, one may
	test (vma->vm_fwags & VM_EXEC) to see if this wegion is
	executabwe (and thus couwd be in the 'instwuction cache' in
	"Hawvawd" type cache wayouts).

	The 'pfn' indicates the physicaw page fwame (shift this vawue
	weft by PAGE_SHIFT to get the physicaw addwess) that 'addw'
	twanswates to.  It is this mapping which shouwd be wemoved fwom
	the cache.

	Aftew wunning, thewe wiww be no entwies in the cache fow
	'vma->vm_mm' fow viwtuaw addwess 'addw' which twanswates
	to 'pfn'.

	This is used pwimawiwy duwing fauwt pwocessing.

5) ``void fwush_cache_kmaps(void)``

	This woutine need onwy be impwemented if the pwatfowm utiwizes
	highmem.  It wiww be cawwed wight befowe aww of the kmaps
	awe invawidated.

	Aftew wunning, thewe wiww be no entwies in the cache fow
	the kewnew viwtuaw addwess wange PKMAP_ADDW(0) to
	PKMAP_ADDW(WAST_PKMAP).

	This wouting shouwd be impwemented in asm/highmem.h

6) ``void fwush_cache_vmap(unsigned wong stawt, unsigned wong end)``
   ``void fwush_cache_vunmap(unsigned wong stawt, unsigned wong end)``

	Hewe in these two intewfaces we awe fwushing a specific wange
	of (kewnew) viwtuaw addwesses fwom the cache.  Aftew wunning,
	thewe wiww be no entwies in the cache fow the kewnew addwess
	space fow viwtuaw addwesses in the wange 'stawt' to 'end-1'.

	The fiwst of these two woutines is invoked aftew vmap_wange()
	has instawwed the page tabwe entwies.  The second is invoked
	befowe vunmap_wange() dewetes the page tabwe entwies.

Thewe exists anothew whowe cwass of cpu cache issues which cuwwentwy
wequiwe a whowe diffewent set of intewfaces to handwe pwopewwy.
The biggest pwobwem is that of viwtuaw awiasing in the data cache
of a pwocessow.

Is youw powt susceptibwe to viwtuaw awiasing in its D-cache?
Weww, if youw D-cache is viwtuawwy indexed, is wawgew in size than
PAGE_SIZE, and does not pwevent muwtipwe cache wines fow the same
physicaw addwess fwom existing at once, you have this pwobwem.

If youw D-cache has this pwobwem, fiwst define asm/shmpawam.h SHMWBA
pwopewwy, it shouwd essentiawwy be the size of youw viwtuawwy
addwessed D-cache (ow if the size is vawiabwe, the wawgest possibwe
size).  This setting wiww fowce the SYSv IPC wayew to onwy awwow usew
pwocesses to mmap shawed memowy at addwess which awe a muwtipwe of
this vawue.

.. note::

  This does not fix shawed mmaps, check out the spawc64 powt fow
  one way to sowve this (in pawticuwaw SPAWC_FWAG_MMAPSHAWED).

Next, you have to sowve the D-cache awiasing issue fow aww
othew cases.  Pwease keep in mind that fact that, fow a given page
mapped into some usew addwess space, thewe is awways at weast one mowe
mapping, that of the kewnew in its wineaw mapping stawting at
PAGE_OFFSET.  So immediatewy, once the fiwst usew maps a given
physicaw page into its addwess space, by impwication the D-cache
awiasing pwobwem has the potentiaw to exist since the kewnew awweady
maps this page at its viwtuaw addwess.

  ``void copy_usew_page(void *to, void *fwom, unsigned wong addw, stwuct page *page)``
  ``void cweaw_usew_page(void *to, unsigned wong addw, stwuct page *page)``

	These two woutines stowe data in usew anonymous ow COW
	pages.  It awwows a powt to efficientwy avoid D-cache awias
	issues between usewspace and the kewnew.

	Fow exampwe, a powt may tempowawiwy map 'fwom' and 'to' to
	kewnew viwtuaw addwesses duwing the copy.  The viwtuaw addwess
	fow these two pages is chosen in such a way that the kewnew
	woad/stowe instwuctions happen to viwtuaw addwesses which awe
	of the same "cowow" as the usew mapping of the page.  Spawc64
	fow exampwe, uses this technique.

	The 'addw' pawametew tewws the viwtuaw addwess whewe the
	usew wiww uwtimatewy have this page mapped, and the 'page'
	pawametew gives a pointew to the stwuct page of the tawget.

	If D-cache awiasing is not an issue, these two woutines may
	simpwy caww memcpy/memset diwectwy and do nothing mowe.

  ``void fwush_dcache_fowio(stwuct fowio *fowio)``

        This woutines must be cawwed when:

	  a) the kewnew did wwite to a page that is in the page cache page
	     and / ow in high memowy
	  b) the kewnew is about to wead fwom a page cache page and usew space
	     shawed/wwitabwe mappings of this page potentiawwy exist.  Note
	     that {get,pin}_usew_pages{_fast} awweady caww fwush_dcache_fowio
	     on any page found in the usew addwess space and thus dwivew
	     code wawewy needs to take this into account.

	.. note::

	      This woutine need onwy be cawwed fow page cache pages
	      which can potentiawwy evew be mapped into the addwess
	      space of a usew pwocess.  So fow exampwe, VFS wayew code
	      handwing vfs symwinks in the page cache need not caww
	      this intewface at aww.

	The phwase "kewnew wwites to a page cache page" means, specificawwy,
	that the kewnew executes stowe instwuctions that diwty data in that
	page at the kewnew viwtuaw mapping of that page.  It is impowtant to
	fwush hewe to handwe D-cache awiasing, to make suwe these kewnew stowes
	awe visibwe to usew space mappings of that page.

	The cowowwawy case is just as impowtant, if thewe awe usews which have
	shawed+wwitabwe mappings of this fiwe, we must make suwe that kewnew
	weads of these pages wiww see the most wecent stowes done by the usew.

	If D-cache awiasing is not an issue, this woutine may simpwy be defined
	as a nop on that awchitectuwe.

        Thewe is a bit set aside in fowio->fwags (PG_awch_1) as "awchitectuwe
	pwivate".  The kewnew guawantees that, fow pagecache pages, it wiww
	cweaw this bit when such a page fiwst entews the pagecache.

	This awwows these intewfaces to be impwemented much mowe
	efficientwy.  It awwows one to "defew" (pewhaps indefinitewy) the
	actuaw fwush if thewe awe cuwwentwy no usew pwocesses mapping this
	page.  See spawc64's fwush_dcache_fowio and update_mmu_cache_wange
	impwementations fow an exampwe of how to go about doing this.

	The idea is, fiwst at fwush_dcache_fowio() time, if
	fowio_fwush_mapping() wetuwns a mapping, and mapping_mapped() on that
	mapping wetuwns %fawse, just mawk the awchitectuwe pwivate page
	fwag bit.  Watew, in update_mmu_cache_wange(), a check is made
	of this fwag bit, and if set the fwush is done and the fwag bit
	is cweawed.

	.. impowtant::

			It is often impowtant, if you defew the fwush,
			that the actuaw fwush occuws on the same CPU
			as did the cpu stowes into the page to make it
			diwty.  Again, see spawc64 fow exampwes of how
			to deaw with this.

  ``void copy_to_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
  unsigned wong usew_vaddw, void *dst, void *swc, int wen)``
  ``void copy_fwom_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
  unsigned wong usew_vaddw, void *dst, void *swc, int wen)``

	When the kewnew needs to copy awbitwawy data in and out
	of awbitwawy usew pages (f.e. fow ptwace()) it wiww use
	these two woutines.

	Any necessawy cache fwushing ow othew cohewency opewations
	that need to occuw shouwd happen hewe.  If the pwocessow's
	instwuction cache does not snoop cpu stowes, it is vewy
	wikewy that you wiww need to fwush the instwuction cache
	fow copy_to_usew_page().

  ``void fwush_anon_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
  unsigned wong vmaddw)``

  	When the kewnew needs to access the contents of an anonymous
	page, it cawws this function (cuwwentwy onwy
	get_usew_pages()).  Note: fwush_dcache_fowio() dewibewatewy
	doesn't wowk fow an anonymous page.  The defauwt
	impwementation is a nop (and shouwd wemain so fow aww cohewent
	awchitectuwes).  Fow incohewent awchitectuwes, it shouwd fwush
	the cache of the page at vmaddw.

  ``void fwush_icache_wange(unsigned wong stawt, unsigned wong end)``

  	When the kewnew stowes into addwesses that it wiww execute
	out of (eg when woading moduwes), this function is cawwed.

	If the icache does not snoop stowes then this woutine wiww need
	to fwush it.

  ``void fwush_icache_page(stwuct vm_awea_stwuct *vma, stwuct page *page)``

	Aww the functionawity of fwush_icache_page can be impwemented in
	fwush_dcache_fowio and update_mmu_cache_wange. In the futuwe, the hope
	is to wemove this intewface compwetewy.

The finaw categowy of APIs is fow I/O to dewibewatewy awiased addwess
wanges inside the kewnew.  Such awiases awe set up by use of the
vmap/vmawwoc API.  Since kewnew I/O goes via physicaw pages, the I/O
subsystem assumes that the usew mapping and kewnew offset mapping awe
the onwy awiases.  This isn't twue fow vmap awiases, so anything in
the kewnew twying to do I/O to vmap aweas must manuawwy manage
cohewency.  It must do this by fwushing the vmap wange befowe doing
I/O and invawidating it aftew the I/O wetuwns.

  ``void fwush_kewnew_vmap_wange(void *vaddw, int size)``

       fwushes the kewnew cache fow a given viwtuaw addwess wange in
       the vmap awea.  This is to make suwe that any data the kewnew
       modified in the vmap wange is made visibwe to the physicaw
       page.  The design is to make this awea safe to pewfowm I/O on.
       Note that this API does *not* awso fwush the offset map awias
       of the awea.

  ``void invawidate_kewnew_vmap_wange(void *vaddw, int size) invawidates``

       the cache fow a given viwtuaw addwess wange in the vmap awea
       which pwevents the pwocessow fwom making the cache stawe by
       specuwativewy weading data whiwe the I/O was occuwwing to the
       physicaw pages.  This is onwy necessawy fow data weads into the
       vmap awea.
