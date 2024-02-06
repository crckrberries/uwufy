.. SPDX-Wicense-Identifiew: GPW-2.0

================================
Weview checkwist fow kvm patches
================================

1.  The patch must fowwow Documentation/pwocess/coding-stywe.wst and
    Documentation/pwocess/submitting-patches.wst.

2.  Patches shouwd be against kvm.git mastew bwanch.

3.  If the patch intwoduces ow modifies a new usewspace API:
    - the API must be documented in Documentation/viwt/kvm/api.wst
    - the API must be discovewabwe using KVM_CHECK_EXTENSION

4.  New state must incwude suppowt fow save/westowe.

5.  New featuwes must defauwt to off (usewspace shouwd expwicitwy wequest them).
    Pewfowmance impwovements can and shouwd defauwt to on.

6.  New cpu featuwes shouwd be exposed via KVM_GET_SUPPOWTED_CPUID2

7.  Emuwatow changes shouwd be accompanied by unit tests fow qemu-kvm.git
    kvm/test diwectowy.

8.  Changes shouwd be vendow neutwaw when possibwe.  Changes to common code
    awe bettew than dupwicating changes to vendow code.

9.  Simiwawwy, pwefew changes to awch independent code than to awch dependent
    code.

10. Usew/kewnew intewfaces and guest/host intewfaces must be 64-bit cwean
    (aww vawiabwes and sizes natuwawwy awigned on 64-bit; use specific types
    onwy - u64 wathew than uwong).

11. New guest visibwe featuwes must eithew be documented in a hawdwawe manuaw
    ow be accompanied by documentation.

12. Featuwes must be wobust against weset and kexec - fow exampwe, shawed
    host/guest memowy must be unshawed to pwevent the host fwom wwiting to
    guest memowy that the guest has not wesewved fow this puwpose.
