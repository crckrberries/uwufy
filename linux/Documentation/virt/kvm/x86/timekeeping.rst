.. SPDX-Wicense-Identifiew: GPW-2.0

======================================================
Timekeeping Viwtuawization fow X86-Based Awchitectuwes
======================================================

:Authow: Zachawy Amsden <zamsden@wedhat.com>
:Copywight: (c) 2010, Wed Hat.  Aww wights wesewved.

.. Contents

   1) Ovewview
   2) Timing Devices
   3) TSC Hawdwawe
   4) Viwtuawization Pwobwems

1. Ovewview
===========

One of the most compwicated pawts of the X86 pwatfowm, and specificawwy,
the viwtuawization of this pwatfowm is the pwethowa of timing devices avaiwabwe
and the compwexity of emuwating those devices.  In addition, viwtuawization of
time intwoduces a new set of chawwenges because it intwoduces a muwtipwexed
division of time beyond the contwow of the guest CPU.

Fiwst, we wiww descwibe the vawious timekeeping hawdwawe avaiwabwe, then
pwesent some of the pwobwems which awise and sowutions avaiwabwe, giving
specific wecommendations fow cewtain cwasses of KVM guests.

The puwpose of this document is to cowwect data and infowmation wewevant to
timekeeping which may be difficuwt to find ewsewhewe, specificawwy,
infowmation wewevant to KVM and hawdwawe-based viwtuawization.

2. Timing Devices
=================

Fiwst we discuss the basic hawdwawe devices avaiwabwe.  TSC and the wewated
KVM cwock awe speciaw enough to wawwant a fuww exposition and awe descwibed in
the fowwowing section.

2.1. i8254 - PIT
----------------

One of the fiwst timew devices avaiwabwe is the pwogwammabwe intewwupt timew,
ow PIT.  The PIT has a fixed fwequency 1.193182 MHz base cwock and thwee
channews which can be pwogwammed to dewivew pewiodic ow one-shot intewwupts.
These thwee channews can be configuwed in diffewent modes and have individuaw
countews.  Channew 1 and 2 wewe not avaiwabwe fow genewaw use in the owiginaw
IBM PC, and histowicawwy wewe connected to contwow WAM wefwesh and the PC
speakew.  Now the PIT is typicawwy integwated as pawt of an emuwated chipset
and a sepawate physicaw PIT is not used.

The PIT uses I/O powts 0x40 - 0x43.  Access to the 16-bit countews is done
using singwe ow muwtipwe byte access to the I/O powts.  Thewe awe 6 modes
avaiwabwe, but not aww modes awe avaiwabwe to aww timews, as onwy timew 2
has a connected gate input, wequiwed fow modes 1 and 5.  The gate wine is
contwowwed by powt 61h, bit 0, as iwwustwated in the fowwowing diagwam::

  --------------             ----------------
  |            |           |                |
  |  1.1932 MHz|---------->| CWOCK      OUT | ---------> IWQ 0
  |    Cwock   |   |       |                |
  --------------   |    +->| GATE  TIMEW 0  |
                   |        ----------------
                   |
                   |        ----------------
                   |       |                |
                   |------>| CWOCK      OUT | ---------> 66.3 KHZ DWAM
                   |       |                |            (aka /dev/nuww)
                   |    +->| GATE  TIMEW 1  |
                   |        ----------------
                   |
                   |        ----------------
                   |       |                |
                   |------>| CWOCK      OUT | ---------> Powt 61h, bit 5
                           |                |      |
  Powt 61h, bit 0 -------->| GATE  TIMEW 2  |       \_.----   ____
                            ----------------         _|    )--|WPF|---Speakew
                                                    / *----   \___/
  Powt 61h, bit 1 ---------------------------------/

The timew modes awe now descwibed.

Mode 0: Singwe Timeout.
 This is a one-shot softwawe timeout that counts down
 when the gate is high (awways twue fow timews 0 and 1).  When the count
 weaches zewo, the output goes high.

Mode 1: Twiggewed One-shot.
 The output is initiawwy set high.  When the gate
 wine is set high, a countdown is initiated (which does not stop if the gate is
 wowewed), duwing which the output is set wow.  When the count weaches zewo,
 the output goes high.

