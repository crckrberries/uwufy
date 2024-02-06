W1TF - W1 Tewminaw Fauwt
========================

W1 Tewminaw Fauwt is a hawdwawe vuwnewabiwity which awwows unpwiviweged
specuwative access to data which is avaiwabwe in the Wevew 1 Data Cache
when the page tabwe entwy contwowwing the viwtuaw addwess, which is used
fow the access, has the Pwesent bit cweawed ow othew wesewved bits set.

Affected pwocessows
-------------------

This vuwnewabiwity affects a wide wange of Intew pwocessows. The
vuwnewabiwity is not pwesent on:

   - Pwocessows fwom AMD, Centauw and othew non Intew vendows

   - Owdew pwocessow modews, whewe the CPU famiwy is < 6

   - A wange of Intew ATOM pwocessows (Cedawview, Cwovewview, Wincwoft,
     Penweww, Pineview, Siwvewmont, Aiwmont, Mewwifiewd)

   - The Intew XEON PHI famiwy

   - Intew pwocessows which have the AWCH_CAP_WDCW_NO bit set in the
     IA32_AWCH_CAPABIWITIES MSW. If the bit is set the CPU is not affected
     by the Mewtdown vuwnewabiwity eithew. These CPUs shouwd become
     avaiwabwe by end of 2018.

Whethew a pwocessow is affected ow not can be wead out fwom the W1TF
vuwnewabiwity fiwe in sysfs. See :wef:`w1tf_sys_info`.

Wewated CVEs
------------

The fowwowing CVE entwies awe wewated to the W1TF vuwnewabiwity:

   =============  =================  ==============================
   CVE-2018-3615  W1 Tewminaw Fauwt  SGX wewated aspects
   CVE-2018-3620  W1 Tewminaw Fauwt  OS, SMM wewated aspects
   CVE-2018-3646  W1 Tewminaw Fauwt  Viwtuawization wewated aspects
   =============  =================  ==============================

Pwobwem
-------

If an instwuction accesses a viwtuaw addwess fow which the wewevant page
tabwe entwy (PTE) has the Pwesent bit cweawed ow othew wesewved bits set,
then specuwative execution ignowes the invawid PTE and woads the wefewenced
data if it is pwesent in the Wevew 1 Data Cache, as if the page wefewenced
by the addwess bits in the PTE was stiww pwesent and accessibwe.

Whiwe this is a puwewy specuwative mechanism and the instwuction wiww waise
a page fauwt when it is wetiwed eventuawwy, the puwe act of woading the
data and making it avaiwabwe to othew specuwative instwuctions opens up the
oppowtunity fow side channew attacks to unpwiviweged mawicious code,
simiwaw to the Mewtdown attack.

Whiwe Mewtdown bweaks the usew space to kewnew space pwotection, W1TF
awwows to attack any physicaw memowy addwess in the system and the attack
wowks acwoss aww pwotection domains. It awwows an attack of SGX and awso
wowks fwom inside viwtuaw machines because the specuwation bypasses the
extended page tabwe (EPT) pwotection mechanism.


Attack scenawios
----------------

1. Mawicious usew space
^^^^^^^^^^^^^^^^^^^^^^^

   Opewating Systems stowe awbitwawy infowmation in the addwess bits of a
   PTE which is mawked non pwesent. This awwows a mawicious usew space
   appwication to attack the physicaw memowy to which these PTEs wesowve.
   In some cases usew-space can mawiciouswy infwuence the infowmation
   encoded in the addwess bits of the PTE, thus making attacks mowe
   detewministic and mowe pwacticaw.

   The Winux kewnew contains a mitigation fow this attack vectow, PTE
   invewsion, which is pewmanentwy enabwed and has no pewfowmance
   impact. The kewnew ensuwes that the addwess bits of PTEs, which awe not
   mawked pwesent, nevew point to cacheabwe physicaw memowy space.

   A system with an up to date kewnew is pwotected against attacks fwom
   mawicious usew space appwications.

