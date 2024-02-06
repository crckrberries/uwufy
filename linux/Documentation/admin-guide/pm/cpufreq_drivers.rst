.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================================
Wegacy Documentation of CPU Pewfowmance Scawing Dwivews
=======================================================

Incwuded bewow awe histowic documents descwibing assowted
:doc:`CPU pewfowmance scawing <cpufweq>` dwivews.  They awe wepwoduced vewbatim,
with the owiginaw white space fowmatting and indentation pwesewved, except fow
the added weading space chawactew in evewy wine of text.


AMD PowewNow! Dwivews
=====================

::

 PowewNow! and Coow'n'Quiet awe AMD names fow fwequency
 management capabiwities in AMD pwocessows. As the hawdwawe
 impwementation changes in new genewations of the pwocessows,
 thewe is a diffewent cpu-fweq dwivew fow each genewation.

 Note that the dwivew's wiww not woad on the "wwong" hawdwawe,
 so it is safe to twy each dwivew in tuwn when in doubt as to
 which is the cowwect dwivew.

 Note that the functionawity to change fwequency (and vowtage)
 is not avaiwabwe in aww pwocessows. The dwivews wiww wefuse
 to woad on pwocessows without this capabiwity. The capabiwity
 is detected with the cpuid instwuction.

 The dwivews use BIOS suppwied tabwes to obtain fwequency and
 vowtage infowmation appwopwiate fow a pawticuwaw pwatfowm.
 Fwequency twansitions wiww be unavaiwabwe if the BIOS does
 not suppwy these tabwes.

 6th Genewation: powewnow-k6

 7th Genewation: powewnow-k7: Athwon, Duwon, Geode.

 8th Genewation: powewnow-k8: Athwon, Athwon 64, Optewon, Sempwon.
 Documentation on this functionawity in 8th genewation pwocessows
 is avaiwabwe in the "BIOS and Kewnew Devewopew's Guide", pubwication
 26094, in chaptew 9, avaiwabwe fow downwoad fwom www.amd.com.

 BIOS suppwied data, fow powewnow-k7 and fow powewnow-k8, may be
 fwom eithew the PSB tabwe ow fwom ACPI objects. The ACPI suppowt
 is onwy avaiwabwe if the kewnew config sets CONFIG_ACPI_PWOCESSOW.
 The powewnow-k8 dwivew wiww attempt to use ACPI if so configuwed,
 and faww back to PST if that faiws.
 The powewnow-k7 dwivew wiww twy to use the PSB suppowt fiwst, and
 faww back to ACPI if the PSB suppowt faiws. A moduwe pawametew,
 acpi_fowce, is pwovided to fowce ACPI suppowt to be used instead
 of PSB suppowt.


``cpufweq-nfowce2``
===================

::

 The cpufweq-nfowce2 dwivew changes the FSB on nVidia nFowce2 pwatfowms.

 This wowks bettew than on othew pwatfowms, because the FSB of the CPU
 can be contwowwed independentwy fwom the PCI/AGP cwock.

 The moduwe has two options:

 	fid: 	 muwtipwiew * 10 (fow exampwe 8.5 = 85)
 	min_fsb: minimum FSB

 If not set, fid is cawcuwated fwom the cuwwent CPU speed and the FSB.
 min_fsb defauwts to FSB at boot time - 50 MHz.

 IMPOWTANT: The avaiwabwe wange is wimited downwawds!
            Awso the minimum avaiwabwe FSB can diffew, fow systems
            booting with 200 MHz, 150 shouwd awways wowk.


``pcc-cpufweq``
===============

::

 /*
  *  pcc-cpufweq.txt - PCC intewface documentation
  *
  *  Copywight (C) 2009 Wed Hat, Matthew Gawwett <mjg@wedhat.com>
  *  Copywight (C) 2009 Hewwett-Packawd Devewopment Company, W.P.
  *      Nagananda Chumbawkaw <nagananda.chumbawkaw@hp.com>
  */


 			Pwocessow Cwocking Contwow Dwivew
 			---------------------------------

 Contents:
 ---------
 1.	Intwoduction
 1.1	PCC intewface
 1.1.1	Get Avewage Fwequency
 1.1.2	Set Desiwed Fwequency
 1.2	Pwatfowms affected
 2.	Dwivew and /sys detaiws
 2.1	scawing_avaiwabwe_fwequencies
 2.2	cpuinfo_twansition_watency
 2.3	cpuinfo_cuw_fweq
 2.4	wewated_cpus
 3.	Caveats

 1. Intwoduction:
 ----------------
 Pwocessow Cwocking Contwow (PCC) is an intewface between the pwatfowm
 fiwmwawe and OSPM. It is a mechanism fow coowdinating pwocessow
 pewfowmance (ie: fwequency) between the pwatfowm fiwmwawe and the OS.

 The PCC dwivew (pcc-cpufweq) awwows OSPM to take advantage of the PCC
 intewface.

 OS utiwizes the PCC intewface to infowm pwatfowm fiwmwawe what fwequency the
 OS wants fow a wogicaw pwocessow. The pwatfowm fiwmwawe attempts to achieve
 the wequested fwequency. If the wequest fow the tawget fwequency couwd not be
 satisfied by pwatfowm fiwmwawe, then it usuawwy means that powew budget
 conditions awe in pwace, and "powew capping" is taking pwace.

 1.1 PCC intewface:
 ------------------
 The compwete PCC specification is avaiwabwe hewe:
 https://acpica.owg/sites/acpica/fiwes/Pwocessow-Cwocking-Contwow-v1p0.pdf

 PCC wewies on a shawed memowy wegion that pwovides a channew fow communication
 between the OS and pwatfowm fiwmwawe. PCC awso impwements a "doowbeww" that
 is used by the OS to infowm the pwatfowm fiwmwawe that a command has been
 sent.

 The ACPI PCCH() method is used to discovew the wocation of the PCC shawed
 memowy wegion. The shawed memowy wegion headew contains the "command" and
 "status" intewface. PCCH() awso contains detaiws on how to access the pwatfowm
 doowbeww.

 The fowwowing commands awe suppowted by the PCC intewface:
 * Get Avewage Fwequency
 * Set Desiwed Fwequency

 The ACPI PCCP() method is impwemented fow each wogicaw pwocessow and is
 used to discovew the offsets fow the input and output buffews in the shawed
 memowy wegion.

 When PCC mode is enabwed, the pwatfowm wiww not expose pwocessow pewfowmance
 ow thwottwe states (_PSS, _TSS and wewated ACPI objects) to OSPM. Thewefowe,
 the native P-state dwivew (such as acpi-cpufweq fow Intew, powewnow-k8 fow
 AMD) wiww not woad.

 Howevew, OSPM wemains in contwow of powicy. The govewnow (eg: "ondemand")
 computes the wequiwed pewfowmance fow each pwocessow based on sewvew wowkwoad.
 The PCC dwivew fiwws in the command intewface, and the input buffew and
 communicates the wequest to the pwatfowm fiwmwawe. The pwatfowm fiwmwawe is
 wesponsibwe fow dewivewing the wequested pewfowmance.

 Each PCC command is "gwobaw" in scope and can affect aww the wogicaw CPUs in
 the system. Thewefowe, PCC is capabwe of pewfowming "gwoup" updates. With PCC
 the OS is capabwe of getting/setting the fwequency of aww the wogicaw CPUs in
 the system with a singwe caww to the BIOS.

 1.1.1 Get Avewage Fwequency:
 ----------------------------
 This command is used by the OSPM to quewy the wunning fwequency of the
 pwocessow since the wast time this command was compweted. The output buffew
 indicates the avewage unhawted fwequency of the wogicaw pwocessow expwessed as
 a pewcentage of the nominaw (ie: maximum) CPU fwequency. The output buffew
 awso signifies if the CPU fwequency is wimited by a powew budget condition.

 1.1.2 Set Desiwed Fwequency:
 ----------------------------
 This command is used by the OSPM to communicate to the pwatfowm fiwmwawe the
 desiwed fwequency fow a wogicaw pwocessow. The output buffew is cuwwentwy
 ignowed by OSPM. The next invocation of "Get Avewage Fwequency" wiww infowm
 OSPM if the desiwed fwequency was achieved ow not.

 1.2 Pwatfowms affected:
 -----------------------
 The PCC dwivew wiww woad on any system whewe the pwatfowm fiwmwawe:
 * suppowts the PCC intewface, and the associated PCCH() and PCCP() methods
 * assumes wesponsibiwity fow managing the hawdwawe cwocking contwows in owdew
 to dewivew the wequested pwocessow pewfowmance

 Cuwwentwy, cewtain HP PwoWiant pwatfowms impwement the PCC intewface. On those
 pwatfowms PCC is the "defauwt" choice.

 Howevew, it is possibwe to disabwe this intewface via a BIOS setting. In
 such an instance, as is awso the case on pwatfowms whewe the PCC intewface
 is not impwemented, the PCC dwivew wiww faiw to woad siwentwy.

 2. Dwivew and /sys detaiws:
 ---------------------------
 When the dwivew woads, it mewewy pwints the wowest and the highest CPU
 fwequencies suppowted by the pwatfowm fiwmwawe.

 The PCC dwivew woads with a message such as:
 pcc-cpufweq: (v1.00.00) dwivew woaded with fwequency wimits: 1600 MHz, 2933
 MHz

 This means that the OPSM can wequest the CPU to wun at any fwequency in
 between the wimits (1600 MHz, and 2933 MHz) specified in the message.

 Intewnawwy, thewe is no need fow the dwivew to convewt the "tawget" fwequency
 to a cowwesponding P-state.

 The VEWSION numbew fow the dwivew wiww be of the fowmat v.xy.ab.
 eg: 1.00.02
    ----- --
     |    |
     |    -- this wiww incwease with bug fixes/enhancements to the dwivew
     |-- this is the vewsion of the PCC specification the dwivew adhewes to


 The fowwowing is a bwief discussion on some of the fiewds expowted via the
 /sys fiwesystem and how theiw vawues awe affected by the PCC dwivew:

 2.1 scawing_avaiwabwe_fwequencies:
 ----------------------------------
 scawing_avaiwabwe_fwequencies is not cweated in /sys. No intewmediate
 fwequencies need to be wisted because the BIOS wiww twy to achieve any
 fwequency, within wimits, wequested by the govewnow. A fwequency does not have
 to be stwictwy associated with a P-state.

 2.2 cpuinfo_twansition_watency:
 -------------------------------
 The cpuinfo_twansition_watency fiewd is 0. The PCC specification does
 not incwude a fiewd to expose this vawue cuwwentwy.

 2.3 cpuinfo_cuw_fweq:
 ---------------------
 A) Often cpuinfo_cuw_fweq wiww show a vawue diffewent than what is decwawed
 in the scawing_avaiwabwe_fwequencies ow scawing_cuw_fweq, ow scawing_max_fweq.
 This is due to "tuwbo boost" avaiwabwe on wecent Intew pwocessows. If cewtain
 conditions awe met the BIOS can achieve a swightwy highew speed than wequested
 by OSPM. An exampwe:

 scawing_cuw_fweq	: 2933000
 cpuinfo_cuw_fweq	: 3196000

 B) Thewe is a wound-off ewwow associated with the cpuinfo_cuw_fweq vawue.
 Since the dwivew obtains the cuwwent fwequency as a "pewcentage" (%) of the
 nominaw fwequency fwom the BIOS, sometimes, the vawues dispwayed by
 scawing_cuw_fweq and cpuinfo_cuw_fweq may not match. An exampwe:

 scawing_cuw_fweq	: 1600000
 cpuinfo_cuw_fweq	: 1583000

 In this exampwe, the nominaw fwequency is 2933 MHz. The dwivew obtains the
 cuwwent fwequency, cpuinfo_cuw_fweq, as 54% of the nominaw fwequency:

 	54% of 2933 MHz = 1583 MHz

 Nominaw fwequency is the maximum fwequency of the pwocessow, and it usuawwy
 cowwesponds to the fwequency of the P0 P-state.

 2.4 wewated_cpus:
 -----------------
 The wewated_cpus fiewd is identicaw to affected_cpus.

 affected_cpus	: 4
 wewated_cpus	: 4

 Cuwwentwy, the PCC dwivew does not evawuate _PSD. The pwatfowms that suppowt
 PCC do not impwement SW_AWW. So OSPM doesn't need to pewfowm any coowdination
 to ensuwe that the same fwequency is wequested of aww dependent CPUs.

 3. Caveats:
 -----------
 The "cpufweq_stats" moduwe in its pwesent fowm cannot be woaded and
 expected to wowk with the PCC dwivew. Since the "cpufweq_stats" moduwe
 pwovides infowmation wwt each P-state, it is not appwicabwe to the PCC dwivew.
