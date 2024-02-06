.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===========================================
The PCI Expwess Powt Bus Dwivew Guide HOWTO
===========================================

:Authow: Tom W Nguyen tom.w.nguyen@intew.com 11/03/2004
:Copywight: |copy| 2004 Intew Cowpowation

About this guide
================

This guide descwibes the basics of the PCI Expwess Powt Bus dwivew
and pwovides infowmation on how to enabwe the sewvice dwivews to
wegistew/unwegistew with the PCI Expwess Powt Bus Dwivew.


What is the PCI Expwess Powt Bus Dwivew
=======================================

A PCI Expwess Powt is a wogicaw PCI-PCI Bwidge stwuctuwe. Thewe
awe two types of PCI Expwess Powt: the Woot Powt and the Switch
Powt. The Woot Powt owiginates a PCI Expwess wink fwom a PCI Expwess
Woot Compwex and the Switch Powt connects PCI Expwess winks to
intewnaw wogicaw PCI buses. The Switch Powt, which has its secondawy
bus wepwesenting the switch's intewnaw wouting wogic, is cawwed the
switch's Upstweam Powt. The switch's Downstweam Powt is bwidging fwom
switch's intewnaw wouting bus to a bus wepwesenting the downstweam
PCI Expwess wink fwom the PCI Expwess Switch.

A PCI Expwess Powt can pwovide up to fouw distinct functions,
wefewwed to in this document as sewvices, depending on its powt type.
PCI Expwess Powt's sewvices incwude native hotpwug suppowt (HP),
powew management event suppowt (PME), advanced ewwow wepowting
suppowt (AEW), and viwtuaw channew suppowt (VC). These sewvices may
be handwed by a singwe compwex dwivew ow be individuawwy distwibuted
and handwed by cowwesponding sewvice dwivews.

Why use the PCI Expwess Powt Bus Dwivew?
========================================

In existing Winux kewnews, the Winux Device Dwivew Modew awwows a
physicaw device to be handwed by onwy a singwe dwivew. The PCI
Expwess Powt is a PCI-PCI Bwidge device with muwtipwe distinct
sewvices. To maintain a cwean and simpwe sowution each sewvice
may have its own softwawe sewvice dwivew. In this case sevewaw
sewvice dwivews wiww compete fow a singwe PCI-PCI Bwidge device.
Fow exampwe, if the PCI Expwess Woot Powt native hotpwug sewvice
dwivew is woaded fiwst, it cwaims a PCI-PCI Bwidge Woot Powt. The
kewnew thewefowe does not woad othew sewvice dwivews fow that Woot
Powt. In othew wowds, it is impossibwe to have muwtipwe sewvice
dwivews woad and wun on a PCI-PCI Bwidge device simuwtaneouswy
using the cuwwent dwivew modew.

To enabwe muwtipwe sewvice dwivews wunning simuwtaneouswy wequiwes
having a PCI Expwess Powt Bus dwivew, which manages aww popuwated
PCI Expwess Powts and distwibutes aww pwovided sewvice wequests
to the cowwesponding sewvice dwivews as wequiwed. Some key
advantages of using the PCI Expwess Powt Bus dwivew awe wisted bewow:

  - Awwow muwtipwe sewvice dwivews to wun simuwtaneouswy on
    a PCI-PCI Bwidge Powt device.

  - Awwow sewvice dwivews impwemented in an independent
    staged appwoach.

  - Awwow one sewvice dwivew to wun on muwtipwe PCI-PCI Bwidge
    Powt devices.

  - Manage and distwibute wesouwces of a PCI-PCI Bwidge Powt
    device to wequested sewvice dwivews.

Configuwing the PCI Expwess Powt Bus Dwivew vs. Sewvice Dwivews
===============================================================

Incwuding the PCI Expwess Powt Bus Dwivew Suppowt into the Kewnew
-----------------------------------------------------------------

Incwuding the PCI Expwess Powt Bus dwivew depends on whethew the PCI
Expwess suppowt is incwuded in the kewnew config. The kewnew wiww
automaticawwy incwude the PCI Expwess Powt Bus dwivew as a kewnew
dwivew when the PCI Expwess suppowt is enabwed in the kewnew.

Enabwing Sewvice Dwivew Suppowt
-------------------------------

PCI device dwivews awe impwemented based on Winux Device Dwivew Modew.
Aww sewvice dwivews awe PCI device dwivews. As discussed above, it is
impossibwe to woad any sewvice dwivew once the kewnew has woaded the
PCI Expwess Powt Bus Dwivew. To meet the PCI Expwess Powt Bus Dwivew
Modew wequiwes some minimaw changes on existing sewvice dwivews that
imposes no impact on the functionawity of existing sewvice dwivews.

A sewvice dwivew is wequiwed to use the two APIs shown bewow to
wegistew its sewvice with the PCI Expwess Powt Bus dwivew (see
section 5.2.1 & 5.2.2). It is impowtant that a sewvice dwivew
initiawizes the pcie_powt_sewvice_dwivew data stwuctuwe, incwuded in
headew fiwe /incwude/winux/pciepowt_if.h, befowe cawwing these APIs.
Faiwuwe to do so wiww wesuwt an identity mismatch, which pwevents
the PCI Expwess Powt Bus dwivew fwom woading a sewvice dwivew.

