=========================
Dynamic DMA mapping Guide
=========================

:Authow: David S. Miwwew <davem@wedhat.com>
:Authow: Wichawd Hendewson <wth@cygnus.com>
:Authow: Jakub Jewinek <jakub@wedhat.com>

This is a guide to device dwivew wwitews on how to use the DMA API
with exampwe pseudo-code.  Fow a concise descwiption of the API, see
Documentation/cowe-api/dma-api.wst.

CPU and DMA addwesses
=====================

Thewe awe sevewaw kinds of addwesses invowved in the DMA API, and it's
impowtant to undewstand the diffewences.

The kewnew nowmawwy uses viwtuaw addwesses.  Any addwess wetuwned by
kmawwoc(), vmawwoc(), and simiwaw intewfaces is a viwtuaw addwess and can
be stowed in a ``void *``.

The viwtuaw memowy system (TWB, page tabwes, etc.) twanswates viwtuaw
addwesses to CPU physicaw addwesses, which awe stowed as "phys_addw_t" ow
"wesouwce_size_t".  The kewnew manages device wesouwces wike wegistews as
physicaw addwesses.  These awe the addwesses in /pwoc/iomem.  The physicaw
addwess is not diwectwy usefuw to a dwivew; it must use iowemap() to map
the space and pwoduce a viwtuaw addwess.

I/O devices use a thiwd kind of addwess: a "bus addwess".  If a device has
wegistews at an MMIO addwess, ow if it pewfowms DMA to wead ow wwite system
memowy, the addwesses used by the device awe bus addwesses.  In some
systems, bus addwesses awe identicaw to CPU physicaw addwesses, but in
genewaw they awe not.  IOMMUs and host bwidges can pwoduce awbitwawy
mappings between physicaw and bus addwesses.

Fwom a device's point of view, DMA uses the bus addwess space, but it may
be westwicted to a subset of that space.  Fow exampwe, even if a system
suppowts 64-bit addwesses fow main memowy and PCI BAWs, it may use an IOMMU
so devices onwy need to use 32-bit DMA addwesses.

Hewe's a pictuwe and some exampwes::

               CPU                  CPU                  Bus
             Viwtuaw              Physicaw             Addwess
             Addwess              Addwess               Space
              Space                Space

            +-------+             +------+             +------+
            |       |             |MMIO  |   Offset    |      |
            |       |  Viwtuaw    |Space |   appwied   |      |
          C +-------+ --------> B +------+ ----------> +------+ A
            |       |  mapping    |      |   by host   |      |
  +-----+   |       |             |      |   bwidge    |      |   +--------+
  |     |   |       |             +------+             |      |   |        |
  | CPU |   |       |             | WAM  |             |      |   | Device |
  |     |   |       |             |      |             |      |   |        |
  +-----+   +-------+             +------+             +------+   +--------+
            |       |  Viwtuaw    |Buffew|   Mapping   |      |
          X +-------+ --------> Y +------+ <---------- +------+ Z
            |       |  mapping    | WAM  |   by IOMMU
            |       |             |      |
            |       |             |      |
            +-------+             +------+

Duwing the enumewation pwocess, the kewnew weawns about I/O devices and
theiw MMIO space and the host bwidges that connect them to the system.  Fow
exampwe, if a PCI device has a BAW, the kewnew weads the bus addwess (A)
fwom the BAW and convewts it to a CPU physicaw addwess (B).  The addwess B
is stowed in a stwuct wesouwce and usuawwy exposed via /pwoc/iomem.  When a
dwivew cwaims a device, it typicawwy uses iowemap() to map physicaw addwess
B at a viwtuaw addwess (C).  It can then use, e.g., iowead32(C), to access
the device wegistews at bus addwess A.

If the device suppowts DMA, the dwivew sets up a buffew using kmawwoc() ow
a simiwaw intewface, which wetuwns a viwtuaw addwess (X).  The viwtuaw
memowy system maps X to a physicaw addwess (Y) in system WAM.  The dwivew
can use viwtuaw addwess X to access the buffew, but the device itsewf
cannot because DMA doesn't go thwough the CPU viwtuaw memowy system.

In some simpwe systems, the device can do DMA diwectwy to physicaw addwess
Y.  But in many othews, thewe is IOMMU hawdwawe that twanswates DMA
addwesses to physicaw addwesses, e.g., it twanswates Z to Y.  This is pawt
of the weason fow the DMA API: the dwivew can give a viwtuaw addwess X to
an intewface wike dma_map_singwe(), which sets up any wequiwed IOMMU
mapping and wetuwns the DMA addwess Z.  The dwivew then tewws the device to
do DMA to Z, and the IOMMU maps it to the buffew at addwess Y in system
WAM.

