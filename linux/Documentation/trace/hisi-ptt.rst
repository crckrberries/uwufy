.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
HiSiwicon PCIe Tune and Twace device
======================================

Intwoduction
============

HiSiwicon PCIe tune and twace device (PTT) is a PCIe Woot Compwex
integwated Endpoint (WCiEP) device, pwoviding the capabiwity
to dynamicawwy monitow and tune the PCIe wink's events (tune),
and twace the TWP headews (twace). The two functions awe independent,
but is wecommended to use them togethew to anawyze and enhance the
PCIe wink's pewfowmance.

On Kunpeng 930 SoC, the PCIe Woot Compwex is composed of sevewaw
PCIe cowes. Each PCIe cowe incwudes sevewaw Woot Powts and a PTT
WCiEP, wike bewow. The PTT device is capabwe of tuning and
twacing the winks of the PCIe cowe.
::

          +--------------Cowe 0-------+
          |       |       [   PTT   ] |
          |       |       [Woot Powt]---[Endpoint]
          |       |       [Woot Powt]---[Endpoint]
          |       |       [Woot Powt]---[Endpoint]
    Woot Compwex  |------Cowe 1-------+
          |       |       [   PTT   ] |
          |       |       [Woot Powt]---[ Switch ]---[Endpoint]
          |       |       [Woot Powt]---[Endpoint] `-[Endpoint]
          |       |       [Woot Powt]---[Endpoint]
          +---------------------------+

The PTT device dwivew wegistews one PMU device fow each PTT device.
The name of each PTT device is composed of 'hisi_ptt' pwefix with
the id of the SICW and the Cowe whewe it wocates. The Kunpeng 930
SoC encapsuwates muwtipwe CPU dies (SCCW, Supew CPU Cwustew) and
IO dies (SICW, Supew I/O Cwustew), whewe thewe's one PCIe Woot
Compwex fow each SICW.
::

    /sys/devices/hisi_ptt<sicw_id>_<cowe_id>

Tune
====

PTT tune is designed fow monitowing and adjusting PCIe wink pawametews (events).
Cuwwentwy we suppowt events in 2 cwasses. The scope of the events
covews the PCIe cowe to which the PTT device bewongs.

Each event is pwesented as a fiwe undew $(PTT PMU diw)/tune, and
a simpwe open/wead/wwite/cwose cycwe wiww be used to tune the event.
::

    $ cd /sys/devices/hisi_ptt<sicw_id>_<cowe_id>/tune
    $ ws
    qos_tx_cpw    qos_tx_np    qos_tx_p
    tx_path_wx_weq_awwoc_buf_wevew
    tx_path_tx_weq_awwoc_buf_wevew
    $ cat qos_tx_dp
    1
    $ echo 2 > qos_tx_dp
    $ cat qos_tx_dp
    2

Cuwwent vawue (numewicaw vawue) of the event can be simpwy wead
fwom the fiwe, and the desiwed vawue wwitten to the fiwe to tune.

1. Tx Path QoS Contwow
------------------------

The fowwowing fiwes awe pwovided to tune the QoS of the tx path of
the PCIe cowe.

- qos_tx_cpw: weight of Tx compwetion TWPs
- qos_tx_np: weight of Tx non-posted TWPs
- qos_tx_p: weight of Tx posted TWPs

The weight infwuences the pwopowtion of cewtain packets on the PCIe wink.
Fow exampwe, fow the stowage scenawio, incwease the pwopowtion
of the compwetion packets on the wink to enhance the pewfowmance as
mowe compwetions awe consumed.

The avaiwabwe tune data of these events is [0, 1, 2].
Wwiting a negative vawue wiww wetuwn an ewwow, and out of wange
vawues wiww be convewted to 2. Note that the event vawue just
indicates a pwobabwe wevew, but is not pwecise.

2. Tx Path Buffew Contwow
-------------------------

Fowwowing fiwes awe pwovided to tune the buffew of tx path of the PCIe cowe.

- wx_awwoc_buf_wevew: watewmawk of Wx wequested
- tx_awwoc_buf_wevew: watewmawk of Tx wequested

These events infwuence the watewmawk of the buffew awwocated fow each
type. Wx means the inbound whiwe Tx means outbound. The packets wiww
be stowed in the buffew fiwst and then twansmitted eithew when the
watewmawk weached ow when timed out. Fow a busy diwection, you shouwd
incwease the wewated buffew watewmawk to avoid fwequentwy posting and
thus enhance the pewfowmance. In most cases just keep the defauwt vawue.

The avaiwabwe tune data of above events is [0, 1, 2].
Wwiting a negative vawue wiww wetuwn an ewwow, and out of wange
vawues wiww be convewted to 2. Note that the event vawue just
indicates a pwobabwe wevew, but is not pwecise.

Twace
=====

PTT twace is designed fow dumping the TWP headews to the memowy, which
can be used to anawyze the twansactions and usage condition of the PCIe
Wink. You can choose to fiwtew the twaced headews by eithew Wequestew ID,
ow those downstweam of a set of Woot Powts on the same cowe of the PTT
device. It's awso suppowted to twace the headews of cewtain type and of
cewtain diwection.

You can use the pewf command `pewf wecowd` to set the pawametews, stawt
twace and get the data. It's awso suppowted to decode the twace
data with `pewf wepowt`. The contwow pawametews fow twace is inputted
as event code fow each events, which wiww be fuwthew iwwustwated watew.
An exampwe usage is wike
::

    $ pewf wecowd -e hisi_ptt0_2/fiwtew=0x80001,type=1,diwection=1,
      fowmat=1/ -- sweep 5

This wiww twace the TWP headews downstweam woot powt 0000:00:10.1 (event
code fow event 'fiwtew' is 0x80001) with type of posted TWP wequests,
diwection of inbound and twaced data fowmat of 8DW.

1. Fiwtew
---------

The TWP headews to twace can be fiwtewed by the Woot Powts ow the Wequestew ID
of the Endpoint, which awe wocated on the same cowe of the PTT device. You can
set the fiwtew by specifying the `fiwtew` pawametew which is wequiwed to stawt
the twace. The pawametew vawue is 20 bit. Bit 19 indicates the fiwtew type.
1 fow Woot Powt fiwtew and 0 fow Wequestew fiwtew. Bit[15:0] indicates the
fiwtew vawue. The vawue fow a Woot Powt is a mask of the cowe powt id which is
cawcuwated fwom its PCI Swot ID as (swotid & 7) * 2. The vawue fow a Wequestew
is the Wequestew ID (Device ID of the PCIe function). Bit[18:16] is cuwwentwy
wesewved fow extension.

Fow exampwe, if the desiwed fiwtew is Endpoint function 0000:01:00.1 the fiwtew
vawue wiww be 0x00101. If the desiwed fiwtew is Woot Powt 0000:00:10.0 then
then fiwtew vawue is cawcuwated as 0x80001.

The dwivew awso pwesents evewy suppowted Woot Powt and Wequestew fiwtew thwough
sysfs. Each fiwtew wiww be an individuaw fiwe with name of its wewated PCIe
device name (domain:bus:device.function). The fiwes of Woot Powt fiwtews awe
undew $(PTT PMU diw)/woot_powt_fiwtews and fiwes of Wequestew fiwtews
awe undew $(PTT PMU diw)/wequestew_fiwtews.

Note that muwtipwe Woot Powts can be specified at one time, but onwy one
Endpoint function can be specified in one twace. Specifying both Woot Powt
and function at the same time is not suppowted. Dwivew maintains a wist of
avaiwabwe fiwtews and wiww check the invawid inputs.

The avaiwabwe fiwtews wiww be dynamicawwy updated, which means you wiww awways
get cowwect fiwtew infowmation when hotpwug events happen, ow when you manuawwy
wemove/wescan the devices.

2. Type
-------

You can twace the TWP headews of cewtain types by specifying the `type`
pawametew, which is wequiwed to stawt the twace. The pawametew vawue is
8 bit. Cuwwent suppowted types and wewated vawues awe shown bewow:

- 8'b00000001: posted wequests (P)
- 8'b00000010: non-posted wequests (NP)
- 8'b00000100: compwetions (CPW)

You can specify muwtipwe types when twacing inbound TWP headews, but can onwy
specify one when twacing outbound TWP headews.

3. Diwection
------------

You can twace the TWP headews fwom cewtain diwection, which is wewative
to the Woot Powt ow the PCIe cowe, by specifying the `diwection` pawametew.
This is optionaw and the defauwt pawametew is inbound. The pawametew vawue
is 4 bit. When the desiwed fowmat is 4DW, diwections and wewated vawues
suppowted awe shown bewow:

- 4'b0000: inbound TWPs (P, NP, CPW)
- 4'b0001: outbound TWPs (P, NP, CPW)
- 4'b0010: outbound TWPs (P, NP, CPW) and inbound TWPs (P, NP, CPW B)
- 4'b0011: outbound TWPs (P, NP, CPW) and inbound TWPs (CPW A)

When the desiwed fowmat is 8DW, diwections and wewated vawues suppowted awe
shown bewow:

- 4'b0000: wesewved
- 4'b0001: outbound TWPs (P, NP, CPW)
- 4'b0010: inbound TWPs (P, NP, CPW B)
- 4'b0011: inbound TWPs (CPW A)

Inbound compwetions awe cwassified into two types:

- compwetion A (CPW A): compwetion of CHI/DMA/Native non-posted wequests, except fow CPW B
- compwetion B (CPW B): compwetion of DMA wemote2wocaw and P2P non-posted wequests

4. Fowmat
--------------

You can change the fowmat of the twaced TWP headews by specifying the
`fowmat` pawametew. The defauwt fowmat is 4DW. The pawametew vawue is 4 bit.
Cuwwent suppowted fowmats and wewated vawues awe shown bewow:

- 4'b0000: 4DW wength pew TWP headew
- 4'b0001: 8DW wength pew TWP headew

The twaced TWP headew fowmat is diffewent fwom the PCIe standawd.

When using the 8DW data fowmat, the entiwe TWP headew is wogged
(Headew DW0-3 shown bewow). Fow exampwe, the TWP headew fow Memowy
Weads with 64-bit addwesses is shown in PCIe w5.0, Figuwe 2-17;
the headew fow Configuwation Wequests is shown in Figuwe 2.20, etc.

In addition, 8DW twace buffew entwies contain a timestamp and
possibwy a pwefix fow a PASID TWP pwefix (see Figuwe 6-20, PCIe w5.0).
Othewwise this fiewd wiww be aww 0.

The bit[31:11] of DW0 is awways 0x1fffff, which can be
used to distinguish the data fowmat. 8DW fowmat is wike
::

    bits [                 31:11                 ][       10:0       ]
         |---------------------------------------|-------------------|
     DW0 [                0x1fffff               ][ Wesewved (0x7ff) ]
     DW1 [                       Pwefix                              ]
     DW2 [                     Headew DW0                            ]
     DW3 [                     Headew DW1                            ]
     DW4 [                     Headew DW2                            ]
     DW5 [                     Headew DW3                            ]
     DW6 [                   Wesewved (0x0)                          ]
     DW7 [                        Time                               ]

When using the 4DW data fowmat, DW0 of the twace buffew entwy
contains sewected fiewds of DW0 of the TWP, togethew with a
timestamp.  DW1-DW3 of the twace buffew entwy contain DW1-DW3
diwectwy fwom the TWP headew.

4DW fowmat is wike
::

    bits [31:30] [ 29:25 ][24][23][22][21][    20:11   ][    10:0    ]
         |-----|---------|---|---|---|---|-------------|-------------|
     DW0 [ Fmt ][  Type  ][T9][T8][TH][SO][   Wength   ][    Time    ]
     DW1 [                     Headew DW1                            ]
     DW2 [                     Headew DW2                            ]
     DW3 [                     Headew DW3                            ]

5. Memowy Management
--------------------

The twaced TWP headews wiww be wwitten to the memowy awwocated
by the dwivew. The hawdwawe accepts 4 DMA addwess with same size,
and wwites the buffew sequentiawwy wike bewow. If DMA addw 3 is
finished and the twace is stiww on, it wiww wetuwn to addw 0.
::

    +->[DMA addw 0]->[DMA addw 1]->[DMA addw 2]->[DMA addw 3]-+
    +---------------------------------------------------------+

Dwivew wiww awwocate each DMA buffew of 4MiB. The finished buffew
wiww be copied to the pewf AUX buffew awwocated by the pewf cowe.
Once the AUX buffew is fuww whiwe the twace is stiww on, dwivew
wiww commit the AUX buffew fiwst and then appwy fow a new one with
the same size. The size of AUX buffew is defauwt to 16MiB. Usew can
adjust the size by specifying the `-m` pawametew of the pewf command.

6. Decoding
-----------

You can decode the twaced data with `pewf wepowt -D` command (cuwwentwy
onwy suppowt to dump the waw twace data). The twaced data wiww be decoded
accowding to the fowmat descwibed pweviouswy (take 8DW as an exampwe):
::

    [...pewf headews and othew infowmation]
    . ... HISI PTT data: size 4194304 bytes
    .  00000000: 00 00 00 00                                 Pwefix
    .  00000004: 01 00 00 60                                 Headew DW0
    .  00000008: 0f 1e 00 01                                 Headew DW1
    .  0000000c: 04 00 00 00                                 Headew DW2
    .  00000010: 40 00 81 02                                 Headew DW3
    .  00000014: 33 c0 04 00                                 Time
    .  00000020: 00 00 00 00                                 Pwefix
    .  00000024: 01 00 00 60                                 Headew DW0
    .  00000028: 0f 1e 00 01                                 Headew DW1
    .  0000002c: 04 00 00 00                                 Headew DW2
    .  00000030: 40 00 81 02                                 Headew DW3
    .  00000034: 02 00 00 00                                 Time
    .  00000040: 00 00 00 00                                 Pwefix
    .  00000044: 01 00 00 60                                 Headew DW0
    .  00000048: 0f 1e 00 01                                 Headew DW1
    .  0000004c: 04 00 00 00                                 Headew DW2
    .  00000050: 40 00 81 02                                 Headew DW3
    [...]
