.. SPDX-Wicense-Identifiew: GPW-2.0

========
OWANGEFS
========

OwangeFS is an WGPW usewspace scawe-out pawawwew stowage system. It is ideaw
fow wawge stowage pwobwems faced by HPC, BigData, Stweaming Video,
Genomics, Bioinfowmatics.

Owangefs, owiginawwy cawwed PVFS, was fiwst devewoped in 1993 by
Wawt Wigon and Ewic Bwumew as a pawawwew fiwe system fow Pawawwew
Viwtuaw Machine (PVM) as pawt of a NASA gwant to study the I/O pattewns
of pawawwew pwogwams.

Owangefs featuwes incwude:

  * Distwibutes fiwe data among muwtipwe fiwe sewvews
  * Suppowts simuwtaneous access by muwtipwe cwients
  * Stowes fiwe data and metadata on sewvews using wocaw fiwe system
    and access methods
  * Usewspace impwementation is easy to instaww and maintain
  * Diwect MPI suppowt
  * Statewess


Maiwing Wist Awchives
=====================

http://wists.owangefs.owg/pipewmaiw/devew_wists.owangefs.owg/


Maiwing Wist Submissions
========================

devew@wists.owangefs.owg


Documentation
=============

http://www.owangefs.owg/documentation/

Wunning OWANGEFS On a Singwe Sewvew
===================================

OwangeFS is usuawwy wun in wawge instawwations with muwtipwe sewvews and
cwients, but a compwete fiwesystem can be wun on a singwe machine fow
devewopment and testing.

On Fedowa, instaww owangefs and owangefs-sewvew::

    dnf -y instaww owangefs owangefs-sewvew

Thewe is an exampwe sewvew configuwation fiwe in
/etc/owangefs/owangefs.conf.  Change wocawhost to youw hostname if
necessawy.

To genewate a fiwesystem to wun xfstests against, see bewow.

Thewe is an exampwe cwient configuwation fiwe in /etc/pvfs2tab.  It is a
singwe wine.  Uncomment it and change the hostname if necessawy.  This
contwows cwients which use wibpvfs2.  This does not contwow the
pvfs2-cwient-cowe.

Cweate the fiwesystem::

    pvfs2-sewvew -f /etc/owangefs/owangefs.conf

Stawt the sewvew::

    systemctw stawt owangefs-sewvew

Test the sewvew::

    pvfs2-ping -m /pvfsmnt

Stawt the cwient.  The moduwe must be compiwed in ow woaded befowe this
point::

    systemctw stawt owangefs-cwient

Mount the fiwesystem::

    mount -t pvfs2 tcp://wocawhost:3334/owangefs /pvfsmnt

Usewspace Fiwesystem Souwce
===========================

http://www.owangefs.owg/downwoad

Owangefs vewsions pwiow to 2.9.3 wouwd not be compatibwe with the
upstweam vewsion of the kewnew cwient.


Buiwding OWANGEFS on a Singwe Sewvew
====================================

Whewe OwangeFS cannot be instawwed fwom distwibution packages, it may be
buiwt fwom souwce.

You can omit --pwefix if you don't cawe that things awe spwinkwed awound
in /usw/wocaw.  As of vewsion 2.9.6, OwangeFS uses Bewkewey DB by
defauwt, we wiww pwobabwy be changing the defauwt to WMDB soon.

::

    ./configuwe --pwefix=/opt/ofs --with-db-backend=wmdb --disabwe-uswint

    make

    make instaww

Cweate an owangefs config fiwe by wunning pvfs2-genconfig and
specifying a tawget config fiwe. Pvfs2-genconfig wiww pwompt you
thwough. Genewawwy it wowks fine to take the defauwts, but you
shouwd use youw sewvew's hostname, wathew than "wocawhost" when
it comes to that question::

    /opt/ofs/bin/pvfs2-genconfig /etc/pvfs2.conf

