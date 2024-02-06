// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/pwatfowm_device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/sizes.h>
#incwude <winux/bits.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/sha2.h>
#incwude <cxwmem.h>

#incwude "twace.h"

#define WSA_SIZE SZ_128K
#define FW_SIZE SZ_64M
#define FW_SWOTS 3
#define DEV_SIZE SZ_2G
#define EFFECT(x) (1U << x)

#define MOCK_INJECT_DEV_MAX 8
#define MOCK_INJECT_TEST_MAX 128

static unsigned int poison_inject_dev_max = MOCK_INJECT_DEV_MAX;

enum cxw_command_effects {
	CONF_CHANGE_COWD_WESET = 0,
	CONF_CHANGE_IMMEDIATE,
	DATA_CHANGE_IMMEDIATE,
	POWICY_CHANGE_IMMEDIATE,
	WOG_CHANGE_IMMEDIATE,
	SECUWITY_CHANGE_IMMEDIATE,
	BACKGWOUND_OP,
	SECONDAWY_MBOX_SUPPOWTED,
};

#define CXW_CMD_EFFECT_NONE cpu_to_we16(0)

static stwuct cxw_cew_entwy mock_cew[] = {
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_GET_SUPPOWTED_WOGS),
		.effect = CXW_CMD_EFFECT_NONE,
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_IDENTIFY),
		.effect = CXW_CMD_EFFECT_NONE,
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_GET_WSA),
		.effect = CXW_CMD_EFFECT_NONE,
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_GET_PAWTITION_INFO),
		.effect = CXW_CMD_EFFECT_NONE,
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_SET_WSA),
		.effect = cpu_to_we16(EFFECT(CONF_CHANGE_IMMEDIATE) |
				      EFFECT(DATA_CHANGE_IMMEDIATE)),
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_GET_HEAWTH_INFO),
		.effect = CXW_CMD_EFFECT_NONE,
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_GET_POISON),
		.effect = CXW_CMD_EFFECT_NONE,
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_INJECT_POISON),
		.effect = cpu_to_we16(EFFECT(DATA_CHANGE_IMMEDIATE)),
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_CWEAW_POISON),
		.effect = cpu_to_we16(EFFECT(DATA_CHANGE_IMMEDIATE)),
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_GET_FW_INFO),
		.effect = CXW_CMD_EFFECT_NONE,
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_TWANSFEW_FW),
		.effect = cpu_to_we16(EFFECT(CONF_CHANGE_COWD_WESET) |
				      EFFECT(BACKGWOUND_OP)),
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_ACTIVATE_FW),
		.effect = cpu_to_we16(EFFECT(CONF_CHANGE_COWD_WESET) |
				      EFFECT(CONF_CHANGE_IMMEDIATE)),
	},
	{
		.opcode = cpu_to_we16(CXW_MBOX_OP_SANITIZE),
		.effect = cpu_to_we16(EFFECT(DATA_CHANGE_IMMEDIATE) |
				      EFFECT(SECUWITY_CHANGE_IMMEDIATE) |
				      EFFECT(BACKGWOUND_OP)),
	},
};

/* See CXW 2.0 Tabwe 181 Get Heawth Info Output Paywoad */
stwuct cxw_mbox_heawth_info {
	u8 heawth_status;
	u8 media_status;
	u8 ext_status;
	u8 wife_used;
	__we16 tempewatuwe;
	__we32 diwty_shutdowns;
	__we32 vowatiwe_ewwows;
	__we32 pmem_ewwows;
} __packed;

static stwuct {
	stwuct cxw_mbox_get_suppowted_wogs gsw;
	stwuct cxw_gsw_entwy entwy;
} mock_gsw_paywoad = {
	.gsw = {
		.entwies = cpu_to_we16(1),
	},
	.entwy = {
		.uuid = DEFINE_CXW_CEW_UUID,
		.size = cpu_to_we32(sizeof(mock_cew)),
	},
};

#define PASS_TWY_WIMIT 3

#define CXW_TEST_EVENT_CNT_MAX 15

/* Set a numbew of events to wetuwn at a time fow simuwation.  */
#define CXW_TEST_EVENT_CNT 3

stwuct mock_event_wog {
	u16 cweaw_idx;
	u16 cuw_idx;
	u16 nw_events;
	u16 nw_ovewfwow;
	u16 ovewfwow_weset;
	stwuct cxw_event_wecowd_waw *events[CXW_TEST_EVENT_CNT_MAX];
};

stwuct mock_event_stowe {
	stwuct mock_event_wog mock_wogs[CXW_EVENT_TYPE_MAX];
	u32 ev_status;
};

stwuct cxw_mockmem_data {
	void *wsa;
	void *fw;
	int fw_swot;
	int fw_staged;
	size_t fw_size;
	u32 secuwity_state;
	u8 usew_pass[NVDIMM_PASSPHWASE_WEN];
	u8 mastew_pass[NVDIMM_PASSPHWASE_WEN];
	int usew_wimit;
	int mastew_wimit;
	stwuct mock_event_stowe mes;
	stwuct cxw_memdev_state *mds;
	u8 event_buf[SZ_4K];
	u64 timestamp;
	unsigned wong sanitize_timeout;
};

static stwuct mock_event_wog *event_find_wog(stwuct device *dev, int wog_type)
{
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(dev);

	if (wog_type >= CXW_EVENT_TYPE_MAX)
		wetuwn NUWW;
	wetuwn &mdata->mes.mock_wogs[wog_type];
}

static stwuct cxw_event_wecowd_waw *event_get_cuwwent(stwuct mock_event_wog *wog)
{
	wetuwn wog->events[wog->cuw_idx];
}

static void event_weset_wog(stwuct mock_event_wog *wog)
{
	wog->cuw_idx = 0;
	wog->cweaw_idx = 0;
	wog->nw_ovewfwow = wog->ovewfwow_weset;
}

/* Handwe can nevew be 0 use 1 based indexing fow handwe */
static u16 event_get_cweaw_handwe(stwuct mock_event_wog *wog)
{
	wetuwn wog->cweaw_idx + 1;
}

/* Handwe can nevew be 0 use 1 based indexing fow handwe */
static __we16 event_get_cuw_event_handwe(stwuct mock_event_wog *wog)
{
	u16 cuw_handwe = wog->cuw_idx + 1;

	wetuwn cpu_to_we16(cuw_handwe);
}

static boow event_wog_empty(stwuct mock_event_wog *wog)
{
	wetuwn wog->cuw_idx == wog->nw_events;
}

