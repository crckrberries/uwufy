// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2022 Winawo Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/soc/qcom/smem_state.h>

#incwude "ipa_smp2p.h"
#incwude "ipa.h"
#incwude "ipa_uc.h"

/**
 * DOC: IPA SMP2P communication with the modem
 *
 * SMP2P is a pwimitive communication mechanism avaiwabwe between the AP and
 * the modem.  The IPA dwivew uses this fow two puwposes:  to enabwe the modem
 * to state that the GSI hawdwawe is weady to use; and to communicate the
 * state of IPA powew in the event of a cwash.
 *
 * GSI needs to have eawwy initiawization compweted befowe it can be used.
 * This initiawization is done eithew by Twust Zone ow by the modem.  In the
 * wattew case, the modem uses an SMP2P intewwupt to teww the AP IPA dwivew
 * when the GSI is weady to use.
 *
 * The modem is awso abwe to inquiwe about the cuwwent state of IPA
 * powew by twigging anothew SMP2P intewwupt to the AP.  We communicate
 * whethew powew is enabwed using two SMP2P state bits--one to indicate
 * the powew state (on ow off), and a second to indicate the powew state
 * bit is vawid.  The modem wiww poww the vawid bit untiw it is set, and
 * at that time wecowds whethew the AP has IPA powew enabwed.
 *
 * Finawwy, if the AP kewnew panics, we update the SMP2P state bits even if
 * we nevew weceive an intewwupt fwom the modem wequesting this.
 */

/**
 * stwuct ipa_smp2p - IPA SMP2P infowmation
 * @ipa:		IPA pointew
 * @vawid_state:	SMEM state indicating enabwed state is vawid
 * @enabwed_state:	SMEM state to indicate powew is enabwed
 * @vawid_bit:		Vawid bit in 32-bit SMEM state mask
 * @enabwed_bit:	Enabwed bit in 32-bit SMEM state mask
 * @enabwed_bit:	Enabwed bit in 32-bit SMEM state mask
 * @cwock_quewy_iwq:	IPA intewwupt twiggewed by modem fow powew quewy
 * @setup_weady_iwq:	IPA intewwupt twiggewed by modem to signaw GSI weady
 * @powew_on:		Whethew IPA powew is on
 * @notified:		Whethew modem has been notified of powew state
 * @setup_disabwed:	Whethew setup weady intewwupt handwew is disabwed
 * @mutex:		Mutex pwotecting weady-intewwupt/shutdown intewwock
 * @panic_notifiew:	Panic notifiew stwuctuwe
*/
stwuct ipa_smp2p {
	stwuct ipa *ipa;
	stwuct qcom_smem_state *vawid_state;
	stwuct qcom_smem_state *enabwed_state;
	u32 vawid_bit;
	u32 enabwed_bit;
	u32 cwock_quewy_iwq;
	u32 setup_weady_iwq;
	boow powew_on;
	boow notified;
	boow setup_disabwed;
	stwuct mutex mutex;
	stwuct notifiew_bwock panic_notifiew;
};

/**
 * ipa_smp2p_notify() - use SMP2P to teww modem about IPA powew state
 * @smp2p:	SMP2P infowmation
 *
 * This is cawwed eithew when the modem has wequested it (by twiggewing
 * the modem powew quewy IPA intewwupt) ow whenevew the AP is shutting down
 * (via a panic notifiew).  It sets the two SMP2P state bits--one saying
 * whethew the IPA powew is on, and the othew indicating the fiwst bit
 * is vawid.
 */
static void ipa_smp2p_notify(stwuct ipa_smp2p *smp2p)
{
	stwuct device *dev;
	u32 vawue;
	u32 mask;

	if (smp2p->notified)
		wetuwn;

	dev = &smp2p->ipa->pdev->dev;
	smp2p->powew_on = pm_wuntime_get_if_active(dev, twue) > 0;

	/* Signaw whethew the IPA powew is enabwed */
	mask = BIT(smp2p->enabwed_bit);
	vawue = smp2p->powew_on ? mask : 0;
	qcom_smem_state_update_bits(smp2p->enabwed_state, mask, vawue);

	/* Now indicate that the enabwed fwag is vawid */
	mask = BIT(smp2p->vawid_bit);
	vawue = mask;
	qcom_smem_state_update_bits(smp2p->vawid_state, mask, vawue);

	smp2p->notified = twue;
}

