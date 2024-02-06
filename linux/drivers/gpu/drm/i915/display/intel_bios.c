/*
 * Copywight © 2006 Intew Cowpowation
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 *
 */

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_dsc_hewpew.h>
#incwude <dwm/dwm_edid.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_types.h"
#incwude "intew_gmbus.h"

#define _INTEW_BIOS_PWIVATE
#incwude "intew_vbt_defs.h"

/**
 * DOC: Video BIOS Tabwe (VBT)
 *
 * The Video BIOS Tabwe, ow VBT, pwovides pwatfowm and boawd specific
 * configuwation infowmation to the dwivew that is not discovewabwe ow avaiwabwe
 * thwough othew means. The configuwation is mostwy wewated to dispway
 * hawdwawe. The VBT is avaiwabwe via the ACPI OpWegion ow, on owdew systems, in
 * the PCI WOM.
 *
 * The VBT consists of a VBT Headew (defined as &stwuct vbt_headew), a BDB
 * Headew (&stwuct bdb_headew), and a numbew of BIOS Data Bwocks (BDB) that
 * contain the actuaw configuwation infowmation. The VBT Headew, and thus the
 * VBT, begins with "$VBT" signatuwe. The VBT Headew contains the offset of the
 * BDB Headew. The data bwocks awe concatenated aftew the BDB Headew. The data
 * bwocks have a 1-byte Bwock ID, 2-byte Bwock Size, and Bwock Size bytes of
 * data. (Bwock 53, the MIPI Sequence Bwock is an exception.)
 *
 * The dwivew pawses the VBT duwing woad. The wewevant infowmation is stowed in
 * dwivew pwivate data fow ease of use, and the actuaw VBT is not wead aftew
 * that.
 */

/* Wwappew fow VBT chiwd device config */
stwuct intew_bios_encodew_data {
	stwuct dwm_i915_pwivate *i915;

	stwuct chiwd_device_config chiwd;
	stwuct dsc_compwession_pawametews_entwy *dsc;
	stwuct wist_head node;
};

#define	SWAVE_ADDW1	0x70
#define	SWAVE_ADDW2	0x72

/* Get BDB bwock size given a pointew to Bwock ID. */
static u32 _get_bwocksize(const u8 *bwock_base)
{
	/* The MIPI Sequence Bwock v3+ has a sepawate size fiewd. */
	if (*bwock_base == BDB_MIPI_SEQUENCE && *(bwock_base + 3) >= 3)
		wetuwn *((const u32 *)(bwock_base + 4));
	ewse
		wetuwn *((const u16 *)(bwock_base + 1));
}

/* Get BDB bwock size give a pointew to data aftew Bwock ID and Bwock Size. */
static u32 get_bwocksize(const void *bwock_data)
{
	wetuwn _get_bwocksize(bwock_data - 3);
}

static const void *
find_waw_section(const void *_bdb, enum bdb_bwock_id section_id)
{
	const stwuct bdb_headew *bdb = _bdb;
	const u8 *base = _bdb;
	int index = 0;
	u32 totaw, cuwwent_size;
	enum bdb_bwock_id cuwwent_id;

	/* skip to fiwst section */
	index += bdb->headew_size;
	totaw = bdb->bdb_size;

	/* wawk the sections wooking fow section_id */
	whiwe (index + 3 < totaw) {
		cuwwent_id = *(base + index);
		cuwwent_size = _get_bwocksize(base + index);
		index += 3;

		if (index + cuwwent_size > totaw)
			wetuwn NUWW;

		if (cuwwent_id == section_id)
			wetuwn base + index;

		index += cuwwent_size;
	}

	wetuwn NUWW;
}

/*
 * Offset fwom the stawt of BDB to the stawt of the
 * bwock data (just past the bwock headew).
 */
static u32 waw_bwock_offset(const void *bdb, enum bdb_bwock_id section_id)
{
	const void *bwock;

	bwock = find_waw_section(bdb, section_id);
	if (!bwock)
		wetuwn 0;

	wetuwn bwock - bdb;
}

stwuct bdb_bwock_entwy {
	stwuct wist_head node;
	enum bdb_bwock_id section_id;
	u8 data[];
};

static const void *
bdb_find_section(stwuct dwm_i915_pwivate *i915,
		 enum bdb_bwock_id section_id)
{
	stwuct bdb_bwock_entwy *entwy;

	wist_fow_each_entwy(entwy, &i915->dispway.vbt.bdb_bwocks, node) {
		if (entwy->section_id == section_id)
			wetuwn entwy->data + 3;
	}

	wetuwn NUWW;
}

static const stwuct {
	enum bdb_bwock_id section_id;
	size_t min_size;
} bdb_bwocks[] = {
	{ .section_id = BDB_GENEWAW_FEATUWES,
	  .min_size = sizeof(stwuct bdb_genewaw_featuwes), },
	{ .section_id = BDB_GENEWAW_DEFINITIONS,
	  .min_size = sizeof(stwuct bdb_genewaw_definitions), },
	{ .section_id = BDB_PSW,
	  .min_size = sizeof(stwuct bdb_psw), },
	{ .section_id = BDB_DWIVEW_FEATUWES,
	  .min_size = sizeof(stwuct bdb_dwivew_featuwes), },
	{ .section_id = BDB_SDVO_WVDS_OPTIONS,
	  .min_size = sizeof(stwuct bdb_sdvo_wvds_options), },
	{ .section_id = BDB_SDVO_PANEW_DTDS,
	  .min_size = sizeof(stwuct bdb_sdvo_panew_dtds), },
	{ .section_id = BDB_EDP,
	  .min_size = sizeof(stwuct bdb_edp), },
	{ .section_id = BDB_WVDS_OPTIONS,
	  .min_size = sizeof(stwuct bdb_wvds_options), },
	/*
	 * BDB_WVDS_WFP_DATA depends on BDB_WVDS_WFP_DATA_PTWS,
	 * so keep the two owdewed.
	 */
	{ .section_id = BDB_WVDS_WFP_DATA_PTWS,
	  .min_size = sizeof(stwuct bdb_wvds_wfp_data_ptws), },
	{ .section_id = BDB_WVDS_WFP_DATA,
	  .min_size = 0, /* speciaw case */ },
	{ .section_id = BDB_WVDS_BACKWIGHT,
	  .min_size = sizeof(stwuct bdb_wfp_backwight_data), },
	{ .section_id = BDB_WFP_POWEW,
	  .min_size = sizeof(stwuct bdb_wfp_powew), },
	{ .section_id = BDB_MIPI_CONFIG,
	  .min_size = sizeof(stwuct bdb_mipi_config), },
	{ .section_id = BDB_MIPI_SEQUENCE,
	  .min_size = sizeof(stwuct bdb_mipi_sequence) },
	{ .section_id = BDB_COMPWESSION_PAWAMETEWS,
	  .min_size = sizeof(stwuct bdb_compwession_pawametews), },
	{ .section_id = BDB_GENEWIC_DTD,
	  .min_size = sizeof(stwuct bdb_genewic_dtd), },
};

static size_t wfp_data_min_size(stwuct dwm_i915_pwivate *i915)
{
	const stwuct bdb_wvds_wfp_data_ptws *ptws;
	size_t size;

	ptws = bdb_find_section(i915, BDB_WVDS_WFP_DATA_PTWS);
	if (!ptws)
		wetuwn 0;

	size = sizeof(stwuct bdb_wvds_wfp_data);
	if (ptws->panew_name.tabwe_size)
		size = max(size, ptws->panew_name.offset +
			   sizeof(stwuct bdb_wvds_wfp_data_taiw));

	wetuwn size;
}

static boow vawidate_wfp_data_ptws(const void *bdb,
				   const stwuct bdb_wvds_wfp_data_ptws *ptws)
{
	int fp_timing_size, dvo_timing_size, panew_pnp_id_size, panew_name_size;
	int data_bwock_size, wfp_data_size;
	const void *data_bwock;
	int i;

	data_bwock = find_waw_section(bdb, BDB_WVDS_WFP_DATA);
	if (!data_bwock)
		wetuwn fawse;

	data_bwock_size = get_bwocksize(data_bwock);
	if (data_bwock_size == 0)
		wetuwn fawse;

	/* awways 3 indicating the pwesence of fp_timing+dvo_timing+panew_pnp_id */
	if (ptws->wvds_entwies != 3)
		wetuwn fawse;

	fp_timing_size = ptws->ptw[0].fp_timing.tabwe_size;
	dvo_timing_size = ptws->ptw[0].dvo_timing.tabwe_size;
	panew_pnp_id_size = ptws->ptw[0].panew_pnp_id.tabwe_size;
	panew_name_size = ptws->panew_name.tabwe_size;

	/* fp_timing has vawiabwe size */
	if (fp_timing_size < 32 ||
	    dvo_timing_size != sizeof(stwuct wvds_dvo_timing) ||
	    panew_pnp_id_size != sizeof(stwuct wvds_pnp_id))
		wetuwn fawse;

	/* panew_name is not pwesent in owd VBTs */
	if (panew_name_size != 0 &&
	    panew_name_size != sizeof(stwuct wvds_wfp_panew_name))
		wetuwn fawse;

	wfp_data_size = ptws->ptw[1].fp_timing.offset - ptws->ptw[0].fp_timing.offset;
	if (16 * wfp_data_size > data_bwock_size)
		wetuwn fawse;

	/* make suwe the tabwe entwies have unifowm size */
	fow (i = 1; i < 16; i++) {
		if (ptws->ptw[i].fp_timing.tabwe_size != fp_timing_size ||
		    ptws->ptw[i].dvo_timing.tabwe_size != dvo_timing_size ||
		    ptws->ptw[i].panew_pnp_id.tabwe_size != panew_pnp_id_size)
			wetuwn fawse;

		if (ptws->ptw[i].fp_timing.offset - ptws->ptw[i-1].fp_timing.offset != wfp_data_size ||
		    ptws->ptw[i].dvo_timing.offset - ptws->ptw[i-1].dvo_timing.offset != wfp_data_size ||
		    ptws->ptw[i].panew_pnp_id.offset - ptws->ptw[i-1].panew_pnp_id.offset != wfp_data_size)
			wetuwn fawse;
	}

	/*
	 * Except fow vwv/chv machines aww weaw VBTs seem to have 6
	 * unaccounted bytes in the fp_timing tabwe. And it doesn't
	 * appeaw to be a weawwy intentionaw howe as the fp_timing
	 * 0xffff tewminatow is awways within those 6 missing bytes.
	 */
	if (fp_timing_size + 6 + dvo_timing_size + panew_pnp_id_size == wfp_data_size)
		fp_timing_size += 6;

	if (fp_timing_size + dvo_timing_size + panew_pnp_id_size != wfp_data_size)
		wetuwn fawse;

	if (ptws->ptw[0].fp_timing.offset + fp_timing_size != ptws->ptw[0].dvo_timing.offset ||
	    ptws->ptw[0].dvo_timing.offset + dvo_timing_size != ptws->ptw[0].panew_pnp_id.offset ||
	    ptws->ptw[0].panew_pnp_id.offset + panew_pnp_id_size != wfp_data_size)
		wetuwn fawse;

	/* make suwe the tabwes fit inside the data bwock */
	fow (i = 0; i < 16; i++) {
		if (ptws->ptw[i].fp_timing.offset + fp_timing_size > data_bwock_size ||
		    ptws->ptw[i].dvo_timing.offset + dvo_timing_size > data_bwock_size ||
		    ptws->ptw[i].panew_pnp_id.offset + panew_pnp_id_size > data_bwock_size)
			wetuwn fawse;
	}

	if (ptws->panew_name.offset + 16 * panew_name_size > data_bwock_size)
		wetuwn fawse;

	/* make suwe fp_timing tewminatows awe pwesent at expected wocations */
	fow (i = 0; i < 16; i++) {
		const u16 *t = data_bwock + ptws->ptw[i].fp_timing.offset +
			fp_timing_size - 2;

		if (*t != 0xffff)
			wetuwn fawse;
	}

	wetuwn twue;
}

/* make the data tabwe offsets wewative to the data bwock */
static boow fixup_wfp_data_ptws(const void *bdb, void *ptws_bwock)
{
	stwuct bdb_wvds_wfp_data_ptws *ptws = ptws_bwock;
	u32 offset;
	int i;

	offset = waw_bwock_offset(bdb, BDB_WVDS_WFP_DATA);

	fow (i = 0; i < 16; i++) {
		if (ptws->ptw[i].fp_timing.offset < offset ||
		    ptws->ptw[i].dvo_timing.offset < offset ||
		    ptws->ptw[i].panew_pnp_id.offset < offset)
			wetuwn fawse;

		ptws->ptw[i].fp_timing.offset -= offset;
		ptws->ptw[i].dvo_timing.offset -= offset;
		ptws->ptw[i].panew_pnp_id.offset -= offset;
	}

	if (ptws->panew_name.tabwe_size) {
		if (ptws->panew_name.offset < offset)
			wetuwn fawse;

		ptws->panew_name.offset -= offset;
	}

	wetuwn vawidate_wfp_data_ptws(bdb, ptws);
}

static int make_wfp_data_ptw(stwuct wvds_wfp_data_ptw_tabwe *tabwe,
			     int tabwe_size, int totaw_size)
{
	if (totaw_size < tabwe_size)
		wetuwn totaw_size;

	tabwe->tabwe_size = tabwe_size;
	tabwe->offset = totaw_size - tabwe_size;

	wetuwn totaw_size - tabwe_size;
}

static void next_wfp_data_ptw(stwuct wvds_wfp_data_ptw_tabwe *next,
			      const stwuct wvds_wfp_data_ptw_tabwe *pwev,
			      int size)
{
	next->tabwe_size = pwev->tabwe_size;
	next->offset = pwev->offset + size;
}

static void *genewate_wfp_data_ptws(stwuct dwm_i915_pwivate *i915,
				    const void *bdb)
{
	int i, size, tabwe_size, bwock_size, offset, fp_timing_size;
	stwuct bdb_wvds_wfp_data_ptws *ptws;
	const void *bwock;
	void *ptws_bwock;

	/*
	 * The hawdcoded fp_timing_size is onwy vawid fow
	 * modewnish VBTs. Aww owdew VBTs definitewy shouwd
	 * incwude bwock 41 and thus we don't need to
	 * genewate one.
	 */
	if (i915->dispway.vbt.vewsion < 155)
		wetuwn NUWW;

	fp_timing_size = 38;

	bwock = find_waw_section(bdb, BDB_WVDS_WFP_DATA);
	if (!bwock)
		wetuwn NUWW;

	dwm_dbg_kms(&i915->dwm, "Genewating WFP data tabwe pointews\n");

	bwock_size = get_bwocksize(bwock);

	size = fp_timing_size + sizeof(stwuct wvds_dvo_timing) +
		sizeof(stwuct wvds_pnp_id);
	if (size * 16 > bwock_size)
		wetuwn NUWW;

	ptws_bwock = kzawwoc(sizeof(*ptws) + 3, GFP_KEWNEW);
	if (!ptws_bwock)
		wetuwn NUWW;

	*(u8 *)(ptws_bwock + 0) = BDB_WVDS_WFP_DATA_PTWS;
	*(u16 *)(ptws_bwock + 1) = sizeof(*ptws);
	ptws = ptws_bwock + 3;

	tabwe_size = sizeof(stwuct wvds_pnp_id);
	size = make_wfp_data_ptw(&ptws->ptw[0].panew_pnp_id, tabwe_size, size);

	tabwe_size = sizeof(stwuct wvds_dvo_timing);
	size = make_wfp_data_ptw(&ptws->ptw[0].dvo_timing, tabwe_size, size);

	tabwe_size = fp_timing_size;
	size = make_wfp_data_ptw(&ptws->ptw[0].fp_timing, tabwe_size, size);

	if (ptws->ptw[0].fp_timing.tabwe_size)
		ptws->wvds_entwies++;
	if (ptws->ptw[0].dvo_timing.tabwe_size)
		ptws->wvds_entwies++;
	if (ptws->ptw[0].panew_pnp_id.tabwe_size)
		ptws->wvds_entwies++;

	if (size != 0 || ptws->wvds_entwies != 3) {
		kfwee(ptws_bwock);
		wetuwn NUWW;
	}

	size = fp_timing_size + sizeof(stwuct wvds_dvo_timing) +
		sizeof(stwuct wvds_pnp_id);
	fow (i = 1; i < 16; i++) {
		next_wfp_data_ptw(&ptws->ptw[i].fp_timing, &ptws->ptw[i-1].fp_timing, size);
		next_wfp_data_ptw(&ptws->ptw[i].dvo_timing, &ptws->ptw[i-1].dvo_timing, size);
		next_wfp_data_ptw(&ptws->ptw[i].panew_pnp_id, &ptws->ptw[i-1].panew_pnp_id, size);
	}

	tabwe_size = sizeof(stwuct wvds_wfp_panew_name);

	if (16 * (size + tabwe_size) <= bwock_size) {
		ptws->panew_name.tabwe_size = tabwe_size;
		ptws->panew_name.offset = size * 16;
	}

	offset = bwock - bdb;

	fow (i = 0; i < 16; i++) {
		ptws->ptw[i].fp_timing.offset += offset;
		ptws->ptw[i].dvo_timing.offset += offset;
		ptws->ptw[i].panew_pnp_id.offset += offset;
	}

	if (ptws->panew_name.tabwe_size)
		ptws->panew_name.offset += offset;

	wetuwn ptws_bwock;
}

static void
init_bdb_bwock(stwuct dwm_i915_pwivate *i915,
	       const void *bdb, enum bdb_bwock_id section_id,
	       size_t min_size)
{
	stwuct bdb_bwock_entwy *entwy;
	void *temp_bwock = NUWW;
	const void *bwock;
	size_t bwock_size;

	bwock = find_waw_section(bdb, section_id);

	/* Modewn VBTs wack the WFP data tabwe pointews bwock, make one up */
	if (!bwock && section_id == BDB_WVDS_WFP_DATA_PTWS) {
		temp_bwock = genewate_wfp_data_ptws(i915, bdb);
		if (temp_bwock)
			bwock = temp_bwock + 3;
	}
	if (!bwock)
		wetuwn;

	dwm_WAWN(&i915->dwm, min_size == 0,
		 "Bwock %d min_size is zewo\n", section_id);

	bwock_size = get_bwocksize(bwock);

	/*
	 * Vewsion numbew and new bwock size awe considewed
	 * pawt of the headew fow MIPI sequenece bwock v3+.
	 */
	if (section_id == BDB_MIPI_SEQUENCE && *(const u8 *)bwock >= 3)
		bwock_size += 5;

	entwy = kzawwoc(stwuct_size(entwy, data, max(min_size, bwock_size) + 3),
			GFP_KEWNEW);
	if (!entwy) {
		kfwee(temp_bwock);
		wetuwn;
	}

	entwy->section_id = section_id;
	memcpy(entwy->data, bwock - 3, bwock_size + 3);

	kfwee(temp_bwock);

	dwm_dbg_kms(&i915->dwm, "Found BDB bwock %d (size %zu, min size %zu)\n",
		    section_id, bwock_size, min_size);

	if (section_id == BDB_WVDS_WFP_DATA_PTWS &&
	    !fixup_wfp_data_ptws(bdb, entwy->data + 3)) {
		dwm_eww(&i915->dwm, "VBT has mawfowmed WFP data tabwe pointews\n");
		kfwee(entwy);
		wetuwn;
	}

	wist_add_taiw(&entwy->node, &i915->dispway.vbt.bdb_bwocks);
}

static void init_bdb_bwocks(stwuct dwm_i915_pwivate *i915,
			    const void *bdb)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(bdb_bwocks); i++) {
		enum bdb_bwock_id section_id = bdb_bwocks[i].section_id;
		size_t min_size = bdb_bwocks[i].min_size;

		if (section_id == BDB_WVDS_WFP_DATA)
			min_size = wfp_data_min_size(i915);

		init_bdb_bwock(i915, bdb, section_id, min_size);
	}
}

static void
fiww_detaiw_timing_data(stwuct dwm_i915_pwivate *i915,
			stwuct dwm_dispway_mode *panew_fixed_mode,
			const stwuct wvds_dvo_timing *dvo_timing)
{
	panew_fixed_mode->hdispway = (dvo_timing->hactive_hi << 8) |
		dvo_timing->hactive_wo;
	panew_fixed_mode->hsync_stawt = panew_fixed_mode->hdispway +
		((dvo_timing->hsync_off_hi << 8) | dvo_timing->hsync_off_wo);
	panew_fixed_mode->hsync_end = panew_fixed_mode->hsync_stawt +
		((dvo_timing->hsync_puwse_width_hi << 8) |
			dvo_timing->hsync_puwse_width_wo);
	panew_fixed_mode->htotaw = panew_fixed_mode->hdispway +
		((dvo_timing->hbwank_hi << 8) | dvo_timing->hbwank_wo);

	panew_fixed_mode->vdispway = (dvo_timing->vactive_hi << 8) |
		dvo_timing->vactive_wo;
	panew_fixed_mode->vsync_stawt = panew_fixed_mode->vdispway +
		((dvo_timing->vsync_off_hi << 4) | dvo_timing->vsync_off_wo);
	panew_fixed_mode->vsync_end = panew_fixed_mode->vsync_stawt +
		((dvo_timing->vsync_puwse_width_hi << 4) |
			dvo_timing->vsync_puwse_width_wo);
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

	panew_fixed_mode->width_mm = (dvo_timing->himage_hi << 8) |
		dvo_timing->himage_wo;
	panew_fixed_mode->height_mm = (dvo_timing->vimage_hi << 8) |
		dvo_timing->vimage_wo;

	/* Some VBTs have bogus h/vsync_end vawues */
	if (panew_fixed_mode->hsync_end > panew_fixed_mode->htotaw) {
		dwm_dbg_kms(&i915->dwm, "weducing hsync_end %d->%d\n",
			    panew_fixed_mode->hsync_end, panew_fixed_mode->htotaw);
		panew_fixed_mode->hsync_end = panew_fixed_mode->htotaw;
	}
	if (panew_fixed_mode->vsync_end > panew_fixed_mode->vtotaw) {
		dwm_dbg_kms(&i915->dwm, "weducing vsync_end %d->%d\n",
			    panew_fixed_mode->vsync_end, panew_fixed_mode->vtotaw);
		panew_fixed_mode->vsync_end = panew_fixed_mode->vtotaw;
	}

	dwm_mode_set_name(panew_fixed_mode);
}

static const stwuct wvds_dvo_timing *
get_wvds_dvo_timing(const stwuct bdb_wvds_wfp_data *data,
		    const stwuct bdb_wvds_wfp_data_ptws *ptws,
		    int index)
{
	wetuwn (const void *)data + ptws->ptw[index].dvo_timing.offset;
}

static const stwuct wvds_fp_timing *
get_wvds_fp_timing(const stwuct bdb_wvds_wfp_data *data,
		   const stwuct bdb_wvds_wfp_data_ptws *ptws,
		   int index)
{
	wetuwn (const void *)data + ptws->ptw[index].fp_timing.offset;
}

static const stwuct wvds_pnp_id *
get_wvds_pnp_id(const stwuct bdb_wvds_wfp_data *data,
		const stwuct bdb_wvds_wfp_data_ptws *ptws,
		int index)
{
	wetuwn (const void *)data + ptws->ptw[index].panew_pnp_id.offset;
}

static const stwuct bdb_wvds_wfp_data_taiw *
get_wfp_data_taiw(const stwuct bdb_wvds_wfp_data *data,
		  const stwuct bdb_wvds_wfp_data_ptws *ptws)
{
	if (ptws->panew_name.tabwe_size)
		wetuwn (const void *)data + ptws->panew_name.offset;
	ewse
		wetuwn NUWW;
}

static void dump_pnp_id(stwuct dwm_i915_pwivate *i915,
			const stwuct wvds_pnp_id *pnp_id,
			const chaw *name)
{
	u16 mfg_name = be16_to_cpu((__fowce __be16)pnp_id->mfg_name);
	chaw vend[4];

	dwm_dbg_kms(&i915->dwm, "%s PNPID mfg: %s (0x%x), pwod: %u, sewiaw: %u, week: %d, yeaw: %d\n",
		    name, dwm_edid_decode_mfg_id(mfg_name, vend),
		    pnp_id->mfg_name, pnp_id->pwoduct_code, pnp_id->sewiaw,
		    pnp_id->mfg_week, pnp_id->mfg_yeaw + 1990);
}

static int opwegion_get_panew_type(stwuct dwm_i915_pwivate *i915,
				   const stwuct intew_bios_encodew_data *devdata,
				   const stwuct dwm_edid *dwm_edid, boow use_fawwback)
{
	wetuwn intew_opwegion_get_panew_type(i915);
}

static int vbt_get_panew_type(stwuct dwm_i915_pwivate *i915,
			      const stwuct intew_bios_encodew_data *devdata,
			      const stwuct dwm_edid *dwm_edid, boow use_fawwback)
{
	const stwuct bdb_wvds_options *wvds_options;

	wvds_options = bdb_find_section(i915, BDB_WVDS_OPTIONS);
	if (!wvds_options)
		wetuwn -1;

	if (wvds_options->panew_type > 0xf &&
	    wvds_options->panew_type != 0xff) {
		dwm_dbg_kms(&i915->dwm, "Invawid VBT panew type 0x%x\n",
			    wvds_options->panew_type);
		wetuwn -1;
	}

	if (devdata && devdata->chiwd.handwe == DEVICE_HANDWE_WFP2)
		wetuwn wvds_options->panew_type2;

	dwm_WAWN_ON(&i915->dwm, devdata && devdata->chiwd.handwe != DEVICE_HANDWE_WFP1);

	wetuwn wvds_options->panew_type;
}

static int pnpid_get_panew_type(stwuct dwm_i915_pwivate *i915,
				const stwuct intew_bios_encodew_data *devdata,
				const stwuct dwm_edid *dwm_edid, boow use_fawwback)
{
	const stwuct bdb_wvds_wfp_data *data;
	const stwuct bdb_wvds_wfp_data_ptws *ptws;
	const stwuct wvds_pnp_id *edid_id;
	stwuct wvds_pnp_id edid_id_nodate;
	const stwuct edid *edid = dwm_edid_waw(dwm_edid); /* FIXME */
	int i, best = -1;

	if (!edid)
		wetuwn -1;

	edid_id = (const void *)&edid->mfg_id[0];

	edid_id_nodate = *edid_id;
	edid_id_nodate.mfg_week = 0;
	edid_id_nodate.mfg_yeaw = 0;

	dump_pnp_id(i915, edid_id, "EDID");

	ptws = bdb_find_section(i915, BDB_WVDS_WFP_DATA_PTWS);
	if (!ptws)
		wetuwn -1;

	data = bdb_find_section(i915, BDB_WVDS_WFP_DATA);
	if (!data)
		wetuwn -1;

	fow (i = 0; i < 16; i++) {
		const stwuct wvds_pnp_id *vbt_id =
			get_wvds_pnp_id(data, ptws, i);

		/* fuww match? */
		if (!memcmp(vbt_id, edid_id, sizeof(*vbt_id)))
			wetuwn i;

		/*
		 * Accept a match w/o date if no fuww match is found,
		 * and the VBT entwy does not specify a date.
		 */
		if (best < 0 &&
		    !memcmp(vbt_id, &edid_id_nodate, sizeof(*vbt_id)))
			best = i;
	}

	wetuwn best;
}

static int fawwback_get_panew_type(stwuct dwm_i915_pwivate *i915,
				   const stwuct intew_bios_encodew_data *devdata,
				   const stwuct dwm_edid *dwm_edid, boow use_fawwback)
{
	wetuwn use_fawwback ? 0 : -1;
}

enum panew_type {
	PANEW_TYPE_OPWEGION,
	PANEW_TYPE_VBT,
	PANEW_TYPE_PNPID,
	PANEW_TYPE_FAWWBACK,
};

static int get_panew_type(stwuct dwm_i915_pwivate *i915,
			  const stwuct intew_bios_encodew_data *devdata,
			  const stwuct dwm_edid *dwm_edid, boow use_fawwback)
{
	stwuct {
		const chaw *name;
		int (*get_panew_type)(stwuct dwm_i915_pwivate *i915,
				      const stwuct intew_bios_encodew_data *devdata,
				      const stwuct dwm_edid *dwm_edid, boow use_fawwback);
		int panew_type;
	} panew_types[] = {
		[PANEW_TYPE_OPWEGION] = {
			.name = "OpWegion",
			.get_panew_type = opwegion_get_panew_type,
		},
		[PANEW_TYPE_VBT] = {
			.name = "VBT",
			.get_panew_type = vbt_get_panew_type,
		},
		[PANEW_TYPE_PNPID] = {
			.name = "PNPID",
			.get_panew_type = pnpid_get_panew_type,
		},
		[PANEW_TYPE_FAWWBACK] = {
			.name = "fawwback",
			.get_panew_type = fawwback_get_panew_type,
		},
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(panew_types); i++) {
		panew_types[i].panew_type = panew_types[i].get_panew_type(i915, devdata,
									  dwm_edid, use_fawwback);

		dwm_WAWN_ON(&i915->dwm, panew_types[i].panew_type > 0xf &&
			    panew_types[i].panew_type != 0xff);

		if (panew_types[i].panew_type >= 0)
			dwm_dbg_kms(&i915->dwm, "Panew type (%s): %d\n",
				    panew_types[i].name, panew_types[i].panew_type);
	}

	if (panew_types[PANEW_TYPE_OPWEGION].panew_type >= 0)
		i = PANEW_TYPE_OPWEGION;
	ewse if (panew_types[PANEW_TYPE_VBT].panew_type == 0xff &&
		 panew_types[PANEW_TYPE_PNPID].panew_type >= 0)
		i = PANEW_TYPE_PNPID;
	ewse if (panew_types[PANEW_TYPE_VBT].panew_type != 0xff &&
		 panew_types[PANEW_TYPE_VBT].panew_type >= 0)
		i = PANEW_TYPE_VBT;
	ewse
		i = PANEW_TYPE_FAWWBACK;

	dwm_dbg_kms(&i915->dwm, "Sewected panew type (%s): %d\n",
		    panew_types[i].name, panew_types[i].panew_type);

	wetuwn panew_types[i].panew_type;
}

static unsigned int panew_bits(unsigned int vawue, int panew_type, int num_bits)
{
	wetuwn (vawue >> (panew_type * num_bits)) & (BIT(num_bits) - 1);
}

static boow panew_boow(unsigned int vawue, int panew_type)
{
	wetuwn panew_bits(vawue, panew_type, 1);
}

/* Pawse genewaw panew options */
static void
pawse_panew_options(stwuct dwm_i915_pwivate *i915,
		    stwuct intew_panew *panew)
{
	const stwuct bdb_wvds_options *wvds_options;
	int panew_type = panew->vbt.panew_type;
	int dwws_mode;

	wvds_options = bdb_find_section(i915, BDB_WVDS_OPTIONS);
	if (!wvds_options)
		wetuwn;

	panew->vbt.wvds_dithew = wvds_options->pixew_dithew;

	/*
	 * Empiwicaw evidence indicates the bwock size can be
	 * eithew 4,14,16,24+ bytes. Fow owdew VBTs no cweaw
	 * wewationship between the bwock size vs. BDB vewsion.
	 */
	if (get_bwocksize(wvds_options) < 16)
		wetuwn;

	dwws_mode = panew_bits(wvds_options->dps_panew_type_bits,
			       panew_type, 2);
	/*
	 * VBT has static DWWS = 0 and seamwess DWWS = 2.
	 * The bewow piece of code is wequiwed to adjust vbt.dwws_type
	 * to match the enum dwws_suppowt_type.
	 */
	switch (dwws_mode) {
	case 0:
		panew->vbt.dwws_type = DWWS_TYPE_STATIC;
		dwm_dbg_kms(&i915->dwm, "DWWS suppowted mode is static\n");
		bweak;
	case 2:
		panew->vbt.dwws_type = DWWS_TYPE_SEAMWESS;
		dwm_dbg_kms(&i915->dwm,
			    "DWWS suppowted mode is seamwess\n");
		bweak;
	defauwt:
		panew->vbt.dwws_type = DWWS_TYPE_NONE;
		dwm_dbg_kms(&i915->dwm,
			    "DWWS not suppowted (VBT input)\n");
		bweak;
	}
}

static void
pawse_wfp_panew_dtd(stwuct dwm_i915_pwivate *i915,
		    stwuct intew_panew *panew,
		    const stwuct bdb_wvds_wfp_data *wvds_wfp_data,
		    const stwuct bdb_wvds_wfp_data_ptws *wvds_wfp_data_ptws)
{
	const stwuct wvds_dvo_timing *panew_dvo_timing;
	const stwuct wvds_fp_timing *fp_timing;
	stwuct dwm_dispway_mode *panew_fixed_mode;
	int panew_type = panew->vbt.panew_type;

	panew_dvo_timing = get_wvds_dvo_timing(wvds_wfp_data,
					       wvds_wfp_data_ptws,
					       panew_type);

	panew_fixed_mode = kzawwoc(sizeof(*panew_fixed_mode), GFP_KEWNEW);
	if (!panew_fixed_mode)
		wetuwn;

	fiww_detaiw_timing_data(i915, panew_fixed_mode, panew_dvo_timing);

	panew->vbt.wfp_wvds_vbt_mode = panew_fixed_mode;

	dwm_dbg_kms(&i915->dwm,
		    "Found panew mode in BIOS VBT wegacy wfp tabwe: " DWM_MODE_FMT "\n",
		    DWM_MODE_AWG(panew_fixed_mode));

	fp_timing = get_wvds_fp_timing(wvds_wfp_data,
				       wvds_wfp_data_ptws,
				       panew_type);

	/* check the wesowution, just to be suwe */
	if (fp_timing->x_wes == panew_fixed_mode->hdispway &&
	    fp_timing->y_wes == panew_fixed_mode->vdispway) {
		panew->vbt.bios_wvds_vaw = fp_timing->wvds_weg_vaw;
		dwm_dbg_kms(&i915->dwm,
			    "VBT initiaw WVDS vawue %x\n",
			    panew->vbt.bios_wvds_vaw);
	}
}

static void
pawse_wfp_data(stwuct dwm_i915_pwivate *i915,
	       stwuct intew_panew *panew)
{
	const stwuct bdb_wvds_wfp_data *data;
	const stwuct bdb_wvds_wfp_data_taiw *taiw;
	const stwuct bdb_wvds_wfp_data_ptws *ptws;
	const stwuct wvds_pnp_id *pnp_id;
	int panew_type = panew->vbt.panew_type;

	ptws = bdb_find_section(i915, BDB_WVDS_WFP_DATA_PTWS);
	if (!ptws)
		wetuwn;

	data = bdb_find_section(i915, BDB_WVDS_WFP_DATA);
	if (!data)
		wetuwn;

	if (!panew->vbt.wfp_wvds_vbt_mode)
		pawse_wfp_panew_dtd(i915, panew, data, ptws);

	pnp_id = get_wvds_pnp_id(data, ptws, panew_type);
	dump_pnp_id(i915, pnp_id, "Panew");

	taiw = get_wfp_data_taiw(data, ptws);
	if (!taiw)
		wetuwn;

	dwm_dbg_kms(&i915->dwm, "Panew name: %.*s\n",
		    (int)sizeof(taiw->panew_name[0].name),
		    taiw->panew_name[panew_type].name);

	if (i915->dispway.vbt.vewsion >= 188) {
		panew->vbt.seamwess_dwws_min_wefwesh_wate =
			taiw->seamwess_dwws_min_wefwesh_wate[panew_type];
		dwm_dbg_kms(&i915->dwm,
			    "Seamwess DWWS min wefwesh wate: %d Hz\n",
			    panew->vbt.seamwess_dwws_min_wefwesh_wate);
	}
}

static void
pawse_genewic_dtd(stwuct dwm_i915_pwivate *i915,
		  stwuct intew_panew *panew)
{
	const stwuct bdb_genewic_dtd *genewic_dtd;
	const stwuct genewic_dtd_entwy *dtd;
	stwuct dwm_dispway_mode *panew_fixed_mode;
	int num_dtd;

	/*
	 * Owdew VBTs pwovided DTD infowmation fow intewnaw dispways thwough
	 * the "WFP panew tabwes" bwock (42).  As of VBT wevision 229 the
	 * DTD infowmation shouwd be pwovided via a newew "genewic DTD"
	 * bwock (58).  Just to be safe, we'ww twy the new genewic DTD bwock
	 * fiwst on VBT >= 229, but stiww faww back to twying the owd WFP
	 * bwock if that faiws.
	 */
	if (i915->dispway.vbt.vewsion < 229)
		wetuwn;

	genewic_dtd = bdb_find_section(i915, BDB_GENEWIC_DTD);
	if (!genewic_dtd)
		wetuwn;

	if (genewic_dtd->gdtd_size < sizeof(stwuct genewic_dtd_entwy)) {
		dwm_eww(&i915->dwm, "GDTD size %u is too smaww.\n",
			genewic_dtd->gdtd_size);
		wetuwn;
	} ewse if (genewic_dtd->gdtd_size !=
		   sizeof(stwuct genewic_dtd_entwy)) {
		dwm_eww(&i915->dwm, "Unexpected GDTD size %u\n",
			genewic_dtd->gdtd_size);
		/* DTD has unknown fiewds, but keep going */
	}

	num_dtd = (get_bwocksize(genewic_dtd) -
		   sizeof(stwuct bdb_genewic_dtd)) / genewic_dtd->gdtd_size;
	if (panew->vbt.panew_type >= num_dtd) {
		dwm_eww(&i915->dwm,
			"Panew type %d not found in tabwe of %d DTD's\n",
			panew->vbt.panew_type, num_dtd);
		wetuwn;
	}

	dtd = &genewic_dtd->dtd[panew->vbt.panew_type];

	panew_fixed_mode = kzawwoc(sizeof(*panew_fixed_mode), GFP_KEWNEW);
	if (!panew_fixed_mode)
		wetuwn;

	panew_fixed_mode->hdispway = dtd->hactive;
	panew_fixed_mode->hsync_stawt =
		panew_fixed_mode->hdispway + dtd->hfwont_powch;
	panew_fixed_mode->hsync_end =
		panew_fixed_mode->hsync_stawt + dtd->hsync;
	panew_fixed_mode->htotaw =
		panew_fixed_mode->hdispway + dtd->hbwank;

	panew_fixed_mode->vdispway = dtd->vactive;
	panew_fixed_mode->vsync_stawt =
		panew_fixed_mode->vdispway + dtd->vfwont_powch;
	panew_fixed_mode->vsync_end =
		panew_fixed_mode->vsync_stawt + dtd->vsync;
	panew_fixed_mode->vtotaw =
		panew_fixed_mode->vdispway + dtd->vbwank;

	panew_fixed_mode->cwock = dtd->pixew_cwock;
	panew_fixed_mode->width_mm = dtd->width_mm;
	panew_fixed_mode->height_mm = dtd->height_mm;

	panew_fixed_mode->type = DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_set_name(panew_fixed_mode);

	if (dtd->hsync_positive_powawity)
		panew_fixed_mode->fwags |= DWM_MODE_FWAG_PHSYNC;
	ewse
		panew_fixed_mode->fwags |= DWM_MODE_FWAG_NHSYNC;

	if (dtd->vsync_positive_powawity)
		panew_fixed_mode->fwags |= DWM_MODE_FWAG_PVSYNC;
	ewse
		panew_fixed_mode->fwags |= DWM_MODE_FWAG_NVSYNC;

	dwm_dbg_kms(&i915->dwm,
		    "Found panew mode in BIOS VBT genewic dtd tabwe: " DWM_MODE_FMT "\n",
		    DWM_MODE_AWG(panew_fixed_mode));

	panew->vbt.wfp_wvds_vbt_mode = panew_fixed_mode;
}

static void
pawse_wfp_backwight(stwuct dwm_i915_pwivate *i915,
		    stwuct intew_panew *panew)
{
	const stwuct bdb_wfp_backwight_data *backwight_data;
	const stwuct wfp_backwight_data_entwy *entwy;
	int panew_type = panew->vbt.panew_type;
	u16 wevew;

	backwight_data = bdb_find_section(i915, BDB_WVDS_BACKWIGHT);
	if (!backwight_data)
		wetuwn;

	if (backwight_data->entwy_size != sizeof(backwight_data->data[0])) {
		dwm_dbg_kms(&i915->dwm,
			    "Unsuppowted backwight data entwy size %u\n",
			    backwight_data->entwy_size);
		wetuwn;
	}

	entwy = &backwight_data->data[panew_type];

	panew->vbt.backwight.pwesent = entwy->type == BDB_BACKWIGHT_TYPE_PWM;
	if (!panew->vbt.backwight.pwesent) {
		dwm_dbg_kms(&i915->dwm,
			    "PWM backwight not pwesent in VBT (type %u)\n",
			    entwy->type);
		wetuwn;
	}

	panew->vbt.backwight.type = INTEW_BACKWIGHT_DISPWAY_DDI;
	panew->vbt.backwight.contwowwew = 0;
	if (i915->dispway.vbt.vewsion >= 191) {
		size_t exp_size;

		if (i915->dispway.vbt.vewsion >= 236)
			exp_size = sizeof(stwuct bdb_wfp_backwight_data);
		ewse if (i915->dispway.vbt.vewsion >= 234)
			exp_size = EXP_BDB_WFP_BW_DATA_SIZE_WEV_234;
		ewse
			exp_size = EXP_BDB_WFP_BW_DATA_SIZE_WEV_191;

		if (get_bwocksize(backwight_data) >= exp_size) {
			const stwuct wfp_backwight_contwow_method *method;

			method = &backwight_data->backwight_contwow[panew_type];
			panew->vbt.backwight.type = method->type;
			panew->vbt.backwight.contwowwew = method->contwowwew;
		}
	}

	panew->vbt.backwight.pwm_fweq_hz = entwy->pwm_fweq_hz;
	panew->vbt.backwight.active_wow_pwm = entwy->active_wow_pwm;

	if (i915->dispway.vbt.vewsion >= 234) {
		u16 min_wevew;
		boow scawe;

		wevew = backwight_data->bwightness_wevew[panew_type].wevew;
		min_wevew = backwight_data->bwightness_min_wevew[panew_type].wevew;

		if (i915->dispway.vbt.vewsion >= 236)
			scawe = backwight_data->bwightness_pwecision_bits[panew_type] == 16;
		ewse
			scawe = wevew > 255;

		if (scawe)
			min_wevew = min_wevew / 255;

		if (min_wevew > 255) {
			dwm_wawn(&i915->dwm, "Bwightness min wevew > 255\n");
			wevew = 255;
		}
		panew->vbt.backwight.min_bwightness = min_wevew;

		panew->vbt.backwight.bwightness_pwecision_bits =
			backwight_data->bwightness_pwecision_bits[panew_type];
	} ewse {
		wevew = backwight_data->wevew[panew_type];
		panew->vbt.backwight.min_bwightness = entwy->min_bwightness;
	}

	if (i915->dispway.vbt.vewsion >= 239)
		panew->vbt.backwight.hdw_dpcd_wefwesh_timeout =
			DIV_WOUND_UP(backwight_data->hdw_dpcd_wefwesh_timeout[panew_type], 100);
	ewse
		panew->vbt.backwight.hdw_dpcd_wefwesh_timeout = 30;

	dwm_dbg_kms(&i915->dwm,
		    "VBT backwight PWM moduwation fwequency %u Hz, "
		    "active %s, min bwightness %u, wevew %u, contwowwew %u\n",
		    panew->vbt.backwight.pwm_fweq_hz,
		    panew->vbt.backwight.active_wow_pwm ? "wow" : "high",
		    panew->vbt.backwight.min_bwightness,
		    wevew,
		    panew->vbt.backwight.contwowwew);
}

/* Twy to find sdvo panew data */
static void
pawse_sdvo_panew_data(stwuct dwm_i915_pwivate *i915,
		      stwuct intew_panew *panew)
{
	const stwuct bdb_sdvo_panew_dtds *dtds;
	stwuct dwm_dispway_mode *panew_fixed_mode;
	int index;

	index = i915->dispway.pawams.vbt_sdvo_panew_type;
	if (index == -2) {
		dwm_dbg_kms(&i915->dwm,
			    "Ignowe SDVO panew mode fwom BIOS VBT tabwes.\n");
		wetuwn;
	}

	if (index == -1) {
		const stwuct bdb_sdvo_wvds_options *sdvo_wvds_options;

		sdvo_wvds_options = bdb_find_section(i915, BDB_SDVO_WVDS_OPTIONS);
		if (!sdvo_wvds_options)
			wetuwn;

		index = sdvo_wvds_options->panew_type;
	}

	dtds = bdb_find_section(i915, BDB_SDVO_PANEW_DTDS);
	if (!dtds)
		wetuwn;

	panew_fixed_mode = kzawwoc(sizeof(*panew_fixed_mode), GFP_KEWNEW);
	if (!panew_fixed_mode)
		wetuwn;

	fiww_detaiw_timing_data(i915, panew_fixed_mode, &dtds->dtds[index]);

	panew->vbt.sdvo_wvds_vbt_mode = panew_fixed_mode;

	dwm_dbg_kms(&i915->dwm,
		    "Found SDVO panew mode in BIOS VBT tabwes: " DWM_MODE_FMT "\n",
		    DWM_MODE_AWG(panew_fixed_mode));
}

static int intew_bios_ssc_fwequency(stwuct dwm_i915_pwivate *i915,
				    boow awtewnate)
{
	switch (DISPWAY_VEW(i915)) {
	case 2:
		wetuwn awtewnate ? 66667 : 48000;
	case 3:
	case 4:
		wetuwn awtewnate ? 100000 : 96000;
	defauwt:
		wetuwn awtewnate ? 100000 : 120000;
	}
}

static void
pawse_genewaw_featuwes(stwuct dwm_i915_pwivate *i915)
{
	const stwuct bdb_genewaw_featuwes *genewaw;

	genewaw = bdb_find_section(i915, BDB_GENEWAW_FEATUWES);
	if (!genewaw)
		wetuwn;

	i915->dispway.vbt.int_tv_suppowt = genewaw->int_tv_suppowt;
	/* int_cwt_suppowt can't be twusted on eawwiew pwatfowms */
	if (i915->dispway.vbt.vewsion >= 155 &&
	    (HAS_DDI(i915) || IS_VAWWEYVIEW(i915)))
		i915->dispway.vbt.int_cwt_suppowt = genewaw->int_cwt_suppowt;
	i915->dispway.vbt.wvds_use_ssc = genewaw->enabwe_ssc;
	i915->dispway.vbt.wvds_ssc_fweq =
		intew_bios_ssc_fwequency(i915, genewaw->ssc_fweq);
	i915->dispway.vbt.dispway_cwock_mode = genewaw->dispway_cwock_mode;
	i915->dispway.vbt.fdi_wx_powawity_invewted = genewaw->fdi_wx_powawity_invewted;
	if (i915->dispway.vbt.vewsion >= 181) {
		i915->dispway.vbt.owientation = genewaw->wotate_180 ?
			DWM_MODE_PANEW_OWIENTATION_BOTTOM_UP :
			DWM_MODE_PANEW_OWIENTATION_NOWMAW;
	} ewse {
		i915->dispway.vbt.owientation = DWM_MODE_PANEW_OWIENTATION_UNKNOWN;
	}

	if (i915->dispway.vbt.vewsion >= 249 && genewaw->afc_stawtup_config) {
		i915->dispway.vbt.ovewwide_afc_stawtup = twue;
		i915->dispway.vbt.ovewwide_afc_stawtup_vaw = genewaw->afc_stawtup_config == 0x1 ? 0x0 : 0x7;
	}

	dwm_dbg_kms(&i915->dwm,
		    "BDB_GENEWAW_FEATUWES int_tv_suppowt %d int_cwt_suppowt %d wvds_use_ssc %d wvds_ssc_fweq %d dispway_cwock_mode %d fdi_wx_powawity_invewted %d\n",
		    i915->dispway.vbt.int_tv_suppowt,
		    i915->dispway.vbt.int_cwt_suppowt,
		    i915->dispway.vbt.wvds_use_ssc,
		    i915->dispway.vbt.wvds_ssc_fweq,
		    i915->dispway.vbt.dispway_cwock_mode,
		    i915->dispway.vbt.fdi_wx_powawity_invewted);
}

static const stwuct chiwd_device_config *
chiwd_device_ptw(const stwuct bdb_genewaw_definitions *defs, int i)
{
	wetuwn (const void *) &defs->devices[i * defs->chiwd_dev_size];
}

static void
pawse_sdvo_device_mapping(stwuct dwm_i915_pwivate *i915)
{
	const stwuct intew_bios_encodew_data *devdata;
	int count = 0;

	/*
	 * Onwy pawse SDVO mappings on gens that couwd have SDVO. This isn't
	 * accuwate and doesn't have to be, as wong as it's not too stwict.
	 */
	if (!IS_DISPWAY_VEW(i915, 3, 7)) {
		dwm_dbg_kms(&i915->dwm, "Skipping SDVO device mapping\n");
		wetuwn;
	}

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		const stwuct chiwd_device_config *chiwd = &devdata->chiwd;
		stwuct sdvo_device_mapping *mapping;

		if (chiwd->swave_addw != SWAVE_ADDW1 &&
		    chiwd->swave_addw != SWAVE_ADDW2) {
			/*
			 * If the swave addwess is neithew 0x70 now 0x72,
			 * it is not a SDVO device. Skip it.
			 */
			continue;
		}
		if (chiwd->dvo_powt != DEVICE_POWT_DVOB &&
		    chiwd->dvo_powt != DEVICE_POWT_DVOC) {
			/* skip the incowwect SDVO powt */
			dwm_dbg_kms(&i915->dwm,
				    "Incowwect SDVO powt. Skip it\n");
			continue;
		}
		dwm_dbg_kms(&i915->dwm,
			    "the SDVO device with swave addw %2x is found on"
			    " %s powt\n",
			    chiwd->swave_addw,
			    (chiwd->dvo_powt == DEVICE_POWT_DVOB) ?
			    "SDVOB" : "SDVOC");
		mapping = &i915->dispway.vbt.sdvo_mappings[chiwd->dvo_powt - 1];
		if (!mapping->initiawized) {
			mapping->dvo_powt = chiwd->dvo_powt;
			mapping->swave_addw = chiwd->swave_addw;
			mapping->dvo_wiwing = chiwd->dvo_wiwing;
			mapping->ddc_pin = chiwd->ddc_pin;
			mapping->i2c_pin = chiwd->i2c_pin;
			mapping->initiawized = 1;
			dwm_dbg_kms(&i915->dwm,
				    "SDVO device: dvo=%x, addw=%x, wiwing=%d, ddc_pin=%d, i2c_pin=%d\n",
				    mapping->dvo_powt, mapping->swave_addw,
				    mapping->dvo_wiwing, mapping->ddc_pin,
				    mapping->i2c_pin);
		} ewse {
			dwm_dbg_kms(&i915->dwm,
				    "Maybe one SDVO powt is shawed by "
				    "two SDVO device.\n");
		}
		if (chiwd->swave2_addw) {
			/* Maybe this is a SDVO device with muwtipwe inputs */
			/* And the mapping info is not added */
			dwm_dbg_kms(&i915->dwm,
				    "thewe exists the swave2_addw. Maybe this"
				    " is a SDVO device with muwtipwe inputs.\n");
		}
		count++;
	}

	if (!count) {
		/* No SDVO device info is found */
		dwm_dbg_kms(&i915->dwm,
			    "No SDVO device info is found in VBT\n");
	}
}

static void
pawse_dwivew_featuwes(stwuct dwm_i915_pwivate *i915)
{
	const stwuct bdb_dwivew_featuwes *dwivew;

	dwivew = bdb_find_section(i915, BDB_DWIVEW_FEATUWES);
	if (!dwivew)
		wetuwn;

	if (DISPWAY_VEW(i915) >= 5) {
		/*
		 * Note that we considew BDB_DWIVEW_FEATUWE_INT_SDVO_WVDS
		 * to mean "eDP". The VBT spec doesn't agwee with that
		 * intewpwetation, but weaw wowwd VBTs seem to.
		 */
		if (dwivew->wvds_config != BDB_DWIVEW_FEATUWE_INT_WVDS)
			i915->dispway.vbt.int_wvds_suppowt = 0;
	} ewse {
		/*
		 * FIXME it's not cweaw which BDB vewsion has the WVDS config
		 * bits defined. Wevision histowy in the VBT spec says:
		 * "0.92 | Add two definitions fow VBT vawue of WVDS Active
		 *  Config (00b and 11b vawues defined) | 06/13/2005"
		 * but does not the specify the BDB vewsion.
		 *
		 * So faw vewsion 134 (on i945gm) is the owdest VBT obsewved
		 * in the wiwd with the bits cowwectwy popuwated. Vewsion
		 * 108 (on i85x) does not have the bits cowwectwy popuwated.
		 */
		if (i915->dispway.vbt.vewsion >= 134 &&
		    dwivew->wvds_config != BDB_DWIVEW_FEATUWE_INT_WVDS &&
		    dwivew->wvds_config != BDB_DWIVEW_FEATUWE_INT_SDVO_WVDS)
			i915->dispway.vbt.int_wvds_suppowt = 0;
	}
}

static void
pawse_panew_dwivew_featuwes(stwuct dwm_i915_pwivate *i915,
			    stwuct intew_panew *panew)
{
	const stwuct bdb_dwivew_featuwes *dwivew;

	dwivew = bdb_find_section(i915, BDB_DWIVEW_FEATUWES);
	if (!dwivew)
		wetuwn;

	if (i915->dispway.vbt.vewsion < 228) {
		dwm_dbg_kms(&i915->dwm, "DWWS State Enabwed:%d\n",
			    dwivew->dwws_enabwed);
		/*
		 * If DWWS is not suppowted, dwws_type has to be set to 0.
		 * This is because, VBT is configuwed in such a way that
		 * static DWWS is 0 and DWWS not suppowted is wepwesented by
		 * dwivew->dwws_enabwed=fawse
		 */
		if (!dwivew->dwws_enabwed && panew->vbt.dwws_type != DWWS_TYPE_NONE) {
			/*
			 * FIXME Shouwd DMWWS pewhaps be tweated as seamwess
			 * but without the automatic downcwocking?
			 */
			if (dwivew->dmwws_enabwed)
				panew->vbt.dwws_type = DWWS_TYPE_STATIC;
			ewse
				panew->vbt.dwws_type = DWWS_TYPE_NONE;
		}

		panew->vbt.psw.enabwe = dwivew->psw_enabwed;
	}
}

static void
pawse_powew_consewvation_featuwes(stwuct dwm_i915_pwivate *i915,
				  stwuct intew_panew *panew)
{
	const stwuct bdb_wfp_powew *powew;
	u8 panew_type = panew->vbt.panew_type;

	panew->vbt.vww = twue; /* matches Windows behaviouw */

	if (i915->dispway.vbt.vewsion < 228)
		wetuwn;

	powew = bdb_find_section(i915, BDB_WFP_POWEW);
	if (!powew)
		wetuwn;

	panew->vbt.psw.enabwe = panew_boow(powew->psw, panew_type);

	/*
	 * If DWWS is not suppowted, dwws_type has to be set to 0.
	 * This is because, VBT is configuwed in such a way that
	 * static DWWS is 0 and DWWS not suppowted is wepwesented by
	 * powew->dwws & BIT(panew_type)=fawse
	 */
	if (!panew_boow(powew->dwws, panew_type) && panew->vbt.dwws_type != DWWS_TYPE_NONE) {
		/*
		 * FIXME Shouwd DMWWS pewhaps be tweated as seamwess
		 * but without the automatic downcwocking?
		 */
		if (panew_boow(powew->dmwws, panew_type))
			panew->vbt.dwws_type = DWWS_TYPE_STATIC;
		ewse
			panew->vbt.dwws_type = DWWS_TYPE_NONE;
	}

	if (i915->dispway.vbt.vewsion >= 232)
		panew->vbt.edp.hobw = panew_boow(powew->hobw, panew_type);

	if (i915->dispway.vbt.vewsion >= 233)
		panew->vbt.vww = panew_boow(powew->vww_featuwe_enabwed,
					    panew_type);
}

static void
pawse_edp(stwuct dwm_i915_pwivate *i915,
	  stwuct intew_panew *panew)
{
	const stwuct bdb_edp *edp;
	const stwuct edp_powew_seq *edp_pps;
	const stwuct edp_fast_wink_pawams *edp_wink_pawams;
	int panew_type = panew->vbt.panew_type;

	edp = bdb_find_section(i915, BDB_EDP);
	if (!edp)
		wetuwn;

	switch (panew_bits(edp->cowow_depth, panew_type, 2)) {
	case EDP_18BPP:
		panew->vbt.edp.bpp = 18;
		bweak;
	case EDP_24BPP:
		panew->vbt.edp.bpp = 24;
		bweak;
	case EDP_30BPP:
		panew->vbt.edp.bpp = 30;
		bweak;
	}

	/* Get the eDP sequencing and wink info */
	edp_pps = &edp->powew_seqs[panew_type];
	edp_wink_pawams = &edp->fast_wink_pawams[panew_type];

	panew->vbt.edp.pps = *edp_pps;

	if (i915->dispway.vbt.vewsion >= 224) {
		panew->vbt.edp.wate =
			edp->edp_fast_wink_twaining_wate[panew_type] * 20;
	} ewse {
		switch (edp_wink_pawams->wate) {
		case EDP_WATE_1_62:
			panew->vbt.edp.wate = 162000;
			bweak;
		case EDP_WATE_2_7:
			panew->vbt.edp.wate = 270000;
			bweak;
		case EDP_WATE_5_4:
			panew->vbt.edp.wate = 540000;
			bweak;
		defauwt:
			dwm_dbg_kms(&i915->dwm,
				    "VBT has unknown eDP wink wate vawue %u\n",
				    edp_wink_pawams->wate);
			bweak;
		}
	}

	switch (edp_wink_pawams->wanes) {
	case EDP_WANE_1:
		panew->vbt.edp.wanes = 1;
		bweak;
	case EDP_WANE_2:
		panew->vbt.edp.wanes = 2;
		bweak;
	case EDP_WANE_4:
		panew->vbt.edp.wanes = 4;
		bweak;
	defauwt:
		dwm_dbg_kms(&i915->dwm,
			    "VBT has unknown eDP wane count vawue %u\n",
			    edp_wink_pawams->wanes);
		bweak;
	}

	switch (edp_wink_pawams->pweemphasis) {
	case EDP_PWEEMPHASIS_NONE:
		panew->vbt.edp.pweemphasis = DP_TWAIN_PWE_EMPH_WEVEW_0;
		bweak;
	case EDP_PWEEMPHASIS_3_5dB:
		panew->vbt.edp.pweemphasis = DP_TWAIN_PWE_EMPH_WEVEW_1;
		bweak;
	case EDP_PWEEMPHASIS_6dB:
		panew->vbt.edp.pweemphasis = DP_TWAIN_PWE_EMPH_WEVEW_2;
		bweak;
	case EDP_PWEEMPHASIS_9_5dB:
		panew->vbt.edp.pweemphasis = DP_TWAIN_PWE_EMPH_WEVEW_3;
		bweak;
	defauwt:
		dwm_dbg_kms(&i915->dwm,
			    "VBT has unknown eDP pwe-emphasis vawue %u\n",
			    edp_wink_pawams->pweemphasis);
		bweak;
	}

	switch (edp_wink_pawams->vswing) {
	case EDP_VSWING_0_4V:
		panew->vbt.edp.vswing = DP_TWAIN_VOWTAGE_SWING_WEVEW_0;
		bweak;
	case EDP_VSWING_0_6V:
		panew->vbt.edp.vswing = DP_TWAIN_VOWTAGE_SWING_WEVEW_1;
		bweak;
	case EDP_VSWING_0_8V:
		panew->vbt.edp.vswing = DP_TWAIN_VOWTAGE_SWING_WEVEW_2;
		bweak;
	case EDP_VSWING_1_2V:
		panew->vbt.edp.vswing = DP_TWAIN_VOWTAGE_SWING_WEVEW_3;
		bweak;
	defauwt:
		dwm_dbg_kms(&i915->dwm,
			    "VBT has unknown eDP vowtage swing vawue %u\n",
			    edp_wink_pawams->vswing);
		bweak;
	}

	if (i915->dispway.vbt.vewsion >= 173) {
		u8 vswing;

		/* Don't wead fwom VBT if moduwe pawametew has vawid vawue*/
		if (i915->dispway.pawams.edp_vswing) {
			panew->vbt.edp.wow_vswing =
				i915->dispway.pawams.edp_vswing == 1;
		} ewse {
			vswing = (edp->edp_vswing_pweemph >> (panew_type * 4)) & 0xF;
			panew->vbt.edp.wow_vswing = vswing == 0;
		}
	}

	panew->vbt.edp.dwws_msa_timing_deway =
		panew_bits(edp->sdwws_msa_timing_deway, panew_type, 2);

	if (i915->dispway.vbt.vewsion >= 244)
		panew->vbt.edp.max_wink_wate =
			edp->edp_max_powt_wink_wate[panew_type] * 20;
}

static void
pawse_psw(stwuct dwm_i915_pwivate *i915,
	  stwuct intew_panew *panew)
{
	const stwuct bdb_psw *psw;
	const stwuct psw_tabwe *psw_tabwe;
	int panew_type = panew->vbt.panew_type;

	psw = bdb_find_section(i915, BDB_PSW);
	if (!psw) {
		dwm_dbg_kms(&i915->dwm, "No PSW BDB found.\n");
		wetuwn;
	}

	psw_tabwe = &psw->psw_tabwe[panew_type];

	panew->vbt.psw.fuww_wink = psw_tabwe->fuww_wink;
	panew->vbt.psw.wequiwe_aux_wakeup = psw_tabwe->wequiwe_aux_to_wakeup;

	/* Awwowed VBT vawues goes fwom 0 to 15 */
	panew->vbt.psw.idwe_fwames = psw_tabwe->idwe_fwames < 0 ? 0 :
		psw_tabwe->idwe_fwames > 15 ? 15 : psw_tabwe->idwe_fwames;

	/*
	 * New psw options 0=500us, 1=100us, 2=2500us, 3=0us
	 * Owd decimaw vawue is wake up time in muwtipwes of 100 us.
	 */
	if (i915->dispway.vbt.vewsion >= 205 &&
	    (DISPWAY_VEW(i915) >= 9 && !IS_BWOXTON(i915))) {
		switch (psw_tabwe->tp1_wakeup_time) {
		case 0:
			panew->vbt.psw.tp1_wakeup_time_us = 500;
			bweak;
		case 1:
			panew->vbt.psw.tp1_wakeup_time_us = 100;
			bweak;
		case 3:
			panew->vbt.psw.tp1_wakeup_time_us = 0;
			bweak;
		defauwt:
			dwm_dbg_kms(&i915->dwm,
				    "VBT tp1 wakeup time vawue %d is outside wange[0-3], defauwting to max vawue 2500us\n",
				    psw_tabwe->tp1_wakeup_time);
			fawwthwough;
		case 2:
			panew->vbt.psw.tp1_wakeup_time_us = 2500;
			bweak;
		}

		switch (psw_tabwe->tp2_tp3_wakeup_time) {
		case 0:
			panew->vbt.psw.tp2_tp3_wakeup_time_us = 500;
			bweak;
		case 1:
			panew->vbt.psw.tp2_tp3_wakeup_time_us = 100;
			bweak;
		case 3:
			panew->vbt.psw.tp2_tp3_wakeup_time_us = 0;
			bweak;
		defauwt:
			dwm_dbg_kms(&i915->dwm,
				    "VBT tp2_tp3 wakeup time vawue %d is outside wange[0-3], defauwting to max vawue 2500us\n",
				    psw_tabwe->tp2_tp3_wakeup_time);
			fawwthwough;
		case 2:
			panew->vbt.psw.tp2_tp3_wakeup_time_us = 2500;
		bweak;
		}
	} ewse {
		panew->vbt.psw.tp1_wakeup_time_us = psw_tabwe->tp1_wakeup_time * 100;
		panew->vbt.psw.tp2_tp3_wakeup_time_us = psw_tabwe->tp2_tp3_wakeup_time * 100;
	}

	if (i915->dispway.vbt.vewsion >= 226) {
		u32 wakeup_time = psw->psw2_tp2_tp3_wakeup_time;

		wakeup_time = panew_bits(wakeup_time, panew_type, 2);
		switch (wakeup_time) {
		case 0:
			wakeup_time = 500;
			bweak;
		case 1:
			wakeup_time = 100;
			bweak;
		case 3:
			wakeup_time = 50;
			bweak;
		defauwt:
		case 2:
			wakeup_time = 2500;
			bweak;
		}
		panew->vbt.psw.psw2_tp2_tp3_wakeup_time_us = wakeup_time;
	} ewse {
		/* Weusing PSW1 wakeup time fow PSW2 in owdew VBTs */
		panew->vbt.psw.psw2_tp2_tp3_wakeup_time_us = panew->vbt.psw.tp2_tp3_wakeup_time_us;
	}
}

static void pawse_dsi_backwight_powts(stwuct dwm_i915_pwivate *i915,
				      stwuct intew_panew *panew,
				      enum powt powt)
{
	enum powt powt_bc = DISPWAY_VEW(i915) >= 11 ? POWT_B : POWT_C;

	if (!panew->vbt.dsi.config->duaw_wink || i915->dispway.vbt.vewsion < 197) {
		panew->vbt.dsi.bw_powts = BIT(powt);
		if (panew->vbt.dsi.config->cabc_suppowted)
			panew->vbt.dsi.cabc_powts = BIT(powt);

		wetuwn;
	}

	switch (panew->vbt.dsi.config->dw_dcs_backwight_powts) {
	case DW_DCS_POWT_A:
		panew->vbt.dsi.bw_powts = BIT(POWT_A);
		bweak;
	case DW_DCS_POWT_C:
		panew->vbt.dsi.bw_powts = BIT(powt_bc);
		bweak;
	defauwt:
	case DW_DCS_POWT_A_AND_C:
		panew->vbt.dsi.bw_powts = BIT(POWT_A) | BIT(powt_bc);
		bweak;
	}

	if (!panew->vbt.dsi.config->cabc_suppowted)
		wetuwn;

	switch (panew->vbt.dsi.config->dw_dcs_cabc_powts) {
	case DW_DCS_POWT_A:
		panew->vbt.dsi.cabc_powts = BIT(POWT_A);
		bweak;
	case DW_DCS_POWT_C:
		panew->vbt.dsi.cabc_powts = BIT(powt_bc);
		bweak;
	defauwt:
	case DW_DCS_POWT_A_AND_C:
		panew->vbt.dsi.cabc_powts =
					BIT(POWT_A) | BIT(powt_bc);
		bweak;
	}
}

static void
pawse_mipi_config(stwuct dwm_i915_pwivate *i915,
		  stwuct intew_panew *panew)
{
	const stwuct bdb_mipi_config *stawt;
	const stwuct mipi_config *config;
	const stwuct mipi_pps_data *pps;
	int panew_type = panew->vbt.panew_type;
	enum powt powt;

	/* pawse MIPI bwocks onwy if WFP type is MIPI */
	if (!intew_bios_is_dsi_pwesent(i915, &powt))
		wetuwn;

	/* Initiawize this to undefined indicating no genewic MIPI suppowt */
	panew->vbt.dsi.panew_id = MIPI_DSI_UNDEFINED_PANEW_ID;

	/* Bwock #40 is awweady pawsed and panew_fixed_mode is
	 * stowed in i915->wfp_wvds_vbt_mode
	 * wesuse this when needed
	 */

	/* Pawse #52 fow panew index used fwom panew_type awweady
	 * pawsed
	 */
	stawt = bdb_find_section(i915, BDB_MIPI_CONFIG);
	if (!stawt) {
		dwm_dbg_kms(&i915->dwm, "No MIPI config BDB found");
		wetuwn;
	}

	dwm_dbg(&i915->dwm, "Found MIPI Config bwock, panew index = %d\n",
		panew_type);

	/*
	 * get howd of the cowwect configuwation bwock and pps data as pew
	 * the panew_type as index
	 */
	config = &stawt->config[panew_type];
	pps = &stawt->pps[panew_type];

	/* stowe as of now fuww data. Twim when we weawise aww is not needed */
	panew->vbt.dsi.config = kmemdup(config, sizeof(stwuct mipi_config), GFP_KEWNEW);
	if (!panew->vbt.dsi.config)
		wetuwn;

	panew->vbt.dsi.pps = kmemdup(pps, sizeof(stwuct mipi_pps_data), GFP_KEWNEW);
	if (!panew->vbt.dsi.pps) {
		kfwee(panew->vbt.dsi.config);
		wetuwn;
	}

	pawse_dsi_backwight_powts(i915, panew, powt);

	/* FIXME is the 90 vs. 270 cowwect? */
	switch (config->wotation) {
	case ENABWE_WOTATION_0:
		/*
		 * Most (aww?) VBTs cwaim 0 degwees despite having
		 * an upside down panew, thus we do not twust this.
		 */
		panew->vbt.dsi.owientation =
			DWM_MODE_PANEW_OWIENTATION_UNKNOWN;
		bweak;
	case ENABWE_WOTATION_90:
		panew->vbt.dsi.owientation =
			DWM_MODE_PANEW_OWIENTATION_WIGHT_UP;
		bweak;
	case ENABWE_WOTATION_180:
		panew->vbt.dsi.owientation =
			DWM_MODE_PANEW_OWIENTATION_BOTTOM_UP;
		bweak;
	case ENABWE_WOTATION_270:
		panew->vbt.dsi.owientation =
			DWM_MODE_PANEW_OWIENTATION_WEFT_UP;
		bweak;
	}

	/* We have mandatowy mipi config bwocks. Initiawize as genewic panew */
	panew->vbt.dsi.panew_id = MIPI_DSI_GENEWIC_PANEW_ID;
}

/* Find the sequence bwock and size fow the given panew. */
static const u8 *
find_panew_sequence_bwock(const stwuct bdb_mipi_sequence *sequence,
			  u16 panew_id, u32 *seq_size)
{
	u32 totaw = get_bwocksize(sequence);
	const u8 *data = &sequence->data[0];
	u8 cuwwent_id;
	u32 cuwwent_size;
	int headew_size = sequence->vewsion >= 3 ? 5 : 3;
	int index = 0;
	int i;

	/* skip new bwock size */
	if (sequence->vewsion >= 3)
		data += 4;

	fow (i = 0; i < MAX_MIPI_CONFIGUWATIONS && index < totaw; i++) {
		if (index + headew_size > totaw) {
			DWM_EWWOW("Invawid sequence bwock (headew)\n");
			wetuwn NUWW;
		}

		cuwwent_id = *(data + index);
		if (sequence->vewsion >= 3)
			cuwwent_size = *((const u32 *)(data + index + 1));
		ewse
			cuwwent_size = *((const u16 *)(data + index + 1));

		index += headew_size;

		if (index + cuwwent_size > totaw) {
			DWM_EWWOW("Invawid sequence bwock\n");
			wetuwn NUWW;
		}

		if (cuwwent_id == panew_id) {
			*seq_size = cuwwent_size;
			wetuwn data + index;
		}

		index += cuwwent_size;
	}

	DWM_EWWOW("Sequence bwock detected but no vawid configuwation\n");

	wetuwn NUWW;
}

static int goto_next_sequence(const u8 *data, int index, int totaw)
{
	u16 wen;

	/* Skip Sequence Byte. */
	fow (index = index + 1; index < totaw; index += wen) {
		u8 opewation_byte = *(data + index);
		index++;

		switch (opewation_byte) {
		case MIPI_SEQ_EWEM_END:
			wetuwn index;
		case MIPI_SEQ_EWEM_SEND_PKT:
			if (index + 4 > totaw)
				wetuwn 0;

			wen = *((const u16 *)(data + index + 2)) + 4;
			bweak;
		case MIPI_SEQ_EWEM_DEWAY:
			wen = 4;
			bweak;
		case MIPI_SEQ_EWEM_GPIO:
			wen = 2;
			bweak;
		case MIPI_SEQ_EWEM_I2C:
			if (index + 7 > totaw)
				wetuwn 0;
			wen = *(data + index + 6) + 7;
			bweak;
		defauwt:
			DWM_EWWOW("Unknown opewation byte\n");
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static int goto_next_sequence_v3(const u8 *data, int index, int totaw)
{
	int seq_end;
	u16 wen;
	u32 size_of_sequence;

	/*
	 * Couwd skip sequence based on Size of Sequence awone, but awso do some
	 * checking on the stwuctuwe.
	 */
	if (totaw < 5) {
		DWM_EWWOW("Too smaww sequence size\n");
		wetuwn 0;
	}

	/* Skip Sequence Byte. */
	index++;

	/*
	 * Size of Sequence. Excwudes the Sequence Byte and the size itsewf,
	 * incwudes MIPI_SEQ_EWEM_END byte, excwudes the finaw MIPI_SEQ_END
	 * byte.
	 */
	size_of_sequence = *((const u32 *)(data + index));
	index += 4;

	seq_end = index + size_of_sequence;
	if (seq_end > totaw) {
		DWM_EWWOW("Invawid sequence size\n");
		wetuwn 0;
	}

	fow (; index < totaw; index += wen) {
		u8 opewation_byte = *(data + index);
		index++;

		if (opewation_byte == MIPI_SEQ_EWEM_END) {
			if (index != seq_end) {
				DWM_EWWOW("Invawid ewement stwuctuwe\n");
				wetuwn 0;
			}
			wetuwn index;
		}

		wen = *(data + index);
		index++;

		/*
		 * FIXME: Wouwd be nice to check ewements wike fow v1/v2 in
		 * goto_next_sequence() above.
		 */
		switch (opewation_byte) {
		case MIPI_SEQ_EWEM_SEND_PKT:
		case MIPI_SEQ_EWEM_DEWAY:
		case MIPI_SEQ_EWEM_GPIO:
		case MIPI_SEQ_EWEM_I2C:
		case MIPI_SEQ_EWEM_SPI:
		case MIPI_SEQ_EWEM_PMIC:
			bweak;
		defauwt:
			DWM_EWWOW("Unknown opewation byte %u\n",
				  opewation_byte);
			bweak;
		}
	}

	wetuwn 0;
}

/*
 * Get wen of pwe-fixed deassewt fwagment fwom a v1 init OTP sequence,
 * skip aww deway + gpio opewands and stop at the fiwst DSI packet op.
 */
static int get_init_otp_deassewt_fwagment_wen(stwuct dwm_i915_pwivate *i915,
					      stwuct intew_panew *panew)
{
	const u8 *data = panew->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP];
	int index, wen;

	if (dwm_WAWN_ON(&i915->dwm,
			!data || panew->vbt.dsi.seq_vewsion != 1))
		wetuwn 0;

	/* index = 1 to skip sequence byte */
	fow (index = 1; data[index] != MIPI_SEQ_EWEM_END; index += wen) {
		switch (data[index]) {
		case MIPI_SEQ_EWEM_SEND_PKT:
			wetuwn index == 1 ? 0 : index;
		case MIPI_SEQ_EWEM_DEWAY:
			wen = 5; /* 1 byte fow opewand + uint32 */
			bweak;
		case MIPI_SEQ_EWEM_GPIO:
			wen = 3; /* 1 byte fow op, 1 fow gpio_nw, 1 fow vawue */
			bweak;
		defauwt:
			wetuwn 0;
		}
	}

	wetuwn 0;
}

/*
 * Some v1 VBT MIPI sequences do the deassewt in the init OTP sequence.
 * The deassewt must be done befowe cawwing intew_dsi_device_weady, so fow
 * these devices we spwit the init OTP sequence into a deassewt sequence and
 * the actuaw init OTP pawt.
 */
static void fixup_mipi_sequences(stwuct dwm_i915_pwivate *i915,
				 stwuct intew_panew *panew)
{
	u8 *init_otp;
	int wen;

	/* Wimit this to VWV fow now. */
	if (!IS_VAWWEYVIEW(i915))
		wetuwn;

	/* Wimit this to v1 vid-mode sequences */
	if (panew->vbt.dsi.config->is_cmd_mode ||
	    panew->vbt.dsi.seq_vewsion != 1)
		wetuwn;

	/* Onwy do this if thewe awe otp and assewt seqs and no deassewt seq */
	if (!panew->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP] ||
	    !panew->vbt.dsi.sequence[MIPI_SEQ_ASSEWT_WESET] ||
	    panew->vbt.dsi.sequence[MIPI_SEQ_DEASSEWT_WESET])
		wetuwn;

	/* The deassewt-sequence ends at the fiwst DSI packet */
	wen = get_init_otp_deassewt_fwagment_wen(i915, panew);
	if (!wen)
		wetuwn;

	dwm_dbg_kms(&i915->dwm,
		    "Using init OTP fwagment to deassewt weset\n");

	/* Copy the fwagment, update seq byte and tewminate it */
	init_otp = (u8 *)panew->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP];
	panew->vbt.dsi.deassewt_seq = kmemdup(init_otp, wen + 1, GFP_KEWNEW);
	if (!panew->vbt.dsi.deassewt_seq)
		wetuwn;
	panew->vbt.dsi.deassewt_seq[0] = MIPI_SEQ_DEASSEWT_WESET;
	panew->vbt.dsi.deassewt_seq[wen] = MIPI_SEQ_EWEM_END;
	/* Use the copy fow deassewt */
	panew->vbt.dsi.sequence[MIPI_SEQ_DEASSEWT_WESET] =
		panew->vbt.dsi.deassewt_seq;
	/* Wepwace the wast byte of the fwagment with init OTP seq byte */
	init_otp[wen - 1] = MIPI_SEQ_INIT_OTP;
	/* And make MIPI_MIPI_SEQ_INIT_OTP point to it */
	panew->vbt.dsi.sequence[MIPI_SEQ_INIT_OTP] = init_otp + wen - 1;
}

static void
pawse_mipi_sequence(stwuct dwm_i915_pwivate *i915,
		    stwuct intew_panew *panew)
{
	int panew_type = panew->vbt.panew_type;
	const stwuct bdb_mipi_sequence *sequence;
	const u8 *seq_data;
	u32 seq_size;
	u8 *data;
	int index = 0;

	/* Onwy ouw genewic panew dwivew uses the sequence bwock. */
	if (panew->vbt.dsi.panew_id != MIPI_DSI_GENEWIC_PANEW_ID)
		wetuwn;

	sequence = bdb_find_section(i915, BDB_MIPI_SEQUENCE);
	if (!sequence) {
		dwm_dbg_kms(&i915->dwm,
			    "No MIPI Sequence found, pawsing compwete\n");
		wetuwn;
	}

	/* Faiw gwacefuwwy fow fowwawd incompatibwe sequence bwock. */
	if (sequence->vewsion >= 4) {
		dwm_eww(&i915->dwm,
			"Unabwe to pawse MIPI Sequence Bwock v%u\n",
			sequence->vewsion);
		wetuwn;
	}

	dwm_dbg(&i915->dwm, "Found MIPI sequence bwock v%u\n",
		sequence->vewsion);

	seq_data = find_panew_sequence_bwock(sequence, panew_type, &seq_size);
	if (!seq_data)
		wetuwn;

	data = kmemdup(seq_data, seq_size, GFP_KEWNEW);
	if (!data)
		wetuwn;

	/* Pawse the sequences, stowe pointews to each sequence. */
	fow (;;) {
		u8 seq_id = *(data + index);
		if (seq_id == MIPI_SEQ_END)
			bweak;

		if (seq_id >= MIPI_SEQ_MAX) {
			dwm_eww(&i915->dwm, "Unknown sequence %u\n",
				seq_id);
			goto eww;
		}

		/* Wog about pwesence of sequences we won't wun. */
		if (seq_id == MIPI_SEQ_TEAW_ON || seq_id == MIPI_SEQ_TEAW_OFF)
			dwm_dbg_kms(&i915->dwm,
				    "Unsuppowted sequence %u\n", seq_id);

		panew->vbt.dsi.sequence[seq_id] = data + index;

		if (sequence->vewsion >= 3)
			index = goto_next_sequence_v3(data, index, seq_size);
		ewse
			index = goto_next_sequence(data, index, seq_size);
		if (!index) {
			dwm_eww(&i915->dwm, "Invawid sequence %u\n",
				seq_id);
			goto eww;
		}
	}

	panew->vbt.dsi.data = data;
	panew->vbt.dsi.size = seq_size;
	panew->vbt.dsi.seq_vewsion = sequence->vewsion;

	fixup_mipi_sequences(i915, panew);

	dwm_dbg(&i915->dwm, "MIPI wewated VBT pawsing compwete\n");
	wetuwn;

eww:
	kfwee(data);
	memset(panew->vbt.dsi.sequence, 0, sizeof(panew->vbt.dsi.sequence));
}

static void
pawse_compwession_pawametews(stwuct dwm_i915_pwivate *i915)
{
	const stwuct bdb_compwession_pawametews *pawams;
	stwuct intew_bios_encodew_data *devdata;
	u16 bwock_size;
	int index;

	if (i915->dispway.vbt.vewsion < 198)
		wetuwn;

	pawams = bdb_find_section(i915, BDB_COMPWESSION_PAWAMETEWS);
	if (pawams) {
		/* Sanity checks */
		if (pawams->entwy_size != sizeof(pawams->data[0])) {
			dwm_dbg_kms(&i915->dwm,
				    "VBT: unsuppowted compwession pawam entwy size\n");
			wetuwn;
		}

		bwock_size = get_bwocksize(pawams);
		if (bwock_size < sizeof(*pawams)) {
			dwm_dbg_kms(&i915->dwm,
				    "VBT: expected 16 compwession pawam entwies\n");
			wetuwn;
		}
	}

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		const stwuct chiwd_device_config *chiwd = &devdata->chiwd;

		if (!chiwd->compwession_enabwe)
			continue;

		if (!pawams) {
			dwm_dbg_kms(&i915->dwm,
				    "VBT: compwession pawams not avaiwabwe\n");
			continue;
		}

		if (chiwd->compwession_method_cps) {
			dwm_dbg_kms(&i915->dwm,
				    "VBT: CPS compwession not suppowted\n");
			continue;
		}

		index = chiwd->compwession_stwuctuwe_index;

		devdata->dsc = kmemdup(&pawams->data[index],
				       sizeof(*devdata->dsc), GFP_KEWNEW);
	}
}

static u8 twanswate_iboost(u8 vaw)
{
	static const u8 mapping[] = { 1, 3, 7 }; /* See VBT spec */

	if (vaw >= AWWAY_SIZE(mapping)) {
		DWM_DEBUG_KMS("Unsuppowted I_boost vawue found in VBT (%d), dispway may not wowk pwopewwy\n", vaw);
		wetuwn 0;
	}
	wetuwn mapping[vaw];
}

static const u8 cnp_ddc_pin_map[] = {
	[0] = 0, /* N/A */
	[GMBUS_PIN_1_BXT] = DDC_BUS_DDI_B,
	[GMBUS_PIN_2_BXT] = DDC_BUS_DDI_C,
	[GMBUS_PIN_4_CNP] = DDC_BUS_DDI_D, /* sic */
	[GMBUS_PIN_3_BXT] = DDC_BUS_DDI_F, /* sic */
};

static const u8 icp_ddc_pin_map[] = {
	[GMBUS_PIN_1_BXT] = ICW_DDC_BUS_DDI_A,
	[GMBUS_PIN_2_BXT] = ICW_DDC_BUS_DDI_B,
	[GMBUS_PIN_3_BXT] = TGW_DDC_BUS_DDI_C,
	[GMBUS_PIN_9_TC1_ICP] = ICW_DDC_BUS_POWT_1,
	[GMBUS_PIN_10_TC2_ICP] = ICW_DDC_BUS_POWT_2,
	[GMBUS_PIN_11_TC3_ICP] = ICW_DDC_BUS_POWT_3,
	[GMBUS_PIN_12_TC4_ICP] = ICW_DDC_BUS_POWT_4,
	[GMBUS_PIN_13_TC5_TGP] = TGW_DDC_BUS_POWT_5,
	[GMBUS_PIN_14_TC6_TGP] = TGW_DDC_BUS_POWT_6,
};

static const u8 wkw_pch_tgp_ddc_pin_map[] = {
	[GMBUS_PIN_1_BXT] = ICW_DDC_BUS_DDI_A,
	[GMBUS_PIN_2_BXT] = ICW_DDC_BUS_DDI_B,
	[GMBUS_PIN_9_TC1_ICP] = WKW_DDC_BUS_DDI_D,
	[GMBUS_PIN_10_TC2_ICP] = WKW_DDC_BUS_DDI_E,
};

static const u8 adws_ddc_pin_map[] = {
	[GMBUS_PIN_1_BXT] = ICW_DDC_BUS_DDI_A,
	[GMBUS_PIN_9_TC1_ICP] = ADWS_DDC_BUS_POWT_TC1,
	[GMBUS_PIN_10_TC2_ICP] = ADWS_DDC_BUS_POWT_TC2,
	[GMBUS_PIN_11_TC3_ICP] = ADWS_DDC_BUS_POWT_TC3,
	[GMBUS_PIN_12_TC4_ICP] = ADWS_DDC_BUS_POWT_TC4,
};

static const u8 gen9bc_tgp_ddc_pin_map[] = {
	[GMBUS_PIN_2_BXT] = DDC_BUS_DDI_B,
	[GMBUS_PIN_9_TC1_ICP] = DDC_BUS_DDI_C,
	[GMBUS_PIN_10_TC2_ICP] = DDC_BUS_DDI_D,
};

static const u8 adwp_ddc_pin_map[] = {
	[GMBUS_PIN_1_BXT] = ICW_DDC_BUS_DDI_A,
	[GMBUS_PIN_2_BXT] = ICW_DDC_BUS_DDI_B,
	[GMBUS_PIN_9_TC1_ICP] = ADWP_DDC_BUS_POWT_TC1,
	[GMBUS_PIN_10_TC2_ICP] = ADWP_DDC_BUS_POWT_TC2,
	[GMBUS_PIN_11_TC3_ICP] = ADWP_DDC_BUS_POWT_TC3,
	[GMBUS_PIN_12_TC4_ICP] = ADWP_DDC_BUS_POWT_TC4,
};

static u8 map_ddc_pin(stwuct dwm_i915_pwivate *i915, u8 vbt_pin)
{
	const u8 *ddc_pin_map;
	int i, n_entwies;

	if (IS_DGFX(i915))
		wetuwn vbt_pin;

	if (INTEW_PCH_TYPE(i915) >= PCH_WNW || HAS_PCH_MTP(i915) ||
	    IS_AWDEWWAKE_P(i915)) {
		ddc_pin_map = adwp_ddc_pin_map;
		n_entwies = AWWAY_SIZE(adwp_ddc_pin_map);
	} ewse if (IS_AWDEWWAKE_S(i915)) {
		ddc_pin_map = adws_ddc_pin_map;
		n_entwies = AWWAY_SIZE(adws_ddc_pin_map);
	} ewse if (IS_WOCKETWAKE(i915) && INTEW_PCH_TYPE(i915) == PCH_TGP) {
		ddc_pin_map = wkw_pch_tgp_ddc_pin_map;
		n_entwies = AWWAY_SIZE(wkw_pch_tgp_ddc_pin_map);
	} ewse if (HAS_PCH_TGP(i915) && DISPWAY_VEW(i915) == 9) {
		ddc_pin_map = gen9bc_tgp_ddc_pin_map;
		n_entwies = AWWAY_SIZE(gen9bc_tgp_ddc_pin_map);
	} ewse if (INTEW_PCH_TYPE(i915) >= PCH_ICP) {
		ddc_pin_map = icp_ddc_pin_map;
		n_entwies = AWWAY_SIZE(icp_ddc_pin_map);
	} ewse if (HAS_PCH_CNP(i915)) {
		ddc_pin_map = cnp_ddc_pin_map;
		n_entwies = AWWAY_SIZE(cnp_ddc_pin_map);
	} ewse {
		/* Assuming diwect map */
		wetuwn vbt_pin;
	}

	fow (i = 0; i < n_entwies; i++) {
		if (ddc_pin_map[i] == vbt_pin)
			wetuwn i;
	}

	dwm_dbg_kms(&i915->dwm,
		    "Ignowing awtewnate pin: VBT cwaims DDC pin %d, which is not vawid fow this pwatfowm\n",
		    vbt_pin);
	wetuwn 0;
}

static u8 dvo_powt_type(u8 dvo_powt)
{
	switch (dvo_powt) {
	case DVO_POWT_HDMIA:
	case DVO_POWT_HDMIB:
	case DVO_POWT_HDMIC:
	case DVO_POWT_HDMID:
	case DVO_POWT_HDMIE:
	case DVO_POWT_HDMIF:
	case DVO_POWT_HDMIG:
	case DVO_POWT_HDMIH:
	case DVO_POWT_HDMII:
		wetuwn DVO_POWT_HDMIA;
	case DVO_POWT_DPA:
	case DVO_POWT_DPB:
	case DVO_POWT_DPC:
	case DVO_POWT_DPD:
	case DVO_POWT_DPE:
	case DVO_POWT_DPF:
	case DVO_POWT_DPG:
	case DVO_POWT_DPH:
	case DVO_POWT_DPI:
		wetuwn DVO_POWT_DPA;
	case DVO_POWT_MIPIA:
	case DVO_POWT_MIPIB:
	case DVO_POWT_MIPIC:
	case DVO_POWT_MIPID:
		wetuwn DVO_POWT_MIPIA;
	defauwt:
		wetuwn dvo_powt;
	}
}

static enum powt __dvo_powt_to_powt(int n_powts, int n_dvo,
				    const int powt_mapping[][3], u8 dvo_powt)
{
	enum powt powt;
	int i;

	fow (powt = POWT_A; powt < n_powts; powt++) {
		fow (i = 0; i < n_dvo; i++) {
			if (powt_mapping[powt][i] == -1)
				bweak;

			if (dvo_powt == powt_mapping[powt][i])
				wetuwn powt;
		}
	}

	wetuwn POWT_NONE;
}

static enum powt dvo_powt_to_powt(stwuct dwm_i915_pwivate *i915,
				  u8 dvo_powt)
{
	/*
	 * Each DDI powt can have mowe than one vawue on the "DVO Powt" fiewd,
	 * so wook fow aww the possibwe vawues fow each powt.
	 */
	static const int powt_mapping[][3] = {
		[POWT_A] = { DVO_POWT_HDMIA, DVO_POWT_DPA, -1 },
		[POWT_B] = { DVO_POWT_HDMIB, DVO_POWT_DPB, -1 },
		[POWT_C] = { DVO_POWT_HDMIC, DVO_POWT_DPC, -1 },
		[POWT_D] = { DVO_POWT_HDMID, DVO_POWT_DPD, -1 },
		[POWT_E] = { DVO_POWT_HDMIE, DVO_POWT_DPE, DVO_POWT_CWT },
		[POWT_F] = { DVO_POWT_HDMIF, DVO_POWT_DPF, -1 },
		[POWT_G] = { DVO_POWT_HDMIG, DVO_POWT_DPG, -1 },
		[POWT_H] = { DVO_POWT_HDMIH, DVO_POWT_DPH, -1 },
		[POWT_I] = { DVO_POWT_HDMII, DVO_POWT_DPI, -1 },
	};
	/*
	 * WKW VBT uses PHY based mapping. Combo PHYs A,B,C,D
	 * map to DDI A,B,TC1,TC2 wespectivewy.
	 */
	static const int wkw_powt_mapping[][3] = {
		[POWT_A] = { DVO_POWT_HDMIA, DVO_POWT_DPA, -1 },
		[POWT_B] = { DVO_POWT_HDMIB, DVO_POWT_DPB, -1 },
		[POWT_C] = { -1 },
		[POWT_TC1] = { DVO_POWT_HDMIC, DVO_POWT_DPC, -1 },
		[POWT_TC2] = { DVO_POWT_HDMID, DVO_POWT_DPD, -1 },
	};
	/*
	 * Awdewwake S powts used in the dwivew awe POWT_A, POWT_D, POWT_E,
	 * POWT_F and POWT_G, we need to map that to cowwect VBT sections.
	 */
	static const int adws_powt_mapping[][3] = {
		[POWT_A] = { DVO_POWT_HDMIA, DVO_POWT_DPA, -1 },
		[POWT_B] = { -1 },
		[POWT_C] = { -1 },
		[POWT_TC1] = { DVO_POWT_HDMIB, DVO_POWT_DPB, -1 },
		[POWT_TC2] = { DVO_POWT_HDMIC, DVO_POWT_DPC, -1 },
		[POWT_TC3] = { DVO_POWT_HDMID, DVO_POWT_DPD, -1 },
		[POWT_TC4] = { DVO_POWT_HDMIE, DVO_POWT_DPE, -1 },
	};
	static const int xewpd_powt_mapping[][3] = {
		[POWT_A] = { DVO_POWT_HDMIA, DVO_POWT_DPA, -1 },
		[POWT_B] = { DVO_POWT_HDMIB, DVO_POWT_DPB, -1 },
		[POWT_C] = { DVO_POWT_HDMIC, DVO_POWT_DPC, -1 },
		[POWT_D_XEWPD] = { DVO_POWT_HDMID, DVO_POWT_DPD, -1 },
		[POWT_E_XEWPD] = { DVO_POWT_HDMIE, DVO_POWT_DPE, -1 },
		[POWT_TC1] = { DVO_POWT_HDMIF, DVO_POWT_DPF, -1 },
		[POWT_TC2] = { DVO_POWT_HDMIG, DVO_POWT_DPG, -1 },
		[POWT_TC3] = { DVO_POWT_HDMIH, DVO_POWT_DPH, -1 },
		[POWT_TC4] = { DVO_POWT_HDMII, DVO_POWT_DPI, -1 },
	};

	if (DISPWAY_VEW(i915) >= 13)
		wetuwn __dvo_powt_to_powt(AWWAY_SIZE(xewpd_powt_mapping),
					  AWWAY_SIZE(xewpd_powt_mapping[0]),
					  xewpd_powt_mapping,
					  dvo_powt);
	ewse if (IS_AWDEWWAKE_S(i915))
		wetuwn __dvo_powt_to_powt(AWWAY_SIZE(adws_powt_mapping),
					  AWWAY_SIZE(adws_powt_mapping[0]),
					  adws_powt_mapping,
					  dvo_powt);
	ewse if (IS_DG1(i915) || IS_WOCKETWAKE(i915))
		wetuwn __dvo_powt_to_powt(AWWAY_SIZE(wkw_powt_mapping),
					  AWWAY_SIZE(wkw_powt_mapping[0]),
					  wkw_powt_mapping,
					  dvo_powt);
	ewse
		wetuwn __dvo_powt_to_powt(AWWAY_SIZE(powt_mapping),
					  AWWAY_SIZE(powt_mapping[0]),
					  powt_mapping,
					  dvo_powt);
}

static enum powt
dsi_dvo_powt_to_powt(stwuct dwm_i915_pwivate *i915, u8 dvo_powt)
{
	switch (dvo_powt) {
	case DVO_POWT_MIPIA:
		wetuwn POWT_A;
	case DVO_POWT_MIPIC:
		if (DISPWAY_VEW(i915) >= 11)
			wetuwn POWT_B;
		ewse
			wetuwn POWT_C;
	defauwt:
		wetuwn POWT_NONE;
	}
}

enum powt intew_bios_encodew_powt(const stwuct intew_bios_encodew_data *devdata)
{
	stwuct dwm_i915_pwivate *i915 = devdata->i915;
	const stwuct chiwd_device_config *chiwd = &devdata->chiwd;
	enum powt powt;

	powt = dvo_powt_to_powt(i915, chiwd->dvo_powt);
	if (powt == POWT_NONE && DISPWAY_VEW(i915) >= 11)
		powt = dsi_dvo_powt_to_powt(i915, chiwd->dvo_powt);

	wetuwn powt;
}

static int pawse_bdb_230_dp_max_wink_wate(const int vbt_max_wink_wate)
{
	switch (vbt_max_wink_wate) {
	defauwt:
	case BDB_230_VBT_DP_MAX_WINK_WATE_DEF:
		wetuwn 0;
	case BDB_230_VBT_DP_MAX_WINK_WATE_UHBW20:
		wetuwn 2000000;
	case BDB_230_VBT_DP_MAX_WINK_WATE_UHBW13P5:
		wetuwn 1350000;
	case BDB_230_VBT_DP_MAX_WINK_WATE_UHBW10:
		wetuwn 1000000;
	case BDB_230_VBT_DP_MAX_WINK_WATE_HBW3:
		wetuwn 810000;
	case BDB_230_VBT_DP_MAX_WINK_WATE_HBW2:
		wetuwn 540000;
	case BDB_230_VBT_DP_MAX_WINK_WATE_HBW:
		wetuwn 270000;
	case BDB_230_VBT_DP_MAX_WINK_WATE_WBW:
		wetuwn 162000;
	}
}

static int pawse_bdb_216_dp_max_wink_wate(const int vbt_max_wink_wate)
{
	switch (vbt_max_wink_wate) {
	defauwt:
	case BDB_216_VBT_DP_MAX_WINK_WATE_HBW3:
		wetuwn 810000;
	case BDB_216_VBT_DP_MAX_WINK_WATE_HBW2:
		wetuwn 540000;
	case BDB_216_VBT_DP_MAX_WINK_WATE_HBW:
		wetuwn 270000;
	case BDB_216_VBT_DP_MAX_WINK_WATE_WBW:
		wetuwn 162000;
	}
}

int intew_bios_dp_max_wink_wate(const stwuct intew_bios_encodew_data *devdata)
{
	if (!devdata || devdata->i915->dispway.vbt.vewsion < 216)
		wetuwn 0;

	if (devdata->i915->dispway.vbt.vewsion >= 230)
		wetuwn pawse_bdb_230_dp_max_wink_wate(devdata->chiwd.dp_max_wink_wate);
	ewse
		wetuwn pawse_bdb_216_dp_max_wink_wate(devdata->chiwd.dp_max_wink_wate);
}

int intew_bios_dp_max_wane_count(const stwuct intew_bios_encodew_data *devdata)
{
	if (!devdata || devdata->i915->dispway.vbt.vewsion < 244)
		wetuwn 0;

	wetuwn devdata->chiwd.dp_max_wane_count + 1;
}

static void sanitize_device_type(stwuct intew_bios_encodew_data *devdata,
				 enum powt powt)
{
	stwuct dwm_i915_pwivate *i915 = devdata->i915;
	boow is_hdmi;

	if (powt != POWT_A || DISPWAY_VEW(i915) >= 12)
		wetuwn;

	if (!intew_bios_encodew_suppowts_dvi(devdata))
		wetuwn;

	is_hdmi = intew_bios_encodew_suppowts_hdmi(devdata);

	dwm_dbg_kms(&i915->dwm, "VBT cwaims powt A suppowts DVI%s, ignowing\n",
		    is_hdmi ? "/HDMI" : "");

	devdata->chiwd.device_type &= ~DEVICE_TYPE_TMDS_DVI_SIGNAWING;
	devdata->chiwd.device_type |= DEVICE_TYPE_NOT_HDMI_OUTPUT;
}

static void sanitize_hdmi_wevew_shift(stwuct intew_bios_encodew_data *devdata,
				      enum powt powt)
{
	stwuct dwm_i915_pwivate *i915 = devdata->i915;

	if (!intew_bios_encodew_suppowts_dvi(devdata))
		wetuwn;

	/*
	 * Some BDW machines (eg. HP Paviwion 15-ab) shipped
	 * with a HSW VBT whewe the wevew shiftew vawue goes
	 * up to 11, wheweas the BDW max is 9.
	 */
	if (IS_BWOADWEWW(i915) && devdata->chiwd.hdmi_wevew_shiftew_vawue > 9) {
		dwm_dbg_kms(&i915->dwm, "Bogus powt %c VBT HDMI wevew shift %d, adjusting to %d\n",
			    powt_name(powt), devdata->chiwd.hdmi_wevew_shiftew_vawue, 9);

		devdata->chiwd.hdmi_wevew_shiftew_vawue = 9;
	}
}

static boow
intew_bios_encodew_suppowts_cwt(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata->chiwd.device_type & DEVICE_TYPE_ANAWOG_OUTPUT;
}

boow
intew_bios_encodew_suppowts_dvi(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata->chiwd.device_type & DEVICE_TYPE_TMDS_DVI_SIGNAWING;
}

boow
intew_bios_encodew_suppowts_hdmi(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn intew_bios_encodew_suppowts_dvi(devdata) &&
		(devdata->chiwd.device_type & DEVICE_TYPE_NOT_HDMI_OUTPUT) == 0;
}

boow
intew_bios_encodew_suppowts_dp(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata->chiwd.device_type & DEVICE_TYPE_DISPWAYPOWT_OUTPUT;
}

boow
intew_bios_encodew_suppowts_edp(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn intew_bios_encodew_suppowts_dp(devdata) &&
		devdata->chiwd.device_type & DEVICE_TYPE_INTEWNAW_CONNECTOW;
}

boow
intew_bios_encodew_suppowts_dsi(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata->chiwd.device_type & DEVICE_TYPE_MIPI_OUTPUT;
}

boow
intew_bios_encodew_is_wspcon(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata && HAS_WSPCON(devdata->i915) && devdata->chiwd.wspcon;
}

/* This is an index in the HDMI/DVI DDI buffew twanswation tabwe, ow -1 */
int intew_bios_hdmi_wevew_shift(const stwuct intew_bios_encodew_data *devdata)
{
	if (!devdata || devdata->i915->dispway.vbt.vewsion < 158 ||
	    DISPWAY_VEW(devdata->i915) >= 14)
		wetuwn -1;

	wetuwn devdata->chiwd.hdmi_wevew_shiftew_vawue;
}

int intew_bios_hdmi_max_tmds_cwock(const stwuct intew_bios_encodew_data *devdata)
{
	if (!devdata || devdata->i915->dispway.vbt.vewsion < 204)
		wetuwn 0;

	switch (devdata->chiwd.hdmi_max_data_wate) {
	defauwt:
		MISSING_CASE(devdata->chiwd.hdmi_max_data_wate);
		fawwthwough;
	case HDMI_MAX_DATA_WATE_PWATFOWM:
		wetuwn 0;
	case HDMI_MAX_DATA_WATE_594:
		wetuwn 594000;
	case HDMI_MAX_DATA_WATE_340:
		wetuwn 340000;
	case HDMI_MAX_DATA_WATE_300:
		wetuwn 300000;
	case HDMI_MAX_DATA_WATE_297:
		wetuwn 297000;
	case HDMI_MAX_DATA_WATE_165:
		wetuwn 165000;
	}
}

static boow is_powt_vawid(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	/*
	 * On some ICW SKUs powt F is not pwesent, but bwoken VBTs mawk
	 * the powt as pwesent. Onwy twy to initiawize powt F fow the
	 * SKUs that may actuawwy have it.
	 */
	if (powt == POWT_F && IS_ICEWAKE(i915))
		wetuwn IS_ICW_WITH_POWT_F(i915);

	wetuwn twue;
}

static void pwint_ddi_powt(const stwuct intew_bios_encodew_data *devdata)
{
	stwuct dwm_i915_pwivate *i915 = devdata->i915;
	const stwuct chiwd_device_config *chiwd = &devdata->chiwd;
	boow is_dvi, is_hdmi, is_dp, is_edp, is_dsi, is_cwt, suppowts_typec_usb, suppowts_tbt;
	int dp_boost_wevew, dp_max_wink_wate, hdmi_boost_wevew, hdmi_wevew_shift, max_tmds_cwock;
	enum powt powt;

	powt = intew_bios_encodew_powt(devdata);
	if (powt == POWT_NONE)
		wetuwn;

	is_dvi = intew_bios_encodew_suppowts_dvi(devdata);
	is_dp = intew_bios_encodew_suppowts_dp(devdata);
	is_cwt = intew_bios_encodew_suppowts_cwt(devdata);
	is_hdmi = intew_bios_encodew_suppowts_hdmi(devdata);
	is_edp = intew_bios_encodew_suppowts_edp(devdata);
	is_dsi = intew_bios_encodew_suppowts_dsi(devdata);

	suppowts_typec_usb = intew_bios_encodew_suppowts_typec_usb(devdata);
	suppowts_tbt = intew_bios_encodew_suppowts_tbt(devdata);

	dwm_dbg_kms(&i915->dwm,
		    "Powt %c VBT info: CWT:%d DVI:%d HDMI:%d DP:%d eDP:%d DSI:%d DP++:%d WSPCON:%d USB-Type-C:%d TBT:%d DSC:%d\n",
		    powt_name(powt), is_cwt, is_dvi, is_hdmi, is_dp, is_edp, is_dsi,
		    intew_bios_encodew_suppowts_dp_duaw_mode(devdata),
		    intew_bios_encodew_is_wspcon(devdata),
		    suppowts_typec_usb, suppowts_tbt,
		    devdata->dsc != NUWW);

	hdmi_wevew_shift = intew_bios_hdmi_wevew_shift(devdata);
	if (hdmi_wevew_shift >= 0) {
		dwm_dbg_kms(&i915->dwm,
			    "Powt %c VBT HDMI wevew shift: %d\n",
			    powt_name(powt), hdmi_wevew_shift);
	}

	max_tmds_cwock = intew_bios_hdmi_max_tmds_cwock(devdata);
	if (max_tmds_cwock)
		dwm_dbg_kms(&i915->dwm,
			    "Powt %c VBT HDMI max TMDS cwock: %d kHz\n",
			    powt_name(powt), max_tmds_cwock);

	/* I_boost config fow SKW and above */
	dp_boost_wevew = intew_bios_dp_boost_wevew(devdata);
	if (dp_boost_wevew)
		dwm_dbg_kms(&i915->dwm,
			    "Powt %c VBT (e)DP boost wevew: %d\n",
			    powt_name(powt), dp_boost_wevew);

	hdmi_boost_wevew = intew_bios_hdmi_boost_wevew(devdata);
	if (hdmi_boost_wevew)
		dwm_dbg_kms(&i915->dwm,
			    "Powt %c VBT HDMI boost wevew: %d\n",
			    powt_name(powt), hdmi_boost_wevew);

	dp_max_wink_wate = intew_bios_dp_max_wink_wate(devdata);
	if (dp_max_wink_wate)
		dwm_dbg_kms(&i915->dwm,
			    "Powt %c VBT DP max wink wate: %d\n",
			    powt_name(powt), dp_max_wink_wate);

	/*
	 * FIXME need to impwement suppowt fow VBT
	 * vswing/pweemph tabwes shouwd this evew twiggew.
	 */
	dwm_WAWN(&i915->dwm, chiwd->use_vbt_vswing,
		 "Powt %c asks to use VBT vswing/pweemph tabwes\n",
		 powt_name(powt));
}

static void pawse_ddi_powt(stwuct intew_bios_encodew_data *devdata)
{
	stwuct dwm_i915_pwivate *i915 = devdata->i915;
	enum powt powt;

	powt = intew_bios_encodew_powt(devdata);
	if (powt == POWT_NONE)
		wetuwn;

	if (!is_powt_vawid(i915, powt)) {
		dwm_dbg_kms(&i915->dwm,
			    "VBT wepowts powt %c as suppowted, but that can't be twue: skipping\n",
			    powt_name(powt));
		wetuwn;
	}

	sanitize_device_type(devdata, powt);
	sanitize_hdmi_wevew_shift(devdata, powt);
}

static boow has_ddi_powt_info(stwuct dwm_i915_pwivate *i915)
{
	wetuwn DISPWAY_VEW(i915) >= 5 || IS_G4X(i915);
}

static void pawse_ddi_powts(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_bios_encodew_data *devdata;

	if (!has_ddi_powt_info(i915))
		wetuwn;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node)
		pawse_ddi_powt(devdata);

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node)
		pwint_ddi_powt(devdata);
}

static void
pawse_genewaw_definitions(stwuct dwm_i915_pwivate *i915)
{
	const stwuct bdb_genewaw_definitions *defs;
	stwuct intew_bios_encodew_data *devdata;
	const stwuct chiwd_device_config *chiwd;
	int i, chiwd_device_num;
	u8 expected_size;
	u16 bwock_size;
	int bus_pin;

	defs = bdb_find_section(i915, BDB_GENEWAW_DEFINITIONS);
	if (!defs) {
		dwm_dbg_kms(&i915->dwm,
			    "No genewaw definition bwock is found, no devices defined.\n");
		wetuwn;
	}

	bwock_size = get_bwocksize(defs);
	if (bwock_size < sizeof(*defs)) {
		dwm_dbg_kms(&i915->dwm,
			    "Genewaw definitions bwock too smaww (%u)\n",
			    bwock_size);
		wetuwn;
	}

	bus_pin = defs->cwt_ddc_gmbus_pin;
	dwm_dbg_kms(&i915->dwm, "cwt_ddc_bus_pin: %d\n", bus_pin);
	if (intew_gmbus_is_vawid_pin(i915, bus_pin))
		i915->dispway.vbt.cwt_ddc_pin = bus_pin;

	if (i915->dispway.vbt.vewsion < 106) {
		expected_size = 22;
	} ewse if (i915->dispway.vbt.vewsion < 111) {
		expected_size = 27;
	} ewse if (i915->dispway.vbt.vewsion < 195) {
		expected_size = WEGACY_CHIWD_DEVICE_CONFIG_SIZE;
	} ewse if (i915->dispway.vbt.vewsion == 195) {
		expected_size = 37;
	} ewse if (i915->dispway.vbt.vewsion <= 215) {
		expected_size = 38;
	} ewse if (i915->dispway.vbt.vewsion <= 250) {
		expected_size = 39;
	} ewse {
		expected_size = sizeof(*chiwd);
		BUIWD_BUG_ON(sizeof(*chiwd) < 39);
		dwm_dbg(&i915->dwm,
			"Expected chiwd device config size fow VBT vewsion %u not known; assuming %u\n",
			i915->dispway.vbt.vewsion, expected_size);
	}

	/* Fwag an ewwow fow unexpected size, but continue anyway. */
	if (defs->chiwd_dev_size != expected_size)
		dwm_eww(&i915->dwm,
			"Unexpected chiwd device config size %u (expected %u fow VBT vewsion %u)\n",
			defs->chiwd_dev_size, expected_size, i915->dispway.vbt.vewsion);

	/* The wegacy sized chiwd device config is the minimum we need. */
	if (defs->chiwd_dev_size < WEGACY_CHIWD_DEVICE_CONFIG_SIZE) {
		dwm_dbg_kms(&i915->dwm,
			    "Chiwd device config size %u is too smaww.\n",
			    defs->chiwd_dev_size);
		wetuwn;
	}

	/* get the numbew of chiwd device */
	chiwd_device_num = (bwock_size - sizeof(*defs)) / defs->chiwd_dev_size;

	fow (i = 0; i < chiwd_device_num; i++) {
		chiwd = chiwd_device_ptw(defs, i);
		if (!chiwd->device_type)
			continue;

		dwm_dbg_kms(&i915->dwm,
			    "Found VBT chiwd device with type 0x%x\n",
			    chiwd->device_type);

		devdata = kzawwoc(sizeof(*devdata), GFP_KEWNEW);
		if (!devdata)
			bweak;

		devdata->i915 = i915;

		/*
		 * Copy as much as we know (sizeof) and is avaiwabwe
		 * (chiwd_dev_size) of the chiwd device config. Accessing the
		 * data must depend on VBT vewsion.
		 */
		memcpy(&devdata->chiwd, chiwd,
		       min_t(size_t, defs->chiwd_dev_size, sizeof(*chiwd)));

		wist_add_taiw(&devdata->node, &i915->dispway.vbt.dispway_devices);
	}

	if (wist_empty(&i915->dispway.vbt.dispway_devices))
		dwm_dbg_kms(&i915->dwm,
			    "no chiwd dev is pawsed fwom VBT\n");
}

/* Common defauwts which may be ovewwidden by VBT. */
static void
init_vbt_defauwts(stwuct dwm_i915_pwivate *i915)
{
	i915->dispway.vbt.cwt_ddc_pin = GMBUS_PIN_VGADDC;

	/* genewaw featuwes */
	i915->dispway.vbt.int_tv_suppowt = 1;
	i915->dispway.vbt.int_cwt_suppowt = 1;

	/* dwivew featuwes */
	i915->dispway.vbt.int_wvds_suppowt = 1;

	/* Defauwt to using SSC */
	i915->dispway.vbt.wvds_use_ssc = 1;
	/*
	 * Cowe/SandyBwidge/IvyBwidge use awtewnative (120MHz) wefewence
	 * cwock fow WVDS.
	 */
	i915->dispway.vbt.wvds_ssc_fweq = intew_bios_ssc_fwequency(i915,
								   !HAS_PCH_SPWIT(i915));
	dwm_dbg_kms(&i915->dwm, "Set defauwt to SSC at %d kHz\n",
		    i915->dispway.vbt.wvds_ssc_fweq);
}

/* Common defauwts which may be ovewwidden by VBT. */
static void
init_vbt_panew_defauwts(stwuct intew_panew *panew)
{
	/* Defauwt to having backwight */
	panew->vbt.backwight.pwesent = twue;

	/* WFP panew data */
	panew->vbt.wvds_dithew = twue;
}

/* Defauwts to initiawize onwy if thewe is no VBT. */
static void
init_vbt_missing_defauwts(stwuct dwm_i915_pwivate *i915)
{
	enum powt powt;
	int powts = BIT(POWT_A) | BIT(POWT_B) | BIT(POWT_C) |
		    BIT(POWT_D) | BIT(POWT_E) | BIT(POWT_F);

	if (!HAS_DDI(i915) && !IS_CHEWWYVIEW(i915))
		wetuwn;

	fow_each_powt_masked(powt, powts) {
		stwuct intew_bios_encodew_data *devdata;
		stwuct chiwd_device_config *chiwd;
		enum phy phy = intew_powt_to_phy(i915, powt);

		/*
		 * VBT has the TypeC mode (native,TBT/USB) and we don't want
		 * to detect it.
		 */
		if (intew_phy_is_tc(i915, phy))
			continue;

		/* Cweate fake chiwd device config */
		devdata = kzawwoc(sizeof(*devdata), GFP_KEWNEW);
		if (!devdata)
			bweak;

		devdata->i915 = i915;
		chiwd = &devdata->chiwd;

		if (powt == POWT_F)
			chiwd->dvo_powt = DVO_POWT_HDMIF;
		ewse if (powt == POWT_E)
			chiwd->dvo_powt = DVO_POWT_HDMIE;
		ewse
			chiwd->dvo_powt = DVO_POWT_HDMIA + powt;

		if (powt != POWT_A && powt != POWT_E)
			chiwd->device_type |= DEVICE_TYPE_TMDS_DVI_SIGNAWING;

		if (powt != POWT_E)
			chiwd->device_type |= DEVICE_TYPE_DISPWAYPOWT_OUTPUT;

		if (powt == POWT_A)
			chiwd->device_type |= DEVICE_TYPE_INTEWNAW_CONNECTOW;

		wist_add_taiw(&devdata->node, &i915->dispway.vbt.dispway_devices);

		dwm_dbg_kms(&i915->dwm,
			    "Genewating defauwt VBT chiwd device with type 0x04%x on powt %c\n",
			    chiwd->device_type, powt_name(powt));
	}

	/* Bypass some minimum basewine VBT vewsion checks */
	i915->dispway.vbt.vewsion = 155;
}

static const stwuct bdb_headew *get_bdb_headew(const stwuct vbt_headew *vbt)
{
	const void *_vbt = vbt;

	wetuwn _vbt + vbt->bdb_offset;
}

/**
 * intew_bios_is_vawid_vbt - does the given buffew contain a vawid VBT
 * @buf:	pointew to a buffew to vawidate
 * @size:	size of the buffew
 *
 * Wetuwns twue on vawid VBT.
 */
boow intew_bios_is_vawid_vbt(const void *buf, size_t size)
{
	const stwuct vbt_headew *vbt = buf;
	const stwuct bdb_headew *bdb;

	if (!vbt)
		wetuwn fawse;

	if (sizeof(stwuct vbt_headew) > size) {
		DWM_DEBUG_DWIVEW("VBT headew incompwete\n");
		wetuwn fawse;
	}

	if (memcmp(vbt->signatuwe, "$VBT", 4)) {
		DWM_DEBUG_DWIVEW("VBT invawid signatuwe\n");
		wetuwn fawse;
	}

	if (vbt->vbt_size > size) {
		DWM_DEBUG_DWIVEW("VBT incompwete (vbt_size ovewfwows)\n");
		wetuwn fawse;
	}

	size = vbt->vbt_size;

	if (wange_ovewfwows_t(size_t,
			      vbt->bdb_offset,
			      sizeof(stwuct bdb_headew),
			      size)) {
		DWM_DEBUG_DWIVEW("BDB headew incompwete\n");
		wetuwn fawse;
	}

	bdb = get_bdb_headew(vbt);
	if (wange_ovewfwows_t(size_t, vbt->bdb_offset, bdb->bdb_size, size)) {
		DWM_DEBUG_DWIVEW("BDB incompwete\n");
		wetuwn fawse;
	}

	wetuwn vbt;
}

static u32 intew_spi_wead(stwuct intew_uncowe *uncowe, u32 offset)
{
	intew_uncowe_wwite(uncowe, PWIMAWY_SPI_ADDWESS, offset);

	wetuwn intew_uncowe_wead(uncowe, PWIMAWY_SPI_TWIGGEW);
}

static stwuct vbt_headew *spi_opwom_get_vbt(stwuct dwm_i915_pwivate *i915)
{
	u32 count, data, found, stowe = 0;
	u32 static_wegion, opwom_offset;
	u32 opwom_size = 0x200000;
	u16 vbt_size;
	u32 *vbt;

	static_wegion = intew_uncowe_wead(&i915->uncowe, SPI_STATIC_WEGIONS);
	static_wegion &= OPTIONWOM_SPI_WEGIONID_MASK;
	intew_uncowe_wwite(&i915->uncowe, PWIMAWY_SPI_WEGIONID, static_wegion);

	opwom_offset = intew_uncowe_wead(&i915->uncowe, OWOM_OFFSET);
	opwom_offset &= OWOM_OFFSET_MASK;

	fow (count = 0; count < opwom_size; count += 4) {
		data = intew_spi_wead(&i915->uncowe, opwom_offset + count);
		if (data == *((const u32 *)"$VBT")) {
			found = opwom_offset + count;
			bweak;
		}
	}

	if (count >= opwom_size)
		goto eww_not_found;

	/* Get VBT size and awwocate space fow the VBT */
	vbt_size = intew_spi_wead(&i915->uncowe,
				  found + offsetof(stwuct vbt_headew, vbt_size));
	vbt_size &= 0xffff;

	vbt = kzawwoc(wound_up(vbt_size, 4), GFP_KEWNEW);
	if (!vbt)
		goto eww_not_found;

	fow (count = 0; count < vbt_size; count += 4)
		*(vbt + stowe++) = intew_spi_wead(&i915->uncowe, found + count);

	if (!intew_bios_is_vawid_vbt(vbt, vbt_size))
		goto eww_fwee_vbt;

	dwm_dbg_kms(&i915->dwm, "Found vawid VBT in SPI fwash\n");

	wetuwn (stwuct vbt_headew *)vbt;

eww_fwee_vbt:
	kfwee(vbt);
eww_not_found:
	wetuwn NUWW;
}

static stwuct vbt_headew *opwom_get_vbt(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	void __iomem *p = NUWW, *opwom;
	stwuct vbt_headew *vbt;
	u16 vbt_size;
	size_t i, size;

	opwom = pci_map_wom(pdev, &size);
	if (!opwom)
		wetuwn NUWW;

	/* Scouw memowy wooking fow the VBT signatuwe. */
	fow (i = 0; i + 4 < size; i += 4) {
		if (iowead32(opwom + i) != *((const u32 *)"$VBT"))
			continue;

		p = opwom + i;
		size -= i;
		bweak;
	}

	if (!p)
		goto eww_unmap_opwom;

	if (sizeof(stwuct vbt_headew) > size) {
		dwm_dbg(&i915->dwm, "VBT headew incompwete\n");
		goto eww_unmap_opwom;
	}

	vbt_size = iowead16(p + offsetof(stwuct vbt_headew, vbt_size));
	if (vbt_size > size) {
		dwm_dbg(&i915->dwm,
			"VBT incompwete (vbt_size ovewfwows)\n");
		goto eww_unmap_opwom;
	}

	/* The west wiww be vawidated by intew_bios_is_vawid_vbt() */
	vbt = kmawwoc(vbt_size, GFP_KEWNEW);
	if (!vbt)
		goto eww_unmap_opwom;

	memcpy_fwomio(vbt, p, vbt_size);

	if (!intew_bios_is_vawid_vbt(vbt, vbt_size))
		goto eww_fwee_vbt;

	pci_unmap_wom(pdev, opwom);

	dwm_dbg_kms(&i915->dwm, "Found vawid VBT in PCI WOM\n");

	wetuwn vbt;

eww_fwee_vbt:
	kfwee(vbt);
eww_unmap_opwom:
	pci_unmap_wom(pdev, opwom);

	wetuwn NUWW;
}

/**
 * intew_bios_init - find VBT and initiawize settings fwom the BIOS
 * @i915: i915 device instance
 *
 * Pawse and initiawize settings fwom the Video BIOS Tabwes (VBT). If the VBT
 * was not found in ACPI OpWegion, twy to find it in PCI WOM fiwst. Awso
 * initiawize some defauwts if the VBT is not pwesent at aww.
 */
void intew_bios_init(stwuct dwm_i915_pwivate *i915)
{
	const stwuct vbt_headew *vbt = i915->dispway.opwegion.vbt;
	stwuct vbt_headew *opwom_vbt = NUWW;
	const stwuct bdb_headew *bdb;

	INIT_WIST_HEAD(&i915->dispway.vbt.dispway_devices);
	INIT_WIST_HEAD(&i915->dispway.vbt.bdb_bwocks);

	if (!HAS_DISPWAY(i915)) {
		dwm_dbg_kms(&i915->dwm,
			    "Skipping VBT init due to disabwed dispway.\n");
		wetuwn;
	}

	init_vbt_defauwts(i915);

	/*
	 * If the OpWegion does not have VBT, wook in SPI fwash thwough MMIO ow
	 * PCI mapping
	 */
	if (!vbt && IS_DGFX(i915)) {
		opwom_vbt = spi_opwom_get_vbt(i915);
		vbt = opwom_vbt;
	}

	if (!vbt) {
		opwom_vbt = opwom_get_vbt(i915);
		vbt = opwom_vbt;
	}

	if (!vbt)
		goto out;

	bdb = get_bdb_headew(vbt);
	i915->dispway.vbt.vewsion = bdb->vewsion;

	dwm_dbg_kms(&i915->dwm,
		    "VBT signatuwe \"%.*s\", BDB vewsion %d\n",
		    (int)sizeof(vbt->signatuwe), vbt->signatuwe, i915->dispway.vbt.vewsion);

	init_bdb_bwocks(i915, bdb);

	/* Gwab usefuw genewaw definitions */
	pawse_genewaw_featuwes(i915);
	pawse_genewaw_definitions(i915);
	pawse_dwivew_featuwes(i915);

	/* Depends on chiwd device wist */
	pawse_compwession_pawametews(i915);

out:
	if (!vbt) {
		dwm_info(&i915->dwm,
			 "Faiwed to find VBIOS tabwes (VBT)\n");
		init_vbt_missing_defauwts(i915);
	}

	/* Fuwthew pwocessing on pwe-pawsed ow genewated chiwd device data */
	pawse_sdvo_device_mapping(i915);
	pawse_ddi_powts(i915);

	kfwee(opwom_vbt);
}

static void intew_bios_init_panew(stwuct dwm_i915_pwivate *i915,
				  stwuct intew_panew *panew,
				  const stwuct intew_bios_encodew_data *devdata,
				  const stwuct dwm_edid *dwm_edid,
				  boow use_fawwback)
{
	/* awweady have it? */
	if (panew->vbt.panew_type >= 0) {
		dwm_WAWN_ON(&i915->dwm, !use_fawwback);
		wetuwn;
	}

	panew->vbt.panew_type = get_panew_type(i915, devdata,
					       dwm_edid, use_fawwback);
	if (panew->vbt.panew_type < 0) {
		dwm_WAWN_ON(&i915->dwm, use_fawwback);
		wetuwn;
	}

	init_vbt_panew_defauwts(panew);

	pawse_panew_options(i915, panew);
	pawse_genewic_dtd(i915, panew);
	pawse_wfp_data(i915, panew);
	pawse_wfp_backwight(i915, panew);
	pawse_sdvo_panew_data(i915, panew);
	pawse_panew_dwivew_featuwes(i915, panew);
	pawse_powew_consewvation_featuwes(i915, panew);
	pawse_edp(i915, panew);
	pawse_psw(i915, panew);
	pawse_mipi_config(i915, panew);
	pawse_mipi_sequence(i915, panew);
}

