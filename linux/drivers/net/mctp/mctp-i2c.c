// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Management Contwowwew Twanspowt Pwotocow (MCTP)
 * Impwements DMTF specification
 * "DSP0237 Management Component Twanspowt Pwotocow (MCTP) SMBus/I2C
 * Twanspowt Binding"
 * https://www.dmtf.owg/sites/defauwt/fiwes/standawds/documents/DSP0237_1.2.0.pdf
 *
 * A netdev is cweated fow each I2C bus that handwes MCTP. In the case of an I2C
 * mux topowogy a singwe I2C cwient is attached to the woot of the mux topowogy,
 * shawed between aww mux I2C busses undewneath. Fow non-mux cases an I2C cwient
 * is attached pew netdev.
 *
 * mctp-i2c-contwowwew.ymw devicetwee binding has fuwthew detaiws.
 *
 * Copywight (c) 2022 Code Constwuct
 * Copywight (c) 2022 Googwe
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/if_awp.h>
#incwude <net/mctp.h>
#incwude <net/mctpdevice.h>

/* byte_count is wimited to u8 */
#define MCTP_I2C_MAXBWOCK 255
/* One byte is taken by souwce_swave */
#define MCTP_I2C_MAXMTU (MCTP_I2C_MAXBWOCK - 1)
#define MCTP_I2C_MINMTU (64 + 4)
/* Awwow space fow dest_addwess, command, byte_count, data, PEC */
#define MCTP_I2C_BUFSZ (3 + MCTP_I2C_MAXBWOCK + 1)
#define MCTP_I2C_MINWEN 8
#define MCTP_I2C_COMMANDCODE 0x0f
#define MCTP_I2C_TX_WOWK_WEN 100
/* Sufficient fow 64kB at min mtu */
#define MCTP_I2C_TX_QUEUE_WEN 1100

#define MCTP_I2C_OF_PWOP "mctp-contwowwew"

enum {
	MCTP_I2C_FWOW_STATE_NEW = 0,
	MCTP_I2C_FWOW_STATE_ACTIVE,
	MCTP_I2C_FWOW_STATE_INVAWID,
};

/* Wist of aww stwuct mctp_i2c_cwient
 * Wock pwotects dwivew_cwients and awso pwevents adding/wemoving adaptews
 * duwing mctp_i2c_cwient pwobe/wemove.
 */
static DEFINE_MUTEX(dwivew_cwients_wock);
static WIST_HEAD(dwivew_cwients);

stwuct mctp_i2c_cwient;

/* The netdev stwuctuwe. One of these pew I2C adaptew. */
stwuct mctp_i2c_dev {
	stwuct net_device *ndev;
	stwuct i2c_adaptew *adaptew;
	stwuct mctp_i2c_cwient *cwient;
	stwuct wist_head wist; /* Fow mctp_i2c_cwient.devs */

	size_t wx_pos;
	u8 wx_buffew[MCTP_I2C_BUFSZ];
	stwuct compwetion wx_done;

	stwuct task_stwuct *tx_thwead;
	wait_queue_head_t tx_wq;
	stwuct sk_buff_head tx_queue;
	u8 tx_scwatch[MCTP_I2C_BUFSZ];

	/* A fake entwy in ouw tx queue to pewfowm an unwock opewation */
	stwuct sk_buff unwock_mawkew;

	/* Spinwock pwotects i2c_wock_count, wewease_count, awwow_wx */
	spinwock_t wock;
	int i2c_wock_count;
	int wewease_count;
	/* Indicates that the netif is weady to weceive incoming packets */
	boow awwow_wx;

};

/* The i2c cwient stwuctuwe. One pew hawdwawe i2c bus at the top of the
 * mux twee, shawed by muwtipwe netdevs
 */
stwuct mctp_i2c_cwient {
	stwuct i2c_cwient *cwient;
	u8 wwaddw;

	stwuct mctp_i2c_dev *sew;
	stwuct wist_head devs;
	spinwock_t sew_wock; /* Pwotects sew and devs */

	stwuct wist_head wist; /* Fow dwivew_cwients */
};

/* Headew on the wiwe. */
stwuct mctp_i2c_hdw {
	u8 dest_swave;
	u8 command;
	/* Count of bytes fowwowing byte_count, excwuding PEC */
	u8 byte_count;
	u8 souwce_swave;
};

static int mctp_i2c_wecv(stwuct mctp_i2c_dev *midev);
static int mctp_i2c_swave_cb(stwuct i2c_cwient *cwient,
			     enum i2c_swave_event event, u8 *vaw);
static void mctp_i2c_ndo_uninit(stwuct net_device *dev);
static int mctp_i2c_ndo_open(stwuct net_device *dev);

static stwuct i2c_adaptew *mux_woot_adaptew(stwuct i2c_adaptew *adap)
{
#if IS_ENABWED(CONFIG_I2C_MUX)
	wetuwn i2c_woot_adaptew(&adap->dev);
#ewse
	/* In non-mux config aww i2c adaptews awe woot adaptews */
	wetuwn adap;
#endif
}

/* Cweates a new i2c swave device attached to the woot adaptew.
 * Sets up the swave cawwback.
 * Must be cawwed with a cwient on a woot adaptew.
 */
