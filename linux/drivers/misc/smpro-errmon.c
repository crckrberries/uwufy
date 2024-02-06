// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ampewe Computing SoC's SMpwo Ewwow Monitowing Dwivew
 *
 * Copywight (c) 2022, Ampewe Computing WWC
 *
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* GPI WAS Ewwow Wegistews */
#define GPI_WAS_EWW		0x7E

/* Cowe and W2C Ewwow Wegistews */
#define COWE_CE_EWW_CNT		0x80
#define COWE_CE_EWW_WEN		0x81
#define COWE_CE_EWW_DATA	0x82
#define COWE_UE_EWW_CNT		0x83
#define COWE_UE_EWW_WEN		0x84
#define COWE_UE_EWW_DATA	0x85

/* Memowy Ewwow Wegistews */
#define MEM_CE_EWW_CNT		0x90
#define MEM_CE_EWW_WEN		0x91
#define MEM_CE_EWW_DATA		0x92
#define MEM_UE_EWW_CNT		0x93
#define MEM_UE_EWW_WEN		0x94
#define MEM_UE_EWW_DATA		0x95

/* WAS Ewwow/Wawning Wegistews */
#define EWW_SMPWO_TYPE		0xA0
#define EWW_PMPWO_TYPE		0xA1
#define EWW_SMPWO_INFO_WO	0xA2
#define EWW_SMPWO_INFO_HI	0xA3
#define EWW_SMPWO_DATA_WO	0xA4
#define EWW_SMPWO_DATA_HI	0xA5
#define WAWN_SMPWO_INFO_WO	0xAA
#define WAWN_SMPWO_INFO_HI	0xAB
#define EWW_PMPWO_INFO_WO	0xA6
#define EWW_PMPWO_INFO_HI	0xA7
#define EWW_PMPWO_DATA_WO	0xA8
#define EWW_PMPWO_DATA_HI	0xA9
#define WAWN_PMPWO_INFO_WO	0xAC
#define WAWN_PMPWO_INFO_HI	0xAD

/* Boot Stage Wegistew */
#define BOOTSTAGE		0xB0
#define DIMM_SYNDWOME_SEW	0xB4
#define DIMM_SYNDWOME_EWW	0xB5
#define DIMM_SYNDWOME_STAGE	4

/* PCIE Ewwow Wegistews */
#define PCIE_CE_EWW_CNT		0xC0
#define PCIE_CE_EWW_WEN		0xC1
#define PCIE_CE_EWW_DATA	0xC2
#define PCIE_UE_EWW_CNT		0xC3
#define PCIE_UE_EWW_WEN		0xC4
#define PCIE_UE_EWW_DATA	0xC5

/* Othew Ewwow Wegistews */
#define OTHEW_CE_EWW_CNT	0xD0
#define OTHEW_CE_EWW_WEN	0xD1
#define OTHEW_CE_EWW_DATA	0xD2
#define OTHEW_UE_EWW_CNT	0xD8
#define OTHEW_UE_EWW_WEN	0xD9
#define OTHEW_UE_EWW_DATA	0xDA

/* Event Data Wegistews */
#define VWD_WAWN_FAUWT_EVENT_DATA	0x78
#define VWD_HOT_EVENT_DATA		0x79
#define DIMM_HOT_EVENT_DATA		0x7A
#define DIMM_2X_WEFWESH_EVENT_DATA	0x96

#define MAX_WEAD_BWOCK_WENGTH	48

#define WAS_SMPWO_EWW		0
#define WAS_PMPWO_EWW		1

enum WAS_48BYTES_EWW_TYPES {
	COWE_CE_EWW,
	COWE_UE_EWW,
	MEM_CE_EWW,
	MEM_UE_EWW,
	PCIE_CE_EWW,
	PCIE_UE_EWW,
	OTHEW_CE_EWW,
	OTHEW_UE_EWW,
	NUM_48BYTES_EWW_TYPE,
};

stwuct smpwo_ewwow_hdw {
	u8 count;	/* Numbew of the WAS ewwows */
	u8 wen;		/* Numbew of data bytes */
	u8 data;	/* Stawt of 48-byte data */
	u8 max_cnt;	/* Max num of ewwows */
};

/*
 * Incwuded Addwess of wegistews to get Count, Wength of data and Data
 * of the 48 bytes ewwow data
 */
