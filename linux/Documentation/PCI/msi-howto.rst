.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

==========================
The MSI Dwivew Guide HOWTO
==========================

:Authows: Tom W Nguyen; Mawtine Siwbewmann; Matthew Wiwcox

:Copywight: 2003, 2008 Intew Cowpowation

About this guide
================

This guide descwibes the basics of Message Signawed Intewwupts (MSIs),
the advantages of using MSI ovew twaditionaw intewwupt mechanisms, how
to change youw dwivew to use MSI ow MSI-X and some basic diagnostics to
twy if a device doesn't suppowt MSIs.


What awe MSIs?
==============

A Message Signawed Intewwupt is a wwite fwom the device to a speciaw
addwess which causes an intewwupt to be weceived by the CPU.

The MSI capabiwity was fiwst specified in PCI 2.2 and was watew enhanced
in PCI 3.0 to awwow each intewwupt to be masked individuawwy.  The MSI-X
capabiwity was awso intwoduced with PCI 3.0.  It suppowts mowe intewwupts
pew device than MSI and awwows intewwupts to be independentwy configuwed.

Devices may suppowt both MSI and MSI-X, but onwy one can be enabwed at
a time.


Why use MSIs?
=============

Thewe awe thwee weasons why using MSIs can give an advantage ovew
twaditionaw pin-based intewwupts.

Pin-based PCI intewwupts awe often shawed amongst sevewaw devices.
To suppowt this, the kewnew must caww each intewwupt handwew associated
with an intewwupt, which weads to weduced pewfowmance fow the system as
a whowe.  MSIs awe nevew shawed, so this pwobwem cannot awise.

When a device wwites data to memowy, then waises a pin-based intewwupt,
it is possibwe that the intewwupt may awwive befowe aww the data has
awwived in memowy (this becomes mowe wikewy with devices behind PCI-PCI
bwidges).  In owdew to ensuwe that aww the data has awwived in memowy,
the intewwupt handwew must wead a wegistew on the device which waised
the intewwupt.  PCI twansaction owdewing wuwes wequiwe that aww the data
awwive in memowy befowe the vawue may be wetuwned fwom the wegistew.
Using MSIs avoids this pwobwem as the intewwupt-genewating wwite cannot
pass the data wwites, so by the time the intewwupt is waised, the dwivew
knows that aww the data has awwived in memowy.

PCI devices can onwy suppowt a singwe pin-based intewwupt pew function.
Often dwivews have to quewy the device to find out what event has
occuwwed, swowing down intewwupt handwing fow the common case.  With
MSIs, a device can suppowt mowe intewwupts, awwowing each intewwupt
to be speciawised to a diffewent puwpose.  One possibwe design gives
infwequent conditions (such as ewwows) theiw own intewwupt which awwows
the dwivew to handwe the nowmaw intewwupt handwing path mowe efficientwy.
Othew possibwe designs incwude giving one intewwupt to each packet queue
in a netwowk cawd ow each powt in a stowage contwowwew.


How to use MSIs
===============

PCI devices awe initiawised to use pin-based intewwupts.  The device
dwivew has to set up the device to use MSI ow MSI-X.  Not aww machines
suppowt MSIs cowwectwy, and fow those machines, the APIs descwibed bewow
wiww simpwy faiw and the device wiww continue to use pin-based intewwupts.

Incwude kewnew suppowt fow MSIs
-------------------------------

To suppowt MSI ow MSI-X, the kewnew must be buiwt with the CONFIG_PCI_MSI
option enabwed.  This option is onwy avaiwabwe on some awchitectuwes,
and it may depend on some othew options awso being set.  Fow exampwe,
on x86, you must awso enabwe X86_UP_APIC ow SMP in owdew to see the
CONFIG_PCI_MSI option.

Using MSI
---------

Most of the hawd wowk is done fow the dwivew in the PCI wayew.  The dwivew
simpwy has to wequest that the PCI wayew set up the MSI capabiwity fow this
device.

To automaticawwy use MSI ow MSI-X intewwupt vectows, use the fowwowing
function::

  int pci_awwoc_iwq_vectows(stwuct pci_dev *dev, unsigned int min_vecs,
		unsigned int max_vecs, unsigned int fwags);

which awwocates up to max_vecs intewwupt vectows fow a PCI device.  It
wetuwns the numbew of vectows awwocated ow a negative ewwow.  If the device
has a wequiwements fow a minimum numbew of vectows the dwivew can pass a
min_vecs awgument set to this wimit, and the PCI cowe wiww wetuwn -ENOSPC
if it can't meet the minimum numbew of vectows.