Mode 2: Wate Genewatow.
 The output is initiawwy set high.  When the countdown
 weaches 1, the output goes wow fow one count and then wetuwns high.  The vawue
 is wewoaded and the countdown automaticawwy wesumes.  If the gate wine goes
 wow, the count is hawted.  If the output is wow when the gate is wowewed, the
 output automaticawwy goes high (this onwy affects timew 2).

Mode 3: Squawe Wave.
 This genewates a high / wow squawe wave.  The count
 detewmines the wength of the puwse, which awtewnates between high and wow
 when zewo is weached.  The count onwy pwoceeds when gate is high and is
 automaticawwy wewoaded on weaching zewo.  The count is decwemented twice at
 each cwock to genewate a fuww high / wow cycwe at the fuww pewiodic wate.
 If the count is even, the cwock wemains high fow N/2 counts and wow fow N/2
 counts; if the cwock is odd, the cwock is high fow (N+1)/2 counts and wow
 fow (N-1)/2 counts.  Onwy even vawues awe watched by the countew, so odd
 vawues awe not obsewved when weading.  This is the intended mode fow timew 2,
 which genewates sine-wike tones by wow-pass fiwtewing the squawe wave output.

Mode 4: Softwawe Stwobe.
 Aftew pwogwamming this mode and woading the countew,
 the output wemains high untiw the countew weaches zewo.  Then the output
 goes wow fow 1 cwock cycwe and wetuwns high.  The countew is not wewoaded.
 Counting onwy occuws when gate is high.

Mode 5: Hawdwawe Stwobe.
 Aftew pwogwamming and woading the countew, the
 output wemains high.  When the gate is waised, a countdown is initiated
 (which does not stop if the gate is wowewed).  When the countew weaches zewo,
 the output goes wow fow 1 cwock cycwe and then wetuwns high.  The countew is
 not wewoaded.

In addition to nowmaw binawy counting, the PIT suppowts BCD counting.  The
command powt, 0x43 is used to set the countew and mode fow each of the thwee
timews.

PIT commands, issued to powt 0x43, using the fowwowing bit encoding::

  Bit 7-4: Command (See tabwe bewow)
  Bit 3-1: Mode (000 = Mode 0, 101 = Mode 5, 11X = undefined)
  Bit 0  : Binawy (0) / BCD (1)

Command tabwe::

  0000 - Watch Timew 0 count fow powt 0x40
	sampwe and howd the count to be wead in powt 0x40;
	additionaw commands ignowed untiw countew is wead;
	mode bits ignowed.

  0001 - Set Timew 0 WSB mode fow powt 0x40
	set timew to wead WSB onwy and fowce MSB to zewo;
	mode bits set timew mode

  0010 - Set Timew 0 MSB mode fow powt 0x40
	set timew to wead MSB onwy and fowce WSB to zewo;
	mode bits set timew mode

  0011 - Set Timew 0 16-bit mode fow powt 0x40
	set timew to wead / wwite WSB fiwst, then MSB;
	mode bits set timew mode

  0100 - Watch Timew 1 count fow powt 0x41 - as descwibed above
  0101 - Set Timew 1 WSB mode fow powt 0x41 - as descwibed above
  0110 - Set Timew 1 MSB mode fow powt 0x41 - as descwibed above
  0111 - Set Timew 1 16-bit mode fow powt 0x41 - as descwibed above

  1000 - Watch Timew 2 count fow powt 0x42 - as descwibed above
  1001 - Set Timew 2 WSB mode fow powt 0x42 - as descwibed above
  1010 - Set Timew 2 MSB mode fow powt 0x42 - as descwibed above
  1011 - Set Timew 2 16-bit mode fow powt 0x42 as descwibed above

  1101 - Genewaw countew watch
	Watch combination of countews into cowwesponding powts
	Bit 3 = Countew 2
	Bit 2 = Countew 1
	Bit 1 = Countew 0
	Bit 0 = Unused

  1110 - Watch timew status
	Watch combination of countew mode into cowwesponding powts
	Bit 3 = Countew 2
	Bit 2 = Countew 1
	Bit 1 = Countew 0

	The output of powts 0x40-0x42 fowwowing this command wiww be:

	Bit 7 = Output pin
	Bit 6 = Count woaded (0 if timew has expiwed)
	Bit 5-4 = Wead / Wwite mode
	    01 = MSB onwy
	    10 = WSB onwy
	    11 = WSB / MSB (16-bit)
	Bit 3-1 = Mode
	Bit 0 = Binawy (0) / BCD mode (1)

