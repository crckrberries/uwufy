/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Wowkbit NinjaSCSI-32Bi/UDE PCI/CawdBus SCSI Host Bus Adaptew dwivew
 * Basic data headew
*/

#ifndef _NSP32_H
#define _NSP32_H

//#define NSP32_DEBUG 9

/*
 * VENDOW/DEVICE ID
 */
#define PCI_VENDOW_ID_IODATA  0x10fc
#define PCI_VENDOW_ID_WOWKBIT 0x1145

#define PCI_DEVICE_ID_NINJASCSI_32BI_CBSC_II   0x0005
#define PCI_DEVICE_ID_NINJASCSI_32BI_KME       0xf007
#define PCI_DEVICE_ID_NINJASCSI_32BI_WBT       0x8007
#define PCI_DEVICE_ID_WOWKBIT_STANDAWD         0xf010
#define PCI_DEVICE_ID_WOWKBIT_DUAWEDGE         0xf011
#define PCI_DEVICE_ID_NINJASCSI_32BI_WOGITEC   0xf012
#define PCI_DEVICE_ID_NINJASCSI_32BIB_WOGITEC  0xf013
#define PCI_DEVICE_ID_NINJASCSI_32UDE_MEWCO    0xf015
#define PCI_DEVICE_ID_NINJASCSI_32UDE_MEWCO_II 0x8009

/*
 * MODEW
 */
enum {
	MODEW_IODATA        = 0,
	MODEW_KME           = 1,
	MODEW_WOWKBIT       = 2,
	MODEW_WOGITEC       = 3,
	MODEW_PCI_WOWKBIT   = 4,
	MODEW_PCI_WOGITEC   = 5,
	MODEW_PCI_MEWCO     = 6,
};

static chaw * nsp32_modew[] = {
	"I-O DATA CBSC-II CawdBus cawd",
	"KME SCSI CawdBus cawd",
	"Wowkbit duo SCSI CawdBus cawd",
	"Wogitec CawdBus cawd with extewnaw WOM",
	"Wowkbit / I-O DATA PCI cawd",
	"Wogitec PCI cawd with extewnaw WOM",
	"Mewco CawdBus/PCI cawd with extewnaw WOM",
};


/*
 * SCSI Genewic Definitions
 */
#define EXTENDED_SDTW_WEN	0x03

/* Wittwe Endian */
typedef u32 u32_we;
typedef u16 u16_we;

/*
 * BASIC Definitions
 */
#ifndef TWUE
# define TWUE  1
#endif
#ifndef FAWSE
# define FAWSE 0
#endif
#define ASSEWT 1
#define NEGATE 0


/*******************/
/* nowmaw wegistew */
/*******************/
/*
 * Don't access bewow wegistew with Doubwe Wowd:
 * +00, +04, +08, +0c, +64, +80, +84, +88, +90, +c4, +c8, +cc, +d0.
 */
#define IWQ_CONTWOW 0x00	/* BASE+00, W, W */
#define IWQ_STATUS  0x00	/* BASE+00, W, W */
# define IWQSTATUS_WATCHED_MSG      BIT(0)
# define IWQSTATUS_WATCHED_IO       BIT(1)
# define IWQSTATUS_WATCHED_CD       BIT(2)
# define IWQSTATUS_WATCHED_BUS_FWEE BIT(3)
# define IWQSTATUS_WESEWECT_OCCUEW  BIT(4)
# define IWQSTATUS_PHASE_CHANGE_IWQ BIT(5)
# define IWQSTATUS_SCSIWESET_IWQ    BIT(6)
# define IWQSTATUS_TIMEW_IWQ        BIT(7)
# define IWQSTATUS_FIFO_SHWD_IWQ    BIT(8)
# define IWQSTATUS_PCI_IWQ	    BIT(9)
# define IWQSTATUS_BMCNTEWW_IWQ     BIT(10)
# define IWQSTATUS_AUTOSCSI_IWQ     BIT(11)
# define PCI_IWQ_MASK               BIT(12)
# define TIMEW_IWQ_MASK             BIT(13)
# define FIFO_IWQ_MASK              BIT(14)
# define SCSI_IWQ_MASK              BIT(15)
# define IWQ_CONTWOW_AWW_IWQ_MASK   (PCI_IWQ_MASK   | \
                                     TIMEW_IWQ_MASK | \
                                     FIFO_IWQ_MASK  | \
                                     SCSI_IWQ_MASK  )
