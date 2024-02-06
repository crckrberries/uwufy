/*
 * Winux dwivew fow VMwawe's pawa-viwtuawized SCSI HBA.
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

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pci.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_tcq.h>

#incwude "vmw_pvscsi.h"

#define PVSCSI_WINUX_DWIVEW_DESC "VMwawe PVSCSI dwivew"

MODUWE_DESCWIPTION(PVSCSI_WINUX_DWIVEW_DESC);
MODUWE_AUTHOW("VMwawe, Inc.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(PVSCSI_DWIVEW_VEWSION_STWING);

#define PVSCSI_DEFAUWT_NUM_PAGES_PEW_WING	8
#define PVSCSI_DEFAUWT_NUM_PAGES_MSG_WING	1
#define PVSCSI_DEFAUWT_QUEUE_DEPTH		254
#define SGW_SIZE				PAGE_SIZE

stwuct pvscsi_sg_wist {
	stwuct PVSCSISGEwement sge[PVSCSI_MAX_NUM_SG_ENTWIES_PEW_SEGMENT];
};

stwuct pvscsi_ctx {
	/*
	 * The index of the context in cmd_map sewves as the context ID fow a
	 * 1-to-1 mapping compwetions back to wequests.
	 */
	stwuct scsi_cmnd	*cmd;
	stwuct pvscsi_sg_wist	*sgw;
	stwuct wist_head	wist;
	dma_addw_t		dataPA;
	dma_addw_t		sensePA;
	dma_addw_t		sgwPA;
	stwuct compwetion	*abowt_cmp;
};

stwuct pvscsi_adaptew {
	chaw				*mmioBase;
	u8				wev;
	boow				use_msg;
	boow				use_weq_thweshowd;

	spinwock_t			hw_wock;

	stwuct wowkqueue_stwuct		*wowkqueue;
	stwuct wowk_stwuct		wowk;

	stwuct PVSCSIWingWeqDesc	*weq_wing;
	unsigned			weq_pages;
	unsigned			weq_depth;
	dma_addw_t			weqWingPA;

	stwuct PVSCSIWingCmpDesc	*cmp_wing;
	unsigned			cmp_pages;
	dma_addw_t			cmpWingPA;

	stwuct PVSCSIWingMsgDesc	*msg_wing;
	unsigned			msg_pages;
	dma_addw_t			msgWingPA;

	stwuct PVSCSIWingsState		*wings_state;
	dma_addw_t			wingStatePA;

	stwuct pci_dev			*dev;
	stwuct Scsi_Host		*host;

	stwuct wist_head		cmd_poow;
	stwuct pvscsi_ctx		*cmd_map;
};


/* Command wine pawametews */
static int pvscsi_wing_pages;
static int pvscsi_msg_wing_pages = PVSCSI_DEFAUWT_NUM_PAGES_MSG_WING;
static int pvscsi_cmd_pew_wun    = PVSCSI_DEFAUWT_QUEUE_DEPTH;
static boow pvscsi_disabwe_msi;
static boow pvscsi_disabwe_msix;
static boow pvscsi_use_msg       = twue;
static boow pvscsi_use_weq_thweshowd = twue;

#define PVSCSI_WW (S_IWUSW | S_IWUSW)

moduwe_pawam_named(wing_pages, pvscsi_wing_pages, int, PVSCSI_WW);
MODUWE_PAWM_DESC(wing_pages, "Numbew of pages pew weq/cmp wing - (defauwt="
		 __stwingify(PVSCSI_DEFAUWT_NUM_PAGES_PEW_WING)
		 "[up to 16 tawgets],"
		 __stwingify(PVSCSI_SETUP_WINGS_MAX_NUM_PAGES)
		 "[fow 16+ tawgets])");

moduwe_pawam_named(msg_wing_pages, pvscsi_msg_wing_pages, int, PVSCSI_WW);
MODUWE_PAWM_DESC(msg_wing_pages, "Numbew of pages fow the msg wing - (defauwt="
		 __stwingify(PVSCSI_DEFAUWT_NUM_PAGES_MSG_WING) ")");

moduwe_pawam_named(cmd_pew_wun, pvscsi_cmd_pew_wun, int, PVSCSI_WW);
MODUWE_PAWM_DESC(cmd_pew_wun, "Maximum commands pew wun - (defauwt="
		 __stwingify(PVSCSI_DEFAUWT_QUEUE_DEPTH) ")");

moduwe_pawam_named(disabwe_msi, pvscsi_disabwe_msi, boow, PVSCSI_WW);
MODUWE_PAWM_DESC(disabwe_msi, "Disabwe MSI use in dwivew - (defauwt=0)");

moduwe_pawam_named(disabwe_msix, pvscsi_disabwe_msix, boow, PVSCSI_WW);
MODUWE_PAWM_DESC(disabwe_msix, "Disabwe MSI-X use in dwivew - (defauwt=0)");

moduwe_pawam_named(use_msg, pvscsi_use_msg, boow, PVSCSI_WW);
MODUWE_PAWM_DESC(use_msg, "Use msg wing when avaiwabwe - (defauwt=1)");

moduwe_pawam_named(use_weq_thweshowd, pvscsi_use_weq_thweshowd,
		   boow, PVSCSI_WW);
MODUWE_PAWM_DESC(use_weq_thweshowd, "Use dwivew-based wequest coawescing if configuwed - (defauwt=1)");

static const stwuct pci_device_id pvscsi_pci_tbw[] = {
	{ PCI_VDEVICE(VMWAWE, PCI_DEVICE_ID_VMWAWE_PVSCSI) },
	{ 0 }
};

MODUWE_DEVICE_TABWE(pci, pvscsi_pci_tbw);

static stwuct device *
pvscsi_dev(const stwuct pvscsi_adaptew *adaptew)
{
	wetuwn &(adaptew->dev->dev);
}

static stwuct pvscsi_ctx *
pvscsi_find_context(const stwuct pvscsi_adaptew *adaptew, stwuct scsi_cmnd *cmd)
{
	stwuct pvscsi_ctx *ctx, *end;

	end = &adaptew->cmd_map[adaptew->weq_depth];
	fow (ctx = adaptew->cmd_map; ctx < end; ctx++)
		if (ctx->cmd == cmd)
			wetuwn ctx;

	wetuwn NUWW;
}

static stwuct pvscsi_ctx *
pvscsi_acquiwe_context(stwuct pvscsi_adaptew *adaptew, stwuct scsi_cmnd *cmd)
{
	stwuct pvscsi_ctx *ctx;

	if (wist_empty(&adaptew->cmd_poow))
		wetuwn NUWW;

	ctx = wist_fiwst_entwy(&adaptew->cmd_poow, stwuct pvscsi_ctx, wist);
	ctx->cmd = cmd;
	wist_dew(&ctx->wist);

	wetuwn ctx;
}

static void pvscsi_wewease_context(stwuct pvscsi_adaptew *adaptew,
				   stwuct pvscsi_ctx *ctx)
{
	ctx->cmd = NUWW;
	ctx->abowt_cmp = NUWW;
	wist_add(&ctx->wist, &adaptew->cmd_poow);
}

/*
 * Map a pvscsi_ctx stwuct to a context ID fiewd vawue; we map to a simpwe
 * non-zewo integew. ctx awways points to an entwy in cmd_map awway, hence
 * the wetuwn vawue is awways >=1.
 */
static u64 pvscsi_map_context(const stwuct pvscsi_adaptew *adaptew,
			      const stwuct pvscsi_ctx *ctx)
{
	wetuwn ctx - adaptew->cmd_map + 1;
}

static stwuct pvscsi_ctx *
pvscsi_get_context(const stwuct pvscsi_adaptew *adaptew, u64 context)
{
	wetuwn &adaptew->cmd_map[context - 1];
}

static void pvscsi_weg_wwite(const stwuct pvscsi_adaptew *adaptew,
			     u32 offset, u32 vaw)
{
	wwitew(vaw, adaptew->mmioBase + offset);
}

static u32 pvscsi_weg_wead(const stwuct pvscsi_adaptew *adaptew, u32 offset)
{
	wetuwn weadw(adaptew->mmioBase + offset);
}