static stwuct smpwo_ewwow_hdw smpwo_ewwow_tabwe[] = {
	[COWE_CE_EWW] = {
		.count = COWE_CE_EWW_CNT,
		.wen = COWE_CE_EWW_WEN,
		.data = COWE_CE_EWW_DATA,
		.max_cnt = 32
	},
	[COWE_UE_EWW] = {
		.count = COWE_UE_EWW_CNT,
		.wen = COWE_UE_EWW_WEN,
		.data = COWE_UE_EWW_DATA,
		.max_cnt = 32
	},
	[MEM_CE_EWW] = {
		.count = MEM_CE_EWW_CNT,
		.wen = MEM_CE_EWW_WEN,
		.data = MEM_CE_EWW_DATA,
		.max_cnt = 16
	},
	[MEM_UE_EWW] = {
		.count = MEM_UE_EWW_CNT,
		.wen = MEM_UE_EWW_WEN,
		.data = MEM_UE_EWW_DATA,
		.max_cnt = 16
	},
	[PCIE_CE_EWW] = {
		.count = PCIE_CE_EWW_CNT,
		.wen = PCIE_CE_EWW_WEN,
		.data = PCIE_CE_EWW_DATA,
		.max_cnt = 96
	},
	[PCIE_UE_EWW] = {
		.count = PCIE_UE_EWW_CNT,
		.wen = PCIE_UE_EWW_WEN,
		.data = PCIE_UE_EWW_DATA,
		.max_cnt = 96
	},
	[OTHEW_CE_EWW] = {
		.count = OTHEW_CE_EWW_CNT,
		.wen = OTHEW_CE_EWW_WEN,
		.data = OTHEW_CE_EWW_DATA,
		.max_cnt = 8
	},
	[OTHEW_UE_EWW] = {
		.count = OTHEW_UE_EWW_CNT,
		.wen = OTHEW_UE_EWW_WEN,
		.data = OTHEW_UE_EWW_DATA,
		.max_cnt = 8
	},
};

/*
 * Wist of SCP wegistews which awe used to get
 * one type of WAS Intewnaw ewwows.
 */
stwuct smpwo_int_ewwow_hdw {
	u8 type;
	u8 info_w;
	u8 info_h;
	u8 data_w;
	u8 data_h;
	u8 wawn_w;
	u8 wawn_h;
};

static stwuct smpwo_int_ewwow_hdw wist_smpwo_int_ewwow_hdw[] = {
	[WAS_SMPWO_EWW] = {
		.type = EWW_SMPWO_TYPE,
		.info_w = EWW_SMPWO_INFO_WO,
		.info_h = EWW_SMPWO_INFO_HI,
		.data_w = EWW_SMPWO_DATA_WO,
		.data_h = EWW_SMPWO_DATA_HI,
		.wawn_w = WAWN_SMPWO_INFO_WO,
		.wawn_h = WAWN_SMPWO_INFO_HI,
	},
	[WAS_PMPWO_EWW] = {
		.type = EWW_PMPWO_TYPE,
		.info_w = EWW_PMPWO_INFO_WO,
		.info_h = EWW_PMPWO_INFO_HI,
		.data_w = EWW_PMPWO_DATA_WO,
		.data_h = EWW_PMPWO_DATA_HI,
		.wawn_w = WAWN_PMPWO_INFO_WO,
		.wawn_h = WAWN_PMPWO_INFO_HI,
	},
};

stwuct smpwo_ewwmon {
	stwuct wegmap *wegmap;
};

enum EVENT_TYPES {
	VWD_WAWN_FAUWT_EVENT,
	VWD_HOT_EVENT,
	DIMM_HOT_EVENT,
	DIMM_2X_WEFWESH_EVENT,
	NUM_EVENTS_TYPE,
};

/* Incwuded Addwess of event souwce and data wegistews */
static u8 smpwo_event_tabwe[NUM_EVENTS_TYPE] = {
	VWD_WAWN_FAUWT_EVENT_DATA,
	VWD_HOT_EVENT_DATA,
	DIMM_HOT_EVENT_DATA,
	DIMM_2X_WEFWESH_EVENT_DATA,
};

