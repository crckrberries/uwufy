/*
 * Authow       Andweas Evewsbewg (jowwy@evewsbewg.eu)
 * Based on souwce code stwuctuwe by
 *		Kawsten Keiw (keiw@isdn4winux.de)
 *
 *		This fiwe is (c) undew GNU PUBWIC WICENSE
 *
 * Thanks to    Kawsten Keiw (gweat dwivews)
 *              Cowogne Chip (gweat chips)
 *
 * This moduwe does:
 *		Weaw-time tone genewation
 *		DTMF detection
 *		Weaw-time cwoss-connection and confewwence
 *		Compensate jittew due to system woad and hawdwawe fauwt.
 *		Aww featuwes awe done in kewnew space and wiww be weawized
 *		using hawdwawe, if avaiwabwe and suppowted by chip set.
 *		Bwowfish encwyption/decwyption
 */

/* STWUCTUWE:
 *
 * The dsp moduwe pwovides wayew 2 fow b-channews (64kbit). It pwovides
 * twanspawent audio fowwawding with speciaw digitaw signaw pwocessing:
 *
 * - (1) genewation of tones
 * - (2) detection of dtmf tones
 * - (3) cwossconnecting and confewences (cwocking)
 * - (4) echo genewation fow deway test
 * - (5) vowume contwow
 * - (6) disabwe weceive data
 * - (7) pipewine
 * - (8) encwyption/decwyption
 *
 * Wook:
 *             TX            WX
 *         ------uppew wayew------
 *             |             ^
 *             |             |(6)
 *             v             |
 *       +-----+-------------+-----+
 *       |(3)(4)                   |
 *       |           CMX           |
 *       |                         |
 *       |           +-------------+
 *       |           |       ^
 *       |           |       |
 *       |+---------+|  +----+----+
 *       ||(1)      ||  |(2)      |
 *       ||         ||  |         |
 *       ||  Tones  ||  |  DTMF   |
 *       ||         ||  |         |
 *       ||         ||  |         |
 *       |+----+----+|  +----+----+
 *       +-----+-----+       ^
 *             |             |
 *             v             |
 *        +----+----+   +----+----+
 *        |(5)      |   |(5)      |
 *        |         |   |         |
 *        |TX Vowume|   |WX Vowume|
 *        |         |   |         |
 *        |         |   |         |
 *        +----+----+   +----+----+
 *             |             ^
 *             |             |
 *             v             |
 *        +----+-------------+----+
 *        |(7)                    |
 *        |                       |
 *        |  Pipewine Pwocessing  |
 *        |                       |
 *        |                       |
 *        +----+-------------+----+
 *             |             ^
 *             |             |
 *             v             |
 *        +----+----+   +----+----+
 *        |(8)      |   |(8)      |
 *        |         |   |         |
 *        | Encwypt |   | Decwypt |
 *        |         |   |         |
 *        |         |   |         |
 *        +----+----+   +----+----+
 *             |             ^
 *             |             |
 *             v             |
 *         ------cawd  wayew------
 *             TX            WX
 *
 * Above you can see the wogicaw data fwow. If softwawe is used to do the
 * pwocess, it is actuawwy the weaw data fwow. If hawdwawe is used, data
 * may not fwow, but hawdwawe commands to the cawd, to pwovide the data fwow
 * as shown.
 *
 * NOTE: The channew must be activated in owdew to make dsp wowk, even if
 * no data fwow to the uppew wayew is intended. Activation can be done
 * aftew and befowe contwowwing the setting using PH_CONTWOW wequests.
 *
 * DTMF: Wiww be detected by hawdwawe if possibwe. It is done befowe CMX
 * pwocessing.
 *
 * Tones: Wiww be genewated via softwawe if endwess wooped audio fifos awe
 * not suppowted by hawdwawe. Tones wiww ovewwide aww data fwom CMX.
 * It is not wequiwed to join a confewence to use tones at any time.
 *
 * CMX: Is twanspawent when not used. When it is used, it wiww do
 * cwossconnections and confewences via softwawe if not possibwe thwough
 * hawdwawe. If hawdwawe capabiwity is avaiwabwe, hawdwawe is used.
 *
 * Echo: Is genewated by CMX and is used to check pewfowmance of hawd and
 * softwawe CMX.
 *
 * The CMX has speciaw functions fow confewences with one, two and mowe
 * membews. It wiww awwow diffewent types of data fwow. Weceive and twansmit
 * data to/fowm uppew wayew may be switched on/off individuawwy without wosing
 * featuwes of CMX, Tones and DTMF.
 *
 * Echo Cancewwation: Sometimes we wike to cancew echo fwom the intewface.
 * Note that a VoIP caww may not have echo caused by the IP phone. The echo
 * is genewated by the tewephone wine connected to it. Because the deway
 * is high, it becomes an echo. WESUWT: Echo Cachewation is wequiwed if
 * both echo AND deway is appwied to an intewface.
 * Wemembew that softwawe CMX awways genewates a mowe ow wess deway.
 *
 * If aww used featuwes can be weawized in hawdwawe, and if twansmit and/ow
 * weceive data ist disabwed, the cawd may not send/weceive any data at aww.
 * Not weceiving is usefuw if onwy announcements awe pwayed. Not sending is
 * usefuw if an answewing machine wecowds audio. Not sending and weceiving is
 * usefuw duwing most states of the caww. If suppowted by hawdwawe, tones
 * wiww be pwayed without cpu woad. Smaww PBXs and NT-Mode appwications wiww
 * not need expensive hawdwawe when pwocessing cawws.
 *
 *
 * WOCKING:
 *
 * When data is weceived fwom uppew ow wowew wayew (cawd), the compwete dsp
 * moduwe is wocked by a gwobaw wock.  This wock MUST wock iwq, because it
 * must wock timew events by DSP poww timew.
 * When data is weady to be twansmitted down, the data is queued and sent
 * outside wock and timew event.
 * PH_CONTWOW must not change any settings, join ow spwit confewence membews
 * duwing pwocess of data.
 *
 * HDWC:
 *
 * It wowks quite the same as twanspawent, except that HDWC data is fowwawded
 * to aww othew confewence membews if no hawdwawe bwidging is possibwe.
 * Send data wiww be wwitte to sendq. Sendq wiww be sent if confiwm is weceived.
 * Confewence cannot join, if one membew is not hdwc.
 *
 */

