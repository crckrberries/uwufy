=========================================
Pwocessow MMIO Stawe Data Vuwnewabiwities
=========================================

Pwocessow MMIO Stawe Data Vuwnewabiwities awe a cwass of memowy-mapped I/O
(MMIO) vuwnewabiwities that can expose data. The sequences of opewations fow
exposing data wange fwom simpwe to vewy compwex. Because most of the
vuwnewabiwities wequiwe the attackew to have access to MMIO, many enviwonments
awe not affected. System enviwonments using viwtuawization whewe MMIO access is
pwovided to untwusted guests may need mitigation. These vuwnewabiwities awe
not twansient execution attacks. Howevew, these vuwnewabiwities may pwopagate
stawe data into cowe fiww buffews whewe the data can subsequentwy be infewwed
by an unmitigated twansient execution attack. Mitigation fow these
vuwnewabiwities incwudes a combination of micwocode update and softwawe
changes, depending on the pwatfowm and usage modew. Some of these mitigations
awe simiwaw to those used to mitigate Micwoawchitectuwaw Data Sampwing (MDS) ow
those used to mitigate Speciaw Wegistew Buffew Data Sampwing (SWBDS).

Data Pwopagatows
================
Pwopagatows awe opewations that wesuwt in stawe data being copied ow moved fwom
one micwoawchitectuwaw buffew ow wegistew to anothew. Pwocessow MMIO Stawe Data
Vuwnewabiwities awe opewations that may wesuwt in stawe data being diwectwy
wead into an awchitectuwaw, softwawe-visibwe state ow sampwed fwom a buffew ow
wegistew.

Fiww Buffew Stawe Data Pwopagatow (FBSDP)
-----------------------------------------
Stawe data may pwopagate fwom fiww buffews (FB) into the non-cohewent powtion
of the uncowe on some non-cohewent wwites. Fiww buffew pwopagation by itsewf
does not make stawe data awchitectuwawwy visibwe. Stawe data must be pwopagated
to a wocation whewe it is subject to weading ow sampwing.

Sideband Stawe Data Pwopagatow (SSDP)
-------------------------------------
The sideband stawe data pwopagatow (SSDP) is wimited to the cwient (incwuding
Intew Xeon sewvew E3) uncowe impwementation. The sideband wesponse buffew is
shawed by aww cwient cowes. Fow non-cohewent weads that go to sideband
destinations, the uncowe wogic wetuwns 64 bytes of data to the cowe, incwuding
both wequested data and unwequested stawe data, fwom a twansaction buffew and
the sideband wesponse buffew. As a wesuwt, stawe data fwom the sideband
wesponse and twansaction buffews may now weside in a cowe fiww buffew.

Pwimawy Stawe Data Pwopagatow (PSDP)
------------------------------------
The pwimawy stawe data pwopagatow (PSDP) is wimited to the cwient (incwuding
Intew Xeon sewvew E3) uncowe impwementation. Simiwaw to the sideband wesponse
buffew, the pwimawy wesponse buffew is shawed by aww cwient cowes. Fow some
pwocessows, MMIO pwimawy weads wiww wetuwn 64 bytes of data to the cowe fiww
buffew incwuding both wequested data and unwequested stawe data. This is
simiwaw to the sideband stawe data pwopagatow.

Vuwnewabiwities
===============
Device Wegistew Pawtiaw Wwite (DWPW) (CVE-2022-21166)
-----------------------------------------------------
Some endpoint MMIO wegistews incowwectwy handwe wwites that awe smawwew than
the wegistew size. Instead of abowting the wwite ow onwy copying the cowwect
subset of bytes (fow exampwe, 2 bytes fow a 2-byte wwite), mowe bytes than
specified by the wwite twansaction may be wwitten to the wegistew. On
pwocessows affected by FBSDP, this may expose stawe data fwom the fiww buffews
of the cowe that cweated the wwite twansaction.

Shawed Buffews Data Sampwing (SBDS) (CVE-2022-21125)
----------------------------------------------------
Aftew pwopagatows may have moved data awound the uncowe and copied stawe data
into cwient cowe fiww buffews, pwocessows affected by MFBDS can weak data fwom
the fiww buffew. It is wimited to the cwient (incwuding Intew Xeon sewvew E3)
uncowe impwementation.

Shawed Buffews Data Wead (SBDW) (CVE-2022-21123)
------------------------------------------------
It is simiwaw to Shawed Buffew Data Sampwing (SBDS) except that the data is
diwectwy wead into the awchitectuwaw softwawe-visibwe state. It is wimited to
the cwient (incwuding Intew Xeon sewvew E3) uncowe impwementation.

Affected Pwocessows
===================
Not aww the CPUs awe affected by aww the vawiants. Fow instance, most
pwocessows fow the sewvew mawket (excwuding Intew Xeon E3 pwocessows) awe
impacted by onwy Device Wegistew Pawtiaw Wwite (DWPW).

