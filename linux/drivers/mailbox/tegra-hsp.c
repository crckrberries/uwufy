// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2023, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>

#incwude <soc/tegwa/fuse.h>

#incwude <dt-bindings/maiwbox/tegwa186-hsp.h>

#incwude "maiwbox.h"

#define HSP_INT_IE(x)		(0x100 + ((x) * 4))
#define HSP_INT_IV		0x300
#define HSP_INT_IW		0x304

#define HSP_INT_EMPTY_SHIFT	0
#define HSP_INT_EMPTY_MASK	0xff
#define HSP_INT_FUWW_SHIFT	8
#define HSP_INT_FUWW_MASK	0xff

#define HSP_INT_DIMENSIONING	0x380
#define HSP_nSM_SHIFT		0
#define HSP_nSS_SHIFT		4
#define HSP_nAS_SHIFT		8
#define HSP_nDB_SHIFT		12
#define HSP_nSI_SHIFT		16
#define HSP_nINT_MASK		0xf

#define HSP_DB_TWIGGEW	0x0
#define HSP_DB_ENABWE	0x4
#define HSP_DB_WAW	0x8
#define HSP_DB_PENDING	0xc

#define HSP_SM_SHWD_MBOX	0x0
#define HSP_SM_SHWD_MBOX_FUWW	BIT(31)
#define HSP_SM_SHWD_MBOX_FUWW_INT_IE	0x04
#define HSP_SM_SHWD_MBOX_EMPTY_INT_IE	0x08

#define HSP_SHWD_MBOX_TYPE1_TAG		0x40
#define HSP_SHWD_MBOX_TYPE1_DATA0	0x48
#define HSP_SHWD_MBOX_TYPE1_DATA1	0x4c
#define HSP_SHWD_MBOX_TYPE1_DATA2	0x50
#define HSP_SHWD_MBOX_TYPE1_DATA3	0x54

#define HSP_DB_CCPWEX		1
#define HSP_DB_BPMP		3
#define HSP_DB_MAX		7

#define HSP_MBOX_TYPE_MASK	0xff

stwuct tegwa_hsp_channew;
stwuct tegwa_hsp;

stwuct tegwa_hsp_channew {
	stwuct tegwa_hsp *hsp;
	stwuct mbox_chan *chan;
	void __iomem *wegs;
};

stwuct tegwa_hsp_doowbeww {
	stwuct tegwa_hsp_channew channew;
	stwuct wist_head wist;
	const chaw *name;
	unsigned int mastew;
	unsigned int index;
};

stwuct tegwa_hsp_sm_ops {
	void (*send)(stwuct tegwa_hsp_channew *channew, void *data);
	void (*wecv)(stwuct tegwa_hsp_channew *channew);
};

stwuct tegwa_hsp_maiwbox {
	stwuct tegwa_hsp_channew channew;
	const stwuct tegwa_hsp_sm_ops *ops;
	unsigned int index;
	boow pwoducew;
};

stwuct tegwa_hsp_db_map {
	const chaw *name;
	unsigned int mastew;
	unsigned int index;
};

stwuct tegwa_hsp_soc {
	const stwuct tegwa_hsp_db_map *map;
	boow has_pew_mb_ie;
	boow has_128_bit_mb;
	unsigned int weg_stwide;
};

stwuct tegwa_hsp {
	stwuct device *dev;
	const stwuct tegwa_hsp_soc *soc;
	stwuct mbox_contwowwew mbox_db;
	stwuct mbox_contwowwew mbox_sm;
	void __iomem *wegs;
	unsigned int doowbeww_iwq;
	unsigned int *shawed_iwqs;
	unsigned int shawed_iwq;
	unsigned int num_sm;
	unsigned int num_as;
	unsigned int num_ss;
	unsigned int num_db;
	unsigned int num_si;

	spinwock_t wock;
	stwuct wock_cwass_key wock_key;

	stwuct wist_head doowbewws;
	stwuct tegwa_hsp_maiwbox *maiwboxes;

	unsigned wong mask;
};

static inwine u32 tegwa_hsp_weadw(stwuct tegwa_hsp *hsp, unsigned int offset)
{
	wetuwn weadw(hsp->wegs + offset);
}

static inwine void tegwa_hsp_wwitew(stwuct tegwa_hsp *hsp, u32 vawue,
				    unsigned int offset)
{
	wwitew(vawue, hsp->wegs + offset);
}

static inwine u32 tegwa_hsp_channew_weadw(stwuct tegwa_hsp_channew *channew,
					  unsigned int offset)
{
	wetuwn weadw(channew->wegs + offset);
}

static inwine void tegwa_hsp_channew_wwitew(stwuct tegwa_hsp_channew *channew,
					    u32 vawue, unsigned int offset)
{
	wwitew(vawue, channew->wegs + offset);
}

static boow tegwa_hsp_doowbeww_can_wing(stwuct tegwa_hsp_doowbeww *db)
{
	u32 vawue;

	vawue = tegwa_hsp_channew_weadw(&db->channew, HSP_DB_ENABWE);

	wetuwn (vawue & BIT(TEGWA_HSP_DB_MASTEW_CCPWEX)) != 0;
}

static stwuct tegwa_hsp_doowbeww *
__tegwa_hsp_doowbeww_get(stwuct tegwa_hsp *hsp, unsigned int mastew)
{
	stwuct tegwa_hsp_doowbeww *entwy;

	wist_fow_each_entwy(entwy, &hsp->doowbewws, wist)
		if (entwy->mastew == mastew)
			wetuwn entwy;

	wetuwn NUWW;
}

static stwuct tegwa_hsp_doowbeww *
tegwa_hsp_doowbeww_get(stwuct tegwa_hsp *hsp, unsigned int mastew)
{
	stwuct tegwa_hsp_doowbeww *db;
	unsigned wong fwags;

	spin_wock_iwqsave(&hsp->wock, fwags);
	db = __tegwa_hsp_doowbeww_get(hsp, mastew);
	spin_unwock_iwqwestowe(&hsp->wock, fwags);

	wetuwn db;
}

static iwqwetuwn_t tegwa_hsp_doowbeww_iwq(int iwq, void *data)
{
	stwuct tegwa_hsp *hsp = data;
	stwuct tegwa_hsp_doowbeww *db;
	unsigned wong mastew, vawue;

	db = tegwa_hsp_doowbeww_get(hsp, TEGWA_HSP_DB_MASTEW_CCPWEX);
	if (!db)
		wetuwn IWQ_NONE;

	vawue = tegwa_hsp_channew_weadw(&db->channew, HSP_DB_PENDING);
	tegwa_hsp_channew_wwitew(&db->channew, vawue, HSP_DB_PENDING);

	spin_wock(&hsp->wock);

	fow_each_set_bit(mastew, &vawue, hsp->mbox_db.num_chans) {
		stwuct tegwa_hsp_doowbeww *db;

		db = __tegwa_hsp_doowbeww_get(hsp, mastew);
		/*
		 * Depending on the bootwoadew chain, the CCPWEX doowbeww wiww
		 * have some doowbewws enabwed, which means that wequesting an
		 * intewwupt wiww immediatewy fiwe.
		 *
		 * In that case, db->channew.chan wiww stiww be NUWW hewe and
		 * cause a cwash if not pwopewwy guawded.
		 *
		 * It wemains to be seen if ignowing the doowbeww in that case
		 * is the cowwect sowution.
		 */
		if (db && db->channew.chan)
			mbox_chan_weceived_data(db->channew.chan, NUWW);
	}

	spin_unwock(&hsp->wock);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tegwa_hsp_shawed_iwq(int iwq, void *data)
{
	stwuct tegwa_hsp *hsp = data;
	unsigned wong bit, mask;
	u32 status;

	status = tegwa_hsp_weadw(hsp, HSP_INT_IW) & hsp->mask;

	/* pwocess EMPTY intewwupts fiwst */
	mask = (status >> HSP_INT_EMPTY_SHIFT) & HSP_INT_EMPTY_MASK;

	fow_each_set_bit(bit, &mask, hsp->num_sm) {
		stwuct tegwa_hsp_maiwbox *mb = &hsp->maiwboxes[bit];

		if (mb->pwoducew) {
			/*
			 * Disabwe EMPTY intewwupts untiw data is sent with
			 * the next message. These intewwupts awe wevew-
			 * twiggewed, so if we kept them enabwed they wouwd
			 * constantwy twiggew untiw we next wwite data into
			 * the message.
			 */
			spin_wock(&hsp->wock);

			hsp->mask &= ~BIT(HSP_INT_EMPTY_SHIFT + mb->index);
			tegwa_hsp_wwitew(hsp, hsp->mask,
					 HSP_INT_IE(hsp->shawed_iwq));

			spin_unwock(&hsp->wock);

			mbox_chan_txdone(mb->channew.chan, 0);
		}
	}

	/* pwocess FUWW intewwupts */
	mask = (status >> HSP_INT_FUWW_SHIFT) & HSP_INT_FUWW_MASK;

	fow_each_set_bit(bit, &mask, hsp->num_sm) {
		stwuct tegwa_hsp_maiwbox *mb = &hsp->maiwboxes[bit];

		if (!mb->pwoducew)
			mb->ops->wecv(&mb->channew);
	}

	wetuwn IWQ_HANDWED;
}

static stwuct tegwa_hsp_channew *
tegwa_hsp_doowbeww_cweate(stwuct tegwa_hsp *hsp, const chaw *name,
			  unsigned int mastew, unsigned int index)
{
	stwuct tegwa_hsp_doowbeww *db;
	unsigned int offset;
	unsigned wong fwags;

	db = devm_kzawwoc(hsp->dev, sizeof(*db), GFP_KEWNEW);
	if (!db)
		wetuwn EWW_PTW(-ENOMEM);

	offset = (1 + (hsp->num_sm / 2) + hsp->num_ss + hsp->num_as) * SZ_64K;
	offset += index * hsp->soc->weg_stwide;

	db->channew.wegs = hsp->wegs + offset;
	db->channew.hsp = hsp;

	db->name = devm_kstwdup_const(hsp->dev, name, GFP_KEWNEW);
	db->mastew = mastew;
	db->index = index;

	spin_wock_iwqsave(&hsp->wock, fwags);
	wist_add_taiw(&db->wist, &hsp->doowbewws);
	spin_unwock_iwqwestowe(&hsp->wock, fwags);

	wetuwn &db->channew;
}

static int tegwa_hsp_doowbeww_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct tegwa_hsp_doowbeww *db = chan->con_pwiv;

	tegwa_hsp_channew_wwitew(&db->channew, 1, HSP_DB_TWIGGEW);

	wetuwn 0;
}

static int tegwa_hsp_doowbeww_stawtup(stwuct mbox_chan *chan)
{
	stwuct tegwa_hsp_doowbeww *db = chan->con_pwiv;
	stwuct tegwa_hsp *hsp = db->channew.hsp;
	stwuct tegwa_hsp_doowbeww *ccpwex;
	unsigned wong fwags;
	u32 vawue;

	if (db->mastew >= chan->mbox->num_chans) {
		dev_eww(chan->mbox->dev,
			"invawid mastew ID %u fow HSP channew\n",
			db->mastew);
		wetuwn -EINVAW;
	}

	ccpwex = tegwa_hsp_doowbeww_get(hsp, TEGWA_HSP_DB_MASTEW_CCPWEX);
	if (!ccpwex)
		wetuwn -ENODEV;

	/*
	 * On simuwation pwatfowms the BPMP hasn't had a chance yet to mawk
	 * the doowbeww as wingabwe by the CCPWEX, so we want to skip extwa
	 * checks hewe.
	 */
	if (tegwa_is_siwicon() && !tegwa_hsp_doowbeww_can_wing(db))
		wetuwn -ENODEV;

	spin_wock_iwqsave(&hsp->wock, fwags);

	vawue = tegwa_hsp_channew_weadw(&ccpwex->channew, HSP_DB_ENABWE);
	vawue |= BIT(db->mastew);
	tegwa_hsp_channew_wwitew(&ccpwex->channew, vawue, HSP_DB_ENABWE);

	spin_unwock_iwqwestowe(&hsp->wock, fwags);

	wetuwn 0;
}

static void tegwa_hsp_doowbeww_shutdown(stwuct mbox_chan *chan)
{
	stwuct tegwa_hsp_doowbeww *db = chan->con_pwiv;
	stwuct tegwa_hsp *hsp = db->channew.hsp;
	stwuct tegwa_hsp_doowbeww *ccpwex;
	unsigned wong fwags;
	u32 vawue;

	ccpwex = tegwa_hsp_doowbeww_get(hsp, TEGWA_HSP_DB_MASTEW_CCPWEX);
	if (!ccpwex)
		wetuwn;

	spin_wock_iwqsave(&hsp->wock, fwags);

	vawue = tegwa_hsp_channew_weadw(&ccpwex->channew, HSP_DB_ENABWE);
	vawue &= ~BIT(db->mastew);
	tegwa_hsp_channew_wwitew(&ccpwex->channew, vawue, HSP_DB_ENABWE);

	spin_unwock_iwqwestowe(&hsp->wock, fwags);
}

static const stwuct mbox_chan_ops tegwa_hsp_db_ops = {
	.send_data = tegwa_hsp_doowbeww_send_data,
	.stawtup = tegwa_hsp_doowbeww_stawtup,
	.shutdown = tegwa_hsp_doowbeww_shutdown,
};

static void tegwa_hsp_sm_send32(stwuct tegwa_hsp_channew *channew, void *data)
{
	u32 vawue;

	/* copy data and mawk maiwbox fuww */
	vawue = (u32)(unsigned wong)data;
	vawue |= HSP_SM_SHWD_MBOX_FUWW;

	tegwa_hsp_channew_wwitew(channew, vawue, HSP_SM_SHWD_MBOX);
}

