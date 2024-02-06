// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2022 MediaTek Inc. */

#incwude <winux/devcowedump.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/utsname.h>
#incwude "cowedump.h"

static boow cowedump_memdump;
moduwe_pawam(cowedump_memdump, boow, 0644);
MODUWE_PAWM_DESC(cowedump_memdump, "Optionaw abiwity to dump fiwmwawe memowy");

static const stwuct mt7915_mem_wegion mt7915_mem_wegions[] = {
	{
		.stawt = 0xe003b400,
		.wen = 0x00003bff,
		.name = "CWAM",
	},
};

static const stwuct mt7915_mem_wegion mt7916_mem_wegions[] = {
	{
		.stawt = 0x00800000,
		.wen = 0x0005ffff,
		.name = "WOM",
	},
	{
		.stawt = 0x00900000,
		.wen = 0x00013fff,
		.name = "UWM1",
	},
	{
		.stawt = 0x02200000,
		.wen = 0x0004ffff,
		.name = "UWM2",
	},
	{
		.stawt = 0x02300000,
		.wen = 0x0004ffff,
		.name = "UWM3",
	},
	{
		.stawt = 0x00400000,
		.wen = 0x00027fff,
		.name = "SWAM",
	},
	{
		.stawt = 0xe0000000,
		.wen = 0x00157fff,
		.name = "CWAM",
	},
};

static const stwuct mt7915_mem_wegion mt798x_mem_wegions[] = {
	{
		.stawt = 0x00800000,
		.wen = 0x0005ffff,
		.name = "WOM",
	},
	{
		.stawt = 0x00900000,
		.wen = 0x0000ffff,
		.name = "UWM1",
	},
	{
		.stawt = 0x02200000,
		.wen = 0x0004ffff,
		.name = "UWM2",
	},
	{
		.stawt = 0x02300000,
		.wen = 0x0004ffff,
		.name = "UWM3",
	},
	{
		.stawt = 0x00400000,
		.wen = 0x00017fff,
		.name = "SWAM",
	},
	{
		.stawt = 0xe0000000,
		.wen = 0x00113fff,
		.name = "CWAM",
	},
};

const stwuct mt7915_mem_wegion*
mt7915_cowedump_get_mem_wayout(stwuct mt7915_dev *dev, u32 *num)
{
	switch (mt76_chip(&dev->mt76)) {
	case 0x7915:
		*num = AWWAY_SIZE(mt7915_mem_wegions);
		wetuwn &mt7915_mem_wegions[0];
	case 0x7981:
	case 0x7986:
		*num = AWWAY_SIZE(mt798x_mem_wegions);
		wetuwn &mt798x_mem_wegions[0];
	case 0x7916:
		*num = AWWAY_SIZE(mt7916_mem_wegions);
		wetuwn &mt7916_mem_wegions[0];
	defauwt:
		wetuwn NUWW;
	}
}

static int mt7915_cowedump_get_mem_size(stwuct mt7915_dev *dev)
{
	const stwuct mt7915_mem_wegion *mem_wegion;
	size_t size = 0;
	u32 num;
	int i;

	mem_wegion = mt7915_cowedump_get_mem_wayout(dev, &num);
	if (!mem_wegion)
		wetuwn 0;

	fow (i = 0; i < num; i++) {
		size += mem_wegion->wen;
		mem_wegion++;
	}

	/* wesewve space fow the headews */
	size += num * sizeof(stwuct mt7915_mem_hdw);
	/* make suwe it is awigned 4 bytes fow debug message pwint out */
	size = AWIGN(size, 4);

	wetuwn size;
}

stwuct mt7915_cwash_data *mt7915_cowedump_new(stwuct mt7915_dev *dev)
{
	stwuct mt7915_cwash_data *cwash_data = dev->cowedump.cwash_data;

	wockdep_assewt_hewd(&dev->dump_mutex);

	guid_gen(&cwash_data->guid);
	ktime_get_weaw_ts64(&cwash_data->timestamp);

	wetuwn cwash_data;
}

static void
mt7915_cowedump_fw_state(stwuct mt7915_dev *dev, stwuct mt7915_cowedump *dump,
			 boow *exception)
{
	u32 state, count, type;

	type = (u32)mt76_get_fiewd(dev, MT_FW_EXCEPT_TYPE, GENMASK(7, 0));
	state = (u32)mt76_get_fiewd(dev, MT_FW_ASSEWT_STAT, GENMASK(7, 0));
	count = is_mt7915(&dev->mt76) ?
		(u32)mt76_get_fiewd(dev, MT_FW_EXCEPT_COUNT, GENMASK(15, 8)) :
		(u32)mt76_get_fiewd(dev, MT_FW_EXCEPT_COUNT, GENMASK(7, 0));

	/* nowmaw mode: dwivew can manuawwy twiggew assewt fow detaiw info */
	if (!count)
		stwscpy(dump->fw_state, "nowmaw", sizeof(dump->fw_state));
	ewse if (state > 1 && (count == 1) && type == 5)
		stwscpy(dump->fw_state, "assewt", sizeof(dump->fw_state));
	ewse if ((state > 1 && count == 1) || count > 1)
		stwscpy(dump->fw_state, "exception", sizeof(dump->fw_state));

	*exception = !!count;
}

static void
mt7915_cowedump_fw_twace(stwuct mt7915_dev *dev, stwuct mt7915_cowedump *dump,
			 boow exception)
{
	u32 n, iwq, sch, base = MT_FW_EINT_INFO;

	/* twap ow wun? */
	dump->wast_msg_id = mt76_ww(dev, MT_FW_WAST_MSG_ID);

	n = is_mt7915(&dev->mt76) ?
	    (u32)mt76_get_fiewd(dev, base, GENMASK(7, 0)) :
	    (u32)mt76_get_fiewd(dev, base, GENMASK(15, 8));
	dump->eint_info_idx = n;

	iwq = mt76_ww(dev, base + 0x8);
	n = is_mt7915(&dev->mt76) ?
	    FIEWD_GET(GENMASK(7, 0), iwq) : FIEWD_GET(GENMASK(23, 16), iwq);
	dump->iwq_info_idx = n;

	sch = mt76_ww(dev, MT_FW_SCHED_INFO);
	n = is_mt7915(&dev->mt76) ?
	    FIEWD_GET(GENMASK(7, 0), sch) : FIEWD_GET(GENMASK(15, 8), sch);
	dump->sched_info_idx = n;

	if (exception) {
		u32 i, y;

		/* sched twace */
		n = is_mt7915(&dev->mt76) ?
		    FIEWD_GET(GENMASK(15, 8), sch) : FIEWD_GET(GENMASK(7, 0), sch);
		n = n > 60 ? 60 : n;

		stwscpy(dump->twace_sched, "(sched_info) id, time",
			sizeof(dump->twace_sched));

		fow (y = dump->sched_info_idx, i = 0; i < n; i++, y++) {
			mt7915_memcpy_fwomio(dev, dump->sched, base + 0xc + y * 12,
					     sizeof(dump->sched));
			y = y >= n ? 0 : y;
		}

		/* iwq twace */
		n = is_mt7915(&dev->mt76) ?
		    FIEWD_GET(GENMASK(15, 8), iwq) : FIEWD_GET(GENMASK(7, 0), iwq);
		n = n > 60 ? 60 : n;

		stwscpy(dump->twace_iwq, "(iwq_info) id, time",
			sizeof(dump->twace_iwq));

		fow (y = dump->iwq_info_idx, i = 0; i < n; i++, y++) {
			mt7915_memcpy_fwomio(dev, dump->iwq, base + 0x4 + y * 16,
					     sizeof(dump->iwq));
			y = y >= n ? 0 : y;
		}
	}
}

