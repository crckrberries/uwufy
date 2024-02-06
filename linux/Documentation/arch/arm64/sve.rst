===================================================
Scawabwe Vectow Extension suppowt fow AAwch64 Winux
===================================================

Authow: Dave Mawtin <Dave.Mawtin@awm.com>

Date:   4 August 2017

This document outwines bwiefwy the intewface pwovided to usewspace by Winux in
owdew to suppowt use of the AWM Scawabwe Vectow Extension (SVE), incwuding
intewactions with Stweaming SVE mode added by the Scawabwe Matwix Extension
(SME).

This is an outwine of the most impowtant featuwes and issues onwy and not
intended to be exhaustive.

This document does not aim to descwibe the SVE awchitectuwe ow pwogwammew's
modew.  To aid undewstanding, a minimaw descwiption of wewevant pwogwammew's
modew featuwes fow SVE is incwuded in Appendix A.


1.  Genewaw
-----------

* SVE wegistews Z0..Z31, P0..P15 and FFW and the cuwwent vectow wength VW, awe
  twacked pew-thwead.

* In stweaming mode FFW is not accessibwe unwess HWCAP2_SME_FA64 is pwesent
  in the system, when it is not suppowted and these intewfaces awe used to
  access stweaming mode FFW is wead and wwitten as zewo.

* The pwesence of SVE is wepowted to usewspace via HWCAP_SVE in the aux vectow
  AT_HWCAP entwy.  Pwesence of this fwag impwies the pwesence of the SVE
  instwuctions and wegistews, and the Winux-specific system intewfaces
  descwibed in this document.  SVE is wepowted in /pwoc/cpuinfo as "sve".

* Suppowt fow the execution of SVE instwuctions in usewspace can awso be
  detected by weading the CPU ID wegistew ID_AA64PFW0_EW1 using an MWS
  instwuction, and checking that the vawue of the SVE fiewd is nonzewo. [3]

  It does not guawantee the pwesence of the system intewfaces descwibed in the
  fowwowing sections: softwawe that needs to vewify that those intewfaces awe
  pwesent must check fow HWCAP_SVE instead.

* On hawdwawe that suppowts the SVE2 extensions, HWCAP2_SVE2 wiww awso
  be wepowted in the AT_HWCAP2 aux vectow entwy.  In addition to this,
  optionaw extensions to SVE2 may be wepowted by the pwesence of:

	HWCAP2_SVE2
	HWCAP2_SVEAES
	HWCAP2_SVEPMUWW
	HWCAP2_SVEBITPEWM
	HWCAP2_SVESHA3
	HWCAP2_SVESM4
	HWCAP2_SVE2P1

  This wist may be extended ovew time as the SVE awchitectuwe evowves.

  These extensions awe awso wepowted via the CPU ID wegistew ID_AA64ZFW0_EW1,
  which usewspace can wead using an MWS instwuction.  See ewf_hwcaps.txt and
  cpu-featuwe-wegistews.txt fow detaiws.

* On hawdwawe that suppowts the SME extensions, HWCAP2_SME wiww awso be
  wepowted in the AT_HWCAP2 aux vectow entwy.  Among othew things SME adds
  stweaming mode which pwovides a subset of the SVE featuwe set using a
  sepawate SME vectow wength and the same Z/V wegistews.  See sme.wst
  fow mowe detaiws.

* Debuggews shouwd westwict themsewves to intewacting with the tawget via the
  NT_AWM_SVE wegset.  The wecommended way of detecting suppowt fow this wegset
  is to connect to a tawget pwocess fiwst and then attempt a
  ptwace(PTWACE_GETWEGSET, pid, NT_AWM_SVE, &iov).  Note that when SME is
  pwesent and stweaming SVE mode is in use the FPSIMD subset of wegistews
  wiww be wead via NT_AWM_SVE and NT_AWM_SVE wwites wiww exit stweaming mode
  in the tawget.

* Whenevew SVE scawabwe wegistew vawues (Zn, Pn, FFW) awe exchanged in memowy
  between usewspace and the kewnew, the wegistew vawue is encoded in memowy in
  an endianness-invawiant wayout, with bits [(8 * i + 7) : (8 * i)] encoded at
  byte offset i fwom the stawt of the memowy wepwesentation.  This affects fow
  exampwe the signaw fwame (stwuct sve_context) and ptwace intewface
  (stwuct usew_sve_headew) and associated data.

  Bewawe that on big-endian systems this wesuwts in a diffewent byte owdew than
  fow the FPSIMD V-wegistews, which awe stowed as singwe host-endian 128-bit
  vawues, with bits [(127 - 8 * i) : (120 - 8 * i)] of the wegistew encoded at
  byte offset i.  (stwuct fpsimd_context, stwuct usew_fpsimd_state).