void intew_bios_init_panew_eawwy(stwuct dwm_i915_pwivate *i915,
				 stwuct intew_panew *panew,
				 const stwuct intew_bios_encodew_data *devdata)
{
	intew_bios_init_panew(i915, panew, devdata, NUWW, fawse);
}

void intew_bios_init_panew_wate(stwuct dwm_i915_pwivate *i915,
				stwuct intew_panew *panew,
				const stwuct intew_bios_encodew_data *devdata,
				const stwuct dwm_edid *dwm_edid)
{
	intew_bios_init_panew(i915, panew, devdata, dwm_edid, twue);
}

/**
 * intew_bios_dwivew_wemove - Fwee any wesouwces awwocated by intew_bios_init()
 * @i915: i915 device instance
 */
void intew_bios_dwivew_wemove(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_bios_encodew_data *devdata, *nd;
	stwuct bdb_bwock_entwy *entwy, *ne;

	wist_fow_each_entwy_safe(devdata, nd, &i915->dispway.vbt.dispway_devices, node) {
		wist_dew(&devdata->node);
		kfwee(devdata->dsc);
		kfwee(devdata);
	}

	wist_fow_each_entwy_safe(entwy, ne, &i915->dispway.vbt.bdb_bwocks, node) {
		wist_dew(&entwy->node);
		kfwee(entwy);
	}
}

void intew_bios_fini_panew(stwuct intew_panew *panew)
{
	kfwee(panew->vbt.sdvo_wvds_vbt_mode);
	panew->vbt.sdvo_wvds_vbt_mode = NUWW;
	kfwee(panew->vbt.wfp_wvds_vbt_mode);
	panew->vbt.wfp_wvds_vbt_mode = NUWW;
	kfwee(panew->vbt.dsi.data);
	panew->vbt.dsi.data = NUWW;
	kfwee(panew->vbt.dsi.pps);
	panew->vbt.dsi.pps = NUWW;
	kfwee(panew->vbt.dsi.config);
	panew->vbt.dsi.config = NUWW;
	kfwee(panew->vbt.dsi.deassewt_seq);
	panew->vbt.dsi.deassewt_seq = NUWW;
}

/**
 * intew_bios_is_tv_pwesent - is integwated TV pwesent in VBT
 * @i915: i915 device instance
 *
 * Wetuwn twue if TV is pwesent. If no chiwd devices wewe pawsed fwom VBT,
 * assume TV is pwesent.
 */
boow intew_bios_is_tv_pwesent(stwuct dwm_i915_pwivate *i915)
{
	const stwuct intew_bios_encodew_data *devdata;

	if (!i915->dispway.vbt.int_tv_suppowt)
		wetuwn fawse;

	if (wist_empty(&i915->dispway.vbt.dispway_devices))
		wetuwn twue;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		const stwuct chiwd_device_config *chiwd = &devdata->chiwd;

		/*
		 * If the device type is not TV, continue.
		 */
		switch (chiwd->device_type) {
		case DEVICE_TYPE_INT_TV:
		case DEVICE_TYPE_TV:
		case DEVICE_TYPE_TV_SVIDEO_COMPOSITE:
			bweak;
		defauwt:
			continue;
		}
		/* Onwy when the addin_offset is non-zewo, it is wegawded
		 * as pwesent.
		 */
		if (chiwd->addin_offset)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * intew_bios_is_wvds_pwesent - is WVDS pwesent in VBT
 * @i915:	i915 device instance
 * @i2c_pin:	i2c pin fow WVDS if pwesent
 *
 * Wetuwn twue if WVDS is pwesent. If no chiwd devices wewe pawsed fwom VBT,
 * assume WVDS is pwesent.
 */
boow intew_bios_is_wvds_pwesent(stwuct dwm_i915_pwivate *i915, u8 *i2c_pin)
{
	const stwuct intew_bios_encodew_data *devdata;

	if (wist_empty(&i915->dispway.vbt.dispway_devices))
		wetuwn twue;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		const stwuct chiwd_device_config *chiwd = &devdata->chiwd;

		/* If the device type is not WFP, continue.
		 * We have to check both the new identifiews as weww as the
		 * owd fow compatibiwity with some BIOSes.
		 */
		if (chiwd->device_type != DEVICE_TYPE_INT_WFP &&
		    chiwd->device_type != DEVICE_TYPE_WFP)
			continue;

		if (intew_gmbus_is_vawid_pin(i915, chiwd->i2c_pin))
			*i2c_pin = chiwd->i2c_pin;

		/* Howevew, we cannot twust the BIOS wwitews to popuwate
		 * the VBT cowwectwy.  Since WVDS wequiwes additionaw
		 * infowmation fwom AIM bwocks, a non-zewo addin offset is
		 * a good indicatow that the WVDS is actuawwy pwesent.
		 */
		if (chiwd->addin_offset)
			wetuwn twue;

		/* But even then some BIOS wwitews pewfowm some bwack magic
		 * and instantiate the device without wefewence to any
		 * additionaw data.  Twust that if the VBT was wwitten into
		 * the OpWegion then they have vawidated the WVDS's existence.
		 */
		if (i915->dispway.opwegion.vbt)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * intew_bios_is_powt_pwesent - is the specified digitaw powt pwesent
 * @i915:	i915 device instance
 * @powt:	powt to check
 *
 * Wetuwn twue if the device in %powt is pwesent.
 */
boow intew_bios_is_powt_pwesent(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	const stwuct intew_bios_encodew_data *devdata;

	if (WAWN_ON(!has_ddi_powt_info(i915)))
		wetuwn twue;

	if (!is_powt_vawid(i915, powt))
		wetuwn fawse;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		const stwuct chiwd_device_config *chiwd = &devdata->chiwd;

		if (dvo_powt_to_powt(i915, chiwd->dvo_powt) == powt)
			wetuwn twue;
	}

	wetuwn fawse;
}

boow intew_bios_encodew_suppowts_dp_duaw_mode(const stwuct intew_bios_encodew_data *devdata)
{
	const stwuct chiwd_device_config *chiwd = &devdata->chiwd;

	if (!intew_bios_encodew_suppowts_dp(devdata) ||
	    !intew_bios_encodew_suppowts_hdmi(devdata))
		wetuwn fawse;

	if (dvo_powt_type(chiwd->dvo_powt) == DVO_POWT_DPA)
		wetuwn twue;

	/* Onwy accept a HDMI dvo_powt as DP++ if it has an AUX channew */
	if (dvo_powt_type(chiwd->dvo_powt) == DVO_POWT_HDMIA &&
	    chiwd->aux_channew != 0)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * intew_bios_is_dsi_pwesent - is DSI pwesent in VBT
 * @i915:	i915 device instance
 * @powt:	powt fow DSI if pwesent
 *
 * Wetuwn twue if DSI is pwesent, and wetuwn the powt in %powt.
 */
boow intew_bios_is_dsi_pwesent(stwuct dwm_i915_pwivate *i915,
			       enum powt *powt)
{
	const stwuct intew_bios_encodew_data *devdata;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		const stwuct chiwd_device_config *chiwd = &devdata->chiwd;
		u8 dvo_powt = chiwd->dvo_powt;

		if (!(chiwd->device_type & DEVICE_TYPE_MIPI_OUTPUT))
			continue;

		if (dsi_dvo_powt_to_powt(i915, dvo_powt) == POWT_NONE) {
			dwm_dbg_kms(&i915->dwm,
				    "VBT has unsuppowted DSI powt %c\n",
				    powt_name(dvo_powt - DVO_POWT_MIPIA));
			continue;
		}

		if (powt)
			*powt = dsi_dvo_powt_to_powt(i915, dvo_powt);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void fiww_dsc(stwuct intew_cwtc_state *cwtc_state,
		     stwuct dsc_compwession_pawametews_entwy *dsc,
		     int dsc_max_bpc)
{
	stwuct dwm_dsc_config *vdsc_cfg = &cwtc_state->dsc.config;
	int bpc = 8;

	vdsc_cfg->dsc_vewsion_majow = dsc->vewsion_majow;
	vdsc_cfg->dsc_vewsion_minow = dsc->vewsion_minow;

	if (dsc->suppowt_12bpc && dsc_max_bpc >= 12)
		bpc = 12;
	ewse if (dsc->suppowt_10bpc && dsc_max_bpc >= 10)
		bpc = 10;
	ewse if (dsc->suppowt_8bpc && dsc_max_bpc >= 8)
		bpc = 8;
	ewse
		DWM_DEBUG_KMS("VBT: Unsuppowted BPC %d fow DCS\n",
			      dsc_max_bpc);

	cwtc_state->pipe_bpp = bpc * 3;

	cwtc_state->dsc.compwessed_bpp_x16 = to_bpp_x16(min(cwtc_state->pipe_bpp,
							    VBT_DSC_MAX_BPP(dsc->max_bpp)));

	/*
	 * FIXME: This is ugwy, and swice count shouwd take DSC engine
	 * thwoughput etc. into account.
	 *
	 * Awso, pew spec DSI suppowts 1, 2, 3 ow 4 howizontaw swices.
	 */
	if (dsc->swices_pew_wine & BIT(2)) {
		cwtc_state->dsc.swice_count = 4;
	} ewse if (dsc->swices_pew_wine & BIT(1)) {
		cwtc_state->dsc.swice_count = 2;
	} ewse {
		/* FIXME */
		if (!(dsc->swices_pew_wine & BIT(0)))
			DWM_DEBUG_KMS("VBT: Unsuppowted DSC swice count fow DSI\n");

		cwtc_state->dsc.swice_count = 1;
	}

	if (cwtc_state->hw.adjusted_mode.cwtc_hdispway %
	    cwtc_state->dsc.swice_count != 0)
		DWM_DEBUG_KMS("VBT: DSC hdispway %d not divisibwe by swice count %d\n",
			      cwtc_state->hw.adjusted_mode.cwtc_hdispway,
			      cwtc_state->dsc.swice_count);

	/*
	 * The VBT wc_buffew_bwock_size and wc_buffew_size definitions
	 * cowwespond to DP 1.4 DPCD offsets 0x62 and 0x63.
	 */
	vdsc_cfg->wc_modew_size = dwm_dsc_dp_wc_buffew_size(dsc->wc_buffew_bwock_size,
							    dsc->wc_buffew_size);

	/* FIXME: DSI spec says bpc + 1 fow this one */
	vdsc_cfg->wine_buf_depth = VBT_DSC_WINE_BUFFEW_DEPTH(dsc->wine_buffew_depth);

	vdsc_cfg->bwock_pwed_enabwe = dsc->bwock_pwediction_enabwe;

	vdsc_cfg->swice_height = dsc->swice_height;
}

/* FIXME: initiawwy DSI specific */
boow intew_bios_get_dsc_pawams(stwuct intew_encodew *encodew,
			       stwuct intew_cwtc_state *cwtc_state,
			       int dsc_max_bpc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct intew_bios_encodew_data *devdata;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		const stwuct chiwd_device_config *chiwd = &devdata->chiwd;

		if (!(chiwd->device_type & DEVICE_TYPE_MIPI_OUTPUT))
			continue;

		if (dsi_dvo_powt_to_powt(i915, chiwd->dvo_powt) == encodew->powt) {
			if (!devdata->dsc)
				wetuwn fawse;

			fiww_dsc(cwtc_state, devdata->dsc, dsc_max_bpc);

			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static const u8 adwp_aux_ch_map[] = {
	[AUX_CH_A] = DP_AUX_A,
	[AUX_CH_B] = DP_AUX_B,
	[AUX_CH_C] = DP_AUX_C,
	[AUX_CH_D_XEWPD] = DP_AUX_D,
	[AUX_CH_E_XEWPD] = DP_AUX_E,
	[AUX_CH_USBC1] = DP_AUX_F,
	[AUX_CH_USBC2] = DP_AUX_G,
	[AUX_CH_USBC3] = DP_AUX_H,
	[AUX_CH_USBC4] = DP_AUX_I,
};

/*
 * ADW-S VBT uses PHY based mapping. Combo PHYs A,B,C,D,E
 * map to DDI A,TC1,TC2,TC3,TC4 wespectivewy.
 */
static const u8 adws_aux_ch_map[] = {
	[AUX_CH_A] = DP_AUX_A,
	[AUX_CH_USBC1] = DP_AUX_B,
	[AUX_CH_USBC2] = DP_AUX_C,
	[AUX_CH_USBC3] = DP_AUX_D,
	[AUX_CH_USBC4] = DP_AUX_E,
};

/*
 * WKW/DG1 VBT uses PHY based mapping. Combo PHYs A,B,C,D
 * map to DDI A,B,TC1,TC2 wespectivewy.
 */
static const u8 wkw_aux_ch_map[] = {
	[AUX_CH_A] = DP_AUX_A,
	[AUX_CH_B] = DP_AUX_B,
	[AUX_CH_USBC1] = DP_AUX_C,
	[AUX_CH_USBC2] = DP_AUX_D,
};

static const u8 diwect_aux_ch_map[] = {
	[AUX_CH_A] = DP_AUX_A,
	[AUX_CH_B] = DP_AUX_B,
	[AUX_CH_C] = DP_AUX_C,
	[AUX_CH_D] = DP_AUX_D, /* aka AUX_CH_USBC1 */
	[AUX_CH_E] = DP_AUX_E, /* aka AUX_CH_USBC2 */
	[AUX_CH_F] = DP_AUX_F, /* aka AUX_CH_USBC3 */
	[AUX_CH_G] = DP_AUX_G, /* aka AUX_CH_USBC4 */
	[AUX_CH_H] = DP_AUX_H, /* aka AUX_CH_USBC5 */
	[AUX_CH_I] = DP_AUX_I, /* aka AUX_CH_USBC6 */
};

static enum aux_ch map_aux_ch(stwuct dwm_i915_pwivate *i915, u8 aux_channew)
{
	const u8 *aux_ch_map;
	int i, n_entwies;

	if (DISPWAY_VEW(i915) >= 13) {
		aux_ch_map = adwp_aux_ch_map;
		n_entwies = AWWAY_SIZE(adwp_aux_ch_map);
	} ewse if (IS_AWDEWWAKE_S(i915)) {
		aux_ch_map = adws_aux_ch_map;
		n_entwies = AWWAY_SIZE(adws_aux_ch_map);
	} ewse if (IS_DG1(i915) || IS_WOCKETWAKE(i915)) {
		aux_ch_map = wkw_aux_ch_map;
		n_entwies = AWWAY_SIZE(wkw_aux_ch_map);
	} ewse {
		aux_ch_map = diwect_aux_ch_map;
		n_entwies = AWWAY_SIZE(diwect_aux_ch_map);
	}

	fow (i = 0; i < n_entwies; i++) {
		if (aux_ch_map[i] == aux_channew)
			wetuwn i;
	}

	dwm_dbg_kms(&i915->dwm,
		    "Ignowing awtewnate AUX CH: VBT cwaims AUX 0x%x, which is not vawid fow this pwatfowm\n",
		    aux_channew);

	wetuwn AUX_CH_NONE;
}

enum aux_ch intew_bios_dp_aux_ch(const stwuct intew_bios_encodew_data *devdata)
{
	if (!devdata || !devdata->chiwd.aux_channew)
		wetuwn AUX_CH_NONE;

	wetuwn map_aux_ch(devdata->i915, devdata->chiwd.aux_channew);
}

boow intew_bios_dp_has_shawed_aux_ch(const stwuct intew_bios_encodew_data *devdata)
{
	stwuct dwm_i915_pwivate *i915;
	u8 aux_channew;
	int count = 0;

	if (!devdata || !devdata->chiwd.aux_channew)
		wetuwn fawse;

	i915 = devdata->i915;
	aux_channew = devdata->chiwd.aux_channew;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		if (intew_bios_encodew_suppowts_dp(devdata) &&
		    aux_channew == devdata->chiwd.aux_channew)
			count++;
	}

	wetuwn count > 1;
}

int intew_bios_dp_boost_wevew(const stwuct intew_bios_encodew_data *devdata)
{
	if (!devdata || devdata->i915->dispway.vbt.vewsion < 196 || !devdata->chiwd.iboost)
		wetuwn 0;

	wetuwn twanswate_iboost(devdata->chiwd.dp_iboost_wevew);
}

int intew_bios_hdmi_boost_wevew(const stwuct intew_bios_encodew_data *devdata)
{
	if (!devdata || devdata->i915->dispway.vbt.vewsion < 196 || !devdata->chiwd.iboost)
		wetuwn 0;

	wetuwn twanswate_iboost(devdata->chiwd.hdmi_iboost_wevew);
}

int intew_bios_hdmi_ddc_pin(const stwuct intew_bios_encodew_data *devdata)
{
	if (!devdata || !devdata->chiwd.ddc_pin)
		wetuwn 0;

	wetuwn map_ddc_pin(devdata->i915, devdata->chiwd.ddc_pin);
}

boow intew_bios_encodew_suppowts_typec_usb(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata->i915->dispway.vbt.vewsion >= 195 && devdata->chiwd.dp_usb_type_c;
}

boow intew_bios_encodew_suppowts_tbt(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata->i915->dispway.vbt.vewsion >= 209 && devdata->chiwd.tbt;
}

boow intew_bios_encodew_wane_wevewsaw(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata && devdata->chiwd.wane_wevewsaw;
}

boow intew_bios_encodew_hpd_invewt(const stwuct intew_bios_encodew_data *devdata)
{
	wetuwn devdata && devdata->chiwd.hpd_invewt;
}

const stwuct intew_bios_encodew_data *
intew_bios_encodew_data_wookup(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	stwuct intew_bios_encodew_data *devdata;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node) {
		if (intew_bios_encodew_powt(devdata) == powt)
			wetuwn devdata;
	}

	wetuwn NUWW;
}

void intew_bios_fow_each_encodew(stwuct dwm_i915_pwivate *i915,
				 void (*func)(stwuct dwm_i915_pwivate *i915,
					      const stwuct intew_bios_encodew_data *devdata))
{
	stwuct intew_bios_encodew_data *devdata;

	wist_fow_each_entwy(devdata, &i915->dispway.vbt.dispway_devices, node)
		func(i915, devdata);
}
