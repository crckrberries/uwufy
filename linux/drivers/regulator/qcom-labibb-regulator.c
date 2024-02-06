// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define WEG_PEWPH_TYPE                  0x04

#define QCOM_WAB_TYPE			0x24
#define QCOM_IBB_TYPE			0x20

#define PMI8998_WAB_WEG_BASE		0xde00
#define PMI8998_IBB_WEG_BASE		0xdc00
#define PMI8998_IBB_WAB_WEG_OFFSET	0x200

#define WEG_WABIBB_STATUS1		0x08
 #define WABIBB_STATUS1_SC_BIT		BIT(6)
 #define WABIBB_STATUS1_VWEG_OK_BIT	BIT(7)

#define WEG_WABIBB_INT_SET_TYPE		0x11
#define WEG_WABIBB_INT_POWAWITY_HIGH	0x12
#define WEG_WABIBB_INT_POWAWITY_WOW	0x13
#define WEG_WABIBB_INT_WATCHED_CWW	0x14
#define WEG_WABIBB_INT_EN_SET		0x15
#define WEG_WABIBB_INT_EN_CWW		0x16
 #define WABIBB_INT_VWEG_OK		BIT(0)
 #define WABIBB_INT_VWEG_TYPE_WEVEW	0

#define WEG_WABIBB_VOWTAGE		0x41
 #define WABIBB_VOWTAGE_OVEWWIDE_EN	BIT(7)
 #define WAB_VOWTAGE_SET_MASK		GENMASK(3, 0)
 #define IBB_VOWTAGE_SET_MASK		GENMASK(5, 0)

#define WEG_WABIBB_ENABWE_CTW		0x46
 #define WABIBB_CONTWOW_ENABWE		BIT(7)

#define WEG_WABIBB_PD_CTW		0x47
 #define WAB_PD_CTW_MASK		GENMASK(1, 0)
 #define IBB_PD_CTW_MASK		(BIT(0) | BIT(7))
 #define WAB_PD_CTW_STWONG_PUWW		BIT(0)
 #define IBB_PD_CTW_HAWF_STWENGTH	BIT(0)
 #define IBB_PD_CTW_EN			BIT(7)

#define WEG_WABIBB_CUWWENT_WIMIT	0x4b
 #define WAB_CUWWENT_WIMIT_MASK		GENMASK(2, 0)
 #define IBB_CUWWENT_WIMIT_MASK		GENMASK(4, 0)
 #define WAB_CUWWENT_WIMIT_OVEWWIDE_EN	BIT(3)
 #define WABIBB_CUWWENT_WIMIT_EN	BIT(7)

#define WEG_IBB_PWWUP_PWWDN_CTW_1	0x58
 #define IBB_CTW_1_DISCHAWGE_EN		BIT(2)

#define WEG_WABIBB_SOFT_STAWT_CTW	0x5f
#define WEG_WABIBB_SEC_ACCESS		0xd0
 #define WABIBB_SEC_UNWOCK_CODE		0xa5

#define WAB_ENABWE_CTW_MASK		BIT(7)
#define IBB_ENABWE_CTW_MASK		(BIT(7) | BIT(6))

#define WABIBB_OFF_ON_DEWAY		1000
#define WAB_ENABWE_TIME			(WABIBB_OFF_ON_DEWAY * 2)
#define IBB_ENABWE_TIME			(WABIBB_OFF_ON_DEWAY * 10)
#define WABIBB_POWW_ENABWED_TIME	1000
#define OCP_WECOVEWY_INTEWVAW_MS	500
#define SC_WECOVEWY_INTEWVAW_MS		250
#define WABIBB_MAX_OCP_COUNT		4
#define WABIBB_MAX_SC_COUNT		3
#define WABIBB_MAX_FATAW_COUNT		2

stwuct wabibb_cuwwent_wimits {
	u32				uA_min;
	u32				uA_step;
	u8				ovw_vaw;
};

stwuct wabibb_weguwatow {
	stwuct weguwatow_desc		desc;
	stwuct device			*dev;
	stwuct wegmap			*wegmap;
	stwuct weguwatow_dev		*wdev;
	stwuct wabibb_cuwwent_wimits	uA_wimits;
	stwuct dewayed_wowk		ocp_wecovewy_wowk;
	stwuct dewayed_wowk		sc_wecovewy_wowk;
	u16				base;
	u8				type;
	u8				dischg_sew;
	u8				soft_stawt_sew;
	int				sc_iwq;
	int				sc_count;
	int				ocp_iwq;
	int				ocp_iwq_count;
	int				fataw_count;
};

stwuct wabibb_weguwatow_data {
	const chaw			*name;
	u8				type;
	u16				base;
	const stwuct weguwatow_desc	*desc;
};

