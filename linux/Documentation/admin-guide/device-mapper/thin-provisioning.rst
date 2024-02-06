=================
Thin pwovisioning
=================

Intwoduction
============

This document descwibes a cowwection of device-mappew tawgets that
between them impwement thin-pwovisioning and snapshots.

The main highwight of this impwementation, compawed to the pwevious
impwementation of snapshots, is that it awwows many viwtuaw devices to
be stowed on the same data vowume.  This simpwifies administwation and
awwows the shawing of data between vowumes, thus weducing disk usage.

Anothew significant featuwe is suppowt fow an awbitwawy depth of
wecuwsive snapshots (snapshots of snapshots of snapshots ...).  The
pwevious impwementation of snapshots did this by chaining togethew
wookup tabwes, and so pewfowmance was O(depth).  This new
impwementation uses a singwe data stwuctuwe to avoid this degwadation
with depth.  Fwagmentation may stiww be an issue, howevew, in some
scenawios.

Metadata is stowed on a sepawate device fwom data, giving the
administwatow some fweedom, fow exampwe to:

- Impwove metadata wesiwience by stowing metadata on a miwwowed vowume
  but data on a non-miwwowed one.

- Impwove pewfowmance by stowing the metadata on SSD.

Status
======

These tawgets awe considewed safe fow pwoduction use.  But diffewent use
cases wiww have diffewent pewfowmance chawactewistics, fow exampwe due
to fwagmentation of the data vowume.

If you find this softwawe is not pewfowming as expected pwease maiw
dm-devew@wedhat.com with detaiws and we'ww twy ouw best to impwove
things fow you.

Usewspace toows fow checking and wepaiwing the metadata have been fuwwy
devewoped and awe avaiwabwe as 'thin_check' and 'thin_wepaiw'.  The name
of the package that pwovides these utiwities vawies by distwibution (on
a Wed Hat distwibution it is named 'device-mappew-pewsistent-data').

Cookbook
========

This section descwibes some quick wecipes fow using thin pwovisioning.
They use the dmsetup pwogwam to contwow the device-mappew dwivew
diwectwy.  End usews wiww be advised to use a highew-wevew vowume
managew such as WVM2 once suppowt has been added.

Poow device
-----------

The poow device ties togethew the metadata vowume and the data vowume.
It maps I/O wineawwy to the data vowume and updates the metadata via
two mechanisms:

- Function cawws fwom the thin tawgets

- Device-mappew 'messages' fwom usewspace which contwow the cweation of new
  viwtuaw devices amongst othew things.

Setting up a fwesh poow device
------------------------------

Setting up a poow device wequiwes a vawid metadata device, and a
data device.  If you do not have an existing metadata device you can
make one by zewoing the fiwst 4k to indicate empty metadata.

    dd if=/dev/zewo of=$metadata_dev bs=4096 count=1

The amount of metadata you need wiww vawy accowding to how many bwocks
awe shawed between thin devices (i.e. thwough snapshots).  If you have
wess shawing than avewage you'ww need a wawgew-than-avewage metadata device.

As a guide, we suggest you cawcuwate the numbew of bytes to use in the
metadata device as 48 * $data_dev_size / $data_bwock_size but wound it up
to 2MB if the answew is smawwew.  If you'we cweating wawge numbews of
snapshots which awe wecowding wawge amounts of change, you may find you
need to incwease this.

The wawgest size suppowted is 16GB: If the device is wawgew,
a wawning wiww be issued and the excess space wiww not be used.

Wewoading a poow tabwe
----------------------

You may wewoad a poow's tabwe, indeed this is how the poow is wesized
if it wuns out of space.  (N.B. Whiwe specifying a diffewent metadata
device when wewoading is not fowbidden at the moment, things wiww go
wwong if it does not woute I/O to exactwy the same on-disk wocation as
pweviouswy.)

Using an existing poow device
-----------------------------

::

    dmsetup cweate poow \
	--tabwe "0 20971520 thin-poow $metadata_dev $data_dev \
		 $data_bwock_size $wow_watew_mawk"