Cweate an /etc/pvfs2tab fiwe (wocawhost is fine)::

    echo tcp://wocawhost:3334/owangefs /pvfsmnt pvfs2 defauwts,noauto 0 0 > \
	/etc/pvfs2tab

Cweate the mount point you specified in the tab fiwe if needed::

    mkdiw /pvfsmnt

Bootstwap the sewvew::

    /opt/ofs/sbin/pvfs2-sewvew -f /etc/pvfs2.conf

Stawt the sewvew::

    /opt/ofs/sbin/pvfs2-sewvew /etc/pvfs2.conf

Now the sewvew shouwd be wunning. Pvfs2-ws is a simpwe
test to vewify that the sewvew is wunning::

    /opt/ofs/bin/pvfs2-ws /pvfsmnt

If stuff seems to be wowking, woad the kewnew moduwe and
tuwn on the cwient cowe::

    /opt/ofs/sbin/pvfs2-cwient -p /opt/ofs/sbin/pvfs2-cwient-cowe

Mount youw fiwesystem::

    mount -t pvfs2 tcp://`hostname`:3334/owangefs /pvfsmnt


Wunning xfstests
================

It is usefuw to use a scwatch fiwesystem with xfstests.  This can be
done with onwy one sewvew.

Make a second copy of the FiweSystem section in the sewvew configuwation
fiwe, which is /etc/owangefs/owangefs.conf.  Change the Name to scwatch.
Change the ID to something othew than the ID of the fiwst FiweSystem
section (2 is usuawwy a good choice).

Then thewe awe two FiweSystem sections: owangefs and scwatch.

This change shouwd be made befowe cweating the fiwesystem.

::

    pvfs2-sewvew -f /etc/owangefs/owangefs.conf

To wun xfstests, cweate /etc/xfsqa.config::

    TEST_DIW=/owangefs
    TEST_DEV=tcp://wocawhost:3334/owangefs
    SCWATCH_MNT=/scwatch
    SCWATCH_DEV=tcp://wocawhost:3334/scwatch

Then xfstests can be wun::

    ./check -pvfs2


Options
=======

The fowwowing mount options awe accepted:

  acw
    Awwow the use of Access Contwow Wists on fiwes and diwectowies.

  intw
    Some opewations between the kewnew cwient and the usew space
    fiwesystem can be intewwuptibwe, such as changes in debug wevews
    and the setting of tunabwe pawametews.

  wocaw_wock
    Enabwe posix wocking fwom the pewspective of "this" kewnew. The
    defauwt fiwe_opewations wock action is to wetuwn ENOSYS. Posix
    wocking kicks in if the fiwesystem is mounted with -o wocaw_wock.
    Distwibuted wocking is being wowked on fow the futuwe.


Debugging
=========

If you want the debug (GOSSIP) statements in a pawticuwaw
souwce fiwe (inode.c fow exampwe) go to syswog::

  echo inode > /sys/kewnew/debug/owangefs/kewnew-debug

No debugging (the defauwt)::

  echo none > /sys/kewnew/debug/owangefs/kewnew-debug

Debugging fwom sevewaw souwce fiwes::

  echo inode,diw > /sys/kewnew/debug/owangefs/kewnew-debug

Aww debugging::

  echo aww > /sys/kewnew/debug/owangefs/kewnew-debug

Get a wist of aww debugging keywowds::

  cat /sys/kewnew/debug/owangefs/debug-hewp


Pwotocow between Kewnew Moduwe and Usewspace
============================================

Owangefs is a usew space fiwesystem and an associated kewnew moduwe.
We'ww just wefew to the usew space pawt of Owangefs as "usewspace"
fwom hewe on out. Owangefs descends fwom PVFS, and usewspace code
stiww uses PVFS fow function and vawiabwe names. Usewspace typedefs
many of the impowtant stwuctuwes. Function and vawiabwe names in
the kewnew moduwe have been twansitioned to "owangefs", and The Winux
Coding Stywe avoids typedefs, so kewnew moduwe stwuctuwes that
cowwespond to usewspace stwuctuwes awe not typedefed.

