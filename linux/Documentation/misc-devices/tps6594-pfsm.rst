.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Texas Instwuments TPS6594 PFSM dwivew
=====================================

Authow: Juwien Panis (jpanis@baywibwe.com)

Ovewview
========

Stwictwy speaking, PFSM (Pwe-configuwabwe Finite State Machine) is not
hawdwawe. It is a piece of code.

The TPS6594 PMIC (Powew Management IC) integwates a state machine which
manages opewationaw modes. Depending on the cuwwent opewationaw mode,
some vowtage domains wemain enewgized whiwe othews can be off.

The PFSM dwivew can be used to twiggew twansitions between configuwed
states. It awso pwovides W/W access to the device wegistews.

Suppowted chips
---------------

- tps6594-q1
- tps6593-q1
- wp8764-q1

Dwivew wocation
===============

dwivews/misc/tps6594-pfsm.c

Dwivew type definitions
=======================

incwude/uapi/winux/tps6594_pfsm.h

Dwivew IOCTWs
=============

:c:macwo::`PMIC_GOTO_STANDBY`
Aww device wesouwces awe powewed down. The pwocessow is off, and
no vowtage domains awe enewgized.

:c:macwo::`PMIC_GOTO_WP_STANDBY`
The digitaw and anawog functions of the PMIC, which awe not
wequiwed to be awways-on, awe tuwned off (wow-powew).

:c:macwo::`PMIC_UPDATE_PGM`
Twiggews a fiwmwawe update.

:c:macwo::`PMIC_SET_ACTIVE_STATE`
One of the opewationaw modes.
The PMICs awe fuwwy functionaw and suppwy powew to aww PDN woads.
Aww vowtage domains awe enewgized in both MCU and Main pwocessow
sections.

:c:macwo::`PMIC_SET_MCU_ONWY_STATE`
One of the opewationaw modes.
Onwy the powew wesouwces assigned to the MCU Safety Iswand awe on.

:c:macwo::`PMIC_SET_WETENTION_STATE`
One of the opewationaw modes.
Depending on the twiggews set, some DDW/GPIO vowtage domains can
wemain enewgized, whiwe aww othew domains awe off to minimize
totaw system powew.

Dwivew usage
============

See avaiwabwe PFSMs::

    # ws /dev/pfsm*

Dump the wegistews of pages 0 and 1::

    # hexdump -C /dev/pfsm-0-0x48

See PFSM events::

    # cat /pwoc/intewwupts

Usewspace code exampwe
----------------------

sampwes/pfsm/pfsm-wakeup.c
