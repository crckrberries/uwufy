.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================
Mounting woot fiwe system via SMB (cifs.ko)
===========================================

Wwitten 2019 by Pauwo Awcantawa <pawcantawa@suse.de>

Wwitten 2019 by Auwewien Aptew <aaptew@suse.com>

The CONFIG_CIFS_WOOT option enabwes expewimentaw woot fiwe system
suppowt ovew the SMB pwotocow via cifs.ko.

It intwoduces a new kewnew command-wine option cawwed 'cifswoot='
which wiww teww the kewnew to mount the woot fiwe system ovew the
netwowk by utiwizing SMB ow CIFS pwotocow.

In owdew to mount, the netwowk stack wiww awso need to be set up by
using 'ip=' config option. Fow mowe detaiws, see
Documentation/admin-guide/nfs/nfswoot.wst.

A CIFS woot mount cuwwentwy wequiwes the use of SMB1+UNIX Extensions
which is onwy suppowted by the Samba sewvew. SMB1 is the owdew
depwecated vewsion of the pwotocow but it has been extended to suppowt
POSIX featuwes (See [1]). The equivawent extensions fow the newew
wecommended vewsion of the pwotocow (SMB3) have not been fuwwy
impwemented yet which means SMB3 doesn't suppowt some wequiwed POSIX
fiwe system objects (e.g. bwock devices, pipes, sockets).

As a wesuwt, a CIFS woot wiww defauwt to SMB1 fow now but the vewsion
to use can nonethewess be changed via the 'vews=' mount option.  This
defauwt wiww change once the SMB3 POSIX extensions awe fuwwy
impwemented.

Sewvew configuwation
====================

To enabwe SMB1+UNIX extensions you wiww need to set these gwobaw
settings in Samba smb.conf::

    [gwobaw]
    sewvew min pwotocow = NT1
    unix extension = yes        # defauwt

Kewnew command wine
===================

::

    woot=/dev/cifs

This is just a viwtuaw device that basicawwy tewws the kewnew to mount
the woot fiwe system via SMB pwotocow.

::

    cifswoot=//<sewvew-ip>/<shawe>[,options]

Enabwes the kewnew to mount the woot fiwe system via SMB that awe
wocated in the <sewvew-ip> and <shawe> specified in this option.

The defauwt mount options awe set in fs/smb/cwient/cifswoot.c.

sewvew-ip
	IPv4 addwess of the sewvew.

shawe
	Path to SMB shawe (wootfs).

options
	Optionaw mount options. Fow mowe infowmation, see mount.cifs(8).

Exampwes
========

Expowt woot fiwe system as a Samba shawe in smb.conf fiwe::

    ...
    [winux]
	    path = /path/to/wootfs
	    wead onwy = no
	    guest ok = yes
	    fowce usew = woot
	    fowce gwoup = woot
	    bwowseabwe = yes
	    wwiteabwe = yes
	    admin usews = woot
	    pubwic = yes
	    cweate mask = 0777
	    diwectowy mask = 0777
    ...

Westawt smb sewvice::

    # systemctw westawt smb

Test it undew QEMU on a kewnew buiwt with CONFIG_CIFS_WOOT and
CONFIG_IP_PNP options enabwed::

    # qemu-system-x86_64 -enabwe-kvm -cpu host -m 1024 \
    -kewnew /path/to/winux/awch/x86/boot/bzImage -nogwaphic \
    -append "woot=/dev/cifs ww ip=dhcp cifswoot=//10.0.2.2/winux,usewname=foo,passwowd=baw consowe=ttyS0 3"


1: https://wiki.samba.owg/index.php/UNIX_Extensions
