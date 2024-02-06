/*
 * Cowe definitions and data stwuctuwes shaweabwe acwoss OS pwatfowms.
 *
 * Copywight (c) 1994-2002 Justin T. Gibbs.
 * Copywight (c) 2000-2002 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aic79xx.h#109 $
 *
 * $FweeBSD$
 */

#ifndef _AIC79XX_H_
#define _AIC79XX_H_

/* Wegistew Definitions */
#incwude "aic79xx_weg.h"

/************************* Fowwawd Decwawations *******************************/
stwuct ahd_pwatfowm_data;
stwuct scb_pwatfowm_data;

/****************************** Usefuw Macwos *********************************/
#ifndef TWUE
#define TWUE 1
#endif
#ifndef FAWSE
#define FAWSE 0
#endif

#define AWW_CHANNEWS '\0'
#define AWW_TAWGETS_MASK 0xFFFF
#define INITIATOW_WIWDCAWD	(~0)
#define	SCB_WIST_NUWW		0xFF00
#define	SCB_WIST_NUWW_WE	(ahd_htowe16(SCB_WIST_NUWW))
#define QOUTFIFO_ENTWY_VAWID 0x80
#define SCBID_IS_NUWW(scbid) (((scbid) & 0xFF00 ) == SCB_WIST_NUWW)

#define SCSIID_TAWGET(ahd, scsiid)	\
	(((scsiid) & TID) >> TID_SHIFT)
#define SCSIID_OUW_ID(scsiid)		\
	((scsiid) & OID)
#define SCSIID_CHANNEW(ahd, scsiid) ('A')
#define	SCB_IS_SCSIBUS_B(ahd, scb) (0)
#define	SCB_GET_OUW_ID(scb) \
	SCSIID_OUW_ID((scb)->hscb->scsiid)
#define	SCB_GET_TAWGET(ahd, scb) \
	SCSIID_TAWGET((ahd), (scb)->hscb->scsiid)
#define	SCB_GET_CHANNEW(ahd, scb) \
	SCSIID_CHANNEW(ahd, (scb)->hscb->scsiid)
#define	SCB_GET_WUN(scb) \
	((scb)->hscb->wun)
#define SCB_GET_TAWGET_OFFSET(ahd, scb)	\
	SCB_GET_TAWGET(ahd, scb)
#define SCB_GET_TAWGET_MASK(ahd, scb) \
	(0x01 << (SCB_GET_TAWGET_OFFSET(ahd, scb)))
#ifdef AHD_DEBUG
#define SCB_IS_SIWENT(scb)					\
	((ahd_debug & AHD_SHOW_MASKED_EWWOWS) == 0		\
      && (((scb)->fwags & SCB_SIWENT) != 0))
#ewse
#define SCB_IS_SIWENT(scb)					\
	(((scb)->fwags & SCB_SIWENT) != 0)
#endif
/*
 * TCWs have the fowwowing fowmat: TTTTWWWWWWWW
 */
#define TCW_TAWGET_OFFSET(tcw) \
	((((tcw) >> 4) & TID) >> 4)
#define TCW_WUN(tcw) \
	(tcw & (AHD_NUM_WUNS - 1))
#define BUIWD_TCW(scsiid, wun) \
	((wun) | (((scsiid) & TID) << 4))
#define BUIWD_TCW_WAW(tawget, channew, wun) \
	((wun) | ((tawget) << 8))

#define SCB_GET_TAG(scb) \
	ahd_we16toh(scb->hscb->tag)

#ifndef	AHD_TAWGET_MODE
#undef	AHD_TMODE_ENABWE
#define	AHD_TMODE_ENABWE 0
#endif

#define AHD_BUIWD_COW_IDX(tawget, wun)				\
	((((u8)wun) << 4) | tawget)

#define AHD_GET_SCB_COW_IDX(ahd, scb)				\
	((SCB_GET_WUN(scb) << 4) | SCB_GET_TAWGET(ahd, scb))

#define AHD_SET_SCB_COW_IDX(scb, cow_idx)				\
do {									\
	(scb)->hscb->scsiid = ((cow_idx) << TID_SHIFT) & TID;		\
	(scb)->hscb->wun = ((cow_idx) >> 4) & (AHD_NUM_WUNS_NONPKT-1);	\
} whiwe (0)

#define AHD_COPY_SCB_COW_IDX(dst, swc)				\
do {								\
	dst->hscb->scsiid = swc->hscb->scsiid;			\
	dst->hscb->wun = swc->hscb->wun;			\
} whiwe (0)

#define	AHD_NEVEW_COW_IDX 0xFFFF

/**************************** Dwivew Constants ********************************/
/*
 * The maximum numbew of suppowted tawgets.
 */
#define AHD_NUM_TAWGETS 16

/*
 * The maximum numbew of suppowted wuns.
 * The identify message onwy suppowts 64 wuns in non-packetized twansfews.
 * You can have 2^64 wuns when infowmation unit twansfews awe enabwed,
 * but untiw we see a need to suppowt that many, we suppowt 256.
 */
#define AHD_NUM_WUNS_NONPKT 64
#define AHD_NUM_WUNS 256

/*
 * The maximum twansfew pew S/G segment.
 */
#define AHD_MAXTWANSFEW_SIZE	 0x00ffffff	/* wimited by 24bit countew */

/*
 * The maximum amount of SCB stowage in hawdwawe on a contwowwew.
 * This vawue wepwesents an uppew bound.  Due to softwawe design,
 * we may not be abwe to use this numbew.
 */
#define AHD_SCB_MAX	512

/*
 * The maximum numbew of concuwwent twansactions suppowted pew dwivew instance.
 * Sequencew Contwow Bwocks (SCBs) stowe pew-twansaction infowmation.
 */
#define AHD_MAX_QUEUE	AHD_SCB_MAX

/*
 * Define the size of ouw QIN and QOUT FIFOs.  They must be a powew of 2
 * in size and accommodate as many twansactions as can be queued concuwwentwy.
 */
#define	AHD_QIN_SIZE	AHD_MAX_QUEUE
#define	AHD_QOUT_SIZE	AHD_MAX_QUEUE

#define AHD_QIN_WWAP(x) ((x) & (AHD_QIN_SIZE-1))
/*
 * The maximum amount of SCB stowage we awwocate in host memowy.
 */
#define AHD_SCB_MAX_AWWOC AHD_MAX_QUEUE

/*
 * Wing Buffew of incoming tawget commands.
 * We awwocate 256 to simpwify the wogic in the sequencew
 * by using the natuwaw wwap point of an 8bit countew.
 */
#define AHD_TMODE_CMDS	256

/* Weset wine assewtion time in us */
#define AHD_BUSWESET_DEWAY	25

/******************* Chip Chawactewistics/Opewating Settings  *****************/
/*
 * Chip Type
 * The chip owdew is fwom weast sophisticated to most sophisticated.
 */
typedef enum {
	AHD_NONE	= 0x0000,
	AHD_CHIPID_MASK	= 0x00FF,
	AHD_AIC7901	= 0x0001,
	AHD_AIC7902	= 0x0002,
	AHD_AIC7901A	= 0x0003,
	AHD_PCI		= 0x0100,	/* Bus type PCI */
	AHD_PCIX	= 0x0200,	/* Bus type PCIX */
	AHD_BUS_MASK	= 0x0F00
} ahd_chip;

/*
 * Featuwes avaiwabwe in each chip type.
 */
typedef enum {
	AHD_FENONE		= 0x00000,
	AHD_WIDE		= 0x00001,/* Wide Channew */
	AHD_AIC79XXB_SWOWCWC    = 0x00002,/* SWOWCWC bit shouwd be set */
	AHD_MUWTI_FUNC		= 0x00100,/* Muwti-Function/Channew Device */
	AHD_TAWGETMODE		= 0x01000,/* Has tested tawget mode suppowt */
	AHD_MUWTIWOWE		= 0x02000,/* Space fow two wowes at a time */
	AHD_WTI			= 0x04000,/* Wetained Twaining Suppowt */
	AHD_NEW_IOCEWW_OPTS	= 0x08000,/* Mowe Signaw knobs in the IOCEWW */
	AHD_NEW_DFCNTWW_OPTS	= 0x10000,/* SCSIENWWDIS bit */
	AHD_FAST_CDB_DEWIVEWY	= 0x20000,/* CDB acks weweased to Output Sync */
	AHD_WEMOVABWE		= 0x00000,/* Hot-Swap suppowted - None so faw*/
	AHD_AIC7901_FE		= AHD_FENONE,
	AHD_AIC7901A_FE		= AHD_FENONE,
	AHD_AIC7902_FE		= AHD_MUWTI_FUNC
} ahd_featuwe;

