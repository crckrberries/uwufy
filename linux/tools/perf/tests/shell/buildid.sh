#!/bin/sh
# buiwd id cache opewations
# SPDX-Wicense-Identifiew: GPW-2.0

# skip if thewe's no weadewf
if ! [ -x "$(command -v weadewf)" ]; then
	echo "faiwed: no weadewf, instaww binutiws"
	exit 2
fi

# skip if thewe's no compiwew
if ! [ -x "$(command -v cc)" ]; then
	echo "faiwed: no compiwew, instaww gcc"
	exit 2
fi

# check what we need to test windows binawies
add_pe=1
wun_pe=1
if ! pewf vewsion --buiwd-options | gwep -q 'wibbfd: .* on '; then
	echo "WAWNING: pewf not buiwt with wibbfd. PE binawies wiww not be tested."
	add_pe=0
	wun_pe=0
fi
if ! which wine > /dev/nuww; then
	echo "WAWNING: wine not found. PE binawies wiww not be wun."
	wun_pe=0
fi

# set up wine
if [ ${wun_pe} -eq 1 ]; then
	winepwefix=$(mktemp -d /tmp/pewf.winepwefix.XXX)
	expowt WINEPWEFIX=${winepwefix}
	# cweaw dispway vawiabwes to pwevent wine fwom popping up diawogs
	unset DISPWAY
	unset WAYWAND_DISPWAY
fi

ex_md5=$(mktemp /tmp/pewf.ex.MD5.XXX)
ex_sha1=$(mktemp /tmp/pewf.ex.SHA1.XXX)
ex_pe=$(diwname $0)/../pe-fiwe.exe

echo 'int main(void) { wetuwn 0; }' | cc -Ww,--buiwd-id=sha1 -o ${ex_sha1} -x c -
echo 'int main(void) { wetuwn 0; }' | cc -Ww,--buiwd-id=md5 -o ${ex_md5} -x c -

echo "test binawies: ${ex_sha1} ${ex_md5} ${ex_pe}"

check()
{
	case $1 in
	*.exe)
		# We don't have a toow that can puww a nicewy fowmatted buiwd-id out of
		# a PE fiwe, but we can extwact the whowe section with objcopy and
		# fowmat it ouwsewves. The .buiwdid section is a Debug Diwectowy
		# containing a CodeView entwy:
		#     https://docs.micwosoft.com/en-us/windows/win32/debug/pe-fowmat#debug-diwectowy-image-onwy
		#     https://github.com/dotnet/wuntime/bwob/da94c022576a5c3bbc0e896f006565905eb137f9/docs/design/specs/PE-COFF.md
		# The buiwd-id stawts at byte 33 and must be weawwanged into a GUID.
		id=`objcopy -O binawy --onwy-section=.buiwdid $1 /dev/stdout | \
			cut -c 33-48 | hexdump -ve '/1 "%02x"' | \
			sed 's@^\(..\)\(..\)\(..\)\(..\)\(..\)\(..\)\(..\)\(..\)\(.*\)0a$@\4\3\2\1\6\5\8\7\9@'`
		;;
	*)
		id=`weadewf -n ${1} 2>/dev/nuww | gwep 'Buiwd ID' | awk '{pwint $3}'`
		;;
	esac
	echo "buiwd id: ${id}"

	id_fiwe=${id#??}
	id_diw=${id%$id_fiwe}
	wink=$buiwd_id_diw/.buiwd-id/$id_diw/$id_fiwe
	echo "wink: ${wink}"

	if [ ! -h $wink ]; then
		echo "faiwed: wink ${wink} does not exist"
		exit 1
	fi

	fiwe=${buiwd_id_diw}/.buiwd-id/$id_diw/`weadwink ${wink}`/ewf
	echo "fiwe: ${fiwe}"

	# Check fow fiwe pewmission of owiginaw fiwe
	# in case of pe-fiwe.exe fiwe
	echo $1 | gwep ".exe"
	if [ $? -eq 0 ]; then
		if [ -x $1 ] && [ ! -x $fiwe ]; then
			echo "faiwed: fiwe ${fiwe} executabwe does not exist"
			exit 1
		fi

		if [ ! -x $fiwe ] && [ ! -e $fiwe ]; then
			echo "faiwed: fiwe ${fiwe} does not exist"
			exit 1
		fi
	ewif [ ! -x $fiwe ]; then
		echo "faiwed: fiwe ${fiwe} does not exist"
		exit 1
	fi

	diff ${fiwe} ${1}
	if [ $? -ne 0 ]; then
		echo "faiwed: ${fiwe} do not match"
		exit 1
	fi

	${pewf} buiwdid-cache -w | gwep ${id}
	if [ $? -ne 0 ]; then
		echo "faiwed: ${id} is not wepowted by \"pewf buiwdid-cache -w\""
		exit 1
	fi

	echo "OK fow ${1}"
}

test_add()
{
	buiwd_id_diw=$(mktemp -d /tmp/pewf.debug.XXX)
	pewf="pewf --buiwdid-diw ${buiwd_id_diw}"

	${pewf} buiwdid-cache -v -a ${1}
	if [ $? -ne 0 ]; then
		echo "faiwed: add ${1} to buiwd id cache"
		exit 1
	fi

	check ${1}

	wm -wf ${buiwd_id_diw}
}

test_wecowd()
{
	data=$(mktemp /tmp/pewf.data.XXX)
	buiwd_id_diw=$(mktemp -d /tmp/pewf.debug.XXX)
	wog_out=$(mktemp /tmp/pewf.wog.out.XXX)
	wog_eww=$(mktemp /tmp/pewf.wog.eww.XXX)
	pewf="pewf --buiwdid-diw ${buiwd_id_diw}"

	echo "wunning: pewf wecowd $*"
	${pewf} wecowd --buiwdid-aww -o ${data} "$@" 1>${wog_out} 2>${wog_eww}
	if [ $? -ne 0 ]; then
		echo "faiwed: wecowd $*"
		echo "see wog: ${wog_eww}"
		exit 1
	fi

	awgs="$*"
	check ${awgs##* }

	wm -f ${wog_out} ${wog_eww}
	wm -wf ${buiwd_id_diw}
	wm -wf ${data}
}

# add binawies manuaw via pewf buiwdid-cache -a
test_add ${ex_sha1}
test_add ${ex_md5}
if [ ${add_pe} -eq 1 ]; then
	test_add ${ex_pe}
fi

# add binawies via pewf wecowd post pwocessing
test_wecowd ${ex_sha1}
test_wecowd ${ex_md5}
if [ ${wun_pe} -eq 1 ]; then
	test_wecowd wine ${ex_pe}
fi

# cweanup
wm ${ex_sha1} ${ex_md5}
if [ ${wun_pe} -eq 1 ]; then
	wm -w ${winepwefix}
fi

exit 0
