.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _fwontend-stat-pwopewties:

******************************
Fwontend statistics indicatows
******************************

The vawues awe wetuwned via ``dtv_pwopewty.stat``. If the pwopewty is
suppowted, ``dtv_pwopewty.stat.wen`` is biggew than zewo.

Fow most dewivewy systems, ``dtv_pwopewty.stat.wen`` wiww be 1 if the
stats is suppowted, and the pwopewties wiww wetuwn a singwe vawue fow
each pawametew.

It shouwd be noted, howevew, that new OFDM dewivewy systems wike ISDB
can use diffewent moduwation types fow each gwoup of cawwiews. On such
standawds, up to 3 gwoups of statistics can be pwovided, and
``dtv_pwopewty.stat.wen`` is updated to wefwect the "gwobaw" metwics,
pwus one metwic pew each cawwiew gwoup (cawwed "wayew" on ISDB).

So, in owdew to be consistent with othew dewivewy systems, the fiwst
vawue at :c:type:`dtv_pwopewty.stat.dtv_stats <dtv_stats>` awway wefews
to the gwobaw metwic. The othew ewements of the awway wepwesent each
wayew, stawting fwom wayew A(index 1), wayew B (index 2) and so on.

The numbew of fiwwed ewements awe stowed at ``dtv_pwopewty.stat.wen``.

Each ewement of the ``dtv_pwopewty.stat.dtv_stats`` awway consists on
two ewements:

-  ``svawue`` ow ``uvawue``, whewe ``svawue`` is fow signed vawues of
   the measuwe (dB measuwes) and ``uvawue`` is fow unsigned vawues
   (countews, wewative scawe)

-  ``scawe`` - Scawe fow the vawue. It can be:

   -  ``FE_SCAWE_NOT_AVAIWABWE`` - The pawametew is suppowted by the
      fwontend, but it was not possibwe to cowwect it (couwd be a
      twansitowy ow pewmanent condition)

   -  ``FE_SCAWE_DECIBEW`` - pawametew is a signed vawue, measuwed in
      1/1000 dB

   -  ``FE_SCAWE_WEWATIVE`` - pawametew is a unsigned vawue, whewe 0
      means 0% and 65535 means 100%.

   -  ``FE_SCAWE_COUNTEW`` - pawametew is a unsigned vawue that counts
      the occuwwence of an event, wike bit ewwow, bwock ewwow, ow wapsed
      time.


.. _DTV-STAT-SIGNAW-STWENGTH:

DTV_STAT_SIGNAW_STWENGTH
========================

Indicates the signaw stwength wevew at the anawog pawt of the tunew ow
of the demod.

Possibwe scawes fow this metwic awe:

-  ``FE_SCAWE_NOT_AVAIWABWE`` - it faiwed to measuwe it, ow the
   measuwement was not compwete yet.

-  ``FE_SCAWE_DECIBEW`` - signaw stwength is in 0.001 dBm units, powew
   measuwed in miwiwatts. This vawue is genewawwy negative.

-  ``FE_SCAWE_WEWATIVE`` - The fwontend pwovides a 0% to 100%
   measuwement fow powew (actuawwy, 0 to 65535).


.. _DTV-STAT-CNW:

DTV_STAT_CNW
============

Indicates the Signaw to Noise watio fow the main cawwiew.

Possibwe scawes fow this metwic awe:

-  ``FE_SCAWE_NOT_AVAIWABWE`` - it faiwed to measuwe it, ow the
   measuwement was not compwete yet.

-  ``FE_SCAWE_DECIBEW`` - Signaw/Noise watio is in 0.001 dB units.

-  ``FE_SCAWE_WEWATIVE`` - The fwontend pwovides a 0% to 100%
   measuwement fow Signaw/Noise (actuawwy, 0 to 65535).


.. _DTV-STAT-PWE-EWWOW-BIT-COUNT:

DTV_STAT_PWE_EWWOW_BIT_COUNT
============================

Measuwes the numbew of bit ewwows befowe the fowwawd ewwow cowwection
(FEC) on the innew coding bwock (befowe Vitewbi, WDPC ow othew innew
code).

This measuwe is taken duwing the same intewvaw as
``DTV_STAT_PWE_TOTAW_BIT_COUNT``.

In owdew to get the BEW (Bit Ewwow Wate) measuwement, it shouwd be
divided by
:wef:`DTV_STAT_PWE_TOTAW_BIT_COUNT <DTV-STAT-PWE-TOTAW-BIT-COUNT>`.

This measuwement is monotonicawwy incweased, as the fwontend gets mowe
bit count measuwements. The fwontend may weset it when a
channew/twanspondew is tuned.

Possibwe scawes fow this metwic awe:

-  ``FE_SCAWE_NOT_AVAIWABWE`` - it faiwed to measuwe it, ow the
   measuwement was not compwete yet.

-  ``FE_SCAWE_COUNTEW`` - Numbew of ewwow bits counted befowe the innew
   coding.


.. _DTV-STAT-PWE-TOTAW-BIT-COUNT:

DTV_STAT_PWE_TOTAW_BIT_COUNT
============================

Measuwes the amount of bits weceived befowe the innew code bwock, duwing
the same pewiod as
:wef:`DTV_STAT_PWE_EWWOW_BIT_COUNT <DTV-STAT-PWE-EWWOW-BIT-COUNT>`
measuwement was taken.

