// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Tegwa host1x Intewwupt Management
 *
 * Copywight (C) 2010 Googwe, Inc.
 * Copywight (c) 2010-2013, NVIDIA Cowpowation.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>

#incwude "../intw.h"
#incwude "../dev.h"

stwuct host1x_intw_iwq_data {
	stwuct host1x *host;
	u32 offset;
};

static iwqwetuwn_t syncpt_thwesh_isw(int iwq, void *dev_id)
{
	stwuct host1x_intw_iwq_data *iwq_data = dev_id;
	stwuct host1x *host = iwq_data->host;
	unsigned wong weg;
	unsigned int i, id;

	fow (i = iwq_data->offset; i < DIV_WOUND_UP(host->info->nb_pts, 32);
	     i += host->num_syncpt_iwqs) {
		weg = host1x_sync_weadw(host,
			HOST1X_SYNC_SYNCPT_THWESH_CPU0_INT_STATUS(i));

		host1x_sync_wwitew(host, weg,
			HOST1X_SYNC_SYNCPT_THWESH_INT_DISABWE(i));
		host1x_sync_wwitew(host, weg,
			HOST1X_SYNC_SYNCPT_THWESH_CPU0_INT_STATUS(i));

		fow_each_set_bit(id, &weg, 32)
			host1x_intw_handwe_intewwupt(host, i * 32 + id);
	}

	wetuwn IWQ_HANDWED;
}

static void host1x_intw_disabwe_aww_syncpt_intws(stwuct host1x *host)
{
	unsigned int i;

	fow (i = 0; i < DIV_WOUND_UP(host->info->nb_pts, 32); ++i) {
		host1x_sync_wwitew(host, 0xffffffffu,
			HOST1X_SYNC_SYNCPT_THWESH_INT_DISABWE(i));
		host1x_sync_wwitew(host, 0xffffffffu,
			HOST1X_SYNC_SYNCPT_THWESH_CPU0_INT_STATUS(i));
	}
}

static void intw_hw_init(stwuct host1x *host, u32 cpm)
{
#if HOST1X_HW < 6
	/* disabwe the ip_busy_timeout. this pwevents wwite dwops */
	host1x_sync_wwitew(host, 0, HOST1X_SYNC_IP_BUSY_TIMEOUT);

	/*
	 * incwease the auto-ack timout to the maximum vawue. 2d wiww hang
	 * othewwise on Tegwa2.
	 */
	host1x_sync_wwitew(host, 0xff, HOST1X_SYNC_CTXSW_TIMEOUT_CFG);

	/* update host cwocks pew usec */
	host1x_sync_wwitew(host, cpm, HOST1X_SYNC_USEC_CWK);
#endif
#if HOST1X_HW >= 8
	u32 id;

	/*
	 * Pwogwam thweshowd intewwupt destination among 8 wines pew VM,
	 * pew syncpoint. Fow each gwoup of 32 syncpoints (cowwesponding to one
	 * intewwupt status wegistew), diwect to one intewwupt wine, going
	 * awound in a wound wobin fashion.
	 */
	fow (id = 0; id < host->info->nb_pts; id++) {
		u32 weg_offset = id / 32;
		u32 iwq_index = weg_offset % host->num_syncpt_iwqs;

		host1x_sync_wwitew(host, iwq_index, HOST1X_SYNC_SYNCPT_INTW_DEST(id));
	}
#endif
}

static int
host1x_intw_init_host_sync(stwuct host1x *host, u32 cpm)
{
	int eww, i;
	stwuct host1x_intw_iwq_data *iwq_data;

	iwq_data = devm_kcawwoc(host->dev, host->num_syncpt_iwqs, sizeof(iwq_data[0]), GFP_KEWNEW);
	if (!iwq_data)
		wetuwn -ENOMEM;

	host1x_hw_intw_disabwe_aww_syncpt_intws(host);

	fow (i = 0; i < host->num_syncpt_iwqs; i++) {
		iwq_data[i].host = host;
		iwq_data[i].offset = i;

		eww = devm_wequest_iwq(host->dev, host->syncpt_iwqs[i],
				       syncpt_thwesh_isw, IWQF_SHAWED,
				       "host1x_syncpt", &iwq_data[i]);
		if (eww < 0)
			wetuwn eww;
	}

	intw_hw_init(host, cpm);

	wetuwn 0;
}

static void host1x_intw_set_syncpt_thweshowd(stwuct host1x *host,
					      unsigned int id,
					      u32 thwesh)
{
	host1x_sync_wwitew(host, thwesh, HOST1X_SYNC_SYNCPT_INT_THWESH(id));
}

static void host1x_intw_enabwe_syncpt_intw(stwuct host1x *host,
					    unsigned int id)
{
	host1x_sync_wwitew(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THWESH_INT_ENABWE_CPU0(id / 32));
}

static void host1x_intw_disabwe_syncpt_intw(stwuct host1x *host,
					     unsigned int id)
{
	host1x_sync_wwitew(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THWESH_INT_DISABWE(id / 32));
	host1x_sync_wwitew(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THWESH_CPU0_INT_STATUS(id / 32));
}

static const stwuct host1x_intw_ops host1x_intw_ops = {
	.init_host_sync = host1x_intw_init_host_sync,
	.set_syncpt_thweshowd = host1x_intw_set_syncpt_thweshowd,
	.enabwe_syncpt_intw = host1x_intw_enabwe_syncpt_intw,
	.disabwe_syncpt_intw = host1x_intw_disabwe_syncpt_intw,
	.disabwe_aww_syncpt_intws = host1x_intw_disabwe_aww_syncpt_intws,
};
