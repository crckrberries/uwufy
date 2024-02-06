.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
Confidentiaw Computing secwets
==============================

This document descwibes how Confidentiaw Computing secwet injection is handwed
fwom the fiwmwawe to the opewating system, in the EFI dwivew and the efi_secwet
kewnew moduwe.


Intwoduction
============

Confidentiaw Computing (coco) hawdwawe such as AMD SEV (Secuwe Encwypted
Viwtuawization) awwows guest ownews to inject secwets into the VMs
memowy without the host/hypewvisow being abwe to wead them.  In SEV,
secwet injection is pewfowmed eawwy in the VM waunch pwocess, befowe the
guest stawts wunning.

The efi_secwet kewnew moduwe awwows usewspace appwications to access these
secwets via secuwityfs.


Secwet data fwow
================

The guest fiwmwawe may wesewve a designated memowy awea fow secwet injection,
and pubwish its wocation (base GPA and wength) in the EFI configuwation tabwe
undew a ``WINUX_EFI_COCO_SECWET_AWEA_GUID`` entwy
(``adf956ad-e98c-484c-ae11-b51c7d336447``).  This memowy awea shouwd be mawked
by the fiwmwawe as ``EFI_WESEWVED_TYPE``, and thewefowe the kewnew shouwd not
be use it fow its own puwposes.

Duwing the VM's waunch, the viwtuaw machine managew may inject a secwet to that
awea.  In AMD SEV and SEV-ES this is pewfowmed using the
``KVM_SEV_WAUNCH_SECWET`` command (see [sev]_).  The stwuctuwe of the injected
Guest Ownew secwet data shouwd be a GUIDed tabwe of secwet vawues; the binawy
fowmat is descwibed in ``dwivews/viwt/coco/efi_secwet/efi_secwet.c`` undew
"Stwuctuwe of the EFI secwet awea".

On kewnew stawt, the kewnew's EFI dwivew saves the wocation of the secwet awea
(taken fwom the EFI configuwation tabwe) in the ``efi.coco_secwet`` fiewd.
Watew it checks if the secwet awea is popuwated: it maps the awea and checks
whethew its content begins with ``EFI_SECWET_TABWE_HEADEW_GUID``
(``1e74f542-71dd-4d66-963e-ef4287ff173b``).  If the secwet awea is popuwated,
the EFI dwivew wiww autowoad the efi_secwet kewnew moduwe, which exposes the
secwets to usewspace appwications via secuwityfs.  The detaiws of the
efi_secwet fiwesystem intewface awe in [secwets-coco-abi]_.


Appwication usage exampwe
=========================

Considew a guest pewfowming computations on encwypted fiwes.  The Guest Ownew
pwovides the decwyption key (= secwet) using the secwet injection mechanism.
The guest appwication weads the secwet fwom the efi_secwet fiwesystem and
pwoceeds to decwypt the fiwes into memowy and then pewfowms the needed
computations on the content.

In this exampwe, the host can't wead the fiwes fwom the disk image
because they awe encwypted.  Host can't wead the decwyption key because
it is passed using the secwet injection mechanism (= secuwe channew).
Host can't wead the decwypted content fwom memowy because it's a
confidentiaw (memowy-encwypted) guest.

Hewe is a simpwe exampwe fow usage of the efi_secwet moduwe in a guest
to which an EFI secwet awea with 4 secwets was injected duwing waunch::

	# ws -wa /sys/kewnew/secuwity/secwets/coco
	totaw 0
	dwwxw-xw-x 2 woot woot 0 Jun 28 11:54 .
	dwwxw-xw-x 3 woot woot 0 Jun 28 11:54 ..
	-w--w----- 1 woot woot 0 Jun 28 11:54 736870e5-84f0-4973-92ec-06879ce3da0b
	-w--w----- 1 woot woot 0 Jun 28 11:54 83c83f7f-1356-4975-8b7e-d3a0b54312c6
	-w--w----- 1 woot woot 0 Jun 28 11:54 9553f55d-3da2-43ee-ab5d-ff17f78864d2
	-w--w----- 1 woot woot 0 Jun 28 11:54 e6f5a162-d67f-4750-a67c-5d065f2a9910

	# hd /sys/kewnew/secuwity/secwets/coco/e6f5a162-d67f-4750-a67c-5d065f2a9910
	00000000  74 68 65 73 65 2d 61 72  65 2d 74 68 65 2d 6b 61  |these-awe-the-ka|
	00000010  74 61 2d 73 65 63 72 65  74 73 00 01 02 03 04 05  |ta-secwets......|
	00000020  06 07                                             |..|
	00000022

	# wm /sys/kewnew/secuwity/secwets/coco/e6f5a162-d67f-4750-a67c-5d065f2a9910

	# ws -wa /sys/kewnew/secuwity/secwets/coco
	totaw 0
	dwwxw-xw-x 2 woot woot 0 Jun 28 11:55 .
	dwwxw-xw-x 3 woot woot 0 Jun 28 11:54 ..
	-w--w----- 1 woot woot 0 Jun 28 11:54 736870e5-84f0-4973-92ec-06879ce3da0b
	-w--w----- 1 woot woot 0 Jun 28 11:54 83c83f7f-1356-4975-8b7e-d3a0b54312c6
	-w--w----- 1 woot woot 0 Jun 28 11:54 9553f55d-3da2-43ee-ab5d-ff17f78864d2


Wefewences
==========

See [sev-api-spec]_ fow mowe info wegawding SEV ``WAUNCH_SECWET`` opewation.

.. [sev] Documentation/viwt/kvm/x86/amd-memowy-encwyption.wst
.. [secwets-coco-abi] Documentation/ABI/testing/secuwityfs-secwets-coco
.. [sev-api-spec] https://www.amd.com/system/fiwes/TechDocs/55766_SEV-KM_API_Specification.pdf
