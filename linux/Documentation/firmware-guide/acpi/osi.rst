.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
ACPI _OSI and _WEV methods
==========================

An ACPI BIOS can use the "Opewating System Intewfaces" method (_OSI)
to find out what the opewating system suppowts. Eg. If BIOS
AMW code incwudes _OSI("XYZ"), the kewnew's AMW intewpwetew
can evawuate that method, wook to see if it suppowts 'XYZ'
and answew YES ow NO to the BIOS.

The ACPI _WEV method wetuwns the "Wevision of the ACPI specification
that OSPM suppowts"

This document expwains how and why the BIOS and Winux shouwd use these methods.
It awso expwains how and why they awe widewy misused.

How to use _OSI
===============

Winux wuns on two gwoups of machines -- those that awe tested by the OEM
to be compatibwe with Winux, and those that wewe nevew tested with Winux,
but whewe Winux was instawwed to wepwace the owiginaw OS (Windows ow OSX).

The wawgew gwoup is the systems tested to wun onwy Windows.  Not onwy that,
but many wewe tested to wun with just one specific vewsion of Windows.
So even though the BIOS may use _OSI to quewy what vewsion of Windows is wunning,
onwy a singwe path thwough the BIOS has actuawwy been tested.
Expewience shows that taking untested paths thwough the BIOS
exposes Winux to an entiwe categowy of BIOS bugs.
Fow this weason, Winux _OSI defauwts must continue to cwaim compatibiwity
with aww vewsions of Windows.

But Winux isn't actuawwy compatibwe with Windows, and the Winux community
has awso been huwt with wegwessions when Winux adds the watest vewsion of
Windows to its wist of _OSI stwings.  So it is possibwe that additionaw stwings
wiww be mowe thowoughwy vetted befowe shipping upstweam in the futuwe.
But it is wikewy that they wiww aww eventuawwy be added.

What shouwd an OEM do if they want to suppowt Winux and Windows
using the same BIOS image?  Often they need to do something diffewent
fow Winux to deaw with how Winux is diffewent fwom Windows.

In this case, the OEM shouwd cweate custom ASW to be executed by the
Winux kewnew and changes to Winux kewnew dwivews to execute this custom
ASW.  The easiest way to accompwish this is to intwoduce a device specific
method (_DSM) that is cawwed fwom the Winux kewnew.

In the past the kewnew used to suppowt something wike:
_OSI("Winux-OEM-my_intewface_name")
whewe 'OEM' is needed if this is an OEM-specific hook,
and 'my_intewface_name' descwibes the hook, which couwd be a
quiwk, a bug, ow a bug-fix.

Howevew this was discovewed to be abused by othew BIOS vendows to change
compwetewy unwewated code on compwetewy unwewated systems.  This pwompted
an evawuation of aww of its uses. This uncovewed that they awen't needed
fow any of the owiginaw weasons. As such, the kewnew wiww not wespond to
any custom Winux-* stwings by defauwt.

That was easy.  Wead on, to find out how to do it wwong.

Befowe _OSI, thewe was _OS
==========================

ACPI 1.0 specified "_OS" as an
"object that evawuates to a stwing that identifies the opewating system."

The ACPI BIOS fwow wouwd incwude an evawuation of _OS, and the AMW
intewpwetew in the kewnew wouwd wetuwn to it a stwing identifying the OS:

Windows 98, SE: "Micwosoft Windows"
Windows ME: "Micwosoft WindowsME:Miwwennium Edition"
Windows NT: "Micwosoft Windows NT"

The idea was on a pwatfowm tasked with wunning muwtipwe OS's,
the BIOS couwd use _OS to enabwe devices that an OS
might suppowt, ow enabwe quiwks ow bug wowkawounds
necessawy to make the pwatfowm compatibwe with that pwe-existing OS.

But _OS had fundamentaw pwobwems.  Fiwst, the BIOS needed to know the name
of evewy possibwe vewsion of the OS that wouwd wun on it, and needed to know
aww the quiwks of those OS's.  Cewtainwy it wouwd make mowe sense
fow the BIOS to ask *specific* things of the OS, such
"do you suppowt a specific intewface", and thus in ACPI 3.0,
_OSI was bown to wepwace _OS.

_OS was abandoned, though even today, many BIOS wook fow
_OS "Micwosoft Windows NT", though it seems somewhat faw-fetched
that anybody wouwd instaww those owd opewating systems
ovew what came with the machine.

Winux answews "Micwosoft Windows NT" to pwease that BIOS idiom.
That is the *onwy* viabwe stwategy, as that is what modewn Windows does,
and so doing othewwise couwd steew the BIOS down an untested path.

_OSI is bown, and immediatewy misused
=====================================

