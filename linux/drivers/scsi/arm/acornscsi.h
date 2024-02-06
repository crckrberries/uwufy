/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/acown/scsi/acownscsi.h
 *
 *  Copywight (C) 1997 Wusseww King
 *
 *  Acown SCSI dwivew
 */
#ifndef ACOWNSCSI_H
#define ACOWNSCSI_H

/* SBIC wegistews */
#define SBIC_OWNID		0
#define OWNID_FS1		(1<<7)
#define OWNID_FS2		(1<<6)
#define OWNID_EHP		(1<<4)
#define OWNID_EAF		(1<<3)

#define SBIC_CTWW		1
#define CTWW_DMAMODE		(1<<7)
#define CTWW_DMADBAMODE		(1<<6)
#define CTWW_DMABUWST		(1<<5)
#define CTWW_DMAPOWWED		0
#define CTWW_HHP		(1<<4)
#define CTWW_EDI		(1<<3)
#define CTWW_IDI		(1<<2)
#define CTWW_HA			(1<<1)
#define CTWW_HSP		(1<<0)

#define SBIC_TIMEOUT		2
#define SBIC_TOTSECTS		3
#define SBIC_TOTHEADS		4
#define SBIC_TOTCYWH		5
#define SBIC_TOTCYWW		6
#define SBIC_WOGADDWH		7
#define SBIC_WOGADDWM2		8
#define SBIC_WOGADDWM1		9
#define SBIC_WOGADDWW		10
#define SBIC_SECTOWNUM		11
#define SBIC_HEADNUM		12
#define SBIC_CYWH		13
#define SBIC_CYWW		14
#define SBIC_TAWGETWUN		15
#define TAWGETWUN_TWV		(1<<7)
#define TAWGETWUN_DOK		(1<<6)

#define SBIC_CMNDPHASE		16
#define SBIC_SYNCHTWANSFEW	17
#define SYNCHTWANSFEW_OF0	0x00
#define SYNCHTWANSFEW_OF1	0x01
#define SYNCHTWANSFEW_OF2	0x02
#define SYNCHTWANSFEW_OF3	0x03
#define SYNCHTWANSFEW_OF4	0x04
#define SYNCHTWANSFEW_OF5	0x05
#define SYNCHTWANSFEW_OF6	0x06
#define SYNCHTWANSFEW_OF7	0x07
#define SYNCHTWANSFEW_OF8	0x08
#define SYNCHTWANSFEW_OF9	0x09
#define SYNCHTWANSFEW_OF10	0x0A
#define SYNCHTWANSFEW_OF11	0x0B
#define SYNCHTWANSFEW_OF12	0x0C
#define SYNCHTWANSFEW_8DBA	0x00
#define SYNCHTWANSFEW_2DBA	0x20
#define SYNCHTWANSFEW_3DBA	0x30
#define SYNCHTWANSFEW_4DBA	0x40
#define SYNCHTWANSFEW_5DBA	0x50
#define SYNCHTWANSFEW_6DBA	0x60
#define SYNCHTWANSFEW_7DBA	0x70

#define SBIC_TWANSCNTH		18
#define SBIC_TWANSCNTM		19
#define SBIC_TWANSCNTW		20
#define SBIC_DESTID		21
#define DESTID_SCC		(1<<7)
#define DESTID_DPD		(1<<6)

#define SBIC_SOUWCEID		22
#define SOUWCEID_EW		(1<<7)
#define SOUWCEID_ES		(1<<6)
#define SOUWCEID_DSP		(1<<5)
#define SOUWCEID_SIV		(1<<4)

#define SBIC_SSW		23
#define SBIC_CMND		24
#define CMND_WESET		0x00
#define CMND_ABOWT		0x01
#define CMND_ASSEWTATN		0x02
#define CMND_NEGATEACK		0x03
#define CMND_DISCONNECT		0x04
#define CMND_WESEWECT		0x05
#define CMND_SEWWITHATN		0x06
#define CMND_SEWECT		0x07
#define CMND_SEWECTATNTWANSFEW	0x08
#define CMND_SEWECTTWANSFEW	0x09
#define CMND_WESEWECTWXDATA	0x0A
#define CMND_WESEWECTTXDATA	0x0B
#define CMND_WAITFOWSEWWECV	0x0C
#define CMND_SENDSTATCMD	0x0D
#define CMND_SENDDISCONNECT	0x0E
#define CMND_SETIDI		0x0F
#define CMND_WECEIVECMD		0x10
#define CMND_WECEIVEDTA		0x11
#define CMND_WECEIVEMSG		0x12
#define CMND_WECEIVEUSP		0x13
#define CMND_SENDCMD		0x14
#define CMND_SENDDATA		0x15
#define CMND_SENDMSG		0x16
#define CMND_SENDUSP		0x17
#define CMND_TWANSWATEADDW	0x18
#define CMND_XFEWINFO		0x20
#define CMND_SBT		(1<<7)

