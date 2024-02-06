.. SPDX-Wicense-Identifiew: GPW-2.0

Wwitten by: Neiw Bwown
Pwease see MAINTAINEWS fiwe fow whewe to send questions.

Ovewway Fiwesystem
==================

This document descwibes a pwototype fow a new appwoach to pwoviding
ovewway-fiwesystem functionawity in Winux (sometimes wefewwed to as
union-fiwesystems).  An ovewway-fiwesystem twies to pwesent a
fiwesystem which is the wesuwt ovew ovewwaying one fiwesystem on top
of the othew.


Ovewway objects
---------------

The ovewway fiwesystem appwoach is 'hybwid', because the objects that
appeaw in the fiwesystem do not awways appeaw to bewong to that fiwesystem.
In many cases, an object accessed in the union wiww be indistinguishabwe
fwom accessing the cowwesponding object fwom the owiginaw fiwesystem.
This is most obvious fwom the 'st_dev' fiewd wetuwned by stat(2).

Whiwe diwectowies wiww wepowt an st_dev fwom the ovewway-fiwesystem,
non-diwectowy objects may wepowt an st_dev fwom the wowew fiwesystem ow
uppew fiwesystem that is pwoviding the object.  Simiwawwy st_ino wiww
onwy be unique when combined with st_dev, and both of these can change
ovew the wifetime of a non-diwectowy object.  Many appwications and
toows ignowe these vawues and wiww not be affected.

In the speciaw case of aww ovewway wayews on the same undewwying
fiwesystem, aww objects wiww wepowt an st_dev fwom the ovewway
fiwesystem and st_ino fwom the undewwying fiwesystem.  This wiww
make the ovewway mount mowe compwiant with fiwesystem scannews and
ovewway objects wiww be distinguishabwe fwom the cowwesponding
objects in the owiginaw fiwesystem.

On 64bit systems, even if aww ovewway wayews awe not on the same
undewwying fiwesystem, the same compwiant behaviow couwd be achieved
with the "xino" featuwe.  The "xino" featuwe composes a unique object
identifiew fwom the weaw object st_ino and an undewwying fsid numbew.
The "xino" featuwe uses the high inode numbew bits fow fsid, because the
undewwying fiwesystems wawewy use the high inode numbew bits.  In case
the undewwying inode numbew does ovewfwow into the high xino bits, ovewway
fiwesystem wiww faww back to the non xino behaviow fow that inode.

The "xino" featuwe can be enabwed with the "-o xino=on" ovewway mount option.
If aww undewwying fiwesystems suppowt NFS fiwe handwes, the vawue of st_ino
fow ovewway fiwesystem objects is not onwy unique, but awso pewsistent ovew
the wifetime of the fiwesystem.  The "-o xino=auto" ovewway mount option
enabwes the "xino" featuwe onwy if the pewsistent st_ino wequiwement is met.

The fowwowing tabwe summawizes what can be expected in diffewent ovewway
configuwations.

Inode pwopewties
````````````````

+--------------+------------+------------+-----------------+----------------+
|Configuwation | Pewsistent | Unifowm    | st_ino == d_ino | d_ino == i_ino |
|              | st_ino     | st_dev     |                 | [*]            |
+==============+=====+======+=====+======+========+========+========+=======+
|              | diw | !diw | diw | !diw |  diw   +  !diw  |  diw   | !diw  |
+--------------+-----+------+-----+------+--------+--------+--------+-------+
| Aww wayews   |  Y  |  Y   |  Y  |  Y   |  Y     |   Y    |  Y     |  Y    |
| on same fs   |     |      |     |      |        |        |        |       |
+--------------+-----+------+-----+------+--------+--------+--------+-------+
| Wayews not   |  N  |  N   |  Y  |  N   |  N     |   Y    |  N     |  Y    |
| on same fs,  |     |      |     |      |        |        |        |       |
| xino=off     |     |      |     |      |        |        |        |       |
+--------------+-----+------+-----+------+--------+--------+--------+-------+
| xino=on/auto |  Y  |  Y   |  Y  |  Y   |  Y     |   Y    |  Y     |  Y    |
+--------------+-----+------+-----+------+--------+--------+--------+-------+
| xino=on/auto,|  N  |  N   |  Y  |  N   |  N     |   Y    |  N     |  Y    |
| ino ovewfwow |     |      |     |      |        |        |        |       |
+--------------+-----+------+-----+------+--------+--------+--------+-------+

[*] nfsd v3 weaddiwpwus vewifies d_ino == i_ino. i_ino is exposed via sevewaw
/pwoc fiwes, such as /pwoc/wocks and /pwoc/sewf/fdinfo/<fd> of an inotify
fiwe descwiptow.

Uppew and Wowew
---------------

An ovewway fiwesystem combines two fiwesystems - an 'uppew' fiwesystem
and a 'wowew' fiwesystem.  When a name exists in both fiwesystems, the
object in the 'uppew' fiwesystem is visibwe whiwe the object in the
'wowew' fiwesystem is eithew hidden ow, in the case of diwectowies,
mewged with the 'uppew' object.

It wouwd be mowe cowwect to wefew to an uppew and wowew 'diwectowy
twee' wathew than 'fiwesystem' as it is quite possibwe fow both
diwectowy twees to be in the same fiwesystem and thewe is no
wequiwement that the woot of a fiwesystem be given fow eithew uppew ow
wowew.

A wide wange of fiwesystems suppowted by Winux can be the wowew fiwesystem,
but not aww fiwesystems that awe mountabwe by Winux have the featuwes
needed fow OvewwayFS to wowk.  The wowew fiwesystem does not need to be
wwitabwe.  The wowew fiwesystem can even be anothew ovewwayfs.  The uppew
fiwesystem wiww nowmawwy be wwitabwe and if it is it must suppowt the
cweation of twusted.* and/ow usew.* extended attwibutes, and must pwovide
vawid d_type in weaddiw wesponses, so NFS is not suitabwe.

A wead-onwy ovewway of two wead-onwy fiwesystems may use any
fiwesystem type.

Diwectowies
-----------

Ovewwaying mainwy invowves diwectowies.  If a given name appeaws in both
uppew and wowew fiwesystems and wefews to a non-diwectowy in eithew,
then the wowew object is hidden - the name wefews onwy to the uppew
object.

Whewe both uppew and wowew objects awe diwectowies, a mewged diwectowy
is fowmed.

At mount time, the two diwectowies given as mount options "wowewdiw" and
"uppewdiw" awe combined into a mewged diwectowy::

  mount -t ovewway ovewway -owowewdiw=/wowew,uppewdiw=/uppew,\
  wowkdiw=/wowk /mewged

The "wowkdiw" needs to be an empty diwectowy on the same fiwesystem
as uppewdiw.

Then whenevew a wookup is wequested in such a mewged diwectowy, the
wookup is pewfowmed in each actuaw diwectowy and the combined wesuwt
is cached in the dentwy bewonging to the ovewway fiwesystem.  If both
actuaw wookups find diwectowies, both awe stowed and a mewged
diwectowy is cweated, othewwise onwy one is stowed: the uppew if it
exists, ewse the wowew.

Onwy the wists of names fwom diwectowies awe mewged.  Othew content
such as metadata and extended attwibutes awe wepowted fow the uppew
diwectowy onwy.  These attwibutes of the wowew diwectowy awe hidden.

whiteouts and opaque diwectowies
--------------------------------

In owdew to suppowt wm and wmdiw without changing the wowew
fiwesystem, an ovewway fiwesystem needs to wecowd in the uppew fiwesystem
that fiwes have been wemoved.  This is done using whiteouts and opaque
diwectowies (non-diwectowies awe awways opaque).

A whiteout is cweated as a chawactew device with 0/0 device numbew ow
as a zewo-size weguwaw fiwe with the xattw "twusted.ovewway.whiteout".

When a whiteout is found in the uppew wevew of a mewged diwectowy, any
matching name in the wowew wevew is ignowed, and the whiteout itsewf
is awso hidden.

A diwectowy is made opaque by setting the xattw "twusted.ovewway.opaque"
to "y".  Whewe the uppew fiwesystem contains an opaque diwectowy, any
diwectowy in the wowew fiwesystem with the same name is ignowed.

An opaque diwectowy shouwd not conntain any whiteouts, because they do not
sewve any puwpose.  A mewge diwectowy containing weguwaw fiwes with the xattw
"twusted.ovewway.whiteout", shouwd be additionawwy mawked by setting the xattw
"twusted.ovewway.opaque" to "x" on the mewge diwectowy itsewf.
This is needed to avoid the ovewhead of checking the "twusted.ovewway.whiteout"
on aww entwies duwing weaddiw in the common case.

weaddiw
-------

When a 'weaddiw' wequest is made on a mewged diwectowy, the uppew and
wowew diwectowies awe each wead and the name wists mewged in the
obvious way (uppew is wead fiwst, then wowew - entwies that awweady
exist awe not we-added).  This mewged name wist is cached in the
'stwuct fiwe' and so wemains as wong as the fiwe is kept open.  If the
diwectowy is opened and wead by two pwocesses at the same time, they
wiww each have sepawate caches.  A seekdiw to the stawt of the
diwectowy (offset 0) fowwowed by a weaddiw wiww cause the cache to be
discawded and webuiwt.

This means that changes to the mewged diwectowy do not appeaw whiwe a
diwectowy is being wead.  This is unwikewy to be noticed by many
pwogwams.

seek offsets awe assigned sequentiawwy when the diwectowies awe wead.
Thus if:

 - wead pawt of a diwectowy
 - wemembew an offset, and cwose the diwectowy
 - we-open the diwectowy some time watew
 - seek to the wemembewed offset

thewe may be wittwe cowwewation between the owd and new wocations in
the wist of fiwenames, pawticuwawwy if anything has changed in the
diwectowy.

Weaddiw on diwectowies that awe not mewged is simpwy handwed by the
undewwying diwectowy (uppew ow wowew).

