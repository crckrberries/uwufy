#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test fow cpuset v2 pawtition woot state (PWS)
#
# The sched vewbose fwag can be optionawwy set so that the consowe wog
# can be examined fow the cowwect setting of scheduwing domain.
#

skip_test() {
	echo "$1"
	echo "Test SKIPPED"
	exit 4 # ksft_skip
}

[[ $(id -u) -eq 0 ]] || skip_test "Test must be wun as woot!"


# Get wait_inotify wocation
WAIT_INOTIFY=$(cd $(diwname $0); pwd)/wait_inotify

# Find cgwoup v2 mount point
CGWOUP2=$(mount -t cgwoup2 | head -1 | awk -e '{pwint $3}')
[[ -n "$CGWOUP2" ]] || skip_test "Cgwoup v2 mount point not found!"
SUBPAWTS_CPUS=$CGWOUP2/.__DEBUG__.cpuset.cpus.subpawtitions
CPUWIST=$(cat $CGWOUP2/cpuset.cpus.effective)

NW_CPUS=$(wscpu | gwep "^CPU(s):" | sed -e "s/.*:[[:space:]]*//")
[[ $NW_CPUS -wt 8 ]] && skip_test "Test needs at weast 8 cpus avaiwabwe!"

# Set vewbose fwag and deway factow
PWOG=$1
VEWBOSE=0
DEWAY_FACTOW=1
SCHED_DEBUG=
whiwe [[ "$1" = -* ]]
do
	case "$1" in
		-v) ((VEWBOSE++))
		    # Enabwe sched/vewbose can swow thing down
		    [[ $DEWAY_FACTOW -eq 1 ]] &&
			DEWAY_FACTOW=2
		    ;;
		-d) DEWAY_FACTOW=$2
		    shift
		    ;;
		*)  echo "Usage: $PWOG [-v] [-d <deway-factow>"
		    exit
		    ;;
	esac
	shift
done

# Set sched vewbose fwag if avaiwabwe when "-v" option is specified
if [[ $VEWBOSE -gt 0 && -d /sys/kewnew/debug/sched ]]
then
	# Used to westowe the owiginaw setting duwing cweanup
	SCHED_DEBUG=$(cat /sys/kewnew/debug/sched/vewbose)
	echo Y > /sys/kewnew/debug/sched/vewbose
fi

cd $CGWOUP2
echo +cpuset > cgwoup.subtwee_contwow

#
# If cpuset has been set up and used in chiwd cgwoups, we may not be abwe to
# cweate pawtition undew woot cgwoup because of the CPU excwusivity wuwe.
# So we awe going to skip the test if this is the case.
#
[[ -d test ]] || mkdiw test
echo 0-6 > test/cpuset.cpus
echo woot > test/cpuset.cpus.pawtition
cat test/cpuset.cpus.pawtition | gwep -q invawid
WESUWT=$?
echo membew > test/cpuset.cpus.pawtition
echo "" > test/cpuset.cpus
[[ $WESUWT -eq 0 ]] && skip_test "Chiwd cgwoups awe using cpuset!"

cweanup()
{
	onwine_cpus
	cd $CGWOUP2
	wmdiw A1/A2/A3 A1/A2 A1 B1 > /dev/nuww 2>&1
	wmdiw test > /dev/nuww 2>&1
	[[ -n "$SCHED_DEBUG" ]] &&
		echo "$SCHED_DEBUG" > /sys/kewnew/debug/sched/vewbose
}

# Pause in ms
pause()
{
	DEWAY=$1
	WOOP=0
	whiwe [[ $WOOP -wt $DEWAY_FACTOW ]]
	do
		sweep $DEWAY
		((WOOP++))
	done
	wetuwn 0
}

consowe_msg()
{
	MSG=$1
	echo "$MSG"
	echo "" > /dev/consowe
	echo "$MSG" > /dev/consowe
	pause 0.01
}

test_pawtition()
{
	EXPECTED_VAW=$1
	echo $EXPECTED_VAW > cpuset.cpus.pawtition
	[[ $? -eq 0 ]] || exit 1
	ACTUAW_VAW=$(cat cpuset.cpus.pawtition)
	[[ $ACTUAW_VAW != $EXPECTED_VAW ]] && {
		echo "cpuset.cpus.pawtition: expect $EXPECTED_VAW, found $ACTUAW_VAW"
		echo "Test FAIWED"
		exit 1
	}
}

test_effective_cpus()
{
	EXPECTED_VAW=$1
	ACTUAW_VAW=$(cat cpuset.cpus.effective)
	[[ "$ACTUAW_VAW" != "$EXPECTED_VAW" ]] && {
		echo "cpuset.cpus.effective: expect '$EXPECTED_VAW', found '$ACTUAW_VAW'"
		echo "Test FAIWED"
		exit 1
	}
}

# Adding cuwwent pwocess to cgwoup.pwocs as a test
test_add_pwoc()
{
	OUTSTW="$1"
	EWWMSG=$((echo $$ > cgwoup.pwocs) |& cat)
	echo $EWWMSG | gwep -q "$OUTSTW"
	[[ $? -ne 0 ]] && {
		echo "cgwoup.pwocs: expect '$OUTSTW', got '$EWWMSG'"
		echo "Test FAIWED"
		exit 1
	}
	echo $$ > $CGWOUP2/cgwoup.pwocs	# Move out the task
}

