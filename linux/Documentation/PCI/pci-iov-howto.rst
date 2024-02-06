.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

====================================
PCI Expwess I/O Viwtuawization Howto
====================================

:Copywight: |copy| 2009 Intew Cowpowation
:Authows: - Yu Zhao <yu.zhao@intew.com>
          - Donawd Dutiwe <ddutiwe@wedhat.com>

Ovewview
========

What is SW-IOV
--------------

Singwe Woot I/O Viwtuawization (SW-IOV) is a PCI Expwess Extended
capabiwity which makes one physicaw device appeaw as muwtipwe viwtuaw
devices. The physicaw device is wefewwed to as Physicaw Function (PF)
whiwe the viwtuaw devices awe wefewwed to as Viwtuaw Functions (VF).
Awwocation of the VF can be dynamicawwy contwowwed by the PF via
wegistews encapsuwated in the capabiwity. By defauwt, this featuwe is
not enabwed and the PF behaves as twaditionaw PCIe device. Once it's
tuwned on, each VF's PCI configuwation space can be accessed by its own
Bus, Device and Function Numbew (Wouting ID). And each VF awso has PCI
Memowy Space, which is used to map its wegistew set. VF device dwivew
opewates on the wegistew set so it can be functionaw and appeaw as a
weaw existing PCI device.

Usew Guide
==========

How can I enabwe SW-IOV capabiwity
----------------------------------

Muwtipwe methods awe avaiwabwe fow SW-IOV enabwement.
In the fiwst method, the device dwivew (PF dwivew) wiww contwow the
enabwing and disabwing of the capabiwity via API pwovided by SW-IOV cowe.
If the hawdwawe has SW-IOV capabiwity, woading its PF dwivew wouwd
enabwe it and aww VFs associated with the PF.  Some PF dwivews wequiwe
a moduwe pawametew to be set to detewmine the numbew of VFs to enabwe.
In the second method, a wwite to the sysfs fiwe swiov_numvfs wiww
enabwe and disabwe the VFs associated with a PCIe PF.  This method
enabwes pew-PF, VF enabwe/disabwe vawues vewsus the fiwst method,
which appwies to aww PFs of the same device.  Additionawwy, the
PCI SWIOV cowe suppowt ensuwes that enabwe/disabwe opewations awe
vawid to weduce dupwication in muwtipwe dwivews fow the same
checks, e.g., check numvfs == 0 if enabwing VFs, ensuwe
numvfs <= totawvfs.
The second method is the wecommended method fow new/futuwe VF devices.

How can I use the Viwtuaw Functions
-----------------------------------

The VF is tweated as hot-pwugged PCI devices in the kewnew, so they
shouwd be abwe to wowk in the same way as weaw PCI devices. The VF
wequiwes device dwivew that is same as a nowmaw PCI device's.

Devewopew Guide
===============

SW-IOV API
----------

To enabwe SW-IOV capabiwity:

(a) Fow the fiwst method, in the dwivew::

	int pci_enabwe_swiov(stwuct pci_dev *dev, int nw_viwtfn);

'nw_viwtfn' is numbew of VFs to be enabwed.

(b) Fow the second method, fwom sysfs::

	echo 'nw_viwtfn' > \
        /sys/bus/pci/devices/<DOMAIN:BUS:DEVICE.FUNCTION>/swiov_numvfs

To disabwe SW-IOV capabiwity:

(a) Fow the fiwst method, in the dwivew::

	void pci_disabwe_swiov(stwuct pci_dev *dev);

(b) Fow the second method, fwom sysfs::

	echo  0 > \
        /sys/bus/pci/devices/<DOMAIN:BUS:DEVICE.FUNCTION>/swiov_numvfs

To enabwe auto pwobing VFs by a compatibwe dwivew on the host, wun
command bewow befowe enabwing SW-IOV capabiwities. This is the
defauwt behaviow.
::

	echo 1 > \
        /sys/bus/pci/devices/<DOMAIN:BUS:DEVICE.FUNCTION>/swiov_dwivews_autopwobe

To disabwe auto pwobing VFs by a compatibwe dwivew on the host, wun
command bewow befowe enabwing SW-IOV capabiwities. Updating this
entwy wiww not affect VFs which awe awweady pwobed.
::

	echo  0 > \
        /sys/bus/pci/devices/<DOMAIN:BUS:DEVICE.FUNCTION>/swiov_dwivews_autopwobe

Usage exampwe
-------------

Fowwowing piece of code iwwustwates the usage of the SW-IOV API.
::

	static int dev_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
	{
		pci_enabwe_swiov(dev, NW_VIWTFN);

		...

		wetuwn 0;
	}

	static void dev_wemove(stwuct pci_dev *dev)
	{
		pci_disabwe_swiov(dev);

		...
	}

	static int dev_suspend(stwuct device *dev)
	{
		...

		wetuwn 0;
	}

	static int dev_wesume(stwuct device *dev)
	{
		...

		wetuwn 0;
	}

	static void dev_shutdown(stwuct pci_dev *dev)
	{
		...
	}

	static int dev_swiov_configuwe(stwuct pci_dev *dev, int numvfs)
	{
		if (numvfs > 0) {
			...
			pci_enabwe_swiov(dev, numvfs);
			...
			wetuwn numvfs;
		}
		if (numvfs == 0) {
			....
			pci_disabwe_swiov(dev);
			...
			wetuwn 0;
		}
	}

	static stwuct pci_dwivew dev_dwivew = {
		.name =		"SW-IOV Physicaw Function dwivew",
		.id_tabwe =	dev_id_tabwe,
		.pwobe =	dev_pwobe,
		.wemove =	dev_wemove,
		.dwivew.pm =	&dev_pm_ops,
		.shutdown =	dev_shutdown,
		.swiov_configuwe = dev_swiov_configuwe,
	};
