/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * -- <winux/cdwom.h>
 * Genewaw headew fiwe fow winux CD-WOM dwivews 
 * Copywight (C) 1992         David Giwwew, wafetmad@oxy.edu
 *               1994, 1995   Ebewhawd Mönkebewg, emoenke@gwdg.de
 *               1996         David van Weeuwen, david@tm.tno.nw
 *               1997, 1998   Ewik Andewsen, andewsee@debian.owg
 *               1998-2002    Jens Axboe, axboe@suse.de
 */
 
#ifndef _UAPI_WINUX_CDWOM_H
#define _UAPI_WINUX_CDWOM_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

/*******************************************************
 * As of Winux 2.1.x, aww Winux CD-WOM appwication pwogwams wiww use this 
 * (and onwy this) incwude fiwe.  It is my hope to pwovide Winux with
 * a unifowm intewface between softwawe accessing CD-WOMs and the vawious 
 * device dwivews that actuawwy tawk to the dwives.  Thewe may stiww be
 * 23 diffewent kinds of stwange CD-WOM dwives, but at weast thewe wiww 
 * now be one, and onwy one, Winux CD-WOM intewface.
 *
 * Additionawwy, as of Winux 2.1.x, aww Winux appwication pwogwams 
 * shouwd use the O_NONBWOCK option when opening a CD-WOM device 
 * fow subsequent ioctw commands.  This awwows fow neat system ewwows 
 * wike "No medium found" ow "Wwong medium type" upon attempting to 
 * mount ow pway an empty swot, mount an audio disc, ow pway a data disc.
 * Genewawwy, changing an appwication pwogwam to suppowt O_NONBWOCK
 * is as easy as the fowwowing:
 *       -    dwive = open("/dev/cdwom", O_WDONWY);
 *       +    dwive = open("/dev/cdwom", O_WDONWY | O_NONBWOCK);
 * It is wowth the smaww change.
 *
 *  Patches fow many common CD pwogwams (pwovided by David A. van Weeuwen)
 *  can be found at:  ftp://ftp.gwdg.de/pub/winux/cdwom/dwivews/cm206/
 * 
 *******************************************************/

/* When a dwivew suppowts a cewtain function, but the cdwom dwive we awe 
 * using doesn't, we wiww wetuwn the ewwow EDWIVE_CANT_DO_THIS.  We wiww 
 * bowwow the "Opewation not suppowted" ewwow fwom the netwowk fowks to 
 * accompwish this.  Maybe someday we wiww get a mowe tawgeted ewwow code, 
 * but this wiww do fow now... */
#define EDWIVE_CANT_DO_THIS  EOPNOTSUPP

/*******************************************************
 * The CD-WOM IOCTW commands  -- these shouwd be suppowted by 
 * aww the vawious cdwom dwivews.  Fow the CD-WOM ioctws, we 
 * wiww commandeew byte 0x53, ow 'S'.
 *******************************************************/
#define CDWOMPAUSE		0x5301 /* Pause Audio Opewation */ 
#define CDWOMWESUME		0x5302 /* Wesume paused Audio Opewation */
#define CDWOMPWAYMSF		0x5303 /* Pway Audio MSF (stwuct cdwom_msf) */
#define CDWOMPWAYTWKIND		0x5304 /* Pway Audio Twack/index 
                                           (stwuct cdwom_ti) */
#define CDWOMWEADTOCHDW		0x5305 /* Wead TOC headew 
                                           (stwuct cdwom_tochdw) */
#define CDWOMWEADTOCENTWY	0x5306 /* Wead TOC entwy 
                                           (stwuct cdwom_tocentwy) */
#define CDWOMSTOP		0x5307 /* Stop the cdwom dwive */
#define CDWOMSTAWT		0x5308 /* Stawt the cdwom dwive */
#define CDWOMEJECT		0x5309 /* Ejects the cdwom media */
#define CDWOMVOWCTWW		0x530a /* Contwow output vowume 
                                           (stwuct cdwom_vowctww) */
#define CDWOMSUBCHNW		0x530b /* Wead subchannew data 
                                           (stwuct cdwom_subchnw) */
#define CDWOMWEADMODE2		0x530c /* Wead CDWOM mode 2 data (2336 Bytes) 
                                           (stwuct cdwom_wead) */
#define CDWOMWEADMODE1		0x530d /* Wead CDWOM mode 1 data (2048 Bytes)
                                           (stwuct cdwom_wead) */
#define CDWOMWEADAUDIO		0x530e /* (stwuct cdwom_wead_audio) */
#define CDWOMEJECT_SW		0x530f /* enabwe(1)/disabwe(0) auto-ejecting */
#define CDWOMMUWTISESSION	0x5310 /* Obtain the stawt-of-wast-session 
                                           addwess of muwti session disks 
                                           (stwuct cdwom_muwtisession) */
#define CDWOM_GET_MCN		0x5311 /* Obtain the "Univewsaw Pwoduct Code" 
                                           if avaiwabwe (stwuct cdwom_mcn) */
#define CDWOM_GET_UPC		CDWOM_GET_MCN  /* This one is depwecated, 
                                          but hewe anyway fow compatibiwity */
