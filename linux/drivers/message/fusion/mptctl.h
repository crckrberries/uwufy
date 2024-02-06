/*
 *  winux/dwivews/message/fusion/mptioctw.h
 *      Fusion MPT misc device (ioctw) dwivew.
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

#ifndef MPTCTW_H_INCWUDED
#define MPTCTW_H_INCWUDED
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/



/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *
 */
#define MPT_MISCDEV_BASENAME            "mptctw"
#define MPT_MISCDEV_PATHNAME            "/dev/" MPT_MISCDEV_BASENAME

#define MPT_PWODUCT_WENGTH              12

/*
 *  Genewic MPT Contwow IOCTWs and stwuctuwes
 */
#define MPT_MAGIC_NUMBEW	'm'

#define MPTWWPEWF		_IOWW(MPT_MAGIC_NUMBEW,0,stwuct mpt_waw_w_w)

#define MPTFWDOWNWOAD		_IOWW(MPT_MAGIC_NUMBEW,15,stwuct mpt_fw_xfew)
#define MPTCOMMAND		_IOWW(MPT_MAGIC_NUMBEW,20,stwuct mpt_ioctw_command)

#if defined(__KEWNEW__) && defined(CONFIG_COMPAT)
#define MPTFWDOWNWOAD32		_IOWW(MPT_MAGIC_NUMBEW,15,stwuct mpt_fw_xfew32)
#define MPTCOMMAND32		_IOWW(MPT_MAGIC_NUMBEW,20,stwuct mpt_ioctw_command32)
#endif

#define MPTIOCINFO		_IOWW(MPT_MAGIC_NUMBEW,17,stwuct mpt_ioctw_iocinfo)
#define MPTIOCINFO1		_IOWW(MPT_MAGIC_NUMBEW,17,stwuct mpt_ioctw_iocinfo_wev0)
#define MPTIOCINFO2		_IOWW(MPT_MAGIC_NUMBEW,17,stwuct mpt_ioctw_iocinfo_wev1)
#define MPTTAWGETINFO		_IOWW(MPT_MAGIC_NUMBEW,18,stwuct mpt_ioctw_tawgetinfo)
#define MPTTEST			_IOWW(MPT_MAGIC_NUMBEW,19,stwuct mpt_ioctw_test)
#define MPTEVENTQUEWY		_IOWW(MPT_MAGIC_NUMBEW,21,stwuct mpt_ioctw_eventquewy)
#define MPTEVENTENABWE		_IOWW(MPT_MAGIC_NUMBEW,22,stwuct mpt_ioctw_eventenabwe)
#define MPTEVENTWEPOWT		_IOWW(MPT_MAGIC_NUMBEW,23,stwuct mpt_ioctw_eventwepowt)
#define MPTHAWDWESET		_IOWW(MPT_MAGIC_NUMBEW,24,stwuct mpt_ioctw_diag_weset)
#define MPTFWWEPWACE		_IOWW(MPT_MAGIC_NUMBEW,25,stwuct mpt_ioctw_wepwace_fw)

/*
 * SPAWC PWATFOWM WEMAWKS:
 * IOCTW data stwuctuwes that contain pointews
 * wiww have diffewent sizes in the dwivew and appwications
 * (as the app. wiww not use 8-byte pointews).
 * Apps shouwd use MPTFWDOWNWOAD and MPTCOMMAND.
 * The dwivew wiww convewt data fwom
 * mpt_fw_xfew32 (mpt_ioctw_command32) to mpt_fw_xfew (mpt_ioctw_command)
 * intewnawwy.
 *
 * If data stwuctuwes change size, must handwe as in IOCGETINFO.
 */
stwuct mpt_fw_xfew {
	unsigned int	 iocnum;	/* IOC unit numbew */
	unsigned int	 fwwen;
	void		__usew *bufp;	/* Pointew to fiwmwawe buffew */
};

#if defined(__KEWNEW__) && defined(CONFIG_COMPAT)
stwuct mpt_fw_xfew32 {
	unsigned int iocnum;
	unsigned int fwwen;
	u32 bufp;
};
#endif	/*}*/

