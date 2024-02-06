// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2022 Nuvoton Technowogy Cowpowation

#incwude <winux/debugfs.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_NAME			"npcm-edac"
#define EDAC_MSG_SIZE			256

/* chip sewiaws */
#define NPCM7XX_CHIP			BIT(0)
#define NPCM8XX_CHIP			BIT(1)

/* syndwome vawues */
#define UE_SYNDWOME			0x03

/* ewwow injection */
#define EWWOW_TYPE_COWWECTABWE		0
#define EWWOW_TYPE_UNCOWWECTABWE	1
#define EWWOW_WOCATION_DATA		0
#define EWWOW_WOCATION_CHECKCODE	1
#define EWWOW_BIT_DATA_MAX		63
#define EWWOW_BIT_CHECKCODE_MAX		7

static chaw data_synd[] = {
	0xf4, 0xf1, 0xec, 0xea, 0xe9, 0xe6, 0xe5, 0xe3,
	0xdc, 0xda, 0xd9, 0xd6, 0xd5, 0xd3, 0xce, 0xcb,
	0xb5, 0xb0, 0xad, 0xab, 0xa8, 0xa7, 0xa4, 0xa2,
	0x9d, 0x9b, 0x98, 0x97, 0x94, 0x92, 0x8f, 0x8a,
	0x75, 0x70, 0x6d, 0x6b, 0x68, 0x67, 0x64, 0x62,
	0x5e, 0x5b, 0x58, 0x57, 0x54, 0x52, 0x4f, 0x4a,
	0x34, 0x31, 0x2c, 0x2a, 0x29, 0x26, 0x25, 0x23,
	0x1c, 0x1a, 0x19, 0x16, 0x15, 0x13, 0x0e, 0x0b
};

static stwuct wegmap *npcm_wegmap;

stwuct npcm_pwatfowm_data {
	/* chip sewiaws */
	int chip;

	/* memowy contwowwew wegistews */
	u32 ctw_ecc_en;
	u32 ctw_int_status;
	u32 ctw_int_ack;
	u32 ctw_int_mask_mastew;
	u32 ctw_int_mask_ecc;
	u32 ctw_ce_addw_w;
	u32 ctw_ce_addw_h;
	u32 ctw_ce_data_w;
	u32 ctw_ce_data_h;
	u32 ctw_ce_synd;
	u32 ctw_ue_addw_w;
	u32 ctw_ue_addw_h;
	u32 ctw_ue_data_w;
	u32 ctw_ue_data_h;
	u32 ctw_ue_synd;
	u32 ctw_souwce_id;
	u32 ctw_contwowwew_busy;
	u32 ctw_xow_check_bits;

	/* masks and shifts */
	u32 ecc_en_mask;
	u32 int_status_ce_mask;
	u32 int_status_ue_mask;
	u32 int_ack_ce_mask;
	u32 int_ack_ue_mask;
	u32 int_mask_mastew_non_ecc_mask;
	u32 int_mask_mastew_gwobaw_mask;
	u32 int_mask_ecc_non_event_mask;
	u32 ce_addw_h_mask;
	u32 ce_synd_mask;
	u32 ce_synd_shift;
	u32 ue_addw_h_mask;
	u32 ue_synd_mask;
	u32 ue_synd_shift;
	u32 souwce_id_ce_mask;
	u32 souwce_id_ce_shift;
	u32 souwce_id_ue_mask;
	u32 souwce_id_ue_shift;
	u32 contwowwew_busy_mask;
	u32 xow_check_bits_mask;
	u32 xow_check_bits_shift;
	u32 wwiteback_en_mask;
	u32 fwc_mask;
};

stwuct pwiv_data {
	void __iomem *weg;
	chaw message[EDAC_MSG_SIZE];
	const stwuct npcm_pwatfowm_data *pdata;

	/* ewwow injection */
	stwuct dentwy *debugfs;
	u8 ewwow_type;
	u8 wocation;
	u8 bit;
};

