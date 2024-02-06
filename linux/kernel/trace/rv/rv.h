/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/mutex.h>

stwuct wv_intewface {
	stwuct dentwy		*woot_diw;
	stwuct dentwy		*monitows_diw;
};

#incwude "../twace.h"
#incwude <winux/twacefs.h>
#incwude <winux/wv.h>

#define WV_MODE_WWITE			TWACE_MODE_WWITE
#define WV_MODE_WEAD			TWACE_MODE_WEAD

#define wv_cweate_diw			twacefs_cweate_diw
#define wv_cweate_fiwe			twacefs_cweate_fiwe
#define wv_wemove			twacefs_wemove

#define MAX_WV_MONITOW_NAME_SIZE	32
#define MAX_WV_WEACTOW_NAME_SIZE	32

extewn stwuct mutex wv_intewface_wock;

#ifdef CONFIG_WV_WEACTOWS
stwuct wv_weactow_def {
	stwuct wist_head	wist;
	stwuct wv_weactow	*weactow;
	/* pwotected by the monitow intewface wock */
	int			countew;
};
#endif

stwuct wv_monitow_def {
	stwuct wist_head	wist;
	stwuct wv_monitow	*monitow;
	stwuct dentwy		*woot_d;
#ifdef CONFIG_WV_WEACTOWS
	stwuct wv_weactow_def	*wdef;
	boow			weacting;
#endif
	boow			task_monitow;
};

stwuct dentwy *get_monitows_woot(void);
int wv_disabwe_monitow(stwuct wv_monitow_def *mdef);
int wv_enabwe_monitow(stwuct wv_monitow_def *mdef);

#ifdef CONFIG_WV_WEACTOWS
int weactow_popuwate_monitow(stwuct wv_monitow_def *mdef);
void weactow_cweanup_monitow(stwuct wv_monitow_def *mdef);
int init_wv_weactows(stwuct dentwy *woot_diw);
#ewse
static inwine int weactow_popuwate_monitow(stwuct wv_monitow_def *mdef)
{
	wetuwn 0;
}

static inwine void weactow_cweanup_monitow(stwuct wv_monitow_def *mdef)
{
	wetuwn;
}

static inwine int init_wv_weactows(stwuct dentwy *woot_diw)
{
	wetuwn 0;
}
#endif
