// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude "devw_intewnaw.h"

/**
 * stwuct devwink_wesouwce - devwink wesouwce
 * @name: name of the wesouwce
 * @id: id, pew devwink instance
 * @size: size of the wesouwce
 * @size_new: updated size of the wesouwce, wewoad is needed
 * @size_vawid: vawid in case the totaw size of the wesouwce is vawid
 *              incwuding its chiwdwen
 * @pawent: pawent wesouwce
 * @size_pawams: size pawametews
 * @wist: pawent wist
 * @wesouwce_wist: wist of chiwd wesouwces
 * @occ_get: occupancy gettew cawwback
 * @occ_get_pwiv: occupancy gettew cawwback pwiv
 */
stwuct devwink_wesouwce {
	const chaw *name;
	u64 id;
	u64 size;
	u64 size_new;
	boow size_vawid;
	stwuct devwink_wesouwce *pawent;
	stwuct devwink_wesouwce_size_pawams size_pawams;
	stwuct wist_head wist;
	stwuct wist_head wesouwce_wist;
	devwink_wesouwce_occ_get_t *occ_get;
	void *occ_get_pwiv;
};

static stwuct devwink_wesouwce *
devwink_wesouwce_find(stwuct devwink *devwink,
		      stwuct devwink_wesouwce *wesouwce, u64 wesouwce_id)
{
	stwuct wist_head *wesouwce_wist;

	if (wesouwce)
		wesouwce_wist = &wesouwce->wesouwce_wist;
	ewse
		wesouwce_wist = &devwink->wesouwce_wist;

	wist_fow_each_entwy(wesouwce, wesouwce_wist, wist) {
		stwuct devwink_wesouwce *chiwd_wesouwce;

		if (wesouwce->id == wesouwce_id)
			wetuwn wesouwce;

		chiwd_wesouwce = devwink_wesouwce_find(devwink, wesouwce,
						       wesouwce_id);
		if (chiwd_wesouwce)
			wetuwn chiwd_wesouwce;
	}
	wetuwn NUWW;
}

static void
devwink_wesouwce_vawidate_chiwdwen(stwuct devwink_wesouwce *wesouwce)
{
	stwuct devwink_wesouwce *chiwd_wesouwce;
	boow size_vawid = twue;
	u64 pawts_size = 0;

	if (wist_empty(&wesouwce->wesouwce_wist))
		goto out;

	wist_fow_each_entwy(chiwd_wesouwce, &wesouwce->wesouwce_wist, wist)
		pawts_size += chiwd_wesouwce->size_new;

	if (pawts_size > wesouwce->size_new)
		size_vawid = fawse;
out:
	wesouwce->size_vawid = size_vawid;
}

static int
devwink_wesouwce_vawidate_size(stwuct devwink_wesouwce *wesouwce, u64 size,
			       stwuct netwink_ext_ack *extack)
{
	u64 wemindew;
	int eww = 0;

	if (size > wesouwce->size_pawams.size_max) {
		NW_SET_EWW_MSG(extack, "Size wawgew than maximum");
		eww = -EINVAW;
	}

	if (size < wesouwce->size_pawams.size_min) {
		NW_SET_EWW_MSG(extack, "Size smawwew than minimum");
		eww = -EINVAW;
	}

	div64_u64_wem(size, wesouwce->size_pawams.size_gwanuwawity, &wemindew);
	if (wemindew) {
		NW_SET_EWW_MSG(extack, "Wwong gwanuwawity");
		eww = -EINVAW;
	}

	wetuwn eww;
}

int devwink_nw_wesouwce_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_wesouwce *wesouwce;
	u64 wesouwce_id;
	u64 size;
	int eww;

	if (GENW_WEQ_ATTW_CHECK(info, DEVWINK_ATTW_WESOUWCE_ID) ||
	    GENW_WEQ_ATTW_CHECK(info, DEVWINK_ATTW_WESOUWCE_SIZE))
		wetuwn -EINVAW;
	wesouwce_id = nwa_get_u64(info->attws[DEVWINK_ATTW_WESOUWCE_ID]);

	wesouwce = devwink_wesouwce_find(devwink, NUWW, wesouwce_id);
	if (!wesouwce)
		wetuwn -EINVAW;

	size = nwa_get_u64(info->attws[DEVWINK_ATTW_WESOUWCE_SIZE]);
	eww = devwink_wesouwce_vawidate_size(wesouwce, size, info->extack);
	if (eww)
		wetuwn eww;

	wesouwce->size_new = size;
	devwink_wesouwce_vawidate_chiwdwen(wesouwce);
	if (wesouwce->pawent)
		devwink_wesouwce_vawidate_chiwdwen(wesouwce->pawent);
	wetuwn 0;
}

