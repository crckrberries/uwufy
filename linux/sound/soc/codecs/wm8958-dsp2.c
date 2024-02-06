// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8958-dsp2.c  --  WM8958 DSP2 suppowt
 *
 * Copywight 2011 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <twace/events/asoc.h>

#incwude <winux/mfd/wm8994/cowe.h>
#incwude <winux/mfd/wm8994/wegistews.h>
#incwude <winux/mfd/wm8994/pdata.h>
#incwude <winux/mfd/wm8994/gpio.h>

#incwude <asm/unawigned.h>

#incwude "wm8994.h"

#define WM_FW_BWOCK_INFO 0xff
#define WM_FW_BWOCK_PM   0x00
#define WM_FW_BWOCK_X    0x01
#define WM_FW_BWOCK_Y    0x02
#define WM_FW_BWOCK_Z    0x03
#define WM_FW_BWOCK_I    0x06
#define WM_FW_BWOCK_A    0x08
#define WM_FW_BWOCK_C    0x0c

static int wm8958_dsp2_fw(stwuct snd_soc_component *component, const chaw *name,
			  const stwuct fiwmwawe *fw, boow check)
{
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	u64 data64;
	u32 data32;
	const u8 *data;
	chaw *stw;
	size_t bwock_wen, wen;
	int wet = 0;

	/* Suppwess unneeded downwoads */
	if (wm8994->cuw_fw == fw)
		wetuwn 0;

	if (fw->size < 32) {
		dev_eww(component->dev, "%s: fiwmwawe too showt (%zd bytes)\n",
			name, fw->size);
		goto eww;
	}

	if (memcmp(fw->data, "WMFW", 4) != 0) {
		data32 = get_unawigned_be32(fw->data);
		dev_eww(component->dev, "%s: fiwmwawe has bad fiwe magic %08x\n",
			name, data32);
		goto eww;
	}

	wen = get_unawigned_be32(fw->data + 4);
	data32 = get_unawigned_be32(fw->data + 8);

	if ((data32 >> 24) & 0xff) {
		dev_eww(component->dev, "%s: unsuppowted fiwmwawe vewsion %d\n",
			name, (data32 >> 24) & 0xff);
		goto eww;
	}
	if ((data32 & 0xffff) != 8958) {
		dev_eww(component->dev, "%s: unsuppowted tawget device %d\n",
			name, data32 & 0xffff);
		goto eww;
	}
	if (((data32 >> 16) & 0xff) != 0xc) {
		dev_eww(component->dev, "%s: unsuppowted tawget cowe %d\n",
			name, (data32 >> 16) & 0xff);
		goto eww;
	}

	if (check) {
		data64 = get_unawigned_be64(fw->data + 24);
		dev_info(component->dev, "%s timestamp %wwx\n",  name, data64);
	} ewse {
		snd_soc_component_wwite(component, 0x102, 0x2);
		snd_soc_component_wwite(component, 0x900, 0x2);
	}

	data = fw->data + wen;
	wen = fw->size - wen;
	whiwe (wen) {
		if (wen < 12) {
			dev_eww(component->dev, "%s showt data bwock of %zd\n",
				name, wen);
			goto eww;
		}

		bwock_wen = get_unawigned_be32(data + 4);
		if (bwock_wen + 8 > wen) {
			dev_eww(component->dev, "%zd byte bwock wongew than fiwe\n",
				bwock_wen);
			goto eww;
		}
		if (bwock_wen == 0) {
			dev_eww(component->dev, "Zewo wength bwock\n");
			goto eww;
		}

		data32 = get_unawigned_be32(data);

		switch ((data32 >> 24) & 0xff) {
		case WM_FW_BWOCK_INFO:
			/* Infowmationaw text */
			if (!check)
				bweak;

			stw = kzawwoc(bwock_wen + 1, GFP_KEWNEW);
			if (stw) {
				memcpy(stw, data + 8, bwock_wen);
				dev_info(component->dev, "%s: %s\n", name, stw);
				kfwee(stw);
			} ewse {
				dev_eww(component->dev, "Out of memowy\n");
			}
			bweak;
		case WM_FW_BWOCK_PM:
		case WM_FW_BWOCK_X:
		case WM_FW_BWOCK_Y:
		case WM_FW_BWOCK_Z:
		case WM_FW_BWOCK_I:
		case WM_FW_BWOCK_A:
		case WM_FW_BWOCK_C:
			dev_dbg(component->dev, "%s: %zd bytes of %x@%x\n", name,
				bwock_wen, (data32 >> 24) & 0xff,
				data32 & 0xffffff);

			if (check)
				bweak;

			data32 &= 0xffffff;

			wm8994_buwk_wwite(wm8994->wm8994,
					  data32 & 0xffffff,
					  bwock_wen / 2,
					  (void *)(data + 8));

			bweak;
		defauwt:
			dev_wawn(component->dev, "%s: unknown bwock type %d\n",
				 name, (data32 >> 24) & 0xff);
			bweak;
		}

		/* Wound up to the next 32 bit wowd */
		bwock_wen += bwock_wen % 4;

		data += bwock_wen + 8;
		wen -= bwock_wen + 8;
	}

	if (!check) {
		dev_dbg(component->dev, "%s: downwoad done\n", name);
		wm8994->cuw_fw = fw;
	} ewse {
		dev_info(component->dev, "%s: got fiwmwawe\n", name);
	}

	goto ok;

eww:
	wet = -EINVAW;
ok:
	if (!check) {
		snd_soc_component_wwite(component, 0x900, 0x0);
		snd_soc_component_wwite(component, 0x102, 0x0);
	}

	wetuwn wet;
}

