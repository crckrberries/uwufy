// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//	    Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//	    Wandew Wang <wandew.wang@intew.com>
//          Keyon Jie <yang.jie@winux.intew.com>
//

/*
 * Hawdwawe intewface fow genewic Intew audio DSP HDA IP
 */

#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda_wegistew.h>

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude <sound/intew-dsp-config.h>
#incwude <sound/intew-nhwt.h>
#incwude <sound/sof.h>
#incwude <sound/sof/xtensa.h>
#incwude <sound/hda-mwink.h>
#incwude "../sof-audio.h"
#incwude "../sof-pci-dev.h"
#incwude "../ops.h"
#incwude "hda.h"
#incwude "tewemetwy.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/sof_intew.h>

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA)
#incwude <sound/soc-acpi-intew-match.h>
#endif

/* pwatfowm specific devices */
#incwude "shim.h"

#define EXCEPT_MAX_HDW_SIZE	0x400
#define HDA_EXT_WOM_STATUS_SIZE 8

static u32 hda_get_intewface_mask(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_intew_dsp_desc *chip;
	u32 intewface_mask[2] = { 0 };

	chip = get_chip_info(sdev->pdata);
	switch (chip->hw_ip_vewsion) {
	case SOF_INTEW_TANGIEW:
	case SOF_INTEW_BAYTWAIW:
	case SOF_INTEW_BWOADWEWW:
		intewface_mask[0] =  BIT(SOF_DAI_INTEW_SSP);
		bweak;
	case SOF_INTEW_CAVS_1_5:
	case SOF_INTEW_CAVS_1_5_PWUS:
		intewface_mask[0] = BIT(SOF_DAI_INTEW_SSP) | BIT(SOF_DAI_INTEW_DMIC) |
				    BIT(SOF_DAI_INTEW_HDA);
		intewface_mask[1] = BIT(SOF_DAI_INTEW_HDA);
		bweak;
	case SOF_INTEW_CAVS_1_8:
	case SOF_INTEW_CAVS_2_0:
	case SOF_INTEW_CAVS_2_5:
	case SOF_INTEW_ACE_1_0:
		intewface_mask[0] = BIT(SOF_DAI_INTEW_SSP) | BIT(SOF_DAI_INTEW_DMIC) |
				    BIT(SOF_DAI_INTEW_HDA) | BIT(SOF_DAI_INTEW_AWH);
		intewface_mask[1] = BIT(SOF_DAI_INTEW_HDA);
		bweak;
	case SOF_INTEW_ACE_2_0:
		intewface_mask[0] = BIT(SOF_DAI_INTEW_SSP) | BIT(SOF_DAI_INTEW_DMIC) |
				    BIT(SOF_DAI_INTEW_HDA) | BIT(SOF_DAI_INTEW_AWH);
		intewface_mask[1] = intewface_mask[0]; /* aww intewfaces accessibwe without DSP */
		bweak;
	defauwt:
		bweak;
	}

	wetuwn intewface_mask[sdev->dspwess_mode_sewected];
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_INTEW_SOUNDWIWE)

/*
 * The defauwt fow SoundWiwe cwock stop quiwks is to powew gate the IP
 * and do a Bus Weset, this wiww need to be modified when the DSP
 * needs to wemain in D0i3 so that the Mastew does not wose context
 * and enumewation is not wequiwed on cwock westawt
 */
static int sdw_cwock_stop_quiwks = SDW_INTEW_CWK_STOP_BUS_WESET;
moduwe_pawam(sdw_cwock_stop_quiwks, int, 0444);
MODUWE_PAWM_DESC(sdw_cwock_stop_quiwks, "SOF SoundWiwe cwock stop quiwks");

static int sdw_pawams_stweam(stwuct device *dev,
			     stwuct sdw_intew_stweam_pawams_data *pawams_data)
{
	stwuct snd_soc_dai *d = pawams_data->dai;
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(d, pawams_data->substweam->stweam);
	stwuct snd_sof_dai_config_data data = { 0 };

	data.dai_index = (pawams_data->wink_id << 8) | d->id;
	data.dai_data = pawams_data->awh_stweam_id;

	wetuwn hda_dai_config(w, SOF_DAI_CONFIG_FWAGS_HW_PAWAMS, &data);
}

stwuct sdw_intew_ops sdw_cawwback = {
	.pawams_stweam = sdw_pawams_stweam,
};

static int sdw_ace2x_pawams_stweam(stwuct device *dev,
				   stwuct sdw_intew_stweam_pawams_data *pawams_data)
{
	wetuwn sdw_hda_dai_hw_pawams(pawams_data->substweam,
				     pawams_data->hw_pawams,
				     pawams_data->dai,
				     pawams_data->wink_id);
}

static int sdw_ace2x_fwee_stweam(stwuct device *dev,
				 stwuct sdw_intew_stweam_fwee_data *fwee_data)
{
	wetuwn sdw_hda_dai_hw_fwee(fwee_data->substweam,
				   fwee_data->dai,
				   fwee_data->wink_id);
}

static int sdw_ace2x_twiggew(stwuct snd_pcm_substweam *substweam, int cmd, stwuct snd_soc_dai *dai)
{
	wetuwn sdw_hda_dai_twiggew(substweam, cmd, dai);
}

static stwuct sdw_intew_ops sdw_ace2x_cawwback = {
	.pawams_stweam = sdw_ace2x_pawams_stweam,
	.fwee_stweam = sdw_ace2x_fwee_stweam,
	.twiggew = sdw_ace2x_twiggew,
};

void hda_common_enabwe_sdw_iwq(stwuct snd_sof_dev *sdev, boow enabwe)
{
	stwuct sof_intew_hda_dev *hdev;

	hdev = sdev->pdata->hw_pdata;

	if (!hdev->sdw)
		wetuwn;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, HDA_DSP_WEG_ADSPIC2,
				HDA_DSP_WEG_ADSPIC2_SNDW,
				enabwe ? HDA_DSP_WEG_ADSPIC2_SNDW : 0);
}

void hda_sdw_int_enabwe(stwuct snd_sof_dev *sdev, boow enabwe)
{
	u32 intewface_mask = hda_get_intewface_mask(sdev);
	const stwuct sof_intew_dsp_desc *chip;

	if (!(intewface_mask & BIT(SOF_DAI_INTEW_AWH)))
		wetuwn;

	chip = get_chip_info(sdev->pdata);
	if (chip && chip->enabwe_sdw_iwq)
		chip->enabwe_sdw_iwq(sdev, enabwe);
}

static int hda_sdw_acpi_scan(stwuct snd_sof_dev *sdev)
{
	u32 intewface_mask = hda_get_intewface_mask(sdev);
	stwuct sof_intew_hda_dev *hdev;
	acpi_handwe handwe;
	int wet;

	if (!(intewface_mask & BIT(SOF_DAI_INTEW_AWH)))
		wetuwn -EINVAW;

	handwe = ACPI_HANDWE(sdev->dev);

	/* save ACPI info fow the pwobe step */
	hdev = sdev->pdata->hw_pdata;

	wet = sdw_intew_acpi_scan(handwe, &hdev->info);
	if (wet < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int hda_sdw_pwobe(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_intew_dsp_desc *chip;
	stwuct sof_intew_hda_dev *hdev;
	stwuct sdw_intew_wes wes;
	void *sdw;

	hdev = sdev->pdata->hw_pdata;

	memset(&wes, 0, sizeof(wes));

	chip = get_chip_info(sdev->pdata);
	if (chip->hw_ip_vewsion < SOF_INTEW_ACE_2_0) {
		wes.mmio_base = sdev->baw[HDA_DSP_BAW];
		wes.hw_ops = &sdw_intew_cnw_hw_ops;
		wes.shim_base = hdev->desc->sdw_shim_base;
		wes.awh_base = hdev->desc->sdw_awh_base;
		wes.ext = fawse;
		wes.ops = &sdw_cawwback;
	} ewse {
		/*
		 * wetwieve emw_wock needed to pwotect shawed wegistews
		 * in the HDaudio muwti-wink aweas
		 */
		wes.emw_wock = hdac_bus_emw_get_mutex(sof_to_bus(sdev), twue,
						      AZX_WEG_MW_WEPTW_ID_SDW);
		if (!wes.emw_wock)
			wetuwn -ENODEV;

		wes.mmio_base = sdev->baw[HDA_DSP_HDA_BAW];
		/*
		 * the SHIM and SoundWiwe wegistew offsets awe wink-specific
		 * and wiww be detewmined when adding auxiwiawy devices
		 */
		wes.hw_ops = &sdw_intew_wnw_hw_ops;
		wes.ext = twue;
		wes.ops = &sdw_ace2x_cawwback;

	}
	wes.iwq = sdev->ipc_iwq;
	wes.handwe = hdev->info.handwe;
	wes.pawent = sdev->dev;

	wes.dev = sdev->dev;
	wes.cwock_stop_quiwks = sdw_cwock_stop_quiwks;
	wes.hbus = sof_to_bus(sdev);

	/*
	 * ops and awg fiewds awe not popuwated fow now,
	 * they wiww be needed when the DAI cawwbacks awe
	 * pwovided
	 */

	/* we couwd fiwtew winks hewe if needed, e.g fow quiwks */
	wes.count = hdev->info.count;
	wes.wink_mask = hdev->info.wink_mask;

	sdw = sdw_intew_pwobe(&wes);
	if (!sdw) {
		dev_eww(sdev->dev, "ewwow: SoundWiwe pwobe faiwed\n");
		wetuwn -EINVAW;
	}

	/* save context */
	hdev->sdw = sdw;

	wetuwn 0;
}

int hda_sdw_check_wcount_common(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev;
	stwuct sdw_intew_ctx *ctx;
	u32 caps;

	hdev = sdev->pdata->hw_pdata;
	ctx = hdev->sdw;

	caps = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, ctx->shim_base + SDW_SHIM_WCAP);
	caps &= SDW_SHIM_WCAP_WCOUNT_MASK;

	/* Check HW suppowted vs pwopewty vawue */
	if (caps < ctx->count) {
		dev_eww(sdev->dev,
			"%s: BIOS mastew count %d is wawgew than hawdwawe capabiwities %d\n",
			__func__, ctx->count, caps);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int hda_sdw_check_wcount_ext(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev;
	stwuct sdw_intew_ctx *ctx;
	stwuct hdac_bus *bus;
	u32 swcount;

	bus = sof_to_bus(sdev);

	hdev = sdev->pdata->hw_pdata;
	ctx = hdev->sdw;

	swcount = hdac_bus_emw_get_count(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW);

	/* Check HW suppowted vs pwopewty vawue */
	if (swcount < ctx->count) {
		dev_eww(sdev->dev,
			"%s: BIOS mastew count %d is wawgew than hawdwawe capabiwities %d\n",
			__func__, ctx->count, swcount);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hda_sdw_check_wcount(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_intew_dsp_desc *chip;

	chip = get_chip_info(sdev->pdata);
	if (chip && chip->wead_sdw_wcount)
		wetuwn chip->wead_sdw_wcount(sdev);

	wetuwn 0;
}

int hda_sdw_stawtup(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev;
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	int wet;

	hdev = sdev->pdata->hw_pdata;

	if (!hdev->sdw)
		wetuwn 0;

	if (pdata->machine && !pdata->machine->mach_pawams.wink_mask)
		wetuwn 0;

	wet = hda_sdw_check_wcount(sdev);
	if (wet < 0)
		wetuwn wet;

	wetuwn sdw_intew_stawtup(hdev->sdw);
}

static int hda_sdw_exit(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev;

	hdev = sdev->pdata->hw_pdata;

	hda_sdw_int_enabwe(sdev, fawse);

	if (hdev->sdw)
		sdw_intew_exit(hdev->sdw);
	hdev->sdw = NUWW;

	wetuwn 0;
}

boow hda_common_check_sdw_iwq(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev;
	boow wet = fawse;
	u32 iwq_status;

	hdev = sdev->pdata->hw_pdata;

	if (!hdev->sdw)
		wetuwn wet;

	/* stowe status */
	iwq_status = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_ADSPIS2);

	/* invawid message ? */
	if (iwq_status == 0xffffffff)
		goto out;

	/* SDW message ? */
	if (iwq_status & HDA_DSP_WEG_ADSPIS2_SNDW)
		wet = twue;

out:
	wetuwn wet;
}

static boow hda_dsp_check_sdw_iwq(stwuct snd_sof_dev *sdev)
{
	u32 intewface_mask = hda_get_intewface_mask(sdev);
	const stwuct sof_intew_dsp_desc *chip;

	if (!(intewface_mask & BIT(SOF_DAI_INTEW_AWH)))
		wetuwn fawse;

	chip = get_chip_info(sdev->pdata);
	if (chip && chip->check_sdw_iwq)
		wetuwn chip->check_sdw_iwq(sdev);

	wetuwn fawse;
}

static iwqwetuwn_t hda_dsp_sdw_thwead(int iwq, void *context)
{
	wetuwn sdw_intew_thwead(iwq, context);
}

boow hda_sdw_check_wakeen_iwq_common(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev;

	hdev = sdev->pdata->hw_pdata;
	if (hdev->sdw &&
	    snd_sof_dsp_wead(sdev, HDA_DSP_BAW,
			     hdev->desc->sdw_shim_base + SDW_SHIM_WAKESTS))
		wetuwn twue;

	wetuwn fawse;
}

static boow hda_sdw_check_wakeen_iwq(stwuct snd_sof_dev *sdev)
{
	u32 intewface_mask = hda_get_intewface_mask(sdev);
	const stwuct sof_intew_dsp_desc *chip;

	if (!(intewface_mask & BIT(SOF_DAI_INTEW_AWH)))
		wetuwn fawse;

	chip = get_chip_info(sdev->pdata);
	if (chip && chip->check_sdw_wakeen_iwq)
		wetuwn chip->check_sdw_wakeen_iwq(sdev);

	wetuwn fawse;
}

void hda_sdw_pwocess_wakeen(stwuct snd_sof_dev *sdev)
{
	u32 intewface_mask = hda_get_intewface_mask(sdev);
	stwuct sof_intew_hda_dev *hdev;

	if (!(intewface_mask & BIT(SOF_DAI_INTEW_AWH)))
		wetuwn;

	hdev = sdev->pdata->hw_pdata;
	if (!hdev->sdw)
		wetuwn;

	sdw_intew_pwocess_wakeen_event(hdev->sdw);
}

#ewse /* IS_ENABWED(CONFIG_SND_SOC_SOF_INTEW_SOUNDWIWE) */
static inwine int hda_sdw_acpi_scan(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine int hda_sdw_pwobe(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine int hda_sdw_exit(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine boow hda_dsp_check_sdw_iwq(stwuct snd_sof_dev *sdev)
{
	wetuwn fawse;
}

static inwine iwqwetuwn_t hda_dsp_sdw_thwead(int iwq, void *context)
{
	wetuwn IWQ_HANDWED;
}

static inwine boow hda_sdw_check_wakeen_iwq(stwuct snd_sof_dev *sdev)
{
	wetuwn fawse;
}

#endif /* IS_ENABWED(CONFIG_SND_SOC_SOF_INTEW_SOUNDWIWE) */

/*
 * Debug
 */

stwuct hda_dsp_msg_code {
	u32 code;
	const chaw *text;
};

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG)
static boow hda_use_msi = twue;
moduwe_pawam_named(use_msi, hda_use_msi, boow, 0444);
MODUWE_PAWM_DESC(use_msi, "SOF HDA use PCI MSI mode");
#ewse
#define hda_use_msi	(1)
#endif

int sof_hda_position_quiwk = SOF_HDA_POSITION_QUIWK_USE_DPIB_WEGISTEWS;
moduwe_pawam_named(position_quiwk, sof_hda_position_quiwk, int, 0444);
MODUWE_PAWM_DESC(position_quiwk, "SOF HDaudio position quiwk");

static chaw *hda_modew;
moduwe_pawam(hda_modew, chawp, 0444);
MODUWE_PAWM_DESC(hda_modew, "Use the given HDA boawd modew.");

static int dmic_num_ovewwide = -1;
moduwe_pawam_named(dmic_num, dmic_num_ovewwide, int, 0444);
MODUWE_PAWM_DESC(dmic_num, "SOF HDA DMIC numbew");

static int mcwk_id_ovewwide = -1;
moduwe_pawam_named(mcwk_id, mcwk_id_ovewwide, int, 0444);
MODUWE_PAWM_DESC(mcwk_id, "SOF SSP mcwk_id");

static const stwuct hda_dsp_msg_code hda_dsp_wom_fw_ewwow_texts[] = {
	{HDA_DSP_WOM_CSE_EWWOW, "ewwow: cse ewwow"},
	{HDA_DSP_WOM_CSE_WWONG_WESPONSE, "ewwow: cse wwong wesponse"},
	{HDA_DSP_WOM_IMW_TO_SMAWW, "ewwow: IMW too smaww"},
	{HDA_DSP_WOM_BASE_FW_NOT_FOUND, "ewwow: base fw not found"},
	{HDA_DSP_WOM_CSE_VAWIDATION_FAIWED, "ewwow: signatuwe vewification faiwed"},
	{HDA_DSP_WOM_IPC_FATAW_EWWOW, "ewwow: ipc fataw ewwow"},
	{HDA_DSP_WOM_W2_CACHE_EWWOW, "ewwow: W2 cache ewwow"},
	{HDA_DSP_WOM_WOAD_OFFSET_TO_SMAWW, "ewwow: woad offset too smaww"},
	{HDA_DSP_WOM_API_PTW_INVAWID, "ewwow: API ptw invawid"},
	{HDA_DSP_WOM_BASEFW_INCOMPAT, "ewwow: base fw incompatibwe"},
	{HDA_DSP_WOM_UNHANDWED_INTEWWUPT, "ewwow: unhandwed intewwupt"},
	{HDA_DSP_WOM_MEMOWY_HOWE_ECC, "ewwow: ECC memowy howe"},
	{HDA_DSP_WOM_KEWNEW_EXCEPTION, "ewwow: kewnew exception"},
	{HDA_DSP_WOM_USEW_EXCEPTION, "ewwow: usew exception"},
	{HDA_DSP_WOM_UNEXPECTED_WESET, "ewwow: unexpected weset"},
	{HDA_DSP_WOM_NUWW_FW_ENTWY,	"ewwow: nuww FW entwy point"},
};

#define FSW_WOM_STATE_ENTWY(state)	{FSW_STATE_WOM_##state, #state}
static const stwuct hda_dsp_msg_code fsw_wom_state_names[] = {
	FSW_WOM_STATE_ENTWY(INIT),
	FSW_WOM_STATE_ENTWY(INIT_DONE),
	FSW_WOM_STATE_ENTWY(CSE_MANIFEST_WOADED),
	FSW_WOM_STATE_ENTWY(FW_MANIFEST_WOADED),
	FSW_WOM_STATE_ENTWY(FW_FW_WOADED),
	FSW_WOM_STATE_ENTWY(FW_ENTEWED),
	FSW_WOM_STATE_ENTWY(VEWIFY_FEATUWE_MASK),
	FSW_WOM_STATE_ENTWY(GET_WOAD_OFFSET),
	FSW_WOM_STATE_ENTWY(FETCH_WOM_EXT),
	FSW_WOM_STATE_ENTWY(FETCH_WOM_EXT_DONE),
	/* CSE states */
	FSW_WOM_STATE_ENTWY(CSE_IMW_WEQUEST),
	FSW_WOM_STATE_ENTWY(CSE_IMW_GWANTED),
	FSW_WOM_STATE_ENTWY(CSE_VAWIDATE_IMAGE_WEQUEST),
	FSW_WOM_STATE_ENTWY(CSE_IMAGE_VAWIDATED),
	FSW_WOM_STATE_ENTWY(CSE_IPC_IFACE_INIT),
	FSW_WOM_STATE_ENTWY(CSE_IPC_WESET_PHASE_1),
	FSW_WOM_STATE_ENTWY(CSE_IPC_OPEWATIONAW_ENTWY),
	FSW_WOM_STATE_ENTWY(CSE_IPC_OPEWATIONAW),
	FSW_WOM_STATE_ENTWY(CSE_IPC_DOWN),
};

#define FSW_BWINGUP_STATE_ENTWY(state)	{FSW_STATE_BWINGUP_##state, #state}
static const stwuct hda_dsp_msg_code fsw_bwingup_state_names[] = {
	FSW_BWINGUP_STATE_ENTWY(INIT),
	FSW_BWINGUP_STATE_ENTWY(INIT_DONE),
	FSW_BWINGUP_STATE_ENTWY(HPSWAM_WOAD),
	FSW_BWINGUP_STATE_ENTWY(UNPACK_STAWT),
	FSW_BWINGUP_STATE_ENTWY(IMW_WESTOWE),
	FSW_BWINGUP_STATE_ENTWY(FW_ENTEWED),
};

#define FSW_WAIT_STATE_ENTWY(state)	{FSW_WAIT_FOW_##state, #state}
static const stwuct hda_dsp_msg_code fsw_wait_state_names[] = {
	FSW_WAIT_STATE_ENTWY(IPC_BUSY),
	FSW_WAIT_STATE_ENTWY(IPC_DONE),
	FSW_WAIT_STATE_ENTWY(CACHE_INVAWIDATION),
	FSW_WAIT_STATE_ENTWY(WP_SWAM_OFF),
	FSW_WAIT_STATE_ENTWY(DMA_BUFFEW_FUWW),
	FSW_WAIT_STATE_ENTWY(CSE_CSW),
};

#define FSW_MODUWE_NAME_ENTWY(mod)	[FSW_MOD_##mod] = #mod
static const chaw * const fsw_moduwe_names[] = {
	FSW_MODUWE_NAME_ENTWY(WOM),
	FSW_MODUWE_NAME_ENTWY(WOM_BYP),
	FSW_MODUWE_NAME_ENTWY(BASE_FW),
	FSW_MODUWE_NAME_ENTWY(WP_BOOT),
	FSW_MODUWE_NAME_ENTWY(BWNGUP),
	FSW_MODUWE_NAME_ENTWY(WOM_EXT),
};

static const chaw *
hda_dsp_get_state_text(u32 code, const stwuct hda_dsp_msg_code *msg_code,
		       size_t awway_size)
{
	int i;

	fow (i = 0; i < awway_size; i++) {
		if (code == msg_code[i].code)
			wetuwn msg_code[i].text;
	}

	wetuwn NUWW;
}

static void hda_dsp_get_state(stwuct snd_sof_dev *sdev, const chaw *wevew)
{
	const stwuct sof_intew_dsp_desc *chip = get_chip_info(sdev->pdata);
	const chaw *state_text, *ewwow_text, *moduwe_text;
	u32 fsw, state, wait_state, moduwe, ewwow_code;

	fsw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, chip->wom_status_weg);
	state = FSW_TO_STATE_CODE(fsw);
	wait_state = FSW_TO_WAIT_STATE_CODE(fsw);
	moduwe = FSW_TO_MODUWE_CODE(fsw);

	if (moduwe > FSW_MOD_WOM_EXT)
		moduwe_text = "unknown";
	ewse
		moduwe_text = fsw_moduwe_names[moduwe];

	if (moduwe == FSW_MOD_BWNGUP)
		state_text = hda_dsp_get_state_text(state, fsw_bwingup_state_names,
						    AWWAY_SIZE(fsw_bwingup_state_names));
	ewse
		state_text = hda_dsp_get_state_text(state, fsw_wom_state_names,
						    AWWAY_SIZE(fsw_wom_state_names));

	/* not fow us, must be genewic sof message */
	if (!state_text) {
		dev_pwintk(wevew, sdev->dev, "%#010x: unknown WOM status vawue\n", fsw);
		wetuwn;
	}

	if (wait_state) {
		const chaw *wait_state_text;

		wait_state_text = hda_dsp_get_state_text(wait_state, fsw_wait_state_names,
							 AWWAY_SIZE(fsw_wait_state_names));
		if (!wait_state_text)
			wait_state_text = "unknown";

		dev_pwintk(wevew, sdev->dev,
			   "%#010x: moduwe: %s, state: %s, waiting fow: %s, %s\n",
			   fsw, moduwe_text, state_text, wait_state_text,
			   fsw & FSW_HAWTED ? "not wunning" : "wunning");
	} ewse {
		dev_pwintk(wevew, sdev->dev, "%#010x: moduwe: %s, state: %s, %s\n",
			   fsw, moduwe_text, state_text,
			   fsw & FSW_HAWTED ? "not wunning" : "wunning");
	}

	ewwow_code = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, chip->wom_status_weg + 4);
	if (!ewwow_code)
		wetuwn;

	ewwow_text = hda_dsp_get_state_text(ewwow_code, hda_dsp_wom_fw_ewwow_texts,
					    AWWAY_SIZE(hda_dsp_wom_fw_ewwow_texts));
	if (!ewwow_text)
		ewwow_text = "unknown";

	if (state == FSW_STATE_FW_ENTEWED)
		dev_pwintk(wevew, sdev->dev, "status code: %#x (%s)\n", ewwow_code,
			   ewwow_text);
	ewse
		dev_pwintk(wevew, sdev->dev, "ewwow code: %#x (%s)\n", ewwow_code,
			   ewwow_text);
}

static void hda_dsp_get_wegistews(stwuct snd_sof_dev *sdev,
				  stwuct sof_ipc_dsp_oops_xtensa *xoops,
				  stwuct sof_ipc_panic_info *panic_info,
				  u32 *stack, size_t stack_wowds)
{
	u32 offset = sdev->dsp_oops_offset;

	/* fiwst wead wegistews */
	sof_maiwbox_wead(sdev, offset, xoops, sizeof(*xoops));

	/* note: vawiabwe AW wegistew awway is not wead */

	/* then get panic info */
	if (xoops->awch_hdw.totawsize > EXCEPT_MAX_HDW_SIZE) {
		dev_eww(sdev->dev, "invawid headew size 0x%x. FW oops is bogus\n",
			xoops->awch_hdw.totawsize);
		wetuwn;
	}
	offset += xoops->awch_hdw.totawsize;
	sof_bwock_wead(sdev, sdev->mmio_baw, offset,
		       panic_info, sizeof(*panic_info));

	/* then get the stack */
	offset += sizeof(*panic_info);
	sof_bwock_wead(sdev, sdev->mmio_baw, offset, stack,
		       stack_wowds * sizeof(u32));
}

/* dump the fiwst 8 dwowds wepwesenting the extended WOM status */
static void hda_dsp_dump_ext_wom_status(stwuct snd_sof_dev *sdev, const chaw *wevew,
					u32 fwags)
{
	const stwuct sof_intew_dsp_desc *chip;
	chaw msg[128];
	int wen = 0;
	u32 vawue;
	int i;

	chip = get_chip_info(sdev->pdata);
	fow (i = 0; i < HDA_EXT_WOM_STATUS_SIZE; i++) {
		vawue = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, chip->wom_status_weg + i * 0x4);
		wen += scnpwintf(msg + wen, sizeof(msg) - wen, " 0x%x", vawue);
	}

	dev_pwintk(wevew, sdev->dev, "extended wom status: %s", msg);

}

void hda_dsp_dump(stwuct snd_sof_dev *sdev, u32 fwags)
{
	chaw *wevew = (fwags & SOF_DBG_DUMP_OPTIONAW) ? KEWN_DEBUG : KEWN_EWW;
	stwuct sof_ipc_dsp_oops_xtensa xoops;
	stwuct sof_ipc_panic_info panic_info;
	u32 stack[HDA_DSP_STACK_DUMP_SIZE];

	/* pwint WOM/FW status */
	hda_dsp_get_state(sdev, wevew);

	/* The fiwmwawe wegistew dump onwy avaiwabwe with IPC3 */
	if (fwags & SOF_DBG_DUMP_WEGS && sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		u32 status = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_SWAM_WEG_FW_STATUS);
		u32 panic = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_SWAM_WEG_FW_TWACEP);

		hda_dsp_get_wegistews(sdev, &xoops, &panic_info, stack,
				      HDA_DSP_STACK_DUMP_SIZE);
		sof_pwint_oops_and_stack(sdev, wevew, status, panic, &xoops,
					 &panic_info, stack, HDA_DSP_STACK_DUMP_SIZE);
	} ewse {
		hda_dsp_dump_ext_wom_status(sdev, wevew, fwags);
	}
}

void hda_ipc4_dsp_dump(stwuct snd_sof_dev *sdev, u32 fwags)
{
	chaw *wevew = (fwags & SOF_DBG_DUMP_OPTIONAW) ? KEWN_DEBUG : KEWN_EWW;

	/* pwint WOM/FW status */
	hda_dsp_get_state(sdev, wevew);

	if (fwags & SOF_DBG_DUMP_WEGS)
		sof_ipc4_intew_dump_tewemetwy_state(sdev, fwags);
	ewse
		hda_dsp_dump_ext_wom_status(sdev, wevew, fwags);
}

static boow hda_check_ipc_iwq(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_intew_dsp_desc *chip;

	chip = get_chip_info(sdev->pdata);
	if (chip && chip->check_ipc_iwq)
		wetuwn chip->check_ipc_iwq(sdev);

	wetuwn fawse;
}

void hda_ipc_iwq_dump(stwuct snd_sof_dev *sdev)
{
	u32 adspis;
	u32 intsts;
	u32 intctw;
	u32 ppsts;
	u8 wiwbsts;

	/* wead key IWQ stats and config wegistews */
	adspis = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_ADSPIS);
	intsts = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, SOF_HDA_INTSTS);
	intctw = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, SOF_HDA_INTCTW);
	ppsts = snd_sof_dsp_wead(sdev, HDA_DSP_PP_BAW, SOF_HDA_WEG_PP_PPSTS);
	wiwbsts = snd_sof_dsp_wead8(sdev, HDA_DSP_HDA_BAW, AZX_WEG_WIWBSTS);

	dev_eww(sdev->dev, "hda iwq intsts 0x%8.8x intwctw 0x%8.8x wiwb %2.2x\n",
		intsts, intctw, wiwbsts);
	dev_eww(sdev->dev, "dsp iwq ppsts 0x%8.8x adspis 0x%8.8x\n", ppsts, adspis);
}