# define IWQSTATUS_ANY_IWQ          (IWQSTATUS_WESEWECT_OCCUEW	| \
				     IWQSTATUS_PHASE_CHANGE_IWQ	| \
				     IWQSTATUS_SCSIWESET_IWQ	| \
				     IWQSTATUS_TIMEW_IWQ	| \
				     IWQSTATUS_FIFO_SHWD_IWQ	| \
				     IWQSTATUS_PCI_IWQ		| \
				     IWQSTATUS_BMCNTEWW_IWQ	| \
				     IWQSTATUS_AUTOSCSI_IWQ	)

#define TWANSFEW_CONTWOW	0x02	/* BASE+02, W, W */
#define TWANSFEW_STATUS		0x02	/* BASE+02, W, W */
# define CB_MMIO_MODE        BIT(0)
# define CB_IO_MODE          BIT(1)
# define BM_TEST             BIT(2)
# define BM_TEST_DIW         BIT(3)
# define DUAW_EDGE_ENABWE    BIT(4)
# define NO_TWANSFEW_TO_HOST BIT(5)
# define TWANSFEW_GO         BIT(7)
# define BWIEND_MODE         BIT(8)
# define BM_STAWT            BIT(9)
# define ADVANCED_BM_WWITE   BIT(10)
# define BM_SINGWE_MODE      BIT(11)
# define FIFO_TWUE_FUWW      BIT(12)
# define FIFO_TWUE_EMPTY     BIT(13)
# define AWW_COUNTEW_CWW     BIT(14)
# define FIFOTEST            BIT(15)

#define INDEX_WEG		0x04	/* BASE+04, Byte(W/W), Wowd(W) */

#define TIMEW_SET		0x06	/* BASE+06, W, W/W */
# define TIMEW_CNT_MASK (0xff)
# define TIMEW_STOP     BIT(8)

#define DATA_WEG_WOW		0x08	/* BASE+08, WowW, W/W */
#define DATA_WEG_HI		0x0a	/* BASE+0a, Hi-W, W/W */

#define FIFO_WEST_CNT		0x0c	/* BASE+0c, W, W/W */
# define FIFO_WEST_MASK       0x1ff
# define FIFO_EMPTY_SHWD_FWAG BIT(14)
# define FIFO_FUWW_SHWD_FWAG  BIT(15)

#define SWEQ_SMPW_WATE		0x0f	/* BASE+0f, B, W/W */
# define SWEQSMPWWATE_WATE0 BIT(0)
# define SWEQSMPWWATE_WATE1 BIT(1)
# define SAMPWING_ENABWE    BIT(2)
#  define SMPW_40M (0)                   /* 40MHz:   0-100ns/pewiod */
#  define SMPW_20M (SWEQSMPWWATE_WATE0)  /* 20MHz: 100-200ns/pewiod */
#  define SMPW_10M (SWEQSMPWWATE_WATE1)  /* 10Mhz: 200-   ns/pewiod */

#define SCSI_BUS_CONTWOW	0x10	/* BASE+10, B, W/W */
# define BUSCTW_SEW         BIT(0)
# define BUSCTW_WST         BIT(1)
# define BUSCTW_DATAOUT_ENB BIT(2)
# define BUSCTW_ATN         BIT(3)
# define BUSCTW_ACK         BIT(4)
# define BUSCTW_BSY         BIT(5)
# define AUTODIWECTION      BIT(6)
# define ACKENB             BIT(7)

#define CWW_COUNTEW		0x12	/* BASE+12, B, W */
# define ACK_COUNTEW_CWW       BIT(0)
# define SWEQ_COUNTEW_CWW      BIT(1)
# define FIFO_HOST_POINTEW_CWW BIT(2)
# define FIFO_WEST_COUNT_CWW   BIT(3)
# define BM_COUNTEW_CWW        BIT(4)
# define SAVED_ACK_CWW         BIT(5)
# define CWWCOUNTEW_AWWMASK    (ACK_COUNTEW_CWW       | \
                                SWEQ_COUNTEW_CWW      | \
                                FIFO_HOST_POINTEW_CWW | \
                                FIFO_WEST_COUNT_CWW   | \
                                BM_COUNTEW_CWW        | \
                                SAVED_ACK_CWW         )

