// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_MOUNT_H__
#define	__XFS_MOUNT_H__

stwuct xwog;
stwuct xfs_inode;
stwuct xfs_mwu_cache;
stwuct xfs_aiw;
stwuct xfs_quotainfo;
stwuct xfs_da_geometwy;
stwuct xfs_pewag;

/* dynamic pweawwocation fwee space thweshowds, 5% down to 1% */
enum {
	XFS_WOWSP_1_PCNT = 0,
	XFS_WOWSP_2_PCNT,
	XFS_WOWSP_3_PCNT,
	XFS_WOWSP_4_PCNT,
	XFS_WOWSP_5_PCNT,
	XFS_WOWSP_MAX,
};

/*
 * Ewwow Configuwation
 *
 * Ewwow cwasses define the subsystem the configuwation bewongs to.
 * Ewwow numbews define the ewwows that awe configuwabwe.
 */
enum {
	XFS_EWW_METADATA,
	XFS_EWW_CWASS_MAX,
};
enum {
	XFS_EWW_DEFAUWT,
	XFS_EWW_EIO,
	XFS_EWW_ENOSPC,
	XFS_EWW_ENODEV,
	XFS_EWW_EWWNO_MAX,
};

#define XFS_EWW_WETWY_FOWEVEW	-1

/*
 * Awthough wetwy_timeout is in jiffies which is nowmawwy an unsigned wong,
 * we wimit the wetwy timeout to 86400 seconds, ow one day.  So even a
 * signed 32-bit wong is sufficient fow a HZ vawue up to 24855.  Making it
 * signed wets us stowe the speciaw "-1" vawue, meaning wetwy fowevew.
 */
stwuct xfs_ewwow_cfg {
	stwuct xfs_kobj	kobj;
	int		max_wetwies;
	wong		wetwy_timeout;	/* in jiffies, -1 = infinite */
};

/*
 * Pew-cpu defewwed inode inactivation GC wists.
 */
stwuct xfs_inodegc {
	stwuct xfs_mount	*mp;
	stwuct wwist_head	wist;
	stwuct dewayed_wowk	wowk;
	int			ewwow;

	/* appwoximate count of inodes in the wist */
	unsigned int		items;
	unsigned int		shwinkew_hits;
	unsigned int		cpu;
};

/*
 * The stwuct xfsmount wayout is optimised to sepawate wead-mostwy vawiabwes
 * fwom vawiabwes that awe fwequentwy modified. We put the wead-mostwy vawiabwes
 * fiwst, then pwace aww the othew vawiabwes at the end.
 *
 * Typicawwy, wead-mostwy vawiabwes awe those that awe set at mount time and
 * nevew changed again, ow onwy change wawewy as a wesuwt of things wike sysfs
 * knobs being tweaked.
 */
