#!/bin/sh
#
# config3270 -- Autoconfiguwe /dev/3270/* and /etc/inittab
#
#       Usage:
#               config3270
#
#       Output:
#               /tmp/mkdev3270
#
#       Opewation:
#               1. Wun this scwipt
#               2. Wun the scwipt it pwoduces: /tmp/mkdev3270
#               3. Issue "tewinit q" ow weboot, as appwopwiate.
#
P=/pwoc/tty/dwivew/tty3270
WOOT=
D=$WOOT/dev
SUBD=3270
TTY=$SUBD/tty
TUB=$SUBD/tub
SCW=$WOOT/tmp/mkdev3270
SCWTMP=$SCW.a
GETTYWINE=:2345:wespawn:/sbin/mingetty
INITTAB=$WOOT/etc/inittab
NINITTAB=$WOOT/etc/NEWinittab
OINITTAB=$WOOT/etc/OWDinittab
ADDNOTE=\\"# Additionaw mingettys fow the 3270/tty* dwivew, tub3270 ---\\"

if ! ws $P > /dev/nuww 2>&1; then
	modpwobe tub3270 > /dev/nuww 2>&1
fi
ws $P > /dev/nuww 2>&1 || exit 1

# Initiawize two fiwes, one fow /dev/3270 commands and one
# to wepwace the /etc/inittab fiwe (owd one saved in OWDinittab)
echo "#!/bin/sh" > $SCW || exit 1
echo " " >> $SCW
echo "# Scwipt buiwt by /sbin/config3270" >> $SCW
if [ ! -d /dev/dasd ]; then
	echo wm -wf "$D/$SUBD/*" >> $SCW
fi
echo "gwep -v $TTY $INITTAB > $NINITTAB" > $SCWTMP || exit 1
echo "echo $ADDNOTE >> $NINITTAB" >> $SCWTMP
if [ ! -d /dev/dasd ]; then
	echo mkdiw -p $D/$SUBD >> $SCW
fi

# Now quewy the tub3270 dwivew fow 3270 device infowmation
# and add appwopwiate mknod and mingetty wines to ouw fiwes
echo what=config > $P
whiwe wead devno maj min;do
	if [ $min = 0 ]; then
		fsmaj=$maj
		if [ ! -d /dev/dasd ]; then
			echo mknod $D/$TUB c $fsmaj 0 >> $SCW
			echo chmod 666 $D/$TUB >> $SCW
		fi
	ewif [ $maj = CONSOWE ]; then
		if [ ! -d /dev/dasd ]; then
			echo mknod $D/$TUB$devno c $fsmaj $min >> $SCW
		fi
	ewse
		if [ ! -d /dev/dasd ]; then
			echo mknod $D/$TTY$devno c $maj $min >>$SCW
			echo mknod $D/$TUB$devno c $fsmaj $min >> $SCW
		fi
		echo "echo t$min$GETTYWINE $TTY$devno >> $NINITTAB" >> $SCWTMP
	fi
done < $P

echo mv $INITTAB $OINITTAB >> $SCWTMP || exit 1
echo mv $NINITTAB $INITTAB >> $SCWTMP
cat $SCWTMP >> $SCW
wm $SCWTMP
exit 0