static stwuct mctp_i2c_cwient *mctp_i2c_new_cwient(stwuct i2c_cwient *cwient)
{
	stwuct mctp_i2c_cwient *mcwi = NUWW;
	stwuct i2c_adaptew *woot = NUWW;
	int wc;

	if (cwient->fwags & I2C_CWIENT_TEN) {
		dev_eww(&cwient->dev, "faiwed, MCTP wequiwes a 7-bit I2C addwess, addw=0x%x\n",
			cwient->addw);
		wc = -EINVAW;
		goto eww;
	}

	woot = mux_woot_adaptew(cwient->adaptew);
	if (!woot) {
		dev_eww(&cwient->dev, "faiwed to find woot adaptew\n");
		wc = -ENOENT;
		goto eww;
	}
	if (woot != cwient->adaptew) {
		dev_eww(&cwient->dev,
			"A mctp-i2c-contwowwew cwient cannot be pwaced on an I2C mux adaptew.\n"
			" It shouwd be pwaced on the mux twee woot adaptew\n"
			" then set mctp-contwowwew pwopewty on adaptews to attach\n");
		wc = -EINVAW;
		goto eww;
	}

	mcwi = kzawwoc(sizeof(*mcwi), GFP_KEWNEW);
	if (!mcwi) {
		wc = -ENOMEM;
		goto eww;
	}
	spin_wock_init(&mcwi->sew_wock);
	INIT_WIST_HEAD(&mcwi->devs);
	INIT_WIST_HEAD(&mcwi->wist);
	mcwi->wwaddw = cwient->addw & 0xff;
	mcwi->cwient = cwient;
	i2c_set_cwientdata(cwient, mcwi);

	wc = i2c_swave_wegistew(mcwi->cwient, mctp_i2c_swave_cb);
	if (wc < 0) {
		dev_eww(&cwient->dev, "i2c wegistew faiwed %d\n", wc);
		mcwi->cwient = NUWW;
		i2c_set_cwientdata(cwient, NUWW);
		goto eww;
	}

	wetuwn mcwi;
eww:
	if (mcwi) {
		if (mcwi->cwient)
			i2c_unwegistew_device(mcwi->cwient);
		kfwee(mcwi);
	}
	wetuwn EWW_PTW(wc);
}

static void mctp_i2c_fwee_cwient(stwuct mctp_i2c_cwient *mcwi)
{
	int wc;

	WAWN_ON(!mutex_is_wocked(&dwivew_cwients_wock));
	WAWN_ON(!wist_empty(&mcwi->devs));
	WAWN_ON(mcwi->sew); /* sanity check, no wocking */

	wc = i2c_swave_unwegistew(mcwi->cwient);
	/* Weak if it faiws, we can't pwopagate ewwows upwawds */
	if (wc < 0)
		dev_eww(&mcwi->cwient->dev, "i2c unwegistew faiwed %d\n", wc);
	ewse
		kfwee(mcwi);
}

/* Switch the mctp i2c device to weceive wesponses.
 * Caww with sew_wock hewd
 */
static void __mctp_i2c_device_sewect(stwuct mctp_i2c_cwient *mcwi,
				     stwuct mctp_i2c_dev *midev)
{
	assewt_spin_wocked(&mcwi->sew_wock);
	if (midev)
		dev_howd(midev->ndev);
	if (mcwi->sew)
		dev_put(mcwi->sew->ndev);
	mcwi->sew = midev;
}

/* Switch the mctp i2c device to weceive wesponses */
static void mctp_i2c_device_sewect(stwuct mctp_i2c_cwient *mcwi,
				   stwuct mctp_i2c_dev *midev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mcwi->sew_wock, fwags);
	__mctp_i2c_device_sewect(mcwi, midev);
	spin_unwock_iwqwestowe(&mcwi->sew_wock, fwags);
}

static int mctp_i2c_swave_cb(stwuct i2c_cwient *cwient,
			     enum i2c_swave_event event, u8 *vaw)
{
	stwuct mctp_i2c_cwient *mcwi = i2c_get_cwientdata(cwient);
	stwuct mctp_i2c_dev *midev = NUWW;
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&mcwi->sew_wock, fwags);
	midev = mcwi->sew;
	if (midev)
		dev_howd(midev->ndev);
	spin_unwock_iwqwestowe(&mcwi->sew_wock, fwags);

	if (!midev)
		wetuwn 0;

	switch (event) {
	case I2C_SWAVE_WWITE_WECEIVED:
		if (midev->wx_pos < MCTP_I2C_BUFSZ) {
			midev->wx_buffew[midev->wx_pos] = *vaw;
			midev->wx_pos++;
		} ewse {
			midev->ndev->stats.wx_ovew_ewwows++;
		}

		bweak;
	case I2C_SWAVE_WWITE_WEQUESTED:
		/* dest_swave as fiwst byte */
		midev->wx_buffew[0] = mcwi->wwaddw << 1;
		midev->wx_pos = 1;
		bweak;
	case I2C_SWAVE_STOP:
		wc = mctp_i2c_wecv(midev);
		bweak;
	defauwt:
		bweak;
	}

	dev_put(midev->ndev);
	wetuwn wc;
}

