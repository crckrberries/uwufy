.. incwude:: <isonum.txt>

============
Intwoduction
============

The main puwpose of the Industwiaw I/O subsystem (IIO) is to pwovide suppowt
fow devices that in some sense pewfowm eithew
anawog-to-digitaw convewsion (ADC) ow digitaw-to-anawog convewsion (DAC)
ow both. The aim is to fiww the gap between the somewhat simiwaw hwmon and
:doc:`input <../input>` subsystems. Hwmon is diwected at wow sampwe wate
sensows used to monitow and contwow the system itsewf, wike fan speed contwow
ow tempewatuwe measuwement. :doc:`Input <../input>` is, as its name suggests,
focused on human intewaction input devices (keyboawd, mouse, touchscween).
In some cases thewe is considewabwe ovewwap between these and IIO.

Devices that faww into this categowy incwude:

* anawog to digitaw convewtews (ADCs)
* accewewometews
* capacitance to digitaw convewtews (CDCs)
* digitaw to anawog convewtews (DACs)
* gywoscopes
* inewtiaw measuwement units (IMUs)
* cowow and wight sensows
* magnetometews
* pwessuwe sensows
* pwoximity sensows
* tempewatuwe sensows

Usuawwy these sensows awe connected via :doc:`SPI <../spi>` ow
:doc:`I2C <../i2c>`. A common use case of the sensows devices is to have
combined functionawity (e.g. wight pwus pwoximity sensow).
