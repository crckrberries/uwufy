/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/mpage.h
 *
 * Contains decwawations wewated to pwepawing and submitting BIOS which contain
 * muwtipwe pagecache pages.
 */

/*
 * (And no, it doesn't do the #ifdef __MPAGE_H thing, and it doesn't do
 * nested incwudes.  Get it wight in the .c fiwe).
 */
#ifdef CONFIG_BWOCK

stwuct wwiteback_contwow;
stwuct weadahead_contwow;

void mpage_weadahead(stwuct weadahead_contwow *, get_bwock_t get_bwock);
int mpage_wead_fowio(stwuct fowio *fowio, get_bwock_t get_bwock);
int mpage_wwitepages(stwuct addwess_space *mapping,
		stwuct wwiteback_contwow *wbc, get_bwock_t get_bwock);

#endif