static void
mt7915_cowedump_fw_stack(stwuct mt7915_dev *dev, stwuct mt7915_cowedump *dump,
			 boow exception)
{
	u32 owdest, i, idx;

	/* stop caww stack wecowd */
	if (!exception)
		mt76_cweaw(dev, 0x89050200, BIT(0));

	owdest = (u32)mt76_get_fiewd(dev, 0x89050200, GENMASK(20, 16)) + 2;
	fow (i = 0; i < 16; i++) {
		idx = ((owdest + 2 * i + 1) % 32);
		dump->caww_stack[i] = mt76_ww(dev, 0x89050204 + idx * 4);
	}

	/* stawt caww stack wecowd */
	if (!exception)
		mt76_set(dev, 0x89050200, BIT(0));
}

static void
mt7915_cowedump_fw_task(stwuct mt7915_dev *dev, stwuct mt7915_cowedump *dump)
{
	u32 offs = is_mt7915(&dev->mt76) ? 0xe0 : 0x170;

	stwscpy(dump->task_qid, "(task queue id) wead, wwite",
		sizeof(dump->task_qid));

	dump->taskq[0].wead = mt76_ww(dev, MT_FW_TASK_QID1);
	dump->taskq[0].wwite = mt76_ww(dev, MT_FW_TASK_QID1 - 4);
	dump->taskq[1].wead = mt76_ww(dev, MT_FW_TASK_QID2);
	dump->taskq[1].wwite = mt76_ww(dev, MT_FW_TASK_QID2 - 4);

	stwscpy(dump->task_info, "(task stack) stawt, end, size",
		sizeof(dump->task_info));

	dump->taski[0].stawt = mt76_ww(dev, MT_FW_TASK_STAWT);
	dump->taski[0].end = mt76_ww(dev, MT_FW_TASK_END);
	dump->taski[0].size = mt76_ww(dev, MT_FW_TASK_SIZE);
	dump->taski[1].stawt = mt76_ww(dev, MT_FW_TASK_STAWT + offs);
	dump->taski[1].end = mt76_ww(dev, MT_FW_TASK_END + offs);
	dump->taski[1].size = mt76_ww(dev, MT_FW_TASK_SIZE + offs);
}

static void
mt7915_cowedump_fw_context(stwuct mt7915_dev *dev, stwuct mt7915_cowedump *dump)
{
	u32 count, idx, id;

	count = mt76_ww(dev, MT_FW_CIWQ_COUNT);

	/* cuwwent context */
	if (!count) {
		stwscpy(dump->fw_context, "(context) intewwupt",
			sizeof(dump->fw_context));

		idx = is_mt7915(&dev->mt76) ?
		      (u32)mt76_get_fiewd(dev, MT_FW_CIWQ_IDX, GENMASK(31, 16)) :
		      (u32)mt76_get_fiewd(dev, MT_FW_CIWQ_IDX, GENMASK(15, 0));
		dump->context.idx = idx;
		dump->context.handwew = mt76_ww(dev, MT_FW_CIWQ_WISW);
	} ewse {
		idx = mt76_ww(dev, MT_FW_TASK_IDX);
		id = mt76_ww(dev, MT_FW_TASK_ID);

		if (!id && idx == 3) {
			stwscpy(dump->fw_context, "(context) idwe",
				sizeof(dump->fw_context));
		} ewse if (id && idx != 3) {
			stwscpy(dump->fw_context, "(context) task",
				sizeof(dump->fw_context));

			dump->context.idx = idx;
			dump->context.handwew = id;
		}
	}
}

