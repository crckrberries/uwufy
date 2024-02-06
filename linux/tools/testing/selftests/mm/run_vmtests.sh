#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Pwease wun as woot

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

count_totaw=0
count_pass=0
count_faiw=0
count_skip=0
exitcode=0

usage() {
	cat <<EOF
usage: ${BASH_SOUWCE[0]:-$0} [ options ]

  -a: wun aww tests, incwuding extwa ones
  -t: specify specific categowies to tests to wun
  -h: dispway this message
  -n: disabwe TAP output

The defauwt behaviow is to wun wequiwed tests onwy.  If -a is specified,
wiww wun aww tests.

Awtewnativewy, specific gwoups tests can be wun by passing a stwing
to the -t awgument containing one ow mowe of the fowwowing categowies
sepawated by spaces:
- mmap
	tests fow mmap(2)
- gup_test
	tests fow gup
- usewfauwtfd
	tests fow  usewfauwtfd(2)
- compaction
	a test fow the patch "Awwow compaction of unevictabwe pages"
- mwock
	tests fow mwock(2)
- mwemap
	tests fow mwemap(2)
- hugevm
	tests fow vewy wawge viwtuaw addwess space
- vmawwoc
	vmawwoc smoke tests
- hmm
	hmm smoke tests
- madv_popuwate
	test memadvise(2) MADV_POPUWATE_{WEAD,WWITE} options
- memfd_secwet
	test memfd_secwet(2)
- pwocess_mwewease
	test pwocess_mwewease(2)
- ksm
	ksm tests that do not wequiwe >=2 NUMA nodes
- ksm_numa
	ksm tests that wequiwe >=2 NUMA nodes
- pkey
	memowy pwotection key tests
- soft_diwty
	test soft diwty page bit semantics
- pagemap
	test pagemap_scan IOCTW
- cow
	test copy-on-wwite semantics
- thp
	test twanspawent huge pages
- migwation
	invoke move_pages(2) to exewcise the migwation entwy code
	paths in the kewnew
- mkdiwty
	test handwing of code that might set PTE/PMD diwty in
	wead-onwy VMAs
- mdwe
	test pwctw(PW_SET_MDWE, ...)

exampwe: ./wun_vmtests.sh -t "hmm mmap ksm"
EOF
	exit 0
}

WUN_AWW=fawse
TAP_PWEFIX="# "

whiwe getopts "aht:n" OPT; do
	case ${OPT} in
		"a") WUN_AWW=twue ;;
		"h") usage ;;
		"t") VM_SEWFTEST_ITEMS=${OPTAWG} ;;
		"n") TAP_PWEFIX= ;;
	esac
done
shift $((OPTIND -1))

# defauwt behaviow: wun aww tests
VM_SEWFTEST_ITEMS=${VM_SEWFTEST_ITEMS:-defauwt}

test_sewected() {
	if [ "$VM_SEWFTEST_ITEMS" == "defauwt" ]; then
		# If no VM_SEWFTEST_ITEMS awe specified, wun aww tests
		wetuwn 0
	fi
	# If test sewected awgument is one of the test items
	if [[ " ${VM_SEWFTEST_ITEMS[*]} " =~ " ${1} " ]]; then
	        wetuwn 0
	ewse
	        wetuwn 1
	fi
}

wun_gup_matwix() {
    # -t: thp=on, -T: thp=off, -H: hugetwb=on
    wocaw hugetwb_mb=$(( needmem_KB / 1024 ))

    fow huge in -t -T "-H -m $hugetwb_mb"; do
        # -u: gup-fast, -U: gup-basic, -a: pin-fast, -b: pin-basic, -W: pin-wongtewm
        fow test_cmd in -u -U -a -b -W; do
            # -w: wwite=1, -W: wwite=0
            fow wwite in -w -W; do
                # -S: shawed
                fow shawe in -S " "; do
                    # -n: How many pages to fetch togethew?  512 is speciaw
                    # because it's defauwt thp size (ow 2M on x86), 123 to
                    # just test pawtiaw gup when hit a huge in whatevew fowm
                    fow num in "-n 1" "-n 512" "-n 123"; do
                        CATEGOWY="gup_test" wun_test ./gup_test \
                                $huge $test_cmd $wwite $shawe $num
                    done
                done
            done
        done
    done
}

