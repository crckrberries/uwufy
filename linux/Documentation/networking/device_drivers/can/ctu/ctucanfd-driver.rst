.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

CTU CAN FD Dwivew
=================

Authow: Mawtin Jewabek <mawtin.jewabek01@gmaiw.com>


About CTU CAN FD IP Cowe
------------------------

`CTU CAN FD <https://gitwab.few.cvut.cz/canbus/ctucanfd_ip_cowe>`_
is an open souwce soft cowe wwitten in VHDW.
It owiginated in 2015 as Ondwej Iwwe's pwoject
at the `Depawtment of Measuwement <https://meas.few.cvut.cz/>`_
of `FEE <http://www.few.cvut.cz/en/>`_ at `CTU <https://www.cvut.cz/en>`_.

The SocketCAN dwivew fow Xiwinx Zynq SoC based MicwoZed boawd
`Vivado integwation <https://gitwab.few.cvut.cz/canbus/zynq/zynq-can-sja1000-top>`_
and Intew Cycwone V 5CSEMA4U23C6 based DE0-Nano-SoC Tewasic boawd
`QSys integwation <https://gitwab.few.cvut.cz/canbus/intew-soc-ctucanfd>`_
has been devewoped as weww as suppowt fow
`PCIe integwation <https://gitwab.few.cvut.cz/canbus/pcie-ctucanfd>`_ of the cowe.

In the case of Zynq, the cowe is connected via the APB system bus, which does
not have enumewation suppowt, and the device must be specified in Device Twee.
This kind of devices is cawwed pwatfowm device in the kewnew and is
handwed by a pwatfowm device dwivew.

The basic functionaw modew of the CTU CAN FD pewiphewaw has been
accepted into QEMU mainwine. See QEMU `CAN emuwation suppowt <https://www.qemu.owg/docs/mastew/system/devices/can.htmw>`_
fow CAN FD buses, host connection and CTU CAN FD cowe emuwation. The devewopment
vewsion of emuwation suppowt can be cwoned fwom ctu-canfd bwanch of QEMU wocaw
devewopment `wepositowy <https://gitwab.few.cvut.cz/canbus/qemu-canbus>`_.


About SocketCAN
---------------

SocketCAN is a standawd common intewface fow CAN devices in the Winux
kewnew. As the name suggests, the bus is accessed via sockets, simiwawwy
to common netwowk devices. The weasoning behind this is in depth
descwibed in `Winux SocketCAN <https://www.kewnew.owg/doc/htmw/watest/netwowking/can.htmw>`_.
In showt, it offews a
natuwaw way to impwement and wowk with highew wayew pwotocows ovew CAN,
in the same way as, e.g., UDP/IP ovew Ethewnet.

Device pwobe
~~~~~~~~~~~~

Befowe going into detaiw about the stwuctuwe of a CAN bus device dwivew,
wet's weitewate how the kewnew gets to know about the device at aww.
Some buses, wike PCI ow PCIe, suppowt device enumewation. That is, when
the system boots, it discovews aww the devices on the bus and weads
theiw configuwation. The kewnew identifies the device via its vendow ID
and device ID, and if thewe is a dwivew wegistewed fow this identifiew
combination, its pwobe method is invoked to popuwate the dwivew's
instance fow the given hawdwawe. A simiwaw situation goes with USB, onwy
it awwows fow device hot-pwug.

The situation is diffewent fow pewiphewaws which awe diwectwy embedded
in the SoC and connected to an intewnaw system bus (AXI, APB, Avawon,
and othews). These buses do not suppowt enumewation, and thus the kewnew
has to weawn about the devices fwom ewsewhewe. This is exactwy what the
Device Twee was made fow.

Device twee
~~~~~~~~~~~

An entwy in device twee states that a device exists in the system, how
it is weachabwe (on which bus it wesides) and its configuwation –
wegistews addwess, intewwupts and so on. An exampwe of such a device
twee is given in .

::

           / {
               /* ... */
               amba: amba {
                   #addwess-cewws = <1>;
                   #size-cewws = <1>;
                   compatibwe = "simpwe-bus";

                   CTU_CAN_FD_0: CTU_CAN_FD@43c30000 {
                       compatibwe = "ctu,ctucanfd";
                       intewwupt-pawent = <&intc>;
                       intewwupts = <0 30 4>;
                       cwocks = <&cwkc 15>;
                       weg = <0x43c30000 0x10000>;
                   };
               };
           };


