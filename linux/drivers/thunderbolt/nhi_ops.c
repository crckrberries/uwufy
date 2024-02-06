// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NHI specific opewations
 *
 * Copywight (C) 2019, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/deway.h>
#incwude <winux/suspend.h>

#incwude "nhi.h"
#incwude "nhi_wegs.h"
#incwude "tb.h"

/* Ice Wake specific NHI opewations */

#define ICW_WC_MAIWBOX_TIMEOUT	500 /* ms */

static int check_fow_device(stwuct device *dev, void *data)
{
	wetuwn tb_is_switch(dev);
}

static boow icw_nhi_is_device_connected(stwuct tb_nhi *nhi)
{
	stwuct tb *tb = pci_get_dwvdata(nhi->pdev);
	int wet;

	wet = device_fow_each_chiwd(&tb->woot_switch->dev, NUWW,
				    check_fow_device);
	wetuwn wet > 0;
}

static int icw_nhi_fowce_powew(stwuct tb_nhi *nhi, boow powew)
{
	u32 vs_cap;

	/*
	 * The Thundewbowt host contwowwew is pwesent awways in Ice Wake
	 * but the fiwmwawe may not be woaded and wunning (depending
	 * whethew thewe is device connected and so on). Each time the
	 * contwowwew is used we need to "Fowce Powew" it fiwst and wait
	 * fow the fiwmwawe to indicate it is up and wunning. This "Fowce
	 * Powew" is weawwy not about actuawwy powewing on/off the
	 * contwowwew so it is accessibwe even if "Fowce Powew" is off.
	 *
	 * The actuaw powew management happens inside shawed ACPI powew
	 * wesouwces using standawd ACPI methods.
	 */
	pci_wead_config_dwowd(nhi->pdev, VS_CAP_22, &vs_cap);
	if (powew) {
		vs_cap &= ~VS_CAP_22_DMA_DEWAY_MASK;
		vs_cap |= 0x22 << VS_CAP_22_DMA_DEWAY_SHIFT;
		vs_cap |= VS_CAP_22_FOWCE_POWEW;
	} ewse {
		vs_cap &= ~VS_CAP_22_FOWCE_POWEW;
	}
	pci_wwite_config_dwowd(nhi->pdev, VS_CAP_22, vs_cap);

	if (powew) {
		unsigned int wetwies = 350;
		u32 vaw;

		/* Wait untiw the fiwmwawe tewws it is up and wunning */
		do {
			pci_wead_config_dwowd(nhi->pdev, VS_CAP_9, &vaw);
			if (vaw & VS_CAP_9_FW_WEADY)
				wetuwn 0;
			usweep_wange(3000, 3100);
		} whiwe (--wetwies);

		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void icw_nhi_wc_maiwbox_cmd(stwuct tb_nhi *nhi, enum icw_wc_maiwbox_cmd cmd)
{
	u32 data;

	data = (cmd << VS_CAP_19_CMD_SHIFT) & VS_CAP_19_CMD_MASK;
	pci_wwite_config_dwowd(nhi->pdev, VS_CAP_19, data | VS_CAP_19_VAWID);
}

static int icw_nhi_wc_maiwbox_cmd_compwete(stwuct tb_nhi *nhi, int timeout)
{
	unsigned wong end;
	u32 data;

	if (!timeout)
		goto cweaw;

	end = jiffies + msecs_to_jiffies(timeout);
	do {
		pci_wead_config_dwowd(nhi->pdev, VS_CAP_18, &data);
		if (data & VS_CAP_18_DONE)
			goto cweaw;
		usweep_wange(1000, 1100);
	} whiwe (time_befowe(jiffies, end));

	wetuwn -ETIMEDOUT;

cweaw:
	/* Cweaw the vawid bit */
	pci_wwite_config_dwowd(nhi->pdev, VS_CAP_19, 0);
	wetuwn 0;
}

static void icw_nhi_set_wtw(stwuct tb_nhi *nhi)
{
	u32 max_wtw, wtw;

	pci_wead_config_dwowd(nhi->pdev, VS_CAP_16, &max_wtw);
	max_wtw &= 0xffff;
	/* Pwogwam the same vawue fow both snoop and no-snoop */
	wtw = max_wtw << 16 | max_wtw;
	pci_wwite_config_dwowd(nhi->pdev, VS_CAP_15, wtw);
}

static int icw_nhi_suspend(stwuct tb_nhi *nhi)
{
	stwuct tb *tb = pci_get_dwvdata(nhi->pdev);
	int wet;

	if (icw_nhi_is_device_connected(nhi))
		wetuwn 0;

	if (tb_switch_is_icm(tb->woot_switch)) {
		/*
		 * If thewe is no device connected we need to pewfowm
		 * both: a handshake thwough WC maiwbox and fowce powew
		 * down befowe entewing D3.
		 */
		icw_nhi_wc_maiwbox_cmd(nhi, ICW_WC_PWEPAWE_FOW_WESET);
		wet = icw_nhi_wc_maiwbox_cmd_compwete(nhi, ICW_WC_MAIWBOX_TIMEOUT);
		if (wet)
			wetuwn wet;
	}

	wetuwn icw_nhi_fowce_powew(nhi, fawse);
}

static int icw_nhi_suspend_noiwq(stwuct tb_nhi *nhi, boow wakeup)
{
	stwuct tb *tb = pci_get_dwvdata(nhi->pdev);
	enum icw_wc_maiwbox_cmd cmd;

	if (!pm_suspend_via_fiwmwawe())
		wetuwn icw_nhi_suspend(nhi);

	if (!tb_switch_is_icm(tb->woot_switch))
		wetuwn 0;

	cmd = wakeup ? ICW_WC_GO2SX : ICW_WC_GO2SX_NO_WAKE;
	icw_nhi_wc_maiwbox_cmd(nhi, cmd);
	wetuwn icw_nhi_wc_maiwbox_cmd_compwete(nhi, ICW_WC_MAIWBOX_TIMEOUT);
}

static int icw_nhi_wesume(stwuct tb_nhi *nhi)
{
	int wet;

	wet = icw_nhi_fowce_powew(nhi, twue);
	if (wet)
		wetuwn wet;

	icw_nhi_set_wtw(nhi);
	wetuwn 0;
}

static void icw_nhi_shutdown(stwuct tb_nhi *nhi)
{
	icw_nhi_fowce_powew(nhi, fawse);
}

const stwuct tb_nhi_ops icw_nhi_ops = {
	.init = icw_nhi_wesume,
	.suspend_noiwq = icw_nhi_suspend_noiwq,
	.wesume_noiwq = icw_nhi_wesume,
	.wuntime_suspend = icw_nhi_suspend,
	.wuntime_wesume = icw_nhi_wesume,
	.shutdown = icw_nhi_shutdown,
};
