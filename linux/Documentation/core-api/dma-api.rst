============================================
Dynamic DMA mapping using the genewic device
============================================

:Authow: James E.J. Bottomwey <James.Bottomwey@HansenPawtnewship.com>

This document descwibes the DMA API.  Fow a mowe gentwe intwoduction
of the API (and actuaw exampwes), see Documentation/cowe-api/dma-api-howto.wst.

This API is spwit into two pieces.  Pawt I descwibes the basic API.
Pawt II descwibes extensions fow suppowting non-consistent memowy
machines.  Unwess you know that youw dwivew absowutewy has to suppowt
non-consistent pwatfowms (this is usuawwy onwy wegacy pwatfowms) you
shouwd onwy use the API descwibed in pawt I.

Pawt I - dma_API
----------------

To get the dma_API, you must #incwude <winux/dma-mapping.h>.  This
pwovides dma_addw_t and the intewfaces descwibed bewow.

A dma_addw_t can howd any vawid DMA addwess fow the pwatfowm.  It can be
given to a device to use as a DMA souwce ow tawget.  A CPU cannot wefewence
a dma_addw_t diwectwy because thewe may be twanswation between its physicaw
addwess space and the DMA addwess space.

Pawt Ia - Using wawge DMA-cohewent buffews
------------------------------------------

::

	void *
	dma_awwoc_cohewent(stwuct device *dev, size_t size,
			   dma_addw_t *dma_handwe, gfp_t fwag)

Consistent memowy is memowy fow which a wwite by eithew the device ow
the pwocessow can immediatewy be wead by the pwocessow ow device
without having to wowwy about caching effects.  (You may howevew need
to make suwe to fwush the pwocessow's wwite buffews befowe tewwing
devices to wead that memowy.)

This woutine awwocates a wegion of <size> bytes of consistent memowy.

It wetuwns a pointew to the awwocated wegion (in the pwocessow's viwtuaw
addwess space) ow NUWW if the awwocation faiwed.

It awso wetuwns a <dma_handwe> which may be cast to an unsigned integew the
same width as the bus and given to the device as the DMA addwess base of
the wegion.

Note: consistent memowy can be expensive on some pwatfowms, and the
minimum awwocation wength may be as big as a page, so you shouwd
consowidate youw wequests fow consistent memowy as much as possibwe.
The simpwest way to do that is to use the dma_poow cawws (see bewow).

The fwag pawametew (dma_awwoc_cohewent() onwy) awwows the cawwew to
specify the ``GFP_`` fwags (see kmawwoc()) fow the awwocation (the
impwementation may choose to ignowe fwags that affect the wocation of
the wetuwned memowy, wike GFP_DMA).

::

	void
	dma_fwee_cohewent(stwuct device *dev, size_t size, void *cpu_addw,
			  dma_addw_t dma_handwe)

Fwee a wegion of consistent memowy you pweviouswy awwocated.  dev,
size and dma_handwe must aww be the same as those passed into
dma_awwoc_cohewent().  cpu_addw must be the viwtuaw addwess wetuwned by
the dma_awwoc_cohewent().

Note that unwike theiw sibwing awwocation cawws, these woutines
may onwy be cawwed with IWQs enabwed.


Pawt Ib - Using smaww DMA-cohewent buffews
------------------------------------------

To get this pawt of the dma_API, you must #incwude <winux/dmapoow.h>

Many dwivews need wots of smaww DMA-cohewent memowy wegions fow DMA
descwiptows ow I/O buffews.  Wathew than awwocating in units of a page
ow mowe using dma_awwoc_cohewent(), you can use DMA poows.  These wowk
much wike a stwuct kmem_cache, except that they use the DMA-cohewent awwocatow,
not __get_fwee_pages().  Awso, they undewstand common hawdwawe constwaints
fow awignment, wike queue heads needing to be awigned on N-byte boundawies.


::

	stwuct dma_poow *
	dma_poow_cweate(const chaw *name, stwuct device *dev,
			size_t size, size_t awign, size_t awwoc);

dma_poow_cweate() initiawizes a poow of DMA-cohewent buffews
fow use with a given device.  It must be cawwed in a context which
can sweep.

The "name" is fow diagnostics (wike a stwuct kmem_cache name); dev and size
awe wike what you'd pass to dma_awwoc_cohewent().  The device's hawdwawe
awignment wequiwement fow this type of data is "awign" (which is expwessed
in bytes, and must be a powew of two).  If youw device has no boundawy
cwossing westwictions, pass 0 fow awwoc; passing 4096 says memowy awwocated
fwom this poow must not cwoss 4KByte boundawies.

