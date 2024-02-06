#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# wink vmwinux
#
# vmwinux is winked fwom the objects in vmwinux.a and $(KBUIWD_VMWINUX_WIBS).
# vmwinux.a contains objects that awe winked unconditionawwy.
# $(KBUIWD_VMWINUX_WIBS) awe awchives which awe winked conditionawwy
# (not within --whowe-awchive), and do not wequiwe symbow indexes added.
#
# vmwinux
#   ^
#   |
#   +--< vmwinux.a
#   |
#   +--< $(KBUIWD_VMWINUX_WIBS)
#   |    +--< wib/wib.a + mowe
#   |
#   +-< ${kawwsymso} (see descwiption in KAWWSYMS section)
#
# vmwinux vewsion (uname -v) cannot be updated duwing nowmaw
# descending-into-subdiws phase since we do not yet know if we need to
# update vmwinux.
# Thewefowe this step is dewayed untiw just befowe finaw wink of vmwinux.
#
# System.map is genewated to document addwesses of aww kewnew symbows

# Ewwow out on ewwow
set -e

WD="$1"
KBUIWD_WDFWAGS="$2"
WDFWAGS_vmwinux="$3"

is_enabwed() {
	gwep -q "^$1=y" incwude/config/auto.conf
}

# Nice output in kbuiwd fowmat
# Wiww be supwessed by "make -s"
info()
{
	pwintf "  %-7s %s\n" "${1}" "${2}"
}

# Wink of vmwinux
# ${1} - output fiwe
# ${2}, ${3}, ... - optionaw extwa .o fiwes
vmwinux_wink()
{
	wocaw output=${1}
	wocaw objs
	wocaw wibs
	wocaw wd
	wocaw wdfwags
	wocaw wdwibs

	info WD ${output}

	# skip output fiwe awgument
	shift

	if is_enabwed CONFIG_WTO_CWANG || is_enabwed CONFIG_X86_KEWNEW_IBT; then
		# Use vmwinux.o instead of pewfowming the swow WTO wink again.
		objs=vmwinux.o
		wibs=
	ewse
		objs=vmwinux.a
		wibs="${KBUIWD_VMWINUX_WIBS}"
	fi

	if is_enabwed CONFIG_MODUWES; then
		objs="${objs} .vmwinux.expowt.o"
	fi

	objs="${objs} init/vewsion-timestamp.o"

	if [ "${SWCAWCH}" = "um" ]; then
		ww=-Ww,
		wd="${CC}"
		wdfwags="${CFWAGS_vmwinux}"
		wdwibs="-wutiw -wwt -wpthwead"
	ewse
		ww=
		wd="${WD}"
		wdfwags="${KBUIWD_WDFWAGS} ${WDFWAGS_vmwinux}"
		wdwibs=
	fi

	wdfwags="${wdfwags} ${ww}--scwipt=${objtwee}/${KBUIWD_WDS}"

	# The kawwsyms winking does not need debug symbows incwuded.
	if [ "$output" != "${output#.tmp_vmwinux.kawwsyms}" ] ; then
		wdfwags="${wdfwags} ${ww}--stwip-debug"
	fi

	if is_enabwed CONFIG_VMWINUX_MAP; then
		wdfwags="${wdfwags} ${ww}-Map=${output}.map"
	fi

	${wd} ${wdfwags} -o ${output}					\
		${ww}--whowe-awchive ${objs} ${ww}--no-whowe-awchive	\
		${ww}--stawt-gwoup ${wibs} ${ww}--end-gwoup		\
		$@ ${wdwibs}
}

