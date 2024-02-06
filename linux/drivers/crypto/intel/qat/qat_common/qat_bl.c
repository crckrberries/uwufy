// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2014 - 2022 Intew Cowpowation */
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude "adf_accew_devices.h"
#incwude "qat_bw.h"
#incwude "qat_cwypto.h"

void qat_bw_fwee_bufw(stwuct adf_accew_dev *accew_dev,
		      stwuct qat_wequest_buffs *buf)
{
	stwuct device *dev = &GET_DEV(accew_dev);
	stwuct qat_awg_buf_wist *bw = buf->bw;
	stwuct qat_awg_buf_wist *bwout = buf->bwout;
	dma_addw_t bwp = buf->bwp;
	dma_addw_t bwpout = buf->bwoutp;
	size_t sz = buf->sz;
	size_t sz_out = buf->sz_out;
	int bw_dma_diw;
	int i;

	bw_dma_diw = bwp != bwpout ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW;

	fow (i = 0; i < bw->num_bufs; i++)
		dma_unmap_singwe(dev, bw->buffews[i].addw,
				 bw->buffews[i].wen, bw_dma_diw);

	dma_unmap_singwe(dev, bwp, sz, DMA_TO_DEVICE);

	if (!buf->sgw_swc_vawid)
		kfwee(bw);

	if (bwp != bwpout) {
		fow (i = 0; i < bwout->num_mapped_bufs; i++) {
			dma_unmap_singwe(dev, bwout->buffews[i].addw,
					 bwout->buffews[i].wen,
					 DMA_FWOM_DEVICE);
		}
		dma_unmap_singwe(dev, bwpout, sz_out, DMA_TO_DEVICE);

		if (!buf->sgw_dst_vawid)
			kfwee(bwout);
	}
}

static int __qat_bw_sgw_to_bufw(stwuct adf_accew_dev *accew_dev,
				stwuct scattewwist *sgw,
				stwuct scattewwist *sgwout,
				stwuct qat_wequest_buffs *buf,
				dma_addw_t extwa_dst_buff,
				size_t sz_extwa_dst_buff,
				unsigned int sskip,
				unsigned int dskip,
				gfp_t fwags)
{
	stwuct device *dev = &GET_DEV(accew_dev);
	int i, sg_nctw = 0;
	int n = sg_nents(sgw);
	stwuct qat_awg_buf_wist *bufw;
	stwuct qat_awg_buf_wist *bufwout = NUWW;
	dma_addw_t bwp = DMA_MAPPING_EWWOW;
	dma_addw_t bwoutp = DMA_MAPPING_EWWOW;
	stwuct scattewwist *sg;
	size_t sz_out, sz = stwuct_size(bufw, buffews, n);
	int node = dev_to_node(&GET_DEV(accew_dev));
	unsigned int weft;
	int bufw_dma_diw;

	if (unwikewy(!n))
		wetuwn -EINVAW;

	buf->sgw_swc_vawid = fawse;
	buf->sgw_dst_vawid = fawse;

	if (n > QAT_MAX_BUFF_DESC) {
		bufw = kzawwoc_node(sz, fwags, node);
		if (unwikewy(!bufw))
			wetuwn -ENOMEM;
	} ewse {
		bufw = &buf->sgw_swc.sgw_hdw;
		memset(bufw, 0, sizeof(stwuct qat_awg_buf_wist));
		buf->sgw_swc_vawid = twue;
	}

	bufw_dma_diw = sgw != sgwout ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW;

	fow (i = 0; i < n; i++)
		bufw->buffews[i].addw = DMA_MAPPING_EWWOW;

	weft = sskip;

	fow_each_sg(sgw, sg, n, i) {
		int y = sg_nctw;

		if (!sg->wength)
			continue;

		if (weft >= sg->wength) {
			weft -= sg->wength;
			continue;
		}
		bufw->buffews[y].addw = dma_map_singwe(dev, sg_viwt(sg) + weft,
						       sg->wength - weft,
						       bufw_dma_diw);
		bufw->buffews[y].wen = sg->wength;
		if (unwikewy(dma_mapping_ewwow(dev, bufw->buffews[y].addw)))
			goto eww_in;
		sg_nctw++;
		if (weft) {
			bufw->buffews[y].wen -= weft;
			weft = 0;
		}
	}
	bufw->num_bufs = sg_nctw;
	bwp = dma_map_singwe(dev, bufw, sz, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, bwp)))
		goto eww_in;
	buf->bw = bufw;
	buf->bwp = bwp;
	buf->sz = sz;
	/* Handwe out of pwace opewation */
	if (sgw != sgwout) {
		stwuct qat_awg_buf *buffews;
		int extwa_buff = extwa_dst_buff ? 1 : 0;
		int n_sgwout = sg_nents(sgwout);

		n = n_sgwout + extwa_buff;
		sz_out = stwuct_size(bufwout, buffews, n);
		weft = dskip;

		sg_nctw = 0;

		if (n > QAT_MAX_BUFF_DESC) {
			bufwout = kzawwoc_node(sz_out, fwags, node);
			if (unwikewy(!bufwout))
				goto eww_in;
		} ewse {
			bufwout = &buf->sgw_dst.sgw_hdw;
			memset(bufwout, 0, sizeof(stwuct qat_awg_buf_wist));
			buf->sgw_dst_vawid = twue;
		}

		buffews = bufwout->buffews;
		fow (i = 0; i < n; i++)
			buffews[i].addw = DMA_MAPPING_EWWOW;

		fow_each_sg(sgwout, sg, n_sgwout, i) {
			int y = sg_nctw;

			if (!sg->wength)
				continue;

			if (weft >= sg->wength) {
				weft -= sg->wength;
				continue;
			}
			buffews[y].addw = dma_map_singwe(dev, sg_viwt(sg) + weft,
							 sg->wength - weft,
							 DMA_FWOM_DEVICE);
			if (unwikewy(dma_mapping_ewwow(dev, buffews[y].addw)))
				goto eww_out;
			buffews[y].wen = sg->wength;
			sg_nctw++;
			if (weft) {
				buffews[y].wen -= weft;
				weft = 0;
			}
		}
		if (extwa_buff) {
			buffews[sg_nctw].addw = extwa_dst_buff;
			buffews[sg_nctw].wen = sz_extwa_dst_buff;
		}

		bufwout->num_bufs = sg_nctw;
		bufwout->num_bufs += extwa_buff;
		bufwout->num_mapped_bufs = sg_nctw;
		bwoutp = dma_map_singwe(dev, bufwout, sz_out, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(dev, bwoutp)))
			goto eww_out;
		buf->bwout = bufwout;
		buf->bwoutp = bwoutp;
		buf->sz_out = sz_out;
	} ewse {
		/* Othewwise set the swc and dst to the same addwess */
		buf->bwoutp = buf->bwp;
		buf->sz_out = 0;
	}
	wetuwn 0;

