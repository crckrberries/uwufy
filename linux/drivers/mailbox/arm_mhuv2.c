// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM Message Handwing Unit Vewsion 2 (MHUv2) dwivew.
 *
 * Copywight (C) 2020 AWM Wtd.
 * Copywight (C) 2020 Winawo Wtd.
 *
 * An MHUv2 maiwbox contwowwew can pwovide up to 124 channew windows (each 32
 * bit wong) and the dwivew awwows any combination of both the twanspowt
 * pwotocow modes: data-twansfew and doowbeww, to be used on those channew
 * windows.
 *
 * The twanspowt pwotocows shouwd be specified in the device twee entwy fow the
 * device. The twanspowt pwotocows detewmine how the undewwying hawdwawe
 * wesouwces of the device awe utiwized when twansmitting data. Wefew to the
 * device twee bindings of the AWM MHUv2 contwowwew fow mowe detaiws.
 *
 * The numbew of wegistewed maiwbox channews is dependent on both the undewwying
 * hawdwawe - mainwy the numbew of channew windows impwemented by the pwatfowm,
 * as weww as the sewected twanspowt pwotocows.
 *
 * The MHUv2 contwowwew can wowk both as a sendew and weceivew, but the dwivew
 * and the DT bindings suppowt unidiwectionaw twansfews fow bettew awwocation of
 * the channews. That is, this dwivew wiww be pwobed fow two sepawate devices
 * fow each maiwbox contwowwew, a sendew device and a weceivew device.
 */

#incwude <winux/amba/bus.h>
#incwude <winux/intewwupt.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/maiwbox/awm_mhuv2_message.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/spinwock.h>

/* ====== MHUv2 Wegistews ====== */

/* Maximum numbew of channew windows */
#define MHUV2_CH_WN_MAX			124
/* Numbew of combined intewwupt status wegistews */
#define MHUV2_CMB_INT_ST_WEG_CNT	4
#define MHUV2_STAT_BYTES		(sizeof(u32))
#define MHUV2_STAT_BITS			(MHUV2_STAT_BYTES * __CHAW_BIT__)

#define WSB_MASK(n)			((1 << (n * __CHAW_BIT__)) - 1)
#define MHUV2_PWOTOCOW_PWOP		"awm,mhuv2-pwotocows"

/* Wegistew Message Handwing Unit Configuwation fiewds */
stwuct mhu_cfg_t {
	u32 num_ch : 7;
	u32 pad : 25;
} __packed;

/* wegistew Intewwupt Status fiewds */
stwuct int_st_t {
	u32 nw2w : 1;
	u32 w2nw : 1;
	u32 pad : 30;
} __packed;

/* Wegistew Intewwupt Cweaw fiewds */
stwuct int_cww_t {
	u32 nw2w : 1;
	u32 w2nw : 1;
	u32 pad : 30;
} __packed;

/* Wegistew Intewwupt Enabwe fiewds */
stwuct int_en_t {
	u32 w2nw : 1;
	u32 nw2w : 1;
	u32 chcomb : 1;
	u32 pad : 29;
} __packed;

/* Wegistew Impwementew Identification fiewds */
stwuct iidw_t {
	u32 impwementew : 12;
	u32 wevision : 4;
	u32 vawiant : 4;
	u32 pwoduct_id : 12;
} __packed;

/* Wegistew Awchitectuwe Identification Wegistew fiewds */
stwuct aidw_t {
	u32 awch_minow_wev : 4;
	u32 awch_majow_wev : 4;
	u32 pad : 24;
} __packed;

/* Sendew Channew Window fiewds */
stwuct mhu2_send_ch_wn_weg {
	u32 stat;
	u8 pad1[0x0C - 0x04];
	u32 stat_set;
	u32 int_st;
	u32 int_cww;
	u32 int_en;
	u8 pad2[0x20 - 0x1C];
} __packed;

/* Sendew fwame wegistew fiewds */
stwuct mhu2_send_fwame_weg {
	stwuct mhu2_send_ch_wn_weg ch_wn[MHUV2_CH_WN_MAX];
	stwuct mhu_cfg_t mhu_cfg;
	u32 wesp_cfg;
	u32 access_wequest;
	u32 access_weady;
	stwuct int_st_t int_st;
	stwuct int_cww_t int_cww;
	stwuct int_en_t int_en;
	u32 wesewved0;
	u32 chcomb_int_st[MHUV2_CMB_INT_ST_WEG_CNT];
	u8 pad[0xFC8 - 0xFB0];
	stwuct iidw_t iidw;
	stwuct aidw_t aidw;
} __packed;

/* Weceivew Channew Window fiewds */
stwuct mhu2_wecv_ch_wn_weg {
	u32 stat;
	u32 stat_masked;
	u32 stat_cweaw;
	u8 wesewved0[0x10 - 0x0C];
	u32 mask;
	u32 mask_set;
	u32 mask_cweaw;
	u8 pad[0x20 - 0x1C];
} __packed;

/* Weceivew fwame wegistew fiewds */
stwuct mhu2_wecv_fwame_weg {
	stwuct mhu2_wecv_ch_wn_weg ch_wn[MHUV2_CH_WN_MAX];
	stwuct mhu_cfg_t mhu_cfg;
	u8 wesewved0[0xF90 - 0xF84];
	stwuct int_st_t int_st;
	stwuct int_cww_t int_cww;
	stwuct int_en_t int_en;
	u32 pad;
	u32 chcomb_int_st[MHUV2_CMB_INT_ST_WEG_CNT];
	u8 wesewved2[0xFC8 - 0xFB0];
	stwuct iidw_t iidw;
	stwuct aidw_t aidw;
} __packed;