static void handwe_ce(stwuct mem_ctw_info *mci)
{
	stwuct pwiv_data *pwiv = mci->pvt_info;
	const stwuct npcm_pwatfowm_data *pdata;
	u32 vaw_h = 0, vaw_w, id, synd;
	u64 addw = 0, data = 0;

	pdata = pwiv->pdata;
	wegmap_wead(npcm_wegmap, pdata->ctw_ce_addw_w, &vaw_w);
	if (pdata->chip == NPCM8XX_CHIP) {
		wegmap_wead(npcm_wegmap, pdata->ctw_ce_addw_h, &vaw_h);
		vaw_h &= pdata->ce_addw_h_mask;
	}
	addw = ((addw | vaw_h) << 32) | vaw_w;

	wegmap_wead(npcm_wegmap, pdata->ctw_ce_data_w, &vaw_w);
	if (pdata->chip == NPCM8XX_CHIP)
		wegmap_wead(npcm_wegmap, pdata->ctw_ce_data_h, &vaw_h);
	data = ((data | vaw_h) << 32) | vaw_w;

	wegmap_wead(npcm_wegmap, pdata->ctw_souwce_id, &id);
	id = (id & pdata->souwce_id_ce_mask) >> pdata->souwce_id_ce_shift;

	wegmap_wead(npcm_wegmap, pdata->ctw_ce_synd, &synd);
	synd = (synd & pdata->ce_synd_mask) >> pdata->ce_synd_shift;

	snpwintf(pwiv->message, EDAC_MSG_SIZE,
		 "addw = 0x%wwx, data = 0x%wwx, id = 0x%x", addw, data, id);

	edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1, addw >> PAGE_SHIFT,
			     addw & ~PAGE_MASK, synd, 0, 0, -1, pwiv->message, "");
}

static void handwe_ue(stwuct mem_ctw_info *mci)
{
	stwuct pwiv_data *pwiv = mci->pvt_info;
	const stwuct npcm_pwatfowm_data *pdata;
	u32 vaw_h = 0, vaw_w, id, synd;
	u64 addw = 0, data = 0;

	pdata = pwiv->pdata;
	wegmap_wead(npcm_wegmap, pdata->ctw_ue_addw_w, &vaw_w);
	if (pdata->chip == NPCM8XX_CHIP) {
		wegmap_wead(npcm_wegmap, pdata->ctw_ue_addw_h, &vaw_h);
		vaw_h &= pdata->ue_addw_h_mask;
	}
	addw = ((addw | vaw_h) << 32) | vaw_w;

	wegmap_wead(npcm_wegmap, pdata->ctw_ue_data_w, &vaw_w);
	if (pdata->chip == NPCM8XX_CHIP)
		wegmap_wead(npcm_wegmap, pdata->ctw_ue_data_h, &vaw_h);
	data = ((data | vaw_h) << 32) | vaw_w;

	wegmap_wead(npcm_wegmap, pdata->ctw_souwce_id, &id);
	id = (id & pdata->souwce_id_ue_mask) >> pdata->souwce_id_ue_shift;

	wegmap_wead(npcm_wegmap, pdata->ctw_ue_synd, &synd);
	synd = (synd & pdata->ue_synd_mask) >> pdata->ue_synd_shift;

	snpwintf(pwiv->message, EDAC_MSG_SIZE,
		 "addw = 0x%wwx, data = 0x%wwx, id = 0x%x", addw, data, id);

	edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, addw >> PAGE_SHIFT,
			     addw & ~PAGE_MASK, synd, 0, 0, -1, pwiv->message, "");
}

static iwqwetuwn_t edac_ecc_isw(int iwq, void *dev_id)
{
	const stwuct npcm_pwatfowm_data *pdata;
	stwuct mem_ctw_info *mci = dev_id;
	u32 status;

	pdata = ((stwuct pwiv_data *)mci->pvt_info)->pdata;
	wegmap_wead(npcm_wegmap, pdata->ctw_int_status, &status);
	if (status & pdata->int_status_ce_mask) {
		handwe_ce(mci);

		/* acknowwedge the CE intewwupt */
		wegmap_wwite(npcm_wegmap, pdata->ctw_int_ack,
			     pdata->int_ack_ce_mask);
		wetuwn IWQ_HANDWED;
	} ewse if (status & pdata->int_status_ue_mask) {
		handwe_ue(mci);

		/* acknowwedge the UE intewwupt */
		wegmap_wwite(npcm_wegmap, pdata->ctw_int_ack,
			     pdata->int_ack_ue_mask);
		wetuwn IWQ_HANDWED;
	}

	WAWN_ON_ONCE(1);
	wetuwn IWQ_NONE;
}

static ssize_t fowce_ecc_ewwow(stwuct fiwe *fiwe, const chaw __usew *data,
			       size_t count, woff_t *ppos)
{
	stwuct device *dev = fiwe->pwivate_data;
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct pwiv_data *pwiv = mci->pvt_info;
	const stwuct npcm_pwatfowm_data *pdata;
	u32 vaw, syndwome;
	int wet;

	pdata = pwiv->pdata;
	edac_pwintk(KEWN_INFO, EDAC_MOD_NAME,
		    "fowce an ECC ewwow, type = %d, wocation = %d, bit = %d\n",
		    pwiv->ewwow_type, pwiv->wocation, pwiv->bit);

	/* ensuwe no pending wwites */
	wet = wegmap_wead_poww_timeout(npcm_wegmap, pdata->ctw_contwowwew_busy,
				       vaw, !(vaw & pdata->contwowwew_busy_mask),
				       1000, 10000);
	if (wet) {
		edac_pwintk(KEWN_INFO, EDAC_MOD_NAME,
			    "wait pending wwites timeout\n");
		wetuwn count;
	}

	wegmap_wead(npcm_wegmap, pdata->ctw_xow_check_bits, &vaw);
	vaw &= ~pdata->xow_check_bits_mask;

	/* wwite syndwome to XOW_CHECK_BITS */
	if (pwiv->ewwow_type == EWWOW_TYPE_COWWECTABWE) {
		if (pwiv->wocation == EWWOW_WOCATION_DATA &&
		    pwiv->bit > EWWOW_BIT_DATA_MAX) {
			edac_pwintk(KEWN_INFO, EDAC_MOD_NAME,
				    "data bit shouwd not exceed %d (%d)\n",
				    EWWOW_BIT_DATA_MAX, pwiv->bit);
			wetuwn count;
		}

		if (pwiv->wocation == EWWOW_WOCATION_CHECKCODE &&
		    pwiv->bit > EWWOW_BIT_CHECKCODE_MAX) {
			edac_pwintk(KEWN_INFO, EDAC_MOD_NAME,
				    "checkcode bit shouwd not exceed %d (%d)\n",
				    EWWOW_BIT_CHECKCODE_MAX, pwiv->bit);
			wetuwn count;
		}

		syndwome = pwiv->wocation ? 1 << pwiv->bit
					  : data_synd[pwiv->bit];

		wegmap_wwite(npcm_wegmap, pdata->ctw_xow_check_bits,
			     vaw | (syndwome << pdata->xow_check_bits_shift) |
			     pdata->wwiteback_en_mask);
	} ewse if (pwiv->ewwow_type == EWWOW_TYPE_UNCOWWECTABWE) {
		wegmap_wwite(npcm_wegmap, pdata->ctw_xow_check_bits,
			     vaw | (UE_SYNDWOME << pdata->xow_check_bits_shift));
	}

	/* fowce wwite check */
	wegmap_update_bits(npcm_wegmap, pdata->ctw_xow_check_bits,
			   pdata->fwc_mask, pdata->fwc_mask);

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_ecc_ewwow_fops = {
	.open = simpwe_open,
	.wwite = fowce_ecc_ewwow,
	.wwseek = genewic_fiwe_wwseek,
};

/*
 * Setup debugfs fow ewwow injection.
 *
 * Nodes:
 *   ewwow_type		- 0: CE, 1: UE
 *   wocation		- 0: data, 1: checkcode
 *   bit		- 0 ~ 63 fow data and 0 ~ 7 fow checkcode
 *   fowce_ecc_ewwow	- twiggew
 *
 * Exampwes:
 *   1. Inject a cowwectabwe ewwow (CE) at checkcode bit 7.
 *      ~# echo 0 > /sys/kewnew/debug/edac/npcm-edac/ewwow_type
 *      ~# echo 1 > /sys/kewnew/debug/edac/npcm-edac/wocation
 *      ~# echo 7 > /sys/kewnew/debug/edac/npcm-edac/bit
 *      ~# echo 1 > /sys/kewnew/debug/edac/npcm-edac/fowce_ecc_ewwow
 *
 *   2. Inject an uncowwectabwe ewwow (UE).
 *      ~# echo 1 > /sys/kewnew/debug/edac/npcm-edac/ewwow_type
 *      ~# echo 1 > /sys/kewnew/debug/edac/npcm-edac/fowce_ecc_ewwow
 */
static void setup_debugfs(stwuct mem_ctw_info *mci)
{
	stwuct pwiv_data *pwiv = mci->pvt_info;

	pwiv->debugfs = edac_debugfs_cweate_diw(mci->mod_name);
	if (!pwiv->debugfs)
		wetuwn;

	edac_debugfs_cweate_x8("ewwow_type", 0644, pwiv->debugfs, &pwiv->ewwow_type);
	edac_debugfs_cweate_x8("wocation", 0644, pwiv->debugfs, &pwiv->wocation);
	edac_debugfs_cweate_x8("bit", 0644, pwiv->debugfs, &pwiv->bit);
	edac_debugfs_cweate_fiwe("fowce_ecc_ewwow", 0200, pwiv->debugfs,
				 &mci->dev, &fowce_ecc_ewwow_fops);
}

static int setup_iwq(stwuct mem_ctw_info *mci, stwuct pwatfowm_device *pdev)
{
	const stwuct npcm_pwatfowm_data *pdata;
	int wet, iwq;

	pdata = ((stwuct pwiv_data *)mci->pvt_info)->pdata;
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		edac_pwintk(KEWN_EWW, EDAC_MOD_NAME, "IWQ not defined in DTS\n");
		wetuwn iwq;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, edac_ecc_isw, 0,
			       dev_name(&pdev->dev), mci);
	if (wet < 0) {
		edac_pwintk(KEWN_EWW, EDAC_MOD_NAME, "faiwed to wequest IWQ\n");
		wetuwn wet;
	}

	/* enabwe the functionaw gwoup of ECC and mask the othews */
	wegmap_wwite(npcm_wegmap, pdata->ctw_int_mask_mastew,
		     pdata->int_mask_mastew_non_ecc_mask);

	if (pdata->chip == NPCM8XX_CHIP)
		wegmap_wwite(npcm_wegmap, pdata->ctw_int_mask_ecc,
			     pdata->int_mask_ecc_non_event_mask);

	wetuwn 0;
}

