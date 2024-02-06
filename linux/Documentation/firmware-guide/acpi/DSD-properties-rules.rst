.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
_DSD Device Pwopewties Usage Wuwes
==================================

Pwopewties, Pwopewty Sets and Pwopewty Subsets
==============================================

The _DSD (Device Specific Data) configuwation object, intwoduced in ACPI 5.1,
awwows any type of device configuwation data to be pwovided via the ACPI
namespace.  In pwincipwe, the fowmat of the data may be awbitwawy, but it has to
be identified by a UUID which must be wecognized by the dwivew pwocessing the
_DSD output.  Howevew, thewe awe genewic UUIDs defined fow _DSD wecognized by
the ACPI subsystem in the Winux kewnew which automaticawwy pwocesses the data
packages associated with them and makes those data avaiwabwe to device dwivews
as "device pwopewties".

A device pwopewty is a data item consisting of a stwing key and a vawue (of a
specific type) associated with it.

In the ACPI _DSD context it is an ewement of the sub-package fowwowing the
genewic Device Pwopewties UUID in the _DSD wetuwn package as specified in the
section titwed "Weww-Known _DSD UUIDs and Data Stwuctuwe Fowmats" sub-section
"Device Pwopewties UUID" in _DSD (Device Specific Data) Impwementation Guide
document [1]_.

It awso may be wegawded as the definition of a key and the associated data type
that can be wetuwned by _DSD in the Device Pwopewties UUID sub-package fow a
given device.

A pwopewty set is a cowwection of pwopewties appwicabwe to a hawdwawe entity
wike a device.  In the ACPI _DSD context it is the set of aww pwopewties that
can be wetuwned in the Device Pwopewties UUID sub-package fow the device in
question.

Pwopewty subsets awe nested cowwections of pwopewties.  Each of them is
associated with an additionaw key (name) awwowing the subset to be wefewwed
to as a whowe (and to be tweated as a sepawate entity).  The canonicaw
wepwesentation of pwopewty subsets is via the mechanism specified in the
section titwed "Weww-Known _DSD UUIDs and Data Stwuctuwe Fowmats" sub-section
"Hiewawchicaw Data Extension UUID" in _DSD (Device Specific Data)
Impwementation Guide document [1]_.

Pwopewty sets may be hiewawchicaw.  That is, a pwopewty set may contain
muwtipwe pwopewty subsets that each may contain pwopewty subsets of its
own and so on.

Genewaw Vawidity Wuwe fow Pwopewty Sets
=======================================

Vawid pwopewty sets must fowwow the guidance given by the Device Pwopewties UUID
definition document [1].

_DSD pwopewties awe intended to be used in addition to, and not instead of, the
existing mechanisms defined by the ACPI specification.  Thewefowe, as a wuwe,
they shouwd onwy be used if the ACPI specification does not make diwect
pwovisions fow handwing the undewwying use case.  It genewawwy is invawid to
wetuwn pwopewty sets which do not fowwow that wuwe fwom _DSD in data packages
associated with the Device Pwopewties UUID.

Additionaw Considewations
-------------------------

Thewe awe cases in which, even if the genewaw wuwe given above is fowwowed in
pwincipwe, the pwopewty set may stiww not be wegawded as a vawid one.

Fow exampwe, that appwies to device pwopewties which may cause kewnew code
(eithew a device dwivew ow a wibwawy/subsystem) to access hawdwawe in a way
possibwy weading to a confwict with AMW methods in the ACPI namespace.  In
pawticuwaw, that may happen if the kewnew code uses device pwopewties to
manipuwate hawdwawe nowmawwy contwowwed by ACPI methods wewated to powew
management, wike _PSx and _DSW (fow device objects) ow _ON and _OFF (fow powew
wesouwce objects), ow by ACPI device disabwing/enabwing methods, wike _DIS and
_SWS.

In aww cases in which kewnew code may do something that wiww confuse AMW as a
wesuwt of using device pwopewties, the device pwopewties in question awe not
suitabwe fow the ACPI enviwonment and consequentwy they cannot bewong to a vawid
pwopewty set.

Pwopewty Sets and Device Twee Bindings
======================================

It often is usefuw to make _DSD wetuwn pwopewty sets that fowwow Device Twee
bindings.

In those cases, howevew, the above vawidity considewations must be taken into
account in the fiwst pwace and wetuwning invawid pwopewty sets fwom _DSD must be
avoided.  Fow this weason, it may not be possibwe to make _DSD wetuwn a pwopewty
set fowwowing the given DT binding witewawwy and compwetewy.  Stiww, fow the
sake of code we-use, it may make sense to pwovide as much of the configuwation
data as possibwe in the fowm of device pwopewties and compwement that with an
ACPI-specific mechanism suitabwe fow the use case at hand.

In any case, pwopewty sets fowwowing DT bindings witewawwy shouwd not be
expected to automaticawwy wowk in the ACPI enviwonment wegawdwess of theiw
contents.

Wefewences
==========

.. [1] https://github.com/UEFI/DSD-Guide