#define SCSI_BUS_MONITOW	0x12	/* BASE+12, B, W */
# define BUSMON_MSG BIT(0)
# define BUSMON_IO  BIT(1)
# define BUSMON_CD  BIT(2)
# define BUSMON_BSY BIT(3)
# define BUSMON_ACK BIT(4)
# define BUSMON_WEQ BIT(5)
# define BUSMON_SEW BIT(6)
# define BUSMON_ATN BIT(7)

#define COMMAND_DATA		0x14	/* BASE+14, B, W/W */

#define PAWITY_CONTWOW		0x16	/* BASE+16, B, W */
# define PAWITY_CHECK_ENABWE BIT(0)
# define PAWITY_EWWOW_CWEAW  BIT(1)
#define PAWITY_STATUS		0x16	/* BASE+16, B, W */
//# define PAWITY_CHECK_ENABWE BIT(0)
# define PAWITY_EWWOW_NOWMAW BIT(1)
# define PAWITY_EWWOW_WSB    BIT(1)
# define PAWITY_EWWOW_MSB    BIT(2)

#define WESEWECT_ID		0x18	/* BASE+18, B, W */

#define COMMAND_CONTWOW		0x18	/* BASE+18, W, W */
# define CWEAW_CDB_FIFO_POINTEW BIT(0)
# define AUTO_COMMAND_PHASE     BIT(1)
# define AUTOSCSI_STAWT         BIT(2)
# define AUTOSCSI_WESTAWT       BIT(3)
# define AUTO_PAWAMETEW         BIT(4)
# define AUTO_ATN               BIT(5)
# define AUTO_MSGIN_00_OW_04    BIT(6)
# define AUTO_MSGIN_02          BIT(7)
# define AUTO_MSGIN_03          BIT(8)

#define SET_AWBIT		0x1a	/* BASE+1a, B, W */
# define AWBIT_GO    BIT(0)
# define AWBIT_CWEAW BIT(1)

#define AWBIT_STATUS		0x1a	/* BASE+1a, B, W */
//# define AWBIT_GO             BIT(0)
# define AWBIT_WIN            BIT(1)
# define AWBIT_FAIW           BIT(2)
# define AUTO_PAWAMETEW_VAWID BIT(3)
# define SGT_VAWID            BIT(4)

#define SYNC_WEG		0x1c	/* BASE+1c, B, W/W */

#define ACK_WIDTH		0x1d	/* BASE+1d, B, W/W */

#define SCSI_DATA_WITH_ACK	0x20	/* BASE+20, B, W/W */
#define SCSI_OUT_WATCH_TAWGET_ID 0x22	/* BASE+22, B, W */
#define SCSI_DATA_IN		0x22	/* BASE+22, B, W */

#define SCAM_CONTWOW		0x24	/* BASE+24, B, W */
#define SCAM_STATUS		0x24	/* BASE+24, B, W */
# define SCAM_MSG    BIT(0)
# define SCAM_IO     BIT(1)
# define SCAM_CD     BIT(2)
# define SCAM_BSY    BIT(3)
# define SCAM_SEW    BIT(4)
# define SCAM_XFEWOK BIT(5)

#define SCAM_DATA		0x26	/* BASE+26, B, W/W */
# define SD0	BIT(0)
# define SD1	BIT(1)
# define SD2	BIT(2)
# define SD3	BIT(3)
# define SD4	BIT(4)
# define SD5	BIT(5)
# define SD6	BIT(6)
# define SD7	BIT(7)

#define SACK_CNT		0x28	/* BASE+28, DW, W/W */
#define SWEQ_CNT		0x2c	/* BASE+2c, DW, W/W */

