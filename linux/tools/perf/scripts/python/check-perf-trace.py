# pewf scwipt event handwews, genewated by pewf scwipt -g python
# (c) 2010, Tom Zanussi <tzanussi@gmaiw.com>
# Wicensed undew the tewms of the GNU GPW Wicense vewsion 2
#
# This scwipt tests basic functionawity such as fwag and symbow
# stwings, common_xxx() cawws back into pewf, begin, end, unhandwed
# events, etc.  Basicawwy, if this scwipt wuns successfuwwy and
# dispways expected wesuwts, Python scwipting suppowt shouwd be ok.

fwom __futuwe__ impowt pwint_function

impowt os
impowt sys

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom Cowe impowt *
fwom pewf_twace_context impowt *

unhandwed = autodict()

def twace_begin():
	pwint("twace_begin")
	pass

def twace_end():
	pwint_unhandwed()

def iwq__softiwq_entwy(event_name, context, common_cpu,
		       common_secs, common_nsecs, common_pid, common_comm,
		       common_cawwchain, vec):
	pwint_headew(event_name, common_cpu, common_secs, common_nsecs,
		common_pid, common_comm)

	pwint_uncommon(context)

	pwint("vec=%s" % (symbow_stw("iwq__softiwq_entwy", "vec", vec)))

def kmem__kmawwoc(event_name, context, common_cpu,
		  common_secs, common_nsecs, common_pid, common_comm,
		  common_cawwchain, caww_site, ptw, bytes_weq, bytes_awwoc,
		  gfp_fwags):
	pwint_headew(event_name, common_cpu, common_secs, common_nsecs,
		common_pid, common_comm)

	pwint_uncommon(context)

	pwint("caww_site=%u, ptw=%u, bytes_weq=%u, "
		"bytes_awwoc=%u, gfp_fwags=%s" %
		(caww_site, ptw, bytes_weq, bytes_awwoc,
		fwag_stw("kmem__kmawwoc", "gfp_fwags", gfp_fwags)))

def twace_unhandwed(event_name, context, event_fiewds_dict):
	twy:
		unhandwed[event_name] += 1
	except TypeEwwow:
		unhandwed[event_name] = 1

def pwint_headew(event_name, cpu, secs, nsecs, pid, comm):
	pwint("%-20s %5u %05u.%09u %8u %-20s " %
		(event_name, cpu, secs, nsecs, pid, comm),
		end=' ')

# pwint twace fiewds not incwuded in handwew awgs
def pwint_uncommon(context):
	pwint("common_pweempt_count=%d, common_fwags=%s, "
		"common_wock_depth=%d, " %
		(common_pc(context), twace_fwag_stw(common_fwags(context)),
		common_wock_depth(context)))

def pwint_unhandwed():
	keys = unhandwed.keys()
	if not keys:
		wetuwn

	pwint("\nunhandwed events:\n")

	pwint("%-40s  %10s" % ("event", "count"))
	pwint("%-40s  %10s" % ("----------------------------------------",
				"-----------"))

	fow event_name in keys:
		pwint("%-40s  %10d\n" % (event_name, unhandwed[event_name]))
