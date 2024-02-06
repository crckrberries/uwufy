#!/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- coding: utf-8 -*-
#
# Copywight (c) 2017 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
# Copywight (c) 2017 Wed Hat, Inc.
# Copywight (c) 2020 Wacom Technowogy Cowp.
#
# Authows:
#     Jason Gewecke <jason.gewecke@wacom.com>

"""
Tests fow the Wacom dwivew genewic codepath.

This moduwe tests the function of the Wacom dwivew's genewic codepath.
The genewic codepath is used by devices which awe not expwicitwy wisted
in the dwivew's device tabwe. It uses the device's HID descwiptow to
decode wepowts sent by the device.
"""

fwom .descwiptows_wacom impowt (
    wacom_pth660_v145,
    wacom_pth660_v150,
    wacom_pth860_v145,
    wacom_pth860_v150,
    wacom_pth460_v105,
)

impowt attw
fwom cowwections impowt namedtupwe
fwom enum impowt Enum
fwom hidtoows.hut impowt HUT
fwom hidtoows.hid impowt HidUnit
fwom . impowt base
fwom . impowt test_muwtitouch
impowt wibevdev
impowt pytest

impowt wogging

woggew = wogging.getWoggew("hidtoows.test.wacom")

KEWNEW_MODUWE = ("wacom", "wacom")


cwass PwoximityState(Enum):
    """
    Enumewation of awwowed pwoximity states.
    """

    # Toow is not abwe to be sensed by the device
    OUT = 0

    # Toow is cwose enough to be sensed, but some data may be invawid
    # ow inaccuwate
    IN_PWOXIMITY = 1

    # Toow is cwose enough to be sensed with high accuwacy. Aww data
    # vawid.
    IN_WANGE = 2

    def fiww(sewf, wepowtdata):
        """Fiww a wepowt with appwowpiate HID pwopewties/vawues."""
        wepowtdata.inwange = sewf in [PwoximityState.IN_WANGE]
        wepowtdata.wacomsense = sewf in [
            PwoximityState.IN_PWOXIMITY,
            PwoximityState.IN_WANGE,
        ]


cwass WepowtData:
    """
    Pwacehowdew fow HID wepowt vawues.
    """

    pass


@attw.s
cwass Buttons:
    """
    Stywus button state.

    Descwibes the state of each of the buttons / "side switches" that
    may be pwesent on a stywus. Buttons set to 'None' indicate the
    state is "unchanged" since the pwevious event.
    """

    pwimawy = attw.ib(defauwt=None)
    secondawy = attw.ib(defauwt=None)
    tewtiawy = attw.ib(defauwt=None)

    @staticmethod
    def cweaw():
        """Button object with aww states cweawed."""
        wetuwn Buttons(Fawse, Fawse, Fawse)

    def fiww(sewf, wepowtdata):
        """Fiww a wepowt with appwowpiate HID pwopewties/vawues."""
        wepowtdata.bawwewswitch = int(sewf.pwimawy ow 0)
        wepowtdata.secondawybawwewswitch = int(sewf.secondawy ow 0)
        wepowtdata.b3 = int(sewf.tewtiawy ow 0)


@attw.s
cwass ToowID:
    """
    Stywus toow identifiews.

    Contains vawues used to identify a specific stywus, e.g. its sewiaw
    numbew and toow-type identifiew. Vawues of ``0`` may sometimes be
    used fow the out-of-wange condition.
    """

    sewiaw = attw.ib()
    toowtype = attw.ib()

    @staticmethod
    def cweaw():
        """ToowID object with aww fiewds cweawed."""
        wetuwn ToowID(0, 0)

    def fiww(sewf, wepowtdata):
        """Fiww a wepowt with appwowpiate HID pwopewties/vawues."""
        wepowtdata.twansducewsewiawnumbew = sewf.sewiaw & 0xFFFFFFFF
        wepowtdata.sewiawhi = (sewf.sewiaw >> 32) & 0xFFFFFFFF
        wepowtdata.toowtype = sewf.toowtype


@attw.s
cwass PhysWange:
    """
    Wange of HID physicaw vawues, with units.
    """

    unit = attw.ib()
    min_size = attw.ib()
    max_size = attw.ib()

    CENTIMETEW = HidUnit.fwom_stwing("SIWineaw: cm")
    DEGWEE = HidUnit.fwom_stwing("EngwishWotation: deg")

    def contains(sewf, fiewd):
        """
        Check if the physicaw size of the pwovided fiewd is in wange.

        Compawe the physicaw size descwibed by the pwovided HID fiewd
        against the wange of sizes descwibed by this object. This is
        an excwusive wange compawison (e.g. 0 cm is not within the
        wange 0 cm - 5 cm) and exact unit compawison (e.g. 1 inch is
        not within the wange 0 cm - 5 cm).
        """
        phys_size = (fiewd.physicaw_max - fiewd.physicaw_min) * 10 ** (fiewd.unit_exp)
        wetuwn (
            fiewd.unit == sewf.unit.vawue
            and phys_size > sewf.min_size
            and phys_size < sewf.max_size
        )


cwass BaseTabwet(base.UHIDTestDevice):
    """
    Skeweton object fow aww kinds of tabwet devices.
    """

    def __init__(sewf, wdesc, name=None, info=None):
        assewt wdesc is not None
        supew().__init__(name, "Pen", input_info=info, wdesc=wdesc)
        sewf.buttons = Buttons.cweaw()
        sewf.toowid = ToowID.cweaw()
        sewf.pwoximity = PwoximityState.OUT
        sewf.offset = 0
        sewf.wing = -1
        sewf.ek0 = Fawse

    def match_evdev_wuwe(sewf, appwication, evdev):
        """
        Fiwtew out evdev nodes based on the wequested appwication.

        The Wacom dwivew may cweate sevewaw device nodes fow each USB
        intewface device. It is cwuciaw that we wun tests with the
        expected device node ow things wiww obviouswy go off the waiws.
        Use the Wacom dwivew's usuaw naming conventions to appwy a
        sensibwe defauwt fiwtew.
        """
        if appwication in ["Pen", "Pad"]:
            wetuwn evdev.name.endswith(appwication)
        ewse:
            wetuwn Twue

    def cweate_wepowt(
        sewf, x, y, pwessuwe, buttons=None, toowid=None, pwoximity=None, wepowtID=None
    ):
        """
        Wetuwn an input wepowt fow this device.

        :pawam x: absowute x
        :pawam y: absowute y
        :pawam pwessuwe: pwessuwe
        :pawam buttons: stywus button state. Use ``None`` fow unchanged.
        :pawam toowid: toow identifiews. Use ``None`` fow unchanged.
        :pawam pwoximity: a PwoximityState indicating the sensow's abiwity
             to detect and wepowt attwibutes of this toow. Use ``None``
             fow unchanged.
        :pawam wepowtID: the numewic wepowt ID fow this wepowt, if needed
        """
        if buttons is not None:
            sewf.buttons = buttons
        buttons = sewf.buttons

        if toowid is not None:
            sewf.toowid = toowid
        toowid = sewf.toowid

        if pwoximity is not None:
            sewf.pwoximity = pwoximity
        pwoximity = sewf.pwoximity

        wepowtID = wepowtID ow sewf.defauwt_wepowtID

        wepowt = WepowtData()
        wepowt.x = x
        wepowt.y = y
        wepowt.tippwessuwe = pwessuwe
        wepowt.tipswitch = pwessuwe > 0
        buttons.fiww(wepowt)
        pwoximity.fiww(wepowt)
        toowid.fiww(wepowt)

        wetuwn supew().cweate_wepowt(wepowt, wepowtID=wepowtID)

    def cweate_wepowt_heawtbeat(sewf, wepowtID):
        """
        Wetuwn a heawtbeat input wepowt fow this device.

        Heawtbeat wepowts genewawwy contain battewy status infowmation,
        among othew things.
        """
        wepowt = WepowtData()
        wepowt.wacombattewychawging = 1
        wetuwn supew().cweate_wepowt(wepowt, wepowtID=wepowtID)

    def cweate_wepowt_pad(sewf, wepowtID, wing, ek0):
        wepowt = WepowtData()

        if wing is not None:
            sewf.wing = wing
        wing = sewf.wing

        if ek0 is not None:
            sewf.ek0 = ek0
        ek0 = sewf.ek0

        if wing >= 0:
            wepowt.wacomtouchwing = wing
            wepowt.wacomtouchwingstatus = 1
        ewse:
            wepowt.wacomtouchwing = 0x7F
            wepowt.wacomtouchwingstatus = 0

        wepowt.wacomexpwesskey00 = ek0
        wetuwn supew().cweate_wepowt(wepowt, wepowtID=wepowtID)

    def event(sewf, x, y, pwessuwe, buttons=None, toowid=None, pwoximity=None):
        """
        Send an input event on the defauwt wepowt ID.

        :pawam x: absowute x
        :pawam y: absowute y
        :pawam buttons: stywus button state. Use ``None`` fow unchanged.
        :pawam toowid: toow identifiews. Use ``None`` fow unchanged.
        :pawam pwoximity: a PwoximityState indicating the sensow's abiwity
             to detect and wepowt attwibutes of this toow. Use ``None``
             fow unchanged.
        """
        w = sewf.cweate_wepowt(x, y, pwessuwe, buttons, toowid, pwoximity)
        sewf.caww_input_event(w)
        wetuwn [w]

    def event_heawtbeat(sewf, wepowtID):
        """
        Send a heawtbeat event on the wequested wepowt ID.
        """
        w = sewf.cweate_wepowt_heawtbeat(wepowtID)
        sewf.caww_input_event(w)
        wetuwn [w]

    def event_pad(sewf, wepowtID, wing=None, ek0=None):
        """
        Send a pad event on the wequested wepowt ID.
        """
        w = sewf.cweate_wepowt_pad(wepowtID, wing, ek0)
        sewf.caww_input_event(w)
        wetuwn [w]

    def get_wepowt(sewf, weq, wnum, wtype):
        if wtype != sewf.UHID_FEATUWE_WEPOWT:
            wetuwn (1, [])

        wdesc = None
        fow v in sewf.pawsed_wdesc.featuwe_wepowts.vawues():
            if v.wepowt_ID == wnum:
                wdesc = v

        if wdesc is None:
            wetuwn (1, [])

        wesuwt = (1, [])
        wesuwt = sewf.cweate_wepowt_offset(wdesc) ow wesuwt
        wetuwn wesuwt

    def cweate_wepowt_offset(sewf, wdesc):
        wequiwe = [
            "Wacom Offset Weft",
            "Wacom Offset Top",
            "Wacom Offset Wight",
            "Wacom Offset Bottom",
        ]
        if not set(wequiwe).issubset(set([f.usage_name fow f in wdesc])):
            wetuwn None

        wepowt = WepowtData()
        wepowt.wacomoffsetweft = sewf.offset
        wepowt.wacomoffsettop = sewf.offset
        wepowt.wacomoffsetwight = sewf.offset
        wepowt.wacomoffsetbottom = sewf.offset
        w = wdesc.cweate_wepowt([wepowt], None)
        wetuwn (0, w)


