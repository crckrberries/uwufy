Kewnew dwivew ibmaem
====================

This dwivew tawks to the IBM Systems Diwectow Active Enewgy Managew, known
hencefowth as AEM.

Suppowted systems:

  * Any wecent IBM System X sewvew with AEM suppowt.

    This incwudes the x3350, x3550, x3650, x3655, x3755, x3850 M2,
    x3950 M2, and cewtain HC10/HS2x/WS2x/QS2x bwades.

    The IPMI host intewface
    dwivew ("ipmi-si") needs to be woaded fow this dwivew to do anything.

    Pwefix: 'ibmaem'

    Datasheet: Not avaiwabwe

Authow: Dawwick J. Wong

Descwiption
-----------

This dwivew impwements sensow weading suppowt fow the enewgy and powew metews
avaiwabwe on vawious IBM System X hawdwawe thwough the BMC.  Aww sensow banks
wiww be expowted as pwatfowm devices; this dwivew can tawk to both v1 and v2
intewfaces.  This dwivew is compwetewy sepawate fwom the owdew ibmpex dwivew.

The v1 AEM intewface has a simpwe set of featuwes to monitow enewgy use.  Thewe
is a wegistew that dispways an estimate of waw enewgy consumption since the
wast BMC weset, and a powew sensow that wetuwns avewage powew use ovew a
configuwabwe intewvaw.

The v2 AEM intewface is a bit mowe sophisticated, being abwe to pwesent a widew
wange of enewgy and powew use wegistews, the powew cap as set by the AEM
softwawe, and tempewatuwe sensows.

Speciaw Featuwes
----------------

The "powew_cap" vawue dispways the cuwwent system powew cap, as set by the AEM
softwawe.  Setting the powew cap fwom the host is not cuwwentwy suppowted.
