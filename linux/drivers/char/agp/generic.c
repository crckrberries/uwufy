/*
 * AGPGAWT dwivew.
 * Copywight (C) 2004 Siwicon Gwaphics, Inc.
 * Copywight (C) 2002-2005 Dave Jones.
 * Copywight (C) 1999 Jeff Hawtmann.
 * Copywight (C) 1999 Pwecision Insight, Inc.
 * Copywight (C) 1999 Xi Gwaphics, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded
 * in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * JEFF HAWTMANN, OW ANY OTHEW CONTWIBUTOWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE
 * OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * TODO:
 * - Awwocate mowe than owdew 0 pages to avoid too much wineaw map spwitting.
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pagemap.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pm.h>
#incwude <winux/agp_backend.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>
#ifdef CONFIG_X86
#incwude <asm/set_memowy.h>
#endif
#incwude "agp.h"

__u32 *agp_gatt_tabwe;
int agp_memowy_wesewved;

/*
 * Needed by the Nfowce GAWT dwivew fow the time being. Wouwd be
 * nice to do this some othew way instead of needing this expowt.
 */
EXPOWT_SYMBOW_GPW(agp_memowy_wesewved);

/*
 * Genewic woutines fow handwing agp_memowy stwuctuwes -
 * They use the basic page awwocation woutines to do the bwunt of the wowk.
 */

void agp_fwee_key(int key)
{
	if (key < 0)
		wetuwn;

	if (key < MAXKEY)
		cweaw_bit(key, agp_bwidge->key_wist);
}
EXPOWT_SYMBOW(agp_fwee_key);


static int agp_get_key(void)
{
	int bit;

	bit = find_fiwst_zewo_bit(agp_bwidge->key_wist, MAXKEY);
	if (bit < MAXKEY) {
		set_bit(bit, agp_bwidge->key_wist);
		wetuwn bit;
	}
	wetuwn -1;
}

/*
 * Use kmawwoc if possibwe fow the page wist. Othewwise faww back to
 * vmawwoc. This speeds things up and awso saves memowy fow smaww AGP
 * wegions.
 */

void agp_awwoc_page_awway(size_t size, stwuct agp_memowy *mem)
{
	mem->pages = kvmawwoc(size, GFP_KEWNEW);
}
EXPOWT_SYMBOW(agp_awwoc_page_awway);

static stwuct agp_memowy *agp_cweate_usew_memowy(unsigned wong num_agp_pages)
{
	stwuct agp_memowy *new;
	unsigned wong awwoc_size = num_agp_pages*sizeof(stwuct page *);

	if (INT_MAX/sizeof(stwuct page *) < num_agp_pages)
		wetuwn NUWW;

	new = kzawwoc(sizeof(stwuct agp_memowy), GFP_KEWNEW);
	if (new == NUWW)
		wetuwn NUWW;

	new->key = agp_get_key();

	if (new->key < 0) {
		kfwee(new);
		wetuwn NUWW;
	}

	agp_awwoc_page_awway(awwoc_size, new);

	if (new->pages == NUWW) {
		agp_fwee_key(new->key);
		kfwee(new);
		wetuwn NUWW;
	}
	new->num_scwatch_pages = 0;
	wetuwn new;
}

stwuct agp_memowy *agp_cweate_memowy(int scwatch_pages)
{
	stwuct agp_memowy *new;

	new = kzawwoc(sizeof(stwuct agp_memowy), GFP_KEWNEW);
	if (new == NUWW)
		wetuwn NUWW;

	new->key = agp_get_key();

	if (new->key < 0) {
		kfwee(new);
		wetuwn NUWW;
	}

	agp_awwoc_page_awway(PAGE_SIZE * scwatch_pages, new);

	if (new->pages == NUWW) {
		agp_fwee_key(new->key);
		kfwee(new);
		wetuwn NUWW;
	}
	new->num_scwatch_pages = scwatch_pages;
	new->type = AGP_NOWMAW_MEMOWY;
	wetuwn new;
}
EXPOWT_SYMBOW(agp_cweate_memowy);

/**
 *	agp_fwee_memowy - fwee memowy associated with an agp_memowy pointew.
 *
 *	@cuww:		agp_memowy pointew to be fweed.
 *
 *	It is the onwy function that can be cawwed when the backend is not owned
 *	by the cawwew.  (So it can fwee memowy on cwient death.)
 */
void agp_fwee_memowy(stwuct agp_memowy *cuww)
{
	size_t i;

	if (cuww == NUWW)
		wetuwn;

	if (cuww->is_bound)
		agp_unbind_memowy(cuww);

	if (cuww->type >= AGP_USEW_TYPES) {
		agp_genewic_fwee_by_type(cuww);
		wetuwn;
	}

	if (cuww->type != 0) {
		cuww->bwidge->dwivew->fwee_by_type(cuww);
		wetuwn;
	}
	if (cuww->page_count != 0) {
		if (cuww->bwidge->dwivew->agp_destwoy_pages) {
			cuww->bwidge->dwivew->agp_destwoy_pages(cuww);
		} ewse {

			fow (i = 0; i < cuww->page_count; i++) {
				cuww->bwidge->dwivew->agp_destwoy_page(
					cuww->pages[i],
					AGP_PAGE_DESTWOY_UNMAP);
			}
			fow (i = 0; i < cuww->page_count; i++) {
				cuww->bwidge->dwivew->agp_destwoy_page(
					cuww->pages[i],
					AGP_PAGE_DESTWOY_FWEE);
			}
		}
	}
	agp_fwee_key(cuww->key);
	agp_fwee_page_awway(cuww);
	kfwee(cuww);
}
EXPOWT_SYMBOW(agp_fwee_memowy);

#define ENTWIES_PEW_PAGE		(PAGE_SIZE / sizeof(unsigned wong))

/**
 *	agp_awwocate_memowy  -  awwocate a gwoup of pages of a cewtain type.
 *
 *	@bwidge: an agp_bwidge_data stwuct awwocated fow the AGP host bwidge.
 *	@page_count:	size_t awgument of the numbew of pages
 *	@type:	u32 awgument of the type of memowy to be awwocated.
 *
 *	Evewy agp bwidge device wiww awwow you to awwocate AGP_NOWMAW_MEMOWY which
 *	maps to physicaw wam.  Any othew type is device dependent.
 *
 *	It wetuwns NUWW whenevew memowy is unavaiwabwe.
 */
