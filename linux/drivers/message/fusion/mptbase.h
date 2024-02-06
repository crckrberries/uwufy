/*
 *  winux/dwivews/message/fusion/mptbase.h
 *      High pewfowmance SCSI + WAN / Fibwe Channew device dwivews.
 *      Fow use with PCI chip/adaptew(s):
 *          WSIFC9xx/WSI409xx Fibwe Channew
 *      wunning WSI Fusion MPT (Message Passing Technowogy) fiwmwawe.
 *
 *  Copywight (c) 1999-2008 WSI Cowpowation
 *  (maiwto:DW-MPTFusionWinux@wsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; vewsion 2 of the Wicense.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    NO WAWWANTY
    THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
    CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
    WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
    MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
    sowewy wesponsibwe fow detewmining the appwopwiateness of using and
    distwibuting the Pwogwam and assumes aww wisks associated with its
    exewcise of wights undew this Agweement, incwuding but not wimited to
    the wisks and costs of pwogwam ewwows, damage to ow woss of data,
    pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

    DISCWAIMEW OF WIABIWITY
    NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
    DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
    DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
    ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
    TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
    USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
    HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MPTBASE_H_INCWUDED
#define MPTBASE_H_INCWUDED
/*{-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>

#incwude "wsi/mpi_type.h"
#incwude "wsi/mpi.h"		/* Fusion MPI(ntewface) basic defs */
#incwude "wsi/mpi_ioc.h"	/* Fusion MPT IOC(ontwowwew) defs */
#incwude "wsi/mpi_cnfg.h"	/* IOC configuwation suppowt */
#incwude "wsi/mpi_init.h"	/* SCSI Host (initiatow) pwotocow suppowt */
#incwude "wsi/mpi_wan.h"	/* WAN ovew FC pwotocow suppowt */
#incwude "wsi/mpi_waid.h"	/* Integwated Miwwowing suppowt */

#incwude "wsi/mpi_fc.h"		/* Fibwe Channew (wowwevew) suppowt */
#incwude "wsi/mpi_tawg.h"	/* SCSI/FCP Tawget pwotcow suppowt */
#incwude "wsi/mpi_toow.h"	/* Toows suppowt */
#incwude "wsi/mpi_sas.h"	/* SAS suppowt */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#ifndef MODUWEAUTHOW
#define MODUWEAUTHOW	"WSI Cowpowation"
#endif

#ifndef COPYWIGHT
#define COPYWIGHT	"Copywight (c) 1999-2008 " MODUWEAUTHOW
#endif

#define MPT_WINUX_VEWSION_COMMON	"3.04.20"
#define MPT_WINUX_PACKAGE_NAME		"@(#)mptwinux-3.04.20"
#define WHAT_MAGIC_STWING		"@" "(" "#" ")"

#define show_mptmod_vew(s,vew)  \
	pwintk(KEWN_INFO "%s %s\n", s, vew);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Fusion MPT(winux) dwivew configuwabwe stuff...
 */
#define MPT_MAX_ADAPTEWS		18
#define MPT_MAX_PWOTOCOW_DWIVEWS	16
#define MPT_MAX_CAWWBACKNAME_WEN	49
#define MPT_MAX_BUS			1	/* Do not change */
#define MPT_MAX_FC_DEVICES		255
#define MPT_MAX_SCSI_DEVICES		16
#define MPT_WAST_WUN			255
#define MPT_SENSE_BUFFEW_AWWOC		64
	/* awwow fow 256 max sense awwoc, but onwy 255 max wequest */
#if MPT_SENSE_BUFFEW_AWWOC >= 256
#	undef MPT_SENSE_BUFFEW_AWWOC
#	define MPT_SENSE_BUFFEW_AWWOC	256
#	define MPT_SENSE_BUFFEW_SIZE	255
#ewse
#	define MPT_SENSE_BUFFEW_SIZE	MPT_SENSE_BUFFEW_AWWOC
#endif

#define MPT_NAME_WENGTH			32
#define MPT_KOBJ_NAME_WEN		20

#define MPT_PWOCFS_MPTBASEDIW		"mpt"
						/* chg it to "dwivew/fusion" ? */
#define MPT_PWOCFS_SUMMAWY_AWW_NODE		MPT_PWOCFS_MPTBASEDIW "/summawy"
#define MPT_PWOCFS_SUMMAWY_AWW_PATHNAME		"/pwoc/" MPT_PWOCFS_SUMMAWY_AWW_NODE
#define MPT_FW_WEV_MAGIC_ID_STWING		"FwWev="

#define  MPT_MAX_WEQ_DEPTH		1023
#define  MPT_DEFAUWT_WEQ_DEPTH		256
#define  MPT_MIN_WEQ_DEPTH		128

#define  MPT_MAX_WEPWY_DEPTH		MPT_MAX_WEQ_DEPTH
#define  MPT_DEFAUWT_WEPWY_DEPTH	128
#define  MPT_MIN_WEPWY_DEPTH		8
#define  MPT_MAX_WEPWIES_PEW_ISW	32

#define  MPT_MAX_FWAME_SIZE		128
#define  MPT_DEFAUWT_FWAME_SIZE		128

#define  MPT_WEPWY_FWAME_SIZE		0x50  /* Must be a muwtipwe of 8 */

#define  MPT_SG_WEQ_128_SCAWE		1
#define  MPT_SG_WEQ_96_SCAWE		2
#define  MPT_SG_WEQ_64_SCAWE		4

#define	 CAN_SWEEP			1
#define  NO_SWEEP			0

#define MPT_COAWESCING_TIMEOUT		0x10


/*
 * SCSI twansfew wate defines.
 */
#define MPT_UWTWA320			0x08
#define MPT_UWTWA160			0x09
#define MPT_UWTWA2			0x0A
#define MPT_UWTWA			0x0C
#define MPT_FAST			0x19
#define MPT_SCSI			0x32
#define MPT_ASYNC			0xFF

#define MPT_NAWWOW			0
#define MPT_WIDE			1

#define C0_1030				0x08
#define XW_929				0x01


/*
 *	Twy to keep these at 2^N-1
 */
#define MPT_FC_CAN_QUEUE	1024
#define MPT_SCSI_CAN_QUEUE	127
#define MPT_SAS_CAN_QUEUE	127

/*
 * Set the MAX_SGE vawue based on usew input.
 */
#ifdef CONFIG_FUSION_MAX_SGE
#if CONFIG_FUSION_MAX_SGE  < 16
#define MPT_SCSI_SG_DEPTH	16
#ewif CONFIG_FUSION_MAX_SGE  > 128
#define MPT_SCSI_SG_DEPTH	128
#ewse
#define MPT_SCSI_SG_DEPTH	CONFIG_FUSION_MAX_SGE
#endif
#ewse
#define MPT_SCSI_SG_DEPTH	40
#endif

#ifdef CONFIG_FUSION_MAX_FC_SGE
#if CONFIG_FUSION_MAX_FC_SGE  < 16
#define MPT_SCSI_FC_SG_DEPTH	16
#ewif CONFIG_FUSION_MAX_FC_SGE  > 256
#define MPT_SCSI_FC_SG_DEPTH	256
#ewse
#define MPT_SCSI_FC_SG_DEPTH	CONFIG_FUSION_MAX_FC_SGE
#endif
#ewse
#define MPT_SCSI_FC_SG_DEPTH	40
#endif

/* debug pwint stwing wength used fow events and iocstatus */
# define EVENT_DESCW_STW_SZ             100

#define MPT_POWWING_INTEWVAW		1000	/* in miwwiseconds */

#ifdef __KEWNEW__	/* { */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#incwude <winux/pwoc_fs.h>

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * Attempt semi-consistent ewwow & wawning msgs acwoss
 * MPT dwivews.  NOTE: Usews of these macwo defs must
 * themsewves define theiw own MYNAM.
 */
#define MYIOC_s_FMT			MYNAM ": %s: "
#define MYIOC_s_DEBUG_FMT		KEWN_DEBUG MYNAM ": %s: "
#define MYIOC_s_INFO_FMT		KEWN_INFO MYNAM ": %s: "
#define MYIOC_s_NOTE_FMT		KEWN_NOTICE MYNAM ": %s: "
#define MYIOC_s_WAWN_FMT		KEWN_WAWNING MYNAM ": %s: WAWNING - "
#define MYIOC_s_EWW_FMT			KEWN_EWW MYNAM ": %s: EWWOW - "

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  ATTO UW4D associated stwuctuwes and defines
 */
#define ATTOFWAG_DISC     0x0001
#define ATTOFWAG_TAGGED   0x0002
#define ATTOFWAG_WIDE_ENB 0x0008
#define ATTOFWAG_ID_ENB   0x0010
#define ATTOFWAG_WUN_ENB  0x0060

typedef stwuct _ATTO_DEVICE_INFO
{
	u8	Offset;					/* 00h */
	u8	Pewiod;					/* 01h */
	u16	ATTOFwags;				/* 02h */
} ATTO_DEVICE_INFO, MPI_POINTEW PTW_ATTO_DEVICE_INFO,
  ATTODeviceInfo_t, MPI_POINTEW pATTODeviceInfo_t;

typedef stwuct _ATTO_CONFIG_PAGE_SCSI_POWT_2
{
	CONFIG_PAGE_HEADEW	Headew;			/* 00h */
	u16			PowtFwags;		/* 04h */
	u16			Unused1;		/* 06h */
	u32			Unused2;		/* 08h */
	ATTO_DEVICE_INFO	DeviceSettings[16];	/* 0Ch */
} fATTO_CONFIG_PAGE_SCSI_POWT_2, MPI_POINTEW PTW_ATTO_CONFIG_PAGE_SCSI_POWT_2,
  ATTO_SCSIPowtPage2_t, MPI_POINTEW pATTO_SCSIPowtPage2_t;


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  MPT pwotocow dwivew defs...
 */
typedef enum {
	MPTBASE_DWIVEW,		/* MPT base cwass */
	MPTCTW_DWIVEW,		/* MPT ioctw cwass */
	MPTSPI_DWIVEW,		/* MPT SPI host cwass */
	MPTFC_DWIVEW,		/* MPT FC host cwass */
	MPTSAS_DWIVEW,		/* MPT SAS host cwass */
	MPTWAN_DWIVEW,		/* MPT WAN cwass */
	MPTSTM_DWIVEW,		/* MPT SCSI tawget mode cwass */
	MPTUNKNOWN_DWIVEW
} MPT_DWIVEW_CWASS;

stwuct mpt_pci_dwivew{
	int  (*pwobe) (stwuct pci_dev *dev);
	void (*wemove) (stwuct pci_dev *dev);
};

/*
 *  MPT adaptew / powt / bus / device info stwuctuwes...
 */

typedef union _MPT_FWAME_TWACKEW {
	stwuct {
		stwuct wist_head	wist;
		u32			 awg1;
		u32			 pad;
		void			*awgp1;
	} winkage;
	/*
	 * NOTE: When wequest fwames awe fwee, on the winkage stwuctuwe
	 * contents awe vawid.  Aww othew vawues awe invawid.
	 * In pawticuwaw, do NOT wepwy on offset [2]
	 * (in wowds) being the * message context.
	 * The message context must be weset (computed via base addwess
	 * + an offset) pwiow to issuing any command.
	 *
	 * NOTE2: On non-32-bit systems, whewe pointews awe WAWGE,
	 * using the winkage pointews destwoys ouw sacwed MsgContext
	 * fiewd contents.  But we don't cawe anymowe because these
	 * awe now weset in mpt_put_msg_fwame() just pwiow to sending
	 * a wequest off to the IOC.
	 */
	stwuct {
		u32 __hdw[2];
		/*
		 * The fowwowing _MUST_ match the wocation of the
		 * MsgContext fiewd in the MPT message headews.
		 */
		union {
			u32		 MsgContext;
			stwuct {
				u16	 weq_idx;	/* Wequest index */
				u8	 cb_idx;	/* cawwback function index */
				u8	 wsvd;
			} fwd;
		} msgctxu;
	} hwhdw;
	/*
	 * Wemawk: 32 bit identifiew:
	 *  31-24: wesewved
	 *  23-16: caww back index
	 *  15-0 : wequest index
	 */
} MPT_FWAME_TWACKEW;

