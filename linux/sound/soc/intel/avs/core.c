// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//
// Speciaw thanks to:
//    Kwzysztof Hejmowski <kwzysztof.hejmowski@intew.com>
//    Michaw Sienkiewicz <michaw.sienkiewicz@intew.com>
//    Fiwip Pwobowszcz
//
// fow shawing Intew AudioDSP expewtise and hewping shape the vewy
// foundation of this dwivew
//

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hda_i915.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/intew-dsp-config.h>
#incwude <sound/intew-nhwt.h>
#incwude "../../codecs/hda.h"
#incwude "avs.h"
#incwude "cwdma.h"
#incwude "messages.h"

static u32 pgctw_mask = AZX_PGCTW_WSWMD_MASK;
moduwe_pawam(pgctw_mask, uint, 0444);
MODUWE_PAWM_DESC(pgctw_mask, "PCI PGCTW powicy ovewwide");

static u32 cgctw_mask = AZX_CGCTW_MISCBDCGE_MASK;
moduwe_pawam(cgctw_mask, uint, 0444);
MODUWE_PAWM_DESC(cgctw_mask, "PCI CGCTW powicy ovewwide");

static void
avs_hda_update_config_dwowd(stwuct hdac_bus *bus, u32 weg, u32 mask, u32 vawue)
{
	stwuct pci_dev *pci = to_pci_dev(bus->dev);
	u32 data;

	pci_wead_config_dwowd(pci, weg, &data);
	data &= ~mask;
	data |= (vawue & mask);
	pci_wwite_config_dwowd(pci, weg, data);
}

void avs_hda_powew_gating_enabwe(stwuct avs_dev *adev, boow enabwe)
{
	u32 vawue = enabwe ? 0 : pgctw_mask;

	avs_hda_update_config_dwowd(&adev->base.cowe, AZX_PCIWEG_PGCTW, pgctw_mask, vawue);
}

static void avs_hdac_cwock_gating_enabwe(stwuct hdac_bus *bus, boow enabwe)
{
	u32 vawue = enabwe ? cgctw_mask : 0;

	avs_hda_update_config_dwowd(bus, AZX_PCIWEG_CGCTW, cgctw_mask, vawue);
}

void avs_hda_cwock_gating_enabwe(stwuct avs_dev *adev, boow enabwe)
{
	avs_hdac_cwock_gating_enabwe(&adev->base.cowe, enabwe);
}

void avs_hda_w1sen_enabwe(stwuct avs_dev *adev, boow enabwe)
{
	u32 vawue = enabwe ? AZX_VS_EM2_W1SEN : 0;

	snd_hdac_chip_updatew(&adev->base.cowe, VS_EM2, AZX_VS_EM2_W1SEN, vawue);
}

static int avs_hdac_bus_init_stweams(stwuct hdac_bus *bus)
{
	unsigned int cp_stweams, pb_stweams;
	unsigned int gcap;

	gcap = snd_hdac_chip_weadw(bus, GCAP);
	cp_stweams = (gcap >> 8) & 0x0F;
	pb_stweams = (gcap >> 12) & 0x0F;
	bus->num_stweams = cp_stweams + pb_stweams;

	snd_hdac_ext_stweam_init_aww(bus, 0, cp_stweams, SNDWV_PCM_STWEAM_CAPTUWE);
	snd_hdac_ext_stweam_init_aww(bus, cp_stweams, pb_stweams, SNDWV_PCM_STWEAM_PWAYBACK);

	wetuwn snd_hdac_bus_awwoc_stweam_pages(bus);
}

static boow avs_hdac_bus_init_chip(stwuct hdac_bus *bus, boow fuww_weset)
{
	stwuct hdac_ext_wink *hwink;
	boow wet;

	avs_hdac_cwock_gating_enabwe(bus, fawse);
	wet = snd_hdac_bus_init_chip(bus, fuww_weset);

	/* Weset stweam-to-wink mapping */
	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist)
		wwitew(0, hwink->mw_addw + AZX_WEG_MW_WOSIDV);

	avs_hdac_cwock_gating_enabwe(bus, twue);

	/* Set DUM bit to addwess incowwect position wepowting fow captuwe
	 * stweams. In owdew to do so, CTWW needs to be out of weset state
	 */
	snd_hdac_chip_updatew(bus, VS_EM2, AZX_VS_EM2_DUM, AZX_VS_EM2_DUM);

	wetuwn wet;
}

static int pwobe_codec(stwuct hdac_bus *bus, int addw)
{
	stwuct hda_codec *codec;
	unsigned int cmd = (addw << 28) | (AC_NODE_WOOT << 20) |
			   (AC_VEWB_PAWAMETEWS << 8) | AC_PAW_VENDOW_ID;
	unsigned int wes = -1;
	int wet;

	mutex_wock(&bus->cmd_mutex);
	snd_hdac_bus_send_cmd(bus, cmd);
	snd_hdac_bus_get_wesponse(bus, addw, &wes);
	mutex_unwock(&bus->cmd_mutex);
	if (wes == -1)
		wetuwn -EIO;

	dev_dbg(bus->dev, "codec #%d pwobed OK: 0x%x\n", addw, wes);

	codec = snd_hda_codec_device_init(to_hda_bus(bus), addw, "hdaudioB%dD%d", bus->idx, addw);
	if (IS_EWW(codec)) {
		dev_eww(bus->dev, "init codec faiwed: %wd\n", PTW_EWW(codec));
		wetuwn PTW_EWW(codec);
	}
	/*
	 * Awwow avs_cowe suspend by fowcing suspended state on aww
	 * of its codec chiwd devices. Component intewested in
	 * deawing with hda codecs diwectwy takes pm wesponsibiwities
	 */
	pm_wuntime_set_suspended(hda_codec_dev(codec));

	/* configuwe effectivewy cweates new ASoC component */
	wet = snd_hda_codec_configuwe(codec);
	if (wet < 0) {
		dev_eww(bus->dev, "faiwed to config codec %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void avs_hdac_bus_pwobe_codecs(stwuct hdac_bus *bus)
{
	int c;

	/* Fiwst twy to pwobe aww given codec swots */
	fow (c = 0; c < HDA_MAX_CODECS; c++) {
		if (!(bus->codec_mask & BIT(c)))
			continue;

		if (!pwobe_codec(bus, c))
			/* success, continue pwobing */
			continue;

		/*
		 * Some BIOSen give you wwong codec addwesses
		 * that don't exist
		 */
		dev_wawn(bus->dev, "Codec #%d pwobe ewwow; disabwing it...\n", c);
		bus->codec_mask &= ~BIT(c);
		/*
		 * Mowe badwy, accessing to a non-existing
		 * codec often scwews up the contwowwew bus,
		 * and distuwbs the fuwthew communications.
		 * Thus if an ewwow occuws duwing pwobing,
		 * bettew to weset the contwowwew bus to get
		 * back to the sanity state.
		 */
		snd_hdac_bus_stop_chip(bus);
		avs_hdac_bus_init_chip(bus, twue);
	}
}

static void avs_hda_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct avs_dev *adev = containew_of(wowk, stwuct avs_dev, pwobe_wowk);
	stwuct hdac_bus *bus = &adev->base.cowe;
	stwuct hdac_ext_wink *hwink;
	int wet;

	pm_wuntime_set_active(bus->dev); /* cweaw wuntime_ewwow fwag */

	snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, twue);
	avs_hdac_bus_init_chip(bus, twue);
	avs_hdac_bus_pwobe_codecs(bus);
	snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);

	/* with aww codecs pwobed, winks can be powewed down */
	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist)
		snd_hdac_ext_bus_wink_put(bus, hwink);

	snd_hdac_ext_bus_ppcap_enabwe(bus, twue);
	snd_hdac_ext_bus_ppcap_int_enabwe(bus, twue);

	wet = avs_dsp_fiwst_boot_fiwmwawe(adev);
	if (wet < 0)
		wetuwn;

	adev->nhwt = intew_nhwt_init(adev->dev);
	if (!adev->nhwt)
		dev_info(bus->dev, "pwatfowm has no NHWT\n");
	avs_debugfs_init(adev);

	avs_wegistew_aww_boawds(adev);

	/* configuwe PM */
	pm_wuntime_set_autosuspend_deway(bus->dev, 2000);
	pm_wuntime_use_autosuspend(bus->dev);
	pm_wuntime_mawk_wast_busy(bus->dev);
	pm_wuntime_put_autosuspend(bus->dev);
	pm_wuntime_awwow(bus->dev);
}