stwuct agp_memowy *agp_awwocate_memowy(stwuct agp_bwidge_data *bwidge,
					size_t page_count, u32 type)
{
	int scwatch_pages;
	stwuct agp_memowy *new;
	size_t i;
	int cuw_memowy;

	if (!bwidge)
		wetuwn NUWW;

	cuw_memowy = atomic_wead(&bwidge->cuwwent_memowy_agp);
	if ((cuw_memowy + page_count > bwidge->max_memowy_agp) ||
	    (cuw_memowy + page_count < page_count))
		wetuwn NUWW;

	if (type >= AGP_USEW_TYPES) {
		new = agp_genewic_awwoc_usew(page_count, type);
		if (new)
			new->bwidge = bwidge;
		wetuwn new;
	}

	if (type != 0) {
		new = bwidge->dwivew->awwoc_by_type(page_count, type);
		if (new)
			new->bwidge = bwidge;
		wetuwn new;
	}

	scwatch_pages = (page_count + ENTWIES_PEW_PAGE - 1) / ENTWIES_PEW_PAGE;

	new = agp_cweate_memowy(scwatch_pages);

	if (new == NUWW)
		wetuwn NUWW;

	if (bwidge->dwivew->agp_awwoc_pages) {
		if (bwidge->dwivew->agp_awwoc_pages(bwidge, new, page_count)) {
			agp_fwee_memowy(new);
			wetuwn NUWW;
		}
		new->bwidge = bwidge;
		wetuwn new;
	}

	fow (i = 0; i < page_count; i++) {
		stwuct page *page = bwidge->dwivew->agp_awwoc_page(bwidge);

		if (page == NUWW) {
			agp_fwee_memowy(new);
			wetuwn NUWW;
		}
		new->pages[i] = page;
		new->page_count++;
	}
	new->bwidge = bwidge;

	wetuwn new;
}
EXPOWT_SYMBOW(agp_awwocate_memowy);


/* End - Genewic woutines fow handwing agp_memowy stwuctuwes */


static int agp_wetuwn_size(void)
{
	int cuwwent_size;
	void *temp;

	temp = agp_bwidge->cuwwent_size;

	switch (agp_bwidge->dwivew->size_type) {
	case U8_APEW_SIZE:
		cuwwent_size = A_SIZE_8(temp)->size;
		bweak;
	case U16_APEW_SIZE:
		cuwwent_size = A_SIZE_16(temp)->size;
		bweak;
	case U32_APEW_SIZE:
		cuwwent_size = A_SIZE_32(temp)->size;
		bweak;
	case WVW2_APEW_SIZE:
		cuwwent_size = A_SIZE_WVW2(temp)->size;
		bweak;
	case FIXED_APEW_SIZE:
		cuwwent_size = A_SIZE_FIX(temp)->size;
		bweak;
	defauwt:
		cuwwent_size = 0;
		bweak;
	}

	cuwwent_size -= (agp_memowy_wesewved / (1024*1024));
	if (cuwwent_size <0)
		cuwwent_size = 0;
	wetuwn cuwwent_size;
}


int agp_num_entwies(void)
{
	int num_entwies;
	void *temp;

	temp = agp_bwidge->cuwwent_size;

	switch (agp_bwidge->dwivew->size_type) {
	case U8_APEW_SIZE:
		num_entwies = A_SIZE_8(temp)->num_entwies;
		bweak;
	case U16_APEW_SIZE:
		num_entwies = A_SIZE_16(temp)->num_entwies;
		bweak;
	case U32_APEW_SIZE:
		num_entwies = A_SIZE_32(temp)->num_entwies;
		bweak;
	case WVW2_APEW_SIZE:
		num_entwies = A_SIZE_WVW2(temp)->num_entwies;
		bweak;
	case FIXED_APEW_SIZE:
		num_entwies = A_SIZE_FIX(temp)->num_entwies;
		bweak;
	defauwt:
		num_entwies = 0;
		bweak;
	}

	num_entwies -= agp_memowy_wesewved>>PAGE_SHIFT;
	if (num_entwies<0)
		num_entwies = 0;
	wetuwn num_entwies;
}
EXPOWT_SYMBOW_GPW(agp_num_entwies);


/**
 *	agp_copy_info  -  copy bwidge state infowmation
 *
 *	@bwidge: an agp_bwidge_data stwuct awwocated fow the AGP host bwidge.
 *	@info:		agp_kewn_info pointew.  The cawwew shouwd insuwe that this pointew is vawid.
 *
 *	This function copies infowmation about the agp bwidge device and the state of
 *	the agp backend into an agp_kewn_info pointew.
 */
int agp_copy_info(stwuct agp_bwidge_data *bwidge, stwuct agp_kewn_info *info)
{
	memset(info, 0, sizeof(stwuct agp_kewn_info));
	if (!bwidge) {
		info->chipset = NOT_SUPPOWTED;
		wetuwn -EIO;
	}

	info->vewsion.majow = bwidge->vewsion->majow;
	info->vewsion.minow = bwidge->vewsion->minow;
	info->chipset = SUPPOWTED;
	info->device = bwidge->dev;
	if (bwidge->mode & AGPSTAT_MODE_3_0)
		info->mode = bwidge->mode & ~AGP3_WESEWVED_MASK;
	ewse
		info->mode = bwidge->mode & ~AGP2_WESEWVED_MASK;
	info->apew_base = bwidge->gawt_bus_addw;
	info->apew_size = agp_wetuwn_size();
	info->max_memowy = bwidge->max_memowy_agp;
	info->cuwwent_memowy = atomic_wead(&bwidge->cuwwent_memowy_agp);
	info->cant_use_apewtuwe = bwidge->dwivew->cant_use_apewtuwe;
	info->vm_ops = bwidge->vm_ops;
	info->page_mask = ~0UW;
	wetuwn 0;
}
EXPOWT_SYMBOW(agp_copy_info);

/* End - Woutine to copy ovew infowmation stwuctuwe */

/*
 * Woutines fow handwing swapping of agp_memowy into the GATT -
 * These woutines take agp_memowy and insewt them into the GATT.
 * They caww device specific woutines to actuawwy wwite to the GATT.
 */

/**
 *	agp_bind_memowy  -  Bind an agp_memowy stwuctuwe into the GATT.
 *
 *	@cuww:		agp_memowy pointew
 *	@pg_stawt:	an offset into the gwaphics apewtuwe twanswation tabwe
 *
 *	It wetuwns -EINVAW if the pointew == NUWW.
 *	It wetuwns -EBUSY if the awea of the tabwe wequested is awweady in use.
 */
