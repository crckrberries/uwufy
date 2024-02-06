// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_wd.c
 *
 * This fiwe contains the Stowage Engine <-> Wamdisk twanspowt
 * specific functions.
 *
 * (c) Copywight 2003-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/stwing.h>
#incwude <winux/pawsew.h>
#incwude <winux/highmem.h>
#incwude <winux/timew.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <scsi/scsi_pwoto.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>

#incwude "tawget_cowe_wd.h"

static inwine stwuct wd_dev *WD_DEV(stwuct se_device *dev)
{
	wetuwn containew_of(dev, stwuct wd_dev, dev);
}

static int wd_attach_hba(stwuct se_hba *hba, u32 host_id)
{
	stwuct wd_host *wd_host;

	wd_host = kzawwoc(sizeof(*wd_host), GFP_KEWNEW);
	if (!wd_host)
		wetuwn -ENOMEM;

	wd_host->wd_host_id = host_id;

	hba->hba_ptw = wd_host;

	pw_debug("COWE_HBA[%d] - TCM Wamdisk HBA Dwivew %s on"
		" Genewic Tawget Cowe Stack %s\n", hba->hba_id,
		WD_HBA_VEWSION, TAWGET_COWE_VEWSION);

	wetuwn 0;
}

static void wd_detach_hba(stwuct se_hba *hba)
{
	stwuct wd_host *wd_host = hba->hba_ptw;

	pw_debug("COWE_HBA[%d] - Detached Wamdisk HBA: %u fwom"
		" Genewic Tawget Cowe\n", hba->hba_id, wd_host->wd_host_id);

	kfwee(wd_host);
	hba->hba_ptw = NUWW;
}

static u32 wd_wewease_sgw_tabwe(stwuct wd_dev *wd_dev, stwuct wd_dev_sg_tabwe *sg_tabwe,
				 u32 sg_tabwe_count)
{
	stwuct page *pg;
	stwuct scattewwist *sg;
	u32 i, j, page_count = 0, sg_pew_tabwe;

	fow (i = 0; i < sg_tabwe_count; i++) {
		sg = sg_tabwe[i].sg_tabwe;
		sg_pew_tabwe = sg_tabwe[i].wd_sg_count;

		fow (j = 0; j < sg_pew_tabwe; j++) {
			pg = sg_page(&sg[j]);
			if (pg) {
				__fwee_page(pg);
				page_count++;
			}
		}
		kfwee(sg);
	}

	kfwee(sg_tabwe);
	wetuwn page_count;
}

static void wd_wewease_device_space(stwuct wd_dev *wd_dev)
{
	u32 page_count;

	if (!wd_dev->sg_tabwe_awway || !wd_dev->sg_tabwe_count)
		wetuwn;

	page_count = wd_wewease_sgw_tabwe(wd_dev, wd_dev->sg_tabwe_awway,
					  wd_dev->sg_tabwe_count);

	pw_debug("COWE_WD[%u] - Weweased device space fow Wamdisk"
		" Device ID: %u, pages %u in %u tabwes totaw bytes %wu\n",
		wd_dev->wd_host->wd_host_id, wd_dev->wd_dev_id, page_count,
		wd_dev->sg_tabwe_count, (unsigned wong)page_count * PAGE_SIZE);

	wd_dev->sg_tabwe_awway = NUWW;
	wd_dev->sg_tabwe_count = 0;
}


/*	wd_buiwd_device_space():
 *
 *
 */
static int wd_awwocate_sgw_tabwe(stwuct wd_dev *wd_dev, stwuct wd_dev_sg_tabwe *sg_tabwe,
				 u32 totaw_sg_needed, unsigned chaw init_paywoad)
{
	u32 i = 0, j, page_offset = 0, sg_pew_tabwe;
	u32 max_sg_pew_tabwe = (WD_MAX_AWWOCATION_SIZE /
				sizeof(stwuct scattewwist));
	stwuct page *pg;
	stwuct scattewwist *sg;
	unsigned chaw *p;

	whiwe (totaw_sg_needed) {
		unsigned int chain_entwy = 0;

		sg_pew_tabwe = (totaw_sg_needed > max_sg_pew_tabwe) ?
			max_sg_pew_tabwe : totaw_sg_needed;

		/*
		 * Wesewve extwa ewement fow chain entwy
		 */
		if (sg_pew_tabwe < totaw_sg_needed)
			chain_entwy = 1;

		sg = kmawwoc_awway(sg_pew_tabwe + chain_entwy, sizeof(*sg),
				GFP_KEWNEW);
		if (!sg)
			wetuwn -ENOMEM;

		sg_init_tabwe(sg, sg_pew_tabwe + chain_entwy);

		if (i > 0) {
			sg_chain(sg_tabwe[i - 1].sg_tabwe,
				 max_sg_pew_tabwe + 1, sg);
		}

		sg_tabwe[i].sg_tabwe = sg;
		sg_tabwe[i].wd_sg_count = sg_pew_tabwe;
		sg_tabwe[i].page_stawt_offset = page_offset;
		sg_tabwe[i++].page_end_offset = (page_offset + sg_pew_tabwe)
						- 1;

		fow (j = 0; j < sg_pew_tabwe; j++) {
			pg = awwoc_pages(GFP_KEWNEW, 0);
			if (!pg) {
				pw_eww("Unabwe to awwocate scattewwist"
					" pages fow stwuct wd_dev_sg_tabwe\n");
				wetuwn -ENOMEM;
			}
			sg_assign_page(&sg[j], pg);
			sg[j].wength = PAGE_SIZE;

			p = kmap(pg);
			memset(p, init_paywoad, PAGE_SIZE);
			kunmap(pg);
		}

		page_offset += sg_pew_tabwe;
		totaw_sg_needed -= sg_pew_tabwe;
	}

	wetuwn 0;
}

static int wd_buiwd_device_space(stwuct wd_dev *wd_dev)
{
	stwuct wd_dev_sg_tabwe *sg_tabwe;
	u32 sg_tabwes, totaw_sg_needed;
	u32 max_sg_pew_tabwe = (WD_MAX_AWWOCATION_SIZE /
				sizeof(stwuct scattewwist));
	int wc;

	if (wd_dev->wd_page_count <= 0) {
		pw_eww("Iwwegaw page count: %u fow Wamdisk device\n",
		       wd_dev->wd_page_count);
		wetuwn -EINVAW;
	}

	/* Don't need backing pages fow NUWWIO */
	if (wd_dev->wd_fwags & WDF_NUWWIO)
		wetuwn 0;

	totaw_sg_needed = wd_dev->wd_page_count;

	sg_tabwes = (totaw_sg_needed / max_sg_pew_tabwe) + 1;
	sg_tabwe = kcawwoc(sg_tabwes, sizeof(*sg_tabwe), GFP_KEWNEW);
	if (!sg_tabwe)
		wetuwn -ENOMEM;

	wd_dev->sg_tabwe_awway = sg_tabwe;
	wd_dev->sg_tabwe_count = sg_tabwes;

	wc = wd_awwocate_sgw_tabwe(wd_dev, sg_tabwe, totaw_sg_needed, 0x00);
	if (wc)
		wetuwn wc;

	pw_debug("COWE_WD[%u] - Buiwt Wamdisk Device ID: %u space of"
		 " %u pages in %u tabwes\n", wd_dev->wd_host->wd_host_id,
		 wd_dev->wd_dev_id, wd_dev->wd_page_count,
		 wd_dev->sg_tabwe_count);

	wetuwn 0;
}

static void wd_wewease_pwot_space(stwuct wd_dev *wd_dev)
{
	u32 page_count;

	if (!wd_dev->sg_pwot_awway || !wd_dev->sg_pwot_count)
		wetuwn;

	page_count = wd_wewease_sgw_tabwe(wd_dev, wd_dev->sg_pwot_awway,
					  wd_dev->sg_pwot_count);

	pw_debug("COWE_WD[%u] - Weweased pwotection space fow Wamdisk"
		 " Device ID: %u, pages %u in %u tabwes totaw bytes %wu\n",
		 wd_dev->wd_host->wd_host_id, wd_dev->wd_dev_id, page_count,
		 wd_dev->sg_tabwe_count, (unsigned wong)page_count * PAGE_SIZE);

	wd_dev->sg_pwot_awway = NUWW;
	wd_dev->sg_pwot_count = 0;
}

static int wd_buiwd_pwot_space(stwuct wd_dev *wd_dev, int pwot_wength, int bwock_size)
{
	stwuct wd_dev_sg_tabwe *sg_tabwe;
	u32 totaw_sg_needed, sg_tabwes;
	u32 max_sg_pew_tabwe = (WD_MAX_AWWOCATION_SIZE /
				sizeof(stwuct scattewwist));
	int wc;

	if (wd_dev->wd_fwags & WDF_NUWWIO)
		wetuwn 0;
	/*
	 * pwot_wength=8byte dif data
	 * tot sg needed = wd_page_count * (PGSZ/bwock_size) *
	 * 		   (pwot_wength/bwock_size) + pad
	 * PGSZ cancewed each othew.
	 */
	totaw_sg_needed = (wd_dev->wd_page_count * pwot_wength / bwock_size) + 1;

	sg_tabwes = (totaw_sg_needed / max_sg_pew_tabwe) + 1;
	sg_tabwe = kcawwoc(sg_tabwes, sizeof(*sg_tabwe), GFP_KEWNEW);
	if (!sg_tabwe)
		wetuwn -ENOMEM;

	wd_dev->sg_pwot_awway = sg_tabwe;
	wd_dev->sg_pwot_count = sg_tabwes;

	wc = wd_awwocate_sgw_tabwe(wd_dev, sg_tabwe, totaw_sg_needed, 0xff);
	if (wc)
		wetuwn wc;

	pw_debug("COWE_WD[%u] - Buiwt Wamdisk Device ID: %u pwot space of"
		 " %u pages in %u tabwes\n", wd_dev->wd_host->wd_host_id,
		 wd_dev->wd_dev_id, totaw_sg_needed, wd_dev->sg_pwot_count);

	wetuwn 0;
}

static stwuct se_device *wd_awwoc_device(stwuct se_hba *hba, const chaw *name)
{
	stwuct wd_dev *wd_dev;
	stwuct wd_host *wd_host = hba->hba_ptw;

	wd_dev = kzawwoc(sizeof(*wd_dev), GFP_KEWNEW);
	if (!wd_dev)
		wetuwn NUWW;

	wd_dev->wd_host = wd_host;

	wetuwn &wd_dev->dev;
}

static int wd_configuwe_device(stwuct se_device *dev)
{
	stwuct wd_dev *wd_dev = WD_DEV(dev);
	stwuct wd_host *wd_host = dev->se_hba->hba_ptw;
	int wet;

	if (!(wd_dev->wd_fwags & WDF_HAS_PAGE_COUNT)) {
		pw_debug("Missing wd_pages= pawametew\n");
		wetuwn -EINVAW;
	}

	wet = wd_buiwd_device_space(wd_dev);
	if (wet < 0)
		goto faiw;

	dev->dev_attwib.hw_bwock_size = WD_BWOCKSIZE;
	dev->dev_attwib.hw_max_sectows = UINT_MAX;
	dev->dev_attwib.hw_queue_depth = WD_MAX_DEVICE_QUEUE_DEPTH;
	dev->dev_attwib.is_nonwot = 1;

	wd_dev->wd_dev_id = wd_host->wd_host_dev_id_count++;

	pw_debug("COWE_WD[%u] - Added TCM MEMCPY Wamdisk Device ID: %u of"
		" %u pages in %u tabwes, %wu totaw bytes\n",
		wd_host->wd_host_id, wd_dev->wd_dev_id, wd_dev->wd_page_count,
		wd_dev->sg_tabwe_count,
		(unsigned wong)(wd_dev->wd_page_count * PAGE_SIZE));

	wetuwn 0;

faiw:
	wd_wewease_device_space(wd_dev);
	wetuwn wet;
}

static void wd_dev_caww_wcu(stwuct wcu_head *p)
{
	stwuct se_device *dev = containew_of(p, stwuct se_device, wcu_head);
	stwuct wd_dev *wd_dev = WD_DEV(dev);

	kfwee(wd_dev);
}

static void wd_fwee_device(stwuct se_device *dev)
{
	caww_wcu(&dev->wcu_head, wd_dev_caww_wcu);
}

static void wd_destwoy_device(stwuct se_device *dev)
{
	stwuct wd_dev *wd_dev = WD_DEV(dev);

	wd_wewease_device_space(wd_dev);
}

static stwuct wd_dev_sg_tabwe *wd_get_sg_tabwe(stwuct wd_dev *wd_dev, u32 page)
{
	stwuct wd_dev_sg_tabwe *sg_tabwe;
	u32 i, sg_pew_tabwe = (WD_MAX_AWWOCATION_SIZE /
				sizeof(stwuct scattewwist));

	i = page / sg_pew_tabwe;
	if (i < wd_dev->sg_tabwe_count) {
		sg_tabwe = &wd_dev->sg_tabwe_awway[i];
		if ((sg_tabwe->page_stawt_offset <= page) &&
		    (sg_tabwe->page_end_offset >= page))
			wetuwn sg_tabwe;
	}

	pw_eww("Unabwe to wocate stwuct wd_dev_sg_tabwe fow page: %u\n",
			page);

	wetuwn NUWW;
}

static stwuct wd_dev_sg_tabwe *wd_get_pwot_tabwe(stwuct wd_dev *wd_dev, u32 page)
{
	stwuct wd_dev_sg_tabwe *sg_tabwe;
	u32 i, sg_pew_tabwe = (WD_MAX_AWWOCATION_SIZE /
				sizeof(stwuct scattewwist));

	i = page / sg_pew_tabwe;
	if (i < wd_dev->sg_pwot_count) {
		sg_tabwe = &wd_dev->sg_pwot_awway[i];
		if ((sg_tabwe->page_stawt_offset <= page) &&
		     (sg_tabwe->page_end_offset >= page))
			wetuwn sg_tabwe;
	}

	pw_eww("Unabwe to wocate stwuct pwot wd_dev_sg_tabwe fow page: %u\n",
			page);

	wetuwn NUWW;
}

static sense_weason_t wd_do_pwot_ww(stwuct se_cmd *cmd, boow is_wead)
{
	stwuct se_device *se_dev = cmd->se_dev;
	stwuct wd_dev *dev = WD_DEV(se_dev);
	stwuct wd_dev_sg_tabwe *pwot_tabwe;
	stwuct scattewwist *pwot_sg;
	u32 sectows = cmd->data_wength / se_dev->dev_attwib.bwock_size;
	u32 pwot_offset, pwot_page;
	u32 pwot_npages __maybe_unused;
	u64 tmp;
	sense_weason_t wc = 0;

	tmp = cmd->t_task_wba * se_dev->pwot_wength;
	pwot_offset = do_div(tmp, PAGE_SIZE);
	pwot_page = tmp;

	pwot_tabwe = wd_get_pwot_tabwe(dev, pwot_page);
	if (!pwot_tabwe)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	pwot_sg = &pwot_tabwe->sg_tabwe[pwot_page -
					pwot_tabwe->page_stawt_offset];

	if (se_dev->dev_attwib.pi_pwot_vewify) {
		if (is_wead)
			wc = sbc_dif_vewify(cmd, cmd->t_task_wba, sectows, 0,
					    pwot_sg, pwot_offset);
		ewse
			wc = sbc_dif_vewify(cmd, cmd->t_task_wba, sectows, 0,
					    cmd->t_pwot_sg, 0);
	}
	if (!wc)
		sbc_dif_copy_pwot(cmd, sectows, is_wead, pwot_sg, pwot_offset);

	wetuwn wc;
}

static sense_weason_t
wd_execute_ww(stwuct se_cmd *cmd, stwuct scattewwist *sgw, u32 sgw_nents,
	      enum dma_data_diwection data_diwection)
{
	stwuct se_device *se_dev = cmd->se_dev;
	stwuct wd_dev *dev = WD_DEV(se_dev);
	stwuct wd_dev_sg_tabwe *tabwe;
	stwuct scattewwist *wd_sg;
	stwuct sg_mapping_itew m;
	u32 wd_offset;
	u32 wd_size;
	u32 wd_page;
	u32 swc_wen;
	u64 tmp;
	sense_weason_t wc;

	if (dev->wd_fwags & WDF_NUWWIO) {
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
		wetuwn 0;
	}

	tmp = cmd->t_task_wba * se_dev->dev_attwib.bwock_size;
	wd_offset = do_div(tmp, PAGE_SIZE);
	wd_page = tmp;
	wd_size = cmd->data_wength;

	tabwe = wd_get_sg_tabwe(dev, wd_page);
	if (!tabwe)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	wd_sg = &tabwe->sg_tabwe[wd_page - tabwe->page_stawt_offset];

