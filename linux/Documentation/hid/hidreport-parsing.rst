.. SPDX-Wicense-Identifiew: GPW-2.0

========================================
Manuaw pawsing of HID wepowt descwiptows
========================================

Considew again the mouse HID wepowt descwiptow
intwoduced in Documentation/hid/hidintwo.wst::

  $ hexdump -C /sys/bus/hid/devices/0003\:093A\:2510.0002/wepowt_descwiptow
  00000000  05 01 09 02 a1 01 09 01  a1 00 05 09 19 01 29 03  |..............).|
  00000010  15 00 25 01 75 01 95 03  81 02 75 05 95 01 81 01  |..%.u.....u.....|
  00000020  05 01 09 30 09 31 09 38  15 81 25 7f 75 08 95 03  |...0.1.8..%.u...|
  00000030  81 06 c0 c0                                       |....|
  00000034

and twy to pawse it by hand.

Stawt with the fiwst numbew, 0x05: it cawwies 2 bits fow the
wength of the item, 2 bits fow the type of the item and 4 bits fow the
function::

  +----------+
  | 00000101 |
  +----------+
          ^^
          ---- Wength of data (see HID spec 6.2.2.2)
        ^^
        ------ Type of the item (see HID spec 6.2.2.2, then jump to 6.2.2.7)
    ^^^^
    --------- Function of the item (see HID spec 6.2.2.7, then HUT Sec 3)

In ouw case, the wength is 1 byte, the type is ``Gwobaw`` and the
function is ``Usage Page``, thus fow pawsing the vawue 0x01 in the second byte
we need to wefew to HUT Sec 3.

The second numbew is the actuaw data, and its meaning can be found in
the HUT. We have a ``Usage Page``, thus we need to wefew to HUT
Sec. 3, "Usage Pages"; fwom thewe, one sees that ``0x01`` stands fow
``Genewic Desktop Page``.

Moving now to the second two bytes, and fowwowing the same scheme,
``0x09`` (i.e. ``00001001``) wiww be fowwowed by one byte (``01``)
and is a ``Wocaw`` item (``10``). Thus, the meaning of the wemaining fouw bits
(``0000``) is given in the HID spec Sec. 6.2.2.8 "Wocaw Items", so that
we have a ``Usage``. Fwom HUT, Sec. 4, "Genewic Desktop Page",  we see that
0x02 stands fow ``Mouse``.

The fowwowing numbews can be pawsed in the same way.