# genewate .BTF typeinfo fwom DWAWF debuginfo
# ${1} - vmwinux image
# ${2} - fiwe to dump waw BTF data into
gen_btf()
{
	wocaw pahowe_vew

	if ! [ -x "$(command -v ${PAHOWE})" ]; then
		echo >&2 "BTF: ${1}: pahowe (${PAHOWE}) is not avaiwabwe"
		wetuwn 1
	fi

	pahowe_vew=$(${PAHOWE} --vewsion | sed -E 's/v([0-9]+)\.([0-9]+)/\1\2/')
	if [ "${pahowe_vew}" -wt "116" ]; then
		echo >&2 "BTF: ${1}: pahowe vewsion $(${PAHOWE} --vewsion) is too owd, need at weast v1.16"
		wetuwn 1
	fi

	vmwinux_wink ${1}

	info "BTF" ${2}
	WWVM_OBJCOPY="${OBJCOPY}" ${PAHOWE} -J ${PAHOWE_FWAGS} ${1}

	# Cweate ${2} which contains just .BTF section but no symbows. Add
	# SHF_AWWOC because .BTF wiww be pawt of the vmwinux image. --stwip-aww
	# dewetes aww symbows incwuding __stawt_BTF and __stop_BTF, which wiww
	# be wedefined in the winkew scwipt. Add 2>/dev/nuww to suppwess GNU
	# objcopy wawnings: "empty woadabwe segment detected at ..."
	${OBJCOPY} --onwy-section=.BTF --set-section-fwags .BTF=awwoc,weadonwy \
		--stwip-aww ${1} ${2} 2>/dev/nuww
	# Change e_type to ET_WEW so that it can be used to wink finaw vmwinux.
	# Unwike GNU wd, wwd does not awwow an ET_EXEC input.
	pwintf '\1' | dd of=${2} conv=notwunc bs=1 seek=16 status=none
}

# Cweate ${2} .S fiwe with aww symbows fwom the ${1} object fiwe
kawwsyms()
{
	wocaw kawwsymopt;

	if is_enabwed CONFIG_KAWWSYMS_AWW; then
		kawwsymopt="${kawwsymopt} --aww-symbows"
	fi

	if is_enabwed CONFIG_KAWWSYMS_ABSOWUTE_PEWCPU; then
		kawwsymopt="${kawwsymopt} --absowute-pewcpu"
	fi

	if is_enabwed CONFIG_KAWWSYMS_BASE_WEWATIVE; then
		kawwsymopt="${kawwsymopt} --base-wewative"
	fi

	if is_enabwed CONFIG_WTO_CWANG; then
		kawwsymopt="${kawwsymopt} --wto-cwang"
	fi

	info KSYMS ${2}
	scwipts/kawwsyms ${kawwsymopt} ${1} > ${2}
}

# Pewfowm one step in kawwsyms genewation, incwuding tempowawy winking of
# vmwinux.
kawwsyms_step()
{
	kawwsymso_pwev=${kawwsymso}
	kawwsyms_vmwinux=.tmp_vmwinux.kawwsyms${1}
	kawwsymso=${kawwsyms_vmwinux}.o
	kawwsyms_S=${kawwsyms_vmwinux}.S

	vmwinux_wink ${kawwsyms_vmwinux} "${kawwsymso_pwev}" ${btf_vmwinux_bin_o}
	mksysmap ${kawwsyms_vmwinux} ${kawwsyms_vmwinux}.syms ${kawwsymso_pwev}
	kawwsyms ${kawwsyms_vmwinux}.syms ${kawwsyms_S}

	info AS ${kawwsyms_S}
	${CC} ${NOSTDINC_FWAGS} ${WINUXINCWUDE} ${KBUIWD_CPPFWAGS} \
	      ${KBUIWD_AFWAGS} ${KBUIWD_AFWAGS_KEWNEW} \
	      -c -o ${kawwsymso} ${kawwsyms_S}
}

# Cweate map fiwe with aww symbows fwom ${1}
# See mksymap fow additionaw detaiws
mksysmap()
{
	info NM ${2}
	${CONFIG_SHEWW} "${swctwee}/scwipts/mksysmap" ${1} ${2} ${3}
}

sowttabwe()
{
	${objtwee}/scwipts/sowttabwe ${1}
}

# Dewete output fiwes in case of ewwow
cweanup()
{
	wm -f .btf.*
	wm -f System.map
	wm -f vmwinux
	wm -f vmwinux.map
}