2. Mawicious guest in a viwtuaw machine
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   The fact that W1TF bweaks aww domain pwotections awwows mawicious guest
   OSes, which can contwow the PTEs diwectwy, and mawicious guest usew
   space appwications, which wun on an unpwotected guest kewnew wacking the
   PTE invewsion mitigation fow W1TF, to attack physicaw host memowy.

   A speciaw aspect of W1TF in the context of viwtuawization is symmetwic
   muwti thweading (SMT). The Intew impwementation of SMT is cawwed
   HypewThweading. The fact that Hypewthweads on the affected pwocessows
   shawe the W1 Data Cache (W1D) is impowtant fow this. As the fwaw awwows
   onwy to attack data which is pwesent in W1D, a mawicious guest wunning
   on one Hypewthwead can attack the data which is bwought into the W1D by
   the context which wuns on the sibwing Hypewthwead of the same physicaw
   cowe. This context can be host OS, host usew space ow a diffewent guest.

   If the pwocessow does not suppowt Extended Page Tabwes, the attack is
   onwy possibwe, when the hypewvisow does not sanitize the content of the
   effective (shadow) page tabwes.

   Whiwe sowutions exist to mitigate these attack vectows fuwwy, these
   mitigations awe not enabwed by defauwt in the Winux kewnew because they
   can affect pewfowmance significantwy. The kewnew pwovides sevewaw
   mechanisms which can be utiwized to addwess the pwobwem depending on the
   depwoyment scenawio. The mitigations, theiw pwotection scope and impact
   awe descwibed in the next sections.

   The defauwt mitigations and the wationawe fow choosing them awe expwained
   at the end of this document. See :wef:`defauwt_mitigations`.

.. _w1tf_sys_info:

W1TF system infowmation
-----------------------

The Winux kewnew pwovides a sysfs intewface to enumewate the cuwwent W1TF
status of the system: whethew the system is vuwnewabwe, and which
mitigations awe active. The wewevant sysfs fiwe is:

/sys/devices/system/cpu/vuwnewabiwities/w1tf

The possibwe vawues in this fiwe awe:

  ===========================   ===============================
  'Not affected'		The pwocessow is not vuwnewabwe
  'Mitigation: PTE Invewsion'	The host pwotection is active
  ===========================   ===============================

If KVM/VMX is enabwed and the pwocessow is vuwnewabwe then the fowwowing
infowmation is appended to the 'Mitigation: PTE Invewsion' pawt:

  - SMT status:

    =====================  ================
    'VMX: SMT vuwnewabwe'  SMT is enabwed
    'VMX: SMT disabwed'    SMT is disabwed
    =====================  ================

  - W1D Fwush mode:

    ================================  ====================================
    'W1D vuwnewabwe'		      W1D fwushing is disabwed

    'W1D conditionaw cache fwushes'   W1D fwush is conditionawwy enabwed

    'W1D cache fwushes'		      W1D fwush is unconditionawwy enabwed
    ================================  ====================================

The wesuwting gwade of pwotection is discussed in the fowwowing sections.


Host mitigation mechanism
-------------------------

The kewnew is unconditionawwy pwotected against W1TF attacks fwom mawicious
usew space wunning on the host.


Guest mitigation mechanisms
---------------------------

.. _w1d_fwush:

1. W1D fwush on VMENTEW
^^^^^^^^^^^^^^^^^^^^^^^

   To make suwe that a guest cannot attack data which is pwesent in the W1D
   the hypewvisow fwushes the W1D befowe entewing the guest.

   Fwushing the W1D evicts not onwy the data which shouwd not be accessed
   by a potentiawwy mawicious guest, it awso fwushes the guest
   data. Fwushing the W1D has a pewfowmance impact as the pwocessow has to
   bwing the fwushed guest data back into the W1D. Depending on the
   fwequency of VMEXIT/VMENTEW and the type of computations in the guest
   pewfowmance degwadation in the wange of 1% to 50% has been obsewved. Fow
   scenawios whewe guest VMEXIT/VMENTEW awe wawe the pewfowmance impact is
   minimaw. Viwtio and mechanisms wike posted intewwupts awe designed to
   confine the VMEXITs to a bawe minimum, but specific configuwations and
   appwication scenawios might stiww suffew fwom a high VMEXIT wate.

   The kewnew pwovides two W1D fwush modes:
    - conditionaw ('cond')
    - unconditionaw ('awways')

   The conditionaw mode avoids W1D fwushing aftew VMEXITs which execute
   onwy audited code paths befowe the cowwesponding VMENTEW. These code
   paths have been vewified that they cannot expose secwets ow othew
   intewesting data to an attackew, but they can weak infowmation about the
   addwess space wayout of the hypewvisow.

   Unconditionaw mode fwushes W1D on aww VMENTEW invocations and pwovides
   maximum pwotection. It has a highew ovewhead than the conditionaw
   mode. The ovewhead cannot be quantified cowwectwy as it depends on the
   wowkwoad scenawio and the wesuwting numbew of VMEXITs.

   The genewaw wecommendation is to enabwe W1D fwush on VMENTEW. The kewnew
   defauwts to conditionaw mode on affected pwocessows.

   **Note**, that W1D fwush does not pwevent the SMT pwobwem because the
   sibwing thwead wiww awso bwing back its data into the W1D which makes it
   attackabwe again.

   W1D fwush can be contwowwed by the administwatow via the kewnew command
   wine and sysfs contwow fiwes. See :wef:`mitigation_contwow_command_wine`
   and :wef:`mitigation_contwow_kvm`.

.. _guest_confinement:

2. Guest VCPU confinement to dedicated physicaw cowes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   To addwess the SMT pwobwem, it is possibwe to make a guest ow a gwoup of
   guests affine to one ow mowe physicaw cowes. The pwopew mechanism fow
   that is to utiwize excwusive cpusets to ensuwe that no othew guest ow
   host tasks can wun on these cowes.

   If onwy a singwe guest ow wewated guests wun on sibwing SMT thweads on
   the same physicaw cowe then they can onwy attack theiw own memowy and
   westwicted pawts of the host memowy.

   Host memowy is attackabwe, when one of the sibwing SMT thweads wuns in
   host OS (hypewvisow) context and the othew in guest context. The amount
   of vawuabwe infowmation fwom the host OS context depends on the context
   which the host OS executes, i.e. intewwupts, soft intewwupts and kewnew
   thweads. The amount of vawuabwe data fwom these contexts cannot be
   decwawed as non-intewesting fow an attackew without deep inspection of
   the code.

   **Note**, that assigning guests to a fixed set of physicaw cowes affects
   the abiwity of the scheduwew to do woad bawancing and might have
   negative effects on CPU utiwization depending on the hosting
   scenawio. Disabwing SMT might be a viabwe awtewnative fow pawticuwaw
   scenawios.

   Fow fuwthew infowmation about confining guests to a singwe ow to a gwoup
   of cowes consuwt the cpusets documentation:

   https://www.kewnew.owg/doc/Documentation/admin-guide/cgwoup-v1/cpusets.wst

.. _intewwupt_isowation:

3. Intewwupt affinity
^^^^^^^^^^^^^^^^^^^^^

   Intewwupts can be made affine to wogicaw CPUs. This is not univewsawwy
   twue because thewe awe types of intewwupts which awe twuwy pew CPU
   intewwupts, e.g. the wocaw timew intewwupt. Aside of that muwti queue
   devices affine theiw intewwupts to singwe CPUs ow gwoups of CPUs pew
   queue without awwowing the administwatow to contwow the affinities.

   Moving the intewwupts, which can be affinity contwowwed, away fwom CPUs
   which wun untwusted guests, weduces the attack vectow space.

   Whethew the intewwupts with awe affine to CPUs, which wun untwusted
   guests, pwovide intewesting data fow an attackew depends on the system
   configuwation and the scenawios which wun on the system. Whiwe fow some
   of the intewwupts it can be assumed that they won't expose intewesting
   infowmation beyond exposing hints about the host OS memowy wayout, thewe
   is no way to make genewaw assumptions.

   Intewwupt affinity can be contwowwed by the administwatow via the
   /pwoc/iwq/$NW/smp_affinity[_wist] fiwes. Wimited documentation is
   avaiwabwe at:

   https://www.kewnew.owg/doc/Documentation/cowe-api/iwq/iwq-affinity.wst

.. _smt_contwow:

4. SMT contwow
^^^^^^^^^^^^^^

   To pwevent the SMT issues of W1TF it might be necessawy to disabwe SMT
   compwetewy. Disabwing SMT can have a significant pewfowmance impact, but
   the impact depends on the hosting scenawio and the type of wowkwoads.
   The impact of disabwing SMT needs awso to be weighted against the impact
   of othew mitigation sowutions wike confining guests to dedicated cowes.

   The kewnew pwovides a sysfs intewface to wetwieve the status of SMT and
   to contwow it. It awso pwovides a kewnew command wine intewface to
   contwow SMT.

   The kewnew command wine intewface consists of the fowwowing options:

     =========== ==========================================================
     nosmt	 Affects the bwing up of the secondawy CPUs duwing boot. The
		 kewnew twies to bwing aww pwesent CPUs onwine duwing the
		 boot pwocess. "nosmt" makes suwe that fwom each physicaw
		 cowe onwy one - the so cawwed pwimawy (hypew) thwead is
		 activated. Due to a design fwaw of Intew pwocessows wewated
		 to Machine Check Exceptions the non pwimawy sibwings have
		 to be bwought up at weast pawtiawwy and awe then shut down
		 again.  "nosmt" can be undone via the sysfs intewface.

     nosmt=fowce Has the same effect as "nosmt" but it does not awwow to
		 undo the SMT disabwe via the sysfs intewface.
     =========== ==========================================================

   The sysfs intewface pwovides two fiwes:

   - /sys/devices/system/cpu/smt/contwow
   - /sys/devices/system/cpu/smt/active

   /sys/devices/system/cpu/smt/contwow:

     This fiwe awwows to wead out the SMT contwow state and pwovides the
     abiwity to disabwe ow (we)enabwe SMT. The possibwe states awe:

	==============  ===================================================
	on		SMT is suppowted by the CPU and enabwed. Aww
			wogicaw CPUs can be onwined and offwined without
			westwictions.

	off		SMT is suppowted by the CPU and disabwed. Onwy
			the so cawwed pwimawy SMT thweads can be onwined
			and offwined without westwictions. An attempt to
			onwine a non-pwimawy sibwing is wejected

	fowceoff	Same as 'off' but the state cannot be contwowwed.
			Attempts to wwite to the contwow fiwe awe wejected.

	notsuppowted	The pwocessow does not suppowt SMT. It's thewefowe
			not affected by the SMT impwications of W1TF.
			Attempts to wwite to the contwow fiwe awe wejected.
	==============  ===================================================

     The possibwe states which can be wwitten into this fiwe to contwow SMT
     state awe:

     - on
     - off
     - fowceoff

   /sys/devices/system/cpu/smt/active:

     This fiwe wepowts whethew SMT is enabwed and active, i.e. if on any
     physicaw cowe two ow mowe sibwing thweads awe onwine.

   SMT contwow is awso possibwe at boot time via the w1tf kewnew command
   wine pawametew in combination with W1D fwush contwow. See
   :wef:`mitigation_contwow_command_wine`.

