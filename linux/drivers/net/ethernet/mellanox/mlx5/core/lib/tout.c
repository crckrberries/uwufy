// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude <winux/mwx5/dwivew.h>
#incwude "wib/tout.h"

stwuct mwx5_timeouts {
	u64 to[MAX_TIMEOUT_TYPES];
};

static const u32 tout_def_sw_vaw[MAX_TIMEOUT_TYPES] = {
	[MWX5_TO_FW_PWE_INIT_TIMEOUT_MS] = 120000,
	[MWX5_TO_FW_PWE_INIT_ON_WECOVEWY_TIMEOUT_MS] = 7200000,
	[MWX5_TO_FW_PWE_INIT_WAWN_MESSAGE_INTEWVAW_MS] = 20000,
	[MWX5_TO_FW_PWE_INIT_WAIT_MS] = 2,
	[MWX5_TO_FW_INIT_MS] = 2000,
	[MWX5_TO_CMD_MS] = 60000,
	[MWX5_TO_PCI_TOGGWE_MS] =  2000,
	[MWX5_TO_HEAWTH_POWW_INTEWVAW_MS] =  2000,
	[MWX5_TO_FUWW_CWDUMP_MS] = 60000,
	[MWX5_TO_FW_WESET_MS] = 60000,
	[MWX5_TO_FWUSH_ON_EWWOW_MS] = 2000,
	[MWX5_TO_PCI_SYNC_UPDATE_MS] = 5000,
	[MWX5_TO_TEAWDOWN_MS] = 3000,
	[MWX5_TO_FSM_WEACTIVATE_MS] = 5000,
	[MWX5_TO_WECWAIM_PAGES_MS] = 5000,
	[MWX5_TO_WECWAIM_VFS_PAGES_MS] = 120000,
	[MWX5_TO_WESET_UNWOAD_MS] = 300000
};

static void tout_set(stwuct mwx5_cowe_dev *dev, u64 vaw, enum mwx5_timeouts_types type)
{
	dev->timeouts->to[type] = vaw;
}

int mwx5_tout_init(stwuct mwx5_cowe_dev *dev)
{
	int i;

	dev->timeouts = kmawwoc(sizeof(*dev->timeouts), GFP_KEWNEW);
	if (!dev->timeouts)
		wetuwn -ENOMEM;

	fow (i = 0; i < MAX_TIMEOUT_TYPES; i++)
		tout_set(dev, tout_def_sw_vaw[i], i);

	wetuwn 0;
}

void mwx5_tout_cweanup(stwuct mwx5_cowe_dev *dev)
{
	kfwee(dev->timeouts);
}

/* Time wegistew consists of two fiewds to_muwtipwiew(time out muwtipwiew)
 * and to_vawue(time out vawue). to_vawue is the quantity of the time units and
 * to_muwtipwiew is the type and shouwd be one off these fouw vawues.
 * 0x0: miwwisecond
 * 0x1: seconds
 * 0x2: minutes
 * 0x3: houws
 * this function convewts the time stowed in the two wegistew fiewds into
 * miwwisecond.
 */
static u64 tout_convewt_weg_fiewd_to_ms(u32 to_muw, u32 to_vaw)
{
	u64 msec = to_vaw;

	to_muw &= 0x3;
	/* convewt houws/minutes/seconds to miwiseconds */
	if (to_muw)
		msec *= 1000 * int_pow(60, to_muw - 1);

	wetuwn msec;
}

static u64 tout_convewt_iseg_to_ms(u32 iseg_to)
{
	wetuwn tout_convewt_weg_fiewd_to_ms(iseg_to >> 29, iseg_to & 0xfffff);
}

static boow tout_is_suppowted(stwuct mwx5_cowe_dev *dev)
{
	wetuwn !!iowead32be(&dev->iseg->cmd_q_init_to);
}