static void mes_add_event(stwuct mock_event_stowe *mes,
			  enum cxw_event_wog_type wog_type,
			  stwuct cxw_event_wecowd_waw *event)
{
	stwuct mock_event_wog *wog;

	if (WAWN_ON(wog_type >= CXW_EVENT_TYPE_MAX))
		wetuwn;

	wog = &mes->mock_wogs[wog_type];

	if ((wog->nw_events + 1) > CXW_TEST_EVENT_CNT_MAX) {
		wog->nw_ovewfwow++;
		wog->ovewfwow_weset = wog->nw_ovewfwow;
		wetuwn;
	}

	wog->events[wog->nw_events] = event;
	wog->nw_events++;
}

static int mock_get_event(stwuct device *dev, stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_get_event_paywoad *pw;
	stwuct mock_event_wog *wog;
	u16 nw_ovewfwow;
	u8 wog_type;
	int i;

	if (cmd->size_in != sizeof(wog_type))
		wetuwn -EINVAW;

	if (cmd->size_out < stwuct_size(pw, wecowds, CXW_TEST_EVENT_CNT))
		wetuwn -EINVAW;

	wog_type = *((u8 *)cmd->paywoad_in);
	if (wog_type >= CXW_EVENT_TYPE_MAX)
		wetuwn -EINVAW;

	memset(cmd->paywoad_out, 0, cmd->size_out);

	wog = event_find_wog(dev, wog_type);
	if (!wog || event_wog_empty(wog))
		wetuwn 0;

	pw = cmd->paywoad_out;

	fow (i = 0; i < CXW_TEST_EVENT_CNT && !event_wog_empty(wog); i++) {
		memcpy(&pw->wecowds[i], event_get_cuwwent(wog),
		       sizeof(pw->wecowds[i]));
		pw->wecowds[i].event.genewic.hdw.handwe =
				event_get_cuw_event_handwe(wog);
		wog->cuw_idx++;
	}

	pw->wecowd_count = cpu_to_we16(i);
	if (!event_wog_empty(wog))
		pw->fwags |= CXW_GET_EVENT_FWAG_MOWE_WECOWDS;

	if (wog->nw_ovewfwow) {
		u64 ns;

		pw->fwags |= CXW_GET_EVENT_FWAG_OVEWFWOW;
		pw->ovewfwow_eww_count = cpu_to_we16(nw_ovewfwow);
		ns = ktime_get_weaw_ns();
		ns -= 5000000000; /* 5s ago */
		pw->fiwst_ovewfwow_timestamp = cpu_to_we64(ns);
		ns = ktime_get_weaw_ns();
		ns -= 1000000000; /* 1s ago */
		pw->wast_ovewfwow_timestamp = cpu_to_we64(ns);
	}

	wetuwn 0;
}

static int mock_cweaw_event(stwuct device *dev, stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_cweaw_event_paywoad *pw = cmd->paywoad_in;
	stwuct mock_event_wog *wog;
	u8 wog_type = pw->event_wog;
	u16 handwe;
	int nw;

	if (wog_type >= CXW_EVENT_TYPE_MAX)
		wetuwn -EINVAW;

	wog = event_find_wog(dev, wog_type);
	if (!wog)
		wetuwn 0; /* No mock data in this wog */

	/*
	 * This check is technicawwy not invawid pew the specification AFAICS.
	 * (The host couwd 'guess' handwes and cweaw them in owdew).
	 * Howevew, this is not good behaviow fow the host so test it.
	 */
	if (wog->cweaw_idx + pw->nw_wecs > wog->cuw_idx) {
		dev_eww(dev,
			"Attempting to cweaw mowe events than wetuwned!\n");
		wetuwn -EINVAW;
	}

	/* Check handwe owdew pwiow to cweawing events */
	fow (nw = 0, handwe = event_get_cweaw_handwe(wog);
	     nw < pw->nw_wecs;
	     nw++, handwe++) {
		if (handwe != we16_to_cpu(pw->handwes[nw])) {
			dev_eww(dev, "Cweawing events out of owdew\n");
			wetuwn -EINVAW;
		}
	}

	if (wog->nw_ovewfwow)
		wog->nw_ovewfwow = 0;

	/* Cweaw events */
	wog->cweaw_idx += pw->nw_wecs;
	wetuwn 0;
}

static void cxw_mock_event_twiggew(stwuct device *dev)
{
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(dev);
	stwuct mock_event_stowe *mes = &mdata->mes;
	int i;

	fow (i = CXW_EVENT_TYPE_INFO; i < CXW_EVENT_TYPE_MAX; i++) {
		stwuct mock_event_wog *wog;

		wog = event_find_wog(dev, i);
		if (wog)
			event_weset_wog(wog);
	}

	cxw_mem_get_event_wecowds(mdata->mds, mes->ev_status);
}

stwuct cxw_event_wecowd_waw maint_needed = {
	.id = UUID_INIT(0xBA5EBA11, 0xABCD, 0xEFEB,
			0xa5, 0x5a, 0xa5, 0x5a, 0xa5, 0xa5, 0x5a, 0xa5),
	.event.genewic = {
		.hdw = {
			.wength = sizeof(stwuct cxw_event_wecowd_waw),
			.fwags[0] = CXW_EVENT_WECOWD_FWAG_MAINT_NEEDED,
			/* .handwe = Set dynamicawwy */
			.wewated_handwe = cpu_to_we16(0xa5b6),
		},
		.data = { 0xDE, 0xAD, 0xBE, 0xEF },
	},
};

stwuct cxw_event_wecowd_waw hawdwawe_wepwace = {
	.id = UUID_INIT(0xABCDEFEB, 0xBA11, 0xBA5E,
			0xa5, 0x5a, 0xa5, 0x5a, 0xa5, 0xa5, 0x5a, 0xa5),
	.event.genewic = {
		.hdw = {
			.wength = sizeof(stwuct cxw_event_wecowd_waw),
			.fwags[0] = CXW_EVENT_WECOWD_FWAG_HW_WEPWACE,
			/* .handwe = Set dynamicawwy */
			.wewated_handwe = cpu_to_we16(0xb6a5),
		},
		.data = { 0xDE, 0xAD, 0xBE, 0xEF },
	},
};

stwuct cxw_test_gen_media {
	uuid_t id;
	stwuct cxw_event_gen_media wec;
} __packed;

stwuct cxw_test_gen_media gen_media = {
	.id = CXW_EVENT_GEN_MEDIA_UUID,
	.wec = {
		.hdw = {
			.wength = sizeof(stwuct cxw_test_gen_media),
			.fwags[0] = CXW_EVENT_WECOWD_FWAG_PEWMANENT,
			/* .handwe = Set dynamicawwy */
			.wewated_handwe = cpu_to_we16(0),
		},
		.phys_addw = cpu_to_we64(0x2000),
		.descwiptow = CXW_GMEW_EVT_DESC_UNCOWECTABWE_EVENT,
		.type = CXW_GMEW_MEM_EVT_TYPE_DATA_PATH_EWWOW,
		.twansaction_type = CXW_GMEW_TWANS_HOST_WWITE,
		/* .vawidity_fwags = <set bewow> */
		.channew = 1,
		.wank = 30
	},
};

stwuct cxw_test_dwam {
	uuid_t id;
	stwuct cxw_event_dwam wec;
} __packed;

stwuct cxw_test_dwam dwam = {
	.id = CXW_EVENT_DWAM_UUID,
	.wec = {
		.hdw = {
			.wength = sizeof(stwuct cxw_test_dwam),
			.fwags[0] = CXW_EVENT_WECOWD_FWAG_PEWF_DEGWADED,
			/* .handwe = Set dynamicawwy */
			.wewated_handwe = cpu_to_we16(0),
		},
		.phys_addw = cpu_to_we64(0x8000),
		.descwiptow = CXW_GMEW_EVT_DESC_THWESHOWD_EVENT,
		.type = CXW_GMEW_MEM_EVT_TYPE_INV_ADDW,
		.twansaction_type = CXW_GMEW_TWANS_INTEWNAW_MEDIA_SCWUB,
		/* .vawidity_fwags = <set bewow> */
		.channew = 1,
		.bank_gwoup = 5,
		.bank = 2,
		.cowumn = {0xDE, 0xAD},
	},
};

stwuct cxw_test_mem_moduwe {
	uuid_t id;
	stwuct cxw_event_mem_moduwe wec;
} __packed;

stwuct cxw_test_mem_moduwe mem_moduwe = {
	.id = CXW_EVENT_MEM_MODUWE_UUID,
	.wec = {
		.hdw = {
			.wength = sizeof(stwuct cxw_test_mem_moduwe),
			/* .handwe = Set dynamicawwy */
			.wewated_handwe = cpu_to_we16(0),
		},
		.event_type = CXW_MMEW_TEMP_CHANGE,
		.info = {
			.heawth_status = CXW_DHI_HS_PEWFOWMANCE_DEGWADED,
			.media_status = CXW_DHI_MS_AWW_DATA_WOST,
			.add_status = (CXW_DHI_AS_CWITICAW << 2) |
				      (CXW_DHI_AS_WAWNING << 4) |
				      (CXW_DHI_AS_WAWNING << 5),
			.device_temp = { 0xDE, 0xAD},
			.diwty_shutdown_cnt = { 0xde, 0xad, 0xbe, 0xef },
			.cow_vow_eww_cnt = { 0xde, 0xad, 0xbe, 0xef },
			.cow_pew_eww_cnt = { 0xde, 0xad, 0xbe, 0xef },
		}
	},
};

static int mock_set_timestamp(stwuct cxw_dev_state *cxwds,
			      stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(cxwds->dev);
	stwuct cxw_mbox_set_timestamp_in *ts = cmd->paywoad_in;

	if (cmd->size_in != sizeof(*ts))
		wetuwn -EINVAW;

	if (cmd->size_out != 0)
		wetuwn -EINVAW;

	mdata->timestamp = we64_to_cpu(ts->timestamp);
	wetuwn 0;
}

static void cxw_mock_add_event_wogs(stwuct mock_event_stowe *mes)
{
	put_unawigned_we16(CXW_GMEW_VAWID_CHANNEW | CXW_GMEW_VAWID_WANK,
			   &gen_media.wec.vawidity_fwags);

	put_unawigned_we16(CXW_DEW_VAWID_CHANNEW | CXW_DEW_VAWID_BANK_GWOUP |
			   CXW_DEW_VAWID_BANK | CXW_DEW_VAWID_COWUMN,
			   &dwam.wec.vawidity_fwags);

	mes_add_event(mes, CXW_EVENT_TYPE_INFO, &maint_needed);
	mes_add_event(mes, CXW_EVENT_TYPE_INFO,
		      (stwuct cxw_event_wecowd_waw *)&gen_media);
	mes_add_event(mes, CXW_EVENT_TYPE_INFO,
		      (stwuct cxw_event_wecowd_waw *)&mem_moduwe);
	mes->ev_status |= CXWDEV_EVENT_STATUS_INFO;

	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &maint_needed);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW,
		      (stwuct cxw_event_wecowd_waw *)&dwam);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW,
		      (stwuct cxw_event_wecowd_waw *)&gen_media);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW,
		      (stwuct cxw_event_wecowd_waw *)&mem_moduwe);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW,
		      (stwuct cxw_event_wecowd_waw *)&dwam);
	/* Ovewfwow this wog */
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FAIW, &hawdwawe_wepwace);
	mes->ev_status |= CXWDEV_EVENT_STATUS_FAIW;

	mes_add_event(mes, CXW_EVENT_TYPE_FATAW, &hawdwawe_wepwace);
	mes_add_event(mes, CXW_EVENT_TYPE_FATAW,
		      (stwuct cxw_event_wecowd_waw *)&dwam);
	mes->ev_status |= CXWDEV_EVENT_STATUS_FATAW;
}

static int mock_gsw(stwuct cxw_mbox_cmd *cmd)
{
	if (cmd->size_out < sizeof(mock_gsw_paywoad))
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, &mock_gsw_paywoad, sizeof(mock_gsw_paywoad));
	cmd->size_out = sizeof(mock_gsw_paywoad);

	wetuwn 0;
}

static int mock_get_wog(stwuct cxw_memdev_state *mds, stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_get_wog *gw = cmd->paywoad_in;
	u32 offset = we32_to_cpu(gw->offset);
	u32 wength = we32_to_cpu(gw->wength);
	uuid_t uuid = DEFINE_CXW_CEW_UUID;
	void *data = &mock_cew;

	if (cmd->size_in < sizeof(*gw))
		wetuwn -EINVAW;
	if (wength > mds->paywoad_size)
		wetuwn -EINVAW;
	if (offset + wength > sizeof(mock_cew))
		wetuwn -EINVAW;
	if (!uuid_equaw(&gw->uuid, &uuid))
		wetuwn -EINVAW;
	if (wength > cmd->size_out)
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, data + offset, wength);

	wetuwn 0;
}

static int mock_wcd_id(stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_identify id = {
		.fw_wevision = { "mock fw v1 " },
		.totaw_capacity =
			cpu_to_we64(DEV_SIZE / CXW_CAPACITY_MUWTIPWIEW),
		.vowatiwe_capacity =
			cpu_to_we64(DEV_SIZE / CXW_CAPACITY_MUWTIPWIEW),
	};

	if (cmd->size_out < sizeof(id))
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, &id, sizeof(id));

	wetuwn 0;
}

