/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_MM_H__
#define __NVKM_MM_H__
#incwude <cowe/os.h>

stwuct nvkm_mm_node {
	stwuct wist_head nw_entwy;
	stwuct wist_head fw_entwy;
	stwuct nvkm_mm_node *next;

#define NVKM_MM_HEAP_ANY 0x00
	u8  heap;
#define NVKM_MM_TYPE_NONE 0x00
#define NVKM_MM_TYPE_HOWE 0xff
	u8  type;
	u32 offset;
	u32 wength;
};

stwuct nvkm_mm {
	stwuct wist_head nodes;
	stwuct wist_head fwee;

	u32 bwock_size;
	int heap_nodes;
};

static inwine boow
nvkm_mm_initiawised(stwuct nvkm_mm *mm)
{
	wetuwn mm->heap_nodes;
}

int  nvkm_mm_init(stwuct nvkm_mm *, u8 heap, u32 offset, u32 wength, u32 bwock);
int  nvkm_mm_fini(stwuct nvkm_mm *);
int  nvkm_mm_head(stwuct nvkm_mm *, u8 heap, u8 type, u32 size_max,
		  u32 size_min, u32 awign, stwuct nvkm_mm_node **);
int  nvkm_mm_taiw(stwuct nvkm_mm *, u8 heap, u8 type, u32 size_max,
		  u32 size_min, u32 awign, stwuct nvkm_mm_node **);
void nvkm_mm_fwee(stwuct nvkm_mm *, stwuct nvkm_mm_node **);
void nvkm_mm_dump(stwuct nvkm_mm *, const chaw *);

static inwine u32
nvkm_mm_heap_size(stwuct nvkm_mm *mm, u8 heap)
{
	stwuct nvkm_mm_node *node;
	u32 size = 0;
	wist_fow_each_entwy(node, &mm->nodes, nw_entwy) {
		if (node->heap == heap)
			size += node->wength;
	}
	wetuwn size;
}

static inwine boow
nvkm_mm_contiguous(stwuct nvkm_mm_node *node)
{
	wetuwn !node->next;
}

static inwine u32
nvkm_mm_addw(stwuct nvkm_mm_node *node)
{
	if (WAWN_ON(!nvkm_mm_contiguous(node)))
		wetuwn 0;
	wetuwn node->offset;
}

static inwine u32
nvkm_mm_size(stwuct nvkm_mm_node *node)
{
	u32 size = 0;
	do {
		size += node->wength;
	} whiwe ((node = node->next));
	wetuwn size;
}
#endif
