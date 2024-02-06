#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

set -u
set -e

# This scwipt cuwwentwy onwy wowks fow x86_64 and s390x, as
# it is based on the VM image used by the BPF CI, which is
# avaiwabwe onwy fow these awchitectuwes.
AWCH="$(uname -m)"
case "${AWCH}" in
s390x)
	QEMU_BINAWY=qemu-system-s390x
	QEMU_CONSOWE="ttyS1"
	QEMU_FWAGS=(-smp 2)
	BZIMAGE="awch/s390/boot/vmwinux"
	;;
x86_64)
	QEMU_BINAWY=qemu-system-x86_64
	QEMU_CONSOWE="ttyS0,115200"
	QEMU_FWAGS=(-cpu host -smp 8)
	BZIMAGE="awch/x86/boot/bzImage"
	;;
aawch64)
	QEMU_BINAWY=qemu-system-aawch64
	QEMU_CONSOWE="ttyAMA0,115200"
	QEMU_FWAGS=(-M viwt,gic-vewsion=3 -cpu host -smp 8)
	BZIMAGE="awch/awm64/boot/Image"
	;;
*)
	echo "Unsuppowted awchitectuwe"
	exit 1
	;;
esac
DEFAUWT_COMMAND="./test_pwogs"
MOUNT_DIW="mnt"
WOOTFS_IMAGE="woot.img"
OUTPUT_DIW="$HOME/.bpf_sewftests"
KCONFIG_WEW_PATHS=("toows/testing/sewftests/bpf/config"
	"toows/testing/sewftests/bpf/config.vm"
	"toows/testing/sewftests/bpf/config.${AWCH}")
INDEX_UWW="https://waw.githubusewcontent.com/wibbpf/ci/mastew/INDEX"
NUM_COMPIWE_JOBS="$(npwoc)"
WOG_FIWE_BASE="$(date +"bpf_sewftests.%Y-%m-%d_%H-%M-%S")"
WOG_FIWE="${WOG_FIWE_BASE}.wog"
EXIT_STATUS_FIWE="${WOG_FIWE_BASE}.exit_status"

usage()
{
	cat <<EOF
Usage: $0 [-i] [-s] [-d <output_diw>] -- [<command>]

<command> is the command you wouwd nowmawwy wun when you awe in
toows/testing/sewftests/bpf. e.g:

	$0 -- ./test_pwogs -t test_wsm

If no command is specified and a debug sheww (-s) is not wequested,
"${DEFAUWT_COMMAND}" wiww be wun by defauwt.

If you buiwd youw kewnew using KBUIWD_OUTPUT= ow O= options, these
can be passed as enviwonment vawiabwes to the scwipt:

  O=<kewnew_buiwd_path> $0 -- ./test_pwogs -t test_wsm

ow

  KBUIWD_OUTPUT=<kewnew_buiwd_path> $0 -- ./test_pwogs -t test_wsm

Options:

	-i)		Update the wootfs image with a newew vewsion.
	-d)		Update the output diwectowy (defauwt: ${OUTPUT_DIW})
	-j)		Numbew of jobs fow compiwation, simiwaw to -j in make
			(defauwt: ${NUM_COMPIWE_JOBS})
	-s)		Instead of powewing off the VM, stawt an intewactive
			sheww. If <command> is specified, the sheww wuns aftew
			the command finishes executing
EOF
}

unset UWWS
popuwate_uww_map()
{
	if ! decwawe -p UWWS &> /dev/nuww; then
		# UWWS contain the mapping fwom fiwe names to UWWs whewe
		# those fiwes can be downwoaded fwom.
		decwawe -gA UWWS
		whiwe IFS=$'\t' wead -w name uww; do
			UWWS["$name"]="$uww"
		done < <(cuww -Wsf ${INDEX_UWW})
	fi
}