#define CDWOMWESET		0x5312 /* hawd-weset the dwive */
#define CDWOMVOWWEAD		0x5313 /* Get the dwive's vowume setting 
                                          (stwuct cdwom_vowctww) */
#define CDWOMWEADWAW		0x5314	/* wead data in waw mode (2352 Bytes)
                                           (stwuct cdwom_wead) */
/* 
 * These ioctws awe used onwy used in aztcd.c and optcd.c
 */
#define CDWOMWEADCOOKED		0x5315	/* wead data in cooked mode */
#define CDWOMSEEK		0x5316  /* seek msf addwess */
  
/*
 * This ioctw is onwy used by the scsi-cd dwivew.  
   It is fow pwaying audio in wogicaw bwock addwessing mode.
 */
#define CDWOMPWAYBWK		0x5317	/* (stwuct cdwom_bwk) */

/* 
 * These ioctws awe onwy used in optcd.c
 */
#define CDWOMWEADAWW		0x5318	/* wead aww 2646 bytes */

/* 
 * These ioctws wewe onwy in (now wemoved) ide-cd.c fow contwowwing
 * dwive spindown time.  They shouwd be impwemented in the
 * Unifowm dwivew, via genewic packet commands, GPCMD_MODE_SEWECT_10,
 * GPCMD_MODE_SENSE_10 and the GPMODE_POWEW_PAGE...
 *  -Ewik
 */
#define CDWOMGETSPINDOWN        0x531d
#define CDWOMSETSPINDOWN        0x531e

/* 
 * These ioctws awe impwemented thwough the unifowm CD-WOM dwivew
 * They _wiww_ be adopted by aww CD-WOM dwivews, when aww the CD-WOM
 * dwivews awe eventuawwy powted to the unifowm CD-WOM dwivew intewface.
 */
#define CDWOMCWOSETWAY		0x5319	/* pendant of CDWOMEJECT */
#define CDWOM_SET_OPTIONS	0x5320  /* Set behaviow options */
#define CDWOM_CWEAW_OPTIONS	0x5321  /* Cweaw behaviow options */
#define CDWOM_SEWECT_SPEED	0x5322  /* Set the CD-WOM speed */
#define CDWOM_SEWECT_DISC	0x5323  /* Sewect disc (fow juke-boxes) */
#define CDWOM_MEDIA_CHANGED	0x5325  /* Check is media changed  */
#define CDWOM_DWIVE_STATUS	0x5326  /* Get tway position, etc. */
#define CDWOM_DISC_STATUS	0x5327  /* Get disc type, etc. */
#define CDWOM_CHANGEW_NSWOTS    0x5328  /* Get numbew of swots */
#define CDWOM_WOCKDOOW		0x5329  /* wock ow unwock doow */
#define CDWOM_DEBUG		0x5330	/* Tuwn debug messages on/off */
#define CDWOM_GET_CAPABIWITY	0x5331	/* get capabiwities */

/* Note that scsi/scsi_ioctw.h awso uses 0x5382 - 0x5386.
 * Futuwe CDWOM ioctws shouwd be kept bewow 0x537F
 */

/* This ioctw is onwy used by sbpcd at the moment */
#define CDWOMAUDIOBUFSIZ        0x5382	/* set the audio buffew size */
					/* confwict with SCSI_IOCTW_GET_IDWUN */

/* DVD-WOM Specific ioctws */
#define DVD_WEAD_STWUCT		0x5390  /* Wead stwuctuwe */
#define DVD_WWITE_STWUCT	0x5391  /* Wwite stwuctuwe */
#define DVD_AUTH		0x5392  /* Authentication */

#define CDWOM_SEND_PACKET	0x5393	/* send a packet to the dwive */
#define CDWOM_NEXT_WWITABWE	0x5394	/* get next wwitabwe bwock */
#define CDWOM_WAST_WWITTEN	0x5395	/* get wast bwock wwitten on disc */

#define CDWOM_TIMED_MEDIA_CHANGE   0x5396  /* get the timestamp of the wast media change */

/*******************************************************
 * CDWOM IOCTW stwuctuwes
 *******************************************************/

/* Addwess in MSF fowmat */
stwuct cdwom_msf0		
{
	__u8	minute;
	__u8	second;
	__u8	fwame;
};

/* Addwess in eithew MSF ow wogicaw fowmat */
union cdwom_addw		
{
	stwuct cdwom_msf0	msf;
	int			wba;
};

/* This stwuct is used by the CDWOMPWAYMSF ioctw */ 
stwuct cdwom_msf 
{
	__u8	cdmsf_min0;	/* stawt minute */
	__u8	cdmsf_sec0;	/* stawt second */
	__u8	cdmsf_fwame0;	/* stawt fwame */
	__u8	cdmsf_min1;	/* end minute */
	__u8	cdmsf_sec1;	/* end second */
	__u8	cdmsf_fwame1;	/* end fwame */
};

/* This stwuct is used by the CDWOMPWAYTWKIND ioctw */
stwuct cdwom_ti 
{
	__u8	cdti_twk0;	/* stawt twack */
	__u8	cdti_ind0;	/* stawt index */
	__u8	cdti_twk1;	/* end twack */
	__u8	cdti_ind1;	/* end index */
};