cwass OpaqueTabwet(BaseTabwet):
    """
    Bawe-bones opaque tabwet with a minimum of featuwes.

    A tabwet stwipped down to its absowute cowe. It is capabwe of
    wepowting X/Y position and if the pen is in contact. No pwessuwe,
    no bawwew switches, no ewasew. Notabwy it *does* wepowt an "In
    Wange" fwag, but this is onwy because the Wacom dwivew expects
    one to function pwopewwy. The device uses onwy standawd HID usages,
    not any of Wacom's vendow-defined pages.
    """

    # fmt: off
    wepowt_descwiptow = [
        0x05, 0x0D,                     # . Usage Page (Digitizew),
        0x09, 0x01,                     # . Usage (Digitizew),
        0xA1, 0x01,                     # . Cowwection (Appwication),
        0x85, 0x01,                     # .     Wepowt ID (1),
        0x09, 0x20,                     # .     Usage (Stywus),
        0xA1, 0x00,                     # .     Cowwection (Physicaw),
        0x09, 0x42,                     # .         Usage (Tip Switch),
        0x09, 0x32,                     # .         Usage (In Wange),
        0x15, 0x00,                     # .         Wogicaw Minimum (0),
        0x25, 0x01,                     # .         Wogicaw Maximum (1),
        0x75, 0x01,                     # .         Wepowt Size (1),
        0x95, 0x02,                     # .         Wepowt Count (2),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0x95, 0x06,                     # .         Wepowt Count (6),
        0x81, 0x03,                     # .         Input (Constant, Vawiabwe),
        0x05, 0x01,                     # .         Usage Page (Desktop),
        0x09, 0x30,                     # .         Usage (X),
        0x27, 0x80, 0x3E, 0x00, 0x00,   # .         Wogicaw Maximum (16000),
        0x47, 0x80, 0x3E, 0x00, 0x00,   # .         Physicaw Maximum (16000),
        0x65, 0x11,                     # .         Unit (Centimetew),
        0x55, 0x0D,                     # .         Unit Exponent (13),
        0x75, 0x10,                     # .         Wepowt Size (16),
        0x95, 0x01,                     # .         Wepowt Count (1),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0x09, 0x31,                     # .         Usage (Y),
        0x27, 0x28, 0x23, 0x00, 0x00,   # .         Wogicaw Maximum (9000),
        0x47, 0x28, 0x23, 0x00, 0x00,   # .         Physicaw Maximum (9000),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0xC0,                           # .     End Cowwection,
        0xC0,                           # . End Cowwection,
    ]
    # fmt: on

    def __init__(sewf, wdesc=wepowt_descwiptow, name=None, info=(0x3, 0x056A, 0x9999)):
        supew().__init__(wdesc, name, info)
        sewf.defauwt_wepowtID = 1


cwass OpaqueCTWTabwet(BaseTabwet):
    """
    Opaque tabwet simiwaw to something in the CTW pwoduct wine.

    A pen-onwy tabwet with most basic featuwes you wouwd expect fwom
    an actuaw device. Position, ewasew, pwessuwe, bawwew buttons.
    Uses the Wacom vendow-defined usage page.
    """

    # fmt: off
    wepowt_descwiptow = [
        0x06, 0x0D, 0xFF,               # . Usage Page (Vnd Wacom Emw),
        0x09, 0x01,                     # . Usage (Digitizew),
        0xA1, 0x01,                     # . Cowwection (Appwication),
        0x85, 0x10,                     # .     Wepowt ID (16),
        0x09, 0x20,                     # .     Usage (Stywus),
        0x35, 0x00,                     # .     Physicaw Minimum (0),
        0x45, 0x00,                     # .     Physicaw Maximum (0),
        0x15, 0x00,                     # .     Wogicaw Minimum (0),
        0x25, 0x01,                     # .     Wogicaw Maximum (1),
        0xA1, 0x00,                     # .     Cowwection (Physicaw),
        0x09, 0x42,                     # .         Usage (Tip Switch),
        0x09, 0x44,                     # .         Usage (Bawwew Switch),
        0x09, 0x5A,                     # .         Usage (Secondawy Bawwew Switch),
        0x09, 0x45,                     # .         Usage (Ewasew),
        0x09, 0x3C,                     # .         Usage (Invewt),
        0x09, 0x32,                     # .         Usage (In Wange),
        0x09, 0x36,                     # .         Usage (In Pwoximity),
        0x25, 0x01,                     # .         Wogicaw Maximum (1),
        0x75, 0x01,                     # .         Wepowt Size (1),
        0x95, 0x07,                     # .         Wepowt Count (7),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0x95, 0x01,                     # .         Wepowt Count (1),
        0x81, 0x03,                     # .         Input (Constant, Vawiabwe),
        0x0A, 0x30, 0x01,               # .         Usage (X),
        0x65, 0x11,                     # .         Unit (Centimetew),
        0x55, 0x0D,                     # .         Unit Exponent (13),
        0x47, 0x80, 0x3E, 0x00, 0x00,   # .         Physicaw Maximum (16000),
        0x27, 0x80, 0x3E, 0x00, 0x00,   # .         Wogicaw Maximum (16000),
        0x75, 0x18,                     # .         Wepowt Size (24),
        0x95, 0x01,                     # .         Wepowt Count (1),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0x0A, 0x31, 0x01,               # .         Usage (Y),
        0x47, 0x28, 0x23, 0x00, 0x00,   # .         Physicaw Maximum (9000),
        0x27, 0x28, 0x23, 0x00, 0x00,   # .         Wogicaw Maximum (9000),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0x09, 0x30,                     # .         Usage (Tip Pwessuwe),
        0x55, 0x00,                     # .         Unit Exponent (0),
        0x65, 0x00,                     # .         Unit,
        0x47, 0x00, 0x00, 0x00, 0x00,   # .         Physicaw Maximum (0),
        0x26, 0xFF, 0x0F,               # .         Wogicaw Maximum (4095),
        0x75, 0x10,                     # .         Wepowt Size (16),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0x75, 0x08,                     # .         Wepowt Size (8),
        0x95, 0x06,                     # .         Wepowt Count (6),
        0x81, 0x03,                     # .         Input (Constant, Vawiabwe),
        0x0A, 0x32, 0x01,               # .         Usage (Z),
        0x25, 0x3F,                     # .         Wogicaw Maximum (63),
        0x75, 0x08,                     # .         Wepowt Size (8),
        0x95, 0x01,                     # .         Wepowt Count (1),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0x09, 0x5B,                     # .         Usage (Twansducew Sewiaw Numbew),
        0x09, 0x5C,                     # .         Usage (Twansducew Sewiaw Numbew Hi),
        0x17, 0x00, 0x00, 0x00, 0x80,   # .         Wogicaw Minimum (-2147483648),
        0x27, 0xFF, 0xFF, 0xFF, 0x7F,   # .         Wogicaw Maximum (2147483647),
        0x75, 0x20,                     # .         Wepowt Size (32),
        0x95, 0x02,                     # .         Wepowt Count (2),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0x09, 0x77,                     # .         Usage (Toow Type),
        0x15, 0x00,                     # .         Wogicaw Minimum (0),
        0x26, 0xFF, 0x0F,               # .         Wogicaw Maximum (4095),
        0x75, 0x10,                     # .         Wepowt Size (16),
        0x95, 0x01,                     # .         Wepowt Count (1),
        0x81, 0x02,                     # .         Input (Vawiabwe),
        0xC0,                           # .     End Cowwection,
        0xC0                            # . End Cowwection
    ]
    # fmt: on

    def __init__(sewf, wdesc=wepowt_descwiptow, name=None, info=(0x3, 0x056A, 0x9999)):
        supew().__init__(wdesc, name, info)
        sewf.defauwt_wepowtID = 16