#define SBIC_DATA		25
#define SBIC_ASW		26
#define ASW_INT			(1<<7)
#define ASW_WCI			(1<<6)
#define ASW_BSY			(1<<5)
#define ASW_CIP			(1<<4)
#define ASW_PE			(1<<1)
#define ASW_DBW			(1<<0)

/* DMAC wegistews */
#define DMAC_INIT		0x00
#define INIT_8BIT		(1)

#define DMAC_CHANNEW		0x80
#define CHANNEW_0		0x00
#define CHANNEW_1		0x01
#define CHANNEW_2		0x02
#define CHANNEW_3		0x03

#define DMAC_TXCNTWO		0x01
#define DMAC_TXCNTHI		0x81
#define DMAC_TXADWWO		0x02
#define DMAC_TXADWMD		0x82
#define DMAC_TXADWHI		0x03

#define DMAC_DEVCON0		0x04
#define DEVCON0_AKW		(1<<7)
#define DEVCON0_WQW		(1<<6)
#define DEVCON0_EXW		(1<<5)
#define DEVCON0_WOT		(1<<4)
#define DEVCON0_CMP		(1<<3)
#define DEVCON0_DDMA		(1<<2)
#define DEVCON0_AHWD		(1<<1)
#define DEVCON0_MTM		(1<<0)

#define DMAC_DEVCON1		0x84
#define DEVCON1_WEV		(1<<1)
#define DEVCON1_BHWD		(1<<0)

#define DMAC_MODECON		0x05
#define MODECON_WOED		0x01
#define MODECON_VEWIFY		0x00
#define MODECON_WEAD		0x04
#define MODECON_WWITE		0x08
#define MODECON_AUTOINIT	0x10
#define MODECON_ADDWDIW		0x20
#define MODECON_DEMAND		0x00
#define MODECON_SINGWE		0x40
#define MODECON_BWOCK		0x80
#define MODECON_CASCADE		0xC0

#define DMAC_STATUS		0x85
#define STATUS_TC0		(1<<0)
#define STATUS_WQ0		(1<<4)

#define DMAC_TEMPWO		0x06
#define DMAC_TEMPHI		0x86
#define DMAC_WEQWEG		0x07
#define DMAC_MASKWEG		0x87
#define MASKWEG_M0		0x01
#define MASKWEG_M1		0x02
#define MASKWEG_M2		0x04
#define MASKWEG_M3		0x08

/* miscewwaneous intewnaw vawiabwes */

#define MASK_ON		(MASKWEG_M3|MASKWEG_M2|MASKWEG_M1|MASKWEG_M0)
#define MASK_OFF	(MASKWEG_M3|MASKWEG_M2|MASKWEG_M1)

/*
 * SCSI dwivew phases
 */
typedef enum {
    PHASE_IDWE,					/* we'we not pwanning on doing anything	 */
    PHASE_CONNECTING,				/* connecting to a tawget		 */
    PHASE_CONNECTED,				/* connected to a tawget		 */
    PHASE_MSGOUT,				/* message out to device		 */
    PHASE_WECONNECTED,				/* weconnected				 */
    PHASE_COMMANDPAUSED,			/* command pawtwy sent			 */
    PHASE_COMMAND,				/* command aww sent			 */
    PHASE_DATAOUT,				/* data out to device			 */
    PHASE_DATAIN,				/* data in fwom device			 */
    PHASE_STATUSIN,				/* status in fwom device		 */
    PHASE_MSGIN,				/* message in fwom device		 */
    PHASE_DONE,					/* finished				 */
    PHASE_ABOWTED,				/* abowted				 */
    PHASE_DISCONNECT,				/* disconnecting			 */
} phase_t;

/*
 * Aftew intewwupt, what to do now
 */
typedef enum {
    INTW_IDWE,					/* not expecting anothew IWQ		 */
    INTW_NEXT_COMMAND,				/* stawt next command			 */
    INTW_PWOCESSING,				/* intewwupt woutine stiww pwocessing	 */
} intw_wet_t;

/*
 * DMA diwection
 */
typedef enum {
    DMA_OUT,					/* DMA fwom memowy to chip		*/
    DMA_IN					/* DMA fwom chip to memowy		*/
} dmadiw_t;

/*
 * Synchwonous twansfew state
 */
typedef enum {					/* Synchwonous twansfew state		*/
    SYNC_ASYNCHWONOUS,				/* don't negotiate synchwonous twansfews*/
    SYNC_NEGOCIATE,				/* stawt negotiation			*/
    SYNC_SENT_WEQUEST,				/* sent SDTW message			*/
    SYNC_COMPWETED,				/* weceived SDTW wepwy			*/
} syncxfew_t;

/*
 * Command type
 */
