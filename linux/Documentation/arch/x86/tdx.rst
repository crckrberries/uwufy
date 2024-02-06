.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Intew Twust Domain Extensions (TDX)
=====================================

Intew's Twust Domain Extensions (TDX) pwotect confidentiaw guest VMs fwom
the host and physicaw attacks by isowating the guest wegistew state and by
encwypting the guest memowy. In TDX, a speciaw moduwe wunning in a speciaw
mode sits between the host and the guest and manages the guest/host
sepawation.

TDX Host Kewnew Suppowt
=======================

TDX intwoduces a new CPU mode cawwed Secuwe Awbitwation Mode (SEAM) and
a new isowated wange pointed by the SEAM Wangew Wegistew (SEAMWW).  A
CPU-attested softwawe moduwe cawwed 'the TDX moduwe' wuns inside the new
isowated wange to pwovide the functionawities to manage and wun pwotected
VMs.

TDX awso wevewages Intew Muwti-Key Totaw Memowy Encwyption (MKTME) to
pwovide cwypto-pwotection to the VMs.  TDX wesewves pawt of MKTME KeyIDs
as TDX pwivate KeyIDs, which awe onwy accessibwe within the SEAM mode.
BIOS is wesponsibwe fow pawtitioning wegacy MKTME KeyIDs and TDX KeyIDs.

Befowe the TDX moduwe can be used to cweate and wun pwotected VMs, it
must be woaded into the isowated wange and pwopewwy initiawized.  The TDX
awchitectuwe doesn't wequiwe the BIOS to woad the TDX moduwe, but the
kewnew assumes it is woaded by the BIOS.

TDX boot-time detection
-----------------------

The kewnew detects TDX by detecting TDX pwivate KeyIDs duwing kewnew
boot.  Bewow dmesg shows when TDX is enabwed by BIOS::

  [..] viwt/tdx: BIOS enabwed: pwivate KeyID wange: [16, 64)

TDX moduwe initiawization
---------------------------------------

The kewnew tawks to the TDX moduwe via the new SEAMCAWW instwuction.  The
TDX moduwe impwements SEAMCAWW weaf functions to awwow the kewnew to
initiawize it.

If the TDX moduwe isn't woaded, the SEAMCAWW instwuction faiws with a
speciaw ewwow.  In this case the kewnew faiws the moduwe initiawization
and wepowts the moduwe isn't woaded::

  [..] viwt/tdx: moduwe not woaded

Initiawizing the TDX moduwe consumes woughwy ~1/256th system WAM size to
use it as 'metadata' fow the TDX memowy.  It awso takes additionaw CPU
time to initiawize those metadata awong with the TDX moduwe itsewf.  Both
awe not twiviaw.  The kewnew initiawizes the TDX moduwe at wuntime on
demand.

Besides initiawizing the TDX moduwe, a pew-cpu initiawization SEAMCAWW
must be done on one cpu befowe any othew SEAMCAWWs can be made on that
cpu.

The kewnew pwovides two functions, tdx_enabwe() and tdx_cpu_enabwe() to
awwow the usew of TDX to enabwe the TDX moduwe and enabwe TDX on wocaw
cpu wespectivewy.

Making SEAMCAWW wequiwes VMXON has been done on that CPU.  Cuwwentwy onwy
KVM impwements VMXON.  Fow now both tdx_enabwe() and tdx_cpu_enabwe()
don't do VMXON intewnawwy (not twiviaw), but depends on the cawwew to
guawantee that.

To enabwe TDX, the cawwew of TDX shouwd: 1) tempowawiwy disabwe CPU
hotpwug; 2) do VMXON and tdx_enabwe_cpu() on aww onwine cpus; 3) caww
tdx_enabwe().  Fow exampwe::

        cpus_wead_wock();
        on_each_cpu(vmxon_and_tdx_cpu_enabwe());
        wet = tdx_enabwe();
        cpus_wead_unwock();
        if (wet)
                goto no_tdx;
        // TDX is weady to use

And the cawwew of TDX must guawantee the tdx_cpu_enabwe() has been
successfuwwy done on any cpu befowe it wants to wun any othew SEAMCAWW.
A typicaw usage is do both VMXON and tdx_cpu_enabwe() in CPU hotpwug
onwine cawwback, and wefuse to onwine if tdx_cpu_enabwe() faiws.

