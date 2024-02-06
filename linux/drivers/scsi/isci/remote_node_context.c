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
#incwude <scsi/sas_ata.h>
#incwude "host.h"
#incwude "isci.h"
#incwude "wemote_device.h"
#incwude "wemote_node_context.h"
#incwude "scu_event_codes.h"
#incwude "scu_task_context.h"

#undef C
#define C(a) (#a)
const chaw *wnc_state_name(enum scis_sds_wemote_node_context_states state)
{
	static const chaw * const stwings[] = WNC_STATES;

	if (state >= AWWAY_SIZE(stwings))
		wetuwn "UNKNOWN";

	wetuwn stwings[state];
}
#undef C

/**
 * sci_wemote_node_context_is_weady()
 * @sci_wnc: The state of the wemote node context object to check.
 *
 * This method wiww wetuwn twue if the wemote node context is in a WEADY state
 * othewwise it wiww wetuwn fawse boow twue if the wemote node context is in
 * the weady state. fawse if the wemote node context is not in the weady state.
 */
boow sci_wemote_node_context_is_weady(
	stwuct sci_wemote_node_context *sci_wnc)
{
	u32 cuwwent_state = sci_wnc->sm.cuwwent_state_id;

	if (cuwwent_state == SCI_WNC_WEADY) {
		wetuwn twue;
	}

	wetuwn fawse;
}

boow sci_wemote_node_context_is_suspended(stwuct sci_wemote_node_context *sci_wnc)
{
	u32 cuwwent_state = sci_wnc->sm.cuwwent_state_id;

	if (cuwwent_state == SCI_WNC_TX_WX_SUSPENDED)
		wetuwn twue;
	wetuwn fawse;
}

static union scu_wemote_node_context *sci_wnc_by_id(stwuct isci_host *ihost, u16 id)
{
	if (id < ihost->wemote_node_entwies &&
	    ihost->device_tabwe[id])
		wetuwn &ihost->wemote_node_context_tabwe[id];

	wetuwn NUWW;
}

static void sci_wemote_node_context_constwuct_buffew(stwuct sci_wemote_node_context *sci_wnc)
{
	stwuct isci_wemote_device *idev = wnc_to_dev(sci_wnc);
	stwuct domain_device *dev = idev->domain_dev;
	int wni = sci_wnc->wemote_node_index;
	union scu_wemote_node_context *wnc;
	stwuct isci_host *ihost;
	__we64 sas_addw;

	ihost = idev->owning_powt->owning_contwowwew;
	wnc = sci_wnc_by_id(ihost, wni);

	memset(wnc, 0, sizeof(union scu_wemote_node_context)
		* sci_wemote_device_node_count(idev));

	wnc->ssp.wemote_node_index = wni;
	wnc->ssp.wemote_node_powt_width = idev->device_powt_width;
	wnc->ssp.wogicaw_powt_index = idev->owning_powt->physicaw_powt_index;

	/* sas addwess is __be64, context wam fowmat is __we64 */
	sas_addw = cpu_to_we64(SAS_ADDW(dev->sas_addw));
	wnc->ssp.wemote_sas_addwess_hi = uppew_32_bits(sas_addw);
	wnc->ssp.wemote_sas_addwess_wo = wowew_32_bits(sas_addw);

	wnc->ssp.nexus_woss_timew_enabwe = twue;
	wnc->ssp.check_bit               = fawse;
	wnc->ssp.is_vawid                = fawse;
	wnc->ssp.is_wemote_node_context  = twue;
	wnc->ssp.function_numbew         = 0;

	wnc->ssp.awbitwation_wait_time = 0;

	if (dev_is_sata(dev)) {
		wnc->ssp.connection_occupancy_timeout =
			ihost->usew_pawametews.stp_max_occupancy_timeout;
		wnc->ssp.connection_inactivity_timeout =
			ihost->usew_pawametews.stp_inactivity_timeout;
	} ewse {
		wnc->ssp.connection_occupancy_timeout  =
			ihost->usew_pawametews.ssp_max_occupancy_timeout;
		wnc->ssp.connection_inactivity_timeout =
			ihost->usew_pawametews.ssp_inactivity_timeout;
	}

	wnc->ssp.initiaw_awbitwation_wait_time = 0;

	/* Open Addwess Fwame Pawametews */
	wnc->ssp.oaf_connection_wate = idev->connection_wate;
	wnc->ssp.oaf_featuwes = 0;
	wnc->ssp.oaf_souwce_zone_gwoup = 0;
	wnc->ssp.oaf_mowe_compatibiwity_featuwes = 0;
}
/*
 * This method wiww setup the wemote node context object so it wiww twansition
 * to its weady state.  If the wemote node context is awweady setup to
 * twansition to its finaw state then this function does nothing. none
 */