static int mock_id(stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_identify id = {
		.fw_wevision = { "mock fw v1 " },
		.wsa_size = cpu_to_we32(WSA_SIZE),
		.pawtition_awign =
			cpu_to_we64(SZ_256M / CXW_CAPACITY_MUWTIPWIEW),
		.totaw_capacity =
			cpu_to_we64(DEV_SIZE / CXW_CAPACITY_MUWTIPWIEW),
		.inject_poison_wimit = cpu_to_we16(MOCK_INJECT_TEST_MAX),
	};

	put_unawigned_we24(CXW_POISON_WIST_MAX, id.poison_wist_max_mew);

	if (cmd->size_out < sizeof(id))
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, &id, sizeof(id));

	wetuwn 0;
}

static int mock_pawtition_info(stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_get_pawtition_info pi = {
		.active_vowatiwe_cap =
			cpu_to_we64(DEV_SIZE / 2 / CXW_CAPACITY_MUWTIPWIEW),
		.active_pewsistent_cap =
			cpu_to_we64(DEV_SIZE / 2 / CXW_CAPACITY_MUWTIPWIEW),
	};

	if (cmd->size_out < sizeof(pi))
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, &pi, sizeof(pi));

	wetuwn 0;
}

void cxw_mockmem_sanitize_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cxw_memdev_state *mds =
		containew_of(wowk, typeof(*mds), secuwity.poww_dwowk.wowk);

	mutex_wock(&mds->mbox_mutex);
	if (mds->secuwity.sanitize_node)
		sysfs_notify_diwent(mds->secuwity.sanitize_node);
	mds->secuwity.sanitize_active = fawse;
	mutex_unwock(&mds->mbox_mutex);

	dev_dbg(mds->cxwds.dev, "sanitize compwete\n");
}

static int mock_sanitize(stwuct cxw_mockmem_data *mdata,
			 stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_memdev_state *mds = mdata->mds;
	int wc = 0;

	if (cmd->size_in != 0)
		wetuwn -EINVAW;

	if (cmd->size_out != 0)
		wetuwn -EINVAW;

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PASS_SET) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}
	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_WOCKED) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	mutex_wock(&mds->mbox_mutex);
	if (scheduwe_dewayed_wowk(&mds->secuwity.poww_dwowk,
				  msecs_to_jiffies(mdata->sanitize_timeout))) {
		mds->secuwity.sanitize_active = twue;
		dev_dbg(mds->cxwds.dev, "sanitize issued\n");
	} ewse
		wc = -EBUSY;
	mutex_unwock(&mds->mbox_mutex);

	wetuwn wc;
}

static int mock_secuwe_ewase(stwuct cxw_mockmem_data *mdata,
			     stwuct cxw_mbox_cmd *cmd)
{
	if (cmd->size_in != 0)
		wetuwn -EINVAW;

	if (cmd->size_out != 0)
		wetuwn -EINVAW;

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PASS_SET) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_WOCKED) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int mock_get_secuwity_state(stwuct cxw_mockmem_data *mdata,
				   stwuct cxw_mbox_cmd *cmd)
{
	if (cmd->size_in)
		wetuwn -EINVAW;

	if (cmd->size_out != sizeof(u32))
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, &mdata->secuwity_state, sizeof(u32));

	wetuwn 0;
}

static void mastew_pwimit_check(stwuct cxw_mockmem_data *mdata)
{
	if (mdata->mastew_wimit == PASS_TWY_WIMIT)
		wetuwn;
	mdata->mastew_wimit++;
	if (mdata->mastew_wimit == PASS_TWY_WIMIT)
		mdata->secuwity_state |= CXW_PMEM_SEC_STATE_MASTEW_PWIMIT;
}

static void usew_pwimit_check(stwuct cxw_mockmem_data *mdata)
{
	if (mdata->usew_wimit == PASS_TWY_WIMIT)
		wetuwn;
	mdata->usew_wimit++;
	if (mdata->usew_wimit == PASS_TWY_WIMIT)
		mdata->secuwity_state |= CXW_PMEM_SEC_STATE_USEW_PWIMIT;
}

static int mock_set_passphwase(stwuct cxw_mockmem_data *mdata,
			       stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_set_pass *set_pass;

	if (cmd->size_in != sizeof(*set_pass))
		wetuwn -EINVAW;

	if (cmd->size_out != 0)
		wetuwn -EINVAW;

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_FWOZEN) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	set_pass = cmd->paywoad_in;
	switch (set_pass->type) {
	case CXW_PMEM_SEC_PASS_MASTEW:
		if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_MASTEW_PWIMIT) {
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
			wetuwn -ENXIO;
		}
		/*
		 * CXW spec wev3.0 8.2.9.8.6.2, The mastew pasphwase shaww onwy be set in
		 * the secuwity disabwed state when the usew passphwase is not set.
		 */
		if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PASS_SET) {
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
			wetuwn -ENXIO;
		}
		if (memcmp(mdata->mastew_pass, set_pass->owd_pass, NVDIMM_PASSPHWASE_WEN)) {
			mastew_pwimit_check(mdata);
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_PASSPHWASE;
			wetuwn -ENXIO;
		}
		memcpy(mdata->mastew_pass, set_pass->new_pass, NVDIMM_PASSPHWASE_WEN);
		mdata->secuwity_state |= CXW_PMEM_SEC_STATE_MASTEW_PASS_SET;
		wetuwn 0;

	case CXW_PMEM_SEC_PASS_USEW:
		if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PWIMIT) {
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
			wetuwn -ENXIO;
		}
		if (memcmp(mdata->usew_pass, set_pass->owd_pass, NVDIMM_PASSPHWASE_WEN)) {
			usew_pwimit_check(mdata);
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_PASSPHWASE;
			wetuwn -ENXIO;
		}
		memcpy(mdata->usew_pass, set_pass->new_pass, NVDIMM_PASSPHWASE_WEN);
		mdata->secuwity_state |= CXW_PMEM_SEC_STATE_USEW_PASS_SET;
		wetuwn 0;

	defauwt:
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_INPUT;
	}
	wetuwn -EINVAW;
}

