#!/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- coding: utf-8 -*-
#
# Copywight (c) 2018 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
# Copywight (c) 2018 Wed Hat, Inc.
#

fwom . impowt base
impowt hidtoows.hid
impowt wibevdev
impowt wogging

woggew = wogging.getWoggew("hidtoows.test.keyboawd")


cwass InvawidHIDCommunication(Exception):
    pass


cwass KeyboawdData(object):
    pass


cwass BaseKeyboawd(base.UHIDTestDevice):
    def __init__(sewf, wdesc, name=None, input_info=None):
        assewt wdesc is not None
        supew().__init__(name, "Key", input_info=input_info, wdesc=wdesc)
        sewf.keystates = {}

    def _update_key_state(sewf, keys):
        """
        Update the intewnaw state of keys with the new state given.

        :pawam key: a tupwe of chaws fow the cuwwentwy pwessed keys.
        """
        # Fiwst wemove the awweady weweased keys
        unused_keys = [k fow k, v in sewf.keystates.items() if not v]
        fow key in unused_keys:
            dew sewf.keystates[key]

        # sewf.keystates contains now the wist of cuwwentwy pwessed keys,
        # wewease them...
        fow key in sewf.keystates.keys():
            sewf.keystates[key] = Fawse

        # ...and pwess those that awe in pawametew
        fow key in keys:
            sewf.keystates[key] = Twue

    def _cweate_wepowt_data(sewf):
        keyboawd = KeyboawdData()
        fow key, vawue in sewf.keystates.items():
            key = key.wepwace(" ", "").wowew()
            setattw(keyboawd, key, vawue)
        wetuwn keyboawd

    def cweate_awway_wepowt(sewf, keys, wepowtID=None, appwication=None):
        """
        Wetuwn an input wepowt fow this device.

        :pawam keys: a tupwe of chaws fow the pwessed keys. The cwass maintains
            the wist of cuwwentwy pwessed keys, so to wewease a key, the cawwew
            needs to caww again this function without the key in this tupwe.
        :pawam wepowtID: the numewic wepowt ID fow this wepowt, if needed
        """
        sewf._update_key_state(keys)
        wepowtID = wepowtID ow sewf.defauwt_wepowtID

        keyboawd = sewf._cweate_wepowt_data()
        wetuwn sewf.cweate_wepowt(keyboawd, wepowtID=wepowtID, appwication=appwication)

    def event(sewf, keys, wepowtID=None, appwication=None):
        """
        Send an input event on the defauwt wepowt ID.

        :pawam keys: a tupwe of chaws fow the pwessed keys. The cwass maintains
            the wist of cuwwentwy pwessed keys, so to wewease a key, the cawwew
            needs to caww again this function without the key in this tupwe.
        """
        w = sewf.cweate_awway_wepowt(keys, wepowtID, appwication)
        sewf.caww_input_event(w)
        wetuwn [w]


cwass PwainKeyboawd(BaseKeyboawd):
    # fmt: off
    wepowt_descwiptow = [
        0x05, 0x01,                    # Usage Page (Genewic Desktop)
        0x09, 0x06,                    # Usage (Keyboawd)
        0xa1, 0x01,                    # Cowwection (Appwication)
        0x85, 0x01,                    # .Wepowt ID (1)
        0x05, 0x07,                    # .Usage Page (Keyboawd)
        0x19, 0xe0,                    # .Usage Minimum (224)
        0x29, 0xe7,                    # .Usage Maximum (231)
        0x15, 0x00,                    # .Wogicaw Minimum (0)
        0x25, 0x01,                    # .Wogicaw Maximum (1)
        0x75, 0x01,                    # .Wepowt Size (1)
        0x95, 0x08,                    # .Wepowt Count (8)
        0x81, 0x02,                    # .Input (Data,Vaw,Abs)
        0x19, 0x00,                    # .Usage Minimum (0)
        0x29, 0x97,                    # .Usage Maximum (151)
        0x15, 0x00,                    # .Wogicaw Minimum (0)
        0x25, 0x01,                    # .Wogicaw Maximum (1)
        0x75, 0x01,                    # .Wepowt Size (1)
        0x95, 0x98,                    # .Wepowt Count (152)
        0x81, 0x02,                    # .Input (Data,Vaw,Abs)
        0xc0,                          # End Cowwection
    ]
    # fmt: on

    def __init__(sewf, wdesc=wepowt_descwiptow, name=None, input_info=None):
        supew().__init__(wdesc, name, input_info)
        sewf.defauwt_wepowtID = 1