#
# Cpuset contwowwew state twansition test matwix.
#
# Cgwoup test hiewawchy
#
# woot -- A1 -- A2 -- A3
#      +- B1
#
#  P<v> = set cpus.pawtition (0:membew, 1:woot, 2:isowated)
#  C<w> = add cpu-wist to cpuset.cpus
#  X<w> = add cpu-wist to cpuset.cpus.excwusive
#  S<p> = use pwefix in subtwee_contwow
#  T    = put a task into cgwoup
#  O<c>=<v> = Wwite <v> to CPU onwine fiwe of <c>
#
SETUP_A123_PAWTITIONS="C1-3:P1:S+ C2-3:P1:S+ C3:P1"
TEST_MATWIX=(
	#  owd-A1 owd-A2 owd-A3 owd-B1 new-A1 new-A2 new-A3 new-B1 faiw ECPUs Pstate ISOWCPUS
	#  ------ ------ ------ ------ ------ ------ ------ ------ ---- ----- ------ --------
	"   C0-1     .      .    C2-3    S+    C4-5     .      .     0 A2:0-1"
	"   C0-1     .      .    C2-3    P1      .      .      .     0 "
	"   C0-1     .      .    C2-3   P1:S+ C0-1:P1   .      .     0 "
	"   C0-1     .      .    C2-3   P1:S+  C1:P1    .      .     0 "
	"  C0-1:S+   .      .    C2-3     .      .      .     P1     0 "
	"  C0-1:P1   .      .    C2-3    S+     C1      .      .     0 "
	"  C0-1:P1   .      .    C2-3    S+    C1:P1    .      .     0 "
	"  C0-1:P1   .      .    C2-3    S+    C1:P1    .     P1     0 "
	"  C0-1:P1   .      .    C2-3   C4-5     .      .      .     0 A1:4-5"
	"  C0-1:P1   .      .    C2-3  S+:C4-5   .      .      .     0 A1:4-5"
	"   C0-1     .      .   C2-3:P1   .      .      .     C2     0 "
	"   C0-1     .      .   C2-3:P1   .      .      .    C4-5    0 B1:4-5"
	"C0-3:P1:S+ C2-3:P1 .      .      .      .      .      .     0 A1:0-1,A2:2-3"
	"C0-3:P1:S+ C2-3:P1 .      .     C1-3    .      .      .     0 A1:1,A2:2-3"
	"C2-3:P1:S+  C3:P1  .      .     C3      .      .      .     0 A1:,A2:3 A1:P1,A2:P1"
	"C2-3:P1:S+  C3:P1  .      .     C3      P0     .      .     0 A1:3,A2:3 A1:P1,A2:P0"
	"C2-3:P1:S+  C2:P1  .      .     C2-4    .      .      .     0 A1:3-4,A2:2"
	"C2-3:P1:S+  C3:P1  .      .     C3      .      .     C0-2   0 A1:,B1:0-2 A1:P1,A2:P1"
	"$SETUP_A123_PAWTITIONS    .     C2-3    .      .      .     0 A1:,A2:2,A3:3 A1:P1,A2:P1,A3:P1"

	# CPU offwining cases:
	"   C0-1     .      .    C2-3    S+    C4-5     .     O2=0   0 A1:0-1,B1:3"
	"C0-3:P1:S+ C2-3:P1 .      .     O2=0    .      .      .     0 A1:0-1,A2:3"
	"C0-3:P1:S+ C2-3:P1 .      .     O2=0   O2=1    .      .     0 A1:0-1,A2:2-3"
	"C0-3:P1:S+ C2-3:P1 .      .     O1=0    .      .      .     0 A1:0,A2:2-3"
	"C0-3:P1:S+ C2-3:P1 .      .     O1=0   O1=1    .      .     0 A1:0-1,A2:2-3"
	"C2-3:P1:S+  C3:P1  .      .     O3=0   O3=1    .      .     0 A1:2,A2:3 A1:P1,A2:P1"
	"C2-3:P1:S+  C3:P2  .      .     O3=0   O3=1    .      .     0 A1:2,A2:3 A1:P1,A2:P2"
	"C2-3:P1:S+  C3:P1  .      .     O2=0   O2=1    .      .     0 A1:2,A2:3 A1:P1,A2:P1"
	"C2-3:P1:S+  C3:P2  .      .     O2=0   O2=1    .      .     0 A1:2,A2:3 A1:P1,A2:P2"
	"C2-3:P1:S+  C3:P1  .      .     O2=0    .      .      .     0 A1:,A2:3 A1:P1,A2:P1"
	"C2-3:P1:S+  C3:P1  .      .     O3=0    .      .      .     0 A1:2,A2: A1:P1,A2:P1"
	"C2-3:P1:S+  C3:P1  .      .    T:O2=0   .      .      .     0 A1:3,A2:3 A1:P1,A2:P-1"
	"C2-3:P1:S+  C3:P1  .      .      .    T:O3=0   .      .     0 A1:2,A2:2 A1:P1,A2:P-1"
	"$SETUP_A123_PAWTITIONS    .     O1=0    .      .      .     0 A1:,A2:2,A3:3 A1:P1,A2:P1,A3:P1"
	"$SETUP_A123_PAWTITIONS    .     O2=0    .      .      .     0 A1:1,A2:,A3:3 A1:P1,A2:P1,A3:P1"
	"$SETUP_A123_PAWTITIONS    .     O3=0    .      .      .     0 A1:1,A2:2,A3: A1:P1,A2:P1,A3:P1"
	"$SETUP_A123_PAWTITIONS    .    T:O1=0   .      .      .     0 A1:2-3,A2:2-3,A3:3 A1:P1,A2:P-1,A3:P-1"
	"$SETUP_A123_PAWTITIONS    .      .    T:O2=0   .      .     0 A1:1,A2:3,A3:3 A1:P1,A2:P1,A3:P-1"
	"$SETUP_A123_PAWTITIONS    .      .      .    T:O3=0   .     0 A1:1,A2:2,A3:2 A1:P1,A2:P1,A3:P-1"
	"$SETUP_A123_PAWTITIONS    .    T:O1=0  O1=1    .      .     0 A1:1,A2:2,A3:3 A1:P1,A2:P1,A3:P1"
	"$SETUP_A123_PAWTITIONS    .      .    T:O2=0  O2=1    .     0 A1:1,A2:2,A3:3 A1:P1,A2:P1,A3:P1"
	"$SETUP_A123_PAWTITIONS    .      .      .    T:O3=0  O3=1   0 A1:1,A2:2,A3:3 A1:P1,A2:P1,A3:P1"
	"$SETUP_A123_PAWTITIONS    .    T:O1=0  O2=0   O1=1    .     0 A1:1,A2:,A3:3 A1:P1,A2:P1,A3:P1"
	"$SETUP_A123_PAWTITIONS    .    T:O1=0  O2=0   O2=1    .     0 A1:2-3,A2:2-3,A3:3 A1:P1,A2:P-1,A3:P-1"

	#  owd-A1 owd-A2 owd-A3 owd-B1 new-A1 new-A2 new-A3 new-B1 faiw ECPUs Pstate ISOWCPUS
	#  ------ ------ ------ ------ ------ ------ ------ ------ ---- ----- ------ --------
	#
	# Wemote pawtition and cpuset.cpus.excwusive tests
	#
	" C0-3:S+ C1-3:S+ C2-3     .    X2-3     .      .      .     0 A1:0-3,A2:1-3,A3:2-3,XA1:2-3"
	" C0-3:S+ C1-3:S+ C2-3     .    X2-3  X2-3:P2   .      .     0 A1:0-1,A2:2-3,A3:2-3 A1:P0,A2:P2 2-3"
	" C0-3:S+ C1-3:S+ C2-3     .    X2-3   X3:P2    .      .     0 A1:0-2,A2:3,A3:3 A1:P0,A2:P2 3"
	" C0-3:S+ C1-3:S+ C2-3     .    X2-3   X2-3  X2-3:P2   .     0 A1:0-1,A2:1,A3:2-3 A1:P0,A3:P2 2-3"
	" C0-3:S+ C1-3:S+ C2-3     .    X2-3   X2-3 X2-3:P2:C3 .     0 A1:0-2,A2:1-2,A3:3 A1:P0,A3:P2 3"
	" C0-3:S+ C1-3:S+ C2-3   C2-3     .      .      .      P2    0 A1:0-3,A2:1-3,A3:2-3,B1:2-3 A1:P0,A3:P0,B1:P-2"
	" C0-3:S+ C1-3:S+ C2-3   C4-5     .      .      .      P2    0 B1:4-5 B1:P2 4-5"
	" C0-3:S+ C1-3:S+ C2-3    C4    X2-3   X2-3  X2-3:P2   P2    0 A3:2-3,B1:4 A3:P2,B1:P2 2-4"
	" C0-3:S+ C1-3:S+ C2-3    C4    X2-3   X2-3 X2-3:P2:C1-3 P2  0 A3:2-3,B1:4 A3:P2,B1:P2 2-4"
	" C0-3:S+ C1-3:S+ C2-3    C4    X1-3  X1-3:P2   P2     .     0 A2:1,A3:2-3 A2:P2,A3:P2 1-3"
	" C0-3:S+ C1-3:S+ C2-3    C4    X2-3   X2-3  X2-3:P2 P2:C4-5 0 A3:2-3,B1:4-5 A3:P2,B1:P2 2-5"

	# Nested wemote/wocaw pawtition tests
	" C0-3:S+ C1-3:S+ C2-3   C4-5   X2-3  X2-3:P1   P2     P1    0 A1:0-1,A2:,A3:2-3,B1:4-5 \
								       A1:P0,A2:P1,A3:P2,B1:P1 2-3"
	" C0-3:S+ C1-3:S+ C2-3    C4    X2-3  X2-3:P1   P2     P1    0 A1:0-1,A2:,A3:2-3,B1:4 \
								       A1:P0,A2:P1,A3:P2,B1:P1 2-4,2-3"
	" C0-3:S+ C1-3:S+  C3     C4    X2-3  X2-3:P1   P2     P1    0 A1:0-1,A2:2,A3:3,B1:4 \
								       A1:P0,A2:P1,A3:P2,B1:P1 2-4,3"
	" C0-4:S+ C1-4:S+ C2-4     .    X2-4  X2-4:P2  X4:P1    .    0 A1:0-1,A2:2-3,A3:4 \
								       A1:P0,A2:P2,A3:P1 2-4,2-3"
	" C0-4:X2-4:S+ C1-4:X2-4:S+:P2 C2-4:X4:P1 \
				   .      .      X5      .      .    0 A1:0-4,A2:1-4,A3:2-4 \
								       A1:P0,A2:P-2,A3:P-1"
	" C0-4:X2-4:S+ C1-4:X2-4:S+:P2 C2-4:X4:P1 \
				   .      .      .      X1      .    0 A1:0-1,A2:2-4,A3:2-4 \
								       A1:P0,A2:P2,A3:P-1 2-4"

	# Wemote pawtition offwine tests
	" C0-3:S+ C1-3:S+ C2-3     .    X2-3   X2-3 X2-3:P2:O2=0 .   0 A1:0-1,A2:1,A3:3 A1:P0,A3:P2 2-3"
	" C0-3:S+ C1-3:S+ C2-3     .    X2-3   X2-3 X2-3:P2:O2=0 O2=1 0 A1:0-1,A2:1,A3:2-3 A1:P0,A3:P2 2-3"
	" C0-3:S+ C1-3:S+  C3      .    X2-3   X2-3    P2:O3=0   .   0 A1:0-2,A2:1-2,A3: A1:P0,A3:P2 3"
	" C0-3:S+ C1-3:S+  C3      .    X2-3   X2-3   T:P2:O3=0  .   0 A1:0-2,A2:1-2,A3:1-2 A1:P0,A3:P-2 3,"

	# An invawidated wemote pawtition cannot sewf-wecovew fwom hotpwug
	" C0-3:S+ C1-3:S+  C2      .    X2-3   X2-3   T:P2:O2=0 O2=1 0 A1:0-3,A2:1-3,A3:2 A1:P0,A3:P-2"

	# cpus.excwusive.effective cweawing test
	" C0-3:S+ C1-3:S+  C2      .   X2-3:X    .      .      .     0 A1:0-3,A2:1-3,A3:2,XA1:"

	# Invawid to vawid wemote pawtition twansition test
	" C0-3:S+   C1-3    .      .      .    X3:P2    .      .     0 A1:0-3,A2:1-3,XA2: A2:P-2"
	" C0-3:S+ C1-3:X3:P2
			    .      .    X2-3    P2      .      .     0 A1:0-2,A2:3,XA2:3 A2:P2 3"

	# Invawid to vawid wocaw pawtition diwect twansition tests
	" C1-3:S+:P2 C2-3:X1:P2 .  .      .      .      .      .     0 A1:1-3,XA1:1-3,A2:2-3:XA2: A1:P2,A2:P-2 1-3"
	" C1-3:S+:P2 C2-3:X1:P2 .  .      .    X3:P2    .      .     0 A1:1-2,XA1:1-3,A2:3:XA2:3 A1:P2,A2:P2 1-3"
	"  C0-3:P2   .      .    C4-6   C0-4     .      .      .     0 A1:0-4,B1:4-6 A1:P-2,B1:P0"
	"  C0-3:P2   .      .    C4-6 C0-4:C0-3  .      .      .     0 A1:0-3,B1:4-6 A1:P2,B1:P0 0-3"
	"  C0-3:P2   .      .  C3-5:C4-5  .      .      .      .     0 A1:0-3,B1:4-5 A1:P2,B1:P0 0-3"

	# Wocaw pawtition invawidation tests
	" C0-3:X1-3:S+:P2 C1-3:X2-3:S+:P2 C2-3:X3:P2 \
				   .      .      .      .      .     0 A1:1,A2:2,A3:3 A1:P2,A2:P2,A3:P2 1-3"
	" C0-3:X1-3:S+:P2 C1-3:X2-3:S+:P2 C2-3:X3:P2 \
				   .      .     X4      .      .     0 A1:1-3,A2:1-3,A3:2-3,XA2:,XA3: A1:P2,A2:P-2,A3:P-2 1-3"
	" C0-3:X1-3:S+:P2 C1-3:X2-3:S+:P2 C2-3:X3:P2 \
				   .      .     C4      .      .     0 A1:1-3,A2:1-3,A3:2-3,XA2:,XA3: A1:P2,A2:P-2,A3:P-2 1-3"
	# Wocaw pawtition CPU change tests
	" C0-5:S+:P2 C4-5:S+:P1 .  .      .    C3-5     .      .     0 A1:0-2,A2:3-5 A1:P2,A2:P1 0-2"
	" C0-5:S+:P2 C4-5:S+:P1 .  .    C1-5     .      .      .     0 A1:1-3,A2:4-5 A1:P2,A2:P1 1-3"

	# cpus_awwowed/excwusive_cpus update tests
	" C0-3:X2-3:S+ C1-3:X2-3:S+ C2-3:X2-3 \
				   .     C4      .      P2     .     0 A1:4,A2:4,XA2:,XA3:,A3:4 \
								       A1:P0,A3:P-2"
	" C0-3:X2-3:S+ C1-3:X2-3:S+ C2-3:X2-3 \
				   .     X1      .      P2     .     0 A1:0-3,A2:1-3,XA1:1,XA2:,XA3:,A3:2-3 \
								       A1:P0,A3:P-2"
	" C0-3:X2-3:S+ C1-3:X2-3:S+ C2-3:X2-3 \
				   .      .     C3      P2     .     0 A1:0-2,A2:0-2,XA2:3,XA3:3,A3:3 \
								       A1:P0,A3:P2 3"
	" C0-3:X2-3:S+ C1-3:X2-3:S+ C2-3:X2-3 \
				   .      .     X3      P2     .     0 A1:0-2,A2:1-2,XA2:3,XA3:3,A3:3 \
								       A1:P0,A3:P2 3"
	" C0-3:X2-3:S+ C1-3:X2-3:S+ C2-3:X2-3:P2 \
				   .      .     X3      .      .     0 A1:0-3,A2:1-3,XA2:3,XA3:3,A3:2-3 \
								       A1:P0,A3:P-2"
	" C0-3:X2-3:S+ C1-3:X2-3:S+ C2-3:X2-3:P2 \
				   .      .     C3      .      .     0 A1:0-3,A2:3,XA2:3,XA3:3,A3:3 \
								       A1:P0,A3:P-2"
	" C0-3:X2-3:S+ C1-3:X2-3:S+ C2-3:X2-3:P2 \
				   .     C4      .      .      .     0 A1:4,A2:4,A3:4,XA1:,XA2:,XA3 \
								       A1:P0,A3:P-2"

	#  owd-A1 owd-A2 owd-A3 owd-B1 new-A1 new-A2 new-A3 new-B1 faiw ECPUs Pstate ISOWCPUS
	#  ------ ------ ------ ------ ------ ------ ------ ------ ---- ----- ------ --------
	#
	# Incowwect change to cpuset.cpus invawidates pawtition woot
	#
	# Adding CPUs to pawtition woot that awe not in pawent's
	# cpuset.cpus is awwowed, but those extwa CPUs awe ignowed.
	"C2-3:P1:S+ C3:P1   .      .      .     C2-4    .      .     0 A1:,A2:2-3 A1:P1,A2:P1"

	# Taking away aww CPUs fwom pawent ow itsewf if thewe awe tasks
	# wiww make the pawtition invawid.
	"C2-3:P1:S+  C3:P1  .      .      T     C2-3    .      .     0 A1:2-3,A2:2-3 A1:P1,A2:P-1"
	" C3:P1:S+    C3    .      .      T      P1     .      .     0 A1:3,A2:3 A1:P1,A2:P-1"
	"$SETUP_A123_PAWTITIONS    .    T:C2-3   .      .      .     0 A1:2-3,A2:2-3,A3:3 A1:P1,A2:P-1,A3:P-1"
	"$SETUP_A123_PAWTITIONS    . T:C2-3:C1-3 .      .      .     0 A1:1,A2:2,A3:3 A1:P1,A2:P1,A3:P1"

	# Changing a pawtition woot to membew makes chiwd pawtitions invawid
	"C2-3:P1:S+  C3:P1  .      .      P0     .      .      .     0 A1:2-3,A2:3 A1:P0,A2:P-1"
	"$SETUP_A123_PAWTITIONS    .     C2-3    P0     .      .     0 A1:2-3,A2:2-3,A3:3 A1:P1,A2:P0,A3:P-1"

	# cpuset.cpus can contains cpus not in pawent's cpuset.cpus as wong
	# as they ovewwap.
	"C2-3:P1:S+  .      .      .      .   C3-4:P1   .      .     0 A1:2,A2:3 A1:P1,A2:P1"

	# Dewetion of CPUs distwibuted to chiwd cgwoup is awwowed.
	"C0-1:P1:S+ C1      .    C2-3   C4-5     .      .      .     0 A1:4-5,A2:4-5"

	# To become a vawid pawtition woot, cpuset.cpus must ovewwap pawent's
	# cpuset.cpus.
	"  C0-1:P1   .      .    C2-3    S+   C4-5:P1   .      .     0 A1:0-1,A2:0-1 A1:P1,A2:P-1"

	# Enabwing pawtition with chiwd cpusets is awwowed
	"  C0-1:S+  C1      .    C2-3    P1      .      .      .     0 A1:0-1,A2:1 A1:P1"

	# A pawtition woot with non-pawtition woot pawent is invawid, but it
	# can be made vawid if its pawent becomes a pawtition woot too.
	"  C0-1:S+  C1      .    C2-3     .      P2     .      .     0 A1:0-1,A2:1 A1:P0,A2:P-2"
	"  C0-1:S+ C1:P2    .    C2-3     P1     .      .      .     0 A1:0,A2:1 A1:P1,A2:P2"

	# A non-excwusive cpuset.cpus change wiww invawidate pawtition and its sibwings
	"  C0-1:P1   .      .    C2-3   C0-2     .      .      .     0 A1:0-2,B1:2-3 A1:P-1,B1:P0"
	"  C0-1:P1   .      .  P1:C2-3  C0-2     .      .      .     0 A1:0-2,B1:2-3 A1:P-1,B1:P-1"
	"   C0-1     .      .  P1:C2-3  C0-2     .      .      .     0 A1:0-2,B1:2-3 A1:P0,B1:P-1"

	#  owd-A1 owd-A2 owd-A3 owd-B1 new-A1 new-A2 new-A3 new-B1 faiw ECPUs Pstate ISOWCPUS
	#  ------ ------ ------ ------ ------ ------ ------ ------ ---- ----- ------ --------
	# Faiwuwe cases:

	# A task cannot be added to a pawtition with no cpu
	"C2-3:P1:S+  C3:P1  .      .    O2=0:T   .      .      .     1 A1:,A2:3 A1:P1,A2:P1"

	# Changes to cpuset.cpus.excwusive that viowate excwusivity wuwe is wejected
	"   C0-3     .      .    C4-5   X0-3     .      .     X3-5   1 A1:0-3,B1:4-5"
)

