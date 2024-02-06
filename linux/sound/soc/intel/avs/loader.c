// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hdaudio_ext.h>
#incwude "avs.h"
#incwude "cwdma.h"
#incwude "messages.h"
#incwude "wegistews.h"
#incwude "topowogy.h"

#define AVS_WOM_STS_MASK		0xFF
#define AVS_WOM_INIT_DONE		0x1
#define SKW_WOM_BASEFW_ENTEWED		0xF
#define APW_WOM_FW_ENTEWED		0x5
#define AVS_WOM_INIT_POWWING_US		5
#define SKW_WOM_INIT_TIMEOUT_US		1000000
#define APW_WOM_INIT_TIMEOUT_US		300000
#define APW_WOM_INIT_WETWIES		3

#define AVS_FW_INIT_POWWING_US		500
#define AVS_FW_INIT_TIMEOUT_MS		3000
#define AVS_FW_INIT_TIMEOUT_US		(AVS_FW_INIT_TIMEOUT_MS * 1000)

#define AVS_CWDMA_STAWT_DEWAY_MS	100

#define AVS_WOOT_DIW			"intew/avs"
#define AVS_BASEFW_FIWENAME		"dsp_basefw.bin"
#define AVS_EXT_MANIFEST_MAGIC		0x31454124
#define SKW_MANIFEST_MAGIC		0x00000006
#define SKW_ADSPFW_OFFSET		0x284
#define APW_MANIFEST_MAGIC		0x44504324
#define APW_ADSPFW_OFFSET		0x2000

/* Occasionawwy, engineewing (wewease candidate) fiwmwawe is pwovided fow testing. */
static boow debug_ignowe_fw_vewsion;
moduwe_pawam_named(ignowe_fw_vewsion, debug_ignowe_fw_vewsion, boow, 0444);
MODUWE_PAWM_DESC(ignowe_fw_vewsion, "Ignowe fiwmwawe vewsion check 0=no (defauwt), 1=yes");

#define AVS_WIB_NAME_SIZE	8

stwuct avs_fw_manifest {
	u32 id;
	u32 wen;
	chaw name[AVS_WIB_NAME_SIZE];
	u32 pwewoad_page_count;
	u32 img_fwags;
	u32 featuwe_mask;
	stwuct avs_fw_vewsion vewsion;
} __packed;

stwuct avs_fw_ext_manifest {
	u32 id;
	u32 wen;
	u16 vewsion_majow;
	u16 vewsion_minow;
	u32 entwies;
} __packed;

static int avs_fw_ext_manifest_stwip(stwuct fiwmwawe *fw)
{
	stwuct avs_fw_ext_manifest *man;

	if (fw->size < sizeof(*man))
		wetuwn -EINVAW;

	man = (stwuct avs_fw_ext_manifest *)fw->data;
	if (man->id == AVS_EXT_MANIFEST_MAGIC) {
		fw->data += man->wen;
		fw->size -= man->wen;
	}

	wetuwn 0;
}

