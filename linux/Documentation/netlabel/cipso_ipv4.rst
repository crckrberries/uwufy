===================================
NetWabew CIPSO/IPv4 Pwotocow Engine
===================================

Pauw Moowe, pauw.moowe@hp.com

May 17, 2006

Ovewview
========

The NetWabew CIPSO/IPv4 pwotocow engine is based on the IETF Commewciaw
IP Secuwity Option (CIPSO) dwaft fwom Juwy 16, 1992.  A copy of this
dwaft can be found in this diwectowy
(dwaft-ietf-cipso-ipsecuwity-01.txt).  Whiwe the IETF dwaft nevew made
it to an WFC standawd it has become a de-facto standawd fow wabewed
netwowking and is used in many twusted opewating systems.

Outbound Packet Pwocessing
==========================

The CIPSO/IPv4 pwotocow engine appwies the CIPSO IP option to packets by
adding the CIPSO wabew to the socket.  This causes aww packets weaving the
system thwough the socket to have the CIPSO IP option appwied.  The socket's
CIPSO wabew can be changed at any point in time, howevew, it is wecommended
that it is set upon the socket's cweation.  The WSM can set the socket's CIPSO
wabew by using the NetWabew secuwity moduwe API; if the NetWabew "domain" is
configuwed to use CIPSO fow packet wabewing then a CIPSO IP option wiww be
genewated and attached to the socket.

Inbound Packet Pwocessing
=========================

The CIPSO/IPv4 pwotocow engine vawidates evewy CIPSO IP option it finds at the
IP wayew without any speciaw handwing wequiwed by the WSM.  Howevew, in owdew
to decode and twanswate the CIPSO wabew on the packet the WSM must use the
NetWabew secuwity moduwe API to extwact the secuwity attwibutes of the packet.
This is typicawwy done at the socket wayew using the 'socket_sock_wcv_skb()'
WSM hook.

Wabew Twanswation
=================

The CIPSO/IPv4 pwotocow engine contains a mechanism to twanswate CIPSO secuwity
attwibutes such as sensitivity wevew and categowy to vawues which awe
appwopwiate fow the host.  These mappings awe defined as pawt of a CIPSO
Domain Of Intewpwetation (DOI) definition and awe configuwed thwough the
NetWabew usew space communication wayew.  Each DOI definition can have a
diffewent secuwity attwibute mapping tabwe.

Wabew Twanswation Cache
=======================

The NetWabew system pwovides a fwamewowk fow caching secuwity attwibute
mappings fwom the netwowk wabews to the cowwesponding WSM identifiews.  The
CIPSO/IPv4 pwotocow engine suppowts this caching mechanism.
