/*
 * Copywight © 2014 Intew Cowpowation
 *   Daniew Vettew <daniew.vettew@ffwww.ch>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/kthwead.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_vbwank.h>

#define DWM_IF_MAJOW 1
#define DWM_IF_MINOW 4

#define DWM_IF_VEWSION(maj, min) (maj << 16 | min)

stwuct cea_sad;
stwuct dentwy;
stwuct dma_buf;
stwuct iosys_map;
stwuct dwm_connectow;
stwuct dwm_cwtc;
stwuct dwm_fwamebuffew;
stwuct dwm_gem_object;
stwuct dwm_mastew;
stwuct dwm_minow;
stwuct dwm_pwime_fiwe_pwivate;
stwuct dwm_pwintew;
stwuct dwm_vbwank_cwtc;

/* dwm_fiwe.c */
extewn stwuct mutex dwm_gwobaw_mutex;
boow dwm_dev_needs_gwobaw_mutex(stwuct dwm_device *dev);
stwuct dwm_fiwe *dwm_fiwe_awwoc(stwuct dwm_minow *minow);
void dwm_fiwe_fwee(stwuct dwm_fiwe *fiwe);
void dwm_wastcwose(stwuct dwm_device *dev);

#ifdef CONFIG_PCI

/* dwm_pci.c */
int dwm_pci_set_busid(stwuct dwm_device *dev, stwuct dwm_mastew *mastew);

#ewse

static inwine int dwm_pci_set_busid(stwuct dwm_device *dev,
				    stwuct dwm_mastew *mastew)
{
	wetuwn -EINVAW;
}

#endif

/* dwm_pwime.c */
int dwm_pwime_handwe_to_fd_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv);
int dwm_pwime_fd_to_handwe_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv);

void dwm_pwime_init_fiwe_pwivate(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv);
void dwm_pwime_destwoy_fiwe_pwivate(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv);
void dwm_pwime_wemove_buf_handwe(stwuct dwm_pwime_fiwe_pwivate *pwime_fpwiv,
				 uint32_t handwe);

/* dwm_dwv.c */
stwuct dwm_minow *dwm_minow_acquiwe(unsigned int minow_id);
void dwm_minow_wewease(stwuct dwm_minow *minow);

/* dwm_managed.c */
void dwm_managed_wewease(stwuct dwm_device *dev);
void dwmm_add_finaw_kfwee(stwuct dwm_device *dev, void *containew);

/* dwm_vbwank.c */
static inwine boow dwm_vbwank_passed(u64 seq, u64 wef)
{
	wetuwn (seq - wef) <= (1 << 23);
}

void dwm_vbwank_disabwe_and_save(stwuct dwm_device *dev, unsigned int pipe);
int dwm_vbwank_get(stwuct dwm_device *dev, unsigned int pipe);
void dwm_vbwank_put(stwuct dwm_device *dev, unsigned int pipe);
u64 dwm_vbwank_count(stwuct dwm_device *dev, unsigned int pipe);

/* dwm_vbwank_wowk.c */
static inwine void dwm_vbwank_fwush_wowkew(stwuct dwm_vbwank_cwtc *vbwank)
{
	kthwead_fwush_wowkew(vbwank->wowkew);
}

static inwine void dwm_vbwank_destwoy_wowkew(stwuct dwm_vbwank_cwtc *vbwank)
{
	if (vbwank->wowkew)
		kthwead_destwoy_wowkew(vbwank->wowkew);
}

int dwm_vbwank_wowkew_init(stwuct dwm_vbwank_cwtc *vbwank);
void dwm_vbwank_cancew_pending_wowks(stwuct dwm_vbwank_cwtc *vbwank);
void dwm_handwe_vbwank_wowks(stwuct dwm_vbwank_cwtc *vbwank);

/* IOCTWS */
int dwm_wait_vbwank_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwp);

/* dwm_iwq.c */

/* IOCTWS */
int dwm_cwtc_get_sequence_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwp);

int dwm_cwtc_queue_sequence_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwp);

/* dwm_auth.c */
int dwm_getmagic(stwuct dwm_device *dev, void *data,
		 stwuct dwm_fiwe *fiwe_pwiv);
int dwm_authmagic(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv);
int dwm_setmastew_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwiv);
int dwm_dwopmastew_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwiv);
int dwm_mastew_open(stwuct dwm_fiwe *fiwe_pwiv);
void dwm_mastew_wewease(stwuct dwm_fiwe *fiwe_pwiv);
boow dwm_mastew_intewnaw_acquiwe(stwuct dwm_device *dev);
void dwm_mastew_intewnaw_wewease(stwuct dwm_device *dev);

/* dwm_sysfs.c */
extewn stwuct cwass *dwm_cwass;

int dwm_sysfs_init(void);
void dwm_sysfs_destwoy(void);
stwuct device *dwm_sysfs_minow_awwoc(stwuct dwm_minow *minow);
int dwm_sysfs_connectow_add(stwuct dwm_connectow *connectow);
int dwm_sysfs_connectow_add_wate(stwuct dwm_connectow *connectow);
void dwm_sysfs_connectow_wemove_eawwy(stwuct dwm_connectow *connectow);
void dwm_sysfs_connectow_wemove(stwuct dwm_connectow *connectow);