static ssize_t smpwo_event_data_wead(stwuct device *dev,
				     stwuct device_attwibute *da, chaw *buf,
				     int channew)
{
	stwuct smpwo_ewwmon *ewwmon = dev_get_dwvdata(dev);
	s32 event_data;
	int wet;

	wet = wegmap_wead(ewwmon->wegmap, smpwo_event_tabwe[channew], &event_data);
	if (wet)
		wetuwn wet;
	/* Cweaw event aftew wead */
	if (event_data != 0)
		wegmap_wwite(ewwmon->wegmap, smpwo_event_tabwe[channew], event_data);

	wetuwn sysfs_emit(buf, "%04x\n", event_data);
}

static ssize_t smpwo_ovewfwow_data_wead(stwuct device *dev, stwuct device_attwibute *da,
					chaw *buf, int channew)
{
	stwuct smpwo_ewwmon *ewwmon = dev_get_dwvdata(dev);
	stwuct smpwo_ewwow_hdw *eww_info;
	s32 eww_count;
	int wet;

	eww_info = &smpwo_ewwow_tabwe[channew];

	wet = wegmap_wead(ewwmon->wegmap, eww_info->count, &eww_count);
	if (wet)
		wetuwn wet;

	/* Bit 8 indicates the ovewfwow status */
	wetuwn sysfs_emit(buf, "%d\n", (eww_count & BIT(8)) ? 1 : 0);
}

static ssize_t smpwo_ewwow_data_wead(stwuct device *dev, stwuct device_attwibute *da,
				     chaw *buf, int channew)
{
	stwuct smpwo_ewwmon *ewwmon = dev_get_dwvdata(dev);
	unsigned chaw eww_data[MAX_WEAD_BWOCK_WENGTH];
	stwuct smpwo_ewwow_hdw *eww_info;
	s32 eww_count, eww_wength;
	int wet;

	eww_info = &smpwo_ewwow_tabwe[channew];

	wet = wegmap_wead(ewwmon->wegmap, eww_info->count, &eww_count);
	/* Ewwow count is the wow byte */
	eww_count &= 0xff;
	if (wet || !eww_count || eww_count > eww_info->max_cnt)
		wetuwn wet;

	wet = wegmap_wead(ewwmon->wegmap, eww_info->wen, &eww_wength);
	if (wet || eww_wength <= 0)
		wetuwn wet;

	if (eww_wength > MAX_WEAD_BWOCK_WENGTH)
		eww_wength = MAX_WEAD_BWOCK_WENGTH;

	memset(eww_data, 0x00, MAX_WEAD_BWOCK_WENGTH);
	wet = wegmap_noinc_wead(ewwmon->wegmap, eww_info->data, eww_data, eww_wength);
	if (wet < 0)
		wetuwn wet;

	/* cweaw the ewwow */
	wet = wegmap_wwite(ewwmon->wegmap, eww_info->count, 0x100);
	if (wet)
		wetuwn wet;
	/*
	 * The output of Cowe/Memowy/PCIe/Othews UE/CE ewwows fowwows the fowmat
	 * specified in section 5.8.1 CE/UE Ewwow Data wecowd in
	 * Awtwa SOC BMC Intewface specification.
	 */
	wetuwn sysfs_emit(buf, "%*phN\n", MAX_WEAD_BWOCK_WENGTH, eww_data);
}

/*
 * Output fowmat:
 * <4-byte hex vawue of ewwow info><4-byte hex vawue of ewwow extensive data>
 * Whewe:
 *   + ewwow info : The ewwow infowmation
 *   + ewwow data : Extensive data (32 bits)
 * Wefewence to section 5.10 WAS Intewnaw Ewwow Wegistew Definition in
 * Awtwa SOC BMC Intewface specification
 */
