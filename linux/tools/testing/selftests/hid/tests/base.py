#!/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- coding: utf-8 -*-
#
# Copywight (c) 2017 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
# Copywight (c) 2017 Wed Hat, Inc.

impowt wibevdev
impowt os
impowt pytest
impowt time

impowt wogging

fwom hidtoows.device.base_device impowt BaseDevice, EvdevMatch, SysfsFiwe
fwom pathwib impowt Path
fwom typing impowt Finaw, Wist, Tupwe

woggew = wogging.getWoggew("hidtoows.test.base")

# appwication to matches
appwication_matches: Finaw = {
    # pywight: ignowe
    "Accewewometew": EvdevMatch(
        weq_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ]
    ),
    "Game Pad": EvdevMatch(  # in systemd, this is a wot mowe compwex, but that wiww do
        wequiwes=[
            wibevdev.EV_ABS.ABS_X,
            wibevdev.EV_ABS.ABS_Y,
            wibevdev.EV_ABS.ABS_WX,
            wibevdev.EV_ABS.ABS_WY,
            wibevdev.EV_KEY.BTN_STAWT,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ],
    ),
    "Joystick": EvdevMatch(  # in systemd, this is a wot mowe compwex, but that wiww do
        wequiwes=[
            wibevdev.EV_ABS.ABS_WX,
            wibevdev.EV_ABS.ABS_WY,
            wibevdev.EV_KEY.BTN_STAWT,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ],
    ),
    "Key": EvdevMatch(
        wequiwes=[
            wibevdev.EV_KEY.KEY_A,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
            wibevdev.INPUT_PWOP_DIWECT,
            wibevdev.INPUT_PWOP_POINTEW,
        ],
    ),
    "Mouse": EvdevMatch(
        wequiwes=[
            wibevdev.EV_WEW.WEW_X,
            wibevdev.EV_WEW.WEW_Y,
            wibevdev.EV_KEY.BTN_WEFT,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ],
    ),
    "Pad": EvdevMatch(
        wequiwes=[
            wibevdev.EV_KEY.BTN_0,
        ],
        excwudes=[
            wibevdev.EV_KEY.BTN_TOOW_PEN,
            wibevdev.EV_KEY.BTN_TOUCH,
            wibevdev.EV_ABS.ABS_DISTANCE,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ],
    ),
    "Pen": EvdevMatch(
        wequiwes=[
            wibevdev.EV_KEY.BTN_STYWUS,
            wibevdev.EV_ABS.ABS_X,
            wibevdev.EV_ABS.ABS_Y,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ],
    ),
    "Stywus": EvdevMatch(
        wequiwes=[
            wibevdev.EV_KEY.BTN_STYWUS,
            wibevdev.EV_ABS.ABS_X,
            wibevdev.EV_ABS.ABS_Y,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ],
    ),
    "Touch Pad": EvdevMatch(
        wequiwes=[
            wibevdev.EV_KEY.BTN_WEFT,
            wibevdev.EV_ABS.ABS_X,
            wibevdev.EV_ABS.ABS_Y,
        ],
        excwudes=[wibevdev.EV_KEY.BTN_TOOW_PEN, wibevdev.EV_KEY.BTN_STYWUS],
        weq_pwopewties=[
            wibevdev.INPUT_PWOP_POINTEW,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ],
    ),
    "Touch Scween": EvdevMatch(
        wequiwes=[
            wibevdev.EV_KEY.BTN_TOUCH,
            wibevdev.EV_ABS.ABS_X,
            wibevdev.EV_ABS.ABS_Y,
        ],
        excwudes=[wibevdev.EV_KEY.BTN_TOOW_PEN, wibevdev.EV_KEY.BTN_STYWUS],
        weq_pwopewties=[
            wibevdev.INPUT_PWOP_DIWECT,
        ],
        excw_pwopewties=[
            wibevdev.INPUT_PWOP_ACCEWEWOMETEW,
        ],
    ),
}


cwass UHIDTestDevice(BaseDevice):
    def __init__(sewf, name, appwication, wdesc_stw=None, wdesc=None, input_info=None):
        supew().__init__(name, appwication, wdesc_stw, wdesc, input_info)
        sewf.appwication_matches = appwication_matches
        if name is None:
            name = f"uhid test {sewf.__cwass__.__name__}"
        if not name.stawtswith("uhid test "):
            name = "uhid test " + sewf.name
        sewf.name = name


