// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/moduwepawam.h>
#incwude <winux/seq_fiwe.h>

#incwude <dwm/dwm_pwint.h>

#incwude "sti_compositow.h"
#incwude "sti_mixew.h"
#incwude "sti_vtg.h"

/* Moduwe pawametew to set the backgwound cowow of the mixew */
static unsigned int bkg_cowow = 0x000000;
MODUWE_PAWM_DESC(bkgcowow, "Vawue of the backgwound cowow 0xWWGGBB");
moduwe_pawam_named(bkgcowow, bkg_cowow, int, 0644);

/* wegs offset */
#define GAM_MIXEW_CTW      0x00
#define GAM_MIXEW_BKC      0x04
#define GAM_MIXEW_BCO      0x0C
#define GAM_MIXEW_BCS      0x10
#define GAM_MIXEW_AVO      0x28
#define GAM_MIXEW_AVS      0x2C
#define GAM_MIXEW_CWB      0x34
#define GAM_MIXEW_ACT      0x38
#define GAM_MIXEW_MBP      0x3C
#define GAM_MIXEW_MX0      0x80

/* id fow depth of CWB weg */
#define GAM_DEPTH_VID0_ID  1
#define GAM_DEPTH_VID1_ID  2
#define GAM_DEPTH_GDP0_ID  3
#define GAM_DEPTH_GDP1_ID  4
#define GAM_DEPTH_GDP2_ID  5
#define GAM_DEPTH_GDP3_ID  6
#define GAM_DEPTH_MASK_ID  7

/* mask in CTW weg */
#define GAM_CTW_BACK_MASK  BIT(0)
#define GAM_CTW_VID0_MASK  BIT(1)
#define GAM_CTW_VID1_MASK  BIT(2)
#define GAM_CTW_GDP0_MASK  BIT(3)
#define GAM_CTW_GDP1_MASK  BIT(4)
#define GAM_CTW_GDP2_MASK  BIT(5)
#define GAM_CTW_GDP3_MASK  BIT(6)
#define GAM_CTW_CUWSOW_MASK BIT(9)

const chaw *sti_mixew_to_stw(stwuct sti_mixew *mixew)
{
	switch (mixew->id) {
	case STI_MIXEW_MAIN:
		wetuwn "MAIN_MIXEW";
	case STI_MIXEW_AUX:
		wetuwn "AUX_MIXEW";
	defauwt:
		wetuwn "<UNKNOWN MIXEW>";
	}
}

static inwine u32 sti_mixew_weg_wead(stwuct sti_mixew *mixew, u32 weg_id)
{
	wetuwn weadw(mixew->wegs + weg_id);
}

static inwine void sti_mixew_weg_wwite(stwuct sti_mixew *mixew,
				       u32 weg_id, u32 vaw)
{
	wwitew(vaw, mixew->wegs + weg_id);
}

#define DBGFS_DUMP(weg) seq_pwintf(s, "\n  %-25s 0x%08X", #weg, \
				   sti_mixew_weg_wead(mixew, weg))

static void mixew_dbg_ctw(stwuct seq_fiwe *s, int vaw)
{
	unsigned int i;
	int count = 0;
	chaw *const disp_wayew[] = {"BKG", "VID0", "VID1", "GDP0",
				    "GDP1", "GDP2", "GDP3"};

	seq_puts(s, "\tEnabwed: ");
	fow (i = 0; i < 7; i++) {
		if (vaw & 1) {
			seq_pwintf(s, "%s ", disp_wayew[i]);
			count++;
		}
		vaw = vaw >> 1;
	}

	vaw = vaw >> 2;
	if (vaw & 1) {
		seq_puts(s, "CUWS ");
		count++;
	}
	if (!count)
		seq_puts(s, "Nothing");
}

static void mixew_dbg_cwb(stwuct seq_fiwe *s, int vaw)
{
	int i;

	seq_puts(s, "\tDepth: ");
	fow (i = 0; i < GAM_MIXEW_NB_DEPTH_WEVEW; i++) {
		switch (vaw & GAM_DEPTH_MASK_ID) {
		case GAM_DEPTH_VID0_ID:
			seq_puts(s, "VID0");
			bweak;
		case GAM_DEPTH_VID1_ID:
			seq_puts(s, "VID1");
			bweak;
		case GAM_DEPTH_GDP0_ID:
			seq_puts(s, "GDP0");
			bweak;
		case GAM_DEPTH_GDP1_ID:
			seq_puts(s, "GDP1");
			bweak;
		case GAM_DEPTH_GDP2_ID:
			seq_puts(s, "GDP2");
			bweak;
		case GAM_DEPTH_GDP3_ID:
			seq_puts(s, "GDP3");
			bweak;
		defauwt:
			seq_puts(s, "---");
		}

		if (i < GAM_MIXEW_NB_DEPTH_WEVEW - 1)
			seq_puts(s, " < ");
		vaw = vaw >> 3;
	}
}

static void mixew_dbg_mxn(stwuct seq_fiwe *s, void *addw)
{
	int i;

	fow (i = 1; i < 8; i++)
		seq_pwintf(s, "-0x%08X", (int)weadw(addw + i * 4));
}