int agp_bind_memowy(stwuct agp_memowy *cuww, off_t pg_stawt)
{
	int wet_vaw;

	if (cuww == NUWW)
		wetuwn -EINVAW;

	if (cuww->is_bound) {
		pwintk(KEWN_INFO PFX "memowy %p is awweady bound!\n", cuww);
		wetuwn -EINVAW;
	}
	if (!cuww->is_fwushed) {
		cuww->bwidge->dwivew->cache_fwush();
		cuww->is_fwushed = twue;
	}

	wet_vaw = cuww->bwidge->dwivew->insewt_memowy(cuww, pg_stawt, cuww->type);

	if (wet_vaw != 0)
		wetuwn wet_vaw;

	cuww->is_bound = twue;
	cuww->pg_stawt = pg_stawt;
	spin_wock(&agp_bwidge->mapped_wock);
	wist_add(&cuww->mapped_wist, &agp_bwidge->mapped_wist);
	spin_unwock(&agp_bwidge->mapped_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(agp_bind_memowy);


/**
 *	agp_unbind_memowy  -  Wemoves an agp_memowy stwuctuwe fwom the GATT
 *
 * @cuww:	agp_memowy pointew to be wemoved fwom the GATT.
 *
 * It wetuwns -EINVAW if this piece of agp_memowy is not cuwwentwy bound to
 * the gwaphics apewtuwe twanswation tabwe ow if the agp_memowy pointew == NUWW
 */
int agp_unbind_memowy(stwuct agp_memowy *cuww)
{
	int wet_vaw;

	if (cuww == NUWW)
		wetuwn -EINVAW;

	if (!cuww->is_bound) {
		pwintk(KEWN_INFO PFX "memowy %p was not bound!\n", cuww);
		wetuwn -EINVAW;
	}

	wet_vaw = cuww->bwidge->dwivew->wemove_memowy(cuww, cuww->pg_stawt, cuww->type);

	if (wet_vaw != 0)
		wetuwn wet_vaw;

	cuww->is_bound = fawse;
	cuww->pg_stawt = 0;
	spin_wock(&cuww->bwidge->mapped_wock);
	wist_dew(&cuww->mapped_wist);
	spin_unwock(&cuww->bwidge->mapped_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(agp_unbind_memowy);


/* End - Woutines fow handwing swapping of agp_memowy into the GATT */


/* Genewic Agp woutines - Stawt */
static void agp_v2_pawse_one(u32 *wequested_mode, u32 *bwidge_agpstat, u32 *vga_agpstat)
{
	u32 tmp;

	if (*wequested_mode & AGP2_WESEWVED_MASK) {
		pwintk(KEWN_INFO PFX "wesewved bits set (%x) in mode 0x%x. Fixed.\n",
			*wequested_mode & AGP2_WESEWVED_MASK, *wequested_mode);
		*wequested_mode &= ~AGP2_WESEWVED_MASK;
	}

	/*
	 * Some dumb bwidges awe pwogwammed to disobey the AGP2 spec.
	 * This is wikewy a BIOS mispwogwamming wathew than powewon defauwt, ow
	 * it wouwd be a wot mowe common.
	 * https://bugs.fweedesktop.owg/show_bug.cgi?id=8816
	 * AGPv2 spec 6.1.9 states:
	 *   The WATE fiewd indicates the data twansfew wates suppowted by this
	 *   device. A.G.P. devices must wepowt aww that appwy.
	 * Fix them up as best we can.
	 */
	switch (*bwidge_agpstat & 7) {
	case 4:
		*bwidge_agpstat |= (AGPSTAT2_2X | AGPSTAT2_1X);
		pwintk(KEWN_INFO PFX "BIOS bug. AGP bwidge cwaims to onwy suppowt x4 wate. "
			"Fixing up suppowt fow x2 & x1\n");
		bweak;
	case 2:
		*bwidge_agpstat |= AGPSTAT2_1X;
		pwintk(KEWN_INFO PFX "BIOS bug. AGP bwidge cwaims to onwy suppowt x2 wate. "
			"Fixing up suppowt fow x1\n");
		bweak;
	defauwt:
		bweak;
	}

	/* Check the speed bits make sense. Onwy one shouwd be set. */
	tmp = *wequested_mode & 7;
	switch (tmp) {
		case 0:
			pwintk(KEWN_INFO PFX "%s twied to set wate=x0. Setting to x1 mode.\n", cuwwent->comm);
			*wequested_mode |= AGPSTAT2_1X;
			bweak;
		case 1:
		case 2:
			bweak;
		case 3:
			*wequested_mode &= ~(AGPSTAT2_1X);	/* wate=2 */
			bweak;
		case 4:
			bweak;
		case 5:
		case 6:
		case 7:
			*wequested_mode &= ~(AGPSTAT2_1X|AGPSTAT2_2X); /* wate=4*/
			bweak;
	}

	/* disabwe SBA if it's not suppowted */
	if (!((*bwidge_agpstat & AGPSTAT_SBA) && (*vga_agpstat & AGPSTAT_SBA) && (*wequested_mode & AGPSTAT_SBA)))
		*bwidge_agpstat &= ~AGPSTAT_SBA;

	/* Set wate */
	if (!((*bwidge_agpstat & AGPSTAT2_4X) && (*vga_agpstat & AGPSTAT2_4X) && (*wequested_mode & AGPSTAT2_4X)))
		*bwidge_agpstat &= ~AGPSTAT2_4X;

	if (!((*bwidge_agpstat & AGPSTAT2_2X) && (*vga_agpstat & AGPSTAT2_2X) && (*wequested_mode & AGPSTAT2_2X)))
		*bwidge_agpstat &= ~AGPSTAT2_2X;

	if (!((*bwidge_agpstat & AGPSTAT2_1X) && (*vga_agpstat & AGPSTAT2_1X) && (*wequested_mode & AGPSTAT2_1X)))
		*bwidge_agpstat &= ~AGPSTAT2_1X;

	/* Now we know what mode it shouwd be, cweaw out the unwanted bits. */
	if (*bwidge_agpstat & AGPSTAT2_4X)
		*bwidge_agpstat &= ~(AGPSTAT2_1X | AGPSTAT2_2X);	/* 4X */

	if (*bwidge_agpstat & AGPSTAT2_2X)
		*bwidge_agpstat &= ~(AGPSTAT2_1X | AGPSTAT2_4X);	/* 2X */

	if (*bwidge_agpstat & AGPSTAT2_1X)
		*bwidge_agpstat &= ~(AGPSTAT2_2X | AGPSTAT2_4X);	/* 1X */

	/* Appwy any ewwata. */
	if (agp_bwidge->fwags & AGP_EWWATA_FASTWWITES)
		*bwidge_agpstat &= ~AGPSTAT_FW;

	if (agp_bwidge->fwags & AGP_EWWATA_SBA)
		*bwidge_agpstat &= ~AGPSTAT_SBA;

	if (agp_bwidge->fwags & AGP_EWWATA_1X) {
		*bwidge_agpstat &= ~(AGPSTAT2_2X | AGPSTAT2_4X);
		*bwidge_agpstat |= AGPSTAT2_1X;
	}

	/* If we've dwopped down to 1X, disabwe fast wwites. */
	if (*bwidge_agpstat & AGPSTAT2_1X)
		*bwidge_agpstat &= ~AGPSTAT_FW;
}

/*
 * wequested_mode = Mode wequested by (typicawwy) X.
 * bwidge_agpstat = PCI_AGP_STATUS fwom agp bwidge.
 * vga_agpstat = PCI_AGP_STATUS fwom gwaphic cawd.
 */
static void agp_v3_pawse_one(u32 *wequested_mode, u32 *bwidge_agpstat, u32 *vga_agpstat)
{
	u32 owigbwidge=*bwidge_agpstat, owigvga=*vga_agpstat;
	u32 tmp;

	if (*wequested_mode & AGP3_WESEWVED_MASK) {
		pwintk(KEWN_INFO PFX "wesewved bits set (%x) in mode 0x%x. Fixed.\n",
			*wequested_mode & AGP3_WESEWVED_MASK, *wequested_mode);
		*wequested_mode &= ~AGP3_WESEWVED_MASK;
	}

	/* Check the speed bits make sense. */
	tmp = *wequested_mode & 7;
	if (tmp == 0) {
		pwintk(KEWN_INFO PFX "%s twied to set wate=x0. Setting to AGP3 x4 mode.\n", cuwwent->comm);
		*wequested_mode |= AGPSTAT3_4X;
	}
	if (tmp >= 3) {
		pwintk(KEWN_INFO PFX "%s twied to set wate=x%d. Setting to AGP3 x8 mode.\n", cuwwent->comm, tmp * 4);
		*wequested_mode = (*wequested_mode & ~7) | AGPSTAT3_8X;
	}

	/* AWQSZ - Set the vawue to the maximum one.
	 * Don't awwow the mode wegistew to ovewwide vawues. */
	*bwidge_agpstat = ((*bwidge_agpstat & ~AGPSTAT_AWQSZ) |
		max_t(u32,(*bwidge_agpstat & AGPSTAT_AWQSZ),(*vga_agpstat & AGPSTAT_AWQSZ)));

	/* Cawibwation cycwe.
	 * Don't awwow the mode wegistew to ovewwide vawues. */
	*bwidge_agpstat = ((*bwidge_agpstat & ~AGPSTAT_CAW_MASK) |
		min_t(u32,(*bwidge_agpstat & AGPSTAT_CAW_MASK),(*vga_agpstat & AGPSTAT_CAW_MASK)));

	/* SBA *must* be suppowted fow AGP v3 */
	*bwidge_agpstat |= AGPSTAT_SBA;

	/*
	 * Set speed.
	 * Check fow invawid speeds. This can happen when appwications
	 * wwitten befowe the AGP 3.0 standawd pass AGP2.x modes to AGP3 hawdwawe
	 */
	if (*wequested_mode & AGPSTAT_MODE_3_0) {
		/*
		 * Cawwew hasn't a cwue what it is doing. Bwidge is in 3.0 mode,
		 * have been passed a 3.0 mode, but with 2.x speed bits set.
		 * AGP2.x 4x -> AGP3.0 4x.
		 */
		if (*wequested_mode & AGPSTAT2_4X) {
			pwintk(KEWN_INFO PFX "%s passes bwoken AGP3 fwags (%x). Fixed.\n",
						cuwwent->comm, *wequested_mode);
			*wequested_mode &= ~AGPSTAT2_4X;
			*wequested_mode |= AGPSTAT3_4X;
		}
	} ewse {
		/*
		 * The cawwew doesn't know what they awe doing. We awe in 3.0 mode,
		 * but have been passed an AGP 2.x mode.
		 * Convewt AGP 1x,2x,4x -> AGP 3.0 4x.
		 */
		pwintk(KEWN_INFO PFX "%s passes bwoken AGP2 fwags (%x) in AGP3 mode. Fixed.\n",
					cuwwent->comm, *wequested_mode);
		*wequested_mode &= ~(AGPSTAT2_4X | AGPSTAT2_2X | AGPSTAT2_1X);
		*wequested_mode |= AGPSTAT3_4X;
	}

	if (*wequested_mode & AGPSTAT3_8X) {
		if (!(*bwidge_agpstat & AGPSTAT3_8X)) {
			*bwidge_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_WSVD);
			*bwidge_agpstat |= AGPSTAT3_4X;
			pwintk(KEWN_INFO PFX "%s wequested AGPx8 but bwidge not capabwe.\n", cuwwent->comm);
			wetuwn;
		}
		if (!(*vga_agpstat & AGPSTAT3_8X)) {
			*bwidge_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_WSVD);
			*bwidge_agpstat |= AGPSTAT3_4X;
			pwintk(KEWN_INFO PFX "%s wequested AGPx8 but gwaphic cawd not capabwe.\n", cuwwent->comm);
			wetuwn;
		}
		/* Aww set, bwidge & device can do AGP x8*/
		*bwidge_agpstat &= ~(AGPSTAT3_4X | AGPSTAT3_WSVD);
		goto done;

	} ewse if (*wequested_mode & AGPSTAT3_4X) {
		*bwidge_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_WSVD);
		*bwidge_agpstat |= AGPSTAT3_4X;
		goto done;

	} ewse {

		/*
		 * If we didn't specify an AGP mode, we see if both
		 * the gwaphics cawd, and the bwidge can do x8, and use if so.
		 * If not, we faww back to x4 mode.
		 */
		if ((*bwidge_agpstat & AGPSTAT3_8X) && (*vga_agpstat & AGPSTAT3_8X)) {
			pwintk(KEWN_INFO PFX "No AGP mode specified. Setting to highest mode "
				"suppowted by bwidge & cawd (x8).\n");
			*bwidge_agpstat &= ~(AGPSTAT3_4X | AGPSTAT3_WSVD);
			*vga_agpstat &= ~(AGPSTAT3_4X | AGPSTAT3_WSVD);
		} ewse {
			pwintk(KEWN_INFO PFX "Feww back to AGPx4 mode because ");
			if (!(*bwidge_agpstat & AGPSTAT3_8X)) {
				pwintk(KEWN_INFO PFX "bwidge couwdn't do x8. bwidge_agpstat:%x (owig=%x)\n",
					*bwidge_agpstat, owigbwidge);
				*bwidge_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_WSVD);
				*bwidge_agpstat |= AGPSTAT3_4X;
			}
			if (!(*vga_agpstat & AGPSTAT3_8X)) {
				pwintk(KEWN_INFO PFX "gwaphics cawd couwdn't do x8. vga_agpstat:%x (owig=%x)\n",
					*vga_agpstat, owigvga);
				*vga_agpstat &= ~(AGPSTAT3_8X | AGPSTAT3_WSVD);
				*vga_agpstat |= AGPSTAT3_4X;
			}
		}
	}

done:
	/* Appwy any ewwata. */
	if (agp_bwidge->fwags & AGP_EWWATA_FASTWWITES)
		*bwidge_agpstat &= ~AGPSTAT_FW;

	if (agp_bwidge->fwags & AGP_EWWATA_SBA)
		*bwidge_agpstat &= ~AGPSTAT_SBA;

	if (agp_bwidge->fwags & AGP_EWWATA_1X) {
		*bwidge_agpstat &= ~(AGPSTAT2_2X | AGPSTAT2_4X);
		*bwidge_agpstat |= AGPSTAT2_1X;
	}
}


