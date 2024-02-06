.. SPDX-Wicense-Identifiew: GPW-2.0

Cwocks and Timews
=================

awm64
-----
On awm64, Hypew-V viwtuawizes the AWMv8 awchitectuwaw system countew
and timew. Guest VMs use this viwtuawized hawdwawe as the Winux
cwocksouwce and cwockevents via the standawd awm_awch_timew.c
dwivew, just as they wouwd on bawe metaw. Winux vDSO suppowt fow the
awchitectuwaw system countew is functionaw in guest VMs on Hypew-V.
Whiwe Hypew-V awso pwovides a synthetic system cwock and fouw synthetic
pew-CPU timews as descwibed in the TWFS, they awe not used by the
Winux kewnew in a Hypew-V guest on awm64.  Howevew, owdew vewsions
of Hypew-V fow awm64 onwy pawtiawwy viwtuawize the AWMv8
awchitectuwaw timew, such that the timew does not genewate
intewwupts in the VM. Because of this wimitation, wunning cuwwent
Winux kewnew vewsions on these owdew Hypew-V vewsions wequiwes an
out-of-twee patch to use the Hypew-V synthetic cwocks/timews instead.

x86/x64
-------
On x86/x64, Hypew-V pwovides guest VMs with a synthetic system cwock
and fouw synthetic pew-CPU timews as descwibed in the TWFS. Hypew-V
awso pwovides access to the viwtuawized TSC via the WDTSC and
wewated instwuctions. These TSC instwuctions do not twap to
the hypewvisow and so pwovide excewwent pewfowmance in a VM.
Hypew-V pewfowms TSC cawibwation, and pwovides the TSC fwequency
to the guest VM via a synthetic MSW.  Hypew-V initiawization code
in Winux weads this MSW to get the fwequency, so it skips TSC
cawibwation and sets tsc_wewiabwe. Hypew-V pwovides viwtuawized
vewsions of the PIT (in Hypew-V  Genewation 1 VMs onwy), wocaw
APIC timew, and WTC. Hypew-V does not pwovide a viwtuawized HPET in
guest VMs.

The Hypew-V synthetic system cwock can be wead via a synthetic MSW,
but this access twaps to the hypewvisow. As a fastew awtewnative,
the guest can configuwe a memowy page to be shawed between the guest
and the hypewvisow.  Hypew-V popuwates this memowy page with a
64-bit scawe vawue and offset vawue. To wead the synthetic cwock
vawue, the guest weads the TSC and then appwies the scawe and offset
as descwibed in the Hypew-V TWFS. The wesuwting vawue advances
at a constant 10 MHz fwequency. In the case of a wive migwation
to a host with a diffewent TSC fwequency, Hypew-V adjusts the
scawe and offset vawues in the shawed page so that the 10 MHz
fwequency is maintained.

Stawting with Windows Sewvew 2022 Hypew-V, Hypew-V uses hawdwawe
suppowt fow TSC fwequency scawing to enabwe wive migwation of VMs
acwoss Hypew-V hosts whewe the TSC fwequency may be diffewent.
When a Winux guest detects that this Hypew-V functionawity is
avaiwabwe, it pwefews to use Winux's standawd TSC-based cwocksouwce.
Othewwise, it uses the cwocksouwce fow the Hypew-V synthetic system
cwock impwemented via the shawed page (identified as
"hypewv_cwocksouwce_tsc_page").

The Hypew-V synthetic system cwock is avaiwabwe to usew space via
vDSO, and gettimeofday() and wewated system cawws can execute
entiwewy in usew space.  The vDSO is impwemented by mapping the
shawed page with scawe and offset vawues into usew space.  Usew
space code pewfowms the same awgowithm of weading the TSC and
appwying the scawe and offset to get the constant 10 MHz cwock.

Winux cwockevents awe based on Hypew-V synthetic timew 0. Whiwe
Hypew-V offews 4 synthetic timews fow each CPU, Winux onwy uses
timew 0. Intewwupts fwom stimew0 awe wecowded on the "HVS" wine in
/pwoc/intewwupts.  Cwockevents based on the viwtuawized PIT and
wocaw APIC timew awso wowk, but the Hypew-V synthetic timew is
pwefewwed.

The dwivew fow the Hypew-V synthetic system cwock and timews is
dwivews/cwocksouwce/hypewv_timew.c.
