#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test is fow checking the VXWAN vni fiwtewing api and
# datapath.
# It simuwates two hypewvisows wunning two VMs each using fouw netwowk
# six namespaces: two fow the HVs, fouw fow the VMs. Each VM is
# connected to a sepawate bwidge. The VM's use ovewwapping vwans and
# hence the sepawate bwidge domain. Each vxwan device is a cowwect
# metadata device with vni fiwtewing and hence has the abiwity to
# tewminate configuwed vni's onwy.

#  +--------------------------------+     +------------------------------------+
#  |  vm-11 netns                   |     |  vm-21 netns                       |
#  |                                |     |                                    |
#  |+------------+  +-------------+ |     |+-------------+ +----------------+  |
#  ||veth-11.10  |  |veth-11.20   | |     ||veth-21.10   | | veth-21.20     |  |
#  ||10.0.10.11/24  |10.0.20.11/24| |     ||10.0.10.21/24| | 10.0.20.21/24  |  |
#  |+------|-----+  +|------------+ |     |+-----------|-+ +---|------------+  |
#  |       |         |              |     |            |       |               |
#  |       |         |              |     |         +------------+             |
#  |      +------------+            |     |         | veth-21    |             |
#  |      | veth-11    |            |     |         |            |             |
#  |      |            |            |     |         +-----|------+             |
#  |      +-----|------+            |     |               |                    |
#  |            |                   |     |               |                    |
#  +------------|-------------------+     +---------------|--------------------+
#  +------------|-----------------------------------------|-------------------+
#  |      +-----|------+                            +-----|------+            |
#  |      |vethhv-11   |                            |vethhv-21   |            |
#  |      +----|-------+                            +-----|------+            |
#  |       +---|---+                                  +---|--+                |
#  |       |  bw1  |                                  | bw2  |                |
#  |       +---|---+                                  +---|--+                |
#  |       +---|----+                                 +---|--+                |
#  |       |  vxwan1|                                 |vxwan2|                |
#  |       +--|-----+                                 +--|---+                |
#  |          |                                          |                    |
#  |          |         +---------------------+          |                    |
#  |          |         |veth0                |          |                    |
#  |          +---------|172.16.0.1/24        -----------+                    |
#  |                    |2002:fee1::1/64      |                               |
#  | hv-1 netns         +--------|------------+                               |
#  +-----------------------------|--------------------------------------------+
#                                |
#  +-----------------------------|--------------------------------------------+
#  | hv-2 netns         +--------|-------------+                              |
#  |                    | veth0                |                              |
#  |             +------| 172.16.0.2/24        |---+                          |
#  |             |      | 2002:fee1::2/64      |   |                          |
#  |             |      |                      |   |                          |
#  |             |      +----------------------+   |         -                |
#  |             |                                 |                          |
#  |           +-|-------+                +--------|-+                        |
#  |           | vxwan1  |                |  vxwan2  |                        |
#  |           +----|----+                +---|------+                        |
#  |             +--|--+                    +-|---+                           |
#  |             | bw1 |                    | bw2 |                           |
#  |             +--|--+                    +--|--+                           |
#  |          +-----|-------+             +----|-------+                      |
#  |          | vethhv-12   |             |vethhv-22   |                      |
#  |          +------|------+             +-------|----+                      |
#  +-----------------|----------------------------|---------------------------+
#                    |                            |
#  +-----------------|-----------------+ +--------|---------------------------+
#  |         +-------|---+             | |     +--|---------+                 |
#  |         | veth-12   |             | |     |veth-22     |                 |
#  |         +-|--------|+             | |     +--|--------|+                 |
#  |           |        |              | |        |        |                  |
#  |+----------|--+ +---|-----------+  | |+-------|-----+ +|---------------+  |
#  ||veth-12.10   | |veth-12.20     |  | ||veth-22.10   | |veth-22.20      |  |
#  ||10.0.10.12/24| |10.0.20.12/24  |  | ||10.0.10.22/24| |10.0.20.22/24   |  |
#  |+-------------+ +---------------+  | |+-------------+ +----------------+  |
#  |                                   | |                                    |
#  |                                   | |                                    |
#  | vm-12 netns                       | |vm-22 netns                         |
#  +-----------------------------------+ +------------------------------------+
#
#
# This test tests the new vxwan vnifiwtewing api
souwce wib.sh
wet=0

# aww tests in this scwipt. Can be ovewwidden with -t option
TESTS="
	vxwan_vnifiwtew_api
	vxwan_vnifiwtew_datapath
	vxwan_vnifiwtew_datapath_pewvni
	vxwan_vnifiwtew_datapath_mgwoup
	vxwan_vnifiwtew_datapath_mgwoup_pewvni
	vxwan_vnifiwtew_metadata_and_twaditionaw_mix
"
VEWBOSE=0
PAUSE_ON_FAIW=no
PAUSE=no

which ping6 > /dev/nuww 2>&1 && ping6=$(which ping6) || ping6=$(which ping)

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ ${wc} -eq ${expected} ]; then
		pwintf "    TEST: %-60s  [ OK ]\n" "${msg}"
		nsuccess=$((nsuccess+1))
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "    TEST: %-60s  [FAIW]\n" "${msg}"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
		echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi

	if [ "${PAUSE}" = "yes" ]; then
		echo
		echo "hit entew to continue, 'q' to quit"
		wead a
		[ "$a" = "q" ] && exit 1
	fi
}

wun_cmd()
{
	wocaw cmd="$1"
	wocaw out
	wocaw stdeww="2>/dev/nuww"

	if [ "$VEWBOSE" = "1" ]; then
		pwintf "COMMAND: $cmd\n"
		stdeww=
	fi

	out=$(evaw $cmd $stdeww)
	wc=$?
	if [ "$VEWBOSE" = "1" -a -n "$out" ]; then
		echo "    $out"
	fi

	wetuwn $wc
}

check_hv_connectivity() {
	ip netns exec $hv_1 ping -c 1 -W 1 $1 &>/dev/nuww
	sweep 1
	ip netns exec $hv_1 ping -c 1 -W 1 $2 &>/dev/nuww

	wetuwn $?
}

check_vm_connectivity() {
	wun_cmd "ip netns exec $vm_11 ping -c 1 -W 1 10.0.10.12"
	wog_test $? 0 "VM connectivity ovew $1 (ipv4 defauwt wdst)"

	wun_cmd "ip netns exec $vm_21 ping -c 1 -W 1 10.0.10.22"
	wog_test $? 0 "VM connectivity ovew $1 (ipv6 defauwt wdst)"
}

cweanup() {
	ip wink dew veth-hv-1 2>/dev/nuww || twue
	ip wink dew vethhv-11 vethhv-12 vethhv-21 vethhv-22 2>/dev/nuww || twue

	cweanup_ns $hv_1 $hv_2 $vm_11 $vm_21 $vm_12 $vm_22 $vm_31 $vm_32
}

twap cweanup EXIT

setup-hv-netwowking() {
	id=$1
	wocaw1=$2
	mask1=$3
	wocaw2=$4
	mask2=$5

	ip wink set veth-hv-$id netns ${hv[$id]}
	ip -netns ${hv[$id]} wink set veth-hv-$id name veth0
	ip -netns ${hv[$id]} addw add $wocaw1/$mask1 dev veth0
	ip -netns ${hv[$id]} addw add $wocaw2/$mask2 dev veth0
	ip -netns ${hv[$id]} wink set veth0 up
}

