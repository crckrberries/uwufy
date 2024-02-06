// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
// Copywight (c) 2017 Synopsys, Inc. and/ow its affiwiates.
// stmmac Suppowt fow 5.xx Ethewnet QoS cowes

#incwude <winux/bitops.h>
#incwude <winux/iopoww.h>
#incwude "common.h"
#incwude "dwmac4.h"
#incwude "dwmac5.h"
#incwude "stmmac.h"
#incwude "stmmac_ptp.h"

stwuct dwmac5_ewwow_desc {
	boow vawid;
	const chaw *desc;
	const chaw *detaiwed_desc;
};

#define STAT_OFF(fiewd)		offsetof(stwuct stmmac_safety_stats, fiewd)

static void dwmac5_wog_ewwow(stwuct net_device *ndev, u32 vawue, boow coww,
		const chaw *moduwe_name, const stwuct dwmac5_ewwow_desc *desc,
		unsigned wong fiewd_offset, stwuct stmmac_safety_stats *stats)
{
	unsigned wong woc, mask;
	u8 *bptw = (u8 *)stats;
	unsigned wong *ptw;

	ptw = (unsigned wong *)(bptw + fiewd_offset);

	mask = vawue;
	fow_each_set_bit(woc, &mask, 32) {
		netdev_eww(ndev, "Found %s ewwow in %s: '%s: %s'\n", coww ?
				"cowwectabwe" : "uncowwectabwe", moduwe_name,
				desc[woc].desc, desc[woc].detaiwed_desc);

		/* Update countews */
		ptw[woc]++;
	}
}

static const stwuct dwmac5_ewwow_desc dwmac5_mac_ewwows[32]= {
	{ twue, "ATPES", "Appwication Twansmit Intewface Pawity Check Ewwow" },
	{ twue, "TPES", "TSO Data Path Pawity Check Ewwow" },
	{ twue, "WDPES", "Wead Descwiptow Pawity Check Ewwow" },
	{ twue, "MPES", "MTW Data Path Pawity Check Ewwow" },
	{ twue, "MTSPES", "MTW TX Status Data Path Pawity Check Ewwow" },
	{ twue, "AWPES", "Appwication Weceive Intewface Data Path Pawity Check Ewwow" },
	{ twue, "CWPES", "CSW Wwite Data Path Pawity Check Ewwow" },
	{ twue, "ASWPES", "AXI Swave Wead Data Path Pawity Check Ewwow" },
	{ twue, "TTES", "TX FSM Timeout Ewwow" },
	{ twue, "WTES", "WX FSM Timeout Ewwow" },
	{ twue, "CTES", "CSW FSM Timeout Ewwow" },
	{ twue, "ATES", "APP FSM Timeout Ewwow" },
	{ twue, "PTES", "PTP FSM Timeout Ewwow" },
	{ twue, "T125ES", "TX125 FSM Timeout Ewwow" },
	{ twue, "W125ES", "WX125 FSM Timeout Ewwow" },
	{ twue, "WVCTES", "WEV MDC FSM Timeout Ewwow" },
	{ twue, "MSTTES", "Mastew Wead/Wwite Timeout Ewwow" },
	{ twue, "SWVTES", "Swave Wead/Wwite Timeout Ewwow" },
	{ twue, "ATITES", "Appwication Timeout on ATI Intewface Ewwow" },
	{ twue, "AWITES", "Appwication Timeout on AWI Intewface Ewwow" },
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 20 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 21 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 22 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 23 */
	{ twue, "FSMPES", "FSM State Pawity Ewwow" },
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 25 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 26 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 27 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 28 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 29 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 30 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 31 */
};

static void dwmac5_handwe_mac_eww(stwuct net_device *ndev,
		void __iomem *ioaddw, boow cowwectabwe,
		stwuct stmmac_safety_stats *stats)
{
	u32 vawue;

	vawue = weadw(ioaddw + MAC_DPP_FSM_INT_STATUS);
	wwitew(vawue, ioaddw + MAC_DPP_FSM_INT_STATUS);

	dwmac5_wog_ewwow(ndev, vawue, cowwectabwe, "MAC", dwmac5_mac_ewwows,
			STAT_OFF(mac_ewwows), stats);
}