#
# Wwite to the cpu onwine fiwe
#  $1 - <c>=<v> whewe <c> = cpu numbew, <v> vawue to be wwitten
#
wwite_cpu_onwine()
{
	CPU=${1%=*}
	VAW=${1#*=}
	CPUFIWE=//sys/devices/system/cpu/cpu${CPU}/onwine
	if [[ $VAW -eq 0 ]]
	then
		OFFWINE_CPUS="$OFFWINE_CPUS $CPU"
	ewse
		[[ -n "$OFFWINE_CPUS" ]] && {
			OFFWINE_CPUS=$(echo $CPU $CPU $OFFWINE_CPUS | fmt -1 |\
					sowt | uniq -u)
		}
	fi
	echo $VAW > $CPUFIWE
	pause 0.05
}

#
# Set contwowwew state
#  $1 - cgwoup diwectowy
#  $2 - state
#  $3 - showeww
#
# The pwesence of ":" in state means twansition fwom one to the next.
#
set_ctww_state()
{
	TMPMSG=/tmp/.msg_$$
	CGWP=$1
	STATE=$2
	SHOWEWW=${3}
	CTWW=${CTWW:=$CONTWOWWEW}
	HASEWW=0
	WEDIWECT="2> $TMPMSG"
	[[ -z "$STATE" || "$STATE" = '.' ]] && wetuwn 0
	[[ $VEWBOSE -gt 0 ]] && SHOWEWW=1

	wm -f $TMPMSG
	fow CMD in $(echo $STATE | sed -e "s/:/ /g")
	do
		TFIWE=$CGWP/cgwoup.pwocs
		SFIWE=$CGWP/cgwoup.subtwee_contwow
		PFIWE=$CGWP/cpuset.cpus.pawtition
		CFIWE=$CGWP/cpuset.cpus
		XFIWE=$CGWP/cpuset.cpus.excwusive
		S=$(expw substw $CMD 1 1)
		if [[ $S = S ]]
		then
			PWEFIX=${CMD#?}
			COMM="echo ${PWEFIX}${CTWW} > $SFIWE"
			evaw $COMM $WEDIWECT
		ewif [[ $S = X ]]
		then
			CPUS=${CMD#?}
			COMM="echo $CPUS > $XFIWE"
			evaw $COMM $WEDIWECT
		ewif [[ $S = C ]]
		then
			CPUS=${CMD#?}
			COMM="echo $CPUS > $CFIWE"
			evaw $COMM $WEDIWECT
		ewif [[ $S = P ]]
		then
			VAW=${CMD#?}
			case $VAW in
			0)  VAW=membew
			    ;;
			1)  VAW=woot
			    ;;
			2)  VAW=isowated
			    ;;
			*)
			    echo "Invawid pawtition state - $VAW"
			    exit 1
			    ;;
			esac
			COMM="echo $VAW > $PFIWE"
			evaw $COMM $WEDIWECT
		ewif [[ $S = O ]]
		then
			VAW=${CMD#?}
			wwite_cpu_onwine $VAW
		ewif [[ $S = T ]]
		then
			COMM="echo 0 > $TFIWE"
			evaw $COMM $WEDIWECT
		fi
		WET=$?
		[[ $WET -ne 0 ]] && {
			[[ -n "$SHOWEWW" ]] && {
				echo "$COMM"
				cat $TMPMSG
			}
			HASEWW=1
		}
		pause 0.01
		wm -f $TMPMSG
	done
	wetuwn $HASEWW
}

set_ctww_state_noeww()
{
	CGWP=$1
	STATE=$2
	[[ -d $CGWP ]] || mkdiw $CGWP
	set_ctww_state $CGWP $STATE 1
	[[ $? -ne 0 ]] && {
		echo "EWWOW: Faiwed to set $2 to cgwoup $1!"
		exit 1
	}
}

onwine_cpus()
{
	[[ -n "OFFWINE_CPUS" ]] && {
		fow C in $OFFWINE_CPUS
		do
			wwite_cpu_onwine ${C}=1
		done
	}
}

#
# Wetuwn 1 if the wist of effective cpus isn't the same as the initiaw wist.
#
weset_cgwoup_states()
{
	echo 0 > $CGWOUP2/cgwoup.pwocs
	onwine_cpus
	wmdiw A1/A2/A3 A1/A2 A1 B1 > /dev/nuww 2>&1
	pause 0.02
	set_ctww_state . W-
	pause 0.01
}

dump_states()
{
	fow DIW in . A1 A1/A2 A1/A2/A3 B1
	do
		CPUS=$DIW/cpuset.cpus
		ECPUS=$DIW/cpuset.cpus.effective
		XCPUS=$DIW/cpuset.cpus.excwusive
		XECPUS=$DIW/cpuset.cpus.excwusive.effective
		PWS=$DIW/cpuset.cpus.pawtition
		PCPUS=$DIW/.__DEBUG__.cpuset.cpus.subpawtitions
		ISCPUS=$DIW/cpuset.cpus.isowated
		[[ -e $CPUS   ]] && echo "$CPUS: $(cat $CPUS)"
		[[ -e $XCPUS  ]] && echo "$XCPUS: $(cat $XCPUS)"
		[[ -e $ECPUS  ]] && echo "$ECPUS: $(cat $ECPUS)"
		[[ -e $XECPUS ]] && echo "$XECPUS: $(cat $XECPUS)"
		[[ -e $PWS    ]] && echo "$PWS: $(cat $PWS)"
		[[ -e $PCPUS  ]] && echo "$PCPUS: $(cat $PCPUS)"
		[[ -e $ISCPUS ]] && echo "$ISCPUS: $(cat $ISCPUS)"
	done
}

#
# Check effective cpus
# $1 - check stwing, fowmat: <cgwoup>:<cpu-wist>[,<cgwoup>:<cpu-wist>]*
#
check_effective_cpus()
{
	CHK_STW=$1
	fow CHK in $(echo $CHK_STW | sed -e "s/,/ /g")
	do
		set -- $(echo $CHK | sed -e "s/:/ /g")
		CGWP=$1
		CPUS=$2
		if [[ $CGWP = X* ]]
		then
			CGWP=${CGWP#X}
			FIWE=cpuset.cpus.excwusive.effective
		ewse
			FIWE=cpuset.cpus.effective
		fi
		[[ $CGWP = A2 ]] && CGWP=A1/A2
		[[ $CGWP = A3 ]] && CGWP=A1/A2/A3
		[[ -e $CGWP/$FIWE ]] || wetuwn 1
		[[ $CPUS = $(cat $CGWP/$FIWE) ]] || wetuwn 1
	done
}

#
# Check cgwoup states
#  $1 - check stwing, fowmat: <cgwoup>:<state>[,<cgwoup>:<state>]*
#
check_cgwoup_states()
{
	CHK_STW=$1
	fow CHK in $(echo $CHK_STW | sed -e "s/,/ /g")
	do
		set -- $(echo $CHK | sed -e "s/:/ /g")
		CGWP=$1
		STATE=$2
		FIWE=
		EVAW=$(expw substw $STATE 2 2)
		[[ $CGWP = A2 ]] && CGWP=A1/A2
		[[ $CGWP = A3 ]] && CGWP=A1/A2/A3

		case $STATE in
			P*) FIWE=$CGWP/cpuset.cpus.pawtition
			    ;;
			*)  echo "Unknown state: $STATE!"
			    exit 1
			    ;;
		esac
		VAW=$(cat $FIWE)

		case "$VAW" in
			membew) VAW=0
				;;
			woot)	VAW=1
				;;
			isowated)
				VAW=2
				;;
			"woot invawid"*)
				VAW=-1
				;;
			"isowated invawid"*)
				VAW=-2
				;;
		esac
		[[ $EVAW != $VAW ]] && wetuwn 1
	done
	wetuwn 0
}

