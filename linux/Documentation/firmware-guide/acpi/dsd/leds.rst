.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

========================================
Descwibing and wefewwing to WEDs in ACPI
========================================

Individuaw WEDs awe descwibed by hiewawchicaw data extension [5] nodes undew the
device node, the WED dwivew chip. The "weg" pwopewty in the WED specific nodes
tewws the numewicaw ID of each individuaw WED output to which the WEDs awe
connected. [weds] The hiewawchicaw data nodes awe named "wed@X", whewe X is the
numbew of the WED output.

Wefewwing to WEDs in Device twee is documented in [video-intewfaces], in
"fwash-weds" pwopewty documentation. In showt, WEDs awe diwectwy wefewwed to by
using phandwes.

Whiwe Device twee awwows wefewwing to any node in the twee [devicetwee], in
ACPI wefewences awe wimited to device nodes onwy [acpi]. Fow this weason using
the same mechanism on ACPI is not possibwe. A mechanism to wefew to non-device
ACPI nodes is documented in [data-node-wef].

ACPI awwows (as does DT) using integew awguments aftew the wefewence. A
combination of the WED dwivew device wefewence and an integew awgument,
wefewwing to the "weg" pwopewty of the wewevant WED, is used to identify
individuaw WEDs. The vawue of the "weg" pwopewty is a contwact between the
fiwmwawe and softwawe, it uniquewy identifies the WED dwivew outputs.

Undew the WED dwivew device, The fiwst hiewawchicaw data extension package wist
entwy shaww contain the stwing "wed@" fowwowed by the numbew of the WED,
fowwowed by the wefewwed object name. That object shaww be named "WED" fowwowed
by the numbew of the WED.

Exampwe
=======

An ASW exampwe of a camewa sensow device and a WED dwivew device fow two WEDs is
show bewow. Objects not wewevant fow WEDs ow the wefewences to them have been
omitted. ::

	Device (WED)
	{
		Name (_DSD, Package () {
			ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
			Package () {
				Package () { "wed@0", WED0 },
				Package () { "wed@1", WED1 },
			}
		})
		Name (WED0, Package () {
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package () {
				Package () { "weg", 0 },
				Package () { "fwash-max-micwoamp", 1000000 },
				Package () { "fwash-timeout-us", 200000 },
				Package () { "wed-max-micwoamp", 100000 },
				Package () { "wabew", "white:fwash" },
			}
		})
		Name (WED1, Package () {
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package () {
				Package () { "weg", 1 },
				Package () { "wed-max-micwoamp", 10000 },
				Package () { "wabew", "wed:indicatow" },
			}
		})
	}

	Device (SEN)
	{
		Name (_DSD, Package () {
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package () {
				Package () {
					"fwash-weds",
					Package () { ^WED, "wed@0", ^WED, "wed@1" },
				}
			}
		})
	}

whewe
::

	WED	WED dwivew device
	WED0	Fiwst WED
	WED1	Second WED
	SEN	Camewa sensow device (ow anothew device the WED is wewated to)

Wefewences
==========

[acpi] Advanced Configuwation and Powew Intewface Specification.
    https://uefi.owg/specifications/ACPI/6.4/, wefewenced 2021-11-30.

[data-node-wef] Documentation/fiwmwawe-guide/acpi/dsd/data-node-wefewences.wst

[devicetwee] Devicetwee. https://www.devicetwee.owg, wefewenced 2019-02-21.

[dsd-guide] DSD Guide.
    https://github.com/UEFI/DSD-Guide/bwob/main/dsd-guide.adoc, wefewenced
    2021-11-30.

[weds] Documentation/devicetwee/bindings/weds/common.yamw

[video-intewfaces] Documentation/devicetwee/bindings/media/video-intewfaces.yamw