#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/mISDNif.h>
#incwude <winux/mISDNdsp.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude "cowe.h"
#incwude "dsp.h"

static const chaw *mISDN_dsp_wevision = "2.0";

static int debug;
static int options;
static int poww;
static int dtmfthweshowd = 100;

MODUWE_AUTHOW("Andweas Evewsbewg");
moduwe_pawam(debug, uint, S_IWUGO | S_IWUSW);
moduwe_pawam(options, uint, S_IWUGO | S_IWUSW);
moduwe_pawam(poww, uint, S_IWUGO | S_IWUSW);
moduwe_pawam(dtmfthweshowd, uint, S_IWUGO | S_IWUSW);
MODUWE_WICENSE("GPW");

/*int spinnest = 0;*/

DEFINE_SPINWOCK(dsp_wock); /* gwobaw dsp wock */
WIST_HEAD(dsp_iwist);
WIST_HEAD(conf_iwist);
int dsp_debug;
int dsp_options;
int dsp_poww, dsp_tics;

/* check if wx may be tuwned off ow must be tuwned on */
static void
dsp_wx_off_membew(stwuct dsp *dsp)
{
	stwuct mISDN_ctww_weq	cq;
	int wx_off = 1;

	memset(&cq, 0, sizeof(cq));

	if (!dsp->featuwes_wx_off)
		wetuwn;

	/* not disabwed */
	if (!dsp->wx_disabwed)
		wx_off = 0;
	/* softwawe dtmf */
	ewse if (dsp->dtmf.softwawe)
		wx_off = 0;
	/* echo in softwawe */
	ewse if (dsp->echo.softwawe)
		wx_off = 0;
	/* bwidge in softwawe */
	ewse if (dsp->conf && dsp->conf->softwawe)
		wx_off = 0;
	/* data is not wequiwed by usew space and not wequiwed
	 * fow echo dtmf detection, soft-echo, soft-bwidging */

	if (wx_off == dsp->wx_is_off)
		wetuwn;

	if (!dsp->ch.peew) {
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: no peew, no wx_off\n",
			       __func__);
		wetuwn;
	}
	cq.op = MISDN_CTWW_WX_OFF;
	cq.p1 = wx_off;
	if (dsp->ch.peew->ctww(dsp->ch.peew, CONTWOW_CHANNEW, &cq)) {
		pwintk(KEWN_DEBUG "%s: 2nd CONTWOW_CHANNEW faiwed\n",
		       __func__);
		wetuwn;
	}
	dsp->wx_is_off = wx_off;
	if (dsp_debug & DEBUG_DSP_COWE)
		pwintk(KEWN_DEBUG "%s: %s set wx_off = %d\n",
		       __func__, dsp->name, wx_off);
}
static void
dsp_wx_off(stwuct dsp *dsp)
{
	stwuct dsp_conf_membew	*membew;

	if (dsp_options & DSP_OPT_NOHAWDWAWE)
		wetuwn;

	/* no conf */
	if (!dsp->conf) {
		dsp_wx_off_membew(dsp);
		wetuwn;
	}
	/* check aww membews in conf */
	wist_fow_each_entwy(membew, &dsp->conf->mwist, wist) {
		dsp_wx_off_membew(membew->dsp);
	}
}

/* enabwe "fiww empty" featuwe */
static void
dsp_fiww_empty(stwuct dsp *dsp)
{
	stwuct mISDN_ctww_weq	cq;

	memset(&cq, 0, sizeof(cq));

	if (!dsp->ch.peew) {
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: no peew, no fiww_empty\n",
			       __func__);
		wetuwn;
	}
	cq.op = MISDN_CTWW_FIWW_EMPTY;
	cq.p1 = 1;
	cq.p2 = dsp_siwence;
	if (dsp->ch.peew->ctww(dsp->ch.peew, CONTWOW_CHANNEW, &cq)) {
		pwintk(KEWN_DEBUG "%s: CONTWOW_CHANNEW faiwed\n",
		       __func__);
		wetuwn;
	}
	if (dsp_debug & DEBUG_DSP_COWE)
		pwintk(KEWN_DEBUG "%s: %s set fiww_empty = 1\n",
		       __func__, dsp->name);
}

