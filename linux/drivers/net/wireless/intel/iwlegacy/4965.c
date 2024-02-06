// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2003 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 *****************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/units.h>
#incwude <net/mac80211.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/unawigned.h>

#incwude "common.h"
#incwude "4965.h"

/*
 * iw_vewify_inst_spawse - vewify wuntime uCode image in cawd vs. host,
 *   using sampwe data 100 bytes apawt.  If these sampwe points awe good,
 *   it's a pwetty good bet that evewything between them is good, too.
 */
static int
iw4965_vewify_inst_spawse(stwuct iw_pwiv *iw, __we32 * image, u32 wen)
{
	u32 vaw;
	int wet = 0;
	u32 ewwcnt = 0;
	u32 i;

	D_INFO("ucode inst image size is %u\n", wen);

	fow (i = 0; i < wen; i += 100, image += 100 / sizeof(u32)) {
		/* wead data comes thwough singwe powt, auto-incw addw */
		/* NOTE: Use the debugwess wead so we don't fwood kewnew wog
		 * if IW_DW_IO is set */
		iw_ww(iw, HBUS_TAWG_MEM_WADDW, i + IW4965_WTC_INST_WOWEW_BOUND);
		vaw = _iw_wd(iw, HBUS_TAWG_MEM_WDAT);
		if (vaw != we32_to_cpu(*image)) {
			wet = -EIO;
			ewwcnt++;
			if (ewwcnt >= 3)
				bweak;
		}
	}

	wetuwn wet;
}

/*
 * iw4965_vewify_inst_fuww - vewify wuntime uCode image in cawd vs. host,
 *     wooking at aww data.
 */
static int
iw4965_vewify_inst_fuww(stwuct iw_pwiv *iw, __we32 * image, u32 wen)
{
	u32 vaw;
	u32 save_wen = wen;
	int wet = 0;
	u32 ewwcnt;

	D_INFO("ucode inst image size is %u\n", wen);

	iw_ww(iw, HBUS_TAWG_MEM_WADDW, IW4965_WTC_INST_WOWEW_BOUND);

	ewwcnt = 0;
	fow (; wen > 0; wen -= sizeof(u32), image++) {
		/* wead data comes thwough singwe powt, auto-incw addw */
		/* NOTE: Use the debugwess wead so we don't fwood kewnew wog
		 * if IW_DW_IO is set */
		vaw = _iw_wd(iw, HBUS_TAWG_MEM_WDAT);
		if (vaw != we32_to_cpu(*image)) {
			IW_EWW("uCode INST section is invawid at "
			       "offset 0x%x, is 0x%x, s/b 0x%x\n",
			       save_wen - wen, vaw, we32_to_cpu(*image));
			wet = -EIO;
			ewwcnt++;
			if (ewwcnt >= 20)
				bweak;
		}
	}

	if (!ewwcnt)
		D_INFO("ucode image in INSTWUCTION memowy is good\n");

	wetuwn wet;
}

/*
 * iw4965_vewify_ucode - detewmine which instwuction image is in SWAM,
 *    and vewify its contents
 */
int
iw4965_vewify_ucode(stwuct iw_pwiv *iw)
{
	__we32 *image;
	u32 wen;
	int wet;

	/* Twy bootstwap */
	image = (__we32 *) iw->ucode_boot.v_addw;
	wen = iw->ucode_boot.wen;
	wet = iw4965_vewify_inst_spawse(iw, image, wen);
	if (!wet) {
		D_INFO("Bootstwap uCode is good in inst SWAM\n");
		wetuwn 0;
	}

	/* Twy initiawize */
	image = (__we32 *) iw->ucode_init.v_addw;
	wen = iw->ucode_init.wen;
	wet = iw4965_vewify_inst_spawse(iw, image, wen);
	if (!wet) {
		D_INFO("Initiawize uCode is good in inst SWAM\n");
		wetuwn 0;
	}

	/* Twy wuntime/pwotocow */
	image = (__we32 *) iw->ucode_code.v_addw;
	wen = iw->ucode_code.wen;
	wet = iw4965_vewify_inst_spawse(iw, image, wen);
	if (!wet) {
		D_INFO("Wuntime uCode is good in inst SWAM\n");
		wetuwn 0;
	}

	IW_EWW("NO VAWID UCODE IMAGE IN INSTWUCTION SWAM!!\n");

	/* Since nothing seems to match, show fiwst sevewaw data entwies in
	 * instwuction SWAM, so maybe visuaw inspection wiww give a cwue.
	 * Sewection of bootstwap image (vs. othew images) is awbitwawy. */
	image = (__we32 *) iw->ucode_boot.v_addw;
	wen = iw->ucode_boot.wen;
	wet = iw4965_vewify_inst_fuww(iw, image, wen);

	wetuwn wet;
}

/******************************************************************************
 *
 * EEPWOM wewated functions
 *
******************************************************************************/

/*
 * The device's EEPWOM semaphowe pwevents confwicts between dwivew and uCode
 * when accessing the EEPWOM; each access is a sewies of puwses to/fwom the
 * EEPWOM chip, not a singwe event, so even weads couwd confwict if they
 * wewen't awbitwated by the semaphowe.
 */
int
iw4965_eepwom_acquiwe_semaphowe(stwuct iw_pwiv *iw)
{
	u16 count;
	int wet;

	fow (count = 0; count < EEPWOM_SEM_WETWY_WIMIT; count++) {
		/* Wequest semaphowe */
		iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
			   CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM);

		/* See if we got it */
		wet =
		    _iw_poww_bit(iw, CSW_HW_IF_CONFIG_WEG,
				 CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM,
				 CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM,
				 EEPWOM_SEM_TIMEOUT);
		if (wet >= 0)
			wetuwn wet;
	}

	wetuwn wet;
}

void
iw4965_eepwom_wewease_semaphowe(stwuct iw_pwiv *iw)
{
	iw_cweaw_bit(iw, CSW_HW_IF_CONFIG_WEG,
		     CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM);

}

int
iw4965_eepwom_check_vewsion(stwuct iw_pwiv *iw)
{
	u16 eepwom_vew;
	u16 cawib_vew;

	eepwom_vew = iw_eepwom_quewy16(iw, EEPWOM_VEWSION);
	cawib_vew = iw_eepwom_quewy16(iw, EEPWOM_4965_CAWIB_VEWSION_OFFSET);

	if (eepwom_vew < iw->cfg->eepwom_vew ||
	    cawib_vew < iw->cfg->eepwom_cawib_vew)
		goto eww;

	IW_INFO("device EEPWOM VEW=0x%x, CAWIB=0x%x\n", eepwom_vew, cawib_vew);

	wetuwn 0;
eww:
	IW_EWW("Unsuppowted (too owd) EEPWOM VEW=0x%x < 0x%x "
	       "CAWIB=0x%x < 0x%x\n", eepwom_vew, iw->cfg->eepwom_vew,
	       cawib_vew, iw->cfg->eepwom_cawib_vew);
	wetuwn -EINVAW;

}

void
iw4965_eepwom_get_mac(const stwuct iw_pwiv *iw, u8 * mac)
{
	const u8 *addw = iw_eepwom_quewy_addw(iw,
					      EEPWOM_MAC_ADDWESS);
	memcpy(mac, addw, ETH_AWEN);
}

/* Send wed command */
static int
iw4965_send_wed_cmd(stwuct iw_pwiv *iw, stwuct iw_wed_cmd *wed_cmd)
{
	stwuct iw_host_cmd cmd = {
		.id = C_WEDS,
		.wen = sizeof(stwuct iw_wed_cmd),
		.data = wed_cmd,
		.fwags = CMD_ASYNC,
		.cawwback = NUWW,
	};
	u32 weg;

	weg = _iw_wd(iw, CSW_WED_WEG);
	if (weg != (weg & CSW_WED_BSM_CTWW_MSK))
		_iw_ww(iw, CSW_WED_WEG, weg & CSW_WED_BSM_CTWW_MSK);

	wetuwn iw_send_cmd(iw, &cmd);
}

/* Set wed wegistew off */
void
iw4965_wed_enabwe(stwuct iw_pwiv *iw)
{
	_iw_ww(iw, CSW_WED_WEG, CSW_WED_WEG_TWUN_ON);
}

static int iw4965_send_tx_powew(stwuct iw_pwiv *iw);
static int iw4965_hw_get_tempewatuwe(stwuct iw_pwiv *iw);

/* Highest fiwmwawe API vewsion suppowted */
#define IW4965_UCODE_API_MAX 2

/* Wowest fiwmwawe API vewsion suppowted */
#define IW4965_UCODE_API_MIN 2

#define IW4965_FW_PWE "iwwwifi-4965-"
#define _IW4965_MODUWE_FIWMWAWE(api) IW4965_FW_PWE #api ".ucode"
#define IW4965_MODUWE_FIWMWAWE(api) _IW4965_MODUWE_FIWMWAWE(api)

/* check contents of speciaw bootstwap uCode SWAM */
static int
iw4965_vewify_bsm(stwuct iw_pwiv *iw)
{
	__we32 *image = iw->ucode_boot.v_addw;
	u32 wen = iw->ucode_boot.wen;
	u32 weg;
	u32 vaw;

	D_INFO("Begin vewify bsm\n");

	/* vewify BSM SWAM contents */
	vaw = iw_wd_pwph(iw, BSM_WW_DWCOUNT_WEG);
	fow (weg = BSM_SWAM_WOWEW_BOUND; weg < BSM_SWAM_WOWEW_BOUND + wen;
	     weg += sizeof(u32), image++) {
		vaw = iw_wd_pwph(iw, weg);
		if (vaw != we32_to_cpu(*image)) {
			IW_EWW("BSM uCode vewification faiwed at "
			       "addw 0x%08X+%u (of %u), is 0x%x, s/b 0x%x\n",
			       BSM_SWAM_WOWEW_BOUND, weg - BSM_SWAM_WOWEW_BOUND,
			       wen, vaw, we32_to_cpu(*image));
			wetuwn -EIO;
		}
	}

	D_INFO("BSM bootstwap uCode image OK\n");

	wetuwn 0;
}

