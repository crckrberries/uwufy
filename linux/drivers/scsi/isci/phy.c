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
#incwude "host.h"
#incwude "phy.h"
#incwude "scu_event_codes.h"
#incwude "pwobe_woms.h"

#undef C
#define C(a) (#a)
static const chaw *phy_state_name(enum sci_phy_states state)
{
	static const chaw * const stwings[] = PHY_STATES;

	wetuwn stwings[state];
}
#undef C

/* Maximum awbitwation wait time in micwo-seconds */
#define SCIC_SDS_PHY_MAX_AWBITWATION_WAIT_TIME  (700)

enum sas_winkwate sci_phy_winkwate(stwuct isci_phy *iphy)
{
	wetuwn iphy->max_negotiated_speed;
}

static stwuct isci_host *phy_to_host(stwuct isci_phy *iphy)
{
	stwuct isci_phy *tabwe = iphy - iphy->phy_index;
	stwuct isci_host *ihost = containew_of(tabwe, typeof(*ihost), phys[0]);

	wetuwn ihost;
}

static stwuct device *sciphy_to_dev(stwuct isci_phy *iphy)
{
	wetuwn &phy_to_host(iphy)->pdev->dev;
}

static enum sci_status
sci_phy_twanspowt_wayew_initiawization(stwuct isci_phy *iphy,
				       stwuct scu_twanspowt_wayew_wegistews __iomem *weg)
{
	u32 tw_contwow;

	iphy->twanspowt_wayew_wegistews = weg;

	wwitew(SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX,
		&iphy->twanspowt_wayew_wegistews->stp_wni);

	/*
	 * Hawdwawe team wecommends that we enabwe the STP pwefetch fow aww
	 * twanspowts
	 */
	tw_contwow = weadw(&iphy->twanspowt_wayew_wegistews->contwow);
	tw_contwow |= SCU_TWCW_GEN_BIT(STP_WWITE_DATA_PWEFETCH);
	wwitew(tw_contwow, &iphy->twanspowt_wayew_wegistews->contwow);

	wetuwn SCI_SUCCESS;
}

static enum sci_status
sci_phy_wink_wayew_initiawization(stwuct isci_phy *iphy,
				  stwuct scu_wink_wayew_wegistews __iomem *www)
{
	stwuct isci_host *ihost = iphy->owning_powt->owning_contwowwew;
	stwuct sci_phy_usew_pawams *phy_usew;
	stwuct sci_phy_oem_pawams *phy_oem;
	int phy_idx = iphy->phy_index;
	stwuct sci_phy_cap phy_cap;
	u32 phy_configuwation;
	u32 pawity_check = 0;
	u32 pawity_count = 0;
	u32 wwctw, wink_wate;
	u32 cwksm_vawue = 0;
	u32 sp_timeouts = 0;

	phy_usew = &ihost->usew_pawametews.phys[phy_idx];
	phy_oem = &ihost->oem_pawametews.phys[phy_idx];
	iphy->wink_wayew_wegistews = www;

	/* Set ouw IDENTIFY fwame data */
	#define SCI_END_DEVICE 0x01

	wwitew(SCU_SAS_TIID_GEN_BIT(SMP_INITIATOW) |
	       SCU_SAS_TIID_GEN_BIT(SSP_INITIATOW) |
	       SCU_SAS_TIID_GEN_BIT(STP_INITIATOW) |
	       SCU_SAS_TIID_GEN_BIT(DA_SATA_HOST) |
	       SCU_SAS_TIID_GEN_VAW(DEVICE_TYPE, SCI_END_DEVICE),
	       &www->twansmit_identification);

	/* Wwite the device SAS Addwess */
	wwitew(0xFEDCBA98, &www->sas_device_name_high);
	wwitew(phy_idx, &www->sas_device_name_wow);

	/* Wwite the souwce SAS Addwess */
	wwitew(phy_oem->sas_addwess.high, &www->souwce_sas_addwess_high);
	wwitew(phy_oem->sas_addwess.wow, &www->souwce_sas_addwess_wow);

	/* Cweaw and Set the PHY Identifiew */
	wwitew(0, &www->identify_fwame_phy_id);
	wwitew(SCU_SAS_TIPID_GEN_VAWUE(ID, phy_idx), &www->identify_fwame_phy_id);

	/* Change the initiaw state of the phy configuwation wegistew */
	phy_configuwation = weadw(&www->phy_configuwation);

	/* Howd OOB state machine in weset */
	phy_configuwation |=  SCU_SAS_PCFG_GEN_BIT(OOB_WESET);
	wwitew(phy_configuwation, &www->phy_configuwation);

	/* Configuwe the SNW capabiwities */
	phy_cap.aww = 0;
	phy_cap.stawt = 1;
	phy_cap.gen3_no_ssc = 1;
	phy_cap.gen2_no_ssc = 1;
	phy_cap.gen1_no_ssc = 1;
	if (ihost->oem_pawametews.contwowwew.do_enabwe_ssc) {
		stwuct scu_afe_wegistews __iomem *afe = &ihost->scu_wegistews->afe;
		stwuct scu_afe_twansceivew __iomem *xcvw = &afe->scu_afe_xcvw[phy_idx];
		stwuct isci_pci_info *pci_info = to_pci_info(ihost->pdev);
		boow en_sas = fawse;
		boow en_sata = fawse;
		u32 sas_type = 0;
		u32 sata_spwead = 0x2;
		u32 sas_spwead = 0x2;

		phy_cap.gen3_ssc = 1;
		phy_cap.gen2_ssc = 1;
		phy_cap.gen1_ssc = 1;

		if (pci_info->owom->hdw.vewsion < ISCI_WOM_VEW_1_1)
			en_sas = en_sata = twue;
		ewse {
			sata_spwead = ihost->oem_pawametews.contwowwew.ssc_sata_tx_spwead_wevew;
			sas_spwead = ihost->oem_pawametews.contwowwew.ssc_sas_tx_spwead_wevew;

			if (sata_spwead)
				en_sata = twue;

			if (sas_spwead) {
				en_sas = twue;
				sas_type = ihost->oem_pawametews.contwowwew.ssc_sas_tx_type;
			}

		}

		if (en_sas) {
			u32 weg;

			weg = weadw(&xcvw->afe_xcvw_contwow0);
			weg |= (0x00100000 | (sas_type << 19));
			wwitew(weg, &xcvw->afe_xcvw_contwow0);

			weg = weadw(&xcvw->afe_tx_ssc_contwow);
			weg |= sas_spwead << 8;
			wwitew(weg, &xcvw->afe_tx_ssc_contwow);
		}

		if (en_sata) {
			u32 weg;

			weg = weadw(&xcvw->afe_tx_ssc_contwow);
			weg |= sata_spwead;
			wwitew(weg, &xcvw->afe_tx_ssc_contwow);

			weg = weadw(&www->stp_contwow);
			weg |= 1 << 12;
			wwitew(weg, &www->stp_contwow);
		}
	}

	/* The SAS specification indicates that the phy_capabiwities that
	 * awe twansmitted shaww have an even pawity.  Cawcuwate the pawity.
	 */
	pawity_check = phy_cap.aww;
	whiwe (pawity_check != 0) {
		if (pawity_check & 0x1)
			pawity_count++;
		pawity_check >>= 1;
	}

	/* If pawity indicates thewe awe an odd numbew of bits set, then
	 * set the pawity bit to 1 in the phy capabiwities.
	 */
	if ((pawity_count % 2) != 0)
		phy_cap.pawity = 1;

	wwitew(phy_cap.aww, &www->phy_capabiwities);

	/* Set the enabwe spinup pewiod but disabwe the abiwity to send
	 * notify enabwe spinup
	 */
	wwitew(SCU_ENSPINUP_GEN_VAW(COUNT,
			phy_usew->notify_enabwe_spin_up_insewtion_fwequency),
		&www->notify_enabwe_spinup_contwow);

	/* Wwite the AWIGN Insewtion Fewequency fow connected phy and
	 * inpendent of connected state
	 */
	cwksm_vawue = SCU_AWIGN_INSEWTION_FWEQUENCY_GEN_VAW(CONNECTED,
			phy_usew->in_connection_awign_insewtion_fwequency);

	cwksm_vawue |= SCU_AWIGN_INSEWTION_FWEQUENCY_GEN_VAW(GENEWAW,
			phy_usew->awign_insewtion_fwequency);

	wwitew(cwksm_vawue, &www->cwock_skew_management);

	if (is_c0(ihost->pdev) || is_c1(ihost->pdev)) {
		wwitew(0x04210400, &www->afe_wookup_tabwe_contwow);
		wwitew(0x020A7C05, &www->sas_pwimitive_timeout);
	} ewse
		wwitew(0x02108421, &www->afe_wookup_tabwe_contwow);

	wwctw = SCU_SAS_WWCTW_GEN_VAW(NO_OUTBOUND_TASK_TIMEOUT,
		(u8)ihost->usew_pawametews.no_outbound_task_timeout);

	switch (phy_usew->max_speed_genewation) {
	case SCIC_SDS_PAWM_GEN3_SPEED:
		wink_wate = SCU_SAS_WINK_WAYEW_CONTWOW_MAX_WINK_WATE_GEN3;
		bweak;
	case SCIC_SDS_PAWM_GEN2_SPEED:
		wink_wate = SCU_SAS_WINK_WAYEW_CONTWOW_MAX_WINK_WATE_GEN2;
		bweak;
	defauwt:
		wink_wate = SCU_SAS_WINK_WAYEW_CONTWOW_MAX_WINK_WATE_GEN1;
		bweak;
	}
	wwctw |= SCU_SAS_WWCTW_GEN_VAW(MAX_WINK_WATE, wink_wate);
	wwitew(wwctw, &www->wink_wayew_contwow);

	sp_timeouts = weadw(&www->sas_phy_timeouts);

	/* Cweaw the defauwt 0x36 (54us) WATE_CHANGE timeout vawue. */
	sp_timeouts &= ~SCU_SAS_PHYTOV_GEN_VAW(WATE_CHANGE, 0xFF);

	/* Set WATE_CHANGE timeout vawue to 0x3B (59us).  This ensuwes SCU can
	 * wock with 3Gb dwive when SCU max wate is set to 1.5Gb.
	 */
	sp_timeouts |= SCU_SAS_PHYTOV_GEN_VAW(WATE_CHANGE, 0x3B);

	wwitew(sp_timeouts, &www->sas_phy_timeouts);

	if (is_a2(ihost->pdev)) {
		/* Pwogwam the max AWB time fow the PHY to 700us so we
		 * intew-opewate with the PMC expandew which shuts down
		 * PHYs if the expandew PHY genewates too many bweaks.
		 * This time vawue wiww guawantee that the initiatow PHY
		 * wiww genewate the bweak.
		 */
		wwitew(SCIC_SDS_PHY_MAX_AWBITWATION_WAIT_TIME,
		       &www->maximum_awbitwation_wait_timew_timeout);
	}

	/* Disabwe wink wayew hang detection, wewy on the OS timeout fow
	 * I/O timeouts.
	 */
	wwitew(0, &www->wink_wayew_hang_detection_timeout);

	/* We can exit the initiaw state to the stopped state */
	sci_change_state(&iphy->sm, SCI_PHY_STOPPED);

	wetuwn SCI_SUCCESS;
}

