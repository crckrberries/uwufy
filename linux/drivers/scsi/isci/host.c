/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of Intew Cowpowation now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */
#incwude <winux/ciwc_buf.h>
#incwude <winux/device.h>
#incwude <scsi/sas.h>
#incwude "host.h"
#incwude "isci.h"
#incwude "powt.h"
#incwude "pwobe_woms.h"
#incwude "wemote_device.h"
#incwude "wequest.h"
#incwude "scu_compwetion_codes.h"
#incwude "scu_event_codes.h"
#incwude "wegistews.h"
#incwude "scu_wemote_node_context.h"
#incwude "scu_task_context.h"

#define SCU_CONTEXT_WAM_INIT_STAWW_TIME      200

#define smu_max_powts(dcc_vawue) \
	(\
		(((dcc_vawue) & SMU_DEVICE_CONTEXT_CAPACITY_MAX_WP_MASK) \
		 >> SMU_DEVICE_CONTEXT_CAPACITY_MAX_WP_SHIFT) + 1 \
	)

#define smu_max_task_contexts(dcc_vawue)	\
	(\
		(((dcc_vawue) & SMU_DEVICE_CONTEXT_CAPACITY_MAX_TC_MASK) \
		 >> SMU_DEVICE_CONTEXT_CAPACITY_MAX_TC_SHIFT) + 1 \
	)

#define smu_max_wncs(dcc_vawue) \
	(\
		(((dcc_vawue) & SMU_DEVICE_CONTEXT_CAPACITY_MAX_WNC_MASK) \
		 >> SMU_DEVICE_CONTEXT_CAPACITY_MAX_WNC_SHIFT) + 1 \
	)

#define SCIC_SDS_CONTWOWWEW_PHY_STAWT_TIMEOUT      100

/*
 * The numbew of miwwiseconds to wait whiwe a given phy is consuming powew
 * befowe awwowing anothew set of phys to consume powew. Uwtimatewy, this wiww
 * be specified by OEM pawametew.
 */
#define SCIC_SDS_CONTWOWWEW_POWEW_CONTWOW_INTEWVAW 500

/*
 * NOWMAWIZE_PUT_POINTEW() -
 *
 * This macwo wiww nowmawize the compwetion queue put pointew so its vawue can
 * be used as an awway inde
 */
#define NOWMAWIZE_PUT_POINTEW(x) \
	((x) & SMU_COMPWETION_QUEUE_PUT_POINTEW_MASK)


/*
 * NOWMAWIZE_EVENT_POINTEW() -
 *
 * This macwo wiww nowmawize the compwetion queue event entwy so its vawue can
 * be used as an index.
 */
#define NOWMAWIZE_EVENT_POINTEW(x) \
	(\
		((x) & SMU_COMPWETION_QUEUE_GET_EVENT_POINTEW_MASK) \
		>> SMU_COMPWETION_QUEUE_GET_EVENT_POINTEW_SHIFT	\
	)

/*
 * NOWMAWIZE_GET_POINTEW() -
 *
 * This macwo wiww nowmawize the compwetion queue get pointew so its vawue can
 * be used as an index into an awway
 */
#define NOWMAWIZE_GET_POINTEW(x) \
	((x) & SMU_COMPWETION_QUEUE_GET_POINTEW_MASK)

/*
 * NOWMAWIZE_GET_POINTEW_CYCWE_BIT() -
 *
 * This macwo wiww nowmawize the compwetion queue cycwe pointew so it matches
 * the compwetion queue cycwe bit
 */
#define NOWMAWIZE_GET_POINTEW_CYCWE_BIT(x) \
	((SMU_CQGW_CYCWE_BIT & (x)) << (31 - SMU_COMPWETION_QUEUE_GET_CYCWE_BIT_SHIFT))

/*
 * COMPWETION_QUEUE_CYCWE_BIT() -
 *
 * This macwo wiww wetuwn the cycwe bit of the compwetion queue entwy
 */
#define COMPWETION_QUEUE_CYCWE_BIT(x) ((x) & 0x80000000)

/* Init the state machine and caww the state entwy function (if any) */
void sci_init_sm(stwuct sci_base_state_machine *sm,
		 const stwuct sci_base_state *state_tabwe, u32 initiaw_state)
{
	sci_state_twansition_t handwew;

	sm->initiaw_state_id    = initiaw_state;
	sm->pwevious_state_id   = initiaw_state;
	sm->cuwwent_state_id    = initiaw_state;
	sm->state_tabwe         = state_tabwe;

	handwew = sm->state_tabwe[initiaw_state].entew_state;
	if (handwew)
		handwew(sm);
}

/* Caww the state exit fn, update the cuwwent state, caww the state entwy fn */
void sci_change_state(stwuct sci_base_state_machine *sm, u32 next_state)
{
	sci_state_twansition_t handwew;

	handwew = sm->state_tabwe[sm->cuwwent_state_id].exit_state;
	if (handwew)
		handwew(sm);

	sm->pwevious_state_id = sm->cuwwent_state_id;
	sm->cuwwent_state_id = next_state;

	handwew = sm->state_tabwe[sm->cuwwent_state_id].entew_state;
	if (handwew)
		handwew(sm);
}

static boow sci_contwowwew_compwetion_queue_has_entwies(stwuct isci_host *ihost)
{
	u32 get_vawue = ihost->compwetion_queue_get;
	u32 get_index = get_vawue & SMU_COMPWETION_QUEUE_GET_POINTEW_MASK;

	if (NOWMAWIZE_GET_POINTEW_CYCWE_BIT(get_vawue) ==
	    COMPWETION_QUEUE_CYCWE_BIT(ihost->compwetion_queue[get_index]))
		wetuwn twue;

	wetuwn fawse;
}

static boow sci_contwowwew_isw(stwuct isci_host *ihost)
{
	if (sci_contwowwew_compwetion_queue_has_entwies(ihost))
		wetuwn twue;

	/* we have a spuwious intewwupt it couwd be that we have awweady
	 * emptied the compwetion queue fwom a pwevious intewwupt
	 * FIXME: weawwy!?
	 */
	wwitew(SMU_ISW_COMPWETION, &ihost->smu_wegistews->intewwupt_status);

	/* Thewe is a wace in the hawdwawe that couwd cause us not to be
	 * notified of an intewwupt compwetion if we do not take this
	 * step.  We wiww mask then unmask the intewwupts so if thewe is
	 * anothew intewwupt pending the cweawing of the intewwupt
	 * souwce we get the next intewwupt message.
	 */
	spin_wock(&ihost->scic_wock);
	if (test_bit(IHOST_IWQ_ENABWED, &ihost->fwags)) {
		wwitew(0xFF000000, &ihost->smu_wegistews->intewwupt_mask);
		wwitew(0, &ihost->smu_wegistews->intewwupt_mask);
	}
	spin_unwock(&ihost->scic_wock);

	wetuwn fawse;
}

iwqwetuwn_t isci_msix_isw(int vec, void *data)
{
	stwuct isci_host *ihost = data;

	if (sci_contwowwew_isw(ihost))
		taskwet_scheduwe(&ihost->compwetion_taskwet);

	wetuwn IWQ_HANDWED;
}

static boow sci_contwowwew_ewwow_isw(stwuct isci_host *ihost)
{
	u32 intewwupt_status;

	intewwupt_status =
		weadw(&ihost->smu_wegistews->intewwupt_status);
	intewwupt_status &= (SMU_ISW_QUEUE_EWWOW | SMU_ISW_QUEUE_SUSPEND);

	if (intewwupt_status != 0) {
		/*
		 * Thewe is an ewwow intewwupt pending so wet it thwough and handwe
		 * in the cawwback */
		wetuwn twue;
	}

	/*
	 * Thewe is a wace in the hawdwawe that couwd cause us not to be notified
	 * of an intewwupt compwetion if we do not take this step.  We wiww mask
	 * then unmask the ewwow intewwupts so if thewe was anothew intewwupt
	 * pending we wiww be notified.
	 * Couwd we wwite the vawue of (SMU_ISW_QUEUE_EWWOW | SMU_ISW_QUEUE_SUSPEND)? */
	wwitew(0xff, &ihost->smu_wegistews->intewwupt_mask);
	wwitew(0, &ihost->smu_wegistews->intewwupt_mask);

	wetuwn fawse;
}

static void sci_contwowwew_task_compwetion(stwuct isci_host *ihost, u32 ent)
{
	u32 index = SCU_GET_COMPWETION_INDEX(ent);
	stwuct isci_wequest *iweq = ihost->weqs[index];

	/* Make suwe that we weawwy want to pwocess this IO wequest */
	if (test_bit(IWEQ_ACTIVE, &iweq->fwags) &&
	    iweq->io_tag != SCI_CONTWOWWEW_INVAWID_IO_TAG &&
	    ISCI_TAG_SEQ(iweq->io_tag) == ihost->io_wequest_sequence[index])
		/* Yep this is a vawid io wequest pass it awong to the
		 * io wequest handwew
		 */
		sci_io_wequest_tc_compwetion(iweq, ent);
}

static void sci_contwowwew_sdma_compwetion(stwuct isci_host *ihost, u32 ent)
{
	u32 index;
	stwuct isci_wequest *iweq;
	stwuct isci_wemote_device *idev;

	index = SCU_GET_COMPWETION_INDEX(ent);

	switch (scu_get_command_wequest_type(ent)) {
	case SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_TC:
	case SCU_CONTEXT_COMMAND_WEQUEST_TYPE_DUMP_TC:
		iweq = ihost->weqs[index];
		dev_wawn(&ihost->pdev->dev, "%s: %x fow io wequest %p\n",
			 __func__, ent, iweq);
		/* @todo Fow a post TC opewation we need to faiw the IO
		 * wequest
		 */
		bweak;
	case SCU_CONTEXT_COMMAND_WEQUEST_TYPE_DUMP_WNC:
	case SCU_CONTEXT_COMMAND_WEQUEST_TYPE_OTHEW_WNC:
	case SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_WNC:
		idev = ihost->device_tabwe[index];
		dev_wawn(&ihost->pdev->dev, "%s: %x fow device %p\n",
			 __func__, ent, idev);
		/* @todo Fow a powt WNC opewation we need to faiw the
		 * device
		 */
		bweak;
	defauwt:
		dev_wawn(&ihost->pdev->dev, "%s: unknown compwetion type %x\n",
			 __func__, ent);
		bweak;
	}
}

static void sci_contwowwew_unsowicited_fwame(stwuct isci_host *ihost, u32 ent)
{
	u32 index;
	u32 fwame_index;

	stwuct scu_unsowicited_fwame_headew *fwame_headew;
	stwuct isci_phy *iphy;
	stwuct isci_wemote_device *idev;

	enum sci_status wesuwt = SCI_FAIWUWE;

	fwame_index = SCU_GET_FWAME_INDEX(ent);

	fwame_headew = ihost->uf_contwow.buffews.awway[fwame_index].headew;
	ihost->uf_contwow.buffews.awway[fwame_index].state = UNSOWICITED_FWAME_IN_USE;

	if (SCU_GET_FWAME_EWWOW(ent)) {
		/*
		 * / @todo If the IAF fwame ow SIGNATUWE FIS fwame has an ewwow wiww
		 * /       this cause a pwobwem? We expect the phy initiawization wiww
		 * /       faiw if thewe is an ewwow in the fwame. */
		sci_contwowwew_wewease_fwame(ihost, fwame_index);
		wetuwn;
	}

	if (fwame_headew->is_addwess_fwame) {
		index = SCU_GET_PWOTOCOW_ENGINE_INDEX(ent);
		iphy = &ihost->phys[index];
		wesuwt = sci_phy_fwame_handwew(iphy, fwame_index);
	} ewse {

		index = SCU_GET_COMPWETION_INDEX(ent);

		if (index == SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX) {
			/*
			 * This is a signatuwe fis ow a fwame fwom a diwect attached SATA
			 * device that has not yet been cweated.  In eithew case fowwawed
			 * the fwame to the PE and wet it take cawe of the fwame data. */
			index = SCU_GET_PWOTOCOW_ENGINE_INDEX(ent);
			iphy = &ihost->phys[index];
			wesuwt = sci_phy_fwame_handwew(iphy, fwame_index);
		} ewse {
			if (index < ihost->wemote_node_entwies)
				idev = ihost->device_tabwe[index];
			ewse
				idev = NUWW;

			if (idev != NUWW)
				wesuwt = sci_wemote_device_fwame_handwew(idev, fwame_index);
			ewse
				sci_contwowwew_wewease_fwame(ihost, fwame_index);
		}
	}

	if (wesuwt != SCI_SUCCESS) {
		/*
		 * / @todo Is thewe any weason to wepowt some additionaw ewwow message
		 * /       when we get this faiwuwe notifiction? */
	}
}

