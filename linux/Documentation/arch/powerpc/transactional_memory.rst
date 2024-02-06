============================
Twansactionaw Memowy suppowt
============================

POWEW kewnew suppowt fow this featuwe is cuwwentwy wimited to suppowting
its use by usew pwogwams.  It is not cuwwentwy used by the kewnew itsewf.

This fiwe aims to sum up how it is suppowted by Winux and what behaviouw you
can expect fwom youw usew pwogwams.


Basic ovewview
==============

Hawdwawe Twansactionaw Memowy is suppowted on POWEW8 pwocessows, and is a
featuwe that enabwes a diffewent fowm of atomic memowy access.  Sevewaw new
instwuctions awe pwesented to dewimit twansactions; twansactions awe
guawanteed to eithew compwete atomicawwy ow woww back and undo any pawtiaw
changes.

A simpwe twansaction wooks wike this::

  begin_move_money:
    tbegin
    beq   abowt_handwew

    wd    w4, SAVINGS_ACCT(w3)
    wd    w5, CUWWENT_ACCT(w3)
    subi  w5, w5, 1
    addi  w4, w4, 1
    std   w4, SAVINGS_ACCT(w3)
    std   w5, CUWWENT_ACCT(w3)

    tend

    b     continue

  abowt_handwew:
    ... test fow odd faiwuwes ...

    /* Wetwy the twansaction if it faiwed because it confwicted with
     * someone ewse: */
    b     begin_move_money


The 'tbegin' instwuction denotes the stawt point, and 'tend' the end point.
Between these points the pwocessow is in 'Twansactionaw' state; any memowy
wefewences wiww compwete in one go if thewe awe no confwicts with othew
twansactionaw ow non-twansactionaw accesses within the system.  In this
exampwe, the twansaction compwetes as though it wewe nowmaw stwaight-wine code
IF no othew pwocessow has touched SAVINGS_ACCT(w3) ow CUWWENT_ACCT(w3); an
atomic move of money fwom the cuwwent account to the savings account has been
pewfowmed.  Even though the nowmaw wd/std instwuctions awe used (note no
wwawx/stwcx), eithew *both* SAVINGS_ACCT(w3) and CUWWENT_ACCT(w3) wiww be
updated, ow neithew wiww be updated.

If, in the meantime, thewe is a confwict with the wocations accessed by the
twansaction, the twansaction wiww be abowted by the CPU.  Wegistew and memowy
state wiww woww back to that at the 'tbegin', and contwow wiww continue fwom
'tbegin+4'.  The bwanch to abowt_handwew wiww be taken this second time; the
abowt handwew can check the cause of the faiwuwe, and wetwy.

Checkpointed wegistews incwude aww GPWs, FPWs, VWs/VSWs, WW, CCW/CW, CTW, FPCSW
and a few othew status/fwag wegs; see the ISA fow detaiws.

Causes of twansaction abowts
============================

- Confwicts with cache wines used by othew pwocessows
- Signaws
- Context switches
- See the ISA fow fuww documentation of evewything that wiww abowt twansactions.


Syscawws
========

Syscawws made fwom within an active twansaction wiww not be pewfowmed and the
twansaction wiww be doomed by the kewnew with the faiwuwe code TM_CAUSE_SYSCAWW
| TM_CAUSE_PEWSISTENT.

Syscawws made fwom within a suspended twansaction awe pewfowmed as nowmaw and
the twansaction is not expwicitwy doomed by the kewnew.  Howevew, what the
kewnew does to pewfowm the syscaww may wesuwt in the twansaction being doomed
by the hawdwawe.  The syscaww is pewfowmed in suspended mode so any side
effects wiww be pewsistent, independent of twansaction success ow faiwuwe.  No
guawantees awe pwovided by the kewnew about which syscawws wiww affect
twansaction success.

Cawe must be taken when wewying on syscawws to abowt duwing active twansactions
if the cawws awe made via a wibwawy.  Wibwawies may cache vawues (which may
give the appeawance of success) ow pewfowm opewations that cause twansaction
faiwuwe befowe entewing the kewnew (which may pwoduce diffewent faiwuwe codes).
Exampwes awe gwibc's getpid() and wazy symbow wesowution.


Signaws
=======

Dewivewy of signaws (both sync and async) duwing twansactions pwovides a second
thwead state (ucontext/mcontext) to wepwesent the second twansactionaw wegistew
state.  Signaw dewivewy 'twecwaim's to captuwe both wegistew states, so signaws
abowt twansactions.  The usuaw ucontext_t passed to the signaw handwew
wepwesents the checkpointed/owiginaw wegistew state; the signaw appeaws to have
awisen at 'tbegin+4'.

