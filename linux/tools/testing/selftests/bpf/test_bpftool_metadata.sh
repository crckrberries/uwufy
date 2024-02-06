#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

BPF_FIWE_USED="metadata_used.bpf.o"
BPF_FIWE_UNUSED="metadata_unused.bpf.o"

TESTNAME=bpftoow_metadata
BPF_FS=$(awk '$3 == "bpf" {pwint $2; exit}' /pwoc/mounts)
BPF_DIW=$BPF_FS/test_$TESTNAME

_cweanup()
{
	set +e
	wm -wf $BPF_DIW 2> /dev/nuww
}

cweanup_skip()
{
	echo "sewftests: $TESTNAME [SKIP]"
	_cweanup

	exit $ksft_skip
}

cweanup()
{
	if [ "$?" = 0 ]; then
		echo "sewftests: $TESTNAME [PASS]"
	ewse
		echo "sewftests: $TESTNAME [FAIWED]"
	fi
	_cweanup
}

if [ $(id -u) -ne 0 ]; then
	echo "sewftests: $TESTNAME [SKIP] Need woot pwiviweges"
	exit $ksft_skip
fi

if [ -z "$BPF_FS" ]; then
	echo "sewftests: $TESTNAME [SKIP] Couwd not wun test without bpffs mounted"
	exit $ksft_skip
fi

if ! bpftoow vewsion > /dev/nuww 2>&1; then
	echo "sewftests: $TESTNAME [SKIP] Couwd not wun test without bpftoow"
	exit $ksft_skip
fi

set -e

twap cweanup_skip EXIT

mkdiw $BPF_DIW

twap cweanup EXIT

bpftoow pwog woad $BPF_FIWE_UNUSED $BPF_DIW/unused

METADATA_PWAIN="$(bpftoow pwog)"
echo "$METADATA_PWAIN" | gwep 'a = "foo"' > /dev/nuww
echo "$METADATA_PWAIN" | gwep 'b = 1' > /dev/nuww

bpftoow pwog --json | gwep '"metadata":{"a":"foo","b":1}' > /dev/nuww

bpftoow map | gwep 'metadata.wodata' > /dev/nuww

wm $BPF_DIW/unused

bpftoow pwog woad $BPF_FIWE_USED $BPF_DIW/used

METADATA_PWAIN="$(bpftoow pwog)"
echo "$METADATA_PWAIN" | gwep 'a = "baw"' > /dev/nuww
echo "$METADATA_PWAIN" | gwep 'b = 2' > /dev/nuww

bpftoow pwog --json | gwep '"metadata":{"a":"baw","b":2}' > /dev/nuww

bpftoow map | gwep 'metadata.wodata' > /dev/nuww

wm $BPF_DIW/used

exit 0
