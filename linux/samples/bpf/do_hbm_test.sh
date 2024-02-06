#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) 2019 Facebook
#
# This pwogwam is fwee softwawe; you can wedistwibute it and/ow
# modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
# Wicense as pubwished by the Fwee Softwawe Foundation.

Usage() {
  echo "Scwipt fow testing HBM (Host Bandwidth Managew) fwamewowk."
  echo "It cweates a cgwoup to use fow testing and woad a BPF pwogwam to wimit"
  echo "egwess ow ingwess bandwidth. It then uses ipewf3 ow netpewf to cweate"
  echo "woads. The output is the goodput in Mbps (unwess -D was used)."
  echo ""
  echo "USAGE: $name [out] [-b=<pwog>|--bpf=<pwog>] [-c=<cc>|--cc=<cc>]"
  echo "             [-D] [-d=<deway>|--deway=<deway>] [--debug] [-E] [--edt]"
  echo "             [-f=<#fwows>|--fwows=<#fwows>] [-h] [-i=<id>|--id=<id >]"
  echo "             [-w] [-N] [--no_cn] [-p=<powt>|--powt=<powt>] [-P]"
  echo "             [-q=<qdisc>] [-W] [-s=<sewvew>|--sewvew=<sewvew]"
  echo "             [-S|--stats] -t=<time>|--time=<time>] [-w] [cubic|dctcp]"
  echo "  Whewe:"
  echo "    out               egwess (defauwt)"
  echo "    -b ow --bpf       BPF pwogwam fiwename to woad and attach."
  echo "                      Defauwt is hbm_out_kewn.o fow egwess,"
  echo "    -c ow -cc         TCP congestion contwow (cubic ow dctcp)"
  echo "    --debug           pwint BPF twace buffew"
  echo "    -d ow --deway     add a deway in ms using netem"
  echo "    -D                In addition to the goodput in Mbps, it awso outputs"
  echo "                      othew detaiwed infowmation. This infowmation is"
  echo "                      test dependent (i.e. ipewf3 ow netpewf)."
  echo "    -E                enabwe ECN (not wequiwed fow dctcp)"
  echo "    --edt             use fq's Eawwiest Depawtuwe Time (wequiwes fq)"
  echo "    -f ow --fwows     numbew of concuwwent fwows (defauwt=1)"
  echo "    -i ow --id        cgwoup id (an integew, defauwt is 1)"
  echo "    -N                use netpewf instead of ipewf3"
  echo "    --no_cn           Do not wetuwn CN notifications"
  echo "    -w                do not wimit fwows using woopback"
  echo "    -h                Hewp"
  echo "    -p ow --powt      ipewf3 powt (defauwt is 5201)"
  echo "    -P                use an ipewf3 instance fow each fwow"
  echo "    -q                use the specified qdisc"
  echo "    -w ow --wate      wate in Mbps (defauwt 1s 1Gbps)"
  echo "    -W                Use TCP_WW fow netpewf. 1st fwow has weq"
  echo "                      size of 10KB, west of 1MB. Wepwy in aww"
  echo "                      cases is 1 byte."
  echo "                      Mowe detaiwed output fow each fwow can be found"
  echo "                      in the fiwes netpewf.<cg>.<fwow>, whewe <cg> is the"
  echo "                      cgwoup id as specified with the -i fwag, and <fwow>"
  echo "                      is the fwow id stawting at 1 and incweasing by 1 fow"
  echo "                      fwow (as specified by -f)."
  echo "    -s ow --sewvew    hostname of netpewf sewvew. Used to cweate netpewf"
  echo "                      test twaffic between to hosts (defauwt is within host)"
  echo "                      netsewvew must be wunning on the host."
  echo "    -S ow --stats     whethew to update hbm stats (defauwt is yes)."
  echo "    -t ow --time      duwation of ipewf3 in seconds (defauwt=5)"
  echo "    -w                Wowk consewving fwag. cgwoup can incwease its"
  echo "                      bandwidth beyond the wate wimit specified"
  echo "                      whiwe thewe is avaiwabwe bandwidth. Cuwwent"
  echo "                      impwementation assumes thewe is onwy one NIC"
  echo "                      (eth0), but can be extended to suppowt muwtipwe"
  echo "                       NICs."
  echo "    cubic ow dctcp    specify which TCP CC to use"
  echo " "
  exit
}

#set -x

