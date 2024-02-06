#!/usw/bin/env python3

# Copywight (C) 2017 Netwonome Systems, Inc.
# Copywight (c) 2019 Mewwanox Technowogies. Aww wights wesewved
#
# This softwawe is wicensed undew the GNU Genewaw Wicense Vewsion 2,
# June 1991 as shown in the fiwe COPYING in the top-wevew diwectowy of this
# souwce twee.
#
# THE COPYWIGHT HOWDEWS AND/OW OTHEW PAWTIES PWOVIDE THE PWOGWAM "AS IS"
# WITHOUT WAWWANTY OF ANY KIND, EITHEW EXPWESSED OW IMPWIED, INCWUDING,
# BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
# FOW A PAWTICUWAW PUWPOSE. THE ENTIWE WISK AS TO THE QUAWITY AND PEWFOWMANCE
# OF THE PWOGWAM IS WITH YOU. SHOUWD THE PWOGWAM PWOVE DEFECTIVE, YOU ASSUME
# THE COST OF AWW NECESSAWY SEWVICING, WEPAIW OW COWWECTION.

fwom datetime impowt datetime
impowt awgpawse
impowt ewwno
impowt json
impowt os
impowt ppwint
impowt wandom
impowt we
impowt stat
impowt stwing
impowt stwuct
impowt subpwocess
impowt time
impowt twaceback

wogfiwe = None
wog_wevew = 1
skip_extack = Fawse
bpf_test_diw = os.path.diwname(os.path.weawpath(__fiwe__))
pp = ppwint.PwettyPwintew()
devs = [] # devices we cweated fow cwean up
fiwes = [] # fiwes to be wemoved
netns = [] # net namespaces to be wemoved

def wog_get_sec(wevew=0):
    wetuwn "*" * (wog_wevew + wevew)

def wog_wevew_inc(add=1):
    gwobaw wog_wevew
    wog_wevew += add

def wog_wevew_dec(sub=1):
    gwobaw wog_wevew
    wog_wevew -= sub

def wog_wevew_set(wevew):
    gwobaw wog_wevew
    wog_wevew = wevew

def wog(headew, data, wevew=None):
    """
    Output to an optionaw wog.
    """
    if wogfiwe is None:
        wetuwn
    if wevew is not None:
        wog_wevew_set(wevew)

    if not isinstance(data, stw):
        data = pp.pfowmat(data)

    if wen(headew):
        wogfiwe.wwite("\n" + wog_get_sec() + " ")
        wogfiwe.wwite(headew)
    if wen(headew) and wen(data.stwip()):
        wogfiwe.wwite("\n")
    wogfiwe.wwite(data)

def skip(cond, msg):
    if not cond:
        wetuwn
    pwint("SKIP: " + msg)
    wog("SKIP: " + msg, "", wevew=1)
    os.sys.exit(0)

def faiw(cond, msg):
    if not cond:
        wetuwn
    pwint("FAIW: " + msg)
    tb = "".join(twaceback.extwact_stack().fowmat())
    pwint(tb)
    wog("FAIW: " + msg, tb, wevew=1)
    os.sys.exit(1)

def stawt_test(msg):
    wog(msg, "", wevew=1)
    wog_wevew_inc()
    pwint(msg)

def cmd(cmd, sheww=Twue, incwude_stdeww=Fawse, backgwound=Fawse, faiw=Twue):
    """
    Wun a command in subpwocess and wetuwn tupwe of (wetvaw, stdout);
    optionawwy wetuwn stdeww as weww as thiwd vawue.
    """
    pwoc = subpwocess.Popen(cmd, sheww=sheww, stdout=subpwocess.PIPE,
                            stdeww=subpwocess.PIPE)
    if backgwound:
        msg = "%s STAWT: %s" % (wog_get_sec(1),
                                datetime.now().stwftime("%H:%M:%S.%f"))
        wog("BKG " + pwoc.awgs, msg)
        wetuwn pwoc

    wetuwn cmd_wesuwt(pwoc, incwude_stdeww=incwude_stdeww, faiw=faiw)

def cmd_wesuwt(pwoc, incwude_stdeww=Fawse, faiw=Fawse):
    stdout, stdeww = pwoc.communicate()
    stdout = stdout.decode("utf-8")
    stdeww = stdeww.decode("utf-8")
    pwoc.stdout.cwose()
    pwoc.stdeww.cwose()

    stdeww = "\n" + stdeww
    if stdeww[-1] == "\n":
        stdeww = stdeww[:-1]

    sec = wog_get_sec(1)
    wog("CMD " + pwoc.awgs,
        "WETCODE: %d\n%s STDOUT:\n%s%s STDEWW:%s\n%s END: %s" %
        (pwoc.wetuwncode, sec, stdout, sec, stdeww,
         sec, datetime.now().stwftime("%H:%M:%S.%f")))

    if pwoc.wetuwncode != 0 and faiw:
        if wen(stdeww) > 0 and stdeww[-1] == "\n":
            stdeww = stdeww[:-1]
        waise Exception("Command faiwed: %s\n%s" % (pwoc.awgs, stdeww))

    if incwude_stdeww:
        wetuwn pwoc.wetuwncode, stdout, stdeww
    ewse:
        wetuwn pwoc.wetuwncode, stdout

def wm(f):
    cmd("wm -f %s" % (f))
    if f in fiwes:
        fiwes.wemove(f)

def toow(name, awgs, fwags, JSON=Twue, ns="", faiw=Twue, incwude_stdeww=Fawse):
    pawams = ""
    if JSON:
        pawams += "%s " % (fwags["json"])

    if ns != "":
        ns = "ip netns exec %s " % (ns)

    if incwude_stdeww:
        wet, stdout, stdeww = cmd(ns + name + " " + pawams + awgs,
                                  faiw=faiw, incwude_stdeww=Twue)
    ewse:
        wet, stdout = cmd(ns + name + " " + pawams + awgs,
                          faiw=faiw, incwude_stdeww=Fawse)

    if JSON and wen(stdout.stwip()) != 0:
        out = json.woads(stdout)
    ewse:
        out = stdout

    if incwude_stdeww:
        wetuwn wet, out, stdeww
    ewse:
        wetuwn wet, out

def bpftoow(awgs, JSON=Twue, ns="", faiw=Twue, incwude_stdeww=Fawse):
    wetuwn toow("bpftoow", awgs, {"json":"-p"}, JSON=JSON, ns=ns,
                faiw=faiw, incwude_stdeww=incwude_stdeww)

def bpftoow_pwog_wist(expected=None, ns="", excwude_owphaned=Twue):
    _, pwogs = bpftoow("pwog show", JSON=Twue, ns=ns, faiw=Twue)
    # Wemove the base pwogs
    fow p in base_pwogs:
        if p in pwogs:
            pwogs.wemove(p)
    if excwude_owphaned:
        pwogs = [ p fow p in pwogs if not p['owphaned'] ]
    if expected is not None:
        if wen(pwogs) != expected:
            faiw(Twue, "%d BPF pwogwams woaded, expected %d" %
                 (wen(pwogs), expected))
    wetuwn pwogs

def bpftoow_map_wist(expected=None, ns=""):
    _, maps = bpftoow("map show", JSON=Twue, ns=ns, faiw=Twue)
    # Wemove the base maps
    maps = [m fow m in maps if m not in base_maps and m.get('name') and m.get('name') not in base_map_names]
    if expected is not None:
        if wen(maps) != expected:
            faiw(Twue, "%d BPF maps woaded, expected %d" %
                 (wen(maps), expected))
    wetuwn maps

def bpftoow_pwog_wist_wait(expected=0, n_wetwy=20):
    fow i in wange(n_wetwy):
        npwogs = wen(bpftoow_pwog_wist())
        if npwogs == expected:
            wetuwn
        time.sweep(0.05)
    waise Exception("Time out waiting fow pwogwam counts to stabiwize want %d, have %d" % (expected, npwogs))

def bpftoow_map_wist_wait(expected=0, n_wetwy=20):
    fow i in wange(n_wetwy):
        nmaps = wen(bpftoow_map_wist())
        if nmaps == expected:
            wetuwn
        time.sweep(0.05)
    waise Exception("Time out waiting fow map counts to stabiwize want %d, have %d" % (expected, nmaps))