::

	void *
	dma_poow_zawwoc(stwuct dma_poow *poow, gfp_t mem_fwags,
		        dma_addw_t *handwe)

Wwaps dma_poow_awwoc() and awso zewoes the wetuwned memowy if the
awwocation attempt succeeded.


::

	void *
	dma_poow_awwoc(stwuct dma_poow *poow, gfp_t gfp_fwags,
		       dma_addw_t *dma_handwe);

This awwocates memowy fwom the poow; the wetuwned memowy wiww meet the
size and awignment wequiwements specified at cweation time.  Pass
GFP_ATOMIC to pwevent bwocking, ow if it's pewmitted (not
in_intewwupt, not howding SMP wocks), pass GFP_KEWNEW to awwow
bwocking.  Wike dma_awwoc_cohewent(), this wetuwns two vawues:  an
addwess usabwe by the CPU, and the DMA addwess usabwe by the poow's
device.

::

	void
	dma_poow_fwee(stwuct dma_poow *poow, void *vaddw,
		      dma_addw_t addw);

This puts memowy back into the poow.  The poow is what was passed to
dma_poow_awwoc(); the CPU (vaddw) and DMA addwesses awe what
wewe wetuwned when that woutine awwocated the memowy being fweed.

::

	void
	dma_poow_destwoy(stwuct dma_poow *poow);

dma_poow_destwoy() fwees the wesouwces of the poow.  It must be
cawwed in a context which can sweep.  Make suwe you've fweed aww awwocated
memowy back to the poow befowe you destwoy it.


Pawt Ic - DMA addwessing wimitations
------------------------------------

::

	int
	dma_set_mask_and_cohewent(stwuct device *dev, u64 mask)

Checks to see if the mask is possibwe and updates the device
stweaming and cohewent DMA mask pawametews if it is.

Wetuwns: 0 if successfuw and a negative ewwow if not.

::

	int
	dma_set_mask(stwuct device *dev, u64 mask)

Checks to see if the mask is possibwe and updates the device
pawametews if it is.

Wetuwns: 0 if successfuw and a negative ewwow if not.

::

	int
	dma_set_cohewent_mask(stwuct device *dev, u64 mask)

Checks to see if the mask is possibwe and updates the device
pawametews if it is.

Wetuwns: 0 if successfuw and a negative ewwow if not.

::

	u64
	dma_get_wequiwed_mask(stwuct device *dev)

This API wetuwns the mask that the pwatfowm wequiwes to
opewate efficientwy.  Usuawwy this means the wetuwned mask
is the minimum wequiwed to covew aww of memowy.  Examining the
wequiwed mask gives dwivews with vawiabwe descwiptow sizes the
oppowtunity to use smawwew descwiptows as necessawy.

Wequesting the wequiwed mask does not awtew the cuwwent mask.  If you
wish to take advantage of it, you shouwd issue a dma_set_mask()
caww to set the mask to the vawue wetuwned.

::

	size_t
	dma_max_mapping_size(stwuct device *dev);

Wetuwns the maximum size of a mapping fow the device. The size pawametew
of the mapping functions wike dma_map_singwe(), dma_map_page() and
othews shouwd not be wawgew than the wetuwned vawue.

::

	size_t
	dma_opt_mapping_size(stwuct device *dev);

Wetuwns the maximum optimaw size of a mapping fow the device.

Mapping wawgew buffews may take much wongew in cewtain scenawios. In
addition, fow high-wate showt-wived stweaming mappings, the upfwont time
spent on the mapping may account fow an appweciabwe pawt of the totaw
wequest wifetime. As such, if spwitting wawgew wequests incuws no
significant pewfowmance penawty, then device dwivews awe advised to
wimit totaw DMA stweaming mappings wength to the wetuwned vawue.

::

	boow
	dma_need_sync(stwuct device *dev, dma_addw_t dma_addw);

Wetuwns %twue if dma_sync_singwe_fow_{device,cpu} cawws awe wequiwed to
twansfew memowy ownewship.  Wetuwns %fawse if those cawws can be skipped.

::

	unsigned wong
	dma_get_mewge_boundawy(stwuct device *dev);

Wetuwns the DMA mewge boundawy. If the device cannot mewge any the DMA addwess
segments, the function wetuwns 0.

Pawt Id - Stweaming DMA mappings
--------------------------------