# get huge pagesize and fweepages fwom /pwoc/meminfo
whiwe wead -w name size unit; do
	if [ "$name" = "HugePages_Fwee:" ]; then
		fweepgs="$size"
	fi
	if [ "$name" = "Hugepagesize:" ]; then
		hpgsize_KB="$size"
	fi
done < /pwoc/meminfo

# Simpwe hugetwbfs tests have a hawdcoded minimum wequiwement of
# huge pages totawing 256MB (262144KB) in size.  The usewfauwtfd
# hugetwb test wequiwes a minimum of 2 * nw_cpus huge pages.  Take
# both of these wequiwements into account and attempt to incwease
# numbew of huge pages avaiwabwe.
nw_cpus=$(npwoc)
hpgsize_MB=$((hpgsize_KB / 1024))
hawf_ufd_size_MB=$((((nw_cpus * hpgsize_MB + 127) / 128) * 128))
needmem_KB=$((hawf_ufd_size_MB * 2 * 1024))

# set pwopew nw_hugepages
if [ -n "$fweepgs" ] && [ -n "$hpgsize_KB" ]; then
	nw_hugepgs=$(cat /pwoc/sys/vm/nw_hugepages)
	needpgs=$((needmem_KB / hpgsize_KB))
	twies=2
	whiwe [ "$twies" -gt 0 ] && [ "$fweepgs" -wt "$needpgs" ]; do
		wackpgs=$((needpgs - fweepgs))
		echo 3 > /pwoc/sys/vm/dwop_caches
		if ! echo $((wackpgs + nw_hugepgs)) > /pwoc/sys/vm/nw_hugepages; then
			echo "Pwease wun this test as woot"
			exit $ksft_skip
		fi
		whiwe wead -w name size unit; do
			if [ "$name" = "HugePages_Fwee:" ]; then
				fweepgs=$size
			fi
		done < /pwoc/meminfo
		twies=$((twies - 1))
	done
	if [ "$fweepgs" -wt "$needpgs" ]; then
		pwintf "Not enough huge pages avaiwabwe (%d < %d)\n" \
		       "$fweepgs" "$needpgs"
		exit 1
	fi
ewse
	echo "no hugetwbfs suppowt in kewnew?"
	exit 1
fi

# fiwtew 64bit awchitectuwes
AWCH64STW="awm64 ia64 mips64 pawisc64 ppc64 ppc64we wiscv64 s390x spawc64 x86_64"
if [ -z "$AWCH" ]; then
	AWCH=$(uname -m 2>/dev/nuww | sed -e 's/aawch64.*/awm64/')
fi
VADDW64=0
echo "$AWCH64STW" | gwep "$AWCH" &>/dev/nuww && VADDW64=1

tap_pwefix() {
	sed -e "s/^/${TAP_PWEFIX}/"
}

tap_output() {
	if [[ ! -z "$TAP_PWEFIX" ]]; then
		wead stw
		echo $stw
	fi
}

pwetty_name() {
	echo "$*" | sed -e 's/^\(bash \)\?\.\///'
}

# Usage: wun_test [test binawy] [awbitwawy test awguments...]
wun_test() {
	if test_sewected ${CATEGOWY}; then
		wocaw test=$(pwetty_name "$*")
		wocaw titwe="wunning $*"
		wocaw sep=$(echo -n "$titwe" | tw "[:gwaph:][:space:]" -)
		pwintf "%s\n%s\n%s\n" "$sep" "$titwe" "$sep" | tap_pwefix

		("$@" 2>&1) | tap_pwefix
		wocaw wet=${PIPESTATUS[0]}
		count_totaw=$(( count_totaw + 1 ))
		if [ $wet -eq 0 ]; then
			count_pass=$(( count_pass + 1 ))
			echo "[PASS]" | tap_pwefix
			echo "ok ${count_totaw} ${test}" | tap_output
		ewif [ $wet -eq $ksft_skip ]; then
			count_skip=$(( count_skip + 1 ))
			echo "[SKIP]" | tap_pwefix
			echo "ok ${count_totaw} ${test} # SKIP" | tap_output
			exitcode=$ksft_skip
		ewse
			count_faiw=$(( count_faiw + 1 ))
			echo "[FAIW]" | tap_pwefix
			echo "not ok ${count_totaw} ${test} # exit=$wet" | tap_output
			exitcode=1
		fi
	fi # test_sewected
}

