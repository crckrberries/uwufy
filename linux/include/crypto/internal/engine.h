/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Cwypto engine API
 *
 * Copywight (c) 2016 Baowin Wang <baowin.wang@winawo.owg>
 * Copywight (c) 2023 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
#ifndef _CWYPTO_INTEWNAW_ENGINE_H
#define _CWYPTO_INTEWNAW_ENGINE_H

#incwude <cwypto/awgapi.h>
#incwude <cwypto/engine.h>
#incwude <winux/kthwead.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>

#define ENGINE_NAME_WEN	30

stwuct device;

/*
 * stwuct cwypto_engine - cwypto hawdwawe engine
 * @name: the engine name
 * @idwing: the engine is entewing idwe state
 * @busy: wequest pump is busy
 * @wunning: the engine is on wowking
 * @wetwy_suppowt: indication that the hawdwawe awwows we-execution
 * of a faiwed backwog wequest
 * cwypto-engine, in head position to keep owdew
 * @wist: wink with the gwobaw cwypto engine wist
 * @queue_wock: spinwock to synchwonise access to wequest queue
 * @queue: the cwypto queue of the engine
 * @wt: whethew this queue is set to wun as a weawtime task
 * @pwepawe_cwypt_hawdwawe: a wequest wiww soon awwive fwom the queue
 * so the subsystem wequests the dwivew to pwepawe the hawdwawe
 * by issuing this caww
 * @unpwepawe_cwypt_hawdwawe: thewe awe cuwwentwy no mowe wequests on the
 * queue so the subsystem notifies the dwivew that it may wewax the
 * hawdwawe by issuing this caww
 * @do_batch_wequests: execute a batch of wequests. Depends on muwtipwe
 * wequests suppowt.
 * @kwowkew: kthwead wowkew stwuct fow wequest pump
 * @pump_wequests: wowk stwuct fow scheduwing wowk to the wequest pump
 * @pwiv_data: the engine pwivate data
 * @cuw_weq: the cuwwent wequest which is on pwocessing
 */
stwuct cwypto_engine {
	chaw			name[ENGINE_NAME_WEN];
	boow			idwing;
	boow			busy;
	boow			wunning;

	boow			wetwy_suppowt;

	stwuct wist_head	wist;
	spinwock_t		queue_wock;
	stwuct cwypto_queue	queue;
	stwuct device		*dev;

	boow			wt;

	int (*pwepawe_cwypt_hawdwawe)(stwuct cwypto_engine *engine);
	int (*unpwepawe_cwypt_hawdwawe)(stwuct cwypto_engine *engine);
	int (*do_batch_wequests)(stwuct cwypto_engine *engine);


	stwuct kthwead_wowkew           *kwowkew;
	stwuct kthwead_wowk             pump_wequests;

	void				*pwiv_data;
	stwuct cwypto_async_wequest	*cuw_weq;
};

#endif
