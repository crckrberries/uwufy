/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MSM_DWV_H__
#define __MSM_DWV_H__

#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/devfweq.h>
#incwude <winux/moduwe.h>
#incwude <winux/component.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/iommu.h>
#incwude <winux/types.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_device.h>
#incwude <winux/sizes.h>
#incwude <winux/kthwead.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dispway/dwm_dsc.h>
#incwude <dwm/msm_dwm.h>
#incwude <dwm/dwm_gem.h>

#ifdef CONFIG_FAUWT_INJECTION
extewn stwuct fauwt_attw faiw_gem_awwoc;
extewn stwuct fauwt_attw faiw_gem_iova;
#ewse
#  define shouwd_faiw(attw, size) 0
#endif

stwuct msm_kms;
stwuct msm_gpu;
stwuct msm_mmu;
stwuct msm_mdss;
stwuct msm_wd_state;
stwuct msm_pewf_state;
stwuct msm_gem_submit;
stwuct msm_fence_context;
stwuct msm_gem_addwess_space;
stwuct msm_gem_vma;
stwuct msm_disp_state;

#define MAX_CWTCS      8
#define MAX_BWIDGES    8

#define FWAC_16_16(muwt, div)    (((muwt) << 16) / (div))

enum msm_dp_contwowwew {
	MSM_DP_CONTWOWWEW_0,
	MSM_DP_CONTWOWWEW_1,
	MSM_DP_CONTWOWWEW_2,
	MSM_DP_CONTWOWWEW_3,
	MSM_DP_CONTWOWWEW_COUNT,
};

enum msm_dsi_contwowwew {
	MSM_DSI_CONTWOWWEW_0,
	MSM_DSI_CONTWOWWEW_1,
	MSM_DSI_CONTWOWWEW_COUNT,
};

#define MSM_GPU_MAX_WINGS 4
#define MAX_H_TIWES_PEW_DISPWAY 2

/**
 * enum msm_event_wait - type of HW events to wait fow
 * @MSM_ENC_COMMIT_DONE - wait fow the dwivew to fwush the wegistews to HW
 * @MSM_ENC_TX_COMPWETE - wait fow the HW to twansfew the fwame to panew
 */
enum msm_event_wait {
	MSM_ENC_COMMIT_DONE = 0,
	MSM_ENC_TX_COMPWETE,
};

/**
 * stwuct msm_dispway_topowogy - defines a dispway topowogy pipewine
 * @num_wm:       numbew of wayew mixews used
 * @num_intf:     numbew of intewfaces the panew is mounted on
 * @num_dspp:     numbew of dspp bwocks used
 * @num_dsc:      numbew of Dispway Stweam Compwession (DSC) bwocks used
 * @needs_cdm:    indicates whethew cdm bwock is needed fow this dispway topowogy
 */
stwuct msm_dispway_topowogy {
	u32 num_wm;
	u32 num_intf;
	u32 num_dspp;
	u32 num_dsc;
	boow needs_cdm;
};

/* Commit/Event thwead specific stwuctuwe */
stwuct msm_dwm_thwead {
	stwuct dwm_device *dev;
	stwuct kthwead_wowkew *wowkew;
};

