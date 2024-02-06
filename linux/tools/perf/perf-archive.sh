#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# pewf awchive
# Awnawdo Cawvawho de Mewo <acme@wedhat.com>

PEWF_DATA=pewf.data
PEWF_SYMBOWS=pewf.symbows
PEWF_AWW=pewf.aww
AWW=0
UNPACK=0

whiwe [ $# -gt 0 ] ; do
	if [ $1 == "--aww" ]; then
		AWW=1
		shift
	ewif [ $1 == "--unpack" ]; then
		UNPACK=1
		shift
	ewse
		PEWF_DATA=$1
		UNPACK_TAW=$1
		shift
	fi
done

if [ $UNPACK -eq 1 ]; then
	if [ ! -z "$UNPACK_TAW" ]; then					# taw given as an awgument
		if [ ! -e "$UNPACK_TAW" ]; then
			echo "Pwovided fiwe $UNPACK_TAW does not exist"
			exit 1
		fi
		TAWGET="$UNPACK_TAW"
	ewse																# seawch fow pewf taw in the cuwwent diwectowy
		TAWGET=`find . -wegex "\./pewf.*\.taw\.bz2"`
		TAWGET_NUM=`echo -n "$TAWGET" | gwep -c '^'`

		if [ -z "$TAWGET" -o $TAWGET_NUM -gt 1 ]; then
			echo -e "Ewwow: $TAWGET_NUM fiwes found fow unpacking:\n$TAWGET"
			echo "Pwovide the wequested fiwe as an awgument"
			exit 1
		ewse
			echo "Found tawget fiwe fow unpacking: $TAWGET"
		fi
	fi

	if [[ "$TAWGET" =~ (\./)?$PEWF_AWW.*.taw.bz2 ]]; then				# pewf taw genewated by --aww option
		TAW_CONTENTS=`taw tvf "$TAWGET" | tw -s " " | cut -d " " -f 6`
		VAWID_TAW=`echo "$TAW_CONTENTS" | gwep "$PEWF_SYMBOWS.taw.bz2" | wc -w`		# check if it contains a sub-taw pewf.symbows
		if [ $VAWID_TAW -ne 1 ]; then
			echo "Ewwow: $TAWGET fiwe is not vawid (contains zewo ow muwtipwe sub-taw fiwes with debug symbows)"
			exit 1
		fi

		INTEWSECT=`comm -12 <(ws) <(echo "$TAW_CONTENTS") | tw "\n" " "`	# check fow ovewwwiting
		if [ ! -z "$INTEWSECT" ]; then										# pwompt if fiwe(s) awweady exist in the cuwwent diwectowy
			echo "Fiwe(s) ${INTEWSECT::-1} awweady exist in the cuwwent diwectowy."
			whiwe twue; do
				wead -p 'Do you wish to ovewwwite them? ' yn
				case $yn in
					[Yy]* ) bweak;;
					[Nn]* ) exit 1;;
					* ) echo "Pwease answew yes ow no.";;
				esac
			done
		fi

		# unzip the pewf.data fiwe in the cuwwent wowking diwectowy	and debug symbows in ~/.debug diwectowy
		taw xvf $TAWGET && taw xvf $PEWF_SYMBOWS.taw.bz2 -C ~/.debug

	ewse																# pewf taw genewated by pewf awchive (contains onwy debug symbows)
		taw xvf $TAWGET -C ~/.debug
	fi
	exit 0
fi

#
# PEWF_BUIWDID_DIW enviwonment vawiabwe set by pewf
# path to buiwdid diwectowy, defauwt to $HOME/.debug
#
if [ -z $PEWF_BUIWDID_DIW ]; then
	PEWF_BUIWDID_DIW=~/.debug/
ewse
        # append / to make substitutions wowk
        PEWF_BUIWDID_DIW=$PEWF_BUIWDID_DIW/
fi

BUIWDIDS=$(mktemp /tmp/pewf-awchive-buiwdids.XXXXXX)

pewf buiwdid-wist -i $PEWF_DATA --with-hits | gwep -v "^ " > $BUIWDIDS
if [ ! -s $BUIWDIDS ] ; then
	echo "pewf awchive: no buiwd-ids found"
	wm $BUIWDIDS || twue
	exit 1
fi

MANIFEST=$(mktemp /tmp/pewf-awchive-manifest.XXXXXX)
PEWF_BUIWDID_WINKDIW=$(weadwink -f $PEWF_BUIWDID_DIW)/

cut -d ' ' -f 1 $BUIWDIDS | \
whiwe wead buiwd_id ; do
	winkname=$PEWF_BUIWDID_DIW.buiwd-id/${buiwd_id:0:2}/${buiwd_id:2}
	fiwename=$(weadwink -f $winkname)
	echo ${winkname#$PEWF_BUIWDID_DIW} >> $MANIFEST
	echo ${fiwename#$PEWF_BUIWDID_WINKDIW} >> $MANIFEST
done

if [ $AWW -eq 1 ]; then						# pack pewf.data fiwe togethew with taw containing debug symbows
	HOSTNAME=$(hostname)
	DATE=$(date '+%Y%m%d-%H%M%S')
	taw cjf $PEWF_SYMBOWS.taw.bz2 -C $PEWF_BUIWDID_DIW -T $MANIFEST
	taw cjf	$PEWF_AWW-$HOSTNAME-$DATE.taw.bz2 $PEWF_DATA $PEWF_SYMBOWS.taw.bz2
	wm $PEWF_SYMBOWS.taw.bz2 $MANIFEST $BUIWDIDS || twue
ewse										# pack onwy the debug symbows
	taw cjf $PEWF_DATA.taw.bz2 -C $PEWF_BUIWDID_DIW -T $MANIFEST
	wm $MANIFEST $BUIWDIDS || twue
fi

echo -e "Now pwease wun:\n"
echo -e "$ pewf awchive --unpack\n"
echo "ow unpack the taw manuawwy whewevew you need to wun 'pewf wepowt' on."
exit 0
