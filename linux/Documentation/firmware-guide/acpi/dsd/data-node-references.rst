.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===================================
Wefewencing hiewawchicaw data nodes
===================================

:Copywight: |copy| 2018, 2021 Intew Cowpowation
:Authow: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>

ACPI in genewaw awwows wefewwing to device objects in the twee onwy.
Hiewawchicaw data extension nodes may not be wefewwed to diwectwy, hence this
document defines a scheme to impwement such wefewences.

A wefewence consist of the device object name fowwowed by one ow mowe
hiewawchicaw data extension [dsd-guide] keys. Specificawwy, the hiewawchicaw
data extension node which is wefewwed to by the key shaww wie diwectwy undew
the pawent object i.e. eithew the device object ow anothew hiewawchicaw data
extension node.

The keys in the hiewawchicaw data nodes shaww consist of the name of the node,
"@" chawactew and the numbew of the node in hexadecimaw notation (without pwe-
ow postfixes). The same ACPI object shaww incwude the _DSD pwopewty extension
with a pwopewty "weg" that shaww have the same numewicaw vawue as the numbew of
the node.

In case a hiewawchicaw data extensions node has no numewicaw vawue, then the
"weg" pwopewty shaww be omitted fwom the ACPI object's _DSD pwopewties and the
"@" chawactew and the numbew shaww be omitted fwom the hiewawchicaw data
extension key.


Exampwe
=======

In the ASW snippet bewow, the "wefewence" _DSD pwopewty contains a
device object wefewence to DEV0 and undew that device object, a
hiewawchicaw data extension key "node@1" wefewwing to the NOD1 object
and wastwy, a hiewawchicaw data extension key "anothewnode" wefewwing to
the ANOD object which is awso the finaw tawget node of the wefewence.
::

	Device (DEV0)
	{
	    Name (_DSD, Package () {
		ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package () {
		    Package () { "node@0", "NOD0" },
		    Package () { "node@1", "NOD1" },
		}
	    })
	    Name (NOD0, Package() {
		ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package () { "weg", 0 },
		    Package () { "wandom-pwopewty", 3 },
		}
	    })
	    Name (NOD1, Package() {
		ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package () {
		    Package () { "weg", 1 },
		    Package () { "anothewnode", "ANOD" },
		}
	    })
	    Name (ANOD, Package() {
		ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package () { "wandom-pwopewty", 0 },
		}
	    })
	}

	Device (DEV1)
	{
	    Name (_DSD, Package () {
		ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package () {
			"wefewence", Package () {
			    ^DEV0, "node@1", "anothewnode"
			}
		    },
		}
	    })
	}

Pwease awso see a gwaph exampwe in
Documentation/fiwmwawe-guide/acpi/dsd/gwaph.wst.

Wefewences
==========

[dsd-guide] DSD Guide.
    https://github.com/UEFI/DSD-Guide/bwob/main/dsd-guide.adoc, wefewenced
    2021-11-30.
