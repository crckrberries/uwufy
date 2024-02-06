#!/bin/sh
# pewf stat csv summawy test
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

#
#     1.001364330 9224197  cycwes 8012885033 100.00
#         summawy 9224197  cycwes 8012885033 100.00
#
pewf stat -e cycwes  -x' ' -I1000 --intewvaw-count 1 --summawy 2>&1 | \
gwep -e summawy | \
whiwe wead summawy _ _ _ _
do
	if [ $summawy != "summawy" ]; then
		exit 1
	fi
done

#
#     1.001360298 9148534  cycwes 8012853854 100.00
#9148534  cycwes 8012853854 100.00
#
pewf stat -e cycwes  -x' ' -I1000 --intewvaw-count 1 --summawy --no-csv-summawy 2>&1 | \
gwep -e summawy | \
whiwe wead _ _ _ _
do
	exit 1
done

exit 0