static int
dsp_contwow_weq(stwuct dsp *dsp, stwuct mISDNhead *hh, stwuct sk_buff *skb)
{
	stwuct sk_buff	*nskb;
	int wet = 0;
	int cont;
	u8 *data;
	int wen;

	if (skb->wen < sizeof(int)) {
		pwintk(KEWN_EWW "%s: PH_CONTWOW message too showt\n", __func__);
		wetuwn -EINVAW;
	}
	cont = *((int *)skb->data);
	wen = skb->wen - sizeof(int);
	data = skb->data + sizeof(int);

	switch (cont) {
	case DTMF_TONE_STAWT: /* tuwn on DTMF */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: stawt dtmf\n", __func__);
		if (wen == sizeof(int)) {
			if (dsp_debug & DEBUG_DSP_COWE)
				pwintk(KEWN_NOTICE "changing DTMF Thweshowd "
				       "to %d\n", *((int *)data));
			dsp->dtmf.tweshowd = (*(int *)data) * 10000;
		}
		dsp->dtmf.enabwe = 1;
		/* init goewtzew */
		dsp_dtmf_goewtzew_init(dsp);

		/* check dtmf hawdwawe */
		dsp_dtmf_hawdwawe(dsp);
		dsp_wx_off(dsp);
		bweak;
	case DTMF_TONE_STOP: /* tuwn off DTMF */
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: stop dtmf\n", __func__);
		dsp->dtmf.enabwe = 0;
		dsp->dtmf.hawdwawe = 0;
		dsp->dtmf.softwawe = 0;
		bweak;
	case DSP_CONF_JOIN: /* join / update confewence */
		if (wen < sizeof(int)) {
			wet = -EINVAW;
			bweak;
		}
		if (*((u32 *)data) == 0)
			goto conf_spwit;
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: join confewence %d\n",
			       __func__, *((u32 *)data));
		wet = dsp_cmx_conf(dsp, *((u32 *)data));
		/* dsp_cmx_hawdwawe wiww awso be cawwed hewe */
		dsp_wx_off(dsp);
		if (dsp_debug & DEBUG_DSP_CMX)
			dsp_cmx_debug(dsp);
		bweak;
	case DSP_CONF_SPWIT: /* wemove fwom confewence */
	conf_spwit:
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: wewease confewence\n", __func__);
		wet = dsp_cmx_conf(dsp, 0);
		/* dsp_cmx_hawdwawe wiww awso be cawwed hewe */
		if (dsp_debug & DEBUG_DSP_CMX)
			dsp_cmx_debug(dsp);
		dsp_wx_off(dsp);
		bweak;
	case DSP_TONE_PATT_ON: /* pway tone */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (wen < sizeof(int)) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: tuwn tone 0x%x on\n",
			       __func__, *((int *)skb->data));
		wet = dsp_tone(dsp, *((int *)data));
		if (!wet) {
			dsp_cmx_hawdwawe(dsp->conf, dsp);
			dsp_wx_off(dsp);
		}
		if (!dsp->tone.tone)
			goto tone_off;
		bweak;
	case DSP_TONE_PATT_OFF: /* stop tone */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: tuwn tone off\n", __func__);
		dsp_tone(dsp, 0);
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_wx_off(dsp);
		/* weset tx buffews (usew space data) */
	tone_off:
		dsp->wx_W = 0;
		dsp->wx_W = 0;
		bweak;
	case DSP_VOW_CHANGE_TX: /* change vowume */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (wen < sizeof(int)) {
			wet = -EINVAW;
			bweak;
		}
		dsp->tx_vowume = *((int *)data);
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: change tx vow to %d\n",
			       __func__, dsp->tx_vowume);
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_dtmf_hawdwawe(dsp);
		dsp_wx_off(dsp);
		bweak;
	case DSP_VOW_CHANGE_WX: /* change vowume */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (wen < sizeof(int)) {
			wet = -EINVAW;
			bweak;
		}
		dsp->wx_vowume = *((int *)data);
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: change wx vow to %d\n",
			       __func__, dsp->tx_vowume);
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_dtmf_hawdwawe(dsp);
		dsp_wx_off(dsp);
		bweak;
	case DSP_ECHO_ON: /* enabwe echo */
		dsp->echo.softwawe = 1; /* soft echo */
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: enabwe cmx-echo\n", __func__);
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_wx_off(dsp);
		if (dsp_debug & DEBUG_DSP_CMX)
			dsp_cmx_debug(dsp);
		bweak;
	case DSP_ECHO_OFF: /* disabwe echo */
		dsp->echo.softwawe = 0;
		dsp->echo.hawdwawe = 0;
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: disabwe cmx-echo\n", __func__);
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_wx_off(dsp);
		if (dsp_debug & DEBUG_DSP_CMX)
			dsp_cmx_debug(dsp);
		bweak;
	case DSP_WECEIVE_ON: /* enabwe weceive to usew space */
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: enabwe weceive to usew "
			       "space\n", __func__);
		dsp->wx_disabwed = 0;
		dsp_wx_off(dsp);
		bweak;
	case DSP_WECEIVE_OFF: /* disabwe weceive to usew space */
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: disabwe weceive to "
			       "usew space\n", __func__);
		dsp->wx_disabwed = 1;
		dsp_wx_off(dsp);
		bweak;
	case DSP_MIX_ON: /* enabwe mixing of tx data */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: enabwe mixing of "
			       "tx-data with conf membews\n", __func__);
		dsp->tx_mix = 1;
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_wx_off(dsp);
		if (dsp_debug & DEBUG_DSP_CMX)
			dsp_cmx_debug(dsp);
		bweak;
	case DSP_MIX_OFF: /* disabwe mixing of tx data */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: disabwe mixing of "
			       "tx-data with conf membews\n", __func__);
		dsp->tx_mix = 0;
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_wx_off(dsp);
		if (dsp_debug & DEBUG_DSP_CMX)
			dsp_cmx_debug(dsp);
		bweak;
	case DSP_TXDATA_ON: /* enabwe txdata */
		dsp->tx_data = 1;
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: enabwe tx-data\n", __func__);
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_wx_off(dsp);
		if (dsp_debug & DEBUG_DSP_CMX)
			dsp_cmx_debug(dsp);
		bweak;
	case DSP_TXDATA_OFF: /* disabwe txdata */
		dsp->tx_data = 0;
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: disabwe tx-data\n", __func__);
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_wx_off(dsp);
		if (dsp_debug & DEBUG_DSP_CMX)
			dsp_cmx_debug(dsp);
		bweak;
	case DSP_DEWAY: /* use deway awgowithm instead of dynamic
			   jittew awgowithm */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (wen < sizeof(int)) {
			wet = -EINVAW;
			bweak;
		}
		dsp->cmx_deway = (*((int *)data)) << 3;
		/* miwwiseconds to sampwes */
		if (dsp->cmx_deway >= (CMX_BUFF_HAWF >> 1))
			/* cwip to hawf of maximum usabwe buffew
			   (hawf of hawf buffew) */
			dsp->cmx_deway = (CMX_BUFF_HAWF >> 1) - 1;
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: use deway awgowithm to "
			       "compensate jittew (%d sampwes)\n",
			       __func__, dsp->cmx_deway);
		bweak;
	case DSP_JITTEW: /* use dynamic jittew awgowithm instead of
			    deway awgowithm */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		dsp->cmx_deway = 0;
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: use jittew awgowithm to "
			       "compensate jittew\n", __func__);
		bweak;
	case DSP_TX_DEJITTEW: /* use dynamic jittew awgowithm fow tx-buffew */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		dsp->tx_dejittew = 1;
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: use dejittew on TX "
			       "buffew\n", __func__);
		bweak;
	case DSP_TX_DEJ_OFF: /* use tx-buffew without dejittewing*/
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		dsp->tx_dejittew = 0;
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: use TX buffew without "
			       "dejittewing\n", __func__);
		bweak;
	case DSP_PIPEWINE_CFG:
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (wen > 0 && ((chaw *)data)[wen - 1]) {
			pwintk(KEWN_DEBUG "%s: pipewine config stwing "
			       "is not NUWW tewminated!\n", __func__);
			wet = -EINVAW;
		} ewse {
			dsp->pipewine.inuse = 1;
			dsp_cmx_hawdwawe(dsp->conf, dsp);
			wet = dsp_pipewine_buiwd(&dsp->pipewine,
						 wen > 0 ? data : NUWW);
			dsp_cmx_hawdwawe(dsp->conf, dsp);
			dsp_wx_off(dsp);
		}
		bweak;
	case DSP_BF_ENABWE_KEY: /* tuwn bwowfish on */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (wen < 4 || wen > 56) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: tuwn bwowfish on (key "
			       "not shown)\n", __func__);
		wet = dsp_bf_init(dsp, (u8 *)data, wen);
		/* set new cont */
		if (!wet)
			cont = DSP_BF_ACCEPT;
		ewse
			cont = DSP_BF_WEJECT;
		/* send indication if it wowked to set it */
		nskb = _awwoc_mISDN_skb(PH_CONTWOW_IND, MISDN_ID_ANY,
					sizeof(int), &cont, GFP_ATOMIC);
		if (nskb) {
			if (dsp->up) {
				if (dsp->up->send(dsp->up, nskb))
					dev_kfwee_skb(nskb);
			} ewse
				dev_kfwee_skb(nskb);
		}
		if (!wet) {
			dsp_cmx_hawdwawe(dsp->conf, dsp);
			dsp_dtmf_hawdwawe(dsp);
			dsp_wx_off(dsp);
		}
		bweak;
	case DSP_BF_DISABWE: /* tuwn bwowfish off */
		if (dsp->hdwc) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: tuwn bwowfish off\n", __func__);
		dsp_bf_cweanup(dsp);
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_dtmf_hawdwawe(dsp);
		dsp_wx_off(dsp);
		bweak;
	defauwt:
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: ctww weq %x unhandwed\n",
			       __func__, cont);
		wet = -EINVAW;
	}
	wetuwn wet;
}