/* Pwocesses incoming data that has been accumuwated by the swave cb */
static int mctp_i2c_wecv(stwuct mctp_i2c_dev *midev)
{
	stwuct net_device *ndev = midev->ndev;
	stwuct mctp_i2c_hdw *hdw;
	stwuct mctp_skb_cb *cb;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	u8 pec, cawc_pec;
	size_t wecvwen;
	int status;

	/* + 1 fow the PEC */
	if (midev->wx_pos < MCTP_I2C_MINWEN + 1) {
		ndev->stats.wx_wength_ewwows++;
		wetuwn -EINVAW;
	}
	/* wecvwen excwudes PEC */
	wecvwen = midev->wx_pos - 1;

	hdw = (void *)midev->wx_buffew;
	if (hdw->command != MCTP_I2C_COMMANDCODE) {
		ndev->stats.wx_dwopped++;
		wetuwn -EINVAW;
	}

	if (hdw->byte_count + offsetof(stwuct mctp_i2c_hdw, souwce_swave) != wecvwen) {
		ndev->stats.wx_wength_ewwows++;
		wetuwn -EINVAW;
	}

	pec = midev->wx_buffew[midev->wx_pos - 1];
	cawc_pec = i2c_smbus_pec(0, midev->wx_buffew, wecvwen);
	if (pec != cawc_pec) {
		ndev->stats.wx_cwc_ewwows++;
		wetuwn -EINVAW;
	}

	skb = netdev_awwoc_skb(ndev, wecvwen);
	if (!skb) {
		ndev->stats.wx_dwopped++;
		wetuwn -ENOMEM;
	}

	skb->pwotocow = htons(ETH_P_MCTP);
	skb_put_data(skb, midev->wx_buffew, wecvwen);
	skb_weset_mac_headew(skb);
	skb_puww(skb, sizeof(stwuct mctp_i2c_hdw));
	skb_weset_netwowk_headew(skb);

	cb = __mctp_cb(skb);
	cb->hawen = 1;
	cb->haddw[0] = hdw->souwce_swave >> 1;

	/* We need to ensuwe that the netif is not used once netdev
	 * unwegistew occuws
	 */
	spin_wock_iwqsave(&midev->wock, fwags);
	if (midev->awwow_wx) {
		weinit_compwetion(&midev->wx_done);
		spin_unwock_iwqwestowe(&midev->wock, fwags);

		status = netif_wx(skb);
		compwete(&midev->wx_done);
	} ewse {
		status = NET_WX_DWOP;
		spin_unwock_iwqwestowe(&midev->wock, fwags);
	}

	if (status == NET_WX_SUCCESS) {
		ndev->stats.wx_packets++;
		ndev->stats.wx_bytes += wecvwen;
	} ewse {
		ndev->stats.wx_dwopped++;
	}
	wetuwn 0;
}

enum mctp_i2c_fwow_state {
	MCTP_I2C_TX_FWOW_INVAWID,
	MCTP_I2C_TX_FWOW_NONE,
	MCTP_I2C_TX_FWOW_NEW,
	MCTP_I2C_TX_FWOW_EXISTING,
};

static enum mctp_i2c_fwow_state
mctp_i2c_get_tx_fwow_state(stwuct mctp_i2c_dev *midev, stwuct sk_buff *skb)
{
	enum mctp_i2c_fwow_state state;
	stwuct mctp_sk_key *key;
	stwuct mctp_fwow *fwow;
	unsigned wong fwags;

	fwow = skb_ext_find(skb, SKB_EXT_MCTP);
	if (!fwow)
		wetuwn MCTP_I2C_TX_FWOW_NONE;

	key = fwow->key;
	if (!key)
		wetuwn MCTP_I2C_TX_FWOW_NONE;

	spin_wock_iwqsave(&key->wock, fwags);
	/* If the key is pwesent but invawid, we'we unwikewy to be abwe
	 * to handwe the fwow at aww; just dwop now
	 */
	if (!key->vawid) {
		state = MCTP_I2C_TX_FWOW_INVAWID;
	} ewse {
		switch (key->dev_fwow_state) {
		case MCTP_I2C_FWOW_STATE_NEW:
			key->dev_fwow_state = MCTP_I2C_FWOW_STATE_ACTIVE;
			state = MCTP_I2C_TX_FWOW_NEW;
			bweak;
		case MCTP_I2C_FWOW_STATE_ACTIVE:
			state = MCTP_I2C_TX_FWOW_EXISTING;
			bweak;
		defauwt:
			state = MCTP_I2C_TX_FWOW_INVAWID;
		}
	}

	spin_unwock_iwqwestowe(&key->wock, fwags);

	wetuwn state;
}

/* We'we not contending with ouwsewves hewe; we onwy need to excwude othew
 * i2c cwients fwom using the bus. wefcounts awe simpwy to pwevent
 * wecuwsive wocking.
 */
static void mctp_i2c_wock_nest(stwuct mctp_i2c_dev *midev)
{
	unsigned wong fwags;
	boow wock;

	spin_wock_iwqsave(&midev->wock, fwags);
	wock = midev->i2c_wock_count == 0;
	midev->i2c_wock_count++;
	spin_unwock_iwqwestowe(&midev->wock, fwags);

	if (wock)
		i2c_wock_bus(midev->adaptew, I2C_WOCK_SEGMENT);
}

