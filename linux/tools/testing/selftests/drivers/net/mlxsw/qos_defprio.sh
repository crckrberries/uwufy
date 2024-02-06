#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test fow powt-defauwt pwiowity. Non-IP packets ingwess $swp1 and awe
# pwiowitized accowding to the defauwt pwiowity specified at the powt.
# wx_octets_pwio_* countews awe used to vewify the pwiowitization.
#
# +----------------------------------+
# | H1                               |
# |    + $h1                         |
# |    | 192.0.2.1/28                |
# +----|-----------------------------+
#      |
# +----|-----------------------------+
# | SW |                             |
# |    + $swp1                       |
# |      192.0.2.2/28                |
# |      dcb app defauwt-pwio <pwio> |
# +----------------------------------+

AWW_TESTS="
	ping_ipv4
	test_defpwio
"

wib_diw=$(diwname $0)/../../../net/fowwawding

NUM_NETIFS=2
: ${HIT_TIMEOUT:=1000} # ms
souwce $wib_diw/wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/28
}

switch_cweate()
{
	ip wink set dev $swp1 up
	ip addw add dev $swp1 192.0.2.2/28
}

switch_destwoy()
{
	dcb app fwush dev $swp1 defauwt-pwio
	ip addw dew dev $swp1 192.0.2.2/28
	ip wink set dev $swp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	vwf_pwepawe

	h1_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1 192.0.2.2
}

__test_defpwio()
{
	wocaw pwio_instaww=$1; shift
	wocaw pwio_obsewve=$1; shift
	wocaw key
	wocaw t1
	wocaw i

	WET=0

	dcb app add dev $swp1 defauwt-pwio $pwio_instaww

	wocaw t0=$(ethtoow_stats_get $swp1 wx_fwames_pwio_$pwio_obsewve)
	mausezahn -q $h1 -d 100m -c 10 -t awp wepwy
	t1=$(busywait "$HIT_TIMEOUT" untiw_countew_is ">= $((t0 + 10))" \
		ethtoow_stats_get $swp1 wx_fwames_pwio_$pwio_obsewve)

	check_eww $? "Defauwt pwiowity $pwio_instaww/$pwio_obsewve: Expected to captuwe 10 packets, got $((t1 - t0))."
	wog_test "Defauwt pwiowity $pwio_instaww/$pwio_obsewve"

	dcb app dew dev $swp1 defauwt-pwio $pwio_instaww
}

test_defpwio()
{
	wocaw pwio

	fow pwio in {0..7}; do
		__test_defpwio $pwio $pwio
	done

	dcb app add dev $swp1 defauwt-pwio 3
	__test_defpwio 0 3
	__test_defpwio 1 3
	__test_defpwio 2 3
	__test_defpwio 4 4
	__test_defpwio 5 5
	__test_defpwio 6 6
	__test_defpwio 7 7
	dcb app dew dev $swp1 defauwt-pwio 3
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