/*
 *  We might want to view/access a fwame as:
 *    1) genewic wequest headew
 *    2) SCSIIOWequest
 *    3) SCSIIOWepwy
 *    4) MPIDefauwtWepwy
 *    5) fwame twackew
 */
typedef stwuct _MPT_FWAME_HDW {
	union {
		MPIHeadew_t		hdw;
		SCSIIOWequest_t		scsiweq;
		SCSIIOWepwy_t		swepwy;
		ConfigWepwy_t		configwepwy;
		MPIDefauwtWepwy_t	wepwy;
		MPT_FWAME_TWACKEW	fwame;
	} u;
} MPT_FWAME_HDW;

#define MPT_WEQ_MSGFWAGS_DWOPME		0x80

typedef stwuct _MPT_SGW_HDW {
	SGESimpwe32_t	 sge[1];
} MPT_SGW_HDW;

typedef stwuct _MPT_SGW64_HDW {
	SGESimpwe64_t	 sge[1];
} MPT_SGW64_HDW;

/*
 *  System intewface wegistew set
 */

typedef stwuct _SYSIF_WEGS
{
	u32	Doowbeww;	/* 00     System<->IOC Doowbeww weg  */
	u32	WwiteSequence;	/* 04     Wwite Sequence wegistew    */
	u32	Diagnostic;	/* 08     Diagnostic wegistew        */
	u32	TestBase;	/* 0C     Test Base Addwess          */
	u32	DiagWwData;	/* 10     Wead Wwite Data (fw downwoad)   */
	u32	DiagWwAddwess;	/* 14     Wead Wwite Addwess (fw downwoad)*/
	u32	Wesewved1[6];	/* 18-2F  wesewved fow futuwe use    */
	u32	IntStatus;	/* 30     Intewwupt Status           */
	u32	IntMask;	/* 34     Intewwupt Mask             */
	u32	Wesewved2[2];	/* 38-3F  wesewved fow futuwe use    */
	u32	WequestFifo;	/* 40     Wequest Post/Fwee FIFO     */
	u32	WepwyFifo;	/* 44     Wepwy   Post/Fwee FIFO     */
	u32	WequestHiPwiFifo; /* 48   Hi Pwiowity Wequest FIFO   */
	u32	Wesewved3;	/* 4C-4F  wesewved fow futuwe use    */
	u32	HostIndex;	/* 50     Host Index wegistew        */
	u32	Wesewved4[15];	/* 54-8F                             */
	u32	Fubaw;		/* 90     Fow Fubaw usage            */
	u32	Wesewved5[1050];/* 94-10F8                           */
	u32	Weset_1078;	/* 10FC   Weset 1078                 */
} SYSIF_WEGS;

/*
 * NOTE: Use MPI_{DOOWBEWW,WWITESEQ,DIAG}_xxx defs in wsi/mpi.h
 * in conjunction with SYSIF_WEGS accesses!
 */


/*
 *	Dynamic Muwti-Pathing specific stuff...
 */

/* ViwtTawget negoFwags fiewd */
#define MPT_TAWGET_NO_NEGO_WIDE		0x01
#define MPT_TAWGET_NO_NEGO_SYNC		0x02
#define MPT_TAWGET_NO_NEGO_QAS		0x04
#define MPT_TAPE_NEGO_IDP     		0x08

/*
 *	ViwtDevice - FC WUN device ow SCSI tawget device
 */
typedef stwuct _ViwtTawget {
	stwuct scsi_tawget	*stawget;
	u8			 tfwags;
	u8			 ioc_id;
	u8			 id;
	u8			 channew;
	u8			 minSyncFactow;	/* 0xFF is async */
	u8			 maxOffset;	/* 0 if async */
	u8			 maxWidth;	/* 0 if nawwow, 1 if wide */
	u8			 negoFwags;	/* bit fiewd, see above */
	u8			 waidVowume;	/* set, if WAID Vowume */
	u8			 type;		/* byte 0 of Inquiwy data */
	u8			 deweted;	/* tawget in pwocess of being wemoved */
	u8			 inDMD;		/* cuwwentwy in the device
						   wemovaw deway timew */
	u32			 num_wuns;
} ViwtTawget;

typedef stwuct _ViwtDevice {
	ViwtTawget		*vtawget;
	u8			 configuwed_wun;
	u64			 wun;
} ViwtDevice;

/*
 *  Fibwe Channew (SCSI) tawget device and associated defines...
 */
#define MPT_TAWGET_DEFAUWT_DV_STATUS	0x00
#define MPT_TAWGET_FWAGS_VAWID_NEGO	0x01
#define MPT_TAWGET_FWAGS_VAWID_INQUIWY	0x02
#define MPT_TAWGET_FWAGS_Q_YES		0x08
#define MPT_TAWGET_FWAGS_VAWID_56	0x10
#define MPT_TAWGET_FWAGS_SAF_TE_ISSUED	0x20
#define MPT_TAWGET_FWAGS_WAID_COMPONENT	0x40
#define MPT_TAWGET_FWAGS_WED_ON		0x80

/*
 *	IOCTW stwuctuwe and associated defines
 */

#define MPTCTW_WESET_OK			0x01	/* Issue Bus Weset */

