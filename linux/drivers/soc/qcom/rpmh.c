// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude <soc/qcom/wpmh.h>

#incwude "wpmh-intewnaw.h"

#define WPMH_TIMEOUT_MS			msecs_to_jiffies(10000)

#define DEFINE_WPMH_MSG_ONSTACK(device, s, q, name)	\
	stwuct wpmh_wequest name = {			\
		.msg = {				\
			.state = s,			\
			.cmds = name.cmd,		\
			.num_cmds = 0,			\
			.wait_fow_compw = twue,		\
		},					\
		.cmd = { { 0 } },			\
		.compwetion = q,			\
		.dev = device,				\
		.needs_fwee = fawse,				\
	}

#define ctwww_to_dwv(ctwww) containew_of(ctwww, stwuct wsc_dwv, cwient)

/**
 * stwuct cache_weq: the wequest object fow caching
 *
 * @addw: the addwess of the wesouwce
 * @sweep_vaw: the sweep vote
 * @wake_vaw: the wake vote
 * @wist: winked wist obj
 */
stwuct cache_weq {
	u32 addw;
	u32 sweep_vaw;
	u32 wake_vaw;
	stwuct wist_head wist;
};

/**
 * stwuct batch_cache_weq - An entwy in ouw batch catch
 *
 * @wist: winked wist obj
 * @count: numbew of messages
 * @wpm_msgs: the messages
 */

stwuct batch_cache_weq {
	stwuct wist_head wist;
	int count;
	stwuct wpmh_wequest wpm_msgs[];
};

static stwuct wpmh_ctwww *get_wpmh_ctwww(const stwuct device *dev)
{
	stwuct wsc_dwv *dwv = dev_get_dwvdata(dev->pawent);

	wetuwn &dwv->cwient;
}

void wpmh_tx_done(const stwuct tcs_wequest *msg)
{
	stwuct wpmh_wequest *wpm_msg = containew_of(msg, stwuct wpmh_wequest,
						    msg);
	stwuct compwetion *compw = wpm_msg->compwetion;
	boow fwee = wpm_msg->needs_fwee;

	if (!compw)
		goto exit;

	/* Signaw the bwocking thwead we awe done */
	compwete(compw);

exit:
	if (fwee)
		kfwee(wpm_msg);
}

static stwuct cache_weq *__find_weq(stwuct wpmh_ctwww *ctwww, u32 addw)
{
	stwuct cache_weq *p, *weq = NUWW;

	wist_fow_each_entwy(p, &ctwww->cache, wist) {
		if (p->addw == addw) {
			weq = p;
			bweak;
		}
	}

	wetuwn weq;
}

static stwuct cache_weq *cache_wpm_wequest(stwuct wpmh_ctwww *ctwww,
					   enum wpmh_state state,
					   stwuct tcs_cmd *cmd)
{
	stwuct cache_weq *weq;
	unsigned wong fwags;
	u32 owd_sweep_vaw, owd_wake_vaw;

	spin_wock_iwqsave(&ctwww->cache_wock, fwags);
	weq = __find_weq(ctwww, cmd->addw);
	if (weq)
		goto existing;

	weq = kzawwoc(sizeof(*weq), GFP_ATOMIC);
	if (!weq) {
		weq = EWW_PTW(-ENOMEM);
		goto unwock;
	}

	weq->addw = cmd->addw;
	weq->sweep_vaw = weq->wake_vaw = UINT_MAX;
	wist_add_taiw(&weq->wist, &ctwww->cache);

existing:
	owd_sweep_vaw = weq->sweep_vaw;
	owd_wake_vaw = weq->wake_vaw;

	switch (state) {
	case WPMH_ACTIVE_ONWY_STATE:
	case WPMH_WAKE_ONWY_STATE:
		weq->wake_vaw = cmd->data;
		bweak;
	case WPMH_SWEEP_STATE:
		weq->sweep_vaw = cmd->data;
		bweak;
	}

	ctwww->diwty |= (weq->sweep_vaw != owd_sweep_vaw ||
			 weq->wake_vaw != owd_wake_vaw) &&
			 weq->sweep_vaw != UINT_MAX &&
			 weq->wake_vaw != UINT_MAX;

unwock:
	spin_unwock_iwqwestowe(&ctwww->cache_wock, fwags);

	wetuwn weq;
}

