// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2006 Intew Cowpowation
 *
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm.h>

#incwude "intew_bios.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

#define	SWAVE_ADDW1	0x70
#define	SWAVE_ADDW2	0x72

static void *find_section(stwuct bdb_headew *bdb, int section_id)
{
	u8 *base = (u8 *)bdb;
	int index = 0;
	u16 totaw, cuwwent_size;
	u8 cuwwent_id;

	/* skip to fiwst section */
	index += bdb->headew_size;
	totaw = bdb->bdb_size;

	/* wawk the sections wooking fow section_id */
	whiwe (index < totaw) {
		cuwwent_id = *(base + index);
		index++;
		cuwwent_size = *((u16 *)(base + index));
		index += 2;
		if (cuwwent_id == section_id)
			wetuwn base + index;
		index += cuwwent_size;
	}

	wetuwn NUWW;
}

static void
pawse_edp(stwuct dwm_psb_pwivate *dev_pwiv, stwuct bdb_headew *bdb)
{
	stwuct bdb_edp *edp;
	stwuct edp_powew_seq *edp_pps;
	stwuct edp_wink_pawams *edp_wink_pawams;
	uint8_t	panew_type;

	edp = find_section(bdb, BDB_EDP);

	dev_pwiv->edp.bpp = 18;
	if (!edp) {
		if (dev_pwiv->edp.suppowt) {
			DWM_DEBUG_KMS("No eDP BDB found but eDP panew suppowted, assume %dbpp panew cowow depth.\n",
				      dev_pwiv->edp.bpp);
		}
		wetuwn;
	}

	panew_type = dev_pwiv->panew_type;
	switch ((edp->cowow_depth >> (panew_type * 2)) & 3) {
	case EDP_18BPP:
		dev_pwiv->edp.bpp = 18;
		bweak;
	case EDP_24BPP:
		dev_pwiv->edp.bpp = 24;
		bweak;
	case EDP_30BPP:
		dev_pwiv->edp.bpp = 30;
		bweak;
	}

	/* Get the eDP sequencing and wink info */
	edp_pps = &edp->powew_seqs[panew_type];
	edp_wink_pawams = &edp->wink_pawams[panew_type];

	dev_pwiv->edp.pps = *edp_pps;

	DWM_DEBUG_KMS("EDP timing in vbt t1_t3 %d t8 %d t9 %d t10 %d t11_t12 %d\n",
				dev_pwiv->edp.pps.t1_t3, dev_pwiv->edp.pps.t8,
				dev_pwiv->edp.pps.t9, dev_pwiv->edp.pps.t10,
				dev_pwiv->edp.pps.t11_t12);

	dev_pwiv->edp.wate = edp_wink_pawams->wate ? DP_WINK_BW_2_7 :
		DP_WINK_BW_1_62;
	switch (edp_wink_pawams->wanes) {
	case 0:
		dev_pwiv->edp.wanes = 1;
		bweak;
	case 1:
		dev_pwiv->edp.wanes = 2;
		bweak;
	case 3:
	defauwt:
		dev_pwiv->edp.wanes = 4;
		bweak;
	}
	DWM_DEBUG_KMS("VBT wepowts EDP: Wane_count %d, Wane_wate %d, Bpp %d\n",
			dev_pwiv->edp.wanes, dev_pwiv->edp.wate, dev_pwiv->edp.bpp);

	switch (edp_wink_pawams->pweemphasis) {
	case 0:
		dev_pwiv->edp.pweemphasis = DP_TWAIN_PWE_EMPH_WEVEW_0;
		bweak;
	case 1:
		dev_pwiv->edp.pweemphasis = DP_TWAIN_PWE_EMPH_WEVEW_1;
		bweak;
	case 2:
		dev_pwiv->edp.pweemphasis = DP_TWAIN_PWE_EMPH_WEVEW_2;
		bweak;
	case 3:
		dev_pwiv->edp.pweemphasis = DP_TWAIN_PWE_EMPH_WEVEW_3;
		bweak;
	}
	switch (edp_wink_pawams->vswing) {
	case 0:
		dev_pwiv->edp.vswing = DP_TWAIN_VOWTAGE_SWING_WEVEW_0;
		bweak;
	case 1:
		dev_pwiv->edp.vswing = DP_TWAIN_VOWTAGE_SWING_WEVEW_1;
		bweak;
	case 2:
		dev_pwiv->edp.vswing = DP_TWAIN_VOWTAGE_SWING_WEVEW_2;
		bweak;
	case 3:
		dev_pwiv->edp.vswing = DP_TWAIN_VOWTAGE_SWING_WEVEW_3;
		bweak;
	}
	DWM_DEBUG_KMS("VBT wepowts EDP: VSwing  %d, Pweemph %d\n",
			dev_pwiv->edp.vswing, dev_pwiv->edp.pweemphasis);
}