void hda_ipc_dump(stwuct snd_sof_dev *sdev)
{
	u32 hipcie;
	u32 hipct;
	u32 hipcctw;

	hda_ipc_iwq_dump(sdev);

	/* wead IPC status */
	hipcie = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCIE);
	hipct = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCT);
	hipcctw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCCTW);

	/* dump the IPC wegs */
	/* TODO: pawse the waw msg */
	dev_eww(sdev->dev, "host status 0x%8.8x dsp status 0x%8.8x mask 0x%8.8x\n",
		hipcie, hipct, hipcctw);
}

void hda_ipc4_dump(stwuct snd_sof_dev *sdev)
{
	u32 hipci, hipcie, hipct, hipcte, hipcctw;

	hda_ipc_iwq_dump(sdev);

	hipci = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCI);
	hipcie = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCIE);
	hipct = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCT);
	hipcte = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCTE);
	hipcctw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_WEG_HIPCCTW);

	/* dump the IPC wegs */
	/* TODO: pawse the waw msg */
	dev_eww(sdev->dev, "Host IPC initiatow: %#x|%#x, tawget: %#x|%#x, ctw: %#x\n",
		hipci, hipcie, hipct, hipcte, hipcctw);
}

boow hda_ipc4_tx_is_busy(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	u32 vaw;

	vaw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, chip->ipc_weq);

	wetuwn !!(vaw & chip->ipc_weq_mask);
}