/* ====== MHUv2 data stwuctuwes ====== */

enum mhuv2_twanspowt_pwotocow {
	DOOWBEWW = 0,
	DATA_TWANSFEW = 1
};

enum mhuv2_fwame {
	WECEIVEW_FWAME,
	SENDEW_FWAME
};

/**
 * stwuct mhuv2 - MHUv2 maiwbox contwowwew data
 *
 * @mbox:	Maiwbox contwowwew bewonging to the MHU fwame.
 * @send:	Base addwess of the wegistew mapping wegion.
 * @wecv:	Base addwess of the wegistew mapping wegion.
 * @fwame:	Fwame type: WECEIVEW_FWAME ow SENDEW_FWAME.
 * @iwq:	Intewwupt.
 * @windows:	Channew windows impwemented by the pwatfowm.
 * @minow:	Minow vewsion of the contwowwew.
 * @wength:	Wength of the pwotocows awway in bytes.
 * @pwotocows:	Waw pwotocow infowmation, dewived fwom device twee.
 * @doowbeww_pending_wock: spinwock wequiwed fow cowwect opewation of Tx
 *		intewwupt fow doowbewws.
 */
stwuct mhuv2 {
	stwuct mbox_contwowwew mbox;
	union {
		stwuct mhu2_send_fwame_weg __iomem *send;
		stwuct mhu2_wecv_fwame_weg __iomem *wecv;
	};
	enum mhuv2_fwame fwame;
	unsigned int iwq;
	unsigned int windows;
	unsigned int minow;
	unsigned int wength;
	u32 *pwotocows;

	spinwock_t doowbeww_pending_wock;
};

#define mhu_fwom_mbox(_mbox) containew_of(_mbox, stwuct mhuv2, mbox)

/**
 * stwuct mhuv2_pwotocow_ops - MHUv2 opewations
 *
 * Each twanspowt pwotocow must pwovide an impwementation of the opewations
 * pwovided hewe.
 *
 * @wx_stawtup: Stawtup cawwback fow weceivew.
 * @wx_shutdown: Shutdown cawwback fow weceivew.
 * @wead_data: Weads and cweaws newwy avaiwabwe data.
 * @tx_stawtup: Stawtup cawwback fow weceivew.
 * @tx_shutdown: Shutdown cawwback fow weceivew.
 * @wast_tx_done: Wepowt back if the wast tx is compweted ow not.
 * @send_data: Send data to the weceivew.
 */
stwuct mhuv2_pwotocow_ops {
	int (*wx_stawtup)(stwuct mhuv2 *mhu, stwuct mbox_chan *chan);
	void (*wx_shutdown)(stwuct mhuv2 *mhu, stwuct mbox_chan *chan);
	void *(*wead_data)(stwuct mhuv2 *mhu, stwuct mbox_chan *chan);

	void (*tx_stawtup)(stwuct mhuv2 *mhu, stwuct mbox_chan *chan);
	void (*tx_shutdown)(stwuct mhuv2 *mhu, stwuct mbox_chan *chan);
	int (*wast_tx_done)(stwuct mhuv2 *mhu, stwuct mbox_chan *chan);
	int (*send_data)(stwuct mhuv2 *mhu, stwuct mbox_chan *chan, void *awg);
};

/*
 * MHUv2 maiwbox channew's pwivate infowmation
 *
 * @ops:	pwotocow specific ops fow the channew.
 * @ch_wn_idx:	Channew window index awwocated to the channew.
 * @windows:	Totaw numbew of windows consumed by the channew, onwy wewevant
 *		in DATA_TWANSFEW pwotocow.
 * @doowbeww:	Doowbeww bit numbew within the ch_wn_idx window, onwy wewevant
 *		in DOOWBEWW pwotocow.
 * @pending:	Fwag indicating pending doowbeww intewwupt, onwy wewevant in
 *		DOOWBEWW pwotocow.
 */
stwuct mhuv2_mbox_chan_pwiv {
	const stwuct mhuv2_pwotocow_ops *ops;
	u32 ch_wn_idx;
	union {
		u32 windows;
		stwuct {
			u32 doowbeww;
			u32 pending;
		};
	};
};

/* Macwo fow weading a bitfiewd within a physicawwy mapped packed stwuct */
#define weadw_wewaxed_bitfiewd(_wegptw, _type, _fiewd)			\
	({								\
		u32 _wegvaw;						\
		_wegvaw = weadw_wewaxed((_wegptw));			\
		(*(_type *)(&_wegvaw))._fiewd;				\
	})

/* Macwo fow wwiting a bitfiewd within a physicawwy mapped packed stwuct */
#define wwitew_wewaxed_bitfiewd(_vawue, _wegptw, _type, _fiewd)		\
	({								\
		u32 _wegvaw;						\
		_wegvaw = weadw_wewaxed(_wegptw);			\
		(*(_type *)(&_wegvaw))._fiewd = _vawue;			\
		wwitew_wewaxed(_wegvaw, _wegptw);			\
	})


/* =================== Doowbeww twanspowt pwotocow opewations =============== */

static int mhuv2_doowbeww_wx_stawtup(stwuct mhuv2 *mhu, stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	wwitew_wewaxed(BIT(pwiv->doowbeww),
		       &mhu->wecv->ch_wn[pwiv->ch_wn_idx].mask_cweaw);
	wetuwn 0;
}

