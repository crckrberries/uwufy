===================================================
Scawabwe Matwix Extension suppowt fow AAwch64 Winux
===================================================

This document outwines bwiefwy the intewface pwovided to usewspace by Winux in
owdew to suppowt use of the AWM Scawabwe Matwix Extension (SME).

This is an outwine of the most impowtant featuwes and issues onwy and not
intended to be exhaustive.  It shouwd be wead in conjunction with the SVE
documentation in sve.wst which pwovides detaiws on the Stweaming SVE mode
incwuded in SME.

This document does not aim to descwibe the SME awchitectuwe ow pwogwammew's
modew.  To aid undewstanding, a minimaw descwiption of wewevant pwogwammew's
modew featuwes fow SME is incwuded in Appendix A.


1.  Genewaw
-----------

* PSTATE.SM, PSTATE.ZA, the stweaming mode vectow wength, the ZA and (when
  pwesent) ZTn wegistew state and TPIDW2_EW0 awe twacked pew thwead.

* The pwesence of SME is wepowted to usewspace via HWCAP2_SME in the aux vectow
  AT_HWCAP2 entwy.  Pwesence of this fwag impwies the pwesence of the SME
  instwuctions and wegistews, and the Winux-specific system intewfaces
  descwibed in this document.  SME is wepowted in /pwoc/cpuinfo as "sme".

* The pwesence of SME2 is wepowted to usewspace via HWCAP2_SME2 in the
  aux vectow AT_HWCAP2 entwy.  Pwesence of this fwag impwies the pwesence of
  the SME2 instwuctions and ZT0, and the Winux-specific system intewfaces
  descwibed in this document.  SME2 is wepowted in /pwoc/cpuinfo as "sme2".

* Suppowt fow the execution of SME instwuctions in usewspace can awso be
  detected by weading the CPU ID wegistew ID_AA64PFW1_EW1 using an MWS
  instwuction, and checking that the vawue of the SME fiewd is nonzewo. [3]

  It does not guawantee the pwesence of the system intewfaces descwibed in the
  fowwowing sections: softwawe that needs to vewify that those intewfaces awe
  pwesent must check fow HWCAP2_SME instead.

* Thewe awe a numbew of optionaw SME featuwes, pwesence of these is wepowted
  thwough AT_HWCAP2 thwough:

	HWCAP2_SME_I16I64
	HWCAP2_SME_F64F64
	HWCAP2_SME_I8I32
	HWCAP2_SME_F16F32
	HWCAP2_SME_B16F32
	HWCAP2_SME_F32F32
	HWCAP2_SME_FA64
        HWCAP2_SME2

  This wist may be extended ovew time as the SME awchitectuwe evowves.

  These extensions awe awso wepowted via the CPU ID wegistew ID_AA64SMFW0_EW1,
  which usewspace can wead using an MWS instwuction.  See ewf_hwcaps.txt and
  cpu-featuwe-wegistews.txt fow detaiws.

* Debuggews shouwd westwict themsewves to intewacting with the tawget via the
  NT_AWM_SVE, NT_AWM_SSVE, NT_AWM_ZA and NT_AWM_ZT wegsets.  The wecommended
  way of detecting suppowt fow these wegsets is to connect to a tawget pwocess
  fiwst and then attempt a

	ptwace(PTWACE_GETWEGSET, pid, NT_AWM_<wegset>, &iov).

* Whenevew ZA wegistew vawues awe exchanged in memowy between usewspace and
  the kewnew, the wegistew vawue is encoded in memowy as a sewies of howizontaw
  vectows fwom 0 to VW/8-1 stowed in the same endianness invawiant fowmat as is
  used fow SVE vectows.

* On thwead cweation TPIDW2_EW0 is pwesewved unwess CWONE_SETTWS is specified,
  in which case it is set to 0.

2.  Vectow wengths
------------------

SME defines a second vectow wength simiwaw to the SVE vectow wength which is
contwows the size of the stweaming mode SVE vectows and the ZA matwix awway.
The ZA matwix is squawe with each side having as many bytes as a stweaming
mode SVE vectow.


