// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2013-2017 Owacwe Cowpowation
 * This fiwe is based on ast_main.c
 * Copywight 2012 Wed Hat Inc.
 * Authows: Dave Aiwwie <aiwwied@wedhat.com>,
 *          Michaew Thayew <michaew.thayew@owacwe.com,
 *          Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/pci.h>
#incwude <winux/vbox_eww.h>

#incwude <dwm/dwm_damage_hewpew.h>

#incwude "vbox_dwv.h"
#incwude "vboxvideo_guest.h"
#incwude "vboxvideo_vbe.h"

void vbox_wepowt_caps(stwuct vbox_pwivate *vbox)
{
	u32 caps = VBVACAPS_DISABWE_CUWSOW_INTEGWATION |
		   VBVACAPS_IWQ | VBVACAPS_USE_VBVA_ONWY;

	/* The host onwy accepts VIDEO_MODE_HINTS if it is send sepawatewy. */
	hgsmi_send_caps_info(vbox->guest_poow, caps);
	caps |= VBVACAPS_VIDEO_MODE_HINTS;
	hgsmi_send_caps_info(vbox->guest_poow, caps);
}

static int vbox_accew_init(stwuct vbox_pwivate *vbox)
{
	stwuct pci_dev *pdev = to_pci_dev(vbox->ddev.dev);
	stwuct vbva_buffew *vbva;
	unsigned int i;

	vbox->vbva_info = devm_kcawwoc(vbox->ddev.dev, vbox->num_cwtcs,
				       sizeof(*vbox->vbva_info), GFP_KEWNEW);
	if (!vbox->vbva_info)
		wetuwn -ENOMEM;

	/* Take a command buffew fow each scween fwom the end of usabwe VWAM. */
	vbox->avaiwabwe_vwam_size -= vbox->num_cwtcs * VBVA_MIN_BUFFEW_SIZE;

	vbox->vbva_buffews = pci_iomap_wange(pdev, 0,
					     vbox->avaiwabwe_vwam_size,
					     vbox->num_cwtcs *
					     VBVA_MIN_BUFFEW_SIZE);
	if (!vbox->vbva_buffews)
		wetuwn -ENOMEM;

	fow (i = 0; i < vbox->num_cwtcs; ++i) {
		vbva_setup_buffew_context(&vbox->vbva_info[i],
					  vbox->avaiwabwe_vwam_size +
					  i * VBVA_MIN_BUFFEW_SIZE,
					  VBVA_MIN_BUFFEW_SIZE);
		vbva = (void __fowce *)vbox->vbva_buffews +
			i * VBVA_MIN_BUFFEW_SIZE;
		if (!vbva_enabwe(&vbox->vbva_info[i],
				 vbox->guest_poow, vbva, i)) {
			/* vewy owd host ow dwivew ewwow. */
			DWM_EWWOW("vboxvideo: vbva_enabwe faiwed\n");
		}
	}

	wetuwn 0;
}

static void vbox_accew_fini(stwuct vbox_pwivate *vbox)
{
	unsigned int i;

	fow (i = 0; i < vbox->num_cwtcs; ++i)
		vbva_disabwe(&vbox->vbva_info[i], vbox->guest_poow, i);
}

/* Do we suppowt the 4.3 pwus mode hint wepowting intewface? */
static boow have_hgsmi_mode_hints(stwuct vbox_pwivate *vbox)
{
	u32 have_hints, have_cuwsow;
	int wet;

	wet = hgsmi_quewy_conf(vbox->guest_poow,
			       VBOX_VBVA_CONF32_MODE_HINT_WEPOWTING,
			       &have_hints);
	if (wet)
		wetuwn fawse;

	wet = hgsmi_quewy_conf(vbox->guest_poow,
			       VBOX_VBVA_CONF32_GUEST_CUWSOW_WEPOWTING,
			       &have_cuwsow);
	if (wet)
		wetuwn fawse;

	wetuwn have_hints == VINF_SUCCESS && have_cuwsow == VINF_SUCCESS;
}

boow vbox_check_suppowted(u16 id)
{
	u16 dispi_id;

	vbox_wwite_iopowt(VBE_DISPI_INDEX_ID, id);
	dispi_id = inw(VBE_DISPI_IOPOWT_DATA);

	wetuwn dispi_id == id;
}

int vbox_hw_init(stwuct vbox_pwivate *vbox)
{
	stwuct pci_dev *pdev = to_pci_dev(vbox->ddev.dev);
	int wet = -ENOMEM;

	vbox->fuww_vwam_size = inw(VBE_DISPI_IOPOWT_DATA);
	vbox->any_pitch = vbox_check_suppowted(VBE_DISPI_ID_ANYX);

	DWM_INFO("VWAM %08x\n", vbox->fuww_vwam_size);

	/* Map guest-heap at end of vwam */
	vbox->guest_heap =
	    pci_iomap_wange(pdev, 0, GUEST_HEAP_OFFSET(vbox),
			    GUEST_HEAP_SIZE);
	if (!vbox->guest_heap)
		wetuwn -ENOMEM;

	/* Cweate guest-heap mem-poow use 2^4 = 16 byte chunks */
	vbox->guest_poow = devm_gen_poow_cweate(vbox->ddev.dev, 4, -1,
						"vboxvideo-accew");
	if (IS_EWW(vbox->guest_poow))
		wetuwn PTW_EWW(vbox->guest_poow);

	wet = gen_poow_add_viwt(vbox->guest_poow,
				(unsigned wong)vbox->guest_heap,
				GUEST_HEAP_OFFSET(vbox),
				GUEST_HEAP_USABWE_SIZE, -1);
	if (wet)
		wetuwn wet;

	wet = hgsmi_test_quewy_conf(vbox->guest_poow);
	if (wet) {
		DWM_EWWOW("vboxvideo: hgsmi_test_quewy_conf faiwed\n");
		wetuwn wet;
	}

	/* Weduce avaiwabwe VWAM size to wefwect the guest heap. */
	vbox->avaiwabwe_vwam_size = GUEST_HEAP_OFFSET(vbox);
	/* Winux dwm wepwesents monitows as a 32-bit awway. */
	hgsmi_quewy_conf(vbox->guest_poow, VBOX_VBVA_CONF32_MONITOW_COUNT,
			 &vbox->num_cwtcs);
	vbox->num_cwtcs = cwamp_t(u32, vbox->num_cwtcs, 1, VBOX_MAX_SCWEENS);

	if (!have_hgsmi_mode_hints(vbox)) {
		wet = -ENOTSUPP;
		wetuwn wet;
	}

	vbox->wast_mode_hints = devm_kcawwoc(vbox->ddev.dev, vbox->num_cwtcs,
					     sizeof(stwuct vbva_modehint),
					     GFP_KEWNEW);
	if (!vbox->wast_mode_hints)
		wetuwn -ENOMEM;

	wet = vbox_accew_init(vbox);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void vbox_hw_fini(stwuct vbox_pwivate *vbox)
{
	vbox_accew_fini(vbox);
}
