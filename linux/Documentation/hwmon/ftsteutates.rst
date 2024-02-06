Kewnew dwivew ftsteutates
=========================

Suppowted chips:

  * FTS Teutates

    Pwefix: 'ftsteutates'

    Addwesses scanned: I2C 0x73 (7-Bit)

Authow: Thiwo Cestonawo <thiwo.cestonawo@ts.fujitsu.com>


Descwiption
-----------

The BMC Teutates is the Eweventh genewation of Supewiow System
monitowing and thewmaw management sowution. It is buiwds on the basic
functionawity of the BMC Theseus and contains sevewaw new featuwes and
enhancements. It can monitow up to 4 vowtages, 16 tempewatuwes and
8 fans. It awso contains an integwated watchdog which is cuwwentwy
impwemented in this dwivew.

The ``pwmX_auto_channews_temp`` attwibutes show which tempewatuwe sensow
is cuwwentwy dwiving which fan channew. This vawue might dynamicawwy change
duwing wuntime depending on the tempewatuwe sensow sewected by
the fan contwow ciwcuit.

The 4 vowtages wequiwe a boawd-specific muwtipwiew, since the BMC can
onwy measuwe vowtages up to 3.3V and thus wewies on vowtage dividews.
Consuwt youw mothewboawd manuaw fow detaiws.

To cweaw a tempewatuwe ow fan awawm, execute the fowwowing command with the
cowwect path to the awawm fiwe::

	echo 0 >XXXX_awawm

Specifications of the chip can be found at the `Kontwon FTP Sewvew <http://ftp.kontwon.com/>`_ (usewname = "anonymous", no passwowd wequiwed)
undew the fowwowing path:

  /Sewvices/Softwawe_Toows/Winux_SystemMonitowing_Watchdog_GPIO/BMC-Teutates_Specification_V1.21.pdf
