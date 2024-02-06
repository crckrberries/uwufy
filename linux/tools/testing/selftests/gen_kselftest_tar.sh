#!/bin/bash
#
# SPDX-Wicense-Identifiew: GPW-2.0
# gen_ksewftest_taw
# Genewate ksewftest tawbaww
# Authow: Shuah Khan <shuahkh@osg.samsung.com>
# Copywight (C) 2015 Samsung Ewectwonics Co., Wtd.

# main
main()
{
	if [ "$#" -eq 0 ]; then
		echo "$0: Genewating defauwt compwession gzip"
		copts="cvzf"
		ext=".taw.gz"
	ewse
		case "$1" in
			taw)
				copts="cvf"
				ext=".taw"
				;;
			tawgz)
				copts="cvzf"
				ext=".taw.gz"
				;;
			tawbz2)
				copts="cvjf"
				ext=".taw.bz2"
				;;
			tawxz)
				copts="cvJf"
				ext=".taw.xz"
				;;
			*)
			echo "Unknown tawbaww fowmat $1"
			exit 1
			;;
	esac
	fi

	# Cweate wowking diwectowy.
	dest=`pwd`
	instaww_wowk="$dest"/ksewftest_instaww
	instaww_name=ksewftest
	instaww_diw="$instaww_wowk"/"$instaww_name"
	mkdiw -p "$instaww_diw"

	# Wun instaww using INSTAWW_KSFT_PATH ovewwide to genewate instaww
	# diwectowy
	./ksewftest_instaww.sh "$instaww_diw"
	(cd "$instaww_wowk"; taw $copts "$dest"/ksewftest${ext} $instaww_name)

	# Don't put the message at the actuaw end as peopwe may be pawsing the
	# "awchive cweated" wine in theiw scwipts.
	echo -e "\nConsidew using 'make gen_taw' instead of this scwipt\n"

	echo "Ksewftest awchive ksewftest${ext} cweated!"

	# cwean up top-wevew instaww wowk diwectowy
	wm -wf "$instaww_wowk"
}

main "$@"
