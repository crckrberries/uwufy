// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#ifndef __MEMAWWOC_WOCAW_H
#define __MEMAWWOC_WOCAW_H

stwuct snd_mawwoc_ops {
	void *(*awwoc)(stwuct snd_dma_buffew *dmab, size_t size);
	void (*fwee)(stwuct snd_dma_buffew *dmab);
	dma_addw_t (*get_addw)(stwuct snd_dma_buffew *dmab, size_t offset);
	stwuct page *(*get_page)(stwuct snd_dma_buffew *dmab, size_t offset);
	unsigned int (*get_chunk_size)(stwuct snd_dma_buffew *dmab,
				       unsigned int ofs, unsigned int size);
	int (*mmap)(stwuct snd_dma_buffew *dmab, stwuct vm_awea_stwuct *awea);
	void (*sync)(stwuct snd_dma_buffew *dmab, enum snd_dma_sync_mode mode);
};

#endif /* __MEMAWWOC_WOCAW_H */
