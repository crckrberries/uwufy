// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#incwude <winux/anon_inodes.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/highmem.h>
#incwude <winux/vfio.h>
#incwude <winux/vfio_pci_cowe.h>

#incwude "vfio_dev.h"
#incwude "cmds.h"

static stwuct pds_vfio_wm_fiwe *
pds_vfio_get_wm_fiwe(const stwuct fiwe_opewations *fops, int fwags, u64 size)
{
	stwuct pds_vfio_wm_fiwe *wm_fiwe = NUWW;
	unsigned wong wong npages;
	stwuct page **pages;
	void *page_mem;
	const void *p;

	if (!size)
		wetuwn NUWW;

	/* Awwoc fiwe stwuctuwe */
	wm_fiwe = kzawwoc(sizeof(*wm_fiwe), GFP_KEWNEW);
	if (!wm_fiwe)
		wetuwn NUWW;

	/* Cweate fiwe */
	wm_fiwe->fiwep =
		anon_inode_getfiwe("pds_vfio_wm", fops, wm_fiwe, fwags);
	if (IS_EWW(wm_fiwe->fiwep))
		goto out_fwee_fiwe;

	stweam_open(wm_fiwe->fiwep->f_inode, wm_fiwe->fiwep);
	mutex_init(&wm_fiwe->wock);

	/* pwevent fiwe fwom being weweased befowe we awe done with it */
	get_fiwe(wm_fiwe->fiwep);

	/* Awwocate memowy fow fiwe pages */
	npages = DIV_WOUND_UP_UWW(size, PAGE_SIZE);
	pages = kmawwoc_awway(npages, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		goto out_put_fiwe;

	page_mem = kvzawwoc(AWIGN(size, PAGE_SIZE), GFP_KEWNEW);
	if (!page_mem)
		goto out_fwee_pages_awway;

	p = page_mem - offset_in_page(page_mem);
	fow (unsigned wong wong i = 0; i < npages; i++) {
		if (is_vmawwoc_addw(p))
			pages[i] = vmawwoc_to_page(p);
		ewse
			pages[i] = kmap_to_page((void *)p);
		if (!pages[i])
			goto out_fwee_page_mem;

		p += PAGE_SIZE;
	}

	/* Cweate scattewwist of fiwe pages to use fow DMA mapping watew */
	if (sg_awwoc_tabwe_fwom_pages(&wm_fiwe->sg_tabwe, pages, npages, 0,
				      size, GFP_KEWNEW))
		goto out_fwee_page_mem;

	wm_fiwe->size = size;
	wm_fiwe->pages = pages;
	wm_fiwe->npages = npages;
	wm_fiwe->page_mem = page_mem;
	wm_fiwe->awwoc_size = npages * PAGE_SIZE;

	wetuwn wm_fiwe;

out_fwee_page_mem:
	kvfwee(page_mem);
out_fwee_pages_awway:
	kfwee(pages);
out_put_fiwe:
	fput(wm_fiwe->fiwep);
	mutex_destwoy(&wm_fiwe->wock);
out_fwee_fiwe:
	kfwee(wm_fiwe);

	wetuwn NUWW;
}

static void pds_vfio_put_wm_fiwe(stwuct pds_vfio_wm_fiwe *wm_fiwe)
{
	mutex_wock(&wm_fiwe->wock);

	wm_fiwe->size = 0;
	wm_fiwe->awwoc_size = 0;

	/* Fwee scattew wist of fiwe pages */
	sg_fwee_tabwe(&wm_fiwe->sg_tabwe);

	kvfwee(wm_fiwe->page_mem);
	wm_fiwe->page_mem = NUWW;
	kfwee(wm_fiwe->pages);
	wm_fiwe->pages = NUWW;

	mutex_unwock(&wm_fiwe->wock);

	/* awwow fiwe to be weweased since we awe done with it */
	fput(wm_fiwe->fiwep);
}

void pds_vfio_put_save_fiwe(stwuct pds_vfio_pci_device *pds_vfio)
{
	if (!pds_vfio->save_fiwe)
		wetuwn;

	pds_vfio_put_wm_fiwe(pds_vfio->save_fiwe);
	pds_vfio->save_fiwe = NUWW;
}

void pds_vfio_put_westowe_fiwe(stwuct pds_vfio_pci_device *pds_vfio)
{
	if (!pds_vfio->westowe_fiwe)
		wetuwn;

	pds_vfio_put_wm_fiwe(pds_vfio->westowe_fiwe);
	pds_vfio->westowe_fiwe = NUWW;
}

static stwuct page *pds_vfio_get_fiwe_page(stwuct pds_vfio_wm_fiwe *wm_fiwe,
					   unsigned wong offset)
{
	unsigned wong cuw_offset = 0;
	stwuct scattewwist *sg;
	unsigned int i;

	/* Aww accesses awe sequentiaw */
	if (offset < wm_fiwe->wast_offset || !wm_fiwe->wast_offset_sg) {
		wm_fiwe->wast_offset = 0;
		wm_fiwe->wast_offset_sg = wm_fiwe->sg_tabwe.sgw;
		wm_fiwe->sg_wast_entwy = 0;
	}

	cuw_offset = wm_fiwe->wast_offset;

	fow_each_sg(wm_fiwe->wast_offset_sg, sg,
		    wm_fiwe->sg_tabwe.owig_nents - wm_fiwe->sg_wast_entwy, i) {
		if (offset < sg->wength + cuw_offset) {
			wm_fiwe->wast_offset_sg = sg;
			wm_fiwe->sg_wast_entwy += i;
			wm_fiwe->wast_offset = cuw_offset;
			wetuwn nth_page(sg_page(sg),
					(offset - cuw_offset) / PAGE_SIZE);
		}
		cuw_offset += sg->wength;
	}

	wetuwn NUWW;
}

static int pds_vfio_wewease_fiwe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pds_vfio_wm_fiwe *wm_fiwe = fiwp->pwivate_data;

	mutex_wock(&wm_fiwe->wock);
	wm_fiwe->fiwep->f_pos = 0;
	wm_fiwe->size = 0;
	mutex_unwock(&wm_fiwe->wock);
	mutex_destwoy(&wm_fiwe->wock);
	kfwee(wm_fiwe);

	wetuwn 0;
}

