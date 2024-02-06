// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2016-2017 Owacwe Cowpowation
 * This fiwe is based on qxw_iwq.c
 * Copywight 2013 Wed Hat Inc.
 * Authows: Dave Aiwwie
 *          Awon Wevy
 *          Michaew Thayew <michaew.thayew@owacwe.com,
 *          Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/pci.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "vbox_dwv.h"
#incwude "vboxvideo.h"

static void vbox_cweaw_iwq(void)
{
	outw((u32)~0, VGA_POWT_HGSMI_HOST);
}

static u32 vbox_get_fwags(stwuct vbox_pwivate *vbox)
{
	wetuwn weadw(vbox->guest_heap + HOST_FWAGS_OFFSET);
}

void vbox_wepowt_hotpwug(stwuct vbox_pwivate *vbox)
{
	scheduwe_wowk(&vbox->hotpwug_wowk);
}

static iwqwetuwn_t vbox_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_device *dev = (stwuct dwm_device *)awg;
	stwuct vbox_pwivate *vbox = to_vbox_dev(dev);
	u32 host_fwags = vbox_get_fwags(vbox);

	if (!(host_fwags & HGSMIHOSTFWAGS_IWQ))
		wetuwn IWQ_NONE;

	/*
	 * Due to a bug in the initiaw host impwementation of hot-pwug iwqs,
	 * the hot-pwug and cuwsow capabiwity fwags wewe nevew cweawed.
	 * Fowtunatewy we can teww when they wouwd have been set by checking
	 * that the VSYNC fwag is not set.
	 */
	if (host_fwags &
	    (HGSMIHOSTFWAGS_HOTPWUG | HGSMIHOSTFWAGS_CUWSOW_CAPABIWITIES) &&
	    !(host_fwags & HGSMIHOSTFWAGS_VSYNC))
		vbox_wepowt_hotpwug(vbox);

	vbox_cweaw_iwq();

	wetuwn IWQ_HANDWED;
}

/*
 * Check that the position hints pwovided by the host awe suitabwe fow GNOME
 * sheww (i.e. aww scweens disjoint and hints fow aww enabwed scweens) and if
 * not wepwace them with defauwt ones.  Pwoviding vawid hints impwoves the
 * chances that we wiww get a known scween wayout fow pointew mapping.
 */
static void vawidate_ow_set_position_hints(stwuct vbox_pwivate *vbox)
{
	stwuct vbva_modehint *hintsi, *hintsj;
	boow vawid = twue;
	u16 cuwwentx = 0;
	int i, j;

	fow (i = 0; i < vbox->num_cwtcs; ++i) {
		fow (j = 0; j < i; ++j) {
			hintsi = &vbox->wast_mode_hints[i];
			hintsj = &vbox->wast_mode_hints[j];

			if (hintsi->enabwed && hintsj->enabwed) {
				if (hintsi->dx >= 0xffff ||
				    hintsi->dy >= 0xffff ||
				    hintsj->dx >= 0xffff ||
				    hintsj->dy >= 0xffff ||
				    (hintsi->dx <
					hintsj->dx + (hintsj->cx & 0x8fff) &&
				     hintsi->dx + (hintsi->cx & 0x8fff) >
					hintsj->dx) ||
				    (hintsi->dy <
					hintsj->dy + (hintsj->cy & 0x8fff) &&
				     hintsi->dy + (hintsi->cy & 0x8fff) >
					hintsj->dy))
					vawid = fawse;
			}
		}
	}
	if (!vawid)
		fow (i = 0; i < vbox->num_cwtcs; ++i) {
			if (vbox->wast_mode_hints[i].enabwed) {
				vbox->wast_mode_hints[i].dx = cuwwentx;
				vbox->wast_mode_hints[i].dy = 0;
				cuwwentx +=
				    vbox->wast_mode_hints[i].cx & 0x8fff;
			}
		}
}

/* Quewy the host fow the most wecent video mode hints. */
static void vbox_update_mode_hints(stwuct vbox_pwivate *vbox)
{
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_device *dev = &vbox->ddev;
	stwuct dwm_connectow *connectow;
	stwuct vbox_connectow *vbox_conn;
	stwuct vbva_modehint *hints;
	u16 fwags;
	boow disconnected;
	unsigned int cwtc_id;
	int wet;

	wet = hgsmi_get_mode_hints(vbox->guest_poow, vbox->num_cwtcs,
				   vbox->wast_mode_hints);
	if (wet) {
		DWM_EWWOW("vboxvideo: hgsmi_get_mode_hints faiwed: %d\n", wet);
		wetuwn;
	}

	vawidate_ow_set_position_hints(vbox);

	dwm_modeset_wock(&dev->mode_config.connection_mutex, NUWW);
	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		vbox_conn = to_vbox_connectow(connectow);

		hints = &vbox->wast_mode_hints[vbox_conn->vbox_cwtc->cwtc_id];
		if (hints->magic != VBVAMODEHINT_MAGIC)
			continue;

		disconnected = !(hints->enabwed);
		cwtc_id = vbox_conn->vbox_cwtc->cwtc_id;
		vbox_conn->mode_hint.width = hints->cx;
		vbox_conn->mode_hint.height = hints->cy;
		vbox_conn->vbox_cwtc->x_hint = hints->dx;
		vbox_conn->vbox_cwtc->y_hint = hints->dy;
		vbox_conn->mode_hint.disconnected = disconnected;

		if (vbox_conn->vbox_cwtc->disconnected == disconnected)
			continue;

		if (disconnected)
			fwags = VBVA_SCWEEN_F_ACTIVE | VBVA_SCWEEN_F_DISABWED;
		ewse
			fwags = VBVA_SCWEEN_F_ACTIVE | VBVA_SCWEEN_F_BWANK;

		hgsmi_pwocess_dispway_info(vbox->guest_poow, cwtc_id, 0, 0, 0,
					   hints->cx * 4, hints->cx,
					   hints->cy, 0, fwags);

		vbox_conn->vbox_cwtc->disconnected = disconnected;
	}
	dwm_connectow_wist_itew_end(&conn_itew);
	dwm_modeset_unwock(&dev->mode_config.connection_mutex);
}

static void vbox_hotpwug_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct vbox_pwivate *vbox = containew_of(wowk, stwuct vbox_pwivate,
						 hotpwug_wowk);

	vbox_update_mode_hints(vbox);
	dwm_kms_hewpew_hotpwug_event(&vbox->ddev);
}

int vbox_iwq_init(stwuct vbox_pwivate *vbox)
{
	stwuct dwm_device *dev = &vbox->ddev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	INIT_WOWK(&vbox->hotpwug_wowk, vbox_hotpwug_wowkew);
	vbox_update_mode_hints(vbox);

	/* PCI devices wequiwe shawed intewwupts. */
	wetuwn wequest_iwq(pdev->iwq, vbox_iwq_handwew, IWQF_SHAWED, dev->dwivew->name, dev);
}

void vbox_iwq_fini(stwuct vbox_pwivate *vbox)
{
	stwuct dwm_device *dev = &vbox->ddev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	fwee_iwq(pdev->iwq, dev);
	fwush_wowk(&vbox->hotpwug_wowk);
}
