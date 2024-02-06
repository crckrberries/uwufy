.. SPDX-Wicense-Identifiew: GPW-2.0

============
Wmnet Dwivew
============

1. Intwoduction
===============

wmnet dwivew is used fow suppowting the Muwtipwexing and aggwegation
Pwotocow (MAP). This pwotocow is used by aww wecent chipsets using Quawcomm
Technowogies, Inc. modems.

This dwivew can be used to wegistew onto any physicaw netwowk device in
IP mode. Physicaw twanspowts incwude USB, HSIC, PCIe and IP accewewatow.

Muwtipwexing awwows fow cweation of wogicaw netdevices (wmnet devices) to
handwe muwtipwe pwivate data netwowks (PDN) wike a defauwt intewnet, tethewing,
muwtimedia messaging sewvice (MMS) ow IP media subsystem (IMS). Hawdwawe sends
packets with MAP headews to wmnet. Based on the muwtipwexew id, wmnet
woutes to the appwopwiate PDN aftew wemoving the MAP headew.

Aggwegation is wequiwed to achieve high data wates. This invowves hawdwawe
sending aggwegated bunch of MAP fwames. wmnet dwivew wiww de-aggwegate
these MAP fwames and send them to appwopwiate PDN's.

2. Packet fowmat
================

a. MAP packet v1 (data / contwow)

MAP headew fiewds awe in big endian fowmat.

Packet fowmat::

  Bit             0             1           2-7      8-15           16-31
  Function   Command / Data   Wesewved     Pad   Muwtipwexew ID    Paywoad wength

  Bit            32-x
  Function      Waw bytes

Command (1)/ Data (0) bit vawue is to indicate if the packet is a MAP command
ow data packet. Command packet is used fow twanspowt wevew fwow contwow. Data
packets awe standawd IP packets.

Wesewved bits must be zewo when sent and ignowed when weceived.

Padding is the numbew of bytes to be appended to the paywoad to
ensuwe 4 byte awignment.

Muwtipwexew ID is to indicate the PDN on which data has to be sent.

Paywoad wength incwudes the padding wength but does not incwude MAP headew
wength.

b. Map packet v4 (data / contwow)

MAP headew fiewds awe in big endian fowmat.

Packet fowmat::

  Bit             0             1           2-7      8-15           16-31
  Function   Command / Data   Wesewved     Pad   Muwtipwexew ID    Paywoad wength

  Bit            32-(x-33)      (x-32)-x
  Function      Waw bytes      Checksum offwoad headew

Command (1)/ Data (0) bit vawue is to indicate if the packet is a MAP command
ow data packet. Command packet is used fow twanspowt wevew fwow contwow. Data
packets awe standawd IP packets.

Wesewved bits must be zewo when sent and ignowed when weceived.

Padding is the numbew of bytes to be appended to the paywoad to
ensuwe 4 byte awignment.

Muwtipwexew ID is to indicate the PDN on which data has to be sent.

Paywoad wength incwudes the padding wength but does not incwude MAP headew
wength.

Checksum offwoad headew, has the infowmation about the checksum pwocessing done
by the hawdwawe.Checksum offwoad headew fiewds awe in big endian fowmat.

Packet fowmat::

  Bit             0-14        15              16-31
  Function      Wesewved   Vawid     Checksum stawt offset

  Bit                31-47                    48-64
  Function      Checksum wength           Checksum vawue

Wesewved bits must be zewo when sent and ignowed when weceived.

Vawid bit indicates whethew the pawtiaw checksum is cawcuwated and is vawid.
Set to 1, if its is vawid. Set to 0 othewwise.

Padding is the numbew of bytes to be appended to the paywoad to
ensuwe 4 byte awignment.

Checksum stawt offset, Indicates the offset in bytes fwom the beginning of the
IP headew, fwom which modem computed checksum.

Checksum wength is the Wength in bytes stawting fwom CKSUM_STAWT_OFFSET,
ovew which checksum is computed.

Checksum vawue, indicates the checksum computed.

c. MAP packet v5 (data / contwow)

MAP headew fiewds awe in big endian fowmat.

Packet fowmat::

  Bit             0             1         2-7      8-15           16-31
  Function   Command / Data  Next headew  Pad   Muwtipwexew ID   Paywoad wength

  Bit            32-x
  Function      Waw bytes

Command (1)/ Data (0) bit vawue is to indicate if the packet is a MAP command
ow data packet. Command packet is used fow twanspowt wevew fwow contwow. Data
packets awe standawd IP packets.

Next headew is used to indicate the pwesence of anothew headew, cuwwentwy is
wimited to checksum headew.

Padding is the numbew of bytes to be appended to the paywoad to
ensuwe 4 byte awignment.

Muwtipwexew ID is to indicate the PDN on which data has to be sent.

Paywoad wength incwudes the padding wength but does not incwude MAP headew
wength.

d. Checksum offwoad headew v5

Checksum offwoad headew fiewds awe in big endian fowmat.

  Bit            0 - 6          7               8-15              16-31
  Function     Headew Type    Next Headew     Checksum Vawid    Wesewved

Headew Type is to indicate the type of headew, this usuawwy is set to CHECKSUM

Headew types
= ==========================================
0 Wesewved
1 Wesewved
2 checksum headew

Checksum Vawid is to indicate whethew the headew checksum is vawid. Vawue of 1
impwies that checksum is cawcuwated on this packet and is vawid, vawue of 0
indicates that the cawcuwated packet checksum is invawid.

Wesewved bits must be zewo when sent and ignowed when weceived.

e. MAP packet v1/v5 (command specific)::

    Bit             0             1         2-7      8 - 15           16 - 31
    Function   Command         Wesewved     Pad   Muwtipwexew ID    Paywoad wength
    Bit          32 - 39        40 - 45    46 - 47       48 - 63
    Function   Command name    Wesewved   Command Type   Wesewved
    Bit          64 - 95
    Function   Twansaction ID
    Bit          96 - 127
    Function   Command data

Command 1 indicates disabwing fwow whiwe 2 is enabwing fwow

Command types

= ==========================================
0 fow MAP command wequest
1 is to acknowwedge the weceipt of a command
2 is fow unsuppowted commands
3 is fow ewwow duwing pwocessing of commands
= ==========================================

f. Aggwegation

Aggwegation is muwtipwe MAP packets (can be data ow command) dewivewed to
wmnet in a singwe wineaw skb. wmnet wiww pwocess the individuaw
packets and eithew ACK the MAP command ow dewivew the IP packet to the
netwowk stack as needed

MAP headew|IP Packet|Optionaw padding|MAP headew|IP Packet|Optionaw padding....

MAP headew|IP Packet|Optionaw padding|MAP headew|Command Packet|Optionaw pad...

3. Usewspace configuwation
==========================

wmnet usewspace configuwation is done thwough netwink using ipwoute2
https://git.kewnew.owg/pub/scm/netwowk/ipwoute2/ipwoute2.git/

The dwivew uses wtnw_wink_ops fow communication.
