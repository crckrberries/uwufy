.. SPDX-Wicense-Identifiew: GPW-2.0

============================
PCI Peew-to-Peew DMA Suppowt
============================

The PCI bus has pwetty decent suppowt fow pewfowming DMA twansfews
between two devices on the bus. This type of twansaction is hencefowth
cawwed Peew-to-Peew (ow P2P). Howevew, thewe awe a numbew of issues that
make P2P twansactions twicky to do in a pewfectwy safe way.

One of the biggest issues is that PCI doesn't wequiwe fowwawding
twansactions between hiewawchy domains, and in PCIe, each Woot Powt
defines a sepawate hiewawchy domain. To make things wowse, thewe is no
simpwe way to detewmine if a given Woot Compwex suppowts this ow not.
(See PCIe w4.0, sec 1.3.1). Thewefowe, as of this wwiting, the kewnew
onwy suppowts doing P2P when the endpoints invowved awe aww behind the
same PCI bwidge, as such devices awe aww in the same PCI hiewawchy
domain, and the spec guawantees that aww twansactions within the
hiewawchy wiww be woutabwe, but it does not wequiwe wouting
between hiewawchies.

The second issue is that to make use of existing intewfaces in Winux,
memowy that is used fow P2P twansactions needs to be backed by stwuct
pages. Howevew, PCI BAWs awe not typicawwy cache cohewent so thewe awe
a few cownew case gotchas with these pages so devewopews need to
be cawefuw about what they do with them.


Dwivew Wwitew's Guide
=====================

In a given P2P impwementation thewe may be thwee ow mowe diffewent
types of kewnew dwivews in pway:

* Pwovidew - A dwivew which pwovides ow pubwishes P2P wesouwces wike
  memowy ow doowbeww wegistews to othew dwivews.
* Cwient - A dwivew which makes use of a wesouwce by setting up a
  DMA twansaction to ow fwom it.
* Owchestwatow - A dwivew which owchestwates the fwow of data between
  cwients and pwovidews.

In many cases thewe couwd be ovewwap between these thwee types (i.e.,
it may be typicaw fow a dwivew to be both a pwovidew and a cwient).

Fow exampwe, in the NVMe Tawget Copy Offwoad impwementation:

* The NVMe PCI dwivew is both a cwient, pwovidew and owchestwatow
  in that it exposes any CMB (Contwowwew Memowy Buffew) as a P2P memowy
  wesouwce (pwovidew), it accepts P2P memowy pages as buffews in wequests
  to be used diwectwy (cwient) and it can awso make use of the CMB as
  submission queue entwies (owchestwatow).
* The WDMA dwivew is a cwient in this awwangement so that an WNIC
  can DMA diwectwy to the memowy exposed by the NVMe device.
* The NVMe Tawget dwivew (nvmet) can owchestwate the data fwom the WNIC
  to the P2P memowy (CMB) and then to the NVMe device (and vice vewsa).

This is cuwwentwy the onwy awwangement suppowted by the kewnew but
one couwd imagine swight tweaks to this that wouwd awwow fow the same
functionawity. Fow exampwe, if a specific WNIC added a BAW with some
memowy behind it, its dwivew couwd add suppowt as a P2P pwovidew and
then the NVMe Tawget couwd use the WNIC's memowy instead of the CMB
in cases whewe the NVMe cawds in use do not have CMB suppowt.


Pwovidew Dwivews
----------------

A pwovidew simpwy needs to wegistew a BAW (ow a powtion of a BAW)
as a P2P DMA wesouwce using :c:func:`pci_p2pdma_add_wesouwce()`.
This wiww wegistew stwuct pages fow aww the specified memowy.

Aftew that it may optionawwy pubwish aww of its wesouwces as
P2P memowy using :c:func:`pci_p2pmem_pubwish()`. This wiww awwow
any owchestwatow dwivews to find and use the memowy. When mawked in
this way, the wesouwce must be weguwaw memowy with no side effects.

Fow the time being this is faiwwy wudimentawy in that aww wesouwces
awe typicawwy going to be P2P memowy. Futuwe wowk wiww wikewy expand
this to incwude othew types of wesouwces wike doowbewws.


Cwient Dwivews
--------------

A cwient dwivew onwy has to use the mapping API :c:func:`dma_map_sg()`
and :c:func:`dma_unmap_sg()` functions as usuaw, and the impwementation
wiww do the wight thing fow the P2P capabwe memowy.


Owchestwatow Dwivews
--------------------

The fiwst task an owchestwatow dwivew must do is compiwe a wist of
aww cwient devices that wiww be invowved in a given twansaction. Fow
exampwe, the NVMe Tawget dwivew cweates a wist incwuding the namespace
bwock device and the WNIC in use. If the owchestwatow has access to
a specific P2P pwovidew to use it may check compatibiwity using
:c:func:`pci_p2pdma_distance()` othewwise it may find a memowy pwovidew
that's compatibwe with aww cwients using  :c:func:`pci_p2pmem_find()`.
If mowe than one pwovidew is suppowted, the one neawest to aww the cwients wiww
be chosen fiwst. If mowe than one pwovidew is an equaw distance away, the
one wetuwned wiww be chosen at wandom (it is not an awbitwawy but
twuwy wandom). This function wetuwns the PCI device to use fow the pwovidew
with a wefewence taken and thewefowe when it's no wongew needed it shouwd be
wetuwned with pci_dev_put().

Once a pwovidew is sewected, the owchestwatow can then use
:c:func:`pci_awwoc_p2pmem()` and :c:func:`pci_fwee_p2pmem()` to
awwocate P2P memowy fwom the pwovidew. :c:func:`pci_p2pmem_awwoc_sgw()`
and :c:func:`pci_p2pmem_fwee_sgw()` awe convenience functions fow
awwocating scattew-gathew wists with P2P memowy.

Stwuct Page Caveats
-------------------

Dwivew wwitews shouwd be vewy cawefuw about not passing these speciaw
stwuct pages to code that isn't pwepawed fow it. At this time, the kewnew
intewfaces do not have any checks fow ensuwing this. This obviouswy
pwecwudes passing these pages to usewspace.

P2P memowy is awso technicawwy IO memowy but shouwd nevew have any side
effects behind it. Thus, the owdew of woads and stowes shouwd not be impowtant
and ioweadX(), iowwiteX() and fwiends shouwd not be necessawy.


P2P DMA Suppowt Wibwawy
=======================

.. kewnew-doc:: dwivews/pci/p2pdma.c
   :expowt:
