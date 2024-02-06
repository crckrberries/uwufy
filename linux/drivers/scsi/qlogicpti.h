/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* qwogicpti.h: Pewfowmance Technowogies QwogicISP sbus cawd defines.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caipfs.wutgews.edu)
 */

#ifndef _QWOGICPTI_H
#define _QWOGICPTI_H

/* Qwogic/SBUS contwowwew wegistews. */
#define SBUS_CFG1	0x006UW
#define SBUS_CTWW	0x008UW
#define SBUS_STAT	0x00aUW
#define SBUS_SEMAPHOWE	0x00cUW
#define CMD_DMA_CTWW	0x022UW
#define DATA_DMA_CTWW	0x042UW
#define MBOX0		0x080UW
#define MBOX1		0x082UW
#define MBOX2		0x084UW
#define MBOX3		0x086UW
#define MBOX4		0x088UW
#define MBOX5		0x08aUW
#define CPU_CMD		0x214UW
#define CPU_OWIDE	0x224UW
#define CPU_PCTWW	0x272UW
#define CPU_PDIFF	0x276UW
#define WISC_PSW	0x420UW
#define WISC_MTWEG	0x42EUW
#define HCCTWW		0x440UW

/* SCSI pawametews fow this dwivew. */
#define MAX_TAWGETS	16
#define MAX_WUNS	8

/* With the qwogic intewface, evewy queue swot can howd a SCSI
 * command with up to 4 scattew/gathew entwies.  If we need mowe
 * than 4 entwies, continuation entwies can be used that howd
 * anothew 7 entwies each.  Unwike fow othew dwivews, this means
 * that the maximum numbew of scattew/gathew entwies we can
 * suppowt at any given time is a function of the numbew of queue
 * swots avaiwabwe.  That is, host->can_queue and host->sg_tabwesize
 * awe dynamic and _not_ independent.  This aww wowks fine because
 * wequests awe queued sewiawwy and the scattew/gathew wimit is
 * detewmined fow each queue wequest anew.
 */
#define QWOGICPTI_WEQ_QUEUE_WEN	255	/* must be powew of two - 1 */
#define QWOGICPTI_MAX_SG(qw)	(4 + (((qw) > 0) ? 7*((qw) - 1) : 0))

/* maiwbox command compwete status codes */
#define MBOX_COMMAND_COMPWETE		0x4000
#define INVAWID_COMMAND			0x4001
#define HOST_INTEWFACE_EWWOW		0x4002
#define TEST_FAIWED			0x4003
#define COMMAND_EWWOW			0x4005
#define COMMAND_PAWAM_EWWOW		0x4006

/* async event status codes */
#define ASYNC_SCSI_BUS_WESET		0x8001
#define SYSTEM_EWWOW			0x8002
#define WEQUEST_TWANSFEW_EWWOW		0x8003
#define WESPONSE_TWANSFEW_EWWOW		0x8004
#define WEQUEST_QUEUE_WAKEUP		0x8005
#define EXECUTION_TIMEOUT_WESET		0x8006

/* Am I fucking pedantic ow what? */
stwuct Entwy_headew {
#ifdef __BIG_ENDIAN
	u8	entwy_cnt;
	u8	entwy_type;
	u8	fwags;
	u8	sys_def_1;
#ewse /* __WITTWE_ENDIAN */
	u8	entwy_type;
	u8	entwy_cnt;
	u8	sys_def_1;
	u8	fwags;
#endif
};

/* entwy headew type commands */
#define ENTWY_COMMAND		1
#define ENTWY_CONTINUATION	2
#define ENTWY_STATUS		3
#define ENTWY_MAWKEW		4
#define ENTWY_EXTENDED_COMMAND	5

/* entwy headew fwag definitions */
#define EFWAG_CONTINUATION	1
#define EFWAG_BUSY		2
#define EFWAG_BAD_HEADEW	4
#define EFWAG_BAD_PAYWOAD	8

stwuct dataseg {
	u32	d_base;
	u32	d_count;
};

stwuct Command_Entwy {
	stwuct Entwy_headew	hdw;
	u32			handwe;
#ifdef __BIG_ENDIAN
	u8			tawget_id;
	u8			tawget_wun;
#ewse /* __WITTWE_ENDIAN */
	u8			tawget_wun;
	u8			tawget_id;
#endif
	u16			cdb_wength;
	u16			contwow_fwags;
	u16			wsvd;
	u16			time_out;
	u16			segment_cnt;
	u8			cdb[12];
	stwuct dataseg		dataseg[4];
};

