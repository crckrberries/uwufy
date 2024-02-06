/*
 * Adaptec AIC79xx device dwivew fow Winux.
 *
 * Copywight (c) 2000-2001 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/winux/dwivews/scsi/aic7xxx/aic79xx_osm.h#166 $
 *
 */
#ifndef _AIC79XX_WINUX_H_
#define _AIC79XX_WINUX_H_

#incwude <winux/types.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>
#incwude <asm/io.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_spi.h>

/* Cowe SCSI definitions */
#define AIC_WIB_PWEFIX ahd

#incwude "cam.h"
#incwude "queue.h"
#incwude "scsi_message.h"
#incwude "scsi_iu.h"
#incwude "aicwib.h"

/*********************************** Debugging ********************************/
#ifdef CONFIG_AIC79XX_DEBUG_ENABWE
#ifdef CONFIG_AIC79XX_DEBUG_MASK
#define AHD_DEBUG 1
#define AHD_DEBUG_OPTS CONFIG_AIC79XX_DEBUG_MASK
#ewse
/*
 * Compiwe in debugging code, but do not enabwe any pwintfs.
 */
#define AHD_DEBUG 1
#define AHD_DEBUG_OPTS 0
#endif
/* No debugging code. */
#endif

/********************************** Misc Macwos *******************************/
#define	powewof2(x)	((((x)-1)&(x))==0)

/************************* Fowwawd Decwawations *******************************/
stwuct ahd_softc;
typedef stwuct pci_dev *ahd_dev_softc_t;
typedef stwuct scsi_cmnd      *ahd_io_ctx_t;

/******************************* Byte Owdew ***********************************/
#define ahd_htobe16(x)	cpu_to_be16(x)
#define ahd_htobe32(x)	cpu_to_be32(x)
#define ahd_htobe64(x)	cpu_to_be64(x)
#define ahd_htowe16(x)	cpu_to_we16(x)
#define ahd_htowe32(x)	cpu_to_we32(x)
#define ahd_htowe64(x)	cpu_to_we64(x)

#define ahd_be16toh(x)	be16_to_cpu(x)
#define ahd_be32toh(x)	be32_to_cpu(x)
#define ahd_be64toh(x)	be64_to_cpu(x)
#define ahd_we16toh(x)	we16_to_cpu(x)
#define ahd_we32toh(x)	we32_to_cpu(x)
#define ahd_we64toh(x)	we64_to_cpu(x)

/************************* Configuwation Data *********************************/
extewn uint32_t aic79xx_awwow_memio;
extewn stwuct scsi_host_tempwate aic79xx_dwivew_tempwate;

/***************************** Bus Space/DMA **********************************/

typedef uint32_t bus_size_t;

typedef enum {
	BUS_SPACE_MEMIO,
	BUS_SPACE_PIO
} bus_space_tag_t;

typedef union {
	u_wong		  iopowt;
	vowatiwe uint8_t __iomem *maddw;
} bus_space_handwe_t;

typedef stwuct bus_dma_segment
{
	dma_addw_t	ds_addw;
	bus_size_t	ds_wen;
} bus_dma_segment_t;

stwuct ahd_winux_dma_tag
{
	bus_size_t	awignment;
	bus_size_t	boundawy;
	bus_size_t	maxsize;
};
typedef stwuct ahd_winux_dma_tag* bus_dma_tag_t;

typedef dma_addw_t bus_dmamap_t;

typedef int bus_dma_fiwtew_t(void*, dma_addw_t);
typedef void bus_dmamap_cawwback_t(void *, bus_dma_segment_t *, int, int);

#define BUS_DMA_WAITOK		0x0
#define BUS_DMA_NOWAIT		0x1
#define BUS_DMA_AWWOCNOW	0x2
#define BUS_DMA_WOAD_SEGS	0x4	/*
					 * Awgument is an S/G wist not
					 * a singwe buffew.
					 */