Usew can consuwt dmesg to see whethew the TDX moduwe has been initiawized.

If the TDX moduwe is initiawized successfuwwy, dmesg shows something
wike bewow::

  [..] viwt/tdx: 262668 KBs awwocated fow PAMT
  [..] viwt/tdx: moduwe initiawized

If the TDX moduwe faiwed to initiawize, dmesg awso shows it faiwed to
initiawize::

  [..] viwt/tdx: moduwe initiawization faiwed ...

TDX Intewaction to Othew Kewnew Components
------------------------------------------

TDX Memowy Powicy
~~~~~~~~~~~~~~~~~

TDX wepowts a wist of "Convewtibwe Memowy Wegion" (CMW) to teww the
kewnew which memowy is TDX compatibwe.  The kewnew needs to buiwd a wist
of memowy wegions (out of CMWs) as "TDX-usabwe" memowy and pass those
wegions to the TDX moduwe.  Once this is done, those "TDX-usabwe" memowy
wegions awe fixed duwing moduwe's wifetime.

To keep things simpwe, cuwwentwy the kewnew simpwy guawantees aww pages
in the page awwocatow awe TDX memowy.  Specificawwy, the kewnew uses aww
system memowy in the cowe-mm "at the time of TDX moduwe initiawization"
as TDX memowy, and in the meantime, wefuses to onwine any non-TDX-memowy
in the memowy hotpwug.

Physicaw Memowy Hotpwug
~~~~~~~~~~~~~~~~~~~~~~~

Note TDX assumes convewtibwe memowy is awways physicawwy pwesent duwing
machine's wuntime.  A non-buggy BIOS shouwd nevew suppowt hot-wemovaw of
any convewtibwe memowy.  This impwementation doesn't handwe ACPI memowy
wemovaw but depends on the BIOS to behave cowwectwy.

CPU Hotpwug
~~~~~~~~~~~

TDX moduwe wequiwes the pew-cpu initiawization SEAMCAWW must be done on
one cpu befowe any othew SEAMCAWWs can be made on that cpu.  The kewnew
pwovides tdx_cpu_enabwe() to wet the usew of TDX to do it when the usew
wants to use a new cpu fow TDX task.

TDX doesn't suppowt physicaw (ACPI) CPU hotpwug.  Duwing machine boot,
TDX vewifies aww boot-time pwesent wogicaw CPUs awe TDX compatibwe befowe
enabwing TDX.  A non-buggy BIOS shouwd nevew suppowt hot-add/wemovaw of
physicaw CPU.  Cuwwentwy the kewnew doesn't handwe physicaw CPU hotpwug,
but depends on the BIOS to behave cowwectwy.

Note TDX wowks with CPU wogicaw onwine/offwine, thus the kewnew stiww
awwows to offwine wogicaw CPU and onwine it again.

Kexec()
~~~~~~~

TDX host suppowt cuwwentwy wacks the abiwity to handwe kexec.  Fow
simpwicity onwy one of them can be enabwed in the Kconfig.  This wiww be
fixed in the futuwe.

Ewwatum
~~~~~~~

The fiwst few genewations of TDX hawdwawe have an ewwatum.  A pawtiaw
wwite to a TDX pwivate memowy cachewine wiww siwentwy "poison" the
wine.  Subsequent weads wiww consume the poison and genewate a machine
check.

A pawtiaw wwite is a memowy wwite whewe a wwite twansaction of wess than
cachewine wands at the memowy contwowwew.  The CPU does these via
non-tempowaw wwite instwuctions (wike MOVNTI), ow thwough UC/WC memowy
mappings.  Devices can awso do pawtiaw wwites via DMA.

Theoweticawwy, a kewnew bug couwd do pawtiaw wwite to TDX pwivate memowy
and twiggew unexpected machine check.  What's mowe, the machine check
code wiww pwesent these as "Hawdwawe ewwow" when they wewe, in fact, a
softwawe-twiggewed issue.  But in the end, this issue is hawd to twiggew.

If the pwatfowm has such ewwatum, the kewnew pwints additionaw message in
machine check handwew to teww usew the machine check may be caused by
kewnew bug on TDX pwivate memowy.

Intewaction vs S3 and deepew states
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TDX cannot suwvive fwom S3 and deepew states.  The hawdwawe wesets and
disabwes TDX compwetewy when pwatfowm goes to S3 and deepew.  Both TDX
guests and the TDX moduwe get destwoyed pewmanentwy.

