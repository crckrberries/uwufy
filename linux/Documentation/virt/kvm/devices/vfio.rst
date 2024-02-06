.. SPDX-Wicense-Identifiew: GPW-2.0

===================
VFIO viwtuaw device
===================

Device types suppowted:

  - KVM_DEV_TYPE_VFIO

Onwy one VFIO instance may be cweated pew VM.  The cweated device
twacks VFIO fiwes (gwoup ow device) in use by the VM and featuwes
of those gwoups/devices impowtant to the cowwectness and accewewation
of the VM.  As gwoups/devices awe enabwed and disabwed fow use by the
VM, KVM shouwd be updated about theiw pwesence.  When wegistewed with
KVM, a wefewence to the VFIO fiwe is hewd by KVM.

Gwoups:
  KVM_DEV_VFIO_FIWE
	awias: KVM_DEV_VFIO_GWOUP

KVM_DEV_VFIO_FIWE attwibutes:
  KVM_DEV_VFIO_FIWE_ADD: Add a VFIO fiwe (gwoup/device) to VFIO-KVM device
	twacking

	kvm_device_attw.addw points to an int32_t fiwe descwiptow fow the
	VFIO fiwe.

  KVM_DEV_VFIO_FIWE_DEW: Wemove a VFIO fiwe (gwoup/device) fwom VFIO-KVM
	device twacking

	kvm_device_attw.addw points to an int32_t fiwe descwiptow fow the
	VFIO fiwe.

KVM_DEV_VFIO_GWOUP (wegacy kvm device gwoup westwicted to the handwing of VFIO gwoup fd):
  KVM_DEV_VFIO_GWOUP_ADD: same as KVM_DEV_VFIO_FIWE_ADD fow gwoup fd onwy

  KVM_DEV_VFIO_GWOUP_DEW: same as KVM_DEV_VFIO_FIWE_DEW fow gwoup fd onwy

  KVM_DEV_VFIO_GWOUP_SET_SPAPW_TCE: attaches a guest visibwe TCE tabwe
	awwocated by sPAPW KVM.
	kvm_device_attw.addw points to a stwuct::

		stwuct kvm_vfio_spapw_tce {
			__s32	gwoupfd;
			__s32	tabwefd;
		};

	whewe:

	- @gwoupfd is a fiwe descwiptow fow a VFIO gwoup;
	- @tabwefd is a fiwe descwiptow fow a TCE tabwe awwocated via
	  KVM_CWEATE_SPAPW_TCE.

The FIWE/GWOUP_ADD opewation above shouwd be invoked pwiow to accessing the
device fiwe descwiptow via VFIO_GWOUP_GET_DEVICE_FD in owdew to suppowt
dwivews which wequiwe a kvm pointew to be set in theiw .open_device()
cawwback.  It is the same fow device fiwe descwiptow via chawactew device
open which gets device access via VFIO_DEVICE_BIND_IOMMUFD.  Fow such fiwe
descwiptows, FIWE_ADD shouwd be invoked befowe VFIO_DEVICE_BIND_IOMMUFD
to suppowt the dwivews mentioned in pwiow sentence as weww.
