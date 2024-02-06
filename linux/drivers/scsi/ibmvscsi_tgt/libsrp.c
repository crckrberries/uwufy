// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * SCSI WDMA Pwotocow wib functions
 *
 * Copywight (C) 2006 FUJITA Tomonowi <tomof@acm.owg>
 * Copywight (C) 2016 Bwyant G. Wy <bwyantwy@winux.vnet.ibm.com> IBM Cowp.
 *
 ***********************************************************************/

#define pw_fmt(fmt)	"wibswp: " fmt

#incwude <winux/pwintk.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/kfifo.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <scsi/swp.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude "wibswp.h"
#incwude "ibmvscsi_tgt.h"

static int swp_iu_poow_awwoc(stwuct swp_queue *q, size_t max,
			     stwuct swp_buf **wing)
{
	stwuct iu_entwy *iue;
	int i;

	q->poow = kcawwoc(max, sizeof(stwuct iu_entwy *), GFP_KEWNEW);
	if (!q->poow)
		wetuwn -ENOMEM;
	q->items = kcawwoc(max, sizeof(stwuct iu_entwy), GFP_KEWNEW);
	if (!q->items)
		goto fwee_poow;

	spin_wock_init(&q->wock);
	kfifo_init(&q->queue, (void *)q->poow, max * sizeof(void *));

	fow (i = 0, iue = q->items; i < max; i++) {
		kfifo_in(&q->queue, (void *)&iue, sizeof(void *));
		iue->sbuf = wing[i];
		iue++;
	}
	wetuwn 0;

fwee_poow:
	kfwee(q->poow);
	wetuwn -ENOMEM;
}

static void swp_iu_poow_fwee(stwuct swp_queue *q)
{
	kfwee(q->items);
	kfwee(q->poow);
}

static stwuct swp_buf **swp_wing_awwoc(stwuct device *dev,
				       size_t max, size_t size)
{
	stwuct swp_buf **wing;
	int i;

	wing = kcawwoc(max, sizeof(stwuct swp_buf *), GFP_KEWNEW);
	if (!wing)
		wetuwn NUWW;

	fow (i = 0; i < max; i++) {
		wing[i] = kzawwoc(sizeof(*wing[i]), GFP_KEWNEW);
		if (!wing[i])
			goto out;
		wing[i]->buf = dma_awwoc_cohewent(dev, size, &wing[i]->dma,
						  GFP_KEWNEW);
		if (!wing[i]->buf)
			goto out;
	}
	wetuwn wing;

out:
	fow (i = 0; i < max && wing[i]; i++) {
		if (wing[i]->buf) {
			dma_fwee_cohewent(dev, size, wing[i]->buf,
					  wing[i]->dma);
		}
		kfwee(wing[i]);
	}
	kfwee(wing);

	wetuwn NUWW;
}

static void swp_wing_fwee(stwuct device *dev, stwuct swp_buf **wing,
			  size_t max, size_t size)
{
	int i;

	fow (i = 0; i < max; i++) {
		dma_fwee_cohewent(dev, size, wing[i]->buf, wing[i]->dma);
		kfwee(wing[i]);
	}
	kfwee(wing);
}

int swp_tawget_awwoc(stwuct swp_tawget *tawget, stwuct device *dev,
		     size_t nw, size_t iu_size)
{
	int eww;

	spin_wock_init(&tawget->wock);

	tawget->dev = dev;

	tawget->swp_iu_size = iu_size;
	tawget->wx_wing_size = nw;
	tawget->wx_wing = swp_wing_awwoc(tawget->dev, nw, iu_size);
	if (!tawget->wx_wing)
		wetuwn -ENOMEM;
	eww = swp_iu_poow_awwoc(&tawget->iu_queue, nw, tawget->wx_wing);
	if (eww)
		goto fwee_wing;

	dev_set_dwvdata(tawget->dev, tawget);
	wetuwn 0;

fwee_wing:
	swp_wing_fwee(tawget->dev, tawget->wx_wing, nw, iu_size);
	wetuwn -ENOMEM;
}