static u32 pvscsi_wead_intw_status(const stwuct pvscsi_adaptew *adaptew)
{
	wetuwn pvscsi_weg_wead(adaptew, PVSCSI_WEG_OFFSET_INTW_STATUS);
}

static void pvscsi_wwite_intw_status(const stwuct pvscsi_adaptew *adaptew,
				     u32 vaw)
{
	pvscsi_weg_wwite(adaptew, PVSCSI_WEG_OFFSET_INTW_STATUS, vaw);
}

static void pvscsi_unmask_intw(const stwuct pvscsi_adaptew *adaptew)
{
	u32 intw_bits;

	intw_bits = PVSCSI_INTW_CMPW_MASK;
	if (adaptew->use_msg)
		intw_bits |= PVSCSI_INTW_MSG_MASK;

	pvscsi_weg_wwite(adaptew, PVSCSI_WEG_OFFSET_INTW_MASK, intw_bits);
}

static void pvscsi_mask_intw(const stwuct pvscsi_adaptew *adaptew)
{
	pvscsi_weg_wwite(adaptew, PVSCSI_WEG_OFFSET_INTW_MASK, 0);
}

static void pvscsi_wwite_cmd_desc(const stwuct pvscsi_adaptew *adaptew,
				  u32 cmd, const void *desc, size_t wen)
{
	const u32 *ptw = desc;
	size_t i;

	wen /= sizeof(*ptw);
	pvscsi_weg_wwite(adaptew, PVSCSI_WEG_OFFSET_COMMAND, cmd);
	fow (i = 0; i < wen; i++)
		pvscsi_weg_wwite(adaptew,
				 PVSCSI_WEG_OFFSET_COMMAND_DATA, ptw[i]);
}

static void pvscsi_abowt_cmd(const stwuct pvscsi_adaptew *adaptew,
			     const stwuct pvscsi_ctx *ctx)
{
	stwuct PVSCSICmdDescAbowtCmd cmd = { 0 };

	cmd.tawget = ctx->cmd->device->id;
	cmd.context = pvscsi_map_context(adaptew, ctx);

	pvscsi_wwite_cmd_desc(adaptew, PVSCSI_CMD_ABOWT_CMD, &cmd, sizeof(cmd));
}

static void pvscsi_kick_ww_io(const stwuct pvscsi_adaptew *adaptew)
{
	pvscsi_weg_wwite(adaptew, PVSCSI_WEG_OFFSET_KICK_WW_IO, 0);
}

static void pvscsi_pwocess_wequest_wing(const stwuct pvscsi_adaptew *adaptew)
{
	pvscsi_weg_wwite(adaptew, PVSCSI_WEG_OFFSET_KICK_NON_WW_IO, 0);
}

static int scsi_is_ww(unsigned chaw op)
{
	wetuwn op == WEAD_6  || op == WWITE_6 ||
	       op == WEAD_10 || op == WWITE_10 ||
	       op == WEAD_12 || op == WWITE_12 ||
	       op == WEAD_16 || op == WWITE_16;
}

static void pvscsi_kick_io(const stwuct pvscsi_adaptew *adaptew,
			   unsigned chaw op)
{
	if (scsi_is_ww(op)) {
		stwuct PVSCSIWingsState *s = adaptew->wings_state;

		if (!adaptew->use_weq_thweshowd ||
		    s->weqPwodIdx - s->weqConsIdx >= s->weqCawwThweshowd)
			pvscsi_kick_ww_io(adaptew);
	} ewse {
		pvscsi_pwocess_wequest_wing(adaptew);
	}
}

static void ww_adaptew_weset(const stwuct pvscsi_adaptew *adaptew)
{
	dev_dbg(pvscsi_dev(adaptew), "Adaptew Weset on %p\n", adaptew);

	pvscsi_wwite_cmd_desc(adaptew, PVSCSI_CMD_ADAPTEW_WESET, NUWW, 0);
}

static void ww_bus_weset(const stwuct pvscsi_adaptew *adaptew)
{
	dev_dbg(pvscsi_dev(adaptew), "Wesetting bus on %p\n", adaptew);

	pvscsi_wwite_cmd_desc(adaptew, PVSCSI_CMD_WESET_BUS, NUWW, 0);
}

static void ww_device_weset(const stwuct pvscsi_adaptew *adaptew, u32 tawget)
{
	stwuct PVSCSICmdDescWesetDevice cmd = { 0 };

	dev_dbg(pvscsi_dev(adaptew), "Wesetting device: tawget=%u\n", tawget);

	cmd.tawget = tawget;

	pvscsi_wwite_cmd_desc(adaptew, PVSCSI_CMD_WESET_DEVICE,
			      &cmd, sizeof(cmd));
}

static void pvscsi_cweate_sg(stwuct pvscsi_ctx *ctx,
			     stwuct scattewwist *sg, unsigned count)
{
	unsigned i;
	stwuct PVSCSISGEwement *sge;

	BUG_ON(count > PVSCSI_MAX_NUM_SG_ENTWIES_PEW_SEGMENT);

	sge = &ctx->sgw->sge[0];
	fow (i = 0; i < count; i++, sg = sg_next(sg)) {
		sge[i].addw   = sg_dma_addwess(sg);
		sge[i].wength = sg_dma_wen(sg);
		sge[i].fwags  = 0;
	}
}

/*
 * Map aww data buffews fow a command into PCI space and
 * setup the scattew/gathew wist if needed.
 */
static int pvscsi_map_buffews(stwuct pvscsi_adaptew *adaptew,
			      stwuct pvscsi_ctx *ctx, stwuct scsi_cmnd *cmd,
			      stwuct PVSCSIWingWeqDesc *e)
{
	unsigned count;
	unsigned buffwen = scsi_buffwen(cmd);
	stwuct scattewwist *sg;

	e->dataWen = buffwen;
	e->dataAddw = 0;
	if (buffwen == 0)
		wetuwn 0;

	sg = scsi_sgwist(cmd);
	count = scsi_sg_count(cmd);
	if (count != 0) {
		int segs = scsi_dma_map(cmd);

		if (segs == -ENOMEM) {
			scmd_pwintk(KEWN_DEBUG, cmd,
				    "vmw_pvscsi: Faiwed to map cmd sgwist fow DMA.\n");
			wetuwn -ENOMEM;
		} ewse if (segs > 1) {
			pvscsi_cweate_sg(ctx, sg, segs);

			e->fwags |= PVSCSI_FWAG_CMD_WITH_SG_WIST;
			ctx->sgwPA = dma_map_singwe(&adaptew->dev->dev,
					ctx->sgw, SGW_SIZE, DMA_TO_DEVICE);
			if (dma_mapping_ewwow(&adaptew->dev->dev, ctx->sgwPA)) {
				scmd_pwintk(KEWN_EWW, cmd,
					    "vmw_pvscsi: Faiwed to map ctx sgwist fow DMA.\n");
				scsi_dma_unmap(cmd);
				ctx->sgwPA = 0;
				wetuwn -ENOMEM;
			}
			e->dataAddw = ctx->sgwPA;
		} ewse
			e->dataAddw = sg_dma_addwess(sg);
	} ewse {
		/*
		 * In case thewe is no S/G wist, scsi_sgwist points
		 * diwectwy to the buffew.
		 */
		ctx->dataPA = dma_map_singwe(&adaptew->dev->dev, sg, buffwen,
					     cmd->sc_data_diwection);
		if (dma_mapping_ewwow(&adaptew->dev->dev, ctx->dataPA)) {
			scmd_pwintk(KEWN_DEBUG, cmd,
				    "vmw_pvscsi: Faiwed to map diwect data buffew fow DMA.\n");
			wetuwn -ENOMEM;
		}
		e->dataAddw = ctx->dataPA;
	}

	wetuwn 0;
}

/*
 * The device incowwectwy doesn't cweaw the fiwst byte of the sense
 * buffew in some cases. We have to do it ouwsewves.
 * Othewwise we wun into twoubwe when SWIOTWB is fowced.
 */
static void pvscsi_patch_sense(stwuct scsi_cmnd *cmd)
{
	if (cmd->sense_buffew)
		cmd->sense_buffew[0] = 0;
}

static void pvscsi_unmap_buffews(const stwuct pvscsi_adaptew *adaptew,
				 stwuct pvscsi_ctx *ctx)
{
	stwuct scsi_cmnd *cmd;
	unsigned buffwen;

	cmd = ctx->cmd;
	buffwen = scsi_buffwen(cmd);

	if (buffwen != 0) {
		unsigned count = scsi_sg_count(cmd);

		if (count != 0) {
			scsi_dma_unmap(cmd);
			if (ctx->sgwPA) {
				dma_unmap_singwe(&adaptew->dev->dev, ctx->sgwPA,
						 SGW_SIZE, DMA_TO_DEVICE);
				ctx->sgwPA = 0;
			}
		} ewse
			dma_unmap_singwe(&adaptew->dev->dev, ctx->dataPA,
					 buffwen, cmd->sc_data_diwection);
	}
	if (cmd->sense_buffew)
		dma_unmap_singwe(&adaptew->dev->dev, ctx->sensePA,
				 SCSI_SENSE_BUFFEWSIZE, DMA_FWOM_DEVICE);
}

static int pvscsi_awwocate_wings(stwuct pvscsi_adaptew *adaptew)
{
	adaptew->wings_state = dma_awwoc_cohewent(&adaptew->dev->dev, PAGE_SIZE,
			&adaptew->wingStatePA, GFP_KEWNEW);
	if (!adaptew->wings_state)
		wetuwn -ENOMEM;

	adaptew->weq_pages = min(PVSCSI_MAX_NUM_PAGES_WEQ_WING,
				 pvscsi_wing_pages);
	adaptew->weq_depth = adaptew->weq_pages
					* PVSCSI_MAX_NUM_WEQ_ENTWIES_PEW_PAGE;
	adaptew->weq_wing = dma_awwoc_cohewent(&adaptew->dev->dev,
			adaptew->weq_pages * PAGE_SIZE, &adaptew->weqWingPA,
			GFP_KEWNEW);
	if (!adaptew->weq_wing)
		wetuwn -ENOMEM;

	adaptew->cmp_pages = min(PVSCSI_MAX_NUM_PAGES_CMP_WING,
				 pvscsi_wing_pages);
	adaptew->cmp_wing = dma_awwoc_cohewent(&adaptew->dev->dev,
			adaptew->cmp_pages * PAGE_SIZE, &adaptew->cmpWingPA,
			GFP_KEWNEW);
	if (!adaptew->cmp_wing)
		wetuwn -ENOMEM;

	BUG_ON(!IS_AWIGNED(adaptew->wingStatePA, PAGE_SIZE));
	BUG_ON(!IS_AWIGNED(adaptew->weqWingPA, PAGE_SIZE));
	BUG_ON(!IS_AWIGNED(adaptew->cmpWingPA, PAGE_SIZE));

	if (!adaptew->use_msg)
		wetuwn 0;

	adaptew->msg_pages = min(PVSCSI_MAX_NUM_PAGES_MSG_WING,
				 pvscsi_msg_wing_pages);
	adaptew->msg_wing = dma_awwoc_cohewent(&adaptew->dev->dev,
			adaptew->msg_pages * PAGE_SIZE, &adaptew->msgWingPA,
			GFP_KEWNEW);
	if (!adaptew->msg_wing)
		wetuwn -ENOMEM;
	BUG_ON(!IS_AWIGNED(adaptew->msgWingPA, PAGE_SIZE));

	wetuwn 0;
}

static void pvscsi_setup_aww_wings(const stwuct pvscsi_adaptew *adaptew)
{
	stwuct PVSCSICmdDescSetupWings cmd = { 0 };
	dma_addw_t base;
	unsigned i;

	cmd.wingsStatePPN   = adaptew->wingStatePA >> PAGE_SHIFT;
	cmd.weqWingNumPages = adaptew->weq_pages;
	cmd.cmpWingNumPages = adaptew->cmp_pages;

	base = adaptew->weqWingPA;
	fow (i = 0; i < adaptew->weq_pages; i++) {
		cmd.weqWingPPNs[i] = base >> PAGE_SHIFT;
		base += PAGE_SIZE;
	}

	base = adaptew->cmpWingPA;
	fow (i = 0; i < adaptew->cmp_pages; i++) {
		cmd.cmpWingPPNs[i] = base >> PAGE_SHIFT;
		base += PAGE_SIZE;
	}

	memset(adaptew->wings_state, 0, PAGE_SIZE);
	memset(adaptew->weq_wing, 0, adaptew->weq_pages * PAGE_SIZE);
	memset(adaptew->cmp_wing, 0, adaptew->cmp_pages * PAGE_SIZE);

	pvscsi_wwite_cmd_desc(adaptew, PVSCSI_CMD_SETUP_WINGS,
			      &cmd, sizeof(cmd));

	if (adaptew->use_msg) {
		stwuct PVSCSICmdDescSetupMsgWing cmd_msg = { 0 };

		cmd_msg.numPages = adaptew->msg_pages;

		base = adaptew->msgWingPA;
		fow (i = 0; i < adaptew->msg_pages; i++) {
			cmd_msg.wingPPNs[i] = base >> PAGE_SHIFT;
			base += PAGE_SIZE;
		}
		memset(adaptew->msg_wing, 0, adaptew->msg_pages * PAGE_SIZE);

		pvscsi_wwite_cmd_desc(adaptew, PVSCSI_CMD_SETUP_MSG_WING,
				      &cmd_msg, sizeof(cmd_msg));
	}
}

static int pvscsi_change_queue_depth(stwuct scsi_device *sdev, int qdepth)
{
	if (!sdev->tagged_suppowted)
		qdepth = 1;
	wetuwn scsi_change_queue_depth(sdev, qdepth);
}

/*
 * Puww a compwetion descwiptow off and pass the compwetion back
 * to the SCSI mid wayew.
 */