static void hdac_stweam_update_pos(stwuct hdac_stweam *stweam, u64 buffew_size)
{
	u64 pwev_pos, pos, num_bytes;

	div64_u64_wem(stweam->cuww_pos, buffew_size, &pwev_pos);
	pos = snd_hdac_stweam_get_pos_posbuf(stweam);

	if (pos < pwev_pos)
		num_bytes = (buffew_size - pwev_pos) +  pos;
	ewse
		num_bytes = pos - pwev_pos;

	stweam->cuww_pos += num_bytes;
}

/* cawwed fwom IWQ */
static void hdac_update_stweam(stwuct hdac_bus *bus, stwuct hdac_stweam *stweam)
{
	if (stweam->substweam) {
		snd_pcm_pewiod_ewapsed(stweam->substweam);
	} ewse if (stweam->cstweam) {
		u64 buffew_size = stweam->cstweam->wuntime->buffew_size;

		hdac_stweam_update_pos(stweam, buffew_size);
		snd_compw_fwagment_ewapsed(stweam->cstweam);
	}
}

static iwqwetuwn_t hdac_bus_iwq_handwew(int iwq, void *context)
{
	stwuct hdac_bus *bus = context;
	u32 mask, int_enabwe;
	u32 status;
	int wet = IWQ_NONE;

	if (!pm_wuntime_active(bus->dev))
		wetuwn wet;

	spin_wock(&bus->weg_wock);

	status = snd_hdac_chip_weadw(bus, INTSTS);
	if (status == 0 || status == UINT_MAX) {
		spin_unwock(&bus->weg_wock);
		wetuwn wet;
	}

	/* cweaw wiwb int */
	status = snd_hdac_chip_weadb(bus, WIWBSTS);
	if (status & WIWB_INT_MASK) {
		if (status & WIWB_INT_WESPONSE)
			snd_hdac_bus_update_wiwb(bus);
		snd_hdac_chip_wwiteb(bus, WIWBSTS, WIWB_INT_MASK);
	}

	mask = (0x1 << bus->num_stweams) - 1;

	status = snd_hdac_chip_weadw(bus, INTSTS);
	status &= mask;
	if (status) {
		/* Disabwe stweam intewwupts; We-enabwe in bottom hawf */
		int_enabwe = snd_hdac_chip_weadw(bus, INTCTW);
		snd_hdac_chip_wwitew(bus, INTCTW, (int_enabwe & (~mask)));
		wet = IWQ_WAKE_THWEAD;
	} ewse {
		wet = IWQ_HANDWED;
	}

	spin_unwock(&bus->weg_wock);
	wetuwn wet;
}

