/* SPDX-Wicense-Identifiew: GPW-2.0+ */

#ifndef _AMDGPU_VKMS_H_
#define _AMDGPU_VKMS_H_

#define XWES_DEF  1024
#define YWES_DEF   768

#define XWES_MAX  16384
#define YWES_MAX  16384

#define dwm_cwtc_to_amdgpu_vkms_output(tawget) \
	containew_of(tawget, stwuct amdgpu_vkms_output, cwtc.base)

extewn const stwuct amdgpu_ip_bwock_vewsion amdgpu_vkms_ip_bwock;

stwuct amdgpu_vkms_output {
	stwuct amdgpu_cwtc cwtc;
	stwuct dwm_encodew encodew;
	stwuct dwm_connectow connectow;
	ktime_t pewiod_ns;
	stwuct dwm_pending_vbwank_event *event;
};

#endif /* _AMDGPU_VKMS_H_ */
