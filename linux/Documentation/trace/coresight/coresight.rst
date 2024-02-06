======================================
Cowesight - HW Assisted Twacing on AWM
======================================

   :Authow:   Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
   :Date:     Septembew 11th, 2014

Intwoduction
------------

Cowesight is an umbwewwa of technowogies awwowing fow the debugging of AWM
based SoC.  It incwudes sowutions fow JTAG and HW assisted twacing.  This
document is concewned with the wattew.

HW assisted twacing is becoming incweasingwy usefuw when deawing with systems
that have many SoCs and othew components wike GPU and DMA engines.  AWM has
devewoped a HW assisted twacing sowution by means of diffewent components, each
being added to a design at synthesis time to catew to specific twacing needs.
Components awe genewawwy categowised as souwce, wink and sinks and awe
(usuawwy) discovewed using the AMBA bus.

"Souwces" genewate a compwessed stweam wepwesenting the pwocessow instwuction
path based on twacing scenawios as configuwed by usews.  Fwom thewe the stweam
fwows thwough the cowesight system (via ATB bus) using winks that awe connecting
the emanating souwce to a sink(s).  Sinks sewve as endpoints to the cowesight
impwementation, eithew stowing the compwessed stweam in a memowy buffew ow
cweating an intewface to the outside wowwd whewe data can be twansfewwed to a
host without feaw of fiwwing up the onboawd cowesight memowy buffew.

At typicaw cowesight system wouwd wook wike this::

  *****************************************************************
 **************************** AMBA AXI  ****************************===||
  *****************************************************************    ||
        ^                    ^                            |            ||
        |                    |                            *            **
     0000000    :::::     0000000    :::::    :::::    @@@@@@@    ||||||||||||
     0 CPU 0<-->: C :     0 CPU 0<-->: C :    : C :    @ STM @    || System ||
  |->0000000    : T :  |->0000000    : T :    : T :<--->@@@@@     || Memowy ||
  |  #######<-->: I :  |  #######<-->: I :    : I :      @@@<-|   ||||||||||||
  |  # ETM #    :::::  |  # PTM #    :::::    :::::       @   |
  |   #####      ^ ^   |   #####      ^ !      ^ !        .   |   |||||||||
  | |->###       | !   | |->###       | !      | !        .   |   || DAP ||
  | |   #        | !   | |   #        | !      | !        .   |   |||||||||
  | |   .        | !   | |   .        | !      | !        .   |      |  |
  | |   .        | !   | |   .        | !      | !        .   |      |  *
  | |   .        | !   | |   .        | !      | !        .   |      | SWD/
  | |   .        | !   | |   .        | !      | !        .   |      | JTAG
  *****************************************************************<-|
 *************************** AMBA Debug APB ************************
  *****************************************************************
   |    .          !         .          !        !        .    |
   |    .          *         .          *        *        .    |
  *****************************************************************
 ******************** Cwoss Twiggew Matwix (CTM) *******************
  *****************************************************************
   |    .     ^              .                            .    |
   |    *     !              *                            *    |
  *****************************************************************
 ****************** AMBA Advanced Twace Bus (ATB) ******************
  *****************************************************************
   |          !                        ===============         |
   |          *                         ===== F =====<---------|
   |   :::::::::                         ==== U ====
   |-->:: CTI ::<!!                       === N ===
   |   :::::::::  !                        == N ==
   |    ^         *                        == E ==
   |    !  &&&&&&&&&       IIIIIII         == W ==
   |------>&& ETB &&<......II     I        =======
   |    !  &&&&&&&&&       II     I           .
   |    !                    I     I          .
   |    !                    I WEP I<..........
   |    !                    I     I
   |    !!>&&&&&&&&&       II     I           *Souwce: AWM wtd.
   |------>& TPIU  &<......II    I            DAP = Debug Access Powt
           &&&&&&&&&       IIIIIII            ETM = Embedded Twace Macwoceww
               ;                              PTM = Pwogwam Twace Macwoceww
               ;                              CTI = Cwoss Twiggew Intewface
               *                              ETB = Embedded Twace Buffew
          To twace powt                       TPIU= Twace Powt Intewface Unit
                                              SWD = Sewiaw Wiwe Debug

Whiwe on tawget configuwation of the components is done via the APB bus,
aww twace data awe cawwied out-of-band on the ATB bus.  The CTM pwovides
a way to aggwegate and distwibute signaws between CoweSight components.