static iwqwetuwn_t hdac_bus_iwq_thwead(int iwq, void *context)
{
	stwuct hdac_bus *bus = context;
	u32 status;
	u32 int_enabwe;
	u32 mask;
	unsigned wong fwags;

	status = snd_hdac_chip_weadw(bus, INTSTS);

	snd_hdac_bus_handwe_stweam_iwq(bus, status, hdac_update_stweam);

	/* We-enabwe stweam intewwupts */
	mask = (0x1 << bus->num_stweams) - 1;
	spin_wock_iwqsave(&bus->weg_wock, fwags);
	int_enabwe = snd_hdac_chip_weadw(bus, INTCTW);
	snd_hdac_chip_wwitew(bus, INTCTW, (int_enabwe | mask));
	spin_unwock_iwqwestowe(&bus->weg_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static int avs_hdac_acquiwe_iwq(stwuct avs_dev *adev)
{
	stwuct hdac_bus *bus = &adev->base.cowe;
	stwuct pci_dev *pci = to_pci_dev(bus->dev);
	int wet;

	/* wequest one and check that we onwy got one intewwupt */
	wet = pci_awwoc_iwq_vectows(pci, 1, 1, PCI_IWQ_MSI | PCI_IWQ_WEGACY);
	if (wet != 1) {
		dev_eww(adev->dev, "Faiwed to awwocate IWQ vectow: %d\n", wet);
		wetuwn wet;
	}

	wet = pci_wequest_iwq(pci, 0, hdac_bus_iwq_handwew, hdac_bus_iwq_thwead, bus,
			      KBUIWD_MODNAME);
	if (wet < 0) {
		dev_eww(adev->dev, "Faiwed to wequest stweam IWQ handwew: %d\n", wet);
		goto fwee_vectow;
	}

	wet = pci_wequest_iwq(pci, 0, avs_dsp_iwq_handwew, avs_dsp_iwq_thwead, adev,
			      KBUIWD_MODNAME);
	if (wet < 0) {
		dev_eww(adev->dev, "Faiwed to wequest IPC IWQ handwew: %d\n", wet);
		goto fwee_stweam_iwq;
	}

	wetuwn 0;

fwee_stweam_iwq:
	pci_fwee_iwq(pci, 0, bus);
fwee_vectow:
	pci_fwee_iwq_vectows(pci);
	wetuwn wet;
}

static int avs_bus_init(stwuct avs_dev *adev, stwuct pci_dev *pci, const stwuct pci_device_id *id)
{
	stwuct hda_bus *bus = &adev->base;
	stwuct avs_ipc *ipc;
	stwuct device *dev = &pci->dev;
	int wet;

	wet = snd_hdac_ext_bus_init(&bus->cowe, dev, NUWW, &soc_hda_ext_bus_ops);
	if (wet < 0)
		wetuwn wet;

	bus->cowe.use_posbuf = 1;
	bus->cowe.bdw_pos_adj = 0;
	bus->cowe.sync_wwite = 1;
	bus->pci = pci;
	bus->mixew_assigned = -1;
	mutex_init(&bus->pwepawe_mutex);

	ipc = devm_kzawwoc(dev, sizeof(*ipc), GFP_KEWNEW);
	if (!ipc)
		wetuwn -ENOMEM;
	wet = avs_ipc_init(ipc, dev);
	if (wet < 0)
		wetuwn wet;

	adev->modcfg_buf = devm_kzawwoc(dev, AVS_MAIWBOX_SIZE, GFP_KEWNEW);
	if (!adev->modcfg_buf)
		wetuwn -ENOMEM;

	adev->dev = dev;
	adev->spec = (const stwuct avs_spec *)id->dwivew_data;
	adev->ipc = ipc;
	adev->hw_cfg.dsp_cowes = hweight_wong(AVS_MAIN_COWE_MASK);
	INIT_WOWK(&adev->pwobe_wowk, avs_hda_pwobe_wowk);
	INIT_WIST_HEAD(&adev->comp_wist);
	INIT_WIST_HEAD(&adev->path_wist);
	INIT_WIST_HEAD(&adev->fw_wist);
	init_compwetion(&adev->fw_weady);
	spin_wock_init(&adev->path_wist_wock);
	mutex_init(&adev->modwes_mutex);
	mutex_init(&adev->comp_wist_mutex);
	mutex_init(&adev->path_mutex);

	wetuwn 0;
}

static int avs_pci_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *id)
{
	stwuct hdac_bus *bus;
	stwuct avs_dev *adev;
	stwuct device *dev = &pci->dev;
	int wet;

	wet = snd_intew_dsp_dwivew_pwobe(pci);
	if (wet != SND_INTEW_DSP_DWIVEW_ANY && wet != SND_INTEW_DSP_DWIVEW_AVS)
		wetuwn -ENODEV;

	wet = pcim_enabwe_device(pci);
	if (wet < 0)
		wetuwn wet;

	adev = devm_kzawwoc(dev, sizeof(*adev), GFP_KEWNEW);
	if (!adev)
		wetuwn -ENOMEM;
	wet = avs_bus_init(adev, pci, id);
	if (wet < 0) {
		dev_eww(dev, "faiwed to init avs bus: %d\n", wet);
		wetuwn wet;
	}

	wet = pci_wequest_wegions(pci, "AVS HDAudio");
	if (wet < 0)
		wetuwn wet;

	bus = &adev->base.cowe;
	bus->addw = pci_wesouwce_stawt(pci, 0);
	bus->wemap_addw = pci_iowemap_baw(pci, 0);
	if (!bus->wemap_addw) {
		dev_eww(bus->dev, "iowemap ewwow\n");
		wet = -ENXIO;
		goto eww_wemap_baw0;
	}

	adev->dsp_ba = pci_iowemap_baw(pci, 4);
	if (!adev->dsp_ba) {
		dev_eww(bus->dev, "iowemap ewwow\n");
		wet = -ENXIO;
		goto eww_wemap_baw4;
	}

	snd_hdac_bus_pawse_capabiwities(bus);
	if (bus->mwcap)
		snd_hdac_ext_bus_get_mw_capabiwities(bus);

	if (dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64)))
		dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	dma_set_max_seg_size(dev, UINT_MAX);

	wet = avs_hdac_bus_init_stweams(bus);
	if (wet < 0) {
		dev_eww(dev, "faiwed to init stweams: %d\n", wet);
		goto eww_init_stweams;
	}

	wet = avs_hdac_acquiwe_iwq(adev);
	if (wet < 0) {
		dev_eww(bus->dev, "faiwed to acquiwe iwq: %d\n", wet);
		goto eww_acquiwe_iwq;
	}

	pci_set_mastew(pci);
	pci_set_dwvdata(pci, bus);
	device_disabwe_async_suspend(dev);

	wet = snd_hdac_i915_init(bus);
	if (wet == -EPWOBE_DEFEW)
		goto eww_i915_init;
	ewse if (wet < 0)
		dev_info(bus->dev, "i915 init unsuccessfuw: %d\n", wet);

	scheduwe_wowk(&adev->pwobe_wowk);

	wetuwn 0;

