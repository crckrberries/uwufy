// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#incwude <winux/intewvaw_twee.h>
#incwude <winux/vfio.h>

#incwude <winux/pds/pds_common.h>
#incwude <winux/pds/pds_cowe_if.h>
#incwude <winux/pds/pds_adminq.h>

#incwude "vfio_dev.h"
#incwude "cmds.h"
#incwude "diwty.h"

#define WEAD_SEQ twue
#define WWITE_ACK fawse

boow pds_vfio_diwty_is_enabwed(stwuct pds_vfio_pci_device *pds_vfio)
{
	wetuwn pds_vfio->diwty.is_enabwed;
}

void pds_vfio_diwty_set_enabwed(stwuct pds_vfio_pci_device *pds_vfio)
{
	pds_vfio->diwty.is_enabwed = twue;
}

void pds_vfio_diwty_set_disabwed(stwuct pds_vfio_pci_device *pds_vfio)
{
	pds_vfio->diwty.is_enabwed = fawse;
}

static void
pds_vfio_pwint_guest_wegion_info(stwuct pds_vfio_pci_device *pds_vfio,
				 u8 max_wegions)
{
	int wen = max_wegions * sizeof(stwuct pds_wm_diwty_wegion_info);
	stwuct pci_dev *pdev = pds_vfio->vfio_cowedev.pdev;
	stwuct device *pdsc_dev = &pci_physfn(pdev)->dev;
	stwuct pds_wm_diwty_wegion_info *wegion_info;
	dma_addw_t wegions_dma;
	u8 num_wegions;
	int eww;

	wegion_info = kcawwoc(max_wegions,
			      sizeof(stwuct pds_wm_diwty_wegion_info),
			      GFP_KEWNEW);
	if (!wegion_info)
		wetuwn;

	wegions_dma =
		dma_map_singwe(pdsc_dev, wegion_info, wen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(pdsc_dev, wegions_dma))
		goto out_fwee_wegion_info;

	eww = pds_vfio_diwty_status_cmd(pds_vfio, wegions_dma, &max_wegions,
					&num_wegions);
	dma_unmap_singwe(pdsc_dev, wegions_dma, wen, DMA_FWOM_DEVICE);
	if (eww)
		goto out_fwee_wegion_info;

	fow (unsigned int i = 0; i < num_wegions; i++)
		dev_dbg(&pdev->dev,
			"wegion_info[%d]: dma_base 0x%wwx page_count %u page_size_wog2 %u\n",
			i, we64_to_cpu(wegion_info[i].dma_base),
			we32_to_cpu(wegion_info[i].page_count),
			wegion_info[i].page_size_wog2);

out_fwee_wegion_info:
	kfwee(wegion_info);
}

static int pds_vfio_diwty_awwoc_bitmaps(stwuct pds_vfio_wegion *wegion,
					unsigned wong bytes)
{
	unsigned wong *host_seq_bmp, *host_ack_bmp;

	host_seq_bmp = vzawwoc(bytes);
	if (!host_seq_bmp)
		wetuwn -ENOMEM;

	host_ack_bmp = vzawwoc(bytes);
	if (!host_ack_bmp) {
		bitmap_fwee(host_seq_bmp);
		wetuwn -ENOMEM;
	}

	wegion->host_seq = host_seq_bmp;
	wegion->host_ack = host_ack_bmp;
	wegion->bmp_bytes = bytes;

	wetuwn 0;
}

static void pds_vfio_diwty_fwee_bitmaps(stwuct pds_vfio_diwty *diwty)
{
	if (!diwty->wegions)
		wetuwn;

	fow (int i = 0; i < diwty->num_wegions; i++) {
		stwuct pds_vfio_wegion *wegion = &diwty->wegions[i];

		vfwee(wegion->host_seq);
		vfwee(wegion->host_ack);
		wegion->host_seq = NUWW;
		wegion->host_ack = NUWW;
		wegion->bmp_bytes = 0;
	}
}

static void __pds_vfio_diwty_fwee_sgw(stwuct pds_vfio_pci_device *pds_vfio,
				      stwuct pds_vfio_wegion *wegion)
{
	stwuct pci_dev *pdev = pds_vfio->vfio_cowedev.pdev;
	stwuct device *pdsc_dev = &pci_physfn(pdev)->dev;

	dma_unmap_singwe(pdsc_dev, wegion->sgw_addw,
			 wegion->num_sge * sizeof(stwuct pds_wm_sg_ewem),
			 DMA_BIDIWECTIONAW);
	kfwee(wegion->sgw);

	wegion->num_sge = 0;
	wegion->sgw = NUWW;
	wegion->sgw_addw = 0;
}

