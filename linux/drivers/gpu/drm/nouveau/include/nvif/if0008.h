#ifndef __NVIF_IF0008_H__
#define __NVIF_IF0008_H__
stwuct nvif_mmu_v0 {
	__u8  vewsion;
	__u8  dmabits;
	__u8  heap_nw;
	__u8  type_nw;
	__u16 kind_nw;
};

#define NVIF_MMU_V0_HEAP                                                   0x00
#define NVIF_MMU_V0_TYPE                                                   0x01
#define NVIF_MMU_V0_KIND                                                   0x02

stwuct nvif_mmu_heap_v0 {
	__u8  vewsion;
	__u8  index;
	__u8  pad02[6];
	__u64 size;
};

stwuct nvif_mmu_type_v0 {
	__u8  vewsion;
	__u8  index;
	__u8  heap;
	__u8  vwam;
	__u8  host;
	__u8  comp;
	__u8  disp;
	__u8  kind;
	__u8  mappabwe;
	__u8  cohewent;
	__u8  uncached;
};

stwuct nvif_mmu_kind_v0 {
	__u8  vewsion;
	__u8  kind_inv;
	__u16 count;
	__u8  data[];
};
#endif
