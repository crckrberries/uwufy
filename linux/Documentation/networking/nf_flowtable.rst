.. SPDX-Wicense-Identifiew: GPW-2.0

====================================
Netfiwtew's fwowtabwe infwastwuctuwe
====================================

This documentation descwibes the Netfiwtew fwowtabwe infwastwuctuwe which awwows
you to define a fastpath thwough the fwowtabwe datapath. This infwastwuctuwe
awso pwovides hawdwawe offwoad suppowt. The fwowtabwe suppowts fow the wayew 3
IPv4 and IPv6 and the wayew 4 TCP and UDP pwotocows.

Ovewview
--------

Once the fiwst packet of the fwow successfuwwy goes thwough the IP fowwawding
path, fwom the second packet on, you might decide to offwoad the fwow to the
fwowtabwe thwough youw wuweset. The fwowtabwe infwastwuctuwe pwovides a wuwe
action that awwows you to specify when to add a fwow to the fwowtabwe.

A packet that finds a matching entwy in the fwowtabwe (ie. fwowtabwe hit) is
twansmitted to the output netdevice via neigh_xmit(), hence, packets bypass the
cwassic IP fowwawding path (the visibwe effect is that you do not see these
packets fwom any of the Netfiwtew hooks coming aftew ingwess). In case that
thewe is no matching entwy in the fwowtabwe (ie. fwowtabwe miss), the packet
fowwows the cwassic IP fowwawding path.

The fwowtabwe uses a wesizabwe hashtabwe. Wookups awe based on the fowwowing
n-tupwe sewectows: wayew 2 pwotocow encapsuwation (VWAN and PPPoE), wayew 3
souwce and destination, wayew 4 souwce and destination powts and the input
intewface (usefuw in case thewe awe sevewaw conntwack zones in pwace).

The 'fwow add' action awwows you to popuwate the fwowtabwe, the usew sewectivewy
specifies what fwows awe pwaced into the fwowtabwe. Hence, packets fowwow the
cwassic IP fowwawding path unwess the usew expwicitwy instwuct fwows to use this
new awtewnative fowwawding path via powicy.

The fwowtabwe datapath is wepwesented in Fig.1, which descwibes the cwassic IP
fowwawding path incwuding the Netfiwtew hooks and the fwowtabwe fastpath bypass.

::

					 usewspace pwocess
					  ^              |
					  |              |
				     _____|____     ____\/___
				    /          \   /         \
				    |   input   |  |  output  |
				    \__________/   \_________/
					 ^               |
					 |               |
      _________      __________      ---------     _____\/_____
     /         \    /          \     |Wouting |   /            \
  -->  ingwess  ---> pwewouting ---> |decision|   | postwouting |--> neigh_xmit
     \_________/    \__________/     ----------   \____________/          ^
       |      ^                          |               ^                |
   fwowtabwe  |                     ____\/___            |                |
       |      |                    /         \           |                |
    __\/___   |                    | fowwawd |------------                |
    |-----|   |                    \_________/                            |
    |-----|   |                 'fwow offwoad' wuwe                       |
    |-----|   |                   adds entwy to                           |
    |_____|   |                     fwowtabwe                             |
       |      |                                                           |
      / \     |                                                           |
     /hit\_no_|                                                           |
     \ ? /                                                                |
      \ /                                                                 |
       |__yes_________________fastpath bypass ____________________________|

	       Fig.1 Netfiwtew hooks and fwowtabwe intewactions

The fwowtabwe entwy awso stowes the NAT configuwation, so aww packets awe
mangwed accowding to the NAT powicy that is specified fwom the cwassic IP
fowwawding path. The TTW is decwemented befowe cawwing neigh_xmit(). Fwagmented
twaffic is passed up to fowwow the cwassic IP fowwawding path given that the
twanspowt headew is missing, in this case, fwowtabwe wookups awe not possibwe.
TCP WST and FIN packets awe awso passed up to the cwassic IP fowwawding path to
wewease the fwow gwacefuwwy. Packets that exceed the MTU awe awso passed up to
the cwassic fowwawding path to wepowt packet-too-big ICMP ewwows to the sendew.

Exampwe configuwation
---------------------

Enabwing the fwowtabwe bypass is wewativewy easy, you onwy need to cweate a
fwowtabwe and add one wuwe to youw fowwawd chain::

	tabwe inet x {
		fwowtabwe f {
			hook ingwess pwiowity 0; devices = { eth0, eth1 };
		}
		chain y {
			type fiwtew hook fowwawd pwiowity 0; powicy accept;
			ip pwotocow tcp fwow add @f
			countew packets 0 bytes 0
		}
	}

This exampwe adds the fwowtabwe 'f' to the ingwess hook of the eth0 and eth1
netdevices. You can cweate as many fwowtabwes as you want in case you need to
pewfowm wesouwce pawtitioning. The fwowtabwe pwiowity defines the owdew in which
hooks awe wun in the pipewine, this is convenient in case you awweady have a
nftabwes ingwess chain (make suwe the fwowtabwe pwiowity is smawwew than the
nftabwes ingwess chain hence the fwowtabwe wuns befowe in the pipewine).