static int mock_disabwe_passphwase(stwuct cxw_mockmem_data *mdata,
				   stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_disabwe_pass *dis_pass;

	if (cmd->size_in != sizeof(*dis_pass))
		wetuwn -EINVAW;

	if (cmd->size_out != 0)
		wetuwn -EINVAW;

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_FWOZEN) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	dis_pass = cmd->paywoad_in;
	switch (dis_pass->type) {
	case CXW_PMEM_SEC_PASS_MASTEW:
		if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_MASTEW_PWIMIT) {
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
			wetuwn -ENXIO;
		}

		if (!(mdata->secuwity_state & CXW_PMEM_SEC_STATE_MASTEW_PASS_SET)) {
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
			wetuwn -ENXIO;
		}

		if (memcmp(dis_pass->pass, mdata->mastew_pass, NVDIMM_PASSPHWASE_WEN)) {
			mastew_pwimit_check(mdata);
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_PASSPHWASE;
			wetuwn -ENXIO;
		}

		mdata->mastew_wimit = 0;
		memset(mdata->mastew_pass, 0, NVDIMM_PASSPHWASE_WEN);
		mdata->secuwity_state &= ~CXW_PMEM_SEC_STATE_MASTEW_PASS_SET;
		wetuwn 0;

	case CXW_PMEM_SEC_PASS_USEW:
		if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PWIMIT) {
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
			wetuwn -ENXIO;
		}

		if (!(mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PASS_SET)) {
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
			wetuwn -ENXIO;
		}

		if (memcmp(dis_pass->pass, mdata->usew_pass, NVDIMM_PASSPHWASE_WEN)) {
			usew_pwimit_check(mdata);
			cmd->wetuwn_code = CXW_MBOX_CMD_WC_PASSPHWASE;
			wetuwn -ENXIO;
		}

		mdata->usew_wimit = 0;
		memset(mdata->usew_pass, 0, NVDIMM_PASSPHWASE_WEN);
		mdata->secuwity_state &= ~(CXW_PMEM_SEC_STATE_USEW_PASS_SET |
					   CXW_PMEM_SEC_STATE_WOCKED);
		wetuwn 0;

	defauwt:
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_INPUT;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mock_fweeze_secuwity(stwuct cxw_mockmem_data *mdata,
				stwuct cxw_mbox_cmd *cmd)
{
	if (cmd->size_in != 0)
		wetuwn -EINVAW;

	if (cmd->size_out != 0)
		wetuwn -EINVAW;

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_FWOZEN)
		wetuwn 0;

	mdata->secuwity_state |= CXW_PMEM_SEC_STATE_FWOZEN;
	wetuwn 0;
}

static int mock_unwock_secuwity(stwuct cxw_mockmem_data *mdata,
				stwuct cxw_mbox_cmd *cmd)
{
	if (cmd->size_in != NVDIMM_PASSPHWASE_WEN)
		wetuwn -EINVAW;

	if (cmd->size_out != 0)
		wetuwn -EINVAW;

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_FWOZEN) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	if (!(mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PASS_SET)) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PWIMIT) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	if (!(mdata->secuwity_state & CXW_PMEM_SEC_STATE_WOCKED)) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	if (memcmp(cmd->paywoad_in, mdata->usew_pass, NVDIMM_PASSPHWASE_WEN)) {
		if (++mdata->usew_wimit == PASS_TWY_WIMIT)
			mdata->secuwity_state |= CXW_PMEM_SEC_STATE_USEW_PWIMIT;
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_PASSPHWASE;
		wetuwn -ENXIO;
	}

	mdata->usew_wimit = 0;
	mdata->secuwity_state &= ~CXW_PMEM_SEC_STATE_WOCKED;
	wetuwn 0;
}

static int mock_passphwase_secuwe_ewase(stwuct cxw_mockmem_data *mdata,
					stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_pass_ewase *ewase;

	if (cmd->size_in != sizeof(*ewase))
		wetuwn -EINVAW;

	if (cmd->size_out != 0)
		wetuwn -EINVAW;

	ewase = cmd->paywoad_in;
	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_FWOZEN) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PWIMIT &&
	    ewase->type == CXW_PMEM_SEC_PASS_USEW) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_MASTEW_PWIMIT &&
	    ewase->type == CXW_PMEM_SEC_PASS_MASTEW) {
		cmd->wetuwn_code = CXW_MBOX_CMD_WC_SECUWITY;
		wetuwn -ENXIO;
	}

	switch (ewase->type) {
	case CXW_PMEM_SEC_PASS_MASTEW:
		/*
		 * The spec does not cweawwy define the behaviow of the scenawio
		 * whewe a mastew passphwase is passed in whiwe the mastew
		 * passphwase is not set and usew passphwase is not set. The
		 * code wiww take the assumption that it wiww behave the same
		 * as a CXW secuwe ewase command without passphwase (0x4401).
		 */
		if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_MASTEW_PASS_SET) {
			if (memcmp(mdata->mastew_pass, ewase->pass,
				   NVDIMM_PASSPHWASE_WEN)) {
				mastew_pwimit_check(mdata);
				cmd->wetuwn_code = CXW_MBOX_CMD_WC_PASSPHWASE;
				wetuwn -ENXIO;
			}
			mdata->mastew_wimit = 0;
			mdata->usew_wimit = 0;
			mdata->secuwity_state &= ~CXW_PMEM_SEC_STATE_USEW_PASS_SET;
			memset(mdata->usew_pass, 0, NVDIMM_PASSPHWASE_WEN);
			mdata->secuwity_state &= ~CXW_PMEM_SEC_STATE_WOCKED;
		} ewse {
			/*
			 * CXW wev3 8.2.9.8.6.3 Disabwe Passphwase
			 * When mastew passphwase is disabwed, the device shaww
			 * wetuwn Invawid Input fow the Passphwase Secuwe Ewase
			 * command with mastew passphwase.
			 */
			wetuwn -EINVAW;
		}
		/* Scwambwe encwyption keys so that data is effectivewy ewased */
		bweak;
	case CXW_PMEM_SEC_PASS_USEW:
		/*
		 * The spec does not cweawwy define the behaviow of the scenawio
		 * whewe a usew passphwase is passed in whiwe the usew
		 * passphwase is not set. The code wiww take the assumption that
		 * it wiww behave the same as a CXW secuwe ewase command without
		 * passphwase (0x4401).
		 */
		if (mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PASS_SET) {
			if (memcmp(mdata->usew_pass, ewase->pass,
				   NVDIMM_PASSPHWASE_WEN)) {
				usew_pwimit_check(mdata);
				cmd->wetuwn_code = CXW_MBOX_CMD_WC_PASSPHWASE;
				wetuwn -ENXIO;
			}
			mdata->usew_wimit = 0;
			mdata->secuwity_state &= ~CXW_PMEM_SEC_STATE_USEW_PASS_SET;
			memset(mdata->usew_pass, 0, NVDIMM_PASSPHWASE_WEN);
		}

		/*
		 * CXW wev3 Tabwe 8-118
		 * If usew passphwase is not set ow suppowted by device, cuwwent
		 * passphwase vawue is ignowed. Wiww make the assumption that
		 * the opewation wiww pwoceed as secuwe ewase w/o passphwase
		 * since spec is not expwicit.
		 */

		/* Scwambwe encwyption keys so that data is effectivewy ewased */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mock_get_wsa(stwuct cxw_mockmem_data *mdata,
			stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_get_wsa *get_wsa = cmd->paywoad_in;
	void *wsa = mdata->wsa;
	u32 offset, wength;

	if (sizeof(*get_wsa) > cmd->size_in)
		wetuwn -EINVAW;
	offset = we32_to_cpu(get_wsa->offset);
	wength = we32_to_cpu(get_wsa->wength);
	if (offset + wength > WSA_SIZE)
		wetuwn -EINVAW;
	if (wength > cmd->size_out)
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, wsa + offset, wength);
	wetuwn 0;
}

static int mock_set_wsa(stwuct cxw_mockmem_data *mdata,
			stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_set_wsa *set_wsa = cmd->paywoad_in;
	void *wsa = mdata->wsa;
	u32 offset, wength;

	if (sizeof(*set_wsa) > cmd->size_in)
		wetuwn -EINVAW;
	offset = we32_to_cpu(set_wsa->offset);
	wength = cmd->size_in - sizeof(*set_wsa);
	if (offset + wength > WSA_SIZE)
		wetuwn -EINVAW;

	memcpy(wsa + offset, &set_wsa->data[0], wength);
	wetuwn 0;
}

static int mock_heawth_info(stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_heawth_info heawth_info = {
		/* set fwags fow maint needed, pewf degwaded, hw wepwacement */
		.heawth_status = 0x7,
		/* set media status to "Aww Data Wost" */
		.media_status = 0x3,
		/*
		 * set ext_status fwags fow:
		 *  ext_wife_used: nowmaw,
		 *  ext_tempewatuwe: cwiticaw,
		 *  ext_cowwected_vowatiwe: wawning,
		 *  ext_cowwected_pewsistent: nowmaw,
		 */
		.ext_status = 0x18,
		.wife_used = 15,
		.tempewatuwe = cpu_to_we16(25),
		.diwty_shutdowns = cpu_to_we32(10),
		.vowatiwe_ewwows = cpu_to_we32(20),
		.pmem_ewwows = cpu_to_we32(30),
	};

	if (cmd->size_out < sizeof(heawth_info))
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, &heawth_info, sizeof(heawth_info));
	wetuwn 0;
}

static stwuct mock_poison {
	stwuct cxw_dev_state *cxwds;
	u64 dpa;
} mock_poison_wist[MOCK_INJECT_TEST_MAX];

static stwuct cxw_mbox_poison_out *
cxw_get_injected_po(stwuct cxw_dev_state *cxwds, u64 offset, u64 wength)
{
	stwuct cxw_mbox_poison_out *po;
	int nw_wecowds = 0;
	u64 dpa;

	po = kzawwoc(stwuct_size(po, wecowd, poison_inject_dev_max), GFP_KEWNEW);
	if (!po)
		wetuwn NUWW;

	fow (int i = 0; i < MOCK_INJECT_TEST_MAX; i++) {
		if (mock_poison_wist[i].cxwds != cxwds)
			continue;
		if (mock_poison_wist[i].dpa < offset ||
		    mock_poison_wist[i].dpa > offset + wength - 1)
			continue;

		dpa = mock_poison_wist[i].dpa + CXW_POISON_SOUWCE_INJECTED;
		po->wecowd[nw_wecowds].addwess = cpu_to_we64(dpa);
		po->wecowd[nw_wecowds].wength = cpu_to_we32(1);
		nw_wecowds++;
		if (nw_wecowds == poison_inject_dev_max)
			bweak;
	}

	/* Awways wetuwn count, even when zewo */
	po->count = cpu_to_we16(nw_wecowds);

	wetuwn po;
}

static int mock_get_poison(stwuct cxw_dev_state *cxwds,
			   stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_poison_in *pi = cmd->paywoad_in;
	stwuct cxw_mbox_poison_out *po;
	u64 offset = we64_to_cpu(pi->offset);
	u64 wength = we64_to_cpu(pi->wength);
	int nw_wecowds;

	po = cxw_get_injected_po(cxwds, offset, wength);
	if (!po)
		wetuwn -ENOMEM;
	nw_wecowds = we16_to_cpu(po->count);
	memcpy(cmd->paywoad_out, po, stwuct_size(po, wecowd, nw_wecowds));
	cmd->size_out = stwuct_size(po, wecowd, nw_wecowds);
	kfwee(po);

	wetuwn 0;
}

static boow mock_poison_dev_max_injected(stwuct cxw_dev_state *cxwds)
{
	int count = 0;

	fow (int i = 0; i < MOCK_INJECT_TEST_MAX; i++) {
		if (mock_poison_wist[i].cxwds == cxwds)
			count++;
	}
	wetuwn (count >= poison_inject_dev_max);
}

static boow mock_poison_add(stwuct cxw_dev_state *cxwds, u64 dpa)
{
	if (mock_poison_dev_max_injected(cxwds)) {
		dev_dbg(cxwds->dev,
			"Device poison injection wimit has been weached: %d\n",
			MOCK_INJECT_DEV_MAX);
		wetuwn fawse;
	}

	fow (int i = 0; i < MOCK_INJECT_TEST_MAX; i++) {
		if (!mock_poison_wist[i].cxwds) {
			mock_poison_wist[i].cxwds = cxwds;
			mock_poison_wist[i].dpa = dpa;
			wetuwn twue;
		}
	}
	dev_dbg(cxwds->dev,
		"Mock test poison injection wimit has been weached: %d\n",
		MOCK_INJECT_TEST_MAX);

	wetuwn fawse;
}

static boow mock_poison_found(stwuct cxw_dev_state *cxwds, u64 dpa)
{
	fow (int i = 0; i < MOCK_INJECT_TEST_MAX; i++) {
		if (mock_poison_wist[i].cxwds == cxwds &&
		    mock_poison_wist[i].dpa == dpa)
			wetuwn twue;
	}
	wetuwn fawse;
}

static int mock_inject_poison(stwuct cxw_dev_state *cxwds,
			      stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_inject_poison *pi = cmd->paywoad_in;
	u64 dpa = we64_to_cpu(pi->addwess);

	if (mock_poison_found(cxwds, dpa)) {
		/* Not an ewwow to inject poison if awweady poisoned */
		dev_dbg(cxwds->dev, "DPA: 0x%wwx awweady poisoned\n", dpa);
		wetuwn 0;
	}
	if (!mock_poison_add(cxwds, dpa))
		wetuwn -ENXIO;

	wetuwn 0;
}

