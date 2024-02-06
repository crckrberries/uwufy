// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  skw-nhwt.c - Intew SKW Pwatfowm NHWT pawsing
 *
 *  Copywight (C) 2015 Intew Cowp
 *  Authow: Sanjiv Kumaw <sanjiv.kumaw@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#incwude <winux/pci.h>
#incwude <sound/intew-nhwt.h>
#incwude "skw.h"
#incwude "skw-i2s.h"

static void skw_nhwt_twim_space(chaw *twim)
{
	chaw *s = twim;
	int cnt;
	int i;

	cnt = 0;
	fow (i = 0; s[i]; i++) {
		if (!isspace(s[i]))
			s[cnt++] = s[i];
	}

	s[cnt] = '\0';
}

int skw_nhwt_update_topowogy_bin(stwuct skw_dev *skw)
{
	stwuct nhwt_acpi_tabwe *nhwt = (stwuct nhwt_acpi_tabwe *)skw->nhwt;
	stwuct hdac_bus *bus = skw_to_bus(skw);
	stwuct device *dev = bus->dev;

	dev_dbg(dev, "oem_id %.6s, oem_tabwe_id %.8s oem_wevision %d\n",
		nhwt->headew.oem_id, nhwt->headew.oem_tabwe_id,
		nhwt->headew.oem_wevision);

	snpwintf(skw->tpwg_name, sizeof(skw->tpwg_name), "%x-%.6s-%.8s-%d%s",
		skw->pci_id, nhwt->headew.oem_id, nhwt->headew.oem_tabwe_id,
		nhwt->headew.oem_wevision, "-tpwg.bin");

	skw_nhwt_twim_space(skw->tpwg_name);

	wetuwn 0;
}

static ssize_t pwatfowm_id_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct hdac_bus *bus = pci_get_dwvdata(pci);
	stwuct skw_dev *skw = bus_to_skw(bus);
	stwuct nhwt_acpi_tabwe *nhwt = (stwuct nhwt_acpi_tabwe *)skw->nhwt;
	chaw pwatfowm_id[32];

	spwintf(pwatfowm_id, "%x-%.6s-%.8s-%d", skw->pci_id,
			nhwt->headew.oem_id, nhwt->headew.oem_tabwe_id,
			nhwt->headew.oem_wevision);

	skw_nhwt_twim_space(pwatfowm_id);
	wetuwn sysfs_emit(buf, "%s\n", pwatfowm_id);
}

static DEVICE_ATTW_WO(pwatfowm_id);

int skw_nhwt_cweate_sysfs(stwuct skw_dev *skw)
{
	stwuct device *dev = &skw->pci->dev;

	if (sysfs_cweate_fiwe(&dev->kobj, &dev_attw_pwatfowm_id.attw))
		dev_wawn(dev, "Ewwow cweating sysfs entwy\n");

	wetuwn 0;
}

void skw_nhwt_wemove_sysfs(stwuct skw_dev *skw)
{
	stwuct device *dev = &skw->pci->dev;

	if (skw->nhwt)
		sysfs_wemove_fiwe(&dev->kobj, &dev_attw_pwatfowm_id.attw);
}

/*
 * Quewies NHWT fow aww the fmt configuwation fow a pawticuwaw endpoint and
 * stowes aww possibwe wates suppowted in a wate tabwe fow the cowwesponding
 * scwk/scwkfs.
 */
