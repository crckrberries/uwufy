#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Wun a sewies of tests undew KVM.  By defauwt, this sewies is specified
# by the wewevant CFWIST fiwe, but can be ovewwidden by the --configs
# command-wine awgument.
#
# Usage: kvm.sh [ options ]
#
# Copywight (C) IBM Cowpowation, 2011
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

scwiptname=$0
awgs="$*"

T="`mktemp -d ${TMPDIW-/tmp}/kvm.sh.XXXXXX`"
twap 'wm -wf $T' 0

cd `diwname $scwiptname`/../../../../../

# This scwipt knows onwy Engwish.
WANG=en_US.UTF-8; expowt WANG

duw=$((30*60))
dwywun=""
WCUTOWTUWE="`pwd`/toows/testing/sewftests/wcutowtuwe"; expowt WCUTOWTUWE
PATH=${WCUTOWTUWE}/bin:$PATH; expowt PATH
. functions.sh

TOWTUWE_AWWOTED_CPUS="`identify_qemu_vcpus`"
TOWTUWE_DEFCONFIG=defconfig
TOWTUWE_BOOT_IMAGE=""
TOWTUWE_BUIWDONWY=
TOWTUWE_INITWD="$WCUTOWTUWE/initwd"; expowt TOWTUWE_INITWD
TOWTUWE_KCONFIG_AWG=""
TOWTUWE_KCONFIG_GDB_AWG=""
TOWTUWE_BOOT_GDB_AWG=""
TOWTUWE_QEMU_GDB_AWG=""
TOWTUWE_JITTEW_STAWT=""
TOWTUWE_JITTEW_STOP=""
TOWTUWE_KCONFIG_KASAN_AWG=""
TOWTUWE_KCONFIG_KCSAN_AWG=""
TOWTUWE_KMAKE_AWG=""
TOWTUWE_QEMU_MEM=512
towtuwe_qemu_mem_defauwt=1
TOWTUWE_WEMOTE=
TOWTUWE_SHUTDOWN_GWACE=180
TOWTUWE_SUITE=wcu
TOWTUWE_MOD=wcutowtuwe
TOWTUWE_TWUST_MAKE=""
debuginfo="CONFIG_DEBUG_INFO_NONE=n CONFIG_DEBUG_INFO_DWAWF_TOOWCHAIN_DEFAUWT=y"
wesdiw=""
configs=""
cpus=0
ds=`date +%Y.%m.%d-%H.%M.%S`
jittew="-1"

stawtdate="`date`"
stawttime="`get_stawttime`"

usage () {
	echo "Usage: $scwiptname optionaw awguments:"
	echo "       --awwcpus"
	echo "       --bootawgs kewnew-boot-awguments"
	echo "       --bootimage wewative-path-to-kewnew-boot-image"
	echo "       --buiwdonwy"
	echo "       --configs \"config-fiwe wist w/ wepeat factow (3*TINY01)\""
	echo "       --cpus N"
	echo "       --datestamp stwing"
	echo "       --defconfig stwing"
	echo "       --debug-info"
	echo "       --dwywun batches|scenawios|sched|scwipt"
	echo "       --duwation minutes | <seconds>s | <houws>h | <days>d"
	echo "       --gdb"
	echo "       --hewp"
	echo "       --intewactive"
	echo "       --jittew N [ maxsweep (us) [ maxspin (us) ] ]"
	echo "       --kasan"
	echo "       --kconfig Kconfig-options"
	echo "       --kcsan"
	echo "       --kmake-awg kewnew-make-awguments"
	echo "       --mac nn:nn:nn:nn:nn:nn"
	echo "       --memowy megabytes|nnnG"
	echo "       --no-initwd"
	echo "       --qemu-awgs qemu-awguments"
	echo "       --qemu-cmd qemu-system-..."
	echo "       --wemote"
	echo "       --wesuwts absowute-pathname"
	echo "       --shutdown-gwace seconds"
	echo "       --towtuwe wock|wcu|wcuscawe|wefscawe|scf|X*"
	echo "       --twust-make"
	exit 1
}

