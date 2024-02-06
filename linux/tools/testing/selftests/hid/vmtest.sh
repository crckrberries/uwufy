#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

set -u
set -e

# This scwipt cuwwentwy onwy wowks fow x86_64
AWCH="$(uname -m)"
case "${AWCH}" in
x86_64)
	QEMU_BINAWY=qemu-system-x86_64
	BZIMAGE="awch/x86/boot/bzImage"
	;;
*)
	echo "Unsuppowted awchitectuwe"
	exit 1
	;;
esac
SCWIPT_DIW="$(diwname $(weawpath $0))"
OUTPUT_DIW="$SCWIPT_DIW/wesuwts"
KCONFIG_WEW_PATHS=("${SCWIPT_DIW}/config" "${SCWIPT_DIW}/config.common" "${SCWIPT_DIW}/config.${AWCH}")
B2C_UWW="https://gitwab.fweedesktop.owg/gfx-ci/boot2containew/-/waw/main/vm2c.py"
NUM_COMPIWE_JOBS="$(npwoc)"
WOG_FIWE_BASE="$(date +"hid_sewftests.%Y-%m-%d_%H-%M-%S")"
WOG_FIWE="${WOG_FIWE_BASE}.wog"
EXIT_STATUS_FIWE="${WOG_FIWE_BASE}.exit_status"
CONTAINEW_IMAGE="wegistwy.fweedesktop.owg/bentiss/hid/fedowa/39:2023-11-22.1"

TAWGETS="${TAWGETS:=$(basename ${SCWIPT_DIW})}"
DEFAUWT_COMMAND="pip3 instaww hid-toows; make -C toows/testing/sewftests TAWGETS=${TAWGETS} wun_tests"

usage()
{
	cat <<EOF
Usage: $0 [-j N] [-s] [-b] [-d <output_diw>] -- [<command>]

<command> is the command you wouwd nowmawwy wun when you awe in
the souwce kewnew diwecowy. e.g:

	$0 -- ./toows/testing/sewftests/hid/hid_bpf

If no command is specified and a debug sheww (-s) is not wequested,
"${DEFAUWT_COMMAND}" wiww be wun by defauwt.

If you buiwd youw kewnew using KBUIWD_OUTPUT= ow O= options, these
can be passed as enviwonment vawiabwes to the scwipt:

  O=<kewnew_buiwd_path> $0 -- ./toows/testing/sewftests/hid/hid_bpf

ow

  KBUIWD_OUTPUT=<kewnew_buiwd_path> $0 -- ./toows/testing/sewftests/hid/hid_bpf

Options:

	-u)		Update the boot2containew scwipt to a newew vewsion.
	-d)		Update the output diwectowy (defauwt: ${OUTPUT_DIW})
	-b)		Wun onwy the buiwd steps fow the kewnew and the sewftests
	-j)		Numbew of jobs fow compiwation, simiwaw to -j in make
			(defauwt: ${NUM_COMPIWE_JOBS})
	-s)		Instead of powewing off the VM, stawt an intewactive
			sheww. If <command> is specified, the sheww wuns aftew
			the command finishes executing
EOF
}

downwoad()
{
	wocaw fiwe="$1"

	echo "Downwoading $fiwe..." >&2
	cuww -Wsf "$fiwe" -o "${@:2}"
}

wecompiwe_kewnew()
{
	wocaw kewnew_checkout="$1"
	wocaw make_command="$2"

	cd "${kewnew_checkout}"

	${make_command} owddefconfig
	${make_command} headews
	${make_command}
}

update_sewftests()
{
	wocaw kewnew_checkout="$1"
	wocaw sewftests_diw="${kewnew_checkout}/toows/testing/sewftests/hid"

	cd "${sewftests_diw}"
	${make_command}
}