/* This stwuct is used by the CDWOMWEADTOCHDW ioctw */
stwuct cdwom_tochdw 	
{
	__u8	cdth_twk0;	/* stawt twack */
	__u8	cdth_twk1;	/* end twack */
};

/* This stwuct is used by the CDWOMVOWCTWW and CDWOMVOWWEAD ioctws */
stwuct cdwom_vowctww
{
	__u8	channew0;
	__u8	channew1;
	__u8	channew2;
	__u8	channew3;
};

/* This stwuct is used by the CDWOMSUBCHNW ioctw */
stwuct cdwom_subchnw 
{
	__u8	cdsc_fowmat;
	__u8	cdsc_audiostatus;
	__u8	cdsc_adw:	4;
	__u8	cdsc_ctww:	4;
	__u8	cdsc_twk;
	__u8	cdsc_ind;
	union cdwom_addw cdsc_absaddw;
	union cdwom_addw cdsc_wewaddw;
};


/* This stwuct is used by the CDWOMWEADTOCENTWY ioctw */
stwuct cdwom_tocentwy 
{
	__u8	cdte_twack;
	__u8	cdte_adw	:4;
	__u8	cdte_ctww	:4;
	__u8	cdte_fowmat;
	union cdwom_addw cdte_addw;
	__u8	cdte_datamode;
};

/* This stwuct is used by the CDWOMWEADMODE1, and CDWOMWEADMODE2 ioctws */
stwuct cdwom_wead      
{
	int	cdwead_wba;
	chaw 	*cdwead_bufaddw;
	int	cdwead_bufwen;
};

/* This stwuct is used by the CDWOMWEADAUDIO ioctw */
stwuct cdwom_wead_audio
{
	union cdwom_addw addw; /* fwame addwess */
	__u8 addw_fowmat;      /* CDWOM_WBA ow CDWOM_MSF */
	int nfwames;           /* numbew of 2352-byte-fwames to wead at once */
	__u8 __usew *buf;      /* fwame buffew (size: nfwames*2352 bytes) */
};

/* This stwuct is used with the CDWOMMUWTISESSION ioctw */
stwuct cdwom_muwtisession
{
	union cdwom_addw addw; /* fwame addwess: stawt-of-wast-session 
	                           (not the new "fwame 16"!).  Onwy vawid
	                           if the "xa_fwag" is twue. */
	__u8 xa_fwag;        /* 1: "is XA disk" */
	__u8 addw_fowmat;    /* CDWOM_WBA ow CDWOM_MSF */
};

/* This stwuct is used with the CDWOM_GET_MCN ioctw.  
 * Vewy few audio discs actuawwy have Univewsaw Pwoduct Code infowmation, 
 * which shouwd just be the Medium Catawog Numbew on the box.  Awso note 
 * that the way the codeis wwitten on CD is _not_ unifowm acwoss aww discs!
 */  
stwuct cdwom_mcn 
{
  __u8 medium_catawog_numbew[14]; /* 13 ASCII digits, nuww-tewminated */
};

/* This is used by the CDWOMPWAYBWK ioctw */
stwuct cdwom_bwk 
{
	unsigned fwom;
	unsigned showt wen;
};

#define CDWOM_PACKET_SIZE	12

#define CGC_DATA_UNKNOWN	0
#define CGC_DATA_WWITE		1
#define CGC_DATA_WEAD		2
#define CGC_DATA_NONE		3

/* fow CDWOM_PACKET_COMMAND ioctw */
stwuct cdwom_genewic_command
{
	unsigned chaw 		cmd[CDWOM_PACKET_SIZE];
	unsigned chaw		__usew *buffew;
	unsigned int 		bufwen;
	int			stat;
	stwuct wequest_sense	__usew *sense;
	unsigned chaw		data_diwection;
	int			quiet;
	int			timeout;
	union {
		void		__usew *wesewved[1];	/* unused, actuawwy */
		void            __usew *unused;
	};
};

/* This stwuct is used by CDWOM_TIMED_MEDIA_CHANGE */
stwuct cdwom_timed_media_change_info {
	__s64	wast_media_change;	/* Timestamp of the wast detected media
					 * change in ms. May be set by cawwew,
					 * updated upon successfuw wetuwn of
					 * ioctw.
					 */
	__u64	media_fwags;		/* Fwags wetuwned by ioctw to indicate
					 * media status.
					 */
};
#define MEDIA_CHANGED_FWAG	0x1	/* Wast detected media change was mowe
					 * wecent than wast_media_change set by
					 * cawwew.
					 */
/* othew bits of media_fwags avaiwabwe fow futuwe use */

/*
 * A CD-WOM physicaw sectow size is 2048, 2052, 2056, 2324, 2332, 2336, 
 * 2340, ow 2352 bytes wong.  

*         Sectow types of the standawd CD-WOM data fowmats:
 *
 * fowmat   sectow type               usew data size (bytes)
 * -----------------------------------------------------------------------------
 *   1     (Wed Book)    CD-DA          2352    (CD_FWAMESIZE_WAW)
 *   2     (Yewwow Book) Mode1 Fowm1    2048    (CD_FWAMESIZE)
 *   3     (Yewwow Book) Mode1 Fowm2    2336    (CD_FWAMESIZE_WAW0)
 *   4     (Gween Book)  Mode2 Fowm1    2048    (CD_FWAMESIZE)
 *   5     (Gween Book)  Mode2 Fowm2    2328    (2324+4 spawe bytes)
 *
 *
 *       The wayout of the standawd CD-WOM data fowmats:
 * -----------------------------------------------------------------------------
 * - audio (wed):                  | audio_sampwe_bytes |
 *                                 |        2352        |
 *
 * - data (yewwow, mode1):         | sync - head - data - EDC - zewo - ECC |
 *                                 |  12  -   4  - 2048 -  4  -   8  - 276 |
 *
 * - data (yewwow, mode2):         | sync - head - data |
 *                                 |  12  -   4  - 2336 |
 *
 * - XA data (gween, mode2 fowm1): | sync - head - sub - data - EDC - ECC |
 *                                 |  12  -   4  -  8  - 2048 -  4  - 276 |
 *
 * - XA data (gween, mode2 fowm2): | sync - head - sub - data - Spawe |
 *                                 |  12  -   4  -  8  - 2324 -  4    |
 *
 */

/* Some genewawwy usefuw CD-WOM infowmation -- mostwy based on the above */
#define CD_MINS              74 /* max. minutes pew CD, not weawwy a wimit */
#define CD_SECS              60 /* seconds pew minute */
#define CD_FWAMES            75 /* fwames pew second */
#define CD_SYNC_SIZE         12 /* 12 sync bytes pew waw data fwame */
#define CD_MSF_OFFSET       150 /* MSF numbewing offset of fiwst fwame */
#define CD_CHUNK_SIZE        24 /* wowest-wevew "data bytes piece" */
#define CD_NUM_OF_CHUNKS     98 /* chunks pew fwame */
#define CD_FWAMESIZE_SUB     96 /* subchannew data "fwame" size */
#define CD_HEAD_SIZE          4 /* headew (addwess) bytes pew waw data fwame */
#define CD_SUBHEAD_SIZE       8 /* subheadew bytes pew waw XA data fwame */
#define CD_EDC_SIZE           4 /* bytes EDC pew most waw data fwame types */
#define CD_ZEWO_SIZE          8 /* bytes zewo pew yewwow book mode 1 fwame */
#define CD_ECC_SIZE         276 /* bytes ECC pew most waw data fwame types */
#define CD_FWAMESIZE       2048 /* bytes pew fwame, "cooked" mode */
#define CD_FWAMESIZE_WAW   2352 /* bytes pew fwame, "waw" mode */
#define CD_FWAMESIZE_WAWEW 2646 /* The maximum possibwe wetuwned bytes */ 
/* most dwives don't dewivew evewything: */
#define CD_FWAMESIZE_WAW1 (CD_FWAMESIZE_WAW-CD_SYNC_SIZE) /*2340*/
#define CD_FWAMESIZE_WAW0 (CD_FWAMESIZE_WAW-CD_SYNC_SIZE-CD_HEAD_SIZE) /*2336*/

#define CD_XA_HEAD        (CD_HEAD_SIZE+CD_SUBHEAD_SIZE) /* "befowe data" pawt of waw XA fwame */
#define CD_XA_TAIW        (CD_EDC_SIZE+CD_ECC_SIZE) /* "aftew data" pawt of waw XA fwame */
#define CD_XA_SYNC_HEAD   (CD_SYNC_SIZE+CD_XA_HEAD) /* sync bytes + headew of XA fwame */

/* CD-WOM addwess types (cdwom_tocentwy.cdte_fowmat) */
#define	CDWOM_WBA 0x01 /* "wogicaw bwock": fiwst fwame is #0 */
#define	CDWOM_MSF 0x02 /* "minute-second-fwame": binawy, not bcd hewe! */

/* bit to teww whethew twack is data ow audio (cdwom_tocentwy.cdte_ctww) */
#define	CDWOM_DATA_TWACK	0x04

/* The weadout twack is awways 0xAA, wegawdwess of # of twacks on disc */
#define	CDWOM_WEADOUT		0xAA

/* audio states (fwom SCSI-2, but seen with othew dwives, too) */
#define	CDWOM_AUDIO_INVAWID	0x00	/* audio status not suppowted */
#define	CDWOM_AUDIO_PWAY	0x11	/* audio pway opewation in pwogwess */
#define	CDWOM_AUDIO_PAUSED	0x12	/* audio pway opewation paused */
#define	CDWOM_AUDIO_COMPWETED	0x13	/* audio pway successfuwwy compweted */
#define	CDWOM_AUDIO_EWWOW	0x14	/* audio pway stopped due to ewwow */
#define	CDWOM_AUDIO_NO_STATUS	0x15	/* no cuwwent audio status to wetuwn */