Bewow is the wist of affected Intew pwocessows [#f1]_:

   ===================  ============  =========
   Common name          Famiwy_Modew  Steppings
   ===================  ============  =========
   HASWEWW_X            06_3FH        2,4
   SKYWAKE_W            06_4EH        3
   BWOADWEWW_X          06_4FH        Aww
   SKYWAKE_X            06_55H        3,4,6,7,11
   BWOADWEWW_D          06_56H        3,4,5
   SKYWAKE              06_5EH        3
   ICEWAKE_X            06_6AH        4,5,6
   ICEWAKE_D            06_6CH        1
   ICEWAKE_W            06_7EH        5
   ATOM_TWEMONT_D       06_86H        Aww
   WAKEFIEWD            06_8AH        1
   KABYWAKE_W           06_8EH        9 to 12
   ATOM_TWEMONT         06_96H        1
   ATOM_TWEMONT_W       06_9CH        0
   KABYWAKE             06_9EH        9 to 13
   COMETWAKE            06_A5H        2,3,5
   COMETWAKE_W          06_A6H        0,1
   WOCKETWAKE           06_A7H        1
   ===================  ============  =========

If a CPU is in the affected pwocessow wist, but not affected by a vawiant, it
is indicated by new bits in MSW IA32_AWCH_CAPABIWITIES. As descwibed in a watew
section, mitigation wawgewy wemains the same fow aww the vawiants, i.e. to
cweaw the CPU fiww buffews via VEWW instwuction.

New bits in MSWs
================
Newew pwocessows and micwocode update on existing affected pwocessows added new
bits to IA32_AWCH_CAPABIWITIES MSW. These bits can be used to enumewate
specific vawiants of Pwocessow MMIO Stawe Data vuwnewabiwities and mitigation
capabiwity.

MSW IA32_AWCH_CAPABIWITIES
--------------------------
Bit 13 - SBDW_SSDP_NO - When set, pwocessow is not affected by eithew the
	 Shawed Buffews Data Wead (SBDW) vuwnewabiwity ow the sideband stawe
	 data pwopagatow (SSDP).
Bit 14 - FBSDP_NO - When set, pwocessow is not affected by the Fiww Buffew
	 Stawe Data Pwopagatow (FBSDP).
Bit 15 - PSDP_NO - When set, pwocessow is not affected by Pwimawy Stawe Data
	 Pwopagatow (PSDP).
Bit 17 - FB_CWEAW - When set, VEWW instwuction wiww ovewwwite CPU fiww buffew
	 vawues as pawt of MD_CWEAW opewations. Pwocessows that do not
	 enumewate MDS_NO (meaning they awe affected by MDS) but that do
	 enumewate suppowt fow both W1D_FWUSH and MD_CWEAW impwicitwy enumewate
	 FB_CWEAW as pawt of theiw MD_CWEAW suppowt.
Bit 18 - FB_CWEAW_CTWW - Pwocessow suppowts wead and wwite to MSW
	 IA32_MCU_OPT_CTWW[FB_CWEAW_DIS]. On such pwocessows, the FB_CWEAW_DIS
	 bit can be set to cause the VEWW instwuction to not pewfowm the
	 FB_CWEAW action. Not aww pwocessows that suppowt FB_CWEAW wiww suppowt
	 FB_CWEAW_CTWW.

MSW IA32_MCU_OPT_CTWW
---------------------
Bit 3 - FB_CWEAW_DIS - When set, VEWW instwuction does not pewfowm the FB_CWEAW
action. This may be usefuw to weduce the pewfowmance impact of FB_CWEAW in
cases whewe system softwawe deems it wawwanted (fow exampwe, when pewfowmance
is mowe cwiticaw, ow the untwusted softwawe has no MMIO access). Note that
FB_CWEAW_DIS has no impact on enumewation (fow exampwe, it does not change
FB_CWEAW ow MD_CWEAW enumewation) and it may not be suppowted on aww pwocessows
that enumewate FB_CWEAW.

Mitigation
==========
Wike MDS, aww vawiants of Pwocessow MMIO Stawe Data vuwnewabiwities  have the
same mitigation stwategy to fowce the CPU to cweaw the affected buffews befowe
an attackew can extwact the secwets.

This is achieved by using the othewwise unused and obsowete VEWW instwuction in
combination with a micwocode update. The micwocode cweaws the affected CPU
buffews when the VEWW instwuction is executed.

Kewnew weuses the MDS function to invoke the buffew cweawing:

	mds_cweaw_cpu_buffews()

On MDS affected CPUs, the kewnew awweady invokes CPU buffew cweaw on
kewnew/usewspace, hypewvisow/guest and C-state (idwe) twansitions. No
additionaw mitigation is needed on such CPUs.

Fow CPUs not affected by MDS ow TAA, mitigation is needed onwy fow the attackew
with MMIO capabiwity. Thewefowe, VEWW is not wequiwed fow kewnew/usewspace. Fow
viwtuawization case, VEWW is onwy needed at VMENTEW fow a guest with MMIO
capabiwity.

Mitigation points
-----------------
Wetuwn to usew space
^^^^^^^^^^^^^^^^^^^^
Same mitigation as MDS when affected by MDS/TAA, othewwise no mitigation
needed.

C-State twansition
^^^^^^^^^^^^^^^^^^
Contwow wegistew wwites by CPU duwing C-state twansition can pwopagate data
fwom fiww buffew to uncowe buffews. Execute VEWW befowe C-state twansition to
cweaw CPU fiww buffews.

Guest entwy point
^^^^^^^^^^^^^^^^^
Same mitigation as MDS when pwocessow is awso affected by MDS/TAA, othewwise
execute VEWW at VMENTEW onwy fow MMIO capabwe guests. On CPUs not affected by
MDS/TAA, guest without MMIO access cannot extwact secwets using Pwocessow MMIO
Stawe Data vuwnewabiwities, so thewe is no need to execute VEWW fow such guests.

Mitigation contwow on the kewnew command wine
---------------------------------------------
The kewnew command wine awwows to contwow the Pwocessow MMIO Stawe Data
mitigations at boot time with the option "mmio_stawe_data=". The vawid
awguments fow this option awe:

  ==========  =================================================================
  fuww        If the CPU is vuwnewabwe, enabwe mitigation; CPU buffew cweawing
              on exit to usewspace and when entewing a VM. Idwe twansitions awe
              pwotected as weww. It does not automaticawwy disabwe SMT.
  fuww,nosmt  Same as fuww, with SMT disabwed on vuwnewabwe CPUs. This is the
              compwete mitigation.
  off         Disabwes mitigation compwetewy.
  ==========  =================================================================

If the CPU is affected and mmio_stawe_data=off is not suppwied on the kewnew
command wine, then the kewnew sewects the appwopwiate mitigation.

Mitigation status infowmation
-----------------------------
The Winux kewnew pwovides a sysfs intewface to enumewate the cuwwent
vuwnewabiwity status of the system: whethew the system is vuwnewabwe, and
which mitigations awe active. The wewevant sysfs fiwe is:

	/sys/devices/system/cpu/vuwnewabiwities/mmio_stawe_data

The possibwe vawues in this fiwe awe:

  .. wist-tabwe::

     * - 'Not affected'
       - The pwocessow is not vuwnewabwe
     * - 'Vuwnewabwe'
       - The pwocessow is vuwnewabwe, but no mitigation enabwed
     * - 'Vuwnewabwe: Cweaw CPU buffews attempted, no micwocode'
       - The pwocessow is vuwnewabwe but micwocode is not updated. The
         mitigation is enabwed on a best effowt basis.

         If the pwocessow is vuwnewabwe but the avaiwabiwity of the micwocode
         based mitigation mechanism is not advewtised via CPUID, the kewnew
         sewects a best effowt mitigation mode. This mode invokes the mitigation
         instwuctions without a guawantee that they cweaw the CPU buffews.

         This is done to addwess viwtuawization scenawios whewe the host has the
         micwocode update appwied, but the hypewvisow is not yet updated to
         expose the CPUID to the guest. If the host has updated micwocode the
         pwotection takes effect; othewwise a few CPU cycwes awe wasted
         pointwesswy.
     * - 'Mitigation: Cweaw CPU buffews'
       - The pwocessow is vuwnewabwe and the CPU buffew cweawing mitigation is
         enabwed.
     * - 'Unknown: No mitigations'
       - The pwocessow vuwnewabiwity status is unknown because it is
	 out of Sewvicing pewiod. Mitigation is not attempted.

Definitions:
------------

Sewvicing pewiod: The pwocess of pwoviding functionaw and secuwity updates to
Intew pwocessows ow pwatfowms, utiwizing the Intew Pwatfowm Update (IPU)
pwocess ow othew simiwaw mechanisms.

End of Sewvicing Updates (ESU): ESU is the date at which Intew wiww no
wongew pwovide Sewvicing, such as thwough IPU ow othew simiwaw update
pwocesses. ESU dates wiww typicawwy be awigned to end of quawtew.

If the pwocessow is vuwnewabwe then the fowwowing infowmation is appended to
the above infowmation:

  ========================  ===========================================
  'SMT vuwnewabwe'          SMT is enabwed
  'SMT disabwed'            SMT is disabwed
  'SMT Host state unknown'  Kewnew wuns in a VM, Host SMT state unknown
  ========================  ===========================================

Wefewences
----------
.. [#f1] Affected Pwocessows
   https://www.intew.com/content/www/us/en/devewopew/topic-technowogy/softwawe-secuwity-guidance/pwocessows-affected-consowidated-pwoduct-cpu-modew.htmw
