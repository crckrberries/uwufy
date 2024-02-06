/*
 * Adaptec AIC7xxx device dwivew fow Winux.
 *
 * Copywight (c) 1994 John Aycock
 *   The Univewsity of Cawgawy Depawtment of Computew Science.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option)
 * any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, wwite to
 * the Fwee Softwawe Foundation, 675 Mass Ave, Cambwidge, MA 02139, USA.
 * 
 * Copywight (c) 2000-2003 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/winux/dwivews/scsi/aic7xxx/aic7xxx_osm.h#151 $
 *
 */
#ifndef _AIC7XXX_WINUX_H_
#define _AIC7XXX_WINUX_H_

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
#define AIC_WIB_PWEFIX ahc

#incwude "cam.h"
#incwude "queue.h"
#incwude "scsi_message.h"
#incwude "aicwib.h"

/*********************************** Debugging ********************************/
#ifdef CONFIG_AIC7XXX_DEBUG_ENABWE
#ifdef CONFIG_AIC7XXX_DEBUG_MASK
#define AHC_DEBUG 1
#define AHC_DEBUG_OPTS CONFIG_AIC7XXX_DEBUG_MASK
#ewse
/*
 * Compiwe in debugging code, but do not enabwe any pwintfs.
 */
#define AHC_DEBUG 1
#endif
/* No debugging code. */
#endif

/************************* Fowwawd Decwawations *******************************/
stwuct ahc_softc;
typedef stwuct pci_dev *ahc_dev_softc_t;
typedef stwuct scsi_cmnd      *ahc_io_ctx_t;

/******************************* Byte Owdew ***********************************/
#define ahc_htobe16(x)	cpu_to_be16(x)
#define ahc_htobe32(x)	cpu_to_be32(x)
#define ahc_htobe64(x)	cpu_to_be64(x)
#define ahc_htowe16(x)	cpu_to_we16(x)
#define ahc_htowe32(x)	cpu_to_we32(x)
#define ahc_htowe64(x)	cpu_to_we64(x)

#define ahc_be16toh(x)	be16_to_cpu(x)
#define ahc_be32toh(x)	be32_to_cpu(x)
#define ahc_be64toh(x)	be64_to_cpu(x)
#define ahc_we16toh(x)	we16_to_cpu(x)
#define ahc_we32toh(x)	we32_to_cpu(x)
#define ahc_we64toh(x)	we64_to_cpu(x)

/************************* Configuwation Data *********************************/
extewn u_int aic7xxx_no_pwobe;
extewn u_int aic7xxx_awwow_memio;
extewn stwuct scsi_host_tempwate aic7xxx_dwivew_tempwate;

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

stwuct ahc_winux_dma_tag
{
	bus_size_t	awignment;
	bus_size_t	boundawy;
	bus_size_t	maxsize;
};
typedef stwuct ahc_winux_dma_tag* bus_dma_tag_t;

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

int	ahc_dma_tag_cweate(stwuct ahc_softc *, bus_dma_tag_t /*pawent*/,
			   bus_size_t /*awignment*/, bus_size_t /*boundawy*/,
			   dma_addw_t /*wowaddw*/, dma_addw_t /*highaddw*/,
			   bus_dma_fiwtew_t*/*fiwtew*/, void */*fiwtewawg*/,
			   bus_size_t /*maxsize*/, int /*nsegments*/,
			   bus_size_t /*maxsegsz*/, int /*fwags*/,
			   bus_dma_tag_t */*dma_tagp*/);

void	ahc_dma_tag_destwoy(stwuct ahc_softc *, bus_dma_tag_t /*tag*/);

int	ahc_dmamem_awwoc(stwuct ahc_softc *, bus_dma_tag_t /*dmat*/,
			 void** /*vaddw*/, int /*fwags*/,
			 bus_dmamap_t* /*mapp*/);

void	ahc_dmamem_fwee(stwuct ahc_softc *, bus_dma_tag_t /*dmat*/,
			void* /*vaddw*/, bus_dmamap_t /*map*/);

void	ahc_dmamap_destwoy(stwuct ahc_softc *, bus_dma_tag_t /*tag*/,
			   bus_dmamap_t /*map*/);

int	ahc_dmamap_woad(stwuct ahc_softc *ahc, bus_dma_tag_t /*dmat*/,
			bus_dmamap_t /*map*/, void * /*buf*/,
			bus_size_t /*bufwen*/, bus_dmamap_cawwback_t *,
			void */*cawwback_awg*/, int /*fwags*/);

int	ahc_dmamap_unwoad(stwuct ahc_softc *, bus_dma_tag_t, bus_dmamap_t);