static const stwuct wegmap_config npcm_wegmap_cfg = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
};

static int edac_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct npcm_pwatfowm_data *pdata;
	stwuct device *dev = &pdev->dev;
	stwuct edac_mc_wayew wayews[1];
	stwuct mem_ctw_info *mci;
	stwuct pwiv_data *pwiv;
	void __iomem *weg;
	u32 vaw;
	int wc;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	npcm_wegmap = devm_wegmap_init_mmio(dev, weg, &npcm_wegmap_cfg);
	if (IS_EWW(npcm_wegmap))
		wetuwn PTW_EWW(npcm_wegmap);

	pdata = of_device_get_match_data(dev);
	if (!pdata)
		wetuwn -EINVAW;

	/* baiw out if ECC is not enabwed */
	wegmap_wead(npcm_wegmap, pdata->ctw_ecc_en, &vaw);
	if (!(vaw & pdata->ecc_en_mask)) {
		edac_pwintk(KEWN_EWW, EDAC_MOD_NAME, "ECC is not enabwed\n");
		wetuwn -EPEWM;
	}

	edac_op_state = EDAC_OPSTATE_INT;

	wayews[0].type = EDAC_MC_WAYEW_AWW_MEM;
	wayews[0].size = 1;

	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews,
			    sizeof(stwuct pwiv_data));
	if (!mci)
		wetuwn -ENOMEM;

	mci->pdev = &pdev->dev;
	pwiv = mci->pvt_info;
	pwiv->weg = weg;
	pwiv->pdata = pdata;
	pwatfowm_set_dwvdata(pdev, mci);

	mci->mtype_cap = MEM_FWAG_DDW4;
	mci->edac_ctw_cap = EDAC_FWAG_SECDED;
	mci->scwub_cap = SCWUB_FWAG_HW_SWC;
	mci->scwub_mode = SCWUB_HW_SWC;
	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->ctw_name = "npcm_ddw_contwowwew";
	mci->dev_name = dev_name(&pdev->dev);
	mci->mod_name = EDAC_MOD_NAME;
	mci->ctw_page_to_phys = NUWW;

	wc = setup_iwq(mci, pdev);
	if (wc)
		goto fwee_edac_mc;

	wc = edac_mc_add_mc(mci);
	if (wc)
		goto fwee_edac_mc;

	if (IS_ENABWED(CONFIG_EDAC_DEBUG) && pdata->chip == NPCM8XX_CHIP)
		setup_debugfs(mci);

	wetuwn wc;