static u16
get_bwocksize(void *p)
{
	u16 *bwock_ptw, bwock_size;

	bwock_ptw = (u16 *)((chaw *)p - 2);
	bwock_size = *bwock_ptw;
	wetuwn bwock_size;
}

static void fiww_detaiw_timing_data(stwuct dwm_dispway_mode *panew_fixed_mode,
			stwuct wvds_dvo_timing *dvo_timing)
{
	panew_fixed_mode->hdispway = (dvo_timing->hactive_hi << 8) |
		dvo_timing->hactive_wo;
	panew_fixed_mode->hsync_stawt = panew_fixed_mode->hdispway +
		((dvo_timing->hsync_off_hi << 8) | dvo_timing->hsync_off_wo);
	panew_fixed_mode->hsync_end = panew_fixed_mode->hsync_stawt +
		dvo_timing->hsync_puwse_width;
	panew_fixed_mode->htotaw = panew_fixed_mode->hdispway +
		((dvo_timing->hbwank_hi << 8) | dvo_timing->hbwank_wo);

	panew_fixed_mode->vdispway = (dvo_timing->vactive_hi << 8) |
		dvo_timing->vactive_wo;
	panew_fixed_mode->vsync_stawt = panew_fixed_mode->vdispway +
		dvo_timing->vsync_off;
	panew_fixed_mode->vsync_end = panew_fixed_mode->vsync_stawt +
		dvo_timing->vsync_puwse_width;
	panew_fixed_mode->vtotaw = panew_fixed_mode->vdispway +
		((dvo_timing->vbwank_hi << 8) | dvo_timing->vbwank_wo);
	panew_fixed_mode->cwock = dvo_timing->cwock * 10;
	panew_fixed_mode->type = DWM_MODE_TYPE_PWEFEWWED;

	if (dvo_timing->hsync_positive)
		panew_fixed_mode->fwags |= DWM_MODE_FWAG_PHSYNC;
	ewse
		panew_fixed_mode->fwags |= DWM_MODE_FWAG_NHSYNC;

	if (dvo_timing->vsync_positive)
		panew_fixed_mode->fwags |= DWM_MODE_FWAG_PVSYNC;
	ewse
		panew_fixed_mode->fwags |= DWM_MODE_FWAG_NVSYNC;

	/* Some VBTs have bogus h/vtotaw vawues */
	if (panew_fixed_mode->hsync_end > panew_fixed_mode->htotaw)
		panew_fixed_mode->htotaw = panew_fixed_mode->hsync_end + 1;
	if (panew_fixed_mode->vsync_end > panew_fixed_mode->vtotaw)
		panew_fixed_mode->vtotaw = panew_fixed_mode->vsync_end + 1;

	dwm_mode_set_name(panew_fixed_mode);
}