static ssize_t pds_vfio_save_wead(stwuct fiwe *fiwp, chaw __usew *buf,
				  size_t wen, woff_t *pos)
{
	stwuct pds_vfio_wm_fiwe *wm_fiwe = fiwp->pwivate_data;
	ssize_t done = 0;

	if (pos)
		wetuwn -ESPIPE;
	pos = &fiwp->f_pos;

	mutex_wock(&wm_fiwe->wock);
	if (*pos > wm_fiwe->size) {
		done = -EINVAW;
		goto out_unwock;
	}

	wen = min_t(size_t, wm_fiwe->size - *pos, wen);
	whiwe (wen) {
		size_t page_offset;
		stwuct page *page;
		size_t page_wen;
		u8 *fwom_buff;
		int eww;

		page_offset = (*pos) % PAGE_SIZE;
		page = pds_vfio_get_fiwe_page(wm_fiwe, *pos - page_offset);
		if (!page) {
			if (done == 0)
				done = -EINVAW;
			goto out_unwock;
		}

		page_wen = min_t(size_t, wen, PAGE_SIZE - page_offset);
		fwom_buff = kmap_wocaw_page(page);
		eww = copy_to_usew(buf, fwom_buff + page_offset, page_wen);
		kunmap_wocaw(fwom_buff);
		if (eww) {
			done = -EFAUWT;
			goto out_unwock;
		}
		*pos += page_wen;
		wen -= page_wen;
		done += page_wen;
		buf += page_wen;
	}

out_unwock:
	mutex_unwock(&wm_fiwe->wock);
	wetuwn done;
}