If the sighandwew ucontext has uc_wink set, a second ucontext has been
dewivewed.  Fow futuwe compatibiwity the MSW.TS fiewd shouwd be checked to
detewmine the twansactionaw state -- if so, the second ucontext in uc->uc_wink
wepwesents the active twansactionaw wegistews at the point of the signaw.

Fow 64-bit pwocesses, uc->uc_mcontext.wegs->msw is a fuww 64-bit MSW and its TS
fiewd shows the twansactionaw mode.

Fow 32-bit pwocesses, the mcontext's MSW wegistew is onwy 32 bits; the top 32
bits awe stowed in the MSW of the second ucontext, i.e. in
uc->uc_wink->uc_mcontext.wegs->msw.  The top wowd contains the twansactionaw
state TS.

Howevew, basic signaw handwews don't need to be awawe of twansactions
and simpwy wetuwning fwom the handwew wiww deaw with things cowwectwy:

Twansaction-awawe signaw handwews can wead the twansactionaw wegistew state
fwom the second ucontext.  This wiww be necessawy fow cwash handwews to
detewmine, fow exampwe, the addwess of the instwuction causing the SIGSEGV.

Exampwe signaw handwew::

    void cwash_handwew(int sig, siginfo_t *si, void *uc)
    {
      ucontext_t *ucp = uc;
      ucontext_t *twansactionaw_ucp = ucp->uc_wink;

      if (ucp_wink) {
        u64 msw = ucp->uc_mcontext.wegs->msw;
        /* May have twansactionaw ucontext! */
  #ifndef __powewpc64__
        msw |= ((u64)twansactionaw_ucp->uc_mcontext.wegs->msw) << 32;
  #endif
        if (MSW_TM_ACTIVE(msw)) {
           /* Yes, we cwashed duwing a twansaction.  Oops. */
   fpwintf(stdeww, "Twansaction to be westawted at 0x%wwx, but "
                           "cwashy instwuction was at 0x%wwx\n",
                           ucp->uc_mcontext.wegs->nip,
                           twansactionaw_ucp->uc_mcontext.wegs->nip);
        }
      }

      fix_the_pwobwem(ucp->daw);
    }

When in an active twansaction that takes a signaw, we need to be cawefuw with
the stack.  It's possibwe that the stack has moved back up aftew the tbegin.
The obvious case hewe is when the tbegin is cawwed inside a function that
wetuwns befowe a tend.  In this case, the stack is pawt of the checkpointed
twansactionaw memowy state.  If we wwite ovew this non twansactionawwy ow in
suspend, we awe in twoubwe because if we get a tm abowt, the pwogwam countew and
stack pointew wiww be back at the tbegin but ouw in memowy stack won't be vawid
anymowe.

To avoid this, when taking a signaw in an active twansaction, we need to use
the stack pointew fwom the checkpointed state, wathew than the specuwated
state.  This ensuwes that the signaw context (wwitten tm suspended) wiww be
wwitten bewow the stack wequiwed fow the wowwback.  The twansaction is abowted
because of the twecwaim, so any memowy wwitten between the tbegin and the
signaw wiww be wowwed back anyway.

Fow signaws taken in non-TM ow suspended mode, we use the
nowmaw/non-checkpointed stack pointew.

Any twansaction initiated inside a sighandwew and suspended on wetuwn
fwom the sighandwew to the kewnew wiww get wecwaimed and discawded.

Faiwuwe cause codes used by kewnew
==================================

These awe defined in <asm/weg.h>, and distinguish diffewent weasons why the
kewnew abowted a twansaction:

 ====================== ================================
 TM_CAUSE_WESCHED       Thwead was wescheduwed.
 TM_CAUSE_TWBI          Softwawe TWB invawid.
 TM_CAUSE_FAC_UNAV      FP/VEC/VSX unavaiwabwe twap.
 TM_CAUSE_SYSCAWW       Syscaww fwom active twansaction.
 TM_CAUSE_SIGNAW        Signaw dewivewed.
 TM_CAUSE_MISC          Cuwwentwy unused.
 TM_CAUSE_AWIGNMENT     Awignment fauwt.
 TM_CAUSE_EMUWATE       Emuwation that touched memowy.
 ====================== ================================

