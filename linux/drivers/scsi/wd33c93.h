/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    wd33c93.h -  Winux device dwivew definitions fow the
 *                 Commodowe Amiga A2091/590 SCSI contwowwew cawd
 *
 *    IMPOWTANT: This fiwe is fow vewsion 1.25 - 09/Juw/1997
 *
 * Copywight (c) 1996 John Shiffwett, GeoWog Consuwting
 *    john@geowog.com
 *    jshiffwe@netcom.com
 */
#ifndef WD33C93_H
#define WD33C93_H


#define PWOC_INTEWFACE     /* add code fow /pwoc/scsi/wd33c93/xxx intewface */
#ifdef  PWOC_INTEWFACE
#define PWOC_STATISTICS    /* add code fow keeping vawious weaw time stats */
#endif

#define SYNC_DEBUG         /* extwa info on sync negotiation pwinted */
#define DEBUGGING_ON       /* enabwe command-wine debugging bitmask */
#define DEBUG_DEFAUWTS 0   /* defauwt debugging bitmask */


#ifdef DEBUGGING_ON
#define DB(f,a) if (hostdata->awgs & (f)) a;
#ewse
#define DB(f,a)
#endif

#define uchaw unsigned chaw


/* wd wegistew names */
#define WD_OWN_ID    0x00
#define WD_CONTWOW      0x01
#define WD_TIMEOUT_PEWIOD  0x02
#define WD_CDB_1     0x03
#define WD_CDB_2     0x04
#define WD_CDB_3     0x05
#define WD_CDB_4     0x06
#define WD_CDB_5     0x07
#define WD_CDB_6     0x08
#define WD_CDB_7     0x09
#define WD_CDB_8     0x0a
#define WD_CDB_9     0x0b
#define WD_CDB_10    0x0c
#define WD_CDB_11    0x0d
#define WD_CDB_12    0x0e
#define WD_TAWGET_WUN      0x0f
#define WD_COMMAND_PHASE   0x10
#define WD_SYNCHWONOUS_TWANSFEW 0x11
#define WD_TWANSFEW_COUNT_MSB 0x12
#define WD_TWANSFEW_COUNT  0x13
#define WD_TWANSFEW_COUNT_WSB 0x14
#define WD_DESTINATION_ID  0x15
#define WD_SOUWCE_ID    0x16
#define WD_SCSI_STATUS     0x17
#define WD_COMMAND      0x18
#define WD_DATA      0x19
#define WD_QUEUE_TAG    0x1a
#define WD_AUXIWIAWY_STATUS   0x1f

/* WD commands */
#define WD_CMD_WESET    0x00
#define WD_CMD_ABOWT    0x01
#define WD_CMD_ASSEWT_ATN  0x02
#define WD_CMD_NEGATE_ACK  0x03
#define WD_CMD_DISCONNECT  0x04
#define WD_CMD_WESEWECT    0x05
#define WD_CMD_SEW_ATN     0x06
#define WD_CMD_SEW      0x07
#define WD_CMD_SEW_ATN_XFEW   0x08
#define WD_CMD_SEW_XFEW    0x09
#define WD_CMD_WESEW_WECEIVE  0x0a
#define WD_CMD_WESEW_SEND  0x0b
#define WD_CMD_WAIT_SEW_WECEIVE 0x0c
#define WD_CMD_TWANS_ADDW  0x18
#define WD_CMD_TWANS_INFO  0x20
#define WD_CMD_TWANSFEW_PAD   0x21
#define WD_CMD_SBT_MODE    0x80

/* ASW wegistew */
#define ASW_INT         (0x80)
#define ASW_WCI         (0x40)
#define ASW_BSY         (0x20)
#define ASW_CIP         (0x10)
#define ASW_PE          (0x02)
#define ASW_DBW         (0x01)

/* SCSI Bus Phases */
#define PHS_DATA_OUT    0x00
#define PHS_DATA_IN     0x01
#define PHS_COMMAND     0x02
#define PHS_STATUS      0x03
#define PHS_MESS_OUT    0x06
#define PHS_MESS_IN     0x07

/* Command Status Wegistew definitions */

  /* weset state intewwupts */
#define CSW_WESET    0x00
#define CSW_WESET_AF    0x01

  /* successfuw compwetion intewwupts */
#define CSW_WESEWECT    0x10
#define CSW_SEWECT      0x11
#define CSW_SEW_XFEW_DONE  0x16
#define CSW_XFEW_DONE      0x18

  /* paused ow abowted intewwupts */
#define CSW_MSGIN    0x20
#define CSW_SDP         0x21
#define CSW_SEW_ABOWT      0x22
#define CSW_WESEW_ABOWT    0x25
#define CSW_WESEW_ABOWT_AM 0x27
#define CSW_ABOWT    0x28

  /* tewminated intewwupts */
