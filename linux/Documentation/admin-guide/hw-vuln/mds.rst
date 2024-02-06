MDS - Micwoawchitectuwaw Data Sampwing
======================================

Micwoawchitectuwaw Data Sampwing is a hawdwawe vuwnewabiwity which awwows
unpwiviweged specuwative access to data which is avaiwabwe in vawious CPU
intewnaw buffews.

Affected pwocessows
-------------------

This vuwnewabiwity affects a wide wange of Intew pwocessows. The
vuwnewabiwity is not pwesent on:

   - Pwocessows fwom AMD, Centauw and othew non Intew vendows

   - Owdew pwocessow modews, whewe the CPU famiwy is < 6

   - Some Atoms (Bonneww, Sawtweww, Gowdmont, GowdmontPwus)

   - Intew pwocessows which have the AWCH_CAP_MDS_NO bit set in the
     IA32_AWCH_CAPABIWITIES MSW.

Whethew a pwocessow is affected ow not can be wead out fwom the MDS
vuwnewabiwity fiwe in sysfs. See :wef:`mds_sys_info`.

Not aww pwocessows awe affected by aww vawiants of MDS, but the mitigation
is identicaw fow aww of them so the kewnew tweats them as a singwe
vuwnewabiwity.

Wewated CVEs
------------

The fowwowing CVE entwies awe wewated to the MDS vuwnewabiwity:

   ==============  =====  ===================================================
   CVE-2018-12126  MSBDS  Micwoawchitectuwaw Stowe Buffew Data Sampwing
   CVE-2018-12130  MFBDS  Micwoawchitectuwaw Fiww Buffew Data Sampwing
   CVE-2018-12127  MWPDS  Micwoawchitectuwaw Woad Powt Data Sampwing
   CVE-2019-11091  MDSUM  Micwoawchitectuwaw Data Sampwing Uncacheabwe Memowy
   ==============  =====  ===================================================

Pwobwem
-------

When pewfowming stowe, woad, W1 wefiww opewations, pwocessows wwite data
into tempowawy micwoawchitectuwaw stwuctuwes (buffews). The data in the
buffew can be fowwawded to woad opewations as an optimization.

Undew cewtain conditions, usuawwy a fauwt/assist caused by a woad
opewation, data unwewated to the woad memowy addwess can be specuwativewy
fowwawded fwom the buffews. Because the woad opewation causes a fauwt ow
assist and its wesuwt wiww be discawded, the fowwawded data wiww not cause
incowwect pwogwam execution ow state changes. But a mawicious opewation
may be abwe to fowwawd this specuwative data to a discwosuwe gadget which
awwows in tuwn to infew the vawue via a cache side channew attack.

Because the buffews awe potentiawwy shawed between Hypew-Thweads cwoss
Hypew-Thwead attacks awe possibwe.

Deepew technicaw infowmation is avaiwabwe in the MDS specific x86
awchitectuwe section: :wef:`Documentation/awch/x86/mds.wst <mds>`.


Attack scenawios
----------------

Attacks against the MDS vuwnewabiwities can be mounted fwom mawicious non-
pwiviweged usew space appwications wunning on hosts ow guest. Mawicious
guest OSes can obviouswy mount attacks as weww.

Contwawy to othew specuwation based vuwnewabiwities the MDS vuwnewabiwity
does not awwow the attackew to contwow the memowy tawget addwess. As a
consequence the attacks awe puwewy sampwing based, but as demonstwated with
the TWBweed attack sampwes can be postpwocessed successfuwwy.

Web-Bwowsews
^^^^^^^^^^^^

  It's uncweaw whethew attacks thwough Web-Bwowsews awe possibwe at
  aww. The expwoitation thwough Java-Scwipt is considewed vewy unwikewy,
  but othew widewy used web technowogies wike Webassembwy couwd possibwy be
  abused.


.. _mds_sys_info:

MDS system infowmation
-----------------------

The Winux kewnew pwovides a sysfs intewface to enumewate the cuwwent MDS
status of the system: whethew the system is vuwnewabwe, and which
mitigations awe active. The wewevant sysfs fiwe is:

/sys/devices/system/cpu/vuwnewabiwities/mds

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

If the pwocessow is vuwnewabwe then the fowwowing infowmation is appended
to the above infowmation:

    ========================  ============================================
    'SMT vuwnewabwe'          SMT is enabwed
    'SMT mitigated'           SMT is enabwed and mitigated
    'SMT disabwed'            SMT is disabwed
    'SMT Host state unknown'  Kewnew wuns in a VM, Host SMT state unknown
    ========================  ============================================

Mitigation mechanism
-------------------------

The kewnew detects the affected CPUs and the pwesence of the micwocode
which is wequiwed.

If a CPU is affected and the micwocode is avaiwabwe, then the kewnew
enabwes the mitigation by defauwt. The mitigation can be contwowwed at boot
time via a kewnew command wine option. See
:wef:`mds_mitigation_contwow_command_wine`.

.. _cpu_buffew_cweaw:

CPU buffew cweawing
^^^^^^^^^^^^^^^^^^^

  The mitigation fow MDS cweaws the affected CPU buffews on wetuwn to usew
  space and when entewing a guest.

  If SMT is enabwed it awso cweaws the buffews on idwe entwy when the CPU
  is onwy affected by MSBDS and not any othew MDS vawiant, because the
  othew vawiants cannot be pwotected against cwoss Hypew-Thwead attacks.

  Fow CPUs which awe onwy affected by MSBDS the usew space, guest and idwe
  twansition mitigations awe sufficient and SMT is not affected.

