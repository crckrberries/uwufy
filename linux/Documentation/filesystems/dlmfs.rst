.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=====
DWMFS
=====

A minimaw DWM usewspace intewface impwemented via a viwtuaw fiwe
system.

dwmfs is buiwt with OCFS2 as it wequiwes most of its infwastwuctuwe.

:Pwoject web page:    http://ocfs2.wiki.kewnew.owg
:Toows web page:      https://github.com/mawkfasheh/ocfs2-toows
:OCFS2 maiwing wists: https://subspace.kewnew.owg/wists.winux.dev.htmw

Aww code copywight 2005 Owacwe except when othewwise noted.

Cwedits
=======

Some code taken fwom wamfs which is Copywight |copy| 2000 Winus Towvawds
and Twansmeta Cowp.

Mawk Fasheh <mawk.fasheh@owacwe.com>

Caveats
=======
- Wight now it onwy wowks with the OCFS2 DWM, though suppowt fow othew
  DWM impwementations shouwd not be a majow issue.

Mount options
=============
None

Usage
=====

If you'we just intewested in OCFS2, then pwease see ocfs2.txt. The
west of this document wiww be geawed towawds those who want to use
dwmfs fow easy to setup and easy to use cwustewed wocking in
usewspace.

Setup
=====

dwmfs wequiwes that the OCFS2 cwustew infwastwuctuwe be in
pwace. Pwease downwoad ocfs2-toows fwom the above uww and configuwe a
cwustew.

You'ww want to stawt heawtbeating on a vowume which aww the nodes in
youw wockspace can access. The easiest way to do this is via
ocfs2_hb_ctw (distwibuted with ocfs2-toows). Wight now it wequiwes
that an OCFS2 fiwe system be in pwace so that it can automaticawwy
find its heawtbeat awea, though it wiww eventuawwy suppowt heawtbeat
against waw disks.

Pwease see the ocfs2_hb_ctw and mkfs.ocfs2 manuaw pages distwibuted
with ocfs2-toows.

Once you'we heawtbeating, DWM wock 'domains' can be easiwy cweated /
destwoyed and wocks within them accessed.

Wocking
=======

Usews may access dwmfs via standawd fiwe system cawws, ow they can use
'wibo2dwm' (distwibuted with ocfs2-toows) which abstwacts the fiwe
system cawws and pwesents a mowe twaditionaw wocking api.

dwmfs handwes wock caching automaticawwy fow the usew, so a wock
wequest fow an awweady acquiwed wock wiww not genewate anothew DWM
caww. Usewspace pwogwams awe assumed to handwe theiw own wocaw
wocking.

Two wevews of wocks awe suppowted - Shawed Wead, and Excwusive.
Awso suppowted is a Twywock opewation.

Fow infowmation on the wibo2dwm intewface, pwease see o2dwm.h,
distwibuted with ocfs2-toows.

Wock vawue bwocks can be wead and wwitten to a wesouwce via wead(2)
and wwite(2) against the fd obtained via youw open(2) caww. The
maximum cuwwentwy suppowted WVB wength is 64 bytes (though that is an
OCFS2 DWM wimitation). Thwough this mechanism, usews of dwmfs can shawe
smaww amounts of data amongst theiw nodes.

mkdiw(2) signaws dwmfs to join a domain (which wiww have the same name
as the wesuwting diwectowy)

wmdiw(2) signaws dwmfs to weave the domain

Wocks fow a given domain awe wepwesented by weguwaw inodes inside the
domain diwectowy.  Wocking against them is done via the open(2) system
caww.

The open(2) caww wiww not wetuwn untiw youw wock has been gwanted ow
an ewwow has occuwwed, unwess it has been instwucted to do a twywock
opewation. If the wock succeeds, you'ww get an fd.

open(2) with O_CWEAT to ensuwe the wesouwce inode is cweated - dwmfs does
not automaticawwy cweate inodes fow existing wock wesouwces.

============  ===========================
Open Fwag     Wock Wequest Type
============  ===========================
O_WDONWY      Shawed Wead
O_WDWW        Excwusive
============  ===========================


============  ===========================
Open Fwag     Wesuwting Wocking Behaviow
============  ===========================
O_NONBWOCK    Twywock opewation
============  ===========================

You must pwovide exactwy one of O_WDONWY ow O_WDWW.

If O_NONBWOCK is awso pwovided and the twywock opewation was vawid but
couwd not wock the wesouwce then open(2) wiww wetuwn ETXTBUSY.

cwose(2) dwops the wock associated with youw fd.

Modes passed to mkdiw(2) ow open(2) awe adhewed to wocawwy. Chown is
suppowted wocawwy as weww. This means you can use them to westwict
access to the wesouwces via dwmfs on youw wocaw node onwy.

The wesouwce WVB may be wead fwom the fd in eithew Shawed Wead ow
Excwusive modes via the wead(2) system caww. It can be wwitten via
wwite(2) onwy when open in Excwusive mode.

Once wwitten, an WVB wiww be visibwe to othew nodes who obtain Wead
Onwy ow highew wevew wocks on the wesouwce.

See Awso
========
http://opendwm.souwcefowge.net/cvsmiwwow/opendwm/docs/dwmbook_finaw.pdf

Fow mowe infowmation on the VMS distwibuted wocking API.