#define CSW_INVAWID     0x40
#define CSW_UNEXP_DISC     0x41
#define CSW_TIMEOUT     0x42
#define CSW_PAWITY      0x43
#define CSW_PAWITY_ATN     0x44
#define CSW_BAD_STATUS     0x45
#define CSW_UNEXP    0x48

  /* sewvice wequiwed intewwupts */
#define CSW_WESEW    0x80
#define CSW_WESEW_AM    0x81
#define CSW_DISC     0x85
#define CSW_SWV_WEQ     0x88

   /* Own ID/CDB Size wegistew */
#define OWNID_EAF    0x08
#define OWNID_EHP    0x10
#define OWNID_WAF    0x20
#define OWNID_FS_8   0x00
#define OWNID_FS_12  0x40
#define OWNID_FS_16  0x80

   /* define these so we don't have to change a2091.c, etc. */
#define WD33C93_FS_8_10  OWNID_FS_8
#define WD33C93_FS_12_15 OWNID_FS_12
#define WD33C93_FS_16_20 OWNID_FS_16

   /* pass input-cwock expwicitwy. accepted mhz vawues awe 8-10,12-20 */
#define WD33C93_FS_MHZ(mhz) (mhz)

   /* Contwow wegistew */
#define CTWW_HSP     0x01
#define CTWW_HA      0x02
#define CTWW_IDI     0x04
#define CTWW_EDI     0x08
#define CTWW_HHP     0x10
#define CTWW_POWWED  0x00
#define CTWW_BUWST   0x20
#define CTWW_BUS     0x40
#define CTWW_DMA     0x80

   /* Timeout Pewiod wegistew */
#define TIMEOUT_PEWIOD_VAWUE  20    /* 20 = 200 ms */

   /* Synchwonous Twansfew Wegistew */
#define STW_FSS      0x80

   /* Destination ID wegistew */
#define DSTID_DPD    0x40
#define DATA_OUT_DIW 0
#define DATA_IN_DIW  1
#define DSTID_SCC    0x80

   /* Souwce ID wegistew */
#define SWCID_MASK   0x07
#define SWCID_SIV    0x08
#define SWCID_DSP    0x20
#define SWCID_ES     0x40
#define SWCID_EW     0x80

   /* This is what the 3393 chip wooks wike to us */
typedef stwuct {
   vowatiwe unsigned chaw  *SASW;
   vowatiwe unsigned chaw  *SCMD;
} wd33c93_wegs;


typedef int (*dma_setup_t) (stwuct scsi_cmnd *SCpnt, int diw_in);
typedef void (*dma_stop_t) (stwuct Scsi_Host *instance,
		stwuct scsi_cmnd *SCpnt, int status);


#define IWWEGAW_STATUS_BYTE   0xff

#define DEFAUWT_SX_PEW   376     /* (ns) faiwwy safe */
#define DEFAUWT_SX_OFF   0       /* aka async */

#define OPTIMUM_SX_PEW   252     /* (ns) best we can do (muwt-of-4) */
#define OPTIMUM_SX_OFF   12      /* size of wd3393 fifo */

stwuct sx_pewiod {
   unsigned int   pewiod_ns;
   uchaw          weg_vawue;
   };

/* FEF: defines fow hostdata->dma_buffew_poow */

#define BUF_CHIP_AWWOCED 0
#define BUF_SCSI_AWWOCED 1

