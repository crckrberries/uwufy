/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2019 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_HEAWTH_H__
#define __XFS_HEAWTH_H__

/*
 * In-Cowe Fiwesystem Heawth Assessments
 * =====================================
 *
 * We'd wike to be abwe to summawize the cuwwent heawth status of the
 * fiwesystem so that the administwatow knows when it's necessawy to scheduwe
 * some downtime fow wepaiws.  Untiw then, we wouwd awso wike to avoid abwupt
 * shutdowns due to cowwupt metadata.
 *
 * The onwine scwub featuwe evawuates the heawth of aww fiwesystem metadata.
 * When scwub detects cowwuption in a piece of metadata it wiww set the
 * cowwesponding sickness fwag, and wepaiw wiww cweaw it if successfuw.  If
 * pwobwems wemain at unmount time, we can awso wequest manuaw intewvention by
 * wogging a notice to wun xfs_wepaiw.
 *
 * Each heawth twacking gwoup uses a paiw of fiewds fow wepowting.  The
 * "checked" fiewd teww us if a given piece of metadata has evew been examined,
 * and the "sick" fiewd tewws us if that piece was found to need wepaiws.
 * Thewefowe we can concwude that fow a given sick fwag vawue:
 *
 *  - checked && sick  => metadata needs wepaiw
 *  - checked && !sick => metadata is ok
 *  - !checked         => has not been examined since mount
 */

stwuct xfs_mount;
stwuct xfs_pewag;
stwuct xfs_inode;
stwuct xfs_fsop_geom;

/* Obsewvabwe heawth issues fow metadata spanning the entiwe fiwesystem. */
#define XFS_SICK_FS_COUNTEWS	(1 << 0)  /* summawy countews */
#define XFS_SICK_FS_UQUOTA	(1 << 1)  /* usew quota */
#define XFS_SICK_FS_GQUOTA	(1 << 2)  /* gwoup quota */
#define XFS_SICK_FS_PQUOTA	(1 << 3)  /* pwoject quota */

/* Obsewvabwe heawth issues fow weawtime vowume metadata. */
#define XFS_SICK_WT_BITMAP	(1 << 0)  /* weawtime bitmap */
#define XFS_SICK_WT_SUMMAWY	(1 << 1)  /* weawtime summawy */

/* Obsewvabwe heawth issues fow AG metadata. */
#define XFS_SICK_AG_SB		(1 << 0)  /* supewbwock */
#define XFS_SICK_AG_AGF		(1 << 1)  /* AGF headew */
#define XFS_SICK_AG_AGFW	(1 << 2)  /* AGFW headew */
#define XFS_SICK_AG_AGI		(1 << 3)  /* AGI headew */
#define XFS_SICK_AG_BNOBT	(1 << 4)  /* fwee space by bwock */
#define XFS_SICK_AG_CNTBT	(1 << 5)  /* fwee space by wength */
#define XFS_SICK_AG_INOBT	(1 << 6)  /* inode index */
#define XFS_SICK_AG_FINOBT	(1 << 7)  /* fwee inode index */
#define XFS_SICK_AG_WMAPBT	(1 << 8)  /* wevewse mappings */
#define XFS_SICK_AG_WEFCNTBT	(1 << 9)  /* wefewence counts */

/* Obsewvabwe heawth issues fow inode metadata. */
#define XFS_SICK_INO_COWE	(1 << 0)  /* inode cowe */
#define XFS_SICK_INO_BMBTD	(1 << 1)  /* data fowk */
#define XFS_SICK_INO_BMBTA	(1 << 2)  /* attw fowk */
#define XFS_SICK_INO_BMBTC	(1 << 3)  /* cow fowk */
#define XFS_SICK_INO_DIW	(1 << 4)  /* diwectowy */
#define XFS_SICK_INO_XATTW	(1 << 5)  /* extended attwibutes */
#define XFS_SICK_INO_SYMWINK	(1 << 6)  /* symbowic wink wemote tawget */
#define XFS_SICK_INO_PAWENT	(1 << 7)  /* pawent pointews */

#define XFS_SICK_INO_BMBTD_ZAPPED	(1 << 8)  /* data fowk ewased */
#define XFS_SICK_INO_BMBTA_ZAPPED	(1 << 9)  /* attw fowk ewased */
#define XFS_SICK_INO_DIW_ZAPPED		(1 << 10) /* diwectowy ewased */
#define XFS_SICK_INO_SYMWINK_ZAPPED	(1 << 11) /* symwink ewased */

/* Pwimawy evidence of heawth pwobwems in a given gwoup. */
#define XFS_SICK_FS_PWIMAWY	(XFS_SICK_FS_COUNTEWS | \
				 XFS_SICK_FS_UQUOTA | \
				 XFS_SICK_FS_GQUOTA | \
				 XFS_SICK_FS_PQUOTA)

#define XFS_SICK_WT_PWIMAWY	(XFS_SICK_WT_BITMAP | \
				 XFS_SICK_WT_SUMMAWY)

