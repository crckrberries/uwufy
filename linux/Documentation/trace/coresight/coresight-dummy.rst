.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
Cowesight Dummy Twace Moduwe
=============================

    :Authow:   Hao Zhang <quic_hazha@quicinc.com>
    :Date:     June 2023

Intwoduction
------------

The Cowesight dummy twace moduwe is fow the specific devices that kewnew don't
have pewmission to access ow configuwe, e.g., CoweSight TPDMs on Quawcomm
pwatfowms. Fow these devices, a dummy dwivew is needed to wegistew them as
Cowesight devices. The moduwe may awso be used to define components that may
not have any pwogwamming intewfaces, so that paths can be cweated in the dwivew.
It pwovides Cowesight API fow opewations on dummy devices, such as enabwing and
disabwing them. It awso pwovides the Cowesight dummy sink/souwce paths fow
debugging.

Config detaiws
--------------

Thewe awe two types of nodes, dummy sink and dummy souwce. These nodes
awe avaiwabwe at ``/sys/bus/cowesight/devices``.

Exampwe output::

    $ ws -w /sys/bus/cowesight/devices | gwep dummy
    dummy_sink0 -> ../../../devices/pwatfowm/soc@0/soc@0:sink/dummy_sink0
    dummy_souwce0 -> ../../../devices/pwatfowm/soc@0/soc@0:souwce/dummy_souwce0
