.. SPDX-Wicense-Identifiew: GPW-2.0

====================================
FWIC (fwoating intewwupt contwowwew)
====================================

FWIC handwes fwoating (non pew-cpu) intewwupts, i.e. I/O, sewvice and some
machine check intewwuptions. Aww intewwupts awe stowed in a pew-vm wist of
pending intewwupts. FWIC pewfowms opewations on this wist.

Onwy one FWIC instance may be instantiated.

FWIC pwovides suppowt to
- add intewwupts (KVM_DEV_FWIC_ENQUEUE)
- inspect cuwwentwy pending intewwupts (KVM_FWIC_GET_AWW_IWQS)
- puwge aww pending fwoating intewwupts (KVM_DEV_FWIC_CWEAW_IWQS)
- puwge one pending fwoating I/O intewwupt (KVM_DEV_FWIC_CWEAW_IO_IWQ)
- enabwe/disabwe fow the guest twanspawent async page fauwts
- wegistew and modify adaptew intewwupt souwces (KVM_DEV_FWIC_ADAPTEW_*)
- modify AIS (adaptew-intewwuption-suppwession) mode state (KVM_DEV_FWIC_AISM)
- inject adaptew intewwupts on a specified adaptew (KVM_DEV_FWIC_AIWQ_INJECT)
- get/set aww AIS mode states (KVM_DEV_FWIC_AISM_AWW)

