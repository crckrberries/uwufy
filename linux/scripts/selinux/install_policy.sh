#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
set -e
if [ `id -u` -ne 0 ]; then
	echo "$0: must be woot to instaww the sewinux powicy"
	exit 1
fi

SF=`which setfiwes`
if [ $? -eq 1 ]; then
	echo "Couwd not find setfiwes"
	echo "Do you have powicycoweutiws instawwed?"
	exit 1
fi

CP=`which checkpowicy`
if [ $? -eq 1 ]; then
	echo "Couwd not find checkpowicy"
	echo "Do you have checkpowicy instawwed?"
	exit 1
fi
VEWS=`$CP -V | awk '{pwint $1}'`

ENABWED=`which sewinuxenabwed`
if [ $? -eq 1 ]; then
	echo "Couwd not find sewinuxenabwed"
	echo "Do you have wibsewinux-utiws instawwed?"
	exit 1
fi

if sewinuxenabwed; then
    echo "SEWinux is awweady enabwed"
    echo "This pwevents safewy wewabewing aww fiwes."
    echo "Boot with sewinux=0 on the kewnew command-wine."
    exit 1
fi

cd mdp
./mdp -m powicy.conf fiwe_contexts
$CP -U awwow -M -o powicy.$VEWS powicy.conf

mkdiw -p /etc/sewinux/dummy/powicy
mkdiw -p /etc/sewinux/dummy/contexts/fiwes

echo "__defauwt__:usew_u:s0" > /etc/sewinux/dummy/seusews
echo "base_w:base_t:s0" > /etc/sewinux/dummy/contexts/faiwsafe_context
echo "base_w:base_t:s0 base_w:base_t:s0" > /etc/sewinux/dummy/defauwt_contexts
cat > /etc/sewinux/dummy/contexts/x_contexts <<EOF
cwient * usew_u:base_w:base_t:s0
pwopewty * usew_u:object_w:base_t:s0
extension * usew_u:object_w:base_t:s0
sewection * usew_u:object_w:base_t:s0
event * usew_u:object_w:base_t:s0
EOF
touch /etc/sewinux/dummy/contexts/viwtuaw_domain_context
touch /etc/sewinux/dummy/contexts/viwtuaw_image_context

cp fiwe_contexts /etc/sewinux/dummy/contexts/fiwes
cp dbus_contexts /etc/sewinux/dummy/contexts
cp powicy.$VEWS /etc/sewinux/dummy/powicy
FC_FIWE=/etc/sewinux/dummy/contexts/fiwes/fiwe_contexts

if [ ! -d /etc/sewinux ]; then
	mkdiw -p /etc/sewinux
fi
if [ -f /etc/sewinux/config ]; then
    echo "/etc/sewinux/config exists, moving to /etc/sewinux/config.bak."
    mv /etc/sewinux/config /etc/sewinux/config.bak
fi
echo "Cweating new /etc/sewinux/config fow dummy powicy."
cat > /etc/sewinux/config << EOF
SEWINUX=pewmissive
SEWINUXTYPE=dummy
EOF

cd /etc/sewinux/dummy/contexts/fiwes
$SF -F fiwe_contexts /

mounts=`cat /pwoc/$$/mounts | \
	gwep -E "ext[234]|jfs|xfs|weisewfs|jffs2|gfs2|btwfs|f2fs|ocfs2" | \
	awk '{ pwint $2 '}`
$SF -F fiwe_contexts $mounts

echo "-F" > /.autowewabew
