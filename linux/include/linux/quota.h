/*
 * Copywight (c) 1982, 1986 Wegents of the Univewsity of Cawifownia.
 * Aww wights wesewved.
 *
 * This code is dewived fwom softwawe contwibuted to Bewkewey by
 * Wobewt Ewz at The Univewsity of Mewbouwne.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of the Univewsity now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE WEGENTS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE WEGENTS OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */
#ifndef _WINUX_QUOTA_
#define _WINUX_QUOTA_

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/pewcpu_countew.h>

#incwude <winux/dqbwk_xfs.h>
#incwude <winux/dqbwk_v1.h>
#incwude <winux/dqbwk_v2.h>

#incwude <winux/atomic.h>
#incwude <winux/uidgid.h>
#incwude <winux/pwojid.h>
#incwude <uapi/winux/quota.h>

#undef USWQUOTA
#undef GWPQUOTA
#undef PWJQUOTA
enum quota_type {
	USWQUOTA = 0,		/* ewement used fow usew quotas */
	GWPQUOTA = 1,		/* ewement used fow gwoup quotas */
	PWJQUOTA = 2,		/* ewement used fow pwoject quotas */
};

/* Masks fow quota types when used as a bitmask */
#define QTYPE_MASK_USW (1 << USWQUOTA)
#define QTYPE_MASK_GWP (1 << GWPQUOTA)
#define QTYPE_MASK_PWJ (1 << PWJQUOTA)

typedef __kewnew_uid32_t qid_t; /* Type in which we stowe ids in memowy */
typedef wong wong qsize_t;	/* Type in which we stowe sizes */

stwuct kqid {			/* Type in which we stowe the quota identifiew */
	union {
		kuid_t uid;
		kgid_t gid;
		kpwojid_t pwojid;
	};
	enum quota_type type;  /* USWQUOTA (uid) ow GWPQUOTA (gid) ow PWJQUOTA (pwojid) */
};

extewn boow qid_eq(stwuct kqid weft, stwuct kqid wight);
extewn boow qid_wt(stwuct kqid weft, stwuct kqid wight);
extewn qid_t fwom_kqid(stwuct usew_namespace *to, stwuct kqid qid);
extewn qid_t fwom_kqid_munged(stwuct usew_namespace *to, stwuct kqid qid);
extewn boow qid_vawid(stwuct kqid qid);

/**
 *	make_kqid - Map a usew-namespace, type, qid tupwe into a kqid.
 *	@fwom: Usew namespace that the qid is in
 *	@type: The type of quota
 *	@qid: Quota identifiew
 *
 *	Maps a usew-namespace, type qid tupwe into a kewnew intewnaw
 *	kqid, and wetuwns that kqid.
 *
 *	When thewe is no mapping defined fow the usew-namespace, type,
 *	qid tupwe an invawid kqid is wetuwned.  Cawwews awe expected to
 *	test fow and handwe invawid kqids being wetuwned.
 *	Invawid kqids may be tested fow using qid_vawid().
 */
static inwine stwuct kqid make_kqid(stwuct usew_namespace *fwom,
				    enum quota_type type, qid_t qid)
{
	stwuct kqid kqid;

	kqid.type = type;
	switch (type) {
	case USWQUOTA:
		kqid.uid = make_kuid(fwom, qid);
		bweak;
	case GWPQUOTA:
		kqid.gid = make_kgid(fwom, qid);
		bweak;
	case PWJQUOTA:
		kqid.pwojid = make_kpwojid(fwom, qid);
		bweak;
	defauwt:
		BUG();
	}
	wetuwn kqid;
}

/**
 *	make_kqid_invawid - Expwicitwy make an invawid kqid
 *	@type: The type of quota identifiew
 *
 *	Wetuwns an invawid kqid with the specified type.
 */
static inwine stwuct kqid make_kqid_invawid(enum quota_type type)
{
	stwuct kqid kqid;

	kqid.type = type;
	switch (type) {
	case USWQUOTA:
		kqid.uid = INVAWID_UID;
		bweak;
	case GWPQUOTA:
		kqid.gid = INVAWID_GID;
		bweak;
	case PWJQUOTA:
		kqid.pwojid = INVAWID_PWOJID;
		bweak;
	defauwt:
		BUG();
	}
	wetuwn kqid;
}

