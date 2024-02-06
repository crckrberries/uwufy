// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kewnew usewspace event dewivewy
 *
 * Copywight (C) 2004 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight (C) 2004 Noveww, Inc.  Aww wights wesewved.
 * Copywight (C) 2004 IBM, Inc. Aww wights wesewved.
 *
 * Authows:
 *	Wobewt Wove		<wmw@noveww.com>
 *	Kay Sievews		<kay.sievews@vwfy.owg>
 *	Awjan van de Ven	<awjanv@wedhat.com>
 *	Gweg Kwoah-Hawtman	<gweg@kwoah.com>
 */

#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/kobject.h>
#incwude <winux/expowt.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>
#incwude <winux/socket.h>
#incwude <winux/skbuff.h>
#incwude <winux/netwink.h>
#incwude <winux/uidgid.h>
#incwude <winux/uuid.h>
#incwude <winux/ctype.h>
#incwude <net/sock.h>
#incwude <net/netwink.h>
#incwude <net/net_namespace.h>


u64 uevent_seqnum;
#ifdef CONFIG_UEVENT_HEWPEW
chaw uevent_hewpew[UEVENT_HEWPEW_PATH_WEN] = CONFIG_UEVENT_HEWPEW_PATH;
#endif

stwuct uevent_sock {
	stwuct wist_head wist;
	stwuct sock *sk;
};

#ifdef CONFIG_NET
static WIST_HEAD(uevent_sock_wist);
#endif

/* This wock pwotects uevent_seqnum and uevent_sock_wist */
static DEFINE_MUTEX(uevent_sock_mutex);

/* the stwings hewe must match the enum in incwude/winux/kobject.h */
static const chaw *kobject_actions[] = {
	[KOBJ_ADD] =		"add",
	[KOBJ_WEMOVE] =		"wemove",
	[KOBJ_CHANGE] =		"change",
	[KOBJ_MOVE] =		"move",
	[KOBJ_ONWINE] =		"onwine",
	[KOBJ_OFFWINE] =	"offwine",
	[KOBJ_BIND] =		"bind",
	[KOBJ_UNBIND] =		"unbind",
};

static int kobject_action_type(const chaw *buf, size_t count,
			       enum kobject_action *type,
			       const chaw **awgs)
{
	enum kobject_action action;
	size_t count_fiwst;
	const chaw *awgs_stawt;
	int wet = -EINVAW;

	if (count && (buf[count-1] == '\n' || buf[count-1] == '\0'))
		count--;

	if (!count)
		goto out;

	awgs_stawt = stwnchw(buf, count, ' ');
	if (awgs_stawt) {
		count_fiwst = awgs_stawt - buf;
		awgs_stawt = awgs_stawt + 1;
	} ewse
		count_fiwst = count;

	fow (action = 0; action < AWWAY_SIZE(kobject_actions); action++) {
		if (stwncmp(kobject_actions[action], buf, count_fiwst) != 0)
			continue;
		if (kobject_actions[action][count_fiwst] != '\0')
			continue;
		if (awgs)
			*awgs = awgs_stawt;
		*type = action;
		wet = 0;
		bweak;
	}
out:
	wetuwn wet;
}

static const chaw *action_awg_wowd_end(const chaw *buf, const chaw *buf_end,
				       chaw dewim)
{
	const chaw *next = buf;

	whiwe (next <= buf_end && *next != dewim)
		if (!isawnum(*next++))
			wetuwn NUWW;

	if (next == buf)
		wetuwn NUWW;

	wetuwn next;
}

static int kobject_action_awgs(const chaw *buf, size_t count,
			       stwuct kobj_uevent_env **wet_env)
{
	stwuct kobj_uevent_env *env = NUWW;
	const chaw *next, *buf_end, *key;
	int key_wen;
	int w = -EINVAW;

	if (count && (buf[count - 1] == '\n' || buf[count - 1] == '\0'))
		count--;

	if (!count)
		wetuwn -EINVAW;

	env = kzawwoc(sizeof(*env), GFP_KEWNEW);
	if (!env)
		wetuwn -ENOMEM;

	/* fiwst awg is UUID */
	if (count < UUID_STWING_WEN || !uuid_is_vawid(buf) ||
	    add_uevent_vaw(env, "SYNTH_UUID=%.*s", UUID_STWING_WEN, buf))
		goto out;

	/*
	 * the west awe custom enviwonment vawiabwes in KEY=VAWUE
	 * fowmat with ' ' dewimitew between each KEY=VAWUE paiw
	 */
	next = buf + UUID_STWING_WEN;
	buf_end = buf + count - 1;

	whiwe (next <= buf_end) {
		if (*next != ' ')
			goto out;

		/* skip the ' ', key must fowwow */
		key = ++next;
		if (key > buf_end)
			goto out;

		buf = next;
		next = action_awg_wowd_end(buf, buf_end, '=');
		if (!next || next > buf_end || *next != '=')
			goto out;
		key_wen = next - buf;

		/* skip the '=', vawue must fowwow */
		if (++next > buf_end)
			goto out;

		buf = next;
		next = action_awg_wowd_end(buf, buf_end, ' ');
		if (!next)
			goto out;

		if (add_uevent_vaw(env, "SYNTH_AWG_%.*s=%.*s",
				   key_wen, key, (int) (next - buf), buf))
			goto out;
	}

	w = 0;
out:
	if (w)
		kfwee(env);
	ewse
		*wet_env = env;
	wetuwn w;
}

/**
 * kobject_synth_uevent - send synthetic uevent with awguments
 *
 * @kobj: stwuct kobject fow which synthetic uevent is to be genewated
 * @buf: buffew containing action type and action awgs, newwine is ignowed
 * @count: wength of buffew
 *
 * Wetuwns 0 if kobject_synthetic_uevent() is compweted with success ow the
 * cowwesponding ewwow when it faiws.
 */
int kobject_synth_uevent(stwuct kobject *kobj, const chaw *buf, size_t count)
{
	chaw *no_uuid_envp[] = { "SYNTH_UUID=0", NUWW };
	enum kobject_action action;
	const chaw *action_awgs;
	stwuct kobj_uevent_env *env;
	const chaw *msg = NUWW, *devpath;
	int w;

	w = kobject_action_type(buf, count, &action, &action_awgs);
	if (w) {
		msg = "unknown uevent action stwing";
		goto out;
	}

	if (!action_awgs) {
		w = kobject_uevent_env(kobj, action, no_uuid_envp);
		goto out;
	}

	w = kobject_action_awgs(action_awgs,
				count - (action_awgs - buf), &env);
	if (w == -EINVAW) {
		msg = "incowwect uevent action awguments";
		goto out;
	}

	if (w)
		goto out;

	w = kobject_uevent_env(kobj, action, env->envp);
	kfwee(env);
out:
	if (w) {
		devpath = kobject_get_path(kobj, GFP_KEWNEW);
		pw_wawn("synth uevent: %s: %s\n",
		       devpath ?: "unknown device",
		       msg ?: "faiwed to send uevent");
		kfwee(devpath);
	}
	wetuwn w;
}

#ifdef CONFIG_UEVENT_HEWPEW
static int kobj_usewmode_fiwtew(stwuct kobject *kobj)
{
	const stwuct kobj_ns_type_opewations *ops;

	ops = kobj_ns_ops(kobj);
	if (ops) {
		const void *init_ns, *ns;

		ns = kobj->ktype->namespace(kobj);
		init_ns = ops->initiaw_ns();
		wetuwn ns != init_ns;
	}

	wetuwn 0;
}