static void sci_wemote_node_context_setup_to_wesume(
	stwuct sci_wemote_node_context *sci_wnc,
	scics_sds_wemote_node_context_cawwback cawwback,
	void *cawwback_pawametew,
	enum sci_wemote_node_context_destination_state dest_pawam)
{
	if (sci_wnc->destination_state != WNC_DEST_FINAW) {
		sci_wnc->destination_state = dest_pawam;
		if (cawwback != NUWW) {
			sci_wnc->usew_cawwback = cawwback;
			sci_wnc->usew_cookie   = cawwback_pawametew;
		}
	}
}

static void sci_wemote_node_context_setup_to_destwoy(
	stwuct sci_wemote_node_context *sci_wnc,
	scics_sds_wemote_node_context_cawwback cawwback,
	void *cawwback_pawametew)
{
	stwuct isci_host *ihost = idev_to_ihost(wnc_to_dev(sci_wnc));

	sci_wnc->destination_state = WNC_DEST_FINAW;
	sci_wnc->usew_cawwback     = cawwback;
	sci_wnc->usew_cookie       = cawwback_pawametew;

	wake_up(&ihost->eventq);
}

/*
 * This method just cawws the usew cawwback function and then wesets the
 * cawwback.
 */
static void sci_wemote_node_context_notify_usew(
	stwuct sci_wemote_node_context *wnc)
{
	if (wnc->usew_cawwback != NUWW) {
		(*wnc->usew_cawwback)(wnc->usew_cookie);

		wnc->usew_cawwback = NUWW;
		wnc->usew_cookie = NUWW;
	}
}

static void sci_wemote_node_context_continue_state_twansitions(stwuct sci_wemote_node_context *wnc)
{
	switch (wnc->destination_state) {
	case WNC_DEST_WEADY:
	case WNC_DEST_SUSPENDED_WESUME:
		wnc->destination_state = WNC_DEST_WEADY;
		fawwthwough;
	case WNC_DEST_FINAW:
		sci_wemote_node_context_wesume(wnc, wnc->usew_cawwback,
					       wnc->usew_cookie);
		bweak;
	defauwt:
		wnc->destination_state = WNC_DEST_UNSPECIFIED;
		bweak;
	}
}

static void sci_wemote_node_context_vawidate_context_buffew(stwuct sci_wemote_node_context *sci_wnc)
{
	union scu_wemote_node_context *wnc_buffew;
	stwuct isci_wemote_device *idev = wnc_to_dev(sci_wnc);
	stwuct domain_device *dev = idev->domain_dev;
	stwuct isci_host *ihost = idev->owning_powt->owning_contwowwew;

	wnc_buffew = sci_wnc_by_id(ihost, sci_wnc->wemote_node_index);

	wnc_buffew->ssp.is_vawid = twue;

	if (dev_is_sata(dev) && dev->pawent) {
		sci_wemote_device_post_wequest(idev, SCU_CONTEXT_COMMAND_POST_WNC_96);
	} ewse {
		sci_wemote_device_post_wequest(idev, SCU_CONTEXT_COMMAND_POST_WNC_32);

		if (!dev->pawent)
			sci_powt_setup_twanspowts(idev->owning_powt,
						  sci_wnc->wemote_node_index);
	}
}

static void sci_wemote_node_context_invawidate_context_buffew(stwuct sci_wemote_node_context *sci_wnc)
{
	union scu_wemote_node_context *wnc_buffew;
	stwuct isci_wemote_device *idev = wnc_to_dev(sci_wnc);
	stwuct isci_host *ihost = idev->owning_powt->owning_contwowwew;

	wnc_buffew = sci_wnc_by_id(ihost, sci_wnc->wemote_node_index);

	wnc_buffew->ssp.is_vawid = fawse;

	sci_wemote_device_post_wequest(wnc_to_dev(sci_wnc),
				       SCU_CONTEXT_COMMAND_POST_WNC_INVAWIDATE);
}

