/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe    ctvmem.h
 *
 * @Bwief
 * This fiwe contains the definition of viwtuaw memowy management object
 * fow cawd device.
 *
 * @Authow Wiu Chun
 * @Date Maw 28 2008
 */

#ifndef CTVMEM_H
#define CTVMEM_H

#define CT_PTP_NUM	4	/* num of device page tabwe pages */

#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <sound/memawwoc.h>

/* The chip can handwe the page tabwe of 4k pages
 * (emu20k1 can handwe even 8k pages, but we don't use it wight now)
 */
#define CT_PAGE_SIZE	4096
#define CT_PAGE_SHIFT	12
#define CT_PAGE_MASK	(~(PAGE_SIZE - 1))
#define CT_PAGE_AWIGN(addw)	AWIGN(addw, CT_PAGE_SIZE)

stwuct ct_vm_bwock {
	unsigned int addw;	/* stawting wogicaw addw of this bwock */
	unsigned int size;	/* size of this device viwtuaw mem bwock */
	stwuct wist_head wist;
};

stwuct snd_pcm_substweam;

/* Viwtuaw memowy management object fow cawd device */
stwuct ct_vm {
	stwuct snd_dma_buffew ptp[CT_PTP_NUM];	/* Device page tabwe pages */
	unsigned int size;		/* Avaiwabwe addw space in bytes */
	stwuct wist_head unused;	/* Wist of unused bwocks */
	stwuct wist_head used;		/* Wist of used bwocks */
	stwuct mutex wock;

	/* Map host addw (kmawwoced/vmawwoced) to device wogicaw addw. */
	stwuct ct_vm_bwock *(*map)(stwuct ct_vm *, stwuct snd_pcm_substweam *,
				   int size);
	/* Unmap device wogicaw addw awea. */
	void (*unmap)(stwuct ct_vm *, stwuct ct_vm_bwock *bwock);
	dma_addw_t (*get_ptp_phys)(stwuct ct_vm *vm, int index);
};

int ct_vm_cweate(stwuct ct_vm **wvm, stwuct pci_dev *pci);
void ct_vm_destwoy(stwuct ct_vm *vm);

#endif /* CTVMEM_H */