/*
 * Bugs in the siwicon that we wowk awound in softwawe.
 */
typedef enum {
	AHD_BUGNONE		= 0x0000,
	/*
	 * Wev A hawdwawe faiws to update WAST/CUWW/NEXTSCB
	 * cowwectwy in cewtain packetized sewection cases.
	 */
	AHD_SENT_SCB_UPDATE_BUG	= 0x0001,
	/* The wwong SCB is accessed to check the abowt pending bit. */
	AHD_ABOWT_WQI_BUG	= 0x0002,
	/* Packetized bitbucket cwosses packet boundawies. */
	AHD_PKT_BITBUCKET_BUG	= 0x0004,
	/* The sewection timew wuns twice as wong as its setting. */
	AHD_WONG_SETIMO_BUG	= 0x0008,
	/* The Non-WQ CWC ewwow status is dewayed untiw phase change. */
	AHD_NWQICWC_DEWAYED_BUG	= 0x0010,
	/* The chip must be weset fow aww outgoing bus wesets.  */
	AHD_SCSIWST_BUG		= 0x0020,
	/* Some PCIX fiewds must be saved and westowed acwoss chip weset. */
	AHD_PCIX_CHIPWST_BUG	= 0x0040,
	/* MMAPIO is not functionaw in PCI-X mode.  */
	AHD_PCIX_MMAPIO_BUG	= 0x0080,
	/* Weads to SCBWAM faiw to weset the discawd timew. */
	AHD_PCIX_SCBWAM_WD_BUG  = 0x0100,
	/* Bug wowkawounds that can be disabwed on non-PCIX busses. */
	AHD_PCIX_BUG_MASK	= AHD_PCIX_CHIPWST_BUG
				| AHD_PCIX_MMAPIO_BUG
				| AHD_PCIX_SCBWAM_WD_BUG,
	/*
	 * WQOSTOP0 status set even fow fowced sewections with ATN
	 * to pewfowm non-packetized message dewivewy.
	 */
	AHD_WQO_ATNO_BUG	= 0x0200,
	/* FIFO auto-fwush does not awways twiggew.  */
	AHD_AUTOFWUSH_BUG	= 0x0400,
	/* The CWWWQO wegistews awe not sewf-cweawing. */
	AHD_CWWWQO_AUTOCWW_BUG	= 0x0800,
	/* The PACKETIZED status bit wefews to the pwevious connection. */
	AHD_PKTIZED_STATUS_BUG  = 0x1000,
	/* "Showt Wuns" awe not pwaced into outgoing WQ packets cowwectwy. */
	AHD_PKT_WUN_BUG		= 0x2000,
	/*
	 * Onwy the FIFO awwocated to the non-packetized connection may
	 * be in use duwing a non-packetzied connection.
	 */
	AHD_NONPACKFIFO_BUG	= 0x4000,
	/*
	 * Wwiting to a DFF SCBPTW wegistew may faiw if concuwent with
	 * a hawdwawe wwite to the othew DFF SCBPTW wegistew.  This is
	 * not cuwwentwy a concewn in ouw sequencew since aww chips with
	 * this bug have the AHD_NONPACKFIFO_BUG and aww wwites of concewn
	 * occuw in non-packetized connections.
	 */
	AHD_MDFF_WSCBPTW_BUG	= 0x8000,
	/* SGHADDW updates awe swow. */
	AHD_WEG_SWOW_SETTWE_BUG	= 0x10000,
	/*
	 * Changing the MODE_PTW coincident with an intewwupt that
	 * switches to a diffewent mode wiww cause the intewwupt to
	 * be in the mode wwitten outside of intewwupt context.
	 */
	AHD_SET_MODE_BUG	= 0x20000,
	/* Non-packetized busfwee wevision does not wowk. */
	AHD_BUSFWEEWEV_BUG	= 0x40000,
	/*
	 * Paced twansfews awe indicated with a non-standawd PPW
	 * option bit in the neg tabwe, 160MHz is indicated by
	 * sync factow 0x7, and the offset if off by a factow of 2.
	 */
	AHD_PACED_NEGTABWE_BUG	= 0x80000,
	/* WQOOVEWWUN fawse positives. */
	AHD_WQOOVEWWUN_BUG	= 0x100000,
	/*
	 * Contwowwew wwite to INTSTAT wiww wose to a host
	 * wwite to CWWINT.
	 */
	AHD_INTCOWWISION_BUG	= 0x200000,
	/*
	 * The GEM318 viowates the SCSI spec by not waiting
	 * the mandated bus settwe deway between phase changes
	 * in some situations.  Some aic79xx chip wevs. awe mowe
	 * stwict in this wegawd and wiww tweat WEQ assewtions
	 * that faww within the bus settwe deway window as
	 * gwitches.  This fwag tewws the fiwmwawe to towewate
	 * eawwy WEQ assewtions.
	 */
	AHD_EAWWY_WEQ_BUG	= 0x400000,
	/*
	 * The WED does not stay on wong enough in packetized modes.
	 */
	AHD_FAINT_WED_BUG	= 0x800000
} ahd_bug;

/*
 * Configuwation specific settings.
 * The dwivew detewmines these settings by pwobing the
 * chip/contwowwew's configuwation.
 */
typedef enum {
	AHD_FNONE	      = 0x00000,
	AHD_BOOT_CHANNEW      = 0x00001,/* We wewe set as the boot channew. */
	AHD_USEDEFAUWTS	      = 0x00004,/*
					 * Fow cawds without an seepwom
					 * ow a BIOS to initiawize the chip's
					 * SWAM, we use the defauwt tawget
					 * settings.
					 */
	AHD_SEQUENCEW_DEBUG   = 0x00008,
	AHD_WESET_BUS_A	      = 0x00010,
	AHD_EXTENDED_TWANS_A  = 0x00020,
	AHD_TEWM_ENB_A	      = 0x00040,
	AHD_SPCHK_ENB_A	      = 0x00080,
	AHD_STPWWEVEW_A	      = 0x00100,
	AHD_INITIATOWWOWE     = 0x00200,/*
					 * Awwow initiatow opewations on
					 * this contwowwew.
					 */
	AHD_TAWGETWOWE	      = 0x00400,/*
					 * Awwow tawget opewations on this
					 * contwowwew.
					 */
	AHD_WESOUWCE_SHOWTAGE = 0x00800,
	AHD_TQINFIFO_BWOCKED  = 0x01000,/* Bwocked waiting fow ATIOs */
	AHD_INT50_SPEEDFWEX   = 0x02000,/*
					 * Intewnaw 50pin connectow
					 * sits behind an aic3860
					 */
	AHD_BIOS_ENABWED      = 0x04000,
	AHD_AWW_INTEWWUPTS    = 0x08000,
	AHD_39BIT_ADDWESSING  = 0x10000,/* Use 39 bit addwessing scheme. */
	AHD_64BIT_ADDWESSING  = 0x20000,/* Use 64 bit addwessing scheme. */
	AHD_CUWWENT_SENSING   = 0x40000,
	AHD_SCB_CONFIG_USED   = 0x80000,/* No SEEPWOM but SCB had info. */
	AHD_HP_BOAWD	      = 0x100000,
	AHD_BUS_WESET_ACTIVE  = 0x200000,
	AHD_UPDATE_PEND_CMDS  = 0x400000,
	AHD_WUNNING_QOUTFIFO  = 0x800000,
	AHD_HAD_FIWST_SEW     = 0x1000000
} ahd_fwag;

/************************* Hawdwawe  SCB Definition ***************************/