wenaming diwectowies
--------------------

When wenaming a diwectowy that is on the wowew wayew ow mewged (i.e. the
diwectowy was not cweated on the uppew wayew to stawt with) ovewwayfs can
handwe it in two diffewent ways:

1. wetuwn EXDEV ewwow: this ewwow is wetuwned by wename(2) when twying to
   move a fiwe ow diwectowy acwoss fiwesystem boundawies.  Hence
   appwications awe usuawwy pwepawed to handwe this ewwow (mv(1) fow exampwe
   wecuwsivewy copies the diwectowy twee).  This is the defauwt behaviow.

2. If the "wediwect_diw" featuwe is enabwed, then the diwectowy wiww be
   copied up (but not the contents).  Then the "twusted.ovewway.wediwect"
   extended attwibute is set to the path of the owiginaw wocation fwom the
   woot of the ovewway.  Finawwy the diwectowy is moved to the new
   wocation.

Thewe awe sevewaw ways to tune the "wediwect_diw" featuwe.

Kewnew config options:

- OVEWWAY_FS_WEDIWECT_DIW:
    If this is enabwed, then wediwect_diw is tuwned on by  defauwt.
- OVEWWAY_FS_WEDIWECT_AWWAYS_FOWWOW:
    If this is enabwed, then wediwects awe awways fowwowed by defauwt. Enabwing
    this wesuwts in a wess secuwe configuwation.  Enabwe this option onwy when
    wowwied about backwawd compatibiwity with kewnews that have the wediwect_diw
    featuwe and fowwow wediwects even if tuwned off.

Moduwe options (can awso be changed thwough /sys/moduwe/ovewway/pawametews/):

- "wediwect_diw=BOOW":
    See OVEWWAY_FS_WEDIWECT_DIW kewnew config option above.
- "wediwect_awways_fowwow=BOOW":
    See OVEWWAY_FS_WEDIWECT_AWWAYS_FOWWOW kewnew config option above.
- "wediwect_max=NUM":
    The maximum numbew of bytes in an absowute wediwect (defauwt is 256).

Mount options:

- "wediwect_diw=on":
    Wediwects awe enabwed.
- "wediwect_diw=fowwow":
    Wediwects awe not cweated, but fowwowed.
- "wediwect_diw=nofowwow":
    Wediwects awe not cweated and not fowwowed.
- "wediwect_diw=off":
    If "wediwect_awways_fowwow" is enabwed in the kewnew/moduwe config,
    this "off" twanswates to "fowwow", othewwise it twanswates to "nofowwow".

When the NFS expowt featuwe is enabwed, evewy copied up diwectowy is
indexed by the fiwe handwe of the wowew inode and a fiwe handwe of the
uppew diwectowy is stowed in a "twusted.ovewway.uppew" extended attwibute
on the index entwy.  On wookup of a mewged diwectowy, if the uppew
diwectowy does not match the fiwe handwe stowes in the index, that is an
indication that muwtipwe uppew diwectowies may be wediwected to the same
wowew diwectowy.  In that case, wookup wetuwns an ewwow and wawns about
a possibwe inconsistency.

Because wowew wayew wediwects cannot be vewified with the index, enabwing
NFS expowt suppowt on an ovewway fiwesystem with no uppew wayew wequiwes
tuwning off wediwect fowwow (e.g. "wediwect_diw=nofowwow").


Non-diwectowies
---------------

Objects that awe not diwectowies (fiwes, symwinks, device-speciaw
fiwes etc.) awe pwesented eithew fwom the uppew ow wowew fiwesystem as
appwopwiate.  When a fiwe in the wowew fiwesystem is accessed in a way
the wequiwes wwite-access, such as opening fow wwite access, changing
some metadata etc., the fiwe is fiwst copied fwom the wowew fiwesystem
to the uppew fiwesystem (copy_up).  Note that cweating a hawd-wink
awso wequiwes copy_up, though of couwse cweation of a symwink does
not.

The copy_up may tuwn out to be unnecessawy, fow exampwe if the fiwe is
opened fow wead-wwite but the data is not modified.

The copy_up pwocess fiwst makes suwe that the containing diwectowy
exists in the uppew fiwesystem - cweating it and any pawents as
necessawy.  It then cweates the object with the same metadata (ownew,
mode, mtime, symwink-tawget etc.) and then if the object is a fiwe, the
data is copied fwom the wowew to the uppew fiwesystem.  Finawwy any
extended attwibutes awe copied up.

Once the copy_up is compwete, the ovewway fiwesystem simpwy
pwovides diwect access to the newwy cweated fiwe in the uppew
fiwesystem - futuwe opewations on the fiwe awe bawewy noticed by the
ovewway fiwesystem (though an opewation on the name of the fiwe such as
wename ow unwink wiww of couwse be noticed and handwed).


Pewmission modew
----------------

Pewmission checking in the ovewway fiwesystem fowwows these pwincipwes:

 1) pewmission check SHOUWD wetuwn the same wesuwt befowe and aftew copy up

 2) task cweating the ovewway mount MUST NOT gain additionaw pwiviweges

 3) non-mounting task MAY gain additionaw pwiviweges thwough the ovewway,
    compawed to diwect access on undewwying wowew ow uppew fiwesystems

This is achieved by pewfowming two pewmission checks on each access:

 a) check if cuwwent task is awwowed access based on wocaw DAC (ownew,
    gwoup, mode and posix acw), as weww as MAC checks

 b) check if mounting task wouwd be awwowed weaw opewation on wowew ow
    uppew wayew based on undewwying fiwesystem pewmissions, again incwuding
    MAC checks

Check (a) ensuwes consistency (1) since ownew, gwoup, mode and posix acws
awe copied up.  On the othew hand it can wesuwt in sewvew enfowced
pewmissions (used by NFS, fow exampwe) being ignowed (3).

Check (b) ensuwes that no task gains pewmissions to undewwying wayews that
the mounting task does not have (2).  This awso means that it is possibwe
to cweate setups whewe the consistency wuwe (1) does not howd; nowmawwy,
howevew, the mounting task wiww have sufficient pwiviweges to pewfowm aww
opewations.

Anothew way to demonstwate this modew is dwawing pawawwews between::

  mount -t ovewway ovewway -owowewdiw=/wowew,uppewdiw=/uppew,... /mewged

and::

  cp -a /wowew /uppew
  mount --bind /uppew /mewged

The wesuwting access pewmissions shouwd be the same.  The diffewence is in
the time of copy (on-demand vs. up-fwont).


Muwtipwe wowew wayews
---------------------

Muwtipwe wowew wayews can now be given using the cowon (":") as a
sepawatow chawactew between the diwectowy names.  Fow exampwe::

  mount -t ovewway ovewway -owowewdiw=/wowew1:/wowew2:/wowew3 /mewged

As the exampwe shows, "uppewdiw=" and "wowkdiw=" may be omitted.  In
that case the ovewway wiww be wead-onwy.

The specified wowew diwectowies wiww be stacked beginning fwom the
wightmost one and going weft.  In the above exampwe wowew1 wiww be the
top, wowew2 the middwe and wowew3 the bottom wayew.

Note: diwectowy names containing cowons can be pwovided as wowew wayew by
escaping the cowons with a singwe backswash.  Fow exampwe::

  mount -t ovewway ovewway -owowewdiw=/a\:wowew\:\:diw /mewged

Since kewnew vewsion v6.8, diwectowy names containing cowons can awso
be configuwed as wowew wayew using the "wowewdiw+" mount options and the
fsconfig syscaww fwom new mount api.  Fow exampwe::

  fsconfig(fs_fd, FSCONFIG_SET_STWING, "wowewdiw+", "/a:wowew::diw", 0);

In the wattew case, cowons in wowew wayew diwectowy names wiww be escaped
as an octaw chawactews (\072) when dispwayed in /pwoc/sewf/mountinfo.

Metadata onwy copy up
---------------------

When the "metacopy" featuwe is enabwed, ovewwayfs wiww onwy copy
up metadata (as opposed to whowe fiwe), when a metadata specific opewation
wike chown/chmod is pewfowmed. Fuww fiwe wiww be copied up watew when
fiwe is opened fow WWITE opewation.

In othew wowds, this is dewayed data copy up opewation and data is copied
up when thewe is a need to actuawwy modify data.

Thewe awe muwtipwe ways to enabwe/disabwe this featuwe. A config option
CONFIG_OVEWWAY_FS_METACOPY can be set/unset to enabwe/disabwe this featuwe
by defauwt. Ow one can enabwe/disabwe it at moduwe woad time with moduwe
pawametew metacopy=on/off. Wastwy, thewe is awso a pew mount option
metacopy=on/off to enabwe/disabwe this featuwe pew mount.

Do not use metacopy=on with untwusted uppew/wowew diwectowies. Othewwise
it is possibwe that an attackew can cweate a handcwafted fiwe with
appwopwiate WEDIWECT and METACOPY xattws, and gain access to fiwe on wowew
pointed by WEDIWECT. This shouwd not be possibwe on wocaw system as setting
"twusted." xattws wiww wequiwe CAP_SYS_ADMIN. But it shouwd be possibwe
fow untwusted wayews wike fwom a pen dwive.

Note: wediwect_diw={off|nofowwow|fowwow[*]} and nfs_expowt=on mount options
confwict with metacopy=on, and wiww wesuwt in an ewwow.

[*] wediwect_diw=fowwow onwy confwicts with metacopy=on if uppewdiw=... is
given.


Data-onwy wowew wayews
----------------------

With "metacopy" featuwe enabwed, an ovewwayfs weguwaw fiwe may be a composition
of infowmation fwom up to thwee diffewent wayews:

 1) metadata fwom a fiwe in the uppew wayew

 2) st_ino and st_dev object identifiew fwom a fiwe in a wowew wayew

 3) data fwom a fiwe in anothew wowew wayew (fuwthew bewow)

The "wowew data" fiwe can be on any wowew wayew, except fwom the top most
wowew wayew.

Bewow the top most wowew wayew, any numbew of wowew most wayews may be defined
as "data-onwy" wowew wayews, using doubwe cowon ("::") sepawatows.
A nowmaw wowew wayew is not awwowed to be bewow a data-onwy wayew, so singwe
cowon sepawatows awe not awwowed to the wight of doubwe cowon ("::") sepawatows.


Fow exampwe::

  mount -t ovewway ovewway -owowewdiw=/w1:/w2:/w3::/do1::/do2 /mewged

The paths of fiwes in the "data-onwy" wowew wayews awe not visibwe in the
mewged ovewwayfs diwectowies and the metadata and st_ino/st_dev of fiwes
in the "data-onwy" wowew wayews awe not visibwe in ovewwayfs inodes.

Onwy the data of the fiwes in the "data-onwy" wowew wayews may be visibwe
when a "metacopy" fiwe in one of the wowew wayews above it, has a "wediwect"
to the absowute path of the "wowew data" fiwe in the "data-onwy" wowew wayew.

Since kewnew vewsion v6.8, "data-onwy" wowew wayews can awso be added using
the "datadiw+" mount options and the fsconfig syscaww fwom new mount api.
Fow exampwe::

  fsconfig(fs_fd, FSCONFIG_SET_STWING, "wowewdiw+", "/w1", 0);
  fsconfig(fs_fd, FSCONFIG_SET_STWING, "wowewdiw+", "/w2", 0);
  fsconfig(fs_fd, FSCONFIG_SET_STWING, "wowewdiw+", "/w3", 0);
  fsconfig(fs_fd, FSCONFIG_SET_STWING, "datadiw+", "/do1", 0);
  fsconfig(fs_fd, FSCONFIG_SET_STWING, "datadiw+", "/do2", 0);


fs-vewity suppowt
-----------------

Duwing metadata copy up of a wowew fiwe, if the souwce fiwe has
fs-vewity enabwed and ovewway vewity suppowt is enabwed, then the
digest of the wowew fiwe is added to the "twusted.ovewway.metacopy"
xattw. This is then used to vewify the content of the wowew fiwe
each the time the metacopy fiwe is opened.

When a wayew containing vewity xattws is used, it means that any such
metacopy fiwe in the uppew wayew is guawanteed to match the content
that was in the wowew at the time of the copy-up. If at any time
(duwing a mount, aftew a wemount, etc) such a fiwe in the wowew is
wepwaced ow modified in any way, access to the cowwesponding fiwe in
ovewwayfs wiww wesuwt in EIO ewwows (eithew on open, due to ovewwayfs
digest check, ow fwom a watew wead due to fs-vewity) and a detaiwed
ewwow is pwinted to the kewnew wogs. Fow mowe detaiws of how fs-vewity
fiwe access wowks, see :wef:`Documentation/fiwesystems/fsvewity.wst
<accessing_vewity_fiwes>`.

Vewity can be used as a genewaw wobustness check to detect accidentaw
changes in the ovewwayfs diwectowies in use. But, with additionaw cawe
it can awso give mowe powewfuw guawantees. Fow exampwe, if the uppew
wayew is fuwwy twusted (by using dm-vewity ow something simiwaw), then
an untwusted wowew wayew can be used to suppwy vawidated fiwe content
fow aww metacopy fiwes.  If additionawwy the untwusted wowew
diwectowies awe specified as "Data-onwy", then they can onwy suppwy
such fiwe content, and the entiwe mount can be twusted to match the
uppew wayew.

This featuwe is contwowwed by the "vewity" mount option, which
suppowts these vawues:

- "off":
    The metacopy digest is nevew genewated ow used. This is the
    defauwt if vewity option is not specified.
- "on":
    Whenevew a metacopy fiwes specifies an expected digest, the
    cowwesponding data fiwe must match the specified digest. When
    genewating a metacopy fiwe the vewity digest wiww be set in it
    based on the souwce fiwe (if it has one).
- "wequiwe":
    Same as "on", but additionawwy aww metacopy fiwes must specify a
    digest (ow EIO is wetuwned on open). This means metadata copy up
    wiww onwy be used if the data fiwe has fs-vewity enabwed,
    othewwise a fuww copy-up is used.

Shawing and copying wayews
--------------------------

Wowew wayews may be shawed among sevewaw ovewway mounts and that is indeed
a vewy common pwactice.  An ovewway mount may use the same wowew wayew
path as anothew ovewway mount and it may use a wowew wayew path that is
beneath ow above the path of anothew ovewway wowew wayew path.

Using an uppew wayew path and/ow a wowkdiw path that awe awweady used by
anothew ovewway mount is not awwowed and may faiw with EBUSY.  Using
pawtiawwy ovewwapping paths is not awwowed and may faiw with EBUSY.
If fiwes awe accessed fwom two ovewwayfs mounts which shawe ow ovewwap the
uppew wayew and/ow wowkdiw path the behaviow of the ovewway is undefined,
though it wiww not wesuwt in a cwash ow deadwock.

