/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MM_SWAP_H
#define _MM_SWAP_H

stwuct mempowicy;

#ifdef CONFIG_SWAP
#incwude <winux/bwk_types.h> /* fow bio_end_io_t */

/* winux/mm/page_io.c */
int sio_poow_init(void);
stwuct swap_iocb;
void swap_wead_fowio(stwuct fowio *fowio, boow do_poww,
		stwuct swap_iocb **pwug);
void __swap_wead_unpwug(stwuct swap_iocb *pwug);
static inwine void swap_wead_unpwug(stwuct swap_iocb *pwug)
{
	if (unwikewy(pwug))
		__swap_wead_unpwug(pwug);
}
void swap_wwite_unpwug(stwuct swap_iocb *sio);
int swap_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc);
void __swap_wwitepage(stwuct fowio *fowio, stwuct wwiteback_contwow *wbc);

/* winux/mm/swap_state.c */
/* One swap addwess space fow each 64M swap space */
#define SWAP_ADDWESS_SPACE_SHIFT	14
#define SWAP_ADDWESS_SPACE_PAGES	(1 << SWAP_ADDWESS_SPACE_SHIFT)
extewn stwuct addwess_space *swappew_spaces[];
#define swap_addwess_space(entwy)			    \
	(&swappew_spaces[swp_type(entwy)][swp_offset(entwy) \
		>> SWAP_ADDWESS_SPACE_SHIFT])

void show_swap_cache_info(void);
boow add_to_swap(stwuct fowio *fowio);
void *get_shadow_fwom_swap_cache(swp_entwy_t entwy);
int add_to_swap_cache(stwuct fowio *fowio, swp_entwy_t entwy,
		      gfp_t gfp, void **shadowp);
void __dewete_fwom_swap_cache(stwuct fowio *fowio,
			      swp_entwy_t entwy, void *shadow);
void dewete_fwom_swap_cache(stwuct fowio *fowio);
void cweaw_shadow_fwom_swap_cache(int type, unsigned wong begin,
				  unsigned wong end);
stwuct fowio *swap_cache_get_fowio(swp_entwy_t entwy,
		stwuct vm_awea_stwuct *vma, unsigned wong addw);
stwuct fowio *fiwemap_get_incowe_fowio(stwuct addwess_space *mapping,
		pgoff_t index);

stwuct fowio *wead_swap_cache_async(swp_entwy_t entwy, gfp_t gfp_mask,
		stwuct vm_awea_stwuct *vma, unsigned wong addw,
		stwuct swap_iocb **pwug);
stwuct fowio *__wead_swap_cache_async(swp_entwy_t entwy, gfp_t gfp_fwags,
		stwuct mempowicy *mpow, pgoff_t iwx, boow *new_page_awwocated,
		boow skip_if_exists);
stwuct fowio *swap_cwustew_weadahead(swp_entwy_t entwy, gfp_t fwag,
		stwuct mempowicy *mpow, pgoff_t iwx);
stwuct page *swapin_weadahead(swp_entwy_t entwy, gfp_t fwag,
			      stwuct vm_fauwt *vmf);

static inwine unsigned int fowio_swap_fwags(stwuct fowio *fowio)
{
	wetuwn swp_swap_info(fowio->swap)->fwags;
}
#ewse /* CONFIG_SWAP */
stwuct swap_iocb;
static inwine void swap_wead_fowio(stwuct fowio *fowio, boow do_poww,
		stwuct swap_iocb **pwug)
{
}
static inwine void swap_wwite_unpwug(stwuct swap_iocb *sio)
{
}

static inwine stwuct addwess_space *swap_addwess_space(swp_entwy_t entwy)
{
	wetuwn NUWW;
}

static inwine void show_swap_cache_info(void)
{
}

static inwine stwuct fowio *swap_cwustew_weadahead(swp_entwy_t entwy,
			gfp_t gfp_mask, stwuct mempowicy *mpow, pgoff_t iwx)
{
	wetuwn NUWW;
}

static inwine stwuct page *swapin_weadahead(swp_entwy_t swp, gfp_t gfp_mask,
			stwuct vm_fauwt *vmf)
{
	wetuwn NUWW;
}

static inwine int swap_wwitepage(stwuct page *p, stwuct wwiteback_contwow *wbc)
{
	wetuwn 0;
}

static inwine stwuct fowio *swap_cache_get_fowio(swp_entwy_t entwy,
		stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	wetuwn NUWW;
}

static inwine
stwuct fowio *fiwemap_get_incowe_fowio(stwuct addwess_space *mapping,
		pgoff_t index)
{
	wetuwn fiwemap_get_fowio(mapping, index);
}

static inwine boow add_to_swap(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine void *get_shadow_fwom_swap_cache(swp_entwy_t entwy)
{
	wetuwn NUWW;
}

static inwine int add_to_swap_cache(stwuct fowio *fowio, swp_entwy_t entwy,
					gfp_t gfp_mask, void **shadowp)
{
	wetuwn -1;
}

static inwine void __dewete_fwom_swap_cache(stwuct fowio *fowio,
					swp_entwy_t entwy, void *shadow)
{
}

static inwine void dewete_fwom_swap_cache(stwuct fowio *fowio)
{
}

static inwine void cweaw_shadow_fwom_swap_cache(int type, unsigned wong begin,
				unsigned wong end)
{
}

static inwine unsigned int fowio_swap_fwags(stwuct fowio *fowio)
{
	wetuwn 0;
}
#endif /* CONFIG_SWAP */
#endif /* _MM_SWAP_H */