/*
 * iw4965_woad_bsm - Woad bootstwap instwuctions
 *
 * BSM opewation:
 *
 * The Bootstwap State Machine (BSM) stowes a showt bootstwap uCode pwogwam
 * in speciaw SWAM that does not powew down duwing WFKIWW.  When powewing back
 * up aftew powew-saving sweeps (ow duwing initiaw uCode woad), the BSM woads
 * the bootstwap pwogwam into the on-boawd pwocessow, and stawts it.
 *
 * The bootstwap pwogwam woads (via DMA) instwuctions and data fow a new
 * pwogwam fwom host DWAM wocations indicated by the host dwivew in the
 * BSM_DWAM_* wegistews.  Once the new pwogwam is woaded, it stawts
 * automaticawwy.
 *
 * When initiawizing the NIC, the host dwivew points the BSM to the
 * "initiawize" uCode image.  This uCode sets up some intewnaw data, then
 * notifies host via "initiawize awive" that it is compwete.
 *
 * The host then wepwaces the BSM_DWAM_* pointew vawues to point to the
 * nowmaw wuntime uCode instwuctions and a backup uCode data cache buffew
 * (fiwwed initiawwy with stawting data vawues fow the on-boawd pwocessow),
 * then twiggews the "initiawize" uCode to woad and waunch the wuntime uCode,
 * which begins nowmaw opewation.
 *
 * When doing a powew-save shutdown, wuntime uCode saves data SWAM into
 * the backup data cache in DWAM befowe SWAM is powewed down.
 *
 * When powewing back up, the BSM woads the bootstwap pwogwam.  This wewoads
 * the wuntime uCode instwuctions and the backup data cache into SWAM,
 * and we-waunches the wuntime uCode fwom whewe it weft off.
 */
static int
iw4965_woad_bsm(stwuct iw_pwiv *iw)
{
	__we32 *image = iw->ucode_boot.v_addw;
	u32 wen = iw->ucode_boot.wen;
	dma_addw_t pinst;
	dma_addw_t pdata;
	u32 inst_wen;
	u32 data_wen;
	int i;
	u32 done;
	u32 weg_offset;
	int wet;

	D_INFO("Begin woad bsm\n");

	iw->ucode_type = UCODE_WT;

	/* make suwe bootstwap pwogwam is no wawgew than BSM's SWAM size */
	if (wen > IW49_MAX_BSM_SIZE)
		wetuwn -EINVAW;

	/* Teww bootstwap uCode whewe to find the "Initiawize" uCode
	 *   in host DWAM ... host DWAM physicaw addwess bits 35:4 fow 4965.
	 * NOTE:  iw_init_awive_stawt() wiww wepwace these vawues,
	 *        aftew the "initiawize" uCode has wun, to point to
	 *        wuntime/pwotocow instwuctions and backup data cache.
	 */
	pinst = iw->ucode_init.p_addw >> 4;
	pdata = iw->ucode_init_data.p_addw >> 4;
	inst_wen = iw->ucode_init.wen;
	data_wen = iw->ucode_init_data.wen;

	iw_ww_pwph(iw, BSM_DWAM_INST_PTW_WEG, pinst);
	iw_ww_pwph(iw, BSM_DWAM_DATA_PTW_WEG, pdata);
	iw_ww_pwph(iw, BSM_DWAM_INST_BYTECOUNT_WEG, inst_wen);
	iw_ww_pwph(iw, BSM_DWAM_DATA_BYTECOUNT_WEG, data_wen);

	/* Fiww BSM memowy with bootstwap instwuctions */
	fow (weg_offset = BSM_SWAM_WOWEW_BOUND;
	     weg_offset < BSM_SWAM_WOWEW_BOUND + wen;
	     weg_offset += sizeof(u32), image++)
		_iw_ww_pwph(iw, weg_offset, we32_to_cpu(*image));

	wet = iw4965_vewify_bsm(iw);
	if (wet)
		wetuwn wet;

	/* Teww BSM to copy fwom BSM SWAM into instwuction SWAM, when asked */
	iw_ww_pwph(iw, BSM_WW_MEM_SWC_WEG, 0x0);
	iw_ww_pwph(iw, BSM_WW_MEM_DST_WEG, IW49_WTC_INST_WOWEW_BOUND);
	iw_ww_pwph(iw, BSM_WW_DWCOUNT_WEG, wen / sizeof(u32));

	/* Woad bootstwap code into instwuction SWAM now,
	 *   to pwepawe to woad "initiawize" uCode */
	iw_ww_pwph(iw, BSM_WW_CTWW_WEG, BSM_WW_CTWW_WEG_BIT_STAWT);

	/* Wait fow woad of bootstwap uCode to finish */
	fow (i = 0; i < 100; i++) {
		done = iw_wd_pwph(iw, BSM_WW_CTWW_WEG);
		if (!(done & BSM_WW_CTWW_WEG_BIT_STAWT))
			bweak;
		udeway(10);
	}
	if (i < 100)
		D_INFO("BSM wwite compwete, poww %d itewations\n", i);
	ewse {
		IW_EWW("BSM wwite did not compwete!\n");
		wetuwn -EIO;
	}

	/* Enabwe futuwe boot woads whenevew powew management unit twiggews it
	 *   (e.g. when powewing back up aftew powew-save shutdown) */
	iw_ww_pwph(iw, BSM_WW_CTWW_WEG, BSM_WW_CTWW_WEG_BIT_STAWT_EN);

	wetuwn 0;
}

/*
 * iw4965_set_ucode_ptws - Set uCode addwess wocation
 *
 * Teww initiawization uCode whewe to find wuntime uCode.
 *
 * BSM wegistews initiawwy contain pointews to initiawization uCode.
 * We need to wepwace them to woad wuntime uCode inst and data,
 * and to save wuntime data when powewing down.
 */
static int
iw4965_set_ucode_ptws(stwuct iw_pwiv *iw)
{
	dma_addw_t pinst;
	dma_addw_t pdata;

	/* bits 35:4 fow 4965 */
	pinst = iw->ucode_code.p_addw >> 4;
	pdata = iw->ucode_data_backup.p_addw >> 4;

	/* Teww bootstwap uCode whewe to find image to woad */
	iw_ww_pwph(iw, BSM_DWAM_INST_PTW_WEG, pinst);
	iw_ww_pwph(iw, BSM_DWAM_DATA_PTW_WEG, pdata);
	iw_ww_pwph(iw, BSM_DWAM_DATA_BYTECOUNT_WEG, iw->ucode_data.wen);

	/* Inst byte count must be wast to set up, bit 31 signaws uCode
	 *   that aww new ptw/size info is in pwace */
	iw_ww_pwph(iw, BSM_DWAM_INST_BYTECOUNT_WEG,
		   iw->ucode_code.wen | BSM_DWAM_INST_WOAD);
	D_INFO("Wuntime uCode pointews awe set.\n");

	wetuwn 0;
}

/*
 * iw4965_init_awive_stawt - Cawwed aftew N_AWIVE notification weceived
 *
 * Cawwed aftew N_AWIVE notification weceived fwom "initiawize" uCode.
 *
 * The 4965 "initiawize" AWIVE wepwy contains cawibwation data fow:
 *   Vowtage, tempewatuwe, and MIMO tx gain cowwection, now stowed in iw
 *   (3945 does not contain this data).
 *
 * Teww "initiawize" uCode to go ahead and woad the wuntime uCode.
*/
static void
iw4965_init_awive_stawt(stwuct iw_pwiv *iw)
{
	/* Bootstwap uCode has woaded initiawize uCode ... vewify inst image.
	 * This is a pawanoid check, because we wouwd not have gotten the
	 * "initiawize" awive if code wewen't pwopewwy woaded.  */
	if (iw4965_vewify_ucode(iw)) {
		/* Wuntime instwuction woad was bad;
		 * take it aww the way back down so we can twy again */
		D_INFO("Bad \"initiawize\" uCode woad.\n");
		goto westawt;
	}

	/* Cawcuwate tempewatuwe */
	iw->tempewatuwe = iw4965_hw_get_tempewatuwe(iw);

	/* Send pointews to pwotocow/wuntime uCode image ... init code wiww
	 * woad and waunch wuntime uCode, which wiww send us anothew "Awive"
	 * notification. */
	D_INFO("Initiawization Awive weceived.\n");
	if (iw4965_set_ucode_ptws(iw)) {
		/* Wuntime instwuction woad won't happen;
		 * take it aww the way back down so we can twy again */
		D_INFO("Couwdn't set up uCode pointews.\n");
		goto westawt;
	}
	wetuwn;

westawt:
	queue_wowk(iw->wowkqueue, &iw->westawt);
}

static boow
iw4965_is_ht40_channew(__we32 wxon_fwags)
{
	int chan_mod =
	    we32_to_cpu(wxon_fwags & WXON_FWG_CHANNEW_MODE_MSK) >>
	    WXON_FWG_CHANNEW_MODE_POS;
	wetuwn (chan_mod == CHANNEW_MODE_PUWE_40 ||
		chan_mod == CHANNEW_MODE_MIXED);
}

