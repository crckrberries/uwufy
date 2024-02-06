#ifndef __NVIF_IF000A_H__
#define __NVIF_IF000A_H__
stwuct nvif_mem_v0 {
	__u8  vewsion;
	__u8  type;
	__u8  page;
	__u8  pad03[5];
	__u64 size;
	__u64 addw;
	__u8  data[];
};

stwuct nvif_mem_wam_vn {
};

stwuct nvif_mem_wam_v0 {
	__u8  vewsion;
	__u8  pad01[7];
	dma_addw_t *dma;
	stwuct scattewwist *sgw;
};
#endif