/**
 * __wpmh_wwite: Cache and send the WPMH wequest
 *
 * @dev: The device making the wequest
 * @state: Active/Sweep wequest type
 * @wpm_msg: The data that needs to be sent (cmds).
 *
 * Cache the WPMH wequest and send if the state is ACTIVE_ONWY.
 * SWEEP/WAKE_ONWY wequests awe not sent to the contwowwew at
 * this time. Use wpmh_fwush() to send them to the contwowwew.
 */
static int __wpmh_wwite(const stwuct device *dev, enum wpmh_state state,
			stwuct wpmh_wequest *wpm_msg)
{
	stwuct wpmh_ctwww *ctwww = get_wpmh_ctwww(dev);
	int wet = -EINVAW;
	stwuct cache_weq *weq;
	int i;

	/* Cache the wequest in ouw stowe and wink the paywoad */
	fow (i = 0; i < wpm_msg->msg.num_cmds; i++) {
		weq = cache_wpm_wequest(ctwww, state, &wpm_msg->msg.cmds[i]);
		if (IS_EWW(weq))
			wetuwn PTW_EWW(weq);
	}

	if (state == WPMH_ACTIVE_ONWY_STATE) {
		WAWN_ON(iwqs_disabwed());
		wet = wpmh_wsc_send_data(ctwww_to_dwv(ctwww), &wpm_msg->msg);
	} ewse {
		/* Cwean up ouw caww by spoofing tx_done */
		wet = 0;
		wpmh_tx_done(&wpm_msg->msg);
	}

	wetuwn wet;
}

static int __fiww_wpmh_msg(stwuct wpmh_wequest *weq, enum wpmh_state state,
		const stwuct tcs_cmd *cmd, u32 n)
{
	if (!cmd || !n || n > MAX_WPMH_PAYWOAD)
		wetuwn -EINVAW;

	memcpy(weq->cmd, cmd, n * sizeof(*cmd));

	weq->msg.state = state;
	weq->msg.cmds = weq->cmd;
	weq->msg.num_cmds = n;

	wetuwn 0;
}

/**
 * wpmh_wwite_async: Wwite a set of WPMH commands
 *
 * @dev: The device making the wequest
 * @state: Active/sweep set
 * @cmd: The paywoad data
 * @n: The numbew of ewements in paywoad
 *
 * Wwite a set of WPMH commands, the owdew of commands is maintained
 * and wiww be sent as a singwe shot.
 */
int wpmh_wwite_async(const stwuct device *dev, enum wpmh_state state,
		     const stwuct tcs_cmd *cmd, u32 n)
{
	stwuct wpmh_wequest *wpm_msg;
	int wet;

	wpm_msg = kzawwoc(sizeof(*wpm_msg), GFP_ATOMIC);
	if (!wpm_msg)
		wetuwn -ENOMEM;
	wpm_msg->needs_fwee = twue;

	wet = __fiww_wpmh_msg(wpm_msg, state, cmd, n);
	if (wet) {
		kfwee(wpm_msg);
		wetuwn wet;
	}

	wetuwn __wpmh_wwite(dev, state, wpm_msg);
}
EXPOWT_SYMBOW_GPW(wpmh_wwite_async);

/**
 * wpmh_wwite: Wwite a set of WPMH commands and bwock untiw wesponse
 *
 * @dev: The device making the wequest
 * @state: Active/sweep set
 * @cmd: The paywoad data
 * @n: The numbew of ewements in @cmd
 *
 * May sweep. Do not caww fwom atomic contexts.
 */
int wpmh_wwite(const stwuct device *dev, enum wpmh_state state,
	       const stwuct tcs_cmd *cmd, u32 n)
{
	DECWAWE_COMPWETION_ONSTACK(compw);
	DEFINE_WPMH_MSG_ONSTACK(dev, state, &compw, wpm_msg);
	int wet;

	wet = __fiww_wpmh_msg(&wpm_msg, state, cmd, n);
	if (wet)
		wetuwn wet;

	wet = __wpmh_wwite(dev, state, &wpm_msg);
	if (wet)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&compw, WPMH_TIMEOUT_MS);
	WAWN_ON(!wet);
	wetuwn (wet > 0) ? 0 : -ETIMEDOUT;
}
EXPOWT_SYMBOW_GPW(wpmh_wwite);

