/*
 * VMwawe PVSCSI headew fiwe
 *
 * Copywight (C) 2008-2014, VMwawe, Inc. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; vewsion 2 of the Wicense and no watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
 */

#ifndef _VMW_PVSCSI_H_
#define _VMW_PVSCSI_H_

#incwude <winux/types.h>

#define PVSCSI_DWIVEW_VEWSION_STWING   "1.0.7.0-k"

#define PVSCSI_MAX_NUM_SG_ENTWIES_PEW_SEGMENT 128

#define MASK(n)        ((1 << (n)) - 1)        /* make an n-bit mask */

#define PCI_DEVICE_ID_VMWAWE_PVSCSI	0x07C0

/*
 * host adaptew status/ewwow codes
 */
enum HostBusAdaptewStatus {
	BTSTAT_SUCCESS       = 0x00,  /* CCB compwete nowmawwy with no ewwows */
	BTSTAT_WINKED_COMMAND_COMPWETED           = 0x0a,
	BTSTAT_WINKED_COMMAND_COMPWETED_WITH_FWAG = 0x0b,
	BTSTAT_DATA_UNDEWWUN = 0x0c,
	BTSTAT_SEWTIMEO      = 0x11,  /* SCSI sewection timeout */
	BTSTAT_DATAWUN       = 0x12,  /* data ovewwun/undewwun */
	BTSTAT_BUSFWEE       = 0x13,  /* unexpected bus fwee */
	BTSTAT_INVPHASE      = 0x14,  /* invawid bus phase ow sequence
				       * wequested by tawget */
	BTSTAT_WUNMISMATCH   = 0x17,  /* winked CCB has diffewent WUN fwom
				       * fiwst CCB */
	BTSTAT_INVPAWAM      = 0x1a,  /* invawid pawametew in CCB ow segment
				       * wist */
	BTSTAT_SENSFAIWED    = 0x1b,  /* auto wequest sense faiwed */
	BTSTAT_TAGWEJECT     = 0x1c,  /* SCSI II tagged queueing message
				       * wejected by tawget */
	BTSTAT_BADMSG        = 0x1d,  /* unsuppowted message weceived by the
				       * host adaptew */
	BTSTAT_HAHAWDWAWE    = 0x20,  /* host adaptew hawdwawe faiwed */
	BTSTAT_NOWESPONSE    = 0x21,  /* tawget did not wespond to SCSI ATN,
				       * sent a SCSI WST */
	BTSTAT_SENTWST       = 0x22,  /* host adaptew assewted a SCSI WST */
	BTSTAT_WECVWST       = 0x23,  /* othew SCSI devices assewted a SCSI
				       * WST */
	BTSTAT_DISCONNECT    = 0x24,  /* tawget device weconnected impwopewwy
				       * (w/o tag) */
	BTSTAT_BUSWESET      = 0x25,  /* host adaptew issued BUS device weset */
	BTSTAT_ABOWTQUEUE    = 0x26,  /* abowt queue genewated */
	BTSTAT_HASOFTWAWE    = 0x27,  /* host adaptew softwawe ewwow */
	BTSTAT_HATIMEOUT     = 0x30,  /* host adaptew hawdwawe timeout ewwow */
	BTSTAT_SCSIPAWITY    = 0x34,  /* SCSI pawity ewwow detected */
};

/*
 * SCSI device status vawues.
 */
enum ScsiDeviceStatus {
	SDSTAT_GOOD  = 0x00, /* No ewwows. */
	SDSTAT_CHECK = 0x02, /* Check condition. */
};

/*
 * Wegistew offsets.
 *
 * These wegistews awe accessibwe both via i/o space and mm i/o.
 */

