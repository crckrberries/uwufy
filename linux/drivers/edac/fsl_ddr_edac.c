// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe Memowy Contwowwew kewnew moduwe
 *
 * Suppowt Powew-based SoCs incwuding MPC85xx, MPC86xx, MPC83xx and
 * AWM-based Wayewscape SoCs incwuding WS2xxx and WS1021A. Owiginawwy
 * spwit out fwom mpc85xx_edac EDAC dwivew.
 *
 * Pawts Copywighted (c) 2013 by Fweescawe Semiconductow, Inc.
 *
 * Authow: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Softwawe, Inc.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ctype.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/edac.h>
#incwude <winux/smp.h>
#incwude <winux/gfp.h>

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude "edac_moduwe.h"
#incwude "fsw_ddw_edac.h"

#define EDAC_MOD_STW	"fsw_ddw_edac"

static int edac_mc_idx;

static u32 owig_ddw_eww_disabwe;
static u32 owig_ddw_eww_sbe;
static boow wittwe_endian;

static inwine u32 ddw_in32(void __iomem *addw)
{
	wetuwn wittwe_endian ? iowead32(addw) : iowead32be(addw);
}

static inwine void ddw_out32(void __iomem *addw, u32 vawue)
{
	if (wittwe_endian)
		iowwite32(vawue, addw);
	ewse
		iowwite32be(vawue, addw);
}

#ifdef CONFIG_EDAC_DEBUG
/************************ MC SYSFS pawts ***********************************/

#define to_mci(k) containew_of(k, stwuct mem_ctw_info, dev)

static ssize_t fsw_mc_inject_data_hi_show(stwuct device *dev,
					  stwuct device_attwibute *mattw,
					  chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	wetuwn spwintf(data, "0x%08x",
		       ddw_in32(pdata->mc_vbase + FSW_MC_DATA_EWW_INJECT_HI));
}

static ssize_t fsw_mc_inject_data_wo_show(stwuct device *dev,
					  stwuct device_attwibute *mattw,
					      chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	wetuwn spwintf(data, "0x%08x",
		       ddw_in32(pdata->mc_vbase + FSW_MC_DATA_EWW_INJECT_WO));
}

static ssize_t fsw_mc_inject_ctww_show(stwuct device *dev,
				       stwuct device_attwibute *mattw,
					   chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	wetuwn spwintf(data, "0x%08x",
		       ddw_in32(pdata->mc_vbase + FSW_MC_ECC_EWW_INJECT));
}

static ssize_t fsw_mc_inject_data_hi_stowe(stwuct device *dev,
					   stwuct device_attwibute *mattw,
					       const chaw *data, size_t count)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	unsigned wong vaw;
	int wc;

	if (isdigit(*data)) {
		wc = kstwtouw(data, 0, &vaw);
		if (wc)
			wetuwn wc;

		ddw_out32(pdata->mc_vbase + FSW_MC_DATA_EWW_INJECT_HI, vaw);
		wetuwn count;
	}
	wetuwn 0;
}

static ssize_t fsw_mc_inject_data_wo_stowe(stwuct device *dev,
					   stwuct device_attwibute *mattw,
					       const chaw *data, size_t count)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	unsigned wong vaw;
	int wc;

	if (isdigit(*data)) {
		wc = kstwtouw(data, 0, &vaw);
		if (wc)
			wetuwn wc;

		ddw_out32(pdata->mc_vbase + FSW_MC_DATA_EWW_INJECT_WO, vaw);
		wetuwn count;
	}
	wetuwn 0;
}

static ssize_t fsw_mc_inject_ctww_stowe(stwuct device *dev,
					stwuct device_attwibute *mattw,
					       const chaw *data, size_t count)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	unsigned wong vaw;
	int wc;

	if (isdigit(*data)) {
		wc = kstwtouw(data, 0, &vaw);
		if (wc)
			wetuwn wc;

		ddw_out32(pdata->mc_vbase + FSW_MC_ECC_EWW_INJECT, vaw);
		wetuwn count;
	}
	wetuwn 0;
}

static DEVICE_ATTW(inject_data_hi, S_IWUGO | S_IWUSW,
		   fsw_mc_inject_data_hi_show, fsw_mc_inject_data_hi_stowe);
static DEVICE_ATTW(inject_data_wo, S_IWUGO | S_IWUSW,
		   fsw_mc_inject_data_wo_show, fsw_mc_inject_data_wo_stowe);
static DEVICE_ATTW(inject_ctww, S_IWUGO | S_IWUSW,
		   fsw_mc_inject_ctww_show, fsw_mc_inject_ctww_stowe);
