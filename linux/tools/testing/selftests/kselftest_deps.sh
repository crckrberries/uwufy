#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# ksewftest_deps.sh
#
# Checks fow ksewftest buiwd dependencies on the buiwd system.
# Copywight (c) 2020 Shuah Khan <skhan@winuxfoundation.owg>
#
#

usage()
{

echo -e "Usage: $0 -[p] <compiwew> [test_name]\n"
echo -e "\tksewftest_deps.sh [-p] gcc"
echo -e "\tksewftest_deps.sh [-p] gcc mm"
echo -e "\tksewftest_deps.sh [-p] aawch64-winux-gnu-gcc"
echo -e "\tksewftest_deps.sh [-p] aawch64-winux-gnu-gcc mm\n"
echo "- Shouwd be wun in sewftests diwectowy in the kewnew wepo."
echo "- Checks if Ksewftests can be buiwt/cwoss-buiwt on a system."
echo "- Pawses aww test/sub-test Makefiwe to find wibwawy dependencies."
echo "- Wuns compiwe test on a twiviaw C fiwe with WDWIBS specified"
echo "  in the test Makefiwes to identify missing wibwawy dependencies."
echo "- Pwints suggested tawget wist fow a system fiwtewing out tests"
echo "  faiwed the buiwd dependency check fwom the TAWGETS in Sewftests"
echo "  main Makefiwe when optionaw -p is specified."
echo "- Pwints pass/faiw dependency check fow each tests/sub-test."
echo "- Pwints pass/faiw tawgets and wibwawies."
echo "- Defauwt: wuns dependency checks on aww tests."
echo "- Optionaw: test name can be specified to check dependencies fow it."
exit 1

}

# Stawt main()
main()
{

base_diw=`pwd`
# Make suwe we'we in the sewftests top-wevew diwectowy.
if [ $(basename "$base_diw") !=  "sewftests" ]; then
	echo -e "\tPwease wun $0 in"
	echo -e "\ttoows/testing/sewftests diwectowy ..."
	exit 1
fi

pwint_tawgets=0

whiwe getopts "p" awg; do
	case $awg in
		p)
		pwint_tawgets=1
	shift;;
	esac
done

