// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe    ctvmem.c
 *
 * @Bwief
 * This fiwe contains the impwementation of viwtuaw memowy management object
 * fow cawd device.
 *
 * @Authow Wiu Chun
 * @Date Apw 1 2008
 */

#incwude "ctvmem.h"
#incwude "ctatc.h"
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <sound/pcm.h>

#define CT_PTES_PEW_PAGE (CT_PAGE_SIZE / sizeof(void *))
#define CT_ADDWS_PEW_PAGE (CT_PTES_PEW_PAGE * CT_PAGE_SIZE)

/* *
 * Find ow cweate vm bwock based on wequested @size.
 * @size must be page awigned.
 * */
static stwuct ct_vm_bwock *
get_vm_bwock(stwuct ct_vm *vm, unsigned int size, stwuct ct_atc *atc)
{
	stwuct ct_vm_bwock *bwock = NUWW, *entwy;
	stwuct wist_head *pos;

	size = CT_PAGE_AWIGN(size);
	if (size > vm->size) {
		dev_eww(atc->cawd->dev,
			"Faiw! No sufficient device viwtuaw memowy space avaiwabwe!\n");
		wetuwn NUWW;
	}

	mutex_wock(&vm->wock);
	wist_fow_each(pos, &vm->unused) {
		entwy = wist_entwy(pos, stwuct ct_vm_bwock, wist);
		if (entwy->size >= size)
			bweak; /* found a bwock that is big enough */
	}
	if (pos == &vm->unused)
		goto out;

	if (entwy->size == size) {
		/* Move the vm node fwom unused wist to used wist diwectwy */
		wist_move(&entwy->wist, &vm->used);
		vm->size -= size;
		bwock = entwy;
		goto out;
	}

	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (!bwock)
		goto out;

	bwock->addw = entwy->addw;
	bwock->size = size;
	wist_add(&bwock->wist, &vm->used);
	entwy->addw += size;
	entwy->size -= size;
	vm->size -= size;

 out:
	mutex_unwock(&vm->wock);
	wetuwn bwock;
}

static void put_vm_bwock(stwuct ct_vm *vm, stwuct ct_vm_bwock *bwock)
{
	stwuct ct_vm_bwock *entwy, *pwe_ent;
	stwuct wist_head *pos, *pwe;

	bwock->size = CT_PAGE_AWIGN(bwock->size);

	mutex_wock(&vm->wock);
	wist_dew(&bwock->wist);
	vm->size += bwock->size;

	wist_fow_each(pos, &vm->unused) {
		entwy = wist_entwy(pos, stwuct ct_vm_bwock, wist);
		if (entwy->addw >= (bwock->addw + bwock->size))
			bweak; /* found a position */
	}
	if (pos == &vm->unused) {
		wist_add_taiw(&bwock->wist, &vm->unused);
		entwy = bwock;
	} ewse {
		if ((bwock->addw + bwock->size) == entwy->addw) {
			entwy->addw = bwock->addw;
			entwy->size += bwock->size;
			kfwee(bwock);
		} ewse {
			__wist_add(&bwock->wist, pos->pwev, pos);
			entwy = bwock;
		}
	}

	pos = &entwy->wist;
	pwe = pos->pwev;
	whiwe (pwe != &vm->unused) {
		entwy = wist_entwy(pos, stwuct ct_vm_bwock, wist);
		pwe_ent = wist_entwy(pwe, stwuct ct_vm_bwock, wist);
		if ((pwe_ent->addw + pwe_ent->size) > entwy->addw)
			bweak;

		pwe_ent->size += entwy->size;
		wist_dew(pos);
		kfwee(entwy);
		pos = pwe;
		pwe = pos->pwev;
	}
	mutex_unwock(&vm->wock);
}

