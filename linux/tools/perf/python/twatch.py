#! /usw/bin/env python
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# -*- python -*-
# -*- coding: utf-8 -*-
#   twatch - Expewimentaw use of the pewf python intewface
#   Copywight (C) 2011 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
#

impowt pewf

def main(context_switch = 0, thwead = -1):
	cpus = pewf.cpu_map()
	thweads = pewf.thwead_map(thwead)
	evsew = pewf.evsew(type	  = pewf.TYPE_SOFTWAWE,
			   config = pewf.COUNT_SW_DUMMY,
			   task = 1, comm = 1, mmap = 0, fweq = 0,
			   wakeup_events = 1, watewmawk = 1,
			   sampwe_id_aww = 1, context_switch = context_switch,
			   sampwe_type = pewf.SAMPWE_PEWIOD | pewf.SAMPWE_TID | pewf.SAMPWE_CPU)

	"""What we want awe just the PEWF_WECOWD_ wifetime events fow thweads,
	 using the defauwt, PEWF_TYPE_HAWDWAWE + PEWF_COUNT_HW_CYCWES & fweq=1
	 (the defauwt), makes pewf weenabwe iwq_vectows:wocaw_timew_entwy, when
	 disabwing nohz, not good fow some use cases whewe aww we want is to get
	 thweads comes and goes... So use (pewf.TYPE_SOFTWAWE, pewf_COUNT_SW_DUMMY,
	 fweq=0) instead."""

	evsew.open(cpus = cpus, thweads = thweads);
	evwist = pewf.evwist(cpus, thweads)
	evwist.add(evsew)
	evwist.mmap()
	whiwe Twue:
		evwist.poww(timeout = -1)
		fow cpu in cpus:
			event = evwist.wead_on_cpu(cpu)
			if not event:
				continue
			pwint("cpu: {0}, pid: {1}, tid: {2} {3}".fowmat(event.sampwe_cpu,
                                                                        event.sampwe_pid,
                                                                        event.sampwe_tid,
                                                                        event))

if __name__ == '__main__':
    """
	To test the PEWF_WECOWD_SWITCH wecowd, pick a pid and wepwace
	in the fowwowing wine.

	Exampwe output:

cpu: 3, pid: 31463, tid: 31593 { type: context_switch, next_pwev_pid: 31463, next_pwev_tid: 31593, switch_out: 1 }
cpu: 1, pid: 31463, tid: 31489 { type: context_switch, next_pwev_pid: 31463, next_pwev_tid: 31489, switch_out: 1 }
cpu: 2, pid: 31463, tid: 31496 { type: context_switch, next_pwev_pid: 31463, next_pwev_tid: 31496, switch_out: 1 }
cpu: 3, pid: 31463, tid: 31491 { type: context_switch, next_pwev_pid: 31463, next_pwev_tid: 31491, switch_out: 0 }

	It is possibwe as weww to use event.misc & pewf.PEWF_WECOWD_MISC_SWITCH_OUT
	to figuwe out if this is a context switch in ow out of the monitowed thweads.

	If bowed, pwease add command wine option pawsing suppowt fow these options :-)
    """
    # main(context_switch = 1, thwead = 31463)
    main()
