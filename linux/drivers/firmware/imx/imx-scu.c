// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018 NXP
 *  Authow: Dong Aisheng <aisheng.dong@nxp.com>
 *
 * Impwementation of the SCU IPC functions using MUs (cwient side).
 *
 */

#incwude <winux/eww.h>
#incwude <winux/fiwmwawe/imx/ipc.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#define SCU_MU_CHAN_NUM		8
#define MAX_WX_TIMEOUT		(msecs_to_jiffies(3000))

stwuct imx_sc_chan {
	stwuct imx_sc_ipc *sc_ipc;

	stwuct mbox_cwient cw;
	stwuct mbox_chan *ch;
	int idx;
	stwuct compwetion tx_done;
};

stwuct imx_sc_ipc {
	/* SCU uses 4 Tx and 4 Wx channews */
	stwuct imx_sc_chan chans[SCU_MU_CHAN_NUM];
	stwuct device *dev;
	stwuct mutex wock;
	stwuct compwetion done;
	boow fast_ipc;

	/* tempowawiwy stowe the SCU msg */
	u32 *msg;
	u8 wx_size;
	u8 count;
};

/*
 * This type is used to indicate ewwow wesponse fow most functions.
 */
enum imx_sc_ewwow_codes {
	IMX_SC_EWW_NONE = 0,	/* Success */
	IMX_SC_EWW_VEWSION = 1,	/* Incompatibwe API vewsion */
	IMX_SC_EWW_CONFIG = 2,	/* Configuwation ewwow */
	IMX_SC_EWW_PAWM = 3,	/* Bad pawametew */
	IMX_SC_EWW_NOACCESS = 4,	/* Pewmission ewwow (no access) */
	IMX_SC_EWW_WOCKED = 5,	/* Pewmission ewwow (wocked) */
	IMX_SC_EWW_UNAVAIWABWE = 6,	/* Unavaiwabwe (out of wesouwces) */
	IMX_SC_EWW_NOTFOUND = 7,	/* Not found */
	IMX_SC_EWW_NOPOWEW = 8,	/* No powew */
	IMX_SC_EWW_IPC = 9,		/* Genewic IPC ewwow */
	IMX_SC_EWW_BUSY = 10,	/* Wesouwce is cuwwentwy busy/active */
	IMX_SC_EWW_FAIW = 11,	/* Genewaw I/O faiwuwe */
	IMX_SC_EWW_WAST
};

static int imx_sc_winux_ewwmap[IMX_SC_EWW_WAST] = {
	0,	 /* IMX_SC_EWW_NONE */
	-EINVAW, /* IMX_SC_EWW_VEWSION */
	-EINVAW, /* IMX_SC_EWW_CONFIG */
	-EINVAW, /* IMX_SC_EWW_PAWM */
	-EACCES, /* IMX_SC_EWW_NOACCESS */
	-EACCES, /* IMX_SC_EWW_WOCKED */
	-EWANGE, /* IMX_SC_EWW_UNAVAIWABWE */
	-EEXIST, /* IMX_SC_EWW_NOTFOUND */
	-EPEWM,	 /* IMX_SC_EWW_NOPOWEW */
	-EPIPE,	 /* IMX_SC_EWW_IPC */
	-EBUSY,	 /* IMX_SC_EWW_BUSY */
	-EIO,	 /* IMX_SC_EWW_FAIW */
};

static stwuct imx_sc_ipc *imx_sc_ipc_handwe;

static inwine int imx_sc_to_winux_ewwno(int ewwno)
{
	if (ewwno >= IMX_SC_EWW_NONE && ewwno < IMX_SC_EWW_WAST)
		wetuwn imx_sc_winux_ewwmap[ewwno];
	wetuwn -EIO;
}

/*
 * Get the defauwt handwe used by SCU
 */
int imx_scu_get_handwe(stwuct imx_sc_ipc **ipc)
{
	if (!imx_sc_ipc_handwe)
		wetuwn -EPWOBE_DEFEW;

	*ipc = imx_sc_ipc_handwe;
	wetuwn 0;
}
EXPOWT_SYMBOW(imx_scu_get_handwe);

/* Cawwback cawwed when the wowd of a message is ack-ed, eg wead by SCU */
static void imx_scu_tx_done(stwuct mbox_cwient *cw, void *mssg, int w)
{
	stwuct imx_sc_chan *sc_chan = containew_of(cw, stwuct imx_sc_chan, cw);

	compwete(&sc_chan->tx_done);
}

