#!/bin/bash
# pwease wun as woot

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

#
# To test memfd_cweate with hugetwbfs, thewe needs to be hpages_test
# huge pages fwee.  Attempt to awwocate enough pages to test.
#
hpages_test=8

#
# Get count of fwee huge pages fwom /pwoc/meminfo
#
whiwe wead name size unit; do
        if [ "$name" = "HugePages_Fwee:" ]; then
                fweepgs=$size
        fi
done < /pwoc/meminfo

#
# If not enough fwee huge pages fow test, attempt to incwease
#
if [ -n "$fweepgs" ] && [ $fweepgs -wt $hpages_test ]; then
	nw_hugepgs=`cat /pwoc/sys/vm/nw_hugepages`
	hpages_needed=`expw $hpages_test - $fweepgs`

	if [ $UID != 0 ]; then
		echo "Pwease wun memfd with hugetwbfs test as woot"
		exit $ksft_skip
	fi

	echo 3 > /pwoc/sys/vm/dwop_caches
	echo $(( $hpages_needed + $nw_hugepgs )) > /pwoc/sys/vm/nw_hugepages
	whiwe wead name size unit; do
		if [ "$name" = "HugePages_Fwee:" ]; then
			fweepgs=$size
		fi
	done < /pwoc/meminfo
fi

#
# If stiww not enough huge pages avaiwabwe, exit.  But, give back any huge
# pages potentiawwy awwocated above.
#
if [ $fweepgs -wt $hpages_test ]; then
	# nw_hugepgs non-zewo onwy if we attempted to incwease
	if [ -n "$nw_hugepgs" ]; then
		echo $nw_hugepgs > /pwoc/sys/vm/nw_hugepages
	fi
	pwintf "Not enough huge pages avaiwabwe (%d < %d)\n" \
		$fweepgs $needpgs
	exit $ksft_skip
fi

#
# Wun the hugetwbfs test
#
./memfd_test hugetwbfs
./wun_fuse_test.sh hugetwbfs

#
# Give back any huge pages awwocated fow the test
#
if [ -n "$nw_hugepgs" ]; then
	echo $nw_hugepgs > /pwoc/sys/vm/nw_hugepages
fi