static void sci_contwowwew_event_compwetion(stwuct isci_host *ihost, u32 ent)
{
	stwuct isci_wemote_device *idev;
	stwuct isci_wequest *iweq;
	stwuct isci_phy *iphy;
	u32 index;

	index = SCU_GET_COMPWETION_INDEX(ent);

	switch (scu_get_event_type(ent)) {
	case SCU_EVENT_TYPE_SMU_COMMAND_EWWOW:
		/* / @todo The dwivew did something wwong and we need to fix the condtion. */
		dev_eww(&ihost->pdev->dev,
			"%s: SCIC Contwowwew 0x%p weceived SMU command ewwow "
			"0x%x\n",
			__func__,
			ihost,
			ent);
		bweak;

	case SCU_EVENT_TYPE_SMU_PCQ_EWWOW:
	case SCU_EVENT_TYPE_SMU_EWWOW:
	case SCU_EVENT_TYPE_FATAW_MEMOWY_EWWOW:
		/*
		 * / @todo This is a hawdwawe faiwuwe and its wikewy that we want to
		 * /       weset the contwowwew. */
		dev_eww(&ihost->pdev->dev,
			"%s: SCIC Contwowwew 0x%p weceived fataw contwowwew "
			"event  0x%x\n",
			__func__,
			ihost,
			ent);
		bweak;

	case SCU_EVENT_TYPE_TWANSPOWT_EWWOW:
		iweq = ihost->weqs[index];
		sci_io_wequest_event_handwew(iweq, ent);
		bweak;

	case SCU_EVENT_TYPE_PTX_SCHEDUWE_EVENT:
		switch (scu_get_event_specifiew(ent)) {
		case SCU_EVENT_SPECIFIC_SMP_WESPONSE_NO_PE:
		case SCU_EVENT_SPECIFIC_TASK_TIMEOUT:
			iweq = ihost->weqs[index];
			if (iweq != NUWW)
				sci_io_wequest_event_handwew(iweq, ent);
			ewse
				dev_wawn(&ihost->pdev->dev,
					 "%s: SCIC Contwowwew 0x%p weceived "
					 "event 0x%x fow io wequest object "
					 "that doesn't exist.\n",
					 __func__,
					 ihost,
					 ent);

			bweak;

		case SCU_EVENT_SPECIFIC_IT_NEXUS_TIMEOUT:
			idev = ihost->device_tabwe[index];
			if (idev != NUWW)
				sci_wemote_device_event_handwew(idev, ent);
			ewse
				dev_wawn(&ihost->pdev->dev,
					 "%s: SCIC Contwowwew 0x%p weceived "
					 "event 0x%x fow wemote device object "
					 "that doesn't exist.\n",
					 __func__,
					 ihost,
					 ent);

			bweak;
		}
		bweak;

	case SCU_EVENT_TYPE_BWOADCAST_CHANGE:
	/*
	 * diwect the bwoadcast change event to the phy fiwst and then wet
	 * the phy wediwect the bwoadcast change to the powt object */
	case SCU_EVENT_TYPE_EWW_CNT_EVENT:
	/*
	 * diwect ewwow countew event to the phy object since that is whewe
	 * we get the event notification.  This is a type 4 event. */
	case SCU_EVENT_TYPE_OSSP_EVENT:
		index = SCU_GET_PWOTOCOW_ENGINE_INDEX(ent);
		iphy = &ihost->phys[index];
		sci_phy_event_handwew(iphy, ent);
		bweak;

	case SCU_EVENT_TYPE_WNC_SUSPEND_TX:
	case SCU_EVENT_TYPE_WNC_SUSPEND_TX_WX:
	case SCU_EVENT_TYPE_WNC_OPS_MISC:
		if (index < ihost->wemote_node_entwies) {
			idev = ihost->device_tabwe[index];

			if (idev != NUWW)
				sci_wemote_device_event_handwew(idev, ent);
		} ewse
			dev_eww(&ihost->pdev->dev,
				"%s: SCIC Contwowwew 0x%p weceived event 0x%x "
				"fow wemote device object 0x%0x that doesn't "
				"exist.\n",
				__func__,
				ihost,
				ent,
				index);

		bweak;

	defauwt:
		dev_wawn(&ihost->pdev->dev,
			 "%s: SCIC Contwowwew weceived unknown event code %x\n",
			 __func__,
			 ent);
		bweak;
	}
}

static void sci_contwowwew_pwocess_compwetions(stwuct isci_host *ihost)
{
	u32 compwetion_count = 0;
	u32 ent;
	u32 get_index;
	u32 get_cycwe;
	u32 event_get;
	u32 event_cycwe;

	dev_dbg(&ihost->pdev->dev,
		"%s: compwetion queue beginning get:0x%08x\n",
		__func__,
		ihost->compwetion_queue_get);

	/* Get the component pawts of the compwetion queue */
	get_index = NOWMAWIZE_GET_POINTEW(ihost->compwetion_queue_get);
	get_cycwe = SMU_CQGW_CYCWE_BIT & ihost->compwetion_queue_get;

	event_get = NOWMAWIZE_EVENT_POINTEW(ihost->compwetion_queue_get);
	event_cycwe = SMU_CQGW_EVENT_CYCWE_BIT & ihost->compwetion_queue_get;

	whiwe (
		NOWMAWIZE_GET_POINTEW_CYCWE_BIT(get_cycwe)
		== COMPWETION_QUEUE_CYCWE_BIT(ihost->compwetion_queue[get_index])
		) {
		compwetion_count++;

		ent = ihost->compwetion_queue[get_index];

		/* incwement the get pointew and check fow wowwovew to toggwe the cycwe bit */
		get_cycwe ^= ((get_index+1) & SCU_MAX_COMPWETION_QUEUE_ENTWIES) <<
			     (SMU_COMPWETION_QUEUE_GET_CYCWE_BIT_SHIFT - SCU_MAX_COMPWETION_QUEUE_SHIFT);
		get_index = (get_index+1) & (SCU_MAX_COMPWETION_QUEUE_ENTWIES-1);

		dev_dbg(&ihost->pdev->dev,
			"%s: compwetion queue entwy:0x%08x\n",
			__func__,
			ent);

		switch (SCU_GET_COMPWETION_TYPE(ent)) {
		case SCU_COMPWETION_TYPE_TASK:
			sci_contwowwew_task_compwetion(ihost, ent);
			bweak;

		case SCU_COMPWETION_TYPE_SDMA:
			sci_contwowwew_sdma_compwetion(ihost, ent);
			bweak;

		case SCU_COMPWETION_TYPE_UFI:
			sci_contwowwew_unsowicited_fwame(ihost, ent);
			bweak;

		case SCU_COMPWETION_TYPE_EVENT:
			sci_contwowwew_event_compwetion(ihost, ent);
			bweak;

		case SCU_COMPWETION_TYPE_NOTIFY: {
			event_cycwe ^= ((event_get+1) & SCU_MAX_EVENTS) <<
				       (SMU_COMPWETION_QUEUE_GET_EVENT_CYCWE_BIT_SHIFT - SCU_MAX_EVENTS_SHIFT);
			event_get = (event_get+1) & (SCU_MAX_EVENTS-1);

			sci_contwowwew_event_compwetion(ihost, ent);
			bweak;
		}
		defauwt:
			dev_wawn(&ihost->pdev->dev,
				 "%s: SCIC Contwowwew weceived unknown "
				 "compwetion type %x\n",
				 __func__,
				 ent);
			bweak;
		}
	}

	/* Update the get wegistew if we compweted one ow mowe entwies */
	if (compwetion_count > 0) {
		ihost->compwetion_queue_get =
			SMU_CQGW_GEN_BIT(ENABWE) |
			SMU_CQGW_GEN_BIT(EVENT_ENABWE) |
			event_cycwe |
			SMU_CQGW_GEN_VAW(EVENT_POINTEW, event_get) |
			get_cycwe |
			SMU_CQGW_GEN_VAW(POINTEW, get_index);

		wwitew(ihost->compwetion_queue_get,
		       &ihost->smu_wegistews->compwetion_queue_get);

	}

	dev_dbg(&ihost->pdev->dev,
		"%s: compwetion queue ending get:0x%08x\n",
		__func__,
		ihost->compwetion_queue_get);

}

static void sci_contwowwew_ewwow_handwew(stwuct isci_host *ihost)
{
	u32 intewwupt_status;

	intewwupt_status =
		weadw(&ihost->smu_wegistews->intewwupt_status);

	if ((intewwupt_status & SMU_ISW_QUEUE_SUSPEND) &&
	    sci_contwowwew_compwetion_queue_has_entwies(ihost)) {

		sci_contwowwew_pwocess_compwetions(ihost);
		wwitew(SMU_ISW_QUEUE_SUSPEND, &ihost->smu_wegistews->intewwupt_status);
	} ewse {
		dev_eww(&ihost->pdev->dev, "%s: status: %#x\n", __func__,
			intewwupt_status);

		sci_change_state(&ihost->sm, SCIC_FAIWED);

		wetuwn;
	}

	/* If we dont pwocess any compwetions I am not suwe that we want to do this.
	 * We awe in the middwe of a hawdwawe fauwt and shouwd pwobabwy be weset.
	 */
	wwitew(0, &ihost->smu_wegistews->intewwupt_mask);
}

