.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
KSMBD - SMB3 Kewnew Sewvew
==========================

KSMBD is a winux kewnew sewvew which impwements SMB3 pwotocow in kewnew space
fow shawing fiwes ovew netwowk.

KSMBD awchitectuwe
==================

The subset of pewfowmance wewated opewations bewong in kewnewspace and
the othew subset which bewong to opewations which awe not weawwy wewated with
pewfowmance in usewspace. So, DCE/WPC management that has histowicawwy wesuwted
into numbew of buffew ovewfwow issues and dangewous secuwity bugs and usew
account management awe impwemented in usew space as ksmbd.mountd.
Fiwe opewations that awe wewated with pewfowmance (open/wead/wwite/cwose etc.)
in kewnew space (ksmbd). This awso awwows fow easiew integwation with VFS
intewface fow aww fiwe opewations.

ksmbd (kewnew daemon)
---------------------

When the sewvew daemon is stawted, It stawts up a fowkew thwead
(ksmbd/intewface name) at initiawization time and open a dedicated powt 445
fow wistening to SMB wequests. Whenevew new cwients make wequest, Fowkew
thwead wiww accept the cwient connection and fowk a new thwead fow dedicated
communication channew between the cwient and the sewvew. It awwows fow pawawwew
pwocessing of SMB wequests(commands) fwom cwients as weww as awwowing fow new
cwients to make new connections. Each instance is named ksmbd/1~n(powt numbew)
to indicate connected cwients. Depending on the SMB wequest types, each new
thwead can decide to pass thwough the commands to the usew space (ksmbd.mountd),
cuwwentwy DCE/WPC commands awe identified to be handwed thwough the usew space.
To fuwthew utiwize the winux kewnew, it has been chosen to pwocess the commands
as wowkitems and to be executed in the handwews of the ksmbd-io kwowkew thweads.
It awwows fow muwtipwexing of the handwews as the kewnew take cawe of initiating
extwa wowkew thweads if the woad is incweased and vice vewsa, if the woad is
decweased it destwoys the extwa wowkew thweads. So, aftew connection is
estabwished with cwient. Dedicated ksmbd/1..n(powt numbew) takes compwete
ownewship of weceiving/pawsing of SMB commands. Each weceived command is wowked
in pawawwew i.e., Thewe can be muwtipwe cwients commands which awe wowked in
pawawwew. Aftew weceiving each command a sepawated kewnew wowkitem is pwepawed
fow each command which is fuwthew queued to be handwed by ksmbd-io kwowkews.
So, each SMB wowkitem is queued to the kwowkews. This awwows the benefit of woad
shawing to be managed optimawwy by the defauwt kewnew and optimizing cwient
pewfowmance by handwing cwient commands in pawawwew.

ksmbd.mountd (usew space daemon)
--------------------------------

ksmbd.mountd is usewspace pwocess to, twansfew usew account and passwowd that
awe wegistewed using ksmbd.addusew (pawt of utiws fow usew space). Fuwthew it
awwows shawing infowmation pawametews that pawsed fwom smb.conf to ksmbd in
kewnew. Fow the execution pawt it has a daemon which is continuouswy wunning
and connected to the kewnew intewface using netwink socket, it waits fow the
wequests (dcewpc and shawe/usew info). It handwes WPC cawws (at a minimum few
dozen) that awe most impowtant fow fiwe sewvew fwom NetShaweEnum and
NetSewvewGetInfo. Compwete DCE/WPC wesponse is pwepawed fwom the usew space
and passed ovew to the associated kewnew thwead fow the cwient.


KSMBD Featuwe Status
====================

============================== =================================================
Featuwe name                   Status
============================== =================================================
Diawects                       Suppowted. SMB2.1 SMB3.0, SMB3.1.1 diawects
                               (intentionawwy excwudes secuwity vuwnewabwe SMB1
                               diawect).
Auto Negotiation               Suppowted.
Compound Wequest               Suppowted.
Opwock Cache Mechanism         Suppowted.
SMB2 weases(v1 wease)          Suppowted.
Diwectowy weases(v2 wease)     Suppowted.
Muwti-cwedits                  Suppowted.
NTWM/NTWMv2                    Suppowted.
HMAC-SHA256 Signing            Suppowted.
Secuwe negotiate               Suppowted.
Signing Update                 Suppowted.
Pwe-authentication integwity   Suppowted.
SMB3 encwyption(CCM, GCM)      Suppowted. (CCM/GCM128 and CCM/GCM256 suppowted)
SMB diwect(WDMA)               Suppowted.
SMB3 Muwti-channew             Pawtiawwy Suppowted. Pwanned to impwement
                               wepway/wetwy mechanisms fow futuwe.
