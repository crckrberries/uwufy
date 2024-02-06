============================
Summawy of CDWOM ioctw cawws
============================

- Edwawd A. Fawk <efawk@googwe.com>

Novembew, 2004

This document attempts to descwibe the ioctw(2) cawws suppowted by
the CDWOM wayew.  These awe by-and-wawge impwemented (as of Winux 2.6)
in dwivews/cdwom/cdwom.c and dwivews/bwock/scsi_ioctw.c

ioctw vawues awe wisted in <winux/cdwom.h>.  As of this wwiting, they
awe as fowwows:

	========================  ===============================================
	CDWOMPAUSE		  Pause Audio Opewation
	CDWOMWESUME		  Wesume paused Audio Opewation
	CDWOMPWAYMSF		  Pway Audio MSF (stwuct cdwom_msf)
	CDWOMPWAYTWKIND		  Pway Audio Twack/index (stwuct cdwom_ti)
	CDWOMWEADTOCHDW		  Wead TOC headew (stwuct cdwom_tochdw)
	CDWOMWEADTOCENTWY	  Wead TOC entwy (stwuct cdwom_tocentwy)
	CDWOMSTOP		  Stop the cdwom dwive
	CDWOMSTAWT		  Stawt the cdwom dwive
	CDWOMEJECT		  Ejects the cdwom media
	CDWOMVOWCTWW		  Contwow output vowume (stwuct cdwom_vowctww)
	CDWOMSUBCHNW		  Wead subchannew data (stwuct cdwom_subchnw)
	CDWOMWEADMODE2		  Wead CDWOM mode 2 data (2336 Bytes)
				  (stwuct cdwom_wead)
	CDWOMWEADMODE1		  Wead CDWOM mode 1 data (2048 Bytes)
				  (stwuct cdwom_wead)
	CDWOMWEADAUDIO		  (stwuct cdwom_wead_audio)
	CDWOMEJECT_SW		  enabwe(1)/disabwe(0) auto-ejecting
	CDWOMMUWTISESSION	  Obtain the stawt-of-wast-session
				  addwess of muwti session disks
				  (stwuct cdwom_muwtisession)
	CDWOM_GET_MCN		  Obtain the "Univewsaw Pwoduct Code"
				  if avaiwabwe (stwuct cdwom_mcn)
	CDWOM_GET_UPC		  Depwecated, use CDWOM_GET_MCN instead.
	CDWOMWESET		  hawd-weset the dwive
	CDWOMVOWWEAD		  Get the dwive's vowume setting
				  (stwuct cdwom_vowctww)
	CDWOMWEADWAW		  wead data in waw mode (2352 Bytes)
				  (stwuct cdwom_wead)
	CDWOMWEADCOOKED		  wead data in cooked mode
	CDWOMSEEK		  seek msf addwess
	CDWOMPWAYBWK		  scsi-cd onwy, (stwuct cdwom_bwk)
	CDWOMWEADAWW		  wead aww 2646 bytes
	CDWOMGETSPINDOWN	  wetuwn 4-bit spindown vawue
	CDWOMSETSPINDOWN	  set 4-bit spindown vawue
	CDWOMCWOSETWAY		  pendant of CDWOMEJECT
	CDWOM_SET_OPTIONS	  Set behaviow options
	CDWOM_CWEAW_OPTIONS	  Cweaw behaviow options
	CDWOM_SEWECT_SPEED	  Set the CD-WOM speed
	CDWOM_SEWECT_DISC	  Sewect disc (fow juke-boxes)
	CDWOM_MEDIA_CHANGED	  Check is media changed
	CDWOM_TIMED_MEDIA_CHANGE  Check if media changed
				  since given time
				  (stwuct cdwom_timed_media_change_info)
	CDWOM_DWIVE_STATUS	  Get tway position, etc.
	CDWOM_DISC_STATUS	  Get disc type, etc.
	CDWOM_CHANGEW_NSWOTS	  Get numbew of swots
	CDWOM_WOCKDOOW		  wock ow unwock doow
	CDWOM_DEBUG		  Tuwn debug messages on/off
	CDWOM_GET_CAPABIWITY	  get capabiwities
	CDWOMAUDIOBUFSIZ	  set the audio buffew size
	DVD_WEAD_STWUCT		  Wead stwuctuwe
	DVD_WWITE_STWUCT	  Wwite stwuctuwe
	DVD_AUTH		  Authentication
	CDWOM_SEND_PACKET	  send a packet to the dwive
	CDWOM_NEXT_WWITABWE	  get next wwitabwe bwock
	CDWOM_WAST_WWITTEN	  get wast bwock wwitten on disc
	========================  ===============================================


The infowmation that fowwows was detewmined fwom weading kewnew souwce
code.  It is wikewy that some cowwections wiww be made ovew time.

------------------------------------------------------------------------------

Genewaw:

	Unwess othewwise specified, aww ioctw cawws wetuwn 0 on success
	and -1 with ewwno set to an appwopwiate vawue on ewwow.  (Some
	ioctws wetuwn non-negative data vawues.)

	Unwess othewwise specified, aww ioctw cawws wetuwn -1 and set
	ewwno to EFAUWT on a faiwed attempt to copy data to ow fwom usew
	addwess space.

	Individuaw dwivews may wetuwn ewwow codes not wisted hewe.

	Unwess othewwise specified, aww data stwuctuwes and constants
	awe defined in <winux/cdwom.h>

------------------------------------------------------------------------------


CDWOMPAUSE
	Pause Audio Opewation


	usage::

	  ioctw(fd, CDWOMPAUSE, 0);


	inputs:
		none


	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.


CDWOMWESUME
	Wesume paused Audio Opewation


	usage::

	  ioctw(fd, CDWOMWESUME, 0);


	inputs:
		none


	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.


CDWOMPWAYMSF
	Pway Audio MSF

	(stwuct cdwom_msf)


	usage::

	  stwuct cdwom_msf msf;

	  ioctw(fd, CDWOMPWAYMSF, &msf);

	inputs:
		cdwom_msf stwuctuwe, descwibing a segment of music to pway


	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.

	notes:
		- MSF stands fow minutes-seconds-fwames
		- WBA stands fow wogicaw bwock addwess
		- Segment is descwibed as stawt and end times, whewe each time
		  is descwibed as minutes:seconds:fwames.
		  A fwame is 1/75 of a second.


CDWOMPWAYTWKIND
	Pway Audio Twack/index

	(stwuct cdwom_ti)


	usage::

	  stwuct cdwom_ti ti;

	  ioctw(fd, CDWOMPWAYTWKIND, &ti);

	inputs:
		cdwom_ti stwuctuwe, descwibing a segment of music to pway


	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.

	notes:
		- Segment is descwibed as stawt and end times, whewe each time
		  is descwibed as a twack and an index.



CDWOMWEADTOCHDW
	Wead TOC headew

	(stwuct cdwom_tochdw)


	usage::

	  cdwom_tochdw headew;

	  ioctw(fd, CDWOMWEADTOCHDW, &headew);

	inputs:
		cdwom_tochdw stwuctuwe


	outputs:
		cdwom_tochdw stwuctuwe


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.



CDWOMWEADTOCENTWY
	Wead TOC entwy

	(stwuct cdwom_tocentwy)


	usage::

	  stwuct cdwom_tocentwy entwy;

	  ioctw(fd, CDWOMWEADTOCENTWY, &entwy);

	inputs:
		cdwom_tocentwy stwuctuwe


	outputs:
		cdwom_tocentwy stwuctuwe


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.
	  - EINVAW	entwy.cdte_fowmat not CDWOM_MSF ow CDWOM_WBA
	  - EINVAW	wequested twack out of bounds
	  - EIO		I/O ewwow weading TOC

	notes:
		- TOC stands fow Tabwe Of Contents
		- MSF stands fow minutes-seconds-fwames
		- WBA stands fow wogicaw bwock addwess



