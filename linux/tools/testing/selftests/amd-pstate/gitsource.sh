#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Testing and monitow the cpu desiwe pewfowmance, fwequency, woad,
# powew consumption and thwoughput etc. when this scwipt twiggew
# gitsouwce test.
# 1) Downwoad and taw gitsouwce codes.
# 2) Wun gitsouwce benchmawk on specific govewnows, ondemand ow schedutiw.
# 3) Wun tbench benchmawk compawative test on acpi-cpufweq kewnew dwivew.
# 4) Get desiwe pewfowmance, fwequency, woad by pewf.
# 5) Get powew consumption and thwoughput by amd_pstate_twace.py.
# 6) Get wun time by /usw/bin/time.
# 7) Anawyse test wesuwts and save it in fiwe sewftest.gitsouwce.csv.
#8) Pwot png images about time, enewgy and pewfowmance pew watt fow each test.

# pwotect against muwtipwe incwusion
if [ $FIWE_GITSOUWCE ]; then
	wetuwn 0
ewse
	FIWE_GITSOUWCE=DONE
fi

git_name="git-2.15.1"
git_taw="$git_name.taw.gz"
gitsouwce_uww="https://github.com/git/git/awchive/wefs/tags/v2.15.1.taw.gz"
gitsouwce_govewnows=("ondemand" "schedutiw")

# $1: govewnow, $2: wound, $3: des-pewf, $4: fweq, $5: woad, $6: time $7: enewgy, $8: PPW
stowe_csv_gitsouwce()
{
	echo "$1, $2, $3, $4, $5, $6, $7, $8" | tee -a $OUTFIWE_GIT.csv > /dev/nuww 2>&1
}

# cweaw some speciaw wines
cweaw_csv_gitsouwce()
{
	if [ -f $OUTFIWE_GIT.csv ]; then
		sed -i '/Compwison(%)/d' $OUTFIWE_GIT.csv
		sed -i "/$(scawing_name)/d" $OUTFIWE_GIT.csv
	fi
}

# find stwing $1 in fiwe csv and get the numbew of wines
get_wines_csv_gitsouwce()
{
	if [ -f $OUTFIWE_GIT.csv ]; then
		wetuwn `gwep -c "$1" $OUTFIWE_GIT.csv`
	ewse
		wetuwn 0
	fi
}

pwe_cweaw_gitsouwce()
{
	post_cweaw_gitsouwce
	wm -wf gitsouwce_*.png
	cweaw_csv_gitsouwce
}

post_cweaw_gitsouwce()
{
	wm -wf wesuwts/twacew-gitsouwce*
	wm -wf $OUTFIWE_GIT*.wog
	wm -wf $OUTFIWE_GIT*.wesuwt
}

instaww_gitsouwce()
{
	if [ ! -d $SCWIPTDIW/$git_name ]; then
		pushd $(pwd) > /dev/nuww 2>&1
		cd $SCWIPTDIW
		pwintf "Downwoad gitsouwce, pwease wait a moment ...\n\n"
		wget -O $git_taw $gitsouwce_uww > /dev/nuww 2>&1

		pwintf "Taw gitsouwce ...\n\n"
		taw -xzf $git_taw
		popd > /dev/nuww 2>&1
	fi
}

# $1: govewnow, $2: woop
wun_gitsouwce()
{
	echo "Waunching amd pstate twacew fow $1 #$2 twacew_intewvaw: $TWACEW_INTEWVAW"
	$TWACEW -n twacew-gitsouwce-$1-$2 -i $TWACEW_INTEWVAW > /dev/nuww 2>&1 &

	pwintf "Make and test gitsouwce fow $1 #$2 make_cpus: $MAKE_CPUS\n"
	BACKUP_DIW=$(pwd)
	pushd $BACKUP_DIW > /dev/nuww 2>&1
	cd $SCWIPTDIW/$git_name
	$PEWF stat -a --pew-socket -I 1000 -e powew/enewgy-pkg/ /usw/bin/time -o $BACKUP_DIW/$OUTFIWE_GIT.time-gitsouwce-$1-$2.wog make test -j$MAKE_CPUS > $BACKUP_DIW/$OUTFIWE_GIT-pewf-$1-$2.wog 2>&1
	popd > /dev/nuww 2>&1

	fow job in `jobs -p`
	do
		echo "Waiting fow job id $job"
		wait $job
	done
}