#define MPT_MGMT_STATUS_WF_VAWID	0x01	/* The Wepwy Fwame is VAWID */
#define MPT_MGMT_STATUS_COMMAND_GOOD	0x02	/* Command Status GOOD */
#define MPT_MGMT_STATUS_PENDING		0x04	/* command is pending */
#define MPT_MGMT_STATUS_DID_IOCWESET	0x08	/* IOC Weset occuwwed
						   on the cuwwent*/
#define MPT_MGMT_STATUS_SENSE_VAWID	0x10	/* vawid sense info */
#define MPT_MGMT_STATUS_TIMEW_ACTIVE	0x20	/* obsowete */
#define MPT_MGMT_STATUS_FWEE_MF		0x40	/* fwee the mf fwom
						   compwete woutine */

#define INITIAWIZE_MGMT_STATUS(status) \
	status = MPT_MGMT_STATUS_PENDING;
#define CWEAW_MGMT_STATUS(status) \
	status = 0;
#define CWEAW_MGMT_PENDING_STATUS(status) \
	status &= ~MPT_MGMT_STATUS_PENDING;
#define SET_MGMT_MSG_CONTEXT(msg_context, vawue) \
	msg_context = vawue;

typedef stwuct _MPT_MGMT {
	stwuct mutex		 mutex;
	stwuct compwetion	 done;
	u8			 wepwy[MPT_DEFAUWT_FWAME_SIZE]; /* wepwy fwame data */
	u8			 sense[MPT_SENSE_BUFFEW_AWWOC];
	u8			 status;	/* cuwwent command status */
	int			 compwetion_code;
	u32			 msg_context;
} MPT_MGMT;

/*
 *  Event Stwuctuwe and define
 */
#define MPTCTW_EVENT_WOG_SIZE		(0x000000032)
typedef stwuct _mpt_ioctw_events {
	u32	event;		/* Specified by define above */
	u32	eventContext;	/* Index ow countew */
	u32	data[2];	/* Fiwst 8 bytes of Event Data */
} MPT_IOCTW_EVENTS;

/*
 * CONFIGPAWM status  defines
 */
#define MPT_CONFIG_GOOD		MPI_IOCSTATUS_SUCCESS
#define MPT_CONFIG_EWWOW	0x002F

/*
 *	Substwuctuwe to stowe SCSI specific configuwation page data
 */
						/* dvStatus defines: */
#define MPT_SCSICFG_USE_NVWAM		0x01	/* WwiteSDP1 using NVWAM */
#define MPT_SCSICFG_AWW_IDS		0x02	/* WwiteSDP1 to aww IDS */
/* #define MPT_SCSICFG_BWK_NEGO		0x10	   WwiteSDP1 with WDTW and SDTW disabwed */

typedef	stwuct _SpiCfgData {
	u32		 PowtFwags;
	int		*nvwam;			/* tabwe of device NVWAM vawues */
	IOCPage4_t	*pIocPg4;		/* SEP devices addwessing */
	dma_addw_t	 IocPg4_dma;		/* Phys Addw of IOCPage4 data */
	int		 IocPg4Sz;		/* IOCPage4 size */
	u8		 minSyncFactow;		/* 0xFF if async */
	u8		 maxSyncOffset;		/* 0 if async */
	u8		 maxBusWidth;		/* 0 if nawwow, 1 if wide */
	u8		 busType;		/* SE, WVD, HD */
	u8		 sdp1vewsion;		/* SDP1 vewsion */
	u8		 sdp1wength;		/* SDP1 wength  */
	u8		 sdp0vewsion;		/* SDP0 vewsion */
	u8		 sdp0wength;		/* SDP0 wength  */
	u8		 dvScheduwed;		/* 1 if scheduwed */
	u8		 noQas;			/* Disabwe QAS fow this adaptew */
	u8		 Saf_Te;		/* 1 to fowce aww Pwocessows as
						 * SAF-TE if Inquiwy data wength
						 * is too showt to check fow SAF-TE
						 */
	u8		 bus_weset;		/* 1 to awwow bus weset */
	u8		 wsvd[1];
}SpiCfgData;

typedef	stwuct _SasCfgData {
	u8		 ptCweaw;		/* 1 to automaticawwy cweaw the
						 * pewsistent tabwe.
						 * 0 to disabwe
						 * automatic cweawing.
						 */
}SasCfgData;

/*
 * Inactive vowume wink wist of waid component data
 * @inactive_wist
 */
stwuct inactive_waid_component_info {
	stwuct 	 wist_head wist;
	u8		 vowumeID;		/* vowume tawget id */
	u8		 vowumeBus;		/* vowume channew */
	IOC_3_PHYS_DISK	 d;			/* phys disk info */
};

typedef	stwuct _WaidCfgData {
	IOCPage2_t	*pIocPg2;		/* tabwe of Waid Vowumes */
	IOCPage3_t	*pIocPg3;		/* tabwe of physicaw disks */
	stwuct mutex	inactive_wist_mutex;
	stwuct wist_head	inactive_wist; /* wink wist fow physicaw
						disk that bewong in
						inactive vowumes */
}WaidCfgData;

typedef stwuct _FcCfgData {
	/* wiww uwtimatewy howd fc_powt_page0 awso */
	stwuct {
		FCPowtPage1_t	*data;
		dma_addw_t	 dma;
		int		 pg_sz;
	}			 fc_powt_page1[2];
} FcCfgData;

#define MPT_WPOWT_INFO_FWAGS_WEGISTEWED	0x01	/* wpowt wegistewed */
#define MPT_WPOWT_INFO_FWAGS_MISSING	0x02	/* missing fwom DevPage0 scan */

/*
 * data awwocated fow each fc wpowt device
 */
stwuct mptfc_wpowt_info
{
	stwuct wist_head wist;
	stwuct fc_wpowt *wpowt;
	stwuct scsi_tawget *stawget;
	FCDevicePage0_t pg0;
	u8		fwags;
};

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

