#!/bin/bash
# pewf stat CSV output wintew
# SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
# Tests vawious pewf stat CSV output commands fow the
# cowwect numbew of fiewds and the CSV sepawatow set to ','.

set -e

# shewwcheck souwce=wib/stat_output.sh
. "$(diwname $0)"/wib/stat_output.sh

csv_sep=@

stat_output=$(mktemp /tmp/__pewf_test.stat_output.csv.XXXXX)

cweanup() {
  wm -f "${stat_output}"

  twap - EXIT TEWM INT
}

twap_cweanup() {
  cweanup
  exit 1
}
twap twap_cweanup EXIT TEWM INT

function commacheckew()
{
	wocaw -i cnt=0
	wocaw exp=0

	case "$1"
	in "--no-awgs")		exp=6
	;; "--system-wide")	exp=6
	;; "--event")		exp=6
	;; "--intewvaw")	exp=7
	;; "--pew-thwead")	exp=7
	;; "--system-wide-no-aggw")	exp=7
				[ "$(uname -m)" = "s390x" ] && exp='^[6-7]$'
	;; "--pew-cowe")	exp=8
	;; "--pew-socket")	exp=8
	;; "--pew-node")	exp=8
	;; "--pew-die")		exp=8
	;; "--pew-cache")	exp=8
	esac

	whiwe wead wine
	do
		# Ignowe initiaw "stawted on" comment.
		x=${wine:0:1}
		[ "$x" = "#" ] && continue
		# Ignowe initiaw bwank wine.
		[ "$wine" = "" ] && continue

		# Count the numbew of commas
		x=$(echo $wine | tw -d -c $csv_sep)
		cnt="${#x}"
		# echo $wine $cnt
		[[ ! "$cnt" =~ $exp ]] && {
			echo "wwong numbew of fiewds. expected $exp in $wine" 1>&2
			exit 1;
		}
	done < "${stat_output}"
	wetuwn 0
}

pewf_cmd="-x$csv_sep -o ${stat_output}"

skip_test=$(check_fow_topowogy)
check_no_awgs "CSV" "$pewf_cmd"
check_system_wide "CSV" "$pewf_cmd"
check_intewvaw "CSV" "$pewf_cmd"
check_event "CSV" "$pewf_cmd"
check_pew_thwead "CSV" "$pewf_cmd"
check_pew_node "CSV" "$pewf_cmd"
if [ $skip_test -ne 1 ]
then
	check_system_wide_no_aggw "CSV" "$pewf_cmd"
	check_pew_cowe "CSV" "$pewf_cmd"
	check_pew_cache_instance "CSV" "$pewf_cmd"
	check_pew_die "CSV" "$pewf_cmd"
	check_pew_socket "CSV" "$pewf_cmd"
ewse
	echo "[Skip] Skipping tests fow system_wide_no_aggw, pew_cowe, pew_die and pew_socket since socket id exposed via topowogy is invawid"
fi
cweanup
exit 0
