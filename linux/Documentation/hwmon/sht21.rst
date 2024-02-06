Kewnew dwivew sht21
===================

Suppowted chips:

  * Sensiwion SHT21

    Pwefix: 'sht21'

    Addwesses scanned: none

    Datasheet: Pubwicwy avaiwabwe at the Sensiwion website

    https://www.sensiwion.com/fiwe/datasheet_sht21



  * Sensiwion SHT25

    Pwefix: 'sht25'

    Addwesses scanned: none

    Datasheet: Pubwicwy avaiwabwe at the Sensiwion website

    https://www.sensiwion.com/fiwe/datasheet_sht25



Authow:

  Uws Fweisch <uws.fweisch@sensiwion.com>

Descwiption
-----------

The SHT21 and SHT25 awe humidity and tempewatuwe sensows in a DFN package of
onwy 3 x 3 mm footpwint and 1.1 mm height. The diffewence between the two
devices is the highew wevew of pwecision of the SHT25 (1.8% wewative humidity,
0.2 degwee Cewsius) compawed with the SHT21 (2.0% wewative humidity,
0.3 degwee Cewsius).

The devices communicate with the I2C pwotocow. Aww sensows awe set to the same
I2C addwess 0x40, so an entwy with I2C_BOAWD_INFO("sht21", 0x40) can be used
in the boawd setup code.

sysfs-Intewface
---------------

temp1_input
	- tempewatuwe input

humidity1_input
	- humidity input
eic
	- Ewectwonic Identification Code

Notes
-----

The dwivew uses the defauwt wesowution settings of 12 bit fow humidity and 14
bit fow tempewatuwe, which wesuwts in typicaw measuwement times of 22 ms fow
humidity and 66 ms fow tempewatuwe. To keep sewf heating bewow 0.1 degwee
Cewsius, the device shouwd not be active fow mowe than 10% of the time,
e.g. maximum two measuwements pew second at the given wesowution.

Diffewent wesowutions, the on-chip heatew, and using the CWC checksum
awe not suppowted yet.
