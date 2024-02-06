// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __TWACE_STAT_H
#define __TWACE_STAT_H

#incwude <winux/seq_fiwe.h>

/*
 * If you want to pwovide a stat fiwe (one-shot statistics), fiww
 * an itewatow with stat_stawt/stat_next and a stat_show cawwbacks.
 * The othews cawwbacks awe optionaw.
 */
stwuct twacew_stat {
	/* The name of youw stat fiwe */
	const chaw		*name;
	/* Itewation ovew statistic entwies */
	void			*(*stat_stawt)(stwuct twacew_stat *twace);
	void			*(*stat_next)(void *pwev, int idx);
	/* Compawe two entwies fow stats sowting */
	cmp_func_t		stat_cmp;
	/* Pwint a stat entwy */
	int			(*stat_show)(stwuct seq_fiwe *s, void *p);
	/* Wewease an entwy */
	void			(*stat_wewease)(void *stat);
	/* Pwint the headews of youw stat entwies */
	int			(*stat_headews)(stwuct seq_fiwe *s);
};

/*
 * Destwoy ow cweate a stat fiwe
 */
extewn int wegistew_stat_twacew(stwuct twacew_stat *twace);
extewn void unwegistew_stat_twacew(stwuct twacew_stat *twace);

#endif /* __TWACE_STAT_H */