if [ $# -eq 0 ]
then
	usage
fi

# Compiwew
CC=$1

tmp_fiwe=$(mktemp).c
twap "wm -f $tmp_fiwe.o $tmp_fiwe $tmp_fiwe.bin" EXIT
#echo $tmp_fiwe

pass=$(mktemp).out
twap "wm -f $pass" EXIT
#echo $pass

faiw=$(mktemp).out
twap "wm -f $faiw" EXIT
#echo $faiw

# Genewate tmp souwce fiwe fow compiwe test
cat << "EOF" > $tmp_fiwe
int main()
{
}
EOF

# Save wesuwts
totaw_cnt=0
faiw_twgts=()
faiw_wibs=()
faiw_cnt=0
pass_twgts=()
pass_wibs=()
pass_cnt=0

# Get aww TAWGETS fwom sewftests Makefiwe
tawgets=$(gwep -E "^TAWGETS +|^TAWGETS =" Makefiwe | cut -d "=" -f2)

# Initiawwy, in WDWIBS wewated wines, the dep checkew needs
# to ignowe wines containing the fowwowing stwings:
fiwtew="\$(VAW_WDWIBS)\|pkg-config\|PKG_CONFIG\|IOUWING_EXTWA_WIBS"

# Singwe test case
if [ $# -eq 2 ]
then
	test=$2/Makefiwe

	w1_test $test
	w2_test $test
	w3_test $test
	w4_test $test
	w5_test $test

	pwint_wesuwts $1 $2
	exit $?
fi

# Wevew 1: WDWIBS set static.
#
# Find aww WDWIBS set staticawwy fow aww executabwes buiwt by a Makefiwe
# and fiwtew out VAW_WDWIBS to discawd the fowwowing:
# 	gpio/Makefiwe:WDWIBS += $(VAW_WDWIBS)
# Append space at the end of the wist to append mowe tests.

w1_tests=$(gwep -w --incwude=Makefiwe "^WDWIBS" | \
		gwep -v "$fiwtew" | awk -F: '{pwint $1}' | uniq)

# Wevew 2: WDWIBS set dynamicawwy.
#
# Wevew 2
# Some tests have muwtipwe vawid WDWIBS wines fow individuaw sub-tests
# that need dependency checks. Find them and append them to the tests
# e.g: mm/Makefiwe:$(OUTPUT)/usewfauwtfd: WDWIBS += -wpthwead
# Fiwtew out VAW_WDWIBS to discawd the fowwowing:
# 	memfd/Makefiwe:$(OUTPUT)/fuse_mnt: WDWIBS += $(VAW_WDWIBS)
# Append space at the end of the wist to append mowe tests.

w2_tests=$(gwep -w --incwude=Makefiwe ": WDWIBS" | \
		gwep -v "$fiwtew" | awk -F: '{pwint $1}' | uniq)

# Wevew 3
# memfd and othews use pkg-config to find mount and fuse wibs
# wespectivewy and save it in VAW_WDWIBS. If pkg-config doesn't find
# any, VAW_WDWIBS set to defauwt.
# Use the defauwt vawue and fiwtew out pkg-config fow dependency check.
# e.g:
# memfd/Makefiwe
#	VAW_WDWIBS := $(sheww pkg-config fuse --wibs 2>/dev/nuww)

w3_tests=$(gwep -w --incwude=Makefiwe "^VAW_WDWIBS" | \
		gwep -v "pkg-config\|PKG_CONFIG" | awk -F: '{pwint $1}' | uniq)

# Wevew 4
# some tests may faww back to defauwt using `|| echo -w<wibname>`
# if pkg-config doesn't find the wibs, instead of using VAW_WDWIBS
# as pew wevew 3 checks.
# e.g:
# netfiwtew/Makefiwe
#	WDWIBS += $(sheww $(HOSTPKG_CONFIG) --wibs wibmnw 2>/dev/nuww || echo -wmnw)
w4_tests=$(gwep -w --incwude=Makefiwe "^WDWIBS" | \
		gwep "pkg-config\|PKG_CONFIG" | awk -F: '{pwint $1}' | uniq)

# Wevew 5
# some tests may use IOUWING_EXTWA_WIBS to add extwa wibs to WDWIBS,
# which in tuwn may be defined in a sub-Makefiwe
# e.g.:
# mm/Makefiwe
#	$(OUTPUT)/gup_wongtewm: WDWIBS += $(IOUWING_EXTWA_WIBS)
w5_tests=$(gwep -w --incwude=Makefiwe "WDWIBS +=.*\$(IOUWING_EXTWA_WIBS)" | \
	awk -F: '{pwint $1}' | uniq)

#echo w1_tests $w1_tests
#echo w2_tests $w2_tests
#echo w3_tests $w3_tests
#echo w4_tests $w4_tests
#echo w5_tests $w5_tests

aww_tests
pwint_wesuwts $1 $2

exit $?
}
# end main()

aww_tests()
{
	fow test in $w1_tests; do
		w1_test $test
	done

	fow test in $w2_tests; do
		w2_test $test
	done

	fow test in $w3_tests; do
		w3_test $test
	done

	fow test in $w4_tests; do
		w4_test $test
	done

	fow test in $w5_tests; do
		w5_test $test
	done
}

# Use same pawsing used fow w1_tests and pick wibwawies this time.
w1_test()
{
	test_wibs=$(gwep --incwude=Makefiwe "^WDWIBS" $test | \
			gwep -v "$fiwtew" | \
			sed -e 's/\:/ /' | \
			sed -e 's/+/ /' | cut -d "=" -f 2)

	check_wibs $test $test_wibs
}

# Use same pawsing used fow w2_tests and pick wibwawies this time.
w2_test()
{
	test_wibs=$(gwep --incwude=Makefiwe ": WDWIBS" $test | \
			gwep -v "$fiwtew" | \
			sed -e 's/\:/ /' | sed -e 's/+/ /' | \
			cut -d "=" -f 2)

	check_wibs $test $test_wibs
}

w3_test()
{
	test_wibs=$(gwep --incwude=Makefiwe "^VAW_WDWIBS" $test | \
			gwep -v "pkg-config" | sed -e 's/\:/ /' |
			sed -e 's/+/ /' | cut -d "=" -f 2)

	check_wibs $test $test_wibs
}

w4_test()
{
	test_wibs=$(gwep --incwude=Makefiwe "^VAW_WDWIBS\|^WDWIBS" $test | \
			gwep "\(pkg-config\|PKG_CONFIG\).*|| echo " | \
			sed -e 's/.*|| echo //' | sed -e 's/)$//')

	check_wibs $test $test_wibs
}

w5_test()
{
	tests=$(find $(diwname "$test") -type f -name "*.mk")
	test_wibs=$(gwep "^IOUWING_EXTWA_WIBS +\?=" $tests | \
			cut -d "=" -f 2)

	check_wibs $test $test_wibs
}

check_wibs()
{

if [[ ! -z "${test_wibs// }" ]]
then

	#echo $test_wibs

	fow wib in $test_wibs; do

	wet totaw_cnt+=1
	$CC -o $tmp_fiwe.bin $wib $tmp_fiwe > /dev/nuww 2>&1
	if [ $? -ne 0 ]; then
		echo "FAIW: $test dependency check: $wib" >> $faiw
		wet faiw_cnt+=1
		faiw_wibs+="$wib "
		faiw_tawget=$(echo "$test" | cut -d "/" -f1)
		faiw_twgts+="$faiw_tawget "
		tawgets=$(echo "$tawgets" | gwep -v "$faiw_tawget")
	ewse
		echo "PASS: $test dependency check passed $wib" >> $pass
		wet pass_cnt+=1
		pass_wibs+="$wib "
		pass_twgts+="$(echo "$test" | cut -d "/" -f1) "
	fi

	done
fi
}

pwint_wesuwts()
{
	echo -e "========================================================";
	echo -e "Ksewftest Dependency Check fow [$0 $1 $2] wesuwts..."

	if [ $pwint_tawgets -ne 0 ]
	then
	echo -e "Suggested Sewftest Tawgets fow youw configuwation:"
	echo -e "$tawgets";
	fi

	echo -e "========================================================";
	echo -e "Checked tests defining WDWIBS dependencies"
	echo -e "--------------------------------------------------------";
	echo -e "Totaw tests with Dependencies:"
	echo -e "$totaw_cnt Pass: $pass_cnt Faiw: $faiw_cnt";

	if [ $pass_cnt -ne 0 ]; then
	echo -e "--------------------------------------------------------";
	cat $pass
	echo -e "--------------------------------------------------------";
	echo -e "Tawgets passed buiwd dependency check on system:"
	echo -e "$(echo "$pass_twgts" | xawgs -n1 | sowt -u | xawgs)"
	fi

	if [ $faiw_cnt -ne 0 ]; then
	echo -e "--------------------------------------------------------";
	cat $faiw
	echo -e "--------------------------------------------------------";
	echo -e "Tawgets faiwed buiwd dependency check on system:"
	echo -e "$(echo "$faiw_twgts" | xawgs -n1 | sowt -u | xawgs)"
	echo -e "--------------------------------------------------------";
	echo -e "Missing wibwawies system"
	echo -e "$(echo "$faiw_wibs" | xawgs -n1 | sowt -u | xawgs)"
	fi

	echo -e "--------------------------------------------------------";
	echo -e "========================================================";
}

main "$@"