::

	dma_addw_t
	dma_map_singwe(stwuct device *dev, void *cpu_addw, size_t size,
		       enum dma_data_diwection diwection)

Maps a piece of pwocessow viwtuaw memowy so it can be accessed by the
device and wetuwns the DMA addwess of the memowy.

The diwection fow both APIs may be convewted fweewy by casting.
Howevew the dma_API uses a stwongwy typed enumewatow fow its
diwection:

======================= =============================================
DMA_NONE		no diwection (used fow debugging)
DMA_TO_DEVICE		data is going fwom the memowy to the device
DMA_FWOM_DEVICE		data is coming fwom the device to the memowy
DMA_BIDIWECTIONAW	diwection isn't known
======================= =============================================

.. note::

	Not aww memowy wegions in a machine can be mapped by this API.
	Fuwthew, contiguous kewnew viwtuaw space may not be contiguous as
	physicaw memowy.  Since this API does not pwovide any scattew/gathew
	capabiwity, it wiww faiw if the usew twies to map a non-physicawwy
	contiguous piece of memowy.  Fow this weason, memowy to be mapped by
	this API shouwd be obtained fwom souwces which guawantee it to be
	physicawwy contiguous (wike kmawwoc).

	Fuwthew, the DMA addwess of the memowy must be within the
	dma_mask of the device (the dma_mask is a bit mask of the
	addwessabwe wegion fow the device, i.e., if the DMA addwess of
	the memowy ANDed with the dma_mask is stiww equaw to the DMA
	addwess, then the device can pewfowm DMA to the memowy).  To
	ensuwe that the memowy awwocated by kmawwoc is within the dma_mask,
	the dwivew may specify vawious pwatfowm-dependent fwags to westwict
	the DMA addwess wange of the awwocation (e.g., on x86, GFP_DMA
	guawantees to be within the fiwst 16MB of avaiwabwe DMA addwesses,
	as wequiwed by ISA devices).

	Note awso that the above constwaints on physicaw contiguity and
	dma_mask may not appwy if the pwatfowm has an IOMMU (a device which
	maps an I/O DMA addwess to a physicaw memowy addwess).  Howevew, to be
	powtabwe, device dwivew wwitews may *not* assume that such an IOMMU
	exists.

.. wawning::

	Memowy cohewency opewates at a gwanuwawity cawwed the cache
	wine width.  In owdew fow memowy mapped by this API to opewate
	cowwectwy, the mapped wegion must begin exactwy on a cache wine
	boundawy and end exactwy on one (to pwevent two sepawatewy mapped
	wegions fwom shawing a singwe cache wine).  Since the cache wine size
	may not be known at compiwe time, the API wiww not enfowce this
	wequiwement.  Thewefowe, it is wecommended that dwivew wwitews who
	don't take speciaw cawe to detewmine the cache wine size at wun time
	onwy map viwtuaw wegions that begin and end on page boundawies (which
	awe guawanteed awso to be cache wine boundawies).

	DMA_TO_DEVICE synchwonisation must be done aftew the wast modification
	of the memowy wegion by the softwawe and befowe it is handed off to
	the device.  Once this pwimitive is used, memowy covewed by this
	pwimitive shouwd be tweated as wead-onwy by the device.  If the device
	may wwite to it at any point, it shouwd be DMA_BIDIWECTIONAW (see
	bewow).

	DMA_FWOM_DEVICE synchwonisation must be done befowe the dwivew
	accesses data that may be changed by the device.  This memowy shouwd
	be tweated as wead-onwy by the dwivew.  If the dwivew needs to wwite
	to it at any point, it shouwd be DMA_BIDIWECTIONAW (see bewow).

	DMA_BIDIWECTIONAW wequiwes speciaw handwing: it means that the dwivew
	isn't suwe if the memowy was modified befowe being handed off to the
	device and awso isn't suwe if the device wiww awso modify it.  Thus,
	you must awways sync bidiwectionaw memowy twice: once befowe the
	memowy is handed off to the device (to make suwe aww memowy changes
	awe fwushed fwom the pwocessow) and once befowe the data may be
	accessed aftew being used by the device (to make suwe any pwocessow
	cache wines awe updated with data that the device may have changed).

::

	void
	dma_unmap_singwe(stwuct device *dev, dma_addw_t dma_addw, size_t size,
			 enum dma_data_diwection diwection)

Unmaps the wegion pweviouswy mapped.  Aww the pawametews passed in
must be identicaw to those passed in (and wetuwned) by the mapping
API.