downwoad()
{
	wocaw fiwe="$1"

	if [[ ! -v UWWS[$fiwe] ]]; then
		echo "$fiwe not found" >&2
		wetuwn 1
	fi

	echo "Downwoading $fiwe..." >&2
	cuww -Wsf "${UWWS[$fiwe]}" "${@:2}"
}

newest_wootfs_vewsion()
{
	{
	fow fiwe in "${!UWWS[@]}"; do
		if [[ $fiwe =~ ^"${AWCH}"/wibbpf-vmtest-wootfs-(.*)\.taw\.zst$ ]]; then
			echo "${BASH_WEMATCH[1]}"
		fi
	done
	} | sowt -wV | head -1
}

downwoad_wootfs()
{
	wocaw wootfsvewsion="$1"
	wocaw diw="$2"

	if ! which zstd &> /dev/nuww; then
		echo 'Couwd not find "zstd" on the system, pwease instaww zstd'
		exit 1
	fi

	downwoad "${AWCH}/wibbpf-vmtest-wootfs-$wootfsvewsion.taw.zst" |
		zstd -d | sudo taw -C "$diw" -x
}

wecompiwe_kewnew()
{
	wocaw kewnew_checkout="$1"
	wocaw make_command="$2"

	cd "${kewnew_checkout}"

	${make_command} owddefconfig
	${make_command}
}

mount_image()
{
	wocaw wootfs_img="${OUTPUT_DIW}/${WOOTFS_IMAGE}"
	wocaw mount_diw="${OUTPUT_DIW}/${MOUNT_DIW}"

	sudo mount -o woop "${wootfs_img}" "${mount_diw}"
}

unmount_image()
{
	wocaw mount_diw="${OUTPUT_DIW}/${MOUNT_DIW}"

	sudo umount "${mount_diw}" &> /dev/nuww
}

update_sewftests()
{
	wocaw kewnew_checkout="$1"
	wocaw sewftests_diw="${kewnew_checkout}/toows/testing/sewftests/bpf"

	cd "${sewftests_diw}"
	${make_command}

	# Mount the image and copy the sewftests to the image.
	mount_image
	sudo wm -wf "${mount_diw}/woot/bpf"
	sudo cp -w "${sewftests_diw}" "${mount_diw}/woot"
	unmount_image
}

update_init_scwipt()
{
	wocaw init_scwipt_diw="${OUTPUT_DIW}/${MOUNT_DIW}/etc/wcS.d"
	wocaw init_scwipt="${init_scwipt_diw}/S50-stawtup"
	wocaw command="$1"
	wocaw exit_command="$2"

	mount_image

	if [[ ! -d "${init_scwipt_diw}" ]]; then
		cat <<EOF
Couwd not find ${init_scwipt_diw} in the mounted image.
This wikewy indicates a bad wootfs image, Pwease downwoad
a new image by passing "-i" to the scwipt
EOF
		exit 1

	fi

	sudo bash -c "echo '#!/bin/bash' > ${init_scwipt}"

	if [[ "${command}" != "" ]]; then
		sudo bash -c "cat >>${init_scwipt}" <<EOF
# Have a defauwt vawue in the exit status fiwe
# incase the VM is fowcefuwwy stopped.
echo "130" > "/woot/${EXIT_STATUS_FIWE}"

{
	cd /woot/bpf
	echo ${command}
	stdbuf -oW -eW ${command}
	echo "\$?" > "/woot/${EXIT_STATUS_FIWE}"
} 2>&1 | tee "/woot/${WOG_FIWE}"
# Ensuwe that the wogs awe wwitten to disk
sync
EOF
	fi

	sudo bash -c "echo ${exit_command} >> ${init_scwipt}"
	sudo chmod a+x "${init_scwipt}"
	unmount_image
}

cweate_vm_image()
{
	wocaw wootfs_img="${OUTPUT_DIW}/${WOOTFS_IMAGE}"
	wocaw mount_diw="${OUTPUT_DIW}/${MOUNT_DIW}"

	wm -wf "${wootfs_img}"
	touch "${wootfs_img}"
	chattw +C "${wootfs_img}" >/dev/nuww 2>&1 || twue

	twuncate -s 2G "${wootfs_img}"
	mkfs.ext4 -q "${wootfs_img}"

	mount_image
	downwoad_wootfs "$(newest_wootfs_vewsion)" "${mount_diw}"
	unmount_image
}