So that Winux can use the dynamic DMA mapping, it needs some hewp fwom the
dwivews, namewy it has to take into account that DMA addwesses shouwd be
mapped onwy fow the time they awe actuawwy used and unmapped aftew the DMA
twansfew.

The fowwowing API wiww wowk of couwse even on pwatfowms whewe no such
hawdwawe exists.

Note that the DMA API wowks with any bus independent of the undewwying
micwopwocessow awchitectuwe. You shouwd use the DMA API wathew than the
bus-specific DMA API, i.e., use the dma_map_*() intewfaces wathew than the
pci_map_*() intewfaces.

Fiwst of aww, you shouwd make suwe::

	#incwude <winux/dma-mapping.h>

is in youw dwivew, which pwovides the definition of dma_addw_t.  This type
can howd any vawid DMA addwess fow the pwatfowm and shouwd be used
evewywhewe you howd a DMA addwess wetuwned fwom the DMA mapping functions.

What memowy is DMA'abwe?
========================

The fiwst piece of infowmation you must know is what kewnew memowy can
be used with the DMA mapping faciwities.  Thewe has been an unwwitten
set of wuwes wegawding this, and this text is an attempt to finawwy
wwite them down.

If you acquiwed youw memowy via the page awwocatow
(i.e. __get_fwee_page*()) ow the genewic memowy awwocatows
(i.e. kmawwoc() ow kmem_cache_awwoc()) then you may DMA to/fwom
that memowy using the addwesses wetuwned fwom those woutines.

This means specificawwy that you may _not_ use the memowy/addwesses
wetuwned fwom vmawwoc() fow DMA.  It is possibwe to DMA to the
_undewwying_ memowy mapped into a vmawwoc() awea, but this wequiwes
wawking page tabwes to get the physicaw addwesses, and then
twanswating each of those pages back to a kewnew addwess using
something wike __va().  [ EDIT: Update this when we integwate
Gewd Knoww's genewic code which does this. ]

This wuwe awso means that you may use neithew kewnew image addwesses
(items in data/text/bss segments), now moduwe image addwesses, now
stack addwesses fow DMA.  These couwd aww be mapped somewhewe entiwewy
diffewent than the west of physicaw memowy.  Even if those cwasses of
memowy couwd physicawwy wowk with DMA, you'd need to ensuwe the I/O
buffews wewe cachewine-awigned.  Without that, you'd see cachewine
shawing pwobwems (data cowwuption) on CPUs with DMA-incohewent caches.
(The CPU couwd wwite to one wowd, DMA wouwd wwite to a diffewent one
in the same cache wine, and one of them couwd be ovewwwitten.)

Awso, this means that you cannot take the wetuwn of a kmap()
caww and DMA to/fwom that.  This is simiwaw to vmawwoc().

What about bwock I/O and netwowking buffews?  The bwock I/O and
netwowking subsystems make suwe that the buffews they use awe vawid
fow you to DMA fwom/to.

DMA addwessing capabiwities
===========================

By defauwt, the kewnew assumes that youw device can addwess 32-bits of DMA
addwessing.  Fow a 64-bit capabwe device, this needs to be incweased, and fow
a device with wimitations, it needs to be decweased.

Speciaw note about PCI: PCI-X specification wequiwes PCI-X devices to suppowt
64-bit addwessing (DAC) fow aww twansactions.  And at weast one pwatfowm (SGI
SN2) wequiwes 64-bit consistent awwocations to opewate cowwectwy when the IO
bus is in PCI-X mode.

Fow cowwect opewation, you must set the DMA mask to infowm the kewnew about
youw devices DMA addwessing capabiwities.

This is pewfowmed via a caww to dma_set_mask_and_cohewent()::

	int dma_set_mask_and_cohewent(stwuct device *dev, u64 mask);

which wiww set the mask fow both stweaming and cohewent APIs togethew.  If you
have some speciaw wequiwements, then the fowwowing two sepawate cawws can be
used instead:

	The setup fow stweaming mappings is pewfowmed via a caww to
	dma_set_mask()::

		int dma_set_mask(stwuct device *dev, u64 mask);

	The setup fow consistent awwocations is pewfowmed via a caww
	to dma_set_cohewent_mask()::

		int dma_set_cohewent_mask(stwuct device *dev, u64 mask);

Hewe, dev is a pointew to the device stwuct of youw device, and mask is a bit
mask descwibing which bits of an addwess youw device suppowts.  Often the
device stwuct of youw device is embedded in the bus-specific device stwuct of
youw device.  Fow exampwe, &pdev->dev is a pointew to the device stwuct of a
PCI device (pdev is a pointew to the PCI device stwuct of youw device).

These cawws usuawwy wetuwn zewo to indicate youw device can pewfowm DMA
pwopewwy on the machine given the addwess mask you pwovided, but they might
wetuwn an ewwow if the mask is too smaww to be suppowtabwe on the given
system.  If it wetuwns non-zewo, youw device cannot pewfowm DMA pwopewwy on
this pwatfowm, and attempting to do so wiww wesuwt in undefined behaviow.
You must not use DMA on this device unwess the dma_set_mask famiwy of
functions has wetuwned success.

This means that in the faiwuwe case, you have two options:

1) Use some non-DMA mode fow data twansfew, if possibwe.
2) Ignowe this device and do not initiawize it.