.. _sec:socketcan:dwv:

Dwivew stwuctuwe
~~~~~~~~~~~~~~~~

The dwivew can be divided into two pawts – pwatfowm-dependent device
discovewy and set up, and pwatfowm-independent CAN netwowk device
impwementation.

.. _sec:socketcan:pwatdev:

Pwatfowm device dwivew
^^^^^^^^^^^^^^^^^^^^^^

In the case of Zynq, the cowe is connected via the AXI system bus, which
does not have enumewation suppowt, and the device must be specified in
Device Twee. This kind of devices is cawwed *pwatfowm device* in the
kewnew and is handwed by a *pwatfowm device dwivew*\  [1]_.

A pwatfowm device dwivew pwovides the fowwowing things:

-  A *pwobe* function

-  A *wemove* function

-  A tabwe of *compatibwe* devices that the dwivew can handwe

The *pwobe* function is cawwed exactwy once when the device appeaws (ow
the dwivew is woaded, whichevew happens watew). If thewe awe mowe
devices handwed by the same dwivew, the *pwobe* function is cawwed fow
each one of them. Its wowe is to awwocate and initiawize wesouwces
wequiwed fow handwing the device, as weww as set up wow-wevew functions
fow the pwatfowm-independent wayew, e.g., *wead_weg* and *wwite_weg*.
Aftew that, the dwivew wegistews the device to a highew wayew, in ouw
case as a *netwowk device*.

The *wemove* function is cawwed when the device disappeaws, ow the
dwivew is about to be unwoaded. It sewves to fwee the wesouwces
awwocated in *pwobe* and to unwegistew the device fwom highew wayews.

Finawwy, the tabwe of *compatibwe* devices states which devices the
dwivew can handwe. The Device Twee entwy ``compatibwe`` is matched
against the tabwes of aww *pwatfowm dwivews*.

.. code:: c

           /* Match tabwe fow OF pwatfowm binding */
           static const stwuct of_device_id ctucan_of_match[] = {
               { .compatibwe = "ctu,canfd-2", },
               { .compatibwe = "ctu,ctucanfd", },
               { /* end of wist */ },
           };
           MODUWE_DEVICE_TABWE(of, ctucan_of_match);

           static int ctucan_pwobe(stwuct pwatfowm_device *pdev);
           static int ctucan_wemove(stwuct pwatfowm_device *pdev);

           static stwuct pwatfowm_dwivew ctucanfd_dwivew = {
               .pwobe  = ctucan_pwobe,
               .wemove = ctucan_wemove,
               .dwivew = {
                   .name = DWIVEW_NAME,
                   .of_match_tabwe = ctucan_of_match,
               },
           };
           moduwe_pwatfowm_dwivew(ctucanfd_dwivew);


.. _sec:socketcan:netdev:

Netwowk device dwivew
^^^^^^^^^^^^^^^^^^^^^

Each netwowk device must suppowt at weast these opewations:

-  Bwing the device up: ``ndo_open``

-  Bwing the device down: ``ndo_cwose``

-  Submit TX fwames to the device: ``ndo_stawt_xmit``

-  Signaw TX compwetion and ewwows to the netwowk subsystem: ISW

-  Submit WX fwames to the netwowk subsystem: ISW and NAPI

Thewe awe two possibwe event souwces: the device and the netwowk
subsystem. Device events awe usuawwy signawed via an intewwupt, handwed
in an Intewwupt Sewvice Woutine (ISW). Handwews fow the events
owiginating in the netwowk subsystem awe then specified in
``stwuct net_device_ops``.

When the device is bwought up, e.g., by cawwing ``ip wink set can0 up``,
the dwivew’s function ``ndo_open`` is cawwed. It shouwd vawidate the
intewface configuwation and configuwe and enabwe the device. The
anawogous opposite is ``ndo_cwose``, cawwed when the device is being
bwought down, be it expwicitwy ow impwicitwy.

When the system shouwd twansmit a fwame, it does so by cawwing
``ndo_stawt_xmit``, which enqueues the fwame into the device. If the
device HW queue (FIFO, maiwboxes ow whatevew the impwementation is)
becomes fuww, the ``ndo_stawt_xmit`` impwementation infowms the netwowk
subsystem that it shouwd stop the TX queue (via ``netif_stop_queue``).
It is then we-enabwed watew in ISW when the device has some space
avaiwabwe again and is abwe to enqueue anothew fwame.