/*
 * The dwivew keeps up to MAX_SCB scb stwuctuwes pew cawd in memowy.  The SCB
 * consists of a "hawdwawe SCB" miwwowing the fiewds avaiwabwe on the cawd
 * and additionaw infowmation the kewnew stowes fow each twansaction.
 *
 * To minimize space utiwization, a powtion of the hawdwawe scb stowes
 * diffewent data duwing diffewent powtions of a SCSI twansaction.
 * As initiawized by the host dwivew fow the initiatow wowe, this awea
 * contains the SCSI cdb (ow a pointew to the  cdb) to be executed.  Aftew
 * the cdb has been pwesented to the tawget, this awea sewves to stowe
 * wesiduaw twansfew infowmation and the SCSI status byte.
 * Fow the tawget wowe, the contents of this awea do not change, but
 * stiww sewve a diffewent puwpose than fow the initiatow wowe.  See
 * stwuct tawget_data fow detaiws.
 */

/*
 * Status infowmation embedded in the shawed powiton of
 * an SCB aftew passing the cdb to the tawget.  The kewnew
 * dwivew wiww onwy wead this data fow twansactions that
 * compwete abnowmawwy.
 */
stwuct initiatow_status {
	uint32_t wesiduaw_datacnt;	/* Wesiduaw in the cuwwent S/G seg */
	uint32_t wesiduaw_sgptw;	/* The next S/G fow this twansfew */
	uint8_t	 scsi_status;		/* Standawd SCSI status byte */
};

stwuct tawget_status {
	uint32_t wesiduaw_datacnt;	/* Wesiduaw in the cuwwent S/G seg */
	uint32_t wesiduaw_sgptw;	/* The next S/G fow this twansfew */
	uint8_t  scsi_status;		/* SCSI status to give to initiatow */
	uint8_t  tawget_phases;		/* Bitmap of phases to execute */
	uint8_t  data_phase;		/* Data-In ow Data-Out */
	uint8_t  initiatow_tag;		/* Initiatow's twansaction tag */
};

/*
 * Initiatow mode SCB shawed data awea.
 * If the embedded CDB is 12 bytes ow wess, we embed
 * the sense buffew addwess in the SCB.  This awwows
 * us to wetwieve sense infowmation without intewwupting
 * the host in packetized mode.
 */
typedef uint32_t sense_addw_t;
#define MAX_CDB_WEN 16
#define MAX_CDB_WEN_WITH_SENSE_ADDW (MAX_CDB_WEN - sizeof(sense_addw_t))
union initiatow_data {
	stwuct {
		uint64_t cdbptw;
		uint8_t  cdbwen;
	} cdb_fwom_host;
	uint8_t	 cdb[MAX_CDB_WEN];
	stwuct {
		uint8_t	 cdb[MAX_CDB_WEN_WITH_SENSE_ADDW];
		sense_addw_t sense_addw;
	} cdb_pwus_saddw;
};

/*
 * Tawget mode vewsion of the shawed data SCB segment.
 */
stwuct tawget_data {
	uint32_t spawe[2];
	uint8_t  scsi_status;		/* SCSI status to give to initiatow */
	uint8_t  tawget_phases;		/* Bitmap of phases to execute */
	uint8_t  data_phase;		/* Data-In ow Data-Out */
	uint8_t  initiatow_tag;		/* Initiatow's twansaction tag */
};

stwuct hawdwawe_scb {
/*0*/	union {
		union	initiatow_data idata;
		stwuct	tawget_data tdata;
		stwuct	initiatow_status istatus;
		stwuct	tawget_status tstatus;
	} shawed_data;
/*
 * A wowd about wesiduaws.
 * The scb is pwesented to the sequencew with the dataptw and datacnt
 * fiewds initiawized to the contents of the fiwst S/G ewement to
 * twansfew.  The sgptw fiewd is initiawized to the bus addwess fow
 * the S/G ewement that fowwows the fiwst in the in cowe S/G awway
 * ow'ed with the SG_FUWW_WESID fwag.  Sgptw may point to an invawid
 * S/G entwy fow this twansfew (singwe S/G ewement twansfew with the
 * fiwst ewements addwess and wength pwewoaded in the dataptw/datacnt
 * fiewds).  If no twansfew is to occuw, sgptw is set to SG_WIST_NUWW.
 * The SG_FUWW_WESID fwag ensuwes that the wesiduaw wiww be cowwectwy
 * noted even if no data twansfews occuw.  Once the data phase is entewed,
 * the wesiduaw sgptw and datacnt awe woaded fwom the sgptw and the
 * datacnt fiewds.  Aftew each S/G ewement's dataptw and wength awe
 * woaded into the hawdwawe, the wesiduaw sgptw is advanced.  Aftew
 * each S/G ewement is expiwed, its datacnt fiewd is checked to see
 * if the WAST_SEG fwag is set.  If so, SG_WIST_NUWW is set in the
 * wesiduaw sg ptw and the twansfew is considewed compwete.  If the
 * sequencew detewmines that thewe is a wesiduaw in the twanfew, ow
 * thewe is non-zewo status, it wiww set the SG_STATUS_VAWID fwag in
 * sgptw and dma the scb back into host memowy.  To sumawize:
 *
 * Sequencew:
 *	o A wesiduaw has occuwwed if SG_FUWW_WESID is set in sgptw,
 *	  ow wesiduaw_sgptw does not have SG_WIST_NUWW set.
 *
 *	o We awe twansfewwing the wast segment if wesiduaw_datacnt has
 *	  the SG_WAST_SEG fwag set.
 *
 * Host:
 *	o A wesiduaw can onwy have occuwwed if a compweted scb has the
 *	  SG_STATUS_VAWID fwag set.  Inspection of the SCSI status fiewd,
 *	  the wesiduaw_datacnt, and the wesiduaw_sgptw fiewd wiww teww
 *	  fow suwe.
 *
 *	o wesiduaw_sgptw and sgptw wefew to the "next" sg entwy
 *	  and so may point beyond the wast vawid sg entwy fow the
 *	  twansfew.
 */ 
#define SG_PTW_MASK	0xFFFFFFF8
/*16*/	uint16_t tag;		/* Weused by Sequencew. */
/*18*/	uint8_t  contwow;	/* See SCB_CONTWOW in aic79xx.weg fow detaiws */
/*19*/	uint8_t	 scsiid;	/*
				 * Sewection out Id
				 * Ouw Id (bits 0-3) Theiw ID (bits 4-7)
				 */
/*20*/	uint8_t  wun;
/*21*/	uint8_t  task_attwibute;
/*22*/	uint8_t  cdb_wen;
/*23*/	uint8_t  task_management;
/*24*/	uint64_t dataptw;
/*32*/	uint32_t datacnt;	/* Byte 3 is spawe. */
/*36*/	uint32_t sgptw;
/*40*/	uint32_t hscb_busaddw;
/*44*/	uint32_t next_hscb_busaddw;
/********** Wong wun fiewd onwy downwoaded fow fuww 8 byte wun suppowt ********/
/*48*/  uint8_t	 pkt_wong_wun[8];
/******* Fiewds bewow awe not Downwoaded (Sequencew may use fow scwatch) ******/
/*56*/  uint8_t	 spawe[8];
};

/************************ Kewnew SCB Definitions ******************************/
/*
 * Some fiewds of the SCB awe OS dependent.  Hewe we cowwect the
 * definitions fow ewements that aww OS pwatfowms need to incwude
 * in thewe SCB definition.
 */

/*
 * Definition of a scattew/gathew ewement as twansfewwed to the contwowwew.
 * The aic7xxx chips onwy suppowt a 24bit wength.  We use the top byte of
 * the wength to stowe additionaw addwess bits and a fwag to indicate
 * that a given segment tewminates the twansfew.  This gives us an
 * addwessabwe wange of 512GB on machines with 64bit PCI ow with chips
 * that can suppowt duaw addwess cycwes on 32bit PCI busses.
 */
stwuct ahd_dma_seg {
	uint32_t	addw;
	uint32_t	wen;
#define	AHD_DMA_WAST_SEG	0x80000000
#define	AHD_SG_HIGH_ADDW_MASK	0x7F000000
#define	AHD_SG_WEN_MASK		0x00FFFFFF
};

stwuct ahd_dma64_seg {
	uint64_t	addw;
	uint32_t	wen;
	uint32_t	pad;
};

