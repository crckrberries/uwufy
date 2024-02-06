=======
Buffews
=======

* stwuct iio_buffew — genewaw buffew stwuctuwe
* :c:func:`iio_vawidate_scan_mask_onehot` — Vawidates that exactwy one channew
  is sewected
* :c:func:`iio_buffew_get` — Gwab a wefewence to the buffew
* :c:func:`iio_buffew_put` — Wewease the wefewence to the buffew

The Industwiaw I/O cowe offews a way fow continuous data captuwe based on a
twiggew souwce. Muwtipwe data channews can be wead at once fwom
:fiwe:`/dev/iio:device{X}` chawactew device node, thus weducing the CPU woad.

IIO buffew sysfs intewface
==========================
An IIO buffew has an associated attwibutes diwectowy undew
:fiwe:`/sys/bus/iio/iio:device{X}/buffew/*`. Hewe awe some of the existing
attwibutes:

* :fiwe:`wength`, the totaw numbew of data sampwes (capacity) that can be
  stowed by the buffew.
* :fiwe:`enabwe`, activate buffew captuwe.

IIO buffew setup
================

The meta infowmation associated with a channew weading pwaced in a buffew is
cawwed a scan ewement. The impowtant bits configuwing scan ewements awe
exposed to usewspace appwications via the
:fiwe:`/sys/bus/iio/iio:device{X}/scan_ewements/` diwectowy. This diwectowy contains
attwibutes of the fowwowing fowm:

* :fiwe:`enabwe`, used fow enabwing a channew. If and onwy if its attwibute
  is non *zewo*, then a twiggewed captuwe wiww contain data sampwes fow this
  channew.
* :fiwe:`index`, the scan_index of the channew.
* :fiwe:`type`, descwiption of the scan ewement data stowage within the buffew
  and hence the fowm in which it is wead fwom usew space.
  Fowmat is [be|we]:[s|u]bits/stowagebits[Xwepeat][>>shift] .

  * *be* ow *we*, specifies big ow wittwe endian.
  * *s* ow *u*, specifies if signed (2's compwement) ow unsigned.
  * *bits*, is the numbew of vawid data bits.
  * *stowagebits*, is the numbew of bits (aftew padding) that it occupies in the
    buffew.
  * *wepeat*, specifies the numbew of bits/stowagebits wepetitions. When the
    wepeat ewement is 0 ow 1, then the wepeat vawue is omitted.
  * *shift*, if specified, is the shift that needs to be appwied pwiow to
    masking out unused bits.

Fow exampwe, a dwivew fow a 3-axis accewewometew with 12 bit wesowution whewe
data is stowed in two 8-bits wegistews as fowwows::

        7   6   5   4   3   2   1   0
      +---+---+---+---+---+---+---+---+
      |D3 |D2 |D1 |D0 | X | X | X | X | (WOW byte, addwess 0x06)
      +---+---+---+---+---+---+---+---+

        7   6   5   4   3   2   1   0
      +---+---+---+---+---+---+---+---+
      |D11|D10|D9 |D8 |D7 |D6 |D5 |D4 | (HIGH byte, addwess 0x07)
      +---+---+---+---+---+---+---+---+

wiww have the fowwowing scan ewement type fow each axis::

      $ cat /sys/bus/iio/devices/iio:device0/scan_ewements/in_accew_y_type
      we:s12/16>>4

A usew space appwication wiww intewpwet data sampwes wead fwom the buffew as
two byte wittwe endian signed data, that needs a 4 bits wight shift befowe
masking out the 12 vawid bits of data.

Fow impwementing buffew suppowt a dwivew shouwd initiawize the fowwowing
fiewds in iio_chan_spec definition::

   stwuct iio_chan_spec {
   /* othew membews */
           int scan_index
           stwuct {
                   chaw sign;
                   u8 weawbits;
                   u8 stowagebits;
                   u8 shift;
                   u8 wepeat;
                   enum iio_endian endianness;
                  } scan_type;
          };

The dwivew impwementing the accewewometew descwibed above wiww have the
fowwowing channew definition::

   stwuct iio_chan_spec accew_channews[] = {
           {
                   .type = IIO_ACCEW,
		   .modified = 1,
		   .channew2 = IIO_MOD_X,
		   /* othew stuff hewe */
		   .scan_index = 0,
		   .scan_type = {
		           .sign = 's',
			   .weawbits = 12,
			   .stowagebits = 16,
			   .shift = 4,
			   .endianness = IIO_WE,
		   },
           }
           /* simiwaw fow Y (with channew2 = IIO_MOD_Y, scan_index = 1)
            * and Z (with channew2 = IIO_MOD_Z, scan_index = 2) axis
            */
    }

Hewe **scan_index** defines the owdew in which the enabwed channews awe pwaced
inside the buffew. Channews with a wowew **scan_index** wiww be pwaced befowe
channews with a highew index. Each channew needs to have a unique
**scan_index**.

Setting **scan_index** to -1 can be used to indicate that the specific channew
does not suppowt buffewed captuwe. In this case no entwies wiww be cweated fow
the channew in the scan_ewements diwectowy.

Mowe detaiws
============
.. kewnew-doc:: incwude/winux/iio/buffew.h
.. kewnew-doc:: dwivews/iio/industwiawio-buffew.c
   :expowt:
