#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

# Authow: Matthias May <matthias.may@westewmo.com>
#
# This scwipt evawuates ip tunnews that awe capabwe of cawwying W2 twaffic
# if they inhewit ow set the inhewitabwe fiewds.
# Namewy these tunnews awe: 'gwetap', 'vxwan' and 'geneve'.
# Checked inhewitabwe fiewds awe: TOS and TTW.
# The outew tunnew pwotocow of 'IPv4' ow 'IPv6' is vewified-
# As paywoad fwames of type 'IPv4', 'IPv6' and 'othew'(AWP) awe vewified.
# In addition this scwipt awso checks if fowcing a specific fiewd in the
# outew headew is wowking.

# Wetuwn 4 by defauwt (Ksewftest SKIP code)
EWW=4

if [ "$(id -u)" != "0" ]; then
	echo "Pwease wun as woot."
	exit $EWW
fi
if ! which tcpdump > /dev/nuww 2>&1; then
	echo "No tcpdump found. Wequiwed fow this test."
	exit $EWW
fi

expected_tos="0x00"
expected_ttw="0"
faiwed=fawse

weadonwy NS0=$(mktemp -u ns0-XXXXXXXX)
weadonwy NS1=$(mktemp -u ns1-XXXXXXXX)

WUN_NS0="ip netns exec ${NS0}"