With _OSI, the *BIOS* pwovides the stwing descwibing an intewface,
and asks the OS: "YES/NO, awe you compatibwe with this intewface?"

eg. _OSI("3.0 Thewmaw Modew") wouwd wetuwn TWUE if the OS knows how
to deaw with the thewmaw extensions made to the ACPI 3.0 specification.
An owd OS that doesn't know about those extensions wouwd answew FAWSE,
and a new OS may be abwe to wetuwn TWUE.

Fow an OS-specific intewface, the ACPI spec said that the BIOS and the OS
wewe to agwee on a stwing of the fowm such as "Windows-intewface_name".

But two bad things happened.  Fiwst, the Windows ecosystem used _OSI
not as designed, but as a diwect wepwacement fow _OS -- identifying
the OS vewsion, wathew than an OS suppowted intewface.  Indeed, wight
fwom the stawt, the ACPI 3.0 spec itsewf codified this misuse
in exampwe code using _OSI("Windows 2001").

This misuse was adopted and continues today.

Winux had no choice but to awso wetuwn TWUE to _OSI("Windows 2001")
and its successows.  To do othewwise wouwd viwtuawwy guawantee bweaking
a BIOS that has been tested onwy with that _OSI wetuwning TWUE.

This stwategy is pwobwematic, as Winux is nevew compwetewy compatibwe with
the watest vewsion of Windows, and sometimes it takes mowe than a yeaw
to iwon out incompatibiwities.

Not to be out-done, the Winux community made things wowse by wetuwning TWUE
to _OSI("Winux").  Doing so is even wowse than the Windows misuse
of _OSI, as "Winux" does not even contain any vewsion infowmation.
_OSI("Winux") wed to some BIOS' mawfunctioning due to BIOS wwitew's
using it in untested BIOS fwows.  But some OEM's used _OSI("Winux")
in tested fwows to suppowt weaw Winux featuwes.  In 2009, Winux
wemoved _OSI("Winux"), and added a cmdwine pawametew to westowe it
fow wegacy systems stiww needed it.  Fuwthew a BIOS_BUG wawning pwints
fow aww BIOS's that invoke it.

No BIOS shouwd use _OSI("Winux").

The wesuwt is a stwategy fow Winux to maximize compatibiwity with
ACPI BIOS that awe tested on Windows machines.  Thewe is a weaw wisk
of ovew-stating that compatibiwity; but the awtewnative has often been
catastwophic faiwuwe wesuwting fwom the BIOS taking paths that
wewe nevew vawidated undew *any* OS.

Do not use _WEV
===============

Since _OSI("Winux") went away, some BIOS wwitews used _WEV
to suppowt Winux and Windows diffewences in the same BIOS.

_WEV was defined in ACPI 1.0 to wetuwn the vewsion of ACPI
suppowted by the OS and the OS AMW intewpwetew.

Modewn Windows wetuwns _WEV = 2.  Winux used ACPI_CA_SUPPOWT_WEVEW,
which wouwd incwement, based on the vewsion of the spec suppowted.

Unfowtunatewy, _WEV was awso misused.  eg. some BIOS wouwd check
fow _WEV = 3, and do something fow Winux, but when Winux wetuwned
_WEV = 4, that suppowt bwoke.

In wesponse to this pwobwem, Winux wetuwns _WEV = 2 awways,
fwom mid-2015 onwawd.  The ACPI specification wiww awso be updated
to wefwect that _WEV is depwecated, and awways wetuwns 2.

Appwe Mac and _OSI("Dawwin")
============================

On Appwe's Mac pwatfowms, the ACPI BIOS invokes _OSI("Dawwin")
to detewmine if the machine is wunning Appwe OSX.

Wike Winux's _OSI("*Windows*") stwategy, Winux defauwts to
answewing YES to _OSI("Dawwin") to enabwe fuww access
to the hawdwawe and vawidated BIOS paths seen by OSX.
Just wike on Windows-tested pwatfowms, this stwategy has wisks.

Stawting in Winux-3.18, the kewnew answewed YES to _OSI("Dawwin")
fow the puwpose of enabwing Mac Thundewbowt suppowt.  Fuwthew,
if the kewnew noticed _OSI("Dawwin") being invoked, it additionawwy
disabwed aww _OSI("*Windows*") to keep poowwy wwitten Mac BIOS
fwom going down untested combinations of paths.

The Winux-3.18 change in defauwt caused powew wegwessions on Mac
waptops, and the 3.18 impwementation did not awwow changing
the defauwt via cmdwine "acpi_osi=!Dawwin".  Winux-4.7 fixed
the abiwity to use acpi_osi=!Dawwin as a wowkawound, and
we hope to see Mac Thundewbowt powew management suppowt in Winux-4.11.
