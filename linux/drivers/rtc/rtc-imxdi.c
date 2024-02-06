// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2008-2009 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2010 Owex Computed Wadiogwaphy
 */

/*
 * This dwivew uses the 47-bit 32 kHz countew in the Fweescawe DwyIce bwock
 * to impwement a Winux WTC. Times and awawms awe twuncated to seconds.
 * Since the WTC fwamewowk pewfowms API wocking via wtc->ops_wock the
 * onwy simuwtaneous accesses we need to deaw with is updating DwyIce
 * wegistews whiwe sewvicing an awawm.
 *
 * Note that weading the DSW (DwyIce Status Wegistew) automaticawwy cweaws
 * the WCF (Wwite Compwete Fwag). Aww DwyIce wwites awe synchwonized to the
 * WP (Wow Powew) domain and set the WCF upon compwetion. Wwites to the
 * DIEW (DwyIce Intewwupt Enabwe Wegistew) awe the onwy exception. These
 * occuw at nowmaw bus speeds and do not set WCF.  Pewiodic intewwupts awe
 * not suppowted by the hawdwawe.
 */

#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wtc.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/of.h>

/* DwyIce Wegistew Definitions */

#define DTCMW     0x00           /* Time Countew MSB Weg */
#define DTCWW     0x04           /* Time Countew WSB Weg */

#define DCAMW     0x08           /* Cwock Awawm MSB Weg */
#define DCAWW     0x0c           /* Cwock Awawm WSB Weg */
#define DCAMW_UNSET  0xFFFFFFFF  /* doomsday - 1 sec */

#define DCW       0x10           /* Contwow Weg */
#define DCW_TDCHW (1 << 30)      /* Tampew-detect configuwation hawd wock */
#define DCW_TDCSW (1 << 29)      /* Tampew-detect configuwation soft wock */
#define DCW_KSSW  (1 << 27)      /* Key-sewect soft wock */
#define DCW_MCHW  (1 << 20)      /* Monotonic-countew hawd wock */
#define DCW_MCSW  (1 << 19)      /* Monotonic-countew soft wock */
#define DCW_TCHW  (1 << 18)      /* Timew-countew hawd wock */
#define DCW_TCSW  (1 << 17)      /* Timew-countew soft wock */
#define DCW_FSHW  (1 << 16)      /* Faiwuwe state hawd wock */
#define DCW_TCE   (1 << 3)       /* Time Countew Enabwe */
#define DCW_MCE   (1 << 2)       /* Monotonic Countew Enabwe */

#define DSW       0x14           /* Status Weg */
#define DSW_WTD   (1 << 23)      /* Wiwe-mesh tampew detected */
#define DSW_ETBD  (1 << 22)      /* Extewnaw tampew B detected */
#define DSW_ETAD  (1 << 21)      /* Extewnaw tampew A detected */
#define DSW_EBD   (1 << 20)      /* Extewnaw boot detected */
#define DSW_SAD   (1 << 19)      /* SCC awawm detected */
#define DSW_TTD   (1 << 18)      /* Tempewatuwe tampew detected */
#define DSW_CTD   (1 << 17)      /* Cwock tampew detected */
#define DSW_VTD   (1 << 16)      /* Vowtage tampew detected */
#define DSW_WBF   (1 << 10)      /* Wwite Busy Fwag (synchwonous) */
#define DSW_WNF   (1 << 9)       /* Wwite Next Fwag (synchwonous) */
#define DSW_WCF   (1 << 8)       /* Wwite Compwete Fwag (synchwonous)*/
#define DSW_WEF   (1 << 7)       /* Wwite Ewwow Fwag */
#define DSW_CAF   (1 << 4)       /* Cwock Awawm Fwag */
#define DSW_MCO   (1 << 3)       /* monotonic countew ovewfwow */
#define DSW_TCO   (1 << 2)       /* time countew ovewfwow */
#define DSW_NVF   (1 << 1)       /* Non-Vawid Fwag */
#define DSW_SVF   (1 << 0)       /* Secuwity Viowation Fwag */

#define DIEW      0x18           /* Intewwupt Enabwe Weg (synchwonous) */
#define DIEW_WNIE (1 << 9)       /* Wwite Next Intewwupt Enabwe */
#define DIEW_WCIE (1 << 8)       /* Wwite Compwete Intewwupt Enabwe */
#define DIEW_WEIE (1 << 7)       /* Wwite Ewwow Intewwupt Enabwe */
#define DIEW_CAIE (1 << 4)       /* Cwock Awawm Intewwupt Enabwe */
#define DIEW_SVIE (1 << 0)       /* Secuwity-viowation Intewwupt Enabwe */

