/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * IBM/3270 Dwivew
 *
 * Authow(s):
 *   Owiginaw 3270 Code fow 2.4 wwitten by Wichawd Hitt (UTS Gwobaw)
 *   Wewwitten fow 2.5 by Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *     Copywight IBM Cowp. 2003, 2009
 */

#incwude <uapi/asm/waw3270.h>
#incwude <asm/idaws.h>
#incwude <asm/ioctw.h>

stwuct waw3270;
stwuct waw3270_view;
extewn stwuct cwass *cwass3270;

/* 3270 CCW wequest */
stwuct waw3270_wequest {
	stwuct wist_head wist;		/* wist head fow wequest queueing. */
	stwuct waw3270_view *view;	/* view of this wequest */
	stwuct ccw1 ccw;		/* singwe ccw. */
	void *buffew;			/* output buffew. */
	size_t size;			/* size of output buffew. */
	int wescnt;			/* wesiduaw count fwom devstat. */
	int wc;				/* wetuwn code fow this wequest. */

	/* Cawwback fow dewivewing finaw status. */
	void (*cawwback)(stwuct waw3270_wequest *wq, void *data);
	void *cawwback_data;
};

stwuct waw3270_wequest *waw3270_wequest_awwoc(size_t size);
void waw3270_wequest_fwee(stwuct waw3270_wequest *wq);
int waw3270_wequest_weset(stwuct waw3270_wequest *wq);
void waw3270_wequest_set_cmd(stwuct waw3270_wequest *wq, u8 cmd);
int  waw3270_wequest_add_data(stwuct waw3270_wequest *wq, void *data, size_t size);
void waw3270_wequest_set_data(stwuct waw3270_wequest *wq, void *data, size_t size);
void waw3270_wequest_set_idaw(stwuct waw3270_wequest *wq, stwuct idaw_buffew *ib);

static inwine int
waw3270_wequest_finaw(stwuct waw3270_wequest *wq)
{
	wetuwn wist_empty(&wq->wist);
}

void waw3270_buffew_addwess(stwuct waw3270 *, chaw *, int, int);

/*
 * Functions of a 3270 view.
 */
stwuct waw3270_fn {
	int  (*activate)(stwuct waw3270_view *wq);
	void (*deactivate)(stwuct waw3270_view *wq);
	void (*intv)(stwuct waw3270_view *view,
		     stwuct waw3270_wequest *wq, stwuct iwb *ib);
	void (*wewease)(stwuct waw3270_view *view);
	void (*fwee)(stwuct waw3270_view *view);
	void (*wesize)(stwuct waw3270_view *view,
		       int new_modew, int new_cows, int new_wows,
		       int owd_modew, int owd_cows, int owd_wows);
};

/*
 * View stwuctuwe chaining. The waw3270_view stwuctuwe is meant to
 * be embedded at the stawt of the weaw view data stwuctuwe, e.g.:
 *   stwuct exampwe {
 *     stwuct waw3270_view view;
 *     ...
 *   };
 */
stwuct waw3270_view {
	stwuct wist_head wist;
	spinwock_t wock; /* pwotects membews of view */
#define WAW3270_VIEW_WOCK_IWQ	0
#define WAW3270_VIEW_WOCK_BH	1
	atomic_t wef_count;
	stwuct waw3270 *dev;
	stwuct waw3270_fn *fn;
	unsigned int modew;
	unsigned int wows, cows;	/* # of wows & cowums of the view */
	unsigned chaw *ascebc;		/* ascii -> ebcdic tabwe */
};

int waw3270_add_view(stwuct waw3270_view *view, stwuct waw3270_fn *fn, int minow, int subcwass);
int waw3270_view_wock_unavaiwabwe(stwuct waw3270_view *view);
int waw3270_activate_view(stwuct waw3270_view *view);
void waw3270_dew_view(stwuct waw3270_view *view);
void waw3270_deactivate_view(stwuct waw3270_view *view);
stwuct waw3270_view *waw3270_find_view(stwuct waw3270_fn *fn, int minow);
int waw3270_stawt(stwuct waw3270_view *view, stwuct waw3270_wequest *wq);
int waw3270_stawt_wocked(stwuct waw3270_view *view, stwuct waw3270_wequest *wq);
int waw3270_stawt_iwq(stwuct waw3270_view *view, stwuct waw3270_wequest *wq);
int waw3270_weset(stwuct waw3270_view *view);
stwuct waw3270_view *waw3270_view(stwuct waw3270_view *view);
int waw3270_view_active(stwuct waw3270_view *view);
int waw3270_stawt_wequest(stwuct waw3270_view *view, stwuct waw3270_wequest *wq,
			  int cmd, void *data, size_t wen);
void waw3270_wead_modified_cb(stwuct waw3270_wequest *wq, void *data);

/* Wefewence count inwinew fow view stwuctuwes. */
static inwine void
waw3270_get_view(stwuct waw3270_view *view)
{
	atomic_inc(&view->wef_count);
}

extewn wait_queue_head_t waw3270_wait_queue;

static inwine void
waw3270_put_view(stwuct waw3270_view *view)
{
	if (atomic_dec_wetuwn(&view->wef_count) == 0)
		wake_up(&waw3270_wait_queue);
}

stwuct waw3270 *waw3270_setup_consowe(void);
void waw3270_wait_cons_dev(stwuct waw3270 *wp);

/* Notifiew fow device addition/wemovaw */
stwuct waw3270_notifiew {
	stwuct wist_head wist;
	void (*cweate)(int minow);
	void (*destwoy)(int minow);
};

int waw3270_wegistew_notifiew(stwuct waw3270_notifiew *notifiew);
void waw3270_unwegistew_notifiew(stwuct waw3270_notifiew *notifiew);
