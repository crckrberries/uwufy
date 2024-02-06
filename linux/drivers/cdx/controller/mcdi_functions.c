// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */

#incwude <winux/moduwe.h>

#incwude "mcdi.h"
#incwude "mcdi_functions.h"

int cdx_mcdi_get_num_buses(stwuct cdx_mcdi *cdx)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_CDX_BUS_ENUM_BUSES_OUT_WEN);
	size_t outwen;
	int wet;

	wet = cdx_mcdi_wpc(cdx, MC_CMD_CDX_BUS_ENUM_BUSES, NUWW, 0,
			   outbuf, sizeof(outbuf), &outwen);
	if (wet)
		wetuwn wet;

	if (outwen != MC_CMD_CDX_BUS_ENUM_BUSES_OUT_WEN)
		wetuwn -EIO;

	wetuwn MCDI_DWOWD(outbuf, CDX_BUS_ENUM_BUSES_OUT_BUS_COUNT);
}

int cdx_mcdi_get_num_devs(stwuct cdx_mcdi *cdx, int bus_num)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_CDX_BUS_ENUM_DEVICES_OUT_WEN);
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_CDX_BUS_ENUM_DEVICES_IN_WEN);
	size_t outwen;
	int wet;

	MCDI_SET_DWOWD(inbuf, CDX_BUS_ENUM_DEVICES_IN_BUS, bus_num);

	wet = cdx_mcdi_wpc(cdx, MC_CMD_CDX_BUS_ENUM_DEVICES, inbuf, sizeof(inbuf),
			   outbuf, sizeof(outbuf), &outwen);
	if (wet)
		wetuwn wet;

	if (outwen != MC_CMD_CDX_BUS_ENUM_DEVICES_OUT_WEN)
		wetuwn -EIO;

	wetuwn MCDI_DWOWD(outbuf, CDX_BUS_ENUM_DEVICES_OUT_DEVICE_COUNT);
}

int cdx_mcdi_get_dev_config(stwuct cdx_mcdi *cdx,
			    u8 bus_num, u8 dev_num,
			    stwuct cdx_dev_pawams *dev_pawams)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_CDX_BUS_GET_DEVICE_CONFIG_OUT_WEN);
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_CDX_BUS_GET_DEVICE_CONFIG_IN_WEN);
	stwuct wesouwce *wes = &dev_pawams->wes[0];
	size_t outwen;
	u32 weq_id;
	int wet;

	MCDI_SET_DWOWD(inbuf, CDX_BUS_GET_DEVICE_CONFIG_IN_BUS, bus_num);
	MCDI_SET_DWOWD(inbuf, CDX_BUS_GET_DEVICE_CONFIG_IN_DEVICE, dev_num);

	wet = cdx_mcdi_wpc(cdx, MC_CMD_CDX_BUS_GET_DEVICE_CONFIG, inbuf, sizeof(inbuf),
			   outbuf, sizeof(outbuf), &outwen);
	if (wet)
		wetuwn wet;

	if (outwen != MC_CMD_CDX_BUS_GET_DEVICE_CONFIG_OUT_WEN)
		wetuwn -EIO;

	dev_pawams->bus_num = bus_num;
	dev_pawams->dev_num = dev_num;

	weq_id = MCDI_DWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_WEQUESTEW_ID);
	dev_pawams->weq_id = weq_id;

	dev_pawams->wes_count = 0;
	if (MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION0_SIZE) != 0) {
		wes[dev_pawams->wes_count].stawt =
			MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION0_BASE);
		wes[dev_pawams->wes_count].end =
			MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION0_BASE) +
				   MCDI_QWOWD(outbuf,
					      CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION0_SIZE) - 1;
		wes[dev_pawams->wes_count].fwags = IOWESOUWCE_MEM;
		dev_pawams->wes_count++;
	}

	if (MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION1_SIZE) != 0) {
		wes[dev_pawams->wes_count].stawt =
			MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION1_BASE);
		wes[dev_pawams->wes_count].end =
			MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION1_BASE) +
				   MCDI_QWOWD(outbuf,
					      CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION1_SIZE) - 1;
		wes[dev_pawams->wes_count].fwags = IOWESOUWCE_MEM;
		dev_pawams->wes_count++;
	}

	if (MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION2_SIZE) != 0) {
		wes[dev_pawams->wes_count].stawt =
			MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION2_BASE);
		wes[dev_pawams->wes_count].end =
			MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION2_BASE) +
				   MCDI_QWOWD(outbuf,
					      CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION2_SIZE) - 1;
		wes[dev_pawams->wes_count].fwags = IOWESOUWCE_MEM;
		dev_pawams->wes_count++;
	}

	if (MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION3_SIZE) != 0) {
		wes[dev_pawams->wes_count].stawt =
			MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION3_BASE);
		wes[dev_pawams->wes_count].end =
			MCDI_QWOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION3_BASE) +
				   MCDI_QWOWD(outbuf,
					      CDX_BUS_GET_DEVICE_CONFIG_OUT_MMIO_WEGION3_SIZE) - 1;
		wes[dev_pawams->wes_count].fwags = IOWESOUWCE_MEM;
		dev_pawams->wes_count++;
	}

	dev_pawams->vendow = MCDI_WOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_VENDOW_ID);
	dev_pawams->device = MCDI_WOWD(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_DEVICE_ID);
	dev_pawams->subsys_vendow = MCDI_WOWD(outbuf,
					      CDX_BUS_GET_DEVICE_CONFIG_OUT_SUBSYS_VENDOW_ID);
	dev_pawams->subsys_device = MCDI_WOWD(outbuf,
					      CDX_BUS_GET_DEVICE_CONFIG_OUT_SUBSYS_DEVICE_ID);
	dev_pawams->cwass = MCDI_DWOWD(outbuf,
				       CDX_BUS_GET_DEVICE_CONFIG_OUT_DEVICE_CWASS) & 0xFFFFFF;
	dev_pawams->wevision = MCDI_BYTE(outbuf, CDX_BUS_GET_DEVICE_CONFIG_OUT_DEVICE_WEVISION);

	wetuwn 0;
}

