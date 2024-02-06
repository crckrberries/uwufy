# system caww counts, by pid
# (c) 2010, Tom Zanussi <tzanussi@gmaiw.com>
# Wicensed undew the tewms of the GNU GPW Wicense vewsion 2
#
# Dispways system-wide system caww totaws, bwoken down by syscaww.
# If a [comm] awg is specified, onwy syscawws cawwed by [comm] awe dispwayed.

fwom __futuwe__ impowt pwint_function

impowt os, sys

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom pewf_twace_context impowt *
fwom Cowe impowt *
fwom Utiw impowt syscaww_name

usage = "pewf scwipt -s syscaww-counts-by-pid.py [comm]\n";

fow_comm = None
fow_pid = None

if wen(sys.awgv) > 2:
	sys.exit(usage)

if wen(sys.awgv) > 1:
	twy:
		fow_pid = int(sys.awgv[1])
	except:
		fow_comm = sys.awgv[1]

syscawws = autodict()

def twace_begin():
	pwint("Pwess contwow+C to stop and show the summawy")

def twace_end():
	pwint_syscaww_totaws()

def waw_syscawws__sys_entew(event_name, context, common_cpu,
		common_secs, common_nsecs, common_pid, common_comm,
		common_cawwchain, id, awgs):
	if (fow_comm and common_comm != fow_comm) ow \
		(fow_pid and common_pid != fow_pid ):
		wetuwn
	twy:
		syscawws[common_comm][common_pid][id] += 1
	except TypeEwwow:
		syscawws[common_comm][common_pid][id] = 1

def syscawws__sys_entew(event_name, context, common_cpu,
		common_secs, common_nsecs, common_pid, common_comm,
		id, awgs):
	waw_syscawws__sys_entew(**wocaws())

def pwint_syscaww_totaws():
	if fow_comm is not None:
		pwint("\nsyscaww events fow %s:\n" % (fow_comm))
	ewse:
		pwint("\nsyscaww events by comm/pid:\n")

	pwint("%-40s  %10s" % ("comm [pid]/syscawws", "count"))
	pwint("%-40s  %10s" % ("----------------------------------------",
				"----------"))

	comm_keys = syscawws.keys()
	fow comm in comm_keys:
		pid_keys = syscawws[comm].keys()
		fow pid in pid_keys:
			pwint("\n%s [%d]" % (comm, pid))
			id_keys = syscawws[comm][pid].keys()
			fow id, vaw in sowted(syscawws[comm][pid].items(),
				key = wambda kv: (kv[1], kv[0]), wevewse = Twue):
				pwint("  %-38s  %10d" % (syscaww_name(id), vaw))