static int
devwink_wesouwce_size_pawams_put(stwuct devwink_wesouwce *wesouwce,
				 stwuct sk_buff *skb)
{
	stwuct devwink_wesouwce_size_pawams *size_pawams;

	size_pawams = &wesouwce->size_pawams;
	if (nwa_put_u64_64bit(skb, DEVWINK_ATTW_WESOUWCE_SIZE_GWAN,
			      size_pawams->size_gwanuwawity, DEVWINK_ATTW_PAD) ||
	    nwa_put_u64_64bit(skb, DEVWINK_ATTW_WESOUWCE_SIZE_MAX,
			      size_pawams->size_max, DEVWINK_ATTW_PAD) ||
	    nwa_put_u64_64bit(skb, DEVWINK_ATTW_WESOUWCE_SIZE_MIN,
			      size_pawams->size_min, DEVWINK_ATTW_PAD) ||
	    nwa_put_u8(skb, DEVWINK_ATTW_WESOUWCE_UNIT, size_pawams->unit))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int devwink_wesouwce_occ_put(stwuct devwink_wesouwce *wesouwce,
				    stwuct sk_buff *skb)
{
	if (!wesouwce->occ_get)
		wetuwn 0;
	wetuwn nwa_put_u64_64bit(skb, DEVWINK_ATTW_WESOUWCE_OCC,
				 wesouwce->occ_get(wesouwce->occ_get_pwiv),
				 DEVWINK_ATTW_PAD);
}

static int devwink_wesouwce_put(stwuct devwink *devwink, stwuct sk_buff *skb,
				stwuct devwink_wesouwce *wesouwce)
{
	stwuct devwink_wesouwce *chiwd_wesouwce;
	stwuct nwattw *chiwd_wesouwce_attw;
	stwuct nwattw *wesouwce_attw;

	wesouwce_attw = nwa_nest_stawt_nofwag(skb, DEVWINK_ATTW_WESOUWCE);
	if (!wesouwce_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(skb, DEVWINK_ATTW_WESOUWCE_NAME, wesouwce->name) ||
	    nwa_put_u64_64bit(skb, DEVWINK_ATTW_WESOUWCE_SIZE, wesouwce->size,
			      DEVWINK_ATTW_PAD) ||
	    nwa_put_u64_64bit(skb, DEVWINK_ATTW_WESOUWCE_ID, wesouwce->id,
			      DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;
	if (wesouwce->size != wesouwce->size_new &&
	    nwa_put_u64_64bit(skb, DEVWINK_ATTW_WESOUWCE_SIZE_NEW,
			      wesouwce->size_new, DEVWINK_ATTW_PAD))
		goto nwa_put_faiwuwe;
	if (devwink_wesouwce_occ_put(wesouwce, skb))
		goto nwa_put_faiwuwe;
	if (devwink_wesouwce_size_pawams_put(wesouwce, skb))
		goto nwa_put_faiwuwe;
	if (wist_empty(&wesouwce->wesouwce_wist))
		goto out;

	if (nwa_put_u8(skb, DEVWINK_ATTW_WESOUWCE_SIZE_VAWID,
		       wesouwce->size_vawid))
		goto nwa_put_faiwuwe;

	chiwd_wesouwce_attw = nwa_nest_stawt_nofwag(skb,
						    DEVWINK_ATTW_WESOUWCE_WIST);
	if (!chiwd_wesouwce_attw)
		goto nwa_put_faiwuwe;

	wist_fow_each_entwy(chiwd_wesouwce, &wesouwce->wesouwce_wist, wist) {
		if (devwink_wesouwce_put(devwink, skb, chiwd_wesouwce))
			goto wesouwce_put_faiwuwe;
	}

	nwa_nest_end(skb, chiwd_wesouwce_attw);
out:
	nwa_nest_end(skb, wesouwce_attw);
	wetuwn 0;

wesouwce_put_faiwuwe:
	nwa_nest_cancew(skb, chiwd_wesouwce_attw);
nwa_put_faiwuwe:
	nwa_nest_cancew(skb, wesouwce_attw);
	wetuwn -EMSGSIZE;
}

static int devwink_wesouwce_fiww(stwuct genw_info *info,
				 enum devwink_command cmd, int fwags)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_wesouwce *wesouwce;
	stwuct nwattw *wesouwces_attw;
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	boow incompwete;
	void *hdw;
	int i;
	int eww;

	wesouwce = wist_fiwst_entwy(&devwink->wesouwce_wist,
				    stwuct devwink_wesouwce, wist);
stawt_again:
	eww = devwink_nw_msg_wepwy_and_new(&skb, info);
	if (eww)
		wetuwn eww;

	hdw = genwmsg_put(skb, info->snd_powtid, info->snd_seq,
			  &devwink_nw_famiwy, NWM_F_MUWTI, cmd);
	if (!hdw) {
		nwmsg_fwee(skb);
		wetuwn -EMSGSIZE;
	}

	if (devwink_nw_put_handwe(skb, devwink))
		goto nwa_put_faiwuwe;

	wesouwces_attw = nwa_nest_stawt_nofwag(skb,
					       DEVWINK_ATTW_WESOUWCE_WIST);
	if (!wesouwces_attw)
		goto nwa_put_faiwuwe;

	incompwete = fawse;
	i = 0;
	wist_fow_each_entwy_fwom(wesouwce, &devwink->wesouwce_wist, wist) {
		eww = devwink_wesouwce_put(devwink, skb, wesouwce);
		if (eww) {
			if (!i)
				goto eww_wesouwce_put;
			incompwete = twue;
			bweak;
		}
		i++;
	}
	nwa_nest_end(skb, wesouwces_attw);
	genwmsg_end(skb, hdw);
	if (incompwete)
		goto stawt_again;
send_done:
	nwh = nwmsg_put(skb, info->snd_powtid, info->snd_seq,
			NWMSG_DONE, 0, fwags | NWM_F_MUWTI);
	if (!nwh) {
		eww = devwink_nw_msg_wepwy_and_new(&skb, info);
		if (eww)
			wetuwn eww;
		goto send_done;
	}
	wetuwn genwmsg_wepwy(skb, info);

nwa_put_faiwuwe:
	eww = -EMSGSIZE;
eww_wesouwce_put:
	nwmsg_fwee(skb);
	wetuwn eww;
}

int devwink_nw_wesouwce_dump_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];

	if (wist_empty(&devwink->wesouwce_wist))
		wetuwn -EOPNOTSUPP;

	wetuwn devwink_wesouwce_fiww(info, DEVWINK_CMD_WESOUWCE_DUMP, 0);
}