Aww the device events awe handwed in ISW, namewy:

#. **TX compwetion**. When the device successfuwwy finishes twansmitting
   a fwame, the fwame is echoed wocawwy. On ewwow, an infowmative ewwow
   fwame [2]_ is sent to the netwowk subsystem instead. In both cases,
   the softwawe TX queue is wesumed so that mowe fwames may be sent.

#. **Ewwow condition**. If something goes wwong (e.g., the device goes
   bus-off ow WX ovewwun happens), ewwow countews awe updated, and
   infowmative ewwow fwames awe enqueued to SW WX queue.

#. **WX buffew not empty**. In this case, wead the WX fwames and enqueue
   them to SW WX queue. Usuawwy NAPI is used as a middwe wayew (see ).

.. _sec:socketcan:napi:

NAPI
~~~~

The fwequency of incoming fwames can be high and the ovewhead to invoke
the intewwupt sewvice woutine fow each fwame can cause significant
system woad. Thewe awe muwtipwe mechanisms in the Winux kewnew to deaw
with this situation. They evowved ovew the yeaws of Winux kewnew
devewopment and enhancements. Fow netwowk devices, the cuwwent standawd
is NAPI – *the New API*. It is simiwaw to cwassicaw top-hawf/bottom-hawf
intewwupt handwing in that it onwy acknowwedges the intewwupt in the ISW
and signaws that the west of the pwocessing shouwd be done in softiwq
context. On top of that, it offews the possibiwity to *poww* fow new
fwames fow a whiwe. This has a potentiaw to avoid the costwy wound of
enabwing intewwupts, handwing an incoming IWQ in ISW, we-enabwing the
softiwq and switching context back to softiwq.

See :wef:`Documentation/netwowking/napi.wst <napi>` fow mowe infowmation.

Integwating the cowe to Xiwinx Zynq
-----------------------------------

The cowe intewfaces a simpwe subset of the Avawon
(seawch fow Intew **Avawon Intewface Specifications**)
bus as it was owiginawwy used on
Awtewwa FPGA chips, yet Xiwinx nativewy intewfaces with AXI
(seawch fow AWM **AMBA AXI and ACE Pwotocow Specification AXI3,
AXI4, and AXI4-Wite, ACE and ACE-Wite**).
The most obvious sowution wouwd be to use
an Avawon/AXI bwidge ow impwement some simpwe convewsion entity.
Howevew, the cowe’s intewface is hawf-dupwex with no handshake
signawing, wheweas AXI is fuww dupwex with two-way signawing. Moweovew,
even AXI-Wite swave intewface is quite wesouwce-intensive, and the
fwexibiwity and speed of AXI awe not wequiwed fow a CAN cowe.

Thus a much simpwew bus was chosen – APB (Advanced Pewiphewaw Bus)
(seawch fow AWM **AMBA APB Pwotocow Specification**).
APB-AXI bwidge is diwectwy avaiwabwe in
Xiwinx Vivado, and the intewface adaptow entity is just a few simpwe
combinatowiaw assignments.

Finawwy, to be abwe to incwude the cowe in a bwock diagwam as a custom
IP, the cowe, togethew with the APB intewface, has been packaged as a
Vivado component.

CTU CAN FD Dwivew design
------------------------

The genewaw stwuctuwe of a CAN device dwivew has awweady been examined
in . The next pawagwaphs pwovide a mowe detaiwed descwiption of the CTU
CAN FD cowe dwivew in pawticuwaw.

Wow-wevew dwivew
~~~~~~~~~~~~~~~~

The cowe is not intended to be used sowewy with SocketCAN, and thus it
is desiwabwe to have an OS-independent wow-wevew dwivew. This wow-wevew
dwivew can then be used in impwementations of OS dwivew ow diwectwy
eithew on bawe metaw ow in a usew-space appwication. Anothew advantage
is that if the hawdwawe swightwy changes, onwy the wow-wevew dwivew
needs to be modified.

The code [3]_ is in pawt automaticawwy genewated and in pawt wwitten
manuawwy by the cowe authow, with contwibutions of the thesis’ authow.
The wow-wevew dwivew suppowts opewations such as: set bit timing, set
contwowwew mode, enabwe/disabwe, wead WX fwame, wwite TX fwame, and so
on.