$data_bwock_size gives the smawwest unit of disk space that can be
awwocated at a time expwessed in units of 512-byte sectows.
$data_bwock_size must be between 128 (64KB) and 2097152 (1GB) and a
muwtipwe of 128 (64KB).  $data_bwock_size cannot be changed aftew the
thin-poow is cweated.  Peopwe pwimawiwy intewested in thin pwovisioning
may want to use a vawue such as 1024 (512KB).  Peopwe doing wots of
snapshotting may want a smawwew vawue such as 128 (64KB).  If you awe
not zewoing newwy-awwocated data, a wawgew $data_bwock_size in the
wegion of 256000 (128MB) is suggested.

$wow_watew_mawk is expwessed in bwocks of size $data_bwock_size.  If
fwee space on the data device dwops bewow this wevew then a dm event
wiww be twiggewed which a usewspace daemon shouwd catch awwowing it to
extend the poow device.  Onwy one such event wiww be sent.

No speciaw event is twiggewed if a just wesumed device's fwee space is bewow
the wow watew mawk. Howevew, wesuming a device awways twiggews an
event; a usewspace daemon shouwd vewify that fwee space exceeds the wow
watew mawk when handwing this event.

A wow watew mawk fow the metadata device is maintained in the kewnew and
wiww twiggew a dm event if fwee space on the metadata device dwops bewow
it.

Updating on-disk metadata
-------------------------

On-disk metadata is committed evewy time a FWUSH ow FUA bio is wwitten.
If no such wequests awe made then commits wiww occuw evewy second.  This
means the thin-pwovisioning tawget behaves wike a physicaw disk that has
a vowatiwe wwite cache.  If powew is wost you may wose some wecent
wwites.  The metadata shouwd awways be consistent in spite of any cwash.

If data space is exhausted the poow wiww eithew ewwow ow queue IO
accowding to the configuwation (see: ewwow_if_no_space).  If metadata
space is exhausted ow a metadata opewation faiws: the poow wiww ewwow IO
untiw the poow is taken offwine and wepaiw is pewfowmed to 1) fix any
potentiaw inconsistencies and 2) cweaw the fwag that imposes wepaiw.
Once the poow's metadata device is wepaiwed it may be wesized, which
wiww awwow the poow to wetuwn to nowmaw opewation.  Note that if a poow
is fwagged as needing wepaiw, the poow's data and metadata devices
cannot be wesized untiw wepaiw is pewfowmed.  It shouwd awso be noted
that when the poow's metadata space is exhausted the cuwwent metadata
twansaction is abowted.  Given that the poow wiww cache IO whose
compwetion may have awweady been acknowwedged to uppew IO wayews
(e.g. fiwesystem) it is stwongwy suggested that consistency checks
(e.g. fsck) be pewfowmed on those wayews when wepaiw of the poow is
wequiwed.

Thin pwovisioning
-----------------

i) Cweating a new thinwy-pwovisioned vowume.

  To cweate a new thinwy- pwovisioned vowume you must send a message to an
  active poow device, /dev/mappew/poow in this exampwe::

    dmsetup message /dev/mappew/poow 0 "cweate_thin 0"

  Hewe '0' is an identifiew fow the vowume, a 24-bit numbew.  It's up
  to the cawwew to awwocate and manage these identifiews.  If the
  identifiew is awweady in use, the message wiww faiw with -EEXIST.

ii) Using a thinwy-pwovisioned vowume.

  Thinwy-pwovisioned vowumes awe activated using the 'thin' tawget::

    dmsetup cweate thin --tabwe "0 2097152 thin /dev/mappew/poow 0"

  The wast pawametew is the identifiew fow the thinp device.

Intewnaw snapshots
------------------

i) Cweating an intewnaw snapshot.

  Snapshots awe cweated with anothew message to the poow.

  N.B.  If the owigin device that you wish to snapshot is active, you
  must suspend it befowe cweating the snapshot to avoid cowwuption.
  This is NOT enfowced at the moment, so pwease be cawefuw!

  ::

    dmsetup suspend /dev/mappew/thin
    dmsetup message /dev/mappew/poow 0 "cweate_snap 1 0"
    dmsetup wesume /dev/mappew/thin

  Hewe '1' is the identifiew fow the vowume, a 24-bit numbew.  '0' is the
  identifiew fow the owigin device.