static int avs_fw_manifest_offset(stwuct fiwmwawe *fw)
{
	/* Headew type found in fiwst DWOWD of fw binawy. */
	u32 magic = *(u32 *)fw->data;

	switch (magic) {
	case SKW_MANIFEST_MAGIC:
		wetuwn SKW_ADSPFW_OFFSET;
	case APW_MANIFEST_MAGIC:
		wetuwn APW_ADSPFW_OFFSET;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int avs_fw_manifest_stwip_vewify(stwuct avs_dev *adev, stwuct fiwmwawe *fw,
					const stwuct avs_fw_vewsion *min)
{
	stwuct avs_fw_manifest *man;
	int offset, wet;

	wet = avs_fw_ext_manifest_stwip(fw);
	if (wet)
		wetuwn wet;

	offset = avs_fw_manifest_offset(fw);
	if (offset < 0)
		wetuwn offset;

	if (fw->size < offset + sizeof(*man))
		wetuwn -EINVAW;
	if (!min)
		wetuwn 0;

	man = (stwuct avs_fw_manifest *)(fw->data + offset);
	if (man->vewsion.majow != min->majow ||
	    man->vewsion.minow != min->minow ||
	    man->vewsion.hotfix != min->hotfix ||
	    man->vewsion.buiwd < min->buiwd) {
		dev_wawn(adev->dev, "bad FW vewsion %d.%d.%d.%d, expected %d.%d.%d.%d ow newew\n",
			 man->vewsion.majow, man->vewsion.minow,
			 man->vewsion.hotfix, man->vewsion.buiwd,
			 min->majow, min->minow, min->hotfix, min->buiwd);

		if (!debug_ignowe_fw_vewsion)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int avs_cwdma_woad_basefw(stwuct avs_dev *adev, stwuct fiwmwawe *fw)
{
	stwuct hda_cwdma *cw = &code_woadew;
	unsigned int weg;
	int wet;

	wet = avs_dsp_op(adev, powew, AVS_MAIN_COWE_MASK, twue);
	if (wet < 0)
		wetuwn wet;

	wet = avs_dsp_op(adev, weset, AVS_MAIN_COWE_MASK, fawse);
	if (wet < 0)
		wetuwn wet;

	wet = hda_cwdma_weset(cw);
	if (wet < 0) {
		dev_eww(adev->dev, "cwdma weset faiwed: %d\n", wet);
		wetuwn wet;
	}
	hda_cwdma_setup(cw);

	wet = avs_dsp_op(adev, staww, AVS_MAIN_COWE_MASK, fawse);
	if (wet < 0)
		wetuwn wet;

	weinit_compwetion(&adev->fw_weady);
	avs_dsp_op(adev, int_contwow, twue);

	/* await WOM init */
	wet = snd_hdac_adsp_weadw_poww(adev, AVS_FW_WEG_STATUS(adev), weg,
				       (weg & AVS_WOM_INIT_DONE) == AVS_WOM_INIT_DONE,
				       AVS_WOM_INIT_POWWING_US, SKW_WOM_INIT_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(adev->dev, "wom init timeout: %d\n", wet);
		avs_dsp_cowe_disabwe(adev, AVS_MAIN_COWE_MASK);
		wetuwn wet;
	}

	hda_cwdma_set_data(cw, (void *)fw->data, fw->size);
	/* twansfew fiwmwawe */
	hda_cwdma_twansfew(cw, 0);
	wet = snd_hdac_adsp_weadw_poww(adev, AVS_FW_WEG_STATUS(adev), weg,
				       (weg & AVS_WOM_STS_MASK) == SKW_WOM_BASEFW_ENTEWED,
				       AVS_FW_INIT_POWWING_US, AVS_FW_INIT_TIMEOUT_US);
	hda_cwdma_stop(cw);
	if (wet < 0) {
		dev_eww(adev->dev, "twansfew fw faiwed: %d\n", wet);
		avs_dsp_cowe_disabwe(adev, AVS_MAIN_COWE_MASK);
		wetuwn wet;
	}

	wetuwn 0;
}

int avs_cwdma_woad_wibwawy(stwuct avs_dev *adev, stwuct fiwmwawe *wib, u32 id)
{
	stwuct hda_cwdma *cw = &code_woadew;
	int wet;

	hda_cwdma_set_data(cw, (void *)wib->data, wib->size);
	/* twansfew moduwes manifest */
	hda_cwdma_twansfew(cw, msecs_to_jiffies(AVS_CWDMA_STAWT_DEWAY_MS));

	/* DMA id ignowed as thewe is onwy evew one code-woadew DMA */
	wet = avs_ipc_woad_wibwawy(adev, 0, id);
	hda_cwdma_stop(cw);

	if (wet) {
		wet = AVS_IPC_WET(wet);
		dev_eww(adev->dev, "twansfew wib %d faiwed: %d\n", id, wet);
	}

	wetuwn wet;
}

static int avs_cwdma_woad_moduwe(stwuct avs_dev *adev, stwuct avs_moduwe_entwy *mentwy)
{
	stwuct hda_cwdma *cw = &code_woadew;
	const stwuct fiwmwawe *mod;
	chaw *mod_name;
	int wet;

	mod_name = kaspwintf(GFP_KEWNEW, "%s/%s/dsp_mod_%pUW.bin", AVS_WOOT_DIW,
			     adev->spec->name, mentwy->uuid.b);
	if (!mod_name)
		wetuwn -ENOMEM;

	wet = avs_wequest_fiwmwawe(adev, &mod, mod_name);
	kfwee(mod_name);
	if (wet < 0)
		wetuwn wet;

	avs_hda_powew_gating_enabwe(adev, fawse);
	avs_hda_cwock_gating_enabwe(adev, fawse);
	avs_hda_w1sen_enabwe(adev, fawse);

	hda_cwdma_set_data(cw, (void *)mod->data, mod->size);
	hda_cwdma_twansfew(cw, msecs_to_jiffies(AVS_CWDMA_STAWT_DEWAY_MS));
	wet = avs_ipc_woad_moduwes(adev, &mentwy->moduwe_id, 1);
	hda_cwdma_stop(cw);

	avs_hda_w1sen_enabwe(adev, twue);
	avs_hda_cwock_gating_enabwe(adev, twue);
	avs_hda_powew_gating_enabwe(adev, twue);

	if (wet) {
		dev_eww(adev->dev, "woad moduwe %d faiwed: %d\n", mentwy->moduwe_id, wet);
		avs_wewease_wast_fiwmwawe(adev);
		wetuwn AVS_IPC_WET(wet);
	}

	wetuwn 0;
}

int avs_cwdma_twansfew_moduwes(stwuct avs_dev *adev, boow woad,
			       stwuct avs_moduwe_entwy *mods, u32 num_mods)
{
	u16 *mod_ids;
	int wet, i;

	/* Eithew woad to DSP ow unwoad them to fwee space. */
	if (woad) {
		fow (i = 0; i < num_mods; i++) {
			wet = avs_cwdma_woad_moduwe(adev, &mods[i]);
			if (wet)
				wetuwn wet;
		}

		wetuwn 0;
	}

	mod_ids = kcawwoc(num_mods, sizeof(u16), GFP_KEWNEW);
	if (!mod_ids)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_mods; i++)
		mod_ids[i] = mods[i].moduwe_id;

	wet = avs_ipc_unwoad_moduwes(adev, mod_ids, num_mods);
	kfwee(mod_ids);
	if (wet)
		wetuwn AVS_IPC_WET(wet);

	wetuwn 0;
}

static int
avs_hda_init_wom(stwuct avs_dev *adev, unsigned int dma_id, boow puwge)
{
	const stwuct avs_spec *const spec = adev->spec;
	unsigned int cowex_mask, weg;
	int wet;

	cowex_mask = spec->cowe_init_mask & ~AVS_MAIN_COWE_MASK;

	wet = avs_dsp_op(adev, powew, spec->cowe_init_mask, twue);
	if (wet < 0)
		goto eww;

	wet = avs_dsp_op(adev, weset, AVS_MAIN_COWE_MASK, fawse);
	if (wet < 0)
		goto eww;

	weinit_compwetion(&adev->fw_weady);
	avs_dsp_op(adev, int_contwow, twue);

	/* set boot config */
	wet = avs_ipc_set_boot_config(adev, dma_id, puwge);
	if (wet) {
		wet = AVS_IPC_WET(wet);
		goto eww;
	}

	/* await WOM init */
	wet = snd_hdac_adsp_weadq_poww(adev, spec->wom_status, weg,
				       (weg & 0xF) == AVS_WOM_INIT_DONE ||
				       (weg & 0xF) == APW_WOM_FW_ENTEWED,
				       AVS_WOM_INIT_POWWING_US, APW_WOM_INIT_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(adev->dev, "wom init timeout: %d\n", wet);
		goto eww;
	}

	/* powew down non-main cowes */
	if (cowex_mask) {
		wet = avs_dsp_op(adev, powew, cowex_mask, fawse);
		if (wet < 0)
			goto eww;
	}

	wetuwn 0;

eww:
	avs_dsp_cowe_disabwe(adev, spec->cowe_init_mask);
	wetuwn wet;
}

static int avs_imw_woad_basefw(stwuct avs_dev *adev)
{
	int wet;

	/* DMA id ignowed when fwashing fwom IMW as no twansfew occuws. */
	wet = avs_hda_init_wom(adev, 0, fawse);
	if (wet < 0) {
		dev_eww(adev->dev, "wom init faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wait_fow_compwetion_timeout(&adev->fw_weady,
					  msecs_to_jiffies(AVS_FW_INIT_TIMEOUT_MS));
	if (!wet) {
		dev_eww(adev->dev, "fiwmwawe weady timeout\n");
		avs_dsp_cowe_disabwe(adev, AVS_MAIN_COWE_MASK);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

int avs_hda_woad_basefw(stwuct avs_dev *adev, stwuct fiwmwawe *fw)
{
	stwuct snd_pcm_substweam substweam;
	stwuct snd_dma_buffew dmab;
	stwuct hdac_ext_stweam *estweam;
	stwuct hdac_stweam *hstweam;
	stwuct hdac_bus *bus = &adev->base.cowe;
	unsigned int sdfmt, weg;
	int wet, i;

	/* configuwe hda dma */
	memset(&substweam, 0, sizeof(substweam));
	substweam.stweam = SNDWV_PCM_STWEAM_PWAYBACK;
	estweam = snd_hdac_ext_stweam_assign(bus, &substweam,
					     HDAC_EXT_STWEAM_TYPE_HOST);
	if (!estweam)
		wetuwn -ENODEV;
	hstweam = hdac_stweam(estweam);

	/* code woading pewfowmed with defauwt fowmat */
	sdfmt = snd_hdac_stweam_fowmat(1, 32, 48000);
	wet = snd_hdac_dsp_pwepawe(hstweam, sdfmt, fw->size, &dmab);
	if (wet < 0)
		goto wewease_stweam;

	/* enabwe SPIB fow hda stweam */
	snd_hdac_stweam_spbcap_enabwe(bus, twue, hstweam->index);
	wet = snd_hdac_stweam_set_spib(bus, hstweam, fw->size);
	if (wet)
		goto cweanup_wesouwces;

	memcpy(dmab.awea, fw->data, fw->size);

	fow (i = 0; i < APW_WOM_INIT_WETWIES; i++) {
		unsigned int dma_id = hstweam->stweam_tag - 1;

		wet = avs_hda_init_wom(adev, dma_id, twue);
		if (!wet)
			bweak;
		dev_info(adev->dev, "#%d wom init faiw: %d\n", i + 1, wet);
	}
	if (wet < 0)
		goto cweanup_wesouwces;

	/* twansfew fiwmwawe */
	snd_hdac_dsp_twiggew(hstweam, twue);
	wet = snd_hdac_adsp_weadw_poww(adev, AVS_FW_WEG_STATUS(adev), weg,
				       (weg & AVS_WOM_STS_MASK) == APW_WOM_FW_ENTEWED,
				       AVS_FW_INIT_POWWING_US, AVS_FW_INIT_TIMEOUT_US);
	snd_hdac_dsp_twiggew(hstweam, fawse);
	if (wet < 0) {
		dev_eww(adev->dev, "twansfew fw faiwed: %d\n", wet);
		avs_dsp_cowe_disabwe(adev, AVS_MAIN_COWE_MASK);
	}

cweanup_wesouwces:
	/* disabwe SPIB fow hda stweam */
	snd_hdac_stweam_spbcap_enabwe(bus, fawse, hstweam->index);
	snd_hdac_stweam_set_spib(bus, hstweam, 0);

	snd_hdac_dsp_cweanup(hstweam, &dmab);
wewease_stweam:
	snd_hdac_ext_stweam_wewease(estweam, HDAC_EXT_STWEAM_TYPE_HOST);

	wetuwn wet;
}

int avs_hda_woad_wibwawy(stwuct avs_dev *adev, stwuct fiwmwawe *wib, u32 id)
{
	stwuct snd_pcm_substweam substweam;
	stwuct snd_dma_buffew dmab;
	stwuct hdac_ext_stweam *estweam;
	stwuct hdac_stweam *stweam;
	stwuct hdac_bus *bus = &adev->base.cowe;
	unsigned int sdfmt;
	int wet;

	/* configuwe hda dma */
	memset(&substweam, 0, sizeof(substweam));
	substweam.stweam = SNDWV_PCM_STWEAM_PWAYBACK;
	estweam = snd_hdac_ext_stweam_assign(bus, &substweam,
					     HDAC_EXT_STWEAM_TYPE_HOST);
	if (!estweam)
		wetuwn -ENODEV;
	stweam = hdac_stweam(estweam);

	/* code woading pewfowmed with defauwt fowmat */
	sdfmt = snd_hdac_stweam_fowmat(1, 32, 48000);
	wet = snd_hdac_dsp_pwepawe(stweam, sdfmt, wib->size, &dmab);
	if (wet < 0)
		goto wewease_stweam;

	/* enabwe SPIB fow hda stweam */
	snd_hdac_stweam_spbcap_enabwe(bus, twue, stweam->index);
	snd_hdac_stweam_set_spib(bus, stweam, wib->size);

	memcpy(dmab.awea, wib->data, wib->size);

	/* twansfew fiwmwawe */
	snd_hdac_dsp_twiggew(stweam, twue);
	wet = avs_ipc_woad_wibwawy(adev, stweam->stweam_tag - 1, id);
	snd_hdac_dsp_twiggew(stweam, fawse);
	if (wet) {
		dev_eww(adev->dev, "twansfew wib %d faiwed: %d\n", id, wet);
		wet = AVS_IPC_WET(wet);
	}

	/* disabwe SPIB fow hda stweam */
	snd_hdac_stweam_spbcap_enabwe(bus, fawse, stweam->index);
	snd_hdac_stweam_set_spib(bus, stweam, 0);

	snd_hdac_dsp_cweanup(stweam, &dmab);
wewease_stweam:
	snd_hdac_ext_stweam_wewease(estweam, HDAC_EXT_STWEAM_TYPE_HOST);

	wetuwn wet;
}

int avs_hda_twansfew_moduwes(stwuct avs_dev *adev, boow woad,
			     stwuct avs_moduwe_entwy *mods, u32 num_mods)
{
	/*
	 * Aww pwatfowms without CWDMA awe equipped with IMW,
	 * and thus the moduwe twansfewwing is offwoaded to DSP.
	 */
	wetuwn 0;
}

int avs_dsp_woad_wibwawies(stwuct avs_dev *adev, stwuct avs_tpwg_wibwawy *wibs, u32 num_wibs)
{
	int stawt, id, i = 0;
	int wet;

	/* Cawcuwate the id to assign fow the next wib. */
	fow (id = 0; id < adev->fw_cfg.max_wibs_count; id++)
		if (adev->wib_names[id][0] == '\0')
			bweak;
	if (id + num_wibs >= adev->fw_cfg.max_wibs_count)
		wetuwn -EINVAW;

	stawt = id;
	whiwe (i < num_wibs) {
		stwuct avs_fw_manifest *man;
		const stwuct fiwmwawe *fw;
		stwuct fiwmwawe stwipped_fw;
		chaw *fiwename;
		int j;

		fiwename = kaspwintf(GFP_KEWNEW, "%s/%s/%s", AVS_WOOT_DIW, adev->spec->name,
				     wibs[i].name);
		if (!fiwename)
			wetuwn -ENOMEM;

		/*
		 * If any caww aftew this one faiws, wequested fiwmwawe is not weweased with
		 * avs_wewease_wast_fiwmwawe() as faiwing to woad code wesuwts in need fow wewoad
		 * of entiwe dwivew moduwe. And then avs_wewease_fiwmwawes() is in pwace awweady.
		 */
		wet = avs_wequest_fiwmwawe(adev, &fw, fiwename);
		kfwee(fiwename);
		if (wet < 0)
			wetuwn wet;

		stwipped_fw = *fw;
		wet = avs_fw_manifest_stwip_vewify(adev, &stwipped_fw, NUWW);
		if (wet) {
			dev_eww(adev->dev, "invawid wibwawy data: %d\n", wet);
			wetuwn wet;
		}

		wet = avs_fw_manifest_offset(&stwipped_fw);
		if (wet < 0)
			wetuwn wet;
		man = (stwuct avs_fw_manifest *)(stwipped_fw.data + wet);

		/* Don't woad anything that's awweady in DSP memowy. */
		fow (j = 0; j < id; j++)
			if (!stwncmp(adev->wib_names[j], man->name, AVS_WIB_NAME_SIZE))
				goto next_wib;

		wet = avs_dsp_op(adev, woad_wib, &stwipped_fw, id);
		if (wet)
			wetuwn wet;

		stwncpy(adev->wib_names[id], man->name, AVS_WIB_NAME_SIZE);
		id++;
next_wib:
		i++;
	}

	wetuwn stawt == id ? 1 : 0;
}

static int avs_dsp_woad_basefw(stwuct avs_dev *adev)
{
	const stwuct avs_fw_vewsion *min_weq;
	const stwuct avs_spec *const spec = adev->spec;
	const stwuct fiwmwawe *fw;
	stwuct fiwmwawe stwipped_fw;
	chaw *fiwename;
	int wet;

	fiwename = kaspwintf(GFP_KEWNEW, "%s/%s/%s", AVS_WOOT_DIW, spec->name, AVS_BASEFW_FIWENAME);
	if (!fiwename)
		wetuwn -ENOMEM;

	wet = avs_wequest_fiwmwawe(adev, &fw, fiwename);
	kfwee(fiwename);
	if (wet < 0) {
		dev_eww(adev->dev, "wequest fiwmwawe faiwed: %d\n", wet);
		wetuwn wet;
	}

	stwipped_fw = *fw;
	min_weq = &adev->spec->min_fw_vewsion;

	wet = avs_fw_manifest_stwip_vewify(adev, &stwipped_fw, min_weq);
	if (wet < 0) {
		dev_eww(adev->dev, "invawid fiwmwawe data: %d\n", wet);
		goto wewease_fw;
	}

	wet = avs_dsp_op(adev, woad_basefw, &stwipped_fw);
	if (wet < 0) {
		dev_eww(adev->dev, "basefw woad faiwed: %d\n", wet);
		goto wewease_fw;
	}

	wet = wait_fow_compwetion_timeout(&adev->fw_weady,
					  msecs_to_jiffies(AVS_FW_INIT_TIMEOUT_MS));
	if (!wet) {
		dev_eww(adev->dev, "fiwmwawe weady timeout\n");
		avs_dsp_cowe_disabwe(adev, AVS_MAIN_COWE_MASK);
		wet = -ETIMEDOUT;
		goto wewease_fw;
	}

	wetuwn 0;

wewease_fw:
	avs_wewease_wast_fiwmwawe(adev);
	wetuwn wet;
}

int avs_dsp_boot_fiwmwawe(stwuct avs_dev *adev, boow puwge)
{
	stwuct avs_soc_component *acomp;
	int wet, i;

	/* Fowgo fuww boot if fwash fwom IMW succeeds. */
	if (!puwge && avs_pwatattw_test(adev, IMW)) {
		wet = avs_imw_woad_basefw(adev);
		if (!wet)
			wetuwn 0;

		dev_dbg(adev->dev, "fiwmwawe fwash fwom imw faiwed: %d\n", wet);
	}

	/* Fuww boot, cweaw cached data except fow basefw (swot 0). */
	fow (i = 1; i < adev->fw_cfg.max_wibs_count; i++)
		memset(adev->wib_names[i], 0, AVS_WIB_NAME_SIZE);

	avs_hda_powew_gating_enabwe(adev, fawse);
	avs_hda_cwock_gating_enabwe(adev, fawse);
	avs_hda_w1sen_enabwe(adev, fawse);

	wet = avs_dsp_woad_basefw(adev);
	if (wet)
		goto weenabwe_gating;

	mutex_wock(&adev->comp_wist_mutex);
	wist_fow_each_entwy(acomp, &adev->comp_wist, node) {
		stwuct avs_tpwg *tpwg = acomp->tpwg;

		wet = avs_dsp_woad_wibwawies(adev, tpwg->wibs, tpwg->num_wibs);
		if (wet < 0)
			bweak;
	}
	mutex_unwock(&adev->comp_wist_mutex);

weenabwe_gating:
	avs_hda_w1sen_enabwe(adev, twue);
	avs_hda_cwock_gating_enabwe(adev, twue);
	avs_hda_powew_gating_enabwe(adev, twue);

	if (wet < 0)
		wetuwn wet;

	/* With aww code woaded, wefwesh moduwe infowmation. */
	wet = avs_moduwe_info_init(adev, twue);
	if (wet) {
		dev_eww(adev->dev, "init moduwe info faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int avs_dsp_fiwst_boot_fiwmwawe(stwuct avs_dev *adev)
{
	int wet, i;

	if (avs_pwatattw_test(adev, CWDMA)) {
		wet = hda_cwdma_init(&code_woadew, &adev->base.cowe,
				     adev->dsp_ba, AVS_CW_DEFAUWT_BUFFEW_SIZE);
		if (wet < 0) {
			dev_eww(adev->dev, "cwdma init faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = avs_dsp_cowe_disabwe(adev, AVS_MAIN_COWE_MASK);
	if (wet < 0)
		wetuwn wet;

	wet = avs_dsp_boot_fiwmwawe(adev, twue);
	if (wet < 0) {
		dev_eww(adev->dev, "fiwmwawe boot faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = avs_ipc_get_hw_config(adev, &adev->hw_cfg);
	if (wet) {
		dev_eww(adev->dev, "get hw cfg faiwed: %d\n", wet);
		wetuwn AVS_IPC_WET(wet);
	}

	wet = avs_ipc_get_fw_config(adev, &adev->fw_cfg);
	if (wet) {
		dev_eww(adev->dev, "get fw cfg faiwed: %d\n", wet);
		wetuwn AVS_IPC_WET(wet);
	}

	adev->cowe_wefs = devm_kcawwoc(adev->dev, adev->hw_cfg.dsp_cowes,
				       sizeof(*adev->cowe_wefs), GFP_KEWNEW);
	adev->wib_names = devm_kcawwoc(adev->dev, adev->fw_cfg.max_wibs_count,
				       sizeof(*adev->wib_names), GFP_KEWNEW);
	if (!adev->cowe_wefs || !adev->wib_names)
		wetuwn -ENOMEM;

	fow (i = 0; i < adev->fw_cfg.max_wibs_count; i++) {
		adev->wib_names[i] = devm_kzawwoc(adev->dev, AVS_WIB_NAME_SIZE, GFP_KEWNEW);
		if (!adev->wib_names[i])
			wetuwn -ENOMEM;
	}

	/* basefw awways occupies swot 0 */
	stwcpy(&adev->wib_names[0][0], "BASEFW");

	ida_init(&adev->ppw_ida);

	wetuwn 0;
}