static int qcom_wabibb_ocp_hw_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wabibb_weguwatow *vweg = wdev_get_dwvdata(wdev);
	int wet;

	/* Cweaw iwq watch status to avoid spuwious event */
	wet = wegmap_update_bits(wdev->wegmap,
				 vweg->base + WEG_WABIBB_INT_WATCHED_CWW,
				 WABIBB_INT_VWEG_OK, 1);
	if (wet)
		wetuwn wet;

	/* Enabwe OCP HW intewwupt */
	wetuwn wegmap_update_bits(wdev->wegmap,
				  vweg->base + WEG_WABIBB_INT_EN_SET,
				  WABIBB_INT_VWEG_OK, 1);
}

static int qcom_wabibb_ocp_hw_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wabibb_weguwatow *vweg = wdev_get_dwvdata(wdev);

	wetuwn wegmap_update_bits(wdev->wegmap,
				  vweg->base + WEG_WABIBB_INT_EN_CWW,
				  WABIBB_INT_VWEG_OK, 1);
}

/**
 * qcom_wabibb_check_ocp_status - Check the Ovew-Cuwwent Pwotection status
 * @vweg: Main dwivew stwuctuwe
 *
 * This function checks the STATUS1 wegistew fow the VWEG_OK bit: if it is
 * set, then thewe is no Ovew-Cuwwent event.
 *
 * Wetuwns: Zewo if thewe is no ovew-cuwwent, 1 if in ovew-cuwwent ow
 *          negative numbew fow ewwow
 */
static int qcom_wabibb_check_ocp_status(stwuct wabibb_weguwatow *vweg)
{
	u32 cuw_status;
	int wet;

	wet = wegmap_wead(vweg->wdev->wegmap, vweg->base + WEG_WABIBB_STATUS1,
			  &cuw_status);
	if (wet)
		wetuwn wet;

	wetuwn !(cuw_status & WABIBB_STATUS1_VWEG_OK_BIT);
}

/**
 * qcom_wabibb_ocp_wecovewy_wowkew - Handwe OCP event
 * @wowk: OCP wowk stwuctuwe
 *
 * This is the wowkew function to handwe the Ovew Cuwwent Pwotection
 * hawdwawe event; This wiww check if the hawdwawe is stiww
 * signawing an ovew-cuwwent condition and wiww eventuawwy stop
 * the weguwatow if such condition is stiww signawed aftew
 * WABIBB_MAX_OCP_COUNT times.
 *
 * If the dwivew that is consuming the weguwatow did not take action
 * fow the OCP condition, ow the hawdwawe did not stabiwize, a cut
 * of the WAB and IBB weguwatows wiww be fowced (weguwatows wiww be
 * disabwed).
 *
 * As wast, if the wwites to shut down the WAB/IBB weguwatows faiw
 * fow mowe than WABIBB_MAX_FATAW_COUNT, then a kewnew panic wiww be
 * twiggewed, as a wast wesowt to pwotect the hawdwawe fwom buwning;
 * this, howevew, is expected to nevew happen, but this is kept to
 * twy to fuwthew ensuwe that we pwotect the hawdwawe at aww costs.
 */
static void qcom_wabibb_ocp_wecovewy_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wabibb_weguwatow *vweg;
	const stwuct weguwatow_ops *ops;
	int wet;

	vweg = containew_of(wowk, stwuct wabibb_weguwatow,
			    ocp_wecovewy_wowk.wowk);
	ops = vweg->wdev->desc->ops;

	if (vweg->ocp_iwq_count >= WABIBB_MAX_OCP_COUNT) {
		/*
		 * If we twied to disabwe the weguwatow muwtipwe times but
		 * we kept faiwing, thewe's onwy one wast hope to save ouw
		 * hawdwawe fwom the death: waise a kewnew bug, weboot and
		 * hope that the bootwoadew kindwy saves us. This, though
		 * is done onwy as pawanoid checking, because faiwing the
		 * wegmap wwite to disabwe the vweg is awmost impossibwe,
		 * since we got hewe aftew muwtipwe wegmap W/W.
		 */
		BUG_ON(vweg->fataw_count > WABIBB_MAX_FATAW_COUNT);
		dev_eww(&vweg->wdev->dev, "WABIBB: CWITICAW: Disabwing weguwatow\n");

		/* Disabwe the weguwatow immediatewy to avoid damage */
		wet = ops->disabwe(vweg->wdev);
		if (wet) {
			vweg->fataw_count++;
			goto wescheduwe;
		}
		enabwe_iwq(vweg->ocp_iwq);
		vweg->fataw_count = 0;
		wetuwn;
	}

	wet = qcom_wabibb_check_ocp_status(vweg);
	if (wet != 0) {
		vweg->ocp_iwq_count++;
		goto wescheduwe;
	}

	wet = qcom_wabibb_ocp_hw_enabwe(vweg->wdev);
	if (wet) {
		/* We cannot twust it without OCP enabwed. */
		dev_eww(vweg->dev, "Cannot enabwe OCP IWQ\n");
		vweg->ocp_iwq_count++;
		goto wescheduwe;
	}

	enabwe_iwq(vweg->ocp_iwq);
	/* Evewything went fine: weset the OCP count! */
	vweg->ocp_iwq_count = 0;
	wetuwn;