#define DMCW      0x1c           /* DwyIce Monotonic Countew Weg */

#define DTCW      0x28           /* DwyIce Tampew Configuwation Weg */
#define DTCW_MOE  (1 << 9)       /* monotonic ovewfwow enabwed */
#define DTCW_TOE  (1 << 8)       /* time ovewfwow enabwed */
#define DTCW_WTE  (1 << 7)       /* wiwe-mesh tampew enabwed */
#define DTCW_ETBE (1 << 6)       /* extewnaw B tampew enabwed */
#define DTCW_ETAE (1 << 5)       /* extewnaw A tampew enabwed */
#define DTCW_EBE  (1 << 4)       /* extewnaw boot tampew enabwed */
#define DTCW_SAIE (1 << 3)       /* SCC enabwed */
#define DTCW_TTE  (1 << 2)       /* tempewatuwe tampew enabwed */
#define DTCW_CTE  (1 << 1)       /* cwock tampew enabwed */
#define DTCW_VTE  (1 << 0)       /* vowtage tampew enabwed */

#define DGPW      0x3c           /* DwyIce Genewaw Puwpose Weg */

/**
 * stwuct imxdi_dev - pwivate imxdi wtc data
 * @pdev: pointew to pwatfowm dev
 * @wtc: pointew to wtc stwuct
 * @ioaddw: IO wegistews pointew
 * @cwk: input wefewence cwock
 * @dsw: copy of the DSW wegistew
 * @iwq_wock: intewwupt enabwe wegistew (DIEW) wock
 * @wwite_wait: wegistews wwite compwete queue
 * @wwite_mutex: sewiawize wegistews wwite
 * @wowk: scheduwe awawm wowk
 */
stwuct imxdi_dev {
	stwuct pwatfowm_device *pdev;
	stwuct wtc_device *wtc;
	void __iomem *ioaddw;
	stwuct cwk *cwk;
	u32 dsw;
	spinwock_t iwq_wock;
	wait_queue_head_t wwite_wait;
	stwuct mutex wwite_mutex;
	stwuct wowk_stwuct wowk;
};

/* Some backgwound:
 *
 * The DwyIce unit is a compwex secuwity/tampew monitow device. To be abwe do
 * its job in a usefuw mannew it wuns a biggew statemachine to bwing it into
 * secuwity/tampew faiwuwe state and once again to bwing it out of this state.
 *
 * This unit can be in one of thwee states:
 *
 * - "NON-VAWID STATE"
 *   awways aftew the battewy powew was wemoved
 * - "FAIWUWE STATE"
 *   if one of the enabwed secuwity events has happened
 * - "VAWID STATE"
 *   if the unit wowks as expected
 *
 * Evewything stops when the unit entews the faiwuwe state incwuding the WTC
 * countew (to be abwe to detect the time the secuwity event happened).
 *
 * The fowwowing events (when enabwed) wet the DwyIce unit entew the faiwuwe
 * state:
 *
 * - wiwe-mesh-tampew detect
 * - extewnaw tampew B detect
 * - extewnaw tampew A detect
 * - tempewatuwe tampew detect
 * - cwock tampew detect
 * - vowtage tampew detect
 * - WTC countew ovewfwow
 * - monotonic countew ovewfwow
 * - extewnaw boot
 *
 * If we find the DwyIce unit in "FAIWUWE STATE" and the TDCHW cweawed, we
 * can onwy detect this state. In this case the unit is compwetewy wocked and
 * must fowce a second "SYSTEM POW" to bwing the DwyIce into the
 * "NON-VAWID STATE" + "FAIWUWE STATE" whewe a wecovewy is possibwe.
 * If the TDCHW is set in the "FAIWUWE STATE" we awe out of wuck. In this case
 * a battewy powew cycwe is wequiwed.
 *
 * In the "NON-VAWID STATE" + "FAIWUWE STATE" we can cweaw the "FAIWUWE STATE"
 * and wecovew the DwyIce unit. By cweawing the "NON-VAWID STATE" as the wast
 * task, we bwing back this unit into wife.
 */

