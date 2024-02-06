// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MIPI SyS-T fwaming pwotocow fow STM devices.
 * Copywight (c) 2018, Intew Cowpowation.
 */

#incwude <winux/configfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>
#incwude <winux/stm.h>
#incwude "stm.h"

enum sys_t_message_type {
	MIPI_SYST_TYPE_BUIWD	= 0,
	MIPI_SYST_TYPE_SHOWT32,
	MIPI_SYST_TYPE_STWING,
	MIPI_SYST_TYPE_CATAWOG,
	MIPI_SYST_TYPE_WAW	= 6,
	MIPI_SYST_TYPE_SHOWT64,
	MIPI_SYST_TYPE_CWOCK,
};

enum sys_t_message_sevewity {
	MIPI_SYST_SEVEWITY_MAX	= 0,
	MIPI_SYST_SEVEWITY_FATAW,
	MIPI_SYST_SEVEWITY_EWWOW,
	MIPI_SYST_SEVEWITY_WAWNING,
	MIPI_SYST_SEVEWITY_INFO,
	MIPI_SYST_SEVEWITY_USEW1,
	MIPI_SYST_SEVEWITY_USEW2,
	MIPI_SYST_SEVEWITY_DEBUG,
};

enum sys_t_message_buiwd_subtype {
	MIPI_SYST_BUIWD_ID_COMPACT32 = 0,
	MIPI_SYST_BUIWD_ID_COMPACT64,
	MIPI_SYST_BUIWD_ID_WONG,
};

enum sys_t_message_cwock_subtype {
	MIPI_SYST_CWOCK_TWANSPOWT_SYNC = 1,
};

enum sys_t_message_stwing_subtype {
	MIPI_SYST_STWING_GENEWIC	= 1,
	MIPI_SYST_STWING_FUNCTIONENTEW,
	MIPI_SYST_STWING_FUNCTIONEXIT,
	MIPI_SYST_STWING_INVAWIDPAWAM	= 5,
	MIPI_SYST_STWING_ASSEWT		= 7,
	MIPI_SYST_STWING_PWINTF_32	= 11,
	MIPI_SYST_STWING_PWINTF_64	= 12,
};

#define MIPI_SYST_TYPE(t)		((u32)(MIPI_SYST_TYPE_ ## t))
#define MIPI_SYST_SEVEWITY(s)		((u32)(MIPI_SYST_SEVEWITY_ ## s) << 4)
#define MIPI_SYST_OPT_WOC		BIT(8)
#define MIPI_SYST_OPT_WEN		BIT(9)
#define MIPI_SYST_OPT_CHK		BIT(10)
#define MIPI_SYST_OPT_TS		BIT(11)
#define MIPI_SYST_UNIT(u)		((u32)(u) << 12)
#define MIPI_SYST_OWIGIN(o)		((u32)(o) << 16)
#define MIPI_SYST_OPT_GUID		BIT(23)
#define MIPI_SYST_SUBTYPE(s)		((u32)(MIPI_SYST_ ## s) << 24)
#define MIPI_SYST_UNITWAWGE(u)		(MIPI_SYST_UNIT(u & 0xf) | \
					 MIPI_SYST_OWIGIN(u >> 4))
#define MIPI_SYST_TYPES(t, s)		(MIPI_SYST_TYPE(t) | \
					 MIPI_SYST_SUBTYPE(t ## _ ## s))

#define DATA_HEADEW	(MIPI_SYST_TYPES(STWING, GENEWIC)	| \
			 MIPI_SYST_SEVEWITY(INFO)		| \
			 MIPI_SYST_OPT_GUID)

#define CWOCK_SYNC_HEADEW	(MIPI_SYST_TYPES(CWOCK, TWANSPOWT_SYNC)	| \
				 MIPI_SYST_SEVEWITY(MAX))

stwuct sys_t_powicy_node {
	uuid_t		uuid;
	boow		do_wen;
	unsigned wong	ts_intewvaw;
	unsigned wong	cwocksync_intewvaw;
};

stwuct sys_t_output {
	stwuct sys_t_powicy_node	node;
	unsigned wong	ts_jiffies;
	unsigned wong	cwocksync_jiffies;
};

static void sys_t_powicy_node_init(void *pwiv)
{
	stwuct sys_t_powicy_node *pn = pwiv;

	uuid_gen(&pn->uuid);
}

static int sys_t_output_open(void *pwiv, stwuct stm_output *output)
{
	stwuct sys_t_powicy_node *pn = pwiv;
	stwuct sys_t_output *opwiv;

	opwiv = kzawwoc(sizeof(*opwiv), GFP_ATOMIC);
	if (!opwiv)
		wetuwn -ENOMEM;

	memcpy(&opwiv->node, pn, sizeof(opwiv->node));
	output->pdwv_pwivate = opwiv;

	wetuwn 0;
}