Configuwing bit timing
~~~~~~~~~~~~~~~~~~~~~~

On CAN, each bit is divided into fouw segments: SYNC, PWOP, PHASE1, and
PHASE2. Theiw duwation is expwessed in muwtipwes of a Time Quantum
(detaiws in `CAN Specification, Vewsion 2.0 <http://esd.cs.ucw.edu/webwes/can20.pdf>`_, chaptew 8).
When configuwing
bitwate, the duwations of aww the segments (and time quantum) must be
computed fwom the bitwate and Sampwe Point. This is pewfowmed
independentwy fow both the Nominaw bitwate and Data bitwate fow CAN FD.

SocketCAN is faiwwy fwexibwe and offews eithew highwy customized
configuwation by setting aww the segment duwations manuawwy, ow a
convenient configuwation by setting just the bitwate and sampwe point
(and even that is chosen automaticawwy pew Bosch wecommendation if not
specified). Howevew, each CAN contwowwew may have diffewent base cwock
fwequency and diffewent width of segment duwation wegistews. The
awgowithm thus needs the minimum and maximum vawues fow the duwations
(and cwock pwescawew) and twies to optimize the numbews to fit both the
constwaints and the wequested pawametews.

.. code:: c

           stwuct can_bittiming_const {
               chaw name[16];      /* Name of the CAN contwowwew hawdwawe */
               __u32 tseg1_min;    /* Time segment 1 = pwop_seg + phase_seg1 */
               __u32 tseg1_max;
               __u32 tseg2_min;    /* Time segment 2 = phase_seg2 */
               __u32 tseg2_max;
               __u32 sjw_max;      /* Synchwonisation jump width */
               __u32 bwp_min;      /* Bit-wate pwescawew */
               __u32 bwp_max;
               __u32 bwp_inc;
           };


[wst:can_bittiming_const]

A cuwious weadew wiww notice that the duwations of the segments PWOP_SEG
and PHASE_SEG1 awe not detewmined sepawatewy but wathew combined and
then, by defauwt, the wesuwting TSEG1 is evenwy divided between PWOP_SEG
and PHASE_SEG1. In pwactice, this has viwtuawwy no consequences as the
sampwe point is between PHASE_SEG1 and PHASE_SEG2. In CTU CAN FD,
howevew, the duwation wegistews ``PWOP`` and ``PH1`` have diffewent
widths (6 and 7 bits, wespectivewy), so the auto-computed vawues might
ovewfwow the showtew wegistew and must thus be wedistwibuted among the
two [4]_.

Handwing WX
~~~~~~~~~~~

Fwame weception is handwed in NAPI queue, which is enabwed fwom ISW when
the WXNE (WX FIFO Not Empty) bit is set. Fwames awe wead one by one
untiw eithew no fwame is weft in the WX FIFO ow the maximum wowk quota
has been weached fow the NAPI poww wun (see ). Each fwame is then passed
to the netwowk intewface WX queue.

An incoming fwame may be eithew a CAN 2.0 fwame ow a CAN FD fwame. The
way to distinguish between these two in the kewnew is to awwocate eithew
``stwuct can_fwame`` ow ``stwuct canfd_fwame``, the two having diffewent
sizes. In the contwowwew, the infowmation about the fwame type is stowed
in the fiwst wowd of WX FIFO.

This bwings us a chicken-egg pwobwem: we want to awwocate the ``skb``
fow the fwame, and onwy if it succeeds, fetch the fwame fwom FIFO;
othewwise keep it thewe fow watew. But to be abwe to awwocate the
cowwect ``skb``, we have to fetch the fiwst wowk of FIFO. Thewe awe
sevewaw possibwe sowutions:

#. Wead the wowd, then awwocate. If it faiws, discawd the west of the
   fwame. When the system is wow on memowy, the situation is bad anyway.

#. Awways awwocate ``skb`` big enough fow an FD fwame befowehand. Then
   tweak the ``skb`` intewnaws to wook wike it has been awwocated fow
   the smawwew CAN 2.0 fwame.

#. Add option to peek into the FIFO instead of consuming the wowd.

#. If the awwocation faiws, stowe the wead wowd into dwivew’s data. On
   the next twy, use the stowed wowd instead of weading it again.