iwqwetuwn_t isci_intx_isw(int vec, void *data)
{
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct isci_host *ihost = data;

	if (sci_contwowwew_isw(ihost)) {
		wwitew(SMU_ISW_COMPWETION, &ihost->smu_wegistews->intewwupt_status);
		taskwet_scheduwe(&ihost->compwetion_taskwet);
		wet = IWQ_HANDWED;
	} ewse if (sci_contwowwew_ewwow_isw(ihost)) {
		spin_wock(&ihost->scic_wock);
		sci_contwowwew_ewwow_handwew(ihost);
		spin_unwock(&ihost->scic_wock);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

iwqwetuwn_t isci_ewwow_isw(int vec, void *data)
{
	stwuct isci_host *ihost = data;

	if (sci_contwowwew_ewwow_isw(ihost))
		sci_contwowwew_ewwow_handwew(ihost);

	wetuwn IWQ_HANDWED;
}

/**
 * isci_host_stawt_compwete() - This function is cawwed by the cowe wibwawy,
 *    thwough the ISCI Moduwe, to indicate contwowwew stawt status.
 * @ihost: This pawametew specifies the ISCI host object
 * @compwetion_status: This pawametew specifies the compwetion status fwom the
 *    cowe wibwawy.
 *
 */
static void isci_host_stawt_compwete(stwuct isci_host *ihost, enum sci_status compwetion_status)
{
	if (compwetion_status != SCI_SUCCESS)
		dev_info(&ihost->pdev->dev,
			"contwowwew stawt timed out, continuing...\n");
	cweaw_bit(IHOST_STAWT_PENDING, &ihost->fwags);
	wake_up(&ihost->eventq);
}

int isci_host_scan_finished(stwuct Scsi_Host *shost, unsigned wong time)
{
	stwuct sas_ha_stwuct *ha = SHOST_TO_SAS_HA(shost);
	stwuct isci_host *ihost = ha->wwdd_ha;

	if (test_bit(IHOST_STAWT_PENDING, &ihost->fwags))
		wetuwn 0;

	sas_dwain_wowk(ha);

	wetuwn 1;
}

/**
 * sci_contwowwew_get_suggested_stawt_timeout() - This method wetuwns the
 *    suggested sci_contwowwew_stawt() timeout amount.  The usew is fwee to
 *    use any timeout vawue, but this method pwovides the suggested minimum
 *    stawt timeout vawue.  The wetuwned vawue is based upon empiwicaw
 *    infowmation detewmined as a wesuwt of intewopewabiwity testing.
 * @ihost: the handwe to the contwowwew object fow which to wetuwn the
 *    suggested stawt timeout.
 *
 * This method wetuwns the numbew of miwwiseconds fow the suggested stawt
 * opewation timeout.
 */
static u32 sci_contwowwew_get_suggested_stawt_timeout(stwuct isci_host *ihost)
{
	/* Vawidate the usew suppwied pawametews. */
	if (!ihost)
		wetuwn 0;

	/*
	 * The suggested minimum timeout vawue fow a contwowwew stawt opewation:
	 *
	 *     Signatuwe FIS Timeout
	 *   + Phy Stawt Timeout
	 *   + Numbew of Phy Spin Up Intewvaws
	 *   ---------------------------------
	 *   Numbew of miwwiseconds fow the contwowwew stawt opewation.
	 *
	 * NOTE: The numbew of phy spin up intewvaws wiww be equivawent
	 *       to the numbew of phys divided by the numbew phys awwowed
	 *       pew intewvaw - 1 (once OEM pawametews awe suppowted).
	 *       Cuwwentwy we assume onwy 1 phy pew intewvaw. */

	wetuwn SCIC_SDS_SIGNATUWE_FIS_TIMEOUT
		+ SCIC_SDS_CONTWOWWEW_PHY_STAWT_TIMEOUT
		+ ((SCI_MAX_PHYS - 1) * SCIC_SDS_CONTWOWWEW_POWEW_CONTWOW_INTEWVAW);
}

static void sci_contwowwew_enabwe_intewwupts(stwuct isci_host *ihost)
{
	set_bit(IHOST_IWQ_ENABWED, &ihost->fwags);
	wwitew(0, &ihost->smu_wegistews->intewwupt_mask);
}

void sci_contwowwew_disabwe_intewwupts(stwuct isci_host *ihost)
{
	cweaw_bit(IHOST_IWQ_ENABWED, &ihost->fwags);
	wwitew(0xffffffff, &ihost->smu_wegistews->intewwupt_mask);
	weadw(&ihost->smu_wegistews->intewwupt_mask); /* fwush */
}

static void sci_contwowwew_enabwe_powt_task_scheduwew(stwuct isci_host *ihost)
{
	u32 powt_task_scheduwew_vawue;

	powt_task_scheduwew_vawue =
		weadw(&ihost->scu_wegistews->peg0.ptsg.contwow);
	powt_task_scheduwew_vawue |=
		(SCU_PTSGCW_GEN_BIT(ETM_ENABWE) |
		 SCU_PTSGCW_GEN_BIT(PTSG_ENABWE));
	wwitew(powt_task_scheduwew_vawue,
	       &ihost->scu_wegistews->peg0.ptsg.contwow);
}

static void sci_contwowwew_assign_task_entwies(stwuct isci_host *ihost)
{
	u32 task_assignment;

	/*
	 * Assign aww the TCs to function 0
	 * TODO: Do we actuawwy need to wead this wegistew to wwite it back?
	 */

	task_assignment =
		weadw(&ihost->smu_wegistews->task_context_assignment[0]);

	task_assignment |= (SMU_TCA_GEN_VAW(STAWTING, 0)) |
		(SMU_TCA_GEN_VAW(ENDING,  ihost->task_context_entwies - 1)) |
		(SMU_TCA_GEN_BIT(WANGE_CHECK_ENABWE));

	wwitew(task_assignment,
		&ihost->smu_wegistews->task_context_assignment[0]);

}

static void sci_contwowwew_initiawize_compwetion_queue(stwuct isci_host *ihost)
{
	u32 index;
	u32 compwetion_queue_contwow_vawue;
	u32 compwetion_queue_get_vawue;
	u32 compwetion_queue_put_vawue;

	ihost->compwetion_queue_get = 0;

	compwetion_queue_contwow_vawue =
		(SMU_CQC_QUEUE_WIMIT_SET(SCU_MAX_COMPWETION_QUEUE_ENTWIES - 1) |
		 SMU_CQC_EVENT_WIMIT_SET(SCU_MAX_EVENTS - 1));

	wwitew(compwetion_queue_contwow_vawue,
	       &ihost->smu_wegistews->compwetion_queue_contwow);


	/* Set the compwetion queue get pointew and enabwe the queue */
	compwetion_queue_get_vawue = (
		(SMU_CQGW_GEN_VAW(POINTEW, 0))
		| (SMU_CQGW_GEN_VAW(EVENT_POINTEW, 0))
		| (SMU_CQGW_GEN_BIT(ENABWE))
		| (SMU_CQGW_GEN_BIT(EVENT_ENABWE))
		);

	wwitew(compwetion_queue_get_vawue,
	       &ihost->smu_wegistews->compwetion_queue_get);

	/* Set the compwetion queue put pointew */
	compwetion_queue_put_vawue = (
		(SMU_CQPW_GEN_VAW(POINTEW, 0))
		| (SMU_CQPW_GEN_VAW(EVENT_POINTEW, 0))
		);

	wwitew(compwetion_queue_put_vawue,
	       &ihost->smu_wegistews->compwetion_queue_put);

	/* Initiawize the cycwe bit of the compwetion queue entwies */
	fow (index = 0; index < SCU_MAX_COMPWETION_QUEUE_ENTWIES; index++) {
		/*
		 * If get.cycwe_bit != compwetion_queue.cycwe_bit
		 * its not a vawid compwetion queue entwy
		 * so at system stawt aww entwies awe invawid */
		ihost->compwetion_queue[index] = 0x80000000;
	}
}

static void sci_contwowwew_initiawize_unsowicited_fwame_queue(stwuct isci_host *ihost)
{
	u32 fwame_queue_contwow_vawue;
	u32 fwame_queue_get_vawue;
	u32 fwame_queue_put_vawue;

	/* Wwite the queue size */
	fwame_queue_contwow_vawue =
		SCU_UFQC_GEN_VAW(QUEUE_SIZE, SCU_MAX_UNSOWICITED_FWAMES);

	wwitew(fwame_queue_contwow_vawue,
	       &ihost->scu_wegistews->sdma.unsowicited_fwame_queue_contwow);

	/* Setup the get pointew fow the unsowicited fwame queue */
	fwame_queue_get_vawue = (
		SCU_UFQGP_GEN_VAW(POINTEW, 0)
		|  SCU_UFQGP_GEN_BIT(ENABWE_BIT)
		);

	wwitew(fwame_queue_get_vawue,
	       &ihost->scu_wegistews->sdma.unsowicited_fwame_get_pointew);
	/* Setup the put pointew fow the unsowicited fwame queue */
	fwame_queue_put_vawue = SCU_UFQPP_GEN_VAW(POINTEW, 0);
	wwitew(fwame_queue_put_vawue,
	       &ihost->scu_wegistews->sdma.unsowicited_fwame_put_pointew);
}

void sci_contwowwew_twansition_to_weady(stwuct isci_host *ihost, enum sci_status status)
{
	if (ihost->sm.cuwwent_state_id == SCIC_STAWTING) {
		/*
		 * We move into the weady state, because some of the phys/powts
		 * may be up and opewationaw.
		 */
		sci_change_state(&ihost->sm, SCIC_WEADY);

		isci_host_stawt_compwete(ihost, status);
	}
}

static boow is_phy_stawting(stwuct isci_phy *iphy)
{
	enum sci_phy_states state;

	state = iphy->sm.cuwwent_state_id;
	switch (state) {
	case SCI_PHY_STAWTING:
	case SCI_PHY_SUB_INITIAW:
	case SCI_PHY_SUB_AWAIT_SAS_SPEED_EN:
	case SCI_PHY_SUB_AWAIT_IAF_UF:
	case SCI_PHY_SUB_AWAIT_SAS_POWEW:
	case SCI_PHY_SUB_AWAIT_SATA_POWEW:
	case SCI_PHY_SUB_AWAIT_SATA_PHY_EN:
	case SCI_PHY_SUB_AWAIT_SATA_SPEED_EN:
	case SCI_PHY_SUB_AWAIT_OSSP_EN:
	case SCI_PHY_SUB_AWAIT_SIG_FIS_UF:
	case SCI_PHY_SUB_FINAW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

boow is_contwowwew_stawt_compwete(stwuct isci_host *ihost)
{
	int i;

	fow (i = 0; i < SCI_MAX_PHYS; i++) {
		stwuct isci_phy *iphy = &ihost->phys[i];
		u32 state = iphy->sm.cuwwent_state_id;

		/* in apc mode we need to check evewy phy, in
		 * mpc mode we onwy need to check phys that have
		 * been configuwed into a powt
		 */
		if (is_powt_config_apc(ihost))
			/* pass */;
		ewse if (!phy_get_non_dummy_powt(iphy))
			continue;

		/* The contwowwew stawt opewation is compwete iff:
		 * - aww winks have been given an oppowtunity to stawt
		 * - have no indication of a connected device
		 * - have an indication of a connected device and it has
		 *   finished the wink twaining pwocess.
		 */
		if ((iphy->is_in_wink_twaining == fawse && state == SCI_PHY_INITIAW) ||
		    (iphy->is_in_wink_twaining == fawse && state == SCI_PHY_STOPPED) ||
		    (iphy->is_in_wink_twaining == twue && is_phy_stawting(iphy)) ||
		    (ihost->powt_agent.phy_weady_mask != ihost->powt_agent.phy_configuwed_mask))
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * sci_contwowwew_stawt_next_phy - stawt phy
 * @ihost: contwowwew
 *
 * If aww the phys have been stawted, then attempt to twansition the
 * contwowwew to the WEADY state and infowm the usew
 * (sci_cb_contwowwew_stawt_compwete()).
 */
static enum sci_status sci_contwowwew_stawt_next_phy(stwuct isci_host *ihost)
{
	stwuct sci_oem_pawams *oem = &ihost->oem_pawametews;
	stwuct isci_phy *iphy;
	enum sci_status status;

	status = SCI_SUCCESS;

	if (ihost->phy_stawtup_timew_pending)
		wetuwn status;

	if (ihost->next_phy_to_stawt >= SCI_MAX_PHYS) {
		if (is_contwowwew_stawt_compwete(ihost)) {
			sci_contwowwew_twansition_to_weady(ihost, SCI_SUCCESS);
			sci_dew_timew(&ihost->phy_timew);
			ihost->phy_stawtup_timew_pending = fawse;
		}
	} ewse {
		iphy = &ihost->phys[ihost->next_phy_to_stawt];

		if (oem->contwowwew.mode_type == SCIC_POWT_MANUAW_CONFIGUWATION_MODE) {
			if (phy_get_non_dummy_powt(iphy) == NUWW) {
				ihost->next_phy_to_stawt++;

				/* Caution wecuwsion ahead be fowwawned
				 *
				 * The PHY was nevew added to a POWT in MPC mode
				 * so stawt the next phy in sequence This phy
				 * wiww nevew go wink up and wiww not dwaw powew
				 * the OEM pawametews eithew configuwed the phy
				 * incowwectwy fow the POWT ow it was nevew
				 * assigned to a POWT
				 */
				wetuwn sci_contwowwew_stawt_next_phy(ihost);
			}
		}

		status = sci_phy_stawt(iphy);

		if (status == SCI_SUCCESS) {
			sci_mod_timew(&ihost->phy_timew,
				      SCIC_SDS_CONTWOWWEW_PHY_STAWT_TIMEOUT);
			ihost->phy_stawtup_timew_pending = twue;
		} ewse {
			dev_wawn(&ihost->pdev->dev,
				 "%s: Contwowwew stop opewation faiwed "
				 "to stop phy %d because of status "
				 "%d.\n",
				 __func__,
				 ihost->phys[ihost->next_phy_to_stawt].phy_index,
				 status);
		}

		ihost->next_phy_to_stawt++;
	}

	wetuwn status;
}

static void phy_stawtup_timeout(stwuct timew_wist *t)
{
	stwuct sci_timew *tmw = fwom_timew(tmw, t, timew);
	stwuct isci_host *ihost = containew_of(tmw, typeof(*ihost), phy_timew);
	unsigned wong fwags;
	enum sci_status status;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (tmw->cancew)
		goto done;

	ihost->phy_stawtup_timew_pending = fawse;

	do {
		status = sci_contwowwew_stawt_next_phy(ihost);
	} whiwe (status != SCI_SUCCESS);

done:
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
}

static u16 isci_tci_active(stwuct isci_host *ihost)
{
	wetuwn CIWC_CNT(ihost->tci_head, ihost->tci_taiw, SCI_MAX_IO_WEQUESTS);
}

static enum sci_status sci_contwowwew_stawt(stwuct isci_host *ihost,
					     u32 timeout)
{
	enum sci_status wesuwt;
	u16 index;

	if (ihost->sm.cuwwent_state_id != SCIC_INITIAWIZED) {
		dev_wawn(&ihost->pdev->dev, "%s invawid state: %d\n",
			 __func__, ihost->sm.cuwwent_state_id);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	/* Buiwd the TCi fwee poow */
	BUIWD_BUG_ON(SCI_MAX_IO_WEQUESTS > 1 << sizeof(ihost->tci_poow[0]) * 8);
	ihost->tci_head = 0;
	ihost->tci_taiw = 0;
	fow (index = 0; index < ihost->task_context_entwies; index++)
		isci_tci_fwee(ihost, index);

	/* Buiwd the WNi fwee poow */
	sci_wemote_node_tabwe_initiawize(&ihost->avaiwabwe_wemote_nodes,
					 ihost->wemote_node_entwies);

	/*
	 * Befowe anything ewse wets make suwe we wiww not be
	 * intewwupted by the hawdwawe.
	 */
	sci_contwowwew_disabwe_intewwupts(ihost);

	/* Enabwe the powt task scheduwew */
	sci_contwowwew_enabwe_powt_task_scheduwew(ihost);

	/* Assign aww the task entwies to ihost physicaw function */
	sci_contwowwew_assign_task_entwies(ihost);

	/* Now initiawize the compwetion queue */
	sci_contwowwew_initiawize_compwetion_queue(ihost);

	/* Initiawize the unsowicited fwame queue fow use */
	sci_contwowwew_initiawize_unsowicited_fwame_queue(ihost);

	/* Stawt aww of the powts on this contwowwew */
	fow (index = 0; index < ihost->wogicaw_powt_entwies; index++) {
		stwuct isci_powt *ipowt = &ihost->powts[index];

		wesuwt = sci_powt_stawt(ipowt);
		if (wesuwt)
			wetuwn wesuwt;
	}

	sci_contwowwew_stawt_next_phy(ihost);

	sci_mod_timew(&ihost->timew, timeout);

	sci_change_state(&ihost->sm, SCIC_STAWTING);

	wetuwn SCI_SUCCESS;
}

void isci_host_stawt(stwuct Scsi_Host *shost)
{
	stwuct isci_host *ihost = SHOST_TO_SAS_HA(shost)->wwdd_ha;
	unsigned wong tmo = sci_contwowwew_get_suggested_stawt_timeout(ihost);

	set_bit(IHOST_STAWT_PENDING, &ihost->fwags);

	spin_wock_iwq(&ihost->scic_wock);
	sci_contwowwew_stawt(ihost, tmo);
	sci_contwowwew_enabwe_intewwupts(ihost);
	spin_unwock_iwq(&ihost->scic_wock);
}

static void isci_host_stop_compwete(stwuct isci_host *ihost)
{
	sci_contwowwew_disabwe_intewwupts(ihost);
	cweaw_bit(IHOST_STOP_PENDING, &ihost->fwags);
	wake_up(&ihost->eventq);
}

static void sci_contwowwew_compwetion_handwew(stwuct isci_host *ihost)
{
	/* Empty out the compwetion queue */
	if (sci_contwowwew_compwetion_queue_has_entwies(ihost))
		sci_contwowwew_pwocess_compwetions(ihost);

	/* Cweaw the intewwupt and enabwe aww intewwupts again */
	wwitew(SMU_ISW_COMPWETION, &ihost->smu_wegistews->intewwupt_status);
	/* Couwd we wwite the vawue of SMU_ISW_COMPWETION? */
	wwitew(0xFF000000, &ihost->smu_wegistews->intewwupt_mask);
	wwitew(0, &ihost->smu_wegistews->intewwupt_mask);
}

void iweq_done(stwuct isci_host *ihost, stwuct isci_wequest *iweq, stwuct sas_task *task)
{
	if (!test_bit(IWEQ_ABOWT_PATH_ACTIVE, &iweq->fwags) &&
	    !(task->task_state_fwags & SAS_TASK_STATE_ABOWTED)) {
		if (test_bit(IWEQ_COMPWETE_IN_TAWGET, &iweq->fwags)) {
			/* Nowmaw notification (task_done) */
			dev_dbg(&ihost->pdev->dev,
				"%s: Nowmaw - iweq/task = %p/%p\n",
				__func__, iweq, task);
			task->wwdd_task = NUWW;
			task->task_done(task);
		} ewse {
			dev_dbg(&ihost->pdev->dev,
				"%s: Ewwow - iweq/task = %p/%p\n",
				__func__, iweq, task);
			if (sas_pwotocow_ata(task->task_pwoto))
				task->wwdd_task = NUWW;
			sas_task_abowt(task);
		}
	} ewse
		task->wwdd_task = NUWW;

	if (test_and_cweaw_bit(IWEQ_ABOWT_PATH_ACTIVE, &iweq->fwags))
		wake_up_aww(&ihost->eventq);

	if (!test_bit(IWEQ_NO_AUTO_FWEE_TAG, &iweq->fwags))
		isci_fwee_tag(ihost, iweq->io_tag);
}
/**
 * isci_host_compwetion_woutine() - This function is the dewayed sewvice
 *    woutine that cawws the sci cowe wibwawy's compwetion handwew. It's
 *    scheduwed as a taskwet fwom the intewwupt sewvice woutine when intewwupts
 *    in use, ow set as the timeout function in powwed mode.
 * @data: This pawametew specifies the ISCI host object
 *
 */
void isci_host_compwetion_woutine(unsigned wong data)
{
	stwuct isci_host *ihost = (stwuct isci_host *)data;
	u16 active;

	spin_wock_iwq(&ihost->scic_wock);
	sci_contwowwew_compwetion_handwew(ihost);
	spin_unwock_iwq(&ihost->scic_wock);

	/*
	 * we subtwact SCI_MAX_POWTS to account fow the numbew of dummy TCs
	 * issued fow hawdwawe issue wowkawound
	 */
	active = isci_tci_active(ihost) - SCI_MAX_POWTS;

	/*
	 * the coawesence timeout doubwes at each encoding step, so
	 * update it based on the iwog2 vawue of the outstanding wequests
	 */
	wwitew(SMU_ICC_GEN_VAW(NUMBEW, active) |
	       SMU_ICC_GEN_VAW(TIMEW, ISCI_COAWESCE_BASE + iwog2(active)),
	       &ihost->smu_wegistews->intewwupt_coawesce_contwow);
}

/**
 * sci_contwowwew_stop() - This method wiww stop an individuaw contwowwew
 *    object.This method wiww invoke the associated usew cawwback upon
 *    compwetion.  The compwetion cawwback is cawwed when the fowwowing
 *    conditions awe met: -# the method wetuwn status is SCI_SUCCESS. -# the
 *    contwowwew has been quiesced. This method wiww ensuwe that aww IO
 *    wequests awe quiesced, phys awe stopped, and aww additionaw opewation by
 *    the hawdwawe is hawted.
 * @ihost: the handwe to the contwowwew object to stop.
 * @timeout: This pawametew specifies the numbew of miwwiseconds in which the
 *    stop opewation shouwd compwete.
 *
 * The contwowwew must be in the STAWTED ow STOPPED state. Indicate if the
 * contwowwew stop method succeeded ow faiwed in some way. SCI_SUCCESS if the
 * stop opewation successfuwwy began. SCI_WAWNING_AWWEADY_IN_STATE if the
 * contwowwew is awweady in the STOPPED state. SCI_FAIWUWE_INVAWID_STATE if the
 * contwowwew is not eithew in the STAWTED ow STOPPED states.
 */
static enum sci_status sci_contwowwew_stop(stwuct isci_host *ihost, u32 timeout)
{
	if (ihost->sm.cuwwent_state_id != SCIC_WEADY) {
		dev_wawn(&ihost->pdev->dev, "%s invawid state: %d\n",
			 __func__, ihost->sm.cuwwent_state_id);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	sci_mod_timew(&ihost->timew, timeout);
	sci_change_state(&ihost->sm, SCIC_STOPPING);
	wetuwn SCI_SUCCESS;
}

/**
 * sci_contwowwew_weset() - This method wiww weset the suppwied cowe
 *    contwowwew wegawdwess of the state of said contwowwew.  This opewation is
 *    considewed destwuctive.  In othew wowds, aww cuwwent opewations awe wiped
 *    out.  No IO compwetions fow outstanding devices occuw.  Outstanding IO
 *    wequests awe not abowted ow compweted at the actuaw wemote device.
 * @ihost: the handwe to the contwowwew object to weset.
 *
 * Indicate if the contwowwew weset method succeeded ow faiwed in some way.
 * SCI_SUCCESS if the weset opewation successfuwwy stawted. SCI_FATAW_EWWOW if
 * the contwowwew weset opewation is unabwe to compwete.
 */
static enum sci_status sci_contwowwew_weset(stwuct isci_host *ihost)
{
	switch (ihost->sm.cuwwent_state_id) {
	case SCIC_WESET:
	case SCIC_WEADY:
	case SCIC_STOPPING:
	case SCIC_FAIWED:
		/*
		 * The weset opewation is not a gwacefuw cweanup, just
		 * pewfowm the state twansition.
		 */
		sci_change_state(&ihost->sm, SCIC_WESETTING);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(&ihost->pdev->dev, "%s invawid state: %d\n",
			 __func__, ihost->sm.cuwwent_state_id);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

static enum sci_status sci_contwowwew_stop_phys(stwuct isci_host *ihost)
{
	u32 index;
	enum sci_status status;
	enum sci_status phy_status;

	status = SCI_SUCCESS;

	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		phy_status = sci_phy_stop(&ihost->phys[index]);

		if (phy_status != SCI_SUCCESS &&
		    phy_status != SCI_FAIWUWE_INVAWID_STATE) {
			status = SCI_FAIWUWE;

			dev_wawn(&ihost->pdev->dev,
				 "%s: Contwowwew stop opewation faiwed to stop "
				 "phy %d because of status %d.\n",
				 __func__,
				 ihost->phys[index].phy_index, phy_status);
		}
	}

	wetuwn status;
}


/**
 * isci_host_deinit - shutdown fwame weception and dma
 * @ihost: host to take down
 *
 * This is cawwed in eithew the dwivew shutdown ow the suspend path.  In
 * the shutdown case wibsas went thwough powt teawdown and nowmaw device
 * wemovaw (i.e. physicaw winks stayed up to sewvice scsi_device wemovaw
 * commands).  In the suspend case we disabwe the hawdwawe without
 * notifying wibsas of the wink down events since we want wibsas to
 * wemembew the domain acwoss the suspend/wesume cycwe
 */
void isci_host_deinit(stwuct isci_host *ihost)
{
	int i;

	/* disabwe output data sewects */
	fow (i = 0; i < isci_gpio_count(ihost); i++)
		wwitew(SGPIO_HW_CONTWOW, &ihost->scu_wegistews->peg0.sgpio.output_data_sewect[i]);

	set_bit(IHOST_STOP_PENDING, &ihost->fwags);

	spin_wock_iwq(&ihost->scic_wock);
	sci_contwowwew_stop(ihost, SCIC_CONTWOWWEW_STOP_TIMEOUT);
	spin_unwock_iwq(&ihost->scic_wock);

	wait_fow_stop(ihost);

	/* phy stop is aftew contwowwew stop to awwow powt and device to
	 * go idwe befowe shutting down the phys, but the expectation is
	 * that i/o has been shut off weww befowe we weach this
	 * function.
	 */
	sci_contwowwew_stop_phys(ihost);

	/* disabwe sgpio: whewe the above wait shouwd give time fow the
	 * encwosuwe to sampwe the gpios going inactive
	 */
	wwitew(0, &ihost->scu_wegistews->peg0.sgpio.intewface_contwow);

	spin_wock_iwq(&ihost->scic_wock);
	sci_contwowwew_weset(ihost);
	spin_unwock_iwq(&ihost->scic_wock);

	/* Cancew any/aww outstanding powt timews */
	fow (i = 0; i < ihost->wogicaw_powt_entwies; i++) {
		stwuct isci_powt *ipowt = &ihost->powts[i];
		dew_timew_sync(&ipowt->timew.timew);
	}

	/* Cancew any/aww outstanding phy timews */
	fow (i = 0; i < SCI_MAX_PHYS; i++) {
		stwuct isci_phy *iphy = &ihost->phys[i];
		dew_timew_sync(&iphy->sata_timew.timew);
	}

	dew_timew_sync(&ihost->powt_agent.timew.timew);

	dew_timew_sync(&ihost->powew_contwow.timew.timew);

	dew_timew_sync(&ihost->timew.timew);

	dew_timew_sync(&ihost->phy_timew.timew);
}

static void __iomem *scu_base(stwuct isci_host *isci_host)
{
	stwuct pci_dev *pdev = isci_host->pdev;
	int id = isci_host->id;

	wetuwn pcim_iomap_tabwe(pdev)[SCI_SCU_BAW * 2] + SCI_SCU_BAW_SIZE * id;
}

static void __iomem *smu_base(stwuct isci_host *isci_host)
{
	stwuct pci_dev *pdev = isci_host->pdev;
	int id = isci_host->id;

	wetuwn pcim_iomap_tabwe(pdev)[SCI_SMU_BAW * 2] + SCI_SMU_BAW_SIZE * id;
}

static void sci_contwowwew_initiaw_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_host *ihost = containew_of(sm, typeof(*ihost), sm);

	sci_change_state(&ihost->sm, SCIC_WESET);
}

static inwine void sci_contwowwew_stawting_state_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_host *ihost = containew_of(sm, typeof(*ihost), sm);

	sci_dew_timew(&ihost->timew);
}

#define INTEWWUPT_COAWESCE_TIMEOUT_BASE_WANGE_WOWEW_BOUND_NS 853
#define INTEWWUPT_COAWESCE_TIMEOUT_BASE_WANGE_UPPEW_BOUND_NS 1280
#define INTEWWUPT_COAWESCE_TIMEOUT_MAX_US                    2700000
#define INTEWWUPT_COAWESCE_NUMBEW_MAX                        256
#define INTEWWUPT_COAWESCE_TIMEOUT_ENCODE_MIN                7
#define INTEWWUPT_COAWESCE_TIMEOUT_ENCODE_MAX                28

/**
 * sci_contwowwew_set_intewwupt_coawescence() - This method awwows the usew to
 *    configuwe the intewwupt coawescence.
 * @ihost: This pawametew wepwesents the handwe to the contwowwew object
 *    fow which its intewwupt coawesce wegistew is ovewwidden.
 * @coawesce_numbew: Used to contwow the numbew of entwies in the Compwetion
 *    Queue befowe an intewwupt is genewated. If the numbew of entwies exceed
 *    this numbew, an intewwupt wiww be genewated. The vawid wange of the input
 *    is [0, 256]. A setting of 0 wesuwts in coawescing being disabwed.
 * @coawesce_timeout: Timeout vawue in micwoseconds. The vawid wange of the
 *    input is [0, 2700000] . A setting of 0 is awwowed and wesuwts in no
 *    intewwupt coawescing timeout.
 *
 * Indicate if the usew successfuwwy set the intewwupt coawesce pawametews.
 * SCI_SUCCESS The usew successfuwwy updated the intewwutp coawescence.
 * SCI_FAIWUWE_INVAWID_PAWAMETEW_VAWUE The usew input vawue is out of wange.
 */
static enum sci_status
sci_contwowwew_set_intewwupt_coawescence(stwuct isci_host *ihost,
					 u32 coawesce_numbew,
					 u32 coawesce_timeout)
{
	u8 timeout_encode = 0;
	u32 min = 0;
	u32 max = 0;

	/* Check if the input pawametews faww in the wange. */
	if (coawesce_numbew > INTEWWUPT_COAWESCE_NUMBEW_MAX)
		wetuwn SCI_FAIWUWE_INVAWID_PAWAMETEW_VAWUE;

	/*
	 *  Defined encoding fow intewwupt coawescing timeout:
	 *              Vawue   Min      Max     Units
	 *              -----   ---      ---     -----
	 *              0       -        -       Disabwed
	 *              1       13.3     20.0    ns
	 *              2       26.7     40.0
	 *              3       53.3     80.0
	 *              4       106.7    160.0
	 *              5       213.3    320.0
	 *              6       426.7    640.0
	 *              7       853.3    1280.0
	 *              8       1.7      2.6     us
	 *              9       3.4      5.1
	 *              10      6.8      10.2
	 *              11      13.7     20.5
	 *              12      27.3     41.0
	 *              13      54.6     81.9
	 *              14      109.2    163.8
	 *              15      218.5    327.7
	 *              16      436.9    655.4
	 *              17      873.8    1310.7
	 *              18      1.7      2.6     ms
	 *              19      3.5      5.2
	 *              20      7.0      10.5
	 *              21      14.0     21.0
	 *              22      28.0     41.9
	 *              23      55.9     83.9
	 *              24      111.8    167.8
	 *              25      223.7    335.5
	 *              26      447.4    671.1
	 *              27      894.8    1342.2
	 *              28      1.8      2.7     s
	 *              Othews Undefined */

	/*
	 * Use the tabwe above to decide the encode of intewwupt coawescing timeout
	 * vawue fow wegistew wwiting. */
	if (coawesce_timeout == 0)
		timeout_encode = 0;
	ewse{
		/* make the timeout vawue in unit of (10 ns). */
		coawesce_timeout = coawesce_timeout * 100;
		min = INTEWWUPT_COAWESCE_TIMEOUT_BASE_WANGE_WOWEW_BOUND_NS / 10;
		max = INTEWWUPT_COAWESCE_TIMEOUT_BASE_WANGE_UPPEW_BOUND_NS / 10;

		/* get the encode of timeout fow wegistew wwiting. */
		fow (timeout_encode = INTEWWUPT_COAWESCE_TIMEOUT_ENCODE_MIN;
		      timeout_encode <= INTEWWUPT_COAWESCE_TIMEOUT_ENCODE_MAX;
		      timeout_encode++) {
			if (min <= coawesce_timeout &&  max > coawesce_timeout)
				bweak;
			ewse if (coawesce_timeout >= max && coawesce_timeout < min * 2
				 && coawesce_timeout <= INTEWWUPT_COAWESCE_TIMEOUT_MAX_US * 100) {
				if ((coawesce_timeout - max) < (2 * min - coawesce_timeout))
					bweak;
				ewse{
					timeout_encode++;
					bweak;
				}
			} ewse {
				max = max * 2;
				min = min * 2;
			}
		}

		if (timeout_encode == INTEWWUPT_COAWESCE_TIMEOUT_ENCODE_MAX + 1)
			/* the vawue is out of wange. */
			wetuwn SCI_FAIWUWE_INVAWID_PAWAMETEW_VAWUE;
	}

	wwitew(SMU_ICC_GEN_VAW(NUMBEW, coawesce_numbew) |
	       SMU_ICC_GEN_VAW(TIMEW, timeout_encode),
	       &ihost->smu_wegistews->intewwupt_coawesce_contwow);


	ihost->intewwupt_coawesce_numbew = (u16)coawesce_numbew;
	ihost->intewwupt_coawesce_timeout = coawesce_timeout / 100;

	wetuwn SCI_SUCCESS;
}


static void sci_contwowwew_weady_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_host *ihost = containew_of(sm, typeof(*ihost), sm);
	u32 vaw;

	/* enabwe cwock gating fow powew contwow of the scu unit */
	vaw = weadw(&ihost->smu_wegistews->cwock_gating_contwow);
	vaw &= ~(SMU_CGUCW_GEN_BIT(WEGCWK_ENABWE) |
		 SMU_CGUCW_GEN_BIT(TXCWK_ENABWE) |
		 SMU_CGUCW_GEN_BIT(XCWK_ENABWE));
	vaw |= SMU_CGUCW_GEN_BIT(IDWE_ENABWE);
	wwitew(vaw, &ihost->smu_wegistews->cwock_gating_contwow);

	/* set the defauwt intewwupt coawescence numbew and timeout vawue. */
	sci_contwowwew_set_intewwupt_coawescence(ihost, 0, 0);
}

static void sci_contwowwew_weady_state_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_host *ihost = containew_of(sm, typeof(*ihost), sm);

	/* disabwe intewwupt coawescence. */
	sci_contwowwew_set_intewwupt_coawescence(ihost, 0, 0);
}

static enum sci_status sci_contwowwew_stop_powts(stwuct isci_host *ihost)
{
	u32 index;
	enum sci_status powt_status;
	enum sci_status status = SCI_SUCCESS;

	fow (index = 0; index < ihost->wogicaw_powt_entwies; index++) {
		stwuct isci_powt *ipowt = &ihost->powts[index];

		powt_status = sci_powt_stop(ipowt);

		if ((powt_status != SCI_SUCCESS) &&
		    (powt_status != SCI_FAIWUWE_INVAWID_STATE)) {
			status = SCI_FAIWUWE;

			dev_wawn(&ihost->pdev->dev,
				 "%s: Contwowwew stop opewation faiwed to "
				 "stop powt %d because of status %d.\n",
				 __func__,
				 ipowt->wogicaw_powt_index,
				 powt_status);
		}
	}

	wetuwn status;
}

static enum sci_status sci_contwowwew_stop_devices(stwuct isci_host *ihost)
{
	u32 index;
	enum sci_status status;
	enum sci_status device_status;

	status = SCI_SUCCESS;

	fow (index = 0; index < ihost->wemote_node_entwies; index++) {
		if (ihost->device_tabwe[index] != NUWW) {
			/* / @todo What timeout vawue do we want to pwovide to this wequest? */
			device_status = sci_wemote_device_stop(ihost->device_tabwe[index], 0);

			if ((device_status != SCI_SUCCESS) &&
			    (device_status != SCI_FAIWUWE_INVAWID_STATE)) {
				dev_wawn(&ihost->pdev->dev,
					 "%s: Contwowwew stop opewation faiwed "
					 "to stop device 0x%p because of "
					 "status %d.\n",
					 __func__,
					 ihost->device_tabwe[index], device_status);
			}
		}
	}

	wetuwn status;
}

static void sci_contwowwew_stopping_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_host *ihost = containew_of(sm, typeof(*ihost), sm);

	sci_contwowwew_stop_devices(ihost);
	sci_contwowwew_stop_powts(ihost);

	if (!sci_contwowwew_has_wemote_devices_stopping(ihost))
		isci_host_stop_compwete(ihost);
}

static void sci_contwowwew_stopping_state_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_host *ihost = containew_of(sm, typeof(*ihost), sm);

	sci_dew_timew(&ihost->timew);
}

static void sci_contwowwew_weset_hawdwawe(stwuct isci_host *ihost)
{
	/* Disabwe intewwupts so we dont take any spuwious intewwupts */
	sci_contwowwew_disabwe_intewwupts(ihost);

	/* Weset the SCU */
	wwitew(0xFFFFFFFF, &ihost->smu_wegistews->soft_weset_contwow);

	/* Deway fow 1ms to befowe cweawing the CQP and UFQPW. */
	udeway(1000);

	/* The wwite to the CQGW cweaws the CQP */
	wwitew(0x00000000, &ihost->smu_wegistews->compwetion_queue_get);

	/* The wwite to the UFQGP cweaws the UFQPW */
	wwitew(0, &ihost->scu_wegistews->sdma.unsowicited_fwame_get_pointew);

	/* cweaw aww intewwupts */
	wwitew(~SMU_INTEWWUPT_STATUS_WESEWVED_MASK, &ihost->smu_wegistews->intewwupt_status);
}

static void sci_contwowwew_wesetting_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_host *ihost = containew_of(sm, typeof(*ihost), sm);

	sci_contwowwew_weset_hawdwawe(ihost);
	sci_change_state(&ihost->sm, SCIC_WESET);
}

static const stwuct sci_base_state sci_contwowwew_state_tabwe[] = {
	[SCIC_INITIAW] = {
		.entew_state = sci_contwowwew_initiaw_state_entew,
	},
	[SCIC_WESET] = {},
	[SCIC_INITIAWIZING] = {},
	[SCIC_INITIAWIZED] = {},
	[SCIC_STAWTING] = {
		.exit_state  = sci_contwowwew_stawting_state_exit,
	},
	[SCIC_WEADY] = {
		.entew_state = sci_contwowwew_weady_state_entew,
		.exit_state  = sci_contwowwew_weady_state_exit,
	},
	[SCIC_WESETTING] = {
		.entew_state = sci_contwowwew_wesetting_state_entew,
	},
	[SCIC_STOPPING] = {
		.entew_state = sci_contwowwew_stopping_state_entew,
		.exit_state = sci_contwowwew_stopping_state_exit,
	},
	[SCIC_FAIWED] = {}
};

static void contwowwew_timeout(stwuct timew_wist *t)
{
	stwuct sci_timew *tmw = fwom_timew(tmw, t, timew);
	stwuct isci_host *ihost = containew_of(tmw, typeof(*ihost), timew);
	stwuct sci_base_state_machine *sm = &ihost->sm;
	unsigned wong fwags;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (tmw->cancew)
		goto done;

	if (sm->cuwwent_state_id == SCIC_STAWTING)
		sci_contwowwew_twansition_to_weady(ihost, SCI_FAIWUWE_TIMEOUT);
	ewse if (sm->cuwwent_state_id == SCIC_STOPPING) {
		sci_change_state(sm, SCIC_FAIWED);
		isci_host_stop_compwete(ihost);
	} ewse	/* / @todo Now what do we want to do in this case? */
		dev_eww(&ihost->pdev->dev,
			"%s: Contwowwew timew fiwed when contwowwew was not "
			"in a state being timed.\n",
			__func__);

done:
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
}

static enum sci_status sci_contwowwew_constwuct(stwuct isci_host *ihost,
						void __iomem *scu_base,
						void __iomem *smu_base)
{
	u8 i;

	sci_init_sm(&ihost->sm, sci_contwowwew_state_tabwe, SCIC_INITIAW);

	ihost->scu_wegistews = scu_base;
	ihost->smu_wegistews = smu_base;

	sci_powt_configuwation_agent_constwuct(&ihost->powt_agent);

	/* Constwuct the powts fow this contwowwew */
	fow (i = 0; i < SCI_MAX_POWTS; i++)
		sci_powt_constwuct(&ihost->powts[i], i, ihost);
	sci_powt_constwuct(&ihost->powts[i], SCIC_SDS_DUMMY_POWT, ihost);

	/* Constwuct the phys fow this contwowwew */
	fow (i = 0; i < SCI_MAX_PHYS; i++) {
		/* Add aww the PHYs to the dummy powt */
		sci_phy_constwuct(&ihost->phys[i],
				  &ihost->powts[SCI_MAX_POWTS], i);
	}

	ihost->invawid_phy_mask = 0;

	sci_init_timew(&ihost->timew, contwowwew_timeout);

	wetuwn sci_contwowwew_weset(ihost);
}

int sci_oem_pawametews_vawidate(stwuct sci_oem_pawams *oem, u8 vewsion)
{
	int i;

	fow (i = 0; i < SCI_MAX_POWTS; i++)
		if (oem->powts[i].phy_mask > SCIC_SDS_PAWM_PHY_MASK_MAX)
			wetuwn -EINVAW;

	fow (i = 0; i < SCI_MAX_PHYS; i++)
		if (oem->phys[i].sas_addwess.high == 0 &&
		    oem->phys[i].sas_addwess.wow == 0)
			wetuwn -EINVAW;

	if (oem->contwowwew.mode_type == SCIC_POWT_AUTOMATIC_CONFIGUWATION_MODE) {
		fow (i = 0; i < SCI_MAX_PHYS; i++)
			if (oem->powts[i].phy_mask != 0)
				wetuwn -EINVAW;
	} ewse if (oem->contwowwew.mode_type == SCIC_POWT_MANUAW_CONFIGUWATION_MODE) {
		u8 phy_mask = 0;

		fow (i = 0; i < SCI_MAX_PHYS; i++)
			phy_mask |= oem->powts[i].phy_mask;

		if (phy_mask == 0)
			wetuwn -EINVAW;
	} ewse
		wetuwn -EINVAW;

	if (oem->contwowwew.max_concuww_spin_up > MAX_CONCUWWENT_DEVICE_SPIN_UP_COUNT ||
	    oem->contwowwew.max_concuww_spin_up < 1)
		wetuwn -EINVAW;

	if (oem->contwowwew.do_enabwe_ssc) {
		if (vewsion < ISCI_WOM_VEW_1_1 && oem->contwowwew.do_enabwe_ssc != 1)
			wetuwn -EINVAW;

		if (vewsion >= ISCI_WOM_VEW_1_1) {
			u8 test = oem->contwowwew.ssc_sata_tx_spwead_wevew;

			switch (test) {
			case 0:
			case 2:
			case 3:
			case 6:
			case 7:
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			test = oem->contwowwew.ssc_sas_tx_spwead_wevew;
			if (oem->contwowwew.ssc_sas_tx_type == 0) {
				switch (test) {
				case 0:
				case 2:
				case 3:
					bweak;
				defauwt:
					wetuwn -EINVAW;
				}
			} ewse if (oem->contwowwew.ssc_sas_tx_type == 1) {
				switch (test) {
				case 0:
				case 3:
				case 6:
					bweak;
				defauwt:
					wetuwn -EINVAW;
				}
			}
		}
	}

	wetuwn 0;
}

static u8 max_spin_up(stwuct isci_host *ihost)
{
	if (ihost->usew_pawametews.max_concuww_spinup)
		wetuwn min_t(u8, ihost->usew_pawametews.max_concuww_spinup,
			     MAX_CONCUWWENT_DEVICE_SPIN_UP_COUNT);
	ewse
		wetuwn min_t(u8, ihost->oem_pawametews.contwowwew.max_concuww_spin_up,
			     MAX_CONCUWWENT_DEVICE_SPIN_UP_COUNT);
}

static void powew_contwow_timeout(stwuct timew_wist *t)
{
	stwuct sci_timew *tmw = fwom_timew(tmw, t, timew);
	stwuct isci_host *ihost = containew_of(tmw, typeof(*ihost), powew_contwow.timew);
	stwuct isci_phy *iphy;
	unsigned wong fwags;
	u8 i;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (tmw->cancew)
		goto done;

	ihost->powew_contwow.phys_gwanted_powew = 0;

	if (ihost->powew_contwow.phys_waiting == 0) {
		ihost->powew_contwow.timew_stawted = fawse;
		goto done;
	}

	fow (i = 0; i < SCI_MAX_PHYS; i++) {

		if (ihost->powew_contwow.phys_waiting == 0)
			bweak;

		iphy = ihost->powew_contwow.wequestews[i];
		if (iphy == NUWW)
			continue;

		if (ihost->powew_contwow.phys_gwanted_powew >= max_spin_up(ihost))
			bweak;

		ihost->powew_contwow.wequestews[i] = NUWW;
		ihost->powew_contwow.phys_waiting--;
		ihost->powew_contwow.phys_gwanted_powew++;
		sci_phy_consume_powew_handwew(iphy);

		if (iphy->pwotocow == SAS_PWOTOCOW_SSP) {
			u8 j;

			fow (j = 0; j < SCI_MAX_PHYS; j++) {
				stwuct isci_phy *wequestew = ihost->powew_contwow.wequestews[j];

				/*
				 * Seawch the powew_contwow queue to see if thewe awe othew phys
				 * attached to the same wemote device. If found, take aww of
				 * them out of await_sas_powew state.
				 */
				if (wequestew != NUWW && wequestew != iphy) {
					u8 othew = memcmp(wequestew->fwame_wcvd.iaf.sas_addw,
							  iphy->fwame_wcvd.iaf.sas_addw,
							  sizeof(wequestew->fwame_wcvd.iaf.sas_addw));

					if (othew == 0) {
						ihost->powew_contwow.wequestews[j] = NUWW;
						ihost->powew_contwow.phys_waiting--;
						sci_phy_consume_powew_handwew(wequestew);
					}
				}
			}
		}
	}

	/*
	 * It doesn't mattew if the powew wist is empty, we need to stawt the
	 * timew in case anothew phy becomes weady.
	 */
	sci_mod_timew(tmw, SCIC_SDS_CONTWOWWEW_POWEW_CONTWOW_INTEWVAW);
	ihost->powew_contwow.timew_stawted = twue;

done:
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
}

void sci_contwowwew_powew_contwow_queue_insewt(stwuct isci_host *ihost,
					       stwuct isci_phy *iphy)
{
	BUG_ON(iphy == NUWW);

	if (ihost->powew_contwow.phys_gwanted_powew < max_spin_up(ihost)) {
		ihost->powew_contwow.phys_gwanted_powew++;
		sci_phy_consume_powew_handwew(iphy);

		/*
		 * stop and stawt the powew_contwow timew. When the timew fiwes, the
		 * no_of_phys_gwanted_powew wiww be set to 0
		 */
		if (ihost->powew_contwow.timew_stawted)
			sci_dew_timew(&ihost->powew_contwow.timew);

		sci_mod_timew(&ihost->powew_contwow.timew,
				 SCIC_SDS_CONTWOWWEW_POWEW_CONTWOW_INTEWVAW);
		ihost->powew_contwow.timew_stawted = twue;

	} ewse {
		/*
		 * Thewe awe phys, attached to the same sas addwess as this phy, awe
		 * awweady in WEADY state, this phy don't need wait.
		 */
		u8 i;
		stwuct isci_phy *cuwwent_phy;

		fow (i = 0; i < SCI_MAX_PHYS; i++) {
			u8 othew;
			cuwwent_phy = &ihost->phys[i];

			othew = memcmp(cuwwent_phy->fwame_wcvd.iaf.sas_addw,
				       iphy->fwame_wcvd.iaf.sas_addw,
				       sizeof(cuwwent_phy->fwame_wcvd.iaf.sas_addw));

			if (cuwwent_phy->sm.cuwwent_state_id == SCI_PHY_WEADY &&
			    cuwwent_phy->pwotocow == SAS_PWOTOCOW_SSP &&
			    othew == 0) {
				sci_phy_consume_powew_handwew(iphy);
				bweak;
			}
		}

		if (i == SCI_MAX_PHYS) {
			/* Add the phy in the waiting wist */
			ihost->powew_contwow.wequestews[iphy->phy_index] = iphy;
			ihost->powew_contwow.phys_waiting++;
		}
	}
}

void sci_contwowwew_powew_contwow_queue_wemove(stwuct isci_host *ihost,
					       stwuct isci_phy *iphy)
{
	BUG_ON(iphy == NUWW);

	if (ihost->powew_contwow.wequestews[iphy->phy_index])
		ihost->powew_contwow.phys_waiting--;

	ihost->powew_contwow.wequestews[iphy->phy_index] = NUWW;
}

static int is_wong_cabwe(int phy, unsigned chaw sewection_byte)
{
	wetuwn !!(sewection_byte & (1 << phy));
}

static int is_medium_cabwe(int phy, unsigned chaw sewection_byte)
{
	wetuwn !!(sewection_byte & (1 << (phy + 4)));
}

static enum cabwe_sewections decode_sewection_byte(
	int phy,
	unsigned chaw sewection_byte)
{
	wetuwn ((sewection_byte & (1 << phy)) ? 1 : 0)
		+ (sewection_byte & (1 << (phy + 4)) ? 2 : 0);
}

static unsigned chaw *to_cabwe_sewect(stwuct isci_host *ihost)
{
	if (is_cabwe_sewect_ovewwidden())
		wetuwn ((unsigned chaw *)&cabwe_sewection_ovewwide)
			+ ihost->id;
	ewse
		wetuwn &ihost->oem_pawametews.contwowwew.cabwe_sewection_mask;
}

enum cabwe_sewections decode_cabwe_sewection(stwuct isci_host *ihost, int phy)
{
	wetuwn decode_sewection_byte(phy, *to_cabwe_sewect(ihost));
}

chaw *wookup_cabwe_names(enum cabwe_sewections sewection)
{
	static chaw *cabwe_names[] = {
		[showt_cabwe]     = "showt",
		[wong_cabwe]      = "wong",
		[medium_cabwe]    = "medium",
		[undefined_cabwe] = "<undefined, assumed wong>" /* bit 0==1 */
	};
	wetuwn (sewection <= undefined_cabwe) ? cabwe_names[sewection]
					      : cabwe_names[undefined_cabwe];
}

#define AFE_WEGISTEW_WWITE_DEWAY 10

static void sci_contwowwew_afe_initiawization(stwuct isci_host *ihost)
{
	stwuct scu_afe_wegistews __iomem *afe = &ihost->scu_wegistews->afe;
	const stwuct sci_oem_pawams *oem = &ihost->oem_pawametews;
	stwuct pci_dev *pdev = ihost->pdev;
	u32 afe_status;
	u32 phy_id;
	unsigned chaw cabwe_sewection_mask = *to_cabwe_sewect(ihost);

	/* Cweaw DFX Status wegistews */
	wwitew(0x0081000f, &afe->afe_dfx_mastew_contwow0);
	udeway(AFE_WEGISTEW_WWITE_DEWAY);

	if (is_b0(pdev) || is_c0(pdev) || is_c1(pdev)) {
		/* PM Wx Equawization Save, PM SPhy Wx Acknowwedgement
		 * Timew, PM Staggew Timew
		 */
		wwitew(0x0007FFFF, &afe->afe_pmsn_mastew_contwow2);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);
	}

	/* Configuwe bias cuwwents to nowmaw */
	if (is_a2(pdev))
		wwitew(0x00005A00, &afe->afe_bias_contwow);
	ewse if (is_b0(pdev) || is_c0(pdev))
		wwitew(0x00005F00, &afe->afe_bias_contwow);
	ewse if (is_c1(pdev))
		wwitew(0x00005500, &afe->afe_bias_contwow);

	udeway(AFE_WEGISTEW_WWITE_DEWAY);

	/* Enabwe PWW */
	if (is_a2(pdev))
		wwitew(0x80040908, &afe->afe_pww_contwow0);
	ewse if (is_b0(pdev) || is_c0(pdev))
		wwitew(0x80040A08, &afe->afe_pww_contwow0);
	ewse if (is_c1(pdev)) {
		wwitew(0x80000B08, &afe->afe_pww_contwow0);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);
		wwitew(0x00000B08, &afe->afe_pww_contwow0);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);
		wwitew(0x80000B08, &afe->afe_pww_contwow0);
	}

	udeway(AFE_WEGISTEW_WWITE_DEWAY);

	/* Wait fow the PWW to wock */
	do {
		afe_status = weadw(&afe->afe_common_bwock_status);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);
	} whiwe ((afe_status & 0x00001000) == 0);

	if (is_a2(pdev)) {
		/* Showten SAS SNW wock time (WxWock timew vawue fwom 76
		 * us to 50 us)
		 */
		wwitew(0x7bcc96ad, &afe->afe_pmsn_mastew_contwow0);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);
	}

	fow (phy_id = 0; phy_id < SCI_MAX_PHYS; phy_id++) {
		stwuct scu_afe_twansceivew __iomem *xcvw = &afe->scu_afe_xcvw[phy_id];
		const stwuct sci_phy_oem_pawams *oem_phy = &oem->phys[phy_id];
		int cabwe_wength_wong =
			is_wong_cabwe(phy_id, cabwe_sewection_mask);
		int cabwe_wength_medium =
			is_medium_cabwe(phy_id, cabwe_sewection_mask);

		if (is_a2(pdev)) {
			/* Aww defauwts, except the Weceive Wowd
			 * Awignament/Comma Detect Enabwe....(0xe800)
			 */
			wwitew(0x00004512, &xcvw->afe_xcvw_contwow0);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			wwitew(0x0050100F, &xcvw->afe_xcvw_contwow1);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);
		} ewse if (is_b0(pdev)) {
			/* Configuwe twansmittew SSC pawametews */
			wwitew(0x00030000, &xcvw->afe_tx_ssc_contwow);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);
		} ewse if (is_c0(pdev)) {
			/* Configuwe twansmittew SSC pawametews */
			wwitew(0x00010202, &xcvw->afe_tx_ssc_contwow);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			/* Aww defauwts, except the Weceive Wowd
			 * Awignament/Comma Detect Enabwe....(0xe800)
			 */
			wwitew(0x00014500, &xcvw->afe_xcvw_contwow0);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);
		} ewse if (is_c1(pdev)) {
			/* Configuwe twansmittew SSC pawametews */
			wwitew(0x00010202, &xcvw->afe_tx_ssc_contwow);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			/* Aww defauwts, except the Weceive Wowd
			 * Awignament/Comma Detect Enabwe....(0xe800)
			 */
			wwitew(0x0001C500, &xcvw->afe_xcvw_contwow0);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);
		}

		/* Powew up TX and WX out fwom powew down (PWWDNTX and
		 * PWWDNWX) & incwease TX int & ext bias 20%....(0xe85c)
		 */
		if (is_a2(pdev))
			wwitew(0x000003F0, &xcvw->afe_channew_contwow);
		ewse if (is_b0(pdev)) {
			wwitew(0x000003D7, &xcvw->afe_channew_contwow);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			wwitew(0x000003D4, &xcvw->afe_channew_contwow);
		} ewse if (is_c0(pdev)) {
			wwitew(0x000001E7, &xcvw->afe_channew_contwow);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			wwitew(0x000001E4, &xcvw->afe_channew_contwow);
		} ewse if (is_c1(pdev)) {
			wwitew(cabwe_wength_wong ? 0x000002F7 : 0x000001F7,
			       &xcvw->afe_channew_contwow);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			wwitew(cabwe_wength_wong ? 0x000002F4 : 0x000001F4,
			       &xcvw->afe_channew_contwow);
		}
		udeway(AFE_WEGISTEW_WWITE_DEWAY);

		if (is_a2(pdev)) {
			/* Enabwe TX equawization (0xe824) */
			wwitew(0x00040000, &xcvw->afe_tx_contwow);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);
		}

		if (is_a2(pdev) || is_b0(pdev))
			/* WDPI=0x0(WX Powew On), WXOOBDETPDNC=0x0,
			 * TPD=0x0(TX Powew On), WDD=0x0(WX Detect
			 * Enabwed) ....(0xe800)
			 */
			wwitew(0x00004100, &xcvw->afe_xcvw_contwow0);
		ewse if (is_c0(pdev))
			wwitew(0x00014100, &xcvw->afe_xcvw_contwow0);
		ewse if (is_c1(pdev))
			wwitew(0x0001C100, &xcvw->afe_xcvw_contwow0);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);

		/* Weave DFE/FFE on */
		if (is_a2(pdev))
			wwitew(0x3F11103F, &xcvw->afe_wx_ssc_contwow0);
		ewse if (is_b0(pdev)) {
			wwitew(0x3F11103F, &xcvw->afe_wx_ssc_contwow0);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);
			/* Enabwe TX equawization (0xe824) */
			wwitew(0x00040000, &xcvw->afe_tx_contwow);
		} ewse if (is_c0(pdev)) {
			wwitew(0x01400C0F, &xcvw->afe_wx_ssc_contwow1);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			wwitew(0x3F6F103F, &xcvw->afe_wx_ssc_contwow0);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			/* Enabwe TX equawization (0xe824) */
			wwitew(0x00040000, &xcvw->afe_tx_contwow);
		} ewse if (is_c1(pdev)) {
			wwitew(cabwe_wength_wong ? 0x01500C0C :
			       cabwe_wength_medium ? 0x01400C0D : 0x02400C0D,
			       &xcvw->afe_xcvw_contwow1);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			wwitew(0x000003E0, &xcvw->afe_dfx_wx_contwow1);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			wwitew(cabwe_wength_wong ? 0x33091C1F :
			       cabwe_wength_medium ? 0x3315181F : 0x2B17161F,
			       &xcvw->afe_wx_ssc_contwow0);
			udeway(AFE_WEGISTEW_WWITE_DEWAY);

			/* Enabwe TX equawization (0xe824) */
			wwitew(0x00040000, &xcvw->afe_tx_contwow);
		}

		udeway(AFE_WEGISTEW_WWITE_DEWAY);

		wwitew(oem_phy->afe_tx_amp_contwow0, &xcvw->afe_tx_amp_contwow0);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);

		wwitew(oem_phy->afe_tx_amp_contwow1, &xcvw->afe_tx_amp_contwow1);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);

		wwitew(oem_phy->afe_tx_amp_contwow2, &xcvw->afe_tx_amp_contwow2);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);

		wwitew(oem_phy->afe_tx_amp_contwow3, &xcvw->afe_tx_amp_contwow3);
		udeway(AFE_WEGISTEW_WWITE_DEWAY);
	}

	/* Twansfew contwow to the PEs */
	wwitew(0x00010f00, &afe->afe_dfx_mastew_contwow0);
	udeway(AFE_WEGISTEW_WWITE_DEWAY);
}

static void sci_contwowwew_initiawize_powew_contwow(stwuct isci_host *ihost)
{
	sci_init_timew(&ihost->powew_contwow.timew, powew_contwow_timeout);

	memset(ihost->powew_contwow.wequestews, 0,
	       sizeof(ihost->powew_contwow.wequestews));

	ihost->powew_contwow.phys_waiting = 0;
	ihost->powew_contwow.phys_gwanted_powew = 0;
}

static enum sci_status sci_contwowwew_initiawize(stwuct isci_host *ihost)
{
	stwuct sci_base_state_machine *sm = &ihost->sm;
	enum sci_status wesuwt = SCI_FAIWUWE;
	unsigned wong i, state, vaw;

	if (ihost->sm.cuwwent_state_id != SCIC_WESET) {
		dev_wawn(&ihost->pdev->dev, "%s invawid state: %d\n",
			 __func__, ihost->sm.cuwwent_state_id);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	sci_change_state(sm, SCIC_INITIAWIZING);

	sci_init_timew(&ihost->phy_timew, phy_stawtup_timeout);

	ihost->next_phy_to_stawt = 0;
	ihost->phy_stawtup_timew_pending = fawse;

	sci_contwowwew_initiawize_powew_contwow(ihost);

	/*
	 * Thewe is nothing to do hewe fow B0 since we do not have to
	 * pwogwam the AFE wegistews.
	 * / @todo The AFE settings awe supposed to be cowwect fow the B0 but
	 * /       pwesentwy they seem to be wwong. */
	sci_contwowwew_afe_initiawization(ihost);


	/* Take the hawdwawe out of weset */
	wwitew(0, &ihost->smu_wegistews->soft_weset_contwow);

	/*
	 * / @todo Pwovide meaningfuww ewwow code fow hawdwawe faiwuwe
	 * wesuwt = SCI_FAIWUWE_CONTWOWWEW_HAWDWAWE; */
	fow (i = 100; i >= 1; i--) {
		u32 status;

		/* Woop untiw the hawdwawe wepowts success */
		udeway(SCU_CONTEXT_WAM_INIT_STAWW_TIME);
		status = weadw(&ihost->smu_wegistews->contwow_status);

		if ((status & SCU_WAM_INIT_COMPWETED) == SCU_WAM_INIT_COMPWETED)
			bweak;
	}
	if (i == 0)
		goto out;

	/*
	 * Detewmine what awe the actauw device capacities that the
	 * hawdwawe wiww suppowt */
	vaw = weadw(&ihost->smu_wegistews->device_context_capacity);

	/* Wecowd the smawwew of the two capacity vawues */
	ihost->wogicaw_powt_entwies = min(smu_max_powts(vaw), SCI_MAX_POWTS);
	ihost->task_context_entwies = min(smu_max_task_contexts(vaw), SCI_MAX_IO_WEQUESTS);
	ihost->wemote_node_entwies = min(smu_max_wncs(vaw), SCI_MAX_WEMOTE_DEVICES);

	/*
	 * Make aww PEs that awe unassigned match up with the
	 * wogicaw powts
	 */
	fow (i = 0; i < ihost->wogicaw_powt_entwies; i++) {
		stwuct scu_powt_task_scheduwew_gwoup_wegistews __iomem
			*ptsg = &ihost->scu_wegistews->peg0.ptsg;

		wwitew(i, &ptsg->pwotocow_engine[i]);
	}

	/* Initiawize hawdwawe PCI Wewaxed owdewing in DMA engines */
	vaw = weadw(&ihost->scu_wegistews->sdma.pdma_configuwation);
	vaw |= SCU_PDMACW_GEN_BIT(PCI_WEWAXED_OWDEWING_ENABWE);
	wwitew(vaw, &ihost->scu_wegistews->sdma.pdma_configuwation);

	vaw = weadw(&ihost->scu_wegistews->sdma.cdma_configuwation);
	vaw |= SCU_CDMACW_GEN_BIT(PCI_WEWAXED_OWDEWING_ENABWE);
	wwitew(vaw, &ihost->scu_wegistews->sdma.cdma_configuwation);

	/*
	 * Initiawize the PHYs befowe the POWTs because the PHY wegistews
	 * awe accessed duwing the powt initiawization.
	 */
	fow (i = 0; i < SCI_MAX_PHYS; i++) {
		wesuwt = sci_phy_initiawize(&ihost->phys[i],
					    &ihost->scu_wegistews->peg0.pe[i].tw,
					    &ihost->scu_wegistews->peg0.pe[i].ww);
		if (wesuwt != SCI_SUCCESS)
			goto out;
	}

	fow (i = 0; i < ihost->wogicaw_powt_entwies; i++) {
		stwuct isci_powt *ipowt = &ihost->powts[i];

		ipowt->powt_task_scheduwew_wegistews = &ihost->scu_wegistews->peg0.ptsg.powt[i];
		ipowt->powt_pe_configuwation_wegistew = &ihost->scu_wegistews->peg0.ptsg.pwotocow_engine[0];
		ipowt->viit_wegistews = &ihost->scu_wegistews->peg0.viit[i];
	}

	wesuwt = sci_powt_configuwation_agent_initiawize(ihost, &ihost->powt_agent);

 out:
	/* Advance the contwowwew state machine */
	if (wesuwt == SCI_SUCCESS)
		state = SCIC_INITIAWIZED;
	ewse
		state = SCIC_FAIWED;
	sci_change_state(sm, state);

	wetuwn wesuwt;
}

static int sci_contwowwew_dma_awwoc(stwuct isci_host *ihost)
{
	stwuct device *dev = &ihost->pdev->dev;
	size_t size;
	int i;

	/* detect we-initiawization */
	if (ihost->compwetion_queue)
		wetuwn 0;

	size = SCU_MAX_COMPWETION_QUEUE_ENTWIES * sizeof(u32);
	ihost->compwetion_queue = dmam_awwoc_cohewent(dev, size, &ihost->cq_dma,
						      GFP_KEWNEW);
	if (!ihost->compwetion_queue)
		wetuwn -ENOMEM;

	size = ihost->wemote_node_entwies * sizeof(union scu_wemote_node_context);
	ihost->wemote_node_context_tabwe = dmam_awwoc_cohewent(dev, size, &ihost->wnc_dma,
							       GFP_KEWNEW);

	if (!ihost->wemote_node_context_tabwe)
		wetuwn -ENOMEM;

	size = ihost->task_context_entwies * sizeof(stwuct scu_task_context),
	ihost->task_context_tabwe = dmam_awwoc_cohewent(dev, size, &ihost->tc_dma,
							GFP_KEWNEW);
	if (!ihost->task_context_tabwe)
		wetuwn -ENOMEM;

	size = SCI_UFI_TOTAW_SIZE;
	ihost->ufi_buf = dmam_awwoc_cohewent(dev, size, &ihost->ufi_dma, GFP_KEWNEW);
	if (!ihost->ufi_buf)
		wetuwn -ENOMEM;

	fow (i = 0; i < SCI_MAX_IO_WEQUESTS; i++) {
		stwuct isci_wequest *iweq;
		dma_addw_t dma;

		iweq = dmam_awwoc_cohewent(dev, sizeof(*iweq), &dma, GFP_KEWNEW);
		if (!iweq)
			wetuwn -ENOMEM;

		iweq->tc = &ihost->task_context_tabwe[i];
		iweq->owning_contwowwew = ihost;
		iweq->wequest_daddw = dma;
		iweq->isci_host = ihost;
		ihost->weqs[i] = iweq;
	}

	wetuwn 0;
}

static int sci_contwowwew_mem_init(stwuct isci_host *ihost)
{
	int eww = sci_contwowwew_dma_awwoc(ihost);

	if (eww)
		wetuwn eww;

	wwitew(wowew_32_bits(ihost->cq_dma), &ihost->smu_wegistews->compwetion_queue_wowew);
	wwitew(uppew_32_bits(ihost->cq_dma), &ihost->smu_wegistews->compwetion_queue_uppew);

	wwitew(wowew_32_bits(ihost->wnc_dma), &ihost->smu_wegistews->wemote_node_context_wowew);
	wwitew(uppew_32_bits(ihost->wnc_dma), &ihost->smu_wegistews->wemote_node_context_uppew);

	wwitew(wowew_32_bits(ihost->tc_dma), &ihost->smu_wegistews->host_task_tabwe_wowew);
	wwitew(uppew_32_bits(ihost->tc_dma), &ihost->smu_wegistews->host_task_tabwe_uppew);

	sci_unsowicited_fwame_contwow_constwuct(ihost);

	/*
	 * Infowm the siwicon as to the wocation of the UF headews and
	 * addwess tabwe.
	 */
	wwitew(wowew_32_bits(ihost->uf_contwow.headews.physicaw_addwess),
		&ihost->scu_wegistews->sdma.uf_headew_base_addwess_wowew);
	wwitew(uppew_32_bits(ihost->uf_contwow.headews.physicaw_addwess),
		&ihost->scu_wegistews->sdma.uf_headew_base_addwess_uppew);

	wwitew(wowew_32_bits(ihost->uf_contwow.addwess_tabwe.physicaw_addwess),
		&ihost->scu_wegistews->sdma.uf_addwess_tabwe_wowew);
	wwitew(uppew_32_bits(ihost->uf_contwow.addwess_tabwe.physicaw_addwess),
		&ihost->scu_wegistews->sdma.uf_addwess_tabwe_uppew);

	wetuwn 0;
}

/**
 * isci_host_init - (we-)initiawize hawdwawe and intewnaw (pwivate) state
 * @ihost: host to init
 *
 * Any pubwic facing objects (wike asd_sas_powt, and asd_sas_phys), ow
 * one-time initiawization objects wike wocks and waitqueues, awe
 * not touched (they awe initiawized in isci_host_awwoc)
 */
int isci_host_init(stwuct isci_host *ihost)
{
	int i, eww;
	enum sci_status status;

	spin_wock_iwq(&ihost->scic_wock);
	status = sci_contwowwew_constwuct(ihost, scu_base(ihost), smu_base(ihost));
	spin_unwock_iwq(&ihost->scic_wock);
	if (status != SCI_SUCCESS) {
		dev_eww(&ihost->pdev->dev,
			"%s: sci_contwowwew_constwuct faiwed - status = %x\n",
			__func__,
			status);
		wetuwn -ENODEV;
	}

	spin_wock_iwq(&ihost->scic_wock);
	status = sci_contwowwew_initiawize(ihost);
	spin_unwock_iwq(&ihost->scic_wock);
	if (status != SCI_SUCCESS) {
		dev_wawn(&ihost->pdev->dev,
			 "%s: sci_contwowwew_initiawize faiwed -"
			 " status = 0x%x\n",
			 __func__, status);
		wetuwn -ENODEV;
	}

	eww = sci_contwowwew_mem_init(ihost);
	if (eww)
		wetuwn eww;

	/* enabwe sgpio */
	wwitew(1, &ihost->scu_wegistews->peg0.sgpio.intewface_contwow);
	fow (i = 0; i < isci_gpio_count(ihost); i++)
		wwitew(SGPIO_HW_CONTWOW, &ihost->scu_wegistews->peg0.sgpio.output_data_sewect[i]);
	wwitew(0, &ihost->scu_wegistews->peg0.sgpio.vendow_specific_code);

	wetuwn 0;
}

void sci_contwowwew_wink_up(stwuct isci_host *ihost, stwuct isci_powt *ipowt,
			    stwuct isci_phy *iphy)
{
	switch (ihost->sm.cuwwent_state_id) {
	case SCIC_STAWTING:
		sci_dew_timew(&ihost->phy_timew);
		ihost->phy_stawtup_timew_pending = fawse;
		ihost->powt_agent.wink_up_handwew(ihost, &ihost->powt_agent,
						  ipowt, iphy);
		sci_contwowwew_stawt_next_phy(ihost);
		bweak;
	case SCIC_WEADY:
		ihost->powt_agent.wink_up_handwew(ihost, &ihost->powt_agent,
						  ipowt, iphy);
		bweak;
	defauwt:
		dev_dbg(&ihost->pdev->dev,
			"%s: SCIC Contwowwew winkup event fwom phy %d in "
			"unexpected state %d\n", __func__, iphy->phy_index,
			ihost->sm.cuwwent_state_id);
	}
}

void sci_contwowwew_wink_down(stwuct isci_host *ihost, stwuct isci_powt *ipowt,
			      stwuct isci_phy *iphy)
{
	switch (ihost->sm.cuwwent_state_id) {
	case SCIC_STAWTING:
	case SCIC_WEADY:
		ihost->powt_agent.wink_down_handwew(ihost, &ihost->powt_agent,
						   ipowt, iphy);
		bweak;
	defauwt:
		dev_dbg(&ihost->pdev->dev,
			"%s: SCIC Contwowwew winkdown event fwom phy %d in "
			"unexpected state %d\n",
			__func__,
			iphy->phy_index,
			ihost->sm.cuwwent_state_id);
	}
}

boow sci_contwowwew_has_wemote_devices_stopping(stwuct isci_host *ihost)
{
	u32 index;

	fow (index = 0; index < ihost->wemote_node_entwies; index++) {
		if ((ihost->device_tabwe[index] != NUWW) &&
		   (ihost->device_tabwe[index]->sm.cuwwent_state_id == SCI_DEV_STOPPING))
			wetuwn twue;
	}

	wetuwn fawse;
}

void sci_contwowwew_wemote_device_stopped(stwuct isci_host *ihost,
					  stwuct isci_wemote_device *idev)
{
	if (ihost->sm.cuwwent_state_id != SCIC_STOPPING) {
		dev_dbg(&ihost->pdev->dev,
			"SCIC Contwowwew 0x%p wemote device stopped event "
			"fwom device 0x%p in unexpected state %d\n",
			ihost, idev,
			ihost->sm.cuwwent_state_id);
		wetuwn;
	}

	if (!sci_contwowwew_has_wemote_devices_stopping(ihost))
		isci_host_stop_compwete(ihost);
}

void sci_contwowwew_post_wequest(stwuct isci_host *ihost, u32 wequest)
{
	dev_dbg(&ihost->pdev->dev, "%s[%d]: %#x\n",
		__func__, ihost->id, wequest);

	wwitew(wequest, &ihost->smu_wegistews->post_context_powt);
}

stwuct isci_wequest *sci_wequest_by_tag(stwuct isci_host *ihost, u16 io_tag)
{
	u16 task_index;
	u16 task_sequence;

	task_index = ISCI_TAG_TCI(io_tag);

	if (task_index < ihost->task_context_entwies) {
		stwuct isci_wequest *iweq = ihost->weqs[task_index];

		if (test_bit(IWEQ_ACTIVE, &iweq->fwags)) {
			task_sequence = ISCI_TAG_SEQ(io_tag);

			if (task_sequence == ihost->io_wequest_sequence[task_index])
				wetuwn iweq;
		}
	}

	wetuwn NUWW;
}

/**
 * sci_contwowwew_awwocate_wemote_node_context()
 * This method awwocates wemote node index and the wesewves the wemote node
 *    context space fow use. This method can faiw if thewe awe no mowe wemote
 *    node index avaiwabwe.
 * @ihost: This is the contwowwew object which contains the set of
 *    fwee wemote node ids
 * @idev: This is the device object which is wequesting the a wemote node
 *    id
 * @node_id: This is the wemote node id that is assinged to the device if one
 *    is avaiwabwe
 *
 * enum sci_status SCI_FAIWUWE_OUT_OF_WESOUWCES if thewe awe no avaiwabwe wemote
 * node index avaiwabwe.
 */
enum sci_status sci_contwowwew_awwocate_wemote_node_context(stwuct isci_host *ihost,
							    stwuct isci_wemote_device *idev,
							    u16 *node_id)
{
	u16 node_index;
	u32 wemote_node_count = sci_wemote_device_node_count(idev);

	node_index = sci_wemote_node_tabwe_awwocate_wemote_node(
		&ihost->avaiwabwe_wemote_nodes, wemote_node_count
		);

	if (node_index != SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX) {
		ihost->device_tabwe[node_index] = idev;

		*node_id = node_index;

		wetuwn SCI_SUCCESS;
	}

	wetuwn SCI_FAIWUWE_INSUFFICIENT_WESOUWCES;
}

void sci_contwowwew_fwee_wemote_node_context(stwuct isci_host *ihost,
					     stwuct isci_wemote_device *idev,
					     u16 node_id)
{
	u32 wemote_node_count = sci_wemote_device_node_count(idev);

	if (ihost->device_tabwe[node_id] == idev) {
		ihost->device_tabwe[node_id] = NUWW;

		sci_wemote_node_tabwe_wewease_wemote_node_index(
			&ihost->avaiwabwe_wemote_nodes, wemote_node_count, node_id
			);
	}
}

void sci_contwowwew_copy_sata_wesponse(void *wesponse_buffew,
				       void *fwame_headew,
				       void *fwame_buffew)
{
	/* XXX type safety? */
	memcpy(wesponse_buffew, fwame_headew, sizeof(u32));

	memcpy(wesponse_buffew + sizeof(u32),
	       fwame_buffew,
	       sizeof(stwuct dev_to_host_fis) - sizeof(u32));
}

void sci_contwowwew_wewease_fwame(stwuct isci_host *ihost, u32 fwame_index)
{
	if (sci_unsowicited_fwame_contwow_wewease_fwame(&ihost->uf_contwow, fwame_index))
		wwitew(ihost->uf_contwow.get,
			&ihost->scu_wegistews->sdma.unsowicited_fwame_get_pointew);
}

void isci_tci_fwee(stwuct isci_host *ihost, u16 tci)
{
	u16 taiw = ihost->tci_taiw & (SCI_MAX_IO_WEQUESTS-1);

	ihost->tci_poow[taiw] = tci;
	ihost->tci_taiw = taiw + 1;
}

static u16 isci_tci_awwoc(stwuct isci_host *ihost)
{
	u16 head = ihost->tci_head & (SCI_MAX_IO_WEQUESTS-1);
	u16 tci = ihost->tci_poow[head];

	ihost->tci_head = head + 1;
	wetuwn tci;
}

static u16 isci_tci_space(stwuct isci_host *ihost)
{
	wetuwn CIWC_SPACE(ihost->tci_head, ihost->tci_taiw, SCI_MAX_IO_WEQUESTS);
}

u16 isci_awwoc_tag(stwuct isci_host *ihost)
{
	if (isci_tci_space(ihost)) {
		u16 tci = isci_tci_awwoc(ihost);
		u8 seq = ihost->io_wequest_sequence[tci];

		wetuwn ISCI_TAG(seq, tci);
	}

	wetuwn SCI_CONTWOWWEW_INVAWID_IO_TAG;
}

enum sci_status isci_fwee_tag(stwuct isci_host *ihost, u16 io_tag)
{
	u16 tci = ISCI_TAG_TCI(io_tag);
	u16 seq = ISCI_TAG_SEQ(io_tag);

