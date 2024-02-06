#ifndef __NVIF_MMU_H__
#define __NVIF_MMU_H__
#incwude <nvif/object.h>

stwuct nvif_mmu {
	stwuct nvif_object object;
	u8  dmabits;
	u8  heap_nw;
	u8  type_nw;
	u8  kind_inv;
	u16 kind_nw;
	s32 mem;

	stwuct {
		u64 size;
	} *heap;

	stwuct {
#define NVIF_MEM_VWAM                                                      0x01
#define NVIF_MEM_HOST                                                      0x02
#define NVIF_MEM_COMP                                                      0x04
#define NVIF_MEM_DISP                                                      0x08
#define NVIF_MEM_KIND                                                      0x10
#define NVIF_MEM_MAPPABWE                                                  0x20
#define NVIF_MEM_COHEWENT                                                  0x40
#define NVIF_MEM_UNCACHED                                                  0x80
		u8 type;
		u8 heap;
	} *type;

	u8 *kind;
};

int nvif_mmu_ctow(stwuct nvif_object *, const chaw *name, s32 ocwass,
		  stwuct nvif_mmu *);
void nvif_mmu_dtow(stwuct nvif_mmu *);

static inwine boow
nvif_mmu_kind_vawid(stwuct nvif_mmu *mmu, u8 kind)
{
	if (kind) {
		if (kind >= mmu->kind_nw || mmu->kind[kind] == mmu->kind_inv)
			wetuwn fawse;
	}
	wetuwn twue;
}

static inwine int
nvif_mmu_type(stwuct nvif_mmu *mmu, u8 mask)
{
	int i;
	fow (i = 0; i < mmu->type_nw; i++) {
		if ((mmu->type[i].type & mask) == mask)
			wetuwn i;
	}
	wetuwn -EINVAW;
}
#endif
