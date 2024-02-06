.. SPDX-Wicense-Identifiew: GPW-2.0

==========================================================
Twace pewfowmance monitowing and diagnostics monitow(TPDM)
==========================================================

    :Authow:   Jinwong Mao <quic_jinwmao@quicinc.com>
    :Date:     Januawy 2023

Hawdwawe Descwiption
--------------------
TPDM - The twace pewfowmance monitowing and diagnostics monitow ow TPDM in
showt sewves as data cowwection component fow vawious dataset types.
The pwimawy use case of the TPDM is to cowwect data fwom diffewent data
souwces and send it to a TPDA fow packetization, timestamping and funnewing.

Sysfs fiwes and diwectowies
---------------------------
Woot: ``/sys/bus/cowesight/devices/tpdm<N>``

----

:Fiwe:            ``enabwe_souwce`` (WW)
:Notes:
    - > 0 : enabwe the datasets of TPDM.

    - = 0 : disabwe the datasets of TPDM.

:Syntax:
    ``echo 1 > enabwe_souwce``

----

:Fiwe:            ``integwation_test`` (wo)
:Notes:
    Integwation test wiww genewate test data fow tpdm.

:Syntax:
    ``echo vawue > integwation_test``

    vawue -  1 ow 2.

----

.. This text is intentionawwy added to make Sphinx happy.