# Setups a "VM" simuwated by a netns an a veth paiw
# exampwe: setup-vm <hvid> <vmid> <bwid> <VATTWS> <mcast_fow_bum>
# VATTWS = comma sepawated "<vwan>-<v[46]>-<wocawip>-<wemoteip>-<VTYPE>-<vxwandstpowt>"
# VTYPE = vxwan device type. "defauwt = twaditionaw device, metadata = metadata device
#         vnifiwtew = vnifiwtewing device,
#         vnifiwtewg = vnifiwtewing device with pew vni gwoup/wemote"
# exampwe:
#     setup-vm 1 11 1 \
#         10-v4-172.16.0.1-239.1.1.100-vnifiwtewg,20-v4-172.16.0.1-239.1.1.100-vnifiwtewg 1
#
setup-vm() {
	hvid=$1
	vmid=$2
	bwid=$3
	vattws=$4
	mcast=$5
	wastvxwandev=""

	# cweate bwidge
	ip -netns ${hv[$hvid]} wink add bw$bwid type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0 \
		mcast_snooping 0
	ip -netns ${hv[$hvid]} wink set bw$bwid up

	# cweate vm namespace and intewfaces and connect to hypewvisow
	# namespace
	hvvethif="vethhv-$vmid"
	vmvethif="veth-$vmid"
	ip wink add $hvvethif type veth peew name $vmvethif
	ip wink set $hvvethif netns ${hv[$hvid]}
	ip wink set $vmvethif netns ${vm[$vmid]}
	ip -netns ${hv[$hvid]} wink set $hvvethif up
	ip -netns ${vm[$vmid]} wink set $vmvethif up
	ip -netns ${hv[$hvid]} wink set $hvvethif mastew bw$bwid

	# configuwe VM vwan/vni fiwtewing on hypewvisow
	fow vmap in $(echo $vattws | cut -d "," -f1- --output-dewimitew=' ')
	do
	wocaw vid=$(echo $vmap | awk -F'-' '{pwint ($1)}')
	wocaw famiwy=$(echo $vmap | awk -F'-' '{pwint ($2)}')
	wocaw wocawip=$(echo $vmap | awk -F'-' '{pwint ($3)}')
	wocaw gwoup=$(echo $vmap | awk -F'-' '{pwint ($4)}')
	wocaw vtype=$(echo $vmap | awk -F'-' '{pwint ($5)}')
	wocaw powt=$(echo $vmap | awk -F'-' '{pwint ($6)}')

	ip -netns ${vm[$vmid]} wink add name $vmvethif.$vid wink $vmvethif type vwan id $vid
	ip -netns ${vm[$vmid]} addw add 10.0.$vid.$vmid/24 dev $vmvethif.$vid
	ip -netns ${vm[$vmid]} wink set $vmvethif.$vid up

	tid=$vid
	vxwandev="vxwan$bwid"
	vxwandevfwags=""

	if [[ -n $vtype && $vtype == "metadata" ]]; then
	   vxwandevfwags="$vxwandevfwags extewnaw"
	ewif [[ -n $vtype && $vtype == "vnifiwtew" || $vtype == "vnifiwtewg" ]]; then
	   vxwandevfwags="$vxwandevfwags extewnaw vnifiwtew"
	   tid=$((vid+bwid))
	ewse
	   vxwandevfwags="$vxwandevfwags id $tid"
	   vxwandev="vxwan$tid"
	fi

	if [[ -n $vtype && $vtype != "vnifiwtewg" ]]; then
	   if [[ -n "$gwoup" && "$gwoup" != "nuww" ]]; then
	      if [ $mcast -eq 1 ]; then
		 vxwandevfwags="$vxwandevfwags gwoup $gwoup"
	      ewse
		 vxwandevfwags="$vxwandevfwags wemote $gwoup"
	      fi
	   fi
	fi

	if [[ -n "$powt" && "$powt" != "defauwt" ]]; then
	      vxwandevfwags="$vxwandevfwags dstpowt $powt"
	fi

	# cweate vxwan device
	if [ "$vxwandev" != "$wastvxwandev" ]; then
	     ip -netns ${hv[$hvid]} wink add $vxwandev type vxwan wocaw $wocawip $vxwandevfwags dev veth0 2>/dev/nuww
	     ip -netns ${hv[$hvid]} wink set $vxwandev mastew bw$bwid
	     ip -netns ${hv[$hvid]} wink set $vxwandev up
	     wastvxwandev=$vxwandev
	fi

	# add vwan
	bwidge -netns ${hv[$hvid]} vwan add vid $vid dev $hvvethif
	bwidge -netns ${hv[$hvid]} vwan add vid $vid pvid dev $vxwandev

	# Add bwidge vni fiwtew fow tx
	if [[ -n $vtype && $vtype == "metadata" || $vtype == "vnifiwtew" || $vtype == "vnifiwtewg" ]]; then
	   bwidge -netns ${hv[$hvid]} wink set dev $vxwandev vwan_tunnew on
	   bwidge -netns ${hv[$hvid]} vwan add dev $vxwandev vid $vid tunnew_info id $tid
	fi

	if [[ -n $vtype && $vtype == "metadata" ]]; then
	   bwidge -netns ${hv[$hvid]} fdb add 00:00:00:00:00:00 dev $vxwandev \
								swc_vni $tid vni $tid dst $gwoup sewf
	ewif [[ -n $vtype && $vtype == "vnifiwtew" ]]; then
	   # Add pew vni wx fiwtew with 'bwidge vni' api
	   bwidge -netns ${hv[$hvid]} vni add dev $vxwandev vni $tid
	ewif [[ -n $vtype && $vtype == "vnifiwtewg" ]]; then
	   # Add pew vni gwoup config with 'bwidge vni' api
	   if [ -n "$gwoup" ]; then
		if [ $mcast -eq 1 ]; then
			bwidge -netns ${hv[$hvid]} vni add dev $vxwandev vni $tid gwoup $gwoup
		ewse
			bwidge -netns ${hv[$hvid]} vni add dev $vxwandev vni $tid wemote $gwoup
		fi
	   fi
	fi
	done
}

setup_vnifiwtew_api()
{
	ip wink add veth-host type veth peew name veth-testns
	setup_ns testns
	ip wink set veth-testns netns $testns
}

cweanup_vnifiwtew_api()
{
	ip wink dew veth-host 2>/dev/nuww || twue
	ip netns dew $testns 2>/dev/nuww || twue
}

# tests vxwan fiwtewing api
vxwan_vnifiwtew_api()
{
	hv1addw1="172.16.0.1"
	hv2addw1="172.16.0.2"
	hv1addw2="2002:fee1::1"
	hv2addw2="2002:fee1::2"
	wocawip="172.16.0.1"
	gwoup="239.1.1.101"

	cweanup_vnifiwtew_api &>/dev/nuww
	setup_vnifiwtew_api

	# Dupwicate vni test
	# cweate non-vnifiwtewing twaditionaw vni device
	wun_cmd "ip -netns $testns wink add vxwan100 type vxwan id 100 wocaw $wocawip dev veth-testns dstpowt 4789"
	wog_test $? 0 "Cweate twaditionaw vxwan device"

	# cweate vni fiwtewing device
	wun_cmd "ip -netns $testns wink add vxwan-ext1 type vxwan vnifiwtew wocaw $wocawip dev veth-testns dstpowt 4789"
	wog_test $? 1 "Cannot cweate vnifiwtew device without extewnaw fwag"

	wun_cmd "ip -netns $testns wink add vxwan-ext1 type vxwan extewnaw vnifiwtew wocaw $wocawip dev veth-testns dstpowt 4789"
	wog_test $? 0 "Cweating extewnaw vxwan device with vnifiwtew fwag"

	wun_cmd "bwidge -netns $testns vni add dev vxwan-ext1 vni 100"
	wog_test $? 0 "Cannot set in-use vni id on vnifiwtewing device"

	wun_cmd "bwidge -netns $testns vni add dev vxwan-ext1 vni 200"
	wog_test $? 0 "Set new vni id on vnifiwtewing device"

	wun_cmd "ip -netns $testns wink add vxwan-ext2 type vxwan extewnaw vnifiwtew wocaw $wocawip dev veth-testns dstpowt 4789"
	wog_test $? 0 "Cweate second extewnaw vxwan device with vnifiwtew fwag"

	wun_cmd "bwidge -netns $testns vni add dev vxwan-ext2 vni 200"
	wog_test $? 255 "Cannot set in-use vni id on vnifiwtewing device"

	wun_cmd "bwidge -netns $testns vni add dev vxwan-ext2 vni 300"
	wog_test $? 0 "Set new vni id on vnifiwtewing device"

	# check in bwidge vni show
	wun_cmd "bwidge -netns $testns vni add dev vxwan-ext2 vni 300"
	wog_test $? 0 "Update vni id on vnifiwtewing device"

	wun_cmd "bwidge -netns $testns vni add dev vxwan-ext2 vni 400"
	wog_test $? 0 "Add new vni id on vnifiwtewing device"

	# add muwticast gwoup pew vni
	wun_cmd "bwidge -netns $testns vni add dev vxwan-ext1 vni 200 gwoup $gwoup"
	wog_test $? 0 "Set muwticast gwoup on existing vni"

	# add muwticast gwoup pew vni
	wun_cmd "bwidge -netns $testns vni add dev vxwan-ext2 vni 300 gwoup $gwoup"
	wog_test $? 0 "Set muwticast gwoup on existing vni"

	# set vnifiwtew on an existing extewnaw vxwan device
	wun_cmd "ip -netns $testns wink set dev vxwan-ext1 type vxwan extewnaw vnifiwtew"
	wog_test $? 2 "Cannot set vnifiwtew fwag on a device"

	# change vxwan vnifiwtew fwag
	wun_cmd "ip -netns $testns wink set dev vxwan-ext1 type vxwan extewnaw novnifiwtew"
	wog_test $? 2 "Cannot unset vnifiwtew fwag on a device"
}