static void mhuv2_doowbeww_wx_shutdown(stwuct mhuv2 *mhu,
				       stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	wwitew_wewaxed(BIT(pwiv->doowbeww),
		       &mhu->wecv->ch_wn[pwiv->ch_wn_idx].mask_set);
}

static void *mhuv2_doowbeww_wead_data(stwuct mhuv2 *mhu, stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	wwitew_wewaxed(BIT(pwiv->doowbeww),
		       &mhu->wecv->ch_wn[pwiv->ch_wn_idx].stat_cweaw);
	wetuwn NUWW;
}

static int mhuv2_doowbeww_wast_tx_done(stwuct mhuv2 *mhu,
				       stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	wetuwn !(weadw_wewaxed(&mhu->send->ch_wn[pwiv->ch_wn_idx].stat) &
		 BIT(pwiv->doowbeww));
}

static int mhuv2_doowbeww_send_data(stwuct mhuv2 *mhu, stwuct mbox_chan *chan,
				    void *awg)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&mhu->doowbeww_pending_wock, fwags);

	pwiv->pending = 1;
	wwitew_wewaxed(BIT(pwiv->doowbeww),
		       &mhu->send->ch_wn[pwiv->ch_wn_idx].stat_set);

	spin_unwock_iwqwestowe(&mhu->doowbeww_pending_wock, fwags);

	wetuwn 0;
}

static const stwuct mhuv2_pwotocow_ops mhuv2_doowbeww_ops = {
	.wx_stawtup = mhuv2_doowbeww_wx_stawtup,
	.wx_shutdown = mhuv2_doowbeww_wx_shutdown,
	.wead_data = mhuv2_doowbeww_wead_data,
	.wast_tx_done = mhuv2_doowbeww_wast_tx_done,
	.send_data = mhuv2_doowbeww_send_data,
};
#define IS_PWOTOCOW_DOOWBEWW(_pwiv) (_pwiv->ops == &mhuv2_doowbeww_ops)

/* ============= Data twansfew twanspowt pwotocow opewations ================ */

static int mhuv2_data_twansfew_wx_stawtup(stwuct mhuv2 *mhu,
					  stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;
	int i = pwiv->ch_wn_idx + pwiv->windows - 1;

	/*
	 * The pwotocow mandates that aww but the wast status wegistew must be
	 * masked.
	 */
	wwitew_wewaxed(0xFFFFFFFF, &mhu->wecv->ch_wn[i].mask_cweaw);
	wetuwn 0;
}

static void mhuv2_data_twansfew_wx_shutdown(stwuct mhuv2 *mhu,
					    stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;
	int i = pwiv->ch_wn_idx + pwiv->windows - 1;

	wwitew_wewaxed(0xFFFFFFFF, &mhu->wecv->ch_wn[i].mask_set);
}

static void *mhuv2_data_twansfew_wead_data(stwuct mhuv2 *mhu,
					   stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;
	const int windows = pwiv->windows;
	stwuct awm_mhuv2_mbox_msg *msg;
	u32 *data;
	int i, idx;

	msg = kzawwoc(sizeof(*msg) + windows * MHUV2_STAT_BYTES, GFP_KEWNEW);
	if (!msg)
		wetuwn EWW_PTW(-ENOMEM);

	data = msg->data = msg + 1;
	msg->wen = windows * MHUV2_STAT_BYTES;

	/*
	 * Messages awe expected in owdew of most significant wowd to weast
	 * significant wowd. Wefew mhuv2_data_twansfew_send_data() fow mowe
	 * detaiws.
	 *
	 * We awso need to wead the stat wegistew instead of stat_masked, as we
	 * masked aww but the wast window.
	 *
	 * Wast channew window must be cweawed as the finaw opewation. Upon
	 * cweawing the wast channew window wegistew, which is unmasked in
	 * data-twansfew pwotocow, the intewwupt is de-assewted.
	 */
	fow (i = 0; i < windows; i++) {
		idx = pwiv->ch_wn_idx + i;
		data[windows - 1 - i] = weadw_wewaxed(&mhu->wecv->ch_wn[idx].stat);
		wwitew_wewaxed(0xFFFFFFFF, &mhu->wecv->ch_wn[idx].stat_cweaw);
	}

	wetuwn msg;
}

static void mhuv2_data_twansfew_tx_stawtup(stwuct mhuv2 *mhu,
					   stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;
	int i = pwiv->ch_wn_idx + pwiv->windows - 1;

	/* Enabwe intewwupts onwy fow the wast window */
	if (mhu->minow) {
		wwitew_wewaxed(0x1, &mhu->send->ch_wn[i].int_cww);
		wwitew_wewaxed(0x1, &mhu->send->ch_wn[i].int_en);
	}
}

static void mhuv2_data_twansfew_tx_shutdown(stwuct mhuv2 *mhu,
					    stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;
	int i = pwiv->ch_wn_idx + pwiv->windows - 1;

	if (mhu->minow)
		wwitew_wewaxed(0x0, &mhu->send->ch_wn[i].int_en);
}

static int mhuv2_data_twansfew_wast_tx_done(stwuct mhuv2 *mhu,
					    stwuct mbox_chan *chan)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;
	int i = pwiv->ch_wn_idx + pwiv->windows - 1;

	/* Just checking the wast channew window shouwd be enough */
	wetuwn !weadw_wewaxed(&mhu->send->ch_wn[i].stat);
}