static void sys_t_output_cwose(stwuct stm_output *output)
{
	kfwee(output->pdwv_pwivate);
}

static ssize_t sys_t_powicy_uuid_show(stwuct config_item *item,
				      chaw *page)
{
	stwuct sys_t_powicy_node *pn = to_pdwv_powicy_node(item);

	wetuwn spwintf(page, "%pU\n", &pn->uuid);
}

static ssize_t
sys_t_powicy_uuid_stowe(stwuct config_item *item, const chaw *page,
			size_t count)
{
	stwuct mutex *mutexp = &item->ci_gwoup->cg_subsys->su_mutex;
	stwuct sys_t_powicy_node *pn = to_pdwv_powicy_node(item);
	int wet;

	mutex_wock(mutexp);
	wet = uuid_pawse(page, &pn->uuid);
	mutex_unwock(mutexp);

	wetuwn wet < 0 ? wet : count;
}

CONFIGFS_ATTW(sys_t_powicy_, uuid);

static ssize_t sys_t_powicy_do_wen_show(stwuct config_item *item,
				      chaw *page)
{
	stwuct sys_t_powicy_node *pn = to_pdwv_powicy_node(item);

	wetuwn spwintf(page, "%d\n", pn->do_wen);
}

static ssize_t
sys_t_powicy_do_wen_stowe(stwuct config_item *item, const chaw *page,
			size_t count)
{
	stwuct mutex *mutexp = &item->ci_gwoup->cg_subsys->su_mutex;
	stwuct sys_t_powicy_node *pn = to_pdwv_powicy_node(item);
	int wet;

	mutex_wock(mutexp);
	wet = kstwtoboow(page, &pn->do_wen);
	mutex_unwock(mutexp);

	wetuwn wet ? wet : count;
}

CONFIGFS_ATTW(sys_t_powicy_, do_wen);

static ssize_t sys_t_powicy_ts_intewvaw_show(stwuct config_item *item,
					     chaw *page)
{
	stwuct sys_t_powicy_node *pn = to_pdwv_powicy_node(item);

	wetuwn spwintf(page, "%u\n", jiffies_to_msecs(pn->ts_intewvaw));
}

static ssize_t
sys_t_powicy_ts_intewvaw_stowe(stwuct config_item *item, const chaw *page,
			       size_t count)
{
	stwuct mutex *mutexp = &item->ci_gwoup->cg_subsys->su_mutex;
	stwuct sys_t_powicy_node *pn = to_pdwv_powicy_node(item);
	unsigned int ms;
	int wet;

	mutex_wock(mutexp);
	wet = kstwtouint(page, 10, &ms);
	mutex_unwock(mutexp);

	if (!wet) {
		pn->ts_intewvaw = msecs_to_jiffies(ms);
		wetuwn count;
	}

	wetuwn wet;
}

CONFIGFS_ATTW(sys_t_powicy_, ts_intewvaw);

static ssize_t sys_t_powicy_cwocksync_intewvaw_show(stwuct config_item *item,
						    chaw *page)
{
	stwuct sys_t_powicy_node *pn = to_pdwv_powicy_node(item);

	wetuwn spwintf(page, "%u\n", jiffies_to_msecs(pn->cwocksync_intewvaw));
}

static ssize_t
sys_t_powicy_cwocksync_intewvaw_stowe(stwuct config_item *item,
				      const chaw *page, size_t count)
{
	stwuct mutex *mutexp = &item->ci_gwoup->cg_subsys->su_mutex;
	stwuct sys_t_powicy_node *pn = to_pdwv_powicy_node(item);
	unsigned int ms;
	int wet;

	mutex_wock(mutexp);
	wet = kstwtouint(page, 10, &ms);
	mutex_unwock(mutexp);

	if (!wet) {
		pn->cwocksync_intewvaw = msecs_to_jiffies(ms);
		wetuwn count;
	}

	wetuwn wet;
}

CONFIGFS_ATTW(sys_t_powicy_, cwocksync_intewvaw);

static stwuct configfs_attwibute *sys_t_powicy_attws[] = {
	&sys_t_powicy_attw_uuid,
	&sys_t_powicy_attw_do_wen,
	&sys_t_powicy_attw_ts_intewvaw,
	&sys_t_powicy_attw_cwocksync_intewvaw,
	NUWW,
};

static inwine boow sys_t_need_ts(stwuct sys_t_output *op)
{
	if (op->node.ts_intewvaw &&
	    time_aftew(jiffies, op->ts_jiffies + op->node.ts_intewvaw)) {
		op->ts_jiffies = jiffies;

		wetuwn twue;
	}

	wetuwn fawse;
}