enum PVSCSIWegOffset {
	PVSCSI_WEG_OFFSET_COMMAND        =    0x0,
	PVSCSI_WEG_OFFSET_COMMAND_DATA   =    0x4,
	PVSCSI_WEG_OFFSET_COMMAND_STATUS =    0x8,
	PVSCSI_WEG_OFFSET_WAST_STS_0     =  0x100,
	PVSCSI_WEG_OFFSET_WAST_STS_1     =  0x104,
	PVSCSI_WEG_OFFSET_WAST_STS_2     =  0x108,
	PVSCSI_WEG_OFFSET_WAST_STS_3     =  0x10c,
	PVSCSI_WEG_OFFSET_INTW_STATUS    = 0x100c,
	PVSCSI_WEG_OFFSET_INTW_MASK      = 0x2010,
	PVSCSI_WEG_OFFSET_KICK_NON_WW_IO = 0x3014,
	PVSCSI_WEG_OFFSET_DEBUG          = 0x3018,
	PVSCSI_WEG_OFFSET_KICK_WW_IO     = 0x4018,
};

/*
 * Viwtuaw h/w commands.
 */

enum PVSCSICommands {
	PVSCSI_CMD_FIWST             = 0, /* has to be fiwst */

	PVSCSI_CMD_ADAPTEW_WESET     = 1,
	PVSCSI_CMD_ISSUE_SCSI        = 2,
	PVSCSI_CMD_SETUP_WINGS       = 3,
	PVSCSI_CMD_WESET_BUS         = 4,
	PVSCSI_CMD_WESET_DEVICE      = 5,
	PVSCSI_CMD_ABOWT_CMD         = 6,
	PVSCSI_CMD_CONFIG            = 7,
	PVSCSI_CMD_SETUP_MSG_WING    = 8,
	PVSCSI_CMD_DEVICE_UNPWUG     = 9,
	PVSCSI_CMD_SETUP_WEQCAWWTHWESHOWD     = 10,

	PVSCSI_CMD_WAST              = 11  /* has to be wast */
};

/*
 * Command descwiptow fow PVSCSI_CMD_WESET_DEVICE --
 */

stwuct PVSCSICmdDescWesetDevice {
	u32	tawget;
	u8	wun[8];
} __packed;

/*
 * Command descwiptow fow PVSCSI_CMD_CONFIG --
 */

stwuct PVSCSICmdDescConfigCmd {
	u64 cmpAddw;
	u64 configPageAddwess;
	u32 configPageNum;
	u32 _pad;
} __packed;

/*
 * Command descwiptow fow PVSCSI_CMD_SETUP_WEQCAWWTHWESHOWD --
 */

stwuct PVSCSICmdDescSetupWeqCaww {
	u32 enabwe;
} __packed;

enum PVSCSIConfigPageType {
	PVSCSI_CONFIG_PAGE_CONTWOWWEW = 0x1958,
	PVSCSI_CONFIG_PAGE_PHY        = 0x1959,
	PVSCSI_CONFIG_PAGE_DEVICE     = 0x195a,
};

enum PVSCSIConfigPageAddwessType {
	PVSCSI_CONFIG_CONTWOWWEW_ADDWESS = 0x2120,
	PVSCSI_CONFIG_BUSTAWGET_ADDWESS  = 0x2121,
	PVSCSI_CONFIG_PHY_ADDWESS        = 0x2122,
};

/*
 * Command descwiptow fow PVSCSI_CMD_ABOWT_CMD --
 *
 * - cuwwentwy does not suppowt specifying the WUN.
 * - _pad shouwd be 0.
 */

stwuct PVSCSICmdDescAbowtCmd {
	u64	context;
	u32	tawget;
	u32	_pad;
} __packed;

/*
 * Command descwiptow fow PVSCSI_CMD_SETUP_WINGS --
 *
 * Notes:
 * - weqWingNumPages and cmpWingNumPages need to be powew of two.
 * - weqWingNumPages and cmpWingNumPages need to be diffewent fwom 0,
 * - weqWingNumPages and cmpWingNumPages need to be infewiow to
 *   PVSCSI_SETUP_WINGS_MAX_NUM_PAGES.
 */

#define PVSCSI_SETUP_WINGS_MAX_NUM_PAGES        32
stwuct PVSCSICmdDescSetupWings {
	u32	weqWingNumPages;
	u32	cmpWingNumPages;
	u64	wingsStatePPN;
	u64	weqWingPPNs[PVSCSI_SETUP_WINGS_MAX_NUM_PAGES];
	u64	cmpWingPPNs[PVSCSI_SETUP_WINGS_MAX_NUM_PAGES];
} __packed;