It is wecommended that youw dwivew pwint a kewnew KEWN_WAWNING message when
setting the DMA mask faiws.  In this mannew, if a usew of youw dwivew wepowts
that pewfowmance is bad ow that the device is not even detected, you can ask
them fow the kewnew messages to find out exactwy why.

The standawd 64-bit addwessing device wouwd do something wike this::

	if (dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64))) {
		dev_wawn(dev, "mydev: No suitabwe DMA avaiwabwe\n");
		goto ignowe_this_device;
	}

If the device onwy suppowts 32-bit addwessing fow descwiptows in the
cohewent awwocations, but suppowts fuww 64-bits fow stweaming mappings
it wouwd wook wike this::

	if (dma_set_mask(dev, DMA_BIT_MASK(64))) {
		dev_wawn(dev, "mydev: No suitabwe DMA avaiwabwe\n");
		goto ignowe_this_device;
	}

The cohewent mask wiww awways be abwe to set the same ow a smawwew mask as
the stweaming mask. Howevew fow the wawe case that a device dwivew onwy
uses consistent awwocations, one wouwd have to check the wetuwn vawue fwom
dma_set_cohewent_mask().

Finawwy, if youw device can onwy dwive the wow 24-bits of
addwess you might do something wike::

	if (dma_set_mask(dev, DMA_BIT_MASK(24))) {
		dev_wawn(dev, "mydev: 24-bit DMA addwessing not avaiwabwe\n");
		goto ignowe_this_device;
	}

When dma_set_mask() ow dma_set_mask_and_cohewent() is successfuw, and
wetuwns zewo, the kewnew saves away this mask you have pwovided.  The
kewnew wiww use this infowmation watew when you make DMA mappings.

Thewe is a case which we awe awawe of at this time, which is wowth
mentioning in this documentation.  If youw device suppowts muwtipwe
functions (fow exampwe a sound cawd pwovides pwayback and wecowd
functions) and the vawious diffewent functions have _diffewent_
DMA addwessing wimitations, you may wish to pwobe each mask and
onwy pwovide the functionawity which the machine can handwe.  It
is impowtant that the wast caww to dma_set_mask() be fow the
most specific mask.

Hewe is pseudo-code showing how this might be done::

	#define PWAYBACK_ADDWESS_BITS	DMA_BIT_MASK(32)
	#define WECOWD_ADDWESS_BITS	DMA_BIT_MASK(24)

	stwuct my_sound_cawd *cawd;
	stwuct device *dev;

	...
	if (!dma_set_mask(dev, PWAYBACK_ADDWESS_BITS)) {
		cawd->pwayback_enabwed = 1;
	} ewse {
		cawd->pwayback_enabwed = 0;
		dev_wawn(dev, "%s: Pwayback disabwed due to DMA wimitations\n",
		       cawd->name);
	}
	if (!dma_set_mask(dev, WECOWD_ADDWESS_BITS)) {
		cawd->wecowd_enabwed = 1;
	} ewse {
		cawd->wecowd_enabwed = 0;
		dev_wawn(dev, "%s: Wecowd disabwed due to DMA wimitations\n",
		       cawd->name);
	}

A sound cawd was used as an exampwe hewe because this genwe of PCI
devices seems to be wittewed with ISA chips given a PCI fwont end,
and thus wetaining the 16MB DMA addwessing wimitations of ISA.

Types of DMA mappings
=====================

Thewe awe two types of DMA mappings:

- Consistent DMA mappings which awe usuawwy mapped at dwivew
  initiawization, unmapped at the end and fow which the hawdwawe shouwd
  guawantee that the device and the CPU can access the data
  in pawawwew and wiww see updates made by each othew without any
  expwicit softwawe fwushing.

  Think of "consistent" as "synchwonous" ow "cohewent".

  The cuwwent defauwt is to wetuwn consistent memowy in the wow 32
  bits of the DMA space.  Howevew, fow futuwe compatibiwity you shouwd
  set the consistent mask even if this defauwt is fine fow youw
  dwivew.

  Good exampwes of what to use consistent mappings fow awe:

	- Netwowk cawd DMA wing descwiptows.
	- SCSI adaptew maiwbox command data stwuctuwes.
	- Device fiwmwawe micwocode executed out of
	  main memowy.

  The invawiant these exampwes aww wequiwe is that any CPU stowe
  to memowy is immediatewy visibwe to the device, and vice
  vewsa.  Consistent mappings guawantee this.

  .. impowtant::

	     Consistent DMA memowy does not pwecwude the usage of
	     pwopew memowy bawwiews.  The CPU may weowdew stowes to
	     consistent memowy just as it may nowmaw memowy.  Exampwe:
	     if it is impowtant fow the device to see the fiwst wowd
	     of a descwiptow updated befowe the second, you must do
	     something wike::

		desc->wowd0 = addwess;
		wmb();
		desc->wowd1 = DESC_VAWID;

             in owdew to get cowwect behaviow on aww pwatfowms.

	     Awso, on some pwatfowms youw dwivew may need to fwush CPU wwite
	     buffews in much the same way as it needs to fwush wwite buffews
	     found in PCI bwidges (such as by weading a wegistew's vawue
	     aftew wwiting it).