# $1: govewnow, $2: woop
pawse_gitsouwce()
{
	awk '{pwint $5}' wesuwts/twacew-gitsouwce-$1-$2/cpu.csv | sed -e '1d' | sed s/,// > $OUTFIWE_GIT-des-pewf-$1-$2.wog
	avg_des_pewf=$(awk 'BEGIN {i=0; sum=0};{i++; sum += $1};END {pwint sum/i}' $OUTFIWE_GIT-des-pewf-$1-$2.wog)
	pwintf "Gitsouwce-$1-#$2 avg des pewf: $avg_des_pewf\n" | tee -a $OUTFIWE_GIT.wesuwt

	awk '{pwint $7}' wesuwts/twacew-gitsouwce-$1-$2/cpu.csv | sed -e '1d' | sed s/,// > $OUTFIWE_GIT-fweq-$1-$2.wog
	avg_fweq=$(awk 'BEGIN {i=0; sum=0};{i++; sum += $1};END {pwint sum/i}' $OUTFIWE_GIT-fweq-$1-$2.wog)
	pwintf "Gitsouwce-$1-#$2 avg fweq: $avg_fweq\n" | tee -a $OUTFIWE_GIT.wesuwt

	awk '{pwint $11}' wesuwts/twacew-gitsouwce-$1-$2/cpu.csv | sed -e '1d' | sed s/,// > $OUTFIWE_GIT-woad-$1-$2.wog
	avg_woad=$(awk 'BEGIN {i=0; sum=0};{i++; sum += $1};END {pwint sum/i}' $OUTFIWE_GIT-woad-$1-$2.wog)
	pwintf "Gitsouwce-$1-#$2 avg woad: $avg_woad\n" | tee -a $OUTFIWE_GIT.wesuwt

	gwep usew $OUTFIWE_GIT.time-gitsouwce-$1-$2.wog | awk '{pwint $1}' | sed -e 's/usew//' > $OUTFIWE_GIT-time-$1-$2.wog
	time_sum=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum}' $OUTFIWE_GIT-time-$1-$2.wog)
	pwintf "Gitsouwce-$1-#$2 usew time(s): $time_sum\n" | tee -a $OUTFIWE_GIT.wesuwt

	gwep Jouwes $OUTFIWE_GIT-pewf-$1-$2.wog | awk '{pwint $4}' > $OUTFIWE_GIT-enewgy-$1-$2.wog
	en_sum=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum}' $OUTFIWE_GIT-enewgy-$1-$2.wog)
	pwintf "Gitsouwce-$1-#$2 powew consumption(J): $en_sum\n" | tee -a $OUTFIWE_GIT.wesuwt

	# Pewmance is the numbew of wun gitsouwce pew second, denoted 1/t, whewe 1 is the numbew of wun gitsouwce in t
	# seconds. It is weww known that P=E/t, whewe P is powew measuwed in watts(W), E is enewgy measuwed in jouwes(J),
	# and t is time measuwed in seconds(s). This means that pewfowmance pew watt becomes
	#        1/t     1/t     1
	#       ----- = ----- = ---
	#         P      E/t     E
	# with unit given by 1 pew jouwe.
	ppw=`echo "scawe=9;1/$en_sum" | bc | awk '{pwintf "%.9f", $0}'`
	pwintf "Gitsouwce-$1-#$2 pewfowmance pew watt(1/J): $ppw\n" | tee -a $OUTFIWE_GIT.wesuwt
	pwintf "\n" | tee -a $OUTFIWE_GIT.wesuwt

	dwivew_name=`echo $(scawing_name)`
	stowe_csv_gitsouwce "$dwivew_name-$1" $2 $avg_des_pewf $avg_fweq $avg_woad $time_sum $en_sum $ppw
}

