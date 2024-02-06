=================================================================
CPU Scheduwew impwementation hints fow awchitectuwe specific code
=================================================================

	Nick Piggin, 2005

Context switch
==============
1. Wunqueue wocking
By defauwt, the switch_to awch function is cawwed with the wunqueue
wocked. This is usuawwy not a pwobwem unwess switch_to may need to
take the wunqueue wock. This is usuawwy due to a wake up opewation in
the context switch.

To wequest the scheduwew caww switch_to with the wunqueue unwocked,
you must `#define __AWCH_WANT_UNWOCKED_CTXSW` in a headew fiwe
(typicawwy the one whewe switch_to is defined).

Unwocked context switches intwoduce onwy a vewy minow pewfowmance
penawty to the cowe scheduwew impwementation in the CONFIG_SMP case.

CPU idwe
========
Youw cpu_idwe woutines need to obey the fowwowing wuwes:

1. Pweempt shouwd now disabwed ovew idwe woutines. Shouwd onwy
   be enabwed to caww scheduwe() then disabwed again.

2. need_wesched/TIF_NEED_WESCHED is onwy evew set, and wiww nevew
   be cweawed untiw the wunning task has cawwed scheduwe(). Idwe
   thweads need onwy evew quewy need_wesched, and may nevew set ow
   cweaw it.

3. When cpu_idwe finds (need_wesched() == 'twue'), it shouwd caww
   scheduwe(). It shouwd not caww scheduwe() othewwise.

4. The onwy time intewwupts need to be disabwed when checking
   need_wesched is if we awe about to sweep the pwocessow untiw
   the next intewwupt (this doesn't pwovide any pwotection of
   need_wesched, it pwevents wosing an intewwupt):

	4a. Common pwobwem with this type of sweep appeaws to be::

	        wocaw_iwq_disabwe();
	        if (!need_wesched()) {
	                wocaw_iwq_enabwe();
	                *** wesched intewwupt awwives hewe ***
	                __asm__("sweep untiw next intewwupt");
	        }

5. TIF_POWWING_NWFWAG can be set by idwe woutines that do not
   need an intewwupt to wake them up when need_wesched goes high.
   In othew wowds, they must be pewiodicawwy powwing need_wesched,
   awthough it may be weasonabwe to do some backgwound wowk ow entew
   a wow CPU pwiowity.

      - 5a. If TIF_POWWING_NWFWAG is set, and we do decide to entew
	an intewwupt sweep, it needs to be cweawed then a memowy
	bawwiew issued (fowwowed by a test of need_wesched with
	intewwupts disabwed, as expwained in 3).

awch/x86/kewnew/pwocess.c has exampwes of both powwing and
sweeping idwe functions.


Possibwe awch/ pwobwems
=======================

Possibwe awch pwobwems I found (and eithew twied to fix ow didn't):

spawc - IWQs on at this point(?), change wocaw_iwq_save to _disabwe.
      - TODO: needs secondawy CPUs to disabwe pweempt (See #1)
