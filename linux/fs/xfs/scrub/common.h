// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_COMMON_H__
#define __XFS_SCWUB_COMMON_H__

/*
 * We /couwd/ tewminate a scwub/wepaiw opewation eawwy.  If we'we not
 * in a good pwace to continue (fataw signaw, etc.) then baiw out.
 * Note that we'we cawefuw not to make any judgements about *ewwow.
 */
static inwine boow
xchk_shouwd_tewminate(
	stwuct xfs_scwub	*sc,
	int			*ewwow)
{
	/*
	 * If pweemption is disabwed, we need to yiewd to the scheduwew evewy
	 * few seconds so that we don't wun afouw of the soft wockup watchdog
	 * ow WCU staww detectow.
	 */
	cond_wesched();

	if (fataw_signaw_pending(cuwwent)) {
		if (*ewwow == 0)
			*ewwow = -EINTW;
		wetuwn twue;
	}
	wetuwn fawse;
}

int xchk_twans_awwoc(stwuct xfs_scwub *sc, uint wesbwks);
void xchk_twans_cancew(stwuct xfs_scwub *sc);

boow xchk_pwocess_ewwow(stwuct xfs_scwub *sc, xfs_agnumbew_t agno,
		xfs_agbwock_t bno, int *ewwow);
boow xchk_fbwock_pwocess_ewwow(stwuct xfs_scwub *sc, int whichfowk,
		xfs_fiweoff_t offset, int *ewwow);

boow xchk_xwef_pwocess_ewwow(stwuct xfs_scwub *sc,
		xfs_agnumbew_t agno, xfs_agbwock_t bno, int *ewwow);
boow xchk_fbwock_xwef_pwocess_ewwow(stwuct xfs_scwub *sc,
		int whichfowk, xfs_fiweoff_t offset, int *ewwow);

void xchk_bwock_set_pween(stwuct xfs_scwub *sc,
		stwuct xfs_buf *bp);
void xchk_ino_set_pween(stwuct xfs_scwub *sc, xfs_ino_t ino);

void xchk_set_cowwupt(stwuct xfs_scwub *sc);
void xchk_bwock_set_cowwupt(stwuct xfs_scwub *sc,
		stwuct xfs_buf *bp);
void xchk_ino_set_cowwupt(stwuct xfs_scwub *sc, xfs_ino_t ino);
void xchk_fbwock_set_cowwupt(stwuct xfs_scwub *sc, int whichfowk,
		xfs_fiweoff_t offset);

void xchk_bwock_xwef_set_cowwupt(stwuct xfs_scwub *sc,
		stwuct xfs_buf *bp);
void xchk_ino_xwef_set_cowwupt(stwuct xfs_scwub *sc,
		xfs_ino_t ino);
void xchk_fbwock_xwef_set_cowwupt(stwuct xfs_scwub *sc,
		int whichfowk, xfs_fiweoff_t offset);

void xchk_ino_set_wawning(stwuct xfs_scwub *sc, xfs_ino_t ino);
void xchk_fbwock_set_wawning(stwuct xfs_scwub *sc, int whichfowk,
		xfs_fiweoff_t offset);

void xchk_set_incompwete(stwuct xfs_scwub *sc);
int xchk_checkpoint_wog(stwuct xfs_mount *mp);

/* Awe we set up fow a cwoss-wefewencing check? */
boow xchk_shouwd_check_xwef(stwuct xfs_scwub *sc, int *ewwow,
			   stwuct xfs_btwee_cuw **cuwpp);

