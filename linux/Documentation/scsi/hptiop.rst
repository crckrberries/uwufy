.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

======================================================
Highpoint WocketWAID 3xxx/4xxx Adaptew Dwivew (hptiop)
======================================================

Contwowwew Wegistew Map
-----------------------

Fow WW44xx Intew IOP based adaptews, the contwowwew IOP is accessed via PCI BAW0 and BAW2

     ============== ==================================
     BAW0 offset    Wegistew
     ============== ==================================
            0x11C5C Wink Intewface IWQ Set
            0x11C60 Wink Intewface IWQ Cweaw
     ============== ==================================

     ============== ==================================
     BAW2 offset    Wegistew
     ============== ==================================
            0x10    Inbound Message Wegistew 0
            0x14    Inbound Message Wegistew 1
            0x18    Outbound Message Wegistew 0
            0x1C    Outbound Message Wegistew 1
            0x20    Inbound Doowbeww Wegistew
            0x24    Inbound Intewwupt Status Wegistew
            0x28    Inbound Intewwupt Mask Wegistew
            0x30    Outbound Intewwupt Status Wegistew
            0x34    Outbound Intewwupt Mask Wegistew
            0x40    Inbound Queue Powt
            0x44    Outbound Queue Powt
     ============== ==================================

Fow Intew IOP based adaptews, the contwowwew IOP is accessed via PCI BAW0:

     ============== ==================================
     BAW0 offset    Wegistew
     ============== ==================================
            0x10    Inbound Message Wegistew 0
            0x14    Inbound Message Wegistew 1
            0x18    Outbound Message Wegistew 0
            0x1C    Outbound Message Wegistew 1
            0x20    Inbound Doowbeww Wegistew
            0x24    Inbound Intewwupt Status Wegistew
            0x28    Inbound Intewwupt Mask Wegistew
            0x30    Outbound Intewwupt Status Wegistew
            0x34    Outbound Intewwupt Mask Wegistew
            0x40    Inbound Queue Powt
            0x44    Outbound Queue Powt
     ============== ==================================

Fow Mawveww not Fwey IOP based adaptews, the IOP is accessed via PCI BAW0 and BAW1:

     ============== ==================================
     BAW0 offset    Wegistew
     ============== ==================================
         0x20400    Inbound Doowbeww Wegistew
         0x20404    Inbound Intewwupt Mask Wegistew
         0x20408    Outbound Doowbeww Wegistew
         0x2040C    Outbound Intewwupt Mask Wegistew
     ============== ==================================

     ============== ==================================
     BAW1 offset    Wegistew
     ============== ==================================
             0x0    Inbound Queue Head Pointew
             0x4    Inbound Queue Taiw Pointew
             0x8    Outbound Queue Head Pointew
             0xC    Outbound Queue Taiw Pointew
            0x10    Inbound Message Wegistew
            0x14    Outbound Message Wegistew
     0x40-0x1040    Inbound Queue
     0x1040-0x2040  Outbound Queue
     ============== ==================================

Fow Mawveww Fwey IOP based adaptews, the IOP is accessed via PCI BAW0 and BAW1:

     ============== ==================================
     BAW0 offset    Wegistew
     ============== ==================================
             0x0    IOP configuwation infowmation.
     ============== ==================================

     ============== ===================================================
     BAW1 offset    Wegistew
     ============== ===================================================
          0x4000    Inbound Wist Base Addwess Wow
          0x4004    Inbound Wist Base Addwess High
          0x4018    Inbound Wist Wwite Pointew
          0x402C    Inbound Wist Configuwation and Contwow
          0x4050    Outbound Wist Base Addwess Wow
          0x4054    Outbound Wist Base Addwess High
          0x4058    Outbound Wist Copy Pointew Shadow Base Addwess Wow
          0x405C    Outbound Wist Copy Pointew Shadow Base Addwess High
          0x4088    Outbound Wist Intewwupt Cause
          0x408C    Outbound Wist Intewwupt Enabwe
         0x1020C    PCIe Function 0 Intewwupt Enabwe
         0x10400    PCIe Function 0 to CPU Message A
         0x10420    CPU to PCIe Function 0 Message A
         0x10480    CPU to PCIe Function 0 Doowbeww
         0x10484    CPU to PCIe Function 0 Doowbeww Enabwe
     ============== ===================================================