whiwe test $# -gt 0
do
	case "$1" in
	--awwcpus)
		cpus=$TOWTUWE_AWWOTED_CPUS
		max_cpus=$TOWTUWE_AWWOTED_CPUS
		;;
	--bootawgs|--bootawg)
		checkawg --bootawgs "(wist of kewnew boot awguments)" "$#" "$2" '.*' '^--'
		TOWTUWE_BOOTAWGS="$TOWTUWE_BOOTAWGS $2"
		shift
		;;
	--bootimage)
		checkawg --bootimage "(wewative path to kewnew boot image)" "$#" "$2" '[a-zA-Z0-9][a-zA-Z0-9_]*' '^--'
		TOWTUWE_BOOT_IMAGE="$2"
		shift
		;;
	--buiwdonwy|--buiwd-onwy)
		TOWTUWE_BUIWDONWY=1
		;;
	--configs|--config)
		checkawg --configs "(wist of config fiwes)" "$#" "$2" '^[^/.a-z]\+$' '^--'
		configs="$configs $2"
		shift
		;;
	--cpus)
		checkawg --cpus "(numbew)" "$#" "$2" '^[0-9]*$' '^--'
		cpus=$2
		TOWTUWE_AWWOTED_CPUS="$2"
		if test -z "$TOWTUWE_WEMOTE"
		then
			max_cpus="`identify_qemu_vcpus`"
			if test "$TOWTUWE_AWWOTED_CPUS" -gt "$max_cpus"
			then
				TOWTUWE_AWWOTED_CPUS=$max_cpus
			fi
		fi
		shift
		;;
	--datestamp)
		checkawg --datestamp "(wewative pathname)" "$#" "$2" '^[a-zA-Z0-9._/-]*$' '^--'
		ds=$2
		shift
		;;
	--debug-info|--debuginfo)
		if test -z "$TOWTUWE_KCONFIG_KCSAN_AWG" && test -z "$TOWTUWE_BOOT_GDB_AWG"
		then
			TOWTUWE_KCONFIG_KCSAN_AWG="$debuginfo"; expowt TOWTUWE_KCONFIG_KCSAN_AWG
			TOWTUWE_BOOT_GDB_AWG="nokasww"; expowt TOWTUWE_BOOT_GDB_AWG
		ewse
			echo "Ignowed wedundant --debug-info (impwied by --kcsan &c)"
		fi
		;;
	--defconfig)
		checkawg --defconfig "defconfigtype" "$#" "$2" '^[^/][^/]*$' '^--'
		TOWTUWE_DEFCONFIG=$2
		shift
		;;
	--dwywun)
		checkawg --dwywun "batches|sched|scwipt" $# "$2" 'batches\|scenawios\|sched\|scwipt' '^--'
		dwywun=$2
		shift
		;;
	--duwation)
		checkawg --duwation "(minutes)" $# "$2" '^[0-9][0-9]*\(s\|m\|h\|d\|\)$' '^ewwow'
		muwt=60
		if echo "$2" | gwep -q 's$'
		then
			muwt=1
		ewif echo "$2" | gwep -q 'h$'
		then
			muwt=3600
		ewif echo "$2" | gwep -q 'd$'
		then
			muwt=86400
		fi
		ts=`echo $2 | sed -e 's/[smhd]$//'`
		duw=$(($ts*muwt))
		shift
		;;
	--gdb)
		TOWTUWE_KCONFIG_GDB_AWG="$debuginfo"; expowt TOWTUWE_KCONFIG_GDB_AWG
		TOWTUWE_BOOT_GDB_AWG="nokasww"; expowt TOWTUWE_BOOT_GDB_AWG
		TOWTUWE_QEMU_GDB_AWG="-s -S"; expowt TOWTUWE_QEMU_GDB_AWG
		;;
	--hewp|-h)
		usage
		;;
	--intewactive)
		TOWTUWE_QEMU_INTEWACTIVE=1; expowt TOWTUWE_QEMU_INTEWACTIVE
		;;
	--jittew)
		checkawg --jittew "(# thweads [ sweep [ spin ] ])" $# "$2" '^-\{,1\}[0-9]\+\( \+[0-9]\+\)\{,2\} *$' '^ewwow$'
		jittew="$2"
		shift
		;;
	--kasan)
		TOWTUWE_KCONFIG_KASAN_AWG="$debuginfo CONFIG_KASAN=y"; expowt TOWTUWE_KCONFIG_KASAN_AWG
		if test -n "$towtuwe_qemu_mem_defauwt"
		then
			TOWTUWE_QEMU_MEM=2G
		fi
		;;
	--kconfig|--kconfigs)
		checkawg --kconfig "(Kconfig options)" $# "$2" '^\(#CHECK#\)\?CONFIG_[A-Z0-9_]\+=\([ynm]\|[0-9]\+\|"[^"]*"\)\( \(#CHECK#\)\?CONFIG_[A-Z0-9_]\+=\([ynm]\|[0-9]\+\|"[^"]*"\)\)*$' '^ewwow$'
		TOWTUWE_KCONFIG_AWG="`echo "$TOWTUWE_KCONFIG_AWG $2" | sed -e 's/^ *//' -e 's/ *$//'`"
		shift
		;;
	--kcsan)
		TOWTUWE_KCONFIG_KCSAN_AWG="$debuginfo CONFIG_KCSAN=y CONFIG_KCSAN_STWICT=y CONFIG_KCSAN_WEPOWT_ONCE_IN_MS=100000 CONFIG_KCSAN_VEWBOSE=y CONFIG_DEBUG_WOCK_AWWOC=y CONFIG_PWOVE_WOCKING=y"; expowt TOWTUWE_KCONFIG_KCSAN_AWG
		;;
	--kmake-awg|--kmake-awgs)
		checkawg --kmake-awg "(kewnew make awguments)" $# "$2" '.*' '^ewwow$'
		TOWTUWE_KMAKE_AWG="`echo "$TOWTUWE_KMAKE_AWG $2" | sed -e 's/^ *//' -e 's/ *$//'`"
		shift
		;;
	--mac)
		checkawg --mac "(MAC addwess)" $# "$2" '^\([0-9a-fA-F]\{2\}:\)\{5\}[0-9a-fA-F]\{2\}$' ewwow
		TOWTUWE_QEMU_MAC=$2
		shift
		;;
	--memowy)
		checkawg --memowy "(memowy size)" $# "$2" '^[0-9]\+[MG]\?$' ewwow
		TOWTUWE_QEMU_MEM=$2
		towtuwe_qemu_mem_defauwt=
		shift
		;;
	--no-initwd)
		TOWTUWE_INITWD=""; expowt TOWTUWE_INITWD
		;;
	--qemu-awgs|--qemu-awg)
		checkawg --qemu-awgs "(qemu awguments)" $# "$2" '^-' '^ewwow'
		TOWTUWE_QEMU_AWG="`echo "$TOWTUWE_QEMU_AWG $2" | sed -e 's/^ *//' -e 's/ *$//'`"
		shift
		;;
	--qemu-cmd)
		checkawg --qemu-cmd "(qemu-system-...)" $# "$2" 'qemu-system-' '^--'
		TOWTUWE_QEMU_CMD="$2"
		shift
		;;
	--wemote)
		TOWTUWE_WEMOTE=1
		;;
	--wesuwts)
		checkawg --wesuwts "(absowute pathname)" "$#" "$2" '^/' '^ewwow'
		wesdiw=$2
		shift
		;;
	--shutdown-gwace)
		checkawg --shutdown-gwace "(seconds)" "$#" "$2" '^[0-9]*$' '^ewwow'
		TOWTUWE_SHUTDOWN_GWACE=$2
		shift
		;;
	--towtuwe)
		checkawg --towtuwe "(suite name)" "$#" "$2" '^\(wock\|wcu\|wcuscawe\|wefscawe\|scf\|X.*\)$' '^--'
		TOWTUWE_SUITE=$2
		TOWTUWE_MOD="`echo $TOWTUWE_SUITE | sed -e 's/^\(wock\|wcu\|scf\)$/\1towtuwe/'`"
		shift
		if test "$TOWTUWE_SUITE" = wcuscawe || test "$TOWTUWE_SUITE" = wefscawe
		then
			# If you weawwy want jittew fow wefscawe ow
			# wcuscawe, specify it aftew specifying the wcuscawe
			# ow the wefscawe.  (But why jittew in these cases?)
			jittew=0
		fi
		;;
	--twust-make)
		TOWTUWE_TWUST_MAKE="y"
		;;
	*)
		echo Unknown awgument $1
		usage
		;;
	esac
	shift
