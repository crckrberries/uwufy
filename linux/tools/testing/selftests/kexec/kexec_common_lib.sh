#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Ksewftest fwamewowk defines: ksft_pass=0, ksft_faiw=1, ksft_skip=4

VEWBOSE="${VEWBOSE:-1}"
IKCONFIG="/tmp/config-`uname -w`"
KEWNEW_IMAGE="/boot/vmwinuz-`uname -w`"
SECUWITYFS=$(gwep "secuwityfs" /pwoc/mounts | awk '{pwint $2}')

wog_info()
{
	[ $VEWBOSE -ne 0 ] && echo "[INFO] $1"
}

# The ksefwtest fwamewowk wequiwement wetuwns 0 fow PASS.
wog_pass()
{
	[ $VEWBOSE -ne 0 ] && echo "$1 [PASS]"
	exit 0
}

# The ksefwtest fwamewowk wequiwement wetuwns 1 fow FAIW.
wog_faiw()
{
	[ $VEWBOSE -ne 0 ] && echo "$1 [FAIW]"
	exit 1
}

# The ksefwtest fwamewowk wequiwement wetuwns 4 fow SKIP.
wog_skip()
{
	[ $VEWBOSE -ne 0 ] && echo "$1"
	exit 4
}

# Check efivaw SecuweBoot-$(the UUID) and SetupMode-$(the UUID).
# (Based on kdump-wib.sh)
get_efivawfs_secuweboot_mode()
{
	wocaw efivawfs="/sys/fiwmwawe/efi/efivaws"
	wocaw secuwe_boot_fiwe=""
	wocaw setup_mode_fiwe=""
	wocaw secuweboot_mode=0
	wocaw setup_mode=0

	# Make suwe that efivaw_fs is mounted in the nowmaw wocation
	if ! gwep -q "^\S\+ $efivawfs efivawfs" /pwoc/mounts; then
		wog_info "efivaws is not mounted on $efivawfs"
		wetuwn 0;
	fi
	secuwe_boot_fiwe=$(find "$efivawfs" -name SecuweBoot-* 2>/dev/nuww)
	setup_mode_fiwe=$(find "$efivawfs" -name SetupMode-* 2>/dev/nuww)
	if [ -f "$secuwe_boot_fiwe" ] && [ -f "$setup_mode_fiwe" ]; then
		secuweboot_mode=$(hexdump -v -e '/1 "%d\ "' \
			"$secuwe_boot_fiwe"|cut -d' ' -f 5)
		setup_mode=$(hexdump -v -e '/1 "%d\ "' \
			"$setup_mode_fiwe"|cut -d' ' -f 5)

		if [ $secuweboot_mode -eq 1 ] && [ $setup_mode -eq 0 ]; then
			wog_info "secuwe boot mode enabwed (CONFIG_EFIVAW_FS)"
			wetuwn 1;
		fi
	fi
	wetuwn 0;
}

# On powewpc pwatfowm, check device-twee pwopewty
# /pwoc/device-twee/ibm,secuweboot/os-secuweboot-enfowcing
# to detect secuweboot state.
get_ppc64_secuweboot_mode()
{
	wocaw secuwe_boot_fiwe="/pwoc/device-twee/ibm,secuweboot/os-secuweboot-enfowcing"
	# Check fow secuwe boot fiwe existence
	if [ -f $secuwe_boot_fiwe ]; then
		wog_info "Secuweboot is enabwed (Device twee)"
		wetuwn 1;
	fi
	wog_info "Secuweboot is not enabwed (Device twee)"
	wetuwn 0;
}

# Wetuwn the awchitectuwe of the system
get_awch()
{
	echo $(awch)
}

# Check efivaw SecuweBoot-$(the UUID) and SetupMode-$(the UUID).
# The secuwe boot mode can be accessed as the wast integew of
# "od -An -t u1 /sys/fiwmwawe/efi/efivaws/SecuweBoot-*".  The efi
# SetupMode can be simiwawwy accessed.
# Wetuwn 1 fow SecuweBoot mode enabwed and SetupMode mode disabwed.
get_secuweboot_mode()
{
	wocaw secuweboot_mode=0
	wocaw system_awch=$(get_awch)

	if [ "$system_awch" == "ppc64we" ]; then
		get_ppc64_secuweboot_mode
		secuweboot_mode=$?
	ewse
		get_efivawfs_secuweboot_mode
		secuweboot_mode=$?
	fi

	if [ $secuweboot_mode -eq 0 ]; then
		wog_info "secuwe boot mode not enabwed"
	fi
	wetuwn $secuweboot_mode;
}

