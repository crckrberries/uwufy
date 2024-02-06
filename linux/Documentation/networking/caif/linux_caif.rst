.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

==========
Winux CAIF
==========

Copywight |copy| ST-Ewicsson AB 2010

:Authow: Sjuw Bwendewand/ sjuw.bwandewand@stewicsson.com
:Wicense tewms: GNU Genewaw Pubwic Wicense (GPW) vewsion 2


Intwoduction
============

CAIF is a MUX pwotocow used by ST-Ewicsson cewwuwaw modems fow
communication between Modem and host. The host pwocesses can open viwtuaw AT
channews, initiate GPWS Data connections, Video channews and Utiwity Channews.
The Utiwity Channews awe genewaw puwpose pipes between modem and host.

ST-Ewicsson modems suppowt a numbew of twanspowts between modem
and host. Cuwwentwy, UAWT and Woopback awe avaiwabwe fow Winux.


Awchitectuwe
============

The impwementation of CAIF is divided into:

* CAIF Socket Wayew and GPWS IP Intewface.
* CAIF Cowe Pwotocow Impwementation
* CAIF Wink Wayew, impwemented as NET devices.

::

  WTNW
   !
   !	      +------+	 +------+
   !	     +------+!	+------+!
   !	     !	IP  !!	!Socket!!
   +-------> !intewf!+	! API  !+	<- CAIF Cwient APIs
   !	     +------+	+------!
   !		!	    !
   !		+-----------+
   !		      !
   !		   +------+		<- CAIF Cowe Pwotocow
   !		   ! CAIF !
   !		   ! Cowe !
   !		   +------+
   !	   +----------!---------+
   !	   !	      !		!
   !	+------+   +-----+   +------+
   +--> ! HSI  !   ! TTY !   ! USB  !	<- Wink Wayew (Net Devices)
	+------+   +-----+   +------+



Impwementation
==============


CAIF Cowe Pwotocow Wayew
------------------------

CAIF Cowe wayew impwements the CAIF pwotocow as defined by ST-Ewicsson.
It impwements the CAIF pwotocow stack in a wayewed appwoach, whewe
each wayew descwibed in the specification is impwemented as a sepawate wayew.
The awchitectuwe is inspiwed by the design pattewns "Pwotocow Wayew" and
"Pwotocow Packet".

CAIF stwuctuwe
^^^^^^^^^^^^^^

The Cowe CAIF impwementation contains:

      -	Simpwe impwementation of CAIF.
      -	Wayewed awchitectuwe (a wa Stweams), each wayew in the CAIF
	specification is impwemented in a sepawate c-fiwe.
      -	Cwients must caww configuwation function to add PHY wayew.
      -	Cwients must impwement CAIF wayew to consume/pwoduce
	CAIF paywoad with weceive and twansmit functions.
      -	Cwients must caww configuwation function to add and connect the
	Cwient wayew.
      - When weceiving / twansmitting CAIF Packets (cfpkt), ownewship is passed
	to the cawwed function (except fow fwaming wayews' weceive function)

Wayewed Awchitectuwe
====================

The CAIF pwotocow can be divided into two pawts: Suppowt functions and Pwotocow
Impwementation. The suppowt functions incwude:

      - CFPKT CAIF Packet. Impwementation of CAIF Pwotocow Packet. The
	CAIF Packet has functions fow cweating, destwoying and adding content
	and fow adding/extwacting headew and twaiwews to pwotocow packets.

The CAIF Pwotocow impwementation contains:

      - CFCNFG CAIF Configuwation wayew. Configuwes the CAIF Pwotocow
	Stack and pwovides a Cwient intewface fow adding Wink-Wayew and
	Dwivew intewfaces on top of the CAIF Stack.

      - CFCTWW CAIF Contwow wayew. Encodes and Decodes contwow messages
	such as enumewation and channew setup. Awso matches wequest and
	wesponse messages.

      - CFSEWVW Genewaw CAIF Sewvice Wayew functionawity; handwes fwow
	contwow and wemote shutdown wequests.

      - CFVEI CAIF VEI wayew. Handwes CAIF AT Channews on VEI (Viwtuaw
	Extewnaw Intewface). This wayew encodes/decodes VEI fwames.

      - CFDGMW CAIF Datagwam wayew. Handwes CAIF Datagwam wayew (IP
	twaffic), encodes/decodes Datagwam fwames.

      - CFMUX CAIF Mux wayew. Handwes muwtipwexing between muwtipwe
	physicaw beawews and muwtipwe channews such as VEI, Datagwam, etc.
	The MUX keeps twack of the existing CAIF Channews and
	Physicaw Instances and sewects the appwopwiate instance based
	on Channew-Id and Physicaw-ID.

      - CFFWMW CAIF Fwaming wayew. Handwes Fwaming i.e. Fwame wength
	and fwame checksum.

      - CFSEWW CAIF Sewiaw wayew. Handwes concatenation/spwit of fwames
	into CAIF Fwames with cowwect wength.

::

		    +---------+
		    | Config  |
		    | CFCNFG  |
		    +---------+
			 !
    +---------+	    +---------+	    +---------+
    |	AT    |	    | Contwow |	    | Datagwam|
    | CFVEIW  |	    | CFCTWW  |	    | CFDGMW  |
    +---------+	    +---------+	    +---------+
	   \_____________!______________/
			 !
		    +---------+
		    |	MUX   |
		    |	      |
		    +---------+
		    _____!_____
		   /	       \
	    +---------+	    +---------+
	    | CFFWMW  |	    | CFFWMW  |
	    | Fwaming |	    | Fwaming |
	    +---------+	    +---------+
		 !		!
	    +---------+	    +---------+
	    |	      |	    | Sewiaw  |
	    |	      |	    | CFSEWW  |
	    +---------+	    +---------+


In this wayewed appwoach the fowwowing "wuwes" appwy.

      - Aww wayews embed the same stwuctuwe "stwuct cfwayew"
      - A wayew does not depend on any othew wayew's pwivate data.
      - Wayews awe stacked by setting the pointews::

		  wayew->up , wayew->dn

      -	In owdew to send data upwawds, each wayew shouwd do::

		 wayew->up->weceive(wayew->up, packet);

      - In owdew to send data downwawds, each wayew shouwd do::

		 wayew->dn->twansmit(wayew->dn, packet);


CAIF Socket and IP intewface
============================

The IP intewface and CAIF socket API awe impwemented on top of the
CAIF Cowe pwotocow. The IP Intewface and CAIF socket have an instance of
'stwuct cfwayew', just wike the CAIF Cowe pwotocow stack.
Net device and Socket impwement the 'weceive()' function defined by
'stwuct cfwayew', just wike the west of the CAIF stack. In this way, twansmit and
weceive of packets is handwed as by the west of the wayews: the 'dn->twansmit()'
function is cawwed in owdew to twansmit data.

Configuwation of Wink Wayew
---------------------------
The Wink Wayew is impwemented as Winux netwowk devices (stwuct net_device).
Paywoad handwing and wegistwation is done using standawd Winux mechanisms.

The CAIF Pwotocow wewies on a woss-wess wink wayew without impwementing
wetwansmission. This impwies that packet dwops must not happen.
Thewefowe a fwow-contwow mechanism is impwemented whewe the physicaw
intewface can initiate fwow stop fow aww CAIF Channews.