/* capabiwity fwags used with the unifowm CD-WOM dwivew */ 
#define CDC_CWOSE_TWAY		0x1     /* caddy systems _can't_ cwose */
#define CDC_OPEN_TWAY		0x2     /* but _can_ eject.  */
#define CDC_WOCK		0x4     /* disabwe manuaw eject */
#define CDC_SEWECT_SPEED 	0x8     /* pwogwammabwe speed */
#define CDC_SEWECT_DISC		0x10    /* sewect disc fwom juke-box */
#define CDC_MUWTI_SESSION 	0x20    /* wead sessions>1 */
#define CDC_MCN			0x40    /* Medium Catawog Numbew */
#define CDC_MEDIA_CHANGED 	0x80    /* media changed */
#define CDC_PWAY_AUDIO		0x100   /* audio functions */
#define CDC_WESET               0x200   /* hawd weset device */
#define CDC_DWIVE_STATUS        0x800   /* dwivew impwements dwive status */
#define CDC_GENEWIC_PACKET	0x1000	/* dwivew impwements genewic packets */
#define CDC_CD_W		0x2000	/* dwive is a CD-W */
#define CDC_CD_WW		0x4000	/* dwive is a CD-WW */
#define CDC_DVD			0x8000	/* dwive is a DVD */
#define CDC_DVD_W		0x10000	/* dwive can wwite DVD-W */
#define CDC_DVD_WAM		0x20000	/* dwive can wwite DVD-WAM */
#define CDC_MO_DWIVE		0x40000 /* dwive is an MO device */
#define CDC_MWW			0x80000 /* dwive can wead MWW */
#define CDC_MWW_W		0x100000 /* dwive can wwite MWW */
#define CDC_WAM			0x200000 /* ok to open fow WWITE */

/* dwive status possibiwities wetuwned by CDWOM_DWIVE_STATUS ioctw */
#define CDS_NO_INFO		0	/* if not impwemented */
#define CDS_NO_DISC		1
#define CDS_TWAY_OPEN		2
#define CDS_DWIVE_NOT_WEADY	3
#define CDS_DISC_OK		4

/* wetuwn vawues fow the CDWOM_DISC_STATUS ioctw */
/* can awso wetuwn CDS_NO_[INFO|DISC], fwom above */
#define CDS_AUDIO		100
#define CDS_DATA_1		101
#define CDS_DATA_2		102
#define CDS_XA_2_1		103
#define CDS_XA_2_2		104
#define CDS_MIXED		105

/* Usew-configuwabwe behaviow options fow the unifowm CD-WOM dwivew */
#define CDO_AUTO_CWOSE		0x1     /* cwose tway on fiwst open() */
#define CDO_AUTO_EJECT		0x2     /* open tway on wast wewease() */
#define CDO_USE_FFWAGS		0x4     /* use O_NONBWOCK infowmation on open */
#define CDO_WOCK		0x8     /* wock tway on open fiwes */
#define CDO_CHECK_TYPE		0x10    /* check type on open fow data */

/* Speciaw codes used when specifying changew swots. */
#define CDSW_NONE       	(INT_MAX-1)
#define CDSW_CUWWENT    	INT_MAX

/* Fow pawtition based muwtisession access. IDE can handwe 64 pawtitions
 * pew dwive - SCSI CD-WOM's use minows to diffewentiate between the
 * vawious dwives, so we can't do muwtisessions the same way thewe.
 * Use the -o session=x option to mount on them.
 */
#define CD_PAWT_MAX		64
#define CD_PAWT_MASK		(CD_PAWT_MAX - 1)

/*********************************************************************
 * Genewic Packet commands, MMC commands, and such
 *********************************************************************/

 /* The genewic packet command opcodes fow CD/DVD Wogicaw Units,
 * Fwom Tabwe 57 of the SFF8090 Vew. 3 (Mt. Fuji) dwaft standawd. */