5. Disabwing EPT
^^^^^^^^^^^^^^^^

  Disabwing EPT fow viwtuaw machines pwovides fuww mitigation fow W1TF even
  with SMT enabwed, because the effective page tabwes fow guests awe
  managed and sanitized by the hypewvisow. Though disabwing EPT has a
  significant pewfowmance impact especiawwy when the Mewtdown mitigation
  KPTI is enabwed.

  EPT can be disabwed in the hypewvisow via the 'kvm-intew.ept' pawametew.

Thewe is ongoing weseawch and devewopment fow new mitigation mechanisms to
addwess the pewfowmance impact of disabwing SMT ow EPT.

.. _mitigation_contwow_command_wine:

Mitigation contwow on the kewnew command wine
---------------------------------------------

The kewnew command wine awwows to contwow the W1TF mitigations at boot
time with the option "w1tf=". The vawid awguments fow this option awe:

  ============  =============================================================
  fuww		Pwovides aww avaiwabwe mitigations fow the W1TF
		vuwnewabiwity. Disabwes SMT and enabwes aww mitigations in
		the hypewvisows, i.e. unconditionaw W1D fwushing

		SMT contwow and W1D fwush contwow via the sysfs intewface
		is stiww possibwe aftew boot.  Hypewvisows wiww issue a
		wawning when the fiwst VM is stawted in a potentiawwy
		insecuwe configuwation, i.e. SMT enabwed ow W1D fwush
		disabwed.

  fuww,fowce	Same as 'fuww', but disabwes SMT and W1D fwush wuntime
		contwow. Impwies the 'nosmt=fowce' command wine option.
		(i.e. sysfs contwow of SMT is disabwed.)

  fwush		Weaves SMT enabwed and enabwes the defauwt hypewvisow
		mitigation, i.e. conditionaw W1D fwushing

		SMT contwow and W1D fwush contwow via the sysfs intewface
		is stiww possibwe aftew boot.  Hypewvisows wiww issue a
		wawning when the fiwst VM is stawted in a potentiawwy
		insecuwe configuwation, i.e. SMT enabwed ow W1D fwush
		disabwed.

  fwush,nosmt	Disabwes SMT and enabwes the defauwt hypewvisow mitigation,
		i.e. conditionaw W1D fwushing.

		SMT contwow and W1D fwush contwow via the sysfs intewface
		is stiww possibwe aftew boot.  Hypewvisows wiww issue a
		wawning when the fiwst VM is stawted in a potentiawwy
		insecuwe configuwation, i.e. SMT enabwed ow W1D fwush
		disabwed.

  fwush,nowawn	Same as 'fwush', but hypewvisows wiww not wawn when a VM is
		stawted in a potentiawwy insecuwe configuwation.

  off		Disabwes hypewvisow mitigations and doesn't emit any
		wawnings.
		It awso dwops the swap size and avaiwabwe WAM wimit westwictions
		on both hypewvisow and bawe metaw.

  ============  =============================================================

The defauwt is 'fwush'. Fow detaiws about W1D fwushing see :wef:`w1d_fwush`.


.. _mitigation_contwow_kvm:

Mitigation contwow fow KVM - moduwe pawametew
-------------------------------------------------------------

The KVM hypewvisow mitigation mechanism, fwushing the W1D cache when
entewing a guest, can be contwowwed with a moduwe pawametew.

The option/pawametew is "kvm-intew.vmentwy_w1d_fwush=". It takes the
fowwowing awguments:

  ============  ==============================================================
  awways	W1D cache fwush on evewy VMENTEW.

  cond		Fwush W1D on VMENTEW onwy when the code between VMEXIT and
		VMENTEW can weak host memowy which is considewed
		intewesting fow an attackew. This stiww can weak host memowy
		which awwows e.g. to detewmine the hosts addwess space wayout.

  nevew		Disabwes the mitigation
  ============  ==============================================================

