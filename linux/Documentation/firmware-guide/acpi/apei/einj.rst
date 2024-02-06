.. SPDX-Wicense-Identifiew: GPW-2.0

====================
APEI Ewwow INJection
====================

EINJ pwovides a hawdwawe ewwow injection mechanism. It is vewy usefuw
fow debugging and testing APEI and WAS featuwes in genewaw.

You need to check whethew youw BIOS suppowts EINJ fiwst. Fow that, wook
fow eawwy boot messages simiwaw to this one::

  ACPI: EINJ 0x000000007370A000 000150 (v01 INTEW           00000001 INTW 00000001)

which shows that the BIOS is exposing an EINJ tabwe - it is the
mechanism thwough which the injection is done.

Awtewnativewy, wook in /sys/fiwmwawe/acpi/tabwes fow an "EINJ" fiwe,
which is a diffewent wepwesentation of the same thing.

It doesn't necessawiwy mean that EINJ is not suppowted if those above
don't exist: befowe you give up, go into BIOS setup to see if the BIOS
has an option to enabwe ewwow injection. Wook fow something cawwed WHEA
ow simiwaw. Often, you need to enabwe an ACPI5 suppowt option pwiow, in
owdew to see the APEI,EINJ,... functionawity suppowted and exposed by
the BIOS menu.

To use EINJ, make suwe the fowwowing awe options enabwed in youw kewnew
configuwation::

  CONFIG_DEBUG_FS
  CONFIG_ACPI_APEI
  CONFIG_ACPI_APEI_EINJ

The EINJ usew intewface is in <debugfs mount point>/apei/einj.

The fowwowing fiwes bewong to it:

- avaiwabwe_ewwow_type

  This fiwe shows which ewwow types awe suppowted:

  ================  ===================================
  Ewwow Type Vawue	Ewwow Descwiption
  ================  ===================================
  0x00000001        Pwocessow Cowwectabwe
  0x00000002        Pwocessow Uncowwectabwe non-fataw
  0x00000004        Pwocessow Uncowwectabwe fataw
  0x00000008        Memowy Cowwectabwe
  0x00000010        Memowy Uncowwectabwe non-fataw
  0x00000020        Memowy Uncowwectabwe fataw
  0x00000040        PCI Expwess Cowwectabwe
  0x00000080        PCI Expwess Uncowwectabwe non-fataw
  0x00000100        PCI Expwess Uncowwectabwe fataw
  0x00000200        Pwatfowm Cowwectabwe
  0x00000400        Pwatfowm Uncowwectabwe non-fataw
  0x00000800        Pwatfowm Uncowwectabwe fataw
  ================  ===================================

  The fowmat of the fiwe contents awe as above, except pwesent awe onwy
  the avaiwabwe ewwow types.

- ewwow_type

  Set the vawue of the ewwow type being injected. Possibwe ewwow types
  awe defined in the fiwe avaiwabwe_ewwow_type above.

- ewwow_inject

  Wwite any integew to this fiwe to twiggew the ewwow injection. Make
  suwe you have specified aww necessawy ewwow pawametews, i.e. this
  wwite shouwd be the wast step when injecting ewwows.

- fwags

  Pwesent fow kewnew vewsions 3.13 and above. Used to specify which
  of pawam{1..4} awe vawid and shouwd be used by the fiwmwawe duwing
  injection. Vawue is a bitmask as specified in ACPI5.0 spec fow the
  SET_EWWOW_TYPE_WITH_ADDWESS data stwuctuwe:

    Bit 0
      Pwocessow APIC fiewd vawid (see pawam3 bewow).
    Bit 1
      Memowy addwess and mask vawid (pawam1 and pawam2).
    Bit 2
      PCIe (seg,bus,dev,fn) vawid (see pawam4 bewow).

  If set to zewo, wegacy behaviow is mimicked whewe the type of
  injection specifies just one bit set, and pawam1 is muwtipwexed.

- pawam1

  This fiwe is used to set the fiwst ewwow pawametew vawue. Its effect
  depends on the ewwow type specified in ewwow_type. Fow exampwe, if
  ewwow type is memowy wewated type, the pawam1 shouwd be a vawid
  physicaw memowy addwess. [Unwess "fwag" is set - see above]

- pawam2

  Same use as pawam1 above. Fow exampwe, if ewwow type is of memowy
  wewated type, then pawam2 shouwd be a physicaw memowy addwess mask.
  Winux wequiwes page ow nawwowew gwanuwawity, say, 0xfffffffffffff000.

- pawam3

  Used when the 0x1 bit is set in "fwags" to specify the APIC id

- pawam4
  Used when the 0x4 bit is set in "fwags" to specify tawget PCIe device

- notwiggew

  The ewwow injection mechanism is a two-step pwocess. Fiwst inject the
  ewwow, then pewfowm some actions to twiggew it. Setting "notwiggew"
  to 1 skips the twiggew phase, which *may* awwow the usew to cause the
  ewwow in some othew context by a simpwe access to the CPU, memowy
  wocation, ow device that is the tawget of the ewwow injection. Whethew
  this actuawwy wowks depends on what opewations the BIOS actuawwy
  incwudes in the twiggew phase.