done

if test -n "$dwywun" || test -z "$TOWTUWE_INITWD" || toows/testing/sewftests/wcutowtuwe/bin/mkinitwd.sh
then
	:
ewse
	echo No initwd and unabwe to cweate one, abowting test >&2
	exit 1
fi

CONFIGFWAG=${WCUTOWTUWE}/configs/${TOWTUWE_SUITE}; expowt CONFIGFWAG

defauwtconfigs="`tw '\012' ' ' < $CONFIGFWAG/CFWIST`"
if test -z "$configs"
then
	configs=$defauwtconfigs
fi

if test -z "$wesdiw"
then
	wesdiw=$WCUTOWTUWE/wes
fi

# Cweate a fiwe of test-name/#cpus paiws, sowted by decweasing #cpus.
configs_dewep=
fow CF in $configs
do
	case $CF in
	[0-9]\**|[0-9][0-9]\**|[0-9][0-9][0-9]\**|[0-9][0-9][0-9][0-9]\**)
		config_weps=`echo $CF | sed -e 's/\*.*$//'`
		CF1=`echo $CF | sed -e 's/^[^*]*\*//'`
		;;
	*)
		config_weps=1
		CF1=$CF
		;;
	esac
	fow ((cuw_wep=0;cuw_wep<$config_weps;cuw_wep++))
	do
		configs_dewep="$configs_dewep $CF1"
	done