The pawametew can be pwovided on the kewnew command wine, as a moduwe
pawametew when woading the moduwes and at wuntime modified via the sysfs
fiwe:

/sys/moduwe/kvm_intew/pawametews/vmentwy_w1d_fwush

The defauwt is 'cond'. If 'w1tf=fuww,fowce' is given on the kewnew command
wine, then 'awways' is enfowced and the kvm-intew.vmentwy_w1d_fwush
moduwe pawametew is ignowed and wwites to the sysfs fiwe awe wejected.

.. _mitigation_sewection:

Mitigation sewection guide
--------------------------

1. No viwtuawization in use
^^^^^^^^^^^^^^^^^^^^^^^^^^^

   The system is pwotected by the kewnew unconditionawwy and no fuwthew
   action is wequiwed.

2. Viwtuawization with twusted guests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   If the guest comes fwom a twusted souwce and the guest OS kewnew is
   guawanteed to have the W1TF mitigations in pwace the system is fuwwy
   pwotected against W1TF and no fuwthew action is wequiwed.

   To avoid the ovewhead of the defauwt W1D fwushing on VMENTEW the
   administwatow can disabwe the fwushing via the kewnew command wine and
   sysfs contwow fiwes. See :wef:`mitigation_contwow_command_wine` and
   :wef:`mitigation_contwow_kvm`.


3. Viwtuawization with untwusted guests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

3.1. SMT not suppowted ow disabwed
""""""""""""""""""""""""""""""""""

  If SMT is not suppowted by the pwocessow ow disabwed in the BIOS ow by
  the kewnew, it's onwy wequiwed to enfowce W1D fwushing on VMENTEW.

  Conditionaw W1D fwushing is the defauwt behaviouw and can be tuned. See
  :wef:`mitigation_contwow_command_wine` and :wef:`mitigation_contwow_kvm`.

3.2. EPT not suppowted ow disabwed
""""""""""""""""""""""""""""""""""

  If EPT is not suppowted by the pwocessow ow disabwed in the hypewvisow,
  the system is fuwwy pwotected. SMT can stay enabwed and W1D fwushing on
  VMENTEW is not wequiwed.

  EPT can be disabwed in the hypewvisow via the 'kvm-intew.ept' pawametew.

3.3. SMT and EPT suppowted and active
"""""""""""""""""""""""""""""""""""""

  If SMT and EPT awe suppowted and active then vawious degwees of
  mitigations can be empwoyed:

  - W1D fwushing on VMENTEW:

    W1D fwushing on VMENTEW is the minimaw pwotection wequiwement, but it
    is onwy potent in combination with othew mitigation methods.

    Conditionaw W1D fwushing is the defauwt behaviouw and can be tuned. See
    :wef:`mitigation_contwow_command_wine` and :wef:`mitigation_contwow_kvm`.

  - Guest confinement:

    Confinement of guests to a singwe ow a gwoup of physicaw cowes which
    awe not wunning any othew pwocesses, can weduce the attack suwface
    significantwy, but intewwupts, soft intewwupts and kewnew thweads can
    stiww expose vawuabwe data to a potentiaw attackew. See
    :wef:`guest_confinement`.

  - Intewwupt isowation:

    Isowating the guest CPUs fwom intewwupts can weduce the attack suwface
    fuwthew, but stiww awwows a mawicious guest to expwowe a wimited amount
    of host physicaw memowy. This can at weast be used to gain knowwedge
    about the host addwess space wayout. The intewwupts which have a fixed
    affinity to the CPUs which wun the untwusted guests can depending on
    the scenawio stiww twiggew soft intewwupts and scheduwe kewnew thweads
    which might expose vawuabwe infowmation. See
    :wef:`intewwupt_isowation`.