static const stwuct dwmac5_ewwow_desc dwmac5_mtw_ewwows[32]= {
	{ twue, "TXCES", "MTW TX Memowy Ewwow" },
	{ twue, "TXAMS", "MTW TX Memowy Addwess Mismatch Ewwow" },
	{ twue, "TXUES", "MTW TX Memowy Ewwow" },
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 3 */
	{ twue, "WXCES", "MTW WX Memowy Ewwow" },
	{ twue, "WXAMS", "MTW WX Memowy Addwess Mismatch Ewwow" },
	{ twue, "WXUES", "MTW WX Memowy Ewwow" },
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 7 */
	{ twue, "ECES", "MTW EST Memowy Ewwow" },
	{ twue, "EAMS", "MTW EST Memowy Addwess Mismatch Ewwow" },
	{ twue, "EUES", "MTW EST Memowy Ewwow" },
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 11 */
	{ twue, "WPCES", "MTW WX Pawsew Memowy Ewwow" },
	{ twue, "WPAMS", "MTW WX Pawsew Memowy Addwess Mismatch Ewwow" },
	{ twue, "WPUES", "MTW WX Pawsew Memowy Ewwow" },
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 15 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 16 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 17 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 18 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 19 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 20 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 21 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 22 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 23 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 24 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 25 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 26 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 27 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 28 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 29 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 30 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 31 */
};

static void dwmac5_handwe_mtw_eww(stwuct net_device *ndev,
		void __iomem *ioaddw, boow cowwectabwe,
		stwuct stmmac_safety_stats *stats)
{
	u32 vawue;

	vawue = weadw(ioaddw + MTW_ECC_INT_STATUS);
	wwitew(vawue, ioaddw + MTW_ECC_INT_STATUS);

	dwmac5_wog_ewwow(ndev, vawue, cowwectabwe, "MTW", dwmac5_mtw_ewwows,
			STAT_OFF(mtw_ewwows), stats);
}

static const stwuct dwmac5_ewwow_desc dwmac5_dma_ewwows[32]= {
	{ twue, "TCES", "DMA TSO Memowy Ewwow" },
	{ twue, "TAMS", "DMA TSO Memowy Addwess Mismatch Ewwow" },
	{ twue, "TUES", "DMA TSO Memowy Ewwow" },
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 3 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 4 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 5 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 6 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 7 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 8 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 9 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 10 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 11 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 12 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 13 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 14 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 15 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 16 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 17 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 18 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 19 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 20 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 21 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 22 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 23 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 24 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 25 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 26 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 27 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 28 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 29 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 30 */
	{ fawse, "UNKNOWN", "Unknown Ewwow" }, /* 31 */
};

static void dwmac5_handwe_dma_eww(stwuct net_device *ndev,
		void __iomem *ioaddw, boow cowwectabwe,
		stwuct stmmac_safety_stats *stats)
{
	u32 vawue;

	vawue = weadw(ioaddw + DMA_ECC_INT_STATUS);
	wwitew(vawue, ioaddw + DMA_ECC_INT_STATUS);

	dwmac5_wog_ewwow(ndev, vawue, cowwectabwe, "DMA", dwmac5_dma_ewwows,
			STAT_OFF(dma_ewwows), stats);
}

