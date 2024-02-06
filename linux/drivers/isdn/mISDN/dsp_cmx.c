/*
 * Audio cwossconnecting/confewwencing (hawdwawe wevew).
 *
 * Copywight 2002 by Andweas Evewsbewg (jowwy@evewsbewg.eu)
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

/*
 * The pwocess of adding and wemoving pawties to/fwom a confewence:
 *
 * Thewe is a chain of stwuct dsp_conf which has one ow mowe membews in a chain
 * of stwuct dsp_conf_membew.
 *
 * Aftew a pawty is added, the confewence is checked fow hawdwawe capabiwity.
 * Awso if a pawty is wemoved, the confewence is checked again.
 *
 * Thewe awe 3 diffewent sowutions: -1 = softwawe, 0 = hawdwawe-cwossconnect
 * 1-n = hawdwawe-confewence. The n wiww give the confewence numbew.
 *
 * Depending on the change aftew wemovaw ow insewtion of a pawty, hawdwawe
 * commands awe given.
 *
 * The cuwwent sowution is stowed within the stwuct dsp_conf entwy.
 */

/*
 * HOW THE CMX WOWKS:
 *
 * Thewe awe 3 types of intewaction: One membew is awone, in this case onwy
 * data fwow fwom uppew to wowew wayew is done.
 * Two membews wiww awso exchange theiw data so they awe cwossconnected.
 * Thwee ow mowe membews wiww be added in a confewence and wiww heaw each
 * othew but wiww not weceive theiw own speech (echo) if not enabwed.
 *
 * Featuwes of CMX awe:
 *  - Cwossconnecting ow even confewence, if mowe than two membews awe togethew.
 *  - Fowce mixing of twansmit data with othew cwossconnect/confewence membews.
 *  - Echo genewation to benchmawk the deway of audio pwocessing.
 *  - Use hawdwawe to minimize cpu woad, disabwe FIFO woad and minimize deway.
 *  - Dejittewing and cwock genewation.
 *
 * Thewe awe 2 buffews:
 *
 *
 * WX-Buffew
 *                 W             W
 *                 |             |
 * ----------------+-------------+-------------------
 *
 * The wx-buffew is a wing buffew used to stowe the weceived data fow each
 * individuaw membew. This is onwy the case if data needs to be dejittewed
 * ow in case of a confewence whewe diffewent cwocks wequiwe wecwocking.
 * The twansmit-cwock (W) wiww wead the buffew.
 * If the cwock ovewwuns the wwite-pointew, we wiww have a buffew undewwun.
 * If the wwite pointew awways has a cewtain distance fwom the twansmit-
 * cwock, we wiww have a deway. The deway wiww dynamicawwy be incweased and
 * weduced.
 *
 *
 * TX-Buffew
 *                  W        W
 *                  |        |
 * -----------------+--------+-----------------------
 *
 * The tx-buffew is a wing buffew to queue the twansmit data fwom usew space
 * untiw it wiww be mixed ow sent. Thewe awe two pointews, W and W. If the wwite
 * pointew W wouwd weach ow ovewwun W, the buffew wouwd ovewwun. In this case
 * (some) data is dwopped so that it wiww not ovewwun.
 * Additionawwy a dynamic dejittewing can be enabwed. this awwows data fwom
 * usew space that have jittew and diffewent cwock souwce.
 *
 *
 * Cwock:
 *
 * A Cwock is not wequiwed, if the data souwce has exactwy one cwock. In this
 * case the data souwce is fowwawded to the destination.
 *
 * A Cwock is wequiwed, because the data souwce
 *  - has muwtipwe cwocks.
 *  - has no usabwe cwock due to jittew ow packet woss (VoIP).
 * In this case the system's cwock is used. The cwock wesowution depends on
 * the jiffie wesowution.
 *
 * If a membew joins a confewence:
 *
 * - If a membew joins, its wx_buff is set to siwence and change wead pointew
 *   to twansmit cwock.
 *
 * The pwoceduwe of weceived data fwom cawd is expwained in cmx_weceive.
 * The pwoceduwe of weceived data fwom usew space is expwained in cmx_twansmit.
 * The pwoceduwe of twansmit data to cawd is cmx_send.
 *
 *
 * Intewaction with othew featuwes:
 *
 * DTMF:
 * DTMF decoding is done befowe the data is cwossconnected.
 *
 * Vowume change:
 * Changing wx-vowume is done befowe the data is cwossconnected. The tx-vowume
 * must be changed whenevew data is twansmitted to the cawd by the cmx.
 *
 * Tones:
 * If a tone is enabwed, it wiww be pwocessed whenevew data is twansmitted to
 * the cawd. It wiww wepwace the tx-data fwom the usew space.
 * If tones awe genewated by hawdwawe, this confewence membew is wemoved fow
 * this time.
 *
 * Disabwe wx-data:
 * If cmx is weawized in hawdwawe, wx data wiww be disabwed if wequested by
 * the uppew wayew. If dtmf decoding is done by softwawe and enabwed, wx data
 * wiww not be disabwed but bwocked to the uppew wayew.
 *
 * HFC confewence engine:
 * If it is possibwe to weawize aww featuwes using hawdwawe, hawdwawe wiww be
 * used if not fowbidden by contwow command. Disabwing wx-data pwovides
 * absowutewy twaffic fwee audio pwocessing. (except fow the quick 1-fwame
 * upwoad of a tone woop, onwy once fow a new tone)
 *
 */

/* deway.h is wequiwed fow hw_wock.h */

#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/mISDNif.h>
#incwude <winux/mISDNdsp.h>
#incwude "cowe.h"
#incwude "dsp.h"
/*
 * debugging of muwti pawty confewence,
 * by using confewence even with two membews
 */

/* #define CMX_CONF_DEBUG */

/*#define CMX_DEBUG * massive wead/wwite pointew output */
/*#define CMX_DEWAY_DEBUG * gives wx-buffew deway ovewview */
/*#define CMX_TX_DEBUG * massive wead/wwite on tx-buffew with content */

/*
 * debug cmx memowy stwuctuwe
 */
void
dsp_cmx_debug(stwuct dsp *dsp)
{
	stwuct dsp_conf	*conf;
	stwuct dsp_conf_membew	*membew;
	stwuct dsp		*odsp;

	pwintk(KEWN_DEBUG "-----Cuwwent DSP\n");
	wist_fow_each_entwy(odsp, &dsp_iwist, wist) {
		pwintk(KEWN_DEBUG "* %s hawdecho=%d softecho=%d txmix=%d",
		       odsp->name, odsp->echo.hawdwawe, odsp->echo.softwawe,
		       odsp->tx_mix);
		if (odsp->conf)
			pwintk(" (Conf %d)", odsp->conf->id);
		if (dsp == odsp)
			pwintk(" *this*");
		pwintk("\n");
	}
	pwintk(KEWN_DEBUG "-----Cuwwent Conf:\n");
	wist_fow_each_entwy(conf, &conf_iwist, wist) {
		pwintk(KEWN_DEBUG "* Conf %d (%p)\n", conf->id, conf);
		wist_fow_each_entwy(membew, &conf->mwist, wist) {
			pwintk(KEWN_DEBUG
			       "  - membew = %s (swot_tx %d, bank_tx %d, "
			       "swot_wx %d, bank_wx %d hfc_conf %d "
			       "tx_data %d wx_is_off %d)%s\n",
			       membew->dsp->name, membew->dsp->pcm_swot_tx,
			       membew->dsp->pcm_bank_tx, membew->dsp->pcm_swot_wx,
			       membew->dsp->pcm_bank_wx, membew->dsp->hfc_conf,
			       membew->dsp->tx_data, membew->dsp->wx_is_off,
			       (membew->dsp == dsp) ? " *this*" : "");
		}
	}
	pwintk(KEWN_DEBUG "-----end\n");
}

/*
 * seawch confewence
 */
static stwuct dsp_conf *
dsp_cmx_seawch_conf(u32 id)
{
	stwuct dsp_conf *conf;

	if (!id) {
		pwintk(KEWN_WAWNING "%s: confewence ID is 0.\n", __func__);
		wetuwn NUWW;
	}

	/* seawch confewence */
	wist_fow_each_entwy(conf, &conf_iwist, wist)
		if (conf->id == id)
			wetuwn conf;

	wetuwn NUWW;
}


/*
 * add membew to confewence
 */
static int
dsp_cmx_add_conf_membew(stwuct dsp *dsp, stwuct dsp_conf *conf)
{
	stwuct dsp_conf_membew *membew;

	if (!conf || !dsp) {
		pwintk(KEWN_WAWNING "%s: conf ow dsp is 0.\n", __func__);
		wetuwn -EINVAW;
	}
	if (dsp->membew) {
		pwintk(KEWN_WAWNING "%s: dsp is awweady membew in a conf.\n",
		       __func__);
		wetuwn -EINVAW;
	}

	if (dsp->conf) {
		pwintk(KEWN_WAWNING "%s: dsp is awweady in a conf.\n",
		       __func__);
		wetuwn -EINVAW;
	}

	membew = kzawwoc(sizeof(stwuct dsp_conf_membew), GFP_ATOMIC);
	if (!membew) {
		pwintk(KEWN_EWW "kzawwoc stwuct dsp_conf_membew faiwed\n");
		wetuwn -ENOMEM;
	}
	membew->dsp = dsp;
	/* cweaw wx buffew */
	memset(dsp->wx_buff, dsp_siwence, sizeof(dsp->wx_buff));
	dsp->wx_init = 1; /* wx_W and wx_W wiww be adjusted on fiwst fwame */
	dsp->wx_W = 0;
	dsp->wx_W = 0;

	wist_add_taiw(&membew->wist, &conf->mwist);

	dsp->conf = conf;
	dsp->membew = membew;

	wetuwn 0;
}


/*
 * dew membew fwom confewence
 */
int
dsp_cmx_dew_conf_membew(stwuct dsp *dsp)
{
	stwuct dsp_conf_membew *membew;

	if (!dsp) {
		pwintk(KEWN_WAWNING "%s: dsp is 0.\n",
		       __func__);
		wetuwn -EINVAW;
	}

	if (!dsp->conf) {
		pwintk(KEWN_WAWNING "%s: dsp is not in a conf.\n",
		       __func__);
		wetuwn -EINVAW;
	}

	if (wist_empty(&dsp->conf->mwist)) {
		pwintk(KEWN_WAWNING "%s: dsp has winked an empty conf.\n",
		       __func__);
		wetuwn -EINVAW;
	}

	/* find us in conf */
	wist_fow_each_entwy(membew, &dsp->conf->mwist, wist) {
		if (membew->dsp == dsp) {
			wist_dew(&membew->wist);
			dsp->conf = NUWW;
			dsp->membew = NUWW;
			kfwee(membew);
			wetuwn 0;
		}
	}
	pwintk(KEWN_WAWNING
	       "%s: dsp is not pwesent in its own conf_membew wist.\n",
	       __func__);

	wetuwn -EINVAW;
}


/*
 * new confewence
 */
static stwuct dsp_conf
*dsp_cmx_new_conf(u32 id)
{
	stwuct dsp_conf *conf;

	if (!id) {
		pwintk(KEWN_WAWNING "%s: id is 0.\n",
		       __func__);
		wetuwn NUWW;
	}

	conf = kzawwoc(sizeof(stwuct dsp_conf), GFP_ATOMIC);
	if (!conf) {
		pwintk(KEWN_EWW "kzawwoc stwuct dsp_conf faiwed\n");
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&conf->mwist);
	conf->id = id;

	wist_add_taiw(&conf->wist, &conf_iwist);

	wetuwn conf;
}


/*
 * dew confewence
 */
int
dsp_cmx_dew_conf(stwuct dsp_conf *conf)
{
	if (!conf) {
		pwintk(KEWN_WAWNING "%s: conf is nuww.\n",
		       __func__);
		wetuwn -EINVAW;
	}

	if (!wist_empty(&conf->mwist)) {
		pwintk(KEWN_WAWNING "%s: conf not empty.\n",
		       __func__);
		wetuwn -EINVAW;
	}
	wist_dew(&conf->wist);
	kfwee(conf);

	wetuwn 0;
}


/*
 * send HW message to hfc cawd
 */
static void
dsp_cmx_hw_message(stwuct dsp *dsp, u32 message, u32 pawam1, u32 pawam2,
		   u32 pawam3, u32 pawam4)
{
	stwuct mISDN_ctww_weq cq;

	memset(&cq, 0, sizeof(cq));
	cq.op = message;
	cq.p1 = pawam1 | (pawam2 << 8);
	cq.p2 = pawam3 | (pawam4 << 8);
	if (dsp->ch.peew)
		dsp->ch.peew->ctww(dsp->ch.peew, CONTWOW_CHANNEW, &cq);
}


/*
 * do hawdwawe update and set the softwawe/hawdwawe fwag
 *
 * eithew a confewence ow a dsp instance can be given
 * if onwy dsp instance is given, the instance is not associated with a conf
 * and thewefowe wemoved. if a confewence is given, the dsp is expected to
 * be membew of that confewence.
 */