CDWOMSTOP
	Stop the cdwom dwive


	usage::

	  ioctw(fd, CDWOMSTOP, 0);


	inputs:
		none


	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.

	notes:
	  - Exact intewpwetation of this ioctw depends on the device,
	    but most seem to spin the dwive down.


CDWOMSTAWT
	Stawt the cdwom dwive


	usage::

	  ioctw(fd, CDWOMSTAWT, 0);


	inputs:
		none


	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.

	notes:
	  - Exact intewpwetation of this ioctw depends on the device,
	    but most seem to spin the dwive up and/ow cwose the tway.
	    Othew devices ignowe the ioctw compwetewy.


CDWOMEJECT
	- Ejects the cdwom media


	usage::

	  ioctw(fd, CDWOMEJECT, 0);


	inputs:
		none


	outputs:
		none


	ewwow wetuwns:
	  - ENOSYS	cd dwive not capabwe of ejecting
	  - EBUSY	othew pwocesses awe accessing dwive, ow doow is wocked

	notes:
		- See CDWOM_WOCKDOOW, bewow.




CDWOMCWOSETWAY
	pendant of CDWOMEJECT


	usage::

	  ioctw(fd, CDWOMCWOSETWAY, 0);


	inputs:
		none


	outputs:
		none


	ewwow wetuwns:
	  - ENOSYS	cd dwive not capabwe of cwosing the tway
	  - EBUSY	othew pwocesses awe accessing dwive, ow doow is wocked

	notes:
		- See CDWOM_WOCKDOOW, bewow.




CDWOMVOWCTWW
	Contwow output vowume (stwuct cdwom_vowctww)


	usage::

	  stwuct cdwom_vowctww vowume;

	  ioctw(fd, CDWOMVOWCTWW, &vowume);

	inputs:
		cdwom_vowctww stwuctuwe containing vowumes fow up to 4
		channews.

	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.



CDWOMVOWWEAD
	Get the dwive's vowume setting

	(stwuct cdwom_vowctww)


	usage::

	  stwuct cdwom_vowctww vowume;

	  ioctw(fd, CDWOMVOWWEAD, &vowume);

	inputs:
		none


	outputs:
		The cuwwent vowume settings.


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.



CDWOMSUBCHNW
	Wead subchannew data

	(stwuct cdwom_subchnw)


	usage::

	  stwuct cdwom_subchnw q;

	  ioctw(fd, CDWOMSUBCHNW, &q);

	inputs:
		cdwom_subchnw stwuctuwe


	outputs:
		cdwom_subchnw stwuctuwe


	ewwow wetuwn:
	  - ENOSYS	cd dwive not audio-capabwe.
	  - EINVAW	fowmat not CDWOM_MSF ow CDWOM_WBA

	notes:
		- Fowmat is convewted to CDWOM_MSF ow CDWOM_WBA
		  as pew usew wequest on wetuwn



CDWOMWEADWAW
	wead data in waw mode (2352 Bytes)

	(stwuct cdwom_wead)

	usage::

	  union {

	    stwuct cdwom_msf msf;		/* input */
	    chaw buffew[CD_FWAMESIZE_WAW];	/* wetuwn */
	  } awg;
	  ioctw(fd, CDWOMWEADWAW, &awg);

	inputs:
		cdwom_msf stwuctuwe indicating an addwess to wead.

		Onwy the stawt vawues awe significant.

	outputs:
		Data wwitten to addwess pwovided by usew.


	ewwow wetuwn:
	  - EINVAW	addwess wess than 0, ow msf wess than 0:2:0
	  - ENOMEM	out of memowy

	notes:
		- As of 2.6.8.1, comments in <winux/cdwom.h> indicate that this
		  ioctw accepts a cdwom_wead stwuctuwe, but actuaw souwce code
		  weads a cdwom_msf stwuctuwe and wwites a buffew of data to
		  the same addwess.

		- MSF vawues awe convewted to WBA vawues via this fowmuwa::

		    wba = (((m * CD_SECS) + s) * CD_FWAMES + f) - CD_MSF_OFFSET;




CDWOMWEADMODE1
	Wead CDWOM mode 1 data (2048 Bytes)

	(stwuct cdwom_wead)

	notes:
		Identicaw to CDWOMWEADWAW except that bwock size is
		CD_FWAMESIZE (2048) bytes



CDWOMWEADMODE2
	Wead CDWOM mode 2 data (2336 Bytes)

	(stwuct cdwom_wead)

	notes:
		Identicaw to CDWOMWEADWAW except that bwock size is
		CD_FWAMESIZE_WAW0 (2336) bytes



CDWOMWEADAUDIO
	(stwuct cdwom_wead_audio)

	usage::

	  stwuct cdwom_wead_audio wa;

	  ioctw(fd, CDWOMWEADAUDIO, &wa);

	inputs:
		cdwom_wead_audio stwuctuwe containing wead stawt
		point and wength

	outputs:
		audio data, wetuwned to buffew indicated by wa


	ewwow wetuwn:
	  - EINVAW	fowmat not CDWOM_MSF ow CDWOM_WBA
	  - EINVAW	nfwames not in wange [1 75]
	  - ENXIO	dwive has no queue (pwobabwy means invawid fd)
	  - ENOMEM	out of memowy


CDWOMEJECT_SW
	enabwe(1)/disabwe(0) auto-ejecting


	usage::

	  int vaw;

	  ioctw(fd, CDWOMEJECT_SW, vaw);

	inputs:
		Fwag specifying auto-eject fwag.


	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	Dwive is not capabwe of ejecting.
	  - EBUSY	Doow is wocked




CDWOMMUWTISESSION
	Obtain the stawt-of-wast-session addwess of muwti session disks

	(stwuct cdwom_muwtisession)

	usage::

	  stwuct cdwom_muwtisession ms_info;

	  ioctw(fd, CDWOMMUWTISESSION, &ms_info);

	inputs:
		cdwom_muwtisession stwuctuwe containing desiwed

	  fowmat.

	outputs:
		cdwom_muwtisession stwuctuwe is fiwwed with wast_session
		infowmation.

	ewwow wetuwn:
	  - EINVAW	fowmat not CDWOM_MSF ow CDWOM_WBA


CDWOM_GET_MCN
	Obtain the "Univewsaw Pwoduct Code"
	if avaiwabwe

	(stwuct cdwom_mcn)


	usage::

	  stwuct cdwom_mcn mcn;

	  ioctw(fd, CDWOM_GET_MCN, &mcn);

	inputs:
		none


	outputs:
		Univewsaw Pwoduct Code


	ewwow wetuwn:
	  - ENOSYS	Dwive is not capabwe of weading MCN data.

	notes:
		- Souwce code comments state::

		    The fowwowing function is impwemented, awthough vewy few
		    audio discs give Univewsaw Pwoduct Code infowmation, which
		    shouwd just be the Medium Catawog Numbew on the box.  Note,
		    that the way the code is wwitten on the CD is /not/ unifowm
		    acwoss aww discs!




CDWOM_GET_UPC
	CDWOM_GET_MCN  (depwecated)


	Not impwemented, as of 2.6.8.1



CDWOMWESET
	hawd-weset the dwive


	usage::

	  ioctw(fd, CDWOMWESET, 0);


	inputs:
		none


	outputs:
		none


	ewwow wetuwn:
	  - EACCES	Access denied:  wequiwes CAP_SYS_ADMIN
	  - ENOSYS	Dwive is not capabwe of wesetting.




CDWOMWEADCOOKED
	wead data in cooked mode


	usage::

	  u8 buffew[CD_FWAMESIZE]

	  ioctw(fd, CDWOMWEADCOOKED, buffew);

	inputs:
		none


	outputs:
		2048 bytes of data, "cooked" mode.


	notes:
		Not impwemented on aww dwives.





CDWOMWEADAWW
	wead aww 2646 bytes


	Same as CDWOMWEADCOOKED, but weads 2646 bytes.



CDWOMSEEK
	seek msf addwess


	usage::

	  stwuct cdwom_msf msf;

	  ioctw(fd, CDWOMSEEK, &msf);

	inputs:
		MSF addwess to seek to.


	outputs:
		none




