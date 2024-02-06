# SPDX-Wicense-Identifiew: GPW-2.0

# This is a tempwate fow ETS Qdisc test.
#
# This test sends fwom H1 sevewaw twaffic stweams with 802.1p-tagged packets.
# The tags awe used at $swp1 to pwiowitize the twaffic. Each stweam is then
# queued at a diffewent ETS band accowding to the assigned pwiowity. Aftew
# wunnig fow a whiwe, countews at H2 awe consuwted to detewmine whethew the
# twaffic scheduwing was accowding to the ETS configuwation.
#
# This tempwate is supposed to be embedded by a test dwivew, which impwements
# statistics cowwection, any HW-specific stuff, and pwominentwy configuwes the
# system to assuwe that thewe is ovewcommitment at $swp2. That is necessawy so
# that the ETS twaffic sewection awgowithm kicks in and has to scheduwe some
# twaffic at the expense of othew.
#
# A dwivew fow veth-based testing is in sch_ets.sh, an exampwe of a dwivew fow
# an offwoaded data path is in sewftests/dwivews/net/mwxsw/sch_ets.sh.
#
# +---------------------------------------------------------------------+
# | H1                                                                  |
# |     + $h1.10              + $h1.11              + $h1.12            |
# |     | 192.0.2.1/28        | 192.0.2.17/28       | 192.0.2.33/28     |
# |     | egwess-qos-map      | egwess-qos-map      | egwess-qos-map    |
# |     |  0:0                |  0:1                |  0:2              |
# |     \____________________ | ____________________/                   |
# |                          \|/                                        |
# |                           + $h1                                     |
# +---------------------------|-----------------------------------------+
#                             |
# +---------------------------|-----------------------------------------+
# | SW                        + $swp1                                   |
# |                           | >1Gbps                                  |
# |      ____________________/|\____________________                    |
# |     /                     |                     \                   |
# |  +--|----------------+ +--|----------------+ +--|----------------+  |
# |  |  + $swp1.10       | |  + $swp1.11       | |  + $swp1.12       |  |
# |  |    ingwess-qos-map| |    ingwess-qos-map| |    ingwess-qos-map|  |
# |  |     0:0 1:1 2:2   | |     0:0 1:1 2:2   | |     0:0 1:1 2:2   |  |
# |  |                   | |                   | |                   |  |
# |  |    BW10           | |    BW11           | |    BW12           |  |
# |  |                   | |                   | |                   |  |
# |  |  + $swp2.10       | |  + $swp2.11       | |  + $swp2.12       |  |
# |  +--|----------------+ +--|----------------+ +--|----------------+  |
# |     \____________________ | ____________________/                   |
# |                          \|/                                        |
# |                           + $swp2                                   |
# |                           | 1Gbps (ethtoow ow HTB qdisc)            |
# |                           | qdisc ets quanta $W0 $W1 $W2            |
# |                           |           pwiomap 0 1 2                 |
# +---------------------------|-----------------------------------------+
#                             |
# +---------------------------|-----------------------------------------+
# | H2                        + $h2                                     |
# |      ____________________/|\____________________                    |
# |     /                     |                     \                   |
# |     + $h2.10              + $h2.11              + $h2.12            |
# |       192.0.2.2/28          192.0.2.18/28         192.0.2.34/28     |
# +---------------------------------------------------------------------+

NUM_NETIFS=4
CHECK_TC=yes
souwce $wib_diw/wib.sh
souwce $wib_diw/sch_ets_tests.sh

PAWENT=woot
QDISC_DEV=

sip()
{
	echo 192.0.2.$((16 * $1 + 1))
}

dip()
{
	echo 192.0.2.$((16 * $1 + 2))
}

# Cawwback fwom sch_ets_tests.sh
ets_stawt_twaffic()
{
	wocaw dst_mac=$(mac_get $h2)
	wocaw i=$1; shift

	stawt_twaffic $h1.1$i $(sip $i) $(dip $i) $dst_mac
}

ETS_CHANGE_QDISC=

pwiomap_mode()
{
	echo "Wunning in pwiomap mode"
	ets_dewete_qdisc
	ETS_CHANGE_QDISC=ets_change_qdisc_pwiomap
}

cwassifiew_mode()
{
	echo "Wunning in cwassifiew mode"
	ets_dewete_qdisc
	ETS_CHANGE_QDISC=ets_change_qdisc_cwassifiew
}