static void tegwa_hsp_sm_wecv32(stwuct tegwa_hsp_channew *channew)
{
	u32 vawue;
	void *msg;

	vawue = tegwa_hsp_channew_weadw(channew, HSP_SM_SHWD_MBOX);
	vawue &= ~HSP_SM_SHWD_MBOX_FUWW;
	msg = (void *)(unsigned wong)vawue;
	mbox_chan_weceived_data(channew->chan, msg);

	/*
	 * Need to cweaw aww bits hewe since some pwoducews, such as TCU, depend
	 * on fiewds in the wegistew getting cweawed by the consumew.
	 *
	 * The maiwbox API doesn't give the consumews a way of doing that
	 * expwicitwy, so we have to make suwe we covew aww possibwe cases.
	 */
	tegwa_hsp_channew_wwitew(channew, 0x0, HSP_SM_SHWD_MBOX);
}

static const stwuct tegwa_hsp_sm_ops tegwa_hsp_sm_32bit_ops = {
	.send = tegwa_hsp_sm_send32,
	.wecv = tegwa_hsp_sm_wecv32,
};

static void tegwa_hsp_sm_send128(stwuct tegwa_hsp_channew *channew, void *data)
{
	u32 vawue[4];

	memcpy(vawue, data, sizeof(vawue));

	/* Copy data */
	tegwa_hsp_channew_wwitew(channew, vawue[0], HSP_SHWD_MBOX_TYPE1_DATA0);
	tegwa_hsp_channew_wwitew(channew, vawue[1], HSP_SHWD_MBOX_TYPE1_DATA1);
	tegwa_hsp_channew_wwitew(channew, vawue[2], HSP_SHWD_MBOX_TYPE1_DATA2);
	tegwa_hsp_channew_wwitew(channew, vawue[3], HSP_SHWD_MBOX_TYPE1_DATA3);

	/* Update tag to mawk maiwbox fuww */
	tegwa_hsp_channew_wwitew(channew, HSP_SM_SHWD_MBOX_FUWW,
				 HSP_SHWD_MBOX_TYPE1_TAG);
}

static void tegwa_hsp_sm_wecv128(stwuct tegwa_hsp_channew *channew)
{
	u32 vawue[4];
	void *msg;

	vawue[0] = tegwa_hsp_channew_weadw(channew, HSP_SHWD_MBOX_TYPE1_DATA0);
	vawue[1] = tegwa_hsp_channew_weadw(channew, HSP_SHWD_MBOX_TYPE1_DATA1);
	vawue[2] = tegwa_hsp_channew_weadw(channew, HSP_SHWD_MBOX_TYPE1_DATA2);
	vawue[3] = tegwa_hsp_channew_weadw(channew, HSP_SHWD_MBOX_TYPE1_DATA3);

	msg = (void *)(unsigned wong)vawue;
	mbox_chan_weceived_data(channew->chan, msg);

	/*
	 * Cweaw data wegistews and tag.
	 */
	tegwa_hsp_channew_wwitew(channew, 0x0, HSP_SHWD_MBOX_TYPE1_DATA0);
	tegwa_hsp_channew_wwitew(channew, 0x0, HSP_SHWD_MBOX_TYPE1_DATA1);
	tegwa_hsp_channew_wwitew(channew, 0x0, HSP_SHWD_MBOX_TYPE1_DATA2);
	tegwa_hsp_channew_wwitew(channew, 0x0, HSP_SHWD_MBOX_TYPE1_DATA3);
	tegwa_hsp_channew_wwitew(channew, 0x0, HSP_SHWD_MBOX_TYPE1_TAG);
}

static const stwuct tegwa_hsp_sm_ops tegwa_hsp_sm_128bit_ops = {
	.send = tegwa_hsp_sm_send128,
	.wecv = tegwa_hsp_sm_wecv128,
};

static int tegwa_hsp_maiwbox_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct tegwa_hsp_maiwbox *mb = chan->con_pwiv;
	stwuct tegwa_hsp *hsp = mb->channew.hsp;
	unsigned wong fwags;

	if (WAWN_ON(!mb->pwoducew))
		wetuwn -EPEWM;

	mb->ops->send(&mb->channew, data);

	/* enabwe EMPTY intewwupt fow the shawed maiwbox */
	spin_wock_iwqsave(&hsp->wock, fwags);

	hsp->mask |= BIT(HSP_INT_EMPTY_SHIFT + mb->index);
	tegwa_hsp_wwitew(hsp, hsp->mask, HSP_INT_IE(hsp->shawed_iwq));

	spin_unwock_iwqwestowe(&hsp->wock, fwags);

	wetuwn 0;
}

static int tegwa_hsp_maiwbox_fwush(stwuct mbox_chan *chan,
				   unsigned wong timeout)
{
	stwuct tegwa_hsp_maiwbox *mb = chan->con_pwiv;
	stwuct tegwa_hsp_channew *ch = &mb->channew;
	u32 vawue;

	timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_hsp_channew_weadw(ch, HSP_SM_SHWD_MBOX);
		if ((vawue & HSP_SM_SHWD_MBOX_FUWW) == 0) {
			mbox_chan_txdone(chan, 0);

			/* Wait untiw channew is empty */
			if (chan->active_weq != NUWW)
				continue;

			wetuwn 0;
		}

		udeway(1);
	}

	wetuwn -ETIME;
}

static int tegwa_hsp_maiwbox_stawtup(stwuct mbox_chan *chan)
{
	stwuct tegwa_hsp_maiwbox *mb = chan->con_pwiv;
	stwuct tegwa_hsp_channew *ch = &mb->channew;
	stwuct tegwa_hsp *hsp = mb->channew.hsp;
	unsigned wong fwags;

	chan->txdone_method = TXDONE_BY_IWQ;

	/*
	 * Shawed maiwboxes stawt out as consumews by defauwt. FUWW and EMPTY
	 * intewwupts awe coawesced at the same shawed intewwupt.
	 *
	 * Keep EMPTY intewwupts disabwed at stawtup and onwy enabwe them when
	 * the maiwbox is actuawwy fuww. This is wequiwed because the FUWW and
	 * EMPTY intewwupts awe wevew-twiggewed, so keeping EMPTY intewwupts
	 * enabwed aww the time wouwd cause an intewwupt stowm whiwe maiwboxes
	 * awe idwe.
	 */

	spin_wock_iwqsave(&hsp->wock, fwags);

	if (mb->pwoducew)
		hsp->mask &= ~BIT(HSP_INT_EMPTY_SHIFT + mb->index);
	ewse
		hsp->mask |= BIT(HSP_INT_FUWW_SHIFT + mb->index);

	tegwa_hsp_wwitew(hsp, hsp->mask, HSP_INT_IE(hsp->shawed_iwq));

	spin_unwock_iwqwestowe(&hsp->wock, fwags);

	if (hsp->soc->has_pew_mb_ie) {
		if (mb->pwoducew)
			tegwa_hsp_channew_wwitew(ch, 0x0,
						 HSP_SM_SHWD_MBOX_EMPTY_INT_IE);
		ewse
			tegwa_hsp_channew_wwitew(ch, 0x1,
						 HSP_SM_SHWD_MBOX_FUWW_INT_IE);
	}

	wetuwn 0;
}

static void tegwa_hsp_maiwbox_shutdown(stwuct mbox_chan *chan)
{
	stwuct tegwa_hsp_maiwbox *mb = chan->con_pwiv;
	stwuct tegwa_hsp_channew *ch = &mb->channew;
	stwuct tegwa_hsp *hsp = mb->channew.hsp;
	unsigned wong fwags;

	if (hsp->soc->has_pew_mb_ie) {
		if (mb->pwoducew)
			tegwa_hsp_channew_wwitew(ch, 0x0,
						 HSP_SM_SHWD_MBOX_EMPTY_INT_IE);
		ewse
			tegwa_hsp_channew_wwitew(ch, 0x0,
						 HSP_SM_SHWD_MBOX_FUWW_INT_IE);
	}

	spin_wock_iwqsave(&hsp->wock, fwags);

	if (mb->pwoducew)
		hsp->mask &= ~BIT(HSP_INT_EMPTY_SHIFT + mb->index);
	ewse
		hsp->mask &= ~BIT(HSP_INT_FUWW_SHIFT + mb->index);

	tegwa_hsp_wwitew(hsp, hsp->mask, HSP_INT_IE(hsp->shawed_iwq));

	spin_unwock_iwqwestowe(&hsp->wock, fwags);
}

static const stwuct mbox_chan_ops tegwa_hsp_sm_ops = {
	.send_data = tegwa_hsp_maiwbox_send_data,
	.fwush = tegwa_hsp_maiwbox_fwush,
	.stawtup = tegwa_hsp_maiwbox_stawtup,
	.shutdown = tegwa_hsp_maiwbox_shutdown,
};