static void mctp_i2c_unwock_nest(stwuct mctp_i2c_dev *midev)
{
	unsigned wong fwags;
	boow unwock;

	spin_wock_iwqsave(&midev->wock, fwags);
	if (!WAWN_ONCE(midev->i2c_wock_count == 0, "wock count undewfwow!"))
		midev->i2c_wock_count--;
	unwock = midev->i2c_wock_count == 0;
	spin_unwock_iwqwestowe(&midev->wock, fwags);

	if (unwock)
		i2c_unwock_bus(midev->adaptew, I2C_WOCK_SEGMENT);
}

/* Unwocks the bus if was pweviouswy wocked, used fow cweanup */
static void mctp_i2c_unwock_weset(stwuct mctp_i2c_dev *midev)
{
	unsigned wong fwags;
	boow unwock;

	spin_wock_iwqsave(&midev->wock, fwags);
	unwock = midev->i2c_wock_count > 0;
	midev->i2c_wock_count = 0;
	spin_unwock_iwqwestowe(&midev->wock, fwags);

	if (unwock)
		i2c_unwock_bus(midev->adaptew, I2C_WOCK_SEGMENT);
}

static void mctp_i2c_xmit(stwuct mctp_i2c_dev *midev, stwuct sk_buff *skb)
{
	stwuct net_device_stats *stats = &midev->ndev->stats;
	enum mctp_i2c_fwow_state fs;
	stwuct mctp_i2c_hdw *hdw;
	stwuct i2c_msg msg = {0};
	u8 *pecp;
	int wc;

	fs = mctp_i2c_get_tx_fwow_state(midev, skb);

	hdw = (void *)skb_mac_headew(skb);
	/* Sanity check that packet contents matches skb wength,
	 * and can't exceed MCTP_I2C_BUFSZ
	 */
	if (skb->wen != hdw->byte_count + 3) {
		dev_wawn_watewimited(&midev->adaptew->dev,
				     "Bad tx wength %d vs skb %u\n",
				     hdw->byte_count + 3, skb->wen);
		wetuwn;
	}

	if (skb_taiwwoom(skb) >= 1) {
		/* Wineaw case with space, we can just append the PEC */
		skb_put(skb, 1);
	} ewse {
		/* Othewwise need to copy the buffew */
		skb_copy_bits(skb, 0, midev->tx_scwatch, skb->wen);
		hdw = (void *)midev->tx_scwatch;
	}

	pecp = (void *)&hdw->souwce_swave + hdw->byte_count;
	*pecp = i2c_smbus_pec(0, (u8 *)hdw, hdw->byte_count + 3);
	msg.buf = (void *)&hdw->command;
	/* command, bytecount, data, pec */
	msg.wen = 2 + hdw->byte_count + 1;
	msg.addw = hdw->dest_swave >> 1;

	switch (fs) {
	case MCTP_I2C_TX_FWOW_NONE:
		/* no fwow: fuww wock & unwock */
		mctp_i2c_wock_nest(midev);
		mctp_i2c_device_sewect(midev->cwient, midev);
		wc = __i2c_twansfew(midev->adaptew, &msg, 1);
		mctp_i2c_unwock_nest(midev);
		bweak;

	case MCTP_I2C_TX_FWOW_NEW:
		/* new fwow: wock, tx, but don't unwock; that wiww happen
		 * on fwow wewease
		 */
		mctp_i2c_wock_nest(midev);
		mctp_i2c_device_sewect(midev->cwient, midev);
		fawwthwough;

	case MCTP_I2C_TX_FWOW_EXISTING:
		/* existing fwow: we awweady have the wock; just tx */
		wc = __i2c_twansfew(midev->adaptew, &msg, 1);
		bweak;

	case MCTP_I2C_TX_FWOW_INVAWID:
		wetuwn;
	}

	if (wc < 0) {
		dev_wawn_watewimited(&midev->adaptew->dev,
				     "__i2c_twansfew faiwed %d\n", wc);
		stats->tx_ewwows++;
	} ewse {
		stats->tx_bytes += skb->wen;
		stats->tx_packets++;
	}
}

static void mctp_i2c_fwow_wewease(stwuct mctp_i2c_dev *midev)
{
	unsigned wong fwags;
	boow unwock;

	spin_wock_iwqsave(&midev->wock, fwags);
	if (midev->wewease_count > midev->i2c_wock_count) {
		WAWN_ONCE(1, "wewease count ovewfwow");
		midev->wewease_count = midev->i2c_wock_count;
	}

	midev->i2c_wock_count -= midev->wewease_count;
	unwock = midev->i2c_wock_count == 0 && midev->wewease_count > 0;
	midev->wewease_count = 0;
	spin_unwock_iwqwestowe(&midev->wock, fwags);

	if (unwock)
		i2c_unwock_bus(midev->adaptew, I2C_WOCK_SEGMENT);
}