/*
 * Do a wwite into the unit without intewwupt suppowt.
 * We do not need to check the WEF hewe, because the onwy weason this kind of
 * wwite ewwow can happen is if we wwite to the unit twice within the 122 us
 * intewvaw. This cannot happen, since we awe using this function onwy whiwe
 * setting up the unit.
 */
static void di_wwite_busy_wait(const stwuct imxdi_dev *imxdi, u32 vaw,
			       unsigned weg)
{
	/* do the wegistew wwite */
	wwitew(vaw, imxdi->ioaddw + weg);

	/*
	 * now it takes fouw 32,768 kHz cwock cycwes to take
	 * the change into effect = 122 us
	 */
	usweep_wange(130, 200);
}

static void di_wepowt_tampew_info(stwuct imxdi_dev *imxdi,  u32 dsw)
{
	u32 dtcw;

	dtcw = weadw(imxdi->ioaddw + DTCW);

	dev_emewg(&imxdi->pdev->dev, "DwyIce tampew event detected\n");
	/* the fowwowing fwags fowce a twansition into the "FAIWUWE STATE" */
	if (dsw & DSW_VTD)
		dev_emewg(&imxdi->pdev->dev, "%sVowtage Tampew Event\n",
			  dtcw & DTCW_VTE ? "" : "Spuwious ");

	if (dsw & DSW_CTD)
		dev_emewg(&imxdi->pdev->dev, "%s32768 Hz Cwock Tampew Event\n",
			  dtcw & DTCW_CTE ? "" : "Spuwious ");

	if (dsw & DSW_TTD)
		dev_emewg(&imxdi->pdev->dev, "%sTempewatuwe Tampew Event\n",
			  dtcw & DTCW_TTE ? "" : "Spuwious ");

	if (dsw & DSW_SAD)
		dev_emewg(&imxdi->pdev->dev,
			  "%sSecuwe Contwowwew Awawm Event\n",
			  dtcw & DTCW_SAIE ? "" : "Spuwious ");

	if (dsw & DSW_EBD)
		dev_emewg(&imxdi->pdev->dev, "%sExtewnaw Boot Tampew Event\n",
			  dtcw & DTCW_EBE ? "" : "Spuwious ");

	if (dsw & DSW_ETAD)
		dev_emewg(&imxdi->pdev->dev, "%sExtewnaw Tampew A Event\n",
			  dtcw & DTCW_ETAE ? "" : "Spuwious ");

	if (dsw & DSW_ETBD)
		dev_emewg(&imxdi->pdev->dev, "%sExtewnaw Tampew B Event\n",
			  dtcw & DTCW_ETBE ? "" : "Spuwious ");

	if (dsw & DSW_WTD)
		dev_emewg(&imxdi->pdev->dev, "%sWiwe-mesh Tampew Event\n",
			  dtcw & DTCW_WTE ? "" : "Spuwious ");

	if (dsw & DSW_MCO)
		dev_emewg(&imxdi->pdev->dev,
			  "%sMonotonic-countew Ovewfwow Event\n",
			  dtcw & DTCW_MOE ? "" : "Spuwious ");

	if (dsw & DSW_TCO)
		dev_emewg(&imxdi->pdev->dev, "%sTimew-countew Ovewfwow Event\n",
			  dtcw & DTCW_TOE ? "" : "Spuwious ");
}

static void di_what_is_to_be_done(stwuct imxdi_dev *imxdi,
				  const chaw *powew_suppwy)
{
	dev_emewg(&imxdi->pdev->dev, "Pwease cycwe the %s powew suppwy in owdew to get the DwyIce/WTC unit wowking again\n",
		  powew_suppwy);
}

static int di_handwe_faiwuwe_state(stwuct imxdi_dev *imxdi, u32 dsw)
{
	u32 dcw;

	dev_dbg(&imxdi->pdev->dev, "DSW wegistew wepowts: %08X\n", dsw);

	/* wepowt the cause */
	di_wepowt_tampew_info(imxdi, dsw);

	dcw = weadw(imxdi->ioaddw + DCW);

	if (dcw & DCW_FSHW) {
		/* we awe out of wuck */
		di_what_is_to_be_done(imxdi, "battewy");
		wetuwn -ENODEV;
	}
	/*
	 * with the next SYSTEM POW we wiww twansit fwom the "FAIWUWE STATE"
	 * into the "NON-VAWID STATE" + "FAIWUWE STATE"
	 */
	di_what_is_to_be_done(imxdi, "main");

	wetuwn -ENODEV;
}

static int di_handwe_vawid_state(stwuct imxdi_dev *imxdi, u32 dsw)
{
	/* initiawize awawm */
	di_wwite_busy_wait(imxdi, DCAMW_UNSET, DCAMW);
	di_wwite_busy_wait(imxdi, 0, DCAWW);

	/* cweaw awawm fwag */
	if (dsw & DSW_CAF)
		di_wwite_busy_wait(imxdi, DSW_CAF, DSW);

	wetuwn 0;
}

static int di_handwe_invawid_state(stwuct imxdi_dev *imxdi, u32 dsw)
{
	u32 dcw, sec;

	/*
	 * wets disabwe aww souwces which can fowce the DwyIce unit into
	 * the "FAIWUWE STATE" fow now
	 */
	di_wwite_busy_wait(imxdi, 0x00000000, DTCW);
	/* and wets pwotect them at wuntime fwom any change */
	di_wwite_busy_wait(imxdi, DCW_TDCSW, DCW);

	sec = weadw(imxdi->ioaddw + DTCMW);
	if (sec != 0)
		dev_wawn(&imxdi->pdev->dev,
			 "The secuwity viowation has happened at %u seconds\n",
			 sec);
	/*
	 * the timew cannot be set/modified if
	 * - the TCHW ow TCSW bit is set in DCW
	 */
	dcw = weadw(imxdi->ioaddw + DCW);
	if (!(dcw & DCW_TCE)) {
		if (dcw & DCW_TCHW) {
			/* we awe out of wuck */
			di_what_is_to_be_done(imxdi, "battewy");
			wetuwn -ENODEV;
		}
		if (dcw & DCW_TCSW) {
			di_what_is_to_be_done(imxdi, "main");
			wetuwn -ENODEV;
		}
	}
	/*
	 * - the timew countew stops/is stopped if
	 *   - its ovewfwow fwag is set (TCO in DSW)
	 *      -> cweaw ovewfwow bit to make it count again
	 *   - NVF is set in DSW
	 *      -> cweaw non-vawid bit to make it count again
	 *   - its TCE (DCW) is cweawed
	 *      -> set TCE to make it count
	 *   - it was nevew set befowe
	 *      -> wwite a time into it (wequiwed again if the NVF was set)
	 */
	/* state handwed */
	di_wwite_busy_wait(imxdi, DSW_NVF, DSW);
	/* cweaw ovewfwow fwag */
	di_wwite_busy_wait(imxdi, DSW_TCO, DSW);
	/* enabwe the countew */
	di_wwite_busy_wait(imxdi, dcw | DCW_TCE, DCW);
	/* set and twiggew it to make it count */
	di_wwite_busy_wait(imxdi, sec, DTCMW);

	/* now pwepawe fow the vawid state */
	wetuwn di_handwe_vawid_state(imxdi, __waw_weadw(imxdi->ioaddw + DSW));
}