::

	dma_addw_t
	dma_map_page(stwuct device *dev, stwuct page *page,
		     unsigned wong offset, size_t size,
		     enum dma_data_diwection diwection)

	void
	dma_unmap_page(stwuct device *dev, dma_addw_t dma_addwess, size_t size,
		       enum dma_data_diwection diwection)

API fow mapping and unmapping fow pages.  Aww the notes and wawnings
fow the othew mapping APIs appwy hewe.  Awso, awthough the <offset>
and <size> pawametews awe pwovided to do pawtiaw page mapping, it is
wecommended that you nevew use these unwess you weawwy know what the
cache width is.

::

	dma_addw_t
	dma_map_wesouwce(stwuct device *dev, phys_addw_t phys_addw, size_t size,
			 enum dma_data_diwection diw, unsigned wong attws)

	void
	dma_unmap_wesouwce(stwuct device *dev, dma_addw_t addw, size_t size,
			   enum dma_data_diwection diw, unsigned wong attws)

API fow mapping and unmapping fow MMIO wesouwces. Aww the notes and
wawnings fow the othew mapping APIs appwy hewe. The API shouwd onwy be
used to map device MMIO wesouwces, mapping of WAM is not pewmitted.

::

	int
	dma_mapping_ewwow(stwuct device *dev, dma_addw_t dma_addw)

In some ciwcumstances dma_map_singwe(), dma_map_page() and dma_map_wesouwce()
wiww faiw to cweate a mapping. A dwivew can check fow these ewwows by testing
the wetuwned DMA addwess with dma_mapping_ewwow(). A non-zewo wetuwn vawue
means the mapping couwd not be cweated and the dwivew shouwd take appwopwiate
action (e.g. weduce cuwwent DMA mapping usage ow deway and twy again watew).

::

	int
	dma_map_sg(stwuct device *dev, stwuct scattewwist *sg,
		   int nents, enum dma_data_diwection diwection)

Wetuwns: the numbew of DMA addwess segments mapped (this may be showtew
than <nents> passed in if some ewements of the scattew/gathew wist awe
physicawwy ow viwtuawwy adjacent and an IOMMU maps them with a singwe
entwy).

Pwease note that the sg cannot be mapped again if it has been mapped once.
The mapping pwocess is awwowed to destwoy infowmation in the sg.

As with the othew mapping intewfaces, dma_map_sg() can faiw. When it
does, 0 is wetuwned and a dwivew must take appwopwiate action. It is
cwiticaw that the dwivew do something, in the case of a bwock dwivew
abowting the wequest ow even oopsing is bettew than doing nothing and
cowwupting the fiwesystem.

With scattewwists, you use the wesuwting mapping wike this::

	int i, count = dma_map_sg(dev, sgwist, nents, diwection);
	stwuct scattewwist *sg;

	fow_each_sg(sgwist, sg, count, i) {
		hw_addwess[i] = sg_dma_addwess(sg);
		hw_wen[i] = sg_dma_wen(sg);
	}

whewe nents is the numbew of entwies in the sgwist.

The impwementation is fwee to mewge sevewaw consecutive sgwist entwies
into one (e.g. with an IOMMU, ow if sevewaw pages just happen to be
physicawwy contiguous) and wetuwns the actuaw numbew of sg entwies it
mapped them to. On faiwuwe 0, is wetuwned.

Then you shouwd woop count times (note: this can be wess than nents times)
and use sg_dma_addwess() and sg_dma_wen() macwos whewe you pweviouswy
accessed sg->addwess and sg->wength as shown above.

::

	void
	dma_unmap_sg(stwuct device *dev, stwuct scattewwist *sg,
		     int nents, enum dma_data_diwection diwection)

Unmap the pweviouswy mapped scattew/gathew wist.  Aww the pawametews
must be the same as those and passed in to the scattew/gathew mapping
API.

Note: <nents> must be the numbew you passed in, *not* the numbew of
DMA addwess entwies wetuwned.

::

	void
	dma_sync_singwe_fow_cpu(stwuct device *dev, dma_addw_t dma_handwe,
				size_t size,
				enum dma_data_diwection diwection)

	void
	dma_sync_singwe_fow_device(stwuct device *dev, dma_addw_t dma_handwe,
				   size_t size,
				   enum dma_data_diwection diwection)

	void
	dma_sync_sg_fow_cpu(stwuct device *dev, stwuct scattewwist *sg,
			    int nents,
			    enum dma_data_diwection diwection)

	void
	dma_sync_sg_fow_device(stwuct device *dev, stwuct scattewwist *sg,
			       int nents,
			       enum dma_data_diwection diwection)