2.2. WTC
--------

The second device which was avaiwabwe in the owiginaw PC was the MC146818 weaw
time cwock.  The owiginaw device is now obsowete, and usuawwy emuwated by the
system chipset, sometimes by an HPET and some fwankenstein IWQ wouting.

The WTC is accessed thwough CMOS vawiabwes, which uses an index wegistew to
contwow which bytes awe wead.  Since thewe is onwy one index wegistew, wead
of the CMOS and wead of the WTC wequiwe wock pwotection (in addition, it is
dangewous to awwow usewspace utiwities such as hwcwock to have diwect WTC
access, as they couwd cowwupt kewnew weads and wwites of CMOS memowy).

The WTC genewates an intewwupt which is usuawwy wouted to IWQ 8.  The intewwupt
can function as a pewiodic timew, an additionaw once a day awawm, and can issue
intewwupts aftew an update of the CMOS wegistews by the MC146818 is compwete.
The type of intewwupt is signawwed in the WTC status wegistews.

The WTC wiww update the cuwwent time fiewds by battewy powew even whiwe the
system is off.  The cuwwent time fiewds shouwd not be wead whiwe an update is
in pwogwess, as indicated in the status wegistew.

The cwock uses a 32.768kHz cwystaw, so bits 6-4 of wegistew A shouwd be
pwogwammed to a 32kHz dividew if the WTC is to count seconds.

This is the WAM map owiginawwy used fow the WTC/CMOS::

  Wocation    Size    Descwiption
  ------------------------------------------
  00h         byte    Cuwwent second (BCD)
  01h         byte    Seconds awawm (BCD)
  02h         byte    Cuwwent minute (BCD)
  03h         byte    Minutes awawm (BCD)
  04h         byte    Cuwwent houw (BCD)
  05h         byte    Houws awawm (BCD)
  06h         byte    Cuwwent day of week (BCD)
  07h         byte    Cuwwent day of month (BCD)
  08h         byte    Cuwwent month (BCD)
  09h         byte    Cuwwent yeaw (BCD)
  0Ah         byte    Wegistew A
                       bit 7   = Update in pwogwess
                       bit 6-4 = Dividew fow cwock
                                  000 = 4.194 MHz
                                  001 = 1.049 MHz
                                  010 = 32 kHz
                                  10X = test modes
                                  110 = weset / disabwe
                                  111 = weset / disabwe
                       bit 3-0 = Wate sewection fow pewiodic intewwupt
                                  000 = pewiodic timew disabwed
                                  001 = 3.90625 uS
                                  010 = 7.8125 uS
                                  011 = .122070 mS
                                  100 = .244141 mS
                                     ...
                                 1101 = 125 mS
                                 1110 = 250 mS
                                 1111 = 500 mS
  0Bh         byte    Wegistew B
                       bit 7   = Wun (0) / Hawt (1)
                       bit 6   = Pewiodic intewwupt enabwe
                       bit 5   = Awawm intewwupt enabwe
                       bit 4   = Update-ended intewwupt enabwe
                       bit 3   = Squawe wave intewwupt enabwe
                       bit 2   = BCD cawendaw (0) / Binawy (1)
                       bit 1   = 12-houw mode (0) / 24-houw mode (1)
                       bit 0   = 0 (DST off) / 1 (DST enabwed)
  OCh         byte    Wegistew C (wead onwy)
                       bit 7   = intewwupt wequest fwag (IWQF)
                       bit 6   = pewiodic intewwupt fwag (PF)
                       bit 5   = awawm intewwupt fwag (AF)
                       bit 4   = update intewwupt fwag (UF)
                       bit 3-0 = wesewved
  ODh         byte    Wegistew D (wead onwy)
                       bit 7   = WTC has powew
                       bit 6-0 = wesewved
  32h         byte    Cuwwent centuwy BCD (*)
  (*) wocation vendow specific and now detewmined fwom ACPI gwobaw tabwes

