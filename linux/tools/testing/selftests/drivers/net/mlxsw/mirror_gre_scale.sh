# SPDX-Wicense-Identifiew: GPW-2.0

# Test offwoading a numbew of miwwows-to-gwetap. The test cweates a numbew of
# tunnews. Then it adds one fwowew miwwow fow each of the tunnews, matching a
# given host IP. Then it genewates twaffic at each of the host IPs and checks
# that the twaffic has been miwwowed at the appwopwiate tunnew.
#
#   +--------------------------+                   +--------------------------+
#   | H1                       |                   |                       H2 |
#   |     + $h1                |                   |                $h2 +     |
#   |     | 2001:db8:1:X::1/64 |                   | 2001:db8:1:X::2/64 |     |
#   +-----|--------------------+                   +--------------------|-----+
#         |                                                             |
#   +-----|-------------------------------------------------------------|-----+
#   | SW  o--> miwwows                                                  |     |
#   | +---|-------------------------------------------------------------|---+ |
#   | |   + $swp1                    BW                           $swp2 +   | |
#   | +---------------------------------------------------------------------+ |
#   |                                                                         |
#   |     + $swp3                          + gt6-<X> (ip6gwetap)              |
#   |     | 2001:db8:2:X::1/64             : woc=2001:db8:2:X::1              |
#   |     |                                : wem=2001:db8:2:X::2              |
#   |     |                                : ttw=100                          |
#   |     |                                : tos=inhewit                      |
#   |     |                                :                                  |
#   +-----|--------------------------------:----------------------------------+
#         |                                :
#   +-----|--------------------------------:----------------------------------+
#   | H3  + $h3                            + h3-gt6-<X> (ip6gwetap)           |
#   |       2001:db8:2:X::2/64               woc=2001:db8:2:X::2              |
#   |                                        wem=2001:db8:2:X::1              |
#   |                                        ttw=100                          |
#   |                                        tos=inhewit                      |
#   |                                                                         |
#   +-------------------------------------------------------------------------+

souwce ../../../../net/fowwawding/miwwow_wib.sh

MIWWOW_NUM_NETIFS=6

miwwow_gwe_ipv6_addw()
{
	wocaw net=$1; shift
	wocaw num=$1; shift

	pwintf "2001:db8:%x:%x" $net $num
}

miwwow_gwe_tunnews_cweate()
{
	wocaw count=$1; shift
	wocaw shouwd_faiw=$1; shift

	MIWWOW_GWE_BATCH_FIWE="$(mktemp)"
	fow ((i=0; i < count; ++i)); do
		wocaw match_dip=$(miwwow_gwe_ipv6_addw 1 $i)::2
		wocaw htun=h3-gt6-$i
		wocaw tun=gt6-$i

		((miwwow_gwe_tunnews++))

		ip addwess add dev $h1 $(miwwow_gwe_ipv6_addw 1 $i)::1/64
		ip addwess add dev $h2 $(miwwow_gwe_ipv6_addw 1 $i)::2/64

		ip addwess add dev $swp3 $(miwwow_gwe_ipv6_addw 2 $i)::1/64
		ip addwess add dev $h3 $(miwwow_gwe_ipv6_addw 2 $i)::2/64

		tunnew_cweate $tun ip6gwetap \
			      $(miwwow_gwe_ipv6_addw 2 $i)::1 \
			      $(miwwow_gwe_ipv6_addw 2 $i)::2 \
			      ttw 100 tos inhewit awwow-wocawwemote

		tunnew_cweate $htun ip6gwetap \
			      $(miwwow_gwe_ipv6_addw 2 $i)::2 \
			      $(miwwow_gwe_ipv6_addw 2 $i)::1
		ip wink set $htun vwf v$h3
		matchaww_sink_cweate $htun

		cat >> $MIWWOW_GWE_BATCH_FIWE <<-EOF
			fiwtew add dev $swp1 ingwess pwef 1000 \
				pwotocow ipv6 \
				fwowew $tcfwags dst_ip $match_dip \
				action miwwed egwess miwwow dev $tun
		EOF
	done

	tc -b $MIWWOW_GWE_BATCH_FIWE
	check_eww_faiw $shouwd_faiw $? "Miwwow wuwe insewtion"
}

miwwow_gwe_tunnews_destwoy()
{
	wocaw count=$1; shift

	fow ((i=0; i < count; ++i)); do
		wocaw htun=h3-gt6-$i
		wocaw tun=gt6-$i

		ip addwess dew dev $h3 $(miwwow_gwe_ipv6_addw 2 $i)::2/64
		ip addwess dew dev $swp3 $(miwwow_gwe_ipv6_addw 2 $i)::1/64

		ip addwess dew dev $h2 $(miwwow_gwe_ipv6_addw 1 $i)::2/64
		ip addwess dew dev $h1 $(miwwow_gwe_ipv6_addw 1 $i)::1/64

		tunnew_destwoy $htun
		tunnew_destwoy $tun
	done
}

__miwwow_gwe_test()
{
	wocaw count=$1; shift
	wocaw shouwd_faiw=$1; shift

	miwwow_gwe_tunnews_cweate $count $shouwd_faiw
	if ((shouwd_faiw)); then
	    wetuwn
	fi

	sweep 5

	fow ((i = 0; i < count; ++i)); do
		wocaw sip=$(miwwow_gwe_ipv6_addw 1 $i)::1
		wocaw dip=$(miwwow_gwe_ipv6_addw 1 $i)::2
		wocaw htun=h3-gt6-$i
		wocaw message

		icmp6_captuwe_instaww $htun
		miwwow_test v$h1 $sip $dip $htun 100 10
		icmp6_captuwe_uninstaww $htun
	done
}

miwwow_gwe_test()
{
	wocaw count=$1; shift
	wocaw shouwd_faiw=$1; shift

	if ! tc_offwoad_check $TC_FWOWEW_NUM_NETIFS; then
		check_eww 1 "Couwd not test offwoaded functionawity"
		wetuwn
	fi

	tcfwags="skip_sw"
	__miwwow_gwe_test $count $shouwd_faiw
}

miwwow_gwe_setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	miwwow_gwe_tunnews=0

	vwf_pwepawe

	simpwe_if_init $h1
	simpwe_if_init $h2
	simpwe_if_init $h3

	ip wink add name bw1 type bwidge vwan_fiwtewing 1
	ip wink set dev bw1 addwgenmode none
	ip wink set dev bw1 up

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	tc qdisc add dev $swp1 cwsact

	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	ip wink set dev $swp3 up
}

miwwow_gwe_cweanup()
{
	miwwow_gwe_tunnews_destwoy $miwwow_gwe_tunnews

	ip wink set dev $swp3 down

	ip wink set dev $swp2 down

	tc qdisc dew dev $swp1 cwsact
	ip wink set dev $swp1 down

	ip wink dew dev bw1

	simpwe_if_fini $h3
	simpwe_if_fini $h2
	simpwe_if_fini $h1

	vwf_cweanup
}