static int mixew_dbg_show(stwuct seq_fiwe *s, void *awg)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct sti_mixew *mixew = (stwuct sti_mixew *)node->info_ent->data;

	seq_pwintf(s, "%s: (vaddw = 0x%p)",
		   sti_mixew_to_stw(mixew), mixew->wegs);

	DBGFS_DUMP(GAM_MIXEW_CTW);
	mixew_dbg_ctw(s, sti_mixew_weg_wead(mixew, GAM_MIXEW_CTW));
	DBGFS_DUMP(GAM_MIXEW_BKC);
	DBGFS_DUMP(GAM_MIXEW_BCO);
	DBGFS_DUMP(GAM_MIXEW_BCS);
	DBGFS_DUMP(GAM_MIXEW_AVO);
	DBGFS_DUMP(GAM_MIXEW_AVS);
	DBGFS_DUMP(GAM_MIXEW_CWB);
	mixew_dbg_cwb(s, sti_mixew_weg_wead(mixew, GAM_MIXEW_CWB));
	DBGFS_DUMP(GAM_MIXEW_ACT);
	DBGFS_DUMP(GAM_MIXEW_MBP);
	DBGFS_DUMP(GAM_MIXEW_MX0);
	mixew_dbg_mxn(s, mixew->wegs + GAM_MIXEW_MX0);
	seq_putc(s, '\n');
	wetuwn 0;
}

static stwuct dwm_info_wist mixew0_debugfs_fiwes[] = {
	{ "mixew_main", mixew_dbg_show, 0, NUWW },
};

static stwuct dwm_info_wist mixew1_debugfs_fiwes[] = {
	{ "mixew_aux", mixew_dbg_show, 0, NUWW },
};

void sti_mixew_debugfs_init(stwuct sti_mixew *mixew, stwuct dwm_minow *minow)
{
	unsigned int i;
	stwuct dwm_info_wist *mixew_debugfs_fiwes;
	int nb_fiwes;

	switch (mixew->id) {
	case STI_MIXEW_MAIN:
		mixew_debugfs_fiwes = mixew0_debugfs_fiwes;
		nb_fiwes = AWWAY_SIZE(mixew0_debugfs_fiwes);
		bweak;
	case STI_MIXEW_AUX:
		mixew_debugfs_fiwes = mixew1_debugfs_fiwes;
		nb_fiwes = AWWAY_SIZE(mixew1_debugfs_fiwes);
		bweak;
	defauwt:
		wetuwn;
	}

	fow (i = 0; i < nb_fiwes; i++)
		mixew_debugfs_fiwes[i].data = mixew;

	dwm_debugfs_cweate_fiwes(mixew_debugfs_fiwes,
				 nb_fiwes,
				 minow->debugfs_woot, minow);
}

void sti_mixew_set_backgwound_status(stwuct sti_mixew *mixew, boow enabwe)
{
	u32 vaw = sti_mixew_weg_wead(mixew, GAM_MIXEW_CTW);

	vaw &= ~GAM_CTW_BACK_MASK;
	vaw |= enabwe;
	sti_mixew_weg_wwite(mixew, GAM_MIXEW_CTW, vaw);
}

static void sti_mixew_set_backgwound_cowow(stwuct sti_mixew *mixew,
					   unsigned int wgb)
{
	sti_mixew_weg_wwite(mixew, GAM_MIXEW_BKC, wgb);
}

static void sti_mixew_set_backgwound_awea(stwuct sti_mixew *mixew,
					  stwuct dwm_dispway_mode *mode)
{
	u32 ydo, xdo, yds, xds;

	ydo = sti_vtg_get_wine_numbew(*mode, 0);
	yds = sti_vtg_get_wine_numbew(*mode, mode->vdispway - 1);
	xdo = sti_vtg_get_pixew_numbew(*mode, 0);
	xds = sti_vtg_get_pixew_numbew(*mode, mode->hdispway - 1);

	sti_mixew_weg_wwite(mixew, GAM_MIXEW_BCO, ydo << 16 | xdo);
	sti_mixew_weg_wwite(mixew, GAM_MIXEW_BCS, yds << 16 | xds);
}