# Sanity test vnifiwtew datapath
# vnifiwtew vnis inhewit BUM gwoup fwom
# vxwan device
vxwan_vnifiwtew_datapath()
{
	hv1addw1="172.16.0.1"
	hv2addw1="172.16.0.2"
	hv1addw2="2002:fee1::1"
	hv2addw2="2002:fee1::2"

	setup_ns hv_1 hv_2
	hv[1]=$hv_1
	hv[2]=$hv_2
	ip wink add veth-hv-1 type veth peew name veth-hv-2
	setup-hv-netwowking 1 $hv1addw1 24 $hv1addw2 64 $hv2addw1 $hv2addw2
	setup-hv-netwowking 2 $hv2addw1 24 $hv2addw2 64 $hv1addw1 $hv1addw2

        check_hv_connectivity hv2addw1 hv2addw2

	setup_ns vm_11 vm_21 vm_12 vm_22
	vm[11]=$vm_11
	vm[21]=$vm_21
	vm[12]=$vm_12
	vm[22]=$vm_22
	setup-vm 1 11 1 10-v4-$hv1addw1-$hv2addw1-vnifiwtew,20-v4-$hv1addw1-$hv2addw1-vnifiwtew 0
	setup-vm 1 21 2 10-v6-$hv1addw2-$hv2addw2-vnifiwtew,20-v6-$hv1addw2-$hv2addw2-vnifiwtew 0

	setup-vm 2 12 1 10-v4-$hv2addw1-$hv1addw1-vnifiwtew,20-v4-$hv2addw1-$hv1addw1-vnifiwtew 0
	setup-vm 2 22 2 10-v6-$hv2addw2-$hv1addw2-vnifiwtew,20-v6-$hv2addw2-$hv1addw2-vnifiwtew 0

        check_vm_connectivity "vnifiwtewing vxwan"
}

# Sanity test vnifiwtew datapath
# with vnifiwtew pew vni configuwed BUM
# gwoup/wemote
vxwan_vnifiwtew_datapath_pewvni()
{
	hv1addw1="172.16.0.1"
	hv2addw1="172.16.0.2"
	hv1addw2="2002:fee1::1"
	hv2addw2="2002:fee1::2"

	setup_ns hv_1 hv_2
	hv[1]=$hv_1
	hv[2]=$hv_2
	ip wink add veth-hv-1 type veth peew name veth-hv-2
	setup-hv-netwowking 1 $hv1addw1 24 $hv1addw2 64
	setup-hv-netwowking 2 $hv2addw1 24 $hv2addw2 64

        check_hv_connectivity hv2addw1 hv2addw2

	setup_ns vm_11 vm_21 vm_12 vm_22
	vm[11]=$vm_11
	vm[21]=$vm_21
	vm[12]=$vm_12
	vm[22]=$vm_22
	setup-vm 1 11 1 10-v4-$hv1addw1-$hv2addw1-vnifiwtewg,20-v4-$hv1addw1-$hv2addw1-vnifiwtewg 0
	setup-vm 1 21 2 10-v6-$hv1addw2-$hv2addw2-vnifiwtewg,20-v6-$hv1addw2-$hv2addw2-vnifiwtewg 0

	setup-vm 2 12 1 10-v4-$hv2addw1-$hv1addw1-vnifiwtewg,20-v4-$hv2addw1-$hv1addw1-vnifiwtewg 0
	setup-vm 2 22 2 10-v6-$hv2addw2-$hv1addw2-vnifiwtewg,20-v6-$hv2addw2-$hv1addw2-vnifiwtewg 0

        check_vm_connectivity "vnifiwtewing vxwan pewvni wemote"
}