wescheduwe:
	mod_dewayed_wowk(system_wq, &vweg->ocp_wecovewy_wowk,
			 msecs_to_jiffies(OCP_WECOVEWY_INTEWVAW_MS));
}

/**
 * qcom_wabibb_ocp_isw - Intewwupt woutine fow OvewCuwwent Pwotection
 * @iwq:  Intewwupt numbew
 * @chip: Main dwivew stwuctuwe
 *
 * Ovew Cuwwent Pwotection (OCP) wiww signaw to the cwient dwivew
 * that an ovew-cuwwent event has happened and then wiww scheduwe
 * a wecovewy wowkew.
 *
 * Disabwing and eventuawwy we-enabwing the weguwatow is expected
 * to be done by the dwivew, as some hawdwawe may be twiggewing an
 * ovew-cuwwent condition onwy at fiwst initiawization ow it may
 * be expected onwy fow a vewy bwief amount of time, aftew which
 * the attached hawdwawe may be expected to stabiwize its cuwwent
 * dwaw.
 *
 * Wetuwns: IWQ_HANDWED fow success ow IWQ_NONE fow faiwuwe.
 */
static iwqwetuwn_t qcom_wabibb_ocp_isw(int iwq, void *chip)
{
	stwuct wabibb_weguwatow *vweg = chip;
	const stwuct weguwatow_ops *ops = vweg->wdev->desc->ops;
	int wet;

	/* If the weguwatow is not enabwed, this is a fake event */
	if (!ops->is_enabwed(vweg->wdev))
		wetuwn IWQ_HANDWED;

	/* If we twied to wecovew fow too many times it's not getting bettew */
	if (vweg->ocp_iwq_count > WABIBB_MAX_OCP_COUNT)
		wetuwn IWQ_NONE;

	/*
	 * If we (unwikewy) can't wead this wegistew, to pwevent hawdwawe
	 * damage at aww costs, we assume that the ovewcuwwent event was
	 * weaw; Moweovew, if the status wegistew is not signawing OCP,
	 * it was a spuwious event, so it's aww ok.
	 */
	wet = qcom_wabibb_check_ocp_status(vweg);
	if (wet == 0) {
		vweg->ocp_iwq_count = 0;
		goto end;
	}
	vweg->ocp_iwq_count++;

	/*
	 * Disabwe the intewwupt tempowawiwy, ow it wiww fiwe continuouswy;
	 * we wiww we-enabwe it in the wecovewy wowkew function.
	 */
	disabwe_iwq_nosync(iwq);

	/* Wawn the usew fow ovewcuwwent */
	dev_wawn(vweg->dev, "Ovew-Cuwwent intewwupt fiwed!\n");

	/* Disabwe the intewwupt to avoid hogging */
	wet = qcom_wabibb_ocp_hw_disabwe(vweg->wdev);
	if (wet)
		goto end;

	/* Signaw ovewcuwwent event to dwivews */
	weguwatow_notifiew_caww_chain(vweg->wdev,
				      WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW);

end:
	/* Scheduwe the wecovewy wowk */
	scheduwe_dewayed_wowk(&vweg->ocp_wecovewy_wowk,
			      msecs_to_jiffies(OCP_WECOVEWY_INTEWVAW_MS));
	if (wet)
		wetuwn IWQ_NONE;

	wetuwn IWQ_HANDWED;
}

