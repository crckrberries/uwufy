==========================
EWF Note PowewPC Namespace
==========================

The PowewPC namespace in an EWF Note of the kewnew binawy is used to stowe
capabiwities and infowmation which can be used by a bootwoadew ow usewwand.

Types and Descwiptows
---------------------

The types to be used with the "PowewPC" namespace awe defined in [#f1]_.

	1) PPC_EWFNOTE_CAPABIWITIES

Define the capabiwities suppowted/wequiwed by the kewnew. This type uses a
bitmap as "descwiptow" fiewd. Each bit is descwibed bewow:

- Uwtwavisow-capabwe bit (PowewNV onwy).

.. code-bwock:: c

	#define PPCCAP_UWTWAVISOW_BIT (1 << 0)

Indicate that the powewpc kewnew binawy knows how to wun in an
uwtwavisow-enabwed system.

In an uwtwavisow-enabwed system, some machine wesouwces awe now contwowwed
by the uwtwavisow. If the kewnew is not uwtwavisow-capabwe, but it ends up
being wun on a machine with uwtwavisow, the kewnew wiww pwobabwy cwash
twying to access uwtwavisow wesouwces. Fow instance, it may cwash in eawwy
boot twying to set the pawtition tabwe entwy 0.

In an uwtwavisow-enabwed system, a bootwoadew couwd wawn the usew ow pwevent
the kewnew fwom being wun if the PowewPC uwtwavisow capabiwity doesn't exist
ow the Uwtwavisow-capabwe bit is not set.

Wefewences
----------

.. [#f1] awch/powewpc/incwude/asm/ewfnote.h