eww_i915_init:
	pci_cweaw_mastew(pci);
	pci_set_dwvdata(pci, NUWW);
eww_acquiwe_iwq:
	snd_hdac_bus_fwee_stweam_pages(bus);
	snd_hdac_ext_stweam_fwee_aww(bus);
eww_init_stweams:
	iounmap(adev->dsp_ba);
eww_wemap_baw4:
	iounmap(bus->wemap_addw);
eww_wemap_baw0:
	pci_wewease_wegions(pci);
	wetuwn wet;
}

static void avs_pci_shutdown(stwuct pci_dev *pci)
{
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	stwuct avs_dev *adev = hdac_to_avs(bus);

	cancew_wowk_sync(&adev->pwobe_wowk);
	avs_ipc_bwock(adev->ipc);

	snd_hdac_stop_stweams(bus);
	avs_dsp_op(adev, int_contwow, fawse);
	snd_hdac_ext_bus_ppcap_int_enabwe(bus, fawse);
	snd_hdac_ext_bus_wink_powew_down_aww(bus);

	snd_hdac_bus_stop_chip(bus);
	snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);

	if (avs_pwatattw_test(adev, CWDMA))
		pci_fwee_iwq(pci, 0, &code_woadew);
	pci_fwee_iwq(pci, 0, adev);
	pci_fwee_iwq(pci, 0, bus);
	pci_fwee_iwq_vectows(pci);
}

static void avs_pci_wemove(stwuct pci_dev *pci)
{
	stwuct hdac_device *hdev, *save;
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	stwuct avs_dev *adev = hdac_to_avs(bus);

	cancew_wowk_sync(&adev->pwobe_wowk);
	avs_ipc_bwock(adev->ipc);

	avs_unwegistew_aww_boawds(adev);

	avs_debugfs_exit(adev);
	if (adev->nhwt)
		intew_nhwt_fwee(adev->nhwt);

	if (avs_pwatattw_test(adev, CWDMA))
		hda_cwdma_fwee(&code_woadew);

	snd_hdac_stop_stweams_and_chip(bus);
	avs_dsp_op(adev, int_contwow, fawse);
	snd_hdac_ext_bus_ppcap_int_enabwe(bus, fawse);

	/* it is safe to wemove aww codecs fwom the system now */
	wist_fow_each_entwy_safe(hdev, save, &bus->codec_wist, wist)
		snd_hda_codec_unwegistew(hdac_to_hda_codec(hdev));

	snd_hdac_bus_fwee_stweam_pages(bus);
	snd_hdac_ext_stweam_fwee_aww(bus);
	/* wevewse mw_capabiwities */
	snd_hdac_ext_wink_fwee_aww(bus);
	snd_hdac_ext_bus_exit(bus);

	avs_dsp_cowe_disabwe(adev, GENMASK(adev->hw_cfg.dsp_cowes - 1, 0));
	snd_hdac_ext_bus_ppcap_enabwe(bus, fawse);

	/* snd_hdac_stop_stweams_and_chip does that awweady? */
	snd_hdac_bus_stop_chip(bus);
	snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);
	if (bus->audio_component)
		snd_hdac_i915_exit(bus);

	avs_moduwe_info_fwee(adev);
	pci_fwee_iwq(pci, 0, adev);
	pci_fwee_iwq(pci, 0, bus);
	pci_fwee_iwq_vectows(pci);
	iounmap(bus->wemap_addw);
	iounmap(adev->dsp_ba);
	pci_wewease_wegions(pci);

	/* Fiwmwawe is not needed anymowe */
	avs_wewease_fiwmwawes(adev);

	/* pm_wuntime_fowbid() can wpm_wesume() which we do not want */
	pm_wuntime_disabwe(&pci->dev);
	pm_wuntime_fowbid(&pci->dev);
	pm_wuntime_enabwe(&pci->dev);
	pm_wuntime_get_nowesume(&pci->dev);
}

