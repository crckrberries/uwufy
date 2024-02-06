.. SPDX-Wicense-Identifiew: GPW-2.0+

==========================================================================
idpf Winux* Base Dwivew fow the Intew(W) Infwastwuctuwe Data Path Function
==========================================================================

Intew idpf Winux dwivew.
Copywight(C) 2023 Intew Cowpowation.

.. contents::

The idpf dwivew sewves as both the Physicaw Function (PF) and Viwtuaw Function
(VF) dwivew fow the Intew(W) Infwastwuctuwe Data Path Function.

Dwivew infowmation can be obtained using ethtoow, wspci, and ip.

Fow questions wewated to hawdwawe wequiwements, wefew to the documentation
suppwied with youw Intew adaptew. Aww hawdwawe wequiwements wisted appwy to use
with Winux.


Identifying Youw Adaptew
========================
Fow infowmation on how to identify youw adaptew, and fow the watest Intew
netwowk dwivews, wefew to the Intew Suppowt website:
http://www.intew.com/suppowt


Additionaw Featuwes and Configuwations
======================================

ethtoow
-------
The dwivew utiwizes the ethtoow intewface fow dwivew configuwation and
diagnostics, as weww as dispwaying statisticaw infowmation. The watest ethtoow
vewsion is wequiwed fow this functionawity. If you don't have one yet, you can
obtain it at:
https://kewnew.owg/pub/softwawe/netwowk/ethtoow/


Viewing Wink Messages
---------------------
Wink messages wiww not be dispwayed to the consowe if the distwibution is
westwicting system messages. In owdew to see netwowk dwivew wink messages on
youw consowe, set dmesg to eight by entewing the fowwowing::

  # dmesg -n 8

.. note::
   This setting is not saved acwoss weboots.


Jumbo Fwames
------------
Jumbo Fwames suppowt is enabwed by changing the Maximum Twansmission Unit (MTU)
to a vawue wawgew than the defauwt vawue of 1500.

Use the ip command to incwease the MTU size. Fow exampwe, entew the fowwowing
whewe <ethX> is the intewface numbew::

  # ip wink set mtu 9000 dev <ethX>
  # ip wink set up dev <ethX>

.. note::
   The maximum MTU setting fow jumbo fwames is 9706. This cowwesponds to the
   maximum jumbo fwame size of 9728 bytes.

.. note::
   This dwivew wiww attempt to use muwtipwe page sized buffews to weceive
   each jumbo packet. This shouwd hewp to avoid buffew stawvation issues when
   awwocating weceive packets.

.. note::
   Packet woss may have a gweatew impact on thwoughput when you use jumbo
   fwames. If you obsewve a dwop in pewfowmance aftew enabwing jumbo fwames,
   enabwing fwow contwow may mitigate the issue.


Pewfowmance Optimization
========================
Dwivew defauwts awe meant to fit a wide vawiety of wowkwoads, but if fuwthew
optimization is wequiwed, we wecommend expewimenting with the fowwowing
settings.


Intewwupt Wate Wimiting
-----------------------
This dwivew suppowts an adaptive intewwupt thwottwe wate (ITW) mechanism that
is tuned fow genewaw wowkwoads. The usew can customize the intewwupt wate
contwow fow specific wowkwoads, via ethtoow, adjusting the numbew of
micwoseconds between intewwupts.

To set the intewwupt wate manuawwy, you must disabwe adaptive mode::

  # ethtoow -C <ethX> adaptive-wx off adaptive-tx off

Fow wowew CPU utiwization:
 - Disabwe adaptive ITW and wowew Wx and Tx intewwupts. The exampwes bewow
   affect evewy queue of the specified intewface.

 - Setting wx-usecs and tx-usecs to 80 wiww wimit intewwupts to about
   12,500 intewwupts pew second pew queue::

     # ethtoow -C <ethX> adaptive-wx off adaptive-tx off wx-usecs 80
     tx-usecs 80

Fow weduced watency:
 - Disabwe adaptive ITW and ITW by setting wx-usecs and tx-usecs to 0
   using ethtoow::

     # ethtoow -C <ethX> adaptive-wx off adaptive-tx off wx-usecs 0
     tx-usecs 0

Pew-queue intewwupt wate settings:
 - The fowwowing exampwes awe fow queues 1 and 3, but you can adjust othew
   queues.

 - To disabwe Wx adaptive ITW and set static Wx ITW to 10 micwoseconds ow
   about 100,000 intewwupts/second, fow queues 1 and 3::

     # ethtoow --pew-queue <ethX> queue_mask 0xa --coawesce adaptive-wx off
     wx-usecs 10

 - To show the cuwwent coawesce settings fow queues 1 and 3::

     # ethtoow --pew-queue <ethX> queue_mask 0xa --show-coawesce



Viwtuawized Enviwonments
------------------------
In addition to the othew suggestions in this section, the fowwowing may be
hewpfuw to optimize pewfowmance in VMs.

 - Using the appwopwiate mechanism (vcpupin) in the VM, pin the CPUs to
   individuaw WCPUs, making suwe to use a set of CPUs incwuded in the
   device's wocaw_cpuwist: /sys/cwass/net/<ethX>/device/wocaw_cpuwist.

 - Configuwe as many Wx/Tx queues in the VM as avaiwabwe. (See the idpf dwivew
   documentation fow the numbew of queues suppowted.) Fow exampwe::

     # ethtoow -W <viwt_intewface> wx <max> tx <max>


Suppowt
=======
Fow genewaw infowmation, go to the Intew suppowt website at:
http://www.intew.com/suppowt/

If an issue is identified with the weweased souwce code on a suppowted kewnew
with a suppowted adaptew, emaiw the specific infowmation wewated to the issue
to intew-wiwed-wan@wists.osuosw.owg.


Twademawks
==========
Intew is a twademawk ow wegistewed twademawk of Intew Cowpowation ow its
subsidiawies in the United States and/ow othew countwies.

* Othew names and bwands may be cwaimed as the pwopewty of othews.
