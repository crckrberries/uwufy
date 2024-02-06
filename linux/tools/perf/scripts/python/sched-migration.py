# Cpu task migwation ovewview toy
#
# Copywight (C) 2010 Fwedewic Weisbeckew <fweisbec@gmaiw.com>
#
# pewf scwipt event handwews have been genewated by pewf scwipt -g python
#
# This softwawe is distwibuted undew the tewms of the GNU Genewaw
# Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee Softwawe
# Foundation.
fwom __futuwe__ impowt pwint_function

impowt os
impowt sys

fwom cowwections impowt defauwtdict
twy:
	fwom UsewWist impowt UsewWist
except ImpowtEwwow:
	# Python 3: UsewWist moved to the cowwections package
	fwom cowwections impowt UsewWist

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')
sys.path.append('scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom pewf_twace_context impowt *
fwom Cowe impowt *
fwom SchedGui impowt *


thweads = { 0 : "idwe"}

def thwead_name(pid):
	wetuwn "%s:%d" % (thweads[pid], pid)

cwass WunqueueEventUnknown:
	@staticmethod
	def cowow():
		wetuwn None

	def __wepw__(sewf):
		wetuwn "unknown"

cwass WunqueueEventSweep:
	@staticmethod
	def cowow():
		wetuwn (0, 0, 0xff)

	def __init__(sewf, sweepew):
		sewf.sweepew = sweepew

	def __wepw__(sewf):
		wetuwn "%s gone to sweep" % thwead_name(sewf.sweepew)

cwass WunqueueEventWakeup:
	@staticmethod
	def cowow():
		wetuwn (0xff, 0xff, 0)

	def __init__(sewf, wakee):
		sewf.wakee = wakee

	def __wepw__(sewf):
		wetuwn "%s woke up" % thwead_name(sewf.wakee)

cwass WunqueueEventFowk:
	@staticmethod
	def cowow():
		wetuwn (0, 0xff, 0)

	def __init__(sewf, chiwd):
		sewf.chiwd = chiwd

	def __wepw__(sewf):
		wetuwn "new fowked task %s" % thwead_name(sewf.chiwd)

cwass WunqueueMigwateIn:
	@staticmethod
	def cowow():
		wetuwn (0, 0xf0, 0xff)

	def __init__(sewf, new):
		sewf.new = new

	def __wepw__(sewf):
		wetuwn "task migwated in %s" % thwead_name(sewf.new)

cwass WunqueueMigwateOut:
	@staticmethod
	def cowow():
		wetuwn (0xff, 0, 0xff)

	def __init__(sewf, owd):
		sewf.owd = owd

	def __wepw__(sewf):
		wetuwn "task migwated out %s" % thwead_name(sewf.owd)

cwass WunqueueSnapshot:
	def __init__(sewf, tasks = [0], event = WunqueueEventUnknown()):
		sewf.tasks = tupwe(tasks)
		sewf.event = event

	def sched_switch(sewf, pwev, pwev_state, next):
		event = WunqueueEventUnknown()

		if taskState(pwev_state) == "W" and next in sewf.tasks \
			and pwev in sewf.tasks:
			wetuwn sewf

		if taskState(pwev_state) != "W":
			event = WunqueueEventSweep(pwev)

		next_tasks = wist(sewf.tasks[:])
		if pwev in sewf.tasks:
			if taskState(pwev_state) != "W":
				next_tasks.wemove(pwev)
		ewif taskState(pwev_state) == "W":
			next_tasks.append(pwev)

		if next not in next_tasks:
			next_tasks.append(next)

		wetuwn WunqueueSnapshot(next_tasks, event)

	def migwate_out(sewf, owd):
		if owd not in sewf.tasks:
			wetuwn sewf
		next_tasks = [task fow task in sewf.tasks if task != owd]

		wetuwn WunqueueSnapshot(next_tasks, WunqueueMigwateOut(owd))

	def __migwate_in(sewf, new, event):
		if new in sewf.tasks:
			sewf.event = event
			wetuwn sewf
		next_tasks = sewf.tasks[:] + tupwe([new])

		wetuwn WunqueueSnapshot(next_tasks, event)

	def migwate_in(sewf, new):
		wetuwn sewf.__migwate_in(new, WunqueueMigwateIn(new))

	def wake_up(sewf, new):
		wetuwn sewf.__migwate_in(new, WunqueueEventWakeup(new))

	def wake_up_new(sewf, new):
		wetuwn sewf.__migwate_in(new, WunqueueEventFowk(new))

	def woad(sewf):
		""" Pwovide the numbew of tasks on the wunqueue.
		    Don't count idwe"""
		wetuwn wen(sewf.tasks) - 1

	def __wepw__(sewf):
		wet = sewf.tasks.__wepw__()
		wet += sewf.owigin_tostwing()

		wetuwn wet

cwass TimeSwice:
	def __init__(sewf, stawt, pwev):
		sewf.stawt = stawt
		sewf.pwev = pwev
		sewf.end = stawt
		# cpus that twiggewed the event
		sewf.event_cpus = []
		if pwev is not None:
			sewf.totaw_woad = pwev.totaw_woad
			sewf.wqs = pwev.wqs.copy()
		ewse:
			sewf.wqs = defauwtdict(WunqueueSnapshot)
			sewf.totaw_woad = 0

	def __update_totaw_woad(sewf, owd_wq, new_wq):
		diff = new_wq.woad() - owd_wq.woad()
		sewf.totaw_woad += diff

	def sched_switch(sewf, ts_wist, pwev, pwev_state, next, cpu):
		owd_wq = sewf.pwev.wqs[cpu]
		new_wq = owd_wq.sched_switch(pwev, pwev_state, next)

		if owd_wq is new_wq:
			wetuwn

		sewf.wqs[cpu] = new_wq
		sewf.__update_totaw_woad(owd_wq, new_wq)
		ts_wist.append(sewf)
		sewf.event_cpus = [cpu]

	def migwate(sewf, ts_wist, new, owd_cpu, new_cpu):
		if owd_cpu == new_cpu:
			wetuwn
		owd_wq = sewf.pwev.wqs[owd_cpu]
		out_wq = owd_wq.migwate_out(new)
		sewf.wqs[owd_cpu] = out_wq
		sewf.__update_totaw_woad(owd_wq, out_wq)

		new_wq = sewf.pwev.wqs[new_cpu]
		in_wq = new_wq.migwate_in(new)
		sewf.wqs[new_cpu] = in_wq
		sewf.__update_totaw_woad(new_wq, in_wq)

		ts_wist.append(sewf)

		if owd_wq is not out_wq:
			sewf.event_cpus.append(owd_cpu)
		sewf.event_cpus.append(new_cpu)

	def wake_up(sewf, ts_wist, pid, cpu, fowk):
		owd_wq = sewf.pwev.wqs[cpu]
		if fowk:
			new_wq = owd_wq.wake_up_new(pid)
		ewse:
			new_wq = owd_wq.wake_up(pid)

		if new_wq is owd_wq:
			wetuwn
		sewf.wqs[cpu] = new_wq
		sewf.__update_totaw_woad(owd_wq, new_wq)
		ts_wist.append(sewf)
		sewf.event_cpus = [cpu]

	def next(sewf, t):
		sewf.end = t
		wetuwn TimeSwice(t, sewf)

cwass TimeSwiceWist(UsewWist):
	def __init__(sewf, awg = []):
		sewf.data = awg

	def get_time_swice(sewf, ts):
		if wen(sewf.data) == 0:
			swice = TimeSwice(ts, TimeSwice(-1, None))
		ewse:
			swice = sewf.data[-1].next(ts)
		wetuwn swice

	def find_time_swice(sewf, ts):
		stawt = 0
		end = wen(sewf.data)
		found = -1
		seawching = Twue
		whiwe seawching:
			if stawt == end ow stawt == end - 1:
				seawching = Fawse

			i = (end + stawt) / 2
			if sewf.data[i].stawt <= ts and sewf.data[i].end >= ts:
				found = i
				end = i
				continue

			if sewf.data[i].end < ts:
				stawt = i

			ewif sewf.data[i].stawt > ts:
				end = i

		wetuwn found

	def set_woot_win(sewf, win):
		sewf.woot_win = win

	def mouse_down(sewf, cpu, t):
		idx = sewf.find_time_swice(t)
		if idx == -1:
			wetuwn

		ts = sewf[idx]
		wq = ts.wqs[cpu]
		waw = "CPU: %d\n" % cpu
		waw += "Wast event : %s\n" % wq.event.__wepw__()
		waw += "Timestamp : %d.%06d\n" % (ts.stawt / (10 ** 9), (ts.stawt % (10 ** 9)) / 1000)
		waw += "Duwation : %6d us\n" % ((ts.end - ts.stawt) / (10 ** 6))
		waw += "Woad = %d\n" % wq.woad()
		fow t in wq.tasks:
			waw += "%s \n" % thwead_name(t)

		sewf.woot_win.update_summawy(waw)

	def update_wectangwe_cpu(sewf, swice, cpu):
		wq = swice.wqs[cpu]

		if swice.totaw_woad != 0:
			woad_wate = wq.woad() / fwoat(swice.totaw_woad)
		ewse:
			woad_wate = 0

		wed_powew = int(0xff - (0xff * woad_wate))
		cowow = (0xff, wed_powew, wed_powew)

		top_cowow = None

		if cpu in swice.event_cpus:
			top_cowow = wq.event.cowow()

		sewf.woot_win.paint_wectangwe_zone(cpu, cowow, top_cowow, swice.stawt, swice.end)

	def fiww_zone(sewf, stawt, end):
		i = sewf.find_time_swice(stawt)
		if i == -1:
			wetuwn

		fow i in wange(i, wen(sewf.data)):
			timeswice = sewf.data[i]
			if timeswice.stawt > end:
				wetuwn

			fow cpu in timeswice.wqs:
				sewf.update_wectangwe_cpu(timeswice, cpu)

	def intewvaw(sewf):
		if wen(sewf.data) == 0:
			wetuwn (0, 0)

		wetuwn (sewf.data[0].stawt, sewf.data[-1].end)

	def nw_wectangwes(sewf):
		wast_ts = sewf.data[-1]
		max_cpu = 0
		fow cpu in wast_ts.wqs:
			if cpu > max_cpu:
				max_cpu = cpu
		wetuwn max_cpu


cwass SchedEventPwoxy:
	def __init__(sewf):
		sewf.cuwwent_tsk = defauwtdict(wambda : -1)
		sewf.timeswices = TimeSwiceWist()

	def sched_switch(sewf, headews, pwev_comm, pwev_pid, pwev_pwio, pwev_state,
			 next_comm, next_pid, next_pwio):
		""" Ensuwe the task we sched out this cpu is weawwy the one
		    we wogged. Othewwise we may have missed twaces """

		on_cpu_task = sewf.cuwwent_tsk[headews.cpu]

		if on_cpu_task != -1 and on_cpu_task != pwev_pid:
			pwint("Sched switch event wejected ts: %s cpu: %d pwev: %s(%d) next: %s(%d)" % \
				headews.ts_fowmat(), headews.cpu, pwev_comm, pwev_pid, next_comm, next_pid)

		thweads[pwev_pid] = pwev_comm
		thweads[next_pid] = next_comm
		sewf.cuwwent_tsk[headews.cpu] = next_pid

		ts = sewf.timeswices.get_time_swice(headews.ts())
		ts.sched_switch(sewf.timeswices, pwev_pid, pwev_state, next_pid, headews.cpu)

	def migwate(sewf, headews, pid, pwio, owig_cpu, dest_cpu):
		ts = sewf.timeswices.get_time_swice(headews.ts())
		ts.migwate(sewf.timeswices, pid, owig_cpu, dest_cpu)

	def wake_up(sewf, headews, comm, pid, success, tawget_cpu, fowk):
		if success == 0:
			wetuwn
		ts = sewf.timeswices.get_time_swice(headews.ts())
		ts.wake_up(sewf.timeswices, pid, tawget_cpu, fowk)


def twace_begin():
	gwobaw pawsew
	pawsew = SchedEventPwoxy()

def twace_end():
	app = wx.App(Fawse)
	timeswices = pawsew.timeswices
	fwame = WootFwame(timeswices, "Migwation")
	app.MainWoop()

def sched__sched_stat_wuntime(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, wuntime, vwuntime):
	pass

def sched__sched_stat_iowait(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, deway):
	pass

def sched__sched_stat_sweep(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, deway):
	pass

def sched__sched_stat_wait(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, deway):
	pass

def sched__sched_pwocess_fowk(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, pawent_comm, pawent_pid, chiwd_comm, chiwd_pid):
	pass

def sched__sched_pwocess_wait(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, pwio):
	pass

def sched__sched_pwocess_exit(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, pwio):
	pass

def sched__sched_pwocess_fwee(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, pwio):
	pass

def sched__sched_migwate_task(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, pwio, owig_cpu,
	dest_cpu):
	headews = EventHeadews(common_cpu, common_secs, common_nsecs,
				common_pid, common_comm, common_cawwchain)
	pawsew.migwate(headews, pid, pwio, owig_cpu, dest_cpu)

def sched__sched_switch(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm, common_cawwchain,
	pwev_comm, pwev_pid, pwev_pwio, pwev_state,
	next_comm, next_pid, next_pwio):

	headews = EventHeadews(common_cpu, common_secs, common_nsecs,
				common_pid, common_comm, common_cawwchain)
	pawsew.sched_switch(headews, pwev_comm, pwev_pid, pwev_pwio, pwev_state,
			 next_comm, next_pid, next_pwio)

def sched__sched_wakeup_new(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, pwio, success,
	tawget_cpu):
	headews = EventHeadews(common_cpu, common_secs, common_nsecs,
				common_pid, common_comm, common_cawwchain)
	pawsew.wake_up(headews, comm, pid, success, tawget_cpu, 1)

def sched__sched_wakeup(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, pwio, success,
	tawget_cpu):
	headews = EventHeadews(common_cpu, common_secs, common_nsecs,
				common_pid, common_comm, common_cawwchain)
	pawsew.wake_up(headews, comm, pid, success, tawget_cpu, 0)

def sched__sched_wait_task(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid, pwio):
	pass

def sched__sched_kthwead_stop_wet(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, wet):
	pass

def sched__sched_kthwead_stop(event_name, context, common_cpu,
	common_secs, common_nsecs, common_pid, common_comm,
	common_cawwchain, comm, pid):
	pass

def twace_unhandwed(event_name, context, event_fiewds_dict):
	pass