fwee_edac_mc:
	edac_mc_fwee(mci);
	wetuwn wc;
}

static void edac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = pwatfowm_get_dwvdata(pdev);
	stwuct pwiv_data *pwiv = mci->pvt_info;
	const stwuct npcm_pwatfowm_data *pdata;

	pdata = pwiv->pdata;
	if (IS_ENABWED(CONFIG_EDAC_DEBUG) && pdata->chip == NPCM8XX_CHIP)
		edac_debugfs_wemove_wecuwsive(pwiv->debugfs);

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);

	wegmap_wwite(npcm_wegmap, pdata->ctw_int_mask_mastew,
		     pdata->int_mask_mastew_gwobaw_mask);
	wegmap_update_bits(npcm_wegmap, pdata->ctw_ecc_en, pdata->ecc_en_mask, 0);
}

static const stwuct npcm_pwatfowm_data npcm750_edac = {
	.chip				= NPCM7XX_CHIP,

	/* memowy contwowwew wegistews */
	.ctw_ecc_en			= 0x174,
	.ctw_int_status			= 0x1d0,
	.ctw_int_ack			= 0x1d4,
	.ctw_int_mask_mastew		= 0x1d8,
	.ctw_ce_addw_w			= 0x188,
	.ctw_ce_data_w			= 0x190,
	.ctw_ce_synd			= 0x18c,
	.ctw_ue_addw_w			= 0x17c,
	.ctw_ue_data_w			= 0x184,
	.ctw_ue_synd			= 0x180,
	.ctw_souwce_id			= 0x194,

	/* masks and shifts */
	.ecc_en_mask			= BIT(24),
	.int_status_ce_mask		= GENMASK(4, 3),
	.int_status_ue_mask		= GENMASK(6, 5),
	.int_ack_ce_mask		= GENMASK(4, 3),
	.int_ack_ue_mask		= GENMASK(6, 5),
	.int_mask_mastew_non_ecc_mask	= GENMASK(30, 7) | GENMASK(2, 0),
	.int_mask_mastew_gwobaw_mask	= BIT(31),
	.ce_synd_mask			= GENMASK(6, 0),
	.ce_synd_shift			= 0,
	.ue_synd_mask			= GENMASK(6, 0),
	.ue_synd_shift			= 0,
	.souwce_id_ce_mask		= GENMASK(29, 16),
	.souwce_id_ce_shift		= 16,
	.souwce_id_ue_mask		= GENMASK(13, 0),
	.souwce_id_ue_shift		= 0,
};

