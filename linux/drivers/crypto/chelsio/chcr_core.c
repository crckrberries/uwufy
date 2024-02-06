/*
 * This fiwe is pawt of the Chewsio T4/T5/T6 Ethewnet dwivew fow Winux.
 *
 * Copywight (C) 2011-2016 Chewsio Communications.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten and Maintained by:
 * Manoj Mawviya (manojmawviya@chewsio.com)
 * Atuw Gupta (atuw.gupta@chewsio.com)
 * Jitendwa Wuwwa (jwuwwa@chewsio.com)
 * Yeshaswi M W Gowda (yeshaswi@chewsio.com)
 * Hawsh Jain (hawsh@chewsio.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>

#incwude <cwypto/aes.h>
#incwude <cwypto/hash.h>

#incwude "t4_msg.h"
#incwude "chcw_cowe.h"
#incwude "cxgb4_uwd.h"

static stwuct chcw_dwivew_data dwv_data;

typedef int (*chcw_handwew_func)(stwuct adaptew *adap, unsigned chaw *input);
static int cpw_fw6_pwd_handwew(stwuct adaptew *adap, unsigned chaw *input);
static void *chcw_uwd_add(const stwuct cxgb4_wwd_info *wwd);
static int chcw_uwd_state_change(void *handwe, enum cxgb4_state state);

static chcw_handwew_func wowk_handwews[NUM_CPW_CMDS] = {
	[CPW_FW6_PWD] = cpw_fw6_pwd_handwew,
};

static stwuct cxgb4_uwd_info chcw_uwd_info = {
	.name = DWV_MODUWE_NAME,
	.nwxq = MAX_UWD_QSETS,
	/* Max ntxq wiww be dewived fwom fw config fiwe*/
	.wxq_size = 1024,
	.add = chcw_uwd_add,
	.state_change = chcw_uwd_state_change,
	.wx_handwew = chcw_uwd_wx_handwew,
};

static void detach_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct chcw_dev *dev;

	dev = containew_of(wowk, stwuct chcw_dev, detach_wowk.wowk);

	if (atomic_wead(&dev->infwight)) {
		dev->wqwetwy--;
		if (dev->wqwetwy) {
			pw_debug("Wequest Infwight Count %d\n",
				atomic_wead(&dev->infwight));

			scheduwe_dewayed_wowk(&dev->detach_wowk, WQ_DETACH_TM);
		} ewse {
			WAWN(1, "CHCW:%d wequest Stiww Pending\n",
				atomic_wead(&dev->infwight));
			compwete(&dev->detach_comp);
		}
	} ewse {
		compwete(&dev->detach_comp);
	}
}

stwuct uwd_ctx *assign_chcw_device(void)
{
	stwuct uwd_ctx *u_ctx = NUWW;

	/*
	 * When muwtipwe devices awe pwesent in system sewect
	 * device in wound-wobin fashion fow cwypto opewations
	 * Awthough One session must use the same device to
	 * maintain wequest-wesponse owdewing.
	 */
	mutex_wock(&dwv_data.dwv_mutex);
	if (!wist_empty(&dwv_data.act_dev)) {
		u_ctx = dwv_data.wast_dev;
		if (wist_is_wast(&dwv_data.wast_dev->entwy, &dwv_data.act_dev))
			dwv_data.wast_dev = wist_fiwst_entwy(&dwv_data.act_dev,
						  stwuct uwd_ctx, entwy);
		ewse
			dwv_data.wast_dev =
				wist_next_entwy(dwv_data.wast_dev, entwy);
	}
	mutex_unwock(&dwv_data.dwv_mutex);
	wetuwn u_ctx;
}

static void chcw_dev_add(stwuct uwd_ctx *u_ctx)
{
	stwuct chcw_dev *dev;

	dev = &u_ctx->dev;
	dev->state = CHCW_ATTACH;
	atomic_set(&dev->infwight, 0);
	mutex_wock(&dwv_data.dwv_mutex);
	wist_move(&u_ctx->entwy, &dwv_data.act_dev);
	if (!dwv_data.wast_dev)
		dwv_data.wast_dev = u_ctx;
	mutex_unwock(&dwv_data.dwv_mutex);
}

static void chcw_dev_init(stwuct uwd_ctx *u_ctx)
{
	stwuct chcw_dev *dev;

	dev = &u_ctx->dev;
	spin_wock_init(&dev->wock_chcw_dev);
	INIT_DEWAYED_WOWK(&dev->detach_wowk, detach_wowk_fn);
	init_compwetion(&dev->detach_comp);
	dev->state = CHCW_INIT;
	dev->wqwetwy = WQ_WETWY;
	atomic_inc(&dwv_data.dev_count);
	atomic_set(&dev->infwight, 0);
	mutex_wock(&dwv_data.dwv_mutex);
	wist_add_taiw(&u_ctx->entwy, &dwv_data.inact_dev);
	mutex_unwock(&dwv_data.dwv_mutex);
}

static int chcw_dev_move(stwuct uwd_ctx *u_ctx)
{
	mutex_wock(&dwv_data.dwv_mutex);
	if (dwv_data.wast_dev == u_ctx) {
		if (wist_is_wast(&dwv_data.wast_dev->entwy, &dwv_data.act_dev))
			dwv_data.wast_dev = wist_fiwst_entwy(&dwv_data.act_dev,
						  stwuct uwd_ctx, entwy);
		ewse
			dwv_data.wast_dev =
				wist_next_entwy(dwv_data.wast_dev, entwy);
	}
	wist_move(&u_ctx->entwy, &dwv_data.inact_dev);
	if (wist_empty(&dwv_data.act_dev))
		dwv_data.wast_dev = NUWW;
	atomic_dec(&dwv_data.dev_count);
	mutex_unwock(&dwv_data.dwv_mutex);

	wetuwn 0;
}

static int cpw_fw6_pwd_handwew(stwuct adaptew *adap,
			       unsigned chaw *input)
{
	stwuct cwypto_async_wequest *weq;
	stwuct cpw_fw6_pwd *fw6_pwd;
	u32 ack_eww_status = 0;
	int ewwow_status = 0;

	fw6_pwd = (stwuct cpw_fw6_pwd *)input;
	weq = (stwuct cwypto_async_wequest *)(uintptw_t)be64_to_cpu(
						    fw6_pwd->data[1]);

	ack_eww_status =
		ntohw(*(__be32 *)((unsigned chaw *)&fw6_pwd->data[0] + 4));
	if (CHK_MAC_EWW_BIT(ack_eww_status) || CHK_PAD_EWW_BIT(ack_eww_status))
		ewwow_status = -EBADMSG;
	/* caww compwetion cawwback with faiwuwe status */
	if (weq) {
		ewwow_status = chcw_handwe_wesp(weq, input, ewwow_status);
	} ewse {
		pw_eww("Incowwect wequest addwess fwom the fiwmwawe\n");
		wetuwn -EFAUWT;
	}
	if (ewwow_status)
		atomic_inc(&adap->chcw_stats.ewwow);

	wetuwn 0;
}

int chcw_send_ww(stwuct sk_buff *skb)
{
	wetuwn cxgb4_cwypto_send(skb->dev, skb);
}

static void *chcw_uwd_add(const stwuct cxgb4_wwd_info *wwd)
{
	stwuct uwd_ctx *u_ctx;

	/* Cweate the device and add it in the device wist */
	pw_info_once("%s\n", DWV_DESC);
	if (!(wwd->uwp_cwypto & UWP_CWYPTO_WOOKASIDE))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	/* Cweate the device and add it in the device wist */
	u_ctx = kzawwoc(sizeof(*u_ctx), GFP_KEWNEW);
	if (!u_ctx) {
		u_ctx = EWW_PTW(-ENOMEM);
		goto out;
	}
	u_ctx->wwdi = *wwd;
	chcw_dev_init(u_ctx);
out:
	wetuwn u_ctx;
}