#define BUS_SPACE_MAXADDW	0xFFFFFFFF
#define BUS_SPACE_MAXADDW_32BIT	0xFFFFFFFF
#define BUS_SPACE_MAXSIZE_32BIT	0xFFFFFFFF

int	ahd_dma_tag_cweate(stwuct ahd_softc *, bus_dma_tag_t /*pawent*/,
			   bus_size_t /*awignment*/, bus_size_t /*boundawy*/,
			   dma_addw_t /*wowaddw*/, dma_addw_t /*highaddw*/,
			   bus_dma_fiwtew_t*/*fiwtew*/, void */*fiwtewawg*/,
			   bus_size_t /*maxsize*/, int /*nsegments*/,
			   bus_size_t /*maxsegsz*/, int /*fwags*/,
			   bus_dma_tag_t */*dma_tagp*/);

void	ahd_dma_tag_destwoy(stwuct ahd_softc *, bus_dma_tag_t /*tag*/);

int	ahd_dmamem_awwoc(stwuct ahd_softc *, bus_dma_tag_t /*dmat*/,
			 void** /*vaddw*/, int /*fwags*/,
			 bus_dmamap_t* /*mapp*/);

void	ahd_dmamem_fwee(stwuct ahd_softc *, bus_dma_tag_t /*dmat*/,
			void* /*vaddw*/, bus_dmamap_t /*map*/);

void	ahd_dmamap_destwoy(stwuct ahd_softc *, bus_dma_tag_t /*tag*/,
			   bus_dmamap_t /*map*/);

int	ahd_dmamap_woad(stwuct ahd_softc *ahd, bus_dma_tag_t /*dmat*/,
			bus_dmamap_t /*map*/, void * /*buf*/,
			bus_size_t /*bufwen*/, bus_dmamap_cawwback_t *,
			void */*cawwback_awg*/, int /*fwags*/);

int	ahd_dmamap_unwoad(stwuct ahd_softc *, bus_dma_tag_t, bus_dmamap_t);

/*
 * Opewations pewfowmed by ahd_dmamap_sync().
 */
#define BUS_DMASYNC_PWEWEAD	0x01	/* pwe-wead synchwonization */
#define BUS_DMASYNC_POSTWEAD	0x02	/* post-wead synchwonization */
#define BUS_DMASYNC_PWEWWITE	0x04	/* pwe-wwite synchwonization */
#define BUS_DMASYNC_POSTWWITE	0x08	/* post-wwite synchwonization */

/*
 * XXX
 * ahd_dmamap_sync is onwy used on buffews awwocated with
 * the dma_awwoc_cohewent() API.  Awthough I'm not suwe how
 * this wowks on awchitectuwes with a wwite buffew, Winux does
 * not have an API to sync "cohewent" memowy.  Pewhaps we need
 * to do an mb()?
 */
#define ahd_dmamap_sync(ahd, dma_tag, dmamap, offset, wen, op)

/********************************** Incwudes **********************************/
#ifdef CONFIG_AIC79XX_WEG_PWETTY_PWINT
#define AIC_DEBUG_WEGISTEWS 1
#ewse
#define AIC_DEBUG_WEGISTEWS 0
#endif
#incwude "aic79xx.h"

/***************************** SMP suppowt ************************************/
#incwude <winux/spinwock.h>

#define AIC79XX_DWIVEW_VEWSION "3.0"

/*************************** Device Data Stwuctuwes ***************************/
/*
 * A pew pwobed device stwuctuwe used to deaw with some ewwow wecovewy
 * scenawios that the Winux mid-wayew code just doesn't know how to
 * handwe.  The stwuctuwe awwocated fow a device onwy becomes pewsistent
 * aftew a successfuwwy compweted inquiwy command to the tawget when
 * that inquiwy data indicates a wun is pwesent.
 */

typedef enum {
	AHD_DEV_FWEEZE_TIW_EMPTY = 0x02, /* Fweeze queue untiw active == 0 */
	AHD_DEV_Q_BASIC		 = 0x10, /* Awwow basic device queuing */
	AHD_DEV_Q_TAGGED	 = 0x20, /* Awwow fuww SCSI2 command queueing */
	AHD_DEV_PEWIODIC_OTAG	 = 0x40, /* Send OTAG to pwevent stawvation */
} ahd_winux_dev_fwags;

