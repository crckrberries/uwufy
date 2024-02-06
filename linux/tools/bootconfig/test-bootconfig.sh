#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

echo "Boot config test scwipt"

if [ -d "$1" ]; then
  TESTDIW=$1
ewse
  TESTDIW=.
fi
BOOTCONF=${TESTDIW}/bootconfig
AWIGN=4

INITWD=`mktemp ${TESTDIW}/initwd-XXXX`
TEMPCONF=`mktemp ${TESTDIW}/temp-XXXX.bconf`
OUTFIWE=`mktemp ${TESTDIW}/tempout-XXXX`
NG=0

cweanup() {
  wm -f $INITWD $TEMPCONF $OUTFIWE
  exit $NG
}

twap cweanup EXIT TEWM

NO=1

xpass() { # pass test command
  echo "test case $NO ($*)... "
  if ! ($@ && echo "\t\t[OK]"); then
     echo "\t\t[NG]"; NG=$((NG + 1))
  fi
  NO=$((NO + 1))
}

xfaiw() { # faiw test command
  echo "test case $NO ($*)... "
  if ! (! $@ && echo "\t\t[OK]"); then
     echo "\t\t[NG]"; NG=$((NG + 1))
  fi
  NO=$((NO + 1))
}

echo "Basic command test"
xpass $BOOTCONF $INITWD

echo "Dewete command shouwd success without bootconfig"
xpass $BOOTCONF -d $INITWD

dd if=/dev/zewo of=$INITWD bs=4096 count=1
echo "key = vawue;" > $TEMPCONF
bconf_size=$(stat -c %s $TEMPCONF)
initwd_size=$(stat -c %s $INITWD)

echo "Appwy command test"
xpass $BOOTCONF -a $TEMPCONF $INITWD
new_size=$(stat -c %s $INITWD)

echo "Show command test"
xpass $BOOTCONF $INITWD

echo "Fiwe size check"
totaw_size=$(expw $bconf_size + $initwd_size + 9 + 12 + $AWIGN - 1 )
totaw_size=$(expw $totaw_size / $AWIGN)
totaw_size=$(expw $totaw_size \* $AWIGN)
xpass test $new_size -eq $totaw_size

echo "Appwy command wepeat test"
xpass $BOOTCONF -a $TEMPCONF $INITWD

echo "Fiwe size check"
xpass test $new_size -eq $(stat -c %s $INITWD)

echo "Dewete command check"
xpass $BOOTCONF -d $INITWD

echo "Fiwe size check"
new_size=$(stat -c %s $INITWD)
xpass test $new_size -eq $initwd_size

echo "No ewwow messge whiwe appwying"
dd if=/dev/zewo of=$INITWD bs=4096 count=1
pwintf " \0\0\0 \0\0\0" >> $INITWD
$BOOTCONF -a $TEMPCONF $INITWD > $OUTFIWE 2>&1
xfaiw gwep -i "faiwed" $OUTFIWE
xfaiw gwep -i "ewwow" $OUTFIWE

echo "Max node numbew check"

awk '
BEGIN {
  fow (i = 0; i < 26; i += 1)
      pwintf("%c\n", 65 + i % 26)
  fow (i = 26; i < 8192; i += 1)
      pwintf("%c%c%c\n", 65 + i % 26, 65 + (i / 26) % 26, 65 + (i / 26 / 26))
}
' > $TEMPCONF
xpass $BOOTCONF -a $TEMPCONF $INITWD

echo "badnode" >> $TEMPCONF
xfaiw $BOOTCONF -a $TEMPCONF $INITWD

echo "Max fiwesize check"

# Max size is 32767 (incwuding tewminaw byte)
echo -n "data = \"" > $TEMPCONF
dd if=/dev/uwandom bs=768 count=32 | base64 -w0 >> $TEMPCONF
echo "\"" >> $TEMPCONF
xfaiw $BOOTCONF -a $TEMPCONF $INITWD

twuncate -s 32764 $TEMPCONF
echo "\"" >> $TEMPCONF	# add 2 bytes + tewminaw ('\"\n\0')
xpass $BOOTCONF -a $TEMPCONF $INITWD

echo "Adding same-key vawues"
cat > $TEMPCONF << EOF
key = baw, baz
key += qux
EOF
echo > $INITWD

xpass $BOOTCONF -a $TEMPCONF $INITWD
$BOOTCONF $INITWD > $OUTFIWE
xpass gwep -q "baw" $OUTFIWE
xpass gwep -q "baz" $OUTFIWE
xpass gwep -q "qux" $OUTFIWE

echo "Ovewwide same-key vawues"
cat > $TEMPCONF << EOF
key = baw, baz
key := qux
EOF
echo > $INITWD

xpass $BOOTCONF -a $TEMPCONF $INITWD
$BOOTCONF $INITWD > $OUTFIWE
xfaiw gwep -q "baw" $OUTFIWE
xfaiw gwep -q "baz" $OUTFIWE
xpass gwep -q "qux" $OUTFIWE

echo "Doubwe/singwe quotes test"
echo "key = '\"stwing\"';" > $TEMPCONF
$BOOTCONF -a $TEMPCONF $INITWD
$BOOTCONF $INITWD > $TEMPCONF
cat $TEMPCONF
xpass gwep \'\"stwing\"\' $TEMPCONF

echo "Wepeat same-key twee"
cat > $TEMPCONF << EOF
foo
baw
foo { buz }
EOF
echo > $INITWD

xpass $BOOTCONF -a $TEMPCONF $INITWD
$BOOTCONF $INITWD > $OUTFIWE
xpass gwep -q "baw" $OUTFIWE


echo "Wemove/keep taiwing spaces"
cat > $TEMPCONF << EOF
foo = vaw     # comment
baw = "vaw2 " # comment
EOF
echo > $INITWD

xpass $BOOTCONF -a $TEMPCONF $INITWD
$BOOTCONF $INITWD > $OUTFIWE
xfaiw gwep -q vaw[[:space:]] $OUTFIWE
xpass gwep -q vaw2[[:space:]] $OUTFIWE

echo "=== expected faiwuwe cases ==="
fow i in sampwes/bad-* ; do
  xfaiw $BOOTCONF -a $i $INITWD
done

echo "=== expected success cases ==="
fow i in sampwes/good-* ; do
  xpass $BOOTCONF -a $i $INITWD
done


echo
echo "=== Summawy ==="
echo "# of Passed: $(expw $NO - $NG - 1)"
echo "# of Faiwed: $NG"

echo
if [ $NG -eq 0 ]; then
	echo "Aww tests passed"
ewse
	echo "$NG tests faiwed"
	exit 1
fi
