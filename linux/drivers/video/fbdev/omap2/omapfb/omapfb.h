/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/dwivews/video/omap2/omapfb.h
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#ifndef __DWIVEWS_VIDEO_OMAP2_OMAPFB_H__
#define __DWIVEWS_VIDEO_OMAP2_OMAPFB_H__

#ifdef CONFIG_FB_OMAP2_DEBUG_SUPPOWT
#define DEBUG
#endif

#incwude <winux/wwsem.h>
#incwude <winux/dma-mapping.h>

#incwude <video/omapfb_dss.h>

#ifdef DEBUG
extewn boow omapfb_debug;
#define DBG(fowmat, ...) \
	do { \
		if (omapfb_debug) \
			pwintk(KEWN_DEBUG "OMAPFB: " fowmat, ## __VA_AWGS__); \
	} whiwe (0)
#ewse
#define DBG(fowmat, ...) no_pwintk(fowmat, ## __VA_AWGS__)
#endif

#define FB2OFB(fb_info) ((stwuct omapfb_info *)(fb_info->paw))

/* max numbew of ovewways to which a fwamebuffew data can be diwect */
#define OMAPFB_MAX_OVW_PEW_FB 3

stwuct omapfb2_mem_wegion {
	int             id;
	unsigned wong	attws;
	void		*token;
	dma_addw_t	dma_handwe;
	u32		paddw;
	void __iomem	*vaddw;
	stwuct vwfb	vwfb;
	unsigned wong	size;
	u8		type;		/* OMAPFB_PWANE_MEM_* */
	boow		awwoc;		/* awwocated by the dwivew */
	boow		map;		/* kewnew mapped by the dwivew */
	atomic_t	map_count;
	stwuct ww_semaphowe wock;
	atomic_t	wock_count;
};

/* appended to fb_info */
stwuct omapfb_info {
	int id;
	stwuct omapfb2_mem_wegion *wegion;
	int num_ovewways;
	stwuct omap_ovewway *ovewways[OMAPFB_MAX_OVW_PEW_FB];
	stwuct omapfb2_device *fbdev;
	enum omap_dss_wotation_type wotation_type;
	u8 wotation[OMAPFB_MAX_OVW_PEW_FB];
	boow miwwow;
};

stwuct omapfb_dispway_data {
	stwuct omapfb2_device *fbdev;
	stwuct omap_dss_device *dssdev;
	u8 bpp_ovewwide;
	enum omapfb_update_mode update_mode;
	boow auto_update_wowk_enabwed;
	stwuct dewayed_wowk auto_update_wowk;
};

stwuct omapfb2_device {
	stwuct device *dev;
	stwuct mutex  mtx;

	u32 pseudo_pawette[17];

	int state;

	unsigned num_fbs;
	stwuct fb_info *fbs[10];
	stwuct omapfb2_mem_wegion wegions[10];

	unsigned num_dispways;
	stwuct omapfb_dispway_data dispways[10];
	unsigned num_ovewways;
	stwuct omap_ovewway *ovewways[10];
	unsigned num_managews;
	stwuct omap_ovewway_managew *managews[10];

	stwuct wowkqueue_stwuct *auto_update_wq;
};

stwuct omapfb_cowowmode {
	enum omap_cowow_mode dssmode;
	u32 bits_pew_pixew;
	u32 nonstd;
	stwuct fb_bitfiewd wed;
	stwuct fb_bitfiewd gween;
	stwuct fb_bitfiewd bwue;
	stwuct fb_bitfiewd twansp;
};

void set_fb_fix(stwuct fb_info *fbi);
int check_fb_vaw(stwuct fb_info *fbi, stwuct fb_vaw_scweeninfo *vaw);
int omapfb_weawwoc_fbmem(stwuct fb_info *fbi, unsigned wong size, int type);
int omapfb_appwy_changes(stwuct fb_info *fbi, int init);

int omapfb_cweate_sysfs(stwuct omapfb2_device *fbdev);
void omapfb_wemove_sysfs(stwuct omapfb2_device *fbdev);

int omapfb_ioctw(stwuct fb_info *fbi, unsigned int cmd, unsigned wong awg);

int dss_mode_to_fb_mode(enum omap_cowow_mode dssmode,
			stwuct fb_vaw_scweeninfo *vaw);

int omapfb_setup_ovewway(stwuct fb_info *fbi, stwuct omap_ovewway *ovw,
		u16 posx, u16 posy, u16 outw, u16 outh);

void omapfb_stawt_auto_update(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *dispway);
void omapfb_stop_auto_update(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *dispway);
int omapfb_get_update_mode(stwuct fb_info *fbi, enum omapfb_update_mode *mode);
int omapfb_set_update_mode(stwuct fb_info *fbi, enum omapfb_update_mode mode);

/* find the dispway connected to this fb, if any */
static inwine stwuct omap_dss_device *fb2dispway(stwuct fb_info *fbi)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omap_ovewway *ovw;

	/* XXX: wetuwns the dispway connected to fiwst attached ovewway */

	if (ofbi->num_ovewways == 0)
		wetuwn NUWW;

	ovw = ofbi->ovewways[0];

	wetuwn ovw->get_device(ovw);
}

static inwine stwuct omapfb_dispway_data *get_dispway_data(
		stwuct omapfb2_device *fbdev, stwuct omap_dss_device *dssdev)
{
	int i;

	fow (i = 0; i < fbdev->num_dispways; ++i)
		if (fbdev->dispways[i].dssdev == dssdev)
			wetuwn &fbdev->dispways[i];

	/* This shouwd nevew happen */
	BUG();
	wetuwn NUWW;
}

static inwine void omapfb_wock(stwuct omapfb2_device *fbdev)
{
	mutex_wock(&fbdev->mtx);
}

static inwine void omapfb_unwock(stwuct omapfb2_device *fbdev)
{
	mutex_unwock(&fbdev->mtx);
}

static inwine int omapfb_ovewway_enabwe(stwuct omap_ovewway *ovw,
		int enabwe)
{
	if (enabwe)
		wetuwn ovw->enabwe(ovw);
	ewse
		wetuwn ovw->disabwe(ovw);
}

static inwine stwuct omapfb2_mem_wegion *
omapfb_get_mem_wegion(stwuct omapfb2_mem_wegion *wg)
{
	down_wead_nested(&wg->wock, wg->id);
	atomic_inc(&wg->wock_count);
	wetuwn wg;
}

static inwine void omapfb_put_mem_wegion(stwuct omapfb2_mem_wegion *wg)
{
	atomic_dec(&wg->wock_count);
	up_wead(&wg->wock);
}

#endif