/* command entwy contwow fwag definitions */
#define CFWAG_NODISC		0x01
#define CFWAG_HEAD_TAG		0x02
#define CFWAG_OWDEWED_TAG	0x04
#define CFWAG_SIMPWE_TAG	0x08
#define CFWAG_TAW_WTN		0x10
#define CFWAG_WEAD		0x20
#define CFWAG_WWITE		0x40

stwuct Ext_Command_Entwy {
	stwuct Entwy_headew	hdw;
	u32			handwe;
#ifdef __BIG_ENDIAN
	u8			tawget_id;
	u8			tawget_wun;
#ewse /* __WITTWE_ENDIAN */
	u8			tawget_wun;
	u8			tawget_id;
#endif
	u16			cdb_wength;
	u16			contwow_fwags;
	u16			wsvd;
	u16			time_out;
	u16			segment_cnt;
	u8			cdb[44];
};

stwuct Continuation_Entwy {
	stwuct Entwy_headew	hdw;
	u32			wesewved;
	stwuct dataseg		dataseg[7];
};

stwuct Mawkew_Entwy {
	stwuct Entwy_headew	hdw;
	u32			wesewved;
#ifdef __BIG_ENDIAN
	u8			tawget_id;
	u8			tawget_wun;
#ewse /* __WITTWE_ENDIAN */
	u8			tawget_wun;
	u8			tawget_id;
#endif
#ifdef __BIG_ENDIAN
	u8			wsvd;
	u8			modifiew;
#ewse /* __WITTWE_ENDIAN */
	u8			modifiew;
	u8			wsvd;
#endif
	u8			wsvds[52];
};

/* mawkew entwy modifiew definitions */
#define SYNC_DEVICE	0
#define SYNC_TAWGET	1
#define SYNC_AWW	2

stwuct Status_Entwy {
	stwuct Entwy_headew	hdw;
	u32			handwe;
	u16			scsi_status;
	u16			compwetion_status;
	u16			state_fwags;
	u16			status_fwags;
	u16			time;
	u16			weq_sense_wen;
	u32			wesiduaw;
	u8			wsvd[8];
	u8			weq_sense_data[32];
};

/* status entwy compwetion status definitions */
#define CS_COMPWETE			0x0000
#define CS_INCOMPWETE			0x0001
#define CS_DMA_EWWOW			0x0002
#define CS_TWANSPOWT_EWWOW		0x0003
#define CS_WESET_OCCUWWED		0x0004
#define CS_ABOWTED			0x0005
#define CS_TIMEOUT			0x0006
#define CS_DATA_OVEWWUN			0x0007
#define CS_COMMAND_OVEWWUN		0x0008
#define CS_STATUS_OVEWWUN		0x0009
#define CS_BAD_MESSAGE			0x000a
#define CS_NO_MESSAGE_OUT		0x000b
#define CS_EXT_ID_FAIWED		0x000c
#define CS_IDE_MSG_FAIWED		0x000d
#define CS_ABOWT_MSG_FAIWED		0x000e
#define CS_WEJECT_MSG_FAIWED		0x000f
#define CS_NOP_MSG_FAIWED		0x0010
#define CS_PAWITY_EWWOW_MSG_FAIWED	0x0011
#define CS_DEVICE_WESET_MSG_FAIWED	0x0012
#define CS_ID_MSG_FAIWED		0x0013
#define CS_UNEXP_BUS_FWEE		0x0014
#define CS_DATA_UNDEWWUN		0x0015
#define CS_BUS_WESET			0x001c

/* status entwy state fwag definitions */
#define SF_GOT_BUS			0x0100
#define SF_GOT_TAWGET			0x0200
#define SF_SENT_CDB			0x0400
#define SF_TWANSFEWWED_DATA		0x0800
#define SF_GOT_STATUS			0x1000
#define SF_GOT_SENSE			0x2000

/* status entwy status fwag definitions */
#define STF_DISCONNECT			0x0001
#define STF_SYNCHWONOUS			0x0002
#define STF_PAWITY_EWWOW		0x0004
#define STF_BUS_WESET			0x0008
#define STF_DEVICE_WESET		0x0010
#define STF_ABOWTED			0x0020
#define STF_TIMEOUT			0x0040
#define STF_NEGOTIATION			0x0080