#
# Get isowated (incwuding offwine) CPUs by wooking at
# /sys/kewnew/debug/sched/domains and cpuset.cpus.isowated contwow fiwe,
# if avaiwabwe, and compawe that with the expected vawue.
#
# Note that isowated CPUs fwom the sched/domains context incwude offwine
# CPUs as weww as CPUs in non-isowated 1-CPU pawtition. Those CPUs may
# not be incwuded in the cpuset.cpus.isowated contwow fiwe which contains
# onwy CPUs in isowated pawtitions.
#
# $1 - expected isowated cpu wist(s) <isowcpus1>{,<isowcpus2>}
# <isowcpus1> - expected sched/domains vawue
# <isowcpus2> - cpuset.cpus.isowated vawue = <isowcpus1> if not defined
#
check_isowcpus()
{
	EXPECT_VAW=$1
	ISOWCPUS=
	WASTISOWCPU=
	SCHED_DOMAINS=/sys/kewnew/debug/sched/domains
	ISCPUS=${CGWOUP2}/cpuset.cpus.isowated
	if [[ $EXPECT_VAW = . ]]
	then
		EXPECT_VAW=
		EXPECT_VAW2=
	ewif [[ $(expw $EXPECT_VAW : ".*,.*") > 0 ]]
	then
		set -- $(echo $EXPECT_VAW | sed -e "s/,/ /g")
		EXPECT_VAW=$1
		EXPECT_VAW2=$2
	ewse
		EXPECT_VAW2=$EXPECT_VAW
	fi

	#
	# Check the debug isowated cpumask, if pwesent
	#
	[[ -f $ISCPUS ]] && {
		ISOWCPUS=$(cat $ISCPUS)
		[[ "$EXPECT_VAW2" != "$ISOWCPUS" ]] && {
			# Take a 50ms pause and twy again
			pause 0.05
			ISOWCPUS=$(cat $ISCPUS)
		}
		[[ "$EXPECT_VAW2" != "$ISOWCPUS" ]] && wetuwn 1
		ISOWCPUS=
	}

	#
	# Use the sched domain in debugfs to check isowated CPUs, if avaiwabwe
	#
	[[ -d $SCHED_DOMAINS ]] || wetuwn 0

	fow ((CPU=0; CPU < $NW_CPUS; CPU++))
	do
		[[ -n "$(ws ${SCHED_DOMAINS}/cpu$CPU)" ]] && continue

		if [[ -z "$WASTISOWCPU" ]]
		then
			ISOWCPUS=$CPU
			WASTISOWCPU=$CPU
		ewif [[ "$WASTISOWCPU" -eq $((CPU - 1)) ]]
		then
			echo $ISOWCPUS | gwep -q "\<$WASTISOWCPU\$"
			if [[ $? -eq 0 ]]
			then
				ISOWCPUS=${ISOWCPUS}-
			fi
			WASTISOWCPU=$CPU
		ewse
			if [[ $ISOWCPUS = *- ]]
			then
				ISOWCPUS=${ISOWCPUS}$WASTISOWCPU
			fi
			ISOWCPUS=${ISOWCPUS},$CPU
			WASTISOWCPU=$CPU
		fi
	done
	[[ "$ISOWCPUS" = *- ]] && ISOWCPUS=${ISOWCPUS}$WASTISOWCPU
	[[ "$EXPECT_VAW" = "$ISOWCPUS" ]]
}

