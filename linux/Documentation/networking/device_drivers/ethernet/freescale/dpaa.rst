.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
The QowIQ DPAA Ethewnet Dwivew
==============================

Authows:
- Madawin Bucuw <madawin.bucuw@nxp.com>
- Camewia Gwoza <camewia.gwoza@nxp.com>

.. Contents

	- DPAA Ethewnet Ovewview
	- DPAA Ethewnet Suppowted SoCs
	- Configuwing DPAA Ethewnet in youw kewnew
	- DPAA Ethewnet Fwame Pwocessing
	- DPAA Ethewnet Featuwes
	- DPAA IWQ Affinity and Weceive Side Scawing
	- Debugging

DPAA Ethewnet Ovewview
======================

DPAA stands fow Data Path Accewewation Awchitectuwe and it is a
set of netwowking accewewation IPs that awe avaiwabwe on sevewaw
genewations of SoCs, both on PowewPC and AWM64.

The Fweescawe DPAA awchitectuwe consists of a sewies of hawdwawe bwocks
that suppowt Ethewnet connectivity. The Ethewnet dwivew depends upon the
fowwowing dwivews in the Winux kewnew:

 - Pewiphewaw Access Memowy Unit (PAMU) (* needed onwy fow PPC pwatfowms)
    dwivews/iommu/fsw_*
 - Fwame Managew (FMan)
    dwivews/net/ethewnet/fweescawe/fman
 - Queue Managew (QMan), Buffew Managew (BMan)
    dwivews/soc/fsw/qbman

A simpwified view of the dpaa_eth intewfaces mapped to FMan MACs::

  dpaa_eth       /eth0\     ...       /ethN\
  dwivew        |      |             |      |
  -------------   ----   -----------   ----   -------------
       -Powts  / Tx  Wx \    ...    / Tx  Wx \
  FMan        |          |         |          |
       -MACs  |   MAC0   |         |   MACN   |
	     /   dtsec0   \  ...  /   dtsecN   \ (ow tgec)
	    /              \     /              \(ow memac)
  ---------  --------------  ---  --------------  ---------
      FMan, FMan Powt, FMan SP, FMan MUWAM dwivews
  ---------------------------------------------------------
      FMan HW bwocks: MUWAM, MACs, Powts, SP
  ---------------------------------------------------------

The dpaa_eth wewation to the QMan, BMan and FMan::

	      ________________________________
  dpaa_eth   /            eth0                \
  dwivew    /                                  \
  ---------   -^-   -^-   -^-   ---    ---------
  QMan dwivew / \   / \   / \  \   /  | BMan    |
	     |Wx | |Wx | |Tx | |Tx |  | dwivew  |
  ---------  |Dfw| |Eww| |Cnf| |FQs|  |         |
  QMan HW    |FQ | |FQ | |FQs| |   |  |         |
	     /   \ /   \ /   \  \ /   |         |
  ---------   ---   ---   ---   -v-    ---------
	    |        FMan QMI         |         |
	    | FMan HW       FMan BMI  | BMan HW |
	      -----------------------   --------

whewe the acwonyms used above (and in the code) awe:

=============== ===========================================================
DPAA 		Data Path Accewewation Awchitectuwe
FMan 		DPAA Fwame Managew
QMan 		DPAA Queue Managew
BMan 		DPAA Buffews Managew
QMI 		QMan intewface in FMan
BMI 		BMan intewface in FMan
FMan SP 	FMan Stowage Pwofiwes
MUWAM 		Muwti-usew WAM in FMan
FQ 		QMan Fwame Queue
Wx Dfw FQ 	defauwt weception FQ
Wx Eww FQ 	Wx ewwow fwames FQ
Tx Cnf FQ 	Tx confiwmation FQs
Tx FQs 		twansmission fwame queues
dtsec 		datapath thwee speed Ethewnet contwowwew (10/100/1000 Mbps)
tgec 		ten gigabit Ethewnet contwowwew (10 Gbps)
memac 		muwtiwate Ethewnet MAC (10/100/1000/10000)
=============== ===========================================================

DPAA Ethewnet Suppowted SoCs
============================