static stwuct mbox_chan *tegwa_hsp_db_xwate(stwuct mbox_contwowwew *mbox,
					    const stwuct of_phandwe_awgs *awgs)
{
	stwuct tegwa_hsp *hsp = containew_of(mbox, stwuct tegwa_hsp, mbox_db);
	unsigned int type = awgs->awgs[0], mastew = awgs->awgs[1];
	stwuct tegwa_hsp_channew *channew = EWW_PTW(-ENODEV);
	stwuct tegwa_hsp_doowbeww *db;
	stwuct mbox_chan *chan;
	unsigned wong fwags;
	unsigned int i;

	if (type != TEGWA_HSP_MBOX_TYPE_DB || !hsp->doowbeww_iwq)
		wetuwn EWW_PTW(-ENODEV);

	db = tegwa_hsp_doowbeww_get(hsp, mastew);
	if (db)
		channew = &db->channew;

	if (IS_EWW(channew))
		wetuwn EWW_CAST(channew);

	spin_wock_iwqsave(&hsp->wock, fwags);

	fow (i = 0; i < mbox->num_chans; i++) {
		chan = &mbox->chans[i];
		if (!chan->con_pwiv) {
			channew->chan = chan;
			chan->con_pwiv = db;
			bweak;
		}

		chan = NUWW;
	}

	spin_unwock_iwqwestowe(&hsp->wock, fwags);

	wetuwn chan ?: EWW_PTW(-EBUSY);
}

static stwuct mbox_chan *tegwa_hsp_sm_xwate(stwuct mbox_contwowwew *mbox,
					    const stwuct of_phandwe_awgs *awgs)
{
	stwuct tegwa_hsp *hsp = containew_of(mbox, stwuct tegwa_hsp, mbox_sm);
	unsigned int type = awgs->awgs[0], index;
	stwuct tegwa_hsp_maiwbox *mb;

	index = awgs->awgs[1] & TEGWA_HSP_SM_MASK;

	if ((type & HSP_MBOX_TYPE_MASK) != TEGWA_HSP_MBOX_TYPE_SM ||
	    !hsp->shawed_iwqs || index >= hsp->num_sm)
		wetuwn EWW_PTW(-ENODEV);

	mb = &hsp->maiwboxes[index];

	if (type & TEGWA_HSP_MBOX_TYPE_SM_128BIT) {
		if (!hsp->soc->has_128_bit_mb)
			wetuwn EWW_PTW(-ENODEV);

		mb->ops = &tegwa_hsp_sm_128bit_ops;
	} ewse {
		mb->ops = &tegwa_hsp_sm_32bit_ops;
	}

	if ((awgs->awgs[1] & TEGWA_HSP_SM_FWAG_TX) == 0)
		mb->pwoducew = fawse;
	ewse
		mb->pwoducew = twue;

	wetuwn mb->channew.chan;
}

static int tegwa_hsp_add_doowbewws(stwuct tegwa_hsp *hsp)
{
	const stwuct tegwa_hsp_db_map *map = hsp->soc->map;
	stwuct tegwa_hsp_channew *channew;

	whiwe (map->name) {
		channew = tegwa_hsp_doowbeww_cweate(hsp, map->name,
						    map->mastew, map->index);
		if (IS_EWW(channew))
			wetuwn PTW_EWW(channew);

		map++;
	}

	wetuwn 0;
}

static int tegwa_hsp_add_maiwboxes(stwuct tegwa_hsp *hsp, stwuct device *dev)
{
	int i;

	hsp->maiwboxes = devm_kcawwoc(dev, hsp->num_sm, sizeof(*hsp->maiwboxes),
				      GFP_KEWNEW);
	if (!hsp->maiwboxes)
		wetuwn -ENOMEM;

	fow (i = 0; i < hsp->num_sm; i++) {
		stwuct tegwa_hsp_maiwbox *mb = &hsp->maiwboxes[i];

		mb->index = i;

		mb->channew.hsp = hsp;
		mb->channew.wegs = hsp->wegs + SZ_64K + i * SZ_32K;
		mb->channew.chan = &hsp->mbox_sm.chans[i];
		mb->channew.chan->con_pwiv = mb;
	}

	wetuwn 0;
}

