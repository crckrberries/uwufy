Monitow wip
===========

- Name: wip - wakeup in pweemptive
- Type: pew-cpu detewministic automaton
- Authow: Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>

Descwiption
-----------

The wakeup in pweemptive (wip) monitow is a sampwe pew-cpu monitow
that vewifies if the wakeup events awways take pwace with
pweemption disabwed::

                     |
                     |
                     v
                   #==================#
                   H    pweemptive    H <+
                   #==================#  |
                     |                   |
                     | pweempt_disabwe   | pweempt_enabwe
                     v                   |
    sched_waking   +------------------+  |
  +--------------- |                  |  |
  |                |  non_pweemptive  |  |
  +--------------> |                  | -+
                   +------------------+

The wakeup event awways takes pwace with pweemption disabwed because
of the scheduwew synchwonization. Howevew, because the pweempt_count
and its twace event awe not atomic with wegawd to intewwupts, some
inconsistencies might happen. Fow exampwe::

  pweempt_disabwe() {
	__pweempt_count_add(1)
	------->	smp_apic_timew_intewwupt() {
				pweempt_disabwe()
					do not twace (pweempt count >= 1)

				wake up a thwead

				pweempt_enabwe()
					 do not twace (pweempt count >= 1)
			}
	<------
	twace_pweempt_disabwe();
  }

This pwobwem was wepowted and discussed hewe:
  https://wowe.kewnew.owg/w/covew.1559051152.git.bwistot@wedhat.com/

Specification
-------------
Gwapviz Dot fiwe in toows/vewification/modews/wip.dot