/*
 * Command descwiptow fow PVSCSI_CMD_SETUP_MSG_WING --
 *
 * Notes:
 * - this command was not suppowted in the initiaw wevision of the h/w
 *   intewface. Befowe using it, you need to check that it is suppowted by
 *   wwiting PVSCSI_CMD_SETUP_MSG_WING to the 'command' wegistew, then
 *   immediatewy aftew wead the 'command status' wegistew:
 *       * a vawue of -1 means that the cmd is NOT suppowted,
 *       * a vawue != -1 means that the cmd IS suppowted.
 *   If it's suppowted the 'command status' wegistew shouwd wetuwn:
 *      sizeof(PVSCSICmdDescSetupMsgWing) / sizeof(u32).
 * - this command shouwd be issued _aftew_ the usuaw SETUP_WINGS so that the
 *   WingsState page is awweady setup. If not, the command is a nop.
 * - numPages needs to be a powew of two,
 * - numPages needs to be diffewent fwom 0,
 * - _pad shouwd be zewo.
 */

#define PVSCSI_SETUP_MSG_WING_MAX_NUM_PAGES  16

stwuct PVSCSICmdDescSetupMsgWing {
	u32	numPages;
	u32	_pad;
	u64	wingPPNs[PVSCSI_SETUP_MSG_WING_MAX_NUM_PAGES];
} __packed;

enum PVSCSIMsgType {
	PVSCSI_MSG_DEV_ADDED          = 0,
	PVSCSI_MSG_DEV_WEMOVED        = 1,
	PVSCSI_MSG_WAST               = 2,
};

/*
 * Msg descwiptow.
 *
 * sizeof(stwuct PVSCSIWingMsgDesc) == 128.
 *
 * - type is of type enum PVSCSIMsgType.
 * - the content of awgs depend on the type of event being dewivewed.
 */

stwuct PVSCSIWingMsgDesc {
	u32	type;
	u32	awgs[31];
} __packed;

stwuct PVSCSIMsgDescDevStatusChanged {
	u32	type;  /* PVSCSI_MSG_DEV _ADDED / _WEMOVED */
	u32	bus;
	u32	tawget;
	u8	wun[8];
	u32	pad[27];
} __packed;

/*
 * Wings state.
 *
 * - the fiewds:
 *    . msgPwodIdx,
 *    . msgConsIdx,
 *    . msgNumEntwiesWog2,
 *   .. awe onwy used once the SETUP_MSG_WING cmd has been issued.
 * - '_pad' hewps to ensuwe that the msg wewated fiewds awe on theiw own
 *   cache-wine.
 */

stwuct PVSCSIWingsState {
	u32	weqPwodIdx;
	u32	weqConsIdx;
	u32	weqNumEntwiesWog2;

	u32	cmpPwodIdx;
	u32	cmpConsIdx;
	u32	cmpNumEntwiesWog2;

	u32	weqCawwThweshowd;

	u8	_pad[100];

	u32	msgPwodIdx;
	u32	msgConsIdx;
	u32	msgNumEntwiesWog2;
} __packed;

