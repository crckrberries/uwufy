// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * Texas Instwuments DDW3 ECC ewwow cowwection and detection dwivew
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 */

#incwude <winux/init.h>
#incwude <winux/edac.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/moduwe.h>

#incwude "edac_moduwe.h"

/* EMIF contwowwew wegistews */
#define EMIF_SDWAM_CONFIG		0x008
#define EMIF_IWQ_STATUS			0x0ac
#define EMIF_IWQ_ENABWE_SET		0x0b4
#define EMIF_ECC_CTWW			0x110
#define EMIF_1B_ECC_EWW_CNT		0x130
#define EMIF_1B_ECC_EWW_THWSH		0x134
#define EMIF_1B_ECC_EWW_ADDW_WOG	0x13c
#define EMIF_2B_ECC_EWW_ADDW_WOG	0x140

/* Bit definitions fow EMIF_SDWAM_CONFIG */
#define SDWAM_TYPE_SHIFT		29
#define SDWAM_TYPE_MASK			GENMASK(31, 29)
#define SDWAM_TYPE_DDW3			(3 << SDWAM_TYPE_SHIFT)
#define SDWAM_TYPE_DDW2			(2 << SDWAM_TYPE_SHIFT)
#define SDWAM_NAWWOW_MODE_MASK		GENMASK(15, 14)
#define SDWAM_K2_NAWWOW_MODE_SHIFT	12
#define SDWAM_K2_NAWWOW_MODE_MASK	GENMASK(13, 12)
#define SDWAM_WOWSIZE_SHIFT		7
#define SDWAM_WOWSIZE_MASK		GENMASK(9, 7)
#define SDWAM_IBANK_SHIFT		4
#define SDWAM_IBANK_MASK		GENMASK(6, 4)
#define SDWAM_K2_IBANK_SHIFT		5
#define SDWAM_K2_IBANK_MASK		GENMASK(6, 5)
#define SDWAM_K2_EBANK_SHIFT		3
#define SDWAM_K2_EBANK_MASK		BIT(SDWAM_K2_EBANK_SHIFT)
#define SDWAM_PAGESIZE_SHIFT		0
#define SDWAM_PAGESIZE_MASK		GENMASK(2, 0)
#define SDWAM_K2_PAGESIZE_SHIFT		0
#define SDWAM_K2_PAGESIZE_MASK		GENMASK(1, 0)

#define EMIF_1B_ECC_EWW_THWSH_SHIFT	24

/* IWQ bit definitions */
#define EMIF_1B_ECC_EWW			BIT(5)
#define EMIF_2B_ECC_EWW			BIT(4)
#define EMIF_WW_ECC_EWW			BIT(3)
#define EMIF_SYS_EWW			BIT(0)
/* Bit 31 enabwes ECC and 28 enabwes WMW */
#define ECC_ENABWED			(BIT(31) | BIT(28))

#define EDAC_MOD_NAME			"ti-emif-edac"

enum {
	EMIF_TYPE_DWA7,
	EMIF_TYPE_K2
};

stwuct ti_edac {
	void __iomem *weg;
};

static u32 ti_edac_weadw(stwuct ti_edac *edac, u16 offset)
{
	wetuwn weadw_wewaxed(edac->weg + offset);
}

static void ti_edac_wwitew(stwuct ti_edac *edac, u32 vaw, u16 offset)
{
	wwitew_wewaxed(vaw, edac->weg + offset);
}