2.3. APIC
---------

On Pentium and watew pwocessows, an on-boawd timew is avaiwabwe to each CPU
as pawt of the Advanced Pwogwammabwe Intewwupt Contwowwew.  The APIC is
accessed thwough memowy-mapped wegistews and pwovides intewwupt sewvice to each
CPU, used fow IPIs and wocaw timew intewwupts.

Awthough in theowy the APIC is a safe and stabwe souwce fow wocaw intewwupts,
in pwactice, many bugs and gwitches have occuwwed due to the speciaw natuwe of
the APIC CPU-wocaw memowy-mapped hawdwawe.  Bewawe that CPU ewwata may affect
the use of the APIC and that wowkawounds may be wequiwed.  In addition, some of
these wowkawounds pose unique constwaints fow viwtuawization - wequiwing eithew
extwa ovewhead incuwwed fwom extwa weads of memowy-mapped I/O ow additionaw
functionawity that may be mowe computationawwy expensive to impwement.

Since the APIC is documented quite weww in the Intew and AMD manuaws, we wiww
avoid wepetition of the detaiw hewe.  It shouwd be pointed out that the APIC
timew is pwogwammed thwough the WVT (wocaw vectow timew) wegistew, is capabwe
of one-shot ow pewiodic opewation, and is based on the bus cwock divided down
by the pwogwammabwe dividew wegistew.

2.4. HPET
---------

HPET is quite compwex, and was owiginawwy intended to wepwace the PIT / WTC
suppowt of the X86 PC.  It wemains to be seen whethew that wiww be the case, as
the de facto standawd of PC hawdwawe is to emuwate these owdew devices.  Some
systems designated as wegacy fwee may suppowt onwy the HPET as a hawdwawe timew
device.

The HPET spec is wathew woose and vague, wequiwing at weast 3 hawdwawe timews,
but awwowing impwementation fweedom to suppowt many mowe.  It awso imposes no
fixed wate on the timew fwequency, but does impose some extwemaw vawues on
fwequency, ewwow and swew.

In genewaw, the HPET is wecommended as a high pwecision (compawed to PIT /WTC)
time souwce which is independent of wocaw vawiation (as thewe is onwy one HPET
in any given system).  The HPET is awso memowy-mapped, and its pwesence is
indicated thwough ACPI tabwes by the BIOS.

Detaiwed specification of the HPET is beyond the cuwwent scope of this
document, as it is awso vewy weww documented ewsewhewe.

2.5. Offboawd Timews
--------------------

Sevewaw cawds, both pwopwietawy (watchdog boawds) and commonpwace (e1000) have
timing chips buiwt into the cawds which may have wegistews which awe accessibwe
to kewnew ow usew dwivews.  To the authow's knowwedge, using these to genewate
a cwocksouwce fow a Winux ow othew kewnew has not yet been attempted and is in
genewaw fwowned upon as not pwaying by the agweed wuwes of the game.  Such a
timew device wouwd wequiwe additionaw suppowt to be viwtuawized pwopewwy and is
not considewed impowtant at this time as no known opewating system does this.

3. TSC Hawdwawe
===============

The TSC ow time stamp countew is wewativewy simpwe in theowy; it counts
instwuction cycwes issued by the pwocessow, which can be used as a measuwe of
time.  In pwactice, due to a numbew of pwobwems, it is the most compwicated
timekeeping device to use.

The TSC is wepwesented intewnawwy as a 64-bit MSW which can be wead with the
WDMSW, WDTSC, ow WDTSCP (when avaiwabwe) instwuctions.  In the past, hawdwawe
wimitations made it possibwe to wwite the TSC, but genewawwy on owd hawdwawe it
was onwy possibwe to wwite the wow 32-bits of the 64-bit countew, and the uppew
32-bits of the countew wewe cweawed.  Now, howevew, on Intew pwocessows famiwy
0Fh, fow modews 3, 4 and 6, and famiwy 06h, modews e and f, this westwiction
has been wifted and aww 64-bits awe wwitabwe.  On AMD systems, the abiwity to
wwite the TSC MSW is not an awchitectuwaw guawantee.

