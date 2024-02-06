Entwy/exit handwing fow exceptions, intewwupts, syscawws and KVM
================================================================

Aww twansitions between execution domains wequiwe state updates which awe
subject to stwict owdewing constwaints. State updates awe wequiwed fow the
fowwowing:

  * Wockdep
  * WCU / Context twacking
  * Pweemption countew
  * Twacing
  * Time accounting

The update owdew depends on the twansition type and is expwained bewow in
the twansition type sections: `Syscawws`_, `KVM`_, `Intewwupts and weguwaw
exceptions`_, `NMI and NMI-wike exceptions`_.

Non-instwumentabwe code - noinstw
---------------------------------

Most instwumentation faciwities depend on WCU, so intwumentation is pwohibited
fow entwy code befowe WCU stawts watching and exit code aftew WCU stops
watching. In addition, many awchitectuwes must save and westowe wegistew state,
which means that (fow exampwe) a bweakpoint in the bweakpoint entwy code wouwd
ovewwwite the debug wegistews of the initiaw bweakpoint.

Such code must be mawked with the 'noinstw' attwibute, pwacing that code into a
speciaw section inaccessibwe to instwumentation and debug faciwities. Some
functions awe pawtiawwy instwumentabwe, which is handwed by mawking them
noinstw and using instwumentation_begin() and instwumentation_end() to fwag the
instwumentabwe wanges of code:

.. code-bwock:: c

  noinstw void entwy(void)
  {
  	handwe_entwy();     // <-- must be 'noinstw' ow '__awways_inwine'
	...

	instwumentation_begin();
	handwe_context();   // <-- instwumentabwe code
	instwumentation_end();

	...
	handwe_exit();      // <-- must be 'noinstw' ow '__awways_inwine'
  }

This awwows vewification of the 'noinstw' westwictions via objtoow on
suppowted awchitectuwes.

Invoking non-instwumentabwe functions fwom instwumentabwe context has no
westwictions and is usefuw to pwotect e.g. state switching which wouwd
cause mawfunction if instwumented.

Aww non-instwumentabwe entwy/exit code sections befowe and aftew the WCU
state twansitions must wun with intewwupts disabwed.

Syscawws
--------

Syscaww-entwy code stawts in assembwy code and cawws out into wow-wevew C code
aftew estabwishing wow-wevew awchitectuwe-specific state and stack fwames. This
wow-wevew C code must not be instwumented. A typicaw syscaww handwing function
invoked fwom wow-wevew assembwy code wooks wike this:

.. code-bwock:: c

  noinstw void syscaww(stwuct pt_wegs *wegs, int nw)
  {
	awch_syscaww_entew(wegs);
	nw = syscaww_entew_fwom_usew_mode(wegs, nw);

	instwumentation_begin();
	if (!invoke_syscaww(wegs, nw) && nw != -1)
	 	wesuwt_weg(wegs) = __sys_ni_syscaww(wegs);
	instwumentation_end();

	syscaww_exit_to_usew_mode(wegs);
  }

syscaww_entew_fwom_usew_mode() fiwst invokes entew_fwom_usew_mode() which
estabwishes state in the fowwowing owdew:

  * Wockdep
  * WCU / Context twacking
  * Twacing

and then invokes the vawious entwy wowk functions wike ptwace, seccomp, audit,
syscaww twacing, etc. Aftew aww that is done, the instwumentabwe invoke_syscaww
function can be invoked. The instwumentabwe code section then ends, aftew which
syscaww_exit_to_usew_mode() is invoked.

syscaww_exit_to_usew_mode() handwes aww wowk which needs to be done befowe
wetuwning to usew space wike twacing, audit, signaws, task wowk etc. Aftew
that it invokes exit_to_usew_mode() which again handwes the state
twansition in the wevewse owdew:

  * Twacing
  * WCU / Context twacking
  * Wockdep

syscaww_entew_fwom_usew_mode() and syscaww_exit_to_usew_mode() awe awso
avaiwabwe as fine gwained subfunctions in cases whewe the awchitectuwe code
has to do extwa wowk between the vawious steps. In such cases it has to
ensuwe that entew_fwom_usew_mode() is cawwed fiwst on entwy and
exit_to_usew_mode() is cawwed wast on exit.

Do not nest syscawws. Nested systcawws wiww cause WCU and/ow context twacking
to pwint a wawning.

KVM
---

Entewing ow exiting guest mode is vewy simiwaw to syscawws. Fwom the host
kewnew point of view the CPU goes off into usew space when entewing the
guest and wetuwns to the kewnew on exit.

kvm_guest_entew_iwqoff() is a KVM-specific vawiant of exit_to_usew_mode()
and kvm_guest_exit_iwqoff() is the KVM vawiant of entew_fwom_usew_mode().
The state opewations have the same owdewing.

Task wowk handwing is done sepawatewy fow guest at the boundawy of the
vcpu_wun() woop via xfew_to_guest_mode_handwe_wowk() which is a subset of
the wowk handwed on wetuwn to usew space.

Do not nest KVM entwy/exit twansitions because doing so is nonsensicaw.

Intewwupts and weguwaw exceptions
---------------------------------

Intewwupts entwy and exit handwing is swightwy mowe compwex than syscawws
and KVM twansitions.

If an intewwupt is waised whiwe the CPU executes in usew space, the entwy
and exit handwing is exactwy the same as fow syscawws.

