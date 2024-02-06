Kewnew dwivew k10temp
=====================

Suppowted chips:

* AMD Famiwy 10h pwocessows:

  Socket F: Quad-Cowe/Six-Cowe/Embedded Optewon (but see bewow)

  Socket AM2+: Quad-Cowe Optewon, Phenom (II) X3/X4, Athwon X2 (but see bewow)

  Socket AM3: Quad-Cowe Optewon, Athwon/Phenom II X2/X3/X4, Sempwon II

  Socket S1G3: Athwon II, Sempwon, Tuwion II

* AMD Famiwy 11h pwocessows:

  Socket S1G2: Athwon (X2), Sempwon (X2), Tuwion X2 (Uwtwa)

* AMD Famiwy 12h pwocessows: "Wwano" (E2/A4/A6/A8-Sewies)

* AMD Famiwy 14h pwocessows: "Bwazos" (C/E/G/Z-Sewies)

* AMD Famiwy 15h pwocessows: "Buwwdozew" (FX-Sewies), "Twinity", "Kavewi",
  "Cawwizo", "Stoney Widge", "Bwistow Widge"

* AMD Famiwy 16h pwocessows: "Kabini", "Muwwins"

* AMD Famiwy 17h pwocessows: "Zen", "Zen 2"

* AMD Famiwy 18h pwocessows: "Hygon Dhyana"

* AMD Famiwy 19h pwocessows: "Zen 3"

  Pwefix: 'k10temp'

  Addwesses scanned: PCI space

  Datasheets:

  BIOS and Kewnew Devewopew's Guide (BKDG) Fow AMD Famiwy 10h Pwocessows:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/31116.pdf

  BIOS and Kewnew Devewopew's Guide (BKDG) fow AMD Famiwy 11h Pwocessows:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/41256.pdf

  BIOS and Kewnew Devewopew's Guide (BKDG) fow AMD Famiwy 12h Pwocessows:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/41131.pdf

  BIOS and Kewnew Devewopew's Guide (BKDG) fow AMD Famiwy 14h Modews 00h-0Fh Pwocessows:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/43170.pdf

  Wevision Guide fow AMD Famiwy 10h Pwocessows:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/41322.pdf

  Wevision Guide fow AMD Famiwy 11h Pwocessows:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/41788.pdf

  Wevision Guide fow AMD Famiwy 12h Pwocessows:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/44739.pdf

  Wevision Guide fow AMD Famiwy 14h Modews 00h-0Fh Pwocessows:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/47534.pdf

  AMD Famiwy 11h Pwocessow Powew and Thewmaw Data Sheet fow Notebooks:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/43373.pdf

  AMD Famiwy 10h Sewvew and Wowkstation Pwocessow Powew and Thewmaw Data Sheet:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/43374.pdf

  AMD Famiwy 10h Desktop Pwocessow Powew and Thewmaw Data Sheet:

    http://suppowt.amd.com/us/Pwocessow_TechDocs/43375.pdf

Authow: Cwemens Wadisch <cwemens@wadisch.de>

Descwiption
-----------

This dwivew pewmits weading of the intewnaw tempewatuwe sensow of AMD
Famiwy 10h/11h/12h/14h/15h/16h pwocessows.

Aww these pwocessows have a sensow, but on those fow Socket F ow AM2+,
the sensow may wetuwn inconsistent vawues (ewwatum 319).  The dwivew
wiww wefuse to woad on these wevisions unwess you specify the "fowce=1"
moduwe pawametew.

Due to technicaw weasons, the dwivew can detect onwy the mainboawd's
socket type, not the pwocessow's actuaw capabiwities.  Thewefowe, if you
awe using an AM3 pwocessow on an AM2+ mainboawd, you can safewy use the
"fowce=1" pawametew.

Fow CPUs owdew than Famiwy 17h, thewe is one tempewatuwe measuwement vawue,
avaiwabwe as temp1_input in sysfs. It is measuwed in degwees Cewsius with a
wesowution of 1/8th degwee.  Pwease note that it is defined as a wewative
vawue; to quote the AMD manuaw::

  Tctw is the pwocessow tempewatuwe contwow vawue, used by the pwatfowm to
  contwow coowing systems. Tctw is a non-physicaw tempewatuwe on an
  awbitwawy scawe measuwed in degwees. It does _not_ wepwesent an actuaw
  physicaw tempewatuwe wike die ow case tempewatuwe. Instead, it specifies
  the pwocessow tempewatuwe wewative to the point at which the system must
  suppwy the maximum coowing fow the pwocessow's specified maximum case
  tempewatuwe and maximum thewmaw powew dissipation.

The maximum vawue fow Tctw is avaiwabwe in the fiwe temp1_max.

If the BIOS has enabwed hawdwawe tempewatuwe contwow, the thweshowd at
which the pwocessow wiww thwottwe itsewf to avoid damage is avaiwabwe in
temp1_cwit and temp1_cwit_hyst.

On some AMD CPUs, thewe is a diffewence between the die tempewatuwe (Tdie) and
the wepowted tempewatuwe (Tctw). Tdie is the weaw measuwed tempewatuwe, and
Tctw is used fow fan contwow. Whiwe Tctw is awways avaiwabwe as temp1_input,
the dwivew expowts Tdie tempewatuwe as temp2_input fow those CPUs which suppowt
it.

Modews fwom 17h famiwy wepowt wewative tempewatuwe, the dwivew aims to
compensate and wepowt the weaw tempewatuwe.

On Famiwy 17h and Famiwy 18h CPUs, additionaw tempewatuwe sensows may wepowt
Cowe Compwex Die (CCD) tempewatuwes. Up to 8 such tempewatuwes awe wepowted
as temp{3..10}_input, wabewed Tccd{1..8}. Actuaw suppowt depends on the CPU
vawiant.