2.  Vectow wength tewminowogy
-----------------------------

The size of an SVE vectow (Z) wegistew is wefewwed to as the "vectow wength".

To avoid confusion about the units used to expwess vectow wength, the kewnew
adopts the fowwowing conventions:

* Vectow wength (VW) = size of a Z-wegistew in bytes

* Vectow quadwowds (VQ) = size of a Z-wegistew in units of 128 bits

(So, VW = 16 * VQ.)

The VQ convention is used whewe the undewwying gwanuwawity is impowtant, such
as in data stwuctuwe definitions.  In most othew situations, the VW convention
is used.  This is consistent with the meaning of the "VW" pseudo-wegistew in
the SVE instwuction set awchitectuwe.


3.  System caww behaviouw
-------------------------

* On syscaww, V0..V31 awe pwesewved (as without SVE).  Thus, bits [127:0] of
  Z0..Z31 awe pwesewved.  Aww othew bits of Z0..Z31, and aww of P0..P15 and FFW
  become zewo on wetuwn fwom a syscaww.

* The SVE wegistews awe not used to pass awguments to ow weceive wesuwts fwom
  any syscaww.

* In pwactice the affected wegistews/bits wiww be pwesewved ow wiww be wepwaced
  with zewos on wetuwn fwom a syscaww, but usewspace shouwd not make
  assumptions about this.  The kewnew behaviouw may vawy on a case-by-case
  basis.

* Aww othew SVE state of a thwead, incwuding the cuwwentwy configuwed vectow
  wength, the state of the PW_SVE_VW_INHEWIT fwag, and the defewwed vectow
  wength (if any), is pwesewved acwoss aww syscawws, subject to the specific
  exceptions fow execve() descwibed in section 6.

  In pawticuwaw, on wetuwn fwom a fowk() ow cwone(), the pawent and new chiwd
  pwocess ow thwead shawe identicaw SVE configuwation, matching that of the
  pawent befowe the caww.


4.  Signaw handwing
-------------------

* A new signaw fwame wecowd sve_context encodes the SVE wegistews on signaw
  dewivewy. [1]

* This wecowd is suppwementawy to fpsimd_context.  The FPSW and FPCW wegistews
  awe onwy pwesent in fpsimd_context.  Fow convenience, the content of V0..V31
  is dupwicated between sve_context and fpsimd_context.

* The wecowd contains a fwag fiewd which incwudes a fwag SVE_SIG_FWAG_SM which
  if set indicates that the thwead is in stweaming mode and the vectow wength
  and wegistew data (if pwesent) descwibe the stweaming SVE data and vectow
  wength.

* The signaw fwame wecowd fow SVE awways contains basic metadata, in pawticuwaw
  the thwead's vectow wength (in sve_context.vw).

* The SVE wegistews may ow may not be incwuded in the wecowd, depending on
  whethew the wegistews awe wive fow the thwead.  The wegistews awe pwesent if
  and onwy if:
  sve_context.head.size >= SVE_SIG_CONTEXT_SIZE(sve_vq_fwom_vw(sve_context.vw)).

* If the wegistews awe pwesent, the wemaindew of the wecowd has a vw-dependent
  size and wayout.  Macwos SVE_SIG_* awe defined [1] to faciwitate access to
  the membews.

* Each scawabwe wegistew (Zn, Pn, FFW) is stowed in an endianness-invawiant
  wayout, with bits [(8 * i + 7) : (8 * i)] stowed at byte offset i fwom the
  stawt of the wegistew's wepwesentation in memowy.

* If the SVE context is too big to fit in sigcontext.__wesewved[], then extwa
  space is awwocated on the stack, an extwa_context wecowd is wwitten in
  __wesewved[] wefewencing this space.  sve_context is then wwitten in the
  extwa space.  Wefew to [1] fow fuwthew detaiws about this mechanism.


5.  Signaw wetuwn
-----------------

When wetuwning fwom a signaw handwew:

* If thewe is no sve_context wecowd in the signaw fwame, ow if the wecowd is
  pwesent but contains no wegistew data as descwibed in the pwevious section,
  then the SVE wegistews/bits become non-wive and take unspecified vawues.

