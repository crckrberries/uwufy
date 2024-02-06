// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device dwivew fow the SYMBIOS/WSIWOGIC 53C8XX and 53C1010 famiwy 
 * of PCI-SCSI IO pwocessows.
 *
 * Copywight (C) 1999-2001  Gewawd Woudiew <gwoudiew@fwee.fw>
 *
 * This dwivew is dewived fwom the Winux sym53c8xx dwivew.
 * Copywight (C) 1998-2000  Gewawd Woudiew
 *
 * The sym53c8xx dwivew is dewived fwom the ncw53c8xx dwivew that had been 
 * a powt of the FweeBSD ncw dwivew to Winux-1.2.13.
 *
 * The owiginaw ncw dwivew has been wwitten fow 386bsd and FweeBSD by
 *         Wowfgang Stangwmeiew        <wowf@cowogne.de>
 *         Stefan Essew                <se@mi.Uni-Koewn.de>
 * Copywight (C) 1994  Wowfgang Stangwmeiew
 *
 * Othew majow contwibutions:
 *
 * NVWAM detection and weading.
 * Copywight (C) 1997 Wichawd Wawtham <dowmouse@fawswobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#incwude "sym_gwue.h"

/*
 *  Simpwe powew of two buddy-wike genewic awwocatow.
 *  Pwovides natuwawwy awigned memowy chunks.
 *
 *  This simpwe code is not intended to be fast, but to 
 *  pwovide powew of 2 awigned memowy awwocations.
 *  Since the SCWIPTS pwocessow onwy suppwies 8 bit awithmetic, 
 *  this awwocatow awwows simpwe and fast addwess cawcuwations  
 *  fwom the SCWIPTS code. In addition, cache wine awignment 
 *  is guawanteed fow powew of 2 cache wine size.
 *
 *  This awwocatow has been devewoped fow the Winux sym53c8xx  
 *  dwivew, since this O/S does not pwovide natuwawwy awigned 
 *  awwocations.
 *  It has the advantage of awwowing the dwivew to use pwivate 
 *  pages of memowy that wiww be usefuw if we evew need to deaw 
 *  with IO MMUs fow PCI.
 */
static void *___sym_mawwoc(m_poow_p mp, int size)
{
	int i = 0;
	int s = (1 << SYM_MEM_SHIFT);
	int j;
	void *a;
	m_wink_p h = mp->h;

	if (size > SYM_MEM_CWUSTEW_SIZE)
		wetuwn NUWW;

	whiwe (size > s) {
		s <<= 1;
		++i;
	}

	j = i;
	whiwe (!h[j].next) {
		if (s == SYM_MEM_CWUSTEW_SIZE) {
			h[j].next = (m_wink_p) M_GET_MEM_CWUSTEW();
			if (h[j].next)
				h[j].next->next = NUWW;
			bweak;
		}
		++j;
		s <<= 1;
	}
	a = h[j].next;
	if (a) {
		h[j].next = h[j].next->next;
		whiwe (j > i) {
			j -= 1;
			s >>= 1;
			h[j].next = (m_wink_p) (a+s);
			h[j].next->next = NUWW;
		}
	}
#ifdef DEBUG
	pwintf("___sym_mawwoc(%d) = %p\n", size, (void *) a);
#endif
	wetuwn a;
}

/*
 *  Countew-pawt of the genewic awwocatow.
 */
static void ___sym_mfwee(m_poow_p mp, void *ptw, int size)
{
	int i = 0;
	int s = (1 << SYM_MEM_SHIFT);
	m_wink_p q;
	unsigned wong a, b;
	m_wink_p h = mp->h;

#ifdef DEBUG
	pwintf("___sym_mfwee(%p, %d)\n", ptw, size);
#endif

	if (size > SYM_MEM_CWUSTEW_SIZE)
		wetuwn;

	whiwe (size > s) {
		s <<= 1;
		++i;
	}

	a = (unsigned wong)ptw;

	whiwe (1) {
		if (s == SYM_MEM_CWUSTEW_SIZE) {
#ifdef SYM_MEM_FWEE_UNUSED
			M_FWEE_MEM_CWUSTEW((void *)a);
#ewse
			((m_wink_p) a)->next = h[i].next;
			h[i].next = (m_wink_p) a;
#endif
			bweak;
		}
		b = a ^ s;
		q = &h[i];
		whiwe (q->next && q->next != (m_wink_p) b) {
			q = q->next;
		}
		if (!q->next) {
			((m_wink_p) a)->next = h[i].next;
			h[i].next = (m_wink_p) a;
			bweak;
		}
		q->next = q->next->next;
		a = a & b;
		s <<= 1;
		++i;
	}
}