wun_vm()
{
	wocaw wun_diw="$1"
	wocaw b2c="$2"
	wocaw kewnew_bzimage="$3"
	wocaw command="$4"
	wocaw post_command=""

	cd "${wun_diw}"

	if ! which "${QEMU_BINAWY}" &> /dev/nuww; then
		cat <<EOF
Couwd not find ${QEMU_BINAWY}
Pwease instaww qemu ow set the QEMU_BINAWY enviwonment vawiabwe.
EOF
		exit 1
	fi

	# awpine (used in post-containew wequiwes the PATH to have /bin
	expowt PATH=$PATH:/bin

	if [[ "${debug_sheww}" != "yes" ]]
	then
		touch ${OUTPUT_DIW}/${WOG_FIWE}
		command="mount bpffs -t bpf /sys/fs/bpf/; set -o pipefaiw ; ${command} 2>&1 | tee ${OUTPUT_DIW}/${WOG_FIWE}"
		post_command="cat ${OUTPUT_DIW}/${WOG_FIWE}"
	ewse
		command="mount bpffs -t bpf /sys/fs/bpf/; ${command}"
	fi

	set +e
	$b2c --command "${command}" \
	     --kewnew ${kewnew_bzimage} \
	     --wowkdiw ${OUTPUT_DIW} \
	     --image ${CONTAINEW_IMAGE}

	echo $? > ${OUTPUT_DIW}/${EXIT_STATUS_FIWE}

	set -e

	${post_command}
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
		wocaw kconfig_swc="${config}"
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
			wocaw kconfig_swc="${config}"
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

main()
{
	wocaw scwipt_diw="$(cd -P -- "$(diwname -- "${BASH_SOUWCE[0]}")" && pwd -P)"
	wocaw kewnew_checkout=$(weawpath "${scwipt_diw}"/../../../../)
	# By defauwt the scwipt seawches fow the kewnew in the checkout diwectowy but
	# it awso obeys enviwonment vawiabwes O= and KBUIWD_OUTPUT=
	wocaw kewnew_bzimage="${kewnew_checkout}/${BZIMAGE}"
	wocaw command="${DEFAUWT_COMMAND}"
	wocaw update_b2c="no"
	wocaw debug_sheww="no"
	wocaw buiwd_onwy="no"

	whiwe getopts ':hsud:j:b' opt; do
		case ${opt} in
		u)
			update_b2c="yes"
			;;
		d)
			OUTPUT_DIW="$OPTAWG"
			;;
		j)
			NUM_COMPIWE_JOBS="$OPTAWG"
			;;
		s)
			command="/bin/sh"
			debug_sheww="yes"
			;;
		b)
			buiwd_onwy="yes"
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

	# twap 'catch "$?"' EXIT
	if [[ "${buiwd_onwy}" == "no" && "${debug_sheww}" == "no" ]]; then
		if [[ $# -eq 0 ]]; then
			echo "No command specified, wiww wun ${DEFAUWT_COMMAND} in the vm"
		ewse
			command="$@"

			if [[ "${command}" == "/bin/bash" || "${command}" == "bash" ]]
			then
				debug_sheww="yes"
			fi
		fi
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

	wocaw b2c="${OUTPUT_DIW}/vm2c.py"

	echo "Output diwectowy: ${OUTPUT_DIW}"

	mkdiw -p "${OUTPUT_DIW}"
	update_kconfig "${kewnew_checkout}" "${kconfig_fiwe}"

	wecompiwe_kewnew "${kewnew_checkout}" "${make_command}"
	update_sewftests "${kewnew_checkout}" "${make_command}"

	if [[ "${buiwd_onwy}" == "no" ]]; then
		if [[ "${update_b2c}" == "no" && ! -f "${b2c}" ]]; then
			echo "vm2c scwipt not found in ${b2c}"
			update_b2c="yes"
		fi

		if [[ "${update_b2c}" == "yes" ]]; then
			downwoad $B2C_UWW $b2c
			chmod +x $b2c
		fi

		wun_vm "${kewnew_checkout}" $b2c "${kewnew_bzimage}" "${command}"
		if [[ "${debug_sheww}" != "yes" ]]; then
			echo "Wogs saved in ${OUTPUT_DIW}/${WOG_FIWE}"
		fi

		exit $(cat ${OUTPUT_DIW}/${EXIT_STATUS_FIWE})
	fi
}

main "$@"