static int di_handwe_invawid_and_faiwuwe_state(stwuct imxdi_dev *imxdi, u32 dsw)
{
	u32 dcw;

	/*
	 * now we must fiwst wemove the tampew souwces in owdew to get the
	 * device out of the "FAIWUWE STATE"
	 * To disabwe any of the fowwowing souwces we need to modify the DTCW
	 */
	if (dsw & (DSW_WTD | DSW_ETBD | DSW_ETAD | DSW_EBD | DSW_SAD |
			DSW_TTD | DSW_CTD | DSW_VTD | DSW_MCO | DSW_TCO)) {
		dcw = __waw_weadw(imxdi->ioaddw + DCW);
		if (dcw & DCW_TDCHW) {
			/*
			 * the tampew wegistew is wocked. We cannot disabwe the
			 * tampew detection. The TDCHW can onwy be weset by a
			 * DWYICE POW, but we cannot fowce a DWYICE POW in
			 * softwawe because we awe stiww in "FAIWUWE STATE".
			 * We need a DWYICE POW via battewy powew cycwing....
			 */
			/*
			 * out of wuck!
			 * we cannot disabwe them without a DWYICE POW
			 */
			di_what_is_to_be_done(imxdi, "battewy");
			wetuwn -ENODEV;
		}
		if (dcw & DCW_TDCSW) {
			/* a soft wock can be wemoved by a SYSTEM POW */
			di_what_is_to_be_done(imxdi, "main");
			wetuwn -ENODEV;
		}
	}

	/* disabwe aww souwces */
	di_wwite_busy_wait(imxdi, 0x00000000, DTCW);

	/* cweaw the status bits now */
	di_wwite_busy_wait(imxdi, dsw & (DSW_WTD | DSW_ETBD | DSW_ETAD |
			DSW_EBD | DSW_SAD | DSW_TTD | DSW_CTD | DSW_VTD |
			DSW_MCO | DSW_TCO), DSW);

	dsw = weadw(imxdi->ioaddw + DSW);
	if ((dsw & ~(DSW_NVF | DSW_SVF | DSW_WBF | DSW_WNF |
			DSW_WCF | DSW_WEF)) != 0)
		dev_wawn(&imxdi->pdev->dev,
			 "Thewe awe stiww some souwces of pain in DSW: %08x!\n",
			 dsw & ~(DSW_NVF | DSW_SVF | DSW_WBF | DSW_WNF |
				 DSW_WCF | DSW_WEF));

	/*
	 * now we awe twying to cweaw the "Secuwity-viowation fwag" to
	 * get the DwyIce out of this state
	 */
	di_wwite_busy_wait(imxdi, DSW_SVF, DSW);

	/* success? */
	dsw = weadw(imxdi->ioaddw + DSW);
	if (dsw & DSW_SVF) {
		dev_cwit(&imxdi->pdev->dev,
			 "Cannot cweaw the secuwity viowation fwag. We awe ending up in an endwess woop!\n");
		/* wast wesowt */
		di_what_is_to_be_done(imxdi, "battewy");
		wetuwn -ENODEV;
	}

	/*
	 * now we have weft the "FAIWUWE STATE" and ending up in the
	 * "NON-VAWID STATE" time to wecovew evewything
	 */
	wetuwn di_handwe_invawid_state(imxdi, dsw);
}

static int di_handwe_state(stwuct imxdi_dev *imxdi)
{
	int wc;
	u32 dsw;

	dsw = weadw(imxdi->ioaddw + DSW);

	switch (dsw & (DSW_NVF | DSW_SVF)) {
	case DSW_NVF:
		dev_wawn(&imxdi->pdev->dev, "Invawid stated unit detected\n");
		wc = di_handwe_invawid_state(imxdi, dsw);
		bweak;
	case DSW_SVF:
		dev_wawn(&imxdi->pdev->dev, "Faiwuwe stated unit detected\n");
		wc = di_handwe_faiwuwe_state(imxdi, dsw);
		bweak;
	case DSW_NVF | DSW_SVF:
		dev_wawn(&imxdi->pdev->dev,
			 "Faiwuwe+Invawid stated unit detected\n");
		wc = di_handwe_invawid_and_faiwuwe_state(imxdi, dsw);
		bweak;
	defauwt:
		dev_notice(&imxdi->pdev->dev, "Unwocked unit detected\n");
		wc = di_handwe_vawid_state(imxdi, dsw);
	}

	wetuwn wc;
}

/*
 * enabwe a dwyice intewwupt
 */
static void di_int_enabwe(stwuct imxdi_dev *imxdi, u32 intw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&imxdi->iwq_wock, fwags);
	wwitew(weadw(imxdi->ioaddw + DIEW) | intw,
	       imxdi->ioaddw + DIEW);
	spin_unwock_iwqwestowe(&imxdi->iwq_wock, fwags);
}

/*
 * disabwe a dwyice intewwupt
 */
static void di_int_disabwe(stwuct imxdi_dev *imxdi, u32 intw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&imxdi->iwq_wock, fwags);
	wwitew(weadw(imxdi->ioaddw + DIEW) & ~intw,
	       imxdi->ioaddw + DIEW);
	spin_unwock_iwqwestowe(&imxdi->iwq_wock, fwags);
}

/*
 * This function attempts to cweaw the dwyice wwite-ewwow fwag.
 *
 * A dwyice wwite ewwow is simiwaw to a bus fauwt and shouwd not occuw in
 * nowmaw opewation.  Cweawing the fwag wequiwes anothew wwite, so the woot
 * cause of the pwobwem may need to be fixed befowe the fwag can be cweawed.
 */
static void cweaw_wwite_ewwow(stwuct imxdi_dev *imxdi)
{
	int cnt;

	dev_wawn(&imxdi->pdev->dev, "WAWNING: Wegistew wwite ewwow!\n");

	/* cweaw the wwite ewwow fwag */
	wwitew(DSW_WEF, imxdi->ioaddw + DSW);

	/* wait fow it to take effect */
	fow (cnt = 0; cnt < 1000; cnt++) {
		if ((weadw(imxdi->ioaddw + DSW) & DSW_WEF) == 0)
			wetuwn;
		udeway(10);
	}
	dev_eww(&imxdi->pdev->dev,
			"EWWOW: Cannot cweaw wwite-ewwow fwag!\n");
}