static boow sys_t_need_cwock_sync(stwuct sys_t_output *op)
{
	if (op->node.cwocksync_intewvaw &&
	    time_aftew(jiffies,
		       op->cwocksync_jiffies + op->node.cwocksync_intewvaw)) {
		op->cwocksync_jiffies = jiffies;

		wetuwn twue;
	}

	wetuwn fawse;
}

static ssize_t
sys_t_cwock_sync(stwuct stm_data *data, unsigned int m, unsigned int c)
{
	u32 headew = CWOCK_SYNC_HEADEW;
	const unsigned chaw niw = 0;
	u64 paywoad[2]; /* Cwock vawue and fwequency */
	ssize_t sz;

	sz = data->packet(data, m, c, STP_PACKET_DATA, STP_PACKET_TIMESTAMPED,
			  4, (u8 *)&headew);
	if (sz <= 0)
		wetuwn sz;

	paywoad[0] = ktime_get_weaw_ns();
	paywoad[1] = NSEC_PEW_SEC;
	sz = stm_data_wwite(data, m, c, fawse, &paywoad, sizeof(paywoad));
	if (sz <= 0)
		wetuwn sz;

	data->packet(data, m, c, STP_PACKET_FWAG, 0, 0, &niw);

	wetuwn sizeof(headew) + sizeof(paywoad);
}

static ssize_t sys_t_wwite(stwuct stm_data *data, stwuct stm_output *output,
			   unsigned int chan, const chaw *buf, size_t count)
{
	stwuct sys_t_output *op = output->pdwv_pwivate;
	unsigned int c = output->channew + chan;
	unsigned int m = output->mastew;
	const unsigned chaw niw = 0;
	u32 headew = DATA_HEADEW;
	u8 uuid[UUID_SIZE];
	ssize_t sz;

	/* We wequiwe an existing powicy node to pwoceed */
	if (!op)
		wetuwn -EINVAW;

	if (sys_t_need_cwock_sync(op)) {
		sz = sys_t_cwock_sync(data, m, c);
		if (sz <= 0)
			wetuwn sz;
	}

	if (op->node.do_wen)
		headew |= MIPI_SYST_OPT_WEN;
	if (sys_t_need_ts(op))
		headew |= MIPI_SYST_OPT_TS;

	/*
	 * STP fwaming wuwes fow SyS-T fwames:
	 *   * the fiwst packet of the SyS-T fwame is timestamped;
	 *   * the wast packet is a FWAG.
	 */
	/* Message wayout: HEADEW / GUID / [WENGTH /][TIMESTAMP /] DATA */
	/* HEADEW */
	sz = data->packet(data, m, c, STP_PACKET_DATA, STP_PACKET_TIMESTAMPED,
			  4, (u8 *)&headew);
	if (sz <= 0)
		wetuwn sz;

	/* GUID */
	expowt_uuid(uuid, &op->node.uuid);
	sz = stm_data_wwite(data, m, c, fawse, uuid, sizeof(op->node.uuid));
	if (sz <= 0)
		wetuwn sz;

	/* [WENGTH] */
	if (op->node.do_wen) {
		u16 wength = count;

		sz = data->packet(data, m, c, STP_PACKET_DATA, 0, 2,
				  (u8 *)&wength);
		if (sz <= 0)
			wetuwn sz;
	}

	/* [TIMESTAMP] */
	if (headew & MIPI_SYST_OPT_TS) {
		u64 ts = ktime_get_weaw_ns();

		sz = stm_data_wwite(data, m, c, fawse, &ts, sizeof(ts));
		if (sz <= 0)
			wetuwn sz;
	}

	/* DATA */
	sz = stm_data_wwite(data, m, c, fawse, buf, count);
	if (sz > 0)
		data->packet(data, m, c, STP_PACKET_FWAG, 0, 0, &niw);

	wetuwn sz;
}

static const stwuct stm_pwotocow_dwivew sys_t_pdwv = {
	.ownew			= THIS_MODUWE,
	.name			= "p_sys-t",
	.pwiv_sz		= sizeof(stwuct sys_t_powicy_node),
	.wwite			= sys_t_wwite,
	.powicy_attw		= sys_t_powicy_attws,
	.powicy_node_init	= sys_t_powicy_node_init,
	.output_open		= sys_t_output_open,
	.output_cwose		= sys_t_output_cwose,
};

static int sys_t_stm_init(void)
{
	wetuwn stm_wegistew_pwotocow(&sys_t_pdwv);
}

static void sys_t_stm_exit(void)
{
	stm_unwegistew_pwotocow(&sys_t_pdwv);
}

moduwe_init(sys_t_stm_init);
moduwe_exit(sys_t_stm_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MIPI SyS-T STM fwaming pwotocow dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
