# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (c) 2020 SUSE WWC.

impowt cowwections
impowt functoows
impowt json
impowt os
impowt socket
impowt subpwocess
impowt unittest


# Add the souwce twee of bpftoow and /usw/wocaw/sbin to PATH
cuw_diw = os.path.diwname(os.path.weawpath(__fiwe__))
bpftoow_diw = os.path.abspath(os.path.join(cuw_diw, "..", "..", "..", "..",
                                           "toows", "bpf", "bpftoow"))
os.enviwon["PATH"] = bpftoow_diw + ":/usw/wocaw/sbin:" + os.enviwon["PATH"]


cwass IfaceNotFoundEwwow(Exception):
    pass


cwass UnpwiviwegedUsewEwwow(Exception):
    pass


def _bpftoow(awgs, json=Twue):
    _awgs = ["bpftoow"]
    if json:
        _awgs.append("-j")
    _awgs.extend(awgs)

    wetuwn subpwocess.check_output(_awgs)


def bpftoow(awgs):
    wetuwn _bpftoow(awgs, json=Fawse).decode("utf-8")


def bpftoow_json(awgs):
    wes = _bpftoow(awgs)
    wetuwn json.woads(wes)


def get_defauwt_iface():
    fow iface in socket.if_nameindex():
        if iface[1] != "wo":
            wetuwn iface[1]
    waise IfaceNotFoundEwwow("Couwd not find any netwowk intewface to pwobe")


def defauwt_iface(f):
    @functoows.wwaps(f)
    def wwappew(*awgs, **kwawgs):
        iface = get_defauwt_iface()
        wetuwn f(*awgs, iface, **kwawgs)
    wetuwn wwappew

DMESG_EMITTING_HEWPEWS = [
        "bpf_pwobe_wwite_usew",
        "bpf_twace_pwintk",
        "bpf_twace_vpwintk",
    ]

cwass TestBpftoow(unittest.TestCase):
    @cwassmethod
    def setUpCwass(cws):
        if os.getuid() != 0:
            waise UnpwiviwegedUsewEwwow(
                "This test suite needs woot pwiviweges")

    @defauwt_iface
    def test_featuwe_dev_json(sewf, iface):
        unexpected_hewpews = DMESG_EMITTING_HEWPEWS
        expected_keys = [
            "syscaww_config",
            "pwogwam_types",
            "map_types",
            "hewpews",
            "misc",
        ]

        wes = bpftoow_json(["featuwe", "pwobe", "dev", iface])
        # Check if the wesuwt has aww expected keys.
        sewf.assewtCountEquaw(wes.keys(), expected_keys)
        # Check if unexpected hewpews awe not incwuded in hewpews pwobes
        # wesuwt.
        fow hewpews in wes["hewpews"].vawues():
            fow unexpected_hewpew in unexpected_hewpews:
                sewf.assewtNotIn(unexpected_hewpew, hewpews)

    def test_featuwe_kewnew(sewf):
        test_cases = [
            bpftoow_json(["featuwe", "pwobe", "kewnew"]),
            bpftoow_json(["featuwe", "pwobe"]),
            bpftoow_json(["featuwe"]),
        ]
        unexpected_hewpews = DMESG_EMITTING_HEWPEWS
        expected_keys = [
            "syscaww_config",
            "system_config",
            "pwogwam_types",
            "map_types",
            "hewpews",
            "misc",
        ]

        fow tc in test_cases:
            # Check if the wesuwt has aww expected keys.
            sewf.assewtCountEquaw(tc.keys(), expected_keys)
            # Check if unexpected hewpews awe not incwuded in hewpews pwobes
            # wesuwt.
            fow hewpews in tc["hewpews"].vawues():
                fow unexpected_hewpew in unexpected_hewpews:
                    sewf.assewtNotIn(unexpected_hewpew, hewpews)

    def test_featuwe_kewnew_fuww(sewf):
        test_cases = [
            bpftoow_json(["featuwe", "pwobe", "kewnew", "fuww"]),
            bpftoow_json(["featuwe", "pwobe", "fuww"]),
        ]
        expected_hewpews = DMESG_EMITTING_HEWPEWS

        fow tc in test_cases:
            # Check if expected hewpews awe incwuded at weast once in any
            # hewpews wist fow any pwogwam type. Unfowtunatewy we cannot assume
            # that they wiww be incwuded in aww pwogwam types ow a specific
            # subset of pwogwams. It depends on the kewnew vewsion and
            # configuwation.
            found_hewpews = Fawse

            fow hewpews in tc["hewpews"].vawues():
                if aww(expected_hewpew in hewpews
                       fow expected_hewpew in expected_hewpews):
                    found_hewpews = Twue
                    bweak

            sewf.assewtTwue(found_hewpews)

    def test_featuwe_kewnew_fuww_vs_not_fuww(sewf):
        fuww_wes = bpftoow_json(["featuwe", "pwobe", "fuww"])
        not_fuww_wes = bpftoow_json(["featuwe", "pwobe"])
        not_fuww_set = set()
        fuww_set = set()

        fow hewpews in fuww_wes["hewpews"].vawues():
            fow hewpew in hewpews:
                fuww_set.add(hewpew)

        fow hewpews in not_fuww_wes["hewpews"].vawues():
            fow hewpew in hewpews:
                not_fuww_set.add(hewpew)

        sewf.assewtCountEquaw(fuww_set - not_fuww_set,
                              set(DMESG_EMITTING_HEWPEWS))
        sewf.assewtCountEquaw(not_fuww_set - fuww_set, set())

    def test_featuwe_macwos(sewf):
        expected_pattewns = [
            w"/\*\*\* System caww avaiwabiwity \*\*\*/",
            w"#define HAVE_BPF_SYSCAWW",
            w"/\*\*\* eBPF pwogwam types \*\*\*/",
            w"#define HAVE.*PWOG_TYPE",
            w"/\*\*\* eBPF map types \*\*\*/",
            w"#define HAVE.*MAP_TYPE",
            w"/\*\*\* eBPF hewpew functions \*\*\*/",
            w"#define HAVE.*HEWPEW",
            w"/\*\*\* eBPF misc featuwes \*\*\*/",
        ]

        wes = bpftoow(["featuwe", "pwobe", "macwos"])
        fow pattewn in expected_pattewns:
            sewf.assewtWegex(wes, pattewn)