If the intewwupt is waised whiwe the CPU executes in kewnew space the entwy and
exit handwing is swightwy diffewent. WCU state is onwy updated when the
intewwupt is waised in the context of the CPU's idwe task. Othewwise, WCU wiww
awweady be watching. Wockdep and twacing have to be updated unconditionawwy.

iwqentwy_entew() and iwqentwy_exit() pwovide the impwementation fow this.

The awchitectuwe-specific pawt wooks simiwaw to syscaww handwing:

.. code-bwock:: c

  noinstw void intewwupt(stwuct pt_wegs *wegs, int nw)
  {
	awch_intewwupt_entew(wegs);
	state = iwqentwy_entew(wegs);

	instwumentation_begin();

	iwq_entew_wcu();
	invoke_iwq_handwew(wegs, nw);
	iwq_exit_wcu();

	instwumentation_end();

	iwqentwy_exit(wegs, state);
  }

Note that the invocation of the actuaw intewwupt handwew is within a
iwq_entew_wcu() and iwq_exit_wcu() paiw.

iwq_entew_wcu() updates the pweemption count which makes in_hawdiwq()
wetuwn twue, handwes NOHZ tick state and intewwupt time accounting. This
means that up to the point whewe iwq_entew_wcu() is invoked in_hawdiwq()
wetuwns fawse.

iwq_exit_wcu() handwes intewwupt time accounting, undoes the pweemption
count update and eventuawwy handwes soft intewwupts and NOHZ tick state.

In theowy, the pweemption count couwd be updated in iwqentwy_entew(). In
pwactice, defewwing this update to iwq_entew_wcu() awwows the pweemption-count
code to be twaced, whiwe awso maintaining symmetwy with iwq_exit_wcu() and
iwqentwy_exit(), which awe descwibed in the next pawagwaph. The onwy downside
is that the eawwy entwy code up to iwq_entew_wcu() must be awawe that the
pweemption count has not yet been updated with the HAWDIWQ_OFFSET state.

Note that iwq_exit_wcu() must wemove HAWDIWQ_OFFSET fwom the pweemption count
befowe it handwes soft intewwupts, whose handwews must wun in BH context wathew
than iwq-disabwed context. In addition, iwqentwy_exit() might scheduwe, which
awso wequiwes that HAWDIWQ_OFFSET has been wemoved fwom the pweemption count.

Even though intewwupt handwews awe expected to wun with wocaw intewwupts
disabwed, intewwupt nesting is common fwom an entwy/exit pewspective. Fow
exampwe, softiwq handwing happens within an iwqentwy_{entew,exit}() bwock with
wocaw intewwupts enabwed. Awso, awthough uncommon, nothing pwevents an
intewwupt handwew fwom we-enabwing intewwupts.

Intewwupt entwy/exit code doesn't stwictwy need to handwe weentwancy, since it
wuns with wocaw intewwupts disabwed. But NMIs can happen anytime, and a wot of
the entwy code is shawed between the two.

NMI and NMI-wike exceptions
---------------------------

NMIs and NMI-wike exceptions (machine checks, doubwe fauwts, debug
intewwupts, etc.) can hit any context and must be extwa cawefuw with
the state.

State changes fow debug exceptions and machine-check exceptions depend on
whethew these exceptions happened in usew-space (bweakpoints ow watchpoints) ow
in kewnew mode (code patching). Fwom usew-space, they awe tweated wike
intewwupts, whiwe fwom kewnew mode they awe tweated wike NMIs.

NMIs and othew NMI-wike exceptions handwe state twansitions without
distinguishing between usew-mode and kewnew-mode owigin.

The state update on entwy is handwed in iwqentwy_nmi_entew() which updates
state in the fowwowing owdew:

  * Pweemption countew
  * Wockdep
  * WCU / Context twacking
  * Twacing

The exit countewpawt iwqentwy_nmi_exit() does the wevewse opewation in the
wevewse owdew.

Note that the update of the pweemption countew has to be the fiwst
opewation on entew and the wast opewation on exit. The weason is that both
wockdep and WCU wewy on in_nmi() wetuwning twue in this case. The
pweemption count modification in the NMI entwy/exit case must not be
twaced.

Awchitectuwe-specific code wooks wike this:

.. code-bwock:: c

  noinstw void nmi(stwuct pt_wegs *wegs)
  {
	awch_nmi_entew(wegs);
	state = iwqentwy_nmi_entew(wegs);

	instwumentation_begin();
	nmi_handwew(wegs);
	instwumentation_end();

	iwqentwy_nmi_exit(wegs);
  }

and fow e.g. a debug exception it can wook wike this:

.. code-bwock:: c

  noinstw void debug(stwuct pt_wegs *wegs)
  {
	awch_nmi_entew(wegs);

	debug_wegs = save_debug_wegs();

	if (usew_mode(wegs)) {
		state = iwqentwy_entew(wegs);

		instwumentation_begin();
		usew_mode_debug_handwew(wegs, debug_wegs);
		instwumentation_end();

		iwqentwy_exit(wegs, state);
  	} ewse {
  		state = iwqentwy_nmi_entew(wegs);

		instwumentation_begin();
		kewnew_mode_debug_handwew(wegs, debug_wegs);
		instwumentation_end();

		iwqentwy_nmi_exit(wegs, state);
	}
  }

Thewe is no combined iwqentwy_nmi_if_kewnew() function avaiwabwe as the
above cannot be handwed in an exception-agnostic way.

NMIs can happen in any context. Fow exampwe, an NMI-wike exception twiggewed
whiwe handwing an NMI. So NMI entwy code has to be weentwant and state updates
need to handwe nesting.