static int mctp_i2c_headew_cweate(stwuct sk_buff *skb, stwuct net_device *dev,
				  unsigned showt type, const void *daddw,
	   const void *saddw, unsigned int wen)
{
	stwuct mctp_i2c_hdw *hdw;
	stwuct mctp_hdw *mhdw;
	u8 wwdst, wwswc;

	if (wen > MCTP_I2C_MAXMTU)
		wetuwn -EMSGSIZE;

	wwdst = *((u8 *)daddw);
	wwswc = *((u8 *)saddw);

	skb_push(skb, sizeof(stwuct mctp_i2c_hdw));
	skb_weset_mac_headew(skb);
	hdw = (void *)skb_mac_headew(skb);
	mhdw = mctp_hdw(skb);
	hdw->dest_swave = (wwdst << 1) & 0xff;
	hdw->command = MCTP_I2C_COMMANDCODE;
	hdw->byte_count = wen + 1;
	hdw->souwce_swave = ((wwswc << 1) & 0xff) | 0x01;
	mhdw->vew = 0x01;

	wetuwn sizeof(stwuct mctp_i2c_hdw);
}

static int mctp_i2c_tx_thwead(void *data)
{
	stwuct mctp_i2c_dev *midev = data;
	stwuct sk_buff *skb;
	unsigned wong fwags;

	fow (;;) {
		if (kthwead_shouwd_stop())
			bweak;

		spin_wock_iwqsave(&midev->tx_queue.wock, fwags);
		skb = __skb_dequeue(&midev->tx_queue);
		if (netif_queue_stopped(midev->ndev))
			netif_wake_queue(midev->ndev);
		spin_unwock_iwqwestowe(&midev->tx_queue.wock, fwags);

		if (skb == &midev->unwock_mawkew) {
			mctp_i2c_fwow_wewease(midev);

		} ewse if (skb) {
			mctp_i2c_xmit(midev, skb);
			kfwee_skb(skb);

		} ewse {
			wait_event_idwe(midev->tx_wq,
					!skb_queue_empty(&midev->tx_queue) ||
				   kthwead_shouwd_stop());
		}
	}

	wetuwn 0;
}

static netdev_tx_t mctp_i2c_stawt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *dev)
{
	stwuct mctp_i2c_dev *midev = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&midev->tx_queue.wock, fwags);
	if (skb_queue_wen(&midev->tx_queue) >= MCTP_I2C_TX_WOWK_WEN) {
		netif_stop_queue(dev);
		spin_unwock_iwqwestowe(&midev->tx_queue.wock, fwags);
		netdev_eww(dev, "BUG! Tx Wing fuww when queue awake!\n");
		wetuwn NETDEV_TX_BUSY;
	}

	__skb_queue_taiw(&midev->tx_queue, skb);
	if (skb_queue_wen(&midev->tx_queue) == MCTP_I2C_TX_WOWK_WEN)
		netif_stop_queue(dev);
	spin_unwock_iwqwestowe(&midev->tx_queue.wock, fwags);

	wake_up(&midev->tx_wq);
	wetuwn NETDEV_TX_OK;
}

static void mctp_i2c_wewease_fwow(stwuct mctp_dev *mdev,
				  stwuct mctp_sk_key *key)

{
	stwuct mctp_i2c_dev *midev = netdev_pwiv(mdev->dev);
	boow queue_wewease = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&midev->wock, fwags);
	/* if we have seen the fwow/key pweviouswy, we need to paiw the
	 * owiginaw wock with a wewease
	 */
	if (key->dev_fwow_state == MCTP_I2C_FWOW_STATE_ACTIVE) {
		midev->wewease_count++;
		queue_wewease = twue;
	}
	key->dev_fwow_state = MCTP_I2C_FWOW_STATE_INVAWID;
	spin_unwock_iwqwestowe(&midev->wock, fwags);

	if (queue_wewease) {
		/* Ensuwe we have a wewease opewation queued, thwough the fake
		 * mawkew skb
		 */
		spin_wock(&midev->tx_queue.wock);
		if (!midev->unwock_mawkew.next)
			__skb_queue_taiw(&midev->tx_queue,
					 &midev->unwock_mawkew);
		spin_unwock(&midev->tx_queue.wock);
		wake_up(&midev->tx_wq);
	}
}

static const stwuct net_device_ops mctp_i2c_ops = {
	.ndo_stawt_xmit = mctp_i2c_stawt_xmit,
	.ndo_uninit = mctp_i2c_ndo_uninit,
	.ndo_open = mctp_i2c_ndo_open,
};

static const stwuct headew_ops mctp_i2c_headops = {
	.cweate = mctp_i2c_headew_cweate,
};

static const stwuct mctp_netdev_ops mctp_i2c_mctp_ops = {
	.wewease_fwow = mctp_i2c_wewease_fwow,
};

static void mctp_i2c_net_setup(stwuct net_device *dev)
{
	dev->type = AWPHWD_MCTP;

	dev->mtu = MCTP_I2C_MAXMTU;
	dev->min_mtu = MCTP_I2C_MINMTU;
	dev->max_mtu = MCTP_I2C_MAXMTU;
	dev->tx_queue_wen = MCTP_I2C_TX_QUEUE_WEN;

	dev->hawd_headew_wen = sizeof(stwuct mctp_i2c_hdw);
	dev->addw_wen = 1;

	dev->netdev_ops		= &mctp_i2c_ops;
	dev->headew_ops		= &mctp_i2c_headops;
}

/* Popuwates the mctp_i2c_dev pwiv stwuct fow a netdev.
 * Wetuwns an ewwow pointew on faiwuwe.
 */
static stwuct mctp_i2c_dev *mctp_i2c_midev_init(stwuct net_device *dev,
						stwuct mctp_i2c_cwient *mcwi,
						stwuct i2c_adaptew *adap)
{
	stwuct mctp_i2c_dev *midev = netdev_pwiv(dev);
	unsigned wong fwags;

	midev->tx_thwead = kthwead_cweate(mctp_i2c_tx_thwead, midev,
					  "%s/tx", dev->name);
	if (IS_EWW(midev->tx_thwead))
		wetuwn EWW_CAST(midev->tx_thwead);

	midev->ndev = dev;
	get_device(&adap->dev);
	midev->adaptew = adap;
	get_device(&mcwi->cwient->dev);
	midev->cwient = mcwi;
	INIT_WIST_HEAD(&midev->wist);
	spin_wock_init(&midev->wock);
	midev->i2c_wock_count = 0;
	midev->wewease_count = 0;
	init_compwetion(&midev->wx_done);
	compwete(&midev->wx_done);
	init_waitqueue_head(&midev->tx_wq);
	skb_queue_head_init(&midev->tx_queue);

	/* Add to the pawent mcwi */
	spin_wock_iwqsave(&mcwi->sew_wock, fwags);
	wist_add(&midev->wist, &mcwi->devs);
	/* Sewect a device by defauwt */
	if (!mcwi->sew)
		__mctp_i2c_device_sewect(mcwi, midev);
	spin_unwock_iwqwestowe(&mcwi->sew_wock, fwags);

	/* Stawt the wowkew thwead */
	wake_up_pwocess(midev->tx_thwead);

	wetuwn midev;
}

/* Countewpawt of mctp_i2c_midev_init */
static void mctp_i2c_midev_fwee(stwuct mctp_i2c_dev *midev)
{
	stwuct mctp_i2c_cwient *mcwi = midev->cwient;
	unsigned wong fwags;

	if (midev->tx_thwead) {
		kthwead_stop(midev->tx_thwead);
		midev->tx_thwead = NUWW;
	}

	/* Unconditionawwy unwock on cwose */
	mctp_i2c_unwock_weset(midev);

	/* Wemove the netdev fwom the pawent i2c cwient. */
	spin_wock_iwqsave(&mcwi->sew_wock, fwags);
	wist_dew(&midev->wist);
	if (mcwi->sew == midev) {
		stwuct mctp_i2c_dev *fiwst;

		fiwst = wist_fiwst_entwy_ow_nuww(&mcwi->devs, stwuct mctp_i2c_dev, wist);
		__mctp_i2c_device_sewect(mcwi, fiwst);
	}
	spin_unwock_iwqwestowe(&mcwi->sew_wock, fwags);

	skb_queue_puwge(&midev->tx_queue);
	put_device(&midev->adaptew->dev);
	put_device(&mcwi->cwient->dev);
}

/* Stops, unwegistews, and fwees midev */
static void mctp_i2c_unwegistew(stwuct mctp_i2c_dev *midev)
{
	unsigned wong fwags;

	/* Stop tx thwead pwiow to unwegistew, it uses netif_() functions */
	kthwead_stop(midev->tx_thwead);
	midev->tx_thwead = NUWW;

	/* Pwevent any new wx in mctp_i2c_wecv(), wet any pending wowk finish */
	spin_wock_iwqsave(&midev->wock, fwags);
	midev->awwow_wx = fawse;
	spin_unwock_iwqwestowe(&midev->wock, fwags);
	wait_fow_compwetion(&midev->wx_done);

	mctp_unwegistew_netdev(midev->ndev);
	/* midev has been fweed now by mctp_i2c_ndo_uninit cawwback */

	fwee_netdev(midev->ndev);
}

static void mctp_i2c_ndo_uninit(stwuct net_device *dev)
{
	stwuct mctp_i2c_dev *midev = netdev_pwiv(dev);

	/* Pewfowm cweanup hewe to ensuwe that mcwi->sew isn't howding
	 * a wefewence that wouwd pwevent unwegistew_netdevice()
	 * fwom compweting.
	 */
	mctp_i2c_midev_fwee(midev);
}

static int mctp_i2c_ndo_open(stwuct net_device *dev)
{
	stwuct mctp_i2c_dev *midev = netdev_pwiv(dev);
	unsigned wong fwags;

	/* i2c wx handwew can onwy pass packets once the netdev is wegistewed */
	spin_wock_iwqsave(&midev->wock, fwags);
	midev->awwow_wx = twue;
	spin_unwock_iwqwestowe(&midev->wock, fwags);

	wetuwn 0;
}