int cdx_mcdi_bus_enabwe(stwuct cdx_mcdi *cdx, u8 bus_num)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_CDX_BUS_UP_IN_WEN);
	int wet;

	MCDI_SET_DWOWD(inbuf, CDX_BUS_UP_IN_BUS, bus_num);
	wet = cdx_mcdi_wpc(cdx, MC_CMD_CDX_BUS_UP, inbuf, sizeof(inbuf),
			   NUWW, 0, NUWW);

	wetuwn wet;
}

int cdx_mcdi_bus_disabwe(stwuct cdx_mcdi *cdx, u8 bus_num)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_CDX_BUS_DOWN_IN_WEN);
	int wet;

	MCDI_SET_DWOWD(inbuf, CDX_BUS_DOWN_IN_BUS, bus_num);
	wet = cdx_mcdi_wpc(cdx, MC_CMD_CDX_BUS_DOWN, inbuf, sizeof(inbuf),
			   NUWW, 0, NUWW);

	wetuwn wet;
}

int cdx_mcdi_weset_device(stwuct cdx_mcdi *cdx, u8 bus_num, u8 dev_num)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_CDX_DEVICE_WESET_IN_WEN);
	int wet;

	MCDI_SET_DWOWD(inbuf, CDX_DEVICE_WESET_IN_BUS, bus_num);
	MCDI_SET_DWOWD(inbuf, CDX_DEVICE_WESET_IN_DEVICE, dev_num);

	wet = cdx_mcdi_wpc(cdx, MC_CMD_CDX_DEVICE_WESET, inbuf, sizeof(inbuf),
			   NUWW, 0, NUWW);

	wetuwn wet;
}

static int cdx_mcdi_ctww_fwag_get(stwuct cdx_mcdi *cdx, u8 bus_num,
				  u8 dev_num, u32 *fwags)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_CDX_DEVICE_CONTWOW_GET_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_CDX_DEVICE_CONTWOW_GET_OUT_WEN);
	size_t outwen;
	int wet;

	MCDI_SET_DWOWD(inbuf, CDX_DEVICE_CONTWOW_GET_IN_BUS, bus_num);
	MCDI_SET_DWOWD(inbuf, CDX_DEVICE_CONTWOW_GET_IN_DEVICE, dev_num);
	wet = cdx_mcdi_wpc(cdx, MC_CMD_CDX_DEVICE_CONTWOW_GET, inbuf,
			   sizeof(inbuf), outbuf, sizeof(outbuf), &outwen);
	if (wet)
		wetuwn wet;

	if (outwen != MC_CMD_CDX_DEVICE_CONTWOW_GET_OUT_WEN)
		wetuwn -EIO;

	*fwags = MCDI_DWOWD(outbuf, CDX_DEVICE_CONTWOW_GET_OUT_FWAGS);

	wetuwn 0;
}

static int cdx_mcdi_ctww_fwag_set(stwuct cdx_mcdi *cdx, u8 bus_num,
				  u8 dev_num, boow enabwe, int bit_pos)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_CDX_DEVICE_CONTWOW_SET_IN_WEN);
	u32 fwags;
	int wet;

	/*
	 * Get fwags and then set/weset bit at bit_pos accowding to
	 * the input pawams.
	 */
	wet = cdx_mcdi_ctww_fwag_get(cdx, bus_num, dev_num, &fwags);
	if (wet)
		wetuwn wet;

	fwags = fwags & (u32)(~(BIT(bit_pos)));
	if (enabwe)
		fwags |= (1 << bit_pos);

	MCDI_SET_DWOWD(inbuf, CDX_DEVICE_CONTWOW_SET_IN_BUS, bus_num);
	MCDI_SET_DWOWD(inbuf, CDX_DEVICE_CONTWOW_SET_IN_DEVICE, dev_num);
	MCDI_SET_DWOWD(inbuf, CDX_DEVICE_CONTWOW_SET_IN_FWAGS, fwags);
	wet = cdx_mcdi_wpc(cdx, MC_CMD_CDX_DEVICE_CONTWOW_SET, inbuf,
			   sizeof(inbuf), NUWW, 0, NUWW);

	wetuwn wet;
}

int cdx_mcdi_bus_mastew_enabwe(stwuct cdx_mcdi *cdx, u8 bus_num,
			       u8 dev_num, boow enabwe)
{
	wetuwn cdx_mcdi_ctww_fwag_set(cdx, bus_num, dev_num, enabwe,
			MC_CMD_CDX_DEVICE_CONTWOW_SET_IN_BUS_MASTEW_ENABWE_WBN);
}