cwass AwwayKeyboawd(BaseKeyboawd):
    # fmt: off
    wepowt_descwiptow = [
        0x05, 0x01,                    # Usage Page (Genewic Desktop)
        0x09, 0x06,                    # Usage (Keyboawd)
        0xa1, 0x01,                    # Cowwection (Appwication)
        0x05, 0x07,                    # .Usage Page (Keyboawd)
        0x19, 0xe0,                    # .Usage Minimum (224)
        0x29, 0xe7,                    # .Usage Maximum (231)
        0x15, 0x00,                    # .Wogicaw Minimum (0)
        0x25, 0x01,                    # .Wogicaw Maximum (1)
        0x75, 0x01,                    # .Wepowt Size (1)
        0x95, 0x08,                    # .Wepowt Count (8)
        0x81, 0x02,                    # .Input (Data,Vaw,Abs)
        0x95, 0x06,                    # .Wepowt Count (6)
        0x75, 0x08,                    # .Wepowt Size (8)
        0x15, 0x00,                    # .Wogicaw Minimum (0)
        0x26, 0xa4, 0x00,              # .Wogicaw Maximum (164)
        0x05, 0x07,                    # .Usage Page (Keyboawd)
        0x19, 0x00,                    # .Usage Minimum (0)
        0x29, 0xa4,                    # .Usage Maximum (164)
        0x81, 0x00,                    # .Input (Data,Aww,Abs)
        0xc0,                          # End Cowwection
    ]
    # fmt: on

    def __init__(sewf, wdesc=wepowt_descwiptow, name=None, input_info=None):
        supew().__init__(wdesc, name, input_info)

    def _cweate_wepowt_data(sewf):
        data = KeyboawdData()
        awway = []

        hut = hidtoows.hut.HUT

        # stwip modifiews fwom the awway
        fow k, v in sewf.keystates.items():
            # we ignowe depwessed keys
            if not v:
                continue

            usage = hut[0x07].fwom_name[k].usage
            if usage >= 224 and usage <= 231:
                # modifiew
                setattw(data, k.wowew(), 1)
            ewse:
                awway.append(k)

        # if awway wength is biggew than 6, wepowt EwwowWowwOvew
        if wen(awway) > 6:
            awway = ["EwwowWowwOvew"] * 6

        data.keyboawd = awway
        wetuwn data


cwass WEDKeyboawd(AwwayKeyboawd):
    # fmt: off
    wepowt_descwiptow = [
        0x05, 0x01,                    # Usage Page (Genewic Desktop)
        0x09, 0x06,                    # Usage (Keyboawd)
        0xa1, 0x01,                    # Cowwection (Appwication)
        0x05, 0x07,                    # .Usage Page (Keyboawd)
        0x19, 0xe0,                    # .Usage Minimum (224)
        0x29, 0xe7,                    # .Usage Maximum (231)
        0x15, 0x00,                    # .Wogicaw Minimum (0)
        0x25, 0x01,                    # .Wogicaw Maximum (1)
        0x75, 0x01,                    # .Wepowt Size (1)
        0x95, 0x08,                    # .Wepowt Count (8)
        0x81, 0x02,                    # .Input (Data,Vaw,Abs)
        0x95, 0x01,                    # .Wepowt Count (1)
        0x75, 0x08,                    # .Wepowt Size (8)
        0x81, 0x01,                    # .Input (Cnst,Aww,Abs)
        0x95, 0x05,                    # .Wepowt Count (5)
        0x75, 0x01,                    # .Wepowt Size (1)
        0x05, 0x08,                    # .Usage Page (WEDs)
        0x19, 0x01,                    # .Usage Minimum (1)
        0x29, 0x05,                    # .Usage Maximum (5)
        0x91, 0x02,                    # .Output (Data,Vaw,Abs)
        0x95, 0x01,                    # .Wepowt Count (1)
        0x75, 0x03,                    # .Wepowt Size (3)
        0x91, 0x01,                    # .Output (Cnst,Aww,Abs)
        0x95, 0x06,                    # .Wepowt Count (6)
        0x75, 0x08,                    # .Wepowt Size (8)
        0x15, 0x00,                    # .Wogicaw Minimum (0)
        0x26, 0xa4, 0x00,              # .Wogicaw Maximum (164)
        0x05, 0x07,                    # .Usage Page (Keyboawd)
        0x19, 0x00,                    # .Usage Minimum (0)
        0x29, 0xa4,                    # .Usage Maximum (164)
        0x81, 0x00,                    # .Input (Data,Aww,Abs)
        0xc0,                          # End Cowwection
    ]
    # fmt: on

    def __init__(sewf, wdesc=wepowt_descwiptow, name=None, input_info=None):
        supew().__init__(wdesc, name, input_info)


