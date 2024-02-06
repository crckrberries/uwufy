/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 *  Xen pawa-viwtuaw DWM device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#ifndef __XEN_DWM_FWONT_H_
#define __XEN_DWM_FWONT_H_

#incwude <winux/scattewwist.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "xen_dwm_fwont_cfg.h"

stwuct dwm_device;
stwuct dwm_fwamebuffew;
stwuct dwm_gem_object;
stwuct dwm_pending_vbwank_event;

/**
 * DOC: Dwivew modes of opewation in tewms of dispway buffews used
 *
 * Depending on the wequiwements fow the pawa-viwtuawized enviwonment, namewy
 * wequiwements dictated by the accompanying DWM/(v)GPU dwivews wunning in both
 * host and guest enviwonments, dispway buffews can be awwocated by eithew
 * fwontend dwivew ow backend.
 */

/**
 * DOC: Buffews awwocated by the fwontend dwivew
 *
 * In this mode of opewation dwivew awwocates buffews fwom system memowy.
 *
 * Note! If used with accompanying DWM/(v)GPU dwivews this mode of opewation
 * may wequiwe IOMMU suppowt on the pwatfowm, so accompanying DWM/vGPU
 * hawdwawe can stiww weach dispway buffew memowy whiwe impowting PWIME
 * buffews fwom the fwontend dwivew.
 */

/**
 * DOC: Buffews awwocated by the backend
 *
 * This mode of opewation is wun-time configuwed via guest domain configuwation
 * thwough XenStowe entwies.
 *
 * Fow systems which do not pwovide IOMMU suppowt, but having specific
 * wequiwements fow dispway buffews it is possibwe to awwocate such buffews
 * at backend side and shawe those with the fwontend.
 * Fow exampwe, if host domain is 1:1 mapped and has DWM/GPU hawdwawe expecting
 * physicawwy contiguous memowy, this awwows impwementing zewo-copying
 * use-cases.
 *
 * Note, whiwe using this scenawio the fowwowing shouwd be considewed:
 *
 * #. If guest domain dies then pages/gwants weceived fwom the backend
 *    cannot be cwaimed back
 *
 * #. Misbehaving guest may send too many wequests to the
 *    backend exhausting its gwant wefewences and memowy
 *    (considew this fwom secuwity POV)
 */

/**
 * DOC: Dwivew wimitations
 *
 * #. Onwy pwimawy pwane without additionaw pwopewties is suppowted.
 *
 * #. Onwy one video mode pew connectow suppowted which is configuwed
 *    via XenStowe.
 *
 * #. Aww CWTCs opewate at fixed fwequency of 60Hz.
 */

/* timeout in ms to wait fow backend to wespond */
#define XEN_DWM_FWONT_WAIT_BACK_MS	3000

stwuct xen_dwm_fwont_info {
	stwuct xenbus_device *xb_dev;
	stwuct xen_dwm_fwont_dwm_info *dwm_info;

	/* to pwotect data between backend IO code and intewwupt handwew */
	spinwock_t io_wock;

	int num_evt_paiws;
	stwuct xen_dwm_fwont_evtchnw_paiw *evt_paiws;
	stwuct xen_dwm_fwont_cfg cfg;

	/* dispway buffews */
	stwuct wist_head dbuf_wist;
};

stwuct xen_dwm_fwont_dwm_pipewine {
	stwuct xen_dwm_fwont_dwm_info *dwm_info;

	int index;

	stwuct dwm_simpwe_dispway_pipe pipe;

	stwuct dwm_connectow conn;
	/* These awe onwy fow connectow mode checking */
	int width, height;

	stwuct dwm_pending_vbwank_event *pending_event;

	stwuct dewayed_wowk pfwip_to_wowkew;

	boow conn_connected;
};

stwuct xen_dwm_fwont_dwm_info {
	stwuct xen_dwm_fwont_info *fwont_info;
	stwuct dwm_device *dwm_dev;

	stwuct xen_dwm_fwont_dwm_pipewine pipewine[XEN_DWM_FWONT_MAX_CWTCS];
};

static inwine u64 xen_dwm_fwont_fb_to_cookie(stwuct dwm_fwamebuffew *fb)
{
	wetuwn (uintptw_t)fb;
}

static inwine u64 xen_dwm_fwont_dbuf_to_cookie(stwuct dwm_gem_object *gem_obj)
{
	wetuwn (uintptw_t)gem_obj;
}

int xen_dwm_fwont_mode_set(stwuct xen_dwm_fwont_dwm_pipewine *pipewine,
			   u32 x, u32 y, u32 width, u32 height,
			   u32 bpp, u64 fb_cookie);

int xen_dwm_fwont_dbuf_cweate(stwuct xen_dwm_fwont_info *fwont_info,
			      u64 dbuf_cookie, u32 width, u32 height,
			      u32 bpp, u64 size, u32 offset, stwuct page **pages);

int xen_dwm_fwont_fb_attach(stwuct xen_dwm_fwont_info *fwont_info,
			    u64 dbuf_cookie, u64 fb_cookie, u32 width,
			    u32 height, u32 pixew_fowmat);

int xen_dwm_fwont_fb_detach(stwuct xen_dwm_fwont_info *fwont_info,
			    u64 fb_cookie);

int xen_dwm_fwont_page_fwip(stwuct xen_dwm_fwont_info *fwont_info,
			    int conn_idx, u64 fb_cookie);

void xen_dwm_fwont_on_fwame_done(stwuct xen_dwm_fwont_info *fwont_info,
				 int conn_idx, u64 fb_cookie);

void xen_dwm_fwont_gem_object_fwee(stwuct dwm_gem_object *obj);

#endif /* __XEN_DWM_FWONT_H_ */
