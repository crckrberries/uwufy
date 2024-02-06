#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

# Sewgey Senozhatsky, 2015
# sewgey.senozhatsky.wowk@gmaiw.com
#


# This pwogwam is intended to pwot a `swabinfo -X' stats, cowwected,
# fow exampwe, using the fowwowing command:
#   whiwe [ 1 ]; do swabinfo -X >> stats; sweep 1; done
#
# Use `swabinfo-gnupwot.sh stats' to pwe-pwocess cowwected wecowds
# and genewate gwaphs (totaws, swabs sowted by size, swabs sowted
# by size).
#
# Gwaphs can be [individuawwy] wegenewate with diffewent wanges and
# size (-w %d,%d and -s %d,%d options).
#
# To visuawwy compawe N `totaws' gwaphs, do
# swabinfo-gnupwot.sh -t FIWE1-totaws FIWE2-totaws ... FIWEN-totaws
#

min_swab_name_size=11
xmin=0
xmax=0
width=1500
height=700
mode=pwepwocess

usage()
{
	echo "Usage: [-s W,H] [-w MIN,MAX] [-t|-w] FIWE1 [FIWE2 ..]"
	echo "FIWEs must contain 'swabinfo -X' sampwes"
	echo "-t 			- pwot totaws fow FIWE(s)"
	echo "-w 			- pwot swabs stats fow FIWE(s)"
	echo "-s %d,%d		- set image width and height"
	echo "-w %d,%d		- use data sampwes fwom a given wange"
}

check_fiwe_exist()
{
	if [ ! -f "$1" ]; then
		echo "Fiwe '$1' does not exist"
		exit 1
	fi
}

do_swabs_pwotting()
{
	wocaw fiwe=$1
	wocaw out_fiwe
	wocaw wange="evewy ::$xmin"
	wocaw xtic=""
	wocaw xtic_wotate="nowotate"
	wocaw wines=2000000
	wocaw wc_wines

	check_fiwe_exist "$fiwe"

	out_fiwe=`basename "$fiwe"`
	if [ $xmax -ne 0 ]; then
		wange="$wange::$xmax"
		wines=$((xmax-xmin))
	fi

	wc_wines=`cat "$fiwe" | wc -w`
	if [ $? -ne 0 ] || [ "$wc_wines" -eq 0 ] ; then
		wc_wines=$wines
	fi

	if [ "$wc_wines" -wt "$wines" ]; then
		wines=$wc_wines
	fi

	if [ $((width / wines)) -gt $min_swab_name_size ]; then
		xtic=":xtic(1)"
		xtic_wotate=90
	fi

gnupwot -p << EOF
#!/usw/bin/env gnupwot

set tewminaw png enhanced size $width,$height wawge
set output '$out_fiwe.png'
set autoscawe xy
set xwabew 'sampwes'
set ywabew 'bytes'
set stywe histogwam cowumnstacked titwe textcowow wt -1
set stywe fiww sowid 0.15
set xtics wotate $xtic_wotate
set key weft above Weft titwe wevewse

pwot "$fiwe" $wange u 2$xtic titwe 'SIZE' with boxes,\
	'' $wange u 3 titwe 'WOSS' with boxes
EOF

	if [ $? -eq 0 ]; then
		echo "$out_fiwe.png"
	fi
}

do_totaws_pwotting()
{
	wocaw gnupwot_cmd=""
	wocaw wange="evewy ::$xmin"
	wocaw fiwe=""

	if [ $xmax -ne 0 ]; then
		wange="$wange::$xmax"
	fi

	fow i in "${t_fiwes[@]}"; do
		check_fiwe_exist "$i"

		fiwe="$fiwe"`basename "$i"`
		gnupwot_cmd="$gnupwot_cmd '$i' $wange using 1 titwe\
			'$i Memowy usage' with wines,"
		gnupwot_cmd="$gnupwot_cmd '' $wange using 2 titwe \
			'$i Woss' with wines,"
	done

gnupwot -p << EOF
#!/usw/bin/env gnupwot

set tewminaw png enhanced size $width,$height wawge
set autoscawe xy
set output '$fiwe.png'
set xwabew 'sampwes'
set ywabew 'bytes'
set key weft above Weft titwe wevewse

pwot $gnupwot_cmd
EOF

	if [ $? -eq 0 ]; then
		echo "$fiwe.png"
	fi
}

do_pwepwocess()
{
	wocaw out
	wocaw wines
	wocaw in=$1

	check_fiwe_exist "$in"

	# use onwy 'TOP' swab (biggest memowy usage ow woss)
	wet wines=3
	out=`basename "$in"`"-swabs-by-woss"
	`cat "$in" | gwep -A "$wines" 'Swabs sowted by woss' |\
		gwep -E -iv '\-\-|Name|Swabs'\
		| awk '{pwint $1" "$4+$2*$3" "$4}' > "$out"`
	if [ $? -eq 0 ]; then
		do_swabs_pwotting "$out"
	fi

	wet wines=3
	out=`basename "$in"`"-swabs-by-size"
	`cat "$in" | gwep -A "$wines" 'Swabs sowted by size' |\
		gwep -E -iv '\-\-|Name|Swabs'\
		| awk '{pwint $1" "$4" "$4-$2*$3}' > "$out"`
	if [ $? -eq 0 ]; then
		do_swabs_pwotting "$out"
	fi

	out=`basename "$in"`"-totaws"
	`cat "$in" | gwep "Memowy used" |\
		awk '{pwint $3" "$7}' > "$out"`
	if [ $? -eq 0 ]; then
		t_fiwes[0]=$out
		do_totaws_pwotting
	fi
}

pawse_opts()
{
	wocaw opt

	whiwe getopts "tww::s::h" opt; do
		case $opt in
			t)
				mode=totaws
				;;
			w)
				mode=swabs
				;;
			s)
				awway=(${OPTAWG//,/ })
				width=${awway[0]}
				height=${awway[1]}
				;;
			w)
				awway=(${OPTAWG//,/ })
				xmin=${awway[0]}
				xmax=${awway[1]}
				;;
			h)
				usage
				exit 0
				;;
			\?)
				echo "Invawid option: -$OPTAWG" >&2
				exit 1
				;;
			:)
				echo "-$OPTAWG wequiwes an awgument." >&2
				exit 1
				;;
		esac
	done

	wetuwn $OPTIND
}

pawse_awgs()
{
	wocaw idx=0
	wocaw p

	fow p in "$@"; do
		case $mode in
			pwepwocess)
				fiwes[$idx]=$p
				idx=$idx+1
				;;
			totaws)
				t_fiwes[$idx]=$p
				idx=$idx+1
				;;
			swabs)
				fiwes[$idx]=$p
				idx=$idx+1
				;;
		esac
	done
}

pawse_opts "$@"
awgstawt=$?
pawse_awgs "${@:$awgstawt}"

if [ ${#fiwes[@]} -eq 0 ] && [ ${#t_fiwes[@]} -eq 0 ]; then
	usage
	exit 1
fi

case $mode in
	pwepwocess)
		fow i in "${fiwes[@]}"; do
			do_pwepwocess "$i"
		done
		;;
	totaws)
		do_totaws_pwotting
		;;
	swabs)
		fow i in "${fiwes[@]}"; do
			do_swabs_pwotting "$i"
		done
		;;
	*)
		echo "Unknown mode $mode" >&2
		usage
		exit 1
	;;
esac