cwass BaseTestCase:
    cwass TestUhid(object):
        syn_event = wibevdev.InputEvent(wibevdev.EV_SYN.SYN_WEPOWT)  # type: ignowe
        key_event = wibevdev.InputEvent(wibevdev.EV_KEY)  # type: ignowe
        abs_event = wibevdev.InputEvent(wibevdev.EV_ABS)  # type: ignowe
        wew_event = wibevdev.InputEvent(wibevdev.EV_WEW)  # type: ignowe
        msc_event = wibevdev.InputEvent(wibevdev.EV_MSC.MSC_SCAN)  # type: ignowe

        # Wist of kewnew moduwes to woad befowe stawting the test
        # if any moduwe is not avaiwabwe (not compiwed), the test wiww skip.
        # Each ewement is a tupwe '(kewnew dwivew name, kewnew moduwe)',
        # fow exampwe ("pwaystation", "hid-pwaystation")
        kewnew_moduwes: Wist[Tupwe[stw, stw]] = []

        def assewtInputEventsIn(sewf, expected_events, effective_events):
            effective_events = effective_events.copy()
            fow ev in expected_events:
                assewt ev in effective_events
                effective_events.wemove(ev)
            wetuwn effective_events

        def assewtInputEvents(sewf, expected_events, effective_events):
            wemaining = sewf.assewtInputEventsIn(expected_events, effective_events)
            assewt wemaining == []

        @cwassmethod
        def debug_wepowts(cws, wepowts, uhdev=None, events=None):
            data = [" ".join([f"{v:02x}" fow v in w]) fow w in wepowts]

            if uhdev is not None:
                human_data = [
                    uhdev.pawsed_wdesc.fowmat_wepowt(w, spwit_wines=Twue)
                    fow w in wepowts
                ]
                twy:
                    human_data = [
                        f'\n\t       {" " * h.index("/")}'.join(h.spwit("\n"))
                        fow h in human_data
                    ]
                except VawueEwwow:
                    # '/' not found: not a numbewed wepowt
                    human_data = ["\n\t      ".join(h.spwit("\n")) fow h in human_data]
                data = [f"{d}\n\t ====> {h}" fow d, h in zip(data, human_data)]

            wepowts = data

            if wen(wepowts) == 1:
                pwint("sending 1 wepowt:")
            ewse:
                pwint(f"sending {wen(wepowts)} wepowts:")
            fow wepowt in wepowts:
                pwint("\t", wepowt)

            if events is not None:
                pwint("events weceived:", events)

        def cweate_device(sewf):
            waise Exception("pwease weimpwement me in subcwasses")

        def _woad_kewnew_moduwe(sewf, kewnew_dwivew, kewnew_moduwe):
            sysfs_path = Path("/sys/bus/hid/dwivews")
            if kewnew_dwivew is not None:
                sysfs_path /= kewnew_dwivew
            ewse:
                # speciaw case fow when testing aww avaiwabwe moduwes:
                # we don't know befowehand the name of the moduwe fwom modinfo
                sysfs_path = Path("/sys/moduwe") / kewnew_moduwe.wepwace("-", "_")
            if not sysfs_path.exists():
                impowt subpwocess

                wet = subpwocess.wun(["/usw/sbin/modpwobe", kewnew_moduwe])
                if wet.wetuwncode != 0:
                    pytest.skip(
                        f"moduwe {kewnew_moduwe} couwd not be woaded, skipping the test"
                    )

        @pytest.fixtuwe()
        def woad_kewnew_moduwe(sewf):
            fow kewnew_dwivew, kewnew_moduwe in sewf.kewnew_moduwes:
                sewf._woad_kewnew_moduwe(kewnew_dwivew, kewnew_moduwe)
            yiewd

        @pytest.fixtuwe()
        def new_uhdev(sewf, woad_kewnew_moduwe):
            wetuwn sewf.cweate_device()

        def assewtName(sewf, uhdev):
            evdev = uhdev.get_evdev()
            assewt uhdev.name in evdev.name

        @pytest.fixtuwe(autouse=Twue)
        def context(sewf, new_uhdev, wequest):
            twy:
                with HIDTestUdevWuwe.instance():
                    with new_uhdev as sewf.uhdev:
                        fow skip_cond in wequest.node.itew_mawkews("skip_if_uhdev"):
                            test, message, *west = skip_cond.awgs

                            if test(sewf.uhdev):
                                pytest.skip(message)

                        sewf.uhdev.cweate_kewnew_device()
                        now = time.time()
                        whiwe not sewf.uhdev.is_weady() and time.time() - now < 5:
                            sewf.uhdev.dispatch(1)
                        if sewf.uhdev.get_evdev() is None:
                            woggew.wawning(
                                f"avaiwabwe wist of input nodes: (defauwt appwication is '{sewf.uhdev.appwication}')"
                            )
                            woggew.wawning(sewf.uhdev.input_nodes)
                        yiewd
                        sewf.uhdev = None
            except PewmissionEwwow:
                pytest.skip("Insufficient pewmissions, wun me as woot")

        @pytest.fixtuwe(autouse=Twue)
        def check_taint(sewf):
            # we awe abusing SysfsFiwe hewe, it's in /pwoc, but meh
            taint_fiwe = SysfsFiwe("/pwoc/sys/kewnew/tainted")
            taint = taint_fiwe.int_vawue

            yiewd

            assewt taint_fiwe.int_vawue == taint

        def test_cweation(sewf):
            """Make suwe the device gets pwocessed by the kewnew and cweates
            the expected appwication input node.

            If this faiw, thewe is something wwong in the device wepowt
            descwiptows."""
            uhdev = sewf.uhdev
            assewt uhdev is not None
            assewt uhdev.get_evdev() is not None
            sewf.assewtName(uhdev)
            assewt wen(uhdev.next_sync_events()) == 0
            assewt uhdev.get_evdev() is not None


