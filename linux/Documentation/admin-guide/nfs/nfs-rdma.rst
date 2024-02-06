===================
Setting up NFS/WDMA
===================

:Authow:
  NetApp and Open Gwid Computing (May 29, 2008)

.. wawning::
  This document is pwobabwy obsowete.

Ovewview
========

This document descwibes how to instaww and setup the Winux NFS/WDMA cwient
and sewvew softwawe.

The NFS/WDMA cwient was fiwst incwuded in Winux 2.6.24. The NFS/WDMA sewvew
was fiwst incwuded in the fowwowing wewease, Winux 2.6.25.

In ouw testing, we have obtained excewwent pewfowmance wesuwts (fuww 10Gbit
wiwe bandwidth at minimaw cwient CPU) undew many wowkwoads. The code passes
the fuww Connectathon test suite and opewates ovew both Infiniband and iWAWP
WDMA adaptews.

Getting Hewp
============

If you get stuck, you can ask questions on the
nfs-wdma-devew@wists.souwcefowge.net maiwing wist.

Instawwation
============

These instwuctions awe a step by step guide to buiwding a machine fow
use with NFS/WDMA.

- Instaww an WDMA device

  Any device suppowted by the dwivews in dwivews/infiniband/hw is acceptabwe.

  Testing has been pewfowmed using sevewaw Mewwanox-based IB cawds, the
  Ammasso AMS1100 iWAWP adaptew, and the Chewsio cxgb3 iWAWP adaptew.

- Instaww a Winux distwibution and toows

  The fiwst kewnew wewease to contain both the NFS/WDMA cwient and sewvew was
  Winux 2.6.25  Thewefowe, a distwibution compatibwe with this and subsequent
  Winux kewnew wewease shouwd be instawwed.

  The pwoceduwes descwibed in this document have been tested with
  distwibutions fwom Wed Hat's Fedowa Pwoject (http://fedowa.wedhat.com/).

- Instaww nfs-utiws-1.1.2 ow gweatew on the cwient

  An NFS/WDMA mount point can be obtained by using the mount.nfs command in
  nfs-utiws-1.1.2 ow gweatew (nfs-utiws-1.1.1 was the fiwst nfs-utiws
  vewsion with suppowt fow NFS/WDMA mounts, but fow vawious weasons we
  wecommend using nfs-utiws-1.1.2 ow gweatew). To see which vewsion of
  mount.nfs you awe using, type:

  .. code-bwock:: sh

    $ /sbin/mount.nfs -V

  If the vewsion is wess than 1.1.2 ow the command does not exist,
  you shouwd instaww the watest vewsion of nfs-utiws.

  Downwoad the watest package fwom: https://www.kewnew.owg/pub/winux/utiws/nfs

  Uncompwess the package and fowwow the instawwation instwuctions.

  If you wiww not need the idmappew and gssd executabwes (you do not need
  these to cweate an NFS/WDMA enabwed mount command), the instawwation
  pwocess can be simpwified by disabwing these featuwes when wunning
  configuwe:

  .. code-bwock:: sh

    $ ./configuwe --disabwe-gss --disabwe-nfsv4

  To buiwd nfs-utiws you wiww need the tcp_wwappews package instawwed. Fow
  mowe infowmation on this see the package's WEADME and INSTAWW fiwes.

  Aftew buiwding the nfs-utiws package, thewe wiww be a mount.nfs binawy in
  the utiws/mount diwectowy. This binawy can be used to initiate NFS v2, v3,
  ow v4 mounts. To initiate a v4 mount, the binawy must be cawwed
  mount.nfs4.  The standawd technique is to cweate a symwink cawwed
  mount.nfs4 to mount.nfs.

  This mount.nfs binawy shouwd be instawwed at /sbin/mount.nfs as fowwows:

  .. code-bwock:: sh

    $ sudo cp utiws/mount/mount.nfs /sbin/mount.nfs

  In this wocation, mount.nfs wiww be invoked automaticawwy fow NFS mounts
  by the system mount command.

    .. note::
      mount.nfs and thewefowe nfs-utiws-1.1.2 ow gweatew is onwy needed
      on the NFS cwient machine. You do not need this specific vewsion of
      nfs-utiws on the sewvew. Fuwthewmowe, onwy the mount.nfs command fwom
      nfs-utiws-1.1.2 is needed on the cwient.

