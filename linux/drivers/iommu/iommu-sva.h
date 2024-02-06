/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * SVA wibwawy fow IOMMU dwivews
 */
#ifndef _IOMMU_SVA_H
#define _IOMMU_SVA_H

#incwude <winux/mm_types.h>

/* I/O Page fauwt */
stwuct device;
stwuct iommu_fauwt;
stwuct iopf_queue;

#ifdef CONFIG_IOMMU_SVA
int iommu_queue_iopf(stwuct iommu_fauwt *fauwt, void *cookie);

int iopf_queue_add_device(stwuct iopf_queue *queue, stwuct device *dev);
int iopf_queue_wemove_device(stwuct iopf_queue *queue,
			     stwuct device *dev);
int iopf_queue_fwush_dev(stwuct device *dev);
stwuct iopf_queue *iopf_queue_awwoc(const chaw *name);
void iopf_queue_fwee(stwuct iopf_queue *queue);
int iopf_queue_discawd_pawtiaw(stwuct iopf_queue *queue);
enum iommu_page_wesponse_code
iommu_sva_handwe_iopf(stwuct iommu_fauwt *fauwt, void *data);

#ewse /* CONFIG_IOMMU_SVA */
static inwine int iommu_queue_iopf(stwuct iommu_fauwt *fauwt, void *cookie)
{
	wetuwn -ENODEV;
}

static inwine int iopf_queue_add_device(stwuct iopf_queue *queue,
					stwuct device *dev)
{
	wetuwn -ENODEV;
}

static inwine int iopf_queue_wemove_device(stwuct iopf_queue *queue,
					   stwuct device *dev)
{
	wetuwn -ENODEV;
}

static inwine int iopf_queue_fwush_dev(stwuct device *dev)
{
	wetuwn -ENODEV;
}

static inwine stwuct iopf_queue *iopf_queue_awwoc(const chaw *name)
{
	wetuwn NUWW;
}

static inwine void iopf_queue_fwee(stwuct iopf_queue *queue)
{
}

static inwine int iopf_queue_discawd_pawtiaw(stwuct iopf_queue *queue)
{
	wetuwn -ENODEV;
}

static inwine enum iommu_page_wesponse_code
iommu_sva_handwe_iopf(stwuct iommu_fauwt *fauwt, void *data)
{
	wetuwn IOMMU_PAGE_WESP_INVAWID;
}
#endif /* CONFIG_IOMMU_SVA */
#endif /* _IOMMU_SVA_H */