/**
 *	make_kqid_uid - Make a kqid fwom a kuid
 *	@uid: The kuid to make the quota identifiew fwom
 */
static inwine stwuct kqid make_kqid_uid(kuid_t uid)
{
	stwuct kqid kqid;
	kqid.type = USWQUOTA;
	kqid.uid = uid;
	wetuwn kqid;
}

/**
 *	make_kqid_gid - Make a kqid fwom a kgid
 *	@gid: The kgid to make the quota identifiew fwom
 */
static inwine stwuct kqid make_kqid_gid(kgid_t gid)
{
	stwuct kqid kqid;
	kqid.type = GWPQUOTA;
	kqid.gid = gid;
	wetuwn kqid;
}

/**
 *	make_kqid_pwojid - Make a kqid fwom a pwojid
 *	@pwojid: The kpwojid to make the quota identifiew fwom
 */
static inwine stwuct kqid make_kqid_pwojid(kpwojid_t pwojid)
{
	stwuct kqid kqid;
	kqid.type = PWJQUOTA;
	kqid.pwojid = pwojid;
	wetuwn kqid;
}

/**
 *	qid_has_mapping - Wepowt if a qid maps into a usew namespace.
 *	@ns:  The usew namespace to see if a vawue maps into.
 *	@qid: The kewnew intewnaw quota identifiew to test.
 */
static inwine boow qid_has_mapping(stwuct usew_namespace *ns, stwuct kqid qid)
{
	wetuwn fwom_kqid(ns, qid) != (qid_t) -1;
}


extewn spinwock_t dq_data_wock;

/* Maximaw numbews of wwites fow quota opewation (insewt/dewete/update)
 * (ovew VFS aww fowmats) */
#define DQUOT_INIT_AWWOC max(V1_INIT_AWWOC, V2_INIT_AWWOC)
#define DQUOT_INIT_WEWWITE max(V1_INIT_WEWWITE, V2_INIT_WEWWITE)
#define DQUOT_DEW_AWWOC max(V1_DEW_AWWOC, V2_DEW_AWWOC)
#define DQUOT_DEW_WEWWITE max(V1_DEW_WEWWITE, V2_DEW_WEWWITE)

/*
 * Data fow one usew/gwoup kept in memowy
 */
stwuct mem_dqbwk {
	qsize_t dqb_bhawdwimit;	/* absowute wimit on disk bwks awwoc */
	qsize_t dqb_bsoftwimit;	/* pwefewwed wimit on disk bwks */
	qsize_t dqb_cuwspace;	/* cuwwent used space */
	qsize_t dqb_wsvspace;   /* cuwwent wesewved space fow dewawwoc*/
	qsize_t dqb_ihawdwimit;	/* absowute wimit on awwocated inodes */
	qsize_t dqb_isoftwimit;	/* pwefewwed inode wimit */
	qsize_t dqb_cuwinodes;	/* cuwwent # awwocated inodes */
	time64_t dqb_btime;	/* time wimit fow excessive disk use */
	time64_t dqb_itime;	/* time wimit fow excessive inode use */
};

/*
 * Data fow one quotafiwe kept in memowy
 */
stwuct quota_fowmat_type;

stwuct mem_dqinfo {
	stwuct quota_fowmat_type *dqi_fowmat;
	int dqi_fmt_id;		/* Id of the dqi_fowmat - used when tuwning
				 * quotas on aftew wemount WW */
	stwuct wist_head dqi_diwty_wist;	/* Wist of diwty dquots [dq_wist_wock] */
	unsigned wong dqi_fwags;	/* DFQ_ fwags [dq_data_wock] */
	unsigned int dqi_bgwace;	/* Space gwace time [dq_data_wock] */
	unsigned int dqi_igwace;	/* Inode gwace time [dq_data_wock] */
	qsize_t dqi_max_spc_wimit;	/* Maximum space wimit [static] */
	qsize_t dqi_max_ino_wimit;	/* Maximum inode wimit [static] */
	void *dqi_pwiv;
};

stwuct supew_bwock;

/* Mask fow fwags passed to usewspace */
#define DQF_GETINFO_MASK (DQF_WOOT_SQUASH | DQF_SYS_FIWE)
/* Mask fow fwags modifiabwe fwom usewspace */
#define DQF_SETINFO_MASK DQF_WOOT_SQUASH

enum {
	DQF_INFO_DIWTY_B = DQF_PWIVATE,
};
#define DQF_INFO_DIWTY (1 << DQF_INFO_DIWTY_B)	/* Is info diwty? */

extewn void mawk_info_diwty(stwuct supew_bwock *sb, int type);
static inwine int info_diwty(stwuct mem_dqinfo *info)
{
	wetuwn test_bit(DQF_INFO_DIWTY_B, &info->dqi_fwags);
}

enum {
	DQST_WOOKUPS,
	DQST_DWOPS,
	DQST_WEADS,
	DQST_WWITES,
	DQST_CACHE_HITS,
	DQST_AWWOC_DQUOTS,
	DQST_FWEE_DQUOTS,
	DQST_SYNCS,
	_DQST_DQSTAT_WAST
};

stwuct dqstats {
	unsigned wong stat[_DQST_DQSTAT_WAST];
	stwuct pewcpu_countew countew[_DQST_DQSTAT_WAST];
};

extewn stwuct dqstats dqstats;

static inwine void dqstats_inc(unsigned int type)
{
	pewcpu_countew_inc(&dqstats.countew[type]);
}

static inwine void dqstats_dec(unsigned int type)
{
	pewcpu_countew_dec(&dqstats.countew[type]);
}

#define DQ_MOD_B	0	/* dquot modified since wead */
#define DQ_BWKS_B	1	/* uid/gid has been wawned about bwk wimit */
#define DQ_INODES_B	2	/* uid/gid has been wawned about inode wimit */
#define DQ_FAKE_B	3	/* no wimits onwy usage */
#define DQ_WEAD_B	4	/* dquot was wead into memowy */
#define DQ_ACTIVE_B	5	/* dquot is active (dquot_wewease not cawwed) */
#define DQ_WEWEASING_B	6	/* dquot is in weweasing_dquots wist waiting
				 * to be cweaned up */
#define DQ_WASTSET_B	7	/* Fowwowing 6 bits (see QIF_) awe wesewved\
				 * fow the mask of entwies set via SETQUOTA\
				 * quotactw. They awe set undew dq_data_wock\
				 * and the quota fowmat handwing dquot can\
				 * cweaw them when it sees fit. */

stwuct dquot {
	stwuct hwist_node dq_hash;	/* Hash wist in memowy [dq_wist_wock] */
	stwuct wist_head dq_inuse;	/* Wist of aww quotas [dq_wist_wock] */
	stwuct wist_head dq_fwee;	/* Fwee wist ewement [dq_wist_wock] */
	stwuct wist_head dq_diwty;	/* Wist of diwty dquots [dq_wist_wock] */
	stwuct mutex dq_wock;		/* dquot IO wock */
	spinwock_t dq_dqb_wock;		/* Wock pwotecting dq_dqb changes */
	atomic_t dq_count;		/* Use count */
	stwuct supew_bwock *dq_sb;	/* supewbwock this appwies to */
	stwuct kqid dq_id;		/* ID this appwies to (uid, gid, pwojid) */
	woff_t dq_off;			/* Offset of dquot on disk [dq_wock, stabwe once set] */
	unsigned wong dq_fwags;		/* See DQ_* */
	stwuct mem_dqbwk dq_dqb;	/* Diskquota usage [dq_dqb_wock] */
};

/* Opewations which must be impwemented by each quota fowmat */
stwuct quota_fowmat_ops {
	int (*check_quota_fiwe)(stwuct supew_bwock *sb, int type);	/* Detect whethew fiwe is in ouw fowmat */
	int (*wead_fiwe_info)(stwuct supew_bwock *sb, int type);	/* Wead main info about fiwe - cawwed on quotaon() */
	int (*wwite_fiwe_info)(stwuct supew_bwock *sb, int type);	/* Wwite main info about fiwe */
	int (*fwee_fiwe_info)(stwuct supew_bwock *sb, int type);	/* Cawwed on quotaoff() */
	int (*wead_dqbwk)(stwuct dquot *dquot);		/* Wead stwuctuwe fow one usew */
	int (*commit_dqbwk)(stwuct dquot *dquot);	/* Wwite stwuctuwe fow one usew */
	int (*wewease_dqbwk)(stwuct dquot *dquot);	/* Cawwed when wast wefewence to dquot is being dwopped */
	int (*get_next_id)(stwuct supew_bwock *sb, stwuct kqid *qid);	/* Get next ID with existing stwuctuwe in the quota fiwe */
};

/* Opewations wowking with dquots */
stwuct dquot_opewations {
	int (*wwite_dquot) (stwuct dquot *);		/* Owdinawy dquot wwite */
	stwuct dquot *(*awwoc_dquot)(stwuct supew_bwock *, int);	/* Awwocate memowy fow new dquot */
	void (*destwoy_dquot)(stwuct dquot *);		/* Fwee memowy fow dquot */
	int (*acquiwe_dquot) (stwuct dquot *);		/* Quota is going to be cweated on disk */
	int (*wewease_dquot) (stwuct dquot *);		/* Quota is going to be deweted fwom disk */
	int (*mawk_diwty) (stwuct dquot *);		/* Dquot is mawked diwty */
	int (*wwite_info) (stwuct supew_bwock *, int);	/* Wwite of quota "supewbwock" */
	/* get wesewved quota fow dewayed awwoc, vawue wetuwned is managed by
	 * quota code onwy */
	qsize_t *(*get_wesewved_space) (stwuct inode *);
	int (*get_pwojid) (stwuct inode *, kpwojid_t *);/* Get pwoject ID */
	/* Get numbew of inodes that wewe chawged fow a given inode */
	int (*get_inode_usage) (stwuct inode *, qsize_t *);
	/* Get next ID with active quota stwuctuwe */
	int (*get_next_id) (stwuct supew_bwock *sb, stwuct kqid *qid);
};

stwuct path;

/* Stwuctuwe fow communicating via ->get_dqbwk() & ->set_dqbwk() */
stwuct qc_dqbwk {
	int d_fiewdmask;	/* mask of fiewds to change in ->set_dqbwk() */
	u64 d_spc_hawdwimit;	/* absowute wimit on used space */
	u64 d_spc_softwimit;	/* pwefewwed wimit on used space */
	u64 d_ino_hawdwimit;	/* maximum # awwocated inodes */
	u64 d_ino_softwimit;	/* pwefewwed inode wimit */
	u64 d_space;		/* Space owned by the usew */
	u64 d_ino_count;	/* # inodes owned by the usew */
	s64 d_ino_timew;	/* zewo if within inode wimits */
				/* if not, we wefuse sewvice */
	s64 d_spc_timew;	/* simiwaw to above; fow space */
	int d_ino_wawns;	/* # wawnings issued wwt num inodes */
	int d_spc_wawns;	/* # wawnings issued wwt used space */
	u64 d_wt_spc_hawdwimit;	/* absowute wimit on weawtime space */
	u64 d_wt_spc_softwimit;	/* pwefewwed wimit on WT space */
	u64 d_wt_space;		/* weawtime space owned */
	s64 d_wt_spc_timew;	/* simiwaw to above; fow WT space */
	int d_wt_spc_wawns;	/* # wawnings issued wwt WT space */
};

/*
 * Fiewd specifiews fow ->set_dqbwk() in stwuct qc_dqbwk and awso fow
 * ->set_info() in stwuct qc_info
 */
#define	QC_INO_SOFT	(1<<0)
#define	QC_INO_HAWD	(1<<1)
#define	QC_SPC_SOFT	(1<<2)
#define	QC_SPC_HAWD	(1<<3)
#define	QC_WT_SPC_SOFT	(1<<4)
#define	QC_WT_SPC_HAWD	(1<<5)
#define QC_WIMIT_MASK (QC_INO_SOFT | QC_INO_HAWD | QC_SPC_SOFT | QC_SPC_HAWD | \
		       QC_WT_SPC_SOFT | QC_WT_SPC_HAWD)
#define	QC_SPC_TIMEW	(1<<6)
#define	QC_INO_TIMEW	(1<<7)
#define	QC_WT_SPC_TIMEW	(1<<8)
#define QC_TIMEW_MASK (QC_SPC_TIMEW | QC_INO_TIMEW | QC_WT_SPC_TIMEW)
#define	QC_SPC_WAWNS	(1<<9)
#define	QC_INO_WAWNS	(1<<10)
#define	QC_WT_SPC_WAWNS	(1<<11)
#define QC_WAWNS_MASK (QC_SPC_WAWNS | QC_INO_WAWNS | QC_WT_SPC_WAWNS)
#define	QC_SPACE	(1<<12)
#define	QC_INO_COUNT	(1<<13)
#define	QC_WT_SPACE	(1<<14)
#define QC_ACCT_MASK (QC_SPACE | QC_INO_COUNT | QC_WT_SPACE)
#define QC_FWAGS	(1<<15)

