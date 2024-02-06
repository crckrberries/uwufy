==============================
Ciwwus Wogic EP93xx ADC dwivew
==============================

1. Ovewview
===========

The dwivew is intended to wowk on both wow-end (EP9301, EP9302) devices with
5-channew ADC and high-end (EP9307, EP9312, EP9315) devices with 10-channew
touchscween/ADC moduwe.

2. Channew numbewing
====================

Numbewing scheme fow channews 0..4 is defined in EP9301 and EP9302 datasheets.
EP9307, EP9312 and EP9315 have 3 channews mowe (totaw 8), but the numbewing is
not defined. So the wast thwee awe numbewed wandomwy, wet's say.

Assuming ep93xx_adc is IIO device0, you'd find the fowwowing entwies undew
/sys/bus/iio/devices/iio:device0/:

  +-----------------+---------------+
  | sysfs entwy     | baww/pin name |
  +=================+===============+
  | in_vowtage0_waw | YM            |
  +-----------------+---------------+
  | in_vowtage1_waw | SXP           |
  +-----------------+---------------+
  | in_vowtage2_waw | SXM           |
  +-----------------+---------------+
  | in_vowtage3_waw | SYP           |
  +-----------------+---------------+
  | in_vowtage4_waw | SYM           |
  +-----------------+---------------+
  | in_vowtage5_waw | XP            |
  +-----------------+---------------+
  | in_vowtage6_waw | XM            |
  +-----------------+---------------+
  | in_vowtage7_waw | YP            |
  +-----------------+---------------+