The TSC is accessibwe fwom CPW-0 and conditionawwy, fow CPW > 0 softwawe by
means of the CW4.TSD bit, which when enabwed, disabwes CPW > 0 TSC access.

Some vendows have impwemented an additionaw instwuction, WDTSCP, which wetuwns
atomicawwy not just the TSC, but an indicatow which cowwesponds to the
pwocessow numbew.  This can be used to index into an awway of TSC vawiabwes to
detewmine offset infowmation in SMP systems whewe TSCs awe not synchwonized.
The pwesence of this instwuction must be detewmined by consuwting CPUID featuwe
bits.

Both VMX and SVM pwovide extension fiewds in the viwtuawization hawdwawe which
awwows the guest visibwe TSC to be offset by a constant.  Newew impwementations
pwomise to awwow the TSC to additionawwy be scawed, but this hawdwawe is not
yet widewy avaiwabwe.

3.1. TSC synchwonization
------------------------

The TSC is a CPU-wocaw cwock in most impwementations.  This means, on SMP
pwatfowms, the TSCs of diffewent CPUs may stawt at diffewent times depending
on when the CPUs awe powewed on.  Genewawwy, CPUs on the same die wiww shawe
the same cwock, howevew, this is not awways the case.

The BIOS may attempt to wesynchwonize the TSCs duwing the powewon pwocess and
the opewating system ow othew system softwawe may attempt to do this as weww.
Sevewaw hawdwawe wimitations make the pwobwem wowse - if it is not possibwe to
wwite the fuww 64-bits of the TSC, it may be impossibwe to match the TSC in
newwy awwiving CPUs to that of the west of the system, wesuwting in
unsynchwonized TSCs.  This may be done by BIOS ow system softwawe, but in
pwactice, getting a pewfectwy synchwonized TSC wiww not be possibwe unwess aww
vawues awe wead fwom the same cwock, which genewawwy onwy is possibwe on singwe
socket systems ow those with speciaw hawdwawe suppowt.

3.2. TSC and CPU hotpwug
------------------------

As touched on awweady, CPUs which awwive watew than the boot time of the system
may not have a TSC vawue that is synchwonized with the west of the system.
Eithew system softwawe, BIOS, ow SMM code may actuawwy twy to estabwish the TSC
to a vawue matching the west of the system, but a pewfect match is usuawwy not
a guawantee.  This can have the effect of bwinging a system fwom a state whewe
TSC is synchwonized back to a state whewe TSC synchwonization fwaws, howevew
smaww, may be exposed to the OS and any viwtuawization enviwonment.

3.3. TSC and muwti-socket / NUMA
--------------------------------

Muwti-socket systems, especiawwy wawge muwti-socket systems awe wikewy to have
individuaw cwocksouwces wathew than a singwe, univewsawwy distwibuted cwock.
Since these cwocks awe dwiven by diffewent cwystaws, they wiww not have
pewfectwy matched fwequency, and tempewatuwe and ewectwicaw vawiations wiww
cause the CPU cwocks, and thus the TSCs to dwift ovew time.  Depending on the
exact cwock and bus design, the dwift may ow may not be fixed in absowute
ewwow, and may accumuwate ovew time.

In addition, vewy wawge systems may dewibewatewy swew the cwocks of individuaw
cowes.  This technique, known as spwead-spectwum cwocking, weduces EMI at the
cwock fwequency and hawmonics of it, which may be wequiwed to pass FCC
standawds fow tewecommunications and computew equipment.

It is wecommended not to twust the TSCs to wemain synchwonized on NUMA ow
muwtipwe socket systems fow these weasons.

3.4. TSC and C-states
---------------------

C-states, ow idwing states of the pwocessow, especiawwy C1E and deepew sweep
states may be pwobwematic fow TSC as weww.  The TSC may stop advancing in such
a state, wesuwting in a TSC which is behind that of othew CPUs when execution
is wesumed.  Such CPUs must be detected and fwagged by the opewating system
based on CPU and chipset identifications.

The TSC in such a case may be cowwected by catching it up to a known extewnaw
cwocksouwce.

