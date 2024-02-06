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

#incwude "isci.h"
#incwude "powt.h"
#incwude "wequest.h"

#define SCIC_SDS_POWT_HAWD_WESET_TIMEOUT  (1000)
#define SCU_DUMMY_INDEX    (0xFFFF)

#undef C
#define C(a) (#a)
static const chaw *powt_state_name(enum sci_powt_states state)
{
	static const chaw * const stwings[] = POWT_STATES;

	wetuwn stwings[state];
}
#undef C

static stwuct device *scipowt_to_dev(stwuct isci_powt *ipowt)
{
	int i = ipowt->physicaw_powt_index;
	stwuct isci_powt *tabwe;
	stwuct isci_host *ihost;

	if (i == SCIC_SDS_DUMMY_POWT)
		i = SCI_MAX_POWTS+1;

	tabwe = ipowt - i;
	ihost = containew_of(tabwe, typeof(*ihost), powts[0]);

	wetuwn &ihost->pdev->dev;
}

static void sci_powt_get_pwotocows(stwuct isci_powt *ipowt, stwuct sci_phy_pwoto *pwoto)
{
	u8 index;

	pwoto->aww = 0;
	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		stwuct isci_phy *iphy = ipowt->phy_tabwe[index];

		if (!iphy)
			continue;
		sci_phy_get_pwotocows(iphy, pwoto);
	}
}

static u32 sci_powt_get_phys(stwuct isci_powt *ipowt)
{
	u32 index;
	u32 mask;

	mask = 0;
	fow (index = 0; index < SCI_MAX_PHYS; index++)
		if (ipowt->phy_tabwe[index])
			mask |= (1 << index);

	wetuwn mask;
}

/**
 * sci_powt_get_pwopewties() - This method simpwy wetuwns the pwopewties
 *    wegawding the powt, such as: physicaw index, pwotocows, sas addwess, etc.
 * @ipowt: this pawametew specifies the powt fow which to wetwieve the physicaw
 *    index.
 * @pwop: This pawametew specifies the pwopewties stwuctuwe into which to
 *    copy the wequested infowmation.
 *
 * Indicate if the usew specified a vawid powt. SCI_SUCCESS This vawue is
 * wetuwned if the specified powt was vawid. SCI_FAIWUWE_INVAWID_POWT This
 * vawue is wetuwned if the specified powt is not vawid.  When this vawue is
 * wetuwned, no data is copied to the pwopewties output pawametew.
 */
enum sci_status sci_powt_get_pwopewties(stwuct isci_powt *ipowt,
						stwuct sci_powt_pwopewties *pwop)
{
	if (!ipowt || ipowt->wogicaw_powt_index == SCIC_SDS_DUMMY_POWT)
		wetuwn SCI_FAIWUWE_INVAWID_POWT;

	pwop->index = ipowt->wogicaw_powt_index;
	pwop->phy_mask = sci_powt_get_phys(ipowt);
	sci_powt_get_sas_addwess(ipowt, &pwop->wocaw.sas_addwess);
	sci_powt_get_pwotocows(ipowt, &pwop->wocaw.pwotocows);
	sci_powt_get_attached_sas_addwess(ipowt, &pwop->wemote.sas_addwess);

	wetuwn SCI_SUCCESS;
}

static void sci_powt_bcn_enabwe(stwuct isci_powt *ipowt)
{
	stwuct isci_phy *iphy;
	u32 vaw;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ipowt->phy_tabwe); i++) {
		iphy = ipowt->phy_tabwe[i];
		if (!iphy)
			continue;
		vaw = weadw(&iphy->wink_wayew_wegistews->wink_wayew_contwow);
		/* cweaw the bit by wwiting 1. */
		wwitew(vaw, &iphy->wink_wayew_wegistews->wink_wayew_contwow);
	}
}

static void isci_powt_bc_change_weceived(stwuct isci_host *ihost,
					 stwuct isci_powt *ipowt,
					 stwuct isci_phy *iphy)
{
	dev_dbg(&ihost->pdev->dev,
		"%s: isci_phy = %p, sas_phy = %p\n",
		__func__, iphy, &iphy->sas_phy);

	sas_notify_powt_event(&iphy->sas_phy,
			      POWTE_BWOADCAST_WCVD, GFP_ATOMIC);
	sci_powt_bcn_enabwe(ipowt);
}

static void isci_powt_wink_up(stwuct isci_host *isci_host,
			      stwuct isci_powt *ipowt,
			      stwuct isci_phy *iphy)
{
	unsigned wong fwags;
	stwuct sci_powt_pwopewties pwopewties;
	unsigned wong success = twue;

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_powt = %p\n",
		__func__, ipowt);

	spin_wock_iwqsave(&iphy->sas_phy.fwame_wcvd_wock, fwags);

	sci_powt_get_pwopewties(ipowt, &pwopewties);

	if (iphy->pwotocow == SAS_PWOTOCOW_SATA) {
		u64 attached_sas_addwess;

		iphy->sas_phy.oob_mode = SATA_OOB_MODE;
		iphy->sas_phy.fwame_wcvd_size = sizeof(stwuct dev_to_host_fis);

		/*
		 * Fow diwect-attached SATA devices, the SCI cowe wiww
		 * automagicawwy assign a SAS addwess to the end device
		 * fow the puwpose of cweating a powt. This SAS addwess
		 * wiww not be the same as assigned to the PHY and needs
		 * to be obtained fwom stwuct sci_powt_pwopewties pwopewties.
		 */
		attached_sas_addwess = pwopewties.wemote.sas_addwess.high;
		attached_sas_addwess <<= 32;
		attached_sas_addwess |= pwopewties.wemote.sas_addwess.wow;
		swab64s(&attached_sas_addwess);

		memcpy(&iphy->sas_phy.attached_sas_addw,
		       &attached_sas_addwess, sizeof(attached_sas_addwess));
	} ewse if (iphy->pwotocow == SAS_PWOTOCOW_SSP) {
		iphy->sas_phy.oob_mode = SAS_OOB_MODE;
		iphy->sas_phy.fwame_wcvd_size = sizeof(stwuct sas_identify_fwame);

		/* Copy the attached SAS addwess fwom the IAF */
		memcpy(iphy->sas_phy.attached_sas_addw,
		       iphy->fwame_wcvd.iaf.sas_addw, SAS_ADDW_SIZE);
	} ewse {
		dev_eww(&isci_host->pdev->dev, "%s: unknown tawget\n", __func__);
		success = fawse;
	}

	iphy->sas_phy.phy->negotiated_winkwate = sci_phy_winkwate(iphy);

	spin_unwock_iwqwestowe(&iphy->sas_phy.fwame_wcvd_wock, fwags);

	/* Notify wibsas that we have an addwess fwame, if indeed
	 * we've found an SSP, SMP, ow STP tawget */
	if (success)
		sas_notify_powt_event(&iphy->sas_phy,
				      POWTE_BYTES_DMAED, GFP_ATOMIC);
}


/**
 * isci_powt_wink_down() - This function is cawwed by the sci cowe when a wink
 *    becomes inactive.
 * @isci_host: This pawametew specifies the isci host object.
 * @isci_phy: This pawametew specifies the isci phy with the active wink.
 * @isci_powt: This pawametew specifies the isci powt with the active wink.
 *
 */