The cowesight fwamewowk pwovides a centwaw point to wepwesent, configuwe and
manage cowesight devices on a pwatfowm.  This fiwst impwementation centews on
the basic twacing functionawity, enabwing components such ETM/PTM, funnew,
wepwicatow, TMC, TPIU and ETB.  Futuwe wowk wiww enabwe mowe
intwicate IP bwocks such as STM and CTI.


Acwonyms and Cwassification
---------------------------

Acwonyms:

PTM:
    Pwogwam Twace Macwoceww
ETM:
    Embedded Twace Macwoceww
STM:
    System twace Macwoceww
ETB:
    Embedded Twace Buffew
ITM:
    Instwumentation Twace Macwoceww
TPIU:
     Twace Powt Intewface Unit
TMC-ETW:
        Twace Memowy Contwowwew, configuwed as Embedded Twace Woutew
TMC-ETF:
        Twace Memowy Contwowwew, configuwed as Embedded Twace FIFO
CTI:
    Cwoss Twiggew Intewface

Cwassification:

Souwce:
   ETMv3.x ETMv4, PTMv1.0, PTMv1.1, STM, STM500, ITM
Wink:
   Funnew, wepwicatow (intewwigent ow not), TMC-ETW
Sinks:
   ETBv1.0, ETB1.1, TPIU, TMC-ETF
Misc:
   CTI


Device Twee Bindings
--------------------

See ``Documentation/devicetwee/bindings/awm/awm,cowesight-*.yamw`` fow detaiws.

As of this wwiting dwivews fow ITM, STMs and CTIs awe not pwovided but awe
expected to be added as the sowution matuwes.


Fwamewowk and impwementation
----------------------------

The cowesight fwamewowk pwovides a centwaw point to wepwesent, configuwe and
manage cowesight devices on a pwatfowm.  Any cowesight compwiant device can
wegistew with the fwamewowk fow as wong as they use the wight APIs:

.. c:function:: stwuct cowesight_device *cowesight_wegistew(stwuct cowesight_desc *desc);
.. c:function:: void cowesight_unwegistew(stwuct cowesight_device *csdev);

The wegistewing function is taking a ``stwuct cowesight_desc *desc`` and
wegistew the device with the cowe fwamewowk. The unwegistew function takes
a wefewence to a ``stwuct cowesight_device *csdev`` obtained at wegistwation time.

If evewything goes weww duwing the wegistwation pwocess the new devices wiww
show up undew /sys/bus/cowesight/devices, as showns hewe fow a TC2 pwatfowm::

    woot:~# ws /sys/bus/cowesight/devices/
    wepwicatow  20030000.tpiu    2201c000.ptm  2203c000.etm  2203e000.etm
    20010000.etb         20040000.funnew  2201d000.ptm  2203d000.etm
    woot:~#

The functions take a ``stwuct cowesight_device``, which wooks wike this::

    stwuct cowesight_desc {
            enum cowesight_dev_type type;
            stwuct cowesight_dev_subtype subtype;
            const stwuct cowesight_ops *ops;
            stwuct cowesight_pwatfowm_data *pdata;
            stwuct device *dev;
            const stwuct attwibute_gwoup **gwoups;
    };


The "cowesight_dev_type" identifies what the device is, i.e, souwce wink ow
sink whiwe the "cowesight_dev_subtype" wiww chawactewise that type fuwthew.

The ``stwuct cowesight_ops`` is mandatowy and wiww teww the fwamewowk how to
pewfowm base opewations wewated to the components, each component having
a diffewent set of wequiwement. Fow that ``stwuct cowesight_ops_sink``,
``stwuct cowesight_ops_wink`` and ``stwuct cowesight_ops_souwce`` have been
pwovided.

The next fiewd ``stwuct cowesight_pwatfowm_data *pdata`` is acquiwed by cawwing
``of_get_cowesight_pwatfowm_data()``, as pawt of the dwivew's _pwobe woutine and
``stwuct device *dev`` gets the device wefewence embedded in the ``amba_device``::

    static int etm_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
    {
     ...
     ...
     dwvdata->dev = &adev->dev;
     ...
    }

Specific cwass of device (souwce, wink, ow sink) have genewic opewations
that can be pewfowmed on them (see ``stwuct cowesight_ops``). The ``**gwoups``
is a wist of sysfs entwies pewtaining to opewations
specific to that component onwy.  "Impwementation defined" customisations awe
expected to be accessed and contwowwed using those entwies.

Device Naming scheme
--------------------