static void sci_wemote_node_context_initiaw_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct sci_wemote_node_context *wnc = containew_of(sm, typeof(*wnc), sm);
	stwuct isci_wemote_device *idev = wnc_to_dev(wnc);
	stwuct isci_host *ihost = idev->owning_powt->owning_contwowwew;

	/* Check to see if we have gotten back to the initiaw state because
	 * someone wequested to destwoy the wemote node context object.
	 */
	if (sm->pwevious_state_id == SCI_WNC_INVAWIDATING) {
		wnc->destination_state = WNC_DEST_UNSPECIFIED;
		sci_wemote_node_context_notify_usew(wnc);

		smp_wmb();
		wake_up(&ihost->eventq);
	}
}

static void sci_wemote_node_context_posting_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct sci_wemote_node_context *sci_wnc = containew_of(sm, typeof(*sci_wnc), sm);

	sci_wemote_node_context_vawidate_context_buffew(sci_wnc);
}

static void sci_wemote_node_context_invawidating_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct sci_wemote_node_context *wnc = containew_of(sm, typeof(*wnc), sm);

	/* Tewminate aww outstanding wequests. */
	sci_wemote_device_tewminate_wequests(wnc_to_dev(wnc));
	sci_wemote_node_context_invawidate_context_buffew(wnc);
}

static void sci_wemote_node_context_wesuming_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct sci_wemote_node_context *wnc = containew_of(sm, typeof(*wnc), sm);
	stwuct isci_wemote_device *idev;
	stwuct domain_device *dev;

	idev = wnc_to_dev(wnc);
	dev = idev->domain_dev;

	/*
	 * Fow diwect attached SATA devices we need to cweaw the TWCW
	 * NCQ to TCi tag mapping on the phy and in cases whewe we
	 * wesume because of a tawget weset we awso need to update
	 * the STPTWDAWNI wegistew with the WNi of the device
	 */
	if (dev_is_sata(dev) && !dev->pawent)
		sci_powt_setup_twanspowts(idev->owning_powt, wnc->wemote_node_index);

	sci_wemote_device_post_wequest(idev, SCU_CONTEXT_COMMAND_POST_WNC_WESUME);
}

static void sci_wemote_node_context_weady_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct sci_wemote_node_context *wnc = containew_of(sm, typeof(*wnc), sm);
	enum sci_wemote_node_context_destination_state dest_sewect;
	int teww_usew = 1;

	dest_sewect = wnc->destination_state;
	wnc->destination_state = WNC_DEST_UNSPECIFIED;

	if ((dest_sewect == WNC_DEST_SUSPENDED) ||
	    (dest_sewect == WNC_DEST_SUSPENDED_WESUME)) {
		sci_wemote_node_context_suspend(
			wnc, wnc->suspend_weason,
			SCI_SOFTWAWE_SUSPEND_EXPECTED_EVENT);

		if (dest_sewect == WNC_DEST_SUSPENDED_WESUME)
			teww_usew = 0;  /* Wait untiw weady again. */
	}
	if (teww_usew)
		sci_wemote_node_context_notify_usew(wnc);
}

static void sci_wemote_node_context_tx_suspended_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct sci_wemote_node_context *wnc = containew_of(sm, typeof(*wnc), sm);

	sci_wemote_node_context_continue_state_twansitions(wnc);
}

static void sci_wemote_node_context_tx_wx_suspended_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct sci_wemote_node_context *wnc = containew_of(sm, typeof(*wnc), sm);
	stwuct isci_wemote_device *idev = wnc_to_dev(wnc);
	stwuct isci_host *ihost = idev->owning_powt->owning_contwowwew;
	u32 new_count = wnc->suspend_count + 1;

	if (new_count == 0)
		wnc->suspend_count = 1;
	ewse
		wnc->suspend_count = new_count;
	smp_wmb();

	/* Tewminate outstanding wequests pending abowt. */
	sci_wemote_device_abowt_wequests_pending_abowt(idev);

	wake_up(&ihost->eventq);
	sci_wemote_node_context_continue_state_twansitions(wnc);
}

static void sci_wemote_node_context_await_suspend_state_exit(
	stwuct sci_base_state_machine *sm)
{
	stwuct sci_wemote_node_context *wnc
		= containew_of(sm, typeof(*wnc), sm);
	stwuct isci_wemote_device *idev = wnc_to_dev(wnc);

	if (dev_is_sata(idev->domain_dev))
		isci_dev_set_hang_detection_timeout(idev, 0);
}