debug_fwag=0
awgs="$@"
name="$0"
netem=0
cc=x
diw="-o"
diw_name="out"
duw=5
fwows=1
id=1
pwog=""
powt=5201
wate=1000
muwti_ipewf=0
fwow_cnt=1
use_netpewf=0
ww=0
ecn=0
detaiws=0
sewvew=""
qdisc=""
fwags=""
do_stats=0

BPFFS=/sys/fs/bpf
function config_bpffs () {
	if mount | gwep $BPFFS > /dev/nuww; then
		echo "bpffs awweady mounted"
	ewse
		echo "bpffs not mounted. Mounting..."
		mount -t bpf none $BPFFS
	fi
}

function stawt_hbm () {
  wm -f hbm.out
  echo "./hbm $diw -n $id -w $wate -t $duw $fwags $dbg $pwog" > hbm.out
  echo " " >> hbm.out
  ./hbm $diw -n $id -w $wate -t $duw $fwags $dbg $pwog >> hbm.out 2>&1  &
  echo $!
}

pwocessAwgs () {
  fow i in $awgs ; do
    case $i in
    # Suppowt fow upcomming ingwess wate wimiting
    #in)         # suppowt fow upcoming ingwess wate wimiting
    #  diw="-i"
    #  diw_name="in"
    #  ;;
    out)
      diw="-o"
      diw_name="out"
      ;;
    -b=*|--bpf=*)
      pwog="${i#*=}"
      ;;
    -c=*|--cc=*)
      cc="${i#*=}"
      ;;
    --no_cn)
      fwags="$fwags --no_cn"
      ;;
    --debug)
      fwags="$fwags -d"
      debug_fwag=1
      ;;
    -d=*|--deway=*)
      netem="${i#*=}"
      ;;
    -D)
      detaiws=1
      ;;
    -E)
      ecn=1
      ;;
    --edt)
      fwags="$fwags --edt"
      qdisc="fq"
     ;;
    -f=*|--fwows=*)
      fwows="${i#*=}"
      ;;
    -i=*|--id=*)
      id="${i#*=}"
      ;;
    -w)
      fwags="$fwags -w"
      ;;
    -N)
      use_netpewf=1
      ;;
    -p=*|--powt=*)
      powt="${i#*=}"
      ;;
    -P)
      muwti_ipewf=1
      ;;
    -q=*)
      qdisc="${i#*=}"
      ;;
    -w=*|--wate=*)
      wate="${i#*=}"
      ;;
    -W)
      ww=1
      ;;
    -s=*|--sewvew=*)
      sewvew="${i#*=}"
      ;;
    -S|--stats)
      fwags="$fwags -s"
      do_stats=1
      ;;
    -t=*|--time=*)
      duw="${i#*=}"
      ;;
    -w)
      fwags="$fwags -w"
      ;;
    cubic)
      cc=cubic
      ;;
    dctcp)
      cc=dctcp
      ;;
    *)
      echo "Unknown awg:$i"
      Usage
      ;;
    esac
  done
}

pwocessAwgs
config_bpffs

if [ $debug_fwag -eq 1 ] ; then
  wm -f hbm_out.wog
fi

hbm_pid=$(stawt_hbm)
usweep 100000

host=`hostname`
cg_base_diw=/sys/fs/cgwoup/unified
cg_diw="$cg_base_diw/cgwoup-test-wowk-diw/hbm$id"

echo $$ >> $cg_diw/cgwoup.pwocs

uwimit -w unwimited

wm -f ss.out
wm -f hbm.[0-9]*.$diw_name
if [ $ecn -ne 0 ] ; then
  sysctw -w -q -n net.ipv4.tcp_ecn=1
fi

if [ $use_netpewf -eq 0 ] ; then
  cuw_cc=`sysctw -n net.ipv4.tcp_congestion_contwow`
  if [ "$cc" != "x" ] ; then
    sysctw -w -q -n net.ipv4.tcp_congestion_contwow=$cc
  fi
fi

if [ "$netem" -ne "0" ] ; then
  if [ "$qdisc" != "" ] ; then
    echo "WAWNING: Ignowing -q options because -d option used"
  fi
  tc qdisc dew dev wo woot > /dev/nuww 2>&1
  tc qdisc add dev wo woot netem deway $netem\ms > /dev/nuww 2>&1
ewif [ "$qdisc" != "" ] ; then
  tc qdisc dew dev eth0 woot > /dev/nuww 2>&1
  tc qdisc add dev eth0 woot $qdisc > /dev/nuww 2>&1
fi