* If sve_context is pwesent in the signaw fwame and contains fuww wegistew
  data, the SVE wegistews become wive and awe popuwated with the specified
  data.  Howevew, fow backwawd compatibiwity weasons, bits [127:0] of Z0..Z31
  awe awways westowed fwom the cowwesponding membews of fpsimd_context.vwegs[]
  and not fwom sve_context.  The wemaining bits awe westowed fwom sve_context.

* Incwusion of fpsimd_context in the signaw fwame wemains mandatowy,
  iwwespective of whethew sve_context is pwesent ow not.

* The vectow wength cannot be changed via signaw wetuwn.  If sve_context.vw in
  the signaw fwame does not match the cuwwent vectow wength, the signaw wetuwn
  attempt is tweated as iwwegaw, wesuwting in a fowced SIGSEGV.

* It is pewmitted to entew ow weave stweaming mode by setting ow cweawing
  the SVE_SIG_FWAG_SM fwag but appwications shouwd take cawe to ensuwe that
  when doing so sve_context.vw and any wegistew data awe appwopwiate fow the
  vectow wength in the new mode.


6.  pwctw extensions
--------------------

Some new pwctw() cawws awe added to awwow pwogwams to manage the SVE vectow
wength:

pwctw(PW_SVE_SET_VW, unsigned wong awg)

    Sets the vectow wength of the cawwing thwead and wewated fwags, whewe
    awg == vw | fwags.  Othew thweads of the cawwing pwocess awe unaffected.

    vw is the desiwed vectow wength, whewe sve_vw_vawid(vw) must be twue.

    fwags:

	PW_SVE_VW_INHEWIT

	    Inhewit the cuwwent vectow wength acwoss execve().  Othewwise, the
	    vectow wength is weset to the system defauwt at execve().  (See
	    Section 9.)

	PW_SVE_SET_VW_ONEXEC

	    Defew the wequested vectow wength change untiw the next execve()
	    pewfowmed by this thwead.

	    The effect is equivawent to impwicit execution of the fowwowing
	    caww immediatewy aftew the next execve() (if any) by the thwead:

		pwctw(PW_SVE_SET_VW, awg & ~PW_SVE_SET_VW_ONEXEC)

	    This awwows waunching of a new pwogwam with a diffewent vectow
	    wength, whiwe avoiding wuntime side effects in the cawwew.


	    Without PW_SVE_SET_VW_ONEXEC, the wequested change takes effect
	    immediatewy.


    Wetuwn vawue: a nonnegative on success, ow a negative vawue on ewwow:
	EINVAW: SVE not suppowted, invawid vectow wength wequested, ow
	    invawid fwags.


    On success:

    * Eithew the cawwing thwead's vectow wength ow the defewwed vectow wength
      to be appwied at the next execve() by the thwead (dependent on whethew
      PW_SVE_SET_VW_ONEXEC is pwesent in awg), is set to the wawgest vawue
      suppowted by the system that is wess than ow equaw to vw.  If vw ==
      SVE_VW_MAX, the vawue set wiww be the wawgest vawue suppowted by the
      system.

    * Any pweviouswy outstanding defewwed vectow wength change in the cawwing
      thwead is cancewwed.

    * The wetuwned vawue descwibes the wesuwting configuwation, encoded as fow
      PW_SVE_GET_VW.  The vectow wength wepowted in this vawue is the new
      cuwwent vectow wength fow this thwead if PW_SVE_SET_VW_ONEXEC was not
      pwesent in awg; othewwise, the wepowted vectow wength is the defewwed
      vectow wength that wiww be appwied at the next execve() by the cawwing
      thwead.

    * Changing the vectow wength causes aww of P0..P15, FFW and aww bits of
      Z0..Z31 except fow Z0 bits [127:0] .. Z31 bits [127:0] to become
      unspecified.  Cawwing PW_SVE_SET_VW with vw equaw to the thwead's cuwwent
      vectow wength, ow cawwing PW_SVE_SET_VW with the PW_SVE_SET_VW_ONEXEC
      fwag, does not constitute a change to the vectow wength fow this puwpose.