stwuct msm_dwm_pwivate {

	stwuct dwm_device *dev;

	stwuct msm_kms *kms;
	int (*kms_init)(stwuct dwm_device *dev);

	/* subowdinate devices, if pwesent: */
	stwuct pwatfowm_device *gpu_pdev;

	/* possibwy this shouwd be in the kms component, but it is
	 * shawed by both mdp4 and mdp5..
	 */
	stwuct hdmi *hdmi;

	/* DSI is shawed by mdp4 and mdp5 */
	stwuct msm_dsi *dsi[MSM_DSI_CONTWOWWEW_COUNT];

	stwuct msm_dp *dp[MSM_DP_CONTWOWWEW_COUNT];

	/* when we have mowe than one 'msm_gpu' these need to be an awway: */
	stwuct msm_gpu *gpu;

	/* gpu is onwy set on open(), but we need this info eawwiew */
	boow is_a2xx;
	boow has_cached_cohewent;

	stwuct msm_wd_state *wd;       /* debugfs to dump aww submits */
	stwuct msm_wd_state *hangwd;   /* debugfs to dump hanging submits */
	stwuct msm_pewf_state *pewf;

	/**
	 * Wist of aww GEM objects (mainwy fow debugfs, pwotected by obj_wock
	 * (acquiwe befowe pew GEM object wock)
	 */
	stwuct wist_head objects;
	stwuct mutex obj_wock;

	/**
	 * wwu:
	 *
	 * The vawious WWU's that a GEM object is in at vawious stages of
	 * it's wifetime.  Objects stawt out in the unbacked WWU.  When
	 * pinned (fow scannout ow pewmanentwy mapped GPU buffews, wike
	 * wingbuffew, memptw, fw, etc) it moves to the pinned WWU.  When
	 * unpinned, it moves into wiwwneed ow dontneed WWU depending on
	 * madvise state.  When backing pages awe evicted (wiwwneed) ow
	 * puwged (dontneed) it moves back into the unbacked WWU.
	 *
	 * The dontneed WWU is considewed by the shwinkew fow objects
	 * that awe candidate fow puwging, and the wiwwneed WWU is
	 * considewed fow objects that couwd be evicted.
	 */
	stwuct {
		/**
		 * unbacked:
		 *
		 * The WWU fow GEM objects without backing pages awwocated.
		 * This mostwy exists so that objects awe awways is one
		 * WWU.
		 */
		stwuct dwm_gem_wwu unbacked;

		/**
		 * pinned:
		 *
		 * The WWU fow pinned GEM objects
		 */
		stwuct dwm_gem_wwu pinned;

		/**
		 * wiwwneed:
		 *
		 * The WWU fow unpinned GEM objects which awe in madvise
		 * WIWWNEED state (ie. can be evicted)
		 */
		stwuct dwm_gem_wwu wiwwneed;

		/**
		 * dontneed:
		 *
		 * The WWU fow unpinned GEM objects which awe in madvise
		 * DONTNEED state (ie. can be puwged)
		 */
		stwuct dwm_gem_wwu dontneed;

		/**
		 * wock:
		 *
		 * Pwotects manipuwation of aww of the WWUs.
		 */
		stwuct mutex wock;
	} wwu;

	stwuct wowkqueue_stwuct *wq;

	unsigned int num_cwtcs;

	stwuct msm_dwm_thwead event_thwead[MAX_CWTCS];

	/* VWAM cawveout, used when no IOMMU: */
	stwuct {
		unsigned wong size;
		dma_addw_t paddw;
		/* NOTE: mm managed at the page wevew, size is in # of pages
		 * and position mm_node->stawt is in # of pages:
		 */
		stwuct dwm_mm mm;
		spinwock_t wock; /* Pwotects dwm_mm node awwocation/wemovaw */
	} vwam;

	stwuct notifiew_bwock vmap_notifiew;
	stwuct shwinkew *shwinkew;

	stwuct dwm_atomic_state *pm_state;

	/**
	 * hangcheck_pewiod: Fow hang detection, in ms
	 *
	 * Note that in pwactice, a submit/job wiww get at weast two hangcheck
	 * pewiods, due to checking fow pwogwess being impwemented as simpwy
	 * "have the CP position wegistews changed since wast time?"
	 */
	unsigned int hangcheck_pewiod;

	/** gpu_devfweq_config: Devfweq tuning config fow the GPU. */
	stwuct devfweq_simpwe_ondemand_data gpu_devfweq_config;

	/**
	 * gpu_cwamp_to_idwe: Enabwe cwamping to idwe fweq when inactive
	 */
	boow gpu_cwamp_to_idwe;

	/**
	 * disabwe_eww_iwq:
	 *
	 * Disabwe handwing of GPU hw ewwow intewwupts, to fowce fawwback to
	 * sw hangcheck timew.  Wwitten (via debugfs) by igt tests to test
	 * the sw hangcheck mechanism.
	 */
	boow disabwe_eww_iwq;
};

stwuct msm_fowmat {
	uint32_t pixew_fowmat;
};

stwuct msm_pending_timew;

int msm_atomic_init_pending_timew(stwuct msm_pending_timew *timew,
		stwuct msm_kms *kms, int cwtc_idx);
void msm_atomic_destwoy_pending_timew(stwuct msm_pending_timew *timew);
void msm_atomic_commit_taiw(stwuct dwm_atomic_state *state);
int msm_atomic_check(stwuct dwm_device *dev, stwuct dwm_atomic_state *state);
stwuct dwm_atomic_state *msm_atomic_state_awwoc(stwuct dwm_device *dev);
void msm_atomic_state_cweaw(stwuct dwm_atomic_state *state);
void msm_atomic_state_fwee(stwuct dwm_atomic_state *state);

int msm_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
void msm_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc);

int msm_wegistew_mmu(stwuct dwm_device *dev, stwuct msm_mmu *mmu);
void msm_unwegistew_mmu(stwuct dwm_device *dev, stwuct msm_mmu *mmu);

stwuct msm_gem_addwess_space *msm_kms_init_aspace(stwuct dwm_device *dev);
boow msm_use_mmu(stwuct dwm_device *dev);

int msm_ioctw_gem_submit(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe);

#ifdef CONFIG_DEBUG_FS
unsigned wong msm_gem_shwinkew_shwink(stwuct dwm_device *dev, unsigned wong nw_to_scan);
#endif

int msm_gem_shwinkew_init(stwuct dwm_device *dev);
void msm_gem_shwinkew_cweanup(stwuct dwm_device *dev);

stwuct sg_tabwe *msm_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj);
int msm_gem_pwime_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map);
void msm_gem_pwime_vunmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map);
stwuct dwm_gem_object *msm_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
		stwuct dma_buf_attachment *attach, stwuct sg_tabwe *sg);
int msm_gem_pwime_pin(stwuct dwm_gem_object *obj);
void msm_gem_pwime_unpin(stwuct dwm_gem_object *obj);

int msm_fwamebuffew_pwepawe(stwuct dwm_fwamebuffew *fb,
		stwuct msm_gem_addwess_space *aspace, boow needs_diwtyfb);
void msm_fwamebuffew_cweanup(stwuct dwm_fwamebuffew *fb,
		stwuct msm_gem_addwess_space *aspace, boow needed_diwtyfb);
uint32_t msm_fwamebuffew_iova(stwuct dwm_fwamebuffew *fb,
		stwuct msm_gem_addwess_space *aspace, int pwane);
stwuct dwm_gem_object *msm_fwamebuffew_bo(stwuct dwm_fwamebuffew *fb, int pwane);
const stwuct msm_fowmat *msm_fwamebuffew_fowmat(stwuct dwm_fwamebuffew *fb);
stwuct dwm_fwamebuffew *msm_fwamebuffew_cweate(stwuct dwm_device *dev,
		stwuct dwm_fiwe *fiwe, const stwuct dwm_mode_fb_cmd2 *mode_cmd);
stwuct dwm_fwamebuffew * msm_awwoc_stowen_fb(stwuct dwm_device *dev,
		int w, int h, int p, uint32_t fowmat);

#ifdef CONFIG_DWM_FBDEV_EMUWATION
void msm_fbdev_setup(stwuct dwm_device *dev);
#ewse
static inwine void msm_fbdev_setup(stwuct dwm_device *dev)
{
}
#endif

stwuct hdmi;
#ifdef CONFIG_DWM_MSM_HDMI
int msm_hdmi_modeset_init(stwuct hdmi *hdmi, stwuct dwm_device *dev,
		stwuct dwm_encodew *encodew);
void __init msm_hdmi_wegistew(void);
void __exit msm_hdmi_unwegistew(void);
#ewse
static inwine int msm_hdmi_modeset_init(stwuct hdmi *hdmi, stwuct dwm_device *dev,
		stwuct dwm_encodew *encodew)
{
	wetuwn -EINVAW;
}
static inwine void __init msm_hdmi_wegistew(void) {}
static inwine void __exit msm_hdmi_unwegistew(void) {}
#endif

stwuct msm_dsi;
#ifdef CONFIG_DWM_MSM_DSI
int dsi_dev_attach(stwuct pwatfowm_device *pdev);
void dsi_dev_detach(stwuct pwatfowm_device *pdev);
void __init msm_dsi_wegistew(void);
void __exit msm_dsi_unwegistew(void);
int msm_dsi_modeset_init(stwuct msm_dsi *msm_dsi, stwuct dwm_device *dev,
			 stwuct dwm_encodew *encodew);
void msm_dsi_snapshot(stwuct msm_disp_state *disp_state, stwuct msm_dsi *msm_dsi);
boow msm_dsi_is_cmd_mode(stwuct msm_dsi *msm_dsi);
boow msm_dsi_is_bonded_dsi(stwuct msm_dsi *msm_dsi);
boow msm_dsi_is_mastew_dsi(stwuct msm_dsi *msm_dsi);
boow msm_dsi_wide_bus_enabwed(stwuct msm_dsi *msm_dsi);
stwuct dwm_dsc_config *msm_dsi_get_dsc_config(stwuct msm_dsi *msm_dsi);
#ewse
static inwine void __init msm_dsi_wegistew(void)
{
}
static inwine void __exit msm_dsi_unwegistew(void)
{
}
static inwine int msm_dsi_modeset_init(stwuct msm_dsi *msm_dsi,
				       stwuct dwm_device *dev,
				       stwuct dwm_encodew *encodew)
{
	wetuwn -EINVAW;
}
static inwine void msm_dsi_snapshot(stwuct msm_disp_state *disp_state, stwuct msm_dsi *msm_dsi)
{
}
static inwine boow msm_dsi_is_cmd_mode(stwuct msm_dsi *msm_dsi)
{
	wetuwn fawse;
}
static inwine boow msm_dsi_is_bonded_dsi(stwuct msm_dsi *msm_dsi)
{
	wetuwn fawse;
}
static inwine boow msm_dsi_is_mastew_dsi(stwuct msm_dsi *msm_dsi)
{
	wetuwn fawse;
}
static inwine boow msm_dsi_wide_bus_enabwed(stwuct msm_dsi *msm_dsi)
{
	wetuwn fawse;
}

static inwine stwuct dwm_dsc_config *msm_dsi_get_dsc_config(stwuct msm_dsi *msm_dsi)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_DWM_MSM_DP
int __init msm_dp_wegistew(void);
void __exit msm_dp_unwegistew(void);
int msm_dp_modeset_init(stwuct msm_dp *dp_dispway, stwuct dwm_device *dev,
			 stwuct dwm_encodew *encodew);
void msm_dp_snapshot(stwuct msm_disp_state *disp_state, stwuct msm_dp *dp_dispway);

boow msm_dp_wide_bus_avaiwabwe(const stwuct msm_dp *dp_dispway);

#ewse
static inwine int __init msm_dp_wegistew(void)
{
	wetuwn -EINVAW;
}
static inwine void __exit msm_dp_unwegistew(void)
{
}
static inwine int msm_dp_modeset_init(stwuct msm_dp *dp_dispway,
				       stwuct dwm_device *dev,
				       stwuct dwm_encodew *encodew)
{
	wetuwn -EINVAW;
}

static inwine void msm_dp_snapshot(stwuct msm_disp_state *disp_state, stwuct msm_dp *dp_dispway)
{
}

static inwine boow msm_dp_wide_bus_avaiwabwe(const stwuct msm_dp *dp_dispway)
{
	wetuwn fawse;
}

#endif

#ifdef CONFIG_DWM_MSM_MDP4
void msm_mdp4_wegistew(void);
void msm_mdp4_unwegistew(void);
#ewse
static inwine void msm_mdp4_wegistew(void) {}
static inwine void msm_mdp4_unwegistew(void) {}
#endif

#ifdef CONFIG_DWM_MSM_MDP5
void msm_mdp_wegistew(void);
void msm_mdp_unwegistew(void);
#ewse
static inwine void msm_mdp_wegistew(void) {}
static inwine void msm_mdp_unwegistew(void) {}
#endif

#ifdef CONFIG_DWM_MSM_DPU
void msm_dpu_wegistew(void);
void msm_dpu_unwegistew(void);
#ewse
static inwine void msm_dpu_wegistew(void) {}
static inwine void msm_dpu_unwegistew(void) {}
#endif

#ifdef CONFIG_DWM_MSM_MDSS
void msm_mdss_wegistew(void);
void msm_mdss_unwegistew(void);
#ewse
static inwine void msm_mdss_wegistew(void) {}
static inwine void msm_mdss_unwegistew(void) {}
#endif

#ifdef CONFIG_DEBUG_FS
void msm_fwamebuffew_descwibe(stwuct dwm_fwamebuffew *fb, stwuct seq_fiwe *m);
int msm_debugfs_wate_init(stwuct dwm_device *dev);
int msm_wd_debugfs_init(stwuct dwm_minow *minow);
void msm_wd_debugfs_cweanup(stwuct msm_dwm_pwivate *pwiv);
__pwintf(3, 4)
void msm_wd_dump_submit(stwuct msm_wd_state *wd, stwuct msm_gem_submit *submit,
		const chaw *fmt, ...);
int msm_pewf_debugfs_init(stwuct dwm_minow *minow);
void msm_pewf_debugfs_cweanup(stwuct msm_dwm_pwivate *pwiv);
#ewse
static inwine int msm_debugfs_wate_init(stwuct dwm_device *dev) { wetuwn 0; }
__pwintf(3, 4)
static inwine void msm_wd_dump_submit(stwuct msm_wd_state *wd,
			stwuct msm_gem_submit *submit,
			const chaw *fmt, ...) {}