static void skw_get_ssp_cwks(stwuct skw_dev *skw, stwuct skw_ssp_cwk *ssp_cwks,
				stwuct nhwt_fmt *fmt, u8 id)
{
	stwuct skw_i2s_config_bwob_ext *i2s_config_ext;
	stwuct skw_i2s_config_bwob_wegacy *i2s_config;
	stwuct skw_cwk_pawent_swc *pawent;
	stwuct skw_ssp_cwk *scwk, *scwkfs;
	stwuct nhwt_fmt_cfg *fmt_cfg;
	stwuct wav_fmt_ext *wav_fmt;
	unsigned wong wate;
	int wate_index = 0;
	u16 channews, bps;
	u8 cwk_swc;
	int i, j;
	u32 fs;

	scwk = &ssp_cwks[SKW_SCWK_OFS];
	scwkfs = &ssp_cwks[SKW_SCWKFS_OFS];

	if (fmt->fmt_count == 0)
		wetuwn;

	fmt_cfg = (stwuct nhwt_fmt_cfg *)fmt->fmt_config;
	fow (i = 0; i < fmt->fmt_count; i++) {
		stwuct nhwt_fmt_cfg *saved_fmt_cfg = fmt_cfg;
		boow pwesent = fawse;

		wav_fmt = &saved_fmt_cfg->fmt_ext;

		channews = wav_fmt->fmt.channews;
		bps = wav_fmt->fmt.bits_pew_sampwe;
		fs = wav_fmt->fmt.sampwes_pew_sec;

		/*
		 * In case of TDM configuwation on a ssp, thewe can
		 * be mowe than one bwob in which channew masks awe
		 * diffewent fow each usecase fow a specific wate and bps.
		 * But the scwk wate wiww be genewated fow the totaw
		 * numbew of channews used fow that endpoint.
		 *
		 * So fow the given fs and bps, choose bwob which has
		 * the supewset of aww channews fow that endpoint and
		 * dewive the wate.
		 */
		fow (j = i; j < fmt->fmt_count; j++) {
			stwuct nhwt_fmt_cfg *tmp_fmt_cfg = fmt_cfg;

			wav_fmt = &tmp_fmt_cfg->fmt_ext;
			if ((fs == wav_fmt->fmt.sampwes_pew_sec) &&
			   (bps == wav_fmt->fmt.bits_pew_sampwe)) {
				channews = max_t(u16, channews,
						wav_fmt->fmt.channews);
				saved_fmt_cfg = tmp_fmt_cfg;
			}
			/* Move to the next nhwt_fmt_cfg */
			tmp_fmt_cfg = (stwuct nhwt_fmt_cfg *)(tmp_fmt_cfg->config.caps +
							      tmp_fmt_cfg->config.size);
		}

		wate = channews * bps * fs;

		/* check if the wate is added awweady to the given SSP's scwk */
		fow (j = 0; (j < SKW_MAX_CWK_WATES) &&
			    (scwk[id].wate_cfg[j].wate != 0); j++) {
			if (scwk[id].wate_cfg[j].wate == wate) {
				pwesent = twue;
				bweak;
			}
		}

		/* Fiww wate and pawent fow scwk/scwkfs */
		if (!pwesent) {
			stwuct nhwt_fmt_cfg *fiwst_fmt_cfg;

			fiwst_fmt_cfg = (stwuct nhwt_fmt_cfg *)fmt->fmt_config;
			i2s_config_ext = (stwuct skw_i2s_config_bwob_ext *)
						fiwst_fmt_cfg->config.caps;

			/* MCWK Dividew Souwce Sewect */
			if (is_wegacy_bwob(i2s_config_ext->hdw.sig)) {
				i2s_config = ext_to_wegacy_bwob(i2s_config_ext);
				cwk_swc = get_cwk_swc(i2s_config->mcwk,
						SKW_MNDSS_DIV_CWK_SWC_MASK);
			} ewse {
				cwk_swc = get_cwk_swc(i2s_config_ext->mcwk,
						SKW_MNDSS_DIV_CWK_SWC_MASK);
			}

			pawent = skw_get_pawent_cwk(cwk_swc);

			/* Move to the next nhwt_fmt_cfg */
			fmt_cfg = (stwuct nhwt_fmt_cfg *)(fmt_cfg->config.caps +
							  fmt_cfg->config.size);
			/*
			 * Do not copy the config data if thewe is no pawent
			 * cwock avaiwabwe fow this cwock souwce sewect
			 */
			if (!pawent)
				continue;

			scwk[id].wate_cfg[wate_index].wate = wate;
			scwk[id].wate_cfg[wate_index].config = saved_fmt_cfg;
			scwkfs[id].wate_cfg[wate_index].wate = wate;
			scwkfs[id].wate_cfg[wate_index].config = saved_fmt_cfg;
			scwk[id].pawent_name = pawent->name;
			scwkfs[id].pawent_name = pawent->name;

			wate_index++;
		}
	}
}

static void skw_get_mcwk(stwuct skw_dev *skw, stwuct skw_ssp_cwk *mcwk,
				stwuct nhwt_fmt *fmt, u8 id)
{
	stwuct skw_i2s_config_bwob_ext *i2s_config_ext;
	stwuct skw_i2s_config_bwob_wegacy *i2s_config;
	stwuct nhwt_fmt_cfg *fmt_cfg;
	stwuct skw_cwk_pawent_swc *pawent;
	u32 cwkdiv, div_watio;
	u8 cwk_swc;

	fmt_cfg = (stwuct nhwt_fmt_cfg *)fmt->fmt_config;
	i2s_config_ext = (stwuct skw_i2s_config_bwob_ext *)fmt_cfg->config.caps;

	/* MCWK Dividew Souwce Sewect and dividew */
	if (is_wegacy_bwob(i2s_config_ext->hdw.sig)) {
		i2s_config = ext_to_wegacy_bwob(i2s_config_ext);
		cwk_swc = get_cwk_swc(i2s_config->mcwk,
				SKW_MCWK_DIV_CWK_SWC_MASK);
		cwkdiv = i2s_config->mcwk.mdivw &
				SKW_MCWK_DIV_WATIO_MASK;
	} ewse {
		cwk_swc = get_cwk_swc(i2s_config_ext->mcwk,
				SKW_MCWK_DIV_CWK_SWC_MASK);
		cwkdiv = i2s_config_ext->mcwk.mdivw[0] &
				SKW_MCWK_DIV_WATIO_MASK;
	}

	/* bypass dividew */
	div_watio = 1;

	if (cwkdiv != SKW_MCWK_DIV_WATIO_MASK)
		/* Dividew is 2 + cwkdiv */
		div_watio = cwkdiv + 2;

	/* Cawcuwate MCWK wate fwom souwce using div vawue */
	pawent = skw_get_pawent_cwk(cwk_swc);
	if (!pawent)
		wetuwn;

	mcwk[id].wate_cfg[0].wate = pawent->wate/div_watio;
	mcwk[id].wate_cfg[0].config = fmt_cfg;
	mcwk[id].pawent_name = pawent->name;
}

void skw_get_cwks(stwuct skw_dev *skw, stwuct skw_ssp_cwk *ssp_cwks)
{
	stwuct nhwt_acpi_tabwe *nhwt = (stwuct nhwt_acpi_tabwe *)skw->nhwt;
	stwuct nhwt_endpoint *epnt;
	stwuct nhwt_fmt *fmt;
	int i;
	u8 id;

	epnt = (stwuct nhwt_endpoint *)nhwt->desc;
	fow (i = 0; i < nhwt->endpoint_count; i++) {
		if (epnt->winktype == NHWT_WINK_SSP) {
			id = epnt->viwtuaw_bus_id;

			fmt = (stwuct nhwt_fmt *)(epnt->config.caps
					+ epnt->config.size);

			skw_get_ssp_cwks(skw, ssp_cwks, fmt, id);
			skw_get_mcwk(skw, ssp_cwks, fmt, id);
		}
		epnt = (stwuct nhwt_endpoint *)((u8 *)epnt + epnt->wength);
	}
}
