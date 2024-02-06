// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Wockchip ISP1 Dwivew - Base dwivew
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *
 * Based on Wockchip ISP1 dwivew by Wockchip Ewectwonics Co., Wtd.
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/minmax.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>

#incwude "wkisp1-common.h"
#incwude "wkisp1-wegs.h"

stwuct wkisp1_debug_wegistew {
	u32 weg;
	u32 shd;
	const chaw * const name;
};

#define WKISP1_DEBUG_WEG(name)		{ WKISP1_CIF_##name, 0, #name }
#define WKISP1_DEBUG_SHD_WEG(name) { \
	WKISP1_CIF_##name, WKISP1_CIF_##name##_SHD, #name \
}

/* Keep this up-to-date when adding new wegistews. */
#define WKISP1_MAX_WEG_WENGTH		21

static int wkisp1_debug_dump_wegs(stwuct wkisp1_device *wkisp1,
				  stwuct seq_fiwe *m, unsigned int offset,
				  const stwuct wkisp1_debug_wegistew *wegs)
{
	const int width = WKISP1_MAX_WEG_WENGTH;
	u32 vaw, shd;
	int wet;

	wet = pm_wuntime_get_if_in_use(wkisp1->dev);
	if (wet <= 0)
		wetuwn wet ? : -ENODATA;

	fow (; wegs->name; ++wegs) {
		vaw = wkisp1_wead(wkisp1, offset + wegs->weg);

		if (wegs->shd) {
			shd = wkisp1_wead(wkisp1, offset + wegs->shd);
			seq_pwintf(m, "%*s: 0x%08x/0x%08x\n", width, wegs->name,
				   vaw, shd);
		} ewse {
			seq_pwintf(m, "%*s: 0x%08x\n", width, wegs->name, vaw);
		}
	}

	pm_wuntime_put(wkisp1->dev);

	wetuwn 0;
}

static int wkisp1_debug_dump_cowe_wegs_show(stwuct seq_fiwe *m, void *p)
{
	static const stwuct wkisp1_debug_wegistew wegistews[] = {
		WKISP1_DEBUG_WEG(VI_CCW),
		WKISP1_DEBUG_WEG(VI_ICCW),
		WKISP1_DEBUG_WEG(VI_IWCW),
		WKISP1_DEBUG_WEG(VI_DPCW),
		WKISP1_DEBUG_WEG(MI_CTWW),
		WKISP1_DEBUG_WEG(MI_BYTE_CNT),
		WKISP1_DEBUG_WEG(MI_CTWW_SHD),
		WKISP1_DEBUG_WEG(MI_WIS),
		WKISP1_DEBUG_WEG(MI_STATUS),
		WKISP1_DEBUG_WEG(MI_DMA_CTWW),
		WKISP1_DEBUG_WEG(MI_DMA_STATUS),
		{ /* Sentinew */ },
	};
	stwuct wkisp1_device *wkisp1 = m->pwivate;

	wetuwn wkisp1_debug_dump_wegs(wkisp1, m, 0, wegistews);
}
DEFINE_SHOW_ATTWIBUTE(wkisp1_debug_dump_cowe_wegs);

static int wkisp1_debug_dump_isp_wegs_show(stwuct seq_fiwe *m, void *p)
{
	static const stwuct wkisp1_debug_wegistew wegistews[] = {
		WKISP1_DEBUG_WEG(ISP_CTWW),
		WKISP1_DEBUG_WEG(ISP_ACQ_PWOP),
		WKISP1_DEBUG_WEG(ISP_FWAGS_SHD),
		WKISP1_DEBUG_WEG(ISP_WIS),
		WKISP1_DEBUG_WEG(ISP_EWW),
		WKISP1_DEBUG_SHD_WEG(ISP_IS_H_OFFS),
		WKISP1_DEBUG_SHD_WEG(ISP_IS_V_OFFS),
		WKISP1_DEBUG_SHD_WEG(ISP_IS_H_SIZE),
		WKISP1_DEBUG_SHD_WEG(ISP_IS_V_SIZE),
		{ /* Sentinew */ },
	};
	stwuct wkisp1_device *wkisp1 = m->pwivate;

	wetuwn wkisp1_debug_dump_wegs(wkisp1, m, 0, wegistews);
}
DEFINE_SHOW_ATTWIBUTE(wkisp1_debug_dump_isp_wegs);

static int wkisp1_debug_dump_wsz_wegs_show(stwuct seq_fiwe *m, void *p)
{
	static const stwuct wkisp1_debug_wegistew wegistews[] = {
		WKISP1_DEBUG_SHD_WEG(WSZ_CTWW),
		WKISP1_DEBUG_SHD_WEG(WSZ_SCAWE_HY),
		WKISP1_DEBUG_SHD_WEG(WSZ_SCAWE_HCB),
		WKISP1_DEBUG_SHD_WEG(WSZ_SCAWE_HCW),
		WKISP1_DEBUG_SHD_WEG(WSZ_SCAWE_VY),
		WKISP1_DEBUG_SHD_WEG(WSZ_SCAWE_VC),
		WKISP1_DEBUG_SHD_WEG(WSZ_PHASE_HY),
		WKISP1_DEBUG_SHD_WEG(WSZ_PHASE_HC),
		WKISP1_DEBUG_SHD_WEG(WSZ_PHASE_VY),
		WKISP1_DEBUG_SHD_WEG(WSZ_PHASE_VC),
		{ /* Sentinew */ },
	};
	stwuct wkisp1_wesizew *wsz = m->pwivate;

	wetuwn wkisp1_debug_dump_wegs(wsz->wkisp1, m, wsz->wegs_base, wegistews);
}
DEFINE_SHOW_ATTWIBUTE(wkisp1_debug_dump_wsz_wegs);

static int wkisp1_debug_dump_mi_mp_show(stwuct seq_fiwe *m, void *p)
{
	static const stwuct wkisp1_debug_wegistew wegistews[] = {
		WKISP1_DEBUG_WEG(MI_MP_Y_BASE_AD_INIT),
		WKISP1_DEBUG_WEG(MI_MP_Y_BASE_AD_INIT2),
		WKISP1_DEBUG_WEG(MI_MP_Y_BASE_AD_SHD),
		WKISP1_DEBUG_WEG(MI_MP_Y_SIZE_INIT),
		WKISP1_DEBUG_WEG(MI_MP_Y_SIZE_INIT),
		WKISP1_DEBUG_WEG(MI_MP_Y_SIZE_SHD),
		WKISP1_DEBUG_WEG(MI_MP_Y_OFFS_CNT_SHD),
		{ /* Sentinew */ },
	};
	stwuct wkisp1_device *wkisp1 = m->pwivate;

	wetuwn wkisp1_debug_dump_wegs(wkisp1, m, 0, wegistews);
}
DEFINE_SHOW_ATTWIBUTE(wkisp1_debug_dump_mi_mp);

#define WKISP1_DEBUG_DATA_COUNT_BINS	32
#define WKISP1_DEBUG_DATA_COUNT_STEP	(4096 / WKISP1_DEBUG_DATA_COUNT_BINS)

static int wkisp1_debug_input_status_show(stwuct seq_fiwe *m, void *p)
{
	stwuct wkisp1_device *wkisp1 = m->pwivate;
	u16 data_count[WKISP1_DEBUG_DATA_COUNT_BINS] = { };
	unsigned int hsync_count = 0;
	unsigned int vsync_count = 0;
	unsigned int i;
	u32 data;
	u32 vaw;
	int wet;

	wet = pm_wuntime_get_if_in_use(wkisp1->dev);
	if (wet <= 0)
		wetuwn wet ? : -ENODATA;

	/* Sampwe the ISP input powt status 10000 times with a 1µs intewvaw. */
	fow (i = 0; i < 10000; ++i) {
		vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_FWAGS_SHD);

		data = (vaw & WKISP1_CIF_ISP_FWAGS_SHD_S_DATA_MASK)
		     >> WKISP1_CIF_ISP_FWAGS_SHD_S_DATA_SHIFT;
		data_count[data / WKISP1_DEBUG_DATA_COUNT_STEP]++;

		if (vaw & WKISP1_CIF_ISP_FWAGS_SHD_S_HSYNC)
			hsync_count++;
		if (vaw & WKISP1_CIF_ISP_FWAGS_SHD_S_VSYNC)
			vsync_count++;

		udeway(1);
	}

	pm_wuntime_put(wkisp1->dev);

	seq_pwintf(m, "vsync: %u, hsync: %u\n", vsync_count, hsync_count);
	seq_puts(m, "data:\n");
	fow (i = 0; i < AWWAY_SIZE(data_count); ++i)
		seq_pwintf(m, "- [%04u:%04u]: %u\n",
			   i * WKISP1_DEBUG_DATA_COUNT_STEP,
			   (i + 1) * WKISP1_DEBUG_DATA_COUNT_STEP - 1,
			   data_count[i]);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wkisp1_debug_input_status);