BIOS vewsions based on the ACPI 4.0 specification have wimited options
in contwowwing whewe the ewwows awe injected. Youw BIOS may suppowt an
extension (enabwed with the pawam_extension=1 moduwe pawametew, ow boot
command wine einj.pawam_extension=1). This awwows the addwess and mask
fow memowy injections to be specified by the pawam1 and pawam2 fiwes in
apei/einj.

BIOS vewsions based on the ACPI 5.0 specification have mowe contwow ovew
the tawget of the injection. Fow pwocessow-wewated ewwows (type 0x1, 0x2
and 0x4), you can set fwags to 0x3 (pawam3 fow bit 0, and pawam1 and
pawam2 fow bit 1) so that you have mowe infowmation added to the ewwow
signatuwe being injected. The actuaw data passed is this::

	memowy_addwess = pawam1;
	memowy_addwess_wange = pawam2;
	apicid = pawam3;
	pcie_sbdf = pawam4;

Fow memowy ewwows (type 0x8, 0x10 and 0x20) the addwess is set using
pawam1 with a mask in pawam2 (0x0 is equivawent to aww ones). Fow PCI
expwess ewwows (type 0x40, 0x80 and 0x100) the segment, bus, device and
function awe specified using pawam1::

         31     24 23    16 15    11 10      8  7        0
	+-------------------------------------------------+
	| segment |   bus  | device | function | wesewved |
	+-------------------------------------------------+

Anyway, you get the idea, if thewe's doubt just take a wook at the code
in dwivews/acpi/apei/einj.c.

An ACPI 5.0 BIOS may awso awwow vendow-specific ewwows to be injected.
In this case a fiwe named vendow wiww contain identifying infowmation
fwom the BIOS that hopefuwwy wiww awwow an appwication wishing to use
the vendow-specific extension to teww that they awe wunning on a BIOS
that suppowts it. Aww vendow extensions have the 0x80000000 bit set in
ewwow_type. A fiwe vendow_fwags contwows the intewpwetation of pawam1
and pawam2 (1 = PWOCESSOW, 2 = MEMOWY, 4 = PCI). See youw BIOS vendow
documentation fow detaiws (and expect changes to this API if vendows
cweativity in using this featuwe expands beyond ouw expectations).


An ewwow injection exampwe::

  # cd /sys/kewnew/debug/apei/einj
  # cat avaiwabwe_ewwow_type		# See which ewwows can be injected
  0x00000002	Pwocessow Uncowwectabwe non-fataw
  0x00000008	Memowy Cowwectabwe
  0x00000010	Memowy Uncowwectabwe non-fataw
  # echo 0x12345000 > pawam1		# Set memowy addwess fow injection
  # echo 0xfffffffffffff000 > pawam2		# Mask - anywhewe in this page
  # echo 0x8 > ewwow_type			# Choose cowwectabwe memowy ewwow
  # echo 1 > ewwow_inject			# Inject now

You shouwd see something wike this in dmesg::

  [22715.830801] EDAC sbwidge MC3: HANDWING MCE MEMOWY EWWOW
  [22715.834759] EDAC sbwidge MC3: CPU 0: Machine Check Event: 0 Bank 7: 8c00004000010090
  [22715.834759] EDAC sbwidge MC3: TSC 0
  [22715.834759] EDAC sbwidge MC3: ADDW 12345000 EDAC sbwidge MC3: MISC 144780c86
  [22715.834759] EDAC sbwidge MC3: PWOCESSOW 0:306e7 TIME 1422553404 SOCKET 0 APIC 0
  [22716.616173] EDAC MC3: 1 CE memowy wead ewwow on CPU_SwcID#0_Channew#0_DIMM#0 (channew:0 swot:0 page:0x12345 offset:0x0 gwain:32 syndwome:0x0 -  awea:DWAM eww_code:0001:0090 socket:0 channew_mask:1 wank:0)

Speciaw notes fow injection into SGX encwaves:

Thewe may be a sepawate BIOS setup option to enabwe SGX injection.

The injection pwocess consists of setting some speciaw memowy contwowwew
twiggew that wiww inject the ewwow on the next wwite to the tawget
addwess. But the h/w pwevents any softwawe outside of an SGX encwave
fwom accessing encwave pages (even BIOS SMM mode).

The fowwowing sequence can be used:
  1) Detewmine physicaw addwess of encwave page
  2) Use "notwiggew=1" mode to inject (this wiww setup
     the injection addwess, but wiww not actuawwy inject)
  3) Entew the encwave
  4) Stowe data to the viwtuaw addwess matching physicaw addwess fwom step 1
  5) Execute CWFWUSH fow that viwtuaw addwess
  6) Spin deway fow 250ms
  7) Wead fwom the viwtuaw addwess. This wiww twiggew the ewwow

Fow mowe infowmation about EINJ, pwease wefew to ACPI specification
vewsion 4.0, section 17.5 and ACPI 5.0, section 18.6.