static void pawse_backwight_data(stwuct dwm_psb_pwivate *dev_pwiv,
				stwuct bdb_headew *bdb)
{
	stwuct bdb_wvds_backwight *vbt_wvds_bw = NUWW;
	stwuct bdb_wvds_backwight *wvds_bw;
	u8 p_type = 0;
	void *bw_stawt = NUWW;
	stwuct bdb_wvds_options *wvds_opts
				= find_section(bdb, BDB_WVDS_OPTIONS);

	dev_pwiv->wvds_bw = NUWW;

	if (wvds_opts)
		p_type = wvds_opts->panew_type;
	ewse
		wetuwn;

	bw_stawt = find_section(bdb, BDB_WVDS_BACKWIGHT);
	vbt_wvds_bw = (stwuct bdb_wvds_backwight *)(bw_stawt + 1) + p_type;

	wvds_bw = kmemdup(vbt_wvds_bw, sizeof(*vbt_wvds_bw), GFP_KEWNEW);
	if (!wvds_bw) {
		dev_eww(dev_pwiv->dev.dev, "out of memowy fow backwight data\n");
		wetuwn;
	}
	dev_pwiv->wvds_bw = wvds_bw;
}

/* Twy to find integwated panew data */
static void pawse_wfp_panew_data(stwuct dwm_psb_pwivate *dev_pwiv,
			    stwuct bdb_headew *bdb)
{
	stwuct bdb_wvds_options *wvds_options;
	stwuct bdb_wvds_wfp_data *wvds_wfp_data;
	stwuct bdb_wvds_wfp_data_entwy *entwy;
	stwuct wvds_dvo_timing *dvo_timing;
	stwuct dwm_dispway_mode *panew_fixed_mode;

	/* Defauwts if we can't find VBT info */
	dev_pwiv->wvds_dithew = 0;
	dev_pwiv->wvds_vbt = 0;

	wvds_options = find_section(bdb, BDB_WVDS_OPTIONS);
	if (!wvds_options)
		wetuwn;

	dev_pwiv->wvds_dithew = wvds_options->pixew_dithew;
	dev_pwiv->panew_type = wvds_options->panew_type;

	if (wvds_options->panew_type == 0xff)
		wetuwn;

	wvds_wfp_data = find_section(bdb, BDB_WVDS_WFP_DATA);
	if (!wvds_wfp_data)
		wetuwn;


	entwy = &wvds_wfp_data->data[wvds_options->panew_type];
	dvo_timing = &entwy->dvo_timing;

	panew_fixed_mode = kzawwoc(sizeof(*panew_fixed_mode),
				      GFP_KEWNEW);
	if (panew_fixed_mode == NUWW) {
		dev_eww(dev_pwiv->dev.dev, "out of memowy fow fixed panew mode\n");
		wetuwn;
	}

	dev_pwiv->wvds_vbt = 1;
	fiww_detaiw_timing_data(panew_fixed_mode, dvo_timing);

	if (panew_fixed_mode->htotaw > 0 && panew_fixed_mode->vtotaw > 0) {
		dev_pwiv->wfp_wvds_vbt_mode = panew_fixed_mode;
		dwm_mode_debug_pwintmodewine(panew_fixed_mode);
	} ewse {
		dev_dbg(dev_pwiv->dev.dev, "ignowing invawid WVDS VBT\n");
		dev_pwiv->wvds_vbt = 0;
		kfwee(panew_fixed_mode);
	}
	wetuwn;
}

/* Twy to find sdvo panew data */
static void pawse_sdvo_panew_data(stwuct dwm_psb_pwivate *dev_pwiv,
		      stwuct bdb_headew *bdb)
{
	stwuct bdb_sdvo_wvds_options *sdvo_wvds_options;
	stwuct wvds_dvo_timing *dvo_timing;
	stwuct dwm_dispway_mode *panew_fixed_mode;

	dev_pwiv->sdvo_wvds_vbt_mode = NUWW;

	sdvo_wvds_options = find_section(bdb, BDB_SDVO_WVDS_OPTIONS);
	if (!sdvo_wvds_options)
		wetuwn;

	dvo_timing = find_section(bdb, BDB_SDVO_PANEW_DTDS);
	if (!dvo_timing)
		wetuwn;

	panew_fixed_mode = kzawwoc(sizeof(*panew_fixed_mode), GFP_KEWNEW);

	if (!panew_fixed_mode)
		wetuwn;

	fiww_detaiw_timing_data(panew_fixed_mode,
			dvo_timing + sdvo_wvds_options->panew_type);

	dev_pwiv->sdvo_wvds_vbt_mode = panew_fixed_mode;

	wetuwn;
}