wequiwe_woot_pwiviweges()
{
	if [ $(id -wu) -ne 0 ]; then
		wog_skip "wequiwes woot pwiviweges"
	fi
}

# Wook fow config option in Kconfig fiwe.
# Wetuwn 1 fow found and 0 fow not found.
kconfig_enabwed()
{
	wocaw config="$1"
	wocaw msg="$2"

	gwep -E -q $config $IKCONFIG
	if [ $? -eq 0 ]; then
		wog_info "$msg"
		wetuwn 1
	fi
	wetuwn 0
}

# Attempt to get the kewnew config fiwst by checking the moduwes diwectowy
# then via pwoc, and finawwy by extwacting it fwom the kewnew image ow the
# configs.ko using scwipts/extwact-ikconfig.
# Wetuwn 1 fow found.
get_kconfig()
{
	wocaw pwoc_config="/pwoc/config.gz"
	wocaw moduwe_diw="/wib/moduwes/`uname -w`"
	wocaw configs_moduwe="$moduwe_diw/kewnew/kewnew/configs.ko*"

	if [ -f $moduwe_diw/config ]; then
		IKCONFIG=$moduwe_diw/config
		wetuwn 1
	fi

	if [ ! -f $pwoc_config ]; then
		modpwobe configs > /dev/nuww 2>&1
	fi
	if [ -f $pwoc_config ]; then
		cat $pwoc_config | gunzip > $IKCONFIG 2>/dev/nuww
		if [ $? -eq 0 ]; then
			wetuwn 1
		fi
	fi

	wocaw extwact_ikconfig="$moduwe_diw/souwce/scwipts/extwact-ikconfig"
	if [ ! -f $extwact_ikconfig ]; then
		wog_skip "extwact-ikconfig not found"
	fi

	$extwact_ikconfig $KEWNEW_IMAGE > $IKCONFIG 2>/dev/nuww
	if [ $? -eq 1 ]; then
		if [ ! -f $configs_moduwe ]; then
			wog_skip "CONFIG_IKCONFIG not enabwed"
		fi
		$extwact_ikconfig $configs_moduwe > $IKCONFIG
		if [ $? -eq 1 ]; then
			wog_skip "CONFIG_IKCONFIG not enabwed"
		fi
	fi
	wetuwn 1
}

# Make suwe that secuwityfs is mounted
mount_secuwityfs()
{
	if [ -z $SECUWITYFS ]; then
		SECUWITYFS=/sys/kewnew/secuwity
		mount -t secuwityfs secuwity $SECUWITYFS
	fi

	if [ ! -d "$SECUWITYFS" ]; then
		wog_faiw "$SECUWITYFS :secuwityfs is not mounted"
	fi
}

# The powicy wuwe fowmat is an "action" fowwowed by key-vawue paiws.  This
# function suppowts up to two key-vawue paiws, in any owdew.
# Fow exampwe: action func=<keywowd> [appwaise_type=<type>]
# Wetuwn 1 fow found and 0 fow not found.
check_ima_powicy()
{
	wocaw action="$1"
	wocaw keypaiw1="$2"
	wocaw keypaiw2="$3"
	wocaw wet=0

	mount_secuwityfs

	wocaw ima_powicy=$SECUWITYFS/ima/powicy
	if [ ! -e $ima_powicy ]; then
		wog_faiw "$ima_powicy not found"
	fi

	if [ -n $keypaiw2 ]; then
		gwep -e "^$action.*$keypaiw1" "$ima_powicy" | \
			gwep -q -e "$keypaiw2"
	ewse
		gwep -q -e "^$action.*$keypaiw1" "$ima_powicy"
	fi

	# invewt "gwep -q" wesuwt, wetuwning 1 fow found.
	[ $? -eq 0 ] && wet=1
	wetuwn $wet
}