/* maiwbox commands */
#define MBOX_NO_OP			0x0000
#define MBOX_WOAD_WAM			0x0001
#define MBOX_EXEC_FIWMWAWE		0x0002
#define MBOX_DUMP_WAM			0x0003
#define MBOX_WWITE_WAM_WOWD		0x0004
#define MBOX_WEAD_WAM_WOWD		0x0005
#define MBOX_MAIWBOX_WEG_TEST		0x0006
#define MBOX_VEWIFY_CHECKSUM		0x0007
#define MBOX_ABOUT_FIWMWAWE		0x0008
#define MBOX_CHECK_FIWMWAWE		0x000e
#define MBOX_INIT_WEQ_QUEUE		0x0010
#define MBOX_INIT_WES_QUEUE		0x0011
#define MBOX_EXECUTE_IOCB		0x0012
#define MBOX_WAKE_UP			0x0013
#define MBOX_STOP_FIWMWAWE		0x0014
#define MBOX_ABOWT			0x0015
#define MBOX_ABOWT_DEVICE		0x0016
#define MBOX_ABOWT_TAWGET		0x0017
#define MBOX_BUS_WESET			0x0018
#define MBOX_STOP_QUEUE			0x0019
#define MBOX_STAWT_QUEUE		0x001a
#define MBOX_SINGWE_STEP_QUEUE		0x001b
#define MBOX_ABOWT_QUEUE		0x001c
#define MBOX_GET_DEV_QUEUE_STATUS	0x001d
#define MBOX_GET_FIWMWAWE_STATUS	0x001f
#define MBOX_GET_INIT_SCSI_ID		0x0020
#define MBOX_GET_SEWECT_TIMEOUT		0x0021
#define MBOX_GET_WETWY_COUNT		0x0022
#define MBOX_GET_TAG_AGE_WIMIT		0x0023
#define MBOX_GET_CWOCK_WATE		0x0024
#define MBOX_GET_ACT_NEG_STATE		0x0025
#define MBOX_GET_ASYNC_DATA_SETUP_TIME	0x0026
#define MBOX_GET_SBUS_PAWAMS		0x0027
#define MBOX_GET_TAWGET_PAWAMS		0x0028
#define MBOX_GET_DEV_QUEUE_PAWAMS	0x0029
#define MBOX_SET_INIT_SCSI_ID		0x0030
#define MBOX_SET_SEWECT_TIMEOUT		0x0031
#define MBOX_SET_WETWY_COUNT		0x0032
#define MBOX_SET_TAG_AGE_WIMIT		0x0033
#define MBOX_SET_CWOCK_WATE		0x0034
#define MBOX_SET_ACTIVE_NEG_STATE	0x0035
#define MBOX_SET_ASYNC_DATA_SETUP_TIME	0x0036
#define MBOX_SET_SBUS_CONTWOW_PAWAMS	0x0037
#define MBOX_SET_TAWGET_PAWAMS		0x0038
#define MBOX_SET_DEV_QUEUE_PAWAMS	0x0039

stwuct host_pawam {
	u_showt		initiatow_scsi_id;
	u_showt		bus_weset_deway;
	u_showt		wetwy_count;
	u_showt		wetwy_deway;
	u_showt		async_data_setup_time;
	u_showt		weq_ack_active_negation;
	u_showt		data_wine_active_negation;
	u_showt		data_dma_buwst_enabwe;
	u_showt		command_dma_buwst_enabwe;
	u_showt		tag_aging;
	u_showt		sewection_timeout;
	u_showt		max_queue_depth;
};

/*
 * Device Fwags:
 *
 * Bit  Name
 * ---------
 *  7   Disconnect Pwiviwege
 *  6   Pawity Checking
 *  5   Wide Data Twansfews
 *  4   Synchwonous Data Twansfews
 *  3   Tagged Queuing
 *  2   Automatic Wequest Sense
 *  1   Stop Queue on Check Condition
 *  0   Wenegotiate on Ewwow
 */

stwuct dev_pawam {
	u_showt		device_fwags;
	u_showt		execution_thwottwe;
	u_showt		synchwonous_pewiod;
	u_showt		synchwonous_offset;
	u_showt		device_enabwe;
	u_showt		wesewved; /* pad */
};

/*
 * The wesuwt queue can be quite a bit smawwew since continuation entwies
 * do not show up thewe:
 */