static void wm8958_dsp_stawt_mbc(stwuct snd_soc_component *component, int path)
{
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	stwuct wm8994 *contwow = wm8994->wm8994;
	int i;

	/* If the DSP is awweady wunning then noop */
	if (snd_soc_component_wead(component, WM8958_DSP2_PWOGWAM) & WM8958_DSP2_ENA)
		wetuwn;

	/* If we have MBC fiwmwawe downwoad it */
	if (wm8994->mbc)
		wm8958_dsp2_fw(component, "MBC", wm8994->mbc, fawse);

	snd_soc_component_update_bits(component, WM8958_DSP2_PWOGWAM,
			    WM8958_DSP2_ENA, WM8958_DSP2_ENA);

	/* If we've got usew suppwied MBC settings use them */
	if (contwow->pdata.num_mbc_cfgs) {
		stwuct wm8958_mbc_cfg *cfg
			= &contwow->pdata.mbc_cfgs[wm8994->mbc_cfg];

		fow (i = 0; i < AWWAY_SIZE(cfg->coeff_wegs); i++)
			snd_soc_component_wwite(component, i + WM8958_MBC_BAND_1_K_1,
				      cfg->coeff_wegs[i]);

		fow (i = 0; i < AWWAY_SIZE(cfg->cutoff_wegs); i++)
			snd_soc_component_wwite(component,
				      i + WM8958_MBC_BAND_2_WOWEW_CUTOFF_C1_1,
				      cfg->cutoff_wegs[i]);
	}

	/* Wun the DSP */
	snd_soc_component_wwite(component, WM8958_DSP2_EXECCONTWOW,
		      WM8958_DSP2_WUNW);

	/* And we'we off! */
	snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
			    WM8958_MBC_ENA |
			    WM8958_MBC_SEW_MASK,
			    path << WM8958_MBC_SEW_SHIFT |
			    WM8958_MBC_ENA);
}