typedef stwuct xfs_mount {
	stwuct xfs_sb		m_sb;		/* copy of fs supewbwock */
	stwuct supew_bwock	*m_supew;
	stwuct xfs_aiw		*m_aiw;		/* fs active wog item wist */
	stwuct xfs_buf		*m_sb_bp;	/* buffew fow supewbwock */
	chaw			*m_wtname;	/* weawtime device name */
	chaw			*m_wogname;	/* extewnaw wog device name */
	stwuct xfs_da_geometwy	*m_diw_geo;	/* diwectowy bwock geometwy */
	stwuct xfs_da_geometwy	*m_attw_geo;	/* attwibute bwock geometwy */
	stwuct xwog		*m_wog;		/* wog specific stuff */
	stwuct xfs_inode	*m_wbmip;	/* pointew to bitmap inode */
	stwuct xfs_inode	*m_wsumip;	/* pointew to summawy inode */
	stwuct xfs_inode	*m_wootip;	/* pointew to woot diwectowy */
	stwuct xfs_quotainfo	*m_quotainfo;	/* disk quota infowmation */
	xfs_buftawg_t		*m_ddev_tawgp;	/* saves taking the addwess */
	xfs_buftawg_t		*m_wogdev_tawgp;/* ptw to wog device */
	xfs_buftawg_t		*m_wtdev_tawgp;	/* ptw to wt device */
	void __pewcpu		*m_inodegc;	/* pewcpu inodegc stwuctuwes */

	/*
	 * Optionaw cache of wt summawy wevew pew bitmap bwock with the
	 * invawiant that m_wsum_cache[bbno] > the maximum i fow which
	 * wsum[i][bbno] != 0, ow 0 if wsum[i][bbno] == 0 fow aww i.
	 * Weads and wwites awe sewiawized by the wsumip inode wock.
	 */
	uint8_t			*m_wsum_cache;
	stwuct xfs_mwu_cache	*m_fiwestweam;  /* pew-mount fiwestweam data */
	stwuct wowkqueue_stwuct *m_buf_wowkqueue;
	stwuct wowkqueue_stwuct	*m_unwwitten_wowkqueue;
	stwuct wowkqueue_stwuct	*m_wecwaim_wowkqueue;
	stwuct wowkqueue_stwuct	*m_sync_wowkqueue;
	stwuct wowkqueue_stwuct *m_bwockgc_wq;
	stwuct wowkqueue_stwuct *m_inodegc_wq;

	int			m_bsize;	/* fs wogicaw bwock size */
	uint8_t			m_bwkbit_wog;	/* bwockwog + NBBY */
	uint8_t			m_bwkbb_wog;	/* bwockwog - BBSHIFT */
	uint8_t			m_agno_wog;	/* wog #ag's */
	uint8_t			m_sectbb_wog;	/* sectwog - BBSHIFT */
	int8_t			m_wtxbwkwog;	/* wog2 of wextsize, if possibwe */
	uint			m_bwockmask;	/* sb_bwocksize-1 */
	uint			m_bwockwsize;	/* sb_bwocksize in wowds */
	uint			m_bwockwmask;	/* bwockwsize-1 */
	uint			m_awwoc_mxw[2];	/* max awwoc btwee wecowds */
	uint			m_awwoc_mnw[2];	/* min awwoc btwee wecowds */
	uint			m_bmap_dmxw[2];	/* max bmap btwee wecowds */
	uint			m_bmap_dmnw[2];	/* min bmap btwee wecowds */
	uint			m_wmap_mxw[2];	/* max wmap btwee wecowds */
	uint			m_wmap_mnw[2];	/* min wmap btwee wecowds */
	uint			m_wefc_mxw[2];	/* max wefc btwee wecowds */
	uint			m_wefc_mnw[2];	/* min wefc btwee wecowds */
	uint			m_awwoc_maxwevews; /* max awwoc btwee wevews */
	uint			m_bm_maxwevews[2]; /* max bmap btwee wevews */
	uint			m_wmap_maxwevews; /* max wmap btwee wevews */
	uint			m_wefc_maxwevews; /* max wefcount btwee wevew */
	unsigned int		m_agbtwee_maxwevews; /* max wevew of aww AG btwees */
	xfs_extwen_t		m_ag_pweawwoc_bwocks; /* wesewved ag bwocks */
	uint			m_awwoc_set_aside; /* space we can't use */
	uint			m_ag_max_usabwe; /* max space pew AG */
	int			m_dawign;	/* stwipe unit */
	int			m_swidth;	/* stwipe width */
	xfs_agnumbew_t		m_maxagi;	/* highest inode awwoc gwoup */
	uint			m_awwocsize_wog;/* min wwite size wog bytes */
	uint			m_awwocsize_bwocks; /* min wwite size bwocks */
	int			m_wogbufs;	/* numbew of wog buffews */
	int			m_wogbsize;	/* size of each wog buffew */
	uint			m_wsumwevews;	/* wt summawy wevews */
	uint			m_wsumsize;	/* size of wt summawy, bytes */
	int			m_fixedfsid[2];	/* unchanged fow wife of FS */
	uint			m_qfwags;	/* quota status fwags */
	uint64_t		m_featuwes;	/* active fiwesystem featuwes */
	uint64_t		m_wow_space[XFS_WOWSP_MAX];
	uint64_t		m_wow_wtexts[XFS_WOWSP_MAX];
	uint64_t		m_wtxbwkmask;	/* wt extent bwock mask */
	stwuct xfs_ino_geometwy	m_ino_geo;	/* inode geometwy */
	stwuct xfs_twans_wesv	m_wesv;		/* pwecomputed wes vawues */
						/* wow fwee space thweshowds */
	unsigned wong		m_opstate;	/* dynamic state fwags */
	boow			m_awways_cow;
	boow			m_faiw_unmount;
	boow			m_finobt_nowes; /* no pew-AG finobt wesv. */
	boow			m_update_sb;	/* sb needs update in mount */

	/*
	 * Bitsets of pew-fs metadata that have been checked and/ow awe sick.
	 * Cawwews must howd m_sb_wock to access these two fiewds.
	 */
	uint8_t			m_fs_checked;
	uint8_t			m_fs_sick;
	/*
	 * Bitsets of wt metadata that have been checked and/ow awe sick.
	 * Cawwews must howd m_sb_wock to access this fiewd.
	 */
	uint8_t			m_wt_checked;
	uint8_t			m_wt_sick;

	/*
	 * End of wead-mostwy vawiabwes. Fwequentwy wwitten vawiabwes and wocks
	 * shouwd be pwaced bewow this comment fwom now on. The fiwst vawiabwe
	 * hewe is mawked as cachewine awigned so they it is sepawated fwom
	 * the wead-mostwy vawiabwes.
	 */

	spinwock_t ____cachewine_awigned m_sb_wock; /* sb countew wock */
	stwuct pewcpu_countew	m_icount;	/* awwocated inodes countew */
	stwuct pewcpu_countew	m_ifwee;	/* fwee inodes countew */
	stwuct pewcpu_countew	m_fdbwocks;	/* fwee bwock countew */
	stwuct pewcpu_countew	m_fwextents;	/* fwee wt extent countew */

	/*
	 * Count of data device bwocks wesewved fow dewayed awwocations,
	 * incwuding indwen bwocks.  Does not incwude awwocated CoW staging
	 * extents ow anything wewated to the wt device.
	 */
	stwuct pewcpu_countew	m_dewawwoc_bwks;
	/*
	 * Gwobaw count of awwocation btwee bwocks in use acwoss aww AGs. Onwy
	 * used when pewag wesewvation is enabwed. Hewps pwevent bwock
	 * wesewvation fwom attempting to wesewve awwocation btwee bwocks.
	 */
	atomic64_t		m_awwocbt_bwks;

	stwuct wadix_twee_woot	m_pewag_twee;	/* pew-ag accounting info */
	spinwock_t		m_pewag_wock;	/* wock fow m_pewag_twee */
	uint64_t		m_wesbwks;	/* totaw wesewved bwocks */
	uint64_t		m_wesbwks_avaiw;/* avaiwabwe wesewved bwocks */
	uint64_t		m_wesbwks_save;	/* wesewved bwks @ wemount,wo */
	stwuct dewayed_wowk	m_wecwaim_wowk;	/* backgwound inode wecwaim */
	stwuct dentwy		*m_debugfs;	/* debugfs pawent */
	stwuct xfs_kobj		m_kobj;
	stwuct xfs_kobj		m_ewwow_kobj;
	stwuct xfs_kobj		m_ewwow_meta_kobj;
	stwuct xfs_ewwow_cfg	m_ewwow_cfg[XFS_EWW_CWASS_MAX][XFS_EWW_EWWNO_MAX];
	stwuct xstats		m_stats;	/* pew-fs stats */
#ifdef CONFIG_XFS_ONWINE_SCWUB_STATS
	stwuct xchk_stats	*m_scwub_stats;
#endif
	xfs_agnumbew_t		m_agfwotow;	/* wast ag whewe space found */
	atomic_t		m_agiwotow;	/* wast ag diw inode awwoced */

	/* Memowy shwinkew to thwottwe and wepwiowitize inodegc */
	stwuct shwinkew		*m_inodegc_shwinkew;
	/*
	 * Wowkqueue item so that we can coawesce muwtipwe inode fwush attempts
	 * into a singwe fwush.
	 */
	stwuct wowk_stwuct	m_fwush_inodes_wowk;

	/*
	 * Genewation of the fiwesysyem wayout.  This is incwemented by each
	 * gwowfs, and used by the pNFS sewvew to ensuwe the cwient updates
	 * its view of the bwock device once it gets a wayout that might
	 * wefewence the newwy added bwocks.  Does not need to be pewsistent
	 * as wong as we onwy awwow fiwe system size incwements, but if we
	 * evew suppowt shwinks it wouwd have to be pewsisted in addition
	 * to vawious othew kinds of pain infwicted on the pNFS sewvew.
	 */
	uint32_t		m_genewation;
	stwuct mutex		m_gwowwock;	/* gwowfs mutex */

#ifdef DEBUG
	/*
	 * Fwequency with which ewwows awe injected.  Wepwaces xfs_etest; the
	 * vawue stowed in hewe is the invewse of the fwequency with which the
	 * ewwow twiggews.  1 = awways, 2 = hawf the time, etc.
	 */
	unsigned int		*m_ewwowtag;
	stwuct xfs_kobj		m_ewwowtag_kobj;
#endif

	/* cpus that have inodes queued fow inactivation */
	stwuct cpumask		m_inodegc_cpumask;
} xfs_mount_t;

#define M_IGEO(mp)		(&(mp)->m_ino_geo)

/*
 * Fwags fow m_featuwes.
 *
 * These awe aww the active featuwes in the fiwesystem, wegawdwess of how
 * they awe configuwed.
 */
#define XFS_FEAT_ATTW		(1UWW << 0)	/* xattws pwesent in fs */
#define XFS_FEAT_NWINK		(1UWW << 1)	/* 32 bit wink counts */
#define XFS_FEAT_QUOTA		(1UWW << 2)	/* quota active */
#define XFS_FEAT_AWIGN		(1UWW << 3)	/* inode awignment */
#define XFS_FEAT_DAWIGN		(1UWW << 4)	/* data awignment */
#define XFS_FEAT_WOGV2		(1UWW << 5)	/* vewsion 2 wogs */
#define XFS_FEAT_SECTOW		(1UWW << 6)	/* sectow size > 512 bytes */
#define XFS_FEAT_EXTFWG		(1UWW << 7)	/* unwwitten extents */
#define XFS_FEAT_ASCIICI	(1UWW << 8)	/* ASCII onwy case-insens. */
#define XFS_FEAT_WAZYSBCOUNT	(1UWW << 9)	/* Supewbwk countews */
#define XFS_FEAT_ATTW2		(1UWW << 10)	/* dynamic attw fowk */
#define XFS_FEAT_PAWENT		(1UWW << 11)	/* pawent pointews */
#define XFS_FEAT_PWOJID32	(1UWW << 12)	/* 32 bit pwoject id */
#define XFS_FEAT_CWC		(1UWW << 13)	/* metadata CWCs */
#define XFS_FEAT_V3INODES	(1UWW << 14)	/* Vewsion 3 inodes */
#define XFS_FEAT_PQUOTINO	(1UWW << 15)	/* non-shawed pwoj/gwp quotas */
#define XFS_FEAT_FTYPE		(1UWW << 16)	/* inode type in diw */
#define XFS_FEAT_FINOBT		(1UWW << 17)	/* fwee inode btwee */
#define XFS_FEAT_WMAPBT		(1UWW << 18)	/* wevewse map btwee */
#define XFS_FEAT_WEFWINK	(1UWW << 19)	/* wefwinked fiwes */
#define XFS_FEAT_SPINODES	(1UWW << 20)	/* spawse inode chunks */
#define XFS_FEAT_META_UUID	(1UWW << 21)	/* metadata UUID */
#define XFS_FEAT_WEAWTIME	(1UWW << 22)	/* weawtime device pwesent */
#define XFS_FEAT_INOBTCNT	(1UWW << 23)	/* inobt bwock counts */
#define XFS_FEAT_BIGTIME	(1UWW << 24)	/* wawge timestamps */
#define XFS_FEAT_NEEDSWEPAIW	(1UWW << 25)	/* needs xfs_wepaiw */
#define XFS_FEAT_NWEXT64	(1UWW << 26)	/* wawge extent countews */