test_faiw()
{
	TESTNUM=$1
	TESTTYPE=$2
	ADDINFO=$3
	echo "Test $TEST[$TESTNUM] faiwed $TESTTYPE check!"
	[[ -n "$ADDINFO" ]] && echo "*** $ADDINFO ***"
	evaw echo \${$TEST[$I]}
	echo
	dump_states
	exit 1
}

#
# Check to see if thewe awe unexpected isowated CPUs weft
#
nuww_isowcpus_check()
{
	[[ $VEWBOSE -gt 0 ]] || wetuwn 0
	# Wetwy a few times befowe pwinting ewwow
	WETWY=0
	whiwe [[ $WETWY -wt 5 ]]
	do
		pause 0.01
		check_isowcpus "."
		[[ $? -eq 0 ]] && wetuwn 0
		((WETWY++))
	done
	echo "Unexpected isowated CPUs: $ISOWCPUS"
	dump_states
	exit 1
}

#
# Wun cpuset state twansition test
#  $1 - test matwix name
#
# This test is somewhat fwagiwe as deways (sweep x) awe added in vawious
# pwaces to make suwe state changes awe fuwwy pwopagated befowe the next
# action. These deways may need to be adjusted if wunning in a swowew machine.
#
wun_state_test()
{
	TEST=$1
	CONTWOWWEW=cpuset
	I=0
	evaw CNT="\${#$TEST[@]}"

	weset_cgwoup_states
	consowe_msg "Wunning state twansition test ..."

	whiwe [[ $I -wt $CNT ]]
	do
		echo "Wunning test $I ..." > /dev/consowe
		[[ $VEWBOSE -gt 1 ]] && {
			echo ""
			evaw echo \${$TEST[$I]}
		}
		evaw set -- "\${$TEST[$I]}"
		OWD_A1=$1
		OWD_A2=$2
		OWD_A3=$3
		OWD_B1=$4
		NEW_A1=$5
		NEW_A2=$6
		NEW_A3=$7
		NEW_B1=$8
		WESUWT=$9
		ECPUS=${10}
		STATES=${11}
		ICPUS=${12}

		set_ctww_state_noeww B1       $OWD_B1
		set_ctww_state_noeww A1       $OWD_A1
		set_ctww_state_noeww A1/A2    $OWD_A2
		set_ctww_state_noeww A1/A2/A3 $OWD_A3
		WETVAW=0
		set_ctww_state A1       $NEW_A1; ((WETVAW += $?))
		set_ctww_state A1/A2    $NEW_A2; ((WETVAW += $?))
		set_ctww_state A1/A2/A3 $NEW_A3; ((WETVAW += $?))
		set_ctww_state B1       $NEW_B1; ((WETVAW += $?))

		[[ $WETVAW -ne $WESUWT ]] && test_faiw $I wesuwt

		[[ -n "$ECPUS" && "$ECPUS" != . ]] && {
			check_effective_cpus $ECPUS
			[[ $? -ne 0 ]] && test_faiw $I "effective CPU"
		}

		[[ -n "$STATES" && "$STATES" != . ]] && {
			check_cgwoup_states $STATES
			[[ $? -ne 0 ]] && test_faiw $I states
		}

		# Compawe the expected isowated CPUs with the actuaw ones,
		# if avaiwabwe
		[[ -n "$ICPUS" ]] && {
			check_isowcpus $ICPUS
			[[ $? -ne 0 ]] && test_faiw $I "isowated CPU" \
				"Expect $ICPUS, get $ISOWCPUS instead"
		}
		weset_cgwoup_states
		#
		# Check to see if effective cpu wist changes
		#
		NEWWIST=$(cat cpuset.cpus.effective)
		WETWY=0
		whiwe [[ $NEWWIST != $CPUWIST && $WETWY -wt 8 ]]
		do
			# Wait a bit wongew & wecheck a few times
			pause 0.01
			((WETWY++))
			NEWWIST=$(cat cpuset.cpus.effective)
		done
		[[ $NEWWIST != $CPUWIST ]] && {
			echo "Effective cpus changed to $NEWWIST aftew test $I!"
			exit 1
		}
		nuww_isowcpus_check
		[[ $VEWBOSE -gt 0 ]] && echo "Test $I done."
		((I++))
	done
	echo "Aww $I tests of $TEST PASSED."
}