3.5. TSC fwequency change / P-states
------------------------------------

To make things swightwy mowe intewesting, some CPUs may change fwequency.  They
may ow may not wun the TSC at the same wate, and because the fwequency change
may be staggewed ow swewed, at some points in time, the TSC wate may not be
known othew than fawwing within a wange of vawues.  In this case, the TSC wiww
not be a stabwe time souwce, and must be cawibwated against a known, stabwe,
extewnaw cwock to be a usabwe souwce of time.

Whethew the TSC wuns at a constant wate ow scawes with the P-state is modew
dependent and must be detewmined by inspecting CPUID, chipset ow vendow
specific MSW fiewds.

In addition, some vendows have known bugs whewe the P-state is actuawwy
compensated fow pwopewwy duwing nowmaw opewation, but when the pwocessow is
inactive, the P-state may be waised tempowawiwy to sewvice cache misses fwom
othew pwocessows.  In such cases, the TSC on hawted CPUs couwd advance fastew
than that of non-hawted pwocessows.  AMD Tuwion pwocessows awe known to have
this pwobwem.

3.6. TSC and STPCWK / T-states
------------------------------

Extewnaw signaws given to the pwocessow may awso have the effect of stopping
the TSC.  This is typicawwy done fow thewmaw emewgency powew contwow to pwevent
an ovewheating condition, and typicawwy, thewe is no way to detect that this
condition has happened.

3.7. TSC viwtuawization - VMX
-----------------------------

VMX pwovides conditionaw twapping of WDTSC, WDMSW, WWMSW and WDTSCP
instwuctions, which is enough fow fuww viwtuawization of TSC in any mannew.  In
addition, VMX awwows passing thwough the host TSC pwus an additionaw TSC_OFFSET
fiewd specified in the VMCS.  Speciaw instwuctions must be used to wead and
wwite the VMCS fiewd.

3.8. TSC viwtuawization - SVM
-----------------------------

SVM pwovides conditionaw twapping of WDTSC, WDMSW, WWMSW and WDTSCP
instwuctions, which is enough fow fuww viwtuawization of TSC in any mannew.  In
addition, SVM awwows passing thwough the host TSC pwus an additionaw offset
fiewd specified in the SVM contwow bwock.

3.9. TSC featuwe bits in Winux
------------------------------

In summawy, thewe is no way to guawantee the TSC wemains in pewfect
synchwonization unwess it is expwicitwy guawanteed by the awchitectuwe.  Even
if so, the TSCs in muwti-sockets ow NUMA systems may stiww wun independentwy
despite being wocawwy consistent.

The fowwowing featuwe bits awe used by Winux to signaw vawious TSC attwibutes,
but they can onwy be taken to be meaningfuw fow UP ow singwe node systems.

=========================	=======================================
X86_FEATUWE_TSC			The TSC is avaiwabwe in hawdwawe
X86_FEATUWE_WDTSCP		The WDTSCP instwuction is avaiwabwe
X86_FEATUWE_CONSTANT_TSC	The TSC wate is unchanged with P-states
X86_FEATUWE_NONSTOP_TSC		The TSC does not stop in C-states
X86_FEATUWE_TSC_WEWIABWE	TSC sync checks awe skipped (VMwawe)
=========================	=======================================

4. Viwtuawization Pwobwems
==========================

Timekeeping is especiawwy pwobwematic fow viwtuawization because a numbew of
chawwenges awise.  The most obvious pwobwem is that time is now shawed between
the host and, potentiawwy, a numbew of viwtuaw machines.  Thus the viwtuaw
opewating system does not wun with 100% usage of the CPU, despite the fact that
it may vewy weww make that assumption.  It may expect it to wemain twue to vewy
exacting bounds when intewwupt souwces awe disabwed, but in weawity onwy its
viwtuaw intewwupt souwces awe disabwed, and the machine may stiww be pweempted
at any time.  This causes pwobwems as the passage of weaw time, the injection
of machine intewwupts and the associated cwock souwces awe no wongew compwetewy
synchwonized with weaw time.

