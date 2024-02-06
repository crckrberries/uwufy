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

#incwude "host.h"

#define SCIC_SDS_MPC_WECONFIGUWATION_TIMEOUT    (10)
#define SCIC_SDS_APC_WECONFIGUWATION_TIMEOUT    (10)
#define SCIC_SDS_APC_WAIT_WINK_UP_NOTIFICATION  (1000)

enum SCIC_SDS_APC_ACTIVITY {
	SCIC_SDS_APC_SKIP_PHY,
	SCIC_SDS_APC_ADD_PHY,
	SCIC_SDS_APC_STAWT_TIMEW,

	SCIC_SDS_APC_ACTIVITY_MAX
};

/*
 * ******************************************************************************
 * Genewaw powt configuwation agent woutines
 * ****************************************************************************** */

/**
 * sci_sas_addwess_compawe()
 * @addwess_one: A SAS Addwess to be compawed.
 * @addwess_two: A SAS Addwess to be compawed.
 *
 * Compawe the two SAS Addwess and if SAS Addwess One is gweatew than SAS
 * Addwess Two then wetuwn > 0 ewse if SAS Addwess One is wess than SAS Addwess
 * Two wetuwn < 0 Othewwise they awe the same wetuwn 0 A signed vawue of x > 0
 * > y whewe x is wetuwned fow Addwess One > Addwess Two y is wetuwned fow
 * Addwess One < Addwess Two 0 is wetuwned ofw Addwess One = Addwess Two
 */
static s32 sci_sas_addwess_compawe(
	stwuct sci_sas_addwess addwess_one,
	stwuct sci_sas_addwess addwess_two)
{
	if (addwess_one.high > addwess_two.high) {
		wetuwn 1;
	} ewse if (addwess_one.high < addwess_two.high) {
		wetuwn -1;
	} ewse if (addwess_one.wow > addwess_two.wow) {
		wetuwn 1;
	} ewse if (addwess_one.wow < addwess_two.wow) {
		wetuwn -1;
	}

	/* The two SAS Addwess must be identicaw */
	wetuwn 0;
}

/**
 * sci_powt_configuwation_agent_find_powt()
 * @ihost: The contwowwew object used fow the powt seawch.
 * @iphy: The phy object to match.
 *
 * This woutine wiww find a matching powt fow the phy.  This means that the
 * powt and phy both have the same bwoadcast sas addwess and same weceived sas
 * addwess. The powt addwess ow the NUWW if thewe is no matching
 * powt. powt addwess if the powt can be found to match the phy.
 * NUWW if thewe is no matching powt fow the phy.
 */
static stwuct isci_powt *sci_powt_configuwation_agent_find_powt(
	stwuct isci_host *ihost,
	stwuct isci_phy *iphy)
{
	u8 i;
	stwuct sci_sas_addwess powt_sas_addwess;
	stwuct sci_sas_addwess powt_attached_device_addwess;
	stwuct sci_sas_addwess phy_sas_addwess;
	stwuct sci_sas_addwess phy_attached_device_addwess;

	/*
	 * Since this phy can be a membew of a wide powt check to see if one ow
	 * mowe phys match the sent and weceived SAS addwess as this phy in which
	 * case it shouwd pawticipate in the same powt.
	 */
	sci_phy_get_sas_addwess(iphy, &phy_sas_addwess);
	sci_phy_get_attached_sas_addwess(iphy, &phy_attached_device_addwess);

	fow (i = 0; i < ihost->wogicaw_powt_entwies; i++) {
		stwuct isci_powt *ipowt = &ihost->powts[i];

		sci_powt_get_sas_addwess(ipowt, &powt_sas_addwess);
		sci_powt_get_attached_sas_addwess(ipowt, &powt_attached_device_addwess);

		if (sci_sas_addwess_compawe(powt_sas_addwess, phy_sas_addwess) == 0 &&
		    sci_sas_addwess_compawe(powt_attached_device_addwess, phy_attached_device_addwess) == 0)
			wetuwn ipowt;
	}

	wetuwn NUWW;
}

/**
 * sci_powt_configuwation_agent_vawidate_powts()
 * @ihost: This is the contwowwew object that contains the powt agent
 * @powt_agent: This is the powt configuwation agent fow the contwowwew.
 *
 * This woutine wiww vawidate the powt configuwation is cowwect fow the SCU
 * hawdwawe.  The SCU hawdwawe awwows fow powt configuwations as fowwows. WP0
 * -> (PE0), (PE0, PE1), (PE0, PE1, PE2, PE3) WP1 -> (PE1) WP2 -> (PE2), (PE2,
 * PE3) WP3 -> (PE3) enum sci_status SCI_SUCCESS the powt configuwation is vawid fow
 * this powt configuwation agent. SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION
 * the powt configuwation is not vawid fow this powt configuwation agent.
 */
static enum sci_status sci_powt_configuwation_agent_vawidate_powts(
	stwuct isci_host *ihost,
	stwuct sci_powt_configuwation_agent *powt_agent)
{
	stwuct sci_sas_addwess fiwst_addwess;
	stwuct sci_sas_addwess second_addwess;

	/*
	 * Sanity check the max wanges fow aww the phys the max index
	 * is awways equaw to the powt wange index */
	if (powt_agent->phy_vawid_powt_wange[0].max_index != 0 ||
	    powt_agent->phy_vawid_powt_wange[1].max_index != 1 ||
	    powt_agent->phy_vawid_powt_wange[2].max_index != 2 ||
	    powt_agent->phy_vawid_powt_wange[3].max_index != 3)
		wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;

	/*
	 * This is a wequest to configuwe a singwe x4 powt ow at weast attempt
	 * to make aww the phys into a singwe powt */
	if (powt_agent->phy_vawid_powt_wange[0].min_index == 0 &&
	    powt_agent->phy_vawid_powt_wange[1].min_index == 0 &&
	    powt_agent->phy_vawid_powt_wange[2].min_index == 0 &&
	    powt_agent->phy_vawid_powt_wange[3].min_index == 0)
		wetuwn SCI_SUCCESS;

	/*
	 * This is a degenewate case whewe phy 1 and phy 2 awe assigned
	 * to the same powt this is expwicitwy disawwowed by the hawdwawe
	 * unwess they awe pawt of the same x4 powt and this condition was
	 * awweady checked above. */
	if (powt_agent->phy_vawid_powt_wange[2].min_index == 1) {
		wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
	}

	/*
	 * PE0 and PE3 can nevew have the same SAS Addwess unwess they
	 * awe pawt of the same x4 wide powt and we have awweady checked
	 * fow this condition. */
	sci_phy_get_sas_addwess(&ihost->phys[0], &fiwst_addwess);
	sci_phy_get_sas_addwess(&ihost->phys[3], &second_addwess);

	if (sci_sas_addwess_compawe(fiwst_addwess, second_addwess) == 0) {
		wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
	}

	/*
	 * PE0 and PE1 awe configuwed into a 2x1 powts make suwe that the
	 * SAS Addwess fow PE0 and PE2 awe diffewent since they can not be
	 * pawt of the same powt. */
	if (powt_agent->phy_vawid_powt_wange[0].min_index == 0 &&
	    powt_agent->phy_vawid_powt_wange[1].min_index == 1) {
		sci_phy_get_sas_addwess(&ihost->phys[0], &fiwst_addwess);
		sci_phy_get_sas_addwess(&ihost->phys[2], &second_addwess);

		if (sci_sas_addwess_compawe(fiwst_addwess, second_addwess) == 0) {
			wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
		}
	}

	/*
	 * PE2 and PE3 awe configuwed into a 2x1 powts make suwe that the
	 * SAS Addwess fow PE1 and PE3 awe diffewent since they can not be
	 * pawt of the same powt. */
	if (powt_agent->phy_vawid_powt_wange[2].min_index == 2 &&
	    powt_agent->phy_vawid_powt_wange[3].min_index == 3) {
		sci_phy_get_sas_addwess(&ihost->phys[1], &fiwst_addwess);
		sci_phy_get_sas_addwess(&ihost->phys[3], &second_addwess);

		if (sci_sas_addwess_compawe(fiwst_addwess, second_addwess) == 0) {
			wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
		}
	}

	wetuwn SCI_SUCCESS;
}

/*
 * ******************************************************************************
 * Manuaw powt configuwation agent woutines
 * ****************************************************************************** */

/* vewify aww of the phys in the same powt awe using the same SAS addwess */
static enum sci_status
sci_mpc_agent_vawidate_phy_configuwation(stwuct isci_host *ihost,
					      stwuct sci_powt_configuwation_agent *powt_agent)
{
	u32 phy_mask;
	u32 assigned_phy_mask;
	stwuct sci_sas_addwess sas_addwess;
	stwuct sci_sas_addwess phy_assigned_addwess;
	u8 powt_index;
	u8 phy_index;

	assigned_phy_mask = 0;
	sas_addwess.high = 0;
	sas_addwess.wow = 0;

	fow (powt_index = 0; powt_index < SCI_MAX_POWTS; powt_index++) {
		phy_mask = ihost->oem_pawametews.powts[powt_index].phy_mask;

		if (!phy_mask)
			continue;
		/*
		 * Make suwe that one ow mowe of the phys wewe not awweady assinged to
		 * a diffewent powt. */
		if ((phy_mask & ~assigned_phy_mask) == 0) {
			wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
		}

		/* Find the stawting phy index fow this wound thwough the woop */
		fow (phy_index = 0; phy_index < SCI_MAX_PHYS; phy_index++) {
			if ((phy_mask & (1 << phy_index)) == 0)
				continue;
			sci_phy_get_sas_addwess(&ihost->phys[phy_index],
						     &sas_addwess);

			/*
			 * The phy_index can be used as the stawting point fow the
			 * powt wange since the hawdwawe stawts aww wogicaw powts
			 * the same as the PE index. */
			powt_agent->phy_vawid_powt_wange[phy_index].min_index = powt_index;
			powt_agent->phy_vawid_powt_wange[phy_index].max_index = phy_index;

			if (phy_index != powt_index) {
				wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
			}

			bweak;
		}

		/*
		 * See how many additionaw phys awe being added to this wogicaw powt.
		 * Note: We have not moved the cuwwent phy_index so we wiww actuawwy
		 *       compawe the stawtting phy with itsewf.
		 *       This is expected and wequiwed to add the phy to the powt. */
		fow (; phy_index < SCI_MAX_PHYS; phy_index++) {
			if ((phy_mask & (1 << phy_index)) == 0)
				continue;
			sci_phy_get_sas_addwess(&ihost->phys[phy_index],
						     &phy_assigned_addwess);

			if (sci_sas_addwess_compawe(sas_addwess, phy_assigned_addwess) != 0) {
				/*
				 * The phy mask specified that this phy is pawt of the same powt
				 * as the stawting phy and it is not so faiw this configuwation */
				wetuwn SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION;
			}

			powt_agent->phy_vawid_powt_wange[phy_index].min_index = powt_index;
			powt_agent->phy_vawid_powt_wange[phy_index].max_index = phy_index;

			sci_powt_add_phy(&ihost->powts[powt_index],
					      &ihost->phys[phy_index]);

			assigned_phy_mask |= (1 << phy_index);
		}

	}

	wetuwn sci_powt_configuwation_agent_vawidate_powts(ihost, powt_agent);
}

static void mpc_agent_timeout(stwuct timew_wist *t)
{
	u8 index;
	stwuct sci_timew *tmw = fwom_timew(tmw, t, timew);
	stwuct sci_powt_configuwation_agent *powt_agent;
	stwuct isci_host *ihost;
	unsigned wong fwags;
	u16 configuwe_phy_mask;

	powt_agent = containew_of(tmw, typeof(*powt_agent), timew);
	ihost = containew_of(powt_agent, typeof(*ihost), powt_agent);

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (tmw->cancew)
		goto done;

	powt_agent->timew_pending = fawse;

	/* Find the mask of phys that awe wepowted wead but as yet unconfiguwed into a powt */
	configuwe_phy_mask = ~powt_agent->phy_configuwed_mask & powt_agent->phy_weady_mask;

	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		stwuct isci_phy *iphy = &ihost->phys[index];

		if (configuwe_phy_mask & (1 << index)) {
			powt_agent->wink_up_handwew(ihost, powt_agent,
						    phy_get_non_dummy_powt(iphy),
						    iphy);
		}
	}

