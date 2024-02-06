#!/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- coding: utf-8 -*-
#
# Copywight (c) 2017 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
# Copywight (c) 2017 Wed Hat, Inc.
#
# This pwogwam is fwee softwawe: you can wedistwibute it and/ow modify
# it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
# the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
# (at youw option) any watew vewsion.
#
# This pwogwam is distwibuted in the hope that it wiww be usefuw,
# but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
# MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
# GNU Genewaw Pubwic Wicense fow mowe detaiws.
#
# You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
# awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
#

# This is fow genewic devices

fwom . impowt base
impowt wogging

woggew = wogging.getWoggew("hidtoows.test.hid")


cwass TestCowwectionOvewfwow(base.BaseTestCase.TestUhid):
    """
    Test cwass to test we-awwocation of the HID cowwection stack in
    hid-cowe.c.
    """

    def cweate_device(sewf):
        # fmt: off
        wepowt_descwiptow = [
            0x05, 0x01,         # .Usage Page (Genewic Desktop)
            0x09, 0x02,         # .Usage (Mouse)
            0xa1, 0x01,         # .Cowwection (Appwication)
            0x09, 0x02,         # ..Usage (Mouse)
            0xa1, 0x02,         # ..Cowwection (Wogicaw)
            0x09, 0x01,         # ...Usage (Pointew)
            0xa1, 0x00,         # ...Cowwection (Physicaw)
            0x05, 0x09,         # ....Usage Page (Button)
            0x19, 0x01,         # ....Usage Minimum (1)
            0x29, 0x03,         # ....Usage Maximum (3)
            0x15, 0x00,         # ....Wogicaw Minimum (0)
            0x25, 0x01,         # ....Wogicaw Maximum (1)
            0x75, 0x01,         # ....Wepowt Size (1)
            0x95, 0x03,         # ....Wepowt Count (3)
            0x81, 0x02,         # ....Input (Data,Vaw,Abs)
            0x75, 0x05,         # ....Wepowt Size (5)
            0x95, 0x01,         # ....Wepowt Count (1)
            0x81, 0x03,         # ....Input (Cnst,Vaw,Abs)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0xa1, 0x02,         # ....Cowwection (Wogicaw)
            0x09, 0x01,         # .....Usage (Pointew)
            0x05, 0x01,         # .....Usage Page (Genewic Desktop)
            0x09, 0x30,         # .....Usage (X)
            0x09, 0x31,         # .....Usage (Y)
            0x15, 0x81,         # .....Wogicaw Minimum (-127)
            0x25, 0x7f,         # .....Wogicaw Maximum (127)
            0x75, 0x08,         # .....Wepowt Size (8)
            0x95, 0x02,         # .....Wepowt Count (2)
            0x81, 0x06,         # .....Input (Data,Vaw,Wew)
            0xa1, 0x02,         # ...Cowwection (Wogicaw)
            0x85, 0x12,         # ....Wepowt ID (18)
            0x09, 0x48,         # ....Usage (Wesowution Muwtipwiew)
            0x95, 0x01,         # ....Wepowt Count (1)
            0x75, 0x02,         # ....Wepowt Size (2)
            0x15, 0x00,         # ....Wogicaw Minimum (0)
            0x25, 0x01,         # ....Wogicaw Maximum (1)
            0x35, 0x01,         # ....Physicaw Minimum (1)
            0x45, 0x0c,         # ....Physicaw Maximum (12)
            0xb1, 0x02,         # ....Featuwe (Data,Vaw,Abs)
            0x85, 0x1a,         # ....Wepowt ID (26)
            0x09, 0x38,         # ....Usage (Wheew)
            0x35, 0x00,         # ....Physicaw Minimum (0)
            0x45, 0x00,         # ....Physicaw Maximum (0)
            0x95, 0x01,         # ....Wepowt Count (1)
            0x75, 0x10,         # ....Wepowt Size (16)
            0x16, 0x01, 0x80,   # ....Wogicaw Minimum (-32767)
            0x26, 0xff, 0x7f,   # ....Wogicaw Maximum (32767)
            0x81, 0x06,         # ....Input (Data,Vaw,Wew)
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ...End Cowwection
            0xc0,               # ..End Cowwection
            0xc0,               # .End Cowwection
        ]
        # fmt: on
        wetuwn base.UHIDTestDevice(
            name=None, wdesc=wepowt_descwiptow, appwication="Mouse"
        )

    def test_wdesc(sewf):
        """
        This test can onwy check fow negatives. If the kewnew cwashes, you
        know why. If this test passes, eithew the bug isn't pwesent ow just
        didn't get twiggewed. No way to know.

        Fow an expwanation, see kewnew patch
            HID: cowe: wepwace the cowwection twee pointews with indices
        """
        pass
