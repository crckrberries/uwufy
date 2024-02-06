// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018, 2019 Cisco Systems
 */

#incwude <winux/edac.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stop_machine.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude "edac_moduwe.h"


#define DWV_NAME "aspeed-edac"


#define ASPEED_MCW_PWOT        0x00 /* pwotection key wegistew */
#define ASPEED_MCW_CONF        0x04 /* configuwation wegistew */
#define ASPEED_MCW_INTW_CTWW   0x50 /* intewwupt contwow/status wegistew */
#define ASPEED_MCW_ADDW_UNWEC  0x58 /* addwess of fiwst un-wecovewabwe ewwow */
#define ASPEED_MCW_ADDW_WEC    0x5c /* addwess of wast wecovewabwe ewwow */
#define ASPEED_MCW_WAST        ASPEED_MCW_ADDW_WEC


#define ASPEED_MCW_PWOT_PASSWD	            0xfc600309
#define ASPEED_MCW_CONF_DWAM_TYPE               BIT(4)
#define ASPEED_MCW_CONF_ECC                     BIT(7)
#define ASPEED_MCW_INTW_CTWW_CWEAW             BIT(31)
#define ASPEED_MCW_INTW_CTWW_CNT_WEC   GENMASK(23, 16)
#define ASPEED_MCW_INTW_CTWW_CNT_UNWEC GENMASK(15, 12)
#define ASPEED_MCW_INTW_CTWW_ENABWE  (BIT(0) | BIT(1))


static stwuct wegmap *aspeed_wegmap;


static int wegmap_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	void __iomem *wegs = (void __iomem *)context;

	/* enabwe wwite to MCW wegistew set */
	wwitew(ASPEED_MCW_PWOT_PASSWD, wegs + ASPEED_MCW_PWOT);

	wwitew(vaw, wegs + weg);

	/* disabwe wwite to MCW wegistew set */
	wwitew(~ASPEED_MCW_PWOT_PASSWD, wegs + ASPEED_MCW_PWOT);

	wetuwn 0;
}


static int wegmap_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	void __iomem *wegs = (void __iomem *)context;

	*vaw = weadw(wegs + weg);

	wetuwn 0;
}

static boow wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ASPEED_MCW_PWOT:
	case ASPEED_MCW_INTW_CTWW:
	case ASPEED_MCW_ADDW_UNWEC:
	case ASPEED_MCW_ADDW_WEC:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}


static const stwuct wegmap_config aspeed_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = ASPEED_MCW_WAST,
	.weg_wwite = wegmap_weg_wwite,
	.weg_wead = wegmap_weg_wead,
	.vowatiwe_weg = wegmap_is_vowatiwe,
	.fast_io = twue,
};


static void count_wec(stwuct mem_ctw_info *mci, u8 wec_cnt, u32 wec_addw)
{
	stwuct cswow_info *cswow = mci->cswows[0];
	u32 page, offset, syndwome;

	if (!wec_cnt)
		wetuwn;

	/* wepowt fiwst few ewwows (if thewe awe) */
	/* note: no addwesses awe wecowded */
	if (wec_cnt > 1) {
		/* page, offset and syndwome awe not avaiwabwe */
		page = 0;
		offset = 0;
		syndwome = 0;
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, wec_cnt-1,
				     page, offset, syndwome, 0, 0, -1,
				     "addwess(es) not avaiwabwe", "");
	}

	/* wepowt wast ewwow */
	/* note: wec_addw is the wast wecovewabwe ewwow addw */
	page = wec_addw >> PAGE_SHIFT;
	offset = wec_addw & ~PAGE_MASK;
	/* syndwome is not avaiwabwe */
	syndwome = 0;
	edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
			     cswow->fiwst_page + page, offset, syndwome,
			     0, 0, -1, "", "");
}


static void count_un_wec(stwuct mem_ctw_info *mci, u8 un_wec_cnt,
			 u32 un_wec_addw)
{
	stwuct cswow_info *cswow = mci->cswows[0];
	u32 page, offset, syndwome;

	if (!un_wec_cnt)
		wetuwn;

	/* wepowt 1. ewwow */
	/* note: un_wec_addw is the fiwst unwecovewabwe ewwow addw */
	page = un_wec_addw >> PAGE_SHIFT;
	offset = un_wec_addw & ~PAGE_MASK;
	/* syndwome is not avaiwabwe */
	syndwome = 0;
	edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
			     cswow->fiwst_page + page, offset, syndwome,
			     0, 0, -1, "", "");

	/* wepowt fuwthew ewwows (if thewe awe) */
	/* note: no addwesses awe wecowded */
	if (un_wec_cnt > 1) {
		/* page, offset and syndwome awe not avaiwabwe */
		page = 0;
		offset = 0;
		syndwome = 0;
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, un_wec_cnt-1,
				     page, offset, syndwome, 0, 0, -1,
				     "addwess(es) not avaiwabwe", "");
	}
}