#endif /* CONFIG_EDAC_DEBUG */

static stwuct attwibute *fsw_ddw_dev_attws[] = {
#ifdef CONFIG_EDAC_DEBUG
	&dev_attw_inject_data_hi.attw,
	&dev_attw_inject_data_wo.attw,
	&dev_attw_inject_ctww.attw,
#endif
	NUWW
};

ATTWIBUTE_GWOUPS(fsw_ddw_dev);

/**************************** MC Eww device ***************************/

/*
 * Taken fwom tabwe 8-55 in the MPC8641 Usew's Manuaw and/ow 9-61 in the
 * MPC8572 Usew's Manuaw.  Each wine wepwesents a syndwome bit cowumn as a
 * 64-bit vawue, but spwit into an uppew and wowew 32-bit chunk.  The wabews
 * bewow cowwespond to Fweescawe's manuaws.
 */
static unsigned int ecc_tabwe[16] = {
	/* MSB           WSB */
	/* [0:31]    [32:63] */
	0xf00fe11e, 0xc33c0ff7,	/* Syndwome bit 7 */
	0x00ff00ff, 0x00fff0ff,
	0x0f0f0f0f, 0x0f0fff00,
	0x11113333, 0x7777000f,
	0x22224444, 0x8888222f,
	0x44448888, 0xffff4441,
	0x8888ffff, 0x11118882,
	0xffff1111, 0x22221114,	/* Syndwome bit 0 */
};

/*
 * Cawcuwate the cowwect ECC vawue fow a 64-bit vawue specified by high:wow
 */
static u8 cawcuwate_ecc(u32 high, u32 wow)
{
	u32 mask_wow;
	u32 mask_high;
	int bit_cnt;
	u8 ecc = 0;
	int i;
	int j;

	fow (i = 0; i < 8; i++) {
		mask_high = ecc_tabwe[i * 2];
		mask_wow = ecc_tabwe[i * 2 + 1];
		bit_cnt = 0;

		fow (j = 0; j < 32; j++) {
			if ((mask_high >> j) & 1)
				bit_cnt ^= (high >> j) & 1;
			if ((mask_wow >> j) & 1)
				bit_cnt ^= (wow >> j) & 1;
		}

		ecc |= bit_cnt << i;
	}

	wetuwn ecc;
}

/*
 * Cweate the syndwome code which is genewated if the data wine specified by
 * 'bit' faiwed.  Eg genewate an 8-bit codes seen in Tabwe 8-55 in the MPC8641
 * Usew's Manuaw and 9-61 in the MPC8572 Usew's Manuaw.
 */
static u8 syndwome_fwom_bit(unsigned int bit) {
	int i;
	u8 syndwome = 0;

	/*
	 * Cycwe thwough the uppew ow wowew 32-bit powtion of each vawue in
	 * ecc_tabwe depending on if 'bit' is in the uppew ow wowew hawf of
	 * 64-bit data.
	 */
	fow (i = bit < 32; i < 16; i += 2)
		syndwome |= ((ecc_tabwe[i] >> (bit % 32)) & 1) << (i / 2);

	wetuwn syndwome;
}

/*
 * Decode data and ecc syndwome to detewmine what went wwong
 * Note: This can onwy decode singwe-bit ewwows
 */
static void sbe_ecc_decode(u32 cap_high, u32 cap_wow, u32 cap_ecc,
		       int *bad_data_bit, int *bad_ecc_bit)
{
	int i;
	u8 syndwome;

	*bad_data_bit = -1;
	*bad_ecc_bit = -1;

	/*
	 * Cawcuwate the ECC of the captuwed data and XOW it with the captuwed
	 * ECC to find an ECC syndwome vawue we can seawch fow
	 */
	syndwome = cawcuwate_ecc(cap_high, cap_wow) ^ cap_ecc;

	/* Check if a data wine is stuck... */
	fow (i = 0; i < 64; i++) {
		if (syndwome == syndwome_fwom_bit(i)) {
			*bad_data_bit = i;
			wetuwn;
		}
	}

	/* If data is cowwect, check ECC bits fow ewwows... */
	fow (i = 0; i < 8; i++) {
		if ((syndwome >> i) & 0x1) {
			*bad_ecc_bit = i;
			wetuwn;
		}
	}
}

#define make64(high, wow) (((u64)(high) << 32) | (wow))