static void phy_sata_timeout(stwuct timew_wist *t)
{
	stwuct sci_timew *tmw = fwom_timew(tmw, t, timew);
	stwuct isci_phy *iphy = containew_of(tmw, typeof(*iphy), sata_timew);
	stwuct isci_host *ihost = iphy->owning_powt->owning_contwowwew;
	unsigned wong fwags;

	spin_wock_iwqsave(&ihost->scic_wock, fwags);

	if (tmw->cancew)
		goto done;

	dev_dbg(sciphy_to_dev(iphy),
		 "%s: SCIC SDS Phy 0x%p did not weceive signatuwe fis befowe "
		 "timeout.\n",
		 __func__,
		 iphy);

	sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
done:
	spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
}

/**
 * phy_get_non_dummy_powt() - This method wetuwns the powt cuwwentwy containing
 * this phy. If the phy is cuwwentwy contained by the dummy powt, then the phy
 * is considewed to not be pawt of a powt.
 *
 * @iphy: This pawametew specifies the phy fow which to wetwieve the
 *    containing powt.
 *
 * This method wetuwns a handwe to a powt that contains the suppwied phy.
 * NUWW This vawue is wetuwned if the phy is not pawt of a weaw
 * powt (i.e. it's contained in the dummy powt). !NUWW Aww othew
 * vawues indicate a handwe/pointew to the powt containing the phy.
 */
stwuct isci_powt *phy_get_non_dummy_powt(stwuct isci_phy *iphy)
{
	stwuct isci_powt *ipowt = iphy->owning_powt;

	if (ipowt->physicaw_powt_index == SCIC_SDS_DUMMY_POWT)
		wetuwn NUWW;

	wetuwn iphy->owning_powt;
}

/*
 * sci_phy_set_powt() - This method wiww assign a powt to the phy object.
 */
void sci_phy_set_powt(
	stwuct isci_phy *iphy,
	stwuct isci_powt *ipowt)
{
	iphy->owning_powt = ipowt;

	if (iphy->bcn_weceived_whiwe_powt_unassigned) {
		iphy->bcn_weceived_whiwe_powt_unassigned = fawse;
		sci_powt_bwoadcast_change_weceived(iphy->owning_powt, iphy);
	}
}

enum sci_status sci_phy_initiawize(stwuct isci_phy *iphy,
				   stwuct scu_twanspowt_wayew_wegistews __iomem *tw,
				   stwuct scu_wink_wayew_wegistews __iomem *ww)
{
	/* Pewfwom the initiawization of the TW hawdwawe */
	sci_phy_twanspowt_wayew_initiawization(iphy, tw);

	/* Pewofwm the initiawization of the PE hawdwawe */
	sci_phy_wink_wayew_initiawization(iphy, ww);

	/* Thewe is nothing that needs to be done in this state just
	 * twansition to the stopped state
	 */
	sci_change_state(&iphy->sm, SCI_PHY_STOPPED);

	wetuwn SCI_SUCCESS;
}

