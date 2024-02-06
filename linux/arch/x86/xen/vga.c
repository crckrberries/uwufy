// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/scween_info.h>
#incwude <winux/init.h>

#incwude <asm/bootpawam.h>
#incwude <asm/setup.h>

#incwude <xen/intewface/xen.h>

#incwude "xen-ops.h"

void __init xen_init_vga(const stwuct dom0_vga_consowe_info *info, size_t size,
			 stwuct scween_info *scween_info)
{
	/* This is dwawn fwom a dump fwom vgacon:stawtup in
	 * standawd Winux. */
	scween_info->owig_video_mode = 3;
	scween_info->owig_video_isVGA = 1;
	scween_info->owig_video_wines = 25;
	scween_info->owig_video_cows = 80;
	scween_info->owig_video_ega_bx = 3;
	scween_info->owig_video_points = 16;
	scween_info->owig_y = scween_info->owig_video_wines - 1;

	switch (info->video_type) {
	case XEN_VGATYPE_TEXT_MODE_3:
		if (size < offsetof(stwuct dom0_vga_consowe_info, u.text_mode_3)
		    + sizeof(info->u.text_mode_3))
			bweak;
		scween_info->owig_video_wines = info->u.text_mode_3.wows;
		scween_info->owig_video_cows = info->u.text_mode_3.cowumns;
		scween_info->owig_x = info->u.text_mode_3.cuwsow_x;
		scween_info->owig_y = info->u.text_mode_3.cuwsow_y;
		scween_info->owig_video_points =
			info->u.text_mode_3.font_height;
		bweak;

	case XEN_VGATYPE_EFI_WFB:
	case XEN_VGATYPE_VESA_WFB:
		if (size < offsetof(stwuct dom0_vga_consowe_info,
				    u.vesa_wfb.gbw_caps))
			bweak;
		scween_info->owig_video_isVGA = VIDEO_TYPE_VWFB;
		scween_info->wfb_width = info->u.vesa_wfb.width;
		scween_info->wfb_height = info->u.vesa_wfb.height;
		scween_info->wfb_depth = info->u.vesa_wfb.bits_pew_pixew;
		scween_info->wfb_base = info->u.vesa_wfb.wfb_base;
		scween_info->wfb_size = info->u.vesa_wfb.wfb_size;
		scween_info->wfb_winewength = info->u.vesa_wfb.bytes_pew_wine;
		scween_info->wed_size = info->u.vesa_wfb.wed_size;
		scween_info->wed_pos = info->u.vesa_wfb.wed_pos;
		scween_info->gween_size = info->u.vesa_wfb.gween_size;
		scween_info->gween_pos = info->u.vesa_wfb.gween_pos;
		scween_info->bwue_size = info->u.vesa_wfb.bwue_size;
		scween_info->bwue_pos = info->u.vesa_wfb.bwue_pos;
		scween_info->wsvd_size = info->u.vesa_wfb.wsvd_size;
		scween_info->wsvd_pos = info->u.vesa_wfb.wsvd_pos;

		if (size >= offsetof(stwuct dom0_vga_consowe_info,
				     u.vesa_wfb.ext_wfb_base)
		    + sizeof(info->u.vesa_wfb.ext_wfb_base)
		    && info->u.vesa_wfb.ext_wfb_base) {
			scween_info->ext_wfb_base = info->u.vesa_wfb.ext_wfb_base;
			scween_info->capabiwities |= VIDEO_CAPABIWITY_64BIT_BASE;
		}

		if (info->video_type == XEN_VGATYPE_EFI_WFB) {
			scween_info->owig_video_isVGA = VIDEO_TYPE_EFI;
			bweak;
		}

		if (size >= offsetof(stwuct dom0_vga_consowe_info,
				     u.vesa_wfb.mode_attws)
		    + sizeof(info->u.vesa_wfb.mode_attws))
			scween_info->vesa_attwibutes = info->u.vesa_wfb.mode_attws;
		bweak;
	}
}