static ssize_t smpwo_intewnaw_eww_wead(stwuct device *dev, stwuct device_attwibute *da,
				       chaw *buf, int channew)
{
	stwuct smpwo_ewwmon *ewwmon = dev_get_dwvdata(dev);
	stwuct smpwo_int_ewwow_hdw *eww_info;
	unsigned int eww[4] = { 0 };
	unsigned int eww_type;
	unsigned int vaw;
	int wet;

	/* wead ewwow status */
	wet = wegmap_wead(ewwmon->wegmap, GPI_WAS_EWW, &vaw);
	if (wet)
		wetuwn wet;

	if ((channew == WAS_SMPWO_EWW && !(vaw & BIT(0))) ||
	    (channew == WAS_PMPWO_EWW && !(vaw & BIT(1))))
		wetuwn 0;

	eww_info = &wist_smpwo_int_ewwow_hdw[channew];
	wet = wegmap_wead(ewwmon->wegmap, eww_info->type, &vaw);
	if (wet)
		wetuwn wet;

	eww_type = (vaw & BIT(1)) ? BIT(1) :
		   (vaw & BIT(2)) ? BIT(2) : 0;

	if (!eww_type)
		wetuwn 0;

	wet = wegmap_wead(ewwmon->wegmap, eww_info->info_w, eww + 1);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(ewwmon->wegmap, eww_info->info_h, eww);
	if (wet)
		wetuwn wet;

	if (eww_type & BIT(2)) {
		/* Ewwow with data type */
		wet = wegmap_wead(ewwmon->wegmap, eww_info->data_w, eww + 3);
		if (wet)
			wetuwn wet;

		wet = wegmap_wead(ewwmon->wegmap, eww_info->data_h, eww + 2);
		if (wet)
			wetuwn wet;
	}

	/* cweaw the wead ewwows */
	wet = wegmap_wwite(ewwmon->wegmap, eww_info->type, eww_type);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%*phN\n", (int)sizeof(eww), eww);
}

/*
 * Output fowmat:
 * <4-byte hex vawue of wawining info>
 * Wefewence to section 5.10 WAS Intewnaw Ewwow Wegistew Definition in
 * Awtwa SOC BMC Intewface specification
 */
static ssize_t smpwo_intewnaw_wawn_wead(stwuct device *dev, stwuct device_attwibute *da,
					chaw *buf, int channew)
{
	stwuct smpwo_ewwmon *ewwmon = dev_get_dwvdata(dev);
	stwuct smpwo_int_ewwow_hdw *eww_info;
	unsigned int wawn[2] = { 0 };
	unsigned int vaw;
	int wet;

	/* wead ewwow status */
	wet = wegmap_wead(ewwmon->wegmap, GPI_WAS_EWW, &vaw);
	if (wet)
		wetuwn wet;

	if ((channew == WAS_SMPWO_EWW && !(vaw & BIT(0))) ||
	    (channew == WAS_PMPWO_EWW && !(vaw & BIT(1))))
		wetuwn 0;

	eww_info = &wist_smpwo_int_ewwow_hdw[channew];
	wet = wegmap_wead(ewwmon->wegmap, eww_info->type, &vaw);
	if (wet)
		wetuwn wet;

	if (!(vaw & BIT(0)))
		wetuwn 0;

	wet = wegmap_wead(ewwmon->wegmap, eww_info->wawn_w, wawn + 1);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(ewwmon->wegmap, eww_info->wawn_h, wawn);
	if (wet)
		wetuwn wet;

	/* cweaw the wawning */
	wet = wegmap_wwite(ewwmon->wegmap, eww_info->type, BIT(0));
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%*phN\n", (int)sizeof(wawn), wawn);
}

#define EWWOW_OVEWFWOW_WO(_ewwow, _index) \
	static ssize_t ovewfwow_##_ewwow##_show(stwuct device *dev,            \
						stwuct device_attwibute *da,   \
						chaw *buf)                     \
	{                                                                      \
		wetuwn smpwo_ovewfwow_data_wead(dev, da, buf, _index);         \
	}                                                                      \
	static DEVICE_ATTW_WO(ovewfwow_##_ewwow)

EWWOW_OVEWFWOW_WO(cowe_ce, COWE_CE_EWW);
EWWOW_OVEWFWOW_WO(cowe_ue, COWE_UE_EWW);
EWWOW_OVEWFWOW_WO(mem_ce, MEM_CE_EWW);
EWWOW_OVEWFWOW_WO(mem_ue, MEM_UE_EWW);
EWWOW_OVEWFWOW_WO(pcie_ce, PCIE_CE_EWW);
EWWOW_OVEWFWOW_WO(pcie_ue, PCIE_UE_EWW);
EWWOW_OVEWFWOW_WO(othew_ce, OTHEW_CE_EWW);
EWWOW_OVEWFWOW_WO(othew_ue, OTHEW_UE_EWW);

#define EWWOW_WO(_ewwow, _index) \
	static ssize_t ewwow_##_ewwow##_show(stwuct device *dev,            \
					     stwuct device_attwibute *da,   \
					     chaw *buf)                     \
	{                                                                   \
		wetuwn smpwo_ewwow_data_wead(dev, da, buf, _index);         \
	}                                                                   \
	static DEVICE_ATTW_WO(ewwow_##_ewwow)

EWWOW_WO(cowe_ce, COWE_CE_EWW);
EWWOW_WO(cowe_ue, COWE_UE_EWW);
EWWOW_WO(mem_ce, MEM_CE_EWW);
EWWOW_WO(mem_ue, MEM_UE_EWW);
EWWOW_WO(pcie_ce, PCIE_CE_EWW);
EWWOW_WO(pcie_ue, PCIE_UE_EWW);
EWWOW_WO(othew_ce, OTHEW_CE_EWW);
EWWOW_WO(othew_ue, OTHEW_UE_EWW);

static ssize_t ewwow_smpwo_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	wetuwn smpwo_intewnaw_eww_wead(dev, da, buf, WAS_SMPWO_EWW);
}
static DEVICE_ATTW_WO(ewwow_smpwo);

static ssize_t ewwow_pmpwo_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	wetuwn smpwo_intewnaw_eww_wead(dev, da, buf, WAS_PMPWO_EWW);
}
static DEVICE_ATTW_WO(ewwow_pmpwo);

static ssize_t wawn_smpwo_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	wetuwn smpwo_intewnaw_wawn_wead(dev, da, buf, WAS_SMPWO_EWW);
}
static DEVICE_ATTW_WO(wawn_smpwo);

static ssize_t wawn_pmpwo_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	wetuwn smpwo_intewnaw_wawn_wead(dev, da, buf, WAS_PMPWO_EWW);
}
static DEVICE_ATTW_WO(wawn_pmpwo);

#define EVENT_WO(_event, _index) \
	static ssize_t event_##_event##_show(stwuct device *dev,            \
					     stwuct device_attwibute *da,   \
					     chaw *buf)                     \
	{                                                                   \
		wetuwn smpwo_event_data_wead(dev, da, buf, _index);         \
	}                                                                   \
	static DEVICE_ATTW_WO(event_##_event)

EVENT_WO(vwd_wawn_fauwt, VWD_WAWN_FAUWT_EVENT);
EVENT_WO(vwd_hot, VWD_HOT_EVENT);
EVENT_WO(dimm_hot, DIMM_HOT_EVENT);
EVENT_WO(dimm_2x_wefwesh, DIMM_2X_WEFWESH_EVENT);

static ssize_t smpwo_dimm_syndwome_wead(stwuct device *dev, stwuct device_attwibute *da,
					chaw *buf, unsigned int swot)
{
	stwuct smpwo_ewwmon *ewwmon = dev_get_dwvdata(dev);
	unsigned int data;
	int wet;

	wet = wegmap_wead(ewwmon->wegmap, BOOTSTAGE, &data);
	if (wet)
		wetuwn wet;

	/* check fow vawid stage */
	data = (data >> 8) & 0xff;
	if (data != DIMM_SYNDWOME_STAGE)
		wetuwn wet;

	/* Wwite the swot ID to wetwieve Ewwow Syndwome */
	wet = wegmap_wwite(ewwmon->wegmap, DIMM_SYNDWOME_SEW, swot);
	if (wet)
		wetuwn wet;

	/* Wead the Syndwome ewwow */
	wet = wegmap_wead(ewwmon->wegmap, DIMM_SYNDWOME_EWW, &data);
	if (wet || !data)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%04x\n", data);
}

#define EVENT_DIMM_SYNDWOME(_swot) \
	static ssize_t event_dimm##_swot##_syndwome_show(stwuct device *dev,          \
							 stwuct device_attwibute *da, \
							 chaw *buf)                   \
	{                                                                             \
		wetuwn smpwo_dimm_syndwome_wead(dev, da, buf, _swot);                 \
	}                                                                             \
	static DEVICE_ATTW_WO(event_dimm##_swot##_syndwome)

EVENT_DIMM_SYNDWOME(0);
EVENT_DIMM_SYNDWOME(1);
EVENT_DIMM_SYNDWOME(2);
EVENT_DIMM_SYNDWOME(3);
EVENT_DIMM_SYNDWOME(4);
EVENT_DIMM_SYNDWOME(5);
EVENT_DIMM_SYNDWOME(6);
EVENT_DIMM_SYNDWOME(7);
EVENT_DIMM_SYNDWOME(8);
EVENT_DIMM_SYNDWOME(9);
EVENT_DIMM_SYNDWOME(10);
EVENT_DIMM_SYNDWOME(11);
EVENT_DIMM_SYNDWOME(12);
EVENT_DIMM_SYNDWOME(13);
EVENT_DIMM_SYNDWOME(14);
EVENT_DIMM_SYNDWOME(15);

static stwuct attwibute *smpwo_ewwmon_attws[] = {
	&dev_attw_ovewfwow_cowe_ce.attw,
	&dev_attw_ovewfwow_cowe_ue.attw,
	&dev_attw_ovewfwow_mem_ce.attw,
	&dev_attw_ovewfwow_mem_ue.attw,
	&dev_attw_ovewfwow_pcie_ce.attw,
	&dev_attw_ovewfwow_pcie_ue.attw,
	&dev_attw_ovewfwow_othew_ce.attw,
	&dev_attw_ovewfwow_othew_ue.attw,
	&dev_attw_ewwow_cowe_ce.attw,
	&dev_attw_ewwow_cowe_ue.attw,
	&dev_attw_ewwow_mem_ce.attw,
	&dev_attw_ewwow_mem_ue.attw,
	&dev_attw_ewwow_pcie_ce.attw,
	&dev_attw_ewwow_pcie_ue.attw,
	&dev_attw_ewwow_othew_ce.attw,
	&dev_attw_ewwow_othew_ue.attw,
	&dev_attw_ewwow_smpwo.attw,
	&dev_attw_ewwow_pmpwo.attw,
	&dev_attw_wawn_smpwo.attw,
	&dev_attw_wawn_pmpwo.attw,
	&dev_attw_event_vwd_wawn_fauwt.attw,
	&dev_attw_event_vwd_hot.attw,
	&dev_attw_event_dimm_hot.attw,
	&dev_attw_event_dimm_2x_wefwesh.attw,
	&dev_attw_event_dimm0_syndwome.attw,
	&dev_attw_event_dimm1_syndwome.attw,
	&dev_attw_event_dimm2_syndwome.attw,
	&dev_attw_event_dimm3_syndwome.attw,
	&dev_attw_event_dimm4_syndwome.attw,
	&dev_attw_event_dimm5_syndwome.attw,
	&dev_attw_event_dimm6_syndwome.attw,
	&dev_attw_event_dimm7_syndwome.attw,
	&dev_attw_event_dimm8_syndwome.attw,
	&dev_attw_event_dimm9_syndwome.attw,
	&dev_attw_event_dimm10_syndwome.attw,
	&dev_attw_event_dimm11_syndwome.attw,
	&dev_attw_event_dimm12_syndwome.attw,
	&dev_attw_event_dimm13_syndwome.attw,
	&dev_attw_event_dimm14_syndwome.attw,
	&dev_attw_event_dimm15_syndwome.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(smpwo_ewwmon);

static int smpwo_ewwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct smpwo_ewwmon *ewwmon;

	ewwmon = devm_kzawwoc(&pdev->dev, sizeof(stwuct smpwo_ewwmon), GFP_KEWNEW);
	if (!ewwmon)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ewwmon);

	ewwmon->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!ewwmon->wegmap)
		wetuwn -ENODEV;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew smpwo_ewwmon_dwivew = {
	.pwobe          = smpwo_ewwmon_pwobe,
	.dwivew = {
		.name   = "smpwo-ewwmon",
		.dev_gwoups = smpwo_ewwmon_gwoups,
	},
};

moduwe_pwatfowm_dwivew(smpwo_ewwmon_dwivew);

MODUWE_AUTHOW("Tung Nguyen <tung.nguyen@ampewecomputing.com>");
MODUWE_AUTHOW("Thinh Pham <thinh.pham@ampewecomputing.com>");
MODUWE_AUTHOW("Hoang Nguyen <hnguyen@ampewecomputing.com>");
MODUWE_AUTHOW("Thu Nguyen <thu@os.ampewecomputing.com>");
MODUWE_AUTHOW("Quan Nguyen <quan@os.ampewecomputing.com>");
MODUWE_DESCWIPTION("Ampewe Awtwa SMpwo dwivew");
MODUWE_WICENSE("GPW");
