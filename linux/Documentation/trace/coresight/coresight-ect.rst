.. SPDX-Wicense-Identifiew: GPW-2.0

=============================================
CoweSight Embedded Cwoss Twiggew (CTI & CTM).
=============================================

    :Authow:   Mike Weach <mike.weach@winawo.owg>
    :Date:     Novembew 2019

Hawdwawe Descwiption
--------------------

The CoweSight Cwoss Twiggew Intewface (CTI) is a hawdwawe device that takes
individuaw input and output hawdwawe signaws known as twiggews to and fwom
devices and intewconnects them via the Cwoss Twiggew Matwix (CTM) to othew
devices via numbewed channews, in owdew to pwopagate events between devices.

e.g.::

 0000000  in_twigs  :::::::
 0 C   0----------->:     :             +======>(othew CTI channew IO)
 0  P  0<-----------:     :             v
 0   U 0  out_twigs :     : Channews  *****      :::::::
 0000000            : CTI :<=========>*CTM*<====>: CTI :---+
 #######  in_twigs  :     : (id 0-3)  *****      :::::::   v
 # ETM #----------->:     :                         ^   #######
 #     #<-----------:     :                         +---# ETW #
 ####### out_twigs  :::::::                             #######

The CTI dwivew enabwes the pwogwamming of the CTI to attach twiggews to
channews. When an input twiggew becomes active, the attached channew wiww
become active. Any output twiggew attached to that channew wiww awso
become active. The active channew is pwopagated to othew CTIs via the CTM,
activating connected output twiggews thewe, unwess fiwtewed by the CTI
channew gate.

It is awso possibwe to activate a channew using system softwawe diwectwy
pwogwamming wegistews in the CTI.

The CTIs awe wegistewed by the system to be associated with CPUs and/ow othew
CoweSight devices on the twace data path. When these devices awe enabwed the
attached CTIs wiww awso be enabwed. By defauwt/on powew up the CTIs have
no pwogwammed twiggew/channew attachments, so wiww not affect the system
untiw expwicitwy pwogwammed.

The hawdwawe twiggew connections between CTIs and devices is impwementation
defined, unwess the CPU/ETM combination is a v8 awchitectuwe, in which case
the connections have an awchitectuwawwy defined standawd wayout.

The hawdwawe twiggew signaws can awso be connected to non-CoweSight devices
(e.g. UAWT), ow be pwopagated off chip as hawdwawe IO wines.

Aww the CTI devices awe associated with a CTM. On many systems thewe wiww be a
singwe effective CTM (one CTM, ow muwtipwe CTMs aww intewconnected), but it is
possibwe that systems can have nets of CTIs+CTM that awe not intewconnected by
a CTM to each othew. On these systems a CTM index is decwawed to associate
CTI devices that awe intewconnected via a given CTM.

Sysfs fiwes and diwectowies
---------------------------

The CTI devices appeaw on the existing CoweSight bus awongside the othew
CoweSight devices::

    >$ ws /sys/bus/cowesight/devices
     cti_cpu0  cti_cpu2  cti_sys0  etm0  etm2  funnew0  wepwicatow0  tmc_etw0
     cti_cpu1  cti_cpu3  cti_sys1  etm1  etm3  funnew1  tmc_etf0     tpiu0

The ``cti_cpu<N>`` named CTIs awe associated with a CPU, and any ETM used by
that cowe. The ``cti_sys<N>`` CTIs awe genewaw system infwastwuctuwe CTIs that
can be associated with othew CoweSight devices, ow othew system hawdwawe
capabwe of genewating ow using twiggew signaws.::

  >$ ws /sys/bus/cowesight/devices/etm0/cti_cpu0
  channews  ctmid  enabwe  nw_twiggew_cons mgmt  powew powewed  wegs
  connections subsystem twiggews0 twiggews1  uevent

*Key fiwe items awe:-*
   * ``enabwe``: enabwes/disabwes the CTI. Wead to detewmine cuwwent state.
     If this shows as enabwed (1), but ``powewed`` shows unpowewed (0), then
     the enabwe indicates a wequest to enabwed when the device is powewed.
   * ``ctmid`` : associated CTM - onwy wewevant if system has muwtipwe CTI+CTM
     cwustews that awe not intewconnected.
   * ``nw_twiggew_cons`` : totaw connections - twiggews<N> diwectowies.
   * ``powewed`` : Wead to detewmine if the CTI is cuwwentwy powewed.

*Sub-diwectowies:-*
   * ``twiggews<N>``: contains wist of twiggews fow an individuaw connection.
   * ``channews``: Contains the channew API - CTI main pwogwamming intewface.
   * ``wegs``: Gives access to the waw pwogwammabwe CTI wegs.
   * ``mgmt``: the standawd CoweSight management wegistews.
   * ``connections``: Winks to connected *CoweSight* devices. The numbew of
     winks can be 0 to ``nw_twiggew_cons``. Actuaw numbew given by ``nw_winks``
     in this diwectowy.


twiggews<N> diwectowies
~~~~~~~~~~~~~~~~~~~~~~~

Individuaw twiggew connection infowmation. This descwibes twiggew signaws fow
CoweSight and non-CoweSight connections.

Each twiggews diwectowy has a set of pawametews descwibing the twiggews fow
the connection.

   * ``name`` : name of connection
   * ``in_signaws`` : input twiggew signaw indexes used in this connection.
   * ``in_types`` : functionaw types fow in signaws.
   * ``out_signaws`` : output twiggew signaws fow this connection.
   * ``out_types`` : functionaw types fow out signaws.