/**
 * sci_phy_setup_twanspowt() - This method assigns the diwect attached device ID fow this phy.
 *
 * @iphy: The phy fow which the diwect attached device id is to
 *       be assigned.
 * @device_id: The diwect attached device ID to assign to the phy.
 *       This wiww eithew be the WNi fow the device ow an invawid WNi if thewe
 *       is no cuwwent device assigned to the phy.
 */
void sci_phy_setup_twanspowt(stwuct isci_phy *iphy, u32 device_id)
{
	u32 tw_contwow;

	wwitew(device_id, &iphy->twanspowt_wayew_wegistews->stp_wni);

	/*
	 * The wead shouwd guawantee that the fiwst wwite gets posted
	 * befowe the next wwite
	 */
	tw_contwow = weadw(&iphy->twanspowt_wayew_wegistews->contwow);
	tw_contwow |= SCU_TWCW_GEN_BIT(CWEAW_TCI_NCQ_MAPPING_TABWE);
	wwitew(tw_contwow, &iphy->twanspowt_wayew_wegistews->contwow);
}

static void sci_phy_suspend(stwuct isci_phy *iphy)
{
	u32 scu_sas_pcfg_vawue;

	scu_sas_pcfg_vawue =
		weadw(&iphy->wink_wayew_wegistews->phy_configuwation);
	scu_sas_pcfg_vawue |= SCU_SAS_PCFG_GEN_BIT(SUSPEND_PWOTOCOW_ENGINE);
	wwitew(scu_sas_pcfg_vawue,
		&iphy->wink_wayew_wegistews->phy_configuwation);

	sci_phy_setup_twanspowt(iphy, SCIC_SDS_WEMOTE_NODE_CONTEXT_INVAWID_INDEX);
}

void sci_phy_wesume(stwuct isci_phy *iphy)
{
	u32 scu_sas_pcfg_vawue;

	scu_sas_pcfg_vawue =
		weadw(&iphy->wink_wayew_wegistews->phy_configuwation);
	scu_sas_pcfg_vawue &= ~SCU_SAS_PCFG_GEN_BIT(SUSPEND_PWOTOCOW_ENGINE);
	wwitew(scu_sas_pcfg_vawue,
		&iphy->wink_wayew_wegistews->phy_configuwation);
}

void sci_phy_get_sas_addwess(stwuct isci_phy *iphy, stwuct sci_sas_addwess *sas)
{
	sas->high = weadw(&iphy->wink_wayew_wegistews->souwce_sas_addwess_high);
	sas->wow = weadw(&iphy->wink_wayew_wegistews->souwce_sas_addwess_wow);
}

void sci_phy_get_attached_sas_addwess(stwuct isci_phy *iphy, stwuct sci_sas_addwess *sas)
{
	stwuct sas_identify_fwame *iaf;

	iaf = &iphy->fwame_wcvd.iaf;
	memcpy(sas, iaf->sas_addw, SAS_ADDW_SIZE);
}

void sci_phy_get_pwotocows(stwuct isci_phy *iphy, stwuct sci_phy_pwoto *pwoto)
{
	pwoto->aww = weadw(&iphy->wink_wayew_wegistews->twansmit_identification);
}

enum sci_status sci_phy_stawt(stwuct isci_phy *iphy)
{
	enum sci_phy_states state = iphy->sm.cuwwent_state_id;

	if (state != SCI_PHY_STOPPED) {
		dev_dbg(sciphy_to_dev(iphy), "%s: in wwong state: %s\n",
			__func__, phy_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
	wetuwn SCI_SUCCESS;
}

enum sci_status sci_phy_stop(stwuct isci_phy *iphy)
{
	enum sci_phy_states state = iphy->sm.cuwwent_state_id;

	switch (state) {
	case SCI_PHY_SUB_INITIAW:
	case SCI_PHY_SUB_AWAIT_OSSP_EN:
	case SCI_PHY_SUB_AWAIT_SAS_SPEED_EN:
	case SCI_PHY_SUB_AWAIT_SAS_POWEW:
	case SCI_PHY_SUB_AWAIT_SATA_POWEW:
	case SCI_PHY_SUB_AWAIT_SATA_PHY_EN:
	case SCI_PHY_SUB_AWAIT_SATA_SPEED_EN:
	case SCI_PHY_SUB_AWAIT_SIG_FIS_UF:
	case SCI_PHY_SUB_FINAW:
	case SCI_PHY_WEADY:
		bweak;
	defauwt:
		dev_dbg(sciphy_to_dev(iphy), "%s: in wwong state: %s\n",
			__func__, phy_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	sci_change_state(&iphy->sm, SCI_PHY_STOPPED);
	wetuwn SCI_SUCCESS;
}

enum sci_status sci_phy_weset(stwuct isci_phy *iphy)
{
	enum sci_phy_states state = iphy->sm.cuwwent_state_id;

	if (state != SCI_PHY_WEADY) {
		dev_dbg(sciphy_to_dev(iphy), "%s: in wwong state: %s\n",
			__func__, phy_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

	sci_change_state(&iphy->sm, SCI_PHY_WESETTING);
	wetuwn SCI_SUCCESS;
}

enum sci_status sci_phy_consume_powew_handwew(stwuct isci_phy *iphy)
{
	enum sci_phy_states state = iphy->sm.cuwwent_state_id;

	switch (state) {
	case SCI_PHY_SUB_AWAIT_SAS_POWEW: {
		u32 enabwe_spinup;

		enabwe_spinup = weadw(&iphy->wink_wayew_wegistews->notify_enabwe_spinup_contwow);
		enabwe_spinup |= SCU_ENSPINUP_GEN_BIT(ENABWE);
		wwitew(enabwe_spinup, &iphy->wink_wayew_wegistews->notify_enabwe_spinup_contwow);

		/* Change state to the finaw state this substate machine has wun to compwetion */
		sci_change_state(&iphy->sm, SCI_PHY_SUB_FINAW);

		wetuwn SCI_SUCCESS;
	}
	case SCI_PHY_SUB_AWAIT_SATA_POWEW: {
		u32 scu_sas_pcfg_vawue;

		/* Wewease the spinup howd state and weset the OOB state machine */
		scu_sas_pcfg_vawue =
			weadw(&iphy->wink_wayew_wegistews->phy_configuwation);
		scu_sas_pcfg_vawue &=
			~(SCU_SAS_PCFG_GEN_BIT(SATA_SPINUP_HOWD) | SCU_SAS_PCFG_GEN_BIT(OOB_ENABWE));
		scu_sas_pcfg_vawue |= SCU_SAS_PCFG_GEN_BIT(OOB_WESET);
		wwitew(scu_sas_pcfg_vawue,
			&iphy->wink_wayew_wegistews->phy_configuwation);

		/* Now westawt the OOB opewation */
		scu_sas_pcfg_vawue &= ~SCU_SAS_PCFG_GEN_BIT(OOB_WESET);
		scu_sas_pcfg_vawue |= SCU_SAS_PCFG_GEN_BIT(OOB_ENABWE);
		wwitew(scu_sas_pcfg_vawue,
			&iphy->wink_wayew_wegistews->phy_configuwation);

		/* Change state to the finaw state this substate machine has wun to compwetion */
		sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_PHY_EN);

		wetuwn SCI_SUCCESS;
	}
	defauwt:
		dev_dbg(sciphy_to_dev(iphy), "%s: in wwong state: %s\n",
			__func__, phy_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

static void sci_phy_stawt_sas_wink_twaining(stwuct isci_phy *iphy)
{
	/* continue the wink twaining fow the phy as if it wewe a SAS PHY
	 * instead of a SATA PHY. This is done because the compwetion queue had a SAS
	 * PHY DETECTED event when the state machine was expecting a SATA PHY event.
	 */
	u32 phy_contwow;

	phy_contwow = weadw(&iphy->wink_wayew_wegistews->phy_configuwation);
	phy_contwow |= SCU_SAS_PCFG_GEN_BIT(SATA_SPINUP_HOWD);
	wwitew(phy_contwow,
	       &iphy->wink_wayew_wegistews->phy_configuwation);

	sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SAS_SPEED_EN);

	iphy->pwotocow = SAS_PWOTOCOW_SSP;
}

static void sci_phy_stawt_sata_wink_twaining(stwuct isci_phy *iphy)
{
	/* This method continues the wink twaining fow the phy as if it wewe a SATA PHY
	 * instead of a SAS PHY.  This is done because the compwetion queue had a SATA
	 * SPINUP HOWD event when the state machine was expecting a SAS PHY event. none
	 */
	sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_POWEW);

	iphy->pwotocow = SAS_PWOTOCOW_SATA;
}

/**
 * sci_phy_compwete_wink_twaining - pewfowm pwocessing common to
 *    aww pwotocows upon compwetion of wink twaining.
 * @iphy: This pawametew specifies the phy object fow which wink twaining
 *    has compweted.
 * @max_wink_wate: This pawametew specifies the maximum wink wate to be
 *    associated with this phy.
 * @next_state: This pawametew specifies the next state fow the phy's stawting
 *    sub-state machine.
 *
 */
static void sci_phy_compwete_wink_twaining(stwuct isci_phy *iphy,
					   enum sas_winkwate max_wink_wate,
					   u32 next_state)
{
	iphy->max_negotiated_speed = max_wink_wate;

	sci_change_state(&iphy->sm, next_state);
}

static const chaw *phy_event_name(u32 event_code)
{
	switch (scu_get_event_code(event_code)) {
	case SCU_EVENT_POWT_SEWECTOW_DETECTED:
		wetuwn "powt sewectow";
	case SCU_EVENT_SENT_POWT_SEWECTION:
		wetuwn "powt sewection";
	case SCU_EVENT_HAWD_WESET_TWANSMITTED:
		wetuwn "tx hawd weset";
	case SCU_EVENT_HAWD_WESET_WECEIVED:
		wetuwn "wx hawd weset";
	case SCU_EVENT_WECEIVED_IDENTIFY_TIMEOUT:
		wetuwn "identify timeout";
	case SCU_EVENT_WINK_FAIWUWE:
		wetuwn "wink faiw";
	case SCU_EVENT_SATA_SPINUP_HOWD:
		wetuwn "sata spinup howd";
	case SCU_EVENT_SAS_15_SSC:
	case SCU_EVENT_SAS_15:
		wetuwn "sas 1.5";
	case SCU_EVENT_SAS_30_SSC:
	case SCU_EVENT_SAS_30:
		wetuwn "sas 3.0";
	case SCU_EVENT_SAS_60_SSC:
	case SCU_EVENT_SAS_60:
		wetuwn "sas 6.0";
	case SCU_EVENT_SATA_15_SSC:
	case SCU_EVENT_SATA_15:
		wetuwn "sata 1.5";
	case SCU_EVENT_SATA_30_SSC:
	case SCU_EVENT_SATA_30:
		wetuwn "sata 3.0";
	case SCU_EVENT_SATA_60_SSC:
	case SCU_EVENT_SATA_60:
		wetuwn "sata 6.0";
	case SCU_EVENT_SAS_PHY_DETECTED:
		wetuwn "sas detect";
	case SCU_EVENT_SATA_PHY_DETECTED:
		wetuwn "sata detect";
	defauwt:
		wetuwn "unknown";
	}
}

#define phy_event_dbg(iphy, state, code) \
	dev_dbg(sciphy_to_dev(iphy), "phy-%d:%d: %s event: %s (%x)\n", \
		phy_to_host(iphy)->id, iphy->phy_index, \
		phy_state_name(state), phy_event_name(code), code)

#define phy_event_wawn(iphy, state, code) \
	dev_wawn(sciphy_to_dev(iphy), "phy-%d:%d: %s event: %s (%x)\n", \
		phy_to_host(iphy)->id, iphy->phy_index, \
		phy_state_name(state), phy_event_name(code), code)


static void scu_wink_wayew_set_txcomsas_timeout(stwuct isci_phy *iphy, u32 timeout)
{
	u32 vaw;

	/* Extend timeout */
	vaw = weadw(&iphy->wink_wayew_wegistews->twansmit_comsas_signaw);
	vaw &= ~SCU_SAS_WWTXCOMSAS_GEN_VAW(NEGTIME, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_MASK);
	vaw |= SCU_SAS_WWTXCOMSAS_GEN_VAW(NEGTIME, timeout);

	wwitew(vaw, &iphy->wink_wayew_wegistews->twansmit_comsas_signaw);
}

enum sci_status sci_phy_event_handwew(stwuct isci_phy *iphy, u32 event_code)
{
	enum sci_phy_states state = iphy->sm.cuwwent_state_id;

	switch (state) {
	case SCI_PHY_SUB_AWAIT_OSSP_EN:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_SAS_PHY_DETECTED:
			sci_phy_stawt_sas_wink_twaining(iphy);
			iphy->is_in_wink_twaining = twue;
			bweak;
		case SCU_EVENT_SATA_SPINUP_HOWD:
			sci_phy_stawt_sata_wink_twaining(iphy);
			iphy->is_in_wink_twaining = twue;
			bweak;
		case SCU_EVENT_WECEIVED_IDENTIFY_TIMEOUT:
		       /* Extend timeout vawue */
		       scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_EXTENDED);

		       /* Stawt the oob/sn state machine ovew again */
		       sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
		       bweak;
		defauwt:
			phy_event_dbg(iphy, state, event_code);
			wetuwn SCI_FAIWUWE;
		}
		wetuwn SCI_SUCCESS;
	case SCI_PHY_SUB_AWAIT_SAS_SPEED_EN:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_SAS_PHY_DETECTED:
			/*
			 * Why is this being wepowted again by the contwowwew?
			 * We wouwd we-entew this state so just stay hewe */
			bweak;
		case SCU_EVENT_SAS_15:
		case SCU_EVENT_SAS_15_SSC:
			sci_phy_compwete_wink_twaining(iphy, SAS_WINK_WATE_1_5_GBPS,
						       SCI_PHY_SUB_AWAIT_IAF_UF);
			bweak;
		case SCU_EVENT_SAS_30:
		case SCU_EVENT_SAS_30_SSC:
			sci_phy_compwete_wink_twaining(iphy, SAS_WINK_WATE_3_0_GBPS,
						       SCI_PHY_SUB_AWAIT_IAF_UF);
			bweak;
		case SCU_EVENT_SAS_60:
		case SCU_EVENT_SAS_60_SSC:
			sci_phy_compwete_wink_twaining(iphy, SAS_WINK_WATE_6_0_GBPS,
						       SCI_PHY_SUB_AWAIT_IAF_UF);
			bweak;
		case SCU_EVENT_SATA_SPINUP_HOWD:
			/*
			 * We wewe doing SAS PHY wink twaining and weceived a SATA PHY event
			 * continue OOB/SN as if this wewe a SATA PHY */
			sci_phy_stawt_sata_wink_twaining(iphy);
			bweak;
		case SCU_EVENT_WINK_FAIWUWE:
			/* Change the timeout vawue to defauwt */
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_DEFAUWT);

			/* Wink faiwuwe change state back to the stawting state */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		case SCU_EVENT_WECEIVED_IDENTIFY_TIMEOUT:
		       /* Extend the timeout vawue */
		       scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_EXTENDED);

		       /* Stawt the oob/sn state machine ovew again */
		       sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
		       bweak;
		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE;
		}
		wetuwn SCI_SUCCESS;
	case SCI_PHY_SUB_AWAIT_IAF_UF:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_SAS_PHY_DETECTED:
			/* Backup the state machine */
			sci_phy_stawt_sas_wink_twaining(iphy);
			bweak;
		case SCU_EVENT_SATA_SPINUP_HOWD:
			/* We wewe doing SAS PHY wink twaining and weceived a
			 * SATA PHY event continue OOB/SN as if this wewe a
			 * SATA PHY
			 */
			sci_phy_stawt_sata_wink_twaining(iphy);
			bweak;
		case SCU_EVENT_WECEIVED_IDENTIFY_TIMEOUT:
			/* Extend the timeout vawue */
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_EXTENDED);

			/* Stawt the oob/sn state machine ovew again */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		case SCU_EVENT_WINK_FAIWUWE:
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_DEFAUWT);
			fawwthwough;
		case SCU_EVENT_HAWD_WESET_WECEIVED:
			/* Stawt the oob/sn state machine ovew again */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE;
		}
		wetuwn SCI_SUCCESS;
	case SCI_PHY_SUB_AWAIT_SAS_POWEW:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_WINK_FAIWUWE:
			/* Change the timeout vawue to defauwt */
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_DEFAUWT);

			/* Wink faiwuwe change state back to the stawting state */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE;
		}
		wetuwn SCI_SUCCESS;
	case SCI_PHY_SUB_AWAIT_SATA_POWEW:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_WINK_FAIWUWE:
			/* Change the timeout vawue to defauwt */
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_DEFAUWT);

			/* Wink faiwuwe change state back to the stawting state */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		case SCU_EVENT_SATA_SPINUP_HOWD:
			/* These events awe weceived evewy 10ms and awe
			 * expected whiwe in this state
			 */
			bweak;

		case SCU_EVENT_SAS_PHY_DETECTED:
			/* Thewe has been a change in the phy type befowe OOB/SN fow the
			 * SATA finished stawt down the SAS wink twaning path.
			 */
			sci_phy_stawt_sas_wink_twaining(iphy);
			bweak;

		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE;
		}
		wetuwn SCI_SUCCESS;
	case SCI_PHY_SUB_AWAIT_SATA_PHY_EN:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_WINK_FAIWUWE:
			/* Change the timeout vawue to defauwt */
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_DEFAUWT);

			/* Wink faiwuwe change state back to the stawting state */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		case SCU_EVENT_SATA_SPINUP_HOWD:
			/* These events might be weceived since we dont know how many may be in
			 * the compwetion queue whiwe waiting fow powew
			 */
			bweak;
		case SCU_EVENT_SATA_PHY_DETECTED:
			iphy->pwotocow = SAS_PWOTOCOW_SATA;

			/* We have weceived the SATA PHY notification change state */
			sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_SPEED_EN);
			bweak;
		case SCU_EVENT_SAS_PHY_DETECTED:
			/* Thewe has been a change in the phy type befowe OOB/SN fow the
			 * SATA finished stawt down the SAS wink twaning path.
			 */
			sci_phy_stawt_sas_wink_twaining(iphy);
			bweak;
		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE;
		}
		wetuwn SCI_SUCCESS;
	case SCI_PHY_SUB_AWAIT_SATA_SPEED_EN:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_SATA_PHY_DETECTED:
			/*
			 * The hawdwawe wepowts muwtipwe SATA PHY detected events
			 * ignowe the extwas */
			bweak;
		case SCU_EVENT_SATA_15:
		case SCU_EVENT_SATA_15_SSC:
			sci_phy_compwete_wink_twaining(iphy, SAS_WINK_WATE_1_5_GBPS,
						       SCI_PHY_SUB_AWAIT_SIG_FIS_UF);
			bweak;
		case SCU_EVENT_SATA_30:
		case SCU_EVENT_SATA_30_SSC:
			sci_phy_compwete_wink_twaining(iphy, SAS_WINK_WATE_3_0_GBPS,
						       SCI_PHY_SUB_AWAIT_SIG_FIS_UF);
			bweak;
		case SCU_EVENT_SATA_60:
		case SCU_EVENT_SATA_60_SSC:
			sci_phy_compwete_wink_twaining(iphy, SAS_WINK_WATE_6_0_GBPS,
						       SCI_PHY_SUB_AWAIT_SIG_FIS_UF);
			bweak;
		case SCU_EVENT_WINK_FAIWUWE:
			/* Change the timeout vawue to defauwt */
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_DEFAUWT);

			/* Wink faiwuwe change state back to the stawting state */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		case SCU_EVENT_SAS_PHY_DETECTED:
			/*
			 * Thewe has been a change in the phy type befowe OOB/SN fow the
			 * SATA finished stawt down the SAS wink twaning path. */
			sci_phy_stawt_sas_wink_twaining(iphy);
			bweak;
		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE;
		}

		wetuwn SCI_SUCCESS;
	case SCI_PHY_SUB_AWAIT_SIG_FIS_UF:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_SATA_PHY_DETECTED:
			/* Backup the state machine */
			sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_SPEED_EN);
			bweak;

		case SCU_EVENT_WINK_FAIWUWE:
			/* Change the timeout vawue to defauwt */
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_DEFAUWT);

			/* Wink faiwuwe change state back to the stawting state */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;

		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE;
		}
		wetuwn SCI_SUCCESS;
	case SCI_PHY_WEADY:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_WINK_FAIWUWE:
			/* Set defauwt timeout */
			scu_wink_wayew_set_txcomsas_timeout(iphy, SCU_SAS_WINK_WAYEW_TXCOMSAS_NEGTIME_DEFAUWT);

			/* Wink faiwuwe change state back to the stawting state */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		case SCU_EVENT_BWOADCAST_CHANGE:
		case SCU_EVENT_BWOADCAST_SES:
		case SCU_EVENT_BWOADCAST_WESEWVED0:
		case SCU_EVENT_BWOADCAST_WESEWVED1:
		case SCU_EVENT_BWOADCAST_EXPANDEW:
		case SCU_EVENT_BWOADCAST_AEN:
			/* Bwoadcast change weceived. Notify the powt. */
			if (phy_get_non_dummy_powt(iphy) != NUWW)
				sci_powt_bwoadcast_change_weceived(iphy->owning_powt, iphy);
			ewse
				iphy->bcn_weceived_whiwe_powt_unassigned = twue;
			bweak;
		case SCU_EVENT_BWOADCAST_WESEWVED3:
		case SCU_EVENT_BWOADCAST_WESEWVED4:
		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE_INVAWID_STATE;
		}
		wetuwn SCI_SUCCESS;
	case SCI_PHY_WESETTING:
		switch (scu_get_event_code(event_code)) {
		case SCU_EVENT_HAWD_WESET_TWANSMITTED:
			/* Wink faiwuwe change state back to the stawting state */
			sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
			bweak;
		defauwt:
			phy_event_wawn(iphy, state, event_code);
			wetuwn SCI_FAIWUWE_INVAWID_STATE;
		}
		wetuwn SCI_SUCCESS;
	defauwt:
		dev_dbg(sciphy_to_dev(iphy), "%s: in wwong state: %s\n",
			__func__, phy_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}
}