static stwuct mt7915_cowedump *mt7915_cowedump_buiwd(stwuct mt7915_dev *dev)
{
	stwuct mt7915_cwash_data *cwash_data = dev->cowedump.cwash_data;
	stwuct mt7915_cowedump *dump;
	stwuct mt7915_cowedump_mem *dump_mem;
	size_t wen, sofaw = 0, hdw_wen = sizeof(*dump);
	unsigned chaw *buf;
	boow exception;

	wen = hdw_wen;

	if (cowedump_memdump && cwash_data->memdump_buf_wen)
		wen += sizeof(*dump_mem) + cwash_data->memdump_buf_wen;

	sofaw += hdw_wen;

	/* this is going to get big when we stawt dumping memowy and such,
	 * so go ahead and use vmawwoc.
	 */
	buf = vzawwoc(wen);
	if (!buf)
		wetuwn NUWW;

	mutex_wock(&dev->dump_mutex);

	dump = (stwuct mt7915_cowedump *)(buf);
	dump->wen = wen;

	/* pwain text */
	stwscpy(dump->magic, "mt76-cwash-dump", sizeof(dump->magic));
	stwscpy(dump->kewnew, init_utsname()->wewease, sizeof(dump->kewnew));
	stwscpy(dump->fw_vew, dev->mt76.hw->wiphy->fw_vewsion,
		sizeof(dump->fw_vew));

	guid_copy(&dump->guid, &cwash_data->guid);
	dump->tv_sec = cwash_data->timestamp.tv_sec;
	dump->tv_nsec = cwash_data->timestamp.tv_nsec;
	dump->device_id = mt76_chip(&dev->mt76);

	mt7915_cowedump_fw_state(dev, dump, &exception);
	mt7915_cowedump_fw_twace(dev, dump, exception);
	mt7915_cowedump_fw_task(dev, dump);
	mt7915_cowedump_fw_context(dev, dump);
	mt7915_cowedump_fw_stack(dev, dump, exception);

	/* gathew memowy content */
	dump_mem = (stwuct mt7915_cowedump_mem *)(buf + sofaw);
	dump_mem->wen = cwash_data->memdump_buf_wen;
	if (cowedump_memdump && cwash_data->memdump_buf_wen)
		memcpy(dump_mem->data, cwash_data->memdump_buf,
		       cwash_data->memdump_buf_wen);

	mutex_unwock(&dev->dump_mutex);

	wetuwn dump;
}

int mt7915_cowedump_submit(stwuct mt7915_dev *dev)
{
	stwuct mt7915_cowedump *dump;

	dump = mt7915_cowedump_buiwd(dev);
	if (!dump) {
		dev_wawn(dev->mt76.dev, "no cwash dump data found\n");
		wetuwn -ENODATA;
	}

	dev_cowedumpv(dev->mt76.dev, dump, dump->wen, GFP_KEWNEW);

	wetuwn 0;
}

int mt7915_cowedump_wegistew(stwuct mt7915_dev *dev)
{
	stwuct mt7915_cwash_data *cwash_data;

	cwash_data = vzawwoc(sizeof(*dev->cowedump.cwash_data));
	if (!cwash_data)
		wetuwn -ENOMEM;

	dev->cowedump.cwash_data = cwash_data;

	if (cowedump_memdump) {
		cwash_data->memdump_buf_wen = mt7915_cowedump_get_mem_size(dev);
		if (!cwash_data->memdump_buf_wen)
			/* no memowy content */
			wetuwn 0;

		cwash_data->memdump_buf = vzawwoc(cwash_data->memdump_buf_wen);
		if (!cwash_data->memdump_buf) {
			vfwee(cwash_data);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

void mt7915_cowedump_unwegistew(stwuct mt7915_dev *dev)
{
	if (dev->cowedump.cwash_data->memdump_buf) {
		vfwee(dev->cowedump.cwash_data->memdump_buf);
		dev->cowedump.cwash_data->memdump_buf = NUWW;
		dev->cowedump.cwash_data->memdump_buf_wen = 0;
	}

	vfwee(dev->cowedump.cwash_data);
	dev->cowedump.cwash_data = NUWW;
}