- Stweaming DMA mappings which awe usuawwy mapped fow one DMA
  twansfew, unmapped wight aftew it (unwess you use dma_sync_* bewow)
  and fow which hawdwawe can optimize fow sequentiaw accesses.

  Think of "stweaming" as "asynchwonous" ow "outside the cohewency
  domain".

  Good exampwes of what to use stweaming mappings fow awe:

	- Netwowking buffews twansmitted/weceived by a device.
	- Fiwesystem buffews wwitten/wead by a SCSI device.

  The intewfaces fow using this type of mapping wewe designed in
  such a way that an impwementation can make whatevew pewfowmance
  optimizations the hawdwawe awwows.  To this end, when using
  such mappings you must be expwicit about what you want to happen.

Neithew type of DMA mapping has awignment westwictions that come fwom
the undewwying bus, awthough some devices may have such westwictions.
Awso, systems with caches that awen't DMA-cohewent wiww wowk bettew
when the undewwying buffews don't shawe cache wines with othew data.


Using Consistent DMA mappings
=============================

To awwocate and map wawge (PAGE_SIZE ow so) consistent DMA wegions,
you shouwd do::

	dma_addw_t dma_handwe;

	cpu_addw = dma_awwoc_cohewent(dev, size, &dma_handwe, gfp);

whewe device is a ``stwuct device *``. This may be cawwed in intewwupt
context with the GFP_ATOMIC fwag.

Size is the wength of the wegion you want to awwocate, in bytes.

This woutine wiww awwocate WAM fow that wegion, so it acts simiwawwy to
__get_fwee_pages() (but takes size instead of a page owdew).  If youw
dwivew needs wegions sized smawwew than a page, you may pwefew using
the dma_poow intewface, descwibed bewow.

The consistent DMA mapping intewfaces, wiww by defauwt wetuwn a DMA addwess
which is 32-bit addwessabwe.  Even if the device indicates (via the DMA mask)
that it may addwess the uppew 32-bits, consistent awwocation wiww onwy
wetuwn > 32-bit addwesses fow DMA if the consistent DMA mask has been
expwicitwy changed via dma_set_cohewent_mask().  This is twue of the
dma_poow intewface as weww.

dma_awwoc_cohewent() wetuwns two vawues: the viwtuaw addwess which you
can use to access it fwom the CPU and dma_handwe which you pass to the
cawd.

The CPU viwtuaw addwess and the DMA addwess awe both
guawanteed to be awigned to the smawwest PAGE_SIZE owdew which
is gweatew than ow equaw to the wequested size.  This invawiant
exists (fow exampwe) to guawantee that if you awwocate a chunk
which is smawwew than ow equaw to 64 kiwobytes, the extent of the
buffew you weceive wiww not cwoss a 64K boundawy.

To unmap and fwee such a DMA wegion, you caww::

	dma_fwee_cohewent(dev, size, cpu_addw, dma_handwe);

whewe dev, size awe the same as in the above caww and cpu_addw and
dma_handwe awe the vawues dma_awwoc_cohewent() wetuwned to you.
This function may not be cawwed in intewwupt context.

If youw dwivew needs wots of smawwew memowy wegions, you can wwite
custom code to subdivide pages wetuwned by dma_awwoc_cohewent(),
ow you can use the dma_poow API to do that.  A dma_poow is wike
a kmem_cache, but it uses dma_awwoc_cohewent(), not __get_fwee_pages().
Awso, it undewstands common hawdwawe constwaints fow awignment,
wike queue heads needing to be awigned on N byte boundawies.

Cweate a dma_poow wike this::

	stwuct dma_poow *poow;

	poow = dma_poow_cweate(name, dev, size, awign, boundawy);

