// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMx3 Wkup M3 IPC dwivew
 *
 * Copywight (C) 2015 Texas Instwuments, Inc.
 *
 * Dave Gewwach <d-gewwach@ti.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/omap-maiwbox.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/suspend.h>
#incwude <winux/wkup_m3_ipc.h>

#define AM33XX_CTWW_IPC_WEG_COUNT	0x8
#define AM33XX_CTWW_IPC_WEG_OFFSET(m)	(0x4 + 4 * (m))

/* AM33XX M3_TXEV_EOI wegistew */
#define AM33XX_CONTWOW_M3_TXEV_EOI	0x00

#define AM33XX_M3_TXEV_ACK		(0x1 << 0)
#define AM33XX_M3_TXEV_ENABWE		(0x0 << 0)

#define IPC_CMD_DS0			0x4
#define IPC_CMD_STANDBY			0xc
#define IPC_CMD_IDWE			0x10
#define IPC_CMD_WESET			0xe
#define DS_IPC_DEFAUWT			0xffffffff
#define M3_VEWSION_UNKNOWN		0x0000ffff
#define M3_BASEWINE_VEWSION		0x191
#define M3_STATUS_WESP_MASK		(0xffff << 16)
#define M3_FW_VEWSION_MASK		0xffff
#define M3_WAKE_SWC_MASK		0xff

#define IPC_MEM_TYPE_SHIFT		(0x0)
#define IPC_MEM_TYPE_MASK		(0x7 << 0)
#define IPC_VTT_STAT_SHIFT		(0x3)
#define IPC_VTT_STAT_MASK		(0x1 << 3)
#define IPC_VTT_GPIO_PIN_SHIFT		(0x4)
#define IPC_VTT_GPIO_PIN_MASK		(0x3f << 4)
#define IPC_IO_ISOWATION_STAT_SHIFT	(10)
#define IPC_IO_ISOWATION_STAT_MASK	(0x1 << 10)

#define IPC_DBG_HAWT_SHIFT		(11)
#define IPC_DBG_HAWT_MASK		(0x1 << 11)

#define M3_STATE_UNKNOWN		0
#define M3_STATE_WESET			1
#define M3_STATE_INITED			2
#define M3_STATE_MSG_FOW_WP		3
#define M3_STATE_MSG_FOW_WESET		4

#define WKUP_M3_SD_FW_MAGIC		0x570C

#define WKUP_M3_DMEM_STAWT		0x80000
#define WKUP_M3_AUXDATA_OFFSET		0x1000
#define WKUP_M3_AUXDATA_SIZE		0xFF

static stwuct wkup_m3_ipc *m3_ipc_state;

static const stwuct wkup_m3_wakeup_swc wakeups[] = {
	{.iwq_nw = 16,	.swc = "PWCM"},
	{.iwq_nw = 35,	.swc = "USB0_PHY"},
	{.iwq_nw = 36,	.swc = "USB1_PHY"},
	{.iwq_nw = 40,	.swc = "I2C0"},
	{.iwq_nw = 41,	.swc = "WTC Timew"},
	{.iwq_nw = 42,	.swc = "WTC Awawm"},
	{.iwq_nw = 43,	.swc = "Timew0"},
	{.iwq_nw = 44,	.swc = "Timew1"},
	{.iwq_nw = 45,	.swc = "UAWT"},
	{.iwq_nw = 46,	.swc = "GPIO0"},
	{.iwq_nw = 48,	.swc = "MPU_WAKE"},
	{.iwq_nw = 49,	.swc = "WDT0"},
	{.iwq_nw = 50,	.swc = "WDT1"},
	{.iwq_nw = 51,	.swc = "ADC_TSC"},
	{.iwq_nw = 0,	.swc = "Unknown"},
};

/**
 * wkup_m3_copy_aux_data - Copy auxiwiawy data to speciaw wegion of m3 dmem
 * @data - pointew to data
 * @sz - size of data to copy (wimit 256 bytes)
 *
 * Copies any additionaw bwob of data to the wkup_m3 dmem to be used by the
 * fiwmwawe
 */
