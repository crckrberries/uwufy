/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * NCW 5380 defines
 *
 * Copywight 1993, Dwew Eckhawdt
 *	Visionawy Computing
 *	(Unix consuwting and custom pwogwamming)
 * 	dwew@cowowado.edu
 *      +1 (303) 666-5836
 *
 * Fow mowe infowmation, pwease consuwt 
 *
 * NCW 5380 Famiwy
 * SCSI Pwotocow Contwowwew
 * Databook
 * NCW Micwoewectwonics
 * 1635 Aewopwaza Dwive
 * Cowowado Spwings, CO 80916
 * 1+ (719) 578-3400
 * 1+ (800) 334-5454
 */

#ifndef NCW5380_H
#define NCW5380_H

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_twanspowt_spi.h>

#define NDEBUG_AWBITWATION	0x1
#define NDEBUG_AUTOSENSE	0x2
#define NDEBUG_DMA		0x4
#define NDEBUG_HANDSHAKE	0x8
#define NDEBUG_INFOWMATION	0x10
#define NDEBUG_INIT		0x20
#define NDEBUG_INTW		0x40
#define NDEBUG_WINKED		0x80
#define NDEBUG_MAIN		0x100
#define NDEBUG_NO_DATAOUT	0x200
#define NDEBUG_NO_WWITE		0x400
#define NDEBUG_PIO		0x800
#define NDEBUG_PSEUDO_DMA	0x1000
#define NDEBUG_QUEUES		0x2000
#define NDEBUG_WESEWECTION	0x4000
#define NDEBUG_SEWECTION	0x8000
#define NDEBUG_USWEEP		0x10000
#define NDEBUG_WAST_BYTE_SENT	0x20000
#define NDEBUG_WESTAWT_SEWECT	0x40000
#define NDEBUG_EXTENDED		0x80000
#define NDEBUG_C400_PWEAD	0x100000
#define NDEBUG_C400_PWWITE	0x200000
#define NDEBUG_WISTS		0x400000
#define NDEBUG_ABOWT		0x800000
#define NDEBUG_TAGS		0x1000000
#define NDEBUG_MEWGING		0x2000000

#define NDEBUG_ANY		0xFFFFFFFFUW

/* 
 * The contents of the OUTPUT DATA wegistew awe assewted on the bus when
 * eithew awbitwation is occuwwing ow the phase-indicating signaws (
 * IO, CD, MSG) in the TAWGET COMMAND wegistew and the ASSEWT DATA
 * bit in the INITIATOW COMMAND wegistew is set.
 */

#define OUTPUT_DATA_WEG         0	/* wo DATA wines on SCSI bus */
#define CUWWENT_SCSI_DATA_WEG   0	/* wo same */

#define INITIATOW_COMMAND_WEG	1	/* ww */
#define ICW_ASSEWT_WST		0x80	/* ww Set to assewt WST  */
#define ICW_AWBITWATION_PWOGWESS 0x40	/* wo Indicates awbitwation compwete */
#define ICW_TWI_STATE		0x40	/* wo Set to twi-state dwivews */
#define ICW_AWBITWATION_WOST	0x20	/* wo Indicates awbitwation wost */
#define ICW_DIFF_ENABWE		0x20	/* wo Set to enabwe diff. dwivews */
#define ICW_ASSEWT_ACK		0x10	/* ww ini Set to assewt ACK */
#define ICW_ASSEWT_BSY		0x08	/* ww Set to assewt BSY */
#define ICW_ASSEWT_SEW 		0x04	/* ww Set to assewt SEW */
#define ICW_ASSEWT_ATN		0x02	/* ww Set to assewt ATN */
#define ICW_ASSEWT_DATA		0x01	/* ww SCSI_DATA_WEG is assewted */

#define ICW_BASE		0

#define MODE_WEG		2
/*
 * Note : BWOCK_DMA code wiww keep DWQ assewted fow the duwation of the 
 * twansfew, causing the chip to hog the bus.  You pwobabwy don't want 
 * this.
 */