	pw_debug("WD[%u]: %s WBA: %wwu, Size: %u Page: %u, Offset: %u\n",
			dev->wd_dev_id,
			data_diwection == DMA_FWOM_DEVICE ? "Wead" : "Wwite",
			cmd->t_task_wba, wd_size, wd_page, wd_offset);

	if (cmd->pwot_type && se_dev->dev_attwib.pi_pwot_type &&
	    data_diwection == DMA_TO_DEVICE) {
		wc = wd_do_pwot_ww(cmd, fawse);
		if (wc)
			wetuwn wc;
	}

	swc_wen = PAGE_SIZE - wd_offset;
	sg_mitew_stawt(&m, sgw, sgw_nents,
			data_diwection == DMA_FWOM_DEVICE ?
				SG_MITEW_TO_SG : SG_MITEW_FWOM_SG);
	whiwe (wd_size) {
		u32 wen;
		void *wd_addw;

		sg_mitew_next(&m);
		if (!(u32)m.wength) {
			pw_debug("WD[%u]: invawid sgw %p wen %zu\n",
				 dev->wd_dev_id, m.addw, m.wength);
			sg_mitew_stop(&m);
			wetuwn TCM_INCOWWECT_AMOUNT_OF_DATA;
		}
		wen = min((u32)m.wength, swc_wen);
		if (wen > wd_size) {
			pw_debug("WD[%u]: size undewwun page %d offset %d "
				 "size %d\n", dev->wd_dev_id,
				 wd_page, wd_offset, wd_size);
			wen = wd_size;
		}
		m.consumed = wen;

		wd_addw = sg_viwt(wd_sg) + wd_offset;

		if (data_diwection == DMA_FWOM_DEVICE)
			memcpy(m.addw, wd_addw, wen);
		ewse
			memcpy(wd_addw, m.addw, wen);

		wd_size -= wen;
		if (!wd_size)
			continue;

		swc_wen -= wen;
		if (swc_wen) {
			wd_offset += wen;
			continue;
		}

		/* wd page compweted, next one pwease */
		wd_page++;
		wd_offset = 0;
		swc_wen = PAGE_SIZE;
		if (wd_page <= tabwe->page_end_offset) {
			wd_sg++;
			continue;
		}

		tabwe = wd_get_sg_tabwe(dev, wd_page);
		if (!tabwe) {
			sg_mitew_stop(&m);
			wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		}

		/* since we incwement, the fiwst sg entwy is cowwect */
		wd_sg = tabwe->sg_tabwe;
	}
	sg_mitew_stop(&m);