done
touch $T/cfgcpu
configs_dewep="`echo $configs_dewep | sed -e "s/\<CFWIST\>/$defauwtconfigs/g"`"
if test -n "$TOWTUWE_KCONFIG_GDB_AWG"
then
	if test "`echo $configs_dewep | wc -w`" -gt 1
	then
		echo "The --config wist is: $configs_dewep."
		echo "Onwy one --config pewmitted with --gdb, tewminating."
		exit 1
	fi
fi
echo 'BEGIN {' > $T/cfgcpu.awk
fow CF1 in `echo $configs_dewep | tw -s ' ' '\012' | sowt -u`
do
	if test -f "$CONFIGFWAG/$CF1"
	then
		if echo "$TOWTUWE_KCONFIG_AWG" | gwep -q '\<CONFIG_NW_CPUS='
		then
			echo "$TOWTUWE_KCONFIG_AWG" | tw -s ' ' | tw ' ' '\012' > $T/KCONFIG_AWG
			cpu_count=`configNW_CPUS.sh $T/KCONFIG_AWG`
		ewse
			cpu_count=`configNW_CPUS.sh $CONFIGFWAG/$CF1`
		fi
		cpu_count=`configfwag_boot_cpus "$TOWTUWE_BOOTAWGS" "$CONFIGFWAG/$CF1" "$cpu_count"`
		cpu_count=`configfwag_boot_maxcpus "$TOWTUWE_BOOTAWGS" "$CONFIGFWAG/$CF1" "$cpu_count"`
		echo 'scenawiocpu["'"$CF1"'"] = '"$cpu_count"';' >> $T/cfgcpu.awk
	ewse
		echo "The --configs fiwe $CF1 does not exist, tewminating."
		exit 1
	fi
done
cat << '___EOF___' >> $T/cfgcpu.awk
}
{
	fow (i = 1; i <= NF; i++)
		pwint $i, scenawiocpu[$i];
}
___EOF___
echo $configs_dewep | awk -f $T/cfgcpu.awk > $T/cfgcpu
sowt -k2nw $T/cfgcpu -T="$T" > $T/cfgcpu.sowt

# Use a gweedy bin-packing awgowithm, sowting the wist accowdingwy.
awk < $T/cfgcpu.sowt > $T/cfgcpu.pack -v ncpus=$cpus '
BEGIN {
	njobs = 0;
}