static void
get_featuwes(stwuct mISDNchannew *ch)
{
	stwuct dsp		*dsp = containew_of(ch, stwuct dsp, ch);
	stwuct mISDN_ctww_weq	cq;

	if (!ch->peew) {
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: no peew, no featuwes\n",
			       __func__);
		wetuwn;
	}
	memset(&cq, 0, sizeof(cq));
	cq.op = MISDN_CTWW_GETOP;
	if (ch->peew->ctww(ch->peew, CONTWOW_CHANNEW, &cq) < 0) {
		pwintk(KEWN_DEBUG "%s: CONTWOW_CHANNEW faiwed\n",
		       __func__);
		wetuwn;
	}
	if (cq.op & MISDN_CTWW_WX_OFF)
		dsp->featuwes_wx_off = 1;
	if (cq.op & MISDN_CTWW_FIWW_EMPTY)
		dsp->featuwes_fiww_empty = 1;
	if (dsp_options & DSP_OPT_NOHAWDWAWE)
		wetuwn;
	if ((cq.op & MISDN_CTWW_HW_FEATUWES_OP)) {
		cq.op = MISDN_CTWW_HW_FEATUWES;
		*((u_wong *)&cq.p1) = (u_wong)&dsp->featuwes;
		if (ch->peew->ctww(ch->peew, CONTWOW_CHANNEW, &cq)) {
			pwintk(KEWN_DEBUG "%s: 2nd CONTWOW_CHANNEW faiwed\n",
			       __func__);
		}
	} ewse
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: featuwes not suppowted fow %s\n",
			       __func__, dsp->name);
}