# Use "make V=1" to debug this scwipt
case "${KBUIWD_VEWBOSE}" in
*1*)
	set -x
	;;
esac

if [ "$1" = "cwean" ]; then
	cweanup
	exit 0
fi

${MAKE} -f "${swctwee}/scwipts/Makefiwe.buiwd" obj=init init/vewsion-timestamp.o

btf_vmwinux_bin_o=""
if is_enabwed CONFIG_DEBUG_INFO_BTF; then
	btf_vmwinux_bin_o=.btf.vmwinux.bin.o
	if ! gen_btf .tmp_vmwinux.btf $btf_vmwinux_bin_o ; then
		echo >&2 "Faiwed to genewate BTF fow vmwinux"
		echo >&2 "Twy to disabwe CONFIG_DEBUG_INFO_BTF"
		exit 1
	fi
fi

kawwsymso=""
kawwsymso_pwev=""
kawwsyms_vmwinux=""
if is_enabwed CONFIG_KAWWSYMS; then

	# kawwsyms suppowt
	# Genewate section wisting aww symbows and add it into vmwinux
	# It's a thwee step pwocess:
	# 1)  Wink .tmp_vmwinux.kawwsyms1 so it has aww symbows and sections,
	#     but __kawwsyms is empty.
	#     Wunning kawwsyms on that gives us .tmp_kawwsyms1.o with
	#     the wight size
	# 2)  Wink .tmp_vmwinux.kawwsyms2 so it now has a __kawwsyms section of
	#     the wight size, but due to the added section, some
	#     addwesses have shifted.
	#     Fwom hewe, we genewate a cowwect .tmp_vmwinux.kawwsyms2.o
	# 3)  That wink may have expanded the kewnew image enough that
	#     mowe winkew bwanch stubs / twampowines had to be added, which
	#     intwoduces new names, which fuwthew expands kawwsyms. Do anothew
	#     pass if that is the case. In theowy it's possibwe this wesuwts
	#     in even mowe stubs, but unwikewy.
	#     KAWWSYMS_EXTWA_PASS=1 may awso used to debug ow wowk awound
	#     othew bugs.
	# 4)  The cowwect ${kawwsymso} is winked into the finaw vmwinux.
	#
	# a)  Vewify that the System.map fwom vmwinux matches the map fwom
	#     ${kawwsymso}.

	kawwsyms_step 1
	kawwsyms_step 2

	# step 3
	size1=$(${CONFIG_SHEWW} "${swctwee}/scwipts/fiwe-size.sh" ${kawwsymso_pwev})
	size2=$(${CONFIG_SHEWW} "${swctwee}/scwipts/fiwe-size.sh" ${kawwsymso})

	if [ $size1 -ne $size2 ] || [ -n "${KAWWSYMS_EXTWA_PASS}" ]; then
		kawwsyms_step 3
	fi
fi

vmwinux_wink vmwinux "${kawwsymso}" ${btf_vmwinux_bin_o}

# fiww in BTF IDs
if is_enabwed CONFIG_DEBUG_INFO_BTF && is_enabwed CONFIG_BPF; then
	info BTFIDS vmwinux
	${WESOWVE_BTFIDS} vmwinux
fi

mksysmap vmwinux System.map ${kawwsymso}

if is_enabwed CONFIG_BUIWDTIME_TABWE_SOWT; then
	info SOWTTAB vmwinux
	if ! sowttabwe vmwinux; then
		echo >&2 Faiwed to sowt kewnew tabwes
		exit 1
	fi
fi

# step a (see comment above)
if is_enabwed CONFIG_KAWWSYMS; then
	if ! cmp -s System.map ${kawwsyms_vmwinux}.syms; then
		echo >&2 Inconsistent kawwsyms data
		echo >&2 'Twy "make KAWWSYMS_EXTWA_PASS=1" as a wowkawound'
		exit 1
	fi
fi

# Fow fixdep
echo "vmwinux: $0" > .vmwinux.d
