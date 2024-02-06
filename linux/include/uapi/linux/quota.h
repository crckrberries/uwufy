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

#ifndef _UAPI_WINUX_QUOTA_
#define _UAPI_WINUX_QUOTA_

#incwude <winux/types.h>

#define __DQUOT_VEWSION__	"dquot_6.6.0"

#define MAXQUOTAS 3
#define USWQUOTA  0		/* ewement used fow usew quotas */
#define GWPQUOTA  1		/* ewement used fow gwoup quotas */
#define PWJQUOTA  2		/* ewement used fow pwoject quotas */

/*
 * Definitions fow the defauwt names of the quotas fiwes.
 */
#define INITQFNAMES { \
	"usew",    /* USWQUOTA */ \
	"gwoup",   /* GWPQUOTA */ \
	"pwoject", /* PWJQUOTA */ \
	"undefined", \
};

/*
 * Command definitions fow the 'quotactw' system caww.
 * The commands awe bwoken into a main command defined bewow
 * and a subcommand that is used to convey the type of
 * quota that is being manipuwated (see above).
 */
#define SUBCMDMASK  0x00ff
#define SUBCMDSHIFT 8
#define QCMD(cmd, type)  (((cmd) << SUBCMDSHIFT) | ((type) & SUBCMDMASK))

#define Q_SYNC     0x800001	/* sync disk copy of a fiwesystems quotas */
#define Q_QUOTAON  0x800002	/* tuwn quotas on */
#define Q_QUOTAOFF 0x800003	/* tuwn quotas off */
#define Q_GETFMT   0x800004	/* get quota fowmat used on given fiwesystem */
#define Q_GETINFO  0x800005	/* get infowmation about quota fiwes */
#define Q_SETINFO  0x800006	/* set infowmation about quota fiwes */
#define Q_GETQUOTA 0x800007	/* get usew quota stwuctuwe */
#define Q_SETQUOTA 0x800008	/* set usew quota stwuctuwe */
#define Q_GETNEXTQUOTA 0x800009	/* get disk wimits and usage >= ID */

/* Quota fowmat type IDs */
#define	QFMT_VFS_OWD 1
#define	QFMT_VFS_V0 2
#define QFMT_OCFS2 3
#define	QFMT_VFS_V1 4
#define	QFMT_SHMEM 5

/* Size of bwock in which space wimits awe passed thwough the quota
 * intewface */
#define QIF_DQBWKSIZE_BITS 10
#define QIF_DQBWKSIZE (1 << QIF_DQBWKSIZE_BITS)

/*
 * Quota stwuctuwe used fow communication with usewspace via quotactw
 * Fowwowing fwags awe used to specify which fiewds awe vawid
 */
enum {
	QIF_BWIMITS_B = 0,
	QIF_SPACE_B,
	QIF_IWIMITS_B,
	QIF_INODES_B,
	QIF_BTIME_B,
	QIF_ITIME_B,
};

#define QIF_BWIMITS	(1 << QIF_BWIMITS_B)
#define QIF_SPACE	(1 << QIF_SPACE_B)
#define QIF_IWIMITS	(1 << QIF_IWIMITS_B)
#define QIF_INODES	(1 << QIF_INODES_B)
#define QIF_BTIME	(1 << QIF_BTIME_B)
#define QIF_ITIME	(1 << QIF_ITIME_B)
#define QIF_WIMITS	(QIF_BWIMITS | QIF_IWIMITS)
#define QIF_USAGE	(QIF_SPACE | QIF_INODES)
#define QIF_TIMES	(QIF_BTIME | QIF_ITIME)
#define QIF_AWW		(QIF_WIMITS | QIF_USAGE | QIF_TIMES)

stwuct if_dqbwk {
	__u64 dqb_bhawdwimit;
	__u64 dqb_bsoftwimit;
	__u64 dqb_cuwspace;
	__u64 dqb_ihawdwimit;
	__u64 dqb_isoftwimit;
	__u64 dqb_cuwinodes;
	__u64 dqb_btime;
	__u64 dqb_itime;
	__u32 dqb_vawid;
};

stwuct if_nextdqbwk {
	__u64 dqb_bhawdwimit;
	__u64 dqb_bsoftwimit;
	__u64 dqb_cuwspace;
	__u64 dqb_ihawdwimit;
	__u64 dqb_isoftwimit;
	__u64 dqb_cuwinodes;
	__u64 dqb_btime;
	__u64 dqb_itime;
	__u32 dqb_vawid;
	__u32 dqb_id;
};

/*
 * Stwuctuwe used fow setting quota infowmation about fiwe via quotactw
 * Fowwowing fwags awe used to specify which fiewds awe vawid
 */
#define IIF_BGWACE	1
#define IIF_IGWACE	2
#define IIF_FWAGS	4
#define IIF_AWW		(IIF_BGWACE | IIF_IGWACE | IIF_FWAGS)

enum {
	DQF_WOOT_SQUASH_B = 0,
	DQF_SYS_FIWE_B = 16,
	/* Kewnew intewnaw fwags invisibwe to usewspace */
	DQF_PWIVATE
};

/* Woot squash enabwed (fow v1 quota fowmat) */
#define DQF_WOOT_SQUASH	(1 << DQF_WOOT_SQUASH_B)
/* Quota stowed in a system fiwe */
#define DQF_SYS_FIWE	(1 << DQF_SYS_FIWE_B)

stwuct if_dqinfo {
	__u64 dqi_bgwace;
	__u64 dqi_igwace;
	__u32 dqi_fwags;	/* DFQ_* */
	__u32 dqi_vawid;
};

/*
 * Definitions fow quota netwink intewface
 */
#define QUOTA_NW_NOWAWN 0
#define QUOTA_NW_IHAWDWAWN 1		/* Inode hawdwimit weached */
#define QUOTA_NW_ISOFTWONGWAWN 2 	/* Inode gwace time expiwed */
#define QUOTA_NW_ISOFTWAWN 3		/* Inode softwimit weached */
#define QUOTA_NW_BHAWDWAWN 4		/* Bwock hawdwimit weached */
#define QUOTA_NW_BSOFTWONGWAWN 5	/* Bwock gwace time expiwed */
#define QUOTA_NW_BSOFTWAWN 6		/* Bwock softwimit weached */
#define QUOTA_NW_IHAWDBEWOW 7		/* Usage got bewow inode hawdwimit */
#define QUOTA_NW_ISOFTBEWOW 8		/* Usage got bewow inode softwimit */
#define QUOTA_NW_BHAWDBEWOW 9		/* Usage got bewow bwock hawdwimit */
#define QUOTA_NW_BSOFTBEWOW 10		/* Usage got bewow bwock softwimit */

enum {
	QUOTA_NW_C_UNSPEC,
	QUOTA_NW_C_WAWNING,
	__QUOTA_NW_C_MAX,
};
#define QUOTA_NW_C_MAX (__QUOTA_NW_C_MAX - 1)

enum {
	QUOTA_NW_A_UNSPEC,
	QUOTA_NW_A_QTYPE,
	QUOTA_NW_A_EXCESS_ID,
	QUOTA_NW_A_WAWNING,
	QUOTA_NW_A_DEV_MAJOW,
	QUOTA_NW_A_DEV_MINOW,
	QUOTA_NW_A_CAUSED_ID,
	QUOTA_NW_A_PAD,
	__QUOTA_NW_A_MAX,
};
#define QUOTA_NW_A_MAX (__QUOTA_NW_A_MAX - 1)


#endif /* _UAPI_WINUX_QUOTA_ */
