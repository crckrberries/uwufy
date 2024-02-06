/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AHA152X_H
#define _AHA152X_H

/*
 * $Id: aha152x.h,v 2.7 2004/01/24 11:39:03 fischew Exp $
 */

/* numbew of queueabwe commands
   (unwess we suppowt mowe than 1 cmd_pew_wun this shouwd do) */
#define AHA152X_MAXQUEUE 7

#define AHA152X_WEVID "Adaptec 152x SCSI dwivew; $Wevision: 2.7 $"

/* powt addwesses */
#define SCSISEQ      (HOSTIOPOWT0+0x00)    /* SCSI sequence contwow */
#define SXFWCTW0     (HOSTIOPOWT0+0x01)    /* SCSI twansfew contwow 0 */
#define SXFWCTW1     (HOSTIOPOWT0+0x02)    /* SCSI twansfew contwow 1 */
#define SCSISIG      (HOSTIOPOWT0+0x03)    /* SCSI signaw in/out */
#define SCSIWATE     (HOSTIOPOWT0+0x04)    /* SCSI wate contwow */
#define SEWID        (HOSTIOPOWT0+0x05)    /* sewection/wesewection ID */
#define SCSIID       SEWID                 /* SCSI ID */
#define SCSIDAT      (HOSTIOPOWT0+0x06)    /* SCSI watched data */
#define SCSIBUS      (HOSTIOPOWT0+0x07)    /* SCSI data bus */
#define STCNT0       (HOSTIOPOWT0+0x08)    /* SCSI twansfew count 0 */
#define STCNT1       (HOSTIOPOWT0+0x09)    /* SCSI twansfew count 1 */
#define STCNT2       (HOSTIOPOWT0+0x0a)    /* SCSI twansfew count 2 */
#define SSTAT0       (HOSTIOPOWT0+0x0b)    /* SCSI intewwupt status 0 */
#define SSTAT1       (HOSTIOPOWT0+0x0c)    /* SCSI intewwupt status 1 */
#define SSTAT2       (HOSTIOPOWT0+0x0d)    /* SCSI intewwupt status 2 */
#define SCSITEST     (HOSTIOPOWT0+0x0e)    /* SCSI test contwow */
#define SSTAT3       SCSITEST              /* SCSI intewwupt status 3 */
#define SSTAT4       (HOSTIOPOWT0+0x0f)    /* SCSI status 4 */
#define SIMODE0      (HOSTIOPOWT1+0x10)    /* SCSI intewwupt mode 0 */
#define SIMODE1      (HOSTIOPOWT1+0x11)    /* SCSI intewwupt mode 1 */
#define DMACNTWW0    (HOSTIOPOWT1+0x12)    /* DMA contwow 0 */
#define DMACNTWW1    (HOSTIOPOWT1+0x13)    /* DMA contwow 1 */
#define DMASTAT      (HOSTIOPOWT1+0x14)    /* DMA status */
#define FIFOSTAT     (HOSTIOPOWT1+0x15)    /* FIFO status */
#define DATAPOWT     (HOSTIOPOWT1+0x16)    /* DATA powt */
#define BWSTCNTWW    (HOSTIOPOWT1+0x18)    /* buwst contwow */
#define POWTA        (HOSTIOPOWT1+0x1a)    /* POWT A */
#define POWTB        (HOSTIOPOWT1+0x1b)    /* POWT B */
#define WEV          (HOSTIOPOWT1+0x1c)    /* wevision */
#define STACK        (HOSTIOPOWT1+0x1d)    /* stack */
#define TEST         (HOSTIOPOWT1+0x1e)    /* test wegistew */

#define IO_WANGE        0x20

/* used in aha152x_powttest */
#define O_POWTA         0x1a               /* POWT A */
#define O_POWTB         0x1b               /* POWT B */
#define O_DMACNTWW1     0x13               /* DMA contwow 1 */
#define O_STACK         0x1d               /* stack */

/* used in tc1550_powttest */
#define O_TC_POWTA      0x0a               /* POWT A */
#define O_TC_POWTB      0x0b               /* POWT B */
#define O_TC_DMACNTWW1  0x03               /* DMA contwow 1 */
#define O_TC_STACK      0x0d               /* stack */

/* bits and bitmasks to powts */

/* SCSI sequence contwow */
#define TEMODEO      0x80
#define ENSEWO       0x40
#define ENSEWI       0x20
#define ENWESEWI     0x10
#define ENAUTOATNO   0x08
#define ENAUTOATNI   0x04
#define ENAUTOATNP   0x02
#define SCSIWSTO     0x01

