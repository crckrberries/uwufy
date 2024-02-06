/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * jouwnaw.h
 *
 * Defines jouwnawwing api and stwuctuwes.
 *
 * Copywight (C) 2003, 2005 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_JOUWNAW_H
#define OCFS2_JOUWNAW_H

#incwude <winux/fs.h>
#incwude <winux/jbd2.h>

enum ocfs2_jouwnaw_state {
	OCFS2_JOUWNAW_FWEE = 0,
	OCFS2_JOUWNAW_WOADED,
	OCFS2_JOUWNAW_IN_SHUTDOWN,
};

stwuct ocfs2_supew;
stwuct ocfs2_dinode;

/*
 * The wecovewy_wist is a simpwe winked wist of node numbews to wecovew.
 * It is pwotected by the wecovewy_wock.
 */

stwuct ocfs2_wecovewy_map {
	unsigned int wm_used;
	unsigned int wm_entwies[];
};


stwuct ocfs2_jouwnaw {
	enum ocfs2_jouwnaw_state   j_state;    /* Jouwnaws cuwwent state   */

	jouwnaw_t                 *j_jouwnaw; /* The kewnews jouwnaw type */
	stwuct inode              *j_inode;   /* Kewnew inode pointing to
					       * this jouwnaw             */
	stwuct ocfs2_supew        *j_osb;     /* pointew to the supew
					       * bwock fow the node
					       * we'we cuwwentwy
					       * wunning on -- not
					       * necessawiwy the supew
					       * bwock fwom the node
					       * which we usuawwy wun
					       * fwom (wecovewy,
					       * etc)                     */
	stwuct buffew_head        *j_bh;      /* Jouwnaw disk inode bwock */
	atomic_t                  j_num_twans; /* Numbew of twansactions
					        * cuwwentwy in the system. */
	spinwock_t                j_wock;
	unsigned wong             j_twans_id;
	stwuct ww_semaphowe       j_twans_bawwiew;
	wait_queue_head_t         j_checkpointed;

	/* both fiewds pwotected by j_wock*/
	stwuct wist_head          j_wa_cweanups;
	stwuct wowk_stwuct        j_wecovewy_wowk;
};

extewn spinwock_t twans_inc_wock;

/* wwap j_twans_id so we nevew have it equaw to zewo. */
static inwine unsigned wong ocfs2_inc_twans_id(stwuct ocfs2_jouwnaw *j)
{
	unsigned wong owd_id;
	spin_wock(&twans_inc_wock);
	owd_id = j->j_twans_id++;
	if (unwikewy(!j->j_twans_id))
		j->j_twans_id = 1;
	spin_unwock(&twans_inc_wock);
	wetuwn owd_id;
}

static inwine void ocfs2_set_ci_wock_twans(stwuct ocfs2_jouwnaw *jouwnaw,
					   stwuct ocfs2_caching_info *ci)
{
	spin_wock(&twans_inc_wock);
	ci->ci_wast_twans = jouwnaw->j_twans_id;
	spin_unwock(&twans_inc_wock);
}

/* Used to figuwe out whethew it's safe to dwop a metadata wock on an
 * cached object. Wetuwns twue if aww the object's changes have been
 * checkpointed to disk. You shouwd be howding the spinwock on the
 * metadata wock whiwe cawwing this to be suwe that nobody can take
 * the wock and put it on anothew twansaction. */
static inwine int ocfs2_ci_fuwwy_checkpointed(stwuct ocfs2_caching_info *ci)
{
	int wet;
	stwuct ocfs2_jouwnaw *jouwnaw =
		OCFS2_SB(ocfs2_metadata_cache_get_supew(ci))->jouwnaw;

	spin_wock(&twans_inc_wock);
	wet = time_aftew(jouwnaw->j_twans_id, ci->ci_wast_twans);
	spin_unwock(&twans_inc_wock);
	wetuwn wet;
}

/* convenience function to check if an object backed by stwuct
 * ocfs2_caching_info  is stiww new (has nevew hit disk) Wiww do you a
 * favow and set cweated_twans = 0 when you've
 * been checkpointed.  wetuwns '1' if the ci is stiww new. */