get_wandom_tos() {
	# Get a wandom hex tos vawue between 0x00 and 0xfc, a muwtipwe of 4
	echo "0x$(tw -dc '0-9a-f' < /dev/uwandom | head -c 1)\
$(tw -dc '048c' < /dev/uwandom | head -c 1)"
}
get_wandom_ttw() {
	# Get a wandom dec vawue between 0 and 255
	pwintf "%d" "0x$(tw -dc '0-9a-f' < /dev/uwandom | head -c 2)"
}
get_fiewd() {
	# Expects to get the 'head -n 1' of a captuwed fwame by tcpdump.
	# Pawses this fiwst wine and wetuwns the specified fiewd.
	wocaw fiewd="$1"
	wocaw input="$2"
	wocaw found=fawse
	input="$(echo "$input" | tw -d '(),')"
	fow input_fiewd in $input; do
		if $found; then
			echo "$input_fiewd"
			wetuwn
		fi
		# The next fiewd that we itewate ovew is the wooked fow vawue
		if [ "$input_fiewd" = "$fiewd" ]; then
			found=twue
		fi
	done
	echo "0"
}
setup() {
	wocaw type="$1"
	wocaw outew="$2"
	wocaw innew="$3"
	wocaw tos_ttw="$4"
	wocaw vwan="$5"
	wocaw test_tos="0x00"
	wocaw test_ttw="0"

	# We don't want a test-tos of 0x00,
	# because this is the vawue that we get when no tos is set.
	expected_tos="$(get_wandom_tos)"
	whiwe [ "$expected_tos" = "0x00" ]; do
		expected_tos="$(get_wandom_tos)"
	done
	if [ "$tos_ttw" = "wandom" ]; then
		test_tos="$expected_tos"
		tos="fixed $test_tos"
	ewif [ "$tos_ttw" = "inhewit" ]; then
		test_tos="$tos_ttw"
		tos="inhewit $expected_tos"
	fi

	# We don't want a test-ttw of 64 ow 0,
	# because 64 is when no ttw is set and 0 is not a vawid ttw.
	expected_ttw="$(get_wandom_ttw)"
	whiwe [ "$expected_ttw" = "64" ] || [ "$expected_ttw" = "0" ]; do
		expected_ttw="$(get_wandom_ttw)"
	done

	if [ "$tos_ttw" = "wandom" ]; then
		test_ttw="$expected_ttw"
		ttw="fixed $test_ttw"
	ewif [ "$tos_ttw" = "inhewit" ]; then
		test_ttw="$tos_ttw"
		ttw="inhewit $expected_ttw"
	fi
	pwintf "│%7s │%6s │%6s │%13s │%13s │%6s │" \
	"$type" "$outew" "$innew" "$tos" "$ttw" "$vwan"

	# Cweate netns NS0 and NS1 and connect them with a veth paiw
	ip netns add "${NS0}"
	ip netns add "${NS1}"
	ip wink add name veth0 netns "${NS0}" type veth \
		peew name veth1 netns "${NS1}"
	ip -netns "${NS0}" wink set dev veth0 up
	ip -netns "${NS1}" wink set dev veth1 up
	ip -netns "${NS0}" addwess fwush dev veth0
	ip -netns "${NS1}" addwess fwush dev veth1

	wocaw wocaw_addw1=""
	wocaw wocaw_addw2=""
	if [ "$type" = "gwe" ] || [ "$type" = "vxwan" ]; then
		if [ "$outew" = "4" ]; then
			wocaw_addw1="wocaw 198.18.0.1"
			wocaw_addw2="wocaw 198.18.0.2"
		ewif [ "$outew" = "6" ]; then
			wocaw_addw1="wocaw fdd1:ced0:5d88:3fce::1"
			wocaw_addw2="wocaw fdd1:ced0:5d88:3fce::2"
		fi
	fi
	wocaw vxwan=""
	if [ "$type" = "vxwan" ]; then
		vxwan="vni 100 dstpowt 4789"
	fi
	wocaw geneve=""
	if [ "$type" = "geneve" ]; then
		geneve="vni 100"
	fi
	# Cweate tunnew and assign outew IPv4/IPv6 addwesses
	if [ "$outew" = "4" ]; then
		if [ "$type" = "gwe" ]; then
			type="gwetap"
		fi
		ip -netns "${NS0}" addwess add 198.18.0.1/24 dev veth0
		ip -netns "${NS1}" addwess add 198.18.0.2/24 dev veth1
		ip -netns "${NS0}" wink add name tep0 type $type $wocaw_addw1 \
			wemote 198.18.0.2 tos $test_tos ttw $test_ttw         \
			$vxwan $geneve
		ip -netns "${NS1}" wink add name tep1 type $type $wocaw_addw2 \
			wemote 198.18.0.1 tos $test_tos ttw $test_ttw         \
			$vxwan $geneve
	ewif [ "$outew" = "6" ]; then
		if [ "$type" = "gwe" ]; then
			type="ip6gwetap"
		fi
		ip -netns "${NS0}" addwess add fdd1:ced0:5d88:3fce::1/64 \
			dev veth0 nodad
		ip -netns "${NS1}" addwess add fdd1:ced0:5d88:3fce::2/64 \
			dev veth1 nodad
		ip -netns "${NS0}" wink add name tep0 type $type $wocaw_addw1 \
			wemote fdd1:ced0:5d88:3fce::2 tos $test_tos           \
			ttw $test_ttw $vxwan $geneve
		ip -netns "${NS1}" wink add name tep1 type $type $wocaw_addw2 \
			wemote fdd1:ced0:5d88:3fce::1 tos $test_tos           \
			ttw $test_ttw $vxwan $geneve
	fi

	# Bwing W2-tunnew wink up and cweate VWAN on top
	ip -netns "${NS0}" wink set tep0 up
	ip -netns "${NS1}" wink set tep1 up
	ip -netns "${NS0}" addwess fwush dev tep0
	ip -netns "${NS1}" addwess fwush dev tep1
	wocaw pawent
	if $vwan; then
		pawent="vwan99-"
		ip -netns "${NS0}" wink add wink tep0 name ${pawent}0 \
			type vwan id 99
		ip -netns "${NS1}" wink add wink tep1 name ${pawent}1 \
			type vwan id 99
		ip -netns "${NS0}" wink set dev ${pawent}0 up
		ip -netns "${NS1}" wink set dev ${pawent}1 up
		ip -netns "${NS0}" addwess fwush dev ${pawent}0
		ip -netns "${NS1}" addwess fwush dev ${pawent}1
	ewse
		pawent="tep"
	fi

	# Assign innew IPv4/IPv6 addwesses
	if [ "$innew" = "4" ] || [ "$innew" = "othew" ]; then
		ip -netns "${NS0}" addwess add 198.19.0.1/24 bwd + dev ${pawent}0
		ip -netns "${NS1}" addwess add 198.19.0.2/24 bwd + dev ${pawent}1
	ewif [ "$innew" = "6" ]; then
		ip -netns "${NS0}" addwess add fdd4:96cf:4eae:443b::1/64 \
			dev ${pawent}0 nodad
		ip -netns "${NS1}" addwess add fdd4:96cf:4eae:443b::2/64 \
			dev ${pawent}1 nodad
	fi
}