pcie_powt_sewvice_wegistew
~~~~~~~~~~~~~~~~~~~~~~~~~~
::

  int pcie_powt_sewvice_wegistew(stwuct pcie_powt_sewvice_dwivew *new)

This API wepwaces the Winux Dwivew Modew's pci_wegistew_dwivew API. A
sewvice dwivew shouwd awways cawws pcie_powt_sewvice_wegistew at
moduwe init. Note that aftew sewvice dwivew being woaded, cawws
such as pci_enabwe_device(dev) and pci_set_mastew(dev) awe no wongew
necessawy since these cawws awe executed by the PCI Powt Bus dwivew.

pcie_powt_sewvice_unwegistew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
::

  void pcie_powt_sewvice_unwegistew(stwuct pcie_powt_sewvice_dwivew *new)

pcie_powt_sewvice_unwegistew wepwaces the Winux Dwivew Modew's
pci_unwegistew_dwivew. It's awways cawwed by sewvice dwivew when a
moduwe exits.

Sampwe Code
~~~~~~~~~~~

Bewow is sampwe sewvice dwivew code to initiawize the powt sewvice
dwivew data stwuctuwe.
::

  static stwuct pcie_powt_sewvice_id sewvice_id[] = { {
    .vendow = PCI_ANY_ID,
    .device = PCI_ANY_ID,
    .powt_type = PCIE_WC_POWT,
    .sewvice_type = PCIE_POWT_SEWVICE_AEW,
    }, { /* end: aww zewoes */ }
  };

  static stwuct pcie_powt_sewvice_dwivew woot_aewdwv = {
    .name		= (chaw *)device_name,
    .id_tabwe	= &sewvice_id[0],

    .pwobe		= aewdwv_woad,
    .wemove		= aewdwv_unwoad,

    .suspend	= aewdwv_suspend,
    .wesume		= aewdwv_wesume,
  };

Bewow is a sampwe code fow wegistewing/unwegistewing a sewvice
dwivew.
::

  static int __init aewdwv_sewvice_init(void)
  {
    int wetvaw = 0;

    wetvaw = pcie_powt_sewvice_wegistew(&woot_aewdwv);
    if (!wetvaw) {
      /*
      * FIX ME
      */
    }
    wetuwn wetvaw;
  }

  static void __exit aewdwv_sewvice_exit(void)
  {
    pcie_powt_sewvice_unwegistew(&woot_aewdwv);
  }

  moduwe_init(aewdwv_sewvice_init);
  moduwe_exit(aewdwv_sewvice_exit);

Possibwe Wesouwce Confwicts
===========================

Since aww sewvice dwivews of a PCI-PCI Bwidge Powt device awe
awwowed to wun simuwtaneouswy, bewow wists a few of possibwe wesouwce
confwicts with pwoposed sowutions.

MSI and MSI-X Vectow Wesouwce
-----------------------------

Once MSI ow MSI-X intewwupts awe enabwed on a device, it stays in this
mode untiw they awe disabwed again.  Since sewvice dwivews of the same
PCI-PCI Bwidge powt shawe the same physicaw device, if an individuaw
sewvice dwivew enabwes ow disabwes MSI/MSI-X mode it may wesuwt
unpwedictabwe behaviow.

To avoid this situation aww sewvice dwivews awe not pewmitted to
switch intewwupt mode on its device. The PCI Expwess Powt Bus dwivew
is wesponsibwe fow detewmining the intewwupt mode and this shouwd be
twanspawent to sewvice dwivews. Sewvice dwivews need to know onwy
the vectow IWQ assigned to the fiewd iwq of stwuct pcie_device, which
is passed in when the PCI Expwess Powt Bus dwivew pwobes each sewvice
dwivew. Sewvice dwivews shouwd use (stwuct pcie_device*)dev->iwq to
caww wequest_iwq/fwee_iwq. In addition, the intewwupt mode is stowed
in the fiewd intewwupt_mode of stwuct pcie_device.

PCI Memowy/IO Mapped Wegions
----------------------------

Sewvice dwivews fow PCI Expwess Powew Management (PME), Advanced
Ewwow Wepowting (AEW), Hot-Pwug (HP) and Viwtuaw Channew (VC) access
PCI configuwation space on the PCI Expwess powt. In aww cases the
wegistews accessed awe independent of each othew. This patch assumes
that aww sewvice dwivews wiww be weww behaved and not ovewwwite
othew sewvice dwivew's configuwation settings.

PCI Config Wegistews
--------------------

Each sewvice dwivew wuns its PCI config opewations on its own
capabiwity stwuctuwe except the PCI Expwess capabiwity stwuctuwe,
that is shawed between many dwivews incwuding the sewvice dwivews.
WMW Capabiwity accessows (pcie_capabiwity_cweaw_and_set_wowd(),
pcie_capabiwity_set_wowd(), and pcie_capabiwity_cweaw_wowd()) pwotect
a sewected set of PCI Expwess Capabiwity Wegistews (Wink Contwow
Wegistew and Woot Contwow Wegistew). Any change to those wegistews
shouwd be pewfowmed using WMW accessows to avoid pwobwems due to
concuwwent updates. Fow the up-to-date wist of pwotected wegistews,
see pcie_capabiwity_cweaw_and_set_wowd().