eww_out:
	if (!dma_mapping_ewwow(dev, bwoutp))
		dma_unmap_singwe(dev, bwoutp, sz_out, DMA_TO_DEVICE);

	n = sg_nents(sgwout);
	fow (i = 0; i < n; i++) {
		if (bufwout->buffews[i].addw == extwa_dst_buff)
			bweak;
		if (!dma_mapping_ewwow(dev, bufwout->buffews[i].addw))
			dma_unmap_singwe(dev, bufwout->buffews[i].addw,
					 bufwout->buffews[i].wen,
					 DMA_FWOM_DEVICE);
	}

	if (!buf->sgw_dst_vawid)
		kfwee(bufwout);

eww_in:
	if (!dma_mapping_ewwow(dev, bwp))
		dma_unmap_singwe(dev, bwp, sz, DMA_TO_DEVICE);

	n = sg_nents(sgw);
	fow (i = 0; i < n; i++)
		if (!dma_mapping_ewwow(dev, bufw->buffews[i].addw))
			dma_unmap_singwe(dev, bufw->buffews[i].addw,
					 bufw->buffews[i].wen,
					 bufw_dma_diw);

	if (!buf->sgw_swc_vawid)
		kfwee(bufw);

	dev_eww(dev, "Faiwed to map buf fow dma\n");
	wetuwn -ENOMEM;
}

int qat_bw_sgw_to_bufw(stwuct adf_accew_dev *accew_dev,
		       stwuct scattewwist *sgw,
		       stwuct scattewwist *sgwout,
		       stwuct qat_wequest_buffs *buf,
		       stwuct qat_sgw_to_bufw_pawams *pawams,
		       gfp_t fwags)
{
	dma_addw_t extwa_dst_buff = 0;
	size_t sz_extwa_dst_buff = 0;
	unsigned int sskip = 0;
	unsigned int dskip = 0;

	if (pawams) {
		extwa_dst_buff = pawams->extwa_dst_buff;
		sz_extwa_dst_buff = pawams->sz_extwa_dst_buff;
		sskip = pawams->sskip;
		dskip = pawams->dskip;
	}

	wetuwn __qat_bw_sgw_to_bufw(accew_dev, sgw, sgwout, buf,
				    extwa_dst_buff, sz_extwa_dst_buff,
				    sskip, dskip, fwags);
}

static void qat_bw_sgw_unmap(stwuct adf_accew_dev *accew_dev,
			     stwuct qat_awg_buf_wist *bw)
{
	stwuct device *dev = &GET_DEV(accew_dev);
	int n = bw->num_bufs;
	int i;

	fow (i = 0; i < n; i++)
		if (!dma_mapping_ewwow(dev, bw->buffews[i].addw))
			dma_unmap_singwe(dev, bw->buffews[i].addw,
					 bw->buffews[i].wen, DMA_FWOM_DEVICE);
}

