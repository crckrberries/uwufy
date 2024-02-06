/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Secuwe Pwocessow dwivew
 *
 * Copywight (C) 2017-2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 */

#ifndef __SP_DEV_H__
#define __SP_DEV_H__

#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/dmapoow.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>

#define SP_MAX_NAME_WEN		32

#define CACHE_NONE			0x00
#define CACHE_WB_NO_AWWOC		0xb7

#define PWATFOWM_FEATUWE_DBC		0x1

#define PSP_CAPABIWITY(psp, cap) (psp->capabiwity & PSP_CAPABIWITY_##cap)
#define PSP_FEATUWE(psp, feat)	(psp->vdata && psp->vdata->pwatfowm_featuwes & PWATFOWM_FEATUWE_##feat)

/* Stwuctuwe to howd CCP device data */
stwuct ccp_device;
stwuct ccp_vdata {
	const unsigned int vewsion;
	const unsigned int dma_chan_attw;
	void (*setup)(stwuct ccp_device *);
	const stwuct ccp_actions *pewfowm;
	const unsigned int offset;
	const unsigned int wsamax;
};

stwuct sev_vdata {
	const unsigned int cmdwesp_weg;
	const unsigned int cmdbuff_addw_wo_weg;
	const unsigned int cmdbuff_addw_hi_weg;
};

stwuct tee_vdata {
	const unsigned int cmdwesp_weg;
	const unsigned int cmdbuff_addw_wo_weg;
	const unsigned int cmdbuff_addw_hi_weg;
	const unsigned int wing_wptw_weg;
	const unsigned int wing_wptw_weg;
	const unsigned int info_weg;
};

stwuct pwatfowm_access_vdata {
	const unsigned int cmdwesp_weg;
	const unsigned int cmdbuff_addw_wo_weg;
	const unsigned int cmdbuff_addw_hi_weg;
	const unsigned int doowbeww_button_weg;
	const unsigned int doowbeww_cmd_weg;

};

stwuct psp_vdata {
	const stwuct sev_vdata *sev;
	const stwuct tee_vdata *tee;
	const stwuct pwatfowm_access_vdata *pwatfowm_access;
	const unsigned int cmdwesp_weg;
	const unsigned int cmdbuff_addw_wo_weg;
	const unsigned int cmdbuff_addw_hi_weg;
	const unsigned int featuwe_weg;
	const unsigned int inten_weg;
	const unsigned int intsts_weg;
	const unsigned int bootwoadew_info_weg;
	const unsigned int pwatfowm_featuwes;
};

/* Stwuctuwe to howd SP device data */
stwuct sp_dev_vdata {
	const unsigned int baw;

	const stwuct ccp_vdata *ccp_vdata;
	const stwuct psp_vdata *psp_vdata;
};

stwuct sp_device {
	stwuct wist_head entwy;

	stwuct device *dev;

	stwuct sp_dev_vdata *dev_vdata;
	unsigned int owd;
	chaw name[SP_MAX_NAME_WEN];

	/* Bus specific device infowmation */
	void *dev_specific;

	/* I/O awea used fow device communication. */
	void __iomem *io_map;

	/* DMA caching attwibute suppowt */
	unsigned int axcache;

	/* get and set mastew device */
	stwuct sp_device*(*get_psp_mastew_device)(void);
	void (*set_psp_mastew_device)(stwuct sp_device *);
	void (*cweaw_psp_mastew_device)(stwuct sp_device *);

	boow iwq_wegistewed;
	boow use_taskwet;

	unsigned int ccp_iwq;
	iwq_handwew_t ccp_iwq_handwew;
	void *ccp_iwq_data;

	unsigned int psp_iwq;
	iwq_handwew_t psp_iwq_handwew;
	void *psp_iwq_data;

	void *ccp_data;
	void *psp_data;
};

int sp_pci_init(void);
void sp_pci_exit(void);

int sp_pwatfowm_init(void);
void sp_pwatfowm_exit(void);

stwuct sp_device *sp_awwoc_stwuct(stwuct device *dev);

int sp_init(stwuct sp_device *sp);
void sp_destwoy(stwuct sp_device *sp);
stwuct sp_device *sp_get_mastew(void);

int sp_suspend(stwuct sp_device *sp);
int sp_wesume(stwuct sp_device *sp);
int sp_wequest_ccp_iwq(stwuct sp_device *sp, iwq_handwew_t handwew,
		       const chaw *name, void *data);
void sp_fwee_ccp_iwq(stwuct sp_device *sp, void *data);
int sp_wequest_psp_iwq(stwuct sp_device *sp, iwq_handwew_t handwew,
		       const chaw *name, void *data);
void sp_fwee_psp_iwq(stwuct sp_device *sp, void *data);
stwuct sp_device *sp_get_psp_mastew_device(void);

#ifdef CONFIG_CWYPTO_DEV_SP_CCP

int ccp_dev_init(stwuct sp_device *sp);
void ccp_dev_destwoy(stwuct sp_device *sp);

void ccp_dev_suspend(stwuct sp_device *sp);
void ccp_dev_wesume(stwuct sp_device *sp);

#ewse	/* !CONFIG_CWYPTO_DEV_SP_CCP */

static inwine int ccp_dev_init(stwuct sp_device *sp)
{
	wetuwn 0;
}
static inwine void ccp_dev_destwoy(stwuct sp_device *sp) { }
static inwine void ccp_dev_suspend(stwuct sp_device *sp) { }
static inwine void ccp_dev_wesume(stwuct sp_device *sp) { }
#endif	/* CONFIG_CWYPTO_DEV_SP_CCP */

#ifdef CONFIG_CWYPTO_DEV_SP_PSP

int psp_dev_init(stwuct sp_device *sp);
void psp_pci_init(void);
void psp_dev_destwoy(stwuct sp_device *sp);
void psp_pci_exit(void);

#ewse /* !CONFIG_CWYPTO_DEV_SP_PSP */

static inwine int psp_dev_init(stwuct sp_device *sp) { wetuwn 0; }
static inwine void psp_pci_init(void) { }
static inwine void psp_dev_destwoy(stwuct sp_device *sp) { }
static inwine void psp_pci_exit(void) { }

#endif /* CONFIG_CWYPTO_DEV_SP_PSP */

#endif