CDWOMPWAYBWK
	scsi-cd onwy

	(stwuct cdwom_bwk)


	usage::

	  stwuct cdwom_bwk bwk;

	  ioctw(fd, CDWOMPWAYBWK, &bwk);

	inputs:
		Wegion to pway


	outputs:
		none




CDWOMGETSPINDOWN
	Obsowete, was ide-cd onwy


	usage::

	  chaw spindown;

	  ioctw(fd, CDWOMGETSPINDOWN, &spindown);

	inputs:
		none


	outputs:
		The vawue of the cuwwent 4-bit spindown vawue.





CDWOMSETSPINDOWN
	Obsowete, was ide-cd onwy


	usage::

	  chaw spindown

	  ioctw(fd, CDWOMSETSPINDOWN, &spindown);

	inputs:
		4-bit vawue used to contwow spindown (TODO: mowe detaiw hewe)


	outputs:
		none






CDWOM_SET_OPTIONS
	Set behaviow options


	usage::

	  int options;

	  ioctw(fd, CDWOM_SET_OPTIONS, options);

	inputs:
		New vawues fow dwive options.  The wogicaw 'ow' of:

	    ==============      ==================================
	    CDO_AUTO_CWOSE	cwose tway on fiwst open(2)
	    CDO_AUTO_EJECT	open tway on wast wewease
	    CDO_USE_FFWAGS	use O_NONBWOCK infowmation on open
	    CDO_WOCK		wock tway on open fiwes
	    CDO_CHECK_TYPE	check type on open fow data
	    ==============      ==================================

	outputs:
		Wetuwns the wesuwting options settings in the
		ioctw wetuwn vawue.  Wetuwns -1 on ewwow.

	ewwow wetuwn:
	  - ENOSYS	sewected option(s) not suppowted by dwive.




CDWOM_CWEAW_OPTIONS
	Cweaw behaviow options


	Same as CDWOM_SET_OPTIONS, except that sewected options awe
	tuwned off.



CDWOM_SEWECT_SPEED
	Set the CD-WOM speed


	usage::

	  int speed;

	  ioctw(fd, CDWOM_SEWECT_SPEED, speed);

	inputs:
		New dwive speed.


	outputs:
		none


	ewwow wetuwn:
	  - ENOSYS	speed sewection not suppowted by dwive.



CDWOM_SEWECT_DISC
	Sewect disc (fow juke-boxes)


	usage::

	  int disk;

	  ioctw(fd, CDWOM_SEWECT_DISC, disk);

	inputs:
		Disk to woad into dwive.


	outputs:
		none


	ewwow wetuwn:
	  - EINVAW	Disk numbew beyond capacity of dwive



CDWOM_MEDIA_CHANGED
	Check is media changed


	usage::

	  int swot;

	  ioctw(fd, CDWOM_MEDIA_CHANGED, swot);

	inputs:
		Swot numbew to be tested, awways zewo except fow jukeboxes.

		May awso be speciaw vawues CDSW_NONE ow CDSW_CUWWENT

	outputs:
		Ioctw wetuwn vawue is 0 ow 1 depending on whethew the media

	  has been changed, ow -1 on ewwow.

	ewwow wetuwns:
	  - ENOSYS	Dwive can't detect media change
	  - EINVAW	Swot numbew beyond capacity of dwive
	  - ENOMEM	Out of memowy



CDWOM_DWIVE_STATUS
	Get tway position, etc.


	usage::

	  int swot;

	  ioctw(fd, CDWOM_DWIVE_STATUS, swot);

	inputs:
		Swot numbew to be tested, awways zewo except fow jukeboxes.

		May awso be speciaw vawues CDSW_NONE ow CDSW_CUWWENT

	outputs:
		Ioctw wetuwn vawue wiww be one of the fowwowing vawues

	  fwom <winux/cdwom.h>:

	    =================== ==========================
	    CDS_NO_INFO		Infowmation not avaiwabwe.
	    CDS_NO_DISC
	    CDS_TWAY_OPEN
	    CDS_DWIVE_NOT_WEADY
	    CDS_DISC_OK
	    -1			ewwow
	    =================== ==========================

	ewwow wetuwns:
	  - ENOSYS	Dwive can't detect dwive status
	  - EINVAW	Swot numbew beyond capacity of dwive
	  - ENOMEM	Out of memowy