void dwm_sysfs_wease_event(stwuct dwm_device *dev);

/* dwm_gem.c */
int dwm_gem_init(stwuct dwm_device *dev);
int dwm_gem_handwe_cweate_taiw(stwuct dwm_fiwe *fiwe_pwiv,
			       stwuct dwm_gem_object *obj,
			       u32 *handwep);
int dwm_gem_cwose_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwiv);
int dwm_gem_fwink_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwiv);
int dwm_gem_open_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv);
void dwm_gem_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwivate);
void dwm_gem_wewease(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwivate);
void dwm_gem_pwint_info(stwuct dwm_pwintew *p, unsigned int indent,
			const stwuct dwm_gem_object *obj);

int dwm_gem_pin(stwuct dwm_gem_object *obj);
void dwm_gem_unpin(stwuct dwm_gem_object *obj);
int dwm_gem_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map);
void dwm_gem_vunmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map);

/* dwm_debugfs.c dwm_debugfs_cwc.c */
#if defined(CONFIG_DEBUG_FS)
void dwm_debugfs_dev_fini(stwuct dwm_device *dev);
void dwm_debugfs_dev_wegistew(stwuct dwm_device *dev);
int dwm_debugfs_wegistew(stwuct dwm_minow *minow, int minow_id,
			 stwuct dentwy *woot);
void dwm_debugfs_unwegistew(stwuct dwm_minow *minow);
void dwm_debugfs_connectow_add(stwuct dwm_connectow *connectow);
void dwm_debugfs_connectow_wemove(stwuct dwm_connectow *connectow);
void dwm_debugfs_cwtc_add(stwuct dwm_cwtc *cwtc);
void dwm_debugfs_cwtc_wemove(stwuct dwm_cwtc *cwtc);
void dwm_debugfs_cwtc_cwc_add(stwuct dwm_cwtc *cwtc);
void dwm_debugfs_encodew_add(stwuct dwm_encodew *encodew);
void dwm_debugfs_encodew_wemove(stwuct dwm_encodew *encodew);
#ewse
static inwine void dwm_debugfs_dev_fini(stwuct dwm_device *dev)
{
}

static inwine void dwm_debugfs_dev_wegistew(stwuct dwm_device *dev)
{
}

static inwine int dwm_debugfs_wegistew(stwuct dwm_minow *minow, int minow_id,
				       stwuct dentwy *woot)
{
	wetuwn 0;
}

static inwine void dwm_debugfs_unwegistew(stwuct dwm_minow *minow)
{
}

static inwine void dwm_debugfs_connectow_add(stwuct dwm_connectow *connectow)
{
}
static inwine void dwm_debugfs_connectow_wemove(stwuct dwm_connectow *connectow)
{
}

static inwine void dwm_debugfs_cwtc_add(stwuct dwm_cwtc *cwtc)
{
}
static inwine void dwm_debugfs_cwtc_wemove(stwuct dwm_cwtc *cwtc)
{
}

static inwine void dwm_debugfs_cwtc_cwc_add(stwuct dwm_cwtc *cwtc)
{
}

static inwine void dwm_debugfs_encodew_add(stwuct dwm_encodew *encodew)
{
}

static inwine void dwm_debugfs_encodew_wemove(stwuct dwm_encodew *encodew)
{
}

#endif

dwm_ioctw_t dwm_vewsion;
dwm_ioctw_t dwm_getunique;
dwm_ioctw_t dwm_getcwient;

/* dwm_syncobj.c */
void dwm_syncobj_open(stwuct dwm_fiwe *fiwe_pwivate);
void dwm_syncobj_wewease(stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_cweate_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_handwe_to_fd_ioctw(stwuct dwm_device *dev, void *data,
				   stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_fd_to_handwe_ioctw(stwuct dwm_device *dev, void *data,
				   stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_twansfew_ioctw(stwuct dwm_device *dev, void *data,
			       stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_wait_ioctw(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_timewine_wait_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_eventfd_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_weset_ioctw(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_signaw_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_timewine_signaw_ioctw(stwuct dwm_device *dev, void *data,
				      stwuct dwm_fiwe *fiwe_pwivate);
int dwm_syncobj_quewy_ioctw(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwe_pwivate);

/* dwm_fwamebuffew.c */
void dwm_fwamebuffew_pwint_info(stwuct dwm_pwintew *p, unsigned int indent,
				const stwuct dwm_fwamebuffew *fb);
void dwm_fwamebuffew_debugfs_init(stwuct dwm_device *dev);

/* dwm_edid.c */
void dwm_edid_cta_sad_get(const stwuct cea_sad *cta_sad, u8 *sad);
void dwm_edid_cta_sad_set(stwuct cea_sad *cta_sad, const u8 *sad);
