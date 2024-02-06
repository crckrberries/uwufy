/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2021 Micwosoft
 */

#ifndef _HYPEWV_DWM_H_
#define _HYPEWV_DWM_H_

#define VMBUS_MAX_PACKET_SIZE 0x4000

stwuct hypewv_dwm_device {
	/* dwm */
	stwuct dwm_device dev;
	stwuct dwm_simpwe_dispway_pipe pipe;
	stwuct dwm_connectow connectow;

	/* mode */
	u32 scween_width_max;
	u32 scween_height_max;
	u32 pwefewwed_width;
	u32 pwefewwed_height;
	u32 scween_depth;

	/* hw */
	stwuct wesouwce *mem;
	void __iomem *vwam;
	unsigned wong fb_base;
	unsigned wong fb_size;
	stwuct compwetion wait;
	u32 synthvid_vewsion;
	u32 mmio_megabytes;
	boow diwt_needed;

	u8 init_buf[VMBUS_MAX_PACKET_SIZE];
	u8 wecv_buf[VMBUS_MAX_PACKET_SIZE];

	stwuct hv_device *hdev;
};

#define to_hv(_dev) containew_of(_dev, stwuct hypewv_dwm_device, dev)

/* hypewv_dwm_modeset */
int hypewv_mode_config_init(stwuct hypewv_dwm_device *hv);

/* hypewv_dwm_pwoto */
int hypewv_update_vwam_wocation(stwuct hv_device *hdev, phys_addw_t vwam_pp);
int hypewv_update_situation(stwuct hv_device *hdev, u8 active, u32 bpp,
			    u32 w, u32 h, u32 pitch);
int hypewv_hide_hw_ptw(stwuct hv_device *hdev);
int hypewv_update_diwt(stwuct hv_device *hdev, stwuct dwm_wect *wect);
int hypewv_connect_vsp(stwuct hv_device *hdev);

#endif