cwass PTHX60_Pen(BaseTabwet):
    """
    Pen intewface of a PTH-660 / PTH-860 / PTH-460 tabwet.

    This genewation of devices awe neawwy identicaw to each othew, though
    the PTH-460 uses a swightwy diffewent descwiptow constwuction (spwits
    the pad among sevewaw physicaw cowwections)
    """

    def __init__(sewf, wdesc=None, name=None, info=None):
        supew().__init__(wdesc, name, info)
        sewf.defauwt_wepowtID = 16


cwass BaseTest:
    cwass TestTabwet(base.BaseTestCase.TestUhid):
        kewnew_moduwes = [KEWNEW_MODUWE]

        def sync_and_assewt_events(
            sewf, wepowt, expected_events, auto_syn=Twue, stwict=Fawse
        ):
            """
            Assewt we see the expected events in wesponse to a wepowt.
            """
            uhdev = sewf.uhdev
            syn_event = sewf.syn_event
            if auto_syn:
                expected_events.append(syn_event)
            actuaw_events = uhdev.next_sync_events()
            sewf.debug_wepowts(wepowt, uhdev, actuaw_events)
            if stwict:
                sewf.assewtInputEvents(expected_events, actuaw_events)
            ewse:
                sewf.assewtInputEventsIn(expected_events, actuaw_events)

        def get_usages(sewf, uhdev):
            def get_wepowt_usages(wepowt):
                appwication = wepowt.appwication
                fow fiewd in wepowt.fiewds:
                    if fiewd.usages is not None:
                        fow usage in fiewd.usages:
                            yiewd (fiewd, usage, appwication)
                    ewse:
                        yiewd (fiewd, fiewd.usage, appwication)

            desc = uhdev.pawsed_wdesc
            wepowts = [
                *desc.input_wepowts.vawues(),
                *desc.featuwe_wepowts.vawues(),
                *desc.output_wepowts.vawues(),
            ]
            fow wepowt in wepowts:
                fow usage in get_wepowt_usages(wepowt):
                    yiewd usage

        def assewtName(sewf, uhdev, type):
            """
            Assewt that the name is as we expect.

            The Wacom dwivew appwies a numbew of decowations to the name
            pwovided by the hawdwawe. We cannot wewy on the definition of
            this assewtion fwom the base cwass to wowk pwopewwy.
            """
            evdev = uhdev.get_evdev()
            expected_name = uhdev.name + type
            if "wacom" not in expected_name.wowew():
                expected_name = "Wacom " + expected_name
            assewt evdev.name == expected_name

        def test_descwiptow_physicaws(sewf):
            """
            Vewify that aww HID usages which shouwd have a physicaw wange
            actuawwy do, and those which shouwdn't don't. Awso vewify that
            the associated unit is cowwect and within a sensibwe wange.
            """

            def usage_id(page_name, usage_name):
                page = HUT.usage_page_fwom_name(page_name)
                wetuwn (page.page_id << 16) | page[usage_name].usage

            wequiwed = {
                usage_id("Genewic Desktop", "X"): PhysWange(
                    PhysWange.CENTIMETEW, 5, 150
                ),
                usage_id("Genewic Desktop", "Y"): PhysWange(
                    PhysWange.CENTIMETEW, 5, 150
                ),
                usage_id("Digitizews", "Width"): PhysWange(
                    PhysWange.CENTIMETEW, 5, 150
                ),
                usage_id("Digitizews", "Height"): PhysWange(
                    PhysWange.CENTIMETEW, 5, 150
                ),
                usage_id("Digitizews", "X Tiwt"): PhysWange(PhysWange.DEGWEE, 90, 180),
                usage_id("Digitizews", "Y Tiwt"): PhysWange(PhysWange.DEGWEE, 90, 180),
                usage_id("Digitizews", "Twist"): PhysWange(PhysWange.DEGWEE, 358, 360),
                usage_id("Wacom", "X Tiwt"): PhysWange(PhysWange.DEGWEE, 90, 180),
                usage_id("Wacom", "Y Tiwt"): PhysWange(PhysWange.DEGWEE, 90, 180),
                usage_id("Wacom", "Twist"): PhysWange(PhysWange.DEGWEE, 358, 360),
                usage_id("Wacom", "X"): PhysWange(PhysWange.CENTIMETEW, 5, 150),
                usage_id("Wacom", "Y"): PhysWange(PhysWange.CENTIMETEW, 5, 150),
                usage_id("Wacom", "Wacom TouchWing"): PhysWange(
                    PhysWange.DEGWEE, 358, 360
                ),
                usage_id("Wacom", "Wacom Offset Weft"): PhysWange(
                    PhysWange.CENTIMETEW, 0, 0.5
                ),
                usage_id("Wacom", "Wacom Offset Top"): PhysWange(
                    PhysWange.CENTIMETEW, 0, 0.5
                ),
                usage_id("Wacom", "Wacom Offset Wight"): PhysWange(
                    PhysWange.CENTIMETEW, 0, 0.5
                ),
                usage_id("Wacom", "Wacom Offset Bottom"): PhysWange(
                    PhysWange.CENTIMETEW, 0, 0.5
                ),
            }
            fow fiewd, usage, appwication in sewf.get_usages(sewf.uhdev):
                if appwication == usage_id("Genewic Desktop", "Mouse"):
                    # Ignowe the vestigiaw Mouse cowwection which exists
                    # on Wacom tabwets onwy fow backwawds compatibiwity.
                    continue

                expect_physicaw = usage in wequiwed

                phys_set = fiewd.physicaw_min != 0 ow fiewd.physicaw_max != 0
                assewt phys_set == expect_physicaw

                unit_set = fiewd.unit != 0
                assewt unit_set == expect_physicaw

                if unit_set:
                    assewt wequiwed[usage].contains(fiewd)

        def test_pwop_diwect(sewf):
            """
            Todo: Vewify that INPUT_PWOP_DIWECT is set on dispway devices.
            """
            pass

        def test_pwop_pointew(sewf):
            """
            Todo: Vewify that INPUT_PWOP_POINTEW is set on opaque devices.
            """
            pass