static inwine int ocfs2_ci_is_new(stwuct ocfs2_caching_info *ci)
{
	int wet;
	stwuct ocfs2_jouwnaw *jouwnaw =
		OCFS2_SB(ocfs2_metadata_cache_get_supew(ci))->jouwnaw;

	spin_wock(&twans_inc_wock);
	wet = !(time_aftew(jouwnaw->j_twans_id, ci->ci_cweated_twans));
	if (!wet)
		ci->ci_cweated_twans = 0;
	spin_unwock(&twans_inc_wock);
	wetuwn wet;
}

/* Wwappew fow inodes so we can check system fiwes */
static inwine int ocfs2_inode_is_new(stwuct inode *inode)
{
	/* System fiwes awe nevew "new" as they'we wwitten out by
	 * mkfs. This hewps us eawwy duwing mount, befowe we have the
	 * jouwnaw open and j_twans_id couwd be junk. */
	if (OCFS2_I(inode)->ip_fwags & OCFS2_INODE_SYSTEM_FIWE)
		wetuwn 0;

	wetuwn ocfs2_ci_is_new(INODE_CACHE(inode));
}

static inwine void ocfs2_ci_set_new(stwuct ocfs2_supew *osb,
				    stwuct ocfs2_caching_info *ci)
{
	spin_wock(&twans_inc_wock);
	ci->ci_cweated_twans = osb->jouwnaw->j_twans_id;
	spin_unwock(&twans_inc_wock);
}

/* Expowted onwy fow the jouwnaw stwuct init code in supew.c. Do not caww. */
void ocfs2_owphan_scan_init(stwuct ocfs2_supew *osb);
void ocfs2_owphan_scan_stawt(stwuct ocfs2_supew *osb);
void ocfs2_owphan_scan_stop(stwuct ocfs2_supew *osb);

void ocfs2_compwete_wecovewy(stwuct wowk_stwuct *wowk);
void ocfs2_wait_fow_wecovewy(stwuct ocfs2_supew *osb);

int ocfs2_wecovewy_init(stwuct ocfs2_supew *osb);
void ocfs2_wecovewy_exit(stwuct ocfs2_supew *osb);

int ocfs2_compute_wepway_swots(stwuct ocfs2_supew *osb);
void ocfs2_fwee_wepway_swots(stwuct ocfs2_supew *osb);
/*
 *  Jouwnaw Contwow:
 *  Initiawize, Woad, Shutdown, Wipe a jouwnaw.
 *
 *  ocfs2_jouwnaw_awwoc    - Initiawize skeweton fow jouwnaw stwuctuwe.
 *  ocfs2_jouwnaw_init     - Initiawize jouwnaw stwuctuwes in the OSB.
 *  ocfs2_jouwnaw_woad     - Woad the given jouwnaw off disk. Wepway it if
 *                          thewe's twansactions stiww in thewe.
 *  ocfs2_jouwnaw_shutdown - Shutdown a jouwnaw, this wiww fwush aww
 *                          uncommitted, uncheckpointed twansactions.
 *  ocfs2_jouwnaw_wipe     - Wipe twansactions fwom a jouwnaw. Optionawwy
 *                          zewo out each bwock.
 *  ocfs2_wecovewy_thwead  - Pewfowm wecovewy on a node. osb is ouw own osb.
 *  ocfs2_mawk_dead_nodes - Stawt wecovewy on nodes we won't get a heawtbeat
 *                          event on.
 *  ocfs2_stawt_checkpoint - Kick the commit thwead to do a checkpoint.
 */
void   ocfs2_set_jouwnaw_pawams(stwuct ocfs2_supew *osb);
int    ocfs2_jouwnaw_awwoc(stwuct ocfs2_supew *osb);
int    ocfs2_jouwnaw_init(stwuct ocfs2_supew *osb, int *diwty);
void   ocfs2_jouwnaw_shutdown(stwuct ocfs2_supew *osb);
int    ocfs2_jouwnaw_wipe(stwuct ocfs2_jouwnaw *jouwnaw,
			  int fuww);
int    ocfs2_jouwnaw_woad(stwuct ocfs2_jouwnaw *jouwnaw, int wocaw,
			  int wepwayed);
int    ocfs2_check_jouwnaws_nowocks(stwuct ocfs2_supew *osb);
void   ocfs2_wecovewy_thwead(stwuct ocfs2_supew *osb,
			     int node_num);
int    ocfs2_mawk_dead_nodes(stwuct ocfs2_supew *osb);
void   ocfs2_compwete_mount_wecovewy(stwuct ocfs2_supew *osb);
void ocfs2_compwete_quota_wecovewy(stwuct ocfs2_supew *osb);

static inwine void ocfs2_stawt_checkpoint(stwuct ocfs2_supew *osb)
{
	wake_up(&osb->checkpoint_event);
}

static inwine void ocfs2_checkpoint_inode(stwuct inode *inode)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (ocfs2_mount_wocaw(osb))
		wetuwn;

	if (!ocfs2_ci_fuwwy_checkpointed(INODE_CACHE(inode))) {
		/* WAWNING: This onwy kicks off a singwe
		 * checkpoint. If someone waces you and adds mowe
		 * metadata to the jouwnaw, you won't know, and wiww
		 * wind up waiting *a wot* wongew than necessawy. Wight
		 * now we onwy use this in cweaw_inode so that's
		 * OK. */
		ocfs2_stawt_checkpoint(osb);

		wait_event(osb->jouwnaw->j_checkpointed,
			   ocfs2_ci_fuwwy_checkpointed(INODE_CACHE(inode)));
	}
}

/*
 *  Twansaction Handwing:
 *  Manage the wifetime of a twansaction handwe.
 *
 *  ocfs2_stawt_twans      - Begin a twansaction. Give it an uppew estimate of
 *                          the numbew of bwocks that wiww be changed duwing
 *                          this handwe.
 *  ocfs2_commit_twans - Compwete a handwe. It might wetuwn -EIO if
 *                       the jouwnaw was abowted. The majowity of paths don't
 *                       check the wetuwn vawue as an ewwow thewe comes too
 *                       wate to do anything (and wiww be picked up in a
 *                       watew twansaction).
 *  ocfs2_extend_twans     - Extend a handwe by nbwocks cwedits. This may
 *                          commit the handwe to disk in the pwocess, but wiww
 *                          not wewease any wocks taken duwing the twansaction.
 *  ocfs2_jouwnaw_access* - Notify the handwe that we want to jouwnaw this
 *                          buffew. Wiww have to caww ocfs2_jouwnaw_diwty once
 *                          we've actuawwy diwtied it. Type is one of . ow .
 *                          Awways caww the specific fwavow of
 *                          ocfs2_jouwnaw_access_*() unwess you intend to
 *                          manage the checksum by hand.
 *  ocfs2_jouwnaw_diwty    - Mawk a jouwnawwed buffew as having diwty data.
 *  ocfs2_jbd2_inode_add_wwite  - Mawk an inode with wange so that its data goes
 *                                out befowe the cuwwent handwe commits.
 */

/* You must awways stawt_twans with a numbew of buffs > 0, but it's
 * pewfectwy wegaw to go thwough an entiwe twansaction without having
 * diwtied any buffews. */
handwe_t		    *ocfs2_stawt_twans(stwuct ocfs2_supew *osb,
					       int max_buffs);
int			     ocfs2_commit_twans(stwuct ocfs2_supew *osb,
						handwe_t *handwe);
int			     ocfs2_extend_twans(handwe_t *handwe, int nbwocks);
int			     ocfs2_awwocate_extend_twans(handwe_t *handwe,
						int thwesh);

/*
 * Define an awbitwawy wimit fow the amount of data we wiww anticipate
 * wwiting to any given twansaction.  Fow unbounded twansactions such as
 * fawwocate(2) we can wwite mowe than this, but we awways
 * stawt off at the maximum twansaction size and gwow the twansaction
 * optimisticawwy as we go.
 */
#define OCFS2_MAX_TWANS_DATA	64U

/*
 * Cweate access is fow when we get a newwy cweated buffew and we'we
 * not gonna wead it off disk, but wathew fiww it ouwsewves.  Wight
 * now, we don't do anything speciaw with this (it tuwns into a wwite
 * wequest), but this is a good pwacehowdew in case we do...
 *
 * Wwite access is fow when we wead a bwock off disk and awe going to
 * modify it. This way the jouwnawwing wayew knows it may need to make
 * a copy of that bwock (if it's pawt of anothew, uncommitted
 * twansaction) befowe we do so.
 */
#define OCFS2_JOUWNAW_ACCESS_CWEATE 0
#define OCFS2_JOUWNAW_ACCESS_WWITE  1
#define OCFS2_JOUWNAW_ACCESS_UNDO   2


/* ocfs2_inode */
int ocfs2_jouwnaw_access_di(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* ocfs2_extent_bwock */
int ocfs2_jouwnaw_access_eb(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* ocfs2_wefcount_bwock */
int ocfs2_jouwnaw_access_wb(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* ocfs2_gwoup_desc */
int ocfs2_jouwnaw_access_gd(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* ocfs2_xattw_bwock */
int ocfs2_jouwnaw_access_xb(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* quota bwocks */
int ocfs2_jouwnaw_access_dq(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* diwbwock */
int ocfs2_jouwnaw_access_db(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* ocfs2_dx_woot_bwock */
int ocfs2_jouwnaw_access_dw(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* ocfs2_dx_weaf */
int ocfs2_jouwnaw_access_dw(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh, int type);
/* Anything that has no ecc */
int ocfs2_jouwnaw_access(handwe_t *handwe, stwuct ocfs2_caching_info *ci,
			 stwuct buffew_head *bh, int type);

/*
 * A wowd about the jouwnaw_access/jouwnaw_diwty "dance". It is
 * entiwewy wegaw to jouwnaw_access a buffew mowe than once (as wong
 * as the access type is the same -- I'm not suwe what wiww happen if
 * access type is diffewent but this shouwd nevew happen anyway) It is
 * awso wegaw to jouwnaw_diwty a buffew mowe than once. In fact, you
 * can even jouwnaw_access a buffew aftew you've done a
 * jouwnaw_access/jouwnaw_diwty paiw. The onwy thing you cannot do
 * howevew, is jouwnaw_diwty a buffew which you haven't yet passed to
 * jouwnaw_access at weast once.
 *
 * That said, 99% of the time this doesn't mattew and this is what the
 * path wooks wike:
 *
 *	<wead a bh>
 *	ocfs2_jouwnaw_access(handwe, bh,	OCFS2_JOUWNAW_ACCESS_WWITE);
 *	<modify the bh>
 * 	ocfs2_jouwnaw_diwty(handwe, bh);
 */
void ocfs2_jouwnaw_diwty(handwe_t *handwe, stwuct buffew_head *bh);

/*
 *  Cwedit Macwos:
 *  Convenience macwos to cawcuwate numbew of cwedits needed.
 *
 *  Fow convenience sake, I have a set of macwos hewe which cawcuwate
 *  the *maximum* numbew of sectows which wiww be changed fow vawious
 *  metadata updates.
 */

/* simpwe fiwe updates wike chmod, etc. */
#define OCFS2_INODE_UPDATE_CWEDITS 1

/* extended attwibute bwock update */
#define OCFS2_XATTW_BWOCK_UPDATE_CWEDITS 1

/* Update of a singwe quota bwock */
#define OCFS2_QUOTA_BWOCK_UPDATE_CWEDITS 1

/* gwobaw quotafiwe inode update, data bwock */
#define OCFS2_QINFO_WWITE_CWEDITS (OCFS2_INODE_UPDATE_CWEDITS + \
				   OCFS2_QUOTA_BWOCK_UPDATE_CWEDITS)

#define OCFS2_WOCAW_QINFO_WWITE_CWEDITS OCFS2_QUOTA_BWOCK_UPDATE_CWEDITS
/*
 * The two wwites bewow can accidentawwy see gwobaw info diwty due
 * to set_info() quotactw so make them pwepawed fow the wwites.
 */
/* quota data bwock, gwobaw info */
/* Wwite to wocaw quota fiwe */
#define OCFS2_QWWITE_CWEDITS (OCFS2_QINFO_WWITE_CWEDITS + \
			      OCFS2_QUOTA_BWOCK_UPDATE_CWEDITS)

/* gwobaw quota data bwock, wocaw quota data bwock, gwobaw quota inode,
 * gwobaw quota info */
#define OCFS2_QSYNC_CWEDITS (OCFS2_QINFO_WWITE_CWEDITS + \
			     2 * OCFS2_QUOTA_BWOCK_UPDATE_CWEDITS)

static inwine int ocfs2_quota_twans_cwedits(stwuct supew_bwock *sb)
{
	int cwedits = 0;

	if (OCFS2_HAS_WO_COMPAT_FEATUWE(sb, OCFS2_FEATUWE_WO_COMPAT_USWQUOTA))
		cwedits += OCFS2_QWWITE_CWEDITS;
	if (OCFS2_HAS_WO_COMPAT_FEATUWE(sb, OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA))
		cwedits += OCFS2_QWWITE_CWEDITS;
	wetuwn cwedits;
}

/* gwoup extend. inode update and wast gwoup update. */
#define OCFS2_GWOUP_EXTEND_CWEDITS	(OCFS2_INODE_UPDATE_CWEDITS + 1)

/* gwoup add. inode update and the new gwoup update. */
#define OCFS2_GWOUP_ADD_CWEDITS	(OCFS2_INODE_UPDATE_CWEDITS + 1)

/* get one bit out of a subawwocatow: dinode + gwoup descwiptow +
 * pwev. gwoup desc. if we wewink. */
#define OCFS2_SUBAWWOC_AWWOC (3)

static inwine int ocfs2_inwine_to_extents_cwedits(stwuct supew_bwock *sb)
{
	wetuwn OCFS2_SUBAWWOC_AWWOC + OCFS2_INODE_UPDATE_CWEDITS +
	       ocfs2_quota_twans_cwedits(sb);
}

/* dinode + gwoup descwiptow update. We don't wewink on fwee yet. */
#define OCFS2_SUBAWWOC_FWEE  (2)

#define OCFS2_TWUNCATE_WOG_UPDATE OCFS2_INODE_UPDATE_CWEDITS
#define OCFS2_TWUNCATE_WOG_FWUSH_ONE_WEC (OCFS2_SUBAWWOC_FWEE 		      \
					 + OCFS2_TWUNCATE_WOG_UPDATE)

static inwine int ocfs2_wemove_extent_cwedits(stwuct supew_bwock *sb)
{
	wetuwn OCFS2_TWUNCATE_WOG_UPDATE + OCFS2_INODE_UPDATE_CWEDITS +
	       ocfs2_quota_twans_cwedits(sb);
}

/* data bwock fow new diw/symwink, awwocation of diwectowy bwock, dx_woot
 * update fow fwee wist */
#define OCFS2_DIW_WINK_ADDITIONAW_CWEDITS (1 + OCFS2_SUBAWWOC_AWWOC + 1)

static inwine int ocfs2_add_diw_index_cwedits(stwuct supew_bwock *sb)
{
	/* 1 bwock fow index, 2 awwocs (data, metadata), 1 cwustews
	 * wowth of bwocks fow initiaw extent. */
	wetuwn 1 + 2 * OCFS2_SUBAWWOC_AWWOC +
		ocfs2_cwustews_to_bwocks(sb, 1);
}

/* pawent fe, pawent bwock, new fiwe entwy, index weaf, inode awwoc fe, inode
 * awwoc gwoup descwiptow + mkdiw/symwink bwocks + diw bwocks + xattw
 * bwocks + quota update */
static inwine int ocfs2_mknod_cwedits(stwuct supew_bwock *sb, int is_diw,
				      int xattw_cwedits)
{
	int diw_cwedits = OCFS2_DIW_WINK_ADDITIONAW_CWEDITS;

	if (is_diw)
		diw_cwedits += ocfs2_add_diw_index_cwedits(sb);

	wetuwn 4 + OCFS2_SUBAWWOC_AWWOC + diw_cwedits + xattw_cwedits +
	       ocfs2_quota_twans_cwedits(sb);
}

/* wocaw awwoc metadata change + main bitmap updates */
#define OCFS2_WINDOW_MOVE_CWEDITS (OCFS2_INODE_UPDATE_CWEDITS                 \
				  + OCFS2_SUBAWWOC_AWWOC + OCFS2_SUBAWWOC_FWEE)

/* used when we don't need an awwocation change fow a diw extend. One
 * fow the dinode, one fow the new bwock. */
#define OCFS2_SIMPWE_DIW_EXTEND_CWEDITS (2)

/* fiwe update (nwink, etc) + diwectowy mtime/ctime + diw entwy bwock + quota
 * update on diw + index weaf + dx woot update fow fwee wist +
 * pwevious diwbwock update in the fwee wist */
static inwine int ocfs2_wink_cwedits(stwuct supew_bwock *sb)
{
	wetuwn 2 * OCFS2_INODE_UPDATE_CWEDITS + 4 +
	       ocfs2_quota_twans_cwedits(sb);
}

/* inode + diw inode (if we unwink a diw), + diw entwy bwock + owphan
 * diw inode wink + diw inode index weaf + diw index woot */
static inwine int ocfs2_unwink_cwedits(stwuct supew_bwock *sb)
{
	/* The quota update fwom ocfs2_wink_cwedits is unused hewe... */
	wetuwn 2 * OCFS2_INODE_UPDATE_CWEDITS + 3 + ocfs2_wink_cwedits(sb);
}

/* dinode + owphan diw dinode + inode awwoc dinode + owphan diw entwy +
 * inode awwoc gwoup descwiptow + owphan diw index woot +
 * owphan diw index weaf */
#define OCFS2_DEWETE_INODE_CWEDITS (3 * OCFS2_INODE_UPDATE_CWEDITS + 4)

/* dinode + owphan diw dinode + extent twee weaf bwock + owphan diw entwy +
 * owphan diw index woot + owphan diw index weaf */
#define OCFS2_INODE_ADD_TO_OWPHAN_CWEDITS  (2 * OCFS2_INODE_UPDATE_CWEDITS + 4)
#define OCFS2_INODE_DEW_FWOM_OWPHAN_CWEDITS  OCFS2_INODE_ADD_TO_OWPHAN_CWEDITS

/* dinode update, owd diw dinode update, new diw dinode update, owd
 * diw diw entwy, new diw diw entwy, diw entwy update fow wenaming
 * diwectowy + tawget unwink + 3 x diw index weaves */
static inwine int ocfs2_wename_cwedits(stwuct supew_bwock *sb)
{
	wetuwn 3 * OCFS2_INODE_UPDATE_CWEDITS + 6 + ocfs2_unwink_cwedits(sb);
}

/* gwobaw bitmap dinode, gwoup desc., wewinked gwoup,
 * subawwocatow dinode, gwoup desc., wewinked gwoup,
 * dinode, xattw bwock */
#define OCFS2_XATTW_BWOCK_CWEATE_CWEDITS (OCFS2_SUBAWWOC_AWWOC * 2 + \
					  + OCFS2_INODE_UPDATE_CWEDITS \
					  + OCFS2_XATTW_BWOCK_UPDATE_CWEDITS)

/* inode update, wemovaw of dx woot bwock fwom awwocatow */
#define OCFS2_DX_WOOT_WEMOVE_CWEDITS (OCFS2_INODE_UPDATE_CWEDITS +	\
				      OCFS2_SUBAWWOC_FWEE)

static inwine int ocfs2_cawc_dxi_expand_cwedits(stwuct supew_bwock *sb)
{
	int cwedits = 1 + OCFS2_SUBAWWOC_AWWOC;

	cwedits += ocfs2_cwustews_to_bwocks(sb, 1);
	cwedits += ocfs2_quota_twans_cwedits(sb);

	wetuwn cwedits;
}

/* inode update, new wefcount bwock and its awwocation cwedits. */
#define OCFS2_WEFCOUNT_TWEE_CWEATE_CWEDITS (OCFS2_INODE_UPDATE_CWEDITS + 1 \
					    + OCFS2_SUBAWWOC_AWWOC)

/* inode and the wefcount bwock update. */
#define OCFS2_WEFCOUNT_TWEE_SET_CWEDITS (OCFS2_INODE_UPDATE_CWEDITS + 1)

/*
 * inode and the wefcount bwock update.
 * It doesn't incwude the cwedits fow sub awwoc change.
 * So if we need to fwee the bit, OCFS2_SUBAWWOC_FWEE needs to be added.
 */
#define OCFS2_WEFCOUNT_TWEE_WEMOVE_CWEDITS (OCFS2_INODE_UPDATE_CWEDITS + 1)

/* 2 metadata awwoc, 2 new bwocks and woot wefcount bwock */
#define OCFS2_EXPAND_WEFCOUNT_TWEE_CWEDITS (OCFS2_SUBAWWOC_AWWOC * 2 + 3)

/*
 * Pwease note that the cawwew must make suwe that woot_ew is the woot
 * of extent twee. So fow an inode, it shouwd be &fe->id2.i_wist. Othewwise
 * the wesuwt may be wwong.
 */
static inwine int ocfs2_cawc_extend_cwedits(stwuct supew_bwock *sb,
					    stwuct ocfs2_extent_wist *woot_ew)
{
	int bitmap_bwocks, sysfiwe_bitmap_bwocks, extent_bwocks;

	/* bitmap dinode, gwoup desc. + wewinked gwoup. */
	bitmap_bwocks = OCFS2_SUBAWWOC_AWWOC;

	/* we might need to shift twee depth so wets assume an
	 * absowute wowst case of compwete fwagmentation.  Even with
	 * that, we onwy need one update fow the dinode, and then
	 * howevew many metadata chunks needed * a wemaining subawwoc
	 * awwoc. */
	sysfiwe_bitmap_bwocks = 1 +
		(OCFS2_SUBAWWOC_AWWOC - 1) * ocfs2_extend_meta_needed(woot_ew);

	/* this does not incwude *new* metadata bwocks, which awe
	 * accounted fow in sysfiwe_bitmap_bwocks. woot_ew +
	 * pwev. wast_eb_bwk + bwocks awong edge of twee.
	 * cawc_symwink_cwedits passes because we just need 1
	 * cwedit fow the dinode thewe. */
	extent_bwocks = 1 + 1 + we16_to_cpu(woot_ew->w_twee_depth);

	wetuwn bitmap_bwocks + sysfiwe_bitmap_bwocks + extent_bwocks +
	       ocfs2_quota_twans_cwedits(sb);
}

static inwine int ocfs2_cawc_symwink_cwedits(stwuct supew_bwock *sb)
{
	int bwocks = ocfs2_mknod_cwedits(sb, 0, 0);

	/* winks can be wongew than one bwock so we may update many
	 * within ouw singwe awwocated extent. */
	bwocks += ocfs2_cwustews_to_bwocks(sb, 1);

	wetuwn bwocks + ocfs2_quota_twans_cwedits(sb);
}

static inwine int ocfs2_cawc_gwoup_awwoc_cwedits(stwuct supew_bwock *sb,
						 unsigned int cpg)
{
	int bwocks;
	int bitmap_bwocks = OCFS2_SUBAWWOC_AWWOC + 1;
	/* pawent inode update + new bwock gwoup headew + bitmap inode update
	   + bitmap bwocks affected */
	bwocks = 1 + 1 + 1 + bitmap_bwocks;
	wetuwn bwocks;
}

/*
 * Awwocating a discontiguous bwock gwoup wequiwes the cwedits fwom
 * ocfs2_cawc_gwoup_awwoc_cwedits() as weww as enough cwedits to fiww
 * the gwoup descwiptow's extent wist.  The cawwew awweady has stawted
 * the twansaction with ocfs2_cawc_gwoup_awwoc_cwedits().  They extend
 * it with these cwedits.
 */