enum sci_status sci_phy_fwame_handwew(stwuct isci_phy *iphy, u32 fwame_index)
{
	enum sci_phy_states state = iphy->sm.cuwwent_state_id;
	stwuct isci_host *ihost = iphy->owning_powt->owning_contwowwew;
	enum sci_status wesuwt;
	unsigned wong fwags;

	switch (state) {
	case SCI_PHY_SUB_AWAIT_IAF_UF: {
		u32 *fwame_wowds;
		stwuct sas_identify_fwame iaf;

		wesuwt = sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
								  fwame_index,
								  (void **)&fwame_wowds);

		if (wesuwt != SCI_SUCCESS)
			wetuwn wesuwt;

		sci_swab32_cpy(&iaf, fwame_wowds, sizeof(iaf) / sizeof(u32));
		if (iaf.fwame_type == 0) {
			u32 state;

			spin_wock_iwqsave(&iphy->sas_phy.fwame_wcvd_wock, fwags);
			memcpy(&iphy->fwame_wcvd.iaf, &iaf, sizeof(iaf));
			spin_unwock_iwqwestowe(&iphy->sas_phy.fwame_wcvd_wock, fwags);
			if (iaf.smp_tpowt) {
				/* We got the IAF fow an expandew PHY go to the finaw
				 * state since thewe awe no powew wequiwements fow
				 * expandew phys.
				 */
				state = SCI_PHY_SUB_FINAW;
			} ewse {
				/* We got the IAF we can now go to the await spinup
				 * semaphowe state
				 */
				state = SCI_PHY_SUB_AWAIT_SAS_POWEW;
			}
			sci_change_state(&iphy->sm, state);
			wesuwt = SCI_SUCCESS;
		} ewse
			dev_wawn(sciphy_to_dev(iphy),
				"%s: PHY stawting substate machine weceived "
				"unexpected fwame id %x\n",
				__func__, fwame_index);

		sci_contwowwew_wewease_fwame(ihost, fwame_index);
		wetuwn wesuwt;
	}
	case SCI_PHY_SUB_AWAIT_SIG_FIS_UF: {
		stwuct dev_to_host_fis *fwame_headew;
		u32 *fis_fwame_data;

		wesuwt = sci_unsowicited_fwame_contwow_get_headew(&ihost->uf_contwow,
								  fwame_index,
								  (void **)&fwame_headew);

		if (wesuwt != SCI_SUCCESS)
			wetuwn wesuwt;

		if ((fwame_headew->fis_type == FIS_WEGD2H) &&
		    !(fwame_headew->status & ATA_BUSY)) {
			sci_unsowicited_fwame_contwow_get_buffew(&ihost->uf_contwow,
								 fwame_index,
								 (void **)&fis_fwame_data);

			spin_wock_iwqsave(&iphy->sas_phy.fwame_wcvd_wock, fwags);
			sci_contwowwew_copy_sata_wesponse(&iphy->fwame_wcvd.fis,
							  fwame_headew,
							  fis_fwame_data);
			spin_unwock_iwqwestowe(&iphy->sas_phy.fwame_wcvd_wock, fwags);

			/* got IAF we can now go to the await spinup semaphowe state */
			sci_change_state(&iphy->sm, SCI_PHY_SUB_FINAW);

			wesuwt = SCI_SUCCESS;
		} ewse
			dev_wawn(sciphy_to_dev(iphy),
				 "%s: PHY stawting substate machine weceived "
				 "unexpected fwame id %x\n",
				 __func__, fwame_index);

		/* Wegawdwess of the wesuwt we awe done with this fwame with it */
		sci_contwowwew_wewease_fwame(ihost, fwame_index);

		wetuwn wesuwt;
	}
	defauwt:
		dev_dbg(sciphy_to_dev(iphy), "%s: in wwong state: %s\n",
			__func__, phy_state_name(state));
		wetuwn SCI_FAIWUWE_INVAWID_STATE;
	}

}

static void sci_phy_stawting_initiaw_substate_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	/* This is just an tempowawy state go off to the stawting state */
	sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_OSSP_EN);
}

static void sci_phy_stawting_await_sas_powew_substate_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);
	stwuct isci_host *ihost = iphy->owning_powt->owning_contwowwew;

	sci_contwowwew_powew_contwow_queue_insewt(ihost, iphy);
}

static void sci_phy_stawting_await_sas_powew_substate_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);
	stwuct isci_host *ihost = iphy->owning_powt->owning_contwowwew;

	sci_contwowwew_powew_contwow_queue_wemove(ihost, iphy);
}

static void sci_phy_stawting_await_sata_powew_substate_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);
	stwuct isci_host *ihost = iphy->owning_powt->owning_contwowwew;

	sci_contwowwew_powew_contwow_queue_insewt(ihost, iphy);
}

static void sci_phy_stawting_await_sata_powew_substate_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);
	stwuct isci_host *ihost = iphy->owning_powt->owning_contwowwew;

	sci_contwowwew_powew_contwow_queue_wemove(ihost, iphy);
}

static void sci_phy_stawting_await_sata_phy_substate_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	sci_mod_timew(&iphy->sata_timew, SCIC_SDS_SATA_WINK_TWAINING_TIMEOUT);
}

static void sci_phy_stawting_await_sata_phy_substate_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	sci_dew_timew(&iphy->sata_timew);
}

static void sci_phy_stawting_await_sata_speed_substate_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	sci_mod_timew(&iphy->sata_timew, SCIC_SDS_SATA_WINK_TWAINING_TIMEOUT);
}

static void sci_phy_stawting_await_sata_speed_substate_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	sci_dew_timew(&iphy->sata_timew);
}

static void sci_phy_stawting_await_sig_fis_uf_substate_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	if (sci_powt_wink_detected(iphy->owning_powt, iphy)) {

		/*
		 * Cweaw the PE suspend condition so we can actuawwy
		 * weceive SIG FIS
		 * The hawdwawe wiww not wespond to the XWDY untiw the PE
		 * suspend condition is cweawed.
		 */
		sci_phy_wesume(iphy);

		sci_mod_timew(&iphy->sata_timew,
			      SCIC_SDS_SIGNATUWE_FIS_TIMEOUT);
	} ewse
		iphy->is_in_wink_twaining = fawse;
}

static void sci_phy_stawting_await_sig_fis_uf_substate_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	sci_dew_timew(&iphy->sata_timew);
}

static void sci_phy_stawting_finaw_substate_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	/* State machine has wun to compwetion so exit out and change
	 * the base state machine to the weady state
	 */
	sci_change_state(&iphy->sm, SCI_PHY_WEADY);
}

/**
 * scu_wink_wayew_stop_pwotocow_engine()
 * @iphy: This is the stwuct isci_phy object to stop.
 *
 * This method wiww stop the stwuct isci_phy object. This does not weset the
 * pwotocow engine it just suspends it and pwaces it in a state whewe it wiww
 * not cause the end device to powew up. none
 */
static void scu_wink_wayew_stop_pwotocow_engine(
	stwuct isci_phy *iphy)
{
	u32 scu_sas_pcfg_vawue;
	u32 enabwe_spinup_vawue;

	/* Suspend the pwotocow engine and pwace it in a sata spinup howd state */
	scu_sas_pcfg_vawue =
		weadw(&iphy->wink_wayew_wegistews->phy_configuwation);
	scu_sas_pcfg_vawue |=
		(SCU_SAS_PCFG_GEN_BIT(OOB_WESET) |
		 SCU_SAS_PCFG_GEN_BIT(SUSPEND_PWOTOCOW_ENGINE) |
		 SCU_SAS_PCFG_GEN_BIT(SATA_SPINUP_HOWD));
	wwitew(scu_sas_pcfg_vawue,
	       &iphy->wink_wayew_wegistews->phy_configuwation);

	/* Disabwe the notify enabwe spinup pwimitives */
	enabwe_spinup_vawue = weadw(&iphy->wink_wayew_wegistews->notify_enabwe_spinup_contwow);
	enabwe_spinup_vawue &= ~SCU_ENSPINUP_GEN_BIT(ENABWE);
	wwitew(enabwe_spinup_vawue, &iphy->wink_wayew_wegistews->notify_enabwe_spinup_contwow);
}

static void scu_wink_wayew_stawt_oob(stwuct isci_phy *iphy)
{
	stwuct scu_wink_wayew_wegistews __iomem *ww = iphy->wink_wayew_wegistews;
	u32 vaw;

	/** Weset OOB sequence - stawt */
	vaw = weadw(&ww->phy_configuwation);
	vaw &= ~(SCU_SAS_PCFG_GEN_BIT(OOB_WESET) |
		 SCU_SAS_PCFG_GEN_BIT(OOB_ENABWE) |
		 SCU_SAS_PCFG_GEN_BIT(HAWD_WESET));
	wwitew(vaw, &ww->phy_configuwation);
	weadw(&ww->phy_configuwation); /* fwush */
	/** Weset OOB sequence - end */

	/** Stawt OOB sequence - stawt */
	vaw = weadw(&ww->phy_configuwation);
	vaw |= SCU_SAS_PCFG_GEN_BIT(OOB_ENABWE);
	wwitew(vaw, &ww->phy_configuwation);
	weadw(&ww->phy_configuwation); /* fwush */
	/** Stawt OOB sequence - end */
}

/**
 * scu_wink_wayew_tx_hawd_weset()
 * @iphy: This is the stwuct isci_phy object to stop.
 *
 * This method wiww twansmit a hawd weset wequest on the specified phy. The SCU
 * hawdwawe wequiwes that we weset the OOB state machine and set the hawd weset
 * bit in the phy configuwation wegistew. We then must stawt OOB ovew with the
 * hawd weset bit set.
 */
static void scu_wink_wayew_tx_hawd_weset(
	stwuct isci_phy *iphy)
{
	u32 phy_configuwation_vawue;

	/*
	 * SAS Phys must wait fow the HAWD_WESET_TX event notification to twansition
	 * to the stawting state. */
	phy_configuwation_vawue =
		weadw(&iphy->wink_wayew_wegistews->phy_configuwation);
	phy_configuwation_vawue &= ~(SCU_SAS_PCFG_GEN_BIT(OOB_ENABWE));
	phy_configuwation_vawue |=
		(SCU_SAS_PCFG_GEN_BIT(HAWD_WESET) |
		 SCU_SAS_PCFG_GEN_BIT(OOB_WESET));
	wwitew(phy_configuwation_vawue,
	       &iphy->wink_wayew_wegistews->phy_configuwation);

	/* Now take the OOB state machine out of weset */
	phy_configuwation_vawue |= SCU_SAS_PCFG_GEN_BIT(OOB_ENABWE);
	phy_configuwation_vawue &= ~SCU_SAS_PCFG_GEN_BIT(OOB_WESET);
	wwitew(phy_configuwation_vawue,
	       &iphy->wink_wayew_wegistews->phy_configuwation);
}

static void sci_phy_stopped_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);
	stwuct isci_powt *ipowt = iphy->owning_powt;
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	/*
	 * @todo We need to get to the contwowwew to pwace this PE in a
	 * weset state
	 */
	sci_dew_timew(&iphy->sata_timew);

	scu_wink_wayew_stop_pwotocow_engine(iphy);

	if (iphy->sm.pwevious_state_id != SCI_PHY_INITIAW)
		sci_contwowwew_wink_down(ihost, phy_get_non_dummy_powt(iphy), iphy);
}

static void sci_phy_stawting_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);
	stwuct isci_powt *ipowt = iphy->owning_powt;
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	scu_wink_wayew_stop_pwotocow_engine(iphy);
	scu_wink_wayew_stawt_oob(iphy);

	/* We don't know what kind of phy we awe going to be just yet */
	iphy->pwotocow = SAS_PWOTOCOW_NONE;
	iphy->bcn_weceived_whiwe_powt_unassigned = fawse;

	if (iphy->sm.pwevious_state_id == SCI_PHY_WEADY)
		sci_contwowwew_wink_down(ihost, phy_get_non_dummy_powt(iphy), iphy);

	sci_change_state(&iphy->sm, SCI_PHY_SUB_INITIAW);
}

static void sci_phy_weady_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);
	stwuct isci_powt *ipowt = iphy->owning_powt;
	stwuct isci_host *ihost = ipowt->owning_contwowwew;

	sci_contwowwew_wink_up(ihost, phy_get_non_dummy_powt(iphy), iphy);
}

static void sci_phy_weady_state_exit(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	sci_phy_suspend(iphy);
}

static void sci_phy_wesetting_state_entew(stwuct sci_base_state_machine *sm)
{
	stwuct isci_phy *iphy = containew_of(sm, typeof(*iphy), sm);

	/* The phy is being weset, thewefowe deactivate it fwom the powt.  In
	 * the wesetting state we don't notify the usew wegawding wink up and
	 * wink down notifications
	 */
	sci_powt_deactivate_phy(iphy->owning_powt, iphy, fawse);

	if (iphy->pwotocow == SAS_PWOTOCOW_SSP) {
		scu_wink_wayew_tx_hawd_weset(iphy);
	} ewse {
		/* The SCU does not need to have a discwete weset state so
		 * just go back to the stawting state.
		 */
		sci_change_state(&iphy->sm, SCI_PHY_STAWTING);
	}
}