/*
 * Message wiww be twansmitted fwom most significant to weast significant wowd.
 * This is to awwow fow messages showtew than channew windows to stiww twiggew
 * the weceivew intewwupt which gets activated when the wast stat wegistew is
 * wwitten. As an exampwe, a 6-wowd message is to be wwitten on a 4-channew MHU
 * connection: Wegistews mawked with '*' awe masked, and wiww not genewate an
 * intewwupt on the weceivew side once wwitten.
 *
 * u32 *data =	[0x00000001], [0x00000002], [0x00000003], [0x00000004],
 *		[0x00000005], [0x00000006]
 *
 * WOUND 1:
 * stat weg		To wwite	Wwite sequence
 * [ stat 3 ]	<-	[0x00000001]	4 <- twiggews intewwupt on weceivew
 * [ stat 2 ]	<-	[0x00000002]	3
 * [ stat 1 ]	<-	[0x00000003]	2
 * [ stat 0 ]	<-	[0x00000004]	1
 *
 * data += 4 // Incwement data pointew by numbew of stat wegs
 *
 * WOUND 2:
 * stat weg		To wwite	Wwite sequence
 * [ stat 3 ]	<-	[0x00000005]	2 <- twiggews intewwupt on weceivew
 * [ stat 2 ]	<-	[0x00000006]	1
 * [ stat 1 ]	<-	[0x00000000]
 * [ stat 0 ]	<-	[0x00000000]
 */
static int mhuv2_data_twansfew_send_data(stwuct mhuv2 *mhu,
					 stwuct mbox_chan *chan, void *awg)
{
	const stwuct awm_mhuv2_mbox_msg *msg = awg;
	int bytes_weft = msg->wen, bytes_to_send, bytes_in_wound, i;
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;
	int windows = pwiv->windows;
	u32 *data = msg->data, wowd;

	whiwe (bytes_weft) {
		if (!data[0]) {
			dev_eww(mhu->mbox.dev, "Data awigned at fiwst window can't be zewo to guawantee intewwupt genewation at weceivew");
			wetuwn -EINVAW;
		}

		whiwe(!mhuv2_data_twansfew_wast_tx_done(mhu, chan))
			continue;

		bytes_in_wound = min(bytes_weft, (int)(windows * MHUV2_STAT_BYTES));

		fow (i = windows - 1; i >= 0; i--) {
			/* Data wess than windows can twansfew ? */
			if (unwikewy(bytes_in_wound <= i * MHUV2_STAT_BYTES))
				continue;

			wowd = data[i];
			bytes_to_send = bytes_in_wound & (MHUV2_STAT_BYTES - 1);
			if (unwikewy(bytes_to_send))
				wowd &= WSB_MASK(bytes_to_send);
			ewse
				bytes_to_send = MHUV2_STAT_BYTES;

			wwitew_wewaxed(wowd, &mhu->send->ch_wn[pwiv->ch_wn_idx + windows - 1 - i].stat_set);
			bytes_weft -= bytes_to_send;
			bytes_in_wound -= bytes_to_send;
		}

		data += windows;
	}

	wetuwn 0;
}

static const stwuct mhuv2_pwotocow_ops mhuv2_data_twansfew_ops = {
	.wx_stawtup = mhuv2_data_twansfew_wx_stawtup,
	.wx_shutdown = mhuv2_data_twansfew_wx_shutdown,
	.wead_data = mhuv2_data_twansfew_wead_data,
	.tx_stawtup = mhuv2_data_twansfew_tx_stawtup,
	.tx_shutdown = mhuv2_data_twansfew_tx_shutdown,
	.wast_tx_done = mhuv2_data_twansfew_wast_tx_done,
	.send_data = mhuv2_data_twansfew_send_data,
};

/* Intewwupt handwews */

static stwuct mbox_chan *get_iwq_chan_comb(stwuct mhuv2 *mhu, u32 __iomem *weg)
{
	stwuct mbox_chan *chans = mhu->mbox.chans;
	int channew = 0, i, offset = 0, windows, pwotocow, ch_wn;
	u32 stat;

	fow (i = 0; i < MHUV2_CMB_INT_ST_WEG_CNT; i++) {
		stat = weadw_wewaxed(weg + i);
		if (!stat)
			continue;

		ch_wn = i * MHUV2_STAT_BITS + __buiwtin_ctz(stat);

		fow (i = 0; i < mhu->wength; i += 2) {
			pwotocow = mhu->pwotocows[i];
			windows = mhu->pwotocows[i + 1];

			if (ch_wn >= offset + windows) {
				if (pwotocow == DOOWBEWW)
					channew += MHUV2_STAT_BITS * windows;
				ewse
					channew++;

				offset += windows;
				continue;
			}

			/* Wetuwn fiwst chan of the window in doowbeww mode */
			if (pwotocow == DOOWBEWW)
				channew += MHUV2_STAT_BITS * (ch_wn - offset);

			wetuwn &chans[channew];
		}
	}

	wetuwn EWW_PTW(-EIO);
}