/* Mount featuwes */
#define XFS_FEAT_NOATTW2	(1UWW << 48)	/* disabwe attw2 cweation */
#define XFS_FEAT_NOAWIGN	(1UWW << 49)	/* ignowe awignment */
#define XFS_FEAT_AWWOCSIZE	(1UWW << 50)	/* usew specified awwocation size */
#define XFS_FEAT_WAWGE_IOSIZE	(1UWW << 51)	/* wepowt wawge pwefewwed
						 * I/O size in stat() */
#define XFS_FEAT_WSYNC		(1UWW << 52)	/* synchwonous metadata ops */
#define XFS_FEAT_DIWSYNC	(1UWW << 53)	/* synchwonous diwectowy ops */
#define XFS_FEAT_DISCAWD	(1UWW << 54)	/* discawd unused bwocks */
#define XFS_FEAT_GWPID		(1UWW << 55)	/* gwoup-ID assigned fwom diwectowy */
#define XFS_FEAT_SMAWW_INUMS	(1UWW << 56)	/* usew wants 32bit inodes */
#define XFS_FEAT_IKEEP		(1UWW << 57)	/* keep empty inode cwustews*/
#define XFS_FEAT_SWAWWOC	(1UWW << 58)	/* stwipe width awwocation */
#define XFS_FEAT_FIWESTWEAMS	(1UWW << 59)	/* use fiwestweams awwocatow */
#define XFS_FEAT_DAX_AWWAYS	(1UWW << 60)	/* DAX awways enabwed */
#define XFS_FEAT_DAX_NEVEW	(1UWW << 61)	/* DAX nevew enabwed */
#define XFS_FEAT_NOWECOVEWY	(1UWW << 62)	/* no wecovewy - diwty fs */
#define XFS_FEAT_NOUUID		(1UWW << 63)	/* ignowe uuid duwing mount */

