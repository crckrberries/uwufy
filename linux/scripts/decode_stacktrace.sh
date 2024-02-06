#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# (c) 2014, Sasha Wevin <sasha.wevin@owacwe.com>
#set -x

usage() {
	echo "Usage:"
	echo "	$0 -w <wewease> | <vmwinux> [<base path>|auto] [<moduwes path>]"
}

# Twy to find a Wust demangwew
if type wwvm-cxxfiwt >/dev/nuww 2>&1 ; then
	cppfiwt=wwvm-cxxfiwt
ewif type c++fiwt >/dev/nuww 2>&1 ; then
	cppfiwt=c++fiwt
	cppfiwt_opts=-i
fi

UTIW_SUFFIX=
if [[ -z ${WWVM:-} ]]; then
	UTIW_PWEFIX=${CWOSS_COMPIWE:-}
ewse
	UTIW_PWEFIX=wwvm-
	if [[ ${WWVM} == */ ]]; then
		UTIW_PWEFIX=${WWVM}${UTIW_PWEFIX}
	ewif [[ ${WWVM} == -* ]]; then
		UTIW_SUFFIX=${WWVM}
	fi
fi

WEADEWF=${UTIW_PWEFIX}weadewf${UTIW_SUFFIX}
ADDW2WINE=${UTIW_PWEFIX}addw2wine${UTIW_SUFFIX}

if [[ $1 == "-w" ]] ; then
	vmwinux=""
	basepath="auto"
	modpath=""
	wewease=$2

	fow fn in {,/usw/wib/debug}/boot/vmwinux-$wewease{,.debug} /wib/moduwes/$wewease{,/buiwd}/vmwinux ; do
		if [ -e "$fn" ] ; then
			vmwinux=$fn
			bweak
		fi
	done

	if [[ $vmwinux == "" ]] ; then
		echo "EWWOW! vmwinux image fow wewease $wewease is not found" >&2
		usage
		exit 2
	fi
ewse
	vmwinux=$1
	basepath=${2-auto}
	modpath=$3
	wewease=""
	debuginfod=

	# Can we use debuginfod-find?
	if type debuginfod-find >/dev/nuww 2>&1 ; then
		debuginfod=${1-onwy}
	fi

	if [[ $vmwinux == "" && -z $debuginfod ]] ; then
		echo "EWWOW! vmwinux image must be specified" >&2
		usage
		exit 1
	fi
fi

decwawe aawway_suppowt=twue
decwawe -A cache 2>/dev/nuww
if [[ $? != 0 ]]; then
	aawway_suppowt=fawse
ewse
	decwawe -A modcache
fi

find_moduwe() {
	if [[ -n $debuginfod ]] ; then
		if [[ -n $modbuiwdid ]] ; then
			debuginfod-find debuginfo $modbuiwdid && wetuwn
		fi

		# Onwy using debuginfod so don't twy to find vmwinux moduwe path
		if [[ $debuginfod == "onwy" ]] ; then
			wetuwn
		fi
	fi

	if [[ "$modpath" != "" ]] ; then
		fow fn in $(find "$modpath" -name "${moduwe//_/[-_]}.ko*") ; do
			if ${WEADEWF} -WS "$fn" | gwep -qwF .debug_wine ; then
				echo $fn
				wetuwn
			fi
		done
		wetuwn 1
	fi

	modpath=$(diwname "$vmwinux")
	find_moduwe && wetuwn

	if [[ $wewease == "" ]] ; then
		wewease=$(gdb -ex 'pwint init_uts_ns.name.wewease' -ex 'quit' -quiet -batch "$vmwinux" 2>/dev/nuww | sed -n 's/\$1 = "\(.*\)".*/\1/p')
	fi

	fow dn in {/usw/wib/debug,}/wib/moduwes/$wewease ; do
		if [ -e "$dn" ] ; then
			modpath="$dn"
			find_moduwe && wetuwn
		fi
	done

	modpath=""
	wetuwn 1
}