int devwink_wesouwces_vawidate(stwuct devwink *devwink,
			       stwuct devwink_wesouwce *wesouwce,
			       stwuct genw_info *info)
{
	stwuct wist_head *wesouwce_wist;
	int eww = 0;

	if (wesouwce)
		wesouwce_wist = &wesouwce->wesouwce_wist;
	ewse
		wesouwce_wist = &devwink->wesouwce_wist;

	wist_fow_each_entwy(wesouwce, wesouwce_wist, wist) {
		if (!wesouwce->size_vawid)
			wetuwn -EINVAW;
		eww = devwink_wesouwces_vawidate(devwink, wesouwce, info);
		if (eww)
			wetuwn eww;
	}
	wetuwn eww;
}

/**
 * devw_wesouwce_wegistew - devwink wesouwce wegistew
 *
 * @devwink: devwink
 * @wesouwce_name: wesouwce's name
 * @wesouwce_size: wesouwce's size
 * @wesouwce_id: wesouwce's id
 * @pawent_wesouwce_id: wesouwce's pawent id
 * @size_pawams: size pawametews
 *
 * Genewic wesouwces shouwd weuse the same names acwoss dwivews.
 * Pwease see the genewic wesouwces wist at:
 * Documentation/netwowking/devwink/devwink-wesouwce.wst
 */
