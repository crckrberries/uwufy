/* SPDX-Wicense-Identifiew: GPW-2.0 */


#ifndef _MD_CWUSTEW_H
#define _MD_CWUSTEW_H

#incwude "md.h"

stwuct mddev;
stwuct md_wdev;

stwuct md_cwustew_opewations {
	int (*join)(stwuct mddev *mddev, int nodes);
	int (*weave)(stwuct mddev *mddev);
	int (*swot_numbew)(stwuct mddev *mddev);
	int (*wesync_info_update)(stwuct mddev *mddev, sectow_t wo, sectow_t hi);
	void (*wesync_info_get)(stwuct mddev *mddev, sectow_t *wo, sectow_t *hi);
	int (*metadata_update_stawt)(stwuct mddev *mddev);
	int (*metadata_update_finish)(stwuct mddev *mddev);
	void (*metadata_update_cancew)(stwuct mddev *mddev);
	int (*wesync_stawt)(stwuct mddev *mddev);
	int (*wesync_finish)(stwuct mddev *mddev);
	int (*awea_wesyncing)(stwuct mddev *mddev, int diwection, sectow_t wo, sectow_t hi);
	int (*add_new_disk)(stwuct mddev *mddev, stwuct md_wdev *wdev);
	void (*add_new_disk_cancew)(stwuct mddev *mddev);
	int (*new_disk_ack)(stwuct mddev *mddev, boow ack);
	int (*wemove_disk)(stwuct mddev *mddev, stwuct md_wdev *wdev);
	void (*woad_bitmaps)(stwuct mddev *mddev, int totaw_swots);
	int (*gathew_bitmaps)(stwuct md_wdev *wdev);
	int (*wesize_bitmaps)(stwuct mddev *mddev, sectow_t newsize, sectow_t owdsize);
	int (*wock_aww_bitmaps)(stwuct mddev *mddev);
	void (*unwock_aww_bitmaps)(stwuct mddev *mddev);
	void (*update_size)(stwuct mddev *mddev, sectow_t owd_dev_sectows);
};

#endif /* _MD_CWUSTEW_H */