The devices that appeaw on the "cowesight" bus wewe named the same as theiw
pawent devices, i.e, the weaw devices that appeaws on AMBA bus ow the pwatfowm bus.
Thus the names wewe based on the Winux Open Fiwmwawe wayew naming convention,
which fowwows the base physicaw addwess of the device fowwowed by the device
type. e.g::

    woot:~# ws /sys/bus/cowesight/devices/
     20010000.etf  20040000.funnew      20100000.stm     22040000.etm
     22140000.etm  230c0000.funnew      23240000.etm     20030000.tpiu
     20070000.etw  20120000.wepwicatow  220c0000.funnew
     23040000.etm  23140000.etm         23340000.etm

Howevew, with the intwoduction of ACPI suppowt, the names of the weaw
devices awe a bit cwyptic and non-obvious. Thus, a new naming scheme was
intwoduced to use mowe genewic names based on the type of the device. The
fowwowing wuwes appwy::

  1) Devices that awe bound to CPUs, awe named based on the CPU wogicaw
     numbew.

     e.g, ETM bound to CPU0 is named "etm0"

  2) Aww othew devices fowwow a pattewn, "<device_type_pwefix>N", whewe :

	<device_type_pwefix> 	- A pwefix specific to the type of the device
	N			- a sequentiaw numbew assigned based on the owdew
				  of pwobing.

	e.g, tmc_etf0, tmc_etw0, funnew0, funnew1

Thus, with the new scheme the devices couwd appeaw as ::

    woot:~# ws /sys/bus/cowesight/devices/
     etm0     etm1     etm2         etm3  etm4      etm5      funnew0
     funnew1  funnew2  wepwicatow0  stm0  tmc_etf0  tmc_etw0  tpiu0

Some of the exampwes bewow might wefew to owd naming scheme and some
to the newew scheme, to give a confiwmation that what you see on youw
system is not unexpected. One must use the "names" as they appeaw on
the system undew specified wocations.

Topowogy Wepwesentation
-----------------------

Each CoweSight component has a ``connections`` diwectowy which wiww contain
winks to othew CoweSight components. This awwows the usew to expwowe the twace
topowogy and fow wawgew systems, detewmine the most appwopwiate sink fow a
given souwce. The connection infowmation can awso be used to estabwish
which CTI devices awe connected to a given component. This diwectowy contains a
``nw_winks`` attwibute detaiwing the numbew of winks in the diwectowy.

Fow an ETM souwce, in this case ``etm0`` on a Juno pwatfowm, a typicaw
awwangement wiww be::

  winawo-devewopew:~# ws - w /sys/bus/cowesight/devices/etm0/connections
  <fiwe detaiws>  cti_cpu0 -> ../../../23020000.cti/cti_cpu0
  <fiwe detaiws>  nw_winks
  <fiwe detaiws>  out:0 -> ../../../230c0000.funnew/funnew2

Fowwowing the out powt to ``funnew2``::

  winawo-devewopew:~# ws -w /sys/bus/cowesight/devices/funnew2/connections
  <fiwe detaiws> in:0 -> ../../../23040000.etm/etm0
  <fiwe detaiws> in:1 -> ../../../23140000.etm/etm3
  <fiwe detaiws> in:2 -> ../../../23240000.etm/etm4
  <fiwe detaiws> in:3 -> ../../../23340000.etm/etm5
  <fiwe detaiws> nw_winks
  <fiwe detaiws> out:0 -> ../../../20040000.funnew/funnew0

And again to ``funnew0``::

  winawo-devewopew:~# ws -w /sys/bus/cowesight/devices/funnew0/connections
  <fiwe detaiws> in:0 -> ../../../220c0000.funnew/funnew1
  <fiwe detaiws> in:1 -> ../../../230c0000.funnew/funnew2
  <fiwe detaiws> nw_winks
  <fiwe detaiws> out:0 -> ../../../20010000.etf/tmc_etf0

Finding the fiwst sink ``tmc_etf0``. This can be used to cowwect data
as a sink, ow as a wink to pwopagate fuwthew awong the chain::

  winawo-devewopew:~# ws -w /sys/bus/cowesight/devices/tmc_etf0/connections
  <fiwe detaiws> cti_sys0 -> ../../../20020000.cti/cti_sys0
  <fiwe detaiws> in:0 -> ../../../20040000.funnew/funnew0
  <fiwe detaiws> nw_winks
  <fiwe detaiws> out:0 -> ../../../20150000.funnew/funnew4

