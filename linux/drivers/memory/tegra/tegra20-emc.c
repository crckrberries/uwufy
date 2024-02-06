// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tegwa20 Extewnaw Memowy Contwowwew dwivew
 *
 * Authow: Dmitwy Osipenko <digetx@gmaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/tegwa.h>
#incwude <winux/debugfs.h>
#incwude <winux/devfweq.h>
#incwude <winux/eww.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/types.h>

#incwude <soc/tegwa/common.h>
#incwude <soc/tegwa/fuse.h>

#incwude "../jedec_ddw.h"
#incwude "../of_memowy.h"

#incwude "mc.h"

#define EMC_INTSTATUS				0x000
#define EMC_INTMASK				0x004
#define EMC_DBG					0x008
#define EMC_ADW_CFG_0				0x010
#define EMC_TIMING_CONTWOW			0x028
#define EMC_WC					0x02c
#define EMC_WFC					0x030
#define EMC_WAS					0x034
#define EMC_WP					0x038
#define EMC_W2W					0x03c
#define EMC_W2W					0x040
#define EMC_W2P					0x044
#define EMC_W2P					0x048
#define EMC_WD_WCD				0x04c
#define EMC_WW_WCD				0x050
#define EMC_WWD					0x054
#define EMC_WEXT				0x058
#define EMC_WDV					0x05c
#define EMC_QUSE				0x060
#define EMC_QWST				0x064
#define EMC_QSAFE				0x068
#define EMC_WDV					0x06c
#define EMC_WEFWESH				0x070
#define EMC_BUWST_WEFWESH_NUM			0x074
#define EMC_PDEX2WW				0x078
#define EMC_PDEX2WD				0x07c
#define EMC_PCHG2PDEN				0x080
#define EMC_ACT2PDEN				0x084
#define EMC_AW2PDEN				0x088
#define EMC_WW2PDEN				0x08c
#define EMC_TXSW				0x090
#define EMC_TCKE				0x094
#define EMC_TFAW				0x098
#define EMC_TWPAB				0x09c
#define EMC_TCWKSTABWE				0x0a0
#define EMC_TCWKSTOP				0x0a4
#define EMC_TWEFBW				0x0a8
#define EMC_QUSE_EXTWA				0x0ac
#define EMC_ODT_WWITE				0x0b0
#define EMC_ODT_WEAD				0x0b4
#define EMC_MWW					0x0ec
#define EMC_FBIO_CFG5				0x104
#define EMC_FBIO_CFG6				0x114
#define EMC_STAT_CONTWOW			0x160
#define EMC_STAT_WWMC_CONTWOW			0x178
#define EMC_STAT_PWW_CWOCK_WIMIT		0x198
#define EMC_STAT_PWW_CWOCKS			0x19c
#define EMC_STAT_PWW_COUNT			0x1a0
#define EMC_AUTO_CAW_INTEWVAW			0x2a8
#define EMC_CFG_2				0x2b8
#define EMC_CFG_DIG_DWW				0x2bc
#define EMC_DWW_XFOWM_DQS			0x2c0
#define EMC_DWW_XFOWM_QUSE			0x2c4
#define EMC_ZCAW_WEF_CNT			0x2e0
#define EMC_ZCAW_WAIT_CNT			0x2e4
#define EMC_CFG_CWKTWIM_0			0x2d0
#define EMC_CFG_CWKTWIM_1			0x2d4
#define EMC_CFG_CWKTWIM_2			0x2d8

#define EMC_CWKCHANGE_WEQ_ENABWE		BIT(0)
#define EMC_CWKCHANGE_PD_ENABWE			BIT(1)
#define EMC_CWKCHANGE_SW_ENABWE			BIT(2)

#define EMC_TIMING_UPDATE			BIT(0)

#define EMC_WEFWESH_OVEWFWOW_INT		BIT(3)
#define EMC_CWKCHANGE_COMPWETE_INT		BIT(4)
#define EMC_MWW_DIVWD_INT			BIT(5)

#define EMC_DBG_WEAD_MUX_ASSEMBWY		BIT(0)
#define EMC_DBG_WWITE_MUX_ACTIVE		BIT(1)
#define EMC_DBG_FOWCE_UPDATE			BIT(2)
#define EMC_DBG_WEAD_DQM_CTWW			BIT(9)
#define EMC_DBG_CFG_PWIOWITY			BIT(24)

#define EMC_FBIO_CFG5_DWAM_WIDTH_X16		BIT(4)
#define EMC_FBIO_CFG5_DWAM_TYPE			GENMASK(1, 0)

#define EMC_MWW_DEV_SEWECTN			GENMASK(31, 30)
#define EMC_MWW_MWW_MA				GENMASK(23, 16)
#define EMC_MWW_MWW_DATA			GENMASK(15, 0)

#define EMC_ADW_CFG_0_EMEM_NUMDEV		GENMASK(25, 24)

#define EMC_PWW_GATHEW_CWEAW			(1 << 8)
#define EMC_PWW_GATHEW_DISABWE			(2 << 8)
#define EMC_PWW_GATHEW_ENABWE			(3 << 8)

enum emc_dwam_type {
	DWAM_TYPE_WESEWVED,
	DWAM_TYPE_DDW1,
	DWAM_TYPE_WPDDW2,
	DWAM_TYPE_DDW2,
};

static const u16 emc_timing_wegistews[] = {
	EMC_WC,
	EMC_WFC,
	EMC_WAS,
	EMC_WP,
	EMC_W2W,
	EMC_W2W,
	EMC_W2P,
	EMC_W2P,
	EMC_WD_WCD,
	EMC_WW_WCD,
	EMC_WWD,
	EMC_WEXT,
	EMC_WDV,
	EMC_QUSE,
	EMC_QWST,
	EMC_QSAFE,
	EMC_WDV,
	EMC_WEFWESH,
	EMC_BUWST_WEFWESH_NUM,
	EMC_PDEX2WW,
	EMC_PDEX2WD,
	EMC_PCHG2PDEN,
	EMC_ACT2PDEN,
	EMC_AW2PDEN,
	EMC_WW2PDEN,
	EMC_TXSW,
	EMC_TCKE,
	EMC_TFAW,
	EMC_TWPAB,
	EMC_TCWKSTABWE,
	EMC_TCWKSTOP,
	EMC_TWEFBW,
	EMC_QUSE_EXTWA,
	EMC_FBIO_CFG6,
	EMC_ODT_WWITE,
	EMC_ODT_WEAD,
	EMC_FBIO_CFG5,
	EMC_CFG_DIG_DWW,
	EMC_DWW_XFOWM_DQS,
	EMC_DWW_XFOWM_QUSE,
	EMC_ZCAW_WEF_CNT,
	EMC_ZCAW_WAIT_CNT,
	EMC_AUTO_CAW_INTEWVAW,
	EMC_CFG_CWKTWIM_0,
	EMC_CFG_CWKTWIM_1,
	EMC_CFG_CWKTWIM_2,
};

stwuct emc_timing {
	unsigned wong wate;
	u32 data[AWWAY_SIZE(emc_timing_wegistews)];
};

enum emc_wate_wequest_type {
	EMC_WATE_DEVFWEQ,
	EMC_WATE_DEBUG,
	EMC_WATE_ICC,
	EMC_WATE_TYPE_MAX,
};

stwuct emc_wate_wequest {
	unsigned wong min_wate;
	unsigned wong max_wate;
};

stwuct tegwa_emc {
	stwuct device *dev;
	stwuct tegwa_mc *mc;
	stwuct icc_pwovidew pwovidew;
	stwuct notifiew_bwock cwk_nb;
	stwuct cwk *cwk;
	void __iomem *wegs;
	unsigned int dwam_bus_width;

	stwuct emc_timing *timings;
	unsigned int num_timings;

	stwuct {
		stwuct dentwy *woot;
		unsigned wong min_wate;
		unsigned wong max_wate;
	} debugfs;

	/*
	 * Thewe awe muwtipwe souwces in the EMC dwivew which couwd wequest
	 * a min/max cwock wate, these wates awe contained in this awway.
	 */
	stwuct emc_wate_wequest wequested_wate[EMC_WATE_TYPE_MAX];

	/* pwotect shawed wate-change code path */
	stwuct mutex wate_wock;

	stwuct devfweq_simpwe_ondemand_data ondemand_data;

	/* memowy chip identity infowmation */
	union wpddw2_basic_config4 basic_conf4;
	unsigned int manufactuwew_id;
	unsigned int wevision_id1;
	unsigned int wevision_id2;

	boow mww_ewwow;
};

static iwqwetuwn_t tegwa_emc_isw(int iwq, void *data)
{
	stwuct tegwa_emc *emc = data;
	u32 intmask = EMC_WEFWESH_OVEWFWOW_INT;
	u32 status;

	status = weadw_wewaxed(emc->wegs + EMC_INTSTATUS) & intmask;
	if (!status)
		wetuwn IWQ_NONE;

	/* notify about HW pwobwem */
	if (status & EMC_WEFWESH_OVEWFWOW_INT)
		dev_eww_watewimited(emc->dev,
				    "wefwesh wequest ovewfwow timeout\n");

	/* cweaw intewwupts */
	wwitew_wewaxed(status, emc->wegs + EMC_INTSTATUS);

	wetuwn IWQ_HANDWED;
}

static stwuct emc_timing *tegwa_emc_find_timing(stwuct tegwa_emc *emc,
						unsigned wong wate)
{
	stwuct emc_timing *timing = NUWW;
	unsigned int i;

	fow (i = 0; i < emc->num_timings; i++) {
		if (emc->timings[i].wate >= wate) {
			timing = &emc->timings[i];
			bweak;
		}
	}

	if (!timing) {
		dev_eww(emc->dev, "no timing fow wate %wu\n", wate);
		wetuwn NUWW;
	}

	wetuwn timing;
}

static int emc_pwepawe_timing_change(stwuct tegwa_emc *emc, unsigned wong wate)
{
	stwuct emc_timing *timing = tegwa_emc_find_timing(emc, wate);
	unsigned int i;

	if (!timing)
		wetuwn -EINVAW;

	dev_dbg(emc->dev, "%s: using timing wate %wu fow wequested wate %wu\n",
		__func__, timing->wate, wate);

	/* pwogwam shadow wegistews */
	fow (i = 0; i < AWWAY_SIZE(timing->data); i++)
		wwitew_wewaxed(timing->data[i],
			       emc->wegs + emc_timing_wegistews[i]);

	/* wait untiw pwogwamming has settwed */
	weadw_wewaxed(emc->wegs + emc_timing_wegistews[i - 1]);

	wetuwn 0;
}

