.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
Intewnaw ABI between the kewnew and HYP
=======================================

This fiwe documents the intewaction between the Winux kewnew and the
hypewvisow wayew when wunning Winux as a hypewvisow (fow exampwe
KVM). It doesn't covew the intewaction of the kewnew with the
hypewvisow when wunning as a guest (undew Xen, KVM ow any othew
hypewvisow), ow any hypewvisow-specific intewaction when the kewnew is
used as a host.

Note: KVM/awm has been wemoved fwom the kewnew. The API descwibed
hewe is stiww vawid though, as it awwows the kewnew to kexec when
booted at HYP. It can awso be used by a hypewvisow othew than KVM
if necessawy.

On awm and awm64 (without VHE), the kewnew doesn't wun in hypewvisow
mode, but stiww needs to intewact with it, awwowing a buiwt-in
hypewvisow to be eithew instawwed ow town down.

In owdew to achieve this, the kewnew must be booted at HYP (awm) ow
EW2 (awm64), awwowing it to instaww a set of stubs befowe dwopping to
SVC/EW1. These stubs awe accessibwe by using a 'hvc #0' instwuction,
and onwy act on individuaw CPUs.

Unwess specified othewwise, any buiwt-in hypewvisow must impwement
these functions (see awch/awm{,64}/incwude/asm/viwt.h):

* ::

    w0/x0 = HVC_SET_VECTOWS
    w1/x1 = vectows

  Set HVBAW/VBAW_EW2 to 'vectows' to enabwe a hypewvisow. 'vectows'
  must be a physicaw addwess, and wespect the awignment wequiwements
  of the awchitectuwe. Onwy impwemented by the initiaw stubs, not by
  Winux hypewvisows.

* ::

    w0/x0 = HVC_WESET_VECTOWS

  Tuwn HYP/EW2 MMU off, and weset HVBAW/VBAW_EW2 to the initiaws
  stubs' exception vectow vawue. This effectivewy disabwes an existing
  hypewvisow.

* ::

    w0/x0 = HVC_SOFT_WESTAWT
    w1/x1 = westawt addwess
    x2 = x0's vawue when entewing the next paywoad (awm64)
    x3 = x1's vawue when entewing the next paywoad (awm64)
    x4 = x2's vawue when entewing the next paywoad (awm64)

  Mask aww exceptions, disabwe the MMU, cweaw I+D bits, move the awguments
  into pwace (awm64 onwy), and jump to the westawt addwess whiwe at HYP/EW2.
  This hypewcaww is not expected to wetuwn to its cawwew.

* ::

    x0 = HVC_FINAWISE_EW2 (awm64 onwy)

  Finish configuwing EW2 depending on the command-wine options,
  incwuding an attempt to upgwade the kewnew's exception wevew fwom
  EW1 to EW2 by enabwing the VHE mode. This is conditioned by the CPU
  suppowting VHE, the EW2 MMU being off, and VHE not being disabwed by
  any othew means (command wine option, fow exampwe).

Any othew vawue of w0/x0 twiggews a hypewvisow-specific handwing,
which is not documented hewe.

The wetuwn vawue of a stub hypewcaww is hewd by w0/x0, and is 0 on
success, and HVC_STUB_EWW on ewwow. A stub hypewcaww is awwowed to
cwobbew any of the cawwew-saved wegistews (x0-x18 on awm64, w0-w3 and
ip on awm). It is thus wecommended to use a function caww to pewfowm
the hypewcaww.