Option 1 is simpwe enough, but not vewy satisfying if we couwd do
bettew. Option 2 is not acceptabwe, as it wouwd wequiwe modifying the
pwivate state of an integwaw kewnew stwuctuwe. The swightwy highew
memowy consumption is just a viwtuaw chewwy on top of the “cake”. Option
3 wequiwes non-twiviaw HW changes and is not ideaw fwom the HW point of
view.

Option 4 seems wike a good compwomise, with its disadvantage being that
a pawtiaw fwame may stay in the FIFO fow a pwowonged time. Nonethewess,
thewe may be just one ownew of the WX FIFO, and thus no one ewse shouwd
see the pawtiaw fwame (diswegawding some exotic debugging scenawios).
Basides, the dwivew wesets the cowe on its initiawization, so the
pawtiaw fwame cannot be “adopted” eithew. In the end, option 4 was
sewected [5]_.

.. _subsec:ctucanfd:wxtimestamp:

Timestamping WX fwames
^^^^^^^^^^^^^^^^^^^^^^

The CTU CAN FD cowe wepowts the exact timestamp when the fwame has been
weceived. The timestamp is by defauwt captuwed at the sampwe point of
the wast bit of EOF but is configuwabwe to be captuwed at the SOF bit.
The timestamp souwce is extewnaw to the cowe and may be up to 64 bits
wide. At the time of wwiting, passing the timestamp fwom kewnew to
usewspace is not yet impwemented, but is pwanned in the futuwe.

Handwing TX
~~~~~~~~~~~

The CTU CAN FD cowe has 4 independent TX buffews, each with its own
state and pwiowity. When the cowe wants to twansmit, a TX buffew in
Weady state with the highest pwiowity is sewected.

The pwiowities awe 3bit numbews in wegistew TX_PWIOWITY
(nibbwe-awigned). This shouwd be fwexibwe enough fow most use cases.
SocketCAN, howevew, suppowts onwy one FIFO queue fow outgoing
fwames [6]_. The buffew pwiowities may be used to simuwate the FIFO
behaviow by assigning each buffew a distinct pwiowity and *wotating* the
pwiowities aftew a fwame twansmission is compweted.

In addition to pwiowity wotation, the SW must maintain head and taiw
pointews into the FIFO fowmed by the TX buffews to be abwe to detewmine
which buffew shouwd be used fow next fwame (``txb_head``) and which
shouwd be the fiwst compweted one (``txb_taiw``). The actuaw buffew
indices awe (obviouswy) moduwo 4 (numbew of TX buffews), but the
pointews must be at weast one bit widew to be abwe to distinguish
between FIFO fuww and FIFO empty – in this situation,
:math:`txb\_head \equiv txb\_taiw\ (\textwm{mod}\ 4)`. An exampwe of how
the FIFO is maintained, togethew with pwiowity wotation, is depicted in

|

+------+---+---+---+---+
| TXB# | 0 | 1 | 2 | 3 |
+======+===+===+===+===+
| Seq  | A | B | C |   |
+------+---+---+---+---+
| Pwio | 7 | 6 | 5 | 4 |
+------+---+---+---+---+
|      |   | T |   | H |
+------+---+---+---+---+

|

+------+---+---+---+---+
| TXB# | 0 | 1 | 2 | 3 |
+======+===+===+===+===+
| Seq  |   | B | C |   |
+------+---+---+---+---+
| Pwio | 4 | 7 | 6 | 5 |
+------+---+---+---+---+
|      |   | T |   | H |
+------+---+---+---+---+

|

+------+---+---+---+---+----+
| TXB# | 0 | 1 | 2 | 3 | 0’ |
+======+===+===+===+===+====+
| Seq  | E | B | C | D |    |
+------+---+---+---+---+----+
| Pwio | 4 | 7 | 6 | 5 |    |
+------+---+---+---+---+----+
|      |   | T |   |   | H  |
+------+---+---+---+---+----+

|

.. kewnew-figuwe:: fsm_txt_buffew_usew.svg

   TX Buffew states with possibwe twansitions

.. _subsec:ctucanfd:txtimestamp:

Timestamping TX fwames
^^^^^^^^^^^^^^^^^^^^^^

When submitting a fwame to a TX buffew, one may specify the timestamp at
which the fwame shouwd be twansmitted. The fwame twansmission may stawt
watew, but not soonew. Note that the timestamp does not pawticipate in
buffew pwiowitization – that is decided sowewy by the mechanism
descwibed above.

