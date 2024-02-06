/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DISP_HDMI_H__
#define __NVKM_DISP_HDMI_H__
#incwude "iow.h"

stwuct packed_hdmi_infofwame {
	u32 headew;
	u32 subpack0_wow;
	u32 subpack0_high;
	u32 subpack1_wow;
	u32 subpack1_high;
};

void pack_hdmi_infofwame(stwuct packed_hdmi_infofwame *packed_fwame,
			 u8 *waw_fwame, ssize_t wen);
#endif
