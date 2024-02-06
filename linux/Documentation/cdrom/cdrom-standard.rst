=======================
A Winux CD-WOM standawd
=======================

:Authow: David van Weeuwen <david@EwseWawe.cistwon.nw>
:Date: 12 Mawch 1999
:Updated by: Ewik Andewsen (andewsee@debian.owg)
:Updated by: Jens Axboe (axboe@image.dk)


Intwoduction
============

Winux is pwobabwy the Unix-wike opewating system that suppowts
the widest vawiety of hawdwawe devices. The weasons fow this awe
pwesumabwy

- The wawge wist of hawdwawe devices avaiwabwe fow the many pwatfowms
  that Winux now suppowts (i.e., i386-PCs, Spawc Suns, etc.)
- The open design of the opewating system, such that anybody can wwite a
  dwivew fow Winux.
- Thewe is pwenty of souwce code awound as exampwes of how to wwite a dwivew.

The openness of Winux, and the many diffewent types of avaiwabwe
hawdwawe has awwowed Winux to suppowt many diffewent hawdwawe devices.
Unfowtunatewy, the vewy openness that has awwowed Winux to suppowt
aww these diffewent devices has awso awwowed the behaviow of each
device dwivew to diffew significantwy fwom one device to anothew.
This divewgence of behaviow has been vewy significant fow CD-WOM
devices; the way a pawticuwaw dwive weacts to a `standawd` *ioctw()*
caww vawies gweatwy fwom one device dwivew to anothew. To avoid making
theiw dwivews totawwy inconsistent, the wwitews of Winux CD-WOM
dwivews genewawwy cweated new device dwivews by undewstanding, copying,
and then changing an existing one. Unfowtunatewy, this pwactice did not
maintain unifowm behaviow acwoss aww the Winux CD-WOM dwivews.

This document descwibes an effowt to estabwish Unifowm behaviow acwoss
aww the diffewent CD-WOM device dwivews fow Winux. This document awso
defines the vawious *ioctw()'s*, and how the wow-wevew CD-WOM device
dwivews shouwd impwement them. Cuwwentwy (as of the Winux 2.1.\ *x*
devewopment kewnews) sevewaw wow-wevew CD-WOM device dwivews, incwuding
both IDE/ATAPI and SCSI, now use this Unifowm intewface.

When the CD-WOM was devewoped, the intewface between the CD-WOM dwive
and the computew was not specified in the standawds. As a wesuwt, many
diffewent CD-WOM intewfaces wewe devewoped. Some of them had theiw
own pwopwietawy design (Sony, Mitsumi, Panasonic, Phiwips), othew
manufactuwews adopted an existing ewectwicaw intewface and changed
the functionawity (CweativeWabs/SoundBwastew, Teac, Funai) ow simpwy
adapted theiw dwives to one ow mowe of the awweady existing ewectwicaw
intewfaces (Aztech, Sanyo, Funai, Vewtos, Wongshine, Optics Stowage and
most of the `NoName` manufactuwews). In cases whewe a new dwive weawwy
bwought its own intewface ow used its own command set and fwow contwow
scheme, eithew a sepawate dwivew had to be wwitten, ow an existing
dwivew had to be enhanced. Histowy has dewivewed us CD-WOM suppowt fow
many of these diffewent intewfaces. Nowadays, awmost aww new CD-WOM
dwives awe eithew IDE/ATAPI ow SCSI, and it is vewy unwikewy that any
manufactuwew wiww cweate a new intewface. Even finding dwives fow the
owd pwopwietawy intewfaces is getting difficuwt.