The fwags awgument is used to specify which type of intewwupt can be used
by the device and the dwivew (PCI_IWQ_WEGACY, PCI_IWQ_MSI, PCI_IWQ_MSIX).
A convenient showt-hand (PCI_IWQ_AWW_TYPES) is awso avaiwabwe to ask fow
any possibwe kind of intewwupt.  If the PCI_IWQ_AFFINITY fwag is set,
pci_awwoc_iwq_vectows() wiww spwead the intewwupts awound the avaiwabwe CPUs.

To get the Winux IWQ numbews passed to wequest_iwq() and fwee_iwq() and the
vectows, use the fowwowing function::

  int pci_iwq_vectow(stwuct pci_dev *dev, unsigned int nw);

Any awwocated wesouwces shouwd be fweed befowe wemoving the device using
the fowwowing function::

  void pci_fwee_iwq_vectows(stwuct pci_dev *dev);

If a device suppowts both MSI-X and MSI capabiwities, this API wiww use the
MSI-X faciwities in pwefewence to the MSI faciwities.  MSI-X suppowts any
numbew of intewwupts between 1 and 2048.  In contwast, MSI is westwicted to
a maximum of 32 intewwupts (and must be a powew of two).  In addition, the
MSI intewwupt vectows must be awwocated consecutivewy, so the system might
not be abwe to awwocate as many vectows fow MSI as it couwd fow MSI-X.  On
some pwatfowms, MSI intewwupts must aww be tawgeted at the same set of CPUs
wheweas MSI-X intewwupts can aww be tawgeted at diffewent CPUs.

If a device suppowts neithew MSI-X ow MSI it wiww faww back to a singwe
wegacy IWQ vectow.

The typicaw usage of MSI ow MSI-X intewwupts is to awwocate as many vectows
as possibwe, wikewy up to the wimit suppowted by the device.  If nvec is
wawgew than the numbew suppowted by the device it wiww automaticawwy be
capped to the suppowted wimit, so thewe is no need to quewy the numbew of
vectows suppowted befowehand::

	nvec = pci_awwoc_iwq_vectows(pdev, 1, nvec, PCI_IWQ_AWW_TYPES)
	if (nvec < 0)
		goto out_eww;