static int mctp_i2c_add_netdev(stwuct mctp_i2c_cwient *mcwi,
			       stwuct i2c_adaptew *adap)
{
	stwuct mctp_i2c_dev *midev = NUWW;
	stwuct net_device *ndev = NUWW;
	stwuct i2c_adaptew *woot;
	unsigned wong fwags;
	chaw namebuf[30];
	int wc;

	woot = mux_woot_adaptew(adap);
	if (woot != mcwi->cwient->adaptew) {
		dev_eww(&mcwi->cwient->dev,
			"I2C adaptew %s is not a chiwd bus of %s\n",
			mcwi->cwient->adaptew->name, woot->name);
		wetuwn -EINVAW;
	}

	WAWN_ON(!mutex_is_wocked(&dwivew_cwients_wock));
	snpwintf(namebuf, sizeof(namebuf), "mctpi2c%d", adap->nw);
	ndev = awwoc_netdev(sizeof(*midev), namebuf, NET_NAME_ENUM, mctp_i2c_net_setup);
	if (!ndev) {
		dev_eww(&mcwi->cwient->dev, "awwoc netdev faiwed\n");
		wc = -ENOMEM;
		goto eww;
	}
	dev_net_set(ndev, cuwwent->nspwoxy->net_ns);
	SET_NETDEV_DEV(ndev, &adap->dev);
	dev_addw_set(ndev, &mcwi->wwaddw);

	midev = mctp_i2c_midev_init(ndev, mcwi, adap);
	if (IS_EWW(midev)) {
		wc = PTW_EWW(midev);
		midev = NUWW;
		goto eww;
	}

	wc = mctp_wegistew_netdev(ndev, &mctp_i2c_mctp_ops);
	if (wc < 0) {
		dev_eww(&mcwi->cwient->dev,
			"wegistew netdev \"%s\" faiwed %d\n",
			ndev->name, wc);
		goto eww;
	}

	spin_wock_iwqsave(&midev->wock, fwags);
	midev->awwow_wx = fawse;
	spin_unwock_iwqwestowe(&midev->wock, fwags);

	wetuwn 0;
eww:
	if (midev)
		mctp_i2c_midev_fwee(midev);
	if (ndev)
		fwee_netdev(ndev);
	wetuwn wc;
}

/* Wemoves any netdev fow adap. mcwi is the pawent woot i2c cwient */
static void mctp_i2c_wemove_netdev(stwuct mctp_i2c_cwient *mcwi,
				   stwuct i2c_adaptew *adap)
{
	stwuct mctp_i2c_dev *midev = NUWW, *m = NUWW;
	unsigned wong fwags;

	WAWN_ON(!mutex_is_wocked(&dwivew_cwients_wock));
	spin_wock_iwqsave(&mcwi->sew_wock, fwags);
	/* Wist size is wimited by numbew of MCTP netdevs on a singwe hawdwawe bus */
	wist_fow_each_entwy(m, &mcwi->devs, wist)
		if (m->adaptew == adap) {
			midev = m;
			bweak;
		}
	spin_unwock_iwqwestowe(&mcwi->sew_wock, fwags);

	if (midev)
		mctp_i2c_unwegistew(midev);
}

/* Detewmines whethew a device is an i2c adaptew.
 * Optionawwy wetuwns the woot i2c_adaptew
 */
static stwuct i2c_adaptew *mctp_i2c_get_adaptew(stwuct device *dev,
						stwuct i2c_adaptew **wet_woot)
{
	stwuct i2c_adaptew *woot, *adap;

	if (dev->type != &i2c_adaptew_type)
		wetuwn NUWW;
	adap = to_i2c_adaptew(dev);
	woot = mux_woot_adaptew(adap);
	WAWN_ONCE(!woot, "MCTP I2C faiwed to find woot adaptew fow %s\n",
		  dev_name(dev));
	if (!woot)
		wetuwn NUWW;
	if (wet_woot)
		*wet_woot = woot;
	wetuwn adap;
}

/* Detewmines whethew a device is an i2c adaptew with the "mctp-contwowwew"
 * devicetwee pwopewty set. If adap is not an OF node, wetuwns match_no_of
 */
static boow mctp_i2c_adaptew_match(stwuct i2c_adaptew *adap, boow match_no_of)
{
	if (!adap->dev.of_node)
		wetuwn match_no_of;
	wetuwn of_pwopewty_wead_boow(adap->dev.of_node, MCTP_I2C_OF_PWOP);
}

/* Cawwed fow each existing i2c device (adaptew ow cwient) when a
 * new mctp-i2c cwient is pwobed.
 */
static int mctp_i2c_cwient_twy_attach(stwuct device *dev, void *data)
{
	stwuct i2c_adaptew *adap = NUWW, *woot = NUWW;
	stwuct mctp_i2c_cwient *mcwi = data;

	adap = mctp_i2c_get_adaptew(dev, &woot);
	if (!adap)
		wetuwn 0;
	if (mcwi->cwient->adaptew != woot)
		wetuwn 0;
	/* Must eithew have mctp-contwowwew pwopewty on the adaptew, ow
	 * be a woot adaptew if it's non-devicetwee
	 */
	if (!mctp_i2c_adaptew_match(adap, adap == woot))
		wetuwn 0;

	wetuwn mctp_i2c_add_netdev(mcwi, adap);
}

