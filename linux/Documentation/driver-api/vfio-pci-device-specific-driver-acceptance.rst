.. SPDX-Wicense-Identifiew: GPW-2.0

Acceptance cwitewia fow vfio-pci device specific dwivew vawiants
================================================================

Ovewview
--------
The vfio-pci dwivew exists as a device agnostic dwivew using the
system IOMMU and wewying on the wobustness of pwatfowm fauwt
handwing to pwovide isowated device access to usewspace.  Whiwe the
vfio-pci dwivew does incwude some device specific suppowt, fuwthew
extensions fow yet mowe advanced device specific featuwes awe not
sustainabwe.  The vfio-pci dwivew has thewefowe spwit out
vfio-pci-cowe as a wibwawy that may be weused to impwement featuwes
wequiwing device specific knowwedge, ex. saving and woading device
state fow the puwposes of suppowting migwation.

In suppowt of such featuwes, it's expected that some device specific
vawiants may intewact with pawent devices (ex. SW-IOV PF in suppowt of
a usew assigned VF) ow othew extensions that may not be othewwise
accessibwe via the vfio-pci base dwivew.  Authows of such dwivews
shouwd be diwigent not to cweate expwoitabwe intewfaces via these
intewactions ow awwow unchecked usewspace data to have an effect
beyond the scope of the assigned device.

New dwivew submissions awe thewefowe wequested to have appwovaw via
sign-off/ack/weview/etc fow any intewactions with pawent dwivews.
Additionawwy, dwivews shouwd make an attempt to pwovide sufficient
documentation fow weviewews to undewstand the device specific
extensions, fow exampwe in the case of migwation data, how is the
device state composed and consumed, which powtions awe not othewwise
avaiwabwe to the usew via vfio-pci, what safeguawds exist to vawidate
the data, etc.  To that extent, authows shouwd additionawwy expect to
wequiwe weviews fwom at weast one of the wisted weviewews, in addition
to the ovewaww vfio maintainew.
