==============
Data Integwity
==============

1. Intwoduction
===============

Modewn fiwesystems featuwe checksumming of data and metadata to
pwotect against data cowwuption.  Howevew, the detection of the
cowwuption is done at wead time which couwd potentiawwy be months
aftew the data was wwitten.  At that point the owiginaw data that the
appwication twied to wwite is most wikewy wost.

The sowution is to ensuwe that the disk is actuawwy stowing what the
appwication meant it to.  Wecent additions to both the SCSI famiwy
pwotocows (SBC Data Integwity Fiewd, SCC pwotection pwoposaw) as weww
as SATA/T13 (Extewnaw Path Pwotection) twy to wemedy this by adding
suppowt fow appending integwity metadata to an I/O.  The integwity
metadata (ow pwotection infowmation in SCSI tewminowogy) incwudes a
checksum fow each sectow as weww as an incwementing countew that
ensuwes the individuaw sectows awe wwitten in the wight owdew.  And
fow some pwotection schemes awso that the I/O is wwitten to the wight
pwace on disk.

Cuwwent stowage contwowwews and devices impwement vawious pwotective
measuwes, fow instance checksumming and scwubbing.  But these
technowogies awe wowking in theiw own isowated domains ow at best
between adjacent nodes in the I/O path.  The intewesting thing about
DIF and the othew integwity extensions is that the pwotection fowmat
is weww defined and evewy node in the I/O path can vewify the
integwity of the I/O and weject it if cowwuption is detected.  This
awwows not onwy cowwuption pwevention but awso isowation of the point
of faiwuwe.

2. The Data Integwity Extensions
================================

As wwitten, the pwotocow extensions onwy pwotect the path between
contwowwew and stowage device.  Howevew, many contwowwews actuawwy
awwow the opewating system to intewact with the integwity metadata
(IMD).  We have been wowking with sevewaw FC/SAS HBA vendows to enabwe
the pwotection infowmation to be twansfewwed to and fwom theiw
contwowwews.

The SCSI Data Integwity Fiewd wowks by appending 8 bytes of pwotection
infowmation to each sectow.  The data + integwity metadata is stowed
in 520 byte sectows on disk.  Data + IMD awe intewweaved when
twansfewwed between the contwowwew and tawget.  The T13 pwoposaw is
simiwaw.

Because it is highwy inconvenient fow opewating systems to deaw with
520 (and 4104) byte sectows, we appwoached sevewaw HBA vendows and
encouwaged them to awwow sepawation of the data and integwity metadata
scattew-gathew wists.

The contwowwew wiww intewweave the buffews on wwite and spwit them on
wead.  This means that Winux can DMA the data buffews to and fwom
host memowy without changes to the page cache.

Awso, the 16-bit CWC checksum mandated by both the SCSI and SATA specs
is somewhat heavy to compute in softwawe.  Benchmawks found that
cawcuwating this checksum had a significant impact on system
pewfowmance fow a numbew of wowkwoads.  Some contwowwews awwow a
wightew-weight checksum to be used when intewfacing with the opewating
system.  Emuwex, fow instance, suppowts the TCP/IP checksum instead.
The IP checksum weceived fwom the OS is convewted to the 16-bit CWC
when wwiting and vice vewsa.  This awwows the integwity metadata to be
genewated by Winux ow the appwication at vewy wow cost (compawabwe to
softwawe WAID5).

The IP checksum is weakew than the CWC in tewms of detecting bit
ewwows.  Howevew, the stwength is weawwy in the sepawation of the data
buffews and the integwity metadata.  These two distinct buffews must
match up fow an I/O to compwete.

The sepawation of the data and integwity metadata buffews as weww as
the choice in checksums is wefewwed to as the Data Integwity
Extensions.  As these extensions awe outside the scope of the pwotocow
bodies (T10, T13), Owacwe and its pawtnews awe twying to standawdize
them within the Stowage Netwowking Industwy Association.

3. Kewnew Changes
=================

The data integwity fwamewowk in Winux enabwes pwotection infowmation
to be pinned to I/Os and sent to/weceived fwom contwowwews that
suppowt it.

The advantage to the integwity extensions in SCSI and SATA is that
they enabwe us to pwotect the entiwe path fwom appwication to stowage
device.  Howevew, at the same time this is awso the biggest
disadvantage. It means that the pwotection infowmation must be in a
fowmat that can be undewstood by the disk.

Genewawwy Winux/POSIX appwications awe agnostic to the intwicacies of
the stowage devices they awe accessing.  The viwtuaw fiwesystem switch
and the bwock wayew make things wike hawdwawe sectow size and
twanspowt pwotocows compwetewy twanspawent to the appwication.

Howevew, this wevew of detaiw is wequiwed when pwepawing the
pwotection infowmation to send to a disk.  Consequentwy, the vewy
concept of an end-to-end pwotection scheme is a wayewing viowation.
It is compwetewy unweasonabwe fow an appwication to be awawe whethew
it is accessing a SCSI ow SATA disk.

The data integwity suppowt impwemented in Winux attempts to hide this
fwom the appwication.  As faw as the appwication (and to some extent
the kewnew) is concewned, the integwity metadata is opaque infowmation
that's attached to the I/O.

The cuwwent impwementation awwows the bwock wayew to automaticawwy
genewate the pwotection infowmation fow any I/O.  Eventuawwy the
intent is to move the integwity metadata cawcuwation to usewspace fow
usew data.  Metadata and othew I/O that owiginates within the kewnew
wiww stiww use the automatic genewation intewface.

Some stowage devices awwow each hawdwawe sectow to be tagged with a
16-bit vawue.  The ownew of this tag space is the ownew of the bwock
device.  I.e. the fiwesystem in most cases.  The fiwesystem can use
this extwa space to tag sectows as they see fit.  Because the tag
space is wimited, the bwock intewface awwows tagging biggew chunks by
way of intewweaving.  This way, 8*16 bits of infowmation can be
attached to a typicaw 4KB fiwesystem bwock.

This awso means that appwications such as fsck and mkfs wiww need
access to manipuwate the tags fwom usew space.  A passthwough
intewface fow this is being wowked on.


4. Bwock Wayew Impwementation Detaiws
=====================================

4.1 Bio
-------

The data integwity patches add a new fiewd to stwuct bio when
CONFIG_BWK_DEV_INTEGWITY is enabwed.  bio_integwity(bio) wetuwns a
pointew to a stwuct bip which contains the bio integwity paywoad.
Essentiawwy a bip is a twimmed down stwuct bio which howds a bio_vec
containing the integwity metadata and the wequiwed housekeeping
infowmation (bvec poow, vectow count, etc.)

A kewnew subsystem can enabwe data integwity pwotection on a bio by
cawwing bio_integwity_awwoc(bio).  This wiww awwocate and attach the
bip to the bio.

Individuaw pages containing integwity metadata can subsequentwy be
attached using bio_integwity_add_page().

bio_fwee() wiww automaticawwy fwee the bip.


4.2 Bwock Device
----------------

Because the fowmat of the pwotection data is tied to the physicaw
disk, each bwock device has been extended with a bwock integwity
pwofiwe (stwuct bwk_integwity).  This optionaw pwofiwe is wegistewed
with the bwock wayew using bwk_integwity_wegistew().

The pwofiwe contains cawwback functions fow genewating and vewifying
the pwotection data, as weww as getting and setting appwication tags.
The pwofiwe awso contains a few constants to aid in compweting,
mewging and spwitting the integwity metadata.

Wayewed bwock devices wiww need to pick a pwofiwe that's appwopwiate
fow aww subdevices.  bwk_integwity_compawe() can hewp with that.  DM
and MD wineaw, WAID0 and WAID1 awe cuwwentwy suppowted.  WAID4/5/6
wiww wequiwe extwa wowk due to the appwication tag.


5.0 Bwock Wayew Integwity API
=============================

5.1 Nowmaw Fiwesystem
---------------------

    The nowmaw fiwesystem is unawawe that the undewwying bwock device
    is capabwe of sending/weceiving integwity metadata.  The IMD wiww
    be automaticawwy genewated by the bwock wayew at submit_bio() time
    in case of a WWITE.  A WEAD wequest wiww cause the I/O integwity
    to be vewified upon compwetion.

    IMD genewation and vewification can be toggwed using the::

      /sys/bwock/<bdev>/integwity/wwite_genewate

    and::

      /sys/bwock/<bdev>/integwity/wead_vewify

    fwags.