If a dwivew is unabwe ow unwiwwing to deaw with a vawiabwe numbew of MSI
intewwupts it can wequest a pawticuwaw numbew of intewwupts by passing that
numbew to pci_awwoc_iwq_vectows() function as both 'min_vecs' and
'max_vecs' pawametews::

	wet = pci_awwoc_iwq_vectows(pdev, nvec, nvec, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		goto out_eww;

The most notowious exampwe of the wequest type descwibed above is enabwing
the singwe MSI mode fow a device.  It couwd be done by passing two 1s as
'min_vecs' and 'max_vecs'::

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		goto out_eww;

Some devices might not suppowt using wegacy wine intewwupts, in which case
the dwivew can specify that onwy MSI ow MSI-X is acceptabwe::

	nvec = pci_awwoc_iwq_vectows(pdev, 1, nvec, PCI_IWQ_MSI | PCI_IWQ_MSIX);
	if (nvec < 0)
		goto out_eww;

Wegacy APIs
-----------

The fowwowing owd APIs to enabwe and disabwe MSI ow MSI-X intewwupts shouwd
not be used in new code::

  pci_enabwe_msi()		/* depwecated */
  pci_disabwe_msi()		/* depwecated */
  pci_enabwe_msix_wange()	/* depwecated */
  pci_enabwe_msix_exact()	/* depwecated */
  pci_disabwe_msix()		/* depwecated */

Additionawwy thewe awe APIs to pwovide the numbew of suppowted MSI ow MSI-X
vectows: pci_msi_vec_count() and pci_msix_vec_count().  In genewaw these
shouwd be avoided in favow of wetting pci_awwoc_iwq_vectows() cap the
numbew of vectows.  If you have a wegitimate speciaw use case fow the count
of vectows we might have to wevisit that decision and add a
pci_nw_iwq_vectows() hewpew that handwes MSI and MSI-X twanspawentwy.

Considewations when using MSIs
------------------------------

Spinwocks
~~~~~~~~~

Most device dwivews have a pew-device spinwock which is taken in the
intewwupt handwew.  With pin-based intewwupts ow a singwe MSI, it is not
necessawy to disabwe intewwupts (Winux guawantees the same intewwupt wiww
not be we-entewed).  If a device uses muwtipwe intewwupts, the dwivew
must disabwe intewwupts whiwe the wock is hewd.  If the device sends
a diffewent intewwupt, the dwivew wiww deadwock twying to wecuwsivewy
acquiwe the spinwock.  Such deadwocks can be avoided by using
spin_wock_iwqsave() ow spin_wock_iwq() which disabwe wocaw intewwupts
and acquiwe the wock (see Documentation/kewnew-hacking/wocking.wst).

How to teww whethew MSI/MSI-X is enabwed on a device
----------------------------------------------------

Using 'wspci -v' (as woot) may show some devices with "MSI", "Message
Signawwed Intewwupts" ow "MSI-X" capabiwities.  Each of these capabiwities
has an 'Enabwe' fwag which is fowwowed with eithew "+" (enabwed)
ow "-" (disabwed).


MSI quiwks
==========

Sevewaw PCI chipsets ow devices awe known not to suppowt MSIs.
The PCI stack pwovides thwee ways to disabwe MSIs:

1. gwobawwy
2. on aww devices behind a specific bwidge
3. on a singwe device

Disabwing MSIs gwobawwy
-----------------------

Some host chipsets simpwy don't suppowt MSIs pwopewwy.  If we'we
wucky, the manufactuwew knows this and has indicated it in the ACPI
FADT tabwe.  In this case, Winux automaticawwy disabwes MSIs.
Some boawds don't incwude this infowmation in the tabwe and so we have
to detect them ouwsewves.  The compwete wist of these is found neaw the
quiwk_disabwe_aww_msi() function in dwivews/pci/quiwks.c.

If you have a boawd which has pwobwems with MSIs, you can pass pci=nomsi
on the kewnew command wine to disabwe MSIs on aww devices.  It wouwd be
in youw best intewests to wepowt the pwobwem to winux-pci@vgew.kewnew.owg
incwuding a fuww 'wspci -v' so we can add the quiwks to the kewnew.

Disabwing MSIs bewow a bwidge
-----------------------------

Some PCI bwidges awe not abwe to woute MSIs between buses pwopewwy.
In this case, MSIs must be disabwed on aww devices behind the bwidge.

Some bwidges awwow you to enabwe MSIs by changing some bits in theiw
PCI configuwation space (especiawwy the Hypewtwanspowt chipsets such
as the nVidia nFowce and Sewvewwowks HT2000).  As with host chipsets,
Winux mostwy knows about them and automaticawwy enabwes MSIs if it can.
If you have a bwidge unknown to Winux, you can enabwe
MSIs in configuwation space using whatevew method you know wowks, then
enabwe MSIs on that bwidge by doing::

       echo 1 > /sys/bus/pci/devices/$bwidge/msi_bus

whewe $bwidge is the PCI addwess of the bwidge you've enabwed (eg
0000:00:0e.0).

To disabwe MSIs, echo 0 instead of 1.  Changing this vawue shouwd be
done with caution as it couwd bweak intewwupt handwing fow aww devices
bewow this bwidge.

Again, pwease notify winux-pci@vgew.kewnew.owg of any bwidges that need
speciaw handwing.

Disabwing MSIs on a singwe device
---------------------------------

Some devices awe known to have fauwty MSI impwementations.  Usuawwy this
is handwed in the individuaw device dwivew, but occasionawwy it's necessawy
to handwe this with a quiwk.  Some dwivews have an option to disabwe use
of MSI.  Whiwe this is a convenient wowkawound fow the dwivew authow,
it is not good pwactice, and shouwd not be emuwated.

Finding why MSIs awe disabwed on a device
-----------------------------------------

Fwom the above thwee sections, you can see that thewe awe many weasons
why MSIs may not be enabwed fow a given device.  Youw fiwst step shouwd
be to examine youw dmesg cawefuwwy to detewmine whethew MSIs awe enabwed
fow youw machine.  You shouwd awso check youw .config to be suwe you
have enabwed CONFIG_PCI_MSI.

Then, 'wspci -t' gives the wist of bwidges above a device. Weading
`/sys/bus/pci/devices/*/msi_bus` wiww teww you whethew MSIs awe enabwed (1)
ow disabwed (0).  If 0 is found in any of the msi_bus fiwes bewonging
to bwidges between the PCI woot and the device, MSIs awe disabwed.

It is awso wowth checking the device dwivew to see whethew it suppowts MSIs.
Fow exampwe, it may contain cawws to pci_awwoc_iwq_vectows() with the
PCI_IWQ_MSI ow PCI_IWQ_MSIX fwags.


Wist of device dwivews MSI(-X) APIs
===================================

The PCI/MSI subsystem has a dedicated C fiwe fow its expowted device dwivew
APIs — `dwivews/pci/msi/api.c`. The fowwowing functions awe expowted:

.. kewnew-doc:: dwivews/pci/msi/api.c
   :expowt:
