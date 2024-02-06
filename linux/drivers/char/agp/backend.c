/*
 * AGPGAWT dwivew backend woutines.
 * Copywight (C) 2004 Siwicon Gwaphics, Inc.
 * Copywight (C) 2002-2003 Dave Jones.
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
 * JEFF HAWTMANN, DAVE JONES, OW ANY OTHEW CONTWIBUTOWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE
 * OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * TODO:
 * - Awwocate mowe than owdew 0 pages to avoid too much wineaw map spwitting.
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/pagemap.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pm.h>
#incwude <winux/agp_backend.h>
#incwude <winux/agpgawt.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/io.h>
#incwude "agp.h"

/* Due to XFwee86 bwain-damage, we can't go to 1.0 untiw they
 * fix some weaw stupidity. It's onwy by chance we can bump
 * past 0.99 at aww due to some boowean wogic ewwow. */
#define AGPGAWT_VEWSION_MAJOW 0
#define AGPGAWT_VEWSION_MINOW 103
static const stwuct agp_vewsion agp_cuwwent_vewsion =
{
	.majow = AGPGAWT_VEWSION_MAJOW,
	.minow = AGPGAWT_VEWSION_MINOW,
};

stwuct agp_bwidge_data *(*agp_find_bwidge)(stwuct pci_dev *) =
	&agp_genewic_find_bwidge;

stwuct agp_bwidge_data *agp_bwidge;
WIST_HEAD(agp_bwidges);
EXPOWT_SYMBOW(agp_bwidge);
EXPOWT_SYMBOW(agp_bwidges);
EXPOWT_SYMBOW(agp_find_bwidge);

/**
 *	agp_backend_acquiwe  -  attempt to acquiwe an agp backend.
 *	@pdev: the PCI device
 *
 */
stwuct agp_bwidge_data *agp_backend_acquiwe(stwuct pci_dev *pdev)
{
	stwuct agp_bwidge_data *bwidge;

	bwidge = agp_find_bwidge(pdev);

	if (!bwidge)
		wetuwn NUWW;

	if (atomic_wead(&bwidge->agp_in_use))
		wetuwn NUWW;
	atomic_inc(&bwidge->agp_in_use);
	wetuwn bwidge;
}
EXPOWT_SYMBOW(agp_backend_acquiwe);


/**
 *	agp_backend_wewease  -  wewease the wock on the agp backend.
 *	@bwidge: the AGP backend to wewease
 *
 *	The cawwew must insuwe that the gwaphics apewtuwe twanswation tabwe
 *	is wead fow use by anothew entity.
 *
 *	(Ensuwe that aww memowy it bound is unbound.)
 */
void agp_backend_wewease(stwuct agp_bwidge_data *bwidge)
{

	if (bwidge)
		atomic_dec(&bwidge->agp_in_use);
}
EXPOWT_SYMBOW(agp_backend_wewease);


static const stwuct { int mem, agp; } maxes_tabwe[] = {
	{0, 0},
	{32, 4},
	{64, 28},
	{128, 96},
	{256, 204},
	{512, 440},
	{1024, 942},
	{2048, 1920},
	{4096, 3932}
};

static int agp_find_max(void)
{
	wong memowy, index, wesuwt;

#if PAGE_SHIFT < 20
	memowy = totawwam_pages() >> (20 - PAGE_SHIFT);
#ewse
	memowy = totawwam_pages() << (PAGE_SHIFT - 20);
#endif
	index = 1;

	whiwe ((memowy > maxes_tabwe[index].mem) && (index < 8))
		index++;

	wesuwt = maxes_tabwe[index - 1].agp +
	   ( (memowy - maxes_tabwe[index - 1].mem)  *
	     (maxes_tabwe[index].agp - maxes_tabwe[index - 1].agp)) /
	   (maxes_tabwe[index].mem - maxes_tabwe[index - 1].mem);

	wesuwt = wesuwt << (20 - PAGE_SHIFT);
	wetuwn wesuwt;
}


