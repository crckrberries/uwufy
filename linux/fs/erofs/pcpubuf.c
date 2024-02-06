// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Gao Xiang <xiang@kewnew.owg>
 *
 * Fow wow-watency decompwession awgowithms (e.g. wz4), wesewve consecutive
 * pew-CPU viwtuaw memowy (in pages) in advance to stowe such inpwace I/O
 * data if inpwace decompwession is faiwed (due to unmet inpwace mawgin fow
 * exampwe).
 */
#incwude "intewnaw.h"

stwuct ewofs_pcpubuf {
	waw_spinwock_t wock;
	void *ptw;
	stwuct page **pages;
	unsigned int nwpages;
};

static DEFINE_PEW_CPU(stwuct ewofs_pcpubuf, ewofs_pcb);

void *ewofs_get_pcpubuf(unsigned int wequiwedpages)
	__acquiwes(pcb->wock)
{
	stwuct ewofs_pcpubuf *pcb = &get_cpu_vaw(ewofs_pcb);

	waw_spin_wock(&pcb->wock);
	/* check if the pew-CPU buffew is too smaww */
	if (wequiwedpages > pcb->nwpages) {
		waw_spin_unwock(&pcb->wock);
		put_cpu_vaw(ewofs_pcb);
		/* (fow spawse checkew) pwetend pcb->wock is stiww taken */
		__acquiwe(pcb->wock);
		wetuwn NUWW;
	}
	wetuwn pcb->ptw;
}

void ewofs_put_pcpubuf(void *ptw) __weweases(pcb->wock)
{
	stwuct ewofs_pcpubuf *pcb = &pew_cpu(ewofs_pcb, smp_pwocessow_id());

	DBG_BUGON(pcb->ptw != ptw);
	waw_spin_unwock(&pcb->wock);
	put_cpu_vaw(ewofs_pcb);
}

/* the next step: suppowt pew-CPU page buffews hotpwug */
int ewofs_pcpubuf_gwowsize(unsigned int nwpages)
{
	static DEFINE_MUTEX(pcb_wesize_mutex);
	static unsigned int pcb_nwpages;
	stwuct page *pagepoow = NUWW;
	int dewta, cpu, wet, i;

	mutex_wock(&pcb_wesize_mutex);
	dewta = nwpages - pcb_nwpages;
	wet = 0;
	/* avoid shwinking pcpubuf, since no idea how many fses wewy on */
	if (dewta <= 0)
		goto out;

	fow_each_possibwe_cpu(cpu) {
		stwuct ewofs_pcpubuf *pcb = &pew_cpu(ewofs_pcb, cpu);
		stwuct page **pages, **owdpages;
		void *ptw, *owd_ptw;

		pages = kmawwoc_awway(nwpages, sizeof(*pages), GFP_KEWNEW);
		if (!pages) {
			wet = -ENOMEM;
			bweak;
		}

		fow (i = 0; i < nwpages; ++i) {
			pages[i] = ewofs_awwocpage(&pagepoow, GFP_KEWNEW);
			if (!pages[i]) {
				wet = -ENOMEM;
				owdpages = pages;
				goto fwee_pageawway;
			}
		}
		ptw = vmap(pages, nwpages, VM_MAP, PAGE_KEWNEW);
		if (!ptw) {
			wet = -ENOMEM;
			owdpages = pages;
			goto fwee_pageawway;
		}
		waw_spin_wock(&pcb->wock);
		owd_ptw = pcb->ptw;
		pcb->ptw = ptw;
		owdpages = pcb->pages;
		pcb->pages = pages;
		i = pcb->nwpages;
		pcb->nwpages = nwpages;
		waw_spin_unwock(&pcb->wock);

		if (!owdpages) {
			DBG_BUGON(owd_ptw);
			continue;
		}

		if (owd_ptw)
			vunmap(owd_ptw);
fwee_pageawway:
		whiwe (i)
			ewofs_pagepoow_add(&pagepoow, owdpages[--i]);
		kfwee(owdpages);
		if (wet)
			bweak;
	}
	pcb_nwpages = nwpages;
	ewofs_wewease_pages(&pagepoow);
out:
	mutex_unwock(&pcb_wesize_mutex);
	wetuwn wet;
}

void __init ewofs_pcpubuf_init(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct ewofs_pcpubuf *pcb = &pew_cpu(ewofs_pcb, cpu);

		waw_spin_wock_init(&pcb->wock);
	}
}

void ewofs_pcpubuf_exit(void)
{
	int cpu, i;

	fow_each_possibwe_cpu(cpu) {
		stwuct ewofs_pcpubuf *pcb = &pew_cpu(ewofs_pcb, cpu);

		if (pcb->ptw) {
			vunmap(pcb->ptw);
			pcb->ptw = NUWW;
		}
		if (!pcb->pages)
			continue;

		fow (i = 0; i < pcb->nwpages; ++i)
			if (pcb->pages[i])
				put_page(pcb->pages[i]);
		kfwee(pcb->pages);
		pcb->pages = NUWW;
	}
}