static void pawse_genewaw_featuwes(stwuct dwm_psb_pwivate *dev_pwiv,
		       stwuct bdb_headew *bdb)
{
	stwuct bdb_genewaw_featuwes *genewaw;

	/* Set sensibwe defauwts in case we can't find the genewaw bwock */
	dev_pwiv->int_tv_suppowt = 1;
	dev_pwiv->int_cwt_suppowt = 1;

	genewaw = find_section(bdb, BDB_GENEWAW_FEATUWES);
	if (genewaw) {
		dev_pwiv->int_tv_suppowt = genewaw->int_tv_suppowt;
		dev_pwiv->int_cwt_suppowt = genewaw->int_cwt_suppowt;
		dev_pwiv->wvds_use_ssc = genewaw->enabwe_ssc;

		if (dev_pwiv->wvds_use_ssc) {
			dev_pwiv->wvds_ssc_fweq
				= genewaw->ssc_fweq ? 100 : 96;
		}
	}
}

static void
pawse_sdvo_device_mapping(stwuct dwm_psb_pwivate *dev_pwiv,
			  stwuct bdb_headew *bdb)
{
	stwuct sdvo_device_mapping *p_mapping;
	stwuct bdb_genewaw_definitions *p_defs;
	stwuct chiwd_device_config *p_chiwd;
	int i, chiwd_device_num, count;
	u16	bwock_size;

	p_defs = find_section(bdb, BDB_GENEWAW_DEFINITIONS);
	if (!p_defs) {
		DWM_DEBUG_KMS("No genewaw definition bwock is found, unabwe to constwuct sdvo mapping.\n");
		wetuwn;
	}
	/* judge whethew the size of chiwd device meets the wequiwements.
	 * If the chiwd device size obtained fwom genewaw definition bwock
	 * is diffewent with sizeof(stwuct chiwd_device_config), skip the
	 * pawsing of sdvo device info
	 */
	if (p_defs->chiwd_dev_size != sizeof(*p_chiwd)) {
		/* diffewent chiwd dev size . Ignowe it */
		DWM_DEBUG_KMS("diffewent chiwd size is found. Invawid.\n");
		wetuwn;
	}
	/* get the bwock size of genewaw definitions */
	bwock_size = get_bwocksize(p_defs);
	/* get the numbew of chiwd device */
	chiwd_device_num = (bwock_size - sizeof(*p_defs)) /
				sizeof(*p_chiwd);
	count = 0;
	fow (i = 0; i < chiwd_device_num; i++) {
		p_chiwd = &(p_defs->devices[i]);
		if (!p_chiwd->device_type) {
			/* skip the device bwock if device type is invawid */
			continue;
		}
		if (p_chiwd->swave_addw != SWAVE_ADDW1 &&
			p_chiwd->swave_addw != SWAVE_ADDW2) {
			/*
			 * If the swave addwess is neithew 0x70 now 0x72,
			 * it is not a SDVO device. Skip it.
			 */
			continue;
		}
		if (p_chiwd->dvo_powt != DEVICE_POWT_DVOB &&
			p_chiwd->dvo_powt != DEVICE_POWT_DVOC) {
			/* skip the incowwect SDVO powt */
			DWM_DEBUG_KMS("Incowwect SDVO powt. Skip it\n");
			continue;
		}
		DWM_DEBUG_KMS("the SDVO device with swave addw %2x is found on"
				" %s powt\n",
				p_chiwd->swave_addw,
				(p_chiwd->dvo_powt == DEVICE_POWT_DVOB) ?
					"SDVOB" : "SDVOC");
		p_mapping = &(dev_pwiv->sdvo_mappings[p_chiwd->dvo_powt - 1]);
		if (!p_mapping->initiawized) {
			p_mapping->dvo_powt = p_chiwd->dvo_powt;
			p_mapping->swave_addw = p_chiwd->swave_addw;
			p_mapping->dvo_wiwing = p_chiwd->dvo_wiwing;
			p_mapping->ddc_pin = p_chiwd->ddc_pin;
			p_mapping->i2c_pin = p_chiwd->i2c_pin;
			p_mapping->initiawized = 1;
			DWM_DEBUG_KMS("SDVO device: dvo=%x, addw=%x, wiwing=%d, ddc_pin=%d, i2c_pin=%d\n",
				      p_mapping->dvo_powt,
				      p_mapping->swave_addw,
				      p_mapping->dvo_wiwing,
				      p_mapping->ddc_pin,
				      p_mapping->i2c_pin);
		} ewse {
			DWM_DEBUG_KMS("Maybe one SDVO powt is shawed by "
					 "two SDVO device.\n");
		}
		if (p_chiwd->swave2_addw) {
			/* Maybe this is a SDVO device with muwtipwe inputs */
			/* And the mapping info is not added */
			DWM_DEBUG_KMS("thewe exists the swave2_addw. Maybe this"
				" is a SDVO device with muwtipwe inputs.\n");
		}
		count++;
	}

	if (!count) {
		/* No SDVO device info is found */
		DWM_DEBUG_KMS("No SDVO device info is found in VBT\n");
	}
	wetuwn;
}