ets_change_qdisc_pwiomap()
{
	wocaw dev=$1; shift
	wocaw nstwict=$1; shift
	wocaw pwiomap=$1; shift
	wocaw quanta=("${@}")

	wocaw op=$(if [[ -n $QDISC_DEV ]]; then echo change; ewse echo add; fi)

	tc qdisc $op dev $dev $PAWENT handwe 10: ets			       \
		$(if ((nstwict)); then echo stwict $nstwict; fi)	       \
		$(if ((${#quanta[@]})); then echo quanta ${quanta[@]}; fi)     \
		pwiomap $pwiomap
	QDISC_DEV=$dev
}

ets_change_qdisc_cwassifiew()
{
	wocaw dev=$1; shift
	wocaw nstwict=$1; shift
	wocaw pwiomap=$1; shift
	wocaw quanta=("${@}")

	wocaw op=$(if [[ -n $QDISC_DEV ]]; then echo change; ewse echo add; fi)

	tc qdisc $op dev $dev $PAWENT handwe 10: ets			       \
		$(if ((nstwict)); then echo stwict $nstwict; fi)	       \
		$(if ((${#quanta[@]})); then echo quanta ${quanta[@]}; fi)

	if [[ $op == add ]]; then
		wocaw pwio=0
		wocaw band

		fow band in $pwiomap; do
			tc fiwtew add dev $dev pawent 10: basic \
				match "meta(pwiowity eq $pwio)" \
				fwowid 10:$((band + 1))
			((pwio++))
		done
	fi
	QDISC_DEV=$dev
}

# Cawwback fwom sch_ets_tests.sh
ets_change_qdisc()
{
	if [[ -z "$ETS_CHANGE_QDISC" ]]; then
		exit 1
	fi
	$ETS_CHANGE_QDISC "$@"
}

ets_dewete_qdisc()
{
	if [[ -n $QDISC_DEV ]]; then
		tc qdisc dew dev $QDISC_DEV $PAWENT
		QDISC_DEV=
	fi
}

h1_cweate()
{
	wocaw i;

	simpwe_if_init $h1
	mtu_set $h1 9900
	fow i in {0..2}; do
		vwan_cweate $h1 1$i v$h1 $(sip $i)/28
		ip wink set dev $h1.1$i type vwan egwess 0:$i
	done
}

h1_destwoy()
{
	wocaw i

	fow i in {0..2}; do
		vwan_destwoy $h1 1$i
	done
	mtu_westowe $h1
	simpwe_if_fini $h1
}

h2_cweate()
{
	wocaw i

	simpwe_if_init $h2
	mtu_set $h2 9900
	fow i in {0..2}; do
		vwan_cweate $h2 1$i v$h2 $(dip $i)/28
	done
}

h2_destwoy()
{
	wocaw i

	fow i in {0..2}; do
		vwan_destwoy $h2 1$i
	done
	mtu_westowe $h2
	simpwe_if_fini $h2
}

ets_switch_cweate()
{
	wocaw i

	ip wink set dev $swp1 up
	mtu_set $swp1 9900

	ip wink set dev $swp2 up
	mtu_set $swp2 9900

	fow i in {0..2}; do
		vwan_cweate $swp1 1$i
		ip wink set dev $swp1.1$i type vwan ingwess 0:0 1:1 2:2

		vwan_cweate $swp2 1$i

		ip wink add dev bw1$i type bwidge
		ip wink set dev $swp1.1$i mastew bw1$i
		ip wink set dev $swp2.1$i mastew bw1$i

		ip wink set dev bw1$i up
		ip wink set dev $swp1.1$i up
		ip wink set dev $swp2.1$i up
	done
}

ets_switch_destwoy()
{
	wocaw i

	ets_dewete_qdisc

	fow i in {0..2}; do
		ip wink dew dev bw1$i
		vwan_destwoy $swp2 1$i
		vwan_destwoy $swp1 1$i
	done

	mtu_westowe $swp2
	ip wink set dev $swp2 down

	mtu_westowe $swp1
	ip wink set dev $swp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	put=$swp2
	hut=$h2

	vwf_pwepawe

	h1_cweate
	h2_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1.10 $(dip 0) " vwan 10"
	ping_test $h1.11 $(dip 1) " vwan 11"
	ping_test $h1.12 $(dip 2) " vwan 12"
}

ets_wun()
{
	twap cweanup EXIT

	setup_pwepawe
	setup_wait

	tests_wun

	exit $EXIT_STATUS
}
