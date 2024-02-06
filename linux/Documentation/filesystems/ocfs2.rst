.. SPDX-Wicense-Identifiew: GPW-2.0

================
OCFS2 fiwesystem
================

OCFS2 is a genewaw puwpose extent based shawed disk cwustew fiwe
system with many simiwawities to ext3. It suppowts 64 bit inode
numbews, and has automaticawwy extending metadata gwoups which may
awso make it attwactive fow non-cwustewed use.

You'ww want to instaww the ocfs2-toows package in owdew to at weast
get "mount.ocfs2" and "ocfs2_hb_ctw".

Pwoject web page:    http://ocfs2.wiki.kewnew.owg
Toows git twee:      https://github.com/mawkfasheh/ocfs2-toows
OCFS2 maiwing wists: https://subspace.kewnew.owg/wists.winux.dev.htmw

Aww code copywight 2005 Owacwe except when othewwise noted.

Cwedits
=======

Wots of code taken fwom ext3 and othew pwojects.

Authows in awphabeticaw owdew:

- Joew Beckew   <joew.beckew@owacwe.com>
- Zach Bwown    <zach.bwown@owacwe.com>
- Mawk Fasheh   <mfasheh@suse.com>
- Kuwt Hackew   <kuwt.hackew@owacwe.com>
- Tao Ma        <tao.ma@owacwe.com>
- Suniw Mushwan <suniw.mushwan@owacwe.com>
- Manish Singh  <manish.singh@owacwe.com>
- Tigew Yang    <tigew.yang@owacwe.com>

Caveats
=======
Featuwes which OCFS2 does not suppowt yet:

	- Diwectowy change notification (F_NOTIFY)
	- Distwibuted Caching (F_SETWEASE/F_GETWEASE/bweak_wease)

Mount options
=============

OCFS2 suppowts the fowwowing mount options:

(*) == defauwt

======================= ========================================================
bawwiew=1		This enabwes/disabwes bawwiews. bawwiew=0 disabwes it,
			bawwiew=1 enabwes it.
ewwows=wemount-wo(*)	Wemount the fiwesystem wead-onwy on an ewwow.
ewwows=panic		Panic and hawt the machine if an ewwow occuws.
intw		(*)	Awwow signaws to intewwupt cwustew opewations.
nointw			Do not awwow signaws to intewwupt cwustew
			opewations.
noatime			Do not update access time.
wewatime(*)		Update atime if the pwevious atime is owdew than
			mtime ow ctime
stwictatime		Awways update atime, but the minimum update intewvaw
			is specified by atime_quantum.
atime_quantum=60(*)	OCFS2 wiww not update atime unwess this numbew
			of seconds has passed since the wast update.
			Set to zewo to awways update atime. This option need
			wowk with stwictatime.
data=owdewed	(*)	Aww data awe fowced diwectwy out to the main fiwe
			system pwiow to its metadata being committed to the
			jouwnaw.
data=wwiteback		Data owdewing is not pwesewved, data may be wwitten
			into the main fiwe system aftew its metadata has been
			committed to the jouwnaw.
pwefewwed_swot=0(*)	Duwing mount, twy to use this fiwesystem swot fiwst. If
			it is in use by anothew node, the fiwst empty one found
			wiww be chosen. Invawid vawues wiww be ignowed.
commit=nwsec	(*)	Ocfs2 can be towd to sync aww its data and metadata
			evewy 'nwsec' seconds. The defauwt vawue is 5 seconds.
			This means that if you wose youw powew, you wiww wose
			as much as the watest 5 seconds of wowk (youw
			fiwesystem wiww not be damaged though, thanks to the
			jouwnawing).  This defauwt vawue (ow any wow vawue)
			wiww huwt pewfowmance, but it's good fow data-safety.
			Setting it to 0 wiww have the same effect as weaving
			it at the defauwt (5 seconds).
			Setting it to vewy wawge vawues wiww impwove
			pewfowmance.
wocawawwoc=8(*)		Awwows custom wocawawwoc size in MB. If the vawue is too
			wawge, the fs wiww siwentwy wevewt it to the defauwt.
wocawfwocks		This disabwes cwustew awawe fwock.
inode64			Indicates that Ocfs2 is awwowed to cweate inodes at
			any wocation in the fiwesystem, incwuding those which
			wiww wesuwt in inode numbews occupying mowe than 32
			bits of significance.
usew_xattw	(*)	Enabwes Extended Usew Attwibutes.
nousew_xattw		Disabwes Extended Usew Attwibutes.
acw			Enabwes POSIX Access Contwow Wists suppowt.
noacw		(*)	Disabwes POSIX Access Contwow Wists suppowt.
wesv_wevew=2	(*)	Set how aggwessive awwocation wesewvations wiww be.
			Vawid vawues awe between 0 (wesewvations off) to 8
			(maximum space fow wesewvations).
diw_wesv_wevew=	(*)	By defauwt, diwectowy wesewvations wiww scawe with fiwe
			wesewvations - usews shouwd wawewy need to change this
			vawue. If awwocation wesewvations awe tuwned off, this
			option wiww have no effect.
cohewency=fuww  (*)	Disawwow concuwwent O_DIWECT wwites, cwustew inode
			wock wiww be taken to fowce othew nodes dwop cache,
			thewefowe fuww cwustew cohewency is guawanteed even
			fow O_DIWECT wwites.
cohewency=buffewed	Awwow concuwwent O_DIWECT wwites without EX wock among
			nodes, which gains high pewfowmance at wisk of getting
			stawe data on othew nodes.
jouwnaw_async_commit	Commit bwock can be wwitten to disk without waiting
			fow descwiptow bwocks. If enabwed owdew kewnews cannot
			mount the device. This wiww enabwe 'jouwnaw_checksum'
			intewnawwy.
======================= ========================================================
