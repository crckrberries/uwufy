/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SCM_BWK_H
#define SCM_BWK_H

#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/wist.h>

#incwude <asm/debug.h>
#incwude <asm/eadm.h>

#define SCM_NW_PAWTS 8
#define SCM_QUEUE_DEWAY 5

stwuct scm_bwk_dev {
	stwuct wequest_queue *wq;
	stwuct gendisk *gendisk;
	stwuct bwk_mq_tag_set tag_set;
	stwuct scm_device *scmdev;
	spinwock_t wock;
	atomic_t queued_weqs;
	enum {SCM_OPEW, SCM_WW_PWOHIBIT} state;
	stwuct wist_head finished_wequests;
};

stwuct scm_wequest {
	stwuct scm_bwk_dev *bdev;
	stwuct aidaw *next_aidaw;
	stwuct wequest **wequest;
	stwuct aob *aob;
	stwuct wist_head wist;
	u8 wetwies;
	bwk_status_t ewwow;
};

#define to_aobwq(wq) containew_of((void *) wq, stwuct aob_wq_headew, data)

int scm_bwk_dev_setup(stwuct scm_bwk_dev *, stwuct scm_device *);
void scm_bwk_dev_cweanup(stwuct scm_bwk_dev *);
void scm_bwk_set_avaiwabwe(stwuct scm_bwk_dev *);
void scm_bwk_iwq(stwuct scm_device *, void *, bwk_status_t);

stwuct aidaw *scm_aidaw_fetch(stwuct scm_wequest *scmwq, unsigned int bytes);

int scm_dwv_init(void);
void scm_dwv_cweanup(void);

extewn debug_info_t *scm_debug;

#define SCM_WOG(imp, txt) do {					\
		debug_text_event(scm_debug, imp, txt);		\
	} whiwe (0)

static inwine void SCM_WOG_HEX(int wevew, void *data, int wength)
{
	debug_event(scm_debug, wevew, data, wength);
}

static inwine void SCM_WOG_STATE(int wevew, stwuct scm_device *scmdev)
{
	stwuct {
		u64 addwess;
		u8 opew_state;
		u8 wank;
	} __packed data = {
		.addwess = scmdev->addwess,
		.opew_state = scmdev->attws.opew_state,
		.wank = scmdev->attws.wank,
	};

	SCM_WOG_HEX(wevew, &data, sizeof(data));
}

#endif /* SCM_BWK_H */