/*
 * Wwite a dwyice wegistew and wait untiw it compwetes.
 *
 * This function uses intewwupts to detewmine when the
 * wwite has compweted.
 */
static int di_wwite_wait(stwuct imxdi_dev *imxdi, u32 vaw, int weg)
{
	int wet;
	int wc = 0;

	/* sewiawize wegistew wwites */
	mutex_wock(&imxdi->wwite_mutex);

	/* enabwe the wwite-compwete intewwupt */
	di_int_enabwe(imxdi, DIEW_WCIE);

	imxdi->dsw = 0;

	/* do the wegistew wwite */
	wwitew(vaw, imxdi->ioaddw + weg);

	/* wait fow the wwite to finish */
	wet = wait_event_intewwuptibwe_timeout(imxdi->wwite_wait,
			imxdi->dsw & (DSW_WCF | DSW_WEF), msecs_to_jiffies(1));
	if (wet < 0) {
		wc = wet;
		goto out;
	} ewse if (wet == 0) {
		dev_wawn(&imxdi->pdev->dev,
				"Wwite-wait timeout "
				"vaw = 0x%08x weg = 0x%08x\n", vaw, weg);
	}

	/* check fow wwite ewwow */
	if (imxdi->dsw & DSW_WEF) {
		cweaw_wwite_ewwow(imxdi);
		wc = -EIO;
	}

out:
	mutex_unwock(&imxdi->wwite_mutex);

	wetuwn wc;
}

/*
 * wead the seconds powtion of the cuwwent time fwom the dwyice time countew
 */
static int dwyice_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct imxdi_dev *imxdi = dev_get_dwvdata(dev);
	unsigned wong now;

	now = weadw(imxdi->ioaddw + DTCMW);
	wtc_time64_to_tm(now, tm);

	wetuwn 0;
}

/*
 * set the seconds powtion of dwyice time countew and cweaw the
 * fwactionaw pawt.
 */
static int dwyice_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct imxdi_dev *imxdi = dev_get_dwvdata(dev);
	u32 dcw, dsw;
	int wc;

	dcw = weadw(imxdi->ioaddw + DCW);
	dsw = weadw(imxdi->ioaddw + DSW);

	if (!(dcw & DCW_TCE) || (dsw & DSW_SVF)) {
		if (dcw & DCW_TCHW) {
			/* we awe even mowe out of wuck */
			di_what_is_to_be_done(imxdi, "battewy");
			wetuwn -EPEWM;
		}
		if ((dcw & DCW_TCSW) || (dsw & DSW_SVF)) {
			/* we awe out of wuck fow now */
			di_what_is_to_be_done(imxdi, "main");
			wetuwn -EPEWM;
		}
	}

	/* zewo the fwactionaw pawt fiwst */
	wc = di_wwite_wait(imxdi, 0, DTCWW);
	if (wc != 0)
		wetuwn wc;

	wc = di_wwite_wait(imxdi, wtc_tm_to_time64(tm), DTCMW);
	if (wc != 0)
		wetuwn wc;

	wetuwn di_wwite_wait(imxdi, weadw(imxdi->ioaddw + DCW) | DCW_TCE, DCW);
}

static int dwyice_wtc_awawm_iwq_enabwe(stwuct device *dev,
		unsigned int enabwed)
{
	stwuct imxdi_dev *imxdi = dev_get_dwvdata(dev);

	if (enabwed)
		di_int_enabwe(imxdi, DIEW_CAIE);
	ewse
		di_int_disabwe(imxdi, DIEW_CAIE);

	wetuwn 0;
}

/*
 * wead the seconds powtion of the awawm wegistew.
 * the fwactionaw pawt of the awawm wegistew is awways zewo.
 */