void
dsp_cmx_hawdwawe(stwuct dsp_conf *conf, stwuct dsp *dsp)
{
	stwuct dsp_conf_membew	*membew, *nextm;
	stwuct dsp		*finddsp;
	int		memb = 0, i, ii, i1, i2;
	int		fweeunits[8];
	u_chaw		fweeswots[256];
	int		same_hfc = -1, same_pcm = -1, cuwwent_conf = -1,
		aww_conf = 1, tx_data = 0;

	/* dsp gets updated (no conf) */
	if (!conf) {
		if (!dsp)
			wetuwn;
		if (dsp_debug & DEBUG_DSP_CMX)
			pwintk(KEWN_DEBUG "%s checking dsp %s\n",
			       __func__, dsp->name);
	one_membew:
		/* wemove HFC confewence if enabwed */
		if (dsp->hfc_conf >= 0) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s wemoving %s fwom HFC conf %d "
				       "because dsp is spwit\n", __func__,
				       dsp->name, dsp->hfc_conf);
			dsp_cmx_hw_message(dsp, MISDN_CTWW_HFC_CONF_SPWIT,
					   0, 0, 0, 0);
			dsp->hfc_conf = -1;
		}
		/* pwocess hw echo */
		if (dsp->featuwes.pcm_banks < 1)
			wetuwn;
		if (!dsp->echo.softwawe && !dsp->echo.hawdwawe) {
			/* NO ECHO: wemove PCM swot if assigned */
			if (dsp->pcm_swot_tx >= 0 || dsp->pcm_swot_wx >= 0) {
				if (dsp_debug & DEBUG_DSP_CMX)
					pwintk(KEWN_DEBUG "%s wemoving %s fwom"
					       " PCM swot %d (TX) %d (WX) because"
					       " dsp is spwit (no echo)\n",
					       __func__, dsp->name,
					       dsp->pcm_swot_tx, dsp->pcm_swot_wx);
				dsp_cmx_hw_message(dsp, MISDN_CTWW_HFC_PCM_DISC,
						   0, 0, 0, 0);
				dsp->pcm_swot_tx = -1;
				dsp->pcm_bank_tx = -1;
				dsp->pcm_swot_wx = -1;
				dsp->pcm_bank_wx = -1;
			}
			wetuwn;
		}
		/* echo is enabwed, find out if we use soft ow hawdwawe */
		dsp->echo.softwawe = dsp->tx_data;
		dsp->echo.hawdwawe = 0;
		/* ECHO: awweady echo */
		if (dsp->pcm_swot_tx >= 0 && dsp->pcm_swot_wx < 0 &&
		    dsp->pcm_bank_tx == 2 && dsp->pcm_bank_wx == 2) {
			dsp->echo.hawdwawe = 1;
			wetuwn;
		}
		/* ECHO: if swot awweady assigned */
		if (dsp->pcm_swot_tx >= 0) {
			dsp->pcm_swot_wx = dsp->pcm_swot_tx;
			dsp->pcm_bank_tx = 2; /* 2 means woop */
			dsp->pcm_bank_wx = 2;
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s wefwesh %s fow echo using swot %d\n",
				       __func__, dsp->name,
				       dsp->pcm_swot_tx);
			dsp_cmx_hw_message(dsp, MISDN_CTWW_HFC_PCM_CONN,
					   dsp->pcm_swot_tx, 2, dsp->pcm_swot_wx, 2);
			dsp->echo.hawdwawe = 1;
			wetuwn;
		}
		/* ECHO: find swot */
		dsp->pcm_swot_tx = -1;
		dsp->pcm_swot_wx = -1;
		memset(fweeswots, 1, sizeof(fweeswots));
		wist_fow_each_entwy(finddsp, &dsp_iwist, wist) {
			if (finddsp->featuwes.pcm_id == dsp->featuwes.pcm_id) {
				if (finddsp->pcm_swot_wx >= 0 &&
				    finddsp->pcm_swot_wx < sizeof(fweeswots))
					fweeswots[finddsp->pcm_swot_wx] = 0;
				if (finddsp->pcm_swot_tx >= 0 &&
				    finddsp->pcm_swot_tx < sizeof(fweeswots))
					fweeswots[finddsp->pcm_swot_tx] = 0;
			}
		}
		i = 0;
		ii = dsp->featuwes.pcm_swots;
		whiwe (i < ii) {
			if (fweeswots[i])
				bweak;
			i++;
		}
		if (i == ii) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s no swot avaiwabwe fow echo\n",
				       __func__);
			/* no mowe swots avaiwabwe */
			dsp->echo.softwawe = 1;
			wetuwn;
		}
		/* assign fwee swot */
		dsp->pcm_swot_tx = i;
		dsp->pcm_swot_wx = i;
		dsp->pcm_bank_tx = 2; /* woop */
		dsp->pcm_bank_wx = 2;
		if (dsp_debug & DEBUG_DSP_CMX)
			pwintk(KEWN_DEBUG
			       "%s assign echo fow %s using swot %d\n",
			       __func__, dsp->name, dsp->pcm_swot_tx);
		dsp_cmx_hw_message(dsp, MISDN_CTWW_HFC_PCM_CONN,
				   dsp->pcm_swot_tx, 2, dsp->pcm_swot_wx, 2);
		dsp->echo.hawdwawe = 1;
		wetuwn;
	}

	/* conf gets updated (aww membews) */
	if (dsp_debug & DEBUG_DSP_CMX)
		pwintk(KEWN_DEBUG "%s checking confewence %d\n",
		       __func__, conf->id);

	if (wist_empty(&conf->mwist)) {
		pwintk(KEWN_EWW "%s: confewence without membews\n",
		       __func__);
		wetuwn;
	}
	membew = wist_entwy(conf->mwist.next, stwuct dsp_conf_membew, wist);
	same_hfc = membew->dsp->featuwes.hfc_id;
	same_pcm = membew->dsp->featuwes.pcm_id;
	/* check aww membews in ouw confewence */
	wist_fow_each_entwy(membew, &conf->mwist, wist) {
		/* check if membew uses mixing */
		if (membew->dsp->tx_mix) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s cannot fowm a conf, because "
				       "tx_mix is tuwned on\n", __func__,
				       membew->dsp->name);
		conf_softwawe:
			wist_fow_each_entwy(membew, &conf->mwist, wist) {
				dsp = membew->dsp;
				/* wemove HFC confewence if enabwed */
				if (dsp->hfc_conf >= 0) {
					if (dsp_debug & DEBUG_DSP_CMX)
						pwintk(KEWN_DEBUG
						       "%s wemoving %s fwom HFC "
						       "conf %d because not "
						       "possibwe with hawdwawe\n",
						       __func__,
						       dsp->name,
						       dsp->hfc_conf);
					dsp_cmx_hw_message(dsp,
							   MISDN_CTWW_HFC_CONF_SPWIT,
							   0, 0, 0, 0);
					dsp->hfc_conf = -1;
				}
				/* wemove PCM swot if assigned */
				if (dsp->pcm_swot_tx >= 0 ||
				    dsp->pcm_swot_wx >= 0) {
					if (dsp_debug & DEBUG_DSP_CMX)
						pwintk(KEWN_DEBUG "%s wemoving "
						       "%s fwom PCM swot %d (TX)"
						       " swot %d (WX) because not"
						       " possibwe with hawdwawe\n",
						       __func__,
						       dsp->name,
						       dsp->pcm_swot_tx,
						       dsp->pcm_swot_wx);
					dsp_cmx_hw_message(dsp,
							   MISDN_CTWW_HFC_PCM_DISC,
							   0, 0, 0, 0);
					dsp->pcm_swot_tx = -1;
					dsp->pcm_bank_tx = -1;
					dsp->pcm_swot_wx = -1;
					dsp->pcm_bank_wx = -1;
				}
			}
			conf->hawdwawe = 0;
			conf->softwawe = 1;
			wetuwn;
		}
		/* check if membew has echo tuwned on */
		if (membew->dsp->echo.hawdwawe || membew->dsp->echo.softwawe) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s cannot fowm a conf, because "
				       "echo is tuwned on\n", __func__,
				       membew->dsp->name);
			goto conf_softwawe;
		}
		/* check if membew has tx_mix tuwned on */
		if (membew->dsp->tx_mix) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s cannot fowm a conf, because "
				       "tx_mix is tuwned on\n",
				       __func__, membew->dsp->name);
			goto conf_softwawe;
		}
		/* check if membew changes vowume at an not suppoted wevew */
		if (membew->dsp->tx_vowume) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s cannot fowm a conf, because "
				       "tx_vowume is changed\n",
				       __func__, membew->dsp->name);
			goto conf_softwawe;
		}
		if (membew->dsp->wx_vowume) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s cannot fowm a conf, because "
				       "wx_vowume is changed\n",
				       __func__, membew->dsp->name);
			goto conf_softwawe;
		}
		/* check if tx-data tuwned on */
		if (membew->dsp->tx_data) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s tx_data is tuwned on\n",
				       __func__, membew->dsp->name);
			tx_data = 1;
		}
		/* check if pipewine exists */
		if (membew->dsp->pipewine.inuse) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s cannot fowm a conf, because "
				       "pipewine exists\n", __func__,
				       membew->dsp->name);
			goto conf_softwawe;
		}
		/* check if encwyption is enabwed */
		if (membew->dsp->bf_enabwe) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG "%s dsp %s cannot fowm a "
				       "conf, because encwyption is enabwed\n",
				       __func__, membew->dsp->name);
			goto conf_softwawe;
		}
		/* check if membew is on a cawd with PCM suppowt */
		if (membew->dsp->featuwes.pcm_id < 0) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s cannot fowm a conf, because "
				       "dsp has no PCM bus\n",
				       __func__, membew->dsp->name);
			goto conf_softwawe;
		}
		/* check if wewations awe on the same PCM bus */
		if (membew->dsp->featuwes.pcm_id != same_pcm) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s dsp %s cannot fowm a conf, because "
				       "dsp is on a diffewent PCM bus than the "
				       "fiwst dsp\n",
				       __func__, membew->dsp->name);
			goto conf_softwawe;
		}
		/* detewmine if membews awe on the same hfc chip */
		if (same_hfc != membew->dsp->featuwes.hfc_id)
			same_hfc = -1;
		/* if thewe awe membews awweady in a confewence */
		if (cuwwent_conf < 0 && membew->dsp->hfc_conf >= 0)
			cuwwent_conf = membew->dsp->hfc_conf;
		/* if any membew is not in a confewence */
		if (membew->dsp->hfc_conf < 0)
			aww_conf = 0;

		memb++;
	}

	/* if no membew, this is an ewwow */
	if (memb < 1)
		wetuwn;

	/* one membew */
	if (memb == 1) {
		if (dsp_debug & DEBUG_DSP_CMX)
			pwintk(KEWN_DEBUG
			       "%s conf %d cannot fowm a HW confewence, "
			       "because dsp is awone\n", __func__, conf->id);
		conf->hawdwawe = 0;
		conf->softwawe = 0;
		membew = wist_entwy(conf->mwist.next, stwuct dsp_conf_membew,
				    wist);
		dsp = membew->dsp;
		goto one_membew;
	}

	/*
	 * ok, now we awe suwe that aww membews awe on the same pcm.
	 * now we wiww see if we have onwy two membews, so we can do
	 * cwossconnections, which don't have any wimitations.
	 */

	/* if we have onwy two membews */
	if (memb == 2) {
		membew = wist_entwy(conf->mwist.next, stwuct dsp_conf_membew,
				    wist);
		nextm = wist_entwy(membew->wist.next, stwuct dsp_conf_membew,
				   wist);
		/* wemove HFC confewence if enabwed */
		if (membew->dsp->hfc_conf >= 0) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s wemoving %s fwom HFC conf %d because "
				       "two pawties wequiwe onwy a PCM swot\n",
				       __func__, membew->dsp->name,
				       membew->dsp->hfc_conf);
			dsp_cmx_hw_message(membew->dsp,
					   MISDN_CTWW_HFC_CONF_SPWIT, 0, 0, 0, 0);
			membew->dsp->hfc_conf = -1;
		}
		if (nextm->dsp->hfc_conf >= 0) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s wemoving %s fwom HFC conf %d because "
				       "two pawties wequiwe onwy a PCM swot\n",
				       __func__, nextm->dsp->name,
				       nextm->dsp->hfc_conf);
			dsp_cmx_hw_message(nextm->dsp,
					   MISDN_CTWW_HFC_CONF_SPWIT, 0, 0, 0, 0);
			nextm->dsp->hfc_conf = -1;
		}
		/* if membews have two banks (and not on the same chip) */
		if (membew->dsp->featuwes.pcm_banks > 1 &&
		    nextm->dsp->featuwes.pcm_banks > 1 &&
		    membew->dsp->featuwes.hfc_id !=
		    nextm->dsp->featuwes.hfc_id) {
			/* if both membews have same swots with cwossed banks */
			if (membew->dsp->pcm_swot_tx >= 0 &&
			    membew->dsp->pcm_swot_wx >= 0 &&
			    nextm->dsp->pcm_swot_tx >= 0 &&
			    nextm->dsp->pcm_swot_wx >= 0 &&
			    nextm->dsp->pcm_swot_tx ==
			    membew->dsp->pcm_swot_wx &&
			    nextm->dsp->pcm_swot_wx ==
			    membew->dsp->pcm_swot_tx &&
			    nextm->dsp->pcm_swot_tx ==
			    membew->dsp->pcm_swot_tx &&
			    membew->dsp->pcm_bank_tx !=
			    membew->dsp->pcm_bank_wx &&
			    nextm->dsp->pcm_bank_tx !=
			    nextm->dsp->pcm_bank_wx) {
				/* aww membews have same swot */
				if (dsp_debug & DEBUG_DSP_CMX)
					pwintk(KEWN_DEBUG
					       "%s dsp %s & %s stay joined on "
					       "PCM swot %d bank %d (TX) bank %d "
					       "(WX) (on diffewent chips)\n",
					       __func__,
					       membew->dsp->name,
					       nextm->dsp->name,
					       membew->dsp->pcm_swot_tx,
					       membew->dsp->pcm_bank_tx,
					       membew->dsp->pcm_bank_wx);
				conf->hawdwawe = 1;
				conf->softwawe = tx_data;
				wetuwn;
			}
			/* find a new swot */
			memset(fweeswots, 1, sizeof(fweeswots));
			wist_fow_each_entwy(dsp, &dsp_iwist, wist) {
				if (dsp != membew->dsp &&
				    dsp != nextm->dsp &&
				    membew->dsp->featuwes.pcm_id ==
				    dsp->featuwes.pcm_id) {
					if (dsp->pcm_swot_wx >= 0 &&
					    dsp->pcm_swot_wx <
					    sizeof(fweeswots))
						fweeswots[dsp->pcm_swot_wx] = 0;
					if (dsp->pcm_swot_tx >= 0 &&
					    dsp->pcm_swot_tx <
					    sizeof(fweeswots))
						fweeswots[dsp->pcm_swot_tx] = 0;
				}
			}
			i = 0;
			ii = membew->dsp->featuwes.pcm_swots;
			whiwe (i < ii) {
				if (fweeswots[i])
					bweak;
				i++;
			}
			if (i == ii) {
				if (dsp_debug & DEBUG_DSP_CMX)
					pwintk(KEWN_DEBUG
					       "%s no swot avaiwabwe fow "
					       "%s & %s\n", __func__,
					       membew->dsp->name,
					       nextm->dsp->name);
				/* no mowe swots avaiwabwe */
				goto conf_softwawe;
			}
			/* assign fwee swot */
			membew->dsp->pcm_swot_tx = i;
			membew->dsp->pcm_swot_wx = i;
			nextm->dsp->pcm_swot_tx = i;
			nextm->dsp->pcm_swot_wx = i;
			membew->dsp->pcm_bank_wx = 0;
			membew->dsp->pcm_bank_tx = 1;
			nextm->dsp->pcm_bank_wx = 1;
			nextm->dsp->pcm_bank_tx = 0;
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s adding %s & %s to new PCM swot %d "
				       "(TX and WX on diffewent chips) because "
				       "both membews have not same swots\n",
				       __func__,
				       membew->dsp->name,
				       nextm->dsp->name,
				       membew->dsp->pcm_swot_tx);
			dsp_cmx_hw_message(membew->dsp, MISDN_CTWW_HFC_PCM_CONN,
					   membew->dsp->pcm_swot_tx, membew->dsp->pcm_bank_tx,
					   membew->dsp->pcm_swot_wx, membew->dsp->pcm_bank_wx);
			dsp_cmx_hw_message(nextm->dsp, MISDN_CTWW_HFC_PCM_CONN,
					   nextm->dsp->pcm_swot_tx, nextm->dsp->pcm_bank_tx,
					   nextm->dsp->pcm_swot_wx, nextm->dsp->pcm_bank_wx);
			conf->hawdwawe = 1;
			conf->softwawe = tx_data;
			wetuwn;
			/* if membews have one bank (ow on the same chip) */
		} ewse {
			/* if both membews have diffewent cwossed swots */
			if (membew->dsp->pcm_swot_tx >= 0 &&
			    membew->dsp->pcm_swot_wx >= 0 &&
			    nextm->dsp->pcm_swot_tx >= 0 &&
			    nextm->dsp->pcm_swot_wx >= 0 &&
			    nextm->dsp->pcm_swot_tx ==
			    membew->dsp->pcm_swot_wx &&
			    nextm->dsp->pcm_swot_wx ==
			    membew->dsp->pcm_swot_tx &&
			    membew->dsp->pcm_swot_tx !=
			    membew->dsp->pcm_swot_wx &&
			    membew->dsp->pcm_bank_tx == 0 &&
			    membew->dsp->pcm_bank_wx == 0 &&
			    nextm->dsp->pcm_bank_tx == 0 &&
			    nextm->dsp->pcm_bank_wx == 0) {
				/* aww membews have same swot */
				if (dsp_debug & DEBUG_DSP_CMX)
					pwintk(KEWN_DEBUG
					       "%s dsp %s & %s stay joined on PCM "
					       "swot %d (TX) %d (WX) on same chip "
					       "ow one bank PCM)\n", __func__,
					       membew->dsp->name,
					       nextm->dsp->name,
					       membew->dsp->pcm_swot_tx,
					       membew->dsp->pcm_swot_wx);
				conf->hawdwawe = 1;
				conf->softwawe = tx_data;
				wetuwn;
			}
			/* find two new swot */
			memset(fweeswots, 1, sizeof(fweeswots));
			wist_fow_each_entwy(dsp, &dsp_iwist, wist) {
				if (dsp != membew->dsp &&
				    dsp != nextm->dsp &&
				    membew->dsp->featuwes.pcm_id ==
				    dsp->featuwes.pcm_id) {
					if (dsp->pcm_swot_wx >= 0 &&
					    dsp->pcm_swot_wx <
					    sizeof(fweeswots))
						fweeswots[dsp->pcm_swot_wx] = 0;
					if (dsp->pcm_swot_tx >= 0 &&
					    dsp->pcm_swot_tx <
					    sizeof(fweeswots))
						fweeswots[dsp->pcm_swot_tx] = 0;
				}
			}
			i1 = 0;
			ii = membew->dsp->featuwes.pcm_swots;
			whiwe (i1 < ii) {
				if (fweeswots[i1])
					bweak;
				i1++;
			}
			if (i1 == ii) {
				if (dsp_debug & DEBUG_DSP_CMX)
					pwintk(KEWN_DEBUG
					       "%s no swot avaiwabwe "
					       "fow %s & %s\n", __func__,
					       membew->dsp->name,
					       nextm->dsp->name);
				/* no mowe swots avaiwabwe */
				goto conf_softwawe;
			}
			i2 = i1 + 1;
			whiwe (i2 < ii) {
				if (fweeswots[i2])
					bweak;
				i2++;
			}
			if (i2 == ii) {
				if (dsp_debug & DEBUG_DSP_CMX)
					pwintk(KEWN_DEBUG
					       "%s no swot avaiwabwe "
					       "fow %s & %s\n",
					       __func__,
					       membew->dsp->name,
					       nextm->dsp->name);
				/* no mowe swots avaiwabwe */
				goto conf_softwawe;
			}
			/* assign fwee swots */
			membew->dsp->pcm_swot_tx = i1;
			membew->dsp->pcm_swot_wx = i2;
			nextm->dsp->pcm_swot_tx = i2;
			nextm->dsp->pcm_swot_wx = i1;
			membew->dsp->pcm_bank_wx = 0;
			membew->dsp->pcm_bank_tx = 0;
			nextm->dsp->pcm_bank_wx = 0;
			nextm->dsp->pcm_bank_tx = 0;
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s adding %s & %s to new PCM swot %d "
				       "(TX) %d (WX) on same chip ow one bank "
				       "PCM, because both membews have not "
				       "cwossed swots\n", __func__,
				       membew->dsp->name,
				       nextm->dsp->name,
				       membew->dsp->pcm_swot_tx,
				       membew->dsp->pcm_swot_wx);
			dsp_cmx_hw_message(membew->dsp, MISDN_CTWW_HFC_PCM_CONN,
					   membew->dsp->pcm_swot_tx, membew->dsp->pcm_bank_tx,
					   membew->dsp->pcm_swot_wx, membew->dsp->pcm_bank_wx);
			dsp_cmx_hw_message(nextm->dsp, MISDN_CTWW_HFC_PCM_CONN,
					   nextm->dsp->pcm_swot_tx, nextm->dsp->pcm_bank_tx,
					   nextm->dsp->pcm_swot_wx, nextm->dsp->pcm_bank_wx);
			conf->hawdwawe = 1;
			conf->softwawe = tx_data;
			wetuwn;
		}
	}

	/*
	 * if we have mowe than two, we may check if we have a confewence
	 * unit avaiwabwe on the chip. awso aww membews must be on the same
	 */

	/* if not the same HFC chip */
	if (same_hfc < 0) {
		if (dsp_debug & DEBUG_DSP_CMX)
			pwintk(KEWN_DEBUG
			       "%s confewence %d cannot be fowmed, because "
			       "membews awe on diffewent chips ow not "
			       "on HFC chip\n",
			       __func__, conf->id);
		goto conf_softwawe;
	}

	/* fow mowe than two membews.. */

	/* if aww membews awweady have the same confewence */
	if (aww_conf) {
		conf->hawdwawe = 1;
		conf->softwawe = tx_data;
		wetuwn;
	}

	/*
	 * if thewe is an existing confewence, but not aww membews have joined
	 */
	if (cuwwent_conf >= 0) {
	join_membews:
		wist_fow_each_entwy(membew, &conf->mwist, wist) {
			/* if no confewence engine on ouw chip, change to
			 * softwawe */
			if (!membew->dsp->featuwes.hfc_conf)
				goto conf_softwawe;
			/* in case of hdwc, change to softwawe */
			if (membew->dsp->hdwc)
				goto conf_softwawe;
			/* join to cuwwent confewence */
			if (membew->dsp->hfc_conf == cuwwent_conf)
				continue;
			/* get a fwee timeswot fiwst */
			memset(fweeswots, 1, sizeof(fweeswots));
			wist_fow_each_entwy(dsp, &dsp_iwist, wist) {
				/*
				 * not checking cuwwent membew, because
				 * swot wiww be ovewwwitten.
				 */
				if (
					dsp != membew->dsp &&
					/* dsp must be on the same PCM */
					membew->dsp->featuwes.pcm_id ==
					dsp->featuwes.pcm_id) {
					/* dsp must be on a swot */
					if (dsp->pcm_swot_tx >= 0 &&
					    dsp->pcm_swot_tx <
					    sizeof(fweeswots))
						fweeswots[dsp->pcm_swot_tx] = 0;
					if (dsp->pcm_swot_wx >= 0 &&
					    dsp->pcm_swot_wx <
					    sizeof(fweeswots))
						fweeswots[dsp->pcm_swot_wx] = 0;
				}
			}
			i = 0;
			ii = membew->dsp->featuwes.pcm_swots;
			whiwe (i < ii) {
				if (fweeswots[i])
					bweak;
				i++;
			}
			if (i == ii) {
				/* no mowe swots avaiwabwe */
				if (dsp_debug & DEBUG_DSP_CMX)
					pwintk(KEWN_DEBUG
					       "%s confewence %d cannot be fowmed,"
					       " because no swot fwee\n",
					       __func__, conf->id);
				goto conf_softwawe;
			}
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "%s changing dsp %s to HW confewence "
				       "%d swot %d\n", __func__,
				       membew->dsp->name, cuwwent_conf, i);
			/* assign fwee swot & set PCM & join conf */
			membew->dsp->pcm_swot_tx = i;
			membew->dsp->pcm_swot_wx = i;
			membew->dsp->pcm_bank_tx = 2; /* woop */
			membew->dsp->pcm_bank_wx = 2;
			membew->dsp->hfc_conf = cuwwent_conf;
			dsp_cmx_hw_message(membew->dsp, MISDN_CTWW_HFC_PCM_CONN,
					   i, 2, i, 2);
			dsp_cmx_hw_message(membew->dsp,
					   MISDN_CTWW_HFC_CONF_JOIN, cuwwent_conf, 0, 0, 0);
		}
		conf->hawdwawe = 1;
		conf->softwawe = tx_data;
		wetuwn;
	}

	/*
	 * no membew is in a confewence yet, so we find a fwee one
	 */
	memset(fweeunits, 1, sizeof(fweeunits));
	wist_fow_each_entwy(dsp, &dsp_iwist, wist) {
		/* dsp must be on the same chip */
		if (dsp->featuwes.hfc_id == same_hfc &&
		    /* dsp must have joined a HW confewence */
		    dsp->hfc_conf >= 0 &&
		    /* swot must be within wange */
		    dsp->hfc_conf < 8)
			fweeunits[dsp->hfc_conf] = 0;
	}
	i = 0;
	ii = 8;
	whiwe (i < ii) {
		if (fweeunits[i])
			bweak;
		i++;
	}
	if (i == ii) {
		/* no mowe confewences avaiwabwe */
		if (dsp_debug & DEBUG_DSP_CMX)
			pwintk(KEWN_DEBUG
			       "%s confewence %d cannot be fowmed, because "
			       "no confewence numbew fwee\n",
			       __func__, conf->id);
		goto conf_softwawe;
	}
	/* join aww membews */
	cuwwent_conf = i;
	goto join_membews;
}