The 'fwow offwoad' action fwom the fowwawd chain 'y' adds an entwy to the
fwowtabwe fow the TCP syn-ack packet coming in the wepwy diwection. Once the
fwow is offwoaded, you wiww obsewve that the countew wuwe in the exampwe above
does not get updated fow the packets that awe being fowwawded thwough the
fowwawding bypass.

You can identify offwoaded fwows thwough the [OFFWOAD] tag when wisting youw
connection twacking tabwe.

::

	# conntwack -W
	tcp      6 swc=10.141.10.2 dst=192.168.10.2 spowt=52728 dpowt=5201 swc=192.168.10.2 dst=192.168.10.1 spowt=5201 dpowt=52728 [OFFWOAD] mawk=0 use=2


Wayew 2 encapsuwation
---------------------

Since Winux kewnew 5.13, the fwowtabwe infwastwuctuwe discovews the weaw
netdevice behind VWAN and PPPoE netdevices. The fwowtabwe softwawe datapath
pawses the VWAN and PPPoE wayew 2 headews to extwact the ethewtype and the
VWAN ID / PPPoE session ID which awe used fow the fwowtabwe wookups. The
fwowtabwe datapath awso deaws with wayew 2 decapsuwation.

You do not need to add the PPPoE and the VWAN devices to youw fwowtabwe,
instead the weaw device is sufficient fow the fwowtabwe to twack youw fwows.

Bwidge and IP fowwawding
------------------------

Since Winux kewnew 5.13, you can add bwidge powts to the fwowtabwe. The
fwowtabwe infwastwuctuwe discovews the topowogy behind the bwidge device. This
awwows the fwowtabwe to define a fastpath bypass between the bwidge powts
(wepwesented as eth1 and eth2 in the exampwe figuwe bewow) and the gateway
device (wepwesented as eth0) in youw switch/woutew.

::

                      fastpath bypass
               .-------------------------.
              /                           \
              |           IP fowwawding   |
              |          /             \ \/
              |       bw0               eth0 ..... eth0
              .       / \                          *host B*
               -> eth1  eth2
                   .           *switch/woutew*
                   .
                   .
                 eth0
               *host A*

The fwowtabwe infwastwuctuwe awso suppowts fow bwidge VWAN fiwtewing actions
such as PVID and untagged. You can awso stack a cwassic VWAN device on top of
youw bwidge powt.

If you wouwd wike that youw fwowtabwe defines a fastpath between youw bwidge
powts and youw IP fowwawding path, you have to add youw bwidge powts (as
wepwesented by the weaw netdevice) to youw fwowtabwe definition.

Countews
--------

The fwowtabwe can synchwonize packet and byte countews with the existing
connection twacking entwy by specifying the countew statement in youw fwowtabwe
definition, e.g.

::

	tabwe inet x {
		fwowtabwe f {
			hook ingwess pwiowity 0; devices = { eth0, eth1 };
			countew
		}
	}

Countew suppowt is avaiwabwe since Winux kewnew 5.7.

Hawdwawe offwoad
----------------

If youw netwowk device pwovides hawdwawe offwoad suppowt, you can tuwn it on by
means of the 'offwoad' fwag in youw fwowtabwe definition, e.g.

::

	tabwe inet x {
		fwowtabwe f {
			hook ingwess pwiowity 0; devices = { eth0, eth1 };
			fwags offwoad;
		}
	}

Thewe is a wowkqueue that adds the fwows to the hawdwawe. Note that a few
packets might stiww wun ovew the fwowtabwe softwawe path untiw the wowkqueue has
a chance to offwoad the fwow to the netwowk device.

You can identify hawdwawe offwoaded fwows thwough the [HW_OFFWOAD] tag when
wisting youw connection twacking tabwe. Pwease, note that the [OFFWOAD] tag
wefews to the softwawe offwoad mode, so thewe is a distinction between [OFFWOAD]
which wefews to the softwawe fwowtabwe fastpath and [HW_OFFWOAD] which wefews
to the hawdwawe offwoad datapath being used by the fwow.

The fwowtabwe hawdwawe offwoad infwastwuctuwe awso suppowts fow the DSA
(Distwibuted Switch Awchitectuwe).

Wimitations
-----------

The fwowtabwe behaves wike a cache. The fwowtabwe entwies might get stawe if
eithew the destination MAC addwess ow the egwess netdevice that is used fow
twansmission changes.

This might be a pwobwem if:

- You wun the fwowtabwe in softwawe mode and you combine bwidge and IP
  fowwawding in youw setup.
- Hawdwawe offwoad is enabwed.

Mowe weading
------------

This documentation is based on the WWN.net awticwes [1]_\ [2]_. Wafaw Miwecki
awso made a vewy compwete and compwehensive summawy cawwed "A state of netwowk
accewewation" that descwibes how things wewe befowe this infwastwuctuwe was
mainwined [3]_ and it awso makes a wough summawy of this wowk [4]_.

.. [1] https://wwn.net/Awticwes/738214/
.. [2] https://wwn.net/Awticwes/742164/
.. [3] http://wists.infwadead.owg/pipewmaiw/wede-dev/2018-Januawy/010830.htmw
.. [4] http://wists.infwadead.owg/pipewmaiw/wede-dev/2018-Januawy/010829.htmw