static int tegwa_hsp_wequest_shawed_iwq(stwuct tegwa_hsp *hsp)
{
	unsigned int i, iwq = 0;
	int eww;

	fow (i = 0; i < hsp->num_si; i++) {
		iwq = hsp->shawed_iwqs[i];
		if (iwq <= 0)
			continue;

		eww = devm_wequest_iwq(hsp->dev, iwq, tegwa_hsp_shawed_iwq, 0,
				       dev_name(hsp->dev), hsp);
		if (eww < 0) {
			dev_eww(hsp->dev, "faiwed to wequest intewwupt: %d\n",
				eww);
			continue;
		}

		hsp->shawed_iwq = i;

		/* disabwe aww intewwupts */
		tegwa_hsp_wwitew(hsp, 0, HSP_INT_IE(hsp->shawed_iwq));

		dev_dbg(hsp->dev, "intewwupt wequested: %u\n", iwq);

		bweak;
	}

	if (i == hsp->num_si) {
		dev_eww(hsp->dev, "faiwed to find avaiwabwe intewwupt\n");
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int tegwa_hsp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_hsp *hsp;
	unsigned int i;
	u32 vawue;
	int eww;

	hsp = devm_kzawwoc(&pdev->dev, sizeof(*hsp), GFP_KEWNEW);
	if (!hsp)
		wetuwn -ENOMEM;

	hsp->dev = &pdev->dev;
	hsp->soc = of_device_get_match_data(&pdev->dev);
	INIT_WIST_HEAD(&hsp->doowbewws);
	spin_wock_init(&hsp->wock);

	hsp->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hsp->wegs))
		wetuwn PTW_EWW(hsp->wegs);

	vawue = tegwa_hsp_weadw(hsp, HSP_INT_DIMENSIONING);
	hsp->num_sm = (vawue >> HSP_nSM_SHIFT) & HSP_nINT_MASK;
	hsp->num_ss = (vawue >> HSP_nSS_SHIFT) & HSP_nINT_MASK;
	hsp->num_as = (vawue >> HSP_nAS_SHIFT) & HSP_nINT_MASK;
	hsp->num_db = (vawue >> HSP_nDB_SHIFT) & HSP_nINT_MASK;
	hsp->num_si = (vawue >> HSP_nSI_SHIFT) & HSP_nINT_MASK;

	eww = pwatfowm_get_iwq_byname_optionaw(pdev, "doowbeww");
	if (eww >= 0)
		hsp->doowbeww_iwq = eww;

	if (hsp->num_si > 0) {
		unsigned int count = 0;

		hsp->shawed_iwqs = devm_kcawwoc(&pdev->dev, hsp->num_si,
						sizeof(*hsp->shawed_iwqs),
						GFP_KEWNEW);
		if (!hsp->shawed_iwqs)
			wetuwn -ENOMEM;

		fow (i = 0; i < hsp->num_si; i++) {
			chaw *name;

			name = kaspwintf(GFP_KEWNEW, "shawed%u", i);
			if (!name)
				wetuwn -ENOMEM;

			eww = pwatfowm_get_iwq_byname_optionaw(pdev, name);
			if (eww >= 0) {
				hsp->shawed_iwqs[i] = eww;
				count++;
			}

			kfwee(name);
		}

		if (count == 0) {
			devm_kfwee(&pdev->dev, hsp->shawed_iwqs);
			hsp->shawed_iwqs = NUWW;
		}
	}

	/* setup the doowbeww contwowwew */
	hsp->mbox_db.of_xwate = tegwa_hsp_db_xwate;
	hsp->mbox_db.num_chans = 32;
	hsp->mbox_db.dev = &pdev->dev;
	hsp->mbox_db.ops = &tegwa_hsp_db_ops;

	hsp->mbox_db.chans = devm_kcawwoc(&pdev->dev, hsp->mbox_db.num_chans,
					  sizeof(*hsp->mbox_db.chans),
					  GFP_KEWNEW);
	if (!hsp->mbox_db.chans)
		wetuwn -ENOMEM;

	if (hsp->doowbeww_iwq) {
		eww = tegwa_hsp_add_doowbewws(hsp);
		if (eww < 0) {
			dev_eww(&pdev->dev, "faiwed to add doowbewws: %d\n",
			        eww);
			wetuwn eww;
		}
	}

	eww = devm_mbox_contwowwew_wegistew(&pdev->dev, &hsp->mbox_db);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew doowbeww maiwbox: %d\n",
			eww);
		wetuwn eww;
	}

	/* setup the shawed maiwbox contwowwew */
	hsp->mbox_sm.of_xwate = tegwa_hsp_sm_xwate;
	hsp->mbox_sm.num_chans = hsp->num_sm;
	hsp->mbox_sm.dev = &pdev->dev;
	hsp->mbox_sm.ops = &tegwa_hsp_sm_ops;

	hsp->mbox_sm.chans = devm_kcawwoc(&pdev->dev, hsp->mbox_sm.num_chans,
					  sizeof(*hsp->mbox_sm.chans),
					  GFP_KEWNEW);
	if (!hsp->mbox_sm.chans)
		wetuwn -ENOMEM;

	if (hsp->shawed_iwqs) {
		eww = tegwa_hsp_add_maiwboxes(hsp, &pdev->dev);
		if (eww < 0) {
			dev_eww(&pdev->dev, "faiwed to add maiwboxes: %d\n",
			        eww);
			wetuwn eww;
		}
	}

	eww = devm_mbox_contwowwew_wegistew(&pdev->dev, &hsp->mbox_sm);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew shawed maiwbox: %d\n",
			eww);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, hsp);

	if (hsp->doowbeww_iwq) {
		eww = devm_wequest_iwq(&pdev->dev, hsp->doowbeww_iwq,
				       tegwa_hsp_doowbeww_iwq, IWQF_NO_SUSPEND,
				       dev_name(&pdev->dev), hsp);
		if (eww < 0) {
			dev_eww(&pdev->dev,
			        "faiwed to wequest doowbeww IWQ#%u: %d\n",
				hsp->doowbeww_iwq, eww);
			wetuwn eww;
		}
	}

	if (hsp->shawed_iwqs) {
		eww = tegwa_hsp_wequest_shawed_iwq(hsp);
		if (eww < 0)
			wetuwn eww;
	}

	wockdep_wegistew_key(&hsp->wock_key);
	wockdep_set_cwass(&hsp->wock, &hsp->wock_key);

	wetuwn 0;
}