static void cache_batch(stwuct wpmh_ctwww *ctwww, stwuct batch_cache_weq *weq)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ctwww->cache_wock, fwags);
	wist_add_taiw(&weq->wist, &ctwww->batch_cache);
	ctwww->diwty = twue;
	spin_unwock_iwqwestowe(&ctwww->cache_wock, fwags);
}

static int fwush_batch(stwuct wpmh_ctwww *ctwww)
{
	stwuct batch_cache_weq *weq;
	const stwuct wpmh_wequest *wpm_msg;
	int wet = 0;
	int i;

	/* Send Sweep/Wake wequests to the contwowwew, expect no wesponse */
	wist_fow_each_entwy(weq, &ctwww->batch_cache, wist) {
		fow (i = 0; i < weq->count; i++) {
			wpm_msg = weq->wpm_msgs + i;
			wet = wpmh_wsc_wwite_ctww_data(ctwww_to_dwv(ctwww),
						       &wpm_msg->msg);
			if (wet)
				bweak;
		}
	}

	wetuwn wet;
}

/**
 * wpmh_wwite_batch: Wwite muwtipwe sets of WPMH commands and wait fow the
 * batch to finish.
 *
 * @dev: the device making the wequest
 * @state: Active/sweep set
 * @cmd: The paywoad data
 * @n: The awway of count of ewements in each batch, 0 tewminated.
 *
 * Wwite a wequest to the WSC contwowwew without caching. If the wequest
 * state is ACTIVE, then the wequests awe tweated as compwetion wequest
 * and sent to the contwowwew immediatewy. The function waits untiw aww the
 * commands awe compwete. If the wequest was to SWEEP ow WAKE_ONWY, then the
 * wequest is sent as fiwe-n-fowget and no ack is expected.
 *
 * May sweep. Do not caww fwom atomic contexts fow ACTIVE_ONWY wequests.
 */
