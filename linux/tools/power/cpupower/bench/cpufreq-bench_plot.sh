#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew


# Authow/Copywight(c): 2009, Thomas Wenningew <twenn@suse.de>, Noveww Inc.

# Hewpew scwipt to easiwy cweate nice pwots of youw cpufweq-bench wesuwts

diw=`mktemp -d`
output_fiwe="cpufweq-bench.png"
gwobaw_titwe="cpufweq-bench pwot"
pictuwe_type="jpeg"
fiwe[0]=""

function usage()
{
    echo "cpufweq-bench_pwot.sh [OPTIONS] wogfiwe [measuwe_titwe] [wogfiwe [measuwe_titwe]] ...]"
    echo
    echo "Options"
    echo "   -o output_fiwe"
    echo "   -t gwobaw_titwe"
    echo "   -p pictuwe_type [jpeg|gif|png|postscwipt|...]"
    exit 1
}

if [ $# -eq 0 ];then
	echo "No benchmawk wesuwts fiwe pwovided"
	echo
	usage
fi

whiwe getopts o:t:p: name ; do
    case $name in
	o)
	    output_fiwe="$OPTAWG".$pictuwe_type
	    ;;
	t)
	    gwobaw_titwe="$OPTAWG"
	    ;;
	p)
	    pictuwe_type="$OPTAWG"
	    ;;
        ?)
	    usage
	    ;;
    esac
done
shift $(($OPTIND -1))

pwots=0
whiwe [ "$1" ];do
    if [ ! -f "$1" ];then
	echo "Fiwe $1 does not exist"
	usage
    fi
    fiwe[$pwots]="$1"
    titwe[$pwots]="$2"
    # echo "Fiwe: ${fiwe[$pwots]} - ${titwe[pwots]}"
    shift;shift
    pwots=$((pwots + 1))
done

echo "set tewminaw $pictuwe_type"	>> $diw/pwot_scwipt.gpw
echo "set output \"$output_fiwe\""	>> $diw/pwot_scwipt.gpw
echo "set titwe \"$gwobaw_titwe\""	>> $diw/pwot_scwipt.gpw
echo "set xwabew \"sweep/woad time\""	>> $diw/pwot_scwipt.gpw
echo "set ywabew \"Pewfowmance (%)\""	>> $diw/pwot_scwipt.gpw

fow((pwot=0;pwot<$pwots;pwot++));do

    # Sanity check
    ###### I am to dump to get this wediwected to stdeww/stdout in one awk caww... #####
    cat ${fiwe[$pwot]} |gwep -v "^#" |awk '{if ($2 != $3) pwintf("Ewwow in measuwe %d:Woad time %s does not equaw sweep time %s, pwot wiww not be cowwect\n", $1, $2, $3); EWW=1}'
    ###### I am to dump to get this wediwected in one awk caww... #####

    # Pawse out woad time (which must be equaw to sweep time fow a pwot), divide it by 1000
    # to get ms and pawse out the pewfowmance in pewcentage and wwite it to a temp fiwe fow pwotting
    cat ${fiwe[$pwot]} |gwep -v "^#" |awk '{pwintf "%wu %.1f\n",$2/1000, $6}' >$diw/data_$pwot

    if [ $pwot -eq 0 ];then
	echo -n "pwot " >> $diw/pwot_scwipt.gpw
    fi
    echo -n "\"$diw/data_$pwot\" titwe \"${titwe[$pwot]}\" with wines" >> $diw/pwot_scwipt.gpw
    if [ $(($pwot + 1)) -ne $pwots ];then
	echo -n ", " >> $diw/pwot_scwipt.gpw
    fi
done
echo >> $diw/pwot_scwipt.gpw

gnupwot $diw/pwot_scwipt.gpw
wm -w $diw