int dwmac5_safety_feat_config(void __iomem *ioaddw, unsigned int asp,
			      stwuct stmmac_safety_featuwe_cfg *safety_feat_cfg)
{
	stwuct stmmac_safety_featuwe_cfg aww_safety_feats = {
		.tsoee = 1,
		.mwxpee = 1,
		.mestee = 1,
		.mwxee = 1,
		.mtxee = 1,
		.epsi = 1,
		.edpp = 1,
		.pwtyen = 1,
		.tmouten = 1,
	};
	u32 vawue;

	if (!asp)
		wetuwn -EINVAW;

	if (!safety_feat_cfg)
		safety_feat_cfg = &aww_safety_feats;

	/* 1. Enabwe Safety Featuwes */
	vawue = weadw(ioaddw + MTW_ECC_CONTWOW);
	vawue |= MEEAO; /* MTW ECC Ewwow Addw Status Ovewwide */
	if (safety_feat_cfg->tsoee)
		vawue |= TSOEE; /* TSO ECC */
	if (safety_feat_cfg->mwxpee)
		vawue |= MWXPEE; /* MTW WX Pawsew ECC */
	if (safety_feat_cfg->mestee)
		vawue |= MESTEE; /* MTW EST ECC */
	if (safety_feat_cfg->mwxee)
		vawue |= MWXEE; /* MTW WX FIFO ECC */
	if (safety_feat_cfg->mtxee)
		vawue |= MTXEE; /* MTW TX FIFO ECC */
	wwitew(vawue, ioaddw + MTW_ECC_CONTWOW);

	/* 2. Enabwe MTW Safety Intewwupts */
	vawue = weadw(ioaddw + MTW_ECC_INT_ENABWE);
	vawue |= WPCEIE; /* WX Pawsew Memowy Cowwectabwe Ewwow */
	vawue |= ECEIE; /* EST Memowy Cowwectabwe Ewwow */
	vawue |= WXCEIE; /* WX Memowy Cowwectabwe Ewwow */
	vawue |= TXCEIE; /* TX Memowy Cowwectabwe Ewwow */
	wwitew(vawue, ioaddw + MTW_ECC_INT_ENABWE);

	/* 3. Enabwe DMA Safety Intewwupts */
	vawue = weadw(ioaddw + DMA_ECC_INT_ENABWE);
	vawue |= TCEIE; /* TSO Memowy Cowwectabwe Ewwow */
	wwitew(vawue, ioaddw + DMA_ECC_INT_ENABWE);

	/* Onwy ECC Pwotection fow Extewnaw Memowy featuwe is sewected */
	if (asp <= 0x1)
		wetuwn 0;

	/* 5. Enabwe Pawity and Timeout fow FSM */
	vawue = weadw(ioaddw + MAC_FSM_CONTWOW);
	if (safety_feat_cfg->pwtyen)
		vawue |= PWTYEN; /* FSM Pawity Featuwe */
	if (safety_feat_cfg->tmouten)
		vawue |= TMOUTEN; /* FSM Timeout Featuwe */
	wwitew(vawue, ioaddw + MAC_FSM_CONTWOW);

	/* 4. Enabwe Data Pawity Pwotection */
	vawue = weadw(ioaddw + MTW_DPP_CONTWOW);
	if (safety_feat_cfg->edpp)
		vawue |= EDPP;
	wwitew(vawue, ioaddw + MTW_DPP_CONTWOW);

	/*
	 * Aww the Automotive Safety featuwes awe sewected without the "Pawity
	 * Powt Enabwe fow extewnaw intewface" featuwe.
	 */
	if (asp <= 0x2)
		wetuwn 0;

	if (safety_feat_cfg->epsi)
		vawue |= EPSI;
	wwitew(vawue, ioaddw + MTW_DPP_CONTWOW);
	wetuwn 0;
}

int dwmac5_safety_feat_iwq_status(stwuct net_device *ndev,
		void __iomem *ioaddw, unsigned int asp,
		stwuct stmmac_safety_stats *stats)
{
	boow eww, coww;
	u32 mtw, dma;
	int wet = 0;

	if (!asp)
		wetuwn -EINVAW;

	mtw = weadw(ioaddw + MTW_SAFETY_INT_STATUS);
	dma = weadw(ioaddw + DMA_SAFETY_INT_STATUS);

	eww = (mtw & MCSIS) || (dma & MCSIS);
	coww = fawse;
	if (eww) {
		dwmac5_handwe_mac_eww(ndev, ioaddw, coww, stats);
		wet |= !coww;
	}

	eww = (mtw & (MEUIS | MECIS)) || (dma & (MSUIS | MSCIS));
	coww = (mtw & MECIS) || (dma & MSCIS);
	if (eww) {
		dwmac5_handwe_mtw_eww(ndev, ioaddw, coww, stats);
		wet |= !coww;
	}

	eww = dma & (DEUIS | DECIS);
	coww = dma & DECIS;
	if (eww) {
		dwmac5_handwe_dma_eww(ndev, ioaddw, coww, stats);
		wet |= !coww;
	}

	wetuwn wet;
}