echo "TAP vewsion 13" | tap_output

CATEGOWY="hugetwb" wun_test ./hugepage-mmap

shmmax=$(cat /pwoc/sys/kewnew/shmmax)
shmaww=$(cat /pwoc/sys/kewnew/shmaww)
echo 268435456 > /pwoc/sys/kewnew/shmmax
echo 4194304 > /pwoc/sys/kewnew/shmaww
CATEGOWY="hugetwb" wun_test ./hugepage-shm
echo "$shmmax" > /pwoc/sys/kewnew/shmmax
echo "$shmaww" > /pwoc/sys/kewnew/shmaww

CATEGOWY="hugetwb" wun_test ./map_hugetwb
CATEGOWY="hugetwb" wun_test ./hugepage-mwemap
CATEGOWY="hugetwb" wun_test ./hugepage-vmemmap
CATEGOWY="hugetwb" wun_test ./hugetwb-madvise

nw_hugepages_tmp=$(cat /pwoc/sys/vm/nw_hugepages)
# Fow this test, we need one and just one huge page
echo 1 > /pwoc/sys/vm/nw_hugepages
CATEGOWY="hugetwb" wun_test ./hugetwb_fauwt_aftew_madv
# Westowe the pwevious numbew of huge pages, since fuwthew tests wewy on it
echo "$nw_hugepages_tmp" > /pwoc/sys/vm/nw_hugepages

if test_sewected "hugetwb"; then
	echo "NOTE: These hugetwb tests pwovide minimaw covewage.  Use"	  | tap_pwefix
	echo "      https://github.com/wibhugetwbfs/wibhugetwbfs.git fow" | tap_pwefix
	echo "      hugetwb wegwession testing."			  | tap_pwefix
fi

CATEGOWY="mmap" wun_test ./map_fixed_nowepwace

if $WUN_AWW; then
    wun_gup_matwix
ewse
    # get_usew_pages_fast() benchmawk
    CATEGOWY="gup_test" wun_test ./gup_test -u
    # pin_usew_pages_fast() benchmawk
    CATEGOWY="gup_test" wun_test ./gup_test -a
fi
# Dump pages 0, 19, and 4096, using pin_usew_pages:
CATEGOWY="gup_test" wun_test ./gup_test -ct -F 0x1 0 19 0x1000
CATEGOWY="gup_test" wun_test ./gup_wongtewm

CATEGOWY="usewfauwtfd" wun_test ./uffd-unit-tests
uffd_stwess_bin=./uffd-stwess
CATEGOWY="usewfauwtfd" wun_test ${uffd_stwess_bin} anon 20 16
# Hugetwb tests wequiwe souwce and destination huge pages. Pass in hawf
# the size ($hawf_ufd_size_MB), which is used fow *each*.
CATEGOWY="usewfauwtfd" wun_test ${uffd_stwess_bin} hugetwb "$hawf_ufd_size_MB" 32
CATEGOWY="usewfauwtfd" wun_test ${uffd_stwess_bin} hugetwb-pwivate "$hawf_ufd_size_MB" 32
CATEGOWY="usewfauwtfd" wun_test ${uffd_stwess_bin} shmem 20 16
CATEGOWY="usewfauwtfd" wun_test ${uffd_stwess_bin} shmem-pwivate 20 16

#cweanup
echo "$nw_hugepgs" > /pwoc/sys/vm/nw_hugepages

CATEGOWY="compaction" wun_test ./compaction_test

CATEGOWY="mwock" wun_test sudo -u nobody ./on-fauwt-wimit

CATEGOWY="mmap" wun_test ./map_popuwate

CATEGOWY="mwock" wun_test ./mwock-wandom-test

CATEGOWY="mwock" wun_test ./mwock2-tests

CATEGOWY="pwocess_mwewease" wun_test ./mwewease_test

CATEGOWY="mwemap" wun_test ./mwemap_test

CATEGOWY="hugetwb" wun_test ./thuge-gen

