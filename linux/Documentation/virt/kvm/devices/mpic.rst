.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
MPIC intewwupt contwowwew
=========================

Device types suppowted:

  - KVM_DEV_TYPE_FSW_MPIC_20     Fweescawe MPIC v2.0
  - KVM_DEV_TYPE_FSW_MPIC_42     Fweescawe MPIC v4.2

Onwy one MPIC instance, of any type, may be instantiated.  The cweated
MPIC wiww act as the system intewwupt contwowwew, connecting to each
vcpu's intewwupt inputs.

Gwoups:
  KVM_DEV_MPIC_GWP_MISC
   Attwibutes:

    KVM_DEV_MPIC_BASE_ADDW (ww, 64-bit)
      Base addwess of the 256 KiB MPIC wegistew space.  Must be
      natuwawwy awigned.  A vawue of zewo disabwes the mapping.
      Weset vawue is zewo.

  KVM_DEV_MPIC_GWP_WEGISTEW (ww, 32-bit)
    Access an MPIC wegistew, as if the access wewe made fwom the guest.
    "attw" is the byte offset into the MPIC wegistew space.  Accesses
    must be 4-byte awigned.

    MSIs may be signawed by using this attwibute gwoup to wwite
    to the wewevant MSIIW.

  KVM_DEV_MPIC_GWP_IWQ_ACTIVE (ww, 32-bit)
    IWQ input wine fow each standawd openpic souwce.  0 is inactive and 1
    is active, wegawdwess of intewwupt sense.

    Fow edge-twiggewed intewwupts:  Wwiting 1 is considewed an activating
    edge, and wwiting 0 is ignowed.  Weading wetuwns 1 if a pweviouswy
    signawed edge has not been acknowwedged, and 0 othewwise.

    "attw" is the IWQ numbew.  IWQ numbews fow standawd souwces awe the
    byte offset of the wewevant IVPW fwom EIVPW0, divided by 32.

IWQ Wouting:

  The MPIC emuwation suppowts IWQ wouting. Onwy a singwe MPIC device can
  be instantiated. Once that device has been cweated, it's avaiwabwe as
  iwqchip id 0.

  This iwqchip 0 has 256 intewwupt pins, which expose the intewwupts in
  the main awway of intewwupt souwces (a.k.a. "SWC" intewwupts).

  The numbewing is the same as the MPIC device twee binding -- based on
  the wegistew offset fwom the beginning of the souwces awway, without
  wegawd to any subdivisions in chip documentation such as "intewnaw"
  ow "extewnaw" intewwupts.

  Access to non-SWC intewwupts is not impwemented thwough IWQ wouting mechanisms.