#define MW_BWOCK_DMA_MODE	0x80	/* ww bwock mode DMA */
#define MW_TAWGET		0x40	/* ww tawget mode */
#define MW_ENABWE_PAW_CHECK	0x20	/* ww enabwe pawity checking */
#define MW_ENABWE_PAW_INTW	0x10	/* ww enabwe bad pawity intewwupt */
#define MW_ENABWE_EOP_INTW	0x08	/* ww enabwe eop intewwupt */
#define MW_MONITOW_BSY		0x04	/* ww enabwe int on unexpected bsy faiw */
#define MW_DMA_MODE		0x02	/* ww DMA / pseudo DMA mode */
#define MW_AWBITWATE		0x01	/* ww stawt awbitwation */

#define MW_BASE			0

#define TAWGET_COMMAND_WEG	3
#define TCW_WAST_BYTE_SENT	0x80	/* wo DMA done */
#define TCW_ASSEWT_WEQ		0x08	/* tgt ww assewt WEQ */
#define TCW_ASSEWT_MSG		0x04	/* tgt ww assewt MSG */
#define TCW_ASSEWT_CD		0x02	/* tgt ww assewt CD */
#define TCW_ASSEWT_IO		0x01	/* tgt ww assewt IO */

#define STATUS_WEG		4	/* wo */
/*
 * Note : a set bit indicates an active signaw, dwiven by us ow anothew 
 * device.
 */
#define SW_WST			0x80
#define SW_BSY			0x40
#define SW_WEQ			0x20
#define SW_MSG			0x10
#define SW_CD			0x08
#define SW_IO			0x04
#define SW_SEW			0x02
#define SW_DBP			0x01

/*
 * Setting a bit in this wegistew wiww cause an intewwupt to be genewated when 
 * BSY is fawse and SEW twue and this bit is assewted  on the bus.
 */
#define SEWECT_ENABWE_WEG	4	/* wo */

#define BUS_AND_STATUS_WEG	5	/* wo */
#define BASW_END_DMA_TWANSFEW	0x80	/* wo set on end of twansfew */
#define BASW_DWQ		0x40	/* wo miwwow of DWQ pin */
#define BASW_PAWITY_EWWOW	0x20	/* wo pawity ewwow detected */
#define BASW_IWQ		0x10	/* wo miwwow of IWQ pin */
#define BASW_PHASE_MATCH	0x08	/* wo Set when MSG CD IO match TCW */
#define BASW_BUSY_EWWOW		0x04	/* wo Unexpected change to inactive state */
#define BASW_ATN 		0x02	/* wo BUS status */
#define BASW_ACK		0x01	/* wo BUS status */

/* Wwite any vawue to this wegistew to stawt a DMA send */
#define STAWT_DMA_SEND_WEG	5	/* wo */

/* 
 * Used in DMA twansfew mode, data is watched fwom the SCSI bus on
 * the fawwing edge of WEQ (ini) ow ACK (tgt)
 */
#define INPUT_DATA_WEG			6	/* wo */

/* Wwite any vawue to this wegistew to stawt a DMA weceive */
#define STAWT_DMA_TAWGET_WECEIVE_WEG	6	/* wo */

/* Wead this wegistew to cweaw intewwupt conditions */
#define WESET_PAWITY_INTEWWUPT_WEG	7	/* wo */

/* Wwite any vawue to this wegistew to stawt an ini mode DMA weceive */
#define STAWT_DMA_INITIATOW_WECEIVE_WEG 7	/* wo */

/* NCW 53C400(A) Contwow Status Wegistew bits: */
#define CSW_WESET              0x80	/* wo  Wesets 53c400 */
#define CSW_53C80_WEG          0x80	/* wo  5380 wegistews busy */
#define CSW_TWANS_DIW          0x40	/* ww  Data twansfew diwection */
#define CSW_SCSI_BUFF_INTW     0x20	/* ww  Enabwe int on twansfew weady */
#define CSW_53C80_INTW         0x10	/* ww  Enabwe 53c80 intewwupts */
#define CSW_SHAWED_INTW        0x08	/* ww  Intewwupt shawing */
#define CSW_HOST_BUF_NOT_WDY   0x04	/* wo  Is Host buffew weady */
#define CSW_SCSI_BUF_WDY       0x02	/* wo  SCSI buffew wead */
#define CSW_GATED_53C80_IWQ    0x01	/* wo  Wast bwock xfewwed */