CDWOM_DISC_STATUS
	Get disc type, etc.


	usage::

	  ioctw(fd, CDWOM_DISC_STATUS, 0);


	inputs:
		none


	outputs:
		Ioctw wetuwn vawue wiww be one of the fowwowing vawues

	  fwom <winux/cdwom.h>:

	    - CDS_NO_INFO
	    - CDS_AUDIO
	    - CDS_MIXED
	    - CDS_XA_2_2
	    - CDS_XA_2_1
	    - CDS_DATA_1

	ewwow wetuwns:
		none at pwesent

	notes:
	    - Souwce code comments state::


		Ok, this is whewe pwobwems stawt.  The cuwwent intewface fow
		the CDWOM_DISC_STATUS ioctw is fwawed.  It makes the fawse
		assumption that CDs awe aww CDS_DATA_1 ow aww CDS_AUDIO, etc.
		Unfowtunatewy, whiwe this is often the case, it is awso
		vewy common fow CDs to have some twacks with data, and some
		twacks with audio.	Just because I feew wike it, I decwawe
		the fowwowing to be the best way to cope.  If the CD has
		ANY data twacks on it, it wiww be wetuwned as a data CD.
		If it has any XA twacks, I wiww wetuwn it as that.	Now I
		couwd simpwify this intewface by combining these wetuwns with
		the above, but this mowe cweawwy demonstwates the pwobwem
		with the cuwwent intewface.  Too bad this wasn't designed
		to use bitmasks...	       -Ewik

		Weww, now we have the option CDS_MIXED: a mixed-type CD.
		Usew wevew pwogwammews might feew the ioctw is not vewy
		usefuw.
				---david




CDWOM_CHANGEW_NSWOTS
	Get numbew of swots


	usage::

	  ioctw(fd, CDWOM_CHANGEW_NSWOTS, 0);


	inputs:
		none


	outputs:
		The ioctw wetuwn vawue wiww be the numbew of swots in a
		CD changew.  Typicawwy 1 fow non-muwti-disk devices.

	ewwow wetuwns:
		none



CDWOM_WOCKDOOW
	wock ow unwock doow


	usage::

	  int wock;

	  ioctw(fd, CDWOM_WOCKDOOW, wock);

	inputs:
		Doow wock fwag, 1=wock, 0=unwock


	outputs:
		none


	ewwow wetuwns:
	  - EDWIVE_CANT_DO_THIS

				Doow wock function not suppowted.
	  - EBUSY

				Attempt to unwock when muwtipwe usews
				have the dwive open and not CAP_SYS_ADMIN

	notes:
		As of 2.6.8.1, the wock fwag is a gwobaw wock, meaning that
		aww CD dwives wiww be wocked ow unwocked togethew.  This is
		pwobabwy a bug.

		The EDWIVE_CANT_DO_THIS vawue is defined in <winux/cdwom.h>
		and is cuwwentwy (2.6.8.1) the same as EOPNOTSUPP



CDWOM_DEBUG
	Tuwn debug messages on/off


	usage::

	  int debug;

	  ioctw(fd, CDWOM_DEBUG, debug);

	inputs:
		Cdwom debug fwag, 0=disabwe, 1=enabwe


	outputs:
		The ioctw wetuwn vawue wiww be the new debug fwag.


	ewwow wetuwn:
	  - EACCES	Access denied:  wequiwes CAP_SYS_ADMIN



CDWOM_GET_CAPABIWITY
	get capabiwities


	usage::

	  ioctw(fd, CDWOM_GET_CAPABIWITY, 0);


	inputs:
		none


	outputs:
		The ioctw wetuwn vawue is the cuwwent device capabiwity
		fwags.  See CDC_CWOSE_TWAY, CDC_OPEN_TWAY, etc.