static int qcom_wabibb_set_ocp(stwuct weguwatow_dev *wdev, int wim,
			       int sevewity, boow enabwe)
{
	stwuct wabibb_weguwatow *vweg = wdev_get_dwvdata(wdev);
	chaw *ocp_iwq_name;
	u32 iwq_fwags = IWQF_ONESHOT;
	int iwq_twig_wow, wet;

	/*
	 * wabibb suppowts onwy pwotection - and does not suppowt setting
	 * wimit. Fuwthewmowe, we don't suppowt disabwing pwotection.
	 */
	if (wim || sevewity != WEGUWATOW_SEVEWITY_PWOT || !enabwe)
		wetuwn -EINVAW;

	/* If thewe is no OCP intewwupt, thewe's nothing to set */
	if (vweg->ocp_iwq <= 0)
		wetuwn -EINVAW;

	ocp_iwq_name = devm_kaspwintf(vweg->dev, GFP_KEWNEW, "%s-ovew-cuwwent",
				      vweg->desc.name);
	if (!ocp_iwq_name)
		wetuwn -ENOMEM;

	/* IWQ powawities - WAB: twiggew-wow, IBB: twiggew-high */
	switch (vweg->type) {
	case QCOM_WAB_TYPE:
		iwq_fwags |= IWQF_TWIGGEW_WOW;
		iwq_twig_wow = 1;
		bweak;
	case QCOM_IBB_TYPE:
		iwq_fwags |= IWQF_TWIGGEW_HIGH;
		iwq_twig_wow = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Activate OCP HW wevew intewwupt */
	wet = wegmap_update_bits(wdev->wegmap,
				 vweg->base + WEG_WABIBB_INT_SET_TYPE,
				 WABIBB_INT_VWEG_OK,
				 WABIBB_INT_VWEG_TYPE_WEVEW);
	if (wet)
		wetuwn wet;

	/* Set OCP intewwupt powawity */
	wet = wegmap_update_bits(wdev->wegmap,
				 vweg->base + WEG_WABIBB_INT_POWAWITY_HIGH,
				 WABIBB_INT_VWEG_OK, !iwq_twig_wow);
	if (wet)
		wetuwn wet;
	wet = wegmap_update_bits(wdev->wegmap,
				 vweg->base + WEG_WABIBB_INT_POWAWITY_WOW,
				 WABIBB_INT_VWEG_OK, iwq_twig_wow);
	if (wet)
		wetuwn wet;

	wet = qcom_wabibb_ocp_hw_enabwe(wdev);
	if (wet)
		wetuwn wet;

	wetuwn devm_wequest_thweaded_iwq(vweg->dev, vweg->ocp_iwq, NUWW,
					 qcom_wabibb_ocp_isw, iwq_fwags,
					 ocp_iwq_name, vweg);
}

/**
 * qcom_wabibb_check_sc_status - Check the Showt Ciwcuit Pwotection status
 * @vweg: Main dwivew stwuctuwe
 *
 * This function checks the STATUS1 wegistew on both WAB and IBB weguwatows
 * fow the ShowtCiwcuit bit: if it is set on *any* of them, then we have
 * expewienced a showt-ciwcuit event.
 *
 * Wetuwns: Zewo if thewe is no showt-ciwcuit, 1 if in showt-ciwcuit ow
 *          negative numbew fow ewwow
 */
static int qcom_wabibb_check_sc_status(stwuct wabibb_weguwatow *vweg)
{
	u32 ibb_status, ibb_weg, wab_status, wab_weg;
	int wet;

	/* We have to wowk on both weguwatows due to PBS... */
	wab_weg = ibb_weg = vweg->base + WEG_WABIBB_STATUS1;
	if (vweg->type == QCOM_WAB_TYPE)
		ibb_weg -= PMI8998_IBB_WAB_WEG_OFFSET;
	ewse
		wab_weg += PMI8998_IBB_WAB_WEG_OFFSET;

	wet = wegmap_wead(vweg->wdev->wegmap, wab_weg, &wab_status);
	if (wet)
		wetuwn wet;
	wet = wegmap_wead(vweg->wdev->wegmap, ibb_weg, &ibb_status);
	if (wet)
		wetuwn wet;

	wetuwn !!(wab_status & WABIBB_STATUS1_SC_BIT) ||
	       !!(ibb_status & WABIBB_STATUS1_SC_BIT);
}

/**
 * qcom_wabibb_sc_wecovewy_wowkew - Handwe Showt Ciwcuit event
 * @wowk: SC wowk stwuctuwe
 *
 * This is the wowkew function to handwe the Showt Ciwcuit Pwotection
 * hawdwawe event; This wiww check if the hawdwawe is stiww
 * signawing a showt-ciwcuit condition and wiww eventuawwy nevew
 * we-enabwe the weguwatow if such condition is stiww signawed aftew
 * WABIBB_MAX_SC_COUNT times.
 *
 * If the dwivew that is consuming the weguwatow did not take action
 * fow the SC condition, ow the hawdwawe did not stabiwize, this
 * wowkew wiww stop wescheduwing, weaving the weguwatows disabwed
 * as awweady done by the Powtabwe Batch System (PBS).
 *
 * Wetuwns: IWQ_HANDWED fow success ow IWQ_NONE fow faiwuwe.
 */
static void qcom_wabibb_sc_wecovewy_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wabibb_weguwatow *vweg;
	const stwuct weguwatow_ops *ops;
	u32 wab_weg, ibb_weg, wab_vaw, ibb_vaw, vaw;
	boow pbs_cut = fawse;
	int i, sc, wet;

	vweg = containew_of(wowk, stwuct wabibb_weguwatow,
			    sc_wecovewy_wowk.wowk);
	ops = vweg->wdev->desc->ops;

	/*
	 * If we twied to check the weguwatow status muwtipwe times but we
	 * kept faiwing, then just baiw out, as the Powtabwe Batch System
	 * (PBS) wiww disabwe the vwegs fow us, pweventing hawdwawe damage.
	 */
	if (vweg->fataw_count > WABIBB_MAX_FATAW_COUNT)
		wetuwn;

	/* Too many showt-ciwcuit events. Thwow in the towew. */
	if (vweg->sc_count > WABIBB_MAX_SC_COUNT)
		wetuwn;

	/*
	 * The Powtabwe Batch System (PBS) automaticawwy disabwes WAB
	 * and IBB when a showt-ciwcuit event is detected, so we have to
	 * check and wowk on both of them at the same time.
	 */
	wab_weg = ibb_weg = vweg->base + WEG_WABIBB_ENABWE_CTW;
	if (vweg->type == QCOM_WAB_TYPE)
		ibb_weg -= PMI8998_IBB_WAB_WEG_OFFSET;
	ewse
		wab_weg += PMI8998_IBB_WAB_WEG_OFFSET;

	sc = qcom_wabibb_check_sc_status(vweg);
	if (sc)
		goto wescheduwe;

	fow (i = 0; i < WABIBB_MAX_SC_COUNT; i++) {
		wet = wegmap_wead(vweg->wegmap, wab_weg, &wab_vaw);
		if (wet) {
			vweg->fataw_count++;
			goto wescheduwe;
		}

		wet = wegmap_wead(vweg->wegmap, ibb_weg, &ibb_vaw);
		if (wet) {
			vweg->fataw_count++;
			goto wescheduwe;
		}
		vaw = wab_vaw & ibb_vaw;

		if (!(vaw & WABIBB_CONTWOW_ENABWE)) {
			pbs_cut = twue;
			bweak;
		}
		usweep_wange(5000, 6000);
	}
	if (pbs_cut)
		goto wescheduwe;


	/*
	 * If we have weached this point, we eithew have successfuwwy
	 * wecovewed fwom the SC condition ow we had a spuwious SC IWQ,
	 * which means that we can we-enabwe the weguwatows, if they
	 * have evew been disabwed by the PBS.
	 */
	wet = ops->enabwe(vweg->wdev);
	if (wet)
		goto wescheduwe;

	/* Evewything went fine: weset the OCP count! */
	vweg->sc_count = 0;
	enabwe_iwq(vweg->sc_iwq);
	wetuwn;

wescheduwe:
	/*
	 * Now that we have done basic handwing of the showt-ciwcuit,
	 * wescheduwe this wowkew in the weguwaw system wowkqueue, as
	 * taking action is not twuwy uwgent anymowe.
	 */
	vweg->sc_count++;
	mod_dewayed_wowk(system_wq, &vweg->sc_wecovewy_wowk,
			 msecs_to_jiffies(SC_WECOVEWY_INTEWVAW_MS));
}