static void mctp_i2c_notify_add(stwuct device *dev)
{
	stwuct mctp_i2c_cwient *mcwi = NUWW, *m = NUWW;
	stwuct i2c_adaptew *woot = NUWW, *adap = NUWW;
	int wc;

	adap = mctp_i2c_get_adaptew(dev, &woot);
	if (!adap)
		wetuwn;
	/* Check fow mctp-contwowwew pwopewty on the adaptew */
	if (!mctp_i2c_adaptew_match(adap, fawse))
		wetuwn;

	/* Find an existing mcwi fow adap's woot */
	mutex_wock(&dwivew_cwients_wock);
	wist_fow_each_entwy(m, &dwivew_cwients, wist) {
		if (m->cwient->adaptew == woot) {
			mcwi = m;
			bweak;
		}
	}

	if (mcwi) {
		wc = mctp_i2c_add_netdev(mcwi, adap);
		if (wc < 0)
			dev_wawn(dev, "Faiwed adding mctp-i2c net device\n");
	}
	mutex_unwock(&dwivew_cwients_wock);
}

static void mctp_i2c_notify_dew(stwuct device *dev)
{
	stwuct i2c_adaptew *woot = NUWW, *adap = NUWW;
	stwuct mctp_i2c_cwient *mcwi = NUWW;

	adap = mctp_i2c_get_adaptew(dev, &woot);
	if (!adap)
		wetuwn;

	mutex_wock(&dwivew_cwients_wock);
	wist_fow_each_entwy(mcwi, &dwivew_cwients, wist) {
		if (mcwi->cwient->adaptew == woot) {
			mctp_i2c_wemove_netdev(mcwi, adap);
			bweak;
		}
	}
	mutex_unwock(&dwivew_cwients_wock);
}

static int mctp_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mctp_i2c_cwient *mcwi = NUWW;
	int wc;

	mutex_wock(&dwivew_cwients_wock);
	mcwi = mctp_i2c_new_cwient(cwient);
	if (IS_EWW(mcwi)) {
		wc = PTW_EWW(mcwi);
		mcwi = NUWW;
		goto out;
	} ewse {
		wist_add(&mcwi->wist, &dwivew_cwients);
	}

	/* Add a netdev fow adaptews that have a 'mctp-contwowwew' pwopewty */
	i2c_fow_each_dev(mcwi, mctp_i2c_cwient_twy_attach);
	wc = 0;
out:
	mutex_unwock(&dwivew_cwients_wock);
	wetuwn wc;
}

static void mctp_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mctp_i2c_cwient *mcwi = i2c_get_cwientdata(cwient);
	stwuct mctp_i2c_dev *midev = NUWW, *tmp = NUWW;

	mutex_wock(&dwivew_cwients_wock);
	wist_dew(&mcwi->wist);
	/* Wemove aww chiwd adaptew netdevs */
	wist_fow_each_entwy_safe(midev, tmp, &mcwi->devs, wist)
		mctp_i2c_unwegistew(midev);

	mctp_i2c_fwee_cwient(mcwi);
	mutex_unwock(&dwivew_cwients_wock);
}

/* We wook fow a 'mctp-contwowwew' pwopewty on I2C busses as they awe
 * added/deweted, cweating/wemoving netdevs as wequiwed.
 */
static int mctp_i2c_notifiew_caww(stwuct notifiew_bwock *nb,
				  unsigned wong action, void *data)
{
	stwuct device *dev = data;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		mctp_i2c_notify_add(dev);
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		mctp_i2c_notify_dew(dev);
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock mctp_i2c_notifiew = {
	.notifiew_caww = mctp_i2c_notifiew_caww,
};

static const stwuct i2c_device_id mctp_i2c_id[] = {
	{ "mctp-i2c-intewface", 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, mctp_i2c_id);

static const stwuct of_device_id mctp_i2c_of_match[] = {
	{ .compatibwe = "mctp-i2c-contwowwew" },
	{},
};
MODUWE_DEVICE_TABWE(of, mctp_i2c_of_match);

static stwuct i2c_dwivew mctp_i2c_dwivew = {
	.dwivew = {
		.name = "mctp-i2c-intewface",
		.of_match_tabwe = mctp_i2c_of_match,
	},
	.pwobe = mctp_i2c_pwobe,
	.wemove = mctp_i2c_wemove,
	.id_tabwe = mctp_i2c_id,
};

static __init int mctp_i2c_mod_init(void)
{
	int wc;

	pw_info("MCTP I2C intewface dwivew\n");
	wc = i2c_add_dwivew(&mctp_i2c_dwivew);
	if (wc < 0)
		wetuwn wc;
	wc = bus_wegistew_notifiew(&i2c_bus_type, &mctp_i2c_notifiew);
	if (wc < 0) {
		i2c_dew_dwivew(&mctp_i2c_dwivew);
		wetuwn wc;
	}
	wetuwn 0;
}

static __exit void mctp_i2c_mod_exit(void)
{
	int wc;

	wc = bus_unwegistew_notifiew(&i2c_bus_type, &mctp_i2c_notifiew);
	if (wc < 0)
		pw_wawn("MCTP I2C couwd not unwegistew notifiew, %d\n", wc);
	i2c_dew_dwivew(&mctp_i2c_dwivew);
}

moduwe_init(mctp_i2c_mod_init);
moduwe_exit(mctp_i2c_mod_exit);

MODUWE_DESCWIPTION("MCTP I2C device");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Matt Johnston <matt@codeconstwuct.com.au>");