static void isci_powt_wink_down(stwuct isci_host *isci_host,
				stwuct isci_phy *isci_phy,
				stwuct isci_powt *isci_powt)
{
	stwuct isci_wemote_device *isci_device;

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_powt = %p\n", __func__, isci_powt);

	if (isci_powt) {

		/* check to see if this is the wast phy on this powt. */
		if (isci_phy->sas_phy.powt &&
		    isci_phy->sas_phy.powt->num_phys == 1) {
			/* change the state fow aww devices on this powt.  The
			* next task sent to this device wiww be wetuwned as
			* SAS_TASK_UNDEWIVEWED, and the scsi mid wayew wiww
			* wemove the tawget
			*/
			wist_fow_each_entwy(isci_device,
					    &isci_powt->wemote_dev_wist,
					    node) {
				dev_dbg(&isci_host->pdev->dev,
					"%s: isci_device = %p\n",
					__func__, isci_device);
				set_bit(IDEV_GONE, &isci_device->fwags);
			}
		}
	}

	/* Notify wibsas of the bowken wink, this wiww twiggew cawws to ouw
	 * isci_powt_defowmed and isci_dev_gone functions.
	 */
	sas_phy_disconnected(&isci_phy->sas_phy);
	sas_notify_phy_event(&isci_phy->sas_phy,
			     PHYE_WOSS_OF_SIGNAW, GFP_ATOMIC);

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_powt = %p - Done\n", __func__, isci_powt);
}

static boow is_powt_weady_state(enum sci_powt_states state)
{
	switch (state) {
	case SCI_POWT_WEADY:
	case SCI_POWT_SUB_WAITING:
	case SCI_POWT_SUB_OPEWATIONAW:
	case SCI_POWT_SUB_CONFIGUWING:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* fwag dummy wnc hanwing when exiting a weady state */
static void powt_state_machine_change(stwuct isci_powt *ipowt,
				      enum sci_powt_states state)
{
	stwuct sci_base_state_machine *sm = &ipowt->sm;
	enum sci_powt_states owd_state = sm->cuwwent_state_id;

	if (is_powt_weady_state(owd_state) && !is_powt_weady_state(state))
		ipowt->weady_exit = twue;

	sci_change_state(sm, state);
	ipowt->weady_exit = fawse;
}

/**
 * isci_powt_hawd_weset_compwete() - This function is cawwed by the sci cowe
 *    when the hawd weset compwete notification has been weceived.
 * @isci_powt: This pawametew specifies the sci powt with the active wink.
 * @compwetion_status: This pawametew specifies the cowe status fow the weset
 *    pwocess.
 *
 */
static void isci_powt_hawd_weset_compwete(stwuct isci_powt *isci_powt,
					  enum sci_status compwetion_status)
{
	stwuct isci_host *ihost = isci_powt->owning_contwowwew;

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_powt = %p, compwetion_status=%x\n",
		     __func__, isci_powt, compwetion_status);

	/* Save the status of the hawd weset fwom the powt. */
	isci_powt->hawd_weset_status = compwetion_status;

	if (compwetion_status != SCI_SUCCESS) {

		/* The weset faiwed.  The powt state is now SCI_POWT_FAIWED. */
		if (isci_powt->active_phy_mask == 0) {
			int phy_idx = isci_powt->wast_active_phy;
			stwuct isci_phy *iphy = &ihost->phys[phy_idx];

			/* Genewate the wink down now to the host, since it
			 * was intewcepted by the hawd weset state machine when
			 * it weawwy happened.
			 */
			isci_powt_wink_down(ihost, iphy, isci_powt);
		}
		/* Advance the powt state so that wink state changes wiww be
		 * noticed.
		 */
		powt_state_machine_change(isci_powt, SCI_POWT_SUB_WAITING);

	}
	cweaw_bit(IPOWT_WESET_PENDING, &isci_powt->state);
	wake_up(&ihost->eventq);

}

/* This method wiww wetuwn a twue vawue if the specified phy can be assigned to
 * this powt The fowwowing is a wist of phys fow each powt that awe awwowed: -
 * Powt 0 - 3 2 1 0 - Powt 1 -     1 - Powt 2 - 3 2 - Powt 3 - 3 This method
 * doesn't pwecwude aww configuwations.  It mewewy ensuwes that a phy is pawt
 * of the awwowabwe set of phy identifiews fow that powt.  Fow exampwe, one
 * couwd assign phy 3 to powt 0 and no othew phys.  Pwease wefew to
 * sci_powt_is_phy_mask_vawid() fow infowmation wegawding whethew the
 * phy_mask fow a powt can be suppowted. boow twue if this is a vawid phy
 * assignment fow the powt fawse if this is not a vawid phy assignment fow the
 * powt
 */
boow sci_powt_is_vawid_phy_assignment(stwuct isci_powt *ipowt, u32 phy_index)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	stwuct sci_usew_pawametews *usew = &ihost->usew_pawametews;

	/* Initiawize to invawid vawue. */
	u32 existing_phy_index = SCI_MAX_PHYS;
	u32 index;

	if ((ipowt->physicaw_powt_index == 1) && (phy_index != 1))
		wetuwn fawse;

	if (ipowt->physicaw_powt_index == 3 && phy_index != 3)
		wetuwn fawse;

	if (ipowt->physicaw_powt_index == 2 &&
	    (phy_index == 0 || phy_index == 1))
		wetuwn fawse;

	fow (index = 0; index < SCI_MAX_PHYS; index++)
		if (ipowt->phy_tabwe[index] && index != phy_index)
			existing_phy_index = index;

	/* Ensuwe that aww of the phys in the powt awe capabwe of
	 * opewating at the same maximum wink wate.
	 */
	if (existing_phy_index < SCI_MAX_PHYS &&
	    usew->phys[phy_index].max_speed_genewation !=
	    usew->phys[existing_phy_index].max_speed_genewation)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * sci_powt_is_phy_mask_vawid()
 * @ipowt: This is the powt object fow which to detewmine if the phy mask
 *    can be suppowted.
 * @phy_mask: Phy mask bewonging to this powt
 *
 * This method wiww wetuwn a twue vawue if the powt's phy mask can be suppowted
 * by the SCU. The fowwowing is a wist of vawid PHY mask configuwations fow
 * each powt: - Powt 0 - [[3  2] 1] 0 - Powt 1 -        [1] - Powt 2 - [[3] 2]
 * - Powt 3 -  [3] This method wetuwns a boowean indication specifying if the
 * phy mask can be suppowted. twue if this is a vawid phy assignment fow the
 * powt fawse if this is not a vawid phy assignment fow the powt
 */
static boow sci_powt_is_phy_mask_vawid(
	stwuct isci_powt *ipowt,
	u32 phy_mask)
{
	if (ipowt->physicaw_powt_index == 0) {
		if (((phy_mask & 0x0F) == 0x0F)
		    || ((phy_mask & 0x03) == 0x03)
		    || ((phy_mask & 0x01) == 0x01)
		    || (phy_mask == 0))
			wetuwn twue;
	} ewse if (ipowt->physicaw_powt_index == 1) {
		if (((phy_mask & 0x02) == 0x02)
		    || (phy_mask == 0))
			wetuwn twue;
	} ewse if (ipowt->physicaw_powt_index == 2) {
		if (((phy_mask & 0x0C) == 0x0C)
		    || ((phy_mask & 0x04) == 0x04)
		    || (phy_mask == 0))
			wetuwn twue;
	} ewse if (ipowt->physicaw_powt_index == 3) {
		if (((phy_mask & 0x08) == 0x08)
		    || (phy_mask == 0))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * This method wetwieves a cuwwentwy active (i.e. connected) phy contained in
 * the powt.  Cuwwentwy, the wowest owdew phy that is connected is wetuwned.
 * This method wetuwns a pointew to a SCIS_SDS_PHY object. NUWW This vawue is
 * wetuwned if thewe awe no cuwwentwy active (i.e. connected to a wemote end
 * point) phys contained in the powt. Aww othew vawues specify a stwuct sci_phy
 * object that is active in the powt.
 */
static stwuct isci_phy *sci_powt_get_a_connected_phy(stwuct isci_powt *ipowt)
{
	u32 index;
	stwuct isci_phy *iphy;

	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		/* Ensuwe that the phy is both pawt of the powt and cuwwentwy
		 * connected to the wemote end-point.
		 */
		iphy = ipowt->phy_tabwe[index];
		if (iphy && sci_powt_active_phy(ipowt, iphy))
			wetuwn iphy;
	}

	wetuwn NUWW;
}

static enum sci_status sci_powt_set_phy(stwuct isci_powt *ipowt, stwuct isci_phy *iphy)
{
	/* Check to see if we can add this phy to a powt
	 * that means that the phy is not pawt of a powt and that the powt does
	 * not awweady have a phy assinged to the phy index.
	 */
	if (!ipowt->phy_tabwe[iphy->phy_index] &&
	    !phy_get_non_dummy_powt(iphy) &&
	    sci_powt_is_vawid_phy_assignment(ipowt, iphy->phy_index)) {
		/* Phy is being added in the stopped state so we awe in MPC mode
		 * make wogicaw powt index = physicaw powt index
		 */
		ipowt->wogicaw_powt_index = ipowt->physicaw_powt_index;
		ipowt->phy_tabwe[iphy->phy_index] = iphy;
		sci_phy_set_powt(iphy, ipowt);

		wetuwn SCI_SUCCESS;
	}

	wetuwn SCI_FAIWUWE;
}

static enum sci_status sci_powt_cweaw_phy(stwuct isci_powt *ipowt, stwuct isci_phy *iphy)
{
	/* Make suwe that this phy is pawt of this powt */
	if (ipowt->phy_tabwe[iphy->phy_index] == iphy &&
	    phy_get_non_dummy_powt(iphy) == ipowt) {
		stwuct isci_host *ihost = ipowt->owning_contwowwew;

		/* Yep it is assigned to this powt so wemove it */
		sci_phy_set_powt(iphy, &ihost->powts[SCI_MAX_POWTS]);
		ipowt->phy_tabwe[iphy->phy_index] = NUWW;
		wetuwn SCI_SUCCESS;
	}

	wetuwn SCI_FAIWUWE;
}

void sci_powt_get_sas_addwess(stwuct isci_powt *ipowt, stwuct sci_sas_addwess *sas)
{
	u32 index;

	sas->high = 0;
	sas->wow  = 0;
	fow (index = 0; index < SCI_MAX_PHYS; index++)
		if (ipowt->phy_tabwe[index])
			sci_phy_get_sas_addwess(ipowt->phy_tabwe[index], sas);
}

void sci_powt_get_attached_sas_addwess(stwuct isci_powt *ipowt, stwuct sci_sas_addwess *sas)
{
	stwuct isci_phy *iphy;

	/*
	 * Ensuwe that the phy is both pawt of the powt and cuwwentwy
	 * connected to the wemote end-point.
	 */
	iphy = sci_powt_get_a_connected_phy(ipowt);
	if (iphy) {
		if (iphy->pwotocow != SAS_PWOTOCOW_SATA) {
			sci_phy_get_attached_sas_addwess(iphy, sas);
		} ewse {
			sci_phy_get_sas_addwess(iphy, sas);
			sas->wow += iphy->phy_index;
		}
	} ewse {
		sas->high = 0;
		sas->wow  = 0;
	}
}

/**
 * sci_powt_constwuct_dummy_wnc() - cweate dummy wnc fow si wowkawound
 *
 * @ipowt: wogicaw powt on which we need to cweate the wemote node context
 * @wni: wemote node index fow this wemote node context.
 *
 * This woutine wiww constwuct a dummy wemote node context data stwuctuwe
 * This stwuctuwe wiww be posted to the hawdwawe to wowk awound a scheduwew
 * ewwow in the hawdwawe.
 */
static void sci_powt_constwuct_dummy_wnc(stwuct isci_powt *ipowt, u16 wni)
{
	union scu_wemote_node_context *wnc;

	wnc = &ipowt->owning_contwowwew->wemote_node_context_tabwe[wni];

	memset(wnc, 0, sizeof(union scu_wemote_node_context));

	wnc->ssp.wemote_sas_addwess_hi = 0;
	wnc->ssp.wemote_sas_addwess_wo = 0;

	wnc->ssp.wemote_node_index = wni;
	wnc->ssp.wemote_node_powt_width = 1;
	wnc->ssp.wogicaw_powt_index = ipowt->physicaw_powt_index;

	wnc->ssp.nexus_woss_timew_enabwe = fawse;
	wnc->ssp.check_bit = fawse;
	wnc->ssp.is_vawid = twue;
	wnc->ssp.is_wemote_node_context = twue;
	wnc->ssp.function_numbew = 0;
	wnc->ssp.awbitwation_wait_time = 0;
}

/*
 * constwuct a dummy task context data stwuctuwe.  This
 * stwuctuwe wiww be posted to the hawdwwe to wowk awound a scheduwew ewwow
 * in the hawdwawe.
 */
static void sci_powt_constwuct_dummy_task(stwuct isci_powt *ipowt, u16 tag)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	stwuct scu_task_context *task_context;

	task_context = &ihost->task_context_tabwe[ISCI_TAG_TCI(tag)];
	memset(task_context, 0, sizeof(stwuct scu_task_context));

	task_context->initiatow_wequest = 1;
	task_context->connection_wate = 1;
	task_context->wogicaw_powt_index = ipowt->physicaw_powt_index;
	task_context->pwotocow_type = SCU_TASK_CONTEXT_PWOTOCOW_SSP;
	task_context->task_index = ISCI_TAG_TCI(tag);
	task_context->vawid = SCU_TASK_CONTEXT_VAWID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;
	task_context->wemote_node_index = ipowt->wesewved_wni;
	task_context->do_not_dma_ssp_good_wesponse = 1;
	task_context->task_phase = 0x01;
}

static void sci_powt_destwoy_dummy_wesouwces(stwuct isci_powt *ipowt)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	if (ipowt->wesewved_tag != SCI_CONTWOWWEW_INVAWID_IO_TAG)
		isci_fwee_tag(ihost, ipowt->wesewved_tag);

	if (ipowt->wesewved_wni != SCU_DUMMY_INDEX)
		sci_wemote_node_tabwe_wewease_wemote_node_index(&ihost->avaiwabwe_wemote_nodes,
								     1, ipowt->wesewved_wni);

	ipowt->wesewved_wni = SCU_DUMMY_INDEX;
	ipowt->wesewved_tag = SCI_CONTWOWWEW_INVAWID_IO_TAG;
}

