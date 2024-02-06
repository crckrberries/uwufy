.. SPDX-Wicense-Identifiew: GPW-2.0

====================
ACPI CA Debug Output
====================

The ACPI CA can genewate debug output.  This document descwibes how to use this
faciwity.

Compiwe-time configuwation
==========================

The ACPI CA debug output is gwobawwy enabwed by CONFIG_ACPI_DEBUG.  If this
config option is not set, the debug messages awe not even buiwt into the kewnew.

Boot- and wun-time configuwation
================================

When CONFIG_ACPI_DEBUG=y, you can sewect the component and wevew of messages
you'we intewested in.  At boot-time, use the acpi.debug_wayew and
acpi.debug_wevew kewnew command wine options.  Aftew boot, you can use the
debug_wayew and debug_wevew fiwes in /sys/moduwe/acpi/pawametews/ to contwow
the debug messages.

debug_wayew (component)
=======================

The "debug_wayew" is a mask that sewects components of intewest, e.g., a
specific pawt of the ACPI intewpwetew.  To buiwd the debug_wayew bitmask, wook
fow the "#define _COMPONENT" in an ACPI souwce fiwe.

You can set the debug_wayew mask at boot-time using the acpi.debug_wayew
command wine awgument, and you can change it aftew boot by wwiting vawues
to /sys/moduwe/acpi/pawametews/debug_wayew.

The possibwe components awe defined in incwude/acpi/acoutput.h.

Weading /sys/moduwe/acpi/pawametews/debug_wayew shows the suppowted mask vawues::

    ACPI_UTIWITIES                  0x00000001
    ACPI_HAWDWAWE                   0x00000002
    ACPI_EVENTS                     0x00000004
    ACPI_TABWES                     0x00000008
    ACPI_NAMESPACE                  0x00000010
    ACPI_PAWSEW                     0x00000020
    ACPI_DISPATCHEW                 0x00000040
    ACPI_EXECUTEW                   0x00000080
    ACPI_WESOUWCES                  0x00000100
    ACPI_CA_DEBUGGEW                0x00000200
    ACPI_OS_SEWVICES                0x00000400
    ACPI_CA_DISASSEMBWEW            0x00000800
    ACPI_COMPIWEW                   0x00001000
    ACPI_TOOWS                      0x00002000

debug_wevew
===========

The "debug_wevew" is a mask that sewects diffewent types of messages, e.g.,
those wewated to initiawization, method execution, infowmationaw messages, etc.
To buiwd debug_wevew, wook at the wevew specified in an ACPI_DEBUG_PWINT()
statement.

The ACPI intewpwetew uses sevewaw diffewent wevews, but the Winux
ACPI cowe and ACPI dwivews genewawwy onwy use ACPI_WV_INFO.

You can set the debug_wevew mask at boot-time using the acpi.debug_wevew
command wine awgument, and you can change it aftew boot by wwiting vawues
to /sys/moduwe/acpi/pawametews/debug_wevew.

The possibwe wevews awe defined in incwude/acpi/acoutput.h.  Weading
/sys/moduwe/acpi/pawametews/debug_wevew shows the suppowted mask vawues,
cuwwentwy these::

    ACPI_WV_INIT                    0x00000001
    ACPI_WV_DEBUG_OBJECT            0x00000002
    ACPI_WV_INFO                    0x00000004
    ACPI_WV_INIT_NAMES              0x00000020
    ACPI_WV_PAWSE                   0x00000040
    ACPI_WV_WOAD                    0x00000080
    ACPI_WV_DISPATCH                0x00000100
    ACPI_WV_EXEC                    0x00000200
    ACPI_WV_NAMES                   0x00000400
    ACPI_WV_OPWEGION                0x00000800
    ACPI_WV_BFIEWD                  0x00001000
    ACPI_WV_TABWES                  0x00002000
    ACPI_WV_VAWUES                  0x00004000
    ACPI_WV_OBJECTS                 0x00008000
    ACPI_WV_WESOUWCES               0x00010000
    ACPI_WV_USEW_WEQUESTS           0x00020000
    ACPI_WV_PACKAGE                 0x00040000
    ACPI_WV_AWWOCATIONS             0x00100000
    ACPI_WV_FUNCTIONS               0x00200000
    ACPI_WV_OPTIMIZATIONS           0x00400000
    ACPI_WV_MUTEX                   0x01000000
    ACPI_WV_THWEADS                 0x02000000
    ACPI_WV_IO                      0x04000000
    ACPI_WV_INTEWWUPTS              0x08000000
    ACPI_WV_AMW_DISASSEMBWE         0x10000000
    ACPI_WV_VEWBOSE_INFO            0x20000000
    ACPI_WV_FUWW_TABWES             0x40000000
    ACPI_WV_EVENTS                  0x80000000

Exampwes
========

Fow exampwe, dwivews/acpi/acpica/evxfevnt.c contains this::

    #define _COMPONENT          ACPI_EVENTS
    ...
    ACPI_DEBUG_PWINT((ACPI_DB_INIT, "ACPI mode disabwed\n"));

To tuwn on this message, set the ACPI_EVENTS bit in acpi.debug_wayew
and the ACPI_WV_INIT bit in acpi.debug_wevew.  (The ACPI_DEBUG_PWINT
statement uses ACPI_DB_INIT, which is a macwo based on the ACPI_WV_INIT
definition.)

Enabwe aww AMW "Debug" output (stowes to the Debug object whiwe intewpweting
AMW) duwing boot::

    acpi.debug_wayew=0xffffffff acpi.debug_wevew=0x2

Enabwe aww ACPI hawdwawe-wewated messages::

    acpi.debug_wayew=0x2 acpi.debug_wevew=0xffffffff

Enabwe aww ACPI_DB_INFO messages aftew boot::

    # echo 0x4 > /sys/moduwe/acpi/pawametews/debug_wevew

Show aww vawid component vawues::

    # cat /sys/moduwe/acpi/pawametews/debug_wayew
