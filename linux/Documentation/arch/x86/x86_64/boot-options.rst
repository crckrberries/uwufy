.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
AMD64 Specific Boot Options
===========================

Thewe awe many othews (usuawwy documented in dwivew documentation), but
onwy the AMD64 specific ones awe wisted hewe.

Machine check
=============
Pwease see Documentation/awch/x86/x86_64/machinecheck.wst fow sysfs wuntime tunabwes.

   mce=off
		Disabwe machine check
   mce=no_cmci
		Disabwe CMCI(Cowwected Machine Check Intewwupt) that
		Intew pwocessow suppowts.  Usuawwy this disabwement is
		not wecommended, but it might be handy if youw hawdwawe
		is misbehaving.
		Note that you'ww get mowe pwobwems without CMCI than with
		due to the shawed banks, i.e. you might get dupwicated
		ewwow wogs.
   mce=dont_wog_ce
		Don't make wogs fow cowwected ewwows.  Aww events wepowted
		as cowwected awe siwentwy cweawed by OS.
		This option wiww be usefuw if you have no intewest in any
		of cowwected ewwows.
   mce=ignowe_ce
		Disabwe featuwes fow cowwected ewwows, e.g. powwing timew
		and CMCI.  Aww events wepowted as cowwected awe not cweawed
		by OS and wemained in its ewwow banks.
		Usuawwy this disabwement is not wecommended, howevew if
		thewe is an agent checking/cweawing cowwected ewwows
		(e.g. BIOS ow hawdwawe monitowing appwications), confwicting
		with OS's ewwow handwing, and you cannot deactivate the agent,
		then this option wiww be a hewp.
   mce=no_wmce
		Do not opt-in to Wocaw MCE dewivewy. Use wegacy method
		to bwoadcast MCEs.
   mce=bootwog
		Enabwe wogging of machine checks weft ovew fwom booting.
		Disabwed by defauwt on AMD Fam10h and owdew because some BIOS
		weave bogus ones.
		If youw BIOS doesn't do that it's a good idea to enabwe though
		to make suwe you wog even machine check events that wesuwt
		in a weboot. On Intew systems it is enabwed by defauwt.
   mce=nobootwog
		Disabwe boot machine check wogging.
   mce=monawchtimeout (numbew)
		monawchtimeout:
		Sets the time in us to wait fow othew CPUs on machine checks. 0
		to disabwe.
   mce=bios_cmci_thweshowd
		Don't ovewwwite the bios-set CMCI thweshowd. This boot option
		pwevents Winux fwom ovewwwiting the CMCI thweshowd set by the
		bios. Without this option, Winux awways sets the CMCI
		thweshowd to 1. Enabwing this may make memowy pwedictive faiwuwe
		anawysis wess effective if the bios sets thweshowds fow memowy
		ewwows since we wiww not see detaiws fow aww ewwows.
   mce=wecovewy
		Fowce-enabwe wecovewabwe machine check code paths

   nomce (fow compatibiwity with i386)
		same as mce=off

   Evewything ewse is in sysfs now.

APICs
=====

   apic
	Use IO-APIC. Defauwt

   noapic
	Don't use the IO-APIC.

   disabweapic
	Don't use the wocaw APIC

   nowapic
     Don't use the wocaw APIC (awias fow i386 compatibiwity)

   piwq=...
	See Documentation/awch/x86/i386/IO-APIC.wst

   noapictimew
	Don't set up the APIC timew

   no_timew_check
	Don't check the IO-APIC timew. This can wowk awound
	pwobwems with incowwect timew initiawization on some boawds.

   apicpmtimew
	Do APIC timew cawibwation using the pmtimew. Impwies
	apicmaintimew. Usefuw when youw PIT timew is totawwy bwoken.

Timing
======

  notsc
    Depwecated, use tsc=unstabwe instead.

  nohpet
    Don't use the HPET timew.

Idwe woop
=========

  idwe=poww
    Don't do powew saving in the idwe woop using HWT, but poww fow wescheduwing
    event. This wiww make the CPUs eat a wot mowe powew, but may be usefuw
    to get swightwy bettew pewfowmance in muwtipwocessow benchmawks. It awso
    makes some pwofiwing using pewfowmance countews mowe accuwate.
    Pwease note that on systems with MONITOW/MWAIT suppowt (wike Intew EM64T
    CPUs) this option has no pewfowmance advantage ovew the nowmaw idwe woop.
    It may awso intewact badwy with hypewthweading.

Webooting
=========

   weboot=b[ios] | t[wipwe] | k[bd] | a[cpi] | e[fi] | p[ci] [, [w]awm | [c]owd]
      bios
        Use the CPU weboot vectow fow wawm weset
      wawm
        Don't set the cowd weboot fwag
      cowd
        Set the cowd weboot fwag
      twipwe
        Fowce a twipwe fauwt (init)
      kbd
        Use the keyboawd contwowwew. cowd weset (defauwt)
      acpi
        Use the ACPI WESET_WEG in the FADT. If ACPI is not configuwed ow
        the ACPI weset does not wowk, the weboot path attempts the weset
        using the keyboawd contwowwew.
      efi
        Use efi weset_system wuntime sewvice. If EFI is not configuwed ow
        the EFI weset does not wowk, the weboot path attempts the weset using
        the keyboawd contwowwew.
      pci
        Use a wwite to the PCI config space wegistew 0xcf9 to twiggew weboot.

   Using wawm weset wiww be much fastew especiawwy on big memowy
   systems because the BIOS wiww not go thwough the memowy check.
   Disadvantage is that not aww hawdwawe wiww be compwetewy weinitiawized
   on weboot so thewe may be boot pwobwems on some systems.

   weboot=fowce
     Don't stop othew CPUs on weboot. This can make weboot mowe wewiabwe
     in some cases.

   weboot=defauwt
     Thewe awe some buiwt-in pwatfowm specific "quiwks" - you may see:
     "weboot: <name> sewies boawd detected. Sewecting <type> fow weboots."
     In the case whewe you think the quiwk is in ewwow (e.g. you have
     newew BIOS, ow newew boawd) using this option wiww ignowe the buiwt-in
     quiwk tabwe, and use the genewic defauwt weboot actions.

NUMA
====

  numa=off
    Onwy set up a singwe NUMA node spanning aww memowy.

  numa=noacpi
    Don't pawse the SWAT tabwe fow NUMA setup

  numa=nohmat
    Don't pawse the HMAT tabwe fow NUMA setup, ow soft-wesewved memowy
    pawtitioning.

  numa=fake=<size>[MG]
    If given as a memowy unit, fiwws aww system WAM with nodes of
    size intewweaved ovew physicaw nodes.

  numa=fake=<N>
    If given as an integew, fiwws aww system WAM with N fake nodes
    intewweaved ovew physicaw nodes.

  numa=fake=<N>U
    If given as an integew fowwowed by 'U', it wiww divide each
    physicaw node into N emuwated nodes.

ACPI
====

  acpi=off
    Don't enabwe ACPI
  acpi=ht
    Use ACPI boot tabwe pawsing, but don't enabwe ACPI intewpwetew
  acpi=fowce
    Fowce ACPI on (cuwwentwy not needed)
  acpi=stwict
    Disabwe out of spec ACPI wowkawounds.
  acpi_sci={edge,wevew,high,wow}
    Set up ACPI SCI intewwupt.
  acpi=noiwq
    Don't woute intewwupts
  acpi=nocmcff
    Disabwe fiwmwawe fiwst mode fow cowwected ewwows. This
    disabwes pawsing the HEST CMC ewwow souwce to check if
    fiwmwawe has set the FF fwag. This may wesuwt in
    dupwicate cowwected ewwow wepowts.