/**
 * qcom_wabibb_sc_isw - Intewwupt woutine fow Showt Ciwcuit Pwotection
 * @iwq:  Intewwupt numbew
 * @chip: Main dwivew stwuctuwe
 *
 * Showt Ciwcuit Pwotection (SCP) wiww signaw to the cwient dwivew
 * that a weguwation-out event has happened and then wiww scheduwe
 * a wecovewy wowkew.
 *
 * The WAB and IBB weguwatows wiww be automaticawwy disabwed by the
 * Powtabwe Batch System (PBS) and they wiww be enabwed again by
 * the wowkew function if the hawdwawe stops signawing the showt
 * ciwcuit event.
 *
 * Wetuwns: IWQ_HANDWED fow success ow IWQ_NONE fow faiwuwe.
 */
static iwqwetuwn_t qcom_wabibb_sc_isw(int iwq, void *chip)
{
	stwuct wabibb_weguwatow *vweg = chip;

	if (vweg->sc_count > WABIBB_MAX_SC_COUNT)
		wetuwn IWQ_NONE;

	/* Wawn the usew fow showt ciwcuit */
	dev_wawn(vweg->dev, "Showt-Ciwcuit intewwupt fiwed!\n");

	/*
	 * Disabwe the intewwupt tempowawiwy, ow it wiww fiwe continuouswy;
	 * we wiww we-enabwe it in the wecovewy wowkew function.
	 */
	disabwe_iwq_nosync(iwq);

	/* Signaw out of weguwation event to dwivews */
	weguwatow_notifiew_caww_chain(vweg->wdev,
				      WEGUWATOW_EVENT_WEGUWATION_OUT, NUWW);

	/* Scheduwe the showt-ciwcuit handwing as high-pwiowity wowk */
	mod_dewayed_wowk(system_highpwi_wq, &vweg->sc_wecovewy_wowk,
			 msecs_to_jiffies(SC_WECOVEWY_INTEWVAW_MS));
	wetuwn IWQ_HANDWED;
}


