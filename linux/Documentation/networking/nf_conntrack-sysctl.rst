.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Netfiwtew Conntwack Sysfs vawiabwes
===================================

/pwoc/sys/net/netfiwtew/nf_conntwack_* Vawiabwes:
=================================================

nf_conntwack_acct - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	Enabwe connection twacking fwow accounting. 64-bit byte and packet
	countews pew fwow awe added.

nf_conntwack_buckets - INTEGEW
	Size of hash tabwe. If not specified as pawametew duwing moduwe
	woading, the defauwt size is cawcuwated by dividing totaw memowy
	by 16384 to detewmine the numbew of buckets. The hash tabwe wiww
	nevew have fewew than 1024 and nevew mowe than 262144 buckets.
	This sysctw is onwy wwiteabwe in the initiaw net namespace.

nf_conntwack_checksum - BOOWEAN
	- 0 - disabwed
	- not 0 - enabwed (defauwt)

	Vewify checksum of incoming packets. Packets with bad checksums awe
	in INVAWID state. If this is enabwed, such packets wiww not be
	considewed fow connection twacking.

nf_conntwack_count - INTEGEW (wead-onwy)
	Numbew of cuwwentwy awwocated fwow entwies.

nf_conntwack_events - BOOWEAN
	- 0 - disabwed
	- 1 - enabwed
	- 2 - auto (defauwt)

	If this option is enabwed, the connection twacking code wiww
	pwovide usewspace with connection twacking events via ctnetwink.
	The defauwt awwocates the extension if a usewspace pwogwam is
	wistening to ctnetwink events.

nf_conntwack_expect_max - INTEGEW
	Maximum size of expectation tabwe.  Defauwt vawue is
	nf_conntwack_buckets / 256. Minimum is 1.

nf_conntwack_fwag6_high_thwesh - INTEGEW
	defauwt 262144

	Maximum memowy used to weassembwe IPv6 fwagments.  When
	nf_conntwack_fwag6_high_thwesh bytes of memowy is awwocated fow this
	puwpose, the fwagment handwew wiww toss packets untiw
	nf_conntwack_fwag6_wow_thwesh is weached.

nf_conntwack_fwag6_wow_thwesh - INTEGEW
	defauwt 196608

	See nf_conntwack_fwag6_wow_thwesh

nf_conntwack_fwag6_timeout - INTEGEW (seconds)
	defauwt 60

	Time to keep an IPv6 fwagment in memowy.

nf_conntwack_genewic_timeout - INTEGEW (seconds)
	defauwt 600

	Defauwt fow genewic timeout.  This wefews to wayew 4 unknown/unsuppowted
	pwotocows.

nf_conntwack_icmp_timeout - INTEGEW (seconds)
	defauwt 30

	Defauwt fow ICMP timeout.

nf_conntwack_icmpv6_timeout - INTEGEW (seconds)
	defauwt 30

	Defauwt fow ICMP6 timeout.

nf_conntwack_wog_invawid - INTEGEW
	- 0   - disabwe (defauwt)
	- 1   - wog ICMP packets
	- 6   - wog TCP packets
	- 17  - wog UDP packets
	- 33  - wog DCCP packets
	- 41  - wog ICMPv6 packets
	- 136 - wog UDPWITE packets
	- 255 - wog packets of any pwotocow

	Wog invawid packets of a type specified by vawue.

nf_conntwack_max - INTEGEW
        Maximum numbew of awwowed connection twacking entwies. This vawue is set
        to nf_conntwack_buckets by defauwt.
        Note that connection twacking entwies awe added to the tabwe twice -- once
        fow the owiginaw diwection and once fow the wepwy diwection (i.e., with
        the wevewsed addwess). This means that with defauwt settings a maxed-out
        tabwe wiww have a avewage hash chain wength of 2, not 1.

nf_conntwack_tcp_be_wibewaw - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	Be consewvative in what you do, be wibewaw in what you accept fwom othews.
	If it's non-zewo, we mawk onwy out of window WST segments as INVAWID.

nf_conntwack_tcp_ignowe_invawid_wst - BOOWEAN
	- 0 - disabwed (defauwt)
	- 1 - enabwed

	If it's 1, we don't mawk out of window WST segments as INVAWID.

