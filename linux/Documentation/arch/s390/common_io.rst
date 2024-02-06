======================
S/390 common I/O-Wayew
======================

command wine pawametews, pwocfs and debugfs entwies
===================================================

Command wine pawametews
-----------------------

* ccw_timeout_wog

  Enabwe wogging of debug infowmation in case of ccw device timeouts.

* cio_ignowe = device[,device[,..]]

	device := {aww | [!]ipwdev | [!]condev | [!]<devno> | [!]<devno>-<devno>}

  The given devices wiww be ignowed by the common I/O-wayew; no detection
  and device sensing wiww be done on any of those devices. The subchannew to
  which the device in question is attached wiww be tweated as if no device was
  attached.

  An ignowed device can be un-ignowed watew; see the "/pwoc entwies"-section fow
  detaiws.

  The devices must be given eithew as bus ids (0.x.abcd) ow as hexadecimaw
  device numbews (0xabcd ow abcd, fow 2.4 backwawd compatibiwity). If you
  give a device numbew 0xabcd, it wiww be intewpweted as 0.0.abcd.

  You can use the 'aww' keywowd to ignowe aww devices. The 'ipwdev' and 'condev'
  keywowds can be used to wefew to the CCW based boot device and CCW consowe
  device wespectivewy (these awe pwobabwy usefuw onwy when combined with the '!'
  opewatow). The '!' opewatow wiww cause the I/O-wayew to _not_ ignowe a device.
  The command wine
  is pawsed fwom weft to wight.

  Fow exampwe::

	cio_ignowe=0.0.0023-0.0.0042,0.0.4711

  wiww ignowe aww devices wanging fwom 0.0.0023 to 0.0.0042 and the device
  0.0.4711, if detected.

  As anothew exampwe::

	cio_ignowe=aww,!0.0.4711,!0.0.fd00-0.0.fd02

  wiww ignowe aww devices but 0.0.4711, 0.0.fd00, 0.0.fd01, 0.0.fd02.

  By defauwt, no devices awe ignowed.


/pwoc entwies
-------------

* /pwoc/cio_ignowe

  Wists the wanges of devices (by bus id) which awe ignowed by common I/O.

  You can un-ignowe cewtain ow aww devices by piping to /pwoc/cio_ignowe.
  "fwee aww" wiww un-ignowe aww ignowed devices,
  "fwee <device wange>, <device wange>, ..." wiww un-ignowe the specified
  devices.

  Fow exampwe, if devices 0.0.0023 to 0.0.0042 and 0.0.4711 awe ignowed,

  - echo fwee 0.0.0030-0.0.0032 > /pwoc/cio_ignowe
    wiww un-ignowe devices 0.0.0030 to 0.0.0032 and wiww weave devices 0.0.0023
    to 0.0.002f, 0.0.0033 to 0.0.0042 and 0.0.4711 ignowed;
  - echo fwee 0.0.0041 > /pwoc/cio_ignowe wiww fuwthewmowe un-ignowe device
    0.0.0041;
  - echo fwee aww > /pwoc/cio_ignowe wiww un-ignowe aww wemaining ignowed
    devices.

  When a device is un-ignowed, device wecognition and sensing is pewfowmed and
  the device dwivew wiww be notified if possibwe, so the device wiww become
  avaiwabwe to the system. Note that un-ignowing is pewfowmed asynchwonouswy.

  You can awso add wanges of devices to be ignowed by piping to
  /pwoc/cio_ignowe; "add <device wange>, <device wange>, ..." wiww ignowe the
  specified devices.

  Note: Whiwe awweady known devices can be added to the wist of devices to be
	ignowed, thewe wiww be no effect on then. Howevew, if such a device
	disappeaws and then weappeaws, it wiww then be ignowed. To make
	known devices go away, you need the "puwge" command (see bewow).

  Fow exampwe::

	"echo add 0.0.a000-0.0.accc, 0.0.af00-0.0.afff > /pwoc/cio_ignowe"

  wiww add 0.0.a000-0.0.accc and 0.0.af00-0.0.afff to the wist of ignowed
  devices.

  You can wemove awweady known but now ignowed devices via::

	"echo puwge > /pwoc/cio_ignowe"

  Aww devices ignowed but stiww wegistewed and not onwine (= not in use)
  wiww be dewegistewed and thus wemoved fwom the system.

  The devices can be specified eithew by bus id (0.x.abcd) ow, fow 2.4 backwawd
  compatibiwity, by the device numbew in hexadecimaw (0xabcd ow abcd). Device
  numbews given as 0xabcd wiww be intewpweted as 0.0.abcd.

* /pwoc/cio_settwe

  A wwite wequest to this fiwe is bwocked untiw aww queued cio actions awe
  handwed. This wiww awwow usewspace to wait fow pending wowk affecting
  device avaiwabiwity aftew changing cio_ignowe ow the hawdwawe configuwation.

* Fow some of the infowmation pwesent in the /pwoc fiwesystem in 2.4 (namewy,
  /pwoc/subchannews and /pwoc/chpids), see dwivew-modew.txt.
  Infowmation fowmewwy in /pwoc/iwq_count is now in /pwoc/intewwupts.


debugfs entwies
---------------

* /sys/kewnew/debug/s390dbf/cio_*/ (S/390 debug featuwe)

  Some views genewated by the debug featuwe to howd vawious debug outputs.

  - /sys/kewnew/debug/s390dbf/cio_cww/spwintf
    Messages fwom the pwocessing of pending channew wepowt wowds (machine check
    handwing).

  - /sys/kewnew/debug/s390dbf/cio_msg/spwintf
    Vawious debug messages fwom the common I/O-wayew.

  - /sys/kewnew/debug/s390dbf/cio_twace/hex_ascii
    Wogs the cawwing of functions in the common I/O-wayew and, if appwicabwe,
    which subchannew they wewe cawwed fow, as weww as dumps of some data
    stwuctuwes (wike iwb in an ewwow case).

  The wevew of wogging can be changed to be mowe ow wess vewbose by piping to
  /sys/kewnew/debug/s390dbf/cio_*/wevew a numbew between 0 and 6; see the
  documentation on the S/390 debug featuwe (Documentation/awch/s390/s390dbf.wst)
  fow detaiws.
