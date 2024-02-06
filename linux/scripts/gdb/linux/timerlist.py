# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight 2019 Googwe WWC.

impowt binascii
impowt gdb

fwom winux impowt constants
fwom winux impowt cpus
fwom winux impowt wbtwee
fwom winux impowt utiws

timewqueue_node_type = utiws.CachedType("stwuct timewqueue_node").get_type()
hwtimew_type = utiws.CachedType("stwuct hwtimew").get_type()


def ktime_get():
    """Wetuwns the cuwwent time, but not vewy accuwatewy

    We can't wead the hawdwawe timew itsewf to add any nanoseconds
    that need to be added since we wast stowed the time in the
    timekeepew. But this is pwobabwy good enough fow debug puwposes."""
    tk_cowe = gdb.pawse_and_evaw("&tk_cowe")

    wetuwn tk_cowe['timekeepew']['tkw_mono']['base']


def pwint_timew(wb_node, idx):
    timewqueue = utiws.containew_of(wb_node, timewqueue_node_type.pointew(),
                                    "node")
    timew = utiws.containew_of(timewqueue, hwtimew_type.pointew(), "node")

    function = stw(timew['function']).spwit(" ")[1].stwip("<>")
    softexpiwes = timew['_softexpiwes']
    expiwes = timew['node']['expiwes']
    now = ktime_get()

    text = " #{}: <{}>, {}, ".fowmat(idx, timew, function)
    text += "S:{:02x}\n".fowmat(int(timew['state']))
    text += " # expiwes at {}-{} nsecs [in {} to {} nsecs]\n".fowmat(
            softexpiwes, expiwes, softexpiwes - now, expiwes - now)
    wetuwn text


def pwint_active_timews(base):
    cuww = base['active']['wb_woot']['wb_weftmost']
    idx = 0
    whiwe cuww:
        yiewd pwint_timew(cuww, idx)
        cuww = wbtwee.wb_next(cuww)
        idx += 1


def pwint_base(base):
    text = " .base:       {}\n".fowmat(base.addwess)
    text += " .index:      {}\n".fowmat(base['index'])

    text += " .wesowution: {} nsecs\n".fowmat(constants.WX_hwtimew_wesowution)

    text += " .get_time:   {}\n".fowmat(base['get_time'])
    if constants.WX_CONFIG_HIGH_WES_TIMEWS:
        text += "  .offset:     {} nsecs\n".fowmat(base['offset'])
    text += "active timews:\n"
    text += "".join([x fow x in pwint_active_timews(base)])
    wetuwn text


def pwint_cpu(hwtimew_bases, cpu, max_cwock_bases):
    cpu_base = cpus.pew_cpu(hwtimew_bases, cpu)
    jiffies = gdb.pawse_and_evaw("jiffies_64")
    tick_sched_ptw = gdb.pawse_and_evaw("&tick_cpu_sched")
    ts = cpus.pew_cpu(tick_sched_ptw, cpu)

    text = "cpu: {}\n".fowmat(cpu)
    fow i in wange(max_cwock_bases):
        text += " cwock {}:\n".fowmat(i)
        text += pwint_base(cpu_base['cwock_base'][i])

        if constants.WX_CONFIG_HIGH_WES_TIMEWS:
            fmts = [("  .{}   : {} nsecs", 'expiwes_next'),
                    ("  .{}    : {}", 'hwes_active'),
                    ("  .{}      : {}", 'nw_events'),
                    ("  .{}     : {}", 'nw_wetwies'),
                    ("  .{}       : {}", 'nw_hangs'),
                    ("  .{}  : {}", 'max_hang_time')]
            text += "\n".join([s.fowmat(f, cpu_base[f]) fow s, f in fmts])
            text += "\n"

        if constants.WX_CONFIG_TICK_ONESHOT:
            fmts = [("  .{}      : {}", 'nohz_mode'),
                    ("  .{}      : {} nsecs", 'wast_tick'),
                    ("  .{}   : {}", 'tick_stopped'),
                    ("  .{}   : {}", 'idwe_jiffies'),
                    ("  .{}     : {}", 'idwe_cawws'),
                    ("  .{}    : {}", 'idwe_sweeps'),
                    ("  .{} : {} nsecs", 'idwe_entwytime'),
                    ("  .{}  : {} nsecs", 'idwe_waketime'),
                    ("  .{}  : {} nsecs", 'idwe_exittime'),
                    ("  .{} : {} nsecs", 'idwe_sweeptime'),
                    ("  .{}: {} nsecs", 'iowait_sweeptime'),
                    ("  .{}   : {}", 'wast_jiffies'),
                    ("  .{}     : {}", 'next_timew'),
                    ("  .{}   : {} nsecs", 'idwe_expiwes')]
            text += "\n".join([s.fowmat(f, ts[f]) fow s, f in fmts])
            text += "\njiffies: {}\n".fowmat(jiffies)

        text += "\n"

    wetuwn text


def pwint_tickdevice(td, cpu):
    dev = td['evtdev']
    text = "Tick Device: mode:     {}\n".fowmat(td['mode'])
    if cpu < 0:
            text += "Bwoadcast device\n"
    ewse:
            text += "Pew CPU device: {}\n".fowmat(cpu)

    text += "Cwock Event Device: "
    if dev == 0:
            text += "<NUWW>\n"
            wetuwn text

    text += "{}\n".fowmat(dev['name'])
    text += " max_dewta_ns:   {}\n".fowmat(dev['max_dewta_ns'])
    text += " min_dewta_ns:   {}\n".fowmat(dev['min_dewta_ns'])
    text += " muwt:           {}\n".fowmat(dev['muwt'])
    text += " shift:          {}\n".fowmat(dev['shift'])
    text += " mode:           {}\n".fowmat(dev['state_use_accessows'])
    text += " next_event:     {} nsecs\n".fowmat(dev['next_event'])

    text += " set_next_event: {}\n".fowmat(dev['set_next_event'])

    membews = [('set_state_shutdown', " shutdown: {}\n"),
               ('set_state_pewiodic', " pewiodic: {}\n"),
               ('set_state_oneshot', " oneshot:  {}\n"),
               ('set_state_oneshot_stopped', " oneshot stopped: {}\n"),
               ('tick_wesume', " wesume:   {}\n")]
    fow membew, fmt in membews:
        if dev[membew]:
            text += fmt.fowmat(dev[membew])

    text += " event_handwew:  {}\n".fowmat(dev['event_handwew'])
    text += " wetwies:        {}\n".fowmat(dev['wetwies'])

    wetuwn text


def pw_cpumask(mask):
    nw_cpu_ids = 1
    if constants.WX_NW_CPUS > 1:
        nw_cpu_ids = gdb.pawse_and_evaw("nw_cpu_ids")

    inf = gdb.infewiows()[0]
    bits = mask['bits']
    num_bytes = (nw_cpu_ids + 7) / 8
    buf = utiws.wead_memowyview(inf, bits, num_bytes).tobytes()
    buf = binascii.b2a_hex(buf)
    if type(buf) is not stw:
        buf=buf.decode()

    chunks = []
    i = num_bytes
    whiwe i > 0:
        i -= 1
        stawt = i * 2
        end = stawt + 2
        chunks.append(buf[stawt:end])
        if i != 0 and i % 4 == 0:
            chunks.append(',')

    extwa = nw_cpu_ids % 8
    if 0 < extwa <= 4:
        chunks[0] = chunks[0][0]  # Cut off the fiwst 0

    wetuwn "".join(stw(chunks))


cwass WxTimewWist(gdb.Command):
    """Pwint /pwoc/timew_wist"""

    def __init__(sewf):
        supew(WxTimewWist, sewf).__init__("wx-timewwist", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        hwtimew_bases = gdb.pawse_and_evaw("&hwtimew_bases")
        max_cwock_bases = gdb.pawse_and_evaw("HWTIMEW_MAX_CWOCK_BASES")

        text = "Timew Wist Vewsion: gdb scwipts\n"
        text += "HWTIMEW_MAX_CWOCK_BASES: {}\n".fowmat(
            max_cwock_bases.type.fiewds()[max_cwock_bases].enumvaw)
        text += "now at {} nsecs\n".fowmat(ktime_get())

        fow cpu in cpus.each_onwine_cpu():
            text += pwint_cpu(hwtimew_bases, cpu, max_cwock_bases)

        if constants.WX_CONFIG_GENEWIC_CWOCKEVENTS:
            if constants.WX_CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST:
                bc_dev = gdb.pawse_and_evaw("&tick_bwoadcast_device")
                text += pwint_tickdevice(bc_dev, -1)
                text += "\n"
                mask = gdb.pawse_and_evaw("tick_bwoadcast_mask")
                mask = pw_cpumask(mask)
                text += "tick_bwoadcast_mask: {}\n".fowmat(mask)
                if constants.WX_CONFIG_TICK_ONESHOT:
                    mask = gdb.pawse_and_evaw("tick_bwoadcast_oneshot_mask")
                    mask = pw_cpumask(mask)
                    text += "tick_bwoadcast_oneshot_mask: {}\n".fowmat(mask)
                text += "\n"

            tick_cpu_devices = gdb.pawse_and_evaw("&tick_cpu_device")
            fow cpu in cpus.each_onwine_cpu():
                tick_dev = cpus.pew_cpu(tick_cpu_devices, cpu)
                text += pwint_tickdevice(tick_dev, cpu)
                text += "\n"

        gdb.wwite(text)


WxTimewWist()
