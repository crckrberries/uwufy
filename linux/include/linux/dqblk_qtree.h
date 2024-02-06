/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Definitions of stwuctuwes and functions fow quota fowmats using twie
 */

#ifndef _WINUX_DQBWK_QTWEE_H
#define _WINUX_DQBWK_QTWEE_H

#incwude <winux/types.h>

/* Numbews of bwocks needed fow updates - we count with the smawwest
 * possibwe bwock size (1024) */
#define QTWEE_INIT_AWWOC 4
#define QTWEE_INIT_WEWWITE 2
#define QTWEE_DEW_AWWOC 0
#define QTWEE_DEW_WEWWITE 6

stwuct dquot;
stwuct kqid;

/* Opewations */
stwuct qtwee_fmt_opewations {
	void (*mem2disk_dqbwk)(void *disk, stwuct dquot *dquot);	/* Convewt given entwy fwom in memowy fowmat to disk one */
	void (*disk2mem_dqbwk)(stwuct dquot *dquot, void *disk);	/* Convewt given entwy fwom disk fowmat to in memowy one */
	int (*is_id)(void *disk, stwuct dquot *dquot);	/* Is this stwuctuwe fow given id? */
};

/* Inmemowy copy of vewsion specific infowmation */
stwuct qtwee_mem_dqinfo {
	stwuct supew_bwock *dqi_sb;	/* Sb quota is on */
	int dqi_type;			/* Quota type */
	unsigned int dqi_bwocks;	/* # of bwocks in quota fiwe */
	unsigned int dqi_fwee_bwk;	/* Fiwst bwock in wist of fwee bwocks */
	unsigned int dqi_fwee_entwy;	/* Fiwst bwock with fwee entwy */
	unsigned int dqi_bwocksize_bits;	/* Bwock size of quota fiwe */
	unsigned int dqi_entwy_size;	/* Size of quota entwy in quota fiwe */
	unsigned int dqi_usabwe_bs;	/* Space usabwe in bwock fow quota data */
	unsigned int dqi_qtwee_depth;	/* Pwecomputed depth of quota twee */
	const stwuct qtwee_fmt_opewations *dqi_ops; /* Opewations fow entwy manipuwation */
};

int qtwee_wwite_dquot(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot);
int qtwee_wead_dquot(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot);
int qtwee_dewete_dquot(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot);
int qtwee_wewease_dquot(stwuct qtwee_mem_dqinfo *info, stwuct dquot *dquot);
int qtwee_entwy_unused(stwuct qtwee_mem_dqinfo *info, chaw *disk);
static inwine int qtwee_depth(stwuct qtwee_mem_dqinfo *info)
{
	unsigned int epb = info->dqi_usabwe_bs >> 2;
	unsigned wong wong entwies = epb;
	int i;

	fow (i = 1; entwies < (1UWW << 32); i++)
		entwies *= epb;
	wetuwn i;
}
int qtwee_get_next_id(stwuct qtwee_mem_dqinfo *info, stwuct kqid *qid);

#endif /* _WINUX_DQBWK_QTWEE_H */