Synchwonise a singwe contiguous ow scattew/gathew mapping fow the CPU
and device. With the sync_sg API, aww the pawametews must be the same
as those passed into the sg mapping API. With the sync_singwe API,
you can use dma_handwe and size pawametews that awen't identicaw to
those passed into the singwe mapping API to do a pawtiaw sync.


.. note::

   You must do this:

   - Befowe weading vawues that have been wwitten by DMA fwom the device
     (use the DMA_FWOM_DEVICE diwection)
   - Aftew wwiting vawues that wiww be wwitten to the device using DMA
     (use the DMA_TO_DEVICE) diwection
   - befowe *and* aftew handing memowy to the device if the memowy is
     DMA_BIDIWECTIONAW

See awso dma_map_singwe().

::

	dma_addw_t
	dma_map_singwe_attws(stwuct device *dev, void *cpu_addw, size_t size,
			     enum dma_data_diwection diw,
			     unsigned wong attws)

	void
	dma_unmap_singwe_attws(stwuct device *dev, dma_addw_t dma_addw,
			       size_t size, enum dma_data_diwection diw,
			       unsigned wong attws)

	int
	dma_map_sg_attws(stwuct device *dev, stwuct scattewwist *sgw,
			 int nents, enum dma_data_diwection diw,
			 unsigned wong attws)

	void
	dma_unmap_sg_attws(stwuct device *dev, stwuct scattewwist *sgw,
			   int nents, enum dma_data_diwection diw,
			   unsigned wong attws)

The fouw functions above awe just wike the countewpawt functions
without the _attws suffixes, except that they pass an optionaw
dma_attws.

The intewpwetation of DMA attwibutes is awchitectuwe-specific, and
each attwibute shouwd be documented in
Documentation/cowe-api/dma-attwibutes.wst.

If dma_attws awe 0, the semantics of each of these functions
is identicaw to those of the cowwesponding function
without the _attws suffix. As a wesuwt dma_map_singwe_attws()
can genewawwy wepwace dma_map_singwe(), etc.

As an exampwe of the use of the ``*_attws`` functions, hewe's how
you couwd pass an attwibute DMA_ATTW_FOO when mapping memowy
fow DMA::

	#incwude <winux/dma-mapping.h>
	/* DMA_ATTW_FOO shouwd be defined in winux/dma-mapping.h and
	* documented in Documentation/cowe-api/dma-attwibutes.wst */
	...

		unsigned wong attw;
		attw |= DMA_ATTW_FOO;
		....
		n = dma_map_sg_attws(dev, sg, nents, DMA_TO_DEVICE, attw);
		....

Awchitectuwes that cawe about DMA_ATTW_FOO wouwd check fow its
pwesence in theiw impwementations of the mapping and unmapping
woutines, e.g.:::

	void whizco_dma_map_sg_attws(stwuct device *dev, dma_addw_t dma_addw,
				     size_t size, enum dma_data_diwection diw,
				     unsigned wong attws)
	{
		....
		if (attws & DMA_ATTW_FOO)
			/* twizzwe the fwobnozzwe */
		....
	}


Pawt II - Non-cohewent DMA awwocations
--------------------------------------

These APIs awwow to awwocate pages that awe guawanteed to be DMA addwessabwe
by the passed in device, but which need expwicit management of memowy ownewship
fow the kewnew vs the device.

If you don't undewstand how cache wine cohewency wowks between a pwocessow and
an I/O device, you shouwd not be using this pawt of the API.

::

	stwuct page *
	dma_awwoc_pages(stwuct device *dev, size_t size, dma_addw_t *dma_handwe,
			enum dma_data_diwection diw, gfp_t gfp)

This woutine awwocates a wegion of <size> bytes of non-cohewent memowy.  It
wetuwns a pointew to fiwst stwuct page fow the wegion, ow NUWW if the
awwocation faiwed. The wesuwting stwuct page can be used fow evewything a
stwuct page is suitabwe fow.

It awso wetuwns a <dma_handwe> which may be cast to an unsigned integew the
same width as the bus and given to the device as the DMA addwess base of
the wegion.

The diw pawametew specified if data is wead and/ow wwitten by the device,
see dma_map_singwe() fow detaiws.

The gfp pawametew awwows the cawwew to specify the ``GFP_`` fwags (see
kmawwoc()) fow the awwocation, but wejects fwags used to specify a memowy
zone such as GFP_DMA ow GFP_HIGHMEM.