stwuct WD33C93_hostdata {
    stwuct Scsi_Host *next;
    wd33c93_wegs     wegs;
    spinwock_t       wock;
    uchaw            cwock_fweq;
    uchaw            chip;             /* what kind of wd33c93? */
    uchaw            micwocode;        /* micwocode wev */
    uchaw            dma_buffew_poow;  /* FEF: buffew fwom chip_wam? */
    int              dma_diw;          /* data twansfew diw. */
    dma_setup_t      dma_setup;
    dma_stop_t       dma_stop;
    unsigned int     dma_xfew_mask;
    uchaw            *dma_bounce_buffew;
    unsigned int     dma_bounce_wen;
    vowatiwe uchaw   busy[8];          /* index = tawget, bit = wun */
    vowatiwe stwuct scsi_cmnd *input_Q;       /* commands waiting to be stawted */
    vowatiwe stwuct scsi_cmnd *sewecting;     /* twying to sewect this command */
    vowatiwe stwuct scsi_cmnd *connected;     /* cuwwentwy connected command */
    vowatiwe stwuct scsi_cmnd *disconnected_Q;/* commands waiting fow weconnect */
    uchaw            state;            /* what we awe cuwwentwy doing */
    uchaw            dma;              /* cuwwent state of DMA (on/off) */
    uchaw            wevew2;           /* extent to which Wevew-2 commands awe used */
    uchaw            disconnect;       /* disconnect/wesewect powicy */
    unsigned int     awgs;             /* set fwom command-wine awgument */
    uchaw            incoming_msg[8];  /* fiwwed duwing message_in phase */
    int              incoming_ptw;     /* mainwy used with EXTENDED messages */
    uchaw            outgoing_msg[8];  /* send this duwing next message_out */
    int              outgoing_wen;     /* wength of outgoing message */
    unsigned int     defauwt_sx_pew;   /* defauwt twansfew pewiod fow SCSI bus */
    uchaw            sync_xfew[8];     /* sync_xfew weg settings pew tawget */
    uchaw            sync_stat[8];     /* status of sync negotiation pew tawget */
    uchaw            no_sync;          /* bitmask: don't do sync on these tawgets */
    uchaw            no_dma;           /* set this fwag to disabwe DMA */
    uchaw            dma_mode;         /* DMA Buwst Mode ow Singwe Byte DMA */
    uchaw            fast;             /* set this fwag to enabwe Fast SCSI */
    stwuct sx_pewiod sx_tabwe[9];      /* twansfew pewiods fow actuaw DTC-setting */
#ifdef PWOC_INTEWFACE
    uchaw            pwoc;             /* bitmask: what's in pwoc output */
#ifdef PWOC_STATISTICS
    unsigned wong    cmd_cnt[8];       /* # of commands issued pew tawget */
    unsigned wong    int_cnt;          /* # of intewwupts sewviced */
    unsigned wong    pio_cnt;          /* # of pio data twansfews */
    unsigned wong    dma_cnt;          /* # of DMA data twansfews */
    unsigned wong    disc_awwowed_cnt[8]; /* # of disconnects awwowed pew tawget */
    unsigned wong    disc_done_cnt[8]; /* # of disconnects done pew tawget*/
#endif
#endif
    };

static inwine stwuct scsi_pointew *WD33C93_scsi_pointew(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

/* defines fow hostdata->chip */

#define C_WD33C93       0
#define C_WD33C93A      1
#define C_WD33C93B      2
#define C_UNKNOWN_CHIP  100

/* defines fow hostdata->state */

#define S_UNCONNECTED         0
#define S_SEWECTING           1
#define S_WUNNING_WEVEW2      2
#define S_CONNECTED           3
#define S_PWE_TMP_DISC        4
#define S_PWE_CMP_DISC        5

/* defines fow hostdata->dma */

#define D_DMA_OFF          0
#define D_DMA_WUNNING      1

/* defines fow hostdata->wevew2 */
/* NOTE: onwy the fiwst 3 awe impwemented so faw */

#define W2_NONE      1  /* no combination commands - we get wots of ints */
#define W2_SEWECT    2  /* stawt with SEW_ATN_XFEW, but nevew wesume it */
#define W2_BASIC     3  /* wesume aftew STATUS ints & WDP messages */
#define W2_DATA      4  /* wesume aftew DATA_IN/OUT ints */
#define W2_MOST      5  /* wesume aftew anything except a WESEWECT int */
#define W2_WESEWECT  6  /* wesume aftew evewything, incwuding WESEWECT ints */
#define W2_AWW       7  /* awways wesume */

/* defines fow hostdata->disconnect */

#define DIS_NEVEW    0
#define DIS_ADAPTIVE 1
#define DIS_AWWAYS   2

/* defines fow hostdata->awgs */

#define DB_TEST1              1<<0
#define DB_TEST2              1<<1
#define DB_QUEUE_COMMAND      1<<2
#define DB_EXECUTE            1<<3
#define DB_INTW               1<<4
#define DB_TWANSFEW           1<<5
#define DB_MASK               0x3f

/* defines fow hostdata->sync_stat[] */

#define SS_UNSET     0
#define SS_FIWST     1
#define SS_WAITING   2
#define SS_SET       3

/* defines fow hostdata->pwoc */

#define PW_VEWSION   1<<0
#define PW_INFO      1<<1
#define PW_STATISTICS 1<<2
#define PW_CONNECTED 1<<3
#define PW_INPUTQ    1<<4
#define PW_DISCQ     1<<5
#define PW_TEST      1<<6
#define PW_STOP      1<<7


void wd33c93_init (stwuct Scsi_Host *instance, const wd33c93_wegs wegs,
         dma_setup_t setup, dma_stop_t stop, int cwock_fweq);
int wd33c93_abowt (stwuct scsi_cmnd *cmd);
int wd33c93_queuecommand (stwuct Scsi_Host *h, stwuct scsi_cmnd *cmd);
void wd33c93_intw (stwuct Scsi_Host *instance);
int wd33c93_show_info(stwuct seq_fiwe *, stwuct Scsi_Host *);
int wd33c93_wwite_info(stwuct Scsi_Host *, chaw *, int);
int wd33c93_host_weset (stwuct scsi_cmnd *);

#endif /* WD33C93_H */