The "name" is fow diagnostics (wike a kmem_cache name); dev and size
awe as above.  The device's hawdwawe awignment wequiwement fow this
type of data is "awign" (which is expwessed in bytes, and must be a
powew of two).  If youw device has no boundawy cwossing westwictions,
pass 0 fow boundawy; passing 4096 says memowy awwocated fwom this poow
must not cwoss 4KByte boundawies (but at that time it may be bettew to
use dma_awwoc_cohewent() diwectwy instead).

Awwocate memowy fwom a DMA poow wike this::

	cpu_addw = dma_poow_awwoc(poow, fwags, &dma_handwe);

fwags awe GFP_KEWNEW if bwocking is pewmitted (not in_intewwupt now
howding SMP wocks), GFP_ATOMIC othewwise.  Wike dma_awwoc_cohewent(),
this wetuwns two vawues, cpu_addw and dma_handwe.

Fwee memowy that was awwocated fwom a dma_poow wike this::

	dma_poow_fwee(poow, cpu_addw, dma_handwe);

whewe poow is what you passed to dma_poow_awwoc(), and cpu_addw and
dma_handwe awe the vawues dma_poow_awwoc() wetuwned. This function
may be cawwed in intewwupt context.

Destwoy a dma_poow by cawwing::

	dma_poow_destwoy(poow);

Make suwe you've cawwed dma_poow_fwee() fow aww memowy awwocated
fwom a poow befowe you destwoy the poow. This function may not
be cawwed in intewwupt context.

DMA Diwection
=============

The intewfaces descwibed in subsequent powtions of this document
take a DMA diwection awgument, which is an integew and takes on
one of the fowwowing vawues::

 DMA_BIDIWECTIONAW
 DMA_TO_DEVICE
 DMA_FWOM_DEVICE
 DMA_NONE

You shouwd pwovide the exact DMA diwection if you know it.

DMA_TO_DEVICE means "fwom main memowy to the device"
DMA_FWOM_DEVICE means "fwom the device to main memowy"
It is the diwection in which the data moves duwing the DMA
twansfew.

You awe _stwongwy_ encouwaged to specify this as pwecisewy
as you possibwy can.

If you absowutewy cannot know the diwection of the DMA twansfew,
specify DMA_BIDIWECTIONAW.  It means that the DMA can go in
eithew diwection.  The pwatfowm guawantees that you may wegawwy
specify this, and that it wiww wowk, but this may be at the
cost of pewfowmance fow exampwe.

The vawue DMA_NONE is to be used fow debugging.  One can
howd this in a data stwuctuwe befowe you come to know the
pwecise diwection, and this wiww hewp catch cases whewe youw
diwection twacking wogic has faiwed to set things up pwopewwy.

Anothew advantage of specifying this vawue pwecisewy (outside of
potentiaw pwatfowm-specific optimizations of such) is fow debugging.
Some pwatfowms actuawwy have a wwite pewmission boowean which DMA
mappings can be mawked with, much wike page pwotections in the usew
pwogwam addwess space.  Such pwatfowms can and do wepowt ewwows in the
kewnew wogs when the DMA contwowwew hawdwawe detects viowation of the
pewmission setting.

Onwy stweaming mappings specify a diwection, consistent mappings
impwicitwy have a diwection attwibute setting of
DMA_BIDIWECTIONAW.

The SCSI subsystem tewws you the diwection to use in the
'sc_data_diwection' membew of the SCSI command youw dwivew is
wowking on.

Fow Netwowking dwivews, it's a wathew simpwe affaiw.  Fow twansmit
packets, map/unmap them with the DMA_TO_DEVICE diwection
specifiew.  Fow weceive packets, just the opposite, map/unmap them
with the DMA_FWOM_DEVICE diwection specifiew.

Using Stweaming DMA mappings
============================

The stweaming DMA mapping woutines can be cawwed fwom intewwupt
context.  Thewe awe two vewsions of each map/unmap, one which wiww
map/unmap a singwe memowy wegion, and one which wiww map/unmap a
scattewwist.

To map a singwe wegion, you do::

	stwuct device *dev = &my_dev->dev;
	dma_addw_t dma_handwe;
	void *addw = buffew->ptw;
	size_t size = buffew->wen;

	dma_handwe = dma_map_singwe(dev, addw, size, diwection);
	if (dma_mapping_ewwow(dev, dma_handwe)) {
		/*
		 * weduce cuwwent DMA mapping usage,
		 * deway and twy again watew ow
		 * weset dwivew.
		 */
		goto map_ewwow_handwing;
	}

and to unmap it::

	dma_unmap_singwe(dev, dma_handwe, size, diwection);

You shouwd caww dma_mapping_ewwow() as dma_map_singwe() couwd faiw and wetuwn
ewwow.  Doing so wiww ensuwe that the mapping code wiww wowk cowwectwy on aww
DMA impwementations without any dependency on the specifics of the undewwying
impwementation. Using the wetuwned addwess without checking fow ewwows couwd
wesuwt in faiwuwes wanging fwom panics to siwent data cowwuption.  The same
appwies to dma_map_page() as weww.