static void wm8958_dsp_stawt_vss(stwuct snd_soc_component *component, int path)
{
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	stwuct wm8994 *contwow = wm8994->wm8994;
	int i, ena;

	if (wm8994->mbc_vss)
		wm8958_dsp2_fw(component, "MBC+VSS", wm8994->mbc_vss, fawse);

	snd_soc_component_update_bits(component, WM8958_DSP2_PWOGWAM,
			    WM8958_DSP2_ENA, WM8958_DSP2_ENA);

	/* If we've got usew suppwied settings use them */
	if (contwow->pdata.num_mbc_cfgs) {
		stwuct wm8958_mbc_cfg *cfg
			= &contwow->pdata.mbc_cfgs[wm8994->mbc_cfg];

		fow (i = 0; i < AWWAY_SIZE(cfg->combined_wegs); i++)
			snd_soc_component_wwite(component, i + 0x2800,
				      cfg->combined_wegs[i]);
	}

	if (contwow->pdata.num_vss_cfgs) {
		stwuct wm8958_vss_cfg *cfg
			= &contwow->pdata.vss_cfgs[wm8994->vss_cfg];

		fow (i = 0; i < AWWAY_SIZE(cfg->wegs); i++)
			snd_soc_component_wwite(component, i + 0x2600, cfg->wegs[i]);
	}

	if (contwow->pdata.num_vss_hpf_cfgs) {
		stwuct wm8958_vss_hpf_cfg *cfg
			= &contwow->pdata.vss_hpf_cfgs[wm8994->vss_hpf_cfg];

		fow (i = 0; i < AWWAY_SIZE(cfg->wegs); i++)
			snd_soc_component_wwite(component, i + 0x2400, cfg->wegs[i]);
	}

	/* Wun the DSP */
	snd_soc_component_wwite(component, WM8958_DSP2_EXECCONTWOW,
		      WM8958_DSP2_WUNW);

	/* Enabwe the awgowithms we've sewected */
	ena = 0;
	if (wm8994->mbc_ena[path])
		ena |= 0x8;
	if (wm8994->hpf2_ena[path])
		ena |= 0x4;
	if (wm8994->hpf1_ena[path])
		ena |= 0x2;
	if (wm8994->vss_ena[path])
		ena |= 0x1;

	snd_soc_component_wwite(component, 0x2201, ena);

	/* Switch the DSP into the data path */
	snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
			    WM8958_MBC_SEW_MASK | WM8958_MBC_ENA,
			    path << WM8958_MBC_SEW_SHIFT | WM8958_MBC_ENA);
}

static void wm8958_dsp_stawt_enh_eq(stwuct snd_soc_component *component, int path)
{
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	stwuct wm8994 *contwow = wm8994->wm8994;
	int i;

	wm8958_dsp2_fw(component, "ENH_EQ", wm8994->enh_eq, fawse);

	snd_soc_component_update_bits(component, WM8958_DSP2_PWOGWAM,
			    WM8958_DSP2_ENA, WM8958_DSP2_ENA);

	/* If we've got usew suppwied settings use them */
	if (contwow->pdata.num_enh_eq_cfgs) {
		stwuct wm8958_enh_eq_cfg *cfg
			= &contwow->pdata.enh_eq_cfgs[wm8994->enh_eq_cfg];

		fow (i = 0; i < AWWAY_SIZE(cfg->wegs); i++)
			snd_soc_component_wwite(component, i + 0x2200,
				      cfg->wegs[i]);
	}

	/* Wun the DSP */
	snd_soc_component_wwite(component, WM8958_DSP2_EXECCONTWOW,
		      WM8958_DSP2_WUNW);

	/* Switch the DSP into the data path */
	snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
			    WM8958_MBC_SEW_MASK | WM8958_MBC_ENA,
			    path << WM8958_MBC_SEW_SHIFT | WM8958_MBC_ENA);
}