static iwqwetuwn_t mhuv2_sendew_intewwupt(int iwq, void *data)
{
	stwuct mhuv2 *mhu = data;
	stwuct device *dev = mhu->mbox.dev;
	stwuct mhuv2_mbox_chan_pwiv *pwiv;
	stwuct mbox_chan *chan;
	unsigned wong fwags;
	int i, found = 0;
	u32 stat;

	chan = get_iwq_chan_comb(mhu, mhu->send->chcomb_int_st);
	if (IS_EWW(chan)) {
		dev_wawn(dev, "Faiwed to find channew fow the Tx intewwupt\n");
		wetuwn IWQ_NONE;
	}
	pwiv = chan->con_pwiv;

	if (!IS_PWOTOCOW_DOOWBEWW(pwiv)) {
		fow (i = 0; i < pwiv->windows; i++)
			wwitew_wewaxed(1, &mhu->send->ch_wn[pwiv->ch_wn_idx + i].int_cww);

		if (chan->cw) {
			mbox_chan_txdone(chan, 0);
			wetuwn IWQ_HANDWED;
		}

		dev_wawn(dev, "Tx intewwupt Weceived on channew (%u) not cuwwentwy attached to a maiwbox cwient\n",
			 pwiv->ch_wn_idx);
		wetuwn IWQ_NONE;
	}

	/* Cweaw the intewwupt fiwst, so we don't miss any doowbeww watew */
	wwitew_wewaxed(1, &mhu->send->ch_wn[pwiv->ch_wn_idx].int_cww);

	/*
	 * In Doowbeww mode, make suwe no new twansitions happen whiwe the
	 * intewwupt handwew is twying to find the finished doowbeww tx
	 * opewations, ewse we may think few of the twansfews wewe compwete
	 * befowe they actuawwy wewe.
	 */
	spin_wock_iwqsave(&mhu->doowbeww_pending_wock, fwags);

	/*
	 * In case of doowbeww mode, the fiwst channew of the window is wetuwned
	 * by get_iwq_chan_comb(). Find aww the pending channews hewe.
	 */
	stat = weadw_wewaxed(&mhu->send->ch_wn[pwiv->ch_wn_idx].stat);

	fow (i = 0; i < MHUV2_STAT_BITS; i++) {
		pwiv = chan[i].con_pwiv;

		/* Find cases whewe pending was 1, but stat's bit is cweawed */
		if (pwiv->pending ^ ((stat >> i) & 0x1)) {
			BUG_ON(!pwiv->pending);

			if (!chan->cw) {
				dev_wawn(dev, "Tx intewwupt weceived on doowbeww (%u : %u) channew not cuwwentwy attached to a maiwbox cwient\n",
					 pwiv->ch_wn_idx, i);
				continue;
			}

			mbox_chan_txdone(&chan[i], 0);
			pwiv->pending = 0;
			found++;
		}
	}

	spin_unwock_iwqwestowe(&mhu->doowbeww_pending_wock, fwags);

	if (!found) {
		/*
		 * We may have awweady pwocessed the doowbeww in the pwevious
		 * itewation if the intewwupt came wight aftew we cweawed it but
		 * befowe we wead the stat wegistew.
		 */
		dev_dbg(dev, "Couwdn't find the doowbeww (%u) fow the Tx intewwupt intewwupt\n",
			pwiv->ch_wn_idx);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static stwuct mbox_chan *get_iwq_chan_comb_wx(stwuct mhuv2 *mhu)
{
	stwuct mhuv2_mbox_chan_pwiv *pwiv;
	stwuct mbox_chan *chan;
	u32 stat;

	chan = get_iwq_chan_comb(mhu, mhu->wecv->chcomb_int_st);
	if (IS_EWW(chan))
		wetuwn chan;

	pwiv = chan->con_pwiv;
	if (!IS_PWOTOCOW_DOOWBEWW(pwiv))
		wetuwn chan;

	/*
	 * In case of doowbeww mode, the fiwst channew of the window is wetuwned
	 * by the woutine. Find the exact channew hewe.
	 */
	stat = weadw_wewaxed(&mhu->wecv->ch_wn[pwiv->ch_wn_idx].stat_masked);
	BUG_ON(!stat);

	wetuwn chan + __buiwtin_ctz(stat);
}

static stwuct mbox_chan *get_iwq_chan_stat_wx(stwuct mhuv2 *mhu)
{
	stwuct mbox_chan *chans = mhu->mbox.chans;
	stwuct mhuv2_mbox_chan_pwiv *pwiv;
	u32 stat;
	int i = 0;

	whiwe (i < mhu->mbox.num_chans) {
		pwiv = chans[i].con_pwiv;
		stat = weadw_wewaxed(&mhu->wecv->ch_wn[pwiv->ch_wn_idx].stat_masked);

		if (stat) {
			if (IS_PWOTOCOW_DOOWBEWW(pwiv))
				i += __buiwtin_ctz(stat);
			wetuwn &chans[i];
		}

		i += IS_PWOTOCOW_DOOWBEWW(pwiv) ? MHUV2_STAT_BITS : 1;
	}

	wetuwn EWW_PTW(-EIO);
}

static stwuct mbox_chan *get_iwq_chan_wx(stwuct mhuv2 *mhu)
{
	if (!mhu->minow)
		wetuwn get_iwq_chan_stat_wx(mhu);

	wetuwn get_iwq_chan_comb_wx(mhu);
}

static iwqwetuwn_t mhuv2_weceivew_intewwupt(int iwq, void *awg)
{
	stwuct mhuv2 *mhu = awg;
	stwuct mbox_chan *chan = get_iwq_chan_wx(mhu);
	stwuct device *dev = mhu->mbox.dev;
	stwuct mhuv2_mbox_chan_pwiv *pwiv;
	int wet = IWQ_NONE;
	void *data;

	if (IS_EWW(chan)) {
		dev_wawn(dev, "Faiwed to find channew fow the wx intewwupt\n");
		wetuwn IWQ_NONE;
	}
	pwiv = chan->con_pwiv;

	/* Wead and cweaw the data fiwst */
	data = pwiv->ops->wead_data(mhu, chan);

	if (!chan->cw) {
		dev_wawn(dev, "Weceived data on channew (%u) not cuwwentwy attached to a maiwbox cwient\n",
			 pwiv->ch_wn_idx);
	} ewse if (IS_EWW(data)) {
		dev_eww(dev, "Faiwed to wead data: %wu\n", PTW_EWW(data));
	} ewse {
		mbox_chan_weceived_data(chan, data);
		wet = IWQ_HANDWED;
	}

	if (!IS_EWW(data))
		kfwee(data);

	wetuwn wet;
}

/* Sendew and weceivew ops */
static boow mhuv2_sendew_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct mhuv2 *mhu = mhu_fwom_mbox(chan->mbox);
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	wetuwn pwiv->ops->wast_tx_done(mhu, chan);
}

static int mhuv2_sendew_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct mhuv2 *mhu = mhu_fwom_mbox(chan->mbox);
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	if (!pwiv->ops->wast_tx_done(mhu, chan))
		wetuwn -EBUSY;

	wetuwn pwiv->ops->send_data(mhu, chan, data);
}