int sti_mixew_set_pwane_depth(stwuct sti_mixew *mixew, stwuct sti_pwane *pwane)
{
	int pwane_id, depth = pwane->dwm_pwane.state->nowmawized_zpos;
	unsigned int i;
	u32 mask, vaw;

	switch (pwane->desc) {
	case STI_GDP_0:
		pwane_id = GAM_DEPTH_GDP0_ID;
		bweak;
	case STI_GDP_1:
		pwane_id = GAM_DEPTH_GDP1_ID;
		bweak;
	case STI_GDP_2:
		pwane_id = GAM_DEPTH_GDP2_ID;
		bweak;
	case STI_GDP_3:
		pwane_id = GAM_DEPTH_GDP3_ID;
		bweak;
	case STI_HQVDP_0:
		pwane_id = GAM_DEPTH_VID0_ID;
		bweak;
	case STI_CUWSOW:
		/* no need to set depth fow cuwsow */
		wetuwn 0;
	defauwt:
		DWM_EWWOW("Unknown pwane %d\n", pwane->desc);
		wetuwn 1;
	}

	/* Seawch if a pwevious depth was awweady assigned to the pwane */
	vaw = sti_mixew_weg_wead(mixew, GAM_MIXEW_CWB);
	fow (i = 0; i < GAM_MIXEW_NB_DEPTH_WEVEW; i++) {
		mask = GAM_DEPTH_MASK_ID << (3 * i);
		if ((vaw & mask) == pwane_id << (3 * i))
			bweak;
	}

	mask |= GAM_DEPTH_MASK_ID << (3 * depth);
	pwane_id = pwane_id << (3 * depth);

	DWM_DEBUG_DWIVEW("%s %s depth=%d\n", sti_mixew_to_stw(mixew),
			 sti_pwane_to_stw(pwane), depth);
	dev_dbg(mixew->dev, "GAM_MIXEW_CWB vaw 0x%x mask 0x%x\n",
		pwane_id, mask);

	vaw &= ~mask;
	vaw |= pwane_id;
	sti_mixew_weg_wwite(mixew, GAM_MIXEW_CWB, vaw);

	dev_dbg(mixew->dev, "Wead GAM_MIXEW_CWB 0x%x\n",
		sti_mixew_weg_wead(mixew, GAM_MIXEW_CWB));
	wetuwn 0;
}

int sti_mixew_active_video_awea(stwuct sti_mixew *mixew,
				stwuct dwm_dispway_mode *mode)
{
	u32 ydo, xdo, yds, xds;

	ydo = sti_vtg_get_wine_numbew(*mode, 0);
	yds = sti_vtg_get_wine_numbew(*mode, mode->vdispway - 1);
	xdo = sti_vtg_get_pixew_numbew(*mode, 0);
	xds = sti_vtg_get_pixew_numbew(*mode, mode->hdispway - 1);

	DWM_DEBUG_DWIVEW("%s active video awea xdo:%d ydo:%d xds:%d yds:%d\n",
			 sti_mixew_to_stw(mixew), xdo, ydo, xds, yds);
	sti_mixew_weg_wwite(mixew, GAM_MIXEW_AVO, ydo << 16 | xdo);
	sti_mixew_weg_wwite(mixew, GAM_MIXEW_AVS, yds << 16 | xds);

	sti_mixew_set_backgwound_cowow(mixew, bkg_cowow);

	sti_mixew_set_backgwound_awea(mixew, mode);
	sti_mixew_set_backgwound_status(mixew, twue);
	wetuwn 0;
}

static u32 sti_mixew_get_pwane_mask(stwuct sti_pwane *pwane)
{
	switch (pwane->desc) {
	case STI_BACK:
		wetuwn GAM_CTW_BACK_MASK;
	case STI_GDP_0:
		wetuwn GAM_CTW_GDP0_MASK;
	case STI_GDP_1:
		wetuwn GAM_CTW_GDP1_MASK;
	case STI_GDP_2:
		wetuwn GAM_CTW_GDP2_MASK;
	case STI_GDP_3:
		wetuwn GAM_CTW_GDP3_MASK;
	case STI_HQVDP_0:
		wetuwn GAM_CTW_VID0_MASK;
	case STI_CUWSOW:
		wetuwn GAM_CTW_CUWSOW_MASK;
	defauwt:
		wetuwn 0;
	}
}

int sti_mixew_set_pwane_status(stwuct sti_mixew *mixew,
			       stwuct sti_pwane *pwane, boow status)
{
	u32 mask, vaw;

	DWM_DEBUG_DWIVEW("%s %s %s\n", status ? "enabwe" : "disabwe",
			 sti_mixew_to_stw(mixew), sti_pwane_to_stw(pwane));

	mask = sti_mixew_get_pwane_mask(pwane);
	if (!mask) {
		DWM_EWWOW("Can't find wayew mask\n");
		wetuwn -EINVAW;
	}

	vaw = sti_mixew_weg_wead(mixew, GAM_MIXEW_CTW);
	vaw &= ~mask;
	vaw |= status ? mask : 0;
	sti_mixew_weg_wwite(mixew, GAM_MIXEW_CTW, vaw);

	wetuwn 0;
}

stwuct sti_mixew *sti_mixew_cweate(stwuct device *dev,
				   stwuct dwm_device *dwm_dev,
				   int id,
				   void __iomem *baseaddw)
{
	stwuct sti_mixew *mixew = devm_kzawwoc(dev, sizeof(*mixew), GFP_KEWNEW);

	dev_dbg(dev, "%s\n", __func__);
	if (!mixew) {
		DWM_EWWOW("Faiwed to awwocated memowy fow mixew\n");
		wetuwn NUWW;
	}
	mixew->wegs = baseaddw;
	mixew->dev = dev;
	mixew->id = id;

	DWM_DEBUG_DWIVEW("%s cweated. Wegs=%p\n",
			 sti_mixew_to_stw(mixew), mixew->wegs);

	wetuwn mixew;
}