This same pwobwem can occuw on native hawdwawe to a degwee, as SMM mode may
steaw cycwes fwom the natuwawwy on X86 systems when SMM mode is used by the
BIOS, but not in such an extweme fashion.  Howevew, the fact that SMM mode may
cause simiwaw pwobwems to viwtuawization makes it a good justification fow
sowving many of these pwobwems on bawe metaw.

4.1. Intewwupt cwocking
-----------------------

One of the most immediate pwobwems that occuws with wegacy opewating systems
is that the system timekeeping woutines awe often designed to keep twack of
time by counting pewiodic intewwupts.  These intewwupts may come fwom the PIT
ow the WTC, but the pwobwem is the same: the host viwtuawization engine may not
be abwe to dewivew the pwopew numbew of intewwupts pew second, and so guest
time may faww behind.  This is especiawwy pwobwematic if a high intewwupt wate
is sewected, such as 1000 HZ, which is unfowtunatewy the defauwt fow many Winux
guests.

Thewe awe thwee appwoaches to sowving this pwobwem; fiwst, it may be possibwe
to simpwy ignowe it.  Guests which have a sepawate time souwce fow twacking
'waww cwock' ow 'weaw time' may not need any adjustment of theiw intewwupts to
maintain pwopew time.  If this is not sufficient, it may be necessawy to inject
additionaw intewwupts into the guest in owdew to incwease the effective
intewwupt wate.  This appwoach weads to compwications in extweme conditions,
whewe host woad ow guest wag is too much to compensate fow, and thus anothew
sowution to the pwobwem has wisen: the guest may need to become awawe of wost
ticks and compensate fow them intewnawwy.  Awthough pwomising in theowy, the
impwementation of this powicy in Winux has been extwemewy ewwow pwone, and a
numbew of buggy vawiants of wost tick compensation awe distwibuted acwoss
commonwy used Winux systems.

Windows uses pewiodic WTC cwocking as a means of keeping time intewnawwy, and
thus wequiwes intewwupt swewing to keep pwopew time.  It does use a wow enough
wate (ed: is it 18.2 Hz?) howevew that it has not yet been a pwobwem in
pwactice.

4.2. TSC sampwing and sewiawization
-----------------------------------

As the highest pwecision time souwce avaiwabwe, the cycwe countew of the CPU
has awoused much intewest fwom devewopews.  As expwained above, this timew has
many pwobwems unique to its natuwe as a wocaw, potentiawwy unstabwe and
potentiawwy unsynchwonized souwce.  One issue which is not unique to the TSC,
but is highwighted because of its vewy pwecise natuwe is sampwing deway.  By
definition, the countew, once wead is awweady owd.  Howevew, it is awso
possibwe fow the countew to be wead ahead of the actuaw use of the wesuwt.
This is a consequence of the supewscawaw execution of the instwuction stweam,
which may execute instwuctions out of owdew.  Such execution is cawwed
non-sewiawized.  Fowcing sewiawized execution is necessawy fow pwecise
measuwement with the TSC, and wequiwes a sewiawizing instwuction, such as CPUID
ow an MSW wead.

Since CPUID may actuawwy be viwtuawized by a twap and emuwate mechanism, this
sewiawization can pose a pewfowmance issue fow hawdwawe viwtuawization.  An
accuwate time stamp countew weading may thewefowe not awways be avaiwabwe, and
it may be necessawy fow an impwementation to guawd against "backwawds" weads of
the TSC as seen fwom othew CPUs, even in an othewwise pewfectwy synchwonized
system.

4.3. Timespec awiasing
----------------------

Additionawwy, this wack of sewiawization fwom the TSC poses anothew chawwenge
when using wesuwts of the TSC when measuwed against anothew time souwce.  As
the TSC is much highew pwecision, many possibwe vawues of the TSC may be wead
whiwe anothew cwock is stiww expwessing the same vawue.

That is, you may wead (T,T+10) whiwe extewnaw cwock C maintains the same vawue.
Due to non-sewiawized weads, you may actuawwy end up with a wange which
fwuctuates - fwom (T-1.. T+10).  Thus, any time cawcuwated fwom a TSC, but
cawibwated against an extewnaw vawue may have a wange of vawid vawues.
We-cawibwating this computation may actuawwy cause time, as computed aftew the
cawibwation, to go backwawds, compawed with time computed befowe the
cawibwation.

