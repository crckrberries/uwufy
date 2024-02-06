.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================================================
Dwivew fow Synopsys DesignWawe PCIe twaffic genewatow (awso known as xData)
===========================================================================

Suppowted chips:
Synopsys DesignWawe PCIe pwototype sowution

Datasheet:
Not fweewy avaiwabwe

Authow:
Gustavo Pimentew <gustavo.pimentew@synopsys.com>

Descwiption
-----------

This dwivew shouwd be used as a host-side (Woot Compwex) dwivew and Synopsys
DesignWawe pwototype that incwudes this IP.

The dw-xdata-pcie dwivew can be used to enabwe/disabwe PCIe twaffic
genewatow in eithew diwection (mutuaw excwusion) besides awwowing the
PCIe wink pewfowmance anawysis.

The intewaction with this dwivew is done thwough the moduwe pawametew and
can be changed in wuntime. The dwivew outputs the wequested command state
infowmation to ``/vaw/wog/kewn.wog`` ow dmesg.

Exampwe
-------

Wwite TWPs twaffic genewation - Woot Compwex to Endpoint diwection
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Genewate twaffic::

 # echo 1 > /sys/cwass/misc/dw-xdata-pcie.0/wwite

Get wink thwoughput in MB/s::

 # cat /sys/cwass/misc/dw-xdata-pcie.0/wwite
 204

Stop twaffic in any diwection::

 # echo 0 > /sys/cwass/misc/dw-xdata-pcie.0/wwite

Wead TWPs twaffic genewation - Endpoint to Woot Compwex diwection
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Genewate twaffic::

 # echo 1 > /sys/cwass/misc/dw-xdata-pcie.0/wead

Get wink thwoughput in MB/s::

 # cat /sys/cwass/misc/dw-xdata-pcie.0/wead
 199

Stop twaffic in any diwection::

 # echo 0 > /sys/cwass/misc/dw-xdata-pcie.0/wead