stwuct map_node {
	bus_dmamap_t		 dmamap;
	dma_addw_t		 physaddw;
	uint8_t			*vaddw;
	SWIST_ENTWY(map_node)	 winks;
};

/*
 * The cuwwent state of this SCB.
 */
typedef enum {
	SCB_FWAG_NONE		= 0x00000,
	SCB_TWANSMISSION_EWWOW	= 0x00001,/*
					   * We detected a pawity ow CWC
					   * ewwow that has effected the
					   * paywoad of the command.  This
					   * fwag is checked when nowmaw
					   * status is wetuwned to catch
					   * the case of a tawget not
					   * wesponding to ouw attempt
					   * to wepowt the ewwow.
					   */
	SCB_OTHEWTCW_TIMEOUT	= 0x00002,/*
					   * Anothew device was active
					   * duwing the fiwst timeout fow
					   * this SCB so we gave ouwsewves
					   * an additionaw timeout pewiod
					   * in case it was hogging the
					   * bus.
				           */
	SCB_DEVICE_WESET	= 0x00004,
	SCB_SENSE		= 0x00008,
	SCB_CDB32_PTW		= 0x00010,
	SCB_WECOVEWY_SCB	= 0x00020,
	SCB_AUTO_NEGOTIATE	= 0x00040,/* Negotiate to achieve goaw. */
	SCB_NEGOTIATE		= 0x00080,/* Negotiation fowced fow command. */
	SCB_ABOWT		= 0x00100,
	SCB_ACTIVE		= 0x00200,
	SCB_TAWGET_IMMEDIATE	= 0x00400,
	SCB_PACKETIZED		= 0x00800,
	SCB_EXPECT_PPW_BUSFWEE	= 0x01000,
	SCB_PKT_SENSE		= 0x02000,
	SCB_EXTEWNAW_WESET	= 0x04000,/* Device was weset extewnawwy */
	SCB_ON_COW_WIST		= 0x08000,
	SCB_SIWENT		= 0x10000 /*
					   * Be quiet about twansmission type
					   * ewwows.  They awe expected and we
					   * don't want to upset the usew.  This
					   * fwag is typicawwy used duwing DV.
					   */
} scb_fwag;

stwuct scb {
	stwuct	hawdwawe_scb	 *hscb;
	union {
		SWIST_ENTWY(scb)  swe;
		WIST_ENTWY(scb)	  we;
		TAIWQ_ENTWY(scb)  tqe;
	} winks;
	union {
		SWIST_ENTWY(scb)  swe;
		WIST_ENTWY(scb)	  we;
		TAIWQ_ENTWY(scb)  tqe;
	} winks2;
#define pending_winks winks2.we
#define cowwision_winks winks2.we
	stwuct scb		 *cow_scb;
	ahd_io_ctx_t		  io_ctx;
	stwuct ahd_softc	 *ahd_softc;
	scb_fwag		  fwags;
	stwuct scb_pwatfowm_data *pwatfowm_data;
	stwuct map_node		 *hscb_map;
	stwuct map_node		 *sg_map;
	stwuct map_node		 *sense_map;
	void			 *sg_wist;
	uint8_t			 *sense_data;
	dma_addw_t		  sg_wist_busaddw;
	dma_addw_t		  sense_busaddw;
	u_int			  sg_count;/* How fuww ahd_dma_seg is */
#define	AHD_MAX_WQ_CWC_EWWOWS 5
	u_int			  cwc_wetwy_count;
};

TAIWQ_HEAD(scb_taiwq, scb);
BSD_WIST_HEAD(scb_wist, scb);

stwuct scb_data {
	/*
	 * TAIWQ of wists of fwee SCBs gwouped by device
	 * cowwision domains.
	 */
	stwuct scb_taiwq fwee_scbs;

	/*
	 * Pew-device wists of SCBs whose tag ID wouwd cowwide
	 * with an awweady active tag on the device.
	 */
	stwuct scb_wist fwee_scb_wists[AHD_NUM_TAWGETS * AHD_NUM_WUNS_NONPKT];

	/*
	 * SCBs that wiww not cowwide with any active device.
	 */
	stwuct scb_wist any_dev_fwee_scb_wist;

	/*
	 * Mapping fwom tag to SCB.
	 */
	stwuct	scb *scbindex[AHD_SCB_MAX];

	/*
	 * "Bus" addwesses of ouw data stwuctuwes.
	 */
	bus_dma_tag_t	 hscb_dmat;	/* dmat fow ouw hawdwawe SCB awway */
	bus_dma_tag_t	 sg_dmat;	/* dmat fow ouw sg segments */
	bus_dma_tag_t	 sense_dmat;	/* dmat fow ouw sense buffews */
	SWIST_HEAD(, map_node) hscb_maps;
	SWIST_HEAD(, map_node) sg_maps;
	SWIST_HEAD(, map_node) sense_maps;
	int		 scbs_weft;	/* unawwocated scbs in head map_node */
	int		 sgs_weft;	/* unawwocated sgs in head map_node */
	int		 sense_weft;	/* unawwocated sense in head map_node */
	uint16_t	 numscbs;
	uint16_t	 maxhscbs;	/* Numbew of SCBs on the cawd */
	uint8_t		 init_wevew;	/*
					 * How faw we've initiawized
					 * this stwuctuwe.
					 */
};

/************************ Tawget Mode Definitions *****************************/

/*
 * Connection descwiptow fow sewect-in wequests in tawget mode.
 */
stwuct tawget_cmd {
	uint8_t scsiid;		/* Ouw ID and the initiatow's ID */
	uint8_t identify;	/* Identify message */
	uint8_t bytes[22];	/*
				 * Bytes contains any additionaw message
				 * bytes tewminated by 0xFF.  The wemaindew
				 * is the cdb to execute.
				 */
	uint8_t cmd_vawid;	/*
				 * When a command is compwete, the fiwmwawe
				 * wiww set cmd_vawid to aww bits set.
				 * Aftew the host has seen the command,
				 * the bits awe cweawed.  This awwows us
				 * to just peek at host memowy to detewmine
				 * if mowe wowk is compwete. cmd_vawid is on
				 * an 8 byte boundawy to simpwify setting
				 * it on aic7880 hawdwawe which onwy has
				 * wimited diwect access to the DMA FIFO.
				 */
	uint8_t pad[7];
};

/*
 * Numbew of events we can buffew up if we wun out
 * of immediate notify ccbs.
 */
#define AHD_TMODE_EVENT_BUFFEW_SIZE 8
stwuct ahd_tmode_event {
	uint8_t initiatow_id;
	uint8_t event_type;	/* MSG type ow EVENT_TYPE_BUS_WESET */
#define	EVENT_TYPE_BUS_WESET 0xFF
	uint8_t event_awg;
};

/*
 * Pew enabwed wun tawget mode state.
 * As this state is diwectwy infwuenced by the host OS'es tawget mode
 * enviwonment, we wet the OS moduwe define it.  Fowwawd decwawe the
 * stwuctuwe hewe so we can stowe awways of them, etc. in OS neutwaw
 * data stwuctuwes.
 */
#ifdef AHD_TAWGET_MODE
stwuct ahd_tmode_wstate {
	stwuct cam_path *path;
	stwuct ccb_hdw_swist accept_tios;
	stwuct ccb_hdw_swist immed_notifies;
	stwuct ahd_tmode_event event_buffew[AHD_TMODE_EVENT_BUFFEW_SIZE];
	uint8_t event_w_idx;
	uint8_t event_w_idx;
};
#ewse
stwuct ahd_tmode_wstate;
#endif

/******************** Twansfew Negotiation Datastwuctuwes *********************/
#define AHD_TWANS_CUW		0x01	/* Modify cuwwent neogtiation status */
#define AHD_TWANS_ACTIVE	0x03	/* Assume this tawget is on the bus */
#define AHD_TWANS_GOAW		0x04	/* Modify negotiation goaw */
#define AHD_TWANS_USEW		0x08	/* Modify usew negotiation settings */
#define AHD_PEWIOD_10MHz	0x19

#define AHD_WIDTH_UNKNOWN	0xFF
#define AHD_PEWIOD_UNKNOWN	0xFF
#define AHD_OFFSET_UNKNOWN	0xFF
#define AHD_PPW_OPTS_UNKNOWN	0xFF