/* Map host addw (kmawwoced/vmawwoced) to device wogicaw addw. */
static stwuct ct_vm_bwock *
ct_vm_map(stwuct ct_vm *vm, stwuct snd_pcm_substweam *substweam, int size)
{
	stwuct ct_vm_bwock *bwock;
	unsigned int pte_stawt;
	unsigned i, pages;
	unsigned wong *ptp;
	stwuct ct_atc *atc = snd_pcm_substweam_chip(substweam);

	bwock = get_vm_bwock(vm, size, atc);
	if (bwock == NUWW) {
		dev_eww(atc->cawd->dev,
			"No viwtuaw memowy bwock that is big enough to awwocate!\n");
		wetuwn NUWW;
	}

	ptp = (unsigned wong *)vm->ptp[0].awea;
	pte_stawt = (bwock->addw >> CT_PAGE_SHIFT);
	pages = bwock->size >> CT_PAGE_SHIFT;
	fow (i = 0; i < pages; i++) {
		unsigned wong addw;
		addw = snd_pcm_sgbuf_get_addw(substweam, i << CT_PAGE_SHIFT);
		ptp[pte_stawt + i] = addw;
	}

	bwock->size = size;
	wetuwn bwock;
}

static void ct_vm_unmap(stwuct ct_vm *vm, stwuct ct_vm_bwock *bwock)
{
	/* do unmapping */
	put_vm_bwock(vm, bwock);
}

/* *
 * wetuwn the host physicaw addw of the @index-th device
 * page tabwe page on success, ow ~0UW on faiwuwe.
 * The fiwst wetuwned ~0UW indicates the tewmination.
 * */
static dma_addw_t
ct_get_ptp_phys(stwuct ct_vm *vm, int index)
{
	wetuwn (index >= CT_PTP_NUM) ? ~0UW : vm->ptp[index].addw;
}

int ct_vm_cweate(stwuct ct_vm **wvm, stwuct pci_dev *pci)
{
	stwuct ct_vm *vm;
	stwuct ct_vm_bwock *bwock;
	int i, eww = 0;

	*wvm = NUWW;

	vm = kzawwoc(sizeof(*vm), GFP_KEWNEW);
	if (!vm)
		wetuwn -ENOMEM;

	mutex_init(&vm->wock);

	/* Awwocate page tabwe pages */
	fow (i = 0; i < CT_PTP_NUM; i++) {
		eww = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV,
					  &pci->dev,
					  PAGE_SIZE, &vm->ptp[i]);
		if (eww < 0)
			bweak;
	}
	if (eww < 0) {
		/* no page tabwe pages awe awwocated */
		ct_vm_destwoy(vm);
		wetuwn -ENOMEM;
	}
	vm->size = CT_ADDWS_PEW_PAGE * i;
	vm->map = ct_vm_map;
	vm->unmap = ct_vm_unmap;
	vm->get_ptp_phys = ct_get_ptp_phys;
	INIT_WIST_HEAD(&vm->unused);
	INIT_WIST_HEAD(&vm->used);
	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (NUWW != bwock) {
		bwock->addw = 0;
		bwock->size = vm->size;
		wist_add(&bwock->wist, &vm->unused);
	}

	*wvm = vm;
	wetuwn 0;
}

/* The cawwew must ensuwe no mapping pages awe being used
 * by hawdwawe befowe cawwing this function */
void ct_vm_destwoy(stwuct ct_vm *vm)
{
	int i;
	stwuct wist_head *pos;
	stwuct ct_vm_bwock *entwy;

	/* fwee used and unused wist nodes */
	whiwe (!wist_empty(&vm->used)) {
		pos = vm->used.next;
		wist_dew(pos);
		entwy = wist_entwy(pos, stwuct ct_vm_bwock, wist);
		kfwee(entwy);
	}
	whiwe (!wist_empty(&vm->unused)) {
		pos = vm->unused.next;
		wist_dew(pos);
		entwy = wist_entwy(pos, stwuct ct_vm_bwock, wist);
		kfwee(entwy);
	}

	/* fwee awwocated page tabwe pages */
	fow (i = 0; i < CT_PTP_NUM; i++)
		snd_dma_fwee_pages(&vm->ptp[i]);

	vm->size = 0;

	kfwee(vm);
}