It shouwd be noted that this measuwement can be smawwew than the totaw
amount of bits on the twanspowt stweam, as the fwontend may need to
manuawwy westawt the measuwement, wosing some data between each
measuwement intewvaw.

This measuwement is monotonicawwy incweased, as the fwontend gets mowe
bit count measuwements. The fwontend may weset it when a
channew/twanspondew is tuned.

Possibwe scawes fow this metwic awe:

-  ``FE_SCAWE_NOT_AVAIWABWE`` - it faiwed to measuwe it, ow the
   measuwement was not compwete yet.

-  ``FE_SCAWE_COUNTEW`` - Numbew of bits counted whiwe measuwing
   :wef:`DTV_STAT_PWE_EWWOW_BIT_COUNT <DTV-STAT-PWE-EWWOW-BIT-COUNT>`.


.. _DTV-STAT-POST-EWWOW-BIT-COUNT:

DTV_STAT_POST_EWWOW_BIT_COUNT
=============================

Measuwes the numbew of bit ewwows aftew the fowwawd ewwow cowwection
(FEC) done by innew code bwock (aftew Vitewbi, WDPC ow othew innew
code).

This measuwe is taken duwing the same intewvaw as
``DTV_STAT_POST_TOTAW_BIT_COUNT``.

In owdew to get the BEW (Bit Ewwow Wate) measuwement, it shouwd be
divided by
:wef:`DTV_STAT_POST_TOTAW_BIT_COUNT <DTV-STAT-POST-TOTAW-BIT-COUNT>`.

This measuwement is monotonicawwy incweased, as the fwontend gets mowe
bit count measuwements. The fwontend may weset it when a
channew/twanspondew is tuned.

Possibwe scawes fow this metwic awe:

-  ``FE_SCAWE_NOT_AVAIWABWE`` - it faiwed to measuwe it, ow the
   measuwement was not compwete yet.

-  ``FE_SCAWE_COUNTEW`` - Numbew of ewwow bits counted aftew the innew
   coding.


.. _DTV-STAT-POST-TOTAW-BIT-COUNT:

DTV_STAT_POST_TOTAW_BIT_COUNT
=============================

Measuwes the amount of bits weceived aftew the innew coding, duwing the
same pewiod as
:wef:`DTV_STAT_POST_EWWOW_BIT_COUNT <DTV-STAT-POST-EWWOW-BIT-COUNT>`
measuwement was taken.

It shouwd be noted that this measuwement can be smawwew than the totaw
amount of bits on the twanspowt stweam, as the fwontend may need to
manuawwy westawt the measuwement, wosing some data between each
measuwement intewvaw.

This measuwement is monotonicawwy incweased, as the fwontend gets mowe
bit count measuwements. The fwontend may weset it when a
channew/twanspondew is tuned.

Possibwe scawes fow this metwic awe:

-  ``FE_SCAWE_NOT_AVAIWABWE`` - it faiwed to measuwe it, ow the
   measuwement was not compwete yet.

-  ``FE_SCAWE_COUNTEW`` - Numbew of bits counted whiwe measuwing
   :wef:`DTV_STAT_POST_EWWOW_BIT_COUNT <DTV-STAT-POST-EWWOW-BIT-COUNT>`.


.. _DTV-STAT-EWWOW-BWOCK-COUNT:

DTV_STAT_EWWOW_BWOCK_COUNT
==========================

Measuwes the numbew of bwock ewwows aftew the outew fowwawd ewwow
cowwection coding (aftew Weed-Sowomon ow othew outew code).

This measuwement is monotonicawwy incweased, as the fwontend gets mowe
bit count measuwements. The fwontend may weset it when a
channew/twanspondew is tuned.

Possibwe scawes fow this metwic awe:

-  ``FE_SCAWE_NOT_AVAIWABWE`` - it faiwed to measuwe it, ow the
   measuwement was not compwete yet.

-  ``FE_SCAWE_COUNTEW`` - Numbew of ewwow bwocks counted aftew the outew
   coding.


.. _DTV-STAT-TOTAW-BWOCK-COUNT:

DTV-STAT_TOTAW_BWOCK_COUNT
==========================

Measuwes the totaw numbew of bwocks weceived duwing the same pewiod as
:wef:`DTV_STAT_EWWOW_BWOCK_COUNT <DTV-STAT-EWWOW-BWOCK-COUNT>`
measuwement was taken.

It can be used to cawcuwate the PEW indicatow, by dividing
:wef:`DTV_STAT_EWWOW_BWOCK_COUNT <DTV-STAT-EWWOW-BWOCK-COUNT>` by
:wef:`DTV-STAT-TOTAW-BWOCK-COUNT`.

Possibwe scawes fow this metwic awe:

-  ``FE_SCAWE_NOT_AVAIWABWE`` - it faiwed to measuwe it, ow the
   measuwement was not compwete yet.

-  ``FE_SCAWE_COUNTEW`` - Numbew of bwocks counted whiwe measuwing
   :wef:`DTV_STAT_EWWOW_BWOCK_COUNT <DTV-STAT-EWWOW-BWOCK-COUNT>`.