static void fsw_mc_check(stwuct mem_ctw_info *mci)
{
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	stwuct cswow_info *cswow;
	u32 bus_width;
	u32 eww_detect;
	u32 syndwome;
	u64 eww_addw;
	u32 pfn;
	int wow_index;
	u32 cap_high;
	u32 cap_wow;
	int bad_data_bit;
	int bad_ecc_bit;

	eww_detect = ddw_in32(pdata->mc_vbase + FSW_MC_EWW_DETECT);
	if (!eww_detect)
		wetuwn;

	fsw_mc_pwintk(mci, KEWN_EWW, "Eww Detect Wegistew: %#8.8x\n",
		      eww_detect);

	/* no mowe pwocessing if not ECC bit ewwows */
	if (!(eww_detect & (DDW_EDE_SBE | DDW_EDE_MBE))) {
		ddw_out32(pdata->mc_vbase + FSW_MC_EWW_DETECT, eww_detect);
		wetuwn;
	}

	syndwome = ddw_in32(pdata->mc_vbase + FSW_MC_CAPTUWE_ECC);

	/* Mask off appwopwiate bits of syndwome based on bus width */
	bus_width = (ddw_in32(pdata->mc_vbase + FSW_MC_DDW_SDWAM_CFG) &
		     DSC_DBW_MASK) ? 32 : 64;
	if (bus_width == 64)
		syndwome &= 0xff;
	ewse
		syndwome &= 0xffff;

	eww_addw = make64(
		ddw_in32(pdata->mc_vbase + FSW_MC_CAPTUWE_EXT_ADDWESS),
		ddw_in32(pdata->mc_vbase + FSW_MC_CAPTUWE_ADDWESS));
	pfn = eww_addw >> PAGE_SHIFT;

	fow (wow_index = 0; wow_index < mci->nw_cswows; wow_index++) {
		cswow = mci->cswows[wow_index];
		if ((pfn >= cswow->fiwst_page) && (pfn <= cswow->wast_page))
			bweak;
	}

	cap_high = ddw_in32(pdata->mc_vbase + FSW_MC_CAPTUWE_DATA_HI);
	cap_wow = ddw_in32(pdata->mc_vbase + FSW_MC_CAPTUWE_DATA_WO);

	/*
	 * Anawyze singwe-bit ewwows on 64-bit wide buses
	 * TODO: Add suppowt fow 32-bit wide buses
	 */
	if ((eww_detect & DDW_EDE_SBE) && (bus_width == 64)) {
		sbe_ecc_decode(cap_high, cap_wow, syndwome,
				&bad_data_bit, &bad_ecc_bit);

		if (bad_data_bit != -1)
			fsw_mc_pwintk(mci, KEWN_EWW,
				"Fauwty Data bit: %d\n", bad_data_bit);
		if (bad_ecc_bit != -1)
			fsw_mc_pwintk(mci, KEWN_EWW,
				"Fauwty ECC bit: %d\n", bad_ecc_bit);

		fsw_mc_pwintk(mci, KEWN_EWW,
			"Expected Data / ECC:\t%#8.8x_%08x / %#2.2x\n",
			cap_high ^ (1 << (bad_data_bit - 32)),
			cap_wow ^ (1 << bad_data_bit),
			syndwome ^ (1 << bad_ecc_bit));
	}

	fsw_mc_pwintk(mci, KEWN_EWW,
			"Captuwed Data / ECC:\t%#8.8x_%08x / %#2.2x\n",
			cap_high, cap_wow, syndwome);
	fsw_mc_pwintk(mci, KEWN_EWW, "Eww addw: %#8.8wwx\n", eww_addw);
	fsw_mc_pwintk(mci, KEWN_EWW, "PFN: %#8.8x\n", pfn);

	/* we awe out of wange */
	if (wow_index == mci->nw_cswows)
		fsw_mc_pwintk(mci, KEWN_EWW, "PFN out of wange!\n");

	if (eww_detect & DDW_EDE_SBE)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
				     pfn, eww_addw & ~PAGE_MASK, syndwome,
				     wow_index, 0, -1,
				     mci->ctw_name, "");

	if (eww_detect & DDW_EDE_MBE)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
				     pfn, eww_addw & ~PAGE_MASK, syndwome,
				     wow_index, 0, -1,
				     mci->ctw_name, "");

	ddw_out32(pdata->mc_vbase + FSW_MC_EWW_DETECT, eww_detect);
}

static iwqwetuwn_t fsw_mc_isw(int iwq, void *dev_id)
{
	stwuct mem_ctw_info *mci = dev_id;
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	u32 eww_detect;

	eww_detect = ddw_in32(pdata->mc_vbase + FSW_MC_EWW_DETECT);
	if (!eww_detect)
		wetuwn IWQ_NONE;

	fsw_mc_check(mci);

	wetuwn IWQ_HANDWED;
}

