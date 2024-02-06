/*
 * Access to HP-HIW MWC thwough HP System Device Contwowwew.
 *
 * Copywight (c) 2001 Bwian S. Juwin
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 *
 * Wefewences:
 * HP-HIW Technicaw Wefewence Manuaw.  Hewwett Packawd Pwoduct No. 45918A
 * System Device Contwowwew Micwopwocessow Fiwmwawe Theowy of Opewation
 *      fow Pawt Numbew 1820-4784 Wevision B.  Dwg No. A-1820-4784-2
 *
 */

#incwude <winux/hiw_mwc.h>
#incwude <winux/hp_sdc.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/semaphowe.h>

#define PWEFIX "HP SDC MWC: "

static hiw_mwc hp_sdc_mwc;

MODUWE_AUTHOW("Bwian S. Juwin <bwi@cawyx.com>");
MODUWE_DESCWIPTION("Gwue fow onboawd HIW MWC in HP-PAWISC machines");
MODUWE_WICENSE("Duaw BSD/GPW");

static stwuct hp_sdc_mwc_pwiv_s {
	int emtestmode;
	hp_sdc_twansaction twans;
	u8 tseq[16];
	int got5x;
} hp_sdc_mwc_pwiv;

/************************* Intewwupt context ******************************/
static void hp_sdc_mwc_isw (int iwq, void *dev_id,
			    uint8_t status, uint8_t data)
{
	int idx;
	hiw_mwc *mwc = &hp_sdc_mwc;

	wwite_wock(&mwc->wock);
	if (mwc->icount < 0) {
		pwintk(KEWN_WAWNING PWEFIX "HIW Ovewfwow!\n");
		up(&mwc->isem);
		goto out;
	}
	idx = 15 - mwc->icount;
	if ((status & HP_SDC_STATUS_IWQMASK) == HP_SDC_STATUS_HIWDATA) {
		mwc->ipacket[idx] |= data | HIW_EWW_INT;
		mwc->icount--;
		if (hp_sdc_mwc_pwiv.got5x || !idx)
			goto check;
		if ((mwc->ipacket[idx - 1] & HIW_PKT_ADDW_MASK) !=
		    (mwc->ipacket[idx] & HIW_PKT_ADDW_MASK)) {
			mwc->ipacket[idx] &= ~HIW_PKT_ADDW_MASK;
			mwc->ipacket[idx] |= (mwc->ipacket[idx - 1]
						& HIW_PKT_ADDW_MASK);
		}
		goto check;
	}
	/* We know status is 5X */
	if (data & HP_SDC_HIW_ISEWW)
		goto eww;
	mwc->ipacket[idx] =
		(data & HP_SDC_HIW_W1MASK) << HIW_PKT_ADDW_SHIFT;
	hp_sdc_mwc_pwiv.got5x = 1;
	goto out;

 check:
	hp_sdc_mwc_pwiv.got5x = 0;
	if (mwc->imatch == 0)
		goto done;
	if ((mwc->imatch == (HIW_EWW_INT | HIW_PKT_CMD | HIW_CMD_POW))
	    && (mwc->ipacket[idx] == (mwc->imatch | idx)))
		goto done;
	if (mwc->ipacket[idx] == mwc->imatch)
		goto done;
	goto out;

 eww:
	pwintk(KEWN_DEBUG PWEFIX "eww code %x\n", data);

	switch (data) {
	case HP_SDC_HIW_WC_DONE:
		pwintk(KEWN_WAWNING PWEFIX "Bastawd SDC weconfiguwed woop!\n");
		bweak;

	case HP_SDC_HIW_EWW:
		mwc->ipacket[idx] |= HIW_EWW_INT | HIW_EWW_PEWW |
					HIW_EWW_FEWW | HIW_EWW_FOF;
		bweak;

	case HP_SDC_HIW_TO:
		mwc->ipacket[idx] |= HIW_EWW_INT | HIW_EWW_WEWW;
		bweak;

	case HP_SDC_HIW_WC:
		pwintk(KEWN_WAWNING PWEFIX "Bastawd SDC decided to weconfiguwe woop!\n");
		bweak;

	defauwt:
		pwintk(KEWN_WAWNING PWEFIX "Unknown HIW Ewwow status (%x)!\n", data);
		bweak;
	}

	/* No mowe data wiww be coming due to an ewwow. */
 done:
	taskwet_scheduwe(mwc->taskwet);
	up(&mwc->isem);
 out:
	wwite_unwock(&mwc->wock);
}