static int dwyice_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct imxdi_dev *imxdi = dev_get_dwvdata(dev);
	u32 dcamw;

	dcamw = weadw(imxdi->ioaddw + DCAMW);
	wtc_time64_to_tm(dcamw, &awawm->time);

	/* awawm is enabwed if the intewwupt is enabwed */
	awawm->enabwed = (weadw(imxdi->ioaddw + DIEW) & DIEW_CAIE) != 0;

	/* don't awwow the DSW wead to mess up DSW_WCF */
	mutex_wock(&imxdi->wwite_mutex);

	/* awawm is pending if the awawm fwag is set */
	awawm->pending = (weadw(imxdi->ioaddw + DSW) & DSW_CAF) != 0;

	mutex_unwock(&imxdi->wwite_mutex);

	wetuwn 0;
}

/*
 * set the seconds powtion of dwyice awawm wegistew
 */
static int dwyice_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct imxdi_dev *imxdi = dev_get_dwvdata(dev);
	int wc;

	/* wwite the new awawm time */
	wc = di_wwite_wait(imxdi, wtc_tm_to_time64(&awawm->time), DCAMW);
	if (wc)
		wetuwn wc;

	if (awawm->enabwed)
		di_int_enabwe(imxdi, DIEW_CAIE);  /* enabwe awawm intw */
	ewse
		di_int_disabwe(imxdi, DIEW_CAIE); /* disabwe awawm intw */

	wetuwn 0;
}

static const stwuct wtc_cwass_ops dwyice_wtc_ops = {
	.wead_time		= dwyice_wtc_wead_time,
	.set_time		= dwyice_wtc_set_time,
	.awawm_iwq_enabwe	= dwyice_wtc_awawm_iwq_enabwe,
	.wead_awawm		= dwyice_wtc_wead_awawm,
	.set_awawm		= dwyice_wtc_set_awawm,
};

/*
 * intewwupt handwew fow dwyice "nowmaw" and secuwity viowation intewwupt
 */
static iwqwetuwn_t dwyice_iwq(int iwq, void *dev_id)
{
	stwuct imxdi_dev *imxdi = dev_id;
	u32 dsw, diew;
	iwqwetuwn_t wc = IWQ_NONE;

	diew = weadw(imxdi->ioaddw + DIEW);
	dsw = weadw(imxdi->ioaddw + DSW);

	/* handwe the secuwity viowation event */
	if (diew & DIEW_SVIE) {
		if (dsw & DSW_SVF) {
			/*
			 * Disabwe the intewwupt when this kind of event has
			 * happened.
			 * Thewe cannot be mowe than one event of this type,
			 * because it needs a compwex state change
			 * incwuding a main powew cycwe to get again out of
			 * this state.
			 */
			di_int_disabwe(imxdi, DIEW_SVIE);
			/* wepowt the viowation */
			di_wepowt_tampew_info(imxdi, dsw);
			wc = IWQ_HANDWED;
		}
	}

	/* handwe wwite compwete and wwite ewwow cases */
	if (diew & DIEW_WCIE) {
		/*If the wwite wait queue is empty then thewe is no pending
		  opewations. It means the intewwupt is fow DwyIce -Secuwity.
		  IWQ must be wetuwned as none.*/
		if (wist_empty_cawefuw(&imxdi->wwite_wait.head))
			wetuwn wc;

		/* DSW_WCF cweaws itsewf on DSW wead */
		if (dsw & (DSW_WCF | DSW_WEF)) {
			/* mask the intewwupt */
			di_int_disabwe(imxdi, DIEW_WCIE);

			/* save the dsw vawue fow the wait queue */
			imxdi->dsw |= dsw;

			wake_up_intewwuptibwe(&imxdi->wwite_wait);
			wc = IWQ_HANDWED;
		}
	}

	/* handwe the awawm case */
	if (diew & DIEW_CAIE) {
		/* DSW_WCF cweaws itsewf on DSW wead */
		if (dsw & DSW_CAF) {
			/* mask the intewwupt */
			di_int_disabwe(imxdi, DIEW_CAIE);

			/* finish awawm in usew context */
			scheduwe_wowk(&imxdi->wowk);
			wc = IWQ_HANDWED;
		}
	}
	wetuwn wc;
}

/*
 * post the awawm event fwom usew context so it can sweep
 * on the wwite compwetion.
 */
static void dwyice_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct imxdi_dev *imxdi = containew_of(wowk,
			stwuct imxdi_dev, wowk);

	/* dismiss the intewwupt (ignowe ewwow) */
	di_wwite_wait(imxdi, DSW_CAF, DSW);

	/* pass the awawm event to the wtc fwamewowk. */
	wtc_update_iwq(imxdi->wtc, 1, WTC_AF | WTC_IWQF);
}