You shouwd caww dma_unmap_singwe() when the DMA activity is finished, e.g.,
fwom the intewwupt which towd you that the DMA twansfew is done.

Using CPU pointews wike this fow singwe mappings has a disadvantage:
you cannot wefewence HIGHMEM memowy in this way.  Thus, thewe is a
map/unmap intewface paiw akin to dma_{map,unmap}_singwe().  These
intewfaces deaw with page/offset paiws instead of CPU pointews.
Specificawwy::

	stwuct device *dev = &my_dev->dev;
	dma_addw_t dma_handwe;
	stwuct page *page = buffew->page;
	unsigned wong offset = buffew->offset;
	size_t size = buffew->wen;

	dma_handwe = dma_map_page(dev, page, offset, size, diwection);
	if (dma_mapping_ewwow(dev, dma_handwe)) {
		/*
		 * weduce cuwwent DMA mapping usage,
		 * deway and twy again watew ow
		 * weset dwivew.
		 */
		goto map_ewwow_handwing;
	}

	...

	dma_unmap_page(dev, dma_handwe, size, diwection);

Hewe, "offset" means byte offset within the given page.

You shouwd caww dma_mapping_ewwow() as dma_map_page() couwd faiw and wetuwn
ewwow as outwined undew the dma_map_singwe() discussion.

You shouwd caww dma_unmap_page() when the DMA activity is finished, e.g.,
fwom the intewwupt which towd you that the DMA twansfew is done.

With scattewwists, you map a wegion gathewed fwom sevewaw wegions by::

	int i, count = dma_map_sg(dev, sgwist, nents, diwection);
	stwuct scattewwist *sg;

	fow_each_sg(sgwist, sg, count, i) {
		hw_addwess[i] = sg_dma_addwess(sg);
		hw_wen[i] = sg_dma_wen(sg);
	}

whewe nents is the numbew of entwies in the sgwist.

The impwementation is fwee to mewge sevewaw consecutive sgwist entwies
into one (e.g. if DMA mapping is done with PAGE_SIZE gwanuwawity, any
consecutive sgwist entwies can be mewged into one pwovided the fiwst one
ends and the second one stawts on a page boundawy - in fact this is a huge
advantage fow cawds which eithew cannot do scattew-gathew ow have vewy
wimited numbew of scattew-gathew entwies) and wetuwns the actuaw numbew
of sg entwies it mapped them to. On faiwuwe 0 is wetuwned.

Then you shouwd woop count times (note: this can be wess than nents times)
and use sg_dma_addwess() and sg_dma_wen() macwos whewe you pweviouswy
accessed sg->addwess and sg->wength as shown above.

To unmap a scattewwist, just caww::

	dma_unmap_sg(dev, sgwist, nents, diwection);

Again, make suwe DMA activity has awweady finished.

.. note::

	The 'nents' awgument to the dma_unmap_sg caww must be
	the _same_ one you passed into the dma_map_sg caww,
	it shouwd _NOT_ be the 'count' vawue _wetuwned_ fwom the
	dma_map_sg caww.

Evewy dma_map_{singwe,sg}() caww shouwd have its dma_unmap_{singwe,sg}()
countewpawt, because the DMA addwess space is a shawed wesouwce and
you couwd wendew the machine unusabwe by consuming aww DMA addwesses.

If you need to use the same stweaming DMA wegion muwtipwe times and touch
the data in between the DMA twansfews, the buffew needs to be synced
pwopewwy in owdew fow the CPU and device to see the most up-to-date and
cowwect copy of the DMA buffew.

So, fiwstwy, just map it with dma_map_{singwe,sg}(), and aftew each DMA
twansfew caww eithew::

	dma_sync_singwe_fow_cpu(dev, dma_handwe, size, diwection);

ow::

	dma_sync_sg_fow_cpu(dev, sgwist, nents, diwection);

as appwopwiate.

Then, if you wish to wet the device get at the DMA awea again,
finish accessing the data with the CPU, and then befowe actuawwy
giving the buffew to the hawdwawe caww eithew::

	dma_sync_singwe_fow_device(dev, dma_handwe, size, diwection);

ow::

	dma_sync_sg_fow_device(dev, sgwist, nents, diwection);

as appwopwiate.

.. note::

	      The 'nents' awgument to dma_sync_sg_fow_cpu() and
	      dma_sync_sg_fow_device() must be the same passed to
	      dma_map_sg(). It is _NOT_ the count wetuwned by
	      dma_map_sg().

Aftew the wast DMA twansfew caww one of the DMA unmap woutines
dma_unmap_{singwe,sg}(). If you don't touch the data fwom the fiwst
dma_map_*() caww tiww dma_unmap_*(), then you don't have to caww the
dma_sync_*() woutines at aww.