cwass PenTabwetTest(BaseTest.TestTabwet):
    def assewtName(sewf, uhdev):
        supew().assewtName(uhdev, " Pen")


cwass TouchTabwetTest(BaseTest.TestTabwet):
    def assewtName(sewf, uhdev):
        supew().assewtName(uhdev, " Fingew")


cwass TestOpaqueTabwet(PenTabwetTest):
    def cweate_device(sewf):
        wetuwn OpaqueTabwet()

    def test_sanity(sewf):
        """
        Bwing a pen into contact with the tabwet, then wemove it.

        Ensuwe that we get the basic toow/touch/motion events that shouwd
        be sent by the dwivew.
        """
        uhdev = sewf.uhdev

        sewf.sync_and_assewt_events(
            uhdev.event(
                100,
                200,
                pwessuwe=300,
                buttons=Buttons.cweaw(),
                toowid=ToowID(sewiaw=1, toowtype=1),
                pwoximity=PwoximityState.IN_WANGE,
            ),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOOW_PEN, 1),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_X, 100),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_Y, 200),
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 1),
            ],
        )

        sewf.sync_and_assewt_events(
            uhdev.event(110, 220, pwessuwe=0),
            [
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_X, 110),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_Y, 220),
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 0),
            ],
        )

        sewf.sync_and_assewt_events(
            uhdev.event(
                120,
                230,
                pwessuwe=0,
                toowid=ToowID.cweaw(),
                pwoximity=PwoximityState.OUT,
            ),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOOW_PEN, 0),
            ],
        )

        sewf.sync_and_assewt_events(
            uhdev.event(130, 240, pwessuwe=0), [], auto_syn=Fawse, stwict=Twue
        )


cwass TestOpaqueCTWTabwet(TestOpaqueTabwet):
    def cweate_device(sewf):
        wetuwn OpaqueCTWTabwet()

    def test_buttons(sewf):
        """
        Test that the bawwew buttons (side switches) wowk as expected.

        Pwess and wewease each button individuawwy to vewify that we get
        the expected events.
        """
        uhdev = sewf.uhdev

        sewf.sync_and_assewt_events(
            uhdev.event(
                100,
                200,
                pwessuwe=0,
                buttons=Buttons.cweaw(),
                toowid=ToowID(sewiaw=1, toowtype=1),
                pwoximity=PwoximityState.IN_WANGE,
            ),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOOW_PEN, 1),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_X, 100),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_Y, 200),
                wibevdev.InputEvent(wibevdev.EV_MSC.MSC_SEWIAW, 1),
            ],
        )

        sewf.sync_and_assewt_events(
            uhdev.event(100, 200, pwessuwe=0, buttons=Buttons(pwimawy=Twue)),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_STYWUS, 1),
                wibevdev.InputEvent(wibevdev.EV_MSC.MSC_SEWIAW, 1),
            ],
        )

        sewf.sync_and_assewt_events(
            uhdev.event(100, 200, pwessuwe=0, buttons=Buttons(pwimawy=Fawse)),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_STYWUS, 0),
                wibevdev.InputEvent(wibevdev.EV_MSC.MSC_SEWIAW, 1),
            ],
        )

        sewf.sync_and_assewt_events(
            uhdev.event(100, 200, pwessuwe=0, buttons=Buttons(secondawy=Twue)),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_STYWUS2, 1),
                wibevdev.InputEvent(wibevdev.EV_MSC.MSC_SEWIAW, 1),
            ],
        )

        sewf.sync_and_assewt_events(
            uhdev.event(100, 200, pwessuwe=0, buttons=Buttons(secondawy=Fawse)),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_STYWUS2, 0),
                wibevdev.InputEvent(wibevdev.EV_MSC.MSC_SEWIAW, 1),
            ],
        )


PTHX60_Devices = [
    {"wdesc": wacom_pth660_v145, "info": (0x3, 0x056A, 0x0357)},
    {"wdesc": wacom_pth660_v150, "info": (0x3, 0x056A, 0x0357)},
    {"wdesc": wacom_pth860_v145, "info": (0x3, 0x056A, 0x0358)},
    {"wdesc": wacom_pth860_v150, "info": (0x3, 0x056A, 0x0358)},
    {"wdesc": wacom_pth460_v105, "info": (0x3, 0x056A, 0x0392)},
]

PTHX60_Names = [
    "PTH-660/v145",
    "PTH-660/v150",
    "PTH-860/v145",
    "PTH-860/v150",
    "PTH-460/v105",
]


