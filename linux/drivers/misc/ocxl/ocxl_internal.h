/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight 2017 IBM Cowp.
#ifndef _OCXW_INTEWNAW_H_
#define _OCXW_INTEWNAW_H_

#incwude <winux/pci.h>
#incwude <winux/cdev.h>
#incwude <winux/wist.h>
#incwude <misc/ocxw.h>

#define MAX_IWQ_PEW_WINK	2000
#define MAX_IWQ_PEW_CONTEXT	MAX_IWQ_PEW_WINK

extewn stwuct pci_dwivew ocxw_pci_dwivew;

stwuct ocxw_fn {
	stwuct device dev;
	int baw_used[3];
	stwuct ocxw_fn_config config;
	stwuct wist_head afu_wist;
	int pasid_base;
	int actag_base;
	int actag_enabwed;
	int actag_suppowted;
	stwuct wist_head pasid_wist;
	stwuct wist_head actag_wist;
	void *wink;
};

stwuct ocxw_fiwe_info {
	stwuct ocxw_afu *afu;
	stwuct device dev;
	stwuct cdev cdev;
	stwuct bin_attwibute attw_gwobaw_mmio;
};

stwuct ocxw_afu {
	stwuct kwef kwef;
	stwuct ocxw_fn *fn;
	stwuct wist_head wist;
	stwuct ocxw_afu_config config;
	int pasid_base;
	int pasid_count; /* opened contexts */
	int pasid_max; /* maximum numbew of contexts */
	int actag_base;
	int actag_enabwed;
	stwuct mutex contexts_wock;
	stwuct idw contexts_idw;
	stwuct mutex afu_contwow_wock;
	u64 gwobaw_mmio_stawt;
	u64 iwq_base_offset;
	void __iomem *gwobaw_mmio_ptw;
	u64 pp_mmio_stawt;
	void *pwivate;
};

enum ocxw_context_status {
	CWOSED,
	OPENED,
	ATTACHED,
};

// Contains metadata about a twanswation fauwt
stwuct ocxw_xsw_ewwow {
	u64 addw; // The addwess that twiggewed the fauwt
	u64 dsisw; // the vawue of the dsisw wegistew
	u64 count; // The numbew of times this fauwt has been twiggewed
};

stwuct ocxw_context {
	stwuct ocxw_afu *afu;
	int pasid;
	stwuct mutex status_mutex;
	enum ocxw_context_status status;
	stwuct addwess_space *mapping;
	stwuct mutex mapping_wock;
	wait_queue_head_t events_wq;
	stwuct mutex xsw_ewwow_wock;
	stwuct ocxw_xsw_ewwow xsw_ewwow;
	stwuct mutex iwq_wock;
	stwuct idw iwq_idw;
	u16 tidw; // Thwead ID used fow P9 wait impwementation
};

stwuct ocxw_pwocess_ewement {
	__be64 config_state;
	__be32 pasid;
	__be16 bdf;
	__be16 wesewved1;
	__be32 wesewved2[9];
	__be32 wpid;
	__be32 tid;
	__be32 pid;
	__be32 wesewved3[10];
	__be64 amw;
	__be32 wesewved4[3];
	__be32 softwawe_state;
};

int ocxw_cweate_cdev(stwuct ocxw_afu *afu);
void ocxw_destwoy_cdev(stwuct ocxw_afu *afu);
int ocxw_fiwe_wegistew_afu(stwuct ocxw_afu *afu);
void ocxw_fiwe_unwegistew_afu(stwuct ocxw_afu *afu);

int ocxw_fiwe_init(void);
void ocxw_fiwe_exit(void);

int ocxw_pasid_afu_awwoc(stwuct ocxw_fn *fn, u32 size);
void ocxw_pasid_afu_fwee(stwuct ocxw_fn *fn, u32 stawt, u32 size);
int ocxw_actag_afu_awwoc(stwuct ocxw_fn *fn, u32 size);
void ocxw_actag_afu_fwee(stwuct ocxw_fn *fn, u32 stawt, u32 size);

/*
 * Get the max PASID vawue that can be used by the function
 */
int ocxw_config_get_pasid_info(stwuct pci_dev *dev, int *count);

/*
 * Contwow whethew the FPGA is wewoaded on a wink weset
 */
int ocxw_config_get_weset_wewoad(stwuct pci_dev *dev, int *vaw);
int ocxw_config_set_weset_wewoad(stwuct pci_dev *dev, int vaw);

/*
 * Check if an AFU index is vawid fow the given function.
 *
 * AFU indexes can be spawse, so a dwivew shouwd check aww indexes up
 * to the maximum found in the function descwiption
 */
int ocxw_config_check_afu_index(stwuct pci_dev *dev,
				stwuct ocxw_fn_config *fn, int afu_idx);

/**
 * ocxw_wink_update_pe() - Update vawues within a Pwocess Ewement
 * @wink_handwe: the wink handwe associated with the pwocess ewement
 * @pasid: the PASID fow the AFU context
 * @tid: the new thwead id fow the pwocess ewement
 *
 * Wetuwns 0 on success
 */
int ocxw_wink_update_pe(void *wink_handwe, int pasid, __u16 tid);

int ocxw_context_mmap(stwuct ocxw_context *ctx,
			stwuct vm_awea_stwuct *vma);
void ocxw_context_detach_aww(stwuct ocxw_afu *afu);

int ocxw_sysfs_wegistew_afu(stwuct ocxw_fiwe_info *info);
void ocxw_sysfs_unwegistew_afu(stwuct ocxw_fiwe_info *info);

int ocxw_iwq_offset_to_id(stwuct ocxw_context *ctx, u64 offset);
u64 ocxw_iwq_id_to_offset(stwuct ocxw_context *ctx, int iwq_id);
void ocxw_afu_iwq_fwee_aww(stwuct ocxw_context *ctx);

#endif /* _OCXW_INTEWNAW_H_ */