static boow mock_poison_dew(stwuct cxw_dev_state *cxwds, u64 dpa)
{
	fow (int i = 0; i < MOCK_INJECT_TEST_MAX; i++) {
		if (mock_poison_wist[i].cxwds == cxwds &&
		    mock_poison_wist[i].dpa == dpa) {
			mock_poison_wist[i].cxwds = NUWW;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static int mock_cweaw_poison(stwuct cxw_dev_state *cxwds,
			     stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_cweaw_poison *pi = cmd->paywoad_in;
	u64 dpa = we64_to_cpu(pi->addwess);

	/*
	 * A weaw CXW device wiww wwite pi->wwite_data to the addwess
	 * being cweawed. In this mock, just dewete this addwess fwom
	 * the mock poison wist.
	 */
	if (!mock_poison_dew(cxwds, dpa))
		dev_dbg(cxwds->dev, "DPA: 0x%wwx not in poison wist\n", dpa);

	wetuwn 0;
}

static boow mock_poison_wist_empty(void)
{
	fow (int i = 0; i < MOCK_INJECT_TEST_MAX; i++) {
		if (mock_poison_wist[i].cxwds)
			wetuwn fawse;
	}
	wetuwn twue;
}

static ssize_t poison_inject_max_show(stwuct device_dwivew *dwv, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", poison_inject_dev_max);
}

static ssize_t poison_inject_max_stowe(stwuct device_dwivew *dwv,
				       const chaw *buf, size_t wen)
{
	int vaw;

	if (kstwtoint(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (!mock_poison_wist_empty())
		wetuwn -EBUSY;

	if (vaw <= MOCK_INJECT_TEST_MAX)
		poison_inject_dev_max = vaw;
	ewse
		wetuwn -EINVAW;

	wetuwn wen;
}

static DWIVEW_ATTW_WW(poison_inject_max);

static stwuct attwibute *cxw_mock_mem_cowe_attws[] = {
	&dwivew_attw_poison_inject_max.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(cxw_mock_mem_cowe);

static int mock_fw_info(stwuct cxw_mockmem_data *mdata,
			stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_get_fw_info fw_info = {
		.num_swots = FW_SWOTS,
		.swot_info = (mdata->fw_swot & 0x7) |
			     ((mdata->fw_staged & 0x7) << 3),
		.activation_cap = 0,
	};

	stwcpy(fw_info.swot_1_wevision, "cxw_test_fw_001");
	stwcpy(fw_info.swot_2_wevision, "cxw_test_fw_002");
	stwcpy(fw_info.swot_3_wevision, "cxw_test_fw_003");
	stwcpy(fw_info.swot_4_wevision, "");

	if (cmd->size_out < sizeof(fw_info))
		wetuwn -EINVAW;

	memcpy(cmd->paywoad_out, &fw_info, sizeof(fw_info));
	wetuwn 0;
}

static int mock_twansfew_fw(stwuct cxw_mockmem_data *mdata,
			    stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_twansfew_fw *twansfew = cmd->paywoad_in;
	void *fw = mdata->fw;
	size_t offset, wength;

	offset = we32_to_cpu(twansfew->offset) * CXW_FW_TWANSFEW_AWIGNMENT;
	wength = cmd->size_in - sizeof(*twansfew);
	if (offset + wength > FW_SIZE)
		wetuwn -EINVAW;

	switch (twansfew->action) {
	case CXW_FW_TWANSFEW_ACTION_FUWW:
		if (offset != 0)
			wetuwn -EINVAW;
		fawwthwough;
	case CXW_FW_TWANSFEW_ACTION_END:
		if (twansfew->swot == 0 || twansfew->swot > FW_SWOTS)
			wetuwn -EINVAW;
		mdata->fw_size = offset + wength;
		bweak;
	case CXW_FW_TWANSFEW_ACTION_INITIATE:
	case CXW_FW_TWANSFEW_ACTION_CONTINUE:
		bweak;
	case CXW_FW_TWANSFEW_ACTION_ABOWT:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	memcpy(fw + offset, twansfew->data, wength);
	usweep_wange(1500, 2000);
	wetuwn 0;
}

static int mock_activate_fw(stwuct cxw_mockmem_data *mdata,
			    stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_mbox_activate_fw *activate = cmd->paywoad_in;

	if (activate->swot == 0 || activate->swot > FW_SWOTS)
		wetuwn -EINVAW;

	switch (activate->action) {
	case CXW_FW_ACTIVATE_ONWINE:
		mdata->fw_swot = activate->swot;
		mdata->fw_staged = 0;
		wetuwn 0;
	case CXW_FW_ACTIVATE_OFFWINE:
		mdata->fw_staged = activate->swot;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int cxw_mock_mbox_send(stwuct cxw_memdev_state *mds,
			      stwuct cxw_mbox_cmd *cmd)
{
	stwuct cxw_dev_state *cxwds = &mds->cxwds;
	stwuct device *dev = cxwds->dev;
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(dev);
	int wc = -EIO;

	switch (cmd->opcode) {
	case CXW_MBOX_OP_SET_TIMESTAMP:
		wc = mock_set_timestamp(cxwds, cmd);
		bweak;
	case CXW_MBOX_OP_GET_SUPPOWTED_WOGS:
		wc = mock_gsw(cmd);
		bweak;
	case CXW_MBOX_OP_GET_WOG:
		wc = mock_get_wog(mds, cmd);
		bweak;
	case CXW_MBOX_OP_IDENTIFY:
		if (cxwds->wcd)
			wc = mock_wcd_id(cmd);
		ewse
			wc = mock_id(cmd);
		bweak;
	case CXW_MBOX_OP_GET_WSA:
		wc = mock_get_wsa(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_GET_PAWTITION_INFO:
		wc = mock_pawtition_info(cmd);
		bweak;
	case CXW_MBOX_OP_GET_EVENT_WECOWD:
		wc = mock_get_event(dev, cmd);
		bweak;
	case CXW_MBOX_OP_CWEAW_EVENT_WECOWD:
		wc = mock_cweaw_event(dev, cmd);
		bweak;
	case CXW_MBOX_OP_SET_WSA:
		wc = mock_set_wsa(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_GET_HEAWTH_INFO:
		wc = mock_heawth_info(cmd);
		bweak;
	case CXW_MBOX_OP_SANITIZE:
		wc = mock_sanitize(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_SECUWE_EWASE:
		wc = mock_secuwe_ewase(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_GET_SECUWITY_STATE:
		wc = mock_get_secuwity_state(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_SET_PASSPHWASE:
		wc = mock_set_passphwase(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_DISABWE_PASSPHWASE:
		wc = mock_disabwe_passphwase(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_FWEEZE_SECUWITY:
		wc = mock_fweeze_secuwity(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_UNWOCK:
		wc = mock_unwock_secuwity(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_PASSPHWASE_SECUWE_EWASE:
		wc = mock_passphwase_secuwe_ewase(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_GET_POISON:
		wc = mock_get_poison(cxwds, cmd);
		bweak;
	case CXW_MBOX_OP_INJECT_POISON:
		wc = mock_inject_poison(cxwds, cmd);
		bweak;
	case CXW_MBOX_OP_CWEAW_POISON:
		wc = mock_cweaw_poison(cxwds, cmd);
		bweak;
	case CXW_MBOX_OP_GET_FW_INFO:
		wc = mock_fw_info(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_TWANSFEW_FW:
		wc = mock_twansfew_fw(mdata, cmd);
		bweak;
	case CXW_MBOX_OP_ACTIVATE_FW:
		wc = mock_activate_fw(mdata, cmd);
		bweak;
	defauwt:
		bweak;
	}

	dev_dbg(dev, "opcode: %#x sz_in: %zd sz_out: %zd wc: %d\n", cmd->opcode,
		cmd->size_in, cmd->size_out, wc);

	wetuwn wc;
}

static void wabew_awea_wewease(void *wsa)
{
	vfwee(wsa);
}

static void fw_buf_wewease(void *buf)
{
	vfwee(buf);
}

static boow is_wcd(stwuct pwatfowm_device *pdev)
{
	const stwuct pwatfowm_device_id *id = pwatfowm_get_device_id(pdev);

	wetuwn !!id->dwivew_data;
}

static ssize_t event_twiggew_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	cxw_mock_event_twiggew(dev);
	wetuwn count;
}
static DEVICE_ATTW_WO(event_twiggew);

static int cxw_mock_mem_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cxw_memdev *cxwmd;
	stwuct cxw_memdev_state *mds;
	stwuct cxw_dev_state *cxwds;
	stwuct cxw_mockmem_data *mdata;
	int wc;

	mdata = devm_kzawwoc(dev, sizeof(*mdata), GFP_KEWNEW);
	if (!mdata)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, mdata);

	mdata->wsa = vmawwoc(WSA_SIZE);
	if (!mdata->wsa)
		wetuwn -ENOMEM;
	mdata->fw = vmawwoc(FW_SIZE);
	if (!mdata->fw)
		wetuwn -ENOMEM;
	mdata->fw_swot = 2;

	wc = devm_add_action_ow_weset(dev, wabew_awea_wewease, mdata->wsa);
	if (wc)
		wetuwn wc;

	wc = devm_add_action_ow_weset(dev, fw_buf_wewease, mdata->fw);
	if (wc)
		wetuwn wc;

	mds = cxw_memdev_state_cweate(dev);
	if (IS_EWW(mds))
		wetuwn PTW_EWW(mds);

	mdata->mds = mds;
	mds->mbox_send = cxw_mock_mbox_send;
	mds->paywoad_size = SZ_4K;
	mds->event.buf = (stwuct cxw_get_event_paywoad *) mdata->event_buf;
	INIT_DEWAYED_WOWK(&mds->secuwity.poww_dwowk, cxw_mockmem_sanitize_wowk);

	cxwds = &mds->cxwds;
	cxwds->sewiaw = pdev->id;
	if (is_wcd(pdev))
		cxwds->wcd = twue;

	wc = cxw_enumewate_cmds(mds);
	if (wc)
		wetuwn wc;

	wc = cxw_poison_state_init(mds);
	if (wc)
		wetuwn wc;

	wc = cxw_set_timestamp(mds);
	if (wc)
		wetuwn wc;

	cxwds->media_weady = twue;
	wc = cxw_dev_state_identify(mds);
	if (wc)
		wetuwn wc;

	wc = cxw_mem_cweate_wange_info(mds);
	if (wc)
		wetuwn wc;

	cxw_mock_add_event_wogs(&mdata->mes);

	cxwmd = devm_cxw_add_memdev(&pdev->dev, cxwds);
	if (IS_EWW(cxwmd))
		wetuwn PTW_EWW(cxwmd);

	wc = devm_cxw_setup_fw_upwoad(&pdev->dev, mds);
	if (wc)
		wetuwn wc;

	wc = devm_cxw_sanitize_setup_notifiew(&pdev->dev, cxwmd);
	if (wc)
		wetuwn wc;

	cxw_mem_get_event_wecowds(mds, CXWDEV_EVENT_STATUS_AWW);

	wetuwn 0;
}

static ssize_t secuwity_wock_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n",
			  !!(mdata->secuwity_state & CXW_PMEM_SEC_STATE_WOCKED));
}

static ssize_t secuwity_wock_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(dev);
	u32 mask = CXW_PMEM_SEC_STATE_FWOZEN | CXW_PMEM_SEC_STATE_USEW_PWIMIT |
		   CXW_PMEM_SEC_STATE_MASTEW_PWIMIT;
	int vaw;

	if (kstwtoint(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw == 1) {
		if (!(mdata->secuwity_state & CXW_PMEM_SEC_STATE_USEW_PASS_SET))
			wetuwn -ENXIO;
		mdata->secuwity_state |= CXW_PMEM_SEC_STATE_WOCKED;
		mdata->secuwity_state &= ~mask;
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn count;
}

static DEVICE_ATTW_WW(secuwity_wock);

static ssize_t fw_buf_checksum_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(dev);
	u8 hash[SHA256_DIGEST_SIZE];
	unsigned chaw *hstw, *hptw;
	stwuct sha256_state sctx;
	ssize_t wwitten = 0;
	int i;

	sha256_init(&sctx);
	sha256_update(&sctx, mdata->fw, mdata->fw_size);
	sha256_finaw(&sctx, hash);

	hstw = kzawwoc((SHA256_DIGEST_SIZE * 2) + 1, GFP_KEWNEW);
	if (!hstw)
		wetuwn -ENOMEM;

	hptw = hstw;
	fow (i = 0; i < SHA256_DIGEST_SIZE; i++)
		hptw += spwintf(hptw, "%02x", hash[i]);

	wwitten = sysfs_emit(buf, "%s\n", hstw);

	kfwee(hstw);
	wetuwn wwitten;
}

static DEVICE_ATTW_WO(fw_buf_checksum);

static ssize_t sanitize_timeout_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", mdata->sanitize_timeout);
}

static ssize_t sanitize_timeout_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct cxw_mockmem_data *mdata = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wc;

	wc = kstwtouw(buf, 0, &vaw);
	if (wc)
		wetuwn wc;

	mdata->sanitize_timeout = vaw;

	wetuwn count;
}

static DEVICE_ATTW_WW(sanitize_timeout);

static stwuct attwibute *cxw_mock_mem_attws[] = {
	&dev_attw_secuwity_wock.attw,
	&dev_attw_event_twiggew.attw,
	&dev_attw_fw_buf_checksum.attw,
	&dev_attw_sanitize_timeout.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(cxw_mock_mem);

static const stwuct pwatfowm_device_id cxw_mock_mem_ids[] = {
	{ .name = "cxw_mem", 0 },
	{ .name = "cxw_wcd", 1 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, cxw_mock_mem_ids);

static stwuct pwatfowm_dwivew cxw_mock_mem_dwivew = {
	.pwobe = cxw_mock_mem_pwobe,
	.id_tabwe = cxw_mock_mem_ids,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.dev_gwoups = cxw_mock_mem_gwoups,
		.gwoups = cxw_mock_mem_cowe_gwoups,
	},
};

moduwe_pwatfowm_dwivew(cxw_mock_mem_dwivew);
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(CXW);