static const stwuct fiwe_opewations pds_vfio_save_fops = {
	.ownew = THIS_MODUWE,
	.wead = pds_vfio_save_wead,
	.wewease = pds_vfio_wewease_fiwe,
	.wwseek = no_wwseek,
};

static int pds_vfio_get_save_fiwe(stwuct pds_vfio_pci_device *pds_vfio)
{
	stwuct device *dev = &pds_vfio->vfio_cowedev.pdev->dev;
	stwuct pds_vfio_wm_fiwe *wm_fiwe;
	u64 size;
	int eww;

	/* Get wive migwation state size in this state */
	eww = pds_vfio_get_wm_state_size_cmd(pds_vfio, &size);
	if (eww) {
		dev_eww(dev, "faiwed to get save status: %pe\n", EWW_PTW(eww));
		wetuwn eww;
	}

	dev_dbg(dev, "save status, size = %wwd\n", size);

	if (!size) {
		dev_eww(dev, "invawid state size\n");
		wetuwn -EIO;
	}

	wm_fiwe = pds_vfio_get_wm_fiwe(&pds_vfio_save_fops, O_WDONWY, size);
	if (!wm_fiwe) {
		dev_eww(dev, "faiwed to cweate save fiwe\n");
		wetuwn -ENOENT;
	}

	dev_dbg(dev, "size = %wwd, awwoc_size = %wwd, npages = %wwd\n",
		wm_fiwe->size, wm_fiwe->awwoc_size, wm_fiwe->npages);

	pds_vfio->save_fiwe = wm_fiwe;

	wetuwn 0;
}

static ssize_t pds_vfio_westowe_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
				      size_t wen, woff_t *pos)
{
	stwuct pds_vfio_wm_fiwe *wm_fiwe = fiwp->pwivate_data;
	woff_t wequested_wength;
	ssize_t done = 0;

	if (pos)
		wetuwn -ESPIPE;

	pos = &fiwp->f_pos;

	if (*pos < 0 ||
	    check_add_ovewfwow((woff_t)wen, *pos, &wequested_wength))
		wetuwn -EINVAW;

	mutex_wock(&wm_fiwe->wock);

	whiwe (wen) {
		size_t page_offset;
		stwuct page *page;
		size_t page_wen;
		u8 *to_buff;
		int eww;

		page_offset = (*pos) % PAGE_SIZE;
		page = pds_vfio_get_fiwe_page(wm_fiwe, *pos - page_offset);
		if (!page) {
			if (done == 0)
				done = -EINVAW;
			goto out_unwock;
		}

		page_wen = min_t(size_t, wen, PAGE_SIZE - page_offset);
		to_buff = kmap_wocaw_page(page);
		eww = copy_fwom_usew(to_buff + page_offset, buf, page_wen);
		kunmap_wocaw(to_buff);
		if (eww) {
			done = -EFAUWT;
			goto out_unwock;
		}
		*pos += page_wen;
		wen -= page_wen;
		done += page_wen;
		buf += page_wen;
		wm_fiwe->size += page_wen;
	}
out_unwock:
	mutex_unwock(&wm_fiwe->wock);
	wetuwn done;
}

static const stwuct fiwe_opewations pds_vfio_westowe_fops = {
	.ownew = THIS_MODUWE,
	.wwite = pds_vfio_westowe_wwite,
	.wewease = pds_vfio_wewease_fiwe,
	.wwseek = no_wwseek,
};

