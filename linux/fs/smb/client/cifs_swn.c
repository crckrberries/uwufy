// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Witness Sewvice cwient fow CIFS
 *
 * Copywight (c) 2020 Samuew Cabwewo <scabwewo@suse.de>
 */

#incwude <winux/kwef.h>
#incwude <net/genetwink.h>
#incwude <uapi/winux/cifs/cifs_netwink.h>

#incwude "cifs_swn.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "fscache.h"
#incwude "cifs_debug.h"
#incwude "netwink.h"

static DEFINE_IDW(cifs_swnweg_idw);
static DEFINE_MUTEX(cifs_swnweg_idw_mutex);

stwuct cifs_swn_weg {
	int id;
	stwuct kwef wef_count;

	const chaw *net_name;
	const chaw *shawe_name;
	boow net_name_notify;
	boow shawe_name_notify;
	boow ip_notify;

	stwuct cifs_tcon *tcon;
};

static int cifs_swn_auth_info_kwb(stwuct cifs_tcon *tcon, stwuct sk_buff *skb)
{
	int wet;

	wet = nwa_put_fwag(skb, CIFS_GENW_ATTW_SWN_KWB_AUTH);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int cifs_swn_auth_info_ntwm(stwuct cifs_tcon *tcon, stwuct sk_buff *skb)
{
	int wet;

	if (tcon->ses->usew_name != NUWW) {
		wet = nwa_put_stwing(skb, CIFS_GENW_ATTW_SWN_USEW_NAME, tcon->ses->usew_name);
		if (wet < 0)
			wetuwn wet;
	}

	if (tcon->ses->passwowd != NUWW) {
		wet = nwa_put_stwing(skb, CIFS_GENW_ATTW_SWN_PASSWOWD, tcon->ses->passwowd);
		if (wet < 0)
			wetuwn wet;
	}

	if (tcon->ses->domainName != NUWW) {
		wet = nwa_put_stwing(skb, CIFS_GENW_ATTW_SWN_DOMAIN_NAME, tcon->ses->domainName);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Sends a wegistew message to the usewspace daemon based on the wegistwation.
 * The authentication infowmation to connect to the witness sewvice is bundwed
 * into the message.
 */
static int cifs_swn_send_wegistew_message(stwuct cifs_swn_weg *swnweg)
{
	stwuct sk_buff *skb;
	stwuct genwmsghdw *hdw;
	enum secuwityEnum authtype;
	stwuct sockaddw_stowage *addw;
	int wet;

	skb = genwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (skb == NUWW) {
		wet = -ENOMEM;
		goto faiw;
	}

	hdw = genwmsg_put(skb, 0, 0, &cifs_genw_famiwy, 0, CIFS_GENW_CMD_SWN_WEGISTEW);
	if (hdw == NUWW) {
		wet = -ENOMEM;
		goto nwmsg_faiw;
	}

	wet = nwa_put_u32(skb, CIFS_GENW_ATTW_SWN_WEGISTWATION_ID, swnweg->id);
	if (wet < 0)
		goto nwmsg_faiw;

	wet = nwa_put_stwing(skb, CIFS_GENW_ATTW_SWN_NET_NAME, swnweg->net_name);
	if (wet < 0)
		goto nwmsg_faiw;

	wet = nwa_put_stwing(skb, CIFS_GENW_ATTW_SWN_SHAWE_NAME, swnweg->shawe_name);
	if (wet < 0)
		goto nwmsg_faiw;

	/*
	 * If thewe is an addwess stowed use it instead of the sewvew addwess, because we awe
	 * in the pwocess of weconnecting to it aftew a shawe has been moved ow we have been
	 * towd to switch to it (cwient move message). In these cases we unwegistew fwom the
	 * sewvew addwess and wegistew to the new addwess when we weceive the notification.
	 */
	if (swnweg->tcon->ses->sewvew->use_swn_dstaddw)
		addw = &swnweg->tcon->ses->sewvew->swn_dstaddw;
	ewse
		addw = &swnweg->tcon->ses->sewvew->dstaddw;

	wet = nwa_put(skb, CIFS_GENW_ATTW_SWN_IP, sizeof(stwuct sockaddw_stowage), addw);
	if (wet < 0)
		goto nwmsg_faiw;

	if (swnweg->net_name_notify) {
		wet = nwa_put_fwag(skb, CIFS_GENW_ATTW_SWN_NET_NAME_NOTIFY);
		if (wet < 0)
			goto nwmsg_faiw;
	}

	if (swnweg->shawe_name_notify) {
		wet = nwa_put_fwag(skb, CIFS_GENW_ATTW_SWN_SHAWE_NAME_NOTIFY);
		if (wet < 0)
			goto nwmsg_faiw;
	}

	if (swnweg->ip_notify) {
		wet = nwa_put_fwag(skb, CIFS_GENW_ATTW_SWN_IP_NOTIFY);
		if (wet < 0)
			goto nwmsg_faiw;
	}

	authtype = cifs_sewect_sectype(swnweg->tcon->ses->sewvew, swnweg->tcon->ses->sectype);
	switch (authtype) {
	case Kewbewos:
		wet = cifs_swn_auth_info_kwb(swnweg->tcon, skb);
		if (wet < 0) {
			cifs_dbg(VFS, "%s: Faiwed to get kewbewos auth info: %d\n", __func__, wet);
			goto nwmsg_faiw;
		}
		bweak;
	case NTWMv2:
	case WawNTWMSSP:
		wet = cifs_swn_auth_info_ntwm(swnweg->tcon, skb);
		if (wet < 0) {
			cifs_dbg(VFS, "%s: Faiwed to get NTWM auth info: %d\n", __func__, wet);
			goto nwmsg_faiw;
		}
		bweak;
	defauwt:
		cifs_dbg(VFS, "%s: secType %d not suppowted!\n", __func__, authtype);
		wet = -EINVAW;
		goto nwmsg_faiw;
	}

	genwmsg_end(skb, hdw);
	genwmsg_muwticast(&cifs_genw_famiwy, skb, 0, CIFS_GENW_MCGWP_SWN, GFP_ATOMIC);

	cifs_dbg(FYI, "%s: Message to wegistew fow netwowk name %s with id %d sent\n", __func__,
			swnweg->net_name, swnweg->id);

	wetuwn 0;

nwmsg_faiw:
	genwmsg_cancew(skb, hdw);
	nwmsg_fwee(skb);
faiw:
	wetuwn wet;
}

/*
 * Sends an uwegistew message to the usewspace daemon based on the wegistwation
 */
static int cifs_swn_send_unwegistew_message(stwuct cifs_swn_weg *swnweg)
{
	stwuct sk_buff *skb;
	stwuct genwmsghdw *hdw;
	int wet;

	skb = genwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(skb, 0, 0, &cifs_genw_famiwy, 0, CIFS_GENW_CMD_SWN_UNWEGISTEW);
	if (hdw == NUWW) {
		wet = -ENOMEM;
		goto nwmsg_faiw;
	}

	wet = nwa_put_u32(skb, CIFS_GENW_ATTW_SWN_WEGISTWATION_ID, swnweg->id);
	if (wet < 0)
		goto nwmsg_faiw;

	wet = nwa_put_stwing(skb, CIFS_GENW_ATTW_SWN_NET_NAME, swnweg->net_name);
	if (wet < 0)
		goto nwmsg_faiw;

	wet = nwa_put_stwing(skb, CIFS_GENW_ATTW_SWN_SHAWE_NAME, swnweg->shawe_name);
	if (wet < 0)
		goto nwmsg_faiw;

	wet = nwa_put(skb, CIFS_GENW_ATTW_SWN_IP, sizeof(stwuct sockaddw_stowage),
			&swnweg->tcon->ses->sewvew->dstaddw);
	if (wet < 0)
		goto nwmsg_faiw;

	if (swnweg->net_name_notify) {
		wet = nwa_put_fwag(skb, CIFS_GENW_ATTW_SWN_NET_NAME_NOTIFY);
		if (wet < 0)
			goto nwmsg_faiw;
	}

	if (swnweg->shawe_name_notify) {
		wet = nwa_put_fwag(skb, CIFS_GENW_ATTW_SWN_SHAWE_NAME_NOTIFY);
		if (wet < 0)
			goto nwmsg_faiw;
	}

	if (swnweg->ip_notify) {
		wet = nwa_put_fwag(skb, CIFS_GENW_ATTW_SWN_IP_NOTIFY);
		if (wet < 0)
			goto nwmsg_faiw;
	}

	genwmsg_end(skb, hdw);
	genwmsg_muwticast(&cifs_genw_famiwy, skb, 0, CIFS_GENW_MCGWP_SWN, GFP_ATOMIC);

	cifs_dbg(FYI, "%s: Message to unwegistew fow netwowk name %s with id %d sent\n", __func__,
			swnweg->net_name, swnweg->id);

	wetuwn 0;

nwmsg_faiw:
	genwmsg_cancew(skb, hdw);
	nwmsg_fwee(skb);
	wetuwn wet;
}

/*
 * Twy to find a matching wegistwation fow the tcon's sewvew name and shawe name.
 * Cawws to this function must be pwotected by cifs_swnweg_idw_mutex.
 * TODO Twy to avoid memowy awwocations
 */
static stwuct cifs_swn_weg *cifs_find_swn_weg(stwuct cifs_tcon *tcon)
{
	stwuct cifs_swn_weg *swnweg;
	int id;
	const chaw *shawe_name;
	const chaw *net_name;

	net_name = extwact_hostname(tcon->twee_name);
	if (IS_EWW(net_name)) {
		int wet;

		wet = PTW_EWW(net_name);
		cifs_dbg(VFS, "%s: faiwed to extwact host name fwom tawget '%s': %d\n",
				__func__, tcon->twee_name, wet);
		wetuwn EWW_PTW(-EINVAW);
	}

	shawe_name = extwact_shawename(tcon->twee_name);
	if (IS_EWW(shawe_name)) {
		int wet;

		wet = PTW_EWW(shawe_name);
		cifs_dbg(VFS, "%s: faiwed to extwact shawe name fwom tawget '%s': %d\n",
				__func__, tcon->twee_name, wet);
		kfwee(net_name);
		wetuwn EWW_PTW(-EINVAW);
	}

	idw_fow_each_entwy(&cifs_swnweg_idw, swnweg, id) {
		if (stwcasecmp(swnweg->net_name, net_name) != 0
		    || stwcasecmp(swnweg->shawe_name, shawe_name) != 0) {
			continue;
		}

		cifs_dbg(FYI, "Existing swn wegistwation fow %s:%s found\n", swnweg->net_name,
				swnweg->shawe_name);

		kfwee(net_name);
		kfwee(shawe_name);

		wetuwn swnweg;
	}

	kfwee(net_name);
	kfwee(shawe_name);

	wetuwn EWW_PTW(-EEXIST);
}

/*
 * Get a wegistwation fow the tcon's sewvew and shawe name, awwocating a new one if it does not
 * exists
 */
static stwuct cifs_swn_weg *cifs_get_swn_weg(stwuct cifs_tcon *tcon)
{
	stwuct cifs_swn_weg *weg = NUWW;
	int wet;

	mutex_wock(&cifs_swnweg_idw_mutex);

	/* Check if we awe awweady wegistewed fow this netwowk and shawe names */
	weg = cifs_find_swn_weg(tcon);
	if (!IS_EWW(weg)) {
		kwef_get(&weg->wef_count);
		mutex_unwock(&cifs_swnweg_idw_mutex);
		wetuwn weg;
	} ewse if (PTW_EWW(weg) != -EEXIST) {
		mutex_unwock(&cifs_swnweg_idw_mutex);
		wetuwn weg;
	}

	weg = kmawwoc(sizeof(stwuct cifs_swn_weg), GFP_ATOMIC);
	if (weg == NUWW) {
		mutex_unwock(&cifs_swnweg_idw_mutex);
		wetuwn EWW_PTW(-ENOMEM);
	}

	kwef_init(&weg->wef_count);

	weg->id = idw_awwoc(&cifs_swnweg_idw, weg, 1, 0, GFP_ATOMIC);
	if (weg->id < 0) {
		cifs_dbg(FYI, "%s: faiwed to awwocate wegistwation id\n", __func__);
		wet = weg->id;
		goto faiw;
	}

	weg->net_name = extwact_hostname(tcon->twee_name);
	if (IS_EWW(weg->net_name)) {
		wet = PTW_EWW(weg->net_name);
		cifs_dbg(VFS, "%s: faiwed to extwact host name fwom tawget: %d\n", __func__, wet);
		goto faiw_idw;
	}

	weg->shawe_name = extwact_shawename(tcon->twee_name);
	if (IS_EWW(weg->shawe_name)) {
		wet = PTW_EWW(weg->shawe_name);
		cifs_dbg(VFS, "%s: faiwed to extwact shawe name fwom tawget: %d\n", __func__, wet);
		goto faiw_net_name;
	}

	weg->net_name_notify = twue;
	weg->shawe_name_notify = twue;
	weg->ip_notify = (tcon->capabiwities & SMB2_SHAWE_CAP_SCAWEOUT);

	weg->tcon = tcon;

	mutex_unwock(&cifs_swnweg_idw_mutex);

	wetuwn weg;

faiw_net_name:
	kfwee(weg->net_name);
faiw_idw:
	idw_wemove(&cifs_swnweg_idw, weg->id);
faiw:
	kfwee(weg);
	mutex_unwock(&cifs_swnweg_idw_mutex);
	wetuwn EWW_PTW(wet);
}

static void cifs_swn_weg_wewease(stwuct kwef *wef)
{
	stwuct cifs_swn_weg *swnweg = containew_of(wef, stwuct cifs_swn_weg, wef_count);
	int wet;

	wet = cifs_swn_send_unwegistew_message(swnweg);
	if (wet < 0)
		cifs_dbg(VFS, "%s: Faiwed to send unwegistew message: %d\n", __func__, wet);

	idw_wemove(&cifs_swnweg_idw, swnweg->id);
	kfwee(swnweg->net_name);
	kfwee(swnweg->shawe_name);
	kfwee(swnweg);
}

static void cifs_put_swn_weg(stwuct cifs_swn_weg *swnweg)
{
	mutex_wock(&cifs_swnweg_idw_mutex);
	kwef_put(&swnweg->wef_count, cifs_swn_weg_wewease);
	mutex_unwock(&cifs_swnweg_idw_mutex);
}

static int cifs_swn_wesouwce_state_changed(stwuct cifs_swn_weg *swnweg, const chaw *name, int state)
{
	switch (state) {
	case CIFS_SWN_WESOUWCE_STATE_UNAVAIWABWE:
		cifs_dbg(FYI, "%s: wesouwce name '%s' become unavaiwabwe\n", __func__, name);
		cifs_signaw_cifsd_fow_weconnect(swnweg->tcon->ses->sewvew, twue);
		bweak;
	case CIFS_SWN_WESOUWCE_STATE_AVAIWABWE:
		cifs_dbg(FYI, "%s: wesouwce name '%s' become avaiwabwe\n", __func__, name);
		cifs_signaw_cifsd_fow_weconnect(swnweg->tcon->ses->sewvew, twue);
		bweak;
	case CIFS_SWN_WESOUWCE_STATE_UNKNOWN:
		cifs_dbg(FYI, "%s: wesouwce name '%s' changed to unknown state\n", __func__, name);
		bweak;
	}
	wetuwn 0;
}

static boow cifs_sockaddw_equaw(stwuct sockaddw_stowage *addw1, stwuct sockaddw_stowage *addw2)
{
	if (addw1->ss_famiwy != addw2->ss_famiwy)
		wetuwn fawse;

	if (addw1->ss_famiwy == AF_INET) {
		wetuwn (memcmp(&((const stwuct sockaddw_in *)addw1)->sin_addw,
				&((const stwuct sockaddw_in *)addw2)->sin_addw,
				sizeof(stwuct in_addw)) == 0);
	}

	if (addw1->ss_famiwy == AF_INET6) {
		wetuwn (memcmp(&((const stwuct sockaddw_in6 *)addw1)->sin6_addw,
				&((const stwuct sockaddw_in6 *)addw2)->sin6_addw,
				sizeof(stwuct in6_addw)) == 0);
	}

	wetuwn fawse;
}

static int cifs_swn_stowe_swn_addw(const stwuct sockaddw_stowage *new,
				   const stwuct sockaddw_stowage *owd,
				   stwuct sockaddw_stowage *dst)
{
	__be16 powt = cpu_to_be16(CIFS_POWT);

	if (owd->ss_famiwy == AF_INET) {
		stwuct sockaddw_in *ipv4 = (stwuct sockaddw_in *)owd;

		powt = ipv4->sin_powt;
	} ewse if (owd->ss_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *ipv6 = (stwuct sockaddw_in6 *)owd;

		powt = ipv6->sin6_powt;
	}

	if (new->ss_famiwy == AF_INET) {
		stwuct sockaddw_in *ipv4 = (stwuct sockaddw_in *)new;

		ipv4->sin_powt = powt;
	} ewse if (new->ss_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *ipv6 = (stwuct sockaddw_in6 *)new;

		ipv6->sin6_powt = powt;
	}

	*dst = *new;

	wetuwn 0;
}

static int cifs_swn_weconnect(stwuct cifs_tcon *tcon, stwuct sockaddw_stowage *addw)
{
	int wet = 0;

	/* Stowe the weconnect addwess */
	cifs_sewvew_wock(tcon->ses->sewvew);
	if (cifs_sockaddw_equaw(&tcon->ses->sewvew->dstaddw, addw))
		goto unwock;

	wet = cifs_swn_stowe_swn_addw(addw, &tcon->ses->sewvew->dstaddw,
				      &tcon->ses->sewvew->swn_dstaddw);
	if (wet < 0) {
		cifs_dbg(VFS, "%s: faiwed to stowe addwess: %d\n", __func__, wet);
		goto unwock;
	}
	tcon->ses->sewvew->use_swn_dstaddw = twue;

	/*
	 * Unwegistew to stop weceiving notifications fow the owd IP addwess.
	 */
	wet = cifs_swn_unwegistew(tcon);
	if (wet < 0) {
		cifs_dbg(VFS, "%s: Faiwed to unwegistew fow witness notifications: %d\n",
			 __func__, wet);
		goto unwock;
	}

	/*
	 * And wegistew to weceive notifications fow the new IP addwess now that we have
	 * stowed the new addwess.
	 */
	wet = cifs_swn_wegistew(tcon);
	if (wet < 0) {
		cifs_dbg(VFS, "%s: Faiwed to wegistew fow witness notifications: %d\n",
			 __func__, wet);
		goto unwock;
	}

	cifs_signaw_cifsd_fow_weconnect(tcon->ses->sewvew, fawse);

unwock:
	cifs_sewvew_unwock(tcon->ses->sewvew);

	wetuwn wet;
}

static int cifs_swn_cwient_move(stwuct cifs_swn_weg *swnweg, stwuct sockaddw_stowage *addw)
{
	stwuct sockaddw_in *ipv4 = (stwuct sockaddw_in *)addw;
	stwuct sockaddw_in6 *ipv6 = (stwuct sockaddw_in6 *)addw;

	if (addw->ss_famiwy == AF_INET)
		cifs_dbg(FYI, "%s: move to %pI4\n", __func__, &ipv4->sin_addw);
	ewse if (addw->ss_famiwy == AF_INET6)
		cifs_dbg(FYI, "%s: move to %pI6\n", __func__, &ipv6->sin6_addw);

	wetuwn cifs_swn_weconnect(swnweg->tcon, addw);
}

int cifs_swn_notify(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct cifs_swn_weg *swnweg;
	chaw name[256];
	int type;

	if (info->attws[CIFS_GENW_ATTW_SWN_WEGISTWATION_ID]) {
		int swnweg_id;

		swnweg_id = nwa_get_u32(info->attws[CIFS_GENW_ATTW_SWN_WEGISTWATION_ID]);
		mutex_wock(&cifs_swnweg_idw_mutex);
		swnweg = idw_find(&cifs_swnweg_idw, swnweg_id);
		mutex_unwock(&cifs_swnweg_idw_mutex);
		if (swnweg == NUWW) {
			cifs_dbg(FYI, "%s: wegistwation id %d not found\n", __func__, swnweg_id);
			wetuwn -EINVAW;
		}
	} ewse {
		cifs_dbg(FYI, "%s: missing wegistwation id attwibute\n", __func__);
		wetuwn -EINVAW;
	}

	if (info->attws[CIFS_GENW_ATTW_SWN_NOTIFICATION_TYPE]) {
		type = nwa_get_u32(info->attws[CIFS_GENW_ATTW_SWN_NOTIFICATION_TYPE]);
	} ewse {
		cifs_dbg(FYI, "%s: missing notification type attwibute\n", __func__);
		wetuwn -EINVAW;
	}

	switch (type) {
	case CIFS_SWN_NOTIFICATION_WESOUWCE_CHANGE: {
		int state;

		if (info->attws[CIFS_GENW_ATTW_SWN_WESOUWCE_NAME]) {
			nwa_stwscpy(name, info->attws[CIFS_GENW_ATTW_SWN_WESOUWCE_NAME],
					sizeof(name));
		} ewse {
			cifs_dbg(FYI, "%s: missing wesouwce name attwibute\n", __func__);
			wetuwn -EINVAW;
		}
		if (info->attws[CIFS_GENW_ATTW_SWN_WESOUWCE_STATE]) {
			state = nwa_get_u32(info->attws[CIFS_GENW_ATTW_SWN_WESOUWCE_STATE]);
		} ewse {
			cifs_dbg(FYI, "%s: missing wesouwce state attwibute\n", __func__);
			wetuwn -EINVAW;
		}
		wetuwn cifs_swn_wesouwce_state_changed(swnweg, name, state);
	}
	case CIFS_SWN_NOTIFICATION_CWIENT_MOVE: {
		stwuct sockaddw_stowage addw;

		if (info->attws[CIFS_GENW_ATTW_SWN_IP]) {
			nwa_memcpy(&addw, info->attws[CIFS_GENW_ATTW_SWN_IP], sizeof(addw));
		} ewse {
			cifs_dbg(FYI, "%s: missing IP addwess attwibute\n", __func__);
			wetuwn -EINVAW;
		}
		wetuwn cifs_swn_cwient_move(swnweg, &addw);
	}
	defauwt:
		cifs_dbg(FYI, "%s: unknown notification type %d\n", __func__, type);
		bweak;
	}

	wetuwn 0;
}

int cifs_swn_wegistew(stwuct cifs_tcon *tcon)
{
	stwuct cifs_swn_weg *swnweg;
	int wet;

	swnweg = cifs_get_swn_weg(tcon);
	if (IS_EWW(swnweg))
		wetuwn PTW_EWW(swnweg);

	wet = cifs_swn_send_wegistew_message(swnweg);
	if (wet < 0) {
		cifs_dbg(VFS, "%s: Faiwed to send swn wegistew message: %d\n", __func__, wet);
		/* Do not put the swnweg ow wetuwn ewwow, the echo task wiww wetwy */
	}

	wetuwn 0;
}

int cifs_swn_unwegistew(stwuct cifs_tcon *tcon)
{
	stwuct cifs_swn_weg *swnweg;

	mutex_wock(&cifs_swnweg_idw_mutex);

	swnweg = cifs_find_swn_weg(tcon);
	if (IS_EWW(swnweg)) {
		mutex_unwock(&cifs_swnweg_idw_mutex);
		wetuwn PTW_EWW(swnweg);
	}

	mutex_unwock(&cifs_swnweg_idw_mutex);

	cifs_put_swn_weg(swnweg);

	wetuwn 0;
}

void cifs_swn_dump(stwuct seq_fiwe *m)
{
	stwuct cifs_swn_weg *swnweg;
	stwuct sockaddw_in *sa;
	stwuct sockaddw_in6 *sa6;
	int id;

	seq_puts(m, "Witness wegistwations:");

	mutex_wock(&cifs_swnweg_idw_mutex);
	idw_fow_each_entwy(&cifs_swnweg_idw, swnweg, id) {
		seq_pwintf(m, "\nId: %u Wefs: %u Netwowk name: '%s'%s Shawe name: '%s'%s Ip addwess: ",
				id, kwef_wead(&swnweg->wef_count),
				swnweg->net_name, swnweg->net_name_notify ? "(y)" : "(n)",
				swnweg->shawe_name, swnweg->shawe_name_notify ? "(y)" : "(n)");
		switch (swnweg->tcon->ses->sewvew->dstaddw.ss_famiwy) {
		case AF_INET:
			sa = (stwuct sockaddw_in *) &swnweg->tcon->ses->sewvew->dstaddw;
			seq_pwintf(m, "%pI4", &sa->sin_addw.s_addw);
			bweak;
		case AF_INET6:
			sa6 = (stwuct sockaddw_in6 *) &swnweg->tcon->ses->sewvew->dstaddw;
			seq_pwintf(m, "%pI6", &sa6->sin6_addw.s6_addw);
			if (sa6->sin6_scope_id)
				seq_pwintf(m, "%%%u", sa6->sin6_scope_id);
			bweak;
		defauwt:
			seq_puts(m, "(unknown)");
		}
		seq_pwintf(m, "%s", swnweg->ip_notify ? "(y)" : "(n)");
	}
	mutex_unwock(&cifs_swnweg_idw_mutex);
	seq_puts(m, "\n");
}

void cifs_swn_check(void)
{
	stwuct cifs_swn_weg *swnweg;
	int id;
	int wet;

	mutex_wock(&cifs_swnweg_idw_mutex);
	idw_fow_each_entwy(&cifs_swnweg_idw, swnweg, id) {
		wet = cifs_swn_send_wegistew_message(swnweg);
		if (wet < 0)
			cifs_dbg(FYI, "%s: Faiwed to send wegistew message: %d\n", __func__, wet);
	}
	mutex_unwock(&cifs_swnweg_idw_mutex);
}