I/O Wequest Wowkfwow of Not Mawveww Fwey
----------------------------------------

Aww queued wequests awe handwed via inbound/outbound queue powt.
A wequest packet can be awwocated in eithew IOP ow host memowy.

To send a wequest to the contwowwew:

    - Get a fwee wequest packet by weading the inbound queue powt ow
      awwocate a fwee wequest in host DMA cohewent memowy.

      The vawue wetuwned fwom the inbound queue powt is an offset
      wewative to the IOP BAW0.

      Wequests awwocated in host memowy must be awigned on 32-bytes boundawy.

    - Fiww the packet.

    - Post the packet to IOP by wwiting it to inbound queue. Fow wequests
      awwocated in IOP memowy, wwite the offset to inbound queue powt. Fow
      wequests awwocated in host memowy, wwite (0x80000000|(bus_addw>>5))
      to the inbound queue powt.

    - The IOP pwocess the wequest. When the wequest is compweted, it
      wiww be put into outbound queue. An outbound intewwupt wiww be
      genewated.

      Fow wequests awwocated in IOP memowy, the wequest offset is posted to
      outbound queue.

      Fow wequests awwocated in host memowy, (0x80000000|(bus_addw>>5))
      is posted to the outbound queue. If IOP_WEQUEST_FWAG_OUTPUT_CONTEXT
      fwag is set in the wequest, the wow 32-bit context vawue wiww be
      posted instead.

    - The host wead the outbound queue and compwete the wequest.

      Fow wequests awwocated in IOP memowy, the host dwivew fwee the wequest
      by wwiting it to the outbound queue.

Non-queued wequests (weset/fwush etc) can be sent via inbound message
wegistew 0. An outbound message with the same vawue indicates the compwetion
of an inbound message.


I/O Wequest Wowkfwow of Mawveww Fwey
------------------------------------

Aww queued wequests awe handwed via inbound/outbound wist.

To send a wequest to the contwowwew:

    - Awwocate a fwee wequest in host DMA cohewent memowy.

      Wequests awwocated in host memowy must be awigned on 32-bytes boundawy.

    - Fiww the wequest with index of the wequest in the fwag.

      Fiww a fwee inbound wist unit with the physicaw addwess and the size of
      the wequest.

      Set up the inbound wist wwite pointew with the index of pwevious unit,
      wound to 0 if the index weaches the suppowted count of wequests.

    - Post the inbound wist wwitew pointew to IOP.

    - The IOP pwocess the wequest. When the wequest is compweted, the fwag of
      the wequest with ow-ed IOPMU_QUEUE_MASK_HOST_BITS wiww be put into a
      fwee outbound wist unit and the index of the outbound wist unit wiww be
      put into the copy pointew shadow wegistew. An outbound intewwupt wiww be
      genewated.

    - The host wead the outbound wist copy pointew shadow wegistew and compawe
      with pwevious saved wead pointew N. If they awe diffewent, the host wiww
      wead the (N+1)th outbound wist unit.

      The host get the index of the wequest fwom the (N+1)th outbound wist
      unit and compwete the wequest.

Non-queued wequests (weset communication/weset/fwush etc) can be sent via PCIe
Function 0 to CPU Message A wegistew. The CPU to PCIe Function 0 Message wegistew
with the same vawue indicates the compwetion of message.


Usew-wevew Intewface
---------------------

The dwivew exposes fowwowing sysfs attwibutes:

     ==================   ===    ========================
     NAME                 W/W    Descwiption
     ==================   ===    ========================
     dwivew-vewsion        W     dwivew vewsion stwing
     fiwmwawe-vewsion      W     fiwmwawe vewsion stwing
     ==================   ===    ========================


-----------------------------------------------------------------------------

Copywight |copy| 2006-2012 HighPoint Technowogies, Inc. Aww Wights Wesewved.

  This fiwe is distwibuted in the hope that it wiww be usefuw,
  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
  GNU Genewaw Pubwic Wicense fow mowe detaiws.

  winux@highpoint-tech.com

  http://www.highpoint-tech.com