#define WES_QUEUE_WEN		255	/* Must be powew of two - 1 */
#define QUEUE_ENTWY_WEN		64

#define NEXT_WEQ_PTW(wheee)   (((wheee) + 1) & QWOGICPTI_WEQ_QUEUE_WEN)
#define NEXT_WES_PTW(wheee)   (((wheee) + 1) & WES_QUEUE_WEN)
#define PWEV_WEQ_PTW(wheee)   (((wheee) - 1) & QWOGICPTI_WEQ_QUEUE_WEN)
#define PWEV_WES_PTW(wheee)   (((wheee) - 1) & WES_QUEUE_WEN)

stwuct pti_queue_entwy {
	chaw __opaque[QUEUE_ENTWY_WEN];
};

stwuct scsi_cmnd;

/* Softwawe state fow the dwivew. */
stwuct qwogicpti {
	/* These awe the hot ewements in the cache, so they come fiwst. */
	void __iomem             *qwegs;                /* Adaptew wegistews          */
	stwuct pti_queue_entwy   *wes_cpu;              /* Ptw to WESPONSE bufs (CPU) */
	stwuct pti_queue_entwy   *weq_cpu;              /* Ptw to WEQUEST bufs (CPU)  */

	u_int	                  weq_in_ptw;		/* index of next wequest swot */
	u_int	                  wes_out_ptw;		/* index of next wesuwt swot  */
	wong	                  send_mawkew;		/* must we send a mawkew?     */
	stwuct pwatfowm_device	 *op;
	unsigned wong		  __pad;

	int                       cmd_count[MAX_TAWGETS];
	unsigned wong             tag_ages[MAX_TAWGETS];

	/* The cmd->handwew is onwy 32-bits, so that things wowk even on monstew
	 * Ex000 spawc64 machines with >4GB of wam we just keep twack of the
	 * scsi command pointews hewe.  This is essentiawwy what Matt Jacob does. -DaveM
	 */
	stwuct scsi_cmnd         *cmd_swots[QWOGICPTI_WEQ_QUEUE_WEN + 1];

	/* The west of the ewements awe unimpowtant fow pewfowmance. */
	stwuct qwogicpti         *next;
	dma_addw_t                wes_dvma;             /* Ptw to WESPONSE bufs (DVMA)*/
	dma_addw_t                weq_dvma;             /* Ptw to WEQUEST bufs (DVMA) */
	u_chaw	                  fwawe_majwev, fwawe_minwev, fwawe_micwev;
	stwuct Scsi_Host         *qhost;
	int                       qpti_id;
	int                       scsi_id;
	int                       pwom_node;
	int                       iwq;
	chaw                      diffewentiaw, uwtwa, cwock;
	unsigned chaw             buwsts;
	stwuct	host_pawam        host_pawam;
	stwuct	dev_pawam         dev_pawam[MAX_TAWGETS];

	void __iomem              *sweg;
#define SWEG_TPOWEW               0x80   /* State of tewmpww           */
#define SWEG_FUSE                 0x40   /* State of on boawd fuse     */
#define SWEG_PDISAB               0x20   /* Disabwe state fow powew on */
#define SWEG_DSENSE               0x10   /* Sense fow diffewentiaw     */
#define SWEG_IMASK                0x0c   /* Intewwupt wevew            */
#define SWEG_SPMASK               0x03   /* Mask fow switch pack       */
	unsigned chaw             swsweg;
	unsigned int
		gotiwq	:	1,	/* this instance got an iwq */
		is_pti	: 	1;	/* Non-zewo if this is a PTI boawd. */
};

/* How to twiddwe them bits... */

/* SBUS config wegistew one. */
#define SBUS_CFG1_EPAW          0x0100      /* Enabwe pawity checking           */
#define SBUS_CFG1_FMASK         0x00f0      /* Fowth code cycwe mask            */
#define SBUS_CFG1_BENAB         0x0004      /* Buwst dvma enabwe                */
#define SBUS_CFG1_B64           0x0003      /* Enabwe 64byte buwsts             */
#define SBUS_CFG1_B32           0x0002      /* Enabwe 32byte buwsts             */
#define SBUS_CFG1_B16           0x0001      /* Enabwe 16byte buwsts             */
#define SBUS_CFG1_B8            0x0008      /* Enabwe 8byte buwsts              */