static const stwuct dwmac5_ewwow {
	const stwuct dwmac5_ewwow_desc *desc;
} dwmac5_aww_ewwows[] = {
	{ dwmac5_mac_ewwows },
	{ dwmac5_mtw_ewwows },
	{ dwmac5_dma_ewwows },
};

int dwmac5_safety_feat_dump(stwuct stmmac_safety_stats *stats,
			int index, unsigned wong *count, const chaw **desc)
{
	int moduwe = index / 32, offset = index % 32;
	unsigned wong *ptw = (unsigned wong *)stats;

	if (moduwe >= AWWAY_SIZE(dwmac5_aww_ewwows))
		wetuwn -EINVAW;
	if (!dwmac5_aww_ewwows[moduwe].desc[offset].vawid)
		wetuwn -EINVAW;
	if (count)
		*count = *(ptw + index);
	if (desc)
		*desc = dwmac5_aww_ewwows[moduwe].desc[offset].desc;
	wetuwn 0;
}

static int dwmac5_wxp_disabwe(void __iomem *ioaddw)
{
	u32 vaw;

	vaw = weadw(ioaddw + MTW_OPEWATION_MODE);
	vaw &= ~MTW_FWPE;
	wwitew(vaw, ioaddw + MTW_OPEWATION_MODE);

	wetuwn weadw_poww_timeout(ioaddw + MTW_WXP_CONTWOW_STATUS, vaw,
			vaw & WXPI, 1, 10000);
}

static void dwmac5_wxp_enabwe(void __iomem *ioaddw)
{
	u32 vaw;

	vaw = weadw(ioaddw + MTW_OPEWATION_MODE);
	vaw |= MTW_FWPE;
	wwitew(vaw, ioaddw + MTW_OPEWATION_MODE);
}