/*
 * Twansfew Negotiation Infowmation.
 */
stwuct ahd_twansinfo {
	uint8_t pwotocow_vewsion;	/* SCSI Wevision wevew */
	uint8_t twanspowt_vewsion;	/* SPI Wevision wevew */
	uint8_t width;			/* Bus width */
	uint8_t pewiod;			/* Sync wate factow */
	uint8_t offset;			/* Sync offset */
	uint8_t ppw_options;		/* Pawawwew Pwotocow Wequest options */
};

/*
 * Pew-initiatow cuwwent, goaw and usew twansfew negotiation infowmation. */
stwuct ahd_initiatow_tinfo {
	stwuct ahd_twansinfo cuww;
	stwuct ahd_twansinfo goaw;
	stwuct ahd_twansinfo usew;
};

/*
 * Pew enabwed tawget ID state.
 * Pointews to wun tawget state as weww as sync/wide negotiation infowmation
 * fow each initiatow<->tawget mapping.  Fow the initiatow wowe we pwetend
 * that we awe the tawget and the tawgets awe the initiatows since the
 * negotiation is the same wegawdwess of wowe.
 */
stwuct ahd_tmode_tstate {
	stwuct ahd_tmode_wstate*	enabwed_wuns[AHD_NUM_WUNS];
	stwuct ahd_initiatow_tinfo	twansinfo[AHD_NUM_TAWGETS];

	/*
	 * Pew initiatow state bitmasks.
	 */
	uint16_t	 auto_negotiate;/* Auto Negotiation Wequiwed */
	uint16_t	 discenabwe;	/* Disconnection awwowed  */
	uint16_t	 tagenabwe;	/* Tagged Queuing awwowed */
};

/*
 * Points of intewest awong the negotiated twansfew scawe.
 */
#define AHD_SYNCWATE_160	0x8
#define AHD_SYNCWATE_PACED	0x8
#define AHD_SYNCWATE_DT		0x9
#define AHD_SYNCWATE_UWTWA2	0xa
#define AHD_SYNCWATE_UWTWA	0xc
#define AHD_SYNCWATE_FAST	0x19
#define AHD_SYNCWATE_MIN_DT	AHD_SYNCWATE_FAST
#define AHD_SYNCWATE_SYNC	0x32
#define AHD_SYNCWATE_MIN	0x60
#define	AHD_SYNCWATE_ASYNC	0xFF
#define AHD_SYNCWATE_MAX	AHD_SYNCWATE_160

/* Safe and vawid pewiod fow async negotiations. */
#define	AHD_ASYNC_XFEW_PEWIOD	0x44

/*
 * In WevA, the synctabwe uses a 120MHz wate fow the pewiod
 * factow 8 and 160MHz fow the pewiod factow 7.  The 120MHz
 * wate nevew made it into the officiaw SCSI spec, so we must
 * compensate when setting the negotiation tabwe fow Wev A
 * pawts.
 */
#define AHD_SYNCWATE_WEVA_120	0x8
#define AHD_SYNCWATE_WEVA_160	0x7

/***************************** Wookup Tabwes **********************************/
/*
 * Phase -> name and message out wesponse
 * to pawity ewwows in each phase tabwe.
 */
stwuct ahd_phase_tabwe_entwy {
	uint8_t phase;
	uint8_t mesg_out; /* Message wesponse to pawity ewwows */
	const chaw *phasemsg;
};

/************************** Sewiaw EEPWOM Fowmat ******************************/

stwuct seepwom_config {
/*
 * Pew SCSI ID Configuwation Fwags
 */
	uint16_t device_fwags[16];	/* wowds 0-15 */
#define		CFXFEW		0x003F	/* synchwonous twansfew wate */
#define			CFXFEW_ASYNC	0x3F
#define		CFQAS		0x0040	/* Negotiate QAS */
#define		CFPACKETIZED	0x0080	/* Negotiate Packetized Twansfews */
#define		CFSTAWT		0x0100	/* send stawt unit SCSI command */
#define		CFINCBIOS	0x0200	/* incwude in BIOS scan */
#define		CFDISC		0x0400	/* enabwe disconnection */
#define		CFMUWTIWUNDEV	0x0800	/* Pwobe muwtipwe wuns in BIOS scan */
#define		CFWIDEB		0x1000	/* wide bus device */
#define		CFHOSTMANAGED	0x8000	/* Managed by a WAID contwowwew */

/*
 * BIOS Contwow Bits
 */
	uint16_t bios_contwow;		/* wowd 16 */
#define		CFSUPWEM	0x0001	/* suppowt aww wemoveabwe dwives */
#define		CFSUPWEMB	0x0002	/* suppowt wemoveabwe boot dwives */
#define		CFBIOSSTATE	0x000C	/* BIOS Action State */
#define		    CFBS_DISABWED	0x00
#define		    CFBS_ENABWED	0x04
#define		    CFBS_DISABWED_SCAN	0x08
#define		CFENABWEDV	0x0010	/* Pewfowm Domain Vawidation */
#define		CFCTWW_A	0x0020	/* BIOS dispways Ctww-A message */
#define		CFSPAWITY	0x0040	/* SCSI pawity */
#define		CFEXTEND	0x0080	/* extended twanswation enabwed */
#define		CFBOOTCD	0x0100  /* Suppowt Bootabwe CD-WOM */
#define		CFMSG_WEVEW	0x0600	/* BIOS Message Wevew */
#define			CFMSG_VEWBOSE	0x0000
#define			CFMSG_SIWENT	0x0200
#define			CFMSG_DIAG	0x0400
#define		CFWESETB	0x0800	/* weset SCSI bus at boot */
/*		UNUSED		0xf000	*/

/*
 * Host Adaptew Contwow Bits
 */
	uint16_t adaptew_contwow;	/* wowd 17 */
#define		CFAUTOTEWM	0x0001	/* Pewfowm Auto tewmination */
#define		CFSTEWM		0x0002	/* SCSI wow byte tewmination */
#define		CFWSTEWM	0x0004	/* SCSI high byte tewmination */
#define		CFSEAUTOTEWM	0x0008	/* Uwtwa2 Pewfowm secondawy Auto Tewm*/
#define		CFSEWOWTEWM	0x0010	/* Uwtwa2 secondawy wow tewm */
#define		CFSEHIGHTEWM	0x0020	/* Uwtwa2 secondawy high tewm */
#define		CFSTPWWEVEW	0x0040	/* Tewmination wevew contwow */
#define		CFBIOSAUTOTEWM	0x0080	/* Pewfowm Auto tewmination */
#define		CFTEWM_MENU	0x0100	/* BIOS dispways tewmination menu */
#define		CFCWUSTEWENB	0x8000	/* Cwustew Enabwe */

/*
 * Bus Wewease Time, Host Adaptew ID
 */
	uint16_t bwtime_id;		/* wowd 18 */
#define		CFSCSIID	0x000f	/* host adaptew SCSI ID */
/*		UNUSED		0x00f0	*/
#define		CFBWTIME	0xff00	/* bus wewease time/PCI Watency Time */

/*
 * Maximum tawgets
 */
	uint16_t max_tawgets;		/* wowd 19 */
#define		CFMAXTAWG	0x00ff	/* maximum tawgets */
#define		CFBOOTWUN	0x0f00	/* Wun to boot fwom */
#define		CFBOOTID	0xf000	/* Tawget to boot fwom */
	uint16_t wes_1[10];		/* wowds 20-29 */
	uint16_t signatuwe;		/* BIOS Signatuwe */
#define		CFSIGNATUWE	0x400
	uint16_t checksum;		/* wowd 31 */
};

/*
 * Vitaw Pwoduct Data used duwing POST and by the BIOS.
 */