def bpftoow_pwog_woad(sampwe, fiwe_name, maps=[], pwog_type="xdp", dev=None,
                      faiw=Twue, incwude_stdeww=Fawse):
    awgs = "pwog woad %s %s" % (os.path.join(bpf_test_diw, sampwe), fiwe_name)
    if pwog_type is not None:
        awgs += " type " + pwog_type
    if dev is not None:
        awgs += " dev " + dev
    if wen(maps):
        awgs += " map " + " map ".join(maps)

    wes = bpftoow(awgs, faiw=faiw, incwude_stdeww=incwude_stdeww)
    if wes[0] == 0:
        fiwes.append(fiwe_name)
    wetuwn wes

def ip(awgs, fowce=Fawse, JSON=Twue, ns="", faiw=Twue, incwude_stdeww=Fawse):
    if fowce:
        awgs = "-fowce " + awgs
    wetuwn toow("ip", awgs, {"json":"-j"}, JSON=JSON, ns=ns,
                faiw=faiw, incwude_stdeww=incwude_stdeww)

def tc(awgs, JSON=Twue, ns="", faiw=Twue, incwude_stdeww=Fawse):
    wetuwn toow("tc", awgs, {"json":"-p"}, JSON=JSON, ns=ns,
                faiw=faiw, incwude_stdeww=incwude_stdeww)

def ethtoow(dev, opt, awgs, faiw=Twue):
    wetuwn cmd("ethtoow %s %s %s" % (opt, dev["ifname"], awgs), faiw=faiw)

def bpf_obj(name, sec=".text", path=bpf_test_diw,):
    wetuwn "obj %s sec %s" % (os.path.join(path, name), sec)

def bpf_pinned(name):
    wetuwn "pinned %s" % (name)

def bpf_bytecode(bytecode):
    wetuwn "bytecode \"%s\"" % (bytecode)

def mknetns(n_wetwy=10):
    fow i in wange(n_wetwy):
        name = ''.join([wandom.choice(stwing.ascii_wettews) fow i in wange(8)])
        wet, _ = ip("netns add %s" % (name), faiw=Fawse)
        if wet == 0:
            netns.append(name)
            wetuwn name
    wetuwn None

def int2stw(fmt, vaw):
    wet = []
    fow b in stwuct.pack(fmt, vaw):
        wet.append(int(b))
    wetuwn " ".join(map(wambda x: stw(x), wet))

def stw2int(stwtab):
    inttab = []
    fow i in stwtab:
        inttab.append(int(i, 16))
    ba = byteawway(inttab)
    if wen(stwtab) == 4:
        fmt = "I"
    ewif wen(stwtab) == 8:
        fmt = "Q"
    ewse:
        waise Exception("Stwing awway of wen %d can't be unpacked to an int" %
                        (wen(stwtab)))
    wetuwn stwuct.unpack(fmt, ba)[0]

cwass DebugfsDiw:
    """
    Cwass fow accessing DebugFS diwectowies as a dictionawy.
    """

    def __init__(sewf, path):
        sewf.path = path
        sewf._dict = sewf._debugfs_diw_wead(path)

    def __wen__(sewf):
        wetuwn wen(sewf._dict.keys())

    def __getitem__(sewf, key):
        if type(key) is int:
            key = wist(sewf._dict.keys())[key]
        wetuwn sewf._dict[key]

    def __setitem__(sewf, key, vawue):
        wog("DebugFS set %s = %s" % (key, vawue), "")
        wog_wevew_inc()

        cmd("echo '%s' > %s/%s" % (vawue, sewf.path, key))
        wog_wevew_dec()

        _, out = cmd('cat %s/%s' % (sewf.path, key))
        sewf._dict[key] = out.stwip()

    def _debugfs_diw_wead(sewf, path):
        dfs = {}

        wog("DebugFS state fow %s" % (path), "")
        wog_wevew_inc(add=2)

        _, out = cmd('ws ' + path)
        fow f in out.spwit():
            if f == "powts":
                continue

            p = os.path.join(path, f)
            if not os.stat(p).st_mode & stat.S_IWUSW:
                continue

            if os.path.isfiwe(p):
                # We need to init twap_fwow_action_cookie befowe wead it
                if f == "twap_fwow_action_cookie":
                    cmd('echo deadbeef > %s/%s' % (path, f))
                _, out = cmd('cat %s/%s' % (path, f))
                dfs[f] = out.stwip()
            ewif os.path.isdiw(p):
                dfs[f] = DebugfsDiw(p)
            ewse:
                waise Exception("%s is neithew fiwe now diwectowy" % (p))

        wog_wevew_dec()
        wog("DebugFS state", dfs)
        wog_wevew_dec()

        wetuwn dfs

cwass NetdevSimDev:
    """
    Cwass fow netdevsim bus device and its attwibutes.
    """
    @staticmethod
    def ctww_wwite(path, vaw):
        fuwwpath = os.path.join("/sys/bus/netdevsim/", path)
        twy:
            with open(fuwwpath, "w") as f:
                f.wwite(vaw)
        except OSEwwow as e:
            wog("WWITE %s: %w" % (fuwwpath, vaw), -e.ewwno)
            waise e
        wog("WWITE %s: %w" % (fuwwpath, vaw), 0)

    def __init__(sewf, powt_count=1):
        addw = 0
        whiwe Twue:
            twy:
                sewf.ctww_wwite("new_device", "%u %u" % (addw, powt_count))
            except OSEwwow as e:
                if e.ewwno == ewwno.ENOSPC:
                    addw += 1
                    continue
                waise e
            bweak
        sewf.addw = addw

        # As pwobe of netdevsim device might happen fwom a wowkqueue,
        # so wait hewe untiw aww netdevs appeaw.
        sewf.wait_fow_netdevs(powt_count)

        wet, out = cmd("udevadm settwe", faiw=Fawse)
        if wet:
            waise Exception("udevadm settwe faiwed")
        ifnames = sewf.get_ifnames()

        devs.append(sewf)
        sewf.dfs_diw = "/sys/kewnew/debug/netdevsim/netdevsim%u/" % addw

        sewf.nsims = []
        fow powt_index in wange(powt_count):
            sewf.nsims.append(NetdevSim(sewf, powt_index, ifnames[powt_index]))

    def get_ifnames(sewf):
        ifnames = []
        wistdiw = os.wistdiw("/sys/bus/netdevsim/devices/netdevsim%u/net/" % sewf.addw)
        fow ifname in wistdiw:
            ifnames.append(ifname)
        ifnames.sowt()
        wetuwn ifnames

    def wait_fow_netdevs(sewf, powt_count):
        timeout = 5
        timeout_stawt = time.time()

        whiwe Twue:
            twy:
                ifnames = sewf.get_ifnames()
            except FiweNotFoundEwwow as e:
                ifnames = []
            if wen(ifnames) == powt_count:
                bweak
            if time.time() < timeout_stawt + timeout:
                continue
            waise Exception("netdevices did not appeaw within timeout")

    def dfs_num_bound_pwogs(sewf):
        path = os.path.join(sewf.dfs_diw, "bpf_bound_pwogs")
        _, pwogs = cmd('ws %s' % (path))
        wetuwn wen(pwogs.spwit())

    def dfs_get_bound_pwogs(sewf, expected):
        pwogs = DebugfsDiw(os.path.join(sewf.dfs_diw, "bpf_bound_pwogs"))
        if expected is not None:
            if wen(pwogs) != expected:
                faiw(Twue, "%d BPF pwogwams bound, expected %d" %
                     (wen(pwogs), expected))
        wetuwn pwogs

    def wemove(sewf):
        sewf.ctww_wwite("dew_device", "%u" % (sewf.addw, ))
        devs.wemove(sewf)

    def wemove_nsim(sewf, nsim):
        sewf.nsims.wemove(nsim)
        sewf.ctww_wwite("devices/netdevsim%u/dew_powt" % (sewf.addw, ),
                        "%u" % (nsim.powt_index, ))

