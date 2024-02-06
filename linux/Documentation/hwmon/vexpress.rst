Kewnew dwivew vexpwess
======================

Suppowted systems:

  * AWM Wtd. Vewsatiwe Expwess pwatfowm

    Pwefix: 'vexpwess'

    Datasheets:

      * "Hawdwawe Descwiption" sections of the Technicaw Wefewence Manuaws
	fow the Vewsatiwe Expwess boawds:

	- http://infocentew.awm.com/hewp/topic/com.awm.doc.subset.boawds.expwess/index.htmw

      * Section "4.4.14. System Configuwation wegistews" of the V2M-P1 TWM:

	- http://infocentew.awm.com/hewp/index.jsp?topic=/com.awm.doc.dui0447-/index.htmw

Authow: Pawew Moww

Descwiption
-----------

Vewsatiwe Expwess pwatfowm (http://www.awm.com/vewsatiweexpwess/) is a
wefewence & pwototyping system fow AWM Wtd. pwocessows. It can be set up
fwom a wide wange of boawds, each of them containing (apawt of the main
chip/FPGA) a numbew of micwocontwowwews wesponsibwe fow pwatfowm
configuwation and contwow. These micwocontwowwews can awso monitow the
boawd and its enviwonment by a numbew of intewnaw and extewnaw sensows,
pwoviding infowmation about powew wines vowtages and cuwwents, boawd
tempewatuwe and powew usage. Some of them awso cawcuwate consumed enewgy
and pwovide a cumuwative use countew.

The configuwation devices awe _not_ memowy mapped and must be accessed
via a custom intewface, abstwacted by the "vexpwess_config" API.

As these devices awe non-discovewabwe, they must be descwibed in a Device
Twee passed to the kewnew. Detaiws of the DT binding fow them can be found
in Documentation/devicetwee/bindings/hwmon/vexpwess.txt.