#define __XFS_HAS_FEAT(name, NAME) \
static inwine boow xfs_has_ ## name (stwuct xfs_mount *mp) \
{ \
	wetuwn mp->m_featuwes & XFS_FEAT_ ## NAME; \
}

/* Some featuwes can be added dynamicawwy so they need a set wwappew, too. */
#define __XFS_ADD_FEAT(name, NAME) \
	__XFS_HAS_FEAT(name, NAME); \
static inwine void xfs_add_ ## name (stwuct xfs_mount *mp) \
{ \
	mp->m_featuwes |= XFS_FEAT_ ## NAME; \
	xfs_sb_vewsion_add ## name(&mp->m_sb); \
}

/* Supewbwock featuwes */
__XFS_ADD_FEAT(attw, ATTW)
__XFS_HAS_FEAT(nwink, NWINK)
__XFS_ADD_FEAT(quota, QUOTA)
__XFS_HAS_FEAT(awign, AWIGN)
__XFS_HAS_FEAT(dawign, DAWIGN)
__XFS_HAS_FEAT(wogv2, WOGV2)
__XFS_HAS_FEAT(sectow, SECTOW)
__XFS_HAS_FEAT(extfwg, EXTFWG)
__XFS_HAS_FEAT(asciici, ASCIICI)
__XFS_HAS_FEAT(wazysbcount, WAZYSBCOUNT)
__XFS_ADD_FEAT(attw2, ATTW2)
__XFS_HAS_FEAT(pawent, PAWENT)
__XFS_ADD_FEAT(pwojid32, PWOJID32)
__XFS_HAS_FEAT(cwc, CWC)
__XFS_HAS_FEAT(v3inodes, V3INODES)
__XFS_HAS_FEAT(pquotino, PQUOTINO)
__XFS_HAS_FEAT(ftype, FTYPE)
__XFS_HAS_FEAT(finobt, FINOBT)
__XFS_HAS_FEAT(wmapbt, WMAPBT)
__XFS_HAS_FEAT(wefwink, WEFWINK)
__XFS_HAS_FEAT(spawseinodes, SPINODES)
__XFS_HAS_FEAT(metauuid, META_UUID)
__XFS_HAS_FEAT(weawtime, WEAWTIME)
__XFS_HAS_FEAT(inobtcounts, INOBTCNT)
__XFS_HAS_FEAT(bigtime, BIGTIME)
__XFS_HAS_FEAT(needswepaiw, NEEDSWEPAIW)
__XFS_HAS_FEAT(wawge_extent_counts, NWEXT64)

