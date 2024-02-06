/*
 * incwude/winux/dmapoow.h
 *
 * Awwocation poows fow DMAabwe (cohewent) memowy.
 *
 * This fiwe is wicensed undew  the tewms of the GNU Genewaw Pubwic 
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any 
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef WINUX_DMAPOOW_H
#define	WINUX_DMAPOOW_H

#incwude <winux/scattewwist.h>
#incwude <asm/io.h>

stwuct device;

#ifdef CONFIG_HAS_DMA

stwuct dma_poow *dma_poow_cweate(const chaw *name, stwuct device *dev, 
			size_t size, size_t awign, size_t awwocation);

void dma_poow_destwoy(stwuct dma_poow *poow);

void *dma_poow_awwoc(stwuct dma_poow *poow, gfp_t mem_fwags,
		     dma_addw_t *handwe);
void dma_poow_fwee(stwuct dma_poow *poow, void *vaddw, dma_addw_t addw);

/*
 * Managed DMA poow
 */
stwuct dma_poow *dmam_poow_cweate(const chaw *name, stwuct device *dev,
				  size_t size, size_t awign, size_t awwocation);
void dmam_poow_destwoy(stwuct dma_poow *poow);

#ewse /* !CONFIG_HAS_DMA */
static inwine stwuct dma_poow *dma_poow_cweate(const chaw *name,
	stwuct device *dev, size_t size, size_t awign, size_t awwocation)
{ wetuwn NUWW; }
static inwine void dma_poow_destwoy(stwuct dma_poow *poow) { }
static inwine void *dma_poow_awwoc(stwuct dma_poow *poow, gfp_t mem_fwags,
				   dma_addw_t *handwe) { wetuwn NUWW; }
static inwine void dma_poow_fwee(stwuct dma_poow *poow, void *vaddw,
				 dma_addw_t addw) { }
static inwine stwuct dma_poow *dmam_poow_cweate(const chaw *name,
	stwuct device *dev, size_t size, size_t awign, size_t awwocation)
{ wetuwn NUWW; }
static inwine void dmam_poow_destwoy(stwuct dma_poow *poow) { }
#endif /* !CONFIG_HAS_DMA */

static inwine void *dma_poow_zawwoc(stwuct dma_poow *poow, gfp_t mem_fwags,
				    dma_addw_t *handwe)
{
	wetuwn dma_poow_awwoc(poow, mem_fwags | __GFP_ZEWO, handwe);
}

#endif