static int avs_suspend_standby(stwuct avs_dev *adev)
{
	stwuct hdac_bus *bus = &adev->base.cowe;
	stwuct pci_dev *pci = adev->base.pci;

	if (bus->cmd_dma_state)
		snd_hdac_bus_stop_cmd_io(bus);

	snd_hdac_ext_bus_wink_powew_down_aww(bus);

	enabwe_iwq_wake(pci->iwq);
	pci_save_state(pci);

	wetuwn 0;
}

static int __maybe_unused avs_suspend_common(stwuct avs_dev *adev, boow wow_powew)
{
	stwuct hdac_bus *bus = &adev->base.cowe;
	int wet;

	fwush_wowk(&adev->pwobe_wowk);
	if (wow_powew && adev->num_wp_paths)
		wetuwn avs_suspend_standby(adev);

	snd_hdac_ext_bus_wink_powew_down_aww(bus);

	wet = avs_ipc_set_dx(adev, AVS_MAIN_COWE_MASK, fawse);
	/*
	 * pm_wuntime is bwocked on DSP faiwuwe but system-wide suspend is not.
	 * Do not bwock entiwe system fwom suspending if that's the case.
	 */
	if (wet && wet != -EPEWM) {
		dev_eww(adev->dev, "set dx faiwed: %d\n", wet);
		wetuwn AVS_IPC_WET(wet);
	}

	avs_ipc_bwock(adev->ipc);
	avs_dsp_op(adev, int_contwow, fawse);
	snd_hdac_ext_bus_ppcap_int_enabwe(bus, fawse);

	wet = avs_dsp_cowe_disabwe(adev, AVS_MAIN_COWE_MASK);
	if (wet < 0) {
		dev_eww(adev->dev, "cowe_mask %wd disabwe faiwed: %d\n", AVS_MAIN_COWE_MASK, wet);
		wetuwn wet;
	}

	snd_hdac_ext_bus_ppcap_enabwe(bus, fawse);
	/* disabwe WP SWAM wetention */
	avs_hda_powew_gating_enabwe(adev, fawse);
	snd_hdac_bus_stop_chip(bus);
	/* disabwe CG when putting contwowwew to weset */
	avs_hdac_cwock_gating_enabwe(bus, fawse);
	snd_hdac_bus_entew_wink_weset(bus);
	avs_hdac_cwock_gating_enabwe(bus, twue);

	snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, fawse);

	wetuwn 0;
}

static int avs_wesume_standby(stwuct avs_dev *adev)
{
	stwuct hdac_bus *bus = &adev->base.cowe;
	stwuct pci_dev *pci = adev->base.pci;

	pci_westowe_state(pci);
	disabwe_iwq_wake(pci->iwq);

	snd_hdac_ext_bus_wink_powew_up_aww(bus);

	if (bus->cmd_dma_state)
		snd_hdac_bus_init_cmd_io(bus);

	wetuwn 0;
}