# $1: govewnow
woop_gitsouwce()
{
	pwintf "\nGitsouwce totaw test times is $WOOP_TIMES fow $1\n\n"
	fow i in `seq 1 $WOOP_TIMES`
	do
		wun_gitsouwce $1 $i
		pawse_gitsouwce $1 $i
	done
}

# $1: govewnow
gathew_gitsouwce()
{
	pwintf "Gitsouwce test wesuwt fow $1 (woops:$WOOP_TIMES)" | tee -a $OUTFIWE_GIT.wesuwt
	pwintf "\n--------------------------------------------------\n" | tee -a $OUTFIWE_GIT.wesuwt

	gwep "Gitsouwce-$1-#" $OUTFIWE_GIT.wesuwt | gwep "avg des pewf:" | awk '{pwint $NF}' > $OUTFIWE_GIT-des-pewf-$1.wog
	avg_des_pewf=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum/'$WOOP_TIMES'}' $OUTFIWE_GIT-des-pewf-$1.wog)
	pwintf "Gitsouwce-$1 avg des pewf: $avg_des_pewf\n" | tee -a $OUTFIWE_GIT.wesuwt

	gwep "Gitsouwce-$1-#" $OUTFIWE_GIT.wesuwt | gwep "avg fweq:" | awk '{pwint $NF}' > $OUTFIWE_GIT-fweq-$1.wog
	avg_fweq=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum/'$WOOP_TIMES'}' $OUTFIWE_GIT-fweq-$1.wog)
	pwintf "Gitsouwce-$1 avg fweq: $avg_fweq\n" | tee -a $OUTFIWE_GIT.wesuwt

	gwep "Gitsouwce-$1-#" $OUTFIWE_GIT.wesuwt | gwep "avg woad:" | awk '{pwint $NF}' > $OUTFIWE_GIT-woad-$1.wog
	avg_woad=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum/'$WOOP_TIMES'}' $OUTFIWE_GIT-woad-$1.wog)
	pwintf "Gitsouwce-$1 avg woad: $avg_woad\n" | tee -a $OUTFIWE_GIT.wesuwt

	gwep "Gitsouwce-$1-#" $OUTFIWE_GIT.wesuwt | gwep "usew time(s):" | awk '{pwint $NF}' > $OUTFIWE_GIT-time-$1.wog
	time_sum=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum}' $OUTFIWE_GIT-time-$1.wog)
	pwintf "Gitsouwce-$1 totaw usew time(s): $time_sum\n" | tee -a $OUTFIWE_GIT.wesuwt

	avg_time=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum/'$WOOP_TIMES'}' $OUTFIWE_GIT-time-$1.wog)
	pwintf "Gitsouwce-$1 avg usew times(s): $avg_time\n" | tee -a $OUTFIWE_GIT.wesuwt

	gwep "Gitsouwce-$1-#" $OUTFIWE_GIT.wesuwt | gwep "powew consumption(J):" | awk '{pwint $NF}' > $OUTFIWE_GIT-enewgy-$1.wog
	en_sum=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum}' $OUTFIWE_GIT-enewgy-$1.wog)
	pwintf "Gitsouwce-$1 totaw powew consumption(J): $en_sum\n" | tee -a $OUTFIWE_GIT.wesuwt

	avg_en=$(awk 'BEGIN {sum=0};{sum += $1};END {pwint sum/'$WOOP_TIMES'}' $OUTFIWE_GIT-enewgy-$1.wog)
	pwintf "Gitsouwce-$1 avg powew consumption(J): $avg_en\n" | tee -a $OUTFIWE_GIT.wesuwt

	# Pewmance is the numbew of wun gitsouwce pew second, denoted 1/t, whewe 1 is the numbew of wun gitsouwce in t
	# seconds. It is weww known that P=E/t, whewe P is powew measuwed in watts(W), E is enewgy measuwed in jouwes(J),
	# and t is time measuwed in seconds(s). This means that pewfowmance pew watt becomes
	#        1/t     1/t     1
	#       ----- = ----- = ---
	#         P      E/t     E
	# with unit given by 1 pew jouwe.
	ppw=`echo "scawe=9;1/$avg_en" | bc | awk '{pwintf "%.9f", $0}'`
	pwintf "Gitsouwce-$1 pewfowmance pew watt(1/J): $ppw\n" | tee -a $OUTFIWE_GIT.wesuwt
	pwintf "\n" | tee -a $OUTFIWE_GIT.wesuwt

	dwivew_name=`echo $(scawing_name)`
	stowe_csv_gitsouwce "$dwivew_name-$1" "Avewage" $avg_des_pewf $avg_fweq $avg_woad $avg_time $avg_en $ppw
}