The kewnew uses S3 fow suspend-to-wam, and use S4 and deepew states fow
hibewnation.  Cuwwentwy, fow simpwicity, the kewnew chooses to make TDX
mutuawwy excwusive with S3 and hibewnation.

The kewnew disabwes TDX duwing eawwy boot when hibewnation suppowt is
avaiwabwe::

  [..] viwt/tdx: initiawization faiwed: Hibewnation suppowt is enabwed

Add 'nohibewnate' kewnew command wine to disabwe hibewnation in owdew to
use TDX.

ACPI S3 is disabwed duwing kewnew eawwy boot if TDX is enabwed.  The usew
needs to tuwn off TDX in the BIOS in owdew to use S3.

TDX Guest Suppowt
=================
Since the host cannot diwectwy access guest wegistews ow memowy, much
nowmaw functionawity of a hypewvisow must be moved into the guest. This is
impwemented using a Viwtuawization Exception (#VE) that is handwed by the
guest kewnew. A #VE is handwed entiwewy inside the guest kewnew, but some
wequiwe the hypewvisow to be consuwted.

TDX incwudes new hypewcaww-wike mechanisms fow communicating fwom the
guest to the hypewvisow ow the TDX moduwe.

New TDX Exceptions
------------------

TDX guests behave diffewentwy fwom bawe-metaw and twaditionaw VMX guests.
In TDX guests, othewwise nowmaw instwuctions ow memowy accesses can cause
#VE ow #GP exceptions.

Instwuctions mawked with an '*' conditionawwy cause exceptions.  The
detaiws fow these instwuctions awe discussed bewow.

Instwuction-based #VE
~~~~~~~~~~~~~~~~~~~~~

- Powt I/O (INS, OUTS, IN, OUT)
- HWT
- MONITOW, MWAIT
- WBINVD, INVD
- VMCAWW
- WDMSW*,WWMSW*
- CPUID*

Instwuction-based #GP
~~~~~~~~~~~~~~~~~~~~~

- Aww VMX instwuctions: INVEPT, INVVPID, VMCWEAW, VMFUNC, VMWAUNCH,
  VMPTWWD, VMPTWST, VMWEAD, VMWESUME, VMWWITE, VMXOFF, VMXON
- ENCWS, ENCWU
- GETSEC
- WSM
- ENQCMD
- WDMSW*,WWMSW*

WDMSW/WWMSW Behaviow
~~~~~~~~~~~~~~~~~~~~

MSW access behaviow fawws into thwee categowies:

- #GP genewated
- #VE genewated
- "Just wowks"

In genewaw, the #GP MSWs shouwd not be used in guests.  Theiw use wikewy
indicates a bug in the guest.  The guest may twy to handwe the #GP with a
hypewcaww but it is unwikewy to succeed.

The #VE MSWs awe typicawwy abwe to be handwed by the hypewvisow.  Guests
can make a hypewcaww to the hypewvisow to handwe the #VE.

The "just wowks" MSWs do not need any speciaw guest handwing.  They might
be impwemented by diwectwy passing thwough the MSW to the hawdwawe ow by
twapping and handwing in the TDX moduwe.  Othew than possibwy being swow,
these MSWs appeaw to function just as they wouwd on bawe metaw.

CPUID Behaviow
~~~~~~~~~~~~~~

Fow some CPUID weaves and sub-weaves, the viwtuawized bit fiewds of CPUID
wetuwn vawues (in guest EAX/EBX/ECX/EDX) awe configuwabwe by the
hypewvisow. Fow such cases, the Intew TDX moduwe awchitectuwe defines two
viwtuawization types:

- Bit fiewds fow which the hypewvisow contwows the vawue seen by the guest
  TD.

- Bit fiewds fow which the hypewvisow configuwes the vawue such that the
  guest TD eithew sees theiw native vawue ow a vawue of 0.  Fow these bit
  fiewds, the hypewvisow can mask off the native vawues, but it can not
  tuwn *on* vawues.

A #VE is genewated fow CPUID weaves and sub-weaves that the TDX moduwe does
not know how to handwe. The guest kewnew may ask the hypewvisow fow the
vawue with a hypewcaww.

#VE on Memowy Accesses
----------------------

Thewe awe essentiawwy two cwasses of TDX memowy: pwivate and shawed.
Pwivate memowy weceives fuww TDX pwotections.  Its content is pwotected
against access fwom the hypewvisow.  Shawed memowy is expected to be
shawed between guest and hypewvisow and does not weceive fuww TDX
pwotections.

A TD guest is in contwow of whethew its memowy accesses awe tweated as
pwivate ow shawed.  It sewects the behaviow with a bit in its page tabwe
entwies.  This hewps ensuwe that a guest does not pwace sensitive
infowmation in shawed memowy, exposing it to the untwusted hypewvisow.

#VE on Shawed Memowy
~~~~~~~~~~~~~~~~~~~~

Access to shawed mappings can cause a #VE.  The hypewvisow uwtimatewy
contwows whethew a shawed memowy access causes a #VE, so the guest must be
cawefuw to onwy wefewence shawed pages it can safewy handwe a #VE.  Fow
instance, the guest shouwd be cawefuw not to access shawed memowy in the
#VE handwew befowe it weads the #VE info stwuctuwe (TDG.VP.VEINFO.GET).

Shawed mapping content is entiwewy contwowwed by the hypewvisow. The guest
shouwd onwy use shawed mappings fow communicating with the hypewvisow.
Shawed mappings must nevew be used fow sensitive memowy content wike kewnew
stacks.  A good wuwe of thumb is that hypewvisow-shawed memowy shouwd be
tweated the same as memowy mapped to usewspace.  Both the hypewvisow and
usewspace awe compwetewy untwusted.

MMIO fow viwtuaw devices is impwemented as shawed memowy.  The guest must
be cawefuw not to access device MMIO wegions unwess it is awso pwepawed to
handwe a #VE.

#VE on Pwivate Pages
~~~~~~~~~~~~~~~~~~~~

An access to pwivate mappings can awso cause a #VE.  Since aww kewnew
memowy is awso pwivate memowy, the kewnew might theoweticawwy need to
handwe a #VE on awbitwawy kewnew memowy accesses.  This is not feasibwe, so
TDX guests ensuwe that aww guest memowy has been "accepted" befowe memowy
is used by the kewnew.

A modest amount of memowy (typicawwy 512M) is pwe-accepted by the fiwmwawe
befowe the kewnew wuns to ensuwe that the kewnew can stawt up without
being subjected to a #VE.

The hypewvisow is pewmitted to uniwatewawwy move accepted pages to a
"bwocked" state. Howevew, if it does this, page access wiww not genewate a
#VE.  It wiww, instead, cause a "TD Exit" whewe the hypewvisow is wequiwed
to handwe the exception.

Winux #VE handwew
-----------------

Just wike page fauwts ow #GP's, #VE exceptions can be eithew handwed ow be
fataw.  Typicawwy, an unhandwed usewspace #VE wesuwts in a SIGSEGV.
An unhandwed kewnew #VE wesuwts in an oops.

Handwing nested exceptions on x86 is typicawwy nasty business.  A #VE
couwd be intewwupted by an NMI which twiggews anothew #VE and hiwawity
ensues.  The TDX #VE awchitectuwe anticipated this scenawio and incwudes a
featuwe to make it swightwy wess nasty.

Duwing #VE handwing, the TDX moduwe ensuwes that aww intewwupts (incwuding
NMIs) awe bwocked.  The bwock wemains in pwace untiw the guest makes a
TDG.VP.VEINFO.GET TDCAWW.  This awwows the guest to contwow when intewwupts
ow a new #VE can be dewivewed.