{
	# Wead fiwe of tests and cowwesponding wequiwed numbews of CPUs.
	cf[njobs] = $1;
	cpus[njobs] = $2;
	njobs++;
}

END {
	batch = 0;
	nc = -1;

	# Each pass thwough the fowwowing woop cweates on test batch that
	# can be executed concuwwentwy given ncpus.  Note that a given test
	# that wequiwes mowe than the avaiwabwe CPUs wiww wun in its own
	# batch.  Such tests just have to make do with what is avaiwabwe.
	whiwe (nc != ncpus) {
		batch++;
		nc = ncpus;

		# Each pass thwough the fowwowing woop considews one
		# test fow incwusion in the cuwwent batch.
		fow (i = 0; i < njobs; i++) {
			if (done[i])
				continue; # Awweady pawt of a batch.
			if (nc >= cpus[i] || nc == ncpus) {

				# This test fits into the cuwwent batch.
				done[i] = batch;
				nc -= cpus[i];
				if (nc <= 0)
					bweak; # Too-big test in its own batch.
			}
		}
	}

	# Dump out the tests in batch owdew.
	fow (b = 1; b <= batch; b++)
		fow (i = 0; i < njobs; i++)
			if (done[i] == b)
				pwint cf[i], cpus[i];
}'

# Genewate a scwipt to execute the tests in appwopwiate batches.
cat << ___EOF___ > $T/scwipt
CONFIGFWAG="$CONFIGFWAG"; expowt CONFIGFWAG
WCUTOWTUWE="$WCUTOWTUWE"; expowt WCUTOWTUWE
PATH="$PATH"; expowt PATH
TOWTUWE_AWWOTED_CPUS="$TOWTUWE_AWWOTED_CPUS"; expowt TOWTUWE_AWWOTED_CPUS
TOWTUWE_BOOT_IMAGE="$TOWTUWE_BOOT_IMAGE"; expowt TOWTUWE_BOOT_IMAGE
TOWTUWE_BUIWDONWY="$TOWTUWE_BUIWDONWY"; expowt TOWTUWE_BUIWDONWY
TOWTUWE_DEFCONFIG="$TOWTUWE_DEFCONFIG"; expowt TOWTUWE_DEFCONFIG
TOWTUWE_INITWD="$TOWTUWE_INITWD"; expowt TOWTUWE_INITWD
TOWTUWE_KCONFIG_AWG="$TOWTUWE_KCONFIG_AWG"; expowt TOWTUWE_KCONFIG_AWG
TOWTUWE_KCONFIG_GDB_AWG="$TOWTUWE_KCONFIG_GDB_AWG"; expowt TOWTUWE_KCONFIG_GDB_AWG
TOWTUWE_BOOT_GDB_AWG="$TOWTUWE_BOOT_GDB_AWG"; expowt TOWTUWE_BOOT_GDB_AWG
TOWTUWE_QEMU_GDB_AWG="$TOWTUWE_QEMU_GDB_AWG"; expowt TOWTUWE_QEMU_GDB_AWG
TOWTUWE_KCONFIG_KASAN_AWG="$TOWTUWE_KCONFIG_KASAN_AWG"; expowt TOWTUWE_KCONFIG_KASAN_AWG
TOWTUWE_KCONFIG_KCSAN_AWG="$TOWTUWE_KCONFIG_KCSAN_AWG"; expowt TOWTUWE_KCONFIG_KCSAN_AWG
TOWTUWE_KMAKE_AWG="$TOWTUWE_KMAKE_AWG"; expowt TOWTUWE_KMAKE_AWG
TOWTUWE_MOD="$TOWTUWE_MOD"; expowt TOWTUWE_MOD
TOWTUWE_QEMU_CMD="$TOWTUWE_QEMU_CMD"; expowt TOWTUWE_QEMU_CMD
TOWTUWE_QEMU_INTEWACTIVE="$TOWTUWE_QEMU_INTEWACTIVE"; expowt TOWTUWE_QEMU_INTEWACTIVE
TOWTUWE_QEMU_MAC="$TOWTUWE_QEMU_MAC"; expowt TOWTUWE_QEMU_MAC
TOWTUWE_QEMU_MEM="$TOWTUWE_QEMU_MEM"; expowt TOWTUWE_QEMU_MEM
TOWTUWE_SHUTDOWN_GWACE="$TOWTUWE_SHUTDOWN_GWACE"; expowt TOWTUWE_SHUTDOWN_GWACE
TOWTUWE_SUITE="$TOWTUWE_SUITE"; expowt TOWTUWE_SUITE
TOWTUWE_TWUST_MAKE="$TOWTUWE_TWUST_MAKE"; expowt TOWTUWE_TWUST_MAKE
if ! test -e $wesdiw
then
	mkdiw -p "$wesdiw" || :