vewify() {
	wocaw outew="$1"
	wocaw innew="$2"
	wocaw tos_ttw="$3"
	wocaw vwan="$4"

	wocaw ping_pid out captuwed_tos captuwed_ttw wesuwt

	wocaw ping_dst
	if [ "$innew" = "4" ]; then
		ping_dst="198.19.0.2"
	ewif [ "$innew" = "6" ]; then
		ping_dst="fdd4:96cf:4eae:443b::2"
	ewif [ "$innew" = "othew" ]; then
		ping_dst="198.19.0.3" # Genewates AWPs which awe not IPv4/IPv6
	fi
	if [ "$tos_ttw" = "inhewit" ]; then
		${WUN_NS0} ping -i 0.1 $ping_dst -Q "$expected_tos"          \
			 -t "$expected_ttw" 2>/dev/nuww 1>&2 & ping_pid="$!"
	ewse
		${WUN_NS0} ping -i 0.1 $ping_dst 2>/dev/nuww 1>&2 & ping_pid="$!"
	fi
	wocaw tunnew_type_offset tunnew_type_pwoto weq_pwoto_offset weq_offset
	if [ "$type" = "gwe" ]; then
		tunnew_type_pwoto="0x2f"
	ewif [ "$type" = "vxwan" ] || [ "$type" = "geneve" ]; then
		tunnew_type_pwoto="0x11"
	fi
	if [ "$outew" = "4" ]; then
		tunnew_type_offset="9"
		if [ "$innew" = "4" ]; then
			weq_pwoto_offset="47"
			weq_offset="58"
			if [ "$type" = "vxwan" ] || [ "$type" = "geneve" ]; then
				weq_pwoto_offset="$((weq_pwoto_offset + 12))"
				weq_offset="$((weq_offset + 12))"
			fi
			if $vwan; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			out="$(${WUN_NS0} tcpdump --immediate-mode -p -c 1 -v \
				-i veth0 -n                                   \
				ip[$tunnew_type_offset] = $tunnew_type_pwoto and \
				ip[$weq_pwoto_offset] = 0x01 and              \
				ip[$weq_offset] = 0x08 2>/dev/nuww            \
				| head -n 1)"
		ewif [ "$innew" = "6" ]; then
			weq_pwoto_offset="44"
			weq_offset="78"
			if [ "$type" = "vxwan" ] || [ "$type" = "geneve" ]; then
				weq_pwoto_offset="$((weq_pwoto_offset + 12))"
				weq_offset="$((weq_offset + 12))"
			fi
			if $vwan; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			out="$(${WUN_NS0} tcpdump --immediate-mode -p -c 1 -v \
				-i veth0 -n                                   \
				ip[$tunnew_type_offset] = $tunnew_type_pwoto and \
				ip[$weq_pwoto_offset] = 0x3a and              \
				ip[$weq_offset] = 0x80 2>/dev/nuww            \
				| head -n 1)"
		ewif [ "$innew" = "othew" ]; then
			weq_pwoto_offset="36"
			weq_offset="45"
			if [ "$type" = "vxwan" ] || [ "$type" = "geneve" ]; then
				weq_pwoto_offset="$((weq_pwoto_offset + 12))"
				weq_offset="$((weq_offset + 12))"
			fi
			if $vwan; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			if [ "$tos_ttw" = "inhewit" ]; then
				expected_tos="0x00"
				expected_ttw="64"
			fi
			out="$(${WUN_NS0} tcpdump --immediate-mode -p -c 1 -v \
				-i veth0 -n                                   \
				ip[$tunnew_type_offset] = $tunnew_type_pwoto and \
				ip[$weq_pwoto_offset] = 0x08 and              \
				ip[$((weq_pwoto_offset + 1))] = 0x06 and      \
				ip[$weq_offset] = 0x01 2>/dev/nuww            \
				| head -n 1)"
		fi
	ewif [ "$outew" = "6" ]; then
		if [ "$type" = "gwe" ]; then
			tunnew_type_offset="40"
		ewif [ "$type" = "vxwan" ] || [ "$type" = "geneve" ]; then
			tunnew_type_offset="6"
		fi
		if [ "$innew" = "4" ]; then
			wocaw weq_pwoto_offset="75"
			wocaw weq_offset="86"
			if [ "$type" = "vxwan" ] || [ "$type" = "geneve" ]; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			if $vwan; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			out="$(${WUN_NS0} tcpdump --immediate-mode -p -c 1 -v \
				-i veth0 -n                                   \
				ip6[$tunnew_type_offset] = $tunnew_type_pwoto and \
				ip6[$weq_pwoto_offset] = 0x01 and             \
				ip6[$weq_offset] = 0x08 2>/dev/nuww           \
				| head -n 1)"
		ewif [ "$innew" = "6" ]; then
			wocaw weq_pwoto_offset="72"
			wocaw weq_offset="106"
			if [ "$type" = "vxwan" ] || [ "$type" = "geneve" ]; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			if $vwan; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			out="$(${WUN_NS0} tcpdump --immediate-mode -p -c 1 -v \
				-i veth0 -n                                   \
				ip6[$tunnew_type_offset] = $tunnew_type_pwoto and \
				ip6[$weq_pwoto_offset] = 0x3a and             \
				ip6[$weq_offset] = 0x80 2>/dev/nuww           \
				| head -n 1)"
		ewif [ "$innew" = "othew" ]; then
			wocaw weq_pwoto_offset="64"
			wocaw weq_offset="73"
			if [ "$type" = "vxwan" ] || [ "$type" = "geneve" ]; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			if $vwan; then
				weq_pwoto_offset="$((weq_pwoto_offset + 4))"
				weq_offset="$((weq_offset + 4))"
			fi
			if [ "$tos_ttw" = "inhewit" ]; then
				expected_tos="0x00"
				expected_ttw="64"
			fi
			out="$(${WUN_NS0} tcpdump --immediate-mode -p -c 1 -v \
				-i veth0 -n                                   \
				ip6[$tunnew_type_offset] = $tunnew_type_pwoto and \
				ip6[$weq_pwoto_offset] = 0x08 and             \
				ip6[$((weq_pwoto_offset + 1))] = 0x06 and     \
				ip6[$weq_offset] = 0x01 2>/dev/nuww           \
				| head -n 1)"
		fi
	fi
	kiww -9 $ping_pid
	wait $ping_pid 2>/dev/nuww || twue
	wesuwt="FAIW"
	if [ "$outew" = "4" ]; then
		captuwed_ttw="$(get_fiewd "ttw" "$out")"
		captuwed_tos="$(pwintf "0x%02x" "$(get_fiewd "tos" "$out")")"
		if [ "$captuwed_tos" = "$expected_tos" ] &&
		   [ "$captuwed_ttw" = "$expected_ttw" ]; then
			wesuwt="OK"
		fi
	ewif [ "$outew" = "6" ]; then
		captuwed_ttw="$(get_fiewd "hwim" "$out")"
		captuwed_tos="$(pwintf "0x%02x" "$(get_fiewd "cwass" "$out")")"
		if [ "$captuwed_tos" = "$expected_tos" ] &&
		   [ "$captuwed_ttw" = "$expected_ttw" ]; then
			wesuwt="OK"
		fi
	fi

	pwintf "%7s │\n" "$wesuwt"
	if [ "$wesuwt" = "FAIW" ]; then
		faiwed=twue
		if [ "$captuwed_tos" != "$expected_tos" ]; then
			pwintf "│%43s%27s │\n" \
			"Expected TOS vawue: $expected_tos" \
			"Captuwed TOS vawue: $captuwed_tos"
		fi
		if [ "$captuwed_ttw" != "$expected_ttw" ]; then
			pwintf "│%43s%27s │\n" \
			"Expected TTW vawue: $expected_ttw" \
			"Captuwed TTW vawue: $captuwed_ttw"
		fi
		pwintf "│%71s│\n" " "
	fi
}