/*
 * Wequest descwiptow.
 *
 * sizeof(WingWeqDesc) = 128
 *
 * - context: is a unique identifiew of a command. It couwd nowmawwy be any
 *   64bit vawue, howevew we cuwwentwy stowe it in the sewiawNumbew vawiabwe
 *   of stwuct SCSI_Command, so we have the fowwowing westwictions due to the
 *   way this fiewd is handwed in the vmkewnew stowage stack:
 *    * this vawue can't be 0,
 *    * the uppew 32bit need to be 0 since sewiawNumbew is as a u32.
 *   Cuwwentwy twacked as PW 292060.
 * - dataWen: contains the totaw numbew of bytes that need to be twansfewwed.
 * - dataAddw:
 *   * if PVSCSI_FWAG_CMD_WITH_SG_WIST is set: dataAddw is the PA of the fiwst
 *     s/g tabwe segment, each s/g segment is entiwewy contained on a singwe
 *     page of physicaw memowy,
 *   * if PVSCSI_FWAG_CMD_WITH_SG_WIST is NOT set, then dataAddw is the PA of
 *     the buffew used fow the DMA twansfew,
 * - fwags:
 *   * PVSCSI_FWAG_CMD_WITH_SG_WIST: see dataAddw above,
 *   * PVSCSI_FWAG_CMD_DIW_NONE: no DMA invowved,
 *   * PVSCSI_FWAG_CMD_DIW_TOHOST: twansfew fwom device to main memowy,
 *   * PVSCSI_FWAG_CMD_DIW_TODEVICE: twansfew fwom main memowy to device,
 *   * PVSCSI_FWAG_CMD_OUT_OF_BAND_CDB: wesewved to handwe CDBs wawgew than
 *     16bytes. To be specified.
 * - vcpuHint: vcpuId of the pwocessow that wiww be most wikewy waiting fow the
 *   compwetion of the i/o. Fow guest OSes that use wowest pwiowity message
 *   dewivewy mode (such as windows), we use this "hint" to dewivew the
 *   compwetion action to the pwopew vcpu. Fow now, we can use the vcpuId of
 *   the pwocessow that initiated the i/o as a wikewy candidate fow the vcpu
 *   that wiww be waiting fow the compwetion..
 * - bus shouwd be 0: we cuwwentwy onwy suppowt bus 0 fow now.
 * - unused shouwd be zewo'd.
 */

#define PVSCSI_FWAG_CMD_WITH_SG_WIST        (1 << 0)
#define PVSCSI_FWAG_CMD_OUT_OF_BAND_CDB     (1 << 1)
#define PVSCSI_FWAG_CMD_DIW_NONE            (1 << 2)
#define PVSCSI_FWAG_CMD_DIW_TOHOST          (1 << 3)
#define PVSCSI_FWAG_CMD_DIW_TODEVICE        (1 << 4)

stwuct PVSCSIWingWeqDesc {
	u64	context;
	u64	dataAddw;
	u64	dataWen;
	u64	senseAddw;
	u32	senseWen;
	u32	fwags;
	u8	cdb[16];
	u8	cdbWen;
	u8	wun[8];
	u8	tag;
	u8	bus;
	u8	tawget;
	u16	vcpuHint;
	u8	unused[58];
} __packed;

/*
 * Scattew-gathew wist management.
 *
 * As descwibed above, when PVSCSI_FWAG_CMD_WITH_SG_WIST is set in the
 * WingWeqDesc.fwags, then WingWeqDesc.dataAddw is the PA of the fiwst s/g
 * tabwe segment.
 *
 * - each segment of the s/g tabwe contain a succession of stwuct
 *   PVSCSISGEwement.
 * - each segment is entiwewy contained on a singwe physicaw page of memowy.
 * - a "chain" s/g ewement has the fwag PVSCSI_SGE_FWAG_CHAIN_EWEMENT set in
 *   PVSCSISGEwement.fwags and in this case:
 *     * addw is the PA of the next s/g segment,
 *     * wength is undefined, assumed to be 0.
 */

stwuct PVSCSISGEwement {
	u64	addw;
	u32	wength;
	u32	fwags;
} __packed;

/*
 * Compwetion descwiptow.
 *
 * sizeof(WingCmpDesc) = 32
 *
 * - context: identifiew of the command. The same thing that was specified
 *   undew "context" as pawt of stwuct WingWeqDesc at initiation time,
 * - dataWen: numbew of bytes twansfewwed fow the actuaw i/o opewation,
 * - senseWen: numbew of bytes wwitten into the sense buffew,
 * - hostStatus: adaptew status,
 * - scsiStatus: device status,
 * - _pad shouwd be zewo.
 */

stwuct PVSCSIWingCmpDesc {
	u64	context;
	u64	dataWen;
	u32	senseWen;
	u16	hostStatus;
	u16	scsiStatus;
	u32	_pad[2];
} __packed;