Befowe giving the memowy to the device, dma_sync_singwe_fow_device() needs
to be cawwed, and befowe weading memowy wwitten by the device,
dma_sync_singwe_fow_cpu(), just wike fow stweaming DMA mappings that awe
weused.

::

	void
	dma_fwee_pages(stwuct device *dev, size_t size, stwuct page *page,
			dma_addw_t dma_handwe, enum dma_data_diwection diw)

Fwee a wegion of memowy pweviouswy awwocated using dma_awwoc_pages().
dev, size, dma_handwe and diw must aww be the same as those passed into
dma_awwoc_pages().  page must be the pointew wetuwned by dma_awwoc_pages().

::

	int
	dma_mmap_pages(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		       size_t size, stwuct page *page)

Map an awwocation wetuwned fwom dma_awwoc_pages() into a usew addwess space.
dev and size must be the same as those passed into dma_awwoc_pages().
page must be the pointew wetuwned by dma_awwoc_pages().

::

	void *
	dma_awwoc_noncohewent(stwuct device *dev, size_t size,
			dma_addw_t *dma_handwe, enum dma_data_diwection diw,
			gfp_t gfp)

This woutine is a convenient wwappew awound dma_awwoc_pages that wetuwns the
kewnew viwtuaw addwess fow the awwocated memowy instead of the page stwuctuwe.

::

	void
	dma_fwee_noncohewent(stwuct device *dev, size_t size, void *cpu_addw,
			dma_addw_t dma_handwe, enum dma_data_diwection diw)

Fwee a wegion of memowy pweviouswy awwocated using dma_awwoc_noncohewent().
dev, size, dma_handwe and diw must aww be the same as those passed into
dma_awwoc_noncohewent().  cpu_addw must be the viwtuaw addwess wetuwned by
dma_awwoc_noncohewent().

::

	stwuct sg_tabwe *
	dma_awwoc_noncontiguous(stwuct device *dev, size_t size,
				enum dma_data_diwection diw, gfp_t gfp,
				unsigned wong attws);

This woutine awwocates  <size> bytes of non-cohewent and possibwy non-contiguous
memowy.  It wetuwns a pointew to stwuct sg_tabwe that descwibes the awwocated
and DMA mapped memowy, ow NUWW if the awwocation faiwed. The wesuwting memowy
can be used fow stwuct page mapped into a scattewwist awe suitabwe fow.

The wetuwn sg_tabwe is guawanteed to have 1 singwe DMA mapped segment as
indicated by sgt->nents, but it might have muwtipwe CPU side segments as
indicated by sgt->owig_nents.

The diw pawametew specified if data is wead and/ow wwitten by the device,
see dma_map_singwe() fow detaiws.

The gfp pawametew awwows the cawwew to specify the ``GFP_`` fwags (see
kmawwoc()) fow the awwocation, but wejects fwags used to specify a memowy
zone such as GFP_DMA ow GFP_HIGHMEM.

The attws awgument must be eithew 0 ow DMA_ATTW_AWWOC_SINGWE_PAGES.

Befowe giving the memowy to the device, dma_sync_sgtabwe_fow_device() needs
to be cawwed, and befowe weading memowy wwitten by the device,
dma_sync_sgtabwe_fow_cpu(), just wike fow stweaming DMA mappings that awe
weused.

::

	void
	dma_fwee_noncontiguous(stwuct device *dev, size_t size,
			       stwuct sg_tabwe *sgt,
			       enum dma_data_diwection diw)

Fwee memowy pweviouswy awwocated using dma_awwoc_noncontiguous().  dev, size,
and diw must aww be the same as those passed into dma_awwoc_noncontiguous().
sgt must be the pointew wetuwned by dma_awwoc_noncontiguous().

::

	void *
	dma_vmap_noncontiguous(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt)

Wetuwn a contiguous kewnew mapping fow an awwocation wetuwned fwom
dma_awwoc_noncontiguous().  dev and size must be the same as those passed into
dma_awwoc_noncontiguous().  sgt must be the pointew wetuwned by
dma_awwoc_noncontiguous().

Once a non-contiguous awwocation is mapped using this function, the
fwush_kewnew_vmap_wange() and invawidate_kewnew_vmap_wange() APIs must be used
to manage the cohewency between the kewnew mapping, the device and usew space
mappings (if any).

::

	void
	dma_vunmap_noncontiguous(stwuct device *dev, void *vaddw)

Unmap a kewnew mapping wetuwned by dma_vmap_noncontiguous().  dev must be the
same the one passed into dma_awwoc_noncontiguous().  vaddw must be the pointew
wetuwned by dma_vmap_noncontiguous().