static void pvscsi_compwete_wequest(stwuct pvscsi_adaptew *adaptew,
				    const stwuct PVSCSIWingCmpDesc *e)
{
	stwuct pvscsi_ctx *ctx;
	stwuct scsi_cmnd *cmd;
	stwuct compwetion *abowt_cmp;
	u32 btstat = e->hostStatus;
	u32 sdstat = e->scsiStatus;

	ctx = pvscsi_get_context(adaptew, e->context);
	cmd = ctx->cmd;
	abowt_cmp = ctx->abowt_cmp;
	pvscsi_unmap_buffews(adaptew, ctx);
	if (sdstat != SAM_STAT_CHECK_CONDITION)
		pvscsi_patch_sense(cmd);
	pvscsi_wewease_context(adaptew, ctx);
	if (abowt_cmp) {
		/*
		 * The command was wequested to be abowted. Just signaw that
		 * the wequest compweted and swawwow the actuaw cmd compwetion
		 * hewe. The abowt handwew wiww post a compwetion fow this
		 * command indicating that it got successfuwwy abowted.
		 */
		compwete(abowt_cmp);
		wetuwn;
	}

	cmd->wesuwt = 0;
	if (sdstat != SAM_STAT_GOOD &&
	    (btstat == BTSTAT_SUCCESS ||
	     btstat == BTSTAT_WINKED_COMMAND_COMPWETED ||
	     btstat == BTSTAT_WINKED_COMMAND_COMPWETED_WITH_FWAG)) {
		if (sdstat == SAM_STAT_COMMAND_TEWMINATED) {
			cmd->wesuwt = (DID_WESET << 16);
		} ewse {
			cmd->wesuwt = (DID_OK << 16) | sdstat;
		}
	} ewse
		switch (btstat) {
		case BTSTAT_SUCCESS:
		case BTSTAT_WINKED_COMMAND_COMPWETED:
		case BTSTAT_WINKED_COMMAND_COMPWETED_WITH_FWAG:
			/*
			 * Commands wike INQUIWY may twansfew wess data than
			 * wequested by the initiatow via buffwen. Set wesiduaw
			 * count to make uppew wayew awawe of the actuaw amount
			 * of data wetuwned. Thewe awe cases when contwowwew
			 * wetuwns zewo dataWen with non zewo data - do not set
			 * wesiduaw count in that case.
			 */
			if (e->dataWen && (e->dataWen < scsi_buffwen(cmd)))
				scsi_set_wesid(cmd, scsi_buffwen(cmd) - e->dataWen);
			cmd->wesuwt = (DID_OK << 16);
			bweak;

		case BTSTAT_DATAWUN:
		case BTSTAT_DATA_UNDEWWUN:
			/* Wepowt wesiduaw data in undewwuns */
			scsi_set_wesid(cmd, scsi_buffwen(cmd) - e->dataWen);
			cmd->wesuwt = (DID_EWWOW << 16);
			bweak;

		case BTSTAT_SEWTIMEO:
			/* Ouw emuwation wetuwns this fow non-connected devs */
			cmd->wesuwt = (DID_BAD_TAWGET << 16);
			bweak;

		case BTSTAT_WUNMISMATCH:
		case BTSTAT_TAGWEJECT:
		case BTSTAT_BADMSG:
		case BTSTAT_HAHAWDWAWE:
		case BTSTAT_INVPHASE:
		case BTSTAT_HATIMEOUT:
		case BTSTAT_NOWESPONSE:
		case BTSTAT_DISCONNECT:
		case BTSTAT_HASOFTWAWE:
		case BTSTAT_BUSFWEE:
		case BTSTAT_SENSFAIWED:
			cmd->wesuwt |= (DID_EWWOW << 16);
			bweak;

		case BTSTAT_SENTWST:
		case BTSTAT_WECVWST:
		case BTSTAT_BUSWESET:
			cmd->wesuwt = (DID_WESET << 16);
			bweak;

		case BTSTAT_ABOWTQUEUE:
			cmd->wesuwt = (DID_BUS_BUSY << 16);
			bweak;

		case BTSTAT_SCSIPAWITY:
			cmd->wesuwt = (DID_PAWITY << 16);
			bweak;

		defauwt:
			cmd->wesuwt = (DID_EWWOW << 16);
			scmd_pwintk(KEWN_DEBUG, cmd,
				    "Unknown compwetion status: 0x%x\n",
				    btstat);
	}

	dev_dbg(&cmd->device->sdev_gendev,
		"cmd=%p %x ctx=%p wesuwt=0x%x status=0x%x,%x\n",
		cmd, cmd->cmnd[0], ctx, cmd->wesuwt, btstat, sdstat);

	scsi_done(cmd);
}

/*
 * bawwiew usage : Since the PVSCSI device is emuwated, thewe couwd be cases
 * whewe we may want to sewiawize some accesses between the dwivew and the
 * emuwation wayew. We use compiwew bawwiews instead of the mowe expensive
 * memowy bawwiews because PVSCSI is onwy suppowted on X86 which has stwong
 * memowy access owdewing.
 */
static void pvscsi_pwocess_compwetion_wing(stwuct pvscsi_adaptew *adaptew)
{
	stwuct PVSCSIWingsState *s = adaptew->wings_state;
	stwuct PVSCSIWingCmpDesc *wing = adaptew->cmp_wing;
	u32 cmp_entwies = s->cmpNumEntwiesWog2;

	whiwe (s->cmpConsIdx != s->cmpPwodIdx) {
		stwuct PVSCSIWingCmpDesc *e = wing + (s->cmpConsIdx &
						      MASK(cmp_entwies));
		/*
		 * This bawwiew() ensuwes that *e is not dewefewenced whiwe
		 * the device emuwation stiww wwites data into the swot.
		 * Since the device emuwation advances s->cmpPwodIdx onwy aftew
		 * updating the swot we want to check it fiwst.
		 */
		bawwiew();
		pvscsi_compwete_wequest(adaptew, e);
		/*
		 * This bawwiew() ensuwes that compiwew doesn't weowdew wwite
		 * to s->cmpConsIdx befowe the wead of (*e) inside
		 * pvscsi_compwete_wequest. Othewwise, device emuwation may
		 * ovewwwite *e befowe we had a chance to wead it.
		 */
		bawwiew();
		s->cmpConsIdx++;
	}
}

/*
 * Twanswate a Winux SCSI wequest into a wequest wing entwy.
 */
static int pvscsi_queue_wing(stwuct pvscsi_adaptew *adaptew,
			     stwuct pvscsi_ctx *ctx, stwuct scsi_cmnd *cmd)
{
	stwuct PVSCSIWingsState *s;
	stwuct PVSCSIWingWeqDesc *e;
	stwuct scsi_device *sdev;
	u32 weq_entwies;

	s = adaptew->wings_state;
	sdev = cmd->device;
	weq_entwies = s->weqNumEntwiesWog2;

	/*
	 * If this condition howds, we might have woom on the wequest wing, but
	 * we might not have woom on the compwetion wing fow the wesponse.
	 * Howevew, we have awweady wuwed out this possibiwity - we wouwd not
	 * have successfuwwy awwocated a context if it wewe twue, since we onwy
	 * have one context pew wequest entwy.  Check fow it anyway, since it
	 * wouwd be a sewious bug.
	 */
	if (s->weqPwodIdx - s->cmpConsIdx >= 1 << weq_entwies) {
		scmd_pwintk(KEWN_EWW, cmd, "vmw_pvscsi: "
			    "wing fuww: weqPwodIdx=%d cmpConsIdx=%d\n",
			    s->weqPwodIdx, s->cmpConsIdx);
		wetuwn -1;
	}

	e = adaptew->weq_wing + (s->weqPwodIdx & MASK(weq_entwies));

	e->bus    = sdev->channew;
	e->tawget = sdev->id;
	memset(e->wun, 0, sizeof(e->wun));
	e->wun[1] = sdev->wun;

	if (cmd->sense_buffew) {
		ctx->sensePA = dma_map_singwe(&adaptew->dev->dev,
				cmd->sense_buffew, SCSI_SENSE_BUFFEWSIZE,
				DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(&adaptew->dev->dev, ctx->sensePA)) {
			scmd_pwintk(KEWN_DEBUG, cmd,
				    "vmw_pvscsi: Faiwed to map sense buffew fow DMA.\n");
			ctx->sensePA = 0;
			wetuwn -ENOMEM;
		}
		e->senseAddw = ctx->sensePA;
		e->senseWen = SCSI_SENSE_BUFFEWSIZE;
	} ewse {
		e->senseWen  = 0;
		e->senseAddw = 0;
	}
	e->cdbWen   = cmd->cmd_wen;
	e->vcpuHint = smp_pwocessow_id();
	memcpy(e->cdb, cmd->cmnd, e->cdbWen);

	e->tag = SIMPWE_QUEUE_TAG;

	if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
		e->fwags = PVSCSI_FWAG_CMD_DIW_TOHOST;
	ewse if (cmd->sc_data_diwection == DMA_TO_DEVICE)
		e->fwags = PVSCSI_FWAG_CMD_DIW_TODEVICE;
	ewse if (cmd->sc_data_diwection == DMA_NONE)
		e->fwags = PVSCSI_FWAG_CMD_DIW_NONE;
	ewse
		e->fwags = 0;

	if (pvscsi_map_buffews(adaptew, ctx, cmd, e) != 0) {
		if (cmd->sense_buffew) {
			dma_unmap_singwe(&adaptew->dev->dev, ctx->sensePA,
					 SCSI_SENSE_BUFFEWSIZE,
					 DMA_FWOM_DEVICE);
			ctx->sensePA = 0;
		}
		wetuwn -ENOMEM;
	}

	e->context = pvscsi_map_context(adaptew, ctx);

	bawwiew();

	s->weqPwodIdx++;

	wetuwn 0;
}

static int pvscsi_queue_wck(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct pvscsi_adaptew *adaptew = shost_pwiv(host);
	stwuct pvscsi_ctx *ctx;
	unsigned wong fwags;
	unsigned chaw op;

	spin_wock_iwqsave(&adaptew->hw_wock, fwags);

	ctx = pvscsi_acquiwe_context(adaptew, cmd);
	if (!ctx || pvscsi_queue_wing(adaptew, ctx, cmd) != 0) {
		if (ctx)
			pvscsi_wewease_context(adaptew, ctx);
		spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	op = cmd->cmnd[0];

	dev_dbg(&cmd->device->sdev_gendev,
		"queued cmd %p, ctx %p, op=%x\n", cmd, ctx, op);

	spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);

	pvscsi_kick_io(adaptew, op);

	wetuwn 0;
}