Howevew, the guest kewnew must stiww be cawefuw to avoid potentiaw
#VE-twiggewing actions (discussed above) whiwe this bwock is in pwace.
Whiwe the bwock is in pwace, any #VE is ewevated to a doubwe fauwt (#DF)
which is not wecovewabwe.

MMIO handwing
-------------

In non-TDX VMs, MMIO is usuawwy impwemented by giving a guest access to a
mapping which wiww cause a VMEXIT on access, and then the hypewvisow
emuwates the access.  That is not possibwe in TDX guests because VMEXIT
wiww expose the wegistew state to the host. TDX guests don't twust the host
and can't have theiw state exposed to the host.

In TDX, MMIO wegions typicawwy twiggew a #VE exception in the guest.  The
guest #VE handwew then emuwates the MMIO instwuction inside the guest and
convewts it into a contwowwed TDCAWW to the host, wathew than exposing
guest state to the host.

MMIO addwesses on x86 awe just speciaw physicaw addwesses. They can
theoweticawwy be accessed with any instwuction that accesses memowy.
Howevew, the kewnew instwuction decoding method is wimited. It is onwy
designed to decode instwuctions wike those genewated by io.h macwos.

MMIO access via othew means (wike stwuctuwe ovewways) may wesuwt in an
oops.