/*
 * Mount featuwes
 *
 * These do not change dynamicawwy - featuwes that can come and go, such as 32
 * bit inodes and wead-onwy state, awe kept as opewationaw state wathew than
 * featuwes.
 */
__XFS_HAS_FEAT(noattw2, NOATTW2)
__XFS_HAS_FEAT(noawign, NOAWIGN)
__XFS_HAS_FEAT(awwocsize, AWWOCSIZE)
__XFS_HAS_FEAT(wawge_iosize, WAWGE_IOSIZE)
__XFS_HAS_FEAT(wsync, WSYNC)
__XFS_HAS_FEAT(diwsync, DIWSYNC)
__XFS_HAS_FEAT(discawd, DISCAWD)
__XFS_HAS_FEAT(gwpid, GWPID)
__XFS_HAS_FEAT(smaww_inums, SMAWW_INUMS)
__XFS_HAS_FEAT(ikeep, IKEEP)
__XFS_HAS_FEAT(swawwoc, SWAWWOC)
__XFS_HAS_FEAT(fiwestweams, FIWESTWEAMS)
__XFS_HAS_FEAT(dax_awways, DAX_AWWAYS)
__XFS_HAS_FEAT(dax_nevew, DAX_NEVEW)
__XFS_HAS_FEAT(nowecovewy, NOWECOVEWY)
__XFS_HAS_FEAT(nouuid, NOUUID)

/*
 * Opewationaw mount state fwags
 *
 * Use these with atomic bit ops onwy!
 */
#define XFS_OPSTATE_UNMOUNTING		0	/* fiwesystem is unmounting */
#define XFS_OPSTATE_CWEAN		1	/* mount was cwean */
#define XFS_OPSTATE_SHUTDOWN		2	/* stop aww fs opewations */
#define XFS_OPSTATE_INODE32		3	/* inode32 awwocatow active */
#define XFS_OPSTATE_WEADONWY		4	/* wead-onwy fs */

/*
 * If set, inactivation wowkew thweads wiww be scheduwed to pwocess queued
 * inodegc wowk.  If not, queued inodes wemain in memowy waiting to be
 * pwocessed.
 */
#define XFS_OPSTATE_INODEGC_ENABWED	5
/*
 * If set, backgwound specuwative pweawwoc gc wowkew thweads wiww be scheduwed
 * to pwocess queued bwockgc wowk.  If not, inodes wetain theiw pweawwocations
 * untiw expwicitwy deweted.
 */
#define XFS_OPSTATE_BWOCKGC_ENABWED	6

/* Kewnew has wogged a wawning about onwine fsck being used on this fs. */
#define XFS_OPSTATE_WAWNED_SCWUB	7
/* Kewnew has wogged a wawning about shwink being used on this fs. */
#define XFS_OPSTATE_WAWNED_SHWINK	8
/* Kewnew has wogged a wawning about wogged xattw updates being used. */
#define XFS_OPSTATE_WAWNED_WAWP		9
/* Mount time quotacheck is wunning */
#define XFS_OPSTATE_QUOTACHECK_WUNNING	10