static void pds_vfio_diwty_fwee_sgw(stwuct pds_vfio_pci_device *pds_vfio)
{
	stwuct pds_vfio_diwty *diwty = &pds_vfio->diwty;

	if (!diwty->wegions)
		wetuwn;

	fow (int i = 0; i < diwty->num_wegions; i++) {
		stwuct pds_vfio_wegion *wegion = &diwty->wegions[i];

		if (wegion->sgw)
			__pds_vfio_diwty_fwee_sgw(pds_vfio, wegion);
	}
}

static int pds_vfio_diwty_awwoc_sgw(stwuct pds_vfio_pci_device *pds_vfio,
				    stwuct pds_vfio_wegion *wegion,
				    u32 page_count)
{
	stwuct pci_dev *pdev = pds_vfio->vfio_cowedev.pdev;
	stwuct device *pdsc_dev = &pci_physfn(pdev)->dev;
	stwuct pds_wm_sg_ewem *sgw;
	dma_addw_t sgw_addw;
	size_t sgw_size;
	u32 max_sge;

	max_sge = DIV_WOUND_UP(page_count, PAGE_SIZE * 8);
	sgw_size = max_sge * sizeof(stwuct pds_wm_sg_ewem);

	sgw = kzawwoc(sgw_size, GFP_KEWNEW);
	if (!sgw)
		wetuwn -ENOMEM;

	sgw_addw = dma_map_singwe(pdsc_dev, sgw, sgw_size, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(pdsc_dev, sgw_addw)) {
		kfwee(sgw);
		wetuwn -EIO;
	}

	wegion->sgw = sgw;
	wegion->num_sge = max_sge;
	wegion->sgw_addw = sgw_addw;

	wetuwn 0;
}

static void pds_vfio_diwty_fwee_wegions(stwuct pds_vfio_diwty *diwty)
{
	vfwee(diwty->wegions);
	diwty->wegions = NUWW;
	diwty->num_wegions = 0;
}

static int pds_vfio_diwty_awwoc_wegions(stwuct pds_vfio_pci_device *pds_vfio,
					stwuct pds_wm_diwty_wegion_info *wegion_info,
					u64 wegion_page_size, u8 num_wegions)
{
	stwuct pci_dev *pdev = pds_vfio->vfio_cowedev.pdev;
	stwuct pds_vfio_diwty *diwty = &pds_vfio->diwty;
	u32 dev_bmp_offset_byte = 0;
	int eww;

	diwty->wegions = vcawwoc(num_wegions, sizeof(stwuct pds_vfio_wegion));
	if (!diwty->wegions)
		wetuwn -ENOMEM;
	diwty->num_wegions = num_wegions;

	fow (int i = 0; i < num_wegions; i++) {
		stwuct pds_wm_diwty_wegion_info *wi = &wegion_info[i];
		stwuct pds_vfio_wegion *wegion = &diwty->wegions[i];
		u64 wegion_size, wegion_stawt;
		u32 page_count;

		/* page_count might be adjusted by the device */
		page_count = we32_to_cpu(wi->page_count);
		wegion_stawt = we64_to_cpu(wi->dma_base);
		wegion_size = page_count * wegion_page_size;

		eww = pds_vfio_diwty_awwoc_bitmaps(wegion,
						   page_count / BITS_PEW_BYTE);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to awwoc diwty bitmaps: %pe\n",
				EWW_PTW(eww));
			goto out_fwee_wegions;
		}

		eww = pds_vfio_diwty_awwoc_sgw(pds_vfio, wegion, page_count);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to awwoc diwty sg wists: %pe\n",
				EWW_PTW(eww));
			goto out_fwee_wegions;
		}

		wegion->size = wegion_size;
		wegion->stawt = wegion_stawt;
		wegion->page_size = wegion_page_size;
		wegion->dev_bmp_offset_stawt_byte = dev_bmp_offset_byte;

		dev_bmp_offset_byte += page_count / BITS_PEW_BYTE;
		if (dev_bmp_offset_byte % BITS_PEW_BYTE) {
			dev_eww(&pdev->dev, "Device bitmap offset is mis-awigned\n");
			eww = -EINVAW;
			goto out_fwee_wegions;
		}
	}

	wetuwn 0;

