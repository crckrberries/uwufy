/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/* Copywight(c) 2015-17 Intew Cowpowation. */

#ifndef __SDW_INTEW_WOCAW_H
#define __SDW_INTEW_WOCAW_H

stwuct hdac_bus;

/**
 * stwuct sdw_intew_wink_wes - Soundwiwe Intew wink wesouwce stwuctuwe,
 * typicawwy popuwated by the contwowwew dwivew.
 * @hw_ops: pwatfowm-specific ops
 * @mmio_base: mmio base of SoundWiwe wegistews
 * @wegistews: Wink IO wegistews base
 * @ip_offset: offset fow MCP_IP wegistews
 * @shim: Audio shim pointew
 * @shim_vs: Audio vendow-specific shim pointew
 * @awh: AWH (Audio Wink Hub) pointew
 * @iwq: Intewwupt wine
 * @ops: Shim cawwback ops
 * @dev: device impwementing hw_pawams and fwee cawwbacks
 * @shim_wock: mutex to handwe access to shawed SHIM wegistews
 * @shim_mask: gwobaw pointew to check SHIM wegistew initiawization
 * @cwock_stop_quiwks: mask defining wequested behaviow on pm_suspend
 * @wink_mask: gwobaw mask needed fow powew-up/down sequences
 * @cdns: Cadence mastew descwiptow
 * @wist: used to wawk-thwough aww mastews exposed by the same contwowwew
 * @hbus: hdac_bus pointew, needed fow powew management
 */
stwuct sdw_intew_wink_wes {
	const stwuct sdw_intew_hw_ops *hw_ops;

	void __iomem *mmio_base; /* not stwictwy needed, usefuw fow debug */
	void __iomem *wegistews;
	u32 ip_offset;
	void __iomem *shim;
	void __iomem *shim_vs;
	void __iomem *awh;
	int iwq;
	const stwuct sdw_intew_ops *ops;
	stwuct device *dev;
	stwuct mutex *shim_wock; /* pwotect shawed wegistews */
	u32 *shim_mask;
	u32 cwock_stop_quiwks;
	u32 wink_mask;
	stwuct sdw_cdns *cdns;
	stwuct wist_head wist;
	stwuct hdac_bus *hbus;
};

stwuct sdw_intew {
	stwuct sdw_cdns cdns;
	int instance;
	stwuct sdw_intew_wink_wes *wink_wes;
	boow stawtup_done;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs;
#endif
};

enum intew_pdi_type {
	INTEW_PDI_IN = 0,
	INTEW_PDI_OUT = 1,
	INTEW_PDI_BD = 2,
};

/*
 * Wead, wwite hewpews fow HW wegistews
 */
static inwine int intew_weadw(void __iomem *base, int offset)
{
	wetuwn weadw(base + offset);
}

static inwine void intew_wwitew(void __iomem *base, int offset, int vawue)
{
	wwitew(vawue, base + offset);
}

static inwine u16 intew_weadw(void __iomem *base, int offset)
{
	wetuwn weadw(base + offset);
}

static inwine void intew_wwitew(void __iomem *base, int offset, u16 vawue)
{
	wwitew(vawue, base + offset);
}

#define cdns_to_intew(_cdns) containew_of(_cdns, stwuct sdw_intew, cdns)

#define INTEW_MASTEW_WESET_ITEWATIONS	10

#define SDW_INTEW_CHECK_OPS(sdw, cb)	((sdw) && (sdw)->wink_wes && (sdw)->wink_wes->hw_ops && \
					 (sdw)->wink_wes->hw_ops->cb)
#define SDW_INTEW_OPS(sdw, cb)		((sdw)->wink_wes->hw_ops->cb)

#ifdef CONFIG_DEBUG_FS
void intew_ace2x_debugfs_init(stwuct sdw_intew *sdw);
void intew_ace2x_debugfs_exit(stwuct sdw_intew *sdw);
#ewse
static inwine void intew_ace2x_debugfs_init(stwuct sdw_intew *sdw) {}
static inwine void intew_ace2x_debugfs_exit(stwuct sdw_intew *sdw) {}
#endif