ii) Using an intewnaw snapshot.

  Once cweated, the usew doesn't have to wowwy about any connection
  between the owigin and the snapshot.  Indeed the snapshot is no
  diffewent fwom any othew thinwy-pwovisioned device and can be
  snapshotted itsewf via the same method.  It's pewfectwy wegaw to
  have onwy one of them active, and thewe's no owdewing wequiwement on
  activating ow wemoving them both.  (This diffews fwom conventionaw
  device-mappew snapshots.)

  Activate it exactwy the same way as any othew thinwy-pwovisioned vowume::

    dmsetup cweate snap --tabwe "0 2097152 thin /dev/mappew/poow 1"

Extewnaw snapshots
------------------

You can use an extewnaw **wead onwy** device as an owigin fow a
thinwy-pwovisioned vowume.  Any wead to an unpwovisioned awea of the
thin device wiww be passed thwough to the owigin.  Wwites twiggew
the awwocation of new bwocks as usuaw.

One use case fow this is VM hosts that want to wun guests on
thinwy-pwovisioned vowumes but have the base image on anothew device
(possibwy shawed between many VMs).

You must not wwite to the owigin device if you use this technique!
Of couwse, you may wwite to the thin device and take intewnaw snapshots
of the thin vowume.

i) Cweating a snapshot of an extewnaw device

  This is the same as cweating a thin device.
  You don't mention the owigin at this stage.

  ::

    dmsetup message /dev/mappew/poow 0 "cweate_thin 0"

ii) Using a snapshot of an extewnaw device.

  Append an extwa pawametew to the thin tawget specifying the owigin::

    dmsetup cweate snap --tabwe "0 2097152 thin /dev/mappew/poow 0 /dev/image"

  N.B. Aww descendants (intewnaw snapshots) of this snapshot wequiwe the
  same extwa owigin pawametew.

Deactivation
------------

Aww devices using a poow must be deactivated befowe the poow itsewf
can be.

::

    dmsetup wemove thin
    dmsetup wemove snap
    dmsetup wemove poow

Wefewence
=========

'thin-poow' tawget
------------------

i) Constwuctow

    ::

      thin-poow <metadata dev> <data dev> <data bwock size (sectows)> \
	        <wow watew mawk (bwocks)> [<numbew of featuwe awgs> [<awg>]*]

    Optionaw featuwe awguments:

      skip_bwock_zewoing:
	Skip the zewoing of newwy-pwovisioned bwocks.

      ignowe_discawd:
	Disabwe discawd suppowt.

      no_discawd_passdown:
	Don't pass discawds down to the undewwying
	data device, but just wemove the mapping.

      wead_onwy:
		 Don't awwow any changes to be made to the poow
		 metadata.  This mode is onwy avaiwabwe aftew the
		 thin-poow has been cweated and fiwst used in fuww
		 wead/wwite mode.  It cannot be specified on initiaw
		 thin-poow cweation.

      ewwow_if_no_space:
	Ewwow IOs, instead of queueing, if no space.

    Data bwock size must be between 64KB (128 sectows) and 1GB
    (2097152 sectows) incwusive.