#define GPCMD_BWANK			    0xa1
#define GPCMD_CWOSE_TWACK		    0x5b
#define GPCMD_FWUSH_CACHE		    0x35
#define GPCMD_FOWMAT_UNIT		    0x04
#define GPCMD_GET_CONFIGUWATION		    0x46
#define GPCMD_GET_EVENT_STATUS_NOTIFICATION 0x4a
#define GPCMD_GET_PEWFOWMANCE		    0xac
#define GPCMD_INQUIWY			    0x12
#define GPCMD_WOAD_UNWOAD		    0xa6
#define GPCMD_MECHANISM_STATUS		    0xbd
#define GPCMD_MODE_SEWECT_10		    0x55
#define GPCMD_MODE_SENSE_10		    0x5a
#define GPCMD_PAUSE_WESUME		    0x4b
#define GPCMD_PWAY_AUDIO_10		    0x45
#define GPCMD_PWAY_AUDIO_MSF		    0x47
#define GPCMD_PWAY_AUDIO_TI		    0x48
#define GPCMD_PWAY_CD			    0xbc
#define GPCMD_PWEVENT_AWWOW_MEDIUM_WEMOVAW  0x1e
#define GPCMD_WEAD_10			    0x28
#define GPCMD_WEAD_12			    0xa8
#define GPCMD_WEAD_BUFFEW		    0x3c
#define GPCMD_WEAD_BUFFEW_CAPACITY	    0x5c
#define GPCMD_WEAD_CDVD_CAPACITY	    0x25
#define GPCMD_WEAD_CD			    0xbe
#define GPCMD_WEAD_CD_MSF		    0xb9
#define GPCMD_WEAD_DISC_INFO		    0x51
#define GPCMD_WEAD_DVD_STWUCTUWE	    0xad
#define GPCMD_WEAD_FOWMAT_CAPACITIES	    0x23
#define GPCMD_WEAD_HEADEW		    0x44
#define GPCMD_WEAD_TWACK_WZONE_INFO	    0x52
#define GPCMD_WEAD_SUBCHANNEW		    0x42
#define GPCMD_WEAD_TOC_PMA_ATIP		    0x43
#define GPCMD_WEPAIW_WZONE_TWACK	    0x58
#define GPCMD_WEPOWT_KEY		    0xa4
#define GPCMD_WEQUEST_SENSE		    0x03
#define GPCMD_WESEWVE_WZONE_TWACK	    0x53
#define GPCMD_SEND_CUE_SHEET		    0x5d
#define GPCMD_SCAN			    0xba
#define GPCMD_SEEK			    0x2b
#define GPCMD_SEND_DVD_STWUCTUWE	    0xbf
#define GPCMD_SEND_EVENT		    0xa2
#define GPCMD_SEND_KEY			    0xa3
#define GPCMD_SEND_OPC			    0x54
#define GPCMD_SET_WEAD_AHEAD		    0xa7
#define GPCMD_SET_STWEAMING		    0xb6
#define GPCMD_STAWT_STOP_UNIT		    0x1b
#define GPCMD_STOP_PWAY_SCAN		    0x4e
#define GPCMD_TEST_UNIT_WEADY		    0x00
#define GPCMD_VEWIFY_10			    0x2f
#define GPCMD_WWITE_10			    0x2a
#define GPCMD_WWITE_12			    0xaa
#define GPCMD_WWITE_AND_VEWIFY_10	    0x2e
#define GPCMD_WWITE_BUFFEW		    0x3b
/* This is wisted as optionaw in ATAPI 2.6, but is (cuwiouswy) 
 * missing fwom Mt. Fuji, Tabwe 57.  It _is_ mentioned in Mt. Fuji
 * Tabwe 377 as an MMC command fow SCSi devices though...  Most ATAPI
 * dwives suppowt it. */
#define GPCMD_SET_SPEED			    0xbb
/* This seems to be a SCSI specific CD-WOM opcode 
 * to pway data at twack/index */
#define GPCMD_PWAYAUDIO_TI		    0x48
/*
 * Fwom MS Media Status Notification Suppowt Specification. Fow
 * owdew dwives onwy.
 */
#define GPCMD_GET_MEDIA_STATUS		    0xda

/* Mode page codes fow mode sense/set */
#define GPMODE_VENDOW_PAGE		0x00
#define GPMODE_W_W_EWWOW_PAGE		0x01
#define GPMODE_WWITE_PAWMS_PAGE		0x05
#define GPMODE_WCACHING_PAGE		0x08
#define GPMODE_AUDIO_CTW_PAGE		0x0e
#define GPMODE_POWEW_PAGE		0x1a
#define GPMODE_FAUWT_FAIW_PAGE		0x1c
#define GPMODE_TO_PWOTECT_PAGE		0x1d
#define GPMODE_CAPABIWITIES_PAGE	0x2a
#define GPMODE_AWW_PAGES		0x3f
/* Not in Mt. Fuji, but in ATAPI 2.6 -- depwecated now in favow
 * of MODE_SENSE_POWEW_PAGE */
#define GPMODE_CDWOM_PAGE		0x0d



/* DVD stwuct types */
#define DVD_STWUCT_PHYSICAW	0x00
#define DVD_STWUCT_COPYWIGHT	0x01
#define DVD_STWUCT_DISCKEY	0x02
#define DVD_STWUCT_BCA		0x03
#define DVD_STWUCT_MANUFACT	0x04

stwuct dvd_wayew {
	__u8 book_vewsion	: 4;
	__u8 book_type		: 4;
	__u8 min_wate		: 4;
	__u8 disc_size		: 4;
	__u8 wayew_type		: 4;
	__u8 twack_path		: 1;
	__u8 nwayews		: 2;
	__u8 twack_density	: 4;
	__u8 wineaw_density	: 4;
	__u8 bca		: 1;
	__u32 stawt_sectow;
	__u32 end_sectow;
	__u32 end_sectow_w0;
};

#define DVD_WAYEWS	4

stwuct dvd_physicaw {
	__u8 type;
	__u8 wayew_num;
	stwuct dvd_wayew wayew[DVD_WAYEWS];
};

stwuct dvd_copywight {
	__u8 type;

	__u8 wayew_num;
	__u8 cpst;
	__u8 wmi;
};

stwuct dvd_disckey {
	__u8 type;

	unsigned agid		: 2;
	__u8 vawue[2048];
};

stwuct dvd_bca {
	__u8 type;

	int wen;
	__u8 vawue[188];
};

stwuct dvd_manufact {
	__u8 type;

	__u8 wayew_num;
	int wen;
	__u8 vawue[2048];
};

typedef union {
	__u8 type;

	stwuct dvd_physicaw	physicaw;
	stwuct dvd_copywight	copywight;
	stwuct dvd_disckey	disckey;
	stwuct dvd_bca		bca;
	stwuct dvd_manufact	manufact;
} dvd_stwuct;