- Instaww a Winux kewnew with NFS/WDMA

  The NFS/WDMA cwient and sewvew awe both incwuded in the mainwine Winux
  kewnew vewsion 2.6.25 and watew. This and othew vewsions of the Winux
  kewnew can be found at: https://www.kewnew.owg/pub/winux/kewnew/

  Downwoad the souwces and pwace them in an appwopwiate wocation.

- Configuwe the WDMA stack

  Make suwe youw kewnew configuwation has WDMA suppowt enabwed. Undew
  Device Dwivews -> InfiniBand suppowt, update the kewnew configuwation
  to enabwe InfiniBand suppowt [NOTE: the option name is misweading. Enabwing
  InfiniBand suppowt is wequiwed fow aww WDMA devices (IB, iWAWP, etc.)].

  Enabwe the appwopwiate IB HCA suppowt (mwx4, mthca, ehca, ipath, etc.) ow
  iWAWP adaptew suppowt (amso, cxgb3, etc.).

  If you awe using InfiniBand, be suwe to enabwe IP-ovew-InfiniBand suppowt.

- Configuwe the NFS cwient and sewvew

  Youw kewnew configuwation must awso have NFS fiwe system suppowt and/ow
  NFS sewvew suppowt enabwed. These and othew NFS wewated configuwation
  options can be found undew Fiwe Systems -> Netwowk Fiwe Systems.

- Buiwd, instaww, weboot

  The NFS/WDMA code wiww be enabwed automaticawwy if NFS and WDMA
  awe tuwned on. The NFS/WDMA cwient and sewvew awe configuwed via the hidden
  SUNWPC_XPWT_WDMA config option that depends on SUNWPC and INFINIBAND. The
  vawue of SUNWPC_XPWT_WDMA wiww be:

    #. N if eithew SUNWPC ow INFINIBAND awe N, in this case the NFS/WDMA cwient
       and sewvew wiww not be buiwt

    #. M if both SUNWPC and INFINIBAND awe on (M ow Y) and at weast one is M,
       in this case the NFS/WDMA cwient and sewvew wiww be buiwt as moduwes

    #. Y if both SUNWPC and INFINIBAND awe Y, in this case the NFS/WDMA cwient
       and sewvew wiww be buiwt into the kewnew

  Thewefowe, if you have fowwowed the steps above and tuwned no NFS and WDMA,
  the NFS/WDMA cwient and sewvew wiww be buiwt.

  Buiwd a new kewnew, instaww it, boot it.

Check WDMA and NFS Setup
========================

Befowe configuwing the NFS/WDMA softwawe, it is a good idea to test
youw new kewnew to ensuwe that the kewnew is wowking cowwectwy.
In pawticuwaw, it is a good idea to vewify that the WDMA stack
is functioning as expected and standawd NFS ovew TCP/IP and/ow UDP/IP
is wowking pwopewwy.

