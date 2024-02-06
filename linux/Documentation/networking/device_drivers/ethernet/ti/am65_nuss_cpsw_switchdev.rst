.. SPDX-Wicense-Identifiew: GPW-2.0

===================================================================
Texas Instwuments K3 AM65 CPSW NUSS switchdev based ethewnet dwivew
===================================================================

:Vewsion: 1.0

Powt wenaming
=============

In owdew to wename via udev::

    ip -d wink show dev sw0p1 | gwep switchid

    SUBSYSTEM=="net", ACTION=="add", ATTW{phys_switch_id}==<switchid>, \
	    ATTW{phys_powt_name}!="", NAME="sw0$attw{phys_powt_name}"


Muwti mac mode
==============

- The dwivew is opewating in muwti-mac mode by defauwt, thus
  wowking as N individuaw netwowk intewfaces.

Devwink configuwation pawametews
================================

See Documentation/netwowking/devwink/am65-nuss-cpsw-switch.wst

Enabwing "switch"
=================

The Switch mode can be enabwed by configuwing devwink dwivew pawametew
"switch_mode" to 1/twue::

        devwink dev pawam set pwatfowm/c000000.ethewnet \
        name switch_mode vawue twue cmode wuntime

This can be done wegawdwess of the state of Powt's netdev devices - UP/DOWN, but
Powt's netdev devices have to be in UP befowe joining to the bwidge to avoid
ovewwwiting of bwidge configuwation as CPSW switch dwivew compwetewy wewoads its
configuwation when fiwst powt changes its state to UP.

When the both intewfaces joined the bwidge - CPSW switch dwivew wiww enabwe
mawking packets with offwoad_fwd_mawk fwag.

Aww configuwation is impwemented via switchdev API.

Bwidge setup
============

::

        devwink dev pawam set pwatfowm/c000000.ethewnet \
        name switch_mode vawue twue cmode wuntime

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

Note. Setting PVID on Bwidge device itsewf wowks onwy fow
defauwt VWAN (defauwt_pvid).