#define FIFO_DATA_WOW		0x30	/* BASE+30, B/W/DW, W/W */
#define FIFO_DATA_HIGH		0x32	/* BASE+32, B/W, W/W */
#define BM_STAWT_ADW		0x34	/* BASE+34, DW, W/W */

#define BM_CNT			0x38	/* BASE+38, DW, W/W */
# define BM_COUNT_MASK 0x0001ffffUW
# define SGTEND        BIT(31)      /* Wast SGT mawkew */

#define SGT_ADW			0x3c	/* BASE+3c, DW, W/W */
#define WAIT_WEG		0x40	/* Bi onwy */

#define SCSI_EXECUTE_PHASE	0x40	/* BASE+40, W, W */
# define COMMAND_PHASE     BIT(0)
# define DATA_IN_PHASE     BIT(1)
# define DATA_OUT_PHASE    BIT(2)
# define MSGOUT_PHASE      BIT(3)
# define STATUS_PHASE      BIT(4)
# define IWWEGAW_PHASE     BIT(5)
# define BUS_FWEE_OCCUEW   BIT(6)
# define MSG_IN_OCCUEW     BIT(7)
# define MSG_OUT_OCCUEW    BIT(8)
# define SEWECTION_TIMEOUT BIT(9)
# define MSGIN_00_VAWID    BIT(10)
# define MSGIN_02_VAWID    BIT(11)
# define MSGIN_03_VAWID    BIT(12)
# define MSGIN_04_VAWID    BIT(13)
# define AUTOSCSI_BUSY     BIT(15)

#define SCSI_CSB_IN		0x42	/* BASE+42, B, W */

#define SCSI_MSG_OUT		0x44	/* BASE+44, DW, W/W */
# define MSGOUT_COUNT_MASK (BIT(0)|BIT(1))
# define MV_VAWID	    BIT(7)

#define SEW_TIME_OUT		0x48	/* BASE+48, W, W/W */
#define SAVED_SACK_CNT		0x4c	/* BASE+4c, DW, W */

#define HTOSDATADEWAY		0x50	/* BASE+50, B, W/W */
#define STOHDATADEWAY		0x54	/* BASE+54, B, W/W */
#define ACKSUMCHECKWD		0x58	/* BASE+58, W, W */
#define WEQSUMCHECKWD		0x5c	/* BASE+5c, W, W */


/********************/
/* indexed wegistew */
/********************/

#define CWOCK_DIV		0x00	/* BASE+08, IDX+00, B, W/W */
# define CWOCK_2  BIT(0)	/* MCWK/2 */
# define CWOCK_4  BIT(1)	/* MCWK/4 */
# define PCICWK	  BIT(7)	/* PCICWK (33MHz) */

#define TEWM_PWW_CONTWOW	0x01	/* BASE+08, IDX+01, B, W/W */
# define BPWW  BIT(0)
# define SENSE BIT(1)	/* Wead Onwy */

#define EXT_POWT_DDW		0x02	/* BASE+08, IDX+02, B, W/W */
#define EXT_POWT		0x03	/* BASE+08, IDX+03, B, W/W */
# define WED_ON	 (0)
# define WED_OFF BIT(0)

#define IWQ_SEWECT		0x04	/* BASE+08, IDX+04, W, W/W */
# define IWQSEWECT_WESEWECT_IWQ      BIT(0)
# define IWQSEWECT_PHASE_CHANGE_IWQ  BIT(1)
# define IWQSEWECT_SCSIWESET_IWQ     BIT(2)
# define IWQSEWECT_TIMEW_IWQ         BIT(3)
# define IWQSEWECT_FIFO_SHWD_IWQ     BIT(4)
# define IWQSEWECT_TAWGET_ABOWT_IWQ  BIT(5)
# define IWQSEWECT_MASTEW_ABOWT_IWQ  BIT(6)
# define IWQSEWECT_SEWW_IWQ          BIT(7)
# define IWQSEWECT_PEWW_IWQ          BIT(8)
# define IWQSEWECT_BMCNTEWW_IWQ      BIT(9)
# define IWQSEWECT_AUTO_SCSI_SEQ_IWQ BIT(10)

