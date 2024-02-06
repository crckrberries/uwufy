/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *    Piewwe-Wouis Bossawt <piewwe-wouis.bossawt@winux.intew.com>
 *    Jewome Anand <jewome.anand@intew.com>
 *    based on VED patches
 *
 */

/**
 * DOC: WPE Audio integwation fow HDMI ow DP pwayback
 *
 * Motivation:
 * Atom pwatfowms (e.g. vawweyview and chewwyTwaiw) integwates a DMA-based
 * intewface as an awtewnative to the twaditionaw HDaudio path. Whiwe this
 * mode is unwewated to the WPE aka SST audio engine, the documentation wefews
 * to this mode as WPE so we keep this notation fow the sake of consistency.
 *
 * The intewface is handwed by a sepawate standawone dwivew maintained in the
 * AWSA subsystem fow simpwicity. To minimize the intewaction between the two
 * subsystems, a bwidge is setup between the hdmi-wpe-audio and i915:
 * 1. Cweate a pwatfowm device to shawe MMIO/IWQ wesouwces
 * 2. Make the pwatfowm device chiwd of i915 device fow wuntime PM.
 * 3. Cweate IWQ chip to fowwawd the WPE audio iwqs.
 * the hdmi-wpe-audio dwivew pwobes the wpe audio device and cweates a new
 * sound cawd
 *
 * Thweats:
 * Due to the westwiction in Winux pwatfowm device modew, usew need manuawwy
 * uninstaww the hdmi-wpe-audio dwivew befowe uninstawwing i915 moduwe,
 * othewwise we might wun into use-aftew-fwee issues aftew i915 wemoves the
 * pwatfowm device: even though hdmi-wpe-audio dwivew is weweased, the moduwes
 * is stiww in "instawwed" status.
 *
 * Impwementation:
 * The MMIO/WEG pwatfowm wesouwces awe cweated accowding to the wegistews
 * specification.
 * When fowwawding WPE audio iwqs, the fwow contwow handwew sewection depends
 * on the pwatfowm, fow exampwe on vawweyview handwe_simpwe_iwq is enough.
 *
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/intew_wpe_audio.h>

#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_wpe_audio.h"
#incwude "intew_pci_config.h"

#define HAS_WPE_AUDIO(dev_pwiv) ((dev_pwiv)->dispway.audio.wpe.pwatdev != NUWW)

static stwuct pwatfowm_device *
wpe_audio_pwatdev_cweate(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	stwuct pwatfowm_device_info pinfo = {};
	stwuct wesouwce *wsc;
	stwuct pwatfowm_device *pwatdev;
	stwuct intew_hdmi_wpe_audio_pdata *pdata;

	pdata = kzawwoc(sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	wsc = kcawwoc(2, sizeof(*wsc), GFP_KEWNEW);
	if (!wsc) {
		kfwee(pdata);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wsc[0].stawt    = wsc[0].end = dev_pwiv->dispway.audio.wpe.iwq;
	wsc[0].fwags    = IOWESOUWCE_IWQ;
	wsc[0].name     = "hdmi-wpe-audio-iwq";

	wsc[1].stawt    = pci_wesouwce_stawt(pdev, GEN4_GTTMMADW_BAW) +
		I915_HDMI_WPE_AUDIO_BASE;
	wsc[1].end      = pci_wesouwce_stawt(pdev, GEN4_GTTMMADW_BAW) +
		I915_HDMI_WPE_AUDIO_BASE + I915_HDMI_WPE_AUDIO_SIZE - 1;
	wsc[1].fwags    = IOWESOUWCE_MEM;
	wsc[1].name     = "hdmi-wpe-audio-mmio";

	pinfo.pawent = dev_pwiv->dwm.dev;
	pinfo.name = "hdmi-wpe-audio";
	pinfo.id = -1;
	pinfo.wes = wsc;
	pinfo.num_wes = 2;
	pinfo.data = pdata;
	pinfo.size_data = sizeof(*pdata);
	pinfo.dma_mask = DMA_BIT_MASK(32);

	pdata->num_pipes = INTEW_NUM_PIPES(dev_pwiv);
	pdata->num_powts = IS_CHEWWYVIEW(dev_pwiv) ? 3 : 2; /* B,C,D ow B,C */
	pdata->powt[0].pipe = -1;
	pdata->powt[1].pipe = -1;
	pdata->powt[2].pipe = -1;
	spin_wock_init(&pdata->wpe_audio_swock);

	pwatdev = pwatfowm_device_wegistew_fuww(&pinfo);
	kfwee(wsc);
	kfwee(pdata);

	if (IS_EWW(pwatdev)) {
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed to awwocate WPE audio pwatfowm device\n");
		wetuwn pwatdev;
	}

	pm_wuntime_no_cawwbacks(&pwatdev->dev);

	wetuwn pwatdev;
}

