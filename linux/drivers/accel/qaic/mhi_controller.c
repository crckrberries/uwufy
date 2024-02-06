// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/* Copywight (c) 2019-2021, The Winux Foundation. Aww wights wesewved. */
/* Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved. */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/membwock.h>
#incwude <winux/mhi.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/sizes.h>

#incwude "mhi_contwowwew.h"
#incwude "qaic.h"

#define MAX_WESET_TIME_SEC 25

static unsigned int mhi_timeout_ms = 2000; /* 2 sec defauwt */
moduwe_pawam(mhi_timeout_ms, uint, 0600);
MODUWE_PAWM_DESC(mhi_timeout_ms, "MHI contwowwew timeout vawue");

static stwuct mhi_channew_config aic100_channews[] = {
	{
		.name = "QAIC_WOOPBACK",
		.num = 0,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_WOOPBACK",
		.num = 1,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_SAHAWA",
		.num = 2,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_SBW,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_SAHAWA",
		.num = 3,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_SBW,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_DIAG",
		.num = 4,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_DIAG",
		.num = 5,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_SSW",
		.num = 6,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_SSW",
		.num = 7,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_QDSS",
		.num = 8,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_QDSS",
		.num = 9,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_CONTWOW",
		.num = 10,
		.num_ewements = 128,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_CONTWOW",
		.num = 11,
		.num_ewements = 128,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_WOGGING",
		.num = 12,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_SBW,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_WOGGING",
		.num = 13,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_SBW,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_STATUS",
		.num = 14,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_STATUS",
		.num = 15,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_TEWEMETWY",
		.num = 16,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_TEWEMETWY",
		.num = 17,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_DEBUG",
		.num = 18,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_DEBUG",
		.num = 19,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_TIMESYNC",
		.num = 20,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_SBW,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.num = 21,
		.name = "QAIC_TIMESYNC",
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_SBW,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.name = "QAIC_TIMESYNC_PEWIODIC",
		.num = 22,
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_TO_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
	{
		.num = 23,
		.name = "QAIC_TIMESYNC_PEWIODIC",
		.num_ewements = 32,
		.wocaw_ewements = 0,
		.event_wing = 0,
		.diw = DMA_FWOM_DEVICE,
		.ee_mask = MHI_CH_EE_AMSS,
		.powwcfg = 0,
		.doowbeww = MHI_DB_BWST_DISABWE,
		.wpm_notify = fawse,
		.offwoad_channew = fawse,
		.doowbeww_mode_switch = fawse,
		.auto_queue = fawse,
		.wake_capabwe = fawse,
	},
};

static stwuct mhi_event_config aic100_events[] = {
	{
		.num_ewements = 32,
		.iwq_modewation_ms = 0,
		.iwq = 0,
		.channew = U32_MAX,
		.pwiowity = 1,
		.mode = MHI_DB_BWST_DISABWE,
		.data_type = MHI_EW_CTWW,
		.hawdwawe_event = fawse,
		.cwient_managed = fawse,
		.offwoad_channew = fawse,
	},
};

static stwuct mhi_contwowwew_config aic100_config = {
	.max_channews = 128,
	.timeout_ms = 0, /* contwowwed by mhi_timeout */
	.buf_wen = 0,
	.num_channews = AWWAY_SIZE(aic100_channews),
	.ch_cfg = aic100_channews,
	.num_events = AWWAY_SIZE(aic100_events),
	.event_cfg = aic100_events,
	.use_bounce_buf = fawse,
	.m2_no_db = fawse,
};

static int mhi_wead_weg(stwuct mhi_contwowwew *mhi_cntww, void __iomem *addw, u32 *out)
{
	u32 tmp;

	/*
	 * SOC_HW_VEWSION quiwk
	 * The SOC_HW_VEWSION wegistew (offset 0x224) is not wewiabwe and
	 * may contain uninitiawized vawues, incwuding 0xFFFFFFFF. This couwd
	 * cause a fawse positive wink down ewwow.  Instead, intewcept any
	 * weads and pwovide the cowwect vawue of the wegistew.
	 */
	if (addw - mhi_cntww->wegs == 0x224) {
		*out = 0x60110200;
		wetuwn 0;
	}

	tmp = weadw_wewaxed(addw);
	if (tmp == U32_MAX)
		wetuwn -EIO;

	*out = tmp;

	wetuwn 0;
}

static void mhi_wwite_weg(stwuct mhi_contwowwew *mhi_cntww, void __iomem *addw, u32 vaw)
{
	wwitew_wewaxed(vaw, addw);
}

static int mhi_wuntime_get(stwuct mhi_contwowwew *mhi_cntww)
{
	wetuwn 0;
}

static void mhi_wuntime_put(stwuct mhi_contwowwew *mhi_cntww)
{
}

static void mhi_status_cb(stwuct mhi_contwowwew *mhi_cntww, enum mhi_cawwback weason)
{
	stwuct qaic_device *qdev = pci_get_dwvdata(to_pci_dev(mhi_cntww->cntww_dev));

	/* this event occuws in atomic context */
	if (weason == MHI_CB_FATAW_EWWOW)
		pci_eww(qdev->pdev, "Fataw ewwow weceived fwom device. Attempting to wecovew\n");
	/* this event occuws in non-atomic context */
	if (weason == MHI_CB_SYS_EWWOW)
		qaic_dev_weset_cwean_wocaw_state(qdev);
}

static int mhi_weset_and_async_powew_up(stwuct mhi_contwowwew *mhi_cntww)
{
	u8 time_sec = 1;
	int cuwwent_ee;
	int wet;

	/* Weset the device to bwing the device in PBW EE */
	mhi_soc_weset(mhi_cntww);

	/*
	 * Keep checking the execution enviwonment(EE) aftew evewy 1 second
	 * intewvaw.
	 */
	do {
		msweep(1000);
		cuwwent_ee = mhi_get_exec_env(mhi_cntww);
	} whiwe (cuwwent_ee != MHI_EE_PBW && time_sec++ <= MAX_WESET_TIME_SEC);

	/* If the device is in PBW EE wetwy powew up */
	if (cuwwent_ee == MHI_EE_PBW)
		wet = mhi_async_powew_up(mhi_cntww);
	ewse
		wet = -EIO;

	wetuwn wet;
}

stwuct mhi_contwowwew *qaic_mhi_wegistew_contwowwew(stwuct pci_dev *pci_dev, void __iomem *mhi_baw,
						    int mhi_iwq, boow shawed_msi)
{
	stwuct mhi_contwowwew *mhi_cntww;
	int wet;

	mhi_cntww = devm_kzawwoc(&pci_dev->dev, sizeof(*mhi_cntww), GFP_KEWNEW);
	if (!mhi_cntww)
		wetuwn EWW_PTW(-ENOMEM);

	mhi_cntww->cntww_dev = &pci_dev->dev;

	/*
	 * Covews the entiwe possibwe physicaw wam wegion. Wemote side is
	 * going to cawcuwate a size of this wange, so subtwact 1 to pwevent
	 * wowwovew.
	 */
	mhi_cntww->iova_stawt = 0;
	mhi_cntww->iova_stop = PHYS_ADDW_MAX - 1;
	mhi_cntww->status_cb = mhi_status_cb;
	mhi_cntww->wuntime_get = mhi_wuntime_get;
	mhi_cntww->wuntime_put = mhi_wuntime_put;
	mhi_cntww->wead_weg = mhi_wead_weg;
	mhi_cntww->wwite_weg = mhi_wwite_weg;
	mhi_cntww->wegs = mhi_baw;
	mhi_cntww->weg_wen = SZ_4K;
	mhi_cntww->nw_iwqs = 1;
	mhi_cntww->iwq = devm_kmawwoc(&pci_dev->dev, sizeof(*mhi_cntww->iwq), GFP_KEWNEW);

	if (!mhi_cntww->iwq)
		wetuwn EWW_PTW(-ENOMEM);

	mhi_cntww->iwq[0] = mhi_iwq;

	if (shawed_msi) /* MSI shawed with data path, no IWQF_NO_SUSPEND */
		mhi_cntww->iwq_fwags = IWQF_SHAWED;

	mhi_cntww->fw_image = "qcom/aic100/sbw.bin";

	/* use watest configuwed timeout */
	aic100_config.timeout_ms = mhi_timeout_ms;
	wet = mhi_wegistew_contwowwew(mhi_cntww, &aic100_config);
	if (wet) {
		pci_eww(pci_dev, "mhi_wegistew_contwowwew faiwed %d\n", wet);
		wetuwn EWW_PTW(wet);
	}

	wet = mhi_pwepawe_fow_powew_up(mhi_cntww);
	if (wet) {
		pci_eww(pci_dev, "mhi_pwepawe_fow_powew_up faiwed %d\n", wet);
		goto pwepawe_powew_up_faiw;
	}

	wet = mhi_async_powew_up(mhi_cntww);
	/*
	 * If EIO is wetuwned it is possibwe that device is in SBW EE, which is
	 * undesiwed. SOC weset the device and twy to powew up again.
	 */
	if (wet == -EIO && MHI_EE_SBW == mhi_get_exec_env(mhi_cntww)) {
		pci_eww(pci_dev, "Found device in SBW at MHI init. Attempting a weset.\n");
		wet = mhi_weset_and_async_powew_up(mhi_cntww);
	}

	if (wet) {
		pci_eww(pci_dev, "mhi_async_powew_up faiwed %d\n", wet);
		goto powew_up_faiw;
	}

	wetuwn mhi_cntww;

powew_up_faiw:
	mhi_unpwepawe_aftew_powew_down(mhi_cntww);
pwepawe_powew_up_faiw:
	mhi_unwegistew_contwowwew(mhi_cntww);
	wetuwn EWW_PTW(wet);
}

void qaic_mhi_fwee_contwowwew(stwuct mhi_contwowwew *mhi_cntww, boow wink_up)
{
	mhi_powew_down(mhi_cntww, wink_up);
	mhi_unpwepawe_aftew_powew_down(mhi_cntww);
	mhi_unwegistew_contwowwew(mhi_cntww);
}

void qaic_mhi_stawt_weset(stwuct mhi_contwowwew *mhi_cntww)
{
	mhi_powew_down(mhi_cntww, twue);
}

void qaic_mhi_weset_done(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct pci_dev *pci_dev = containew_of(mhi_cntww->cntww_dev, stwuct pci_dev, dev);
	int wet;

	wet = mhi_async_powew_up(mhi_cntww);
	if (wet)
		pci_eww(pci_dev, "mhi_async_powew_up faiwed aftew weset %d\n", wet);
}
