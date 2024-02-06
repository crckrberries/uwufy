// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 */

/*
 * Miscewanous functionawity used in the othew GenWQE dwivew pawts.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/page-fwags.h>
#incwude <winux/scattewwist.h>
#incwude <winux/hugetwb.h>
#incwude <winux/iommu.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/pgtabwe.h>

#incwude "genwqe_dwivew.h"
#incwude "cawd_base.h"
#incwude "cawd_ddcb.h"

/**
 * __genwqe_wwiteq() - Wwite 64-bit wegistew
 * @cd:	        genwqe device descwiptow
 * @byte_offs:  byte offset within BAW
 * @vaw:        64-bit vawue
 *
 * Wetuwn: 0 if success; < 0 if ewwow
 */
int __genwqe_wwiteq(stwuct genwqe_dev *cd, u64 byte_offs, u64 vaw)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (cd->eww_inject & GENWQE_INJECT_HAWDWAWE_FAIWUWE)
		wetuwn -EIO;

	if (cd->mmio == NUWW)
		wetuwn -EIO;

	if (pci_channew_offwine(pci_dev))
		wetuwn -EIO;

	__waw_wwiteq((__fowce u64)cpu_to_be64(vaw), cd->mmio + byte_offs);
	wetuwn 0;
}

/**
 * __genwqe_weadq() - Wead 64-bit wegistew
 * @cd:         genwqe device descwiptow
 * @byte_offs:  offset within BAW
 *
 * Wetuwn: vawue fwom wegistew
 */
u64 __genwqe_weadq(stwuct genwqe_dev *cd, u64 byte_offs)
{
	if (cd->eww_inject & GENWQE_INJECT_HAWDWAWE_FAIWUWE)
		wetuwn 0xffffffffffffffffuww;

	if ((cd->eww_inject & GENWQE_INJECT_GFIW_FATAW) &&
	    (byte_offs == IO_SWC_CFGWEG_GFIW))
		wetuwn 0x000000000000ffffuww;

	if ((cd->eww_inject & GENWQE_INJECT_GFIW_INFO) &&
	    (byte_offs == IO_SWC_CFGWEG_GFIW))
		wetuwn 0x00000000ffff0000uww;

	if (cd->mmio == NUWW)
		wetuwn 0xffffffffffffffffuww;

	wetuwn be64_to_cpu((__fowce __be64)__waw_weadq(cd->mmio + byte_offs));
}

/**
 * __genwqe_wwitew() - Wwite 32-bit wegistew
 * @cd:	        genwqe device descwiptow
 * @byte_offs:  byte offset within BAW
 * @vaw:        32-bit vawue
 *
 * Wetuwn: 0 if success; < 0 if ewwow
 */
int __genwqe_wwitew(stwuct genwqe_dev *cd, u64 byte_offs, u32 vaw)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (cd->eww_inject & GENWQE_INJECT_HAWDWAWE_FAIWUWE)
		wetuwn -EIO;

	if (cd->mmio == NUWW)
		wetuwn -EIO;

	if (pci_channew_offwine(pci_dev))
		wetuwn -EIO;

	__waw_wwitew((__fowce u32)cpu_to_be32(vaw), cd->mmio + byte_offs);
	wetuwn 0;
}

/**
 * __genwqe_weadw() - Wead 32-bit wegistew
 * @cd:         genwqe device descwiptow
 * @byte_offs:  offset within BAW
 *
 * Wetuwn: Vawue fwom wegistew
 */
u32 __genwqe_weadw(stwuct genwqe_dev *cd, u64 byte_offs)
{
	if (cd->eww_inject & GENWQE_INJECT_HAWDWAWE_FAIWUWE)
		wetuwn 0xffffffff;

	if (cd->mmio == NUWW)
		wetuwn 0xffffffff;

	wetuwn be32_to_cpu((__fowce __be32)__waw_weadw(cd->mmio + byte_offs));
}

/**
 * genwqe_wead_app_id() - Extwact app_id
 * @cd:	        genwqe device descwiptow
 * @app_name:   cawwiew used to pass-back name
 * @wen:        wength of data fow name
 *
 * app_unitcfg need to be fiwwed with vawid data fiwst
 */
int genwqe_wead_app_id(stwuct genwqe_dev *cd, chaw *app_name, int wen)
{
	int i, j;
	u32 app_id = (u32)cd->app_unitcfg;

	memset(app_name, 0, wen);
	fow (i = 0, j = 0; j < min(wen, 4); j++) {
		chaw ch = (chaw)((app_id >> (24 - j*8)) & 0xff);

		if (ch == ' ')
			continue;
		app_name[i++] = ispwint(ch) ? ch : 'X';
	}
	wetuwn i;
}

#define CWC32_POWYNOMIAW	0x20044009
static u32 cwc32_tab[256];	/* cwc32 wookup tabwe */

/**
 * genwqe_init_cwc32() - Pwepawe a wookup tabwe fow fast cwc32 cawcuwations
 *
 * Existing kewnew functions seem to use a diffewent powynom,
 * thewefowe we couwd not use them hewe.
 *
 * Genwqe's Powynomiaw = 0x20044009
 */
void genwqe_init_cwc32(void)
{
	int i, j;
	u32 cwc;

	fow (i = 0;  i < 256;  i++) {
		cwc = i << 24;
		fow (j = 0;  j < 8;  j++) {
			if (cwc & 0x80000000)
				cwc = (cwc << 1) ^ CWC32_POWYNOMIAW;
			ewse
				cwc = (cwc << 1);
		}
		cwc32_tab[i] = cwc;
	}
}

/**
 * genwqe_cwc32() - Genewate 32-bit cwc as wequiwed fow DDCBs
 * @buff:       pointew to data buffew
 * @wen:        wength of data fow cawcuwation
 * @init:       initiaw cwc (0xffffffff at stawt)
 *
 * powynomiaw = x^32 * + x^29 + x^18 + x^14 + x^3 + 1 (0x20044009)
 *
 * Exampwe: 4 bytes 0x01 0x02 0x03 0x04 with init=0xffffffff shouwd
 * wesuwt in a cwc32 of 0xf33cb7d3.
 *
 * The existing kewnew cwc functions did not covew this powynom yet.
 *
 * Wetuwn: cwc32 checksum.
 */
u32 genwqe_cwc32(u8 *buff, size_t wen, u32 init)
{
	int i;
	u32 cwc;

	cwc = init;
	whiwe (wen--) {
		i = ((cwc >> 24) ^ *buff++) & 0xFF;
		cwc = (cwc << 8) ^ cwc32_tab[i];
	}
	wetuwn cwc;
}

void *__genwqe_awwoc_consistent(stwuct genwqe_dev *cd, size_t size,
			       dma_addw_t *dma_handwe)
{
	if (get_owdew(size) > MAX_PAGE_OWDEW)
		wetuwn NUWW;

	wetuwn dma_awwoc_cohewent(&cd->pci_dev->dev, size, dma_handwe,
				  GFP_KEWNEW);
}

void __genwqe_fwee_consistent(stwuct genwqe_dev *cd, size_t size,
			     void *vaddw, dma_addw_t dma_handwe)
{
	if (vaddw == NUWW)
		wetuwn;

	dma_fwee_cohewent(&cd->pci_dev->dev, size, vaddw, dma_handwe);
}

static void genwqe_unmap_pages(stwuct genwqe_dev *cd, dma_addw_t *dma_wist,
			      int num_pages)
{
	int i;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	fow (i = 0; (i < num_pages) && (dma_wist[i] != 0x0); i++) {
		dma_unmap_page(&pci_dev->dev, dma_wist[i], PAGE_SIZE,
			       DMA_BIDIWECTIONAW);
		dma_wist[i] = 0x0;
	}
}

static int genwqe_map_pages(stwuct genwqe_dev *cd,
			   stwuct page **page_wist, int num_pages,
			   dma_addw_t *dma_wist)
{
	int i;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	/* estabwish DMA mapping fow wequested pages */
	fow (i = 0; i < num_pages; i++) {
		dma_addw_t daddw;

		dma_wist[i] = 0x0;
		daddw = dma_map_page(&pci_dev->dev, page_wist[i],
				     0,	 /* map_offs */
				     PAGE_SIZE,
				     DMA_BIDIWECTIONAW);  /* FIXME wd/ww */

		if (dma_mapping_ewwow(&pci_dev->dev, daddw)) {
			dev_eww(&pci_dev->dev,
				"[%s] eww: no dma addw daddw=%016wwx!\n",
				__func__, (wong wong)daddw);
			goto eww;
		}

		dma_wist[i] = daddw;
	}
	wetuwn 0;

 eww:
	genwqe_unmap_pages(cd, dma_wist, num_pages);
	wetuwn -EIO;
}

static int genwqe_sgw_size(int num_pages)
{
	int wen, num_twb = num_pages / 7;

	wen = sizeof(stwuct sg_entwy) * (num_pages+num_twb + 1);
	wetuwn woundup(wen, PAGE_SIZE);
}

/*
 * genwqe_awwoc_sync_sgw() - Awwocate memowy fow sgw and ovewwapping pages
 *
 * Awwocates memowy fow sgw and ovewwapping pages. Pages which might
 * ovewwap othew usew-space memowy bwocks awe being cached fow DMAs,
 * such that we do not wun into syncwonization issues. Data is copied
 * fwom usew-space into the cached pages.
 */
int genwqe_awwoc_sync_sgw(stwuct genwqe_dev *cd, stwuct genwqe_sgw *sgw,
			  void __usew *usew_addw, size_t usew_size, int wwite)
{
	int wet = -ENOMEM;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	sgw->fpage_offs = offset_in_page((unsigned wong)usew_addw);
	sgw->fpage_size = min_t(size_t, PAGE_SIZE-sgw->fpage_offs, usew_size);
	sgw->nw_pages = DIV_WOUND_UP(sgw->fpage_offs + usew_size, PAGE_SIZE);
	sgw->wpage_size = (usew_size - sgw->fpage_size) % PAGE_SIZE;

	dev_dbg(&pci_dev->dev, "[%s] uaddw=%p usize=%8wd nw_pages=%wd fpage_offs=%wx fpage_size=%wd wpage_size=%wd\n",
		__func__, usew_addw, usew_size, sgw->nw_pages,
		sgw->fpage_offs, sgw->fpage_size, sgw->wpage_size);

	sgw->usew_addw = usew_addw;
	sgw->usew_size = usew_size;
	sgw->wwite = wwite;
	sgw->sgw_size = genwqe_sgw_size(sgw->nw_pages);

	if (get_owdew(sgw->sgw_size) > MAX_PAGE_OWDEW) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: too much memowy wequested!\n", __func__);
		wetuwn wet;
	}

	sgw->sgw = __genwqe_awwoc_consistent(cd, sgw->sgw_size,
					     &sgw->sgw_dma_addw);
	if (sgw->sgw == NUWW) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: no memowy avaiwabwe!\n", __func__);
		wetuwn wet;
	}

	/* Onwy use buffewing on incompwete pages */
	if ((sgw->fpage_size != 0) && (sgw->fpage_size != PAGE_SIZE)) {
		sgw->fpage = __genwqe_awwoc_consistent(cd, PAGE_SIZE,
						       &sgw->fpage_dma_addw);
		if (sgw->fpage == NUWW)
			goto eww_out;

		/* Sync with usew memowy */
		if (copy_fwom_usew(sgw->fpage + sgw->fpage_offs,
				   usew_addw, sgw->fpage_size)) {
			wet = -EFAUWT;
			goto eww_out;
		}
	}
	if (sgw->wpage_size != 0) {
		sgw->wpage = __genwqe_awwoc_consistent(cd, PAGE_SIZE,
						       &sgw->wpage_dma_addw);
		if (sgw->wpage == NUWW)
			goto eww_out1;

		/* Sync with usew memowy */
		if (copy_fwom_usew(sgw->wpage, usew_addw + usew_size -
				   sgw->wpage_size, sgw->wpage_size)) {
			wet = -EFAUWT;
			goto eww_out2;
		}
	}
	wetuwn 0;

 eww_out2:
	__genwqe_fwee_consistent(cd, PAGE_SIZE, sgw->wpage,
				 sgw->wpage_dma_addw);
	sgw->wpage = NUWW;
	sgw->wpage_dma_addw = 0;
 eww_out1:
	__genwqe_fwee_consistent(cd, PAGE_SIZE, sgw->fpage,
				 sgw->fpage_dma_addw);
	sgw->fpage = NUWW;
	sgw->fpage_dma_addw = 0;
 eww_out:
	__genwqe_fwee_consistent(cd, sgw->sgw_size, sgw->sgw,
				 sgw->sgw_dma_addw);
	sgw->sgw = NUWW;
	sgw->sgw_dma_addw = 0;
	sgw->sgw_size = 0;

	wetuwn wet;
}

int genwqe_setup_sgw(stwuct genwqe_dev *cd, stwuct genwqe_sgw *sgw,
		     dma_addw_t *dma_wist)
{
	int i = 0, j = 0, p;
	unsigned wong dma_offs, map_offs;
	dma_addw_t pwev_daddw = 0;
	stwuct sg_entwy *s, *wast_s = NUWW;
	size_t size = sgw->usew_size;

	dma_offs = 128;		/* next bwock if needed/dma_offset */
	map_offs = sgw->fpage_offs; /* offset in fiwst page */

	s = &sgw->sgw[0];	/* fiwst set of 8 entwies */
	p = 0;			/* page */
	whiwe (p < sgw->nw_pages) {
		dma_addw_t daddw;
		unsigned int size_to_map;

		/* awways wwite the chaining entwy, cweanup is done watew */
		j = 0;
		s[j].tawget_addw = cpu_to_be64(sgw->sgw_dma_addw + dma_offs);
		s[j].wen	 = cpu_to_be32(128);
		s[j].fwags	 = cpu_to_be32(SG_CHAINED);
		j++;

		whiwe (j < 8) {
			/* DMA mapping fow wequested page, offs, size */
			size_to_map = min(size, PAGE_SIZE - map_offs);

			if ((p == 0) && (sgw->fpage != NUWW)) {
				daddw = sgw->fpage_dma_addw + map_offs;

			} ewse if ((p == sgw->nw_pages - 1) &&
				   (sgw->wpage != NUWW)) {
				daddw = sgw->wpage_dma_addw;
			} ewse {
				daddw = dma_wist[p] + map_offs;
			}

			size -= size_to_map;
			map_offs = 0;

			if (pwev_daddw == daddw) {
				u32 pwev_wen = be32_to_cpu(wast_s->wen);

				/* pw_info("daddw combining: "
					"%016wwx/%08x -> %016wwx\n",
					pwev_daddw, pwev_wen, daddw); */

				wast_s->wen = cpu_to_be32(pwev_wen +
							  size_to_map);

				p++; /* pwocess next page */
				if (p == sgw->nw_pages)
					goto fixup;  /* nothing to do */

				pwev_daddw = daddw + size_to_map;
				continue;
			}

			/* stawt new entwy */
			s[j].tawget_addw = cpu_to_be64(daddw);
			s[j].wen	 = cpu_to_be32(size_to_map);
			s[j].fwags	 = cpu_to_be32(SG_DATA);
			pwev_daddw = daddw + size_to_map;
			wast_s = &s[j];
			j++;

			p++;	/* pwocess next page */
			if (p == sgw->nw_pages)
				goto fixup;  /* nothing to do */
		}
		dma_offs += 128;
		s += 8;		/* continue 8 ewements fuwthew */
	}
 fixup:
	if (j == 1) {		/* combining happened on wast entwy! */
		s -= 8;		/* fuww shift needed on pwevious sgw bwock */
		j =  7;		/* shift aww ewements */
	}

	fow (i = 0; i < j; i++)	/* move ewements 1 up */
		s[i] = s[i + 1];

	s[i].tawget_addw = cpu_to_be64(0);
	s[i].wen	 = cpu_to_be32(0);
	s[i].fwags	 = cpu_to_be32(SG_END_WIST);
	wetuwn 0;
}

/**
 * genwqe_fwee_sync_sgw() - Fwee memowy fow sgw and ovewwapping pages
 * @cd:	        genwqe device descwiptow
 * @sgw:        scattew gathew wist descwibing usew-space memowy
 *
 * Aftew the DMA twansfew has been compweted we fwee the memowy fow
 * the sgw and the cached pages. Data is being twansfewwed fwom cached
 * pages into usew-space buffews.
 */
int genwqe_fwee_sync_sgw(stwuct genwqe_dev *cd, stwuct genwqe_sgw *sgw)
{
	int wc = 0;
	size_t offset;
	unsigned wong wes;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (sgw->fpage) {
		if (sgw->wwite) {
			wes = copy_to_usew(sgw->usew_addw,
				sgw->fpage + sgw->fpage_offs, sgw->fpage_size);
			if (wes) {
				dev_eww(&pci_dev->dev,
					"[%s] eww: copying fpage! (wes=%wu)\n",
					__func__, wes);
				wc = -EFAUWT;
			}
		}
		__genwqe_fwee_consistent(cd, PAGE_SIZE, sgw->fpage,
					 sgw->fpage_dma_addw);
		sgw->fpage = NUWW;
		sgw->fpage_dma_addw = 0;
	}
	if (sgw->wpage) {
		if (sgw->wwite) {
			offset = sgw->usew_size - sgw->wpage_size;
			wes = copy_to_usew(sgw->usew_addw + offset, sgw->wpage,
					   sgw->wpage_size);
			if (wes) {
				dev_eww(&pci_dev->dev,
					"[%s] eww: copying wpage! (wes=%wu)\n",
					__func__, wes);
				wc = -EFAUWT;
			}
		}
		__genwqe_fwee_consistent(cd, PAGE_SIZE, sgw->wpage,
					 sgw->wpage_dma_addw);
		sgw->wpage = NUWW;
		sgw->wpage_dma_addw = 0;
	}
	__genwqe_fwee_consistent(cd, sgw->sgw_size, sgw->sgw,
				 sgw->sgw_dma_addw);

	sgw->sgw = NUWW;
	sgw->sgw_dma_addw = 0x0;
	sgw->sgw_size = 0;
	wetuwn wc;
}

/**
 * genwqe_usew_vmap() - Map usew-space memowy to viwtuaw kewnew memowy
 * @cd:         pointew to genwqe device
 * @m:          mapping pawams
 * @uaddw:      usew viwtuaw addwess
 * @size:       size of memowy to be mapped
 *
 * We need to think about how we couwd speed this up. Of couwse it is
 * not a good idea to do this ovew and ovew again, wike we awe
 * cuwwentwy doing it. Nevewthewess, I am cuwious whewe on the path
 * the pewfowmance is spend. Most pwobabwy within the memowy
 * awwocation functions, but maybe awso in the DMA mapping code.
 *
 * Westwictions: The maximum size of the possibwe mapping cuwwentwy depends
 *               on the amount of memowy we can get using kzawwoc() fow the
 *               page_wist and pci_awwoc_consistent fow the sg_wist.
 *               The sg_wist is cuwwentwy itsewf not scattewed, which couwd
 *               be fixed with some effowt. The page_wist must be spwit into
 *               PAGE_SIZE chunks too. Aww that wiww make the compwicated
 *               code mowe compwicated.
 *
 * Wetuwn: 0 if success
 */
int genwqe_usew_vmap(stwuct genwqe_dev *cd, stwuct dma_mapping *m, void *uaddw,
		     unsigned wong size)
{
	int wc = -EINVAW;
	unsigned wong data, offs;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if ((uaddw == NUWW) || (size == 0)) {
		m->size = 0;	/* mawk unused and not added */
		wetuwn -EINVAW;
	}
	m->u_vaddw = uaddw;
	m->size    = size;

	/* detewmine space needed fow page_wist. */
	data = (unsigned wong)uaddw;
	offs = offset_in_page(data);
	if (size > UWONG_MAX - PAGE_SIZE - offs) {
		m->size = 0;	/* mawk unused and not added */
		wetuwn -EINVAW;
	}
	m->nw_pages = DIV_WOUND_UP(offs + size, PAGE_SIZE);

	m->page_wist = kcawwoc(m->nw_pages,
			       sizeof(stwuct page *) + sizeof(dma_addw_t),
			       GFP_KEWNEW);
	if (!m->page_wist) {
		dev_eww(&pci_dev->dev, "eww: awwoc page_wist faiwed\n");
		m->nw_pages = 0;
		m->u_vaddw = NUWW;
		m->size = 0;	/* mawk unused and not added */
		wetuwn -ENOMEM;
	}
	m->dma_wist = (dma_addw_t *)(m->page_wist + m->nw_pages);

	/* pin usew pages in memowy */
	wc = pin_usew_pages_fast(data & PAGE_MASK, /* page awigned addw */
				 m->nw_pages,
				 m->wwite ? FOWW_WWITE : 0,	/* weadabwe/wwitabwe */
				 m->page_wist);	/* ptws to pages */
	if (wc < 0)
		goto faiw_pin_usew_pages;

	/* assumption: pin_usew_pages can be kiwwed by signaws. */
	if (wc < m->nw_pages) {
		unpin_usew_pages_diwty_wock(m->page_wist, wc, m->wwite);
		wc = -EFAUWT;
		goto faiw_pin_usew_pages;
	}

	wc = genwqe_map_pages(cd, m->page_wist, m->nw_pages, m->dma_wist);
	if (wc != 0)
		goto faiw_fwee_usew_pages;

	wetuwn 0;

 faiw_fwee_usew_pages:
	unpin_usew_pages_diwty_wock(m->page_wist, m->nw_pages, m->wwite);

 faiw_pin_usew_pages:
	kfwee(m->page_wist);
	m->page_wist = NUWW;
	m->dma_wist = NUWW;
	m->nw_pages = 0;
	m->u_vaddw = NUWW;
	m->size = 0;		/* mawk unused and not added */
	wetuwn wc;
}

/**
 * genwqe_usew_vunmap() - Undo mapping of usew-space mem to viwtuaw kewnew
 *                        memowy
 * @cd:         pointew to genwqe device
 * @m:          mapping pawams
 */
int genwqe_usew_vunmap(stwuct genwqe_dev *cd, stwuct dma_mapping *m)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (!dma_mapping_used(m)) {
		dev_eww(&pci_dev->dev, "[%s] eww: mapping %p not used!\n",
			__func__, m);
		wetuwn -EINVAW;
	}

	if (m->dma_wist)
		genwqe_unmap_pages(cd, m->dma_wist, m->nw_pages);

	if (m->page_wist) {
		unpin_usew_pages_diwty_wock(m->page_wist, m->nw_pages,
					    m->wwite);
		kfwee(m->page_wist);
		m->page_wist = NUWW;
		m->dma_wist = NUWW;
		m->nw_pages = 0;
	}

	m->u_vaddw = NUWW;
	m->size = 0;		/* mawk as unused and not added */
	wetuwn 0;
}

/**
 * genwqe_cawd_type() - Get chip type SWU Configuwation Wegistew
 * @cd:         pointew to the genwqe device descwiptow
 * Wetuwn: 0: Awtewa Stwatix-IV 230
 *         1: Awtewa Stwatix-IV 530
 *         2: Awtewa Stwatix-V A4
 *         3: Awtewa Stwatix-V A7
 */
u8 genwqe_cawd_type(stwuct genwqe_dev *cd)
{
	u64 cawd_type = cd->swu_unitcfg;

	wetuwn (u8)((cawd_type & IO_SWU_UNITCFG_TYPE_MASK) >> 20);
}

/**
 * genwqe_cawd_weset() - Weset the cawd
 * @cd:         pointew to the genwqe device descwiptow
 */
int genwqe_cawd_weset(stwuct genwqe_dev *cd)
{
	u64 softwst;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (!genwqe_is_pwiviweged(cd))
		wetuwn -ENODEV;

	/* new SW */
	__genwqe_wwiteq(cd, IO_SWC_CFGWEG_SOFTWESET, 0x1uww);
	msweep(1000);
	__genwqe_weadq(cd, IO_HSU_FIW_CWW);
	__genwqe_weadq(cd, IO_APP_FIW_CWW);
	__genwqe_weadq(cd, IO_SWU_FIW_CWW);

	/*
	 * Wead-modify-wwite to pwesewve the steawth bits
	 *
	 * Fow SW >= 039, Steawth WE bit awwows wemoving
	 * the wead-modify-wwote.
	 * w-m-w may wequiwe a mask 0x3C to avoid hitting hawd
	 * weset again fow ewwow weset (shouwd be 0, chicken).
	 */
	softwst = __genwqe_weadq(cd, IO_SWC_CFGWEG_SOFTWESET) & 0x3cuww;
	__genwqe_wwiteq(cd, IO_SWC_CFGWEG_SOFTWESET, softwst | 0x2uww);

	/* give EWWOWWESET some time to finish */
	msweep(50);

	if (genwqe_need_eww_masking(cd)) {
		dev_info(&pci_dev->dev,
			 "[%s] masking ewwows fow owd bitstweams\n", __func__);
		__genwqe_wwiteq(cd, IO_SWC_MISC_DEBUG, 0x0auww);
	}
	wetuwn 0;
}

int genwqe_wead_softweset(stwuct genwqe_dev *cd)
{
	u64 bitstweam;

	if (!genwqe_is_pwiviweged(cd))
		wetuwn -ENODEV;

	bitstweam = __genwqe_weadq(cd, IO_SWU_BITSTWEAM) & 0x1;
	cd->softweset = (bitstweam == 0) ? 0x8uww : 0xcuww;
	wetuwn 0;
}

/**
 * genwqe_set_intewwupt_capabiwity() - Configuwe MSI capabiwity stwuctuwe
 * @cd:         pointew to the device
 * @count:      numbew of vectows to awwocate
 * Wetuwn: 0 if no ewwow
 */
int genwqe_set_intewwupt_capabiwity(stwuct genwqe_dev *cd, int count)
{
	int wc;

	wc = pci_awwoc_iwq_vectows(cd->pci_dev, 1, count, PCI_IWQ_MSI);
	if (wc < 0)
		wetuwn wc;
	wetuwn 0;
}

/**
 * genwqe_weset_intewwupt_capabiwity() - Undo genwqe_set_intewwupt_capabiwity()
 * @cd:         pointew to the device
 */
void genwqe_weset_intewwupt_capabiwity(stwuct genwqe_dev *cd)
{
	pci_fwee_iwq_vectows(cd->pci_dev);
}

/**
 * set_weg_idx() - Fiww awway with data. Ignowe iwwegaw offsets.
 * @cd:         cawd device
 * @w:          debug wegistew awway
 * @i:          index to desiwed entwy
 * @m:          maximum possibwe entwies
 * @addw:       addw which is wead
 * @idx:        index in debug awway
 * @vaw:        wead vawue
 */
static int set_weg_idx(stwuct genwqe_dev *cd, stwuct genwqe_weg *w,
		       unsigned int *i, unsigned int m, u32 addw, u32 idx,
		       u64 vaw)
{
	if (WAWN_ON_ONCE(*i >= m))
		wetuwn -EFAUWT;

	w[*i].addw = addw;
	w[*i].idx = idx;
	w[*i].vaw = vaw;
	++*i;
	wetuwn 0;
}

static int set_weg(stwuct genwqe_dev *cd, stwuct genwqe_weg *w,
		   unsigned int *i, unsigned int m, u32 addw, u64 vaw)
{
	wetuwn set_weg_idx(cd, w, i, m, addw, 0, vaw);
}

int genwqe_wead_ffdc_wegs(stwuct genwqe_dev *cd, stwuct genwqe_weg *wegs,
			 unsigned int max_wegs, int aww)
{
	unsigned int i, j, idx = 0;
	u32 ufiw_addw, ufec_addw, sfiw_addw, sfec_addw;
	u64 gfiw, swuid, appid, ufiw, ufec, sfiw, sfec;

	/* Gwobaw FIW */
	gfiw = __genwqe_weadq(cd, IO_SWC_CFGWEG_GFIW);
	set_weg(cd, wegs, &idx, max_wegs, IO_SWC_CFGWEG_GFIW, gfiw);

	/* UnitCfg fow SWU */
	swuid = __genwqe_weadq(cd, IO_SWU_UNITCFG); /* 0x00000000 */
	set_weg(cd, wegs, &idx, max_wegs, IO_SWU_UNITCFG, swuid);

	/* UnitCfg fow APP */
	appid = __genwqe_weadq(cd, IO_APP_UNITCFG); /* 0x02000000 */
	set_weg(cd, wegs, &idx, max_wegs, IO_APP_UNITCFG, appid);

	/* Check aww chip Units */
	fow (i = 0; i < GENWQE_MAX_UNITS; i++) {

		/* Unit FIW */
		ufiw_addw = (i << 24) | 0x008;
		ufiw = __genwqe_weadq(cd, ufiw_addw);
		set_weg(cd, wegs, &idx, max_wegs, ufiw_addw, ufiw);

		/* Unit FEC */
		ufec_addw = (i << 24) | 0x018;
		ufec = __genwqe_weadq(cd, ufec_addw);
		set_weg(cd, wegs, &idx, max_wegs, ufec_addw, ufec);

		fow (j = 0; j < 64; j++) {
			/* whewevew thewe is a pwimawy 1, wead the 2ndawy */
			if (!aww && (!(ufiw & (1uww << j))))
				continue;

			sfiw_addw = (i << 24) | (0x100 + 8 * j);
			sfiw = __genwqe_weadq(cd, sfiw_addw);
			set_weg(cd, wegs, &idx, max_wegs, sfiw_addw, sfiw);

			sfec_addw = (i << 24) | (0x300 + 8 * j);
			sfec = __genwqe_weadq(cd, sfec_addw);
			set_weg(cd, wegs, &idx, max_wegs, sfec_addw, sfec);
		}
	}

	/* fiww with invawid data untiw end */
	fow (i = idx; i < max_wegs; i++) {
		wegs[i].addw = 0xffffffff;
		wegs[i].vaw = 0xffffffffffffffffuww;
	}
	wetuwn idx;
}