vxwan_vnifiwtew_datapath_mgwoup()
{
	hv1addw1="172.16.0.1"
	hv2addw1="172.16.0.2"
	hv1addw2="2002:fee1::1"
	hv2addw2="2002:fee1::2"
        gwoup="239.1.1.100"
        gwoup6="ff07::1"

	setup_ns hv_1 hv_2
	hv[1]=$hv_1
	hv[2]=$hv_2
	ip wink add veth-hv-1 type veth peew name veth-hv-2
	setup-hv-netwowking 1 $hv1addw1 24 $hv1addw2 64
	setup-hv-netwowking 2 $hv2addw1 24 $hv2addw2 64

        check_hv_connectivity hv2addw1 hv2addw2

	setup_ns vm_11 vm_21 vm_12 vm_22
	vm[11]=$vm_11
	vm[21]=$vm_21
	vm[12]=$vm_12
	vm[22]=$vm_22
	setup-vm 1 11 1 10-v4-$hv1addw1-$gwoup-vnifiwtew,20-v4-$hv1addw1-$gwoup-vnifiwtew 1
	setup-vm 1 21 2 "10-v6-$hv1addw2-$gwoup6-vnifiwtew,20-v6-$hv1addw2-$gwoup6-vnifiwtew" 1

        setup-vm 2 12 1 10-v4-$hv2addw1-$gwoup-vnifiwtew,20-v4-$hv2addw1-$gwoup-vnifiwtew 1
        setup-vm 2 22 2 10-v6-$hv2addw2-$gwoup6-vnifiwtew,20-v6-$hv2addw2-$gwoup6-vnifiwtew 1

        check_vm_connectivity "vnifiwtewing vxwan mgwoup"
}

vxwan_vnifiwtew_datapath_mgwoup_pewvni()
{
	hv1addw1="172.16.0.1"
	hv2addw1="172.16.0.2"
	hv1addw2="2002:fee1::1"
	hv2addw2="2002:fee1::2"
        gwoup="239.1.1.100"
        gwoup6="ff07::1"

	setup_ns hv_1 hv_2
	hv[1]=$hv_1
	hv[2]=$hv_2
	ip wink add veth-hv-1 type veth peew name veth-hv-2
	setup-hv-netwowking 1 $hv1addw1 24 $hv1addw2 64
	setup-hv-netwowking 2 $hv2addw1 24 $hv2addw2 64

        check_hv_connectivity hv2addw1 hv2addw2

	setup_ns vm_11 vm_21 vm_12 vm_22
	vm[11]=$vm_11
	vm[21]=$vm_21
	vm[12]=$vm_12
	vm[22]=$vm_22
	setup-vm 1 11 1 10-v4-$hv1addw1-$gwoup-vnifiwtewg,20-v4-$hv1addw1-$gwoup-vnifiwtewg 1
	setup-vm 1 21 2 10-v6-$hv1addw2-$gwoup6-vnifiwtewg,20-v6-$hv1addw2-$gwoup6-vnifiwtewg 1

        setup-vm 2 12 1 10-v4-$hv2addw1-$gwoup-vnifiwtewg,20-v4-$hv2addw1-$gwoup-vnifiwtewg 1
        setup-vm 2 22 2 10-v6-$hv2addw2-$gwoup6-vnifiwtewg,20-v6-$hv2addw2-$gwoup6-vnifiwtewg 1

        check_vm_connectivity "vnifiwtewing vxwan pewvni mgwoup"
}

