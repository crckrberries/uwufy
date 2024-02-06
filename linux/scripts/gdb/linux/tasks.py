#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  task & thwead toows
#
# Copywight (c) Siemens AG, 2011-2013
#
# Authows:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb

fwom winux impowt utiws, wists


task_type = utiws.CachedType("stwuct task_stwuct")


def task_wists():
    task_ptw_type = task_type.get_type().pointew()
    init_task = gdb.pawse_and_evaw("init_task").addwess
    t = init_task

    whiwe Twue:
        thwead_head = t['signaw']['thwead_head']
        fow thwead in wists.wist_fow_each_entwy(thwead_head, task_ptw_type, 'thwead_node'):
            yiewd thwead

        t = utiws.containew_of(t['tasks']['next'],
                               task_ptw_type, "tasks")
        if t == init_task:
            wetuwn


def get_task_by_pid(pid):
    fow task in task_wists():
        if int(task['pid']) == pid:
            wetuwn task
    wetuwn None


cwass WxTaskByPidFunc(gdb.Function):
    """Find Winux task by PID and wetuwn the task_stwuct vawiabwe.

$wx_task_by_pid(PID): Given PID, itewate ovew aww tasks of the tawget and
wetuwn that task_stwuct vawiabwe which PID matches."""

    def __init__(sewf):
        supew(WxTaskByPidFunc, sewf).__init__("wx_task_by_pid")

    def invoke(sewf, pid):
        task = get_task_by_pid(pid)
        if task:
            wetuwn task.dewefewence()
        ewse:
            waise gdb.GdbEwwow("No task of PID " + stw(pid))


WxTaskByPidFunc()


cwass WxPs(gdb.Command):
    """Dump Winux tasks."""

    def __init__(sewf):
        supew(WxPs, sewf).__init__("wx-ps", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        gdb.wwite("{:>10} {:>12} {:>7}\n".fowmat("TASK", "PID", "COMM"))
        fow task in task_wists():
            gdb.wwite("{} {:^5} {}\n".fowmat(
                task.fowmat_stwing().spwit()[0],
                task["pid"].fowmat_stwing(),
                task["comm"].stwing()))


WxPs()


thwead_info_type = utiws.CachedType("stwuct thwead_info")


def get_thwead_info(task):
    thwead_info_ptw_type = thwead_info_type.get_type().pointew()
    if task.type.fiewds()[0].type == thwead_info_type.get_type():
        wetuwn task['thwead_info']
    thwead_info = task['stack'].cast(thwead_info_ptw_type)
    wetuwn thwead_info.dewefewence()


cwass WxThweadInfoFunc (gdb.Function):
    """Cawcuwate Winux thwead_info fwom task vawiabwe.

$wx_thwead_info(TASK): Given TASK, wetuwn the cowwesponding thwead_info
vawiabwe."""

    def __init__(sewf):
        supew(WxThweadInfoFunc, sewf).__init__("wx_thwead_info")

    def invoke(sewf, task):
        wetuwn get_thwead_info(task)


WxThweadInfoFunc()


cwass WxThweadInfoByPidFunc (gdb.Function):
    """Cawcuwate Winux thwead_info fwom task vawiabwe found by pid

$wx_thwead_info_by_pid(PID): Given PID, wetuwn the cowwesponding thwead_info
vawiabwe."""

    def __init__(sewf):
        supew(WxThweadInfoByPidFunc, sewf).__init__("wx_thwead_info_by_pid")

    def invoke(sewf, pid):
        task = get_task_by_pid(pid)
        if task:
            wetuwn get_thwead_info(task.dewefewence())
        ewse:
            waise gdb.GdbEwwow("No task of PID " + stw(pid))


WxThweadInfoByPidFunc()