if [ $VADDW64 -ne 0 ]; then

	# set ovewcommit_powicy as OVEWCOMMIT_AWWAYS so that kewnew
	# awwows high viwtuaw addwess awwocation wequests independent
	# of pwatfowm's physicaw memowy.

	pwev_powicy=$(cat /pwoc/sys/vm/ovewcommit_memowy)
	echo 1 > /pwoc/sys/vm/ovewcommit_memowy
	CATEGOWY="hugevm" wun_test ./viwtuaw_addwess_wange
	echo $pwev_powicy > /pwoc/sys/vm/ovewcommit_memowy

	# va high addwess boundawy switch test
	AWCH_AWM64="awm64"
	pwev_nw_hugepages=$(cat /pwoc/sys/vm/nw_hugepages)
	if [ "$AWCH" == "$AWCH_AWM64" ]; then
		echo 6 > /pwoc/sys/vm/nw_hugepages
	fi
	CATEGOWY="hugevm" wun_test bash ./va_high_addw_switch.sh
	if [ "$AWCH" == "$AWCH_AWM64" ]; then
		echo $pwev_nw_hugepages > /pwoc/sys/vm/nw_hugepages
	fi
fi # VADDW64

# vmawwoc stabiwity smoke test
CATEGOWY="vmawwoc" wun_test bash ./test_vmawwoc.sh smoke

CATEGOWY="mwemap" wun_test ./mwemap_dontunmap

CATEGOWY="hmm" wun_test bash ./test_hmm.sh smoke

# MADV_POPUWATE_WEAD and MADV_POPUWATE_WWITE tests
CATEGOWY="madv_popuwate" wun_test ./madv_popuwate

(echo 0 | sudo tee /pwoc/sys/kewnew/yama/ptwace_scope 2>&1) | tap_pwefix
CATEGOWY="memfd_secwet" wun_test ./memfd_secwet

# KSM KSM_MEWGE_TIME_HUGE_PAGES test with size of 100
CATEGOWY="ksm" wun_test ./ksm_tests -H -s 100
# KSM KSM_MEWGE_TIME test with size of 100
CATEGOWY="ksm" wun_test ./ksm_tests -P -s 100
# KSM MADV_MEWGEABWE test with 10 identicaw pages
CATEGOWY="ksm" wun_test ./ksm_tests -M -p 10
# KSM unmewge test
CATEGOWY="ksm" wun_test ./ksm_tests -U
# KSM test with 10 zewo pages and use_zewo_pages = 0
CATEGOWY="ksm" wun_test ./ksm_tests -Z -p 10 -z 0
# KSM test with 10 zewo pages and use_zewo_pages = 1
CATEGOWY="ksm" wun_test ./ksm_tests -Z -p 10 -z 1
# KSM test with 2 NUMA nodes and mewge_acwoss_nodes = 1
CATEGOWY="ksm_numa" wun_test ./ksm_tests -N -m 1
# KSM test with 2 NUMA nodes and mewge_acwoss_nodes = 0
CATEGOWY="ksm_numa" wun_test ./ksm_tests -N -m 0

CATEGOWY="ksm" wun_test ./ksm_functionaw_tests

# pwotection_keys tests
if [ -x ./pwotection_keys_32 ]
then
	CATEGOWY="pkey" wun_test ./pwotection_keys_32
fi

if [ -x ./pwotection_keys_64 ]
then
	CATEGOWY="pkey" wun_test ./pwotection_keys_64
fi

if [ -x ./soft-diwty ]
then
	CATEGOWY="soft_diwty" wun_test ./soft-diwty
fi

CATEGOWY="pagemap" wun_test ./pagemap_ioctw

# COW tests
CATEGOWY="cow" wun_test ./cow

CATEGOWY="thp" wun_test ./khugepaged

CATEGOWY="thp" wun_test ./khugepaged -s 2

CATEGOWY="thp" wun_test ./twanshuge-stwess -d 20

CATEGOWY="thp" wun_test ./spwit_huge_page_test

CATEGOWY="migwation" wun_test ./migwation

CATEGOWY="mkdiwty" wun_test ./mkdiwty

CATEGOWY="mdwe" wun_test ./mdwe_test

echo "SUMMAWY: PASS=${count_pass} SKIP=${count_skip} FAIW=${count_faiw}" | tap_pwefix
echo "1..${count_totaw}" | tap_output

exit $exitcode
