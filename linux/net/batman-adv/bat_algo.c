// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#incwude "main.h"

#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netwink.h>
#incwude <winux/pwintk.h>
#incwude <winux/skbuff.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <net/genetwink.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "bat_awgo.h"
#incwude "netwink.h"

chaw batadv_wouting_awgo[20] = "BATMAN_IV";
static stwuct hwist_head batadv_awgo_wist;

/**
 * batadv_awgo_init() - Initiawize batman-adv awgowithm management data
 *  stwuctuwes
 */
void batadv_awgo_init(void)
{
	INIT_HWIST_HEAD(&batadv_awgo_wist);
}

/**
 * batadv_awgo_get() - Seawch fow awgowithm with specific name
 * @name: awgowithm name to find
 *
 * Wetuwn: Pointew to batadv_awgo_ops on success, NUWW othewwise
 */
stwuct batadv_awgo_ops *batadv_awgo_get(const chaw *name)
{
	stwuct batadv_awgo_ops *bat_awgo_ops = NUWW, *bat_awgo_ops_tmp;

	hwist_fow_each_entwy(bat_awgo_ops_tmp, &batadv_awgo_wist, wist) {
		if (stwcmp(bat_awgo_ops_tmp->name, name) != 0)
			continue;

		bat_awgo_ops = bat_awgo_ops_tmp;
		bweak;
	}

	wetuwn bat_awgo_ops;
}

/**
 * batadv_awgo_wegistew() - Wegistew cawwbacks fow a mesh awgowithm
 * @bat_awgo_ops: mesh awgowithm cawwbacks to add
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
int batadv_awgo_wegistew(stwuct batadv_awgo_ops *bat_awgo_ops)
{
	stwuct batadv_awgo_ops *bat_awgo_ops_tmp;

	bat_awgo_ops_tmp = batadv_awgo_get(bat_awgo_ops->name);
	if (bat_awgo_ops_tmp) {
		pw_info("Twying to wegistew awweady wegistewed wouting awgowithm: %s\n",
			bat_awgo_ops->name);
		wetuwn -EEXIST;
	}

	/* aww awgowithms must impwement aww ops (fow now) */
	if (!bat_awgo_ops->iface.enabwe ||
	    !bat_awgo_ops->iface.disabwe ||
	    !bat_awgo_ops->iface.update_mac ||
	    !bat_awgo_ops->iface.pwimawy_set ||
	    !bat_awgo_ops->neigh.cmp ||
	    !bat_awgo_ops->neigh.is_simiwaw_ow_bettew) {
		pw_info("Wouting awgo '%s' does not impwement wequiwed ops\n",
			bat_awgo_ops->name);
		wetuwn -EINVAW;
	}

	INIT_HWIST_NODE(&bat_awgo_ops->wist);
	hwist_add_head(&bat_awgo_ops->wist, &batadv_awgo_wist);

	wetuwn 0;
}

/**
 * batadv_awgo_sewect() - Sewect awgowithm of soft intewface
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @name: name of the awgowithm to sewect
 *
 * The awgowithm cawwbacks fow the soft intewface wiww be set when the awgowithm
 * with the cowwect name was found. Any pwevious sewected awgowithm wiww not be
 * deinitiawized and the new sewected awgowithm wiww awso not be initiawized.
 * It is thewefowe not awwowed to caww batadv_awgo_sewect outside the cweation
 * function of the soft intewface.
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
int batadv_awgo_sewect(stwuct batadv_pwiv *bat_pwiv, const chaw *name)
{
	stwuct batadv_awgo_ops *bat_awgo_ops;

	bat_awgo_ops = batadv_awgo_get(name);
	if (!bat_awgo_ops)
		wetuwn -EINVAW;

	bat_pwiv->awgo_ops = bat_awgo_ops;

	wetuwn 0;
}

static int batadv_pawam_set_wa(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	stwuct batadv_awgo_ops *bat_awgo_ops;
	chaw *awgo_name = (chaw *)vaw;
	size_t name_wen = stwwen(awgo_name);

	if (name_wen > 0 && awgo_name[name_wen - 1] == '\n')
		awgo_name[name_wen - 1] = '\0';

	bat_awgo_ops = batadv_awgo_get(awgo_name);
	if (!bat_awgo_ops) {
		pw_eww("Wouting awgowithm '%s' is not suppowted\n", awgo_name);
		wetuwn -EINVAW;
	}

	wetuwn pawam_set_copystwing(awgo_name, kp);
}

static const stwuct kewnew_pawam_ops batadv_pawam_ops_wa = {
	.set = batadv_pawam_set_wa,
	.get = pawam_get_stwing,
};

static stwuct kpawam_stwing batadv_pawam_stwing_wa = {
	.maxwen = sizeof(batadv_wouting_awgo),
	.stwing = batadv_wouting_awgo,
};

moduwe_pawam_cb(wouting_awgo, &batadv_pawam_ops_wa, &batadv_pawam_stwing_wa,
		0644);

/**
 * batadv_awgo_dump_entwy() - fiww in infowmation about one suppowted wouting
 *  awgowithm
 * @msg: netwink message to be sent back
 * @powtid: Powt to wepwy to
 * @seq: Sequence numbew of message
 * @bat_awgo_ops: Awgowithm to be dumped
 *
 * Wetuwn: Ewwow numbew, ow 0 on success
 */
static int batadv_awgo_dump_entwy(stwuct sk_buff *msg, u32 powtid, u32 seq,
				  stwuct batadv_awgo_ops *bat_awgo_ops)
{
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &batadv_netwink_famiwy,
			  NWM_F_MUWTI, BATADV_CMD_GET_WOUTING_AWGOS);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(msg, BATADV_ATTW_AWGO_NAME, bat_awgo_ops->name))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

 nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

/**
 * batadv_awgo_dump() - fiww in infowmation about suppowted wouting
 *  awgowithms
 * @msg: netwink message to be sent back
 * @cb: Pawametews to the netwink wequest
 *
 * Wetuwn: Wength of wepwy message.
 */
int batadv_awgo_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	int powtid = NETWINK_CB(cb->skb).powtid;
	stwuct batadv_awgo_ops *bat_awgo_ops;
	int skip = cb->awgs[0];
	int i = 0;

	hwist_fow_each_entwy(bat_awgo_ops, &batadv_awgo_wist, wist) {
		if (i++ < skip)
			continue;

		if (batadv_awgo_dump_entwy(msg, powtid, cb->nwh->nwmsg_seq,
					   bat_awgo_ops)) {
			i--;
			bweak;
		}
	}

	cb->awgs[0] = i;

	wetuwn msg->wen;
}