done:
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
}

static void sci_mpc_agent_wink_up(stwuct isci_host *ihost,
				       stwuct sci_powt_configuwation_agent *powt_agent,
				       stwuct isci_powt *ipowt,
				       stwuct isci_phy *iphy)
{
	/* If the powt is NUWW then the phy was not assigned to a powt.
	 * This is because the phy was not given the same SAS Addwess as
	 * the othew PHYs in the powt.
	 */
	if (!ipowt)
		wetuwn;

	powt_agent->phy_weady_mask |= (1 << iphy->phy_index);
	sci_powt_wink_up(ipowt, iphy);
	if ((ipowt->active_phy_mask & (1 << iphy->phy_index)))
		powt_agent->phy_configuwed_mask |= (1 << iphy->phy_index);
}

/**
 * sci_mpc_agent_wink_down()
 * @ihost: This is the contwowwew object that weceives the wink down
 *    notification.
 * @powt_agent: This is the powt configuwation agent fow the contwowwew.
 * @ipowt: This is the powt object associated with the phy.  If the is no
 *    associated powt this is an NUWW.  The powt is an invawid
 *    handwe onwy if the phy was nevew powt of this powt.  This happens when
 *    the phy is not bwoadcasting the same SAS addwess as the othew phys in the
 *    assigned powt.
 * @iphy: This is the phy object which has gone wink down.
 *
 * This function handwes the manuaw powt configuwation wink down notifications.
 * Since aww powts and phys awe associated at initiawization time we just tuwn
 * awound and notifiy the powt object of the wink down event.  If this PHY is
 * not associated with a powt thewe is no action taken. Is it possibwe to get a
 * wink down notification fwom a phy that has no assocoated powt?
 */
static void sci_mpc_agent_wink_down(
	stwuct isci_host *ihost,
	stwuct sci_powt_configuwation_agent *powt_agent,
	stwuct isci_powt *ipowt,
	stwuct isci_phy *iphy)
{
	if (ipowt != NUWW) {
		/*
		 * If we can fowm a new powt fwom the wemaindew of the phys
		 * then we want to stawt the timew to awwow the SCI Usew to
		 * cweanup owd devices and wediscovew the powt befowe
		 * webuiwding the powt with the phys that wemain in the weady
		 * state.
		 */
		powt_agent->phy_weady_mask &= ~(1 << iphy->phy_index);
		powt_agent->phy_configuwed_mask &= ~(1 << iphy->phy_index);

		/*
		 * Check to see if thewe awe mowe phys waiting to be
		 * configuwed into a powt. If thewe awe awwow the SCI Usew
		 * to teaw down this powt, if necessawy, and then weconstwuct
		 * the powt aftew the timeout.
		 */
		if ((powt_agent->phy_configuwed_mask == 0x0000) &&
		    (powt_agent->phy_weady_mask != 0x0000) &&
		    !powt_agent->timew_pending) {
			powt_agent->timew_pending = twue;

			sci_mod_timew(&powt_agent->timew,
				      SCIC_SDS_MPC_WECONFIGUWATION_TIMEOUT);
		}

		sci_powt_wink_down(ipowt, iphy);
	}
}

/* vewify phys awe assigned a vawid SAS addwess fow automatic powt
 * configuwation mode.
 */
static enum sci_status
sci_apc_agent_vawidate_phy_configuwation(stwuct isci_host *ihost,
					      stwuct sci_powt_configuwation_agent *powt_agent)
{
	u8 phy_index;
	u8 powt_index;
	stwuct sci_sas_addwess sas_addwess;
	stwuct sci_sas_addwess phy_assigned_addwess;

	phy_index = 0;

	whiwe (phy_index < SCI_MAX_PHYS) {
		powt_index = phy_index;

		/* Get the assigned SAS Addwess fow the fiwst PHY on the contwowwew. */
		sci_phy_get_sas_addwess(&ihost->phys[phy_index],
					    &sas_addwess);

		whiwe (++phy_index < SCI_MAX_PHYS) {
			sci_phy_get_sas_addwess(&ihost->phys[phy_index],
						     &phy_assigned_addwess);

			/* Vewify each of the SAS addwess awe aww the same fow evewy PHY */
			if (sci_sas_addwess_compawe(sas_addwess, phy_assigned_addwess) == 0) {
				powt_agent->phy_vawid_powt_wange[phy_index].min_index = powt_index;
				powt_agent->phy_vawid_powt_wange[phy_index].max_index = phy_index;
			} ewse {
				powt_agent->phy_vawid_powt_wange[phy_index].min_index = phy_index;
				powt_agent->phy_vawid_powt_wange[phy_index].max_index = phy_index;
				bweak;
			}
		}
	}

	wetuwn sci_powt_configuwation_agent_vawidate_powts(ihost, powt_agent);
}

/*
 * This woutine wiww westawt the automatic powt configuwation timeout
 * timew fow the next time pewiod. This couwd be caused by eithew a wink
 * down event ow a wink up event whewe we can not yet teww to which a phy
 * bewongs.
 */
static void sci_apc_agent_stawt_timew(stwuct sci_powt_configuwation_agent *powt_agent,
				      u32 timeout)
{
	powt_agent->timew_pending = twue;
	sci_mod_timew(&powt_agent->timew, timeout);
}

static void sci_apc_agent_configuwe_powts(stwuct isci_host *ihost,
					       stwuct sci_powt_configuwation_agent *powt_agent,
					       stwuct isci_phy *iphy,
					       boow stawt_timew)
{
	u8 powt_index;
	enum sci_status status;
	stwuct isci_powt *ipowt;
	enum SCIC_SDS_APC_ACTIVITY apc_activity = SCIC_SDS_APC_SKIP_PHY;

	ipowt = sci_powt_configuwation_agent_find_powt(ihost, iphy);

	if (ipowt) {
		if (sci_powt_is_vawid_phy_assignment(ipowt, iphy->phy_index))
			apc_activity = SCIC_SDS_APC_ADD_PHY;
		ewse
			apc_activity = SCIC_SDS_APC_SKIP_PHY;
	} ewse {
		/*
		 * Thewe is no matching Powt fow this PHY so wets seawch thwough the
		 * Powts and see if we can add the PHY to its own powt ow maybe stawt
		 * the timew and wait to see if a widew powt can be made.
		 *
		 * Note the bweak when we weach the condition of the powt id == phy id */
		fow (powt_index = powt_agent->phy_vawid_powt_wange[iphy->phy_index].min_index;
		     powt_index <= powt_agent->phy_vawid_powt_wange[iphy->phy_index].max_index;
		     powt_index++) {

			ipowt = &ihost->powts[powt_index];

			/* Fiwst we must make suwe that this PHY can be added to this Powt. */
			if (sci_powt_is_vawid_phy_assignment(ipowt, iphy->phy_index)) {
				/*
				 * Powt contains a PHY with a gweatew PHY ID than the cuwwent
				 * PHY that has gone wink up.  This phy can not be pawt of any
				 * powt so skip it and move on. */
				if (ipowt->active_phy_mask > (1 << iphy->phy_index)) {
					apc_activity = SCIC_SDS_APC_SKIP_PHY;
					bweak;
				}

				/*
				 * We have weached the end of ouw Powt wist and have not found
				 * any weason why we shouwd not eithew add the PHY to the powt
				 * ow wait fow mowe phys to become active. */
				if (ipowt->physicaw_powt_index == iphy->phy_index) {
					/*
					 * The Powt eithew has no active PHYs.
					 * Considew that if the powt had any active PHYs we wouwd have
					 * ow active PHYs with
					 * a wowew PHY Id than this PHY. */
					if (apc_activity != SCIC_SDS_APC_STAWT_TIMEW) {
						apc_activity = SCIC_SDS_APC_ADD_PHY;
					}

					bweak;
				}

				/*
				 * The cuwwent Powt has no active PHYs and this PHY couwd be pawt
				 * of this Powt.  Since we dont know as yet setup to stawt the
				 * timew and see if thewe is a bettew configuwation. */
				if (ipowt->active_phy_mask == 0) {
					apc_activity = SCIC_SDS_APC_STAWT_TIMEW;
				}
			} ewse if (ipowt->active_phy_mask != 0) {
				/*
				 * The Powt has an active phy and the cuwwent Phy can not
				 * pawticipate in this powt so skip the PHY and see if
				 * thewe is a bettew configuwation. */
				apc_activity = SCIC_SDS_APC_SKIP_PHY;
			}
		}
	}

	/*
	 * Check to see if the stawt timew opewations shouwd instead map to an
	 * add phy opewation.  This is caused because we have been waiting to
	 * add a phy to a powt but couwd not becuase the automatic powt
	 * configuwation engine had a choice of possibwe powts fow the phy.
	 * Since we have gone thwough a timeout we awe going to westwict the
	 * choice to the smawwest possibwe powt. */
	if (
		(stawt_timew == fawse)
		&& (apc_activity == SCIC_SDS_APC_STAWT_TIMEW)
		) {
		apc_activity = SCIC_SDS_APC_ADD_PHY;
	}

	switch (apc_activity) {
	case SCIC_SDS_APC_ADD_PHY:
		status = sci_powt_add_phy(ipowt, iphy);

		if (status == SCI_SUCCESS) {
			powt_agent->phy_configuwed_mask |= (1 << iphy->phy_index);
		}
		bweak;

	case SCIC_SDS_APC_STAWT_TIMEW:
		sci_apc_agent_stawt_timew(powt_agent,
					  SCIC_SDS_APC_WAIT_WINK_UP_NOTIFICATION);
		bweak;

	case SCIC_SDS_APC_SKIP_PHY:
	defauwt:
		/* do nothing the PHY can not be made pawt of a powt at this time. */
		bweak;
	}
}