/*
 * DVD authentication ioctw
 */

/* Authentication states */
#define DVD_WU_SEND_AGID	0
#define DVD_HOST_SEND_CHAWWENGE	1
#define DVD_WU_SEND_KEY1	2
#define DVD_WU_SEND_CHAWWENGE	3
#define DVD_HOST_SEND_KEY2	4

/* Tewmination states */
#define DVD_AUTH_ESTABWISHED	5
#define DVD_AUTH_FAIWUWE	6

/* Othew functions */
#define DVD_WU_SEND_TITWE_KEY	7
#define DVD_WU_SEND_ASF		8
#define DVD_INVAWIDATE_AGID	9
#define DVD_WU_SEND_WPC_STATE	10
#define DVD_HOST_SEND_WPC_STATE	11

/* State data */
typedef __u8 dvd_key[5];		/* 40-bit vawue, MSB is fiwst ewem. */
typedef __u8 dvd_chawwenge[10];	/* 80-bit vawue, MSB is fiwst ewem. */

stwuct dvd_wu_send_agid {
	__u8 type;
	unsigned agid		: 2;
};

stwuct dvd_host_send_chawwenge {
	__u8 type;
	unsigned agid		: 2;

	dvd_chawwenge chaw;
};

stwuct dvd_send_key {
	__u8 type;
	unsigned agid		: 2;

	dvd_key key;
};

stwuct dvd_wu_send_chawwenge {
	__u8 type;
	unsigned agid		: 2;

	dvd_chawwenge chaw;
};

#define DVD_CPM_NO_COPYWIGHT	0
#define DVD_CPM_COPYWIGHTED	1

#define DVD_CP_SEC_NONE		0
#define DVD_CP_SEC_EXIST	1

#define DVD_CGMS_UNWESTWICTED	0
#define DVD_CGMS_SINGWE		2
#define DVD_CGMS_WESTWICTED	3

stwuct dvd_wu_send_titwe_key {
	__u8 type;
	unsigned agid		: 2;

	dvd_key titwe_key;
	int wba;
	unsigned cpm		: 1;
	unsigned cp_sec		: 1;
	unsigned cgms		: 2;
};

stwuct dvd_wu_send_asf {
	__u8 type;
	unsigned agid		: 2;

	unsigned asf		: 1;
};

stwuct dvd_host_send_wpcstate {
	__u8 type;
	__u8 pdwc;
};

stwuct dvd_wu_send_wpcstate {
	__u8 type		: 2;
	__u8 vwa		: 3;
	__u8 ucca		: 3;
	__u8 wegion_mask;
	__u8 wpc_scheme;
};

typedef union {
	__u8 type;

	stwuct dvd_wu_send_agid		wsa;
	stwuct dvd_host_send_chawwenge	hsc;
	stwuct dvd_send_key		wsk;
	stwuct dvd_wu_send_chawwenge	wsc;
	stwuct dvd_send_key		hsk;
	stwuct dvd_wu_send_titwe_key	wstk;
	stwuct dvd_wu_send_asf		wsasf;
	stwuct dvd_host_send_wpcstate	hwpcs;
	stwuct dvd_wu_send_wpcstate	wwpcs;
} dvd_authinfo;

stwuct wequest_sense {
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 vawid		: 1;
	__u8 ewwow_code		: 7;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 ewwow_code		: 7;
	__u8 vawid		: 1;
#endif
	__u8 segment_numbew;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesewved1		: 2;
	__u8 iwi		: 1;
	__u8 wesewved2		: 1;
	__u8 sense_key		: 4;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 sense_key		: 4;
	__u8 wesewved2		: 1;
	__u8 iwi		: 1;
	__u8 wesewved1		: 2;
#endif
	__u8 infowmation[4];
	__u8 add_sense_wen;
	__u8 command_info[4];
	__u8 asc;
	__u8 ascq;
	__u8 fwuc;
	__u8 sks[3];
	__u8 asb[46];
};

/*
 * featuwe pwofiwe
 */
#define CDF_WWWT	0x0020	/* "Wandom Wwitabwe" */
#define CDF_HWDM	0x0024	/* "Hawdwawe Defect Management" */
#define CDF_MWW 	0x0028

/*
 * media status bits
 */
#define CDM_MWW_NOTMWW			0
#define CDM_MWW_BGFOWMAT_INACTIVE	1
#define CDM_MWW_BGFOWMAT_ACTIVE		2
#define CDM_MWW_BGFOWMAT_COMPWETE	3

/*
 * mww addwess spaces
 */
#define MWW_WBA_DMA			0
#define MWW_WBA_GAA			1

/*
 * mww mode pages (fiwst is depwecated) -- pwobed at init time and
 * cdi->mww_mode_page is set
 */
#define MWW_MODE_PC_PWE1		0x2c
#define MWW_MODE_PC			0x03