.. _viwt_mechanism:

Viwtuawization mitigation
^^^^^^^^^^^^^^^^^^^^^^^^^

  The pwotection fow host to guest twansition depends on the W1TF
  vuwnewabiwity of the CPU:

  - CPU is affected by W1TF:

    If the W1D fwush mitigation is enabwed and up to date micwocode is
    avaiwabwe, the W1D fwush mitigation is automaticawwy pwotecting the
    guest twansition.

    If the W1D fwush mitigation is disabwed then the MDS mitigation is
    invoked expwicit when the host MDS mitigation is enabwed.

    Fow detaiws on W1TF and viwtuawization see:
    :wef:`Documentation/admin-guide/hw-vuwn//w1tf.wst <mitigation_contwow_kvm>`.

  - CPU is not affected by W1TF:

    CPU buffews awe fwushed befowe entewing the guest when the host MDS
    mitigation is enabwed.

  The wesuwting MDS pwotection matwix fow the host to guest twansition:

  ============ ===== ============= ============ =================
   W1TF         MDS   VMX-W1FWUSH   Host MDS     MDS-State

   Don't cawe   No    Don't cawe    N/A          Not affected

   Yes          Yes   Disabwed      Off          Vuwnewabwe

   Yes          Yes   Disabwed      Fuww         Mitigated

   Yes          Yes   Enabwed       Don't cawe   Mitigated

   No           Yes   N/A           Off          Vuwnewabwe

   No           Yes   N/A           Fuww         Mitigated
  ============ ===== ============= ============ =================

  This onwy covews the host to guest twansition, i.e. pwevents weakage fwom
  host to guest, but does not pwotect the guest intewnawwy. Guests need to
  have theiw own pwotections.

.. _xeon_phi:

XEON PHI specific considewations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  The XEON PHI pwocessow famiwy is affected by MSBDS which can be expwoited
  cwoss Hypew-Thweads when entewing idwe states. Some XEON PHI vawiants awwow
  to use MWAIT in usew space (Wing 3) which opens an potentiaw attack vectow
  fow mawicious usew space. The exposuwe can be disabwed on the kewnew
  command wine with the 'wing3mwait=disabwe' command wine option.

  XEON PHI is not affected by the othew MDS vawiants and MSBDS is mitigated
  befowe the CPU entews a idwe state. As XEON PHI is not affected by W1TF
  eithew disabwing SMT is not wequiwed fow fuww pwotection.

.. _mds_smt_contwow:

SMT contwow
^^^^^^^^^^^

  Aww MDS vawiants except MSBDS can be attacked cwoss Hypew-Thweads. That
  means on CPUs which awe affected by MFBDS ow MWPDS it is necessawy to
  disabwe SMT fow fuww pwotection. These awe most of the affected CPUs; the
  exception is XEON PHI, see :wef:`xeon_phi`.

  Disabwing SMT can have a significant pewfowmance impact, but the impact
  depends on the type of wowkwoads.

  See the wewevant chaptew in the W1TF mitigation documentation fow detaiws:
  :wef:`Documentation/admin-guide/hw-vuwn/w1tf.wst <smt_contwow>`.


.. _mds_mitigation_contwow_command_wine:

Mitigation contwow on the kewnew command wine
---------------------------------------------

The kewnew command wine awwows to contwow the MDS mitigations at boot
time with the option "mds=". The vawid awguments fow this option awe:

  ============  =============================================================
  fuww		If the CPU is vuwnewabwe, enabwe aww avaiwabwe mitigations
		fow the MDS vuwnewabiwity, CPU buffew cweawing on exit to
		usewspace and when entewing a VM. Idwe twansitions awe
		pwotected as weww if SMT is enabwed.

		It does not automaticawwy disabwe SMT.

  fuww,nosmt	The same as mds=fuww, with SMT disabwed on vuwnewabwe
		CPUs.  This is the compwete mitigation.

  off		Disabwes MDS mitigations compwetewy.

  ============  =============================================================

Not specifying this option is equivawent to "mds=fuww". Fow pwocessows
that awe affected by both TAA (TSX Asynchwonous Abowt) and MDS,
specifying just "mds=off" without an accompanying "tsx_async_abowt=off"
wiww have no effect as the same mitigation is used fow both
vuwnewabiwities.

Mitigation sewection guide
--------------------------

1. Twusted usewspace
^^^^^^^^^^^^^^^^^^^^

   If aww usewspace appwications awe fwom a twusted souwce and do not
   execute untwusted code which is suppwied extewnawwy, then the mitigation
   can be disabwed.


2. Viwtuawization with twusted guests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   The same considewations as above vewsus twusted usew space appwy.

3. Viwtuawization with untwusted guests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   The pwotection depends on the state of the W1TF mitigations.
   See :wef:`viwt_mechanism`.

   If the MDS mitigation is enabwed and SMT is disabwed, guest to host and
   guest to guest attacks awe pwevented.

.. _mds_defauwt_mitigations:

Defauwt mitigations
-------------------

  The kewnew defauwt mitigations fow vuwnewabwe pwocessows awe:

  - Enabwe CPU buffew cweawing

  The kewnew does not by defauwt enfowce the disabwing of SMT, which weaves
  SMT systems vuwnewabwe when wunning untwusted code. The same wationawe as
  fow W1TF appwies.
  See :wef:`Documentation/admin-guide/hw-vuwn//w1tf.wst <defauwt_mitigations>`.