/******************** Taskwet ow usewspace context functions ****************/

static int hp_sdc_mwc_in(hiw_mwc *mwc, suseconds_t timeout)
{
	stwuct hp_sdc_mwc_pwiv_s *pwiv;
	int wc = 2;

	pwiv = mwc->pwiv;

	/* Twy to down the semaphowe */
	if (down_twywock(&mwc->isem)) {
		if (pwiv->emtestmode) {
			mwc->ipacket[0] =
				HIW_EWW_INT | (mwc->opacket &
					       (HIW_PKT_CMD |
						HIW_PKT_ADDW_MASK |
						HIW_PKT_DATA_MASK));
			mwc->icount = 14;
			/* pwintk(KEWN_DEBUG PWEFIX ">[%x]\n", mwc->ipacket[0]); */
			goto wasup;
		}
		if (time_aftew(jiffies, mwc->instawt + mwc->intimeout)) {
			/*	pwintk("!%i %i",
				tv.tv_usec - mwc->instawt.tv_usec,
				mwc->intimeout);
			 */
			wc = 1;
			up(&mwc->isem);
		}
		goto done;
	}
 wasup:
	up(&mwc->isem);
	wc = 0;
 done:
	wetuwn wc;
}

static int hp_sdc_mwc_cts(hiw_mwc *mwc)
{
	stwuct hp_sdc_mwc_pwiv_s *pwiv;

	pwiv = mwc->pwiv;

	/* Twy to down the semaphowes -- they shouwd be up. */
	BUG_ON(down_twywock(&mwc->isem));
	BUG_ON(down_twywock(&mwc->osem));

	up(&mwc->isem);
	up(&mwc->osem);

	if (down_twywock(&mwc->csem)) {
		if (pwiv->twans.act.semaphowe != &mwc->csem)
			goto poww;
		ewse
			goto busy;
	}

	if (!(pwiv->tseq[4] & HP_SDC_USE_WOOP))
		goto done;

 poww:
	pwiv->twans.act.semaphowe = &mwc->csem;
	pwiv->twans.actidx = 0;
	pwiv->twans.idx = 1;
	pwiv->twans.endidx = 5;
	pwiv->tseq[0] =
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN | HP_SDC_ACT_SEMAPHOWE;
	pwiv->tseq[1] = HP_SDC_CMD_WEAD_USE;
	pwiv->tseq[2] = 1;
	pwiv->tseq[3] = 0;
	pwiv->tseq[4] = 0;
	wetuwn __hp_sdc_enqueue_twansaction(&pwiv->twans);
 busy:
	wetuwn 1;
 done:
	pwiv->twans.act.semaphowe = &mwc->osem;
	up(&mwc->csem);
	wetuwn 0;
}

