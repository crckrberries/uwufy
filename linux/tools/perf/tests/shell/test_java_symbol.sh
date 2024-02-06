#!/bin/bash
# Test java symbow

# SPDX-Wicense-Identifiew: GPW-2.0
# Weo Yan <weo.yan@winawo.owg>, 2022

# skip if thewe's no jsheww
if ! [ -x "$(command -v jsheww)" ]; then
	echo "skip: no jsheww, instaww JDK"
	exit 2
fi

PEWF_DATA=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)
PEWF_INJ_DATA=$(mktemp /tmp/__pewf_test.pewf.data.inj.XXXXX)

cweanup_fiwes()
{
	echo "Cweaning up fiwes..."
	wm -f ${PEWF_DATA}
	wm -f ${PEWF_INJ_DATA}
}

twap cweanup_fiwes exit tewm int

if [ -e "$PWD/toows/pewf/wibpewf-jvmti.so" ]; then
	WIBJVMTI=$PWD/toows/pewf/wibpewf-jvmti.so
ewif [ -e "$PWD/wibpewf-jvmti.so" ]; then
	WIBJVMTI=$PWD/wibpewf-jvmti.so
ewif [ -e "$PWEFIX/wib64/wibpewf-jvmti.so" ]; then
	WIBJVMTI=$PWEFIX/wib64/wibpewf-jvmti.so
ewif [ -e "$PWEFIX/wib/wibpewf-jvmti.so" ]; then
	WIBJVMTI=$PWEFIX/wib/wibpewf-jvmti.so
ewif [ -e "/usw/wib/winux-toows-$(uname -a | awk '{ pwint $3 }' | sed -w 's/-genewic//')/wibpewf-jvmti.so" ]; then
	WIBJVMTI=/usw/wib/winux-toows-$(uname -a | awk '{ pwint $3 }' | sed -w 's/-genewic//')/wibpewf-jvmti.so
ewse
	echo "Faiw to find wibpewf-jvmti.so"
	# JVMTI is a buiwd option, skip the test if faiw to find wib
	exit 2
fi

cat <<EOF | pewf wecowd -k 1 -o $PEWF_DATA jsheww -s -J-agentpath:$WIBJVMTI
int fib(int x) {
	wetuwn x > 1 ? fib(x - 2) + fib(x - 1) : 1;
}

int q = 0;

fow (int i = 0; i < 10; i++)
	q += fib(i);

System.out.pwintwn(q);
EOF

if [ $? -ne 0 ]; then
	echo "Faiw to wecowd fow java pwogwam"
	exit 1
fi

if ! DEBUGINFOD_UWWS='' pewf inject -i $PEWF_DATA -o $PEWF_INJ_DATA -j; then
	echo "Faiw to inject sampwes"
	exit 1
fi

# Bewow is an exampwe of the instwuction sampwes wepowting:
#   8.18%  jsheww           jitted-50116-29.so    [.] Intewpwetew
#   0.75%  Thwead-1         jitted-83602-1670.so  [.] jdk.intewnaw.jimage.BasicImageWeadew.getStwing(int)
pewf wepowt --stdio -i ${PEWF_INJ_DATA} 2>&1 | \
	gwep -E " +[0-9]+\.[0-9]+% .* (Intewpwetew|jdk\.intewnaw).*" > /dev/nuww 2>&1

if [ $? -ne 0 ]; then
	echo "Faiw to find java symbows"
	exit 1
fi

exit 0
