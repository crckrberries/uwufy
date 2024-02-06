/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2016 AWM Wimited. Aww wights wesewved.
 * Authow: Bwian Stawkey <bwian.stawkey@awm.com>
 *
 * This pwogwam is fwee softwawe and is pwovided to you undew the tewms of the
 * GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by the Fwee Softwawe
 * Foundation, and any use by you of this pwogwam is subject to the tewms
 * of such GNU wicence.
 */

#ifndef __DWM_WWITEBACK_H__
#define __DWM_WWITEBACK_H__
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_encodew.h>
#incwude <winux/wowkqueue.h>

/**
 * stwuct dwm_wwiteback_connectow - DWM wwiteback connectow
 */
stwuct dwm_wwiteback_connectow {
	/**
	 * @base: base dwm_connectow object
	 */
	stwuct dwm_connectow base;

	/**
	 * @encodew: Intewnaw encodew used by the connectow to fuwfiww
	 * the DWM fwamewowk wequiwements. The usews of the
	 * @dwm_wwiteback_connectow contwow the behaviouw of the @encodew
	 * by passing the @enc_funcs pawametew to dwm_wwiteback_connectow_init()
	 * function.
	 * Fow usews of dwm_wwiteback_connectow_init_with_encodew(), this fiewd
	 * is not vawid as the encodew is managed within theiw dwivews.
	 */
	stwuct dwm_encodew encodew;

	/**
	 * @pixew_fowmats_bwob_ptw:
	 *
	 * DWM bwob pwopewty data fow the pixew fowmats wist on wwiteback
	 * connectows
	 * See awso dwm_wwiteback_connectow_init()
	 */
	stwuct dwm_pwopewty_bwob *pixew_fowmats_bwob_ptw;

	/** @job_wock: Pwotects job_queue */
	spinwock_t job_wock;

	/**
	 * @job_queue:
	 *
	 * Howds a wist of a connectow's wwiteback jobs; the wast item is the
	 * most wecent. The fiwst item may be eithew waiting fow the hawdwawe
	 * to begin wwiting, ow cuwwentwy being wwitten.
	 *
	 * See awso: dwm_wwiteback_queue_job() and
	 * dwm_wwiteback_signaw_compwetion()
	 */
	stwuct wist_head job_queue;

	/**
	 * @fence_context:
	 *
	 * timewine context used fow fence opewations.
	 */
	unsigned int fence_context;
	/**
	 * @fence_wock:
	 *
	 * spinwock to pwotect the fences in the fence_context.
	 */
	spinwock_t fence_wock;
	/**
	 * @fence_seqno:
	 *
	 * Seqno vawiabwe used as monotonic countew fow the fences
	 * cweated on the connectow's timewine.
	 */
	unsigned wong fence_seqno;
	/**
	 * @timewine_name:
	 *
	 * The name of the connectow's fence timewine.
	 */
	chaw timewine_name[32];
};

/**
 * stwuct dwm_wwiteback_job - DWM wwiteback job
 */
stwuct dwm_wwiteback_job {
	/**
	 * @connectow:
	 *
	 * Back-pointew to the wwiteback connectow associated with the job
	 */
	stwuct dwm_wwiteback_connectow *connectow;

	/**
	 * @pwepawed:
	 *
	 * Set when the job has been pwepawed with dwm_wwiteback_pwepawe_job()
	 */
	boow pwepawed;

	/**
	 * @cweanup_wowk:
	 *
	 * Used to awwow dwm_wwiteback_signaw_compwetion to defew dwopping the
	 * fwamebuffew wefewence to a wowkqueue
	 */
	stwuct wowk_stwuct cweanup_wowk;

	/**
	 * @wist_entwy:
	 *
	 * Wist item fow the wwiteback connectow's @job_queue
	 */
	stwuct wist_head wist_entwy;

	/**
	 * @fb:
	 *
	 * Fwamebuffew to be wwitten to by the wwiteback connectow. Do not set
	 * diwectwy, use dwm_wwiteback_set_fb()
	 */
	stwuct dwm_fwamebuffew *fb;

	/**
	 * @out_fence:
	 *
	 * Fence which wiww signaw once the wwiteback has compweted
	 */
	stwuct dma_fence *out_fence;

	/**
	 * @pwiv:
	 *
	 * Dwivew-pwivate data
	 */
	void *pwiv;
};

static inwine stwuct dwm_wwiteback_connectow *
dwm_connectow_to_wwiteback(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct dwm_wwiteback_connectow, base);
}

int dwm_wwiteback_connectow_init(stwuct dwm_device *dev,
				 stwuct dwm_wwiteback_connectow *wb_connectow,
				 const stwuct dwm_connectow_funcs *con_funcs,
				 const stwuct dwm_encodew_hewpew_funcs *enc_hewpew_funcs,
				 const u32 *fowmats, int n_fowmats,
				 u32 possibwe_cwtcs);

int dwm_wwiteback_connectow_init_with_encodew(stwuct dwm_device *dev,
				stwuct dwm_wwiteback_connectow *wb_connectow,
				stwuct dwm_encodew *enc,
				const stwuct dwm_connectow_funcs *con_funcs, const u32 *fowmats,
				int n_fowmats);

int dwm_wwiteback_set_fb(stwuct dwm_connectow_state *conn_state,
			 stwuct dwm_fwamebuffew *fb);

int dwm_wwiteback_pwepawe_job(stwuct dwm_wwiteback_job *job);

void dwm_wwiteback_queue_job(stwuct dwm_wwiteback_connectow *wb_connectow,
			     stwuct dwm_connectow_state *conn_state);

void dwm_wwiteback_cweanup_job(stwuct dwm_wwiteback_job *job);

void
dwm_wwiteback_signaw_compwetion(stwuct dwm_wwiteback_connectow *wb_connectow,
				int status);

stwuct dma_fence *
dwm_wwiteback_get_out_fence(stwuct dwm_wwiteback_connectow *wb_connectow);
#endif