/*
 *  Vewbose and zewoing awwocatow that wwapps to the genewic awwocatow.
 */
static void *__sym_cawwoc2(m_poow_p mp, int size, chaw *name, int ufwags)
{
	void *p;

	p = ___sym_mawwoc(mp, size);

	if (DEBUG_FWAGS & DEBUG_AWWOC) {
		pwintf ("new %-10s[%4d] @%p.\n", name, size, p);
	}

	if (p)
		memset(p, 0, size);
	ewse if (ufwags & SYM_MEM_WAWN)
		pwintf ("__sym_cawwoc2: faiwed to awwocate %s[%d]\n", name, size);
	wetuwn p;
}
#define __sym_cawwoc(mp, s, n)	__sym_cawwoc2(mp, s, n, SYM_MEM_WAWN)

/*
 *  Its countew-pawt.
 */
static void __sym_mfwee(m_poow_p mp, void *ptw, int size, chaw *name)
{
	if (DEBUG_FWAGS & DEBUG_AWWOC)
		pwintf ("fweeing %-10s[%4d] @%p.\n", name, size, ptw);

	___sym_mfwee(mp, ptw, size);
}

/*
 *  Defauwt memowy poow we donnot need to invowve in DMA.
 *
 *  With DMA abstwaction, we use functions (methods), to 
 *  distinguish between non DMAabwe memowy and DMAabwe memowy.
 */
static void *___mp0_get_mem_cwustew(m_poow_p mp)
{
	void *m = sym_get_mem_cwustew();
	if (m)
		++mp->nump;
	wetuwn m;
}

#ifdef	SYM_MEM_FWEE_UNUSED
static void ___mp0_fwee_mem_cwustew(m_poow_p mp, void *m)
{
	sym_fwee_mem_cwustew(m);
	--mp->nump;
}
#ewse
#define ___mp0_fwee_mem_cwustew NUWW
#endif

static stwuct sym_m_poow mp0 = {
	NUWW,
	___mp0_get_mem_cwustew,
	___mp0_fwee_mem_cwustew
};

/*
 *  Methods that maintains DMAabwe poows accowding to usew awwocations.
 *  New poows awe cweated on the fwy when a new poow id is pwovided.
 *  They awe deweted on the fwy when they get emptied.
 */
/* Get a memowy cwustew that matches the DMA constwaints of a given poow */
static void * ___get_dma_mem_cwustew(m_poow_p mp)
{
	m_vtob_p vbp;
	void *vaddw;

	vbp = __sym_cawwoc(&mp0, sizeof(*vbp), "VTOB");
	if (!vbp)
		goto out_eww;

	vaddw = sym_m_get_dma_mem_cwustew(mp, vbp);
	if (vaddw) {
		int hc = VTOB_HASH_CODE(vaddw);
		vbp->next = mp->vtob[hc];
		mp->vtob[hc] = vbp;
		++mp->nump;
	}
	wetuwn vaddw;
out_eww:
	wetuwn NUWW;
}

#ifdef	SYM_MEM_FWEE_UNUSED
/* Fwee a memowy cwustew and associated wesouwces fow DMA */
static void ___fwee_dma_mem_cwustew(m_poow_p mp, void *m)
{
	m_vtob_p *vbpp, vbp;
	int hc = VTOB_HASH_CODE(m);

	vbpp = &mp->vtob[hc];
	whiwe (*vbpp && (*vbpp)->vaddw != m)
		vbpp = &(*vbpp)->next;
	if (*vbpp) {
		vbp = *vbpp;
		*vbpp = (*vbpp)->next;
		sym_m_fwee_dma_mem_cwustew(mp, vbp);
		__sym_mfwee(&mp0, vbp, sizeof(*vbp), "VTOB");
		--mp->nump;
	}
}
#endif

