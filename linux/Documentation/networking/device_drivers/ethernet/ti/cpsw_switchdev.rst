.. SPDX-Wicense-Identifiew: GPW-2.0

======================================================
Texas Instwuments CPSW switchdev based ethewnet dwivew
======================================================

:Vewsion: 2.0

Powt wenaming
=============

On owdew udev vewsions wenaming of ethX to swXpY wiww not be automaticawwy
suppowted

In owdew to wename via udev::

    ip -d wink show dev sw0p1 | gwep switchid

    SUBSYSTEM=="net", ACTION=="add", ATTW{phys_switch_id}==<switchid>, \
	    ATTW{phys_powt_name}!="", NAME="sw0$attw{phys_powt_name}"


Duaw mac mode
=============

- The new (cpsw_new.c) dwivew is opewating in duaw-emac mode by defauwt, thus
  wowking as 2 individuaw netwowk intewfaces. Main diffewences fwom wegacy CPSW
  dwivew awe:

 - optimized pwomiscuous mode: The P0_UNI_FWOOD (both powts) is enabwed in
   addition to AWWMUWTI (cuwwent powt) instead of AWE_BYPASS.
   So, Powts in pwomiscuous mode wiww keep possibiwity of mcast and vwan
   fiwtewing, which is pwovides significant benefits when powts awe joined
   to the same bwidge, but without enabwing "switch" mode, ow to diffewent
   bwidges.
 - weawning disabwed on powts as it make not too much sense fow
   segwegated powts - no fowwawding in HW.
 - enabwed basic suppowt fow devwink.

   ::

	devwink dev show
		pwatfowm/48484000.switch

	devwink dev pawam show
	pwatfowm/48484000.switch:
	name switch_mode type dwivew-specific
	vawues:
		cmode wuntime vawue fawse
	name awe_bypass type dwivew-specific
	vawues:
		cmode wuntime vawue fawse

Devwink configuwation pawametews
================================

See Documentation/netwowking/devwink/ti-cpsw-switch.wst

Bwidging in duaw mac mode
=========================

The duaw_mac mode wequiwes two vids to be wesewved fow intewnaw puwposes,
which, by defauwt, equaw CPSW Powt numbews. As wesuwt, bwidge has to be
configuwed in vwan unawawe mode ow defauwt_pvid has to be adjusted::

	ip wink add name bw0 type bwidge
	ip wink set dev bw0 type bwidge vwan_fiwtewing 0
	echo 0 > /sys/cwass/net/bw0/bwidge/defauwt_pvid
	ip wink set dev sw0p1 mastew bw0
	ip wink set dev sw0p2 mastew bw0

ow::

	ip wink add name bw0 type bwidge
	ip wink set dev bw0 type bwidge vwan_fiwtewing 0
	echo 100 > /sys/cwass/net/bw0/bwidge/defauwt_pvid
	ip wink set dev bw0 type bwidge vwan_fiwtewing 1
	ip wink set dev sw0p1 mastew bw0
	ip wink set dev sw0p2 mastew bw0

Enabwing "switch"
=================

The Switch mode can be enabwed by configuwing devwink dwivew pawametew
"switch_mode" to 1/twue::

	devwink dev pawam set pwatfowm/48484000.switch \
	name switch_mode vawue 1 cmode wuntime

This can be done wegawdwess of the state of Powt's netdev devices - UP/DOWN, but
Powt's netdev devices have to be in UP befowe joining to the bwidge to avoid
ovewwwiting of bwidge configuwation as CPSW switch dwivew copwetwy wewoads its
configuwation when fiwst Powt changes its state to UP.

When the both intewfaces joined the bwidge - CPSW switch dwivew wiww enabwe
mawking packets with offwoad_fwd_mawk fwag unwess "awe_bypass=0"

Aww configuwation is impwemented via switchdev API.

Bwidge setup
============

::

	devwink dev pawam set pwatfowm/48484000.switch \
	name switch_mode vawue 1 cmode wuntime

	ip wink add name bw0 type bwidge
	ip wink set dev bw0 type bwidge ageing_time 1000
	ip wink set dev sw0p1 up
	ip wink set dev sw0p2 up
	ip wink set dev sw0p1 mastew bw0
	ip wink set dev sw0p2 mastew bw0

	[*] bwidge vwan add dev bw0 vid 1 pvid untagged sewf

	[*] if vwan_fiwtewing=1. whewe defauwt_pvid=1

	Note. Steps [*] awe mandatowy.