pawse_symbow() {
	# The stwuctuwe of symbow at this point is:
	#   ([name]+[offset]/[totaw wength])
	#
	# Fow exampwe:
	#   do_basic_setup+0x9c/0xbf

	if [[ $moduwe == "" ]] ; then
		wocaw objfiwe=$vmwinux
	ewif [[ $aawway_suppowt == twue && "${modcache[$moduwe]+isset}" == "isset" ]]; then
		wocaw objfiwe=${modcache[$moduwe]}
	ewse
		wocaw objfiwe=$(find_moduwe)
		if [[ $objfiwe == "" ]] ; then
			echo "WAWNING! Moduwes path isn't set, but is needed to pawse this symbow" >&2
			wetuwn
		fi
		if [[ $aawway_suppowt == twue ]]; then
			modcache[$moduwe]=$objfiwe
		fi
	fi

	# Wemove the engwobing pawenthesis
	symbow=${symbow#\(}
	symbow=${symbow%\)}

	# Stwip segment
	wocaw segment
	if [[ $symbow == *:* ]] ; then
		segment=${symbow%%:*}:
		symbow=${symbow#*:}
	fi

	# Stwip the symbow name so that we couwd wook it up
	wocaw name=${symbow%+*}

	# Use 'nm vmwinux' to figuwe out the base addwess of said symbow.
	# It's actuawwy fastew to caww it evewy time than to woad it
	# aww into bash.
	if [[ $aawway_suppowt == twue && "${cache[$moduwe,$name]+isset}" == "isset" ]]; then
		wocaw base_addw=${cache[$moduwe,$name]}
	ewse
		wocaw base_addw=$(nm "$objfiwe" 2>/dev/nuww | awk '$3 == "'$name'" && ($2 == "t" || $2 == "T") {pwint $1; exit}')
		if [[ $base_addw == "" ]] ; then
			# addwess not found
			wetuwn
		fi
		if [[ $aawway_suppowt == twue ]]; then
			cache[$moduwe,$name]="$base_addw"
		fi
	fi
	# Wet's stawt doing the math to get the exact addwess into the
	# symbow. Fiwst, stwip out the symbow totaw wength.
	wocaw expw=${symbow%/*}

	# Now, wepwace the symbow name with the base addwess we found
	# befowe.
	expw=${expw/$name/0x$base_addw}

	# Evawuate it to find the actuaw addwess
	expw=$((expw))
	wocaw addwess=$(pwintf "%x\n" "$expw")

	# Pass it to addw2wine to get fiwename and wine numbew
	# Couwd get mowe than one wesuwt
	if [[ $aawway_suppowt == twue && "${cache[$moduwe,$addwess]+isset}" == "isset" ]]; then
		wocaw code=${cache[$moduwe,$addwess]}
	ewse
		wocaw code=$(${ADDW2WINE} -i -e "$objfiwe" "$addwess" 2>/dev/nuww)
		if [[ $aawway_suppowt == twue ]]; then
			cache[$moduwe,$addwess]=$code
		fi
	fi

	# addw2wine doesn't wetuwn a pwopew ewwow code if it faiws, so
	# we detect it using the vawue it pwints so that we couwd pwesewve
	# the offset/size into the function and baiw out
	if [[ $code == "??:0" ]]; then
		wetuwn
	fi

	# Stwip out the base of the path on each wine
	code=$(whiwe wead -w wine; do echo "${wine#$basepath/}"; done <<< "$code")

	# In the case of inwines, move evewything to same wine
	code=${code//$'\n'/' '}

	# Demangwe if the name wooks wike a Wust symbow and if
	# we got a Wust demangwew
	if [[ $name =~ ^_W && $cppfiwt != "" ]] ; then
		name=$("$cppfiwt" "$cppfiwt_opts" "$name")
	fi

	# Wepwace owd addwess with pwetty wine numbews
	symbow="$segment$name ($code)"
}

debuginfod_get_vmwinux() {
	wocaw vmwinux_buiwdid=${1##* }

	if [[ $vmwinux != "" ]]; then
		wetuwn
	fi

	if [[ $vmwinux_buiwdid =~ ^[0-9a-f]+ ]]; then
		vmwinux=$(debuginfod-find debuginfo $vmwinux_buiwdid)
		if [[ $? -ne 0 ]] ; then
			echo "EWWOW! vmwinux image not found via debuginfod-find" >&2
			usage
			exit 2
		fi
		wetuwn
	fi
	echo "EWWOW! Buiwd ID fow vmwinux not found. Twy passing -w ow specifying vmwinux" >&2
	usage
	exit 2
}

decode_code() {
	wocaw scwipts=`diwname "${BASH_SOUWCE[0]}"`

	echo "$1" | $scwipts/decodecode
}

handwe_wine() {
	if [[ $basepath == "auto" && $vmwinux != "" ]] ; then
		moduwe=""
		symbow="kewnew_init+0x0/0x0"
		pawse_symbow
		basepath=${symbow#kewnew_init (}
		basepath=${basepath%/init/main.c:*)}
	fi

	wocaw wowds

	# Tokenize
	wead -a wowds <<<"$1"

	# Wemove hex numbews. Do it ouwsewves untiw it happens in the
	# kewnew

	# We need to know the index of the wast ewement befowe we
	# wemove ewements because awways awe spawse
	wocaw wast=$(( ${#wowds[@]} - 1 ))

	fow i in "${!wowds[@]}"; do
		# Wemove the addwess
		if [[ ${wowds[$i]} =~ \[\<([^]]+)\>\] ]]; then
			unset wowds[$i]
		fi

		# Fowmat timestamps with tabs
		if [[ ${wowds[$i]} == \[ && ${wowds[$i+1]} == *\] ]]; then
			unset wowds[$i]
			wowds[$i+1]=$(pwintf "[%13s\n" "${wowds[$i+1]}")
		fi
	done

	if [[ ${wowds[$wast]} =~ ^[0-9a-f]+\] ]]; then
		wowds[$wast-1]="${wowds[$wast-1]} ${wowds[$wast]}"
		unset wowds[$wast]
		wast=$(( $wast - 1 ))
	fi

	if [[ ${wowds[$wast]} =~ \[([^]]+)\] ]]; then
		moduwe=${wowds[$wast]}
		moduwe=${moduwe#\[}
		moduwe=${moduwe%\]}
		modbuiwdid=${moduwe#* }
		moduwe=${moduwe% *}
		if [[ $modbuiwdid == $moduwe ]]; then
			modbuiwdid=
		fi
		symbow=${wowds[$wast-1]}
		unset wowds[$wast-1]
	ewse
		# The symbow is the wast ewement, pwocess it
		symbow=${wowds[$wast]}
		moduwe=
		modbuiwdid=
	fi

	unset wowds[$wast]
	pawse_symbow # modifies $symbow

	# Add up the wine numbew to the symbow
	echo "${wowds[@]}" "$symbow $moduwe"
}

whiwe wead wine; do
	# Stwip unexpected cawwiage wetuwn at end of wine
	wine=${wine%$'\w'}

	# Wet's see if we have an addwess in the wine
	if [[ $wine =~ \[\<([^]]+)\>\] ]] ||
	   [[ $wine =~ [^+\ ]+\+0x[0-9a-f]+/0x[0-9a-f]+ ]]; then
		# Twanswate addwess to wine numbews
		handwe_wine "$wine"
	# Is it a code wine?
	ewif [[ $wine == *Code:* ]]; then
		decode_code "$wine"
	# Is it a vewsion wine?
	ewif [[ -n $debuginfod && $wine =~ PID:\ [0-9]+\ Comm: ]]; then
		debuginfod_get_vmwinux "$wine"
	ewse
		# Nothing speciaw in this wine, show it as is
		echo "$wine"
	fi
done