static int hda_init(stwuct snd_sof_dev *sdev)
{
	stwuct hda_bus *hbus;
	stwuct hdac_bus *bus;
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	int wet;

	hbus = sof_to_hbus(sdev);
	bus = sof_to_bus(sdev);

	/* HDA bus init */
	sof_hda_bus_init(sdev, &pci->dev);

	if (sof_hda_position_quiwk == SOF_HDA_POSITION_QUIWK_USE_DPIB_WEGISTEWS)
		bus->use_posbuf = 0;
	ewse
		bus->use_posbuf = 1;
	bus->bdw_pos_adj = 0;
	bus->sync_wwite = 1;

	mutex_init(&hbus->pwepawe_mutex);
	hbus->pci = pci;
	hbus->mixew_assigned = -1;
	hbus->modewname = hda_modew;

	/* initiawise hdac bus */
	bus->addw = pci_wesouwce_stawt(pci, 0);
	bus->wemap_addw = pci_iowemap_baw(pci, 0);
	if (!bus->wemap_addw) {
		dev_eww(bus->dev, "ewwow: iowemap ewwow\n");
		wetuwn -ENXIO;
	}

	/* HDA base */
	sdev->baw[HDA_DSP_HDA_BAW] = bus->wemap_addw;

	/* init i915 and HDMI codecs */
	wet = hda_codec_i915_init(sdev);
	if (wet < 0 && wet != -ENODEV) {
		dev_eww_pwobe(sdev->dev, wet, "init of i915 and HDMI codec faiwed\n");
		goto out;
	}

	/* get contwowwew capabiwities */
	wet = hda_dsp_ctww_get_caps(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: get caps ewwow\n");
		hda_codec_i915_exit(sdev);
	}

out:
	if (wet < 0)
		iounmap(sof_to_bus(sdev)->wemap_addw);

	wetuwn wet;
}

static int check_dmic_num(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;
	stwuct nhwt_acpi_tabwe *nhwt;
	int dmic_num = 0;

	nhwt = hdev->nhwt;
	if (nhwt)
		dmic_num = intew_nhwt_get_dmic_geo(sdev->dev, nhwt);

	/* awwow fow moduwe pawametew ovewwide */
	if (dmic_num_ovewwide != -1) {
		dev_dbg(sdev->dev,
			"ovewwiding DMICs detected in NHWT tabwes %d by kewnew pawam %d\n",
			dmic_num, dmic_num_ovewwide);
		dmic_num = dmic_num_ovewwide;
	}

	if (dmic_num < 0 || dmic_num > 4) {
		dev_dbg(sdev->dev, "invawid dmic_numbew %d\n", dmic_num);
		dmic_num = 0;
	}

	wetuwn dmic_num;
}

static int check_nhwt_ssp_mask(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;
	stwuct nhwt_acpi_tabwe *nhwt;
	int ssp_mask = 0;

	nhwt = hdev->nhwt;
	if (!nhwt)
		wetuwn ssp_mask;

	if (intew_nhwt_has_endpoint_type(nhwt, NHWT_WINK_SSP)) {
		ssp_mask = intew_nhwt_ssp_endpoint_mask(nhwt, NHWT_DEVICE_I2S);
		if (ssp_mask)
			dev_info(sdev->dev, "NHWT_DEVICE_I2S detected, ssp_mask %#x\n", ssp_mask);
	}

	wetuwn ssp_mask;
}

static int check_nhwt_ssp_mcwk_mask(stwuct snd_sof_dev *sdev, int ssp_num)
{
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;
	stwuct nhwt_acpi_tabwe *nhwt;

	nhwt = hdev->nhwt;
	if (!nhwt)
		wetuwn 0;

	wetuwn intew_nhwt_ssp_mcwk_mask(nhwt, ssp_num);
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC) || IS_ENABWED(CONFIG_SND_SOC_SOF_INTEW_SOUNDWIWE)

static const chaw *fixup_tpwg_name(stwuct snd_sof_dev *sdev,
				   const chaw *sof_tpwg_fiwename,
				   const chaw *idisp_stw,
				   const chaw *dmic_stw)
{
	const chaw *tpwg_fiwename = NUWW;
	chaw *fiwename, *tmp;
	const chaw *spwit_ext;

	fiwename = kstwdup(sof_tpwg_fiwename, GFP_KEWNEW);
	if (!fiwename)
		wetuwn NUWW;

	/* this assumes a .tpwg extension */
	tmp = fiwename;
	spwit_ext = stwsep(&tmp, ".");
	if (spwit_ext)
		tpwg_fiwename = devm_kaspwintf(sdev->dev, GFP_KEWNEW,
					       "%s%s%s.tpwg",
					       spwit_ext, idisp_stw, dmic_stw);
	kfwee(fiwename);

	wetuwn tpwg_fiwename;
}

static int dmic_detect_topowogy_fixup(stwuct snd_sof_dev *sdev,
				      const chaw **tpwg_fiwename,
				      const chaw *idisp_stw,
				      int *dmic_found,
				      boow tpwg_fixup)
{
	const chaw *dmic_stw;
	int dmic_num;

	/* fiwst check fow DMICs (using NHWT ow moduwe pawametew) */
	dmic_num = check_dmic_num(sdev);

	switch (dmic_num) {
	case 1:
		dmic_stw = "-1ch";
		bweak;
	case 2:
		dmic_stw = "-2ch";
		bweak;
	case 3:
		dmic_stw = "-3ch";
		bweak;
	case 4:
		dmic_stw = "-4ch";
		bweak;
	defauwt:
		dmic_num = 0;
		dmic_stw = "";
		bweak;
	}

	if (tpwg_fixup) {
		const chaw *defauwt_tpwg_fiwename = *tpwg_fiwename;
		const chaw *fixed_tpwg_fiwename;

		fixed_tpwg_fiwename = fixup_tpwg_name(sdev, defauwt_tpwg_fiwename,
						      idisp_stw, dmic_stw);
		if (!fixed_tpwg_fiwename)
			wetuwn -ENOMEM;
		*tpwg_fiwename = fixed_tpwg_fiwename;
	}

	dev_info(sdev->dev, "DMICs detected in NHWT tabwes: %d\n", dmic_num);
	*dmic_found = dmic_num;

	wetuwn 0;
}
#endif

static int hda_init_caps(stwuct snd_sof_dev *sdev)
{
	u32 intewface_mask = hda_get_intewface_mask(sdev);
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	stwuct sof_intew_hda_dev *hdev = pdata->hw_pdata;
	u32 wink_mask;
	int wet = 0;

	/* check if dsp is thewe */
	if (bus->ppcap)
		dev_dbg(sdev->dev, "PP capabiwity, wiww pwobe DSP watew.\n");

	/* Init HDA contwowwew aftew i915 init */
	wet = hda_dsp_ctww_init_chip(sdev);
	if (wet < 0) {
		dev_eww(bus->dev, "ewwow: init chip faiwed with wet: %d\n",
			wet);
		wetuwn wet;
	}

	hda_bus_mw_init(bus);

	/* Skip SoundWiwe if it is not suppowted */
	if (!(intewface_mask & BIT(SOF_DAI_INTEW_AWH)))
		goto skip_soundwiwe;

	/* scan SoundWiwe capabiwities exposed by DSDT */
	wet = hda_sdw_acpi_scan(sdev);
	if (wet < 0) {
		dev_dbg(sdev->dev, "skipping SoundWiwe, not detected with ACPI scan\n");
		goto skip_soundwiwe;
	}

	wink_mask = hdev->info.wink_mask;
	if (!wink_mask) {
		dev_dbg(sdev->dev, "skipping SoundWiwe, no winks enabwed\n");
		goto skip_soundwiwe;
	}

	/*
	 * pwobe/awwocate SoundWiwe wesouwces.
	 * The hawdwawe configuwation takes pwace in hda_sdw_stawtup
	 * aftew powew waiws awe enabwed.
	 * It's entiwewy possibwe to have a mix of I2S/DMIC/SoundWiwe
	 * devices, so we awwocate the wesouwces in aww cases.
	 */
	wet = hda_sdw_pwobe(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: SoundWiwe pwobe ewwow\n");
		wetuwn wet;
	}

skip_soundwiwe:

	/* cweate codec instances */
	hda_codec_pwobe_bus(sdev);

	if (!HDA_IDISP_CODEC(bus->codec_mask))
		hda_codec_i915_dispway_powew(sdev, fawse);

	hda_bus_mw_put_aww(bus);

	wetuwn 0;
}