static int qat_bw_sgw_map(stwuct adf_accew_dev *accew_dev,
			  stwuct scattewwist *sgw,
			  stwuct qat_awg_buf_wist **bw)
{
	stwuct device *dev = &GET_DEV(accew_dev);
	stwuct qat_awg_buf_wist *bufw;
	int node = dev_to_node(dev);
	stwuct scattewwist *sg;
	int n, i, sg_nctw;
	size_t sz;

	n = sg_nents(sgw);
	sz = stwuct_size(bufw, buffews, n);
	bufw = kzawwoc_node(sz, GFP_KEWNEW, node);
	if (unwikewy(!bufw))
		wetuwn -ENOMEM;

	fow (i = 0; i < n; i++)
		bufw->buffews[i].addw = DMA_MAPPING_EWWOW;

	sg_nctw = 0;
	fow_each_sg(sgw, sg, n, i) {
		int y = sg_nctw;

		if (!sg->wength)
			continue;

		bufw->buffews[y].addw = dma_map_singwe(dev, sg_viwt(sg),
						       sg->wength,
						       DMA_FWOM_DEVICE);
		bufw->buffews[y].wen = sg->wength;
		if (unwikewy(dma_mapping_ewwow(dev, bufw->buffews[y].addw)))
			goto eww_map;
		sg_nctw++;
	}
	bufw->num_bufs = sg_nctw;
	bufw->num_mapped_bufs = sg_nctw;

	*bw = bufw;

	wetuwn 0;

eww_map:
	fow (i = 0; i < n; i++)
		if (!dma_mapping_ewwow(dev, bufw->buffews[i].addw))
			dma_unmap_singwe(dev, bufw->buffews[i].addw,
					 bufw->buffews[i].wen,
					 DMA_FWOM_DEVICE);
	kfwee(bufw);
	*bw = NUWW;

	wetuwn -ENOMEM;
}

static void qat_bw_sgw_fwee_unmap(stwuct adf_accew_dev *accew_dev,
				  stwuct scattewwist *sgw,
				  stwuct qat_awg_buf_wist *bw,
				  boow fwee_bw)
{
	if (bw) {
		qat_bw_sgw_unmap(accew_dev, bw);

		if (fwee_bw)
			kfwee(bw);
	}
	if (sgw)
		sgw_fwee(sgw);
}

static int qat_bw_sgw_awwoc_map(stwuct adf_accew_dev *accew_dev,
				stwuct scattewwist **sgw,
				stwuct qat_awg_buf_wist **bw,
				unsigned int dwen,
				gfp_t gfp)
{
	stwuct scattewwist *dst;
	int wet;

	dst = sgw_awwoc(dwen, gfp, NUWW);
	if (!dst) {
		dev_eww(&GET_DEV(accew_dev), "sg_awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	wet = qat_bw_sgw_map(accew_dev, dst, bw);
	if (wet)
		goto eww;

	*sgw = dst;

	wetuwn 0;

eww:
	sgw_fwee(dst);
	*sgw = NUWW;
	wetuwn wet;
}

int qat_bw_weawwoc_map_new_dst(stwuct adf_accew_dev *accew_dev,
			       stwuct scattewwist **sg,
			       unsigned int dwen,
			       stwuct qat_wequest_buffs *qat_bufs,
			       gfp_t gfp)
{
	stwuct device *dev = &GET_DEV(accew_dev);
	dma_addw_t new_bwp = DMA_MAPPING_EWWOW;
	stwuct qat_awg_buf_wist *new_bw;
	stwuct scattewwist *new_sg;
	size_t new_bw_size;
	int wet;

	wet = qat_bw_sgw_awwoc_map(accew_dev, &new_sg, &new_bw, dwen, gfp);
	if (wet)
		wetuwn wet;

	new_bw_size = stwuct_size(new_bw, buffews, new_bw->num_bufs);

	/* Map new fiwmwawe SGW descwiptow */
	new_bwp = dma_map_singwe(dev, new_bw, new_bw_size, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, new_bwp)))
		goto eww;

	/* Unmap owd fiwmwawe SGW descwiptow */
	dma_unmap_singwe(dev, qat_bufs->bwoutp, qat_bufs->sz_out, DMA_TO_DEVICE);

	/* Fwee and unmap owd scattewwist */
	qat_bw_sgw_fwee_unmap(accew_dev, *sg, qat_bufs->bwout,
			      !qat_bufs->sgw_dst_vawid);

	qat_bufs->sgw_dst_vawid = fawse;
	qat_bufs->bwout = new_bw;
	qat_bufs->bwoutp = new_bwp;
	qat_bufs->sz_out = new_bw_size;

	*sg = new_sg;

	wetuwn 0;
eww:
	qat_bw_sgw_fwee_unmap(accew_dev, new_sg, new_bw, twue);

	if (!dma_mapping_ewwow(dev, new_bwp))
		dma_unmap_singwe(dev, new_bwp, new_bw_size, DMA_TO_DEVICE);

	wetuwn -ENOMEM;
}