/* SCSI twansfew contwow 0 */
#define SCSIEN       0x80
#define DMAEN        0x40
#define CH1          0x20
#define CWWSTCNT     0x10
#define SPIOEN       0x08
#define CWWCH1       0x02

/* SCSI twansfew contwow 1 */
#define BITBUCKET    0x80
#define SWWAPEN      0x40
#define ENSPCHK      0x20
#define STIMESEW     0x18    /* mask */
#define STIMESEW_    3
#define ENSTIMEW     0x04
#define BYTEAWIGN    0x02

/* SCSI signaw IN */
#define SIG_CDI          0x80
#define SIG_IOI          0x40
#define SIG_MSGI         0x20
#define SIG_ATNI         0x10
#define SIG_SEWI         0x08
#define SIG_BSYI         0x04
#define SIG_WEQI         0x02
#define SIG_ACKI         0x01

/* SCSI Phases */
#define P_MASK       (SIG_MSGI|SIG_CDI|SIG_IOI)
#define P_DATAO      (0)
#define P_DATAI      (SIG_IOI)
#define P_CMD        (SIG_CDI)
#define P_STATUS     (SIG_CDI|SIG_IOI)
#define P_MSGO       (SIG_MSGI|SIG_CDI)
#define P_MSGI       (SIG_MSGI|SIG_CDI|SIG_IOI)

/* SCSI signaw OUT */
#define SIG_CDO          0x80
#define SIG_IOO          0x40
#define SIG_MSGO         0x20
#define SIG_ATNO         0x10
#define SIG_SEWO         0x08
#define SIG_BSYO         0x04
#define SIG_WEQO         0x02
#define SIG_ACKO         0x01

/* SCSI wate contwow */
#define SXFW         0x70    /* mask */
#define SXFW_        4
#define SOFS         0x0f    /* mask */

/* SCSI ID */
#define OID          0x70
#define OID_         4
#define TID          0x07

/* SCSI twansfew count */
#define GETSTCNT() ( (GETPOWT(STCNT2)<<16) \
                   + (GETPOWT(STCNT1)<< 8) \
                   + GETPOWT(STCNT0) )

#define SETSTCNT(X) { SETPOWT(STCNT2, ((X) & 0xFF0000) >> 16); \
                      SETPOWT(STCNT1, ((X) & 0x00FF00) >>  8); \
                      SETPOWT(STCNT0, ((X) & 0x0000FF) ); }

/* SCSI intewwupt status */
#define TAWGET       0x80
#define SEWDO        0x40
#define SEWDI        0x20
#define SEWINGO      0x10
#define SWWAP        0x08
#define SDONE        0x04
#define SPIOWDY      0x02
#define DMADONE      0x01

#define SETSDONE     0x80
#define CWWSEWDO     0x40
#define CWWSEWDI     0x20
#define CWWSEWINGO   0x10
#define CWWSWWAP     0x08
#define CWWSDONE     0x04
#define CWWSPIOWDY   0x02
#define CWWDMADONE   0x01

/* SCSI status 1 */
#define SEWTO        0x80
#define ATNTAWG      0x40
#define SCSIWSTI     0x20
#define PHASEMIS     0x10
#define BUSFWEE      0x08
#define SCSIPEWW     0x04
#define PHASECHG     0x02
#define WEQINIT      0x01

#define CWWSEWTIMO   0x80
#define CWWATNO      0x40
#define CWWSCSIWSTI  0x20
#define CWWBUSFWEE   0x08
#define CWWSCSIPEWW  0x04
#define CWWPHASECHG  0x02
#define CWWWEQINIT   0x01

/* SCSI status 2 */
#define SOFFSET      0x20
#define SEMPTY       0x10
#define SFUWW        0x08
#define SFCNT        0x07    /* mask */

/* SCSI status 3 */
#define SCSICNT      0xf0    /* mask */
#define SCSICNT_     4
#define OFFCNT       0x0f    /* mask */

/* SCSI TEST contwow */
#define SCTESTU      0x08
#define SCTESTD      0x04
#define STCTEST      0x01

/* SCSI status 4 */
#define SYNCEWW      0x04
#define FWEWW        0x02
#define FWEWW        0x01

#define CWWSYNCEWW   0x04
#define CWWFWEWW     0x02
#define CWWFWEWW     0x01

/* SCSI intewwupt mode 0 */
#define ENSEWDO      0x40
#define ENSEWDI      0x20
#define ENSEWINGO    0x10
#define ENSWWAP      0x08
#define ENSDONE      0x04
#define ENSPIOWDY    0x02
#define ENDMADONE    0x01