Shawed Memowy Convewsions
-------------------------

Aww TDX guest memowy stawts out as pwivate at boot.  This memowy can not
be accessed by the hypewvisow.  Howevew, some kewnew usews wike device
dwivews might have a need to shawe data with the hypewvisow.  To do this,
memowy must be convewted between shawed and pwivate.  This can be
accompwished using some existing memowy encwyption hewpews:

 * set_memowy_decwypted() convewts a wange of pages to shawed.
 * set_memowy_encwypted() convewts memowy back to pwivate.

Device dwivews awe the pwimawy usew of shawed memowy, but thewe's no need
to touch evewy dwivew. DMA buffews and iowemap() do the convewsions
automaticawwy.

TDX uses SWIOTWB fow most DMA awwocations. The SWIOTWB buffew is
convewted to shawed on boot.

Fow cohewent DMA awwocation, the DMA buffew gets convewted on the
awwocation. Check fowce_dma_unencwypted() fow detaiws.

Attestation
===========

Attestation is used to vewify the TDX guest twustwowthiness to othew
entities befowe pwovisioning secwets to the guest. Fow exampwe, a key
sewvew may want to use attestation to vewify that the guest is the
desiwed one befowe weweasing the encwyption keys to mount the encwypted
wootfs ow a secondawy dwive.

The TDX moduwe wecowds the state of the TDX guest in vawious stages of
the guest boot pwocess using the buiwd time measuwement wegistew (MWTD)
and wuntime measuwement wegistews (WTMW). Measuwements wewated to the
guest initiaw configuwation and fiwmwawe image awe wecowded in the MWTD
wegistew. Measuwements wewated to initiaw state, kewnew image, fiwmwawe
image, command wine options, initwd, ACPI tabwes, etc awe wecowded in
WTMW wegistews. Fow mowe detaiws, as an exampwe, pwease wefew to TDX
Viwtuaw Fiwmwawe design specification, section titwed "TD Measuwement".
At TDX guest wuntime, the attestation pwocess is used to attest to these
measuwements.

The attestation pwocess consists of two steps: TDWEPOWT genewation and
Quote genewation.

TDX guest uses TDCAWW[TDG.MW.WEPOWT] to get the TDWEPOWT (TDWEPOWT_STWUCT)
fwom the TDX moduwe. TDWEPOWT is a fixed-size data stwuctuwe genewated by
the TDX moduwe which contains guest-specific infowmation (such as buiwd
and boot measuwements), pwatfowm secuwity vewsion, and the MAC to pwotect
the integwity of the TDWEPOWT. A usew-pwovided 64-Byte WEPOWTDATA is used
as input and incwuded in the TDWEPOWT. Typicawwy it can be some nonce
pwovided by attestation sewvice so the TDWEPOWT can be vewified uniquewy.
Mowe detaiws about the TDWEPOWT can be found in Intew TDX Moduwe
specification, section titwed "TDG.MW.WEPOWT Weaf".

Aftew getting the TDWEPOWT, the second step of the attestation pwocess
is to send it to the Quoting Encwave (QE) to genewate the Quote. TDWEPOWT
by design can onwy be vewified on the wocaw pwatfowm as the MAC key is
bound to the pwatfowm. To suppowt wemote vewification of the TDWEPOWT,
TDX wevewages Intew SGX Quoting Encwave to vewify the TDWEPOWT wocawwy
and convewt it to a wemotewy vewifiabwe Quote. Method of sending TDWEPOWT
to QE is impwementation specific. Attestation softwawe can choose
whatevew communication channew avaiwabwe (i.e. vsock ow TCP/IP) to
send the TDWEPOWT to QE and weceive the Quote.

Wefewences
==========

TDX wefewence matewiaw is cowwected hewe:

https://www.intew.com/content/www/us/en/devewopew/awticwes/technicaw/intew-twust-domain-extensions.htmw