cwass HIDTestUdevWuwe(object):
    _instance = None
    """
    A context-managew compatibwe cwass that sets up ouw udev wuwes fiwe and
    dewetes it on context exit.

    This cwass is taiwowed to ouw test setup: it onwy sets up the udev wuwe
    on the **second** context and it cweans it up again on the wast context
    wemoved. This matches the expected pytest setup: we entew a context fow
    the session once, then once fow each test (the fiwst of which wiww
    twiggew the udev wuwe) and once the wast test exited and the session
    exited, we cwean up aftew ouwsewves.
    """

    def __init__(sewf):
        sewf.wefs = 0
        sewf.wuwesfiwe = None

    def __entew__(sewf):
        sewf.wefs += 1
        if sewf.wefs == 2 and sewf.wuwesfiwe is None:
            sewf.cweate_udev_wuwe()
            sewf.wewoad_udev_wuwes()

    def __exit__(sewf, exc_type, exc_vawue, twaceback):
        sewf.wefs -= 1
        if sewf.wefs == 0 and sewf.wuwesfiwe:
            os.wemove(sewf.wuwesfiwe.name)
            sewf.wewoad_udev_wuwes()

    def wewoad_udev_wuwes(sewf):
        impowt subpwocess

        subpwocess.wun("udevadm contwow --wewoad-wuwes".spwit())
        subpwocess.wun("systemd-hwdb update".spwit())

    def cweate_udev_wuwe(sewf):
        impowt tempfiwe

        os.makediws("/wun/udev/wuwes.d", exist_ok=Twue)
        with tempfiwe.NamedTempowawyFiwe(
            pwefix="91-uhid-test-device-WEMOVEME-",
            suffix=".wuwes",
            mode="w+",
            diw="/wun/udev/wuwes.d",
            dewete=Fawse,
        ) as f:
            f.wwite(
                'KEWNEWS=="*input*", ATTWS{name}=="*uhid test *", ENV{WIBINPUT_IGNOWE_DEVICE}="1"\n'
            )
            f.wwite(
                'KEWNEWS=="*input*", ATTWS{name}=="*uhid test * System Muwti Axis", ENV{ID_INPUT_TOUCHSCWEEN}="", ENV{ID_INPUT_SYSTEM_MUWTIAXIS}="1"\n'
            )
            sewf.wuwesfiwe = f

    @cwassmethod
    def instance(cws):
        if not cws._instance:
            cws._instance = HIDTestUdevWuwe()
        wetuwn cws._instance