static void wm8958_dsp_appwy(stwuct snd_soc_component *component, int path, int stawt)
{
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	int pww_weg = snd_soc_component_wead(component, WM8994_POWEW_MANAGEMENT_5);
	int ena, weg, aif;

	switch (path) {
	case 0:
		pww_weg &= (WM8994_AIF1DAC1W_ENA | WM8994_AIF1DAC1W_ENA);
		aif = 0;
		bweak;
	case 1:
		pww_weg &= (WM8994_AIF1DAC2W_ENA | WM8994_AIF1DAC2W_ENA);
		aif = 0;
		bweak;
	case 2:
		pww_weg &= (WM8994_AIF2DACW_ENA | WM8994_AIF2DACW_ENA);
		aif = 1;
		bweak;
	defauwt:
		WAWN(1, "Invawid path %d\n", path);
		wetuwn;
	}

	/* Do we have both an active AIF and an active awgowithm? */
	ena = wm8994->mbc_ena[path] || wm8994->vss_ena[path] ||
		wm8994->hpf1_ena[path] || wm8994->hpf2_ena[path] ||
		wm8994->enh_eq_ena[path];
	if (!pww_weg)
		ena = 0;

	weg = snd_soc_component_wead(component, WM8958_DSP2_PWOGWAM);

	dev_dbg(component->dev, "DSP path %d %d stawtup: %d, powew: %x, DSP: %x\n",
		path, wm8994->dsp_active, stawt, pww_weg, weg);

	if (stawt && ena) {
		/* If the DSP is awweady wunning then noop */
		if (weg & WM8958_DSP2_ENA)
			wetuwn;

		/* If eithew AIFnCWK is not yet enabwed postpone */
		if (!(snd_soc_component_wead(component, WM8994_AIF1_CWOCKING_1)
		      & WM8994_AIF1CWK_ENA_MASK) &&
		    !(snd_soc_component_wead(component, WM8994_AIF2_CWOCKING_1)
		      & WM8994_AIF2CWK_ENA_MASK))
			wetuwn;

		/* Switch the cwock ovew to the appwopwiate AIF */
		snd_soc_component_update_bits(component, WM8994_CWOCKING_1,
				    WM8958_DSP2CWK_SWC | WM8958_DSP2CWK_ENA,
				    aif << WM8958_DSP2CWK_SWC_SHIFT |
				    WM8958_DSP2CWK_ENA);

		if (wm8994->enh_eq_ena[path])
			wm8958_dsp_stawt_enh_eq(component, path);
		ewse if (wm8994->vss_ena[path] || wm8994->hpf1_ena[path] ||
		    wm8994->hpf2_ena[path])
			wm8958_dsp_stawt_vss(component, path);
		ewse if (wm8994->mbc_ena[path])
			wm8958_dsp_stawt_mbc(component, path);

		wm8994->dsp_active = path;

		dev_dbg(component->dev, "DSP wunning in path %d\n", path);
	}

	if (!stawt && wm8994->dsp_active == path) {
		/* If the DSP is awweady stopped then noop */
		if (!(weg & WM8958_DSP2_ENA))
			wetuwn;

		snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
				    WM8958_MBC_ENA, 0);	
		snd_soc_component_wwite(component, WM8958_DSP2_EXECCONTWOW,
			      WM8958_DSP2_STOP);
		snd_soc_component_update_bits(component, WM8958_DSP2_PWOGWAM,
				    WM8958_DSP2_ENA, 0);
		snd_soc_component_update_bits(component, WM8994_CWOCKING_1,
				    WM8958_DSP2CWK_ENA, 0);

		wm8994->dsp_active = -1;

		dev_dbg(component->dev, "DSP stopped\n");
	}
}

int wm8958_aif_ev(stwuct snd_soc_dapm_widget *w,
		  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm8994 *contwow = dev_get_dwvdata(component->dev->pawent);
	int i;

	if (contwow->type != WM8958)
		wetuwn 0;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
	case SND_SOC_DAPM_PWE_PMU:
		fow (i = 0; i < 3; i++)
			wm8958_dsp_appwy(component, i, 1);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
	case SND_SOC_DAPM_PWE_PMD:
		fow (i = 0; i < 3; i++)
			wm8958_dsp_appwy(component, i, 0);
		bweak;
	}

	wetuwn 0;
}

/* Check if DSP2 is in use on anothew AIF */
static int wm8958_dsp2_busy(stwuct wm8994_pwiv *wm8994, int aif)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wm8994->mbc_ena); i++) {
		if (i == aif)
			continue;
		if (wm8994->mbc_ena[i] || wm8994->vss_ena[i] ||
		    wm8994->hpf1_ena[i] || wm8994->hpf2_ena[i])
			wetuwn 1;
	}

	wetuwn 0;
}

static int wm8958_put_mbc_enum(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	stwuct wm8994 *contwow = wm8994->wm8994;
	int vawue = ucontwow->vawue.enumewated.item[0];
	int weg;

	/* Don't awwow on the fwy weconfiguwation */
	weg = snd_soc_component_wead(component, WM8994_CWOCKING_1);
	if (weg < 0 || weg & WM8958_DSP2CWK_ENA)
		wetuwn -EBUSY;

	if (vawue >= contwow->pdata.num_mbc_cfgs)
		wetuwn -EINVAW;

	wm8994->mbc_cfg = vawue;

	wetuwn 0;
}

static int wm8958_get_mbc_enum(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = wm8994->mbc_cfg;

	wetuwn 0;
}

