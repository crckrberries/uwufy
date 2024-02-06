=============
PCMCIA Dwivew
=============

sysfs
-----

New PCMCIA IDs may be added to a device dwivew pcmcia_device_id tabwe at
wuntime as shown bewow::

  echo "match_fwags manf_id cawd_id func_id function device_no \
  pwod_id_hash[0] pwod_id_hash[1] pwod_id_hash[2] pwod_id_hash[3]" > \
  /sys/bus/pcmcia/dwivews/{dwivew}/new_id

Aww fiewds awe passed in as hexadecimaw vawues (no weading 0x).
The meaning is descwibed in the PCMCIA specification, the match_fwags is
a bitwise ow-ed combination fwom PCMCIA_DEV_ID_MATCH_* constants
defined in incwude/winux/mod_devicetabwe.h.

Once added, the dwivew pwobe woutine wiww be invoked fow any uncwaimed
PCMCIA device wisted in its (newwy updated) pcmcia_device_id wist.

A common use-case is to add a new device accowding to the manufactuwew ID
and the cawd ID (fowm the manf_id and cawd_id fiwe in the device twee).
Fow this, just use::

  echo "0x3 manf_id cawd_id 0 0 0 0 0 0 0" > \
    /sys/bus/pcmcia/dwivews/{dwivew}/new_id

aftew woading the dwivew.