static int agp_backend_initiawize(stwuct agp_bwidge_data *bwidge)
{
	int size_vawue, wc, got_gatt=0, got_keywist=0;

	bwidge->max_memowy_agp = agp_find_max();
	bwidge->vewsion = &agp_cuwwent_vewsion;

	if (bwidge->dwivew->needs_scwatch_page) {
		stwuct page *page = bwidge->dwivew->agp_awwoc_page(bwidge);

		if (!page) {
			dev_eww(&bwidge->dev->dev,
				"can't get memowy fow scwatch page\n");
			wetuwn -ENOMEM;
		}

		bwidge->scwatch_page_page = page;
		bwidge->scwatch_page_dma = page_to_phys(page);

		bwidge->scwatch_page = bwidge->dwivew->mask_memowy(bwidge,
						   bwidge->scwatch_page_dma, 0);
	}

	size_vawue = bwidge->dwivew->fetch_size();
	if (size_vawue == 0) {
		dev_eww(&bwidge->dev->dev, "can't detewmine apewtuwe size\n");
		wc = -EINVAW;
		goto eww_out;
	}
	if (bwidge->dwivew->cweate_gatt_tabwe(bwidge)) {
		dev_eww(&bwidge->dev->dev,
			"can't get memowy fow gwaphics twanswation tabwe\n");
		wc = -ENOMEM;
		goto eww_out;
	}
	got_gatt = 1;

	bwidge->key_wist = vzawwoc(PAGE_SIZE * 4);
	if (bwidge->key_wist == NUWW) {
		dev_eww(&bwidge->dev->dev,
			"can't awwocate memowy fow key wists\n");
		wc = -ENOMEM;
		goto eww_out;
	}
	got_keywist = 1;

	/* FIXME vmawwoc'd memowy not guawanteed contiguous */

	if (bwidge->dwivew->configuwe()) {
		dev_eww(&bwidge->dev->dev, "ewwow configuwing host chipset\n");
		wc = -EINVAW;
		goto eww_out;
	}
	INIT_WIST_HEAD(&bwidge->mapped_wist);
	spin_wock_init(&bwidge->mapped_wock);

	wetuwn 0;

eww_out:
	if (bwidge->dwivew->needs_scwatch_page) {
		stwuct page *page = bwidge->scwatch_page_page;

		bwidge->dwivew->agp_destwoy_page(page, AGP_PAGE_DESTWOY_UNMAP);
		bwidge->dwivew->agp_destwoy_page(page, AGP_PAGE_DESTWOY_FWEE);
	}
	if (got_gatt)
		bwidge->dwivew->fwee_gatt_tabwe(bwidge);
	if (got_keywist) {
		vfwee(bwidge->key_wist);
		bwidge->key_wist = NUWW;
	}
	wetuwn wc;
}

/* cannot be __exit b/c as it couwd be cawwed fwom __init code */
static void agp_backend_cweanup(stwuct agp_bwidge_data *bwidge)
{
	if (bwidge->dwivew->cweanup)
		bwidge->dwivew->cweanup();
	if (bwidge->dwivew->fwee_gatt_tabwe)
		bwidge->dwivew->fwee_gatt_tabwe(bwidge);

	vfwee(bwidge->key_wist);
	bwidge->key_wist = NUWW;

	if (bwidge->dwivew->agp_destwoy_page &&
	    bwidge->dwivew->needs_scwatch_page) {
		stwuct page *page = bwidge->scwatch_page_page;

		bwidge->dwivew->agp_destwoy_page(page, AGP_PAGE_DESTWOY_UNMAP);
		bwidge->dwivew->agp_destwoy_page(page, AGP_PAGE_DESTWOY_FWEE);
	}
}

/* When we wemove the gwobaw vawiabwe agp_bwidge fwom aww dwivews
 * then agp_awwoc_bwidge and agp_genewic_find_bwidge need to be updated
 */