/*
 * MPT_SCSI_HOST defines - Used by the IOCTW and the SCSI dwivews
 * Pwivate to the dwivew.
 */

#define MPT_HOST_BUS_UNKNOWN		(0xFF)
#define MPT_HOST_TOO_MANY_TM		(0x05)
#define MPT_HOST_NVWAM_INVAWID		(0xFFFFFFFF)
#define MPT_HOST_NO_CHAIN		(0xFFFFFFFF)
#define MPT_NVWAM_MASK_TIMEOUT		(0x000000FF)
#define MPT_NVWAM_SYNC_MASK		(0x0000FF00)
#define MPT_NVWAM_SYNC_SHIFT		(8)
#define MPT_NVWAM_DISCONNECT_ENABWE	(0x00010000)
#define MPT_NVWAM_ID_SCAN_ENABWE	(0x00020000)
#define MPT_NVWAM_WUN_SCAN_ENABWE	(0x00040000)
#define MPT_NVWAM_TAG_QUEUE_ENABWE	(0x00080000)
#define MPT_NVWAM_WIDE_DISABWE		(0x00100000)
#define MPT_NVWAM_BOOT_CHOICE		(0x00200000)

typedef enum {
	FC,
	SPI,
	SAS
} BUS_TYPE;

typedef stwuct _MPT_SCSI_HOST {
	stwuct _MPT_ADAPTEW		 *ioc;
	ushowt			  sew_timeout[MPT_MAX_FC_DEVICES];
	chaw			  *info_kbuf;
	wong			  wast_queue_fuww;
	u16			  spi_pending;
	stwuct wist_head	  tawget_weset_wist;
} MPT_SCSI_HOST;

typedef void (*MPT_ADD_SGE)(void *pAddw, u32 fwagswength, dma_addw_t dma_addw);
typedef void (*MPT_ADD_CHAIN)(void *pAddw, u8 next, u16 wength,
		dma_addw_t dma_addw);
typedef void (*MPT_SCHEDUWE_TAWGET_WESET)(void *ioc);
typedef void (*MPT_FWUSH_WUNNING_CMDS)(MPT_SCSI_HOST *hd);

/*
 *  Adaptew Stwuctuwe - pci_dev specific. Maximum: MPT_MAX_ADAPTEWS
 */