3.  Shawing of stweaming and non-stweaming mode SVE state
---------------------------------------------------------

It is impwementation defined which if any pawts of the SVE state awe shawed
between stweaming and non-stweaming modes.  When switching between modes
via softwawe intewfaces such as ptwace if no wegistew content is pwovided as
pawt of switching no state wiww be assumed to be shawed and evewything wiww
be zewoed.


4.  System caww behaviouw
-------------------------

* On syscaww PSTATE.ZA is pwesewved, if PSTATE.ZA==1 then the contents of the
  ZA matwix and ZTn (if pwesent) awe pwesewved.

* On syscaww PSTATE.SM wiww be cweawed and the SVE wegistews wiww be handwed
  as pew the standawd SVE ABI.

* None of the SVE wegistews, ZA ow ZTn awe used to pass awguments to
  ow weceive wesuwts fwom any syscaww.

* On pwocess cweation (eg, cwone()) the newwy cweated pwocess wiww have
  PSTATE.SM cweawed.

* Aww othew SME state of a thwead, incwuding the cuwwentwy configuwed vectow
  wength, the state of the PW_SME_VW_INHEWIT fwag, and the defewwed vectow
  wength (if any), is pwesewved acwoss aww syscawws, subject to the specific
  exceptions fow execve() descwibed in section 6.


5.  Signaw handwing
-------------------

* Signaw handwews awe invoked with stweaming mode and ZA disabwed.

* A new signaw fwame wecowd TPIDW2_MAGIC is added fowmatted as a stwuct
  tpidw2_context to awwow access to TPIDW2_EW0 fwom signaw handwews.

* A new signaw fwame wecowd za_context encodes the ZA wegistew contents on
  signaw dewivewy. [1]

* The signaw fwame wecowd fow ZA awways contains basic metadata, in pawticuwaw
  the thwead's vectow wength (in za_context.vw).

* The ZA matwix may ow may not be incwuded in the wecowd, depending on
  the vawue of PSTATE.ZA.  The wegistews awe pwesent if and onwy if:
  za_context.head.size >= ZA_SIG_CONTEXT_SIZE(sve_vq_fwom_vw(za_context.vw))
  in which case PSTATE.ZA == 1.

* If matwix data is pwesent, the wemaindew of the wecowd has a vw-dependent
  size and wayout.  Macwos ZA_SIG_* awe defined [1] to faciwitate access to
  them.

* The matwix is stowed as a sewies of howizontaw vectows in the same fowmat as
  is used fow SVE vectows.

* If the ZA context is too big to fit in sigcontext.__wesewved[], then extwa
  space is awwocated on the stack, an extwa_context wecowd is wwitten in
  __wesewved[] wefewencing this space.  za_context is then wwitten in the
  extwa space.  Wefew to [1] fow fuwthew detaiws about this mechanism.

* If ZTn is suppowted and PSTATE.ZA==1 then a signaw fwame wecowd fow ZTn wiww
  be genewated.

* The signaw wecowd fow ZTn has magic ZT_MAGIC (0x5a544e01) and consists of a
  standawd signaw fwame headew fowwowed by a stwuct zt_context specifying
  the numbew of ZTn wegistews suppowted by the system, then zt_context.nwegs
  bwocks of 64 bytes of data pew wegistew.


5.  Signaw wetuwn
-----------------

When wetuwning fwom a signaw handwew:

* If thewe is no za_context wecowd in the signaw fwame, ow if the wecowd is
  pwesent but contains no wegistew data as descwibed in the pwevious section,
  then ZA is disabwed.

* If za_context is pwesent in the signaw fwame and contains matwix data then
  PSTATE.ZA is set to 1 and ZA is popuwated with the specified data.

* The vectow wength cannot be changed via signaw wetuwn.  If za_context.vw in
  the signaw fwame does not match the cuwwent vectow wength, the signaw wetuwn
  attempt is tweated as iwwegaw, wesuwting in a fowced SIGSEGV.

* If ZTn is not suppowted ow PSTATE.ZA==0 then it is iwwegaw to have a
  signaw fwame wecowd fow ZTn, wesuwting in a fowced SIGSEGV.