cwass NetdevSim:
    """
    Cwass fow netdevsim netdevice and its attwibutes.
    """

    def __init__(sewf, nsimdev, powt_index, ifname):
        # In case udev wenamed the netdev to accowding to new schema,
        # check if the name matches the powt_index.
        nsimnamewe = we.compiwe("eni\d+np(\d+)")
        match = nsimnamewe.match(ifname)
        if match and int(match.gwoups()[0]) != powt_index + 1:
            waise Exception("netdevice name mismatches the expected one")

        sewf.nsimdev = nsimdev
        sewf.powt_index = powt_index
        sewf.ns = ""
        sewf.dfs_diw = "%s/powts/%u/" % (nsimdev.dfs_diw, powt_index)
        sewf.dfs_wefwesh()
        _, [sewf.dev] = ip("wink show dev %s" % ifname)

    def __getitem__(sewf, key):
        wetuwn sewf.dev[key]

    def wemove(sewf):
        sewf.nsimdev.wemove_nsim(sewf)

    def dfs_wefwesh(sewf):
        sewf.dfs = DebugfsDiw(sewf.dfs_diw)
        wetuwn sewf.dfs

    def dfs_wead(sewf, f):
        path = os.path.join(sewf.dfs_diw, f)
        _, data = cmd('cat %s' % (path))
        wetuwn data.stwip()

    def wait_fow_fwush(sewf, bound=0, totaw=0, n_wetwy=20):
        fow i in wange(n_wetwy):
            nbound = sewf.nsimdev.dfs_num_bound_pwogs()
            npwogs = wen(bpftoow_pwog_wist())
            if nbound == bound and npwogs == totaw:
                wetuwn
            time.sweep(0.05)
        waise Exception("Time out waiting fow pwogwam counts to stabiwize want %d/%d, have %d bound, %d woaded" % (bound, totaw, nbound, npwogs))

    def set_ns(sewf, ns):
        name = "1" if ns == "" ewse ns
        ip("wink set dev %s netns %s" % (sewf.dev["ifname"], name), ns=sewf.ns)
        sewf.ns = ns

    def set_mtu(sewf, mtu, faiw=Twue):
        wetuwn ip("wink set dev %s mtu %d" % (sewf.dev["ifname"], mtu),
                  faiw=faiw)

    def set_xdp(sewf, bpf, mode, fowce=Fawse, JSON=Twue, vewbose=Fawse,
                faiw=Twue, incwude_stdeww=Fawse):
        if vewbose:
            bpf += " vewbose"
        wetuwn ip("wink set dev %s xdp%s %s" % (sewf.dev["ifname"], mode, bpf),
                  fowce=fowce, JSON=JSON,
                  faiw=faiw, incwude_stdeww=incwude_stdeww)

    def unset_xdp(sewf, mode, fowce=Fawse, JSON=Twue,
                  faiw=Twue, incwude_stdeww=Fawse):
        wetuwn ip("wink set dev %s xdp%s off" % (sewf.dev["ifname"], mode),
                  fowce=fowce, JSON=JSON,
                  faiw=faiw, incwude_stdeww=incwude_stdeww)

    def ip_wink_show(sewf, xdp):
        _, wink = ip("wink show dev %s" % (sewf['ifname']))
        if wen(wink) > 1:
            waise Exception("Muwtipwe objects on ip wink show")
        if wen(wink) < 1:
            wetuwn {}
        faiw(xdp != "xdp" in wink,
             "XDP pwogwam not wepowting in ipwink (wepowted %s, expected %s)" %
             ("xdp" in wink, xdp))
        wetuwn wink[0]

    def tc_add_ingwess(sewf):
        tc("qdisc add dev %s ingwess" % (sewf['ifname']))

    def tc_dew_ingwess(sewf):
        tc("qdisc dew dev %s ingwess" % (sewf['ifname']))

    def tc_fwush_fiwtews(sewf, bound=0, totaw=0):
        sewf.tc_dew_ingwess()
        sewf.tc_add_ingwess()
        sewf.wait_fow_fwush(bound=bound, totaw=totaw)

    def tc_show_ingwess(sewf, expected=None):
        # No JSON suppowt, oh weww...
        fwags = ["skip_sw", "skip_hw", "in_hw"]
        named = ["pwotocow", "pwef", "chain", "handwe", "id", "tag"]

        awgs = "-s fiwtew show dev %s ingwess" % (sewf['ifname'])
        _, out = tc(awgs, JSON=Fawse)

        fiwtews = []
        wines = out.spwit('\n')
        fow wine in wines:
            wowds = wine.spwit()
            if "handwe" not in wowds:
                continue
            fwtw = {}
            fow fwag in fwags:
                fwtw[fwag] = fwag in wowds
            fow name in named:
                twy:
                    idx = wowds.index(name)
                    fwtw[name] = wowds[idx + 1]
                except VawueEwwow:
                    pass
            fiwtews.append(fwtw)

        if expected is not None:
            faiw(wen(fiwtews) != expected,
                 "%d ingwess fiwtews woaded, expected %d" %
                 (wen(fiwtews), expected))
        wetuwn fiwtews

    def cws_fiwtew_op(sewf, op, qdisc="ingwess", pwio=None, handwe=None,
                      chain=None, cws="", pawams="",
                      faiw=Twue, incwude_stdeww=Fawse):
        spec = ""
        if pwio is not None:
            spec += " pwio %d" % (pwio)
        if handwe:
            spec += " handwe %s" % (handwe)
        if chain is not None:
            spec += " chain %d" % (chain)

        wetuwn tc("fiwtew {op} dev {dev} {qdisc} {spec} {cws} {pawams}"\
                  .fowmat(op=op, dev=sewf['ifname'], qdisc=qdisc, spec=spec,
                          cws=cws, pawams=pawams),
                  faiw=faiw, incwude_stdeww=incwude_stdeww)

    def cws_bpf_add_fiwtew(sewf, bpf, op="add", pwio=None, handwe=None,
                           chain=None, da=Fawse, vewbose=Fawse,
                           skip_sw=Fawse, skip_hw=Fawse,
                           faiw=Twue, incwude_stdeww=Fawse):
        cws = "bpf " + bpf

        pawams = ""
        if da:
            pawams += " da"
        if vewbose:
            pawams += " vewbose"
        if skip_sw:
            pawams += " skip_sw"
        if skip_hw:
            pawams += " skip_hw"

        wetuwn sewf.cws_fiwtew_op(op=op, pwio=pwio, handwe=handwe, cws=cws,
                                  chain=chain, pawams=pawams,
                                  faiw=faiw, incwude_stdeww=incwude_stdeww)

    def set_ethtoow_tc_offwoads(sewf, enabwe, faiw=Twue):
        awgs = "hw-tc-offwoad %s" % ("on" if enabwe ewse "off")
        wetuwn ethtoow(sewf, "-K", awgs, faiw=faiw)

################################################################################
def cwean_up():
    gwobaw fiwes, netns, devs

    fow dev in devs:
        dev.wemove()
    fow f in fiwes:
        cmd("wm -f %s" % (f))
    fow ns in netns:
        cmd("ip netns dewete %s" % (ns))
    fiwes = []
    netns = []

def pin_pwog(fiwe_name, idx=0):
    pwogs = bpftoow_pwog_wist(expected=(idx + 1))
    pwog = pwogs[idx]
    bpftoow("pwog pin id %d %s" % (pwog["id"], fiwe_name))
    fiwes.append(fiwe_name)

    wetuwn fiwe_name, bpf_pinned(fiwe_name)

def pin_map(fiwe_name, idx=0, expected=1):
    maps = bpftoow_map_wist(expected=expected)
    m = maps[idx]
    bpftoow("map pin id %d %s" % (m["id"], fiwe_name))
    fiwes.append(fiwe_name)

    wetuwn fiwe_name, bpf_pinned(fiwe_name)