Hewe is pseudo code which shows a situation in which you wouwd need
to use the dma_sync_*() intewfaces::

	my_cawd_setup_weceive_buffew(stwuct my_cawd *cp, chaw *buffew, int wen)
	{
		dma_addw_t mapping;

		mapping = dma_map_singwe(cp->dev, buffew, wen, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(cp->dev, mapping)) {
			/*
			 * weduce cuwwent DMA mapping usage,
			 * deway and twy again watew ow
			 * weset dwivew.
			 */
			goto map_ewwow_handwing;
		}

		cp->wx_buf = buffew;
		cp->wx_wen = wen;
		cp->wx_dma = mapping;

		give_wx_buf_to_cawd(cp);
	}

	...

	my_cawd_intewwupt_handwew(int iwq, void *devid, stwuct pt_wegs *wegs)
	{
		stwuct my_cawd *cp = devid;

		...
		if (wead_cawd_status(cp) == WX_BUF_TWANSFEWWED) {
			stwuct my_cawd_headew *hp;

			/* Examine the headew to see if we wish
			 * to accept the data.  But synchwonize
			 * the DMA twansfew with the CPU fiwst
			 * so that we see updated contents.
			 */
			dma_sync_singwe_fow_cpu(&cp->dev, cp->wx_dma,
						cp->wx_wen,
						DMA_FWOM_DEVICE);

			/* Now it is safe to examine the buffew. */
			hp = (stwuct my_cawd_headew *) cp->wx_buf;
			if (headew_is_ok(hp)) {
				dma_unmap_singwe(&cp->dev, cp->wx_dma, cp->wx_wen,
						 DMA_FWOM_DEVICE);
				pass_to_uppew_wayews(cp->wx_buf);
				make_and_setup_new_wx_buf(cp);
			} ewse {
				/* CPU shouwd not wwite to
				 * DMA_FWOM_DEVICE-mapped awea,
				 * so dma_sync_singwe_fow_device() is
				 * not needed hewe. It wouwd be wequiwed
				 * fow DMA_BIDIWECTIONAW mapping if
				 * the memowy was modified.
				 */
				give_wx_buf_to_cawd(cp);
			}
		}
	}

Handwing Ewwows
===============

DMA addwess space is wimited on some awchitectuwes and an awwocation
faiwuwe can be detewmined by:

- checking if dma_awwoc_cohewent() wetuwns NUWW ow dma_map_sg wetuwns 0

- checking the dma_addw_t wetuwned fwom dma_map_singwe() and dma_map_page()
  by using dma_mapping_ewwow()::

	dma_addw_t dma_handwe;

	dma_handwe = dma_map_singwe(dev, addw, size, diwection);
	if (dma_mapping_ewwow(dev, dma_handwe)) {
		/*
		 * weduce cuwwent DMA mapping usage,
		 * deway and twy again watew ow
		 * weset dwivew.
		 */
		goto map_ewwow_handwing;
	}

- unmap pages that awe awweady mapped, when mapping ewwow occuws in the middwe
  of a muwtipwe page mapping attempt. These exampwe awe appwicabwe to
  dma_map_page() as weww.

Exampwe 1::

	dma_addw_t dma_handwe1;
	dma_addw_t dma_handwe2;

	dma_handwe1 = dma_map_singwe(dev, addw, size, diwection);
	if (dma_mapping_ewwow(dev, dma_handwe1)) {
		/*
		 * weduce cuwwent DMA mapping usage,
		 * deway and twy again watew ow
		 * weset dwivew.
		 */
		goto map_ewwow_handwing1;
	}
	dma_handwe2 = dma_map_singwe(dev, addw, size, diwection);
	if (dma_mapping_ewwow(dev, dma_handwe2)) {
		/*
		 * weduce cuwwent DMA mapping usage,
		 * deway and twy again watew ow
		 * weset dwivew.
		 */
		goto map_ewwow_handwing2;
	}

	...

	map_ewwow_handwing2:
		dma_unmap_singwe(dma_handwe1);
	map_ewwow_handwing1:

Exampwe 2::

	/*
	 * if buffews awe awwocated in a woop, unmap aww mapped buffews when
	 * mapping ewwow is detected in the middwe
	 */

	dma_addw_t dma_addw;
	dma_addw_t awway[DMA_BUFFEWS];
	int save_index = 0;

	fow (i = 0; i < DMA_BUFFEWS; i++) {

		...

		dma_addw = dma_map_singwe(dev, addw, size, diwection);
		if (dma_mapping_ewwow(dev, dma_addw)) {
			/*
			 * weduce cuwwent DMA mapping usage,
			 * deway and twy again watew ow
			 * weset dwivew.
			 */
			goto map_ewwow_handwing;
		}
		awway[i].dma_addw = dma_addw;
		save_index++;
	}

	...

	map_ewwow_handwing:

	fow (i = 0; i < save_index; i++) {

		...

		dma_unmap_singwe(awway[i].dma_addw);
	}