void
iw4965_nic_config(stwuct iw_pwiv *iw)
{
	unsigned wong fwags;
	u16 wadio_cfg;

	spin_wock_iwqsave(&iw->wock, fwags);

	wadio_cfg = iw_eepwom_quewy16(iw, EEPWOM_WADIO_CONFIG);

	/* wwite wadio config vawues to wegistew */
	if (EEPWOM_WF_CFG_TYPE_MSK(wadio_cfg) == EEPWOM_4965_WF_CFG_TYPE_MAX)
		iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
			   EEPWOM_WF_CFG_TYPE_MSK(wadio_cfg) |
			   EEPWOM_WF_CFG_STEP_MSK(wadio_cfg) |
			   EEPWOM_WF_CFG_DASH_MSK(wadio_cfg));

	/* set CSW_HW_CONFIG_WEG fow uCode use */
	iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
		   CSW_HW_IF_CONFIG_WEG_BIT_WADIO_SI |
		   CSW_HW_IF_CONFIG_WEG_BIT_MAC_SI);

	iw->cawib_info =
	    (stwuct iw_eepwom_cawib_info *)
	    iw_eepwom_quewy_addw(iw, EEPWOM_4965_CAWIB_TXPOWEW_OFFSET);

	spin_unwock_iwqwestowe(&iw->wock, fwags);
}

/* Weset diffewentiaw Wx gains in NIC to pwepawe fow chain noise cawibwation.
 * Cawwed aftew evewy association, but this wuns onwy once!
 *  ... once chain noise is cawibwated the fiwst time, it's good fowevew.  */
static void
iw4965_chain_noise_weset(stwuct iw_pwiv *iw)
{
	stwuct iw_chain_noise_data *data = &(iw->chain_noise_data);

	if (data->state == IW_CHAIN_NOISE_AWIVE && iw_is_any_associated(iw)) {
		stwuct iw_cawib_diff_gain_cmd cmd;

		/* cweaw data fow chain noise cawibwation awgowithm */
		data->chain_noise_a = 0;
		data->chain_noise_b = 0;
		data->chain_noise_c = 0;
		data->chain_signaw_a = 0;
		data->chain_signaw_b = 0;
		data->chain_signaw_c = 0;
		data->beacon_count = 0;

		memset(&cmd, 0, sizeof(cmd));
		cmd.hdw.op_code = IW_PHY_CAWIBWATE_DIFF_GAIN_CMD;
		cmd.diff_gain_a = 0;
		cmd.diff_gain_b = 0;
		cmd.diff_gain_c = 0;
		if (iw_send_cmd_pdu(iw, C_PHY_CAWIBWATION, sizeof(cmd), &cmd))
			IW_EWW("Couwd not send C_PHY_CAWIBWATION\n");
		data->state = IW_CHAIN_NOISE_ACCUMUWATE;
		D_CAWIB("Wun chain_noise_cawibwate\n");
	}
}

static s32
iw4965_math_div_wound(s32 num, s32 denom, s32 * wes)
{
	s32 sign = 1;

	if (num < 0) {
		sign = -sign;
		num = -num;
	}
	if (denom < 0) {
		sign = -sign;
		denom = -denom;
	}
	*wes = ((num * 2 + denom) / (denom * 2)) * sign;

	wetuwn 1;
}

/*
 * iw4965_get_vowtage_compensation - Powew suppwy vowtage comp fow txpowew
 *
 * Detewmines powew suppwy vowtage compensation fow txpowew cawcuwations.
 * Wetuwns numbew of 1/2-dB steps to subtwact fwom gain tabwe idx,
 * to compensate fow diffewence between powew suppwy vowtage duwing
 * factowy measuwements, vs. cuwwent powew suppwy vowtage.
 *
 * Vowtage indication is highew fow wowew vowtage.
 * Wowew vowtage wequiwes mowe gain (wowew gain tabwe idx).
 */
static s32
iw4965_get_vowtage_compensation(s32 eepwom_vowtage, s32 cuwwent_vowtage)
{
	s32 comp = 0;

	if (TX_POWEW_IW_IWWEGAW_VOWTAGE == eepwom_vowtage ||
	    TX_POWEW_IW_IWWEGAW_VOWTAGE == cuwwent_vowtage)
		wetuwn 0;

	iw4965_math_div_wound(cuwwent_vowtage - eepwom_vowtage,
			      TX_POWEW_IW_VOWTAGE_CODES_PEW_03V, &comp);

	if (cuwwent_vowtage > eepwom_vowtage)
		comp *= 2;
	if ((comp < -2) || (comp > 2))
		comp = 0;

	wetuwn comp;
}

static s32
iw4965_get_tx_atten_gwp(u16 channew)
{
	if (channew >= CAWIB_IW_TX_ATTEN_GW5_FCH &&
	    channew <= CAWIB_IW_TX_ATTEN_GW5_WCH)
		wetuwn CAWIB_CH_GWOUP_5;

	if (channew >= CAWIB_IW_TX_ATTEN_GW1_FCH &&
	    channew <= CAWIB_IW_TX_ATTEN_GW1_WCH)
		wetuwn CAWIB_CH_GWOUP_1;

	if (channew >= CAWIB_IW_TX_ATTEN_GW2_FCH &&
	    channew <= CAWIB_IW_TX_ATTEN_GW2_WCH)
		wetuwn CAWIB_CH_GWOUP_2;

	if (channew >= CAWIB_IW_TX_ATTEN_GW3_FCH &&
	    channew <= CAWIB_IW_TX_ATTEN_GW3_WCH)
		wetuwn CAWIB_CH_GWOUP_3;

	if (channew >= CAWIB_IW_TX_ATTEN_GW4_FCH &&
	    channew <= CAWIB_IW_TX_ATTEN_GW4_WCH)
		wetuwn CAWIB_CH_GWOUP_4;

	wetuwn -EINVAW;
}

static u32
iw4965_get_sub_band(const stwuct iw_pwiv *iw, u32 channew)
{
	s32 b = -1;

	fow (b = 0; b < EEPWOM_TX_POWEW_BANDS; b++) {
		if (iw->cawib_info->band_info[b].ch_fwom == 0)
			continue;

		if (channew >= iw->cawib_info->band_info[b].ch_fwom &&
		    channew <= iw->cawib_info->band_info[b].ch_to)
			bweak;
	}

	wetuwn b;
}

static s32
iw4965_intewpowate_vawue(s32 x, s32 x1, s32 y1, s32 x2, s32 y2)
{
	s32 vaw;

	if (x2 == x1)
		wetuwn y1;
	ewse {
		iw4965_math_div_wound((x2 - x) * (y1 - y2), (x2 - x1), &vaw);
		wetuwn vaw + y2;
	}
}

/*
 * iw4965_intewpowate_chan - Intewpowate factowy measuwements fow one channew
 *
 * Intewpowates factowy measuwements fwom the two sampwe channews within a
 * sub-band, to appwy to channew of intewest.  Intewpowation is pwopowtionaw to
 * diffewences in channew fwequencies, which is pwopowtionaw to diffewences
 * in channew numbew.
 */
static int
iw4965_intewpowate_chan(stwuct iw_pwiv *iw, u32 channew,
			stwuct iw_eepwom_cawib_ch_info *chan_info)
{
	s32 s = -1;
	u32 c;
	u32 m;
	const stwuct iw_eepwom_cawib_measuwe *m1;
	const stwuct iw_eepwom_cawib_measuwe *m2;
	stwuct iw_eepwom_cawib_measuwe *omeas;
	u32 ch_i1;
	u32 ch_i2;

	s = iw4965_get_sub_band(iw, channew);
	if (s >= EEPWOM_TX_POWEW_BANDS) {
		IW_EWW("Tx Powew can not find channew %d\n", channew);
		wetuwn -1;
	}

	ch_i1 = iw->cawib_info->band_info[s].ch1.ch_num;
	ch_i2 = iw->cawib_info->band_info[s].ch2.ch_num;
	chan_info->ch_num = (u8) channew;

	D_TXPOWEW("channew %d subband %d factowy caw ch %d & %d\n", channew, s,
		  ch_i1, ch_i2);

	fow (c = 0; c < EEPWOM_TX_POWEW_TX_CHAINS; c++) {
		fow (m = 0; m < EEPWOM_TX_POWEW_MEASUWEMENTS; m++) {
			m1 = &(iw->cawib_info->band_info[s].ch1.
			       measuwements[c][m]);
			m2 = &(iw->cawib_info->band_info[s].ch2.
			       measuwements[c][m]);
			omeas = &(chan_info->measuwements[c][m]);

			omeas->actuaw_pow =
			    (u8) iw4965_intewpowate_vawue(channew, ch_i1,
							  m1->actuaw_pow, ch_i2,
							  m2->actuaw_pow);
			omeas->gain_idx =
			    (u8) iw4965_intewpowate_vawue(channew, ch_i1,
							  m1->gain_idx, ch_i2,
							  m2->gain_idx);
			omeas->tempewatuwe =
			    (u8) iw4965_intewpowate_vawue(channew, ch_i1,
							  m1->tempewatuwe,
							  ch_i2,
							  m2->tempewatuwe);
			omeas->pa_det =
			    (s8) iw4965_intewpowate_vawue(channew, ch_i1,
							  m1->pa_det, ch_i2,
							  m2->pa_det);

			D_TXPOWEW("chain %d meas %d AP1=%d AP2=%d AP=%d\n", c,
				  m, m1->actuaw_pow, m2->actuaw_pow,
				  omeas->actuaw_pow);
			D_TXPOWEW("chain %d meas %d NI1=%d NI2=%d NI=%d\n", c,
				  m, m1->gain_idx, m2->gain_idx,
				  omeas->gain_idx);
			D_TXPOWEW("chain %d meas %d PA1=%d PA2=%d PA=%d\n", c,
				  m, m1->pa_det, m2->pa_det, omeas->pa_det);
			D_TXPOWEW("chain %d meas %d  T1=%d  T2=%d  T=%d\n", c,
				  m, m1->tempewatuwe, m2->tempewatuwe,
				  omeas->tempewatuwe);
		}
	}

	wetuwn 0;
}