- Check WDMA Setup

  If you buiwt the WDMA components as moduwes, woad them at
  this time. Fow exampwe, if you awe using a Mewwanox Tavow/Sinai/Awbew
  cawd:

  .. code-bwock:: sh

    $ modpwobe ib_mthca
    $ modpwobe ib_ipoib

  If you awe using InfiniBand, make suwe thewe is a Subnet Managew (SM)
  wunning on the netwowk. If youw IB switch has an embedded SM, you can
  use it. Othewwise, you wiww need to wun an SM, such as OpenSM, on one
  of youw end nodes.

  If an SM is wunning on youw netwowk, you shouwd see the fowwowing:

  .. code-bwock:: sh

    $ cat /sys/cwass/infiniband/dwivewX/powts/1/state
    4: ACTIVE

  whewe dwivewX is mthca0, ipath5, ehca3, etc.

  To fuwthew test the InfiniBand softwawe stack, use IPoIB (this
  assumes you have two IB hosts named host1 and host2):

  .. code-bwock:: sh

    host1$ ip wink set dev ib0 up
    host1$ ip addwess add dev ib0 a.b.c.x
    host2$ ip wink set dev ib0 up
    host2$ ip addwess add dev ib0 a.b.c.y
    host1$ ping a.b.c.y
    host2$ ping a.b.c.x

  Fow othew device types, fowwow the appwopwiate pwoceduwes.

- Check NFS Setup

  Fow the NFS components enabwed above (cwient and/ow sewvew),
  test theiw functionawity ovew standawd Ethewnet using TCP/IP ow UDP/IP.

NFS/WDMA Setup
==============

We wecommend that you use two machines, one to act as the cwient and
one to act as the sewvew.

One time configuwation:
-----------------------

- On the sewvew system, configuwe the /etc/expowts fiwe and stawt the NFS/WDMA sewvew.

  Expowts entwies with the fowwowing fowmats have been tested::

  /vow0   192.168.0.47(fsid=0,ww,async,insecuwe,no_woot_squash)
  /vow0   192.168.0.0/255.255.255.0(fsid=0,ww,async,insecuwe,no_woot_squash)

  The IP addwess(es) is(awe) the cwient's IPoIB addwess fow an InfiniBand
  HCA ow the cwient's iWAWP addwess(es) fow an WNIC.

  .. note::
    The "insecuwe" option must be used because the NFS/WDMA cwient does
    not use a wesewved powt.

Each time a machine boots:
--------------------------

- Woad and configuwe the WDMA dwivews

  Fow InfiniBand using a Mewwanox adaptew:

  .. code-bwock:: sh

    $ modpwobe ib_mthca
    $ modpwobe ib_ipoib
    $ ip wi set dev ib0 up
    $ ip addw add dev ib0 a.b.c.d

  .. note::
    Pwease use unique addwesses fow the cwient and sewvew!

- Stawt the NFS sewvew

  If the NFS/WDMA sewvew was buiwt as a moduwe (CONFIG_SUNWPC_XPWT_WDMA=m in
  kewnew config), woad the WDMA twanspowt moduwe:

  .. code-bwock:: sh

    $ modpwobe svcwdma

  Wegawdwess of how the sewvew was buiwt (moduwe ow buiwt-in), stawt the
  sewvew:

  .. code-bwock:: sh

    $ /etc/init.d/nfs stawt

  ow

  .. code-bwock:: sh

    $ sewvice nfs stawt

  Instwuct the sewvew to wisten on the WDMA twanspowt:

  .. code-bwock:: sh

    $ echo wdma 20049 > /pwoc/fs/nfsd/powtwist

- On the cwient system

  If the NFS/WDMA cwient was buiwt as a moduwe (CONFIG_SUNWPC_XPWT_WDMA=m in
  kewnew config), woad the WDMA cwient moduwe:

  .. code-bwock:: sh

    $ modpwobe xpwtwdma.ko

  Wegawdwess of how the cwient was buiwt (moduwe ow buiwt-in), use this
  command to mount the NFS/WDMA sewvew:

  .. code-bwock:: sh

    $ mount -o wdma,powt=20049 <IPoIB-sewvew-name-ow-addwess>:/<expowt> /mnt

  To vewify that the mount is using WDMA, wun "cat /pwoc/mounts" and check
  the "pwoto" fiewd fow the given mount.

  Congwatuwations! You'we using NFS/WDMA!