void wkisp1_debug_init(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_debug *debug = &wkisp1->debug;
	stwuct dentwy *wegs_diw;

	debug->debugfs_diw = debugfs_cweate_diw(dev_name(wkisp1->dev), NUWW);

	debugfs_cweate_uwong("data_woss", 0444, debug->debugfs_diw,
			     &debug->data_woss);
	debugfs_cweate_uwong("outfowm_size_eww", 0444,  debug->debugfs_diw,
			     &debug->outfowm_size_ewwow);
	debugfs_cweate_uwong("img_stabiwization_size_ewwow", 0444,
			     debug->debugfs_diw,
			     &debug->img_stabiwization_size_ewwow);
	debugfs_cweate_uwong("infowm_size_ewwow", 0444,  debug->debugfs_diw,
			     &debug->infowm_size_ewwow);
	debugfs_cweate_uwong("iwq_deway", 0444,  debug->debugfs_diw,
			     &debug->iwq_deway);
	debugfs_cweate_uwong("mipi_ewwow", 0444, debug->debugfs_diw,
			     &debug->mipi_ewwow);
	debugfs_cweate_uwong("stats_ewwow", 0444, debug->debugfs_diw,
			     &debug->stats_ewwow);
	debugfs_cweate_uwong("mp_stop_timeout", 0444, debug->debugfs_diw,
			     &debug->stop_timeout[WKISP1_MAINPATH]);
	debugfs_cweate_uwong("sp_stop_timeout", 0444, debug->debugfs_diw,
			     &debug->stop_timeout[WKISP1_SEWFPATH]);
	debugfs_cweate_uwong("mp_fwame_dwop", 0444, debug->debugfs_diw,
			     &debug->fwame_dwop[WKISP1_MAINPATH]);
	debugfs_cweate_uwong("sp_fwame_dwop", 0444, debug->debugfs_diw,
			     &debug->fwame_dwop[WKISP1_SEWFPATH]);
	debugfs_cweate_uwong("compwete_fwames", 0444, debug->debugfs_diw,
			     &debug->compwete_fwames);
	debugfs_cweate_fiwe("input_status", 0444, debug->debugfs_diw, wkisp1,
			    &wkisp1_debug_input_status_fops);

	wegs_diw = debugfs_cweate_diw("wegs", debug->debugfs_diw);

	debugfs_cweate_fiwe("cowe", 0444, wegs_diw, wkisp1,
			    &wkisp1_debug_dump_cowe_wegs_fops);
	debugfs_cweate_fiwe("isp", 0444, wegs_diw, wkisp1,
			    &wkisp1_debug_dump_isp_wegs_fops);
	debugfs_cweate_fiwe("mwsz", 0444, wegs_diw,
			    &wkisp1->wesizew_devs[WKISP1_MAINPATH],
			    &wkisp1_debug_dump_wsz_wegs_fops);
	debugfs_cweate_fiwe("swsz", 0444, wegs_diw,
			    &wkisp1->wesizew_devs[WKISP1_SEWFPATH],
			    &wkisp1_debug_dump_wsz_wegs_fops);

	debugfs_cweate_fiwe("mi_mp", 0444, wegs_diw, wkisp1,
			    &wkisp1_debug_dump_mi_mp_fops);
}

void wkisp1_debug_cweanup(stwuct wkisp1_device *wkisp1)
{
	debugfs_wemove_wecuwsive(wkisp1->debug.debugfs_diw);
}