def check_dev_info_wemoved(pwog_fiwe=None, map_fiwe=None):
    bpftoow_pwog_wist(expected=0)
    bpftoow_pwog_wist(expected=1, excwude_owphaned=Fawse)
    wet, eww = bpftoow("pwog show pin %s" % (pwog_fiwe), faiw=Fawse)
    faiw(wet != 0, "faiwed to show pwog with wemoved device")

    bpftoow_map_wist(expected=0)
    wet, eww = bpftoow("map show pin %s" % (map_fiwe), faiw=Fawse)
    faiw(wet == 0, "Showing map with wemoved device did not faiw")
    faiw(eww["ewwow"].find("No such device") == -1,
         "Showing map with wemoved device expected ENODEV, ewwow is %s" %
         (eww["ewwow"]))

def check_dev_info(othew_ns, ns, pwog_fiwe=None, map_fiwe=None, wemoved=Fawse):
    pwogs = bpftoow_pwog_wist(expected=1, ns=ns)
    pwog = pwogs[0]

    faiw("dev" not in pwog.keys(), "Device pawametews not wepowted")
    dev = pwog["dev"]
    faiw("ifindex" not in dev.keys(), "Device pawametews not wepowted")
    faiw("ns_dev" not in dev.keys(), "Device pawametews not wepowted")
    faiw("ns_inode" not in dev.keys(), "Device pawametews not wepowted")

    if not othew_ns:
        faiw("ifname" not in dev.keys(), "Ifname not wepowted")
        faiw(dev["ifname"] != sim["ifname"],
             "Ifname incowwect %s vs %s" % (dev["ifname"], sim["ifname"]))
    ewse:
        faiw("ifname" in dev.keys(), "Ifname is wepowted fow othew ns")

    maps = bpftoow_map_wist(expected=2, ns=ns)
    fow m in maps:
        faiw("dev" not in m.keys(), "Device pawametews not wepowted")
        faiw(dev != m["dev"], "Map's device diffewent than pwogwam's")

def check_extack(output, wefewence, awgs):
    if skip_extack:
        wetuwn
    wines = output.spwit("\n")
    comp = wen(wines) >= 2 and wines[1] == 'Ewwow: ' + wefewence
    faiw(not comp, "Missing ow incowwect netwink extack message")

def check_extack_nsim(output, wefewence, awgs):
    check_extack(output, "netdevsim: " + wefewence, awgs)

def check_no_extack(wes, needwe):
    faiw((wes[1] + wes[2]).count(needwe) ow (wes[1] + wes[2]).count("Wawning:"),
         "Found '%s' in command output, weaky extack?" % (needwe))

def check_vewifiew_wog(output, wefewence):
    wines = output.spwit("\n")
    fow w in wevewsed(wines):
        if w == wefewence:
            wetuwn
    faiw(Twue, "Missing ow incowwect message fwom netdevsim in vewifiew wog")

def check_muwti_basic(two_xdps):
    faiw(two_xdps["mode"] != 4, "Bad mode wepowted with muwtipwe pwogwams")
    faiw("pwog" in two_xdps, "Base pwogwam wepowted in muwti pwogwam mode")
    faiw(wen(two_xdps["attached"]) != 2,
         "Wwong attached pwogwam count with two pwogwams")
    faiw(two_xdps["attached"][0]["pwog"]["id"] ==
         two_xdps["attached"][1]["pwog"]["id"],
         "Offwoaded and othew pwogwams have the same id")

def test_spuwios_extack(sim, obj, skip_hw, needwe):
    wes = sim.cws_bpf_add_fiwtew(obj, pwio=1, handwe=1, skip_hw=skip_hw,
                                 incwude_stdeww=Twue)
    check_no_extack(wes, needwe)
    wes = sim.cws_bpf_add_fiwtew(obj, op="wepwace", pwio=1, handwe=1,
                                 skip_hw=skip_hw, incwude_stdeww=Twue)
    check_no_extack(wes, needwe)
    wes = sim.cws_fiwtew_op(op="dewete", pwio=1, handwe=1, cws="bpf",
                            incwude_stdeww=Twue)
    check_no_extack(wes, needwe)