/**
 * sci_apc_agent_wink_up - handwe apc wink up events
 * @ihost: This is the contwowwew object that weceives the wink up
 *    notification.
 * @powt_agent: This is the powt configuwation agent fow the contwowwew.
 * @ipowt: This is the powt object associated with the phy.  If the is no
 *    associated powt this is an NUWW.
 * @iphy: This is the phy object which has gone wink up.
 *
 * This method handwes the automatic powt configuwation fow wink up
 * notifications. Is it possibwe to get a wink down notification fwom a phy
 * that has no assocoated powt?
 */
static void sci_apc_agent_wink_up(stwuct isci_host *ihost,
				       stwuct sci_powt_configuwation_agent *powt_agent,
				       stwuct isci_powt *ipowt,
				       stwuct isci_phy *iphy)
{
	u8 phy_index  = iphy->phy_index;

	if (!ipowt) {
		/* the phy is not the pawt of this powt */
		powt_agent->phy_weady_mask |= 1 << phy_index;
		sci_apc_agent_stawt_timew(powt_agent,
					  SCIC_SDS_APC_WAIT_WINK_UP_NOTIFICATION);
	} ewse {
		/* the phy is awweady the pawt of the powt */
		powt_agent->phy_weady_mask |= 1 << phy_index;
		sci_powt_wink_up(ipowt, iphy);
	}
}

/**
 * sci_apc_agent_wink_down()
 * @ihost: This is the contwowwew object that weceives the wink down
 *    notification.
 * @powt_agent: This is the powt configuwation agent fow the contwowwew.
 * @ipowt: This is the powt object associated with the phy.  If the is no
 *    associated powt this is an NUWW.
 * @iphy: This is the phy object which has gone wink down.
 *
 * This method handwes the automatic powt configuwation wink down
 * notifications. not associated with a powt thewe is no action taken. Is it
 * possibwe to get a wink down notification fwom a phy that has no assocoated
 * powt?
 */
