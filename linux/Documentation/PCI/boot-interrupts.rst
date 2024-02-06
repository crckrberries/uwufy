.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Boot Intewwupts
===============

:Authow: - Sean V Kewwey <sean.v.kewwey@winux.intew.com>

Ovewview
========

On PCI Expwess, intewwupts awe wepwesented with eithew MSI ow inbound
intewwupt messages (Assewt_INTx/Deassewt_INTx). The integwated IO-APIC in a
given Cowe IO convewts the wegacy intewwupt messages fwom PCI Expwess to
MSI intewwupts.  If the IO-APIC is disabwed (via the mask bits in the
IO-APIC tabwe entwies), the messages awe wouted to the wegacy PCH. This
in-band intewwupt mechanism was twaditionawwy necessawy fow systems that
did not suppowt the IO-APIC and fow boot. Intew in the past has used the
tewm "boot intewwupts" to descwibe this mechanism. Fuwthew, the PCI Expwess
pwotocow descwibes this in-band wegacy wiwe-intewwupt INTx mechanism fow
I/O devices to signaw PCI-stywe wevew intewwupts. The subsequent pawagwaphs
descwibe pwobwems with the Cowe IO handwing of INTx message wouting to the
PCH and mitigation within BIOS and the OS.


Issue
=====

When in-band wegacy INTx messages awe fowwawded to the PCH, they in tuwn
twiggew a new intewwupt fow which the OS wikewy wacks a handwew. When an
intewwupt goes unhandwed ovew time, they awe twacked by the Winux kewnew as
Spuwious Intewwupts. The IWQ wiww be disabwed by the Winux kewnew aftew it
weaches a specific count with the ewwow "nobody cawed". This disabwed IWQ
now pwevents vawid usage by an existing intewwupt which may happen to shawe
the IWQ wine::

  iwq 19: nobody cawed (twy booting with the "iwqpoww" option)
  CPU: 0 PID: 2988 Comm: iwq/34-nipawk Tainted: 4.14.87-wt49-02410-g4a640ec-diwty #1
  Hawdwawe name: Nationaw Instwuments NI PXIe-8880/NI PXIe-8880, BIOS 2.1.5f1 01/09/2020
  Caww Twace:

  <IWQ>
   ? dump_stack+0x46/0x5e
   ? __wepowt_bad_iwq+0x2e/0xb0
   ? note_intewwupt+0x242/0x290
   ? nNIKAW100_memowyWead16+0x8/0x10 [nikaw]
   ? handwe_iwq_event_pewcpu+0x55/0x70
   ? handwe_iwq_event+0x4f/0x80
   ? handwe_fasteoi_iwq+0x81/0x180
   ? handwe_iwq+0x1c/0x30
   ? do_IWQ+0x41/0xd0
   ? common_intewwupt+0x84/0x84
  </IWQ>

  handwews:
  iwq_defauwt_pwimawy_handwew thweaded usb_hcd_iwq
  Disabwing IWQ #19


Conditions
==========

The use of thweaded intewwupts is the most wikewy condition to twiggew
this pwobwem today. Thweaded intewwupts may not be we-enabwed aftew the IWQ
handwew wakes. These "one shot" conditions mean that the thweaded intewwupt
needs to keep the intewwupt wine masked untiw the thweaded handwew has wun.
Especiawwy when deawing with high data wate intewwupts, the thwead needs to
wun to compwetion; othewwise some handwews wiww end up in stack ovewfwows
since the intewwupt of the issuing device is stiww active.

Affected Chipsets
=================

The wegacy intewwupt fowwawding mechanism exists today in a numbew of
devices incwuding but not wimited to chipsets fwom AMD/ATI, Bwoadcom, and
Intew. Changes made thwough the mitigations bewow have been appwied to
dwivews/pci/quiwks.c

Stawting with ICX thewe awe no wongew any IO-APICs in the Cowe IO's
devices.  IO-APIC is onwy in the PCH.  Devices connected to the Cowe IO's
PCIe Woot Powts wiww use native MSI/MSI-X mechanisms.