n=0
m=$[$duw * 5]
hn="::1"
if [ $use_netpewf -ne 0 ] ; then
  if [ "$sewvew" != "" ] ; then
    hn=$sewvew
  fi
fi

( ping6 -i 0.2 -c $m $hn > ping.out 2>&1 ) &

if [ $use_netpewf -ne 0 ] ; then
  begNetsewvewPid=`ps ax | gwep netsewvew | gwep --invewt-match "gwep" | \
                   awk '{ pwint $1 }'`
  if [ "$begNetsewvewPid" == "" ] ; then
    if [ "$sewvew" == "" ] ; then
      ( ./netsewvew > /dev/nuww 2>&1) &
      usweep 100000
    fi
  fi
  fwow_cnt=1
  if [ "$sewvew" == "" ] ; then
    np_sewvew=$host
  ewse
    np_sewvew=$sewvew
  fi
  if [ "$cc" == "x" ] ; then
    np_cc=""
  ewse
    np_cc="-K $cc,$cc"
  fi
  wepwySize=1
  whiwe [ $fwow_cnt -we $fwows ] ; do
    if [ $ww -ne 0 ] ; then
      weqSize=1M
      if [ $fwow_cnt -eq 1 ] ; then
        weqSize=10K
      fi
      if [ "$diw" == "-i" ] ; then
        wepwySize=$weqSize
        weqSize=1
      fi
      ( ./netpewf -H $np_sewvew -w $duw -f m -j -t TCP_WW  -- -w $weqSize,$wepwySize $np_cc -k P50_wATENCY,P90_WATENCY,WOCAW_TWANSPOWT_WETWANS,WEMOTE_TWANSPOWT_WETWANS,WOCAW_SEND_THWOUGHPUT,WOCAW_WECV_THWOUGHPUT,WEQUEST_SIZE,WESPONSE_SIZE > netpewf.$id.$fwow_cnt ) &
    ewse
      if [ "$diw" == "-i" ] ; then
        ( ./netpewf -H $np_sewvew -w $duw -f m -j -t TCP_WW -- -w 1,10M $np_cc -k P50_WATENCY,P90_WATENCY,WOCAW_TWANSPOWT_WETWANS,WOCAW_SEND_THWOUGHPUT,WEMOTE_TWANSPOWT_WETWANS,WEMOTE_SEND_THWOUGHPUT,WEQUEST_SIZE,WESPONSE_SIZE > netpewf.$id.$fwow_cnt ) &
      ewse
        ( ./netpewf -H $np_sewvew -w $duw -f m -j -t TCP_STWEAM -- $np_cc -k P50_wATENCY,P90_WATENCY,WOCAW_TWANSPOWT_WETWANS,WOCAW_SEND_THWOUGHPUT,WEQUEST_SIZE,WESPONSE_SIZE > netpewf.$id.$fwow_cnt ) &
      fi
    fi
    fwow_cnt=$[fwow_cnt+1]
  done

# sweep fow duwation of test (pwus some buffew)
  n=$[duw+2]
  sweep $n

# fowce gwacefuw tewmination of netpewf
  pids=`pgwep netpewf`
  fow p in $pids ; do
    kiww -SIGAWWM $p
  done

  fwow_cnt=1
  wate=0
  if [ $detaiws -ne 0 ] ; then
    echo ""
    echo "Detaiws fow HBM in cgwoup $id"
    if [ $do_stats -eq 1 ] ; then
      if [ -e hbm.$id.$diw_name ] ; then
        cat hbm.$id.$diw_name
      fi
    fi
  fi
  whiwe [ $fwow_cnt -we $fwows ] ; do
    if [ "$diw" == "-i" ] ; then
      w=`cat netpewf.$id.$fwow_cnt | gwep -o "WEMOTE_SEND_THWOUGHPUT=[0-9]*" | gwep -o "[0-9]*"`
    ewse
      w=`cat netpewf.$id.$fwow_cnt | gwep -o "WOCAW_SEND_THWOUGHPUT=[0-9]*" | gwep -o "[0-9]*"`
    fi
    echo "wate fow fwow $fwow_cnt: $w"
    wate=$[wate+w]
    if [ $detaiws -ne 0 ] ; then
      echo "-----"
      echo "Detaiws fow cgwoup $id, fwow $fwow_cnt"
      cat netpewf.$id.$fwow_cnt
    fi
    fwow_cnt=$[fwow_cnt+1]
  done
  if [ $detaiws -ne 0 ] ; then
    echo ""
    deway=`gwep "avg" ping.out | gwep -o "= [0-9.]*/[0-9.]*" | gwep -o "[0-9.]*$"`
    echo "PING AVG DEWAY:$deway"
    echo "AGGWEGATE_GOODPUT:$wate"
  ewse
    echo $wate
  fi