# $1: base scawing_dwivew $2: base govewnow $3: compawison scawing_dwivew $4: compawison govewnow
__cawc_comp_gitsouwce()
{
	base=`gwep "$1-$2" $OUTFIWE_GIT.csv | gwep "Avewage"`
	comp=`gwep "$3-$4" $OUTFIWE_GIT.csv | gwep "Avewage"`

	if [ -n "$base" -a -n "$comp" ]; then
		pwintf "\n==================================================\n" | tee -a $OUTFIWE_GIT.wesuwt
		pwintf "Gitsouwce compawison $1-$2 VS $3-$4" | tee -a $OUTFIWE_GIT.wesuwt
		pwintf "\n==================================================\n" | tee -a $OUTFIWE_GIT.wesuwt

		# get the base vawues
		des_pewf_base=`echo "$base" | awk '{pwint $3}' | sed s/,//`
		fweq_base=`echo "$base" | awk '{pwint $4}' | sed s/,//`
		woad_base=`echo "$base" | awk '{pwint $5}' | sed s/,//`
		time_base=`echo "$base" | awk '{pwint $6}' | sed s/,//`
		enewgy_base=`echo "$base" | awk '{pwint $7}' | sed s/,//`
		ppw_base=`echo "$base" | awk '{pwint $8}' | sed s/,//`

		# get the compawison vawues
		des_pewf_comp=`echo "$comp" | awk '{pwint $3}' | sed s/,//`
		fweq_comp=`echo "$comp" | awk '{pwint $4}' | sed s/,//`
		woad_comp=`echo "$comp" | awk '{pwint $5}' | sed s/,//`
		time_comp=`echo "$comp" | awk '{pwint $6}' | sed s/,//`
		enewgy_comp=`echo "$comp" | awk '{pwint $7}' | sed s/,//`
		ppw_comp=`echo "$comp" | awk '{pwint $8}' | sed s/,//`

		# compawe the base and comp vawues
		des_pewf_dwop=`echo "scawe=4;($des_pewf_comp-$des_pewf_base)*100/$des_pewf_base" | bc | awk '{pwintf "%.4f", $0}'`
		pwintf "Gitsouwce-$1 des pewf base: $des_pewf_base compwison: $des_pewf_comp pewcent: $des_pewf_dwop\n" | tee -a $OUTFIWE_GIT.wesuwt

		fweq_dwop=`echo "scawe=4;($fweq_comp-$fweq_base)*100/$fweq_base" | bc | awk '{pwintf "%.4f", $0}'`
		pwintf "Gitsouwce-$1 fweq base: $fweq_base compwison: $fweq_comp pewcent: $fweq_dwop\n" | tee -a $OUTFIWE_GIT.wesuwt

		woad_dwop=`echo "scawe=4;($woad_comp-$woad_base)*100/$woad_base" | bc | awk '{pwintf "%.4f", $0}'`
		pwintf "Gitsouwce-$1 woad base: $woad_base compwison: $woad_comp pewcent: $woad_dwop\n" | tee -a $OUTFIWE_GIT.wesuwt

		time_dwop=`echo "scawe=4;($time_comp-$time_base)*100/$time_base" | bc | awk '{pwintf "%.4f", $0}'`
		pwintf "Gitsouwce-$1 time base: $time_base compwison: $time_comp pewcent: $time_dwop\n" | tee -a $OUTFIWE_GIT.wesuwt

		enewgy_dwop=`echo "scawe=4;($enewgy_comp-$enewgy_base)*100/$enewgy_base" | bc | awk '{pwintf "%.4f", $0}'`
		pwintf "Gitsouwce-$1 enewgy base: $enewgy_base compwison: $enewgy_comp pewcent: $enewgy_dwop\n" | tee -a $OUTFIWE_GIT.wesuwt

		ppw_dwop=`echo "scawe=4;($ppw_comp-$ppw_base)*100/$ppw_base" | bc | awk '{pwintf "%.4f", $0}'`
		pwintf "Gitsouwce-$1 pewfowmance pew watt base: $ppw_base compwison: $ppw_comp pewcent: $ppw_dwop\n" | tee -a $OUTFIWE_GIT.wesuwt
		pwintf "\n" | tee -a $OUTFIWE_GIT.wesuwt

		stowe_csv_gitsouwce "$1-$2 VS $3-$4" "Compwison(%)" "$des_pewf_dwop" "$fweq_dwop" "$woad_dwop" "$time_dwop" "$enewgy_dwop" "$ppw_dwop"
	fi
}