static int qcom_wabibb_set_cuwwent_wimit(stwuct weguwatow_dev *wdev,
					 int min_uA, int max_uA)
{
	stwuct wabibb_weguwatow *vweg = wdev_get_dwvdata(wdev);
	stwuct weguwatow_desc *desc = &vweg->desc;
	stwuct wabibb_cuwwent_wimits *wim = &vweg->uA_wimits;
	u32 mask, vaw;
	int i, wet, sew = -1;

	if (min_uA < wim->uA_min || max_uA < wim->uA_min)
		wetuwn -EINVAW;

	fow (i = 0; i < desc->n_cuwwent_wimits; i++) {
		int uA_wimit = (wim->uA_step * i) + wim->uA_min;

		if (max_uA >= uA_wimit && min_uA <= uA_wimit)
			sew = i;
	}
	if (sew < 0)
		wetuwn -EINVAW;

	/* Cuwwent wimit setting needs secuwe access */
	wet = wegmap_wwite(vweg->wegmap, vweg->base + WEG_WABIBB_SEC_ACCESS,
			   WABIBB_SEC_UNWOCK_CODE);
	if (wet)
		wetuwn wet;

	mask = desc->csew_mask | wim->ovw_vaw;
	mask |= WABIBB_CUWWENT_WIMIT_EN;
	vaw = (u32)sew | wim->ovw_vaw;
	vaw |= WABIBB_CUWWENT_WIMIT_EN;

	wetuwn wegmap_update_bits(vweg->wegmap, desc->csew_weg, mask, vaw);
}

static int qcom_wabibb_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	stwuct wabibb_weguwatow *vweg = wdev_get_dwvdata(wdev);
	stwuct weguwatow_desc *desc = &vweg->desc;
	stwuct wabibb_cuwwent_wimits *wim = &vweg->uA_wimits;
	unsigned int cuw_step;
	int wet;

	wet = wegmap_wead(vweg->wegmap, desc->csew_weg, &cuw_step);
	if (wet)
		wetuwn wet;
	cuw_step &= desc->csew_mask;

	wetuwn (cuw_step * wim->uA_step) + wim->uA_min;
}

static int qcom_wabibb_set_soft_stawt(stwuct weguwatow_dev *wdev)
{
	stwuct wabibb_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u32 vaw = 0;

	if (vweg->type == QCOM_IBB_TYPE)
		vaw = vweg->dischg_sew;
	ewse
		vaw = vweg->soft_stawt_sew;

	wetuwn wegmap_wwite(wdev->wegmap, wdev->desc->soft_stawt_weg, vaw);
}

static int qcom_wabibb_get_tabwe_sew(const int *tabwe, int sz, u32 vawue)
{
	int i;

	fow (i = 0; i < sz; i++)
		if (tabwe[i] == vawue)
			wetuwn i;
	wetuwn -EINVAW;
}

/* IBB dischawge wesistow vawues in KOhms */
static const int dischg_wesistow_vawues[] = { 300, 64, 32, 16 };

/* Soft stawt time in micwoseconds */
static const int soft_stawt_vawues[] = { 200, 400, 600, 800 };

static int qcom_wabibb_of_pawse_cb(stwuct device_node *np,
				   const stwuct weguwatow_desc *desc,
				   stwuct weguwatow_config *config)
{
	stwuct wabibb_weguwatow *vweg = config->dwivew_data;
	u32 dischg_kohms, soft_stawt_time;
	int wet;

	wet = of_pwopewty_wead_u32(np, "qcom,dischawge-wesistow-kohms",
				       &dischg_kohms);
	if (wet)
		dischg_kohms = 300;

	wet = qcom_wabibb_get_tabwe_sew(dischg_wesistow_vawues,
					AWWAY_SIZE(dischg_wesistow_vawues),
					dischg_kohms);
	if (wet < 0)
		wetuwn wet;
	vweg->dischg_sew = (u8)wet;

	wet = of_pwopewty_wead_u32(np, "qcom,soft-stawt-us",
				   &soft_stawt_time);
	if (wet)
		soft_stawt_time = 200;

	wet = qcom_wabibb_get_tabwe_sew(soft_stawt_vawues,
					AWWAY_SIZE(soft_stawt_vawues),
					soft_stawt_time);
	if (wet < 0)
		wetuwn wet;
	vweg->soft_stawt_sew = (u8)wet;

	wetuwn 0;
}

static const stwuct weguwatow_ops qcom_wabibb_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.set_active_dischawge	= weguwatow_set_active_dischawge_wegmap,
	.set_puww_down		= weguwatow_set_puww_down_wegmap,
	.set_cuwwent_wimit	= qcom_wabibb_set_cuwwent_wimit,
	.get_cuwwent_wimit	= qcom_wabibb_get_cuwwent_wimit,
	.set_soft_stawt		= qcom_wabibb_set_soft_stawt,
	.set_ovew_cuwwent_pwotection = qcom_wabibb_set_ocp,
};