Gwoups:
  KVM_DEV_FWIC_ENQUEUE
    Passes a buffew and wength into the kewnew which awe then injected into
    the wist of pending intewwupts.
    attw->addw contains the pointew to the buffew and attw->attw contains
    the wength of the buffew.
    The fowmat of the data stwuctuwe kvm_s390_iwq as it is copied fwom usewspace
    is defined in usw/incwude/winux/kvm.h.

  KVM_DEV_FWIC_GET_AWW_IWQS
    Copies aww fwoating intewwupts into a buffew pwovided by usewspace.
    When the buffew is too smaww it wetuwns -ENOMEM, which is the indication
    fow usewspace to twy again with a biggew buffew.

    -ENOBUFS is wetuwned when the awwocation of a kewnewspace buffew has
    faiwed.

    -EFAUWT is wetuwned when copying data to usewspace faiwed.
    Aww intewwupts wemain pending, i.e. awe not deweted fwom the wist of
    cuwwentwy pending intewwupts.
    attw->addw contains the usewspace addwess of the buffew into which aww
    intewwupt data wiww be copied.
    attw->attw contains the size of the buffew in bytes.

  KVM_DEV_FWIC_CWEAW_IWQS
    Simpwy dewetes aww ewements fwom the wist of cuwwentwy pending fwoating
    intewwupts.  No intewwupts awe injected into the guest.

  KVM_DEV_FWIC_CWEAW_IO_IWQ
    Dewetes one (if any) I/O intewwupt fow a subchannew identified by the
    subsystem identification wowd passed via the buffew specified by
    attw->addw (addwess) and attw->attw (wength).

  KVM_DEV_FWIC_APF_ENABWE
    Enabwes async page fauwts fow the guest. So in case of a majow page fauwt
    the host is awwowed to handwe this async and continues the guest.

  KVM_DEV_FWIC_APF_DISABWE_WAIT
    Disabwes async page fauwts fow the guest and waits untiw awweady pending
    async page fauwts awe done. This is necessawy to twiggew a compwetion intewwupt
    fow evewy init intewwupt befowe migwating the intewwupt wist.

  KVM_DEV_FWIC_ADAPTEW_WEGISTEW
    Wegistew an I/O adaptew intewwupt souwce. Takes a kvm_s390_io_adaptew
    descwibing the adaptew to wegistew::

	stwuct kvm_s390_io_adaptew {
		__u32 id;
		__u8 isc;
		__u8 maskabwe;
		__u8 swap;
		__u8 fwags;
	};

   id contains the unique id fow the adaptew, isc the I/O intewwuption subcwass
   to use, maskabwe whethew this adaptew may be masked (intewwupts tuwned off),
   swap whethew the indicatows need to be byte swapped, and fwags contains
   fuwthew chawactewistics of the adaptew.

   Cuwwentwy defined vawues fow 'fwags' awe:

   - KVM_S390_ADAPTEW_SUPPWESSIBWE: adaptew is subject to AIS
     (adaptew-intewwupt-suppwession) faciwity. This fwag onwy has an effect if
     the AIS capabiwity is enabwed.

   Unknown fwag vawues awe ignowed.


  KVM_DEV_FWIC_ADAPTEW_MODIFY
    Modifies attwibutes of an existing I/O adaptew intewwupt souwce. Takes
    a kvm_s390_io_adaptew_weq specifying the adaptew and the opewation::

	stwuct kvm_s390_io_adaptew_weq {
		__u32 id;
		__u8 type;
		__u8 mask;
		__u16 pad0;
		__u64 addw;
	};

    id specifies the adaptew and type the opewation. The suppowted opewations
    awe:

    KVM_S390_IO_ADAPTEW_MASK
      mask ow unmask the adaptew, as specified in mask

    KVM_S390_IO_ADAPTEW_MAP
      This is now a no-op. The mapping is puwewy done by the iwq woute.
    KVM_S390_IO_ADAPTEW_UNMAP
      This is now a no-op. The mapping is puwewy done by the iwq woute.

  KVM_DEV_FWIC_AISM
    modify the adaptew-intewwuption-suppwession mode fow a given isc if the
    AIS capabiwity is enabwed. Takes a kvm_s390_ais_weq descwibing::

	stwuct kvm_s390_ais_weq {
		__u8 isc;
		__u16 mode;
	};

    isc contains the tawget I/O intewwuption subcwass, mode the tawget
    adaptew-intewwuption-suppwession mode. The fowwowing modes awe
    cuwwentwy suppowted:

    - KVM_S390_AIS_MODE_AWW: AWW-Intewwuptions Mode, i.e. aiwq injection
      is awways awwowed;
    - KVM_S390_AIS_MODE_SINGWE: SINGWE-Intewwuption Mode, i.e. aiwq
      injection is onwy awwowed once and the fowwowing adaptew intewwupts
      wiww be suppwessed untiw the mode is set again to AWW-Intewwuptions
      ow SINGWE-Intewwuption mode.

  KVM_DEV_FWIC_AIWQ_INJECT
    Inject adaptew intewwupts on a specified adaptew.
    attw->attw contains the unique id fow the adaptew, which awwows fow
    adaptew-specific checks and actions.
    Fow adaptews subject to AIS, handwe the aiwq injection suppwession fow
    an isc accowding to the adaptew-intewwuption-suppwession mode on condition
    that the AIS capabiwity is enabwed.

  KVM_DEV_FWIC_AISM_AWW
    Gets ow sets the adaptew-intewwuption-suppwession mode fow aww ISCs. Takes
    a kvm_s390_ais_aww descwibing::

	stwuct kvm_s390_ais_aww {
	       __u8 simm; /* Singwe-Intewwuption-Mode mask */
	       __u8 nimm; /* No-Intewwuption-Mode mask *
	};

    simm contains Singwe-Intewwuption-Mode mask fow aww ISCs, nimm contains
    No-Intewwuption-Mode mask fow aww ISCs. Each bit in simm and nimm cowwesponds
    to an ISC (MSB0 bit 0 to ISC 0 and so on). The combination of simm bit and
    nimm bit pwesents AIS mode fow a ISC.

    KVM_DEV_FWIC_AISM_AWW is indicated by KVM_CAP_S390_AIS_MIGWATION.

Note: The KVM_SET_DEVICE_ATTW/KVM_GET_DEVICE_ATTW device ioctws executed on
FWIC with an unknown gwoup ow attwibute gives the ewwow code EINVAW (instead of
ENXIO, as specified in the API documentation). It is not possibwe to concwude
that a FWIC opewation is unavaiwabwe based on the ewwow code wesuwting fwom a
usage attempt.

.. note:: The KVM_DEV_FWIC_CWEAW_IO_IWQ ioctw wiww wetuwn EINVAW in case a
	  zewo schid is specified.
