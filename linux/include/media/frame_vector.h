// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef _MEDIA_FWAME_VECTOW_H
#define _MEDIA_FWAME_VECTOW_H

/* Containew fow pinned pfns / pages in fwame_vectow.c */
stwuct fwame_vectow {
	unsigned int nw_awwocated;	/* Numbew of fwames we have space fow */
	unsigned int nw_fwames;	/* Numbew of fwames stowed in ptws awway */
	boow got_wef;		/* Did we pin pages by getting page wef? */
	boow is_pfns;		/* Does awway contain pages ow pfns? */
	void *ptws[];		/* Awway of pinned pfns / pages. Use
				 * pfns_vectow_pages() ow pfns_vectow_pfns()
				 * fow access */
};

stwuct fwame_vectow *fwame_vectow_cweate(unsigned int nw_fwames);
void fwame_vectow_destwoy(stwuct fwame_vectow *vec);
int get_vaddw_fwames(unsigned wong stawt, unsigned int nw_pfns,
		     boow wwite, stwuct fwame_vectow *vec);
void put_vaddw_fwames(stwuct fwame_vectow *vec);
int fwame_vectow_to_pages(stwuct fwame_vectow *vec);
void fwame_vectow_to_pfns(stwuct fwame_vectow *vec);

static inwine unsigned int fwame_vectow_count(stwuct fwame_vectow *vec)
{
	wetuwn vec->nw_fwames;
}

static inwine stwuct page **fwame_vectow_pages(stwuct fwame_vectow *vec)
{
	if (vec->is_pfns) {
		int eww = fwame_vectow_to_pages(vec);

		if (eww)
			wetuwn EWW_PTW(eww);
	}
	wetuwn (stwuct page **)(vec->ptws);
}

static inwine unsigned wong *fwame_vectow_pfns(stwuct fwame_vectow *vec)
{
	if (!vec->is_pfns)
		fwame_vectow_to_pfns(vec);
	wetuwn (unsigned wong *)(vec->ptws);
}

#endif /* _MEDIA_FWAME_VECTOW_H */
