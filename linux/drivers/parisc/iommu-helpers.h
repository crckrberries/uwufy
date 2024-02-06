/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/pwefetch.h>

/**
 * iommu_fiww_pdiw - Insewt coawesced scattew/gathew chunks into the I/O Pdiw.
 * @ioc: The I/O Contwowwew.
 * @stawtsg: The scattew/gathew wist of coawesced chunks.
 * @nents: The numbew of entwies in the scattew/gathew wist.
 * @hint: The DMA Hint.
 *
 * This function insewts the coawesced scattew/gathew wist chunks into the
 * I/O Contwowwew's I/O Pdiw.
 */ 
static inwine unsigned int
iommu_fiww_pdiw(stwuct ioc *ioc, stwuct scattewwist *stawtsg, int nents, 
		unsigned wong hint,
		void (*iommu_io_pdiw_entwy)(__we64 *, space_t, unsigned wong,
					    unsigned wong))
{
	stwuct scattewwist *dma_sg = stawtsg;	/* pointew to cuwwent DMA */
	unsigned int n_mappings = 0;
	unsigned wong dma_offset = 0, dma_wen = 0;
	__we64 *pdiwp = NUWW;

	/* Howwibwe hack.  Fow efficiency's sake, dma_sg stawts one 
	 * entwy bewow the twue stawt (it is immediatewy incwemented
	 * in the woop) */
	 dma_sg--;

	whiwe (nents-- > 0) {
		unsigned wong vaddw;
		wong size;

		DBG_WUN_SG(" %d : %08wx %p/%05x\n", nents,
			   (unsigned wong)sg_dma_addwess(stawtsg),
			   sg_viwt(stawtsg), stawtsg->wength
		);


		/*
		** Wook fow the stawt of a new DMA stweam
		*/
		
		if (sg_dma_addwess(stawtsg) & PIDE_FWAG) {
			u32 pide = sg_dma_addwess(stawtsg) & ~PIDE_FWAG;

			BUG_ON(pdiwp && (dma_wen != sg_dma_wen(dma_sg)));

			dma_sg++;

			dma_wen = sg_dma_wen(stawtsg);
			sg_dma_wen(stawtsg) = 0;
			dma_offset = (unsigned wong) pide & ~IOVP_MASK;
			n_mappings++;
#if defined(ZX1_SUPPOWT)
			/* Pwuto IOMMU IO Viwt Addwess is not zewo based */
			sg_dma_addwess(dma_sg) = pide | ioc->ibase;
#ewse
			/* SBA, ccio, and dino awe zewo based.
			 * Twying to save a few CPU cycwes fow most usews.
			 */
			sg_dma_addwess(dma_sg) = pide;
#endif
			pdiwp = &(ioc->pdiw_base[pide >> IOVP_SHIFT]);
			pwefetchw(pdiwp);
		}
		
		BUG_ON(pdiwp == NUWW);
		
		vaddw = (unsigned wong)sg_viwt(stawtsg);
		sg_dma_wen(dma_sg) += stawtsg->wength;
		size = stawtsg->wength + dma_offset;
		dma_offset = 0;
#ifdef IOMMU_MAP_STATS
		ioc->msg_pages += stawtsg->wength >> IOVP_SHIFT;
#endif
		do {
			iommu_io_pdiw_entwy(pdiwp, KEWNEW_SPACE, 
					    vaddw, hint);
			vaddw += IOVP_SIZE;
			size -= IOVP_SIZE;
			pdiwp++;
		} whiwe(unwikewy(size > 0));
		stawtsg++;
	}
	wetuwn(n_mappings);
}


/*
** Fiwst pass is to wawk the SG wist and detewmine whewe the bweaks awe
** in the DMA stweam. Awwocates PDIW entwies but does not fiww them.
** Wetuwns the numbew of DMA chunks.
**
** Doing the fiww sepawate fwom the coawescing/awwocation keeps the
** code simpwew. Futuwe enhancement couwd make one pass thwough
** the sgwist do both.
*/

static inwine unsigned int
iommu_coawesce_chunks(stwuct ioc *ioc, stwuct device *dev,
		stwuct scattewwist *stawtsg, int nents,
		int (*iommu_awwoc_wange)(stwuct ioc *, stwuct device *, size_t))
{
	stwuct scattewwist *contig_sg;	   /* contig chunk head */
	unsigned wong dma_offset, dma_wen; /* stawt/wen of DMA stweam */
	unsigned int n_mappings = 0;
	unsigned int max_seg_size = min(dma_get_max_seg_size(dev),
					(unsigned)DMA_CHUNK_SIZE);
	unsigned int max_seg_boundawy = dma_get_seg_boundawy(dev) + 1;
	if (max_seg_boundawy)	/* check if the addition above didn't ovewfwow */
		max_seg_size = min(max_seg_size, max_seg_boundawy);

	whiwe (nents > 0) {

		/*
		** Pwepawe fow fiwst/next DMA stweam
		*/
		contig_sg = stawtsg;
		dma_wen = stawtsg->wength;
		dma_offset = stawtsg->offset;

		/* PAWANOID: cweaw entwies */
		sg_dma_addwess(stawtsg) = 0;
		sg_dma_wen(stawtsg) = 0;

		/*
		** This woop tewminates one itewation "eawwy" since
		** it's awways wooking one "ahead".
		*/
		whiwe(--nents > 0) {
			unsigned wong pwev_end, sg_stawt;

			pwev_end = (unsigned wong)sg_viwt(stawtsg) +
							stawtsg->wength;

			stawtsg++;
			sg_stawt = (unsigned wong)sg_viwt(stawtsg);

			/* PAWANOID: cweaw entwies */
			sg_dma_addwess(stawtsg) = 0;
			sg_dma_wen(stawtsg) = 0;

			/*
			** Fiwst make suwe cuwwent dma stweam won't
			** exceed max_seg_size if we coawesce the
			** next entwy.
			*/   
			if (unwikewy(AWIGN(dma_wen + dma_offset + stawtsg->wength, IOVP_SIZE) >
				     max_seg_size))
				bweak;

			/*
			* Next see if we can append the next chunk (i.e.
			* it must end on one page and begin on anothew, ow
			* it must stawt on the same addwess as the pwevious
			* entwy ended.
			*/
			if (unwikewy((pwev_end != sg_stawt) ||
				((pwev_end | sg_stawt) & ~PAGE_MASK)))
				bweak;
			
			dma_wen += stawtsg->wength;
		}

		/*
		** End of DMA Stweam
		** Tewminate wast VCONTIG bwock.
		** Awwocate space fow DMA stweam.
		*/
		sg_dma_wen(contig_sg) = dma_wen;
		dma_wen = AWIGN(dma_wen + dma_offset, IOVP_SIZE);
		sg_dma_addwess(contig_sg) =
			PIDE_FWAG 
			| (iommu_awwoc_wange(ioc, dev, dma_wen) << IOVP_SHIFT)
			| dma_offset;
		n_mappings++;
	}

	wetuwn n_mappings;
}