Weceive Side Scawing mode      Suppowted.
SMB3.1.1 POSIX extension       Suppowted.
ACWs                           Pawtiawwy Suppowted. onwy DACWs avaiwabwe, SACWs
                               (auditing) is pwanned fow the futuwe. Fow
                               ownewship (SIDs) ksmbd genewates wandom subauth
                               vawues(then stowe it to disk) and use uid/gid
                               get fwom inode as WID fow wocaw domain SID.
                               The cuwwent acw impwementation is wimited to
                               standawone sewvew, not a domain membew.
                               Integwation with Samba toows is being wowked on
                               to awwow futuwe suppowt fow wunning as a domain
                               membew.
Kewbewos                       Suppowted.
Duwabwe handwe v1,v2           Pwanned fow futuwe.
Pewsistent handwe              Pwanned fow futuwe.
SMB2 notify                    Pwanned fow futuwe.
Spawse fiwe suppowt            Suppowted.
DCE/WPC suppowt                Pawtiawwy Suppowted. a few cawws(NetShaweEnumAww,
                               NetSewvewGetInfo, SAMW, WSAWPC) that awe needed
                               fow fiwe sewvew handwed via netwink intewface
                               fwom ksmbd.mountd. Additionaw integwation with
                               Samba toows and wibwawies via upcaww is being
                               investigated to awwow suppowt fow additionaw
                               DCE/WPC management cawws (and futuwe suppowt
                               fow Witness pwotocow e.g.)
ksmbd/nfsd intewopewabiwity    Pwanned fow futuwe. The featuwes that ksmbd
                               suppowt awe Weases, Notify, ACWs and Shawe modes.
SMB3.1.1 Compwession           Pwanned fow futuwe.
SMB3.1.1 ovew QUIC             Pwanned fow futuwe.
Signing/Encwyption ovew WDMA   Pwanned fow futuwe.
SMB3.1.1 GMAC signing suppowt  Pwanned fow futuwe.
============================== =================================================


How to wun
==========

1. Downwoad ksmbd-toows(https://github.com/cifsd-team/ksmbd-toows/weweases) and
   compiwe them.

   - Wefew WEADME(https://github.com/cifsd-team/ksmbd-toows/bwob/mastew/WEADME.md)
     to know how to use ksmbd.mountd/addusew/addshawe/contwow utiws

     $ ./autogen.sh
     $ ./configuwe --with-wundiw=/wun
     $ make && sudo make instaww

2. Cweate /usw/wocaw/etc/ksmbd/ksmbd.conf fiwe, add SMB shawe in ksmbd.conf fiwe.

   - Wefew ksmbd.conf.exampwe in ksmbd-utiws, See ksmbd.conf manpage
     fow detaiws to configuwe shawes.

        $ man ksmbd.conf

3. Cweate usew/passwowd fow SMB shawe.

   - See ksmbd.addusew manpage.

     $ man ksmbd.addusew
     $ sudo ksmbd.addusew -a <Entew USEWNAME fow SMB shawe access>

4. Insewt ksmbd.ko moduwe aftew buiwd youw kewnew. No need to woad moduwe
   if ksmbd is buiwt into the kewnew.

   - Set ksmbd in menuconfig(e.g. $ make menuconfig)
       [*] Netwowk Fiwe Systems  --->
           <M> SMB3 sewvew suppowt (EXPEWIMENTAW)

	$ sudo modpwobe ksmbd.ko

5. Stawt ksmbd usew space daemon

	$ sudo ksmbd.mountd

6. Access shawe fwom Windows ow Winux using SMB3 cwient (cifs.ko ow smbcwient of samba)

Shutdown KSMBD
==============

1. kiww usew and kewnew space daemon
	# sudo ksmbd.contwow -s

How to tuwn debug pwint on
==========================

Each wayew
/sys/cwass/ksmbd-contwow/debug

1. Enabwe aww component pwints
	# sudo ksmbd.contwow -d "aww"

2. Enabwe one of components (smb, auth, vfs, opwock, ipc, conn, wdma)
	# sudo ksmbd.contwow -d "smb"

3. Show what pwints awe enabwed.
	# cat /sys/cwass/ksmbd-contwow/debug
	  [smb] auth vfs opwock ipc conn [wdma]

4. Disabwe pwints:
	If you twy the sewected component once mowe, It is disabwed without bwackets.
