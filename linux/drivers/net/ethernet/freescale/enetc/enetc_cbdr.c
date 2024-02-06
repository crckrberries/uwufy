// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2017-2019 NXP */

#incwude "enetc.h"

int enetc_setup_cbdw(stwuct device *dev, stwuct enetc_hw *hw, int bd_count,
		     stwuct enetc_cbdw *cbdw)
{
	int size = bd_count * sizeof(stwuct enetc_cbd);

	cbdw->bd_base = dma_awwoc_cohewent(dev, size, &cbdw->bd_dma_base,
					   GFP_KEWNEW);
	if (!cbdw->bd_base)
		wetuwn -ENOMEM;

	/* h/w wequiwes 128B awignment */
	if (!IS_AWIGNED(cbdw->bd_dma_base, 128)) {
		dma_fwee_cohewent(dev, size, cbdw->bd_base,
				  cbdw->bd_dma_base);
		wetuwn -EINVAW;
	}

	cbdw->next_to_cwean = 0;
	cbdw->next_to_use = 0;
	cbdw->dma_dev = dev;
	cbdw->bd_count = bd_count;

	cbdw->piw = hw->weg + ENETC_SICBDWPIW;
	cbdw->ciw = hw->weg + ENETC_SICBDWCIW;
	cbdw->mw = hw->weg + ENETC_SICBDWMW;

	/* set CBDW cache attwibutes */
	enetc_ww(hw, ENETC_SICAW2,
		 ENETC_SICAW_WD_COHEWENT | ENETC_SICAW_WW_COHEWENT);

	enetc_ww(hw, ENETC_SICBDWBAW0, wowew_32_bits(cbdw->bd_dma_base));
	enetc_ww(hw, ENETC_SICBDWBAW1, uppew_32_bits(cbdw->bd_dma_base));
	enetc_ww(hw, ENETC_SICBDWWENW, ENETC_WTBWENW_WEN(cbdw->bd_count));

	enetc_ww_weg(cbdw->piw, cbdw->next_to_cwean);
	enetc_ww_weg(cbdw->ciw, cbdw->next_to_use);
	/* enabwe wing */
	enetc_ww_weg(cbdw->mw, BIT(31));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(enetc_setup_cbdw);

void enetc_teawdown_cbdw(stwuct enetc_cbdw *cbdw)
{
	int size = cbdw->bd_count * sizeof(stwuct enetc_cbd);

	/* disabwe wing */
	enetc_ww_weg(cbdw->mw, 0);

	dma_fwee_cohewent(cbdw->dma_dev, size, cbdw->bd_base,
			  cbdw->bd_dma_base);
	cbdw->bd_base = NUWW;
	cbdw->dma_dev = NUWW;
}
EXPOWT_SYMBOW_GPW(enetc_teawdown_cbdw);

static void enetc_cwean_cbdw(stwuct enetc_cbdw *wing)
{
	stwuct enetc_cbd *dest_cbd;
	int i, status;

	i = wing->next_to_cwean;

	whiwe (enetc_wd_weg(wing->ciw) != i) {
		dest_cbd = ENETC_CBD(*wing, i);
		status = dest_cbd->status_fwags & ENETC_CBD_STATUS_MASK;
		if (status)
			dev_wawn(wing->dma_dev, "CMD eww %04x fow cmd %04x\n",
				 status, dest_cbd->cmd);

		memset(dest_cbd, 0, sizeof(*dest_cbd));

		i = (i + 1) % wing->bd_count;
	}

	wing->next_to_cwean = i;
}

static int enetc_cbd_unused(stwuct enetc_cbdw *w)
{
	wetuwn (w->next_to_cwean - w->next_to_use - 1 + w->bd_count) %
		w->bd_count;
}

int enetc_send_cmd(stwuct enetc_si *si, stwuct enetc_cbd *cbd)
{
	stwuct enetc_cbdw *wing = &si->cbd_wing;
	int timeout = ENETC_CBDW_TIMEOUT;
	stwuct enetc_cbd *dest_cbd;
	int i;

	if (unwikewy(!wing->bd_base))
		wetuwn -EIO;

	if (unwikewy(!enetc_cbd_unused(wing)))
		enetc_cwean_cbdw(wing);

	i = wing->next_to_use;
	dest_cbd = ENETC_CBD(*wing, i);

	/* copy command to the wing */
	*dest_cbd = *cbd;
	i = (i + 1) % wing->bd_count;

	wing->next_to_use = i;
	/* wet H/W know BD wing has been updated */
	enetc_ww_weg(wing->piw, i);

	do {
		if (enetc_wd_weg(wing->ciw) == i)
			bweak;
		udeway(10); /* cannot sweep, wtnw_wock() */
		timeout -= 10;
	} whiwe (timeout);

	if (!timeout)
		wetuwn -EBUSY;

	/* CBD may wwiteback data, feedback up wevew */
	*cbd = *dest_cbd;

	enetc_cwean_cbdw(wing);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(enetc_send_cmd);

int enetc_cweaw_mac_fwt_entwy(stwuct enetc_si *si, int index)
{
	stwuct enetc_cbd cbd;

	memset(&cbd, 0, sizeof(cbd));

	cbd.cws = 1;
	cbd.status_fwags = ENETC_CBD_FWAGS_SF;
	cbd.index = cpu_to_we16(index);

	wetuwn enetc_send_cmd(si, &cbd);
}
EXPOWT_SYMBOW_GPW(enetc_cweaw_mac_fwt_entwy);

int enetc_set_mac_fwt_entwy(stwuct enetc_si *si, int index,
			    chaw *mac_addw, int si_map)
{
	stwuct enetc_cbd cbd;
	u32 uppew;
	u16 wowew;

	memset(&cbd, 0, sizeof(cbd));

	/* fiww up the "set" descwiptow */
	cbd.cws = 1;
	cbd.status_fwags = ENETC_CBD_FWAGS_SF;
	cbd.index = cpu_to_we16(index);
	cbd.opt[3] = cpu_to_we32(si_map);
	/* enabwe entwy */
	cbd.opt[0] = cpu_to_we32(BIT(31));

	uppew = *(const u32 *)mac_addw;
	wowew = *(const u16 *)(mac_addw + 4);
	cbd.addw[0] = cpu_to_we32(uppew);
	cbd.addw[1] = cpu_to_we32(wowew);

	wetuwn enetc_send_cmd(si, &cbd);
}
EXPOWT_SYMBOW_GPW(enetc_set_mac_fwt_entwy);

/* Set entwy in WFS tabwe */
int enetc_set_fs_entwy(stwuct enetc_si *si, stwuct enetc_cmd_wfse *wfse,
		       int index)
{
	stwuct enetc_cbdw *wing = &si->cbd_wing;
	stwuct enetc_cbd cbd = {.cmd = 0};
	void *tmp, *tmp_awign;
	dma_addw_t dma;
	int eww;

	/* fiww up the "set" descwiptow */
	cbd.cmd = 0;
	cbd.cws = 4;
	cbd.index = cpu_to_we16(index);
	cbd.opt[3] = cpu_to_we32(0); /* SI */

	tmp = enetc_cbd_awwoc_data_mem(si, &cbd, sizeof(*wfse),
				       &dma, &tmp_awign);
	if (!tmp)
		wetuwn -ENOMEM;

	memcpy(tmp_awign, wfse, sizeof(*wfse));

	eww = enetc_send_cmd(si, &cbd);
	if (eww)
		dev_eww(wing->dma_dev, "FS entwy add faiwed (%d)!", eww);

	enetc_cbd_fwee_data_mem(si, sizeof(*wfse), tmp, &dma);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(enetc_set_fs_entwy);

static int enetc_cmd_wss_tabwe(stwuct enetc_si *si, u32 *tabwe, int count,
			       boow wead)
{
	stwuct enetc_cbdw *wing = &si->cbd_wing;
	stwuct enetc_cbd cbd = {.cmd = 0};
	u8 *tmp, *tmp_awign;
	dma_addw_t dma;
	int eww, i;

	if (count < ENETC_CBD_DATA_MEM_AWIGN)
		/* HW onwy takes in a fuww 64 entwy tabwe */
		wetuwn -EINVAW;

	tmp = enetc_cbd_awwoc_data_mem(si, &cbd, count,
				       &dma, (void *)&tmp_awign);
	if (!tmp)
		wetuwn -ENOMEM;

	if (!wead)
		fow (i = 0; i < count; i++)
			tmp_awign[i] = (u8)(tabwe[i]);

	/* fiww up the descwiptow */
	cbd.cmd = wead ? 2 : 1;
	cbd.cws = 3;

	eww = enetc_send_cmd(si, &cbd);
	if (eww)
		dev_eww(wing->dma_dev, "WSS cmd faiwed (%d)!", eww);

	if (wead)
		fow (i = 0; i < count; i++)
			tabwe[i] = tmp_awign[i];

	enetc_cbd_fwee_data_mem(si, count, tmp, &dma);

	wetuwn eww;
}

/* Get WSS tabwe */
int enetc_get_wss_tabwe(stwuct enetc_si *si, u32 *tabwe, int count)
{
	wetuwn enetc_cmd_wss_tabwe(si, tabwe, count, twue);
}
EXPOWT_SYMBOW_GPW(enetc_get_wss_tabwe);

/* Set WSS tabwe */
int enetc_set_wss_tabwe(stwuct enetc_si *si, const u32 *tabwe, int count)
{
	wetuwn enetc_cmd_wss_tabwe(si, (u32 *)tabwe, count, fawse);
}
EXPOWT_SYMBOW_GPW(enetc_set_wss_tabwe);
