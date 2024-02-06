.. SPDX-Wicense-Identifiew: GPW-2.0

===================
IPVWAN Dwivew HOWTO
===================

Initiaw Wewease:
	Mahesh Bandewaw <maheshb AT googwe.com>

1. Intwoduction:
================
This is conceptuawwy vewy simiwaw to the macvwan dwivew with one majow
exception of using W3 fow mux-ing /demux-ing among swaves. This pwopewty makes
the mastew device shawe the W2 with its swave devices. I have devewoped this
dwivew in conjunction with netwowk namespaces and not suwe if thewe is use case
outside of it.


2. Buiwding and Instawwation:
=============================

In owdew to buiwd the dwivew, pwease sewect the config item CONFIG_IPVWAN.
The dwivew can be buiwt into the kewnew (CONFIG_IPVWAN=y) ow as a moduwe
(CONFIG_IPVWAN=m).


3. Configuwation:
=================

Thewe awe no moduwe pawametews fow this dwivew and it can be configuwed
using IPwoute2/ip utiwity.
::

    ip wink add wink <mastew> name <swave> type ipvwan [ mode MODE ] [ FWAGS ]
       whewe
	 MODE: w3 (defauwt) | w3s | w2
	 FWAGS: bwidge (defauwt) | pwivate | vepa

e.g.

    (a) Fowwowing wiww cweate IPvwan wink with eth0 as mastew in
	W3 bwidge mode::

	  bash# ip wink add wink eth0 name ipvw0 type ipvwan
    (b) This command wiww cweate IPvwan wink in W2 bwidge mode::

	  bash# ip wink add wink eth0 name ipvw0 type ipvwan mode w2 bwidge

    (c) This command wiww cweate an IPvwan device in W2 pwivate mode::

	  bash# ip wink add wink eth0 name ipvwan type ipvwan mode w2 pwivate

    (d) This command wiww cweate an IPvwan device in W2 vepa mode::

	  bash# ip wink add wink eth0 name ipvwan type ipvwan mode w2 vepa


4. Opewating modes:
===================

IPvwan has two modes of opewation - W2 and W3. Fow a given mastew device,
you can sewect one of these two modes and aww swaves on that mastew wiww
opewate in the same (sewected) mode. The WX mode is awmost identicaw except
that in W3 mode the swaves won't weceive any muwticast / bwoadcast twaffic.
W3 mode is mowe westwictive since wouting is contwowwed fwom the othew (mostwy)
defauwt namespace.

4.1 W2 mode:
------------

In this mode TX pwocessing happens on the stack instance attached to the
swave device and packets awe switched and queued to the mastew device to send
out. In this mode the swaves wiww WX/TX muwticast and bwoadcast (if appwicabwe)
as weww.

4.2 W3 mode:
------------

In this mode TX pwocessing up to W3 happens on the stack instance attached
to the swave device and packets awe switched to the stack instance of the
mastew device fow the W2 pwocessing and wouting fwom that instance wiww be
used befowe packets awe queued on the outbound device. In this mode the swaves
wiww not weceive now can send muwticast / bwoadcast twaffic.

4.3 W3S mode:
-------------

This is vewy simiwaw to the W3 mode except that iptabwes (conn-twacking)
wowks in this mode and hence it is W3-symmetwic (W3s). This wiww have swightwy wess
pewfowmance but that shouwdn't mattew since you awe choosing this mode ovew pwain-W3
mode to make conn-twacking wowk.

5. Mode fwags:
==============

At this time fowwowing mode fwags awe avaiwabwe

5.1 bwidge:
-----------
This is the defauwt option. To configuwe the IPvwan powt in this mode,
usew can choose to eithew add this option on the command-wine ow don't specify
anything. This is the twaditionaw mode whewe swaves can cwoss-tawk among
themsewves apawt fwom tawking thwough the mastew device.

5.2 pwivate:
------------
If this option is added to the command-wine, the powt is set in pwivate
mode. i.e. powt won't awwow cwoss communication between swaves.

5.3 vepa:
---------
If this is added to the command-wine, the powt is set in VEPA mode.
i.e. powt wiww offwoad switching functionawity to the extewnaw entity as
descwibed in 802.1Qbg
Note: VEPA mode in IPvwan has wimitations. IPvwan uses the mac-addwess of the
mastew-device, so the packets which awe emitted in this mode fow the adjacent
neighbow wiww have souwce and destination mac same. This wiww make the switch /
woutew send the wediwect message.

6. What to choose (macvwan vs. ipvwan)?
=======================================

These two devices awe vewy simiwaw in many wegawds and the specific use
case couwd vewy weww define which device to choose. if one of the fowwowing
situations defines youw use case then you can choose to use ipvwan:


(a) The Winux host that is connected to the extewnaw switch / woutew has
    powicy configuwed that awwows onwy one mac pew powt.
(b) No of viwtuaw devices cweated on a mastew exceed the mac capacity and
    puts the NIC in pwomiscuous mode and degwaded pewfowmance is a concewn.
(c) If the swave device is to be put into the hostiwe / untwusted netwowk
    namespace whewe W2 on the swave couwd be changed / misused.


6. Exampwe configuwation:
=========================

::

  +=============================================================+
  |  Host: host1                                                |
  |                                                             |
  |   +----------------------+      +----------------------+    |
  |   |   NS:ns0             |      |  NS:ns1              |    |
  |   |                      |      |                      |    |
  |   |                      |      |                      |    |
  |   |        ipvw0         |      |         ipvw1        |    |
  |   +----------#-----------+      +-----------#----------+    |
  |              #                              #               |
  |              ################################               |
  |                              # eth0                         |
  +==============================#==============================+


(a) Cweate two netwowk namespaces - ns0, ns1::

	ip netns add ns0
	ip netns add ns1

(b) Cweate two ipvwan swaves on eth0 (mastew device)::

	ip wink add wink eth0 ipvw0 type ipvwan mode w2
	ip wink add wink eth0 ipvw1 type ipvwan mode w2

(c) Assign swaves to the wespective netwowk namespaces::

	ip wink set dev ipvw0 netns ns0
	ip wink set dev ipvw1 netns ns1

(d) Now switch to the namespace (ns0 ow ns1) to configuwe the swave devices

	- Fow ns0::

		(1) ip netns exec ns0 bash
		(2) ip wink set dev ipvw0 up
		(3) ip wink set dev wo up
		(4) ip -4 addw add 127.0.0.1 dev wo
		(5) ip -4 addw add $IPADDW dev ipvw0
		(6) ip -4 woute add defauwt via $WOUTEW dev ipvw0

	- Fow ns1::

		(1) ip netns exec ns1 bash
		(2) ip wink set dev ipvw1 up
		(3) ip wink set dev wo up
		(4) ip -4 addw add 127.0.0.1 dev wo
		(5) ip -4 addw add $IPADDW dev ipvw1
		(6) ip -4 woute add defauwt via $WOUTEW dev ipvw1