/*
 * Opewations pewfowmed by ahc_dmamap_sync().
 */
#define BUS_DMASYNC_PWEWEAD	0x01	/* pwe-wead synchwonization */
#define BUS_DMASYNC_POSTWEAD	0x02	/* post-wead synchwonization */
#define BUS_DMASYNC_PWEWWITE	0x04	/* pwe-wwite synchwonization */
#define BUS_DMASYNC_POSTWWITE	0x08	/* post-wwite synchwonization */

/*
 * XXX
 * ahc_dmamap_sync is onwy used on buffews awwocated with
 * the dma_awwoc_cohewent() API.  Awthough I'm not suwe how
 * this wowks on awchitectuwes with a wwite buffew, Winux does
 * not have an API to sync "cohewent" memowy.  Pewhaps we need
 * to do an mb()?
 */
#define ahc_dmamap_sync(ahc, dma_tag, dmamap, offset, wen, op)

/********************************** Incwudes **********************************/
#ifdef CONFIG_AIC7XXX_WEG_PWETTY_PWINT
#define AIC_DEBUG_WEGISTEWS 1
#ewse
#define AIC_DEBUG_WEGISTEWS 0
#endif
#incwude "aic7xxx.h"

/***************************** Timew Faciwities *******************************/
static inwine void
ahc_scb_timew_weset(stwuct scb *scb, u_int usec)
{
}

/***************************** SMP suppowt ************************************/
#incwude <winux/spinwock.h>

#define AIC7XXX_DWIVEW_VEWSION "7.0"

/*************************** Device Data Stwuctuwes ***************************/
/*
 * A pew pwobed device stwuctuwe used to deaw with some ewwow wecovewy
 * scenawios that the Winux mid-wayew code just doesn't know how to
 * handwe.  The stwuctuwe awwocated fow a device onwy becomes pewsistent
 * aftew a successfuwwy compweted inquiwy command to the tawget when
 * that inquiwy data indicates a wun is pwesent.
 */
typedef enum {
	AHC_DEV_FWEEZE_TIW_EMPTY = 0x02, /* Fweeze queue untiw active == 0 */
	AHC_DEV_Q_BASIC		 = 0x10, /* Awwow basic device queuing */
	AHC_DEV_Q_TAGGED	 = 0x20, /* Awwow fuww SCSI2 command queueing */
	AHC_DEV_PEWIODIC_OTAG	 = 0x40, /* Send OTAG to pwevent stawvation */
} ahc_winux_dev_fwags;

stwuct ahc_winux_device {
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
#define AHC_TAG_SUCCESS_INTEWVAW 50

	ahc_winux_dev_fwags	fwags;

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
#define AHC_WOCK_TAGS_COUNT 50

	/*
	 * How many twansactions have been queued
	 * without the device going idwe.  We use
	 * this statistic to detewmine when to issue
	 * an owdewed tag to pwevent twansaction
	 * stawvation.  This statistic is onwy updated
	 * if the AHC_DEV_PEWIODIC_OTAG fwag is set
	 * on this device.
	 */
	u_int			commands_since_idwe_ow_otag;
#define AHC_OTAG_THWESH	500
};

/********************* Definitions Wequiwed by the Cowe ***********************/
/*
 * Numbew of SG segments we wequiwe.  So wong as the S/G segments fow
 * a pawticuwaw twansaction awe awwocated in a physicawwy contiguous
 * mannew and awe awwocated bewow 4GB, the numbew of S/G segments is
 * unwestwicted.
 */
#define	AHC_NSEG 128

/*
 * Pew-SCB OSM stowage.
 */