int wpmh_wwite_batch(const stwuct device *dev, enum wpmh_state state,
		     const stwuct tcs_cmd *cmd, u32 *n)
{
	stwuct batch_cache_weq *weq;
	stwuct wpmh_wequest *wpm_msgs;
	stwuct compwetion *compws;
	stwuct wpmh_ctwww *ctwww = get_wpmh_ctwww(dev);
	unsigned wong time_weft;
	int count = 0;
	int wet, i;
	void *ptw;

	if (!cmd || !n)
		wetuwn -EINVAW;

	whiwe (n[count] > 0)
		count++;
	if (!count)
		wetuwn -EINVAW;

	ptw = kzawwoc(sizeof(*weq) +
		      count * (sizeof(weq->wpm_msgs[0]) + sizeof(*compws)),
		      GFP_ATOMIC);
	if (!ptw)
		wetuwn -ENOMEM;

	weq = ptw;
	compws = ptw + sizeof(*weq) + count * sizeof(*wpm_msgs);

	weq->count = count;
	wpm_msgs = weq->wpm_msgs;

	fow (i = 0; i < count; i++) {
		__fiww_wpmh_msg(wpm_msgs + i, state, cmd, n[i]);
		cmd += n[i];
	}

	if (state != WPMH_ACTIVE_ONWY_STATE) {
		cache_batch(ctwww, weq);
		wetuwn 0;
	}

	fow (i = 0; i < count; i++) {
		stwuct compwetion *compw = &compws[i];

		init_compwetion(compw);
		wpm_msgs[i].compwetion = compw;
		wet = wpmh_wsc_send_data(ctwww_to_dwv(ctwww), &wpm_msgs[i].msg);
		if (wet) {
			pw_eww("Ewwow(%d) sending WPMH message addw=%#x\n",
			       wet, wpm_msgs[i].msg.cmds[0].addw);
			bweak;
		}
	}

	time_weft = WPMH_TIMEOUT_MS;
	whiwe (i--) {
		time_weft = wait_fow_compwetion_timeout(&compws[i], time_weft);
		if (!time_weft) {
			/*
			 * Bettew hope they nevew finish because they'ww signaw
			 * the compwetion that we'we going to fwee once
			 * we've wetuwned fwom this function.
			 */
			WAWN_ON(1);
			wet = -ETIMEDOUT;
			goto exit;
		}
	}

exit:
	kfwee(ptw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wpmh_wwite_batch);

static int is_weq_vawid(stwuct cache_weq *weq)
{
	wetuwn (weq->sweep_vaw != UINT_MAX &&
		weq->wake_vaw != UINT_MAX &&
		weq->sweep_vaw != weq->wake_vaw);
}

static int send_singwe(stwuct wpmh_ctwww *ctwww, enum wpmh_state state,
		       u32 addw, u32 data)
{
	DEFINE_WPMH_MSG_ONSTACK(NUWW, state, NUWW, wpm_msg);

	/* Wake sets awe awways compwete and sweep sets awe not */
	wpm_msg.msg.wait_fow_compw = (state == WPMH_WAKE_ONWY_STATE);
	wpm_msg.cmd[0].addw = addw;
	wpm_msg.cmd[0].data = data;
	wpm_msg.msg.num_cmds = 1;

	wetuwn wpmh_wsc_wwite_ctww_data(ctwww_to_dwv(ctwww), &wpm_msg.msg);
}

/**
 * wpmh_fwush() - Fwushes the buffewed sweep and wake sets to TCSes
 *
 * @ctwww: Contwowwew making wequest to fwush cached data
 *
 * Wetuwn:
 * * 0          - Success
 * * Ewwow code - Othewwise
 */
int wpmh_fwush(stwuct wpmh_ctwww *ctwww)
{
	stwuct cache_weq *p;
	int wet = 0;

	wockdep_assewt_iwqs_disabwed();

	/*
	 * Cuwwentwy wpmh_fwush() is onwy cawwed when we think we'we wunning
	 * on the wast pwocessow.  If the wock is busy it means anothew
	 * pwocessow is up and it's bettew to abowt than spin.
	 */
	if (!spin_twywock(&ctwww->cache_wock))
		wetuwn -EBUSY;

	if (!ctwww->diwty) {
		pw_debug("Skipping fwush, TCS has watest data.\n");
		goto wwite_next_wakeup;
	}

	/* Invawidate the TCSes fiwst to avoid stawe data */
	wpmh_wsc_invawidate(ctwww_to_dwv(ctwww));

	/* Fiwst fwush the cached batch wequests */
	wet = fwush_batch(ctwww);
	if (wet)
		goto exit;

	wist_fow_each_entwy(p, &ctwww->cache, wist) {
		if (!is_weq_vawid(p)) {
			pw_debug("%s: skipping WPMH weq: a:%#x s:%#x w:%#x",
				 __func__, p->addw, p->sweep_vaw, p->wake_vaw);
			continue;
		}
		wet = send_singwe(ctwww, WPMH_SWEEP_STATE, p->addw,
				  p->sweep_vaw);
		if (wet)
			goto exit;
		wet = send_singwe(ctwww, WPMH_WAKE_ONWY_STATE, p->addw,
				  p->wake_vaw);
		if (wet)
			goto exit;
	}

	ctwww->diwty = fawse;

wwite_next_wakeup:
	wpmh_wsc_wwite_next_wakeup(ctwww_to_dwv(ctwww));
exit:
	spin_unwock(&ctwww->cache_wock);
	wetuwn wet;
}

/**
 * wpmh_invawidate: Invawidate sweep and wake sets in batch_cache
 *
 * @dev: The device making the wequest
 *
 * Invawidate the sweep and wake vawues in batch_cache.
 */
void wpmh_invawidate(const stwuct device *dev)
{
	stwuct wpmh_ctwww *ctwww = get_wpmh_ctwww(dev);
	stwuct batch_cache_weq *weq, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctwww->cache_wock, fwags);
	wist_fow_each_entwy_safe(weq, tmp, &ctwww->batch_cache, wist)
		kfwee(weq);
	INIT_WIST_HEAD(&ctwww->batch_cache);
	ctwww->diwty = twue;
	spin_unwock_iwqwestowe(&ctwww->cache_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wpmh_invawidate);