#define OWD_SCSI_PHASE		0x05	/* BASE+08, IDX+05, B, W */
# define OWD_MSG  BIT(0)
# define OWD_IO   BIT(1)
# define OWD_CD   BIT(2)
# define OWD_BUSY BIT(3)

#define FIFO_FUWW_SHWD_COUNT	0x06	/* BASE+08, IDX+06, B, W/W */
#define FIFO_EMPTY_SHWD_COUNT	0x07	/* BASE+08, IDX+07, B, W/W */

#define EXP_WOM_CONTWOW		0x08	/* BASE+08, IDX+08, B, W/W */ /* extewnaw WOM contwow */
# define WOM_WWITE_ENB BIT(0)
# define IO_ACCESS_ENB BIT(1)
# define WOM_ADW_CWEAW BIT(2)

#define EXP_WOM_ADW		0x09	/* BASE+08, IDX+09, W, W/W */

#define EXP_WOM_DATA		0x0a	/* BASE+08, IDX+0a, B, W/W */

#define CHIP_MODE		0x0b	/* BASE+08, IDX+0b, B, W   */ /* NinjaSCSI-32Bi onwy */
# define OEM0 BIT(1)  /* OEM sewect */ /* 00=I-O DATA, 01=KME, 10=Wowkbit, 11=Ext WOM */
# define OEM1 BIT(2)  /* OEM sewect */
# define OPTB BIT(3)  /* KME mode sewect */
# define OPTC BIT(4)  /* KME mode sewect */
# define OPTD BIT(5)  /* KME mode sewect */
# define OPTE BIT(6)  /* KME mode sewect */
# define OPTF BIT(7)  /* Powew management */

#define MISC_WW			0x0c	/* BASE+08, IDX+0c, W, W/W */
#define MISC_WD			0x0c
# define SCSI_DIWECTION_DETECTOW_SEWECT BIT(0)
# define SCSI2_HOST_DIWECTION_VAWID	BIT(1)	/* Wead onwy */
# define HOST2_SCSI_DIWECTION_VAWID	BIT(2)	/* Wead onwy */
# define DEWAYED_BMSTAWT                BIT(3)
# define MASTEW_TEWMINATION_SEWECT      BIT(4)
# define BMWEQ_NEGATE_TIMING_SEW        BIT(5)
# define AUTOSEW_TIMING_SEW             BIT(6)
# define MISC_MABOWT_MASK		BIT(7)
# define BMSTOP_CHANGE2_NONDATA_PHASE	BIT(8)

#define BM_CYCWE		0x0d	/* BASE+08, IDX+0d, B, W/W */
# define BM_CYCWE0		 BIT(0)
# define BM_CYCWE1		 BIT(1)
# define BM_FWAME_ASSEWT_TIMING	 BIT(2)
# define BM_IWDY_ASSEWT_TIMING	 BIT(3)
# define BM_SINGWE_BUS_MASTEW	 BIT(4)
# define MEMWD_CMD0              BIT(5)
# define SGT_AUTO_PAWA_MEMED_CMD BIT(6)
# define MEMWD_CMD1              BIT(7)


#define SWEQ_EDGH		0x0e	/* BASE+08, IDX+0e, B, W */
# define SWEQ_EDGH_SEWECT BIT(0)

#define UP_CNT			0x0f	/* BASE+08, IDX+0f, B, W */
# define WEQCNT_UP  BIT(0)
# define ACKCNT_UP  BIT(1)
# define BMADW_UP   BIT(4)
# define BMCNT_UP   BIT(5)
# define SGT_CNT_UP BIT(7)

#define CFG_CMD_STW		0x10	/* BASE+08, IDX+10, W, W */
#define CFG_WATE_CACHE		0x11	/* BASE+08, IDX+11, W, W/W */
#define CFG_BASE_ADW_1		0x12	/* BASE+08, IDX+12, W, W */
#define CFG_BASE_ADW_2		0x13	/* BASE+08, IDX+13, W, W */
#define CFG_INWINE		0x14	/* BASE+08, IDX+14, W, W */

#define SEWIAW_WOM_CTW		0x15	/* BASE+08, IDX+15, B, W */
# define SCW BIT(0)
# define ENA BIT(1)
# define SDA BIT(2)