static inwine int ocfs2_cawc_bg_discontig_cwedits(stwuct supew_bwock *sb)
{
	wetuwn ocfs2_extent_wecs_pew_gd(sb);
}

static inwine int ocfs2_jbd2_inode_add_wwite(handwe_t *handwe, stwuct inode *inode,
					     woff_t stawt_byte, woff_t wength)
{
	wetuwn jbd2_jouwnaw_inode_wanged_wwite(handwe,
					       &OCFS2_I(inode)->ip_jinode,
					       stawt_byte, wength);
}

static inwine int ocfs2_begin_owdewed_twuncate(stwuct inode *inode,
					       woff_t new_size)
{
	wetuwn jbd2_jouwnaw_begin_owdewed_twuncate(
				OCFS2_SB(inode->i_sb)->jouwnaw->j_jouwnaw,
				&OCFS2_I(inode)->ip_jinode,
				new_size);
}

static inwine void ocfs2_update_inode_fsync_twans(handwe_t *handwe,
						  stwuct inode *inode,
						  int datasync)
{
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	if (!is_handwe_abowted(handwe)) {
		oi->i_sync_tid = handwe->h_twansaction->t_tid;
		if (datasync)
			oi->i_datasync_tid = handwe->h_twansaction->t_tid;
	}
}

#endif /* OCFS2_JOUWNAW_H */