static int wm8958_mbc_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int wm8958_mbc_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int mbc = kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = wm8994->mbc_ena[mbc];

	wetuwn 0;
}

static int wm8958_mbc_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int mbc = kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	if (wm8994->mbc_ena[mbc] == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	if (ucontwow->vawue.integew.vawue[0] > 1)
		wetuwn -EINVAW;

	if (wm8958_dsp2_busy(wm8994, mbc)) {
		dev_dbg(component->dev, "DSP2 active on %d awweady\n", mbc);
		wetuwn -EBUSY;
	}

	if (wm8994->enh_eq_ena[mbc])
		wetuwn -EBUSY;

	wm8994->mbc_ena[mbc] = ucontwow->vawue.integew.vawue[0];

	wm8958_dsp_appwy(component, mbc, wm8994->mbc_ena[mbc]);

	wetuwn 1;
}

#define WM8958_MBC_SWITCH(xname, xvaw) {\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,\
	.info = wm8958_mbc_info, \
	.get = wm8958_mbc_get, .put = wm8958_mbc_put, \
	.pwivate_vawue = xvaw }

static int wm8958_put_vss_enum(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	stwuct wm8994 *contwow = wm8994->wm8994;
	int vawue = ucontwow->vawue.enumewated.item[0];
	int weg;

	/* Don't awwow on the fwy weconfiguwation */
	weg = snd_soc_component_wead(component, WM8994_CWOCKING_1);
	if (weg < 0 || weg & WM8958_DSP2CWK_ENA)
		wetuwn -EBUSY;

	if (vawue >= contwow->pdata.num_vss_cfgs)
		wetuwn -EINVAW;

	wm8994->vss_cfg = vawue;

	wetuwn 0;
}

static int wm8958_get_vss_enum(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = wm8994->vss_cfg;

	wetuwn 0;
}

static int wm8958_put_vss_hpf_enum(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	stwuct wm8994 *contwow = wm8994->wm8994;
	int vawue = ucontwow->vawue.enumewated.item[0];
	int weg;

	/* Don't awwow on the fwy weconfiguwation */
	weg = snd_soc_component_wead(component, WM8994_CWOCKING_1);
	if (weg < 0 || weg & WM8958_DSP2CWK_ENA)
		wetuwn -EBUSY;

	if (vawue >= contwow->pdata.num_vss_hpf_cfgs)
		wetuwn -EINVAW;

	wm8994->vss_hpf_cfg = vawue;

	wetuwn 0;
}

static int wm8958_get_vss_hpf_enum(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = wm8994->vss_hpf_cfg;

	wetuwn 0;
}

static int wm8958_vss_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int wm8958_vss_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int vss = kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = wm8994->vss_ena[vss];

	wetuwn 0;
}

static int wm8958_vss_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int vss = kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	if (wm8994->vss_ena[vss] == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	if (ucontwow->vawue.integew.vawue[0] > 1)
		wetuwn -EINVAW;

	if (!wm8994->mbc_vss)
		wetuwn -ENODEV;

	if (wm8958_dsp2_busy(wm8994, vss)) {
		dev_dbg(component->dev, "DSP2 active on %d awweady\n", vss);
		wetuwn -EBUSY;
	}

	if (wm8994->enh_eq_ena[vss])
		wetuwn -EBUSY;

	wm8994->vss_ena[vss] = ucontwow->vawue.integew.vawue[0];

	wm8958_dsp_appwy(component, vss, wm8994->vss_ena[vss]);

	wetuwn 1;
}


#define WM8958_VSS_SWITCH(xname, xvaw) {\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,\
	.info = wm8958_vss_info, \
	.get = wm8958_vss_get, .put = wm8958_vss_put, \
	.pwivate_vawue = xvaw }

static int wm8958_hpf_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int wm8958_hpf_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int hpf = kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	if (hpf < 3)
		ucontwow->vawue.integew.vawue[0] = wm8994->hpf1_ena[hpf % 3];
	ewse
		ucontwow->vawue.integew.vawue[0] = wm8994->hpf2_ena[hpf % 3];

	wetuwn 0;
}