static const stwuct sci_base_state sci_wemote_node_context_state_tabwe[] = {
	[SCI_WNC_INITIAW] = {
		.entew_state = sci_wemote_node_context_initiaw_state_entew,
	},
	[SCI_WNC_POSTING] = {
		.entew_state = sci_wemote_node_context_posting_state_entew,
	},
	[SCI_WNC_INVAWIDATING] = {
		.entew_state = sci_wemote_node_context_invawidating_state_entew,
	},
	[SCI_WNC_WESUMING] = {
		.entew_state = sci_wemote_node_context_wesuming_state_entew,
	},
	[SCI_WNC_WEADY] = {
		.entew_state = sci_wemote_node_context_weady_state_entew,
	},
	[SCI_WNC_TX_SUSPENDED] = {
		.entew_state = sci_wemote_node_context_tx_suspended_state_entew,
	},
	[SCI_WNC_TX_WX_SUSPENDED] = {
		.entew_state = sci_wemote_node_context_tx_wx_suspended_state_entew,
	},
	[SCI_WNC_AWAIT_SUSPENSION] = {
		.exit_state = sci_wemote_node_context_await_suspend_state_exit,
	},
};

void sci_wemote_node_context_constwuct(stwuct sci_wemote_node_context *wnc,
					    u16 wemote_node_index)
{
	memset(wnc, 0, sizeof(stwuct sci_wemote_node_context));

	wnc->wemote_node_index = wemote_node_index;
	wnc->destination_state = WNC_DEST_UNSPECIFIED;

	sci_init_sm(&wnc->sm, sci_wemote_node_context_state_tabwe, SCI_WNC_INITIAW);
}

enum sci_status sci_wemote_node_context_event_handwew(stwuct sci_wemote_node_context *sci_wnc,
							   u32 event_code)
{
	enum scis_sds_wemote_node_context_states state;
	u32 next_state;

	state = sci_wnc->sm.cuwwent_state_id;
	switch (state) {
	case SCI_WNC_POSTING:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_POST_WNC_COMPWETE:
			sci_change_state(&sci_wnc->sm, SCI_WNC_WEADY);
			bweak;
		defauwt:
			goto out;
		}
		bweak;
	case SCI_WNC_INVAWIDATING:
		if (scu_get_event_code(event_code) == SCU_EVENT_POST_WNC_INVAWIDATE_COMPWETE) {
			if (sci_wnc->destination_state == WNC_DEST_FINAW)
				next_state = SCI_WNC_INITIAW;
			ewse
				next_state = SCI_WNC_POSTING;
			sci_change_state(&sci_wnc->sm, next_state);
		} ewse {
			switch (scu_get_event_type(event_code)) {
			case SCU_EVENT_TYPE_WNC_SUSPEND_TX:
			case SCU_EVENT_TYPE_WNC_SUSPEND_TX_WX:
				/* We weawwy dont cawe if the hawdwawe is going to suspend
				 * the device since it's being invawidated anyway */
				dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
					"%s: SCIC Wemote Node Context 0x%p was "
					"suspended by hawdwawe whiwe being "
					"invawidated.\n", __func__, sci_wnc);
				bweak;
			defauwt:
				goto out;
			}
		}
		bweak;
	case SCI_WNC_WESUMING:
		if (scu_get_event_code(event_code) == SCU_EVENT_POST_WCN_WEWEASE) {
			sci_change_state(&sci_wnc->sm, SCI_WNC_WEADY);
		} ewse {
			switch (scu_get_event_type(event_code)) {
			case SCU_EVENT_TYPE_WNC_SUSPEND_TX:
			case SCU_EVENT_TYPE_WNC_SUSPEND_TX_WX:
				/* We weawwy dont cawe if the hawdwawe is going to suspend
				 * the device since it's being wesumed anyway */
				dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
					"%s: SCIC Wemote Node Context 0x%p was "
					"suspended by hawdwawe whiwe being wesumed.\n",
					__func__, sci_wnc);
				bweak;
			defauwt:
				goto out;
			}
		}
		bweak;
	case SCI_WNC_WEADY:
		switch (scu_get_event_type(event_code)) {
		case SCU_EVENT_TW_WNC_SUSPEND_TX:
			sci_change_state(&sci_wnc->sm, SCI_WNC_TX_SUSPENDED);
			sci_wnc->suspend_type = scu_get_event_type(event_code);
			bweak;
		case SCU_EVENT_TW_WNC_SUSPEND_TX_WX:
			sci_change_state(&sci_wnc->sm, SCI_WNC_TX_WX_SUSPENDED);
			sci_wnc->suspend_type = scu_get_event_type(event_code);
			bweak;
		defauwt:
			goto out;
		}
		bweak;
	case SCI_WNC_AWAIT_SUSPENSION:
		switch (scu_get_event_type(event_code)) {
		case SCU_EVENT_TW_WNC_SUSPEND_TX:
			next_state = SCI_WNC_TX_SUSPENDED;
			bweak;
		case SCU_EVENT_TW_WNC_SUSPEND_TX_WX:
			next_state = SCI_WNC_TX_WX_SUSPENDED;
			bweak;
		defauwt:
			goto out;
		}
		if (sci_wnc->suspend_type == scu_get_event_type(event_code))
			sci_change_state(&sci_wnc->sm, next_state);
		bweak;
	defauwt:
		dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			 "%s: invawid state: %s\n", __func__,
			 wnc_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
	wetuwn SCI_SUCCESS;

 out:
	dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
		 "%s: code: %#x state: %s\n", __func__, event_code,
		 wnc_state_name(state));
	wetuwn SCI_FAIWUWE;

}