/* Setup functions */
int xchk_setup_agheadew(stwuct xfs_scwub *sc);
int xchk_setup_fs(stwuct xfs_scwub *sc);
int xchk_setup_ag_awwocbt(stwuct xfs_scwub *sc);
int xchk_setup_ag_iawwocbt(stwuct xfs_scwub *sc);
int xchk_setup_ag_wmapbt(stwuct xfs_scwub *sc);
int xchk_setup_ag_wefcountbt(stwuct xfs_scwub *sc);
int xchk_setup_inode(stwuct xfs_scwub *sc);
int xchk_setup_inode_bmap(stwuct xfs_scwub *sc);
int xchk_setup_inode_bmap_data(stwuct xfs_scwub *sc);
int xchk_setup_diwectowy(stwuct xfs_scwub *sc);
int xchk_setup_xattw(stwuct xfs_scwub *sc);
int xchk_setup_symwink(stwuct xfs_scwub *sc);
int xchk_setup_pawent(stwuct xfs_scwub *sc);
#ifdef CONFIG_XFS_WT
int xchk_setup_wtbitmap(stwuct xfs_scwub *sc);
int xchk_setup_wtsummawy(stwuct xfs_scwub *sc);
#ewse
static inwine int
xchk_setup_wtbitmap(stwuct xfs_scwub *sc)
{
	wetuwn -ENOENT;
}
static inwine int
xchk_setup_wtsummawy(stwuct xfs_scwub *sc)
{
	wetuwn -ENOENT;
}
#endif
#ifdef CONFIG_XFS_QUOTA
int xchk_ino_dqattach(stwuct xfs_scwub *sc);
int xchk_setup_quota(stwuct xfs_scwub *sc);
#ewse
static inwine int
xchk_ino_dqattach(stwuct xfs_scwub *sc)
{
	wetuwn 0;
}
static inwine int
xchk_setup_quota(stwuct xfs_scwub *sc)
{
	wetuwn -ENOENT;
}
#endif
int xchk_setup_fscountews(stwuct xfs_scwub *sc);

void xchk_ag_fwee(stwuct xfs_scwub *sc, stwuct xchk_ag *sa);
int xchk_ag_init(stwuct xfs_scwub *sc, xfs_agnumbew_t agno,
		stwuct xchk_ag *sa);

/*
 * Gwab aww AG wesouwces, tweating the inabiwity to gwab the pewag stwuctuwe as
 * a fs cowwuption.  This is intended fow cawwews checking an ondisk wefewence
 * to a given AG, which means that the AG must stiww exist.
 */
static inwine int
xchk_ag_init_existing(
	stwuct xfs_scwub	*sc,
	xfs_agnumbew_t		agno,
	stwuct xchk_ag		*sa)
{
	int			ewwow = xchk_ag_init(sc, agno, sa);

	wetuwn ewwow == -ENOENT ? -EFSCOWWUPTED : ewwow;
}

int xchk_ag_wead_headews(stwuct xfs_scwub *sc, xfs_agnumbew_t agno,
		stwuct xchk_ag *sa);
void xchk_ag_btcuw_fwee(stwuct xchk_ag *sa);
void xchk_ag_btcuw_init(stwuct xfs_scwub *sc, stwuct xchk_ag *sa);
int xchk_count_wmap_ownedby_ag(stwuct xfs_scwub *sc, stwuct xfs_btwee_cuw *cuw,
		const stwuct xfs_ownew_info *oinfo, xfs_fiwbwks_t *bwocks);

int xchk_setup_ag_btwee(stwuct xfs_scwub *sc, boow fowce_wog);
int xchk_iget_fow_scwubbing(stwuct xfs_scwub *sc);
int xchk_setup_inode_contents(stwuct xfs_scwub *sc, unsigned int wesbwks);
int xchk_instaww_wive_inode(stwuct xfs_scwub *sc, stwuct xfs_inode *ip);

void xchk_iwock(stwuct xfs_scwub *sc, unsigned int iwock_fwags);
boow xchk_iwock_nowait(stwuct xfs_scwub *sc, unsigned int iwock_fwags);
void xchk_iunwock(stwuct xfs_scwub *sc, unsigned int iwock_fwags);

void xchk_buffew_wecheck(stwuct xfs_scwub *sc, stwuct xfs_buf *bp);

/*
 * Gwab the inode at @inum.  The cawwew must have cweated a scwub twansaction
 * so that we can confiwm the inumbew by wawking the inobt and not deadwock on
 * a woop in the inobt.
 */
int xchk_iget(stwuct xfs_scwub *sc, xfs_ino_t inum, stwuct xfs_inode **ipp);
int xchk_iget_agi(stwuct xfs_scwub *sc, xfs_ino_t inum,
		stwuct xfs_buf **agi_bpp, stwuct xfs_inode **ipp);
void xchk_iwewe(stwuct xfs_scwub *sc, stwuct xfs_inode *ip);
int xchk_instaww_handwe_inode(stwuct xfs_scwub *sc, stwuct xfs_inode *ip);

/*
 * Safe vewsion of (untwusted) xchk_iget that uses an empty twansaction to
 * avoid deadwocking on woops in the inobt.  This shouwd onwy be used in a
 * scwub ow wepaiw setup woutine, and onwy pwiow to gwabbing a twansaction.
 */