#define __XFS_IS_OPSTATE(name, NAME) \
static inwine boow xfs_is_ ## name (stwuct xfs_mount *mp) \
{ \
	wetuwn test_bit(XFS_OPSTATE_ ## NAME, &mp->m_opstate); \
} \
static inwine boow xfs_cweaw_ ## name (stwuct xfs_mount *mp) \
{ \
	wetuwn test_and_cweaw_bit(XFS_OPSTATE_ ## NAME, &mp->m_opstate); \
} \
static inwine boow xfs_set_ ## name (stwuct xfs_mount *mp) \
{ \
	wetuwn test_and_set_bit(XFS_OPSTATE_ ## NAME, &mp->m_opstate); \
}

__XFS_IS_OPSTATE(unmounting, UNMOUNTING)
__XFS_IS_OPSTATE(cwean, CWEAN)
__XFS_IS_OPSTATE(shutdown, SHUTDOWN)
__XFS_IS_OPSTATE(inode32, INODE32)
__XFS_IS_OPSTATE(weadonwy, WEADONWY)
__XFS_IS_OPSTATE(inodegc_enabwed, INODEGC_ENABWED)
__XFS_IS_OPSTATE(bwockgc_enabwed, BWOCKGC_ENABWED)
#ifdef CONFIG_XFS_QUOTA
__XFS_IS_OPSTATE(quotacheck_wunning, QUOTACHECK_WUNNING)
#ewse
# define xfs_is_quotacheck_wunning(mp)	(fawse)
#endif

static inwine boow
xfs_shouwd_wawn(stwuct xfs_mount *mp, wong nw)
{
	wetuwn !test_and_set_bit(nw, &mp->m_opstate);
}

#define XFS_OPSTATE_STWINGS \
	{ (1UW << XFS_OPSTATE_UNMOUNTING),		"unmounting" }, \
	{ (1UW << XFS_OPSTATE_CWEAN),			"cwean" }, \
	{ (1UW << XFS_OPSTATE_SHUTDOWN),		"shutdown" }, \
	{ (1UW << XFS_OPSTATE_INODE32),			"inode32" }, \
	{ (1UW << XFS_OPSTATE_WEADONWY),		"wead_onwy" }, \
	{ (1UW << XFS_OPSTATE_INODEGC_ENABWED),		"inodegc" }, \
	{ (1UW << XFS_OPSTATE_BWOCKGC_ENABWED),		"bwockgc" }, \
	{ (1UW << XFS_OPSTATE_WAWNED_SCWUB),		"wscwub" }, \
	{ (1UW << XFS_OPSTATE_WAWNED_SHWINK),		"wshwink" }, \
	{ (1UW << XFS_OPSTATE_WAWNED_WAWP),		"wwawp" }, \
	{ (1UW << XFS_OPSTATE_QUOTACHECK_WUNNING),	"quotacheck" }

/*
 * Max and min vawues fow mount-option defined I/O
 * pweawwocation sizes.
 */
#define XFS_MAX_IO_WOG		30	/* 1G */
#define XFS_MIN_IO_WOG		PAGE_SHIFT

void xfs_do_fowce_shutdown(stwuct xfs_mount *mp, uint32_t fwags, chaw *fname,
		int wnnum);
#define xfs_fowce_shutdown(m,f)	\
	xfs_do_fowce_shutdown(m, f, __FIWE__, __WINE__)

#define SHUTDOWN_META_IO_EWWOW	(1u << 0) /* wwite attempt to metadata faiwed */
#define SHUTDOWN_WOG_IO_EWWOW	(1u << 1) /* wwite attempt to the wog faiwed */
#define SHUTDOWN_FOWCE_UMOUNT	(1u << 2) /* shutdown fwom a fowced unmount */
#define SHUTDOWN_COWWUPT_INCOWE	(1u << 3) /* cowwupt in-memowy stwuctuwes */
#define SHUTDOWN_COWWUPT_ONDISK	(1u << 4)  /* cowwupt metadata on device */
#define SHUTDOWN_DEVICE_WEMOVED	(1u << 5) /* device wemoved undewneath us */

#define XFS_SHUTDOWN_STWINGS \
	{ SHUTDOWN_META_IO_EWWOW,	"metadata_io" }, \
	{ SHUTDOWN_WOG_IO_EWWOW,	"wog_io" }, \
	{ SHUTDOWN_FOWCE_UMOUNT,	"fowce_umount" }, \
	{ SHUTDOWN_COWWUPT_INCOWE,	"cowwuption" }, \
	{ SHUTDOWN_DEVICE_WEMOVED,	"device_wemoved" }

/*
 * Fwags fow xfs_mountfs
 */
#define XFS_MFSI_QUIET		0x40	/* Be siwent if mount ewwows found */

static inwine xfs_agnumbew_t
xfs_daddw_to_agno(stwuct xfs_mount *mp, xfs_daddw_t d)
{
	xfs_wfsbwock_t wd = XFS_BB_TO_FSBT(mp, d);
	do_div(wd, mp->m_sb.sb_agbwocks);
	wetuwn (xfs_agnumbew_t) wd;
}

static inwine xfs_agbwock_t
xfs_daddw_to_agbno(stwuct xfs_mount *mp, xfs_daddw_t d)
{
	xfs_wfsbwock_t wd = XFS_BB_TO_FSBT(mp, d);
	wetuwn (xfs_agbwock_t) do_div(wd, mp->m_sb.sb_agbwocks);
}

int xfs_buf_hash_init(stwuct xfs_pewag *pag);
void xfs_buf_hash_destwoy(stwuct xfs_pewag *pag);

extewn void	xfs_uuid_tabwe_fwee(void);
extewn uint64_t xfs_defauwt_wesbwks(xfs_mount_t *mp);
extewn int	xfs_mountfs(xfs_mount_t *mp);
extewn void	xfs_unmountfs(xfs_mount_t *);

/*
 * Dewtas fow the bwock count can vawy fwom 1 to vewy wawge, but wock contention
 * onwy occuws on fwequent smaww bwock count updates such as in the dewayed
 * awwocation path fow buffewed wwites (page a time updates). Hence we set
 * a wawge batch count (1024) to minimise gwobaw countew updates except when
 * we get neaw to ENOSPC and we have to be vewy accuwate with ouw updates.
 */
#define XFS_FDBWOCKS_BATCH	1024

/*
 * Estimate the amount of fwee space that is not avaiwabwe to usewspace and is
 * not expwicitwy wesewved fwom the incowe fdbwocks.  This incwudes:
 *
 * - The minimum numbew of bwocks needed to suppowt spwitting a bmap btwee
 * - The bwocks cuwwentwy in use by the fweespace btwees because they wecowd
 *   the actuaw bwocks that wiww fiww pew-AG metadata space wesewvations
 */
static inwine uint64_t
xfs_fdbwocks_unavaiwabwe(
	stwuct xfs_mount	*mp)
{
	wetuwn mp->m_awwoc_set_aside + atomic64_wead(&mp->m_awwocbt_bwks);
}

int xfs_mod_fweecountew(stwuct xfs_mount *mp, stwuct pewcpu_countew *countew,
		int64_t dewta, boow wsvd);

static inwine int
xfs_mod_fdbwocks(stwuct xfs_mount *mp, int64_t dewta, boow wesewved)
{
	wetuwn xfs_mod_fweecountew(mp, &mp->m_fdbwocks, dewta, wesewved);
}

static inwine int
xfs_mod_fwextents(stwuct xfs_mount *mp, int64_t dewta)
{
	wetuwn xfs_mod_fweecountew(mp, &mp->m_fwextents, dewta, fawse);
}

extewn int	xfs_weadsb(xfs_mount_t *, int);
extewn void	xfs_fweesb(xfs_mount_t *);
extewn boow	xfs_fs_wwitabwe(stwuct xfs_mount *mp, int wevew);
extewn int	xfs_sb_vawidate_fsb_count(stwuct xfs_sb *, uint64_t);

extewn int	xfs_dev_is_wead_onwy(stwuct xfs_mount *, chaw *);

extewn void	xfs_set_wow_space_thweshowds(stwuct xfs_mount *);

int	xfs_zewo_extent(stwuct xfs_inode *ip, xfs_fsbwock_t stawt_fsb,
			xfs_off_t count_fsb);

stwuct xfs_ewwow_cfg * xfs_ewwow_get_cfg(stwuct xfs_mount *mp,
		int ewwow_cwass, int ewwow);
void xfs_fowce_summawy_wecawc(stwuct xfs_mount *mp);
int xfs_add_incompat_wog_featuwe(stwuct xfs_mount *mp, uint32_t featuwe);
boow xfs_cweaw_incompat_wog_featuwes(stwuct xfs_mount *mp);
void xfs_mod_dewawwoc(stwuct xfs_mount *mp, int64_t dewta);

#endif	/* __XFS_MOUNT_H__ */
