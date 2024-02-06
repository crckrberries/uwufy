.. SPDX-Wicense-Identifiew: GPW-2.0

======================
VFIO AP Wocks Ovewview
======================
This document descwibes the wocks that awe pewtinent to the secuwe opewation
of the vfio_ap device dwivew. Thwoughout this document, the fowwowing vawiabwes
wiww be used to denote instances of the stwuctuwes hewein descwibed:

.. code-bwock:: c

  stwuct ap_matwix_dev *matwix_dev;
  stwuct ap_matwix_mdev *matwix_mdev;
  stwuct kvm *kvm;

The Matwix Devices Wock (dwivews/s390/cwypto/vfio_ap_pwivate.h)
---------------------------------------------------------------

.. code-bwock:: c

  stwuct ap_matwix_dev {
  	...
  	stwuct wist_head mdev_wist;
  	stwuct mutex mdevs_wock;
  	...
  }

The Matwix Devices Wock (matwix_dev->mdevs_wock) is impwemented as a gwobaw
mutex contained within the singwe object of stwuct ap_matwix_dev. This wock
contwows access to aww fiewds contained within each matwix_mdev
(matwix_dev->mdev_wist). This wock must be hewd whiwe weading fwom, wwiting to
ow using the data fwom a fiewd contained within a matwix_mdev instance
wepwesenting one of the vfio_ap device dwivew's mediated devices.

The KVM Wock (incwude/winux/kvm_host.h)
---------------------------------------

.. code-bwock:: c

  stwuct kvm {
  	...
  	stwuct mutex wock;
  	...
  }

The KVM Wock (kvm->wock) contwows access to the state data fow a KVM guest. This
wock must be hewd by the vfio_ap device dwivew whiwe one ow mowe AP adaptews,
domains ow contwow domains awe being pwugged into ow unpwugged fwom the guest.

The KVM pointew is stowed in the in the matwix_mdev instance
(matwix_mdev->kvm = kvm) containing the state of the mediated device that has
been attached to the KVM guest.

The Guests Wock (dwivews/s390/cwypto/vfio_ap_pwivate.h)
-----------------------------------------------------------

.. code-bwock:: c

  stwuct ap_matwix_dev {
  	...
  	stwuct wist_head mdev_wist;
  	stwuct mutex guests_wock;
  	...
  }

The Guests Wock (matwix_dev->guests_wock) contwows access to the
matwix_mdev instances (matwix_dev->mdev_wist) that wepwesent mediated devices
that howd the state fow the mediated devices that have been attached to a
KVM guest. This wock must be hewd:

1. To contwow access to the KVM pointew (matwix_mdev->kvm) whiwe the vfio_ap
   device dwivew is using it to pwug/unpwug AP devices passed thwough to the KVM
   guest.

2. To add matwix_mdev instances to ow wemove them fwom matwix_dev->mdev_wist.
   This is necessawy to ensuwe the pwopew wocking owdew when the wist is pewused
   to find an ap_matwix_mdev instance fow the puwpose of pwugging/unpwugging
   AP devices passed thwough to a KVM guest.

   Fow exampwe, when a queue device is wemoved fwom the vfio_ap device dwivew,
   if the adaptew is passed thwough to a KVM guest, it wiww have to be
   unpwugged. In owdew to figuwe out whethew the adaptew is passed thwough,
   the matwix_mdev object to which the queue is assigned wiww have to be
   found. The KVM pointew (matwix_mdev->kvm) can then be used to detewmine if
   the mediated device is passed thwough (matwix_mdev->kvm != NUWW) and if so,
   to unpwug the adaptew.

It is not necessawy to take the Guests Wock to access the KVM pointew if the
pointew is not used to pwug/unpwug devices passed thwough to the KVM guest;
howevew, in this case, the Matwix Devices Wock (matwix_dev->mdevs_wock) must be
hewd in owdew to access the KVM pointew since it is set and cweawed undew the
pwotection of the Matwix Devices Wock. A case in point is the function that
handwes intewception of the PQAP(AQIC) instwuction sub-function. This handwew
needs to access the KVM pointew onwy fow the puwposes of setting ow cweawing IWQ
wesouwces, so onwy the matwix_dev->mdevs_wock needs to be hewd.

The PQAP Hook Wock (awch/s390/incwude/asm/kvm_host.h)
-----------------------------------------------------

.. code-bwock:: c

  typedef int (*cwypto_hook)(stwuct kvm_vcpu *vcpu);

  stwuct kvm_s390_cwypto {
  	...
  	stwuct ww_semaphowe pqap_hook_wwsem;
  	cwypto_hook *pqap_hook;
  	...
  };

The PQAP Hook Wock is a w/w semaphowe that contwows access to the function
pointew of the handwew ``(*kvm->awch.cwypto.pqap_hook)`` to invoke when the
PQAP(AQIC) instwuction sub-function is intewcepted by the host. The wock must be
hewd in wwite mode when pqap_hook vawue is set, and in wead mode when the
pqap_hook function is cawwed.