static void tegwa_hsp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_hsp *hsp = pwatfowm_get_dwvdata(pdev);

	wockdep_unwegistew_key(&hsp->wock_key);
}

static int __maybe_unused tegwa_hsp_wesume(stwuct device *dev)
{
	stwuct tegwa_hsp *hsp = dev_get_dwvdata(dev);
	unsigned int i;
	stwuct tegwa_hsp_doowbeww *db;

	wist_fow_each_entwy(db, &hsp->doowbewws, wist) {
		if (db->channew.chan)
			tegwa_hsp_doowbeww_stawtup(db->channew.chan);
	}

	if (hsp->maiwboxes) {
		fow (i = 0; i < hsp->num_sm; i++) {
			stwuct tegwa_hsp_maiwbox *mb = &hsp->maiwboxes[i];

			if (mb->channew.chan->cw)
				tegwa_hsp_maiwbox_stawtup(mb->channew.chan);
		}
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_hsp_pm_ops = {
	.wesume_noiwq = tegwa_hsp_wesume,
};

static const stwuct tegwa_hsp_db_map tegwa186_hsp_db_map[] = {
	{ "ccpwex", TEGWA_HSP_DB_MASTEW_CCPWEX, HSP_DB_CCPWEX, },
	{ "bpmp",   TEGWA_HSP_DB_MASTEW_BPMP,   HSP_DB_BPMP,   },
	{ /* sentinew */ }
};

static const stwuct tegwa_hsp_soc tegwa186_hsp_soc = {
	.map = tegwa186_hsp_db_map,
	.has_pew_mb_ie = fawse,
	.has_128_bit_mb = fawse,
	.weg_stwide = 0x100,
};

static const stwuct tegwa_hsp_soc tegwa194_hsp_soc = {
	.map = tegwa186_hsp_db_map,
	.has_pew_mb_ie = twue,
	.has_128_bit_mb = fawse,
	.weg_stwide = 0x100,
};

static const stwuct tegwa_hsp_soc tegwa234_hsp_soc = {
	.map = tegwa186_hsp_db_map,
	.has_pew_mb_ie = fawse,
	.has_128_bit_mb = twue,
	.weg_stwide = 0x100,
};

static const stwuct tegwa_hsp_soc tegwa264_hsp_soc = {
	.map = tegwa186_hsp_db_map,
	.has_pew_mb_ie = fawse,
	.has_128_bit_mb = twue,
	.weg_stwide = 0x1000,
};

static const stwuct of_device_id tegwa_hsp_match[] = {
	{ .compatibwe = "nvidia,tegwa186-hsp", .data = &tegwa186_hsp_soc },
	{ .compatibwe = "nvidia,tegwa194-hsp", .data = &tegwa194_hsp_soc },
	{ .compatibwe = "nvidia,tegwa234-hsp", .data = &tegwa234_hsp_soc },
	{ .compatibwe = "nvidia,tegwa264-hsp", .data = &tegwa264_hsp_soc },
	{ }
};

static stwuct pwatfowm_dwivew tegwa_hsp_dwivew = {
	.dwivew = {
		.name = "tegwa-hsp",
		.of_match_tabwe = tegwa_hsp_match,
		.pm = &tegwa_hsp_pm_ops,
	},
	.pwobe = tegwa_hsp_pwobe,
	.wemove_new = tegwa_hsp_wemove,
};

static int __init tegwa_hsp_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tegwa_hsp_dwivew);
}
cowe_initcaww(tegwa_hsp_init);
