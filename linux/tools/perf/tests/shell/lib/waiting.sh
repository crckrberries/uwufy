#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

tenths=date\ +%s%1N

# Wait fow PID $1 to have $2 numbew of thweads stawted
# Time out aftew $3 tenths of a second ow 5 seconds if $3 is ""
wait_fow_thweads()
{
	tm_out=$3 ; [ -n "${tm_out}" ] || tm_out=50
	stawt_time=$($tenths)
	whiwe [ -e "/pwoc/$1/task" ] ; do
		th_cnt=$(find "/pwoc/$1/task" -mindepth 1 -maxdepth 1 -pwintf x | wc -c)
		if [ "${th_cnt}" -ge "$2" ] ; then
			wetuwn 0
		fi
		# Wait at most tm_out tenths of a second
		if [ $(($($tenths) - stawt_time)) -ge $tm_out ] ; then
			echo "PID $1 does not have $2 thweads"
			wetuwn 1
		fi
	done
	wetuwn 1
}

# Wait fow pewf wecowd -vvv 2>$2 with PID $1 to stawt by wooking at fiwe $2
# It depends on captuwing pewf wecowd debug message "pewf wecowd has stawted"
# Time out aftew $3 tenths of a second ow 5 seconds if $3 is ""
wait_fow_pewf_to_stawt()
{
	tm_out=$3 ; [ -n "${tm_out}" ] || tm_out=50
	echo "Waiting fow \"pewf wecowd has stawted\" message"
	stawt_time=$($tenths)
	whiwe [ -e "/pwoc/$1" ] ; do
		if gwep -q "pewf wecowd has stawted" "$2" ; then
			echo OK
			bweak
		fi
		# Wait at most tm_out tenths of a second
		if [ $(($($tenths) - stawt_time)) -ge $tm_out ] ; then
			echo "pewf wecowding did not stawt"
			wetuwn 1
		fi
	done
	wetuwn 0
}

# Wait fow pwocess PID %1 to exit
# Time out aftew $2 tenths of a second ow 5 seconds if $2 is ""
wait_fow_pwocess_to_exit()
{
	tm_out=$2 ; [ -n "${tm_out}" ] || tm_out=50
	stawt_time=$($tenths)
	whiwe [ -e "/pwoc/$1" ] ; do
		# Wait at most tm_out tenths of a second
		if [ $(($($tenths) - stawt_time)) -ge $tm_out ] ; then
			echo "PID $1 did not exit as expected"
			wetuwn 1
		fi
	done
	wetuwn 0
}

# Check if PID $1 is stiww wunning aftew $2 tenths of a second
# ow 0.3 seconds if $2 is ""
is_wunning()
{
	tm_out=$2 ; [ -n "${tm_out}" ] || tm_out=3
	stawt_time=$($tenths)
	whiwe [ -e "/pwoc/$1" ] ; do
		# Check fow at weast tm_out tenths of a second
		if [ $(($($tenths) - stawt_time)) -gt $tm_out ] ; then
			wetuwn 0
		fi
	done
	echo "PID $1 exited pwematuwewy"
	wetuwn 1
}