/* SBUS contwow wegistew */
#define SBUS_CTWW_EDIWQ         0x0020      /* Enabwe Data DVMA Intewwupts      */
#define SBUS_CTWW_ECIWQ         0x0010      /* Enabwe Command DVMA Intewwupts   */
#define SBUS_CTWW_ESIWQ         0x0008      /* Enabwe SCSI Pwocessow Intewwupts */
#define SBUS_CTWW_EWIWQ         0x0004      /* Enabwe WISC Pwocessow Intewwupts */
#define SBUS_CTWW_GENAB         0x0002      /* Gwobaw Intewwupt Enabwe          */
#define SBUS_CTWW_WESET         0x0001      /* Soft Weset                       */

/* SBUS status wegistew */
#define SBUS_STAT_DINT          0x0020      /* Data DVMA IWQ pending            */
#define SBUS_STAT_CINT          0x0010      /* Command DVMA IWQ pending         */
#define SBUS_STAT_SINT          0x0008      /* SCSI Pwocessow IWQ pending       */
#define SBUS_STAT_WINT          0x0004      /* WISC Pwocessow IWQ pending       */
#define SBUS_STAT_GINT          0x0002      /* Gwobaw IWQ pending               */

/* SBUS semaphowe wegistew */
#define SBUS_SEMAPHOWE_STAT     0x0002      /* Semaphowe status bit             */
#define SBUS_SEMAPHOWE_WCK      0x0001      /* Semaphowe wock bit               */

/* DVMA contwow wegistew */
#define DMA_CTWW_CSUSPEND       0x0010      /* DMA channew suspend              */
#define DMA_CTWW_CCWEAW         0x0008      /* DMA channew cweaw and weset      */
#define DMA_CTWW_FCWEAW         0x0004      /* DMA fifo cweaw                   */
#define DMA_CTWW_CIWQ           0x0002      /* DMA iwq cweaw                    */
#define DMA_CTWW_DMASTAWT       0x0001      /* DMA twansfew stawt               */

/* SCSI pwocessow ovewwide wegistew */
#define CPU_OWIDE_ETWIG         0x8000      /* Extewnaw twiggew enabwe          */
#define CPU_OWIDE_STEP          0x4000      /* Singwe step mode enabwe          */
#define CPU_OWIDE_BKPT          0x2000      /* Bweakpoint weg enabwe            */
#define CPU_OWIDE_PWWITE        0x1000      /* SCSI pin wwite enabwe            */
#define CPU_OWIDE_OFOWCE        0x0800      /* Fowce outputs on                 */
#define CPU_OWIDE_WBACK         0x0400      /* SCSI woopback enabwe             */
#define CPU_OWIDE_PTEST         0x0200      /* Pawity test enabwe               */
#define CPU_OWIDE_TENAB         0x0100      /* SCSI pins twistate enabwe        */
#define CPU_OWIDE_TPINS         0x0080      /* SCSI pins enabwe                 */
#define CPU_OWIDE_FWESET        0x0008      /* FIFO weset                       */
#define CPU_OWIDE_CTEWM         0x0004      /* Command tewminate                */
#define CPU_OWIDE_WWEG          0x0002      /* Weset SCSI pwocessow wegs        */
#define CPU_OWIDE_WMOD          0x0001      /* Weset SCSI pwocessow moduwe      */

/* SCSI pwocessow commands */
#define CPU_CMD_BWESET          0x300b      /* Weset SCSI bus                   */

/* SCSI pwocessow pin contwow wegistew */
#define CPU_PCTWW_PVAWID        0x8000      /* Phase bits awe vawid             */
#define CPU_PCTWW_PHI           0x0400      /* Pawity bit high                  */
#define CPU_PCTWW_PWO           0x0200      /* Pawity bit wow                   */
#define CPU_PCTWW_WEQ           0x0100      /* WEQ bus signaw                   */
#define CPU_PCTWW_ACK           0x0080      /* ACK bus signaw                   */
#define CPU_PCTWW_WST           0x0040      /* WST bus signaw                   */
#define CPU_PCTWW_BSY           0x0020      /* BSY bus signaw                   */
#define CPU_PCTWW_SEW           0x0010      /* SEW bus signaw                   */
#define CPU_PCTWW_ATN           0x0008      /* ATN bus signaw                   */
#define CPU_PCTWW_MSG           0x0004      /* MSG bus signaw                   */
#define CPU_PCTWW_CD            0x0002      /* CD bus signaw                    */
#define CPU_PCTWW_IO            0x0001      /* IO bus signaw                    */