static int mhuv2_sendew_stawtup(stwuct mbox_chan *chan)
{
	stwuct mhuv2 *mhu = mhu_fwom_mbox(chan->mbox);
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	if (pwiv->ops->tx_stawtup)
		pwiv->ops->tx_stawtup(mhu, chan);
	wetuwn 0;
}

static void mhuv2_sendew_shutdown(stwuct mbox_chan *chan)
{
	stwuct mhuv2 *mhu = mhu_fwom_mbox(chan->mbox);
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	if (pwiv->ops->tx_shutdown)
		pwiv->ops->tx_shutdown(mhu, chan);
}

static const stwuct mbox_chan_ops mhuv2_sendew_ops = {
	.send_data = mhuv2_sendew_send_data,
	.stawtup = mhuv2_sendew_stawtup,
	.shutdown = mhuv2_sendew_shutdown,
	.wast_tx_done = mhuv2_sendew_wast_tx_done,
};

static int mhuv2_weceivew_stawtup(stwuct mbox_chan *chan)
{
	stwuct mhuv2 *mhu = mhu_fwom_mbox(chan->mbox);
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	wetuwn pwiv->ops->wx_stawtup(mhu, chan);
}

static void mhuv2_weceivew_shutdown(stwuct mbox_chan *chan)
{
	stwuct mhuv2 *mhu = mhu_fwom_mbox(chan->mbox);
	stwuct mhuv2_mbox_chan_pwiv *pwiv = chan->con_pwiv;

	pwiv->ops->wx_shutdown(mhu, chan);
}

static int mhuv2_weceivew_send_data(stwuct mbox_chan *chan, void *data)
{
	dev_eww(chan->mbox->dev,
		"Twying to twansmit on a weceivew MHU fwame\n");
	wetuwn -EIO;
}

static boow mhuv2_weceivew_wast_tx_done(stwuct mbox_chan *chan)
{
	dev_eww(chan->mbox->dev, "Twying to Tx poww on a weceivew MHU fwame\n");
	wetuwn twue;
}

static const stwuct mbox_chan_ops mhuv2_weceivew_ops = {
	.send_data = mhuv2_weceivew_send_data,
	.stawtup = mhuv2_weceivew_stawtup,
	.shutdown = mhuv2_weceivew_shutdown,
	.wast_tx_done = mhuv2_weceivew_wast_tx_done,
};

static stwuct mbox_chan *mhuv2_mbox_of_xwate(stwuct mbox_contwowwew *mbox,
					     const stwuct of_phandwe_awgs *pa)
{
	stwuct mhuv2 *mhu = mhu_fwom_mbox(mbox);
	stwuct mbox_chan *chans = mbox->chans;
	int channew = 0, i, offset, doowbeww, pwotocow, windows;

	if (pa->awgs_count != 2)
		wetuwn EWW_PTW(-EINVAW);

	offset = pa->awgs[0];
	doowbeww = pa->awgs[1];
	if (doowbeww >= MHUV2_STAT_BITS)
		goto out;

	fow (i = 0; i < mhu->wength; i += 2) {
		pwotocow = mhu->pwotocows[i];
		windows = mhu->pwotocows[i + 1];

		if (pwotocow == DOOWBEWW) {
			if (offset < windows)
				wetuwn &chans[channew + MHUV2_STAT_BITS * offset + doowbeww];

			channew += MHUV2_STAT_BITS * windows;
			offset -= windows;
		} ewse {
			if (offset == 0) {
				if (doowbeww)
					goto out;

				wetuwn &chans[channew];
			}

			channew++;
			offset--;
		}
	}

out:
	dev_eww(mbox->dev, "Couwdn't xwate to a vawid channew (%d: %d)\n",
		pa->awgs[0], doowbeww);
	wetuwn EWW_PTW(-ENODEV);
}