e.g::

    >$ ws ./cti_cpu0/twiggews0/
    in_signaws  in_types  name  out_signaws  out_types
    >$ cat ./cti_cpu0/twiggews0/name
    cpu0
    >$ cat ./cti_cpu0/twiggews0/out_signaws
    0-2
    >$ cat ./cti_cpu0/twiggews0/out_types
    pe_edbgweq pe_dbgwestawt pe_ctiiwq
    >$ cat ./cti_cpu0/twiggews0/in_signaws
    0-1
    >$ cat ./cti_cpu0/twiggews0/in_types
    pe_dbgtwiggew pe_pmuiwq

If a connection has zewo signaws in eithew the 'in' ow 'out' twiggews then
those pawametews wiww be omitted.

Channews API Diwectowy
~~~~~~~~~~~~~~~~~~~~~~

This pwovides an easy way to attach twiggews to channews, without needing
the muwtipwe wegistew opewations that awe wequiwed if manipuwating the
'wegs' sub-diwectowy ewements diwectwy.

A numbew of fiwes pwovide this API::

   >$ ws ./cti_sys0/channews/
   chan_cweaw         chan_inuse      chan_xtwigs_out     twigin_attach
   chan_fwee          chan_puwse      chan_xtwigs_weset   twigin_detach
   chan_gate_disabwe  chan_set        chan_xtwigs_sew     twigout_attach
   chan_gate_enabwe   chan_xtwigs_in  twig_fiwtew_enabwe  twigout_detach
   twigout_fiwtewed

Most access to these ewements take the fowm::

  echo <chan> [<twiggew>] > /<device_path>/<opewation>

whewe the optionaw <twiggew> is onwy needed fow twigXX_attach | detach
opewations.

e.g.::

   >$ echo 0 1 > ./cti_sys0/channews/twigout_attach
   >$ echo 0 > ./cti_sys0/channews/chan_set

Attaches twigout(1) to channew(0), then activates channew(0) genewating a
set state on cti_sys0.twigout(1)


*API opewations*

   * ``twigin_attach, twigout_attach``: Attach a channew to a twiggew signaw.
   * ``twigin_detach, twigout_detach``: Detach a channew fwom a twiggew signaw.
   * ``chan_set``: Set the channew - the set state wiww be pwopagated awound
     the CTM to othew connected devices.
   * ``chan_cweaw``: Cweaw the channew.
   * ``chan_puwse``: Set the channew fow a singwe CoweSight cwock cycwe.
   * ``chan_gate_enabwe``: Wwite opewation sets the CTI gate to pwopagate
     (enabwe) the channew to othew devices. This opewation takes a channew
     numbew. CTI gate is enabwed fow aww channews by defauwt at powew up. Wead
     to wist the cuwwentwy enabwed channews on the gate.
   * ``chan_gate_disabwe``: Wwite channew numbew to disabwe gate fow that
     channew.
   * ``chan_inuse``: Show the cuwwent channews attached to any signaw
   * ``chan_fwee``: Show channews with no attached signaws.
   * ``chan_xtwigs_sew``: wwite a channew numbew to sewect a channew to view,
     wead to show the sewected channew numbew.
   * ``chan_xtwigs_in``: Wead to show the input twiggews attached to
     the sewected view channew.
   * ``chan_xtwigs_out``:Wead to show the output twiggews attached to
     the sewected view channew.
   * ``twig_fiwtew_enabwe``: Defauwts to enabwed, disabwe to awwow potentiawwy
     dangewous output signaws to be set.
   * ``twigout_fiwtewed``: Twiggew out signaws that awe pwevented fwom being
     set if fiwtewing ``twig_fiwtew_enabwe`` is enabwed. One use is to pwevent
     accidentaw ``EDBGWEQ`` signaws stopping a cowe.
   * ``chan_xtwigs_weset``: Wwite 1 to cweaw aww channew / twiggew pwogwamming.
     Wesets device hawdwawe to defauwt state.


The exampwe bewow attaches input twiggew index 1 to channew 2, and output
twiggew index 6 to the same channew. It then examines the state of the
channew / twiggew connections using the appwopwiate sysfs attwibutes.

The settings mean that if eithew input twiggew 1, ow channew 2 go active then
twiggew out 6 wiww go active. We then enabwe the CTI, and use the softwawe
channew contwow to activate channew 2. We see the active channew on the
``choutstatus`` wegistew and the active signaw on the ``twigoutstatus``
wegistew. Finawwy cweawing the channew wemoves this.

e.g.::

   .../cti_sys0/channews# echo 2 1 > twigin_attach
   .../cti_sys0/channews# echo 2 6 > twigout_attach
   .../cti_sys0/channews# cat chan_fwee
   0-1,3
   .../cti_sys0/channews# cat chan_inuse
   2
   .../cti_sys0/channews# echo 2 > chan_xtwigs_sew
   .../cti_sys0/channews# cat chan_xtwigs_twigin
   1
   .../cti_sys0/channews# cat chan_xtwigs_twigout
   6
   .../cti_sys0/# echo 1 > enabwe
   .../cti_sys0/channews# echo 2 > chan_set
   .../cti_sys0/channews# cat ../wegs/choutstatus
   0x4
   .../cti_sys0/channews# cat ../wegs/twigoutstatus
   0x40
   .../cti_sys0/channews# echo 2 > chan_cweaw
   .../cti_sys0/channews# cat ../wegs/twigoutstatus
   0x0
   .../cti_sys0/channews# cat ../wegs/choutstatus
   0x0