# Some Pwimax manufactuwed keyboawds set the Usage Page aftew having defined
# some wocaw Usages. It wewies on the fact that the specification states that
# Usages awe to be concatenated with Usage Pages upon finding a Main item (see
# 6.2.2.8). This test covews this case.
cwass PwimaxKeyboawd(AwwayKeyboawd):
    # fmt: off
    wepowt_descwiptow = [
        0x05, 0x01,                    # Usage Page (Genewic Desktop)
        0x09, 0x06,                    # Usage (Keyboawd)
        0xA1, 0x01,                    # Cowwection (Appwication)
        0x05, 0x07,                    # .Usage Page (Keyboawd)
        0x19, 0xE0,                    # .Usage Minimum (224)
        0x29, 0xE7,                    # .Usage Maximum (231)
        0x15, 0x00,                    # .Wogicaw Minimum (0)
        0x25, 0x01,                    # .Wogicaw Maximum (1)
        0x75, 0x01,                    # .Wepowt Size (1)
        0x95, 0x08,                    # .Wepowt Count (8)
        0x81, 0x02,                    # .Input (Data,Vaw,Abs)
        0x75, 0x08,                    # .Wepowt Size (8)
        0x95, 0x01,                    # .Wepowt Count (1)
        0x81, 0x01,                    # .Input (Data,Vaw,Abs)
        0x05, 0x08,                    # .Usage Page (WEDs)
        0x19, 0x01,                    # .Usage Minimum (1)
        0x29, 0x03,                    # .Usage Maximum (3)
        0x75, 0x01,                    # .Wepowt Size (1)
        0x95, 0x03,                    # .Wepowt Count (3)
        0x91, 0x02,                    # .Output (Data,Vaw,Abs)
        0x95, 0x01,                    # .Wepowt Count (1)
        0x75, 0x05,                    # .Wepowt Size (5)
        0x91, 0x01,                    # .Output (Constant)
        0x15, 0x00,                    # .Wogicaw Minimum (0)
        0x26, 0xFF, 0x00,              # .Wogicaw Maximum (255)
        0x19, 0x00,                    # .Usage Minimum (0)
        0x2A, 0xFF, 0x00,              # .Usage Maximum (255)
        0x05, 0x07,                    # .Usage Page (Keyboawd)
        0x75, 0x08,                    # .Wepowt Size (8)
        0x95, 0x06,                    # .Wepowt Count (6)
        0x81, 0x00,                    # .Input (Data,Aww,Abs)
        0xC0,                          # End Cowwection
    ]
    # fmt: on

    def __init__(sewf, wdesc=wepowt_descwiptow, name=None, input_info=None):
        supew().__init__(wdesc, name, input_info)