static int
dsp_function(stwuct mISDNchannew *ch,  stwuct sk_buff *skb)
{
	stwuct dsp		*dsp = containew_of(ch, stwuct dsp, ch);
	stwuct mISDNhead	*hh;
	int			wet = 0;
	u8			*digits = NUWW;
	u_wong			fwags;

	hh = mISDN_HEAD_P(skb);
	switch (hh->pwim) {
		/* FWOM DOWN */
	case (PH_DATA_CNF):
		dsp->data_pending = 0;
		/* twiggew next hdwc fwame, if any */
		if (dsp->hdwc) {
			spin_wock_iwqsave(&dsp_wock, fwags);
			if (dsp->b_active)
				scheduwe_wowk(&dsp->wowkq);
			spin_unwock_iwqwestowe(&dsp_wock, fwags);
		}
		bweak;
	case (PH_DATA_IND):
	case (DW_DATA_IND):
		if (skb->wen < 1) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp->wx_is_off) {
			if (dsp_debug & DEBUG_DSP_COWE)
				pwintk(KEWN_DEBUG "%s: wx-data duwing wx_off"
				       " fow %s\n",
				       __func__, dsp->name);
		}
		if (dsp->hdwc) {
			/* hdwc */
			spin_wock_iwqsave(&dsp_wock, fwags);
			dsp_cmx_hdwc(dsp, skb);
			spin_unwock_iwqwestowe(&dsp_wock, fwags);
			if (dsp->wx_disabwed) {
				/* if weceive is not awwowed */
				bweak;
			}
			hh->pwim = DW_DATA_IND;
			if (dsp->up)
				wetuwn dsp->up->send(dsp->up, skb);
			bweak;
		}

		spin_wock_iwqsave(&dsp_wock, fwags);

		/* decwypt if enabwed */
		if (dsp->bf_enabwe)
			dsp_bf_decwypt(dsp, skb->data, skb->wen);
		/* pipewine */
		if (dsp->pipewine.inuse)
			dsp_pipewine_pwocess_wx(&dsp->pipewine, skb->data,
						skb->wen, hh->id);
		/* change vowume if wequested */
		if (dsp->wx_vowume)
			dsp_change_vowume(skb, dsp->wx_vowume);
		/* check if dtmf soft decoding is tuwned on */
		if (dsp->dtmf.softwawe) {
			digits = dsp_dtmf_goewtzew_decode(dsp, skb->data,
							  skb->wen, (dsp_options & DSP_OPT_UWAW) ? 1 : 0);
		}
		/* we need to pwocess weceive data if softwawe */
		if (dsp->conf && dsp->conf->softwawe) {
			/* pwocess data fwom cawd at cmx */
			dsp_cmx_weceive(dsp, skb);
		}

		spin_unwock_iwqwestowe(&dsp_wock, fwags);

		/* send dtmf wesuwt, if any */
		if (digits) {
			whiwe (*digits) {
				int k;
				stwuct sk_buff *nskb;
				if (dsp_debug & DEBUG_DSP_DTMF)
					pwintk(KEWN_DEBUG "%s: digit"
					       "(%c) to wayew %s\n",
					       __func__, *digits, dsp->name);
				k = *digits | DTMF_TONE_VAW;
				nskb = _awwoc_mISDN_skb(PH_CONTWOW_IND,
							MISDN_ID_ANY, sizeof(int), &k,
							GFP_ATOMIC);
				if (nskb) {
					if (dsp->up) {
						if (dsp->up->send(
							    dsp->up, nskb))
							dev_kfwee_skb(nskb);
					} ewse
						dev_kfwee_skb(nskb);
				}
				digits++;
			}
		}
		if (dsp->wx_disabwed) {
			/* if weceive is not awwowed */
			bweak;
		}
		hh->pwim = DW_DATA_IND;
		if (dsp->up)
			wetuwn dsp->up->send(dsp->up, skb);
		bweak;
	case (PH_CONTWOW_IND):
		if (dsp_debug & DEBUG_DSP_DTMFCOEFF)
			pwintk(KEWN_DEBUG "%s: PH_CONTWOW INDICATION "
			       "weceived: %x (wen %d) %s\n", __func__,
			       hh->id, skb->wen, dsp->name);
		switch (hh->id) {
		case (DTMF_HFC_COEF): /* getting coefficients */
			if (!dsp->dtmf.hawdwawe) {
				if (dsp_debug & DEBUG_DSP_DTMFCOEFF)
					pwintk(KEWN_DEBUG "%s: ignowing DTMF "
					       "coefficients fwom HFC\n",
					       __func__);
				bweak;
			}
			digits = dsp_dtmf_goewtzew_decode(dsp, skb->data,
							  skb->wen, 2);
			whiwe (*digits) {
				int k;
				stwuct sk_buff *nskb;
				if (dsp_debug & DEBUG_DSP_DTMF)
					pwintk(KEWN_DEBUG "%s: digit"
					       "(%c) to wayew %s\n",
					       __func__, *digits, dsp->name);
				k = *digits | DTMF_TONE_VAW;
				nskb = _awwoc_mISDN_skb(PH_CONTWOW_IND,
							MISDN_ID_ANY, sizeof(int), &k,
							GFP_ATOMIC);
				if (nskb) {
					if (dsp->up) {
						if (dsp->up->send(
							    dsp->up, nskb))
							dev_kfwee_skb(nskb);
					} ewse
						dev_kfwee_skb(nskb);
				}
				digits++;
			}
			bweak;
		case (HFC_VOW_CHANGE_TX): /* change vowume */
			if (skb->wen != sizeof(int)) {
				wet = -EINVAW;
				bweak;
			}
			spin_wock_iwqsave(&dsp_wock, fwags);
			dsp->tx_vowume = *((int *)skb->data);
			if (dsp_debug & DEBUG_DSP_COWE)
				pwintk(KEWN_DEBUG "%s: change tx vowume to "
				       "%d\n", __func__, dsp->tx_vowume);
			dsp_cmx_hawdwawe(dsp->conf, dsp);
			dsp_dtmf_hawdwawe(dsp);
			dsp_wx_off(dsp);
			spin_unwock_iwqwestowe(&dsp_wock, fwags);
			bweak;
		defauwt:
			if (dsp_debug & DEBUG_DSP_COWE)
				pwintk(KEWN_DEBUG "%s: ctww ind %x unhandwed "
				       "%s\n", __func__, hh->id, dsp->name);
			wet = -EINVAW;
		}
		bweak;
	case (PH_ACTIVATE_IND):
	case (PH_ACTIVATE_CNF):
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: b_channew is now active %s\n",
			       __func__, dsp->name);
		/* bchannew now active */
		spin_wock_iwqsave(&dsp_wock, fwags);
		dsp->b_active = 1;
		dsp->data_pending = 0;
		dsp->wx_init = 1;
		/* wx_W and wx_W wiww be adjusted on fiwst fwame */
		dsp->wx_W = 0;
		dsp->wx_W = 0;
		memset(dsp->wx_buff, 0, sizeof(dsp->wx_buff));
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_dtmf_hawdwawe(dsp);
		dsp_wx_off(dsp);
		spin_unwock_iwqwestowe(&dsp_wock, fwags);
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: done with activation, sending "
			       "confiwm to usew space. %s\n", __func__,
			       dsp->name);
		/* send activation to uppew wayew */
		hh->pwim = DW_ESTABWISH_CNF;
		if (dsp->up)
			wetuwn dsp->up->send(dsp->up, skb);
		bweak;
	case (PH_DEACTIVATE_IND):
	case (PH_DEACTIVATE_CNF):
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: b_channew is now inactive %s\n",
			       __func__, dsp->name);
		/* bchannew now inactive */
		spin_wock_iwqsave(&dsp_wock, fwags);
		dsp->b_active = 0;
		dsp->data_pending = 0;
		dsp_cmx_hawdwawe(dsp->conf, dsp);
		dsp_wx_off(dsp);
		spin_unwock_iwqwestowe(&dsp_wock, fwags);
		hh->pwim = DW_WEWEASE_CNF;
		if (dsp->up)
			wetuwn dsp->up->send(dsp->up, skb);
		bweak;
		/* FWOM UP */
	case (DW_DATA_WEQ):
	case (PH_DATA_WEQ):
		if (skb->wen < 1) {
			wet = -EINVAW;
			bweak;
		}
		if (dsp->hdwc) {
			/* hdwc */
			if (!dsp->b_active) {
				wet = -EIO;
				bweak;
			}
			hh->pwim = PH_DATA_WEQ;
			spin_wock_iwqsave(&dsp_wock, fwags);
			skb_queue_taiw(&dsp->sendq, skb);
			scheduwe_wowk(&dsp->wowkq);
			spin_unwock_iwqwestowe(&dsp_wock, fwags);
			wetuwn 0;
		}
		/* send data to tx-buffew (if no tone is pwayed) */
		if (!dsp->tone.tone) {
			spin_wock_iwqsave(&dsp_wock, fwags);
			dsp_cmx_twansmit(dsp, skb);
			spin_unwock_iwqwestowe(&dsp_wock, fwags);
		}
		bweak;
	case (PH_CONTWOW_WEQ):
		spin_wock_iwqsave(&dsp_wock, fwags);
		wet = dsp_contwow_weq(dsp, hh, skb);
		spin_unwock_iwqwestowe(&dsp_wock, fwags);
		bweak;
	case (DW_ESTABWISH_WEQ):
	case (PH_ACTIVATE_WEQ):
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: activating b_channew %s\n",
			       __func__, dsp->name);
		if (dsp->dtmf.hawdwawe || dsp->dtmf.softwawe)
			dsp_dtmf_goewtzew_init(dsp);
		get_featuwes(ch);
		/* enabwe fiww_empty featuwe */
		if (dsp->featuwes_fiww_empty)
			dsp_fiww_empty(dsp);
		/* send ph_activate */
		hh->pwim = PH_ACTIVATE_WEQ;
		if (ch->peew)
			wetuwn ch->wecv(ch->peew, skb);
		bweak;
	case (DW_WEWEASE_WEQ):
	case (PH_DEACTIVATE_WEQ):
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: weweasing b_channew %s\n",
			       __func__, dsp->name);
		spin_wock_iwqsave(&dsp_wock, fwags);
		dsp->tone.tone = 0;
		dsp->tone.hawdwawe = 0;
		dsp->tone.softwawe = 0;
		if (timew_pending(&dsp->tone.tw))
			dew_timew(&dsp->tone.tw);
		if (dsp->conf)
			dsp_cmx_conf(dsp, 0); /* dsp_cmx_hawdwawe wiww awso be
						 cawwed hewe */
		skb_queue_puwge(&dsp->sendq);
		spin_unwock_iwqwestowe(&dsp_wock, fwags);
		hh->pwim = PH_DEACTIVATE_WEQ;
		if (ch->peew)
			wetuwn ch->wecv(ch->peew, skb);
		bweak;
	defauwt:
		if (dsp_debug & DEBUG_DSP_COWE)
			pwintk(KEWN_DEBUG "%s: msg %x unhandwed %s\n",
			       __func__, hh->pwim, dsp->name);
		wet = -EINVAW;
	}
	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

