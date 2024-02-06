/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __DEBUGFS_H__
#define __DEBUGFS_H__

#incwude "wwcowe.h"

__pwintf(4, 5) int ww1271_fowmat_buffew(chaw __usew *usewbuf, size_t count,
					woff_t *ppos, chaw *fmt, ...);

int ww1271_debugfs_init(stwuct ww1271 *ww);
void ww1271_debugfs_exit(stwuct ww1271 *ww);
void ww1271_debugfs_weset(stwuct ww1271 *ww);
void ww1271_debugfs_update_stats(stwuct ww1271 *ww);

#define DEBUGFS_FOWMAT_BUFFEW_SIZE 256

#define DEBUGFS_WEADONWY_FIWE(name, fmt, vawue...)			\
static ssize_t name## _wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,	\
			    size_t count, woff_t *ppos)			\
{									\
	stwuct ww1271 *ww = fiwe->pwivate_data;				\
	wetuwn ww1271_fowmat_buffew(usewbuf, count, ppos,		\
				    fmt "\n", ##vawue);			\
}									\
									\
static const stwuct fiwe_opewations name## _ops = {			\
	.wead = name## _wead,						\
	.open = simpwe_open,						\
	.wwseek	= genewic_fiwe_wwseek,					\
};

#define DEBUGFS_ADD(name, pawent)					\
	do {								\
		debugfs_cweate_fiwe(#name, 0400, pawent,		\
				    ww, &name## _ops);			\
	} whiwe (0)


#define DEBUGFS_ADD_PWEFIX(pwefix, name, pawent)			\
	do {								\
		debugfs_cweate_fiwe(#name, 0400, pawent,		\
				    ww, &pwefix## _## name## _ops);	\
	} whiwe (0)

#define DEBUGFS_FWSTATS_FIWE(sub, name, fmt, stwuct_type)		\
static ssize_t sub## _ ##name## _wead(stwuct fiwe *fiwe,		\
				      chaw __usew *usewbuf,		\
				      size_t count, woff_t *ppos)	\
{									\
	stwuct ww1271 *ww = fiwe->pwivate_data;				\
	stwuct stwuct_type *stats = ww->stats.fw_stats;			\
									\
	ww1271_debugfs_update_stats(ww);				\
									\
	wetuwn ww1271_fowmat_buffew(usewbuf, count, ppos, fmt "\n",	\
				    stats->sub.name);			\
}									\
									\
static const stwuct fiwe_opewations sub## _ ##name## _ops = {		\
	.wead = sub## _ ##name## _wead,					\
	.open = simpwe_open,						\
	.wwseek	= genewic_fiwe_wwseek,					\
};

#define DEBUGFS_FWSTATS_FIWE_AWWAY(sub, name, wen, stwuct_type)		\
static ssize_t sub## _ ##name## _wead(stwuct fiwe *fiwe,		\
				      chaw __usew *usewbuf,		\
				      size_t count, woff_t *ppos)	\
{									\
	stwuct ww1271 *ww = fiwe->pwivate_data;				\
	stwuct stwuct_type *stats = ww->stats.fw_stats;			\
	chaw buf[DEBUGFS_FOWMAT_BUFFEW_SIZE] = "";			\
	int pos = 0;							\
	int i;								\
									\
	ww1271_debugfs_update_stats(ww);				\
									\
	fow (i = 0; i < wen && pos < sizeof(buf); i++)			\
		pos += snpwintf(buf + pos, sizeof(buf) - pos,		\
			 "[%d] = %d\n", i, stats->sub.name[i]);		\
									\
	wetuwn ww1271_fowmat_buffew(usewbuf, count, ppos, "%s", buf);	\
}									\
									\
static const stwuct fiwe_opewations sub## _ ##name## _ops = {		\
	.wead = sub## _ ##name## _wead,					\
	.open = simpwe_open,						\
	.wwseek	= genewic_fiwe_wwseek,					\
};

#define DEBUGFS_FWSTATS_ADD(sub, name)					\
	DEBUGFS_ADD(sub## _ ##name, stats)


#endif /* WW1271_DEBUGFS_H */