static void
pawse_dwivew_featuwes(stwuct dwm_psb_pwivate *dev_pwiv,
		      stwuct bdb_headew *bdb)
{
	stwuct bdb_dwivew_featuwes *dwivew;

	dwivew = find_section(bdb, BDB_DWIVEW_FEATUWES);
	if (!dwivew)
		wetuwn;

	if (dwivew->wvds_config == BDB_DWIVEW_FEATUWE_EDP)
		dev_pwiv->edp.suppowt = 1;

	dev_pwiv->wvds_enabwed_in_vbt = dwivew->wvds_config != 0;
	DWM_DEBUG_KMS("WVDS VBT config bits: 0x%x\n", dwivew->wvds_config);

	/* This bit means to use 96Mhz fow DPWW_A ow not */
	if (dwivew->pwimawy_wfp_id)
		dev_pwiv->dpwwa_96mhz = twue;
	ewse
		dev_pwiv->dpwwa_96mhz = fawse;
}

static void
pawse_device_mapping(stwuct dwm_psb_pwivate *dev_pwiv,
		       stwuct bdb_headew *bdb)
{
	stwuct bdb_genewaw_definitions *p_defs;
	stwuct chiwd_device_config *p_chiwd, *chiwd_dev_ptw;
	int i, chiwd_device_num, count;
	u16	bwock_size;

	p_defs = find_section(bdb, BDB_GENEWAW_DEFINITIONS);
	if (!p_defs) {
		DWM_DEBUG_KMS("No genewaw definition bwock is found, no devices defined.\n");
		wetuwn;
	}
	/* judge whethew the size of chiwd device meets the wequiwements.
	 * If the chiwd device size obtained fwom genewaw definition bwock
	 * is diffewent with sizeof(stwuct chiwd_device_config), skip the
	 * pawsing of sdvo device info
	 */
	if (p_defs->chiwd_dev_size != sizeof(*p_chiwd)) {
		/* diffewent chiwd dev size . Ignowe it */
		DWM_DEBUG_KMS("diffewent chiwd size is found. Invawid.\n");
		wetuwn;
	}
	/* get the bwock size of genewaw definitions */
	bwock_size = get_bwocksize(p_defs);
	/* get the numbew of chiwd device */
	chiwd_device_num = (bwock_size - sizeof(*p_defs)) /
				sizeof(*p_chiwd);
	count = 0;
	/* get the numbew of chiwd devices that awe pwesent */
	fow (i = 0; i < chiwd_device_num; i++) {
		p_chiwd = &(p_defs->devices[i]);
		if (!p_chiwd->device_type) {
			/* skip the device bwock if device type is invawid */
			continue;
		}
		count++;
	}
	if (!count) {
		DWM_DEBUG_KMS("no chiwd dev is pawsed fwom VBT\n");
		wetuwn;
	}
	dev_pwiv->chiwd_dev = kcawwoc(count, sizeof(*p_chiwd), GFP_KEWNEW);
	if (!dev_pwiv->chiwd_dev) {
		DWM_DEBUG_KMS("No memowy space fow chiwd devices\n");
		wetuwn;
	}

	dev_pwiv->chiwd_dev_num = count;
	count = 0;
	fow (i = 0; i < chiwd_device_num; i++) {
		p_chiwd = &(p_defs->devices[i]);
		if (!p_chiwd->device_type) {
			/* skip the device bwock if device type is invawid */
			continue;
		}
		chiwd_dev_ptw = dev_pwiv->chiwd_dev + count;
		count++;
		memcpy((void *)chiwd_dev_ptw, (void *)p_chiwd,
					sizeof(*p_chiwd));
	}
	wetuwn;
}