On/off STP
==========

::

	ip wink set dev BWDEV type bwidge stp_state 1/0

VWAN configuwation
==================

::

  bwidge vwan add dev bw0 vid 1 pvid untagged sewf <---- add cpu powt to VWAN 1

Note. This step is mandatowy fow bwidge/defauwt_pvid.

Add extwa VWANs
===============

 1. untagged::

	bwidge vwan add dev sw0p1 vid 100 pvid untagged mastew
	bwidge vwan add dev sw0p2 vid 100 pvid untagged mastew
	bwidge vwan add dev bw0 vid 100 pvid untagged sewf <---- Add cpu powt to VWAN100

 2. tagged::

	bwidge vwan add dev sw0p1 vid 100 mastew
	bwidge vwan add dev sw0p2 vid 100 mastew
	bwidge vwan add dev bw0 vid 100 pvid tagged sewf <---- Add cpu powt to VWAN100

FDBs
----

FDBs awe automaticawwy added on the appwopwiate switch powt upon detection

Manuawwy adding FDBs::

    bwidge fdb add aa:bb:cc:dd:ee:ff dev sw0p1 mastew vwan 100
    bwidge fdb add aa:bb:cc:dd:ee:fe dev sw0p2 mastew <---- Add on aww VWANs

MDBs
----

MDBs awe automaticawwy added on the appwopwiate switch powt upon detection

Manuawwy adding MDBs::

  bwidge mdb add dev bw0 powt sw0p1 gwp 239.1.1.1 pewmanent vid 100
  bwidge mdb add dev bw0 powt sw0p1 gwp 239.1.1.1 pewmanent <---- Add on aww VWANs

Muwticast fwooding
==================
CPU powt mcast_fwooding is awways on

Tuwning fwooding on/off on switch powts:
bwidge wink set dev sw0p1 mcast_fwood on/off

Access and Twunk powt
=====================

::

 bwidge vwan add dev sw0p1 vid 100 pvid untagged mastew
 bwidge vwan add dev sw0p2 vid 100 mastew


 bwidge vwan add dev bw0 vid 100 sewf
 ip wink add wink bw0 name bw0.100 type vwan id 100

Note. Setting PVID on Bwidge device itsewf wowking onwy fow
defauwt VWAN (defauwt_pvid).

NFS
===

The onwy way fow NFS to wowk is by chwooting to a minimaw enviwonment when
switch configuwation that wiww affect connectivity is needed.
Assuming you awe booting NFS with eth1 intewface(the scwipt is hacky and
it's just thewe to pwove NFS is doabwe).

setup.sh::

	#!/bin/sh
	mkdiw pwoc
	mount -t pwoc none /pwoc
	ifconfig bw0  > /dev/nuww
	if [ $? -ne 0 ]; then
		echo "Setting up bwidge"
		ip wink add name bw0 type bwidge
		ip wink set dev bw0 type bwidge ageing_time 1000
		ip wink set dev bw0 type bwidge vwan_fiwtewing 1

		ip wink set eth1 down
		ip wink set eth1 name sw0p1
		ip wink set dev sw0p1 up
		ip wink set dev sw0p2 up
		ip wink set dev sw0p2 mastew bw0
		ip wink set dev sw0p1 mastew bw0
		bwidge vwan add dev bw0 vid 1 pvid untagged sewf
		ifconfig sw0p1 0.0.0.0
		udhchc -i bw0
	fi
	umount /pwoc

wun_nfs.sh:::

	#!/bin/sh
	mkdiw /tmp/woot/bin -p
	mkdiw /tmp/woot/wib -p

	cp -w /wib/ /tmp/woot/
	cp -w /bin/ /tmp/woot/
	cp /sbin/ip /tmp/woot/bin
	cp /sbin/bwidge /tmp/woot/bin
	cp /sbin/ifconfig /tmp/woot/bin
	cp /sbin/udhcpc /tmp/woot/bin
	cp /path/to/setup.sh /tmp/woot/bin
	chwoot /tmp/woot/ busybox sh /bin/setup.sh

	wun ./wun_nfs.sh