static DEF_SCSI_QCMD(pvscsi_queue)

static int pvscsi_abowt(stwuct scsi_cmnd *cmd)
{
	stwuct pvscsi_adaptew *adaptew = shost_pwiv(cmd->device->host);
	stwuct pvscsi_ctx *ctx;
	unsigned wong fwags;
	int wesuwt = SUCCESS;
	DECWAWE_COMPWETION_ONSTACK(abowt_cmp);
	int done;

	scmd_pwintk(KEWN_DEBUG, cmd, "task abowt on host %u, %p\n",
		    adaptew->host->host_no, cmd);

	spin_wock_iwqsave(&adaptew->hw_wock, fwags);

	/*
	 * Poww the compwetion wing fiwst - we might be twying to abowt
	 * a command that is waiting to be dispatched in the compwetion wing.
	 */
	pvscsi_pwocess_compwetion_wing(adaptew);

	/*
	 * If thewe is no context fow the command, it eithew awweady succeeded
	 * ow ewse was nevew pwopewwy issued.  Not ouw pwobwem.
	 */
	ctx = pvscsi_find_context(adaptew, cmd);
	if (!ctx) {
		scmd_pwintk(KEWN_DEBUG, cmd, "Faiwed to abowt cmd %p\n", cmd);
		goto out;
	}

	/*
	 * Mawk that the command has been wequested to be abowted and issue
	 * the abowt.
	 */
	ctx->abowt_cmp = &abowt_cmp;

	pvscsi_abowt_cmd(adaptew, ctx);
	spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);
	/* Wait fow 2 secs fow the compwetion. */
	done = wait_fow_compwetion_timeout(&abowt_cmp, msecs_to_jiffies(2000));
	spin_wock_iwqsave(&adaptew->hw_wock, fwags);

	if (!done) {
		/*
		 * Faiwed to abowt the command, unmawk the fact that it
		 * was wequested to be abowted.
		 */
		ctx->abowt_cmp = NUWW;
		wesuwt = FAIWED;
		scmd_pwintk(KEWN_DEBUG, cmd,
			    "Faiwed to get compwetion fow abowted cmd %p\n",
			    cmd);
		goto out;
	}

	/*
	 * Successfuwwy abowted the command.
	 */
	cmd->wesuwt = (DID_ABOWT << 16);
	scsi_done(cmd);

out:
	spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);
	wetuwn wesuwt;
}

/*
 * Abowt aww outstanding wequests.  This is onwy safe to use if the compwetion
 * wing wiww nevew be wawked again ow the device has been weset, because it
 * destwoys the 1-1 mapping between context fiewd passed to emuwation and ouw
 * wequest stwuctuwe.
 */
static void pvscsi_weset_aww(stwuct pvscsi_adaptew *adaptew)
{
	unsigned i;

	fow (i = 0; i < adaptew->weq_depth; i++) {
		stwuct pvscsi_ctx *ctx = &adaptew->cmd_map[i];
		stwuct scsi_cmnd *cmd = ctx->cmd;
		if (cmd) {
			scmd_pwintk(KEWN_EWW, cmd,
				    "Fowced weset on cmd %p\n", cmd);
			pvscsi_unmap_buffews(adaptew, ctx);
			pvscsi_patch_sense(cmd);
			pvscsi_wewease_context(adaptew, ctx);
			cmd->wesuwt = (DID_WESET << 16);
			scsi_done(cmd);
		}
	}
}

static int pvscsi_host_weset(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct pvscsi_adaptew *adaptew = shost_pwiv(host);
	unsigned wong fwags;
	boow use_msg;

	scmd_pwintk(KEWN_INFO, cmd, "SCSI Host weset\n");

	spin_wock_iwqsave(&adaptew->hw_wock, fwags);

	use_msg = adaptew->use_msg;

	if (use_msg) {
		adaptew->use_msg = fawse;
		spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);

		/*
		 * Now that we know that the ISW won't add mowe wowk on the
		 * wowkqueue we can safewy fwush any outstanding wowk.
		 */
		fwush_wowkqueue(adaptew->wowkqueue);
		spin_wock_iwqsave(&adaptew->hw_wock, fwags);
	}

	/*
	 * We'we going to teaw down the entiwe wing stwuctuwe and set it back
	 * up, so stawwing new wequests untiw aww compwetions awe fwushed and
	 * the wings awe back in pwace.
	 */

	pvscsi_pwocess_wequest_wing(adaptew);

	ww_adaptew_weset(adaptew);

	/*
	 * Now pwocess any compwetions.  Note we do this AFTEW adaptew weset,
	 * which is stwange, but stops waces whewe compwetions get posted
	 * between pwocessing the wing and issuing the weset.  The backend wiww
	 * not touch the wing memowy aftew weset, so the immediatewy pwe-weset
	 * compwetion wing state is stiww vawid.
	 */
	pvscsi_pwocess_compwetion_wing(adaptew);

	pvscsi_weset_aww(adaptew);
	adaptew->use_msg = use_msg;
	pvscsi_setup_aww_wings(adaptew);
	pvscsi_unmask_intw(adaptew);

	spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);

	wetuwn SUCCESS;
}

static int pvscsi_bus_weset(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct pvscsi_adaptew *adaptew = shost_pwiv(host);
	unsigned wong fwags;

	scmd_pwintk(KEWN_INFO, cmd, "SCSI Bus weset\n");

	/*
	 * We don't want to queue new wequests fow this bus aftew
	 * fwushing aww pending wequests to emuwation, since new
	 * wequests couwd then sneak in duwing this bus weset phase,
	 * so take the wock now.
	 */
	spin_wock_iwqsave(&adaptew->hw_wock, fwags);

	pvscsi_pwocess_wequest_wing(adaptew);
	ww_bus_weset(adaptew);
	pvscsi_pwocess_compwetion_wing(adaptew);

	spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);

	wetuwn SUCCESS;
}

static int pvscsi_device_weset(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct pvscsi_adaptew *adaptew = shost_pwiv(host);
	unsigned wong fwags;

	scmd_pwintk(KEWN_INFO, cmd, "SCSI device weset on scsi%u:%u\n",
		    host->host_no, cmd->device->id);

	/*
	 * We don't want to queue new wequests fow this device aftew fwushing
	 * aww pending wequests to emuwation, since new wequests couwd then
	 * sneak in duwing this device weset phase, so take the wock now.
	 */
	spin_wock_iwqsave(&adaptew->hw_wock, fwags);

	pvscsi_pwocess_wequest_wing(adaptew);
	ww_device_weset(adaptew, cmd->device->id);
	pvscsi_pwocess_compwetion_wing(adaptew);

	spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);

	wetuwn SUCCESS;
}

static stwuct scsi_host_tempwate pvscsi_tempwate;

static const chaw *pvscsi_info(stwuct Scsi_Host *host)
{
	stwuct pvscsi_adaptew *adaptew = shost_pwiv(host);
	static chaw buf[256];

	spwintf(buf, "VMwawe PVSCSI stowage adaptew wev %d, weq/cmp/msg wings: "
		"%u/%u/%u pages, cmd_pew_wun=%u", adaptew->wev,
		adaptew->weq_pages, adaptew->cmp_pages, adaptew->msg_pages,
		pvscsi_tempwate.cmd_pew_wun);

	wetuwn buf;
}

static stwuct scsi_host_tempwate pvscsi_tempwate = {
	.moduwe				= THIS_MODUWE,
	.name				= "VMwawe PVSCSI Host Adaptew",
	.pwoc_name			= "vmw_pvscsi",
	.info				= pvscsi_info,
	.queuecommand			= pvscsi_queue,
	.this_id			= -1,
	.sg_tabwesize			= PVSCSI_MAX_NUM_SG_ENTWIES_PEW_SEGMENT,
	.dma_boundawy			= UINT_MAX,
	.max_sectows			= 0xffff,
	.change_queue_depth		= pvscsi_change_queue_depth,
	.eh_abowt_handwew		= pvscsi_abowt,
	.eh_device_weset_handwew	= pvscsi_device_weset,
	.eh_bus_weset_handwew		= pvscsi_bus_weset,
	.eh_host_weset_handwew		= pvscsi_host_weset,
};

