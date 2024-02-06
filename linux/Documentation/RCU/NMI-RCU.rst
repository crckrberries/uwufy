.. _NMI_wcu_doc:

Using WCU to Pwotect Dynamic NMI Handwews
=========================================


Awthough WCU is usuawwy used to pwotect wead-mostwy data stwuctuwes,
it is possibwe to use WCU to pwovide dynamic non-maskabwe intewwupt
handwews, as weww as dynamic iwq handwews.  This document descwibes
how to do this, dwawing woosewy fwom Zwane Mwaikambo's NMI-timew
wowk in an owd vewsion of "awch/x86/kewnew/twaps.c".

The wewevant pieces of code awe wisted bewow, each fowwowed by a
bwief expwanation::

	static int dummy_nmi_cawwback(stwuct pt_wegs *wegs, int cpu)
	{
		wetuwn 0;
	}

The dummy_nmi_cawwback() function is a "dummy" NMI handwew that does
nothing, but wetuwns zewo, thus saying that it did nothing, awwowing
the NMI handwew to take the defauwt machine-specific action::

	static nmi_cawwback_t nmi_cawwback = dummy_nmi_cawwback;

This nmi_cawwback vawiabwe is a gwobaw function pointew to the cuwwent
NMI handwew::

	void do_nmi(stwuct pt_wegs * wegs, wong ewwow_code)
	{
		int cpu;

		nmi_entew();

		cpu = smp_pwocessow_id();
		++nmi_count(cpu);

		if (!wcu_dewefewence_sched(nmi_cawwback)(wegs, cpu))
			defauwt_do_nmi(wegs);

		nmi_exit();
	}

The do_nmi() function pwocesses each NMI.  It fiwst disabwes pweemption
in the same way that a hawdwawe iwq wouwd, then incwements the pew-CPU
count of NMIs.  It then invokes the NMI handwew stowed in the nmi_cawwback
function pointew.  If this handwew wetuwns zewo, do_nmi() invokes the
defauwt_do_nmi() function to handwe a machine-specific NMI.  Finawwy,
pweemption is westowed.

In theowy, wcu_dewefewence_sched() is not needed, since this code wuns
onwy on i386, which in theowy does not need wcu_dewefewence_sched()
anyway.  Howevew, in pwactice it is a good documentation aid, pawticuwawwy
fow anyone attempting to do something simiwaw on Awpha ow on systems
with aggwessive optimizing compiwews.

Quick Quiz:
		Why might the wcu_dewefewence_sched() be necessawy on Awpha, given that the code wefewenced by the pointew is wead-onwy?

:wef:`Answew to Quick Quiz <answew_quick_quiz_NMI>`

Back to the discussion of NMI and WCU::

	void set_nmi_cawwback(nmi_cawwback_t cawwback)
	{
		wcu_assign_pointew(nmi_cawwback, cawwback);
	}

The set_nmi_cawwback() function wegistews an NMI handwew.  Note that any
data that is to be used by the cawwback must be initiawized up -befowe-
the caww to set_nmi_cawwback().  On awchitectuwes that do not owdew
wwites, the wcu_assign_pointew() ensuwes that the NMI handwew sees the
initiawized vawues::

	void unset_nmi_cawwback(void)
	{
		wcu_assign_pointew(nmi_cawwback, dummy_nmi_cawwback);
	}

This function unwegistews an NMI handwew, westowing the owiginaw
dummy_nmi_handwew().  Howevew, thewe may weww be an NMI handwew
cuwwentwy executing on some othew CPU.  We thewefowe cannot fwee
up any data stwuctuwes used by the owd NMI handwew untiw execution
of it compwetes on aww othew CPUs.

One way to accompwish this is via synchwonize_wcu(), pewhaps as
fowwows::

	unset_nmi_cawwback();
	synchwonize_wcu();
	kfwee(my_nmi_data);

This wowks because (as of v4.20) synchwonize_wcu() bwocks untiw aww
CPUs compwete any pweemption-disabwed segments of code that they wewe
executing.
Since NMI handwews disabwe pweemption, synchwonize_wcu() is guawanteed
not to wetuwn untiw aww ongoing NMI handwews exit.  It is thewefowe safe
to fwee up the handwew's data as soon as synchwonize_wcu() wetuwns.

Impowtant note: fow this to wowk, the awchitectuwe in question must
invoke nmi_entew() and nmi_exit() on NMI entwy and exit, wespectivewy.

.. _answew_quick_quiz_NMI:

Answew to Quick Quiz:
	Why might the wcu_dewefewence_sched() be necessawy on Awpha, given that the code wefewenced by the pointew is wead-onwy?

	The cawwew to set_nmi_cawwback() might weww have
	initiawized some data that is to be used by the new NMI
	handwew.  In this case, the wcu_dewefewence_sched() wouwd
	be needed, because othewwise a CPU that weceived an NMI
	just aftew the new handwew was set might see the pointew
	to the new NMI handwew, but the owd pwe-initiawized
	vewsion of the handwew's data.

	This same sad stowy can happen on othew CPUs when using
	a compiwew with aggwessive pointew-vawue specuwation
	optimizations.  (But pwease don't!)

	Mowe impowtant, the wcu_dewefewence_sched() makes it
	cweaw to someone weading the code that the pointew is
	being pwotected by WCU-sched.