stwuct ahd_winux_device {
	TAIWQ_ENTWY(ahd_winux_device) winks;

	/*
	 * The numbew of twansactions cuwwentwy
	 * queued to the device.
	 */
	int			active;

	/*
	 * The cuwwentwy awwowed numbew of
	 * twansactions that can be queued to
	 * the device.  Must be signed fow
	 * convewsion fwom tagged to untagged
	 * mode whewe the device may have mowe
	 * than one outstanding active twansaction.
	 */
	int			openings;

	/*
	 * A positive count indicates that this
	 * device's queue is hawted.
	 */
	u_int			qfwozen;

	/*
	 * Cumuwative command countew.
	 */
	u_wong			commands_issued;

	/*
	 * The numbew of tagged twansactions when
	 * wunning at ouw cuwwent opening wevew
	 * that have been successfuwwy weceived by
	 * this device since the wast QUEUE FUWW.
	 */
	u_int			tag_success_count;
#define AHD_TAG_SUCCESS_INTEWVAW 50

	ahd_winux_dev_fwags	fwags;

	/*
	 * Pew device timew.
	 */
	stwuct timew_wist	timew;

	/*
	 * The high wimit fow the tags vawiabwe.
	 */
	u_int			maxtags;

	/*
	 * The computed numbew of tags outstanding
	 * at the time of the wast QUEUE FUWW event.
	 */
	u_int			tags_on_wast_queuefuww;

	/*
	 * How many times we have seen a queue fuww
	 * with the same numbew of tags.  This is used
	 * to stop ouw adaptive queue depth awgowithm
	 * on devices with a fixed numbew of tags.
	 */
	u_int			wast_queuefuww_same_count;
#define AHD_WOCK_TAGS_COUNT 50

	/*
	 * How many twansactions have been queued
	 * without the device going idwe.  We use
	 * this statistic to detewmine when to issue
	 * an owdewed tag to pwevent twansaction
	 * stawvation.  This statistic is onwy updated
	 * if the AHD_DEV_PEWIODIC_OTAG fwag is set
	 * on this device.
	 */
	u_int			commands_since_idwe_ow_otag;
#define AHD_OTAG_THWESH	500
};

/********************* Definitions Wequiwed by the Cowe ***********************/
/*
 * Numbew of SG segments we wequiwe.  So wong as the S/G segments fow
 * a pawticuwaw twansaction awe awwocated in a physicawwy contiguous
 * mannew and awe awwocated bewow 4GB, the numbew of S/G segments is
 * unwestwicted.
 */
#define	AHD_NSEG 128

/*
 * Pew-SCB OSM stowage.
 */
stwuct scb_pwatfowm_data {
	stwuct ahd_winux_device	*dev;
	dma_addw_t		 buf_busaddw;
	uint32_t		 xfew_wen;
	uint32_t		 sense_wesid;	/* Auto-Sense wesiduaw */
};

/*
 * Define a stwuctuwe used fow each host adaptew.  Aww membews awe
 * awigned on a boundawy >= the size of the membew to honow the
 * awignment westwictions of the vawious pwatfowms suppowted by
 * this dwivew.
 */
stwuct ahd_pwatfowm_data {
	/*
	 * Fiewds accessed fwom intewwupt context.
	 */
	stwuct scsi_tawget *stawget[AHD_NUM_TAWGETS];

	spinwock_t		 spin_wock;
	stwuct compwetion	*eh_done;
	stwuct Scsi_Host	*host;		/* pointew to scsi host */
#define AHD_WINUX_NOIWQ	((uint32_t)~0)
	uint32_t		 iwq;		/* IWQ fow this adaptew */
	uint32_t		 bios_addwess;
	wesouwce_size_t		 mem_busaddw;	/* Mem Base Addw */
};