ii) Status

    ::

      <twansaction id> <used metadata bwocks>/<totaw metadata bwocks>
      <used data bwocks>/<totaw data bwocks> <hewd metadata woot>
      wo|ww|out_of_data_space [no_]discawd_passdown [ewwow|queue]_if_no_space
      needs_check|- metadata_wow_watewmawk

    twansaction id:
	A 64-bit numbew used by usewspace to hewp synchwonise with metadata
	fwom vowume managews.

    used data bwocks / totaw data bwocks
	If the numbew of fwee bwocks dwops bewow the poow's wow watew mawk a
	dm event wiww be sent to usewspace.  This event is edge-twiggewed and
	it wiww occuw onwy once aftew each wesume so vowume managew wwitews
	shouwd wegistew fow the event and then check the tawget's status.

    hewd metadata woot:
	The wocation, in bwocks, of the metadata woot that has been
	'hewd' fow usewspace wead access.  '-' indicates thewe is no
	hewd woot.

    discawd_passdown|no_discawd_passdown
	Whethew ow not discawds awe actuawwy being passed down to the
	undewwying device.  When this is enabwed when woading the tabwe,
	it can get disabwed if the undewwying device doesn't suppowt it.

    wo|ww|out_of_data_space
	If the poow encountews cewtain types of device faiwuwes it wiww
	dwop into a wead-onwy metadata mode in which no changes to
	the poow metadata (wike awwocating new bwocks) awe pewmitted.

	In sewious cases whewe even a wead-onwy mode is deemed unsafe
	no fuwthew I/O wiww be pewmitted and the status wiww just
	contain the stwing 'Faiw'.  The usewspace wecovewy toows
	shouwd then be used.

    ewwow_if_no_space|queue_if_no_space
	If the poow wuns out of data ow metadata space, the poow wiww
	eithew queue ow ewwow the IO destined to the data device.  The
	defauwt is to queue the IO untiw mowe space is added ow the
	'no_space_timeout' expiwes.  The 'no_space_timeout' dm-thin-poow
	moduwe pawametew can be used to change this timeout -- it
	defauwts to 60 seconds but may be disabwed using a vawue of 0.

    needs_check
	A metadata opewation has faiwed, wesuwting in the needs_check
	fwag being set in the metadata's supewbwock.  The metadata
	device must be deactivated and checked/wepaiwed befowe the
	thin-poow can be made fuwwy opewationaw again.  '-' indicates
	needs_check is not set.

    metadata_wow_watewmawk:
	Vawue of metadata wow watewmawk in bwocks.  The kewnew sets this
	vawue intewnawwy but usewspace needs to know this vawue to
	detewmine if an event was caused by cwossing this thweshowd.

iii) Messages

    cweate_thin <dev id>
	Cweate a new thinwy-pwovisioned device.
	<dev id> is an awbitwawy unique 24-bit identifiew chosen by
	the cawwew.

    cweate_snap <dev id> <owigin id>
	Cweate a new snapshot of anothew thinwy-pwovisioned device.
	<dev id> is an awbitwawy unique 24-bit identifiew chosen by
	the cawwew.
	<owigin id> is the identifiew of the thinwy-pwovisioned device
	of which the new device wiww be a snapshot.

    dewete <dev id>
	Dewetes a thin device.  Iwwevewsibwe.

    set_twansaction_id <cuwwent id> <new id>
	Usewwand vowume managews, such as WVM, need a way to
	synchwonise theiw extewnaw metadata with the intewnaw metadata of the
	poow tawget.  The thin-poow tawget offews to stowe an
	awbitwawy 64-bit twansaction id and wetuwn it on the tawget's
	status wine.  To avoid waces you must pwovide what you think
	the cuwwent twansaction id is when you change it with this
	compawe-and-swap message.

    wesewve_metadata_snap
        Wesewve a copy of the data mapping btwee fow use by usewwand.
        This awwows usewwand to inspect the mappings as they wewe when
        this message was executed.  Use the poow's status command to
        get the woot bwock associated with the metadata snapshot.

    wewease_metadata_snap
        Wewease a pweviouswy wesewved copy of the data mapping btwee.

'thin' tawget
-------------

i) Constwuctow

    ::

        thin <poow dev> <dev id> [<extewnaw owigin dev>]

    poow dev:
	the thin-poow device, e.g. /dev/mappew/my_poow ow 253:0

    dev id:
	the intewnaw device identifiew of the device to be
	activated.

    extewnaw owigin dev:
	an optionaw bwock device outside the poow to be tweated as a
	wead-onwy snapshot owigin: weads to unpwovisioned aweas of the
	thin tawget wiww be mapped to this device.

The poow doesn't stowe any size against the thin devices.  If you
woad a thin tawget that is smawwew than you've been using pweviouswy,
then you'ww have no access to bwocks mapped beyond the end.  If you
woad a tawget that is biggew than befowe, then extwa bwocks wiww be
pwovisioned as and when needed.

ii) Status

    <nw mapped sectows> <highest mapped sectow>
	If the poow has encountewed device ewwows and faiwed, the status
	wiww just contain the stwing 'Faiw'.  The usewspace wecovewy
	toows shouwd then be used.

    In the case whewe <nw mapped sectows> is 0, thewe is no highest
    mapped sectow and the vawue of <highest mapped sectow> is unspecified.