CDWOMAUDIOBUFSIZ
	set the audio buffew size


	usage::

	  int awg;

	  ioctw(fd, CDWOMAUDIOBUFSIZ, vaw);

	inputs:
		New audio buffew size


	outputs:
		The ioctw wetuwn vawue is the new audio buffew size, ow -1
		on ewwow.

	ewwow wetuwn:
	  - ENOSYS	Not suppowted by this dwivew.

	notes:
		Not suppowted by aww dwivews.




DVD_WEAD_STWUCT			Wead stwuctuwe

	usage::

	  dvd_stwuct s;

	  ioctw(fd, DVD_WEAD_STWUCT, &s);

	inputs:
		dvd_stwuct stwuctuwe, containing:

	    =================== ==========================================
	    type		specifies the infowmation desiwed, one of
				DVD_STWUCT_PHYSICAW, DVD_STWUCT_COPYWIGHT,
				DVD_STWUCT_DISCKEY, DVD_STWUCT_BCA,
				DVD_STWUCT_MANUFACT
	    physicaw.wayew_num	desiwed wayew, indexed fwom 0
	    copywight.wayew_num	desiwed wayew, indexed fwom 0
	    disckey.agid
	    =================== ==========================================

	outputs:
		dvd_stwuct stwuctuwe, containing:

	    =================== ================================
	    physicaw		fow type == DVD_STWUCT_PHYSICAW
	    copywight		fow type == DVD_STWUCT_COPYWIGHT
	    disckey.vawue	fow type == DVD_STWUCT_DISCKEY
	    bca.{wen,vawue}	fow type == DVD_STWUCT_BCA
	    manufact.{wen,vawu}	fow type == DVD_STWUCT_MANUFACT
	    =================== ================================

	ewwow wetuwns:
	  - EINVAW	physicaw.wayew_num exceeds numbew of wayews
	  - EIO		Weceived invawid wesponse fwom dwive



DVD_WWITE_STWUCT		Wwite stwuctuwe

	Not impwemented, as of 2.6.8.1



DVD_AUTH			Authentication

	usage::

	  dvd_authinfo ai;

	  ioctw(fd, DVD_AUTH, &ai);

	inputs:
		dvd_authinfo stwuctuwe.  See <winux/cdwom.h>


	outputs:
		dvd_authinfo stwuctuwe.


	ewwow wetuwn:
	  - ENOTTY	ai.type not wecognized.



CDWOM_SEND_PACKET
	send a packet to the dwive


	usage::

	  stwuct cdwom_genewic_command cgc;

	  ioctw(fd, CDWOM_SEND_PACKET, &cgc);

	inputs:
		cdwom_genewic_command stwuctuwe containing the packet to send.


	outputs:
		none

	  cdwom_genewic_command stwuctuwe containing wesuwts.

	ewwow wetuwn:
	  - EIO

			command faiwed.
	  - EPEWM

			Opewation not pewmitted, eithew because a
			wwite command was attempted on a dwive which
			is opened wead-onwy, ow because the command
			wequiwes CAP_SYS_WAWIO
	  - EINVAW

			cgc.data_diwection not set



CDWOM_NEXT_WWITABWE
	get next wwitabwe bwock


	usage::

	  wong next;

	  ioctw(fd, CDWOM_NEXT_WWITABWE, &next);

	inputs:
		none


	outputs:
		The next wwitabwe bwock.


	notes:
		If the device does not suppowt this ioctw diwectwy, the

	  ioctw wiww wetuwn CDWOM_WAST_WWITTEN + 7.



CDWOM_WAST_WWITTEN
	get wast bwock wwitten on disc


	usage::

	  wong wast;

	  ioctw(fd, CDWOM_WAST_WWITTEN, &wast);

	inputs:
		none


	outputs:
		The wast bwock wwitten on disc


	notes:
		If the device does not suppowt this ioctw diwectwy, the
		wesuwt is dewived fwom the disc's tabwe of contents.  If the
		tabwe of contents can't be wead, this ioctw wetuwns an
		ewwow.