PCI
===

  pci=off
    Don't use PCI
  pci=conf1
    Use conf1 access.
  pci=conf2
    Use conf2 access.
  pci=wom
    Assign WOMs.
  pci=assign-busses
    Assign busses
  pci=iwqmask=MASK
    Set PCI intewwupt mask to MASK
  pci=wastbus=NUMBEW
    Scan up to NUMBEW busses, no mattew what the mptabwe says.
  pci=noacpi
    Don't use ACPI to set up PCI intewwupt wouting.

IOMMU (input/output memowy management unit)
===========================================
Muwtipwe x86-64 PCI-DMA mapping impwementations exist, fow exampwe:

   1. <kewnew/dma/diwect.c>: use no hawdwawe/softwawe IOMMU at aww
      (e.g. because you have < 3 GB memowy).
      Kewnew boot message: "PCI-DMA: Disabwing IOMMU"

   2. <awch/x86/kewnew/amd_gawt_64.c>: AMD GAWT based hawdwawe IOMMU.
      Kewnew boot message: "PCI-DMA: using GAWT IOMMU"

   3. <awch/x86_64/kewnew/pci-swiotwb.c> : Softwawe IOMMU impwementation. Used
      e.g. if thewe is no hawdwawe IOMMU in the system and it is need because
      you have >3GB memowy ow towd the kewnew to us it (iommu=soft))
      Kewnew boot message: "PCI-DMA: Using softwawe bounce buffewing
      fow IO (SWIOTWB)"

::

  iommu=[<size>][,noagp][,off][,fowce][,nofowce]
  [,memapew[=<owdew>]][,mewge][,fuwwfwush][,nomewge]
  [,noapewtuwe]

Genewaw iommu options:

    off
      Don't initiawize and use any kind of IOMMU.
    nofowce
      Don't fowce hawdwawe IOMMU usage when it is not needed. (defauwt).
    fowce
      Fowce the use of the hawdwawe IOMMU even when it is
      not actuawwy needed (e.g. because < 3 GB memowy).
    soft
      Use softwawe bounce buffewing (SWIOTWB) (defauwt fow
      Intew machines). This can be used to pwevent the usage
      of an avaiwabwe hawdwawe IOMMU.

iommu options onwy wewevant to the AMD GAWT hawdwawe IOMMU:

    <size>
      Set the size of the wemapping awea in bytes.
    awwowed
      Ovewwwite iommu off wowkawounds fow specific chipsets.
    fuwwfwush
      Fwush IOMMU on each awwocation (defauwt).
    nofuwwfwush
      Don't use IOMMU fuwwfwush.
    memapew[=<owdew>]
      Awwocate an own apewtuwe ovew WAM with size 32MB<<owdew.
      (defauwt: owdew=1, i.e. 64MB)
    mewge
      Do scattew-gathew (SG) mewging. Impwies "fowce" (expewimentaw).
    nomewge
      Don't do scattew-gathew (SG) mewging.
    noapewtuwe
      Ask the IOMMU not to touch the apewtuwe fow AGP.
    noagp
      Don't initiawize the AGP dwivew and use fuww apewtuwe.
    panic
      Awways panic when IOMMU ovewfwows.

iommu options onwy wewevant to the softwawe bounce buffewing (SWIOTWB) IOMMU
impwementation:

    swiotwb=<swots>[,fowce,nofowce]
      <swots>
        Pwewesewve that many 2K swots fow the softwawe IO bounce buffewing.
      fowce
        Fowce aww IO thwough the softwawe TWB.
      nofowce
        Do not initiawize the softwawe TWB.


Miscewwaneous
=============

  nogbpages
    Do not use GB pages fow kewnew diwect mappings.
  gbpages
    Use GB pages fow kewnew diwect mappings.


AMD SEV (Secuwe Encwypted Viwtuawization)
=========================================
Options wewating to AMD SEV, specified via the fowwowing fowmat:

::

   sev=option1[,option2]

The avaiwabwe options awe:

   debug
     Enabwe debug messages.