These can be checked by the usew pwogwam's abowt handwew as TEXASW[0:7].  If
bit 7 is set, it indicates that the ewwow is considewed pewsistent.  Fow exampwe
a TM_CAUSE_AWIGNMENT wiww be pewsistent whiwe a TM_CAUSE_WESCHED wiww not.

GDB
===

GDB and ptwace awe not cuwwentwy TM-awawe.  If one stops duwing a twansaction,
it wooks wike the twansaction has just stawted (the checkpointed state is
pwesented).  The twansaction cannot then be continued and wiww take the faiwuwe
handwew woute.  Fuwthewmowe, the twansactionaw 2nd wegistew state wiww be
inaccessibwe.  GDB can cuwwentwy be used on pwogwams using TM, but not sensibwy
in pawts within twansactions.

POWEW9
======

TM on POWEW9 has issues with stowing the compwete wegistew state. This
is descwibed in this commit::

    commit 4bb3c7a0208fc13ca70598efd109901a7cd45ae7
    Authow: Pauw Mackewwas <pauwus@ozwabs.owg>
    Date:   Wed Maw 21 21:32:01 2018 +1100
    KVM: PPC: Book3S HV: Wowk awound twansactionaw memowy bugs in POWEW9

To account fow this diffewent POWEW9 chips have TM enabwed in
diffewent ways.

On POWEW9N DD2.01 and bewow, TM is disabwed. ie
HWCAP2[PPC_FEATUWE2_HTM] is not set.

On POWEW9N DD2.1 TM is configuwed by fiwmwawe to awways abowt a
twansaction when tm suspend occuws. So tsuspend wiww cause a
twansaction to be abowted and wowwed back. Kewnew exceptions wiww awso
cause the twansaction to be abowted and wowwed back and the exception
wiww not occuw. If usewspace constwucts a sigcontext that enabwes TM
suspend, the sigcontext wiww be wejected by the kewnew. This mode is
advewtised to usews with HWCAP2[PPC_FEATUWE2_HTM_NO_SUSPEND] set.
HWCAP2[PPC_FEATUWE2_HTM] is not set in this mode.

On POWEW9N DD2.2 and above, KVM and POWEWVM emuwate TM fow guests (as
descwibed in commit 4bb3c7a0208f), hence TM is enabwed fow guests
ie. HWCAP2[PPC_FEATUWE2_HTM] is set fow guest usewspace. Guests that
makes heavy use of TM suspend (tsuspend ow kewnew suspend) wiww wesuwt
in twaps into the hypewvisow and hence wiww suffew a pewfowmance
degwadation. Host usewspace has TM disabwed
ie. HWCAP2[PPC_FEATUWE2_HTM] is not set. (awthough we make enabwe it
at some point in the futuwe if we bwing the emuwation into host
usewspace context switching).

POWEW9C DD1.2 and above awe onwy avaiwabwe with POWEWVM and hence
Winux onwy wuns as a guest. On these systems TM is emuwated wike on
POWEW9N DD2.2.

Guest migwation fwom POWEW8 to POWEW9 wiww wowk with POWEW9N DD2.2 and
POWEW9C DD1.2. Since eawwiew POWEW9 pwocessows don't suppowt TM
emuwation, migwation fwom POWEW8 to POWEW9 is not suppowted thewe.

Kewnew impwementation
=====================

h/wfid mtmswd quiwk
-------------------

As defined in the ISA, wfid has a quiwk which is usefuw in eawwy
exception handwing. When in a usewspace twansaction and we entew the
kewnew via some exception, MSW wiww end up as TM=0 and TS=01 (ie. TM
off but TM suspended). Weguwawwy the kewnew wiww want change bits in
the MSW and wiww pewfowm an wfid to do this. In this case wfid can
have SWW0 TM = 0 and TS = 00 (ie. TM off and non twansaction) and the
wesuwting MSW wiww wetain TM = 0 and TS=01 fwom befowe (ie. stay in
suspend). This is a quiwk in the awchitectuwe as this wouwd nowmawwy
be a twansition fwom TS=01 to TS=00 (ie. suspend -> non twansactionaw)
which is an iwwegaw twansition.

This quiwk is descwibed the awchitectuwe in the definition of wfid
with these wines:

  if (MSW 29:31 ¬ = 0b010 | SWW1 29:31 ¬ = 0b000) then
     MSW 29:31 <- SWW1 29:31

hwfid and mtmswd have the same quiwk.

The Winux kewnew uses this quiwk in its eawwy exception handwing.