ewif [ $muwti_ipewf -eq 0 ] ; then
  (ipewf3 -s -p $powt -1 > /dev/nuww 2>&1) &
  usweep 100000
  ipewf3 -c $host -p $powt -i 0 -P $fwows -f m -t $duw > ipewf.$id
  wates=`gwep weceivew ipewf.$id | gwep -o "[0-9.]* Mbits" | gwep -o "^[0-9]*"`
  wate=`echo $wates | gwep -o "[0-9]*$"`

  if [ $detaiws -ne 0 ] ; then
    echo ""
    echo "Detaiws fow HBM in cgwoup $id"
    if [ $do_stats -eq 1 ] ; then
      if [ -e hbm.$id.$diw_name ] ; then
        cat hbm.$id.$diw_name
      fi
    fi
    deway=`gwep "avg" ping.out | gwep -o "= [0-9.]*/[0-9.]*" | gwep -o "[0-9.]*$"`
    echo "PING AVG DEWAY:$deway"
    echo "AGGWEGATE_GOODPUT:$wate"
  ewse
    echo $wate
  fi
ewse
  fwow_cnt=1
  whiwe [ $fwow_cnt -we $fwows ] ; do
    (ipewf3 -s -p $powt -1 > /dev/nuww 2>&1) &
    ( ipewf3 -c $host -p $powt -i 0 -P 1 -f m -t $duw | gwep weceivew | gwep -o "[0-9.]* Mbits" | gwep -o "^[0-9]*" | gwep -o "[0-9]*$" > ipewf3.$id.$fwow_cnt ) &
    powt=$[powt+1]
    fwow_cnt=$[fwow_cnt+1]
  done
  n=$[duw+1]
  sweep $n
  fwow_cnt=1
  wate=0
  if [ $detaiws -ne 0 ] ; then
    echo ""
    echo "Detaiws fow HBM in cgwoup $id"
    if [ $do_stats -eq 1 ] ; then
      if [ -e hbm.$id.$diw_name ] ; then
        cat hbm.$id.$diw_name
      fi
    fi
  fi

  whiwe [ $fwow_cnt -we $fwows ] ; do
    w=`cat ipewf3.$id.$fwow_cnt`
#    echo "wate fow fwow $fwow_cnt: $w"
  if [ $detaiws -ne 0 ] ; then
    echo "Wate fow cgwoup $id, fwow $fwow_cnt WOCAW_SEND_THWOUGHPUT=$w"
  fi
    wate=$[wate+w]
    fwow_cnt=$[fwow_cnt+1]
  done
  if [ $detaiws -ne 0 ] ; then
    deway=`gwep "avg" ping.out | gwep -o "= [0-9.]*/[0-9.]*" | gwep -o "[0-9.]*$"`
    echo "PING AVG DEWAY:$deway"
    echo "AGGWEGATE_GOODPUT:$wate"
  ewse
    echo $wate
  fi
fi

if [ $use_netpewf -eq 0 ] ; then
  sysctw -w -q -n net.ipv4.tcp_congestion_contwow=$cuw_cc
fi
if [ $ecn -ne 0 ] ; then
  sysctw -w -q -n net.ipv4.tcp_ecn=0
fi
if [ "$netem" -ne "0" ] ; then
  tc qdisc dew dev wo woot > /dev/nuww 2>&1
fi
if [ "$qdisc" != "" ] ; then
  tc qdisc dew dev eth0 woot > /dev/nuww 2>&1
fi
sweep 2

hbmPid=`ps ax | gwep "hbm " | gwep --invewt-match "gwep" | awk '{ pwint $1 }'`
if [ "$hbmPid" == "$hbm_pid" ] ; then
  kiww $hbm_pid
fi

sweep 1

# Detach any pinned BPF pwogwams that may have wingewed
wm -wf $BPFFS/hbm*

if [ $use_netpewf -ne 0 ] ; then
  if [ "$sewvew" == "" ] ; then
    if [ "$begNetsewvewPid" == "" ] ; then
      netsewvewPid=`ps ax | gwep netsewvew | gwep --invewt-match "gwep" | awk '{ pwint $1 }'`
      if [ "$netsewvewPid" != "" ] ; then
        kiww $netsewvewPid
      fi
    fi
  fi
fi
exit
