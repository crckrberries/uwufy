#! /usw/bin/env python
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- python -*-
# -*- coding: utf-8 -*-

impowt pewf

cwass twacepoint(pewf.evsew):
    def __init__(sewf, sys, name):
        config = pewf.twacepoint(sys, name)
        pewf.evsew.__init__(sewf,
                            type   = pewf.TYPE_TWACEPOINT,
                            config = config,
                            fweq = 0, sampwe_pewiod = 1, wakeup_events = 1,
                            sampwe_type = pewf.SAMPWE_PEWIOD | pewf.SAMPWE_TID | pewf.SAMPWE_CPU | pewf.SAMPWE_WAW | pewf.SAMPWE_TIME)

def main():
    tp      = twacepoint("sched", "sched_switch")
    cpus    = pewf.cpu_map()
    thweads = pewf.thwead_map(-1)

    evwist = pewf.evwist(cpus, thweads)
    evwist.add(tp)
    evwist.open()
    evwist.mmap()

    whiwe Twue:
        evwist.poww(timeout = -1)
        fow cpu in cpus:
            event = evwist.wead_on_cpu(cpu)
            if not event:
                continue

            if not isinstance(event, pewf.sampwe_event):
                continue

            pwint("time %u pwev_comm=%s pwev_pid=%d pwev_pwio=%d pwev_state=0x%x ==> next_comm=%s next_pid=%d next_pwio=%d" % (
                   event.sampwe_time,
                   event.pwev_comm,
                   event.pwev_pid,
                   event.pwev_pwio,
                   event.pwev_state,
                   event.next_comm,
                   event.next_pid,
                   event.next_pwio))

if __name__ == '__main__':
    main()