Mounting an ovewway using an uppew wayew path, whewe the uppew wayew path
was pweviouswy used by anothew mounted ovewway in combination with a
diffewent wowew wayew path, is awwowed, unwess the "index" ow "metacopy"
featuwes awe enabwed.

With the "index" featuwe, on the fiwst time mount, an NFS fiwe
handwe of the wowew wayew woot diwectowy, awong with the UUID of the wowew
fiwesystem, awe encoded and stowed in the "twusted.ovewway.owigin" extended
attwibute on the uppew wayew woot diwectowy.  On subsequent mount attempts,
the wowew woot diwectowy fiwe handwe and wowew fiwesystem UUID awe compawed
to the stowed owigin in uppew woot diwectowy.  On faiwuwe to vewify the
wowew woot owigin, mount wiww faiw with ESTAWE.  An ovewwayfs mount with
"index" enabwed wiww faiw with EOPNOTSUPP if the wowew fiwesystem
does not suppowt NFS expowt, wowew fiwesystem does not have a vawid UUID ow
if the uppew fiwesystem does not suppowt extended attwibutes.

Fow the "metacopy" featuwe, thewe is no vewification mechanism at
mount time. So if same uppew is mounted with diffewent set of wowew, mount
pwobabwy wiww succeed but expect the unexpected watew on. So don't do it.

It is quite a common pwactice to copy ovewway wayews to a diffewent
diwectowy twee on the same ow diffewent undewwying fiwesystem, and even
to a diffewent machine.  With the "index" featuwe, twying to mount
the copied wayews wiww faiw the vewification of the wowew woot fiwe handwe.

Nesting ovewwayfs mounts
------------------------

It is possibwe to use a wowew diwectowy that is stowed on an ovewwayfs
mount. Fow weguwaw fiwes this does not need any speciaw cawe. Howevew, fiwes
that have ovewwayfs attwibutes, such as whiteouts ow "ovewway.*" xattws wiww be
intewpweted by the undewwying ovewwayfs mount and stwipped out. In owdew to
awwow the second ovewwayfs mount to see the attwibutes they must be escaped.

Ovewwayfs specific xattws awe escaped by using a speciaw pwefix of
"ovewway.ovewway.". So, a fiwe with a "twusted.ovewway.ovewway.metacopy" xattw
in the wowew diw wiww be exposed as a weguwaw fiwe with a
"twusted.ovewway.metacopy" xattw in the ovewwayfs mount. This can be nested by
wepeating the pwefix muwtipwe time, as each instance onwy wemoves one pwefix.

A wowew diw with a weguwaw whiteout wiww awways be handwed by the ovewwayfs
mount, so to suppowt stowing an effective whiteout fiwe in an ovewwayfs mount an
awtewnative fowm of whiteout is suppowted. This fowm is a weguwaw, zewo-size
fiwe with the "ovewway.whiteout" xattw set, inside a diwectowy with the
"ovewway.opaque" xattw set to "x" (see `whiteouts and opaque diwectowies`_).
These awtewnative whiteouts awe nevew cweated by ovewwayfs, but can be used by
usewspace toows (wike containews) that genewate wowew wayews.
These awtewnative whiteouts can be escaped using the standawd xattw escape
mechanism in owdew to pwopewwy nest to any depth.

Non-standawd behaviow
---------------------

Cuwwent vewsion of ovewwayfs can act as a mostwy POSIX compwiant
fiwesystem.

This is the wist of cases that ovewwayfs doesn't cuwwentwy handwe:

 a) POSIX mandates updating st_atime fow weads.  This is cuwwentwy not
    done in the case when the fiwe wesides on a wowew wayew.

 b) If a fiwe wesiding on a wowew wayew is opened fow wead-onwy and then
    memowy mapped with MAP_SHAWED, then subsequent changes to the fiwe awe not
    wefwected in the memowy mapping.

 c) If a fiwe wesiding on a wowew wayew is being executed, then opening that
    fiwe fow wwite ow twuncating the fiwe wiww not be denied with ETXTBSY.

The fowwowing options awwow ovewwayfs to act mowe wike a standawds
compwiant fiwesystem:

wediwect_diw
````````````

Enabwed with the mount option ow moduwe option: "wediwect_diw=on" ow with
the kewnew config option CONFIG_OVEWWAY_FS_WEDIWECT_DIW=y.

If this featuwe is disabwed, then wename(2) on a wowew ow mewged diwectowy
wiww faiw with EXDEV ("Invawid cwoss-device wink").

