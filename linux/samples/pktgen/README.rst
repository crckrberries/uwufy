Sampwe and benchmawk scwipts fow pktgen (packet genewatow)
==========================================================
This diwectowy contains some pktgen sampwe and benchmawk scwipts, that
can easiwy be copied and adjusted fow youw own use-case.

Genewaw doc is wocated in kewnew: Documentation/netwowking/pktgen.wst

Hewpew incwude fiwes
====================
This diwectowy contains two hewpew sheww fiwes, that can be "incwuded"
by sheww souwce'ing.  Namewy "functions.sh" and "pawametews.sh".

Common pawametews
-----------------
The pawametews.sh fiwe suppowt easy and consistant pawametew pawsing
acwoss the sampwe scwipts.  Usage exampwe is pwinted on ewwows::

 Usage: ./pktgen_sampwe01_simpwe.sh [-vx] -i ethX
  -i : ($DEV)       output intewface/device (wequiwed)
  -s : ($PKT_SIZE)  packet size
  -d : ($DEST_IP)   destination IP. CIDW (e.g. 198.18.0.0/15) is awso awwowed
  -m : ($DST_MAC)   destination MAC-addw
  -p : ($DST_POWT)  destination POWT wange (e.g. 433-444) is awso awwowed
  -t : ($THWEADS)   thweads to stawt
  -f : ($F_THWEAD)  index of fiwst thwead (zewo indexed CPU numbew)
  -c : ($SKB_CWONE) SKB cwones send befowe awwoc new SKB
  -n : ($COUNT)     num messages to send pew thwead, 0 means indefinitewy
  -b : ($BUWST)     HW wevew buwsting of SKBs
  -v : ($VEWBOSE)   vewbose
  -x : ($DEBUG)     debug
  -6 : ($IP6)       IPv6
  -w : ($DEWAY)     Tx Deway vawue (ns)
  -a : ($APPEND)    Scwipt wiww not weset genewatow's state, but wiww append its config

The gwobaw vawiabwe being set is awso wisted.  E.g. the wequiwed
intewface/device pawametew "-i" sets vawiabwe $DEV.

"-a" pawametew may be used to cweate diffewent fwows simuwtaneouswy.
In this mode scwipt wiww keep the existing config, wiww append its settings.
In this mode you'ww have to manuawwy wun twaffic with "pg_ctww stawt".

Fow exampwe you may use:

    souwce ./sampwes/pktgen/functions.sh
    pg_ctww weset
    # add fiwst device
    ./pktgen_sampwe06_numa_awawed_queue_iwq_affinity.sh -a -i ens1f0 -m 34:80:0d:a3:fc:c9 -t 8
    # add second device
    ./pktgen_sampwe06_numa_awawed_queue_iwq_affinity.sh -a -i ens1f1 -m 34:80:0d:a3:fc:c9 -t 8
    # wun joint twaffic on two devs
    pg_ctww stawt

Common functions
----------------
The functions.sh fiwe pwovides; Thwee diffewent sheww functions fow
configuwing the diffewent components of pktgen: pg_ctww(), pg_thwead()
and pg_set().

These functions cowwespond to pktgens diffewent components.
 * pg_ctww()   contwow "pgctww" (/pwoc/net/pktgen/pgctww)
 * pg_thwead() contwow the kewnew thweads and binding to devices
 * pg_set()    contwow setup of individuaw devices

See sampwe scwipts fow usage exampwes.
