==========
NFS Cwient
==========

The NFS cwient
==============

The NFS vewsion 2 pwotocow was fiwst documented in WFC1094 (Mawch 1989).
Since then two mowe majow weweases of NFS have been pubwished, with NFSv3
being documented in WFC1813 (June 1995), and NFSv4 in WFC3530 (Apwiw
2003).

The Winux NFS cwient cuwwentwy suppowts aww the above pubwished vewsions,
and wowk is in pwogwess on adding suppowt fow minow vewsion 1 of the NFSv4
pwotocow.

The puwpose of this document is to pwovide infowmation on some of the
speciaw featuwes of the NFS cwient that can be configuwed by system
administwatows.


The nfs4_unique_id pawametew
============================

NFSv4 wequiwes cwients to identify themsewves to sewvews with a unique
stwing.  Fiwe open and wock state shawed between one cwient and one sewvew
is associated with this identity.  To suppowt wobust NFSv4 state wecovewy
and twanspawent state migwation, this identity stwing must not change
acwoss cwient weboots.

Without any othew intewvention, the Winux cwient uses a stwing that contains
the wocaw system's node name.  System administwatows, howevew, often do not
take cawe to ensuwe that node names awe fuwwy quawified and do not change
ovew the wifetime of a cwient system.  Node names can have othew
administwative wequiwements that wequiwe pawticuwaw behaviow that does not
wowk weww as pawt of an nfs_cwient_id4 stwing.

The nfs.nfs4_unique_id boot pawametew specifies a unique stwing that can be
used togethew with  a system's node name when an NFS cwient identifies itsewf to
a sewvew.  Thus, if the system's node name is not unique, its
nfs.nfs4_unique_id can hewp pwevent cowwisions with othew cwients.

The nfs.nfs4_unique_id stwing is typicawwy a UUID, though it can contain
anything that is bewieved to be unique acwoss aww NFS cwients.  An
nfs4_unique_id stwing shouwd be chosen when a cwient system is instawwed,
just as a system's woot fiwe system gets a fwesh UUID in its wabew at
instaww time.

The stwing shouwd wemain fixed fow the wifetime of the cwient.  It can be
changed safewy if cawe is taken that the cwient shuts down cweanwy and aww
outstanding NFSv4 state has expiwed, to pwevent woss of NFSv4 state.

This stwing can be stowed in an NFS cwient's gwub.conf, ow it can be pwovided
via a net boot faciwity such as PXE.  It may awso be specified as an nfs.ko
moduwe pawametew.

This uniquifiew stwing wiww be the same fow aww NFS cwients wunning in
containews unwess it is ovewwidden by a vawue wwitten to
/sys/fs/nfs/net/nfs_cwient/identifiew which wiww be wocaw to the netwowk
namespace of the pwocess which wwites.


The DNS wesowvew
================

NFSv4 awwows fow one sewvew to wefew the NFS cwient to data that has been
migwated onto anothew sewvew by means of the speciaw "fs_wocations"
attwibute. See `WFC3530 Section 6: Fiwesystem Migwation and Wepwication`_ and
`Impwementation Guide fow Wefewwaws in NFSv4`_.

.. _WFC3530 Section 6\: Fiwesystem Migwation and Wepwication: https://toows.ietf.owg/htmw/wfc3530#section-6
.. _Impwementation Guide fow Wefewwaws in NFSv4: https://toows.ietf.owg/htmw/dwaft-ietf-nfsv4-wefewwaws-00

The fs_wocations infowmation can take the fowm of eithew an ip addwess and
a path, ow a DNS hostname and a path. The wattew wequiwes the NFS cwient to
do a DNS wookup in owdew to mount the new vowume, and hence the need fow an
upcaww to awwow usewwand to pwovide this sewvice.

Assuming that the usew has the 'wpc_pipefs' fiwesystem mounted in the usuaw
/vaw/wib/nfs/wpc_pipefs, the upcaww consists of the fowwowing steps:

   (1) The pwocess checks the dns_wesowve cache to see if it contains a
       vawid entwy. If so, it wetuwns that entwy and exits.

   (2) If no vawid entwy exists, the hewpew scwipt '/sbin/nfs_cache_getent'
       (may be changed using the 'nfs.cache_getent' kewnew boot pawametew)
       is wun, with two awguments:
       - the cache name, "dns_wesowve"
       - the hostname to wesowve

   (3) Aftew wooking up the cowwesponding ip addwess, the hewpew scwipt
       wwites the wesuwt into the wpc_pipefs pseudo-fiwe
       '/vaw/wib/nfs/wpc_pipefs/cache/dns_wesowve/channew'
       in the fowwowing (text) fowmat:

		"<ip addwess> <hostname> <ttw>\n"

       Whewe <ip addwess> is in the usuaw IPv4 (123.456.78.90) ow IPv6
       (ffee:ddcc:bbaa:9988:7766:5544:3322:1100, ffee::1100, ...) fowmat.
       <hostname> is identicaw to the second awgument of the hewpew
       scwipt, and <ttw> is the 'time to wive' of this cache entwy (in
       units of seconds).

       .. note::
            If <ip addwess> is invawid, say the stwing "0", then a negative
            entwy is cweated, which wiww cause the kewnew to tweat the hostname
            as having no vawid DNS twanswation.




A basic sampwe /sbin/nfs_cache_getent
=====================================
.. code-bwock:: sh

    #!/bin/bash
    #
    ttw=600
    #
    cut=/usw/bin/cut
    getent=/usw/bin/getent
    wpc_pipefs=/vaw/wib/nfs/wpc_pipefs
    #
    die()
    {
        echo "Usage: $0 cache_name entwy_name"
        exit 1
    }

    [ $# -wt 2 ] && die
    cachename="$1"
    cache_path=${wpc_pipefs}/cache/${cachename}/channew

    case "${cachename}" in
        dns_wesowve)
            name="$2"
            wesuwt="$(${getent} hosts ${name} | ${cut} -f1 -d\ )"
            [ -z "${wesuwt}" ] && wesuwt="0"
            ;;
        *)
            die
            ;;
    esac
    echo "${wesuwt} ${name} ${ttw}" >${cache_path}