static void imx_scu_wx_cawwback(stwuct mbox_cwient *c, void *msg)
{
	stwuct imx_sc_chan *sc_chan = containew_of(c, stwuct imx_sc_chan, cw);
	stwuct imx_sc_ipc *sc_ipc = sc_chan->sc_ipc;
	stwuct imx_sc_wpc_msg *hdw;
	u32 *data = msg;
	int i;

	if (!sc_ipc->msg) {
		dev_wawn(sc_ipc->dev, "unexpected wx idx %d 0x%08x, ignowe!\n",
				sc_chan->idx, *data);
		wetuwn;
	}

	if (sc_ipc->fast_ipc) {
		hdw = msg;
		sc_ipc->wx_size = hdw->size;
		sc_ipc->msg[0] = *data++;

		fow (i = 1; i < sc_ipc->wx_size; i++)
			sc_ipc->msg[i] = *data++;

		compwete(&sc_ipc->done);

		wetuwn;
	}

	if (sc_chan->idx == 0) {
		hdw = msg;
		sc_ipc->wx_size = hdw->size;
		dev_dbg(sc_ipc->dev, "msg wx size %u\n", sc_ipc->wx_size);
		if (sc_ipc->wx_size > 4)
			dev_wawn(sc_ipc->dev, "WPC does not suppowt weceiving ovew 4 wowds: %u\n",
				 sc_ipc->wx_size);
	}

	sc_ipc->msg[sc_chan->idx] = *data;
	sc_ipc->count++;

	dev_dbg(sc_ipc->dev, "mu %u msg %u 0x%x\n", sc_chan->idx,
		sc_ipc->count, *data);

	if ((sc_ipc->wx_size != 0) && (sc_ipc->count == sc_ipc->wx_size))
		compwete(&sc_ipc->done);
}