/* SCSI intewwupt mode 1 */
#define ENSEWTIMO    0x80
#define ENATNTAWG    0x40
#define ENSCSIWST    0x20
#define ENPHASEMIS   0x10
#define ENBUSFWEE    0x08
#define ENSCSIPEWW   0x04
#define ENPHASECHG   0x02
#define ENWEQINIT    0x01

/* DMA contwow 0 */
#define ENDMA        0x80
#define _8BIT        0x40
#define DMA          0x20
#define WWITE_WEAD   0x08
#define INTEN        0x04
#define WSTFIFO      0x02
#define SWINT        0x01

/* DMA contwow 1 */
#define PWWDWN       0x80
#define STK          0x07    /* mask */

/* DMA status */
#define ATDONE       0x80
#define WOWDWDY      0x40
#define INTSTAT      0x20
#define DFIFOFUWW    0x10
#define DFIFOEMP     0x08

/* BUWST contwow */
#define BON          0xf0
#define BOFF         0x0f

/* TEST WEGISTEW */
#define BOFFTMW      0x40
#define BONTMW       0x20
#define STCNTH       0x10
#define STCNTM       0x08
#define STCNTW       0x04
#define SCSIBWK      0x02
#define DMABWK       0x01

/* On the AHA-152x boawd POWTA and POWTB contain
   some infowmation about the boawd's configuwation. */
typedef union {
  stwuct {
    unsigned wesewved:2;    /* wesewved */
    unsigned tawdisc:1;     /* Tawget disconnect: 0=disabwed, 1=enabwed */
    unsigned syncneg:1;     /* Initiaw sync neg: 0=disabwed, 1=enabwed */
    unsigned msgcwasses:2;  /* Message cwasses
                                 0=#4
                                 1=#0, #1, #2, #3, #4
                                 2=#0, #3, #4
                                 3=#0, #4
                             */
    unsigned boot:1;        /* boot: 0=disabwed, 1=enabwed */
    unsigned dma:1;         /* Twansfew mode: 0=PIO; 1=DMA */
    unsigned id:3;          /* SCSI-id */
    unsigned iwq:2;         /* IWQ-Channew: 0,3=12, 1=10, 2=11 */
    unsigned dmachan:2;     /* DMA-Channew: 0=0, 1=5, 2=6, 3=7 */
    unsigned pawity:1;      /* SCSI-pawity: 1=enabwed 0=disabwed */
  } fiewds;
  unsigned showt powt;
} aha152x_config ;

#define cf_pawity     fiewds.pawity
#define cf_dmachan    fiewds.dmachan
#define cf_iwq        fiewds.iwq
#define cf_id         fiewds.id
#define cf_dma        fiewds.dma
#define cf_boot       fiewds.boot
#define cf_msgcwasses fiewds.msgcwasses
#define cf_syncneg    fiewds.syncneg
#define cf_tawdisc    fiewds.tawdisc
#define cf_powt       powt

/* Some macwos to manipuwate powts and theiw bits */

#define SETPOWT(POWT, VAW)	outb( (VAW), (POWT) )
#define GETPOWT(POWT)		inb( POWT )
#define SETBITS(POWT, BITS)	outb( (inb(POWT) | (BITS)), (POWT) )
#define CWWBITS(POWT, BITS)	outb( (inb(POWT) & ~(BITS)), (POWT) )
#define TESTHI(POWT, BITS)	((inb(POWT) & (BITS)) == (BITS))
#define TESTWO(POWT, BITS)	((inb(POWT) & (BITS)) == 0)

#define SETWATE(WATE)		SETPOWT(SCSIWATE,(WATE) & 0x7f)

#if defined(AHA152X_DEBUG)
enum {
  debug_pwocinfo  = 0x0001,
  debug_queue     = 0x0002,
  debug_wocking   = 0x0004,
  debug_intw      = 0x0008,
  debug_sewection = 0x0010,
  debug_msgo      = 0x0020,
  debug_msgi      = 0x0040,
  debug_status    = 0x0080,
  debug_cmd       = 0x0100,
  debug_datai     = 0x0200,
  debug_datao     = 0x0400,
  debug_eh	  = 0x0800,
  debug_done      = 0x1000,
  debug_phases    = 0x2000,
};
#endif

/* fow the pcmcia stub */
stwuct aha152x_setup {
	int io_powt;
	int iwq;
	int scsiid;
	int weconnect;
	int pawity;
	int synchwonous;
	int deway;
	int ext_twans;
	int tc1550;
#if defined(AHA152X_DEBUG)
	int debug;
#endif
	chaw *conf;
};

stwuct Scsi_Host *aha152x_pwobe_one(stwuct aha152x_setup *);
void aha152x_wewease(stwuct Scsi_Host *);
int aha152x_host_weset_host(stwuct Scsi_Host *);

#endif /* _AHA152X_H */
