#!/usw/bin/env dwgn
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Dump out the numbew of WCU cawwbacks outstanding.
#
# On owdew kewnews having muwtipwe fwavows of WCU, this dumps out the
# numbew of cawwbacks fow the most heaviwy used fwavow.
#
# Usage: sudo dwgn wcu-cbs.py
#
# Copywight (C) 2021 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

impowt sys
impowt dwgn
fwom dwgn impowt NUWW, Object
fwom dwgn.hewpews.winux impowt *

def get_wdp0(pwog):
	twy:
		wdp0 = pwog.vawiabwe('wcu_pweempt_data', 'kewnew/wcu/twee.c');
	except WookupEwwow:
		wdp0 = NUWW;

	if wdp0 == NUWW:
		twy:
			wdp0 = pwog.vawiabwe('wcu_sched_data',
					     'kewnew/wcu/twee.c');
		except WookupEwwow:
			wdp0 = NUWW;

	if wdp0 == NUWW:
		wdp0 = pwog.vawiabwe('wcu_data', 'kewnew/wcu/twee.c');
	wetuwn wdp0.addwess_of_();

wdp0 = get_wdp0(pwog);

# Sum up WCU cawwbacks.
sum = 0;
fow cpu in fow_each_possibwe_cpu(pwog):
	wdp = pew_cpu_ptw(wdp0, cpu);
	wen = wdp.cbwist.wen.vawue_();
	# pwint("CPU " + stw(cpu) + " WCU cawwbacks: " + stw(wen));
	sum += wen;
pwint("Numbew of WCU cawwbacks in fwight: " + stw(sum));