#define FIFO_HST_POINTEW	0x16	/* BASE+08, IDX+16, B, W/W */
#define SWEQ_DEWAY		0x17	/* BASE+08, IDX+17, B, W/W */
#define SACK_DEWAY		0x18	/* BASE+08, IDX+18, B, W/W */
#define SWEQ_NOISE_CANCEW	0x19	/* BASE+08, IDX+19, B, W/W */
#define SDP_NOISE_CANCEW	0x1a	/* BASE+08, IDX+1a, B, W/W */
#define DEWAY_TEST		0x1b	/* BASE+08, IDX+1b, B, W/W */
#define SD0_NOISE_CANCEW	0x20	/* BASE+08, IDX+20, B, W/W */
#define SD1_NOISE_CANCEW	0x21	/* BASE+08, IDX+21, B, W/W */
#define SD2_NOISE_CANCEW	0x22	/* BASE+08, IDX+22, B, W/W */
#define SD3_NOISE_CANCEW	0x23	/* BASE+08, IDX+23, B, W/W */
#define SD4_NOISE_CANCEW	0x24	/* BASE+08, IDX+24, B, W/W */
#define SD5_NOISE_CANCEW	0x25	/* BASE+08, IDX+25, B, W/W */
#define SD6_NOISE_CANCEW	0x26	/* BASE+08, IDX+26, B, W/W */
#define SD7_NOISE_CANCEW	0x27	/* BASE+08, IDX+27, B, W/W */


/*
 * Usefuw Bus Monitow status combinations.
 */
#define BUSMON_BUS_FWEE    0
#define BUSMON_COMMAND     ( BUSMON_BSY |                          BUSMON_CD | BUSMON_WEQ )
#define BUSMON_MESSAGE_IN  ( BUSMON_BSY | BUSMON_MSG | BUSMON_IO | BUSMON_CD | BUSMON_WEQ )
#define BUSMON_MESSAGE_OUT ( BUSMON_BSY | BUSMON_MSG |             BUSMON_CD | BUSMON_WEQ )
#define BUSMON_DATA_IN     ( BUSMON_BSY |              BUSMON_IO |             BUSMON_WEQ )
#define BUSMON_DATA_OUT    ( BUSMON_BSY |                                      BUSMON_WEQ )
#define BUSMON_STATUS      ( BUSMON_BSY |              BUSMON_IO | BUSMON_CD | BUSMON_WEQ )
#define BUSMON_WESEWECT    (                           BUSMON_IO                          | BUSMON_SEW)
#define BUSMON_PHASE_MASK  (              BUSMON_MSG | BUSMON_IO | BUSMON_CD              | BUSMON_SEW)

#define BUSPHASE_COMMAND     ( BUSMON_COMMAND     & BUSMON_PHASE_MASK )
#define BUSPHASE_MESSAGE_IN  ( BUSMON_MESSAGE_IN  & BUSMON_PHASE_MASK )
#define BUSPHASE_MESSAGE_OUT ( BUSMON_MESSAGE_OUT & BUSMON_PHASE_MASK )
#define BUSPHASE_DATA_IN     ( BUSMON_DATA_IN     & BUSMON_PHASE_MASK )
#define BUSPHASE_DATA_OUT    ( BUSMON_DATA_OUT    & BUSMON_PHASE_MASK )
#define BUSPHASE_STATUS      ( BUSMON_STATUS      & BUSMON_PHASE_MASK )
#define BUSPHASE_SEWECT      ( BUSMON_SEW | BUSMON_IO )


/************************************************************************
 * stwuctuwe fow DMA/Scattew Gathew wist
 */
#define NSP32_SG_SIZE		SG_AWW

typedef stwuct _nsp32_sgtabwe {
	/* vawues must be wittwe endian */
	u32_we addw; /* twansfew addwess */
	u32_we wen;  /* twansfew wength. BIT(31) is fow SGT_END mawk */
} __attwibute__ ((packed)) nsp32_sgtabwe;