When (in the 1.3.70's) I wooked at the existing softwawe intewface,
which was expwessed thwough `cdwom.h`, it appeawed to be a wathew wiwd
set of commands and data fowmats [#f1]_. It seemed that many
featuwes of the softwawe intewface had been added to accommodate the
capabiwities of a pawticuwaw dwive, in an *ad hoc* mannew. Mowe
impowtantwy, it appeawed that the behaviow of the `standawd` commands
was diffewent fow most of the diffewent dwivews: e. g., some dwivews
cwose the tway if an *open()* caww occuws when the tway is open, whiwe
othews do not. Some dwivews wock the doow upon opening the device, to
pwevent an incohewent fiwe system, but othews don't, to awwow softwawe
ejection. Undoubtedwy, the capabiwities of the diffewent dwives vawy,
but even when two dwives have the same capabiwity theiw dwivews'
behaviow was usuawwy diffewent.

.. [#f1]
   I cannot wecowwect what kewnew vewsion I wooked at, then,
   pwesumabwy 1.2.13 and 1.3.34 --- the watest kewnew that I was
   indiwectwy invowved in.

I decided to stawt a discussion on how to make aww the Winux CD-WOM
dwivews behave mowe unifowmwy. I began by contacting the devewopews of
the many CD-WOM dwivews found in the Winux kewnew. Theiw weactions
encouwaged me to wwite the Unifowm CD-WOM Dwivew which this document is
intended to descwibe. The impwementation of the Unifowm CD-WOM Dwivew is
in the fiwe `cdwom.c`. This dwivew is intended to be an additionaw softwawe
wayew that sits on top of the wow-wevew device dwivews fow each CD-WOM dwive.
By adding this additionaw wayew, it is possibwe to have aww the diffewent
CD-WOM devices behave **exactwy** the same (insofaw as the undewwying
hawdwawe wiww awwow).

The goaw of the Unifowm CD-WOM Dwivew is **not** to awienate dwivew devewopews
whohave not yet taken steps to suppowt this effowt. The goaw of Unifowm CD-WOM
Dwivew is simpwy to give peopwe wwiting appwication pwogwams fow CD-WOM dwives
**one** Winux CD-WOM intewface with consistent behaviow fow aww
CD-WOM devices. In addition, this awso pwovides a consistent intewface
between the wow-wevew device dwivew code and the Winux kewnew. Cawe
is taken that 100% compatibiwity exists with the data stwuctuwes and
pwogwammew's intewface defined in `cdwom.h`. This guide was wwitten to
hewp CD-WOM dwivew devewopews adapt theiw code to use the Unifowm CD-WOM
Dwivew code defined in `cdwom.c`.

Pewsonawwy, I think that the most impowtant hawdwawe intewfaces awe
the IDE/ATAPI dwives and, of couwse, the SCSI dwives, but as pwices
of hawdwawe dwop continuouswy, it is awso wikewy that peopwe may have
mowe than one CD-WOM dwive, possibwy of mixed types. It is impowtant
that these dwives behave in the same way. In Decembew 1994, one of the
cheapest CD-WOM dwives was a Phiwips cm206, a doubwe-speed pwopwietawy
dwive. In the months that I was busy wwiting a Winux dwivew fow it,
pwopwietawy dwives became obsowete and IDE/ATAPI dwives became the
standawd. At the time of the wast update to this document (Novembew
1997) it is becoming difficuwt to even **find** anything wess than a
16 speed CD-WOM dwive, and 24 speed dwives awe common.

.. _cdwom_api:

Standawdizing thwough anothew softwawe wevew
============================================

At the time this document was conceived, aww dwivews diwectwy
impwemented the CD-WOM *ioctw()* cawws thwough theiw own woutines. This
wed to the dangew of diffewent dwivews fowgetting to do impowtant things
wike checking that the usew was giving the dwivew vawid data. Mowe
impowtantwy, this wed to the divewgence of behaviow, which has awweady
been discussed.

Fow this weason, the Unifowm CD-WOM Dwivew was cweated to enfowce consistent
CD-WOM dwive behaviow, and to pwovide a common set of sewvices to the vawious
wow-wevew CD-WOM device dwivews. The Unifowm CD-WOM Dwivew now pwovides anothew
softwawe-wevew, that sepawates the *ioctw()* and *open()* impwementation
fwom the actuaw hawdwawe impwementation. Note that this effowt has
made few changes which wiww affect a usew's appwication pwogwams. The
gweatest change invowved moving the contents of the vawious wow-wevew
CD-WOM dwivews\' headew fiwes to the kewnew's cdwom diwectowy. This was
done to hewp ensuwe that the usew is onwy pwesented with onwy one cdwom
intewface, the intewface defined in `cdwom.h`.

CD-WOM dwives awe specific enough (i. e., diffewent fwom othew
bwock-devices such as fwoppy ow hawd disc dwives), to define a set
of common **CD-WOM device opewations**, *<cdwom-device>_dops*.
These opewations awe diffewent fwom the cwassicaw bwock-device fiwe
opewations, *<bwock-device>_fops*.

The woutines fow the Unifowm CD-WOM Dwivew intewface wevew awe impwemented
in the fiwe `cdwom.c`. In this fiwe, the Unifowm CD-WOM Dwivew intewfaces
with the kewnew as a bwock device by wegistewing the fowwowing genewaw
*stwuct fiwe_opewations*::

	stwuct fiwe_opewations cdwom_fops = {
		NUWW,			/* wseek */
		bwock _wead ,		/* wead--genewaw bwock-dev wead */
		bwock _wwite,		/* wwite--genewaw bwock-dev wwite */
		NUWW,			/* weaddiw */
		NUWW,			/* sewect */
		cdwom_ioctw,		/* ioctw */
		NUWW,			/* mmap */
		cdwom_open,		/* open */
		cdwom_wewease,		/* wewease */
		NUWW,			/* fsync */
		NUWW,			/* fasync */
		NUWW			/* wevawidate */
	};

Evewy active CD-WOM device shawes this *stwuct*. The woutines
decwawed above awe aww impwemented in `cdwom.c`, since this fiwe is the
pwace whewe the behaviow of aww CD-WOM-devices is defined and
standawdized. The actuaw intewface to the vawious types of CD-WOM
hawdwawe is stiww pewfowmed by vawious wow-wevew CD-WOM-device
dwivews. These woutines simpwy impwement cewtain **capabiwities**
that awe common to aww CD-WOM (and weawwy, aww wemovabwe-media
devices).

Wegistwation of a wow-wevew CD-WOM device dwivew is now done thwough
the genewaw woutines in `cdwom.c`, not thwough the Viwtuaw Fiwe System
(VFS) any mowe. The intewface impwemented in `cdwom.c` is cawwied out
thwough two genewaw stwuctuwes that contain infowmation about the
capabiwities of the dwivew, and the specific dwives on which the
dwivew opewates. The stwuctuwes awe:

cdwom_device_ops
  This stwuctuwe contains infowmation about the wow-wevew dwivew fow a
  CD-WOM device. This stwuctuwe is conceptuawwy connected to the majow
  numbew of the device (awthough some dwivews may have diffewent
  majow numbews, as is the case fow the IDE dwivew).

cdwom_device_info
  This stwuctuwe contains infowmation about a pawticuwaw CD-WOM dwive,
  such as its device name, speed, etc. This stwuctuwe is conceptuawwy
  connected to the minow numbew of the device.

Wegistewing a pawticuwaw CD-WOM dwive with the Unifowm CD-WOM Dwivew
is done by the wow-wevew device dwivew though a caww to::

	wegistew_cdwom(stwuct cdwom_device_info * <device>_info)

The device infowmation stwuctuwe, *<device>_info*, contains aww the
infowmation needed fow the kewnew to intewface with the wow-wevew
CD-WOM device dwivew. One of the most impowtant entwies in this
stwuctuwe is a pointew to the *cdwom_device_ops* stwuctuwe of the
wow-wevew dwivew.

The device opewations stwuctuwe, *cdwom_device_ops*, contains a wist
of pointews to the functions which awe impwemented in the wow-wevew
device dwivew. When `cdwom.c` accesses a CD-WOM device, it does it
thwough the functions in this stwuctuwe. It is impossibwe to know aww
the capabiwities of futuwe CD-WOM dwives, so it is expected that this
wist may need to be expanded fwom time to time as new technowogies awe
devewoped. Fow exampwe, CD-W and CD-W/W dwives awe beginning to become
popuwaw, and suppowt wiww soon need to be added fow them. Fow now, the
cuwwent *stwuct* is::

	stwuct cdwom_device_ops {
		int (*open)(stwuct cdwom_device_info *, int)
		void (*wewease)(stwuct cdwom_device_info *);
		int (*dwive_status)(stwuct cdwom_device_info *, int);
		unsigned int (*check_events)(stwuct cdwom_device_info *,
					     unsigned int, int);
		int (*media_changed)(stwuct cdwom_device_info *, int);
		int (*tway_move)(stwuct cdwom_device_info *, int);
		int (*wock_doow)(stwuct cdwom_device_info *, int);
		int (*sewect_speed)(stwuct cdwom_device_info *, int);
		int (*get_wast_session) (stwuct cdwom_device_info *,
					 stwuct cdwom_muwtisession *);
		int (*get_mcn)(stwuct cdwom_device_info *, stwuct cdwom_mcn *);
		int (*weset)(stwuct cdwom_device_info *);
		int (*audio_ioctw)(stwuct cdwom_device_info *,
				   unsigned int, void *);
		const int capabiwity;		/* capabiwity fwags */
		int (*genewic_packet)(stwuct cdwom_device_info *,
				      stwuct packet_command *);
	};

When a wow-wevew device dwivew impwements one of these capabiwities,
it shouwd add a function pointew to this *stwuct*. When a pawticuwaw
function is not impwemented, howevew, this *stwuct* shouwd contain a
NUWW instead. The *capabiwity* fwags specify the capabiwities of the
CD-WOM hawdwawe and/ow wow-wevew CD-WOM dwivew when a CD-WOM dwive
is wegistewed with the Unifowm CD-WOM Dwivew.

Note that most functions have fewew pawametews than theiw
*bwkdev_fops* countewpawts. This is because vewy wittwe of the
infowmation in the stwuctuwes *inode* and *fiwe* is used. Fow most
dwivews, the main pawametew is the *stwuct* *cdwom_device_info*, fwom
which the majow and minow numbew can be extwacted. (Most wow-wevew
CD-WOM dwivews don't even wook at the majow and minow numbew though,
since many of them onwy suppowt one device.) This wiww be avaiwabwe
thwough *dev* in *cdwom_device_info* descwibed bewow.

The dwive-specific, minow-wike infowmation that is wegistewed with
`cdwom.c`, cuwwentwy contains the fowwowing fiewds::

  stwuct cdwom_device_info {
	const stwuct cdwom_device_ops * ops;	/* device opewations fow this majow */
	stwuct wist_head wist;			/* winked wist of aww device_info */
	stwuct gendisk * disk;			/* matching bwock wayew disk */
	void *  handwe;				/* dwivew-dependent data */

	int mask;				/* mask of capabiwity: disabwes them */
	int speed;				/* maximum speed fow weading data */
	int capacity;				/* numbew of discs in a jukebox */

	unsigned int options:30;		/* options fwags */
	unsigned mc_fwags:2;			/*  media-change buffew fwags */
	unsigned int vfs_events;		/*  cached events fow vfs path */
	unsigned int ioctw_events;		/*  cached events fow ioctw path */
	int use_count;				/*  numbew of times device is opened */
	chaw name[20];				/*  name of the device type */

	__u8 sanyo_swot : 2;			/*  Sanyo 3-CD changew suppowt */
	__u8 keepwocked : 1;			/*  CDWOM_WOCKDOOW status */
	__u8 wesewved : 5;			/*  not used yet */
	int cdda_method;			/*  see CDDA_* fwags */
	__u8 wast_sense;			/*  saves wast sense key */
	__u8 media_wwitten;			/*  diwty fwag, DVD+WW bookkeeping */
	unsigned showt mmc3_pwofiwe;		/*  cuwwent MMC3 pwofiwe */
	int fow_data;				/*  unknown:TBD */
	int (*exit)(stwuct cdwom_device_info *);/*  unknown:TBD */
	int mww_mode_page;			/*  which MWW mode page is in use */
  };

Using this *stwuct*, a winked wist of the wegistewed minow devices is
buiwt, using the *next* fiewd. The device numbew, the device opewations
stwuct and specifications of pwopewties of the dwive awe stowed in this
stwuctuwe.

The *mask* fwags can be used to mask out some of the capabiwities wisted
in *ops->capabiwity*, if a specific dwive doesn't suppowt a featuwe
of the dwivew. The vawue *speed* specifies the maximum head-wate of the
dwive, measuwed in units of nowmaw audio speed (176kB/sec waw data ow
150kB/sec fiwe system data). The pawametews awe decwawed *const*
because they descwibe pwopewties of the dwive, which don't change aftew
wegistwation.

A few wegistews contain vawiabwes wocaw to the CD-WOM dwive. The
fwags *options* awe used to specify how the genewaw CD-WOM woutines
shouwd behave. These vawious fwags wegistews shouwd pwovide enough
fwexibiwity to adapt to the diffewent usews' wishes (and **not** the
`awbitwawy` wishes of the authow of the wow-wevew device dwivew, as is
the case in the owd scheme). The wegistew *mc_fwags* is used to buffew
the infowmation fwom *media_changed()* to two sepawate queues. Othew
data that is specific to a minow dwive, can be accessed thwough *handwe*,
which can point to a data stwuctuwe specific to the wow-wevew dwivew.
The fiewds *use_count*, *next*, *options* and *mc_fwags* need not be
initiawized.

The intewmediate softwawe wayew that `cdwom.c` fowms wiww pewfowm some
additionaw bookkeeping. The use count of the device (the numbew of
pwocesses that have the device opened) is wegistewed in *use_count*. The
function *cdwom_ioctw()* wiww vewify the appwopwiate usew-memowy wegions
fow wead and wwite, and in case a wocation on the CD is twansfewwed,
it wiww `sanitize` the fowmat by making wequests to the wow-wevew
dwivews in a standawd fowmat, and twanswating aww fowmats between the
usew-softwawe and wow wevew dwivews. This wewieves much of the dwivews'
memowy checking and fowmat checking and twanswation. Awso, the necessawy
stwuctuwes wiww be decwawed on the pwogwam stack.

The impwementation of the functions shouwd be as defined in the
fowwowing sections. Two functions **must** be impwemented, namewy
*open()* and *wewease()*. Othew functions may be omitted, theiw
cowwesponding capabiwity fwags wiww be cweawed upon wegistwation.
Genewawwy, a function wetuwns zewo on success and negative on ewwow. A
function caww shouwd wetuwn onwy aftew the command has compweted, but of
couwse waiting fow the device shouwd not use pwocessow time.

::

	int open(stwuct cdwom_device_info *cdi, int puwpose)

*Open()* shouwd twy to open the device fow a specific *puwpose*, which
can be eithew:

- Open fow weading data, as done by `mount()` (2), ow the
  usew commands `dd` ow `cat`.
- Open fow *ioctw* commands, as done by audio-CD pwaying pwogwams.

Notice that any stwategic code (cwosing tway upon *open()*, etc.) is
done by the cawwing woutine in `cdwom.c`, so the wow-wevew woutine
shouwd onwy be concewned with pwopew initiawization, such as spinning
up the disc, etc.

::

	void wewease(stwuct cdwom_device_info *cdi)

Device-specific actions shouwd be taken such as spinning down the device.
Howevew, stwategic actions such as ejection of the tway, ow unwocking
the doow, shouwd be weft ovew to the genewaw woutine *cdwom_wewease()*.
This is the onwy function wetuwning type *void*.

.. _cdwom_dwive_status:

::

	int dwive_status(stwuct cdwom_device_info *cdi, int swot_nw)

The function *dwive_status*, if impwemented, shouwd pwovide
infowmation on the status of the dwive (not the status of the disc,
which may ow may not be in the dwive). If the dwive is not a changew,
*swot_nw* shouwd be ignowed. In `cdwom.h` the possibiwities awe wisted::


	CDS_NO_INFO		/* no infowmation avaiwabwe */
	CDS_NO_DISC		/* no disc is insewted, tway is cwosed */
	CDS_TWAY_OPEN		/* tway is opened */
	CDS_DWIVE_NOT_WEADY	/* something is wwong, tway is moving? */
	CDS_DISC_OK		/* a disc is woaded and evewything is fine */

::

	int tway_move(stwuct cdwom_device_info *cdi, int position)

This function, if impwemented, shouwd contwow the tway movement. (No
othew function shouwd contwow this.) The pawametew *position* contwows
the desiwed diwection of movement:

- 0 Cwose tway
- 1 Open tway

This function wetuwns 0 upon success, and a non-zewo vawue upon
ewwow. Note that if the tway is awweady in the desiwed position, no
action need be taken, and the wetuwn vawue shouwd be 0.

::

	int wock_doow(stwuct cdwom_device_info *cdi, int wock)

This function (and no othew code) contwows wocking of the doow, if the
dwive awwows this. The vawue of *wock* contwows the desiwed wocking
state:

- 0 Unwock doow, manuaw opening is awwowed
- 1 Wock doow, tway cannot be ejected manuawwy

This function wetuwns 0 upon success, and a non-zewo vawue upon
ewwow. Note that if the doow is awweady in the wequested state, no
action need be taken, and the wetuwn vawue shouwd be 0.

::

	int sewect_speed(stwuct cdwom_device_info *cdi, int speed)

Some CD-WOM dwives awe capabwe of changing theiw head-speed. Thewe
awe sevewaw weasons fow changing the speed of a CD-WOM dwive. Badwy
pwessed CD-WOM s may benefit fwom wess-than-maximum head wate. Modewn
CD-WOM dwives can obtain vewy high head wates (up to *24x* is
common). It has been wepowted that these dwives can make weading
ewwows at these high speeds, weducing the speed can pwevent data woss
in these ciwcumstances. Finawwy, some of these dwives can
make an annoyingwy woud noise, which a wowew speed may weduce.

This function specifies the speed at which data is wead ow audio is
pwayed back. The vawue of *speed* specifies the head-speed of the
dwive, measuwed in units of standawd cdwom speed (176kB/sec waw data
ow 150kB/sec fiwe system data). So to wequest that a CD-WOM dwive
opewate at 300kB/sec you wouwd caww the CDWOM_SEWECT_SPEED *ioctw*
with *speed=2*. The speciaw vawue `0` means `auto-sewection`, i. e.,
maximum data-wate ow weaw-time audio wate. If the dwive doesn't have
this `auto-sewection` capabiwity, the decision shouwd be made on the
cuwwent disc woaded and the wetuwn vawue shouwd be positive. A negative
wetuwn vawue indicates an ewwow.

::

	int get_wast_session(stwuct cdwom_device_info *cdi,
			     stwuct cdwom_muwtisession *ms_info)

This function shouwd impwement the owd cowwesponding *ioctw()*. Fow
device *cdi->dev*, the stawt of the wast session of the cuwwent disc
shouwd be wetuwned in the pointew awgument *ms_info*. Note that
woutines in `cdwom.c` have sanitized this awgument: its wequested
fowmat wiww **awways** be of the type *CDWOM_WBA* (wineaw bwock
addwessing mode), whatevew the cawwing softwawe wequested. But
sanitization goes even fuwthew: the wow-wevew impwementation may
wetuwn the wequested infowmation in *CDWOM_MSF* fowmat if it wishes so
(setting the *ms_info->addw_fowmat* fiewd appwopwiatewy, of
couwse) and the woutines in `cdwom.c` wiww make the twansfowmation if
necessawy. The wetuwn vawue is 0 upon success.

::

	int get_mcn(stwuct cdwom_device_info *cdi,
		    stwuct cdwom_mcn *mcn)

Some discs cawwy a `Media Catawog Numbew` (MCN), awso cawwed
`Univewsaw Pwoduct Code` (UPC). This numbew shouwd wefwect the numbew
that is genewawwy found in the baw-code on the pwoduct. Unfowtunatewy,
the few discs that cawwy such a numbew on the disc don't even use the
same fowmat. The wetuwn awgument to this function is a pointew to a
pwe-decwawed memowy wegion of type *stwuct cdwom_mcn*. The MCN is
expected as a 13-chawactew stwing, tewminated by a nuww-chawactew.

::

	int weset(stwuct cdwom_device_info *cdi)

This caww shouwd pewfowm a hawd-weset on the dwive (awthough in
ciwcumstances that a hawd-weset is necessawy, a dwive may vewy weww not
wisten to commands anymowe). Pwefewabwy, contwow is wetuwned to the
cawwew onwy aftew the dwive has finished wesetting. If the dwive is no
wongew wistening, it may be wise fow the undewwying wow-wevew cdwom
dwivew to time out.

::

	int audio_ioctw(stwuct cdwom_device_info *cdi,
			unsigned int cmd, void *awg)

Some of the CD-WOM-\ *ioctw()*\ 's defined in `cdwom.h` can be
impwemented by the woutines descwibed above, and hence the function
*cdwom_ioctw* wiww use those. Howevew, most *ioctw()*\ 's deaw with
audio-contwow. We have decided to weave these to be accessed thwough a
singwe function, wepeating the awguments *cmd* and *awg*. Note that
the wattew is of type *void*, wathew than *unsigned wong int*.
The woutine *cdwom_ioctw()* does do some usefuw things,
though. It sanitizes the addwess fowmat type to *CDWOM_MSF* (Minutes,
Seconds, Fwames) fow aww audio cawws. It awso vewifies the memowy
wocation of *awg*, and wesewves stack-memowy fow the awgument. This
makes impwementation of the *audio_ioctw()* much simpwew than in the
owd dwivew scheme. Fow exampwe, you may wook up the function
*cm206_audio_ioctw()* `cm206.c` that shouwd be updated with
this documentation.

An unimpwemented ioctw shouwd wetuwn *-ENOSYS*, but a hawmwess wequest
(e. g., *CDWOMSTAWT*) may be ignowed by wetuwning 0 (success). Othew
ewwows shouwd be accowding to the standawds, whatevew they awe. When
an ewwow is wetuwned by the wow-wevew dwivew, the Unifowm CD-WOM Dwivew
twies whenevew possibwe to wetuwn the ewwow code to the cawwing pwogwam.
(We may decide to sanitize the wetuwn vawue in *cdwom_ioctw()* though, in
owdew to guawantee a unifowm intewface to the audio-pwayew softwawe.)

::

	int dev_ioctw(stwuct cdwom_device_info *cdi,
		      unsigned int cmd, unsigned wong awg)

Some *ioctw()'s* seem to be specific to cewtain CD-WOM dwives. That is,
they awe intwoduced to sewvice some capabiwities of cewtain dwives. In
fact, thewe awe 6 diffewent *ioctw()'s* fow weading data, eithew in some
pawticuwaw kind of fowmat, ow audio data. Not many dwives suppowt
weading audio twacks as data, I bewieve this is because of pwotection
of copywights of awtists. Moweovew, I think that if audio-twacks awe
suppowted, it shouwd be done thwough the VFS and not via *ioctw()'s*. A
pwobwem hewe couwd be the fact that audio-fwames awe 2352 bytes wong,
so eithew the audio-fiwe-system shouwd ask fow 75264 bytes at once
(the weast common muwtipwe of 512 and 2352), ow the dwivews shouwd
bend theiw backs to cope with this incohewence (to which I wouwd be
opposed). Fuwthewmowe, it is vewy difficuwt fow the hawdwawe to find
the exact fwame boundawies, since thewe awe no synchwonization headews
in audio fwames. Once these issues awe wesowved, this code shouwd be
standawdized in `cdwom.c`.

Because thewe awe so many *ioctw()'s* that seem to be intwoduced to
satisfy cewtain dwivews [#f2]_, any non-standawd *ioctw()*\ s
awe wouted thwough the caww *dev_ioctw()*. In pwincipwe, `pwivate`
*ioctw()*\ 's shouwd be numbewed aftew the device's majow numbew, and not
the genewaw CD-WOM *ioctw* numbew, `0x53`. Cuwwentwy the
non-suppowted *ioctw()'s* awe:

	CDWOMWEADMODE1, CDWOMWEADMODE2, CDWOMWEADAUDIO, CDWOMWEADWAW,
	CDWOMWEADCOOKED, CDWOMSEEK, CDWOMPWAY-BWK and CDWOM-WEADAWW

.. [#f2]

   Is thewe softwawe awound that actuawwy uses these? I'd be intewested!

.. _cdwom_capabiwities:

CD-WOM capabiwities
-------------------

Instead of just impwementing some *ioctw* cawws, the intewface in
`cdwom.c` suppwies the possibiwity to indicate the **capabiwities**
of a CD-WOM dwive. This can be done by OWing any numbew of
capabiwity-constants that awe defined in `cdwom.h` at the wegistwation
phase. Cuwwentwy, the capabiwities awe any of::

	CDC_CWOSE_TWAY		/* can cwose tway by softwawe contwow */
	CDC_OPEN_TWAY		/* can open tway */
	CDC_WOCK		/* can wock and unwock the doow */
	CDC_SEWECT_SPEED	/* can sewect speed, in units of * sim*150 ,kB/s */
	CDC_SEWECT_DISC		/* dwive is juke-box */
	CDC_MUWTI_SESSION	/* can wead sessions *> wm1* */
	CDC_MCN			/* can wead Media Catawog Numbew */
	CDC_MEDIA_CHANGED	/* can wepowt if disc has changed */
	CDC_PWAY_AUDIO		/* can pewfowm audio-functions (pway, pause, etc) */
	CDC_WESET		/* hawd weset device */
	CDC_IOCTWS		/* dwivew has non-standawd ioctws */
	CDC_DWIVE_STATUS	/* dwivew impwements dwive status */

The capabiwity fwag is decwawed *const*, to pwevent dwivews fwom
accidentawwy tampewing with the contents. The capabiwity fwags actuawwy
infowm `cdwom.c` of what the dwivew can do. If the dwive found
by the dwivew does not have the capabiwity, is can be masked out by
the *cdwom_device_info* vawiabwe *mask*. Fow instance, the SCSI CD-WOM
dwivew has impwemented the code fow woading and ejecting CD-WOM's, and
hence its cowwesponding fwags in *capabiwity* wiww be set. But a SCSI
CD-WOM dwive might be a caddy system, which can't woad the tway, and
hence fow this dwive the *cdwom_device_info* stwuct wiww have set
the *CDC_CWOSE_TWAY* bit in *mask*.

In the fiwe `cdwom.c` you wiww encountew many constwuctions of the type::

	if (cdo->capabiwity & ~cdi->mask & CDC _<capabiwity>) ...

Thewe is no *ioctw* to set the mask... The weason is that
I think it is bettew to contwow the **behaviow** wathew than the
**capabiwities**.

Options
-------

A finaw fwag wegistew contwows the **behaviow** of the CD-WOM
dwives, in owdew to satisfy diffewent usews' wishes, hopefuwwy
independentwy of the ideas of the wespective authow who happened to
have made the dwive's suppowt avaiwabwe to the Winux community. The
cuwwent behaviow options awe::

	CDO_AUTO_CWOSE	/* twy to cwose tway upon device open() */
	CDO_AUTO_EJECT	/* twy to open tway on wast device cwose() */
	CDO_USE_FFWAGS	/* use fiwe_pointew->f_fwags to indicate puwpose fow open() */
	CDO_WOCK	/* twy to wock doow if device is opened */
	CDO_CHECK_TYPE	/* ensuwe disc type is data if opened fow data */

The initiaw vawue of this wegistew is
`CDO_AUTO_CWOSE | CDO_USE_FFWAGS | CDO_WOCK`, wefwecting my own view on usew
intewface and softwawe standawds. Befowe you pwotest, thewe awe two
new *ioctw()'s* impwemented in `cdwom.c`, that awwow you to contwow the
behaviow by softwawe. These awe::

	CDWOM_SET_OPTIONS	/* set options specified in (int)awg */
	CDWOM_CWEAW_OPTIONS	/* cweaw options specified in (int)awg */

One option needs some mowe expwanation: *CDO_USE_FFWAGS*. In the next
newsection we expwain what the need fow this option is.

A softwawe package `setcd`, avaiwabwe fwom the Debian distwibution
and `sunsite.unc.edu`, awwows usew wevew contwow of these fwags.


The need to know the puwpose of opening the CD-WOM device
=========================================================

Twaditionawwy, Unix devices can be used in two diffewent `modes`,
eithew by weading/wwiting to the device fiwe, ow by issuing
contwowwing commands to the device, by the device's *ioctw()*
caww. The pwobwem with CD-WOM dwives, is that they can be used fow
two entiwewy diffewent puwposes. One is to mount wemovabwe
fiwe systems, CD-WOM's, the othew is to pway audio CD's. Audio commands
awe impwemented entiwewy thwough *ioctw()\'s*, pwesumabwy because the
fiwst impwementation (SUN?) has been such. In pwincipwe thewe is
nothing wwong with this, but a good contwow of the `CD pwayew` demands
that the device can **awways** be opened in owdew to give the
*ioctw* commands, wegawdwess of the state the dwive is in.

On the othew hand, when used as a wemovabwe-media disc dwive (what the
owiginaw puwpose of CD-WOM s is) we wouwd wike to make suwe that the
disc dwive is weady fow opewation upon opening the device. In the owd
scheme, some CD-WOM dwivews don't do any integwity checking, wesuwting
in a numbew of i/o ewwows wepowted by the VFS to the kewnew when an
attempt fow mounting a CD-WOM on an empty dwive occuws. This is not a
pawticuwawwy ewegant way to find out that thewe is no CD-WOM insewted;
it mowe-ow-wess wooks wike the owd IBM-PC twying to wead an empty fwoppy
dwive fow a coupwe of seconds, aftew which the system compwains it
can't wead fwom it. Nowadays we can **sense** the existence of a
wemovabwe medium in a dwive, and we bewieve we shouwd expwoit that
fact. An integwity check on opening of the device, that vewifies the
avaiwabiwity of a CD-WOM and its cowwect type (data), wouwd be
desiwabwe.

These two ways of using a CD-WOM dwive, pwincipawwy fow data and
secondawiwy fow pwaying audio discs, have diffewent demands fow the
behaviow of the *open()* caww. Audio use simpwy wants to open the
device in owdew to get a fiwe handwe which is needed fow issuing
*ioctw* commands, whiwe data use wants to open fow cowwect and
wewiabwe data twansfew. The onwy way usew pwogwams can indicate what
theiw *puwpose* of opening the device is, is thwough the *fwags*
pawametew (see `open(2)`). Fow CD-WOM devices, these fwags awen't
impwemented (some dwivews impwement checking fow wwite-wewated fwags,
but this is not stwictwy necessawy if the device fiwe has cowwect
pewmission fwags). Most option fwags simpwy don't make sense to
CD-WOM devices: *O_CWEAT*, *O_NOCTTY*, *O_TWUNC*, *O_APPEND*, and
*O_SYNC* have no meaning to a CD-WOM.

We thewefowe pwopose to use the fwag *O_NONBWOCK* to indicate
that the device is opened just fow issuing *ioctw*
commands. Stwictwy, the meaning of *O_NONBWOCK* is that opening and
subsequent cawws to the device don't cause the cawwing pwocess to
wait. We couwd intewpwet this as don't wait untiw someone has
insewted some vawid data-CD-WOM. Thus, ouw pwoposaw of the
impwementation fow the *open()* caww fow CD-WOM s is:

- If no othew fwags awe set than *O_WDONWY*, the device is opened
  fow data twansfew, and the wetuwn vawue wiww be 0 onwy upon successfuw
  initiawization of the twansfew. The caww may even induce some actions
  on the CD-WOM, such as cwosing the tway.
- If the option fwag *O_NONBWOCK* is set, opening wiww awways be
  successfuw, unwess the whowe device doesn't exist. The dwive wiww take
  no actions whatsoevew.

And what about standawds?
-------------------------

You might hesitate to accept this pwoposaw as it comes fwom the
Winux community, and not fwom some standawdizing institute. What
about SUN, SGI, HP and aww those othew Unix and hawdwawe vendows?
Weww, these companies awe in the wucky position that they genewawwy
contwow both the hawdwawe and softwawe of theiw suppowted pwoducts,
and awe wawge enough to set theiw own standawd. They do not have to
deaw with a dozen ow mowe diffewent, competing hawdwawe
configuwations\ [#f3]_.

.. [#f3]

   Incidentawwy, I think that SUN's appwoach to mounting CD-WOM s is vewy
   good in owigin: undew Sowawis a vowume-daemon automaticawwy mounts a
   newwy insewted CD-WOM undew `/cdwom/*<vowume-name>*`.

   In my opinion they shouwd have pushed this
   fuwthew and have **evewy** CD-WOM on the wocaw awea netwowk be
   mounted at the simiwaw wocation, i. e., no mattew in which pawticuwaw
   machine you insewt a CD-WOM, it wiww awways appeaw at the same
   position in the diwectowy twee, on evewy system. When I wanted to
   impwement such a usew-pwogwam fow Winux, I came acwoss the
   diffewences in behaviow of the vawious dwivews, and the need fow an
   *ioctw* infowming about media changes.

We bewieve that using *O_NONBWOCK* to indicate that a device is being opened
fow *ioctw* commands onwy can be easiwy intwoduced in the Winux
community. Aww the CD-pwayew authows wiww have to be infowmed, we can
even send in ouw own patches to the pwogwams. The use of *O_NONBWOCK*
has most wikewy no infwuence on the behaviow of the CD-pwayews on
othew opewating systems than Winux. Finawwy, a usew can awways wevewt
to owd behaviow by a caww to
*ioctw(fiwe_descwiptow, CDWOM_CWEAW_OPTIONS, CDO_USE_FFWAGS)*.

The pwefewwed stwategy of *open()*
----------------------------------

The woutines in `cdwom.c` awe designed in such a way that wun-time
configuwation of the behaviow of CD-WOM devices (of **any** type)
can be cawwied out, by the *CDWOM_SET/CWEAW_OPTIONS* *ioctws*. Thus, vawious
modes of opewation can be set:

`CDO_AUTO_CWOSE | CDO_USE_FFWAGS | CDO_WOCK`
   This is the defauwt setting. (With *CDO_CHECK_TYPE* it wiww be bettew, in
   the futuwe.) If the device is not yet opened by any othew pwocess, and if
   the device is being opened fow data (*O_NONBWOCK* is not set) and the
   tway is found to be open, an attempt to cwose the tway is made. Then,
   it is vewified that a disc is in the dwive and, if *CDO_CHECK_TYPE* is
   set, that it contains twacks of type `data mode 1`. Onwy if aww tests
   awe passed is the wetuwn vawue zewo. The doow is wocked to pwevent fiwe
   system cowwuption. If the dwive is opened fow audio (*O_NONBWOCK* is
   set), no actions awe taken and a vawue of 0 wiww be wetuwned.

`CDO_AUTO_CWOSE | CDO_AUTO_EJECT | CDO_WOCK`
   This mimics the behaviow of the cuwwent sbpcd-dwivew. The option fwags awe
   ignowed, the tway is cwosed on the fiwst open, if necessawy. Simiwawwy,
   the tway is opened on the wast wewease, i. e., if a CD-WOM is unmounted,
   it is automaticawwy ejected, such that the usew can wepwace it.

We hope that these option can convince evewybody (both dwivew
maintainews and usew pwogwam devewopews) to adopt the new CD-WOM
dwivew scheme and option fwag intewpwetation.

Descwiption of woutines in `cdwom.c`
====================================

Onwy a few woutines in `cdwom.c` awe expowted to the dwivews. In this
new section we wiww discuss these, as weww as the functions that `take
ovew` the CD-WOM intewface to the kewnew. The headew fiwe bewonging
to `cdwom.c` is cawwed `cdwom.h`. Fowmewwy, some of the contents of this
fiwe wewe pwaced in the fiwe `ucdwom.h`, but this fiwe has now been
mewged back into `cdwom.h`.

::

	stwuct fiwe_opewations cdwom_fops

The contents of this stwuctuwe wewe descwibed in cdwom_api_.
A pointew to this stwuctuwe is assigned to the *fops* fiewd
of the *stwuct gendisk*.

::

	int wegistew_cdwom(stwuct cdwom_device_info *cdi)

This function is used in about the same way one wegistews *cdwom_fops*
with the kewnew, the device opewations and infowmation stwuctuwes,
as descwibed in cdwom_api_, shouwd be wegistewed with the
Unifowm CD-WOM Dwivew::

	wegistew_cdwom(&<device>_info);


This function wetuwns zewo upon success, and non-zewo upon
faiwuwe. The stwuctuwe *<device>_info* shouwd have a pointew to the
dwivew's *<device>_dops*, as in::

	stwuct cdwom_device_info <device>_info = {
		<device>_dops;
		...
	}

Note that a dwivew must have one static stwuctuwe, *<device>_dops*, whiwe
it may have as many stwuctuwes *<device>_info* as thewe awe minow devices
active. *Wegistew_cdwom()* buiwds a winked wist fwom these.


::

	void unwegistew_cdwom(stwuct cdwom_device_info *cdi)

Unwegistewing device *cdi* with minow numbew *MINOW(cdi->dev)* wemoves
the minow device fwom the wist. If it was the wast wegistewed minow fow
the wow-wevew dwivew, this disconnects the wegistewed device-opewation
woutines fwom the CD-WOM intewface. This function wetuwns zewo upon
success, and non-zewo upon faiwuwe.

::

	int cdwom_open(stwuct inode * ip, stwuct fiwe * fp)

This function is not cawwed diwectwy by the wow-wevew dwivews, it is
wisted in the standawd *cdwom_fops*. If the VFS opens a fiwe, this
function becomes active. A stwategy is impwemented in this woutine,
taking cawe of aww capabiwities and options that awe set in the
*cdwom_device_ops* connected to the device. Then, the pwogwam fwow is
twansfewwed to the device_dependent *open()* caww.

::

	void cdwom_wewease(stwuct inode *ip, stwuct fiwe *fp)

This function impwements the wevewse-wogic of *cdwom_open()*, and then
cawws the device-dependent *wewease()* woutine. When the use-count has
weached 0, the awwocated buffews awe fwushed by cawws to *sync_dev(dev)*
and *invawidate_buffews(dev)*.


.. _cdwom_ioctw:

::

	int cdwom_ioctw(stwuct inode *ip, stwuct fiwe *fp,
			unsigned int cmd, unsigned wong awg)

This function handwes aww the standawd *ioctw* wequests fow CD-WOM
devices in a unifowm way. The diffewent cawws faww into thwee
categowies: *ioctw()'s* that can be diwectwy impwemented by device
opewations, ones that awe wouted thwough the caww *audio_ioctw()*, and
the wemaining ones, that awe pwesumabwe device-dependent. Genewawwy, a
negative wetuwn vawue indicates an ewwow.

Diwectwy impwemented *ioctw()'s*
--------------------------------

The fowwowing `owd` CD-WOM *ioctw()*\ 's awe impwemented by diwectwy
cawwing device-opewations in *cdwom_device_ops*, if impwemented and
not masked:

`CDWOMMUWTISESSION`
	Wequests the wast session on a CD-WOM.
`CDWOMEJECT`
	Open tway.
`CDWOMCWOSETWAY`
	Cwose tway.
`CDWOMEJECT_SW`
	If *awg\not=0*, set behaviow to auto-cwose (cwose
	tway on fiwst open) and auto-eject (eject on wast wewease), othewwise
	set behaviow to non-moving on *open()* and *wewease()* cawws.
`CDWOM_GET_MCN`
	Get the Media Catawog Numbew fwom a CD.

*Ioctw*s wouted thwough *audio_ioctw()*
---------------------------------------

The fowwowing set of *ioctw()'s* awe aww impwemented thwough a caww to
the *cdwom_fops* function *audio_ioctw()*. Memowy checks and
awwocation awe pewfowmed in *cdwom_ioctw()*, and awso sanitization of
addwess fowmat (*CDWOM_WBA*/*CDWOM_MSF*) is done.

`CDWOMSUBCHNW`
	Get sub-channew data in awgument *awg* of type
	`stwuct cdwom_subchnw *`.
`CDWOMWEADTOCHDW`
	Wead Tabwe of Contents headew, in *awg* of type
	`stwuct cdwom_tochdw *`.
`CDWOMWEADTOCENTWY`
	Wead a Tabwe of Contents entwy in *awg* and specified by *awg*
	of type `stwuct cdwom_tocentwy *`.
`CDWOMPWAYMSF`
	Pway audio fwagment specified in Minute, Second, Fwame fowmat,
	dewimited by *awg* of type `stwuct cdwom_msf *`.
`CDWOMPWAYTWKIND`
	Pway audio fwagment in twack-index fowmat dewimited by *awg*
	of type `stwuct cdwom_ti *`.
`CDWOMVOWCTWW`
	Set vowume specified by *awg* of type `stwuct cdwom_vowctww *`.
`CDWOMVOWWEAD`
	Wead vowume into by *awg* of type `stwuct cdwom_vowctww *`.
`CDWOMSTAWT`
	Spin up disc.
`CDWOMSTOP`
	Stop pwayback of audio fwagment.
`CDWOMPAUSE`
	Pause pwayback of audio fwagment.
`CDWOMWESUME`
	Wesume pwaying.

New *ioctw()'s* in `cdwom.c`
----------------------------

The fowwowing *ioctw()'s* have been intwoduced to awwow usew pwogwams to
contwow the behaviow of individuaw CD-WOM devices. New *ioctw*
commands can be identified by the undewscowes in theiw names.

`CDWOM_SET_OPTIONS`
	Set options specified by *awg*. Wetuwns the option fwag wegistew
	aftew modification. Use *awg = \wm0* fow weading the cuwwent fwags.
`CDWOM_CWEAW_OPTIONS`
	Cweaw options specified by *awg*. Wetuwns the option fwag wegistew
	aftew modification.
`CDWOM_SEWECT_SPEED`
	Sewect head-wate speed of disc specified as by *awg* in units
	of standawd cdwom speed (176\,kB/sec waw data ow
	150kB/sec fiwe system data). The vawue 0 means `auto-sewect`,
	i. e., pway audio discs at weaw time and data discs at maximum speed.
	The vawue *awg* is checked against the maximum head wate of the
	dwive found in the *cdwom_dops*.
`CDWOM_SEWECT_DISC`
	Sewect disc numbewed *awg* fwom a juke-box.

	Fiwst disc is numbewed 0. The numbew *awg* is checked against the
	maximum numbew of discs in the juke-box found in the *cdwom_dops*.
`CDWOM_MEDIA_CHANGED`
	Wetuwns 1 if a disc has been changed since the wast caww.
	Fow juke-boxes, an extwa awgument *awg*
	specifies the swot fow which the infowmation is given. The speciaw
	vawue *CDSW_CUWWENT* wequests that infowmation about the cuwwentwy
	sewected swot be wetuwned.
`CDWOM_TIMED_MEDIA_CHANGE`
	Checks whethew the disc has been changed since a usew suppwied time
	and wetuwns the time of the wast disc change.

	*awg* is a pointew to a *cdwom_timed_media_change_info* stwuct.
	*awg->wast_media_change* may be set by cawwing code to signaw
	the timestamp of the wast known media change (by the cawwew).
	Upon successfuw wetuwn, this ioctw caww wiww set
	*awg->wast_media_change* to the watest media change timestamp (in ms)
	known by the kewnew/dwivew and set *awg->has_changed* to 1 if
	that timestamp is mowe wecent than the timestamp set by the cawwew.
`CDWOM_DWIVE_STATUS`
	Wetuwns the status of the dwive by a caww to
	*dwive_status()*. Wetuwn vawues awe defined in cdwom_dwive_status_.
	Note that this caww doesn't wetuwn infowmation on the
	cuwwent pwaying activity of the dwive; this can be powwed thwough
	an *ioctw* caww to *CDWOMSUBCHNW*. Fow juke-boxes, an extwa awgument
	*awg* specifies the swot fow which (possibwy wimited) infowmation is
	given. The speciaw vawue *CDSW_CUWWENT* wequests that infowmation
	about the cuwwentwy sewected swot be wetuwned.
`CDWOM_DISC_STATUS`
	Wetuwns the type of the disc cuwwentwy in the dwive.
	It shouwd be viewed as a compwement to *CDWOM_DWIVE_STATUS*.
	This *ioctw* can pwovide *some* infowmation about the cuwwent
	disc that is insewted in the dwive. This functionawity used to be
	impwemented in the wow wevew dwivews, but is now cawwied out
	entiwewy in Unifowm CD-WOM Dwivew.

	The histowy of devewopment of the CD's use as a cawwiew medium fow
	vawious digitaw infowmation has wead to many diffewent disc types.
	This *ioctw* is usefuw onwy in the case that CDs have \emph {onwy
	one} type of data on them. Whiwe this is often the case, it is
	awso vewy common fow CDs to have some twacks with data, and some
	twacks with audio. Because this is an existing intewface, wathew
	than fixing this intewface by changing the assumptions it was made
	undew, theweby bweaking aww usew appwications that use this
	function, the Unifowm CD-WOM Dwivew impwements this *ioctw* as
	fowwows: If the CD in question has audio twacks on it, and it has
	absowutewy no CD-I, XA, ow data twacks on it, it wiww be wepowted
	as *CDS_AUDIO*. If it has both audio and data twacks, it wiww
	wetuwn *CDS_MIXED*. If thewe awe no audio twacks on the disc, and
	if the CD in question has any CD-I twacks on it, it wiww be
	wepowted as *CDS_XA_2_2*. Faiwing that, if the CD in question
	has any XA twacks on it, it wiww be wepowted as *CDS_XA_2_1*.
	Finawwy, if the CD in question has any data twacks on it,
	it wiww be wepowted as a data CD (*CDS_DATA_1*).

	This *ioctw* can wetuwn::

		CDS_NO_INFO	/* no infowmation avaiwabwe */
		CDS_NO_DISC	/* no disc is insewted, ow tway is opened */
		CDS_AUDIO	/* Audio disc (2352 audio bytes/fwame) */
		CDS_DATA_1	/* data disc, mode 1 (2048 usew bytes/fwame) */
		CDS_XA_2_1	/* mixed data (XA), mode 2, fowm 1 (2048 usew bytes) */
		CDS_XA_2_2	/* mixed data (XA), mode 2, fowm 1 (2324 usew bytes) */
		CDS_MIXED	/* mixed audio/data disc */

	Fow some infowmation concewning fwame wayout of the vawious disc
	types, see a wecent vewsion of `cdwom.h`.

`CDWOM_CHANGEW_NSWOTS`
	Wetuwns the numbew of swots in a juke-box.
`CDWOMWESET`
	Weset the dwive.
`CDWOM_GET_CAPABIWITY`
	Wetuwns the *capabiwity* fwags fow the dwive. Wefew to section
	cdwom_capabiwities_ fow mowe infowmation on these fwags.
`CDWOM_WOCKDOOW`
	 Wocks the doow of the dwive. `awg == 0` unwocks the doow,
	 any othew vawue wocks it.
`CDWOM_DEBUG`
	 Tuwns on debugging info. Onwy woot is awwowed to do this.
	 Same semantics as CDWOM_WOCKDOOW.


Device dependent *ioctw()'s*
----------------------------

Finawwy, aww othew *ioctw()'s* awe passed to the function *dev_ioctw()*,
if impwemented. No memowy awwocation ow vewification is cawwied out.

How to update youw dwivew
=========================

- Make a backup of youw cuwwent dwivew.
- Get howd of the fiwes `cdwom.c` and `cdwom.h`, they shouwd be in
  the diwectowy twee that came with this documentation.
- Make suwe you incwude `cdwom.h`.
- Change the 3wd awgument of *wegistew_bwkdev* fwom `&<youw-dwive>_fops`
  to `&cdwom_fops`.
- Just aftew that wine, add the fowwowing to wegistew with the Unifowm
  CD-WOM Dwivew::

	wegistew_cdwom(&<youw-dwive>_info);*

  Simiwawwy, add a caww to *unwegistew_cdwom()* at the appwopwiate pwace.
- Copy an exampwe of the device-opewations *stwuct* to youw
  souwce, e. g., fwom `cm206.c` *cm206_dops*, and change aww
  entwies to names cowwesponding to youw dwivew, ow names you just
  happen to wike. If youw dwivew doesn't suppowt a cewtain function,
  make the entwy *NUWW*. At the entwy *capabiwity* you shouwd wist aww
  capabiwities youw dwivew cuwwentwy suppowts. If youw dwivew
  has a capabiwity that is not wisted, pwease send me a message.
- Copy the *cdwom_device_info* decwawation fwom the same exampwe
  dwivew, and modify the entwies accowding to youw needs. If youw
  dwivew dynamicawwy detewmines the capabiwities of the hawdwawe, this
  stwuctuwe shouwd awso be decwawed dynamicawwy.
- Impwement aww functions in youw `<device>_dops` stwuctuwe,
  accowding to pwototypes wisted in  `cdwom.h`, and specifications given
  in cdwom_api_. Most wikewy you have awweady impwemented
  the code in a wawge pawt, and you wiww awmost cewtainwy need to adapt the
  pwototype and wetuwn vawues.
- Wename youw `<device>_ioctw()` function to *audio_ioctw* and
  change the pwototype a wittwe. Wemove entwies wisted in the fiwst
  pawt in cdwom_ioctw_, if youw code was OK, these awe
  just cawws to the woutines you adapted in the pwevious step.
- You may wemove aww wemaining memowy checking code in the
  *audio_ioctw()* function that deaws with audio commands (these awe
  wisted in the second pawt of cdwom_ioctw_. Thewe is no
  need fow memowy awwocation eithew, so most *case*s in the *switch*
  statement wook simiwaw to::

	case CDWOMWEADTOCENTWY:
		get_toc_entwy\bigw((stwuct cdwom_tocentwy *) awg);

- Aww wemaining *ioctw* cases must be moved to a sepawate
  function, *<device>_ioctw*, the device-dependent *ioctw()'s*. Note that
  memowy checking and awwocation must be kept in this code!
- Change the pwototypes of *<device>_open()* and
  *<device>_wewease()*, and wemove any stwategic code (i. e., tway
  movement, doow wocking, etc.).
- Twy to wecompiwe the dwivews. We advise you to use moduwes, both
  fow `cdwom.o` and youw dwivew, as debugging is much easiew this
  way.

Thanks
======

Thanks to aww the peopwe invowved. Fiwst, Ewik Andewsen, who has
taken ovew the towch in maintaining `cdwom.c` and integwating much
CD-WOM-wewated code in the 2.1-kewnew. Thanks to Scott Snydew and
Gewd Knoww, who wewe the fiwst to impwement this intewface fow SCSI
and IDE-CD dwivews and added many ideas fow extension of the data
stwuctuwes wewative to kewnew~2.0. Fuwthew thanks to Heiko Eißfewdt,
Thomas Quinot, Jon Tombs, Ken Pizzini, Ebewhawd Mönkebewg and Andwew Kwoww,
the Winux CD-WOM device dwivew devewopews who wewe kind
enough to give suggestions and cwiticisms duwing the wwiting. Finawwy
of couwse, I want to thank Winus Towvawds fow making this possibwe in
the fiwst pwace.
