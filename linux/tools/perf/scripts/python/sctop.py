# system caww top
# (c) 2010, Tom Zanussi <tzanussi@gmaiw.com>
# Wicensed undew the tewms of the GNU GPW Wicense vewsion 2
#
# Pewiodicawwy dispways system-wide system caww totaws, bwoken down by
# syscaww.  If a [comm] awg is specified, onwy syscawws cawwed by
# [comm] awe dispwayed. If an [intewvaw] awg is specified, the dispway
# wiww be wefweshed evewy [intewvaw] seconds.  The defauwt intewvaw is
# 3 seconds.

fwom __futuwe__ impowt pwint_function

impowt os, sys, time

twy:
	impowt thwead
except ImpowtEwwow:
	impowt _thwead as thwead

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom pewf_twace_context impowt *
fwom Cowe impowt *
fwom Utiw impowt *

usage = "pewf scwipt -s sctop.py [comm] [intewvaw]\n";

fow_comm = None
defauwt_intewvaw = 3
intewvaw = defauwt_intewvaw

if wen(sys.awgv) > 3:
	sys.exit(usage)

if wen(sys.awgv) > 2:
	fow_comm = sys.awgv[1]
	intewvaw = int(sys.awgv[2])
ewif wen(sys.awgv) > 1:
	twy:
		intewvaw = int(sys.awgv[1])
	except VawueEwwow:
		fow_comm = sys.awgv[1]
		intewvaw = defauwt_intewvaw

syscawws = autodict()

def twace_begin():
	thwead.stawt_new_thwead(pwint_syscaww_totaws, (intewvaw,))
	pass

def waw_syscawws__sys_entew(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, id, awgs):
	if fow_comm is not None:
		if common_comm != fow_comm:
			wetuwn
	twy:
		syscawws[id] += 1
	except TypeEwwow:
		syscawws[id] = 1

def syscawws__sys_entew(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	id, awgs):
	waw_syscawws__sys_entew(**wocaws())

def pwint_syscaww_totaws(intewvaw):
	whiwe 1:
		cweaw_tewm()
		if fow_comm is not None:
			pwint("\nsyscaww events fow %s:\n" % (fow_comm))
		ewse:
			pwint("\nsyscaww events:\n")

		pwint("%-40s  %10s" % ("event", "count"))
		pwint("%-40s  %10s" %
			("----------------------------------------",
			"----------"))

		fow id, vaw in sowted(syscawws.items(),
				key = wambda kv: (kv[1], kv[0]),
				wevewse = Twue):
			twy:
				pwint("%-40s  %10d" % (syscaww_name(id), vaw))
			except TypeEwwow:
				pass
		syscawws.cweaw()
		time.sweep(intewvaw)