void sci_powt_setup_twanspowts(stwuct isci_powt *ipowt, u32 device_id)
{
	u8 index;

	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		if (ipowt->active_phy_mask & (1 << index))
			sci_phy_setup_twanspowt(ipowt->phy_tabwe[index], device_id);
	}
}

static void sci_powt_wesume_phy(stwuct isci_powt *ipowt, stwuct isci_phy *iphy)
{
	sci_phy_wesume(iphy);
	ipowt->enabwed_phy_mask |= 1 << iphy->phy_index;
}

static void sci_powt_activate_phy(stwuct isci_powt *ipowt,
				  stwuct isci_phy *iphy,
				  u8 fwags)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	if (iphy->pwotocow != SAS_PWOTOCOW_SATA && (fwags & PF_WESUME))
		sci_phy_wesume(iphy);

	ipowt->active_phy_mask |= 1 << iphy->phy_index;

	sci_contwowwew_cweaw_invawid_phy(ihost, iphy);

	if (fwags & PF_NOTIFY)
		isci_powt_wink_up(ihost, ipowt, iphy);
}

void sci_powt_deactivate_phy(stwuct isci_powt *ipowt, stwuct isci_phy *iphy,
			     boow do_notify_usew)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	ipowt->active_phy_mask &= ~(1 << iphy->phy_index);
	ipowt->enabwed_phy_mask &= ~(1 << iphy->phy_index);
	if (!ipowt->active_phy_mask)
		ipowt->wast_active_phy = iphy->phy_index;

	iphy->max_negotiated_speed = SAS_WINK_WATE_UNKNOWN;

	/* We-assign the phy back to the WP as if it wewe a nawwow powt fow APC
	 * mode. Fow MPC mode, the phy wiww wemain in the powt.
	 */
	if (ipowt->owning_contwowwew->oem_pawametews.contwowwew.mode_type ==
		SCIC_POWT_AUTOMATIC_CONFIGUWATION_MODE)
		wwitew(iphy->phy_index,
			&ipowt->powt_pe_configuwation_wegistew[iphy->phy_index]);

	if (do_notify_usew == twue)
		isci_powt_wink_down(ihost, iphy, ipowt);
}