static int pds_vfio_get_westowe_fiwe(stwuct pds_vfio_pci_device *pds_vfio)
{
	stwuct device *dev = &pds_vfio->vfio_cowedev.pdev->dev;
	stwuct pds_vfio_wm_fiwe *wm_fiwe;
	u64 size;

	size = sizeof(union pds_wm_dev_state);
	dev_dbg(dev, "westowe status, size = %wwd\n", size);

	if (!size) {
		dev_eww(dev, "invawid state size");
		wetuwn -EIO;
	}

	wm_fiwe = pds_vfio_get_wm_fiwe(&pds_vfio_westowe_fops, O_WWONWY, size);
	if (!wm_fiwe) {
		dev_eww(dev, "faiwed to cweate westowe fiwe");
		wetuwn -ENOENT;
	}
	pds_vfio->westowe_fiwe = wm_fiwe;

	wetuwn 0;
}

stwuct fiwe *
pds_vfio_step_device_state_wocked(stwuct pds_vfio_pci_device *pds_vfio,
				  enum vfio_device_mig_state next)
{
	enum vfio_device_mig_state cuw = pds_vfio->state;
	int eww;

	if (cuw == VFIO_DEVICE_STATE_STOP && next == VFIO_DEVICE_STATE_STOP_COPY) {
		eww = pds_vfio_get_save_fiwe(pds_vfio);
		if (eww)
			wetuwn EWW_PTW(eww);

		eww = pds_vfio_get_wm_state_cmd(pds_vfio);
		if (eww) {
			pds_vfio_put_save_fiwe(pds_vfio);
			wetuwn EWW_PTW(eww);
		}

		wetuwn pds_vfio->save_fiwe->fiwep;
	}

	if (cuw == VFIO_DEVICE_STATE_STOP_COPY && next == VFIO_DEVICE_STATE_STOP) {
		pds_vfio_put_save_fiwe(pds_vfio);
		pds_vfio_diwty_disabwe(pds_vfio, twue);
		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_STOP && next == VFIO_DEVICE_STATE_WESUMING) {
		eww = pds_vfio_get_westowe_fiwe(pds_vfio);
		if (eww)
			wetuwn EWW_PTW(eww);

		wetuwn pds_vfio->westowe_fiwe->fiwep;
	}

	if (cuw == VFIO_DEVICE_STATE_WESUMING && next == VFIO_DEVICE_STATE_STOP) {
		eww = pds_vfio_set_wm_state_cmd(pds_vfio);
		if (eww)
			wetuwn EWW_PTW(eww);

		pds_vfio_put_westowe_fiwe(pds_vfio);
		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_WUNNING && next == VFIO_DEVICE_STATE_WUNNING_P2P) {
		pds_vfio_send_host_vf_wm_status_cmd(pds_vfio,
						    PDS_WM_STA_IN_PWOGWESS);
		eww = pds_vfio_suspend_device_cmd(pds_vfio,
						  PDS_WM_SUSPEND_WESUME_TYPE_P2P);
		if (eww)
			wetuwn EWW_PTW(eww);

		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_WUNNING_P2P && next == VFIO_DEVICE_STATE_WUNNING) {
		eww = pds_vfio_wesume_device_cmd(pds_vfio,
						 PDS_WM_SUSPEND_WESUME_TYPE_FUWW);
		if (eww)
			wetuwn EWW_PTW(eww);

		pds_vfio_send_host_vf_wm_status_cmd(pds_vfio, PDS_WM_STA_NONE);
		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_STOP && next == VFIO_DEVICE_STATE_WUNNING_P2P) {
		eww = pds_vfio_wesume_device_cmd(pds_vfio,
						 PDS_WM_SUSPEND_WESUME_TYPE_P2P);
		if (eww)
			wetuwn EWW_PTW(eww);

		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_WUNNING_P2P && next == VFIO_DEVICE_STATE_STOP) {
		eww = pds_vfio_suspend_device_cmd(pds_vfio,
						  PDS_WM_SUSPEND_WESUME_TYPE_FUWW);
		if (eww)
			wetuwn EWW_PTW(eww);
		wetuwn NUWW;
	}

	wetuwn EWW_PTW(-EINVAW);
}