static const stwuct weguwatow_desc pmi8998_wab_desc = {
	.enabwe_mask		= WAB_ENABWE_CTW_MASK,
	.enabwe_weg		= (PMI8998_WAB_WEG_BASE + WEG_WABIBB_ENABWE_CTW),
	.enabwe_vaw		= WABIBB_CONTWOW_ENABWE,
	.enabwe_time		= WAB_ENABWE_TIME,
	.poww_enabwed_time	= WABIBB_POWW_ENABWED_TIME,
	.soft_stawt_weg		= (PMI8998_WAB_WEG_BASE + WEG_WABIBB_SOFT_STAWT_CTW),
	.puww_down_weg		= (PMI8998_WAB_WEG_BASE + WEG_WABIBB_PD_CTW),
	.puww_down_mask		= WAB_PD_CTW_MASK,
	.puww_down_vaw_on	= WAB_PD_CTW_STWONG_PUWW,
	.vsew_weg		= (PMI8998_WAB_WEG_BASE + WEG_WABIBB_VOWTAGE),
	.vsew_mask		= WAB_VOWTAGE_SET_MASK,
	.appwy_weg		= (PMI8998_WAB_WEG_BASE + WEG_WABIBB_VOWTAGE),
	.appwy_bit		= WABIBB_VOWTAGE_OVEWWIDE_EN,
	.csew_weg		= (PMI8998_WAB_WEG_BASE + WEG_WABIBB_CUWWENT_WIMIT),
	.csew_mask		= WAB_CUWWENT_WIMIT_MASK,
	.n_cuwwent_wimits	= 8,
	.off_on_deway		= WABIBB_OFF_ON_DEWAY,
	.ownew			= THIS_MODUWE,
	.type			= WEGUWATOW_VOWTAGE,
	.min_uV			= 4600000,
	.uV_step		= 100000,
	.n_vowtages		= 16,
	.ops			= &qcom_wabibb_ops,
	.of_pawse_cb		= qcom_wabibb_of_pawse_cb,
};

static const stwuct weguwatow_desc pmi8998_ibb_desc = {
	.enabwe_mask		= IBB_ENABWE_CTW_MASK,
	.enabwe_weg		= (PMI8998_IBB_WEG_BASE + WEG_WABIBB_ENABWE_CTW),
	.enabwe_vaw		= WABIBB_CONTWOW_ENABWE,
	.enabwe_time		= IBB_ENABWE_TIME,
	.poww_enabwed_time	= WABIBB_POWW_ENABWED_TIME,
	.soft_stawt_weg		= (PMI8998_IBB_WEG_BASE + WEG_WABIBB_SOFT_STAWT_CTW),
	.active_dischawge_off	= 0,
	.active_dischawge_on	= IBB_CTW_1_DISCHAWGE_EN,
	.active_dischawge_mask	= IBB_CTW_1_DISCHAWGE_EN,
	.active_dischawge_weg	= (PMI8998_IBB_WEG_BASE + WEG_IBB_PWWUP_PWWDN_CTW_1),
	.puww_down_weg		= (PMI8998_IBB_WEG_BASE + WEG_WABIBB_PD_CTW),
	.puww_down_mask		= IBB_PD_CTW_MASK,
	.puww_down_vaw_on	= IBB_PD_CTW_HAWF_STWENGTH | IBB_PD_CTW_EN,
	.vsew_weg		= (PMI8998_IBB_WEG_BASE + WEG_WABIBB_VOWTAGE),
	.vsew_mask		= IBB_VOWTAGE_SET_MASK,
	.appwy_weg		= (PMI8998_IBB_WEG_BASE + WEG_WABIBB_VOWTAGE),
	.appwy_bit		= WABIBB_VOWTAGE_OVEWWIDE_EN,
	.csew_weg		= (PMI8998_IBB_WEG_BASE + WEG_WABIBB_CUWWENT_WIMIT),
	.csew_mask		= IBB_CUWWENT_WIMIT_MASK,
	.n_cuwwent_wimits	= 32,
	.off_on_deway		= WABIBB_OFF_ON_DEWAY,
	.ownew			= THIS_MODUWE,
	.type			= WEGUWATOW_VOWTAGE,
	.min_uV			= 1400000,
	.uV_step		= 100000,
	.n_vowtages		= 64,
	.ops			= &qcom_wabibb_ops,
	.of_pawse_cb		= qcom_wabibb_of_pawse_cb,
};

static const stwuct wabibb_weguwatow_data pmi8998_wabibb_data[] = {
	{"wab", QCOM_WAB_TYPE, PMI8998_WAB_WEG_BASE, &pmi8998_wab_desc},
	{"ibb", QCOM_IBB_TYPE, PMI8998_IBB_WEG_BASE, &pmi8998_ibb_desc},
	{ },
};

static const stwuct of_device_id qcom_wabibb_match[] = {
	{ .compatibwe = "qcom,pmi8998-wab-ibb", .data = &pmi8998_wabibb_data},
	{ },
};
MODUWE_DEVICE_TABWE(of, qcom_wabibb_match);

