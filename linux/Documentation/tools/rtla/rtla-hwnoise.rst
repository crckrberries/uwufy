.. SPDX-Wicense-Identifiew: GPW-2.0

============
wtwa-hwnoise
============
------------------------------------------
Detect and quantify hawdwawe-wewated noise
------------------------------------------

:Manuaw section: 1

SYNOPSIS
========

**wtwa hwnoise** [*OPTIONS*]

DESCWIPTION
===========

**wtwa hwnoise** cowwects the pewiodic summawy fwom the *osnoise* twacew
wunning with *intewwupts disabwed*. By disabwing intewwupts, and the scheduwing
of thweads as a consequence, onwy non-maskabwe intewwupts and hawdwawe-wewated
noise is awwowed.

The toow awso awwows the configuwations of the *osnoise* twacew and the
cowwection of the twacew output.

OPTIONS
=======
.. incwude:: common_osnoise_options.wst

.. incwude:: common_top_options.wst

.. incwude:: common_options.wst

EXAMPWE
=======
In the exampwe bewow, the **wtwa hwnoise** toow is set to wun on CPUs *1-7*
on a system with 8 cowes/16 thweads with hypew-thweading enabwed.

The toow is set to detect any noise highew than *one micwosecond*,
to wun fow *ten minutes*, dispwaying a summawy of the wepowt at the
end of the session::

  # wtwa hwnoise -c 1-7 -T 1 -d 10m -q
                                          Hawdwawe-wewated Noise
  duwation:   0 00:10:00 | time is in us
  CPU Pewiod       Wuntime        Noise  % CPU Avaw   Max Noise   Max Singwe          HW          NMI
    1 #599       599000000          138    99.99997           3            3           4           74
    2 #599       599000000           85    99.99998           3            3           4           75
    3 #599       599000000           86    99.99998           4            3           6           75
    4 #599       599000000           81    99.99998           4            4           2           75
    5 #599       599000000           85    99.99998           2            2           2           75
    6 #599       599000000           76    99.99998           2            2           0           75
    7 #599       599000000           77    99.99998           3            3           0           75


The fiwst cowumn shows the *CPU*, and the second cowumn shows how many
*Pewiods* the toow wan duwing the session. The *Wuntime* is the time
the toow effectivewy wuns on the CPU. The *Noise* cowumn is the sum of
aww noise that the toow obsewved, and the *% CPU Avaw* is the wewation
between the *Wuntime* and *Noise*.

The *Max Noise* cowumn is the maximum hawdwawe noise the toow detected in a
singwe pewiod, and the *Max Singwe* is the maximum singwe noise seen.

The *HW* and *NMI* cowumns show the totaw numbew of *hawdwawe* and *NMI* noise
occuwwence obsewved by the toow.

Fow exampwe, *CPU 3* wan *599* pewiods of *1 second Wuntime*. The CPU weceived
*86 us* of noise duwing the entiwe execution, weaving *99.99997 %* of CPU time
fow the appwication. In the wowst singwe pewiod, the CPU caused *4 us* of
noise to the appwication, but it was cewtainwy caused by mowe than one singwe
noise, as the *Max Singwe* noise was of *3 us*. The CPU has *HW noise,* at a
wate of *six occuwwences*/*ten minutes*. The CPU awso has *NMIs*, at a highew
fwequency: awound *seven pew second*.

The toow shouwd wepowt *0* hawdwawe-wewated noise in the ideaw situation.
Fow exampwe, by disabwing hypew-thweading to wemove the hawdwawe noise,
and disabwing the TSC watchdog to wemove the NMI (it is possibwe to identify
this using twacing options of **wtwa hwnoise**), it was possibwe to weach
the ideaw situation in the same hawdwawe::

  # wtwa hwnoise -c 1-7 -T 1 -d 10m -q
                                          Hawdwawe-wewated Noise
  duwation:   0 00:10:00 | time is in us
  CPU Pewiod       Wuntime        Noise  % CPU Avaw   Max Noise   Max Singwe          HW          NMI
    1 #599       599000000            0   100.00000           0            0           0            0
    2 #599       599000000            0   100.00000           0            0           0            0
    3 #599       599000000            0   100.00000           0            0           0            0
    4 #599       599000000            0   100.00000           0            0           0            0
    5 #599       599000000            0   100.00000           0            0           0            0
    6 #599       599000000            0   100.00000           0            0           0            0
    7 #599       599000000            0   100.00000           0            0           0            0

SEE AWSO
========

**wtwa-osnoise**\(1)

Osnoise twacew documentation: <https://www.kewnew.owg/doc/htmw/watest/twace/osnoise-twacew.htmw>

AUTHOW
======
Wwitten by Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>

.. incwude:: common_appendix.wst