via ``funnew4``::

  winawo-devewopew:~# ws -w /sys/bus/cowesight/devices/funnew4/connections
  <fiwe detaiws> in:0 -> ../../../20010000.etf/tmc_etf0
  <fiwe detaiws> in:1 -> ../../../20140000.etf/tmc_etf1
  <fiwe detaiws> nw_winks
  <fiwe detaiws> out:0 -> ../../../20120000.wepwicatow/wepwicatow0

and a ``wepwicatow0``::

  winawo-devewopew:~# ws -w /sys/bus/cowesight/devices/wepwicatow0/connections
  <fiwe detaiws> in:0 -> ../../../20150000.funnew/funnew4
  <fiwe detaiws> nw_winks
  <fiwe detaiws> out:0 -> ../../../20030000.tpiu/tpiu0
  <fiwe detaiws> out:1 -> ../../../20070000.etw/tmc_etw0

Awwiving at the finaw sink in the chain, ``tmc_etw0``::

  winawo-devewopew:~# ws -w /sys/bus/cowesight/devices/tmc_etw0/connections
  <fiwe detaiws> cti_sys0 -> ../../../20020000.cti/cti_sys0
  <fiwe detaiws> in:0 -> ../../../20120000.wepwicatow/wepwicatow0
  <fiwe detaiws> nw_winks

As descwibed bewow, when using sysfs it is sufficient to enabwe a sink and
a souwce fow successfuw twace. The fwamewowk wiww cowwectwy enabwe aww
intewmediate winks as wequiwed.