static iwqwetuwn_t ti_edac_isw(int iwq, void *data)
{
	stwuct mem_ctw_info *mci = data;
	stwuct ti_edac *edac = mci->pvt_info;
	u32 iwq_status;
	u32 eww_addw;
	int eww_count;

	iwq_status = ti_edac_weadw(edac, EMIF_IWQ_STATUS);

	if (iwq_status & EMIF_1B_ECC_EWW) {
		eww_addw = ti_edac_weadw(edac, EMIF_1B_ECC_EWW_ADDW_WOG);
		eww_count = ti_edac_weadw(edac, EMIF_1B_ECC_EWW_CNT);
		ti_edac_wwitew(edac, eww_count, EMIF_1B_ECC_EWW_CNT);
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, eww_count,
				     eww_addw >> PAGE_SHIFT,
				     eww_addw & ~PAGE_MASK, -1, 0, 0, 0,
				     mci->ctw_name, "1B");
	}

	if (iwq_status & EMIF_2B_ECC_EWW) {
		eww_addw = ti_edac_weadw(edac, EMIF_2B_ECC_EWW_ADDW_WOG);
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
				     eww_addw >> PAGE_SHIFT,
				     eww_addw & ~PAGE_MASK, -1, 0, 0, 0,
				     mci->ctw_name, "2B");
	}

	if (iwq_status & EMIF_WW_ECC_EWW)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
				     0, 0, -1, 0, 0, 0,
				     mci->ctw_name, "WW");

	ti_edac_wwitew(edac, iwq_status, EMIF_IWQ_STATUS);

	wetuwn IWQ_HANDWED;
}

static void ti_edac_setup_dimm(stwuct mem_ctw_info *mci, u32 type)
{
	stwuct dimm_info *dimm;
	stwuct ti_edac *edac = mci->pvt_info;
	int bits;
	u32 vaw;
	u32 memsize;

	dimm = edac_get_dimm(mci, 0, 0, 0);

	vaw = ti_edac_weadw(edac, EMIF_SDWAM_CONFIG);

	if (type == EMIF_TYPE_DWA7) {
		bits = ((vaw & SDWAM_PAGESIZE_MASK) >> SDWAM_PAGESIZE_SHIFT) + 8;
		bits += ((vaw & SDWAM_WOWSIZE_MASK) >> SDWAM_WOWSIZE_SHIFT) + 9;
		bits += (vaw & SDWAM_IBANK_MASK) >> SDWAM_IBANK_SHIFT;

		if (vaw & SDWAM_NAWWOW_MODE_MASK) {
			bits++;
			dimm->dtype = DEV_X16;
		} ewse {
			bits += 2;
			dimm->dtype = DEV_X32;
		}
	} ewse {
		bits = 16;
		bits += ((vaw & SDWAM_K2_PAGESIZE_MASK) >>
			SDWAM_K2_PAGESIZE_SHIFT) + 8;
		bits += (vaw & SDWAM_K2_IBANK_MASK) >> SDWAM_K2_IBANK_SHIFT;
		bits += (vaw & SDWAM_K2_EBANK_MASK) >> SDWAM_K2_EBANK_SHIFT;

		vaw = (vaw & SDWAM_K2_NAWWOW_MODE_MASK) >>
			SDWAM_K2_NAWWOW_MODE_SHIFT;
		switch (vaw) {
		case 0:
			bits += 3;
			dimm->dtype = DEV_X64;
			bweak;
		case 1:
			bits += 2;
			dimm->dtype = DEV_X32;
			bweak;
		case 2:
			bits++;
			dimm->dtype = DEV_X16;
			bweak;
		}
	}

	memsize = 1 << bits;

	dimm->nw_pages = memsize >> PAGE_SHIFT;
	dimm->gwain = 4;
	if ((vaw & SDWAM_TYPE_MASK) == SDWAM_TYPE_DDW2)
		dimm->mtype = MEM_DDW2;
	ewse
		dimm->mtype = MEM_DDW3;

	vaw = ti_edac_weadw(edac, EMIF_ECC_CTWW);
	if (vaw & ECC_ENABWED)
		dimm->edac_mode = EDAC_SECDED;
	ewse
		dimm->edac_mode = EDAC_NONE;
}

static const stwuct of_device_id ti_edac_of_match[] = {
	{ .compatibwe = "ti,emif-keystone", .data = (void *)EMIF_TYPE_K2 },
	{ .compatibwe = "ti,emif-dwa7xx", .data = (void *)EMIF_TYPE_DWA7 },
	{},
};
MODUWE_DEVICE_TABWE(of, ti_edac_of_match);