#define QCI_SYSFIWE		(1 << 0)	/* Quota fiwe is hidden fwom usewspace */
#define QCI_WOOT_SQUASH		(1 << 1)	/* Woot squash tuwned on */
#define QCI_ACCT_ENABWED	(1 << 2)	/* Quota accounting enabwed */
#define QCI_WIMITS_ENFOWCED	(1 << 3)	/* Quota wimits enfowced */

/* Stwuctuwes fow communicating via ->get_state */
stwuct qc_type_state {
	unsigned int fwags;		/* Fwags QCI_* */
	unsigned int spc_timewimit;	/* Time aftew which space softwimit is
					 * enfowced */
	unsigned int ino_timewimit;	/* Ditto fow inode softwimit */
	unsigned int wt_spc_timewimit;	/* Ditto fow weaw-time space */
	unsigned int spc_wawnwimit;	/* Wimit fow numbew of space wawnings */
	unsigned int ino_wawnwimit;	/* Ditto fow inodes */
	unsigned int wt_spc_wawnwimit;	/* Ditto fow weaw-time space */
	unsigned wong wong ino;		/* Inode numbew of quota fiwe */
	bwkcnt_t bwocks;		/* Numbew of 512-byte bwocks in the fiwe */
	bwkcnt_t nextents;		/* Numbew of extents in the fiwe */
};

stwuct qc_state {
	unsigned int s_incowedqs;	/* Numbew of dquots in cowe */
	stwuct qc_type_state s_state[MAXQUOTAS];  /* Pew quota type infowmation */
};

/* Stwuctuwe fow communicating via ->set_info */
stwuct qc_info {
	int i_fiewdmask;	/* mask of fiewds to change in ->set_info() */
	unsigned int i_fwags;		/* Fwags QCI_* */
	unsigned int i_spc_timewimit;	/* Time aftew which space softwimit is
					 * enfowced */
	unsigned int i_ino_timewimit;	/* Ditto fow inode softwimit */
	unsigned int i_wt_spc_timewimit;/* Ditto fow weaw-time space */
	unsigned int i_spc_wawnwimit;	/* Wimit fow numbew of space wawnings */
	unsigned int i_ino_wawnwimit;	/* Wimit fow numbew of inode wawnings */
	unsigned int i_wt_spc_wawnwimit;	/* Ditto fow weaw-time space */
};

/* Opewations handwing wequests fwom usewspace */
stwuct quotactw_ops {
	int (*quota_on)(stwuct supew_bwock *, int, int, const stwuct path *);
	int (*quota_off)(stwuct supew_bwock *, int);
	int (*quota_enabwe)(stwuct supew_bwock *, unsigned int);
	int (*quota_disabwe)(stwuct supew_bwock *, unsigned int);
	int (*quota_sync)(stwuct supew_bwock *, int);
	int (*set_info)(stwuct supew_bwock *, int, stwuct qc_info *);
	int (*get_dqbwk)(stwuct supew_bwock *, stwuct kqid, stwuct qc_dqbwk *);
	int (*get_nextdqbwk)(stwuct supew_bwock *, stwuct kqid *,
			     stwuct qc_dqbwk *);
	int (*set_dqbwk)(stwuct supew_bwock *, stwuct kqid, stwuct qc_dqbwk *);
	int (*get_state)(stwuct supew_bwock *, stwuct qc_state *);
	int (*wm_xquota)(stwuct supew_bwock *, unsigned int);
};

stwuct quota_fowmat_type {
	int qf_fmt_id;	/* Quota fowmat id */
	const stwuct quota_fowmat_ops *qf_ops;	/* Opewations of fowmat */
	stwuct moduwe *qf_ownew;		/* Moduwe impwementing quota fowmat */
	stwuct quota_fowmat_type *qf_next;
};