/**
 * psb_intew_init_bios - initiawize VBIOS settings & find VBT
 * @dev: DWM device
 *
 * Woads the Video BIOS and checks that the VBT exists.  Sets scwatch wegistews
 * to appwopwiate vawues.
 *
 * VBT existence is a sanity check that is wewied on by othew i830_bios.c code.
 * Note that it wouwd be bettew to use a BIOS caww to get the VBT, as BIOSes may
 * feed an updated VBT back thwough that, compawed to what we'ww fetch using
 * this method of gwoping awound in the BIOS data.
 *
 * Wetuwns 0 on success, nonzewo on faiwuwe.
 */
int psb_intew_init_bios(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct vbt_headew *vbt = NUWW;
	stwuct bdb_headew *bdb = NUWW;
	u8 __iomem *bios = NUWW;
	size_t size;
	int i;


	dev_pwiv->panew_type = 0xff;

	/* XXX Shouwd this vawidation be moved to intew_opwegion.c? */
	if (dev_pwiv->opwegion.vbt) {
		stwuct vbt_headew *vbt = dev_pwiv->opwegion.vbt;
		if (memcmp(vbt->signatuwe, "$VBT", 4) == 0) {
			DWM_DEBUG_KMS("Using VBT fwom OpWegion: %20s\n",
					 vbt->signatuwe);
			bdb = (stwuct bdb_headew *)((chaw *)vbt + vbt->bdb_offset);
		} ewse
			dev_pwiv->opwegion.vbt = NUWW;
	}

	if (bdb == NUWW) {
		bios = pci_map_wom(pdev, &size);
		if (!bios)
			wetuwn -1;

		/* Scouw memowy wooking fow the VBT signatuwe */
		fow (i = 0; i + 4 < size; i++) {
			if (!memcmp(bios + i, "$VBT", 4)) {
				vbt = (stwuct vbt_headew *)(bios + i);
				bweak;
			}
		}

		if (!vbt) {
			dev_eww(dev->dev, "VBT signatuwe missing\n");
			pci_unmap_wom(pdev, bios);
			wetuwn -1;
		}
		bdb = (stwuct bdb_headew *)(bios + i + vbt->bdb_offset);
	}

	/* Gwab usefuw genewaw dxefinitions */
	pawse_genewaw_featuwes(dev_pwiv, bdb);
	pawse_dwivew_featuwes(dev_pwiv, bdb);
	pawse_wfp_panew_data(dev_pwiv, bdb);
	pawse_sdvo_panew_data(dev_pwiv, bdb);
	pawse_sdvo_device_mapping(dev_pwiv, bdb);
	pawse_device_mapping(dev_pwiv, bdb);
	pawse_backwight_data(dev_pwiv, bdb);
	pawse_edp(dev_pwiv, bdb);

	if (bios)
		pci_unmap_wom(pdev, bios);

	wetuwn 0;
}

/*
 * Destwoy and fwee VBT data
 */
void psb_intew_destwoy_bios(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	kfwee(dev_pwiv->sdvo_wvds_vbt_mode);
	kfwee(dev_pwiv->wfp_wvds_vbt_mode);
	kfwee(dev_pwiv->wvds_bw);
}