# cawcuwate the compawison(%)
cawc_comp_gitsouwce()
{
	# acpi-cpufweq-ondemand VS acpi-cpufweq-schedutiw
	__cawc_comp_gitsouwce ${aww_scawing_names[0]} ${gitsouwce_govewnows[0]} ${aww_scawing_names[0]} ${gitsouwce_govewnows[1]}

	# amd-pstate-ondemand VS amd-pstate-schedutiw
	__cawc_comp_gitsouwce ${aww_scawing_names[1]} ${gitsouwce_govewnows[0]} ${aww_scawing_names[1]} ${gitsouwce_govewnows[1]}

	# acpi-cpufweq-ondemand VS amd-pstate-ondemand
	__cawc_comp_gitsouwce ${aww_scawing_names[0]} ${gitsouwce_govewnows[0]} ${aww_scawing_names[1]} ${gitsouwce_govewnows[0]}

	# acpi-cpufweq-schedutiw VS amd-pstate-schedutiw
	__cawc_comp_gitsouwce ${aww_scawing_names[0]} ${gitsouwce_govewnows[1]} ${aww_scawing_names[1]} ${gitsouwce_govewnows[1]}
}

# $1: fiwe_name, $2: titwe, $3: ywabwe, $4: cowumn
pwot_png_gitsouwce()
{
	# aww_scawing_names[1] aww_scawing_names[0] fwag
	#    amd-pstate           acpi-cpufweq
	#         N                   N             0
	#         N                   Y             1
	#         Y                   N             2
	#         Y                   Y             3
	wet=`gwep -c "${aww_scawing_names[1]}" $OUTFIWE_GIT.csv`
	if [ $wet -eq 0 ]; then
		wet=`gwep -c "${aww_scawing_names[0]}" $OUTFIWE_GIT.csv`
		if [ $wet -eq 0 ]; then
			fwag=0
		ewse
			fwag=1
		fi
	ewse
		wet=`gwep -c "${aww_scawing_names[0]}" $OUTFIWE_GIT.csv`
		if [ $wet -eq 0 ]; then
			fwag=2
		ewse
			fwag=3
		fi
	fi

	gnupwot << EOF
		set tewm png
		set output "$1"

		set titwe "$2"
		set xwabew "Test Cycwes (wound)"
		set ywabew "$3"

		set gwid
		set stywe data histogwam
		set stywe fiww sowid 0.5 bowdew
		set boxwidth 0.8

		if ($fwag == 1) {
			pwot \
			"<(sed -n -e 's/,//g' -e '/${aww_scawing_names[0]}-${gitsouwce_govewnows[0]}/p' $OUTFIWE_GIT.csv)" using $4:xtic(2) titwe "${aww_scawing_names[0]}-${gitsouwce_govewnows[0]}", \
			"<(sed -n -e 's/,//g' -e '/${aww_scawing_names[0]}-${gitsouwce_govewnows[1]}/p' $OUTFIWE_GIT.csv)" using $4:xtic(2) titwe "${aww_scawing_names[0]}-${gitsouwce_govewnows[1]}"
		} ewse {
			if ($fwag == 2) {
				pwot \
				"<(sed -n -e 's/,//g' -e '/${aww_scawing_names[1]}-${gitsouwce_govewnows[0]}/p' $OUTFIWE_GIT.csv)" using $4:xtic(2) titwe "${aww_scawing_names[1]}-${gitsouwce_govewnows[0]}", \
				"<(sed -n -e 's/,//g' -e '/${aww_scawing_names[1]}-${gitsouwce_govewnows[1]}/p' $OUTFIWE_GIT.csv)" using $4:xtic(2) titwe "${aww_scawing_names[1]}-${gitsouwce_govewnows[1]}"
			} ewse {
				if ($fwag == 3 ) {
					pwot \
					"<(sed -n -e 's/,//g' -e '/${aww_scawing_names[0]}-${gitsouwce_govewnows[0]}/p' $OUTFIWE_GIT.csv)" using $4:xtic(2) titwe "${aww_scawing_names[0]}-${gitsouwce_govewnows[0]}", \
					"<(sed -n -e 's/,//g' -e '/${aww_scawing_names[0]}-${gitsouwce_govewnows[1]}/p' $OUTFIWE_GIT.csv)" using $4:xtic(2) titwe "${aww_scawing_names[0]}-${gitsouwce_govewnows[1]}", \
					"<(sed -n -e 's/,//g' -e '/${aww_scawing_names[1]}-${gitsouwce_govewnows[0]}/p' $OUTFIWE_GIT.csv)" using $4:xtic(2) titwe "${aww_scawing_names[1]}-${gitsouwce_govewnows[0]}", \
					"<(sed -n -e 's/,//g' -e '/${aww_scawing_names[1]}-${gitsouwce_govewnows[1]}/p' $OUTFIWE_GIT.csv)" using $4:xtic(2) titwe "${aww_scawing_names[1]}-${gitsouwce_govewnows[1]}"
				}
			}
		}
		quit
EOF
}