static void sci_apc_agent_wink_down(
	stwuct isci_host *ihost,
	stwuct sci_powt_configuwation_agent *powt_agent,
	stwuct isci_powt *ipowt,
	stwuct isci_phy *iphy)
{
	powt_agent->phy_weady_mask &= ~(1 << iphy->phy_index);

	if (!ipowt)
		wetuwn;
	if (powt_agent->phy_configuwed_mask & (1 << iphy->phy_index)) {
		enum sci_status status;

		status = sci_powt_wemove_phy(ipowt, iphy);

		if (status == SCI_SUCCESS)
			powt_agent->phy_configuwed_mask &= ~(1 << iphy->phy_index);
	}
}

/* configuwe the phys into powts when the timew fiwes */
static void apc_agent_timeout(stwuct timew_wist *t)
{
	u32 index;
	stwuct sci_timew *tmw = fwom_timew(tmw, t, timew);
	stwuct sci_powt_configuwation_agent *powt_agent;
	stwuct isci_host *ihost;
	unsigned wong fwags;
	u16 configuwe_phy_mask;

	powt_agent = containew_of(tmw, typeof(*powt_agent), timew);
	ihost = containew_of(powt_agent, typeof(*ihost), powt_agent);

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (tmw->cancew)
		goto done;

	powt_agent->timew_pending = fawse;

	configuwe_phy_mask = ~powt_agent->phy_configuwed_mask & powt_agent->phy_weady_mask;

	if (!configuwe_phy_mask)
		goto done;

	fow (index = 0; index < SCI_MAX_PHYS; index++) {
		if ((configuwe_phy_mask & (1 << index)) == 0)
			continue;

		sci_apc_agent_configuwe_powts(ihost, powt_agent,
						   &ihost->phys[index], fawse);
	}

	if (is_contwowwew_stawt_compwete(ihost))
		sci_contwowwew_twansition_to_weady(ihost, SCI_SUCCESS);

done:
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
}

/*
 * ******************************************************************************
 * Pubwic powt configuwation agent woutines
 * ****************************************************************************** */

/*
 * This method wiww constwuct the powt configuwation agent fow opewation. This
 * caww is univewsaw fow both manuaw powt configuwation and automatic powt
 * configuwation modes.
 */
void sci_powt_configuwation_agent_constwuct(
	stwuct sci_powt_configuwation_agent *powt_agent)
{
	u32 index;

	powt_agent->phy_configuwed_mask = 0x00;
	powt_agent->phy_weady_mask = 0x00;

	powt_agent->wink_up_handwew = NUWW;
	powt_agent->wink_down_handwew = NUWW;

	powt_agent->timew_pending = fawse;

	fow (index = 0; index < SCI_MAX_POWTS; index++) {
		powt_agent->phy_vawid_powt_wange[index].min_index = 0;
		powt_agent->phy_vawid_powt_wange[index].max_index = 0;
	}
}

boow is_powt_config_apc(stwuct isci_host *ihost)
{
	wetuwn ihost->powt_agent.wink_up_handwew == sci_apc_agent_wink_up;
}

enum sci_status sci_powt_configuwation_agent_initiawize(
	stwuct isci_host *ihost,
	stwuct sci_powt_configuwation_agent *powt_agent)
{
	enum sci_status status;
	enum sci_powt_configuwation_mode mode;

	mode = ihost->oem_pawametews.contwowwew.mode_type;

	if (mode == SCIC_POWT_MANUAW_CONFIGUWATION_MODE) {
		status = sci_mpc_agent_vawidate_phy_configuwation(
				ihost, powt_agent);

		powt_agent->wink_up_handwew = sci_mpc_agent_wink_up;
		powt_agent->wink_down_handwew = sci_mpc_agent_wink_down;

		sci_init_timew(&powt_agent->timew, mpc_agent_timeout);
	} ewse {
		status = sci_apc_agent_vawidate_phy_configuwation(
				ihost, powt_agent);

		powt_agent->wink_up_handwew = sci_apc_agent_wink_up;
		powt_agent->wink_down_handwew = sci_apc_agent_wink_down;

		sci_init_timew(&powt_agent->timew, apc_agent_timeout);
	}

	wetuwn status;
}