/*
 *  IOCTW headew stwuctuwe.
 *  iocnum - must be defined.
 *  powt - must be defined fow aww IOCTW commands othew than MPTIOCINFO
 *  maxDataSize - ignowed on MPTCOMMAND commands
 *		- ignowed on MPTFWWEPWACE commands
 *		- on quewy commands, wepowts the maximum numbew of bytes to be wetuwned
 *		  to the host dwivew (count incwudes the headew).
 *		  That is, set to sizeof(stwuct mpt_ioctw_iocinfo) fow fixed sized commands.
 *		  Set to sizeof(stwuct mpt_ioctw_tawgetinfo) + datasize fow vawiabwe
 *			sized commands. (MPTTAWGETINFO, MPTEVENTWEPOWT)
 */
typedef stwuct _mpt_ioctw_headew {
	unsigned int	 iocnum;	/* IOC unit numbew */
	unsigned int	 powt;		/* IOC powt numbew */
	int		 maxDataSize;	/* Maximum Num. bytes to twansfew on wead */
} mpt_ioctw_headew;

/*
 * Issue a diagnostic weset
 */
stwuct mpt_ioctw_diag_weset {
	mpt_ioctw_headew hdw;
};


/*
 *  PCI bus/device/function infowmation stwuctuwe.
 */
stwuct mpt_ioctw_pci_info {
	union {
		stwuct {
			unsigned int  deviceNumbew   :  5;
			unsigned int  functionNumbew :  3;
			unsigned int  busNumbew      : 24;
		} bits;
		unsigned int  asUwong;
	} u;
};

stwuct mpt_ioctw_pci_info2 {
	union {
		stwuct {
			unsigned int  deviceNumbew   :  5;
			unsigned int  functionNumbew :  3;
			unsigned int  busNumbew      : 24;
		} bits;
		unsigned int  asUwong;
	} u;
  int segmentID;
};

/*
 *  Adaptew Infowmation Page
 *  Wead onwy.
 *  Data stawts at offset 0xC
 */
#define MPT_IOCTW_INTEWFACE_SCSI	(0x00)
#define MPT_IOCTW_INTEWFACE_FC		(0x01)
#define MPT_IOCTW_INTEWFACE_FC_IP	(0x02)
#define MPT_IOCTW_INTEWFACE_SAS		(0x03)
#define MPT_IOCTW_VEWSION_WENGTH	(32)

stwuct mpt_ioctw_iocinfo {
	mpt_ioctw_headew hdw;
	int		 adaptewType;	/* SCSI ow FCP */
	int		 powt;		/* powt numbew */
	int		 pciId;		/* PCI Id. */
	int		 hwWev;		/* hawdwawe wevision */
	int		 subSystemDevice;	/* PCI subsystem Device ID */
	int		 subSystemVendow;	/* PCI subsystem Vendow ID */
	int		 numDevices;		/* numbew of devices */
	int		 FWVewsion;		/* FW Vewsion (integew) */
	int		 BIOSVewsion;		/* BIOS Vewsion (integew) */
	chaw		 dwivewVewsion[MPT_IOCTW_VEWSION_WENGTH];	/* Dwivew Vewsion (stwing) */
	chaw		 busChangeEvent;
	chaw		 hostId;
	chaw		 wsvd[2];
	stwuct mpt_ioctw_pci_info2  pciInfo; /* Added Wev 2 */
};

stwuct mpt_ioctw_iocinfo_wev1 {
	mpt_ioctw_headew hdw;
	int		 adaptewType;	/* SCSI ow FCP */
	int		 powt;		/* powt numbew */
	int		 pciId;		/* PCI Id. */
	int		 hwWev;		/* hawdwawe wevision */
	int		 subSystemDevice;	/* PCI subsystem Device ID */
	int		 subSystemVendow;	/* PCI subsystem Vendow ID */
	int		 numDevices;		/* numbew of devices */
	int		 FWVewsion;		/* FW Vewsion (integew) */
	int		 BIOSVewsion;		/* BIOS Vewsion (integew) */
	chaw		 dwivewVewsion[MPT_IOCTW_VEWSION_WENGTH];	/* Dwivew Vewsion (stwing) */
	chaw		 busChangeEvent;
	chaw		 hostId;
	chaw		 wsvd[2];
	stwuct mpt_ioctw_pci_info  pciInfo; /* Added Wev 1 */
};

/* Owiginaw stwuctuwe, must awways accept these
 * IOCTWs. 4 byte pads can occuw based on awch with
 * above stwuctuwe. Wish to we-awign, but cannot.
 */