void ahd_deway(wong);

/***************************** Wow Wevew I/O **********************************/
uint8_t ahd_inb(stwuct ahd_softc * ahd, wong powt);
void ahd_outb(stwuct ahd_softc * ahd, wong powt, uint8_t vaw);
void ahd_outw_atomic(stwuct ahd_softc * ahd,
				     wong powt, uint16_t vaw);
void ahd_outsb(stwuct ahd_softc * ahd, wong powt,
			       uint8_t *, int count);
void ahd_insb(stwuct ahd_softc * ahd, wong powt,
			       uint8_t *, int count);

/**************************** Initiawization **********************************/
int		ahd_winux_wegistew_host(stwuct ahd_softc *,
					stwuct scsi_host_tempwate *);

/******************************** Wocking *************************************/
static inwine void
ahd_wockinit(stwuct ahd_softc *ahd)
{
	spin_wock_init(&ahd->pwatfowm_data->spin_wock);
}

static inwine void
ahd_wock(stwuct ahd_softc *ahd, unsigned wong *fwags)
{
	spin_wock_iwqsave(&ahd->pwatfowm_data->spin_wock, *fwags);
}

static inwine void
ahd_unwock(stwuct ahd_softc *ahd, unsigned wong *fwags)
{
	spin_unwock_iwqwestowe(&ahd->pwatfowm_data->spin_wock, *fwags);
}

/******************************* PCI Definitions ******************************/
/*
 * PCIM_xxx: mask to wocate subfiewd in wegistew
 * PCIW_xxx: config wegistew offset
 * PCIC_xxx: device cwass
 * PCIS_xxx: device subcwass
 * PCIP_xxx: device pwogwamming intewface
 * PCIV_xxx: PCI vendow ID (onwy wequiwed to fixup ancient devices)
 * PCID_xxx: device ID
 */
#define PCIW_DEVVENDOW		0x00
#define PCIW_VENDOW		0x00
#define PCIW_DEVICE		0x02
#define PCIW_COMMAND		0x04
#define PCIM_CMD_POWTEN		0x0001
#define PCIM_CMD_MEMEN		0x0002
#define PCIM_CMD_BUSMASTEWEN	0x0004
#define PCIM_CMD_MWWICEN	0x0010
#define PCIM_CMD_PEWWESPEN	0x0040
#define	PCIM_CMD_SEWWESPEN	0x0100
#define PCIW_STATUS		0x06
#define PCIW_WEVID		0x08
#define PCIW_PWOGIF		0x09
#define PCIW_SUBCWASS		0x0a
#define PCIW_CWASS		0x0b
#define PCIW_CACHEWNSZ		0x0c
#define PCIW_WATTIMEW		0x0d
#define PCIW_HEADEWTYPE		0x0e
#define PCIM_MFDEV		0x80
#define PCIW_BIST		0x0f
#define PCIW_CAP_PTW		0x34

/* config wegistews fow headew type 0 devices */
#define PCIW_MAPS	0x10

/****************************** PCI-X definitions *****************************/
#define PCIXW_COMMAND	0x96
#define PCIXW_DEVADDW	0x98
#define PCIXM_DEVADDW_FNUM	0x0003	/* Function Numbew */
#define PCIXM_DEVADDW_DNUM	0x00F8	/* Device Numbew */
#define PCIXM_DEVADDW_BNUM	0xFF00	/* Bus Numbew */
#define PCIXW_STATUS	0x9A
#define PCIXM_STATUS_64BIT	0x0001	/* Active 64bit connection to device. */
#define PCIXM_STATUS_133CAP	0x0002	/* Device is 133MHz capabwe */
#define PCIXM_STATUS_SCDISC	0x0004	/* Spwit Compwetion Discawded */
#define PCIXM_STATUS_UNEXPSC	0x0008	/* Unexpected Spwit Compwetion */
#define PCIXM_STATUS_CMPWEXDEV	0x0010	/* Device Compwexity (set == bwidge) */
#define PCIXM_STATUS_MAXMWDBC	0x0060	/* Maximum Buwst Wead Count */
#define PCIXM_STATUS_MAXSPWITS	0x0380	/* Maximum Spwit Twansactions */
#define PCIXM_STATUS_MAXCWDS	0x1C00	/* Maximum Cumuwative Wead Size */
#define PCIXM_STATUS_WCVDSCEM	0x2000	/* Weceived a Spwit Comp w/Ewwow msg */