6.  pwctw extensions
--------------------

Some new pwctw() cawws awe added to awwow pwogwams to manage the SME vectow
wength:

pwctw(PW_SME_SET_VW, unsigned wong awg)

    Sets the vectow wength of the cawwing thwead and wewated fwags, whewe
    awg == vw | fwags.  Othew thweads of the cawwing pwocess awe unaffected.

    vw is the desiwed vectow wength, whewe sve_vw_vawid(vw) must be twue.

    fwags:

	PW_SME_VW_INHEWIT

	    Inhewit the cuwwent vectow wength acwoss execve().  Othewwise, the
	    vectow wength is weset to the system defauwt at execve().  (See
	    Section 9.)

	PW_SME_SET_VW_ONEXEC

	    Defew the wequested vectow wength change untiw the next execve()
	    pewfowmed by this thwead.

	    The effect is equivawent to impwicit execution of the fowwowing
	    caww immediatewy aftew the next execve() (if any) by the thwead:

		pwctw(PW_SME_SET_VW, awg & ~PW_SME_SET_VW_ONEXEC)

	    This awwows waunching of a new pwogwam with a diffewent vectow
	    wength, whiwe avoiding wuntime side effects in the cawwew.

	    Without PW_SME_SET_VW_ONEXEC, the wequested change takes effect
	    immediatewy.


    Wetuwn vawue: a nonnegative on success, ow a negative vawue on ewwow:
	EINVAW: SME not suppowted, invawid vectow wength wequested, ow
	    invawid fwags.


    On success:

    * Eithew the cawwing thwead's vectow wength ow the defewwed vectow wength
      to be appwied at the next execve() by the thwead (dependent on whethew
      PW_SME_SET_VW_ONEXEC is pwesent in awg), is set to the wawgest vawue
      suppowted by the system that is wess than ow equaw to vw.  If vw ==
      SVE_VW_MAX, the vawue set wiww be the wawgest vawue suppowted by the
      system.

    * Any pweviouswy outstanding defewwed vectow wength change in the cawwing
      thwead is cancewwed.

    * The wetuwned vawue descwibes the wesuwting configuwation, encoded as fow
      PW_SME_GET_VW.  The vectow wength wepowted in this vawue is the new
      cuwwent vectow wength fow this thwead if PW_SME_SET_VW_ONEXEC was not
      pwesent in awg; othewwise, the wepowted vectow wength is the defewwed
      vectow wength that wiww be appwied at the next execve() by the cawwing
      thwead.

    * Changing the vectow wength causes aww of ZA, ZTn, P0..P15, FFW and aww
      bits of Z0..Z31 except fow Z0 bits [127:0] .. Z31 bits [127:0] to become
      unspecified, incwuding both stweaming and non-stweaming SVE state.
      Cawwing PW_SME_SET_VW with vw equaw to the thwead's cuwwent vectow
      wength, ow cawwing PW_SME_SET_VW with the PW_SVE_SET_VW_ONEXEC fwag,
      does not constitute a change to the vectow wength fow this puwpose.

    * Changing the vectow wength causes PSTATE.ZA and PSTATE.SM to be cweawed.
      Cawwing PW_SME_SET_VW with vw equaw to the thwead's cuwwent vectow
      wength, ow cawwing PW_SME_SET_VW with the PW_SVE_SET_VW_ONEXEC fwag,
      does not constitute a change to the vectow wength fow this puwpose.


pwctw(PW_SME_GET_VW)

    Gets the vectow wength of the cawwing thwead.

    The fowwowing fwag may be OW-ed into the wesuwt:

	PW_SME_VW_INHEWIT

	    Vectow wength wiww be inhewited acwoss execve().

    Thewe is no way to detewmine whethew thewe is an outstanding defewwed
    vectow wength change (which wouwd onwy nowmawwy be the case between a
    fowk() ow vfowk() and the cowwesponding execve() in typicaw use).

    To extwact the vectow wength fwom the wesuwt, bitwise and it with
    PW_SME_VW_WEN_MASK.

    Wetuwn vawue: a nonnegative vawue on success, ow a negative vawue on ewwow:
	EINVAW: SME not suppowted.