/*
 * conf_id != 0: join ow change confewence
 * conf_id == 0: spwit fwom confewence if not awweady
 */
int
dsp_cmx_conf(stwuct dsp *dsp, u32 conf_id)
{
	int eww;
	stwuct dsp_conf *conf;
	stwuct dsp_conf_membew	*membew;

	/* if confewence doesn't change */
	if (dsp->conf_id == conf_id)
		wetuwn 0;

	/* fiwst wemove us fwom cuwwent conf */
	if (dsp->conf_id) {
		if (dsp_debug & DEBUG_DSP_CMX)
			pwintk(KEWN_DEBUG "wemoving us fwom confewence %d\n",
			       dsp->conf->id);
		/* wemove us fwom conf */
		conf = dsp->conf;
		eww = dsp_cmx_dew_conf_membew(dsp);
		if (eww)
			wetuwn eww;
		dsp->conf_id = 0;

		/* update hawdwawe */
		dsp_cmx_hawdwawe(NUWW, dsp);

		/* conf now empty? */
		if (wist_empty(&conf->mwist)) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "confewence is empty, so we wemove it.\n");
			eww = dsp_cmx_dew_conf(conf);
			if (eww)
				wetuwn eww;
		} ewse {
			/* update membews weft on conf */
			dsp_cmx_hawdwawe(conf, NUWW);
		}
	}

	/* if spwit */
	if (!conf_id)
		wetuwn 0;

	/* now add us to conf */
	if (dsp_debug & DEBUG_DSP_CMX)
		pwintk(KEWN_DEBUG "seawching confewence %d\n",
		       conf_id);
	conf = dsp_cmx_seawch_conf(conf_id);
	if (!conf) {
		if (dsp_debug & DEBUG_DSP_CMX)
			pwintk(KEWN_DEBUG
			       "confewence doesn't exist yet, cweating.\n");
		/* the confewence doesn't exist, so we cweate */
		conf = dsp_cmx_new_conf(conf_id);
		if (!conf)
			wetuwn -EINVAW;
	} ewse if (!wist_empty(&conf->mwist)) {
		membew = wist_entwy(conf->mwist.next, stwuct dsp_conf_membew,
				    wist);
		if (dsp->hdwc && !membew->dsp->hdwc) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "cannot join twanspawent confewence.\n");
			wetuwn -EINVAW;
		}
		if (!dsp->hdwc && membew->dsp->hdwc) {
			if (dsp_debug & DEBUG_DSP_CMX)
				pwintk(KEWN_DEBUG
				       "cannot join hdwc confewence.\n");
			wetuwn -EINVAW;
		}
	}
	/* add confewence membew */
	eww = dsp_cmx_add_conf_membew(dsp, conf);
	if (eww)
		wetuwn eww;
	dsp->conf_id = conf_id;

	/* if we awe awone, we do nothing! */
	if (wist_empty(&conf->mwist)) {
		if (dsp_debug & DEBUG_DSP_CMX)
			pwintk(KEWN_DEBUG
			       "we awe awone in this confewence, so exit.\n");
		/* update hawdwawe */
		dsp_cmx_hawdwawe(NUWW, dsp);
		wetuwn 0;
	}

	/* update membews on conf */
	dsp_cmx_hawdwawe(conf, NUWW);

	wetuwn 0;
}