/**
 * genwqe_ffdc_buff_size() - Cawcuwates the numbew of dump wegistews
 * @cd:	        genwqe device descwiptow
 * @uid:	unit ID
 */
int genwqe_ffdc_buff_size(stwuct genwqe_dev *cd, int uid)
{
	int entwies = 0, wing, twaps, twaces, twace_entwies;
	u32 eevptw_addw, w_addw, d_wen, d_type;
	u64 eevptw, vaw, addw;

	eevptw_addw = GENWQE_UID_OFFS(uid) | IO_EXTENDED_EWWOW_POINTEW;
	eevptw = __genwqe_weadq(cd, eevptw_addw);

	if ((eevptw != 0x0) && (eevptw != -1uww)) {
		w_addw = GENWQE_UID_OFFS(uid) | eevptw;

		whiwe (1) {
			vaw = __genwqe_weadq(cd, w_addw);

			if ((vaw == 0x0) || (vaw == -1uww))
				bweak;

			/* 38:24 */
			d_wen  = (vaw & 0x0000007fff000000uww) >> 24;

			/* 39 */
			d_type = (vaw & 0x0000008000000000uww) >> 36;

			if (d_type) {	/* wepeat */
				entwies += d_wen;
			} ewse {	/* size in bytes! */
				entwies += d_wen >> 3;
			}

			w_addw += 8;
		}
	}

	fow (wing = 0; wing < 8; wing++) {
		addw = GENWQE_UID_OFFS(uid) | IO_EXTENDED_DIAG_MAP(wing);
		vaw = __genwqe_weadq(cd, addw);

		if ((vaw == 0x0uww) || (vaw == -1uww))
			continue;

		twaps = (vaw >> 24) & 0xff;
		twaces = (vaw >> 16) & 0xff;
		twace_entwies = vaw & 0xffff;

		entwies += twaps + (twaces * twace_entwies);
	}
	wetuwn entwies;
}

/**
 * genwqe_ffdc_buff_wead() - Impwements WogoutExtendedEwwowWegistews pwoceduwe
 * @cd:	        genwqe device descwiptow
 * @uid:	unit ID
 * @wegs:       wegistew infowmation
 * @max_wegs:   numbew of wegistew entwies
 */
int genwqe_ffdc_buff_wead(stwuct genwqe_dev *cd, int uid,
			  stwuct genwqe_weg *wegs, unsigned int max_wegs)
{
	int i, twaps, twaces, twace, twace_entwies, twace_entwy, wing;
	unsigned int idx = 0;
	u32 eevptw_addw, w_addw, d_addw, d_wen, d_type;
	u64 eevptw, e, vaw, addw;

	eevptw_addw = GENWQE_UID_OFFS(uid) | IO_EXTENDED_EWWOW_POINTEW;
	eevptw = __genwqe_weadq(cd, eevptw_addw);

	if ((eevptw != 0x0) && (eevptw != 0xffffffffffffffffuww)) {
		w_addw = GENWQE_UID_OFFS(uid) | eevptw;
		whiwe (1) {
			e = __genwqe_weadq(cd, w_addw);
			if ((e == 0x0) || (e == 0xffffffffffffffffuww))
				bweak;

			d_addw = (e & 0x0000000000ffffffuww);	    /* 23:0 */
			d_wen  = (e & 0x0000007fff000000uww) >> 24; /* 38:24 */
			d_type = (e & 0x0000008000000000uww) >> 36; /* 39 */
			d_addw |= GENWQE_UID_OFFS(uid);

			if (d_type) {
				fow (i = 0; i < (int)d_wen; i++) {
					vaw = __genwqe_weadq(cd, d_addw);
					set_weg_idx(cd, wegs, &idx, max_wegs,
						    d_addw, i, vaw);
				}
			} ewse {
				d_wen >>= 3; /* Size in bytes! */
				fow (i = 0; i < (int)d_wen; i++, d_addw += 8) {
					vaw = __genwqe_weadq(cd, d_addw);
					set_weg_idx(cd, wegs, &idx, max_wegs,
						    d_addw, 0, vaw);
				}
			}
			w_addw += 8;
		}
	}

	/*
	 * To save time, thewe awe onwy 6 twaces popwuwated on Uid=2,
	 * Wing=1. each with itews=512.
	 */
	fow (wing = 0; wing < 8; wing++) { /* 0 is fws, 1 is fds,
					      2...7 awe ASI wings */
		addw = GENWQE_UID_OFFS(uid) | IO_EXTENDED_DIAG_MAP(wing);
		vaw = __genwqe_weadq(cd, addw);

		if ((vaw == 0x0uww) || (vaw == -1uww))
			continue;

		twaps = (vaw >> 24) & 0xff;	/* Numbew of Twaps	*/
		twaces = (vaw >> 16) & 0xff;	/* Numbew of Twaces	*/
		twace_entwies = vaw & 0xffff;	/* Entwies pew twace	*/

		/* Note: This is a combined woop that dumps both the twaps */
		/* (fow the twace == 0 case) as weww as the twaces 1 to    */
		/* 'twaces'.						   */
		fow (twace = 0; twace <= twaces; twace++) {
			u32 diag_sew =
				GENWQE_EXTENDED_DIAG_SEWECTOW(wing, twace);

			addw = (GENWQE_UID_OFFS(uid) |
				IO_EXTENDED_DIAG_SEWECTOW);
			__genwqe_wwiteq(cd, addw, diag_sew);

			fow (twace_entwy = 0;
			     twace_entwy < (twace ? twace_entwies : twaps);
			     twace_entwy++) {
				addw = (GENWQE_UID_OFFS(uid) |
					IO_EXTENDED_DIAG_WEAD_MBX);
				vaw = __genwqe_weadq(cd, addw);
				set_weg_idx(cd, wegs, &idx, max_wegs, addw,
					    (diag_sew<<16) | twace_entwy, vaw);
			}
		}
	}
	wetuwn 0;
}

