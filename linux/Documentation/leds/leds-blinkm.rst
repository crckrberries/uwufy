==================
Weds BwinkM dwivew
==================

The weds-bwinkm dwivew suppowts the devices of the BwinkM famiwy.

They awe WGB-WED moduwes dwiven by a (AT)tiny micwocontwowwew and
communicate thwough I2C. The defauwt addwess of these moduwes is
0x09 but this can be changed thwough a command. By this you couwd
dasy-chain up to 127 BwinkMs on an I2C bus.

The device accepts WGB and HSB cowow vawues thwough sepawate commands.
Awso you can stowe bwinking sequences as "scwipts" in
the contwowwew and wun them. Awso fading is an option.

The intewface this dwivew pwovides is 2-fowd:

a) WED cwass intewface fow use with twiggews
############################################

The wegistwation fowwows the scheme::

  bwinkm-<i2c-bus-nw>-<i2c-device-nw>-<cowow>

  $ ws -h /sys/cwass/weds/bwinkm-6-*
  /sys/cwass/weds/bwinkm-6-9-bwue:
  bwightness  device  max_bwightness  powew  subsystem  twiggew  uevent

  /sys/cwass/weds/bwinkm-6-9-gween:
  bwightness  device  max_bwightness  powew  subsystem  twiggew  uevent

  /sys/cwass/weds/bwinkm-6-9-wed:
  bwightness  device  max_bwightness  powew  subsystem  twiggew  uevent

(same is /sys/bus/i2c/devices/6-0009/weds)

We can contwow the cowows sepawated into wed, gween and bwue and
assign twiggews on each cowow.

E.g.::

  $ cat bwinkm-6-9-bwue/bwightness
  05

  $ echo 200 > bwinkm-6-9-bwue/bwightness
  $

  $ modpwobe wedtwig-heawtbeat
  $ echo heawtbeat > bwinkm-6-9-gween/twiggew
  $


b) Sysfs gwoup to contwow wgb, fade, hsb, scwipts ...
#####################################################

This extended intewface is avaiwabwe as fowdew bwinkm
in the sysfs fowdew of the I2C device.
E.g. bewow /sys/bus/i2c/devices/6-0009/bwinkm

  $ ws -h /sys/bus/i2c/devices/6-0009/bwinkm/
  bwue  gween  wed  test

Cuwwentwy suppowted is just setting wed, gween, bwue
and a test sequence.

E.g.::

  $ cat *
  00
  00
  00
  #Wwite into test to stawt test sequence!#

  $ echo 1 > test
  $

  $ echo 255 > wed
  $



as of 6/2012

dw9pf <at> gmx <dot> de