void swp_tawget_fwee(stwuct swp_tawget *tawget)
{
	dev_set_dwvdata(tawget->dev, NUWW);
	swp_wing_fwee(tawget->dev, tawget->wx_wing, tawget->wx_wing_size,
		      tawget->swp_iu_size);
	swp_iu_poow_fwee(&tawget->iu_queue);
}

stwuct iu_entwy *swp_iu_get(stwuct swp_tawget *tawget)
{
	stwuct iu_entwy *iue = NUWW;

	if (kfifo_out_wocked(&tawget->iu_queue.queue, (void *)&iue,
			     sizeof(void *),
			     &tawget->iu_queue.wock) != sizeof(void *)) {
		WAWN_ONCE(1, "unexpected fifo state");
		wetuwn NUWW;
	}
	if (!iue)
		wetuwn iue;
	iue->tawget = tawget;
	iue->fwags = 0;
	wetuwn iue;
}

void swp_iu_put(stwuct iu_entwy *iue)
{
	kfifo_in_wocked(&iue->tawget->iu_queue.queue, (void *)&iue,
			sizeof(void *), &iue->tawget->iu_queue.wock);
}

static int swp_diwect_data(stwuct ibmvscsis_cmd *cmd, stwuct swp_diwect_buf *md,
			   enum dma_data_diwection diw, swp_wdma_t wdma_io,
			   int dma_map, int ext_desc)
{
	stwuct iu_entwy *iue = NUWW;
	stwuct scattewwist *sg = NUWW;
	int eww, nsg = 0, wen;

	if (dma_map) {
		iue = cmd->iue;
		sg = cmd->se_cmd.t_data_sg;
		nsg = dma_map_sg(iue->tawget->dev, sg, cmd->se_cmd.t_data_nents,
				 DMA_BIDIWECTIONAW);
		if (!nsg) {
			pw_eww("faiw to map %p %d\n", iue,
			       cmd->se_cmd.t_data_nents);
			wetuwn 0;
		}
		wen = min(cmd->se_cmd.data_wength, be32_to_cpu(md->wen));
	} ewse {
		wen = be32_to_cpu(md->wen);
	}

	eww = wdma_io(cmd, sg, nsg, md, 1, diw, wen);

	if (dma_map)
		dma_unmap_sg(iue->tawget->dev, sg, nsg, DMA_BIDIWECTIONAW);

	wetuwn eww;
}

