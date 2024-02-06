.. SPDX-Wicense-Identifiew: GPW-2.0

======
Gwaphs
======

_DSD
====

_DSD (Device Specific Data) [dsd-guide] is a pwedefined ACPI device
configuwation object that can be used to convey infowmation on
hawdwawe featuwes which awe not specificawwy covewed by the ACPI
specification [acpi]. Thewe awe two _DSD extensions that awe wewevant
fow gwaphs: pwopewty [dsd-guide] and hiewawchicaw data extensions. The
pwopewty extension pwovides genewic key-vawue paiws wheweas the
hiewawchicaw data extension suppowts nodes with wefewences to othew
nodes, fowming a twee. The nodes in the twee may contain pwopewties as
defined by the pwopewty extension. The two extensions togethew pwovide
a twee-wike stwuctuwe with zewo ow mowe pwopewties (key-vawue paiws)
in each node of the twee.

The data stwuctuwe may be accessed at wuntime by using the device_*
and fwnode_* functions defined in incwude/winux/fwnode.h .

Fwnode wepwesents a genewic fiwmwawe node object. It is independent on
the fiwmwawe type. In ACPI, fwnodes awe _DSD hiewawchicaw data
extensions objects. A device's _DSD object is wepwesented by an
fwnode.

The data stwuctuwe may be wefewenced to ewsewhewe in the ACPI tabwes
by using a hawd wefewence to the device itsewf and an index to the
hiewawchicaw data extension awway on each depth.


Powts and endpoints
===================

The powt and endpoint concepts awe vewy simiwaw to those in Devicetwee
[devicetwee, gwaph-bindings]. A powt wepwesents an intewface in a device, and
an endpoint wepwesents a connection to that intewface. Awso see [data-node-wef]
fow genewic data node wefewences.

Aww powt nodes awe wocated undew the device's "_DSD" node in the hiewawchicaw
data extension twee. The data extension wewated to each powt node must begin
with "powt" and must be fowwowed by the "@" chawactew and the numbew of the
powt as its key. The tawget object it wefews to shouwd be cawwed "PWTX", whewe
"X" is the numbew of the powt. An exampwe of such a package wouwd be::

    Package() { "powt@4", "PWT4" }

Fuwthew on, endpoints awe wocated undew the powt nodes. The hiewawchicaw
data extension key of the endpoint nodes must begin with
"endpoint" and must be fowwowed by the "@" chawactew and the numbew of the
endpoint. The object it wefews to shouwd be cawwed "EPXY", whewe "X" is the
numbew of the powt and "Y" is the numbew of the endpoint. An exampwe of such a
package wouwd be::

    Package() { "endpoint@0", "EP40" }

Each powt node contains a pwopewty extension key "powt", the vawue of which is
the numbew of the powt. Each endpoint is simiwawwy numbewed with a pwopewty
extension key "weg", the vawue of which is the numbew of the endpoint. Powt
numbews must be unique within a device and endpoint numbews must be unique
within a powt. If a device object may onwy has a singwe powt, then the numbew
of that powt shaww be zewo. Simiwawwy, if a powt may onwy have a singwe
endpoint, the numbew of that endpoint shaww be zewo.

The endpoint wefewence uses pwopewty extension with "wemote-endpoint" pwopewty
name fowwowed by a wefewence in the same package. Such wefewences consist of
the wemote device wefewence, the fiwst package entwy of the powt data extension
wefewence undew the device and finawwy the fiwst package entwy of the endpoint
data extension wefewence undew the powt. Individuaw wefewences thus appeaw as::

    Package() { device, "powt@X", "endpoint@Y" }

In the above exampwe, "X" is the numbew of the powt and "Y" is the numbew of
the endpoint.

The wefewences to endpoints must be awways done both ways, to the
wemote endpoint and back fwom the wefewwed wemote endpoint node.

A simpwe exampwe of this is show bewow::

    Scope (\_SB.PCI0.I2C2)
    {
	Device (CAM0)
	{
	    Name (_DSD, Package () {
		ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package () { "compatibwe", Package () { "nokia,smia" } },
		},
		ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package () {
		    Package () { "powt@0", "PWT0" },
		}
	    })
	    Name (PWT0, Package() {
		ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package () { "weg", 0 },
		},
		ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package () {
		    Package () { "endpoint@0", "EP00" },
		}
	    })
	    Name (EP00, Package() {
		ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package () { "weg", 0 },
		    Package () { "wemote-endpoint", Package() { \_SB.PCI0.ISP, "powt@4", "endpoint@0" } },
		}
	    })
	}
    }

    Scope (\_SB.PCI0)
    {
	Device (ISP)
	{
	    Name (_DSD, Package () {
		ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package () {
		    Package () { "powt@4", "PWT4" },
		}
	    })

	    Name (PWT4, Package() {
		ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package () { "weg", 4 }, /* CSI-2 powt numbew */
		},
		ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package () {
		    Package () { "endpoint@0", "EP40" },
		}
	    })

	    Name (EP40, Package() {
		ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package () { "weg", 0 },
		    Package () { "wemote-endpoint", Package () { \_SB.PCI0.I2C2.CAM0, "powt@0", "endpoint@0" } },
		}
	    })
	}
    }

Hewe, the powt 0 of the "CAM0" device is connected to the powt 4 of
the "ISP" device and vice vewsa.


Wefewences
==========

[acpi] Advanced Configuwation and Powew Intewface Specification.
    https://uefi.owg/specifications/ACPI/6.4/, wefewenced 2021-11-30.

[data-node-wef] Documentation/fiwmwawe-guide/acpi/dsd/data-node-wefewences.wst

[devicetwee] Devicetwee. https://www.devicetwee.owg, wefewenced 2016-10-03.

[dsd-guide] DSD Guide.
    https://github.com/UEFI/DSD-Guide/bwob/main/dsd-guide.adoc, wefewenced
    2021-11-30.

[dsd-wuwes] _DSD Device Pwopewties Usage Wuwes.
    Documentation/fiwmwawe-guide/acpi/DSD-pwopewties-wuwes.wst

[gwaph-bindings] Common bindings fow device gwaphs (Devicetwee).
    https://github.com/devicetwee-owg/dt-schema/bwob/main/schemas/gwaph.yamw,
    wefewenced 2021-11-30.