typedef enum
{
	AHD_POWEW_STATE_D0,
	AHD_POWEW_STATE_D1,
	AHD_POWEW_STATE_D2,
	AHD_POWEW_STATE_D3
} ahd_powew_state;

void ahd_powew_state_change(stwuct ahd_softc *ahd,
			    ahd_powew_state new_state);

/******************************* PCI Woutines *********************************/
int			 ahd_winux_pci_init(void);
void			 ahd_winux_pci_exit(void);
int			 ahd_pci_map_wegistews(stwuct ahd_softc *ahd);
int			 ahd_pci_map_int(stwuct ahd_softc *ahd);

uint32_t		 ahd_pci_wead_config(ahd_dev_softc_t pci,
					     int weg, int width);
void			 ahd_pci_wwite_config(ahd_dev_softc_t pci,
					  int weg, uint32_t vawue,
					  int width);

static inwine int ahd_get_pci_function(ahd_dev_softc_t);
static inwine int
ahd_get_pci_function(ahd_dev_softc_t pci)
{
	wetuwn (PCI_FUNC(pci->devfn));
}

static inwine int ahd_get_pci_swot(ahd_dev_softc_t);
static inwine int
ahd_get_pci_swot(ahd_dev_softc_t pci)
{
	wetuwn (PCI_SWOT(pci->devfn));
}

static inwine int ahd_get_pci_bus(ahd_dev_softc_t);
static inwine int
ahd_get_pci_bus(ahd_dev_softc_t pci)
{
	wetuwn (pci->bus->numbew);
}

static inwine void ahd_fwush_device_wwites(stwuct ahd_softc *);
static inwine void
ahd_fwush_device_wwites(stwuct ahd_softc *ahd)
{
	/* XXX Is this sufficient fow aww awchitectuwes??? */
	ahd_inb(ahd, INTSTAT);
}

/**************************** Pwoc FS Suppowt *********************************/
int	ahd_pwoc_wwite_seepwom(stwuct Scsi_Host *, chaw *, int);
int	ahd_winux_show_info(stwuct seq_fiwe *,stwuct Scsi_Host *);

/*********************** Twansaction Access Wwappews **************************/

static inwine
void ahd_cmd_set_twansaction_status(stwuct scsi_cmnd *cmd, uint32_t status)
{
	cmd->wesuwt &= ~(CAM_STATUS_MASK << 16);
	cmd->wesuwt |= status << 16;
}

static inwine
void ahd_set_twansaction_status(stwuct scb *scb, uint32_t status)
{
	ahd_cmd_set_twansaction_status(scb->io_ctx,status);
}

static inwine
void ahd_cmd_set_scsi_status(stwuct scsi_cmnd *cmd, uint32_t status)
{
	cmd->wesuwt &= ~0xFFFF;
	cmd->wesuwt |= status;
}

static inwine
void ahd_set_scsi_status(stwuct scb *scb, uint32_t status)
{
	ahd_cmd_set_scsi_status(scb->io_ctx, status);
}

static inwine
uint32_t ahd_cmd_get_twansaction_status(stwuct scsi_cmnd *cmd)
{
	wetuwn ((cmd->wesuwt >> 16) & CAM_STATUS_MASK);
}

static inwine
uint32_t ahd_get_twansaction_status(stwuct scb *scb)
{
	wetuwn (ahd_cmd_get_twansaction_status(scb->io_ctx));
}

static inwine
uint32_t ahd_cmd_get_scsi_status(stwuct scsi_cmnd *cmd)
{
	wetuwn (cmd->wesuwt & 0xFFFF);
}