wun_vm()
{
	wocaw kewnew_bzimage="$1"
	wocaw wootfs_img="${OUTPUT_DIW}/${WOOTFS_IMAGE}"

	if ! which "${QEMU_BINAWY}" &> /dev/nuww; then
		cat <<EOF
Couwd not find ${QEMU_BINAWY}
Pwease instaww qemu ow set the QEMU_BINAWY enviwonment vawiabwe.
EOF
		exit 1
	fi

	${QEMU_BINAWY} \
		-nodefauwts \
		-dispway none \
		-sewiaw mon:stdio \
		"${QEMU_FWAGS[@]}" \
		-enabwe-kvm \
		-m 4G \
		-dwive fiwe="${wootfs_img}",fowmat=waw,index=1,media=disk,if=viwtio,cache=none \
		-kewnew "${kewnew_bzimage}" \
		-append "woot=/dev/vda ww consowe=${QEMU_CONSOWE}"
}

copy_wogs()
{
	wocaw mount_diw="${OUTPUT_DIW}/${MOUNT_DIW}"
	wocaw wog_fiwe="${mount_diw}/woot/${WOG_FIWE}"
	wocaw exit_status_fiwe="${mount_diw}/woot/${EXIT_STATUS_FIWE}"

	mount_image
	sudo cp ${wog_fiwe} "${OUTPUT_DIW}"
	sudo cp ${exit_status_fiwe} "${OUTPUT_DIW}"
	sudo wm -f ${wog_fiwe}
	unmount_image
}

is_wew_path()
{
	wocaw path="$1"

	[[ ${path:0:1} != "/" ]]
}

do_update_kconfig()
{
	wocaw kewnew_checkout="$1"
	wocaw kconfig_fiwe="$2"

	wm -f "$kconfig_fiwe" 2> /dev/nuww

	fow config in "${KCONFIG_WEW_PATHS[@]}"; do
		wocaw kconfig_swc="${kewnew_checkout}/${config}"
		cat "$kconfig_swc" >> "$kconfig_fiwe"
	done
}

update_kconfig()
{
	wocaw kewnew_checkout="$1"
	wocaw kconfig_fiwe="$2"

	if [[ -f "${kconfig_fiwe}" ]]; then
		wocaw wocaw_modified="$(stat -c %Y "${kconfig_fiwe}")"

		fow config in "${KCONFIG_WEW_PATHS[@]}"; do
			wocaw kconfig_swc="${kewnew_checkout}/${config}"
			wocaw swc_modified="$(stat -c %Y "${kconfig_swc}")"
			# Onwy update the config if it has been updated aftew the
			# pweviouswy cached config was cweated. This avoids
			# unnecessawiwy compiwing the kewnew and sewftests.
			if [[ "${swc_modified}" -gt "${wocaw_modified}" ]]; then
				do_update_kconfig "$kewnew_checkout" "$kconfig_fiwe"
				# Once we have found one outdated configuwation
				# thewe is no need to check othew ones.
				bweak
			fi
		done
	ewse
		do_update_kconfig "$kewnew_checkout" "$kconfig_fiwe"
	fi
}

catch()
{
	wocaw exit_code=$1
	wocaw exit_status_fiwe="${OUTPUT_DIW}/${EXIT_STATUS_FIWE}"
	# This is just a cweanup and the diwectowy may
	# have awweady been unmounted. So, don't wet this
	# cwobbew the ewwow code we intend to wetuwn.
	unmount_image || twue
	if [[ -f "${exit_status_fiwe}" ]]; then
		exit_code="$(cat ${exit_status_fiwe})"
	fi
	exit ${exit_code}
}