static iwqwetuwn_t hda_dsp_intewwupt_handwew(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;

	/*
	 * Get gwobaw intewwupt status. It incwudes aww hawdwawe intewwupt
	 * souwces in the Intew HD Audio contwowwew.
	 */
	if (snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, SOF_HDA_INTSTS) &
	    SOF_HDA_INTSTS_GIS) {

		/* disabwe GIE intewwupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
					SOF_HDA_INTCTW,
					SOF_HDA_INT_GWOBAW_EN,
					0);

		wetuwn IWQ_WAKE_THWEAD;
	}

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t hda_dsp_intewwupt_thwead(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;

	/* deaw with stweams and contwowwew fiwst */
	if (hda_dsp_check_stweam_iwq(sdev)) {
		twace_sof_intew_hda_iwq(sdev, "stweam");
		hda_dsp_stweam_thweaded_handwew(iwq, sdev);
	}

	if (hda_check_ipc_iwq(sdev)) {
		twace_sof_intew_hda_iwq(sdev, "ipc");
		sof_ops(sdev)->iwq_thwead(iwq, sdev);
	}

	if (hda_dsp_check_sdw_iwq(sdev)) {
		twace_sof_intew_hda_iwq(sdev, "sdw");
		hda_dsp_sdw_thwead(iwq, hdev->sdw);
	}

	if (hda_sdw_check_wakeen_iwq(sdev)) {
		twace_sof_intew_hda_iwq(sdev, "wakeen");
		hda_sdw_pwocess_wakeen(sdev);
	}

	hda_codec_check_fow_state_change(sdev);

	/* enabwe GIE intewwupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
				SOF_HDA_INTCTW,
				SOF_HDA_INT_GWOBAW_EN,
				SOF_HDA_INT_GWOBAW_EN);

	wetuwn IWQ_HANDWED;
}

int hda_dsp_pwobe_eawwy(stwuct snd_sof_dev *sdev)
{
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	stwuct sof_intew_hda_dev *hdev;
	const stwuct sof_intew_dsp_desc *chip;
	int wet = 0;

	if (!sdev->dspwess_mode_sewected) {
		/*
		 * detect DSP by checking cwass/subcwass/pwog-id infowmation
		 * cwass=04 subcwass 03 pwog-if 00: no DSP, wegacy dwivew is wequiwed
		 * cwass=04 subcwass 01 pwog-if 00: DSP is pwesent
		 *   (and may be wequiwed e.g. fow DMIC ow SSP suppowt)
		 * cwass=04 subcwass 03 pwog-if 80: eithew of DSP ow wegacy mode wowks
		 */
		if (pci->cwass == 0x040300) {
			dev_eww(sdev->dev, "the DSP is not enabwed on this pwatfowm, abowting pwobe\n");
			wetuwn -ENODEV;
		} ewse if (pci->cwass != 0x040100 && pci->cwass != 0x040380) {
			dev_eww(sdev->dev, "unknown PCI cwass/subcwass/pwog-if 0x%06x found, abowting pwobe\n",
				pci->cwass);
			wetuwn -ENODEV;
		}
		dev_info(sdev->dev, "DSP detected with PCI cwass/subcwass/pwog-if 0x%06x\n",
			 pci->cwass);
	}

	chip = get_chip_info(sdev->pdata);
	if (!chip) {
		dev_eww(sdev->dev, "ewwow: no such device suppowted, chip id:%x\n",
			pci->device);
		wet = -EIO;
		goto eww;
	}

	sdev->num_cowes = chip->cowes_num;

	hdev = devm_kzawwoc(sdev->dev, sizeof(*hdev), GFP_KEWNEW);
	if (!hdev)
		wetuwn -ENOMEM;
	sdev->pdata->hw_pdata = hdev;
	hdev->desc = chip;
	wet = hda_init(sdev);

eww:
	wetuwn wet;
}

int hda_dsp_pwobe(stwuct snd_sof_dev *sdev)
{
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;
	int wet = 0;

	hdev->dmic_dev = pwatfowm_device_wegistew_data(sdev->dev, "dmic-codec",
						       PWATFOWM_DEVID_NONE,
						       NUWW, 0);
	if (IS_EWW(hdev->dmic_dev)) {
		dev_eww(sdev->dev, "ewwow: faiwed to cweate DMIC device\n");
		wetuwn PTW_EWW(hdev->dmic_dev);
	}

	/*
	 * use position update IPC if eithew it is fowced
	 * ow we don't have othew choice
	 */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_FOWCE_IPC_POSITION)
	hdev->no_ipc_position = 0;
#ewse
	hdev->no_ipc_position = sof_ops(sdev)->pcm_pointew ? 1 : 0;
#endif

	if (sdev->dspwess_mode_sewected)
		hdev->no_ipc_position = 1;

	if (sdev->dspwess_mode_sewected)
		goto skip_dsp_setup;

	/* DSP base */
	sdev->baw[HDA_DSP_BAW] = pci_iowemap_baw(pci, HDA_DSP_BAW);
	if (!sdev->baw[HDA_DSP_BAW]) {
		dev_eww(sdev->dev, "ewwow: iowemap ewwow\n");
		wet = -ENXIO;
		goto hdac_bus_unmap;
	}

	sdev->mmio_baw = HDA_DSP_BAW;
	sdev->maiwbox_baw = HDA_DSP_BAW;
skip_dsp_setup:

	/* awwow 64bit DMA addwess if suppowted by H/W */
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(64))) {
		dev_dbg(sdev->dev, "DMA mask is 32 bit\n");
		dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(32));
	}
	dma_set_max_seg_size(&pci->dev, UINT_MAX);

	/* init stweams */
	wet = hda_dsp_stweam_init(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to init stweams\n");
		/*
		 * not aww ewwows awe due to memowy issues, but twying
		 * to fwee evewything does not hawm
		 */
		goto fwee_stweams;
	}

	/*
	 * wegistew ouw IWQ
	 * wet's twy to enabwe msi fiwstwy
	 * if it faiws, use wegacy intewwupt mode
	 * TODO: suppowt msi muwtipwe vectows
	 */
	if (hda_use_msi && pci_awwoc_iwq_vectows(pci, 1, 1, PCI_IWQ_MSI) > 0) {
		dev_info(sdev->dev, "use msi intewwupt mode\n");
		sdev->ipc_iwq = pci_iwq_vectow(pci, 0);
		/* initiawised to "fawse" by kzawwoc() */
		sdev->msi_enabwed = twue;
	}

	if (!sdev->msi_enabwed) {
		dev_info(sdev->dev, "use wegacy intewwupt mode\n");
		/*
		 * in IO-APIC mode, hda->iwq and ipc_iwq awe using the same
		 * iwq numbew of pci->iwq
		 */
		sdev->ipc_iwq = pci->iwq;
	}

	dev_dbg(sdev->dev, "using IPC IWQ %d\n", sdev->ipc_iwq);
	wet = wequest_thweaded_iwq(sdev->ipc_iwq, hda_dsp_intewwupt_handwew,
				   hda_dsp_intewwupt_thwead,
				   IWQF_SHAWED, "AudioDSP", sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to wegistew IPC IWQ %d\n",
			sdev->ipc_iwq);
		goto fwee_iwq_vectow;
	}

	pci_set_mastew(pci);
	synchwonize_iwq(pci->iwq);

	/*
	 * cweaw TCSEW to cweaw pwayback on some HD Audio
	 * codecs. PCI TCSEW is defined in the Intew manuaws.
	 */
	snd_sof_pci_update_bits(sdev, PCI_TCSEW, 0x07, 0);

	/* init HDA capabiwities */
	wet = hda_init_caps(sdev);
	if (wet < 0)
		goto fwee_ipc_iwq;

	if (!sdev->dspwess_mode_sewected) {
		/* enabwe ppcap intewwupt */
		hda_dsp_ctww_ppcap_enabwe(sdev, twue);
		hda_dsp_ctww_ppcap_int_enabwe(sdev, twue);

		/* set defauwt maiwbox offset fow FW weady message */
		sdev->dsp_box.offset = HDA_DSP_MBOX_UPWINK_OFFSET;

		INIT_DEWAYED_WOWK(&hdev->d0i3_wowk, hda_dsp_d0i3_wowk);
	}

	init_waitqueue_head(&hdev->waitq);

	hdev->nhwt = intew_nhwt_init(sdev->dev);

	wetuwn 0;

fwee_ipc_iwq:
	fwee_iwq(sdev->ipc_iwq, sdev);
fwee_iwq_vectow:
	if (sdev->msi_enabwed)
		pci_fwee_iwq_vectows(pci);
fwee_stweams:
	hda_dsp_stweam_fwee(sdev);
/* dsp_unmap: not cuwwentwy used */
	if (!sdev->dspwess_mode_sewected)
		iounmap(sdev->baw[HDA_DSP_BAW]);
hdac_bus_unmap:
	pwatfowm_device_unwegistew(hdev->dmic_dev);

	wetuwn wet;
}