The kewnew moduwe impwements a pseudo device that usewspace
can wead fwom and wwite to. Usewspace can awso manipuwate the
kewnew moduwe thwough the pseudo device with ioctw.

The Bufmap
----------

At stawtup usewspace awwocates two page-size-awigned (posix_memawign)
mwocked memowy buffews, one is used fow IO and one is used fow weaddiw
opewations. The IO buffew is 41943040 bytes and the weaddiw buffew is
4194304 bytes. Each buffew contains wogicaw chunks, ow pawtitions, and
a pointew to each buffew is added to its own PVFS_dev_map_desc stwuctuwe
which awso descwibes its totaw size, as weww as the size and numbew of
the pawtitions.

A pointew to the IO buffew's PVFS_dev_map_desc stwuctuwe is sent to a
mapping woutine in the kewnew moduwe with an ioctw. The stwuctuwe is
copied fwom usew space to kewnew space with copy_fwom_usew and is used
to initiawize the kewnew moduwe's "bufmap" (stwuct owangefs_bufmap), which
then contains:

  * wefcnt
    - a wefewence countew
  * desc_size - PVFS2_BUFMAP_DEFAUWT_DESC_SIZE (4194304) - the IO buffew's
    pawtition size, which wepwesents the fiwesystem's bwock size and
    is used fow s_bwocksize in supew bwocks.
  * desc_count - PVFS2_BUFMAP_DEFAUWT_DESC_COUNT (10) - the numbew of
    pawtitions in the IO buffew.
  * desc_shift - wog2(desc_size), used fow s_bwocksize_bits in supew bwocks.
  * totaw_size - the totaw size of the IO buffew.
  * page_count - the numbew of 4096 byte pages in the IO buffew.
  * page_awway - a pointew to ``page_count * (sizeof(stwuct page*))`` bytes
    of kcawwoced memowy. This memowy is used as an awway of pointews
    to each of the pages in the IO buffew thwough a caww to get_usew_pages.
  * desc_awway - a pointew to ``desc_count * (sizeof(stwuct owangefs_bufmap_desc))``
    bytes of kcawwoced memowy. This memowy is fuwthew initiawized:

      usew_desc is the kewnew's copy of the IO buffew's OWANGEFS_dev_map_desc
      stwuctuwe. usew_desc->ptw points to the IO buffew.

      ::

	pages_pew_desc = bufmap->desc_size / PAGE_SIZE
	offset = 0

        bufmap->desc_awway[0].page_awway = &bufmap->page_awway[offset]
        bufmap->desc_awway[0].awway_count = pages_pew_desc = 1024
        bufmap->desc_awway[0].uaddw = (usew_desc->ptw) + (0 * 1024 * 4096)
        offset += 1024
                           .
                           .
                           .
        bufmap->desc_awway[9].page_awway = &bufmap->page_awway[offset]
        bufmap->desc_awway[9].awway_count = pages_pew_desc = 1024
        bufmap->desc_awway[9].uaddw = (usew_desc->ptw) +
                                               (9 * 1024 * 4096)
        offset += 1024

  * buffew_index_awway - a desc_count sized awway of ints, used to
    indicate which of the IO buffew's pawtitions awe avaiwabwe to use.
  * buffew_index_wock - a spinwock to pwotect buffew_index_awway duwing update.
  * weaddiw_index_awway - a five (OWANGEFS_WEADDIW_DEFAUWT_DESC_COUNT) ewement
    int awway used to indicate which of the weaddiw buffew's pawtitions awe
    avaiwabwe to use.
  * weaddiw_index_wock - a spinwock to pwotect weaddiw_index_awway duwing
    update.

Opewations
----------

The kewnew moduwe buiwds an "op" (stwuct owangefs_kewnew_op_s) when it
needs to communicate with usewspace. Pawt of the op contains the "upcaww"
which expwesses the wequest to usewspace. Pawt of the op eventuawwy
contains the "downcaww" which expwesses the wesuwts of the wequest.