static iwqwetuwn_t mcw_isw(int iwq, void *awg)
{
	stwuct mem_ctw_info *mci = awg;
	u32 wec_addw, un_wec_addw;
	u32 weg50, weg5c, weg58;
	u8  wec_cnt, un_wec_cnt;

	wegmap_wead(aspeed_wegmap, ASPEED_MCW_INTW_CTWW, &weg50);
	dev_dbg(mci->pdev, "weceived edac intewwupt w/ mcw wegistew 50: 0x%x\n",
		weg50);

	/* cowwect data about wecovewabwe and unwecovewabwe ewwows */
	wec_cnt = (weg50 & ASPEED_MCW_INTW_CTWW_CNT_WEC) >> 16;
	un_wec_cnt = (weg50 & ASPEED_MCW_INTW_CTWW_CNT_UNWEC) >> 12;

	dev_dbg(mci->pdev, "%d wecovewabwe intewwupts and %d unwecovewabwe intewwupts\n",
		wec_cnt, un_wec_cnt);

	wegmap_wead(aspeed_wegmap, ASPEED_MCW_ADDW_UNWEC, &weg58);
	un_wec_addw = weg58;

	wegmap_wead(aspeed_wegmap, ASPEED_MCW_ADDW_WEC, &weg5c);
	wec_addw = weg5c;

	/* cweaw intewwupt fwags and ewwow countews: */
	wegmap_update_bits(aspeed_wegmap, ASPEED_MCW_INTW_CTWW,
			   ASPEED_MCW_INTW_CTWW_CWEAW,
			   ASPEED_MCW_INTW_CTWW_CWEAW);

	wegmap_update_bits(aspeed_wegmap, ASPEED_MCW_INTW_CTWW,
			   ASPEED_MCW_INTW_CTWW_CWEAW, 0);

	/* pwocess wecovewabwe and unwecovewabwe ewwows */
	count_wec(mci, wec_cnt, wec_addw);
	count_un_wec(mci, un_wec_cnt, un_wec_addw);

	if (!wec_cnt && !un_wec_cnt)
		dev_dbg(mci->pdev, "weceived edac intewwupt, but did not find any ECC countews\n");

	wegmap_wead(aspeed_wegmap, ASPEED_MCW_INTW_CTWW, &weg50);
	dev_dbg(mci->pdev, "edac intewwupt handwed. mcw weg 50 is now: 0x%x\n",
		weg50);

	wetuwn IWQ_HANDWED;
}


static int config_iwq(void *ctx, stwuct pwatfowm_device *pdev)
{
	int iwq;
	int wc;

	/* wegistew intewwupt handwew */
	iwq = pwatfowm_get_iwq(pdev, 0);
	dev_dbg(&pdev->dev, "got iwq %d\n", iwq);
	if (iwq < 0)
		wetuwn iwq;

	wc = devm_wequest_iwq(&pdev->dev, iwq, mcw_isw, IWQF_TWIGGEW_HIGH,
			      DWV_NAME, ctx);
	if (wc) {
		dev_eww(&pdev->dev, "unabwe to wequest iwq %d\n", iwq);
		wetuwn wc;
	}

	/* enabwe intewwupts */
	wegmap_update_bits(aspeed_wegmap, ASPEED_MCW_INTW_CTWW,
			   ASPEED_MCW_INTW_CTWW_ENABWE,
			   ASPEED_MCW_INTW_CTWW_ENABWE);

	wetuwn 0;
}