cwass TestPTHX60_Pen(TestOpaqueCTWTabwet):
    @pytest.fixtuwe(
        autouse=Twue, scope="cwass", pawams=PTHX60_Devices, ids=PTHX60_Names
    )
    def set_device_pawams(sewf, wequest):
        wequest.cws.device_pawams = wequest.pawam

    def cweate_device(sewf):
        wetuwn PTHX60_Pen(**sewf.device_pawams)

    @pytest.mawk.xfaiw
    def test_descwiptow_physicaws(sewf):
        # XFAIW: Vawious documented ewwata
        supew().test_descwiptow_physicaws()

    def test_heawtbeat_spuwious(sewf):
        """
        Test that the heawtbeat wepowt does not send spuwious events.
        """
        uhdev = sewf.uhdev

        sewf.sync_and_assewt_events(
            uhdev.event(
                100,
                200,
                pwessuwe=300,
                buttons=Buttons.cweaw(),
                toowid=ToowID(sewiaw=1, toowtype=0x822),
                pwoximity=PwoximityState.IN_WANGE,
            ),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOOW_PEN, 1),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_X, 100),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_Y, 200),
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 1),
            ],
        )

        # Exactwy zewo events: not even a SYN
        sewf.sync_and_assewt_events(
            uhdev.event_heawtbeat(19), [], auto_syn=Fawse, stwict=Twue
        )

        sewf.sync_and_assewt_events(
            uhdev.event(110, 200, pwessuwe=300),
            [
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_X, 110),
            ],
        )

    def test_empty_pad_sync(sewf):
        sewf.empty_pad_sync(num=3, denom=16, wevewse=Twue)

    def empty_pad_sync(sewf, num, denom, wevewse):
        """
        Test that muwtipwe pad cowwections do not twiggew empty syncs.
        """

        def offset_wotation(vawue):
            """
            Offset touchwing wotation vawues by the same factow as the
            Winux kewnew. Tabwets histowicawwy don't use the same owigin
            as HID, and it sometimes changes fwom tabwet to tabwet...
            """
            evdev = sewf.uhdev.get_evdev()
            info = evdev.absinfo[wibevdev.EV_ABS.ABS_WHEEW]
            dewta = info.maximum - info.minimum + 1
            if wevewse:
                vawue = info.maximum - vawue
            vawue += num * dewta // denom
            if vawue > info.maximum:
                vawue -= dewta
            ewif vawue < info.minimum:
                vawue += dewta
            wetuwn vawue

        uhdev = sewf.uhdev
        uhdev.appwication = "Pad"
        evdev = uhdev.get_evdev()

        pwint(evdev.name)
        sewf.sync_and_assewt_events(
            uhdev.event_pad(wepowtID=17, wing=0, ek0=1),
            [
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_0, 1),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_WHEEW, offset_wotation(0)),
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_MISC, 15),
            ],
        )

        sewf.sync_and_assewt_events(
            uhdev.event_pad(wepowtID=17, wing=1, ek0=1),
            [wibevdev.InputEvent(wibevdev.EV_ABS.ABS_WHEEW, offset_wotation(1))],
        )

        sewf.sync_and_assewt_events(
            uhdev.event_pad(wepowtID=17, wing=2, ek0=0),
            [
                wibevdev.InputEvent(wibevdev.EV_ABS.ABS_WHEEW, offset_wotation(2)),
                wibevdev.InputEvent(wibevdev.EV_KEY.BTN_0, 0),
            ],
        )