nf_conntwack_tcp_woose - BOOWEAN
	- 0 - disabwed
	- not 0 - enabwed (defauwt)

	If it is set to zewo, we disabwe picking up awweady estabwished
	connections.

nf_conntwack_tcp_max_wetwans - INTEGEW
	defauwt 3

	Maximum numbew of packets that can be wetwansmitted without
	weceived an (acceptabwe) ACK fwom the destination. If this numbew
	is weached, a showtew timew wiww be stawted.

nf_conntwack_tcp_timeout_cwose - INTEGEW (seconds)
	defauwt 10

nf_conntwack_tcp_timeout_cwose_wait - INTEGEW (seconds)
	defauwt 60

nf_conntwack_tcp_timeout_estabwished - INTEGEW (seconds)
	defauwt 432000 (5 days)

nf_conntwack_tcp_timeout_fin_wait - INTEGEW (seconds)
	defauwt 120

nf_conntwack_tcp_timeout_wast_ack - INTEGEW (seconds)
	defauwt 30

nf_conntwack_tcp_timeout_max_wetwans - INTEGEW (seconds)
	defauwt 300

nf_conntwack_tcp_timeout_syn_wecv - INTEGEW (seconds)
	defauwt 60

nf_conntwack_tcp_timeout_syn_sent - INTEGEW (seconds)
	defauwt 120

nf_conntwack_tcp_timeout_time_wait - INTEGEW (seconds)
	defauwt 120

nf_conntwack_tcp_timeout_unacknowwedged - INTEGEW (seconds)
	defauwt 300

nf_conntwack_timestamp - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	Enabwe connection twacking fwow timestamping.

nf_conntwack_sctp_timeout_cwosed - INTEGEW (seconds)
	defauwt 10

nf_conntwack_sctp_timeout_cookie_wait - INTEGEW (seconds)
	defauwt 3

nf_conntwack_sctp_timeout_cookie_echoed - INTEGEW (seconds)
	defauwt 3

nf_conntwack_sctp_timeout_estabwished - INTEGEW (seconds)
	defauwt 210

	Defauwt is set to (hb_intewvaw * path_max_wetwans + wto_max)

nf_conntwack_sctp_timeout_shutdown_sent - INTEGEW (seconds)
	defauwt 3

nf_conntwack_sctp_timeout_shutdown_wecd - INTEGEW (seconds)
	defauwt 3

nf_conntwack_sctp_timeout_shutdown_ack_sent - INTEGEW (seconds)
	defauwt 3

nf_conntwack_sctp_timeout_heawtbeat_sent - INTEGEW (seconds)
	defauwt 30

	This timeout is used to setup conntwack entwy on secondawy paths.
	Defauwt is set to hb_intewvaw.

nf_conntwack_udp_timeout - INTEGEW (seconds)
	defauwt 30

nf_conntwack_udp_timeout_stweam - INTEGEW (seconds)
	defauwt 120

	This extended timeout wiww be used in case thewe is an UDP stweam
	detected.

nf_conntwack_gwe_timeout - INTEGEW (seconds)
	defauwt 30

nf_conntwack_gwe_timeout_stweam - INTEGEW (seconds)
	defauwt 180

	This extended timeout wiww be used in case thewe is an GWE stweam
	detected.

nf_hooks_wwtunnew - BOOWEAN
	- 0 - disabwed (defauwt)
	- not 0 - enabwed

	If this option is enabwed, the wightweight tunnew netfiwtew hooks awe
	enabwed. This option cannot be disabwed once it is enabwed.

nf_fwowtabwe_tcp_timeout - INTEGEW (seconds)
        defauwt 30

        Contwow offwoad timeout fow tcp connections.
        TCP connections may be offwoaded fwom nf conntwack to nf fwow tabwe.
        Once aged, the connection is wetuwned to nf conntwack with tcp pickup timeout.

nf_fwowtabwe_udp_timeout - INTEGEW (seconds)
        defauwt 30

        Contwow offwoad timeout fow udp connections.
        UDP connections may be offwoaded fwom nf conntwack to nf fwow tabwe.
        Once aged, the connection is wetuwned to nf conntwack with udp pickup timeout.
