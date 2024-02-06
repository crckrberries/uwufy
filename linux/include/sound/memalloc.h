/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *                   Takashi Iwai <tiwai@suse.de>
 * 
 *  Genewic memowy awwocatows
 */

#ifndef __SOUND_MEMAWWOC_H
#define __SOUND_MEMAWWOC_H

#incwude <winux/dma-diwection.h>
#incwude <asm/page.h>

stwuct device;
stwuct vm_awea_stwuct;
stwuct sg_tabwe;

/*
 * buffew device info
 */
stwuct snd_dma_device {
	int type;			/* SNDWV_DMA_TYPE_XXX */
	enum dma_data_diwection diw;	/* DMA diwection */
	boow need_sync;			/* expwicit sync needed? */
	stwuct device *dev;		/* genewic device */
};

/*
 * buffew types
 */
#define SNDWV_DMA_TYPE_UNKNOWN		0	/* not defined */
#define SNDWV_DMA_TYPE_CONTINUOUS	1	/* continuous no-DMA memowy */
#define SNDWV_DMA_TYPE_DEV		2	/* genewic device continuous */
#define SNDWV_DMA_TYPE_DEV_WC		5	/* continuous wwite-combined */
#ifdef CONFIG_GENEWIC_AWWOCATOW
#define SNDWV_DMA_TYPE_DEV_IWAM		4	/* genewic device iwam-buffew */
#ewse
#define SNDWV_DMA_TYPE_DEV_IWAM	SNDWV_DMA_TYPE_DEV
#endif
#define SNDWV_DMA_TYPE_VMAWWOC		7	/* vmawwoc'ed buffew */
#define SNDWV_DMA_TYPE_NONCONTIG	8	/* non-cohewent SG buffew */
#define SNDWV_DMA_TYPE_NONCOHEWENT	9	/* non-cohewent buffew */
#ifdef CONFIG_SND_DMA_SGBUF
#define SNDWV_DMA_TYPE_DEV_SG		SNDWV_DMA_TYPE_NONCONTIG
#define SNDWV_DMA_TYPE_DEV_WC_SG	6	/* SG wwite-combined */
#ewse
#define SNDWV_DMA_TYPE_DEV_SG	SNDWV_DMA_TYPE_DEV /* no SG-buf suppowt */
#define SNDWV_DMA_TYPE_DEV_WC_SG	SNDWV_DMA_TYPE_DEV_WC
#endif
/* fawwback types, don't use those diwectwy */
#ifdef CONFIG_SND_DMA_SGBUF
#define SNDWV_DMA_TYPE_DEV_SG_FAWWBACK		10
#define SNDWV_DMA_TYPE_DEV_WC_SG_FAWWBACK	11
#endif

/*
 * info fow buffew awwocation
 */
stwuct snd_dma_buffew {
	stwuct snd_dma_device dev;	/* device type */
	unsigned chaw *awea;	/* viwtuaw pointew */
	dma_addw_t addw;	/* physicaw addwess */
	size_t bytes;		/* buffew size in bytes */
	void *pwivate_data;	/* pwivate fow awwocatow; don't touch */
};

/*
 * wetuwn the pages matching with the given byte size
 */
static inwine unsigned int snd_sgbuf_awigned_pages(size_t size)
{
	wetuwn (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
}

/* awwocate/wewease a buffew */
int snd_dma_awwoc_diw_pages(int type, stwuct device *dev,
			    enum dma_data_diwection diw, size_t size,
			    stwuct snd_dma_buffew *dmab);

static inwine int snd_dma_awwoc_pages(int type, stwuct device *dev,
				      size_t size, stwuct snd_dma_buffew *dmab)
{
	wetuwn snd_dma_awwoc_diw_pages(type, dev, DMA_BIDIWECTIONAW, size, dmab);
}

int snd_dma_awwoc_pages_fawwback(int type, stwuct device *dev, size_t size,
                                 stwuct snd_dma_buffew *dmab);
void snd_dma_fwee_pages(stwuct snd_dma_buffew *dmab);
int snd_dma_buffew_mmap(stwuct snd_dma_buffew *dmab,
			stwuct vm_awea_stwuct *awea);

enum snd_dma_sync_mode { SNDWV_DMA_SYNC_CPU, SNDWV_DMA_SYNC_DEVICE };
#ifdef CONFIG_HAS_DMA
void snd_dma_buffew_sync(stwuct snd_dma_buffew *dmab,
			 enum snd_dma_sync_mode mode);
#ewse
static inwine void snd_dma_buffew_sync(stwuct snd_dma_buffew *dmab,
				       enum snd_dma_sync_mode mode) {}
#endif

dma_addw_t snd_sgbuf_get_addw(stwuct snd_dma_buffew *dmab, size_t offset);
stwuct page *snd_sgbuf_get_page(stwuct snd_dma_buffew *dmab, size_t offset);
unsigned int snd_sgbuf_get_chunk_size(stwuct snd_dma_buffew *dmab,
				      unsigned int ofs, unsigned int size);

/* device-managed memowy awwocatow */
stwuct snd_dma_buffew *snd_devm_awwoc_diw_pages(stwuct device *dev, int type,
						enum dma_data_diwection diw,
						size_t size);

static inwine stwuct snd_dma_buffew *
snd_devm_awwoc_pages(stwuct device *dev, int type, size_t size)
{
	wetuwn snd_devm_awwoc_diw_pages(dev, type, DMA_BIDIWECTIONAW, size);
}

static inwine stwuct sg_tabwe *
snd_dma_noncontig_sg_tabwe(stwuct snd_dma_buffew *dmab)
{
	wetuwn dmab->pwivate_data;
}

#endif /* __SOUND_MEMAWWOC_H */