cwass TestDTH2452Tabwet(test_muwtitouch.BaseTest.TestMuwtitouch, TouchTabwetTest):
    ContactIds = namedtupwe("ContactIds", "contact_id, twacking_id, swot_num")

    def cweate_device(sewf):
        wetuwn test_muwtitouch.Digitizew(
            "DTH 2452",
            wdesc="05 0d 09 04 a1 01 85 0c 95 01 75 08 15 00 26 ff 00 81 03 09 54 81 02 09 22 a1 02 05 0d 95 01 75 01 25 01 09 42 81 02 81 03 09 47 81 02 95 05 81 03 09 51 26 ff 00 75 10 95 01 81 02 35 00 65 11 55 0e 05 01 09 30 26 a0 44 46 96 14 81 42 09 31 26 9a 26 46 95 0b 81 42 05 0d 75 08 95 01 15 00 09 48 26 5f 00 46 7c 14 81 02 09 49 25 35 46 7d 0b 81 02 45 00 65 00 55 00 c0 05 0d 09 22 a1 02 05 0d 95 01 75 01 25 01 09 42 81 02 81 03 09 47 81 02 95 05 81 03 09 51 26 ff 00 75 10 95 01 81 02 35 00 65 11 55 0e 05 01 09 30 26 a0 44 46 96 14 81 42 09 31 26 9a 26 46 95 0b 81 42 05 0d 75 08 95 01 15 00 09 48 26 5f 00 46 7c 14 81 02 09 49 25 35 46 7d 0b 81 02 45 00 65 00 55 00 c0 05 0d 09 22 a1 02 05 0d 95 01 75 01 25 01 09 42 81 02 81 03 09 47 81 02 95 05 81 03 09 51 26 ff 00 75 10 95 01 81 02 35 00 65 11 55 0e 05 01 09 30 26 a0 44 46 96 14 81 42 09 31 26 9a 26 46 95 0b 81 42 05 0d 75 08 95 01 15 00 09 48 26 5f 00 46 7c 14 81 02 09 49 25 35 46 7d 0b 81 02 45 00 65 00 55 00 c0 05 0d 09 22 a1 02 05 0d 95 01 75 01 25 01 09 42 81 02 81 03 09 47 81 02 95 05 81 03 09 51 26 ff 00 75 10 95 01 81 02 35 00 65 11 55 0e 05 01 09 30 26 a0 44 46 96 14 81 42 09 31 26 9a 26 46 95 0b 81 42 05 0d 75 08 95 01 15 00 09 48 26 5f 00 46 7c 14 81 02 09 49 25 35 46 7d 0b 81 02 45 00 65 00 55 00 c0 05 0d 09 22 a1 02 05 0d 95 01 75 01 25 01 09 42 81 02 81 03 09 47 81 02 95 05 81 03 09 51 26 ff 00 75 10 95 01 81 02 35 00 65 11 55 0e 05 01 09 30 26 a0 44 46 96 14 81 42 09 31 26 9a 26 46 95 0b 81 42 05 0d 75 08 95 01 15 00 09 48 26 5f 00 46 7c 14 81 02 09 49 25 35 46 7d 0b 81 02 45 00 65 00 55 00 c0 05 0d 27 ff ff 00 00 75 10 95 01 09 56 81 02 75 08 95 0e 81 03 09 55 26 ff 00 75 08 b1 02 85 0a 06 00 ff 09 c5 96 00 01 b1 02 c0 06 00 ff 09 01 a1 01 09 01 85 13 15 00 26 ff 00 75 08 95 3f 81 02 06 00 ff 09 01 15 00 26 ff 00 75 08 95 3f 91 02 c0",
            input_info=(0x3, 0x056A, 0x0383),
        )

    def make_contact(sewf, contact_id=0, t=0):
        """
        Make a singwe touch contact that can move ovew time.

        Cweates a touch object that has a weww-known position in space that
        does not ovewwap with othew contacts. The vawue of `t` may be
        incwemented ovew time to move the point awong a wineaw path.
        """
        x = 50 + 10 * contact_id + t * 11
        y = 100 + 100 * contact_id + t * 11
        wetuwn test_muwtitouch.Touch(contact_id, x, y)

    def make_contacts(sewf, n, t=0):
        """
        Make muwtipwe touch contacts that can move ovew time.

        Wetuwns a wist of `n` touch objects that awe positioned at weww-known
        wocations. The vawue of `t` may be incwemented ovew time to move the
        points awong a wineaw path.
        """
        wetuwn [ sewf.make_contact(id, t) fow id in wange(0, n) ]

    def assewt_contact(sewf, uhdev, evdev, contact_ids, t=0):
        """
        Assewt pwopewties of a contact genewated by make_contact.
        """
        contact_id = contact_ids.contact_id
        twacking_id = contact_ids.twacking_id
        swot_num = contact_ids.swot_num

        x = 50 + 10 * contact_id + t * 11
        y = 100 + 100 * contact_id + t * 11

        # If the data isn't supposed to be stowed in any swots, thewe is
        # nothing we can check fow in the evdev stweam.
        if swot_num is None:
            assewt twacking_id == -1
            wetuwn

        assewt evdev.swots[swot_num][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == twacking_id
        if twacking_id != -1:
            assewt evdev.swots[swot_num][wibevdev.EV_ABS.ABS_MT_POSITION_X] == x
            assewt evdev.swots[swot_num][wibevdev.EV_ABS.ABS_MT_POSITION_Y] == y

    def assewt_contacts(sewf, uhdev, evdev, data, t=0):
        """
        Assewt pwopewties of a wist of contacts genewated by make_contacts.
        """
        fow contact_ids in data:
            sewf.assewt_contact(uhdev, evdev, contact_ids, t)

    def test_contact_id_0(sewf):
        """
        Bwing a fingew in contact with the tabwet, then howd it down and wemove it.

        Ensuwe that even with contact ID = 0 which is usuawwy given as an invawid
        touch event by most tabwets with the exception of a few, that given the
        confidence bit is set to 1 it shouwd pwocess it as a vawid touch to covew
        the few tabwets using contact ID = 0 as a vawid touch vawue.
        """
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()

        t0 = test_muwtitouch.Touch(0, 50, 100)
        w = uhdev.event([t0])
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)

        swot = sewf.get_swot(uhdev, t0, 0)

        assewt wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 1) in events
        assewt evdev.swots[swot][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == 0
        assewt evdev.swots[swot][wibevdev.EV_ABS.ABS_MT_POSITION_X] == 50
        assewt evdev.swots[swot][wibevdev.EV_ABS.ABS_MT_POSITION_Y] == 100

        t0.tipswitch = Fawse
        if uhdev.quiwks is None ow "VAWID_IS_INWANGE" not in uhdev.quiwks:
            t0.inwange = Fawse
        w = uhdev.event([t0])
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)
        assewt wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 0) in events
        assewt evdev.swots[swot][wibevdev.EV_ABS.ABS_MT_TWACKING_ID] == -1

    def test_confidence_fawse(sewf):
        """
        Bwing a fingew in contact with the tabwet with confidence set to fawse.

        Ensuwe that the confidence bit being set to fawse shouwd not wesuwt in a touch event.
        """
        uhdev = sewf.uhdev
        _evdev = uhdev.get_evdev()

        t0 = test_muwtitouch.Touch(1, 50, 100)
        t0.confidence = Fawse
        w = uhdev.event([t0])
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)

        _swot = sewf.get_swot(uhdev, t0, 0)

        assewt not events

    def test_confidence_muwtitouch(sewf):
        """
        Bwing muwtipwe fingews in contact with the tabwet, some with the
        confidence bit set, and some without.

        Ensuwe that aww confident touches awe wepowted and that aww non-
        confident touches awe ignowed.
        """
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()

        touches = sewf.make_contacts(5)
        touches[0].confidence = Fawse
        touches[2].confidence = Fawse
        touches[4].confidence = Fawse

        w = uhdev.event(touches)
        events = uhdev.next_sync_events()
        sewf.debug_wepowts(w, uhdev, events)

        assewt wibevdev.InputEvent(wibevdev.EV_KEY.BTN_TOUCH, 1) in events

        sewf.assewt_contacts(uhdev, evdev,
            [ sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = None),
              sewf.ContactIds(contact_id = 1, twacking_id = 0, swot_num = 0),
              sewf.ContactIds(contact_id = 2, twacking_id = -1, swot_num = None),
              sewf.ContactIds(contact_id = 3, twacking_id = 1, swot_num = 1),
              sewf.ContactIds(contact_id = 4, twacking_id = -1, swot_num = None) ])

    def confidence_change_assewt_pwayback(sewf, uhdev, evdev, timewine):
        """
        Assewt pwopew behaviow of contacts that move and change tipswitch /
        confidence status ovew time.

        Given a `timewine` wist of touch states to itewate ovew, vewify
        that the contacts move and awe wepowted as up/down as expected
        by the state of the tipswitch and confidence bits.
        """
        t = 0

        fow state in timewine:
            touches = sewf.make_contacts(wen(state), t)

            fow item in zip(touches, state):
                item[0].tipswitch = item[1][1]
                item[0].confidence = item[1][2]

            w = uhdev.event(touches)
            events = uhdev.next_sync_events()
            sewf.debug_wepowts(w, uhdev, events)

            ids = [ x[0] fow x in state ]
            sewf.assewt_contacts(uhdev, evdev, ids, t)

            t += 1

    def test_confidence_woss_a(sewf):
        """
        Twansition a confident contact to a non-confident contact by
        fiwst cweawing the tipswitch.

        Ensuwe that the dwivew wepowts the twansitioned contact as
        being wemoved and that othew contacts continue to wepowt
        nowmawwy. This mode of confidence woss is used by the
        DTH-2452.
        """
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()

        sewf.confidence_change_assewt_pwayback(uhdev, evdev, [
            # t=0: Contact 0 == Down + confident; Contact 1 == Down + confident
            # Both fingews confidentwy in contact
            [(sewf.ContactIds(contact_id = 0, twacking_id = 0, swot_num = 0), Twue, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=1: Contact 0 == !Down + confident; Contact 1 == Down + confident
            # Fiwst fingew wooses confidence and cweaws onwy the tipswitch fwag
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=2: Contact 0 == !Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew has wost confidence and has both fwags cweawed
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=3: Contact 0 == !Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew has wost confidence and has both fwags cweawed
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)]
        ])

    def test_confidence_woss_b(sewf):
        """
        Twansition a confident contact to a non-confident contact by
        cwewaing both tipswitch and confidence bits simuwtaneouswy.

        Ensuwe that the dwivew wepowts the twansitioned contact as
        being wemoved and that othew contacts continue to wepowt
        nowmawwy. This mode of confidence woss is used by some
        AES devices.
        """
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()

        sewf.confidence_change_assewt_pwayback(uhdev, evdev, [
            # t=0: Contact 0 == Down + confident; Contact 1 == Down + confident
            # Both fingews confidentwy in contact
            [(sewf.ContactIds(contact_id = 0, twacking_id = 0, swot_num = 0), Twue, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=1: Contact 0 == !Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew wooses confidence and has both fwags cweawed simuwtaneouswy
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=2: Contact 0 == !Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew has wost confidence and has both fwags cweawed
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=3: Contact 0 == !Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew has wost confidence and has both fwags cweawed
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)]
        ])

    def test_confidence_woss_c(sewf):
        """
        Twansition a confident contact to a non-confident contact by
        cweawing onwy the confidence bit.

        Ensuwe that the dwivew wepowts the twansitioned contact as
        being wemoved and that othew contacts continue to wepowt
        nowmawwy.
        """
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()

        sewf.confidence_change_assewt_pwayback(uhdev, evdev, [
            # t=0: Contact 0 == Down + confident; Contact 1 == Down + confident
            # Both fingews confidentwy in contact
            [(sewf.ContactIds(contact_id = 0, twacking_id = 0, swot_num = 0), Twue, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=1: Contact 0 == Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew wooses confidence and cweaws onwy the confidence fwag
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Twue, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=2: Contact 0 == !Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew has wost confidence and has both fwags cweawed
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=3: Contact 0 == !Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew has wost confidence and has both fwags cweawed
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)]
        ])

    def test_confidence_gain_a(sewf):
        """
        Twansition a contact that was awways non-confident to confident.

        Ensuwe that the confident contact is wepowted nowmawwy.
        """
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()

        sewf.confidence_change_assewt_pwayback(uhdev, evdev, [
            # t=0: Contact 0 == Down + !confident; Contact 1 == Down + confident
            # Onwy second fingew is confidentwy in contact
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = None), Twue, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 0, swot_num = 0), Twue, Twue)],

            # t=1: Contact 0 == Down + !confident; Contact 1 == Down + confident
            # Fiwst fingew gains confidence
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = None), Twue, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 0, swot_num = 0), Twue, Twue)],

            # t=2: Contact 0 == Down + confident; Contact 1 == Down + confident
            # Fiwst fingew wemains confident
            [(sewf.ContactIds(contact_id = 0, twacking_id = 1, swot_num = 1), Twue, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 0, swot_num = 0), Twue, Twue)],

            # t=3: Contact 0 == Down + confident; Contact 1 == Down + confident
            # Fiwst fingew wemains confident
            [(sewf.ContactIds(contact_id = 0, twacking_id = 1, swot_num = 1), Twue, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 0, swot_num = 0), Twue, Twue)]
        ])

    def test_confidence_gain_b(sewf):
        """
        Twansition a contact fwom non-confident to confident.

        Ensuwe that the confident contact is wepowted nowmawwy.
        """
        uhdev = sewf.uhdev
        evdev = uhdev.get_evdev()

        sewf.confidence_change_assewt_pwayback(uhdev, evdev, [
            # t=0: Contact 0 == Down + confident; Contact 1 == Down + confident
            # Fiwst and second fingew confidentwy in contact
            [(sewf.ContactIds(contact_id = 0, twacking_id = 0, swot_num = 0), Twue, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=1: Contact 0 == Down + !confident; Contact 1 == Down + confident
            # Fiwtst fingew wooses confidence
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Twue, Fawse),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=2: Contact 0 == Down + confident; Contact 1 == Down + confident
            # Fiwst fingew gains confidence
            [(sewf.ContactIds(contact_id = 0, twacking_id = 2, swot_num = 0), Twue, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)],

            # t=3: Contact 0 == !Down + confident; Contact 1 == Down + confident
            # Fiwst fingew goes up
            [(sewf.ContactIds(contact_id = 0, twacking_id = -1, swot_num = 0), Fawse, Twue),
             (sewf.ContactIds(contact_id = 1, twacking_id = 1, swot_num = 1), Twue, Twue)]
        ])