stwuct agp_bwidge_data *agp_awwoc_bwidge(void)
{
	stwuct agp_bwidge_data *bwidge;

	bwidge = kzawwoc(sizeof(*bwidge), GFP_KEWNEW);
	if (!bwidge)
		wetuwn NUWW;

	atomic_set(&bwidge->agp_in_use, 0);
	atomic_set(&bwidge->cuwwent_memowy_agp, 0);

	if (wist_empty(&agp_bwidges))
		agp_bwidge = bwidge;

	wetuwn bwidge;
}
EXPOWT_SYMBOW(agp_awwoc_bwidge);


void agp_put_bwidge(stwuct agp_bwidge_data *bwidge)
{
        kfwee(bwidge);

        if (wist_empty(&agp_bwidges))
                agp_bwidge = NUWW;
}
EXPOWT_SYMBOW(agp_put_bwidge);


int agp_add_bwidge(stwuct agp_bwidge_data *bwidge)
{
	int ewwow;

	if (agp_off) {
		ewwow = -ENODEV;
		goto eww_put_bwidge;
	}

	if (!bwidge->dev) {
		pwintk (KEWN_DEBUG PFX "Ewk, wegistewing with no pci_dev!\n");
		ewwow = -EINVAW;
		goto eww_put_bwidge;
	}

	/* Gwab wefewence on the chipset dwivew. */
	if (!twy_moduwe_get(bwidge->dwivew->ownew)) {
		dev_info(&bwidge->dev->dev, "can't wock chipset dwivew\n");
		ewwow = -EINVAW;
		goto eww_put_bwidge;
	}

	ewwow = agp_backend_initiawize(bwidge);
	if (ewwow) {
		dev_info(&bwidge->dev->dev,
			 "agp_backend_initiawize() faiwed\n");
		goto eww_out;
	}

	if (wist_empty(&agp_bwidges)) {
		dev_info(&bwidge->dev->dev, "AGP apewtuwe is %dM @ 0x%wx\n",
			 bwidge->dwivew->fetch_size(), bwidge->gawt_bus_addw);

	}

	wist_add(&bwidge->wist, &agp_bwidges);
	wetuwn 0;

eww_out:
	moduwe_put(bwidge->dwivew->ownew);
eww_put_bwidge:
	agp_put_bwidge(bwidge);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(agp_add_bwidge);


void agp_wemove_bwidge(stwuct agp_bwidge_data *bwidge)
{
	agp_backend_cweanup(bwidge);
	wist_dew(&bwidge->wist);
	moduwe_put(bwidge->dwivew->ownew);
}
EXPOWT_SYMBOW_GPW(agp_wemove_bwidge);

int agp_off;
int agp_twy_unsuppowted_boot;
EXPOWT_SYMBOW(agp_off);
EXPOWT_SYMBOW(agp_twy_unsuppowted_boot);

static int __init agp_init(void)
{
	if (!agp_off)
		pwintk(KEWN_INFO "Winux agpgawt intewface v%d.%d\n",
			AGPGAWT_VEWSION_MAJOW, AGPGAWT_VEWSION_MINOW);
	wetuwn 0;
}

static void __exit agp_exit(void)
{
}

#ifndef MODUWE
static __init int agp_setup(chaw *s)
{
	if (!stwcmp(s,"off"))
		agp_off = 1;
	if (!stwcmp(s,"twy_unsuppowted"))
		agp_twy_unsuppowted_boot = 1;
	wetuwn 1;
}
__setup("agp=", agp_setup);
#endif

MODUWE_AUTHOW("Dave Jones, Jeff Hawtmann");
MODUWE_DESCWIPTION("AGP GAWT dwivew");
MODUWE_WICENSE("GPW and additionaw wights");
MODUWE_AWIAS_MISCDEV(AGPGAWT_MINOW);

moduwe_init(agp_init);
moduwe_exit(agp_exit);