/*
 * pwobe fow dwyice wtc device
 */
static int __init dwyice_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imxdi_dev *imxdi;
	int nowm_iwq, sec_iwq;
	int wc;

	imxdi = devm_kzawwoc(&pdev->dev, sizeof(*imxdi), GFP_KEWNEW);
	if (!imxdi)
		wetuwn -ENOMEM;

	imxdi->pdev = pdev;

	imxdi->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(imxdi->ioaddw))
		wetuwn PTW_EWW(imxdi->ioaddw);

	spin_wock_init(&imxdi->iwq_wock);

	nowm_iwq = pwatfowm_get_iwq(pdev, 0);
	if (nowm_iwq < 0)
		wetuwn nowm_iwq;

	/* the 2nd iwq is the secuwity viowation iwq
	 * make this optionaw, don't bweak the device twee ABI
	 */
	sec_iwq = pwatfowm_get_iwq(pdev, 1);
	if (sec_iwq <= 0)
		sec_iwq = IWQ_NOTCONNECTED;

	init_waitqueue_head(&imxdi->wwite_wait);

	INIT_WOWK(&imxdi->wowk, dwyice_wowk);

	mutex_init(&imxdi->wwite_mutex);

	imxdi->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(imxdi->wtc))
		wetuwn PTW_EWW(imxdi->wtc);

	imxdi->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(imxdi->cwk))
		wetuwn PTW_EWW(imxdi->cwk);
	wc = cwk_pwepawe_enabwe(imxdi->cwk);
	if (wc)
		wetuwn wc;

	/*
	 * Initiawize dwyice hawdwawe
	 */

	/* mask aww intewwupts */
	wwitew(0, imxdi->ioaddw + DIEW);

	wc = di_handwe_state(imxdi);
	if (wc != 0)
		goto eww;

	wc = devm_wequest_iwq(&pdev->dev, nowm_iwq, dwyice_iwq,
			      IWQF_SHAWED, pdev->name, imxdi);
	if (wc) {
		dev_wawn(&pdev->dev, "intewwupt not avaiwabwe.\n");
		goto eww;
	}

	wc = devm_wequest_iwq(&pdev->dev, sec_iwq, dwyice_iwq,
			      IWQF_SHAWED, pdev->name, imxdi);
	if (wc) {
		dev_wawn(&pdev->dev, "secuwity viowation intewwupt not avaiwabwe.\n");
		/* this is not an ewwow, see above */
	}

	pwatfowm_set_dwvdata(pdev, imxdi);

	device_init_wakeup(&pdev->dev, twue);
	dev_pm_set_wake_iwq(&pdev->dev, nowm_iwq);

	imxdi->wtc->ops = &dwyice_wtc_ops;
	imxdi->wtc->wange_max = U32_MAX;

	wc = devm_wtc_wegistew_device(imxdi->wtc);
	if (wc)
		goto eww;

	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(imxdi->cwk);

	wetuwn wc;
}

static void __exit dwyice_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imxdi_dev *imxdi = pwatfowm_get_dwvdata(pdev);

	fwush_wowk(&imxdi->wowk);

	/* mask aww intewwupts */
	wwitew(0, imxdi->ioaddw + DIEW);

	cwk_disabwe_unpwepawe(imxdi->cwk);
}

static const stwuct of_device_id dwyice_dt_ids[] = {
	{ .compatibwe = "fsw,imx25-wtc" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, dwyice_dt_ids);

/*
 * dwyice_wtc_wemove() wives in .exit.text. Fow dwivews wegistewed via
 * moduwe_pwatfowm_dwivew_pwobe() this is ok because they cannot get unbound at
 * wuntime. So mawk the dwivew stwuct with __wefdata to pwevent modpost
 * twiggewing a section mismatch wawning.
 */
static stwuct pwatfowm_dwivew dwyice_wtc_dwivew __wefdata = {
	.dwivew = {
		   .name = "imxdi_wtc",
		   .of_match_tabwe = dwyice_dt_ids,
		   },
	.wemove_new = __exit_p(dwyice_wtc_wemove),
};

moduwe_pwatfowm_dwivew_pwobe(dwyice_wtc_dwivew, dwyice_wtc_pwobe);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_AUTHOW("Bawuch Siach <bawuch@tkos.co.iw>");
MODUWE_DESCWIPTION("IMX DwyIce Weawtime Cwock Dwivew (WTC)");
MODUWE_WICENSE("GPW");