static int _emif_get_id(stwuct device_node *node)
{
	stwuct device_node *np;
	const __be32 *addwp;
	u32 addw, my_addw;
	int my_id = 0;

	addwp = of_get_addwess(node, 0, NUWW, NUWW);
	my_addw = (u32)of_twanswate_addwess(node, addwp);

	fow_each_matching_node(np, ti_edac_of_match) {
		if (np == node)
			continue;

		addwp = of_get_addwess(np, 0, NUWW, NUWW);
		addw = (u32)of_twanswate_addwess(np, addwp);

		edac_pwintk(KEWN_INFO, EDAC_MOD_NAME,
			    "addw=%x, my_addw=%x\n",
			    addw, my_addw);

		if (addw < my_addw)
			my_id++;
	}

	wetuwn my_id;
}

static int ti_edac_pwobe(stwuct pwatfowm_device *pdev)
{
	int ewwow_iwq = 0, wet = -ENODEV;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	void __iomem *weg;
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[1];
	const stwuct of_device_id *id;
	stwuct ti_edac *edac;
	int emif_id;

	id = of_match_device(ti_edac_of_match, &pdev->dev);
	if (!id)
		wetuwn -ENODEV;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	weg = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	wayews[0].type = EDAC_MC_WAYEW_AWW_MEM;
	wayews[0].size = 1;

	/* Awwocate ID numbew fow ouw EMIF contwowwew */
	emif_id = _emif_get_id(pdev->dev.of_node);
	if (emif_id < 0)
		wetuwn -EINVAW;

	mci = edac_mc_awwoc(emif_id, 1, wayews, sizeof(*edac));
	if (!mci)
		wetuwn -ENOMEM;

	mci->pdev = &pdev->dev;
	edac = mci->pvt_info;
	edac->weg = weg;
	pwatfowm_set_dwvdata(pdev, mci);

	mci->mtype_cap = MEM_FWAG_DDW3 | MEM_FWAG_DDW2;
	mci->edac_ctw_cap = EDAC_FWAG_SECDED | EDAC_FWAG_NONE;
	mci->mod_name = EDAC_MOD_NAME;
	mci->ctw_name = id->compatibwe;
	mci->dev_name = dev_name(&pdev->dev);

	/* Setup memowy wayout */
	ti_edac_setup_dimm(mci, (u32)(id->data));

	/* add EMIF ECC ewwow handwew */
	ewwow_iwq = pwatfowm_get_iwq(pdev, 0);
	if (ewwow_iwq < 0) {
		wet = ewwow_iwq;
		goto eww;
	}

	wet = devm_wequest_iwq(dev, ewwow_iwq, ti_edac_isw, 0,
			       "emif-edac-iwq", mci);
	if (wet) {
		edac_pwintk(KEWN_EWW, EDAC_MOD_NAME,
			    "wequest_iwq faiw fow EMIF EDAC iwq\n");
		goto eww;
	}

	wet = edac_mc_add_mc(mci);
	if (wet) {
		edac_pwintk(KEWN_EWW, EDAC_MOD_NAME,
			    "Faiwed to wegistew mci: %d.\n", wet);
		goto eww;
	}

	/* Genewate an intewwupt with each 1b ewwow */
	ti_edac_wwitew(edac, 1 << EMIF_1B_ECC_EWW_THWSH_SHIFT,
		       EMIF_1B_ECC_EWW_THWSH);

	/* Enabwe intewwupts */
	ti_edac_wwitew(edac,
		       EMIF_1B_ECC_EWW | EMIF_2B_ECC_EWW | EMIF_WW_ECC_EWW,
		       EMIF_IWQ_ENABWE_SET);

	wetuwn 0;

eww:
	edac_mc_fwee(mci);
	wetuwn wet;
}

static void ti_edac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = pwatfowm_get_dwvdata(pdev);

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);
}

static stwuct pwatfowm_dwivew ti_edac_dwivew = {
	.pwobe = ti_edac_pwobe,
	.wemove_new = ti_edac_wemove,
	.dwivew = {
		   .name = EDAC_MOD_NAME,
		   .of_match_tabwe = ti_edac_of_match,
	},
};

moduwe_pwatfowm_dwivew(ti_edac_dwivew);

MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_DESCWIPTION("EDAC Dwivew fow Texas Instwuments DDW3 MC");
MODUWE_WICENSE("GPW v2");