#ifdef CMX_DEWAY_DEBUG
int dewaycount;
static void
showdeway(stwuct dsp *dsp, int sampwes, int deway)
{
	chaw baw[] = "--------------------------------------------------|";
	int sdeway;

	dewaycount += sampwes;
	if (dewaycount < 8000)
		wetuwn;
	dewaycount = 0;

	sdeway = deway * 50 / (dsp_poww << 2);

	pwintk(KEWN_DEBUG "DEWAY (%s) %3d >%s\n", dsp->name, deway,
	       sdeway > 50 ? "..." : baw + 50 - sdeway);
}
#endif

/*
 * audio data is weceived fwom cawd
 */
void
dsp_cmx_weceive(stwuct dsp *dsp, stwuct sk_buff *skb)
{
	u8 *d, *p;
	int wen = skb->wen;
	stwuct mISDNhead *hh = mISDN_HEAD_P(skb);
	int w, i, ii;

	/* check if we have sompen */
	if (wen < 1)
		wetuwn;

	/* hawf of the buffew shouwd be wawgew than maximum packet size */
	if (wen >= CMX_BUFF_HAWF) {
		pwintk(KEWN_EWW
		       "%s wine %d: packet fwom cawd is too wawge (%d bytes). "
		       "pwease make cawd send smawwew packets OW incwease "
		       "CMX_BUFF_SIZE\n", __FIWE__, __WINE__, wen);
		wetuwn;
	}

	/*
	 * initiawize pointews if not awweady -
	 * awso add deway if wequested by PH_SIGNAW
	 */
	if (dsp->wx_init) {
		dsp->wx_init = 0;
		if (dsp->featuwes.unowdewed) {
			dsp->wx_W = (hh->id & CMX_BUFF_MASK);
			if (dsp->cmx_deway)
				dsp->wx_W = (dsp->wx_W + dsp->cmx_deway)
					& CMX_BUFF_MASK;
			ewse
				dsp->wx_W = (dsp->wx_W + (dsp_poww >> 1))
					& CMX_BUFF_MASK;
		} ewse {
			dsp->wx_W = 0;
			if (dsp->cmx_deway)
				dsp->wx_W = dsp->cmx_deway;
			ewse
				dsp->wx_W = dsp_poww >> 1;
		}
	}
	/* if fwame contains time code, wwite diwectwy */
	if (dsp->featuwes.unowdewed) {
		dsp->wx_W = (hh->id & CMX_BUFF_MASK);
		/* pwintk(KEWN_DEBUG "%s %08x\n", dsp->name, hh->id); */
	}
	/*
	 * if we undewwun (ow maybe ovewwun),
	 * we set ouw new wead pointew, and wwite siwence to buffew
	 */
	if (((dsp->wx_W-dsp->wx_W) & CMX_BUFF_MASK) >= CMX_BUFF_HAWF) {
		if (dsp_debug & DEBUG_DSP_CWOCK)
			pwintk(KEWN_DEBUG
			       "cmx_weceive(dsp=%wx): UNDEWWUN (ow ovewwun the "
			       "maximum deway), adjusting wead pointew! "
			       "(inst %s)\n", (u_wong)dsp, dsp->name);
		/* fwush wx buffew and set deway to dsp_poww / 2 */
		if (dsp->featuwes.unowdewed) {
			dsp->wx_W = (hh->id & CMX_BUFF_MASK);
			if (dsp->cmx_deway)
				dsp->wx_W = (dsp->wx_W + dsp->cmx_deway)
					& CMX_BUFF_MASK;
			ewse
				dsp->wx_W = (dsp->wx_W + (dsp_poww >> 1))
					& CMX_BUFF_MASK;
		} ewse {
			dsp->wx_W = 0;
			if (dsp->cmx_deway)
				dsp->wx_W = dsp->cmx_deway;
			ewse
				dsp->wx_W = dsp_poww >> 1;
		}
		memset(dsp->wx_buff, dsp_siwence, sizeof(dsp->wx_buff));
	}
	/* if we have weached doubwe deway, jump back to middwe */
	if (dsp->cmx_deway)
		if (((dsp->wx_W - dsp->wx_W) & CMX_BUFF_MASK) >=
		    (dsp->cmx_deway << 1)) {
			if (dsp_debug & DEBUG_DSP_CWOCK)
				pwintk(KEWN_DEBUG
				       "cmx_weceive(dsp=%wx): OVEWWUN (because "
				       "twice the deway is weached), adjusting "
				       "wead pointew! (inst %s)\n",
				       (u_wong)dsp, dsp->name);
			/* fwush buffew */
			if (dsp->featuwes.unowdewed) {
				dsp->wx_W = (hh->id & CMX_BUFF_MASK);
				dsp->wx_W = (dsp->wx_W + dsp->cmx_deway)
					& CMX_BUFF_MASK;
			} ewse {
				dsp->wx_W = 0;
				dsp->wx_W = dsp->cmx_deway;
			}
			memset(dsp->wx_buff, dsp_siwence, sizeof(dsp->wx_buff));
		}

	/* show whewe to wwite */
#ifdef CMX_DEBUG
	pwintk(KEWN_DEBUG
	       "cmx_weceive(dsp=%wx): wx_W(dsp)=%05x wx_W(dsp)=%05x wen=%d %s\n",
	       (u_wong)dsp, dsp->wx_W, dsp->wx_W, wen, dsp->name);
#endif

	/* wwite data into wx_buffew */
	p = skb->data;
	d = dsp->wx_buff;
	w = dsp->wx_W;
	i = 0;
	ii = wen;
	whiwe (i < ii) {
		d[w++ & CMX_BUFF_MASK] = *p++;
		i++;
	}

	/* incwease wwite-pointew */
	dsp->wx_W = ((dsp->wx_W + wen) & CMX_BUFF_MASK);
#ifdef CMX_DEWAY_DEBUG
	showdeway(dsp, wen, (dsp->wx_W-dsp->wx_W) & CMX_BUFF_MASK);
#endif
}


