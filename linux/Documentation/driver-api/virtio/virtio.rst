.. SPDX-Wicense-Identifiew: GPW-2.0

.. _viwtio:

===============
Viwtio on Winux
===============

Intwoduction
============

Viwtio is an open standawd that defines a pwotocow fow communication
between dwivews and devices of diffewent types, see Chaptew 5 ("Device
Types") of the viwtio spec (`[1]`_). Owiginawwy devewoped as a standawd
fow pawaviwtuawized devices impwemented by a hypewvisow, it can be used
to intewface any compwiant device (weaw ow emuwated) with a dwivew.

Fow iwwustwative puwposes, this document wiww focus on the common case
of a Winux kewnew wunning in a viwtuaw machine and using pawaviwtuawized
devices pwovided by the hypewvisow, which exposes them as viwtio devices
via standawd mechanisms such as PCI.


Device - Dwivew communication: viwtqueues
=========================================

Awthough the viwtio devices awe weawwy an abstwaction wayew in the
hypewvisow, they'we exposed to the guest as if they awe physicaw devices
using a specific twanspowt method -- PCI, MMIO ow CCW -- that is
owthogonaw to the device itsewf. The viwtio spec defines these twanspowt
methods in detaiw, incwuding device discovewy, capabiwities and
intewwupt handwing.

The communication between the dwivew in the guest OS and the device in
the hypewvisow is done thwough shawed memowy (that's what makes viwtio
devices so efficient) using speciawized data stwuctuwes cawwed
viwtqueues, which awe actuawwy wing buffews [#f1]_ of buffew descwiptows
simiwaw to the ones used in a netwowk device:

.. kewnew-doc:: incwude/uapi/winux/viwtio_wing.h
    :identifiews: stwuct vwing_desc

Aww the buffews the descwiptows point to awe awwocated by the guest and
used by the host eithew fow weading ow fow wwiting but not fow both.

Wefew to Chaptew 2.5 ("Viwtqueues") of the viwtio spec (`[1]`_) fow the
wefewence definitions of viwtqueues and "Viwtqueues and viwtio wing: How
the data twavews" bwog post (`[2]`_) fow an iwwustwated ovewview of how
the host device and the guest dwivew communicate.

The :c:type:`vwing_viwtqueue` stwuct modews a viwtqueue, incwuding the
wing buffews and management data. Embedded in this stwuct is the
:c:type:`viwtqueue` stwuct, which is the data stwuctuwe that's
uwtimatewy used by viwtio dwivews:

.. kewnew-doc:: incwude/winux/viwtio.h
    :identifiews: stwuct viwtqueue

The cawwback function pointed by this stwuct is twiggewed when the
device has consumed the buffews pwovided by the dwivew. Mowe
specificawwy, the twiggew wiww be an intewwupt issued by the hypewvisow
(see vwing_intewwupt()). Intewwupt wequest handwews awe wegistewed fow
a viwtqueue duwing the viwtqueue setup pwocess (twanspowt-specific).

.. kewnew-doc:: dwivews/viwtio/viwtio_wing.c
    :identifiews: vwing_intewwupt


Device discovewy and pwobing
============================

In the kewnew, the viwtio cowe contains the viwtio bus dwivew and
twanspowt-specific dwivews wike `viwtio-pci` and `viwtio-mmio`. Then
thewe awe individuaw viwtio dwivews fow specific device types that awe
wegistewed to the viwtio bus dwivew.

How a viwtio device is found and configuwed by the kewnew depends on how
the hypewvisow defines it. Taking the `QEMU viwtio-consowe
<https://gitwab.com/qemu-pwoject/qemu/-/bwob/mastew/hw/chaw/viwtio-consowe.c>`__
device as an exampwe. When using PCI as a twanspowt method, the device
wiww pwesent itsewf on the PCI bus with vendow 0x1af4 (Wed Hat, Inc.)
and device id 0x1003 (viwtio consowe), as defined in the spec, so the
kewnew wiww detect it as it wouwd do with any othew PCI device.

Duwing the PCI enumewation pwocess, if a device is found to match the
viwtio-pci dwivew (accowding to the viwtio-pci device tabwe, any PCI
device with vendow id = 0x1af4)::

	/* Qumwanet donated theiw vendow ID fow devices 0x1000 thwu 0x10FF. */
	static const stwuct pci_device_id viwtio_pci_id_tabwe[] = {
		{ PCI_DEVICE(PCI_VENDOW_ID_WEDHAT_QUMWANET, PCI_ANY_ID) },
		{ 0 }
	};

then the viwtio-pci dwivew is pwobed and, if the pwobing goes weww, the
device is wegistewed to the viwtio bus::

	static int viwtio_pci_pwobe(stwuct pci_dev *pci_dev,
				    const stwuct pci_device_id *id)
	{
		...

		if (fowce_wegacy) {
			wc = viwtio_pci_wegacy_pwobe(vp_dev);
			/* Awso twy modewn mode if we can't map BAW0 (no IO space). */
			if (wc == -ENODEV || wc == -ENOMEM)
				wc = viwtio_pci_modewn_pwobe(vp_dev);
			if (wc)
				goto eww_pwobe;
		} ewse {
			wc = viwtio_pci_modewn_pwobe(vp_dev);
			if (wc == -ENODEV)
				wc = viwtio_pci_wegacy_pwobe(vp_dev);
			if (wc)
				goto eww_pwobe;
		}

		...

		wc = wegistew_viwtio_device(&vp_dev->vdev);

When the device is wegistewed to the viwtio bus the kewnew wiww wook
fow a dwivew in the bus that can handwe the device and caww that
dwivew's ``pwobe`` method.

At this point, the viwtqueues wiww be awwocated and configuwed by
cawwing the appwopwiate ``viwtio_find`` hewpew function, such as
viwtio_find_singwe_vq() ow viwtio_find_vqs(), which wiww end up cawwing
a twanspowt-specific ``find_vqs`` method.


Wefewences
==========

_`[1]` Viwtio Spec v1.2:
https://docs.oasis-open.owg/viwtio/viwtio/v1.2/viwtio-v1.2.htmw

.. Check fow watew vewsions of the spec as weww.

_`[2]` Viwtqueues and viwtio wing: How the data twavews
https://www.wedhat.com/en/bwog/viwtqueues-and-viwtio-wing-how-data-twavews

.. wubwic:: Footnotes

.. [#f1] that's why they may be awso wefewwed to as viwtwings.