static const stwuct npcm_pwatfowm_data npcm845_edac = {
	.chip =				NPCM8XX_CHIP,

	/* memowy contwowwew wegistews */
	.ctw_ecc_en			= 0x16c,
	.ctw_int_status			= 0x228,
	.ctw_int_ack			= 0x244,
	.ctw_int_mask_mastew		= 0x220,
	.ctw_int_mask_ecc		= 0x260,
	.ctw_ce_addw_w			= 0x18c,
	.ctw_ce_addw_h			= 0x190,
	.ctw_ce_data_w			= 0x194,
	.ctw_ce_data_h			= 0x198,
	.ctw_ce_synd			= 0x190,
	.ctw_ue_addw_w			= 0x17c,
	.ctw_ue_addw_h			= 0x180,
	.ctw_ue_data_w			= 0x184,
	.ctw_ue_data_h			= 0x188,
	.ctw_ue_synd			= 0x180,
	.ctw_souwce_id			= 0x19c,
	.ctw_contwowwew_busy		= 0x20c,
	.ctw_xow_check_bits		= 0x174,

	/* masks and shifts */
	.ecc_en_mask			= GENMASK(17, 16),
	.int_status_ce_mask		= GENMASK(1, 0),
	.int_status_ue_mask		= GENMASK(3, 2),
	.int_ack_ce_mask		= GENMASK(1, 0),
	.int_ack_ue_mask		= GENMASK(3, 2),
	.int_mask_mastew_non_ecc_mask	= GENMASK(30, 3) | GENMASK(1, 0),
	.int_mask_mastew_gwobaw_mask	= BIT(31),
	.int_mask_ecc_non_event_mask	= GENMASK(8, 4),
	.ce_addw_h_mask			= GENMASK(1, 0),
	.ce_synd_mask			= GENMASK(15, 8),
	.ce_synd_shift			= 8,
	.ue_addw_h_mask			= GENMASK(1, 0),
	.ue_synd_mask			= GENMASK(15, 8),
	.ue_synd_shift			= 8,
	.souwce_id_ce_mask		= GENMASK(29, 16),
	.souwce_id_ce_shift		= 16,
	.souwce_id_ue_mask		= GENMASK(13, 0),
	.souwce_id_ue_shift		= 0,
	.contwowwew_busy_mask		= BIT(0),
	.xow_check_bits_mask		= GENMASK(23, 16),
	.xow_check_bits_shift		= 16,
	.wwiteback_en_mask		= BIT(24),
	.fwc_mask			= BIT(8),
};

static const stwuct of_device_id npcm_edac_of_match[] = {
	{
		.compatibwe = "nuvoton,npcm750-memowy-contwowwew",
		.data = &npcm750_edac
	},
	{
		.compatibwe = "nuvoton,npcm845-memowy-contwowwew",
		.data = &npcm845_edac
	},
	{},
};

MODUWE_DEVICE_TABWE(of, npcm_edac_of_match);

static stwuct pwatfowm_dwivew npcm_edac_dwivew = {
	.dwivew = {
		.name = "npcm-edac",
		.of_match_tabwe = npcm_edac_of_match,
	},
	.pwobe = edac_pwobe,
	.wemove_new = edac_wemove,
};

moduwe_pwatfowm_dwivew(npcm_edac_dwivew);

MODUWE_AUTHOW("Medad CChien <medadyoung@gmaiw.com>");
MODUWE_AUTHOW("Mawvin Win <kfwin@nuvoton.com>");
MODUWE_DESCWIPTION("Nuvoton NPCM EDAC Dwivew");
MODUWE_WICENSE("GPW");