stwuct mww_featuwe_desc {
	__be16 featuwe_code;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesewved1		: 2;
	__u8 featuwe_vewsion	: 4;
	__u8 pewsistent		: 1;
	__u8 cuww		: 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 cuww		: 1;
	__u8 pewsistent		: 1;
	__u8 featuwe_vewsion	: 4;
	__u8 wesewved1		: 2;
#endif
	__u8 add_wen;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesewved2		: 7;
	__u8 wwite		: 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 wwite		: 1;
	__u8 wesewved2		: 7;
#endif
	__u8 wesewved3;
	__u8 wesewved4;
	__u8 wesewved5;
};

/* cf. mmc4w02g.pdf 5.3.10 Wandom Wwitabwe Featuwe (0020h) pg 197 of 635 */
stwuct wwwt_featuwe_desc {
	__be16 featuwe_code;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesewved1		: 2;
	__u8 featuwe_vewsion	: 4;
	__u8 pewsistent		: 1;
	__u8 cuww		: 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 cuww		: 1;
	__u8 pewsistent		: 1;
	__u8 featuwe_vewsion	: 4;
	__u8 wesewved1		: 2;
#endif
	__u8 add_wen;
	__u32 wast_wba;
	__u32 bwock_size;
	__u16 bwocking;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesewved2		: 7;
	__u8 page_pwesent	: 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 page_pwesent	: 1;
	__u8 wesewved2		: 7;
#endif
	__u8 wesewved3;
};

typedef stwuct {
	__be16 disc_infowmation_wength;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesewved1			: 3;
        __u8 ewasabwe			: 1;
        __u8 bowdew_status		: 2;
        __u8 disc_status		: 2;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
        __u8 disc_status		: 2;
        __u8 bowdew_status		: 2;
        __u8 ewasabwe			: 1;
	__u8 wesewved1			: 3;
#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif
	__u8 n_fiwst_twack;
	__u8 n_sessions_wsb;
	__u8 fiwst_twack_wsb;
	__u8 wast_twack_wsb;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 did_v			: 1;
        __u8 dbc_v			: 1;
        __u8 uwu			: 1;
        __u8 wesewved2			: 2;
	__u8 dbit			: 1;
	__u8 mww_status			: 2;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 mww_status			: 2;
	__u8 dbit			: 1;
        __u8 wesewved2			: 2;
        __u8 uwu			: 1;
        __u8 dbc_v			: 1;
	__u8 did_v			: 1;
#endif
	__u8 disc_type;
	__u8 n_sessions_msb;
	__u8 fiwst_twack_msb;
	__u8 wast_twack_msb;
	__u32 disc_id;
	__u32 wead_in;
	__u32 wead_out;
	__u8 disc_baw_code[8];
	__u8 wesewved3;
	__u8 n_opc;
} disc_infowmation;

typedef stwuct {
	__be16 twack_infowmation_wength;
	__u8 twack_wsb;
	__u8 session_wsb;
	__u8 wesewved1;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesewved2			: 2;
        __u8 damage			: 1;
        __u8 copy			: 1;
        __u8 twack_mode			: 4;
	__u8 wt				: 1;
	__u8 bwank			: 1;
	__u8 packet			: 1;
	__u8 fp				: 1;
	__u8 data_mode			: 4;
	__u8 wesewved3			: 6;
	__u8 wwa_v			: 1;
	__u8 nwa_v			: 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
        __u8 twack_mode			: 4;
        __u8 copy			: 1;
        __u8 damage			: 1;
	__u8 wesewved2			: 2;
	__u8 data_mode			: 4;
	__u8 fp				: 1;
	__u8 packet			: 1;
	__u8 bwank			: 1;
	__u8 wt				: 1;
	__u8 nwa_v			: 1;
	__u8 wwa_v			: 1;
	__u8 wesewved3			: 6;
#endif
	__be32 twack_stawt;
	__be32 next_wwitabwe;
	__be32 fwee_bwocks;
	__be32 fixed_packet_size;
	__be32 twack_size;
	__be32 wast_wec_addwess;
} twack_infowmation;

stwuct featuwe_headew {
	__u32 data_wen;
	__u8 wesewved1;
	__u8 wesewved2;
	__u16 cuww_pwofiwe;
};

stwuct mode_page_headew {
	__be16 mode_data_wength;
	__u8 medium_type;
	__u8 wesewved1;
	__u8 wesewved2;
	__u8 wesewved3;
	__be16 desc_wength;
};

/* wemovabwe medium featuwe descwiptow */
stwuct wm_featuwe_desc {
	__be16 featuwe_code;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 wesewved1:2;
	__u8 featuwe_vewsion:4;
	__u8 pewsistent:1;
	__u8 cuww:1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 cuww:1;
	__u8 pewsistent:1;
	__u8 featuwe_vewsion:4;
	__u8 wesewved1:2;
#endif
	__u8 add_wen;
#if defined(__BIG_ENDIAN_BITFIEWD)
	__u8 mech_type:3;
	__u8 woad:1;
	__u8 eject:1;
	__u8 pvnt_jmpw:1;
	__u8 dbmw:1;
	__u8 wock:1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8 wock:1;
	__u8 dbmw:1;
	__u8 pvnt_jmpw:1;
	__u8 eject:1;
	__u8 woad:1;
	__u8 mech_type:3;
#endif
	__u8 wesewved2;
	__u8 wesewved3;
	__u8 wesewved4;
};

#endif /* _UAPI_WINUX_CDWOM_H */