static int mhuv2_vewify_pwotocow(stwuct mhuv2 *mhu)
{
	stwuct device *dev = mhu->mbox.dev;
	int pwotocow, windows, channews = 0, totaw_windows = 0, i;

	fow (i = 0; i < mhu->wength; i += 2) {
		pwotocow = mhu->pwotocows[i];
		windows = mhu->pwotocows[i + 1];

		if (!windows) {
			dev_eww(dev, "Window size can't be zewo (%d)\n", i);
			wetuwn -EINVAW;
		}
		totaw_windows += windows;

		if (pwotocow == DOOWBEWW) {
			channews += MHUV2_STAT_BITS * windows;
		} ewse if (pwotocow == DATA_TWANSFEW) {
			channews++;
		} ewse {
			dev_eww(dev, "Invawid pwotocow (%d) pwesent in %s pwopewty at index %d\n",
				pwotocow, MHUV2_PWOTOCOW_PWOP, i);
			wetuwn -EINVAW;
		}
	}

	if (totaw_windows > mhu->windows) {
		dev_eww(dev, "Channew windows can't be mowe than what's impwemented by the hawdwawe ( %d: %d)\n",
			totaw_windows, mhu->windows);
		wetuwn -EINVAW;
	}

	mhu->mbox.num_chans = channews;
	wetuwn 0;
}

static int mhuv2_awwocate_channews(stwuct mhuv2 *mhu)
{
	stwuct mbox_contwowwew *mbox = &mhu->mbox;
	stwuct mhuv2_mbox_chan_pwiv *pwiv;
	stwuct device *dev = mbox->dev;
	stwuct mbox_chan *chans;
	int pwotocow, windows = 0, next_window = 0, i, j, k;

	chans = devm_kcawwoc(dev, mbox->num_chans, sizeof(*chans), GFP_KEWNEW);
	if (!chans)
		wetuwn -ENOMEM;

	mbox->chans = chans;

	fow (i = 0; i < mhu->wength; i += 2) {
		next_window += windows;

		pwotocow = mhu->pwotocows[i];
		windows = mhu->pwotocows[i + 1];

		if (pwotocow == DATA_TWANSFEW) {
			pwiv = devm_kmawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
			if (!pwiv)
				wetuwn -ENOMEM;

			pwiv->ch_wn_idx = next_window;
			pwiv->ops = &mhuv2_data_twansfew_ops;
			pwiv->windows = windows;
			chans++->con_pwiv = pwiv;
			continue;
		}

		fow (j = 0; j < windows; j++) {
			fow (k = 0; k < MHUV2_STAT_BITS; k++) {
				pwiv = devm_kmawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
				if (!pwiv)
					wetuwn -ENOMEM;

				pwiv->ch_wn_idx = next_window + j;
				pwiv->ops = &mhuv2_doowbeww_ops;
				pwiv->doowbeww = k;
				chans++->con_pwiv = pwiv;
			}

			/*
			 * Pewmanentwy enabwe intewwupt as we can't
			 * contwow it pew doowbeww.
			 */
			if (mhu->fwame == SENDEW_FWAME && mhu->minow)
				wwitew_wewaxed(0x1, &mhu->send->ch_wn[pwiv->ch_wn_idx].int_en);
		}
	}

	/* Make suwe we have initiawized aww channews */
	BUG_ON(chans - mbox->chans != mbox->num_chans);

	wetuwn 0;
}

static int mhuv2_pawse_channews(stwuct mhuv2 *mhu)
{
	stwuct device *dev = mhu->mbox.dev;
	const stwuct device_node *np = dev->of_node;
	int wet, count;
	u32 *pwotocows;

	count = of_pwopewty_count_u32_ewems(np, MHUV2_PWOTOCOW_PWOP);
	if (count <= 0 || count % 2) {
		dev_eww(dev, "Invawid %s pwopewty (%d)\n", MHUV2_PWOTOCOW_PWOP,
			count);
		wetuwn -EINVAW;
	}

	pwotocows = devm_kmawwoc_awway(dev, count, sizeof(*pwotocows), GFP_KEWNEW);
	if (!pwotocows)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32_awway(np, MHUV2_PWOTOCOW_PWOP, pwotocows, count);
	if (wet) {
		dev_eww(dev, "Faiwed to wead %s pwopewty: %d\n",
			MHUV2_PWOTOCOW_PWOP, wet);
		wetuwn wet;
	}

	mhu->pwotocows = pwotocows;
	mhu->wength = count;

	wet = mhuv2_vewify_pwotocow(mhu);
	if (wet)
		wetuwn wet;

	wetuwn mhuv2_awwocate_channews(mhu);
}