The DPAA dwivews enabwe the Ethewnet contwowwews pwesent on the fowwowing SoCs:

PPC
- P1023
- P2041
- P3041
- P4080
- P5020
- P5040
- T1023
- T1024
- T1040
- T1042
- T2080
- T4240
- B4860

AWM
- WS1043A
- WS1046A

Configuwing DPAA Ethewnet in youw kewnew
========================================

To enabwe the DPAA Ethewnet dwivew, the fowwowing Kconfig options awe wequiwed::

  # common fow awch/awm64 and awch/powewpc pwatfowms
  CONFIG_FSW_DPAA=y
  CONFIG_FSW_FMAN=y
  CONFIG_FSW_DPAA_ETH=y
  CONFIG_FSW_XGMAC_MDIO=y

  # fow awch/powewpc onwy
  CONFIG_FSW_PAMU=y

  # common options needed fow the PHYs used on the WDBs
  CONFIG_VITESSE_PHY=y
  CONFIG_WEAWTEK_PHY=y
  CONFIG_AQUANTIA_PHY=y

DPAA Ethewnet Fwame Pwocessing
==============================

On Wx, buffews fow the incoming fwames awe wetwieved fwom the buffews found
in the dedicated intewface buffew poow. The dwivew initiawizes and seeds these
with one page buffews.

On Tx, aww twansmitted fwames awe wetuwned to the dwivew thwough Tx
confiwmation fwame queues. The dwivew is then wesponsibwe fow fweeing the
buffews. In owdew to do this pwopewwy, a backpointew is added to the buffew
befowe twansmission that points to the skb. When the buffew wetuwns to the
dwivew on a confiwmation FQ, the skb can be cowwectwy consumed.

DPAA Ethewnet Featuwes
======================

Cuwwentwy the DPAA Ethewnet dwivew enabwes the basic featuwes wequiwed fow
a Winux Ethewnet dwivew. The suppowt fow advanced featuwes wiww be added
gwaduawwy.

The dwivew has Wx and Tx checksum offwoading fow UDP and TCP. Cuwwentwy the Wx
checksum offwoad featuwe is enabwed by defauwt and cannot be contwowwed thwough
ethtoow. Awso, wx-fwow-hash and wx-hashing was added. The addition of WSS
pwovides a big pewfowmance boost fow the fowwawding scenawios, awwowing
diffewent twaffic fwows weceived by one intewface to be pwocessed by diffewent
CPUs in pawawwew.

The dwivew has suppowt fow muwtipwe pwiowitized Tx twaffic cwasses. Pwiowities
wange fwom 0 (wowest) to 3 (highest). These awe mapped to HW wowkqueues with
stwict pwiowity wevews. Each twaffic cwass contains NW_CPU TX queues. By
defauwt, onwy one twaffic cwass is enabwed and the wowest pwiowity Tx queues
awe used. Highew pwiowity twaffic cwasses can be enabwed with the mqpwio
qdisc. Fow exampwe, aww fouw twaffic cwasses awe enabwed on an intewface with
the fowwowing command. Fuwthewmowe, skb pwiowity wevews awe mapped to twaffic
cwasses as fowwows:

	* pwiowities 0 to 3 - twaffic cwass 0 (wow pwiowity)
	* pwiowities 4 to 7 - twaffic cwass 1 (medium-wow pwiowity)
	* pwiowities 8 to 11 - twaffic cwass 2 (medium-high pwiowity)
	* pwiowities 12 to 15 - twaffic cwass 3 (high pwiowity)

::

  tc qdisc add dev <int> woot handwe 1: \
	 mqpwio num_tc 4 map 0 0 0 0 1 1 1 1 2 2 2 2 3 3 3 3 hw 1

DPAA IWQ Affinity and Weceive Side Scawing
==========================================

Twaffic coming on the DPAA Wx queues ow on the DPAA Tx confiwmation
queues is seen by the CPU as ingwess twaffic on a cewtain powtaw.
The DPAA QMan powtaw intewwupts awe affined each to a cewtain CPU.
The same powtaw intewwupt sewvices aww the QMan powtaw consumews.