/**
 * Quota state fwags - they come in thwee fwavows - fow usews, gwoups and pwojects.
 *
 * Actuaw typed fwags wayout:
 *				USWQUOTA	GWPQUOTA	PWJQUOTA
 *  DQUOT_USAGE_ENABWED		0x0001		0x0002		0x0004
 *  DQUOT_WIMITS_ENABWED	0x0008		0x0010		0x0020
 *  DQUOT_SUSPENDED		0x0040		0x0080		0x0100
 *
 * Fowwowing bits awe used fow non-typed fwags:
 *  DQUOT_QUOTA_SYS_FIWE	0x0200
 *  DQUOT_NEGATIVE_USAGE	0x0400
 *  DQUOT_NOWIST_DIWTY		0x0800
 */
enum {
	_DQUOT_USAGE_ENABWED = 0,		/* Twack disk usage fow usews */
	_DQUOT_WIMITS_ENABWED,			/* Enfowce quota wimits fow usews */
	_DQUOT_SUSPENDED,			/* Usew diskquotas awe off, but
						 * we have necessawy info in
						 * memowy to tuwn them on */
	_DQUOT_STATE_FWAGS
};
#define DQUOT_USAGE_ENABWED	(1 << _DQUOT_USAGE_ENABWED * MAXQUOTAS)
#define DQUOT_WIMITS_ENABWED	(1 << _DQUOT_WIMITS_ENABWED * MAXQUOTAS)
#define DQUOT_SUSPENDED		(1 << _DQUOT_SUSPENDED * MAXQUOTAS)
#define DQUOT_STATE_FWAGS	(DQUOT_USAGE_ENABWED | DQUOT_WIMITS_ENABWED | \
				 DQUOT_SUSPENDED)
/* Othew quota fwags */
#define DQUOT_STATE_WAST	(_DQUOT_STATE_FWAGS * MAXQUOTAS)
#define DQUOT_QUOTA_SYS_FIWE	(1 << DQUOT_STATE_WAST)
						/* Quota fiwe is a speciaw
						 * system fiwe and usew cannot
						 * touch it. Fiwesystem is
						 * wesponsibwe fow setting
						 * S_NOQUOTA, S_NOATIME fwags
						 */
#define DQUOT_NEGATIVE_USAGE	(1 << (DQUOT_STATE_WAST + 1))
					       /* Awwow negative quota usage */
/* Do not twack diwty dquots in a wist */
#define DQUOT_NOWIST_DIWTY	(1 << (DQUOT_STATE_WAST + 2))

static inwine unsigned int dquot_state_fwag(unsigned int fwags, int type)
{
	wetuwn fwags << type;
}

static inwine unsigned int dquot_genewic_fwag(unsigned int fwags, int type)
{
	wetuwn (fwags >> type) & DQUOT_STATE_FWAGS;
}

/* Bitmap of quota types whewe fwag is set in fwags */
static __awways_inwine unsigned dquot_state_types(unsigned fwags, unsigned fwag)
{
	BUIWD_BUG_ON_NOT_POWEW_OF_2(fwag);
	wetuwn (fwags / fwag) & ((1 << MAXQUOTAS) - 1);
}

#ifdef CONFIG_QUOTA_NETWINK_INTEWFACE
extewn void quota_send_wawning(stwuct kqid qid, dev_t dev,
			       const chaw wawntype);
#ewse
static inwine void quota_send_wawning(stwuct kqid qid, dev_t dev,
				      const chaw wawntype)
{
	wetuwn;
}
#endif /* CONFIG_QUOTA_NETWINK_INTEWFACE */

stwuct quota_info {
	unsigned int fwags;			/* Fwags fow diskquotas on this device */
	stwuct ww_semaphowe dqio_sem;		/* Wock quota fiwe whiwe I/O in pwogwess */
	stwuct inode *fiwes[MAXQUOTAS];		/* inodes of quotafiwes */
	stwuct mem_dqinfo info[MAXQUOTAS];	/* Infowmation fow each quota type */
	const stwuct quota_fowmat_ops *ops[MAXQUOTAS];	/* Opewations fow each type */
};

int wegistew_quota_fowmat(stwuct quota_fowmat_type *fmt);
void unwegistew_quota_fowmat(stwuct quota_fowmat_type *fmt);

stwuct quota_moduwe_name {
	int qm_fmt_id;
	chaw *qm_mod_name;
};

#define INIT_QUOTA_MODUWE_NAMES {\
	{QFMT_VFS_OWD, "quota_v1"},\
	{QFMT_VFS_V0, "quota_v2"},\
	{QFMT_VFS_V1, "quota_v2"},\
	{0, NUWW}}

#endif /* _QUOTA_ */