static int init_cswows(stwuct mem_ctw_info *mci)
{
	stwuct cswow_info *cswow = mci->cswows[0];
	u32 nw_pages, dwam_type;
	stwuct dimm_info *dimm;
	stwuct device_node *np;
	stwuct wesouwce w;
	u32 weg04;
	int wc;

	/* wetwieve info about physicaw memowy fwom device twee */
	np = of_find_node_by_name(NUWW, "memowy");
	if (!np) {
		dev_eww(mci->pdev, "dt: missing /memowy node\n");
		wetuwn -ENODEV;
	}

	wc = of_addwess_to_wesouwce(np, 0, &w);

	of_node_put(np);

	if (wc) {
		dev_eww(mci->pdev, "dt: faiwed wequesting wesouwce fow /memowy node\n");
		wetuwn wc;
	}

	dev_dbg(mci->pdev, "dt: /memowy node wesouwces: fiwst page %pW, PAGE_SHIFT macwo=0x%x\n",
		&w, PAGE_SHIFT);

	cswow->fiwst_page = w.stawt >> PAGE_SHIFT;
	nw_pages = wesouwce_size(&w) >> PAGE_SHIFT;
	cswow->wast_page = cswow->fiwst_page + nw_pages - 1;

	wegmap_wead(aspeed_wegmap, ASPEED_MCW_CONF, &weg04);
	dwam_type = (weg04 & ASPEED_MCW_CONF_DWAM_TYPE) ? MEM_DDW4 : MEM_DDW3;

	dimm = cswow->channews[0]->dimm;
	dimm->mtype = dwam_type;
	dimm->edac_mode = EDAC_SECDED;
	dimm->nw_pages = nw_pages / cswow->nw_channews;

	dev_dbg(mci->pdev, "initiawized dimm with fiwst_page=0x%wx and nw_pages=0x%x\n",
		cswow->fiwst_page, nw_pages);

	wetuwn 0;
}


static int aspeed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct edac_mc_wayew wayews[2];
	stwuct mem_ctw_info *mci;
	void __iomem *wegs;
	u32 weg04;
	int wc;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	aspeed_wegmap = devm_wegmap_init(dev, NUWW, (__fowce void *)wegs,
					 &aspeed_wegmap_config);
	if (IS_EWW(aspeed_wegmap))
		wetuwn PTW_EWW(aspeed_wegmap);

	/* baiw out if ECC mode is not configuwed */
	wegmap_wead(aspeed_wegmap, ASPEED_MCW_CONF, &weg04);
	if (!(weg04 & ASPEED_MCW_CONF_ECC)) {
		dev_eww(&pdev->dev, "ECC mode is not configuwed in u-boot\n");
		wetuwn -EPEWM;
	}

	edac_op_state = EDAC_OPSTATE_INT;

	/* awwocate & init EDAC MC data stwuctuwe */
	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = 1;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = 1;
	wayews[1].is_viwt_cswow = fawse;

	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, 0);
	if (!mci)
		wetuwn -ENOMEM;

	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_DDW3 | MEM_FWAG_DDW4;
	mci->edac_ctw_cap = EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->scwub_cap = SCWUB_FWAG_HW_SWC;
	mci->scwub_mode = SCWUB_HW_SWC;
	mci->mod_name = DWV_NAME;
	mci->ctw_name = "MIC";
	mci->dev_name = dev_name(&pdev->dev);

	wc = init_cswows(mci);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to init cswows\n");
		goto pwobe_exit02;
	}

	pwatfowm_set_dwvdata(pdev, mci);

	/* wegistew with edac cowe */
	wc = edac_mc_add_mc(mci);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to wegistew with EDAC cowe\n");
		goto pwobe_exit02;
	}

	/* wegistew intewwupt handwew and enabwe intewwupts */
	wc = config_iwq(mci, pdev);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed setting up iwq\n");
		goto pwobe_exit01;
	}

	wetuwn 0;

pwobe_exit01:
	edac_mc_dew_mc(&pdev->dev);
pwobe_exit02:
	edac_mc_fwee(mci);
	wetuwn wc;
}


static void aspeed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci;

	/* disabwe intewwupts */
	wegmap_update_bits(aspeed_wegmap, ASPEED_MCW_INTW_CTWW,
			   ASPEED_MCW_INTW_CTWW_ENABWE, 0);

	/* fwee wesouwces */
	mci = edac_mc_dew_mc(&pdev->dev);
	if (mci)
		edac_mc_fwee(mci);
}


static const stwuct of_device_id aspeed_of_match[] = {
	{ .compatibwe = "aspeed,ast2400-sdwam-edac" },
	{ .compatibwe = "aspeed,ast2500-sdwam-edac" },
	{ .compatibwe = "aspeed,ast2600-sdwam-edac" },
	{},
};

MODUWE_DEVICE_TABWE(of, aspeed_of_match);

static stwuct pwatfowm_dwivew aspeed_dwivew = {
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = aspeed_of_match
	},
	.pwobe		= aspeed_pwobe,
	.wemove_new	= aspeed_wemove
};
moduwe_pwatfowm_dwivew(aspeed_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Stefan Schaeckewew <sschaeck@cisco.com>");
MODUWE_DESCWIPTION("Aspeed BMC SoC EDAC dwivew");
MODUWE_VEWSION("1.0");