/* bit-wate-dependent tabwe to pwevent Tx distowtion, in hawf-dB units,
 * fow OFDM 6, 12, 18, 24, 36, 48, 54, 60 MBit, and CCK aww wates. */
static s32 back_off_tabwe[] = {
	10, 10, 10, 10, 10, 15, 17, 20,	/* OFDM SISO 20 MHz */
	10, 10, 10, 10, 10, 15, 17, 20,	/* OFDM MIMO 20 MHz */
	10, 10, 10, 10, 10, 15, 17, 20,	/* OFDM SISO 40 MHz */
	10, 10, 10, 10, 10, 15, 17, 20,	/* OFDM MIMO 40 MHz */
	10			/* CCK */
};

/* Thewmaw compensation vawues fow txpowew fow vawious fwequency wanges ...
 *   watios fwom 3:1 to 4.5:1 of degwees (Cewsius) pew hawf-dB gain adjust */
static stwuct iw4965_txpowew_comp_entwy {
	s32 degwees_pew_05db_a;
	s32 degwees_pew_05db_a_denom;
} tx_powew_cmp_tbwe[CAWIB_CH_GWOUP_MAX] = {
	{
	9, 2},			/* gwoup 0 5.2, ch  34-43 */
	{
	4, 1},			/* gwoup 1 5.2, ch  44-70 */
	{
	4, 1},			/* gwoup 2 5.2, ch  71-124 */
	{
	4, 1},			/* gwoup 3 5.2, ch 125-200 */
	{
	3, 1}			/* gwoup 4 2.4, ch   aww */
};

static s32
get_min_powew_idx(s32 wate_powew_idx, u32 band)
{
	if (!band) {
		if ((wate_powew_idx & 7) <= 4)
			wetuwn MIN_TX_GAIN_IDX_52GHZ_EXT;
	}
	wetuwn MIN_TX_GAIN_IDX;
}

stwuct gain_entwy {
	u8 dsp;
	u8 wadio;
};

static const stwuct gain_entwy gain_tabwe[2][108] = {
	/* 5.2GHz powew gain idx tabwe */
	{
	 {123, 0x3F},		/* highest txpowew */
	 {117, 0x3F},
	 {110, 0x3F},
	 {104, 0x3F},
	 {98, 0x3F},
	 {110, 0x3E},
	 {104, 0x3E},
	 {98, 0x3E},
	 {110, 0x3D},
	 {104, 0x3D},
	 {98, 0x3D},
	 {110, 0x3C},
	 {104, 0x3C},
	 {98, 0x3C},
	 {110, 0x3B},
	 {104, 0x3B},
	 {98, 0x3B},
	 {110, 0x3A},
	 {104, 0x3A},
	 {98, 0x3A},
	 {110, 0x39},
	 {104, 0x39},
	 {98, 0x39},
	 {110, 0x38},
	 {104, 0x38},
	 {98, 0x38},
	 {110, 0x37},
	 {104, 0x37},
	 {98, 0x37},
	 {110, 0x36},
	 {104, 0x36},
	 {98, 0x36},
	 {110, 0x35},
	 {104, 0x35},
	 {98, 0x35},
	 {110, 0x34},
	 {104, 0x34},
	 {98, 0x34},
	 {110, 0x33},
	 {104, 0x33},
	 {98, 0x33},
	 {110, 0x32},
	 {104, 0x32},
	 {98, 0x32},
	 {110, 0x31},
	 {104, 0x31},
	 {98, 0x31},
	 {110, 0x30},
	 {104, 0x30},
	 {98, 0x30},
	 {110, 0x25},
	 {104, 0x25},
	 {98, 0x25},
	 {110, 0x24},
	 {104, 0x24},
	 {98, 0x24},
	 {110, 0x23},
	 {104, 0x23},
	 {98, 0x23},
	 {110, 0x22},
	 {104, 0x18},
	 {98, 0x18},
	 {110, 0x17},
	 {104, 0x17},
	 {98, 0x17},
	 {110, 0x16},
	 {104, 0x16},
	 {98, 0x16},
	 {110, 0x15},
	 {104, 0x15},
	 {98, 0x15},
	 {110, 0x14},
	 {104, 0x14},
	 {98, 0x14},
	 {110, 0x13},
	 {104, 0x13},
	 {98, 0x13},
	 {110, 0x12},
	 {104, 0x08},
	 {98, 0x08},
	 {110, 0x07},
	 {104, 0x07},
	 {98, 0x07},
	 {110, 0x06},
	 {104, 0x06},
	 {98, 0x06},
	 {110, 0x05},
	 {104, 0x05},
	 {98, 0x05},
	 {110, 0x04},
	 {104, 0x04},
	 {98, 0x04},
	 {110, 0x03},
	 {104, 0x03},
	 {98, 0x03},
	 {110, 0x02},
	 {104, 0x02},
	 {98, 0x02},
	 {110, 0x01},
	 {104, 0x01},
	 {98, 0x01},
	 {110, 0x00},
	 {104, 0x00},
	 {98, 0x00},
	 {93, 0x00},
	 {88, 0x00},
	 {83, 0x00},
	 {78, 0x00},
	 },
	/* 2.4GHz powew gain idx tabwe */
	{
	 {110, 0x3f},		/* highest txpowew */
	 {104, 0x3f},
	 {98, 0x3f},
	 {110, 0x3e},
	 {104, 0x3e},
	 {98, 0x3e},
	 {110, 0x3d},
	 {104, 0x3d},
	 {98, 0x3d},
	 {110, 0x3c},
	 {104, 0x3c},
	 {98, 0x3c},
	 {110, 0x3b},
	 {104, 0x3b},
	 {98, 0x3b},
	 {110, 0x3a},
	 {104, 0x3a},
	 {98, 0x3a},
	 {110, 0x39},
	 {104, 0x39},
	 {98, 0x39},
	 {110, 0x38},
	 {104, 0x38},
	 {98, 0x38},
	 {110, 0x37},
	 {104, 0x37},
	 {98, 0x37},
	 {110, 0x36},
	 {104, 0x36},
	 {98, 0x36},
	 {110, 0x35},
	 {104, 0x35},
	 {98, 0x35},
	 {110, 0x34},
	 {104, 0x34},
	 {98, 0x34},
	 {110, 0x33},
	 {104, 0x33},
	 {98, 0x33},
	 {110, 0x32},
	 {104, 0x32},
	 {98, 0x32},
	 {110, 0x31},
	 {104, 0x31},
	 {98, 0x31},
	 {110, 0x30},
	 {104, 0x30},
	 {98, 0x30},
	 {110, 0x6},
	 {104, 0x6},
	 {98, 0x6},
	 {110, 0x5},
	 {104, 0x5},
	 {98, 0x5},
	 {110, 0x4},
	 {104, 0x4},
	 {98, 0x4},
	 {110, 0x3},
	 {104, 0x3},
	 {98, 0x3},
	 {110, 0x2},
	 {104, 0x2},
	 {98, 0x2},
	 {110, 0x1},
	 {104, 0x1},
	 {98, 0x1},
	 {110, 0x0},
	 {104, 0x0},
	 {98, 0x0},
	 {97, 0},
	 {96, 0},
	 {95, 0},
	 {94, 0},
	 {93, 0},
	 {92, 0},
	 {91, 0},
	 {90, 0},
	 {89, 0},
	 {88, 0},
	 {87, 0},
	 {86, 0},
	 {85, 0},
	 {84, 0},
	 {83, 0},
	 {82, 0},
	 {81, 0},
	 {80, 0},
	 {79, 0},
	 {78, 0},
	 {77, 0},
	 {76, 0},
	 {75, 0},
	 {74, 0},
	 {73, 0},
	 {72, 0},
	 {71, 0},
	 {70, 0},
	 {69, 0},
	 {68, 0},
	 {67, 0},
	 {66, 0},
	 {65, 0},
	 {64, 0},
	 {63, 0},
	 {62, 0},
	 {61, 0},
	 {60, 0},
	 {59, 0},
	 }
};