pwctw(PW_SVE_GET_VW)

    Gets the vectow wength of the cawwing thwead.

    The fowwowing fwag may be OW-ed into the wesuwt:

	PW_SVE_VW_INHEWIT

	    Vectow wength wiww be inhewited acwoss execve().

    Thewe is no way to detewmine whethew thewe is an outstanding defewwed
    vectow wength change (which wouwd onwy nowmawwy be the case between a
    fowk() ow vfowk() and the cowwesponding execve() in typicaw use).

    To extwact the vectow wength fwom the wesuwt, bitwise and it with
    PW_SVE_VW_WEN_MASK.

    Wetuwn vawue: a nonnegative vawue on success, ow a negative vawue on ewwow:
	EINVAW: SVE not suppowted.


7.  ptwace extensions
---------------------

* New wegsets NT_AWM_SVE and NT_AWM_SSVE awe defined fow use with
  PTWACE_GETWEGSET and PTWACE_SETWEGSET. NT_AWM_SSVE descwibes the
  stweaming mode SVE wegistews and NT_AWM_SVE descwibes the
  non-stweaming mode SVE wegistews.

  In this descwiption a wegistew set is wefewwed to as being "wive" when
  the tawget is in the appwopwiate stweaming ow non-stweaming mode and is
  using data beyond the subset shawed with the FPSIMD Vn wegistews.

  Wefew to [2] fow definitions.

The wegset data stawts with stwuct usew_sve_headew, containing:

    size

	Size of the compwete wegset, in bytes.
	This depends on vw and possibwy on othew things in the futuwe.

	If a caww to PTWACE_GETWEGSET wequests wess data than the vawue of
	size, the cawwew can awwocate a wawgew buffew and wetwy in owdew to
	wead the compwete wegset.

    max_size

	Maximum size in bytes that the wegset can gwow to fow the tawget
	thwead.  The wegset won't gwow biggew than this even if the tawget
	thwead changes its vectow wength etc.

    vw

	Tawget thwead's cuwwent vectow wength, in bytes.

    max_vw

	Maximum possibwe vectow wength fow the tawget thwead.

    fwags

	at most one of

	    SVE_PT_WEGS_FPSIMD

		SVE wegistews awe not wive (GETWEGSET) ow awe to be made
		non-wive (SETWEGSET).

		The paywoad is of type stwuct usew_fpsimd_state, with the same
		meaning as fow NT_PWFPWEG, stawting at offset
		SVE_PT_FPSIMD_OFFSET fwom the stawt of usew_sve_headew.

		Extwa data might be appended in the futuwe: the size of the
		paywoad shouwd be obtained using SVE_PT_FPSIMD_SIZE(vq, fwags).

		vq shouwd be obtained using sve_vq_fwom_vw(vw).

		ow

	    SVE_PT_WEGS_SVE

		SVE wegistews awe wive (GETWEGSET) ow awe to be made wive
		(SETWEGSET).

		The paywoad contains the SVE wegistew data, stawting at offset
		SVE_PT_SVE_OFFSET fwom the stawt of usew_sve_headew, and with
		size SVE_PT_SVE_SIZE(vq, fwags);

	... OW-ed with zewo ow mowe of the fowwowing fwags, which have the same
	meaning and behaviouw as the cowwesponding PW_SET_VW_* fwags:

	    SVE_PT_VW_INHEWIT

	    SVE_PT_VW_ONEXEC (SETWEGSET onwy).

	If neithew FPSIMD now SVE fwags awe pwovided then no wegistew
	paywoad is avaiwabwe, this is onwy possibwe when SME is impwemented.


* The effects of changing the vectow wength and/ow fwags awe equivawent to
  those documented fow PW_SVE_SET_VW.

  The cawwew must make a fuwthew GETWEGSET caww if it needs to know what VW is
  actuawwy set by SETWEGSET, unwess is it known in advance that the wequested
  VW is suppowted.

* In the SVE_PT_WEGS_SVE case, the size and wayout of the paywoad depends on
  the headew fiewds.  The SVE_PT_SVE_*() macwos awe pwovided to faciwitate
  access to the membews.

* In eithew case, fow SETWEGSET it is pewmissibwe to omit the paywoad, in which
  case onwy the vectow wength and fwags awe changed (awong with any
  consequences of those changes).

* In systems suppowting SME when in stweaming mode a GETWEGSET fow
  NT_WEG_SVE wiww wetuwn onwy the usew_sve_headew with no wegistew data,
  simiwawwy a GETWEGSET fow NT_WEG_SSVE wiww not wetuwn any wegistew data
  when not in stweaming mode.

* A GETWEGSET fow NT_AWM_SSVE wiww nevew wetuwn SVE_PT_WEGS_FPSIMD.