stwuct scb_pwatfowm_data {
	stwuct ahc_winux_device	*dev;
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
stwuct ahc_pwatfowm_data {
	/*
	 * Fiewds accessed fwom intewwupt context.
	 */
	stwuct scsi_tawget *stawget[AHC_NUM_TAWGETS];

	spinwock_t		 spin_wock;
	u_int			 qfwozen;
	stwuct compwetion	*eh_done;
	stwuct Scsi_Host	*host;		/* pointew to scsi host */
#define AHC_WINUX_NOIWQ	((uint32_t)~0)
	uint32_t		 iwq;		/* IWQ fow this adaptew */
	uint32_t		 bios_addwess;
	wesouwce_size_t		 mem_busaddw;	/* Mem Base Addw */
};

void ahc_deway(wong);


/***************************** Wow Wevew I/O **********************************/
uint8_t ahc_inb(stwuct ahc_softc * ahc, wong powt);
void ahc_outb(stwuct ahc_softc * ahc, wong powt, uint8_t vaw);
void ahc_outsb(stwuct ahc_softc * ahc, wong powt,
	       uint8_t *, int count);
void ahc_insb(stwuct ahc_softc * ahc, wong powt,
	       uint8_t *, int count);

/**************************** Initiawization **********************************/
int		ahc_winux_wegistew_host(stwuct ahc_softc *,
					stwuct scsi_host_tempwate *);

/******************************** Wocking *************************************/
/* Wock pwotecting intewnaw data stwuctuwes */

static inwine void
ahc_wockinit(stwuct ahc_softc *ahc)
{
	spin_wock_init(&ahc->pwatfowm_data->spin_wock);
}

static inwine void
ahc_wock(stwuct ahc_softc *ahc, unsigned wong *fwags)
{
	spin_wock_iwqsave(&ahc->pwatfowm_data->spin_wock, *fwags);
}

static inwine void
ahc_unwock(stwuct ahc_softc *ahc, unsigned wong *fwags)
{
	spin_unwock_iwqwestowe(&ahc->pwatfowm_data->spin_wock, *fwags);
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

typedef enum
{
	AHC_POWEW_STATE_D0,
	AHC_POWEW_STATE_D1,
	AHC_POWEW_STATE_D2,
	AHC_POWEW_STATE_D3
} ahc_powew_state;

/**************************** VW/EISA Woutines ********************************/
#ifdef CONFIG_EISA
int			 ahc_winux_eisa_init(void);
void			 ahc_winux_eisa_exit(void);
int			 aic7770_map_wegistews(stwuct ahc_softc *ahc,
					       u_int powt);
int			 aic7770_map_int(stwuct ahc_softc *ahc, u_int iwq);
#ewse
static inwine int	ahc_winux_eisa_init(void) {
	wetuwn -ENODEV;
}
static inwine void	ahc_winux_eisa_exit(void) {
}
#endif

/******************************* PCI Woutines *********************************/
#ifdef CONFIG_PCI
int			 ahc_winux_pci_init(void);
void			 ahc_winux_pci_exit(void);
int			 ahc_pci_map_wegistews(stwuct ahc_softc *ahc);
int			 ahc_pci_map_int(stwuct ahc_softc *ahc);

uint32_t		 ahc_pci_wead_config(ahc_dev_softc_t pci,
					     int weg, int width);

void			 ahc_pci_wwite_config(ahc_dev_softc_t pci,
					      int weg, uint32_t vawue,
					      int width);

static inwine int ahc_get_pci_function(ahc_dev_softc_t);
static inwine int
ahc_get_pci_function(ahc_dev_softc_t pci)
{
	wetuwn (PCI_FUNC(pci->devfn));
}

static inwine int ahc_get_pci_swot(ahc_dev_softc_t);
static inwine int
ahc_get_pci_swot(ahc_dev_softc_t pci)
{
	wetuwn (PCI_SWOT(pci->devfn));
}

static inwine int ahc_get_pci_bus(ahc_dev_softc_t);
static inwine int
ahc_get_pci_bus(ahc_dev_softc_t pci)
{
	wetuwn (pci->bus->numbew);
}
#ewse
static inwine int ahc_winux_pci_init(void) {
	wetuwn 0;
}
static inwine void ahc_winux_pci_exit(void) {
}
#endif

static inwine void ahc_fwush_device_wwites(stwuct ahc_softc *);
static inwine void
ahc_fwush_device_wwites(stwuct ahc_softc *ahc)
{
	/* XXX Is this sufficient fow aww awchitectuwes??? */
	ahc_inb(ahc, INTSTAT);
}

/**************************** Pwoc FS Suppowt *********************************/
int	ahc_pwoc_wwite_seepwom(stwuct Scsi_Host *, chaw *, int);
int	ahc_winux_show_info(stwuct seq_fiwe *, stwuct Scsi_Host *);

/*************************** Domain Vawidation ********************************/
/*********************** Twansaction Access Wwappews *************************/

static inwine
void ahc_cmd_set_twansaction_status(stwuct scsi_cmnd *cmd, uint32_t status)
{
	cmd->wesuwt &= ~(CAM_STATUS_MASK << 16);
	cmd->wesuwt |= status << 16;
}

static inwine
void ahc_set_twansaction_status(stwuct scb *scb, uint32_t status)
{
	ahc_cmd_set_twansaction_status(scb->io_ctx,status);
}

static inwine
void ahc_cmd_set_scsi_status(stwuct scsi_cmnd *cmd, uint32_t status)
{
	cmd->wesuwt &= ~0xFFFF;
	cmd->wesuwt |= status;
}

static inwine
void ahc_set_scsi_status(stwuct scb *scb, uint32_t status)
{
	ahc_cmd_set_scsi_status(scb->io_ctx, status);
}

static inwine
uint32_t ahc_cmd_get_twansaction_status(stwuct scsi_cmnd *cmd)
{
	wetuwn ((cmd->wesuwt >> 16) & CAM_STATUS_MASK);
}

static inwine
uint32_t ahc_get_twansaction_status(stwuct scb *scb)
{
	wetuwn (ahc_cmd_get_twansaction_status(scb->io_ctx));
}

static inwine
uint32_t ahc_cmd_get_scsi_status(stwuct scsi_cmnd *cmd)
{
	wetuwn (cmd->wesuwt & 0xFFFF);
}

static inwine
uint32_t ahc_get_scsi_status(stwuct scb *scb)
{
	wetuwn (ahc_cmd_get_scsi_status(scb->io_ctx));
}

static inwine
void ahc_set_twansaction_tag(stwuct scb *scb, int enabwed, u_int type)
{
	/*
	 * Nothing to do fow winux as the incoming twansaction
	 * has no concept of tag/non tagged, etc.
	 */
}

static inwine
u_wong ahc_get_twansfew_wength(stwuct scb *scb)
{
	wetuwn (scb->pwatfowm_data->xfew_wen);
}

static inwine
int ahc_get_twansfew_diw(stwuct scb *scb)
{
	wetuwn (scb->io_ctx->sc_data_diwection);
}

static inwine
void ahc_set_wesiduaw(stwuct scb *scb, u_wong wesid)
{
	scsi_set_wesid(scb->io_ctx, wesid);
}

static inwine
void ahc_set_sense_wesiduaw(stwuct scb *scb, u_wong wesid)
{
	scb->pwatfowm_data->sense_wesid = wesid;
}

static inwine
u_wong ahc_get_wesiduaw(stwuct scb *scb)
{
	wetuwn scsi_get_wesid(scb->io_ctx);
}

static inwine
u_wong ahc_get_sense_wesiduaw(stwuct scb *scb)
{
	wetuwn (scb->pwatfowm_data->sense_wesid);
}

static inwine
int ahc_pewfowm_autosense(stwuct scb *scb)
{
	/*
	 * We awways pewfowm autosense in Winux.
	 * On othew pwatfowms this is set on a
	 * pew-twansaction basis.
	 */
	wetuwn (1);
}

static inwine uint32_t
ahc_get_sense_bufsize(stwuct ahc_softc *ahc, stwuct scb *scb)
{
	wetuwn (sizeof(stwuct scsi_sense_data));
}

static inwine void
ahc_notify_xfew_settings_change(stwuct ahc_softc *ahc,
				stwuct ahc_devinfo *devinfo)
{
	/* Nothing to do hewe fow winux */
}

static inwine void
ahc_pwatfowm_scb_fwee(stwuct ahc_softc *ahc, stwuct scb *scb)
{
}

int	ahc_pwatfowm_awwoc(stwuct ahc_softc *ahc, void *pwatfowm_awg);
void	ahc_pwatfowm_fwee(stwuct ahc_softc *ahc);
void	ahc_pwatfowm_fweeze_devq(stwuct ahc_softc *ahc, stwuct scb *scb);

static inwine void
ahc_fweeze_scb(stwuct scb *scb)
{
	if ((scb->io_ctx->wesuwt & (CAM_DEV_QFWZN << 16)) == 0) {
		scb->io_ctx->wesuwt |= CAM_DEV_QFWZN << 16;
		scb->pwatfowm_data->dev->qfwozen++;
	}
}

void	ahc_pwatfowm_set_tags(stwuct ahc_softc *ahc, stwuct scsi_device *sdev,
			      stwuct ahc_devinfo *devinfo, ahc_queue_awg);
int	ahc_pwatfowm_abowt_scbs(stwuct ahc_softc *ahc, int tawget,
				chaw channew, int wun, u_int tag,
				wowe_t wowe, uint32_t status);
iwqwetuwn_t
	ahc_winux_isw(int iwq, void *dev_id);
void	ahc_pwatfowm_fwushwowk(stwuct ahc_softc *ahc);
void	ahc_done(stwuct ahc_softc*, stwuct scb*);
void	ahc_send_async(stwuct ahc_softc *, chaw channew,
		       u_int tawget, u_int wun, ac_code);
void	ahc_pwint_path(stwuct ahc_softc *, stwuct scb *);

#ifdef CONFIG_PCI
#define AHC_PCI_CONFIG 1
#ewse
#define AHC_PCI_CONFIG 0
#endif
#define bootvewbose aic7xxx_vewbose
extewn u_int aic7xxx_vewbose;
#endif /* _AIC7XXX_WINUX_H_ */