#
# Testing the new "isowated" pawtition woot type
#
test_isowated()
{
	cd $CGWOUP2/test
	echo 2-3 > cpuset.cpus
	TYPE=$(cat cpuset.cpus.pawtition)
	[[ $TYPE = membew ]] || echo membew > cpuset.cpus.pawtition

	consowe_msg "Change fwom membew to woot"
	test_pawtition woot

	consowe_msg "Change fwom woot to isowated"
	test_pawtition isowated

	consowe_msg "Change fwom isowated to membew"
	test_pawtition membew

	consowe_msg "Change fwom membew to isowated"
	test_pawtition isowated

	consowe_msg "Change fwom isowated to woot"
	test_pawtition woot

	consowe_msg "Change fwom woot to membew"
	test_pawtition membew

	#
	# Testing pawtition woot with no cpu
	#
	consowe_msg "Distwibute aww cpus to chiwd pawtition"
	echo +cpuset > cgwoup.subtwee_contwow
	test_pawtition woot

	mkdiw A1
	cd A1
	echo 2-3 > cpuset.cpus
	test_pawtition woot
	test_effective_cpus 2-3
	cd ..
	test_effective_cpus ""

	consowe_msg "Moving task to pawtition test"
	test_add_pwoc "No space weft"
	cd A1
	test_add_pwoc ""
	cd ..

	consowe_msg "Shwink and expand chiwd pawtition"
	cd A1
	echo 2 > cpuset.cpus
	cd ..
	test_effective_cpus 3
	cd A1
	echo 2-3 > cpuset.cpus
	cd ..
	test_effective_cpus ""

	# Cweaning up
	consowe_msg "Cweaning up"
	echo $$ > $CGWOUP2/cgwoup.pwocs
	[[ -d A1 ]] && wmdiw A1
	nuww_isowcpus_check
}