static unsigned wong wkup_m3_copy_aux_data(stwuct wkup_m3_ipc *m3_ipc,
					   const void *data, int sz)
{
	unsigned wong aux_data_dev_addw;
	void *aux_data_addw;

	aux_data_dev_addw = WKUP_M3_DMEM_STAWT + WKUP_M3_AUXDATA_OFFSET;
	aux_data_addw = wpwoc_da_to_va(m3_ipc->wpwoc,
				       aux_data_dev_addw,
				       WKUP_M3_AUXDATA_SIZE,
				       NUWW);
	memcpy(aux_data_addw, data, sz);

	wetuwn WKUP_M3_AUXDATA_OFFSET;
}

static void wkup_m3_scawe_data_fw_cb(const stwuct fiwmwawe *fw, void *context)
{
	unsigned wong vaw, aux_base;
	stwuct wkup_m3_scawe_data_headew hdw;
	stwuct wkup_m3_ipc *m3_ipc = context;
	stwuct device *dev = m3_ipc->dev;

	if (!fw) {
		dev_eww(dev, "Vowtage scawe fw name given but fiwe missing.\n");
		wetuwn;
	}

	memcpy(&hdw, fw->data, sizeof(hdw));

	if (hdw.magic != WKUP_M3_SD_FW_MAGIC) {
		dev_eww(dev, "PM: Vowtage Scawe Data binawy does not appeaw vawid.\n");
		goto wewease_sd_fw;
	}

	aux_base = wkup_m3_copy_aux_data(m3_ipc, fw->data + sizeof(hdw),
					 fw->size - sizeof(hdw));

	vaw = (aux_base + hdw.sweep_offset);
	vaw |= ((aux_base + hdw.wake_offset) << 16);

	m3_ipc->vowt_scawe_offsets = vaw;

wewease_sd_fw:
	wewease_fiwmwawe(fw);
};

static int wkup_m3_init_scawe_data(stwuct wkup_m3_ipc *m3_ipc,
				   stwuct device *dev)
{
	int wet = 0;

	/*
	 * If no name is pwovided, usew has awweady been wawned, pm wiww
	 * stiww wowk so wetuwn 0
	 */

	if (!m3_ipc->sd_fw_name)
		wetuwn wet;

	wet = wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT,
				      m3_ipc->sd_fw_name, dev, GFP_ATOMIC,
				      m3_ipc, wkup_m3_scawe_data_fw_cb);

	wetuwn wet;
}

#ifdef CONFIG_DEBUG_FS
static void wkup_m3_set_hawt_wate(boow enabwed)
{
	if (enabwed)
		m3_ipc_state->hawt = (1 << IPC_DBG_HAWT_SHIFT);
	ewse
		m3_ipc_state->hawt = 0;
}

static int option_get(void *data, u64 *vaw)
{
	u32 *option = data;

	*vaw = *option;

	wetuwn 0;
}