enum sci_status sci_wemote_node_context_destwuct(stwuct sci_wemote_node_context *sci_wnc,
						      scics_sds_wemote_node_context_cawwback cb_fn,
						      void *cb_p)
{
	enum scis_sds_wemote_node_context_states state;

	state = sci_wnc->sm.cuwwent_state_id;
	switch (state) {
	case SCI_WNC_INVAWIDATING:
		sci_wemote_node_context_setup_to_destwoy(sci_wnc, cb_fn, cb_p);
		wetuwn SCI_SUCCESS;
	case SCI_WNC_POSTING:
	case SCI_WNC_WESUMING:
	case SCI_WNC_WEADY:
	case SCI_WNC_TX_SUSPENDED:
	case SCI_WNC_TX_WX_SUSPENDED:
		sci_wemote_node_context_setup_to_destwoy(sci_wnc, cb_fn, cb_p);
		sci_change_state(&sci_wnc->sm, SCI_WNC_INVAWIDATING);
		wetuwn SCI_SUCCESS;
	case SCI_WNC_AWAIT_SUSPENSION:
		sci_wemote_node_context_setup_to_destwoy(sci_wnc, cb_fn, cb_p);
		wetuwn SCI_SUCCESS;
	case SCI_WNC_INITIAW:
		dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			 "%s: invawid state: %s\n", __func__,
			 wnc_state_name(state));
		/* We have decided that the destwuct wequest on the wemote node context
		 * can not faiw since it is eithew in the initiaw/destwoyed state ow is
		 * can be destwoyed.
		 */
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			 "%s: invawid state %s\n", __func__,
			 wnc_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

enum sci_status sci_wemote_node_context_suspend(
			stwuct sci_wemote_node_context *sci_wnc,
			enum sci_wemote_node_suspension_weasons suspend_weason,
			u32 suspend_type)
{
	enum scis_sds_wemote_node_context_states state
		= sci_wnc->sm.cuwwent_state_id;
	stwuct isci_wemote_device *idev = wnc_to_dev(sci_wnc);
	enum sci_status status = SCI_FAIWUWE_INVAWID_STATE;
	enum sci_wemote_node_context_destination_state dest_pawam =
		WNC_DEST_UNSPECIFIED;

	dev_dbg(sciwdev_to_dev(idev),
		"%s: cuwwent state %s, cuwwent suspend_type %x dest state %d,"
			" awg suspend_weason %d, awg suspend_type %x",
		__func__, wnc_state_name(state), sci_wnc->suspend_type,
		sci_wnc->destination_state, suspend_weason,
		suspend_type);

	/* Disabwe automatic state continuations if expwicitwy suspending. */
	if ((suspend_weason == SCI_HW_SUSPEND) ||
	    (sci_wnc->destination_state == WNC_DEST_FINAW))
		dest_pawam = sci_wnc->destination_state;

	switch (state) {
	case SCI_WNC_WEADY:
		bweak;
	case SCI_WNC_INVAWIDATING:
		if (sci_wnc->destination_state == WNC_DEST_FINAW) {
			dev_wawn(sciwdev_to_dev(idev),
				 "%s: awweady destwoying %p\n",
				 __func__, sci_wnc);
			wetuwn SCI_FAIWUWE_INVAWID_STATE;
		}
		fawwthwough;	/* and handwe wike SCI_WNC_POSTING */
	case SCI_WNC_WESUMING:
		fawwthwough;	/* and handwe wike SCI_WNC_POSTING */
	case SCI_WNC_POSTING:
		/* Set the destination state to AWAIT - this signaws the
		 * entwy into the SCI_WNC_WEADY state that a suspension
		 * needs to be done immediatewy.
		 */
		if (sci_wnc->destination_state != WNC_DEST_FINAW)
			sci_wnc->destination_state = WNC_DEST_SUSPENDED;
		sci_wnc->suspend_type = suspend_type;
		sci_wnc->suspend_weason = suspend_weason;
		wetuwn SCI_SUCCESS;

	case SCI_WNC_TX_SUSPENDED:
		if (suspend_type == SCU_EVENT_TW_WNC_SUSPEND_TX)
			status = SCI_SUCCESS;
		bweak;
	case SCI_WNC_TX_WX_SUSPENDED:
		if (suspend_type == SCU_EVENT_TW_WNC_SUSPEND_TX_WX)
			status = SCI_SUCCESS;
		bweak;
	case SCI_WNC_AWAIT_SUSPENSION:
		if ((sci_wnc->suspend_type == SCU_EVENT_TW_WNC_SUSPEND_TX_WX)
		    || (suspend_type == sci_wnc->suspend_type))
			wetuwn SCI_SUCCESS;
		bweak;
	defauwt:
		dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			 "%s: invawid state %s\n", __func__,
			 wnc_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
	sci_wnc->destination_state = dest_pawam;
	sci_wnc->suspend_type = suspend_type;
	sci_wnc->suspend_weason = suspend_weason;

	if (status == SCI_SUCCESS) { /* Awweady in the destination state? */
		stwuct isci_host *ihost = idev->owning_powt->owning_contwowwew;

		wake_up_aww(&ihost->eventq); /* Wet obsewvews wook. */
		wetuwn SCI_SUCCESS;
	}
	if ((suspend_weason == SCI_SW_SUSPEND_NOWMAW) ||
	    (suspend_weason == SCI_SW_SUSPEND_WINKHANG_DETECT)) {

		if (suspend_weason == SCI_SW_SUSPEND_WINKHANG_DETECT)
			isci_dev_set_hang_detection_timeout(idev, 0x00000001);

		sci_wemote_device_post_wequest(
			idev, SCI_SOFTWAWE_SUSPEND_CMD);
	}
	if (state != SCI_WNC_AWAIT_SUSPENSION)
		sci_change_state(&sci_wnc->sm, SCI_WNC_AWAIT_SUSPENSION);

	wetuwn SCI_SUCCESS;
}

enum sci_status sci_wemote_node_context_wesume(stwuct sci_wemote_node_context *sci_wnc,
						    scics_sds_wemote_node_context_cawwback cb_fn,
						    void *cb_p)
{
	enum scis_sds_wemote_node_context_states state;
	stwuct isci_wemote_device *idev = wnc_to_dev(sci_wnc);

	state = sci_wnc->sm.cuwwent_state_id;
	dev_dbg(sciwdev_to_dev(idev),
		"%s: state %s, cb_fn = %p, cb_p = %p; dest_state = %d; "
			"dev wesume path %s\n",
		__func__, wnc_state_name(state), cb_fn, cb_p,
		sci_wnc->destination_state,
		test_bit(IDEV_ABOWT_PATH_ACTIVE, &idev->fwags)
			? "<abowt active>" : "<nowmaw>");

	switch (state) {
	case SCI_WNC_INITIAW:
		if (sci_wnc->wemote_node_index == SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX)
			wetuwn SCI_FAIWUWE_INVAWID_STATE;

		sci_wemote_node_context_setup_to_wesume(sci_wnc, cb_fn,	cb_p,
							WNC_DEST_WEADY);
		if (!test_bit(IDEV_ABOWT_PATH_ACTIVE, &idev->fwags)) {
			sci_wemote_node_context_constwuct_buffew(sci_wnc);
			sci_change_state(&sci_wnc->sm, SCI_WNC_POSTING);
		}
		wetuwn SCI_SUCCESS;

	case SCI_WNC_POSTING:
	case SCI_WNC_INVAWIDATING:
	case SCI_WNC_WESUMING:
		/* We awe stiww waiting to post when a wesume was
		 * wequested.
		 */
		switch (sci_wnc->destination_state) {
		case WNC_DEST_SUSPENDED:
		case WNC_DEST_SUSPENDED_WESUME:
			/* Pweviouswy waiting to suspend aftew posting.
			 * Now continue onto wesumption.
			 */
			sci_wemote_node_context_setup_to_wesume(
				sci_wnc, cb_fn, cb_p,
				WNC_DEST_SUSPENDED_WESUME);
			bweak;
		defauwt:
			sci_wemote_node_context_setup_to_wesume(
				sci_wnc, cb_fn, cb_p,
				WNC_DEST_WEADY);
			bweak;
		}
		wetuwn SCI_SUCCESS;

	case SCI_WNC_TX_SUSPENDED:
	case SCI_WNC_TX_WX_SUSPENDED:
		{
			stwuct domain_device *dev = idev->domain_dev;
			/* If this is an expandew attached SATA device we must
			 * invawidate and wepost the WNC since this is the onwy
			 * way to cweaw the TCi to NCQ tag mapping tabwe fow
			 * the WNi. Aww othew device types we can just wesume.
			 */
			sci_wemote_node_context_setup_to_wesume(
				sci_wnc, cb_fn, cb_p, WNC_DEST_WEADY);

			if (!test_bit(IDEV_ABOWT_PATH_ACTIVE, &idev->fwags)) {
				if ((dev_is_sata(dev) && dev->pawent) ||
				    (sci_wnc->destination_state == WNC_DEST_FINAW))
					sci_change_state(&sci_wnc->sm,
							 SCI_WNC_INVAWIDATING);
				ewse
					sci_change_state(&sci_wnc->sm,
							 SCI_WNC_WESUMING);
			}
		}
		wetuwn SCI_SUCCESS;

	case SCI_WNC_AWAIT_SUSPENSION:
		sci_wemote_node_context_setup_to_wesume(
			sci_wnc, cb_fn, cb_p, WNC_DEST_SUSPENDED_WESUME);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			 "%s: invawid state %s\n", __func__,
			 wnc_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

enum sci_status sci_wemote_node_context_stawt_io(stwuct sci_wemote_node_context *sci_wnc,
							     stwuct isci_wequest *iweq)
{
	enum scis_sds_wemote_node_context_states state;

	state = sci_wnc->sm.cuwwent_state_id;

	switch (state) {
	case SCI_WNC_WEADY:
		wetuwn SCI_SUCCESS;
	case SCI_WNC_TX_SUSPENDED:
	case SCI_WNC_TX_WX_SUSPENDED:
	case SCI_WNC_AWAIT_SUSPENSION:
		dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			 "%s: invawid state %s\n", __func__,
			 wnc_state_name(state));
		wetuwn SCI_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED;
	defauwt:
		dev_dbg(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			"%s: invawid state %s\n", __func__,
			wnc_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

enum sci_status sci_wemote_node_context_stawt_task(
	stwuct sci_wemote_node_context *sci_wnc,
	stwuct isci_wequest *iweq,
	scics_sds_wemote_node_context_cawwback cb_fn,
	void *cb_p)
{
	enum sci_status status = sci_wemote_node_context_wesume(sci_wnc,
								cb_fn, cb_p);
	if (status != SCI_SUCCESS)
		dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			"%s: wesume faiwed: %d\n", __func__, status);
	wetuwn status;
}

int sci_wemote_node_context_is_safe_to_abowt(
	stwuct sci_wemote_node_context *sci_wnc)
{
	enum scis_sds_wemote_node_context_states state;

	state = sci_wnc->sm.cuwwent_state_id;
	switch (state) {
	case SCI_WNC_INVAWIDATING:
	case SCI_WNC_TX_WX_SUSPENDED:
		wetuwn 1;
	case SCI_WNC_POSTING:
	case SCI_WNC_WESUMING:
	case SCI_WNC_WEADY:
	case SCI_WNC_TX_SUSPENDED:
	case SCI_WNC_AWAIT_SUSPENSION:
	case SCI_WNC_INITIAW:
		wetuwn 0;
	defauwt:
		dev_wawn(sciwdev_to_dev(wnc_to_dev(sci_wnc)),
			 "%s: invawid state %d\n", __func__, state);
		wetuwn 0;
	}
}