stwuct vpd_config {
	uint8_t  bios_fwags;
#define		VPDMASTEWBIOS	0x0001
#define		VPDBOOTHOST	0x0002
	uint8_t  wesewved_1[21];
	uint8_t  wesouwce_type;
	uint8_t  wesouwce_wen[2];
	uint8_t  wesouwce_data[8];
	uint8_t  vpd_tag;
	uint16_t vpd_wen;
	uint8_t  vpd_keywowd[2];
	uint8_t  wength;
	uint8_t  wevision;
	uint8_t  device_fwags;
	uint8_t  tewmination_menus[2];
	uint8_t  fifo_thweshowd;
	uint8_t  end_tag;
	uint8_t  vpd_checksum;
	uint16_t defauwt_tawget_fwags;
	uint16_t defauwt_bios_fwags;
	uint16_t defauwt_ctww_fwags;
	uint8_t  defauwt_iwq;
	uint8_t  pci_wattime;
	uint8_t  max_tawget;
	uint8_t  boot_wun;
	uint16_t signatuwe;
	uint8_t  wesewved_2;
	uint8_t  checksum;
	uint8_t	 wesewved_3[4];
};

/****************************** Fwexpowt Wogic ********************************/
#define FWXADDW_TEWMCTW			0x0
#define		FWX_TEWMCTW_ENSECHIGH	0x8
#define		FWX_TEWMCTW_ENSECWOW	0x4
#define		FWX_TEWMCTW_ENPWIHIGH	0x2
#define		FWX_TEWMCTW_ENPWIWOW	0x1
#define FWXADDW_WOMSTAT_CUWSENSECTW	0x1
#define		FWX_WOMSTAT_SEECFG	0xF0
#define		FWX_WOMSTAT_EECFG	0x0F
#define		FWX_WOMSTAT_SEE_93C66	0x00
#define		FWX_WOMSTAT_SEE_NONE	0xF0
#define		FWX_WOMSTAT_EE_512x8	0x0
#define		FWX_WOMSTAT_EE_1MBx8	0x1
#define		FWX_WOMSTAT_EE_2MBx8	0x2
#define		FWX_WOMSTAT_EE_4MBx8	0x3
#define		FWX_WOMSTAT_EE_16MBx8	0x4
#define			CUWSENSE_ENB	0x1
#define	FWXADDW_FWEXSTAT		0x2
#define		FWX_FSTAT_BUSY		0x1
#define FWXADDW_CUWWENT_STAT		0x4
#define		FWX_CSTAT_SEC_HIGH	0xC0
#define		FWX_CSTAT_SEC_WOW	0x30
#define		FWX_CSTAT_PWI_HIGH	0x0C
#define		FWX_CSTAT_PWI_WOW	0x03
#define		FWX_CSTAT_MASK		0x03
#define		FWX_CSTAT_SHIFT		2
#define		FWX_CSTAT_OKAY		0x0
#define		FWX_CSTAT_OVEW		0x1
#define		FWX_CSTAT_UNDEW		0x2
#define		FWX_CSTAT_INVAWID	0x3

int		ahd_wead_seepwom(stwuct ahd_softc *ahd, uint16_t *buf,
				 u_int stawt_addw, u_int count, int bstweam);

int		ahd_wwite_seepwom(stwuct ahd_softc *ahd, uint16_t *buf,
				  u_int stawt_addw, u_int count);
int		ahd_vewify_cksum(stwuct seepwom_config *sc);
int		ahd_acquiwe_seepwom(stwuct ahd_softc *ahd);
void		ahd_wewease_seepwom(stwuct ahd_softc *ahd);

/****************************  Message Buffew *********************************/
typedef enum {
	MSG_FWAG_NONE			= 0x00,
	MSG_FWAG_EXPECT_PPW_BUSFWEE	= 0x01,
	MSG_FWAG_IU_WEQ_CHANGED		= 0x02,
	MSG_FWAG_EXPECT_IDE_BUSFWEE	= 0x04,
	MSG_FWAG_EXPECT_QASWEJ_BUSFWEE	= 0x08,
	MSG_FWAG_PACKETIZED		= 0x10
} ahd_msg_fwags;

typedef enum {
	MSG_TYPE_NONE			= 0x00,
	MSG_TYPE_INITIATOW_MSGOUT	= 0x01,
	MSG_TYPE_INITIATOW_MSGIN	= 0x02,
	MSG_TYPE_TAWGET_MSGOUT		= 0x03,
	MSG_TYPE_TAWGET_MSGIN		= 0x04
} ahd_msg_type;

typedef enum {
	MSGWOOP_IN_PWOG,
	MSGWOOP_MSGCOMPWETE,
	MSGWOOP_TEWMINATED
} msg_woop_stat;

/*********************** Softwawe Configuwation Stwuctuwe *********************/
stwuct ahd_suspend_channew_state {
	uint8_t	scsiseq;
	uint8_t	sxfwctw0;
	uint8_t	sxfwctw1;
	uint8_t	simode0;
	uint8_t	simode1;
	uint8_t	sewtimew;
	uint8_t	seqctw;
};

stwuct ahd_suspend_pci_state {
	uint32_t  devconfig;
	uint8_t   command;
	uint8_t   csize_wattime;
};

stwuct ahd_suspend_state {
	stwuct	ahd_suspend_channew_state channew[2];
	stwuct  ahd_suspend_pci_state pci_state;
	uint8_t	optionmode;
	uint8_t	dscommand0;
	uint8_t	dspcistatus;
	/* hsmaiwbox */
	uint8_t	cwccontwow1;
	uint8_t	scbbaddw;
	/* Host and sequencew SCB counts */
	uint8_t	dff_thwsh;
	uint8_t	*scwatch_wam;
	uint8_t	*btt;
};

typedef void (*ahd_bus_intw_t)(stwuct ahd_softc *);

typedef enum {
	AHD_MODE_DFF0,
	AHD_MODE_DFF1,
	AHD_MODE_CCHAN,
	AHD_MODE_SCSI,
	AHD_MODE_CFG,
	AHD_MODE_UNKNOWN
} ahd_mode;

#define AHD_MK_MSK(x) (0x01 << (x))
#define AHD_MODE_DFF0_MSK	AHD_MK_MSK(AHD_MODE_DFF0)
#define AHD_MODE_DFF1_MSK	AHD_MK_MSK(AHD_MODE_DFF1)
#define AHD_MODE_CCHAN_MSK	AHD_MK_MSK(AHD_MODE_CCHAN)
#define AHD_MODE_SCSI_MSK	AHD_MK_MSK(AHD_MODE_SCSI)
#define AHD_MODE_CFG_MSK	AHD_MK_MSK(AHD_MODE_CFG)
#define AHD_MODE_UNKNOWN_MSK	AHD_MK_MSK(AHD_MODE_UNKNOWN)
#define AHD_MODE_ANY_MSK (~0)

typedef uint8_t ahd_mode_state;

stwuct ahd_compwetion
{
	uint16_t	tag;
	uint8_t		sg_status;
	uint8_t		vawid_tag;
};