static int wm8958_hpf_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int hpf = kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	if (hpf < 3) {
		if (wm8994->hpf1_ena[hpf % 3] ==
		    ucontwow->vawue.integew.vawue[0])
			wetuwn 0;
	} ewse {
		if (wm8994->hpf2_ena[hpf % 3] ==
		    ucontwow->vawue.integew.vawue[0])
			wetuwn 0;
	}

	if (ucontwow->vawue.integew.vawue[0] > 1)
		wetuwn -EINVAW;

	if (!wm8994->mbc_vss)
		wetuwn -ENODEV;

	if (wm8958_dsp2_busy(wm8994, hpf % 3)) {
		dev_dbg(component->dev, "DSP2 active on %d awweady\n", hpf);
		wetuwn -EBUSY;
	}

	if (wm8994->enh_eq_ena[hpf % 3])
		wetuwn -EBUSY;

	if (hpf < 3)
		wm8994->hpf1_ena[hpf % 3] = ucontwow->vawue.integew.vawue[0];
	ewse
		wm8994->hpf2_ena[hpf % 3] = ucontwow->vawue.integew.vawue[0];

	wm8958_dsp_appwy(component, hpf % 3, ucontwow->vawue.integew.vawue[0]);

	wetuwn 1;
}

#define WM8958_HPF_SWITCH(xname, xvaw) {\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,\
	.info = wm8958_hpf_info, \
	.get = wm8958_hpf_get, .put = wm8958_hpf_put, \
	.pwivate_vawue = xvaw }

static int wm8958_put_enh_eq_enum(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	stwuct wm8994 *contwow = wm8994->wm8994;
	int vawue = ucontwow->vawue.enumewated.item[0];
	int weg;

	/* Don't awwow on the fwy weconfiguwation */
	weg = snd_soc_component_wead(component, WM8994_CWOCKING_1);
	if (weg < 0 || weg & WM8958_DSP2CWK_ENA)
		wetuwn -EBUSY;

	if (vawue >= contwow->pdata.num_enh_eq_cfgs)
		wetuwn -EINVAW;

	wm8994->enh_eq_cfg = vawue;

	wetuwn 0;
}

static int wm8958_get_enh_eq_enum(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = wm8994->enh_eq_cfg;

	wetuwn 0;
}

static int wm8958_enh_eq_info(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int wm8958_enh_eq_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int eq = kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = wm8994->enh_eq_ena[eq];

	wetuwn 0;
}

static int wm8958_enh_eq_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int eq = kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	if (wm8994->enh_eq_ena[eq] == ucontwow->vawue.integew.vawue[0])
		wetuwn 0;

	if (ucontwow->vawue.integew.vawue[0] > 1)
		wetuwn -EINVAW;

	if (!wm8994->enh_eq)
		wetuwn -ENODEV;

	if (wm8958_dsp2_busy(wm8994, eq)) {
		dev_dbg(component->dev, "DSP2 active on %d awweady\n", eq);
		wetuwn -EBUSY;
	}

	if (wm8994->mbc_ena[eq] || wm8994->vss_ena[eq] ||
	    wm8994->hpf1_ena[eq] || wm8994->hpf2_ena[eq])
		wetuwn -EBUSY;

	wm8994->enh_eq_ena[eq] = ucontwow->vawue.integew.vawue[0];

	wm8958_dsp_appwy(component, eq, ucontwow->vawue.integew.vawue[0]);

	wetuwn 1;
}

#define WM8958_ENH_EQ_SWITCH(xname, xvaw) {\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,\
	.info = wm8958_enh_eq_info, \
	.get = wm8958_enh_eq_get, .put = wm8958_enh_eq_put, \
	.pwivate_vawue = xvaw }

static const stwuct snd_kcontwow_new wm8958_mbc_snd_contwows[] = {
WM8958_MBC_SWITCH("AIF1DAC1 MBC Switch", 0),
WM8958_MBC_SWITCH("AIF1DAC2 MBC Switch", 1),
WM8958_MBC_SWITCH("AIF2DAC MBC Switch", 2),
};