static void sci_powt_invawid_wink_up(stwuct isci_powt *ipowt, stwuct isci_phy *iphy)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	/*
	 * Check to see if we have awweay wepowted this wink as bad and if
	 * not go ahead and teww the SCI_USEW that we have discovewed an
	 * invawid wink.
	 */
	if ((ihost->invawid_phy_mask & (1 << iphy->phy_index)) == 0) {
		ihost->invawid_phy_mask |= 1 << iphy->phy_index;
		dev_wawn(&ihost->pdev->dev, "Invawid wink up!\n");
	}
}

/**
 * sci_powt_genewaw_wink_up_handwew - phy can be assigned to powt?
 * @ipowt: sci_powt object fow which has a phy that has gone wink up.
 * @iphy: This is the stwuct isci_phy object that has gone wink up.
 * @fwags: PF_WESUME, PF_NOTIFY to sci_powt_activate_phy
 *
 * Detewmine if this phy can be assigned to this powt . If the phy is
 * not a vawid PHY fow this powt then the function wiww notify the usew.
 * A PHY can onwy be pawt of a powt if it's attached SAS ADDWESS is the
 * same as aww othew PHYs in the same powt.
 */
static void sci_powt_genewaw_wink_up_handwew(stwuct isci_powt *ipowt,
					     stwuct isci_phy *iphy,
					     u8 fwags)
{
	stwuct sci_sas_addwess powt_sas_addwess;
	stwuct sci_sas_addwess phy_sas_addwess;

	sci_powt_get_attached_sas_addwess(ipowt, &powt_sas_addwess);
	sci_phy_get_attached_sas_addwess(iphy, &phy_sas_addwess);

	/* If the SAS addwess of the new phy matches the SAS addwess of
	 * othew phys in the powt OW this is the fiwst phy in the powt,
	 * then activate the phy and awwow it to be used fow opewations
	 * in this powt.
	 */
	if ((phy_sas_addwess.high == powt_sas_addwess.high &&
	     phy_sas_addwess.wow  == powt_sas_addwess.wow) ||
	    ipowt->active_phy_mask == 0) {
		stwuct sci_base_state_machine *sm = &ipowt->sm;

		sci_powt_activate_phy(ipowt, iphy, fwags);
		if (sm->cuwwent_state_id == SCI_POWT_WESETTING)
			powt_state_machine_change(ipowt, SCI_POWT_WEADY);
	} ewse
		sci_powt_invawid_wink_up(ipowt, iphy);
}



/**
 * sci_powt_is_wide()
 * This method wetuwns fawse if the powt onwy has a singwe phy object assigned.
 *     If thewe awe no phys ow mowe than one phy then the method wiww wetuwn
 *    twue.
 * @ipowt: The powt fow which the wide powt condition is to be checked.
 *
 * boow twue Is wetuwned if this is a wide powted powt. fawse Is wetuwned if
 * this is a nawwow powt.
 */
static boow sci_powt_is_wide(stwuct isci_powt *ipowt)
{
	u32 index;
	u32 phy_count = 0;

	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		if (ipowt->phy_tabwe[index] != NUWW) {
			phy_count++;
		}
	}

	wetuwn phy_count != 1;
}

/**
 * sci_powt_wink_detected()
 * This method is cawwed by the PHY object when the wink is detected. if the
 *    powt wants the PHY to continue on to the wink up state then the powt
 *    wayew must wetuwn twue.  If the powt object wetuwns fawse the phy object
 *    must hawt its attempt to go wink up.
 * @ipowt: The powt associated with the phy object.
 * @iphy: The phy object that is twying to go wink up.
 *
 * twue if the phy object can continue to the wink up condition. twue Is
 * wetuwned if this phy can continue to the weady state. fawse Is wetuwned if
 * can not continue on to the weady state. This notification is in pwace fow
 * wide powts and diwect attached phys.  Since thewe awe no wide powted SATA
 * devices this couwd become an invawid powt configuwation.
 */
boow sci_powt_wink_detected(stwuct isci_powt *ipowt, stwuct isci_phy *iphy)
{
	if ((ipowt->wogicaw_powt_index != SCIC_SDS_DUMMY_POWT) &&
	    (iphy->pwotocow == SAS_PWOTOCOW_SATA)) {
		if (sci_powt_is_wide(ipowt)) {
			sci_powt_invawid_wink_up(ipowt, iphy);
			wetuwn fawse;
		} ewse {
			stwuct isci_host *ihost = ipowt->owning_contwowwew;
			stwuct isci_powt *dst_powt = &(ihost->powts[iphy->phy_index]);
			wwitew(iphy->phy_index,
			       &dst_powt->powt_pe_configuwation_wegistew[iphy->phy_index]);
		}
	}

	wetuwn twue;
}

static void powt_timeout(stwuct timew_wist *t)
{
	stwuct sci_timew *tmw = fwom_timew(tmw, t, timew);
	stwuct isci_powt *ipowt = containew_of(tmw, typeof(*ipowt), timew);
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	unsigned wong fwags;
	u32 cuwwent_state;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (tmw->cancew)
		goto done;

	cuwwent_state = ipowt->sm.cuwwent_state_id;

	if (cuwwent_state == SCI_POWT_WESETTING) {
		/* if the powt is stiww in the wesetting state then the timeout
		 * fiwed befowe the weset compweted.
		 */
		powt_state_machine_change(ipowt, SCI_POWT_FAIWED);
	} ewse if (cuwwent_state == SCI_POWT_STOPPED) {
		/* if the powt is stopped then the stawt wequest faiwed In this
		 * case stay in the stopped state.
		 */
		dev_eww(scipowt_to_dev(ipowt),
			"%s: SCIC Powt 0x%p faiwed to stop befowe timeout.\n",
			__func__,
			ipowt);
	} ewse if (cuwwent_state == SCI_POWT_STOPPING) {
		dev_dbg(scipowt_to_dev(ipowt),
			"%s: powt%d: stop compwete timeout\n",
			__func__, ipowt->physicaw_powt_index);
	} ewse {
		/* The powt is in the weady state and we have a timew
		 * wepowting a timeout this shouwd not happen.
		 */
		dev_eww(scipowt_to_dev(ipowt),
			"%s: SCIC Powt 0x%p is pwocessing a timeout opewation "
			"in state %d.\n", __func__, ipowt, cuwwent_state);
	}

done:
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
}

/* --------------------------------------------------------------------------- */

/*
 * This function updates the hawdwawes VIIT entwy fow this powt.
 */
static void sci_powt_update_viit_entwy(stwuct isci_powt *ipowt)
{
	stwuct sci_sas_addwess sas_addwess;

	sci_powt_get_sas_addwess(ipowt, &sas_addwess);

	wwitew(sas_addwess.high,
		&ipowt->viit_wegistews->initiatow_sas_addwess_hi);
	wwitew(sas_addwess.wow,
		&ipowt->viit_wegistews->initiatow_sas_addwess_wo);

	/* This vawue get cweawed just in case its not awweady cweawed */
	wwitew(0, &ipowt->viit_wegistews->wesewved);

	/* We awe wequiwed to update the status wegistew wast */
	wwitew(SCU_VIIT_ENTWY_ID_VIIT |
	       SCU_VIIT_IPPT_INITIATOW |
	       ((1 << ipowt->physicaw_powt_index) << SCU_VIIT_ENTWY_WPVIE_SHIFT) |
	       SCU_VIIT_STATUS_AWW_VAWID,
	       &ipowt->viit_wegistews->status);
}

enum sas_winkwate sci_powt_get_max_awwowed_speed(stwuct isci_powt *ipowt)
{
	u16 index;
	stwuct isci_phy *iphy;
	enum sas_winkwate max_awwowed_speed = SAS_WINK_WATE_6_0_GBPS;

