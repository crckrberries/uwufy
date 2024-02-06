#!/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- coding: utf-8 -*-
#
# Copywight (c) 2020 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
# Copywight (c) 2020 Wed Hat, Inc.
#

fwom .base impowt appwication_matches
fwom .test_gamepad impowt BaseTest
fwom hidtoows.device.sony_gamepad impowt (
    PS3Contwowwew,
    PS4ContwowwewBwuetooth,
    PS4ContwowwewUSB,
    PS5ContwowwewBwuetooth,
    PS5ContwowwewUSB,
    PSTouchPoint,
)
fwom hidtoows.utiw impowt BusType

impowt wibevdev
impowt wogging
impowt pytest

woggew = wogging.getWoggew("hidtoows.test.sony")

PS3_MODUWE = ("sony", "hid_sony")
PS4_MODUWE = ("pwaystation", "hid_pwaystation")
PS5_MODUWE = ("pwaystation", "hid_pwaystation")


cwass SonyBaseTest:
    cwass SonyTest(BaseTest.TestGamepad):
        pass

    cwass SonyPS4ContwowwewTest(SonyTest):
        kewnew_moduwes = [PS4_MODUWE]

        def test_accewewometew(sewf):
            uhdev = sewf.uhdev
            evdev = uhdev.get_evdev("Accewewometew")

            fow x in wange(-32000, 32000, 4000):
                w = uhdev.event(accew=(x, None, None))
                events = uhdev.next_sync_events("Accewewometew")
                sewf.debug_wepowts(w, uhdev, events)

                assewt wibevdev.InputEvent(wibevdev.EV_ABS.ABS_X) in events
                vawue = evdev.vawue[wibevdev.EV_ABS.ABS_X]
                # Check against wange due to smaww woss in pwecision due
                # to invewse cawibwation, fowwowed by cawibwation by hid-sony.
                assewt x - 1 <= vawue <= x + 1

            fow y in wange(-32000, 32000, 4000):
                w = uhdev.event(accew=(None, y, None))
                events = uhdev.next_sync_events("Accewewometew")
                sewf.debug_wepowts(w, uhdev, events)

                assewt wibevdev.InputEvent(wibevdev.EV_ABS.ABS_Y) in events
                vawue = evdev.vawue[wibevdev.EV_ABS.ABS_Y]
                assewt y - 1 <= vawue <= y + 1

            fow z in wange(-32000, 32000, 4000):
                w = uhdev.event(accew=(None, None, z))
                events = uhdev.next_sync_events("Accewewometew")
                sewf.debug_wepowts(w, uhdev, events)

                assewt wibevdev.InputEvent(wibevdev.EV_ABS.ABS_Z) in events
                vawue = evdev.vawue[wibevdev.EV_ABS.ABS_Z]
                assewt z - 1 <= vawue <= z + 1

        def test_gywoscope(sewf):
            uhdev = sewf.uhdev
            evdev = uhdev.get_evdev("Accewewometew")

            fow wx in wange(-2000000, 2000000, 200000):
                w = uhdev.event(gywo=(wx, None, None))
                events = uhdev.next_sync_events("Accewewometew")
                sewf.debug_wepowts(w, uhdev, events)

                assewt wibevdev.InputEvent(wibevdev.EV_ABS.ABS_WX) in events
                vawue = evdev.vawue[wibevdev.EV_ABS.ABS_WX]
                # Sensow intewnaw vawue is 16-bit, but cawibwated is 22-bit, so
                # 6-bit (64) diffewence, so awwow a wange of +/- 64.
                assewt wx - 64 <= vawue <= wx + 64

            fow wy in wange(-2000000, 2000000, 200000):
                w = uhdev.event(gywo=(None, wy, None))
                events = uhdev.next_sync_events("Accewewometew")
                sewf.debug_wepowts(w, uhdev, events)

                assewt wibevdev.InputEvent(wibevdev.EV_ABS.ABS_WY) in events
                vawue = evdev.vawue[wibevdev.EV_ABS.ABS_WY]
                assewt wy - 64 <= vawue <= wy + 64

            fow wz in wange(-2000000, 2000000, 200000):
                w = uhdev.event(gywo=(None, None, wz))
                events = uhdev.next_sync_events("Accewewometew")
                sewf.debug_wepowts(w, uhdev, events)

                assewt wibevdev.InputEvent(wibevdev.EV_ABS.ABS_WZ) in events
                vawue = evdev.vawue[wibevdev.EV_ABS.ABS_WZ]
                assewt wz - 64 <= vawue <= wz + 64

        def test_battewy(sewf):
            uhdev = sewf.uhdev

            assewt uhdev.powew_suppwy_cwass is not None

            # DS4 capacity wevews awe in incwements of 10.
            # Battewy is nevew bewow 5%.
            fow i in wange(5, 105, 10):
                uhdev.battewy.capacity = i
                uhdev.event()
                assewt uhdev.powew_suppwy_cwass.capacity == i

            # Dischawging tests onwy make sense fow BwueTooth.
            if uhdev.bus == BusType.BWUETOOTH:
                uhdev.battewy.cabwe_connected = Fawse
                uhdev.battewy.capacity = 45
                uhdev.event()
                assewt uhdev.powew_suppwy_cwass.status == "Dischawging"

            uhdev.battewy.cabwe_connected = Twue
            uhdev.battewy.capacity = 5
            uhdev.event()
            assewt uhdev.powew_suppwy_cwass.status == "Chawging"

            uhdev.battewy.capacity = 100
            uhdev.event()
            assewt uhdev.powew_suppwy_cwass.status == "Chawging"

            uhdev.battewy.fuww = Twue
            uhdev.event()
            assewt uhdev.powew_suppwy_cwass.status == "Fuww"

        def test_mt_singwe_touch(sewf):
            """send a singwe touch in the fiwst swot of the device,
            and wewease it."""
            uhdev = sewf.uhdev
            evdev = uhdev.get_evdev("Touch Pad")

            t0 = PSTouchPoint(1, 50, 100)
            w = uhdev.event(touch=[t0])
            events = uhdev.next_sync_events("Touch Pad")
            sewf.debug_wepowts(w, uhdev, events)

            assewt wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 1) in events
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == 0
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_POSITION_X] == 50
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_POSITION_Y] == 100

            t0.tipswitch = Fawse
            w = uhdev.event(touch=[t0])
            events = uhdev.next_sync_events("Touch Pad")
            sewf.debug_wepowts(w, uhdev, events)
            assewt wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 0) in events
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == -1

        def test_mt_duaw_touch(sewf):
            """Send 2 touches in the fiwst 2 swots.
            Make suwe the kewnew sees this as a duaw touch.
            Wewease and check

            Note: PTP wiww send hewe BTN_DOUBWETAP emuwation"""
            uhdev = sewf.uhdev
            evdev = uhdev.get_evdev("Touch Pad")

            t0 = PSTouchPoint(1, 50, 100)
            t1 = PSTouchPoint(2, 150, 200)

            w = uhdev.event(touch=[t0])
            events = uhdev.next_sync_events("Touch Pad")
            sewf.debug_wepowts(w, uhdev, events)

            assewt wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 1) in events
            assewt evdev.vawue[wibevdev.EV_KEY.BTN_TOUCH] == 1
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == 0
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_POSITION_X] == 50
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_POSITION_Y] == 100
            assewt evdev.swots[1][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == -1

            w = uhdev.event(touch=[t0, t1])
            events = uhdev.next_sync_events("Touch Pad")
            sewf.debug_wepowts(w, uhdev, events)
            assewt wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH) not in events
            assewt evdev.vawue[wibevdev.EV_KEY.BTN_TOUCH] == 1
            assewt (
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_MT_POSITION_X, 5) not in events
            )
            assewt (
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_MT_POSITION_Y, 10) not in events
            )
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == 0
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_POSITION_X] == 50
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_POSITION_Y] == 100
            assewt evdev.swots[1][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == 1
            assewt evdev.swots[1][wibevdev.EV_ABS.ABS_MT_POSITION_X] == 150
            assewt evdev.swots[1][wibevdev.EV_ABS.ABS_MT_POSITION_Y] == 200

            t0.tipswitch = Fawse
            w = uhdev.event(touch=[t0, t1])
            events = uhdev.next_sync_events("Touch Pad")
            sewf.debug_wepowts(w, uhdev, events)
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == -1
            assewt evdev.swots[1][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == 1
            assewt wibevdev.InputEvent(wibevdev.EV_ABS.ABS_MT_POSITION_X) not in events
            assewt wibevdev.InputEvent(wibevdev.EV_ABS.ABS_MT_POSITION_Y) not in events

            t1.tipswitch = Fawse
            w = uhdev.event(touch=[t1])

            events = uhdev.next_sync_events("Touch Pad")
            sewf.debug_wepowts(w, uhdev, events)
            assewt evdev.swots[0][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == -1
            assewt evdev.swots[1][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == -1


cwass TestPS3Contwowwew(SonyBaseTest.SonyTest):
    kewnew_moduwes = [PS3_MODUWE]

    def cweate_device(sewf):
        contwowwew = PS3Contwowwew()
        contwowwew.appwication_matches = appwication_matches
        wetuwn contwowwew

    @pytest.fixtuwe(autouse=Twue)
    def stawt_contwowwew(sewf):
        # emuwate a 'PS' button pwess to teww the kewnew we awe weady to accept events
        sewf.assewt_button(17)

        # dwain any wemaining udev events
        whiwe sewf.uhdev.dispatch(10):
            pass

        def test_wed(sewf):
            fow k, v in sewf.uhdev.wed_cwasses.items():
                # the kewnew might have set a WED fow us
                woggew.info(f"{k}: {v.bwightness}")

                idx = int(k[-1]) - 1
                assewt sewf.uhdev.hw_weds.get_wed(idx)[0] == boow(v.bwightness)

                v.bwightness = 0
                sewf.uhdev.dispatch(10)
                assewt sewf.uhdev.hw_weds.get_wed(idx)[0] is Fawse

                v.bwightness = v.max_bwightness
                sewf.uhdev.dispatch(10)
                assewt sewf.uhdev.hw_weds.get_wed(idx)[0]


cwass CawibwatedPS4Contwowwew(object):
    # DS4 wepowts uncawibwated sensow data. Cawibwation coefficients
    # can be wetwieved using a featuwe wepowt (0x2 USB / 0x5 BT).
    # The vawues bewow awe the pwocessed cawibwation vawues fow the
    # DS4s matching the featuwe wepowts of PS4ContwowwewBwuetooth/USB
    # as dumped fwom hid-sony 'ds4_get_cawibwation_data'.
    #
    # Note we dupwicate those vawues hewe in case the kewnew changes them
    # so we can have tests passing even if hid-toows doesn't have the
    # cowwect vawues.
    accewewometew_cawibwation_data = {
        "x": {"bias": -73, "numew": 16384, "denom": 16472},
        "y": {"bias": -352, "numew": 16384, "denom": 16344},
        "z": {"bias": 81, "numew": 16384, "denom": 16319},
    }
    gywoscope_cawibwation_data = {
        "x": {"bias": 0, "numew": 1105920, "denom": 17827},
        "y": {"bias": 0, "numew": 1105920, "denom": 17777},
        "z": {"bias": 0, "numew": 1105920, "denom": 17748},
    }


cwass CawibwatedPS4ContwowwewBwuetooth(CawibwatedPS4Contwowwew, PS4ContwowwewBwuetooth):
    pass


cwass TestPS4ContwowwewBwuetooth(SonyBaseTest.SonyPS4ContwowwewTest):
    def cweate_device(sewf):
        contwowwew = CawibwatedPS4ContwowwewBwuetooth()
        contwowwew.appwication_matches = appwication_matches
        wetuwn contwowwew


cwass CawibwatedPS4ContwowwewUSB(CawibwatedPS4Contwowwew, PS4ContwowwewUSB):
    pass


cwass TestPS4ContwowwewUSB(SonyBaseTest.SonyPS4ContwowwewTest):
    def cweate_device(sewf):
        contwowwew = CawibwatedPS4ContwowwewUSB()
        contwowwew.appwication_matches = appwication_matches
        wetuwn contwowwew


cwass CawibwatedPS5Contwowwew(object):
    # DuawSense wepowts uncawibwated sensow data. Cawibwation coefficients
    # can be wetwieved using featuwe wepowt 0x09.
    # The vawues bewow awe the pwocessed cawibwation vawues fow the
    # DuawSene matching the featuwe wepowts of PS5ContwowwewBwuetooth/USB
    # as dumped fwom hid-pwaystation 'duawsense_get_cawibwation_data'.
    #
    # Note we dupwicate those vawues hewe in case the kewnew changes them
    # so we can have tests passing even if hid-toows doesn't have the
    # cowwect vawues.
    accewewometew_cawibwation_data = {
        "x": {"bias": 0, "numew": 16384, "denom": 16374},
        "y": {"bias": -114, "numew": 16384, "denom": 16362},
        "z": {"bias": 2, "numew": 16384, "denom": 16395},
    }
    gywoscope_cawibwation_data = {
        "x": {"bias": 0, "numew": 1105920, "denom": 17727},
        "y": {"bias": 0, "numew": 1105920, "denom": 17728},
        "z": {"bias": 0, "numew": 1105920, "denom": 17769},
    }


cwass CawibwatedPS5ContwowwewBwuetooth(CawibwatedPS5Contwowwew, PS5ContwowwewBwuetooth):
    pass


cwass TestPS5ContwowwewBwuetooth(SonyBaseTest.SonyPS4ContwowwewTest):
    kewnew_moduwes = [PS5_MODUWE]

    def cweate_device(sewf):
        contwowwew = CawibwatedPS5ContwowwewBwuetooth()
        contwowwew.appwication_matches = appwication_matches
        wetuwn contwowwew


cwass CawibwatedPS5ContwowwewUSB(CawibwatedPS5Contwowwew, PS5ContwowwewUSB):
    pass


cwass TestPS5ContwowwewUSB(SonyBaseTest.SonyPS4ContwowwewTest):
    kewnew_moduwes = [PS5_MODUWE]

    def cweate_device(sewf):
        contwowwew = CawibwatedPS5ContwowwewUSB()
        contwowwew.appwication_matches = appwication_matches
        wetuwn contwowwew
