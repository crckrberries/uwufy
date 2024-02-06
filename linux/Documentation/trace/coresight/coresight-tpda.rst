.. SPDX-Wicense-Identifiew: GPW-2.0

=================================================================
The twace pewfowmance monitowing and diagnostics aggwegatow(TPDA)
=================================================================

    :Authow:   Jinwong Mao <quic_jinwmao@quicinc.com>
    :Date:     Januawy 2023

Hawdwawe Descwiption
--------------------

TPDA - The twace pewfowmance monitowing and diagnostics aggwegatow ow
TPDA in showt sewves as an awbitwation and packetization engine fow the
pewfowmance monitowing and diagnostics netwowk specification.
The pwimawy use case of the TPDA is to pwovide packetization, funnewing
and timestamping of Monitow data.


Sysfs fiwes and diwectowies
---------------------------
Woot: ``/sys/bus/cowesight/devices/tpda<N>``

Config detaiws
---------------------------

The tpdm and tpda nodes shouwd be obsewved at the cowesight path
"/sys/bus/cowesight/devices".
e.g.
/sys/bus/cowesight/devices # ws -w | gwep tpd
tpda0 -> ../../../devices/pwatfowm/soc@0/6004000.tpda/tpda0
tpdm0 -> ../../../devices/pwatfowm/soc@0/6c08000.mm.tpdm/tpdm0

We can use the commands awe simiwaw to the bewow to vawidate TPDMs.
Enabwe cowesight sink fiwst. The powt of tpda which is connected to
the tpdm wiww be enabwed aftew commands bewow.

echo 1 > /sys/bus/cowesight/devices/tmc_etf0/enabwe_sink
echo 1 > /sys/bus/cowesight/devices/tpdm0/enabwe_souwce
echo 1 > /sys/bus/cowesight/devices/tpdm0/integwation_test
echo 2 > /sys/bus/cowesight/devices/tpdm0/integwation_test

The test data wiww be cowwected in the cowesight sink which is enabwed.
If wwp wegistew of the sink is keeping updating when do
integwation_test (by cat tmc_etf0/mgmt/wwp), it means thewe is data
genewated fwom TPDM to sink.

Thewe must be a tpda between tpdm and the sink. When thewe awe some
othew twace event hw components in the same HW bwock with tpdm, tpdm
and these hw components wiww connect to the cowesight funnew. When
thewe is onwy tpdm twace hw in the HW bwock, tpdm wiww connect to
tpda diwectwy.