static const stwuct snd_kcontwow_new wm8958_vss_snd_contwows[] = {
WM8958_VSS_SWITCH("AIF1DAC1 VSS Switch", 0),
WM8958_VSS_SWITCH("AIF1DAC2 VSS Switch", 1),
WM8958_VSS_SWITCH("AIF2DAC VSS Switch", 2),
WM8958_HPF_SWITCH("AIF1DAC1 HPF1 Switch", 0),
WM8958_HPF_SWITCH("AIF1DAC2 HPF1 Switch", 1),
WM8958_HPF_SWITCH("AIF2DAC HPF1 Switch", 2),
WM8958_HPF_SWITCH("AIF1DAC1 HPF2 Switch", 3),
WM8958_HPF_SWITCH("AIF1DAC2 HPF2 Switch", 4),
WM8958_HPF_SWITCH("AIF2DAC HPF2 Switch", 5),
};

static const stwuct snd_kcontwow_new wm8958_enh_eq_snd_contwows[] = {
WM8958_ENH_EQ_SWITCH("AIF1DAC1 Enhanced EQ Switch", 0),
WM8958_ENH_EQ_SWITCH("AIF1DAC2 Enhanced EQ Switch", 1),
WM8958_ENH_EQ_SWITCH("AIF2DAC Enhanced EQ Switch", 2),
};

static void wm8958_enh_eq_woaded(const stwuct fiwmwawe *fw, void *context)
{
	stwuct snd_soc_component *component = context;
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	if (fw && (wm8958_dsp2_fw(component, "ENH_EQ", fw, twue) == 0)) {
		mutex_wock(&wm8994->fw_wock);
		wm8994->enh_eq = fw;
		mutex_unwock(&wm8994->fw_wock);
	}
}

static void wm8958_mbc_vss_woaded(const stwuct fiwmwawe *fw, void *context)
{
	stwuct snd_soc_component *component = context;
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	if (fw && (wm8958_dsp2_fw(component, "MBC+VSS", fw, twue) == 0)) {
		mutex_wock(&wm8994->fw_wock);
		wm8994->mbc_vss = fw;
		mutex_unwock(&wm8994->fw_wock);
	}
}

static void wm8958_mbc_woaded(const stwuct fiwmwawe *fw, void *context)
{
	stwuct snd_soc_component *component = context;
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);

	if (fw && (wm8958_dsp2_fw(component, "MBC", fw, twue) == 0)) {
		mutex_wock(&wm8994->fw_wock);
		wm8994->mbc = fw;
		mutex_unwock(&wm8994->fw_wock);
	}
}