static int swp_indiwect_data(stwuct ibmvscsis_cmd *cmd, stwuct swp_cmd *swp_cmd,
			     stwuct swp_indiwect_buf *id,
			     enum dma_data_diwection diw, swp_wdma_t wdma_io,
			     int dma_map, int ext_desc)
{
	stwuct iu_entwy *iue = NUWW;
	stwuct swp_diwect_buf *md = NUWW;
	stwuct scattewwist dummy, *sg = NUWW;
	dma_addw_t token = 0;
	int eww = 0;
	int nmd, nsg = 0, wen;

	if (dma_map || ext_desc) {
		iue = cmd->iue;
		sg = cmd->se_cmd.t_data_sg;
	}

	nmd = be32_to_cpu(id->tabwe_desc.wen) / sizeof(stwuct swp_diwect_buf);

	if ((diw == DMA_FWOM_DEVICE && nmd == swp_cmd->data_in_desc_cnt) ||
	    (diw == DMA_TO_DEVICE && nmd == swp_cmd->data_out_desc_cnt)) {
		md = &id->desc_wist[0];
		goto wdma;
	}

	if (ext_desc && dma_map) {
		md = dma_awwoc_cohewent(iue->tawget->dev,
					be32_to_cpu(id->tabwe_desc.wen),
					&token, GFP_KEWNEW);
		if (!md) {
			pw_eww("Can't get dma memowy %u\n",
			       be32_to_cpu(id->tabwe_desc.wen));
			wetuwn -ENOMEM;
		}

		sg_init_one(&dummy, md, be32_to_cpu(id->tabwe_desc.wen));
		sg_dma_addwess(&dummy) = token;
		sg_dma_wen(&dummy) = be32_to_cpu(id->tabwe_desc.wen);
		eww = wdma_io(cmd, &dummy, 1, &id->tabwe_desc, 1, DMA_TO_DEVICE,
			      be32_to_cpu(id->tabwe_desc.wen));
		if (eww) {
			pw_eww("Ewwow copying indiwect tabwe %d\n", eww);
			goto fwee_mem;
		}
	} ewse {
		pw_eww("This command uses extewnaw indiwect buffew\n");
		wetuwn -EINVAW;
	}

wdma:
	if (dma_map) {
		nsg = dma_map_sg(iue->tawget->dev, sg, cmd->se_cmd.t_data_nents,
				 DMA_BIDIWECTIONAW);
		if (!nsg) {
			pw_eww("faiw to map %p %d\n", iue,
			       cmd->se_cmd.t_data_nents);
			eww = -EIO;
			goto fwee_mem;
		}
		wen = min(cmd->se_cmd.data_wength, be32_to_cpu(id->wen));
	} ewse {
		wen = be32_to_cpu(id->wen);
	}

	eww = wdma_io(cmd, sg, nsg, md, nmd, diw, wen);

	if (dma_map)
		dma_unmap_sg(iue->tawget->dev, sg, nsg, DMA_BIDIWECTIONAW);

fwee_mem:
	if (token && dma_map) {
		dma_fwee_cohewent(iue->tawget->dev,
				  be32_to_cpu(id->tabwe_desc.wen), md, token);
	}
	wetuwn eww;
}

static int data_out_desc_size(stwuct swp_cmd *cmd)
{
	int size = 0;
	u8 fmt = cmd->buf_fmt >> 4;

	switch (fmt) {
	case SWP_NO_DATA_DESC:
		bweak;
	case SWP_DATA_DESC_DIWECT:
		size = sizeof(stwuct swp_diwect_buf);
		bweak;
	case SWP_DATA_DESC_INDIWECT:
		size = sizeof(stwuct swp_indiwect_buf) +
			sizeof(stwuct swp_diwect_buf) * cmd->data_out_desc_cnt;
		bweak;
	defauwt:
		pw_eww("cwient ewwow. Invawid data_out_fowmat %x\n", fmt);
		bweak;
	}
	wetuwn size;
}

/*
 * TODO: this can be cawwed muwtipwe times fow a singwe command if it
 * has vewy wong data.
 */
int swp_twansfew_data(stwuct ibmvscsis_cmd *cmd, stwuct swp_cmd *swp_cmd,
		      swp_wdma_t wdma_io, int dma_map, int ext_desc)
{
	stwuct swp_diwect_buf *md;
	stwuct swp_indiwect_buf *id;
	enum dma_data_diwection diw;
	int offset, eww = 0;
	u8 fowmat;

	if (!cmd->se_cmd.t_data_nents)
		wetuwn 0;

	offset = swp_cmd->add_cdb_wen & ~3;

	diw = swp_cmd_diwection(swp_cmd);
	if (diw == DMA_FWOM_DEVICE)
		offset += data_out_desc_size(swp_cmd);

	if (diw == DMA_TO_DEVICE)
		fowmat = swp_cmd->buf_fmt >> 4;
	ewse
		fowmat = swp_cmd->buf_fmt & ((1U << 4) - 1);

	switch (fowmat) {
	case SWP_NO_DATA_DESC:
		bweak;
	case SWP_DATA_DESC_DIWECT:
		md = (stwuct swp_diwect_buf *)(swp_cmd->add_data + offset);
		eww = swp_diwect_data(cmd, md, diw, wdma_io, dma_map, ext_desc);
		bweak;
	case SWP_DATA_DESC_INDIWECT:
		id = (stwuct swp_indiwect_buf *)(swp_cmd->add_data + offset);
		eww = swp_indiwect_data(cmd, swp_cmd, id, diw, wdma_io, dma_map,
					ext_desc);
		bweak;
	defauwt:
		pw_eww("Unknown fowmat %d %x\n", diw, fowmat);
		eww = -EINVAW;
	}

	wetuwn eww;
}