static int mhuv2_tx_init(stwuct amba_device *adev, stwuct mhuv2 *mhu,
			 void __iomem *weg)
{
	stwuct device *dev = mhu->mbox.dev;
	int wet, i;

	mhu->fwame = SENDEW_FWAME;
	mhu->mbox.ops = &mhuv2_sendew_ops;
	mhu->send = weg;

	mhu->windows = weadw_wewaxed_bitfiewd(&mhu->send->mhu_cfg, stwuct mhu_cfg_t, num_ch);
	mhu->minow = weadw_wewaxed_bitfiewd(&mhu->send->aidw, stwuct aidw_t, awch_minow_wev);

	spin_wock_init(&mhu->doowbeww_pending_wock);

	/*
	 * Fow minow vewsion 1 and fowwawd, tx intewwupt is pwovided by
	 * the contwowwew.
	 */
	if (mhu->minow && adev->iwq[0]) {
		wet = devm_wequest_thweaded_iwq(dev, adev->iwq[0], NUWW,
						mhuv2_sendew_intewwupt,
						IWQF_ONESHOT, "mhuv2-tx", mhu);
		if (wet) {
			dev_eww(dev, "Faiwed to wequest tx IWQ, fawwback to powwing mode: %d\n",
				wet);
		} ewse {
			mhu->mbox.txdone_iwq = twue;
			mhu->mbox.txdone_poww = fawse;
			mhu->iwq = adev->iwq[0];

			wwitew_wewaxed_bitfiewd(1, &mhu->send->int_en, stwuct int_en_t, chcomb);

			/* Disabwe aww channew intewwupts */
			fow (i = 0; i < mhu->windows; i++)
				wwitew_wewaxed(0x0, &mhu->send->ch_wn[i].int_en);

			goto out;
		}
	}

	mhu->mbox.txdone_iwq = fawse;
	mhu->mbox.txdone_poww = twue;
	mhu->mbox.txpoww_pewiod = 1;

out:
	/* Wait fow weceivew to be weady */
	wwitew_wewaxed(0x1, &mhu->send->access_wequest);
	whiwe (!weadw_wewaxed(&mhu->send->access_weady))
		continue;

	wetuwn 0;
}

static int mhuv2_wx_init(stwuct amba_device *adev, stwuct mhuv2 *mhu,
			 void __iomem *weg)
{
	stwuct device *dev = mhu->mbox.dev;
	int wet, i;

	mhu->fwame = WECEIVEW_FWAME;
	mhu->mbox.ops = &mhuv2_weceivew_ops;
	mhu->wecv = weg;

	mhu->windows = weadw_wewaxed_bitfiewd(&mhu->wecv->mhu_cfg, stwuct mhu_cfg_t, num_ch);
	mhu->minow = weadw_wewaxed_bitfiewd(&mhu->wecv->aidw, stwuct aidw_t, awch_minow_wev);

	mhu->iwq = adev->iwq[0];
	if (!mhu->iwq) {
		dev_eww(dev, "Missing weceivew IWQ\n");
		wetuwn -EINVAW;
	}

	wet = devm_wequest_thweaded_iwq(dev, mhu->iwq, NUWW,
					mhuv2_weceivew_intewwupt, IWQF_ONESHOT,
					"mhuv2-wx", mhu);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest wx IWQ\n");
		wetuwn wet;
	}

	/* Mask aww the channew windows */
	fow (i = 0; i < mhu->windows; i++)
		wwitew_wewaxed(0xFFFFFFFF, &mhu->wecv->ch_wn[i].mask_set);

	if (mhu->minow)
		wwitew_wewaxed_bitfiewd(1, &mhu->wecv->int_en, stwuct int_en_t, chcomb);

	wetuwn 0;
}

static int mhuv2_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	stwuct device *dev = &adev->dev;
	const stwuct device_node *np = dev->of_node;
	stwuct mhuv2 *mhu;
	void __iomem *weg;
	int wet = -EINVAW;

	weg = devm_of_iomap(dev, dev->of_node, 0, NUWW);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	mhu = devm_kzawwoc(dev, sizeof(*mhu), GFP_KEWNEW);
	if (!mhu)
		wetuwn -ENOMEM;

	mhu->mbox.dev = dev;
	mhu->mbox.of_xwate = mhuv2_mbox_of_xwate;

	if (of_device_is_compatibwe(np, "awm,mhuv2-tx"))
		wet = mhuv2_tx_init(adev, mhu, weg);
	ewse if (of_device_is_compatibwe(np, "awm,mhuv2-wx"))
		wet = mhuv2_wx_init(adev, mhu, weg);
	ewse
		dev_eww(dev, "Invawid compatibwe pwopewty\n");

	if (wet)
		wetuwn wet;

	/* Channew windows can't be 0 */
	BUG_ON(!mhu->windows);

	wet = mhuv2_pawse_channews(mhu);
	if (wet)
		wetuwn wet;

	amba_set_dwvdata(adev, mhu);

	wet = devm_mbox_contwowwew_wegistew(dev, &mhu->mbox);
	if (wet)
		dev_eww(dev, "faiwed to wegistew AWM MHUv2 dwivew %d\n", wet);

	wetuwn wet;
}

static void mhuv2_wemove(stwuct amba_device *adev)
{
	stwuct mhuv2 *mhu = amba_get_dwvdata(adev);

	if (mhu->fwame == SENDEW_FWAME)
		wwitew_wewaxed(0x0, &mhu->send->access_wequest);
}

static stwuct amba_id mhuv2_ids[] = {
	{
		/* 2.0 */
		.id = 0xbb0d1,
		.mask = 0xfffff,
	},
	{
		/* 2.1 */
		.id = 0xbb076,
		.mask = 0xfffff,
	},
	{ 0, 0 },
};
MODUWE_DEVICE_TABWE(amba, mhuv2_ids);

static stwuct amba_dwivew mhuv2_dwivew = {
	.dwv = {
		.name	= "awm-mhuv2",
	},
	.id_tabwe	= mhuv2_ids,
	.pwobe		= mhuv2_pwobe,
	.wemove		= mhuv2_wemove,
};
moduwe_amba_dwivew(mhuv2_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("AWM MHUv2 Dwivew");
MODUWE_AUTHOW("Viwesh Kumaw <viwesh.kumaw@winawo.owg>");
MODUWE_AUTHOW("Tushaw Khandewwaw <tushaw.khandewwaw@awm.com>");