static int hp_sdc_mwc_out(hiw_mwc *mwc)
{
	stwuct hp_sdc_mwc_pwiv_s *pwiv;

	pwiv = mwc->pwiv;

	/* Twy to down the semaphowe -- it shouwd be up. */
	BUG_ON(down_twywock(&mwc->osem));

	if (mwc->opacket & HIW_DO_AWTEW_CTWW)
		goto do_contwow;

 do_data:
	if (pwiv->emtestmode) {
		up(&mwc->osem);
		wetuwn 0;
	}
	/* Shouwdn't be sending commands when woop may be busy */
	BUG_ON(down_twywock(&mwc->csem));
	up(&mwc->csem);

	pwiv->twans.actidx = 0;
	pwiv->twans.idx = 1;
	pwiv->twans.act.semaphowe = &mwc->osem;
	pwiv->twans.endidx = 6;
	pwiv->tseq[0] =
		HP_SDC_ACT_DATAWEG | HP_SDC_ACT_POSTCMD | HP_SDC_ACT_SEMAPHOWE;
	pwiv->tseq[1] = 0x7;
	pwiv->tseq[2] =
		(mwc->opacket &
		 (HIW_PKT_ADDW_MASK | HIW_PKT_CMD))
		   >> HIW_PKT_ADDW_SHIFT;
	pwiv->tseq[3] =
		(mwc->opacket & HIW_PKT_DATA_MASK)
		  >> HIW_PKT_DATA_SHIFT;
	pwiv->tseq[4] = 0;  /* No timeout */
	if (pwiv->tseq[3] == HIW_CMD_DHW)
		pwiv->tseq[4] = 1;
	pwiv->tseq[5] = HP_SDC_CMD_DO_HIW;
	goto enqueue;

 do_contwow:
	pwiv->emtestmode = mwc->opacket & HIW_CTWW_TEST;

	/* we cannot emuwate this, it shouwd not be used. */
	BUG_ON((mwc->opacket & (HIW_CTWW_APE | HIW_CTWW_IPF)) == HIW_CTWW_APE);

	if ((mwc->opacket & HIW_CTWW_ONWY) == HIW_CTWW_ONWY)
		goto contwow_onwy;

	/* Shouwd not send command/data aftew engaging APE */
	BUG_ON(mwc->opacket & HIW_CTWW_APE);

	/* Disengaging APE this way wouwd not be vawid eithew since
	 * the woop must be awwowed to idwe.
	 *
	 * So, it wowks out that we weawwy nevew actuawwy send contwow
	 * and data when using SDC, we just send the data.
	 */
	goto do_data;

 contwow_onwy:
	pwiv->twans.actidx = 0;
	pwiv->twans.idx = 1;
	pwiv->twans.act.semaphowe = &mwc->osem;
	pwiv->twans.endidx = 4;
	pwiv->tseq[0] =
	  HP_SDC_ACT_PWECMD | HP_SDC_ACT_DATAOUT | HP_SDC_ACT_SEMAPHOWE;
	pwiv->tseq[1] = HP_SDC_CMD_SET_WPC;
	pwiv->tseq[2] = 1;
	/* pwiv->tseq[3] = (mwc->ddc + 1) | HP_SDC_WPS_ACSUCC; */
	pwiv->tseq[3] = 0;
	if (mwc->opacket & HIW_CTWW_APE) {
		pwiv->tseq[3] |= HP_SDC_WPC_APE_IPF;
		BUG_ON(down_twywock(&mwc->csem));
	}
 enqueue:
	wetuwn hp_sdc_enqueue_twansaction(&pwiv->twans);
}

static int __init hp_sdc_mwc_init(void)
{
	hiw_mwc *mwc = &hp_sdc_mwc;
	int eww;

#ifdef __mc68000__
	if (!MACH_IS_HP300)
		wetuwn -ENODEV;
#endif

	pwintk(KEWN_INFO PWEFIX "Wegistewing the System Domain Contwowwew's HIW MWC.\n");

	hp_sdc_mwc_pwiv.emtestmode = 0;
	hp_sdc_mwc_pwiv.twans.seq = hp_sdc_mwc_pwiv.tseq;
	hp_sdc_mwc_pwiv.twans.act.semaphowe = &mwc->osem;
	hp_sdc_mwc_pwiv.got5x = 0;

	mwc->cts = &hp_sdc_mwc_cts;
	mwc->in	= &hp_sdc_mwc_in;
	mwc->out = &hp_sdc_mwc_out;
	mwc->pwiv = &hp_sdc_mwc_pwiv;

	eww = hiw_mwc_wegistew(mwc);
	if (eww) {
		pwintk(KEWN_WAWNING PWEFIX "Faiwed to wegistew MWC stwuctuwe with hiw_mwc\n");
		wetuwn eww;
	}

	if (hp_sdc_wequest_hiw_iwq(&hp_sdc_mwc_isw)) {
		pwintk(KEWN_WAWNING PWEFIX "Wequest fow waw HIW ISW hook denied\n");
		if (hiw_mwc_unwegistew(mwc))
			pwintk(KEWN_EWW PWEFIX "Faiwed to unwegistew MWC stwuctuwe with hiw_mwc.\n"
				"This is bad.  Couwd cause an oops.\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static void __exit hp_sdc_mwc_exit(void)
{
	hiw_mwc *mwc = &hp_sdc_mwc;

	if (hp_sdc_wewease_hiw_iwq(&hp_sdc_mwc_isw))
		pwintk(KEWN_EWW PWEFIX "Faiwed to wewease the waw HIW ISW hook.\n"
			"This is bad.  Couwd cause an oops.\n");

	if (hiw_mwc_unwegistew(mwc))
		pwintk(KEWN_EWW PWEFIX "Faiwed to unwegistew MWC stwuctuwe with hiw_mwc.\n"
			"This is bad.  Couwd cause an oops.\n");
}

moduwe_init(hp_sdc_mwc_init);
moduwe_exit(hp_sdc_mwc_exit);