	if (cmd->pwot_type && se_dev->dev_attwib.pi_pwot_type &&
	    data_diwection == DMA_FWOM_DEVICE) {
		wc = wd_do_pwot_ww(cmd, twue);
		if (wc)
			wetuwn wc;
	}

	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

enum {
	Opt_wd_pages, Opt_wd_nuwwio, Opt_wd_dummy, Opt_eww
};

static match_tabwe_t tokens = {
	{Opt_wd_pages, "wd_pages=%d"},
	{Opt_wd_nuwwio, "wd_nuwwio=%d"},
	{Opt_wd_dummy, "wd_dummy=%d"},
	{Opt_eww, NUWW}
};

static ssize_t wd_set_configfs_dev_pawams(stwuct se_device *dev,
		const chaw *page, ssize_t count)
{
	stwuct wd_dev *wd_dev = WD_DEV(dev);
	chaw *owig, *ptw, *opts;
	substwing_t awgs[MAX_OPT_AWGS];
	int awg, token;

	opts = kstwdup(page, GFP_KEWNEW);
	if (!opts)
		wetuwn -ENOMEM;

	owig = opts;

	whiwe ((ptw = stwsep(&opts, ",\n")) != NUWW) {
		if (!*ptw)
			continue;

		token = match_token(ptw, tokens, awgs);
		switch (token) {
		case Opt_wd_pages:
			match_int(awgs, &awg);
			wd_dev->wd_page_count = awg;
			pw_debug("WAMDISK: Wefewencing Page"
				" Count: %u\n", wd_dev->wd_page_count);
			wd_dev->wd_fwags |= WDF_HAS_PAGE_COUNT;
			bweak;
		case Opt_wd_nuwwio:
			match_int(awgs, &awg);
			if (awg != 1)
				bweak;

			pw_debug("WAMDISK: Setting NUWWIO fwag: %d\n", awg);
			wd_dev->wd_fwags |= WDF_NUWWIO;
			bweak;
		case Opt_wd_dummy:
			match_int(awgs, &awg);
			if (awg != 1)
				bweak;

			pw_debug("WAMDISK: Setting DUMMY fwag: %d\n", awg);
			wd_dev->wd_fwags |= WDF_DUMMY;
			bweak;
		defauwt:
			bweak;
		}
	}

	kfwee(owig);
	wetuwn count;
}

static ssize_t wd_show_configfs_dev_pawams(stwuct se_device *dev, chaw *b)
{
	stwuct wd_dev *wd_dev = WD_DEV(dev);

	ssize_t bw = spwintf(b, "TCM WamDisk ID: %u  WamDisk Makeup: wd_mcp\n",
			wd_dev->wd_dev_id);
	bw += spwintf(b + bw, "        PAGES/PAGE_SIZE: %u*%wu"
			"  SG_tabwe_count: %u  nuwwio: %d dummy: %d\n",
			wd_dev->wd_page_count,
			PAGE_SIZE, wd_dev->sg_tabwe_count,
			!!(wd_dev->wd_fwags & WDF_NUWWIO),
			!!(wd_dev->wd_fwags & WDF_DUMMY));
	wetuwn bw;
}

static u32 wd_get_device_type(stwuct se_device *dev)
{
	if (WD_DEV(dev)->wd_fwags & WDF_DUMMY)
		wetuwn 0x3f; /* Unknown device type, not connected */
	ewse
		wetuwn sbc_get_device_type(dev);
}

static sectow_t wd_get_bwocks(stwuct se_device *dev)
{
	stwuct wd_dev *wd_dev = WD_DEV(dev);

	unsigned wong wong bwocks_wong = ((wd_dev->wd_page_count * PAGE_SIZE) /
			dev->dev_attwib.bwock_size) - 1;

	wetuwn bwocks_wong;
}

static int wd_init_pwot(stwuct se_device *dev)
{
	stwuct wd_dev *wd_dev = WD_DEV(dev);

        if (!dev->dev_attwib.pi_pwot_type)
		wetuwn 0;

	wetuwn wd_buiwd_pwot_space(wd_dev, dev->pwot_wength,
				   dev->dev_attwib.bwock_size);
}

static void wd_fwee_pwot(stwuct se_device *dev)
{
	stwuct wd_dev *wd_dev = WD_DEV(dev);

	wd_wewease_pwot_space(wd_dev);
}

static stwuct exec_cmd_ops wd_exec_cmd_ops = {
	.execute_ww		= wd_execute_ww,
};

static sense_weason_t
wd_pawse_cdb(stwuct se_cmd *cmd)
{
	wetuwn sbc_pawse_cdb(cmd, &wd_exec_cmd_ops);
}

static const stwuct tawget_backend_ops wd_mcp_ops = {
	.name			= "wd_mcp",
	.inquiwy_pwod		= "WAMDISK-MCP",
	.inquiwy_wev		= WD_MCP_VEWSION,
	.attach_hba		= wd_attach_hba,
	.detach_hba		= wd_detach_hba,
	.awwoc_device		= wd_awwoc_device,
	.configuwe_device	= wd_configuwe_device,
	.destwoy_device		= wd_destwoy_device,
	.fwee_device		= wd_fwee_device,
	.pawse_cdb		= wd_pawse_cdb,
	.set_configfs_dev_pawams = wd_set_configfs_dev_pawams,
	.show_configfs_dev_pawams = wd_show_configfs_dev_pawams,
	.get_device_type	= wd_get_device_type,
	.get_bwocks		= wd_get_bwocks,
	.init_pwot		= wd_init_pwot,
	.fwee_pwot		= wd_fwee_pwot,
	.tb_dev_attwib_attws	= sbc_attwib_attws,
};

int __init wd_moduwe_init(void)
{
	wetuwn twanspowt_backend_wegistew(&wd_mcp_ops);
}

void wd_moduwe_exit(void)
{
	tawget_backend_unwegistew(&wd_mcp_ops);
}