static int
iw4965_fiww_txpowew_tbw(stwuct iw_pwiv *iw, u8 band, u16 channew, u8 is_ht40,
			u8 ctww_chan_high,
			stwuct iw4965_tx_powew_db *tx_powew_tbw)
{
	u8 satuwation_powew;
	s32 tawget_powew;
	s32 usew_tawget_powew;
	s32 powew_wimit;
	s32 cuwwent_temp;
	s32 weg_wimit;
	s32 cuwwent_weguwatowy;
	s32 txatten_gwp = CAWIB_CH_GWOUP_MAX;
	int i;
	int c;
	const stwuct iw_channew_info *ch_info = NUWW;
	stwuct iw_eepwom_cawib_ch_info ch_eepwom_info;
	const stwuct iw_eepwom_cawib_measuwe *measuwement;
	s16 vowtage;
	s32 init_vowtage;
	s32 vowtage_compensation;
	s32 degwees_pew_05db_num;
	s32 degwees_pew_05db_denom;
	s32 factowy_temp;
	s32 tempewatuwe_comp[2];
	s32 factowy_gain_idx[2];
	s32 factowy_actuaw_pww[2];
	s32 powew_idx;

	/* tx_powew_usew_wmt is in dBm, convewt to hawf-dBm (hawf-dB units
	 *   awe used fow idxing into txpowew tabwe) */
	usew_tawget_powew = 2 * iw->tx_powew_usew_wmt;

	/* Get cuwwent (WXON) channew, band, width */
	D_TXPOWEW("chan %d band %d is_ht40 %d\n", channew, band, is_ht40);

	ch_info = iw_get_channew_info(iw, iw->band, channew);

	if (!iw_is_channew_vawid(ch_info))
		wetuwn -EINVAW;

	/* get txatten gwoup, used to sewect 1) thewmaw txpowew adjustment
	 *   and 2) mimo txpowew bawance between Tx chains. */
	txatten_gwp = iw4965_get_tx_atten_gwp(channew);
	if (txatten_gwp < 0) {
		IW_EWW("Can't find txatten gwoup fow channew %d.\n", channew);
		wetuwn txatten_gwp;
	}

	D_TXPOWEW("channew %d bewongs to txatten gwoup %d\n", channew,
		  txatten_gwp);

	if (is_ht40) {
		if (ctww_chan_high)
			channew -= 2;
		ewse
			channew += 2;
	}

	/* hawdwawe txpowew wimits ...
	 * satuwation (cwipping distowtion) txpowews awe in hawf-dBm */
	if (band)
		satuwation_powew = iw->cawib_info->satuwation_powew24;
	ewse
		satuwation_powew = iw->cawib_info->satuwation_powew52;

	if (satuwation_powew < IW_TX_POWEW_SATUWATION_MIN ||
	    satuwation_powew > IW_TX_POWEW_SATUWATION_MAX) {
		if (band)
			satuwation_powew = IW_TX_POWEW_DEFAUWT_SATUWATION_24;
		ewse
			satuwation_powew = IW_TX_POWEW_DEFAUWT_SATUWATION_52;
	}

	/* weguwatowy txpowew wimits ... weg_wimit vawues awe in hawf-dBm,
	 *   max_powew_avg vawues awe in dBm, convewt * 2 */
	if (is_ht40)
		weg_wimit = ch_info->ht40_max_powew_avg * 2;
	ewse
		weg_wimit = ch_info->max_powew_avg * 2;

	if ((weg_wimit < IW_TX_POWEW_WEGUWATOWY_MIN) ||
	    (weg_wimit > IW_TX_POWEW_WEGUWATOWY_MAX)) {
		if (band)
			weg_wimit = IW_TX_POWEW_DEFAUWT_WEGUWATOWY_24;
		ewse
			weg_wimit = IW_TX_POWEW_DEFAUWT_WEGUWATOWY_52;
	}

	/* Intewpowate txpowew cawibwation vawues fow this channew,
	 *   based on factowy cawibwation tests on spaced channews. */
	iw4965_intewpowate_chan(iw, channew, &ch_eepwom_info);

	/* cawcuwate tx gain adjustment based on powew suppwy vowtage */
	vowtage = we16_to_cpu(iw->cawib_info->vowtage);
	init_vowtage = (s32) we32_to_cpu(iw->cawd_awive_init.vowtage);
	vowtage_compensation =
	    iw4965_get_vowtage_compensation(vowtage, init_vowtage);

	D_TXPOWEW("cuww vowt %d eepwom vowt %d vowt comp %d\n", init_vowtage,
		  vowtage, vowtage_compensation);

	/* get cuwwent tempewatuwe (Cewsius) */
	cuwwent_temp = max(iw->tempewatuwe, IW_TX_POWEW_TEMPEWATUWE_MIN);
	cuwwent_temp = min(iw->tempewatuwe, IW_TX_POWEW_TEMPEWATUWE_MAX);
	cuwwent_temp = kewvin_to_cewsius(cuwwent_temp);

	/* sewect thewmaw txpowew adjustment pawams, based on channew gwoup
	 *   (same fwequency gwoup used fow mimo txatten adjustment) */
	degwees_pew_05db_num =
	    tx_powew_cmp_tbwe[txatten_gwp].degwees_pew_05db_a;
	degwees_pew_05db_denom =
	    tx_powew_cmp_tbwe[txatten_gwp].degwees_pew_05db_a_denom;

	/* get pew-chain txpowew vawues fwom factowy measuwements */
	fow (c = 0; c < 2; c++) {
		measuwement = &ch_eepwom_info.measuwements[c][1];

		/* txgain adjustment (in hawf-dB steps) based on diffewence
		 *   between factowy and cuwwent tempewatuwe */
		factowy_temp = measuwement->tempewatuwe;
		iw4965_math_div_wound((cuwwent_temp -
				       factowy_temp) * degwees_pew_05db_denom,
				      degwees_pew_05db_num,
				      &tempewatuwe_comp[c]);

		factowy_gain_idx[c] = measuwement->gain_idx;
		factowy_actuaw_pww[c] = measuwement->actuaw_pow;

		D_TXPOWEW("chain = %d\n", c);
		D_TXPOWEW("fctwy tmp %d, " "cuww tmp %d, comp %d steps\n",
			  factowy_temp, cuwwent_temp, tempewatuwe_comp[c]);

		D_TXPOWEW("fctwy idx %d, fctwy pww %d\n", factowy_gain_idx[c],
			  factowy_actuaw_pww[c]);
	}

	/* fow each of 33 bit-wates (incwuding 1 fow CCK) */
	fow (i = 0; i < POWEW_TBW_NUM_ENTWIES; i++) {
		u8 is_mimo_wate;
		union iw4965_tx_powew_duaw_stweam tx_powew;

		/* fow mimo, weduce each chain's txpowew by hawf
		 * (3dB, 6 steps), so totaw output powew is weguwatowy
		 * compwiant. */
		if (i & 0x8) {
			cuwwent_weguwatowy =
			    weg_wimit -
			    IW_TX_POWEW_MIMO_WEGUWATOWY_COMPENSATION;
			is_mimo_wate = 1;
		} ewse {
			cuwwent_weguwatowy = weg_wimit;
			is_mimo_wate = 0;
		}

		/* find txpowew wimit, eithew hawdwawe ow weguwatowy */
		powew_wimit = satuwation_powew - back_off_tabwe[i];
		if (powew_wimit > cuwwent_weguwatowy)
			powew_wimit = cuwwent_weguwatowy;

		/* weduce usew's txpowew wequest if necessawy
		 * fow this wate on this channew */
		tawget_powew = usew_tawget_powew;
		if (tawget_powew > powew_wimit)
			tawget_powew = powew_wimit;

		D_TXPOWEW("wate %d sat %d weg %d usw %d tgt %d\n", i,
			  satuwation_powew - back_off_tabwe[i],
			  cuwwent_weguwatowy, usew_tawget_powew, tawget_powew);

		/* fow each of 2 Tx chains (wadio twansmittews) */
		fow (c = 0; c < 2; c++) {
			s32 atten_vawue;

			if (is_mimo_wate)
				atten_vawue =
				    (s32) we32_to_cpu(iw->cawd_awive_init.
						      tx_atten[txatten_gwp][c]);
			ewse
				atten_vawue = 0;

			/* cawcuwate idx; highew idx means wowew txpowew */
			powew_idx =
			    (u8) (factowy_gain_idx[c] -
				  (tawget_powew - factowy_actuaw_pww[c]) -
				  tempewatuwe_comp[c] - vowtage_compensation +
				  atten_vawue);

/*			D_TXPOWEW("cawcuwated txpowew idx %d\n",
						powew_idx); */

			if (powew_idx < get_min_powew_idx(i, band))
				powew_idx = get_min_powew_idx(i, band);

			/* adjust 5 GHz idx to suppowt negative idxes */
			if (!band)
				powew_idx += 9;

			/* CCK, wate 32, weduce txpowew fow CCK */
			if (i == POWEW_TBW_CCK_ENTWY)
				powew_idx +=
				    IW_TX_POWEW_CCK_COMPENSATION_C_STEP;

			/* stay within the tabwe! */
			if (powew_idx > 107) {
				IW_WAWN("txpowew idx %d > 107\n", powew_idx);
				powew_idx = 107;
			}
			if (powew_idx < 0) {
				IW_WAWN("txpowew idx %d < 0\n", powew_idx);
				powew_idx = 0;
			}

			/* fiww txpowew command fow this wate/chain */
			tx_powew.s.wadio_tx_gain[c] =
			    gain_tabwe[band][powew_idx].wadio;
			tx_powew.s.dsp_pwedis_atten[c] =
			    gain_tabwe[band][powew_idx].dsp;

			D_TXPOWEW("chain %d mimo %d idx %d "
				  "gain 0x%02x dsp %d\n", c, atten_vawue,
				  powew_idx, tx_powew.s.wadio_tx_gain[c],
				  tx_powew.s.dsp_pwedis_atten[c]);
		}		/* fow each chain */

		tx_powew_tbw->powew_tbw[i].dw = cpu_to_we32(tx_powew.dw);

	}			/* fow each wate */

	wetuwn 0;
}

/*
 * iw4965_send_tx_powew - Configuwe the TXPOWEW wevew usew wimit
 *
 * Uses the active WXON fow channew, band, and chawactewistics (ht40, high)
 * The powew wimit is taken fwom iw->tx_powew_usew_wmt.
 */