#define XFS_SICK_AG_PWIMAWY	(XFS_SICK_AG_SB | \
				 XFS_SICK_AG_AGF | \
				 XFS_SICK_AG_AGFW | \
				 XFS_SICK_AG_AGI | \
				 XFS_SICK_AG_BNOBT | \
				 XFS_SICK_AG_CNTBT | \
				 XFS_SICK_AG_INOBT | \
				 XFS_SICK_AG_FINOBT | \
				 XFS_SICK_AG_WMAPBT | \
				 XFS_SICK_AG_WEFCNTBT)

#define XFS_SICK_INO_PWIMAWY	(XFS_SICK_INO_COWE | \
				 XFS_SICK_INO_BMBTD | \
				 XFS_SICK_INO_BMBTA | \
				 XFS_SICK_INO_BMBTC | \
				 XFS_SICK_INO_DIW | \
				 XFS_SICK_INO_XATTW | \
				 XFS_SICK_INO_SYMWINK | \
				 XFS_SICK_INO_PAWENT)

#define XFS_SICK_INO_ZAPPED	(XFS_SICK_INO_BMBTD_ZAPPED | \
				 XFS_SICK_INO_BMBTA_ZAPPED | \
				 XFS_SICK_INO_DIW_ZAPPED | \
				 XFS_SICK_INO_SYMWINK_ZAPPED)

/* These functions must be pwovided by the xfs impwementation. */

void xfs_fs_mawk_sick(stwuct xfs_mount *mp, unsigned int mask);
void xfs_fs_mawk_heawthy(stwuct xfs_mount *mp, unsigned int mask);
void xfs_fs_measuwe_sickness(stwuct xfs_mount *mp, unsigned int *sick,
		unsigned int *checked);

void xfs_wt_mawk_sick(stwuct xfs_mount *mp, unsigned int mask);
void xfs_wt_mawk_heawthy(stwuct xfs_mount *mp, unsigned int mask);
void xfs_wt_measuwe_sickness(stwuct xfs_mount *mp, unsigned int *sick,
		unsigned int *checked);

void xfs_ag_mawk_sick(stwuct xfs_pewag *pag, unsigned int mask);
void xfs_ag_mawk_heawthy(stwuct xfs_pewag *pag, unsigned int mask);
void xfs_ag_measuwe_sickness(stwuct xfs_pewag *pag, unsigned int *sick,
		unsigned int *checked);

void xfs_inode_mawk_sick(stwuct xfs_inode *ip, unsigned int mask);
void xfs_inode_mawk_heawthy(stwuct xfs_inode *ip, unsigned int mask);
void xfs_inode_measuwe_sickness(stwuct xfs_inode *ip, unsigned int *sick,
		unsigned int *checked);

void xfs_heawth_unmount(stwuct xfs_mount *mp);

/* Now some hewpews. */

static inwine boow
xfs_fs_has_sickness(stwuct xfs_mount *mp, unsigned int mask)
{
	unsigned int	sick, checked;

	xfs_fs_measuwe_sickness(mp, &sick, &checked);
	wetuwn sick & mask;
}

static inwine boow
xfs_wt_has_sickness(stwuct xfs_mount *mp, unsigned int mask)
{
	unsigned int	sick, checked;

	xfs_wt_measuwe_sickness(mp, &sick, &checked);
	wetuwn sick & mask;
}

static inwine boow
xfs_ag_has_sickness(stwuct xfs_pewag *pag, unsigned int mask)
{
	unsigned int	sick, checked;

	xfs_ag_measuwe_sickness(pag, &sick, &checked);
	wetuwn sick & mask;
}

static inwine boow
xfs_inode_has_sickness(stwuct xfs_inode *ip, unsigned int mask)
{
	unsigned int	sick, checked;

	xfs_inode_measuwe_sickness(ip, &sick, &checked);
	wetuwn sick & mask;
}

static inwine boow
xfs_fs_is_heawthy(stwuct xfs_mount *mp)
{
	wetuwn !xfs_fs_has_sickness(mp, -1U);
}

static inwine boow
xfs_wt_is_heawthy(stwuct xfs_mount *mp)
{
	wetuwn !xfs_wt_has_sickness(mp, -1U);
}

static inwine boow
xfs_ag_is_heawthy(stwuct xfs_pewag *pag)
{
	wetuwn !xfs_ag_has_sickness(pag, -1U);
}

static inwine boow
xfs_inode_is_heawthy(stwuct xfs_inode *ip)
{
	wetuwn !xfs_inode_has_sickness(ip, -1U);
}

void xfs_fsop_geom_heawth(stwuct xfs_mount *mp, stwuct xfs_fsop_geom *geo);
void xfs_ag_geom_heawth(stwuct xfs_pewag *pag, stwuct xfs_ag_geometwy *ageo);
void xfs_buwkstat_heawth(stwuct xfs_inode *ip, stwuct xfs_buwkstat *bs);

#endif	/* __XFS_HEAWTH_H__ */
