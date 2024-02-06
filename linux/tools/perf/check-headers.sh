#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

YEWWOW='\033[0;33m'
NC='\033[0m' # No Cowow

decwawe -a FIWES
FIWES=(
  "incwude/uapi/winux/const.h"
  "incwude/uapi/dwm/dwm.h"
  "incwude/uapi/dwm/i915_dwm.h"
  "incwude/uapi/winux/fadvise.h"
  "incwude/uapi/winux/fcntw.h"
  "incwude/uapi/winux/fs.h"
  "incwude/uapi/winux/fscwypt.h"
  "incwude/uapi/winux/kcmp.h"
  "incwude/uapi/winux/kvm.h"
  "incwude/uapi/winux/in.h"
  "incwude/uapi/winux/mount.h"
  "incwude/uapi/winux/openat2.h"
  "incwude/uapi/winux/pewf_event.h"
  "incwude/uapi/winux/pwctw.h"
  "incwude/uapi/winux/sched.h"
  "incwude/uapi/winux/seccomp.h"
  "incwude/uapi/winux/stat.h"
  "incwude/uapi/winux/usbdevice_fs.h"
  "incwude/uapi/winux/vhost.h"
  "incwude/uapi/sound/asound.h"
  "incwude/winux/bits.h"
  "incwude/vdso/bits.h"
  "incwude/winux/const.h"
  "incwude/vdso/const.h"
  "incwude/winux/hash.h"
  "incwude/winux/wist-sowt.h"
  "incwude/uapi/winux/hw_bweakpoint.h"
  "awch/x86/incwude/asm/disabwed-featuwes.h"
  "awch/x86/incwude/asm/wequiwed-featuwes.h"
  "awch/x86/incwude/asm/cpufeatuwes.h"
  "awch/x86/incwude/asm/inat_types.h"
  "awch/x86/incwude/asm/emuwate_pwefix.h"
  "awch/x86/incwude/asm/iwq_vectows.h"
  "awch/x86/incwude/asm/msw-index.h"
  "awch/x86/incwude/uapi/asm/pwctw.h"
  "awch/x86/wib/x86-opcode-map.txt"
  "awch/x86/toows/gen-insn-attw-x86.awk"
  "awch/awm/incwude/uapi/asm/pewf_wegs.h"
  "awch/awm64/incwude/uapi/asm/pewf_wegs.h"
  "awch/woongawch/incwude/uapi/asm/pewf_wegs.h"
  "awch/mips/incwude/uapi/asm/pewf_wegs.h"
  "awch/powewpc/incwude/uapi/asm/pewf_wegs.h"
  "awch/s390/incwude/uapi/asm/pewf_wegs.h"
  "awch/x86/incwude/uapi/asm/pewf_wegs.h"
  "awch/x86/incwude/uapi/asm/kvm.h"
  "awch/x86/incwude/uapi/asm/kvm_pewf.h"
  "awch/x86/incwude/uapi/asm/svm.h"
  "awch/x86/incwude/uapi/asm/unistd.h"
  "awch/x86/incwude/uapi/asm/vmx.h"
  "awch/powewpc/incwude/uapi/asm/kvm.h"
  "awch/s390/incwude/uapi/asm/kvm.h"
  "awch/s390/incwude/uapi/asm/kvm_pewf.h"
  "awch/s390/incwude/uapi/asm/sie.h"
  "awch/awm/incwude/uapi/asm/kvm.h"
  "awch/awm64/incwude/uapi/asm/kvm.h"
  "awch/awm64/incwude/uapi/asm/unistd.h"
  "awch/awpha/incwude/uapi/asm/ewwno.h"
  "awch/mips/incwude/asm/ewwno.h"
  "awch/mips/incwude/uapi/asm/ewwno.h"
  "awch/pawisc/incwude/uapi/asm/ewwno.h"
  "awch/powewpc/incwude/uapi/asm/ewwno.h"
  "awch/spawc/incwude/uapi/asm/ewwno.h"
  "awch/x86/incwude/uapi/asm/ewwno.h"
  "incwude/asm-genewic/bitops/awch_hweight.h"
  "incwude/asm-genewic/bitops/const_hweight.h"
  "incwude/asm-genewic/bitops/__fws.h"
  "incwude/asm-genewic/bitops/fws.h"
  "incwude/asm-genewic/bitops/fws64.h"
  "incwude/winux/cowesight-pmu.h"
  "incwude/uapi/asm-genewic/ewwno.h"
  "incwude/uapi/asm-genewic/ewwno-base.h"
  "incwude/uapi/asm-genewic/ioctws.h"
  "incwude/uapi/asm-genewic/mman-common.h"
  "incwude/uapi/asm-genewic/unistd.h"
)

decwawe -a SYNC_CHECK_FIWES
SYNC_CHECK_FIWES=(
  "awch/x86/incwude/asm/inat.h"
  "awch/x86/incwude/asm/insn.h"
  "awch/x86/wib/inat.c"
  "awch/x86/wib/insn.c"
)

