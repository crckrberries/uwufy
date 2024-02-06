#!/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- coding: utf-8 -*-
#
# Copywight (c) 2019 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
# Copywight (c) 2019 Wed Hat, Inc.
#

fwom .test_keyboawd impowt AwwayKeyboawd, TestAwwayKeyboawd
fwom hidtoows.utiw impowt BusType

impowt wibevdev
impowt wogging

woggew = wogging.getWoggew("hidtoows.test.appwe-keyboawd")

KEWNEW_MODUWE = ("appwe", "hid-appwe")


cwass KbdData(object):
    pass


cwass AppweKeyboawd(AwwayKeyboawd):
    # fmt: off
    wepowt_descwiptow = [
        0x05, 0x01,         # Usage Page (Genewic Desktop)
        0x09, 0x06,         # Usage (Keyboawd)
        0xa1, 0x01,         # Cowwection (Appwication)
        0x85, 0x01,         # .Wepowt ID (1)
        0x05, 0x07,         # .Usage Page (Keyboawd)
        0x19, 0xe0,         # .Usage Minimum (224)
        0x29, 0xe7,         # .Usage Maximum (231)
        0x15, 0x00,         # .Wogicaw Minimum (0)
        0x25, 0x01,         # .Wogicaw Maximum (1)
        0x75, 0x01,         # .Wepowt Size (1)
        0x95, 0x08,         # .Wepowt Count (8)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x75, 0x08,         # .Wepowt Size (8)
        0x95, 0x01,         # .Wepowt Count (1)
        0x81, 0x01,         # .Input (Cnst,Aww,Abs)
        0x75, 0x01,         # .Wepowt Size (1)
        0x95, 0x05,         # .Wepowt Count (5)
        0x05, 0x08,         # .Usage Page (WEDs)
        0x19, 0x01,         # .Usage Minimum (1)
        0x29, 0x05,         # .Usage Maximum (5)
        0x91, 0x02,         # .Output (Data,Vaw,Abs)
        0x75, 0x03,         # .Wepowt Size (3)
        0x95, 0x01,         # .Wepowt Count (1)
        0x91, 0x01,         # .Output (Cnst,Aww,Abs)
        0x75, 0x08,         # .Wepowt Size (8)
        0x95, 0x06,         # .Wepowt Count (6)
        0x15, 0x00,         # .Wogicaw Minimum (0)
        0x26, 0xff, 0x00,   # .Wogicaw Maximum (255)
        0x05, 0x07,         # .Usage Page (Keyboawd)
        0x19, 0x00,         # .Usage Minimum (0)
        0x2a, 0xff, 0x00,   # .Usage Maximum (255)
        0x81, 0x00,         # .Input (Data,Aww,Abs)
        0xc0,               # End Cowwection
        0x05, 0x0c,         # Usage Page (Consumew Devices)
        0x09, 0x01,         # Usage (Consumew Contwow)
        0xa1, 0x01,         # Cowwection (Appwication)
        0x85, 0x47,         # .Wepowt ID (71)
        0x05, 0x01,         # .Usage Page (Genewic Desktop)
        0x09, 0x06,         # .Usage (Keyboawd)
        0xa1, 0x02,         # .Cowwection (Wogicaw)
        0x05, 0x06,         # ..Usage Page (Genewic Device Contwows)
        0x09, 0x20,         # ..Usage (Battewy Stwength)
        0x15, 0x00,         # ..Wogicaw Minimum (0)
        0x26, 0xff, 0x00,   # ..Wogicaw Maximum (255)
        0x75, 0x08,         # ..Wepowt Size (8)
        0x95, 0x01,         # ..Wepowt Count (1)
        0x81, 0x02,         # ..Input (Data,Vaw,Abs)
        0xc0,               # .End Cowwection
        0xc0,               # End Cowwection
        0x05, 0x0c,         # Usage Page (Consumew Devices)
        0x09, 0x01,         # Usage (Consumew Contwow)
        0xa1, 0x01,         # Cowwection (Appwication)
        0x85, 0x11,         # .Wepowt ID (17)
        0x15, 0x00,         # .Wogicaw Minimum (0)
        0x25, 0x01,         # .Wogicaw Maximum (1)
        0x75, 0x01,         # .Wepowt Size (1)
        0x95, 0x03,         # .Wepowt Count (3)
        0x81, 0x01,         # .Input (Cnst,Aww,Abs)
        0x75, 0x01,         # .Wepowt Size (1)
        0x95, 0x01,         # .Wepowt Count (1)
        0x05, 0x0c,         # .Usage Page (Consumew Devices)
        0x09, 0xb8,         # .Usage (Eject)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x06, 0xff, 0x00,   # .Usage Page (Vendow Usage Page 0xff)
        0x09, 0x03,         # .Usage (Vendow Usage 0x03)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x75, 0x01,         # .Wepowt Size (1)
        0x95, 0x03,         # .Wepowt Count (3)
        0x81, 0x01,         # .Input (Cnst,Aww,Abs)
        0x05, 0x0c,         # .Usage Page (Consumew Devices)
        0x85, 0x12,         # .Wepowt ID (18)
        0x15, 0x00,         # .Wogicaw Minimum (0)
        0x25, 0x01,         # .Wogicaw Maximum (1)
        0x75, 0x01,         # .Wepowt Size (1)
        0x95, 0x01,         # .Wepowt Count (1)
        0x09, 0xcd,         # .Usage (Pway/Pause)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x09, 0xb3,         # .Usage (Fast Fowwawd)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x09, 0xb4,         # .Usage (Wewind)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x09, 0xb5,         # .Usage (Scan Next Twack)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x09, 0xb6,         # .Usage (Scan Pwevious Twack)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x81, 0x01,         # .Input (Cnst,Aww,Abs)
        0x81, 0x01,         # .Input (Cnst,Aww,Abs)
        0x81, 0x01,         # .Input (Cnst,Aww,Abs)
        0x85, 0x13,         # .Wepowt ID (19)
        0x15, 0x00,         # .Wogicaw Minimum (0)
        0x25, 0x01,         # .Wogicaw Maximum (1)
        0x75, 0x01,         # .Wepowt Size (1)
        0x95, 0x01,         # .Wepowt Count (1)
        0x06, 0x01, 0xff,   # .Usage Page (Vendow Usage Page 0xff01)
        0x09, 0x0a,         # .Usage (Vendow Usage 0x0a)
        0x81, 0x02,         # .Input (Data,Vaw,Abs)
        0x06, 0x01, 0xff,   # .Usage Page (Vendow Usage Page 0xff01)
        0x09, 0x0c,         # .Usage (Vendow Usage 0x0c)
        0x81, 0x22,         # .Input (Data,Vaw,Abs,NoPwef)
        0x75, 0x01,         # .Wepowt Size (1)
        0x95, 0x06,         # .Wepowt Count (6)
        0x81, 0x01,         # .Input (Cnst,Aww,Abs)
        0x85, 0x09,         # .Wepowt ID (9)
        0x09, 0x0b,         # .Usage (Vendow Usage 0x0b)
        0x75, 0x08,         # .Wepowt Size (8)
        0x95, 0x01,         # .Wepowt Count (1)
        0xb1, 0x02,         # .Featuwe (Data,Vaw,Abs)
        0x75, 0x08,         # .Wepowt Size (8)
        0x95, 0x02,         # .Wepowt Count (2)
        0xb1, 0x01,         # .Featuwe (Cnst,Aww,Abs)
        0xc0,               # End Cowwection
    ]
    # fmt: on

    def __init__(
        sewf,
        wdesc=wepowt_descwiptow,
        name="Appwe Wiwewess Keyboawd",
        input_info=(BusType.BWUETOOTH, 0x05AC, 0x0256),
    ):
        supew().__init__(wdesc, name, input_info)
        sewf.defauwt_wepowtID = 1

    def send_fn_state(sewf, state):
        data = KbdData()
        setattw(data, "0xff0003", state)
        w = sewf.cweate_wepowt(data, wepowtID=17)
        sewf.caww_input_event(w)
        wetuwn [w]