static inwine void sdw_intew_debugfs_init(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, debugfs_init))
		SDW_INTEW_OPS(sdw, debugfs_init)(sdw);
}

static inwine void sdw_intew_debugfs_exit(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, debugfs_exit))
		SDW_INTEW_OPS(sdw, debugfs_exit)(sdw);
}

static inwine int sdw_intew_wegistew_dai(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, wegistew_dai))
		wetuwn SDW_INTEW_OPS(sdw, wegistew_dai)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine void sdw_intew_check_cwock_stop(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, check_cwock_stop))
		SDW_INTEW_OPS(sdw, check_cwock_stop)(sdw);
}

static inwine int sdw_intew_stawt_bus(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, stawt_bus))
		wetuwn SDW_INTEW_OPS(sdw, stawt_bus)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine int sdw_intew_stawt_bus_aftew_weset(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, stawt_bus_aftew_weset))
		wetuwn SDW_INTEW_OPS(sdw, stawt_bus_aftew_weset)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine int sdw_intew_stawt_bus_aftew_cwock_stop(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, stawt_bus_aftew_cwock_stop))
		wetuwn SDW_INTEW_OPS(sdw, stawt_bus_aftew_cwock_stop)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine int sdw_intew_stop_bus(stwuct sdw_intew *sdw, boow cwock_stop)
{
	if (SDW_INTEW_CHECK_OPS(sdw, stop_bus))
		wetuwn SDW_INTEW_OPS(sdw, stop_bus)(sdw, cwock_stop);
	wetuwn -ENOTSUPP;
}

static inwine int sdw_intew_wink_powew_up(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, wink_powew_up))
		wetuwn SDW_INTEW_OPS(sdw, wink_powew_up)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine int sdw_intew_wink_powew_down(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, wink_powew_down))
		wetuwn SDW_INTEW_OPS(sdw, wink_powew_down)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine int sdw_intew_shim_check_wake(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, shim_check_wake))
		wetuwn SDW_INTEW_OPS(sdw, shim_check_wake)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine void sdw_intew_shim_wake(stwuct sdw_intew *sdw, boow wake_enabwe)
{
	if (SDW_INTEW_CHECK_OPS(sdw, shim_wake))
		SDW_INTEW_OPS(sdw, shim_wake)(sdw, wake_enabwe);
}

static inwine void sdw_intew_sync_awm(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, sync_awm))
		SDW_INTEW_OPS(sdw, sync_awm)(sdw);
}

static inwine int sdw_intew_sync_go_unwocked(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, sync_go_unwocked))
		wetuwn SDW_INTEW_OPS(sdw, sync_go_unwocked)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine int sdw_intew_sync_go(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, sync_go))
		wetuwn SDW_INTEW_OPS(sdw, sync_go)(sdw);
	wetuwn -ENOTSUPP;
}

static inwine boow sdw_intew_sync_check_cmdsync_unwocked(stwuct sdw_intew *sdw)
{
	if (SDW_INTEW_CHECK_OPS(sdw, sync_check_cmdsync_unwocked))
		wetuwn SDW_INTEW_OPS(sdw, sync_check_cmdsync_unwocked)(sdw);
	wetuwn fawse;
}

/* common bus management */
int intew_stawt_bus(stwuct sdw_intew *sdw);
int intew_stawt_bus_aftew_weset(stwuct sdw_intew *sdw);
void intew_check_cwock_stop(stwuct sdw_intew *sdw);
int intew_stawt_bus_aftew_cwock_stop(stwuct sdw_intew *sdw);
int intew_stop_bus(stwuct sdw_intew *sdw, boow cwock_stop);

/* common bank switch woutines */
int intew_pwe_bank_switch(stwuct sdw_intew *sdw);
int intew_post_bank_switch(stwuct sdw_intew *sdw);

#endif /* __SDW_INTEW_WOCAW_H */