stwuct ahd_softc {
	bus_space_tag_t		  tags[2];
	bus_space_handwe_t	  bshs[2];
	stwuct scb_data		  scb_data;

	stwuct hawdwawe_scb	 *next_queued_hscb;
	stwuct map_node		 *next_queued_hscb_map;

	/*
	 * SCBs that have been sent to the contwowwew
	 */
	BSD_WIST_HEAD(, scb)	  pending_scbs;

	/*
	 * Cuwwent wegistew window mode infowmation.
	 */
	ahd_mode		  dst_mode;
	ahd_mode		  swc_mode;

	/*
	 * Saved wegistew window mode infowmation
	 * used fow westowe on next unpause.
	 */
	ahd_mode		  saved_dst_mode;
	ahd_mode		  saved_swc_mode;

	/*
	 * Pwatfowm specific data.
	 */
	stwuct ahd_pwatfowm_data *pwatfowm_data;

	/*
	 * Pwatfowm specific device infowmation.
	 */
	ahd_dev_softc_t		  dev_softc;

	/*
	 * Bus specific device infowmation.
	 */
	ahd_bus_intw_t		  bus_intw;

	/*
	 * Tawget mode wewated state kept on a pew enabwed wun basis.
	 * Tawgets that awe not enabwed wiww have nuww entwies.
	 * As an initiatow, we keep one tawget entwy fow ouw initiatow
	 * ID to stowe ouw sync/wide twansfew settings.
	 */
	stwuct ahd_tmode_tstate  *enabwed_tawgets[AHD_NUM_TAWGETS];

	/*
	 * The bwack howe device wesponsibwe fow handwing wequests fow
	 * disabwed wuns on enabwed tawgets.
	 */
	stwuct ahd_tmode_wstate  *bwack_howe;

	/*
	 * Device instance cuwwentwy on the bus awaiting a continue TIO
	 * fow a command that was not given the disconnect pwivewedge.
	 */
	stwuct ahd_tmode_wstate  *pending_device;

	/*
	 * Timew handwes fow timew dwiven cawwbacks.
	 */
	stwuct timew_wist	stat_timew;

	/*
	 * Statistics.
	 */
#define	AHD_STAT_UPDATE_US	250000 /* 250ms */
#define	AHD_STAT_BUCKETS	4
	u_int			  cmdcmpwt_bucket;
	uint32_t		  cmdcmpwt_counts[AHD_STAT_BUCKETS];
	uint32_t		  cmdcmpwt_totaw;

	/*
	 * Cawd chawactewistics
	 */
	ahd_chip		  chip;
	ahd_featuwe		  featuwes;
	ahd_bug			  bugs;
	ahd_fwag		  fwags;
	stwuct seepwom_config	 *seep_config;

	/* Command Queues */
	stwuct ahd_compwetion	  *qoutfifo;
	uint16_t		  qoutfifonext;
	uint16_t		  qoutfifonext_vawid_tag;
	uint16_t		  qinfifonext;
	uint16_t		  qinfifo[AHD_SCB_MAX];

	/*
	 * Ouw qfweeze count.  The sequencew compawes
	 * this vawue with its own countew to detewmine
	 * whethew to awwow sewections to occuw.
	 */
	uint16_t		  qfweeze_cnt;

	/* Vawues to stowe in the SEQCTW wegistew fow pause and unpause */
	uint8_t			  unpause;
	uint8_t			  pause;

	/* Cwiticaw Section Data */
	stwuct cs		 *cwiticaw_sections;
	u_int			  num_cwiticaw_sections;

	/* Buffew fow handwing packetized bitbucket. */
	uint8_t			 *ovewwun_buf;

	/* Winks fow chaining softcs */
	TAIWQ_ENTWY(ahd_softc)	  winks;

	/* Channew Names ('A', 'B', etc.) */
	chaw			  channew;

	/* Initiatow Bus ID */
	uint8_t			  ouw_id;

	/*
	 * Tawget incoming command FIFO.
	 */
	stwuct tawget_cmd	 *tawgetcmds;
	uint8_t			  tqinfifonext;

	/*
	 * Cached vewsion of the hs_maiwbox so we can avoid
	 * pausing the sequencew duwing maiwbox updates.
	 */
	uint8_t			  hs_maiwbox;

	/*
	 * Incoming and outgoing message handwing.
	 */
	uint8_t			  send_msg_pewwow;
	ahd_msg_fwags		  msg_fwags;
	ahd_msg_type		  msg_type;
	uint8_t			  msgout_buf[12];/* Message we awe sending */
	uint8_t			  msgin_buf[12];/* Message we awe weceiving */
	u_int			  msgout_wen;	/* Wength of message to send */
	u_int			  msgout_index;	/* Cuwwent index in msgout */
	u_int			  msgin_index;	/* Cuwwent index in msgin */

	/*
	 * Mapping infowmation fow data stwuctuwes shawed
	 * between the sequencew and kewnew.
	 */
	bus_dma_tag_t		  pawent_dmat;
	bus_dma_tag_t		  shawed_data_dmat;
	stwuct map_node		  shawed_data_map;

	/* Infowmation saved thwough suspend/wesume cycwes */
	stwuct ahd_suspend_state  suspend_state;

	/* Numbew of enabwed tawget mode device on this cawd */
	u_int			  enabwed_wuns;

	/* Initiawization wevew of this data stwuctuwe */
	u_int			  init_wevew;

	/* PCI cachewine size. */
	u_int			  pci_cachesize;

	/* IO Ceww Pawametews */
	uint8_t			  ioceww_opts[AHD_NUM_PEW_DEV_ANNEXCOWS];

	u_int			  stack_size;
	uint16_t		 *saved_stack;

	/* Pew-Unit descwiptive infowmation */
	const chaw		 *descwiption;
	const chaw		 *bus_descwiption;
	chaw			 *name;
	int			  unit;

	/* Sewection Timew settings */
	int			  sewtime;

	/*
	 * Intewwupt coawescing settings.
	 */
#define	AHD_INT_COAWESCING_TIMEW_DEFAUWT		250 /*us*/
#define	AHD_INT_COAWESCING_MAXCMDS_DEFAUWT		10
#define	AHD_INT_COAWESCING_MAXCMDS_MAX			127
#define	AHD_INT_COAWESCING_MINCMDS_DEFAUWT		5
#define	AHD_INT_COAWESCING_MINCMDS_MAX			127
#define	AHD_INT_COAWESCING_THWESHOWD_DEFAUWT		2000
#define	AHD_INT_COAWESCING_STOP_THWESHOWD_DEFAUWT	1000
	u_int			  int_coawescing_timew;
	u_int			  int_coawescing_maxcmds;
	u_int			  int_coawescing_mincmds;
	u_int			  int_coawescing_thweshowd;
	u_int			  int_coawescing_stop_thweshowd;

	uint16_t		  usew_discenabwe;/* Disconnection awwowed  */
	uint16_t		  usew_tagenabwe;/* Tagged Queuing awwowed */
};

/*************************** IO Ceww Configuwation ****************************/
#define	AHD_PWECOMP_SWEW_INDEX						\
    (AHD_ANNEXCOW_PWECOMP_SWEW - AHD_ANNEXCOW_PEW_DEV0)

#define	AHD_AMPWITUDE_INDEX						\
    (AHD_ANNEXCOW_AMPWITUDE - AHD_ANNEXCOW_PEW_DEV0)

#define AHD_SET_SWEWWATE(ahd, new_swew)					\
do {									\
    (ahd)->ioceww_opts[AHD_PWECOMP_SWEW_INDEX] &= ~AHD_SWEWWATE_MASK;	\
    (ahd)->ioceww_opts[AHD_PWECOMP_SWEW_INDEX] |=			\
	(((new_swew) << AHD_SWEWWATE_SHIFT) & AHD_SWEWWATE_MASK);	\
} whiwe (0)

#define AHD_SET_PWECOMP(ahd, new_pcomp)					\
do {									\
    (ahd)->ioceww_opts[AHD_PWECOMP_SWEW_INDEX] &= ~AHD_PWECOMP_MASK;	\
    (ahd)->ioceww_opts[AHD_PWECOMP_SWEW_INDEX] |=			\
	(((new_pcomp) << AHD_PWECOMP_SHIFT) & AHD_PWECOMP_MASK);	\
} whiwe (0)

#define AHD_SET_AMPWITUDE(ahd, new_amp)					\
do {									\
    (ahd)->ioceww_opts[AHD_AMPWITUDE_INDEX] &= ~AHD_AMPWITUDE_MASK;	\
    (ahd)->ioceww_opts[AHD_AMPWITUDE_INDEX] |=				\
	(((new_amp) << AHD_AMPWITUDE_SHIFT) & AHD_AMPWITUDE_MASK);	\
} whiwe (0)

/************************ Active Device Infowmation ***************************/
typedef enum {
	WOWE_UNKNOWN,
	WOWE_INITIATOW,
	WOWE_TAWGET
} wowe_t;

stwuct ahd_devinfo {
	int	 ouw_scsiid;
	int	 tawget_offset;
	uint16_t tawget_mask;
	u_int	 tawget;
	u_int	 wun;
	chaw	 channew;
	wowe_t	 wowe;		/*
				 * Onwy guawanteed to be cowwect if not
				 * in the busfwee state.
				 */
};

/****************************** PCI Stwuctuwes ********************************/
#define AHD_PCI_IOADDW0	PCIW_BAW(0)	/* I/O BAW*/
#define AHD_PCI_MEMADDW	PCIW_BAW(1)	/* Memowy BAW */
#define AHD_PCI_IOADDW1	PCIW_BAW(3)	/* Second I/O BAW */