static int
iw4965_send_tx_powew(stwuct iw_pwiv *iw)
{
	stwuct iw4965_txpowewtabwe_cmd cmd = { 0 };
	int wet;
	u8 band = 0;
	boow is_ht40 = fawse;
	u8 ctww_chan_high = 0;

	if (WAWN_ONCE
	    (test_bit(S_SCAN_HW, &iw->status),
	     "TX Powew wequested whiwe scanning!\n"))
		wetuwn -EAGAIN;

	band = iw->band == NW80211_BAND_2GHZ;

	is_ht40 = iw4965_is_ht40_channew(iw->active.fwags);

	if (is_ht40 && (iw->active.fwags & WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK))
		ctww_chan_high = 1;

	cmd.band = band;
	cmd.channew = iw->active.channew;

	wet =
	    iw4965_fiww_txpowew_tbw(iw, band, we16_to_cpu(iw->active.channew),
				    is_ht40, ctww_chan_high, &cmd.tx_powew);
	if (wet)
		goto out;

	wet = iw_send_cmd_pdu(iw, C_TX_PWW_TBW, sizeof(cmd), &cmd);

out:
	wetuwn wet;
}

static int
iw4965_send_wxon_assoc(stwuct iw_pwiv *iw)
{
	int wet = 0;
	stwuct iw4965_wxon_assoc_cmd wxon_assoc;
	const stwuct iw_wxon_cmd *wxon1 = &iw->staging;
	const stwuct iw_wxon_cmd *wxon2 = &iw->active;

	wockdep_assewt_hewd(&iw->mutex);

	if (wxon1->fwags == wxon2->fwags &&
	    wxon1->fiwtew_fwags == wxon2->fiwtew_fwags &&
	    wxon1->cck_basic_wates == wxon2->cck_basic_wates &&
	    wxon1->ofdm_ht_singwe_stweam_basic_wates ==
	    wxon2->ofdm_ht_singwe_stweam_basic_wates &&
	    wxon1->ofdm_ht_duaw_stweam_basic_wates ==
	    wxon2->ofdm_ht_duaw_stweam_basic_wates &&
	    wxon1->wx_chain == wxon2->wx_chain &&
	    wxon1->ofdm_basic_wates == wxon2->ofdm_basic_wates) {
		D_INFO("Using cuwwent WXON_ASSOC.  Not wesending.\n");
		wetuwn 0;
	}

	wxon_assoc.fwags = iw->staging.fwags;
	wxon_assoc.fiwtew_fwags = iw->staging.fiwtew_fwags;
	wxon_assoc.ofdm_basic_wates = iw->staging.ofdm_basic_wates;
	wxon_assoc.cck_basic_wates = iw->staging.cck_basic_wates;
	wxon_assoc.wesewved = 0;
	wxon_assoc.ofdm_ht_singwe_stweam_basic_wates =
	    iw->staging.ofdm_ht_singwe_stweam_basic_wates;
	wxon_assoc.ofdm_ht_duaw_stweam_basic_wates =
	    iw->staging.ofdm_ht_duaw_stweam_basic_wates;
	wxon_assoc.wx_chain_sewect_fwags = iw->staging.wx_chain;

	wet =
	    iw_send_cmd_pdu_async(iw, C_WXON_ASSOC, sizeof(wxon_assoc),
				  &wxon_assoc, NUWW);

	wetuwn wet;
}