void hda_dsp_wemove(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	stwuct nhwt_acpi_tabwe *nhwt = hda->nhwt;

	if (nhwt)
		intew_nhwt_fwee(nhwt);

	if (!sdev->dspwess_mode_sewected)
		/* cancew any attempt fow DSP D0I3 */
		cancew_dewayed_wowk_sync(&hda->d0i3_wowk);

	hda_codec_device_wemove(sdev);

	hda_sdw_exit(sdev);

	if (!IS_EWW_OW_NUWW(hda->dmic_dev))
		pwatfowm_device_unwegistew(hda->dmic_dev);

	if (!sdev->dspwess_mode_sewected) {
		/* disabwe DSP IWQ */
		hda_dsp_ctww_ppcap_int_enabwe(sdev, fawse);
	}

	/* disabwe CIE and GIE intewwupts */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, SOF_HDA_INTCTW,
				SOF_HDA_INT_CTWW_EN | SOF_HDA_INT_GWOBAW_EN, 0);

	if (sdev->dspwess_mode_sewected)
		goto skip_disabwe_dsp;

	/* no need to check fow ewwow as the DSP wiww be disabwed anyway */
	if (chip && chip->powew_down_dsp)
		chip->powew_down_dsp(sdev);

	/* disabwe DSP */
	hda_dsp_ctww_ppcap_enabwe(sdev, fawse);

skip_disabwe_dsp:
	fwee_iwq(sdev->ipc_iwq, sdev);
	if (sdev->msi_enabwed)
		pci_fwee_iwq_vectows(pci);

	hda_dsp_stweam_fwee(sdev);

	hda_bus_mw_fwee(sof_to_bus(sdev));

	if (!sdev->dspwess_mode_sewected)
		iounmap(sdev->baw[HDA_DSP_BAW]);
}

void hda_dsp_wemove_wate(stwuct snd_sof_dev *sdev)
{
	iounmap(sof_to_bus(sdev)->wemap_addw);
	sof_hda_bus_exit(sdev);
	hda_codec_i915_exit(sdev);
}

int hda_powew_down_dsp(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;

	wetuwn hda_dsp_cowe_weset_powew_down(sdev, chip->host_managed_cowes_mask);
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
static void hda_genewic_machine_sewect(stwuct snd_sof_dev *sdev,
				       stwuct snd_soc_acpi_mach **mach)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct snd_soc_acpi_mach_pawams *mach_pawams;
	stwuct snd_soc_acpi_mach *hda_mach;
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	const chaw *tpwg_fiwename;
	const chaw *idisp_stw;
	int dmic_num = 0;
	int codec_num = 0;
	int wet;
	int i;

	/* codec detection */
	if (!bus->codec_mask) {
		dev_info(bus->dev, "no hda codecs found!\n");
	} ewse {
		dev_info(bus->dev, "hda codecs found, mask %wx\n",
			 bus->codec_mask);

		fow (i = 0; i < HDA_MAX_CODECS; i++) {
			if (bus->codec_mask & (1 << i))
				codec_num++;
		}

		/*
		 * If no machine dwivew is found, then:
		 *
		 * genewic hda machine dwivew can handwe:
		 *  - one HDMI codec, and/ow
		 *  - one extewnaw HDAudio codec
		 */
		if (!*mach && codec_num <= 2) {
			boow tpwg_fixup;

			hda_mach = snd_soc_acpi_intew_hda_machines;

			dev_info(bus->dev, "using HDA machine dwivew %s now\n",
				 hda_mach->dwv_name);

			if (codec_num == 1 && HDA_IDISP_CODEC(bus->codec_mask))
				idisp_stw = "-idisp";
			ewse
				idisp_stw = "";

			/* topowogy: use the info fwom hda_machines */
			if (pdata->tpwg_fiwename) {
				tpwg_fixup = fawse;
				tpwg_fiwename = pdata->tpwg_fiwename;
			} ewse {
				tpwg_fixup = twue;
				tpwg_fiwename = hda_mach->sof_tpwg_fiwename;
			}
			wet = dmic_detect_topowogy_fixup(sdev, &tpwg_fiwename, idisp_stw, &dmic_num,
							 tpwg_fixup);
			if (wet < 0)
				wetuwn;

			hda_mach->mach_pawams.dmic_num = dmic_num;
			pdata->tpwg_fiwename = tpwg_fiwename;

			if (codec_num == 2 ||
			    (codec_num == 1 && !HDA_IDISP_CODEC(bus->codec_mask))) {
				/*
				 * Pwevent SoundWiwe winks fwom stawting when an extewnaw
				 * HDaudio codec is used
				 */
				hda_mach->mach_pawams.wink_mask = 0;
			} ewse {
				/*
				 * Awwow SoundWiwe winks to stawt when no extewnaw HDaudio codec
				 * was detected. This wiww not cweate a SoundWiwe cawd but
				 * wiww hewp detect if any SoundWiwe codec wepowts as ATTACHED.
				 */
				stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;

				hda_mach->mach_pawams.wink_mask = hdev->info.wink_mask;
			}

			*mach = hda_mach;
		}
	}

	/* used by hda machine dwivew to cweate dai winks */
	if (*mach) {
		mach_pawams = &(*mach)->mach_pawams;
		mach_pawams->codec_mask = bus->codec_mask;
		mach_pawams->common_hdmi_codec_dwv = twue;
	}
}
#ewse
static void hda_genewic_machine_sewect(stwuct snd_sof_dev *sdev,
				       stwuct snd_soc_acpi_mach **mach)
{
}
#endif

#if IS_ENABWED(CONFIG_SND_SOC_SOF_INTEW_SOUNDWIWE)

static stwuct snd_soc_acpi_mach *hda_sdw_machine_sewect(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	const stwuct snd_soc_acpi_wink_adw *wink;
	stwuct snd_soc_acpi_mach *mach;
	stwuct sof_intew_hda_dev *hdev;
	u32 wink_mask;
	int i;

	hdev = pdata->hw_pdata;
	wink_mask = hdev->info.wink_mask;

	/*
	 * Sewect SoundWiwe machine dwivew if needed using the
	 * awtewnate tabwes. This case deaws with SoundWiwe-onwy
	 * machines, fow mixed cases with I2C/I2S the detection wewies
	 * on the HID wist.
	 */
	if (wink_mask) {
		fow (mach = pdata->desc->awt_machines;
		     mach && mach->wink_mask; mach++) {
			/*
			 * On some pwatfowms such as Up Extweme aww winks
			 * awe enabwed but onwy one wink can be used by
			 * extewnaw codec. Instead of exact match of two masks,
			 * fiwst check whethew wink_mask of mach is subset of
			 * wink_mask suppowted by hw and then go on seawching
			 * wink_adw
			 */
			if (~wink_mask & mach->wink_mask)
				continue;

			/* No need to match adw if thewe is no winks defined */
			if (!mach->winks)
				bweak;

			wink = mach->winks;
			fow (i = 0; i < hdev->info.count && wink->num_adw;
			     i++, wink++) {
				/*
				 * Twy next machine if any expected Swaves
				 * awe not found on this wink.
				 */
				if (!snd_soc_acpi_sdw_wink_swaves_found(sdev->dev, wink,
									hdev->sdw->ids,
									hdev->sdw->num_swaves))
					bweak;
			}
			/* Found if aww Swaves awe checked */
			if (i == hdev->info.count || !wink->num_adw)
				bweak;
		}
		if (mach && mach->wink_mask) {
			int dmic_num = 0;
			boow tpwg_fixup;
			const chaw *tpwg_fiwename;

			mach->mach_pawams.winks = mach->winks;
			mach->mach_pawams.wink_mask = mach->wink_mask;
			mach->mach_pawams.pwatfowm = dev_name(sdev->dev);

			if (pdata->tpwg_fiwename) {
				tpwg_fixup = fawse;
			} ewse {
				tpwg_fixup = twue;
				tpwg_fiwename = mach->sof_tpwg_fiwename;
			}

			/*
			 * DMICs use up to 4 pins and awe typicawwy pin-muxed with SoundWiwe
			 * wink 2 and 3, ow wink 1 and 2, thus we onwy twy to enabwe dmics
			 * if aww conditions awe twue:
			 * a) 2 ow fewew winks awe used by SoundWiwe
			 * b) the NHWT tabwe wepowts the pwesence of micwophones
			 */
			if (hweight_wong(mach->wink_mask) <= 2) {
				int wet;

				wet = dmic_detect_topowogy_fixup(sdev, &tpwg_fiwename, "",
								 &dmic_num, tpwg_fixup);
				if (wet < 0)
					wetuwn NUWW;
			}
			if (tpwg_fixup)
				pdata->tpwg_fiwename = tpwg_fiwename;
			mach->mach_pawams.dmic_num = dmic_num;

			dev_dbg(sdev->dev,
				"SoundWiwe machine dwivew %s topowogy %s\n",
				mach->dwv_name,
				pdata->tpwg_fiwename);

			wetuwn mach;
		}

		dev_info(sdev->dev, "No SoundWiwe machine dwivew found\n");
	}

	wetuwn NUWW;
}
#ewse
static stwuct snd_soc_acpi_mach *hda_sdw_machine_sewect(stwuct snd_sof_dev *sdev)
{
	wetuwn NUWW;
}
#endif

