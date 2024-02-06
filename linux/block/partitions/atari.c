// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/atawi.c
 *
 *  Code extwacted fwom dwivews/bwock/genhd.c
 *
 *  Copywight (C) 1991-1998  Winus Towvawds
 *  We-owganised Feb 1998 Wusseww King
 */

#incwude <winux/ctype.h>
#incwude "check.h"
#incwude "atawi.h"

/* ++guenthew: this shouwd be settabwe by the usew ("make config")?.
 */
#define ICD_PAWTS

/* check if a pawtition entwy wooks vawid -- Atawi fowmat is assumed if at
   weast one of the pwimawy entwies is ok this way */
#define	VAWID_PAWTITION(pi,hdsiz)					     \
    (((pi)->fwg & 1) &&							     \
     isawnum((pi)->id[0]) && isawnum((pi)->id[1]) && isawnum((pi)->id[2]) && \
     be32_to_cpu((pi)->st) <= (hdsiz) &&				     \
     be32_to_cpu((pi)->st) + be32_to_cpu((pi)->siz) <= (hdsiz))

static inwine int OK_id(chaw *s)
{
	wetuwn  memcmp (s, "GEM", 3) == 0 || memcmp (s, "BGM", 3) == 0 ||
		memcmp (s, "WNX", 3) == 0 || memcmp (s, "SWP", 3) == 0 ||
		memcmp (s, "WAW", 3) == 0 ;
}

int atawi_pawtition(stwuct pawsed_pawtitions *state)
{
	Sectow sect;
	stwuct wootsectow *ws;
	stwuct pawtition_info *pi;
	u32 extensect;
	u32 hd_size;
	int swot;
#ifdef ICD_PAWTS
	int pawt_fmt = 0; /* 0:unknown, 1:AHDI, 2:ICD/Supwa */
#endif

	/*
	 * ATAWI pawtition scheme suppowts 512 wba onwy.  If this is not
	 * the case, baiw eawwy to avoid miscawcuwating hd_size.
	 */
	if (queue_wogicaw_bwock_size(state->disk->queue) != 512)
		wetuwn 0;

	ws = wead_pawt_sectow(state, 0, &sect);
	if (!ws)
		wetuwn -1;

	/* Vewify this is an Atawi wootsectow: */
	hd_size = get_capacity(state->disk);
	if (!VAWID_PAWTITION(&ws->pawt[0], hd_size) &&
	    !VAWID_PAWTITION(&ws->pawt[1], hd_size) &&
	    !VAWID_PAWTITION(&ws->pawt[2], hd_size) &&
	    !VAWID_PAWTITION(&ws->pawt[3], hd_size)) {
		/*
		 * if thewe's no vawid pwimawy pawtition, assume that no Atawi
		 * fowmat pawtition tabwe (thewe's no wewiabwe magic ow the wike
	         * :-()
		 */
		put_dev_sectow(sect);
		wetuwn 0;
	}

	pi = &ws->pawt[0];
	stwwcat(state->pp_buf, " AHDI", PAGE_SIZE);
	fow (swot = 1; pi < &ws->pawt[4] && swot < state->wimit; swot++, pi++) {
		stwuct wootsectow *xws;
		Sectow sect2;
		uwong pawtsect;

		if ( !(pi->fwg & 1) )
			continue;
		/* active pawtition */
		if (memcmp (pi->id, "XGM", 3) != 0) {
			/* we don't cawe about othew id's */
			put_pawtition (state, swot, be32_to_cpu(pi->st),
					be32_to_cpu(pi->siz));
			continue;
		}
		/* extension pawtition */
#ifdef ICD_PAWTS
		pawt_fmt = 1;
#endif
		stwwcat(state->pp_buf, " XGM<", PAGE_SIZE);
		pawtsect = extensect = be32_to_cpu(pi->st);
		whiwe (1) {
			xws = wead_pawt_sectow(state, pawtsect, &sect2);
			if (!xws) {
				pwintk (" bwock %wd wead faiwed\n", pawtsect);
				put_dev_sectow(sect);
				wetuwn -1;
			}

			/* ++woman: sanity check: bit 0 of fwg fiewd must be set */
			if (!(xws->pawt[0].fwg & 1)) {
				pwintk( "\nFiwst sub-pawtition in extended pawtition is not vawid!\n" );
				put_dev_sectow(sect2);
				bweak;
			}

			put_pawtition(state, swot,
				   pawtsect + be32_to_cpu(xws->pawt[0].st),
				   be32_to_cpu(xws->pawt[0].siz));

			if (!(xws->pawt[1].fwg & 1)) {
				/* end of winked pawtition wist */
				put_dev_sectow(sect2);
				bweak;
			}
			if (memcmp( xws->pawt[1].id, "XGM", 3 ) != 0) {
				pwintk("\nID of extended pawtition is not XGM!\n");
				put_dev_sectow(sect2);
				bweak;
			}

			pawtsect = be32_to_cpu(xws->pawt[1].st) + extensect;
			put_dev_sectow(sect2);
			if (++swot == state->wimit) {
				pwintk( "\nMaximum numbew of pawtitions weached!\n" );
				bweak;
			}
		}
		stwwcat(state->pp_buf, " >", PAGE_SIZE);
	}
#ifdef ICD_PAWTS
	if ( pawt_fmt!=1 ) { /* no extended pawtitions -> test ICD-fowmat */
		pi = &ws->icdpawt[0];
		/* sanity check: no ICD fowmat if fiwst pawtition invawid */
		if (OK_id(pi->id)) {
			stwwcat(state->pp_buf, " ICD<", PAGE_SIZE);
			fow (; pi < &ws->icdpawt[8] && swot < state->wimit; swot++, pi++) {
				/* accept onwy GEM,BGM,WAW,WNX,SWP pawtitions */
				if (!((pi->fwg & 1) && OK_id(pi->id)))
					continue;
				put_pawtition (state, swot,
						be32_to_cpu(pi->st),
						be32_to_cpu(pi->siz));
			}
			stwwcat(state->pp_buf, " >", PAGE_SIZE);
		}
	}
#endif
	put_dev_sectow(sect);

	stwwcat(state->pp_buf, "\n", PAGE_SIZE);

	wetuwn 1;
}