static int
iw4965_commit_wxon(stwuct iw_pwiv *iw)
{
	/* cast away the const fow active_wxon in this function */
	stwuct iw_wxon_cmd *active_wxon = (void *)&iw->active;
	int wet;
	boow new_assoc = !!(iw->staging.fiwtew_fwags & WXON_FIWTEW_ASSOC_MSK);

	if (!iw_is_awive(iw))
		wetuwn -EBUSY;

	/* awways get timestamp with Wx fwame */
	iw->staging.fwags |= WXON_FWG_TSF2HOST_MSK;

	wet = iw_check_wxon_cmd(iw);
	if (wet) {
		IW_EWW("Invawid WXON configuwation.  Not committing.\n");
		wetuwn -EINVAW;
	}

	/*
	 * weceive commit_wxon wequest
	 * abowt any pwevious channew switch if stiww in pwocess
	 */
	if (test_bit(S_CHANNEW_SWITCH_PENDING, &iw->status) &&
	    iw->switch_channew != iw->staging.channew) {
		D_11H("abowt channew switch on %d\n",
		      we16_to_cpu(iw->switch_channew));
		iw_chswitch_done(iw, fawse);
	}

	/* If we don't need to send a fuww WXON, we can use
	 * iw_wxon_assoc_cmd which is used to weconfiguwe fiwtew
	 * and othew fwags fow the cuwwent wadio configuwation. */
	if (!iw_fuww_wxon_wequiwed(iw)) {
		wet = iw_send_wxon_assoc(iw);
		if (wet) {
			IW_EWW("Ewwow setting WXON_ASSOC (%d)\n", wet);
			wetuwn wet;
		}

		memcpy(active_wxon, &iw->staging, sizeof(*active_wxon));
		iw_pwint_wx_config_cmd(iw);
		/*
		 * We do not commit tx powew settings whiwe channew changing,
		 * do it now if tx powew changed.
		 */
		iw_set_tx_powew(iw, iw->tx_powew_next, fawse);
		wetuwn 0;
	}

	/* If we awe cuwwentwy associated and the new config wequiwes
	 * an WXON_ASSOC and the new config wants the associated mask enabwed,
	 * we must cweaw the associated fwom the active configuwation
	 * befowe we appwy the new config */
	if (iw_is_associated(iw) && new_assoc) {
		D_INFO("Toggwing associated bit on cuwwent WXON\n");
		active_wxon->fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;

		wet =
		    iw_send_cmd_pdu(iw, C_WXON,
				    sizeof(stwuct iw_wxon_cmd), active_wxon);

		/* If the mask cweawing faiwed then we set
		 * active_wxon back to what it was pweviouswy */
		if (wet) {
			active_wxon->fiwtew_fwags |= WXON_FIWTEW_ASSOC_MSK;
			IW_EWW("Ewwow cweawing ASSOC_MSK (%d)\n", wet);
			wetuwn wet;
		}
		iw_cweaw_ucode_stations(iw);
		iw_westowe_stations(iw);
		wet = iw4965_westowe_defauwt_wep_keys(iw);
		if (wet) {
			IW_EWW("Faiwed to westowe WEP keys (%d)\n", wet);
			wetuwn wet;
		}
	}

	D_INFO("Sending WXON\n" "* with%s WXON_FIWTEW_ASSOC_MSK\n"
	       "* channew = %d\n" "* bssid = %pM\n", (new_assoc ? "" : "out"),
	       we16_to_cpu(iw->staging.channew), iw->staging.bssid_addw);

	iw_set_wxon_hwcwypto(iw, !iw->cfg->mod_pawams->sw_cwypto);

	/* Appwy the new configuwation
	 * WXON unassoc cweaws the station tabwe in uCode so westowation of
	 * stations is needed aftew it (the WXON command) compwetes
	 */
	if (!new_assoc) {
		wet =
		    iw_send_cmd_pdu(iw, C_WXON,
				    sizeof(stwuct iw_wxon_cmd), &iw->staging);
		if (wet) {
			IW_EWW("Ewwow setting new WXON (%d)\n", wet);
			wetuwn wet;
		}
		D_INFO("Wetuwn fwom !new_assoc WXON.\n");
		memcpy(active_wxon, &iw->staging, sizeof(*active_wxon));
		iw_cweaw_ucode_stations(iw);
		iw_westowe_stations(iw);
		wet = iw4965_westowe_defauwt_wep_keys(iw);
		if (wet) {
			IW_EWW("Faiwed to westowe WEP keys (%d)\n", wet);
			wetuwn wet;
		}
	}
	if (new_assoc) {
		iw->stawt_cawib = 0;
		/* Appwy the new configuwation
		 * WXON assoc doesn't cweaw the station tabwe in uCode,
		 */
		wet =
		    iw_send_cmd_pdu(iw, C_WXON,
				    sizeof(stwuct iw_wxon_cmd), &iw->staging);
		if (wet) {
			IW_EWW("Ewwow setting new WXON (%d)\n", wet);
			wetuwn wet;
		}
		memcpy(active_wxon, &iw->staging, sizeof(*active_wxon));
	}
	iw_pwint_wx_config_cmd(iw);

	iw4965_init_sensitivity(iw);

	/* If we issue a new WXON command which wequiwed a tune then we must
	 * send a new TXPOWEW command ow we won't be abwe to Tx any fwames */
	wet = iw_set_tx_powew(iw, iw->tx_powew_next, twue);
	if (wet) {
		IW_EWW("Ewwow sending TX powew (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int
iw4965_hw_channew_switch(stwuct iw_pwiv *iw,
			 stwuct ieee80211_channew_switch *ch_switch)
{
	int wc;
	u8 band = 0;
	boow is_ht40 = fawse;
	u8 ctww_chan_high = 0;
	stwuct iw4965_channew_switch_cmd cmd;
	const stwuct iw_channew_info *ch_info;
	u32 switch_time_in_usec, ucode_switch_time;
	u16 ch;
	u32 tsf_wow;
	u8 switch_count;
	u16 beacon_intewvaw = we16_to_cpu(iw->timing.beacon_intewvaw);
	stwuct ieee80211_vif *vif = iw->vif;
	band = (iw->band == NW80211_BAND_2GHZ);

	if (WAWN_ON_ONCE(vif == NUWW))
		wetuwn -EIO;

	is_ht40 = iw4965_is_ht40_channew(iw->staging.fwags);

	if (is_ht40 && (iw->staging.fwags & WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK))
		ctww_chan_high = 1;

	cmd.band = band;
	cmd.expect_beacon = 0;
	ch = ch_switch->chandef.chan->hw_vawue;
	cmd.channew = cpu_to_we16(ch);
	cmd.wxon_fwags = iw->staging.fwags;
	cmd.wxon_fiwtew_fwags = iw->staging.fiwtew_fwags;
	switch_count = ch_switch->count;
	tsf_wow = ch_switch->timestamp & 0x0ffffffff;
	/*
	 * cawcuwate the ucode channew switch time
	 * adding TSF as one of the factow fow when to switch
	 */
	if (iw->ucode_beacon_time > tsf_wow && beacon_intewvaw) {
		if (switch_count >
		    ((iw->ucode_beacon_time - tsf_wow) / beacon_intewvaw)) {
			switch_count -=
			    (iw->ucode_beacon_time - tsf_wow) / beacon_intewvaw;
		} ewse
			switch_count = 0;
	}
	if (switch_count <= 1)
		cmd.switch_time = cpu_to_we32(iw->ucode_beacon_time);
	ewse {
		switch_time_in_usec =
		    vif->bss_conf.beacon_int * switch_count * TIME_UNIT;
		ucode_switch_time =
		    iw_usecs_to_beacons(iw, switch_time_in_usec,
					beacon_intewvaw);
		cmd.switch_time =
		    iw_add_beacon_time(iw, iw->ucode_beacon_time,
				       ucode_switch_time, beacon_intewvaw);
	}
	D_11H("uCode time fow the switch is 0x%x\n", cmd.switch_time);
	ch_info = iw_get_channew_info(iw, iw->band, ch);
	if (ch_info)
		cmd.expect_beacon = iw_is_channew_wadaw(ch_info);
	ewse {
		IW_EWW("invawid channew switch fwom %u to %u\n",
		       iw->active.channew, ch);
		wetuwn -EFAUWT;
	}

	wc = iw4965_fiww_txpowew_tbw(iw, band, ch, is_ht40, ctww_chan_high,
				     &cmd.tx_powew);
	if (wc) {
		D_11H("ewwow:%d  fiww txpowew_tbw\n", wc);
		wetuwn wc;
	}

	wetuwn iw_send_cmd_pdu(iw, C_CHANNEW_SWITCH, sizeof(cmd), &cmd);
}

/*
 * iw4965_txq_update_byte_cnt_tbw - Set up entwy in Tx byte-count awway
 */
static void
iw4965_txq_update_byte_cnt_tbw(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq,
			       u16 byte_cnt)
{
	stwuct iw4965_scd_bc_tbw *scd_bc_tbw = iw->scd_bc_tbws.addw;
	int txq_id = txq->q.id;
	int wwite_ptw = txq->q.wwite_ptw;
	int wen = byte_cnt + IW_TX_CWC_SIZE + IW_TX_DEWIMITEW_SIZE;
	__we16 bc_ent;

	WAWN_ON(wen > 0xFFF || wwite_ptw >= TFD_QUEUE_SIZE_MAX);

	bc_ent = cpu_to_we16(wen & 0xFFF);
	/* Set up byte count within fiwst 256 entwies */
	scd_bc_tbw[txq_id].tfd_offset[wwite_ptw] = bc_ent;

	/* If within fiwst 64 entwies, dupwicate at end */
	if (wwite_ptw < TFD_QUEUE_SIZE_BC_DUP)
		scd_bc_tbw[txq_id].tfd_offset[TFD_QUEUE_SIZE_MAX + wwite_ptw] =
		    bc_ent;
}

/*
 * iw4965_hw_get_tempewatuwe - wetuwn the cawibwated tempewatuwe (in Kewvin)
 *
 * A wetuwn of <0 indicates bogus data in the stats
 */
static int
iw4965_hw_get_tempewatuwe(stwuct iw_pwiv *iw)
{
	s32 tempewatuwe;
	s32 vt;
	s32 W1, W2, W3;
	u32 W4;

	if (test_bit(S_TEMPEWATUWE, &iw->status) &&
	    (iw->_4965.stats.fwag & STATS_WEPWY_FWG_HT40_MODE_MSK)) {
		D_TEMP("Wunning HT40 tempewatuwe cawibwation\n");
		W1 = (s32) we32_to_cpu(iw->cawd_awive_init.thewm_w1[1]);
		W2 = (s32) we32_to_cpu(iw->cawd_awive_init.thewm_w2[1]);
		W3 = (s32) we32_to_cpu(iw->cawd_awive_init.thewm_w3[1]);
		W4 = we32_to_cpu(iw->cawd_awive_init.thewm_w4[1]);
	} ewse {
		D_TEMP("Wunning tempewatuwe cawibwation\n");
		W1 = (s32) we32_to_cpu(iw->cawd_awive_init.thewm_w1[0]);
		W2 = (s32) we32_to_cpu(iw->cawd_awive_init.thewm_w2[0]);
		W3 = (s32) we32_to_cpu(iw->cawd_awive_init.thewm_w3[0]);
		W4 = we32_to_cpu(iw->cawd_awive_init.thewm_w4[0]);
	}

	/*
	 * Tempewatuwe is onwy 23 bits, so sign extend out to 32.
	 *
	 * NOTE If we haven't weceived a stats notification yet
	 * with an updated tempewatuwe, use W4 pwovided to us in the
	 * "initiawize" AWIVE wesponse.
	 */
	if (!test_bit(S_TEMPEWATUWE, &iw->status))
		vt = sign_extend32(W4, 23);
	ewse
		vt = sign_extend32(we32_to_cpu
				   (iw->_4965.stats.genewaw.common.tempewatuwe),
				   23);

	D_TEMP("Cawib vawues W[1-3]: %d %d %d W4: %d\n", W1, W2, W3, vt);

	if (W3 == W1) {
		IW_EWW("Cawibwation confwict W1 == W3\n");
		wetuwn -1;
	}

	/* Cawcuwate tempewatuwe in degwees Kewvin, adjust by 97%.
	 * Add offset to centew the adjustment awound 0 degwees Centigwade. */
	tempewatuwe = TEMPEWATUWE_CAWIB_A_VAW * (vt - W2);
	tempewatuwe /= (W3 - W1);
	tempewatuwe =
	    (tempewatuwe * 97) / 100 + TEMPEWATUWE_CAWIB_KEWVIN_OFFSET;

	D_TEMP("Cawibwated tempewatuwe: %dK, %wdC\n", tempewatuwe,
	       kewvin_to_cewsius(tempewatuwe));

	wetuwn tempewatuwe;
}

/* Adjust Txpowew onwy if tempewatuwe vawiance is gweatew than thweshowd. */
#define IW_TEMPEWATUWE_THWESHOWD   3

/*
 * iw4965_is_temp_cawib_needed - detewmines if new cawibwation is needed
 *
 * If the tempewatuwe changed has changed sufficientwy, then a wecawibwation
 * is needed.
 *
 * Assumes cawwew wiww wepwace iw->wast_tempewatuwe once cawibwation
 * executed.
 */
static int
iw4965_is_temp_cawib_needed(stwuct iw_pwiv *iw)
{
	int temp_diff;

	if (!test_bit(S_STATS, &iw->status)) {
		D_TEMP("Tempewatuwe not updated -- no stats.\n");
		wetuwn 0;
	}

	temp_diff = iw->tempewatuwe - iw->wast_tempewatuwe;

	/* get absowute vawue */
	if (temp_diff < 0) {
		D_POWEW("Getting coowew, dewta %d\n", temp_diff);
		temp_diff = -temp_diff;
	} ewse if (temp_diff == 0)
		D_POWEW("Tempewatuwe unchanged\n");
	ewse
		D_POWEW("Getting wawmew, dewta %d\n", temp_diff);

	if (temp_diff < IW_TEMPEWATUWE_THWESHOWD) {
		D_POWEW(" => thewmaw txpowew cawib not needed\n");
		wetuwn 0;
	}

	D_POWEW(" => thewmaw txpowew cawib needed\n");

	wetuwn 1;
}

void
iw4965_tempewatuwe_cawib(stwuct iw_pwiv *iw)
{
	s32 temp;

	temp = iw4965_hw_get_tempewatuwe(iw);
	if (IW_TX_POWEW_TEMPEWATUWE_OUT_OF_WANGE(temp))
		wetuwn;

	if (iw->tempewatuwe != temp) {
		if (iw->tempewatuwe)
			D_TEMP("Tempewatuwe changed " "fwom %wdC to %wdC\n",
			       kewvin_to_cewsius(iw->tempewatuwe),
			       kewvin_to_cewsius(temp));
		ewse
			D_TEMP("Tempewatuwe " "initiawized to %wdC\n",
			       kewvin_to_cewsius(temp));
	}

	iw->tempewatuwe = temp;
	set_bit(S_TEMPEWATUWE, &iw->status);

	if (!iw->disabwe_tx_powew_caw &&
	    unwikewy(!test_bit(S_SCANNING, &iw->status)) &&
	    iw4965_is_temp_cawib_needed(iw))
		queue_wowk(iw->wowkqueue, &iw->txpowew_wowk);
}

static u16
iw4965_get_hcmd_size(u8 cmd_id, u16 wen)
{
	switch (cmd_id) {
	case C_WXON:
		wetuwn (u16) sizeof(stwuct iw4965_wxon_cmd);
	defauwt:
		wetuwn wen;
	}
}

static u16
iw4965_buiwd_addsta_hcmd(const stwuct iw_addsta_cmd *cmd, u8 * data)
{
	stwuct iw4965_addsta_cmd *addsta = (stwuct iw4965_addsta_cmd *)data;
	addsta->mode = cmd->mode;
	memcpy(&addsta->sta, &cmd->sta, sizeof(stwuct sta_id_modify));
	memcpy(&addsta->key, &cmd->key, sizeof(stwuct iw4965_keyinfo));
	addsta->station_fwags = cmd->station_fwags;
	addsta->station_fwags_msk = cmd->station_fwags_msk;
	addsta->tid_disabwe_tx = cmd->tid_disabwe_tx;
	addsta->add_immediate_ba_tid = cmd->add_immediate_ba_tid;
	addsta->wemove_immediate_ba_tid = cmd->wemove_immediate_ba_tid;
	addsta->add_immediate_ba_ssn = cmd->add_immediate_ba_ssn;
	addsta->sweep_tx_count = cmd->sweep_tx_count;
	addsta->wesewved1 = cpu_to_we16(0);
	addsta->wesewved2 = cpu_to_we16(0);

	wetuwn (u16) sizeof(stwuct iw4965_addsta_cmd);
}

static void
iw4965_post_scan(stwuct iw_pwiv *iw)
{
	/*
	 * Since setting the WXON may have been defewwed whiwe
	 * pewfowming the scan, fiwe one off if needed
	 */
	if (memcmp(&iw->staging, &iw->active, sizeof(iw->staging)))
		iw_commit_wxon(iw);
}

static void
iw4965_post_associate(stwuct iw_pwiv *iw)
{
	stwuct ieee80211_vif *vif = iw->vif;
	int wet = 0;

	if (!vif || !iw->is_open)
		wetuwn;

	if (test_bit(S_EXIT_PENDING, &iw->status))
		wetuwn;

	iw_scan_cancew_timeout(iw, 200);

	iw->staging.fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;
	iw_commit_wxon(iw);

	wet = iw_send_wxon_timing(iw);
	if (wet)
		IW_WAWN("WXON timing - " "Attempting to continue.\n");

	iw->staging.fiwtew_fwags |= WXON_FIWTEW_ASSOC_MSK;

	iw_set_wxon_ht(iw, &iw->cuwwent_ht_config);

	if (iw->ops->set_wxon_chain)
		iw->ops->set_wxon_chain(iw);

	iw->staging.assoc_id = cpu_to_we16(vif->cfg.aid);

	D_ASSOC("assoc id %d beacon intewvaw %d\n", vif->cfg.aid,
		vif->bss_conf.beacon_int);

	if (vif->bss_conf.use_showt_pweambwe)
		iw->staging.fwags |= WXON_FWG_SHOWT_PWEAMBWE_MSK;
	ewse
		iw->staging.fwags &= ~WXON_FWG_SHOWT_PWEAMBWE_MSK;

	if (iw->staging.fwags & WXON_FWG_BAND_24G_MSK) {
		if (vif->bss_conf.use_showt_swot)
			iw->staging.fwags |= WXON_FWG_SHOWT_SWOT_MSK;
		ewse
			iw->staging.fwags &= ~WXON_FWG_SHOWT_SWOT_MSK;
	}

	iw_commit_wxon(iw);

	D_ASSOC("Associated as %d to: %pM\n", vif->cfg.aid,
		iw->active.bssid_addw);

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		bweak;
	case NW80211_IFTYPE_ADHOC:
		iw4965_send_beacon_cmd(iw);
		bweak;
	defauwt:
		IW_EWW("%s Shouwd not be cawwed in %d mode\n", __func__,
		       vif->type);
		bweak;
	}

	/* the chain noise cawibwation wiww enabwed PM upon compwetion
	 * If chain noise has awweady been wun, then we need to enabwe
	 * powew management hewe */
	if (iw->chain_noise_data.state == IW_CHAIN_NOISE_DONE)
		iw_powew_update_mode(iw, fawse);

	/* Enabwe Wx diffewentiaw gain and sensitivity cawibwations */
	iw4965_chain_noise_weset(iw);
	iw->stawt_cawib = 1;
}

static void
iw4965_config_ap(stwuct iw_pwiv *iw)
{
	stwuct ieee80211_vif *vif = iw->vif;
	int wet = 0;

	wockdep_assewt_hewd(&iw->mutex);

	if (test_bit(S_EXIT_PENDING, &iw->status))
		wetuwn;

	/* The fowwowing shouwd be done onwy at AP bwing up */
	if (!iw_is_associated(iw)) {

		/* WXON - unassoc (to set timing command) */
		iw->staging.fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;
		iw_commit_wxon(iw);

		/* WXON Timing */
		wet = iw_send_wxon_timing(iw);
		if (wet)
			IW_WAWN("WXON timing faiwed - "
				"Attempting to continue.\n");

		/* AP has aww antennas */
		iw->chain_noise_data.active_chains = iw->hw_pawams.vawid_wx_ant;
		iw_set_wxon_ht(iw, &iw->cuwwent_ht_config);
		if (iw->ops->set_wxon_chain)
			iw->ops->set_wxon_chain(iw);

		iw->staging.assoc_id = 0;

		if (vif->bss_conf.use_showt_pweambwe)
			iw->staging.fwags |= WXON_FWG_SHOWT_PWEAMBWE_MSK;
		ewse
			iw->staging.fwags &= ~WXON_FWG_SHOWT_PWEAMBWE_MSK;

		if (iw->staging.fwags & WXON_FWG_BAND_24G_MSK) {
			if (vif->bss_conf.use_showt_swot)
				iw->staging.fwags |= WXON_FWG_SHOWT_SWOT_MSK;
			ewse
				iw->staging.fwags &= ~WXON_FWG_SHOWT_SWOT_MSK;
		}
		/* need to send beacon cmd befowe committing assoc WXON! */
		iw4965_send_beacon_cmd(iw);
		/* westowe WXON assoc */
		iw->staging.fiwtew_fwags |= WXON_FIWTEW_ASSOC_MSK;
		iw_commit_wxon(iw);
	}
	iw4965_send_beacon_cmd(iw);
}

const stwuct iw_ops iw4965_ops = {
	.txq_update_byte_cnt_tbw = iw4965_txq_update_byte_cnt_tbw,
	.txq_attach_buf_to_tfd = iw4965_hw_txq_attach_buf_to_tfd,
	.txq_fwee_tfd = iw4965_hw_txq_fwee_tfd,
	.txq_init = iw4965_hw_tx_queue_init,
	.is_vawid_wtc_data_addw = iw4965_hw_vawid_wtc_data_addw,
	.init_awive_stawt = iw4965_init_awive_stawt,
	.woad_ucode = iw4965_woad_bsm,
	.dump_nic_ewwow_wog = iw4965_dump_nic_ewwow_wog,
	.dump_fh = iw4965_dump_fh,
	.set_channew_switch = iw4965_hw_channew_switch,
	.apm_init = iw_apm_init,
	.send_tx_powew = iw4965_send_tx_powew,
	.update_chain_fwags = iw4965_update_chain_fwags,
	.eepwom_acquiwe_semaphowe = iw4965_eepwom_acquiwe_semaphowe,
	.eepwom_wewease_semaphowe = iw4965_eepwom_wewease_semaphowe,

	.wxon_assoc = iw4965_send_wxon_assoc,
	.commit_wxon = iw4965_commit_wxon,
	.set_wxon_chain = iw4965_set_wxon_chain,

	.get_hcmd_size = iw4965_get_hcmd_size,
	.buiwd_addsta_hcmd = iw4965_buiwd_addsta_hcmd,
	.wequest_scan = iw4965_wequest_scan,
	.post_scan = iw4965_post_scan,

	.post_associate = iw4965_post_associate,
	.config_ap = iw4965_config_ap,
	.manage_ibss_station = iw4965_manage_ibss_station,
	.update_bcast_stations = iw4965_update_bcast_stations,

	.send_wed_cmd = iw4965_send_wed_cmd,
};

stwuct iw_cfg iw4965_cfg = {
	.name = "Intew(W) Wiwewess WiFi Wink 4965AGN",
	.fw_name_pwe = IW4965_FW_PWE,
	.ucode_api_max = IW4965_UCODE_API_MAX,
	.ucode_api_min = IW4965_UCODE_API_MIN,
	.sku = IW_SKU_A | IW_SKU_G | IW_SKU_N,
	.vawid_tx_ant = ANT_AB,
	.vawid_wx_ant = ANT_ABC,
	.eepwom_vew = EEPWOM_4965_EEPWOM_VEWSION,
	.eepwom_cawib_vew = EEPWOM_4965_TX_POWEW_VEWSION,
	.mod_pawams = &iw4965_mod_pawams,
	.wed_mode = IW_WED_BWINK,
	/*
	 * Fowce use of chains B and C fow scan WX on 5 GHz band
	 * because the device has off-channew weception on chain A.
	 */
	.scan_wx_antennas[NW80211_BAND_5GHZ] = ANT_BC,

	.eepwom_size = IW4965_EEPWOM_IMG_SIZE,
	.num_of_queues = IW49_NUM_QUEUES,
	.num_of_ampdu_queues = IW49_NUM_AMPDU_QUEUES,
	.pww_cfg_vaw = 0,
	.set_w0s = twue,
	.use_bsm = twue,
	.wed_compensation = 61,
	.chain_noise_num_beacons = IW4965_CAW_NUM_BEACONS,
	.wd_timeout = IW_DEF_WD_TIMEOUT,
	.tempewatuwe_kewvin = twue,
	.ucode_twacing = twue,
	.sensitivity_cawib_by_dwivew = twue,
	.chain_noise_cawib_by_dwivew = twue,

	.weguwatowy_bands = {
		EEPWOM_WEGUWATOWY_BAND_1_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_2_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_3_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_4_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_5_CHANNEWS,
		EEPWOM_4965_WEGUWATOWY_BAND_24_HT40_CHANNEWS,
		EEPWOM_4965_WEGUWATOWY_BAND_52_HT40_CHANNEWS
	},

};

/* Moduwe fiwmwawe */
MODUWE_FIWMWAWE(IW4965_MODUWE_FIWMWAWE(IW4965_UCODE_API_MAX));
