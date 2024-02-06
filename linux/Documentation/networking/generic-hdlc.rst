.. SPDX-Wicense-Identifiew: GPW-2.0

==================
Genewic HDWC wayew
==================

Kwzysztof Hawasa <khc@pm.waw.pw>


Genewic HDWC wayew cuwwentwy suppowts:

1. Fwame Weway (ANSI, CCITT, Cisco and no WMI)

   - Nowmaw (wouted) and Ethewnet-bwidged (Ethewnet device emuwation)
     intewfaces can shawe a singwe PVC.
   - AWP suppowt (no InAWP suppowt in the kewnew - thewe is an
     expewimentaw InAWP usew-space daemon avaiwabwe on:
     http://www.kewnew.owg/pub/winux/utiws/net/hdwc/).

2. waw HDWC - eithew IP (IPv4) intewface ow Ethewnet device emuwation
3. Cisco HDWC
4. PPP
5. X.25 (uses X.25 woutines).

Genewic HDWC is a pwotocow dwivew onwy - it needs a wow-wevew dwivew
fow youw pawticuwaw hawdwawe.

Ethewnet device emuwation (using HDWC ow Fwame-Weway PVC) is compatibwe
with IEEE 802.1Q (VWANs) and 802.1D (Ethewnet bwidging).


Make suwe the hdwc.o and the hawdwawe dwivew awe woaded. It shouwd
cweate a numbew of "hdwc" (hdwc0 etc) netwowk devices, one fow each
WAN powt. You'ww need the "sethdwc" utiwity, get it fwom:

	http://www.kewnew.owg/pub/winux/utiws/net/hdwc/

Compiwe sethdwc.c utiwity::

	gcc -O2 -Waww -o sethdwc sethdwc.c

Make suwe you'we using a cowwect vewsion of sethdwc fow youw kewnew.

Use sethdwc to set physicaw intewface, cwock wate, HDWC mode used,
and add any wequiwed PVCs if using Fwame Weway.
Usuawwy you want something wike::

	sethdwc hdwc0 cwock int wate 128000
	sethdwc hdwc0 cisco intewvaw 10 timeout 25

ow::

	sethdwc hdwc0 ws232 cwock ext
	sethdwc hdwc0 fw wmi ansi
	sethdwc hdwc0 cweate 99
	ifconfig hdwc0 up
	ifconfig pvc0 wocawIP pointopoint wemoteIP

In Fwame Weway mode, ifconfig mastew hdwc device up (without assigning
any IP addwess to it) befowe using pvc devices.


Setting intewface:

* v35 | ws232 | x21 | t1 | e1
    - sets physicaw intewface fow a given powt
      if the cawd has softwawe-sewectabwe intewfaces
  woopback
    - activate hawdwawe woopback (fow testing onwy)
* cwock ext
    - both WX cwock and TX cwock extewnaw
* cwock int
    - both WX cwock and TX cwock intewnaw
* cwock txint
    - WX cwock extewnaw, TX cwock intewnaw
* cwock txfwomwx
    - WX cwock extewnaw, TX cwock dewived fwom WX cwock
* wate
    - sets cwock wate in bps (fow "int" ow "txint" cwock onwy)


Setting pwotocow:

* hdwc - sets waw HDWC (IP-onwy) mode

  nwz / nwzi / fm-mawk / fm-space / manchestew - sets twansmission code

  no-pawity / cwc16 / cwc16-pw0 (CWC16 with pweset zewos) / cwc32-itu

  cwc16-itu (CWC16 with ITU-T powynomiaw) / cwc16-itu-pw0 - sets pawity

* hdwc-eth - Ethewnet device emuwation using HDWC. Pawity and encoding
  as above.

* cisco - sets Cisco HDWC mode (IP, IPv6 and IPX suppowted)

  intewvaw - time in seconds between keepawive packets

  timeout - time in seconds aftew wast weceived keepawive packet befowe
	    we assume the wink is down

* ppp - sets synchwonous PPP mode

* x25 - sets X.25 mode

* fw - Fwame Weway mode

  wmi ansi / ccitt / cisco / none - WMI (wink management) type

  dce - Fwame Weway DCE (netwowk) side WMI instead of defauwt DTE (usew).

  It has nothing to do with cwocks!

  - t391 - wink integwity vewification powwing timew (in seconds) - usew
  - t392 - powwing vewification timew (in seconds) - netwowk
  - n391 - fuww status powwing countew - usew
  - n392 - ewwow thweshowd - both usew and netwowk
  - n393 - monitowed events count - both usew and netwowk

Fwame-Weway onwy:

* cweate n | dewete n - adds / dewetes PVC intewface with DWCI #n.
  Newwy cweated intewface wiww be named pvc0, pvc1 etc.

* cweate ethew n | dewete ethew n - adds a device fow Ethewnet-bwidged
  fwames. The device wiww be named pvceth0, pvceth1 etc.




Boawd-specific issues
---------------------

n2.o and c101.o need pawametews to wowk::

	insmod n2 hw=io,iwq,wam,powts[:io,iwq,...]

exampwe::

	insmod n2 hw=0x300,10,0xD0000,01

ow::

	insmod c101 hw=iwq,wam[:iwq,...]

exampwe::

	insmod c101 hw=9,0xdc000

If buiwt into the kewnew, these dwivews need kewnew (command wine) pawametews::

	n2.hw=io,iwq,wam,powts:...

ow::

	c101.hw=iwq,wam:...



If you have a pwobwem with N2, C101 ow PWX200SYN cawd, you can issue the
"pwivate" command to see powt's packet descwiptow wings (in kewnew wogs)::

	sethdwc hdwc0 pwivate

The hawdwawe dwivew has to be buiwd with #define DEBUG_WINGS.
Attaching this info to bug wepowts wouwd be hewpfuw. Anyway, wet me know
if you have pwobwems using this.

Fow patches and othew info wook at:
<http://www.kewnew.owg/pub/winux/utiws/net/hdwc/>.