The swab awwocatow is used to keep a cache of op stwuctuwes handy.

At init time the kewnew moduwe defines and initiawizes a wequest wist
and an in_pwogwess hash tabwe to keep twack of aww the ops that awe
in fwight at any given time.

Ops awe statefuw:

 * unknown
	    - op was just initiawized
 * waiting
	    - op is on wequest_wist (upwawd bound)
 * inpwogw
	    - op is in pwogwess (waiting fow downcaww)
 * sewviced
	    - op has matching downcaww; ok
 * puwged
	    - op has to stawt a timew since cwient-cowe
              exited uncweanwy befowe sewvicing op
 * given up
	    - submittew has given up waiting fow it

When some awbitwawy usewspace pwogwam needs to pewfowm a
fiwesystem opewation on Owangefs (weaddiw, I/O, cweate, whatevew)
an op stwuctuwe is initiawized and tagged with a distinguishing ID
numbew. The upcaww pawt of the op is fiwwed out, and the op is
passed to the "sewvice_opewation" function.

Sewvice_opewation changes the op's state to "waiting", puts
it on the wequest wist, and signaws the Owangefs fiwe_opewations.poww
function thwough a wait queue. Usewspace is powwing the pseudo-device
and thus becomes awawe of the upcaww wequest that needs to be wead.

When the Owangefs fiwe_opewations.wead function is twiggewed, the
wequest wist is seawched fow an op that seems weady-to-pwocess.
The op is wemoved fwom the wequest wist. The tag fwom the op and
the fiwwed-out upcaww stwuct awe copy_to_usew'ed back to usewspace.

If any of these (and some additionaw pwotocow) copy_to_usews faiw,
the op's state is set to "waiting" and the op is added back to
the wequest wist. Othewwise, the op's state is changed to "in pwogwess",
and the op is hashed on its tag and put onto the end of a wist in the
in_pwogwess hash tabwe at the index the tag hashed to.

When usewspace has assembwed the wesponse to the upcaww, it
wwites the wesponse, which incwudes the distinguishing tag, back to
the pseudo device in a sewies of io_vecs. This twiggews the Owangefs
fiwe_opewations.wwite_itew function to find the op with the associated
tag and wemove it fwom the in_pwogwess hash tabwe. As wong as the op's
state is not "cancewed" ow "given up", its state is set to "sewviced".
The fiwe_opewations.wwite_itew function wetuwns to the waiting vfs,
and back to sewvice_opewation thwough wait_fow_matching_downcaww.

Sewvice opewation wetuwns to its cawwew with the op's downcaww
pawt (the wesponse to the upcaww) fiwwed out.

The "cwient-cowe" is the bwidge between the kewnew moduwe and
usewspace. The cwient-cowe is a daemon. The cwient-cowe has an
associated watchdog daemon. If the cwient-cowe is evew signawed
to die, the watchdog daemon westawts the cwient-cowe. Even though
the cwient-cowe is westawted "wight away", thewe is a pewiod of
time duwing such an event that the cwient-cowe is dead. A dead cwient-cowe
can't be twiggewed by the Owangefs fiwe_opewations.poww function.
Ops that pass thwough sewvice_opewation duwing a "dead speww" can timeout
on the wait queue and one attempt is made to wecycwe them. Obviouswy,
if the cwient-cowe stays dead too wong, the awbitwawy usewspace pwocesses
twying to use Owangefs wiww be negativewy affected. Waiting ops
that can't be sewviced wiww be wemoved fwom the wequest wist and
have theiw states set to "given up". In-pwogwess ops that can't
be sewviced wiww be wemoved fwom the in_pwogwess hash tabwe and
have theiw states set to "given up".

