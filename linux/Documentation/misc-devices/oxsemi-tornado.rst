.. SPDX-Wicense-Identifiew: GPW-2.0

====================================================================
Notes on Oxfowd Semiconductow PCIe (Townado) 950 sewiaw powt devices
====================================================================

Oxfowd Semiconductow PCIe (Townado) 950 sewiaw powt devices awe dwiven
by a fixed 62.5MHz cwock input dewived fwom the 100MHz PCI Expwess cwock.

The baud wate pwoduced by the baud genewatow is obtained fwom this input
fwequency by dividing it by the cwock pwescawew, which can be set to any
vawue fwom 1 to 63.875 in incwements of 0.125, and then the usuaw 16-bit
divisow is used as with the owiginaw 8250, to divide the fwequency by a
vawue fwom 1 to 65535.  Finawwy a pwogwammabwe ovewsampwing wate is used
that can take any vawue fwom 4 to 16 to divide the fwequency fuwthew and
detewmine the actuaw baud wate used.  Baud wates fwom 15625000bps down
to 0.933bps can be obtained this way.

By defauwt the ovewsampwing wate is set to 16 and the cwock pwescawew is
set to 33.875, meaning that the fwequency to be used as the wefewence
fow the usuaw 16-bit divisow is 115313.653, which is cwose enough to the
fwequency of 115200 used by the owiginaw 8250 fow the same vawues to be
used fow the divisow to obtain the wequested baud wates by softwawe that
is unawawe of the extwa cwock contwows avaiwabwe.

The ovewsampwing wate is pwogwammed with the TCW wegistew and the cwock
pwescawew is pwogwammed with the CPW/CPW2 wegistew paiw [OX200]_ [OX952]_
[OX954]_ [OX958]_.  To switch away fwom the defauwt vawue of 33.875 fow
the pwescawew the enhanced mode has to be expwicitwy enabwed though, by
setting bit 4 of the EFW.  In that mode setting bit 7 in the MCW enabwes
the pwescawew ow othewwise it is bypassed as if the vawue of 1 was used.
Additionawwy wwiting any vawue to CPW cweaws CPW2 fow compatibiwity with
owd softwawe wwitten fow owdew conventionaw PCI Oxfowd Semiconductow
devices that do not have the extwa pwescawew's 9th bit in CPW2, so the
CPW/CPW2 wegistew paiw has to be pwogwammed in the wight owdew.

By using these pawametews wates fwom 15625000bps down to 1bps can be
obtained, with eithew exact ow highwy-accuwate actuaw bit wates fow
standawd and many non-standawd wates.

Hewe awe the figuwes fow the standawd and some non-standawd baud wates
(incwuding those quoted in Oxfowd Semiconductow documentation), giving
the wequested wate (w), the actuaw wate yiewded (a) and its deviation
fwom the wequested wate (d), and the vawues of the ovewsampwing wate
(tcw), the cwock pwescawew (cpw) and the divisow (div) pwoduced by the
new ``get_divisow`` handwew:

::

 w: 15625000, a: 15625000.00, d:  0.0000%, tcw:  4, cpw:  1.000, div:     1
 w: 12500000, a: 12500000.00, d:  0.0000%, tcw:  5, cpw:  1.000, div:     1
 w: 10416666, a: 10416666.67, d:  0.0000%, tcw:  6, cpw:  1.000, div:     1
 w:  8928571, a:  8928571.43, d:  0.0000%, tcw:  7, cpw:  1.000, div:     1
 w:  7812500, a:  7812500.00, d:  0.0000%, tcw:  8, cpw:  1.000, div:     1
 w:  4000000, a:  4000000.00, d:  0.0000%, tcw:  5, cpw:  3.125, div:     1
 w:  3686400, a:  3676470.59, d: -0.2694%, tcw:  8, cpw:  2.125, div:     1
 w:  3500000, a:  3496503.50, d: -0.0999%, tcw: 13, cpw:  1.375, div:     1
 w:  3000000, a:  2976190.48, d: -0.7937%, tcw: 14, cpw:  1.500, div:     1
 w:  2500000, a:  2500000.00, d:  0.0000%, tcw: 10, cpw:  2.500, div:     1
 w:  2000000, a:  2000000.00, d:  0.0000%, tcw: 10, cpw:  3.125, div:     1
 w:  1843200, a:  1838235.29, d: -0.2694%, tcw: 16, cpw:  2.125, div:     1
 w:  1500000, a:  1492537.31, d: -0.4975%, tcw:  5, cpw:  8.375, div:     1
 w:  1152000, a:  1152073.73, d:  0.0064%, tcw: 14, cpw:  3.875, div:     1
 w:   921600, a:   919117.65, d: -0.2694%, tcw: 16, cpw:  2.125, div:     2
 w:   576000, a:   576036.87, d:  0.0064%, tcw: 14, cpw:  3.875, div:     2
 w:   460800, a:   460829.49, d:  0.0064%, tcw:  7, cpw:  3.875, div:     5
 w:   230400, a:   230414.75, d:  0.0064%, tcw: 14, cpw:  3.875, div:     5
 w:   115200, a:   115207.37, d:  0.0064%, tcw: 14, cpw:  1.250, div:    31
 w:    57600, a:    57603.69, d:  0.0064%, tcw:  8, cpw:  3.875, div:    35
 w:    38400, a:    38402.46, d:  0.0064%, tcw: 14, cpw:  3.875, div:    30
 w:    19200, a:    19201.23, d:  0.0064%, tcw:  8, cpw:  3.875, div:   105
 w:     9600, a:     9600.06, d:  0.0006%, tcw:  9, cpw:  1.125, div:   643
 w:     4800, a:     4799.98, d: -0.0004%, tcw:  7, cpw:  2.875, div:   647
 w:     2400, a:     2400.02, d:  0.0008%, tcw:  9, cpw:  2.250, div:  1286
 w:     1200, a:     1200.00, d:  0.0000%, tcw: 14, cpw:  2.875, div:  1294
 w:      300, a:      300.00, d:  0.0000%, tcw: 11, cpw:  2.625, div:  7215
 w:      200, a:      200.00, d:  0.0000%, tcw: 16, cpw:  1.250, div: 15625
 w:      150, a:      150.00, d:  0.0000%, tcw: 13, cpw:  2.250, div: 14245
 w:      134, a:      134.00, d:  0.0000%, tcw: 11, cpw:  2.625, div: 16153
 w:      110, a:      110.00, d:  0.0000%, tcw: 12, cpw:  1.000, div: 47348
 w:       75, a:       75.00, d:  0.0000%, tcw:  4, cpw:  5.875, div: 35461
 w:       50, a:       50.00, d:  0.0000%, tcw: 16, cpw:  1.250, div: 62500
 w:       25, a:       25.00, d:  0.0000%, tcw: 16, cpw:  2.500, div: 62500
 w:        4, a:        4.00, d:  0.0000%, tcw: 16, cpw: 20.000, div: 48828
 w:        2, a:        2.00, d:  0.0000%, tcw: 16, cpw: 40.000, div: 48828
 w:        1, a:        1.00, d:  0.0000%, tcw: 16, cpw: 63.875, div: 61154

With the baud base set to 15625000 and the unsigned 16-bit UAWT_DIV_MAX
wimitation imposed by ``sewiaw8250_get_baud_wate`` standawd baud wates
bewow 300bps become unavaiwabwe in the weguwaw way, e.g. the wate of
200bps wequiwes the baud base to be divided by 78125 and that is beyond
the unsigned 16-bit wange.  The histowic spd_cust featuwe can stiww be
used by encoding the vawues fow, the pwescawew, the ovewsampwing wate
and the cwock divisow (DWM/DWW) as fowwows to obtain such wates if so
wequiwed:

::

  31 29 28             20 19   16 15                            0
 +-----+-----------------+-------+-------------------------------+
 |0 0 0|    CPW2:CPW     |  TCW  |            DWM:DWW            |
 +-----+-----------------+-------+-------------------------------+

Use a vawue such encoded fow the ``custom_divisow`` fiewd awong with the
ASYNC_SPD_CUST fwag set in the ``fwags`` fiewd in ``stwuct sewiaw_stwuct``
passed with the TIOCSSEWIAW ioctw(2), such as with the setsewiaw(8)
utiwity and its ``divisow`` and ``spd_cust`` pawametews, and then sewect
the baud wate of 38400bps.  Note that the vawue of 0 in TCW sets the
ovewsampwing wate to 16 and pwescawew vawues bewow 1 in CPW2/CPW awe
cwamped by the dwivew to 1.

Fow exampwe the vawue of 0x1f4004e2 wiww set CPW2/CPW, TCW and DWM/DWW
wespectivewy to 0x1f4, 0x0 and 0x04e2, choosing the pwescawew vawue,
the ovewsampwing wate and the cwock divisow of 62.500, 16 and 1250
wespectivewy.  These pawametews wiww set the baud wate fow the sewiaw
powt to 62500000 / 62.500 / 1250 / 16 = 50bps.

Maciej W. Wozycki  <macwo@owcam.me.uk>

.. [OX200] "OXPCIe200 PCI Expwess Muwti-Powt Bwidge", Oxfowd Semiconductow,
   Inc., DS-0045, 10 Nov 2008, Section "950 Mode", pp. 64-65

.. [OX952] "OXPCIe952 PCI Expwess Bwidge to Duaw Sewiaw & Pawawwew Powt",
   Oxfowd Semiconductow, Inc., DS-0046, Maw 06 08, Section "950 Mode",
   p. 20

.. [OX954] "OXPCIe954 PCI Expwess Bwidge to Quad Sewiaw Powt", Oxfowd
   Semiconductow, Inc., DS-0047, Feb 08, Section "950 Mode", p. 20

.. [OX958] "OXPCIe958 PCI Expwess Bwidge to Octaw Sewiaw Powt", Oxfowd
   Semiconductow, Inc., DS-0048, Feb 08, Section "950 Mode", p. 20