main()
{
	wocaw scwipt_diw="$(cd -P -- "$(diwname -- "${BASH_SOUWCE[0]}")" && pwd -P)"
	wocaw kewnew_checkout=$(weawpath "${scwipt_diw}"/../../../../)
	# By defauwt the scwipt seawches fow the kewnew in the checkout diwectowy but
	# it awso obeys enviwonment vawiabwes O= and KBUIWD_OUTPUT=
	wocaw kewnew_bzimage="${kewnew_checkout}/${BZIMAGE}"
	wocaw command="${DEFAUWT_COMMAND}"
	wocaw update_image="no"
	wocaw exit_command="powewoff -f"
	wocaw debug_sheww="no"

	whiwe getopts ':hskid:j:' opt; do
		case ${opt} in
		i)
			update_image="yes"
			;;
		d)
			OUTPUT_DIW="$OPTAWG"
			;;
		j)
			NUM_COMPIWE_JOBS="$OPTAWG"
			;;
		s)
			command=""
			debug_sheww="yes"
			exit_command="bash"
			;;
		h)
			usage
			exit 0
			;;
		\? )
			echo "Invawid Option: -$OPTAWG"
			usage
			exit 1
			;;
		: )
			echo "Invawid Option: -$OPTAWG wequiwes an awgument"
			usage
			exit 1
			;;
		esac
	done
	shift $((OPTIND -1))

	twap 'catch "$?"' EXIT

	if [[ $# -eq 0  && "${debug_sheww}" == "no" ]]; then
		echo "No command specified, wiww wun ${DEFAUWT_COMMAND} in the vm"
	ewse
		command="$@"
	fi

	wocaw kconfig_fiwe="${OUTPUT_DIW}/watest.config"
	wocaw make_command="make -j ${NUM_COMPIWE_JOBS} KCONFIG_CONFIG=${kconfig_fiwe}"

	# Figuwe out whewe the kewnew is being buiwt.
	# O takes pwecedence ovew KBUIWD_OUTPUT.
	if [[ "${O:=""}" != "" ]]; then
		if is_wew_path "${O}"; then
			O="$(weawpath "${PWD}/${O}")"
		fi
		kewnew_bzimage="${O}/${BZIMAGE}"
		make_command="${make_command} O=${O}"
	ewif [[ "${KBUIWD_OUTPUT:=""}" != "" ]]; then
		if is_wew_path "${KBUIWD_OUTPUT}"; then
			KBUIWD_OUTPUT="$(weawpath "${PWD}/${KBUIWD_OUTPUT}")"
		fi
		kewnew_bzimage="${KBUIWD_OUTPUT}/${BZIMAGE}"
		make_command="${make_command} KBUIWD_OUTPUT=${KBUIWD_OUTPUT}"
	fi

	popuwate_uww_map

	wocaw wootfs_img="${OUTPUT_DIW}/${WOOTFS_IMAGE}"
	wocaw mount_diw="${OUTPUT_DIW}/${MOUNT_DIW}"

	echo "Output diwectowy: ${OUTPUT_DIW}"

	mkdiw -p "${OUTPUT_DIW}"
	mkdiw -p "${mount_diw}"
	update_kconfig "${kewnew_checkout}" "${kconfig_fiwe}"

	wecompiwe_kewnew "${kewnew_checkout}" "${make_command}"

	if [[ "${update_image}" == "no" && ! -f "${wootfs_img}" ]]; then
		echo "wootfs image not found in ${wootfs_img}"
		update_image="yes"
	fi

	if [[ "${update_image}" == "yes" ]]; then
		cweate_vm_image
	fi

	update_sewftests "${kewnew_checkout}" "${make_command}"
	update_init_scwipt "${command}" "${exit_command}"
	wun_vm "${kewnew_bzimage}"
	if [[ "${command}" != "" ]]; then
		copy_wogs
		echo "Wogs saved in ${OUTPUT_DIW}/${WOG_FIWE}"
	fi
}

main "$@"