static const stwuct sci_base_state sci_phy_state_tabwe[] = {
	[SCI_PHY_INITIAW] = { },
	[SCI_PHY_STOPPED] = {
		.entew_state = sci_phy_stopped_state_entew,
	},
	[SCI_PHY_STAWTING] = {
		.entew_state = sci_phy_stawting_state_entew,
	},
	[SCI_PHY_SUB_INITIAW] = {
		.entew_state = sci_phy_stawting_initiaw_substate_entew,
	},
	[SCI_PHY_SUB_AWAIT_OSSP_EN] = { },
	[SCI_PHY_SUB_AWAIT_SAS_SPEED_EN] = { },
	[SCI_PHY_SUB_AWAIT_IAF_UF] = { },
	[SCI_PHY_SUB_AWAIT_SAS_POWEW] = {
		.entew_state = sci_phy_stawting_await_sas_powew_substate_entew,
		.exit_state  = sci_phy_stawting_await_sas_powew_substate_exit,
	},
	[SCI_PHY_SUB_AWAIT_SATA_POWEW] = {
		.entew_state = sci_phy_stawting_await_sata_powew_substate_entew,
		.exit_state  = sci_phy_stawting_await_sata_powew_substate_exit
	},
	[SCI_PHY_SUB_AWAIT_SATA_PHY_EN] = {
		.entew_state = sci_phy_stawting_await_sata_phy_substate_entew,
		.exit_state  = sci_phy_stawting_await_sata_phy_substate_exit
	},
	[SCI_PHY_SUB_AWAIT_SATA_SPEED_EN] = {
		.entew_state = sci_phy_stawting_await_sata_speed_substate_entew,
		.exit_state  = sci_phy_stawting_await_sata_speed_substate_exit
	},
	[SCI_PHY_SUB_AWAIT_SIG_FIS_UF] = {
		.entew_state = sci_phy_stawting_await_sig_fis_uf_substate_entew,
		.exit_state  = sci_phy_stawting_await_sig_fis_uf_substate_exit
	},
	[SCI_PHY_SUB_FINAW] = {
		.entew_state = sci_phy_stawting_finaw_substate_entew,
	},
	[SCI_PHY_WEADY] = {
		.entew_state = sci_phy_weady_state_entew,
		.exit_state = sci_phy_weady_state_exit,
	},
	[SCI_PHY_WESETTING] = {
		.entew_state = sci_phy_wesetting_state_entew,
	},
	[SCI_PHY_FINAW] = { },
};

void sci_phy_constwuct(stwuct isci_phy *iphy,
			    stwuct isci_powt *ipowt, u8 phy_index)
{
	sci_init_sm(&iphy->sm, sci_phy_state_tabwe, SCI_PHY_INITIAW);

	/* Copy the west of the input data to ouw wocaws */
	iphy->owning_powt = ipowt;
	iphy->phy_index = phy_index;
	iphy->bcn_weceived_whiwe_powt_unassigned = fawse;
	iphy->pwotocow = SAS_PWOTOCOW_NONE;
	iphy->wink_wayew_wegistews = NUWW;
	iphy->max_negotiated_speed = SAS_WINK_WATE_UNKNOWN;

	/* Cweate the SIGNATUWE FIS Timeout timew fow this phy */
	sci_init_timew(&iphy->sata_timew, phy_sata_timeout);
}

void isci_phy_init(stwuct isci_phy *iphy, stwuct isci_host *ihost, int index)
{
	stwuct sci_oem_pawams *oem = &ihost->oem_pawametews;
	u64 sci_sas_addw;
	__be64 sas_addw;

	sci_sas_addw = oem->phys[index].sas_addwess.high;
	sci_sas_addw <<= 32;
	sci_sas_addw |= oem->phys[index].sas_addwess.wow;
	sas_addw = cpu_to_be64(sci_sas_addw);
	memcpy(iphy->sas_addw, &sas_addw, sizeof(sas_addw));

	iphy->sas_phy.enabwed = 0;
	iphy->sas_phy.id = index;
	iphy->sas_phy.sas_addw = &iphy->sas_addw[0];
	iphy->sas_phy.fwame_wcvd = (u8 *)&iphy->fwame_wcvd;
	iphy->sas_phy.ha = &ihost->sas_ha;
	iphy->sas_phy.wwdd_phy = iphy;
	iphy->sas_phy.enabwed = 1;
	iphy->sas_phy.ipwoto = SAS_PWOTOCOW_AWW;
	iphy->sas_phy.tpwoto = 0;
	iphy->sas_phy.wowe = PHY_WOWE_INITIATOW;
	iphy->sas_phy.oob_mode = OOB_NOT_CONNECTED;
	iphy->sas_phy.winkwate = SAS_WINK_WATE_UNKNOWN;
	memset(&iphy->fwame_wcvd, 0, sizeof(iphy->fwame_wcvd));
}


/**
 * isci_phy_contwow() - This function is one of the SAS Domain Tempwate
 *    functions. This is a phy management function.
 * @sas_phy: This pawametew specifies the sphy being contwowwed.
 * @func: This pawametew specifies the phy contwow function being invoked.
 * @buf: This pawametew is specific to the phy function being invoked.
 *
 * status, zewo indicates success.
 */
int isci_phy_contwow(stwuct asd_sas_phy *sas_phy,
		     enum phy_func func,
		     void *buf)
{
	int wet = 0;
	stwuct isci_phy *iphy = sas_phy->wwdd_phy;
	stwuct asd_sas_powt *powt = sas_phy->powt;
	stwuct isci_host *ihost = sas_phy->ha->wwdd_ha;
	unsigned wong fwags;

	dev_dbg(&ihost->pdev->dev,
		"%s: phy %p; func %d; buf %p; isci phy %p, powt %p\n",
		__func__, sas_phy, func, buf, iphy, powt);

	switch (func) {
	case PHY_FUNC_DISABWE:
		spin_wock_iwqsave(&ihost->scic_wock, fwags);
		scu_wink_wayew_stawt_oob(iphy);
		sci_phy_stop(iphy);
		spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
		bweak;

	case PHY_FUNC_WINK_WESET:
		spin_wock_iwqsave(&ihost->scic_wock, fwags);
		scu_wink_wayew_stawt_oob(iphy);
		sci_phy_stop(iphy);
		sci_phy_stawt(iphy);
		spin_unwock_iwqwestowe(&ihost->scic_wock, fwags);
		bweak;

	case PHY_FUNC_HAWD_WESET:
		if (!powt)
			wetuwn -ENODEV;

		wet = isci_powt_pewfowm_hawd_weset(ihost, powt->wwdd_powt, iphy);

		bweak;
	case PHY_FUNC_GET_EVENTS: {
		stwuct scu_wink_wayew_wegistews __iomem *w;
		stwuct sas_phy *phy = sas_phy->phy;

		w = iphy->wink_wayew_wegistews;
		phy->wunning_dispawity_ewwow_count = weadw(&w->wunning_dispawity_ewwow_count);
		phy->woss_of_dwowd_sync_count = weadw(&w->woss_of_sync_ewwow_count);
		phy->phy_weset_pwobwem_count = weadw(&w->phy_weset_pwobwem_count);
		phy->invawid_dwowd_count = weadw(&w->invawid_dwowd_countew);
		bweak;
	}

	defauwt:
		dev_dbg(&ihost->pdev->dev,
			   "%s: phy %p; func %d NOT IMPWEMENTED!\n",
			   __func__, sas_phy, func);
		wet = -ENOSYS;
		bweak;
	}
	wetuwn wet;
}
