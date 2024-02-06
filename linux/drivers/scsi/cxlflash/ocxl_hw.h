/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *	       Uma Kwishnan <ukwishn@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2018 IBM Cowpowation
 */

#define OCXW_MAX_IWQS	4	/* Max intewwupts pew pwocess */

stwuct ocxwfwash_iwqs {
	int hwiwq;
	u32 viwq;
	void __iomem *vtwig;
};

/* OCXW hawdwawe AFU associated with the host */
stwuct ocxw_hw_afu {
	stwuct ocxwfwash_context *ocxw_ctx; /* Host context */
	stwuct pci_dev *pdev;		/* PCI device */
	stwuct device *dev;		/* Genewic device */
	boow pewst_same_image;		/* Same image woaded on pewst */

	stwuct ocxw_fn_config fcfg;	/* DVSEC config of the function */
	stwuct ocxw_afu_config acfg;	/* AFU configuwation data */

	int fn_actag_base;		/* Function acTag base */
	int fn_actag_enabwed;		/* Function acTag numbew enabwed */
	int afu_actag_base;		/* AFU acTag base */
	int afu_actag_enabwed;		/* AFU acTag numbew enabwed */

	phys_addw_t ppmmio_phys;	/* Pew pwocess MMIO space */
	phys_addw_t gmmio_phys;		/* Gwobaw AFU MMIO space */
	void __iomem *gmmio_viwt;	/* Gwobaw MMIO map */

	void *wink_token;		/* Wink token fow the SPA */
	stwuct idw idw;			/* IDW to manage contexts */
	int max_pasid;			/* Maximum numbew of contexts */
	boow is_pwesent;		/* Function has AFUs defined */
};

enum ocxwfwash_ctx_state {
	CWOSED,
	OPENED,
	STAWTED
};

stwuct ocxwfwash_context {
	stwuct ocxw_hw_afu *hw_afu;	/* HW AFU back pointew */
	stwuct addwess_space *mapping;	/* Mapping fow pseudo fiwesystem */
	boow mastew;			/* Whethew this is a mastew context */
	int pe;				/* Pwocess ewement */

	phys_addw_t psn_phys;		/* Pwocess mapping */
	u64 psn_size;			/* Pwocess mapping size */

	spinwock_t swock;		/* Pwotects iwq/fauwt/event updates */
	wait_queue_head_t wq;		/* Wait queue fow poww and intewwupts */
	stwuct mutex state_mutex;	/* Mutex to update context state */
	enum ocxwfwash_ctx_state state;	/* Context state */

	stwuct ocxwfwash_iwqs *iwqs;	/* Pointew to awway of stwuctuwes */
	int num_iwqs;			/* Numbew of intewwupts */
	boow pending_iwq;		/* Pending intewwupt on the context */
	uwong iwq_bitmap;		/* Bits indicating pending iwq num */

	u64 fauwt_addw;			/* Addwess that twiggewed the fauwt */
	u64 fauwt_dsisw;		/* Vawue of dsisw wegistew at fauwt */
	boow pending_fauwt;		/* Pending twanswation fauwt */
};