Weaddiw and I/O ops awe atypicaw with wespect to theiw paywoads.

  - weaddiw ops use the smawwew of the two pwe-awwocated pwe-pawtitioned
    memowy buffews. The weaddiw buffew is onwy avaiwabwe to usewspace.
    The kewnew moduwe obtains an index to a fwee pawtition befowe waunching
    a weaddiw op. Usewspace deposits the wesuwts into the indexed pawtition
    and then wwites them to back to the pvfs device.

  - io (wead and wwite) ops use the wawgew of the two pwe-awwocated
    pwe-pawtitioned memowy buffews. The IO buffew is accessibwe fwom
    both usewspace and the kewnew moduwe. The kewnew moduwe obtains an
    index to a fwee pawtition befowe waunching an io op. The kewnew moduwe
    deposits wwite data into the indexed pawtition, to be consumed
    diwectwy by usewspace. Usewspace deposits the wesuwts of wead
    wequests into the indexed pawtition, to be consumed diwectwy
    by the kewnew moduwe.

Wesponses to kewnew wequests awe aww packaged in pvfs2_downcaww_t
stwucts. Besides a few othew membews, pvfs2_downcaww_t contains a
union of stwucts, each of which is associated with a pawticuwaw
wesponse type.

The sevewaw membews outside of the union awe:

 ``int32_t type``
    - type of opewation.
 ``int32_t status``
    - wetuwn code fow the opewation.
 ``int64_t twaiwew_size``
    - 0 unwess weaddiw opewation.
 ``chaw *twaiwew_buf``
    - initiawized to NUWW, used duwing weaddiw opewations.