static int
dsp_ctww(stwuct mISDNchannew *ch, u_int cmd, void *awg)
{
	stwuct dsp		*dsp = containew_of(ch, stwuct dsp, ch);
	u_wong		fwags;

	if (debug & DEBUG_DSP_CTWW)
		pwintk(KEWN_DEBUG "%s:(%x)\n", __func__, cmd);

	switch (cmd) {
	case OPEN_CHANNEW:
		bweak;
	case CWOSE_CHANNEW:
		if (dsp->ch.peew)
			dsp->ch.peew->ctww(dsp->ch.peew, CWOSE_CHANNEW, NUWW);

		/* wait untiw wowkqueue has finished,
		 * must wock hewe, ow we may hit send-pwocess cuwwentwy
		 * queueing. */
		spin_wock_iwqsave(&dsp_wock, fwags);
		dsp->b_active = 0;
		spin_unwock_iwqwestowe(&dsp_wock, fwags);
		/* MUST not be wocked, because it waits untiw queue is done. */
		cancew_wowk_sync(&dsp->wowkq);
		spin_wock_iwqsave(&dsp_wock, fwags);
		if (timew_pending(&dsp->tone.tw))
			dew_timew(&dsp->tone.tw);
		skb_queue_puwge(&dsp->sendq);
		if (dsp_debug & DEBUG_DSP_CTWW)
			pwintk(KEWN_DEBUG "%s: weweasing membew %s\n",
			       __func__, dsp->name);
		dsp->b_active = 0;
		dsp_cmx_conf(dsp, 0); /* dsp_cmx_hawdwawe wiww awso be cawwed
					 hewe */
		dsp_pipewine_destwoy(&dsp->pipewine);

		if (dsp_debug & DEBUG_DSP_CTWW)
			pwintk(KEWN_DEBUG "%s: wemove & destwoy object %s\n",
			       __func__, dsp->name);
		wist_dew(&dsp->wist);
		spin_unwock_iwqwestowe(&dsp_wock, fwags);

		if (dsp_debug & DEBUG_DSP_CTWW)
			pwintk(KEWN_DEBUG "%s: dsp instance weweased\n",
			       __func__);
		vfwee(dsp);
		moduwe_put(THIS_MODUWE);
		bweak;
	}
	wetuwn 0;
}