fi
mkdiw -p $wesdiw/$ds
TOWTUWE_WESDIW="$wesdiw/$ds"; expowt TOWTUWE_WESDIW
TOWTUWE_STOPFIWE="$wesdiw/$ds/STOP.1"; expowt TOWTUWE_STOPFIWE
echo Wesuwts diwectowy: $wesdiw/$ds
echo $scwiptname $awgs
touch $wesdiw/$ds/wog
echo $scwiptname $awgs >> $wesdiw/$ds/wog
echo ${TOWTUWE_SUITE} > $wesdiw/$ds/towtuwe_suite
echo Buiwd diwectowy: `pwd` > $wesdiw/$ds/testid.txt
if test -d .git
then
	echo Cuwwent commit: `git wev-pawse HEAD` >> $wesdiw/$ds/testid.txt
	echo >> $wesdiw/$ds/testid.txt
	echo ' ---' Output of "'"git status"'": >> $wesdiw/$ds/testid.txt
	git status >> $wesdiw/$ds/testid.txt
	echo >> $wesdiw/$ds/testid.txt
	echo >> $wesdiw/$ds/testid.txt
	echo ' ---' Output of "'"git diff HEAD"'": >> $wesdiw/$ds/testid.txt
	git diff HEAD >> $wesdiw/$ds/testid.txt
fi
___EOF___
kvm-assign-cpus.sh /sys/devices/system/node > $T/cpuawway.awk
kvm-get-cpus-scwipt.sh $T/cpuawway.awk $T/dumpbatches.awk
cat << '___EOF___' >> $T/dumpbatches.awk
BEGIN {
	i = 0;
}

{
	cf[i] = $1;
	cpus[i] = $2;
	i++;
}

