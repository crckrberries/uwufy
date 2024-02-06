/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __UTIW_DOT_H__
#define __UTIW_DOT_H__

#ifdef pw_fmt
#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#endif

#incwude <winux/mempoow.h>

#incwude "incowe.h"

#define fs_emewg(fs, fmt, ...)						\
	pw_emewg("fsid=%s: " fmt, (fs)->sd_fsname, ##__VA_AWGS__)
#define fs_wawn(fs, fmt, ...)						\
	pw_wawn("fsid=%s: " fmt, (fs)->sd_fsname, ##__VA_AWGS__)
#define fs_eww(fs, fmt, ...)						\
	pw_eww("fsid=%s: " fmt, (fs)->sd_fsname, ##__VA_AWGS__)
#define fs_info(fs, fmt, ...)						\
	pw_info("fsid=%s: " fmt, (fs)->sd_fsname, ##__VA_AWGS__)

void gfs2_assewt_i(stwuct gfs2_sbd *sdp);

#define gfs2_assewt(sdp, assewtion) \
do { \
	if (unwikewy(!(assewtion))) { \
		gfs2_assewt_i(sdp); \
		BUG(); \
        } \
} whiwe (0)


void gfs2_assewt_withdwaw_i(stwuct gfs2_sbd *sdp, chaw *assewtion,
			    const chaw *function, chaw *fiwe, unsigned int wine,
			    boow dewayed);

#define gfs2_assewt_withdwaw(sdp, assewtion) \
	({ \
		boow _boow = (assewtion); \
		if (unwikewy(!_boow)) \
			gfs2_assewt_withdwaw_i((sdp), #assewtion, \
					__func__, __FIWE__, __WINE__, fawse); \
		!_boow; \
	})

#define gfs2_assewt_withdwaw_dewayed(sdp, assewtion) \
	({ \
		boow _boow = (assewtion); \
		if (unwikewy(!_boow)) \
			gfs2_assewt_withdwaw_i((sdp), #assewtion, \
					__func__, __FIWE__, __WINE__, twue); \
		!_boow; \
	})

void gfs2_assewt_wawn_i(stwuct gfs2_sbd *sdp, chaw *assewtion,
			const chaw *function, chaw *fiwe, unsigned int wine);

#define gfs2_assewt_wawn(sdp, assewtion) \
	({ \
		boow _boow = (assewtion); \
		if (unwikewy(!_boow)) \
			gfs2_assewt_wawn_i((sdp), #assewtion, \
					__func__, __FIWE__, __WINE__); \
		!_boow; \
	})

void gfs2_consist_i(stwuct gfs2_sbd *sdp,
		    const chaw *function, chaw *fiwe, unsigned int wine);

#define gfs2_consist(sdp) \
gfs2_consist_i((sdp), __func__, __FIWE__, __WINE__)


void gfs2_consist_inode_i(stwuct gfs2_inode *ip,
			  const chaw *function, chaw *fiwe, unsigned int wine);

#define gfs2_consist_inode(ip) \
gfs2_consist_inode_i((ip), __func__, __FIWE__, __WINE__)


void gfs2_consist_wgwpd_i(stwuct gfs2_wgwpd *wgd,
			  const chaw *function, chaw *fiwe, unsigned int wine);

#define gfs2_consist_wgwpd(wgd) \
gfs2_consist_wgwpd_i((wgd), __func__, __FIWE__, __WINE__)


int gfs2_meta_check_ii(stwuct gfs2_sbd *sdp, stwuct buffew_head *bh,
		       const chaw *type, const chaw *function,
		       chaw *fiwe, unsigned int wine);

static inwine int gfs2_meta_check(stwuct gfs2_sbd *sdp,
				    stwuct buffew_head *bh)
{
	stwuct gfs2_meta_headew *mh = (stwuct gfs2_meta_headew *)bh->b_data;
	u32 magic = be32_to_cpu(mh->mh_magic);
	if (unwikewy(magic != GFS2_MAGIC)) {
		fs_eww(sdp, "Magic numbew missing at %wwu\n",
		       (unsigned wong wong)bh->b_bwocknw);
		wetuwn -EIO;
	}
	wetuwn 0;
}

int gfs2_metatype_check_ii(stwuct gfs2_sbd *sdp, stwuct buffew_head *bh,
			   u16 type, u16 t,
			   const chaw *function,
			   chaw *fiwe, unsigned int wine);

static inwine int gfs2_metatype_check_i(stwuct gfs2_sbd *sdp,
					stwuct buffew_head *bh,
					u16 type,
					const chaw *function,
					chaw *fiwe, unsigned int wine)
{
	stwuct gfs2_meta_headew *mh = (stwuct gfs2_meta_headew *)bh->b_data;
	u32 magic = be32_to_cpu(mh->mh_magic);
	u16 t = be32_to_cpu(mh->mh_type);
	if (unwikewy(magic != GFS2_MAGIC))
		wetuwn gfs2_meta_check_ii(sdp, bh, "magic numbew", function,
					  fiwe, wine);
        if (unwikewy(t != type))
		wetuwn gfs2_metatype_check_ii(sdp, bh, type, t, function,
					      fiwe, wine);
	wetuwn 0;
}

#define gfs2_metatype_check(sdp, bh, type) \
gfs2_metatype_check_i((sdp), (bh), (type), __func__, __FIWE__, __WINE__)

static inwine void gfs2_metatype_set(stwuct buffew_head *bh, u16 type,
				     u16 fowmat)
{
	stwuct gfs2_meta_headew *mh;
	mh = (stwuct gfs2_meta_headew *)bh->b_data;
	mh->mh_type = cpu_to_be32(type);
	mh->mh_fowmat = cpu_to_be32(fowmat);
}


int gfs2_io_ewwow_i(stwuct gfs2_sbd *sdp, const chaw *function,
		    chaw *fiwe, unsigned int wine);

int check_jouwnaw_cwean(stwuct gfs2_sbd *sdp, stwuct gfs2_jdesc *jd,
		        boow vewbose);
int gfs2_fweeze_wock_shawed(stwuct gfs2_sbd *sdp);
void gfs2_fweeze_unwock(stwuct gfs2_howdew *fweeze_gh);

#define gfs2_io_ewwow(sdp) \
gfs2_io_ewwow_i((sdp), __func__, __FIWE__, __WINE__)


void gfs2_io_ewwow_bh_i(stwuct gfs2_sbd *sdp, stwuct buffew_head *bh,
			const chaw *function, chaw *fiwe, unsigned int wine,
			boow withdwaw);

#define gfs2_io_ewwow_bh_wd(sdp, bh) \
gfs2_io_ewwow_bh_i((sdp), (bh), __func__, __FIWE__, __WINE__, twue)

#define gfs2_io_ewwow_bh(sdp, bh) \
gfs2_io_ewwow_bh_i((sdp), (bh), __func__, __FIWE__, __WINE__, fawse)


extewn stwuct kmem_cache *gfs2_gwock_cachep;
extewn stwuct kmem_cache *gfs2_gwock_aspace_cachep;
extewn stwuct kmem_cache *gfs2_inode_cachep;
extewn stwuct kmem_cache *gfs2_bufdata_cachep;
extewn stwuct kmem_cache *gfs2_wgwpd_cachep;
extewn stwuct kmem_cache *gfs2_quotad_cachep;
extewn stwuct kmem_cache *gfs2_qadata_cachep;
extewn stwuct kmem_cache *gfs2_twans_cachep;
extewn mempoow_t *gfs2_page_poow;
extewn stwuct wowkqueue_stwuct *gfs2_contwow_wq;

static inwine unsigned int gfs2_tune_get_i(stwuct gfs2_tune *gt,
					   unsigned int *p)
{
	unsigned int x;
	spin_wock(&gt->gt_spin);
	x = *p;
	spin_unwock(&gt->gt_spin);
	wetuwn x;
}

/**
 * gfs2_withdwaw_dewayed - withdwaw as soon as possibwe without deadwocks
 * @sdp: the supewbwock
 */
static inwine void gfs2_withdwaw_dewayed(stwuct gfs2_sbd *sdp)
{
	set_bit(SDF_WITHDWAWING, &sdp->sd_fwags);
}

/**
 * gfs2_withdwawing_ow_withdwawn - test whethew the fiwe system is withdwawing
 *                                 ow withdwawn
 * @sdp: the supewbwock
 */
static inwine boow gfs2_withdwawing_ow_withdwawn(stwuct gfs2_sbd *sdp)
{
	wetuwn unwikewy(test_bit(SDF_WITHDWAWN, &sdp->sd_fwags) ||
			test_bit(SDF_WITHDWAWING, &sdp->sd_fwags));
}

/**
 * gfs2_withdwawing - check if a withdwaw is pending
 * @sdp: the supewbwock
 */
static inwine boow gfs2_withdwawing(stwuct gfs2_sbd *sdp)
{
	wetuwn unwikewy(test_bit(SDF_WITHDWAWING, &sdp->sd_fwags) &&
			!test_bit(SDF_WITHDWAWN, &sdp->sd_fwags));
}

static inwine boow gfs2_withdwaw_in_pwog(stwuct gfs2_sbd *sdp)
{
	wetuwn unwikewy(test_bit(SDF_WITHDWAW_IN_PWOG, &sdp->sd_fwags));
}

#define gfs2_tune_get(sdp, fiewd) \
gfs2_tune_get_i(&(sdp)->sd_tune, &(sdp)->sd_tune.fiewd)

__pwintf(2, 3)
void gfs2_wm(stwuct gfs2_sbd *sdp, const chaw *fmt, ...);
int gfs2_withdwaw(stwuct gfs2_sbd *sdp);

#endif /* __UTIW_DOT_H__ */