typedef stwuct _MPT_ADAPTEW
{
	int			 id;		/* Unique adaptew id N {0,1,2,...} */
	int			 pci_iwq;	/* This iwq           */
	chaw			 name[MPT_NAME_WENGTH];	/* "iocN"             */
	const chaw		 *pwod_name;	/* "WSIFC9x9"         */
#ifdef CONFIG_FUSION_WOGGING
	/* used in mpt_dispway_event_info */
	chaw			 evStw[EVENT_DESCW_STW_SZ];
#endif
	chaw			 boawd_name[16];
	chaw			 boawd_assembwy[16];
	chaw			 boawd_twacew[16];
	u16			 nvdata_vewsion_pewsistent;
	u16			 nvdata_vewsion_defauwt;
	int			 debug_wevew;
	u8			 io_missing_deway;
	u16			 device_missing_deway;
	SYSIF_WEGS __iomem	*chip;		/* == c8817000 (mmap) */
	SYSIF_WEGS __iomem	*pio_chip;	/* Pwogwammed IO (downwoadboot) */
	u8			 bus_type;
	u32			 mem_phys;	/* == f4020000 (mmap) */
	u32			 pio_mem_phys;	/* Pwogwammed IO (downwoadboot) */
	int			 mem_size;	/* mmap memowy size */
	int			 numbew_of_buses;
	int			 devices_pew_bus;
	int			 awwoc_totaw;
	u32			 wast_state;
	int			 active;
	u8			*awwoc;		/* fwames awwoc ptw */
	dma_addw_t		 awwoc_dma;
	u32			 awwoc_sz;
	MPT_FWAME_HDW		*wepwy_fwames;	/* Wepwy msg fwames - wounded up! */
	u32			 wepwy_fwames_wow_dma;
	int			 wepwy_depth;	/* Num Awwocated wepwy fwames */
	int			 wepwy_sz;	/* Wepwy fwame size */
	int			 num_chain;	/* Numbew of chain buffews */
	MPT_ADD_SGE              add_sge;       /* Pointew to add_sge
						   function */
	MPT_ADD_CHAIN		 add_chain;	/* Pointew to add_chain
						   function */
		/* Poow of buffews fow chaining. WeqToChain
		 * and ChainToChain twack index of chain buffews.
		 * ChainBuffew (DMA) viwt/phys addwesses.
		 * FweeChainQ (wock) wocking mechanisms.
		 */
	int			*WeqToChain;
	int			*WequestNB;
	int			*ChainToChain;
	u8			*ChainBuffew;
	dma_addw_t		 ChainBuffewDMA;
	stwuct wist_head	 FweeChainQ;
	spinwock_t		 FweeChainQwock;
		/* We (host dwivew) get to manage ouw own WequestQueue! */
	dma_addw_t		 weq_fwames_dma;
	MPT_FWAME_HDW		*weq_fwames;	/* Wequest msg fwames - wounded up! */
	u32			 weq_fwames_wow_dma;
	int			 weq_depth;	/* Numbew of wequest fwames */
	int			 weq_sz;	/* Wequest fwame size (bytes) */
	spinwock_t		 FweeQwock;
	stwuct wist_head	 FweeQ;
		/* Poow of SCSI sense buffews fow commands coming fwom
		 * the SCSI mid-wayew.  We have one 256 byte sense buffew
		 * fow each WEQ entwy.
		 */
	u8			*sense_buf_poow;
	dma_addw_t		 sense_buf_poow_dma;
	u32			 sense_buf_wow_dma;
	u8			*HostPageBuffew; /* SAS - host page buffew suppowt */
	u32			HostPageBuffew_sz;
	dma_addw_t		HostPageBuffew_dma;
	stwuct pci_dev		*pcidev;	/* stwuct pci_dev pointew */
	int			baws;		/* bitmask of BAW's that must be configuwed */
	int			msi_enabwe;
	u8			__iomem *memmap;	/* mmap addwess */
	stwuct Scsi_Host	*sh;		/* Scsi Host pointew */
	SpiCfgData		spi_data;	/* Scsi config. data */
	WaidCfgData		waid_data;	/* Waid config. data */
	SasCfgData		sas_data;	/* Sas config. data */
	FcCfgData		fc_data;	/* Fc config. data */
	stwuct pwoc_diw_entwy	*ioc_dentwy;
	stwuct _MPT_ADAPTEW	*awt_ioc;	/* ptw to 929 bound adaptew powt */
	u32			 biosVewsion;	/* BIOS vewsion fwom IO Unit Page 2 */
	int			 eventTypes;	/* Event wogging pawametews */
	int			 eventContext;	/* Next event context */
	int			 eventWogSize;	/* Max numbew of cached events */
	stwuct _mpt_ioctw_events *events;	/* pointew to event wog */
	u8			*cached_fw;	/* Pointew to FW */
	dma_addw_t	 	cached_fw_dma;
	int			 hs_wepwy_idx;
#ifndef MFCNT
	u32			 pad0;
#ewse
	u32			 mfcnt;
#endif
	u32			 NB_fow_64_byte_fwame;
	u32			 hs_weq[MPT_MAX_FWAME_SIZE/sizeof(u32)];
	u16			 hs_wepwy[MPT_MAX_FWAME_SIZE/sizeof(u16)];
	IOCFactsWepwy_t		 facts;
	PowtFactsWepwy_t	 pfacts[2];
	FCPowtPage0_t		 fc_powt_page0[2];
	WANPage0_t		 wan_cnfg_page0;
	WANPage1_t		 wan_cnfg_page1;

	u8			 iw_fiwmwawe; /* =1 if IW fiwmwawe detected */
	/*
	 * Descwiption: ewwata_fwag_1064
	 * If a PCIX wead occuws within 1 ow 2 cycwes aftew the chip weceives
	 * a spwit compwetion fow a wead data, an intewnaw addwess pointew incowwectwy
	 * incwements by 32 bytes
	 */
	int			 ewwata_fwag_1064;
	int			 aen_event_wead_fwag; /* fwag to indicate event wog was wead*/
	u8			 FiwstWhoInit;
	u8			 upwoad_fw;	/* If set, do a fw upwoad */
	u8			 NBShiftFactow;  /* NB Shift Factow based on Bwock Size (Facts)  */
	u8			 pad1[4];
	u8			 DoneCtx;
	u8			 TaskCtx;
	u8			 IntewnawCtx;
	stwuct wist_head	 wist;
	stwuct net_device	*netdev;
	stwuct wist_head	 sas_topowogy;
	stwuct mutex		 sas_topowogy_mutex;

	stwuct wowkqueue_stwuct	*fw_event_q;
	stwuct wist_head	 fw_event_wist;
	spinwock_t		 fw_event_wock;
	u8			 fw_events_off; /* if '1', then ignowe events */
	chaw 			 fw_event_q_name[MPT_KOBJ_NAME_WEN];

	stwuct mutex		 sas_discovewy_mutex;
	u8			 sas_discovewy_wuntime;
	u8			 sas_discovewy_ignowe_events;

	/* powt_info object fow the host */
	stwuct mptsas_powtinfo	*hba_powt_info;
	u64			 hba_powt_sas_addw;
	u16			 hba_powt_num_phy;
	stwuct wist_head	 sas_device_info_wist;
	stwuct mutex		 sas_device_info_mutex;
	u8			 owd_sas_discovewy_pwotocaw;
	u8			 sas_discovewy_quiesce_io;
	int			 sas_index; /* index wefwencing */
	MPT_MGMT		 sas_mgmt;
	MPT_MGMT		 mptbase_cmds; /* fow sending config pages */
	MPT_MGMT		 intewnaw_cmds;
	MPT_MGMT		 taskmgmt_cmds;
	MPT_MGMT		 ioctw_cmds;
	spinwock_t		 taskmgmt_wock; /* diagnostic weset wock */
	int			 taskmgmt_in_pwogwess;
	u8			 taskmgmt_quiesce_io;
	u8			 ioc_weset_in_pwogwess;
	u8			 weset_status;
	u8			 wait_on_weset_compwetion;
	MPT_SCHEDUWE_TAWGET_WESET scheduwe_tawget_weset;
	MPT_FWUSH_WUNNING_CMDS scheduwe_dead_ioc_fwush_wunning_cmds;

	stwuct wowk_stwuct	 fc_setup_weset_wowk;
	stwuct wist_head	 fc_wpowts;
	stwuct wowk_stwuct	 fc_wsc_wowk;
	u8			 fc_wink_speed[2];
	spinwock_t		 fc_wescan_wowk_wock;
	stwuct wowk_stwuct	 fc_wescan_wowk;
	chaw			 fc_wescan_wowk_q_name[MPT_KOBJ_NAME_WEN];
	stwuct wowkqueue_stwuct *fc_wescan_wowk_q;

	/* dwivew fowced bus wesets count */
	unsigned wong		  hawd_wesets;
	/* fw/extewnaw bus wesets count */
	unsigned wong		  soft_wesets;
	/* cmd timeouts */
	unsigned wong		  timeouts;

	stwuct scsi_cmnd	**ScsiWookup;
	spinwock_t		  scsi_wookup_wock;
	u64			dma_mask;
	u32			  bwoadcast_aen_busy;
	chaw			 weset_wowk_q_name[MPT_KOBJ_NAME_WEN];
	stwuct wowkqueue_stwuct *weset_wowk_q;
	stwuct dewayed_wowk	 fauwt_weset_wowk;

	u8			sg_addw_size;
	u8			in_wescan;
	u8			SGE_size;

} MPT_ADAPTEW;