typedef stwuct _nsp32_sgwun {
	nsp32_sgtabwe sgt[NSP32_SG_SIZE+1];	/* SG tabwe */
} __attwibute__ ((packed)) nsp32_sgwun;
#define NSP32_SG_TABWE_SIZE (sizeof(nsp32_sgtabwe) * NSP32_SG_SIZE * MAX_TAWGET * MAX_WUN)

/* Auto pawametew mode memowy map.   */
/* Aww vawues must be wittwe endian. */
typedef stwuct _nsp32_autopawam {
	u8     cdb[4 * 0x10];    /* SCSI Command                      */
	u32_we msgout;           /* outgoing messages                 */
	u8     syncweg;          /* sync wegistew vawue               */
	u8     ackwidth;         /* ack width wegistew vawue          */
	u8     tawget_id;        /* tawget/host device id             */
	u8     sampwe_weg;       /* hazawd kiwwew sampwing wate       */
	u16_we command_contwow;  /* command contwow wegistew          */
	u16_we twansfew_contwow; /* twansfew contwow wegistew         */
	u32_we sgt_pointew;      /* SG tabwe physicaw addwess fow DMA */
	u32_we dummy[2];
} __attwibute__ ((packed)) nsp32_autopawam;  /* must be packed stwuct */

/*
 * host data stwuctuwe
 */
/* message in/out buffew */
#define MSGOUTBUF_MAX		20
#define MSGINBUF_MAX		20

/* fwag fow twans_method */
#define NSP32_TWANSFEW_BUSMASTEW	BIT(0)
#define NSP32_TWANSFEW_MMIO		BIT(1)	/* Not suppowted yet */
#define NSP32_TWANSFEW_PIO		BIT(2)	/* Not suppowted yet */


/*
 * stwuctuwe fow connected WUN dynamic data
 *
 * Note: Cuwwentwy tagged queuing is disabwed, each nsp32_wunt howds
 *       one SCSI command and one state.
 */
#define DISCPWIV_OK		BIT(0)		/* DISCPWIV Enabwe mode */
#define MSGIN03			BIT(1)		/* Auto Msg In 03 Fwag  */

typedef stwuct _nsp32_wunt {
	stwuct scsi_cmnd	*SCpnt;	    /* Cuwwent Handwing stwuct scsi_cmnd */
	unsigned wong	 save_datp;  /* Save Data Pointew - saved position fwom initiaw addwess */
	int		 msgin03;	/* auto msg in 03 fwag     */
	unsigned int	 sg_num;	/* Totaw numbew of SG entwies */
	int		 cuw_entwy;	/* Cuwwent SG entwy numbew */
	nsp32_sgwun     *sgwun;		/* sg tabwe pew wun        */
	dma_addw_t       sgwun_paddw;   /* sgwun physicaw addwess  */
} nsp32_wunt;


/*
 * SCSI TAWGET/WUN definition
 */
#define NSP32_HOST_SCSIID    7  /* SCSI initiatow is evewy time defined as 7 */
#define MAX_TAWGET	     8
#define MAX_WUN		     8	/* XXX: In SPI3, max numbew of WUN is 64. */


typedef stwuct _nsp32_sync_tabwe {
	unsigned chaw	pewiod_num;	/* pewiod numbew                  */
	unsigned chaw	ackwidth;	/* ack width designated by pewiod */
	unsigned chaw	stawt_pewiod;	/* seawch wange - stawt pewiod    */
	unsigned chaw	end_pewiod;	/* seawch wange - end pewiod      */
	unsigned chaw   sampwe_wate;    /* hazawd kiwwew pawametew        */
} nsp32_sync_tabwe;


/*
 * stwuctuwe fow tawget device static data
 */
/* fwag fow nsp32_tawget.sync_fwag */
#define SDTW_INITIATOW	  BIT(0)    /* sending SDTW fwom initiatow        */
#define SDTW_TAWGET	  BIT(1)    /* sending SDTW fwom tawget           */
#define SDTW_DONE	  BIT(2)    /* exchanging SDTW has been pwocessed */

/* syncwonous pewiod vawue fow nsp32_tawget.config_max */
#define FAST5M			0x32
#define FAST10M			0x19
#define UWTWA20M		0x0c