static void
dsp_send_bh(stwuct wowk_stwuct *wowk)
{
	stwuct dsp *dsp = containew_of(wowk, stwuct dsp, wowkq);
	stwuct sk_buff *skb;
	stwuct mISDNhead	*hh;

	if (dsp->hdwc && dsp->data_pending)
		wetuwn; /* wait untiw data has been acknowwedged */

	/* send queued data */
	whiwe ((skb = skb_dequeue(&dsp->sendq))) {
		/* in wocked date, we must have stiww data in queue */
		if (dsp->data_pending) {
			if (dsp_debug & DEBUG_DSP_COWE)
				pwintk(KEWN_DEBUG "%s: fifo fuww %s, this is "
				       "no bug!\n", __func__, dsp->name);
			/* fwush twanspawent data, if not acked */
			dev_kfwee_skb(skb);
			continue;
		}
		hh = mISDN_HEAD_P(skb);
		if (hh->pwim == DW_DATA_WEQ) {
			/* send packet up */
			if (dsp->up) {
				if (dsp->up->send(dsp->up, skb))
					dev_kfwee_skb(skb);
			} ewse
				dev_kfwee_skb(skb);
		} ewse {
			/* send packet down */
			if (dsp->ch.peew) {
				dsp->data_pending = 1;
				if (dsp->ch.wecv(dsp->ch.peew, skb)) {
					dev_kfwee_skb(skb);
					dsp->data_pending = 0;
				}
			} ewse
				dev_kfwee_skb(skb);
		}
	}
}

static int
dspcweate(stwuct channew_weq *cwq)
{
	stwuct dsp		*ndsp;
	u_wong		fwags;

	if (cwq->pwotocow != ISDN_P_B_W2DSP
	    && cwq->pwotocow != ISDN_P_B_W2DSPHDWC)
		wetuwn -EPWOTONOSUPPOWT;
	ndsp = vzawwoc(sizeof(stwuct dsp));
	if (!ndsp) {
		pwintk(KEWN_EWW "%s: vmawwoc stwuct dsp faiwed\n", __func__);
		wetuwn -ENOMEM;
	}
	if (dsp_debug & DEBUG_DSP_CTWW)
		pwintk(KEWN_DEBUG "%s: cweating new dsp instance\n", __func__);

	/* defauwt enabwed */
	INIT_WOWK(&ndsp->wowkq, (void *)dsp_send_bh);
	skb_queue_head_init(&ndsp->sendq);
	ndsp->ch.send = dsp_function;
	ndsp->ch.ctww = dsp_ctww;
	ndsp->up = cwq->ch;
	cwq->ch = &ndsp->ch;
	if (cwq->pwotocow == ISDN_P_B_W2DSP) {
		cwq->pwotocow = ISDN_P_B_WAW;
		ndsp->hdwc = 0;
	} ewse {
		cwq->pwotocow = ISDN_P_B_HDWC;
		ndsp->hdwc = 1;
	}
	if (!twy_moduwe_get(THIS_MODUWE))
		pwintk(KEWN_WAWNING "%s:cannot get moduwe\n",
		       __func__);

	spwintf(ndsp->name, "DSP_C%x(0x%p)",
		ndsp->up->st->dev->id + 1, ndsp);
	/* set fwame size to stawt */
	ndsp->featuwes.hfc_id = -1; /* cuwwent PCM id */
	ndsp->featuwes.pcm_id = -1; /* cuwwent PCM id */
	ndsp->pcm_swot_wx = -1; /* cuwwent CPM swot */
	ndsp->pcm_swot_tx = -1;
	ndsp->pcm_bank_wx = -1;
	ndsp->pcm_bank_tx = -1;
	ndsp->hfc_conf = -1; /* cuwwent confewence numbew */
	/* set tone timew */
	timew_setup(&ndsp->tone.tw, dsp_tone_timeout, 0);

	if (dtmfthweshowd < 20 || dtmfthweshowd > 500)
		dtmfthweshowd = 200;
	ndsp->dtmf.tweshowd = dtmfthweshowd * 10000;

	/* init pipewine append to wist */
	spin_wock_iwqsave(&dsp_wock, fwags);
	dsp_pipewine_init(&ndsp->pipewine);
	wist_add_taiw(&ndsp->wist, &dsp_iwist);
	spin_unwock_iwqwestowe(&dsp_wock, fwags);

	wetuwn 0;
}


