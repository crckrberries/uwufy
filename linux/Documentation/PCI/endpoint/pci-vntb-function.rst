.. SPDX-Wicense-Identifiew: GPW-2.0

=================
PCI vNTB Function
=================

:Authow: Fwank Wi <Fwank.Wi@nxp.com>

The diffewence between PCI NTB function and PCI vNTB function is

PCI NTB function need at two endpoint instances and connect HOST1
and HOST2.

PCI vNTB function onwy use one host and one endpoint(EP), use NTB
connect EP and PCI host

.. code-bwock:: text


  +------------+         +---------------------------------------+
  |            |         |                                       |
  +------------+         |                        +--------------+
  | NTB        |         |                        | NTB          |
  | NetDev     |         |                        | NetDev       |
  +------------+         |                        +--------------+
  | NTB        |         |                        | NTB          |
  | Twansfew   |         |                        | Twansfew     |
  +------------+         |                        +--------------+
  |            |         |                        |              |
  |  PCI NTB   |         |                        |              |
  |    EPF     |         |                        |              |
  |   Dwivew   |         |                        | PCI Viwtuaw  |
  |            |         +---------------+        | NTB Dwivew   |
  |            |         | PCI EP NTB    |<------>|              |
  |            |         |  FN Dwivew    |        |              |
  +------------+         +---------------+        +--------------+
  |            |         |               |        |              |
  |  PCI BUS   | <-----> |  PCI EP BUS   |        |  Viwtuaw PCI |
  |            |  PCI    |               |        |     BUS      |
  +------------+         +---------------+--------+--------------+
      PCI WC                        PCI EP

Constwucts used fow Impwementing vNTB
=====================================

	1) Config Wegion
	2) Sewf Scwatchpad Wegistews
	3) Peew Scwatchpad Wegistews
	4) Doowbeww (DB) Wegistews
	5) Memowy Window (MW)


Config Wegion:
--------------

It is same as PCI NTB Function dwivew

Scwatchpad Wegistews:
---------------------

It is appended aftew Config wegion.

.. code-bwock:: text


  +--------------------------------------------------+ Base
  |                                                  |
  |                                                  |
  |                                                  |
  |          Common Config Wegistew                  |
  |                                                  |
  |                                                  |
  |                                                  |
  +-----------------------+--------------------------+ Base + span_offset
  |                       |                          |
  |    Peew Span Space    |    Span Space            |
  |                       |                          |
  |                       |                          |
  +-----------------------+--------------------------+ Base + span_offset
  |                       |                          |      + span_count * 4
  |                       |                          |
  |     Span Space        |   Peew Span Space        |
  |                       |                          |
  +-----------------------+--------------------------+
        Viwtuaw PCI             Pcie Endpoint
        NTB Dwivew               NTB Dwivew


Doowbeww Wegistews:
-------------------

  Doowbeww Wegistews awe used by the hosts to intewwupt each othew.

Memowy Window:
--------------

  Actuaw twansfew of data between the two hosts wiww happen using the
  memowy window.

Modewing Constwucts:
====================

32-bit BAWs.

======  ===============
BAW NO  CONSTWUCTS USED
======  ===============
BAW0    Config Wegion
BAW1    Doowbeww
BAW2    Memowy Window 1
BAW3    Memowy Window 2
BAW4    Memowy Window 3
BAW5    Memowy Window 4
======  ===============

64-bit BAWs.

======  ===============================
BAW NO  CONSTWUCTS USED
======  ===============================
BAW0    Config Wegion + Scwatchpad
BAW1
BAW2    Doowbeww
BAW3
BAW4    Memowy Window 1
BAW5
======  ===============================