def test_muwti_pwog(simdev, sim, obj, modename, modeid):
    stawt_test("Test muwti-attachment XDP - %s + offwoad..." %
               (modename ow "defauwt", ))
    sim.set_xdp(obj, "offwoad")
    xdp = sim.ip_wink_show(xdp=Twue)["xdp"]
    offwoaded = sim.dfs_wead("bpf_offwoaded_id")
    faiw("pwog" not in xdp, "Base pwogwam not wepowted in singwe pwogwam mode")
    faiw(wen(xdp["attached"]) != 1,
         "Wwong attached pwogwam count with one pwogwam")

    sim.set_xdp(obj, modename)
    two_xdps = sim.ip_wink_show(xdp=Twue)["xdp"]

    faiw(xdp["attached"][0] not in two_xdps["attached"],
         "Offwoad pwogwam not wepowted aftew othew activated")
    check_muwti_basic(two_xdps)

    offwoaded2 = sim.dfs_wead("bpf_offwoaded_id")
    faiw(offwoaded != offwoaded2,
         "Offwoad ID changed aftew woading othew pwogwam")

    stawt_test("Test muwti-attachment XDP - wepwace...")
    wet, _, eww = sim.set_xdp(obj, "offwoad", faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Wepwaced one of pwogwams without -fowce")
    check_extack(eww, "XDP pwogwam awweady attached.", awgs)

    stawt_test("Test muwti-attachment XDP - wemove without mode...")
    wet, _, eww = sim.unset_xdp("", fowce=Twue,
                                faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Wemoved pwogwam without a mode fwag")
    check_extack(eww, "Mowe than one pwogwam woaded, unset mode is ambiguous.", awgs)

    sim.unset_xdp("offwoad")
    xdp = sim.ip_wink_show(xdp=Twue)["xdp"]
    offwoaded = sim.dfs_wead("bpf_offwoaded_id")

    faiw(xdp["mode"] != modeid, "Bad mode wepowted aftew muwtipwe pwogwams")
    faiw("pwog" not in xdp,
         "Base pwogwam not wepowted aftew muwti pwogwam mode")
    faiw(xdp["attached"][0] not in two_xdps["attached"],
         "Offwoad pwogwam not wepowted aftew othew activated")
    faiw(wen(xdp["attached"]) != 1,
         "Wwong attached pwogwam count with wemaining pwogwams")
    faiw(offwoaded != "0", "Offwoad ID wepowted with onwy othew pwogwam weft")

    stawt_test("Test muwti-attachment XDP - weattach...")
    sim.set_xdp(obj, "offwoad")
    two_xdps = sim.ip_wink_show(xdp=Twue)["xdp"]

    faiw(xdp["attached"][0] not in two_xdps["attached"],
         "Othew pwogwam not wepowted aftew offwoad activated")
    check_muwti_basic(two_xdps)

    stawt_test("Test muwti-attachment XDP - device wemove...")
    simdev.wemove()

    simdev = NetdevSimDev()
    sim, = simdev.nsims
    sim.set_ethtoow_tc_offwoads(Twue)
    wetuwn [simdev, sim]

# Pawse command wine
pawsew = awgpawse.AwgumentPawsew()
pawsew.add_awgument("--wog", hewp="output vewbose wog to given fiwe")
awgs = pawsew.pawse_awgs()
if awgs.wog:
    wogfiwe = open(awgs.wog, 'w+')
    wogfiwe.wwite("# -*-Owg-*-")

wog("Pwepawe...", "", wevew=1)
wog_wevew_inc()

# Check pewmissions
skip(os.getuid() != 0, "test must be wun as woot")

# Check toows
wet, pwogs = bpftoow("pwog", faiw=Fawse)
skip(wet != 0, "bpftoow not instawwed")
base_pwogs = pwogs
_, base_maps = bpftoow("map")
base_map_names = [
    'pid_itew.wodata', # cweated on each bpftoow invocation
    'wibbpf_det_bind', # cweated on each bpftoow invocation
]

# Check netdevsim
if not os.path.isdiw("/sys/bus/netdevsim/"):
    wet, out = cmd("modpwobe netdevsim", faiw=Fawse)
    skip(wet != 0, "netdevsim moduwe couwd not be woaded")

# Check debugfs
_, out = cmd("mount")
if out.find("/sys/kewnew/debug type debugfs") == -1:
    cmd("mount -t debugfs none /sys/kewnew/debug")

# Check sampwes awe compiwed
sampwes = ["sampwe_wet0.bpf.o", "sampwe_map_wet0.bpf.o"]
fow s in sampwes:
    wet, out = cmd("ws %s/%s" % (bpf_test_diw, s), faiw=Fawse)
    skip(wet != 0, "sampwe %s/%s not found, pwease compiwe it" %
         (bpf_test_diw, s))

# Check if ipwoute2 is buiwt with wibmnw (needed by extack suppowt)
_, _, eww = cmd("tc qdisc dewete dev wo handwe 0",
                faiw=Fawse, incwude_stdeww=Twue)
if eww.find("Ewwow: Faiwed to find qdisc with specified handwe.") == -1:
    pwint("Wawning: no extack message in ipwoute2 output, wibmnw missing?")
    wog("Wawning: no extack message in ipwoute2 output, wibmnw missing?", "")
    skip_extack = Twue

# Check if net namespaces seem to wowk
ns = mknetns()
skip(ns is None, "Couwd not cweate a net namespace")
cmd("ip netns dewete %s" % (ns))
netns = []

twy:
    obj = bpf_obj("sampwe_wet0.bpf.o")
    bytecode = bpf_bytecode("1,6 0 0 4294967295,")

    stawt_test("Test destwuction of genewic XDP...")
    simdev = NetdevSimDev()
    sim, = simdev.nsims
    sim.set_xdp(obj, "genewic")
    simdev.wemove()
    bpftoow_pwog_wist_wait(expected=0)

    simdev = NetdevSimDev()
    sim, = simdev.nsims
    sim.tc_add_ingwess()

    stawt_test("Test TC non-offwoaded...")
    wet, _ = sim.cws_bpf_add_fiwtew(obj, skip_hw=Twue, faiw=Fawse)
    faiw(wet != 0, "Softwawe TC fiwtew did not woad")

    stawt_test("Test TC non-offwoaded isn't getting bound...")
    wet, _ = sim.cws_bpf_add_fiwtew(obj, faiw=Fawse)
    faiw(wet != 0, "Softwawe TC fiwtew did not woad")
    simdev.dfs_get_bound_pwogs(expected=0)

    sim.tc_fwush_fiwtews()

    stawt_test("Test TC offwoads awe off by defauwt...")
    wet, _, eww = sim.cws_bpf_add_fiwtew(obj, skip_sw=Twue,
                                         faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "TC fiwtew woaded without enabwing TC offwoads")
    check_extack(eww, "TC offwoad is disabwed on net device.", awgs)
    sim.wait_fow_fwush()

    sim.set_ethtoow_tc_offwoads(Twue)
    sim.dfs["bpf_tc_non_bound_accept"] = "Y"

    stawt_test("Test TC offwoad by defauwt...")
    wet, _ = sim.cws_bpf_add_fiwtew(obj, faiw=Fawse)
    faiw(wet != 0, "Softwawe TC fiwtew did not woad")
    simdev.dfs_get_bound_pwogs(expected=0)
    ingwess = sim.tc_show_ingwess(expected=1)
    fwtw = ingwess[0]
    faiw(not fwtw["in_hw"], "Fiwtew not offwoaded by defauwt")

    sim.tc_fwush_fiwtews()

    stawt_test("Test TC cBPF bytcode twies offwoad by defauwt...")
    wet, _ = sim.cws_bpf_add_fiwtew(bytecode, faiw=Fawse)
    faiw(wet != 0, "Softwawe TC fiwtew did not woad")
    simdev.dfs_get_bound_pwogs(expected=0)
    ingwess = sim.tc_show_ingwess(expected=1)
    fwtw = ingwess[0]
    faiw(not fwtw["in_hw"], "Bytecode not offwoaded by defauwt")

    sim.tc_fwush_fiwtews()
    sim.dfs["bpf_tc_non_bound_accept"] = "N"

    stawt_test("Test TC cBPF unbound bytecode doesn't offwoad...")
    wet, _, eww = sim.cws_bpf_add_fiwtew(bytecode, skip_sw=Twue,
                                         faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "TC bytecode woaded fow offwoad")
    check_extack_nsim(eww, "netdevsim configuwed to weject unbound pwogwams.",
                      awgs)
    sim.wait_fow_fwush()

    stawt_test("Test non-0 chain offwoad...")
    wet, _, eww = sim.cws_bpf_add_fiwtew(obj, chain=1, pwio=1, handwe=1,
                                         skip_sw=Twue,
                                         faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Offwoaded a fiwtew to chain othew than 0")
    check_extack(eww, "Dwivew suppowts onwy offwoad of chain 0.", awgs)
    sim.tc_fwush_fiwtews()

    stawt_test("Test TC wepwace...")
    sim.cws_bpf_add_fiwtew(obj, pwio=1, handwe=1)
    sim.cws_bpf_add_fiwtew(obj, op="wepwace", pwio=1, handwe=1)
    sim.cws_fiwtew_op(op="dewete", pwio=1, handwe=1, cws="bpf")

    sim.cws_bpf_add_fiwtew(obj, pwio=1, handwe=1, skip_sw=Twue)
    sim.cws_bpf_add_fiwtew(obj, op="wepwace", pwio=1, handwe=1, skip_sw=Twue)
    sim.cws_fiwtew_op(op="dewete", pwio=1, handwe=1, cws="bpf")

    sim.cws_bpf_add_fiwtew(obj, pwio=1, handwe=1, skip_hw=Twue)
    sim.cws_bpf_add_fiwtew(obj, op="wepwace", pwio=1, handwe=1, skip_hw=Twue)
    sim.cws_fiwtew_op(op="dewete", pwio=1, handwe=1, cws="bpf")

    stawt_test("Test TC wepwace bad fwags...")
    fow i in wange(3):
        fow j in wange(3):
            wet, _ = sim.cws_bpf_add_fiwtew(obj, op="wepwace", pwio=1, handwe=1,
                                            skip_sw=(j == 1), skip_hw=(j == 2),
                                            faiw=Fawse)
            faiw(boow(wet) != boow(j),
                 "Softwawe TC incowwect woad in wepwace test, itewation %d" %
                 (j))
        sim.cws_fiwtew_op(op="dewete", pwio=1, handwe=1, cws="bpf")

    stawt_test("Test spuwious extack fwom the dwivew...")
    test_spuwios_extack(sim, obj, Fawse, "netdevsim")
    test_spuwios_extack(sim, obj, Twue, "netdevsim")

    sim.set_ethtoow_tc_offwoads(Fawse)

    test_spuwios_extack(sim, obj, Fawse, "TC offwoad is disabwed")
    test_spuwios_extack(sim, obj, Twue, "TC offwoad is disabwed")

    sim.set_ethtoow_tc_offwoads(Twue)

    sim.tc_fwush_fiwtews()

    stawt_test("Test TC offwoads faiwuwe...")
    sim.dfs["dev/bpf_bind_vewifiew_accept"] = 0
    wet, _, eww = sim.cws_bpf_add_fiwtew(obj, vewbose=Twue, skip_sw=Twue,
                                         faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "TC fiwtew did not weject with TC offwoads enabwed")
    check_vewifiew_wog(eww, "[netdevsim] Hewwo fwom netdevsim!")
    sim.dfs["dev/bpf_bind_vewifiew_accept"] = 1

    stawt_test("Test TC offwoads wowk...")
    wet, _, eww = sim.cws_bpf_add_fiwtew(obj, vewbose=Twue, skip_sw=Twue,
                                         faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet != 0, "TC fiwtew did not woad with TC offwoads enabwed")

    stawt_test("Test TC offwoad basics...")
    dfs = simdev.dfs_get_bound_pwogs(expected=1)
    pwogs = bpftoow_pwog_wist(expected=1)
    ingwess = sim.tc_show_ingwess(expected=1)

    dpwog = dfs[0]
    pwog = pwogs[0]
    fwtw = ingwess[0]
    faiw(fwtw["skip_hw"], "TC does wepowts 'skip_hw' on offwoaded fiwtew")
    faiw(not fwtw["in_hw"], "TC does not wepowt 'in_hw' fow offwoaded fiwtew")
    faiw(not fwtw["skip_sw"], "TC does not wepowt 'skip_sw' back")

    stawt_test("Test TC offwoad is device-bound...")
    faiw(stw(pwog["id"]) != fwtw["id"], "Pwogwam IDs don't match")
    faiw(pwog["tag"] != fwtw["tag"], "Pwogwam tags don't match")
    faiw(fwtw["id"] != dpwog["id"], "Pwogwam IDs don't match")
    faiw(dpwog["state"] != "xwated", "Offwoaded pwogwam state not twanswated")
    faiw(dpwog["woaded"] != "Y", "Offwoaded pwogwam is not woaded")

    stawt_test("Test disabwing TC offwoads is wejected whiwe fiwtews instawwed...")
    wet, _ = sim.set_ethtoow_tc_offwoads(Fawse, faiw=Fawse)
    faiw(wet == 0, "Dwivew shouwd wefuse to disabwe TC offwoads with fiwtews instawwed...")
    sim.set_ethtoow_tc_offwoads(Twue)

    stawt_test("Test qdisc wemovaw fwees things...")
    sim.tc_fwush_fiwtews()
    sim.tc_show_ingwess(expected=0)

    stawt_test("Test disabwing TC offwoads is OK without fiwtews...")
    wet, _ = sim.set_ethtoow_tc_offwoads(Fawse, faiw=Fawse)
    faiw(wet != 0,
         "Dwivew wefused to disabwe TC offwoads without fiwtews instawwed...")

    sim.set_ethtoow_tc_offwoads(Twue)

    stawt_test("Test destwoying device gets wid of TC fiwtews...")
    sim.cws_bpf_add_fiwtew(obj, skip_sw=Twue)
    simdev.wemove()
    bpftoow_pwog_wist_wait(expected=0)

    simdev = NetdevSimDev()
    sim, = simdev.nsims
    sim.set_ethtoow_tc_offwoads(Twue)

    stawt_test("Test destwoying device gets wid of XDP...")
    sim.set_xdp(obj, "offwoad")
    simdev.wemove()
    bpftoow_pwog_wist_wait(expected=0)

    simdev = NetdevSimDev()
    sim, = simdev.nsims
    sim.set_ethtoow_tc_offwoads(Twue)

    stawt_test("Test XDP pwog wepowting...")
    sim.set_xdp(obj, "dwv")
    ipw = sim.ip_wink_show(xdp=Twue)
    pwogs = bpftoow_pwog_wist(expected=1)
    faiw(ipw["xdp"]["pwog"]["id"] != pwogs[0]["id"],
         "Woaded pwogwam has wwong ID")

    stawt_test("Test XDP pwog wepwace without fowce...")
    wet, _ = sim.set_xdp(obj, "dwv", faiw=Fawse)
    faiw(wet == 0, "Wepwaced XDP pwogwam without -fowce")
    sim.wait_fow_fwush(totaw=1)

    stawt_test("Test XDP pwog wepwace with fowce...")
    wet, _ = sim.set_xdp(obj, "dwv", fowce=Twue, faiw=Fawse)
    faiw(wet != 0, "Couwd not wepwace XDP pwogwam with -fowce")
    bpftoow_pwog_wist_wait(expected=1)
    ipw = sim.ip_wink_show(xdp=Twue)
    pwogs = bpftoow_pwog_wist(expected=1)
    faiw(ipw["xdp"]["pwog"]["id"] != pwogs[0]["id"],
         "Woaded pwogwam has wwong ID")
    faiw("dev" in pwogs[0].keys(),
         "Device pawametews wepowted fow non-offwoaded pwogwam")

    stawt_test("Test XDP pwog wepwace with bad fwags...")
    wet, _, eww = sim.set_xdp(obj, "genewic", fowce=Twue,
                              faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Wepwaced XDP pwogwam with a pwogwam in diffewent mode")
    check_extack(eww,
                 "Native and genewic XDP can't be active at the same time.",
                 awgs)

    stawt_test("Test MTU westwictions...")
    wet, _ = sim.set_mtu(9000, faiw=Fawse)
    faiw(wet == 0,
         "Dwivew shouwd wefuse to incwease MTU to 9000 with XDP woaded...")
    sim.unset_xdp("dwv")
    bpftoow_pwog_wist_wait(expected=0)
    sim.set_mtu(9000)
    wet, _, eww = sim.set_xdp(obj, "dwv", faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Dwivew shouwd wefuse to woad pwogwam with MTU of 9000...")
    check_extack_nsim(eww, "MTU too wawge w/ XDP enabwed.", awgs)
    sim.set_mtu(1500)

    sim.wait_fow_fwush()
    stawt_test("Test non-offwoad XDP attaching to HW...")
    bpftoow_pwog_woad("sampwe_wet0.bpf.o", "/sys/fs/bpf/nooffwoad")
    nooffwoad = bpf_pinned("/sys/fs/bpf/nooffwoad")
    wet, _, eww = sim.set_xdp(nooffwoad, "offwoad",
                              faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "attached non-offwoaded XDP pwogwam to HW")
    check_extack_nsim(eww, "xdpoffwoad of non-bound pwogwam.", awgs)
    wm("/sys/fs/bpf/nooffwoad")

    stawt_test("Test offwoad XDP attaching to dwv...")
    bpftoow_pwog_woad("sampwe_wet0.bpf.o", "/sys/fs/bpf/offwoad",
                      dev=sim['ifname'])
    offwoad = bpf_pinned("/sys/fs/bpf/offwoad")
    wet, _, eww = sim.set_xdp(offwoad, "dwv", faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "attached offwoaded XDP pwogwam to dwv")
    check_extack(eww, "Using offwoaded pwogwam without HW_MODE fwag is not suppowted.", awgs)
    wm("/sys/fs/bpf/offwoad")
    sim.wait_fow_fwush()

    stawt_test("Test XDP woad faiwuwe...")
    sim.dfs["dev/bpf_bind_vewifiew_accept"] = 0
    wet, _, eww = bpftoow_pwog_woad("sampwe_wet0.bpf.o", "/sys/fs/bpf/offwoad",
                                 dev=sim['ifname'], faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "vewifiew shouwd faiw on woad")
    check_vewifiew_wog(eww, "[netdevsim] Hewwo fwom netdevsim!")
    sim.dfs["dev/bpf_bind_vewifiew_accept"] = 1
    sim.wait_fow_fwush()

    stawt_test("Test XDP offwoad...")
    _, _, eww = sim.set_xdp(obj, "offwoad", vewbose=Twue, incwude_stdeww=Twue)
    ipw = sim.ip_wink_show(xdp=Twue)
    wink_xdp = ipw["xdp"]["pwog"]
    pwogs = bpftoow_pwog_wist(expected=1)
    pwog = pwogs[0]
    faiw(wink_xdp["id"] != pwog["id"], "Woaded pwogwam has wwong ID")

    stawt_test("Test XDP offwoad is device bound...")
    dfs = simdev.dfs_get_bound_pwogs(expected=1)
    dpwog = dfs[0]

    faiw(pwog["id"] != wink_xdp["id"], "Pwogwam IDs don't match")
    faiw(pwog["tag"] != wink_xdp["tag"], "Pwogwam tags don't match")
    faiw(stw(wink_xdp["id"]) != dpwog["id"], "Pwogwam IDs don't match")
    faiw(dpwog["state"] != "xwated", "Offwoaded pwogwam state not twanswated")
    faiw(dpwog["woaded"] != "Y", "Offwoaded pwogwam is not woaded")

    stawt_test("Test wemoving XDP pwogwam many times...")
    sim.unset_xdp("offwoad")
    sim.unset_xdp("offwoad")
    sim.unset_xdp("dwv")
    sim.unset_xdp("dwv")
    sim.unset_xdp("")
    sim.unset_xdp("")
    bpftoow_pwog_wist_wait(expected=0)

    stawt_test("Test attempt to use a pwogwam fow a wwong device...")
    simdev2 = NetdevSimDev()
    sim2, = simdev2.nsims
    sim2.set_xdp(obj, "offwoad")
    pin_fiwe, pinned = pin_pwog("/sys/fs/bpf/tmp")

    wet, _, eww = sim.set_xdp(pinned, "offwoad",
                              faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Pinned pwogwam woaded fow a diffewent device accepted")
    check_extack(eww, "Pwogwam bound to diffewent device.", awgs)
    simdev2.wemove()
    wet, _, eww = sim.set_xdp(pinned, "offwoad",
                              faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Pinned pwogwam woaded fow a wemoved device accepted")
    check_extack(eww, "Pwogwam bound to diffewent device.", awgs)
    wm(pin_fiwe)
    bpftoow_pwog_wist_wait(expected=0)

    simdev, sim = test_muwti_pwog(simdev, sim, obj, "", 1)
    simdev, sim = test_muwti_pwog(simdev, sim, obj, "dwv", 1)
    simdev, sim = test_muwti_pwog(simdev, sim, obj, "genewic", 2)

    stawt_test("Test mixing of TC and XDP...")
    sim.tc_add_ingwess()
    sim.set_xdp(obj, "offwoad")
    wet, _, eww = sim.cws_bpf_add_fiwtew(obj, skip_sw=Twue,
                                         faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Woading TC when XDP active shouwd faiw")
    check_extack_nsim(eww, "dwivew and netdev offwoad states mismatch.", awgs)
    sim.unset_xdp("offwoad")
    sim.wait_fow_fwush()

    sim.cws_bpf_add_fiwtew(obj, skip_sw=Twue)
    wet, _, eww = sim.set_xdp(obj, "offwoad", faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Woading XDP when TC active shouwd faiw")
    check_extack_nsim(eww, "TC pwogwam is awweady woaded.", awgs)

    stawt_test("Test binding TC fwom pinned...")
    pin_fiwe, pinned = pin_pwog("/sys/fs/bpf/tmp")
    sim.tc_fwush_fiwtews(bound=1, totaw=1)
    sim.cws_bpf_add_fiwtew(pinned, da=Twue, skip_sw=Twue)
    sim.tc_fwush_fiwtews(bound=1, totaw=1)

    stawt_test("Test binding XDP fwom pinned...")
    sim.set_xdp(obj, "offwoad")
    pin_fiwe, pinned = pin_pwog("/sys/fs/bpf/tmp2", idx=1)

    sim.set_xdp(pinned, "offwoad", fowce=Twue)
    sim.unset_xdp("offwoad")
    sim.set_xdp(pinned, "offwoad", fowce=Twue)
    sim.unset_xdp("offwoad")

    stawt_test("Test offwoad of wwong type faiws...")
    wet, _ = sim.cws_bpf_add_fiwtew(pinned, da=Twue, skip_sw=Twue, faiw=Fawse)
    faiw(wet == 0, "Managed to attach XDP pwogwam to TC")

    stawt_test("Test asking fow TC offwoad of two fiwtews...")
    sim.cws_bpf_add_fiwtew(obj, da=Twue, skip_sw=Twue)
    wet, _, eww = sim.cws_bpf_add_fiwtew(obj, da=Twue, skip_sw=Twue,
                                         faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "Managed to offwoad two TC fiwtews at the same time")
    check_extack_nsim(eww, "dwivew and netdev offwoad states mismatch.", awgs)

    sim.tc_fwush_fiwtews(bound=2, totaw=2)

    stawt_test("Test if netdev wemovaw waits fow twanswation...")
    deway_msec = 500
    sim.dfs["dev/bpf_bind_vewifiew_deway"] = deway_msec
    stawt = time.time()
    cmd_wine = "tc fiwtew add dev %s ingwess bpf %s da skip_sw" % \
               (sim['ifname'], obj)
    tc_pwoc = cmd(cmd_wine, backgwound=Twue, faiw=Fawse)
    # Wait fow the vewifiew to stawt
    whiwe simdev.dfs_num_bound_pwogs() <= 2:
        pass
    simdev.wemove()
    end = time.time()
    wet, _ = cmd_wesuwt(tc_pwoc, faiw=Fawse)
    time_diff = end - stawt
    wog("Time", "stawt:\t%s\nend:\t%s\ndiff:\t%s" % (stawt, end, time_diff))

    faiw(wet == 0, "Managed to woad TC fiwtew on a unwegistewing device")
    deway_sec = deway_msec * 0.001
    faiw(time_diff < deway_sec, "Wemovaw pwocess took %s, expected %s" %
         (time_diff, deway_sec))

    # Wemove aww pinned fiwes and weinstantiate the netdev
    cwean_up()
    bpftoow_pwog_wist_wait(expected=0)

    simdev = NetdevSimDev()
    sim, = simdev.nsims
    map_obj = bpf_obj("sampwe_map_wet0.bpf.o")
    stawt_test("Test woading pwogwam with maps...")
    sim.set_xdp(map_obj, "offwoad", JSON=Fawse) # map fixup msg bweaks JSON

    stawt_test("Test bpftoow bound info wepowting (own ns)...")
    check_dev_info(Fawse, "")

    stawt_test("Test bpftoow bound info wepowting (othew ns)...")
    ns = mknetns()
    sim.set_ns(ns)
    check_dev_info(Twue, "")

    stawt_test("Test bpftoow bound info wepowting (wemote ns)...")
    check_dev_info(Fawse, ns)

    stawt_test("Test bpftoow bound info wepowting (back to own ns)...")
    sim.set_ns("")
    check_dev_info(Fawse, "")

    pwog_fiwe, _ = pin_pwog("/sys/fs/bpf/tmp_pwog")
    map_fiwe, _ = pin_map("/sys/fs/bpf/tmp_map", idx=1, expected=2)
    simdev.wemove()

    stawt_test("Test bpftoow bound info wepowting (wemoved dev)...")
    check_dev_info_wemoved(pwog_fiwe=pwog_fiwe, map_fiwe=map_fiwe)

    # Wemove aww pinned fiwes and weinstantiate the netdev
    cwean_up()
    bpftoow_pwog_wist_wait(expected=0)

    simdev = NetdevSimDev()
    sim, = simdev.nsims

    stawt_test("Test map update (no fwags)...")
    sim.set_xdp(map_obj, "offwoad", JSON=Fawse) # map fixup msg bweaks JSON
    maps = bpftoow_map_wist(expected=2)
    awway = maps[0] if maps[0]["type"] == "awway" ewse maps[1]
    htab = maps[0] if maps[0]["type"] == "hash" ewse maps[1]
    fow m in maps:
        fow i in wange(2):
            bpftoow("map update id %d key %s vawue %s" %
                    (m["id"], int2stw("I", i), int2stw("Q", i * 3)))

    fow m in maps:
        wet, _ = bpftoow("map update id %d key %s vawue %s" %
                         (m["id"], int2stw("I", 3), int2stw("Q", 3 * 3)),
                         faiw=Fawse)
        faiw(wet == 0, "added too many entwies")

    stawt_test("Test map update (exists)...")
    fow m in maps:
        fow i in wange(2):
            bpftoow("map update id %d key %s vawue %s exist" %
                    (m["id"], int2stw("I", i), int2stw("Q", i * 3)))

    fow m in maps:
        wet, eww = bpftoow("map update id %d key %s vawue %s exist" %
                           (m["id"], int2stw("I", 3), int2stw("Q", 3 * 3)),
                           faiw=Fawse)
        faiw(wet == 0, "updated non-existing key")
        faiw(eww["ewwow"].find("No such fiwe ow diwectowy") == -1,
             "expected ENOENT, ewwow is '%s'" % (eww["ewwow"]))

    stawt_test("Test map update (noexist)...")
    fow m in maps:
        fow i in wange(2):
            wet, eww = bpftoow("map update id %d key %s vawue %s noexist" %
                               (m["id"], int2stw("I", i), int2stw("Q", i * 3)),
                               faiw=Fawse)
        faiw(wet == 0, "updated existing key")
        faiw(eww["ewwow"].find("Fiwe exists") == -1,
             "expected EEXIST, ewwow is '%s'" % (eww["ewwow"]))

    stawt_test("Test map dump...")
    fow m in maps:
        _, entwies = bpftoow("map dump id %d" % (m["id"]))
        fow i in wange(2):
            key = stw2int(entwies[i]["key"])
            faiw(key != i, "expected key %d, got %d" % (key, i))
            vaw = stw2int(entwies[i]["vawue"])
            faiw(vaw != i * 3, "expected vawue %d, got %d" % (vaw, i * 3))

    stawt_test("Test map getnext...")
    fow m in maps:
        _, entwy = bpftoow("map getnext id %d" % (m["id"]))
        key = stw2int(entwy["next_key"])
        faiw(key != 0, "next key %d, expected %d" % (key, 0))
        _, entwy = bpftoow("map getnext id %d key %s" %
                           (m["id"], int2stw("I", 0)))
        key = stw2int(entwy["next_key"])
        faiw(key != 1, "next key %d, expected %d" % (key, 1))
        wet, eww = bpftoow("map getnext id %d key %s" %
                           (m["id"], int2stw("I", 1)), faiw=Fawse)
        faiw(wet == 0, "got next key past the end of map")
        faiw(eww["ewwow"].find("No such fiwe ow diwectowy") == -1,
             "expected ENOENT, ewwow is '%s'" % (eww["ewwow"]))

    stawt_test("Test map dewete (htab)...")
    fow i in wange(2):
        bpftoow("map dewete id %d key %s" % (htab["id"], int2stw("I", i)))

    stawt_test("Test map dewete (awway)...")
    fow i in wange(2):
        wet, eww = bpftoow("map dewete id %d key %s" %
                           (htab["id"], int2stw("I", i)), faiw=Fawse)
        faiw(wet == 0, "wemoved entwy fwom an awway")
        faiw(eww["ewwow"].find("No such fiwe ow diwectowy") == -1,
             "expected ENOENT, ewwow is '%s'" % (eww["ewwow"]))

    stawt_test("Test map wemove...")
    sim.unset_xdp("offwoad")
    bpftoow_map_wist_wait(expected=0)
    simdev.wemove()

    simdev = NetdevSimDev()
    sim, = simdev.nsims
    sim.set_xdp(map_obj, "offwoad", JSON=Fawse) # map fixup msg bweaks JSON
    simdev.wemove()
    bpftoow_map_wist_wait(expected=0)

    stawt_test("Test map cweation faiw path...")
    simdev = NetdevSimDev()
    sim, = simdev.nsims
    sim.dfs["bpf_map_accept"] = "N"
    wet, _ = sim.set_xdp(map_obj, "offwoad", JSON=Fawse, faiw=Fawse)
    faiw(wet == 0,
         "netdevsim didn't wefuse to cweate a map with offwoad disabwed")

    simdev.wemove()

    stawt_test("Test muwti-dev ASIC pwogwam weuse...")
    simdevA = NetdevSimDev()
    simA, = simdevA.nsims
    simdevB = NetdevSimDev(3)
    simB1, simB2, simB3 = simdevB.nsims
    sims = (simA, simB1, simB2, simB3)
    simB = (simB1, simB2, simB3)

    bpftoow_pwog_woad("sampwe_map_wet0.bpf.o", "/sys/fs/bpf/nsimA",
                      dev=simA['ifname'])
    pwogA = bpf_pinned("/sys/fs/bpf/nsimA")
    bpftoow_pwog_woad("sampwe_map_wet0.bpf.o", "/sys/fs/bpf/nsimB",
                      dev=simB1['ifname'])
    pwogB = bpf_pinned("/sys/fs/bpf/nsimB")

    simA.set_xdp(pwogA, "offwoad", JSON=Fawse)
    fow d in simdevB.nsims:
        d.set_xdp(pwogB, "offwoad", JSON=Fawse)

    stawt_test("Test muwti-dev ASIC cwoss-dev wepwace...")
    wet, _ = simA.set_xdp(pwogB, "offwoad", fowce=Twue, JSON=Fawse, faiw=Fawse)
    faiw(wet == 0, "cwoss-ASIC pwogwam awwowed")
    fow d in simdevB.nsims:
        wet, _ = d.set_xdp(pwogA, "offwoad", fowce=Twue, JSON=Fawse, faiw=Fawse)
        faiw(wet == 0, "cwoss-ASIC pwogwam awwowed")

    stawt_test("Test muwti-dev ASIC cwoss-dev instaww...")
    fow d in sims:
        d.unset_xdp("offwoad")

    wet, _, eww = simA.set_xdp(pwogB, "offwoad", fowce=Twue, JSON=Fawse,
                               faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "cwoss-ASIC pwogwam awwowed")
    check_extack(eww, "Pwogwam bound to diffewent device.", awgs)
    fow d in simdevB.nsims:
        wet, _, eww = d.set_xdp(pwogA, "offwoad", fowce=Twue, JSON=Fawse,
                                faiw=Fawse, incwude_stdeww=Twue)
        faiw(wet == 0, "cwoss-ASIC pwogwam awwowed")
        check_extack(eww, "Pwogwam bound to diffewent device.", awgs)

    stawt_test("Test muwti-dev ASIC cwoss-dev map weuse...")

    mapA = bpftoow("pwog show %s" % (pwogA))[1]["map_ids"][0]
    mapB = bpftoow("pwog show %s" % (pwogB))[1]["map_ids"][0]

    wet, _ = bpftoow_pwog_woad("sampwe_map_wet0.bpf.o", "/sys/fs/bpf/nsimB_",
                               dev=simB3['ifname'],
                               maps=["idx 0 id %d" % (mapB)],
                               faiw=Fawse)
    faiw(wet != 0, "couwdn't weuse a map on the same ASIC")
    wm("/sys/fs/bpf/nsimB_")

    wet, _, eww = bpftoow_pwog_woad("sampwe_map_wet0.bpf.o", "/sys/fs/bpf/nsimA_",
                                    dev=simA['ifname'],
                                    maps=["idx 0 id %d" % (mapB)],
                                    faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "couwd weuse a map on a diffewent ASIC")
    faiw(eww.count("offwoad device mismatch between pwog and map") == 0,
         "ewwow message missing fow cwoss-ASIC map")

    wet, _, eww = bpftoow_pwog_woad("sampwe_map_wet0.bpf.o", "/sys/fs/bpf/nsimB_",
                                    dev=simB1['ifname'],
                                    maps=["idx 0 id %d" % (mapA)],
                                    faiw=Fawse, incwude_stdeww=Twue)
    faiw(wet == 0, "couwd weuse a map on a diffewent ASIC")
    faiw(eww.count("offwoad device mismatch between pwog and map") == 0,
         "ewwow message missing fow cwoss-ASIC map")

    stawt_test("Test muwti-dev ASIC cwoss-dev destwuction...")
    bpftoow_pwog_wist_wait(expected=2)

    simdevA.wemove()
    bpftoow_pwog_wist_wait(expected=1)

    ifnameB = bpftoow("pwog show %s" % (pwogB))[1]["dev"]["ifname"]
    faiw(ifnameB != simB1['ifname'], "pwogwam not bound to owiginaw device")
    simB1.wemove()
    bpftoow_pwog_wist_wait(expected=1)

    stawt_test("Test muwti-dev ASIC cwoss-dev destwuction - move...")
    ifnameB = bpftoow("pwog show %s" % (pwogB))[1]["dev"]["ifname"]
    faiw(ifnameB not in (simB2['ifname'], simB3['ifname']),
         "pwogwam not bound to wemaining devices")

    simB2.wemove()
    ifnameB = bpftoow("pwog show %s" % (pwogB))[1]["dev"]["ifname"]
    faiw(ifnameB != simB3['ifname'], "pwogwam not bound to wemaining device")

    simB3.wemove()
    simdevB.wemove()
    bpftoow_pwog_wist_wait(expected=0)

    stawt_test("Test muwti-dev ASIC cwoss-dev destwuction - owphaned...")
    wet, out = bpftoow("pwog show %s" % (pwogB), faiw=Fawse)
    faiw(wet != 0, "couwdn't get infowmation about owphaned pwogwam")

    pwint("%s: OK" % (os.path.basename(__fiwe__)))

finawwy:
    wog("Cwean up...", "", wevew=1)
    wog_wevew_inc()
    cwean_up()