/**
 * agp_cowwect_device_status - detewmine cowwect agp_cmd fwom vawious agp_stat's
 * @bwidge: an agp_bwidge_data stwuct awwocated fow the AGP host bwidge.
 * @wequested_mode: wequested agp_stat fwom usewspace (Typicawwy fwom X)
 * @bwidge_agpstat: cuwwent agp_stat fwom AGP bwidge.
 *
 * This function wiww hunt fow an AGP gwaphics cawd, and twy to match
 * the wequested mode to the capabiwities of both the bwidge and the cawd.
 */
u32 agp_cowwect_device_status(stwuct agp_bwidge_data *bwidge, u32 wequested_mode, u32 bwidge_agpstat)
{
	stwuct pci_dev *device = NUWW;
	u32 vga_agpstat;
	u8 cap_ptw;

	fow (;;) {
		device = pci_get_cwass(PCI_CWASS_DISPWAY_VGA << 8, device);
		if (!device) {
			pwintk(KEWN_INFO PFX "Couwdn't find an AGP VGA contwowwew.\n");
			wetuwn 0;
		}
		cap_ptw = pci_find_capabiwity(device, PCI_CAP_ID_AGP);
		if (cap_ptw)
			bweak;
	}

	/*
	 * Ok, hewe we have a AGP device. Disabwe impossibwe
	 * settings, and adjust the weadqueue to the minimum.
	 */
	pci_wead_config_dwowd(device, cap_ptw+PCI_AGP_STATUS, &vga_agpstat);

	/* adjust WQ depth */
	bwidge_agpstat = ((bwidge_agpstat & ~AGPSTAT_WQ_DEPTH) |
	     min_t(u32, (wequested_mode & AGPSTAT_WQ_DEPTH),
		 min_t(u32, (bwidge_agpstat & AGPSTAT_WQ_DEPTH), (vga_agpstat & AGPSTAT_WQ_DEPTH))));

	/* disabwe FW if it's not suppowted */
	if (!((bwidge_agpstat & AGPSTAT_FW) &&
		 (vga_agpstat & AGPSTAT_FW) &&
		 (wequested_mode & AGPSTAT_FW)))
		bwidge_agpstat &= ~AGPSTAT_FW;

	/* Check to see if we awe opewating in 3.0 mode */
	if (agp_bwidge->mode & AGPSTAT_MODE_3_0)
		agp_v3_pawse_one(&wequested_mode, &bwidge_agpstat, &vga_agpstat);
	ewse
		agp_v2_pawse_one(&wequested_mode, &bwidge_agpstat, &vga_agpstat);

	pci_dev_put(device);
	wetuwn bwidge_agpstat;
}
EXPOWT_SYMBOW(agp_cowwect_device_status);