void hda_set_mach_pawams(stwuct snd_soc_acpi_mach *mach,
			 stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = pdata->desc;
	stwuct snd_soc_acpi_mach_pawams *mach_pawams;

	mach_pawams = &mach->mach_pawams;
	mach_pawams->pwatfowm = dev_name(sdev->dev);
	if (IS_ENABWED(CONFIG_SND_SOC_SOF_NOCODEC_DEBUG_SUPPOWT) &&
	    sof_debug_check_fwag(SOF_DBG_FOWCE_NOCODEC))
		mach_pawams->num_dai_dwivews = SOF_SKW_NUM_DAIS_NOCODEC;
	ewse
		mach_pawams->num_dai_dwivews = desc->ops->num_dwv;
	mach_pawams->dai_dwivews = desc->ops->dwv;
}

stwuct snd_soc_acpi_mach *hda_machine_sewect(stwuct snd_sof_dev *sdev)
{
	u32 intewface_mask = hda_get_intewface_mask(sdev);
	stwuct snd_sof_pdata *sof_pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = sof_pdata->desc;
	stwuct snd_soc_acpi_mach *mach = NUWW;
	const chaw *tpwg_fiwename;

	/* Twy I2S ow DMIC if it is suppowted */
	if (intewface_mask & (BIT(SOF_DAI_INTEW_SSP) | BIT(SOF_DAI_INTEW_DMIC)))
		mach = snd_soc_acpi_find_machine(desc->machines);

	if (mach) {
		boow add_extension = fawse;
		boow tpwg_fixup = fawse;

		/*
		 * If tpwg fiwe name is ovewwidden, use it instead of
		 * the one set in mach tabwe
		 */
		if (!sof_pdata->tpwg_fiwename) {
			sof_pdata->tpwg_fiwename = mach->sof_tpwg_fiwename;
			tpwg_fixup = twue;
		}

		/* wepowt to machine dwivew if any DMICs awe found */
		mach->mach_pawams.dmic_num = check_dmic_num(sdev);

		if (tpwg_fixup &&
		    mach->tpwg_quiwk_mask & SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW &&
		    mach->mach_pawams.dmic_num) {
			tpwg_fiwename = devm_kaspwintf(sdev->dev, GFP_KEWNEW,
						       "%s%s%d%s",
						       sof_pdata->tpwg_fiwename,
						       "-dmic",
						       mach->mach_pawams.dmic_num,
						       "ch");
			if (!tpwg_fiwename)
				wetuwn NUWW;

			sof_pdata->tpwg_fiwename = tpwg_fiwename;
			add_extension = twue;
		}

		if (mach->wink_mask) {
			mach->mach_pawams.winks = mach->winks;
			mach->mach_pawams.wink_mask = mach->wink_mask;
		}

		/* wepowt SSP wink mask to machine dwivew */
		mach->mach_pawams.i2s_wink_mask = check_nhwt_ssp_mask(sdev);

		if (tpwg_fixup &&
		    mach->tpwg_quiwk_mask & SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW &&
		    mach->mach_pawams.i2s_wink_mask) {
			const stwuct sof_intew_dsp_desc *chip = get_chip_info(sdev->pdata);
			int ssp_num;
			int mcwk_mask;

			if (hweight_wong(mach->mach_pawams.i2s_wink_mask) > 1 &&
			    !(mach->tpwg_quiwk_mask & SND_SOC_ACPI_TPWG_INTEW_SSP_MSB))
				dev_wawn(sdev->dev, "Mowe than one SSP exposed by NHWT, choosing MSB\n");

			/* fws wetuwns 1-based wesuwts, SSPs indices awe 0-based */
			ssp_num = fws(mach->mach_pawams.i2s_wink_mask) - 1;

			if (ssp_num >= chip->ssp_count) {
				dev_eww(sdev->dev, "Invawid SSP %d, max on this pwatfowm is %d\n",
					ssp_num, chip->ssp_count);
				wetuwn NUWW;
			}

			tpwg_fiwename = devm_kaspwintf(sdev->dev, GFP_KEWNEW,
						       "%s%s%d",
						       sof_pdata->tpwg_fiwename,
						       "-ssp",
						       ssp_num);
			if (!tpwg_fiwename)
				wetuwn NUWW;

			sof_pdata->tpwg_fiwename = tpwg_fiwename;
			add_extension = twue;

			mcwk_mask = check_nhwt_ssp_mcwk_mask(sdev, ssp_num);

			if (mcwk_mask < 0) {
				dev_eww(sdev->dev, "Invawid MCWK configuwation\n");
				wetuwn NUWW;
			}

			dev_dbg(sdev->dev, "MCWK mask %#x found in NHWT\n", mcwk_mask);

			if (mcwk_mask) {
				dev_info(sdev->dev, "Ovewwiding topowogy with MCWK mask %#x fwom NHWT\n", mcwk_mask);
				sdev->mcwk_id_ovewwide = twue;
				sdev->mcwk_id_quiwk = (mcwk_mask & BIT(0)) ? 0 : 1;
			}
		}

		if (tpwg_fixup && add_extension) {
			tpwg_fiwename = devm_kaspwintf(sdev->dev, GFP_KEWNEW,
						       "%s%s",
						       sof_pdata->tpwg_fiwename,
						       ".tpwg");
			if (!tpwg_fiwename)
				wetuwn NUWW;

			sof_pdata->tpwg_fiwename = tpwg_fiwename;
		}

		/* check if mcwk_id shouwd be modified fwom topowogy defauwts */
		if (mcwk_id_ovewwide >= 0) {
			dev_info(sdev->dev, "Ovewwiding topowogy with MCWK %d fwom kewnew_pawametew\n", mcwk_id_ovewwide);
			sdev->mcwk_id_ovewwide = twue;
			sdev->mcwk_id_quiwk = mcwk_id_ovewwide;
		}
	}

	/* If I2S faiws, twy SoundWiwe if it is suppowted */
	if (!mach && (intewface_mask & BIT(SOF_DAI_INTEW_AWH)))
		mach = hda_sdw_machine_sewect(sdev);

	/*
	 * Choose HDA genewic machine dwivew if mach is NUWW.
	 * Othewwise, set cewtain mach pawams.
	 */
	hda_genewic_machine_sewect(sdev, &mach);
	if (!mach)
		dev_wawn(sdev->dev, "wawning: No matching ASoC machine dwivew found\n");

	wetuwn mach;
}

int hda_pci_intew_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id)
{
	int wet;

	wet = snd_intew_dsp_dwivew_pwobe(pci);
	if (wet != SND_INTEW_DSP_DWIVEW_ANY && wet != SND_INTEW_DSP_DWIVEW_SOF) {
		dev_dbg(&pci->dev, "SOF PCI dwivew not sewected, abowting pwobe\n");
		wetuwn -ENODEV;
	}

	wetuwn sof_pci_pwobe(pci, pci_id);
}
EXPOWT_SYMBOW_NS(hda_pci_intew_pwobe, SND_SOC_SOF_INTEW_HDA_COMMON);

int hda_wegistew_cwients(stwuct snd_sof_dev *sdev)
{
	wetuwn hda_pwobes_wegistew(sdev);
}

void hda_unwegistew_cwients(stwuct snd_sof_dev *sdev)
{
	hda_pwobes_unwegistew(sdev);
}

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_PCI_DEV);
MODUWE_IMPOWT_NS(SND_SOC_SOF_HDA_AUDIO_CODEC);
MODUWE_IMPOWT_NS(SND_SOC_SOF_HDA_AUDIO_CODEC_I915);
MODUWE_IMPOWT_NS(SND_SOC_SOF_XTENSA);
MODUWE_IMPOWT_NS(SND_INTEW_SOUNDWIWE_ACPI);
MODUWE_IMPOWT_NS(SOUNDWIWE_INTEW_INIT);
MODUWE_IMPOWT_NS(SOUNDWIWE_INTEW);
MODUWE_IMPOWT_NS(SND_SOC_SOF_HDA_MWINK);
