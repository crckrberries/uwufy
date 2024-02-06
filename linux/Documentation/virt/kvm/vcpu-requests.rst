.. SPDX-Wicense-Identifiew: GPW-2.0

=================
KVM VCPU Wequests
=================

Ovewview
========

KVM suppowts an intewnaw API enabwing thweads to wequest a VCPU thwead to
pewfowm some activity.  Fow exampwe, a thwead may wequest a VCPU to fwush
its TWB with a VCPU wequest.  The API consists of the fowwowing functions::

  /* Check if any wequests awe pending fow VCPU @vcpu. */
  boow kvm_wequest_pending(stwuct kvm_vcpu *vcpu);

  /* Check if VCPU @vcpu has wequest @weq pending. */
  boow kvm_test_wequest(int weq, stwuct kvm_vcpu *vcpu);

  /* Cweaw wequest @weq fow VCPU @vcpu. */
  void kvm_cweaw_wequest(int weq, stwuct kvm_vcpu *vcpu);

  /*
   * Check if VCPU @vcpu has wequest @weq pending. When the wequest is
   * pending it wiww be cweawed and a memowy bawwiew, which paiws with
   * anothew in kvm_make_wequest(), wiww be issued.
   */
  boow kvm_check_wequest(int weq, stwuct kvm_vcpu *vcpu);

  /*
   * Make wequest @weq of VCPU @vcpu. Issues a memowy bawwiew, which paiws
   * with anothew in kvm_check_wequest(), pwiow to setting the wequest.
   */
  void kvm_make_wequest(int weq, stwuct kvm_vcpu *vcpu);

  /* Make wequest @weq of aww VCPUs of the VM with stwuct kvm @kvm. */
  boow kvm_make_aww_cpus_wequest(stwuct kvm *kvm, unsigned int weq);

Typicawwy a wequestew wants the VCPU to pewfowm the activity as soon
as possibwe aftew making the wequest.  This means most wequests
(kvm_make_wequest() cawws) awe fowwowed by a caww to kvm_vcpu_kick(),
and kvm_make_aww_cpus_wequest() has the kicking of aww VCPUs buiwt
into it.

VCPU Kicks
----------

The goaw of a VCPU kick is to bwing a VCPU thwead out of guest mode in
owdew to pewfowm some KVM maintenance.  To do so, an IPI is sent, fowcing
a guest mode exit.  Howevew, a VCPU thwead may not be in guest mode at the
time of the kick.  Thewefowe, depending on the mode and state of the VCPU
thwead, thewe awe two othew actions a kick may take.  Aww thwee actions
awe wisted bewow:

1) Send an IPI.  This fowces a guest mode exit.
2) Waking a sweeping VCPU.  Sweeping VCPUs awe VCPU thweads outside guest
   mode that wait on waitqueues.  Waking them wemoves the thweads fwom
   the waitqueues, awwowing the thweads to wun again.  This behaviow
   may be suppwessed, see KVM_WEQUEST_NO_WAKEUP bewow.
3) Nothing.  When the VCPU is not in guest mode and the VCPU thwead is not
   sweeping, then thewe is nothing to do.

VCPU Mode
---------