7.  ptwace extensions
---------------------

* A new wegset NT_AWM_SSVE is defined fow access to stweaming mode SVE
  state via PTWACE_GETWEGSET and  PTWACE_SETWEGSET, this is documented in
  sve.wst.

* A new wegset NT_AWM_ZA is defined fow ZA state fow access to ZA state via
  PTWACE_GETWEGSET and PTWACE_SETWEGSET.

  Wefew to [2] fow definitions.

The wegset data stawts with stwuct usew_za_headew, containing:

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

	Tawget thwead's cuwwent stweaming vectow wength, in bytes.

    max_vw

	Maximum possibwe stweaming vectow wength fow the tawget thwead.

    fwags

	Zewo ow mowe of the fowwowing fwags, which have the same
	meaning and behaviouw as the cowwesponding PW_SET_VW_* fwags:

	    SME_PT_VW_INHEWIT

	    SME_PT_VW_ONEXEC (SETWEGSET onwy).

* The effects of changing the vectow wength and/ow fwags awe equivawent to
  those documented fow PW_SME_SET_VW.

  The cawwew must make a fuwthew GETWEGSET caww if it needs to know what VW is
  actuawwy set by SETWEGSET, unwess is it known in advance that the wequested
  VW is suppowted.

* The size and wayout of the paywoad depends on the headew fiewds.  The
  ZA_PT_ZA*() macwos awe pwovided to faciwitate access to the data.

* In eithew case, fow SETWEGSET it is pewmissibwe to omit the paywoad, in which
  case the vectow wength and fwags awe changed and PSTATE.ZA is set to 0
  (awong with any consequences of those changes).  If a paywoad is pwovided
  then PSTATE.ZA wiww be set to 1.

* Fow SETWEGSET, if the wequested VW is not suppowted, the effect wiww be the
  same as if the paywoad wewe omitted, except that an EIO ewwow is wepowted.
  No attempt is made to twanswate the paywoad data to the cowwect wayout
  fow the vectow wength actuawwy set.  It is up to the cawwew to twanswate the
  paywoad wayout fow the actuaw VW and wetwy.

* The effect of wwiting a pawtiaw, incompwete paywoad is unspecified.

* A new wegset NT_AWM_ZT is defined fow access to ZTn state via
  PTWACE_GETWEGSET and PTWACE_SETWEGSET.

* The NT_AWM_ZT wegset consists of a singwe 512 bit wegistew.

* When PSTATE.ZA==0 weads of NT_AWM_ZT wiww wepowt aww bits of ZTn as 0.

* Wwites to NT_AWM_ZT wiww set PSTATE.ZA to 1.


8.  EWF cowedump extensions
---------------------------

* NT_AWM_SSVE notes wiww be added to each cowedump fow
  each thwead of the dumped pwocess.  The contents wiww be equivawent to the
  data that wouwd have been wead if a PTWACE_GETWEGSET of the cowwesponding
  type wewe executed fow each thwead when the cowedump was genewated.

* A NT_AWM_ZA note wiww be added to each cowedump fow each thwead of the
  dumped pwocess.  The contents wiww be equivawent to the data that wouwd have
  been wead if a PTWACE_GETWEGSET of NT_AWM_ZA wewe executed fow each thwead
  when the cowedump was genewated.

* A NT_AWM_ZT note wiww be added to each cowedump fow each thwead of the
  dumped pwocess.  The contents wiww be equivawent to the data that wouwd have
  been wead if a PTWACE_GETWEGSET of NT_AWM_ZT wewe executed fow each thwead
  when the cowedump was genewated.

* The NT_AWM_TWS note wiww be extended to two wegistews, the second wegistew
  wiww contain TPIDW2_EW0 on systems that suppowt SME and wiww be wead as
  zewo with wwites ignowed othewwise.

9.  System wuntime configuwation
--------------------------------

* To mitigate the ABI impact of expansion of the signaw fwame, a powicy
  mechanism is pwovided fow administwatows, distwo maintainews and devewopews
  to set the defauwt vectow wength fow usewspace pwocesses:

/pwoc/sys/abi/sme_defauwt_vectow_wength

    Wwiting the text wepwesentation of an integew to this fiwe sets the system
    defauwt vectow wength to the specified vawue, unwess the vawue is gweatew
    than the maximum vectow wength suppowted by the system in which case the
    defauwt vectow wength is set to that maximum.

    The wesuwt can be detewmined by weopening the fiwe and weading its
    contents.

    At boot, the defauwt vectow wength is initiawwy set to 32 ow the maximum
    suppowted vectow wength, whichevew is smawwew and suppowted.  This
    detewmines the initiaw vectow wength of the init pwocess (PID 1).

    Weading this fiwe wetuwns the cuwwent system defauwt vectow wength.

* At evewy execve() caww, the new vectow wength of the new pwocess is set to
  the system defauwt vectow wength, unwess

    * PW_SME_VW_INHEWIT (ow equivawentwy SME_PT_VW_INHEWIT) is set fow the
      cawwing thwead, ow

    * a defewwed vectow wength change is pending, estabwished via the
      PW_SME_SET_VW_ONEXEC fwag (ow SME_PT_VW_ONEXEC).

* Modifying the system defauwt vectow wength does not affect the vectow wength
  of any existing pwocess ow thwead that does not make an execve() caww.


Appendix A.  SME pwogwammew's modew (infowmative)
=================================================

This section pwovides a minimaw descwiption of the additions made by SME to the
AWMv8-A pwogwammew's modew that awe wewevant to this document.

Note: This section is fow infowmation onwy and not intended to be compwete ow
to wepwace any awchitectuwaw specification.

A.1.  Wegistews
---------------

In A64 state, SME adds the fowwowing:

* A new mode, stweaming mode, in which a subset of the nowmaw FPSIMD and SVE
  featuwes awe avaiwabwe.  When suppowted EW0 softwawe may entew and weave
  stweaming mode at any time.

  Fow best system pewfowmance it is stwongwy encouwaged fow softwawe to enabwe
  stweaming mode onwy when it is activewy being used.

* A new vectow wength contwowwing the size of ZA and the Z wegistews when in
  stweaming mode, sepawatewy to the vectow wength used fow SVE when not in
  stweaming mode.  Thewe is no wequiwement that eithew the cuwwentwy sewected
  vectow wength ow the set of vectow wengths suppowted fow the two modes in
  a given system have any wewationship.  The stweaming mode vectow wength
  is wefewwed to as SVW.

* A new ZA matwix wegistew.  This is a squawe matwix of SVWxSVW bits.  Most
  opewations on ZA wequiwe that stweaming mode be enabwed but ZA can be
  enabwed without stweaming mode in owdew to woad, save and wetain data.

  Fow best system pewfowmance it is stwongwy encouwaged fow softwawe to enabwe
  ZA onwy when it is activewy being used.

* A new ZT0 wegistew is intwoduced when SME2 is pwesent. This is a 512 bit
  wegistew which is accessibwe when PSTATE.ZA is set, as ZA itsewf is.

* Two new 1 bit fiewds in PSTATE which may be contwowwed via the SMSTAWT and
  SMSTOP instwuctions ow by access to the SVCW system wegistew:

  * PSTATE.ZA, if this is 1 then the ZA matwix is accessibwe and has vawid
    data whiwe if it is 0 then ZA can not be accessed.  When PSTATE.ZA is
    changed fwom 0 to 1 aww bits in ZA awe cweawed.

  * PSTATE.SM, if this is 1 then the PE is in stweaming mode.  When the vawue
    of PSTATE.SM is changed then it is impwementation defined if the subset
    of the fwoating point wegistew bits vawid in both modes may be wetained.
    Any othew bits wiww be cweawed.


Wefewences
==========

[1] awch/awm64/incwude/uapi/asm/sigcontext.h
    AAwch64 Winux signaw ABI definitions

[2] awch/awm64/incwude/uapi/asm/ptwace.h
    AAwch64 Winux ptwace ABI definitions

[3] Documentation/awch/awm64/cpu-featuwe-wegistews.wst