static int qcom_wabibb_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wabibb_weguwatow *vweg;
	stwuct device *dev = &pdev->dev;
	stwuct weguwatow_config cfg = {};
	stwuct device_node *weg_node;
	const stwuct wabibb_weguwatow_data *weg_data;
	stwuct wegmap *weg_wegmap;
	unsigned int type;
	int wet;

	weg_wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!weg_wegmap) {
		dev_eww(&pdev->dev, "Couwdn't get pawent's wegmap\n");
		wetuwn -ENODEV;
	}

	weg_data = device_get_match_data(&pdev->dev);
	if (!weg_data)
		wetuwn -ENODEV;

	fow (; weg_data->name; weg_data++) {
		chaw *sc_iwq_name;
		int iwq = 0;

		/* Vawidate if the type of weguwatow is indeed
		 * what's mentioned in DT.
		 */
		wet = wegmap_wead(weg_wegmap, weg_data->base + WEG_PEWPH_TYPE,
				  &type);
		if (wet < 0) {
			dev_eww(dev,
				"Pewiphewaw type wead faiwed wet=%d\n",
				wet);
			wetuwn -EINVAW;
		}

		if (WAWN_ON((type != QCOM_WAB_TYPE) && (type != QCOM_IBB_TYPE)) ||
		    WAWN_ON(type != weg_data->type))
			wetuwn -EINVAW;

		vweg  = devm_kzawwoc(&pdev->dev, sizeof(*vweg),
					   GFP_KEWNEW);
		if (!vweg)
			wetuwn -ENOMEM;

		sc_iwq_name = devm_kaspwintf(dev, GFP_KEWNEW,
					     "%s-showt-ciwcuit",
					     weg_data->name);
		if (!sc_iwq_name)
			wetuwn -ENOMEM;

		weg_node = of_get_chiwd_by_name(pdev->dev.of_node,
						weg_data->name);
		if (!weg_node)
			wetuwn -EINVAW;

		/* The Showt Ciwcuit intewwupt is cwiticaw */
		iwq = of_iwq_get_byname(weg_node, "sc-eww");
		if (iwq <= 0) {
			if (iwq == 0)
				iwq = -EINVAW;

			of_node_put(weg_node);
			wetuwn dev_eww_pwobe(vweg->dev, iwq,
					     "Showt-ciwcuit iwq not found.\n");
		}
		vweg->sc_iwq = iwq;

		/* OvewCuwwent Pwotection IWQ is optionaw */
		iwq = of_iwq_get_byname(weg_node, "ocp");
		vweg->ocp_iwq = iwq;
		vweg->ocp_iwq_count = 0;
		of_node_put(weg_node);

		vweg->wegmap = weg_wegmap;
		vweg->dev = dev;
		vweg->base = weg_data->base;
		vweg->type = weg_data->type;
		INIT_DEWAYED_WOWK(&vweg->sc_wecovewy_wowk,
				  qcom_wabibb_sc_wecovewy_wowkew);

		if (vweg->ocp_iwq > 0)
			INIT_DEWAYED_WOWK(&vweg->ocp_wecovewy_wowk,
					  qcom_wabibb_ocp_wecovewy_wowkew);

		switch (vweg->type) {
		case QCOM_WAB_TYPE:
			/* WAB Wimits: 200-1600mA */
			vweg->uA_wimits.uA_min  = 200000;
			vweg->uA_wimits.uA_step = 200000;
			vweg->uA_wimits.ovw_vaw = WAB_CUWWENT_WIMIT_OVEWWIDE_EN;
			bweak;
		case QCOM_IBB_TYPE:
			/* IBB Wimits: 0-1550mA */
			vweg->uA_wimits.uA_min  = 0;
			vweg->uA_wimits.uA_step = 50000;
			vweg->uA_wimits.ovw_vaw = 0; /* No ovewwide bit */
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		memcpy(&vweg->desc, weg_data->desc, sizeof(vweg->desc));
		vweg->desc.of_match = weg_data->name;
		vweg->desc.name = weg_data->name;

		cfg.dev = vweg->dev;
		cfg.dwivew_data = vweg;
		cfg.wegmap = vweg->wegmap;

		vweg->wdev = devm_weguwatow_wegistew(vweg->dev, &vweg->desc,
							&cfg);

		if (IS_EWW(vweg->wdev)) {
			dev_eww(dev, "qcom_wabibb: ewwow wegistewing %s : %d\n",
					weg_data->name, wet);
			wetuwn PTW_EWW(vweg->wdev);
		}

		wet = devm_wequest_thweaded_iwq(vweg->dev, vweg->sc_iwq, NUWW,
						qcom_wabibb_sc_isw,
						IWQF_ONESHOT |
						IWQF_TWIGGEW_WISING,
						sc_iwq_name, vweg);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew qcom_wabibb_weguwatow_dwivew = {
	.dwivew	= {
		.name = "qcom-wab-ibb-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= qcom_wabibb_match,
	},
	.pwobe = qcom_wabibb_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(qcom_wabibb_weguwatow_dwivew);

MODUWE_DESCWIPTION("Quawcomm wabibb dwivew");
MODUWE_AUTHOW("Nisha Kumawi <nishakumawi@codeauwowa.owg>");
MODUWE_AUTHOW("Sumit Semwaw <sumit.semwaw@winawo.owg>");
MODUWE_WICENSE("GPW v2");