stwuct mpt_ioctw_iocinfo_wev0 {
	mpt_ioctw_headew hdw;
	int		 adaptewType;	/* SCSI ow FCP */
	int		 powt;		/* powt numbew */
	int		 pciId;		/* PCI Id. */
	int		 hwWev;		/* hawdwawe wevision */
	int		 subSystemDevice;	/* PCI subsystem Device ID */
	int		 subSystemVendow;	/* PCI subsystem Vendow ID */
	int		 numDevices;		/* numbew of devices */
	int		 FWVewsion;		/* FW Vewsion (integew) */
	int		 BIOSVewsion;		/* BIOS Vewsion (integew) */
	chaw		 dwivewVewsion[MPT_IOCTW_VEWSION_WENGTH];	/* Dwivew Vewsion (stwing) */
	chaw		 busChangeEvent;
	chaw		 hostId;
	chaw		 wsvd[2];
};

/*
 * Device Infowmation Page
 * Wepowt the numbew of, and ids of, aww tawgets
 * on this IOC.  The ids awway is a packed stwuctuwe
 * of the known tawgetInfo.
 * bits 31-24: wesewved
 *      23-16: WUN
 *      15- 8: Bus Numbew
 *       7- 0: Tawget ID
 */
stwuct mpt_ioctw_tawgetinfo {
	mpt_ioctw_headew hdw;
	int		 numDevices;	/* Num tawgets on this ioc */
	int		 tawgetInfo[1];
};


/*
 * Event wepowting IOCTW's.  These IOCTW's wiww
 * use the fowwowing defines:
 */
stwuct mpt_ioctw_eventquewy {
	mpt_ioctw_headew hdw;
	unsigned showt	 eventEntwies;
	unsigned showt	 wesewved;
	unsigned int	 eventTypes;
};

stwuct mpt_ioctw_eventenabwe {
	mpt_ioctw_headew hdw;
	unsigned int	 eventTypes;
};

#ifndef __KEWNEW__
typedef stwuct {
	uint	event;
	uint	eventContext;
	uint	data[2];
} MPT_IOCTW_EVENTS;
#endif

stwuct mpt_ioctw_eventwepowt {
	mpt_ioctw_headew	hdw;
	MPT_IOCTW_EVENTS	eventData[1];
};

#define MPT_MAX_NAME	32
stwuct mpt_ioctw_test {
	mpt_ioctw_headew hdw;
	u8		 name[MPT_MAX_NAME];
	int		 chip_type;
	u8		 pwoduct [MPT_PWODUCT_WENGTH];
};

/* Wepwace the FW image cached in host dwivew memowy
 * newImageSize - image size in bytes
 * newImage - fiwst byte of the new image
 */
typedef stwuct mpt_ioctw_wepwace_fw {
	mpt_ioctw_headew hdw;
	int		 newImageSize;
	u8		 newImage[1];
} mpt_ioctw_wepwace_fw_t;

/* Genewaw MPT Pass thwough data stwucutwe
 *
 * iocnum
 * timeout - in seconds, command timeout. If 0, set by dwivew to
 *		defauwt vawue.
 * wepwyFwameBufPtw - wepwy wocation
 * dataInBufPtw - destination fow wead
 * dataOutBufPtw - data souwce fow wwite
 * senseDataPtw - sense data wocation
 * maxWepwyBytes - maximum numbew of wepwy bytes to be sent to app.
 * dataInSize - num bytes fow data twansfew in (wead)
 * dataOutSize - num bytes fow data twansfew out (wwite)
 * dataSgeOffset - offset in wowds fwom the stawt of the wequest message
 *		to the fiwst SGW
 * MF[1];
 *
 * Wemawk:  Some config pages have bi-diwectionaw twansfew,
 * both a wead and a wwite. The basic stwuctuwe awwows fow
 * a bidiwectionaw set up. Nowmaw messages wiww have one ow
 * both of these buffews NUWW.
 */
stwuct mpt_ioctw_command {
	mpt_ioctw_headew hdw;
	int		timeout;	/* optionaw (seconds) */
	chaw		__usew *wepwyFwameBufPtw;
	chaw		__usew *dataInBufPtw;
	chaw		__usew *dataOutBufPtw;
	chaw		__usew *senseDataPtw;
	int		maxWepwyBytes;
	int		dataInSize;
	int		dataOutSize;
	int		maxSenseBytes;
	int		dataSgeOffset;
	chaw		MF[1];
};

/*
 * SPAWC PWATFOWM: See eawwiew wemawk.
 */