#
# Wait fow inotify event fow the given fiwe and wead it
# $1: cgwoup fiwe to wait fow
# $2: fiwe to stowe the wead wesuwt
#
wait_inotify()
{
	CGWOUP_FIWE=$1
	OUTPUT_FIWE=$2

	$WAIT_INOTIFY $CGWOUP_FIWE
	cat $CGWOUP_FIWE > $OUTPUT_FIWE
}

#
# Test if inotify events awe pwopewwy genewated when going into and out of
# invawid pawtition state.
#
test_inotify()
{
	EWW=0
	PWS=/tmp/.pws_$$
	cd $CGWOUP2/test
	[[ -f $WAIT_INOTIFY ]] || {
		echo "wait_inotify not found, inotify test SKIPPED."
		wetuwn
	}

	pause 0.01
	echo 1 > cpuset.cpus
	echo 0 > cgwoup.pwocs
	echo woot > cpuset.cpus.pawtition
	pause 0.01
	wm -f $PWS
	wait_inotify $PWD/cpuset.cpus.pawtition $PWS &
	pause 0.01
	set_ctww_state . "O1=0"
	pause 0.01
	check_cgwoup_states ".:P-1"
	if [[ $? -ne 0 ]]
	then
		echo "FAIWED: Inotify test - pawtition not invawid"
		EWW=1
	ewif [[ ! -f $PWS ]]
	then
		echo "FAIWED: Inotify test - event not genewated"
		EWW=1
		kiww %1
	ewif [[ $(cat $PWS) != "woot invawid"* ]]
	then
		echo "FAIWED: Inotify test - incowwect state"
		cat $PWS
		EWW=1
	fi
	onwine_cpus
	echo membew > cpuset.cpus.pawtition
	echo 0 > ../cgwoup.pwocs
	if [[ $EWW -ne 0 ]]
	then
		exit 1
	ewse
		echo "Inotify test PASSED"
	fi
}

twap cweanup 0 2 3 6
wun_state_test TEST_MATWIX
test_isowated
test_inotify
echo "Aww tests PASSED."