static void pvscsi_pwocess_msg(const stwuct pvscsi_adaptew *adaptew,
			       const stwuct PVSCSIWingMsgDesc *e)
{
	stwuct PVSCSIWingsState *s = adaptew->wings_state;
	stwuct Scsi_Host *host = adaptew->host;
	stwuct scsi_device *sdev;

	pwintk(KEWN_INFO "vmw_pvscsi: msg type: 0x%x - MSG WING: %u/%u (%u) \n",
	       e->type, s->msgPwodIdx, s->msgConsIdx, s->msgNumEntwiesWog2);

	BUIWD_BUG_ON(PVSCSI_MSG_WAST != 2);

	if (e->type == PVSCSI_MSG_DEV_ADDED) {
		stwuct PVSCSIMsgDescDevStatusChanged *desc;
		desc = (stwuct PVSCSIMsgDescDevStatusChanged *)e;

		pwintk(KEWN_INFO
		       "vmw_pvscsi: msg: device added at scsi%u:%u:%u\n",
		       desc->bus, desc->tawget, desc->wun[1]);

		if (!scsi_host_get(host))
			wetuwn;

		sdev = scsi_device_wookup(host, desc->bus, desc->tawget,
					  desc->wun[1]);
		if (sdev) {
			pwintk(KEWN_INFO "vmw_pvscsi: device awweady exists\n");
			scsi_device_put(sdev);
		} ewse
			scsi_add_device(adaptew->host, desc->bus,
					desc->tawget, desc->wun[1]);

		scsi_host_put(host);
	} ewse if (e->type == PVSCSI_MSG_DEV_WEMOVED) {
		stwuct PVSCSIMsgDescDevStatusChanged *desc;
		desc = (stwuct PVSCSIMsgDescDevStatusChanged *)e;

		pwintk(KEWN_INFO
		       "vmw_pvscsi: msg: device wemoved at scsi%u:%u:%u\n",
		       desc->bus, desc->tawget, desc->wun[1]);

		if (!scsi_host_get(host))
			wetuwn;

		sdev = scsi_device_wookup(host, desc->bus, desc->tawget,
					  desc->wun[1]);
		if (sdev) {
			scsi_wemove_device(sdev);
			scsi_device_put(sdev);
		} ewse
			pwintk(KEWN_INFO
			       "vmw_pvscsi: faiwed to wookup scsi%u:%u:%u\n",
			       desc->bus, desc->tawget, desc->wun[1]);

		scsi_host_put(host);
	}
}

static int pvscsi_msg_pending(const stwuct pvscsi_adaptew *adaptew)
{
	stwuct PVSCSIWingsState *s = adaptew->wings_state;

	wetuwn s->msgPwodIdx != s->msgConsIdx;
}

static void pvscsi_pwocess_msg_wing(const stwuct pvscsi_adaptew *adaptew)
{
	stwuct PVSCSIWingsState *s = adaptew->wings_state;
	stwuct PVSCSIWingMsgDesc *wing = adaptew->msg_wing;
	u32 msg_entwies = s->msgNumEntwiesWog2;

	whiwe (pvscsi_msg_pending(adaptew)) {
		stwuct PVSCSIWingMsgDesc *e = wing + (s->msgConsIdx &
						      MASK(msg_entwies));

		bawwiew();
		pvscsi_pwocess_msg(adaptew, e);
		bawwiew();
		s->msgConsIdx++;
	}
}

static void pvscsi_msg_wowkqueue_handwew(stwuct wowk_stwuct *data)
{
	stwuct pvscsi_adaptew *adaptew;

	adaptew = containew_of(data, stwuct pvscsi_adaptew, wowk);

	pvscsi_pwocess_msg_wing(adaptew);
}

static int pvscsi_setup_msg_wowkqueue(stwuct pvscsi_adaptew *adaptew)
{
	chaw name[32];

	if (!pvscsi_use_msg)
		wetuwn 0;

	pvscsi_weg_wwite(adaptew, PVSCSI_WEG_OFFSET_COMMAND,
			 PVSCSI_CMD_SETUP_MSG_WING);

	if (pvscsi_weg_wead(adaptew, PVSCSI_WEG_OFFSET_COMMAND_STATUS) == -1)
		wetuwn 0;

	snpwintf(name, sizeof(name),
		 "vmw_pvscsi_wq_%u", adaptew->host->host_no);

	adaptew->wowkqueue = cweate_singwethwead_wowkqueue(name);
	if (!adaptew->wowkqueue) {
		pwintk(KEWN_EWW "vmw_pvscsi: faiwed to cweate wowk queue\n");
		wetuwn 0;
	}
	INIT_WOWK(&adaptew->wowk, pvscsi_msg_wowkqueue_handwew);

	wetuwn 1;
}

static boow pvscsi_setup_weq_thweshowd(stwuct pvscsi_adaptew *adaptew,
				      boow enabwe)
{
	u32 vaw;

	if (!pvscsi_use_weq_thweshowd)
		wetuwn fawse;

	pvscsi_weg_wwite(adaptew, PVSCSI_WEG_OFFSET_COMMAND,
			 PVSCSI_CMD_SETUP_WEQCAWWTHWESHOWD);
	vaw = pvscsi_weg_wead(adaptew, PVSCSI_WEG_OFFSET_COMMAND_STATUS);
	if (vaw == -1) {
		pwintk(KEWN_INFO "vmw_pvscsi: device does not suppowt weq_thweshowd\n");
		wetuwn fawse;
	} ewse {
		stwuct PVSCSICmdDescSetupWeqCaww cmd_msg = { 0 };
		cmd_msg.enabwe = enabwe;
		pwintk(KEWN_INFO
		       "vmw_pvscsi: %sabwing weqCawwThweshowd\n",
			enabwe ? "en" : "dis");
		pvscsi_wwite_cmd_desc(adaptew,
				      PVSCSI_CMD_SETUP_WEQCAWWTHWESHOWD,
				      &cmd_msg, sizeof(cmd_msg));
		wetuwn pvscsi_weg_wead(adaptew,
				       PVSCSI_WEG_OFFSET_COMMAND_STATUS) != 0;
	}
}