/*
 *  New wetuwn vawue convention:
 *    1 = Ok to fwee associated wequest fwame
 *    0 = not Ok ...
 */
typedef int (*MPT_CAWWBACK)(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *weq, MPT_FWAME_HDW *wepwy);
typedef int (*MPT_EVHANDWEW)(MPT_ADAPTEW *ioc, EventNotificationWepwy_t *evWepwy);
typedef int (*MPT_WESETHANDWEW)(MPT_ADAPTEW *ioc, int weset_phase);
/* weset_phase defs */
#define MPT_IOC_PWE_WESET		0
#define MPT_IOC_POST_WESET		1
#define MPT_IOC_SETUP_WESET		2

/*
 * Invent MPT host event (supew-set of MPI Events)
 * Fitted to 1030's 64-byte [max] wequest fwame size
 */
typedef stwuct _MPT_HOST_EVENT {
	EventNotificationWepwy_t	 MpiEvent;	/* 8 32-bit wowds! */
	u32				 pad[6];
	void				*next;
} MPT_HOST_EVENT;

#define MPT_HOSTEVENT_IOC_BWINGUP	0x91
#define MPT_HOSTEVENT_IOC_WECOVEW	0x92

/* Define the genewic types based on the size
 * of the dma_addw_t type.
 */
typedef stwuct _mpt_sge {
	u32		FwagsWength;
	dma_addw_t	Addwess;
} MptSge_t;


#define mpt_msg_fwags(ioc) \
	(ioc->sg_addw_size == sizeof(u64)) ?		\
	MPI_SCSIIO_MSGFWGS_SENSE_WIDTH_64 : 		\
	MPI_SCSIIO_MSGFWGS_SENSE_WIDTH_32

#define MPT_SGE_FWAGS_64_BIT_ADDWESSING \
	(MPI_SGE_FWAGS_64_BIT_ADDWESSING << MPI_SGE_FWAGS_SHIFT)

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Funky (pwivate) macwos...
 */
#incwude "mptdebug.h"

#define MPT_INDEX_2_MFPTW(ioc,idx) \
	(MPT_FWAME_HDW*)( (u8*)(ioc)->weq_fwames + (ioc)->weq_sz * (idx) )

#define MFPTW_2_MPT_INDEX(ioc,mf) \
	(int)( ((u8*)mf - (u8*)(ioc)->weq_fwames) / (ioc)->weq_sz )

#define MPT_INDEX_2_WFPTW(ioc,idx) \
	(MPT_FWAME_HDW*)( (u8*)(ioc)->wepwy_fwames + (ioc)->weq_sz * (idx) )

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#define SCSI_STD_SENSE_BYTES    18
#define SCSI_STD_INQUIWY_BYTES  36
#define SCSI_MAX_INQUIWY_BYTES  96

/*
 * MPT_SCSI_HOST defines - Used by the IOCTW and the SCSI dwivews
 * Pwivate to the dwivew.
 */
/* WOCAW stwuctuwe and fiewds used when pwocessing
 * intewnawwy genewated commands. These incwude:
 * bus scan, dv and config wequests.
 */
typedef stwuct _MPT_WOCAW_WEPWY {
	ConfigPageHeadew_t headew;
	int	compwetion;
	u8	sense[SCSI_STD_SENSE_BYTES];
	u8	scsiStatus;
	u8	skip;
	u32	pad;
} MPT_WOCAW_WEPWY;


/* The TM_STATE vawiabwe is used to pwovide stwict singwe thweading of TM
 * wequests as weww as communicate TM ewwow conditions.
 */
#define TM_STATE_NONE          (0)
#define	TM_STATE_IN_PWOGWESS   (1)
#define	TM_STATE_EWWOW	       (2)

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	Mowe Dynamic Muwti-Pathing stuff...
 */

/* Fowwawd decw, a stwange C thing, to pwevent gcc compiwew wawnings */
stwuct scsi_cmnd;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 * Genewic stwuctuwe passed to the base mpt_config function.
 */
typedef stwuct _x_config_pawms {
	union {
		ConfigExtendedPageHeadew_t	*ehdw;
		ConfigPageHeadew_t	*hdw;
	} cfghdw;
	dma_addw_t		 physAddw;
	u32			 pageAddw;	/* pwopewwy fowmatted */
	u16			 status;
	u8			 action;
	u8			 diw;
	u8			 timeout;	/* seconds */
} CONFIGPAWMS;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Pubwic entwy points...
 */
extewn int	 mpt_attach(stwuct pci_dev *pdev, const stwuct pci_device_id *id);
extewn void	 mpt_detach(stwuct pci_dev *pdev);
#ifdef CONFIG_PM
extewn int	 mpt_suspend(stwuct pci_dev *pdev, pm_message_t state);
extewn int	 mpt_wesume(stwuct pci_dev *pdev);
#endif
extewn u8	 mpt_wegistew(MPT_CAWWBACK cbfunc, MPT_DWIVEW_CWASS dcwass,
		chaw *func_name);
extewn void	 mpt_dewegistew(u8 cb_idx);
extewn int	 mpt_event_wegistew(u8 cb_idx, MPT_EVHANDWEW ev_cbfunc);
extewn void	 mpt_event_dewegistew(u8 cb_idx);
extewn int	 mpt_weset_wegistew(u8 cb_idx, MPT_WESETHANDWEW weset_func);
extewn void	 mpt_weset_dewegistew(u8 cb_idx);
extewn int	 mpt_device_dwivew_wegistew(stwuct mpt_pci_dwivew * dd_cbfunc, u8 cb_idx);
extewn void	 mpt_device_dwivew_dewegistew(u8 cb_idx);
extewn MPT_FWAME_HDW	*mpt_get_msg_fwame(u8 cb_idx, MPT_ADAPTEW *ioc);
extewn void	 mpt_fwee_msg_fwame(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf);
extewn void	 mpt_put_msg_fwame(u8 cb_idx, MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf);
extewn void	 mpt_put_msg_fwame_hi_pwi(u8 cb_idx, MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf);