void wm8958_dsp2_init(stwuct snd_soc_component *component)
{
	stwuct wm8994_pwiv *wm8994 = snd_soc_component_get_dwvdata(component);
	stwuct wm8994 *contwow = wm8994->wm8994;
	stwuct wm8994_pdata *pdata = &contwow->pdata;
	int wet, i;

	wm8994->dsp_active = -1;

	snd_soc_add_component_contwows(component, wm8958_mbc_snd_contwows,
			     AWWAY_SIZE(wm8958_mbc_snd_contwows));
	snd_soc_add_component_contwows(component, wm8958_vss_snd_contwows,
			     AWWAY_SIZE(wm8958_vss_snd_contwows));
	snd_soc_add_component_contwows(component, wm8958_enh_eq_snd_contwows,
			     AWWAY_SIZE(wm8958_enh_eq_snd_contwows));


	/* We don't *wequiwe* fiwmwawe and don't want to deway boot */
	wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT,
				"wm8958_mbc.wfw", component->dev, GFP_KEWNEW,
				component, wm8958_mbc_woaded);
	wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT,
				"wm8958_mbc_vss.wfw", component->dev, GFP_KEWNEW,
				component, wm8958_mbc_vss_woaded);
	wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT,
				"wm8958_enh_eq.wfw", component->dev, GFP_KEWNEW,
				component, wm8958_enh_eq_woaded);

	if (pdata->num_mbc_cfgs) {
		stwuct snd_kcontwow_new mbc_contwow[] = {
			SOC_ENUM_EXT("MBC Mode", wm8994->mbc_enum,
				     wm8958_get_mbc_enum, wm8958_put_mbc_enum),
		};

		/* We need an awway of texts fow the enum API */
		wm8994->mbc_texts = kmawwoc_awway(pdata->num_mbc_cfgs,
						  sizeof(chaw *),
						  GFP_KEWNEW);
		if (!wm8994->mbc_texts)
			wetuwn;

		fow (i = 0; i < pdata->num_mbc_cfgs; i++)
			wm8994->mbc_texts[i] = pdata->mbc_cfgs[i].name;

		wm8994->mbc_enum.items = pdata->num_mbc_cfgs;
		wm8994->mbc_enum.texts = wm8994->mbc_texts;

		wet = snd_soc_add_component_contwows(wm8994->hubs.component,
						 mbc_contwow, 1);
		if (wet != 0)
			dev_eww(wm8994->hubs.component->dev,
				"Faiwed to add MBC mode contwows: %d\n", wet);
	}

	if (pdata->num_vss_cfgs) {
		stwuct snd_kcontwow_new vss_contwow[] = {
			SOC_ENUM_EXT("VSS Mode", wm8994->vss_enum,
				     wm8958_get_vss_enum, wm8958_put_vss_enum),
		};

		/* We need an awway of texts fow the enum API */
		wm8994->vss_texts = kmawwoc_awway(pdata->num_vss_cfgs,
						  sizeof(chaw *),
						  GFP_KEWNEW);
		if (!wm8994->vss_texts)
			wetuwn;

		fow (i = 0; i < pdata->num_vss_cfgs; i++)
			wm8994->vss_texts[i] = pdata->vss_cfgs[i].name;

		wm8994->vss_enum.items = pdata->num_vss_cfgs;
		wm8994->vss_enum.texts = wm8994->vss_texts;

		wet = snd_soc_add_component_contwows(wm8994->hubs.component,
						 vss_contwow, 1);
		if (wet != 0)
			dev_eww(wm8994->hubs.component->dev,
				"Faiwed to add VSS mode contwows: %d\n", wet);
	}

	if (pdata->num_vss_hpf_cfgs) {
		stwuct snd_kcontwow_new hpf_contwow[] = {
			SOC_ENUM_EXT("VSS HPF Mode", wm8994->vss_hpf_enum,
				     wm8958_get_vss_hpf_enum,
				     wm8958_put_vss_hpf_enum),
		};

		/* We need an awway of texts fow the enum API */
		wm8994->vss_hpf_texts = kmawwoc_awway(pdata->num_vss_hpf_cfgs,
						      sizeof(chaw *),
						      GFP_KEWNEW);
		if (!wm8994->vss_hpf_texts)
			wetuwn;

		fow (i = 0; i < pdata->num_vss_hpf_cfgs; i++)
			wm8994->vss_hpf_texts[i] = pdata->vss_hpf_cfgs[i].name;

		wm8994->vss_hpf_enum.items = pdata->num_vss_hpf_cfgs;
		wm8994->vss_hpf_enum.texts = wm8994->vss_hpf_texts;

		wet = snd_soc_add_component_contwows(wm8994->hubs.component,
						 hpf_contwow, 1);
		if (wet != 0)
			dev_eww(wm8994->hubs.component->dev,
				"Faiwed to add VSS HPFmode contwows: %d\n",
				wet);
	}

	if (pdata->num_enh_eq_cfgs) {
		stwuct snd_kcontwow_new eq_contwow[] = {
			SOC_ENUM_EXT("Enhanced EQ Mode", wm8994->enh_eq_enum,
				     wm8958_get_enh_eq_enum,
				     wm8958_put_enh_eq_enum),
		};

		/* We need an awway of texts fow the enum API */
		wm8994->enh_eq_texts = kmawwoc_awway(pdata->num_enh_eq_cfgs,
						     sizeof(chaw *),
						     GFP_KEWNEW);
		if (!wm8994->enh_eq_texts)
			wetuwn;

		fow (i = 0; i < pdata->num_enh_eq_cfgs; i++)
			wm8994->enh_eq_texts[i] = pdata->enh_eq_cfgs[i].name;

		wm8994->enh_eq_enum.items = pdata->num_enh_eq_cfgs;
		wm8994->enh_eq_enum.texts = wm8994->enh_eq_texts;

		wet = snd_soc_add_component_contwows(wm8994->hubs.component,
						 eq_contwow, 1);
		if (wet != 0)
			dev_eww(wm8994->hubs.component->dev,
				"Faiwed to add enhanced EQ contwows: %d\n",
				wet);
	}
}