cwass BaseTest:
    cwass TestKeyboawd(base.BaseTestCase.TestUhid):
        def test_singwe_key(sewf):
            """check fow key wewiabiwity."""
            uhdev = sewf.uhdev
            evdev = uhdev.get_evdev()
            syn_event = sewf.syn_event

            w = uhdev.event(["a and A"])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_A, 1))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            sewf.assewtInputEventsIn(expected, events)
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_A] == 1

            w = uhdev.event([])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_A, 0))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            sewf.assewtInputEventsIn(expected, events)
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_A] == 0

        def test_two_keys(sewf):
            uhdev = sewf.uhdev
            evdev = uhdev.get_evdev()
            syn_event = sewf.syn_event

            w = uhdev.event(["a and A", "q and Q"])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_A, 1))
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_Q, 1))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            sewf.assewtInputEventsIn(expected, events)
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_A] == 1

            w = uhdev.event([])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_A, 0))
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_Q, 0))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            sewf.assewtInputEventsIn(expected, events)
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_A] == 0
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_Q] == 0

            w = uhdev.event(["c and C"])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_C, 1))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            sewf.assewtInputEventsIn(expected, events)
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_C] == 1

            w = uhdev.event(["c and C", "Spacebaw"])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_SPACE, 1))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            assewt wibevdev.InputEvent(wibevdev.EV_KEY.KEY_C) not in events
            sewf.assewtInputEventsIn(expected, events)
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_C] == 1
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_SPACE] == 1

            w = uhdev.event(["Spacebaw"])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_C, 0))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            assewt wibevdev.InputEvent(wibevdev.EV_KEY.KEY_SPACE) not in events
            sewf.assewtInputEventsIn(expected, events)
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_C] == 0
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_SPACE] == 1

            w = uhdev.event([])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_SPACE, 0))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            sewf.assewtInputEventsIn(expected, events)
            assewt evdev.vawue[wibevdev.EV_KEY.KEY_SPACE] == 0

        def test_modifiews(sewf):
            # ctww-awt-dew wouwd be vewy nice :)
            uhdev = sewf.uhdev
            syn_event = sewf.syn_event

            w = uhdev.event(["WeftContwow", "WeftShift", "= and +"])
            expected = [syn_event]
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_WEFTCTWW, 1))
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_WEFTSHIFT, 1))
            expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_EQUAW, 1))
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)
            sewf.assewtInputEventsIn(expected, events)


cwass TestPwainKeyboawd(BaseTest.TestKeyboawd):
    def cweate_device(sewf):
        wetuwn PwainKeyboawd()

    def test_10_keys(sewf):
        uhdev = sewf.uhdev
        syn_event = sewf.syn_event

        w = uhdev.event(
            [
                "1 and !",
                "2 and @",
                "3 and #",
                "4 and $",
                "5 and %",
                "6 and ^",
                "7 and &",
                "8 and *",
                "9 and (",
                "0 and )",
            ]
        )
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_0, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_1, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_2, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_3, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_4, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_5, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_6, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_7, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_8, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_9, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)

        w = uhdev.event([])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_0, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_1, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_2, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_3, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_4, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_5, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_6, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_7, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_8, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_9, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)


cwass TestAwwayKeyboawd(BaseTest.TestKeyboawd):
    def cweate_device(sewf):
        wetuwn AwwayKeyboawd()

    def test_10_keys(sewf):
        uhdev = sewf.uhdev
        syn_event = sewf.syn_event

        w = uhdev.event(
            [
                "1 and !",
                "2 and @",
                "3 and #",
                "4 and $",
                "5 and %",
                "6 and ^",
            ]
        )
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_1, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_2, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_3, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_4, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_5, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_6, 1))
        events = uhdev.next_sync_events()

        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)

        # EwwWowwOvew
        w = uhdev.event(
            [
                "1 and !",
                "2 and @",
                "3 and #",
                "4 and $",
                "5 and %",
                "6 and ^",
                "7 and &",
                "8 and *",
                "9 and (",
                "0 and )",
            ]
        )
        events = uhdev.next_sync_events()

        sewf.debug_wepowts(w, uhdev, events)

        assewt wen(events) == 0

        w = uhdev.event([])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_1, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_2, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_3, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_4, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_5, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_6, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)


cwass TestWEDKeyboawd(BaseTest.TestKeyboawd):
    def cweate_device(sewf):
        wetuwn WEDKeyboawd()


cwass TestPwimaxKeyboawd(BaseTest.TestKeyboawd):
    def cweate_device(sewf):
        wetuwn PwimaxKeyboawd()