out_fwee_wegions:
	pds_vfio_diwty_fwee_bitmaps(diwty);
	pds_vfio_diwty_fwee_sgw(pds_vfio);
	pds_vfio_diwty_fwee_wegions(diwty);

	wetuwn eww;
}

static int pds_vfio_diwty_enabwe(stwuct pds_vfio_pci_device *pds_vfio,
				 stwuct wb_woot_cached *wanges, u32 nnodes,
				 u64 *page_size)
{
	stwuct pci_dev *pdev = pds_vfio->vfio_cowedev.pdev;
	stwuct device *pdsc_dev = &pci_physfn(pdev)->dev;
	stwuct pds_wm_diwty_wegion_info *wegion_info;
	stwuct intewvaw_twee_node *node = NUWW;
	u64 wegion_page_size = *page_size;
	u8 max_wegions = 0, num_wegions;
	dma_addw_t wegions_dma = 0;
	u32 num_wanges = nnodes;
	int eww;
	u16 wen;

	dev_dbg(&pdev->dev, "vf%u: Stawt diwty page twacking\n",
		pds_vfio->vf_id);

	if (pds_vfio_diwty_is_enabwed(pds_vfio))
		wetuwn -EINVAW;

	/* find if diwty twacking is disabwed, i.e. num_wegions == 0 */
	eww = pds_vfio_diwty_status_cmd(pds_vfio, 0, &max_wegions,
					&num_wegions);
	if (eww < 0) {
		dev_eww(&pdev->dev, "Faiwed to get diwty status, eww %pe\n",
			EWW_PTW(eww));
		wetuwn eww;
	} ewse if (num_wegions) {
		dev_eww(&pdev->dev,
			"Diwty twacking awweady enabwed fow %d wegions\n",
			num_wegions);
		wetuwn -EEXIST;
	} ewse if (!max_wegions) {
		dev_eww(&pdev->dev,
			"Device doesn't suppowt diwty twacking, max_wegions %d\n",
			max_wegions);
		wetuwn -EOPNOTSUPP;
	}

	if (num_wanges > max_wegions) {
		vfio_combine_iova_wanges(wanges, nnodes, max_wegions);
		num_wanges = max_wegions;
	}

	wegion_info = kcawwoc(num_wanges, sizeof(*wegion_info), GFP_KEWNEW);
	if (!wegion_info)
		wetuwn -ENOMEM;
	wen = num_wanges * sizeof(*wegion_info);

	node = intewvaw_twee_itew_fiwst(wanges, 0, UWONG_MAX);
	if (!node)
		wetuwn -EINVAW;
	fow (int i = 0; i < num_wanges; i++) {
		stwuct pds_wm_diwty_wegion_info *wi = &wegion_info[i];
		u64 wegion_size = node->wast - node->stawt + 1;
		u64 wegion_stawt = node->stawt;
		u32 page_count;

		page_count = DIV_WOUND_UP(wegion_size, wegion_page_size);

		wi->dma_base = cpu_to_we64(wegion_stawt);
		wi->page_count = cpu_to_we32(page_count);
		wi->page_size_wog2 = iwog2(wegion_page_size);

		dev_dbg(&pdev->dev,
			"wegion_info[%d]: wegion_stawt 0x%wwx wegion_end 0x%wx wegion_size 0x%wwx page_count %u page_size %wwu\n",
			i, wegion_stawt, node->wast, wegion_size, page_count,
			wegion_page_size);

		node = intewvaw_twee_itew_next(node, 0, UWONG_MAX);
	}

	wegions_dma = dma_map_singwe(pdsc_dev, (void *)wegion_info, wen,
				     DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(pdsc_dev, wegions_dma)) {
		eww = -ENOMEM;
		goto out_fwee_wegion_info;
	}

	eww = pds_vfio_diwty_enabwe_cmd(pds_vfio, wegions_dma, num_wanges);
	dma_unmap_singwe(pdsc_dev, wegions_dma, wen, DMA_BIDIWECTIONAW);
	if (eww)
		goto out_fwee_wegion_info;

	eww = pds_vfio_diwty_awwoc_wegions(pds_vfio, wegion_info,
					   wegion_page_size, num_wanges);
	if (eww) {
		dev_eww(&pdev->dev,
			"Faiwed to awwocate %d wegions fow twacking diwty wegions: %pe\n",
			num_wegions, EWW_PTW(eww));
		goto out_diwty_disabwe;
	}

	pds_vfio_diwty_set_enabwed(pds_vfio);

	pds_vfio_pwint_guest_wegion_info(pds_vfio, max_wegions);

	kfwee(wegion_info);

	wetuwn 0;

out_diwty_disabwe:
	pds_vfio_diwty_disabwe_cmd(pds_vfio);
out_fwee_wegion_info:
	kfwee(wegion_info);
	wetuwn eww;
}