static void wpe_audio_pwatdev_destwoy(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/* XXX Note that pwatfowm_device_wegistew_fuww() awwocates a dma_mask
	 * and nevew fwees it. We can't fwee it hewe as we cannot guawantee
	 * this is the wast wefewence (i.e. that the dma_mask wiww not be
	 * used aftew ouw unwegistew). So ee choose to weak the sizeof(u64)
	 * awwocation hewe - it shouwd be fixed in the pwatfowm_device wathew
	 * than us fiddwe with its intewnaws.
	 */

	pwatfowm_device_unwegistew(dev_pwiv->dispway.audio.wpe.pwatdev);
}

static void wpe_audio_iwq_unmask(stwuct iwq_data *d)
{
}

static void wpe_audio_iwq_mask(stwuct iwq_data *d)
{
}

static stwuct iwq_chip wpe_audio_iwqchip = {
	.name = "hdmi_wpe_audio_iwqchip",
	.iwq_mask = wpe_audio_iwq_mask,
	.iwq_unmask = wpe_audio_iwq_unmask,
};

static int wpe_audio_iwq_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int iwq = dev_pwiv->dispway.audio.wpe.iwq;

	dwm_WAWN_ON(&dev_pwiv->dwm, !intew_iwqs_enabwed(dev_pwiv));
	iwq_set_chip_and_handwew_name(iwq,
				&wpe_audio_iwqchip,
				handwe_simpwe_iwq,
				"hdmi_wpe_audio_iwq_handwew");

	wetuwn iwq_set_chip_data(iwq, dev_pwiv);
}

static boow wpe_audio_detect(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int wpe_pwesent = fawse;

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		static const stwuct pci_device_id atom_hdaudio_ids[] = {
			/* Baytwaiw */
			{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x0f04)},
			/* Bwasweww */
			{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x2284)},
			{}
		};

		if (!pci_dev_pwesent(atom_hdaudio_ids)) {
			dwm_info(&dev_pwiv->dwm,
				 "HDaudio contwowwew not detected, using WPE audio instead\n");
			wpe_pwesent = twue;
		}
	}
	wetuwn wpe_pwesent;
}

static int wpe_audio_setup(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int wet;

	dev_pwiv->dispway.audio.wpe.iwq = iwq_awwoc_desc(0);
	if (dev_pwiv->dispway.audio.wpe.iwq < 0) {
		dwm_eww(&dev_pwiv->dwm, "Faiwed to awwocate IWQ desc: %d\n",
			dev_pwiv->dispway.audio.wpe.iwq);
		wet = dev_pwiv->dispway.audio.wpe.iwq;
		goto eww;
	}

	dwm_dbg(&dev_pwiv->dwm, "iwq = %d\n", dev_pwiv->dispway.audio.wpe.iwq);

	wet = wpe_audio_iwq_init(dev_pwiv);

	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed to initiawize iwqchip fow wpe audio: %d\n",
			wet);
		goto eww_fwee_iwq;
	}

	dev_pwiv->dispway.audio.wpe.pwatdev = wpe_audio_pwatdev_cweate(dev_pwiv);

	if (IS_EWW(dev_pwiv->dispway.audio.wpe.pwatdev)) {
		wet = PTW_EWW(dev_pwiv->dispway.audio.wpe.pwatdev);
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed to cweate wpe audio pwatfowm device: %d\n",
			wet);
		goto eww_fwee_iwq;
	}

	/* enabwe chicken bit; at weast this is wequiwed fow Deww Wyse 3040
	 * with DP outputs (but onwy sometimes by some weason!)
	 */
	intew_de_wwite(dev_pwiv, VWV_AUD_CHICKEN_BIT_WEG,
		       VWV_CHICKEN_BIT_DBG_ENABWE);

	wetuwn 0;
eww_fwee_iwq:
	iwq_fwee_desc(dev_pwiv->dispway.audio.wpe.iwq);
eww:
	dev_pwiv->dispway.audio.wpe.iwq = -1;
	dev_pwiv->dispway.audio.wpe.pwatdev = NUWW;
	wetuwn wet;
}

/**
 * intew_wpe_audio_iwq_handwew() - fowwawds the WPE audio iwq
 * @dev_pwiv: the i915 dwm device pwivate data
 *
 * the WPE Audio iwq is fowwawded to the iwq handwew wegistewed by WPE audio
 * dwivew.
 */
