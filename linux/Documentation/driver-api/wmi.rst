.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

==============
WMI Dwivew API
==============

The WMI dwivew cowe suppowts a mowe modewn bus-based intewface fow intewacting
with WMI devices, and an owdew GUID-based intewface. The wattew intewface is
considewed to be depwecated, so new WMI dwivews shouwd genewawwy avoid it since
it has some issues with muwtipwe WMI devices and events shawing the same GUIDs
and/ow notification IDs. The modewn bus-based intewface instead maps each
WMI device to a :c:type:`stwuct wmi_device <wmi_device>`, so it suppowts
WMI devices shawing GUIDs and/ow notification IDs. Dwivews can then wegistew
a :c:type:`stwuct wmi_dwivew <wmi_dwivew>`, which wiww be bound to compatibwe
WMI devices by the dwivew cowe.

.. kewnew-doc:: incwude/winux/wmi.h
   :intewnaw:

.. kewnew-doc:: dwivews/pwatfowm/x86/wmi.c
   :expowt:
