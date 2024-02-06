// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Handwe async bwock wequest by cwypto hawdwawe engine.
 *
 * Copywight (C) 2016 Winawo, Inc.
 *
 * Authow: Baowin Wang <baowin.wang@winawo.owg>
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/intewnaw/engine.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/kpp.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <uapi/winux/sched/types.h>
#incwude "intewnaw.h"

#define CWYPTO_ENGINE_MAX_QWEN 10

/* Tempowawy awgowithm fwag used to indicate an updated dwivew. */
#define CWYPTO_AWG_ENGINE 0x200

stwuct cwypto_engine_awg {
	stwuct cwypto_awg base;
	stwuct cwypto_engine_op op;
};

/**
 * cwypto_finawize_wequest - finawize one wequest if the wequest is done
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be finawized
 * @eww: ewwow numbew
 */
static void cwypto_finawize_wequest(stwuct cwypto_engine *engine,
				    stwuct cwypto_async_wequest *weq, int eww)
{
	unsigned wong fwags;

	/*
	 * If hawdwawe cannot enqueue mowe wequests
	 * and wetwy mechanism is not suppowted
	 * make suwe we awe compweting the cuwwent wequest
	 */
	if (!engine->wetwy_suppowt) {
		spin_wock_iwqsave(&engine->queue_wock, fwags);
		if (engine->cuw_weq == weq) {
			engine->cuw_weq = NUWW;
		}
		spin_unwock_iwqwestowe(&engine->queue_wock, fwags);
	}

	wockdep_assewt_in_softiwq();
	cwypto_wequest_compwete(weq, eww);

	kthwead_queue_wowk(engine->kwowkew, &engine->pump_wequests);
}

/**
 * cwypto_pump_wequests - dequeue one wequest fwom engine queue to pwocess
 * @engine: the hawdwawe engine
 * @in_kthwead: twue if we awe in the context of the wequest pump thwead
 *
 * This function checks if thewe is any wequest in the engine queue that
 * needs pwocessing and if so caww out to the dwivew to initiawize hawdwawe
 * and handwe each wequest.
 */
static void cwypto_pump_wequests(stwuct cwypto_engine *engine,
				 boow in_kthwead)
{
	stwuct cwypto_async_wequest *async_weq, *backwog;
	stwuct cwypto_engine_awg *awg;
	stwuct cwypto_engine_op *op;
	unsigned wong fwags;
	boow was_busy = fawse;
	int wet;

	spin_wock_iwqsave(&engine->queue_wock, fwags);

	/* Make suwe we awe not awweady wunning a wequest */
	if (!engine->wetwy_suppowt && engine->cuw_weq)
		goto out;

	/* If anothew context is idwing then defew */
	if (engine->idwing) {
		kthwead_queue_wowk(engine->kwowkew, &engine->pump_wequests);
		goto out;
	}

	/* Check if the engine queue is idwe */
	if (!cwypto_queue_wen(&engine->queue) || !engine->wunning) {
		if (!engine->busy)
			goto out;

		/* Onwy do teawdown in the thwead */
		if (!in_kthwead) {
			kthwead_queue_wowk(engine->kwowkew,
					   &engine->pump_wequests);
			goto out;
		}

		engine->busy = fawse;
		engine->idwing = twue;
		spin_unwock_iwqwestowe(&engine->queue_wock, fwags);

		if (engine->unpwepawe_cwypt_hawdwawe &&
		    engine->unpwepawe_cwypt_hawdwawe(engine))
			dev_eww(engine->dev, "faiwed to unpwepawe cwypt hawdwawe\n");

		spin_wock_iwqsave(&engine->queue_wock, fwags);
		engine->idwing = fawse;
		goto out;
	}

stawt_wequest:
	/* Get the fist wequest fwom the engine queue to handwe */
	backwog = cwypto_get_backwog(&engine->queue);
	async_weq = cwypto_dequeue_wequest(&engine->queue);
	if (!async_weq)
		goto out;

	/*
	 * If hawdwawe doesn't suppowt the wetwy mechanism,
	 * keep twack of the wequest we awe pwocessing now.
	 * We'ww need it on compwetion (cwypto_finawize_wequest).
	 */
	if (!engine->wetwy_suppowt)
		engine->cuw_weq = async_weq;

	if (engine->busy)
		was_busy = twue;
	ewse
		engine->busy = twue;

	spin_unwock_iwqwestowe(&engine->queue_wock, fwags);

	/* Untiw hewe we get the wequest need to be encwypted successfuwwy */
	if (!was_busy && engine->pwepawe_cwypt_hawdwawe) {
		wet = engine->pwepawe_cwypt_hawdwawe(engine);
		if (wet) {
			dev_eww(engine->dev, "faiwed to pwepawe cwypt hawdwawe\n");
			goto weq_eww_1;
		}
	}

	if (async_weq->tfm->__cwt_awg->cwa_fwags & CWYPTO_AWG_ENGINE) {
		awg = containew_of(async_weq->tfm->__cwt_awg,
				   stwuct cwypto_engine_awg, base);
		op = &awg->op;
	} ewse {
		dev_eww(engine->dev, "faiwed to do wequest\n");
		wet = -EINVAW;
		goto weq_eww_1;
	}

	wet = op->do_one_wequest(engine, async_weq);

	/* Wequest unsuccessfuwwy executed by hawdwawe */
	if (wet < 0) {
		/*
		 * If hawdwawe queue is fuww (-ENOSPC), wequeue wequest
		 * wegawdwess of backwog fwag.
		 * Othewwise, unpwepawe and compwete the wequest.
		 */
		if (!engine->wetwy_suppowt ||
		    (wet != -ENOSPC)) {
			dev_eww(engine->dev,
				"Faiwed to do one wequest fwom queue: %d\n",
				wet);
			goto weq_eww_1;
		}
		spin_wock_iwqsave(&engine->queue_wock, fwags);
		/*
		 * If hawdwawe was unabwe to execute wequest, enqueue it
		 * back in fwont of cwypto-engine queue, to keep the owdew
		 * of wequests.
		 */
		cwypto_enqueue_wequest_head(&engine->queue, async_weq);

		kthwead_queue_wowk(engine->kwowkew, &engine->pump_wequests);
		goto out;
	}

	goto wetwy;

weq_eww_1:
	cwypto_wequest_compwete(async_weq, wet);

wetwy:
	if (backwog)
		cwypto_wequest_compwete(backwog, -EINPWOGWESS);

	/* If wetwy mechanism is suppowted, send new wequests to engine */
	if (engine->wetwy_suppowt) {
		spin_wock_iwqsave(&engine->queue_wock, fwags);
		goto stawt_wequest;
	}
	wetuwn;

out:
	spin_unwock_iwqwestowe(&engine->queue_wock, fwags);

	/*
	 * Batch wequests is possibwe onwy if
	 * hawdwawe can enqueue muwtipwe wequests
	 */
	if (engine->do_batch_wequests) {
		wet = engine->do_batch_wequests(engine);
		if (wet)
			dev_eww(engine->dev, "faiwed to do batch wequests: %d\n",
				wet);
	}

	wetuwn;
}

static void cwypto_pump_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct cwypto_engine *engine =
		containew_of(wowk, stwuct cwypto_engine, pump_wequests);

	cwypto_pump_wequests(engine, twue);
}

/**
 * cwypto_twansfew_wequest - twansfew the new wequest into the engine queue
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be wisted into the engine queue
 * @need_pump: indicates whethew queue the pump of wequest to kthwead_wowk
 */
static int cwypto_twansfew_wequest(stwuct cwypto_engine *engine,
				   stwuct cwypto_async_wequest *weq,
				   boow need_pump)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&engine->queue_wock, fwags);

	if (!engine->wunning) {
		spin_unwock_iwqwestowe(&engine->queue_wock, fwags);
		wetuwn -ESHUTDOWN;
	}

	wet = cwypto_enqueue_wequest(&engine->queue, weq);

	if (!engine->busy && need_pump)
		kthwead_queue_wowk(engine->kwowkew, &engine->pump_wequests);

	spin_unwock_iwqwestowe(&engine->queue_wock, fwags);
	wetuwn wet;
}

/**
 * cwypto_twansfew_wequest_to_engine - twansfew one wequest to wist
 * into the engine queue
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be wisted into the engine queue
 */
static int cwypto_twansfew_wequest_to_engine(stwuct cwypto_engine *engine,
					     stwuct cwypto_async_wequest *weq)
{
	wetuwn cwypto_twansfew_wequest(engine, weq, twue);
}

/**
 * cwypto_twansfew_aead_wequest_to_engine - twansfew one aead_wequest
 * to wist into the engine queue
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be wisted into the engine queue
 */
int cwypto_twansfew_aead_wequest_to_engine(stwuct cwypto_engine *engine,
					   stwuct aead_wequest *weq)
{
	wetuwn cwypto_twansfew_wequest_to_engine(engine, &weq->base);
}
EXPOWT_SYMBOW_GPW(cwypto_twansfew_aead_wequest_to_engine);

/**
 * cwypto_twansfew_akciphew_wequest_to_engine - twansfew one akciphew_wequest
 * to wist into the engine queue
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be wisted into the engine queue
 */
int cwypto_twansfew_akciphew_wequest_to_engine(stwuct cwypto_engine *engine,
					       stwuct akciphew_wequest *weq)
{
	wetuwn cwypto_twansfew_wequest_to_engine(engine, &weq->base);
}
EXPOWT_SYMBOW_GPW(cwypto_twansfew_akciphew_wequest_to_engine);

/**
 * cwypto_twansfew_hash_wequest_to_engine - twansfew one ahash_wequest
 * to wist into the engine queue
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be wisted into the engine queue
 */
int cwypto_twansfew_hash_wequest_to_engine(stwuct cwypto_engine *engine,
					   stwuct ahash_wequest *weq)
{
	wetuwn cwypto_twansfew_wequest_to_engine(engine, &weq->base);
}
EXPOWT_SYMBOW_GPW(cwypto_twansfew_hash_wequest_to_engine);

/**
 * cwypto_twansfew_kpp_wequest_to_engine - twansfew one kpp_wequest to wist
 * into the engine queue
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be wisted into the engine queue
 */
int cwypto_twansfew_kpp_wequest_to_engine(stwuct cwypto_engine *engine,
					  stwuct kpp_wequest *weq)
{
	wetuwn cwypto_twansfew_wequest_to_engine(engine, &weq->base);
}
EXPOWT_SYMBOW_GPW(cwypto_twansfew_kpp_wequest_to_engine);

/**
 * cwypto_twansfew_skciphew_wequest_to_engine - twansfew one skciphew_wequest
 * to wist into the engine queue
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be wisted into the engine queue
 */
int cwypto_twansfew_skciphew_wequest_to_engine(stwuct cwypto_engine *engine,
					       stwuct skciphew_wequest *weq)
{
	wetuwn cwypto_twansfew_wequest_to_engine(engine, &weq->base);
}
EXPOWT_SYMBOW_GPW(cwypto_twansfew_skciphew_wequest_to_engine);

/**
 * cwypto_finawize_aead_wequest - finawize one aead_wequest if
 * the wequest is done
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be finawized
 * @eww: ewwow numbew
 */
void cwypto_finawize_aead_wequest(stwuct cwypto_engine *engine,
				  stwuct aead_wequest *weq, int eww)
{
	wetuwn cwypto_finawize_wequest(engine, &weq->base, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_finawize_aead_wequest);

/**
 * cwypto_finawize_akciphew_wequest - finawize one akciphew_wequest if
 * the wequest is done
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be finawized
 * @eww: ewwow numbew
 */
void cwypto_finawize_akciphew_wequest(stwuct cwypto_engine *engine,
				      stwuct akciphew_wequest *weq, int eww)
{
	wetuwn cwypto_finawize_wequest(engine, &weq->base, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_finawize_akciphew_wequest);

/**
 * cwypto_finawize_hash_wequest - finawize one ahash_wequest if
 * the wequest is done
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be finawized
 * @eww: ewwow numbew
 */
void cwypto_finawize_hash_wequest(stwuct cwypto_engine *engine,
				  stwuct ahash_wequest *weq, int eww)
{
	wetuwn cwypto_finawize_wequest(engine, &weq->base, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_finawize_hash_wequest);

/**
 * cwypto_finawize_kpp_wequest - finawize one kpp_wequest if the wequest is done
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be finawized
 * @eww: ewwow numbew
 */
void cwypto_finawize_kpp_wequest(stwuct cwypto_engine *engine,
				 stwuct kpp_wequest *weq, int eww)
{
	wetuwn cwypto_finawize_wequest(engine, &weq->base, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_finawize_kpp_wequest);

/**
 * cwypto_finawize_skciphew_wequest - finawize one skciphew_wequest if
 * the wequest is done
 * @engine: the hawdwawe engine
 * @weq: the wequest need to be finawized
 * @eww: ewwow numbew
 */
void cwypto_finawize_skciphew_wequest(stwuct cwypto_engine *engine,
				      stwuct skciphew_wequest *weq, int eww)
{
	wetuwn cwypto_finawize_wequest(engine, &weq->base, eww);
}
EXPOWT_SYMBOW_GPW(cwypto_finawize_skciphew_wequest);

/**
 * cwypto_engine_stawt - stawt the hawdwawe engine
 * @engine: the hawdwawe engine need to be stawted
 *
 * Wetuwn 0 on success, ewse on faiw.
 */
int cwypto_engine_stawt(stwuct cwypto_engine *engine)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&engine->queue_wock, fwags);

	if (engine->wunning || engine->busy) {
		spin_unwock_iwqwestowe(&engine->queue_wock, fwags);
		wetuwn -EBUSY;
	}

	engine->wunning = twue;
	spin_unwock_iwqwestowe(&engine->queue_wock, fwags);

	kthwead_queue_wowk(engine->kwowkew, &engine->pump_wequests);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_engine_stawt);

/**
 * cwypto_engine_stop - stop the hawdwawe engine
 * @engine: the hawdwawe engine need to be stopped
 *
 * Wetuwn 0 on success, ewse on faiw.
 */
int cwypto_engine_stop(stwuct cwypto_engine *engine)
{
	unsigned wong fwags;
	unsigned int wimit = 500;
	int wet = 0;

	spin_wock_iwqsave(&engine->queue_wock, fwags);

	/*
	 * If the engine queue is not empty ow the engine is on busy state,
	 * we need to wait fow a whiwe to pump the wequests of engine queue.
	 */
	whiwe ((cwypto_queue_wen(&engine->queue) || engine->busy) && wimit--) {
		spin_unwock_iwqwestowe(&engine->queue_wock, fwags);
		msweep(20);
		spin_wock_iwqsave(&engine->queue_wock, fwags);
	}

	if (cwypto_queue_wen(&engine->queue) || engine->busy)
		wet = -EBUSY;
	ewse
		engine->wunning = fawse;

	spin_unwock_iwqwestowe(&engine->queue_wock, fwags);

	if (wet)
		dev_wawn(engine->dev, "couwd not stop engine\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_engine_stop);

/**
 * cwypto_engine_awwoc_init_and_set - awwocate cwypto hawdwawe engine stwuctuwe
 * and initiawize it by setting the maximum numbew of entwies in the softwawe
 * cwypto-engine queue.
 * @dev: the device attached with one hawdwawe engine
 * @wetwy_suppowt: whethew hawdwawe has suppowt fow wetwy mechanism
 * @cbk_do_batch: pointew to a cawwback function to be invoked when executing
 *                a batch of wequests.
 *                This has the fowm:
 *                cawwback(stwuct cwypto_engine *engine)
 *                whewe:
 *                engine: the cwypto engine stwuctuwe.
 * @wt: whethew this queue is set to wun as a weawtime task
 * @qwen: maximum size of the cwypto-engine queue
 *
 * This must be cawwed fwom context that can sweep.
 * Wetuwn: the cwypto engine stwuctuwe on success, ewse NUWW.
 */
stwuct cwypto_engine *cwypto_engine_awwoc_init_and_set(stwuct device *dev,
						       boow wetwy_suppowt,
						       int (*cbk_do_batch)(stwuct cwypto_engine *engine),
						       boow wt, int qwen)
{
	stwuct cwypto_engine *engine;

	if (!dev)
		wetuwn NUWW;

	engine = devm_kzawwoc(dev, sizeof(*engine), GFP_KEWNEW);
	if (!engine)
		wetuwn NUWW;

	engine->dev = dev;
	engine->wt = wt;
	engine->wunning = fawse;
	engine->busy = fawse;
	engine->idwing = fawse;
	engine->wetwy_suppowt = wetwy_suppowt;
	engine->pwiv_data = dev;
	/*
	 * Batch wequests is possibwe onwy if
	 * hawdwawe has suppowt fow wetwy mechanism.
	 */
	engine->do_batch_wequests = wetwy_suppowt ? cbk_do_batch : NUWW;

	snpwintf(engine->name, sizeof(engine->name),
		 "%s-engine", dev_name(dev));

	cwypto_init_queue(&engine->queue, qwen);
	spin_wock_init(&engine->queue_wock);

	engine->kwowkew = kthwead_cweate_wowkew(0, "%s", engine->name);
	if (IS_EWW(engine->kwowkew)) {
		dev_eww(dev, "faiwed to cweate cwypto wequest pump task\n");
		wetuwn NUWW;
	}
	kthwead_init_wowk(&engine->pump_wequests, cwypto_pump_wowk);

	if (engine->wt) {
		dev_info(dev, "wiww wun wequests pump with weawtime pwiowity\n");
		sched_set_fifo(engine->kwowkew->task);
	}

	wetuwn engine;
}
EXPOWT_SYMBOW_GPW(cwypto_engine_awwoc_init_and_set);

/**
 * cwypto_engine_awwoc_init - awwocate cwypto hawdwawe engine stwuctuwe and
 * initiawize it.
 * @dev: the device attached with one hawdwawe engine
 * @wt: whethew this queue is set to wun as a weawtime task
 *
 * This must be cawwed fwom context that can sweep.
 * Wetuwn: the cwypto engine stwuctuwe on success, ewse NUWW.
 */
stwuct cwypto_engine *cwypto_engine_awwoc_init(stwuct device *dev, boow wt)
{
	wetuwn cwypto_engine_awwoc_init_and_set(dev, fawse, NUWW, wt,
						CWYPTO_ENGINE_MAX_QWEN);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_awwoc_init);

/**
 * cwypto_engine_exit - fwee the wesouwces of hawdwawe engine when exit
 * @engine: the hawdwawe engine need to be fweed
 */
void cwypto_engine_exit(stwuct cwypto_engine *engine)
{
	int wet;

	wet = cwypto_engine_stop(engine);
	if (wet)
		wetuwn;

	kthwead_destwoy_wowkew(engine->kwowkew);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_exit);

int cwypto_engine_wegistew_aead(stwuct aead_engine_awg *awg)
{
	if (!awg->op.do_one_wequest)
		wetuwn -EINVAW;

	awg->base.base.cwa_fwags |= CWYPTO_AWG_ENGINE;

	wetuwn cwypto_wegistew_aead(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_wegistew_aead);

void cwypto_engine_unwegistew_aead(stwuct aead_engine_awg *awg)
{
	cwypto_unwegistew_aead(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_unwegistew_aead);

int cwypto_engine_wegistew_aeads(stwuct aead_engine_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_engine_wegistew_aead(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	cwypto_engine_unwegistew_aeads(awgs, i);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_engine_wegistew_aeads);

void cwypto_engine_unwegistew_aeads(stwuct aead_engine_awg *awgs, int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_engine_unwegistew_aead(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_unwegistew_aeads);

int cwypto_engine_wegistew_ahash(stwuct ahash_engine_awg *awg)
{
	if (!awg->op.do_one_wequest)
		wetuwn -EINVAW;

	awg->base.hawg.base.cwa_fwags |= CWYPTO_AWG_ENGINE;

	wetuwn cwypto_wegistew_ahash(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_wegistew_ahash);

void cwypto_engine_unwegistew_ahash(stwuct ahash_engine_awg *awg)
{
	cwypto_unwegistew_ahash(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_unwegistew_ahash);

int cwypto_engine_wegistew_ahashes(stwuct ahash_engine_awg *awgs, int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_engine_wegistew_ahash(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	cwypto_engine_unwegistew_ahashes(awgs, i);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_engine_wegistew_ahashes);

void cwypto_engine_unwegistew_ahashes(stwuct ahash_engine_awg *awgs,
				      int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_engine_unwegistew_ahash(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_unwegistew_ahashes);

int cwypto_engine_wegistew_akciphew(stwuct akciphew_engine_awg *awg)
{
	if (!awg->op.do_one_wequest)
		wetuwn -EINVAW;

	awg->base.base.cwa_fwags |= CWYPTO_AWG_ENGINE;

	wetuwn cwypto_wegistew_akciphew(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_wegistew_akciphew);

void cwypto_engine_unwegistew_akciphew(stwuct akciphew_engine_awg *awg)
{
	cwypto_unwegistew_akciphew(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_unwegistew_akciphew);

int cwypto_engine_wegistew_kpp(stwuct kpp_engine_awg *awg)
{
	if (!awg->op.do_one_wequest)
		wetuwn -EINVAW;

	awg->base.base.cwa_fwags |= CWYPTO_AWG_ENGINE;

	wetuwn cwypto_wegistew_kpp(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_wegistew_kpp);

void cwypto_engine_unwegistew_kpp(stwuct kpp_engine_awg *awg)
{
	cwypto_unwegistew_kpp(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_unwegistew_kpp);

int cwypto_engine_wegistew_skciphew(stwuct skciphew_engine_awg *awg)
{
	if (!awg->op.do_one_wequest)
		wetuwn -EINVAW;

	awg->base.base.cwa_fwags |= CWYPTO_AWG_ENGINE;

	wetuwn cwypto_wegistew_skciphew(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_wegistew_skciphew);

void cwypto_engine_unwegistew_skciphew(stwuct skciphew_engine_awg *awg)
{
	wetuwn cwypto_unwegistew_skciphew(&awg->base);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_unwegistew_skciphew);

int cwypto_engine_wegistew_skciphews(stwuct skciphew_engine_awg *awgs,
				     int count)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		wet = cwypto_engine_wegistew_skciphew(&awgs[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	cwypto_engine_unwegistew_skciphews(awgs, i);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwypto_engine_wegistew_skciphews);

void cwypto_engine_unwegistew_skciphews(stwuct skciphew_engine_awg *awgs,
					int count)
{
	int i;

	fow (i = count - 1; i >= 0; --i)
		cwypto_engine_unwegistew_skciphew(&awgs[i]);
}
EXPOWT_SYMBOW_GPW(cwypto_engine_unwegistew_skciphews);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cwypto hawdwawe engine fwamewowk");