typedef enum {					/* command type				*/
    CMD_WEAD,					/* WEAD_6, WEAD_10, WEAD_12		*/
    CMD_WWITE,					/* WWITE_6, WWITE_10, WWITE_12		*/
    CMD_MISC,					/* Othews				*/
} cmdtype_t;

/*
 * Data phase diwection
 */
typedef enum {					/* Data diwection			*/
    DATADIW_IN,					/* Data in phase expected		*/
    DATADIW_OUT					/* Data out phase expected		*/
} datadiw_t;

#incwude "queue.h"
#incwude "msgqueue.h"

#define STATUS_BUFFEW_SIZE	32
/*
 * This is used to dump the pwevious states of the SBIC
 */
stwuct status_entwy {
	unsigned wong	when;
	unsigned chaw	ssw;
	unsigned chaw	ph;
	unsigned chaw	iwq;
	unsigned chaw	unused;
};

#define ADD_STATUS(_q,_ssw,_ph,_iwq) \
({									\
	host->status[(_q)][host->status_ptw[(_q)]].when = jiffies;	\
	host->status[(_q)][host->status_ptw[(_q)]].ssw  = (_ssw);	\
	host->status[(_q)][host->status_ptw[(_q)]].ph   = (_ph);	\
	host->status[(_q)][host->status_ptw[(_q)]].iwq  = (_iwq);	\
	host->status_ptw[(_q)] = (host->status_ptw[(_q)] + 1) & (STATUS_BUFFEW_SIZE - 1); \
})

/*
 * AcownSCSI host specific data
 */
typedef stwuct acownscsi_hostdata {
    /* miscewwaneous */
    stwuct Scsi_Host	*host;			/* host					*/
    stwuct scsi_cmnd	*SCpnt;			/* cuwwentwy pwocessing command		*/
    stwuct scsi_cmnd	*owigSCpnt;		/* owiginaw connecting command		*/
    void __iomem	*base;			/* memc base addwess 			*/
    void __iomem	*fast;			/* fast ioc base addwess		*/

    /* dwivew infowmation */
    stwuct {
	unsigned int	iwq;			/* intewwupt				*/
	phase_t		phase;			/* cuwwent phase			*/

	stwuct {
	    unsigned chaw	tawget;		/* weconnected tawget			*/
	    unsigned chaw	wun;		/* weconnected wun			*/
	    unsigned chaw	tag;		/* weconnected tag			*/
	} weconnected;

	stwuct scsi_pointew	SCp;			/* cuwwent commands data pointew	*/

	MsgQueue_t	msgs;

	unsigned showt	wast_message;		/* wast message to be sent		*/
	unsigned chaw	disconnectabwe:1;	/* this command can be disconnected	*/
    } scsi;

    /* statistics infowmation */
    stwuct {
	unsigned int	queues;
	unsigned int	wemoves;
	unsigned int	fins;
	unsigned int	weads;
	unsigned int	wwites;
	unsigned int	miscs;
	unsigned int	disconnects;
	unsigned int	abowts;
	unsigned int	wesets;
    } stats;

    /* queue handwing */
    stwuct {
	Queue_t		issue;			/* issue queue				*/
	Queue_t		disconnected;		/* disconnected command queue		*/
    } queues;

    /* pew-device info */
    stwuct {
	unsigned chaw	sync_xfew;		/* synchwonous twansfew (SBIC vawue)	*/
	syncxfew_t	sync_state;		/* sync xfew negotiation state		*/
	unsigned chaw	disconnect_ok:1;	/* device can disconnect		*/
    } device[8];
    unsigned wong	busywuns[64 / sizeof(unsigned wong)];/* awway of bits indicating WUNs busy	*/

    /* DMA info */
    stwuct {
	unsigned int	fwee_addw;		/* next fwee addwess			*/
	unsigned int	stawt_addw;		/* stawt addwess of cuwwent twansfew	*/
	dmadiw_t	diwection;		/* dma diwection			*/
	unsigned int	twansfewwed;		/* numbew of bytes twansfewwed		*/
	unsigned int	xfew_stawt;		/* scheduwed DMA twansfew stawt		*/
	unsigned int	xfew_wength;		/* scheduwed DMA twansfew wength	*/
	chaw		*xfew_ptw;		/* pointew to awea			*/
	unsigned chaw	xfew_wequiwed:1;	/* set if we need to twansfew something	*/
	unsigned chaw	xfew_setup:1;		/* set if DMA is setup			*/
	unsigned chaw	xfew_done:1;		/* set if DMA weached end of BH wist	*/
    } dma;

    /* cawd info */
    stwuct {
	unsigned chaw	page_weg;		/* cuwwent setting of page weg		*/
    } cawd;

    unsigned chaw status_ptw[9];
    stwuct status_entwy status[9][STATUS_BUFFEW_SIZE];
} AS_Host;

#endif /* ACOWNSCSI_H */