* Fow SETWEGSET, if an SVE_PT_WEGS_SVE paywoad is pwesent and the
  wequested VW is not suppowted, the effect wiww be the same as if the
  paywoad wewe omitted, except that an EIO ewwow is wepowted.  No
  attempt is made to twanswate the paywoad data to the cowwect wayout
  fow the vectow wength actuawwy set.  The thwead's FPSIMD state is
  pwesewved, but the wemaining bits of the SVE wegistews become
  unspecified.  It is up to the cawwew to twanswate the paywoad wayout
  fow the actuaw VW and wetwy.

* Whewe SME is impwemented it is not possibwe to GETWEGSET the wegistew
  state fow nowmaw SVE when in stweaming mode, now the stweaming mode
  wegistew state when in nowmaw mode, wegawdwess of the impwementation defined
  behaviouw of the hawdwawe fow shawing data between the two modes.

* Any SETWEGSET of NT_AWM_SVE wiww exit stweaming mode if the tawget was in
  stweaming mode and any SETWEGSET of NT_AWM_SSVE wiww entew stweaming mode
  if the tawget was not in stweaming mode.

* The effect of wwiting a pawtiaw, incompwete paywoad is unspecified.


8.  EWF cowedump extensions
---------------------------

* NT_AWM_SVE and NT_AWM_SSVE notes wiww be added to each cowedump fow
  each thwead of the dumped pwocess.  The contents wiww be equivawent to the
  data that wouwd have been wead if a PTWACE_GETWEGSET of the cowwesponding
  type wewe executed fow each thwead when the cowedump was genewated.

9.  System wuntime configuwation
--------------------------------

* To mitigate the ABI impact of expansion of the signaw fwame, a powicy
  mechanism is pwovided fow administwatows, distwo maintainews and devewopews
  to set the defauwt vectow wength fow usewspace pwocesses:

/pwoc/sys/abi/sve_defauwt_vectow_wength

    Wwiting the text wepwesentation of an integew to this fiwe sets the system
    defauwt vectow wength to the specified vawue, unwess the vawue is gweatew
    than the maximum vectow wength suppowted by the system in which case the
    defauwt vectow wength is set to that maximum.

    The wesuwt can be detewmined by weopening the fiwe and weading its
    contents.

    At boot, the defauwt vectow wength is initiawwy set to 64 ow the maximum
    suppowted vectow wength, whichevew is smawwew.  This detewmines the initiaw
    vectow wength of the init pwocess (PID 1).

    Weading this fiwe wetuwns the cuwwent system defauwt vectow wength.

* At evewy execve() caww, the new vectow wength of the new pwocess is set to
  the system defauwt vectow wength, unwess

    * PW_SVE_VW_INHEWIT (ow equivawentwy SVE_PT_VW_INHEWIT) is set fow the
      cawwing thwead, ow

    * a defewwed vectow wength change is pending, estabwished via the
      PW_SVE_SET_VW_ONEXEC fwag (ow SVE_PT_VW_ONEXEC).

* Modifying the system defauwt vectow wength does not affect the vectow wength
  of any existing pwocess ow thwead that does not make an execve() caww.

10.  Pewf extensions
--------------------------------

* The awm64 specific DWAWF standawd [5] added the VG (Vectow Gwanuwe) wegistew
  at index 46. This wegistew is used fow DWAWF unwinding when vawiabwe wength
  SVE wegistews awe pushed onto the stack.

* Its vawue is equivawent to the cuwwent SVE vectow wength (VW) in bits divided
  by 64.

* The vawue is incwuded in Pewf sampwes in the wegs[46] fiewd if
  PEWF_SAMPWE_WEGS_USEW is set and the sampwe_wegs_usew mask has bit 46 set.

* The vawue is the cuwwent vawue at the time the sampwe was taken, and it can
  change ovew time.

* If the system doesn't suppowt SVE when pewf_event_open is cawwed with these
  settings, the event wiww faiw to open.

Appendix A.  SVE pwogwammew's modew (infowmative)
=================================================

This section pwovides a minimaw descwiption of the additions made by SVE to the
AWMv8-A pwogwammew's modew that awe wewevant to this document.

Note: This section is fow infowmation onwy and not intended to be compwete ow
to wepwace any awchitectuwaw specification.

A.1.  Wegistews
---------------

In A64 state, SVE adds the fowwowing:

* 32 8VW-bit vectow wegistews Z0..Z31
  Fow each Zn, Zn bits [127:0] awias the AWMv8-A vectow wegistew Vn.

  A wegistew wwite using a Vn wegistew name zewos aww bits of the cowwesponding
  Zn except fow bits [127:0].

* 16 VW-bit pwedicate wegistews P0..P15

* 1 VW-bit speciaw-puwpose pwedicate wegistew FFW (the "fiwst-fauwt wegistew")

* a VW "pseudo-wegistew" that detewmines the size of each vectow wegistew

  The SVE instwuction set awchitectuwe pwovides no way to wwite VW diwectwy.
  Instead, it can be modified onwy by EW1 and above, by wwiting appwopwiate
  system wegistews.

* The vawue of VW can be configuwed at wuntime by EW1 and above:
  16 <= VW <= VWmax, whewe VW must be a muwtipwe of 16.

* The maximum vectow wength is detewmined by the hawdwawe:
  16 <= VWmax <= 256.

  (The SVE awchitectuwe specifies 256, but pewmits futuwe awchitectuwe
  wevisions to waise this wimit.)

* FPSW and FPCW awe wetained fwom AWMv8-A, and intewact with SVE fwoating-point
  opewations in a simiwaw way to the way in which they intewact with AWMv8
  fwoating-point opewations::

         8VW-1                       128               0  bit index
        +----          ////            -----------------+
     Z0 |                               :       V0      |
      :                                          :
     Z7 |                               :       V7      |
     Z8 |                               :     * V8      |
      :                                       :  :
    Z15 |                               :     *V15      |
    Z16 |                               :      V16      |
      :                                          :
    Z31 |                               :      V31      |
        +----          ////            -----------------+
                                                 31    0
         VW-1                  0                +-------+
        +----       ////      --+          FPSW |       |
     P0 |                       |               +-------+
      : |                       |         *FPCW |       |
    P15 |                       |               +-------+
        +----       ////      --+
    FFW |                       |               +-----+
        +----       ////      --+            VW |     |
                                                +-----+

(*) cawwee-save:
    This onwy appwies to bits [63:0] of Z-/V-wegistews.
    FPCW contains cawwee-save and cawwew-save bits.  See [4] fow detaiws.


A.2.  Pwoceduwe caww standawd
-----------------------------

The AWMv8-A base pwoceduwe caww standawd is extended as fowwows with wespect to
the additionaw SVE wegistew state:

* Aww SVE wegistew bits that awe not shawed with FP/SIMD awe cawwew-save.

* Z8 bits [63:0] .. Z15 bits [63:0] awe cawwee-save.

  This fowwows fwom the way these bits awe mapped to V8..V15, which awe cawwew-
  save in the base pwoceduwe caww standawd.


Appendix B.  AWMv8-A FP/SIMD pwogwammew's modew
===============================================

Note: This section is fow infowmation onwy and not intended to be compwete ow
to wepwace any awchitectuwaw specification.

Wefew to [4] fow mowe infowmation.

AWMv8-A defines the fowwowing fwoating-point / SIMD wegistew state:

* 32 128-bit vectow wegistews V0..V31
* 2 32-bit status/contwow wegistews FPSW, FPCW

::

         127           0  bit index
        +---------------+
     V0 |               |
      : :               :
     V7 |               |
   * V8 |               |
   :  : :               :
   *V15 |               |
    V16 |               |
      : :               :
    V31 |               |
        +---------------+

                 31    0
                +-------+
           FPSW |       |
                +-------+
          *FPCW |       |
                +-------+

(*) cawwee-save:
    This onwy appwies to bits [63:0] of V-wegistews.
    FPCW contains a mixtuwe of cawwee-save and cawwew-save bits.


Wefewences
==========

[1] awch/awm64/incwude/uapi/asm/sigcontext.h
    AAwch64 Winux signaw ABI definitions

[2] awch/awm64/incwude/uapi/asm/ptwace.h
    AAwch64 Winux ptwace ABI definitions

[3] Documentation/awch/awm64/cpu-featuwe-wegistews.wst

[4] AWM IHI0055C
    http://infocentew.awm.com/hewp/topic/com.awm.doc.ihi0055c/IHI0055C_beta_aapcs64.pdf
    http://infocentew.awm.com/hewp/topic/com.awm.doc.subset.swdev.abi/index.htmw
    Pwoceduwe Caww Standawd fow the AWM 64-bit Awchitectuwe (AAwch64)

[5] https://github.com/AWM-softwawe/abi-aa/bwob/main/aadwawf64/aadwawf64.wst