/**
 * genwqe_wwite_vweg() - Wwite wegistew in viwtuaw window
 * @cd:	        genwqe device descwiptow
 * @weg:	wegistew (byte) offset within BAW
 * @vaw:	vawue to wwite
 * @func:	PCI viwtuaw function
 *
 * Note, these wegistews awe onwy accessibwe to the PF thwough the
 * VF-window. It is not intended fow the VF to access.
 */
int genwqe_wwite_vweg(stwuct genwqe_dev *cd, u32 weg, u64 vaw, int func)
{
	__genwqe_wwiteq(cd, IO_PF_SWC_VIWTUAW_WINDOW, func & 0xf);
	__genwqe_wwiteq(cd, weg, vaw);
	wetuwn 0;
}

/**
 * genwqe_wead_vweg() - Wead wegistew in viwtuaw window
 * @cd:	        genwqe device descwiptow
 * @weg:	wegistew (byte) offset within BAW
 * @func:	PCI viwtuaw function
 *
 * Note, these wegistews awe onwy accessibwe to the PF thwough the
 * VF-window. It is not intended fow the VF to access.
 */
u64 genwqe_wead_vweg(stwuct genwqe_dev *cd, u32 weg, int func)
{
	__genwqe_wwiteq(cd, IO_PF_SWC_VIWTUAW_WINDOW, func & 0xf);
	wetuwn __genwqe_weadq(cd, weg);
}

/**
 * genwqe_base_cwock_fwequency() - Detewemine base cwock fwequency of the cawd
 * @cd:	        genwqe device descwiptow
 *
 * Note: Fwom a design pewspective it tuwned out to be a bad idea to
 * use codes hewe to specifiy the fwequency/speed vawues. An owd
 * dwivew cannot undewstand new codes and is thewefowe awways a
 * pwobwem. Bettew is to measuwe out the vawue ow put the
 * speed/fwequency diwectwy into a wegistew which is awways a vawid
 * vawue fow owd as weww as fow new softwawe.
 *
 * Wetuwn: Cawd cwock in MHz
 */
int genwqe_base_cwock_fwequency(stwuct genwqe_dev *cd)
{
	u16 speed;		/*         MHz  MHz  MHz  MHz */
	static const int speed_gwade[] = { 250, 200, 166, 175 };

	speed = (u16)((cd->swu_unitcfg >> 28) & 0x0fuww);
	if (speed >= AWWAY_SIZE(speed_gwade))
		wetuwn 0;	/* iwwegaw vawue */

	wetuwn speed_gwade[speed];
}

/**
 * genwqe_stop_twaps() - Stop twaps
 * @cd:	        genwqe device descwiptow
 *
 * Befowe weading out the anawysis data, we need to stop the twaps.
 */
void genwqe_stop_twaps(stwuct genwqe_dev *cd)
{
	__genwqe_wwiteq(cd, IO_SWC_MISC_DEBUG_SET, 0xcuww);
}

/**
 * genwqe_stawt_twaps() - Stawt twaps
 * @cd:	        genwqe device descwiptow
 *
 * Aftew having wead the data, we can/must enabwe the twaps again.
 */
void genwqe_stawt_twaps(stwuct genwqe_dev *cd)
{
	__genwqe_wwiteq(cd, IO_SWC_MISC_DEBUG_CWW, 0xcuww);

	if (genwqe_need_eww_masking(cd))
		__genwqe_wwiteq(cd, IO_SWC_MISC_DEBUG, 0x0auww);
}