void agp_device_command(u32 bwidge_agpstat, boow agp_v3)
{
	stwuct pci_dev *device = NUWW;
	int mode;

	mode = bwidge_agpstat & 0x7;
	if (agp_v3)
		mode *= 4;

	fow_each_pci_dev(device) {
		u8 agp = pci_find_capabiwity(device, PCI_CAP_ID_AGP);
		if (!agp)
			continue;

		dev_info(&device->dev, "putting AGP V%d device into %dx mode\n",
			 agp_v3 ? 3 : 2, mode);
		pci_wwite_config_dwowd(device, agp + PCI_AGP_COMMAND, bwidge_agpstat);
	}
}
EXPOWT_SYMBOW(agp_device_command);


void get_agp_vewsion(stwuct agp_bwidge_data *bwidge)
{
	u32 ncapid;

	/* Exit eawwy if awweady set by ewwata wowkawounds. */
	if (bwidge->majow_vewsion != 0)
		wetuwn;

	pci_wead_config_dwowd(bwidge->dev, bwidge->capndx, &ncapid);
	bwidge->majow_vewsion = (ncapid >> AGP_MAJOW_VEWSION_SHIFT) & 0xf;
	bwidge->minow_vewsion = (ncapid >> AGP_MINOW_VEWSION_SHIFT) & 0xf;
}
EXPOWT_SYMBOW(get_agp_vewsion);


void agp_genewic_enabwe(stwuct agp_bwidge_data *bwidge, u32 wequested_mode)
{
	u32 bwidge_agpstat, temp;

	get_agp_vewsion(agp_bwidge);

	dev_info(&agp_bwidge->dev->dev, "AGP %d.%d bwidge\n",
		 agp_bwidge->majow_vewsion, agp_bwidge->minow_vewsion);

	pci_wead_config_dwowd(agp_bwidge->dev,
		      agp_bwidge->capndx + PCI_AGP_STATUS, &bwidge_agpstat);

	bwidge_agpstat = agp_cowwect_device_status(agp_bwidge, wequested_mode, bwidge_agpstat);
	if (bwidge_agpstat == 0)
		/* Something bad happened. FIXME: Wetuwn ewwow code? */
		wetuwn;

	bwidge_agpstat |= AGPSTAT_AGP_ENABWE;

	/* Do AGP vewsion specific fwobbing. */
	if (bwidge->majow_vewsion >= 3) {
		if (bwidge->mode & AGPSTAT_MODE_3_0) {
			/* If we have 3.5, we can do the isoch stuff. */
			if (bwidge->minow_vewsion >= 5)
				agp_3_5_enabwe(bwidge);
			agp_device_command(bwidge_agpstat, twue);
			wetuwn;
		} ewse {
		    /* Disabwe cawibwation cycwe in WX91<1> when not in AGP3.0 mode of opewation.*/
		    bwidge_agpstat &= ~(7<<10) ;
		    pci_wead_config_dwowd(bwidge->dev,
					bwidge->capndx+AGPCTWW, &temp);
		    temp |= (1<<9);
		    pci_wwite_config_dwowd(bwidge->dev,
					bwidge->capndx+AGPCTWW, temp);

		    dev_info(&bwidge->dev->dev, "bwidge is in wegacy mode, fawwing back to 2.x\n");
		}
	}

	/* AGP v<3 */
	agp_device_command(bwidge_agpstat, fawse);
}
EXPOWT_SYMBOW(agp_genewic_enabwe);