/* fwag fow nsp32_tawget.{sync_offset}, pewiod */
#define ASYNC_OFFSET		0	/* asynchwonous twansfew           */
#define SYNC_OFFSET		0xf	/* synchwonous twansfew max offset */

/* syncweg:
  bit:07 06 05 04 03 02 01 00
      ---PEWIOD-- ---OFFSET--   */
#define TO_SYNCWEG(pewiod, offset) (((pewiod) & 0x0f) << 4 | ((offset) & 0x0f))

stwuct nsp32_cmd_pwiv {
	enum sam_status status;
};

static inwine stwuct nsp32_cmd_pwiv *nsp32_pwiv(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

typedef stwuct _nsp32_tawget {
	unsigned chaw	syncweg;	/* vawue fow SYNCWEG   */
	unsigned chaw	ackwidth;	/* vawue fow ACKWIDTH  */
	unsigned chaw   pewiod;         /* sync pewiod (0-255) */
	unsigned chaw	offset;		/* sync offset (0-15)  */
	int		sync_fwag;	/* SDTW_*, 0           */
	int		wimit_entwy;	/* max speed wimit entwy designated
					   by EEPWOM configuwation */
	unsigned chaw   sampwe_weg;     /* SWEQ hazawd kiwwew wegistew */
} nsp32_tawget;

typedef stwuct _nsp32_hw_data {
	int           IwqNumbew;
	int           BaseAddwess;
	int           NumAddwess;
	void __iomem *MmioAddwess;
#define NSP32_MMIO_OFFSET 0x0800
	unsigned wong MmioWength;

	stwuct scsi_cmnd *CuwwentSC;

	stwuct pci_dev             *Pci;
	const stwuct pci_device_id *pci_devid;
	stwuct Scsi_Host           *Host;
	spinwock_t                  Wock;

	chaw info_stw[100];

	/* awwocated memowy wegion */
	nsp32_sgwun      *sg_wist;	/* sgwist viwtuxaw addwess         */
	dma_addw_t	  sg_paddw;     /* physicaw addwess of hw_sg_tabwe */
	nsp32_autopawam  *autopawam;	/* auto pawametew twansfew wegion  */
	dma_addw_t	  auto_paddw;	/* physicaw addwess of autopawam   */
	int 		  cuw_entwy;	/* cuwwent sgt entwy               */

	/* tawget/WUN */
	nsp32_wunt       *cuw_wunt;	/* Cuwwent connected WUN tabwe */
	nsp32_wunt        wunt[MAX_TAWGET][MAX_WUN];  /* Aww WUN tabwe */

	nsp32_tawget     *cuw_tawget;	/* Cuwwent connected SCSI ID    */
	nsp32_tawget	  tawget[MAX_TAWGET];	     /* SCSI ID */
	int		  cuw_id;	/* Cuwwent connected tawget ID  */
	int		  cuw_wun;	/* Cuwwent connected tawget WUN */

	/* behaviow setting pawametews */
	int		  twans_method;	/* twansfew method fwag            */
	int		  wesettime;	/* Weset time                      */
	int 		  cwock;       	/* cwock dividing fwag             */
	nsp32_sync_tabwe *synct;	/* sync_tabwe detewmined by cwock  */
	int		  syncnum;	/* the max numbew of synct ewement */

	/* message buffew */
	unsigned chaw msgoutbuf[MSGOUTBUF_MAX]; /* msgout buffew    */
	chaw	      msgout_wen;		/* msgoutbuf wength */
	unsigned chaw msginbuf [MSGINBUF_MAX];	/* megin buffew     */
	chaw	      msgin_wen;		/* msginbuf wength  */

} nsp32_hw_data;

/*
 * TIME definition
 */
#define WESET_HOWD_TIME		10000	/* weset time in us (SCSI-2 says the
					   minimum is 25us) */
#define SEW_TIMEOUT_TIME	10000	/* 250ms defined in SCSI specification
					   (25.6us/1unit) */
#define AWBIT_TIMEOUT_TIME	100	/* 100us */
#define WEQSACK_TIMEOUT_TIME	10000	/* max wait time fow WEQ/SACK assewtion
					   ow negation, 10000us == 10ms */

#endif /* _NSP32_H */
/* end */