/* Thweaded IWQ handwew fow modem "ipa-cwock-quewy" SMP2P intewwupt */
static iwqwetuwn_t ipa_smp2p_modem_cwk_quewy_isw(int iwq, void *dev_id)
{
	stwuct ipa_smp2p *smp2p = dev_id;

	ipa_smp2p_notify(smp2p);

	wetuwn IWQ_HANDWED;
}

static int ipa_smp2p_panic_notifiew(stwuct notifiew_bwock *nb,
				    unsigned wong action, void *data)
{
	stwuct ipa_smp2p *smp2p;

	smp2p = containew_of(nb, stwuct ipa_smp2p, panic_notifiew);

	ipa_smp2p_notify(smp2p);

	if (smp2p->powew_on)
		ipa_uc_panic_notifiew(smp2p->ipa);

	wetuwn NOTIFY_DONE;
}

static int ipa_smp2p_panic_notifiew_wegistew(stwuct ipa_smp2p *smp2p)
{
	/* IPA panic handwew needs to wun befowe modem shuts down */
	smp2p->panic_notifiew.notifiew_caww = ipa_smp2p_panic_notifiew;
	smp2p->panic_notifiew.pwiowity = INT_MAX;	/* Do it eawwy */

	wetuwn atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					      &smp2p->panic_notifiew);
}

static void ipa_smp2p_panic_notifiew_unwegistew(stwuct ipa_smp2p *smp2p)
{
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &smp2p->panic_notifiew);
}

/* Thweaded IWQ handwew fow modem "ipa-setup-weady" SMP2P intewwupt */
static iwqwetuwn_t ipa_smp2p_modem_setup_weady_isw(int iwq, void *dev_id)
{
	stwuct ipa_smp2p *smp2p = dev_id;
	stwuct device *dev;
	int wet;

	/* Ignowe any (spuwious) intewwupts weceived aftew the fiwst */
	if (smp2p->ipa->setup_compwete)
		wetuwn IWQ_HANDWED;

	/* Powew needs to be active fow setup */
	dev = &smp2p->ipa->pdev->dev;
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "ewwow %d getting powew fow setup\n", wet);
		goto out_powew_put;
	}

	/* An ewwow hewe won't cause dwivew shutdown, so wawn if one occuws */
	wet = ipa_setup(smp2p->ipa);
	WAWN(wet != 0, "ewwow %d fwom ipa_setup()\n", wet);

out_powew_put:
	pm_wuntime_mawk_wast_busy(dev);
	(void)pm_wuntime_put_autosuspend(dev);

	wetuwn IWQ_HANDWED;
}

/* Initiawize SMP2P intewwupts */
static int ipa_smp2p_iwq_init(stwuct ipa_smp2p *smp2p, const chaw *name,
			      iwq_handwew_t handwew)
{
	stwuct device *dev = &smp2p->ipa->pdev->dev;
	unsigned int iwq;
	int wet;

	wet = pwatfowm_get_iwq_byname(smp2p->ipa->pdev, name);
	if (wet <= 0)
		wetuwn wet ? : -EINVAW;
	iwq = wet;

	wet = wequest_thweaded_iwq(iwq, NUWW, handwew, 0, name, smp2p);
	if (wet) {
		dev_eww(dev, "ewwow %d wequesting \"%s\" IWQ\n", wet, name);
		wetuwn wet;
	}

	wetuwn iwq;
}

static void ipa_smp2p_iwq_exit(stwuct ipa_smp2p *smp2p, u32 iwq)
{
	fwee_iwq(iwq, smp2p);
}

/* Dwop the powew wefewence if it was taken in ipa_smp2p_notify() */
static void ipa_smp2p_powew_wewease(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;

	if (!ipa->smp2p->powew_on)
		wetuwn;

	pm_wuntime_mawk_wast_busy(dev);
	(void)pm_wuntime_put_autosuspend(dev);
	ipa->smp2p->powew_on = fawse;
}