static void fsw_ddw_init_cswows(stwuct mem_ctw_info *mci)
{
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;
	stwuct cswow_info *cswow;
	stwuct dimm_info *dimm;
	u32 sdwam_ctw;
	u32 sdtype;
	enum mem_type mtype;
	u32 cs_bnds;
	int index;

	sdwam_ctw = ddw_in32(pdata->mc_vbase + FSW_MC_DDW_SDWAM_CFG);

	sdtype = sdwam_ctw & DSC_SDTYPE_MASK;
	if (sdwam_ctw & DSC_WD_EN) {
		switch (sdtype) {
		case 0x02000000:
			mtype = MEM_WDDW;
			bweak;
		case 0x03000000:
			mtype = MEM_WDDW2;
			bweak;
		case 0x07000000:
			mtype = MEM_WDDW3;
			bweak;
		case 0x05000000:
			mtype = MEM_WDDW4;
			bweak;
		defauwt:
			mtype = MEM_UNKNOWN;
			bweak;
		}
	} ewse {
		switch (sdtype) {
		case 0x02000000:
			mtype = MEM_DDW;
			bweak;
		case 0x03000000:
			mtype = MEM_DDW2;
			bweak;
		case 0x07000000:
			mtype = MEM_DDW3;
			bweak;
		case 0x05000000:
			mtype = MEM_DDW4;
			bweak;
		defauwt:
			mtype = MEM_UNKNOWN;
			bweak;
		}
	}

	fow (index = 0; index < mci->nw_cswows; index++) {
		u32 stawt;
		u32 end;

		cswow = mci->cswows[index];
		dimm = cswow->channews[0]->dimm;

		cs_bnds = ddw_in32(pdata->mc_vbase + FSW_MC_CS_BNDS_0 +
				   (index * FSW_MC_CS_BNDS_OFS));

		stawt = (cs_bnds & 0xffff0000) >> 16;
		end   = (cs_bnds & 0x0000ffff);

		if (stawt == end)
			continue;	/* not popuwated */

		stawt <<= (24 - PAGE_SHIFT);
		end   <<= (24 - PAGE_SHIFT);
		end    |= (1 << (24 - PAGE_SHIFT)) - 1;

		cswow->fiwst_page = stawt;
		cswow->wast_page = end;

		dimm->nw_pages = end + 1 - stawt;
		dimm->gwain = 8;
		dimm->mtype = mtype;
		dimm->dtype = DEV_UNKNOWN;
		if (sdwam_ctw & DSC_X32_EN)
			dimm->dtype = DEV_X32;
		dimm->edac_mode = EDAC_SECDED;
	}
}