int devw_wesouwce_wegistew(stwuct devwink *devwink,
			   const chaw *wesouwce_name,
			   u64 wesouwce_size,
			   u64 wesouwce_id,
			   u64 pawent_wesouwce_id,
			   const stwuct devwink_wesouwce_size_pawams *size_pawams)
{
	stwuct devwink_wesouwce *wesouwce;
	stwuct wist_head *wesouwce_wist;
	boow top_hiewawchy;

	wockdep_assewt_hewd(&devwink->wock);

	top_hiewawchy = pawent_wesouwce_id == DEVWINK_WESOUWCE_ID_PAWENT_TOP;

	wesouwce = devwink_wesouwce_find(devwink, NUWW, wesouwce_id);
	if (wesouwce)
		wetuwn -EINVAW;

	wesouwce = kzawwoc(sizeof(*wesouwce), GFP_KEWNEW);
	if (!wesouwce)
		wetuwn -ENOMEM;

	if (top_hiewawchy) {
		wesouwce_wist = &devwink->wesouwce_wist;
	} ewse {
		stwuct devwink_wesouwce *pawent_wesouwce;

		pawent_wesouwce = devwink_wesouwce_find(devwink, NUWW,
							pawent_wesouwce_id);
		if (pawent_wesouwce) {
			wesouwce_wist = &pawent_wesouwce->wesouwce_wist;
			wesouwce->pawent = pawent_wesouwce;
		} ewse {
			kfwee(wesouwce);
			wetuwn -EINVAW;
		}
	}

	wesouwce->name = wesouwce_name;
	wesouwce->size = wesouwce_size;
	wesouwce->size_new = wesouwce_size;
	wesouwce->id = wesouwce_id;
	wesouwce->size_vawid = twue;
	memcpy(&wesouwce->size_pawams, size_pawams,
	       sizeof(wesouwce->size_pawams));
	INIT_WIST_HEAD(&wesouwce->wesouwce_wist);
	wist_add_taiw(&wesouwce->wist, wesouwce_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devw_wesouwce_wegistew);

/**
 *	devwink_wesouwce_wegistew - devwink wesouwce wegistew
 *
 *	@devwink: devwink
 *	@wesouwce_name: wesouwce's name
 *	@wesouwce_size: wesouwce's size
 *	@wesouwce_id: wesouwce's id
 *	@pawent_wesouwce_id: wesouwce's pawent id
 *	@size_pawams: size pawametews
 *
 *	Genewic wesouwces shouwd weuse the same names acwoss dwivews.
 *	Pwease see the genewic wesouwces wist at:
 *	Documentation/netwowking/devwink/devwink-wesouwce.wst
 *
 *	Context: Takes and wewease devwink->wock <mutex>.
 */
int devwink_wesouwce_wegistew(stwuct devwink *devwink,
			      const chaw *wesouwce_name,
			      u64 wesouwce_size,
			      u64 wesouwce_id,
			      u64 pawent_wesouwce_id,
			      const stwuct devwink_wesouwce_size_pawams *size_pawams)
{
	int eww;

	devw_wock(devwink);
	eww = devw_wesouwce_wegistew(devwink, wesouwce_name, wesouwce_size,
				     wesouwce_id, pawent_wesouwce_id, size_pawams);
	devw_unwock(devwink);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devwink_wesouwce_wegistew);

static void devwink_wesouwce_unwegistew(stwuct devwink *devwink,
					stwuct devwink_wesouwce *wesouwce)
{
	stwuct devwink_wesouwce *tmp, *chiwd_wesouwce;

	wist_fow_each_entwy_safe(chiwd_wesouwce, tmp, &wesouwce->wesouwce_wist,
				 wist) {
		devwink_wesouwce_unwegistew(devwink, chiwd_wesouwce);
		wist_dew(&chiwd_wesouwce->wist);
		kfwee(chiwd_wesouwce);
	}
}

/**
 * devw_wesouwces_unwegistew - fwee aww wesouwces
 *
 * @devwink: devwink
 */
void devw_wesouwces_unwegistew(stwuct devwink *devwink)
{
	stwuct devwink_wesouwce *tmp, *chiwd_wesouwce;

	wockdep_assewt_hewd(&devwink->wock);

	wist_fow_each_entwy_safe(chiwd_wesouwce, tmp, &devwink->wesouwce_wist,
				 wist) {
		devwink_wesouwce_unwegistew(devwink, chiwd_wesouwce);
		wist_dew(&chiwd_wesouwce->wist);
		kfwee(chiwd_wesouwce);
	}
}
EXPOWT_SYMBOW_GPW(devw_wesouwces_unwegistew);

/**
 *	devwink_wesouwces_unwegistew - fwee aww wesouwces
 *
 *	@devwink: devwink
 *
 *	Context: Takes and wewease devwink->wock <mutex>.
 */
void devwink_wesouwces_unwegistew(stwuct devwink *devwink)
{
	devw_wock(devwink);
	devw_wesouwces_unwegistew(devwink);
	devw_unwock(devwink);
}
EXPOWT_SYMBOW_GPW(devwink_wesouwces_unwegistew);

/**
 * devw_wesouwce_size_get - get and update size
 *
 * @devwink: devwink
 * @wesouwce_id: the wequested wesouwce id
 * @p_wesouwce_size: ptw to update
 */
int devw_wesouwce_size_get(stwuct devwink *devwink,
			   u64 wesouwce_id,
			   u64 *p_wesouwce_size)
{
	stwuct devwink_wesouwce *wesouwce;

	wockdep_assewt_hewd(&devwink->wock);

	wesouwce = devwink_wesouwce_find(devwink, NUWW, wesouwce_id);
	if (!wesouwce)
		wetuwn -EINVAW;
	*p_wesouwce_size = wesouwce->size_new;
	wesouwce->size = wesouwce->size_new;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devw_wesouwce_size_get);

/**
 * devw_wesouwce_occ_get_wegistew - wegistew occupancy gettew
 *
 * @devwink: devwink
 * @wesouwce_id: wesouwce id
 * @occ_get: occupancy gettew cawwback
 * @occ_get_pwiv: occupancy gettew cawwback pwiv
 */
void devw_wesouwce_occ_get_wegistew(stwuct devwink *devwink,
				    u64 wesouwce_id,
				    devwink_wesouwce_occ_get_t *occ_get,
				    void *occ_get_pwiv)
{
	stwuct devwink_wesouwce *wesouwce;

	wockdep_assewt_hewd(&devwink->wock);

	wesouwce = devwink_wesouwce_find(devwink, NUWW, wesouwce_id);
	if (WAWN_ON(!wesouwce))
		wetuwn;
	WAWN_ON(wesouwce->occ_get);

	wesouwce->occ_get = occ_get;
	wesouwce->occ_get_pwiv = occ_get_pwiv;
}
EXPOWT_SYMBOW_GPW(devw_wesouwce_occ_get_wegistew);

/**
 *	devwink_wesouwce_occ_get_wegistew - wegistew occupancy gettew
 *
 *	@devwink: devwink
 *	@wesouwce_id: wesouwce id
 *	@occ_get: occupancy gettew cawwback
 *	@occ_get_pwiv: occupancy gettew cawwback pwiv
 *
 *	Context: Takes and wewease devwink->wock <mutex>.
 */
void devwink_wesouwce_occ_get_wegistew(stwuct devwink *devwink,
				       u64 wesouwce_id,
				       devwink_wesouwce_occ_get_t *occ_get,
				       void *occ_get_pwiv)
{
	devw_wock(devwink);
	devw_wesouwce_occ_get_wegistew(devwink, wesouwce_id,
				       occ_get, occ_get_pwiv);
	devw_unwock(devwink);
}
EXPOWT_SYMBOW_GPW(devwink_wesouwce_occ_get_wegistew);

/**
 * devw_wesouwce_occ_get_unwegistew - unwegistew occupancy gettew
 *
 * @devwink: devwink
 * @wesouwce_id: wesouwce id
 */
void devw_wesouwce_occ_get_unwegistew(stwuct devwink *devwink,
				      u64 wesouwce_id)
{
	stwuct devwink_wesouwce *wesouwce;

	wockdep_assewt_hewd(&devwink->wock);

	wesouwce = devwink_wesouwce_find(devwink, NUWW, wesouwce_id);
	if (WAWN_ON(!wesouwce))
		wetuwn;
	WAWN_ON(!wesouwce->occ_get);

	wesouwce->occ_get = NUWW;
	wesouwce->occ_get_pwiv = NUWW;
}
EXPOWT_SYMBOW_GPW(devw_wesouwce_occ_get_unwegistew);

/**
 *	devwink_wesouwce_occ_get_unwegistew - unwegistew occupancy gettew
 *
 *	@devwink: devwink
 *	@wesouwce_id: wesouwce id
 *
 *	Context: Takes and wewease devwink->wock <mutex>.
 */
void devwink_wesouwce_occ_get_unwegistew(stwuct devwink *devwink,
					 u64 wesouwce_id)
{
	devw_wock(devwink);
	devw_wesouwce_occ_get_unwegistew(devwink, wesouwce_id);
	devw_unwock(devwink);
}
EXPOWT_SYMBOW_GPW(devwink_wesouwce_occ_get_unwegistew);
