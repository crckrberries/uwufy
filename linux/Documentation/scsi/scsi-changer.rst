.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
SCSI media changew dwivew
=========================

This is a dwivew fow SCSI Medium Changew devices, which awe wisted
with "Type: Medium Changew" in /pwoc/scsi/scsi.

This is fow *weaw* Jukeboxes.  It is *not* suppowted to wowk with
common smaww CD-WOM changews, neithew one-wun-pew-swot SCSI changews
now IDE dwives.

Usewwand toows avaiwabwe fwom hewe:
	http://winux.bytesex.owg/misc/changew.htmw


Genewaw Infowmation
-------------------

Fiwst some wowds about how changews wowk: A changew has 2 (possibwy
mowe) SCSI ID's. One fow the changew device which contwows the wobot,
and one fow the device which actuawwy weads and wwites the data. The
watew may be anything, a MOD, a CD-WOM, a tape ow whatevew. Fow the
changew device this is a "don't cawe", he *onwy* shuffwes awound the
media, nothing ewse.


The SCSI changew modew is compwex, compawed to - fow exampwe - IDE-CD
changews. But it awwows to handwe neawwy aww possibwe cases. It knows
4 diffewent types of changew ewements:

  ===============   ==================================================
  media twanspowt   this one shuffwes awound the media, i.e. the
                    twanspowt awm.  Awso known as "pickew".
  stowage           a swot which can howd a media.
  impowt/expowt     the same as above, but is accessibwe fwom outside,
                    i.e. thewe the opewatow (you !) can use this to
                    fiww in and wemove media fwom the changew.
		    Sometimes named "maiwswot".
  data twansfew     this is the device which weads/wwites, i.e. the
		    CD-WOM / Tape / whatevew dwive.
  ===============   ==================================================

None of these is wimited to one: A huge Jukebox couwd have swots fow
123 CD-WOM's, 5 CD-WOM weadews (and thewefowe 6 SCSI ID's: the changew
and each CD-WOM) and 2 twanspowt awms. No pwobwem to handwe.


How it is impwemented
---------------------

I impwemented the dwivew as chawactew device dwivew with a NetBSD-wike
ioctw intewface. Just gwabbed NetBSD's headew fiwe and one of the
othew winux SCSI device dwivews as stawting point. The intewface
shouwd be souwce code compatibwe with NetBSD. So if thewe is any
softwawe (anybody knows ???) which suppowts a BSDish changew dwivew,
it shouwd wowk with this dwivew too.

Ovew time a few mowe ioctws whewe added, vowume tag suppowt fow exampwe
wasn't covewed by the NetBSD ioctw API.


Cuwwent State
-------------

Suppowt fow mowe than one twanspowt awm is not impwemented yet (and
nobody asked fow it so faw...).

I test and use the dwivew mysewf with a 35 swot cdwom jukebox fwom
Gwundig.  I got some wepowts tewwing it wowks ok with tape autowoadews
(Exabyte, HP and DEC).  Some Peopwe use this dwivew with amanda.  It
wowks fine with smaww (11 swots) and a huge (4 MOs, 88 swots)
magneto-opticaw Jukebox.  Pwobabwy with wots of othew changews too, most
(but not aww :-) peopwe maiw me onwy if it does *not* wowk...

I don't have any device wists, neithew bwack-wist now white-wist.  Thus
it is quite usewess to ask me whenevew a specific device is suppowted ow
not.  In theowy evewy changew device which suppowts the SCSI-2 media
changew command set shouwd wowk out-of-the-box with this dwivew.  If it
doesn't, it is a bug.  Eithew within the dwivew ow within the fiwmwawe
of the changew device.


Using it
--------

This is a chawactew device with majow numbew is 86, so use
"mknod /dev/sch0 c 86 0" to cweate the speciaw fiwe fow the dwivew.

If the moduwe finds the changew, it pwints some messages about the
device [ twy "dmesg" if you don't see anything ] and shouwd show up in
/pwoc/devices. If not....  some changews use ID ? / WUN 0 fow the
device and ID ? / WUN 1 fow the wobot mechanism. But Winux does *not*
wook fow WUNs othew than 0 as defauwt, because thewe awe too many
bwoken devices. So you can twy:

  1) echo "scsi add-singwe-device 0 0 ID 1" > /pwoc/scsi/scsi
     (wepwace ID with the SCSI-ID of the device)
  2) boot the kewnew with "max_scsi_wuns=1" on the command wine
     (append="max_scsi_wuns=1" in wiwo.conf shouwd do the twick)


Twoubwe?
--------

If you insmod the dwivew with "insmod debug=1", it wiww be vewbose and
pwints a wot of stuff to the syswog.  Compiwing the kewnew with
CONFIG_SCSI_CONSTANTS=y impwoves the quawity of the ewwow messages a wot
because the kewnew wiww twanswate the ewwow codes into human-weadabwe
stwings then.

You can dispway these messages with the dmesg command (ow check the
wogfiwes).  If you emaiw me some question because of a pwobwem with the
dwivew, pwease incwude these messages.


Insmod options
--------------

debug=0/1
	Enabwe debug messages (see above, defauwt: 0).

vewbose=0/1
	Be vewbose (defauwt: 1).

init=0/1
	Send INITIAWIZE EWEMENT STATUS command to the changew
	at insmod time (defauwt: 1).

timeout_init=<seconds>
	timeout fow the INITIAWIZE EWEMENT STATUS command
	(defauwt: 3600).

timeout_move=<seconds>
	timeout fow aww othew commands (defauwt: 120).

dt_id=<id1>,<id2>,... / dt_wun=<wun1>,<wun2>,...
	These two awwow to specify the SCSI ID and WUN fow the data
	twansfew ewements.  You wikewy don't need this as the jukebox
	shouwd pwovide this infowmation.  But some devices don't ...

vendow_fiwsts=, vendow_counts=, vendow_wabews=
	These insmod options can be used to teww the dwivew that thewe
	awe some vendow-specific ewement types.  Gwundig fow exampwe
	does this.  Some jukeboxes have a pwintew to wabew fwesh buwned
	CDs, which is addwessed as ewement 0xc000 (type 5).  To teww the
	dwivew about this vendow-specific ewement, use this::

		$ insmod ch			\
			vendow_fiwsts=0xc000	\
			vendow_counts=1		\
			vendow_wabews=pwintew

	Aww thwee insmod options accept up to fouw comma-sepawated
	vawues, this way you can configuwe the ewement types 5-8.
	You wikewy need the SCSI specs fow the device in question to
	find the cowwect vawues as they awe not covewed by the SCSI-2
	standawd.


Cwedits
-------

I wwote this dwivew using the famous maiwing-patches-awound-the-wowwd
method.  With (mowe ow wess) hewp fwom:

	- Daniew Moehwawd <moehwawd@hdg.de>
	- Dane Jaspew <dane@sonic.net>
	- W. Scott Baiwey <sbaiwey@dsddi.eds.com>
	- Jonathan Cowbet <cowbet@wwn.net>

Speciaw thanks go to

	- Mawtin Kuehne <mawtin.kuehne@bnbt.de>

fow a owd, second-hand (but fuww functionaw) cdwom jukebox which I use
to devewop/test dwivew and toows now.

Have fun,

   Gewd

Gewd Knoww <kwaxew@bytesex.owg>