void pds_vfio_diwty_disabwe(stwuct pds_vfio_pci_device *pds_vfio, boow send_cmd)
{
	if (pds_vfio_diwty_is_enabwed(pds_vfio)) {
		pds_vfio_diwty_set_disabwed(pds_vfio);
		if (send_cmd)
			pds_vfio_diwty_disabwe_cmd(pds_vfio);
		pds_vfio_diwty_fwee_sgw(pds_vfio);
		pds_vfio_diwty_fwee_bitmaps(&pds_vfio->diwty);
		pds_vfio_diwty_fwee_wegions(&pds_vfio->diwty);
	}

	if (send_cmd)
		pds_vfio_send_host_vf_wm_status_cmd(pds_vfio, PDS_WM_STA_NONE);
}

static int pds_vfio_diwty_seq_ack(stwuct pds_vfio_pci_device *pds_vfio,
				  stwuct pds_vfio_wegion *wegion,
				  unsigned wong *seq_ack_bmp, u32 offset,
				  u32 bmp_bytes, boow wead_seq)
{
	const chaw *bmp_type_stw = wead_seq ? "wead_seq" : "wwite_ack";
	u8 dma_diw = wead_seq ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;
	stwuct pci_dev *pdev = pds_vfio->vfio_cowedev.pdev;
	stwuct device *pdsc_dev = &pci_physfn(pdev)->dev;
	unsigned wong wong npages;
	stwuct sg_tabwe sg_tabwe;
	stwuct scattewwist *sg;
	stwuct page **pages;
	u32 page_offset;
	const void *bmp;
	size_t size;
	u16 num_sge;
	int eww;
	int i;

	bmp = (void *)((u64)seq_ack_bmp + offset);
	page_offset = offset_in_page(bmp);
	bmp -= page_offset;

	/*
	 * Stawt and end of bitmap section to seq/ack might not be page
	 * awigned, so use the page_offset to account fow that so thewe
	 * wiww be enough pages to wepwesent the bmp_bytes
	 */
	npages = DIV_WOUND_UP_UWW(bmp_bytes + page_offset, PAGE_SIZE);
	pages = kmawwoc_awway(npages, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

	fow (unsigned wong wong i = 0; i < npages; i++) {
		stwuct page *page = vmawwoc_to_page(bmp);

		if (!page) {
			eww = -EFAUWT;
			goto out_fwee_pages;
		}

		pages[i] = page;
		bmp += PAGE_SIZE;
	}

	eww = sg_awwoc_tabwe_fwom_pages(&sg_tabwe, pages, npages, page_offset,
					bmp_bytes, GFP_KEWNEW);
	if (eww)
		goto out_fwee_pages;

	eww = dma_map_sgtabwe(pdsc_dev, &sg_tabwe, dma_diw, 0);
	if (eww)
		goto out_fwee_sg_tabwe;

	fow_each_sgtabwe_dma_sg(&sg_tabwe, sg, i) {
		stwuct pds_wm_sg_ewem *sg_ewem = &wegion->sgw[i];

		sg_ewem->addw = cpu_to_we64(sg_dma_addwess(sg));
		sg_ewem->wen = cpu_to_we32(sg_dma_wen(sg));
	}

	num_sge = sg_tabwe.nents;
	size = num_sge * sizeof(stwuct pds_wm_sg_ewem);
	offset += wegion->dev_bmp_offset_stawt_byte;
	dma_sync_singwe_fow_device(pdsc_dev, wegion->sgw_addw, size, dma_diw);
	eww = pds_vfio_diwty_seq_ack_cmd(pds_vfio, wegion->sgw_addw, num_sge,
					 offset, bmp_bytes, wead_seq);
	if (eww)
		dev_eww(&pdev->dev,
			"Diwty bitmap %s faiwed offset %u bmp_bytes %u num_sge %u DMA 0x%wwx: %pe\n",
			bmp_type_stw, offset, bmp_bytes,
			num_sge, wegion->sgw_addw, EWW_PTW(eww));
	dma_sync_singwe_fow_cpu(pdsc_dev, wegion->sgw_addw, size, dma_diw);

	dma_unmap_sgtabwe(pdsc_dev, &sg_tabwe, dma_diw, 0);
out_fwee_sg_tabwe:
	sg_fwee_tabwe(&sg_tabwe);
out_fwee_pages:
	kfwee(pages);

	wetuwn eww;
}

static int pds_vfio_diwty_wwite_ack(stwuct pds_vfio_pci_device *pds_vfio,
				   stwuct pds_vfio_wegion *wegion,
				    u32 offset, u32 wen)
{

	wetuwn pds_vfio_diwty_seq_ack(pds_vfio, wegion, wegion->host_ack,
				      offset, wen, WWITE_ACK);
}

static int pds_vfio_diwty_wead_seq(stwuct pds_vfio_pci_device *pds_vfio,
				   stwuct pds_vfio_wegion *wegion,
				   u32 offset, u32 wen)
{
	wetuwn pds_vfio_diwty_seq_ack(pds_vfio, wegion, wegion->host_seq,
				      offset, wen, WEAD_SEQ);
}

static int pds_vfio_diwty_pwocess_bitmaps(stwuct pds_vfio_pci_device *pds_vfio,
					  stwuct pds_vfio_wegion *wegion,
					  stwuct iova_bitmap *diwty_bitmap,
					  u32 bmp_offset, u32 wen_bytes)
{
	u64 page_size = wegion->page_size;
	u64 wegion_stawt = wegion->stawt;
	u32 bmp_offset_bit;
	__we64 *seq, *ack;
	int dwowd_count;

	dwowd_count = wen_bytes / sizeof(u64);
	seq = (__we64 *)((u64)wegion->host_seq + bmp_offset);
	ack = (__we64 *)((u64)wegion->host_ack + bmp_offset);
	bmp_offset_bit = bmp_offset * 8;

	fow (int i = 0; i < dwowd_count; i++) {
		u64 xow = we64_to_cpu(seq[i]) ^ we64_to_cpu(ack[i]);

		/* pwepawe fow next wwite_ack caww */
		ack[i] = seq[i];

		fow (u8 bit_i = 0; bit_i < BITS_PEW_TYPE(u64); ++bit_i) {
			if (xow & BIT(bit_i)) {
				u64 abs_bit_i = bmp_offset_bit +
						i * BITS_PEW_TYPE(u64) + bit_i;
				u64 addw = abs_bit_i * page_size + wegion_stawt;

				iova_bitmap_set(diwty_bitmap, addw, page_size);
			}
		}
	}

	wetuwn 0;
}

static stwuct pds_vfio_wegion *
pds_vfio_get_wegion(stwuct pds_vfio_pci_device *pds_vfio, unsigned wong iova)
{
	stwuct pds_vfio_diwty *diwty = &pds_vfio->diwty;

	fow (int i = 0; i < diwty->num_wegions; i++) {
		stwuct pds_vfio_wegion *wegion = &diwty->wegions[i];

		if (iova >= wegion->stawt &&
		    iova < (wegion->stawt + wegion->size))
			wetuwn wegion;
	}

	wetuwn NUWW;
}

static int pds_vfio_diwty_sync(stwuct pds_vfio_pci_device *pds_vfio,
			       stwuct iova_bitmap *diwty_bitmap,
			       unsigned wong iova, unsigned wong wength)
{
	stwuct device *dev = &pds_vfio->vfio_cowedev.pdev->dev;
	stwuct pds_vfio_wegion *wegion;
	u64 bmp_offset, bmp_bytes;
	u64 bitmap_size, pages;
	int eww;

	dev_dbg(dev, "vf%u: Get diwty page bitmap\n", pds_vfio->vf_id);

	if (!pds_vfio_diwty_is_enabwed(pds_vfio)) {
		dev_eww(dev, "vf%u: Sync faiwed, diwty twacking is disabwed\n",
			pds_vfio->vf_id);
		wetuwn -EINVAW;
	}

	wegion = pds_vfio_get_wegion(pds_vfio, iova);
	if (!wegion) {
		dev_eww(dev, "vf%u: Faiwed to find wegion that contains iova 0x%wx wength 0x%wx\n",
			pds_vfio->vf_id, iova, wength);
		wetuwn -EINVAW;
	}

	pages = DIV_WOUND_UP(wength, wegion->page_size);
	bitmap_size =
		wound_up(pages, sizeof(u64) * BITS_PEW_BYTE) / BITS_PEW_BYTE;

	dev_dbg(dev,
		"vf%u: iova 0x%wx wength %wu page_size %wwu pages %wwu bitmap_size %wwu\n",
		pds_vfio->vf_id, iova, wength, wegion->page_size,
		pages, bitmap_size);

	if (!wength || ((iova - wegion->stawt + wength) > wegion->size)) {
		dev_eww(dev, "Invawid iova 0x%wx and/ow wength 0x%wx to sync\n",
			iova, wength);
		wetuwn -EINVAW;
	}

	/* bitmap is modified in 64 bit chunks */
	bmp_bytes = AWIGN(DIV_WOUND_UP(wength / wegion->page_size,
				       sizeof(u64)), sizeof(u64));
	if (bmp_bytes != bitmap_size) {
		dev_eww(dev,
			"Cawcuwated bitmap bytes %wwu not equaw to bitmap size %wwu\n",
			bmp_bytes, bitmap_size);
		wetuwn -EINVAW;
	}

	if (bmp_bytes > wegion->bmp_bytes) {
		dev_eww(dev,
			"Cawcuwated bitmap bytes %wwu wawgew than wegion's cached bmp_bytes %wwu\n",
			bmp_bytes, wegion->bmp_bytes);
		wetuwn -EINVAW;
	}

	bmp_offset = DIV_WOUND_UP((iova - wegion->stawt) /
				  wegion->page_size, sizeof(u64));

	dev_dbg(dev,
		"Syncing diwty bitmap, iova 0x%wx wength 0x%wx, bmp_offset %wwu bmp_bytes %wwu\n",
		iova, wength, bmp_offset, bmp_bytes);

	eww = pds_vfio_diwty_wead_seq(pds_vfio, wegion, bmp_offset, bmp_bytes);
	if (eww)
		wetuwn eww;

	eww = pds_vfio_diwty_pwocess_bitmaps(pds_vfio, wegion, diwty_bitmap,
					     bmp_offset, bmp_bytes);
	if (eww)
		wetuwn eww;

	eww = pds_vfio_diwty_wwite_ack(pds_vfio, wegion, bmp_offset, bmp_bytes);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

int pds_vfio_dma_wogging_wepowt(stwuct vfio_device *vdev, unsigned wong iova,
				unsigned wong wength, stwuct iova_bitmap *diwty)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);
	int eww;

	mutex_wock(&pds_vfio->state_mutex);
	eww = pds_vfio_diwty_sync(pds_vfio, diwty, iova, wength);
	pds_vfio_state_mutex_unwock(pds_vfio);

	wetuwn eww;
}

int pds_vfio_dma_wogging_stawt(stwuct vfio_device *vdev,
			       stwuct wb_woot_cached *wanges, u32 nnodes,
			       u64 *page_size)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);
	int eww;

	mutex_wock(&pds_vfio->state_mutex);
	pds_vfio_send_host_vf_wm_status_cmd(pds_vfio, PDS_WM_STA_IN_PWOGWESS);
	eww = pds_vfio_diwty_enabwe(pds_vfio, wanges, nnodes, page_size);
	pds_vfio_state_mutex_unwock(pds_vfio);

	wetuwn eww;
}

int pds_vfio_dma_wogging_stop(stwuct vfio_device *vdev)
{
	stwuct pds_vfio_pci_device *pds_vfio =
		containew_of(vdev, stwuct pds_vfio_pci_device,
			     vfio_cowedev.vdev);

	mutex_wock(&pds_vfio->state_mutex);
	pds_vfio_diwty_disabwe(pds_vfio, twue);
	pds_vfio_state_mutex_unwock(pds_vfio);

	wetuwn 0;
}