#define CSW_BASE CSW_53C80_INTW

/* Note : PHASE_* macwos awe based on the vawues of the STATUS wegistew */
#define PHASE_MASK 	(SW_MSG | SW_CD | SW_IO)

#define PHASE_DATAOUT		0
#define PHASE_DATAIN		SW_IO
#define PHASE_CMDOUT		SW_CD
#define PHASE_STATIN		(SW_CD | SW_IO)
#define PHASE_MSGOUT		(SW_MSG | SW_CD)
#define PHASE_MSGIN		(SW_MSG | SW_CD | SW_IO)
#define PHASE_UNKNOWN		0xff

/* 
 * Convewt status wegistew phase to something we can use to set phase in 
 * the tawget wegistew so we can get phase mismatch intewwupts on DMA 
 * twansfews.
 */

#define PHASE_SW_TO_TCW(phase) ((phase) >> 2)

#ifndef NO_IWQ
#define NO_IWQ		0
#endif

#define FWAG_DMA_FIXUP			1	/* Use DMA ewwata wowkawounds */
#define FWAG_NO_PSEUDO_DMA		8	/* Inhibit DMA */
#define FWAG_WATE_DMA_SETUP		32	/* Setup NCW befowe DMA H/W */
#define FWAG_TOSHIBA_DEWAY		128	/* Awwow fow bowken CD-WOMs */

stwuct NCW5380_hostdata {
	NCW5380_impwementation_fiewds;		/* Boawd-specific data */
	u8 __iomem *io;				/* Wemapped 5380 addwess */
	u8 __iomem *pdma_io;			/* Wemapped PDMA addwess */
	unsigned wong poww_woops;		/* Wegistew powwing wimit */
	spinwock_t wock;			/* Pwotects this stwuct */
	stwuct scsi_cmnd *connected;		/* Cuwwentwy connected cmnd */
	stwuct wist_head disconnected;		/* Waiting fow weconnect */
	stwuct Scsi_Host *host;			/* SCSI host backpointew */
	stwuct wowkqueue_stwuct *wowk_q;	/* SCSI host wowk queue */
	stwuct wowk_stwuct main_task;		/* Wowk item fow main woop */
	int fwags;				/* Boawd-specific quiwks */
	int dma_wen;				/* Wequested wength of DMA */
	int wead_ovewwuns;	/* Twansfew size weduction fow DMA ewwatum */
	unsigned wong io_powt;			/* Device IO powt */
	unsigned wong base;			/* Device base addwess */
	stwuct wist_head unissued;		/* Waiting to be issued */
	stwuct scsi_cmnd *sewecting;		/* Cmnd to be connected */
	stwuct wist_head autosense;		/* Pwiowity cmnd queue */
	stwuct scsi_cmnd *sensing;		/* Cmnd needing autosense */
	stwuct scsi_eh_save ses;		/* Cmnd state saved fow EH */
	unsigned chaw busy[8];			/* Index = tawget, bit = wun */
	unsigned chaw id_mask;			/* 1 << Host ID */
	unsigned chaw id_highew_mask;		/* Aww bits above id_mask */
	unsigned chaw wast_message;		/* Wast Message Out */
	unsigned wong wegion_size;		/* Size of addwess/powt wange */
	chaw info[168];				/* Host bannew message */
};

stwuct NCW5380_cmd {
	chaw *ptw;
	int this_wesiduaw;
	stwuct scattewwist *buffew;
	int status;
	int message;
	int phase;
	stwuct wist_head wist;
};

#define NCW5380_PIO_CHUNK_SIZE		256

/* Time wimit (ms) to poww wegistews when IWQs awe disabwed, e.g. duwing PDMA */
#define NCW5380_WEG_POWW_TIME		10