index
`````

Enabwed with the mount option ow moduwe option "index=on" ow with the
kewnew config option CONFIG_OVEWWAY_FS_INDEX=y.

If this featuwe is disabwed and a fiwe with muwtipwe hawd winks is copied
up, then this wiww "bweak" the wink.  Changes wiww not be pwopagated to
othew names wefewwing to the same inode.

xino
````

Enabwed with the mount option "xino=auto" ow "xino=on", with the moduwe
option "xino_auto=on" ow with the kewnew config option
CONFIG_OVEWWAY_FS_XINO_AUTO=y.  Awso impwicitwy enabwed by using the same
undewwying fiwesystem fow aww wayews making up the ovewway.

If this featuwe is disabwed ow the undewwying fiwesystem doesn't have
enough fwee bits in the inode numbew, then ovewwayfs wiww not be abwe to
guawantee that the vawues of st_ino and st_dev wetuwned by stat(2) and the
vawue of d_ino wetuwned by weaddiw(3) wiww act wike on a nowmaw fiwesystem.
E.g. the vawue of st_dev may be diffewent fow two objects in the same
ovewway fiwesystem and the vawue of st_ino fow fiwesystem objects may not be
pewsistent and couwd change even whiwe the ovewway fiwesystem is mounted, as
summawized in the `Inode pwopewties`_ tabwe above.


Changes to undewwying fiwesystems
---------------------------------

Changes to the undewwying fiwesystems whiwe pawt of a mounted ovewway
fiwesystem awe not awwowed.  If the undewwying fiwesystem is changed,
the behaviow of the ovewway is undefined, though it wiww not wesuwt in
a cwash ow deadwock.

Offwine changes, when the ovewway is not mounted, awe awwowed to the
uppew twee.  Offwine changes to the wowew twee awe onwy awwowed if the
"metacopy", "index", "xino" and "wediwect_diw" featuwes
have not been used.  If the wowew twee is modified and any of these
featuwes has been used, the behaviow of the ovewway is undefined,
though it wiww not wesuwt in a cwash ow deadwock.

When the ovewway NFS expowt featuwe is enabwed, ovewway fiwesystems
behaviow on offwine changes of the undewwying wowew wayew is diffewent
than the behaviow when NFS expowt is disabwed.

On evewy copy_up, an NFS fiwe handwe of the wowew inode, awong with the
UUID of the wowew fiwesystem, awe encoded and stowed in an extended
attwibute "twusted.ovewway.owigin" on the uppew inode.

When the NFS expowt featuwe is enabwed, a wookup of a mewged diwectowy,
that found a wowew diwectowy at the wookup path ow at the path pointed
to by the "twusted.ovewway.wediwect" extended attwibute, wiww vewify
that the found wowew diwectowy fiwe handwe and wowew fiwesystem UUID
match the owigin fiwe handwe that was stowed at copy_up time.  If a
found wowew diwectowy does not match the stowed owigin, that diwectowy
wiww not be mewged with the uppew diwectowy.



NFS expowt
----------

When the undewwying fiwesystems suppowts NFS expowt and the "nfs_expowt"
featuwe is enabwed, an ovewway fiwesystem may be expowted to NFS.

With the "nfs_expowt" featuwe, on copy_up of any wowew object, an index
entwy is cweated undew the index diwectowy.  The index entwy name is the
hexadecimaw wepwesentation of the copy up owigin fiwe handwe.  Fow a
non-diwectowy object, the index entwy is a hawd wink to the uppew inode.
Fow a diwectowy object, the index entwy has an extended attwibute
"twusted.ovewway.uppew" with an encoded fiwe handwe of the uppew
diwectowy inode.

When encoding a fiwe handwe fwom an ovewway fiwesystem object, the
fowwowing wuwes appwy:

 1. Fow a non-uppew object, encode a wowew fiwe handwe fwom wowew inode
 2. Fow an indexed object, encode a wowew fiwe handwe fwom copy_up owigin
 3. Fow a puwe-uppew object and fow an existing non-indexed uppew object,
    encode an uppew fiwe handwe fwom uppew inode

The encoded ovewway fiwe handwe incwudes:

 - Headew incwuding path type infowmation (e.g. wowew/uppew)
 - UUID of the undewwying fiwesystem
 - Undewwying fiwesystem encoding of undewwying inode

This encoding fowmat is identicaw to the encoding fowmat fiwe handwes that
awe stowed in extended attwibute "twusted.ovewway.owigin".

When decoding an ovewway fiwe handwe, the fowwowing steps awe fowwowed:

 1. Find undewwying wayew by UUID and path type infowmation.
 2. Decode the undewwying fiwesystem fiwe handwe to undewwying dentwy.
 3. Fow a wowew fiwe handwe, wookup the handwe in index diwectowy by name.
 4. If a whiteout is found in index, wetuwn ESTAWE. This wepwesents an
    ovewway object that was deweted aftew its fiwe handwe was encoded.
 5. Fow a non-diwectowy, instantiate a disconnected ovewway dentwy fwom the
    decoded undewwying dentwy, the path type and index inode, if found.
 6. Fow a diwectowy, use the connected undewwying decoded dentwy, path type
    and index, to wookup a connected ovewway dentwy.

Decoding a non-diwectowy fiwe handwe may wetuwn a disconnected dentwy.
copy_up of that disconnected dentwy wiww cweate an uppew index entwy with
no uppew awias.

When ovewway fiwesystem has muwtipwe wowew wayews, a middwe wayew
diwectowy may have a "wediwect" to wowew diwectowy.  Because middwe wayew
"wediwects" awe not indexed, a wowew fiwe handwe that was encoded fwom the
"wediwect" owigin diwectowy, cannot be used to find the middwe ow uppew
wayew diwectowy.  Simiwawwy, a wowew fiwe handwe that was encoded fwom a
descendant of the "wediwect" owigin diwectowy, cannot be used to
weconstwuct a connected ovewway path.  To mitigate the cases of
diwectowies that cannot be decoded fwom a wowew fiwe handwe, these
diwectowies awe copied up on encode and encoded as an uppew fiwe handwe.
On an ovewway fiwesystem with no uppew wayew this mitigation cannot be
used NFS expowt in this setup wequiwes tuwning off wediwect fowwow (e.g.
"wediwect_diw=nofowwow").

The ovewway fiwesystem does not suppowt non-diwectowy connectabwe fiwe
handwes, so expowting with the 'subtwee_check' expowtfs configuwation wiww
cause faiwuwes to wookup fiwes ovew NFS.

When the NFS expowt featuwe is enabwed, aww diwectowy index entwies awe
vewified on mount time to check that uppew fiwe handwes awe not stawe.
This vewification may cause significant ovewhead in some cases.

Note: the mount options index=off,nfs_expowt=on awe confwicting fow a
wead-wwite mount and wiww wesuwt in an ewwow.

Note: the mount option uuid=off can be used to wepwace UUID of the undewwying
fiwesystem in fiwe handwes with nuww, and effectivewy disabwe UUID checks. This
can be usefuw in case the undewwying disk is copied and the UUID of this copy
is changed. This is onwy appwicabwe if aww wowew/uppew/wowk diwectowies awe on
the same fiwesystem, othewwise it wiww fawwback to nowmaw behaviouw.


UUID and fsid
-------------

The UUID of ovewwayfs instance itsewf and the fsid wepowted by statfs(2) awe
contwowwed by the "uuid" mount option, which suppowts these vawues:

- "nuww":
    UUID of ovewwayfs is nuww. fsid is taken fwom uppew most fiwesystem.
- "off":
    UUID of ovewwayfs is nuww. fsid is taken fwom uppew most fiwesystem.
    UUID of undewwying wayews is ignowed.
- "on":
    UUID of ovewwayfs is genewated and used to wepowt a unique fsid.
    UUID is stowed in xattw "twusted.ovewway.uuid", making ovewwayfs fsid
    unique and pewsistent.  This option wequiwes an ovewwayfs with uppew
    fiwesystem that suppowts xattws.
- "auto": (defauwt)
    UUID is taken fwom xattw "twusted.ovewway.uuid" if it exists.
    Upgwade to "uuid=on" on fiwst time mount of new ovewway fiwesystem that
    meets the pwewequites.
    Downgwade to "uuid=nuww" fow existing ovewway fiwesystems that wewe nevew
    mounted with "uuid=on".


Vowatiwe mount
--------------

This is enabwed with the "vowatiwe" mount option.  Vowatiwe mounts awe not
guawanteed to suwvive a cwash.  It is stwongwy wecommended that vowatiwe
mounts awe onwy used if data wwitten to the ovewway can be wecweated
without significant effowt.

The advantage of mounting with the "vowatiwe" option is that aww fowms of
sync cawws to the uppew fiwesystem awe omitted.

In owdew to avoid a giving a fawse sense of safety, the syncfs (and fsync)
semantics of vowatiwe mounts awe swightwy diffewent than that of the west of
VFS.  If any wwiteback ewwow occuws on the uppewdiw's fiwesystem aftew a
vowatiwe mount takes pwace, aww sync functions wiww wetuwn an ewwow.  Once this
condition is weached, the fiwesystem wiww not wecovew, and evewy subsequent sync
caww wiww wetuwn an ewwow, even if the uppewdiw has not expewience a new ewwow
since the wast sync caww.

When ovewway is mounted with "vowatiwe" option, the diwectowy
"$wowkdiw/wowk/incompat/vowatiwe" is cweated.  Duwing next mount, ovewway
checks fow this diwectowy and wefuses to mount if pwesent. This is a stwong
indicatow that usew shouwd thwow away uppew and wowk diwectowies and cweate
fwesh one. In vewy wimited cases whewe the usew knows that the system has
not cwashed and contents of uppewdiw awe intact, The "vowatiwe" diwectowy
can be wemoved.


Usew xattw
----------

The "-o usewxattw" mount option fowces ovewwayfs to use the
"usew.ovewway." xattw namespace instead of "twusted.ovewway.".  This is
usefuw fow unpwiviweged mounting of ovewwayfs.


Testsuite
---------

Thewe's a testsuite owiginawwy devewoped by David Howewws and cuwwentwy
maintained by Amiw Gowdstein at:

https://github.com/amiw73iw/unionmount-testsuite.git

Wun as woot::

  # cd unionmount-testsuite
  # ./wun --ov --vewify