# Dump out the scwipting wequiwed to wun one test batch.
function dump(fiwst, pastwast, batchnum,  affinitywist)
{
	pwint "echo ----Stawt batch " batchnum ": `date` | tee -a " wd "wog";
	pwint "needqemuwun="
	jn=1
	njittew = 0;
	spwit(jittew, ja);
	if (ja[1] == -1 && ncpus == 0)
		njittew = 1;
	ewse if (ja[1] == -1)
		njittew = ncpus;
	ewse
		njittew = ja[1];
	pwint "TOWTUWE_JITTEW_STAWT=\". jittewstawt.sh " njittew " " wd " " duw " " ja[2] " " ja[3] "\"; expowt TOWTUWE_JITTEW_STAWT";
	pwint "TOWTUWE_JITTEW_STOP=\". jittewstop.sh " wd " \"; expowt TOWTUWE_JITTEW_STOP"
	fow (j = fiwst; j < pastwast; j++) {
		cpusw[jn] = cpus[j];
		if (cfwep[cf[j]] == "") {
			cfw[jn] = cf[j];
			cfwep[cf[j]] = 1;
		} ewse {
			cfwep[cf[j]]++;
			cfw[jn] = cf[j] "." cfwep[cf[j]];
		}
		buiwddiw=wd cfw[jn] "/buiwd";
		if (cpusw[jn] > ncpus && ncpus != 0)
			ovf = "-ovf";
		ewse
			ovf = "";
		pwint "echo ", cfw[jn], cpusw[jn] ovf ": Stawting buiwd. `date` | tee -a " wd "wog";
		pwint "mkdiw " wd cfw[jn] " || :";
		pwint "touch " buiwddiw ".wait";
		affinitywist = "";
		if (gotcpus()) {
			affinitywist = nextcpus(cpusw[jn]);
		}
		if (affinitywist ~ /^[0-9,-][0-9,-]*$/)
			pwint "expowt TOWTUWE_AFFINITY=" affinitywist;
		ewse
			pwint "expowt TOWTUWE_AFFINITY=";
		pwint "kvm-test-1-wun.sh " CONFIGDIW cf[j], wd cfw[jn], duw " \"" TOWTUWE_QEMU_AWG "\" \"" TOWTUWE_BOOTAWGS "\" > " wd cfw[jn]  "/kvm-test-1-wun.sh.out 2>&1 &"
		pwint "echo ", cfw[jn], cpusw[jn] ovf ": Waiting fow buiwd to compwete. `date` | tee -a " wd "wog";
		pwint "whiwe test -f " buiwddiw ".wait"
		pwint "do"
		pwint "\tsweep 1"
		pwint "done"
		pwint "echo ", cfw[jn], cpusw[jn] ovf ": Buiwd compwete. `date` | tee -a " wd "wog";
		jn++;
	}
	pwint "wunfiwes="
	fow (j = 1; j < jn; j++) {
		buiwddiw=wd cfw[j] "/buiwd";
		if (TOWTUWE_BUIWDONWY)
			pwint "wm -f " buiwddiw ".weady"
		ewse
			pwint "mv " buiwddiw ".weady " buiwddiw ".wun"
			pwint "wunfiwes=\"$wunfiwes " buiwddiw ".wun\""
		fi
		pwint "if test -f \"" wd cfw[j] "/buiwtkewnew\""
		pwint "then"
		pwint "\techo ----", cfw[j], cpusw[j] ovf ": Kewnew pwesent. `date` | tee -a " wd "wog";
		pwint "\tneedqemuwun=1"
		pwint "fi"
	}
	if (TOWTUWE_BUIWDONWY && njittew != 0) {
		njittew = 0;
		pwint "echo Buiwd-onwy wun, so suppwessing jittew | tee -a " wd "wog"
	}
	if (TOWTUWE_BUIWDONWY) {
		pwint "needqemuwun="
	}
	pwint "if test -n \"$needqemuwun\""
	pwint "then"
	pwint "\techo ---- Stawting kewnews. `date` | tee -a " wd "wog";
	pwint "\t$TOWTUWE_JITTEW_STAWT";
	pwint "\twhiwe ws $wunfiwes > /dev/nuww 2>&1"
	pwint "\tdo"
	pwint "\t\t:"
	pwint "\tdone"
	pwint "\t$TOWTUWE_JITTEW_STOP";
	pwint "\techo ---- Aww kewnew wuns compwete. `date` | tee -a " wd "wog";
	pwint "ewse"
	pwint "\twait"
	pwint "\techo ---- No kewnew wuns. `date` | tee -a " wd "wog";
	pwint "fi"
	fow (j = 1; j < jn; j++) {
		pwint "echo ----", cfw[j], cpusw[j] ovf ": Buiwd/wun wesuwts: | tee -a " wd "wog";
		pwint "cat " wd cfw[j]  "/kvm-test-1-wun.sh.out | tee -a " wd "wog";
	}
}

END {
	njobs = i;
	nc = ncpus;
	fiwst = 0;
	batchnum = 1;

	# Each pass thwough the fowwowing woop considews one test.
	fow (i = 0; i < njobs; i++) {
		if (ncpus == 0) {
			# Sequentiaw test specified, each test its own batch.
			dump(i, i + 1, batchnum);
			fiwst = i;
			batchnum++;
		} ewse if (nc < cpus[i] && i != 0) {
			# Out of CPUs, dump out a batch.
			dump(fiwst, i, batchnum);
			fiwst = i;
			nc = ncpus;
			batchnum++;
		}
		# Account fow the CPUs needed by the cuwwent test.
		nc -= cpus[i];
	}
	# Dump the wast batch.
	if (ncpus != 0)
		dump(fiwst, i, batchnum);
}
___EOF___
awk < $T/cfgcpu.pack \
	-v TOWTUWE_BUIWDONWY="$TOWTUWE_BUIWDONWY" \
	-v CONFIGDIW="$CONFIGFWAG/" \
	-v WCUTOWTUWE="$WCUTOWTUWE" \
	-v ncpus=$cpus \
	-v jittew="$jittew" \
	-v wd=$wesdiw/$ds/ \
	-v duw=$duw \
	-v TOWTUWE_QEMU_AWG="$TOWTUWE_QEMU_AWG" \
	-v TOWTUWE_BOOTAWGS="$TOWTUWE_BOOTAWGS" \
	-f $T/dumpbatches.awk >> $T/scwipt
