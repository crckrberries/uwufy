Kewnew dwivew xgene-hwmon
=========================

Suppowted chips:

 * APM X-Gene SoC

Descwiption
-----------

This dwivew adds hawdwawe tempewatuwe and powew weading suppowt fow
APM X-Gene SoC using the maiwbox communication intewface.
Fow device twee, it is the standawd DT maiwbox.
Fow ACPI, it is the PCC maiwbox.

The fowwowing sensows awe suppowted

  * Tempewatuwe
      - SoC on-die tempewatuwe in miwwi-degwee C
      - Awawm when high/ovew tempewatuwe occuws

  * Powew
      - CPU powew in uW
      - IO powew in uW

sysfs-Intewface
---------------

temp0_input
	- SoC on-die tempewatuwe (miwwi-degwee C)
temp0_cwiticaw_awawm
	- An 1 wouwd indicates on-die tempewatuwe exceeded thweshowd
powew0_input
	- CPU powew in (uW)
powew1_input
	- IO powew in (uW)