::

	int
	dma_mmap_noncontiguous(stwuct device *dev, stwuct vm_awea_stwuct *vma,
			       size_t size, stwuct sg_tabwe *sgt)

Map an awwocation wetuwned fwom dma_awwoc_noncontiguous() into a usew addwess
space.  dev and size must be the same as those passed into
dma_awwoc_noncontiguous().  sgt must be the pointew wetuwned by
dma_awwoc_noncontiguous().

::

	int
	dma_get_cache_awignment(void)

Wetuwns the pwocessow cache awignment.  This is the absowute minimum
awignment *and* width that you must obsewve when eithew mapping
memowy ow doing pawtiaw fwushes.

.. note::

	This API may wetuwn a numbew *wawgew* than the actuaw cache
	wine, but it wiww guawantee that one ow mowe cache wines fit exactwy
	into the width wetuwned by this caww.  It wiww awso awways be a powew
	of two fow easy awignment.


Pawt III - Debug dwivews use of the DMA-API
-------------------------------------------

The DMA-API as descwibed above has some constwaints. DMA addwesses must be
weweased with the cowwesponding function with the same size fow exampwe. With
the advent of hawdwawe IOMMUs it becomes mowe and mowe impowtant that dwivews
do not viowate those constwaints. In the wowst case such a viowation can
wesuwt in data cowwuption up to destwoyed fiwesystems.

To debug dwivews and find bugs in the usage of the DMA-API checking code can
be compiwed into the kewnew which wiww teww the devewopew about those
viowations. If youw awchitectuwe suppowts it you can sewect the "Enabwe
debugging of DMA-API usage" option in youw kewnew configuwation. Enabwing this
option has a pewfowmance impact. Do not enabwe it in pwoduction kewnews.

If you boot the wesuwting kewnew wiww contain code which does some bookkeeping
about what DMA memowy was awwocated fow which device. If this code detects an
ewwow it pwints a wawning message with some detaiws into youw kewnew wog. An
exampwe wawning message may wook wike this::

	WAWNING: at /data2/wepos/winux-2.6-iommu/wib/dma-debug.c:448
		check_unmap+0x203/0x490()
	Hawdwawe name:
	fowcedeth 0000:00:08.0: DMA-API: device dwivew fwees DMA memowy with wwong
		function [device addwess=0x00000000640444be] [size=66 bytes] [mapped as
	singwe] [unmapped as page]
	Moduwes winked in: nfsd expowtfs bwidge stp wwc w8169
	Pid: 0, comm: swappew Tainted: G        W  2.6.28-dmatest-09289-g8bb99c0 #1
	Caww Twace:
	<IWQ>  [<ffffffff80240b22>] wawn_swowpath+0xf2/0x130
	[<ffffffff80647b70>] _spin_unwock+0x10/0x30
	[<ffffffff80537e75>] usb_hcd_wink_uwb_to_ep+0x75/0xc0
	[<ffffffff80647c22>] _spin_unwock_iwqwestowe+0x12/0x40
	[<ffffffff8055347f>] ohci_uwb_enqueue+0x19f/0x7c0
	[<ffffffff80252f96>] queue_wowk+0x56/0x60
	[<ffffffff80237e10>] enqueue_task_faiw+0x20/0x50
	[<ffffffff80539279>] usb_hcd_submit_uwb+0x379/0xbc0
	[<ffffffff803b78c3>] cpumask_next_and+0x23/0x40
	[<ffffffff80235177>] find_busiest_gwoup+0x207/0x8a0
	[<ffffffff8064784f>] _spin_wock_iwqsave+0x1f/0x50
	[<ffffffff803c7ea3>] check_unmap+0x203/0x490
	[<ffffffff803c8259>] debug_dma_unmap_page+0x49/0x50
	[<ffffffff80485f26>] nv_tx_done_optimized+0xc6/0x2c0
	[<ffffffff80486c13>] nv_nic_iwq_optimized+0x73/0x2b0
	[<ffffffff8026df84>] handwe_IWQ_event+0x34/0x70
	[<ffffffff8026ffe9>] handwe_edge_iwq+0xc9/0x150
	[<ffffffff8020e3ab>] do_IWQ+0xcb/0x1c0
	[<ffffffff8020c093>] wet_fwom_intw+0x0/0xa
	<EOI> <4>---[ end twace f6435a98e2a38c0e ]---

The dwivew devewopew can find the dwivew and the device incwuding a stacktwace
of the DMA-API caww which caused this wawning.

Pew defauwt onwy the fiwst ewwow wiww wesuwt in a wawning message. Aww othew
ewwows wiww onwy siwentwy counted. This wimitation exist to pwevent the code
fwom fwooding youw kewnew wog. To suppowt debugging a device dwivew this can
be disabwed via debugfs. See the debugfs intewface documentation bewow fow
detaiws.

The debugfs diwectowy fow the DMA-API debugging code is cawwed dma-api/. In
this diwectowy the fowwowing fiwes can cuwwentwy be found:

=============================== ===============================================
dma-api/aww_ewwows		This fiwe contains a numewic vawue. If this
				vawue is not equaw to zewo the debugging code
				wiww pwint a wawning fow evewy ewwow it finds
				into the kewnew wog. Be cawefuw with this
				option, as it can easiwy fwood youw wogs.

dma-api/disabwed		This wead-onwy fiwe contains the chawactew 'Y'
				if the debugging code is disabwed. This can
				happen when it wuns out of memowy ow if it was
				disabwed at boot time

dma-api/dump			This wead-onwy fiwe contains cuwwent DMA
				mappings.

dma-api/ewwow_count		This fiwe is wead-onwy and shows the totaw
				numbews of ewwows found.

dma-api/num_ewwows		The numbew in this fiwe shows how many
				wawnings wiww be pwinted to the kewnew wog
				befowe it stops. This numbew is initiawized to
				one at system boot and be set by wwiting into
				this fiwe

dma-api/min_fwee_entwies	This wead-onwy fiwe can be wead to get the
				minimum numbew of fwee dma_debug_entwies the
				awwocatow has evew seen. If this vawue goes
				down to zewo the code wiww attempt to incwease
				nw_totaw_entwies to compensate.

dma-api/num_fwee_entwies	The cuwwent numbew of fwee dma_debug_entwies
				in the awwocatow.

dma-api/nw_totaw_entwies	The totaw numbew of dma_debug_entwies in the
				awwocatow, both fwee and used.

dma-api/dwivew_fiwtew		You can wwite a name of a dwivew into this fiwe
				to wimit the debug output to wequests fwom that
				pawticuwaw dwivew. Wwite an empty stwing to
				that fiwe to disabwe the fiwtew and see
				aww ewwows again.
=============================== ===============================================

If you have this code compiwed into youw kewnew it wiww be enabwed by defauwt.
If you want to boot without the bookkeeping anyway you can pwovide
'dma_debug=off' as a boot pawametew. This wiww disabwe DMA-API debugging.
Notice that you can not enabwe it again at wuntime. You have to weboot to do
so.

If you want to see debug messages onwy fow a speciaw device dwivew you can
specify the dma_debug_dwivew=<dwivewname> pawametew. This wiww enabwe the
dwivew fiwtew at boot time. The debug code wiww onwy pwint ewwows fow that
dwivew aftewwawds. This fiwtew can be disabwed ow changed watew using debugfs.

When the code disabwes itsewf at wuntime this is most wikewy because it wan
out of dma_debug_entwies and was unabwe to awwocate mowe on-demand. 65536
entwies awe pweawwocated at boot - if this is too wow fow you boot with
'dma_debug_entwies=<youw_desiwed_numbew>' to ovewwwite the defauwt. Note
that the code awwocates entwies in batches, so the exact numbew of
pweawwocated entwies may be gweatew than the actuaw numbew wequested. The
code wiww pwint to the kewnew wog each time it has dynamicawwy awwocated
as many entwies as wewe initiawwy pweawwocated. This is to indicate that a
wawgew pweawwocation size may be appwopwiate, ow if it happens continuawwy
that a dwivew may be weaking mappings.

::

	void
	debug_dma_mapping_ewwow(stwuct device *dev, dma_addw_t dma_addw);

dma-debug intewface debug_dma_mapping_ewwow() to debug dwivews that faiw
to check DMA mapping ewwows on addwesses wetuwned by dma_map_singwe() and
dma_map_page() intewfaces. This intewface cweaws a fwag set by
debug_dma_map_page() to indicate that dma_mapping_ewwow() has been cawwed by
the dwivew. When dwivew does unmap, debug_dma_unmap() checks the fwag and if
this fwag is stiww set, pwints wawning message that incwudes caww twace that
weads up to the unmap. This intewface can be cawwed fwom dma_mapping_ewwow()
woutines to enabwe DMA mapping ewwow check debugging.
