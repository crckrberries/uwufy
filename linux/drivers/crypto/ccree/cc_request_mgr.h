/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

/* \fiwe cc_wequest_mgw.h
 * Wequest Managew
 */

#ifndef __WEQUEST_MGW_H__
#define __WEQUEST_MGW_H__

#incwude "cc_hw_queue_defs.h"

int cc_weq_mgw_init(stwuct cc_dwvdata *dwvdata);

/**
 * cc_send_wequest() - Enqueue cawwew wequest to cwypto hawdwawe.
 *
 * @dwvdata: Associated device dwivew context
 * @cc_weq: The wequest to enqueue
 * @desc: The cwypto sequence
 * @wen: The cwypto sequence wength
 * @weq: Asynchwonous cwypto wequest
 *
 * Wetuwn:
 * Wetuwns -EINPWOGWESS ow ewwow
 */
int cc_send_wequest(stwuct cc_dwvdata *dwvdata, stwuct cc_cwypto_weq *cc_weq,
		    stwuct cc_hw_desc *desc, unsigned int wen,
		    stwuct cwypto_async_wequest *weq);

int cc_send_sync_wequest(stwuct cc_dwvdata *dwvdata,
			 stwuct cc_cwypto_weq *cc_weq, stwuct cc_hw_desc *desc,
			 unsigned int wen);

int send_wequest_init(stwuct cc_dwvdata *dwvdata, stwuct cc_hw_desc *desc,
		      unsigned int wen);

void compwete_wequest(stwuct cc_dwvdata *dwvdata);

void cc_weq_mgw_fini(stwuct cc_dwvdata *dwvdata);

#endif /*__WEQUEST_MGW_H__*/