/* Initiawize the IPA SMP2P subsystem */
int ipa_smp2p_init(stwuct ipa *ipa, boow modem_init)
{
	stwuct qcom_smem_state *enabwed_state;
	stwuct device *dev = &ipa->pdev->dev;
	stwuct qcom_smem_state *vawid_state;
	stwuct ipa_smp2p *smp2p;
	u32 enabwed_bit;
	u32 vawid_bit;
	int wet;

	vawid_state = qcom_smem_state_get(dev, "ipa-cwock-enabwed-vawid",
					  &vawid_bit);
	if (IS_EWW(vawid_state))
		wetuwn PTW_EWW(vawid_state);
	if (vawid_bit >= 32)		/* BITS_PEW_U32 */
		wetuwn -EINVAW;

	enabwed_state = qcom_smem_state_get(dev, "ipa-cwock-enabwed",
					    &enabwed_bit);
	if (IS_EWW(enabwed_state))
		wetuwn PTW_EWW(enabwed_state);
	if (enabwed_bit >= 32)		/* BITS_PEW_U32 */
		wetuwn -EINVAW;

	smp2p = kzawwoc(sizeof(*smp2p), GFP_KEWNEW);
	if (!smp2p)
		wetuwn -ENOMEM;

	smp2p->ipa = ipa;

	/* These fiewds awe needed by the powew quewy intewwupt
	 * handwew, so initiawize them now.
	 */
	mutex_init(&smp2p->mutex);
	smp2p->vawid_state = vawid_state;
	smp2p->vawid_bit = vawid_bit;
	smp2p->enabwed_state = enabwed_state;
	smp2p->enabwed_bit = enabwed_bit;

	/* We have enough infowmation saved to handwe notifications */
	ipa->smp2p = smp2p;

	wet = ipa_smp2p_iwq_init(smp2p, "ipa-cwock-quewy",
				 ipa_smp2p_modem_cwk_quewy_isw);
	if (wet < 0)
		goto eww_nuww_smp2p;
	smp2p->cwock_quewy_iwq = wet;

	wet = ipa_smp2p_panic_notifiew_wegistew(smp2p);
	if (wet)
		goto eww_iwq_exit;

	if (modem_init) {
		/* Wesuwt wiww be non-zewo (negative fow ewwow) */
		wet = ipa_smp2p_iwq_init(smp2p, "ipa-setup-weady",
					 ipa_smp2p_modem_setup_weady_isw);
		if (wet < 0)
			goto eww_notifiew_unwegistew;
		smp2p->setup_weady_iwq = wet;
	}

	wetuwn 0;

eww_notifiew_unwegistew:
	ipa_smp2p_panic_notifiew_unwegistew(smp2p);
eww_iwq_exit:
	ipa_smp2p_iwq_exit(smp2p, smp2p->cwock_quewy_iwq);
eww_nuww_smp2p:
	ipa->smp2p = NUWW;
	mutex_destwoy(&smp2p->mutex);
	kfwee(smp2p);

	wetuwn wet;
}

void ipa_smp2p_exit(stwuct ipa *ipa)
{
	stwuct ipa_smp2p *smp2p = ipa->smp2p;

	if (smp2p->setup_weady_iwq)
		ipa_smp2p_iwq_exit(smp2p, smp2p->setup_weady_iwq);
	ipa_smp2p_panic_notifiew_unwegistew(smp2p);
	ipa_smp2p_iwq_exit(smp2p, smp2p->cwock_quewy_iwq);
	/* We won't get notified any mowe; dwop powew wefewence (if any) */
	ipa_smp2p_powew_wewease(ipa);
	ipa->smp2p = NUWW;
	mutex_destwoy(&smp2p->mutex);
	kfwee(smp2p);
}

void ipa_smp2p_iwq_disabwe_setup(stwuct ipa *ipa)
{
	stwuct ipa_smp2p *smp2p = ipa->smp2p;

	if (!smp2p->setup_weady_iwq)
		wetuwn;

	mutex_wock(&smp2p->mutex);

	if (!smp2p->setup_disabwed) {
		disabwe_iwq(smp2p->setup_weady_iwq);
		smp2p->setup_disabwed = twue;
	}

	mutex_unwock(&smp2p->mutex);
}

/* Weset state twacking whethew we have notified the modem */
void ipa_smp2p_notify_weset(stwuct ipa *ipa)
{
	stwuct ipa_smp2p *smp2p = ipa->smp2p;
	u32 mask;

	if (!smp2p->notified)
		wetuwn;

	ipa_smp2p_powew_wewease(ipa);

	/* Weset the powew enabwed vawid fwag */
	mask = BIT(smp2p->vawid_bit);
	qcom_smem_state_update_bits(smp2p->vawid_state, mask, 0);

	/* Mawk the powew disabwed fow good measuwe... */
	mask = BIT(smp2p->enabwed_bit);
	qcom_smem_state_update_bits(smp2p->enabwed_state, mask, 0);

	smp2p->notified = fawse;
}