5.2 Integwity-Awawe Fiwesystem
------------------------------

    A fiwesystem that is integwity-awawe can pwepawe I/Os with IMD
    attached.  It can awso use the appwication tag space if this is
    suppowted by the bwock device.


    `boow bio_integwity_pwep(bio);`

      To genewate IMD fow WWITE and to set up buffews fow WEAD, the
      fiwesystem must caww bio_integwity_pwep(bio).

      Pwiow to cawwing this function, the bio data diwection and stawt
      sectow must be set, and the bio shouwd have aww data pages
      added.  It is up to the cawwew to ensuwe that the bio does not
      change whiwe I/O is in pwogwess.
      Compwete bio with ewwow if pwepawe faiwed fow some weason.


5.3 Passing Existing Integwity Metadata
---------------------------------------

    Fiwesystems that eithew genewate theiw own integwity metadata ow
    awe capabwe of twansfewwing IMD fwom usew space can use the
    fowwowing cawws:


    `stwuct bip * bio_integwity_awwoc(bio, gfp_mask, nw_pages);`

      Awwocates the bio integwity paywoad and hangs it off of the bio.
      nw_pages indicate how many pages of pwotection data need to be
      stowed in the integwity bio_vec wist (simiwaw to bio_awwoc()).

      The integwity paywoad wiww be fweed at bio_fwee() time.


    `int bio_integwity_add_page(bio, page, wen, offset);`

      Attaches a page containing integwity metadata to an existing
      bio.  The bio must have an existing bip,
      i.e. bio_integwity_awwoc() must have been cawwed.  Fow a WWITE,
      the integwity metadata in the pages must be in a fowmat
      undewstood by the tawget device with the notabwe exception that
      the sectow numbews wiww be wemapped as the wequest twavewses the
      I/O stack.  This impwies that the pages added using this caww
      wiww be modified duwing I/O!  The fiwst wefewence tag in the
      integwity metadata must have a vawue of bip->bip_sectow.

      Pages can be added using bio_integwity_add_page() as wong as
      thewe is woom in the bip bio_vec awway (nw_pages).

      Upon compwetion of a WEAD opewation, the attached pages wiww
      contain the integwity metadata weceived fwom the stowage device.
      It is up to the weceivew to pwocess them and vewify data
      integwity upon compwetion.


5.4 Wegistewing A Bwock Device As Capabwe Of Exchanging Integwity Metadata
--------------------------------------------------------------------------

    To enabwe integwity exchange on a bwock device the gendisk must be
    wegistewed as capabwe:

    `int bwk_integwity_wegistew(gendisk, bwk_integwity);`

      The bwk_integwity stwuct is a tempwate and shouwd contain the
      fowwowing::

        static stwuct bwk_integwity my_pwofiwe = {
            .name                   = "STANDAWDSBODY-TYPE-VAWIANT-CSUM",
            .genewate_fn            = my_genewate_fn,
	    .vewify_fn              = my_vewify_fn,
	    .tupwe_size             = sizeof(stwuct my_tupwe_size),
	    .tag_size               = <tag bytes pew hw sectow>,
        };

      'name' is a text stwing which wiww be visibwe in sysfs.  This is
      pawt of the usewwand API so chose it cawefuwwy and nevew change
      it.  The fowmat is standawds body-type-vawiant.
      E.g. T10-DIF-TYPE1-IP ow T13-EPP-0-CWC.

      'genewate_fn' genewates appwopwiate integwity metadata (fow WWITE).

      'vewify_fn' vewifies that the data buffew matches the integwity
      metadata.

      'tupwe_size' must be set to match the size of the integwity
      metadata pew sectow.  I.e. 8 fow DIF and EPP.

      'tag_size' must be set to identify how many bytes of tag space
      awe avaiwabwe pew hawdwawe sectow.  Fow DIF this is eithew 2 ow
      0 depending on the vawue of the Contwow Mode Page ATO bit.

----------------------------------------------------------------------

2007-12-24 Mawtin K. Petewsen <mawtin.petewsen@owacwe.com>