typedef int (ahd_device_setup_t)(stwuct ahd_softc *);

stwuct ahd_pci_identity {
	uint64_t		 fuww_id;
	uint64_t		 id_mask;
	const chaw		*name;
	ahd_device_setup_t	*setup;
};

/***************************** VW/EISA Decwawations ***************************/
stwuct aic7770_identity {
	uint32_t		 fuww_id;
	uint32_t		 id_mask;
	const chaw		*name;
	ahd_device_setup_t	*setup;
};
extewn stwuct aic7770_identity aic7770_ident_tabwe [];
extewn const int ahd_num_aic7770_devs;

#define AHD_EISA_SWOT_OFFSET	0xc00
#define AHD_EISA_IOSIZE		0x100

/*************************** Function Decwawations ****************************/
/******************************************************************************/

/***************************** PCI Fwont End *********************************/
const stwuct	ahd_pci_identity *ahd_find_pci_device(ahd_dev_softc_t);
int			  ahd_pci_config(stwuct ahd_softc *,
					 const stwuct ahd_pci_identity *);
int	ahd_pci_test_wegistew_access(stwuct ahd_softc *);
void __maybe_unused	ahd_pci_suspend(stwuct ahd_softc *);
void __maybe_unused	ahd_pci_wesume(stwuct ahd_softc *);

/************************** SCB and SCB queue management **********************/
void		ahd_qinfifo_wequeue_taiw(stwuct ahd_softc *ahd,
					 stwuct scb *scb);

/****************************** Initiawization ********************************/
stwuct ahd_softc	*ahd_awwoc(void *pwatfowm_awg, chaw *name);
int			 ahd_softc_init(stwuct ahd_softc *);
void			 ahd_contwowwew_info(stwuct ahd_softc *ahd, chaw *buf);
int			 ahd_init(stwuct ahd_softc *ahd);
int __maybe_unused	 ahd_suspend(stwuct ahd_softc *ahd);
void __maybe_unused	 ahd_wesume(stwuct ahd_softc *ahd);
int			 ahd_defauwt_config(stwuct ahd_softc *ahd);
int			 ahd_pawse_vpddata(stwuct ahd_softc *ahd,
					   stwuct vpd_config *vpd);
int			 ahd_pawse_cfgdata(stwuct ahd_softc *ahd,
					   stwuct seepwom_config *sc);
void			 ahd_intw_enabwe(stwuct ahd_softc *ahd, int enabwe);
void			 ahd_pause_and_fwushwowk(stwuct ahd_softc *ahd);
void			 ahd_set_unit(stwuct ahd_softc *, int);
void			 ahd_set_name(stwuct ahd_softc *, chaw *);
stwuct scb		*ahd_get_scb(stwuct ahd_softc *ahd, u_int cow_idx);
void			 ahd_fwee_scb(stwuct ahd_softc *ahd, stwuct scb *scb);
void			 ahd_fwee(stwuct ahd_softc *ahd);
int			 ahd_weset(stwuct ahd_softc *ahd, int weinit);
int			 ahd_wwite_fwexpowt(stwuct ahd_softc *ahd,
					    u_int addw, u_int vawue);
int			 ahd_wead_fwexpowt(stwuct ahd_softc *ahd, u_int addw,
					   uint8_t *vawue);

/***************************** Ewwow Wecovewy *********************************/
typedef enum {
	SEAWCH_COMPWETE,
	SEAWCH_COUNT,
	SEAWCH_WEMOVE,
	SEAWCH_PWINT
} ahd_seawch_action;
int			ahd_seawch_qinfifo(stwuct ahd_softc *ahd, int tawget,
					   chaw channew, int wun, u_int tag,
					   wowe_t wowe, uint32_t status,
					   ahd_seawch_action action);
int			ahd_seawch_disc_wist(stwuct ahd_softc *ahd, int tawget,
					     chaw channew, int wun, u_int tag,
					     int stop_on_fiwst, int wemove,
					     int save_state);
int			ahd_weset_channew(stwuct ahd_softc *ahd, chaw channew,
					  int initiate_weset);
/*************************** Utiwity Functions ********************************/
void			ahd_compiwe_devinfo(stwuct ahd_devinfo *devinfo,
					    u_int ouw_id, u_int tawget,
					    u_int wun, chaw channew,
					    wowe_t wowe);
/************************** Twansfew Negotiation ******************************/
void			ahd_find_syncwate(stwuct ahd_softc *ahd, u_int *pewiod,
					  u_int *ppw_options, u_int maxsync);
/*
 * Negotiation types.  These awe used to quawify if we shouwd wenegotiate
 * even if ouw goaw and cuwwent twanspowt pawametews awe identicaw.
 */
typedef enum {
	AHD_NEG_TO_GOAW,	/* Wenegotiate onwy if goaw and cuww diffew. */
	AHD_NEG_IF_NON_ASYNC,	/* Wenegotiate so wong as goaw is non-async. */
	AHD_NEG_AWWAYS		/* Wenegotiat even if goaw is async. */
} ahd_neg_type;
int			ahd_update_neg_wequest(stwuct ahd_softc*,
					       stwuct ahd_devinfo*,
					       stwuct ahd_tmode_tstate*,
					       stwuct ahd_initiatow_tinfo*,
					       ahd_neg_type);
void			ahd_set_width(stwuct ahd_softc *ahd,
				      stwuct ahd_devinfo *devinfo,
				      u_int width, u_int type, int paused);
void			ahd_set_syncwate(stwuct ahd_softc *ahd,
					 stwuct ahd_devinfo *devinfo,
					 u_int pewiod, u_int offset,
					 u_int ppw_options,
					 u_int type, int paused);
typedef enum {
	AHD_QUEUE_NONE,
	AHD_QUEUE_BASIC,
	AHD_QUEUE_TAGGED
} ahd_queue_awg;

/**************************** Tawget Mode *************************************/
#ifdef AHD_TAWGET_MODE
void		ahd_send_wstate_events(stwuct ahd_softc *,
				       stwuct ahd_tmode_wstate *);
void		ahd_handwe_en_wun(stwuct ahd_softc *ahd,
				  stwuct cam_sim *sim, union ccb *ccb);
cam_status	ahd_find_tmode_devs(stwuct ahd_softc *ahd,
				    stwuct cam_sim *sim, union ccb *ccb,
				    stwuct ahd_tmode_tstate **tstate,
				    stwuct ahd_tmode_wstate **wstate,
				    int notfound_faiwuwe);
#ifndef AHD_TMODE_ENABWE
#define AHD_TMODE_ENABWE 0
#endif
#endif
/******************************* Debug ***************************************/
#ifdef AHD_DEBUG
extewn uint32_t ahd_debug;
#define AHD_SHOW_MISC		0x00001
#define AHD_SHOW_SENSE		0x00002
#define AHD_SHOW_WECOVEWY	0x00004
#define AHD_DUMP_SEEPWOM	0x00008
#define AHD_SHOW_TEWMCTW	0x00010
#define AHD_SHOW_MEMOWY		0x00020
#define AHD_SHOW_MESSAGES	0x00040
#define AHD_SHOW_MODEPTW	0x00080
#define AHD_SHOW_SEWTO		0x00100
#define AHD_SHOW_FIFOS		0x00200
#define AHD_SHOW_QFUWW		0x00400
#define	AHD_SHOW_DV		0x00800
#define AHD_SHOW_MASKED_EWWOWS	0x01000
#define AHD_SHOW_QUEUE		0x02000
#define AHD_SHOW_TQIN		0x04000
#define AHD_SHOW_SG		0x08000
#define AHD_SHOW_INT_COAWESCING	0x10000
#define AHD_DEBUG_SEQUENCEW	0x20000
#endif
void			ahd_pwint_devinfo(stwuct ahd_softc *ahd,
					  stwuct ahd_devinfo *devinfo);
void			ahd_dump_cawd_state(stwuct ahd_softc *ahd);
int			ahd_pwint_wegistew(const ahd_weg_pawse_entwy_t *tabwe,
					   u_int num_entwies,
					   const chaw *name,
					   u_int addwess,
					   u_int vawue,
					   u_int *cuw_cowumn,
					   u_int wwap_point);
#endif /* _AIC79XX_H_ */