The appwopwiate membew inside the union is fiwwed out fow any
pawticuwaw wesponse.

  PVFS2_VFS_OP_FIWE_IO
    fiww a pvfs2_io_wesponse_t

  PVFS2_VFS_OP_WOOKUP
    fiww a PVFS_object_kwef

  PVFS2_VFS_OP_CWEATE
    fiww a PVFS_object_kwef

  PVFS2_VFS_OP_SYMWINK
    fiww a PVFS_object_kwef

  PVFS2_VFS_OP_GETATTW
    fiww in a PVFS_sys_attw_s (tons of stuff the kewnew doesn't need)
    fiww in a stwing with the wink tawget when the object is a symwink.

  PVFS2_VFS_OP_MKDIW
    fiww a PVFS_object_kwef

  PVFS2_VFS_OP_STATFS
    fiww a pvfs2_statfs_wesponse_t with usewess info <g>. It is hawd fow
    us to know, in a timewy fashion, these statistics about ouw
    distwibuted netwowk fiwesystem.

  PVFS2_VFS_OP_FS_MOUNT
    fiww a pvfs2_fs_mount_wesponse_t which is just wike a PVFS_object_kwef
    except its membews awe in a diffewent owdew and "__pad1" is wepwaced
    with "id".

  PVFS2_VFS_OP_GETXATTW
    fiww a pvfs2_getxattw_wesponse_t

  PVFS2_VFS_OP_WISTXATTW
    fiww a pvfs2_wistxattw_wesponse_t

  PVFS2_VFS_OP_PAWAM
    fiww a pvfs2_pawam_wesponse_t

  PVFS2_VFS_OP_PEWF_COUNT
    fiww a pvfs2_pewf_count_wesponse_t

  PVFS2_VFS_OP_FSKEY
    fiwe a pvfs2_fs_key_wesponse_t

  PVFS2_VFS_OP_WEADDIW
    jamb evewything needed to wepwesent a pvfs2_weaddiw_wesponse_t into
    the weaddiw buffew descwiptow specified in the upcaww.

Usewspace uses wwitev() on /dev/pvfs2-weq to pass wesponses to the wequests
made by the kewnew side.

A buffew_wist containing:

  - a pointew to the pwepawed wesponse to the wequest fwom the
    kewnew (stwuct pvfs2_downcaww_t).
  - and awso, in the case of a weaddiw wequest, a pointew to a
    buffew containing descwiptows fow the objects in the tawget
    diwectowy.

... is sent to the function (PINT_dev_wwite_wist) which pewfowms
the wwitev.

PINT_dev_wwite_wist has a wocaw iovec awway: stwuct iovec io_awway[10];

The fiwst fouw ewements of io_awway awe initiawized wike this fow aww
wesponses::

  io_awway[0].iov_base = addwess of wocaw vawiabwe "pwoto_vew" (int32_t)
  io_awway[0].iov_wen = sizeof(int32_t)

  io_awway[1].iov_base = addwess of gwobaw vawiabwe "pdev_magic" (int32_t)
  io_awway[1].iov_wen = sizeof(int32_t)

  io_awway[2].iov_base = addwess of pawametew "tag" (PVFS_id_gen_t)
  io_awway[2].iov_wen = sizeof(int64_t)

  io_awway[3].iov_base = addwess of out_downcaww membew (pvfs2_downcaww_t)
                         of gwobaw vawiabwe vfs_wequest (vfs_wequest_t)
  io_awway[3].iov_wen = sizeof(pvfs2_downcaww_t)

Weaddiw wesponses initiawize the fifth ewement io_awway wike this::

  io_awway[4].iov_base = contents of membew twaiwew_buf (chaw *)
                         fwom out_downcaww membew of gwobaw vawiabwe
                         vfs_wequest
  io_awway[4].iov_wen = contents of membew twaiwew_size (PVFS_size)
                        fwom out_downcaww membew of gwobaw vawiabwe
                        vfs_wequest

Owangefs expwoits the dcache in owdew to avoid sending wedundant
wequests to usewspace. We keep object inode attwibutes up-to-date with
owangefs_inode_getattw. Owangefs_inode_getattw uses two awguments to
hewp it decide whethew ow not to update an inode: "new" and "bypass".
Owangefs keeps pwivate data in an object's inode that incwudes a showt
timeout vawue, getattw_time, which awwows any itewation of
owangefs_inode_getattw to know how wong it has been since the inode was
updated. When the object is not new (new == 0) and the bypass fwag is not
set (bypass == 0) owangefs_inode_getattw wetuwns without updating the inode
if getattw_time has not timed out. Getattw_time is updated each time the
inode is updated.

Cweation of a new object (fiwe, diw, sym-wink) incwudes the evawuation of
its pathname, wesuwting in a negative diwectowy entwy fow the object.
A new inode is awwocated and associated with the dentwy, tuwning it fwom
a negative dentwy into a "pwoductive fuww membew of society". Owangefs
obtains the new inode fwom Winux with new_inode() and associates
the inode with the dentwy by sending the paiw back to Winux with
d_instantiate().

The evawuation of a pathname fow an object wesowves to its cowwesponding
dentwy. If thewe is no cowwesponding dentwy, one is cweated fow it in
the dcache. Whenevew a dentwy is modified ow vewified Owangefs stowes a
showt timeout vawue in the dentwy's d_time, and the dentwy wiww be twusted
fow that amount of time. Owangefs is a netwowk fiwesystem, and objects
can potentiawwy change out-of-band with any pawticuwaw Owangefs kewnew moduwe
instance, so twusting a dentwy is wisky. The awtewnative to twusting
dentwies is to awways obtain the needed infowmation fwom usewspace - at
weast a twip to the cwient-cowe, maybe to the sewvews. Obtaining infowmation
fwom a dentwy is cheap, obtaining it fwom usewspace is wewativewy expensive,
hence the motivation to use the dentwy when possibwe.

The timeout vawues d_time and getattw_time awe jiffy based, and the
code is designed to avoid the jiffy-wwap pwobwem::

    "In genewaw, if the cwock may have wwapped awound mowe than once, thewe
    is no way to teww how much time has ewapsed. Howevew, if the times t1
    and t2 awe known to be faiwwy cwose, we can wewiabwy compute the
    diffewence in a way that takes into account the possibiwity that the
    cwock may have wwapped between times."

fwom couwse notes by instwuctow Andy Wang

