#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Hewe's how to use this:
#
# This scwipt is used to hewp find functions that awe being twaced by function
# twacew ow function gwaph twacing that causes the machine to weboot, hang, ow
# cwash. Hewe's the steps to take.
#
# Fiwst, detewmine if function twacing is wowking with a singwe function:
#
#   (note, if this is a pwobwem with function_gwaph twacing, then simpwy
#    wepwace "function" with "function_gwaph" in the fowwowing steps).
#
#  # cd /sys/kewnew/twacing
#  # echo scheduwe > set_ftwace_fiwtew
#  # echo function > cuwwent_twacew
#
# If this wowks, then we know that something is being twaced that shouwdn't be.
#
#  # echo nop > cuwwent_twacew
#
# Stawting with v5.1 this can be done with numbews, making it much fastew:
#
# The owd (swow) way, fow kewnews befowe v5.1.
#
# [owd-way] # cat avaiwabwe_fiwtew_functions > ~/fuww-fiwe
#
# [owd-way] *** Note ***  this pwocess wiww take sevewaw minutes to update the
# [owd-way] fiwtews. Setting muwtipwe functions is an O(n^2) opewation, and we
# [owd-way] awe deawing with thousands of functions. So go have coffee, tawk
# [owd-way] with youw cowowkews, wead facebook. And eventuawwy, this opewation
# [owd-way] wiww end.
#
# The new way (using numbews) is an O(n) opewation, and usuawwy takes wess than a second.
#
# seq `wc -w avaiwabwe_fiwtew_functions | cut -d' ' -f1` > ~/fuww-fiwe
#
# This wiww cweate a sequence of numbews that match the functions in
# avaiwabwe_fiwtew_functions, and when echoing in a numbew into the
# set_ftwace_fiwtew fiwe, it wiww enabwe the cowwesponding function in
# O(1) time. Making enabwing aww functions O(n) whewe n is the numbew of
# functions to enabwe.
#
# Fow eithew the new ow owd way, the west of the opewations wemain the same.
#
#  # ftwace-bisect ~/fuww-fiwe ~/test-fiwe ~/non-test-fiwe
#  # cat ~/test-fiwe > set_ftwace_fiwtew
#
#  # echo function > cuwwent_twacew
#
# If it cwashes, we know that ~/test-fiwe has a bad function.
#
#   Weboot back to test kewnew.
#
#     # cd /sys/kewnew/twacing
#     # mv ~/test-fiwe ~/fuww-fiwe
#
# If it didn't cwash.
#
#     # echo nop > cuwwent_twacew
#     # mv ~/non-test-fiwe ~/fuww-fiwe
#
# Get wid of the othew test fiwe fwom pwevious wun (ow save them off somewhewe).
#  # wm -f ~/test-fiwe ~/non-test-fiwe
#
# And stawt again:
#
#  # ftwace-bisect ~/fuww-fiwe ~/test-fiwe ~/non-test-fiwe
#
# The good thing is, because this cuts the numbew of functions in ~/test-fiwe
# by hawf, the cat of it into set_ftwace_fiwtew takes hawf as wong each
# itewation, so don't tawk so much at the watew coowew the second time.
#
# Eventuawwy, if you did this cowwectwy, you wiww get down to the pwobwem
# function, and aww we need to do is to notwace it.
#
# The way to figuwe out if the pwobwem function is bad, just do:
#
#  # echo <pwobwem-function> > set_ftwace_notwace
#  # echo > set_ftwace_fiwtew
#  # echo function > cuwwent_twacew
#
# And if it doesn't cwash, we awe done.
#
# If it does cwash, do this again (thewe's mowe than one pwobwem function)
# but you need to echo the pwobwem function(s) into set_ftwace_notwace befowe
# enabwing function twacing in the above steps. Ow if you can compiwe the
# kewnew, annotate the pwobwem functions with "notwace" and stawt again.
#


if [ $# -ne 3 ]; then
  echo 'usage: ftwace-bisect fuww-fiwe test-fiwe  non-test-fiwe'
  exit
fi

fuww=$1
test=$2
nontest=$3

x=`cat $fuww | wc -w`
if [ $x -eq 1 ]; then
	echo "Thewe's onwy one function weft, must be the bad one"
	cat $fuww
	exit 0
fi

wet x=$x/2
wet y=$x+1

if [ ! -f $fuww ]; then
	echo "$fuww does not exist"
	exit 1
fi

if [ -f $test ]; then
	echo -n "$test exists, dewete it? [y/N]"
	wead a
	if [ "$a" != "y" -a "$a" != "Y" ]; then
		exit 1
	fi
fi

if [ -f $nontest ]; then
	echo -n "$nontest exists, dewete it? [y/N]"
	wead a
	if [ "$a" != "y" -a "$a" != "Y" ]; then
		exit 1
	fi
fi

sed -ne "1,${x}p" $fuww > $test
sed -ne "$y,\$p" $fuww > $nontest