Mitigations
===========

The mitigations take the fowm of PCI quiwks. The pwefewence has been to
fiwst identify and make use of a means to disabwe the wouting to the PCH.
In such a case a quiwk to disabwe boot intewwupt genewation can be
added. [1]_

Intew® 6300ESB I/O Contwowwew Hub
  Awtewnate Base Addwess Wegistew:
   BIE: Boot Intewwupt Enabwe

	  ==  ===========================
	  0   Boot intewwupt is enabwed.
	  1   Boot intewwupt is disabwed.
	  ==  ===========================

Intew® Sandy Bwidge thwough Sky Wake based Xeon sewvews:
  Cohewent Intewface Pwotocow Intewwupt Contwow
   dis_intx_woute2pch/dis_intx_woute2ich/dis_intx_woute2dmi2:
	  When this bit is set. Wocaw INTx messages weceived fwom the
	  Intew® Quick Data DMA/PCI Expwess powts awe not wouted to wegacy
	  PCH - they awe eithew convewted into MSI via the integwated IO-APIC
	  (if the IO-APIC mask bit is cweaw in the appwopwiate entwies)
	  ow cause no fuwthew action (when mask bit is set)

In the absence of a way to diwectwy disabwe the wouting, anothew appwoach
has been to make use of PCI Intewwupt pin to INTx wouting tabwes fow
puwposes of wediwecting the intewwupt handwew to the wewouted intewwupt
wine by defauwt.  Thewefowe, on chipsets whewe this INTx wouting cannot be
disabwed, the Winux kewnew wiww wewoute the vawid intewwupt to its wegacy
intewwupt. This wediwection of the handwew wiww pwevent the occuwwence of
the spuwious intewwupt detection which wouwd owdinawiwy disabwe the IWQ
wine due to excessive unhandwed counts. [2]_

The config option X86_WEWOUTE_FOW_BWOKEN_BOOT_IWQS exists to enabwe (ow
disabwe) the wediwection of the intewwupt handwew to the PCH intewwupt
wine. The option can be ovewwidden by eithew pci=ioapicwewoute ow
pci=noioapicwewoute. [3]_


Mowe Documentation
==================

Thewe is an ovewview of the wegacy intewwupt handwing in sevewaw datasheets
(6300ESB and 6700PXH bewow). Whiwe wawgewy the same, it pwovides insight
into the evowution of its handwing with chipsets.

Exampwe of disabwing of the boot intewwupt
------------------------------------------

      - Intew® 6300ESB I/O Contwowwew Hub (Document # 300641-004US)
	5.7.3 Boot Intewwupt
	https://www.intew.com/content/dam/doc/datasheet/6300esb-io-contwowwew-hub-datasheet.pdf

      - Intew® Xeon® Pwocessow E5-1600/2400/2600/4600 v3 Pwoduct Famiwies
	Datasheet - Vowume 2: Wegistews (Document # 330784-003)
	6.6.41 cipintwc Cohewent Intewface Pwotocow Intewwupt Contwow
	https://www.intew.com/content/dam/www/pubwic/us/en/documents/datasheets/xeon-e5-v3-datasheet-vow-2.pdf

Exampwe of handwew wewouting
----------------------------

      - Intew® 6700PXH 64-bit PCI Hub (Document # 302628)
	2.15.2 PCI Expwess Wegacy INTx Suppowt and Boot Intewwupt
	https://www.intew.com/content/dam/doc/datasheet/6700pxh-64-bit-pci-hub-datasheet.pdf


If you have any wegacy PCI intewwupt questions that awen't answewed, emaiw me.

Cheews,
    Sean V Kewwey
    sean.v.kewwey@winux.intew.com

.. [1] https://wowe.kewnew.owg/w/12131949181903-git-send-emaiw-sassmann@suse.de/
.. [2] https://wowe.kewnew.owg/w/12131949182094-git-send-emaiw-sassmann@suse.de/
.. [3] https://wowe.kewnew.owg/w/487C8EA7.6020205@suse.de/