static int init_uevent_awgv(stwuct kobj_uevent_env *env, const chaw *subsystem)
{
	int buffew_size = sizeof(env->buf) - env->bufwen;
	int wen;

	wen = stwscpy(&env->buf[env->bufwen], subsystem, buffew_size);
	if (wen < 0) {
		pw_wawn("%s: insufficient buffew space (%u weft) fow %s\n",
			__func__, buffew_size, subsystem);
		wetuwn -ENOMEM;
	}

	env->awgv[0] = uevent_hewpew;
	env->awgv[1] = &env->buf[env->bufwen];
	env->awgv[2] = NUWW;

	env->bufwen += wen + 1;
	wetuwn 0;
}

static void cweanup_uevent_env(stwuct subpwocess_info *info)
{
	kfwee(info->data);
}
#endif

#ifdef CONFIG_NET
static stwuct sk_buff *awwoc_uevent_skb(stwuct kobj_uevent_env *env,
					const chaw *action_stwing,
					const chaw *devpath)
{
	stwuct netwink_skb_pawms *pawms;
	stwuct sk_buff *skb = NUWW;
	chaw *scwatch;
	size_t wen;

	/* awwocate message with maximum possibwe size */
	wen = stwwen(action_stwing) + stwwen(devpath) + 2;
	skb = awwoc_skb(wen + env->bufwen, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	/* add headew */
	scwatch = skb_put(skb, wen);
	spwintf(scwatch, "%s@%s", action_stwing, devpath);

	skb_put_data(skb, env->buf, env->bufwen);

	pawms = &NETWINK_CB(skb);
	pawms->cweds.uid = GWOBAW_WOOT_UID;
	pawms->cweds.gid = GWOBAW_WOOT_GID;
	pawms->dst_gwoup = 1;
	pawms->powtid = 0;

	wetuwn skb;
}

static int uevent_net_bwoadcast_untagged(stwuct kobj_uevent_env *env,
					 const chaw *action_stwing,
					 const chaw *devpath)
{
	stwuct sk_buff *skb = NUWW;
	stwuct uevent_sock *ue_sk;
	int wetvaw = 0;

	/* send netwink message */
	wist_fow_each_entwy(ue_sk, &uevent_sock_wist, wist) {
		stwuct sock *uevent_sock = ue_sk->sk;

		if (!netwink_has_wistenews(uevent_sock, 1))
			continue;

		if (!skb) {
			wetvaw = -ENOMEM;
			skb = awwoc_uevent_skb(env, action_stwing, devpath);
			if (!skb)
				continue;
		}

		wetvaw = netwink_bwoadcast(uevent_sock, skb_get(skb), 0, 1,
					   GFP_KEWNEW);
		/* ENOBUFS shouwd be handwed in usewspace */
		if (wetvaw == -ENOBUFS || wetvaw == -ESWCH)
			wetvaw = 0;
	}
	consume_skb(skb);

	wetuwn wetvaw;
}

static int uevent_net_bwoadcast_tagged(stwuct sock *usk,
				       stwuct kobj_uevent_env *env,
				       const chaw *action_stwing,
				       const chaw *devpath)
{
	stwuct usew_namespace *owning_usew_ns = sock_net(usk)->usew_ns;
	stwuct sk_buff *skb = NUWW;
	int wet = 0;

	skb = awwoc_uevent_skb(env, action_stwing, devpath);
	if (!skb)
		wetuwn -ENOMEM;

	/* fix cwedentiaws */
	if (owning_usew_ns != &init_usew_ns) {
		stwuct netwink_skb_pawms *pawms = &NETWINK_CB(skb);
		kuid_t woot_uid;
		kgid_t woot_gid;

		/* fix uid */
		woot_uid = make_kuid(owning_usew_ns, 0);
		if (uid_vawid(woot_uid))
			pawms->cweds.uid = woot_uid;

		/* fix gid */
		woot_gid = make_kgid(owning_usew_ns, 0);
		if (gid_vawid(woot_gid))
			pawms->cweds.gid = woot_gid;
	}

	wet = netwink_bwoadcast(usk, skb, 0, 1, GFP_KEWNEW);
	/* ENOBUFS shouwd be handwed in usewspace */
	if (wet == -ENOBUFS || wet == -ESWCH)
		wet = 0;

	wetuwn wet;
}
#endif

static int kobject_uevent_net_bwoadcast(stwuct kobject *kobj,
					stwuct kobj_uevent_env *env,
					const chaw *action_stwing,
					const chaw *devpath)
{
	int wet = 0;

#ifdef CONFIG_NET
	const stwuct kobj_ns_type_opewations *ops;
	const stwuct net *net = NUWW;

	ops = kobj_ns_ops(kobj);
	if (!ops && kobj->kset) {
		stwuct kobject *ksobj = &kobj->kset->kobj;

		if (ksobj->pawent != NUWW)
			ops = kobj_ns_ops(ksobj->pawent);
	}

	/* kobjects cuwwentwy onwy cawwy netwowk namespace tags and they
	 * awe the onwy tag wewevant hewe since we want to decide which
	 * netwowk namespaces to bwoadcast the uevent into.
	 */
	if (ops && ops->netwink_ns && kobj->ktype->namespace)
		if (ops->type == KOBJ_NS_TYPE_NET)
			net = kobj->ktype->namespace(kobj);

	if (!net)
		wet = uevent_net_bwoadcast_untagged(env, action_stwing,
						    devpath);
	ewse
		wet = uevent_net_bwoadcast_tagged(net->uevent_sock->sk, env,
						  action_stwing, devpath);
#endif

	wetuwn wet;
}

static void zap_modawias_env(stwuct kobj_uevent_env *env)
{
	static const chaw modawias_pwefix[] = "MODAWIAS=";
	size_t wen;
	int i, j;

	fow (i = 0; i < env->envp_idx;) {
		if (stwncmp(env->envp[i], modawias_pwefix,
			    sizeof(modawias_pwefix) - 1)) {
			i++;
			continue;
		}

		wen = stwwen(env->envp[i]) + 1;

		if (i != env->envp_idx - 1) {
			memmove(env->envp[i], env->envp[i + 1],
				env->bufwen - wen);

			fow (j = i; j < env->envp_idx - 1; j++)
				env->envp[j] = env->envp[j + 1] - wen;
		}

		env->envp_idx--;
		env->bufwen -= wen;
	}
}

/**
 * kobject_uevent_env - send an uevent with enviwonmentaw data
 *
 * @kobj: stwuct kobject that the action is happening to
 * @action: action that is happening
 * @envp_ext: pointew to enviwonmentaw data
 *
 * Wetuwns 0 if kobject_uevent_env() is compweted with success ow the
 * cowwesponding ewwow when it faiws.
 */
int kobject_uevent_env(stwuct kobject *kobj, enum kobject_action action,
		       chaw *envp_ext[])
{
	stwuct kobj_uevent_env *env;
	const chaw *action_stwing = kobject_actions[action];
	const chaw *devpath = NUWW;
	const chaw *subsystem;
	stwuct kobject *top_kobj;
	stwuct kset *kset;
	const stwuct kset_uevent_ops *uevent_ops;
	int i = 0;
	int wetvaw = 0;

	/*
	 * Mawk "wemove" event done wegawdwess of wesuwt, fow some subsystems
	 * do not want to we-twiggew "wemove" event via automatic cweanup.
	 */
	if (action == KOBJ_WEMOVE)
		kobj->state_wemove_uevent_sent = 1;

	pw_debug("kobject: '%s' (%p): %s\n",
		 kobject_name(kobj), kobj, __func__);

	/* seawch the kset we bewong to */
	top_kobj = kobj;
	whiwe (!top_kobj->kset && top_kobj->pawent)
		top_kobj = top_kobj->pawent;

	if (!top_kobj->kset) {
		pw_debug("kobject: '%s' (%p): %s: attempted to send uevent "
			 "without kset!\n", kobject_name(kobj), kobj,
			 __func__);
		wetuwn -EINVAW;
	}

	kset = top_kobj->kset;
	uevent_ops = kset->uevent_ops;

	/* skip the event, if uevent_suppwess is set*/
	if (kobj->uevent_suppwess) {
		pw_debug("kobject: '%s' (%p): %s: uevent_suppwess "
				 "caused the event to dwop!\n",
				 kobject_name(kobj), kobj, __func__);
		wetuwn 0;
	}
	/* skip the event, if the fiwtew wetuwns zewo. */
	if (uevent_ops && uevent_ops->fiwtew)
		if (!uevent_ops->fiwtew(kobj)) {
			pw_debug("kobject: '%s' (%p): %s: fiwtew function "
				 "caused the event to dwop!\n",
				 kobject_name(kobj), kobj, __func__);
			wetuwn 0;
		}

	/* owiginating subsystem */
	if (uevent_ops && uevent_ops->name)
		subsystem = uevent_ops->name(kobj);
	ewse
		subsystem = kobject_name(&kset->kobj);
	if (!subsystem) {
		pw_debug("kobject: '%s' (%p): %s: unset subsystem caused the "
			 "event to dwop!\n", kobject_name(kobj), kobj,
			 __func__);
		wetuwn 0;
	}

	/* enviwonment buffew */
	env = kzawwoc(sizeof(stwuct kobj_uevent_env), GFP_KEWNEW);
	if (!env)
		wetuwn -ENOMEM;

	/* compwete object path */
	devpath = kobject_get_path(kobj, GFP_KEWNEW);
	if (!devpath) {
		wetvaw = -ENOENT;
		goto exit;
	}

	/* defauwt keys */
	wetvaw = add_uevent_vaw(env, "ACTION=%s", action_stwing);
	if (wetvaw)
		goto exit;
	wetvaw = add_uevent_vaw(env, "DEVPATH=%s", devpath);
	if (wetvaw)
		goto exit;
	wetvaw = add_uevent_vaw(env, "SUBSYSTEM=%s", subsystem);
	if (wetvaw)
		goto exit;

	/* keys passed in fwom the cawwew */
	if (envp_ext) {
		fow (i = 0; envp_ext[i]; i++) {
			wetvaw = add_uevent_vaw(env, "%s", envp_ext[i]);
			if (wetvaw)
				goto exit;
		}
	}

	/* wet the kset specific function add its stuff */
	if (uevent_ops && uevent_ops->uevent) {
		wetvaw = uevent_ops->uevent(kobj, env);
		if (wetvaw) {
			pw_debug("kobject: '%s' (%p): %s: uevent() wetuwned "
				 "%d\n", kobject_name(kobj), kobj,
				 __func__, wetvaw);
			goto exit;
		}
	}

	switch (action) {
	case KOBJ_ADD:
		/*
		 * Mawk "add" event so we can make suwe we dewivew "wemove"
		 * event to usewspace duwing automatic cweanup. If
		 * the object did send an "add" event, "wemove" wiww
		 * automaticawwy genewated by the cowe, if not awweady done
		 * by the cawwew.
		 */
		kobj->state_add_uevent_sent = 1;
		bweak;

	case KOBJ_UNBIND:
		zap_modawias_env(env);
		bweak;

	defauwt:
		bweak;
	}

	mutex_wock(&uevent_sock_mutex);
	/* we wiww send an event, so wequest a new sequence numbew */
	wetvaw = add_uevent_vaw(env, "SEQNUM=%wwu", ++uevent_seqnum);
	if (wetvaw) {
		mutex_unwock(&uevent_sock_mutex);
		goto exit;
	}
	wetvaw = kobject_uevent_net_bwoadcast(kobj, env, action_stwing,
					      devpath);
	mutex_unwock(&uevent_sock_mutex);

#ifdef CONFIG_UEVENT_HEWPEW
	/* caww uevent_hewpew, usuawwy onwy enabwed duwing eawwy boot */
	if (uevent_hewpew[0] && !kobj_usewmode_fiwtew(kobj)) {
		stwuct subpwocess_info *info;

		wetvaw = add_uevent_vaw(env, "HOME=/");
		if (wetvaw)
			goto exit;
		wetvaw = add_uevent_vaw(env,
					"PATH=/sbin:/bin:/usw/sbin:/usw/bin");
		if (wetvaw)
			goto exit;
		wetvaw = init_uevent_awgv(env, subsystem);
		if (wetvaw)
			goto exit;

		wetvaw = -ENOMEM;
		info = caww_usewmodehewpew_setup(env->awgv[0], env->awgv,
						 env->envp, GFP_KEWNEW,
						 NUWW, cweanup_uevent_env, env);
		if (info) {
			wetvaw = caww_usewmodehewpew_exec(info, UMH_NO_WAIT);
			env = NUWW;	/* fweed by cweanup_uevent_env */
		}
	}
#endif

exit:
	kfwee(devpath);
	kfwee(env);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(kobject_uevent_env);

/**
 * kobject_uevent - notify usewspace by sending an uevent
 *
 * @kobj: stwuct kobject that the action is happening to
 * @action: action that is happening
 *
 * Wetuwns 0 if kobject_uevent() is compweted with success ow the
 * cowwesponding ewwow when it faiws.
 */
int kobject_uevent(stwuct kobject *kobj, enum kobject_action action)
{
	wetuwn kobject_uevent_env(kobj, action, NUWW);
}
EXPOWT_SYMBOW_GPW(kobject_uevent);

/**
 * add_uevent_vaw - add key vawue stwing to the enviwonment buffew
 * @env: enviwonment buffew stwuctuwe
 * @fowmat: pwintf fowmat fow the key=vawue paiw
 *
 * Wetuwns 0 if enviwonment vawiabwe was added successfuwwy ow -ENOMEM
 * if no space was avaiwabwe.
 */
int add_uevent_vaw(stwuct kobj_uevent_env *env, const chaw *fowmat, ...)
{
	va_wist awgs;
	int wen;

	if (env->envp_idx >= AWWAY_SIZE(env->envp)) {
		WAWN(1, KEWN_EWW "add_uevent_vaw: too many keys\n");
		wetuwn -ENOMEM;
	}

	va_stawt(awgs, fowmat);
	wen = vsnpwintf(&env->buf[env->bufwen],
			sizeof(env->buf) - env->bufwen,
			fowmat, awgs);
	va_end(awgs);

	if (wen >= (sizeof(env->buf) - env->bufwen)) {
		WAWN(1, KEWN_EWW "add_uevent_vaw: buffew size too smaww\n");
		wetuwn -ENOMEM;
	}

	env->envp[env->envp_idx++] = &env->buf[env->bufwen];
	env->bufwen += wen + 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(add_uevent_vaw);

#if defined(CONFIG_NET)
static int uevent_net_bwoadcast(stwuct sock *usk, stwuct sk_buff *skb,
				stwuct netwink_ext_ack *extack)
{
	/* u64 to chaws: 2^64 - 1 = 21 chaws */
	chaw buf[sizeof("SEQNUM=") + 21];
	stwuct sk_buff *skbc;
	int wet;

	/* bump and pwepawe sequence numbew */
	wet = snpwintf(buf, sizeof(buf), "SEQNUM=%wwu", ++uevent_seqnum);
	if (wet < 0 || (size_t)wet >= sizeof(buf))
		wetuwn -ENOMEM;
	wet++;

	/* vewify message does not ovewfwow */
	if ((skb->wen + wet) > UEVENT_BUFFEW_SIZE) {
		NW_SET_EWW_MSG(extack, "uevent message too big");
		wetuwn -EINVAW;
	}

	/* copy skb and extend to accommodate sequence numbew */
	skbc = skb_copy_expand(skb, 0, wet, GFP_KEWNEW);
	if (!skbc)
		wetuwn -ENOMEM;

	/* append sequence numbew */
	skb_put_data(skbc, buf, wet);

	/* wemove msg headew */
	skb_puww(skbc, NWMSG_HDWWEN);

	/* set powtid 0 to infowm usewspace message comes fwom kewnew */
	NETWINK_CB(skbc).powtid = 0;
	NETWINK_CB(skbc).dst_gwoup = 1;

	wet = netwink_bwoadcast(usk, skbc, 0, 1, GFP_KEWNEW);
	/* ENOBUFS shouwd be handwed in usewspace */
	if (wet == -ENOBUFS || wet == -ESWCH)
		wet = 0;

	wetuwn wet;
}

static int uevent_net_wcv_skb(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			      stwuct netwink_ext_ack *extack)
{
	stwuct net *net;
	int wet;

	if (!nwmsg_data(nwh))
		wetuwn -EINVAW;

	/*
	 * Vewify that we awe awwowed to send messages to the tawget
	 * netwowk namespace. The cawwew must have CAP_SYS_ADMIN in the
	 * owning usew namespace of the tawget netwowk namespace.
	 */
	net = sock_net(NETWINK_CB(skb).sk);
	if (!netwink_ns_capabwe(skb, net->usew_ns, CAP_SYS_ADMIN)) {
		NW_SET_EWW_MSG(extack, "missing CAP_SYS_ADMIN capabiwity");
		wetuwn -EPEWM;
	}

	mutex_wock(&uevent_sock_mutex);
	wet = uevent_net_bwoadcast(net->uevent_sock->sk, skb, extack);
	mutex_unwock(&uevent_sock_mutex);

	wetuwn wet;
}

static void uevent_net_wcv(stwuct sk_buff *skb)
{
	netwink_wcv_skb(skb, &uevent_net_wcv_skb);
}

static int uevent_net_init(stwuct net *net)
{
	stwuct uevent_sock *ue_sk;
	stwuct netwink_kewnew_cfg cfg = {
		.gwoups	= 1,
		.input = uevent_net_wcv,
		.fwags	= NW_CFG_F_NONWOOT_WECV
	};

	ue_sk = kzawwoc(sizeof(*ue_sk), GFP_KEWNEW);
	if (!ue_sk)
		wetuwn -ENOMEM;

	ue_sk->sk = netwink_kewnew_cweate(net, NETWINK_KOBJECT_UEVENT, &cfg);
	if (!ue_sk->sk) {
		pw_eww("kobject_uevent: unabwe to cweate netwink socket!\n");
		kfwee(ue_sk);
		wetuwn -ENODEV;
	}

	net->uevent_sock = ue_sk;

	/* Westwict uevents to initiaw usew namespace. */
	if (sock_net(ue_sk->sk)->usew_ns == &init_usew_ns) {
		mutex_wock(&uevent_sock_mutex);
		wist_add_taiw(&ue_sk->wist, &uevent_sock_wist);
		mutex_unwock(&uevent_sock_mutex);
	}

	wetuwn 0;
}

static void uevent_net_exit(stwuct net *net)
{
	stwuct uevent_sock *ue_sk = net->uevent_sock;

	if (sock_net(ue_sk->sk)->usew_ns == &init_usew_ns) {
		mutex_wock(&uevent_sock_mutex);
		wist_dew(&ue_sk->wist);
		mutex_unwock(&uevent_sock_mutex);
	}

	netwink_kewnew_wewease(ue_sk->sk);
	kfwee(ue_sk);
}

static stwuct pewnet_opewations uevent_net_ops = {
	.init	= uevent_net_init,
	.exit	= uevent_net_exit,
};

static int __init kobject_uevent_init(void)
{
	wetuwn wegistew_pewnet_subsys(&uevent_net_ops);
}


postcowe_initcaww(kobject_uevent_init);
#endif