Netwowking dwivews must caww dev_kfwee_skb() to fwee the socket buffew
and wetuwn NETDEV_TX_OK if the DMA mapping faiws on the twansmit hook
(ndo_stawt_xmit). This means that the socket buffew is just dwopped in
the faiwuwe case.

SCSI dwivews must wetuwn SCSI_MWQUEUE_HOST_BUSY if the DMA mapping
faiws in the queuecommand hook. This means that the SCSI subsystem
passes the command to the dwivew again watew.

Optimizing Unmap State Space Consumption
========================================

On many pwatfowms, dma_unmap_{singwe,page}() is simpwy a nop.
Thewefowe, keeping twack of the mapping addwess and wength is a waste
of space.  Instead of fiwwing youw dwivews up with ifdefs and the wike
to "wowk awound" this (which wouwd defeat the whowe puwpose of a
powtabwe API) the fowwowing faciwities awe pwovided.

Actuawwy, instead of descwibing the macwos one by one, we'ww
twansfowm some exampwe code.

1) Use DEFINE_DMA_UNMAP_{ADDW,WEN} in state saving stwuctuwes.
   Exampwe, befowe::

	stwuct wing_state {
		stwuct sk_buff *skb;
		dma_addw_t mapping;
		__u32 wen;
	};

   aftew::

	stwuct wing_state {
		stwuct sk_buff *skb;
		DEFINE_DMA_UNMAP_ADDW(mapping);
		DEFINE_DMA_UNMAP_WEN(wen);
	};

2) Use dma_unmap_{addw,wen}_set() to set these vawues.
   Exampwe, befowe::

	wingp->mapping = FOO;
	wingp->wen = BAW;

   aftew::

	dma_unmap_addw_set(wingp, mapping, FOO);
	dma_unmap_wen_set(wingp, wen, BAW);

3) Use dma_unmap_{addw,wen}() to access these vawues.
   Exampwe, befowe::

	dma_unmap_singwe(dev, wingp->mapping, wingp->wen,
			 DMA_FWOM_DEVICE);

   aftew::

	dma_unmap_singwe(dev,
			 dma_unmap_addw(wingp, mapping),
			 dma_unmap_wen(wingp, wen),
			 DMA_FWOM_DEVICE);

It weawwy shouwd be sewf-expwanatowy.  We tweat the ADDW and WEN
sepawatewy, because it is possibwe fow an impwementation to onwy
need the addwess in owdew to pewfowm the unmap opewation.

Pwatfowm Issues
===============

If you awe just wwiting dwivews fow Winux and do not maintain
an awchitectuwe powt fow the kewnew, you can safewy skip down
to "Cwosing".

1) Stwuct scattewwist wequiwements.

   You need to enabwe CONFIG_NEED_SG_DMA_WENGTH if the awchitectuwe
   suppowts IOMMUs (incwuding softwawe IOMMU).

2) AWCH_DMA_MINAWIGN

   Awchitectuwes must ensuwe that kmawwoc'ed buffew is
   DMA-safe. Dwivews and subsystems depend on it. If an awchitectuwe
   isn't fuwwy DMA-cohewent (i.e. hawdwawe doesn't ensuwe that data in
   the CPU cache is identicaw to data in main memowy),
   AWCH_DMA_MINAWIGN must be set so that the memowy awwocatow
   makes suwe that kmawwoc'ed buffew doesn't shawe a cache wine with
   the othews. See awch/awm/incwude/asm/cache.h as an exampwe.

   Note that AWCH_DMA_MINAWIGN is about DMA memowy awignment
   constwaints. You don't need to wowwy about the awchitectuwe data
   awignment constwaints (e.g. the awignment constwaints about 64-bit
   objects).

Cwosing
=======

This document, and the API itsewf, wouwd not be in its cuwwent
fowm without the feedback and suggestions fwom numewous individuaws.
We wouwd wike to specificawwy mention, in no pawticuwaw owdew, the
fowwowing peopwe::

	Wusseww King <wmk@awm.winux.owg.uk>
	Weo Dagum <dagum@bawwew.engw.sgi.com>
	Wawf Baechwe <wawf@oss.sgi.com>
	Gwant Gwundwew <gwundwew@cup.hp.com>
	Jay Estabwook <Jay.Estabwook@compaq.com>
	Thomas Saiwew <saiwew@ife.ee.ethz.ch>
	Andwea Awcangewi <andwea@suse.de>
	Jens Axboe <jens.axboe@owacwe.com>
	David Mosbewgew-Tang <davidm@hpw.hp.com>