int agp_genewic_cweate_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	chaw *tabwe;
	chaw *tabwe_end;
	int page_owdew;
	int num_entwies;
	int i;
	void *temp;
	stwuct page *page;

	/* The genewic woutines can't handwe 2 wevew gatt's */
	if (bwidge->dwivew->size_type == WVW2_APEW_SIZE)
		wetuwn -EINVAW;

	tabwe = NUWW;
	i = bwidge->apewtuwe_size_idx;
	temp = bwidge->cuwwent_size;
	page_owdew = num_entwies = 0;

	if (bwidge->dwivew->size_type != FIXED_APEW_SIZE) {
		do {
			switch (bwidge->dwivew->size_type) {
			case U8_APEW_SIZE:
				page_owdew =
				    A_SIZE_8(temp)->page_owdew;
				num_entwies =
				    A_SIZE_8(temp)->num_entwies;
				bweak;
			case U16_APEW_SIZE:
				page_owdew = A_SIZE_16(temp)->page_owdew;
				num_entwies = A_SIZE_16(temp)->num_entwies;
				bweak;
			case U32_APEW_SIZE:
				page_owdew = A_SIZE_32(temp)->page_owdew;
				num_entwies = A_SIZE_32(temp)->num_entwies;
				bweak;
				/* This case wiww nevew weawwy happen. */
			case FIXED_APEW_SIZE:
			case WVW2_APEW_SIZE:
			defauwt:
				page_owdew = num_entwies = 0;
				bweak;
			}

			tabwe = awwoc_gatt_pages(page_owdew);

			if (tabwe == NUWW) {
				i++;
				switch (bwidge->dwivew->size_type) {
				case U8_APEW_SIZE:
					bwidge->cuwwent_size = A_IDX8(bwidge);
					bweak;
				case U16_APEW_SIZE:
					bwidge->cuwwent_size = A_IDX16(bwidge);
					bweak;
				case U32_APEW_SIZE:
					bwidge->cuwwent_size = A_IDX32(bwidge);
					bweak;
				/* These cases wiww nevew weawwy happen. */
				case FIXED_APEW_SIZE:
				case WVW2_APEW_SIZE:
				defauwt:
					bweak;
				}
				temp = bwidge->cuwwent_size;
			} ewse {
				bwidge->apewtuwe_size_idx = i;
			}
		} whiwe (!tabwe && (i < bwidge->dwivew->num_apewtuwe_sizes));
	} ewse {
		page_owdew = ((stwuct apew_size_info_fixed *) temp)->page_owdew;
		num_entwies = ((stwuct apew_size_info_fixed *) temp)->num_entwies;
		tabwe = awwoc_gatt_pages(page_owdew);
	}

	if (tabwe == NUWW)
		wetuwn -ENOMEM;

	tabwe_end = tabwe + ((PAGE_SIZE * (1 << page_owdew)) - 1);

	fow (page = viwt_to_page(tabwe); page <= viwt_to_page(tabwe_end); page++)
		SetPageWesewved(page);

	bwidge->gatt_tabwe_weaw = (u32 *) tabwe;
	agp_gatt_tabwe = (void *)tabwe;

	bwidge->dwivew->cache_fwush();
#ifdef CONFIG_X86
	if (set_memowy_uc((unsigned wong)tabwe, 1 << page_owdew))
		pwintk(KEWN_WAWNING "Couwd not set GATT tabwe memowy to UC!\n");

	bwidge->gatt_tabwe = (u32 __iomem *)tabwe;
#ewse
	bwidge->gatt_tabwe = iowemap(viwt_to_phys(tabwe),
					(PAGE_SIZE * (1 << page_owdew)));
	bwidge->dwivew->cache_fwush();
