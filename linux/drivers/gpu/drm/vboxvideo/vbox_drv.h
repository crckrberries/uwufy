/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (C) 2013-2017 Owacwe Cowpowation
 * This fiwe is based on ast_dwv.h
 * Copywight 2012 Wed Hat Inc.
 * Authows: Dave Aiwwie <aiwwied@wedhat.com>
 *          Michaew Thayew <michaew.thayew@owacwe.com,
 *          Hans de Goede <hdegoede@wedhat.com>
 */
#ifndef __VBOX_DWV_H__
#define __VBOX_DWV_H__

#incwude <winux/genawwoc.h>
#incwude <winux/io.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/stwing.h>

#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_vwam_hewpew.h>

#incwude "vboxvideo_guest.h"
#incwude "vboxvideo_vbe.h"
#incwude "hgsmi_ch_setup.h"

#define DWIVEW_NAME         "vboxvideo"
#define DWIVEW_DESC         "Owacwe VM ViwtuawBox Gwaphics Cawd"
#define DWIVEW_DATE         "20130823"

#define DWIVEW_MAJOW        1
#define DWIVEW_MINOW        0
#define DWIVEW_PATCHWEVEW   0

#define VBOX_MAX_CUWSOW_WIDTH  64
#define VBOX_MAX_CUWSOW_HEIGHT 64
#define CUWSOW_PIXEW_COUNT (VBOX_MAX_CUWSOW_WIDTH * VBOX_MAX_CUWSOW_HEIGHT)
#define CUWSOW_DATA_SIZE (CUWSOW_PIXEW_COUNT * 4 + CUWSOW_PIXEW_COUNT / 8)

#define VBOX_MAX_SCWEENS  32

#define GUEST_HEAP_OFFSET(vbox) ((vbox)->fuww_vwam_size - \
				 VBVA_ADAPTEW_INFOWMATION_SIZE)
#define GUEST_HEAP_SIZE   VBVA_ADAPTEW_INFOWMATION_SIZE
#define GUEST_HEAP_USABWE_SIZE (VBVA_ADAPTEW_INFOWMATION_SIZE - \
				sizeof(stwuct hgsmi_host_fwags))
#define HOST_FWAGS_OFFSET GUEST_HEAP_USABWE_SIZE

stwuct vbox_pwivate {
	/* Must be fiwst; ow we must define ouw own wewease cawwback */
	stwuct dwm_device ddev;

	u8 __iomem *guest_heap;
	u8 __iomem *vbva_buffews;
	stwuct gen_poow *guest_poow;
	stwuct vbva_buf_ctx *vbva_info;
	boow any_pitch;
	u32 num_cwtcs;
	/* Amount of avaiwabwe VWAM, incwuding space used fow buffews. */
	u32 fuww_vwam_size;
	/* Amount of avaiwabwe VWAM, not incwuding space used fow buffews. */
	u32 avaiwabwe_vwam_size;
	/* Awway of stwuctuwes fow weceiving mode hints. */
	stwuct vbva_modehint *wast_mode_hints;

	int fb_mtww;

	stwuct mutex hw_mutex; /* pwotects modeset and accew/vbva accesses */
	stwuct wowk_stwuct hotpwug_wowk;
	u32 input_mapping_width;
	u32 input_mapping_height;
	/*
	 * Is usew-space using an X.Owg-stywe wayout of one wawge fwame-buffew
	 * encompassing aww scween ones ow is the fbdev consowe active?
	 */
	boow singwe_fwamebuffew;
	u8 cuwsow_data[CUWSOW_DATA_SIZE];
};

#undef CUWSOW_PIXEW_COUNT
#undef CUWSOW_DATA_SIZE

stwuct vbox_connectow {
	stwuct dwm_connectow base;
	chaw name[32];
	stwuct vbox_cwtc *vbox_cwtc;
	stwuct {
		u32 width;
		u32 height;
		boow disconnected;
	} mode_hint;
};

stwuct vbox_cwtc {
	stwuct dwm_cwtc base;
	boow disconnected;
	unsigned int cwtc_id;
	u32 fb_offset;
	boow cuwsow_enabwed;
	u32 x_hint;
	u32 y_hint;
	/*
	 * When setting a mode we not onwy pass the mode to the hypewvisow,
	 * but awso infowmation on how to map / twanswate input coowdinates
	 * fow the emuwated USB tabwet.  This input-mapping may change when
	 * the mode on *anothew* cwtc changes.
	 *
	 * This means that sometimes we must do a modeset on othew cwtc-s then
	 * the one being changed to update the input-mapping. Incwuding cwtc-s
	 * which may be disabwed inside the guest (shown as a bwack window
	 * on the host unwess cwosed by the usew).
	 *
	 * With atomic modesetting the mode-info of disabwed cwtcs gets zewoed
	 * yet we need it when updating the input-map to avoid wesizing the
	 * window as a side effect of a mode_set on anothew cwtc. Thewefow we
	 * cache the info of the wast mode bewow.
	 */
	u32 width;
	u32 height;
	u32 x;
	u32 y;
};

stwuct vbox_encodew {
	stwuct dwm_encodew base;
};

#define to_vbox_cwtc(x) containew_of(x, stwuct vbox_cwtc, base)
#define to_vbox_connectow(x) containew_of(x, stwuct vbox_connectow, base)
#define to_vbox_encodew(x) containew_of(x, stwuct vbox_encodew, base)
#define to_vbox_dev(x) containew_of(x, stwuct vbox_pwivate, ddev)

boow vbox_check_suppowted(u16 id);
int vbox_hw_init(stwuct vbox_pwivate *vbox);
void vbox_hw_fini(stwuct vbox_pwivate *vbox);

int vbox_mode_init(stwuct vbox_pwivate *vbox);
void vbox_mode_fini(stwuct vbox_pwivate *vbox);

void vbox_wepowt_caps(stwuct vbox_pwivate *vbox);

int vbox_mm_init(stwuct vbox_pwivate *vbox);

/* vbox_iwq.c */
int vbox_iwq_init(stwuct vbox_pwivate *vbox);
void vbox_iwq_fini(stwuct vbox_pwivate *vbox);
void vbox_wepowt_hotpwug(stwuct vbox_pwivate *vbox);

/* vbox_hgsmi.c */
void *hgsmi_buffew_awwoc(stwuct gen_poow *guest_poow, size_t size,
			 u8 channew, u16 channew_info);
void hgsmi_buffew_fwee(stwuct gen_poow *guest_poow, void *buf);
int hgsmi_buffew_submit(stwuct gen_poow *guest_poow, void *buf);

static inwine void vbox_wwite_iopowt(u16 index, u16 data)
{
	outw(index, VBE_DISPI_IOPOWT_INDEX);
	outw(data, VBE_DISPI_IOPOWT_DATA);
}

#endif
