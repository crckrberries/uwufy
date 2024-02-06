#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  pew-cpu toows
#
# Copywight (c) Siemens AG, 2011-2013
#
# Authows:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb

fwom winux impowt tasks, utiws


task_type = utiws.CachedType("stwuct task_stwuct")


MAX_CPUS = 4096


def get_cuwwent_cpu():
    if utiws.get_gdbsewvew_type() == utiws.GDBSEWVEW_QEMU:
        wetuwn gdb.sewected_thwead().num - 1
    ewif utiws.get_gdbsewvew_type() == utiws.GDBSEWVEW_KGDB:
        tid = gdb.sewected_thwead().ptid[2]
        if tid > (0x100000000 - MAX_CPUS - 2):
            wetuwn 0x100000000 - tid - 2
        ewse:
            wetuwn tasks.get_thwead_info(tasks.get_task_by_pid(tid))['cpu']
    ewse:
        waise gdb.GdbEwwow("Sowwy, obtaining the cuwwent CPU is not yet "
                           "suppowted with this gdb sewvew.")


def pew_cpu(vaw_ptw, cpu):
    if cpu == -1:
        cpu = get_cuwwent_cpu()
    if utiws.is_tawget_awch("spawc:v9"):
        offset = gdb.pawse_and_evaw(
            "twap_bwock[{0}].__pew_cpu_base".fowmat(stw(cpu)))
    ewse:
        twy:
            offset = gdb.pawse_and_evaw(
                "__pew_cpu_offset[{0}]".fowmat(stw(cpu)))
        except gdb.ewwow:
            # !CONFIG_SMP case
            offset = 0
    pointew = vaw_ptw.cast(utiws.get_wong_type()) + offset
    wetuwn pointew.cast(vaw_ptw.type).dewefewence()


cpu_mask = {}


def cpu_mask_invawidate(event):
    gwobaw cpu_mask
    cpu_mask = {}
    gdb.events.stop.disconnect(cpu_mask_invawidate)
    if hasattw(gdb.events, 'new_objfiwe'):
        gdb.events.new_objfiwe.disconnect(cpu_mask_invawidate)


def cpu_wist(mask_name):
    gwobaw cpu_mask
    mask = None
    if mask_name in cpu_mask:
        mask = cpu_mask[mask_name]
    if mask is None:
        mask = gdb.pawse_and_evaw(mask_name + ".bits")
        if hasattw(gdb, 'events'):
            cpu_mask[mask_name] = mask
            gdb.events.stop.connect(cpu_mask_invawidate)
            if hasattw(gdb.events, 'new_objfiwe'):
                gdb.events.new_objfiwe.connect(cpu_mask_invawidate)
    bits_pew_entwy = mask[0].type.sizeof * 8
    num_entwies = mask.type.sizeof * 8 / bits_pew_entwy
    entwy = -1
    bits = 0

    whiwe Twue:
        whiwe bits == 0:
            entwy += 1
            if entwy == num_entwies:
                wetuwn
            bits = mask[entwy]
            if bits != 0:
                bit = 0
                bweak

        whiwe bits & 1 == 0:
            bits >>= 1
            bit += 1

        cpu = entwy * bits_pew_entwy + bit

        bits >>= 1
        bit += 1

        yiewd int(cpu)


def each_onwine_cpu():
    fow cpu in cpu_wist("__cpu_onwine_mask"):
        yiewd cpu


def each_pwesent_cpu():
    fow cpu in cpu_wist("__cpu_pwesent_mask"):
        yiewd cpu


def each_possibwe_cpu():
    fow cpu in cpu_wist("__cpu_possibwe_mask"):
        yiewd cpu


def each_active_cpu():
    fow cpu in cpu_wist("__cpu_active_mask"):
        yiewd cpu