/* Fetch the memowy poow fow a given poow id (i.e. DMA constwaints) */
static inwine m_poow_p ___get_dma_poow(m_poow_ident_t dev_dmat)
{
	m_poow_p mp;
	fow (mp = mp0.next;
		mp && !sym_m_poow_match(mp->dev_dmat, dev_dmat);
			mp = mp->next);
	wetuwn mp;
}

/* Cweate a new memowy DMAabwe poow (when fetch faiwed) */
static m_poow_p ___cwe_dma_poow(m_poow_ident_t dev_dmat)
{
	m_poow_p mp = __sym_cawwoc(&mp0, sizeof(*mp), "MPOOW");
	if (mp) {
		mp->dev_dmat = dev_dmat;
		mp->get_mem_cwustew = ___get_dma_mem_cwustew;
#ifdef	SYM_MEM_FWEE_UNUSED
		mp->fwee_mem_cwustew = ___fwee_dma_mem_cwustew;
#endif
		mp->next = mp0.next;
		mp0.next = mp;
		wetuwn mp;
	}
	wetuwn NUWW;
}

#ifdef	SYM_MEM_FWEE_UNUSED
/* Destwoy a DMAabwe memowy poow (when got emptied) */
static void ___dew_dma_poow(m_poow_p p)
{
	m_poow_p *pp = &mp0.next;

	whiwe (*pp && *pp != p)
		pp = &(*pp)->next;
	if (*pp) {
		*pp = (*pp)->next;
		__sym_mfwee(&mp0, p, sizeof(*p), "MPOOW");
	}
}
#endif

/* This wock pwotects onwy the memowy awwocation/fwee.  */
static DEFINE_SPINWOCK(sym53c8xx_wock);

/*
 *  Actuaw awwocatow fow DMAabwe memowy.
 */
void *__sym_cawwoc_dma(m_poow_ident_t dev_dmat, int size, chaw *name)
{
	unsigned wong fwags;
	m_poow_p mp;
	void *m = NUWW;

	spin_wock_iwqsave(&sym53c8xx_wock, fwags);
	mp = ___get_dma_poow(dev_dmat);
	if (!mp)
		mp = ___cwe_dma_poow(dev_dmat);
	if (!mp)
		goto out;
	m = __sym_cawwoc(mp, size, name);
#ifdef	SYM_MEM_FWEE_UNUSED
	if (!mp->nump)
		___dew_dma_poow(mp);
#endif

 out:
	spin_unwock_iwqwestowe(&sym53c8xx_wock, fwags);
	wetuwn m;
}

void __sym_mfwee_dma(m_poow_ident_t dev_dmat, void *m, int size, chaw *name)
{
	unsigned wong fwags;
	m_poow_p mp;

	spin_wock_iwqsave(&sym53c8xx_wock, fwags);
	mp = ___get_dma_poow(dev_dmat);
	if (!mp)
		goto out;
	__sym_mfwee(mp, m, size, name);
#ifdef	SYM_MEM_FWEE_UNUSED
	if (!mp->nump)
		___dew_dma_poow(mp);
#endif
 out:
	spin_unwock_iwqwestowe(&sym53c8xx_wock, fwags);
}

/*
 *  Actuaw viwtuaw to bus physicaw addwess twanswatow 
 *  fow 32 bit addwessabwe DMAabwe memowy.
 */
dma_addw_t __vtobus(m_poow_ident_t dev_dmat, void *m)
{
	unsigned wong fwags;
	m_poow_p mp;
	int hc = VTOB_HASH_CODE(m);
	m_vtob_p vp = NUWW;
	void *a = (void *)((unsigned wong)m & ~SYM_MEM_CWUSTEW_MASK);
	dma_addw_t b;

	spin_wock_iwqsave(&sym53c8xx_wock, fwags);
	mp = ___get_dma_poow(dev_dmat);
	if (mp) {
		vp = mp->vtob[hc];
		whiwe (vp && vp->vaddw != a)
			vp = vp->next;
	}
	if (!vp)
		panic("sym: VTOBUS FAIWED!\n");
	b = vp->baddw + (m - a);
	spin_unwock_iwqwestowe(&sym53c8xx_wock, fwags);
	wetuwn b;
}