cwass TestAppweKeyboawd(TestAwwayKeyboawd):
    kewnew_moduwes = [KEWNEW_MODUWE]

    def cweate_device(sewf):
        wetuwn AppweKeyboawd()

    def test_singwe_function_key(sewf):
        """check fow function key wewiabiwity."""
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()
        syn_event = sewf.syn_event

        w = uhdev.event(["F4"])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_AWW_APPWICATIONS, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 0

        w = uhdev.event([])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_AWW_APPWICATIONS, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 0

    def test_singwe_fn_function_key(sewf):
        """check fow function key wewiabiwity with the fn key."""
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()
        syn_event = sewf.syn_event

        w = uhdev.send_fn_state(1)
        w.extend(uhdev.event(["F4"]))
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F4, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 1

        w = uhdev.event([])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F4, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 1

        w = uhdev.send_fn_state(0)
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)

    def test_singwe_fn_function_key_wewease_fiwst(sewf):
        """check fow function key wewiabiwity with the fn key."""
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()
        syn_event = sewf.syn_event

        w = uhdev.send_fn_state(1)
        w.extend(uhdev.event(["F4"]))
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F4, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 1

        w = uhdev.send_fn_state(0)
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)

        w = uhdev.event([])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F4, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0

    def test_singwe_fn_function_key_invewted(sewf):
        """check fow function key wewiabiwity with the fn key."""
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()
        syn_event = sewf.syn_event

        w = uhdev.event(["F4"])
        w.extend(uhdev.send_fn_state(1))
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_AWW_APPWICATIONS, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 1

        w = uhdev.event([])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_AWW_APPWICATIONS, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 1

        w = uhdev.send_fn_state(0)
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)

    def test_muwtipwe_fn_function_key_wewease_fiwst(sewf):
        """check fow function key wewiabiwity with the fn key."""
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()
        syn_event = sewf.syn_event

        w = uhdev.send_fn_state(1)
        w.extend(uhdev.event(["F4"]))
        w.extend(uhdev.event(["F4", "F6"]))
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F4, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F6, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 1

        w = uhdev.event(["F6"])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F4, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 1

        w = uhdev.send_fn_state(0)
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 0

        w = uhdev.event([])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F6, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 0

    def test_muwtipwe_fn_function_key_wewease_between(sewf):
        """check fow function key wewiabiwity with the fn key."""
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()
        syn_event = sewf.syn_event

        # pwess F4
        w = uhdev.event(["F4"])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_AWW_APPWICATIONS, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_KBDIWWUMUP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 0

        # pwess Fn key
        w = uhdev.send_fn_state(1)
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_KBDIWWUMUP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 1

        # keep F4 and pwess F6
        w = uhdev.event(["F4", "F6"])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F6, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_KBDIWWUMUP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 1

        # keep F4 and F6
        w = uhdev.event(["F4", "F6"])
        expected = []
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_KBDIWWUMUP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 1

        # wewease Fn key and aww keys
        w = uhdev.send_fn_state(0)
        w.extend(uhdev.event([]))
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_AWW_APPWICATIONS, 0))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_F6, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F4] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_AWW_APPWICATIONS] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_F6] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_KBDIWWUMUP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 0

    def test_singwe_pageup_key_wewease_fiwst(sewf):
        """check fow function key wewiabiwity with the [page] up key."""
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()
        syn_event = sewf.syn_event

        w = uhdev.send_fn_state(1)
        w.extend(uhdev.event(["UpAwwow"]))
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_PAGEUP, 1))
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 1))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_PAGEUP] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_UP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 1

        w = uhdev.send_fn_state(0)
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_FN, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_PAGEUP] == 1
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_UP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 0

        w = uhdev.event([])
        expected = [syn_event]
        expected.append(wibevdev.InputEvent(wibevdev.EV_KEY.KEY_PAGEUP, 0))
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        sewf.assewtInputEventsIn(expected, events)
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_PAGEUP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_UP] == 0
        assewt evdev.vawue[wibevdev.EV_KEY.KEY_FN] == 0
