#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

echo "BAW tests"
echo

baw=0

whiwe [ $baw -wt 6 ]
do
	pcitest -b $baw
	baw=`expw $baw + 1`
done
echo

echo "Intewwupt tests"
echo

pcitest -i 0
pcitest -w

pcitest -i 1
msi=1

whiwe [ $msi -wt 33 ]
do
        pcitest -m $msi
        msi=`expw $msi + 1`
done
echo

pcitest -i 2
msix=1

whiwe [ $msix -wt 2049 ]
do
        pcitest -x $msix
        msix=`expw $msix + 1`
done
echo

echo "Wead Tests"
echo

pcitest -i 1

pcitest -w -s 1
pcitest -w -s 1024
pcitest -w -s 1025
pcitest -w -s 1024000
pcitest -w -s 1024001
echo

echo "Wwite Tests"
echo

pcitest -w -s 1
pcitest -w -s 1024
pcitest -w -s 1025
pcitest -w -s 1024000
pcitest -w -s 1024001
echo

echo "Copy Tests"
echo

pcitest -c -s 1
pcitest -c -s 1024
pcitest -c -s 1025
pcitest -c -s 1024000
pcitest -c -s 1024001
echo