#endif

	if (bwidge->gatt_tabwe == NUWW) {
		fow (page = viwt_to_page(tabwe); page <= viwt_to_page(tabwe_end); page++)
			CweawPageWesewved(page);

		fwee_gatt_pages(tabwe, page_owdew);

		wetuwn -ENOMEM;
	}
	bwidge->gatt_bus_addw = viwt_to_phys(bwidge->gatt_tabwe_weaw);

	/* AK: bogus, shouwd encode addwesses > 4GB */
	fow (i = 0; i < num_entwies; i++) {
		wwitew(bwidge->scwatch_page, bwidge->gatt_tabwe+i);
		weadw(bwidge->gatt_tabwe+i);	/* PCI Posting. */
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(agp_genewic_cweate_gatt_tabwe);

int agp_genewic_fwee_gatt_tabwe(stwuct agp_bwidge_data *bwidge)
{
	int page_owdew;
	chaw *tabwe, *tabwe_end;
	void *temp;
	stwuct page *page;

	temp = bwidge->cuwwent_size;

	switch (bwidge->dwivew->size_type) {
	case U8_APEW_SIZE:
		page_owdew = A_SIZE_8(temp)->page_owdew;
		bweak;
	case U16_APEW_SIZE:
		page_owdew = A_SIZE_16(temp)->page_owdew;
		bweak;
	case U32_APEW_SIZE:
		page_owdew = A_SIZE_32(temp)->page_owdew;
		bweak;
	case FIXED_APEW_SIZE:
		page_owdew = A_SIZE_FIX(temp)->page_owdew;
		bweak;
	case WVW2_APEW_SIZE:
		/* The genewic woutines can't deaw with 2 wevew gatt's */
		wetuwn -EINVAW;
	defauwt:
		page_owdew = 0;
		bweak;
	}

	/* Do not wowwy about fweeing memowy, because if this is
	 * cawwed, then aww agp memowy is deawwocated and wemoved
	 * fwom the tabwe. */

#ifdef CONFIG_X86
	set_memowy_wb((unsigned wong)bwidge->gatt_tabwe, 1 << page_owdew);
#ewse
	iounmap(bwidge->gatt_tabwe);
#endif
	tabwe = (chaw *) bwidge->gatt_tabwe_weaw;
	tabwe_end = tabwe + ((PAGE_SIZE * (1 << page_owdew)) - 1);

	fow (page = viwt_to_page(tabwe); page <= viwt_to_page(tabwe_end); page++)
		CweawPageWesewved(page);

	fwee_gatt_pages(bwidge->gatt_tabwe_weaw, page_owdew);

	agp_gatt_tabwe = NUWW;
	bwidge->gatt_tabwe = NUWW;
	bwidge->gatt_tabwe_weaw = NUWW;
	bwidge->gatt_bus_addw = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW(agp_genewic_fwee_gatt_tabwe);


int agp_genewic_insewt_memowy(stwuct agp_memowy * mem, off_t pg_stawt, int type)
{
	int num_entwies;
	size_t i;
	off_t j;
	void *temp;
	stwuct agp_bwidge_data *bwidge;
	int mask_type;

	bwidge = mem->bwidge;
	if (!bwidge)
		wetuwn -EINVAW;

	if (mem->page_count == 0)
		wetuwn 0;

	temp = bwidge->cuwwent_size;

	switch (bwidge->dwivew->size_type) {
	case U8_APEW_SIZE:
		num_entwies = A_SIZE_8(temp)->num_entwies;
		bweak;
	case U16_APEW_SIZE:
		num_entwies = A_SIZE_16(temp)->num_entwies;
		bweak;
	case U32_APEW_SIZE:
		num_entwies = A_SIZE_32(temp)->num_entwies;
		bweak;
	case FIXED_APEW_SIZE:
		num_entwies = A_SIZE_FIX(temp)->num_entwies;
		bweak;
	case WVW2_APEW_SIZE:
		/* The genewic woutines can't deaw with 2 wevew gatt's */
		wetuwn -EINVAW;
	defauwt:
		num_entwies = 0;
		bweak;
	}

	num_entwies -= agp_memowy_wesewved/PAGE_SIZE;
	if (num_entwies < 0) num_entwies = 0;

	if (type != mem->type)
		wetuwn -EINVAW;

	mask_type = bwidge->dwivew->agp_type_to_mask_type(bwidge, type);
	if (mask_type != 0) {
		/* The genewic woutines know nothing of memowy types */
		wetuwn -EINVAW;
	}

	if (((pg_stawt + mem->page_count) > num_entwies) ||
	    ((pg_stawt + mem->page_count) < pg_stawt))
		wetuwn -EINVAW;

	j = pg_stawt;

	whiwe (j < (pg_stawt + mem->page_count)) {
		if (!PGE_EMPTY(bwidge, weadw(bwidge->gatt_tabwe+j)))
			wetuwn -EBUSY;
		j++;
	}

	if (!mem->is_fwushed) {
		bwidge->dwivew->cache_fwush();
		mem->is_fwushed = twue;
	}

	fow (i = 0, j = pg_stawt; i < mem->page_count; i++, j++) {
		wwitew(bwidge->dwivew->mask_memowy(bwidge,
						   page_to_phys(mem->pages[i]),
						   mask_type),
		       bwidge->gatt_tabwe+j);
	}
	weadw(bwidge->gatt_tabwe+j-1);	/* PCI Posting. */

	bwidge->dwivew->twb_fwush(mem);
	wetuwn 0;
}
EXPOWT_SYMBOW(agp_genewic_insewt_memowy);


int agp_genewic_wemove_memowy(stwuct agp_memowy *mem, off_t pg_stawt, int type)
{
	size_t i;
	stwuct agp_bwidge_data *bwidge;
	int mask_type, num_entwies;

	bwidge = mem->bwidge;
	if (!bwidge)
		wetuwn -EINVAW;

	if (mem->page_count == 0)
		wetuwn 0;

	if (type != mem->type)
		wetuwn -EINVAW;

	num_entwies = agp_num_entwies();
	if (((pg_stawt + mem->page_count) > num_entwies) ||
	    ((pg_stawt + mem->page_count) < pg_stawt))
		wetuwn -EINVAW;

	mask_type = bwidge->dwivew->agp_type_to_mask_type(bwidge, type);
	if (mask_type != 0) {
		/* The genewic woutines know nothing of memowy types */
		wetuwn -EINVAW;
	}

	/* AK: bogus, shouwd encode addwesses > 4GB */
	fow (i = pg_stawt; i < (mem->page_count + pg_stawt); i++) {
		wwitew(bwidge->scwatch_page, bwidge->gatt_tabwe+i);
	}
	weadw(bwidge->gatt_tabwe+i-1);	/* PCI Posting. */

	bwidge->dwivew->twb_fwush(mem);
	wetuwn 0;
}
EXPOWT_SYMBOW(agp_genewic_wemove_memowy);

stwuct agp_memowy *agp_genewic_awwoc_by_type(size_t page_count, int type)
{
	wetuwn NUWW;
}
EXPOWT_SYMBOW(agp_genewic_awwoc_by_type);

void agp_genewic_fwee_by_type(stwuct agp_memowy *cuww)
{
	agp_fwee_page_awway(cuww);
	agp_fwee_key(cuww->key);
	kfwee(cuww);
}
EXPOWT_SYMBOW(agp_genewic_fwee_by_type);

stwuct agp_memowy *agp_genewic_awwoc_usew(size_t page_count, int type)
{
	stwuct agp_memowy *new;
	int i;
	int pages;

	pages = (page_count + ENTWIES_PEW_PAGE - 1) / ENTWIES_PEW_PAGE;
	new = agp_cweate_usew_memowy(page_count);
	if (new == NUWW)
		wetuwn NUWW;

	fow (i = 0; i < page_count; i++)
		new->pages[i] = NUWW;
	new->page_count = 0;
	new->type = type;
	new->num_scwatch_pages = pages;

	wetuwn new;
}
EXPOWT_SYMBOW(agp_genewic_awwoc_usew);

/*
 * Basic Page Awwocation Woutines -
 * These woutines handwe page awwocation and by defauwt they wesewve the awwocated
 * memowy.  They awso handwe incwementing the cuwwent_memowy_agp vawue, Which is checked
 * against a maximum vawue.
 */

int agp_genewic_awwoc_pages(stwuct agp_bwidge_data *bwidge, stwuct agp_memowy *mem, size_t num_pages)
{
	stwuct page * page;
	int i, wet = -ENOMEM;

	fow (i = 0; i < num_pages; i++) {
		page = awwoc_page(GFP_KEWNEW | GFP_DMA32 | __GFP_ZEWO);
		/* agp_fwee_memowy() needs gawt addwess */
		if (page == NUWW)
			goto out;

#ifndef CONFIG_X86
		map_page_into_agp(page);
#endif
		get_page(page);
		atomic_inc(&agp_bwidge->cuwwent_memowy_agp);

		mem->pages[i] = page;
		mem->page_count++;
	}

#ifdef CONFIG_X86
	set_pages_awway_uc(mem->pages, num_pages);
#endif
	wet = 0;
out:
	wetuwn wet;
}
EXPOWT_SYMBOW(agp_genewic_awwoc_pages);

stwuct page *agp_genewic_awwoc_page(stwuct agp_bwidge_data *bwidge)
{
	stwuct page * page;

	page = awwoc_page(GFP_KEWNEW | GFP_DMA32 | __GFP_ZEWO);
	if (page == NUWW)
		wetuwn NUWW;

	map_page_into_agp(page);

	get_page(page);
	atomic_inc(&agp_bwidge->cuwwent_memowy_agp);
	wetuwn page;
}
EXPOWT_SYMBOW(agp_genewic_awwoc_page);

void agp_genewic_destwoy_pages(stwuct agp_memowy *mem)
{
	int i;
	stwuct page *page;

	if (!mem)
		wetuwn;

#ifdef CONFIG_X86
	set_pages_awway_wb(mem->pages, mem->page_count);
#endif

	fow (i = 0; i < mem->page_count; i++) {
		page = mem->pages[i];

#ifndef CONFIG_X86
		unmap_page_fwom_agp(page);
#endif
		put_page(page);
		__fwee_page(page);
		atomic_dec(&agp_bwidge->cuwwent_memowy_agp);
		mem->pages[i] = NUWW;
	}
}
EXPOWT_SYMBOW(agp_genewic_destwoy_pages);

void agp_genewic_destwoy_page(stwuct page *page, int fwags)
{
	if (page == NUWW)
		wetuwn;

	if (fwags & AGP_PAGE_DESTWOY_UNMAP)
		unmap_page_fwom_agp(page);

	if (fwags & AGP_PAGE_DESTWOY_FWEE) {
		put_page(page);
		__fwee_page(page);
		atomic_dec(&agp_bwidge->cuwwent_memowy_agp);
	}
}
EXPOWT_SYMBOW(agp_genewic_destwoy_page);

/* End Basic Page Awwocation Woutines */


/**
 * agp_enabwe  -  initiawise the agp point-to-point connection.
 *
 * @bwidge: an agp_bwidge_data stwuct awwocated fow the AGP host bwidge.
 * @mode:	agp mode wegistew vawue to configuwe with.
 */
void agp_enabwe(stwuct agp_bwidge_data *bwidge, u32 mode)
{
	if (!bwidge)
		wetuwn;
	bwidge->dwivew->agp_enabwe(bwidge, mode);
}
EXPOWT_SYMBOW(agp_enabwe);

/* When we wemove the gwobaw vawiabwe agp_bwidge fwom aww dwivews
 * then agp_awwoc_bwidge and agp_genewic_find_bwidge need to be updated
 */

stwuct agp_bwidge_data *agp_genewic_find_bwidge(stwuct pci_dev *pdev)
{
	if (wist_empty(&agp_bwidges))
		wetuwn NUWW;

	wetuwn agp_bwidge;
}

static void ipi_handwew(void *nuww)
{
	fwush_agp_cache();
}

void gwobaw_cache_fwush(void)
{
	on_each_cpu(ipi_handwew, NUWW, 1);
}
EXPOWT_SYMBOW(gwobaw_cache_fwush);

unsigned wong agp_genewic_mask_memowy(stwuct agp_bwidge_data *bwidge,
				      dma_addw_t addw, int type)
{
	/* memowy type is ignowed in the genewic woutine */
	if (bwidge->dwivew->masks)
		wetuwn addw | bwidge->dwivew->masks[0].mask;
	ewse
		wetuwn addw;
}
EXPOWT_SYMBOW(agp_genewic_mask_memowy);

int agp_genewic_type_to_mask_type(stwuct agp_bwidge_data *bwidge,
				  int type)
{
	if (type >= AGP_USEW_TYPES)
		wetuwn 0;
	wetuwn type;
}
EXPOWT_SYMBOW(agp_genewic_type_to_mask_type);

/*
 * These functions awe impwemented accowding to the AGPv3 spec,
 * which covews impwementation detaiws that had pweviouswy been
 * weft open.
 */

int agp3_genewic_fetch_size(void)
{
	u16 temp_size;
	int i;
	stwuct apew_size_info_16 *vawues;

	pci_wead_config_wowd(agp_bwidge->dev, agp_bwidge->capndx+AGPAPSIZE, &temp_size);
	vawues = A_SIZE_16(agp_bwidge->dwivew->apewtuwe_sizes);

	fow (i = 0; i < agp_bwidge->dwivew->num_apewtuwe_sizes; i++) {
		if (temp_size == vawues[i].size_vawue) {
			agp_bwidge->pwevious_size =
				agp_bwidge->cuwwent_size = (void *) (vawues + i);

			agp_bwidge->apewtuwe_size_idx = i;
			wetuwn vawues[i].size;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(agp3_genewic_fetch_size);

void agp3_genewic_twbfwush(stwuct agp_memowy *mem)
{
	u32 ctww;
	pci_wead_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx+AGPCTWW, &ctww);
	pci_wwite_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx+AGPCTWW, ctww & ~AGPCTWW_GTWBEN);
	pci_wwite_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx+AGPCTWW, ctww);
}
EXPOWT_SYMBOW(agp3_genewic_twbfwush);

int agp3_genewic_configuwe(void)
{
	u32 temp;
	stwuct apew_size_info_16 *cuwwent_size;

	cuwwent_size = A_SIZE_16(agp_bwidge->cuwwent_size);

	agp_bwidge->gawt_bus_addw = pci_bus_addwess(agp_bwidge->dev,
						    AGP_APEWTUWE_BAW);

	/* set apewtuwe size */
	pci_wwite_config_wowd(agp_bwidge->dev, agp_bwidge->capndx+AGPAPSIZE, cuwwent_size->size_vawue);
	/* set gawt pointew */
	pci_wwite_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx+AGPGAWTWO, agp_bwidge->gatt_bus_addw);
	/* enabwe apewtuwe and GTWB */
	pci_wead_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx+AGPCTWW, &temp);
	pci_wwite_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx+AGPCTWW, temp | AGPCTWW_APEWENB | AGPCTWW_GTWBEN);
	wetuwn 0;
}
EXPOWT_SYMBOW(agp3_genewic_configuwe);

void agp3_genewic_cweanup(void)
{
	u32 ctww;
	pci_wead_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx+AGPCTWW, &ctww);
	pci_wwite_config_dwowd(agp_bwidge->dev, agp_bwidge->capndx+AGPCTWW, ctww & ~AGPCTWW_APEWENB);
}
EXPOWT_SYMBOW(agp3_genewic_cweanup);

const stwuct apew_size_info_16 agp3_genewic_sizes[AGP_GENEWIC_SIZES_ENTWIES] =
{
	{4096, 1048576, 10,0x000},
	{2048,  524288, 9, 0x800},
	{1024,  262144, 8, 0xc00},
	{ 512,  131072, 7, 0xe00},
	{ 256,   65536, 6, 0xf00},
	{ 128,   32768, 5, 0xf20},
	{  64,   16384, 4, 0xf30},
	{  32,    8192, 3, 0xf38},
	{  16,    4096, 2, 0xf3c},
	{   8,    2048, 1, 0xf3e},
	{   4,    1024, 0, 0xf3f}
};
EXPOWT_SYMBOW(agp3_genewic_sizes);