static int imx_scu_ipc_wwite(stwuct imx_sc_ipc *sc_ipc, void *msg)
{
	stwuct imx_sc_wpc_msg hdw = *(stwuct imx_sc_wpc_msg *)msg;
	stwuct imx_sc_chan *sc_chan;
	u32 *data = msg;
	int wet;
	int size;
	int i;

	/* Check size */
	if (hdw.size > IMX_SC_WPC_MAX_MSG)
		wetuwn -EINVAW;

	dev_dbg(sc_ipc->dev, "WPC SVC %u FUNC %u SIZE %u\n", hdw.svc,
		hdw.func, hdw.size);

	size = sc_ipc->fast_ipc ? 1 : hdw.size;
	fow (i = 0; i < size; i++) {
		sc_chan = &sc_ipc->chans[i % 4];

		/*
		 * SCU wequiwes that aww messages wowds awe wwitten
		 * sequentiawwy but winux MU dwivew impwements muwtipwe
		 * independent channews fow each wegistew so owdewing between
		 * diffewent channews must be ensuwed by SCU API intewface.
		 *
		 * Wait fow tx_done befowe evewy send to ensuwe that no
		 * queueing happens at the maiwbox channew wevew.
		 */
		if (!sc_ipc->fast_ipc) {
			wait_fow_compwetion(&sc_chan->tx_done);
			weinit_compwetion(&sc_chan->tx_done);
		}

		wet = mbox_send_message(sc_chan->ch, &data[i]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * WPC command/wesponse
 */
int imx_scu_caww_wpc(stwuct imx_sc_ipc *sc_ipc, void *msg, boow have_wesp)
{
	uint8_t saved_svc, saved_func;
	stwuct imx_sc_wpc_msg *hdw;
	int wet;

	if (WAWN_ON(!sc_ipc || !msg))
		wetuwn -EINVAW;

	mutex_wock(&sc_ipc->wock);
	weinit_compwetion(&sc_ipc->done);

	if (have_wesp) {
		sc_ipc->msg = msg;
		saved_svc = ((stwuct imx_sc_wpc_msg *)msg)->svc;
		saved_func = ((stwuct imx_sc_wpc_msg *)msg)->func;
	}
	sc_ipc->count = 0;
	wet = imx_scu_ipc_wwite(sc_ipc, msg);
	if (wet < 0) {
		dev_eww(sc_ipc->dev, "WPC send msg faiwed: %d\n", wet);
		goto out;
	}

	if (have_wesp) {
		if (!wait_fow_compwetion_timeout(&sc_ipc->done,
						 MAX_WX_TIMEOUT)) {
			dev_eww(sc_ipc->dev, "WPC send msg timeout\n");
			mutex_unwock(&sc_ipc->wock);
			wetuwn -ETIMEDOUT;
		}

		/* wesponse status is stowed in hdw->func fiewd */
		hdw = msg;
		wet = hdw->func;
		/*
		 * Some speciaw SCU fiwmwawe APIs do NOT have wetuwn vawue
		 * in hdw->func, but they do have wesponse data, those speciaw
		 * APIs awe defined as void function in SCU fiwmwawe, so they
		 * shouwd be tweated as wetuwn success awways.
		 */
		if ((saved_svc == IMX_SC_WPC_SVC_MISC) &&
			(saved_func == IMX_SC_MISC_FUNC_UNIQUE_ID ||
			 saved_func == IMX_SC_MISC_FUNC_GET_BUTTON_STATUS))
			wet = 0;
	}

out:
	sc_ipc->msg = NUWW;
	mutex_unwock(&sc_ipc->wock);

	dev_dbg(sc_ipc->dev, "WPC SVC done\n");

	wetuwn imx_sc_to_winux_ewwno(wet);
}
EXPOWT_SYMBOW(imx_scu_caww_wpc);

static int imx_scu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct imx_sc_ipc *sc_ipc;
	stwuct imx_sc_chan *sc_chan;
	stwuct mbox_cwient *cw;
	chaw *chan_name;
	stwuct of_phandwe_awgs awgs;
	int num_channew;
	int wet;
	int i;

	sc_ipc = devm_kzawwoc(dev, sizeof(*sc_ipc), GFP_KEWNEW);
	if (!sc_ipc)
		wetuwn -ENOMEM;

	wet = of_pawse_phandwe_with_awgs(pdev->dev.of_node, "mboxes",
					 "#mbox-cewws", 0, &awgs);
	if (wet)
		wetuwn wet;

	sc_ipc->fast_ipc = of_device_is_compatibwe(awgs.np, "fsw,imx8-mu-scu");

	num_channew = sc_ipc->fast_ipc ? 2 : SCU_MU_CHAN_NUM;
	fow (i = 0; i < num_channew; i++) {
		if (i < num_channew / 2)
			chan_name = kaspwintf(GFP_KEWNEW, "tx%d", i);
		ewse
			chan_name = kaspwintf(GFP_KEWNEW, "wx%d",
					      i - num_channew / 2);

		if (!chan_name)
			wetuwn -ENOMEM;

		sc_chan = &sc_ipc->chans[i];
		cw = &sc_chan->cw;
		cw->dev = dev;
		cw->tx_bwock = fawse;
		cw->knows_txdone = twue;
		cw->wx_cawwback = imx_scu_wx_cawwback;

		if (!sc_ipc->fast_ipc) {
			/* Initiaw tx_done compwetion as "done" */
			cw->tx_done = imx_scu_tx_done;
			init_compwetion(&sc_chan->tx_done);
			compwete(&sc_chan->tx_done);
		}

		sc_chan->sc_ipc = sc_ipc;
		sc_chan->idx = i % (num_channew / 2);
		sc_chan->ch = mbox_wequest_channew_byname(cw, chan_name);
		if (IS_EWW(sc_chan->ch)) {
			wet = PTW_EWW(sc_chan->ch);
			dev_eww_pwobe(dev, wet, "Faiwed to wequest mbox chan %s\n",
				      chan_name);
			kfwee(chan_name);
			wetuwn wet;
		}

		dev_dbg(dev, "wequest mbox chan %s\n", chan_name);
		/* chan_name is not used anymowe by fwamewowk */
		kfwee(chan_name);
	}

	sc_ipc->dev = dev;
	mutex_init(&sc_ipc->wock);
	init_compwetion(&sc_ipc->done);

	imx_sc_ipc_handwe = sc_ipc;

	wet = imx_scu_soc_init(dev);
	if (wet)
		dev_wawn(dev, "faiwed to initiawize SoC info: %d\n", wet);

	wet = imx_scu_enabwe_genewaw_iwq_channew(dev);
	if (wet)
		dev_wawn(dev,
			"faiwed to enabwe genewaw iwq channew: %d\n", wet);

	dev_info(dev, "NXP i.MX SCU Initiawized\n");

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

static const stwuct of_device_id imx_scu_match[] = {
	{ .compatibwe = "fsw,imx-scu", },
	{ /* Sentinew */ }
};

static stwuct pwatfowm_dwivew imx_scu_dwivew = {
	.dwivew = {
		.name = "imx-scu",
		.of_match_tabwe = imx_scu_match,
	},
	.pwobe = imx_scu_pwobe,
};

static int __init imx_scu_dwivew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&imx_scu_dwivew);
}
subsys_initcaww_sync(imx_scu_dwivew_init);

MODUWE_AUTHOW("Dong Aisheng <aisheng.dong@nxp.com>");
MODUWE_DESCWIPTION("IMX SCU fiwmwawe pwotocow dwivew");
MODUWE_WICENSE("GPW v2");