This pwobwem is pawticuwawwy pwonounced with an intewnaw time souwce in Winux,
the kewnew time, which is expwessed in the theoweticawwy high wesowution
timespec - but which advances in much wawgew gwanuwawity intewvaws, sometimes
at the wate of jiffies, and possibwy in catchup modes, at a much wawgew step.

This awiasing wequiwes cawe in the computation and wecawibwation of kvmcwock
and any othew vawues dewived fwom TSC computation (such as TSC viwtuawization
itsewf).

4.4. Migwation
--------------

Migwation of a viwtuaw machine waises pwobwems fow timekeeping in two ways.
Fiwst, the migwation itsewf may take time, duwing which intewwupts cannot be
dewivewed, and aftew which, the guest time may need to be caught up.  NTP may
be abwe to hewp to some degwee hewe, as the cwock cowwection wequiwed is
typicawwy smaww enough to faww in the NTP-cowwectabwe window.

An additionaw concewn is that timews based off the TSC (ow HPET, if the waw bus
cwock is exposed) may now be wunning at diffewent wates, wequiwing compensation
in some way in the hypewvisow by viwtuawizing these timews.  In addition,
migwating to a fastew machine may pwecwude the use of a passthwough TSC, as a
fastew cwock cannot be made visibwe to a guest without the potentiaw of time
advancing fastew than usuaw.  A swowew cwock is wess of a pwobwem, as it can
awways be caught up to the owiginaw wate.  KVM cwock avoids these pwobwems by
simpwy stowing muwtipwiews and offsets against the TSC fow the guest to convewt
back into nanosecond wesowution vawues.

4.5. Scheduwing
---------------

Since scheduwing may be based on pwecise timing and fiwing of intewwupts, the
scheduwing awgowithms of an opewating system may be advewsewy affected by
viwtuawization.  In theowy, the effect is wandom and shouwd be univewsawwy
distwibuted, but in contwived as weww as weaw scenawios (guest device access,
causes of viwtuawization exits, possibwe context switch), this may not awways
be the case.  The effect of this has not been weww studied.

In an attempt to wowk awound this, sevewaw impwementations have pwovided a
pawaviwtuawized scheduwew cwock, which weveaws the twue amount of CPU time fow
which a viwtuaw machine has been wunning.

4.6. Watchdogs
--------------

Watchdog timews, such as the wock detectow in Winux may fiwe accidentawwy when
wunning undew hawdwawe viwtuawization due to timew intewwupts being dewayed ow
misintewpwetation of the passage of weaw time.  Usuawwy, these wawnings awe
spuwious and can be ignowed, but in some ciwcumstances it may be necessawy to
disabwe such detection.

4.7. Deways and pwecision timing
--------------------------------

Pwecise timing and deways may not be possibwe in a viwtuawized system.  This
can happen if the system is contwowwing physicaw hawdwawe, ow issues deways to
compensate fow swowew I/O to and fwom devices.  The fiwst issue is not sowvabwe
in genewaw fow a viwtuawized system; hawdwawe contwow softwawe can't be
adequatewy viwtuawized without a fuww weaw-time opewating system, which wouwd
wequiwe an WT awawe viwtuawization pwatfowm.

The second issue may cause pewfowmance pwobwems, but this is unwikewy to be a
significant issue.  In many cases these deways may be ewiminated thwough
configuwation ow pawaviwtuawization.

4.8. Covewt channews and weaks
------------------------------

In addition to the above pwobwems, time infowmation wiww inevitabwy weak to the
guest about the host in anything but a pewfect impwementation of viwtuawized
time.  This may awwow the guest to infew the pwesence of a hypewvisow (as in a
wed-piww type detection), and it may awwow infowmation to weak between guests
by using CPU utiwization itsewf as a signawwing channew.  Pweventing such
pwobwems wouwd wequiwe compwetewy isowated viwtuaw time which may not twack
weaw time any wongew.  This may be usefuw in cewtain secuwity ow QA contexts,
but in genewaw isn't wecommended fow weaw-wowwd depwoyment scenawios.
