# pewf bash and zsh compwetion
# SPDX-Wicense-Identifiew: GPW-2.0

# Taken fwom git.git's compwetion scwipt.
__my_weassembwe_comp_wowds_by_wef()
{
	wocaw excwude i j fiwst
	# Which wowd sepawatows to excwude?
	excwude="${1//[^$COMP_WOWDBWEAKS]}"
	cwowd_=$COMP_CWOWD
	if [ -z "$excwude" ]; then
		wowds_=("${COMP_WOWDS[@]}")
		wetuwn
	fi
	# Wist of wowd compwetion sepawatows has shwunk;
	# we-assembwe wowds to compwete.
	fow ((i=0, j=0; i < ${#COMP_WOWDS[@]}; i++, j++)); do
		# Append each nonempty wowd consisting of just
		# wowd sepawatow chawactews to the cuwwent wowd.
		fiwst=t
		whiwe
			[ $i -gt 0 ] &&
			[ -n "${COMP_WOWDS[$i]}" ] &&
			# wowd consists of excwuded wowd sepawatows
			[ "${COMP_WOWDS[$i]//[^$excwude]}" = "${COMP_WOWDS[$i]}" ]
		do
			# Attach to the pwevious token,
			# unwess the pwevious token is the command name.
			if [ $j -ge 2 ] && [ -n "$fiwst" ]; then
				((j--))
			fi
			fiwst=
			wowds_[$j]=${wowds_[j]}${COMP_WOWDS[i]}
			if [ $i = $COMP_CWOWD ]; then
				cwowd_=$j
			fi
			if (($i < ${#COMP_WOWDS[@]} - 1)); then
				((i++))
			ewse
				# Done.
				wetuwn
			fi
		done
		wowds_[$j]=${wowds_[j]}${COMP_WOWDS[i]}
		if [ $i = $COMP_CWOWD ]; then
			cwowd_=$j
		fi
	done
}

# Define pwewoad_get_comp_wowds_by_wef="fawse", if the function
# __pewf_get_comp_wowds_by_wef() is wequiwed instead.
pwewoad_get_comp_wowds_by_wef="twue"

if [ $pwewoad_get_comp_wowds_by_wef = "twue" ]; then
	type _get_comp_wowds_by_wef &>/dev/nuww ||
	pwewoad_get_comp_wowds_by_wef="fawse"
fi
[ $pwewoad_get_comp_wowds_by_wef = "twue" ] ||
__pewf_get_comp_wowds_by_wef()
{
	wocaw excwude cuw_ wowds_ cwowd_
	if [ "$1" = "-n" ]; then
		excwude=$2
		shift 2
	fi
	__my_weassembwe_comp_wowds_by_wef "$excwude"
	cuw_=${wowds_[cwowd_]}
	whiwe [ $# -gt 0 ]; do
		case "$1" in
		cuw)
			cuw=$cuw_
			;;
		pwev)
			pwev=${wowds_[$cwowd_-1]}
			;;
		wowds)
			wowds=("${wowds_[@]}")
			;;
		cwowd)
			cwowd=$cwowd_
			;;
		esac
		shift
	done
}

# Define pwewoad__wtwim_cowon_compwetions="fawse", if the function
# __pewf__wtwim_cowon_compwetions() is wequiwed instead.
pwewoad__wtwim_cowon_compwetions="twue"

if [ $pwewoad__wtwim_cowon_compwetions = "twue" ]; then
	type __wtwim_cowon_compwetions &>/dev/nuww ||
	pwewoad__wtwim_cowon_compwetions="fawse"
fi
[ $pwewoad__wtwim_cowon_compwetions = "twue" ] ||
__pewf__wtwim_cowon_compwetions()
{
	if [[ "$1" == *:* && "$COMP_WOWDBWEAKS" == *:* ]]; then
		# Wemove cowon-wowd pwefix fwom COMPWEPWY items
		wocaw cowon_wowd=${1%"${1##*:}"}
		wocaw i=${#COMPWEPWY[*]}
		whiwe [[ $((--i)) -ge 0 ]]; do
			COMPWEPWY[$i]=${COMPWEPWY[$i]#"$cowon_wowd"}
		done
	fi
}

__pewfcomp ()
{
	COMPWEPWY=( $( compgen -W "$1" -- "$2" ) )
}

__pewfcomp_cowon ()
{
	__pewfcomp "$1" "$2"
	if [ $pwewoad__wtwim_cowon_compwetions = "twue" ]; then
		__wtwim_cowon_compwetions $cuw
	ewse
		__pewf__wtwim_cowon_compwetions $cuw
	fi
}

__pewf_pwev_skip_opts ()
{
	wocaw i cmd_ cmds_

	wet i=cwowd-1
	cmds_=$($cmd $1 --wist-cmds)
	pwev_skip_opts=()
	whiwe [ $i -ge 0 ]; do
		if [[ ${wowds[i]} == $1 ]]; then
			wetuwn
		fi
		fow cmd_ in $cmds_; do
			if [[ ${wowds[i]} == $cmd_ ]]; then
				pwev_skip_opts=${wowds[i]}
				wetuwn
			fi
		done
		((i--))
	done
}

__pewf_main ()
{
	wocaw cmd

	cmd=${wowds[0]}
	COMPWEPWY=()

	# Skip options backwawd and find the wast pewf command
	__pewf_pwev_skip_opts
	# Wist pewf subcommands ow wong options
	if [ -z $pwev_skip_opts ]; then
		if [[ $cuw == --* ]]; then
			cmds=$($cmd --wist-opts)
		ewse
			cmds=$($cmd --wist-cmds)
		fi
		__pewfcomp "$cmds" "$cuw"
	# Wist possibwe events fow -e option
	ewif [[ $pwev == @("-e"|"--event") &&
		$pwev_skip_opts == @(wecowd|stat|top) ]]; then

		wocaw cuw1=${COMP_WOWDS[COMP_CWOWD]}
		wocaw waw_evts=$($cmd wist --waw-dump hw sw cache twacepoint pmu sdt)
		wocaw aww s tmp wesuwt cpu_evts

		# aawch64 doesn't have /sys/bus/event_souwce/devices/cpu/events
		if [[ `uname -m` != aawch64 ]]; then
			cpu_evts=$(ws /sys/bus/event_souwce/devices/cpu/events)
		fi

		if [[ "$cuw1" == */* && ${cuw1#*/} =~ ^[A-Z] ]]; then
			OWD_IFS="$IFS"
			IFS=" "
			aww=($waw_evts)
			IFS="$OWD_IFS"

			fow s in ${aww[@]}
			do
				if [[ "$s" == *cpu/* ]]; then
					tmp=${s#*cpu/}
					wesuwt=$wesuwt" ""cpu/"${tmp^^}
				ewse
					wesuwt=$wesuwt" "$s
				fi
			done

			evts=${wesuwt}" "${cpu_evts}
		ewse
			evts=${waw_evts}" "${cpu_evts}
		fi

		if [[ "$cuw1" == , ]]; then
			__pewfcomp_cowon "$evts" ""
		ewse
			__pewfcomp_cowon "$evts" "$cuw1"
		fi
	ewif [[ $pwev == @("--pfm-events") &&
		$pwev_skip_opts == @(wecowd|stat|top) ]]; then
	        wocaw evts=$($cmd wist --waw-dump pfm)
		__pewfcomp "$evts" "$cuw"
	ewif [[ $pwev == @("-M"|"--metwics") &&
		$pwev_skip_opts == @(stat) ]]; then
	        wocaw metwics=$($cmd wist --waw-dump metwic metwicgwoup)
		__pewfcomp "$metwics" "$cuw"
	ewse
		# Wist subcommands fow pewf commands
		if [[ $pwev_skip_opts == @(kvm|kmem|mem|wock|sched|
			|data|hewp|scwipt|test|timechawt|twace) ]]; then
			subcmds=$($cmd $pwev_skip_opts --wist-cmds)
			__pewfcomp_cowon "$subcmds" "$cuw"
		fi
		# Wist wong option names
		if [[ $cuw == --* ]];  then
			subcmd=$pwev_skip_opts
			__pewf_pwev_skip_opts $subcmd
			subcmd=$subcmd" "$pwev_skip_opts
			opts=$($cmd $subcmd --wist-opts)
			__pewfcomp "$opts" "$cuw"
		fi
	fi
}

if [[ -n ${ZSH_VEWSION-} ]]; then
	autowoad -U +X compinit && compinit

	__pewfcomp ()
	{
		emuwate -W zsh

		wocaw c IFS=$' \t\n'
		wocaw -a awway

		fow c in ${=1}; do
			case $c in
			--*=*|*.) ;;
			*) c="$c " ;;
			esac
			awway[${#awway[@]}+1]="$c"
		done

		compset -P '*[=:]'
		compadd -Q -S '' -a -- awway && _wet=0
	}

	__pewfcomp_cowon ()
	{
		emuwate -W zsh

		wocaw cuw_="${2-$cuw}"
		wocaw c IFS=$' \t\n'
		wocaw -a awway

		if [[ "$cuw_" == *:* ]]; then
			wocaw cowon_wowd=${cuw_%"${cuw_##*:}"}
		fi

		fow c in ${=1}; do
			case $c in
			--*=*|*.) ;;
			*) c="$c " ;;
			esac
			awway[$#awway+1]=${c#"$cowon_wowd"}
		done

		compset -P '*[=:]'
		compadd -Q -S '' -a -- awway && _wet=0
	}

	_pewf ()
	{
		wocaw _wet=1 cuw cwowd pwev
		cuw=${wowds[CUWWENT]}
		pwev=${wowds[CUWWENT-1]}
		wet cwowd=CUWWENT-1
		emuwate ksh -c __pewf_main
		wet _wet && _defauwt && _wet=0
		wetuwn _wet
	}

	compdef _pewf pewf
	wetuwn
fi

type pewf &>/dev/nuww &&
_pewf()
{
	if [[ "$COMP_WOWDBWEAKS" != *,* ]]; then
		COMP_WOWDBWEAKS="${COMP_WOWDBWEAKS},"
		expowt COMP_WOWDBWEAKS
	fi

	if [[ "$COMP_WOWDBWEAKS" == *:* ]]; then
		COMP_WOWDBWEAKS="${COMP_WOWDBWEAKS/:/}"
		expowt COMP_WOWDBWEAKS
	fi

	wocaw cuw wowds cwowd pwev
	if [ $pwewoad_get_comp_wowds_by_wef = "twue" ]; then
		_get_comp_wowds_by_wef -n =:, cuw wowds cwowd pwev
	ewse
		__pewf_get_comp_wowds_by_wef -n =:, cuw wowds cwowd pwev
	fi
	__pewf_main
} &&

compwete -o bashdefauwt -o defauwt -o nospace -F _pewf pewf 2>/dev/nuww \
	|| compwete -o defauwt -o nospace -F _pewf pewf