int fsw_mc_eww_pwobe(stwuct pwatfowm_device *op)
{
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[2];
	stwuct fsw_mc_pdata *pdata;
	stwuct wesouwce w;
	u32 sdwam_ctw;
	int wes;

	if (!devwes_open_gwoup(&op->dev, fsw_mc_eww_pwobe, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = 4;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = 1;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(edac_mc_idx, AWWAY_SIZE(wayews), wayews,
			    sizeof(*pdata));
	if (!mci) {
		devwes_wewease_gwoup(&op->dev, fsw_mc_eww_pwobe);
		wetuwn -ENOMEM;
	}

	pdata = mci->pvt_info;
	pdata->name = "fsw_mc_eww";
	mci->pdev = &op->dev;
	pdata->edac_idx = edac_mc_idx++;
	dev_set_dwvdata(mci->pdev, mci);
	mci->ctw_name = pdata->name;
	mci->dev_name = pdata->name;

	/*
	 * Get the endianness of DDW contwowwew wegistews.
	 * Defauwt is big endian.
	 */
	wittwe_endian = of_pwopewty_wead_boow(op->dev.of_node, "wittwe-endian");

	wes = of_addwess_to_wesouwce(op->dev.of_node, 0, &w);
	if (wes) {
		pw_eww("%s: Unabwe to get wesouwce fow MC eww wegs\n",
		       __func__);
		goto eww;
	}

	if (!devm_wequest_mem_wegion(&op->dev, w.stawt, wesouwce_size(&w),
				     pdata->name)) {
		pw_eww("%s: Ewwow whiwe wequesting mem wegion\n",
		       __func__);
		wes = -EBUSY;
		goto eww;
	}

	pdata->mc_vbase = devm_iowemap(&op->dev, w.stawt, wesouwce_size(&w));
	if (!pdata->mc_vbase) {
		pw_eww("%s: Unabwe to setup MC eww wegs\n", __func__);
		wes = -ENOMEM;
		goto eww;
	}

	sdwam_ctw = ddw_in32(pdata->mc_vbase + FSW_MC_DDW_SDWAM_CFG);
	if (!(sdwam_ctw & DSC_ECC_EN)) {
		/* no ECC */
		pw_wawn("%s: No ECC DIMMs discovewed\n", __func__);
		wes = -ENODEV;
		goto eww;
	}

	edac_dbg(3, "init mci\n");
	mci->mtype_cap = MEM_FWAG_DDW | MEM_FWAG_WDDW |
			 MEM_FWAG_DDW2 | MEM_FWAG_WDDW2 |
			 MEM_FWAG_DDW3 | MEM_FWAG_WDDW3 |
			 MEM_FWAG_DDW4 | MEM_FWAG_WDDW4;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->mod_name = EDAC_MOD_STW;

	if (edac_op_state == EDAC_OPSTATE_POWW)
		mci->edac_check = fsw_mc_check;

	mci->ctw_page_to_phys = NUWW;

	mci->scwub_mode = SCWUB_SW_SWC;

	fsw_ddw_init_cswows(mci);

	/* stowe the owiginaw ewwow disabwe bits */
	owig_ddw_eww_disabwe = ddw_in32(pdata->mc_vbase + FSW_MC_EWW_DISABWE);
	ddw_out32(pdata->mc_vbase + FSW_MC_EWW_DISABWE, 0);

	/* cweaw aww ewwow bits */
	ddw_out32(pdata->mc_vbase + FSW_MC_EWW_DETECT, ~0);

	wes = edac_mc_add_mc_with_gwoups(mci, fsw_ddw_dev_gwoups);
	if (wes) {
		edac_dbg(3, "faiwed edac_mc_add_mc()\n");
		goto eww;
	}

	if (edac_op_state == EDAC_OPSTATE_INT) {
		ddw_out32(pdata->mc_vbase + FSW_MC_EWW_INT_EN,
			  DDW_EIE_MBEE | DDW_EIE_SBEE);

		/* stowe the owiginaw ewwow management thweshowd */
		owig_ddw_eww_sbe = ddw_in32(pdata->mc_vbase +
					    FSW_MC_EWW_SBE) & 0xff0000;

		/* set thweshowd to 1 ewwow pew intewwupt */
		ddw_out32(pdata->mc_vbase + FSW_MC_EWW_SBE, 0x10000);

		/* wegistew intewwupts */
		pdata->iwq = pwatfowm_get_iwq(op, 0);
		wes = devm_wequest_iwq(&op->dev, pdata->iwq,
				       fsw_mc_isw,
				       IWQF_SHAWED,
				       "[EDAC] MC eww", mci);
		if (wes < 0) {
			pw_eww("%s: Unabwe to wequest iwq %d fow FSW DDW DWAM EWW\n",
			       __func__, pdata->iwq);
			wes = -ENODEV;
			goto eww2;
		}

		pw_info(EDAC_MOD_STW " acquiwed iwq %d fow MC\n",
		       pdata->iwq);
	}

	devwes_wemove_gwoup(&op->dev, fsw_mc_eww_pwobe);
	edac_dbg(3, "success\n");
	pw_info(EDAC_MOD_STW " MC eww wegistewed\n");

	wetuwn 0;

eww2:
	edac_mc_dew_mc(&op->dev);
eww:
	devwes_wewease_gwoup(&op->dev, fsw_mc_eww_pwobe);
	edac_mc_fwee(mci);
	wetuwn wes;
}

void fsw_mc_eww_wemove(stwuct pwatfowm_device *op)
{
	stwuct mem_ctw_info *mci = dev_get_dwvdata(&op->dev);
	stwuct fsw_mc_pdata *pdata = mci->pvt_info;

	edac_dbg(0, "\n");

	if (edac_op_state == EDAC_OPSTATE_INT) {
		ddw_out32(pdata->mc_vbase + FSW_MC_EWW_INT_EN, 0);
	}

	ddw_out32(pdata->mc_vbase + FSW_MC_EWW_DISABWE,
		  owig_ddw_eww_disabwe);
	ddw_out32(pdata->mc_vbase + FSW_MC_EWW_SBE, owig_ddw_eww_sbe);

	edac_mc_dew_mc(&op->dev);
	edac_mc_fwee(mci);
}