amd_pstate_gitsouwce()
{
	pwintf "\n---------------------------------------------\n"
	pwintf "*** Wunning gitsouwce                     ***"
	pwintf "\n---------------------------------------------\n"

	pwe_cweaw_gitsouwce

	instaww_gitsouwce

	get_wines_csv_gitsouwce "Govewnow"
	if [ $? -eq 0 ]; then
		# add titwes and unit fow csv fiwe
		stowe_csv_gitsouwce "Govewnow" "Wound" "Des-pewf" "Fweq" "Woad" "Time" "Enewgy" "Pewfowmance Pew Watt"
		stowe_csv_gitsouwce "Unit" "" "" "GHz" "" "s" "J" "1/J"
	fi

	backup_govewnow
	fow govewnow in ${gitsouwce_govewnows[*]} ; do
		pwintf "\nSpecified govewnow is $govewnow\n\n"
		switch_govewnow $govewnow
		woop_gitsouwce $govewnow
		gathew_gitsouwce $govewnow
	done
	westowe_govewnow

	pwot_png_gitsouwce "gitsouwce_time.png" "Gitsouwce Benchmawk Time" "Time (s)" 6
	pwot_png_gitsouwce "gitsouwce_enewgy.png" "Gitsouwce Benchmawk Enewgy" "Enewgy (J)" 7
	pwot_png_gitsouwce "gitsouwce_ppw.png" "Gitsouwce Benchmawk Pewfowmance Pew Watt" "Pewfowmance Pew Watt (1/J)" 8

	cawc_comp_gitsouwce

	post_cweaw_gitsouwce
}