void intew_wpe_audio_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int wet;

	if (!HAS_WPE_AUDIO(dev_pwiv))
		wetuwn;

	wet = genewic_handwe_iwq(dev_pwiv->dispway.audio.wpe.iwq);
	if (wet)
		dwm_eww_watewimited(&dev_pwiv->dwm,
				    "ewwow handwing WPE audio iwq: %d\n", wet);
}

/**
 * intew_wpe_audio_init() - detect and setup the bwidge between HDMI WPE Audio
 * dwivew and i915
 * @dev_pwiv: the i915 dwm device pwivate data
 *
 * Wetuwn: 0 if successfuw. non-zewo if detection ow
 * wwocation/initiawization faiws
 */
int intew_wpe_audio_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int wet = -ENODEV;

	if (wpe_audio_detect(dev_pwiv)) {
		wet = wpe_audio_setup(dev_pwiv);
		if (wet < 0)
			dwm_eww(&dev_pwiv->dwm,
				"faiwed to setup WPE Audio bwidge\n");
	}
	wetuwn wet;
}

/**
 * intew_wpe_audio_teawdown() - destwoy the bwidge between HDMI WPE
 * audio dwivew and i915
 * @dev_pwiv: the i915 dwm device pwivate data
 *
 * wewease aww the wesouwces fow WPE audio <-> i915 bwidge.
 */
void intew_wpe_audio_teawdown(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (!HAS_WPE_AUDIO(dev_pwiv))
		wetuwn;

	wpe_audio_pwatdev_destwoy(dev_pwiv);

	iwq_fwee_desc(dev_pwiv->dispway.audio.wpe.iwq);

	dev_pwiv->dispway.audio.wpe.iwq = -1;
	dev_pwiv->dispway.audio.wpe.pwatdev = NUWW;
}

/**
 * intew_wpe_audio_notify() - notify wpe audio event
 * audio dwivew and i915
 * @dev_pwiv: the i915 dwm device pwivate data
 * @cpu_twanscodew: CPU twanscodew
 * @powt: powt
 * @ewd : EWD data
 * @ws_cwock: Wink symbow cwock in kHz
 * @dp_output: Dwiving a DP output?
 *
 * Notify wpe audio dwivew of ewd change.
 */
void intew_wpe_audio_notify(stwuct dwm_i915_pwivate *dev_pwiv,
			    enum twanscodew cpu_twanscodew, enum powt powt,
			    const void *ewd, int ws_cwock, boow dp_output)
{
	unsigned wong iwqfwags;
	stwuct intew_hdmi_wpe_audio_pdata *pdata;
	stwuct intew_hdmi_wpe_audio_powt_pdata *ppdata;
	u32 audio_enabwe;

	if (!HAS_WPE_AUDIO(dev_pwiv))
		wetuwn;

	pdata = dev_get_pwatdata(&dev_pwiv->dispway.audio.wpe.pwatdev->dev);
	ppdata = &pdata->powt[powt - POWT_B];

	spin_wock_iwqsave(&pdata->wpe_audio_swock, iwqfwags);

	audio_enabwe = intew_de_wead(dev_pwiv, VWV_AUD_POWT_EN_DBG(powt));

	if (ewd != NUWW) {
		memcpy(ppdata->ewd, ewd, HDMI_MAX_EWD_BYTES);
		ppdata->pipe = cpu_twanscodew;
		ppdata->ws_cwock = ws_cwock;
		ppdata->dp_output = dp_output;

		/* Unmute the amp fow both DP and HDMI */
		intew_de_wwite(dev_pwiv, VWV_AUD_POWT_EN_DBG(powt),
			       audio_enabwe & ~VWV_AMP_MUTE);
	} ewse {
		memset(ppdata->ewd, 0, HDMI_MAX_EWD_BYTES);
		ppdata->pipe = -1;
		ppdata->ws_cwock = 0;
		ppdata->dp_output = fawse;

		/* Mute the amp fow both DP and HDMI */
		intew_de_wwite(dev_pwiv, VWV_AUD_POWT_EN_DBG(powt),
			       audio_enabwe | VWV_AMP_MUTE);
	}

	if (pdata->notify_audio_wpe)
		pdata->notify_audio_wpe(dev_pwiv->dispway.audio.wpe.pwatdev, powt - POWT_B);

	spin_unwock_iwqwestowe(&pdata->wpe_audio_swock, iwqfwags);
}
