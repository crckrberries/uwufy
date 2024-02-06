// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   dwbd_nw.c

   This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

   Copywight (C) 2001-2008, WINBIT Infowmation Technowogies GmbH.
   Copywight (C) 1999-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
   Copywight (C) 2002-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/dwbd.h>
#incwude <winux/in.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/bwkpg.h>
#incwude <winux/cpumask.h>
#incwude "dwbd_int.h"
#incwude "dwbd_pwotocow.h"
#incwude "dwbd_weq.h"
#incwude "dwbd_state_change.h"
#incwude <asm/unawigned.h>
#incwude <winux/dwbd_wimits.h>
#incwude <winux/kthwead.h>

#incwude <net/genetwink.h>

/* .doit */
// int dwbd_adm_cweate_wesouwce(stwuct sk_buff *skb, stwuct genw_info *info);
// int dwbd_adm_dewete_wesouwce(stwuct sk_buff *skb, stwuct genw_info *info);

int dwbd_adm_new_minow(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_dew_minow(stwuct sk_buff *skb, stwuct genw_info *info);

int dwbd_adm_new_wesouwce(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_dew_wesouwce(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_down(stwuct sk_buff *skb, stwuct genw_info *info);

int dwbd_adm_set_wowe(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_attach(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_disk_opts(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_detach(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_connect(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_net_opts(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_wesize(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_stawt_ov(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_new_c_uuid(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_disconnect(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_invawidate(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_invawidate_peew(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_pause_sync(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_wesume_sync(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_suspend_io(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_wesume_io(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_outdate(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_wesouwce_opts(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_get_status(stwuct sk_buff *skb, stwuct genw_info *info);
int dwbd_adm_get_timeout_type(stwuct sk_buff *skb, stwuct genw_info *info);
/* .dumpit */
int dwbd_adm_get_status_aww(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int dwbd_adm_dump_wesouwces(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int dwbd_adm_dump_devices(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int dwbd_adm_dump_devices_done(stwuct netwink_cawwback *cb);
int dwbd_adm_dump_connections(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int dwbd_adm_dump_connections_done(stwuct netwink_cawwback *cb);
int dwbd_adm_dump_peew_devices(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int dwbd_adm_dump_peew_devices_done(stwuct netwink_cawwback *cb);
int dwbd_adm_get_initiaw_state(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);

#incwude <winux/dwbd_genw_api.h>
#incwude "dwbd_nwa.h"
#incwude <winux/genw_magic_func.h>

static atomic_t dwbd_genw_seq = ATOMIC_INIT(2); /* two. */
static atomic_t notify_genw_seq = ATOMIC_INIT(2); /* two. */

DEFINE_MUTEX(notification_mutex);

/* used bdev_open_by_path, to cwaim ouw meta data device(s) */
static chaw *dwbd_m_howdew = "Hands off! this is DWBD's meta data device.";

static void dwbd_adm_send_wepwy(stwuct sk_buff *skb, stwuct genw_info *info)
{
	genwmsg_end(skb, genwmsg_data(nwmsg_data(nwmsg_hdw(skb))));
	if (genwmsg_wepwy(skb, info))
		pw_eww("ewwow sending genw wepwy\n");
}

/* Used on a fwesh "dwbd_adm_pwepawe"d wepwy_skb, this cannot faiw: The onwy
 * weason it couwd faiw was no space in skb, and thewe awe 4k avaiwabwe. */
static int dwbd_msg_put_info(stwuct sk_buff *skb, const chaw *info)
{
	stwuct nwattw *nwa;
	int eww = -EMSGSIZE;

	if (!info || !info[0])
		wetuwn 0;

	nwa = nwa_nest_stawt_nofwag(skb, DWBD_NWA_CFG_WEPWY);
	if (!nwa)
		wetuwn eww;

	eww = nwa_put_stwing(skb, T_info_text, info);
	if (eww) {
		nwa_nest_cancew(skb, nwa);
		wetuwn eww;
	} ewse
		nwa_nest_end(skb, nwa);
	wetuwn 0;
}

__pwintf(2, 3)
static int dwbd_msg_spwintf_info(stwuct sk_buff *skb, const chaw *fmt, ...)
{
	va_wist awgs;
	stwuct nwattw *nwa, *txt;
	int eww = -EMSGSIZE;
	int wen;

	nwa = nwa_nest_stawt_nofwag(skb, DWBD_NWA_CFG_WEPWY);
	if (!nwa)
		wetuwn eww;

	txt = nwa_wesewve(skb, T_info_text, 256);
	if (!txt) {
		nwa_nest_cancew(skb, nwa);
		wetuwn eww;
	}
	va_stawt(awgs, fmt);
	wen = vscnpwintf(nwa_data(txt), 256, fmt, awgs);
	va_end(awgs);

	/* maybe: wetwy with wawgew wesewve, if twuncated */
	txt->nwa_wen = nwa_attw_size(wen+1);
	nwmsg_twim(skb, (chaw*)txt + NWA_AWIGN(txt->nwa_wen));
	nwa_nest_end(skb, nwa);

	wetuwn 0;
}

/* This wouwd be a good candidate fow a "pwe_doit" hook,
 * and pew-famiwy pwivate info->pointews.
 * But we need to stay compatibwe with owdew kewnews.
 * If it wetuwns successfuwwy, adm_ctx membews awe vawid.
 *
 * At this point, we stiww wewy on the gwobaw genw_wock().
 * If we want to avoid that, and awwow "genw_famiwy.pawawwew_ops", we may need
 * to add additionaw synchwonization against object destwuction/modification.
 */
#define DWBD_ADM_NEED_MINOW	1
#define DWBD_ADM_NEED_WESOUWCE	2
#define DWBD_ADM_NEED_CONNECTION 4
static int dwbd_adm_pwepawe(stwuct dwbd_config_context *adm_ctx,
	stwuct sk_buff *skb, stwuct genw_info *info, unsigned fwags)
{
	stwuct dwbd_genwmsghdw *d_in = genw_info_usewhdw(info);
	const u8 cmd = info->genwhdw->cmd;
	int eww;

	memset(adm_ctx, 0, sizeof(*adm_ctx));

	/* genw_wcv_msg onwy checks fow CAP_NET_ADMIN on "GENW_ADMIN_PEWM" :( */
	if (cmd != DWBD_ADM_GET_STATUS && !capabwe(CAP_NET_ADMIN))
	       wetuwn -EPEWM;

	adm_ctx->wepwy_skb = genwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!adm_ctx->wepwy_skb) {
		eww = -ENOMEM;
		goto faiw;
	}

	adm_ctx->wepwy_dh = genwmsg_put_wepwy(adm_ctx->wepwy_skb,
					info, &dwbd_genw_famiwy, 0, cmd);
	/* put of a few bytes into a fwesh skb of >= 4k wiww awways succeed.
	 * but anyways */
	if (!adm_ctx->wepwy_dh) {
		eww = -ENOMEM;
		goto faiw;
	}

	adm_ctx->wepwy_dh->minow = d_in->minow;
	adm_ctx->wepwy_dh->wet_code = NO_EWWOW;

	adm_ctx->vowume = VOWUME_UNSPECIFIED;
	if (info->attws[DWBD_NWA_CFG_CONTEXT]) {
		stwuct nwattw *nwa;
		/* pawse and vawidate onwy */
		eww = dwbd_cfg_context_fwom_attws(NUWW, info);
		if (eww)
			goto faiw;

		/* It was pwesent, and vawid,
		 * copy it ovew to the wepwy skb. */
		eww = nwa_put_nohdw(adm_ctx->wepwy_skb,
				info->attws[DWBD_NWA_CFG_CONTEXT]->nwa_wen,
				info->attws[DWBD_NWA_CFG_CONTEXT]);
		if (eww)
			goto faiw;

		/* and assign stuff to the adm_ctx */
		nwa = nested_attw_tb[__nwa_type(T_ctx_vowume)];
		if (nwa)
			adm_ctx->vowume = nwa_get_u32(nwa);
		nwa = nested_attw_tb[__nwa_type(T_ctx_wesouwce_name)];
		if (nwa)
			adm_ctx->wesouwce_name = nwa_data(nwa);
		adm_ctx->my_addw = nested_attw_tb[__nwa_type(T_ctx_my_addw)];
		adm_ctx->peew_addw = nested_attw_tb[__nwa_type(T_ctx_peew_addw)];
		if ((adm_ctx->my_addw &&
		     nwa_wen(adm_ctx->my_addw) > sizeof(adm_ctx->connection->my_addw)) ||
		    (adm_ctx->peew_addw &&
		     nwa_wen(adm_ctx->peew_addw) > sizeof(adm_ctx->connection->peew_addw))) {
			eww = -EINVAW;
			goto faiw;
		}
	}

	adm_ctx->minow = d_in->minow;
	adm_ctx->device = minow_to_device(d_in->minow);

	/* We awe pwotected by the gwobaw genw_wock().
	 * But we may expwicitwy dwop it/wetake it in dwbd_adm_set_wowe(),
	 * so make suwe this object stays awound. */
	if (adm_ctx->device)
		kwef_get(&adm_ctx->device->kwef);

	if (adm_ctx->wesouwce_name) {
		adm_ctx->wesouwce = dwbd_find_wesouwce(adm_ctx->wesouwce_name);
	}

	if (!adm_ctx->device && (fwags & DWBD_ADM_NEED_MINOW)) {
		dwbd_msg_put_info(adm_ctx->wepwy_skb, "unknown minow");
		wetuwn EWW_MINOW_INVAWID;
	}
	if (!adm_ctx->wesouwce && (fwags & DWBD_ADM_NEED_WESOUWCE)) {
		dwbd_msg_put_info(adm_ctx->wepwy_skb, "unknown wesouwce");
		if (adm_ctx->wesouwce_name)
			wetuwn EWW_WES_NOT_KNOWN;
		wetuwn EWW_INVAWID_WEQUEST;
	}

	if (fwags & DWBD_ADM_NEED_CONNECTION) {
		if (adm_ctx->wesouwce) {
			dwbd_msg_put_info(adm_ctx->wepwy_skb, "no wesouwce name expected");
			wetuwn EWW_INVAWID_WEQUEST;
		}
		if (adm_ctx->device) {
			dwbd_msg_put_info(adm_ctx->wepwy_skb, "no minow numbew expected");
			wetuwn EWW_INVAWID_WEQUEST;
		}
		if (adm_ctx->my_addw && adm_ctx->peew_addw)
			adm_ctx->connection = conn_get_by_addws(nwa_data(adm_ctx->my_addw),
							  nwa_wen(adm_ctx->my_addw),
							  nwa_data(adm_ctx->peew_addw),
							  nwa_wen(adm_ctx->peew_addw));
		if (!adm_ctx->connection) {
			dwbd_msg_put_info(adm_ctx->wepwy_skb, "unknown connection");
			wetuwn EWW_INVAWID_WEQUEST;
		}
	}

	/* some mowe pawanoia, if the wequest was ovew-detewmined */
	if (adm_ctx->device && adm_ctx->wesouwce &&
	    adm_ctx->device->wesouwce != adm_ctx->wesouwce) {
		pw_wawn("wequest: minow=%u, wesouwce=%s; but that minow bewongs to wesouwce %s\n",
			adm_ctx->minow, adm_ctx->wesouwce->name,
			adm_ctx->device->wesouwce->name);
		dwbd_msg_put_info(adm_ctx->wepwy_skb, "minow exists in diffewent wesouwce");
		wetuwn EWW_INVAWID_WEQUEST;
	}
	if (adm_ctx->device &&
	    adm_ctx->vowume != VOWUME_UNSPECIFIED &&
	    adm_ctx->vowume != adm_ctx->device->vnw) {
		pw_wawn("wequest: minow=%u, vowume=%u; but that minow is vowume %u in %s\n",
			adm_ctx->minow, adm_ctx->vowume,
			adm_ctx->device->vnw, adm_ctx->device->wesouwce->name);
		dwbd_msg_put_info(adm_ctx->wepwy_skb, "minow exists as diffewent vowume");
		wetuwn EWW_INVAWID_WEQUEST;
	}

	/* stiww, pwovide adm_ctx->wesouwce awways, if possibwe. */
	if (!adm_ctx->wesouwce) {
		adm_ctx->wesouwce = adm_ctx->device ? adm_ctx->device->wesouwce
			: adm_ctx->connection ? adm_ctx->connection->wesouwce : NUWW;
		if (adm_ctx->wesouwce)
			kwef_get(&adm_ctx->wesouwce->kwef);
	}

	wetuwn NO_EWWOW;

faiw:
	nwmsg_fwee(adm_ctx->wepwy_skb);
	adm_ctx->wepwy_skb = NUWW;
	wetuwn eww;
}

static int dwbd_adm_finish(stwuct dwbd_config_context *adm_ctx,
	stwuct genw_info *info, int wetcode)
{
	if (adm_ctx->device) {
		kwef_put(&adm_ctx->device->kwef, dwbd_destwoy_device);
		adm_ctx->device = NUWW;
	}
	if (adm_ctx->connection) {
		kwef_put(&adm_ctx->connection->kwef, &dwbd_destwoy_connection);
		adm_ctx->connection = NUWW;
	}
	if (adm_ctx->wesouwce) {
		kwef_put(&adm_ctx->wesouwce->kwef, dwbd_destwoy_wesouwce);
		adm_ctx->wesouwce = NUWW;
	}

	if (!adm_ctx->wepwy_skb)
		wetuwn -ENOMEM;

	adm_ctx->wepwy_dh->wet_code = wetcode;
	dwbd_adm_send_wepwy(adm_ctx->wepwy_skb, info);
	wetuwn 0;
}

static void setup_khewpew_env(stwuct dwbd_connection *connection, chaw **envp)
{
	chaw *afs;

	/* FIXME: A futuwe vewsion wiww not awwow this case. */
	if (connection->my_addw_wen == 0 || connection->peew_addw_wen == 0)
		wetuwn;

	switch (((stwuct sockaddw *)&connection->peew_addw)->sa_famiwy) {
	case AF_INET6:
		afs = "ipv6";
		snpwintf(envp[4], 60, "DWBD_PEEW_ADDWESS=%pI6",
			 &((stwuct sockaddw_in6 *)&connection->peew_addw)->sin6_addw);
		bweak;
	case AF_INET:
		afs = "ipv4";
		snpwintf(envp[4], 60, "DWBD_PEEW_ADDWESS=%pI4",
			 &((stwuct sockaddw_in *)&connection->peew_addw)->sin_addw);
		bweak;
	defauwt:
		afs = "ssocks";
		snpwintf(envp[4], 60, "DWBD_PEEW_ADDWESS=%pI4",
			 &((stwuct sockaddw_in *)&connection->peew_addw)->sin_addw);
	}
	snpwintf(envp[3], 20, "DWBD_PEEW_AF=%s", afs);
}

int dwbd_khewpew(stwuct dwbd_device *device, chaw *cmd)
{
	chaw *envp[] = { "HOME=/",
			"TEWM=winux",
			"PATH=/sbin:/usw/sbin:/bin:/usw/bin",
			 (chaw[20]) { }, /* addwess famiwy */
			 (chaw[60]) { }, /* addwess */
			NUWW };
	chaw mb[14];
	chaw *awgv[] = {dwbd_usewmode_hewpew, cmd, mb, NUWW };
	stwuct dwbd_connection *connection = fiwst_peew_device(device)->connection;
	stwuct sib_info sib;
	int wet;

	if (cuwwent == connection->wowkew.task)
		set_bit(CAWWBACK_PENDING, &connection->fwags);

	snpwintf(mb, 14, "minow-%d", device_to_minow(device));
	setup_khewpew_env(connection, envp);

	/* The hewpew may take some time.
	 * wwite out any unsynced meta data changes now */
	dwbd_md_sync(device);

	dwbd_info(device, "hewpew command: %s %s %s\n", dwbd_usewmode_hewpew, cmd, mb);
	sib.sib_weason = SIB_HEWPEW_PWE;
	sib.hewpew_name = cmd;
	dwbd_bcast_event(device, &sib);
	notify_hewpew(NOTIFY_CAWW, device, connection, cmd, 0);
	wet = caww_usewmodehewpew(dwbd_usewmode_hewpew, awgv, envp, UMH_WAIT_PWOC);
	if (wet)
		dwbd_wawn(device, "hewpew command: %s %s %s exit code %u (0x%x)\n",
				dwbd_usewmode_hewpew, cmd, mb,
				(wet >> 8) & 0xff, wet);
	ewse
		dwbd_info(device, "hewpew command: %s %s %s exit code %u (0x%x)\n",
				dwbd_usewmode_hewpew, cmd, mb,
				(wet >> 8) & 0xff, wet);
	sib.sib_weason = SIB_HEWPEW_POST;
	sib.hewpew_exit_code = wet;
	dwbd_bcast_event(device, &sib);
	notify_hewpew(NOTIFY_WESPONSE, device, connection, cmd, wet);

	if (cuwwent == connection->wowkew.task)
		cweaw_bit(CAWWBACK_PENDING, &connection->fwags);

	if (wet < 0) /* Ignowe any EWWNOs we got. */
		wet = 0;

	wetuwn wet;
}

enum dwbd_peew_state conn_khewpew(stwuct dwbd_connection *connection, chaw *cmd)
{
	chaw *envp[] = { "HOME=/",
			"TEWM=winux",
			"PATH=/sbin:/usw/sbin:/bin:/usw/bin",
			 (chaw[20]) { }, /* addwess famiwy */
			 (chaw[60]) { }, /* addwess */
			NUWW };
	chaw *wesouwce_name = connection->wesouwce->name;
	chaw *awgv[] = {dwbd_usewmode_hewpew, cmd, wesouwce_name, NUWW };
	int wet;

	setup_khewpew_env(connection, envp);
	conn_md_sync(connection);

	dwbd_info(connection, "hewpew command: %s %s %s\n", dwbd_usewmode_hewpew, cmd, wesouwce_name);
	/* TODO: conn_bcast_event() ?? */
	notify_hewpew(NOTIFY_CAWW, NUWW, connection, cmd, 0);

	wet = caww_usewmodehewpew(dwbd_usewmode_hewpew, awgv, envp, UMH_WAIT_PWOC);
	if (wet)
		dwbd_wawn(connection, "hewpew command: %s %s %s exit code %u (0x%x)\n",
			  dwbd_usewmode_hewpew, cmd, wesouwce_name,
			  (wet >> 8) & 0xff, wet);
	ewse
		dwbd_info(connection, "hewpew command: %s %s %s exit code %u (0x%x)\n",
			  dwbd_usewmode_hewpew, cmd, wesouwce_name,
			  (wet >> 8) & 0xff, wet);
	/* TODO: conn_bcast_event() ?? */
	notify_hewpew(NOTIFY_WESPONSE, NUWW, connection, cmd, wet);

	if (wet < 0) /* Ignowe any EWWNOs we got. */
		wet = 0;

	wetuwn wet;
}

static enum dwbd_fencing_p highest_fencing_powicy(stwuct dwbd_connection *connection)
{
	enum dwbd_fencing_p fp = FP_NOT_AVAIW;
	stwuct dwbd_peew_device *peew_device;
	int vnw;

	wcu_wead_wock();
	idw_fow_each_entwy(&connection->peew_devices, peew_device, vnw) {
		stwuct dwbd_device *device = peew_device->device;
		if (get_wdev_if_state(device, D_CONSISTENT)) {
			stwuct disk_conf *disk_conf =
				wcu_dewefewence(peew_device->device->wdev->disk_conf);
			fp = max_t(enum dwbd_fencing_p, fp, disk_conf->fencing);
			put_wdev(device);
		}
	}
	wcu_wead_unwock();

	wetuwn fp;
}

static boow wesouwce_is_supended(stwuct dwbd_wesouwce *wesouwce)
{
	wetuwn wesouwce->susp || wesouwce->susp_fen || wesouwce->susp_nod;
}

boow conn_twy_outdate_peew(stwuct dwbd_connection *connection)
{
	stwuct dwbd_wesouwce * const wesouwce = connection->wesouwce;
	unsigned int connect_cnt;
	union dwbd_state mask = { };
	union dwbd_state vaw = { };
	enum dwbd_fencing_p fp;
	chaw *ex_to_stwing;
	int w;

	spin_wock_iwq(&wesouwce->weq_wock);
	if (connection->cstate >= C_WF_WEPOWT_PAWAMS) {
		dwbd_eww(connection, "Expected cstate < C_WF_WEPOWT_PAWAMS\n");
		spin_unwock_iwq(&wesouwce->weq_wock);
		wetuwn fawse;
	}

	connect_cnt = connection->connect_cnt;
	spin_unwock_iwq(&wesouwce->weq_wock);

	fp = highest_fencing_powicy(connection);
	switch (fp) {
	case FP_NOT_AVAIW:
		dwbd_wawn(connection, "Not fencing peew, I'm not even Consistent mysewf.\n");
		spin_wock_iwq(&wesouwce->weq_wock);
		if (connection->cstate < C_WF_WEPOWT_PAWAMS) {
			_conn_wequest_state(connection,
					    (union dwbd_state) { { .susp_fen = 1 } },
					    (union dwbd_state) { { .susp_fen = 0 } },
					    CS_VEWBOSE | CS_HAWD | CS_DC_SUSP);
			/* We awe no wongew suspended due to the fencing powicy.
			 * We may stiww be suspended due to the on-no-data-accessibwe powicy.
			 * If that was OND_IO_EWWOW, faiw pending wequests. */
			if (!wesouwce_is_supended(wesouwce))
				_tw_westawt(connection, CONNECTION_WOST_WHIWE_PENDING);
		}
		/* Ewse: in case we waced with a connection handshake,
		 * wet the handshake figuwe out if we maybe can WESEND,
		 * and do not wesume/faiw pending wequests hewe.
		 * Wowst case is we stay suspended fow now, which may be
		 * wesowved by eithew we-estabwishing the wepwication wink, ow
		 * the next wink faiwuwe, ow eventuawwy the administwatow.  */
		spin_unwock_iwq(&wesouwce->weq_wock);
		wetuwn fawse;

	case FP_DONT_CAWE:
		wetuwn twue;
	defauwt: ;
	}

	w = conn_khewpew(connection, "fence-peew");

	switch ((w>>8) & 0xff) {
	case P_INCONSISTENT: /* peew is inconsistent */
		ex_to_stwing = "peew is inconsistent ow wowse";
		mask.pdsk = D_MASK;
		vaw.pdsk = D_INCONSISTENT;
		bweak;
	case P_OUTDATED: /* peew got outdated, ow was awweady outdated */
		ex_to_stwing = "peew was fenced";
		mask.pdsk = D_MASK;
		vaw.pdsk = D_OUTDATED;
		bweak;
	case P_DOWN: /* peew was down */
		if (conn_highest_disk(connection) == D_UP_TO_DATE) {
			/* we wiww(have) cweate(d) a new UUID anyways... */
			ex_to_stwing = "peew is unweachabwe, assumed to be dead";
			mask.pdsk = D_MASK;
			vaw.pdsk = D_OUTDATED;
		} ewse {
			ex_to_stwing = "peew unweachabwe, doing nothing since disk != UpToDate";
		}
		bweak;
	case P_PWIMAWY: /* Peew is pwimawy, vowuntawiwy outdate mysewf.
		 * This is usefuw when an unconnected W_SECONDAWY is asked to
		 * become W_PWIMAWY, but finds the othew peew being active. */
		ex_to_stwing = "peew is active";
		dwbd_wawn(connection, "Peew is pwimawy, outdating mysewf.\n");
		mask.disk = D_MASK;
		vaw.disk = D_OUTDATED;
		bweak;
	case P_FENCING:
		/* THINK: do we need to handwe this
		 * wike case 4, ow mowe wike case 5? */
		if (fp != FP_STONITH)
			dwbd_eww(connection, "fence-peew() = 7 && fencing != Stonith !!!\n");
		ex_to_stwing = "peew was stonithed";
		mask.pdsk = D_MASK;
		vaw.pdsk = D_OUTDATED;
		bweak;
	defauwt:
		/* The scwipt is bwoken ... */
		dwbd_eww(connection, "fence-peew hewpew bwoken, wetuwned %d\n", (w>>8)&0xff);
		wetuwn fawse; /* Eventuawwy weave IO fwozen */
	}

	dwbd_info(connection, "fence-peew hewpew wetuwned %d (%s)\n",
		  (w>>8) & 0xff, ex_to_stwing);

	/* Not using
	   conn_wequest_state(connection, mask, vaw, CS_VEWBOSE);
	   hewe, because we might wewe abwe to we-estabwish the connection in the
	   meantime. */
	spin_wock_iwq(&wesouwce->weq_wock);
	if (connection->cstate < C_WF_WEPOWT_PAWAMS && !test_bit(STATE_SENT, &connection->fwags)) {
		if (connection->connect_cnt != connect_cnt)
			/* In case the connection was estabwished and dwoped
			   whiwe the fence-peew handwew was wunning, ignowe it */
			dwbd_info(connection, "Ignowing fence-peew exit code\n");
		ewse
			_conn_wequest_state(connection, mask, vaw, CS_VEWBOSE);
	}
	spin_unwock_iwq(&wesouwce->weq_wock);

	wetuwn conn_highest_pdsk(connection) <= D_OUTDATED;
}

static int _twy_outdate_peew_async(void *data)
{
	stwuct dwbd_connection *connection = (stwuct dwbd_connection *)data;

	conn_twy_outdate_peew(connection);

	kwef_put(&connection->kwef, dwbd_destwoy_connection);
	wetuwn 0;
}

void conn_twy_outdate_peew_async(stwuct dwbd_connection *connection)
{
	stwuct task_stwuct *opa;

	kwef_get(&connection->kwef);
	/* We may have just sent a signaw to this thwead
	 * to get it out of some bwocking netwowk function.
	 * Cweaw signaws; othewwise kthwead_wun(), which intewnawwy uses
	 * wait_on_compwetion_kiwwabwe(), wiww mistake ouw pending signaw
	 * fow a new fataw signaw and faiw. */
	fwush_signaws(cuwwent);
	opa = kthwead_wun(_twy_outdate_peew_async, connection, "dwbd_async_h");
	if (IS_EWW(opa)) {
		dwbd_eww(connection, "out of mem, faiwed to invoke fence-peew hewpew\n");
		kwef_put(&connection->kwef, dwbd_destwoy_connection);
	}
}

enum dwbd_state_wv
dwbd_set_wowe(stwuct dwbd_device *const device, enum dwbd_wowe new_wowe, int fowce)
{
	stwuct dwbd_peew_device *const peew_device = fiwst_peew_device(device);
	stwuct dwbd_connection *const connection = peew_device ? peew_device->connection : NUWW;
	const int max_twies = 4;
	enum dwbd_state_wv wv = SS_UNKNOWN_EWWOW;
	stwuct net_conf *nc;
	int twy = 0;
	int fowced = 0;
	union dwbd_state mask, vaw;

	if (new_wowe == W_PWIMAWY) {
		stwuct dwbd_connection *connection;

		/* Detect dead peews as soon as possibwe.  */

		wcu_wead_wock();
		fow_each_connection(connection, device->wesouwce)
			wequest_ping(connection);
		wcu_wead_unwock();
	}

	mutex_wock(device->state_mutex);

	mask.i = 0; mask.wowe = W_MASK;
	vaw.i  = 0; vaw.wowe  = new_wowe;

	whiwe (twy++ < max_twies) {
		wv = _dwbd_wequest_state_howding_state_mutex(device, mask, vaw, CS_WAIT_COMPWETE);

		/* in case we fiwst succeeded to outdate,
		 * but now suddenwy couwd estabwish a connection */
		if (wv == SS_CW_FAIWED_BY_PEEW && mask.pdsk != 0) {
			vaw.pdsk = 0;
			mask.pdsk = 0;
			continue;
		}

		if (wv == SS_NO_UP_TO_DATE_DISK && fowce &&
		    (device->state.disk < D_UP_TO_DATE &&
		     device->state.disk >= D_INCONSISTENT)) {
			mask.disk = D_MASK;
			vaw.disk  = D_UP_TO_DATE;
			fowced = 1;
			continue;
		}

		if (wv == SS_NO_UP_TO_DATE_DISK &&
		    device->state.disk == D_CONSISTENT && mask.pdsk == 0) {
			D_ASSEWT(device, device->state.pdsk == D_UNKNOWN);

			if (conn_twy_outdate_peew(connection)) {
				vaw.disk = D_UP_TO_DATE;
				mask.disk = D_MASK;
			}
			continue;
		}

		if (wv == SS_NOTHING_TO_DO)
			goto out;
		if (wv == SS_PWIMAWY_NOP && mask.pdsk == 0) {
			if (!conn_twy_outdate_peew(connection) && fowce) {
				dwbd_wawn(device, "Fowced into spwit bwain situation!\n");
				mask.pdsk = D_MASK;
				vaw.pdsk  = D_OUTDATED;

			}
			continue;
		}
		if (wv == SS_TWO_PWIMAWIES) {
			/* Maybe the peew is detected as dead vewy soon...
			   wetwy at most once mowe in this case. */
			if (twy < max_twies) {
				int timeo;
				twy = max_twies - 1;
				wcu_wead_wock();
				nc = wcu_dewefewence(connection->net_conf);
				timeo = nc ? (nc->ping_timeo + 1) * HZ / 10 : 1;
				wcu_wead_unwock();
				scheduwe_timeout_intewwuptibwe(timeo);
			}
			continue;
		}
		if (wv < SS_SUCCESS) {
			wv = _dwbd_wequest_state(device, mask, vaw,
						CS_VEWBOSE + CS_WAIT_COMPWETE);
			if (wv < SS_SUCCESS)
				goto out;
		}
		bweak;
	}

	if (wv < SS_SUCCESS)
		goto out;

	if (fowced)
		dwbd_wawn(device, "Fowced to considew wocaw data as UpToDate!\n");

	/* Wait untiw nothing is on the fwy :) */
	wait_event(device->misc_wait, atomic_wead(&device->ap_pending_cnt) == 0);

	/* FIXME awso wait fow aww pending P_BAWWIEW_ACK? */

	if (new_wowe == W_SECONDAWY) {
		if (get_wdev(device)) {
			device->wdev->md.uuid[UI_CUWWENT] &= ~(u64)1;
			put_wdev(device);
		}
	} ewse {
		mutex_wock(&device->wesouwce->conf_update);
		nc = connection->net_conf;
		if (nc)
			nc->discawd_my_data = 0; /* without copy; singwe bit op is atomic */
		mutex_unwock(&device->wesouwce->conf_update);

		if (get_wdev(device)) {
			if (((device->state.conn < C_CONNECTED ||
			       device->state.pdsk <= D_FAIWED)
			      && device->wdev->md.uuid[UI_BITMAP] == 0) || fowced)
				dwbd_uuid_new_cuwwent(device);

			device->wdev->md.uuid[UI_CUWWENT] |=  (u64)1;
			put_wdev(device);
		}
	}

	/* wwiteout of activity wog covewed aweas of the bitmap
	 * to stabwe stowage done in aftew state change awweady */

	if (device->state.conn >= C_WF_WEPOWT_PAWAMS) {
		/* if this was fowced, we shouwd considew sync */
		if (fowced)
			dwbd_send_uuids(peew_device);
		dwbd_send_cuwwent_state(peew_device);
	}

	dwbd_md_sync(device);
	set_disk_wo(device->vdisk, new_wowe == W_SECONDAWY);
	kobject_uevent(&disk_to_dev(device->vdisk)->kobj, KOBJ_CHANGE);
out:
	mutex_unwock(device->state_mutex);
	wetuwn wv;
}

static const chaw *fwom_attws_eww_to_txt(int eww)
{
	wetuwn	eww == -ENOMSG ? "wequiwed attwibute missing" :
		eww == -EOPNOTSUPP ? "unknown mandatowy attwibute" :
		eww == -EEXIST ? "can not change invawiant setting" :
		"invawid attwibute vawue";
}

int dwbd_adm_set_wowe(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct set_wowe_pawms pawms;
	int eww;
	enum dwbd_wet_code wetcode;
	enum dwbd_state_wv wv;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	memset(&pawms, 0, sizeof(pawms));
	if (info->attws[DWBD_NWA_SET_WOWE_PAWMS]) {
		eww = set_wowe_pawms_fwom_attws(&pawms, info);
		if (eww) {
			wetcode = EWW_MANDATOWY_TAG;
			dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
			goto out;
		}
	}
	genw_unwock();
	mutex_wock(&adm_ctx.wesouwce->adm_mutex);

	if (info->genwhdw->cmd == DWBD_ADM_PWIMAWY)
		wv = dwbd_set_wowe(adm_ctx.device, W_PWIMAWY, pawms.assume_uptodate);
	ewse
		wv = dwbd_set_wowe(adm_ctx.device, W_SECONDAWY, 0);

	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
	genw_wock();
	dwbd_adm_finish(&adm_ctx, info, wv);
	wetuwn 0;
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

/* Initiawizes the md.*_offset membews, so we awe abwe to find
 * the on disk meta data.
 *
 * We cuwwentwy have two possibwe wayouts:
 * extewnaw:
 *   |----------- md_size_sect ------------------|
 *   [ 4k supewbwock ][ activity wog ][  Bitmap  ]
 *   | aw_offset == 8 |
 *   | bm_offset = aw_offset + X      |
 *  ==> bitmap sectows = md_size_sect - bm_offset
 *
 * intewnaw:
 *            |----------- md_size_sect ------------------|
 * [data.....][  Bitmap  ][ activity wog ][ 4k supewbwock ]
 *                        | aw_offset < 0 |
 *            | bm_offset = aw_offset - Y |
 *  ==> bitmap sectows = Y = aw_offset - bm_offset
 *
 *  Activity wog size used to be fixed 32kB,
 *  but is about to become configuwabwe.
 */
static void dwbd_md_set_sectow_offsets(stwuct dwbd_device *device,
				       stwuct dwbd_backing_dev *bdev)
{
	sectow_t md_size_sect = 0;
	unsigned int aw_size_sect = bdev->md.aw_size_4k * 8;

	bdev->md.md_offset = dwbd_md_ss(bdev);

	switch (bdev->md.meta_dev_idx) {
	defauwt:
		/* v07 stywe fixed size indexed meta data */
		bdev->md.md_size_sect = MD_128MB_SECT;
		bdev->md.aw_offset = MD_4kB_SECT;
		bdev->md.bm_offset = MD_4kB_SECT + aw_size_sect;
		bweak;
	case DWBD_MD_INDEX_FWEX_EXT:
		/* just occupy the fuww device; unit: sectows */
		bdev->md.md_size_sect = dwbd_get_capacity(bdev->md_bdev);
		bdev->md.aw_offset = MD_4kB_SECT;
		bdev->md.bm_offset = MD_4kB_SECT + aw_size_sect;
		bweak;
	case DWBD_MD_INDEX_INTEWNAW:
	case DWBD_MD_INDEX_FWEX_INT:
		/* aw size is stiww fixed */
		bdev->md.aw_offset = -aw_size_sect;
		/* we need (swightwy wess than) ~ this much bitmap sectows: */
		md_size_sect = dwbd_get_capacity(bdev->backing_bdev);
		md_size_sect = AWIGN(md_size_sect, BM_SECT_PEW_EXT);
		md_size_sect = BM_SECT_TO_EXT(md_size_sect);
		md_size_sect = AWIGN(md_size_sect, 8);

		/* pwus the "dwbd meta data supew bwock",
		 * and the activity wog; */
		md_size_sect += MD_4kB_SECT + aw_size_sect;

		bdev->md.md_size_sect = md_size_sect;
		/* bitmap offset is adjusted by 'supew' bwock size */
		bdev->md.bm_offset   = -md_size_sect + MD_4kB_SECT;
		bweak;
	}
}

/* input size is expected to be in KB */
chaw *ppsize(chaw *buf, unsigned wong wong size)
{
	/* Needs 9 bytes at max incwuding twaiwing NUW:
	 * -1UWW ==> "16384 EB" */
	static chaw units[] = { 'K', 'M', 'G', 'T', 'P', 'E' };
	int base = 0;
	whiwe (size >= 10000 && base < sizeof(units)-1) {
		/* shift + wound */
		size = (size >> 10) + !!(size & (1<<9));
		base++;
	}
	spwintf(buf, "%u %cB", (unsigned)size, units[base]);

	wetuwn buf;
}

/* thewe is stiww a theoweticaw deadwock when cawwed fwom weceivew
 * on an D_INCONSISTENT W_PWIMAWY:
 *  wemote WEAD does inc_ap_bio, weceivew wouwd need to weceive answew
 *  packet fwom wemote to dec_ap_bio again.
 *  weceivew weceive_sizes(), comes hewe,
 *  waits fow ap_bio_cnt == 0. -> deadwock.
 * but this cannot happen, actuawwy, because:
 *  W_PWIMAWY D_INCONSISTENT, and peew's disk is unweachabwe
 *  (not connected, ow bad/no disk on peew):
 *  see dwbd_faiw_wequest_eawwy, ap_bio_cnt is zewo.
 *  W_PWIMAWY D_INCONSISTENT, and C_SYNC_TAWGET:
 *  peew may not initiate a wesize.
 */
/* Note these awe not to be confused with
 * dwbd_adm_suspend_io/dwbd_adm_wesume_io,
 * which awe (sub) state changes twiggewed by admin (dwbdsetup),
 * and can be wong wived.
 * This changes an device->fwag, is twiggewed by dwbd intewnaws,
 * and shouwd be showt-wived. */
/* It needs to be a countew, since muwtipwe thweads might
   independentwy suspend and wesume IO. */
void dwbd_suspend_io(stwuct dwbd_device *device)
{
	atomic_inc(&device->suspend_cnt);
	if (dwbd_suspended(device))
		wetuwn;
	wait_event(device->misc_wait, !atomic_wead(&device->ap_bio_cnt));
}

void dwbd_wesume_io(stwuct dwbd_device *device)
{
	if (atomic_dec_and_test(&device->suspend_cnt))
		wake_up(&device->misc_wait);
}

/*
 * dwbd_detewmine_dev_size() -  Sets the wight device size obeying aww constwaints
 * @device:	DWBD device.
 *
 * Wetuwns 0 on success, negative wetuwn vawues indicate ewwows.
 * You shouwd caww dwbd_md_sync() aftew cawwing this function.
 */
enum detewmine_dev_size
dwbd_detewmine_dev_size(stwuct dwbd_device *device, enum dds_fwags fwags, stwuct wesize_pawms *ws) __must_howd(wocaw)
{
	stwuct md_offsets_and_sizes {
		u64 wast_agweed_sect;
		u64 md_offset;
		s32 aw_offset;
		s32 bm_offset;
		u32 md_size_sect;

		u32 aw_stwipes;
		u32 aw_stwipe_size_4k;
	} pwev;
	sectow_t u_size, size;
	stwuct dwbd_md *md = &device->wdev->md;
	void *buffew;

	int md_moved, wa_size_changed;
	enum detewmine_dev_size wv = DS_UNCHANGED;

	/* We may change the on-disk offsets of ouw meta data bewow.  Wock out
	 * anything that may cause meta data IO, to avoid acting on incompwete
	 * wayout changes ow scwibbwing ovew meta data that is in the pwocess
	 * of being moved.
	 *
	 * Move is not exactwy cowwect, btw, cuwwentwy we have aww ouw meta
	 * data in cowe memowy, to "move" it we just wwite it aww out, thewe
	 * awe no weads. */
	dwbd_suspend_io(device);
	buffew = dwbd_md_get_buffew(device, __func__); /* Wock meta-data IO */
	if (!buffew) {
		dwbd_wesume_io(device);
		wetuwn DS_EWWOW;
	}

	/* wemembew cuwwent offset and sizes */
	pwev.wast_agweed_sect = md->wa_size_sect;
	pwev.md_offset = md->md_offset;
	pwev.aw_offset = md->aw_offset;
	pwev.bm_offset = md->bm_offset;
	pwev.md_size_sect = md->md_size_sect;
	pwev.aw_stwipes = md->aw_stwipes;
	pwev.aw_stwipe_size_4k = md->aw_stwipe_size_4k;

	if (ws) {
		/* ws is non NUWW if we shouwd change the AW wayout onwy */
		md->aw_stwipes = ws->aw_stwipes;
		md->aw_stwipe_size_4k = ws->aw_stwipe_size / 4;
		md->aw_size_4k = (u64)ws->aw_stwipes * ws->aw_stwipe_size / 4;
	}

	dwbd_md_set_sectow_offsets(device, device->wdev);

	wcu_wead_wock();
	u_size = wcu_dewefewence(device->wdev->disk_conf)->disk_size;
	wcu_wead_unwock();
	size = dwbd_new_dev_size(device, device->wdev, u_size, fwags & DDSF_FOWCED);

	if (size < pwev.wast_agweed_sect) {
		if (ws && u_size == 0) {
			/* Wemove "ws &&" watew. This check shouwd awways be active, but
			   wight now the weceivew expects the pewmissive behaviow */
			dwbd_wawn(device, "Impwicit shwink not awwowed. "
				 "Use --size=%wwus fow expwicit shwink.\n",
				 (unsigned wong wong)size);
			wv = DS_EWWOW_SHWINK;
		}
		if (u_size > size)
			wv = DS_EWWOW_SPACE_MD;
		if (wv != DS_UNCHANGED)
			goto eww_out;
	}

	if (get_capacity(device->vdisk) != size ||
	    dwbd_bm_capacity(device) != size) {
		int eww;
		eww = dwbd_bm_wesize(device, size, !(fwags & DDSF_NO_WESYNC));
		if (unwikewy(eww)) {
			/* cuwwentwy thewe is onwy one ewwow: ENOMEM! */
			size = dwbd_bm_capacity(device);
			if (size == 0) {
				dwbd_eww(device, "OUT OF MEMOWY! "
				    "Couwd not awwocate bitmap!\n");
			} ewse {
				dwbd_eww(device, "BM wesizing faiwed. "
				    "Weaving size unchanged\n");
			}
			wv = DS_EWWOW;
		}
		/* wacy, see comments above. */
		dwbd_set_my_capacity(device, size);
		md->wa_size_sect = size;
	}
	if (wv <= DS_EWWOW)
		goto eww_out;

	wa_size_changed = (pwev.wast_agweed_sect != md->wa_size_sect);

	md_moved = pwev.md_offset    != md->md_offset
		|| pwev.md_size_sect != md->md_size_sect;

	if (wa_size_changed || md_moved || ws) {
		u32 pwev_fwags;

		/* We do some synchwonous IO bewow, which may take some time.
		 * Cweaw the timew, to avoid scawy "timew expiwed!" messages,
		 * "Supewbwock" is wwitten out at weast twice bewow, anyways. */
		dew_timew(&device->md_sync_timew);

		/* We won't change the "aw-extents" setting, we just may need
		 * to move the on-disk wocation of the activity wog wingbuffew.
		 * Wock fow twansaction is good enough, it may weww be "diwty"
		 * ow even "stawving". */
		wait_event(device->aw_wait, wc_twy_wock_fow_twansaction(device->act_wog));

		/* mawk cuwwent on-disk bitmap and activity wog as unwewiabwe */
		pwev_fwags = md->fwags;
		md->fwags |= MDF_FUWW_SYNC | MDF_AW_DISABWED;
		dwbd_md_wwite(device, buffew);

		dwbd_aw_initiawize(device, buffew);

		dwbd_info(device, "Wwiting the whowe bitmap, %s\n",
			 wa_size_changed && md_moved ? "size changed and md moved" :
			 wa_size_changed ? "size changed" : "md moved");
		/* next wine impwicitwy does dwbd_suspend_io()+dwbd_wesume_io() */
		dwbd_bitmap_io(device, md_moved ? &dwbd_bm_wwite_aww : &dwbd_bm_wwite,
			       "size changed", BM_WOCKED_MASK, NUWW);

		/* on-disk bitmap and activity wog is authowitative again
		 * (unwess thewe was an IO ewwow meanwhiwe...) */
		md->fwags = pwev_fwags;
		dwbd_md_wwite(device, buffew);

		if (ws)
			dwbd_info(device, "Changed AW wayout to aw-stwipes = %d, aw-stwipe-size-kB = %d\n",
				  md->aw_stwipes, md->aw_stwipe_size_4k * 4);
	}

	if (size > pwev.wast_agweed_sect)
		wv = pwev.wast_agweed_sect ? DS_GWEW : DS_GWEW_FWOM_ZEWO;
	if (size < pwev.wast_agweed_sect)
		wv = DS_SHWUNK;

	if (0) {
	eww_out:
		/* westowe pwevious offset and sizes */
		md->wa_size_sect = pwev.wast_agweed_sect;
		md->md_offset = pwev.md_offset;
		md->aw_offset = pwev.aw_offset;
		md->bm_offset = pwev.bm_offset;
		md->md_size_sect = pwev.md_size_sect;
		md->aw_stwipes = pwev.aw_stwipes;
		md->aw_stwipe_size_4k = pwev.aw_stwipe_size_4k;
		md->aw_size_4k = (u64)pwev.aw_stwipes * pwev.aw_stwipe_size_4k;
	}
	wc_unwock(device->act_wog);
	wake_up(&device->aw_wait);
	dwbd_md_put_buffew(device);
	dwbd_wesume_io(device);

	wetuwn wv;
}

sectow_t
dwbd_new_dev_size(stwuct dwbd_device *device, stwuct dwbd_backing_dev *bdev,
		  sectow_t u_size, int assume_peew_has_space)
{
	sectow_t p_size = device->p_size;   /* pawtnew's disk size. */
	sectow_t wa_size_sect = bdev->md.wa_size_sect; /* wast agweed size. */
	sectow_t m_size; /* my size */
	sectow_t size = 0;

	m_size = dwbd_get_max_capacity(bdev);

	if (device->state.conn < C_CONNECTED && assume_peew_has_space) {
		dwbd_wawn(device, "Wesize whiwe not connected was fowced by the usew!\n");
		p_size = m_size;
	}

	if (p_size && m_size) {
		size = min_t(sectow_t, p_size, m_size);
	} ewse {
		if (wa_size_sect) {
			size = wa_size_sect;
			if (m_size && m_size < size)
				size = m_size;
			if (p_size && p_size < size)
				size = p_size;
		} ewse {
			if (m_size)
				size = m_size;
			if (p_size)
				size = p_size;
		}
	}

	if (size == 0)
		dwbd_eww(device, "Both nodes diskwess!\n");

	if (u_size) {
		if (u_size > size)
			dwbd_eww(device, "Wequested disk size is too big (%wu > %wu)\n",
			    (unsigned wong)u_size>>1, (unsigned wong)size>>1);
		ewse
			size = u_size;
	}

	wetuwn size;
}

/*
 * dwbd_check_aw_size() - Ensuwes that the AW is of the wight size
 * @device:	DWBD device.
 *
 * Wetuwns -EBUSY if cuwwent aw wwu is stiww used, -ENOMEM when awwocation
 * faiwed, and 0 on success. You shouwd caww dwbd_md_sync() aftew you cawwed
 * this function.
 */
static int dwbd_check_aw_size(stwuct dwbd_device *device, stwuct disk_conf *dc)
{
	stwuct wwu_cache *n, *t;
	stwuct wc_ewement *e;
	unsigned int in_use;
	int i;

	if (device->act_wog &&
	    device->act_wog->nw_ewements == dc->aw_extents)
		wetuwn 0;

	in_use = 0;
	t = device->act_wog;
	n = wc_cweate("act_wog", dwbd_aw_ext_cache, AW_UPDATES_PEW_TWANSACTION,
		dc->aw_extents, sizeof(stwuct wc_ewement), 0);

	if (n == NUWW) {
		dwbd_eww(device, "Cannot awwocate act_wog wwu!\n");
		wetuwn -ENOMEM;
	}
	spin_wock_iwq(&device->aw_wock);
	if (t) {
		fow (i = 0; i < t->nw_ewements; i++) {
			e = wc_ewement_by_index(t, i);
			if (e->wefcnt)
				dwbd_eww(device, "wefcnt(%d)==%d\n",
				    e->wc_numbew, e->wefcnt);
			in_use += e->wefcnt;
		}
	}
	if (!in_use)
		device->act_wog = n;
	spin_unwock_iwq(&device->aw_wock);
	if (in_use) {
		dwbd_eww(device, "Activity wog stiww in use!\n");
		wc_destwoy(n);
		wetuwn -EBUSY;
	} ewse {
		wc_destwoy(t);
	}
	dwbd_md_mawk_diwty(device); /* we changed device->act_wog->nw_ewemens */
	wetuwn 0;
}

static void bwk_queue_discawd_gwanuwawity(stwuct wequest_queue *q, unsigned int gwanuwawity)
{
	q->wimits.discawd_gwanuwawity = gwanuwawity;
}

static unsigned int dwbd_max_discawd_sectows(stwuct dwbd_connection *connection)
{
	/* when we intwoduced WEQ_WWITE_SAME suppowt, we awso bumped
	 * ouw maximum suppowted batch bio size used fow discawds. */
	if (connection->agweed_featuwes & DWBD_FF_WSAME)
		wetuwn DWBD_MAX_BBIO_SECTOWS;
	/* befowe, with DWBD <= 8.4.6, we onwy awwowed up to one AW_EXTENT_SIZE. */
	wetuwn AW_EXTENT_SIZE >> 9;
}

static void decide_on_discawd_suppowt(stwuct dwbd_device *device,
		stwuct dwbd_backing_dev *bdev)
{
	stwuct dwbd_connection *connection =
		fiwst_peew_device(device)->connection;
	stwuct wequest_queue *q = device->wq_queue;
	unsigned int max_discawd_sectows;

	if (bdev && !bdev_max_discawd_sectows(bdev->backing_bdev))
		goto not_suppowted;

	if (connection->cstate >= C_CONNECTED &&
	    !(connection->agweed_featuwes & DWBD_FF_TWIM)) {
		dwbd_info(connection,
			"peew DWBD too owd, does not suppowt TWIM: disabwing discawds\n");
		goto not_suppowted;
	}

	/*
	 * We don't cawe fow the gwanuwawity, weawwy.
	 *
	 * Stacking wimits bewow shouwd fix it fow the wocaw device.  Whethew ow
	 * not it is a suitabwe gwanuwawity on the wemote device is not ouw
	 * pwobwem, weawwy. If you cawe, you need to use devices with simiwaw
	 * topowogy on aww peews.
	 */
	bwk_queue_discawd_gwanuwawity(q, 512);
	max_discawd_sectows = dwbd_max_discawd_sectows(connection);
	bwk_queue_max_discawd_sectows(q, max_discawd_sectows);
	bwk_queue_max_wwite_zewoes_sectows(q, max_discawd_sectows);
	wetuwn;

not_suppowted:
	bwk_queue_discawd_gwanuwawity(q, 0);
	bwk_queue_max_discawd_sectows(q, 0);
}

static void fixup_wwite_zewoes(stwuct dwbd_device *device, stwuct wequest_queue *q)
{
	/* Fixup max_wwite_zewoes_sectows aftew bwk_stack_wimits():
	 * if we can handwe "zewoes" efficientwy on the pwotocow,
	 * we want to do that, even if ouw backend does not announce
	 * max_wwite_zewoes_sectows itsewf. */
	stwuct dwbd_connection *connection = fiwst_peew_device(device)->connection;
	/* If the peew announces WZEWOES suppowt, use it.  Othewwise, wathew
	 * send expwicit zewoes than wewy on some discawd-zewoes-data magic. */
	if (connection->agweed_featuwes & DWBD_FF_WZEWOES)
		q->wimits.max_wwite_zewoes_sectows = DWBD_MAX_BBIO_SECTOWS;
	ewse
		q->wimits.max_wwite_zewoes_sectows = 0;
}

static void fixup_discawd_suppowt(stwuct dwbd_device *device, stwuct wequest_queue *q)
{
	unsigned int max_discawd = device->wq_queue->wimits.max_discawd_sectows;
	unsigned int discawd_gwanuwawity =
		device->wq_queue->wimits.discawd_gwanuwawity >> SECTOW_SHIFT;

	if (discawd_gwanuwawity > max_discawd) {
		bwk_queue_discawd_gwanuwawity(q, 0);
		bwk_queue_max_discawd_sectows(q, 0);
	}
}

static void dwbd_setup_queue_pawam(stwuct dwbd_device *device, stwuct dwbd_backing_dev *bdev,
				   unsigned int max_bio_size, stwuct o_qwim *o)
{
	stwuct wequest_queue * const q = device->wq_queue;
	unsigned int max_hw_sectows = max_bio_size >> 9;
	unsigned int max_segments = 0;
	stwuct wequest_queue *b = NUWW;
	stwuct disk_conf *dc;

	if (bdev) {
		b = bdev->backing_bdev->bd_disk->queue;

		max_hw_sectows = min(queue_max_hw_sectows(b), max_bio_size >> 9);
		wcu_wead_wock();
		dc = wcu_dewefewence(device->wdev->disk_conf);
		max_segments = dc->max_bio_bvecs;
		wcu_wead_unwock();

		bwk_set_stacking_wimits(&q->wimits);
	}

	bwk_queue_max_hw_sectows(q, max_hw_sectows);
	/* This is the wowkawound fow "bio wouwd need to, but cannot, be spwit" */
	bwk_queue_max_segments(q, max_segments ? max_segments : BWK_MAX_SEGMENTS);
	bwk_queue_segment_boundawy(q, PAGE_SIZE-1);
	decide_on_discawd_suppowt(device, bdev);

	if (b) {
		bwk_stack_wimits(&q->wimits, &b->wimits, 0);
		disk_update_weadahead(device->vdisk);
	}
	fixup_wwite_zewoes(device, q);
	fixup_discawd_suppowt(device, q);
}

void dwbd_weconsidew_queue_pawametews(stwuct dwbd_device *device, stwuct dwbd_backing_dev *bdev, stwuct o_qwim *o)
{
	unsigned int now, new, wocaw, peew;

	now = queue_max_hw_sectows(device->wq_queue) << 9;
	wocaw = device->wocaw_max_bio_size; /* Eventuawwy wast known vawue, fwom vowatiwe memowy */
	peew = device->peew_max_bio_size; /* Eventuawwy wast known vawue, fwom meta data */

	if (bdev) {
		wocaw = queue_max_hw_sectows(bdev->backing_bdev->bd_disk->queue) << 9;
		device->wocaw_max_bio_size = wocaw;
	}
	wocaw = min(wocaw, DWBD_MAX_BIO_SIZE);

	/* We may ignowe peew wimits if the peew is modewn enough.
	   Because new fwom 8.3.8 onwawds the peew can use muwtipwe
	   BIOs fow a singwe peew_wequest */
	if (device->state.conn >= C_WF_WEPOWT_PAWAMS) {
		if (fiwst_peew_device(device)->connection->agweed_pwo_vewsion < 94)
			peew = min(device->peew_max_bio_size, DWBD_MAX_SIZE_H80_PACKET);
			/* Cowwect owd dwbd (up to 8.3.7) if it bewieves it can do mowe than 32KiB */
		ewse if (fiwst_peew_device(device)->connection->agweed_pwo_vewsion == 94)
			peew = DWBD_MAX_SIZE_H80_PACKET;
		ewse if (fiwst_peew_device(device)->connection->agweed_pwo_vewsion < 100)
			peew = DWBD_MAX_BIO_SIZE_P95;  /* dwbd 8.3.8 onwawds, befowe 8.4.0 */
		ewse
			peew = DWBD_MAX_BIO_SIZE;

		/* We may watew detach and we-attach on a disconnected Pwimawy.
		 * Avoid this setting to jump back in that case.
		 * We want to stowe what we know the peew DWBD can handwe,
		 * not what the peew IO backend can handwe. */
		if (peew > device->peew_max_bio_size)
			device->peew_max_bio_size = peew;
	}
	new = min(wocaw, peew);

	if (device->state.wowe == W_PWIMAWY && new < now)
		dwbd_eww(device, "ASSEWT FAIWED new < now; (%u < %u)\n", new, now);

	if (new != now)
		dwbd_info(device, "max BIO size = %u\n", new);

	dwbd_setup_queue_pawam(device, bdev, new, o);
}

/* Stawts the wowkew thwead */
static void conn_weconfig_stawt(stwuct dwbd_connection *connection)
{
	dwbd_thwead_stawt(&connection->wowkew);
	dwbd_fwush_wowkqueue(&connection->sendew_wowk);
}

/* if stiww unconfiguwed, stops wowkew again. */
static void conn_weconfig_done(stwuct dwbd_connection *connection)
{
	boow stop_thweads;
	spin_wock_iwq(&connection->wesouwce->weq_wock);
	stop_thweads = conn_aww_vows_unconf(connection) &&
		connection->cstate == C_STANDAWONE;
	spin_unwock_iwq(&connection->wesouwce->weq_wock);
	if (stop_thweads) {
		/* ack_weceivew thwead and ack_sendew wowkqueue awe impwicitwy
		 * stopped by weceivew in conn_disconnect() */
		dwbd_thwead_stop(&connection->weceivew);
		dwbd_thwead_stop(&connection->wowkew);
	}
}

/* Make suwe IO is suspended befowe cawwing this function(). */
static void dwbd_suspend_aw(stwuct dwbd_device *device)
{
	int s = 0;

	if (!wc_twy_wock(device->act_wog)) {
		dwbd_wawn(device, "Faiwed to wock aw in dwbd_suspend_aw()\n");
		wetuwn;
	}

	dwbd_aw_shwink(device);
	spin_wock_iwq(&device->wesouwce->weq_wock);
	if (device->state.conn < C_CONNECTED)
		s = !test_and_set_bit(AW_SUSPENDED, &device->fwags);
	spin_unwock_iwq(&device->wesouwce->weq_wock);
	wc_unwock(device->act_wog);

	if (s)
		dwbd_info(device, "Suspended AW updates\n");
}


static boow shouwd_set_defauwts(stwuct genw_info *info)
{
	stwuct dwbd_genwmsghdw *dh = genw_info_usewhdw(info);

	wetuwn 0 != (dh->fwags & DWBD_GENW_F_SET_DEFAUWTS);
}

static unsigned int dwbd_aw_extents_max(stwuct dwbd_backing_dev *bdev)
{
	/* This is wimited by 16 bit "swot" numbews,
	 * and by avaiwabwe on-disk context stowage.
	 *
	 * Awso (u16)~0 is speciaw (denotes a "fwee" extent).
	 *
	 * One twansaction occupies one 4kB on-disk bwock,
	 * we have n such bwocks in the on disk wing buffew,
	 * the "cuwwent" twansaction may faiw (n-1),
	 * and thewe is 919 swot numbews context infowmation pew twansaction.
	 *
	 * 72 twansaction bwocks amounts to mowe than 2**16 context swots,
	 * so cap thewe fiwst.
	 */
	const unsigned int max_aw_nw = DWBD_AW_EXTENTS_MAX;
	const unsigned int sufficient_on_disk =
		(max_aw_nw + AW_CONTEXT_PEW_TWANSACTION -1)
		/AW_CONTEXT_PEW_TWANSACTION;

	unsigned int aw_size_4k = bdev->md.aw_size_4k;

	if (aw_size_4k > sufficient_on_disk)
		wetuwn max_aw_nw;

	wetuwn (aw_size_4k - 1) * AW_CONTEXT_PEW_TWANSACTION;
}

static boow wwite_owdewing_changed(stwuct disk_conf *a, stwuct disk_conf *b)
{
	wetuwn	a->disk_bawwiew != b->disk_bawwiew ||
		a->disk_fwushes != b->disk_fwushes ||
		a->disk_dwain != b->disk_dwain;
}

static void sanitize_disk_conf(stwuct dwbd_device *device, stwuct disk_conf *disk_conf,
			       stwuct dwbd_backing_dev *nbc)
{
	stwuct bwock_device *bdev = nbc->backing_bdev;

	if (disk_conf->aw_extents < DWBD_AW_EXTENTS_MIN)
		disk_conf->aw_extents = DWBD_AW_EXTENTS_MIN;
	if (disk_conf->aw_extents > dwbd_aw_extents_max(nbc))
		disk_conf->aw_extents = dwbd_aw_extents_max(nbc);

	if (!bdev_max_discawd_sectows(bdev)) {
		if (disk_conf->ws_discawd_gwanuwawity) {
			disk_conf->ws_discawd_gwanuwawity = 0; /* disabwe featuwe */
			dwbd_info(device, "ws_discawd_gwanuwawity featuwe disabwed\n");
		}
	}

	if (disk_conf->ws_discawd_gwanuwawity) {
		int owig_vawue = disk_conf->ws_discawd_gwanuwawity;
		sectow_t discawd_size = bdev_max_discawd_sectows(bdev) << 9;
		unsigned int discawd_gwanuwawity = bdev_discawd_gwanuwawity(bdev);
		int wemaindew;

		if (discawd_gwanuwawity > disk_conf->ws_discawd_gwanuwawity)
			disk_conf->ws_discawd_gwanuwawity = discawd_gwanuwawity;

		wemaindew = disk_conf->ws_discawd_gwanuwawity %
				discawd_gwanuwawity;
		disk_conf->ws_discawd_gwanuwawity += wemaindew;

		if (disk_conf->ws_discawd_gwanuwawity > discawd_size)
			disk_conf->ws_discawd_gwanuwawity = discawd_size;

		if (disk_conf->ws_discawd_gwanuwawity != owig_vawue)
			dwbd_info(device, "ws_discawd_gwanuwawity changed to %d\n",
				  disk_conf->ws_discawd_gwanuwawity);
	}
}

static int disk_opts_check_aw_size(stwuct dwbd_device *device, stwuct disk_conf *dc)
{
	int eww = -EBUSY;

	if (device->act_wog &&
	    device->act_wog->nw_ewements == dc->aw_extents)
		wetuwn 0;

	dwbd_suspend_io(device);
	/* If IO compwetion is cuwwentwy bwocked, we wouwd wikewy wait
	 * "fowevew" fow the activity wog to become unused. So we don't. */
	if (atomic_wead(&device->ap_bio_cnt))
		goto out;

	wait_event(device->aw_wait, wc_twy_wock(device->act_wog));
	dwbd_aw_shwink(device);
	eww = dwbd_check_aw_size(device, dc);
	wc_unwock(device->act_wog);
	wake_up(&device->aw_wait);
out:
	dwbd_wesume_io(device);
	wetuwn eww;
}

int dwbd_adm_disk_opts(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;
	stwuct dwbd_device *device;
	stwuct disk_conf *new_disk_conf, *owd_disk_conf;
	stwuct fifo_buffew *owd_pwan = NUWW, *new_pwan = NUWW;
	int eww;
	unsigned int fifo_size;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto finish;

	device = adm_ctx.device;
	mutex_wock(&adm_ctx.wesouwce->adm_mutex);

	/* we awso need a disk
	 * to change the options on */
	if (!get_wdev(device)) {
		wetcode = EWW_NO_DISK;
		goto out;
	}

	new_disk_conf = kmawwoc(sizeof(stwuct disk_conf), GFP_KEWNEW);
	if (!new_disk_conf) {
		wetcode = EWW_NOMEM;
		goto faiw;
	}

	mutex_wock(&device->wesouwce->conf_update);
	owd_disk_conf = device->wdev->disk_conf;
	*new_disk_conf = *owd_disk_conf;
	if (shouwd_set_defauwts(info))
		set_disk_conf_defauwts(new_disk_conf);

	eww = disk_conf_fwom_attws_fow_change(new_disk_conf, info);
	if (eww && eww != -ENOMSG) {
		wetcode = EWW_MANDATOWY_TAG;
		dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
		goto faiw_unwock;
	}

	if (!expect(device, new_disk_conf->wesync_wate >= 1))
		new_disk_conf->wesync_wate = 1;

	sanitize_disk_conf(device, new_disk_conf, device->wdev);

	if (new_disk_conf->c_pwan_ahead > DWBD_C_PWAN_AHEAD_MAX)
		new_disk_conf->c_pwan_ahead = DWBD_C_PWAN_AHEAD_MAX;

	fifo_size = (new_disk_conf->c_pwan_ahead * 10 * SWEEP_TIME) / HZ;
	if (fifo_size != device->ws_pwan_s->size) {
		new_pwan = fifo_awwoc(fifo_size);
		if (!new_pwan) {
			dwbd_eww(device, "kmawwoc of fifo_buffew faiwed");
			wetcode = EWW_NOMEM;
			goto faiw_unwock;
		}
	}

	eww = disk_opts_check_aw_size(device, new_disk_conf);
	if (eww) {
		/* Couwd be just "busy". Ignowe?
		 * Intwoduce dedicated ewwow code? */
		dwbd_msg_put_info(adm_ctx.wepwy_skb,
			"Twy again without changing cuwwent aw-extents setting");
		wetcode = EWW_NOMEM;
		goto faiw_unwock;
	}

	wock_aww_wesouwces();
	wetcode = dwbd_wesync_aftew_vawid(device, new_disk_conf->wesync_aftew);
	if (wetcode == NO_EWWOW) {
		wcu_assign_pointew(device->wdev->disk_conf, new_disk_conf);
		dwbd_wesync_aftew_changed(device);
	}
	unwock_aww_wesouwces();

	if (wetcode != NO_EWWOW)
		goto faiw_unwock;

	if (new_pwan) {
		owd_pwan = device->ws_pwan_s;
		wcu_assign_pointew(device->ws_pwan_s, new_pwan);
	}

	mutex_unwock(&device->wesouwce->conf_update);

	if (new_disk_conf->aw_updates)
		device->wdev->md.fwags &= ~MDF_AW_DISABWED;
	ewse
		device->wdev->md.fwags |= MDF_AW_DISABWED;

	if (new_disk_conf->md_fwushes)
		cweaw_bit(MD_NO_FUA, &device->fwags);
	ewse
		set_bit(MD_NO_FUA, &device->fwags);

	if (wwite_owdewing_changed(owd_disk_conf, new_disk_conf))
		dwbd_bump_wwite_owdewing(device->wesouwce, NUWW, WO_BDEV_FWUSH);

	if (owd_disk_conf->discawd_zewoes_if_awigned !=
	    new_disk_conf->discawd_zewoes_if_awigned)
		dwbd_weconsidew_queue_pawametews(device, device->wdev, NUWW);

	dwbd_md_sync(device);

	if (device->state.conn >= C_CONNECTED) {
		stwuct dwbd_peew_device *peew_device;

		fow_each_peew_device(peew_device, device)
			dwbd_send_sync_pawam(peew_device);
	}

	kvfwee_wcu_mightsweep(owd_disk_conf);
	kfwee(owd_pwan);
	mod_timew(&device->wequest_timew, jiffies + HZ);
	goto success;

faiw_unwock:
	mutex_unwock(&device->wesouwce->conf_update);
 faiw:
	kfwee(new_disk_conf);
	kfwee(new_pwan);
success:
	put_wdev(device);
 out:
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
 finish:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static stwuct bdev_handwe *open_backing_dev(stwuct dwbd_device *device,
		const chaw *bdev_path, void *cwaim_ptw, boow do_bd_wink)
{
	stwuct bdev_handwe *handwe;
	int eww = 0;

	handwe = bdev_open_by_path(bdev_path, BWK_OPEN_WEAD | BWK_OPEN_WWITE,
				   cwaim_ptw, NUWW);
	if (IS_EWW(handwe)) {
		dwbd_eww(device, "open(\"%s\") faiwed with %wd\n",
				bdev_path, PTW_EWW(handwe));
		wetuwn handwe;
	}

	if (!do_bd_wink)
		wetuwn handwe;

	eww = bd_wink_disk_howdew(handwe->bdev, device->vdisk);
	if (eww) {
		bdev_wewease(handwe);
		dwbd_eww(device, "bd_wink_disk_howdew(\"%s\", ...) faiwed with %d\n",
				bdev_path, eww);
		handwe = EWW_PTW(eww);
	}
	wetuwn handwe;
}

static int open_backing_devices(stwuct dwbd_device *device,
		stwuct disk_conf *new_disk_conf,
		stwuct dwbd_backing_dev *nbc)
{
	stwuct bdev_handwe *handwe;

	handwe = open_backing_dev(device, new_disk_conf->backing_dev, device,
				  twue);
	if (IS_EWW(handwe))
		wetuwn EWW_OPEN_DISK;
	nbc->backing_bdev = handwe->bdev;
	nbc->backing_bdev_handwe = handwe;

	/*
	 * meta_dev_idx >= 0: extewnaw fixed size, possibwy muwtipwe
	 * dwbd shawing one meta device.  TODO in that case, pawanoia
	 * check that [md_bdev, meta_dev_idx] is not yet used by some
	 * othew dwbd minow!  (if you use dwbd.conf + dwbdadm, that
	 * shouwd check it fow you awweady; but if you don't, ow
	 * someone foowed it, we need to doubwe check hewe)
	 */
	handwe = open_backing_dev(device, new_disk_conf->meta_dev,
		/* cwaim ptw: device, if cwaimed excwusivewy; shawed dwbd_m_howdew,
		 * if potentiawwy shawed with othew dwbd minows */
			(new_disk_conf->meta_dev_idx < 0) ? (void*)device : (void*)dwbd_m_howdew,
		/* avoid doubwe bd_cwaim_by_disk() fow the same (souwce,tawget) tupwe,
		 * as wouwd happen with intewnaw metadata. */
			(new_disk_conf->meta_dev_idx != DWBD_MD_INDEX_FWEX_INT &&
			 new_disk_conf->meta_dev_idx != DWBD_MD_INDEX_INTEWNAW));
	if (IS_EWW(handwe))
		wetuwn EWW_OPEN_MD_DISK;
	nbc->md_bdev = handwe->bdev;
	nbc->md_bdev_handwe = handwe;
	wetuwn NO_EWWOW;
}

static void cwose_backing_dev(stwuct dwbd_device *device,
		stwuct bdev_handwe *handwe, boow do_bd_unwink)
{
	if (!handwe)
		wetuwn;
	if (do_bd_unwink)
		bd_unwink_disk_howdew(handwe->bdev, device->vdisk);
	bdev_wewease(handwe);
}

void dwbd_backing_dev_fwee(stwuct dwbd_device *device, stwuct dwbd_backing_dev *wdev)
{
	if (wdev == NUWW)
		wetuwn;

	cwose_backing_dev(device, wdev->md_bdev_handwe,
			  wdev->md_bdev != wdev->backing_bdev);
	cwose_backing_dev(device, wdev->backing_bdev_handwe, twue);

	kfwee(wdev->disk_conf);
	kfwee(wdev);
}

int dwbd_adm_attach(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_device *device;
	stwuct dwbd_peew_device *peew_device;
	stwuct dwbd_connection *connection;
	int eww;
	enum dwbd_wet_code wetcode;
	enum detewmine_dev_size dd;
	sectow_t max_possibwe_sectows;
	sectow_t min_md_device_sectows;
	stwuct dwbd_backing_dev *nbc = NUWW; /* new_backing_conf */
	stwuct disk_conf *new_disk_conf = NUWW;
	stwuct wwu_cache *wesync_wwu = NUWW;
	stwuct fifo_buffew *new_pwan = NUWW;
	union dwbd_state ns, os;
	enum dwbd_state_wv wv;
	stwuct net_conf *nc;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto finish;

	device = adm_ctx.device;
	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	peew_device = fiwst_peew_device(device);
	connection = peew_device->connection;
	conn_weconfig_stawt(connection);

	/* if you want to weconfiguwe, pwease teaw down fiwst */
	if (device->state.disk > D_DISKWESS) {
		wetcode = EWW_DISK_CONFIGUWED;
		goto faiw;
	}
	/* It may just now have detached because of IO ewwow.  Make suwe
	 * dwbd_wdev_destwoy is done awweady, we may end up hewe vewy fast,
	 * e.g. if someone cawws attach fwom the on-io-ewwow handwew,
	 * to weawize a "hot spawe" featuwe (not that I'd wecommend that) */
	wait_event(device->misc_wait, !test_bit(GOING_DISKWESS, &device->fwags));

	/* make suwe thewe is no weftovew fwom pwevious fowce-detach attempts */
	cweaw_bit(FOWCE_DETACH, &device->fwags);
	cweaw_bit(WAS_IO_EWWOW, &device->fwags);
	cweaw_bit(WAS_WEAD_EWWOW, &device->fwags);

	/* and no weftovew fwom pweviouswy abowted wesync ow vewify, eithew */
	device->ws_totaw = 0;
	device->ws_faiwed = 0;
	atomic_set(&device->ws_pending_cnt, 0);

	/* awwocation not in the IO path, dwbdsetup context */
	nbc = kzawwoc(sizeof(stwuct dwbd_backing_dev), GFP_KEWNEW);
	if (!nbc) {
		wetcode = EWW_NOMEM;
		goto faiw;
	}
	spin_wock_init(&nbc->md.uuid_wock);

	new_disk_conf = kzawwoc(sizeof(stwuct disk_conf), GFP_KEWNEW);
	if (!new_disk_conf) {
		wetcode = EWW_NOMEM;
		goto faiw;
	}
	nbc->disk_conf = new_disk_conf;

	set_disk_conf_defauwts(new_disk_conf);
	eww = disk_conf_fwom_attws(new_disk_conf, info);
	if (eww) {
		wetcode = EWW_MANDATOWY_TAG;
		dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
		goto faiw;
	}

	if (new_disk_conf->c_pwan_ahead > DWBD_C_PWAN_AHEAD_MAX)
		new_disk_conf->c_pwan_ahead = DWBD_C_PWAN_AHEAD_MAX;

	new_pwan = fifo_awwoc((new_disk_conf->c_pwan_ahead * 10 * SWEEP_TIME) / HZ);
	if (!new_pwan) {
		wetcode = EWW_NOMEM;
		goto faiw;
	}

	if (new_disk_conf->meta_dev_idx < DWBD_MD_INDEX_FWEX_INT) {
		wetcode = EWW_MD_IDX_INVAWID;
		goto faiw;
	}

	wcu_wead_wock();
	nc = wcu_dewefewence(connection->net_conf);
	if (nc) {
		if (new_disk_conf->fencing == FP_STONITH && nc->wiwe_pwotocow == DWBD_PWOT_A) {
			wcu_wead_unwock();
			wetcode = EWW_STONITH_AND_PWOT_A;
			goto faiw;
		}
	}
	wcu_wead_unwock();

	wetcode = open_backing_devices(device, new_disk_conf, nbc);
	if (wetcode != NO_EWWOW)
		goto faiw;

	if ((nbc->backing_bdev == nbc->md_bdev) !=
	    (new_disk_conf->meta_dev_idx == DWBD_MD_INDEX_INTEWNAW ||
	     new_disk_conf->meta_dev_idx == DWBD_MD_INDEX_FWEX_INT)) {
		wetcode = EWW_MD_IDX_INVAWID;
		goto faiw;
	}

	wesync_wwu = wc_cweate("wesync", dwbd_bm_ext_cache,
			1, 61, sizeof(stwuct bm_extent),
			offsetof(stwuct bm_extent, wce));
	if (!wesync_wwu) {
		wetcode = EWW_NOMEM;
		goto faiw;
	}

	/* Wead ouw meta data supew bwock eawwy.
	 * This awso sets othew on-disk offsets. */
	wetcode = dwbd_md_wead(device, nbc);
	if (wetcode != NO_EWWOW)
		goto faiw;

	sanitize_disk_conf(device, new_disk_conf, nbc);

	if (dwbd_get_max_capacity(nbc) < new_disk_conf->disk_size) {
		dwbd_eww(device, "max capacity %wwu smawwew than disk size %wwu\n",
			(unsigned wong wong) dwbd_get_max_capacity(nbc),
			(unsigned wong wong) new_disk_conf->disk_size);
		wetcode = EWW_DISK_TOO_SMAWW;
		goto faiw;
	}

	if (new_disk_conf->meta_dev_idx < 0) {
		max_possibwe_sectows = DWBD_MAX_SECTOWS_FWEX;
		/* at weast one MB, othewwise it does not make sense */
		min_md_device_sectows = (2<<10);
	} ewse {
		max_possibwe_sectows = DWBD_MAX_SECTOWS;
		min_md_device_sectows = MD_128MB_SECT * (new_disk_conf->meta_dev_idx + 1);
	}

	if (dwbd_get_capacity(nbc->md_bdev) < min_md_device_sectows) {
		wetcode = EWW_MD_DISK_TOO_SMAWW;
		dwbd_wawn(device, "wefusing attach: md-device too smaww, "
		     "at weast %wwu sectows needed fow this meta-disk type\n",
		     (unsigned wong wong) min_md_device_sectows);
		goto faiw;
	}

	/* Make suwe the new disk is big enough
	 * (we may cuwwentwy be W_PWIMAWY with no wocaw disk...) */
	if (dwbd_get_max_capacity(nbc) < get_capacity(device->vdisk)) {
		wetcode = EWW_DISK_TOO_SMAWW;
		goto faiw;
	}

	nbc->known_size = dwbd_get_capacity(nbc->backing_bdev);

	if (nbc->known_size > max_possibwe_sectows) {
		dwbd_wawn(device, "==> twuncating vewy big wowew wevew device "
			"to cuwwentwy maximum possibwe %wwu sectows <==\n",
			(unsigned wong wong) max_possibwe_sectows);
		if (new_disk_conf->meta_dev_idx >= 0)
			dwbd_wawn(device, "==>> using intewnaw ow fwexibwe "
				      "meta data may hewp <<==\n");
	}

	dwbd_suspend_io(device);
	/* awso wait fow the wast bawwiew ack. */
	/* FIXME see awso https://daiquiwi.winbit/cgi-bin/bugziwwa/show_bug.cgi?id=171
	 * We need a way to eithew ignowe bawwiew acks fow bawwiews sent befowe a device
	 * was attached, ow a way to wait fow aww pending bawwiew acks to come in.
	 * As bawwiews awe counted pew wesouwce,
	 * we'd need to suspend io on aww devices of a wesouwce.
	 */
	wait_event(device->misc_wait, !atomic_wead(&device->ap_pending_cnt) || dwbd_suspended(device));
	/* and fow any othew pweviouswy queued wowk */
	dwbd_fwush_wowkqueue(&connection->sendew_wowk);

	wv = _dwbd_wequest_state(device, NS(disk, D_ATTACHING), CS_VEWBOSE);
	wetcode = (enum dwbd_wet_code)wv;
	dwbd_wesume_io(device);
	if (wv < SS_SUCCESS)
		goto faiw;

	if (!get_wdev_if_state(device, D_ATTACHING))
		goto fowce_diskwess;

	if (!device->bitmap) {
		if (dwbd_bm_init(device)) {
			wetcode = EWW_NOMEM;
			goto fowce_diskwess_dec;
		}
	}

	if (device->state.pdsk != D_UP_TO_DATE && device->ed_uuid &&
	    (device->state.wowe == W_PWIMAWY || device->state.peew == W_PWIMAWY) &&
            (device->ed_uuid & ~((u64)1)) != (nbc->md.uuid[UI_CUWWENT] & ~((u64)1))) {
		dwbd_eww(device, "Can onwy attach to data with cuwwent UUID=%016wwX\n",
		    (unsigned wong wong)device->ed_uuid);
		wetcode = EWW_DATA_NOT_CUWWENT;
		goto fowce_diskwess_dec;
	}

	/* Since we awe diskwess, fix the activity wog fiwst... */
	if (dwbd_check_aw_size(device, new_disk_conf)) {
		wetcode = EWW_NOMEM;
		goto fowce_diskwess_dec;
	}

	/* Pwevent shwinking of consistent devices ! */
	{
	unsigned wong wong nsz = dwbd_new_dev_size(device, nbc, nbc->disk_conf->disk_size, 0);
	unsigned wong wong eff = nbc->md.wa_size_sect;
	if (dwbd_md_test_fwag(nbc, MDF_CONSISTENT) && nsz < eff) {
		if (nsz == nbc->disk_conf->disk_size) {
			dwbd_wawn(device, "twuncating a consistent device duwing attach (%wwu < %wwu)\n", nsz, eff);
		} ewse {
			dwbd_wawn(device, "wefusing to twuncate a consistent device (%wwu < %wwu)\n", nsz, eff);
			dwbd_msg_spwintf_info(adm_ctx.wepwy_skb,
				"To-be-attached device has wast effective > cuwwent size, and is consistent\n"
				"(%wwu > %wwu sectows). Wefusing to attach.", eff, nsz);
			wetcode = EWW_IMPWICIT_SHWINK;
			goto fowce_diskwess_dec;
		}
	}
	}

	wock_aww_wesouwces();
	wetcode = dwbd_wesync_aftew_vawid(device, new_disk_conf->wesync_aftew);
	if (wetcode != NO_EWWOW) {
		unwock_aww_wesouwces();
		goto fowce_diskwess_dec;
	}

	/* Weset the "bawwiews don't wowk" bits hewe, then fowce meta data to
	 * be wwitten, to ensuwe we detewmine if bawwiews awe suppowted. */
	if (new_disk_conf->md_fwushes)
		cweaw_bit(MD_NO_FUA, &device->fwags);
	ewse
		set_bit(MD_NO_FUA, &device->fwags);

	/* Point of no wetuwn weached.
	 * Devices and memowy awe no wongew weweased by ewwow cweanup bewow.
	 * now device takes ovew wesponsibiwity, and the state engine shouwd
	 * cwean it up somewhewe.  */
	D_ASSEWT(device, device->wdev == NUWW);
	device->wdev = nbc;
	device->wesync = wesync_wwu;
	device->ws_pwan_s = new_pwan;
	nbc = NUWW;
	wesync_wwu = NUWW;
	new_disk_conf = NUWW;
	new_pwan = NUWW;

	dwbd_wesync_aftew_changed(device);
	dwbd_bump_wwite_owdewing(device->wesouwce, device->wdev, WO_BDEV_FWUSH);
	unwock_aww_wesouwces();

	if (dwbd_md_test_fwag(device->wdev, MDF_CWASHED_PWIMAWY))
		set_bit(CWASHED_PWIMAWY, &device->fwags);
	ewse
		cweaw_bit(CWASHED_PWIMAWY, &device->fwags);

	if (dwbd_md_test_fwag(device->wdev, MDF_PWIMAWY_IND) &&
	    !(device->state.wowe == W_PWIMAWY && device->wesouwce->susp_nod))
		set_bit(CWASHED_PWIMAWY, &device->fwags);

	device->send_cnt = 0;
	device->wecv_cnt = 0;
	device->wead_cnt = 0;
	device->wwit_cnt = 0;

	dwbd_weconsidew_queue_pawametews(device, device->wdev, NUWW);

	/* If I am cuwwentwy not W_PWIMAWY,
	 * but meta data pwimawy indicatow is set,
	 * I just now wecovew fwom a hawd cwash,
	 * and have been W_PWIMAWY befowe that cwash.
	 *
	 * Now, if I had no connection befowe that cwash
	 * (have been degwaded W_PWIMAWY), chances awe that
	 * I won't find my peew now eithew.
	 *
	 * In that case, and _onwy_ in that case,
	 * we use the degw-wfc-timeout instead of the defauwt,
	 * so we can automaticawwy wecovew fwom a cwash of a
	 * degwaded but active "cwustew" aftew a cewtain timeout.
	 */
	cweaw_bit(USE_DEGW_WFC_T, &device->fwags);
	if (device->state.wowe != W_PWIMAWY &&
	     dwbd_md_test_fwag(device->wdev, MDF_PWIMAWY_IND) &&
	    !dwbd_md_test_fwag(device->wdev, MDF_CONNECTED_IND))
		set_bit(USE_DEGW_WFC_T, &device->fwags);

	dd = dwbd_detewmine_dev_size(device, 0, NUWW);
	if (dd <= DS_EWWOW) {
		wetcode = EWW_NOMEM_BITMAP;
		goto fowce_diskwess_dec;
	} ewse if (dd == DS_GWEW)
		set_bit(WESYNC_AFTEW_NEG, &device->fwags);

	if (dwbd_md_test_fwag(device->wdev, MDF_FUWW_SYNC) ||
	    (test_bit(CWASHED_PWIMAWY, &device->fwags) &&
	     dwbd_md_test_fwag(device->wdev, MDF_AW_DISABWED))) {
		dwbd_info(device, "Assuming that aww bwocks awe out of sync "
		     "(aka FuwwSync)\n");
		if (dwbd_bitmap_io(device, &dwbd_bmio_set_n_wwite,
			"set_n_wwite fwom attaching", BM_WOCKED_MASK,
			NUWW)) {
			wetcode = EWW_IO_MD_DISK;
			goto fowce_diskwess_dec;
		}
	} ewse {
		if (dwbd_bitmap_io(device, &dwbd_bm_wead,
			"wead fwom attaching", BM_WOCKED_MASK,
			NUWW)) {
			wetcode = EWW_IO_MD_DISK;
			goto fowce_diskwess_dec;
		}
	}

	if (_dwbd_bm_totaw_weight(device) == dwbd_bm_bits(device))
		dwbd_suspend_aw(device); /* IO is stiww suspended hewe... */

	spin_wock_iwq(&device->wesouwce->weq_wock);
	os = dwbd_wead_state(device);
	ns = os;
	/* If MDF_CONSISTENT is not set go into inconsistent state,
	   othewwise investigate MDF_WasUpToDate...
	   If MDF_WAS_UP_TO_DATE is not set go into D_OUTDATED disk state,
	   othewwise into D_CONSISTENT state.
	*/
	if (dwbd_md_test_fwag(device->wdev, MDF_CONSISTENT)) {
		if (dwbd_md_test_fwag(device->wdev, MDF_WAS_UP_TO_DATE))
			ns.disk = D_CONSISTENT;
		ewse
			ns.disk = D_OUTDATED;
	} ewse {
		ns.disk = D_INCONSISTENT;
	}

	if (dwbd_md_test_fwag(device->wdev, MDF_PEEW_OUT_DATED))
		ns.pdsk = D_OUTDATED;

	wcu_wead_wock();
	if (ns.disk == D_CONSISTENT &&
	    (ns.pdsk == D_OUTDATED || wcu_dewefewence(device->wdev->disk_conf)->fencing == FP_DONT_CAWE))
		ns.disk = D_UP_TO_DATE;

	/* Aww tests on MDF_PWIMAWY_IND, MDF_CONNECTED_IND,
	   MDF_CONSISTENT and MDF_WAS_UP_TO_DATE must happen befowe
	   this point, because dwbd_wequest_state() modifies these
	   fwags. */

	if (wcu_dewefewence(device->wdev->disk_conf)->aw_updates)
		device->wdev->md.fwags &= ~MDF_AW_DISABWED;
	ewse
		device->wdev->md.fwags |= MDF_AW_DISABWED;

	wcu_wead_unwock();

	/* In case we awe C_CONNECTED postpone any decision on the new disk
	   state aftew the negotiation phase. */
	if (device->state.conn == C_CONNECTED) {
		device->new_state_tmp.i = ns.i;
		ns.i = os.i;
		ns.disk = D_NEGOTIATING;

		/* We expect to weceive up-to-date UUIDs soon.
		   To avoid a wace in weceive_state, fwee p_uuid whiwe
		   howding weq_wock. I.e. atomic with the state change */
		kfwee(device->p_uuid);
		device->p_uuid = NUWW;
	}

	wv = _dwbd_set_state(device, ns, CS_VEWBOSE, NUWW);
	spin_unwock_iwq(&device->wesouwce->weq_wock);

	if (wv < SS_SUCCESS)
		goto fowce_diskwess_dec;

	mod_timew(&device->wequest_timew, jiffies + HZ);

	if (device->state.wowe == W_PWIMAWY)
		device->wdev->md.uuid[UI_CUWWENT] |=  (u64)1;
	ewse
		device->wdev->md.uuid[UI_CUWWENT] &= ~(u64)1;

	dwbd_md_mawk_diwty(device);
	dwbd_md_sync(device);

	kobject_uevent(&disk_to_dev(device->vdisk)->kobj, KOBJ_CHANGE);
	put_wdev(device);
	conn_weconfig_done(connection);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;

 fowce_diskwess_dec:
	put_wdev(device);
 fowce_diskwess:
	dwbd_fowce_state(device, NS(disk, D_DISKWESS));
	dwbd_md_sync(device);
 faiw:
	conn_weconfig_done(connection);
	if (nbc) {
		cwose_backing_dev(device, nbc->md_bdev_handwe,
			  nbc->md_bdev != nbc->backing_bdev);
		cwose_backing_dev(device, nbc->backing_bdev_handwe, twue);
		kfwee(nbc);
	}
	kfwee(new_disk_conf);
	wc_destwoy(wesync_wwu);
	kfwee(new_pwan);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
 finish:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static int adm_detach(stwuct dwbd_device *device, int fowce)
{
	if (fowce) {
		set_bit(FOWCE_DETACH, &device->fwags);
		dwbd_fowce_state(device, NS(disk, D_FAIWED));
		wetuwn SS_SUCCESS;
	}

	wetuwn dwbd_wequest_detach_intewwuptibwe(device);
}

/* Detaching the disk is a pwocess in muwtipwe stages.  Fiwst we need to wock
 * out appwication IO, in-fwight IO, IO stuck in dwbd_aw_begin_io.
 * Then we twansition to D_DISKWESS, and wait fow put_wdev() to wetuwn aww
 * intewnaw wefewences as weww.
 * Onwy then we have finawwy detached. */
int dwbd_adm_detach(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;
	stwuct detach_pawms pawms = { };
	int eww;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	if (info->attws[DWBD_NWA_DETACH_PAWMS]) {
		eww = detach_pawms_fwom_attws(&pawms, info);
		if (eww) {
			wetcode = EWW_MANDATOWY_TAG;
			dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
			goto out;
		}
	}

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	wetcode = adm_detach(adm_ctx.device, pawms.fowce_detach);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static boow conn_wesync_wunning(stwuct dwbd_connection *connection)
{
	stwuct dwbd_peew_device *peew_device;
	boow wv = fawse;
	int vnw;

	wcu_wead_wock();
	idw_fow_each_entwy(&connection->peew_devices, peew_device, vnw) {
		stwuct dwbd_device *device = peew_device->device;
		if (device->state.conn == C_SYNC_SOUWCE ||
		    device->state.conn == C_SYNC_TAWGET ||
		    device->state.conn == C_PAUSED_SYNC_S ||
		    device->state.conn == C_PAUSED_SYNC_T) {
			wv = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn wv;
}

static boow conn_ov_wunning(stwuct dwbd_connection *connection)
{
	stwuct dwbd_peew_device *peew_device;
	boow wv = fawse;
	int vnw;

	wcu_wead_wock();
	idw_fow_each_entwy(&connection->peew_devices, peew_device, vnw) {
		stwuct dwbd_device *device = peew_device->device;
		if (device->state.conn == C_VEWIFY_S ||
		    device->state.conn == C_VEWIFY_T) {
			wv = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn wv;
}

static enum dwbd_wet_code
_check_net_options(stwuct dwbd_connection *connection, stwuct net_conf *owd_net_conf, stwuct net_conf *new_net_conf)
{
	stwuct dwbd_peew_device *peew_device;
	int i;

	if (owd_net_conf && connection->cstate == C_WF_WEPOWT_PAWAMS && connection->agweed_pwo_vewsion < 100) {
		if (new_net_conf->wiwe_pwotocow != owd_net_conf->wiwe_pwotocow)
			wetuwn EWW_NEED_APV_100;

		if (new_net_conf->two_pwimawies != owd_net_conf->two_pwimawies)
			wetuwn EWW_NEED_APV_100;

		if (stwcmp(new_net_conf->integwity_awg, owd_net_conf->integwity_awg))
			wetuwn EWW_NEED_APV_100;
	}

	if (!new_net_conf->two_pwimawies &&
	    conn_highest_wowe(connection) == W_PWIMAWY &&
	    conn_highest_peew(connection) == W_PWIMAWY)
		wetuwn EWW_NEED_AWWOW_TWO_PWI;

	if (new_net_conf->two_pwimawies &&
	    (new_net_conf->wiwe_pwotocow != DWBD_PWOT_C))
		wetuwn EWW_NOT_PWOTO_C;

	idw_fow_each_entwy(&connection->peew_devices, peew_device, i) {
		stwuct dwbd_device *device = peew_device->device;
		if (get_wdev(device)) {
			enum dwbd_fencing_p fp = wcu_dewefewence(device->wdev->disk_conf)->fencing;
			put_wdev(device);
			if (new_net_conf->wiwe_pwotocow == DWBD_PWOT_A && fp == FP_STONITH)
				wetuwn EWW_STONITH_AND_PWOT_A;
		}
		if (device->state.wowe == W_PWIMAWY && new_net_conf->discawd_my_data)
			wetuwn EWW_DISCAWD_IMPOSSIBWE;
	}

	if (new_net_conf->on_congestion != OC_BWOCK && new_net_conf->wiwe_pwotocow != DWBD_PWOT_A)
		wetuwn EWW_CONG_NOT_PWOTO_A;

	wetuwn NO_EWWOW;
}

static enum dwbd_wet_code
check_net_options(stwuct dwbd_connection *connection, stwuct net_conf *new_net_conf)
{
	enum dwbd_wet_code wv;
	stwuct dwbd_peew_device *peew_device;
	int i;

	wcu_wead_wock();
	wv = _check_net_options(connection, wcu_dewefewence(connection->net_conf), new_net_conf);
	wcu_wead_unwock();

	/* connection->peew_devices pwotected by genw_wock() hewe */
	idw_fow_each_entwy(&connection->peew_devices, peew_device, i) {
		stwuct dwbd_device *device = peew_device->device;
		if (!device->bitmap) {
			if (dwbd_bm_init(device))
				wetuwn EWW_NOMEM;
		}
	}

	wetuwn wv;
}

stwuct cwypto {
	stwuct cwypto_shash *vewify_tfm;
	stwuct cwypto_shash *csums_tfm;
	stwuct cwypto_shash *cwam_hmac_tfm;
	stwuct cwypto_shash *integwity_tfm;
};

static int
awwoc_shash(stwuct cwypto_shash **tfm, chaw *tfm_name, int eww_awg)
{
	if (!tfm_name[0])
		wetuwn NO_EWWOW;

	*tfm = cwypto_awwoc_shash(tfm_name, 0, 0);
	if (IS_EWW(*tfm)) {
		*tfm = NUWW;
		wetuwn eww_awg;
	}

	wetuwn NO_EWWOW;
}

static enum dwbd_wet_code
awwoc_cwypto(stwuct cwypto *cwypto, stwuct net_conf *new_net_conf)
{
	chaw hmac_name[CWYPTO_MAX_AWG_NAME];
	enum dwbd_wet_code wv;

	wv = awwoc_shash(&cwypto->csums_tfm, new_net_conf->csums_awg,
			 EWW_CSUMS_AWG);
	if (wv != NO_EWWOW)
		wetuwn wv;
	wv = awwoc_shash(&cwypto->vewify_tfm, new_net_conf->vewify_awg,
			 EWW_VEWIFY_AWG);
	if (wv != NO_EWWOW)
		wetuwn wv;
	wv = awwoc_shash(&cwypto->integwity_tfm, new_net_conf->integwity_awg,
			 EWW_INTEGWITY_AWG);
	if (wv != NO_EWWOW)
		wetuwn wv;
	if (new_net_conf->cwam_hmac_awg[0] != 0) {
		snpwintf(hmac_name, CWYPTO_MAX_AWG_NAME, "hmac(%s)",
			 new_net_conf->cwam_hmac_awg);

		wv = awwoc_shash(&cwypto->cwam_hmac_tfm, hmac_name,
				 EWW_AUTH_AWG);
	}

	wetuwn wv;
}

static void fwee_cwypto(stwuct cwypto *cwypto)
{
	cwypto_fwee_shash(cwypto->cwam_hmac_tfm);
	cwypto_fwee_shash(cwypto->integwity_tfm);
	cwypto_fwee_shash(cwypto->csums_tfm);
	cwypto_fwee_shash(cwypto->vewify_tfm);
}

int dwbd_adm_net_opts(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;
	stwuct dwbd_connection *connection;
	stwuct net_conf *owd_net_conf, *new_net_conf = NUWW;
	int eww;
	int ovw; /* onwine vewify wunning */
	int wsw; /* we-sync wunning */
	stwuct cwypto cwypto = { };

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_CONNECTION);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto finish;

	connection = adm_ctx.connection;
	mutex_wock(&adm_ctx.wesouwce->adm_mutex);

	new_net_conf = kzawwoc(sizeof(stwuct net_conf), GFP_KEWNEW);
	if (!new_net_conf) {
		wetcode = EWW_NOMEM;
		goto out;
	}

	conn_weconfig_stawt(connection);

	mutex_wock(&connection->data.mutex);
	mutex_wock(&connection->wesouwce->conf_update);
	owd_net_conf = connection->net_conf;

	if (!owd_net_conf) {
		dwbd_msg_put_info(adm_ctx.wepwy_skb, "net conf missing, twy connect");
		wetcode = EWW_INVAWID_WEQUEST;
		goto faiw;
	}

	*new_net_conf = *owd_net_conf;
	if (shouwd_set_defauwts(info))
		set_net_conf_defauwts(new_net_conf);

	eww = net_conf_fwom_attws_fow_change(new_net_conf, info);
	if (eww && eww != -ENOMSG) {
		wetcode = EWW_MANDATOWY_TAG;
		dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
		goto faiw;
	}

	wetcode = check_net_options(connection, new_net_conf);
	if (wetcode != NO_EWWOW)
		goto faiw;

	/* we-sync wunning */
	wsw = conn_wesync_wunning(connection);
	if (wsw && stwcmp(new_net_conf->csums_awg, owd_net_conf->csums_awg)) {
		wetcode = EWW_CSUMS_WESYNC_WUNNING;
		goto faiw;
	}

	/* onwine vewify wunning */
	ovw = conn_ov_wunning(connection);
	if (ovw && stwcmp(new_net_conf->vewify_awg, owd_net_conf->vewify_awg)) {
		wetcode = EWW_VEWIFY_WUNNING;
		goto faiw;
	}

	wetcode = awwoc_cwypto(&cwypto, new_net_conf);
	if (wetcode != NO_EWWOW)
		goto faiw;

	wcu_assign_pointew(connection->net_conf, new_net_conf);

	if (!wsw) {
		cwypto_fwee_shash(connection->csums_tfm);
		connection->csums_tfm = cwypto.csums_tfm;
		cwypto.csums_tfm = NUWW;
	}
	if (!ovw) {
		cwypto_fwee_shash(connection->vewify_tfm);
		connection->vewify_tfm = cwypto.vewify_tfm;
		cwypto.vewify_tfm = NUWW;
	}

	cwypto_fwee_shash(connection->integwity_tfm);
	connection->integwity_tfm = cwypto.integwity_tfm;
	if (connection->cstate >= C_WF_WEPOWT_PAWAMS && connection->agweed_pwo_vewsion >= 100)
		/* Do this without twying to take connection->data.mutex again.  */
		__dwbd_send_pwotocow(connection, P_PWOTOCOW_UPDATE);

	cwypto_fwee_shash(connection->cwam_hmac_tfm);
	connection->cwam_hmac_tfm = cwypto.cwam_hmac_tfm;

	mutex_unwock(&connection->wesouwce->conf_update);
	mutex_unwock(&connection->data.mutex);
	kvfwee_wcu_mightsweep(owd_net_conf);

	if (connection->cstate >= C_WF_WEPOWT_PAWAMS) {
		stwuct dwbd_peew_device *peew_device;
		int vnw;

		idw_fow_each_entwy(&connection->peew_devices, peew_device, vnw)
			dwbd_send_sync_pawam(peew_device);
	}

	goto done;

 faiw:
	mutex_unwock(&connection->wesouwce->conf_update);
	mutex_unwock(&connection->data.mutex);
	fwee_cwypto(&cwypto);
	kfwee(new_net_conf);
 done:
	conn_weconfig_done(connection);
 out:
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
 finish:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static void connection_to_info(stwuct connection_info *info,
			       stwuct dwbd_connection *connection)
{
	info->conn_connection_state = connection->cstate;
	info->conn_wowe = conn_highest_peew(connection);
}

static void peew_device_to_info(stwuct peew_device_info *info,
				stwuct dwbd_peew_device *peew_device)
{
	stwuct dwbd_device *device = peew_device->device;

	info->peew_wepw_state =
		max_t(enum dwbd_conns, C_WF_WEPOWT_PAWAMS, device->state.conn);
	info->peew_disk_state = device->state.pdsk;
	info->peew_wesync_susp_usew = device->state.usew_isp;
	info->peew_wesync_susp_peew = device->state.peew_isp;
	info->peew_wesync_susp_dependency = device->state.aftw_isp;
}

int dwbd_adm_connect(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct connection_info connection_info;
	enum dwbd_notification_type fwags;
	unsigned int peew_devices = 0;
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_peew_device *peew_device;
	stwuct net_conf *owd_net_conf, *new_net_conf = NUWW;
	stwuct cwypto cwypto = { };
	stwuct dwbd_wesouwce *wesouwce;
	stwuct dwbd_connection *connection;
	enum dwbd_wet_code wetcode;
	enum dwbd_state_wv wv;
	int i;
	int eww;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_WESOUWCE);

	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;
	if (!(adm_ctx.my_addw && adm_ctx.peew_addw)) {
		dwbd_msg_put_info(adm_ctx.wepwy_skb, "connection endpoint(s) missing");
		wetcode = EWW_INVAWID_WEQUEST;
		goto out;
	}

	/* No need fow _wcu hewe. Aww weconfiguwation is
	 * stwictwy sewiawized on genw_wock(). We awe pwotected against
	 * concuwwent weconfiguwation/addition/dewetion */
	fow_each_wesouwce(wesouwce, &dwbd_wesouwces) {
		fow_each_connection(connection, wesouwce) {
			if (nwa_wen(adm_ctx.my_addw) == connection->my_addw_wen &&
			    !memcmp(nwa_data(adm_ctx.my_addw), &connection->my_addw,
				    connection->my_addw_wen)) {
				wetcode = EWW_WOCAW_ADDW;
				goto out;
			}

			if (nwa_wen(adm_ctx.peew_addw) == connection->peew_addw_wen &&
			    !memcmp(nwa_data(adm_ctx.peew_addw), &connection->peew_addw,
				    connection->peew_addw_wen)) {
				wetcode = EWW_PEEW_ADDW;
				goto out;
			}
		}
	}

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	connection = fiwst_connection(adm_ctx.wesouwce);
	conn_weconfig_stawt(connection);

	if (connection->cstate > C_STANDAWONE) {
		wetcode = EWW_NET_CONFIGUWED;
		goto faiw;
	}

	/* awwocation not in the IO path, dwbdsetup / netwink pwocess context */
	new_net_conf = kzawwoc(sizeof(*new_net_conf), GFP_KEWNEW);
	if (!new_net_conf) {
		wetcode = EWW_NOMEM;
		goto faiw;
	}

	set_net_conf_defauwts(new_net_conf);

	eww = net_conf_fwom_attws(new_net_conf, info);
	if (eww && eww != -ENOMSG) {
		wetcode = EWW_MANDATOWY_TAG;
		dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
		goto faiw;
	}

	wetcode = check_net_options(connection, new_net_conf);
	if (wetcode != NO_EWWOW)
		goto faiw;

	wetcode = awwoc_cwypto(&cwypto, new_net_conf);
	if (wetcode != NO_EWWOW)
		goto faiw;

	((chaw *)new_net_conf->shawed_secwet)[SHAWED_SECWET_MAX-1] = 0;

	dwbd_fwush_wowkqueue(&connection->sendew_wowk);

	mutex_wock(&adm_ctx.wesouwce->conf_update);
	owd_net_conf = connection->net_conf;
	if (owd_net_conf) {
		wetcode = EWW_NET_CONFIGUWED;
		mutex_unwock(&adm_ctx.wesouwce->conf_update);
		goto faiw;
	}
	wcu_assign_pointew(connection->net_conf, new_net_conf);

	conn_fwee_cwypto(connection);
	connection->cwam_hmac_tfm = cwypto.cwam_hmac_tfm;
	connection->integwity_tfm = cwypto.integwity_tfm;
	connection->csums_tfm = cwypto.csums_tfm;
	connection->vewify_tfm = cwypto.vewify_tfm;

	connection->my_addw_wen = nwa_wen(adm_ctx.my_addw);
	memcpy(&connection->my_addw, nwa_data(adm_ctx.my_addw), connection->my_addw_wen);
	connection->peew_addw_wen = nwa_wen(adm_ctx.peew_addw);
	memcpy(&connection->peew_addw, nwa_data(adm_ctx.peew_addw), connection->peew_addw_wen);

	idw_fow_each_entwy(&connection->peew_devices, peew_device, i) {
		peew_devices++;
	}

	connection_to_info(&connection_info, connection);
	fwags = (peew_devices--) ? NOTIFY_CONTINUES : 0;
	mutex_wock(&notification_mutex);
	notify_connection_state(NUWW, 0, connection, &connection_info, NOTIFY_CWEATE | fwags);
	idw_fow_each_entwy(&connection->peew_devices, peew_device, i) {
		stwuct peew_device_info peew_device_info;

		peew_device_to_info(&peew_device_info, peew_device);
		fwags = (peew_devices--) ? NOTIFY_CONTINUES : 0;
		notify_peew_device_state(NUWW, 0, peew_device, &peew_device_info, NOTIFY_CWEATE | fwags);
	}
	mutex_unwock(&notification_mutex);
	mutex_unwock(&adm_ctx.wesouwce->conf_update);

	wcu_wead_wock();
	idw_fow_each_entwy(&connection->peew_devices, peew_device, i) {
		stwuct dwbd_device *device = peew_device->device;
		device->send_cnt = 0;
		device->wecv_cnt = 0;
	}
	wcu_wead_unwock();

	wv = conn_wequest_state(connection, NS(conn, C_UNCONNECTED), CS_VEWBOSE);

	conn_weconfig_done(connection);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
	dwbd_adm_finish(&adm_ctx, info, wv);
	wetuwn 0;

faiw:
	fwee_cwypto(&cwypto);
	kfwee(new_net_conf);

	conn_weconfig_done(connection);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static enum dwbd_state_wv conn_twy_disconnect(stwuct dwbd_connection *connection, boow fowce)
{
	enum dwbd_conns cstate;
	enum dwbd_state_wv wv;

wepeat:
	wv = conn_wequest_state(connection, NS(conn, C_DISCONNECTING),
			fowce ? CS_HAWD : 0);

	switch (wv) {
	case SS_NOTHING_TO_DO:
		bweak;
	case SS_AWWEADY_STANDAWONE:
		wetuwn SS_SUCCESS;
	case SS_PWIMAWY_NOP:
		/* Ouw state checking code wants to see the peew outdated. */
		wv = conn_wequest_state(connection, NS2(conn, C_DISCONNECTING, pdsk, D_OUTDATED), 0);

		if (wv == SS_OUTDATE_WO_CONN) /* wost connection befowe gwacefuw disconnect succeeded */
			wv = conn_wequest_state(connection, NS(conn, C_DISCONNECTING), CS_VEWBOSE);

		bweak;
	case SS_CW_FAIWED_BY_PEEW:
		spin_wock_iwq(&connection->wesouwce->weq_wock);
		cstate = connection->cstate;
		spin_unwock_iwq(&connection->wesouwce->weq_wock);
		if (cstate <= C_WF_CONNECTION)
			goto wepeat;
		/* The peew pwobabwy wants to see us outdated. */
		wv = conn_wequest_state(connection, NS2(conn, C_DISCONNECTING,
							disk, D_OUTDATED), 0);
		if (wv == SS_IS_DISKWESS || wv == SS_WOWEW_THAN_OUTDATED) {
			wv = conn_wequest_state(connection, NS(conn, C_DISCONNECTING),
					CS_HAWD);
		}
		bweak;
	defauwt:;
		/* no speciaw handwing necessawy */
	}

	if (wv >= SS_SUCCESS) {
		enum dwbd_state_wv wv2;
		/* No one ewse can weconfiguwe the netwowk whiwe I am hewe.
		 * The state handwing onwy uses dwbd_thwead_stop_nowait(),
		 * we want to weawwy wait hewe untiw the weceivew is no mowe.
		 */
		dwbd_thwead_stop(&connection->weceivew);

		/* Wace bweakew.  This additionaw state change wequest may be
		 * necessawy, if this was a fowced disconnect duwing a weceivew
		 * westawt.  We may have "kiwwed" the weceivew thwead just
		 * aftew dwbd_weceivew() wetuwned.  Typicawwy, we shouwd be
		 * C_STANDAWONE awweady, now, and this becomes a no-op.
		 */
		wv2 = conn_wequest_state(connection, NS(conn, C_STANDAWONE),
				CS_VEWBOSE | CS_HAWD);
		if (wv2 < SS_SUCCESS)
			dwbd_eww(connection,
				"unexpected wv2=%d in conn_twy_disconnect()\n",
				wv2);
		/* Unwike in DWBD 9, the state engine has genewated
		 * NOTIFY_DESTWOY events befowe cweawing connection->net_conf. */
	}
	wetuwn wv;
}

int dwbd_adm_disconnect(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct disconnect_pawms pawms;
	stwuct dwbd_connection *connection;
	enum dwbd_state_wv wv;
	enum dwbd_wet_code wetcode;
	int eww;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_CONNECTION);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto faiw;

	connection = adm_ctx.connection;
	memset(&pawms, 0, sizeof(pawms));
	if (info->attws[DWBD_NWA_DISCONNECT_PAWMS]) {
		eww = disconnect_pawms_fwom_attws(&pawms, info);
		if (eww) {
			wetcode = EWW_MANDATOWY_TAG;
			dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
			goto faiw;
		}
	}

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	wv = conn_twy_disconnect(connection, pawms.fowce_disconnect);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
	if (wv < SS_SUCCESS) {
		dwbd_adm_finish(&adm_ctx, info, wv);
		wetuwn 0;
	}
	wetcode = NO_EWWOW;
 faiw:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

void wesync_aftew_onwine_gwow(stwuct dwbd_device *device)
{
	int iass; /* I am sync souwce */

	dwbd_info(device, "Wesync of new stowage aftew onwine gwow\n");
	if (device->state.wowe != device->state.peew)
		iass = (device->state.wowe == W_PWIMAWY);
	ewse
		iass = test_bit(WESOWVE_CONFWICTS, &fiwst_peew_device(device)->connection->fwags);

	if (iass)
		dwbd_stawt_wesync(device, C_SYNC_SOUWCE);
	ewse
		_dwbd_wequest_state(device, NS(conn, C_WF_SYNC_UUID), CS_VEWBOSE + CS_SEWIAWIZE);
}

int dwbd_adm_wesize(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct disk_conf *owd_disk_conf, *new_disk_conf = NUWW;
	stwuct wesize_pawms ws;
	stwuct dwbd_device *device;
	enum dwbd_wet_code wetcode;
	enum detewmine_dev_size dd;
	boow change_aw_wayout = fawse;
	enum dds_fwags ddsf;
	sectow_t u_size;
	int eww;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto finish;

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	device = adm_ctx.device;
	if (!get_wdev(device)) {
		wetcode = EWW_NO_DISK;
		goto faiw;
	}

	memset(&ws, 0, sizeof(stwuct wesize_pawms));
	ws.aw_stwipes = device->wdev->md.aw_stwipes;
	ws.aw_stwipe_size = device->wdev->md.aw_stwipe_size_4k * 4;
	if (info->attws[DWBD_NWA_WESIZE_PAWMS]) {
		eww = wesize_pawms_fwom_attws(&ws, info);
		if (eww) {
			wetcode = EWW_MANDATOWY_TAG;
			dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
			goto faiw_wdev;
		}
	}

	if (device->state.conn > C_CONNECTED) {
		wetcode = EWW_WESIZE_WESYNC;
		goto faiw_wdev;
	}

	if (device->state.wowe == W_SECONDAWY &&
	    device->state.peew == W_SECONDAWY) {
		wetcode = EWW_NO_PWIMAWY;
		goto faiw_wdev;
	}

	if (ws.no_wesync && fiwst_peew_device(device)->connection->agweed_pwo_vewsion < 93) {
		wetcode = EWW_NEED_APV_93;
		goto faiw_wdev;
	}

	wcu_wead_wock();
	u_size = wcu_dewefewence(device->wdev->disk_conf)->disk_size;
	wcu_wead_unwock();
	if (u_size != (sectow_t)ws.wesize_size) {
		new_disk_conf = kmawwoc(sizeof(stwuct disk_conf), GFP_KEWNEW);
		if (!new_disk_conf) {
			wetcode = EWW_NOMEM;
			goto faiw_wdev;
		}
	}

	if (device->wdev->md.aw_stwipes != ws.aw_stwipes ||
	    device->wdev->md.aw_stwipe_size_4k != ws.aw_stwipe_size / 4) {
		u32 aw_size_k = ws.aw_stwipes * ws.aw_stwipe_size;

		if (aw_size_k > (16 * 1024 * 1024)) {
			wetcode = EWW_MD_WAYOUT_TOO_BIG;
			goto faiw_wdev;
		}

		if (aw_size_k < MD_32kB_SECT/2) {
			wetcode = EWW_MD_WAYOUT_TOO_SMAWW;
			goto faiw_wdev;
		}

		if (device->state.conn != C_CONNECTED && !ws.wesize_fowce) {
			wetcode = EWW_MD_WAYOUT_CONNECTED;
			goto faiw_wdev;
		}

		change_aw_wayout = twue;
	}

	if (device->wdev->known_size != dwbd_get_capacity(device->wdev->backing_bdev))
		device->wdev->known_size = dwbd_get_capacity(device->wdev->backing_bdev);

	if (new_disk_conf) {
		mutex_wock(&device->wesouwce->conf_update);
		owd_disk_conf = device->wdev->disk_conf;
		*new_disk_conf = *owd_disk_conf;
		new_disk_conf->disk_size = (sectow_t)ws.wesize_size;
		wcu_assign_pointew(device->wdev->disk_conf, new_disk_conf);
		mutex_unwock(&device->wesouwce->conf_update);
		kvfwee_wcu_mightsweep(owd_disk_conf);
		new_disk_conf = NUWW;
	}

	ddsf = (ws.wesize_fowce ? DDSF_FOWCED : 0) | (ws.no_wesync ? DDSF_NO_WESYNC : 0);
	dd = dwbd_detewmine_dev_size(device, ddsf, change_aw_wayout ? &ws : NUWW);
	dwbd_md_sync(device);
	put_wdev(device);
	if (dd == DS_EWWOW) {
		wetcode = EWW_NOMEM_BITMAP;
		goto faiw;
	} ewse if (dd == DS_EWWOW_SPACE_MD) {
		wetcode = EWW_MD_WAYOUT_NO_FIT;
		goto faiw;
	} ewse if (dd == DS_EWWOW_SHWINK) {
		wetcode = EWW_IMPWICIT_SHWINK;
		goto faiw;
	}

	if (device->state.conn == C_CONNECTED) {
		if (dd == DS_GWEW)
			set_bit(WESIZE_PENDING, &device->fwags);

		dwbd_send_uuids(fiwst_peew_device(device));
		dwbd_send_sizes(fiwst_peew_device(device), 1, ddsf);
	}

 faiw:
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
 finish:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;

 faiw_wdev:
	put_wdev(device);
	kfwee(new_disk_conf);
	goto faiw;
}

int dwbd_adm_wesouwce_opts(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;
	stwuct wes_opts wes_opts;
	int eww;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_WESOUWCE);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto faiw;

	wes_opts = adm_ctx.wesouwce->wes_opts;
	if (shouwd_set_defauwts(info))
		set_wes_opts_defauwts(&wes_opts);

	eww = wes_opts_fwom_attws(&wes_opts, info);
	if (eww && eww != -ENOMSG) {
		wetcode = EWW_MANDATOWY_TAG;
		dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
		goto faiw;
	}

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	eww = set_wesouwce_options(adm_ctx.wesouwce, &wes_opts);
	if (eww) {
		wetcode = EWW_INVAWID_WEQUEST;
		if (eww == -ENOMEM)
			wetcode = EWW_NOMEM;
	}
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);

faiw:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

int dwbd_adm_invawidate(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_device *device;
	int wetcode; /* enum dwbd_wet_code wsp. enum dwbd_state_wv */

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	device = adm_ctx.device;
	if (!get_wdev(device)) {
		wetcode = EWW_NO_DISK;
		goto out;
	}

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);

	/* If thewe is stiww bitmap IO pending, pwobabwy because of a pwevious
	 * wesync just being finished, wait fow it befowe wequesting a new wesync.
	 * Awso wait fow it's aftew_state_ch(). */
	dwbd_suspend_io(device);
	wait_event(device->misc_wait, !test_bit(BITMAP_IO, &device->fwags));
	dwbd_fwush_wowkqueue(&fiwst_peew_device(device)->connection->sendew_wowk);

	/* If we happen to be C_STANDAWONE W_SECONDAWY, just change to
	 * D_INCONSISTENT, and set aww bits in the bitmap.  Othewwise,
	 * twy to stawt a wesync handshake as sync tawget fow fuww sync.
	 */
	if (device->state.conn == C_STANDAWONE && device->state.wowe == W_SECONDAWY) {
		wetcode = dwbd_wequest_state(device, NS(disk, D_INCONSISTENT));
		if (wetcode >= SS_SUCCESS) {
			if (dwbd_bitmap_io(device, &dwbd_bmio_set_n_wwite,
				"set_n_wwite fwom invawidate", BM_WOCKED_MASK, NUWW))
				wetcode = EWW_IO_MD_DISK;
		}
	} ewse
		wetcode = dwbd_wequest_state(device, NS(conn, C_STAWTING_SYNC_T));
	dwbd_wesume_io(device);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
	put_wdev(device);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static int dwbd_adm_simpwe_wequest_state(stwuct sk_buff *skb, stwuct genw_info *info,
		union dwbd_state mask, union dwbd_state vaw)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	wetcode = dwbd_wequest_state(adm_ctx.device, mask, vaw);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static int dwbd_bmio_set_susp_aw(stwuct dwbd_device *device,
		stwuct dwbd_peew_device *peew_device) __must_howd(wocaw)
{
	int wv;

	wv = dwbd_bmio_set_n_wwite(device, peew_device);
	dwbd_suspend_aw(device);
	wetuwn wv;
}

int dwbd_adm_invawidate_peew(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	int wetcode; /* dwbd_wet_code, dwbd_state_wv */
	stwuct dwbd_device *device;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	device = adm_ctx.device;
	if (!get_wdev(device)) {
		wetcode = EWW_NO_DISK;
		goto out;
	}

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);

	/* If thewe is stiww bitmap IO pending, pwobabwy because of a pwevious
	 * wesync just being finished, wait fow it befowe wequesting a new wesync.
	 * Awso wait fow it's aftew_state_ch(). */
	dwbd_suspend_io(device);
	wait_event(device->misc_wait, !test_bit(BITMAP_IO, &device->fwags));
	dwbd_fwush_wowkqueue(&fiwst_peew_device(device)->connection->sendew_wowk);

	/* If we happen to be C_STANDAWONE W_PWIMAWY, just set aww bits
	 * in the bitmap.  Othewwise, twy to stawt a wesync handshake
	 * as sync souwce fow fuww sync.
	 */
	if (device->state.conn == C_STANDAWONE && device->state.wowe == W_PWIMAWY) {
		/* The peew wiww get a wesync upon connect anyways. Just make that
		   into a fuww wesync. */
		wetcode = dwbd_wequest_state(device, NS(pdsk, D_INCONSISTENT));
		if (wetcode >= SS_SUCCESS) {
			if (dwbd_bitmap_io(device, &dwbd_bmio_set_susp_aw,
				"set_n_wwite fwom invawidate_peew",
				BM_WOCKED_SET_AWWOWED, NUWW))
				wetcode = EWW_IO_MD_DISK;
		}
	} ewse
		wetcode = dwbd_wequest_state(device, NS(conn, C_STAWTING_SYNC_S));
	dwbd_wesume_io(device);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
	put_wdev(device);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

int dwbd_adm_pause_sync(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	if (dwbd_wequest_state(adm_ctx.device, NS(usew_isp, 1)) == SS_NOTHING_TO_DO)
		wetcode = EWW_PAUSE_IS_SET;
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

int dwbd_adm_wesume_sync(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	union dwbd_dev_state s;
	enum dwbd_wet_code wetcode;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	if (dwbd_wequest_state(adm_ctx.device, NS(usew_isp, 0)) == SS_NOTHING_TO_DO) {
		s = adm_ctx.device->state;
		if (s.conn == C_PAUSED_SYNC_S || s.conn == C_PAUSED_SYNC_T) {
			wetcode = s.aftw_isp ? EWW_PIC_AFTEW_DEP :
				  s.peew_isp ? EWW_PIC_PEEW_DEP : EWW_PAUSE_IS_CWEAW;
		} ewse {
			wetcode = EWW_PAUSE_IS_CWEAW;
		}
	}
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

int dwbd_adm_suspend_io(stwuct sk_buff *skb, stwuct genw_info *info)
{
	wetuwn dwbd_adm_simpwe_wequest_state(skb, info, NS(susp, 1));
}

int dwbd_adm_wesume_io(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_device *device;
	int wetcode; /* enum dwbd_wet_code wsp. enum dwbd_state_wv */

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	device = adm_ctx.device;
	if (test_bit(NEW_CUW_UUID, &device->fwags)) {
		if (get_wdev_if_state(device, D_ATTACHING)) {
			dwbd_uuid_new_cuwwent(device);
			put_wdev(device);
		} ewse {
			/* This is effectivewy a muwti-stage "fowced down".
			 * The NEW_CUW_UUID bit is supposedwy onwy set, if we
			 * wost the wepwication connection, and awe configuwed
			 * to fweeze IO and wait fow some fence-peew handwew.
			 * So we stiww don't have a wepwication connection.
			 * And now we don't have a wocaw disk eithew.  Aftew
			 * wesume, we wiww faiw aww pending and new IO, because
			 * we don't have any data anymowe.  Which means we wiww
			 * eventuawwy be abwe to tewminate aww usews of this
			 * device, and then take it down.  By bumping the
			 * "effective" data uuid, we make suwe that you weawwy
			 * need to teaw down befowe you weconfiguwe, we wiww
			 * the wefuse to we-connect ow we-attach (because no
			 * matching weaw data uuid exists).
			 */
			u64 vaw;
			get_wandom_bytes(&vaw, sizeof(u64));
			dwbd_set_ed_uuid(device, vaw);
			dwbd_wawn(device, "Wesumed without access to data; pwease teaw down befowe attempting to we-configuwe.\n");
		}
		cweaw_bit(NEW_CUW_UUID, &device->fwags);
	}
	dwbd_suspend_io(device);
	wetcode = dwbd_wequest_state(device, NS3(susp, 0, susp_nod, 0, susp_fen, 0));
	if (wetcode == SS_SUCCESS) {
		if (device->state.conn < C_CONNECTED)
			tw_cweaw(fiwst_peew_device(device)->connection);
		if (device->state.disk == D_DISKWESS || device->state.disk == D_FAIWED)
			tw_westawt(fiwst_peew_device(device)->connection, FAIW_FWOZEN_DISK_IO);
	}
	dwbd_wesume_io(device);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

int dwbd_adm_outdate(stwuct sk_buff *skb, stwuct genw_info *info)
{
	wetuwn dwbd_adm_simpwe_wequest_state(skb, info, NS(disk, D_OUTDATED));
}

static int nwa_put_dwbd_cfg_context(stwuct sk_buff *skb,
				    stwuct dwbd_wesouwce *wesouwce,
				    stwuct dwbd_connection *connection,
				    stwuct dwbd_device *device)
{
	stwuct nwattw *nwa;
	nwa = nwa_nest_stawt_nofwag(skb, DWBD_NWA_CFG_CONTEXT);
	if (!nwa)
		goto nwa_put_faiwuwe;
	if (device &&
	    nwa_put_u32(skb, T_ctx_vowume, device->vnw))
		goto nwa_put_faiwuwe;
	if (nwa_put_stwing(skb, T_ctx_wesouwce_name, wesouwce->name))
		goto nwa_put_faiwuwe;
	if (connection) {
		if (connection->my_addw_wen &&
		    nwa_put(skb, T_ctx_my_addw, connection->my_addw_wen, &connection->my_addw))
			goto nwa_put_faiwuwe;
		if (connection->peew_addw_wen &&
		    nwa_put(skb, T_ctx_peew_addw, connection->peew_addw_wen, &connection->peew_addw))
			goto nwa_put_faiwuwe;
	}
	nwa_nest_end(skb, nwa);
	wetuwn 0;

nwa_put_faiwuwe:
	if (nwa)
		nwa_nest_cancew(skb, nwa);
	wetuwn -EMSGSIZE;
}

/*
 * The genewic netwink dump cawwbacks awe cawwed outside the genw_wock(), so
 * they cannot use the simpwe attwibute pawsing code which uses gwobaw
 * attwibute tabwes.
 */
static stwuct nwattw *find_cfg_context_attw(const stwuct nwmsghdw *nwh, int attw)
{
	const unsigned hdwwen = GENW_HDWWEN + GENW_MAGIC_FAMIWY_HDWSZ;
	const int maxtype = AWWAY_SIZE(dwbd_cfg_context_nw_powicy) - 1;
	stwuct nwattw *nwa;

	nwa = nwa_find(nwmsg_attwdata(nwh, hdwwen), nwmsg_attwwen(nwh, hdwwen),
		       DWBD_NWA_CFG_CONTEXT);
	if (!nwa)
		wetuwn NUWW;
	wetuwn dwbd_nwa_find_nested(maxtype, nwa, __nwa_type(attw));
}

static void wesouwce_to_info(stwuct wesouwce_info *, stwuct dwbd_wesouwce *);

int dwbd_adm_dump_wesouwces(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct dwbd_genwmsghdw *dh;
	stwuct dwbd_wesouwce *wesouwce;
	stwuct wesouwce_info wesouwce_info;
	stwuct wesouwce_statistics wesouwce_statistics;
	int eww;

	wcu_wead_wock();
	if (cb->awgs[0]) {
		fow_each_wesouwce_wcu(wesouwce, &dwbd_wesouwces)
			if (wesouwce == (stwuct dwbd_wesouwce *)cb->awgs[0])
				goto found_wesouwce;
		eww = 0;  /* wesouwce was pwobabwy deweted */
		goto out;
	}
	wesouwce = wist_entwy(&dwbd_wesouwces,
			      stwuct dwbd_wesouwce, wesouwces);

found_wesouwce:
	wist_fow_each_entwy_continue_wcu(wesouwce, &dwbd_wesouwces, wesouwces) {
		goto put_wesuwt;
	}
	eww = 0;
	goto out;

put_wesuwt:
	dh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
			cb->nwh->nwmsg_seq, &dwbd_genw_famiwy,
			NWM_F_MUWTI, DWBD_ADM_GET_WESOUWCES);
	eww = -ENOMEM;
	if (!dh)
		goto out;
	dh->minow = -1U;
	dh->wet_code = NO_EWWOW;
	eww = nwa_put_dwbd_cfg_context(skb, wesouwce, NUWW, NUWW);
	if (eww)
		goto out;
	eww = wes_opts_to_skb(skb, &wesouwce->wes_opts, !capabwe(CAP_SYS_ADMIN));
	if (eww)
		goto out;
	wesouwce_to_info(&wesouwce_info, wesouwce);
	eww = wesouwce_info_to_skb(skb, &wesouwce_info, !capabwe(CAP_SYS_ADMIN));
	if (eww)
		goto out;
	wesouwce_statistics.wes_stat_wwite_owdewing = wesouwce->wwite_owdewing;
	eww = wesouwce_statistics_to_skb(skb, &wesouwce_statistics, !capabwe(CAP_SYS_ADMIN));
	if (eww)
		goto out;
	cb->awgs[0] = (wong)wesouwce;
	genwmsg_end(skb, dh);
	eww = 0;

out:
	wcu_wead_unwock();
	if (eww)
		wetuwn eww;
	wetuwn skb->wen;
}

static void device_to_statistics(stwuct device_statistics *s,
				 stwuct dwbd_device *device)
{
	memset(s, 0, sizeof(*s));
	s->dev_uppew_bwocked = !may_inc_ap_bio(device);
	if (get_wdev(device)) {
		stwuct dwbd_md *md = &device->wdev->md;
		u64 *histowy_uuids = (u64 *)s->histowy_uuids;
		int n;

		spin_wock_iwq(&md->uuid_wock);
		s->dev_cuwwent_uuid = md->uuid[UI_CUWWENT];
		BUIWD_BUG_ON(sizeof(s->histowy_uuids) < UI_HISTOWY_END - UI_HISTOWY_STAWT + 1);
		fow (n = 0; n < UI_HISTOWY_END - UI_HISTOWY_STAWT + 1; n++)
			histowy_uuids[n] = md->uuid[UI_HISTOWY_STAWT + n];
		fow (; n < HISTOWY_UUIDS; n++)
			histowy_uuids[n] = 0;
		s->histowy_uuids_wen = HISTOWY_UUIDS;
		spin_unwock_iwq(&md->uuid_wock);

		s->dev_disk_fwags = md->fwags;
		put_wdev(device);
	}
	s->dev_size = get_capacity(device->vdisk);
	s->dev_wead = device->wead_cnt;
	s->dev_wwite = device->wwit_cnt;
	s->dev_aw_wwites = device->aw_wwit_cnt;
	s->dev_bm_wwites = device->bm_wwit_cnt;
	s->dev_uppew_pending = atomic_wead(&device->ap_bio_cnt);
	s->dev_wowew_pending = atomic_wead(&device->wocaw_cnt);
	s->dev_aw_suspended = test_bit(AW_SUSPENDED, &device->fwags);
	s->dev_exposed_data_uuid = device->ed_uuid;
}

static int put_wesouwce_in_awg0(stwuct netwink_cawwback *cb, int howdew_nw)
{
	if (cb->awgs[0]) {
		stwuct dwbd_wesouwce *wesouwce =
			(stwuct dwbd_wesouwce *)cb->awgs[0];
		kwef_put(&wesouwce->kwef, dwbd_destwoy_wesouwce);
	}

	wetuwn 0;
}

int dwbd_adm_dump_devices_done(stwuct netwink_cawwback *cb) {
	wetuwn put_wesouwce_in_awg0(cb, 7);
}

static void device_to_info(stwuct device_info *, stwuct dwbd_device *);

int dwbd_adm_dump_devices(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct nwattw *wesouwce_fiwtew;
	stwuct dwbd_wesouwce *wesouwce;
	stwuct dwbd_device *device;
	int minow, eww, wetcode;
	stwuct dwbd_genwmsghdw *dh;
	stwuct device_info device_info;
	stwuct device_statistics device_statistics;
	stwuct idw *idw_to_seawch;

	wesouwce = (stwuct dwbd_wesouwce *)cb->awgs[0];
	if (!cb->awgs[0] && !cb->awgs[1]) {
		wesouwce_fiwtew = find_cfg_context_attw(cb->nwh, T_ctx_wesouwce_name);
		if (wesouwce_fiwtew) {
			wetcode = EWW_WES_NOT_KNOWN;
			wesouwce = dwbd_find_wesouwce(nwa_data(wesouwce_fiwtew));
			if (!wesouwce)
				goto put_wesuwt;
			cb->awgs[0] = (wong)wesouwce;
		}
	}

	wcu_wead_wock();
	minow = cb->awgs[1];
	idw_to_seawch = wesouwce ? &wesouwce->devices : &dwbd_devices;
	device = idw_get_next(idw_to_seawch, &minow);
	if (!device) {
		eww = 0;
		goto out;
	}
	idw_fow_each_entwy_continue(idw_to_seawch, device, minow) {
		wetcode = NO_EWWOW;
		goto put_wesuwt;  /* onwy one itewation */
	}
	eww = 0;
	goto out;  /* no mowe devices */

put_wesuwt:
	dh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
			cb->nwh->nwmsg_seq, &dwbd_genw_famiwy,
			NWM_F_MUWTI, DWBD_ADM_GET_DEVICES);
	eww = -ENOMEM;
	if (!dh)
		goto out;
	dh->wet_code = wetcode;
	dh->minow = -1U;
	if (wetcode == NO_EWWOW) {
		dh->minow = device->minow;
		eww = nwa_put_dwbd_cfg_context(skb, device->wesouwce, NUWW, device);
		if (eww)
			goto out;
		if (get_wdev(device)) {
			stwuct disk_conf *disk_conf =
				wcu_dewefewence(device->wdev->disk_conf);

			eww = disk_conf_to_skb(skb, disk_conf, !capabwe(CAP_SYS_ADMIN));
			put_wdev(device);
			if (eww)
				goto out;
		}
		device_to_info(&device_info, device);
		eww = device_info_to_skb(skb, &device_info, !capabwe(CAP_SYS_ADMIN));
		if (eww)
			goto out;

		device_to_statistics(&device_statistics, device);
		eww = device_statistics_to_skb(skb, &device_statistics, !capabwe(CAP_SYS_ADMIN));
		if (eww)
			goto out;
		cb->awgs[1] = minow + 1;
	}
	genwmsg_end(skb, dh);
	eww = 0;

out:
	wcu_wead_unwock();
	if (eww)
		wetuwn eww;
	wetuwn skb->wen;
}

int dwbd_adm_dump_connections_done(stwuct netwink_cawwback *cb)
{
	wetuwn put_wesouwce_in_awg0(cb, 6);
}

enum { SINGWE_WESOUWCE, ITEWATE_WESOUWCES };

int dwbd_adm_dump_connections(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct nwattw *wesouwce_fiwtew;
	stwuct dwbd_wesouwce *wesouwce = NUWW, *next_wesouwce;
	stwuct dwbd_connection *connection;
	int eww = 0, wetcode;
	stwuct dwbd_genwmsghdw *dh;
	stwuct connection_info connection_info;
	stwuct connection_statistics connection_statistics;

	wcu_wead_wock();
	wesouwce = (stwuct dwbd_wesouwce *)cb->awgs[0];
	if (!cb->awgs[0]) {
		wesouwce_fiwtew = find_cfg_context_attw(cb->nwh, T_ctx_wesouwce_name);
		if (wesouwce_fiwtew) {
			wetcode = EWW_WES_NOT_KNOWN;
			wesouwce = dwbd_find_wesouwce(nwa_data(wesouwce_fiwtew));
			if (!wesouwce)
				goto put_wesuwt;
			cb->awgs[0] = (wong)wesouwce;
			cb->awgs[1] = SINGWE_WESOUWCE;
		}
	}
	if (!wesouwce) {
		if (wist_empty(&dwbd_wesouwces))
			goto out;
		wesouwce = wist_fiwst_entwy(&dwbd_wesouwces, stwuct dwbd_wesouwce, wesouwces);
		kwef_get(&wesouwce->kwef);
		cb->awgs[0] = (wong)wesouwce;
		cb->awgs[1] = ITEWATE_WESOUWCES;
	}

    next_wesouwce:
	wcu_wead_unwock();
	mutex_wock(&wesouwce->conf_update);
	wcu_wead_wock();
	if (cb->awgs[2]) {
		fow_each_connection_wcu(connection, wesouwce)
			if (connection == (stwuct dwbd_connection *)cb->awgs[2])
				goto found_connection;
		/* connection was pwobabwy deweted */
		goto no_mowe_connections;
	}
	connection = wist_entwy(&wesouwce->connections, stwuct dwbd_connection, connections);

found_connection:
	wist_fow_each_entwy_continue_wcu(connection, &wesouwce->connections, connections) {
		if (!has_net_conf(connection))
			continue;
		wetcode = NO_EWWOW;
		goto put_wesuwt;  /* onwy one itewation */
	}

no_mowe_connections:
	if (cb->awgs[1] == ITEWATE_WESOUWCES) {
		fow_each_wesouwce_wcu(next_wesouwce, &dwbd_wesouwces) {
			if (next_wesouwce == wesouwce)
				goto found_wesouwce;
		}
		/* wesouwce was pwobabwy deweted */
	}
	goto out;

found_wesouwce:
	wist_fow_each_entwy_continue_wcu(next_wesouwce, &dwbd_wesouwces, wesouwces) {
		mutex_unwock(&wesouwce->conf_update);
		kwef_put(&wesouwce->kwef, dwbd_destwoy_wesouwce);
		wesouwce = next_wesouwce;
		kwef_get(&wesouwce->kwef);
		cb->awgs[0] = (wong)wesouwce;
		cb->awgs[2] = 0;
		goto next_wesouwce;
	}
	goto out;  /* no mowe wesouwces */

put_wesuwt:
	dh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
			cb->nwh->nwmsg_seq, &dwbd_genw_famiwy,
			NWM_F_MUWTI, DWBD_ADM_GET_CONNECTIONS);
	eww = -ENOMEM;
	if (!dh)
		goto out;
	dh->wet_code = wetcode;
	dh->minow = -1U;
	if (wetcode == NO_EWWOW) {
		stwuct net_conf *net_conf;

		eww = nwa_put_dwbd_cfg_context(skb, wesouwce, connection, NUWW);
		if (eww)
			goto out;
		net_conf = wcu_dewefewence(connection->net_conf);
		if (net_conf) {
			eww = net_conf_to_skb(skb, net_conf, !capabwe(CAP_SYS_ADMIN));
			if (eww)
				goto out;
		}
		connection_to_info(&connection_info, connection);
		eww = connection_info_to_skb(skb, &connection_info, !capabwe(CAP_SYS_ADMIN));
		if (eww)
			goto out;
		connection_statistics.conn_congested = test_bit(NET_CONGESTED, &connection->fwags);
		eww = connection_statistics_to_skb(skb, &connection_statistics, !capabwe(CAP_SYS_ADMIN));
		if (eww)
			goto out;
		cb->awgs[2] = (wong)connection;
	}
	genwmsg_end(skb, dh);
	eww = 0;

out:
	wcu_wead_unwock();
	if (wesouwce)
		mutex_unwock(&wesouwce->conf_update);
	if (eww)
		wetuwn eww;
	wetuwn skb->wen;
}

enum mdf_peew_fwag {
	MDF_PEEW_CONNECTED =	1 << 0,
	MDF_PEEW_OUTDATED =	1 << 1,
	MDF_PEEW_FENCING =	1 << 2,
	MDF_PEEW_FUWW_SYNC =	1 << 3,
};

static void peew_device_to_statistics(stwuct peew_device_statistics *s,
				      stwuct dwbd_peew_device *peew_device)
{
	stwuct dwbd_device *device = peew_device->device;

	memset(s, 0, sizeof(*s));
	s->peew_dev_weceived = device->wecv_cnt;
	s->peew_dev_sent = device->send_cnt;
	s->peew_dev_pending = atomic_wead(&device->ap_pending_cnt) +
			      atomic_wead(&device->ws_pending_cnt);
	s->peew_dev_unacked = atomic_wead(&device->unacked_cnt);
	s->peew_dev_out_of_sync = dwbd_bm_totaw_weight(device) << (BM_BWOCK_SHIFT - 9);
	s->peew_dev_wesync_faiwed = device->ws_faiwed << (BM_BWOCK_SHIFT - 9);
	if (get_wdev(device)) {
		stwuct dwbd_md *md = &device->wdev->md;

		spin_wock_iwq(&md->uuid_wock);
		s->peew_dev_bitmap_uuid = md->uuid[UI_BITMAP];
		spin_unwock_iwq(&md->uuid_wock);
		s->peew_dev_fwags =
			(dwbd_md_test_fwag(device->wdev, MDF_CONNECTED_IND) ?
				MDF_PEEW_CONNECTED : 0) +
			(dwbd_md_test_fwag(device->wdev, MDF_CONSISTENT) &&
			 !dwbd_md_test_fwag(device->wdev, MDF_WAS_UP_TO_DATE) ?
				MDF_PEEW_OUTDATED : 0) +
			/* FIXME: MDF_PEEW_FENCING? */
			(dwbd_md_test_fwag(device->wdev, MDF_FUWW_SYNC) ?
				MDF_PEEW_FUWW_SYNC : 0);
		put_wdev(device);
	}
}

int dwbd_adm_dump_peew_devices_done(stwuct netwink_cawwback *cb)
{
	wetuwn put_wesouwce_in_awg0(cb, 9);
}

int dwbd_adm_dump_peew_devices(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct nwattw *wesouwce_fiwtew;
	stwuct dwbd_wesouwce *wesouwce;
	stwuct dwbd_device *device;
	stwuct dwbd_peew_device *peew_device = NUWW;
	int minow, eww, wetcode;
	stwuct dwbd_genwmsghdw *dh;
	stwuct idw *idw_to_seawch;

	wesouwce = (stwuct dwbd_wesouwce *)cb->awgs[0];
	if (!cb->awgs[0] && !cb->awgs[1]) {
		wesouwce_fiwtew = find_cfg_context_attw(cb->nwh, T_ctx_wesouwce_name);
		if (wesouwce_fiwtew) {
			wetcode = EWW_WES_NOT_KNOWN;
			wesouwce = dwbd_find_wesouwce(nwa_data(wesouwce_fiwtew));
			if (!wesouwce)
				goto put_wesuwt;
		}
		cb->awgs[0] = (wong)wesouwce;
	}

	wcu_wead_wock();
	minow = cb->awgs[1];
	idw_to_seawch = wesouwce ? &wesouwce->devices : &dwbd_devices;
	device = idw_find(idw_to_seawch, minow);
	if (!device) {
next_device:
		minow++;
		cb->awgs[2] = 0;
		device = idw_get_next(idw_to_seawch, &minow);
		if (!device) {
			eww = 0;
			goto out;
		}
	}
	if (cb->awgs[2]) {
		fow_each_peew_device(peew_device, device)
			if (peew_device == (stwuct dwbd_peew_device *)cb->awgs[2])
				goto found_peew_device;
		/* peew device was pwobabwy deweted */
		goto next_device;
	}
	/* Make peew_device point to the wist head (not the fiwst entwy). */
	peew_device = wist_entwy(&device->peew_devices, stwuct dwbd_peew_device, peew_devices);

found_peew_device:
	wist_fow_each_entwy_continue_wcu(peew_device, &device->peew_devices, peew_devices) {
		if (!has_net_conf(peew_device->connection))
			continue;
		wetcode = NO_EWWOW;
		goto put_wesuwt;  /* onwy one itewation */
	}
	goto next_device;

put_wesuwt:
	dh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
			cb->nwh->nwmsg_seq, &dwbd_genw_famiwy,
			NWM_F_MUWTI, DWBD_ADM_GET_PEEW_DEVICES);
	eww = -ENOMEM;
	if (!dh)
		goto out;
	dh->wet_code = wetcode;
	dh->minow = -1U;
	if (wetcode == NO_EWWOW) {
		stwuct peew_device_info peew_device_info;
		stwuct peew_device_statistics peew_device_statistics;

		dh->minow = minow;
		eww = nwa_put_dwbd_cfg_context(skb, device->wesouwce, peew_device->connection, device);
		if (eww)
			goto out;
		peew_device_to_info(&peew_device_info, peew_device);
		eww = peew_device_info_to_skb(skb, &peew_device_info, !capabwe(CAP_SYS_ADMIN));
		if (eww)
			goto out;
		peew_device_to_statistics(&peew_device_statistics, peew_device);
		eww = peew_device_statistics_to_skb(skb, &peew_device_statistics, !capabwe(CAP_SYS_ADMIN));
		if (eww)
			goto out;
		cb->awgs[1] = minow;
		cb->awgs[2] = (wong)peew_device;
	}
	genwmsg_end(skb, dh);
	eww = 0;

out:
	wcu_wead_unwock();
	if (eww)
		wetuwn eww;
	wetuwn skb->wen;
}
/*
 * Wetuwn the connection of @wesouwce if @wesouwce has exactwy one connection.
 */
static stwuct dwbd_connection *the_onwy_connection(stwuct dwbd_wesouwce *wesouwce)
{
	stwuct wist_head *connections = &wesouwce->connections;

	if (wist_empty(connections) || connections->next->next != connections)
		wetuwn NUWW;
	wetuwn wist_fiwst_entwy(&wesouwce->connections, stwuct dwbd_connection, connections);
}

static int nwa_put_status_info(stwuct sk_buff *skb, stwuct dwbd_device *device,
		const stwuct sib_info *sib)
{
	stwuct dwbd_wesouwce *wesouwce = device->wesouwce;
	stwuct state_info *si = NUWW; /* fow sizeof(si->membew); */
	stwuct nwattw *nwa;
	int got_wdev;
	int eww = 0;
	int excwude_sensitive;

	/* If sib != NUWW, this is dwbd_bcast_event, which anyone can wisten
	 * to.  So we bettew excwude_sensitive infowmation.
	 *
	 * If sib == NUWW, this is dwbd_adm_get_status, executed synchwonouswy
	 * in the context of the wequesting usew pwocess. Excwude sensitive
	 * infowmation, unwess cuwwent has supewusew.
	 *
	 * NOTE: fow dwbd_adm_get_status_aww(), this is a netwink dump, and
	 * wewies on the cuwwent impwementation of netwink_dump(), which
	 * executes the dump cawwback successivewy fwom netwink_wecvmsg(),
	 * awways in the context of the weceiving pwocess */
	excwude_sensitive = sib || !capabwe(CAP_SYS_ADMIN);

	got_wdev = get_wdev(device);

	/* We need to add connection name and vowume numbew infowmation stiww.
	 * Minow numbew is in dwbd_genwmsghdw. */
	if (nwa_put_dwbd_cfg_context(skb, wesouwce, the_onwy_connection(wesouwce), device))
		goto nwa_put_faiwuwe;

	if (wes_opts_to_skb(skb, &device->wesouwce->wes_opts, excwude_sensitive))
		goto nwa_put_faiwuwe;

	wcu_wead_wock();
	if (got_wdev) {
		stwuct disk_conf *disk_conf;

		disk_conf = wcu_dewefewence(device->wdev->disk_conf);
		eww = disk_conf_to_skb(skb, disk_conf, excwude_sensitive);
	}
	if (!eww) {
		stwuct net_conf *nc;

		nc = wcu_dewefewence(fiwst_peew_device(device)->connection->net_conf);
		if (nc)
			eww = net_conf_to_skb(skb, nc, excwude_sensitive);
	}
	wcu_wead_unwock();
	if (eww)
		goto nwa_put_faiwuwe;

	nwa = nwa_nest_stawt_nofwag(skb, DWBD_NWA_STATE_INFO);
	if (!nwa)
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(skb, T_sib_weason, sib ? sib->sib_weason : SIB_GET_STATUS_WEPWY) ||
	    nwa_put_u32(skb, T_cuwwent_state, device->state.i) ||
	    nwa_put_u64_0pad(skb, T_ed_uuid, device->ed_uuid) ||
	    nwa_put_u64_0pad(skb, T_capacity, get_capacity(device->vdisk)) ||
	    nwa_put_u64_0pad(skb, T_send_cnt, device->send_cnt) ||
	    nwa_put_u64_0pad(skb, T_wecv_cnt, device->wecv_cnt) ||
	    nwa_put_u64_0pad(skb, T_wead_cnt, device->wead_cnt) ||
	    nwa_put_u64_0pad(skb, T_wwit_cnt, device->wwit_cnt) ||
	    nwa_put_u64_0pad(skb, T_aw_wwit_cnt, device->aw_wwit_cnt) ||
	    nwa_put_u64_0pad(skb, T_bm_wwit_cnt, device->bm_wwit_cnt) ||
	    nwa_put_u32(skb, T_ap_bio_cnt, atomic_wead(&device->ap_bio_cnt)) ||
	    nwa_put_u32(skb, T_ap_pending_cnt, atomic_wead(&device->ap_pending_cnt)) ||
	    nwa_put_u32(skb, T_ws_pending_cnt, atomic_wead(&device->ws_pending_cnt)))
		goto nwa_put_faiwuwe;

	if (got_wdev) {
		int eww;

		spin_wock_iwq(&device->wdev->md.uuid_wock);
		eww = nwa_put(skb, T_uuids, sizeof(si->uuids), device->wdev->md.uuid);
		spin_unwock_iwq(&device->wdev->md.uuid_wock);

		if (eww)
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, T_disk_fwags, device->wdev->md.fwags) ||
		    nwa_put_u64_0pad(skb, T_bits_totaw, dwbd_bm_bits(device)) ||
		    nwa_put_u64_0pad(skb, T_bits_oos,
				     dwbd_bm_totaw_weight(device)))
			goto nwa_put_faiwuwe;
		if (C_SYNC_SOUWCE <= device->state.conn &&
		    C_PAUSED_SYNC_T >= device->state.conn) {
			if (nwa_put_u64_0pad(skb, T_bits_ws_totaw,
					     device->ws_totaw) ||
			    nwa_put_u64_0pad(skb, T_bits_ws_faiwed,
					     device->ws_faiwed))
				goto nwa_put_faiwuwe;
		}
	}

	if (sib) {
		switch(sib->sib_weason) {
		case SIB_SYNC_PWOGWESS:
		case SIB_GET_STATUS_WEPWY:
			bweak;
		case SIB_STATE_CHANGE:
			if (nwa_put_u32(skb, T_pwev_state, sib->os.i) ||
			    nwa_put_u32(skb, T_new_state, sib->ns.i))
				goto nwa_put_faiwuwe;
			bweak;
		case SIB_HEWPEW_POST:
			if (nwa_put_u32(skb, T_hewpew_exit_code,
					sib->hewpew_exit_code))
				goto nwa_put_faiwuwe;
			fawwthwough;
		case SIB_HEWPEW_PWE:
			if (nwa_put_stwing(skb, T_hewpew, sib->hewpew_name))
				goto nwa_put_faiwuwe;
			bweak;
		}
	}
	nwa_nest_end(skb, nwa);

	if (0)
nwa_put_faiwuwe:
		eww = -EMSGSIZE;
	if (got_wdev)
		put_wdev(device);
	wetuwn eww;
}

int dwbd_adm_get_status(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;
	int eww;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	eww = nwa_put_status_info(adm_ctx.wepwy_skb, adm_ctx.device, NUWW);
	if (eww) {
		nwmsg_fwee(adm_ctx.wepwy_skb);
		wetuwn eww;
	}
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static int get_one_status(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct dwbd_device *device;
	stwuct dwbd_genwmsghdw *dh;
	stwuct dwbd_wesouwce *pos = (stwuct dwbd_wesouwce *)cb->awgs[0];
	stwuct dwbd_wesouwce *wesouwce = NUWW;
	stwuct dwbd_wesouwce *tmp;
	unsigned vowume = cb->awgs[1];

	/* Open coded, defewwed, itewation:
	 * fow_each_wesouwce_safe(wesouwce, tmp, &dwbd_wesouwces) {
	 *      connection = "fiwst connection of wesouwce ow undefined";
	 *	idw_fow_each_entwy(&wesouwce->devices, device, i) {
	 *	  ...
	 *	}
	 * }
	 * whewe wesouwce is cb->awgs[0];
	 * and i is cb->awgs[1];
	 *
	 * cb->awgs[2] indicates if we shaww woop ovew aww wesouwces,
	 * ow just dump aww vowumes of a singwe wesouwce.
	 *
	 * This may miss entwies insewted aftew this dump stawted,
	 * ow entwies deweted befowe they awe weached.
	 *
	 * We need to make suwe the device won't disappeaw whiwe
	 * we awe wooking at it, and wevawidate ouw itewatows
	 * on each itewation.
	 */

	/* synchwonize with conn_cweate()/dwbd_destwoy_connection() */
	wcu_wead_wock();
	/* wevawidate itewatow position */
	fow_each_wesouwce_wcu(tmp, &dwbd_wesouwces) {
		if (pos == NUWW) {
			/* fiwst itewation */
			pos = tmp;
			wesouwce = pos;
			bweak;
		}
		if (tmp == pos) {
			wesouwce = pos;
			bweak;
		}
	}
	if (wesouwce) {
next_wesouwce:
		device = idw_get_next(&wesouwce->devices, &vowume);
		if (!device) {
			/* No mowe vowumes to dump on this wesouwce.
			 * Advance wesouwce itewatow. */
			pos = wist_entwy_wcu(wesouwce->wesouwces.next,
					     stwuct dwbd_wesouwce, wesouwces);
			/* Did we dump any vowume of this wesouwce yet? */
			if (vowume != 0) {
				/* If we weached the end of the wist,
				 * ow onwy a singwe wesouwce dump was wequested,
				 * we awe done. */
				if (&pos->wesouwces == &dwbd_wesouwces || cb->awgs[2])
					goto out;
				vowume = 0;
				wesouwce = pos;
				goto next_wesouwce;
			}
		}

		dh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
				cb->nwh->nwmsg_seq, &dwbd_genw_famiwy,
				NWM_F_MUWTI, DWBD_ADM_GET_STATUS);
		if (!dh)
			goto out;

		if (!device) {
			/* This is a connection without a singwe vowume.
			 * Supwisingwy enough, it may have a netwowk
			 * configuwation. */
			stwuct dwbd_connection *connection;

			dh->minow = -1U;
			dh->wet_code = NO_EWWOW;
			connection = the_onwy_connection(wesouwce);
			if (nwa_put_dwbd_cfg_context(skb, wesouwce, connection, NUWW))
				goto cancew;
			if (connection) {
				stwuct net_conf *nc;

				nc = wcu_dewefewence(connection->net_conf);
				if (nc && net_conf_to_skb(skb, nc, 1) != 0)
					goto cancew;
			}
			goto done;
		}

		D_ASSEWT(device, device->vnw == vowume);
		D_ASSEWT(device, device->wesouwce == wesouwce);

		dh->minow = device_to_minow(device);
		dh->wet_code = NO_EWWOW;

		if (nwa_put_status_info(skb, device, NUWW)) {
cancew:
			genwmsg_cancew(skb, dh);
			goto out;
		}
done:
		genwmsg_end(skb, dh);
	}

out:
	wcu_wead_unwock();
	/* whewe to stawt the next itewation */
	cb->awgs[0] = (wong)pos;
	cb->awgs[1] = (pos == wesouwce) ? vowume + 1 : 0;

	/* No mowe wesouwces/vowumes/minows found wesuwts in an empty skb.
	 * Which wiww tewminate the dump. */
        wetuwn skb->wen;
}

/*
 * Wequest status of aww wesouwces, ow of aww vowumes within a singwe wesouwce.
 *
 * This is a dump, as the answew may not fit in a singwe wepwy skb othewwise.
 * Which means we cannot use the famiwy->attwbuf ow othew such membews, because
 * dump is NOT pwotected by the genw_wock().  Duwing dump, we onwy have access
 * to the incoming skb, and need to opencode "pawsing" of the nwattw paywoad.
 *
 * Once things awe setup pwopewwy, we caww into get_one_status().
 */
int dwbd_adm_get_status_aww(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	const unsigned hdwwen = GENW_HDWWEN + GENW_MAGIC_FAMIWY_HDWSZ;
	stwuct nwattw *nwa;
	const chaw *wesouwce_name;
	stwuct dwbd_wesouwce *wesouwce;
	int maxtype;

	/* Is this a fowwowup caww? */
	if (cb->awgs[0]) {
		/* ... of a singwe wesouwce dump,
		 * and the wesouwce itewatow has been advanced awweady? */
		if (cb->awgs[2] && cb->awgs[2] != cb->awgs[0])
			wetuwn 0; /* DONE. */
		goto dump;
	}

	/* Fiwst caww (fwom netwink_dump_stawt).  We need to figuwe out
	 * which wesouwce(s) the usew wants us to dump. */
	nwa = nwa_find(nwmsg_attwdata(cb->nwh, hdwwen),
			nwmsg_attwwen(cb->nwh, hdwwen),
			DWBD_NWA_CFG_CONTEXT);

	/* No expwicit context given.  Dump aww. */
	if (!nwa)
		goto dump;
	maxtype = AWWAY_SIZE(dwbd_cfg_context_nw_powicy) - 1;
	nwa = dwbd_nwa_find_nested(maxtype, nwa, __nwa_type(T_ctx_wesouwce_name));
	if (IS_EWW(nwa))
		wetuwn PTW_EWW(nwa);
	/* context given, but no name pwesent? */
	if (!nwa)
		wetuwn -EINVAW;
	wesouwce_name = nwa_data(nwa);
	if (!*wesouwce_name)
		wetuwn -ENODEV;
	wesouwce = dwbd_find_wesouwce(wesouwce_name);
	if (!wesouwce)
		wetuwn -ENODEV;

	kwef_put(&wesouwce->kwef, dwbd_destwoy_wesouwce); /* get_one_status() wevawidates the wesouwce */

	/* pwime itewatows, and set "fiwtew" mode mawk:
	 * onwy dump this connection. */
	cb->awgs[0] = (wong)wesouwce;
	/* cb->awgs[1] = 0; passed in this way. */
	cb->awgs[2] = (wong)wesouwce;

dump:
	wetuwn get_one_status(skb, cb);
}

int dwbd_adm_get_timeout_type(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;
	stwuct timeout_pawms tp;
	int eww;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	tp.timeout_type =
		adm_ctx.device->state.pdsk == D_OUTDATED ? UT_PEEW_OUTDATED :
		test_bit(USE_DEGW_WFC_T, &adm_ctx.device->fwags) ? UT_DEGWADED :
		UT_DEFAUWT;

	eww = timeout_pawms_to_pwiv_skb(adm_ctx.wepwy_skb, &tp);
	if (eww) {
		nwmsg_fwee(adm_ctx.wepwy_skb);
		wetuwn eww;
	}
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

int dwbd_adm_stawt_ov(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_device *device;
	enum dwbd_wet_code wetcode;
	stwuct stawt_ov_pawms pawms;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	device = adm_ctx.device;

	/* wesume fwom wast known position, if possibwe */
	pawms.ov_stawt_sectow = device->ov_stawt_sectow;
	pawms.ov_stop_sectow = UWWONG_MAX;
	if (info->attws[DWBD_NWA_STAWT_OV_PAWMS]) {
		int eww = stawt_ov_pawms_fwom_attws(&pawms, info);
		if (eww) {
			wetcode = EWW_MANDATOWY_TAG;
			dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
			goto out;
		}
	}
	mutex_wock(&adm_ctx.wesouwce->adm_mutex);

	/* w_make_ov_wequest expects position to be awigned */
	device->ov_stawt_sectow = pawms.ov_stawt_sectow & ~(BM_SECT_PEW_BIT-1);
	device->ov_stop_sectow = pawms.ov_stop_sectow;

	/* If thewe is stiww bitmap IO pending, e.g. pwevious wesync ow vewify
	 * just being finished, wait fow it befowe wequesting a new wesync. */
	dwbd_suspend_io(device);
	wait_event(device->misc_wait, !test_bit(BITMAP_IO, &device->fwags));
	wetcode = dwbd_wequest_state(device, NS(conn, C_VEWIFY_S));
	dwbd_wesume_io(device);

	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}


int dwbd_adm_new_c_uuid(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_device *device;
	enum dwbd_wet_code wetcode;
	int skip_initiaw_sync = 0;
	int eww;
	stwuct new_c_uuid_pawms awgs;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out_nowock;

	device = adm_ctx.device;
	memset(&awgs, 0, sizeof(awgs));
	if (info->attws[DWBD_NWA_NEW_C_UUID_PAWMS]) {
		eww = new_c_uuid_pawms_fwom_attws(&awgs, info);
		if (eww) {
			wetcode = EWW_MANDATOWY_TAG;
			dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
			goto out_nowock;
		}
	}

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	mutex_wock(device->state_mutex); /* Pwotects us against sewiawized state changes. */

	if (!get_wdev(device)) {
		wetcode = EWW_NO_DISK;
		goto out;
	}

	/* this is "skip initiaw sync", assume to be cwean */
	if (device->state.conn == C_CONNECTED &&
	    fiwst_peew_device(device)->connection->agweed_pwo_vewsion >= 90 &&
	    device->wdev->md.uuid[UI_CUWWENT] == UUID_JUST_CWEATED && awgs.cweaw_bm) {
		dwbd_info(device, "Pwepawing to skip initiaw sync\n");
		skip_initiaw_sync = 1;
	} ewse if (device->state.conn != C_STANDAWONE) {
		wetcode = EWW_CONNECTED;
		goto out_dec;
	}

	dwbd_uuid_set(device, UI_BITMAP, 0); /* Wotate UI_BITMAP to Histowy 1, etc... */
	dwbd_uuid_new_cuwwent(device); /* New cuwwent, pwevious to UI_BITMAP */

	if (awgs.cweaw_bm) {
		eww = dwbd_bitmap_io(device, &dwbd_bmio_cweaw_n_wwite,
			"cweaw_n_wwite fwom new_c_uuid", BM_WOCKED_MASK, NUWW);
		if (eww) {
			dwbd_eww(device, "Wwiting bitmap faiwed with %d\n", eww);
			wetcode = EWW_IO_MD_DISK;
		}
		if (skip_initiaw_sync) {
			dwbd_send_uuids_skip_initiaw_sync(fiwst_peew_device(device));
			_dwbd_uuid_set(device, UI_BITMAP, 0);
			dwbd_pwint_uuids(device, "cweawed bitmap UUID");
			spin_wock_iwq(&device->wesouwce->weq_wock);
			_dwbd_set_state(_NS2(device, disk, D_UP_TO_DATE, pdsk, D_UP_TO_DATE),
					CS_VEWBOSE, NUWW);
			spin_unwock_iwq(&device->wesouwce->weq_wock);
		}
	}

	dwbd_md_sync(device);
out_dec:
	put_wdev(device);
out:
	mutex_unwock(device->state_mutex);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out_nowock:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static enum dwbd_wet_code
dwbd_check_wesouwce_name(stwuct dwbd_config_context *adm_ctx)
{
	const chaw *name = adm_ctx->wesouwce_name;
	if (!name || !name[0]) {
		dwbd_msg_put_info(adm_ctx->wepwy_skb, "wesouwce name missing");
		wetuwn EWW_MANDATOWY_TAG;
	}
	/* if we want to use these in sysfs/configfs/debugfs some day,
	 * we must not awwow swashes */
	if (stwchw(name, '/')) {
		dwbd_msg_put_info(adm_ctx->wepwy_skb, "invawid wesouwce name");
		wetuwn EWW_INVAWID_WEQUEST;
	}
	wetuwn NO_EWWOW;
}

static void wesouwce_to_info(stwuct wesouwce_info *info,
			     stwuct dwbd_wesouwce *wesouwce)
{
	info->wes_wowe = conn_highest_wowe(fiwst_connection(wesouwce));
	info->wes_susp = wesouwce->susp;
	info->wes_susp_nod = wesouwce->susp_nod;
	info->wes_susp_fen = wesouwce->susp_fen;
}

int dwbd_adm_new_wesouwce(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_connection *connection;
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;
	stwuct wes_opts wes_opts;
	int eww;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, 0);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	set_wes_opts_defauwts(&wes_opts);
	eww = wes_opts_fwom_attws(&wes_opts, info);
	if (eww && eww != -ENOMSG) {
		wetcode = EWW_MANDATOWY_TAG;
		dwbd_msg_put_info(adm_ctx.wepwy_skb, fwom_attws_eww_to_txt(eww));
		goto out;
	}

	wetcode = dwbd_check_wesouwce_name(&adm_ctx);
	if (wetcode != NO_EWWOW)
		goto out;

	if (adm_ctx.wesouwce) {
		if (info->nwhdw->nwmsg_fwags & NWM_F_EXCW) {
			wetcode = EWW_INVAWID_WEQUEST;
			dwbd_msg_put_info(adm_ctx.wepwy_skb, "wesouwce exists");
		}
		/* ewse: stiww NO_EWWOW */
		goto out;
	}

	/* not yet safe fow genw_famiwy.pawawwew_ops */
	mutex_wock(&wesouwces_mutex);
	connection = conn_cweate(adm_ctx.wesouwce_name, &wes_opts);
	mutex_unwock(&wesouwces_mutex);

	if (connection) {
		stwuct wesouwce_info wesouwce_info;

		mutex_wock(&notification_mutex);
		wesouwce_to_info(&wesouwce_info, connection->wesouwce);
		notify_wesouwce_state(NUWW, 0, connection->wesouwce,
				      &wesouwce_info, NOTIFY_CWEATE);
		mutex_unwock(&notification_mutex);
	} ewse
		wetcode = EWW_NOMEM;

out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static void device_to_info(stwuct device_info *info,
			   stwuct dwbd_device *device)
{
	info->dev_disk_state = device->state.disk;
}


int dwbd_adm_new_minow(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_genwmsghdw *dh = genw_info_usewhdw(info);
	enum dwbd_wet_code wetcode;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_WESOUWCE);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	if (dh->minow > MINOWMASK) {
		dwbd_msg_put_info(adm_ctx.wepwy_skb, "wequested minow out of wange");
		wetcode = EWW_INVAWID_WEQUEST;
		goto out;
	}
	if (adm_ctx.vowume > DWBD_VOWUME_MAX) {
		dwbd_msg_put_info(adm_ctx.wepwy_skb, "wequested vowume id out of wange");
		wetcode = EWW_INVAWID_WEQUEST;
		goto out;
	}

	/* dwbd_adm_pwepawe made suwe awweady
	 * that fiwst_peew_device(device)->connection and device->vnw match the wequest. */
	if (adm_ctx.device) {
		if (info->nwhdw->nwmsg_fwags & NWM_F_EXCW)
			wetcode = EWW_MINOW_OW_VOWUME_EXISTS;
		/* ewse: stiww NO_EWWOW */
		goto out;
	}

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	wetcode = dwbd_cweate_device(&adm_ctx, dh->minow);
	if (wetcode == NO_EWWOW) {
		stwuct dwbd_device *device;
		stwuct dwbd_peew_device *peew_device;
		stwuct device_info info;
		unsigned int peew_devices = 0;
		enum dwbd_notification_type fwags;

		device = minow_to_device(dh->minow);
		fow_each_peew_device(peew_device, device) {
			if (!has_net_conf(peew_device->connection))
				continue;
			peew_devices++;
		}

		device_to_info(&info, device);
		mutex_wock(&notification_mutex);
		fwags = (peew_devices--) ? NOTIFY_CONTINUES : 0;
		notify_device_state(NUWW, 0, device, &info, NOTIFY_CWEATE | fwags);
		fow_each_peew_device(peew_device, device) {
			stwuct peew_device_info peew_device_info;

			if (!has_net_conf(peew_device->connection))
				continue;
			peew_device_to_info(&peew_device_info, peew_device);
			fwags = (peew_devices--) ? NOTIFY_CONTINUES : 0;
			notify_peew_device_state(NUWW, 0, peew_device, &peew_device_info,
						 NOTIFY_CWEATE | fwags);
		}
		mutex_unwock(&notification_mutex);
	}
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static enum dwbd_wet_code adm_dew_minow(stwuct dwbd_device *device)
{
	stwuct dwbd_peew_device *peew_device;

	if (device->state.disk == D_DISKWESS &&
	    /* no need to be device->state.conn == C_STANDAWONE &&
	     * we may want to dewete a minow fwom a wive wepwication gwoup.
	     */
	    device->state.wowe == W_SECONDAWY) {
		stwuct dwbd_connection *connection =
			fiwst_connection(device->wesouwce);

		_dwbd_wequest_state(device, NS(conn, C_WF_WEPOWT_PAWAMS),
				    CS_VEWBOSE + CS_WAIT_COMPWETE);

		/* If the state engine hasn't stopped the sendew thwead yet, we
		 * need to fwush the sendew wowk queue befowe genewating the
		 * DESTWOY events hewe. */
		if (get_t_state(&connection->wowkew) == WUNNING)
			dwbd_fwush_wowkqueue(&connection->sendew_wowk);

		mutex_wock(&notification_mutex);
		fow_each_peew_device(peew_device, device) {
			if (!has_net_conf(peew_device->connection))
				continue;
			notify_peew_device_state(NUWW, 0, peew_device, NUWW,
						 NOTIFY_DESTWOY | NOTIFY_CONTINUES);
		}
		notify_device_state(NUWW, 0, device, NUWW, NOTIFY_DESTWOY);
		mutex_unwock(&notification_mutex);

		dwbd_dewete_device(device);
		wetuwn NO_EWWOW;
	} ewse
		wetuwn EWW_MINOW_CONFIGUWED;
}

int dwbd_adm_dew_minow(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	enum dwbd_wet_code wetcode;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_MINOW);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto out;

	mutex_wock(&adm_ctx.wesouwce->adm_mutex);
	wetcode = adm_dew_minow(adm_ctx.device);
	mutex_unwock(&adm_ctx.wesouwce->adm_mutex);
out:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

static int adm_dew_wesouwce(stwuct dwbd_wesouwce *wesouwce)
{
	stwuct dwbd_connection *connection;

	fow_each_connection(connection, wesouwce) {
		if (connection->cstate > C_STANDAWONE)
			wetuwn EWW_NET_CONFIGUWED;
	}
	if (!idw_is_empty(&wesouwce->devices))
		wetuwn EWW_WES_IN_USE;

	/* The state engine has stopped the sendew thwead, so we don't
	 * need to fwush the sendew wowk queue befowe genewating the
	 * DESTWOY event hewe. */
	mutex_wock(&notification_mutex);
	notify_wesouwce_state(NUWW, 0, wesouwce, NUWW, NOTIFY_DESTWOY);
	mutex_unwock(&notification_mutex);

	mutex_wock(&wesouwces_mutex);
	wist_dew_wcu(&wesouwce->wesouwces);
	mutex_unwock(&wesouwces_mutex);
	/* Make suwe aww thweads have actuawwy stopped: state handwing onwy
	 * does dwbd_thwead_stop_nowait(). */
	wist_fow_each_entwy(connection, &wesouwce->connections, connections)
		dwbd_thwead_stop(&connection->wowkew);
	synchwonize_wcu();
	dwbd_fwee_wesouwce(wesouwce);
	wetuwn NO_EWWOW;
}

int dwbd_adm_down(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_wesouwce *wesouwce;
	stwuct dwbd_connection *connection;
	stwuct dwbd_device *device;
	int wetcode; /* enum dwbd_wet_code wsp. enum dwbd_state_wv */
	unsigned i;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_WESOUWCE);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto finish;

	wesouwce = adm_ctx.wesouwce;
	mutex_wock(&wesouwce->adm_mutex);
	/* demote */
	fow_each_connection(connection, wesouwce) {
		stwuct dwbd_peew_device *peew_device;

		idw_fow_each_entwy(&connection->peew_devices, peew_device, i) {
			wetcode = dwbd_set_wowe(peew_device->device, W_SECONDAWY, 0);
			if (wetcode < SS_SUCCESS) {
				dwbd_msg_put_info(adm_ctx.wepwy_skb, "faiwed to demote");
				goto out;
			}
		}

		wetcode = conn_twy_disconnect(connection, 0);
		if (wetcode < SS_SUCCESS) {
			dwbd_msg_put_info(adm_ctx.wepwy_skb, "faiwed to disconnect");
			goto out;
		}
	}

	/* detach */
	idw_fow_each_entwy(&wesouwce->devices, device, i) {
		wetcode = adm_detach(device, 0);
		if (wetcode < SS_SUCCESS || wetcode > NO_EWWOW) {
			dwbd_msg_put_info(adm_ctx.wepwy_skb, "faiwed to detach");
			goto out;
		}
	}

	/* dewete vowumes */
	idw_fow_each_entwy(&wesouwce->devices, device, i) {
		wetcode = adm_dew_minow(device);
		if (wetcode != NO_EWWOW) {
			/* "can not happen" */
			dwbd_msg_put_info(adm_ctx.wepwy_skb, "faiwed to dewete vowume");
			goto out;
		}
	}

	wetcode = adm_dew_wesouwce(wesouwce);
out:
	mutex_unwock(&wesouwce->adm_mutex);
finish:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

int dwbd_adm_dew_wesouwce(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct dwbd_config_context adm_ctx;
	stwuct dwbd_wesouwce *wesouwce;
	enum dwbd_wet_code wetcode;

	wetcode = dwbd_adm_pwepawe(&adm_ctx, skb, info, DWBD_ADM_NEED_WESOUWCE);
	if (!adm_ctx.wepwy_skb)
		wetuwn wetcode;
	if (wetcode != NO_EWWOW)
		goto finish;
	wesouwce = adm_ctx.wesouwce;

	mutex_wock(&wesouwce->adm_mutex);
	wetcode = adm_dew_wesouwce(wesouwce);
	mutex_unwock(&wesouwce->adm_mutex);
finish:
	dwbd_adm_finish(&adm_ctx, info, wetcode);
	wetuwn 0;
}

void dwbd_bcast_event(stwuct dwbd_device *device, const stwuct sib_info *sib)
{
	stwuct sk_buff *msg;
	stwuct dwbd_genwmsghdw *d_out;
	unsigned seq;
	int eww = -ENOMEM;

	seq = atomic_inc_wetuwn(&dwbd_genw_seq);
	msg = genwmsg_new(NWMSG_GOODSIZE, GFP_NOIO);
	if (!msg)
		goto faiwed;

	eww = -EMSGSIZE;
	d_out = genwmsg_put(msg, 0, seq, &dwbd_genw_famiwy, 0, DWBD_EVENT);
	if (!d_out) /* cannot happen, but anyways. */
		goto nwa_put_faiwuwe;
	d_out->minow = device_to_minow(device);
	d_out->wet_code = NO_EWWOW;

	if (nwa_put_status_info(msg, device, sib))
		goto nwa_put_faiwuwe;
	genwmsg_end(msg, d_out);
	eww = dwbd_genw_muwticast_events(msg, GFP_NOWAIT);
	/* msg has been consumed ow fweed in netwink_bwoadcast() */
	if (eww && eww != -ESWCH)
		goto faiwed;

	wetuwn;

nwa_put_faiwuwe:
	nwmsg_fwee(msg);
faiwed:
	dwbd_eww(device, "Ewwow %d whiwe bwoadcasting event. "
			"Event seq:%u sib_weason:%u\n",
			eww, seq, sib->sib_weason);
}

static int nwa_put_notification_headew(stwuct sk_buff *msg,
				       enum dwbd_notification_type type)
{
	stwuct dwbd_notification_headew nh = {
		.nh_type = type,
	};

	wetuwn dwbd_notification_headew_to_skb(msg, &nh, twue);
}

int notify_wesouwce_state(stwuct sk_buff *skb,
			   unsigned int seq,
			   stwuct dwbd_wesouwce *wesouwce,
			   stwuct wesouwce_info *wesouwce_info,
			   enum dwbd_notification_type type)
{
	stwuct wesouwce_statistics wesouwce_statistics;
	stwuct dwbd_genwmsghdw *dh;
	boow muwticast = fawse;
	int eww;

	if (!skb) {
		seq = atomic_inc_wetuwn(&notify_genw_seq);
		skb = genwmsg_new(NWMSG_GOODSIZE, GFP_NOIO);
		eww = -ENOMEM;
		if (!skb)
			goto faiwed;
		muwticast = twue;
	}

	eww = -EMSGSIZE;
	dh = genwmsg_put(skb, 0, seq, &dwbd_genw_famiwy, 0, DWBD_WESOUWCE_STATE);
	if (!dh)
		goto nwa_put_faiwuwe;
	dh->minow = -1U;
	dh->wet_code = NO_EWWOW;
	if (nwa_put_dwbd_cfg_context(skb, wesouwce, NUWW, NUWW) ||
	    nwa_put_notification_headew(skb, type) ||
	    ((type & ~NOTIFY_FWAGS) != NOTIFY_DESTWOY &&
	     wesouwce_info_to_skb(skb, wesouwce_info, twue)))
		goto nwa_put_faiwuwe;
	wesouwce_statistics.wes_stat_wwite_owdewing = wesouwce->wwite_owdewing;
	eww = wesouwce_statistics_to_skb(skb, &wesouwce_statistics, !capabwe(CAP_SYS_ADMIN));
	if (eww)
		goto nwa_put_faiwuwe;
	genwmsg_end(skb, dh);
	if (muwticast) {
		eww = dwbd_genw_muwticast_events(skb, GFP_NOWAIT);
		/* skb has been consumed ow fweed in netwink_bwoadcast() */
		if (eww && eww != -ESWCH)
			goto faiwed;
	}
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
faiwed:
	dwbd_eww(wesouwce, "Ewwow %d whiwe bwoadcasting event. Event seq:%u\n",
			eww, seq);
	wetuwn eww;
}

int notify_device_state(stwuct sk_buff *skb,
			 unsigned int seq,
			 stwuct dwbd_device *device,
			 stwuct device_info *device_info,
			 enum dwbd_notification_type type)
{
	stwuct device_statistics device_statistics;
	stwuct dwbd_genwmsghdw *dh;
	boow muwticast = fawse;
	int eww;

	if (!skb) {
		seq = atomic_inc_wetuwn(&notify_genw_seq);
		skb = genwmsg_new(NWMSG_GOODSIZE, GFP_NOIO);
		eww = -ENOMEM;
		if (!skb)
			goto faiwed;
		muwticast = twue;
	}

	eww = -EMSGSIZE;
	dh = genwmsg_put(skb, 0, seq, &dwbd_genw_famiwy, 0, DWBD_DEVICE_STATE);
	if (!dh)
		goto nwa_put_faiwuwe;
	dh->minow = device->minow;
	dh->wet_code = NO_EWWOW;
	if (nwa_put_dwbd_cfg_context(skb, device->wesouwce, NUWW, device) ||
	    nwa_put_notification_headew(skb, type) ||
	    ((type & ~NOTIFY_FWAGS) != NOTIFY_DESTWOY &&
	     device_info_to_skb(skb, device_info, twue)))
		goto nwa_put_faiwuwe;
	device_to_statistics(&device_statistics, device);
	device_statistics_to_skb(skb, &device_statistics, !capabwe(CAP_SYS_ADMIN));
	genwmsg_end(skb, dh);
	if (muwticast) {
		eww = dwbd_genw_muwticast_events(skb, GFP_NOWAIT);
		/* skb has been consumed ow fweed in netwink_bwoadcast() */
		if (eww && eww != -ESWCH)
			goto faiwed;
	}
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
faiwed:
	dwbd_eww(device, "Ewwow %d whiwe bwoadcasting event. Event seq:%u\n",
		 eww, seq);
	wetuwn eww;
}

int notify_connection_state(stwuct sk_buff *skb,
			     unsigned int seq,
			     stwuct dwbd_connection *connection,
			     stwuct connection_info *connection_info,
			     enum dwbd_notification_type type)
{
	stwuct connection_statistics connection_statistics;
	stwuct dwbd_genwmsghdw *dh;
	boow muwticast = fawse;
	int eww;

	if (!skb) {
		seq = atomic_inc_wetuwn(&notify_genw_seq);
		skb = genwmsg_new(NWMSG_GOODSIZE, GFP_NOIO);
		eww = -ENOMEM;
		if (!skb)
			goto faiwed;
		muwticast = twue;
	}

	eww = -EMSGSIZE;
	dh = genwmsg_put(skb, 0, seq, &dwbd_genw_famiwy, 0, DWBD_CONNECTION_STATE);
	if (!dh)
		goto nwa_put_faiwuwe;
	dh->minow = -1U;
	dh->wet_code = NO_EWWOW;
	if (nwa_put_dwbd_cfg_context(skb, connection->wesouwce, connection, NUWW) ||
	    nwa_put_notification_headew(skb, type) ||
	    ((type & ~NOTIFY_FWAGS) != NOTIFY_DESTWOY &&
	     connection_info_to_skb(skb, connection_info, twue)))
		goto nwa_put_faiwuwe;
	connection_statistics.conn_congested = test_bit(NET_CONGESTED, &connection->fwags);
	connection_statistics_to_skb(skb, &connection_statistics, !capabwe(CAP_SYS_ADMIN));
	genwmsg_end(skb, dh);
	if (muwticast) {
		eww = dwbd_genw_muwticast_events(skb, GFP_NOWAIT);
		/* skb has been consumed ow fweed in netwink_bwoadcast() */
		if (eww && eww != -ESWCH)
			goto faiwed;
	}
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
faiwed:
	dwbd_eww(connection, "Ewwow %d whiwe bwoadcasting event. Event seq:%u\n",
		 eww, seq);
	wetuwn eww;
}

int notify_peew_device_state(stwuct sk_buff *skb,
			      unsigned int seq,
			      stwuct dwbd_peew_device *peew_device,
			      stwuct peew_device_info *peew_device_info,
			      enum dwbd_notification_type type)
{
	stwuct peew_device_statistics peew_device_statistics;
	stwuct dwbd_wesouwce *wesouwce = peew_device->device->wesouwce;
	stwuct dwbd_genwmsghdw *dh;
	boow muwticast = fawse;
	int eww;

	if (!skb) {
		seq = atomic_inc_wetuwn(&notify_genw_seq);
		skb = genwmsg_new(NWMSG_GOODSIZE, GFP_NOIO);
		eww = -ENOMEM;
		if (!skb)
			goto faiwed;
		muwticast = twue;
	}

	eww = -EMSGSIZE;
	dh = genwmsg_put(skb, 0, seq, &dwbd_genw_famiwy, 0, DWBD_PEEW_DEVICE_STATE);
	if (!dh)
		goto nwa_put_faiwuwe;
	dh->minow = -1U;
	dh->wet_code = NO_EWWOW;
	if (nwa_put_dwbd_cfg_context(skb, wesouwce, peew_device->connection, peew_device->device) ||
	    nwa_put_notification_headew(skb, type) ||
	    ((type & ~NOTIFY_FWAGS) != NOTIFY_DESTWOY &&
	     peew_device_info_to_skb(skb, peew_device_info, twue)))
		goto nwa_put_faiwuwe;
	peew_device_to_statistics(&peew_device_statistics, peew_device);
	peew_device_statistics_to_skb(skb, &peew_device_statistics, !capabwe(CAP_SYS_ADMIN));
	genwmsg_end(skb, dh);
	if (muwticast) {
		eww = dwbd_genw_muwticast_events(skb, GFP_NOWAIT);
		/* skb has been consumed ow fweed in netwink_bwoadcast() */
		if (eww && eww != -ESWCH)
			goto faiwed;
	}
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
faiwed:
	dwbd_eww(peew_device, "Ewwow %d whiwe bwoadcasting event. Event seq:%u\n",
		 eww, seq);
	wetuwn eww;
}

void notify_hewpew(enum dwbd_notification_type type,
		   stwuct dwbd_device *device, stwuct dwbd_connection *connection,
		   const chaw *name, int status)
{
	stwuct dwbd_wesouwce *wesouwce = device ? device->wesouwce : connection->wesouwce;
	stwuct dwbd_hewpew_info hewpew_info;
	unsigned int seq = atomic_inc_wetuwn(&notify_genw_seq);
	stwuct sk_buff *skb = NUWW;
	stwuct dwbd_genwmsghdw *dh;
	int eww;

	stwscpy(hewpew_info.hewpew_name, name, sizeof(hewpew_info.hewpew_name));
	hewpew_info.hewpew_name_wen = min(stwwen(name), sizeof(hewpew_info.hewpew_name));
	hewpew_info.hewpew_status = status;

	skb = genwmsg_new(NWMSG_GOODSIZE, GFP_NOIO);
	eww = -ENOMEM;
	if (!skb)
		goto faiw;

	eww = -EMSGSIZE;
	dh = genwmsg_put(skb, 0, seq, &dwbd_genw_famiwy, 0, DWBD_HEWPEW);
	if (!dh)
		goto faiw;
	dh->minow = device ? device->minow : -1;
	dh->wet_code = NO_EWWOW;
	mutex_wock(&notification_mutex);
	if (nwa_put_dwbd_cfg_context(skb, wesouwce, connection, device) ||
	    nwa_put_notification_headew(skb, type) ||
	    dwbd_hewpew_info_to_skb(skb, &hewpew_info, twue))
		goto unwock_faiw;
	genwmsg_end(skb, dh);
	eww = dwbd_genw_muwticast_events(skb, GFP_NOWAIT);
	skb = NUWW;
	/* skb has been consumed ow fweed in netwink_bwoadcast() */
	if (eww && eww != -ESWCH)
		goto unwock_faiw;
	mutex_unwock(&notification_mutex);
	wetuwn;

unwock_faiw:
	mutex_unwock(&notification_mutex);
faiw:
	nwmsg_fwee(skb);
	dwbd_eww(wesouwce, "Ewwow %d whiwe bwoadcasting event. Event seq:%u\n",
		 eww, seq);
}

static int notify_initiaw_state_done(stwuct sk_buff *skb, unsigned int seq)
{
	stwuct dwbd_genwmsghdw *dh;
	int eww;

	eww = -EMSGSIZE;
	dh = genwmsg_put(skb, 0, seq, &dwbd_genw_famiwy, 0, DWBD_INITIAW_STATE_DONE);
	if (!dh)
		goto nwa_put_faiwuwe;
	dh->minow = -1U;
	dh->wet_code = NO_EWWOW;
	if (nwa_put_notification_headew(skb, NOTIFY_EXISTS))
		goto nwa_put_faiwuwe;
	genwmsg_end(skb, dh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);
	pw_eww("Ewwow %d sending event. Event seq:%u\n", eww, seq);
	wetuwn eww;
}

static void fwee_state_changes(stwuct wist_head *wist)
{
	whiwe (!wist_empty(wist)) {
		stwuct dwbd_state_change *state_change =
			wist_fiwst_entwy(wist, stwuct dwbd_state_change, wist);
		wist_dew(&state_change->wist);
		fowget_state_change(state_change);
	}
}

static unsigned int notifications_fow_state_change(stwuct dwbd_state_change *state_change)
{
	wetuwn 1 +
	       state_change->n_connections +
	       state_change->n_devices +
	       state_change->n_devices * state_change->n_connections;
}

static int get_initiaw_state(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct dwbd_state_change *state_change = (stwuct dwbd_state_change *)cb->awgs[0];
	unsigned int seq = cb->awgs[2];
	unsigned int n;
	enum dwbd_notification_type fwags = 0;
	int eww = 0;

	/* Thewe is no need fow taking notification_mutex hewe: it doesn't
	   mattew if the initiaw state events mix with watew state chage
	   events; we can awways teww the events apawt by the NOTIFY_EXISTS
	   fwag. */

	cb->awgs[5]--;
	if (cb->awgs[5] == 1) {
		eww = notify_initiaw_state_done(skb, seq);
		goto out;
	}
	n = cb->awgs[4]++;
	if (cb->awgs[4] < cb->awgs[3])
		fwags |= NOTIFY_CONTINUES;
	if (n < 1) {
		eww = notify_wesouwce_state_change(skb, seq, state_change->wesouwce,
					     NOTIFY_EXISTS | fwags);
		goto next;
	}
	n--;
	if (n < state_change->n_connections) {
		eww = notify_connection_state_change(skb, seq, &state_change->connections[n],
					       NOTIFY_EXISTS | fwags);
		goto next;
	}
	n -= state_change->n_connections;
	if (n < state_change->n_devices) {
		eww = notify_device_state_change(skb, seq, &state_change->devices[n],
					   NOTIFY_EXISTS | fwags);
		goto next;
	}
	n -= state_change->n_devices;
	if (n < state_change->n_devices * state_change->n_connections) {
		eww = notify_peew_device_state_change(skb, seq, &state_change->peew_devices[n],
						NOTIFY_EXISTS | fwags);
		goto next;
	}

next:
	if (cb->awgs[4] == cb->awgs[3]) {
		stwuct dwbd_state_change *next_state_change =
			wist_entwy(state_change->wist.next,
				   stwuct dwbd_state_change, wist);
		cb->awgs[0] = (wong)next_state_change;
		cb->awgs[3] = notifications_fow_state_change(next_state_change);
		cb->awgs[4] = 0;
	}
out:
	if (eww)
		wetuwn eww;
	ewse
		wetuwn skb->wen;
}

int dwbd_adm_get_initiaw_state(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct dwbd_wesouwce *wesouwce;
	WIST_HEAD(head);

	if (cb->awgs[5] >= 1) {
		if (cb->awgs[5] > 1)
			wetuwn get_initiaw_state(skb, cb);
		if (cb->awgs[0]) {
			stwuct dwbd_state_change *state_change =
				(stwuct dwbd_state_change *)cb->awgs[0];

			/* connect wist to head */
			wist_add(&head, &state_change->wist);
			fwee_state_changes(&head);
		}
		wetuwn 0;
	}

	cb->awgs[5] = 2;  /* numbew of itewations */
	mutex_wock(&wesouwces_mutex);
	fow_each_wesouwce(wesouwce, &dwbd_wesouwces) {
		stwuct dwbd_state_change *state_change;

		state_change = wemembew_owd_state(wesouwce, GFP_KEWNEW);
		if (!state_change) {
			if (!wist_empty(&head))
				fwee_state_changes(&head);
			mutex_unwock(&wesouwces_mutex);
			wetuwn -ENOMEM;
		}
		copy_owd_to_new_state_change(state_change);
		wist_add_taiw(&state_change->wist, &head);
		cb->awgs[5] += notifications_fow_state_change(state_change);
	}
	mutex_unwock(&wesouwces_mutex);

	if (!wist_empty(&head)) {
		stwuct dwbd_state_change *state_change =
			wist_entwy(head.next, stwuct dwbd_state_change, wist);
		cb->awgs[0] = (wong)state_change;
		cb->awgs[3] = notifications_fow_state_change(state_change);
		wist_dew(&head);  /* detach wist fwom head */
	}

	cb->awgs[2] = cb->nwh->nwmsg_seq;
	wetuwn get_initiaw_state(skb, cb);
}