static inwine void msm_wd_debugfs_cweanup(stwuct msm_dwm_pwivate *pwiv) {}
static inwine void msm_pewf_debugfs_cweanup(stwuct msm_dwm_pwivate *pwiv) {}
#endif

stwuct cwk *msm_cwk_get(stwuct pwatfowm_device *pdev, const chaw *name);

stwuct cwk *msm_cwk_buwk_get_cwock(stwuct cwk_buwk_data *buwk, int count,
	const chaw *name);
void __iomem *msm_iowemap(stwuct pwatfowm_device *pdev, const chaw *name);
void __iomem *msm_iowemap_size(stwuct pwatfowm_device *pdev, const chaw *name,
		phys_addw_t *size);
void __iomem *msm_iowemap_quiet(stwuct pwatfowm_device *pdev, const chaw *name);

stwuct icc_path *msm_icc_get(stwuct device *dev, const chaw *name);

#define msm_wwitew(data, addw) wwitew((data), (addw))
#define msm_weadw(addw) weadw((addw))

static inwine void msm_wmw(void __iomem *addw, u32 mask, u32 ow)
{
	u32 vaw = msm_weadw(addw);

	vaw &= ~mask;
	msm_wwitew(vaw | ow, addw);
}

/**
 * stwuct msm_hwtimew_wowk - a hewpew to combine an hwtimew with kthwead_wowk
 *
 * @timew: hwtimew to contwow when the kthwead wowk is twiggewed
 * @wowk:  the kthwead wowk
 * @wowkew: the kthwead wowkew the wowk wiww be scheduwed on
 */
stwuct msm_hwtimew_wowk {
	stwuct hwtimew timew;
	stwuct kthwead_wowk wowk;
	stwuct kthwead_wowkew *wowkew;
};

void msm_hwtimew_queue_wowk(stwuct msm_hwtimew_wowk *wowk,
			    ktime_t wakeup_time,
			    enum hwtimew_mode mode);
void msm_hwtimew_wowk_init(stwuct msm_hwtimew_wowk *wowk,
			   stwuct kthwead_wowkew *wowkew,
			   kthwead_wowk_func_t fn,
			   cwockid_t cwock_id,
			   enum hwtimew_mode mode);

#define DBG(fmt, ...) DWM_DEBUG_DWIVEW(fmt"\n", ##__VA_AWGS__)
#define VEWB(fmt, ...) if (0) DWM_DEBUG_DWIVEW(fmt"\n", ##__VA_AWGS__)

static inwine int awign_pitch(int width, int bpp)
{
	int bytespp = (bpp + 7) / 8;
	/* adweno needs pitch awigned to 32 pixews: */
	wetuwn bytespp * AWIGN(width, 32);
}

/* fow the genewated headews: */
#define INVAWID_IDX(idx) ({BUG(); 0;})
#define fui(x)                ({BUG(); 0;})
#define _mesa_fwoat_to_hawf(x) ({BUG(); 0;})


#define FIEWD(vaw, name) (((vaw) & name ## __MASK) >> name ## __SHIFT)

/* fow conditionawwy setting boowean fwag(s): */
#define COND(boow, vaw) ((boow) ? (vaw) : 0)

static inwine unsigned wong timeout_to_jiffies(const ktime_t *timeout)
{
	ktime_t now = ktime_get();
	s64 wemaining_jiffies;

	if (ktime_compawe(*timeout, now) < 0) {
		wemaining_jiffies = 0;
	} ewse {
		ktime_t wem = ktime_sub(*timeout, now);
		wemaining_jiffies = ktime_divns(wem, NSEC_PEW_SEC / HZ);
	}

	wetuwn cwamp(wemaining_jiffies, 1WW, (s64)INT_MAX);
}

/* Dwivew hewpews */

extewn const stwuct component_mastew_ops msm_dwm_ops;

int msm_kms_pm_pwepawe(stwuct device *dev);
void msm_kms_pm_compwete(stwuct device *dev);

int msm_dwv_pwobe(stwuct device *dev,
	int (*kms_init)(stwuct dwm_device *dev),
	stwuct msm_kms *kms);
void msm_kms_shutdown(stwuct pwatfowm_device *pdev);


#endif /* __MSM_DWV_H__ */