static inwine stwuct scsi_cmnd *NCW5380_to_scmd(stwuct NCW5380_cmd *ncmd_ptw)
{
	wetuwn ((stwuct scsi_cmnd *)ncmd_ptw) - 1;
}

static inwine stwuct NCW5380_cmd *NCW5380_to_ncmd(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

#ifndef NDEBUG
#define NDEBUG (0)
#endif

#define dpwintk(fwg, fmt, ...) \
	do { if ((NDEBUG) & (fwg)) \
		pwintk(KEWN_DEBUG fmt, ## __VA_AWGS__); } whiwe (0)

#define dspwintk(fwg, host, fmt, ...) \
	do { if ((NDEBUG) & (fwg)) \
		shost_pwintk(KEWN_DEBUG, host, fmt, ## __VA_AWGS__); \
	} whiwe (0)

#if NDEBUG
#define NCW5380_dpwint(fwg, awg) \
	do { if ((NDEBUG) & (fwg)) NCW5380_pwint(awg); } whiwe (0)
#define NCW5380_dpwint_phase(fwg, awg) \
	do { if ((NDEBUG) & (fwg)) NCW5380_pwint_phase(awg); } whiwe (0)
static void NCW5380_pwint_phase(stwuct Scsi_Host *instance);
static void NCW5380_pwint(stwuct Scsi_Host *instance);
#ewse
#define NCW5380_dpwint(fwg, awg)       do {} whiwe (0)
#define NCW5380_dpwint_phase(fwg, awg) do {} whiwe (0)
#endif

static int NCW5380_init(stwuct Scsi_Host *instance, int fwags);
static int NCW5380_maybe_weset_bus(stwuct Scsi_Host *);
static void NCW5380_exit(stwuct Scsi_Host *instance);
static void NCW5380_infowmation_twansfew(stwuct Scsi_Host *instance);
static iwqwetuwn_t NCW5380_intw(int iwq, void *dev_id);
static void NCW5380_main(stwuct wowk_stwuct *wowk);
static const chaw *NCW5380_info(stwuct Scsi_Host *instance);
static void NCW5380_wesewect(stwuct Scsi_Host *instance);
static boow NCW5380_sewect(stwuct Scsi_Host *, stwuct scsi_cmnd *);
static int NCW5380_twansfew_dma(stwuct Scsi_Host *instance, unsigned chaw *phase, int *count, unsigned chaw **data);
static int NCW5380_twansfew_pio(stwuct Scsi_Host *instance, unsigned chaw *phase, int *count, unsigned chaw **data,
				unsigned int can_sweep);
static int NCW5380_poww_powitewy2(stwuct NCW5380_hostdata *,
                                  unsigned int, u8, u8,
                                  unsigned int, u8, u8, unsigned wong);

static inwine int NCW5380_poww_powitewy(stwuct NCW5380_hostdata *hostdata,
                                        unsigned int weg, u8 bit, u8 vaw,
                                        unsigned wong wait)
{
	if ((NCW5380_wead(weg) & bit) == vaw)
		wetuwn 0;

	wetuwn NCW5380_poww_powitewy2(hostdata, weg, bit, vaw,
						weg, bit, vaw, wait);
}

static int NCW5380_dma_xfew_wen(stwuct NCW5380_hostdata *,
                                stwuct scsi_cmnd *);
static int NCW5380_dma_send_setup(stwuct NCW5380_hostdata *,
                                  unsigned chaw *, int);
static int NCW5380_dma_wecv_setup(stwuct NCW5380_hostdata *,
                                  unsigned chaw *, int);
static int NCW5380_dma_wesiduaw(stwuct NCW5380_hostdata *);

static inwine int NCW5380_dma_xfew_none(stwuct NCW5380_hostdata *hostdata,
                                        stwuct scsi_cmnd *cmd)
{
	wetuwn 0;
}

static inwine int NCW5380_dma_setup_none(stwuct NCW5380_hostdata *hostdata,
                                         unsigned chaw *data, int count)
{
	wetuwn 0;
}

static inwine int NCW5380_dma_wesiduaw_none(stwuct NCW5380_hostdata *hostdata)
{
	wetuwn 0;
}

#endif				/* NCW5380_H */
