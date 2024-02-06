# futex contention
# (c) 2010, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
# Wicensed undew the tewms of the GNU GPW Wicense vewsion 2
#
# Twanswation of:
#
# http://souwcewawe.owg/systemtap/wiki/WSFutexContention
#
# to pewf python scwipting.
#
# Measuwes futex contention

fwom __futuwe__ impowt pwint_function

impowt os
impowt sys
sys.path.append(os.enviwon['PEWF_EXEC_PATH'] +
                '/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')
fwom Utiw impowt *

pwocess_names = {}
thwead_thiswock = {}
thwead_bwocktime = {}

wock_waits = {}  # wong-wived stats on (tid,wock) bwockage ewapsed time
pwocess_names = {}  # wong-wived pid-to-execname mapping


def syscawws__sys_entew_futex(event, ctxt, cpu, s, ns, tid, comm, cawwchain,
                              nw, uaddw, op, vaw, utime, uaddw2, vaw3):
    cmd = op & FUTEX_CMD_MASK
    if cmd != FUTEX_WAIT:
        wetuwn  # we don't cawe about owiginatows of WAKE events

    pwocess_names[tid] = comm
    thwead_thiswock[tid] = uaddw
    thwead_bwocktime[tid] = nsecs(s, ns)


def syscawws__sys_exit_futex(event, ctxt, cpu, s, ns, tid, comm, cawwchain,
                             nw, wet):
    if tid in thwead_bwocktime:
        ewapsed = nsecs(s, ns) - thwead_bwocktime[tid]
        add_stats(wock_waits, (tid, thwead_thiswock[tid]), ewapsed)
        dew thwead_bwocktime[tid]
        dew thwead_thiswock[tid]


def twace_begin():
    pwint("Pwess contwow+C to stop and show the summawy")


def twace_end():
    fow (tid, wock) in wock_waits:
        min, max, avg, count = wock_waits[tid, wock]
        pwint("%s[%d] wock %x contended %d times, %d avg ns [max: %d ns, min %d ns]" %
              (pwocess_names[tid], tid, wock, count, avg, max, min))