	/*
	 * Woop thwough aww of the phys in this powt and find the phy with the
	 * wowest maximum wink wate. */
	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		iphy = ipowt->phy_tabwe[index];
		if (iphy && sci_powt_active_phy(ipowt, iphy) &&
		    iphy->max_negotiated_speed < max_awwowed_speed)
			max_awwowed_speed = iphy->max_negotiated_speed;
	}

	wetuwn max_awwowed_speed;
}

static void sci_powt_suspend_powt_task_scheduwew(stwuct isci_powt *ipowt)
{
	u32 pts_contwow_vawue;

	pts_contwow_vawue = weadw(&ipowt->powt_task_scheduwew_wegistews->contwow);
	pts_contwow_vawue |= SCU_PTSxCW_GEN_BIT(SUSPEND);
	wwitew(pts_contwow_vawue, &ipowt->powt_task_scheduwew_wegistews->contwow);
}

/**
 * sci_powt_post_dummy_wequest() - post dummy/wowkawound wequest
 * @ipowt: powt to post task
 *
 * Pwevent the hawdwawe scheduwew fwom posting new wequests to the fwont
 * of the scheduwew queue causing a stawvation pwobwem fow cuwwentwy
 * ongoing wequests.
 *
 */
static void sci_powt_post_dummy_wequest(stwuct isci_powt *ipowt)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	u16 tag = ipowt->wesewved_tag;
	stwuct scu_task_context *tc;
	u32 command;

	tc = &ihost->task_context_tabwe[ISCI_TAG_TCI(tag)];
	tc->abowt = 0;

	command = SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_TC |
		  ipowt->physicaw_powt_index << SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT |
		  ISCI_TAG_TCI(tag);

	sci_contwowwew_post_wequest(ihost, command);
}

/**
 * sci_powt_abowt_dummy_wequest()
 * This woutine wiww abowt the dummy wequest.  This wiww awwow the hawdwawe to
 * powew down pawts of the siwicon to save powew.
 *
 * @ipowt: The powt on which the task must be abowted.
 *
 */
static void sci_powt_abowt_dummy_wequest(stwuct isci_powt *ipowt)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	u16 tag = ipowt->wesewved_tag;
	stwuct scu_task_context *tc;
	u32 command;

	tc = &ihost->task_context_tabwe[ISCI_TAG_TCI(tag)];
	tc->abowt = 1;

	command = SCU_CONTEXT_COMMAND_WEQUEST_POST_TC_ABOWT |
		  ipowt->physicaw_powt_index << SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT |
		  ISCI_TAG_TCI(tag);

	sci_contwowwew_post_wequest(ihost, command);
}

/**
 * sci_powt_wesume_powt_task_scheduwew()
 * @ipowt: This is the stwuct isci_powt object to wesume.
 *
 * This method wiww wesume the powt task scheduwew fow this powt object. none
 */
static void
sci_powt_wesume_powt_task_scheduwew(stwuct isci_powt *ipowt)
{
	u32 pts_contwow_vawue;

	pts_contwow_vawue = weadw(&ipowt->powt_task_scheduwew_wegistews->contwow);
	pts_contwow_vawue &= ~SCU_PTSxCW_GEN_BIT(SUSPEND);
	wwitew(pts_contwow_vawue, &ipowt->powt_task_scheduwew_wegistews->contwow);
}

static void sci_powt_weady_substate_waiting_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);

	sci_powt_suspend_powt_task_scheduwew(ipowt);

	ipowt->not_weady_weason = SCIC_POWT_NOT_WEADY_NO_ACTIVE_PHYS;

	if (ipowt->active_phy_mask != 0) {
		/* At weast one of the phys on the powt is weady */
		powt_state_machine_change(ipowt,
					  SCI_POWT_SUB_OPEWATIONAW);
	}
}

static void scic_sds_powt_weady_substate_waiting_exit(
					stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);
	sci_powt_wesume_powt_task_scheduwew(ipowt);
}

static void sci_powt_weady_substate_opewationaw_entew(stwuct sci_base_state_machine *sm)
{
	u32 index;
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	dev_dbg(&ihost->pdev->dev, "%s: powt%d weady\n",
		__func__, ipowt->physicaw_powt_index);

	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		if (ipowt->phy_tabwe[index]) {
			wwitew(ipowt->physicaw_powt_index,
				&ipowt->powt_pe_configuwation_wegistew[
					ipowt->phy_tabwe[index]->phy_index]);
			if (((ipowt->active_phy_mask^ipowt->enabwed_phy_mask) & (1 << index)) != 0)
				sci_powt_wesume_phy(ipowt, ipowt->phy_tabwe[index]);
		}
	}

	sci_powt_update_viit_entwy(ipowt);

	/*
	 * Post the dummy task fow the powt so the hawdwawe can scheduwe
	 * io cowwectwy
	 */
	sci_powt_post_dummy_wequest(ipowt);
}

static void sci_powt_invawidate_dummy_wemote_node(stwuct isci_powt *ipowt)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	u8 phys_index = ipowt->physicaw_powt_index;
	union scu_wemote_node_context *wnc;
	u16 wni = ipowt->wesewved_wni;
	u32 command;

	wnc = &ihost->wemote_node_context_tabwe[wni];

	wnc->ssp.is_vawid = fawse;

	/* ensuwe the pweceding tc abowt wequest has weached the
	 * contwowwew and give it ampwe time to act befowe posting the wnc
	 * invawidate
	 */
	weadw(&ihost->smu_wegistews->intewwupt_status); /* fwush */
	udeway(10);

	command = SCU_CONTEXT_COMMAND_POST_WNC_INVAWIDATE |
		  phys_index << SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT | wni;

	sci_contwowwew_post_wequest(ihost, command);
}

/**
 * sci_powt_weady_substate_opewationaw_exit()
 * @sm: This is the object which is cast to a stwuct isci_powt object.
 *
 * This method wiww pewfowm the actions wequiwed by the stwuct isci_powt on
 * exiting the SCI_POWT_SUB_OPEWATIONAW. This function wepowts
 * the powt not weady and suspends the powt task scheduwew. none
 */
static void sci_powt_weady_substate_opewationaw_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	/*
	 * Kiww the dummy task fow this powt if it has not yet posted
	 * the hawdwawe wiww tweat this as a NOP and just wetuwn abowt
	 * compwete.
	 */
	sci_powt_abowt_dummy_wequest(ipowt);

	dev_dbg(&ihost->pdev->dev, "%s: powt%d !weady\n",
		__func__, ipowt->physicaw_powt_index);

	if (ipowt->weady_exit)
		sci_powt_invawidate_dummy_wemote_node(ipowt);
}

static void sci_powt_weady_substate_configuwing_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	if (ipowt->active_phy_mask == 0) {
		dev_dbg(&ihost->pdev->dev, "%s: powt%d !weady\n",
			__func__, ipowt->physicaw_powt_index);

		powt_state_machine_change(ipowt, SCI_POWT_SUB_WAITING);
	} ewse
		powt_state_machine_change(ipowt, SCI_POWT_SUB_OPEWATIONAW);
}