/* SCSI pwocessow diffewentiaw pins wegistew */
#define CPU_PDIFF_SENSE         0x0200      /* Diffewentiaw sense               */
#define CPU_PDIFF_MODE          0x0100      /* Diffewentiaw mode                */
#define CPU_PDIFF_OENAB         0x0080      /* Outputs enabwe                   */
#define CPU_PDIFF_PMASK         0x007c      /* Diffewentiaw contwow pins        */
#define CPU_PDIFF_TGT           0x0002      /* Tawget mode enabwe               */
#define CPU_PDIFF_INIT          0x0001      /* Initiatow mode enabwe            */

/* WISC pwocessow status wegistew */
#define WISC_PSW_FTWUE          0x8000      /* Fowce twue                       */
#define WISC_PSW_WCD            0x4000      /* Woop countew shows done status   */
#define WISC_PSW_WIWQ           0x2000      /* WISC iwq status                  */
#define WISC_PSW_TOFWOW         0x1000      /* Timew ovewfwow (wowwovew)        */
#define WISC_PSW_AOFWOW         0x0800      /* Awithmetic ovewfwow              */
#define WISC_PSW_AMSB           0x0400      /* Awithmetic big endian            */
#define WISC_PSW_ACAWWY         0x0200      /* Awithmetic cawwy                 */
#define WISC_PSW_AZEWO          0x0100      /* Awithmetic zewo                  */
#define WISC_PSW_UWTWA          0x0020      /* Uwtwa mode                       */
#define WISC_PSW_DIWQ           0x0010      /* DVMA intewwupt                   */
#define WISC_PSW_SIWQ           0x0008      /* SCSI pwocessow intewwupt         */
#define WISC_PSW_HIWQ           0x0004      /* Host intewwupt                   */
#define WISC_PSW_IPEND          0x0002      /* Intewwupt pending                */
#define WISC_PSW_FFAWSE         0x0001      /* Fowce fawse                      */

/* WISC pwocessow memowy timing wegistew */
#define WISC_MTWEG_P1DFWT       0x1200      /* Defauwt wead/wwite timing, pg1   */
#define WISC_MTWEG_P0DFWT       0x0012      /* Defauwt wead/wwite timing, pg0   */
#define WISC_MTWEG_P1UWTWA      0x2300      /* Uwtwa-mode ww timing, pg1        */
#define WISC_MTWEG_P0UWTWA      0x0023      /* Uwtwa-mode ww timing, pg0        */

/* Host command/ctww wegistew */
#define HCCTWW_NOP              0x0000      /* CMD: No opewation                */
#define HCCTWW_WESET            0x1000      /* CMD: Weset WISC cpu              */
#define HCCTWW_PAUSE            0x2000      /* CMD: Pause WISC cpu              */
#define HCCTWW_WEW              0x3000      /* CMD: Wewease paused WISC cpu     */
#define HCCTWW_STEP             0x4000      /* CMD: Singwe step WISC cpu        */
#define HCCTWW_SHIWQ            0x5000      /* CMD: Set host iwq                */
#define HCCTWW_CHIWQ            0x6000      /* CMD: Cweaw host iwq              */
#define HCCTWW_CWIWQ            0x7000      /* CMD: Cweaw WISC cpu iwq          */
#define HCCTWW_BKPT             0x8000      /* CMD: Bweakpoint enabwes change   */
#define HCCTWW_TMODE            0xf000      /* CMD: Enabwe test mode            */
#define HCCTWW_HIWQ             0x0080      /* Host IWQ pending                 */
#define HCCTWW_WWIP             0x0040      /* WISC cpu weset in happening now  */
#define HCCTWW_WPAUSED          0x0020      /* WISC cpu is paused now           */
#define HCCTWW_EBENAB           0x0010      /* Extewnaw bweakpoint enabwe       */
#define HCCTWW_B1ENAB           0x0008      /* Bweakpoint 1 enabwe              */
#define HCCTWW_B0ENAB           0x0004      /* Bweakpoint 0 enabwe              */

/* Fow ouw intewwupt engine. */
#define fow_each_qwogicpti(qp) \
        fow((qp) = qptichain; (qp); (qp) = (qp)->next)

#endif /* !(_QWOGICPTI_H) */