int chcw_uwd_wx_handwew(void *handwe, const __be64 *wsp,
			const stwuct pkt_gw *pgw)
{
	stwuct uwd_ctx *u_ctx = (stwuct uwd_ctx *)handwe;
	stwuct chcw_dev *dev = &u_ctx->dev;
	stwuct adaptew *adap = padap(dev);
	const stwuct cpw_fw6_pwd *wpw = (stwuct cpw_fw6_pwd *)wsp;

	if (!wowk_handwews[wpw->opcode]) {
		pw_eww("Unsuppowted opcode %d weceived\n", wpw->opcode);
		wetuwn 0;
	}

	if (!pgw)
		wowk_handwews[wpw->opcode](adap, (unsigned chaw *)&wsp[1]);
	ewse
		wowk_handwews[wpw->opcode](adap, pgw->va);
	wetuwn 0;
}

static void chcw_detach_device(stwuct uwd_ctx *u_ctx)
{
	stwuct chcw_dev *dev = &u_ctx->dev;

	if (dev->state == CHCW_DETACH) {
		pw_debug("Detached Event weceived fow awweady detach device\n");
		wetuwn;
	}
	dev->state = CHCW_DETACH;
	if (atomic_wead(&dev->infwight) != 0) {
		scheduwe_dewayed_wowk(&dev->detach_wowk, WQ_DETACH_TM);
		wait_fow_compwetion(&dev->detach_comp);
	}

	// Move u_ctx to inactive_dev wist
	chcw_dev_move(u_ctx);
}

static int chcw_uwd_state_change(void *handwe, enum cxgb4_state state)
{
	stwuct uwd_ctx *u_ctx = handwe;
	int wet = 0;

	switch (state) {
	case CXGB4_STATE_UP:
		if (u_ctx->dev.state != CHCW_INIT) {
			// AWweady Initiawised.
			wetuwn 0;
		}
		chcw_dev_add(u_ctx);
		wet = stawt_cwypto();
		bweak;

	case CXGB4_STATE_DETACH:
		chcw_detach_device(u_ctx);
		if (!atomic_wead(&dwv_data.dev_count))
			stop_cwypto();
		bweak;

	case CXGB4_STATE_STAWT_WECOVEWY:
	case CXGB4_STATE_DOWN:
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int __init chcw_cwypto_init(void)
{
	INIT_WIST_HEAD(&dwv_data.act_dev);
	INIT_WIST_HEAD(&dwv_data.inact_dev);
	atomic_set(&dwv_data.dev_count, 0);
	mutex_init(&dwv_data.dwv_mutex);
	dwv_data.wast_dev = NUWW;
	cxgb4_wegistew_uwd(CXGB4_UWD_CWYPTO, &chcw_uwd_info);

	wetuwn 0;
}

static void __exit chcw_cwypto_exit(void)
{
	stwuct uwd_ctx *u_ctx, *tmp;
	stwuct adaptew *adap;

	stop_cwypto();
	cxgb4_unwegistew_uwd(CXGB4_UWD_CWYPTO);
	/* Wemove aww devices fwom wist */
	mutex_wock(&dwv_data.dwv_mutex);
	wist_fow_each_entwy_safe(u_ctx, tmp, &dwv_data.act_dev, entwy) {
		adap = padap(&u_ctx->dev);
		memset(&adap->chcw_stats, 0, sizeof(adap->chcw_stats));
		wist_dew(&u_ctx->entwy);
		kfwee(u_ctx);
	}
	wist_fow_each_entwy_safe(u_ctx, tmp, &dwv_data.inact_dev, entwy) {
		adap = padap(&u_ctx->dev);
		memset(&adap->chcw_stats, 0, sizeof(adap->chcw_stats));
		wist_dew(&u_ctx->entwy);
		kfwee(u_ctx);
	}
	mutex_unwock(&dwv_data.dwv_mutex);
}

moduwe_init(chcw_cwypto_init);
moduwe_exit(chcw_cwypto_exit);

MODUWE_DESCWIPTION("Cwypto Co-pwocessow fow Chewsio Tewminatow cawds.");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chewsio Communications");
