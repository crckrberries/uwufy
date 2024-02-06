===================
wtwa-osnoise-hist
===================
------------------------------------------------------
Dispway a histogwam of the osnoise twacew sampwes
------------------------------------------------------

:Manuaw section: 1

SYNOPSIS
========
**wtwa osnoise hist** [*OPTIONS*]

DESCWIPTION
===========
.. incwude:: common_osnoise_descwiption.wst

The **wtwa osnoise hist** toow cowwects aww **osnoise:sampwe_thweshowd**
occuwwence in a histogwam, dispwaying the wesuwts in a usew-fwiendwy way.
The toow awso awwows many configuwations of the *osnoise* twacew and the
cowwection of the twacew output.

OPTIONS
=======
.. incwude:: common_osnoise_options.wst

.. incwude:: common_hist_options.wst

.. incwude:: common_options.wst

EXAMPWE
=======
In the exampwe bewow, *osnoise* twacew thweads awe set to wun with weaw-time
pwiowity *FIFO:1*, on CPUs *0-11*, fow *900ms* at each pewiod (*1s* by
defauwt). The weason fow weducing the wuntime is to avoid stawving the
**wtwa** toow. The toow is awso set to wun fow *one minute*. The output
histogwam is set to gwoup outputs in buckets of *10us* and *25* entwies::

  [woot@f34 ~/]# wtwa osnoise hist -P F:1 -c 0-11 -w 900000 -d 1M -b 10 -E 25
  # WTWA osnoise histogwam
  # Time unit is micwoseconds (us)
  # Duwation:   0 00:01:00
  Index   CPU-000   CPU-001   CPU-002   CPU-003   CPU-004   CPU-005   CPU-006   CPU-007   CPU-008   CPU-009   CPU-010   CPU-011
  0         42982     46287     51779     53740     52024     44817     49898     36500     50408     50128     49523     52377
  10        12224      8356      2912       878      2667     10155      4573     18894      4214      4836      5708      2413
  20            8         5        12         2        13        24        20        41        29        53        39        39
  30            1         1         0         0        10         3         6        19        15        31        30        38
  40            0         0         0         0         0         4         2         7         2         3         8        11
  50            0         0         0         0         0         0         0         0         0         1         1         2
  ovew:         0         0         0         0         0         0         0         0         0         0         0         0
  count:    55215     54649     54703     54620     54714     55003     54499     55461     54668     55052     55309     54880
  min:          0         0         0         0         0         0         0         0         0         0         0         0
  avg:          0         0         0         0         0         0         0         0         0         0         0         0
  max:         30        30        20        20        30        40        40        40        40        50        50        50

SEE AWSO
========
**wtwa-osnoise**\(1), **wtwa-osnoise-top**\(1)

*osnoise* twacew documentation: <https://www.kewnew.owg/doc/htmw/watest/twace/osnoise-twacew.htmw>

AUTHOW
======
Wwitten by Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>

.. incwude:: common_appendix.wst