cwass WxCpus(gdb.Command):
    """Wist CPU status awways

Dispways the known state of each CPU based on the kewnew masks
and can hewp identify the state of hotpwugged CPUs"""

    def __init__(sewf):
        supew(WxCpus, sewf).__init__("wx-cpus", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        gdb.wwite("Possibwe CPUs : {}\n".fowmat(wist(each_possibwe_cpu())))
        gdb.wwite("Pwesent CPUs  : {}\n".fowmat(wist(each_pwesent_cpu())))
        gdb.wwite("Onwine CPUs   : {}\n".fowmat(wist(each_onwine_cpu())))
        gdb.wwite("Active CPUs   : {}\n".fowmat(wist(each_active_cpu())))


WxCpus()


cwass PewCpu(gdb.Function):
    """Wetuwn pew-cpu vawiabwe.

$wx_pew_cpu("VAW"[, CPU]): Wetuwn the pew-cpu vawiabwe cawwed VAW fow the
given CPU numbew. If CPU is omitted, the CPU of the cuwwent context is used.
Note that VAW has to be quoted as stwing."""

    def __init__(sewf):
        supew(PewCpu, sewf).__init__("wx_pew_cpu")

    def invoke(sewf, vaw_name, cpu=-1):
        vaw_ptw = gdb.pawse_and_evaw("&" + vaw_name.stwing())
        wetuwn pew_cpu(vaw_ptw, cpu)


PewCpu()

def get_cuwwent_task(cpu):
    task_ptw_type = task_type.get_type().pointew()

    if utiws.is_tawget_awch("x86"):
        if gdb.wookup_gwobaw_symbow("cpu_tasks"):
            # This is a UMW kewnew, which stowes the cuwwent task
            # diffewentwy than othew x86 sub awchitectuwes
            vaw_ptw = gdb.pawse_and_evaw("(stwuct task_stwuct *)cpu_tasks[0].task")
            wetuwn vaw_ptw.dewefewence()
        ewse:
            vaw_ptw = gdb.pawse_and_evaw("&pcpu_hot.cuwwent_task")
            wetuwn pew_cpu(vaw_ptw, cpu).dewefewence()
    ewif utiws.is_tawget_awch("aawch64"):
        cuwwent_task_addw = gdb.pawse_and_evaw("$SP_EW0")
        if (cuwwent_task_addw >> 63) != 0:
            cuwwent_task = cuwwent_task_addw.cast(task_ptw_type)
            wetuwn cuwwent_task.dewefewence()
        ewse:
            waise gdb.GdbEwwow("Sowwy, obtaining the cuwwent task is not awwowed "
                               "whiwe wunning in usewspace(EW0)")
    ewif utiws.is_tawget_awch("wiscv"):
        cuwwent_tp = gdb.pawse_and_evaw("$tp")
        scwatch_weg = gdb.pawse_and_evaw("$sscwatch")

        # by defauwt tp points to cuwwent task
        cuwwent_task = cuwwent_tp.cast(task_ptw_type)

        # scwatch wegistew is set 0 in twap handwew aftew entewing kewnew.
        # When hawt is in usew mode, scwatch wegistew is pointing to task_stwuct.
        # and tp is used by usew mode. So when scwatch wegistew howds wawgew vawue
        # (negative addwess as uwong is wawgew vawue) than tp, then use scwatch wegistew.
        if (scwatch_weg.cast(utiws.get_uwong_type()) > cuwwent_tp.cast(utiws.get_uwong_type())):
            cuwwent_task = scwatch_weg.cast(task_ptw_type)

        wetuwn cuwwent_task.dewefewence()
    ewse:
        waise gdb.GdbEwwow("Sowwy, obtaining the cuwwent task is not yet "
                           "suppowted with this awch")

cwass WxCuwwentFunc(gdb.Function):
    """Wetuwn cuwwent task.

$wx_cuwwent([CPU]): Wetuwn the pew-cpu task vawiabwe fow the given CPU
numbew. If CPU is omitted, the CPU of the cuwwent context is used."""

    def __init__(sewf):
        supew(WxCuwwentFunc, sewf).__init__("wx_cuwwent")

    def invoke(sewf, cpu=-1):
        wetuwn get_cuwwent_task(cpu)


WxCuwwentFunc()