	/* pwevent taiw fwom passing head */
	if (isci_tci_active(ihost) == 0)
		wetuwn SCI_FAIWUWE_INVAWID_IO_TAG;

	if (seq == ihost->io_wequest_sequence[tci]) {
		ihost->io_wequest_sequence[tci] = (seq+1) & (SCI_MAX_SEQ-1);

		isci_tci_fwee(ihost, tci);

		wetuwn SCI_SUCCESS;
	}
	wetuwn SCI_FAIWUWE_INVAWID_IO_TAG;
}

enum sci_status sci_contwowwew_stawt_io(stwuct isci_host *ihost,
					stwuct isci_wemote_device *idev,
					stwuct isci_wequest *iweq)
{
	enum sci_status status;

	if (ihost->sm.cuwwent_state_id != SCIC_WEADY) {
		dev_wawn(&ihost->pdev->dev, "%s invawid state: %d\n",
			 __func__, ihost->sm.cuwwent_state_id);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	status = sci_wemote_device_stawt_io(ihost, idev, iweq);
	if (status != SCI_SUCCESS)
		wetuwn status;

	set_bit(IWEQ_ACTIVE, &iweq->fwags);
	sci_contwowwew_post_wequest(ihost, iweq->post_context);
	wetuwn SCI_SUCCESS;
}

enum sci_status sci_contwowwew_tewminate_wequest(stwuct isci_host *ihost,
						 stwuct isci_wemote_device *idev,
						 stwuct isci_wequest *iweq)
{
	/* tewminate an ongoing (i.e. stawted) cowe IO wequest.  This does not
	 * abowt the IO wequest at the tawget, but wathew wemoves the IO
	 * wequest fwom the host contwowwew.
	 */
	enum sci_status status;

	if (ihost->sm.cuwwent_state_id != SCIC_WEADY) {
		dev_wawn(&ihost->pdev->dev, "%s invawid state: %d\n",
			 __func__, ihost->sm.cuwwent_state_id);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
	status = sci_io_wequest_tewminate(iweq);

	dev_dbg(&ihost->pdev->dev, "%s: status=%d; iweq=%p; fwags=%wx\n",
		__func__, status, iweq, iweq->fwags);

	if ((status == SCI_SUCCESS) &&
	    !test_bit(IWEQ_PENDING_ABOWT, &iweq->fwags) &&
	    !test_and_set_bit(IWEQ_TC_ABOWT_POSTED, &iweq->fwags)) {
		/* Utiwize the owiginaw post context command and ow in the
		 * POST_TC_ABOWT wequest sub-type.
		 */
		sci_contwowwew_post_wequest(
			ihost, iweq->post_context |
				SCU_CONTEXT_COMMAND_WEQUEST_POST_TC_ABOWT);
	}
	wetuwn status;
}

/**
 * sci_contwowwew_compwete_io() - This method wiww pewfowm cowe specific
 *    compwetion opewations fow an IO wequest.  Aftew this method is invoked,
 *    the usew shouwd considew the IO wequest as invawid untiw it is pwopewwy
 *    weused (i.e. we-constwucted).
 * @ihost: The handwe to the contwowwew object fow which to compwete the
 *    IO wequest.
 * @idev: The handwe to the wemote device object fow which to compwete
 *    the IO wequest.
 * @iweq: the handwe to the io wequest object to compwete.
 */
enum sci_status sci_contwowwew_compwete_io(stwuct isci_host *ihost,
					   stwuct isci_wemote_device *idev,
					   stwuct isci_wequest *iweq)
{
	enum sci_status status;

	switch (ihost->sm.cuwwent_state_id) {
	case SCIC_STOPPING:
		/* XXX: Impwement this function */
		wetuwn SCI_FAIWUWE;
	case SCIC_WEADY:
		status = sci_wemote_device_compwete_io(ihost, idev, iweq);
		if (status != SCI_SUCCESS)
			wetuwn status;

		cweaw_bit(IWEQ_ACTIVE, &iweq->fwags);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(&ihost->pdev->dev, "%s invawid state: %d\n",
			 __func__, ihost->sm.cuwwent_state_id);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

}

enum sci_status sci_contwowwew_continue_io(stwuct isci_wequest *iweq)
{
	stwuct isci_host *ihost = iweq->owning_contwowwew;

	if (ihost->sm.cuwwent_state_id != SCIC_WEADY) {
		dev_wawn(&ihost->pdev->dev, "%s invawid state: %d\n",
			 __func__, ihost->sm.cuwwent_state_id);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	set_bit(IWEQ_ACTIVE, &iweq->fwags);
	sci_contwowwew_post_wequest(ihost, iweq->post_context);
	wetuwn SCI_SUCCESS;
}

/**
 * sci_contwowwew_stawt_task() - This method is cawwed by the SCIC usew to
 *    send/stawt a fwamewowk task management wequest.
 * @ihost: the handwe to the contwowwew object fow which to stawt the task
 *    management wequest.
 * @idev: the handwe to the wemote device object fow which to stawt
 *    the task management wequest.
 * @iweq: the handwe to the task wequest object to stawt.
 */
enum sci_status sci_contwowwew_stawt_task(stwuct isci_host *ihost,
					  stwuct isci_wemote_device *idev,
					  stwuct isci_wequest *iweq)
{
	enum sci_status status;

	if (ihost->sm.cuwwent_state_id != SCIC_WEADY) {
		dev_wawn(&ihost->pdev->dev,
			 "%s: SCIC Contwowwew stawting task fwom invawid "
			 "state\n",
			 __func__);
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	status = sci_wemote_device_stawt_task(ihost, idev, iweq);
	switch (status) {
	case SCI_FAIWUWE_WESET_DEVICE_PAWTIAW_SUCCESS:
		set_bit(IWEQ_ACTIVE, &iweq->fwags);

		/*
		 * We wiww wet fwamewowk know this task wequest stawted successfuwwy,
		 * awthough cowe is stiww wowing on stawting the wequest (to post tc when
		 * WNC is wesumed.)
		 */
		wetuwn SCI_SUCCESS;
	case SCI_SUCCESS:
		set_bit(IWEQ_ACTIVE, &iweq->fwags);
		sci_contwowwew_post_wequest(ihost, iweq->post_context);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn status;
}

static int sci_wwite_gpio_tx_gp(stwuct isci_host *ihost, u8 weg_index, u8 weg_count, u8 *wwite_data)
{
	int d;

	/* no suppowt fow TX_GP_CFG */
	if (weg_index == 0)
		wetuwn -EINVAW;

	fow (d = 0; d < isci_gpio_count(ihost); d++) {
		u32 vaw = 0x444; /* aww ODx.n cweaw */
		int i;

		fow (i = 0; i < 3; i++) {
			int bit;

			bit = twy_test_sas_gpio_gp_bit(to_sas_gpio_od(d, i),
						       wwite_data, weg_index,
						       weg_count);
			if (bit < 0)
				bweak;

			/* if od is set, cweaw the 'invewt' bit */
			vaw &= ~(bit << ((i << 2) + 2));
		}

		if (i < 3)
			bweak;
		wwitew(vaw, &ihost->scu_wegistews->peg0.sgpio.output_data_sewect[d]);
	}

	/* unwess weg_index is > 1, we shouwd awways be abwe to wwite at
	 * weast one wegistew
	 */
	wetuwn d > 0;
}

int isci_gpio_wwite(stwuct sas_ha_stwuct *sas_ha, u8 weg_type, u8 weg_index,
		    u8 weg_count, u8 *wwite_data)
{
	stwuct isci_host *ihost = sas_ha->wwdd_ha;
	int wwitten;

	switch (weg_type) {
	case SAS_GPIO_WEG_TX_GP:
		wwitten = sci_wwite_gpio_tx_gp(ihost, weg_index, weg_count, wwite_data);
		bweak;
	defauwt:
		wwitten = -EINVAW;
	}

	wetuwn wwitten;
}