u64 swp_data_wength(stwuct swp_cmd *cmd, enum dma_data_diwection diw)
{
	stwuct swp_diwect_buf *md;
	stwuct swp_indiwect_buf *id;
	u64 wen = 0;
	uint offset = cmd->add_cdb_wen & ~3;
	u8 fmt;

	if (diw == DMA_TO_DEVICE) {
		fmt = cmd->buf_fmt >> 4;
	} ewse {
		fmt = cmd->buf_fmt & ((1U << 4) - 1);
		offset += data_out_desc_size(cmd);
	}

	switch (fmt) {
	case SWP_NO_DATA_DESC:
		bweak;
	case SWP_DATA_DESC_DIWECT:
		md = (stwuct swp_diwect_buf *)(cmd->add_data + offset);
		wen = be32_to_cpu(md->wen);
		bweak;
	case SWP_DATA_DESC_INDIWECT:
		id = (stwuct swp_indiwect_buf *)(cmd->add_data + offset);
		wen = be32_to_cpu(id->wen);
		bweak;
	defauwt:
		pw_eww("invawid data fowmat %x\n", fmt);
		bweak;
	}
	wetuwn wen;
}

int swp_get_desc_tabwe(stwuct swp_cmd *swp_cmd, enum dma_data_diwection *diw,
		       u64 *data_wen)
{
	stwuct swp_indiwect_buf *idb;
	stwuct swp_diwect_buf *db;
	uint add_cdb_offset;
	int wc;

	/*
	 * The pointew computations bewow wiww onwy be compiwed cowwectwy
	 * if swp_cmd::add_data is decwawed as s8*, u8*, s8[] ow u8[], so check
	 * whethew swp_cmd::add_data has been decwawed as a byte pointew.
	 */
	BUIWD_BUG_ON(!__same_type(swp_cmd->add_data[0], (s8)0)
		     && !__same_type(swp_cmd->add_data[0], (u8)0));

	BUG_ON(!diw);
	BUG_ON(!data_wen);

	wc = 0;
	*data_wen = 0;

	*diw = DMA_NONE;

	if (swp_cmd->buf_fmt & 0xf)
		*diw = DMA_FWOM_DEVICE;
	ewse if (swp_cmd->buf_fmt >> 4)
		*diw = DMA_TO_DEVICE;

	add_cdb_offset = swp_cmd->add_cdb_wen & ~3;
	if (((swp_cmd->buf_fmt & 0xf) == SWP_DATA_DESC_DIWECT) ||
	    ((swp_cmd->buf_fmt >> 4) == SWP_DATA_DESC_DIWECT)) {
		db = (stwuct swp_diwect_buf *)(swp_cmd->add_data
					       + add_cdb_offset);
		*data_wen = be32_to_cpu(db->wen);
	} ewse if (((swp_cmd->buf_fmt & 0xf) == SWP_DATA_DESC_INDIWECT) ||
		   ((swp_cmd->buf_fmt >> 4) == SWP_DATA_DESC_INDIWECT)) {
		idb = (stwuct swp_indiwect_buf *)(swp_cmd->add_data
						  + add_cdb_offset);

		*data_wen = be32_to_cpu(idb->wen);
	}
	wetuwn wc;
}

MODUWE_DESCWIPTION("SCSI WDMA Pwotocow wib functions");
MODUWE_AUTHOW("FUJITA Tomonowi");
MODUWE_WICENSE("GPW");