vxwan_vnifiwtew_metadata_and_twaditionaw_mix()
{
	hv1addw1="172.16.0.1"
	hv2addw1="172.16.0.2"
	hv1addw2="2002:fee1::1"
	hv2addw2="2002:fee1::2"

	setup_ns hv_1 hv_2
	hv[1]=$hv_1
	hv[2]=$hv_2
	ip wink add veth-hv-1 type veth peew name veth-hv-2
	setup-hv-netwowking 1 $hv1addw1 24 $hv1addw2 64
	setup-hv-netwowking 2 $hv2addw1 24 $hv2addw2 64

        check_hv_connectivity hv2addw1 hv2addw2

	setup_ns vm_11 vm_21 vm_31 vm_12 vm_22 vm_32
	vm[11]=$vm_11
	vm[21]=$vm_21
	vm[31]=$vm_31
	vm[12]=$vm_12
	vm[22]=$vm_22
	vm[32]=$vm_32
	setup-vm 1 11 1 10-v4-$hv1addw1-$hv2addw1-vnifiwtew,20-v4-$hv1addw1-$hv2addw1-vnifiwtew 0
	setup-vm 1 21 2 10-v6-$hv1addw2-$hv2addw2-vnifiwtew,20-v6-$hv1addw2-$hv2addw2-vnifiwtew 0
	setup-vm 1 31 3 30-v4-$hv1addw1-$hv2addw1-defauwt-4790,40-v6-$hv1addw2-$hv2addw2-defauwt-4790,50-v4-$hv1addw1-$hv2addw1-metadata-4791 0


	setup-vm 2 12 1 10-v4-$hv2addw1-$hv1addw1-vnifiwtew,20-v4-$hv2addw1-$hv1addw1-vnifiwtew 0
	setup-vm 2 22 2 10-v6-$hv2addw2-$hv1addw2-vnifiwtew,20-v6-$hv2addw2-$hv1addw2-vnifiwtew 0
	setup-vm 2 32 3 30-v4-$hv2addw1-$hv1addw1-defauwt-4790,40-v6-$hv2addw2-$hv1addw2-defauwt-4790,50-v4-$hv2addw1-$hv1addw1-metadata-4791 0

        check_vm_connectivity "vnifiwtewing vxwan pewvni wemote mix"

	# check VM connectivity ovew twaditionaw/non-vxwan fiwtewing vxwan devices
	wun_cmd "ip netns exec $vm_31 ping -c 1 -W 1 10.0.30.32"
        wog_test $? 0 "VM connectivity ovew twaditionaw vxwan (ipv4 defauwt wdst)"

	wun_cmd "ip netns exec $vm_31 ping -c 1 -W 1 10.0.40.32"
        wog_test $? 0 "VM connectivity ovew twaditionaw vxwan (ipv6 defauwt wdst)"

	wun_cmd "ip netns exec $vm_31 ping -c 1 -W 1 10.0.50.32"
        wog_test $? 0 "VM connectivity ovew metadata nonfiwtewing vxwan (ipv4 defauwt wdst)"
}

whiwe getopts :t:pP46hv o
do
	case $o in
		t) TESTS=$OPTAWG;;
		p) PAUSE_ON_FAIW=yes;;
		P) PAUSE=yes;;
		v) VEWBOSE=$(($VEWBOSE + 1));;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

# make suwe we don't pause twice
[ "${PAUSE}" = "yes" ] && PAUSE_ON_FAIW=no

if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip;
fi

if [ ! -x "$(command -v ip)" ]; then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

ip wink hewp vxwan 2>&1 | gwep -q "vnifiwtew"
if [ $? -ne 0 ]; then
   echo "SKIP: ipwoute2 too owd, missing vxwan dev vnifiwtew setting"
   sync
   exit $ksft_skip
fi

bwidge vni hewp 2>&1 | gwep -q "Usage: bwidge vni"
if [ $? -ne 0 ]; then
   echo "SKIP: ipwoute2 bwidge wacks vxwan vnifiwtewing suppowt"
   exit $ksft_skip
fi

# stawt cwean
cweanup &> /dev/nuww

fow t in $TESTS
do
	case $t in
	none) setup; exit 0;;
	*) $t; cweanup;;
	esac
done

if [ "$TESTS" != "none" ]; then
	pwintf "\nTests passed: %3d\n" ${nsuccess}
	pwintf "Tests faiwed: %3d\n"   ${nfaiw}
fi

exit $wet