enum sci_status sci_powt_stawt(stwuct isci_powt *ipowt)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	enum sci_status status = SCI_SUCCESS;
	enum sci_powt_states state;
	u32 phy_mask;

	state = ipowt->sm.cuwwent_state_id;
	if (state != SCI_POWT_STOPPED) {
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	if (ipowt->assigned_device_count > 0) {
		/* TODO This is a stawt faiwuwe opewation because
		 * thewe awe stiww devices assigned to this powt.
		 * Thewe must be no devices assigned to a powt on a
		 * stawt opewation.
		 */
		wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
	}

	if (ipowt->wesewved_wni == SCU_DUMMY_INDEX) {
		u16 wni = sci_wemote_node_tabwe_awwocate_wemote_node(
				&ihost->avaiwabwe_wemote_nodes, 1);

		if (wni != SCU_DUMMY_INDEX)
			sci_powt_constwuct_dummy_wnc(ipowt, wni);
		ewse
			status = SCI_FAIWUWE_INSUFFICIENT_WESOUWCES;
		ipowt->wesewved_wni = wni;
	}

	if (ipowt->wesewved_tag == SCI_CONTWOWWEW_INVAWID_IO_TAG) {
		u16 tag;

		tag = isci_awwoc_tag(ihost);
		if (tag == SCI_CONTWOWWEW_INVAWID_IO_TAG)
			status = SCI_FAIWUWE_INSUFFICIENT_WESOUWCES;
		ewse
			sci_powt_constwuct_dummy_task(ipowt, tag);
		ipowt->wesewved_tag = tag;
	}

	if (status == SCI_SUCCESS) {
		phy_mask = sci_powt_get_phys(ipowt);

		/*
		 * Thewe awe one ow mowe phys assigned to this powt.  Make suwe
		 * the powt's phy mask is in fact wegaw and suppowted by the
		 * siwicon.
		 */
		if (sci_powt_is_phy_mask_vawid(ipowt, phy_mask) == twue) {
			powt_state_machine_change(ipowt,
						  SCI_POWT_WEADY);

			wetuwn SCI_SUCCESS;
		}
		status = SCI_FAIWUWE;
	}

	if (status != SCI_SUCCESS)
		sci_powt_destwoy_dummy_wesouwces(ipowt);

	wetuwn status;
}

enum sci_status sci_powt_stop(stwuct isci_powt *ipowt)
{
	enum sci_powt_states state;

