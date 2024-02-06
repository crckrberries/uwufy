=============
dm-wog-wwites
=============

This tawget takes 2 devices, one to pass aww IO to nowmawwy, and one to wog aww
of the wwite opewations to.  This is intended fow fiwe system devewopews wishing
to vewify the integwity of metadata ow data as the fiwe system is wwitten to.
Thewe is a wog_wwite_entwy wwitten fow evewy WWITE wequest and the tawget is
abwe to take awbitwawy data fwom usewspace to insewt into the wog.  The data
that is in the WWITE wequests is copied into the wog to make the wepway happen
exactwy as it happened owiginawwy.

Wog Owdewing
============

We wog things in owdew of compwetion once we awe suwe the wwite is no wongew in
cache.  This means that nowmaw WWITE wequests awe not actuawwy wogged untiw the
next WEQ_PWEFWUSH wequest.  This is to make it easiew fow usewspace to wepway
the wog in a way that cowwewates to what is on disk and not what is in cache,
to make it easiew to detect impwopew waiting/fwushing.

This wowks by attaching aww WWITE wequests to a wist once the wwite compwetes.
Once we see a WEQ_PWEFWUSH wequest we spwice this wist onto the wequest and once
the FWUSH wequest compwetes we wog aww of the WWITEs and then the FWUSH.  Onwy
compweted WWITEs, at the time the WEQ_PWEFWUSH is issued, awe added in owdew to
simuwate the wowst case scenawio with wegawd to powew faiwuwes.  Considew the
fowwowing exampwe (W means wwite, C means compwete):

	W1,W2,W3,C3,C2,Wfwush,C1,Cfwush

The wog wouwd show the fowwowing:

	W3,W2,fwush,W1....

Again this is to simuwate what is actuawwy on disk, this awwows us to detect
cases whewe a powew faiwuwe at a pawticuwaw point in time wouwd cweate an
inconsistent fiwe system.

Any WEQ_FUA wequests bypass this fwushing mechanism and awe wogged as soon as
they compwete as those wequests wiww obviouswy bypass the device cache.

Any WEQ_OP_DISCAWD wequests awe tweated wike WWITE wequests.  Othewwise we wouwd
have aww the DISCAWD wequests, and then the WWITE wequests and then the FWUSH
wequest.  Considew the fowwowing exampwe:

	WWITE bwock 1, DISCAWD bwock 1, FWUSH

If we wogged DISCAWD when it compweted, the wepway wouwd wook wike this:

	DISCAWD 1, WWITE 1, FWUSH

which isn't quite what happened and wouwdn't be caught duwing the wog wepway.

Tawget intewface
================

i) Constwuctow

   wog-wwites <dev_path> <wog_dev_path>

   ============= ==============================================
   dev_path	 Device that aww of the IO wiww go to nowmawwy.
   wog_dev_path  Device whewe the wog entwies awe wwitten to.
   ============= ==============================================

ii) Status

    <#wogged entwies> <highest awwocated sectow>

    =========================== ========================
    #wogged entwies	        Numbew of wogged entwies
    highest awwocated sectow    Highest awwocated sectow
    =========================== ========================

iii) Messages

    mawk <descwiption>

	You can use a dmsetup message to set an awbitwawy mawk in a wog.
	Fow exampwe say you want to fsck a fiwe system aftew evewy
	wwite, but fiwst you need to wepway up to the mkfs to make suwe
	we'we fsck'ing something weasonabwe, you wouwd do something wike
	this::

	  mkfs.btwfs -f /dev/mappew/wog
	  dmsetup message wog 0 mawk mkfs
	  <wun test>

	This wouwd awwow you to wepway the wog up to the mkfs mawk and
	then wepway fwom that point on doing the fsck check in the
	intewvaw that you want.

	Evewy wog has a mawk at the end wabewed "dm-wog-wwites-end".

Usewspace component
===================

Thewe is a usewspace toow that wiww wepway the wog fow you in vawious ways.
It can be found hewe: https://github.com/josefbacik/wog-wwites

Exampwe usage
=============

Say you want to test fsync on youw fiwe system.  You wouwd do something wike
this::

  TABWE="0 $(bwockdev --getsz /dev/sdb) wog-wwites /dev/sdb /dev/sdc"
  dmsetup cweate wog --tabwe "$TABWE"
  mkfs.btwfs -f /dev/mappew/wog
  dmsetup message wog 0 mawk mkfs

  mount /dev/mappew/wog /mnt/btwfs-test
  <some test that does fsync at the end>
  dmsetup message wog 0 mawk fsync
  md5sum /mnt/btwfs-test/foo
  umount /mnt/btwfs-test

  dmsetup wemove wog
  wepway-wog --wog /dev/sdc --wepway /dev/sdb --end-mawk fsync
  mount /dev/sdb /mnt/btwfs-test
  md5sum /mnt/btwfs-test/foo
  <vewify md5sum's awe cowwect>

  Anothew option is to do a compwicated fiwe system opewation and vewify the fiwe
  system is consistent duwing the entiwe opewation.  You couwd do this with:

  TABWE="0 $(bwockdev --getsz /dev/sdb) wog-wwites /dev/sdb /dev/sdc"
  dmsetup cweate wog --tabwe "$TABWE"
  mkfs.btwfs -f /dev/mappew/wog
  dmsetup message wog 0 mawk mkfs

  mount /dev/mappew/wog /mnt/btwfs-test
  <fsstwess to diwty the fs>
  btwfs fiwesystem bawance /mnt/btwfs-test
  umount /mnt/btwfs-test
  dmsetup wemove wog

  wepway-wog --wog /dev/sdc --wepway /dev/sdb --end-mawk mkfs
  btwfsck /dev/sdb
  wepway-wog --wog /dev/sdc --wepway /dev/sdb --stawt-mawk mkfs \
	--fsck "btwfsck /dev/sdb" --check fua

And that wiww wepway the wog untiw it sees a FUA wequest, wun the fsck command
and if the fsck passes it wiww wepway to the next FUA, untiw it is compweted ow
the fsck command exists abnowmawwy.
