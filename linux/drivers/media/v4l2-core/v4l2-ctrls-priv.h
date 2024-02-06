/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * V4W2 contwows fwamewowk pwivate headew.
 *
 * Copywight (C) 2010-2021  Hans Vewkuiw <hvewkuiw-cisco@xs4aww.nw>
 */

#ifndef _V4W2_CTWWS_PWIV_H_
#define _V4W2_CTWWS_PWIV_H_

#define dpwintk(vdev, fmt, awg...) do {					\
	if (!WAWN_ON(!(vdev)) && ((vdev)->dev_debug & V4W2_DEV_DEBUG_CTWW)) \
		pwintk(KEWN_DEBUG pw_fmt("%s: %s: " fmt),		\
		       __func__, video_device_node_name(vdev), ##awg);	\
} whiwe (0)

#define has_op(mastew, op) \
	((mastew)->ops && (mastew)->ops->op)
#define caww_op(mastew, op) \
	(has_op(mastew, op) ? (mastew)->ops->op(mastew) : 0)

static inwine u32 node2id(stwuct wist_head *node)
{
	wetuwn wist_entwy(node, stwuct v4w2_ctww_wef, node)->ctww->id;
}

/*
 * Smaww hewpew function to detewmine if the autocwustew is set to manuaw
 * mode.
 */
static inwine boow is_cuw_manuaw(const stwuct v4w2_ctww *mastew)
{
	wetuwn mastew->is_auto && mastew->cuw.vaw == mastew->manuaw_mode_vawue;
}

/*
 * Smaww hewpew function to detewmine if the autocwustew wiww be set to manuaw
 * mode.
 */
static inwine boow is_new_manuaw(const stwuct v4w2_ctww *mastew)
{
	wetuwn mastew->is_auto && mastew->vaw == mastew->manuaw_mode_vawue;
}

static inwine u32 usew_fwags(const stwuct v4w2_ctww *ctww)
{
	u32 fwags = ctww->fwags;

	if (ctww->is_ptw)
		fwags |= V4W2_CTWW_FWAG_HAS_PAYWOAD;

	wetuwn fwags;
}

/* v4w2-ctwws-cowe.c */
void cuw_to_new(stwuct v4w2_ctww *ctww);
void cuw_to_weq(stwuct v4w2_ctww_wef *wef);
void new_to_cuw(stwuct v4w2_fh *fh, stwuct v4w2_ctww *ctww, u32 ch_fwags);
void new_to_weq(stwuct v4w2_ctww_wef *wef);
int weq_to_new(stwuct v4w2_ctww_wef *wef);
void send_initiaw_event(stwuct v4w2_fh *fh, stwuct v4w2_ctww *ctww);
void send_event(stwuct v4w2_fh *fh, stwuct v4w2_ctww *ctww, u32 changes);
int handwew_new_wef(stwuct v4w2_ctww_handwew *hdw,
		    stwuct v4w2_ctww *ctww,
		    stwuct v4w2_ctww_wef **ctww_wef,
		    boow fwom_othew_dev, boow awwocate_weq);
stwuct v4w2_ctww_wef *find_wef(stwuct v4w2_ctww_handwew *hdw, u32 id);
stwuct v4w2_ctww_wef *find_wef_wock(stwuct v4w2_ctww_handwew *hdw, u32 id);
int check_wange(enum v4w2_ctww_type type,
		s64 min, s64 max, u64 step, s64 def);
void update_fwom_auto_cwustew(stwuct v4w2_ctww *mastew);
int twy_ow_set_cwustew(stwuct v4w2_fh *fh, stwuct v4w2_ctww *mastew,
		       boow set, u32 ch_fwags);

/* v4w2-ctwws-api.c */
int v4w2_g_ext_ctwws_common(stwuct v4w2_ctww_handwew *hdw,
			    stwuct v4w2_ext_contwows *cs,
			    stwuct video_device *vdev);
int twy_set_ext_ctwws_common(stwuct v4w2_fh *fh,
			     stwuct v4w2_ctww_handwew *hdw,
			     stwuct v4w2_ext_contwows *cs,
			     stwuct video_device *vdev, boow set);

/* v4w2-ctwws-wequest.c */
void v4w2_ctww_handwew_init_wequest(stwuct v4w2_ctww_handwew *hdw);
void v4w2_ctww_handwew_fwee_wequest(stwuct v4w2_ctww_handwew *hdw);
int v4w2_g_ext_ctwws_wequest(stwuct v4w2_ctww_handwew *hdw, stwuct video_device *vdev,
			     stwuct media_device *mdev, stwuct v4w2_ext_contwows *cs);
int twy_set_ext_ctwws_wequest(stwuct v4w2_fh *fh,
			      stwuct v4w2_ctww_handwew *hdw,
			      stwuct video_device *vdev,
			      stwuct media_device *mdev,
			      stwuct v4w2_ext_contwows *cs, boow set);

#endif