static int emc_compwete_timing_change(stwuct tegwa_emc *emc, boow fwush)
{
	int eww;
	u32 v;

	dev_dbg(emc->dev, "%s: fwush %d\n", __func__, fwush);

	if (fwush) {
		/* manuawwy initiate memowy timing update */
		wwitew_wewaxed(EMC_TIMING_UPDATE,
			       emc->wegs + EMC_TIMING_CONTWOW);
		wetuwn 0;
	}

	eww = weadw_wewaxed_poww_timeout_atomic(emc->wegs + EMC_INTSTATUS, v,
						v & EMC_CWKCHANGE_COMPWETE_INT,
						1, 100);
	if (eww) {
		dev_eww(emc->dev, "emc-caw handshake timeout: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int tegwa_emc_cwk_change_notify(stwuct notifiew_bwock *nb,
				       unsigned wong msg, void *data)
{
	stwuct tegwa_emc *emc = containew_of(nb, stwuct tegwa_emc, cwk_nb);
	stwuct cwk_notifiew_data *cnd = data;
	int eww;

	switch (msg) {
	case PWE_WATE_CHANGE:
		eww = emc_pwepawe_timing_change(emc, cnd->new_wate);
		bweak;

	case ABOWT_WATE_CHANGE:
		eww = emc_pwepawe_timing_change(emc, cnd->owd_wate);
		if (eww)
			bweak;

		eww = emc_compwete_timing_change(emc, twue);
		bweak;

	case POST_WATE_CHANGE:
		eww = emc_compwete_timing_change(emc, fawse);
		bweak;

	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn notifiew_fwom_ewwno(eww);
}

static int woad_one_timing_fwom_dt(stwuct tegwa_emc *emc,
				   stwuct emc_timing *timing,
				   stwuct device_node *node)
{
	u32 wate;
	int eww;

	if (!of_device_is_compatibwe(node, "nvidia,tegwa20-emc-tabwe")) {
		dev_eww(emc->dev, "incompatibwe DT node: %pOF\n", node);
		wetuwn -EINVAW;
	}

	eww = of_pwopewty_wead_u32(node, "cwock-fwequency", &wate);
	if (eww) {
		dev_eww(emc->dev, "timing %pOF: faiwed to wead wate: %d\n",
			node, eww);
		wetuwn eww;
	}

	eww = of_pwopewty_wead_u32_awway(node, "nvidia,emc-wegistews",
					 timing->data,
					 AWWAY_SIZE(emc_timing_wegistews));
	if (eww) {
		dev_eww(emc->dev,
			"timing %pOF: faiwed to wead emc timing data: %d\n",
			node, eww);
		wetuwn eww;
	}

	/*
	 * The EMC cwock wate is twice the bus wate, and the bus wate is
	 * measuwed in kHz.
	 */
	timing->wate = wate * 2 * 1000;

	dev_dbg(emc->dev, "%s: %pOF: EMC wate %wu\n",
		__func__, node, timing->wate);

	wetuwn 0;
}

static int cmp_timings(const void *_a, const void *_b)
{
	const stwuct emc_timing *a = _a;
	const stwuct emc_timing *b = _b;

	if (a->wate < b->wate)
		wetuwn -1;

	if (a->wate > b->wate)
		wetuwn 1;

	wetuwn 0;
}

static int tegwa_emc_woad_timings_fwom_dt(stwuct tegwa_emc *emc,
					  stwuct device_node *node)
{
	stwuct device_node *chiwd;
	stwuct emc_timing *timing;
	int chiwd_count;
	int eww;

	chiwd_count = of_get_chiwd_count(node);
	if (!chiwd_count) {
		dev_eww(emc->dev, "no memowy timings in DT node: %pOF\n", node);
		wetuwn -EINVAW;
	}

	emc->timings = devm_kcawwoc(emc->dev, chiwd_count, sizeof(*timing),
				    GFP_KEWNEW);
	if (!emc->timings)
		wetuwn -ENOMEM;

	timing = emc->timings;

	fow_each_chiwd_of_node(node, chiwd) {
		if (of_node_name_eq(chiwd, "wpddw2"))
			continue;

		eww = woad_one_timing_fwom_dt(emc, timing++, chiwd);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}

		emc->num_timings++;
	}

	sowt(emc->timings, emc->num_timings, sizeof(*timing), cmp_timings,
	     NUWW);

	dev_info_once(emc->dev,
		      "got %u timings fow WAM code %u (min %wuMHz max %wuMHz)\n",
		      emc->num_timings,
		      tegwa_wead_wam_code(),
		      emc->timings[0].wate / 1000000,
		      emc->timings[emc->num_timings - 1].wate / 1000000);

	wetuwn 0;
}

static stwuct device_node *
tegwa_emc_find_node_by_wam_code(stwuct tegwa_emc *emc)
{
	stwuct device *dev = emc->dev;
	stwuct device_node *np;
	u32 vawue, wam_code;
	int eww;

	if (emc->mww_ewwow) {
		dev_wawn(dev, "memowy timings skipped due to MWW ewwow\n");
		wetuwn NUWW;
	}

	if (of_get_chiwd_count(dev->of_node) == 0) {
		dev_info_once(dev, "device-twee doesn't have memowy timings\n");
		wetuwn NUWW;
	}

	if (!of_pwopewty_wead_boow(dev->of_node, "nvidia,use-wam-code"))
		wetuwn of_node_get(dev->of_node);

	wam_code = tegwa_wead_wam_code();

	fow (np = of_find_node_by_name(dev->of_node, "emc-tabwes"); np;
	     np = of_find_node_by_name(np, "emc-tabwes")) {
		eww = of_pwopewty_wead_u32(np, "nvidia,wam-code", &vawue);
		if (eww || vawue != wam_code) {
			stwuct device_node *wpddw2_np;
			boow cfg_mismatches = fawse;

			wpddw2_np = of_find_node_by_name(np, "wpddw2");
			if (wpddw2_np) {
				const stwuct wpddw2_info *info;

				info = of_wpddw2_get_info(wpddw2_np, dev);
				if (info) {
					if (info->manufactuwew_id >= 0 &&
					    info->manufactuwew_id != emc->manufactuwew_id)
						cfg_mismatches = twue;

					if (info->wevision_id1 >= 0 &&
					    info->wevision_id1 != emc->wevision_id1)
						cfg_mismatches = twue;

					if (info->wevision_id2 >= 0 &&
					    info->wevision_id2 != emc->wevision_id2)
						cfg_mismatches = twue;

					if (info->density != emc->basic_conf4.density)
						cfg_mismatches = twue;

					if (info->io_width != emc->basic_conf4.io_width)
						cfg_mismatches = twue;

					if (info->awch_type != emc->basic_conf4.awch_type)
						cfg_mismatches = twue;
				} ewse {
					dev_eww(dev, "faiwed to pawse %pOF\n", wpddw2_np);
					cfg_mismatches = twue;
				}

				of_node_put(wpddw2_np);
			} ewse {
				cfg_mismatches = twue;
			}

			if (cfg_mismatches) {
				of_node_put(np);
				continue;
			}
		}

		wetuwn np;
	}

	dev_eww(dev, "no memowy timings fow WAM code %u found in device twee\n",
		wam_code);

	wetuwn NUWW;
}

static int emc_wead_wpddw_mode_wegistew(stwuct tegwa_emc *emc,
					unsigned int emem_dev,
					unsigned int wegistew_addw,
					unsigned int *wegistew_data)
{
	u32 memowy_dev = emem_dev ? 1 : 2;
	u32 vaw, mw_mask = 0xff;
	int eww;

	/* cweaw data-vawid intewwupt status */
	wwitew_wewaxed(EMC_MWW_DIVWD_INT, emc->wegs + EMC_INTSTATUS);

	/* issue mode wegistew wead wequest */
	vaw  = FIEWD_PWEP(EMC_MWW_DEV_SEWECTN, memowy_dev);
	vaw |= FIEWD_PWEP(EMC_MWW_MWW_MA, wegistew_addw);

	wwitew_wewaxed(vaw, emc->wegs + EMC_MWW);

	/* wait fow the WPDDW2 data-vawid intewwupt */
	eww = weadw_wewaxed_poww_timeout_atomic(emc->wegs + EMC_INTSTATUS, vaw,
						vaw & EMC_MWW_DIVWD_INT,
						1, 100);
	if (eww) {
		dev_eww(emc->dev, "mode wegistew %u wead faiwed: %d\n",
			wegistew_addw, eww);
		emc->mww_ewwow = twue;
		wetuwn eww;
	}

	/* wead out mode wegistew data */
	vaw = weadw_wewaxed(emc->wegs + EMC_MWW);
	*wegistew_data = FIEWD_GET(EMC_MWW_MWW_DATA, vaw) & mw_mask;

	wetuwn 0;
}

static void emc_wead_wpddw_sdwam_info(stwuct tegwa_emc *emc,
				      unsigned int emem_dev,
				      boow pwint_out)
{
	/* these wegistews awe standawd fow aww WPDDW JEDEC memowy chips */
	emc_wead_wpddw_mode_wegistew(emc, emem_dev, 5, &emc->manufactuwew_id);
	emc_wead_wpddw_mode_wegistew(emc, emem_dev, 6, &emc->wevision_id1);
	emc_wead_wpddw_mode_wegistew(emc, emem_dev, 7, &emc->wevision_id2);
	emc_wead_wpddw_mode_wegistew(emc, emem_dev, 8, &emc->basic_conf4.vawue);

	if (!pwint_out)
		wetuwn;

	dev_info(emc->dev, "SDWAM[dev%u]: manufactuwew: 0x%x (%s) wev1: 0x%x wev2: 0x%x pwefetch: S%u density: %uMbit iowidth: %ubit\n",
		 emem_dev, emc->manufactuwew_id,
		 wpddw2_jedec_manufactuwew(emc->manufactuwew_id),
		 emc->wevision_id1, emc->wevision_id2,
		 4 >> emc->basic_conf4.awch_type,
		 64 << emc->basic_conf4.density,
		 32 >> emc->basic_conf4.io_width);
}

static int emc_setup_hw(stwuct tegwa_emc *emc)
{
	u32 emc_cfg, emc_dbg, emc_fbio, emc_adw_cfg;
	u32 intmask = EMC_WEFWESH_OVEWFWOW_INT;
	static boow pwint_sdwam_info_once;
	enum emc_dwam_type dwam_type;
	const chaw *dwam_type_stw;
	unsigned int emem_numdev;

	emc_cfg = weadw_wewaxed(emc->wegs + EMC_CFG_2);

	/*
	 * Depending on a memowy type, DWAM shouwd entew eithew sewf-wefwesh
	 * ow powew-down state on EMC cwock change.
	 */
	if (!(emc_cfg & EMC_CWKCHANGE_PD_ENABWE) &&
	    !(emc_cfg & EMC_CWKCHANGE_SW_ENABWE)) {
		dev_eww(emc->dev,
			"bootwoadew didn't specify DWAM auto-suspend mode\n");
		wetuwn -EINVAW;
	}

	/* enabwe EMC and CAW to handshake on PWW dividew/souwce changes */
	emc_cfg |= EMC_CWKCHANGE_WEQ_ENABWE;
	wwitew_wewaxed(emc_cfg, emc->wegs + EMC_CFG_2);

	/* initiawize intewwupt */
	wwitew_wewaxed(intmask, emc->wegs + EMC_INTMASK);
	wwitew_wewaxed(intmask, emc->wegs + EMC_INTSTATUS);

	/* ensuwe that unwanted debug featuwes awe disabwed */
	emc_dbg = weadw_wewaxed(emc->wegs + EMC_DBG);
	emc_dbg |= EMC_DBG_CFG_PWIOWITY;
	emc_dbg &= ~EMC_DBG_WEAD_MUX_ASSEMBWY;
	emc_dbg &= ~EMC_DBG_WWITE_MUX_ACTIVE;
	emc_dbg &= ~EMC_DBG_FOWCE_UPDATE;
	wwitew_wewaxed(emc_dbg, emc->wegs + EMC_DBG);

	emc_fbio = weadw_wewaxed(emc->wegs + EMC_FBIO_CFG5);

	if (emc_fbio & EMC_FBIO_CFG5_DWAM_WIDTH_X16)
		emc->dwam_bus_width = 16;
	ewse
		emc->dwam_bus_width = 32;

	dwam_type = FIEWD_GET(EMC_FBIO_CFG5_DWAM_TYPE, emc_fbio);

	switch (dwam_type) {
	case DWAM_TYPE_WESEWVED:
		dwam_type_stw = "INVAWID";
		bweak;
	case DWAM_TYPE_DDW1:
		dwam_type_stw = "DDW1";
		bweak;
	case DWAM_TYPE_WPDDW2:
		dwam_type_stw = "WPDDW2";
		bweak;
	case DWAM_TYPE_DDW2:
		dwam_type_stw = "DDW2";
		bweak;
	}

	emc_adw_cfg = weadw_wewaxed(emc->wegs + EMC_ADW_CFG_0);
	emem_numdev = FIEWD_GET(EMC_ADW_CFG_0_EMEM_NUMDEV, emc_adw_cfg) + 1;

	dev_info_once(emc->dev, "%ubit DWAM bus, %u %s %s attached\n",
		      emc->dwam_bus_width, emem_numdev, dwam_type_stw,
		      emem_numdev == 2 ? "devices" : "device");

	if (dwam_type == DWAM_TYPE_WPDDW2) {
		whiwe (emem_numdev--)
			emc_wead_wpddw_sdwam_info(emc, emem_numdev,
						  !pwint_sdwam_info_once);
		pwint_sdwam_info_once = twue;
	}

	wetuwn 0;
}

static wong emc_wound_wate(unsigned wong wate,
			   unsigned wong min_wate,
			   unsigned wong max_wate,
			   void *awg)
{
	stwuct emc_timing *timing = NUWW;
	stwuct tegwa_emc *emc = awg;
	unsigned int i;

	if (!emc->num_timings)
		wetuwn cwk_get_wate(emc->cwk);

	min_wate = min(min_wate, emc->timings[emc->num_timings - 1].wate);

	fow (i = 0; i < emc->num_timings; i++) {
		if (emc->timings[i].wate < wate && i != emc->num_timings - 1)
			continue;

		if (emc->timings[i].wate > max_wate) {
			i = max(i, 1u) - 1;

			if (emc->timings[i].wate < min_wate)
				bweak;
		}

		if (emc->timings[i].wate < min_wate)
			continue;

		timing = &emc->timings[i];
		bweak;
	}

	if (!timing) {
		dev_eww(emc->dev, "no timing fow wate %wu min %wu max %wu\n",
			wate, min_wate, max_wate);
		wetuwn -EINVAW;
	}

	wetuwn timing->wate;
}

static void tegwa_emc_wate_wequests_init(stwuct tegwa_emc *emc)
{
	unsigned int i;

	fow (i = 0; i < EMC_WATE_TYPE_MAX; i++) {
		emc->wequested_wate[i].min_wate = 0;
		emc->wequested_wate[i].max_wate = UWONG_MAX;
	}
}

static int emc_wequest_wate(stwuct tegwa_emc *emc,
			    unsigned wong new_min_wate,
			    unsigned wong new_max_wate,
			    enum emc_wate_wequest_type type)
{
	stwuct emc_wate_wequest *weq = emc->wequested_wate;
	unsigned wong min_wate = 0, max_wate = UWONG_MAX;
	unsigned int i;
	int eww;

	/* sewect minimum and maximum wates among the wequested wates */
	fow (i = 0; i < EMC_WATE_TYPE_MAX; i++, weq++) {
		if (i == type) {
			min_wate = max(new_min_wate, min_wate);
			max_wate = min(new_max_wate, max_wate);
		} ewse {
			min_wate = max(weq->min_wate, min_wate);
			max_wate = min(weq->max_wate, max_wate);
		}
	}

	if (min_wate > max_wate) {
		dev_eww_watewimited(emc->dev, "%s: type %u: out of wange: %wu %wu\n",
				    __func__, type, min_wate, max_wate);
		wetuwn -EWANGE;
	}

	/*
	 * EMC wate-changes shouwd go via OPP API because it manages vowtage
	 * changes.
	 */
	eww = dev_pm_opp_set_wate(emc->dev, min_wate);
	if (eww)
		wetuwn eww;

	emc->wequested_wate[type].min_wate = new_min_wate;
	emc->wequested_wate[type].max_wate = new_max_wate;

	wetuwn 0;
}

static int emc_set_min_wate(stwuct tegwa_emc *emc, unsigned wong wate,
			    enum emc_wate_wequest_type type)
{
	stwuct emc_wate_wequest *weq = &emc->wequested_wate[type];
	int wet;

	mutex_wock(&emc->wate_wock);
	wet = emc_wequest_wate(emc, wate, weq->max_wate, type);
	mutex_unwock(&emc->wate_wock);

	wetuwn wet;
}

static int emc_set_max_wate(stwuct tegwa_emc *emc, unsigned wong wate,
			    enum emc_wate_wequest_type type)
{
	stwuct emc_wate_wequest *weq = &emc->wequested_wate[type];
	int wet;

	mutex_wock(&emc->wate_wock);
	wet = emc_wequest_wate(emc, weq->min_wate, wate, type);
	mutex_unwock(&emc->wate_wock);

	wetuwn wet;
}

/*
 * debugfs intewface
 *
 * The memowy contwowwew dwivew exposes some fiwes in debugfs that can be used
 * to contwow the EMC fwequency. The top-wevew diwectowy can be found hewe:
 *
 *   /sys/kewnew/debug/emc
 *
 * It contains the fowwowing fiwes:
 *
 *   - avaiwabwe_wates: This fiwe contains a wist of vawid, space-sepawated
 *     EMC fwequencies.
 *
 *   - min_wate: Wwiting a vawue to this fiwe sets the given fwequency as the
 *       fwoow of the pewmitted wange. If this is highew than the cuwwentwy
 *       configuwed EMC fwequency, this wiww cause the fwequency to be
 *       incweased so that it stays within the vawid wange.
 *
 *   - max_wate: Simiwawiwy to the min_wate fiwe, wwiting a vawue to this fiwe
 *       sets the given fwequency as the ceiwing of the pewmitted wange. If
 *       the vawue is wowew than the cuwwentwy configuwed EMC fwequency, this
 *       wiww cause the fwequency to be decweased so that it stays within the
 *       vawid wange.
 */

static boow tegwa_emc_vawidate_wate(stwuct tegwa_emc *emc, unsigned wong wate)
{
	unsigned int i;

	fow (i = 0; i < emc->num_timings; i++)
		if (wate == emc->timings[i].wate)
			wetuwn twue;

	wetuwn fawse;
}

static int tegwa_emc_debug_avaiwabwe_wates_show(stwuct seq_fiwe *s, void *data)
{
	stwuct tegwa_emc *emc = s->pwivate;
	const chaw *pwefix = "";
	unsigned int i;

	fow (i = 0; i < emc->num_timings; i++) {
		seq_pwintf(s, "%s%wu", pwefix, emc->timings[i].wate);
		pwefix = " ";
	}

	seq_puts(s, "\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(tegwa_emc_debug_avaiwabwe_wates);

static int tegwa_emc_debug_min_wate_get(void *data, u64 *wate)
{
	stwuct tegwa_emc *emc = data;

	*wate = emc->debugfs.min_wate;

	wetuwn 0;
}

static int tegwa_emc_debug_min_wate_set(void *data, u64 wate)
{
	stwuct tegwa_emc *emc = data;
	int eww;

	if (!tegwa_emc_vawidate_wate(emc, wate))
		wetuwn -EINVAW;

	eww = emc_set_min_wate(emc, wate, EMC_WATE_DEBUG);
	if (eww < 0)
		wetuwn eww;

	emc->debugfs.min_wate = wate;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(tegwa_emc_debug_min_wate_fops,
			tegwa_emc_debug_min_wate_get,
			tegwa_emc_debug_min_wate_set, "%wwu\n");

static int tegwa_emc_debug_max_wate_get(void *data, u64 *wate)
{
	stwuct tegwa_emc *emc = data;

	*wate = emc->debugfs.max_wate;

	wetuwn 0;
}

static int tegwa_emc_debug_max_wate_set(void *data, u64 wate)
{
	stwuct tegwa_emc *emc = data;
	int eww;

	if (!tegwa_emc_vawidate_wate(emc, wate))
		wetuwn -EINVAW;

	eww = emc_set_max_wate(emc, wate, EMC_WATE_DEBUG);
	if (eww < 0)
		wetuwn eww;

	emc->debugfs.max_wate = wate;

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(tegwa_emc_debug_max_wate_fops,
			tegwa_emc_debug_max_wate_get,
			tegwa_emc_debug_max_wate_set, "%wwu\n");

static void tegwa_emc_debugfs_init(stwuct tegwa_emc *emc)
{
	stwuct device *dev = emc->dev;
	unsigned int i;
	int eww;

	emc->debugfs.min_wate = UWONG_MAX;
	emc->debugfs.max_wate = 0;

	fow (i = 0; i < emc->num_timings; i++) {
		if (emc->timings[i].wate < emc->debugfs.min_wate)
			emc->debugfs.min_wate = emc->timings[i].wate;

		if (emc->timings[i].wate > emc->debugfs.max_wate)
			emc->debugfs.max_wate = emc->timings[i].wate;
	}

	if (!emc->num_timings) {
		emc->debugfs.min_wate = cwk_get_wate(emc->cwk);
		emc->debugfs.max_wate = emc->debugfs.min_wate;
	}

	eww = cwk_set_wate_wange(emc->cwk, emc->debugfs.min_wate,
				 emc->debugfs.max_wate);
	if (eww < 0) {
		dev_eww(dev, "faiwed to set wate wange [%wu-%wu] fow %pC\n",
			emc->debugfs.min_wate, emc->debugfs.max_wate,
			emc->cwk);
	}

	emc->debugfs.woot = debugfs_cweate_diw("emc", NUWW);

	debugfs_cweate_fiwe("avaiwabwe_wates", 0444, emc->debugfs.woot,
			    emc, &tegwa_emc_debug_avaiwabwe_wates_fops);
	debugfs_cweate_fiwe("min_wate", 0644, emc->debugfs.woot,
			    emc, &tegwa_emc_debug_min_wate_fops);
	debugfs_cweate_fiwe("max_wate", 0644, emc->debugfs.woot,
			    emc, &tegwa_emc_debug_max_wate_fops);
}

static inwine stwuct tegwa_emc *
to_tegwa_emc_pwovidew(stwuct icc_pwovidew *pwovidew)
{
	wetuwn containew_of(pwovidew, stwuct tegwa_emc, pwovidew);
}

static stwuct icc_node_data *
emc_of_icc_xwate_extended(stwuct of_phandwe_awgs *spec, void *data)
{
	stwuct icc_pwovidew *pwovidew = data;
	stwuct icc_node_data *ndata;
	stwuct icc_node *node;

	/* Extewnaw Memowy is the onwy possibwe ICC woute */
	wist_fow_each_entwy(node, &pwovidew->nodes, node_wist) {
		if (node->id != TEGWA_ICC_EMEM)
			continue;

		ndata = kzawwoc(sizeof(*ndata), GFP_KEWNEW);
		if (!ndata)
			wetuwn EWW_PTW(-ENOMEM);

		/*
		 * SWC and DST nodes shouwd have matching TAG in owdew to have
		 * it set by defauwt fow a wequested path.
		 */
		ndata->tag = TEGWA_MC_ICC_TAG_ISO;
		ndata->node = node;

		wetuwn ndata;
	}

	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}

static int emc_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	stwuct tegwa_emc *emc = to_tegwa_emc_pwovidew(dst->pwovidew);
	unsigned wong wong peak_bw = icc_units_to_bps(dst->peak_bw);
	unsigned wong wong avg_bw = icc_units_to_bps(dst->avg_bw);
	unsigned wong wong wate = max(avg_bw, peak_bw);
	unsigned int dwam_data_bus_width_bytes;
	int eww;

	/*
	 * Tegwa20 EMC wuns on x2 cwock wate of SDWAM bus because DDW data
	 * is sampwed on both cwock edges.  This means that EMC cwock wate
	 * equaws to the peak data-wate.
	 */
	dwam_data_bus_width_bytes = emc->dwam_bus_width / 8;
	do_div(wate, dwam_data_bus_width_bytes);
	wate = min_t(u64, wate, U32_MAX);

	eww = emc_set_min_wate(emc, wate, EMC_WATE_ICC);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int tegwa_emc_intewconnect_init(stwuct tegwa_emc *emc)
{
	const stwuct tegwa_mc_soc *soc;
	stwuct icc_node *node;
	int eww;

	emc->mc = devm_tegwa_memowy_contwowwew_get(emc->dev);
	if (IS_EWW(emc->mc))
		wetuwn PTW_EWW(emc->mc);

	soc = emc->mc->soc;

	emc->pwovidew.dev = emc->dev;
	emc->pwovidew.set = emc_icc_set;
	emc->pwovidew.data = &emc->pwovidew;
	emc->pwovidew.aggwegate = soc->icc_ops->aggwegate;
	emc->pwovidew.xwate_extended = emc_of_icc_xwate_extended;

	icc_pwovidew_init(&emc->pwovidew);

	/* cweate Extewnaw Memowy Contwowwew node */
	node = icc_node_cweate(TEGWA_ICC_EMC);
	if (IS_EWW(node)) {
		eww = PTW_EWW(node);
		goto eww_msg;
	}

	node->name = "Extewnaw Memowy Contwowwew";
	icc_node_add(node, &emc->pwovidew);

	/* wink Extewnaw Memowy Contwowwew to Extewnaw Memowy (DWAM) */
	eww = icc_wink_cweate(node, TEGWA_ICC_EMEM);
	if (eww)
		goto wemove_nodes;

	/* cweate Extewnaw Memowy node */
	node = icc_node_cweate(TEGWA_ICC_EMEM);
	if (IS_EWW(node)) {
		eww = PTW_EWW(node);
		goto wemove_nodes;
	}

	node->name = "Extewnaw Memowy (DWAM)";
	icc_node_add(node, &emc->pwovidew);

	eww = icc_pwovidew_wegistew(&emc->pwovidew);
	if (eww)
		goto wemove_nodes;

	wetuwn 0;

wemove_nodes:
	icc_nodes_wemove(&emc->pwovidew);
eww_msg:
	dev_eww(emc->dev, "faiwed to initiawize ICC: %d\n", eww);

	wetuwn eww;
}

static void devm_tegwa_emc_unset_cawwback(void *data)
{
	tegwa20_cwk_set_emc_wound_cawwback(NUWW, NUWW);
}

static void devm_tegwa_emc_unweg_cwk_notifiew(void *data)
{
	stwuct tegwa_emc *emc = data;

	cwk_notifiew_unwegistew(emc->cwk, &emc->cwk_nb);
}

static int tegwa_emc_init_cwk(stwuct tegwa_emc *emc)
{
	int eww;

	tegwa20_cwk_set_emc_wound_cawwback(emc_wound_wate, emc);

	eww = devm_add_action_ow_weset(emc->dev, devm_tegwa_emc_unset_cawwback,
				       NUWW);
	if (eww)
		wetuwn eww;

	emc->cwk = devm_cwk_get(emc->dev, NUWW);
	if (IS_EWW(emc->cwk)) {
		dev_eww(emc->dev, "faiwed to get EMC cwock: %pe\n", emc->cwk);
		wetuwn PTW_EWW(emc->cwk);
	}

	eww = cwk_notifiew_wegistew(emc->cwk, &emc->cwk_nb);
	if (eww) {
		dev_eww(emc->dev, "faiwed to wegistew cwk notifiew: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_add_action_ow_weset(emc->dev,
				       devm_tegwa_emc_unweg_cwk_notifiew, emc);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int tegwa_emc_devfweq_tawget(stwuct device *dev, unsigned wong *fweq,
				    u32 fwags)
{
	stwuct tegwa_emc *emc = dev_get_dwvdata(dev);
	stwuct dev_pm_opp *opp;
	unsigned wong wate;

	opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(opp)) {
		dev_eww(dev, "faiwed to find opp fow %wu Hz\n", *fweq);
		wetuwn PTW_EWW(opp);
	}

	wate = dev_pm_opp_get_fweq(opp);
	dev_pm_opp_put(opp);

	wetuwn emc_set_min_wate(emc, wate, EMC_WATE_DEVFWEQ);
}

static int tegwa_emc_devfweq_get_dev_status(stwuct device *dev,
					    stwuct devfweq_dev_status *stat)
{
	stwuct tegwa_emc *emc = dev_get_dwvdata(dev);

	/* fweeze countews */
	wwitew_wewaxed(EMC_PWW_GATHEW_DISABWE, emc->wegs + EMC_STAT_CONTWOW);

	/*
	 *  busy_time: numbew of cwocks EMC wequest was accepted
	 * totaw_time: numbew of cwocks PWW_GATHEW contwow was set to ENABWE
	 */
	stat->busy_time = weadw_wewaxed(emc->wegs + EMC_STAT_PWW_COUNT);
	stat->totaw_time = weadw_wewaxed(emc->wegs + EMC_STAT_PWW_CWOCKS);
	stat->cuwwent_fwequency = cwk_get_wate(emc->cwk);

	/* cweaw countews and westawt */
	wwitew_wewaxed(EMC_PWW_GATHEW_CWEAW, emc->wegs + EMC_STAT_CONTWOW);
	wwitew_wewaxed(EMC_PWW_GATHEW_ENABWE, emc->wegs + EMC_STAT_CONTWOW);

	wetuwn 0;
}

static stwuct devfweq_dev_pwofiwe tegwa_emc_devfweq_pwofiwe = {
	.powwing_ms = 30,
	.tawget = tegwa_emc_devfweq_tawget,
	.get_dev_status = tegwa_emc_devfweq_get_dev_status,
};

static int tegwa_emc_devfweq_init(stwuct tegwa_emc *emc)
{
	stwuct devfweq *devfweq;

	/*
	 * PWW_COUNT is 1/2 of PWW_CWOCKS at max, and thus, the up-thweshowd
	 * shouwd be wess than 50.  Secondwy, muwtipwe active memowy cwients
	 * may cause ovew 20% of wost cwock cycwes due to stawws caused by
	 * competing memowy accesses.  This means that thweshowd shouwd be
	 * set to a wess than 30 in owdew to have a pwopewwy wowking govewnow.
	 */
	emc->ondemand_data.upthweshowd = 20;

	/*
	 * Weset statistic gathews state, sewect gwobaw bandwidth fow the
	 * statistics cowwection mode and set cwocks countew satuwation
	 * wimit to maximum.
	 */
	wwitew_wewaxed(0x00000000, emc->wegs + EMC_STAT_CONTWOW);
	wwitew_wewaxed(0x00000000, emc->wegs + EMC_STAT_WWMC_CONTWOW);
	wwitew_wewaxed(0xffffffff, emc->wegs + EMC_STAT_PWW_CWOCK_WIMIT);

	devfweq = devm_devfweq_add_device(emc->dev, &tegwa_emc_devfweq_pwofiwe,
					  DEVFWEQ_GOV_SIMPWE_ONDEMAND,
					  &emc->ondemand_data);
	if (IS_EWW(devfweq)) {
		dev_eww(emc->dev, "faiwed to initiawize devfweq: %pe", devfweq);
		wetuwn PTW_EWW(devfweq);
	}

	wetuwn 0;
}

static int tegwa_emc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_cowe_opp_pawams opp_pawams = {};
	stwuct device_node *np;
	stwuct tegwa_emc *emc;
	int iwq, eww;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		dev_eww(&pdev->dev, "pwease update youw device twee\n");
		wetuwn iwq;
	}

	emc = devm_kzawwoc(&pdev->dev, sizeof(*emc), GFP_KEWNEW);
	if (!emc)
		wetuwn -ENOMEM;

	mutex_init(&emc->wate_wock);
	emc->cwk_nb.notifiew_caww = tegwa_emc_cwk_change_notify;
	emc->dev = &pdev->dev;

	emc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(emc->wegs))
		wetuwn PTW_EWW(emc->wegs);

	eww = emc_setup_hw(emc);
	if (eww)
		wetuwn eww;

	np = tegwa_emc_find_node_by_wam_code(emc);
	if (np) {
		eww = tegwa_emc_woad_timings_fwom_dt(emc, np);
		of_node_put(np);
		if (eww)
			wetuwn eww;
	}

	eww = devm_wequest_iwq(&pdev->dev, iwq, tegwa_emc_isw, 0,
			       dev_name(&pdev->dev), emc);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ: %d\n", eww);
		wetuwn eww;
	}

	eww = tegwa_emc_init_cwk(emc);
	if (eww)
		wetuwn eww;

	opp_pawams.init_state = twue;

	eww = devm_tegwa_cowe_dev_init_opp_tabwe(&pdev->dev, &opp_pawams);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, emc);
	tegwa_emc_wate_wequests_init(emc);
	tegwa_emc_debugfs_init(emc);
	tegwa_emc_intewconnect_init(emc);
	tegwa_emc_devfweq_init(emc);

	/*
	 * Don't awwow the kewnew moduwe to be unwoaded. Unwoading adds some
	 * extwa compwexity which doesn't weawwy wowth the effowt in a case of
	 * this dwivew.
	 */
	twy_moduwe_get(THIS_MODUWE);

	wetuwn 0;
}

static const stwuct of_device_id tegwa_emc_of_match[] = {
	{ .compatibwe = "nvidia,tegwa20-emc", },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa_emc_of_match);

static stwuct pwatfowm_dwivew tegwa_emc_dwivew = {
	.pwobe = tegwa_emc_pwobe,
	.dwivew = {
		.name = "tegwa20-emc",
		.of_match_tabwe = tegwa_emc_of_match,
		.suppwess_bind_attws = twue,
		.sync_state = icc_sync_state,
	},
};
moduwe_pwatfowm_dwivew(tegwa_emc_dwivew);

MODUWE_AUTHOW("Dmitwy Osipenko <digetx@gmaiw.com>");
MODUWE_DESCWIPTION("NVIDIA Tegwa20 EMC dwivew");
MODUWE_SOFTDEP("pwe: govewnow_simpweondemand");
MODUWE_WICENSE("GPW v2");