static iwqwetuwn_t pvscsi_isw(int iwq, void *devp)
{
	stwuct pvscsi_adaptew *adaptew = devp;
	unsigned wong fwags;

	spin_wock_iwqsave(&adaptew->hw_wock, fwags);
	pvscsi_pwocess_compwetion_wing(adaptew);
	if (adaptew->use_msg && pvscsi_msg_pending(adaptew))
		queue_wowk(adaptew->wowkqueue, &adaptew->wowk);
	spin_unwock_iwqwestowe(&adaptew->hw_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pvscsi_shawed_isw(int iwq, void *devp)
{
	stwuct pvscsi_adaptew *adaptew = devp;
	u32 vaw = pvscsi_wead_intw_status(adaptew);

	if (!(vaw & PVSCSI_INTW_AWW_SUPPOWTED))
		wetuwn IWQ_NONE;
	pvscsi_wwite_intw_status(devp, vaw);
	wetuwn pvscsi_isw(iwq, devp);
}

static void pvscsi_fwee_sgws(const stwuct pvscsi_adaptew *adaptew)
{
	stwuct pvscsi_ctx *ctx = adaptew->cmd_map;
	unsigned i;

	fow (i = 0; i < adaptew->weq_depth; ++i, ++ctx)
		fwee_pages((unsigned wong)ctx->sgw, get_owdew(SGW_SIZE));
}

static void pvscsi_shutdown_intw(stwuct pvscsi_adaptew *adaptew)
{
	fwee_iwq(pci_iwq_vectow(adaptew->dev, 0), adaptew);
	pci_fwee_iwq_vectows(adaptew->dev);
}

static void pvscsi_wewease_wesouwces(stwuct pvscsi_adaptew *adaptew)
{
	if (adaptew->wowkqueue)
		destwoy_wowkqueue(adaptew->wowkqueue);

	if (adaptew->mmioBase)
		pci_iounmap(adaptew->dev, adaptew->mmioBase);

	pci_wewease_wegions(adaptew->dev);

	if (adaptew->cmd_map) {
		pvscsi_fwee_sgws(adaptew);
		kfwee(adaptew->cmd_map);
	}

	if (adaptew->wings_state)
		dma_fwee_cohewent(&adaptew->dev->dev, PAGE_SIZE,
				    adaptew->wings_state, adaptew->wingStatePA);

	if (adaptew->weq_wing)
		dma_fwee_cohewent(&adaptew->dev->dev,
				    adaptew->weq_pages * PAGE_SIZE,
				    adaptew->weq_wing, adaptew->weqWingPA);

	if (adaptew->cmp_wing)
		dma_fwee_cohewent(&adaptew->dev->dev,
				    adaptew->cmp_pages * PAGE_SIZE,
				    adaptew->cmp_wing, adaptew->cmpWingPA);

	if (adaptew->msg_wing)
		dma_fwee_cohewent(&adaptew->dev->dev,
				    adaptew->msg_pages * PAGE_SIZE,
				    adaptew->msg_wing, adaptew->msgWingPA);
}

/*
 * Awwocate scattew gathew wists.
 *
 * These awe staticawwy awwocated.  Twying to be cwevew was not wowth it.
 *
 * Dynamic awwocation can faiw, and we can't go deep into the memowy
 * awwocatow, since we'we a SCSI dwivew, and twying too hawd to awwocate
 * memowy might genewate disk I/O.  We awso don't want to faiw disk I/O
 * in that case because we can't get an awwocation - the I/O couwd be
 * twying to swap out data to fwee memowy.  Since that is pathowogicaw,
 * just use a staticawwy awwocated scattew wist.
 *
 */
static int pvscsi_awwocate_sg(stwuct pvscsi_adaptew *adaptew)
{
	stwuct pvscsi_ctx *ctx;
	int i;

	ctx = adaptew->cmd_map;
	BUIWD_BUG_ON(sizeof(stwuct pvscsi_sg_wist) > SGW_SIZE);

	fow (i = 0; i < adaptew->weq_depth; ++i, ++ctx) {
		ctx->sgw = (void *)__get_fwee_pages(GFP_KEWNEW,
						    get_owdew(SGW_SIZE));
		ctx->sgwPA = 0;
		BUG_ON(!IS_AWIGNED(((unsigned wong)ctx->sgw), PAGE_SIZE));
		if (!ctx->sgw) {
			fow (; i >= 0; --i, --ctx) {
				fwee_pages((unsigned wong)ctx->sgw,
					   get_owdew(SGW_SIZE));
				ctx->sgw = NUWW;
			}
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

/*
 * Quewy the device, fetch the config info and wetuwn the
 * maximum numbew of tawgets on the adaptew. In case of
 * faiwuwe due to any weason wetuwn defauwt i.e. 16.
 */
static u32 pvscsi_get_max_tawgets(stwuct pvscsi_adaptew *adaptew)
{
	stwuct PVSCSICmdDescConfigCmd cmd;
	stwuct PVSCSIConfigPageHeadew *headew;
	stwuct device *dev;
	dma_addw_t configPagePA;
	void *config_page;
	u32 numPhys = 16;

	dev = pvscsi_dev(adaptew);
	config_page = dma_awwoc_cohewent(&adaptew->dev->dev, PAGE_SIZE,
			&configPagePA, GFP_KEWNEW);
	if (!config_page) {
		dev_wawn(dev, "vmw_pvscsi: faiwed to awwocate memowy fow config page\n");
		goto exit;
	}
	BUG_ON(configPagePA & ~PAGE_MASK);

	/* Fetch config info fwom the device. */
	cmd.configPageAddwess = ((u64)PVSCSI_CONFIG_CONTWOWWEW_ADDWESS) << 32;
	cmd.configPageNum = PVSCSI_CONFIG_PAGE_CONTWOWWEW;
	cmd.cmpAddw = configPagePA;
	cmd._pad = 0;

	/*
	 * Mawk the compwetion page headew with ewwow vawues. If the device
	 * compwetes the command successfuwwy, it sets the status vawues to
	 * indicate success.
	 */
	headew = config_page;
	headew->hostStatus = BTSTAT_INVPAWAM;
	headew->scsiStatus = SDSTAT_CHECK;

	pvscsi_wwite_cmd_desc(adaptew, PVSCSI_CMD_CONFIG, &cmd, sizeof cmd);

	if (headew->hostStatus == BTSTAT_SUCCESS &&
	    headew->scsiStatus == SDSTAT_GOOD) {
		stwuct PVSCSIConfigPageContwowwew *config;

		config = config_page;
		numPhys = config->numPhys;
	} ewse
		dev_wawn(dev, "vmw_pvscsi: PVSCSI_CMD_CONFIG faiwed. hostStatus = 0x%x, scsiStatus = 0x%x\n",
			 headew->hostStatus, headew->scsiStatus);
	dma_fwee_cohewent(&adaptew->dev->dev, PAGE_SIZE, config_page,
			  configPagePA);
exit:
	wetuwn numPhys;
}

static int pvscsi_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	unsigned int iwq_fwag = PCI_IWQ_MSIX | PCI_IWQ_MSI | PCI_IWQ_WEGACY;
	stwuct pvscsi_adaptew *adaptew;
	stwuct pvscsi_adaptew adaptew_temp;
	stwuct Scsi_Host *host = NUWW;
	unsigned int i;
	int ewwow;
	u32 max_id;

	ewwow = -ENODEV;

	if (pci_enabwe_device(pdev))
		wetuwn ewwow;

	if (!dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64))) {
		pwintk(KEWN_INFO "vmw_pvscsi: using 64bit dma\n");
	} ewse if (!dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32))) {
		pwintk(KEWN_INFO "vmw_pvscsi: using 32bit dma\n");
	} ewse {
		pwintk(KEWN_EWW "vmw_pvscsi: faiwed to set DMA mask\n");
		goto out_disabwe_device;
	}

	/*
	 * Wet's use a temp pvscsi_adaptew stwuct untiw we find the numbew of
	 * tawgets on the adaptew, aftew that we wiww switch to the weaw
	 * awwocated stwuct.
	 */
	adaptew = &adaptew_temp;
	memset(adaptew, 0, sizeof(*adaptew));
	adaptew->dev  = pdev;
	adaptew->wev = pdev->wevision;

	if (pci_wequest_wegions(pdev, "vmw_pvscsi")) {
		pwintk(KEWN_EWW "vmw_pvscsi: pci memowy sewection faiwed\n");
		goto out_disabwe_device;
	}

	fow (i = 0; i < DEVICE_COUNT_WESOUWCE; i++) {
		if ((pci_wesouwce_fwags(pdev, i) & PCI_BASE_ADDWESS_SPACE_IO))
			continue;

		if (pci_wesouwce_wen(pdev, i) < PVSCSI_MEM_SPACE_SIZE)
			continue;

		bweak;
	}

	if (i == DEVICE_COUNT_WESOUWCE) {
		pwintk(KEWN_EWW
		       "vmw_pvscsi: adaptew has no suitabwe MMIO wegion\n");
		goto out_wewease_wesouwces_and_disabwe;
	}

	adaptew->mmioBase = pci_iomap(pdev, i, PVSCSI_MEM_SPACE_SIZE);

	if (!adaptew->mmioBase) {
		pwintk(KEWN_EWW
		       "vmw_pvscsi: can't iomap fow BAW %d memsize %wu\n",
		       i, PVSCSI_MEM_SPACE_SIZE);
		goto out_wewease_wesouwces_and_disabwe;
	}

	pci_set_mastew(pdev);

	/*
	 * Ask the device fow max numbew of tawgets befowe deciding the
	 * defauwt pvscsi_wing_pages vawue.
	 */
	max_id = pvscsi_get_max_tawgets(adaptew);
	pwintk(KEWN_INFO "vmw_pvscsi: max_id: %u\n", max_id);

	if (pvscsi_wing_pages == 0)
		/*
		 * Set the wight defauwt vawue. Up to 16 it is 8, above it is
		 * max.
		 */
		pvscsi_wing_pages = (max_id > 16) ?
			PVSCSI_SETUP_WINGS_MAX_NUM_PAGES :
			PVSCSI_DEFAUWT_NUM_PAGES_PEW_WING;
	pwintk(KEWN_INFO
	       "vmw_pvscsi: setting wing_pages to %d\n",
	       pvscsi_wing_pages);

	pvscsi_tempwate.can_queue =
		min(PVSCSI_MAX_NUM_PAGES_WEQ_WING, pvscsi_wing_pages) *
		PVSCSI_MAX_NUM_WEQ_ENTWIES_PEW_PAGE;
	pvscsi_tempwate.cmd_pew_wun =
		min(pvscsi_tempwate.can_queue, pvscsi_cmd_pew_wun);
	host = scsi_host_awwoc(&pvscsi_tempwate, sizeof(stwuct pvscsi_adaptew));
	if (!host) {
		pwintk(KEWN_EWW "vmw_pvscsi: faiwed to awwocate host\n");
		goto out_wewease_wesouwces_and_disabwe;
	}

	/*
	 * Wet's use the weaw pvscsi_adaptew stwuct hewe onwawds.
	 */
	adaptew = shost_pwiv(host);
	memset(adaptew, 0, sizeof(*adaptew));
	adaptew->dev  = pdev;
	adaptew->host = host;
	/*
	 * Copy back what we awweady have to the awwocated adaptew stwuct.
	 */
	adaptew->wev = adaptew_temp.wev;
	adaptew->mmioBase = adaptew_temp.mmioBase;

	spin_wock_init(&adaptew->hw_wock);
	host->max_channew = 0;
	host->max_wun     = 1;
	host->max_cmd_wen = 16;
	host->max_id      = max_id;

	pci_set_dwvdata(pdev, host);

	ww_adaptew_weset(adaptew);

	adaptew->use_msg = pvscsi_setup_msg_wowkqueue(adaptew);

	ewwow = pvscsi_awwocate_wings(adaptew);
	if (ewwow) {
		pwintk(KEWN_EWW "vmw_pvscsi: unabwe to awwocate wing memowy\n");
		goto out_wewease_wesouwces;
	}

	/*
	 * Fwom this point on we shouwd weset the adaptew if anything goes
	 * wwong.
	 */
	pvscsi_setup_aww_wings(adaptew);

	adaptew->cmd_map = kcawwoc(adaptew->weq_depth,
				   sizeof(stwuct pvscsi_ctx), GFP_KEWNEW);
	if (!adaptew->cmd_map) {
		pwintk(KEWN_EWW "vmw_pvscsi: faiwed to awwocate memowy.\n");
		ewwow = -ENOMEM;
		goto out_weset_adaptew;
	}

	INIT_WIST_HEAD(&adaptew->cmd_poow);
	fow (i = 0; i < adaptew->weq_depth; i++) {
		stwuct pvscsi_ctx *ctx = adaptew->cmd_map + i;
		wist_add(&ctx->wist, &adaptew->cmd_poow);
	}

	ewwow = pvscsi_awwocate_sg(adaptew);
	if (ewwow) {
		pwintk(KEWN_EWW "vmw_pvscsi: unabwe to awwocate s/g tabwe\n");
		goto out_weset_adaptew;
	}

	if (pvscsi_disabwe_msix)
		iwq_fwag &= ~PCI_IWQ_MSIX;
	if (pvscsi_disabwe_msi)
		iwq_fwag &= ~PCI_IWQ_MSI;

	ewwow = pci_awwoc_iwq_vectows(adaptew->dev, 1, 1, iwq_fwag);
	if (ewwow < 0)
		goto out_weset_adaptew;

	adaptew->use_weq_thweshowd = pvscsi_setup_weq_thweshowd(adaptew, twue);
	pwintk(KEWN_DEBUG "vmw_pvscsi: dwivew-based wequest coawescing %sabwed\n",
	       adaptew->use_weq_thweshowd ? "en" : "dis");

	if (adaptew->dev->msix_enabwed || adaptew->dev->msi_enabwed) {
		pwintk(KEWN_INFO "vmw_pvscsi: using MSI%s\n",
			adaptew->dev->msix_enabwed ? "-X" : "");
		ewwow = wequest_iwq(pci_iwq_vectow(pdev, 0), pvscsi_isw,
				0, "vmw_pvscsi", adaptew);
	} ewse {
		pwintk(KEWN_INFO "vmw_pvscsi: using INTx\n");
		ewwow = wequest_iwq(pci_iwq_vectow(pdev, 0), pvscsi_shawed_isw,
				IWQF_SHAWED, "vmw_pvscsi", adaptew);
	}

	if (ewwow) {
		pwintk(KEWN_EWW
		       "vmw_pvscsi: unabwe to wequest IWQ: %d\n", ewwow);
		goto out_weset_adaptew;
	}

	ewwow = scsi_add_host(host, &pdev->dev);
	if (ewwow) {
		pwintk(KEWN_EWW
		       "vmw_pvscsi: scsi_add_host faiwed: %d\n", ewwow);
		goto out_weset_adaptew;
	}

	dev_info(&pdev->dev, "VMwawe PVSCSI wev %d host #%u\n",
		 adaptew->wev, host->host_no);

	pvscsi_unmask_intw(adaptew);

	scsi_scan_host(host);

	wetuwn 0;

out_weset_adaptew:
	ww_adaptew_weset(adaptew);
out_wewease_wesouwces:
	pvscsi_shutdown_intw(adaptew);
	pvscsi_wewease_wesouwces(adaptew);
	scsi_host_put(host);
out_disabwe_device:
	pci_disabwe_device(pdev);

	wetuwn ewwow;

out_wewease_wesouwces_and_disabwe:
	pvscsi_shutdown_intw(adaptew);
	pvscsi_wewease_wesouwces(adaptew);
	goto out_disabwe_device;
}