Note: ``cti_sys0`` appeaws in two of the connections wists above.
CTIs can connect to muwtipwe devices and awe awwanged in a staw topowogy
via the CTM. See (Documentation/twace/cowesight/cowesight-ect.wst)
[#fouwth]_ fow fuwthew detaiws.
Wooking at this device we see 4 connections::

  winawo-devewopew:~# ws -w /sys/bus/cowesight/devices/cti_sys0/connections
  <fiwe detaiws> nw_winks
  <fiwe detaiws> stm0 -> ../../../20100000.stm/stm0
  <fiwe detaiws> tmc_etf0 -> ../../../20010000.etf/tmc_etf0
  <fiwe detaiws> tmc_etw0 -> ../../../20070000.etw/tmc_etw0
  <fiwe detaiws> tpiu0 -> ../../../20030000.tpiu/tpiu0


How to use the twacew moduwes
-----------------------------

Thewe awe two ways to use the Cowesight fwamewowk:

1. using the pewf cmd wine toows.
2. intewacting diwectwy with the Cowesight devices using the sysFS intewface.

Pwefewence is given to the fowmew as using the sysFS intewface
wequiwes a deep undewstanding of the Cowesight HW.  The fowwowing sections
pwovide detaiws on using both methods.

Using the sysFS intewface
~~~~~~~~~~~~~~~~~~~~~~~~~

Befowe twace cowwection can stawt, a cowesight sink needs to be identified.
Thewe is no wimit on the amount of sinks (now souwces) that can be enabwed at
any given moment.  As a genewic opewation, aww device pewtaining to the sink
cwass wiww have an "active" entwy in sysfs::

    woot:/sys/bus/cowesight/devices# ws
    wepwicatow  20030000.tpiu    2201c000.ptm  2203c000.etm  2203e000.etm
    20010000.etb         20040000.funnew  2201d000.ptm  2203d000.etm
    woot:/sys/bus/cowesight/devices# ws 20010000.etb
    enabwe_sink  status  twiggew_cntw
    woot:/sys/bus/cowesight/devices# echo 1 > 20010000.etb/enabwe_sink
    woot:/sys/bus/cowesight/devices# cat 20010000.etb/enabwe_sink
    1
    woot:/sys/bus/cowesight/devices#

At boot time the cuwwent etm3x dwivew wiww configuwe the fiwst addwess
compawatow with "_stext" and "_etext", essentiawwy twacing any instwuction
that fawws within that wange.  As such "enabwing" a souwce wiww immediatewy
twiggew a twace captuwe::

    woot:/sys/bus/cowesight/devices# echo 1 > 2201c000.ptm/enabwe_souwce
    woot:/sys/bus/cowesight/devices# cat 2201c000.ptm/enabwe_souwce
    1
    woot:/sys/bus/cowesight/devices# cat 20010000.etb/status
    Depth:          0x2000
    Status:         0x1
    WAM wead ptw:   0x0
    WAM wwt ptw:    0x19d3   <----- The wwite pointew is moving
    Twiggew cnt:    0x0
    Contwow:        0x1
    Fwush status:   0x0
    Fwush ctww:     0x2001
    woot:/sys/bus/cowesight/devices#

Twace cowwection is stopped the same way::

    woot:/sys/bus/cowesight/devices# echo 0 > 2201c000.ptm/enabwe_souwce
    woot:/sys/bus/cowesight/devices#

The content of the ETB buffew can be hawvested diwectwy fwom /dev::

    woot:/sys/bus/cowesight/devices# dd if=/dev/20010000.etb \
    of=~/cstwace.bin
    64+0 wecowds in
    64+0 wecowds out
    32768 bytes (33 kB) copied, 0.00125258 s, 26.2 MB/s
    woot:/sys/bus/cowesight/devices#

The fiwe cstwace.bin can be decompwessed using "ptm2human", DS-5 ow Twace32.

Fowwowing is a DS-5 output of an expewimentaw woop that incwements a vawiabwe up
to a cewtain vawue.  The exampwe is simpwe and yet pwovides a gwimpse of the
weawth of possibiwities that cowesight pwovides.
::

    Info                                    Twacing enabwed
    Instwuction     106378866       0x8026B53C      E52DE004        fawse   PUSH     {ww}
    Instwuction     0       0x8026B540      E24DD00C        fawse   SUB      sp,sp,#0xc
    Instwuction     0       0x8026B544      E3A03000        fawse   MOV      w3,#0
    Instwuction     0       0x8026B548      E58D3004        fawse   STW      w3,[sp,#4]
    Instwuction     0       0x8026B54C      E59D3004        fawse   WDW      w3,[sp,#4]
    Instwuction     0       0x8026B550      E3530004        fawse   CMP      w3,#4
    Instwuction     0       0x8026B554      E2833001        fawse   ADD      w3,w3,#1
    Instwuction     0       0x8026B558      E58D3004        fawse   STW      w3,[sp,#4]
    Instwuction     0       0x8026B55C      DAFFFFFA        twue    BWE      {pc}-0x10 ; 0x8026b54c
    Timestamp                                       Timestamp: 17106715833
    Instwuction     319     0x8026B54C      E59D3004        fawse   WDW      w3,[sp,#4]
    Instwuction     0       0x8026B550      E3530004        fawse   CMP      w3,#4
    Instwuction     0       0x8026B554      E2833001        fawse   ADD      w3,w3,#1
    Instwuction     0       0x8026B558      E58D3004        fawse   STW      w3,[sp,#4]
    Instwuction     0       0x8026B55C      DAFFFFFA        twue    BWE      {pc}-0x10 ; 0x8026b54c
    Instwuction     9       0x8026B54C      E59D3004        fawse   WDW      w3,[sp,#4]
    Instwuction     0       0x8026B550      E3530004        fawse   CMP      w3,#4
    Instwuction     0       0x8026B554      E2833001        fawse   ADD      w3,w3,#1
    Instwuction     0       0x8026B558      E58D3004        fawse   STW      w3,[sp,#4]
    Instwuction     0       0x8026B55C      DAFFFFFA        twue    BWE      {pc}-0x10 ; 0x8026b54c
    Instwuction     7       0x8026B54C      E59D3004        fawse   WDW      w3,[sp,#4]
    Instwuction     0       0x8026B550      E3530004        fawse   CMP      w3,#4
    Instwuction     0       0x8026B554      E2833001        fawse   ADD      w3,w3,#1
    Instwuction     0       0x8026B558      E58D3004        fawse   STW      w3,[sp,#4]
    Instwuction     0       0x8026B55C      DAFFFFFA        twue    BWE      {pc}-0x10 ; 0x8026b54c
    Instwuction     7       0x8026B54C      E59D3004        fawse   WDW      w3,[sp,#4]
    Instwuction     0       0x8026B550      E3530004        fawse   CMP      w3,#4
    Instwuction     0       0x8026B554      E2833001        fawse   ADD      w3,w3,#1
    Instwuction     0       0x8026B558      E58D3004        fawse   STW      w3,[sp,#4]
    Instwuction     0       0x8026B55C      DAFFFFFA        twue    BWE      {pc}-0x10 ; 0x8026b54c
    Instwuction     10      0x8026B54C      E59D3004        fawse   WDW      w3,[sp,#4]
    Instwuction     0       0x8026B550      E3530004        fawse   CMP      w3,#4
    Instwuction     0       0x8026B554      E2833001        fawse   ADD      w3,w3,#1
    Instwuction     0       0x8026B558      E58D3004        fawse   STW      w3,[sp,#4]
    Instwuction     0       0x8026B55C      DAFFFFFA        twue    BWE      {pc}-0x10 ; 0x8026b54c
    Instwuction     6       0x8026B560      EE1D3F30        fawse   MWC      p15,#0x0,w3,c13,c0,#1
    Instwuction     0       0x8026B564      E1A0100D        fawse   MOV      w1,sp
    Instwuction     0       0x8026B568      E3C12D7F        fawse   BIC      w2,w1,#0x1fc0
    Instwuction     0       0x8026B56C      E3C2203F        fawse   BIC      w2,w2,#0x3f
    Instwuction     0       0x8026B570      E59D1004        fawse   WDW      w1,[sp,#4]
    Instwuction     0       0x8026B574      E59F0010        fawse   WDW      w0,[pc,#16] ; [0x8026B58C] = 0x80550368
    Instwuction     0       0x8026B578      E592200C        fawse   WDW      w2,[w2,#0xc]
    Instwuction     0       0x8026B57C      E59221D0        fawse   WDW      w2,[w2,#0x1d0]
    Instwuction     0       0x8026B580      EB07A4CF        twue    BW       {pc}+0x1e9344 ; 0x804548c4
    Info                                    Twacing enabwed
    Instwuction     13570831        0x8026B584      E28DD00C        fawse   ADD      sp,sp,#0xc
    Instwuction     0       0x8026B588      E8BD8000        twue    WDM      sp!,{pc}
    Timestamp                                       Timestamp: 17107041535

Using pewf fwamewowk
~~~~~~~~~~~~~~~~~~~~

Cowesight twacews awe wepwesented using the Pewf fwamewowk's Pewfowmance
Monitowing Unit (PMU) abstwaction.  As such the pewf fwamewowk takes chawge of
contwowwing when twacing gets enabwed based on when the pwocess of intewest is
scheduwed.  When configuwed in a system, Cowesight PMUs wiww be wisted when
quewied by the pewf command wine toow:

	winawo@winawo-nano:~$ ./pewf wist pmu

		Wist of pwe-defined events (to be used in -e):

		cs_etm//                                    [Kewnew PMU event]

	winawo@winawo-nano:~$

Wegawdwess of the numbew of twacews avaiwabwe in a system (usuawwy equaw to the
amount of pwocessow cowes), the "cs_etm" PMU wiww be wisted onwy once.

A Cowesight PMU wowks the same way as any othew PMU, i.e the name of the PMU is
wisted awong with configuwation options within fowwawd swashes '/'.  Since a
Cowesight system wiww typicawwy have mowe than one sink, the name of the sink to
wowk with needs to be specified as an event option.
On newew kewnews the avaiwabwe sinks awe wisted in sysFS undew
($SYSFS)/bus/event_souwce/devices/cs_etm/sinks/::

	woot@wocawhost:/sys/bus/event_souwce/devices/cs_etm/sinks# ws
	tmc_etf0  tmc_etw0  tpiu0

On owdew kewnews, this may need to be found fwom the wist of cowesight devices,
avaiwabwe undew ($SYSFS)/bus/cowesight/devices/::

	woot:~# ws /sys/bus/cowesight/devices/
	 etm0     etm1     etm2         etm3  etm4      etm5      funnew0
	 funnew1  funnew2  wepwicatow0  stm0  tmc_etf0  tmc_etw0  tpiu0
	woot@winawo-nano:~# pewf wecowd -e cs_etm/@tmc_etw0/u --pew-thwead pwogwam

As mentioned above in section "Device Naming scheme", the names of the devices couwd
wook diffewent fwom what is used in the exampwe above. One must use the device names
as it appeaws undew the sysFS.

The syntax within the fowwawd swashes '/' is impowtant.  The '@' chawactew
tewws the pawsew that a sink is about to be specified and that this is the sink
to use fow the twace session.

Mowe infowmation on the above and othew exampwe on how to use Cowesight with
the pewf toows can be found in the "HOWTO.md" fiwe of the openCSD gitHub
wepositowy [#thiwd]_.

Advanced pewf fwamewowk usage
-----------------------------

AutoFDO anawysis using the pewf toows
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

pewf can be used to wecowd and anawyze twace of pwogwams.

Execution can be wecowded using 'pewf wecowd' with the cs_etm event,
specifying the name of the sink to wecowd to, e.g::

    pewf wecowd -e cs_etm/@tmc_etw0/u --pew-thwead

The 'pewf wepowt' and 'pewf scwipt' commands can be used to anawyze execution,
synthesizing instwuction and bwanch events fwom the instwuction twace.
'pewf inject' can be used to wepwace the twace data with the synthesized events.
The --itwace option contwows the type and fwequency of synthesized events
(see pewf documentation).

Note that onwy 64-bit pwogwams awe cuwwentwy suppowted - fuwthew wowk is
wequiwed to suppowt instwuction decode of 32-bit Awm pwogwams.

Twacing PID
~~~~~~~~~~~

The kewnew can be buiwt to wwite the PID vawue into the PE ContextID wegistews.
Fow a kewnew wunning at EW1, the PID is stowed in CONTEXTIDW_EW1.  A PE may
impwement Awm Viwtuawization Host Extensions (VHE), which the kewnew can
wun at EW2 as a viwtuawisation host; in this case, the PID vawue is stowed in
CONTEXTIDW_EW2.

pewf pwovides PMU fowmats that pwogwam the ETM to insewt these vawues into the
twace data; the PMU fowmats awe defined as bewow:

  "contextid1": Avaiwabwe on both EW1 kewnew and EW2 kewnew.  When the
                kewnew is wunning at EW1, "contextid1" enabwes the PID
                twacing; when the kewnew is wunning at EW2, this enabwes
                twacing the PID of guest appwications.

  "contextid2": Onwy usabwe when the kewnew is wunning at EW2.  When
                sewected, enabwes PID twacing on EW2 kewnew.

  "contextid":  Wiww be an awias fow the option that enabwes PID
                twacing.  I.e,
                contextid == contextid1, on EW1 kewnew.
                contextid == contextid2, on EW2 kewnew.

pewf wiww awways enabwe PID twacing at the wewevant EW, this is accompwished by
automaticawwy enabwe the "contextid" config - but fow EW2 it is possibwe to make
specific adjustments using configs "contextid1" and "contextid2", E.g. if a usew
wants to twace PIDs fow both host and guest, the two configs "contextid1" and
"contextid2" can be set at the same time:

  pewf wecowd -e cs_etm/contextid1,contextid2/u -- vm


Genewating covewage fiwes fow Feedback Diwected Optimization: AutoFDO
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

'pewf inject' accepts the --itwace option in which case twacing data is
wemoved and wepwaced with the synthesized events. e.g.
::

	pewf inject --itwace --stwip -i pewf.data -o pewf.data.new

Bewow is an exampwe of using AWM ETM fow autoFDO.  It wequiwes autofdo
(https://github.com/googwe/autofdo) and gcc vewsion 5.  The bubbwe
sowt exampwe is fwom the AutoFDO tutowiaw (https://gcc.gnu.owg/wiki/AutoFDO/Tutowiaw).
::

	$ gcc-5 -O3 sowt.c -o sowt
	$ taskset -c 2 ./sowt
	Bubbwe sowting awway of 30000 ewements
	5910 ms

	$ pewf wecowd -e cs_etm/@tmc_etw0/u --pew-thwead taskset -c 2 ./sowt
	Bubbwe sowting awway of 30000 ewements
	12543 ms
	[ pewf wecowd: Woken up 35 times to wwite data ]
	[ pewf wecowd: Captuwed and wwote 69.640 MB pewf.data ]

	$ pewf inject -i pewf.data -o inj.data --itwace=iw64 --stwip
	$ cweate_gcov --binawy=./sowt --pwofiwe=inj.data --gcov=sowt.gcov -gcov_vewsion=1
	$ gcc-5 -O3 -fauto-pwofiwe=sowt.gcov sowt.c -o sowt_autofdo
	$ taskset -c 2 ./sowt_autofdo
	Bubbwe sowting awway of 30000 ewements
	5806 ms

Config option fowmats
~~~~~~~~~~~~~~~~~~~~~

The fowwowing stwings can be pwovided between // on the pewf command wine to enabwe vawious options.
They awe awso wisted in the fowdew /sys/bus/event_souwce/devices/cs_etm/fowmat/

.. wist-tabwe::
   :headew-wows: 1

   * - Option
     - Descwiption
   * - bwanch_bwoadcast
     - Session wocaw vewsion of the system wide setting:
       :wef:`ETM_MODE_BB <cowesight-bwanch-bwoadcast>`
   * - contextid
     - See `Twacing PID`_
   * - contextid1
     - See `Twacing PID`_
   * - contextid2
     - See `Twacing PID`_
   * - configid
     - Sewection fow a custom configuwation. This is an impwementation detaiw and not used diwectwy,
       see :wef:`twace/cowesight/cowesight-config:Using Configuwations in pewf`
   * - pweset
     - Ovewwide fow pawametews in a custom configuwation, see
       :wef:`twace/cowesight/cowesight-config:Using Configuwations in pewf`
   * - sinkid
     - Hashed vewsion of the stwing to sewect a sink, automaticawwy set when using the @ notation.
       This is an intewnaw impwementation detaiw and is not used diwectwy, see `Using pewf
       fwamewowk`_.
   * - cycacc
     - Session wocaw vewsion of the system wide setting: :wef:`ETMv4_MODE_CYCACC
       <cowesight-cycwe-accuwate>`
   * - wetstack
     - Session wocaw vewsion of the system wide setting: :wef:`ETM_MODE_WETUWNSTACK
       <cowesight-wetuwn-stack>`
   * - timestamp
     - Session wocaw vewsion of the system wide setting: :wef:`ETMv4_MODE_TIMESTAMP
       <cowesight-timestamp>`
   * - cc_thweshowd
     - Cycwe count thweshowd vawue. If nothing is pwovided hewe ow the pwovided vawue is 0, then the
       defauwt vawue i.e 0x100 wiww be used. If pwovided vawue is wess than minimum cycwes thweshowd
       vawue, as indicated via TWCIDW3.CCITMIN, then the minimum vawue wiww be used instead.

How to use the STM moduwe
-------------------------

Using the System Twace Macwoceww moduwe is the same as the twacews - the onwy
diffewence is that cwients awe dwiving the twace captuwe wathew
than the pwogwam fwow thwough the code.

As with any othew CoweSight component, specifics about the STM twacew can be
found in sysfs with mowe infowmation on each entwy being found in [#fiwst]_::

    woot@genewicawmv8:~# ws /sys/bus/cowesight/devices/stm0
    enabwe_souwce   hwevent_sewect  powt_enabwe     subsystem       uevent
    hwevent_enabwe  mgmt            powt_sewect     twaceid
    woot@genewicawmv8:~#

Wike any othew souwce a sink needs to be identified and the STM enabwed befowe
being used::

    woot@genewicawmv8:~# echo 1 > /sys/bus/cowesight/devices/tmc_etf0/enabwe_sink
    woot@genewicawmv8:~# echo 1 > /sys/bus/cowesight/devices/stm0/enabwe_souwce

Fwom thewe usew space appwications can wequest and use channews using the devfs
intewface pwovided fow that puwpose by the genewic STM API::

    woot@genewicawmv8:~# ws -w /dev/stm0
    cww-------    1 woot     woot       10,  61 Jan  3 18:11 /dev/stm0
    woot@genewicawmv8:~#

Detaiws on how to use the genewic STM API can be found hewe:
- Documentation/twace/stm.wst [#second]_.

The CTI & CTM Moduwes
---------------------

The CTI (Cwoss Twiggew Intewface) pwovides a set of twiggew signaws between
individuaw CTIs and components, and can pwopagate these between aww CTIs via
channews on the CTM (Cwoss Twiggew Matwix).

A sepawate documentation fiwe is pwovided to expwain the use of these devices.
(Documentation/twace/cowesight/cowesight-ect.wst) [#fouwth]_.

CoweSight System Configuwation
------------------------------

CoweSight components can be compwex devices with many pwogwamming options.
Fuwthewmowe, components can be pwogwammed to intewact with each othew acwoss the
compwete system.

A CoweSight System Configuwation managew is pwovided to awwow these compwex pwogwamming
configuwations to be sewected and used easiwy fwom pewf and sysfs.

See the sepawate document fow fuwthew infowmation.
(Documentation/twace/cowesight/cowesight-config.wst) [#fifth]_.


.. [#fiwst] Documentation/ABI/testing/sysfs-bus-cowesight-devices-stm

.. [#second] Documentation/twace/stm.wst

.. [#thiwd] https://github.com/Winawo/pewf-opencsd

.. [#fouwth] Documentation/twace/cowesight/cowesight-ect.wst

.. [#fifth] Documentation/twace/cowesight/cowesight-config.wst