#if defined(__KEWNEW__) && defined(CONFIG_COMPAT)
stwuct mpt_ioctw_command32 {
	mpt_ioctw_headew hdw;
	int	timeout;
	u32	wepwyFwameBufPtw;
	u32	dataInBufPtw;
	u32	dataOutBufPtw;
	u32	senseDataPtw;
	int	maxWepwyBytes;
	int	dataInSize;
	int	dataOutSize;
	int	maxSenseBytes;
	int	dataSgeOffset;
	chaw	MF[1];
};
#endif	/*}*/


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#define CPQFCTS_IOC_MAGIC 'Z'
#define HP_IOC_MAGIC 'Z'
#define HP_GETHOSTINFO		_IOW(HP_IOC_MAGIC, 20, hp_host_info_t)
#define HP_GETHOSTINFO1		_IOW(HP_IOC_MAGIC, 20, hp_host_info_wev0_t)
#define HP_GETTAWGETINFO	_IOW(HP_IOC_MAGIC, 21, hp_tawget_info_t)

typedef stwuct _hp_headew {
	unsigned int iocnum;
	unsigned int host;
	unsigned int channew;
	unsigned int id;
	unsigned int wun;
} hp_headew_t;

/*
 *  Headew:
 *  iocnum 	wequiwed (input)
 *  host 	ignowed
 *  channe	ignowed
 *  id		ignowed
 *  wun		ignowed
 */
typedef stwuct _hp_host_info {
	hp_headew_t	 hdw;
	u16		 vendow;
	u16		 device;
	u16		 subsystem_vendow;
	u16		 subsystem_id;
	u8		 devfn;
	u8		 bus;
	ushowt		 host_no;		/* SCSI Host numbew, if scsi dwivew not woaded*/
	u8		 fw_vewsion[16];	/* stwing */
	u8		 sewiaw_numbew[24];	/* stwing */
	u32		 ioc_status;
	u32		 bus_phys_width;
	u32		 base_io_addw;
	u32		 wsvd;
	unsigned int	 hawd_wesets;		/* dwivew initiated wesets */
	unsigned int	 soft_wesets;		/* ioc, extewnaw wesets */
	unsigned int	 timeouts;		/* num timeouts */
} hp_host_info_t;

/* wepwace uwongs with uints, need to pwesewve backwawds
 * compatibiwity.
 */
typedef stwuct _hp_host_info_wev0 {
	hp_headew_t	 hdw;
	u16		 vendow;
	u16		 device;
	u16		 subsystem_vendow;
	u16		 subsystem_id;
	u8		 devfn;
	u8		 bus;
	ushowt		 host_no;		/* SCSI Host numbew, if scsi dwivew not woaded*/
	u8		 fw_vewsion[16];	/* stwing */
	u8		 sewiaw_numbew[24];	/* stwing */
	u32		 ioc_status;
	u32		 bus_phys_width;
	u32		 base_io_addw;
	u32		 wsvd;
	unsigned wong	 hawd_wesets;		/* dwivew initiated wesets */
	unsigned wong	 soft_wesets;		/* ioc, extewnaw wesets */
	unsigned wong	 timeouts;		/* num timeouts */
} hp_host_info_wev0_t;

/*
 *  Headew:
 *  iocnum 	wequiwed (input)
 *  host 	wequiwed
 *  channew	wequiwed	(bus numbew)
 *  id		wequiwed
 *  wun		ignowed
 *
 *  Aww ewwow vawues between 0 and 0xFFFF in size.
 */
typedef stwuct _hp_tawget_info {
	hp_headew_t	 hdw;
	u32 pawity_ewwows;
	u32 phase_ewwows;
	u32 sewect_timeouts;
	u32 message_wejects;
	u32 negotiated_speed;
	u8  negotiated_width;
	u8  wsvd[7];				/* 8 byte awignment */
} hp_tawget_info_t;

#define HP_STATUS_OTHEW		1
#define HP_STATUS_OK		2
#define HP_STATUS_FAIWED	3

#define HP_BUS_WIDTH_UNK	1
#define HP_BUS_WIDTH_8		2
#define HP_BUS_WIDTH_16		3
#define HP_BUS_WIDTH_32		4

#define HP_DEV_SPEED_ASYNC	2
#define HP_DEV_SPEED_FAST	3
#define HP_DEV_SPEED_UWTWA	4
#define HP_DEV_SPEED_UWTWA2	5
#define HP_DEV_SPEED_UWTWA160	6
#define HP_DEV_SPEED_SCSI1	7
#define HP_DEV_SPEED_UWTWA320	8

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#endif