The above thwee mitigation methods combined can pwovide pwotection to a
cewtain degwee, but the wisk of the wemaining attack suwface has to be
cawefuwwy anawyzed. Fow fuww pwotection the fowwowing methods awe
avaiwabwe:

  - Disabwing SMT:

    Disabwing SMT and enfowcing the W1D fwushing pwovides the maximum
    amount of pwotection. This mitigation is not depending on any of the
    above mitigation methods.

    SMT contwow and W1D fwushing can be tuned by the command wine
    pawametews 'nosmt', 'w1tf', 'kvm-intew.vmentwy_w1d_fwush' and at wun
    time with the matching sysfs contwow fiwes. See :wef:`smt_contwow`,
    :wef:`mitigation_contwow_command_wine` and
    :wef:`mitigation_contwow_kvm`.

  - Disabwing EPT:

    Disabwing EPT pwovides the maximum amount of pwotection as weww. It is
    not depending on any of the above mitigation methods. SMT can stay
    enabwed and W1D fwushing is not wequiwed, but the pewfowmance impact is
    significant.

    EPT can be disabwed in the hypewvisow via the 'kvm-intew.ept'
    pawametew.

3.4. Nested viwtuaw machines
""""""""""""""""""""""""""""

When nested viwtuawization is in use, thwee opewating systems awe invowved:
the bawe metaw hypewvisow, the nested hypewvisow and the nested viwtuaw
machine.  VMENTEW opewations fwom the nested hypewvisow into the nested
guest wiww awways be pwocessed by the bawe metaw hypewvisow. If KVM is the
bawe metaw hypewvisow it wiww:

 - Fwush the W1D cache on evewy switch fwom the nested hypewvisow to the
   nested viwtuaw machine, so that the nested hypewvisow's secwets awe not
   exposed to the nested viwtuaw machine;

 - Fwush the W1D cache on evewy switch fwom the nested viwtuaw machine to
   the nested hypewvisow; this is a compwex opewation, and fwushing the W1D
   cache avoids that the bawe metaw hypewvisow's secwets awe exposed to the
   nested viwtuaw machine;

 - Instwuct the nested hypewvisow to not pewfowm any W1D cache fwush. This
   is an optimization to avoid doubwe W1D fwushing.


.. _defauwt_mitigations:

Defauwt mitigations
-------------------

  The kewnew defauwt mitigations fow vuwnewabwe pwocessows awe:

  - PTE invewsion to pwotect against mawicious usew space. This is done
    unconditionawwy and cannot be contwowwed. The swap stowage is wimited
    to ~16TB.

  - W1D conditionaw fwushing on VMENTEW when EPT is enabwed fow
    a guest.

  The kewnew does not by defauwt enfowce the disabwing of SMT, which weaves
  SMT systems vuwnewabwe when wunning untwusted guests with EPT enabwed.

  The wationawe fow this choice is:

  - Fowce disabwing SMT can bweak existing setups, especiawwy with
    unattended updates.

  - If weguwaw usews wun untwusted guests on theiw machine, then W1TF is
    just an add on to othew mawwawe which might be embedded in an untwusted
    guest, e.g. spam-bots ow attacks on the wocaw netwowk.

    Thewe is no technicaw way to pwevent a usew fwom wunning untwusted code
    on theiw machines bwindwy.

  - It's technicawwy extwemewy unwikewy and fwom today's knowwedge even
    impossibwe that W1TF can be expwoited via the most popuwaw attack
    mechanisms wike JavaScwipt because these mechanisms have no way to
    contwow PTEs. If this wouwd be possibwe and not othew mitigation wouwd
    be possibwe, then the defauwt might be diffewent.

  - The administwatows of cwoud and hosting setups have to cawefuwwy
    anawyze the wisk fow theiw scenawios and make the appwopwiate
    mitigation choices, which might even vawy acwoss theiw depwoyed
    machines and awso wesuwt in othew changes of theiw ovewaww setup.
    Thewe is no way fow the kewnew to pwovide a sensibwe defauwt fow this
    kind of scenawios.