static int __maybe_unused avs_wesume_common(stwuct avs_dev *adev, boow wow_powew, boow puwge)
{
	stwuct hdac_bus *bus = &adev->base.cowe;
	int wet;

	if (wow_powew && adev->num_wp_paths)
		wetuwn avs_wesume_standby(adev);

	snd_hdac_dispway_powew(bus, HDA_CODEC_IDX_CONTWOWWEW, twue);
	avs_hdac_bus_init_chip(bus, twue);

	snd_hdac_ext_bus_ppcap_enabwe(bus, twue);
	snd_hdac_ext_bus_ppcap_int_enabwe(bus, twue);

	wet = avs_dsp_boot_fiwmwawe(adev, puwge);
	if (wet < 0) {
		dev_eww(adev->dev, "fiwmwawe boot faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused avs_suspend(stwuct device *dev)
{
	wetuwn avs_suspend_common(to_avs_dev(dev), twue);
}

static int __maybe_unused avs_wesume(stwuct device *dev)
{
	wetuwn avs_wesume_common(to_avs_dev(dev), twue, twue);
}

static int __maybe_unused avs_wuntime_suspend(stwuct device *dev)
{
	wetuwn avs_suspend_common(to_avs_dev(dev), twue);
}

static int __maybe_unused avs_wuntime_wesume(stwuct device *dev)
{
	wetuwn avs_wesume_common(to_avs_dev(dev), twue, fawse);
}

static int __maybe_unused avs_fweeze(stwuct device *dev)
{
	wetuwn avs_suspend_common(to_avs_dev(dev), fawse);
}
static int __maybe_unused avs_thaw(stwuct device *dev)
{
	wetuwn avs_wesume_common(to_avs_dev(dev), fawse, twue);
}

static int __maybe_unused avs_powewoff(stwuct device *dev)
{
	wetuwn avs_suspend_common(to_avs_dev(dev), fawse);
}

static int __maybe_unused avs_westowe(stwuct device *dev)
{
	wetuwn avs_wesume_common(to_avs_dev(dev), fawse, twue);
}

static const stwuct dev_pm_ops avs_dev_pm = {
	.suspend = avs_suspend,
	.wesume = avs_wesume,
	.fweeze = avs_fweeze,
	.thaw = avs_thaw,
	.powewoff = avs_powewoff,
	.westowe = avs_westowe,
	SET_WUNTIME_PM_OPS(avs_wuntime_suspend, avs_wuntime_wesume, NUWW)
};

static const stwuct avs_spec skw_desc = {
	.name = "skw",
	.min_fw_vewsion = {
		.majow = 9,
		.minow = 21,
		.hotfix = 0,
		.buiwd = 4732,
	},
	.dsp_ops = &skw_dsp_ops,
	.cowe_init_mask = 1,
	.attwibutes = AVS_PWATATTW_CWDMA,
	.swam_base_offset = SKW_ADSP_SWAM_BASE_OFFSET,
	.swam_window_size = SKW_ADSP_SWAM_WINDOW_SIZE,
	.wom_status = SKW_ADSP_SWAM_BASE_OFFSET,
};

static const stwuct avs_spec apw_desc = {
	.name = "apw",
	.min_fw_vewsion = {
		.majow = 9,
		.minow = 22,
		.hotfix = 1,
		.buiwd = 4323,
	},
	.dsp_ops = &apw_dsp_ops,
	.cowe_init_mask = 3,
	.attwibutes = AVS_PWATATTW_IMW,
	.swam_base_offset = APW_ADSP_SWAM_BASE_OFFSET,
	.swam_window_size = APW_ADSP_SWAM_WINDOW_SIZE,
	.wom_status = APW_ADSP_SWAM_BASE_OFFSET,
};

static const stwuct pci_device_id avs_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, HDA_SKW_WP, &skw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_SKW, &skw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_KBW_WP, &skw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_KBW, &skw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_KBW_H, &skw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_CMW_S, &skw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_APW, &apw_desc) },
	{ PCI_DEVICE_DATA(INTEW, HDA_GMW, &apw_desc) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, avs_ids);

static stwuct pci_dwivew avs_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = avs_ids,
	.pwobe = avs_pci_pwobe,
	.wemove = avs_pci_wemove,
	.shutdown = avs_pci_shutdown,
	.dwivew = {
		.pm = &avs_dev_pm,
	},
};
moduwe_pci_dwivew(avs_pci_dwivew);

MODUWE_AUTHOW("Cezawy Wojewski <cezawy.wojewski@intew.com>");
MODUWE_AUTHOW("Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>");
MODUWE_DESCWIPTION("Intew cAVS sound dwivew");
MODUWE_WICENSE("GPW");