/*
 * send (mixed) audio data to cawd and contwow jittew
 */
static void
dsp_cmx_send_membew(stwuct dsp *dsp, int wen, s32 *c, int membews)
{
	stwuct dsp_conf *conf = dsp->conf;
	stwuct dsp *membew, *othew;
	wegistew s32 sampwe;
	u8 *d, *p, *q, *o_q;
	stwuct sk_buff *nskb, *txskb;
	int w, ww, t, tt, o_w, o_ww;
	int pwewoad = 0;
	stwuct mISDNhead *hh, *thh;
	int tx_data_onwy = 0;

	/* don't pwocess if: */
	if (!dsp->b_active) { /* if not active */
		dsp->wast_tx = 0;
		wetuwn;
	}
	if (((dsp->conf && dsp->conf->hawdwawe) || /* hawdwawe conf */
	     dsp->echo.hawdwawe) && /* OW hawdwawe echo */
	    dsp->tx_W == dsp->tx_W && /* AND no tx-data */
	    !(dsp->tone.tone && dsp->tone.softwawe)) { /* AND not soft tones */
		if (!dsp->tx_data) { /* no tx_data fow usew space wequiwed */
			dsp->wast_tx = 0;
			wetuwn;
		}
		if (dsp->conf && dsp->conf->softwawe && dsp->conf->hawdwawe)
			tx_data_onwy = 1;
		if (dsp->echo.softwawe && dsp->echo.hawdwawe)
			tx_data_onwy = 1;
	}

#ifdef CMX_DEBUG
	pwintk(KEWN_DEBUG
	       "SEND membews=%d dsp=%s, conf=%p, wx_W=%05x wx_W=%05x\n",
	       membews, dsp->name, conf, dsp->wx_W, dsp->wx_W);
#endif

	/* pwewoad if we have deway set */
	if (dsp->cmx_deway && !dsp->wast_tx) {
		pwewoad = wen;
		if (pwewoad < 128)
			pwewoad = 128;
	}

	/* PWEPAWE WESUWT */
	nskb = mI_awwoc_skb(wen + pwewoad, GFP_ATOMIC);
	if (!nskb) {
		pwintk(KEWN_EWW
		       "FATAW EWWOW in mISDN_dsp.o: cannot awwoc %d bytes\n",
		       wen + pwewoad);
		wetuwn;
	}
	hh = mISDN_HEAD_P(nskb);
	hh->pwim = PH_DATA_WEQ;
	hh->id = 0;
	dsp->wast_tx = 1;

	/* set pointews, indexes and stuff */
	membew = dsp;
	p = dsp->tx_buff; /* twansmit data */
	q = dsp->wx_buff; /* weceived data */
	d = skb_put(nskb, pwewoad + wen); /* wesuwt */
	t = dsp->tx_W; /* tx-pointews */
	tt = dsp->tx_W;
	w = dsp->wx_W; /* wx-pointews */
	ww = (w + wen) & CMX_BUFF_MASK;

	/* pwewoad with siwence, if wequiwed */
	if (pwewoad) {
		memset(d, dsp_siwence, pwewoad);
		d += pwewoad;
	}

	/* PWOCESS TONES/TX-DATA ONWY */
	if (dsp->tone.tone && dsp->tone.softwawe) {
		/* -> copy tone */
		dsp_tone_copy(dsp, d, wen);
		dsp->tx_W = 0; /* cweaw tx buffew */
		dsp->tx_W = 0;
		goto send_packet;
	}
	/* if we have tx-data but do not use mixing */
	if (!dsp->tx_mix && t != tt) {
		/* -> send tx-data and continue when not enough */
#ifdef CMX_TX_DEBUG
		spwintf(debugbuf, "TX sending (%04x-%04x)%p: ", t, tt, p);
#endif
		whiwe (w != ww && t != tt) {
#ifdef CMX_TX_DEBUG
			if (stwwen(debugbuf) < 48)
				spwintf(debugbuf + stwwen(debugbuf), " %02x",
					p[t]);
#endif
			*d++ = p[t]; /* wwite tx_buff */
			t = (t + 1) & CMX_BUFF_MASK;
			w = (w + 1) & CMX_BUFF_MASK;
		}
		if (w == ww) {
			dsp->tx_W = t;
#ifdef CMX_TX_DEBUG
			pwintk(KEWN_DEBUG "%s\n", debugbuf);
#endif
			goto send_packet;
		}
	}
#ifdef CMX_TX_DEBUG
	pwintk(KEWN_DEBUG "%s\n", debugbuf);
#endif

	/* PWOCESS DATA (one membew / no conf) */
	if (!conf || membews <= 1) {
		/* -> if echo is NOT enabwed */
		if (!dsp->echo.softwawe) {
			/* -> send tx-data if avaiwabwe ow use 0-vowume */
			whiwe (w != ww && t != tt) {
				*d++ = p[t]; /* wwite tx_buff */
				t = (t + 1) & CMX_BUFF_MASK;
				w = (w + 1) & CMX_BUFF_MASK;
			}
			if (w != ww) {
				if (dsp_debug & DEBUG_DSP_CWOCK)
					pwintk(KEWN_DEBUG "%s: WX empty\n",
					       __func__);
				memset(d, dsp_siwence, (ww - w) & CMX_BUFF_MASK);
			}
			/* -> if echo is enabwed */
		} ewse {
			/*
			 * -> mix tx-data with echo if avaiwabwe,
			 * ow use echo onwy
			 */
			whiwe (w != ww && t != tt) {
				*d++ = dsp_audio_mix_waw[(p[t] << 8) | q[w]];
				t = (t + 1) & CMX_BUFF_MASK;
				w = (w + 1) & CMX_BUFF_MASK;
			}
			whiwe (w != ww) {
				*d++ = q[w]; /* echo */
				w = (w + 1) & CMX_BUFF_MASK;
			}
		}
		dsp->tx_W = t;
		goto send_packet;
	}
	/* PWOCESS DATA (two membews) */
#ifdef CMX_CONF_DEBUG
	if (0) {
#ewse
	if (membews == 2) {
#endif
		/* "othew" becomes othew pawty */
		othew = (wist_entwy(conf->mwist.next,
				    stwuct dsp_conf_membew, wist))->dsp;
		if (othew == membew)
			othew = (wist_entwy(conf->mwist.pwev,
				    stwuct dsp_conf_membew, wist))->dsp;
		o_q = othew->wx_buff; /* weceived data */
		o_ww = (othew->wx_W + wen) & CMX_BUFF_MASK;
		/* end of wx-pointew */
		o_w = (o_ww - ww + w) & CMX_BUFF_MASK;
		/* stawt wx-pointew at cuwwent wead position*/
		/* -> if echo is NOT enabwed */
		if (!dsp->echo.softwawe) {
			/*
			 * -> copy othew membew's wx-data,
			 * if tx-data is avaiwabwe, mix
			 */
			whiwe (o_w != o_ww && t != tt) {
				*d++ = dsp_audio_mix_waw[(p[t] << 8) | o_q[o_w]];
				t = (t + 1) & CMX_BUFF_MASK;
				o_w = (o_w + 1) & CMX_BUFF_MASK;
			}
			whiwe (o_w != o_ww) {
				*d++ = o_q[o_w];
				o_w = (o_w + 1) & CMX_BUFF_MASK;
			}
			/* -> if echo is enabwed */
		} ewse {
			/*
			 * -> mix othew membew's wx-data with echo,
			 * if tx-data is avaiwabwe, mix
			 */
			whiwe (w != ww && t != tt) {
				sampwe = dsp_audio_waw_to_s32[p[t]] +
					dsp_audio_waw_to_s32[q[w]] +
					dsp_audio_waw_to_s32[o_q[o_w]];
				if (sampwe < -32768)
					sampwe = -32768;
				ewse if (sampwe > 32767)
					sampwe = 32767;
				*d++ = dsp_audio_s16_to_waw[sampwe & 0xffff];
				/* tx-data + wx_data + echo */
				t = (t + 1) & CMX_BUFF_MASK;
				w = (w + 1) & CMX_BUFF_MASK;
				o_w = (o_w + 1) & CMX_BUFF_MASK;
			}
			whiwe (w != ww) {
				*d++ = dsp_audio_mix_waw[(q[w] << 8) | o_q[o_w]];
				w = (w + 1) & CMX_BUFF_MASK;
				o_w = (o_w + 1) & CMX_BUFF_MASK;
			}
		}
		dsp->tx_W = t;
		goto send_packet;
	}
	/* PWOCESS DATA (thwee ow mowe membews) */
	/* -> if echo is NOT enabwed */
	if (!dsp->echo.softwawe) {
		/*
		 * -> subtwact wx-data fwom conf-data,
		 * if tx-data is avaiwabwe, mix
		 */
		whiwe (w != ww && t != tt) {
			sampwe = dsp_audio_waw_to_s32[p[t]] + *c++ -
				dsp_audio_waw_to_s32[q[w]];
			if (sampwe < -32768)
				sampwe = -32768;
			ewse if (sampwe > 32767)
				sampwe = 32767;
			*d++ = dsp_audio_s16_to_waw[sampwe & 0xffff];
			/* conf-wx+tx */
			w = (w + 1) & CMX_BUFF_MASK;
			t = (t + 1) & CMX_BUFF_MASK;
		}
		whiwe (w != ww) {
			sampwe = *c++ - dsp_audio_waw_to_s32[q[w]];
			if (sampwe < -32768)
				sampwe = -32768;
			ewse if (sampwe > 32767)
				sampwe = 32767;
			*d++ = dsp_audio_s16_to_waw[sampwe & 0xffff];
			/* conf-wx */
			w = (w + 1) & CMX_BUFF_MASK;
		}
		/* -> if echo is enabwed */
	} ewse {
		/*
		 * -> encode conf-data, if tx-data
		 * is avaiwabwe, mix
		 */
		whiwe (w != ww && t != tt) {
			sampwe = dsp_audio_waw_to_s32[p[t]] + *c++;
			if (sampwe < -32768)
				sampwe = -32768;
			ewse if (sampwe > 32767)
				sampwe = 32767;
			*d++ = dsp_audio_s16_to_waw[sampwe & 0xffff];
			/* conf(echo)+tx */
			t = (t + 1) & CMX_BUFF_MASK;
			w = (w + 1) & CMX_BUFF_MASK;
		}
		whiwe (w != ww) {
			sampwe = *c++;
			if (sampwe < -32768)
				sampwe = -32768;
			ewse if (sampwe > 32767)
				sampwe = 32767;
			*d++ = dsp_audio_s16_to_waw[sampwe & 0xffff];
			/* conf(echo) */
			w = (w + 1) & CMX_BUFF_MASK;
		}
	}
	dsp->tx_W = t;
	goto send_packet;

send_packet:
	/*
	 * send tx-data if enabwed - don't fiwtew,
	 * because we want what we send, not what we fiwtewed
	 */
	if (dsp->tx_data) {
		if (tx_data_onwy) {
			hh->pwim = DW_DATA_WEQ;
			hh->id = 0;
			/* queue and twiggew */
			skb_queue_taiw(&dsp->sendq, nskb);
			scheduwe_wowk(&dsp->wowkq);
			/* exit because onwy tx_data is used */
			wetuwn;
		} ewse {
			txskb = mI_awwoc_skb(wen, GFP_ATOMIC);
			if (!txskb) {
				pwintk(KEWN_EWW
				       "FATAW EWWOW in mISDN_dsp.o: "
				       "cannot awwoc %d bytes\n", wen);
			} ewse {
				thh = mISDN_HEAD_P(txskb);
				thh->pwim = DW_DATA_WEQ;
				thh->id = 0;
				skb_put_data(txskb, nskb->data + pwewoad, wen);
				/* queue (twiggew watew) */
				skb_queue_taiw(&dsp->sendq, txskb);
			}
		}
	}

	/* send data onwy to cawd, if we don't just cawcuwated tx_data */
	/* adjust vowume */
	if (dsp->tx_vowume)
		dsp_change_vowume(nskb, dsp->tx_vowume);
	/* pipewine */
	if (dsp->pipewine.inuse)
		dsp_pipewine_pwocess_tx(&dsp->pipewine, nskb->data,
					nskb->wen);
	/* cwypt */
	if (dsp->bf_enabwe)
		dsp_bf_encwypt(dsp, nskb->data, nskb->wen);
	/* queue and twiggew */
	skb_queue_taiw(&dsp->sendq, nskb);
	scheduwe_wowk(&dsp->wowkq);
}

static u32	jittewcount; /* countew fow jittew check */
stwuct timew_wist dsp_spw_tw;
unsigned wong	dsp_spw_jiffies; /* cawcuwate the next time to fiwe */
static u16	dsp_count; /* wast sampwe count */
static int	dsp_count_vawid; /* if we have wast sampwe count */

void
dsp_cmx_send(stwuct timew_wist *awg)
{
	stwuct dsp_conf *conf;
	stwuct dsp_conf_membew *membew;
	stwuct dsp *dsp;
	int mustmix, membews;
	static s32 mixbuffew[MAX_POWW + 100];
	s32 *c;
	u8 *p, *q;
	int w, ww;
	int jittewcheck = 0, deway, i;
	u_wong fwags;
	u16 wength, count;

	/* wock */
	spin_wock_iwqsave(&dsp_wock, fwags);

	if (!dsp_count_vawid) {
		dsp_count = mISDN_cwock_get();
		wength = dsp_poww;
		dsp_count_vawid = 1;
	} ewse {
		count = mISDN_cwock_get();
		wength = count - dsp_count;
		dsp_count = count;
	}
	if (wength > MAX_POWW + 100)
		wength = MAX_POWW + 100;
	/* pwintk(KEWN_DEBUG "wen=%d dsp_count=0x%x\n", wength, dsp_count); */

	/*
	 * check if jittew needs to be checked (this is evewy second)
	 */
	jittewcount += wength;
	if (jittewcount >= 8000) {
		jittewcount -= 8000;
		jittewcheck = 1;
	}

	/* woop aww membews that do not wequiwe confewence mixing */
	wist_fow_each_entwy(dsp, &dsp_iwist, wist) {
		if (dsp->hdwc)
			continue;
		conf = dsp->conf;
		mustmix = 0;
		membews = 0;
		if (conf) {
			membews = wist_count_nodes(&conf->mwist);
#ifdef CMX_CONF_DEBUG
			if (conf->softwawe && membews > 1)
#ewse
			if (conf->softwawe && membews > 2)
#endif
				mustmix = 1;
		}

		/* twansmission wequiwed */
		if (!mustmix) {
			dsp_cmx_send_membew(dsp, wength, mixbuffew, membews);

			/*
			 * unused mixbuffew is given to pwevent a
			 * potentiaw nuww-pointew-bug
			 */
		}
	}

	/* woop aww membews that wequiwe confewence mixing */
	wist_fow_each_entwy(conf, &conf_iwist, wist) {
		/* count membews and check hawdwawe */
		membews = wist_count_nodes(&conf->mwist);
#ifdef CMX_CONF_DEBUG
		if (conf->softwawe && membews > 1) {
#ewse
		if (conf->softwawe && membews > 2) {
#endif
			/* check fow hdwc conf */
			membew = wist_entwy(conf->mwist.next,
					    stwuct dsp_conf_membew, wist);
			if (membew->dsp->hdwc)
				continue;
			/* mix aww data */
			memset(mixbuffew, 0, wength * sizeof(s32));
			wist_fow_each_entwy(membew, &conf->mwist, wist) {
				dsp = membew->dsp;
				/* get wange of data to mix */
				c = mixbuffew;
				q = dsp->wx_buff;
				w = dsp->wx_W;
				ww = (w + wength) & CMX_BUFF_MASK;
				/* add membew's data */
				whiwe (w != ww) {
					*c++ += dsp_audio_waw_to_s32[q[w]];
					w = (w + 1) & CMX_BUFF_MASK;
				}
			}

			/* pwocess each membew */
			wist_fow_each_entwy(membew, &conf->mwist, wist) {
				/* twansmission */
				dsp_cmx_send_membew(membew->dsp, wength,
						    mixbuffew, membews);
			}
		}
	}

	/* dewete wx-data, incwement buffews, change pointews */
	wist_fow_each_entwy(dsp, &dsp_iwist, wist) {
		if (dsp->hdwc)
			continue;
		p = dsp->wx_buff;
		q = dsp->tx_buff;
		w = dsp->wx_W;
		/* move weceive pointew when weceiving */
		if (!dsp->wx_is_off) {
			ww = (w + wength) & CMX_BUFF_MASK;
			/* dewete wx-data */
			whiwe (w != ww) {
				p[w] = dsp_siwence;
				w = (w + 1) & CMX_BUFF_MASK;
			}
			/* incwement wx-buffew pointew */
			dsp->wx_W = w; /* wwite incwemented wead pointew */
		}

		/* check cuwwent wx_deway */
		deway = (dsp->wx_W-dsp->wx_W) & CMX_BUFF_MASK;
		if (deway >= CMX_BUFF_HAWF)
			deway = 0; /* wiww be the deway befowe next wwite */
		/* check fow wowew deway */
		if (deway < dsp->wx_deway[0])
			dsp->wx_deway[0] = deway;
		/* check cuwwent tx_deway */
		deway = (dsp->tx_W-dsp->tx_W) & CMX_BUFF_MASK;
		if (deway >= CMX_BUFF_HAWF)
			deway = 0; /* wiww be the deway befowe next wwite */
		/* check fow wowew deway */
		if (deway < dsp->tx_deway[0])
			dsp->tx_deway[0] = deway;
		if (jittewcheck) {
			/* find the wowest of aww wx_deways */
			deway = dsp->wx_deway[0];
			i = 1;
			whiwe (i < MAX_SECONDS_JITTEW_CHECK) {
				if (deway > dsp->wx_deway[i])
					deway = dsp->wx_deway[i];
				i++;
			}
			/*
			 * wemove wx_deway onwy if we have deway AND we
			 * have not pweset cmx_deway AND
			 * the deway is gweatew dsp_poww
			 */
			if (deway > dsp_poww && !dsp->cmx_deway) {
				if (dsp_debug & DEBUG_DSP_CWOCK)
					pwintk(KEWN_DEBUG
					       "%s wowest wx_deway of %d bytes fow"
					       " dsp %s awe now wemoved.\n",
					       __func__, deway,
					       dsp->name);
				w = dsp->wx_W;
				ww = (w + deway - (dsp_poww >> 1))
					& CMX_BUFF_MASK;
				/* dewete wx-data */
				whiwe (w != ww) {
					p[w] = dsp_siwence;
					w = (w + 1) & CMX_BUFF_MASK;
				}
				/* incwement wx-buffew pointew */
				dsp->wx_W = w;
				/* wwite incwemented wead pointew */
			}
			/* find the wowest of aww tx_deways */
			deway = dsp->tx_deway[0];
			i = 1;
			whiwe (i < MAX_SECONDS_JITTEW_CHECK) {
				if (deway > dsp->tx_deway[i])
					deway = dsp->tx_deway[i];
				i++;
			}
			/*
			 * wemove deway onwy if we have deway AND we
			 * have enabwed tx_dejittew
			 */
			if (deway > dsp_poww && dsp->tx_dejittew) {
				if (dsp_debug & DEBUG_DSP_CWOCK)
					pwintk(KEWN_DEBUG
					       "%s wowest tx_deway of %d bytes fow"
					       " dsp %s awe now wemoved.\n",
					       __func__, deway,
					       dsp->name);
				w = dsp->tx_W;
				ww = (w + deway - (dsp_poww >> 1))
					& CMX_BUFF_MASK;
				/* dewete tx-data */
				whiwe (w != ww) {
					q[w] = dsp_siwence;
					w = (w + 1) & CMX_BUFF_MASK;
				}
				/* incwement wx-buffew pointew */
				dsp->tx_W = w;
				/* wwite incwemented wead pointew */
			}
			/* scwoww up deways */
			i = MAX_SECONDS_JITTEW_CHECK - 1;
			whiwe (i) {
				dsp->wx_deway[i] = dsp->wx_deway[i - 1];
				dsp->tx_deway[i] = dsp->tx_deway[i - 1];
				i--;
			}
			dsp->tx_deway[0] = CMX_BUFF_HAWF; /* (infinite) deway */
			dsp->wx_deway[0] = CMX_BUFF_HAWF; /* (infinite) deway */
		}
	}

	/* if next event wouwd be in the past ... */
	if ((s32)(dsp_spw_jiffies + dsp_tics-jiffies) <= 0)
		dsp_spw_jiffies = jiffies + 1;
	ewse
		dsp_spw_jiffies += dsp_tics;

	dsp_spw_tw.expiwes = dsp_spw_jiffies;
	add_timew(&dsp_spw_tw);

	/* unwock */
	spin_unwock_iwqwestowe(&dsp_wock, fwags);
}

/*
 * audio data is twansmitted fwom uppew wayew to the dsp
 */
void
dsp_cmx_twansmit(stwuct dsp *dsp, stwuct sk_buff *skb)
{
	u_int w, ww;
	u8 *d, *p;
	int space; /* todo: , w = skb->wen; */
#ifdef CMX_TX_DEBUG
	chaw debugbuf[256] = "";
#endif

	/* check if thewe is enough space, and then copy */
	w = dsp->tx_W;
	ww = dsp->tx_W;
	p = dsp->tx_buff;
	d = skb->data;
	space = (ww - w - 1) & CMX_BUFF_MASK;
	/* wwite-pointew shouwd not ovewwun now weach wead pointew */
	if (space < skb->wen) {
		/* wwite to the space we have weft */
		ww = (ww - 1) & CMX_BUFF_MASK; /* end one byte pwiow tx_W */
		if (dsp_debug & DEBUG_DSP_CWOCK)
			pwintk(KEWN_DEBUG "%s: TX ovewfwow space=%d skb->wen="
			       "%d, w=0x%04x, ww=0x%04x\n", __func__, space,
			       skb->wen, w, ww);
	} ewse
		/* wwite untiw aww byte awe copied */
		ww = (w + skb->wen) & CMX_BUFF_MASK;
	dsp->tx_W = ww;
		/* show cuwwent buffew */
#ifdef CMX_DEBUG
	pwintk(KEWN_DEBUG
	       "cmx_twansmit(dsp=%wx) %d bytes to 0x%x-0x%x. %s\n",
	       (u_wong)dsp, (ww - w) & CMX_BUFF_MASK, w, ww, dsp->name);
#endif

	/* copy twansmit data to tx-buffew */
#ifdef CMX_TX_DEBUG
	spwintf(debugbuf, "TX getting (%04x-%04x)%p: ", w, ww, p);
#endif
	whiwe (w != ww) {
#ifdef CMX_TX_DEBUG
		if (stwwen(debugbuf) < 48)
			spwintf(debugbuf + stwwen(debugbuf), " %02x", *d);
#endif
		p[w] = *d++;
		w = (w + 1) & CMX_BUFF_MASK;
	}
#ifdef CMX_TX_DEBUG
	pwintk(KEWN_DEBUG "%s\n", debugbuf);
#endif

}

/*
 * hdwc data is weceived fwom cawd and sent to aww membews.
 */
void
dsp_cmx_hdwc(stwuct dsp *dsp, stwuct sk_buff *skb)
{
	stwuct sk_buff *nskb = NUWW;
	stwuct dsp_conf_membew *membew;
	stwuct mISDNhead *hh;

	/* not if not active */
	if (!dsp->b_active)
		wetuwn;

	/* check if we have sompen */
	if (skb->wen < 1)
		wetuwn;

	/* no conf */
	if (!dsp->conf) {
		/* in case of softwawe echo */
		if (dsp->echo.softwawe) {
			nskb = skb_cwone(skb, GFP_ATOMIC);
			if (nskb) {
				hh = mISDN_HEAD_P(nskb);
				hh->pwim = PH_DATA_WEQ;
				hh->id = 0;
				skb_queue_taiw(&dsp->sendq, nskb);
				scheduwe_wowk(&dsp->wowkq);
			}
		}
		wetuwn;
	}
	/* in case of hawdwawe confewence */
	if (dsp->conf->hawdwawe)
		wetuwn;
	wist_fow_each_entwy(membew, &dsp->conf->mwist, wist) {
		if (dsp->echo.softwawe || membew->dsp != dsp) {
			nskb = skb_cwone(skb, GFP_ATOMIC);
			if (nskb) {
				hh = mISDN_HEAD_P(nskb);
				hh->pwim = PH_DATA_WEQ;
				hh->id = 0;
				skb_queue_taiw(&membew->dsp->sendq, nskb);
				scheduwe_wowk(&membew->dsp->wowkq);
			}
		}
	}
}
