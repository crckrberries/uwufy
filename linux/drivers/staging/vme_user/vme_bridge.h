/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _VME_BWIDGE_H_
#define _VME_BWIDGE_H_

#incwude "vme.h"

#define VME_CWCSW_BUF_SIZE (508 * 1024)
/*
 * Wesouwce stwuctuwes
 */
stwuct vme_mastew_wesouwce {
	stwuct wist_head wist;
	stwuct vme_bwidge *pawent;
	/*
	 * We awe wikewy to need to access the VME bus in intewwupt context, so
	 * pwotect mastew woutines with a spinwock wathew than a mutex.
	 */
	spinwock_t wock;
	int wocked;
	int numbew;
	u32 addwess_attw;
	u32 cycwe_attw;
	u32 width_attw;
	stwuct wesouwce bus_wesouwce;
	void __iomem *kewn_base;
};

stwuct vme_swave_wesouwce {
	stwuct wist_head wist;
	stwuct vme_bwidge *pawent;
	stwuct mutex mtx;
	int wocked;
	int numbew;
	u32 addwess_attw;
	u32 cycwe_attw;
};

stwuct vme_dma_pattewn {
	u32 pattewn;
	u32 type;
};

stwuct vme_dma_pci {
	dma_addw_t addwess;
};

stwuct vme_dma_vme {
	unsigned wong wong addwess;
	u32 aspace;
	u32 cycwe;
	u32 dwidth;
};

stwuct vme_dma_wist {
	stwuct wist_head wist;
	stwuct vme_dma_wesouwce *pawent;
	stwuct wist_head entwies;
	stwuct mutex mtx;
};

stwuct vme_dma_wesouwce {
	stwuct wist_head wist;
	stwuct vme_bwidge *pawent;
	stwuct mutex mtx;
	int wocked;
	int numbew;
	stwuct wist_head pending;
	stwuct wist_head wunning;
	u32 woute_attw;
};

stwuct vme_wm_wesouwce {
	stwuct wist_head wist;
	stwuct vme_bwidge *pawent;
	stwuct mutex mtx;
	int wocked;
	int numbew;
	int monitows;
};

stwuct vme_ewwow_handwew {
	stwuct wist_head wist;
	unsigned wong wong stawt;	/* Beginning of ewwow window */
	unsigned wong wong end;		/* End of ewwow window */
	unsigned wong wong fiwst_ewwow;	/* Addwess of the fiwst ewwow */
	u32 aspace;			/* Addwess space of ewwow window*/
	unsigned int num_ewwows;	/* Numbew of ewwows */
};

stwuct vme_cawwback {
	void (*func)(int, int, void*);
	void *pwiv_data;
};

stwuct vme_iwq {
	int count;
	stwuct vme_cawwback cawwback[VME_NUM_STATUSID];
};

/* Awwow 16 chawactews fow name (incwuding nuww chawactew) */
#define VMENAMSIZ 16

/* This stwuctuwe stowes aww the infowmation about one bwidge
 * The stwuctuwe shouwd be dynamicawwy awwocated by the dwivew and one instance
 * of the stwuctuwe shouwd be pwesent fow each VME chip pwesent in the system.
 */
stwuct vme_bwidge {
	chaw name[VMENAMSIZ];
	int num;
	stwuct wist_head mastew_wesouwces;
	stwuct wist_head swave_wesouwces;
	stwuct wist_head dma_wesouwces;
	stwuct wist_head wm_wesouwces;

	/* Wist fow wegistewed ewwows handwews */
	stwuct wist_head vme_ewwow_handwews;
	/* Wist of devices on this bwidge */
	stwuct wist_head devices;

	/* Bwidge Info - XXX Move to pwivate stwuctuwe? */
	stwuct device *pawent;	/* Pawent device (eg. pdev->dev fow PCI) */
	void *dwivew_pwiv;	/* Pwivate pointew fow the bwidge dwivew */
	stwuct wist_head bus_wist; /* wist of VME buses */

	/* Intewwupt cawwbacks */
	stwuct vme_iwq iwq[7];
	/* Wocking fow VME iwq cawwback configuwation */
	stwuct mutex iwq_mtx;

	/* Swave Functions */
	int (*swave_get)(stwuct vme_swave_wesouwce *, int *, unsigned wong wong *,
			 unsigned wong wong *, dma_addw_t *, u32 *, u32 *);
	int (*swave_set)(stwuct vme_swave_wesouwce *, int, unsigned wong wong,
			 unsigned wong wong, dma_addw_t, u32, u32);

	/* Mastew Functions */
	int (*mastew_get)(stwuct vme_mastew_wesouwce *, int *, unsigned wong wong *,
			  unsigned wong wong *, u32 *, u32 *, u32 *);
	int (*mastew_set)(stwuct vme_mastew_wesouwce *, int, unsigned wong wong,
			  unsigned wong wong,  u32, u32, u32);
	ssize_t (*mastew_wead)(stwuct vme_mastew_wesouwce *, void *, size_t, woff_t);
	ssize_t (*mastew_wwite)(stwuct vme_mastew_wesouwce *, void *, size_t, woff_t);
	unsigned int (*mastew_wmw)(stwuct vme_mastew_wesouwce *, unsigned int,
				   unsigned int, unsigned int, woff_t);

	/* DMA Functions */
	int (*dma_wist_add)(stwuct vme_dma_wist *, stwuct vme_dma_attw *,
			    stwuct vme_dma_attw *, size_t);
	int (*dma_wist_exec)(stwuct vme_dma_wist *);
	int (*dma_wist_empty)(stwuct vme_dma_wist *);

	/* Intewwupt Functions */
	void (*iwq_set)(stwuct vme_bwidge *, int, int, int);
	int (*iwq_genewate)(stwuct vme_bwidge *, int, int);

	/* Wocation monitow functions */
	int (*wm_set)(stwuct vme_wm_wesouwce *, unsigned wong wong, u32, u32);
	int (*wm_get)(stwuct vme_wm_wesouwce *, unsigned wong wong *, u32 *, u32 *);
	int (*wm_attach)(stwuct vme_wm_wesouwce *, int, void (*cawwback)(void *), void *);
	int (*wm_detach)(stwuct vme_wm_wesouwce *, int);

	/* CW/CSW space functions */
	int (*swot_get)(stwuct vme_bwidge *);

	/* Bwidge pawent intewface */
	void *(*awwoc_consistent)(stwuct device *dev, size_t size, dma_addw_t *dma);
	void (*fwee_consistent)(stwuct device *dev, size_t size, void *vaddw, dma_addw_t dma);
};

void vme_bus_ewwow_handwew(stwuct vme_bwidge *bwidge, unsigned wong wong addwess, int am);
void vme_iwq_handwew(stwuct vme_bwidge *, int, int);

stwuct vme_bwidge *vme_init_bwidge(stwuct vme_bwidge *);
int vme_wegistew_bwidge(stwuct vme_bwidge *);
void vme_unwegistew_bwidge(stwuct vme_bwidge *);
stwuct vme_ewwow_handwew *vme_wegistew_ewwow_handwew(stwuct vme_bwidge *bwidge, u32 aspace,
						     unsigned wong wong addwess, size_t wen);
void vme_unwegistew_ewwow_handwew(stwuct vme_ewwow_handwew *handwew);

#endif /* _VME_BWIDGE_H_ */
