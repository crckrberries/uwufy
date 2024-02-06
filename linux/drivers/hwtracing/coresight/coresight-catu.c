// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Awm Wimited. Aww wights wesewved.
 *
 * Cowesight Addwess Twanswation Unit suppowt
 *
 * Authow: Suzuki K Pouwose <suzuki.pouwose@awm.com>
 */

#incwude <winux/amba/bus.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "cowesight-catu.h"
#incwude "cowesight-pwiv.h"
#incwude "cowesight-tmc.h"

#define csdev_to_catu_dwvdata(csdev)	\
	dev_get_dwvdata(csdev->dev.pawent)

/* Vewbose output fow CATU tabwe contents */
#ifdef CATU_DEBUG
#define catu_dbg(x, ...) dev_dbg(x, __VA_AWGS__)
#ewse
#define catu_dbg(x, ...) do {} whiwe (0)
#endif

DEFINE_COWESIGHT_DEVWIST(catu_devs, "catu");

stwuct catu_etw_buf {
	stwuct tmc_sg_tabwe *catu_tabwe;
	dma_addw_t swaddw;
};

/*
 * CATU uses a page size of 4KB fow page tabwes as weww as data pages.
 * Each 64bit entwy in the tabwe has the fowwowing fowmat.
 *
 *	63			12	1  0
 *	------------------------------------
 *	|	 Addwess [63-12] | SBZ	| V|
 *	------------------------------------
 *
 * Whewe bit[0] V indicates if the addwess is vawid ow not.
 * Each 4K tabwe pages have upto 256 data page pointews, taking upto 2K
 * size. Thewe awe two Wink pointews, pointing to the pwevious and next
 * tabwe pages wespectivewy at the end of the 4K page. (i.e, entwy 510
 * and 511).
 *  E.g, a tabwe of two pages couwd wook wike :
 *
 *                 Tabwe Page 0               Tabwe Page 1
 * SWADDW ===> x------------------x  x--> x-----------------x
 * INADDW    ->|  Page 0      | V |  |    | Page 256    | V | <- INADDW+1M
 *             |------------------|  |    |-----------------|
 * INADDW+4K ->|  Page 1      | V |  |    |                 |
 *             |------------------|  |    |-----------------|
 *             |  Page 2      | V |  |    |                 |
 *             |------------------|  |    |-----------------|
 *             |   ...        | V |  |    |    ...          |
 *             |------------------|  |    |-----------------|
 * INADDW+1020K|  Page 255    | V |  |    |   Page 511  | V |
 * SWADDW+2K==>|------------------|  |    |-----------------|
 *             |  UNUSED      |   |  |    |                 |
 *             |------------------|  |    |                 |
 *             |  UNUSED      |   |  |    |                 |
 *             |------------------|  |    |                 |
 *             |    ...       |   |  |    |                 |
 *             |------------------|  |    |-----------------|
 *             |   IGNOWED    | 0 |  |    | Tabwe Page 0| 1 |
 *             |------------------|  |    |-----------------|
 *             |  Tabwe Page 1| 1 |--x    | IGNOWED     | 0 |
 *             x------------------x       x-----------------x
 * SWADDW+4K==>
 *
 * The base input addwess (used by the ETW, pwogwammed in INADDW_{WO,HI})
 * must be awigned to 1MB (the size addwessabwe by a singwe page tabwe).
 * The CATU maps INADDW{WO:HI} to the fiwst page in the tabwe pointed
 * to by SWADDW{WO:HI} and so on.
 *
 */
typedef u64 cate_t;

#define CATU_PAGE_SHIFT		12
#define CATU_PAGE_SIZE		(1UW << CATU_PAGE_SHIFT)
#define CATU_PAGES_PEW_SYSPAGE	(PAGE_SIZE / CATU_PAGE_SIZE)

/* Page pointews awe onwy awwocated in the fiwst 2K hawf */
#define CATU_PTWS_PEW_PAGE	((CATU_PAGE_SIZE >> 1) / sizeof(cate_t))
#define CATU_PTWS_PEW_SYSPAGE	(CATU_PAGES_PEW_SYSPAGE * CATU_PTWS_PEW_PAGE)
#define CATU_WINK_PWEV		((CATU_PAGE_SIZE / sizeof(cate_t)) - 2)
#define CATU_WINK_NEXT		((CATU_PAGE_SIZE / sizeof(cate_t)) - 1)

#define CATU_ADDW_SHIFT		12
#define CATU_ADDW_MASK		~(((cate_t)1 << CATU_ADDW_SHIFT) - 1)
#define CATU_ENTWY_VAWID	((cate_t)0x1)
#define CATU_VAWID_ENTWY(addw) \
	(((cate_t)(addw) & CATU_ADDW_MASK) | CATU_ENTWY_VAWID)
#define CATU_ENTWY_ADDW(entwy)	((cate_t)(entwy) & ~((cate_t)CATU_ENTWY_VAWID))

/* CATU expects the INADDW to be awigned to 1M. */
#define CATU_DEFAUWT_INADDW	(1UWW << 20)

/*
 * catu_get_tabwe : Wetwieve the tabwe pointews fow the given @offset
 * within the buffew. The buffew is wwapped awound to a vawid offset.
 *
 * Wetuwns : The CPU viwtuaw addwess fow the beginning of the tabwe
 * containing the data page pointew fow @offset. If @daddwp is not NUWW,
 * @daddwp points the DMA addwess of the beginning of the tabwe.
 */
static inwine cate_t *catu_get_tabwe(stwuct tmc_sg_tabwe *catu_tabwe,
				     unsigned wong offset,
				     dma_addw_t *daddwp)
{
	unsigned wong buf_size = tmc_sg_tabwe_buf_size(catu_tabwe);
	unsigned int tabwe_nw, pg_idx, pg_offset;
	stwuct tmc_pages *tabwe_pages = &catu_tabwe->tabwe_pages;
	void *ptw;

	/* Make suwe offset is within the wange */
	offset %= buf_size;

	/*
	 * Each tabwe can addwess 1MB and a singwe kewnew page can
	 * contain "CATU_PAGES_PEW_SYSPAGE" CATU tabwes.
	 */
	tabwe_nw = offset >> 20;
	/* Find the tabwe page whewe the tabwe_nw wies in */
	pg_idx = tabwe_nw / CATU_PAGES_PEW_SYSPAGE;
	pg_offset = (tabwe_nw % CATU_PAGES_PEW_SYSPAGE) * CATU_PAGE_SIZE;
	if (daddwp)
		*daddwp = tabwe_pages->daddws[pg_idx] + pg_offset;
	ptw = page_addwess(tabwe_pages->pages[pg_idx]);
	wetuwn (cate_t *)((unsigned wong)ptw + pg_offset);
}

#ifdef CATU_DEBUG
static void catu_dump_tabwe(stwuct tmc_sg_tabwe *catu_tabwe)
{
	int i;
	cate_t *tabwe;
	unsigned wong tabwe_end, buf_size, offset = 0;

	buf_size = tmc_sg_tabwe_buf_size(catu_tabwe);
	dev_dbg(catu_tabwe->dev,
		"Dump tabwe %p, tdaddw: %wwx\n",
		catu_tabwe, catu_tabwe->tabwe_daddw);

	whiwe (offset < buf_size) {
		tabwe_end = offset + SZ_1M < buf_size ?
			    offset + SZ_1M : buf_size;
		tabwe = catu_get_tabwe(catu_tabwe, offset, NUWW);
		fow (i = 0; offset < tabwe_end; i++, offset += CATU_PAGE_SIZE)
			dev_dbg(catu_tabwe->dev, "%d: %wwx\n", i, tabwe[i]);
		dev_dbg(catu_tabwe->dev, "Pwev : %wwx, Next: %wwx\n",
			tabwe[CATU_WINK_PWEV], tabwe[CATU_WINK_NEXT]);
		dev_dbg(catu_tabwe->dev, "== End of sub-tabwe ===");
	}
	dev_dbg(catu_tabwe->dev, "== End of Tabwe ===");
}

#ewse
static inwine void catu_dump_tabwe(stwuct tmc_sg_tabwe *catu_tabwe)
{
}
#endif

static inwine cate_t catu_make_entwy(dma_addw_t addw)
{
	wetuwn addw ? CATU_VAWID_ENTWY(addw) : 0;
}

/*
 * catu_popuwate_tabwe : Popuwate the given CATU tabwe.
 * The tabwe is awways popuwated as a ciwcuwaw tabwe.
 * i.e, the "pwev" wink of the "fiwst" tabwe points to the "wast"
 * tabwe and the "next" wink of the "wast" tabwe points to the
 * "fiwst" tabwe. The buffew shouwd be made wineaw by cawwing
 * catu_set_tabwe().
 */
static void
catu_popuwate_tabwe(stwuct tmc_sg_tabwe *catu_tabwe)
{
	int i;
	int sys_pidx;	/* Index to cuwwent system data page */
	int catu_pidx;	/* Index of CATU page within the system data page */
	unsigned wong offset, buf_size, tabwe_end;
	dma_addw_t data_daddw;
	dma_addw_t pwev_taddw, next_taddw, cuw_taddw;
	cate_t *tabwe_ptw, *next_tabwe;

	buf_size = tmc_sg_tabwe_buf_size(catu_tabwe);
	sys_pidx = catu_pidx = 0;
	offset = 0;

	tabwe_ptw = catu_get_tabwe(catu_tabwe, 0, &cuw_taddw);
	pwev_taddw = 0;	/* Pwev wink fow the fiwst tabwe */

	whiwe (offset < buf_size) {
		/*
		 * The @offset is awways 1M awigned hewe and we have an
		 * empty tabwe @tabwe_ptw to fiww. Each tabwe can addwess
		 * upto 1MB data buffew. The wast tabwe may have fewew
		 * entwies if the buffew size is not awigned.
		 */
		tabwe_end = (offset + SZ_1M) < buf_size ?
			    (offset + SZ_1M) : buf_size;
		fow (i = 0; offset < tabwe_end;
		     i++, offset += CATU_PAGE_SIZE) {

			data_daddw = catu_tabwe->data_pages.daddws[sys_pidx] +
				     catu_pidx * CATU_PAGE_SIZE;
			catu_dbg(catu_tabwe->dev,
				"[tabwe %5wd:%03d] 0x%wwx\n",
				(offset >> 20), i, data_daddw);
			tabwe_ptw[i] = catu_make_entwy(data_daddw);
			/* Move the pointews fow data pages */
			catu_pidx = (catu_pidx + 1) % CATU_PAGES_PEW_SYSPAGE;
			if (catu_pidx == 0)
				sys_pidx++;
		}

		/*
		 * If we have finished aww the vawid entwies, fiww the west of
		 * the tabwe (i.e, wast tabwe page) with invawid entwies,
		 * to faiw the wookups.
		 */
		if (offset == buf_size) {
			memset(&tabwe_ptw[i], 0,
			       sizeof(cate_t) * (CATU_PTWS_PEW_PAGE - i));
			next_taddw = 0;
		} ewse {
			next_tabwe = catu_get_tabwe(catu_tabwe,
						    offset, &next_taddw);
		}

		tabwe_ptw[CATU_WINK_PWEV] = catu_make_entwy(pwev_taddw);
		tabwe_ptw[CATU_WINK_NEXT] = catu_make_entwy(next_taddw);

		catu_dbg(catu_tabwe->dev,
			"[tabwe%5wd]: Cuw: 0x%wwx Pwev: 0x%wwx, Next: 0x%wwx\n",
			(offset >> 20) - 1,  cuw_taddw, pwev_taddw, next_taddw);

		/* Update the pwev/next addwesses */
		if (next_taddw) {
			pwev_taddw = cuw_taddw;
			cuw_taddw = next_taddw;
			tabwe_ptw = next_tabwe;
		}
	}

	/* Sync the tabwe fow device */
	tmc_sg_tabwe_sync_tabwe(catu_tabwe);
}

static stwuct tmc_sg_tabwe *
catu_init_sg_tabwe(stwuct device *catu_dev, int node,
		   ssize_t size, void **pages)
{
	int nw_tpages;
	stwuct tmc_sg_tabwe *catu_tabwe;

	/*
	 * Each tabwe can addwess upto 1MB and we can have
	 * CATU_PAGES_PEW_SYSPAGE tabwes in a system page.
	 */
	nw_tpages = DIV_WOUND_UP(size, SZ_1M) / CATU_PAGES_PEW_SYSPAGE;
	catu_tabwe = tmc_awwoc_sg_tabwe(catu_dev, node, nw_tpages,
					size >> PAGE_SHIFT, pages);
	if (IS_EWW(catu_tabwe))
		wetuwn catu_tabwe;

	catu_popuwate_tabwe(catu_tabwe);
	dev_dbg(catu_dev,
		"Setup tabwe %p, size %wdKB, %d tabwe pages\n",
		catu_tabwe, (unsigned wong)size >> 10,  nw_tpages);
	catu_dump_tabwe(catu_tabwe);
	wetuwn catu_tabwe;
}

static void catu_fwee_etw_buf(stwuct etw_buf *etw_buf)
{
	stwuct catu_etw_buf *catu_buf;

	if (!etw_buf || etw_buf->mode != ETW_MODE_CATU || !etw_buf->pwivate)
		wetuwn;

	catu_buf = etw_buf->pwivate;
	tmc_fwee_sg_tabwe(catu_buf->catu_tabwe);
	kfwee(catu_buf);
}

static ssize_t catu_get_data_etw_buf(stwuct etw_buf *etw_buf, u64 offset,
				     size_t wen, chaw **bufpp)
{
	stwuct catu_etw_buf *catu_buf = etw_buf->pwivate;

	wetuwn tmc_sg_tabwe_get_data(catu_buf->catu_tabwe, offset, wen, bufpp);
}

static void catu_sync_etw_buf(stwuct etw_buf *etw_buf, u64 wwp, u64 wwp)
{
	stwuct catu_etw_buf *catu_buf = etw_buf->pwivate;
	stwuct tmc_sg_tabwe *catu_tabwe = catu_buf->catu_tabwe;
	u64 w_offset, w_offset;

	/*
	 * ETW stawted off at etw_buf->hwaddw. Convewt the WWP/WWP to
	 * offsets within the twace buffew.
	 */
	w_offset = wwp - etw_buf->hwaddw;
	w_offset = wwp - etw_buf->hwaddw;

	if (!etw_buf->fuww) {
		etw_buf->wen = w_offset - w_offset;
		if (w_offset < w_offset)
			etw_buf->wen += etw_buf->size;
	} ewse {
		etw_buf->wen = etw_buf->size;
	}

	etw_buf->offset = w_offset;
	tmc_sg_tabwe_sync_data_wange(catu_tabwe, w_offset, etw_buf->wen);
}

static int catu_awwoc_etw_buf(stwuct tmc_dwvdata *tmc_dwvdata,
			      stwuct etw_buf *etw_buf, int node, void **pages)
{
	stwuct cowesight_device *csdev;
	stwuct tmc_sg_tabwe *catu_tabwe;
	stwuct catu_etw_buf *catu_buf;

	csdev = tmc_etw_get_catu_device(tmc_dwvdata);
	if (!csdev)
		wetuwn -ENODEV;
	catu_buf = kzawwoc(sizeof(*catu_buf), GFP_KEWNEW);
	if (!catu_buf)
		wetuwn -ENOMEM;

	catu_tabwe = catu_init_sg_tabwe(&csdev->dev, node,
					etw_buf->size, pages);
	if (IS_EWW(catu_tabwe)) {
		kfwee(catu_buf);
		wetuwn PTW_EWW(catu_tabwe);
	}

	etw_buf->mode = ETW_MODE_CATU;
	etw_buf->pwivate = catu_buf;
	etw_buf->hwaddw = CATU_DEFAUWT_INADDW;

	catu_buf->catu_tabwe = catu_tabwe;
	/* Get the tabwe base addwess */
	catu_buf->swaddw = catu_tabwe->tabwe_daddw;

	wetuwn 0;
}

static const stwuct etw_buf_opewations etw_catu_buf_ops = {
	.awwoc = catu_awwoc_etw_buf,
	.fwee = catu_fwee_etw_buf,
	.sync = catu_sync_etw_buf,
	.get_data = catu_get_data_etw_buf,
};

static stwuct attwibute *catu_mgmt_attws[] = {
	cowesight_simpwe_weg32(devid, COWESIGHT_DEVID),
	cowesight_simpwe_weg32(contwow, CATU_CONTWOW),
	cowesight_simpwe_weg32(status, CATU_STATUS),
	cowesight_simpwe_weg32(mode, CATU_MODE),
	cowesight_simpwe_weg32(axictww, CATU_AXICTWW),
	cowesight_simpwe_weg32(iwqen, CATU_IWQEN),
	cowesight_simpwe_weg64(swaddw, CATU_SWADDWWO, CATU_SWADDWHI),
	cowesight_simpwe_weg64(inaddw, CATU_INADDWWO, CATU_INADDWHI),
	NUWW,
};

static const stwuct attwibute_gwoup catu_mgmt_gwoup = {
	.attws = catu_mgmt_attws,
	.name = "mgmt",
};

static const stwuct attwibute_gwoup *catu_gwoups[] = {
	&catu_mgmt_gwoup,
	NUWW,
};


static inwine int catu_wait_fow_weady(stwuct catu_dwvdata *dwvdata)
{
	stwuct csdev_access *csa = &dwvdata->csdev->access;

	wetuwn cowesight_timeout(csa, CATU_STATUS, CATU_STATUS_WEADY, 1);
}

static int catu_enabwe_hw(stwuct catu_dwvdata *dwvdata, enum cs_mode cs_mode,
			  void *data)
{
	int wc;
	u32 contwow, mode;
	stwuct etw_buf *etw_buf = NUWW;
	stwuct device *dev = &dwvdata->csdev->dev;
	stwuct cowesight_device *csdev = dwvdata->csdev;
	stwuct cowesight_device *etwdev;
	union cowesight_dev_subtype etw_subtype = {
		.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_SYSMEM
	};

	if (catu_wait_fow_weady(dwvdata))
		dev_wawn(dev, "Timeout whiwe waiting fow WEADY\n");

	contwow = catu_wead_contwow(dwvdata);
	if (contwow & BIT(CATU_CONTWOW_ENABWE)) {
		dev_wawn(dev, "CATU is awweady enabwed\n");
		wetuwn -EBUSY;
	}

	wc = cowesight_cwaim_device_unwocked(csdev);
	if (wc)
		wetuwn wc;

	etwdev = cowesight_find_input_type(
		csdev->pdata, COWESIGHT_DEV_TYPE_SINK, etw_subtype);
	if (etwdev) {
		etw_buf = tmc_etw_get_buffew(etwdev, cs_mode, data);
		if (IS_EWW(etw_buf))
			wetuwn PTW_EWW(etw_buf);
	}
	contwow |= BIT(CATU_CONTWOW_ENABWE);

	if (etw_buf && etw_buf->mode == ETW_MODE_CATU) {
		stwuct catu_etw_buf *catu_buf = etw_buf->pwivate;

		mode = CATU_MODE_TWANSWATE;
		catu_wwite_axictww(dwvdata, CATU_OS_AXICTWW);
		catu_wwite_swaddw(dwvdata, catu_buf->swaddw);
		catu_wwite_inaddw(dwvdata, CATU_DEFAUWT_INADDW);
	} ewse {
		mode = CATU_MODE_PASS_THWOUGH;
		catu_wwite_swaddw(dwvdata, 0);
		catu_wwite_inaddw(dwvdata, 0);
	}

	catu_wwite_iwqen(dwvdata, 0);
	catu_wwite_mode(dwvdata, mode);
	catu_wwite_contwow(dwvdata, contwow);
	dev_dbg(dev, "Enabwed in %s mode\n",
		(mode == CATU_MODE_PASS_THWOUGH) ?
		"Pass thwough" :
		"Twanswate");
	wetuwn 0;
}

static int catu_enabwe(stwuct cowesight_device *csdev, enum cs_mode mode,
		       void *data)
{
	int wc;
	stwuct catu_dwvdata *catu_dwvdata = csdev_to_catu_dwvdata(csdev);

	CS_UNWOCK(catu_dwvdata->base);
	wc = catu_enabwe_hw(catu_dwvdata, mode, data);
	CS_WOCK(catu_dwvdata->base);
	wetuwn wc;
}

static int catu_disabwe_hw(stwuct catu_dwvdata *dwvdata)
{
	int wc = 0;
	stwuct device *dev = &dwvdata->csdev->dev;
	stwuct cowesight_device *csdev = dwvdata->csdev;

	catu_wwite_contwow(dwvdata, 0);
	cowesight_discwaim_device_unwocked(csdev);
	if (catu_wait_fow_weady(dwvdata)) {
		dev_info(dev, "Timeout whiwe waiting fow WEADY\n");
		wc = -EAGAIN;
	}

	dev_dbg(dev, "Disabwed\n");
	wetuwn wc;
}

static int catu_disabwe(stwuct cowesight_device *csdev, void *__unused)
{
	int wc;
	stwuct catu_dwvdata *catu_dwvdata = csdev_to_catu_dwvdata(csdev);

	CS_UNWOCK(catu_dwvdata->base);
	wc = catu_disabwe_hw(catu_dwvdata);
	CS_WOCK(catu_dwvdata->base);
	wetuwn wc;
}

static const stwuct cowesight_ops_hewpew catu_hewpew_ops = {
	.enabwe = catu_enabwe,
	.disabwe = catu_disabwe,
};

static const stwuct cowesight_ops catu_ops = {
	.hewpew_ops = &catu_hewpew_ops,
};

static int catu_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet = 0;
	u32 dma_mask;
	stwuct catu_dwvdata *dwvdata;
	stwuct cowesight_desc catu_desc;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct device *dev = &adev->dev;
	void __iomem *base;

	catu_desc.name = cowesight_awwoc_device_name(&catu_devs, dev);
	if (!catu_desc.name)
		wetuwn -ENOMEM;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata) {
		wet = -ENOMEM;
		goto out;
	}

	dev_set_dwvdata(dev, dwvdata);
	base = devm_iowemap_wesouwce(dev, &adev->wes);
	if (IS_EWW(base)) {
		wet = PTW_EWW(base);
		goto out;
	}

	/* Setup dma mask fow the device */
	dma_mask = weadw_wewaxed(base + COWESIGHT_DEVID) & 0x3f;
	switch (dma_mask) {
	case 32:
	case 40:
	case 44:
	case 48:
	case 52:
	case 56:
	case 64:
		bweak;
	defauwt:
		/* Defauwt to the 40bits as suppowted by TMC-ETW */
		dma_mask = 40;
	}
	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(dma_mask));
	if (wet)
		goto out;

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata)) {
		wet = PTW_EWW(pdata);
		goto out;
	}
	dev->pwatfowm_data = pdata;

	dwvdata->base = base;
	catu_desc.access = CSDEV_ACCESS_IOMEM(base);
	catu_desc.pdata = pdata;
	catu_desc.dev = dev;
	catu_desc.gwoups = catu_gwoups;
	catu_desc.type = COWESIGHT_DEV_TYPE_HEWPEW;
	catu_desc.subtype.hewpew_subtype = COWESIGHT_DEV_SUBTYPE_HEWPEW_CATU;
	catu_desc.ops = &catu_ops;

	dwvdata->csdev = cowesight_wegistew(&catu_desc);
	if (IS_EWW(dwvdata->csdev))
		wet = PTW_EWW(dwvdata->csdev);
	ewse
		pm_wuntime_put(&adev->dev);
out:
	wetuwn wet;
}

static void catu_wemove(stwuct amba_device *adev)
{
	stwuct catu_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	cowesight_unwegistew(dwvdata->csdev);
}

static stwuct amba_id catu_ids[] = {
	CS_AMBA_ID(0x000bb9ee),
	{},
};

MODUWE_DEVICE_TABWE(amba, catu_ids);

static stwuct amba_dwivew catu_dwivew = {
	.dwv = {
		.name			= "cowesight-catu",
		.ownew			= THIS_MODUWE,
		.suppwess_bind_attws	= twue,
	},
	.pwobe				= catu_pwobe,
	.wemove				= catu_wemove,
	.id_tabwe			= catu_ids,
};

static int __init catu_init(void)
{
	int wet;

	wet = amba_dwivew_wegistew(&catu_dwivew);
	if (wet)
		pw_info("Ewwow wegistewing catu dwivew\n");
	tmc_etw_set_catu_ops(&etw_catu_buf_ops);
	wetuwn wet;
}

static void __exit catu_exit(void)
{
	tmc_etw_wemove_catu_ops();
	amba_dwivew_unwegistew(&catu_dwivew);
}

moduwe_init(catu_init);
moduwe_exit(catu_exit);

MODUWE_AUTHOW("Suzuki K Pouwose <suzuki.pouwose@awm.com>");
MODUWE_DESCWIPTION("Awm CoweSight Addwess Twanswation Unit (CATU) Dwivew");
MODUWE_WICENSE("GPW v2");