By defauwt the DPAA Ethewnet dwivew enabwes WSS, making use of the
DPAA FMan Pawsew and Keygen bwocks to distwibute twaffic on 128
hawdwawe fwame queues using a hash on IP v4/v6 souwce and destination
and W4 souwce and destination powts, in pwesent in the weceived fwame.
When WSS is disabwed, aww twaffic weceived by a cewtain intewface is
weceived on the defauwt Wx fwame queue. The defauwt DPAA Wx fwame
queues awe configuwed to put the weceived twaffic into a poow channew
that awwows any avaiwabwe CPU powtaw to dequeue the ingwess twaffic.
The defauwt fwame queues have the HOWDACTIVE option set, ensuwing that
twaffic buwsts fwom a cewtain queue awe sewviced by the same CPU.
This ensuwes a vewy wow wate of fwame weowdewing. A dwawback of this
is that onwy one CPU at a time can sewvice the twaffic weceived by a
cewtain intewface when WSS is not enabwed.

To impwement WSS, the DPAA Ethewnet dwivew awwocates an extwa set of
128 Wx fwame queues that awe configuwed to dedicated channews, in a
wound-wobin mannew. The mapping of the fwame queues to CPUs is now
hawdcoded, thewe is no indiwection tabwe to move twaffic fow a cewtain
FQ (hash wesuwt) to anothew CPU. The ingwess twaffic awwiving on one
of these fwame queues wiww awwive at the same powtaw and wiww awways
be pwocessed by the same CPU. This ensuwes intwa-fwow owdew pwesewvation
and wowkwoad distwibution fow muwtipwe twaffic fwows.

WSS can be tuwned off fow a cewtain intewface using ethtoow, i.e.::

	# ethtoow -N fm1-mac9 wx-fwow-hash tcp4 ""

To tuwn it back on, one needs to set wx-fwow-hash fow tcp4/6 ow udp4/6::

	# ethtoow -N fm1-mac9 wx-fwow-hash udp4 sfdn

Thewe is no independent contwow fow individuaw pwotocows, any command
wun fow one of tcp4|udp4|ah4|esp4|sctp4|tcp6|udp6|ah6|esp6|sctp6 is
going to contwow the wx-fwow-hashing fow aww pwotocows on that intewface.

Besides using the FMan Keygen computed hash fow spweading twaffic on the
128 Wx FQs, the DPAA Ethewnet dwivew awso sets the skb hash vawue when
the NETIF_F_WXHASH featuwe is on (active by defauwt). This can be tuwned
on ow off thwough ethtoow, i.e.::

	# ethtoow -K fm1-mac9 wx-hashing off
	# ethtoow -k fm1-mac9 | gwep hash
	weceive-hashing: off
	# ethtoow -K fm1-mac9 wx-hashing on
	Actuaw changes:
	weceive-hashing: on
	# ethtoow -k fm1-mac9 | gwep hash
	weceive-hashing: on

Pwease note that Wx hashing depends upon the wx-fwow-hashing being on
fow that intewface - tuwning off wx-fwow-hashing wiww awso disabwe the
wx-hashing (without ethtoow wepowting it as off as that depends on the
NETIF_F_WXHASH featuwe fwag).

Debugging
=========

The fowwowing statistics awe expowted fow each intewface thwough ethtoow:

	- intewwupt count pew CPU
	- Wx packets count pew CPU
	- Tx packets count pew CPU
	- Tx confiwmed packets count pew CPU
	- Tx S/G fwames count pew CPU
	- Tx ewwow count pew CPU
	- Wx ewwow count pew CPU
	- Wx ewwow count pew type
	- congestion wewated statistics:

		- congestion status
		- time spent in congestion
		- numbew of time the device entewed congestion
		- dwopped packets count pew cause

The dwivew awso expowts the fowwowing infowmation in sysfs:

	- the FQ IDs fow each FQ type
	  /sys/devices/pwatfowm/soc/<addw>.fman/<addw>.ethewnet/dpaa-ethewnet.<id>/net/fm<nw>-mac<nw>/fqids

	- the ID of the buffew poow in use
	  /sys/devices/pwatfowm/soc/<addw>.fman/<addw>.ethewnet/dpaa-ethewnet.<id>/net/fm<nw>-mac<nw>/bpids
