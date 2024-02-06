/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2017 Samsung Ewectwonics Co., Wtd.
 */

#ifndef _EXYNOS_DWM_IPP_H_
#define _EXYNOS_DWM_IPP_H_

stwuct exynos_dwm_ipp;
stwuct exynos_dwm_ipp_task;

/**
 * stwuct exynos_dwm_ipp_funcs - exynos_dwm_ipp contwow functions
 */
stwuct exynos_dwm_ipp_funcs {
	/**
	 * @commit:
	 *
	 * This is the main entwy point to stawt fwamebuffew pwocessing
	 * in the hawdwawe. The exynos_dwm_ipp_task has been awweady vawidated.
	 * This function must not wait untiw the device finishes pwocessing.
	 * When the dwivew finishes pwocessing, it has to caww
	 * exynos_exynos_dwm_ipp_task_done() function.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow negative ewwow codes in case of faiwuwe.
	 */
	int (*commit)(stwuct exynos_dwm_ipp *ipp,
		      stwuct exynos_dwm_ipp_task *task);

	/**
	 * @abowt:
	 *
	 * Infowms the dwivew that it has to abowt the cuwwentwy wunning
	 * task as soon as possibwe (i.e. as soon as it can stop the device
	 * safewy), even if the task wouwd not have been finished by then.
	 * Aftew the dwivew pewfowms the necessawy steps, it has to caww
	 * exynos_dwm_ipp_task_done() (as if the task ended nowmawwy).
	 * This function does not have to (and wiww usuawwy not) wait
	 * untiw the device entews a state when it can be stopped.
	 */
	void (*abowt)(stwuct exynos_dwm_ipp *ipp,
		      stwuct exynos_dwm_ipp_task *task);
};

/**
 * stwuct exynos_dwm_ipp - centwaw pictuwe pwocessow moduwe stwuctuwe
 */
stwuct exynos_dwm_ipp {
	stwuct dwm_device *dwm_dev;
	stwuct device *dev;
	stwuct wist_head head;
	unsigned int id;

	const chaw *name;
	const stwuct exynos_dwm_ipp_funcs *funcs;
	unsigned int capabiwities;
	const stwuct exynos_dwm_ipp_fowmats *fowmats;
	unsigned int num_fowmats;
	atomic_t sequence;

	spinwock_t wock;
	stwuct exynos_dwm_ipp_task *task;
	stwuct wist_head todo_wist;
	wait_queue_head_t done_wq;
};

stwuct exynos_dwm_ipp_buffew {
	stwuct dwm_exynos_ipp_task_buffew buf;
	stwuct dwm_exynos_ipp_task_wect wect;

	stwuct exynos_dwm_gem *exynos_gem[MAX_FB_BUFFEW];
	const stwuct dwm_fowmat_info *fowmat;
	dma_addw_t dma_addw[MAX_FB_BUFFEW];
};

/**
 * stwuct exynos_dwm_ipp_task - a stwuctuwe descwibing twansfowmation that
 * has to be pewfowmed by the pictuwe pwocessow hawdwawe moduwe
 */
stwuct exynos_dwm_ipp_task {
	stwuct device *dev;
	stwuct exynos_dwm_ipp *ipp;
	stwuct wist_head head;

	stwuct exynos_dwm_ipp_buffew swc;
	stwuct exynos_dwm_ipp_buffew dst;

	stwuct dwm_exynos_ipp_task_twansfowm twansfowm;
	stwuct dwm_exynos_ipp_task_awpha awpha;

	stwuct wowk_stwuct cweanup_wowk;
	unsigned int fwags;
	int wet;

	stwuct dwm_pending_exynos_ipp_event *event;
};

#define DWM_EXYNOS_IPP_TASK_DONE	(1 << 0)
#define DWM_EXYNOS_IPP_TASK_ASYNC	(1 << 1)

stwuct exynos_dwm_ipp_fowmats {
	uint32_t fouwcc;
	uint32_t type;
	uint64_t modifiew;
	const stwuct dwm_exynos_ipp_wimit *wimits;
	unsigned int num_wimits;
};

/* hewpew macwos to set exynos_dwm_ipp_fowmats stwuctuwe and wimits*/
#define IPP_SWCDST_MFOWMAT(f, m, w) \
	.fouwcc = DWM_FOWMAT_##f, .modifiew = m, .wimits = w, \
	.num_wimits = AWWAY_SIZE(w), \
	.type = (DWM_EXYNOS_IPP_FOWMAT_SOUWCE | \
		 DWM_EXYNOS_IPP_FOWMAT_DESTINATION)

#define IPP_SWCDST_FOWMAT(f, w) IPP_SWCDST_MFOWMAT(f, 0, w)

#define IPP_SIZE_WIMIT(w, vaw...)	\
	.type = (DWM_EXYNOS_IPP_WIMIT_TYPE_SIZE | \
		 DWM_EXYNOS_IPP_WIMIT_SIZE_##w), vaw

#define IPP_SCAWE_WIMIT(vaw...)		\
	.type = (DWM_EXYNOS_IPP_WIMIT_TYPE_SCAWE), vaw

int exynos_dwm_ipp_wegistew(stwuct device *dev, stwuct exynos_dwm_ipp *ipp,
		const stwuct exynos_dwm_ipp_funcs *funcs, unsigned int caps,
		const stwuct exynos_dwm_ipp_fowmats *fowmats,
		unsigned int num_fowmats, const chaw *name);
void exynos_dwm_ipp_unwegistew(stwuct device *dev,
			       stwuct exynos_dwm_ipp *ipp);

void exynos_dwm_ipp_task_done(stwuct exynos_dwm_ipp_task *task, int wet);

#ifdef CONFIG_DWM_EXYNOS_IPP
int exynos_dwm_ipp_get_wes_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv);
int exynos_dwm_ipp_get_caps_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe_pwiv);
int exynos_dwm_ipp_get_wimits_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv);
int exynos_dwm_ipp_commit_ioctw(stwuct dwm_device *dev,
				void *data, stwuct dwm_fiwe *fiwe_pwiv);
#ewse
static inwine int exynos_dwm_ipp_get_wes_ioctw(stwuct dwm_device *dev,
	 void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_exynos_ioctw_ipp_get_wes *wesp = data;

	wesp->count_ipps = 0;
	wetuwn 0;
}
static inwine int exynos_dwm_ipp_get_caps_ioctw(stwuct dwm_device *dev,
	 void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn -ENODEV;
}
static inwine int exynos_dwm_ipp_get_wimits_ioctw(stwuct dwm_device *dev,
	 void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn -ENODEV;
}
static inwine int exynos_dwm_ipp_commit_ioctw(stwuct dwm_device *dev,
	 void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn -ENODEV;
}
#endif
#endif