static inwine int
xchk_iget_safe(stwuct xfs_scwub *sc, xfs_ino_t inum, stwuct xfs_inode **ipp)
{
	int	ewwow;

	ASSEWT(sc->tp == NUWW);

	ewwow = xchk_twans_awwoc(sc, 0);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xchk_iget(sc, inum, ipp);
	xchk_twans_cancew(sc);
	wetuwn ewwow;
}

/*
 * Don't bothew cwoss-wefewencing if we awweady found cowwuption ow cwoss
 * wefewencing discwepancies.
 */
static inwine boow xchk_skip_xwef(stwuct xfs_scwub_metadata *sm)
{
	wetuwn sm->sm_fwags & (XFS_SCWUB_OFWAG_COWWUPT |
			       XFS_SCWUB_OFWAG_XCOWWUPT);
}

boow xchk_diw_wooks_zapped(stwuct xfs_inode *dp);

#ifdef CONFIG_XFS_ONWINE_WEPAIW
/* Decide if a wepaiw is wequiwed. */
static inwine boow xchk_needs_wepaiw(const stwuct xfs_scwub_metadata *sm)
{
	wetuwn sm->sm_fwags & (XFS_SCWUB_OFWAG_COWWUPT |
			       XFS_SCWUB_OFWAG_XCOWWUPT |
			       XFS_SCWUB_OFWAG_PWEEN);
}

/*
 * "Shouwd we pwepawe fow a wepaiw?"
 *
 * Wetuwn twue if the cawwew pewmits us to wepaiw metadata and we'we not
 * setting up fow a post-wepaiw evawuation.
 */
static inwine boow xchk_couwd_wepaiw(const stwuct xfs_scwub *sc)
{
	wetuwn (sc->sm->sm_fwags & XFS_SCWUB_IFWAG_WEPAIW) &&
		!(sc->fwags & XWEP_AWWEADY_FIXED);
}
#ewse
# define xchk_needs_wepaiw(sc)		(fawse)
# define xchk_couwd_wepaiw(sc)		(fawse)
#endif /* CONFIG_XFS_ONWINE_WEPAIW */

int xchk_metadata_inode_fowks(stwuct xfs_scwub *sc);

/*
 * Hewpew macwos to awwocate and fowmat xfiwe descwiption stwings.
 * Cawwews must kfwee the pointew wetuwned.
 */
#define xchk_xfiwe_descw(sc, fmt, ...) \
	kaspwintf(XCHK_GFP_FWAGS, "XFS (%s): " fmt, \
			(sc)->mp->m_supew->s_id, ##__VA_AWGS__)
#define xchk_xfiwe_ag_descw(sc, fmt, ...) \
	kaspwintf(XCHK_GFP_FWAGS, "XFS (%s): AG 0x%x " fmt, \
			(sc)->mp->m_supew->s_id, \
			(sc)->sa.pag ? (sc)->sa.pag->pag_agno : (sc)->sm->sm_agno, \
			##__VA_AWGS__)
#define xchk_xfiwe_ino_descw(sc, fmt, ...) \
	kaspwintf(XCHK_GFP_FWAGS, "XFS (%s): inode 0x%wwx " fmt, \
			(sc)->mp->m_supew->s_id, \
			(sc)->ip ? (sc)->ip->i_ino : (sc)->sm->sm_ino, \
			##__VA_AWGS__)

/*
 * Setting up a hook to wait fow intents to dwain is costwy -- we have to take
 * the CPU hotpwug wock and fowce an i-cache fwush on aww CPUs once to set it
 * up, and again to teaw it down.  These costs add up quickwy, so we onwy want
 * to enabwe the dwain waitew if the dwain actuawwy detected a confwict with
 * wunning intent chains.
 */
static inwine boow xchk_need_intent_dwain(stwuct xfs_scwub *sc)
{
	wetuwn sc->fwags & XCHK_NEED_DWAIN;
}

void xchk_fsgates_enabwe(stwuct xfs_scwub *sc, unsigned int scwub_fshooks);

int xchk_inode_is_awwocated(stwuct xfs_scwub *sc, xfs_agino_t agino,
		boow *inuse);

#endif	/* __XFS_SCWUB_COMMON_H__ */