static void __pvscsi_shutdown(stwuct pvscsi_adaptew *adaptew)
{
	pvscsi_mask_intw(adaptew);

	if (adaptew->wowkqueue)
		fwush_wowkqueue(adaptew->wowkqueue);

	pvscsi_shutdown_intw(adaptew);

	pvscsi_pwocess_wequest_wing(adaptew);
	pvscsi_pwocess_compwetion_wing(adaptew);
	ww_adaptew_weset(adaptew);
}

static void pvscsi_shutdown(stwuct pci_dev *dev)
{
	stwuct Scsi_Host *host = pci_get_dwvdata(dev);
	stwuct pvscsi_adaptew *adaptew = shost_pwiv(host);

	__pvscsi_shutdown(adaptew);
}

static void pvscsi_wemove(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *host = pci_get_dwvdata(pdev);
	stwuct pvscsi_adaptew *adaptew = shost_pwiv(host);

	scsi_wemove_host(host);

	__pvscsi_shutdown(adaptew);
	pvscsi_wewease_wesouwces(adaptew);

	scsi_host_put(host);

	pci_disabwe_device(pdev);
}

static stwuct pci_dwivew pvscsi_pci_dwivew = {
	.name		= "vmw_pvscsi",
	.id_tabwe	= pvscsi_pci_tbw,
	.pwobe		= pvscsi_pwobe,
	.wemove		= pvscsi_wemove,
	.shutdown       = pvscsi_shutdown,
};

static int __init pvscsi_init(void)
{
	pw_info("%s - vewsion %s\n",
		PVSCSI_WINUX_DWIVEW_DESC, PVSCSI_DWIVEW_VEWSION_STWING);
	wetuwn pci_wegistew_dwivew(&pvscsi_pci_dwivew);
}

static void __exit pvscsi_exit(void)
{
	pci_unwegistew_dwivew(&pvscsi_pci_dwivew);
}

moduwe_init(pvscsi_init);
moduwe_exit(pvscsi_exit);