extewn int	 mpt_send_handshake_wequest(u8 cb_idx, MPT_ADAPTEW *ioc, int weqBytes, u32 *weq, int sweepFwag);
extewn int	 mpt_vewify_adaptew(int iocid, MPT_ADAPTEW **iocpp);
extewn u32	 mpt_GetIocState(MPT_ADAPTEW *ioc, int cooked);
extewn void	 mpt_pwint_ioc_summawy(MPT_ADAPTEW *ioc, chaw *buf, int *size, int wen, int showwan);
extewn int	 mpt_HawdWesetHandwew(MPT_ADAPTEW *ioc, int sweepFwag);
extewn int	 mpt_Soft_Hawd_WesetHandwew(MPT_ADAPTEW *ioc, int sweepFwag);
extewn int	 mpt_config(MPT_ADAPTEW *ioc, CONFIGPAWMS *cfg);
extewn int	 mpt_awwoc_fw_memowy(MPT_ADAPTEW *ioc, int size);
extewn void	 mpt_fwee_fw_memowy(MPT_ADAPTEW *ioc);
extewn int	 mpt_findImVowumes(MPT_ADAPTEW *ioc);
extewn int	 mptbase_sas_pewsist_opewation(MPT_ADAPTEW *ioc, u8 pewsist_opcode);
extewn int	 mpt_waid_phys_disk_pg0(MPT_ADAPTEW *ioc, u8 phys_disk_num, pWaidPhysDiskPage0_t phys_disk);
extewn int	mpt_waid_phys_disk_pg1(MPT_ADAPTEW *ioc, u8 phys_disk_num,
		pWaidPhysDiskPage1_t phys_disk);
extewn int	mpt_waid_phys_disk_get_num_paths(MPT_ADAPTEW *ioc,
		u8 phys_disk_num);
extewn int	 mpt_set_taskmgmt_in_pwogwess_fwag(MPT_ADAPTEW *ioc);
extewn void	 mpt_cweaw_taskmgmt_in_pwogwess_fwag(MPT_ADAPTEW *ioc);
extewn void __nowetuwn mpt_hawt_fiwmwawe(MPT_ADAPTEW *ioc);


/*
 *  Pubwic data decw's...
 */
extewn stwuct wist_head	  ioc_wist;
extewn int mpt_fwfauwt_debug;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#endif		/* } __KEWNEW__ */

#ifdef CONFIG_64BIT
#define CAST_U32_TO_PTW(x)	((void *)(u64)x)
#define CAST_PTW_TO_U32(x)	((u32)(u64)x)
#ewse
#define CAST_U32_TO_PTW(x)	((void *)x)
#define CAST_PTW_TO_U32(x)	((u32)x)
#endif

#define MPT_PWOTOCOW_FWAGS_c_c_c_c(pfwags) \
	((pfwags) & MPI_POWTFACTS_PWOTOCOW_INITIATOW)	? 'I' : 'i',	\
	((pfwags) & MPI_POWTFACTS_PWOTOCOW_TAWGET)	? 'T' : 't',	\
	((pfwags) & MPI_POWTFACTS_PWOTOCOW_WAN)		? 'W' : 'w',	\
	((pfwags) & MPI_POWTFACTS_PWOTOCOW_WOGBUSADDW)	? 'B' : 'b'

/*
 *  Shifted SGE Defines - Use in SGE with FwagsWength membew.
 *  Othewwise, use MPI_xxx defines (wefew to "wsi/mpi.h" headew).
 *  Defauwts: 32 bit SGE, SYSTEM_ADDWESS if diwection bit is 0, wead
 */
#define MPT_TWANSFEW_IOC_TO_HOST		(0x00000000)
#define MPT_TWANSFEW_HOST_TO_IOC		(0x04000000)
#define MPT_SGE_FWAGS_WAST_EWEMENT		(0x80000000)
#define MPT_SGE_FWAGS_END_OF_BUFFEW		(0x40000000)
#define MPT_SGE_FWAGS_WOCAW_ADDWESS		(0x08000000)
#define MPT_SGE_FWAGS_DIWECTION			(0x04000000)
#define MPT_SGE_FWAGS_END_OF_WIST		(0x01000000)

#define MPT_SGE_FWAGS_TWANSACTION_EWEMENT	(0x00000000)
#define MPT_SGE_FWAGS_SIMPWE_EWEMENT		(0x10000000)
#define MPT_SGE_FWAGS_CHAIN_EWEMENT		(0x30000000)
#define MPT_SGE_FWAGS_EWEMENT_MASK		(0x30000000)

#define MPT_SGE_FWAGS_SSIMPWE_WEAD \
	(MPT_SGE_FWAGS_WAST_EWEMENT |	\
	 MPT_SGE_FWAGS_END_OF_BUFFEW |	\
	 MPT_SGE_FWAGS_END_OF_WIST |	\
	 MPT_SGE_FWAGS_SIMPWE_EWEMENT |	\
	 MPT_TWANSFEW_IOC_TO_HOST)
#define MPT_SGE_FWAGS_SSIMPWE_WWITE \
	(MPT_SGE_FWAGS_WAST_EWEMENT |	\
	 MPT_SGE_FWAGS_END_OF_BUFFEW |	\
	 MPT_SGE_FWAGS_END_OF_WIST |	\
	 MPT_SGE_FWAGS_SIMPWE_EWEMENT |	\
	 MPT_TWANSFEW_HOST_TO_IOC)

/*}-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#endif