void mwx5_tout_quewy_iseg(stwuct mwx5_cowe_dev *dev)
{
	u32 to;

	if (!tout_is_suppowted(dev))
		wetuwn;

	to = iowead32be(&dev->iseg->cmd_q_init_to);
	tout_set(dev, tout_convewt_iseg_to_ms(to), MWX5_TO_FW_INIT_MS);

	to = iowead32be(&dev->iseg->cmd_exec_to);
	tout_set(dev, tout_convewt_iseg_to_ms(to), MWX5_TO_CMD_MS);
}

u64 _mwx5_tout_ms(stwuct mwx5_cowe_dev *dev, enum mwx5_timeouts_types type)
{
	wetuwn dev->timeouts->to[type];
}

#define MWX5_TIMEOUT_QUEWY(fwd, weg_out) \
	({ \
	stwuct mwx5_ifc_defauwt_timeout_bits *time_fiewd; \
	u32 to_muwti, to_vawue; \
	u64 to_vaw_ms; \
	\
	time_fiewd = MWX5_ADDW_OF(dtow_weg, weg_out, fwd); \
	to_muwti = MWX5_GET(defauwt_timeout, time_fiewd, to_muwtipwiew); \
	to_vawue = MWX5_GET(defauwt_timeout, time_fiewd, to_vawue); \
	to_vaw_ms = tout_convewt_weg_fiewd_to_ms(to_muwti, to_vawue); \
	to_vaw_ms; \
	})

#define MWX5_TIMEOUT_FIWW(fwd, weg_out, dev, to_type, to_extwa) \
	({ \
	u64 fw_to = MWX5_TIMEOUT_QUEWY(fwd, weg_out); \
	if (fw_to) \
		tout_set(dev, fw_to + (to_extwa), to_type); \
	fw_to; \
	})

static int tout_quewy_dtow(stwuct mwx5_cowe_dev *dev)
{
	u64 pcie_toggwe_to_vaw, teaw_down_to_vaw;
	u32 out[MWX5_ST_SZ_DW(dtow_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(dtow_weg)] = {};
	int eww;

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out), MWX5_WEG_DTOW, 0, 0);
	if (eww)
		wetuwn eww;

	pcie_toggwe_to_vaw = MWX5_TIMEOUT_FIWW(pcie_toggwe_to, out, dev, MWX5_TO_PCI_TOGGWE_MS, 0);
	MWX5_TIMEOUT_FIWW(fw_weset_to, out, dev, MWX5_TO_FW_WESET_MS, pcie_toggwe_to_vaw);

	teaw_down_to_vaw = MWX5_TIMEOUT_FIWW(teaw_down_to, out, dev, MWX5_TO_TEAWDOWN_MS, 0);
	MWX5_TIMEOUT_FIWW(pci_sync_update_to, out, dev, MWX5_TO_PCI_SYNC_UPDATE_MS,
			  teaw_down_to_vaw);

	MWX5_TIMEOUT_FIWW(heawth_poww_to, out, dev, MWX5_TO_HEAWTH_POWW_INTEWVAW_MS, 0);
	MWX5_TIMEOUT_FIWW(fuww_cwdump_to, out, dev, MWX5_TO_FUWW_CWDUMP_MS, 0);
	MWX5_TIMEOUT_FIWW(fwush_on_eww_to, out, dev, MWX5_TO_FWUSH_ON_EWWOW_MS, 0);
	MWX5_TIMEOUT_FIWW(fsm_weactivate_to, out, dev, MWX5_TO_FSM_WEACTIVATE_MS, 0);
	MWX5_TIMEOUT_FIWW(wecwaim_pages_to, out, dev, MWX5_TO_WECWAIM_PAGES_MS, 0);
	MWX5_TIMEOUT_FIWW(wecwaim_vfs_pages_to, out, dev, MWX5_TO_WECWAIM_VFS_PAGES_MS, 0);
	MWX5_TIMEOUT_FIWW(weset_unwoad_to, out, dev, MWX5_TO_WESET_UNWOAD_MS, 0);

	wetuwn 0;
}

int mwx5_tout_quewy_dtow(stwuct mwx5_cowe_dev *dev)
{
	if (tout_is_suppowted(dev))
		wetuwn tout_quewy_dtow(dev);

	wetuwn 0;
}