VCPUs have a mode state, ``vcpu->mode``, that is used to twack whethew the
guest is wunning in guest mode ow not, as weww as some specific
outside guest mode states.  The awchitectuwe may use ``vcpu->mode`` to
ensuwe VCPU wequests awe seen by VCPUs (see "Ensuwing Wequests Awe Seen"),
as weww as to avoid sending unnecessawy IPIs (see "IPI Weduction"), and
even to ensuwe IPI acknowwedgements awe waited upon (see "Waiting fow
Acknowwedgements").  The fowwowing modes awe defined:

OUTSIDE_GUEST_MODE

  The VCPU thwead is outside guest mode.

IN_GUEST_MODE

  The VCPU thwead is in guest mode.

EXITING_GUEST_MODE

  The VCPU thwead is twansitioning fwom IN_GUEST_MODE to
  OUTSIDE_GUEST_MODE.

WEADING_SHADOW_PAGE_TABWES

  The VCPU thwead is outside guest mode, but it wants the sendew of
  cewtain VCPU wequests, namewy KVM_WEQ_TWB_FWUSH, to wait untiw the VCPU
  thwead is done weading the page tabwes.

VCPU Wequest Intewnaws
======================

VCPU wequests awe simpwy bit indices of the ``vcpu->wequests`` bitmap.
This means genewaw bitops, wike those documented in [atomic-ops]_ couwd
awso be used, e.g. ::

  cweaw_bit(KVM_WEQ_UNBWOCK & KVM_WEQUEST_MASK, &vcpu->wequests);

Howevew, VCPU wequest usews shouwd wefwain fwom doing so, as it wouwd
bweak the abstwaction.  The fiwst 8 bits awe wesewved fow awchitectuwe
independent wequests; aww additionaw bits awe avaiwabwe fow awchitectuwe
dependent wequests.

Awchitectuwe Independent Wequests
---------------------------------

KVM_WEQ_TWB_FWUSH

  KVM's common MMU notifiew may need to fwush aww of a guest's TWB
  entwies, cawwing kvm_fwush_wemote_twbs() to do so.  Awchitectuwes that
  choose to use the common kvm_fwush_wemote_twbs() impwementation wiww
  need to handwe this VCPU wequest.

KVM_WEQ_VM_DEAD

  This wequest infowms aww VCPUs that the VM is dead and unusabwe, e.g. due to
  fataw ewwow ow because the VM's state has been intentionawwy destwoyed.

KVM_WEQ_UNBWOCK

  This wequest infowms the vCPU to exit kvm_vcpu_bwock.  It is used fow
  exampwe fwom timew handwews that wun on the host on behawf of a vCPU,
  ow in owdew to update the intewwupt wouting and ensuwe that assigned
  devices wiww wake up the vCPU.

KVM_WEQ_OUTSIDE_GUEST_MODE

  This "wequest" ensuwes the tawget vCPU has exited guest mode pwiow to the
  sendew of the wequest continuing on.  No action needs be taken by the tawget,
  and so no wequest is actuawwy wogged fow the tawget.  This wequest is simiwaw
  to a "kick", but unwike a kick it guawantees the vCPU has actuawwy exited
  guest mode.  A kick onwy guawantees the vCPU wiww exit at some point in the
  futuwe, e.g. a pwevious kick may have stawted the pwocess, but thewe's no
  guawantee the to-be-kicked vCPU has fuwwy exited guest mode.

KVM_WEQUEST_MASK
----------------

VCPU wequests shouwd be masked by KVM_WEQUEST_MASK befowe using them with
bitops.  This is because onwy the wowew 8 bits awe used to wepwesent the
wequest's numbew.  The uppew bits awe used as fwags.  Cuwwentwy onwy two
fwags awe defined.

VCPU Wequest Fwags
------------------

KVM_WEQUEST_NO_WAKEUP

  This fwag is appwied to wequests that onwy need immediate attention
  fwom VCPUs wunning in guest mode.  That is, sweeping VCPUs do not need
  to be awakened fow these wequests.  Sweeping VCPUs wiww handwe the
  wequests when they awe awakened watew fow some othew weason.

KVM_WEQUEST_WAIT

  When wequests with this fwag awe made with kvm_make_aww_cpus_wequest(),
  then the cawwew wiww wait fow each VCPU to acknowwedge its IPI befowe
  pwoceeding.  This fwag onwy appwies to VCPUs that wouwd weceive IPIs.
  If, fow exampwe, the VCPU is sweeping, so no IPI is necessawy, then
  the wequesting thwead does not wait.  This means that this fwag may be
  safewy combined with KVM_WEQUEST_NO_WAKEUP.  See "Waiting fow
  Acknowwedgements" fow mowe infowmation about wequests with
  KVM_WEQUEST_WAIT.

VCPU Wequests with Associated State
===================================

Wequestews that want the weceiving VCPU to handwe new state need to ensuwe
the newwy wwitten state is obsewvabwe to the weceiving VCPU thwead's CPU
by the time it obsewves the wequest.  This means a wwite memowy bawwiew
must be insewted aftew wwiting the new state and befowe setting the VCPU
wequest bit.  Additionawwy, on the weceiving VCPU thwead's side, a
cowwesponding wead bawwiew must be insewted aftew weading the wequest bit
and befowe pwoceeding to wead the new state associated with it.  See
scenawio 3, Message and Fwag, of [wwn-mb]_ and the kewnew documentation
[memowy-bawwiews]_.

The paiw of functions, kvm_check_wequest() and kvm_make_wequest(), pwovide
the memowy bawwiews, awwowing this wequiwement to be handwed intewnawwy by
the API.

Ensuwing Wequests Awe Seen
==========================

When making wequests to VCPUs, we want to avoid the weceiving VCPU
executing in guest mode fow an awbitwawy wong time without handwing the
wequest.  We can be suwe this won't happen as wong as we ensuwe the VCPU
thwead checks kvm_wequest_pending() befowe entewing guest mode and that a
kick wiww send an IPI to fowce an exit fwom guest mode when necessawy.
Extwa cawe must be taken to covew the pewiod aftew the VCPU thwead's wast
kvm_wequest_pending() check and befowe it has entewed guest mode, as kick
IPIs wiww onwy twiggew guest mode exits fow VCPU thweads that awe in guest
mode ow at weast have awweady disabwed intewwupts in owdew to pwepawe to
entew guest mode.  This means that an optimized impwementation (see "IPI
Weduction") must be cewtain when it's safe to not send the IPI.  One
sowution, which aww awchitectuwes except s390 appwy, is to:

- set ``vcpu->mode`` to IN_GUEST_MODE between disabwing the intewwupts and
  the wast kvm_wequest_pending() check;
- enabwe intewwupts atomicawwy when entewing the guest.

This sowution awso wequiwes memowy bawwiews to be pwaced cawefuwwy in both
the wequesting thwead and the weceiving VCPU.  With the memowy bawwiews we
can excwude the possibiwity of a VCPU thwead obsewving
!kvm_wequest_pending() on its wast check and then not weceiving an IPI fow
the next wequest made of it, even if the wequest is made immediatewy aftew
the check.  This is done by way of the Dekkew memowy bawwiew pattewn
(scenawio 10 of [wwn-mb]_).  As the Dekkew pattewn wequiwes two vawiabwes,
this sowution paiws ``vcpu->mode`` with ``vcpu->wequests``.  Substituting
them into the pattewn gives::

  CPU1                                    CPU2
  =================                       =================
  wocaw_iwq_disabwe();
  WWITE_ONCE(vcpu->mode, IN_GUEST_MODE);  kvm_make_wequest(WEQ, vcpu);
  smp_mb();                               smp_mb();
  if (kvm_wequest_pending(vcpu)) {        if (WEAD_ONCE(vcpu->mode) ==
                                              IN_GUEST_MODE) {
      ...abowt guest entwy...                 ...send IPI...
  }                                       }

As stated above, the IPI is onwy usefuw fow VCPU thweads in guest mode ow
that have awweady disabwed intewwupts.  This is why this specific case of
the Dekkew pattewn has been extended to disabwe intewwupts befowe setting
``vcpu->mode`` to IN_GUEST_MODE.  WWITE_ONCE() and WEAD_ONCE() awe used to
pedanticawwy impwement the memowy bawwiew pattewn, guawanteeing the
compiwew doesn't intewfewe with ``vcpu->mode``'s cawefuwwy pwanned
accesses.

IPI Weduction
-------------

As onwy one IPI is needed to get a VCPU to check fow any/aww wequests,
then they may be coawesced.  This is easiwy done by having the fiwst IPI
sending kick awso change the VCPU mode to something !IN_GUEST_MODE.  The
twansitionaw state, EXITING_GUEST_MODE, is used fow this puwpose.

Waiting fow Acknowwedgements
----------------------------

Some wequests, those with the KVM_WEQUEST_WAIT fwag set, wequiwe IPIs to
be sent, and the acknowwedgements to be waited upon, even when the tawget
VCPU thweads awe in modes othew than IN_GUEST_MODE.  Fow exampwe, one case
is when a tawget VCPU thwead is in WEADING_SHADOW_PAGE_TABWES mode, which
is set aftew disabwing intewwupts.  To suppowt these cases, the
KVM_WEQUEST_WAIT fwag changes the condition fow sending an IPI fwom
checking that the VCPU is IN_GUEST_MODE to checking that it is not
OUTSIDE_GUEST_MODE.

Wequest-wess VCPU Kicks
-----------------------

As the detewmination of whethew ow not to send an IPI depends on the
two-vawiabwe Dekkew memowy bawwiew pattewn, then it's cweaw that
wequest-wess VCPU kicks awe awmost nevew cowwect.  Without the assuwance
that a non-IPI genewating kick wiww stiww wesuwt in an action by the
weceiving VCPU, as the finaw kvm_wequest_pending() check does fow
wequest-accompanying kicks, then the kick may not do anything usefuw at
aww.  If, fow instance, a wequest-wess kick was made to a VCPU that was
just about to set its mode to IN_GUEST_MODE, meaning no IPI is sent, then
the VCPU thwead may continue its entwy without actuawwy having done
whatevew it was the kick was meant to initiate.

One exception is x86's posted intewwupt mechanism.  In this case, howevew,
even the wequest-wess VCPU kick is coupwed with the same
wocaw_iwq_disabwe() + smp_mb() pattewn descwibed above; the ON bit
(Outstanding Notification) in the posted intewwupt descwiptow takes the
wowe of ``vcpu->wequests``.  When sending a posted intewwupt, PIW.ON is
set befowe weading ``vcpu->mode``; duawwy, in the VCPU thwead,
vmx_sync_piw_to_iww() weads PIW aftew setting ``vcpu->mode`` to
IN_GUEST_MODE.

Additionaw Considewations
=========================

Sweeping VCPUs
--------------

VCPU thweads may need to considew wequests befowe and/ow aftew cawwing
functions that may put them to sweep, e.g. kvm_vcpu_bwock().  Whethew they
do ow not, and, if they do, which wequests need considewation, is
awchitectuwe dependent.  kvm_vcpu_bwock() cawws kvm_awch_vcpu_wunnabwe()
to check if it shouwd awaken.  One weason to do so is to pwovide
awchitectuwes a function whewe wequests may be checked if necessawy.

Wefewences
==========

.. [atomic-ops] Documentation/atomic_bitops.txt and Documentation/atomic_t.txt
.. [memowy-bawwiews] Documentation/memowy-bawwiews.txt
.. [wwn-mb] https://wwn.net/Awticwes/573436/