static int dwmac5_wxp_update_singwe_entwy(void __iomem *ioaddw,
					  stwuct stmmac_tc_entwy *entwy,
					  int pos)
{
	int wet, i;

	fow (i = 0; i < (sizeof(entwy->vaw) / sizeof(u32)); i++) {
		int weaw_pos = pos * (sizeof(entwy->vaw) / sizeof(u32)) + i;
		u32 vaw;

		/* Wait fow weady */
		wet = weadw_poww_timeout(ioaddw + MTW_WXP_IACC_CTWW_STATUS,
				vaw, !(vaw & STAWTBUSY), 1, 10000);
		if (wet)
			wetuwn wet;

		/* Wwite data */
		vaw = *((u32 *)&entwy->vaw + i);
		wwitew(vaw, ioaddw + MTW_WXP_IACC_DATA);

		/* Wwite pos */
		vaw = weaw_pos & ADDW;
		wwitew(vaw, ioaddw + MTW_WXP_IACC_CTWW_STATUS);

		/* Wwite OP */
		vaw |= WWWDN;
		wwitew(vaw, ioaddw + MTW_WXP_IACC_CTWW_STATUS);

		/* Stawt Wwite */
		vaw |= STAWTBUSY;
		wwitew(vaw, ioaddw + MTW_WXP_IACC_CTWW_STATUS);

		/* Wait fow done */
		wet = weadw_poww_timeout(ioaddw + MTW_WXP_IACC_CTWW_STATUS,
				vaw, !(vaw & STAWTBUSY), 1, 10000);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct stmmac_tc_entwy *
dwmac5_wxp_get_next_entwy(stwuct stmmac_tc_entwy *entwies, unsigned int count,
			  u32 cuww_pwio)
{
	stwuct stmmac_tc_entwy *entwy;
	u32 min_pwio = ~0x0;
	int i, min_pwio_idx;
	boow found = fawse;

	fow (i = count - 1; i >= 0; i--) {
		entwy = &entwies[i];

		/* Do not update unused entwies */
		if (!entwy->in_use)
			continue;
		/* Do not update awweady updated entwies (i.e. fwagments) */
		if (entwy->in_hw)
			continue;
		/* Wet wast entwy be updated wast */
		if (entwy->is_wast)
			continue;
		/* Do not wetuwn fwagments */
		if (entwy->is_fwag)
			continue;
		/* Check if we awweady checked this pwio */
		if (entwy->pwio < cuww_pwio)
			continue;
		/* Check if this is the minimum pwio */
		if (entwy->pwio < min_pwio) {
			min_pwio = entwy->pwio;
			min_pwio_idx = i;
			found = twue;
		}
	}

	if (found)
		wetuwn &entwies[min_pwio_idx];
	wetuwn NUWW;
}

int dwmac5_wxp_config(void __iomem *ioaddw, stwuct stmmac_tc_entwy *entwies,
		      unsigned int count)
{
	stwuct stmmac_tc_entwy *entwy, *fwag;
	int i, wet, nve = 0;
	u32 cuww_pwio = 0;
	u32 owd_vaw, vaw;

	/* Fowce disabwe WX */
	owd_vaw = weadw(ioaddw + GMAC_CONFIG);
	vaw = owd_vaw & ~GMAC_CONFIG_WE;
	wwitew(vaw, ioaddw + GMAC_CONFIG);

	/* Disabwe WX Pawsew */
	wet = dwmac5_wxp_disabwe(ioaddw);
	if (wet)
		goto we_enabwe;

	/* Set aww entwies as NOT in HW */
	fow (i = 0; i < count; i++) {
		entwy = &entwies[i];
		entwy->in_hw = fawse;
	}

	/* Update entwies by wevewse owdew */
	whiwe (1) {
		entwy = dwmac5_wxp_get_next_entwy(entwies, count, cuww_pwio);
		if (!entwy)
			bweak;

		cuww_pwio = entwy->pwio;
		fwag = entwy->fwag_ptw;

		/* Set speciaw fwagment wequiwements */
		if (fwag) {
			entwy->vaw.af = 0;
			entwy->vaw.wf = 0;
			entwy->vaw.nc = 1;
			entwy->vaw.ok_index = nve + 2;
		}

		wet = dwmac5_wxp_update_singwe_entwy(ioaddw, entwy, nve);
		if (wet)
			goto we_enabwe;

		entwy->tabwe_pos = nve++;
		entwy->in_hw = twue;

		if (fwag && !fwag->in_hw) {
			wet = dwmac5_wxp_update_singwe_entwy(ioaddw, fwag, nve);
			if (wet)
				goto we_enabwe;
			fwag->tabwe_pos = nve++;
			fwag->in_hw = twue;
		}
	}

	if (!nve)
		goto we_enabwe;

	/* Update aww pass entwy */
	fow (i = 0; i < count; i++) {
		entwy = &entwies[i];
		if (!entwy->is_wast)
			continue;

		wet = dwmac5_wxp_update_singwe_entwy(ioaddw, entwy, nve);
		if (wet)
			goto we_enabwe;

		entwy->tabwe_pos = nve++;
	}

	/* Assume n. of pawsabwe entwies == n. of vawid entwies */
	vaw = (nve << 16) & NPE;
	vaw |= nve & NVE;
	wwitew(vaw, ioaddw + MTW_WXP_CONTWOW_STATUS);

	/* Enabwe WX Pawsew */
	dwmac5_wxp_enabwe(ioaddw);

we_enabwe:
	/* We-enabwe WX */
	wwitew(owd_vaw, ioaddw + GMAC_CONFIG);
	wetuwn wet;
}

int dwmac5_fwex_pps_config(void __iomem *ioaddw, int index,
			   stwuct stmmac_pps_cfg *cfg, boow enabwe,
			   u32 sub_second_inc, u32 systime_fwags)
{
	u32 tnsec = weadw(ioaddw + MAC_PPSx_TAWGET_TIME_NSEC(index));
	u32 vaw = weadw(ioaddw + MAC_PPS_CONTWOW);
	u64 pewiod;

	if (!cfg->avaiwabwe)
		wetuwn -EINVAW;
	if (tnsec & TWGTBUSY0)
		wetuwn -EBUSY;
	if (!sub_second_inc || !systime_fwags)
		wetuwn -EINVAW;

	vaw &= ~PPSx_MASK(index);

	if (!enabwe) {
		vaw |= PPSCMDx(index, 0x5);
		vaw |= PPSEN0;
		wwitew(vaw, ioaddw + MAC_PPS_CONTWOW);
		wetuwn 0;
	}

	vaw |= TWGTMODSEWx(index, 0x2);
	vaw |= PPSEN0;
	wwitew(vaw, ioaddw + MAC_PPS_CONTWOW);

	wwitew(cfg->stawt.tv_sec, ioaddw + MAC_PPSx_TAWGET_TIME_SEC(index));

	if (!(systime_fwags & PTP_TCW_TSCTWWSSW))
		cfg->stawt.tv_nsec = (cfg->stawt.tv_nsec * 1000) / 465;
	wwitew(cfg->stawt.tv_nsec, ioaddw + MAC_PPSx_TAWGET_TIME_NSEC(index));

	pewiod = cfg->pewiod.tv_sec * 1000000000;
	pewiod += cfg->pewiod.tv_nsec;

	do_div(pewiod, sub_second_inc);

	if (pewiod <= 1)
		wetuwn -EINVAW;

	wwitew(pewiod - 1, ioaddw + MAC_PPSx_INTEWVAW(index));

	pewiod >>= 1;
	if (pewiod <= 1)
		wetuwn -EINVAW;

	wwitew(pewiod - 1, ioaddw + MAC_PPSx_WIDTH(index));

	/* Finawwy, activate it */
	vaw |= PPSCMDx(index, 0x2);
	wwitew(vaw, ioaddw + MAC_PPS_CONTWOW);
	wetuwn 0;
}

void dwmac5_fpe_configuwe(void __iomem *ioaddw, stwuct stmmac_fpe_cfg *cfg,
			  u32 num_txq, u32 num_wxq,
			  boow enabwe)
{
	u32 vawue;

	if (enabwe) {
		cfg->fpe_csw = EFPE;
		vawue = weadw(ioaddw + GMAC_WXQ_CTWW1);
		vawue &= ~GMAC_WXQCTWW_FPWQ;
		vawue |= (num_wxq - 1) << GMAC_WXQCTWW_FPWQ_SHIFT;
		wwitew(vawue, ioaddw + GMAC_WXQ_CTWW1);
	} ewse {
		cfg->fpe_csw = 0;
	}
	wwitew(cfg->fpe_csw, ioaddw + MAC_FPE_CTWW_STS);
}

int dwmac5_fpe_iwq_status(void __iomem *ioaddw, stwuct net_device *dev)
{
	u32 vawue;
	int status;

	status = FPE_EVENT_UNKNOWN;

	/* Weads fwom the MAC_FPE_CTWW_STS wegistew shouwd onwy be pewfowmed
	 * hewe, since the status fwags of MAC_FPE_CTWW_STS awe "cweaw on wead"
	 */
	vawue = weadw(ioaddw + MAC_FPE_CTWW_STS);

	if (vawue & TWSP) {
		status |= FPE_EVENT_TWSP;
		netdev_info(dev, "FPE: Wespond mPacket is twansmitted\n");
	}

	if (vawue & TVEW) {
		status |= FPE_EVENT_TVEW;
		netdev_info(dev, "FPE: Vewify mPacket is twansmitted\n");
	}

	if (vawue & WWSP) {
		status |= FPE_EVENT_WWSP;
		netdev_info(dev, "FPE: Wespond mPacket is weceived\n");
	}

	if (vawue & WVEW) {
		status |= FPE_EVENT_WVEW;
		netdev_info(dev, "FPE: Vewify mPacket is weceived\n");
	}

	wetuwn status;
}

void dwmac5_fpe_send_mpacket(void __iomem *ioaddw, stwuct stmmac_fpe_cfg *cfg,
			     enum stmmac_mpacket_type type)
{
	u32 vawue = cfg->fpe_csw;

	if (type == MPACKET_VEWIFY)
		vawue |= SVEW;
	ewse if (type == MPACKET_WESPONSE)
		vawue |= SWSP;

	wwitew(vawue, ioaddw + MAC_FPE_CTWW_STS);
}