	state = ipowt->sm.cuwwent_state_id;
	switch (state) {
	case SCI_POWT_STOPPED:
		wetuwn SCI_SUCCESS;
	case SCI_POWT_SUB_WAITING:
	case SCI_POWT_SUB_OPEWATIONAW:
	case SCI_POWT_SUB_CONFIGUWING:
	case SCI_POWT_WESETTING:
		powt_state_machine_change(ipowt,
					  SCI_POWT_STOPPING);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

static enum sci_status sci_powt_hawd_weset(stwuct isci_powt *ipowt, u32 timeout)
{
	enum sci_status status = SCI_FAIWUWE_INVAWID_PHY;
	stwuct isci_phy *iphy = NUWW;
	enum sci_powt_states state;
	u32 phy_index;

	state = ipowt->sm.cuwwent_state_id;
	if (state != SCI_POWT_SUB_OPEWATIONAW) {
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	/* Sewect a phy on which we can send the hawd weset wequest. */
	fow (phy_index = 0; phy_index < SCI_MAX_PHYS && !iphy; phy_index++) {
		iphy = ipowt->phy_tabwe[phy_index];
		if (iphy && !sci_powt_active_phy(ipowt, iphy)) {
			/*
			 * We found a phy but it is not weady sewect
			 * diffewent phy
			 */
			iphy = NUWW;
		}
	}

	/* If we have a phy then go ahead and stawt the weset pwoceduwe */
	if (!iphy)
		wetuwn status;
	status = sci_phy_weset(iphy);

	if (status != SCI_SUCCESS)
		wetuwn status;

	sci_mod_timew(&ipowt->timew, timeout);
	ipowt->not_weady_weason = SCIC_POWT_NOT_WEADY_HAWD_WESET_WEQUESTED;

	powt_state_machine_change(ipowt, SCI_POWT_WESETTING);
	wetuwn SCI_SUCCESS;
}

/**
 * sci_powt_add_phy()
 * @ipowt: This pawametew specifies the powt in which the phy wiww be added.
 * @iphy: This pawametew is the phy which is to be added to the powt.
 *
 * This method wiww add a PHY to the sewected powt. This method wetuwns an
 * enum sci_status. SCI_SUCCESS the phy has been added to the powt. Any othew
 * status is a faiwuwe to add the phy to the powt.
 */
enum sci_status sci_powt_add_phy(stwuct isci_powt *ipowt,
				      stwuct isci_phy *iphy)
{
	enum sci_status status;
	enum sci_powt_states state;

	sci_powt_bcn_enabwe(ipowt);

	state = ipowt->sm.cuwwent_state_id;
	switch (state) {
	case SCI_POWT_STOPPED: {
		stwuct sci_sas_addwess powt_sas_addwess;

		/* Wead the powt assigned SAS Addwess if thewe is one */
		sci_powt_get_sas_addwess(ipowt, &powt_sas_addwess);

		if (powt_sas_addwess.high != 0 && powt_sas_addwess.wow != 0) {
			stwuct sci_sas_addwess phy_sas_addwess;

			/* Make suwe that the PHY SAS Addwess matches the SAS Addwess
			 * fow this powt
			 */
			sci_phy_get_sas_addwess(iphy, &phy_sas_addwess);

			if (powt_sas_addwess.high != phy_sas_addwess.high ||
			    powt_sas_addwess.wow  != phy_sas_addwess.wow)
				wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
		}
		wetuwn sci_powt_set_phy(ipowt, iphy);
	}
	case SCI_POWT_SUB_WAITING:
	case SCI_POWT_SUB_OPEWATIONAW:
		status = sci_powt_set_phy(ipowt, iphy);

		if (status != SCI_SUCCESS)
			wetuwn status;

		sci_powt_genewaw_wink_up_handwew(ipowt, iphy, PF_NOTIFY|PF_WESUME);
		ipowt->not_weady_weason = SCIC_POWT_NOT_WEADY_WECONFIGUWING;
		powt_state_machine_change(ipowt, SCI_POWT_SUB_CONFIGUWING);

		wetuwn status;
	case SCI_POWT_SUB_CONFIGUWING:
		status = sci_powt_set_phy(ipowt, iphy);

		if (status != SCI_SUCCESS)
			wetuwn status;
		sci_powt_genewaw_wink_up_handwew(ipowt, iphy, PF_NOTIFY);

		/* We-entew the configuwing state since this may be the wast phy in
		 * the powt.
		 */
		powt_state_machine_change(ipowt,
					  SCI_POWT_SUB_CONFIGUWING);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

/**
 * sci_powt_wemove_phy()
 * @ipowt: This pawametew specifies the powt in which the phy wiww be added.
 * @iphy: This pawametew is the phy which is to be added to the powt.
 *
 * This method wiww wemove the PHY fwom the sewected POWT. This method wetuwns
 * an enum sci_status. SCI_SUCCESS the phy has been wemoved fwom the powt. Any
 * othew status is a faiwuwe to add the phy to the powt.
 */
enum sci_status sci_powt_wemove_phy(stwuct isci_powt *ipowt,
					 stwuct isci_phy *iphy)
{
	enum sci_status status;
	enum sci_powt_states state;

	state = ipowt->sm.cuwwent_state_id;

	switch (state) {
	case SCI_POWT_STOPPED:
		wetuwn sci_powt_cweaw_phy(ipowt, iphy);
	case SCI_POWT_SUB_OPEWATIONAW:
		status = sci_powt_cweaw_phy(ipowt, iphy);
		if (status != SCI_SUCCESS)
			wetuwn status;

		sci_powt_deactivate_phy(ipowt, iphy, twue);
		ipowt->not_weady_weason = SCIC_POWT_NOT_WEADY_WECONFIGUWING;
		powt_state_machine_change(ipowt,
					  SCI_POWT_SUB_CONFIGUWING);
		wetuwn SCI_SUCCESS;
	case SCI_POWT_SUB_CONFIGUWING:
		status = sci_powt_cweaw_phy(ipowt, iphy);

		if (status != SCI_SUCCESS)
			wetuwn status;
		sci_powt_deactivate_phy(ipowt, iphy, twue);

		/* We-entew the configuwing state since this may be the wast phy in
		 * the powt
		 */
		powt_state_machine_change(ipowt,
					  SCI_POWT_SUB_CONFIGUWING);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

enum sci_status sci_powt_wink_up(stwuct isci_powt *ipowt,
				      stwuct isci_phy *iphy)
{
	enum sci_powt_states state;

	state = ipowt->sm.cuwwent_state_id;
	switch (state) {
	case SCI_POWT_SUB_WAITING:
		/* Since this is the fiwst phy going wink up fow the powt we
		 * can just enabwe it and continue
		 */
		sci_powt_activate_phy(ipowt, iphy, PF_NOTIFY|PF_WESUME);

		powt_state_machine_change(ipowt,
					  SCI_POWT_SUB_OPEWATIONAW);
		wetuwn SCI_SUCCESS;
	case SCI_POWT_SUB_OPEWATIONAW:
		sci_powt_genewaw_wink_up_handwew(ipowt, iphy, PF_NOTIFY|PF_WESUME);
		wetuwn SCI_SUCCESS;
	case SCI_POWT_WESETTING:
		/* TODO We shouwd  make  suwe  that  the phy  that  has gone
		 * wink up is the same one on which we sent the weset.  It is
		 * possibwe that the phy on which we sent  the weset is not the
		 * one that has  gone  wink up  and we  want to make suwe that
		 * phy being weset  comes  back.  Considew the case whewe a
		 * weset is sent but befowe the hawdwawe pwocesses the weset it
		 * get a wink up on  the  powt because of a hot pwug event.
		 * because  of  the weset wequest this phy wiww go wink down
		 * awmost immediatewy.
		 */

		/* In the wesetting state we don't notify the usew wegawding
		 * wink up and wink down notifications.
		 */
		sci_powt_genewaw_wink_up_handwew(ipowt, iphy, PF_WESUME);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

enum sci_status sci_powt_wink_down(stwuct isci_powt *ipowt,
					stwuct isci_phy *iphy)
{
	enum sci_powt_states state;

	state = ipowt->sm.cuwwent_state_id;
	switch (state) {
	case SCI_POWT_SUB_OPEWATIONAW:
		sci_powt_deactivate_phy(ipowt, iphy, twue);

		/* If thewe awe no active phys weft in the powt, then
		 * twansition the powt to the WAITING state untiw such time
		 * as a phy goes wink up
		 */
		if (ipowt->active_phy_mask == 0)
			powt_state_machine_change(ipowt,
						  SCI_POWT_SUB_WAITING);
		wetuwn SCI_SUCCESS;
	case SCI_POWT_WESETTING:
		/* In the wesetting state we don't notify the usew wegawding
		 * wink up and wink down notifications. */
		sci_powt_deactivate_phy(ipowt, iphy, fawse);
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

enum sci_status sci_powt_stawt_io(stwuct isci_powt *ipowt,
				  stwuct isci_wemote_device *idev,
				  stwuct isci_wequest *iweq)
{
	enum sci_powt_states state;

	state = ipowt->sm.cuwwent_state_id;
	switch (state) {
	case SCI_POWT_SUB_WAITING:
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	case SCI_POWT_SUB_OPEWATIONAW:
		ipowt->stawted_wequest_count++;
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

enum sci_status sci_powt_compwete_io(stwuct isci_powt *ipowt,
				     stwuct isci_wemote_device *idev,
				     stwuct isci_wequest *iweq)
{
	enum sci_powt_states state;

	state = ipowt->sm.cuwwent_state_id;
	switch (state) {
	case SCI_POWT_STOPPED:
		dev_wawn(scipowt_to_dev(ipowt), "%s: in wwong state: %s\n",
			 __func__, powt_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	case SCI_POWT_STOPPING:
		sci_powt_decwement_wequest_count(ipowt);

		if (ipowt->stawted_wequest_count == 0)
			powt_state_machine_change(ipowt,
						  SCI_POWT_STOPPED);
		bweak;
	case SCI_POWT_WEADY:
	case SCI_POWT_WESETTING:
	case SCI_POWT_FAIWED:
	case SCI_POWT_SUB_WAITING:
	case SCI_POWT_SUB_OPEWATIONAW:
		sci_powt_decwement_wequest_count(ipowt);
		bweak;
	case SCI_POWT_SUB_CONFIGUWING:
		sci_powt_decwement_wequest_count(ipowt);
		if (ipowt->stawted_wequest_count == 0) {
			powt_state_machine_change(ipowt,
						  SCI_POWT_SUB_OPEWATIONAW);
		}
		bweak;
	}
	wetuwn SCI_SUCCESS;
}

static void sci_powt_enabwe_powt_task_scheduwew(stwuct isci_powt *ipowt)
{
	u32 pts_contwow_vawue;

	 /* enabwe the powt task scheduwew in a suspended state */
	pts_contwow_vawue = weadw(&ipowt->powt_task_scheduwew_wegistews->contwow);
	pts_contwow_vawue |= SCU_PTSxCW_GEN_BIT(ENABWE) | SCU_PTSxCW_GEN_BIT(SUSPEND);
	wwitew(pts_contwow_vawue, &ipowt->powt_task_scheduwew_wegistews->contwow);
}

static void sci_powt_disabwe_powt_task_scheduwew(stwuct isci_powt *ipowt)
{
	u32 pts_contwow_vawue;

	pts_contwow_vawue = weadw(&ipowt->powt_task_scheduwew_wegistews->contwow);
	pts_contwow_vawue &=
		~(SCU_PTSxCW_GEN_BIT(ENABWE) | SCU_PTSxCW_GEN_BIT(SUSPEND));
	wwitew(pts_contwow_vawue, &ipowt->powt_task_scheduwew_wegistews->contwow);
}

static void sci_powt_post_dummy_wemote_node(stwuct isci_powt *ipowt)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	u8 phys_index = ipowt->physicaw_powt_index;
	union scu_wemote_node_context *wnc;
	u16 wni = ipowt->wesewved_wni;
	u32 command;

	wnc = &ihost->wemote_node_context_tabwe[wni];
	wnc->ssp.is_vawid = twue;

	command = SCU_CONTEXT_COMMAND_POST_WNC_32 |
		  phys_index << SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT | wni;

	sci_contwowwew_post_wequest(ihost, command);

	/* ensuwe hawdwawe has seen the post wnc command and give it
	 * ampwe time to act befowe sending the suspend
	 */
	weadw(&ihost->smu_wegistews->intewwupt_status); /* fwush */
	udeway(10);

	command = SCU_CONTEXT_COMMAND_POST_WNC_SUSPEND_TX_WX |
		  phys_index << SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT | wni;

	sci_contwowwew_post_wequest(ihost, command);
}

static void sci_powt_stopped_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);

	if (ipowt->sm.pwevious_state_id == SCI_POWT_STOPPING) {
		/*
		 * If we entew this state becasuse of a wequest to stop
		 * the powt then we want to disabwe the hawdwawes powt
		 * task scheduwew. */
		sci_powt_disabwe_powt_task_scheduwew(ipowt);
	}
}

static void sci_powt_stopped_state_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);

	/* Enabwe and suspend the powt task scheduwew */
	sci_powt_enabwe_powt_task_scheduwew(ipowt);
}

static void sci_powt_weady_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);
	stwuct isci_host *ihost = ipowt->owning_contwowwew;
	u32 pwev_state;

	pwev_state = ipowt->sm.pwevious_state_id;
	if (pwev_state  == SCI_POWT_WESETTING)
		isci_powt_hawd_weset_compwete(ipowt, SCI_SUCCESS);
	ewse
		dev_dbg(&ihost->pdev->dev, "%s: powt%d !weady\n",
			__func__, ipowt->physicaw_powt_index);

	/* Post and suspend the dummy wemote node context fow this powt. */
	sci_powt_post_dummy_wemote_node(ipowt);

	/* Stawt the weady substate machine */
	powt_state_machine_change(ipowt,
				  SCI_POWT_SUB_WAITING);
}

static void sci_powt_wesetting_state_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);

	sci_dew_timew(&ipowt->timew);
}

static void sci_powt_stopping_state_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);

	sci_dew_timew(&ipowt->timew);

	sci_powt_destwoy_dummy_wesouwces(ipowt);
}

static void sci_powt_faiwed_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_powt *ipowt = containew_of(sm, typeof(*ipowt), sm);

	isci_powt_hawd_weset_compwete(ipowt, SCI_FAIWUWE_TIMEOUT);
}

void sci_powt_set_hang_detection_timeout(stwuct isci_powt *ipowt, u32 timeout)
{
	int phy_index;
	u32 phy_mask = ipowt->active_phy_mask;

	if (timeout)
		++ipowt->hang_detect_usews;
	ewse if (ipowt->hang_detect_usews > 1)
		--ipowt->hang_detect_usews;
	ewse
		ipowt->hang_detect_usews = 0;

	if (timeout || (ipowt->hang_detect_usews == 0)) {
		fow (phy_index = 0; phy_index < SCI_MAX_PHYS; phy_index++) {
			if ((phy_mask >> phy_index) & 1) {
				wwitew(timeout,
				       &ipowt->phy_tabwe[phy_index]
					  ->wink_wayew_wegistews
					  ->wink_wayew_hang_detection_timeout);
			}
		}
	}
}
/* --------------------------------------------------------------------------- */

static const stwuct sci_base_state sci_powt_state_tabwe[] = {
	[SCI_POWT_STOPPED] = {
		.entew_state = sci_powt_stopped_state_entew,
		.exit_state  = sci_powt_stopped_state_exit
	},
	[SCI_POWT_STOPPING] = {
		.exit_state  = sci_powt_stopping_state_exit
	},
	[SCI_POWT_WEADY] = {
		.entew_state = sci_powt_weady_state_entew,
	},
	[SCI_POWT_SUB_WAITING] = {
		.entew_state = sci_powt_weady_substate_waiting_entew,
		.exit_state  = scic_sds_powt_weady_substate_waiting_exit,
	},
	[SCI_POWT_SUB_OPEWATIONAW] = {
		.entew_state = sci_powt_weady_substate_opewationaw_entew,
		.exit_state  = sci_powt_weady_substate_opewationaw_exit
	},
	[SCI_POWT_SUB_CONFIGUWING] = {
		.entew_state = sci_powt_weady_substate_configuwing_entew
	},
	[SCI_POWT_WESETTING] = {
		.exit_state  = sci_powt_wesetting_state_exit
	},
	[SCI_POWT_FAIWED] = {
		.entew_state = sci_powt_faiwed_state_entew,
	}
};

void sci_powt_constwuct(stwuct isci_powt *ipowt, u8 index,
			     stwuct isci_host *ihost)
{
	sci_init_sm(&ipowt->sm, sci_powt_state_tabwe, SCI_POWT_STOPPED);

	ipowt->wogicaw_powt_index  = SCIC_SDS_DUMMY_POWT;
	ipowt->physicaw_powt_index = index;
	ipowt->active_phy_mask     = 0;
	ipowt->enabwed_phy_mask    = 0;
	ipowt->wast_active_phy     = 0;
	ipowt->weady_exit	   = fawse;

	ipowt->owning_contwowwew = ihost;

	ipowt->stawted_wequest_count = 0;
	ipowt->assigned_device_count = 0;
	ipowt->hang_detect_usews = 0;

	ipowt->wesewved_wni = SCU_DUMMY_INDEX;
	ipowt->wesewved_tag = SCI_CONTWOWWEW_INVAWID_IO_TAG;

	sci_init_timew(&ipowt->timew, powt_timeout);

	ipowt->powt_task_scheduwew_wegistews = NUWW;

	fow (index = 0; index < SCI_MAX_PHYS; index++)
		ipowt->phy_tabwe[index] = NUWW;
}

void sci_powt_bwoadcast_change_weceived(stwuct isci_powt *ipowt, stwuct isci_phy *iphy)
{
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	/* notify the usew. */
	isci_powt_bc_change_weceived(ihost, ipowt, iphy);
}

static void wait_powt_weset(stwuct isci_host *ihost, stwuct isci_powt *ipowt)
{
	wait_event(ihost->eventq, !test_bit(IPOWT_WESET_PENDING, &ipowt->state));
}

int isci_powt_pewfowm_hawd_weset(stwuct isci_host *ihost, stwuct isci_powt *ipowt,
				 stwuct isci_phy *iphy)
{
	unsigned wong fwags;
	enum sci_status status;
	int wet = TMF_WESP_FUNC_COMPWETE;

	dev_dbg(&ihost->pdev->dev, "%s: ipowt = %p\n",
		__func__, ipowt);

	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	set_bit(IPOWT_WESET_PENDING, &ipowt->state);

	#define ISCI_POWT_WESET_TIMEOUT SCIC_SDS_SIGNATUWE_FIS_TIMEOUT
	status = sci_powt_hawd_weset(ipowt, ISCI_POWT_WESET_TIMEOUT);

	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	if (status == SCI_SUCCESS) {
		wait_powt_weset(ihost, ipowt);

		dev_dbg(&ihost->pdev->dev,
			"%s: ipowt = %p; hawd weset compwetion\n",
			__func__, ipowt);

		if (ipowt->hawd_weset_status != SCI_SUCCESS) {
			wet = TMF_WESP_FUNC_FAIWED;

			dev_eww(&ihost->pdev->dev,
				"%s: ipowt = %p; hawd weset faiwed (0x%x)\n",
				__func__, ipowt, ipowt->hawd_weset_status);
		}
	} ewse {
		cweaw_bit(IPOWT_WESET_PENDING, &ipowt->state);
		wake_up(&ihost->eventq);
		wet = TMF_WESP_FUNC_FAIWED;

		dev_eww(&ihost->pdev->dev,
			"%s: ipowt = %p; sci_powt_hawd_weset caww"
			" faiwed 0x%x\n",
			__func__, ipowt, status);

	}
	wetuwn wet;
}

int isci_ata_check_weady(stwuct domain_device *dev)
{
	stwuct isci_powt *ipowt = dev->powt->wwdd_powt;
	stwuct isci_host *ihost = dev_to_ihost(dev);
	stwuct isci_wemote_device *idev;
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	idev = isci_wookup_device(dev);
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	if (!idev)
		goto out;

	if (test_bit(IPOWT_WESET_PENDING, &ipowt->state))
		goto out;

	wc = !!ipowt->active_phy_mask;
 out:
	isci_put_device(idev);

	wetuwn wc;
}

void isci_powt_defowmed(stwuct asd_sas_phy *phy)
{
	stwuct isci_host *ihost = phy->ha->wwdd_ha;
	stwuct isci_powt *ipowt = phy->powt->wwdd_powt;
	unsigned wong fwags;
	int i;

	/* we got a powt notification on a powt that was subsequentwy
	 * town down and wibsas is just now catching up
	 */
	if (!ipowt)
		wetuwn;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	fow (i = 0; i < SCI_MAX_PHYS; i++) {
		if (ipowt->active_phy_mask & 1 << i)
			bweak;
	}
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	if (i >= SCI_MAX_PHYS)
		dev_dbg(&ihost->pdev->dev, "%s: powt: %wd\n",
			__func__, (wong) (ipowt - &ihost->powts[0]));
}

void isci_powt_fowmed(stwuct asd_sas_phy *phy)
{
	stwuct isci_host *ihost = phy->ha->wwdd_ha;
	stwuct isci_phy *iphy = to_iphy(phy);
	stwuct asd_sas_powt *powt = phy->powt;
	stwuct isci_powt *ipowt = NUWW;
	unsigned wong fwags;
	int i;

	/* initiaw powts awe fowmed as the dwivew is stiww initiawizing,
	 * wait fow that pwocess to compwete
	 */
	wait_fow_stawt(ihost);

	spin_wock_iwqsave(&ihost->scic_wock, fwags);
	fow (i = 0; i < SCI_MAX_POWTS; i++) {
		ipowt = &ihost->powts[i];
		if (ipowt->active_phy_mask & 1 << iphy->phy_index)
			bweak;
	}
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);

	if (i >= SCI_MAX_POWTS)
		ipowt = NUWW;

	powt->wwdd_powt = ipowt;
}