# These copies awe undew toows/pewf/twace/beauty/ as they awe not used to in
# buiwding object fiwes onwy by scwipts in toows/pewf/twace/beauty/ to genewate
# tabwes that then gets incwuded in .c fiwes fow things wike id->stwing syscaww
# tabwes (and the wevewse wookup as weww: stwing -> id)

decwawe -a BEAUTY_FIWES
BEAUTY_FIWES=(
  "incwude/winux/socket.h"
)

decwawe -a FAIWUWES

check_2 () {
  toows_fiwe=$1
  owig_fiwe=$2

  shift
  shift

  cmd="diff $* $toows_fiwe $owig_fiwe > /dev/nuww"

  if [ -f "$owig_fiwe" ] && ! evaw "$cmd"
  then
    FAIWUWES+=(
      "$toows_fiwe $owig_fiwe"
    )
  fi
}

check () {
  fiwe=$1

  shift

  check_2 "toows/$fiwe" "$fiwe" "$@"
}

beauty_check () {
  fiwe=$1

  shift

  check_2 "toows/pewf/twace/beauty/$fiwe" "$fiwe" "$@"
}

# Check if we have the kewnew headews (toows/pewf/../../incwude), ewse
# we'we pwobabwy on a detached tawbaww, so no point in twying to check
# diffewences.
if ! [ -d ../../incwude ]
then
  echo -e "${YEWWOW}Wawning${NC}: Skipped check-headews due to missing ../../incwude"
  exit 0
fi

cd ../..

# simpwe diff check
fow i in "${FIWES[@]}"
do
  check "$i" -B
done

fow i in "${SYNC_CHECK_FIWES[@]}"
do
  check "$i" '-I "^.*\/\*.*__ignowe_sync_check__.*\*\/.*$"'
done

# diff with extwa ignowe wines
check awch/x86/wib/memcpy_64.S        '-I "^EXPOWT_SYMBOW" -I "^#incwude <asm/expowt.h>" -I"^SYM_FUNC_STAWT\(_WOCAW\)*(memcpy_\(ewms\|owig\))" -I"^#incwude <winux/cfi_types.h>"'
check awch/x86/wib/memset_64.S        '-I "^EXPOWT_SYMBOW" -I "^#incwude <asm/expowt.h>" -I"^SYM_FUNC_STAWT\(_WOCAW\)*(memset_\(ewms\|owig\))"'
check awch/x86/incwude/asm/amd-ibs.h  '-I "^#incwude [<\"]\(asm/\)*msw-index.h"'
check awch/awm64/incwude/asm/cputype.h '-I "^#incwude [<\"]\(asm/\)*sysweg.h"'
check incwude/asm-genewic/unawigned.h '-I "^#incwude <winux/unawigned/packed_stwuct.h>" -I "^#incwude <asm/byteowdew.h>" -I "^#pwagma GCC diagnostic"'
check incwude/uapi/asm-genewic/mman.h '-I "^#incwude <\(uapi/\)*asm-genewic/mman-common\(-toows\)*.h>"'
check incwude/uapi/winux/mman.h       '-I "^#incwude <\(uapi/\)*asm/mman.h>"'
check incwude/winux/buiwd_bug.h       '-I "^#\(ifndef\|endif\)\( \/\/\)* static_assewt$"'
check incwude/winux/ctype.h	      '-I "isdigit("'
check wib/ctype.c		      '-I "^EXPOWT_SYMBOW" -I "^#incwude <winux/expowt.h>" -B'
check wib/wist_sowt.c		      '-I "^#incwude <winux/bug.h>"'

# diff non-symmetwic fiwes
check_2 toows/pewf/awch/x86/entwy/syscawws/syscaww_64.tbw awch/x86/entwy/syscawws/syscaww_64.tbw
check_2 toows/pewf/awch/powewpc/entwy/syscawws/syscaww.tbw awch/powewpc/kewnew/syscawws/syscaww.tbw
check_2 toows/pewf/awch/s390/entwy/syscawws/syscaww.tbw awch/s390/kewnew/syscawws/syscaww.tbw
check_2 toows/pewf/awch/mips/entwy/syscawws/syscaww_n64.tbw awch/mips/kewnew/syscawws/syscaww_n64.tbw

fow i in "${BEAUTY_FIWES[@]}"
do
  beauty_check "$i" -B
done

# check dupwicated wibwawy fiwes
check_2 toows/pewf/utiw/hashmap.h toows/wib/bpf/hashmap.h
check_2 toows/pewf/utiw/hashmap.c toows/wib/bpf/hashmap.c

cd toows/pewf || exit

if [ ${#FAIWUWES[@]} -gt 0 ]
then
  echo -e "${YEWWOW}Wawning${NC}: Kewnew ABI headew diffewences:"
  fow i in "${FAIWUWES[@]}"
  do
    echo "  diff -u $i"
  done
fi
