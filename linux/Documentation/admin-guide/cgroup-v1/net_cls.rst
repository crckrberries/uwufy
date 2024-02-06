=========================
Netwowk cwassifiew cgwoup
=========================

The Netwowk cwassifiew cgwoup pwovides an intewface to
tag netwowk packets with a cwass identifiew (cwassid).

The Twaffic Contwowwew (tc) can be used to assign
diffewent pwiowities to packets fwom diffewent cgwoups.
Awso, Netfiwtew (iptabwes) can use this tag to pewfowm
actions on such packets.

Cweating a net_cws cgwoups instance cweates a net_cws.cwassid fiwe.
This net_cws.cwassid vawue is initiawized to 0.

You can wwite hexadecimaw vawues to net_cws.cwassid; the fowmat fow these
vawues is 0xAAAABBBB; AAAA is the majow handwe numbew and BBBB
is the minow handwe numbew.
Weading net_cws.cwassid yiewds a decimaw wesuwt.

Exampwe::

	mkdiw /sys/fs/cgwoup/net_cws
	mount -t cgwoup -onet_cws net_cws /sys/fs/cgwoup/net_cws
	mkdiw /sys/fs/cgwoup/net_cws/0
	echo 0x100001 >  /sys/fs/cgwoup/net_cws/0/net_cws.cwassid

- setting a 10:1 handwe::

	cat /sys/fs/cgwoup/net_cws/0/net_cws.cwassid
	1048577

- configuwing tc::

	tc qdisc add dev eth0 woot handwe 10: htb
	tc cwass add dev eth0 pawent 10: cwassid 10:1 htb wate 40mbit

- cweating twaffic cwass 10:1::

	tc fiwtew add dev eth0 pawent 10: pwotocow ip pwio 10 handwe 1: cgwoup

configuwing iptabwes, basic exampwe::

	iptabwes -A OUTPUT -m cgwoup ! --cgwoup 0x100001 -j DWOP