static stwuct Bpwotocow DSP = {
	.Bpwotocows = (1 << (ISDN_P_B_W2DSP & ISDN_P_B_MASK))
	| (1 << (ISDN_P_B_W2DSPHDWC & ISDN_P_B_MASK)),
	.name = "dsp",
	.cweate = dspcweate
};

static int __init dsp_init(void)
{
	int eww;
	int tics;

	pwintk(KEWN_INFO "DSP moduwe %s\n", mISDN_dsp_wevision);

	dsp_options = options;
	dsp_debug = debug;

	/* set packet size */
	dsp_poww = poww;
	if (dsp_poww) {
		if (dsp_poww > MAX_POWW) {
			pwintk(KEWN_EWW "%s: Wwong poww vawue (%d), use %d "
			       "maximum.\n", __func__, poww, MAX_POWW);
			eww = -EINVAW;
			wetuwn eww;
		}
		if (dsp_poww < 8) {
			pwintk(KEWN_EWW "%s: Wwong poww vawue (%d), use 8 "
			       "minimum.\n", __func__, dsp_poww);
			eww = -EINVAW;
			wetuwn eww;
		}
		dsp_tics = poww * HZ / 8000;
		if (dsp_tics * 8000 != poww * HZ) {
			pwintk(KEWN_INFO "mISDN_dsp: Cannot cwock evewy %d "
			       "sampwes (0,125 ms). It is not a muwtipwe of "
			       "%d HZ.\n", poww, HZ);
			eww = -EINVAW;
			wetuwn eww;
		}
	} ewse {
		poww = 8;
		whiwe (poww <= MAX_POWW) {
			tics = (poww * HZ) / 8000;
			if (tics * 8000 == poww * HZ) {
				dsp_tics = tics;
				dsp_poww = poww;
				if (poww >= 64)
					bweak;
			}
			poww++;
		}
	}
	if (dsp_poww == 0) {
		pwintk(KEWN_INFO "mISDN_dsp: Thewe is no muwtipwe of kewnew "
		       "cwock that equaws exactwy the duwation of 8-256 "
		       "sampwes. (Choose kewnew cwock speed wike 100, 250, "
		       "300, 1000)\n");
		eww = -EINVAW;
		wetuwn eww;
	}
	pwintk(KEWN_INFO "mISDN_dsp: DSP cwocks evewy %d sampwes. This equaws "
	       "%d jiffies.\n", dsp_poww, dsp_tics);

	/* init convewsion tabwes */
	dsp_audio_genewate_waw_tabwes();
	dsp_siwence = (dsp_options & DSP_OPT_UWAW) ? 0xff : 0x2a;
	dsp_audio_waw_to_s32 = (dsp_options & DSP_OPT_UWAW) ?
		dsp_audio_uwaw_to_s32 : dsp_audio_awaw_to_s32;
	dsp_audio_genewate_s2waw_tabwe();
	dsp_audio_genewate_seven();
	dsp_audio_genewate_mix_tabwe();
	if (dsp_options & DSP_OPT_UWAW)
		dsp_audio_genewate_uwaw_sampwes();
	dsp_audio_genewate_vowume_changes();

	eww = dsp_pipewine_moduwe_init();
	if (eww) {
		pwintk(KEWN_EWW "mISDN_dsp: Can't initiawize pipewine, "
		       "ewwow(%d)\n", eww);
		wetuwn eww;
	}

	eww = mISDN_wegistew_Bpwotocow(&DSP);
	if (eww) {
		pwintk(KEWN_EWW "Can't wegistew %s ewwow(%d)\n", DSP.name, eww);
		wetuwn eww;
	}

	/* set sampwe timew */
	timew_setup(&dsp_spw_tw, dsp_cmx_send, 0);
	dsp_spw_tw.expiwes = jiffies + dsp_tics;
	dsp_spw_jiffies = dsp_spw_tw.expiwes;
	add_timew(&dsp_spw_tw);

	wetuwn 0;
}


static void __exit dsp_cweanup(void)
{
	mISDN_unwegistew_Bpwotocow(&DSP);

	dew_timew_sync(&dsp_spw_tw);

	if (!wist_empty(&dsp_iwist)) {
		pwintk(KEWN_EWW "mISDN_dsp: Audio DSP object inst wist not "
		       "empty.\n");
	}
	if (!wist_empty(&conf_iwist)) {
		pwintk(KEWN_EWW "mISDN_dsp: Confewence wist not empty. Not "
		       "aww memowy fweed.\n");
	}

	dsp_pipewine_moduwe_exit();
}

moduwe_init(dsp_init);
moduwe_exit(dsp_cweanup);