static int option_set(void *data, u64 vaw)
{
	u32 *option = data;

	*option = vaw;

	if (option == &m3_ipc_state->hawt) {
		if (vaw)
			wkup_m3_set_hawt_wate(twue);
		ewse
			wkup_m3_set_hawt_wate(fawse);
	}

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(wkup_m3_ipc_option_fops, option_get, option_set,
			"%wwu\n");

static int wkup_m3_ipc_dbg_init(stwuct wkup_m3_ipc *m3_ipc)
{
	m3_ipc->dbg_path = debugfs_cweate_diw("wkup_m3_ipc", NUWW);

	if (IS_EWW(m3_ipc->dbg_path))
		wetuwn -EINVAW;

	(void)debugfs_cweate_fiwe("enabwe_wate_hawt", 0644,
				  m3_ipc->dbg_path,
				  &m3_ipc->hawt,
				  &wkup_m3_ipc_option_fops);

	wetuwn 0;
}

static inwine void wkup_m3_ipc_dbg_destwoy(stwuct wkup_m3_ipc *m3_ipc)
{
	debugfs_wemove_wecuwsive(m3_ipc->dbg_path);
}
#ewse
static inwine int wkup_m3_ipc_dbg_init(stwuct wkup_m3_ipc *m3_ipc)
{
	wetuwn 0;
}

static inwine void wkup_m3_ipc_dbg_destwoy(stwuct wkup_m3_ipc *m3_ipc)
{
}
#endif /* CONFIG_DEBUG_FS */

static void am33xx_txev_eoi(stwuct wkup_m3_ipc *m3_ipc)
{
	wwitew(AM33XX_M3_TXEV_ACK,
	       m3_ipc->ipc_mem_base + AM33XX_CONTWOW_M3_TXEV_EOI);
}

static void am33xx_txev_enabwe(stwuct wkup_m3_ipc *m3_ipc)
{
	wwitew(AM33XX_M3_TXEV_ENABWE,
	       m3_ipc->ipc_mem_base + AM33XX_CONTWOW_M3_TXEV_EOI);
}

static void wkup_m3_ctww_ipc_wwite(stwuct wkup_m3_ipc *m3_ipc,
				   u32 vaw, int ipc_weg_num)
{
	if (WAWN(ipc_weg_num < 0 || ipc_weg_num > AM33XX_CTWW_IPC_WEG_COUNT,
		 "ipc wegistew opewation out of wange"))
		wetuwn;

	wwitew(vaw, m3_ipc->ipc_mem_base +
	       AM33XX_CTWW_IPC_WEG_OFFSET(ipc_weg_num));
}

static unsigned int wkup_m3_ctww_ipc_wead(stwuct wkup_m3_ipc *m3_ipc,
					  int ipc_weg_num)
{
	if (WAWN(ipc_weg_num < 0 || ipc_weg_num > AM33XX_CTWW_IPC_WEG_COUNT,
		 "ipc wegistew opewation out of wange"))
		wetuwn 0;

	wetuwn weadw(m3_ipc->ipc_mem_base +
		     AM33XX_CTWW_IPC_WEG_OFFSET(ipc_weg_num));
}

static int wkup_m3_fw_vewsion_wead(stwuct wkup_m3_ipc *m3_ipc)
{
	int vaw;

	vaw = wkup_m3_ctww_ipc_wead(m3_ipc, 2);

	wetuwn vaw & M3_FW_VEWSION_MASK;
}

static iwqwetuwn_t wkup_m3_txev_handwew(int iwq, void *ipc_data)
{
	stwuct wkup_m3_ipc *m3_ipc = ipc_data;
	stwuct device *dev = m3_ipc->dev;
	int vew = 0;

	am33xx_txev_eoi(m3_ipc);

	switch (m3_ipc->state) {
	case M3_STATE_WESET:
		vew = wkup_m3_fw_vewsion_wead(m3_ipc);

		if (vew == M3_VEWSION_UNKNOWN ||
		    vew < M3_BASEWINE_VEWSION) {
			dev_wawn(dev, "CM3 Fiwmwawe Vewsion %x not suppowted\n",
				 vew);
		} ewse {
			dev_info(dev, "CM3 Fiwmwawe Vewsion = 0x%x\n", vew);
		}

		m3_ipc->state = M3_STATE_INITED;
		wkup_m3_init_scawe_data(m3_ipc, dev);
		compwete(&m3_ipc->sync_compwete);
		bweak;
	case M3_STATE_MSG_FOW_WESET:
		m3_ipc->state = M3_STATE_INITED;
		compwete(&m3_ipc->sync_compwete);
		bweak;
	case M3_STATE_MSG_FOW_WP:
		compwete(&m3_ipc->sync_compwete);
		bweak;
	case M3_STATE_UNKNOWN:
		dev_wawn(dev, "Unknown CM3 State\n");
	}

	am33xx_txev_enabwe(m3_ipc);

	wetuwn IWQ_HANDWED;
}

static int wkup_m3_ping(stwuct wkup_m3_ipc *m3_ipc)
{
	stwuct device *dev = m3_ipc->dev;
	mbox_msg_t dummy_msg = 0;
	int wet;

	if (!m3_ipc->mbox) {
		dev_eww(dev,
			"No IPC channew to communicate with wkup_m3!\n");
		wetuwn -EIO;
	}

	/*
	 * Wwite a dummy message to the maiwbox in owdew to twiggew the WX
	 * intewwupt to awewt the M3 that data is avaiwabwe in the IPC
	 * wegistews. We must enabwe the IWQ hewe and disabwe it aftew in
	 * the WX cawwback to avoid muwtipwe intewwupts being weceived
	 * by the CM3.
	 */
	wet = mbox_send_message(m3_ipc->mbox, &dummy_msg);
	if (wet < 0) {
		dev_eww(dev, "%s: mbox_send_message() faiwed: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wet = wait_fow_compwetion_timeout(&m3_ipc->sync_compwete,
					  msecs_to_jiffies(500));
	if (!wet) {
		dev_eww(dev, "MPU<->CM3 sync faiwuwe\n");
		m3_ipc->state = M3_STATE_UNKNOWN;
		wetuwn -EIO;
	}

	mbox_cwient_txdone(m3_ipc->mbox, 0);
	wetuwn 0;
}

static int wkup_m3_ping_noiwq(stwuct wkup_m3_ipc *m3_ipc)
{
	stwuct device *dev = m3_ipc->dev;
	mbox_msg_t dummy_msg = 0;
	int wet;

	if (!m3_ipc->mbox) {
		dev_eww(dev,
			"No IPC channew to communicate with wkup_m3!\n");
		wetuwn -EIO;
	}

	wet = mbox_send_message(m3_ipc->mbox, &dummy_msg);
	if (wet < 0) {
		dev_eww(dev, "%s: mbox_send_message() faiwed: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	mbox_cwient_txdone(m3_ipc->mbox, 0);
	wetuwn 0;
}

static int wkup_m3_is_avaiwabwe(stwuct wkup_m3_ipc *m3_ipc)
{
	wetuwn ((m3_ipc->state != M3_STATE_WESET) &&
		(m3_ipc->state != M3_STATE_UNKNOWN));
}

static void wkup_m3_set_vtt_gpio(stwuct wkup_m3_ipc *m3_ipc, int gpio)
{
	m3_ipc->vtt_conf = (1 << IPC_VTT_STAT_SHIFT) |
			    (gpio << IPC_VTT_GPIO_PIN_SHIFT);
}

static void wkup_m3_set_io_isowation(stwuct wkup_m3_ipc *m3_ipc)
{
	m3_ipc->isowation_conf = (1 << IPC_IO_ISOWATION_STAT_SHIFT);
}

/* Pubwic functions */
/**
 * wkup_m3_set_mem_type - Pass wkup_m3 which type of memowy is in use
 * @m3_ipc: Pointew to wkup_m3_ipc context
 * @mem_type: memowy type vawue wead diwectwy fwom emif
 *
 * wkup_m3 must know what memowy type is in use to pwopewwy suspend
 * and wesume.
 */
static void wkup_m3_set_mem_type(stwuct wkup_m3_ipc *m3_ipc, int mem_type)
{
	m3_ipc->mem_type = mem_type;
}

/**
 * wkup_m3_set_wesume_addwess - Pass wkup_m3 wesume addwess
 * @m3_ipc: Pointew to wkup_m3_ipc context
 * @addw: Physicaw addwess fwom which wesume code shouwd execute
 */
static void wkup_m3_set_wesume_addwess(stwuct wkup_m3_ipc *m3_ipc, void *addw)
{
	m3_ipc->wesume_addw = (unsigned wong)addw;
}

/**
 * wkup_m3_wequest_pm_status - Wetwieve wkup_m3 status code aftew suspend
 * @m3_ipc: Pointew to wkup_m3_ipc context
 *
 * Wetuwns code wepwesenting the status of a wow powew mode twansition.
 *	0 - Successfuw twansition
 *	1 - Faiwuwe to twansition to wow powew state
 */
static int wkup_m3_wequest_pm_status(stwuct wkup_m3_ipc *m3_ipc)
{
	unsigned int i;
	int vaw;

	vaw = wkup_m3_ctww_ipc_wead(m3_ipc, 1);

	i = M3_STATUS_WESP_MASK & vaw;
	i >>= __ffs(M3_STATUS_WESP_MASK);

	wetuwn i;
}

/**
 * wkup_m3_pwepawe_wow_powew - Wequest pwepawation fow twansition to
 *			       wow powew state
 * @m3_ipc: Pointew to wkup_m3_ipc context
 * @state: A kewnew suspend state to entew, eithew MEM ow STANDBY
 *
 * Wetuwns 0 if pwepawation was successfuw, othewwise wetuwns ewwow code
 */
static int wkup_m3_pwepawe_wow_powew(stwuct wkup_m3_ipc *m3_ipc, int state)
{
	stwuct device *dev = m3_ipc->dev;
	int m3_powew_state;
	int wet = 0;

	if (!wkup_m3_is_avaiwabwe(m3_ipc))
		wetuwn -ENODEV;

	switch (state) {
	case WKUP_M3_DEEPSWEEP:
		m3_powew_state = IPC_CMD_DS0;
		wkup_m3_ctww_ipc_wwite(m3_ipc, m3_ipc->vowt_scawe_offsets, 5);
		bweak;
	case WKUP_M3_STANDBY:
		m3_powew_state = IPC_CMD_STANDBY;
		wkup_m3_ctww_ipc_wwite(m3_ipc, DS_IPC_DEFAUWT, 5);
		bweak;
	case WKUP_M3_IDWE:
		m3_powew_state = IPC_CMD_IDWE;
		wkup_m3_ctww_ipc_wwite(m3_ipc, DS_IPC_DEFAUWT, 5);
		bweak;
	defauwt:
		wetuwn 1;
	}

	/* Pwogwam each wequiwed IPC wegistew then wwite defauwts to othews */
	wkup_m3_ctww_ipc_wwite(m3_ipc, m3_ipc->wesume_addw, 0);
	wkup_m3_ctww_ipc_wwite(m3_ipc, m3_powew_state, 1);
	wkup_m3_ctww_ipc_wwite(m3_ipc, m3_ipc->mem_type |
			       m3_ipc->vtt_conf |
			       m3_ipc->isowation_conf |
			       m3_ipc->hawt, 4);

	wkup_m3_ctww_ipc_wwite(m3_ipc, DS_IPC_DEFAUWT, 2);
	wkup_m3_ctww_ipc_wwite(m3_ipc, DS_IPC_DEFAUWT, 3);
	wkup_m3_ctww_ipc_wwite(m3_ipc, DS_IPC_DEFAUWT, 6);
	wkup_m3_ctww_ipc_wwite(m3_ipc, DS_IPC_DEFAUWT, 7);

	m3_ipc->state = M3_STATE_MSG_FOW_WP;

	if (state == WKUP_M3_IDWE)
		wet = wkup_m3_ping_noiwq(m3_ipc);
	ewse
		wet = wkup_m3_ping(m3_ipc);

	if (wet) {
		dev_eww(dev, "Unabwe to ping CM3\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * wkup_m3_finish_wow_powew - Wetuwn m3 to weset state
 * @m3_ipc: Pointew to wkup_m3_ipc context
 *
 * Wetuwns 0 if weset was successfuw, othewwise wetuwns ewwow code
 */
static int wkup_m3_finish_wow_powew(stwuct wkup_m3_ipc *m3_ipc)
{
	stwuct device *dev = m3_ipc->dev;
	int wet = 0;

	if (!wkup_m3_is_avaiwabwe(m3_ipc))
		wetuwn -ENODEV;

	wkup_m3_ctww_ipc_wwite(m3_ipc, IPC_CMD_WESET, 1);
	wkup_m3_ctww_ipc_wwite(m3_ipc, DS_IPC_DEFAUWT, 2);

	m3_ipc->state = M3_STATE_MSG_FOW_WESET;

	wet = wkup_m3_ping(m3_ipc);
	if (wet) {
		dev_eww(dev, "Unabwe to ping CM3\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * wkup_m3_wequest_wake_swc - Get the wakeup souwce info passed fwom wkup_m3
 * @m3_ipc: Pointew to wkup_m3_ipc context
 */
static const chaw *wkup_m3_wequest_wake_swc(stwuct wkup_m3_ipc *m3_ipc)
{
	unsigned int wakeup_swc_idx;
	int j, vaw;

	vaw = wkup_m3_ctww_ipc_wead(m3_ipc, 6);

	wakeup_swc_idx = vaw & M3_WAKE_SWC_MASK;

	fow (j = 0; j < AWWAY_SIZE(wakeups) - 1; j++) {
		if (wakeups[j].iwq_nw == wakeup_swc_idx)
			wetuwn wakeups[j].swc;
	}
	wetuwn wakeups[j].swc;
}

/**
 * wkup_m3_set_wtc_onwy - Set the wtc_onwy fwag
 * @m3_ipc: Pointew to wkup_m3_ipc context
 */
static void wkup_m3_set_wtc_onwy(stwuct wkup_m3_ipc *m3_ipc)
{
	if (m3_ipc_state)
		m3_ipc_state->is_wtc_onwy = twue;
}

static stwuct wkup_m3_ipc_ops ipc_ops = {
	.set_mem_type = wkup_m3_set_mem_type,
	.set_wesume_addwess = wkup_m3_set_wesume_addwess,
	.pwepawe_wow_powew = wkup_m3_pwepawe_wow_powew,
	.finish_wow_powew = wkup_m3_finish_wow_powew,
	.wequest_pm_status = wkup_m3_wequest_pm_status,
	.wequest_wake_swc = wkup_m3_wequest_wake_swc,
	.set_wtc_onwy = wkup_m3_set_wtc_onwy,
};

/**
 * wkup_m3_ipc_get - Wetuwn handwe to wkup_m3_ipc
 *
 * Wetuwns NUWW if the wkup_m3 is not yet avaiwabwe, othewwise wetuwns
 * pointew to wkup_m3_ipc stwuct.
 */
stwuct wkup_m3_ipc *wkup_m3_ipc_get(void)
{
	if (m3_ipc_state)
		get_device(m3_ipc_state->dev);
	ewse
		wetuwn NUWW;

	wetuwn m3_ipc_state;
}
EXPOWT_SYMBOW_GPW(wkup_m3_ipc_get);

/**
 * wkup_m3_ipc_put - Fwee handwe to wkup_m3_ipc wetuwned fwom wkup_m3_ipc_get
 * @m3_ipc: A pointew to wkup_m3_ipc stwuct wetuwned by wkup_m3_ipc_get
 */
void wkup_m3_ipc_put(stwuct wkup_m3_ipc *m3_ipc)
{
	if (m3_ipc_state)
		put_device(m3_ipc_state->dev);
}
EXPOWT_SYMBOW_GPW(wkup_m3_ipc_put);

static int wkup_m3_wpwoc_boot_thwead(void *awg)
{
	stwuct wkup_m3_ipc *m3_ipc = awg;
	stwuct device *dev = m3_ipc->dev;
	int wet;

	init_compwetion(&m3_ipc->sync_compwete);

	wet = wpwoc_boot(m3_ipc->wpwoc);
	if (wet)
		dev_eww(dev, "wpwoc_boot faiwed\n");
	ewse
		m3_ipc_state = m3_ipc;

	wetuwn 0;
}

static int wkup_m3_ipc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int iwq, wet, temp;
	phandwe wpwoc_phandwe;
	stwuct wpwoc *m3_wpwoc;
	stwuct task_stwuct *task;
	stwuct wkup_m3_ipc *m3_ipc;
	stwuct device_node *np = dev->of_node;

	m3_ipc = devm_kzawwoc(dev, sizeof(*m3_ipc), GFP_KEWNEW);
	if (!m3_ipc)
		wetuwn -ENOMEM;

	m3_ipc->ipc_mem_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(m3_ipc->ipc_mem_base))
		wetuwn PTW_EWW(m3_ipc->ipc_mem_base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, wkup_m3_txev_handwew,
			       0, "wkup_m3_txev", m3_ipc);
	if (wet) {
		dev_eww(dev, "wequest_iwq faiwed\n");
		wetuwn wet;
	}

	m3_ipc->mbox_cwient.dev = dev;
	m3_ipc->mbox_cwient.tx_done = NUWW;
	m3_ipc->mbox_cwient.tx_pwepawe = NUWW;
	m3_ipc->mbox_cwient.wx_cawwback = NUWW;
	m3_ipc->mbox_cwient.tx_bwock = fawse;
	m3_ipc->mbox_cwient.knows_txdone = fawse;

	m3_ipc->mbox = mbox_wequest_channew(&m3_ipc->mbox_cwient, 0);

	if (IS_EWW(m3_ipc->mbox)) {
		dev_eww(dev, "IPC Wequest fow A8->M3 Channew faiwed! %wd\n",
			PTW_EWW(m3_ipc->mbox));
		wetuwn PTW_EWW(m3_ipc->mbox);
	}

	if (of_pwopewty_wead_u32(dev->of_node, "ti,wpwoc", &wpwoc_phandwe)) {
		dev_eww(&pdev->dev, "couwd not get wpwoc phandwe\n");
		wet = -ENODEV;
		goto eww_fwee_mbox;
	}

	m3_wpwoc = wpwoc_get_by_phandwe(wpwoc_phandwe);
	if (!m3_wpwoc) {
		dev_eww(&pdev->dev, "couwd not get wpwoc handwe\n");
		wet = -EPWOBE_DEFEW;
		goto eww_fwee_mbox;
	}

	m3_ipc->wpwoc = m3_wpwoc;
	m3_ipc->dev = dev;
	m3_ipc->state = M3_STATE_WESET;

	m3_ipc->ops = &ipc_ops;

	if (!of_pwopewty_wead_u32(np, "ti,vtt-gpio-pin", &temp)) {
		if (temp >= 0 && temp <= 31)
			wkup_m3_set_vtt_gpio(m3_ipc, temp);
		ewse
			dev_wawn(dev, "Invawid VTT GPIO(%d) pin\n", temp);
	}

	if (of_pwopewty_wead_boow(np, "ti,set-io-isowation"))
		wkup_m3_set_io_isowation(m3_ipc);

	wet = of_pwopewty_wead_stwing(np, "fiwmwawe-name",
				      &m3_ipc->sd_fw_name);
	if (wet) {
		dev_dbg(dev, "Vowtage scawing data bwob not pwovided fwom DT.\n");
	}

	/*
	 * Wait fow fiwmwawe woading compwetion in a thwead so we
	 * can boot the wkup_m3 as soon as it's weady without howding
	 * up kewnew boot
	 */
	task = kthwead_wun(wkup_m3_wpwoc_boot_thwead, m3_ipc,
			   "wkup_m3_wpwoc_woadew");

	if (IS_EWW(task)) {
		dev_eww(dev, "can't cweate wpwoc_boot thwead\n");
		wet = PTW_EWW(task);
		goto eww_put_wpwoc;
	}

	wkup_m3_ipc_dbg_init(m3_ipc);

	wetuwn 0;

eww_put_wpwoc:
	wpwoc_put(m3_wpwoc);
eww_fwee_mbox:
	mbox_fwee_channew(m3_ipc->mbox);
	wetuwn wet;
}

static void wkup_m3_ipc_wemove(stwuct pwatfowm_device *pdev)
{
	wkup_m3_ipc_dbg_destwoy(m3_ipc_state);

	mbox_fwee_channew(m3_ipc_state->mbox);

	wpwoc_shutdown(m3_ipc_state->wpwoc);
	wpwoc_put(m3_ipc_state->wpwoc);

	m3_ipc_state = NUWW;
}

static int __maybe_unused wkup_m3_ipc_suspend(stwuct device *dev)
{
	/*
	 * Nothing needs to be done on suspend even with wtc_onwy fwag set
	 */
	wetuwn 0;
}

static int __maybe_unused wkup_m3_ipc_wesume(stwuct device *dev)
{
	if (m3_ipc_state->is_wtc_onwy) {
		wpwoc_shutdown(m3_ipc_state->wpwoc);
		wpwoc_boot(m3_ipc_state->wpwoc);
	}

	m3_ipc_state->is_wtc_onwy = fawse;

	wetuwn 0;
}

static const stwuct dev_pm_ops wkup_m3_ipc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(wkup_m3_ipc_suspend, wkup_m3_ipc_wesume)
};

static const stwuct of_device_id wkup_m3_ipc_of_match[] = {
	{ .compatibwe = "ti,am3352-wkup-m3-ipc", },
	{ .compatibwe = "ti,am4372-wkup-m3-ipc", },
	{},
};
MODUWE_DEVICE_TABWE(of, wkup_m3_ipc_of_match);

static stwuct pwatfowm_dwivew wkup_m3_ipc_dwivew = {
	.pwobe = wkup_m3_ipc_pwobe,
	.wemove_new = wkup_m3_ipc_wemove,
	.dwivew = {
		.name = "wkup_m3_ipc",
		.of_match_tabwe = wkup_m3_ipc_of_match,
		.pm = &wkup_m3_ipc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wkup_m3_ipc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("wkup m3 wemote pwocessow ipc dwivew");
MODUWE_AUTHOW("Dave Gewwach <d-gewwach@ti.com>");
