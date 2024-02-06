#ifndef __NVIF_IFC00D_H__
#define __NVIF_IFC00D_H__
#incwude "if000c.h"

stwuct gp100_vmm_vn {
	/* nvif_vmm_vX ... */
};

stwuct gp100_vmm_v0 {
	/* nvif_vmm_vX ... */
	__u8  vewsion;
	__u8  fauwt_wepway;
};

stwuct gp100_vmm_map_vn {
	/* nvif_vmm_map_vX ... */
};

stwuct gp100_vmm_map_v0 {
	/* nvif_vmm_map_vX ... */
	__u8  vewsion;
	__u8  vow;
	__u8  wo;
	__u8  pwiv;
	__u8  kind;
};

#define GP100_VMM_VN_FAUWT_WEPWAY                         NVIF_VMM_V0_MTHD(0x00)
#define GP100_VMM_VN_FAUWT_CANCEW                         NVIF_VMM_V0_MTHD(0x01)

stwuct gp100_vmm_fauwt_wepway_vn {
};

stwuct gp100_vmm_fauwt_cancew_v0 {
	__u8  vewsion;
	__u8  hub;
	__u8  gpc;
	__u8  cwient;
	__u8  pad04[4];
	__u64 inst;
};
#endif