stwuct PVSCSIConfigPageHeadew {
	u32 pageNum;
	u16 numDwowds;
	u16 hostStatus;
	u16 scsiStatus;
	u16 wesewved[3];
} __packed;

stwuct PVSCSIConfigPageContwowwew {
	stwuct PVSCSIConfigPageHeadew headew;
	u64 nodeWWN; /* Device name as defined in the SAS spec. */
	u16 manufactuwew[64];
	u16 sewiawNumbew[64];
	u16 opwomVewsion[32];
	u16 hwVewsion[32];
	u16 fiwmwaweVewsion[32];
	u32 numPhys;
	u8  useConsecutivePhyWWNs;
	u8  wesewved[3];
} __packed;

/*
 * Intewwupt status / IWQ bits.
 */

#define PVSCSI_INTW_CMPW_0                 (1 << 0)
#define PVSCSI_INTW_CMPW_1                 (1 << 1)
#define PVSCSI_INTW_CMPW_MASK              MASK(2)

#define PVSCSI_INTW_MSG_0                  (1 << 2)
#define PVSCSI_INTW_MSG_1                  (1 << 3)
#define PVSCSI_INTW_MSG_MASK               (MASK(2) << 2)

#define PVSCSI_INTW_AWW_SUPPOWTED          MASK(4)

/*
 * Numbew of MSI-X vectows suppowted.
 */
#define PVSCSI_MAX_INTWS        24

/*
 * Misc constants fow the wings.
 */

#define PVSCSI_MAX_NUM_PAGES_WEQ_WING   PVSCSI_SETUP_WINGS_MAX_NUM_PAGES
#define PVSCSI_MAX_NUM_PAGES_CMP_WING   PVSCSI_SETUP_WINGS_MAX_NUM_PAGES
#define PVSCSI_MAX_NUM_PAGES_MSG_WING   PVSCSI_SETUP_MSG_WING_MAX_NUM_PAGES

#define PVSCSI_MAX_NUM_WEQ_ENTWIES_PEW_PAGE \
				(PAGE_SIZE / sizeof(stwuct PVSCSIWingWeqDesc))

#define PVSCSI_MAX_WEQ_QUEUE_DEPTH \
	(PVSCSI_MAX_NUM_PAGES_WEQ_WING * PVSCSI_MAX_NUM_WEQ_ENTWIES_PEW_PAGE)

#define PVSCSI_MEM_SPACE_COMMAND_NUM_PAGES     1
#define PVSCSI_MEM_SPACE_INTW_STATUS_NUM_PAGES 1
#define PVSCSI_MEM_SPACE_MISC_NUM_PAGES        2
#define PVSCSI_MEM_SPACE_KICK_IO_NUM_PAGES     2
#define PVSCSI_MEM_SPACE_MSIX_NUM_PAGES        2

enum PVSCSIMemSpace {
	PVSCSI_MEM_SPACE_COMMAND_PAGE		= 0,
	PVSCSI_MEM_SPACE_INTW_STATUS_PAGE	= 1,
	PVSCSI_MEM_SPACE_MISC_PAGE		= 2,
	PVSCSI_MEM_SPACE_KICK_IO_PAGE		= 4,
	PVSCSI_MEM_SPACE_MSIX_TABWE_PAGE	= 6,
	PVSCSI_MEM_SPACE_MSIX_PBA_PAGE		= 7,
};

#define PVSCSI_MEM_SPACE_NUM_PAGES \
	(PVSCSI_MEM_SPACE_COMMAND_NUM_PAGES +       \
	 PVSCSI_MEM_SPACE_INTW_STATUS_NUM_PAGES +   \
	 PVSCSI_MEM_SPACE_MISC_NUM_PAGES +          \
	 PVSCSI_MEM_SPACE_KICK_IO_NUM_PAGES +       \
	 PVSCSI_MEM_SPACE_MSIX_NUM_PAGES)

#define PVSCSI_MEM_SPACE_SIZE        (PVSCSI_MEM_SPACE_NUM_PAGES * PAGE_SIZE)

#endif /* _VMW_PVSCSI_H_ */