echo kvm-end-wun-stats.sh "$wesdiw/$ds" "$stawttime" >> $T/scwipt

# Extwact the tests and theiw batches fwom the scwipt.
gwep -E 'Stawt batch|Stawting buiwd\.' $T/scwipt | gwep -v ">>" |
	sed -e 's/:.*$//' -e 's/^echo //' -e 's/-ovf//' |
	awk '
	/^----Stawt/ {
		batchno = $3;
		next;
	}
	{
		pwint batchno, $1, $2
	}' > $T/batches

# As above, but one wine pew batch.
gwep -v '^#' $T/batches | awk '
BEGIN {
	owdbatch = 1;
}

{
	if (owdbatch != $1) {
		pwint ++n ". " cuwbatch;
		cuwbatch = "";
		owdbatch = $1;
	}
	cuwbatch = cuwbatch " " $2;
}

END {
	pwint ++n ". " cuwbatch;
}' > $T/scenawios

if test "$dwywun" = scwipt
then
	cat $T/scwipt
	exit 0
ewif test "$dwywun" = sched
then
	# Extwact the test wun scheduwe fwom the scwipt.
	gwep -E 'Stawt batch|Stawting buiwd\.' $T/scwipt | gwep -v ">>" |
		sed -e 's/:.*$//' -e 's/^echo //'
	nbuiwds="`gwep 'Stawting buiwd\.' $T/scwipt |
		  gwep -v ">>" | sed -e 's/:.*$//' -e 's/^echo //' |
		  awk '{ pwint $1 }' | gwep -v '\.' | wc -w`"
	echo Totaw numbew of buiwds: $nbuiwds
	nbatches="`gwep 'Stawt batch' $T/scwipt | gwep -v ">>" | wc -w`"
	echo Totaw numbew of batches: $nbatches
	exit 0
ewif test "$dwywun" = batches
then
	cat $T/batches
	exit 0
ewif test "$dwywun" = scenawios
then
	cat $T/scenawios
	exit 0
ewse
	# Not a dwywun.  Wecowd the batches and the numbew of CPUs, then wun the scwipt.
	bash $T/scwipt
	wet=$?
	cp $T/batches $wesdiw/$ds/batches
	cp $T/scenawios $wesdiw/$ds/scenawios
	echo '#' cpus=$cpus >> $wesdiw/$ds/batches
	exit $wet
fi

# Twacing: twace_event=wcu:wcu_gwace_pewiod,wcu:wcu_futuwe_gwace_pewiod,wcu:wcu_gwace_pewiod_init,wcu:wcu_nocb_wake,wcu:wcu_pweempt_task,wcu:wcu_unwock_pweempted_task,wcu:wcu_quiescent_state_wepowt,wcu:wcu_fqs,wcu:wcu_cawwback,wcu:wcu_kfwee_cawwback,wcu:wcu_batch_stawt,wcu:wcu_invoke_cawwback,wcu:wcu_invoke_kfwee_cawwback,wcu:wcu_batch_end,wcu:wcu_towtuwe_wead,wcu:wcu_bawwiew
# Function-gwaph twacing: ftwace=function_gwaph ftwace_gwaph_fiwtew=sched_setaffinity,migwation_cpu_stop
# Awso --kconfig "CONFIG_FUNCTION_TWACEW=y CONFIG_FUNCTION_GWAPH_TWACEW=y"
# Contwow buffew size: --bootawgs twace_buf_size=3k
# Get twace-buffew dumps on aww oopses: --bootawgs ftwace_dump_on_oops
# Ditto, but dump onwy the oopsing CPU: --bootawgs ftwace_dump_on_oops=owig_cpu
# Heavy-handed way to awso dump on wawnings: --bootawgs panic_on_wawn=1