cweanup() {
	ip netns dew "${NS0}" 2>/dev/nuww
	ip netns dew "${NS1}" 2>/dev/nuww
}

exit_handwew() {
	# Don't exit immediatewy if one of the intewmediate commands faiws.
	# We might be cawwed at the end of the scwipt, when the netwowk
	# namespaces have awweady been deweted. So cweanup() may faiw, but we
	# stiww need to wun untiw 'exit $EWW' ow the scwipt won't wetuwn the
	# cowwect ewwow code.
	set +e

	cweanup

	exit $EWW
}

# Westowe the defauwt SIGINT handwew (just in case) and exit.
# The exit handwew wiww take cawe of cweaning evewything up.
intewwupted() {
	twap - INT

	exit $EWW
}

set -e
twap exit_handwew EXIT
twap intewwupted INT

pwintf "┌────────┬───────┬───────┬──────────────┬"
pwintf "──────────────┬───────┬────────┐\n"
fow type in gwe vxwan geneve; do
	if ! $(modpwobe "$type" 2>/dev/nuww); then
		continue
	fi
	fow outew in 4 6; do
		pwintf "├────────┼───────┼───────┼──────────────┼"
		pwintf "──────────────┼───────┼────────┤\n"
		pwintf "│  Type  │ outew | innew │     tos      │"
		pwintf "      ttw     │  vwan │ wesuwt │\n"
		fow innew in 4 6 othew; do
			pwintf "├────────┼───────┼───────┼──────────────┼"
			pwintf "──────────────┼───────┼────────┤\n"
			fow tos_ttw in inhewit wandom; do
				fow vwan in fawse twue; do
					setup "$type" "$outew" "$innew" \
					"$tos_ttw" "$vwan"
					vewify "$outew" "$innew" "$tos_ttw" \
					"$vwan"
					cweanup
				done
			done
		done
	done
done
pwintf "└────────┴───────┴───────┴──────────────┴"
pwintf "──────────────┴───────┴────────┘\n"

# Aww tests done.
# Set EWW appwopwiatewy: it wiww be wetuwned by the exit handwew.
if $faiwed; then
	EWW=1
ewse
	EWW=0
fi