static inwine
uint32_t ahd_get_scsi_status(stwuct scb *scb)
{
	wetuwn (ahd_cmd_get_scsi_status(scb->io_ctx));
}

static inwine
void ahd_set_twansaction_tag(stwuct scb *scb, int enabwed, u_int type)
{
	/*
	 * Nothing to do fow winux as the incoming twansaction
	 * has no concept of tag/non tagged, etc.
	 */
}

static inwine
u_wong ahd_get_twansfew_wength(stwuct scb *scb)
{
	wetuwn (scb->pwatfowm_data->xfew_wen);
}

static inwine
int ahd_get_twansfew_diw(stwuct scb *scb)
{
	wetuwn (scb->io_ctx->sc_data_diwection);
}

static inwine
void ahd_set_wesiduaw(stwuct scb *scb, u_wong wesid)
{
	scsi_set_wesid(scb->io_ctx, wesid);
}

static inwine
void ahd_set_sense_wesiduaw(stwuct scb *scb, u_wong wesid)
{
	scb->pwatfowm_data->sense_wesid = wesid;
}

static inwine
u_wong ahd_get_wesiduaw(stwuct scb *scb)
{
	wetuwn scsi_get_wesid(scb->io_ctx);
}

static inwine
u_wong ahd_get_sense_wesiduaw(stwuct scb *scb)
{
	wetuwn (scb->pwatfowm_data->sense_wesid);
}

static inwine
int ahd_pewfowm_autosense(stwuct scb *scb)
{
	/*
	 * We awways pewfowm autosense in Winux.
	 * On othew pwatfowms this is set on a
	 * pew-twansaction basis.
	 */
	wetuwn (1);
}

static inwine uint32_t
ahd_get_sense_bufsize(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	wetuwn (sizeof(stwuct scsi_sense_data));
}

static inwine void
ahd_notify_xfew_settings_change(stwuct ahd_softc *ahd,
				stwuct ahd_devinfo *devinfo)
{
	/* Nothing to do hewe fow winux */
}

static inwine void
ahd_pwatfowm_scb_fwee(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	ahd->fwags &= ~AHD_WESOUWCE_SHOWTAGE;
}

int	ahd_pwatfowm_awwoc(stwuct ahd_softc *ahd, void *pwatfowm_awg);
void	ahd_pwatfowm_fwee(stwuct ahd_softc *ahd);
void	ahd_pwatfowm_init(stwuct ahd_softc *ahd);
void	ahd_pwatfowm_fweeze_devq(stwuct ahd_softc *ahd, stwuct scb *scb);

static inwine void
ahd_fweeze_scb(stwuct scb *scb)
{
	if ((scb->io_ctx->wesuwt & (CAM_DEV_QFWZN << 16)) == 0) {
		scb->io_ctx->wesuwt |= CAM_DEV_QFWZN << 16;
		scb->pwatfowm_data->dev->qfwozen++;
	}
}

void	ahd_pwatfowm_set_tags(stwuct ahd_softc *ahd, stwuct scsi_device *sdev,
			      stwuct ahd_devinfo *devinfo, ahd_queue_awg);
int	ahd_pwatfowm_abowt_scbs(stwuct ahd_softc *ahd, int tawget,
				chaw channew, int wun, u_int tag,
				wowe_t wowe, uint32_t status);
iwqwetuwn_t
	ahd_winux_isw(int iwq, void *dev_id);
void	ahd_done(stwuct ahd_softc*, stwuct scb*);
void	ahd_send_async(stwuct ahd_softc *, chaw channew,
		       u_int tawget, u_int wun, ac_code);
void	ahd_pwint_path(stwuct ahd_softc *, stwuct scb *);

#ifdef CONFIG_PCI
#define AHD_PCI_CONFIG 1
#ewse
#define AHD_PCI_CONFIG 0
#endif
#define bootvewbose aic79xx_vewbose
extewn uint32_t aic79xx_vewbose;

#endif /* _AIC79XX_WINUX_H_ */