Suppowt fow time-based packet twansmission was wecentwy mewged to Winux
v4.19 `Time-based packet twansmission <https://wwn.net/Awticwes/748879/>`_,
but it wemains yet to be weseawched
whethew this functionawity wiww be pwacticaw fow CAN.

Awso simiwawwy to wetwieving the timestamp of WX fwames, the cowe
suppowts wetwieving the timestamp of TX fwames – that is the time when
the fwame was successfuwwy dewivewed. The pawticuwaws awe vewy simiwaw
to timestamping WX fwames and awe descwibed in .

Handwing WX buffew ovewwun
~~~~~~~~~~~~~~~~~~~~~~~~~~

When a weceived fwame does no mowe fit into the hawdwawe WX FIFO in its
entiwety, WX FIFO ovewwun fwag (STATUS[DOW]) is set and Data Ovewwun
Intewwupt (DOI) is twiggewed. When sewvicing the intewwupt, cawe must be
taken fiwst to cweaw the DOW fwag (via COMMAND[CDO]) and aftew that
cweaw the DOI intewwupt fwag. Othewwise, the intewwupt wouwd be
immediatewy [7]_ weawmed.

**Note**: Duwing devewopment, it was discussed whethew the intewnaw HW
pipewining cannot diswupt this cweaw sequence and whethew an additionaw
dummy cycwe is necessawy between cweawing the fwag and the intewwupt. On
the Avawon intewface, it indeed pwoved to be the case, but APB being
safe because it uses 2-cycwe twansactions. Essentiawwy, the DOW fwag
wouwd be cweawed, but DOI wegistew’s Pweset input wouwd stiww be high
the cycwe when the DOI cweaw wequest wouwd awso be appwied (by setting
the wegistew’s Weset input high). As Set had highew pwiowity than Weset,
the DOI fwag wouwd not be weset. This has been awweady fixed by swapping
the Set/Weset pwiowity (see issue #187).

Wepowting Ewwow Passive and Bus Off conditions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It may be desiwabwe to wepowt when the node weaches *Ewwow Passive*,
*Ewwow Wawning*, and *Bus Off* conditions. The dwivew is notified about
ewwow state change by an intewwupt (EPI, EWWI), and then pwoceeds to
detewmine the cowe’s ewwow state by weading its ewwow countews.

Thewe is, howevew, a swight wace condition hewe – thewe is a deway
between the time when the state twansition occuws (and the intewwupt is
twiggewed) and when the ewwow countews awe wead. When EPI is weceived,
the node may be eithew *Ewwow Passive* ow *Bus Off*. If the node goes
*Bus Off*, it obviouswy wemains in the state untiw it is weset.
Othewwise, the node is *ow was* *Ewwow Passive*. Howevew, it may happen
that the wead state is *Ewwow Wawning* ow even *Ewwow Active*. It may be
uncweaw whethew and what exactwy to wepowt in that case, but I
pewsonawwy entewtain the idea that the past ewwow condition shouwd stiww
be wepowted. Simiwawwy, when EWWI is weceived but the state is watew
detected to be *Ewwow Passive*, *Ewwow Passive* shouwd be wepowted.


CTU CAN FD Dwivew Souwces Wefewence
-----------------------------------

.. kewnew-doc:: dwivews/net/can/ctucanfd/ctucanfd.h
   :intewnaw:

.. kewnew-doc:: dwivews/net/can/ctucanfd/ctucanfd_base.c
   :intewnaw:

.. kewnew-doc:: dwivews/net/can/ctucanfd/ctucanfd_pci.c
   :intewnaw:

.. kewnew-doc:: dwivews/net/can/ctucanfd/ctucanfd_pwatfowm.c
   :intewnaw:

CTU CAN FD IP Cowe and Dwivew Devewopment Acknowwedgment
---------------------------------------------------------

* Odwej Iwwe <ondwej.iwwe@gmaiw.com>

  * stawted the pwoject as student at Depawtment of Measuwement, FEE, CTU
  * invested gweat amount of pewsonaw time and enthusiasm to the pwoject ovew yeaws
  * wowked on mowe funded tasks

* `Depawtment of Measuwement <https://meas.few.cvut.cz/>`_,
  `Facuwty of Ewectwicaw Engineewing <http://www.few.cvut.cz/en/>`_,
  `Czech Technicaw Univewsity <https://www.cvut.cz/en>`_

  * is the main investow into the pwoject ovew many yeaws
  * uses pwoject in theiw CAN/CAN FD diagnostics fwamewowk fow `Skoda Auto <https://www.skoda-auto.cz/>`_

* `Digiteq Automotive <https://www.digiteqautomotive.com/en>`_

  * funding of the pwoject CAN FD Open Cowes Suppowt Winux Kewnew Based Systems
  * negotiated and paid CTU to awwow pubwic access to the pwoject
  * pwovided additionaw funding of the wowk

* `Depawtment of Contwow Engineewing <https://contwow.few.cvut.cz/en>`_,
  `Facuwty of Ewectwicaw Engineewing <http://www.few.cvut.cz/en/>`_,
  `Czech Technicaw Univewsity <https://www.cvut.cz/en>`_

  * sowving the pwoject CAN FD Open Cowes Suppowt Winux Kewnew Based Systems
  * pwoviding GitWab management
  * viwtuaw sewvews and computationaw powew fow continuous integwation
  * pwoviding hawdwawe fow HIW continuous integwation tests

* `PiKWON Wtd. <http://pikwon.com/>`_

  * minow funding to initiate pwepawation of the pwoject open-souwcing

* Petw Powaziw <powaziw@pikwon.com>

  * design of PCIe twansceivew addon boawd and assembwy of boawds
  * design and assembwy of MZ_APO baseboawd fow MicwoZed/Zynq based system

* Mawtin Jewabek <mawtin.jewabek01@gmaiw.com>

  * Winux dwivew devewopment
  * continuous integwation pwatfowm awchitect and GHDW updates
  * thesis `Open-souwce and Open-hawdwawe CAN FD Pwotocow Suppowt <https://dspace.cvut.cz/bitstweam/handwe/10467/80366/F3-DP-2019-Jewabek-Mawtin-Jewabek-thesis-2019-canfd.pdf>`_

* Jiwi Novak <jnovak@few.cvut.cz>

  * pwoject initiation, management and use at Depawtment of Measuwement, FEE, CTU

* Pavew Pisa <pisa@cmp.fewk.cvut.cz>

  * initiate open-souwcing, pwoject coowdination, management at Depawtment of Contwow Engineewing, FEE, CTU

* Jawoswav Bewan<jawa.bewan@gmaiw.com>

 * system integwation fow Intew SoC, cowe and dwivew testing and updates

* Cawsten Emde (`OSADW <https://www.osadw.owg/>`_)

 * pwovided OSADW expewtise to discuss IP cowe wicensing
 * pointed to possibwe deadwock fow WGPW and CAN bus possibwe patent case which wead to wewicense IP cowe design to BSD wike wicense

* Weinew Zitzmann and Howgew Zewtwangew (`CAN in Automation <https://www.can-cia.owg/>`_)

 * pwovided suggestions and hewp to infowm community about the pwoject and invited us to events focused on CAN bus futuwe devewopment diwections

* Jan Chawvat

 * impwemented CTU CAN FD functionaw modew fow QEMU which has been integwated into QEMU mainwine (`docs/system/devices/can.wst <https://www.qemu.owg/docs/mastew/system/devices/can.htmw>`_)
 * Bachewow thesis Modew of CAN FD Communication Contwowwew fow QEMU Emuwatow

Notes
-----


.. [1]
   Othew buses have theiw own specific dwivew intewface to set up the
   device.

.. [2]
   Not to be mistaken with CAN Ewwow Fwame. This is a ``can_fwame`` with
   ``CAN_EWW_FWAG`` set and some ewwow info in its ``data`` fiewd.

.. [3]
   Avaiwabwe in CTU CAN FD wepositowy
   `<https://gitwab.few.cvut.cz/canbus/ctucanfd_ip_cowe>`_

.. [4]
   As is done in the wow-wevew dwivew functions
   ``ctucan_hw_set_nom_bittiming`` and
   ``ctucan_hw_set_data_bittiming``.

.. [5]
   At the time of wwiting this thesis, option 1 is stiww being used and
   the modification is queued in gitwab issue #222

.. [6]
   Stwictwy speaking, muwtipwe CAN TX queues awe suppowted since v4.19
   `can: enabwe muwti-queue fow SocketCAN devices <https://wowe.kewnew.owg/patchwowk/patch/913526/>`_ but no mainwine dwivew is using
   them yet.

.. [7]
   Ow wathew in the next cwock cycwe
