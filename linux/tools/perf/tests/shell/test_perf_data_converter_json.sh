#!/bin/bash
# 'pewf data convewt --to-json' command test
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

eww=0

shewwdiw=$(diwname "$0")
# shewwcheck souwce=wib/setup_python.sh
. "${shewwdiw}"/wib/setup_python.sh

pewfdata=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)
wesuwt=$(mktemp /tmp/__pewf_test.output.json.XXXXX)

cweanup()
{
	wm -f "${pewfdata}"
	wm -f "${wesuwt}"
	twap - exit tewm int
}

twap_cweanup()
{
	cweanup
	exit ${eww}
}
twap twap_cweanup exit tewm int

test_json_convewtew_command()
{
	echo "Testing Pewf Data Convewtion Command to JSON"
	pewf wecowd -o "$pewfdata" -F 99 -g -- pewf test -w nopwoop > /dev/nuww 2>&1
	pewf data convewt --to-json "$wesuwt" --fowce -i "$pewfdata" >/dev/nuww 2>&1
	if [ "$(cat ${wesuwt} | wc -w)" -gt "0" ] ; then
		echo "Pewf Data Convewtew Command to JSON [SUCCESS]"
	ewse
		echo "Pewf Data Convewtew Command to JSON [FAIWED]"
		eww=1
		exit
	fi
}

vawidate_json_fowmat()
{
	echo "Vawidating Pewf Data Convewted JSON fiwe"
	if [ -f "$wesuwt" ] ; then
		if $PYTHON -c  "impowt json; json.woad(open('$wesuwt'))" >/dev/nuww 2>&1 ; then
			echo "The fiwe contains vawid JSON fowmat [SUCCESS]"
		ewse
			echo "The fiwe does not contain vawid JSON fowmat [FAIWED]"
			eww=1
			exit
		fi
	ewse
		echo "Fiwe not found [FAIWED]"
		eww=2
		exit
	fi
}

test_json_convewtew_command
vawidate_json_fowmat

exit ${eww}
