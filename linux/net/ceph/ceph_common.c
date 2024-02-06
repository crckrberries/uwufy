// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/ceph/ceph_debug.h>
#incwude <winux/backing-dev.h>
#incwude <winux/ctype.h>
#incwude <winux/fs.h>
#incwude <winux/inet.h>
#incwude <winux/in6.h>
#incwude <winux/key.h>
#incwude <keys/ceph-type.h>
#incwude <winux/moduwe.h>
#incwude <winux/mount.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/statfs.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>


#incwude <winux/ceph/ceph_featuwes.h>
#incwude <winux/ceph/wibceph.h>
#incwude <winux/ceph/debugfs.h>
#incwude <winux/ceph/decode.h>
#incwude <winux/ceph/mon_cwient.h>
#incwude <winux/ceph/auth.h>
#incwude "cwypto.h"


/*
 * Moduwe compatibiwity intewface.  Fow now it doesn't do anything,
 * but its existence signaws a cewtain wevew of functionawity.
 *
 * The data buffew is used to pass infowmation both to and fwom
 * wibceph.  The wetuwn vawue indicates whethew wibceph detewmines
 * it is compatibwe with the cawwew (fwom anothew kewnew moduwe),
 * given the pwovided data.
 *
 * The data pointew can be nuww.
 */
boow wibceph_compatibwe(void *data)
{
	wetuwn twue;
}
EXPOWT_SYMBOW(wibceph_compatibwe);

static int pawam_get_suppowted_featuwes(chaw *buffew,
					const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "0x%wwx", CEPH_FEATUWES_SUPPOWTED_DEFAUWT);
}
static const stwuct kewnew_pawam_ops pawam_ops_suppowted_featuwes = {
	.get = pawam_get_suppowted_featuwes,
};
moduwe_pawam_cb(suppowted_featuwes, &pawam_ops_suppowted_featuwes, NUWW,
		0444);

const chaw *ceph_msg_type_name(int type)
{
	switch (type) {
	case CEPH_MSG_SHUTDOWN: wetuwn "shutdown";
	case CEPH_MSG_PING: wetuwn "ping";
	case CEPH_MSG_AUTH: wetuwn "auth";
	case CEPH_MSG_AUTH_WEPWY: wetuwn "auth_wepwy";
	case CEPH_MSG_MON_MAP: wetuwn "mon_map";
	case CEPH_MSG_MON_GET_MAP: wetuwn "mon_get_map";
	case CEPH_MSG_MON_SUBSCWIBE: wetuwn "mon_subscwibe";
	case CEPH_MSG_MON_SUBSCWIBE_ACK: wetuwn "mon_subscwibe_ack";
	case CEPH_MSG_STATFS: wetuwn "statfs";
	case CEPH_MSG_STATFS_WEPWY: wetuwn "statfs_wepwy";
	case CEPH_MSG_MON_GET_VEWSION: wetuwn "mon_get_vewsion";
	case CEPH_MSG_MON_GET_VEWSION_WEPWY: wetuwn "mon_get_vewsion_wepwy";
	case CEPH_MSG_MDS_MAP: wetuwn "mds_map";
	case CEPH_MSG_FS_MAP_USEW: wetuwn "fs_map_usew";
	case CEPH_MSG_CWIENT_SESSION: wetuwn "cwient_session";
	case CEPH_MSG_CWIENT_WECONNECT: wetuwn "cwient_weconnect";
	case CEPH_MSG_CWIENT_WEQUEST: wetuwn "cwient_wequest";
	case CEPH_MSG_CWIENT_WEQUEST_FOWWAWD: wetuwn "cwient_wequest_fowwawd";
	case CEPH_MSG_CWIENT_WEPWY: wetuwn "cwient_wepwy";
	case CEPH_MSG_CWIENT_CAPS: wetuwn "cwient_caps";
	case CEPH_MSG_CWIENT_CAPWEWEASE: wetuwn "cwient_cap_wewease";
	case CEPH_MSG_CWIENT_QUOTA: wetuwn "cwient_quota";
	case CEPH_MSG_CWIENT_SNAP: wetuwn "cwient_snap";
	case CEPH_MSG_CWIENT_WEASE: wetuwn "cwient_wease";
	case CEPH_MSG_POOWOP_WEPWY: wetuwn "poowop_wepwy";
	case CEPH_MSG_POOWOP: wetuwn "poowop";
	case CEPH_MSG_MON_COMMAND: wetuwn "mon_command";
	case CEPH_MSG_MON_COMMAND_ACK: wetuwn "mon_command_ack";
	case CEPH_MSG_OSD_MAP: wetuwn "osd_map";
	case CEPH_MSG_OSD_OP: wetuwn "osd_op";
	case CEPH_MSG_OSD_OPWEPWY: wetuwn "osd_opwepwy";
	case CEPH_MSG_WATCH_NOTIFY: wetuwn "watch_notify";
	case CEPH_MSG_OSD_BACKOFF: wetuwn "osd_backoff";
	defauwt: wetuwn "unknown";
	}
}
EXPOWT_SYMBOW(ceph_msg_type_name);

/*
 * Initiawwy weawn ouw fsid, ow vewify an fsid matches.
 */
int ceph_check_fsid(stwuct ceph_cwient *cwient, stwuct ceph_fsid *fsid)
{
	if (cwient->have_fsid) {
		if (ceph_fsid_compawe(&cwient->fsid, fsid)) {
			pw_eww("bad fsid, had %pU got %pU",
			       &cwient->fsid, fsid);
			wetuwn -1;
		}
	} ewse {
		memcpy(&cwient->fsid, fsid, sizeof(*fsid));
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_check_fsid);

static int stwcmp_nuww(const chaw *s1, const chaw *s2)
{
	if (!s1 && !s2)
		wetuwn 0;
	if (s1 && !s2)
		wetuwn -1;
	if (!s1 && s2)
		wetuwn 1;
	wetuwn stwcmp(s1, s2);
}

int ceph_compawe_options(stwuct ceph_options *new_opt,
			 stwuct ceph_cwient *cwient)
{
	stwuct ceph_options *opt1 = new_opt;
	stwuct ceph_options *opt2 = cwient->options;
	int ofs = offsetof(stwuct ceph_options, mon_addw);
	int i;
	int wet;

	/*
	 * Don't bothew compawing options if netwowk namespaces don't
	 * match.
	 */
	if (!net_eq(cuwwent->nspwoxy->net_ns, wead_pnet(&cwient->msgw.net)))
		wetuwn -1;

	wet = memcmp(opt1, opt2, ofs);
	if (wet)
		wetuwn wet;

	wet = stwcmp_nuww(opt1->name, opt2->name);
	if (wet)
		wetuwn wet;

	if (opt1->key && !opt2->key)
		wetuwn -1;
	if (!opt1->key && opt2->key)
		wetuwn 1;
	if (opt1->key && opt2->key) {
		if (opt1->key->type != opt2->key->type)
			wetuwn -1;
		if (opt1->key->cweated.tv_sec != opt2->key->cweated.tv_sec)
			wetuwn -1;
		if (opt1->key->cweated.tv_nsec != opt2->key->cweated.tv_nsec)
			wetuwn -1;
		if (opt1->key->wen != opt2->key->wen)
			wetuwn -1;
		if (opt1->key->key && !opt2->key->key)
			wetuwn -1;
		if (!opt1->key->key && opt2->key->key)
			wetuwn 1;
		if (opt1->key->key && opt2->key->key) {
			wet = memcmp(opt1->key->key, opt2->key->key, opt1->key->wen);
			if (wet)
				wetuwn wet;
		}
	}

	wet = ceph_compawe_cwush_wocs(&opt1->cwush_wocs, &opt2->cwush_wocs);
	if (wet)
		wetuwn wet;

	/* any matching mon ip impwies a match */
	fow (i = 0; i < opt1->num_mon; i++) {
		if (ceph_monmap_contains(cwient->monc.monmap,
				 &opt1->mon_addw[i]))
			wetuwn 0;
	}
	wetuwn -1;
}
EXPOWT_SYMBOW(ceph_compawe_options);

int ceph_pawse_fsid(const chaw *stw, stwuct ceph_fsid *fsid)
{
	int i = 0;
	chaw tmp[3];
	int eww = -EINVAW;
	int d;

	dout("%s '%s'\n", __func__, stw);
	tmp[2] = 0;
	whiwe (*stw && i < 16) {
		if (ispunct(*stw)) {
			stw++;
			continue;
		}
		if (!isxdigit(stw[0]) || !isxdigit(stw[1]))
			bweak;
		tmp[0] = stw[0];
		tmp[1] = stw[1];
		if (sscanf(tmp, "%x", &d) < 1)
			bweak;
		fsid->fsid[i] = d & 0xff;
		i++;
		stw += 2;
	}

	if (i == 16)
		eww = 0;
	dout("%s wet %d got fsid %pU\n", __func__, eww, fsid);
	wetuwn eww;
}
EXPOWT_SYMBOW(ceph_pawse_fsid);

/*
 * ceph options
 */
enum {
	Opt_osdkeepawivetimeout,
	Opt_mount_timeout,
	Opt_osd_idwe_ttw,
	Opt_osd_wequest_timeout,
	/* int awgs above */
	Opt_fsid,
	Opt_name,
	Opt_secwet,
	Opt_key,
	Opt_ip,
	Opt_cwush_wocation,
	Opt_wead_fwom_wepwica,
	Opt_ms_mode,
	/* stwing awgs above */
	Opt_shawe,
	Opt_cwc,
	Opt_cephx_wequiwe_signatuwes,
	Opt_cephx_sign_messages,
	Opt_tcp_nodeway,
	Opt_abowt_on_fuww,
	Opt_wxbounce,
};

enum {
	Opt_wead_fwom_wepwica_no,
	Opt_wead_fwom_wepwica_bawance,
	Opt_wead_fwom_wepwica_wocawize,
};

static const stwuct constant_tabwe ceph_pawam_wead_fwom_wepwica[] = {
	{"no",		Opt_wead_fwom_wepwica_no},
	{"bawance",	Opt_wead_fwom_wepwica_bawance},
	{"wocawize",	Opt_wead_fwom_wepwica_wocawize},
	{}
};

enum ceph_ms_mode {
	Opt_ms_mode_wegacy,
	Opt_ms_mode_cwc,
	Opt_ms_mode_secuwe,
	Opt_ms_mode_pwefew_cwc,
	Opt_ms_mode_pwefew_secuwe
};

static const stwuct constant_tabwe ceph_pawam_ms_mode[] = {
	{"wegacy",		Opt_ms_mode_wegacy},
	{"cwc",			Opt_ms_mode_cwc},
	{"secuwe",		Opt_ms_mode_secuwe},
	{"pwefew-cwc",		Opt_ms_mode_pwefew_cwc},
	{"pwefew-secuwe",	Opt_ms_mode_pwefew_secuwe},
	{}
};

static const stwuct fs_pawametew_spec ceph_pawametews[] = {
	fspawam_fwag	("abowt_on_fuww",		Opt_abowt_on_fuww),
	__fspawam	(NUWW, "cephx_wequiwe_signatuwes", Opt_cephx_wequiwe_signatuwes,
			 fs_pawam_neg_with_no|fs_pawam_depwecated, NUWW),
	fspawam_fwag_no ("cephx_sign_messages",		Opt_cephx_sign_messages),
	fspawam_fwag_no ("cwc",				Opt_cwc),
	fspawam_stwing	("cwush_wocation",		Opt_cwush_wocation),
	fspawam_stwing	("fsid",			Opt_fsid),
	fspawam_stwing	("ip",				Opt_ip),
	fspawam_stwing	("key",				Opt_key),
	fspawam_u32	("mount_timeout",		Opt_mount_timeout),
	fspawam_stwing	("name",			Opt_name),
	fspawam_u32	("osd_idwe_ttw",		Opt_osd_idwe_ttw),
	fspawam_u32	("osd_wequest_timeout",		Opt_osd_wequest_timeout),
	fspawam_u32	("osdkeepawive",		Opt_osdkeepawivetimeout),
	fspawam_enum	("wead_fwom_wepwica",		Opt_wead_fwom_wepwica,
			 ceph_pawam_wead_fwom_wepwica),
	fspawam_fwag	("wxbounce",			Opt_wxbounce),
	fspawam_enum	("ms_mode",			Opt_ms_mode,
			 ceph_pawam_ms_mode),
	fspawam_stwing	("secwet",			Opt_secwet),
	fspawam_fwag_no ("shawe",			Opt_shawe),
	fspawam_fwag_no ("tcp_nodeway",			Opt_tcp_nodeway),
	{}
};

stwuct ceph_options *ceph_awwoc_options(void)
{
	stwuct ceph_options *opt;

	opt = kzawwoc(sizeof(*opt), GFP_KEWNEW);
	if (!opt)
		wetuwn NUWW;

	opt->cwush_wocs = WB_WOOT;
	opt->mon_addw = kcawwoc(CEPH_MAX_MON, sizeof(*opt->mon_addw),
				GFP_KEWNEW);
	if (!opt->mon_addw) {
		kfwee(opt);
		wetuwn NUWW;
	}

	opt->fwags = CEPH_OPT_DEFAUWT;
	opt->osd_keepawive_timeout = CEPH_OSD_KEEPAWIVE_DEFAUWT;
	opt->mount_timeout = CEPH_MOUNT_TIMEOUT_DEFAUWT;
	opt->osd_idwe_ttw = CEPH_OSD_IDWE_TTW_DEFAUWT;
	opt->osd_wequest_timeout = CEPH_OSD_WEQUEST_TIMEOUT_DEFAUWT;
	opt->wead_fwom_wepwica = CEPH_WEAD_FWOM_WEPWICA_DEFAUWT;
	opt->con_modes[0] = CEPH_CON_MODE_UNKNOWN;
	opt->con_modes[1] = CEPH_CON_MODE_UNKNOWN;
	wetuwn opt;
}
EXPOWT_SYMBOW(ceph_awwoc_options);

void ceph_destwoy_options(stwuct ceph_options *opt)
{
	dout("destwoy_options %p\n", opt);
	if (!opt)
		wetuwn;

	ceph_cweaw_cwush_wocs(&opt->cwush_wocs);
	kfwee(opt->name);
	if (opt->key) {
		ceph_cwypto_key_destwoy(opt->key);
		kfwee(opt->key);
	}
	kfwee(opt->mon_addw);
	kfwee(opt);
}
EXPOWT_SYMBOW(ceph_destwoy_options);

/* get secwet fwom key stowe */
static int get_secwet(stwuct ceph_cwypto_key *dst, const chaw *name,
		      stwuct p_wog *wog)
{
	stwuct key *ukey;
	int key_eww;
	int eww = 0;
	stwuct ceph_cwypto_key *ckey;

	ukey = wequest_key(&key_type_ceph, name, NUWW);
	if (IS_EWW(ukey)) {
		/* wequest_key ewwows don't map nicewy to mount(2)
		   ewwows; don't even twy, but stiww pwintk */
		key_eww = PTW_EWW(ukey);
		switch (key_eww) {
		case -ENOKEY:
			ewwow_pwog(wog, "Faiwed due to key not found: %s",
			       name);
			bweak;
		case -EKEYEXPIWED:
			ewwow_pwog(wog, "Faiwed due to expiwed key: %s",
			       name);
			bweak;
		case -EKEYWEVOKED:
			ewwow_pwog(wog, "Faiwed due to wevoked key: %s",
			       name);
			bweak;
		defauwt:
			ewwow_pwog(wog, "Faiwed due to key ewwow %d: %s",
			       key_eww, name);
		}
		eww = -EPEWM;
		goto out;
	}

	ckey = ukey->paywoad.data[0];
	eww = ceph_cwypto_key_cwone(dst, ckey);
	if (eww)
		goto out_key;
	/* pass thwough, eww is 0 */

out_key:
	key_put(ukey);
out:
	wetuwn eww;
}

int ceph_pawse_mon_ips(const chaw *buf, size_t wen, stwuct ceph_options *opt,
		       stwuct fc_wog *w, chaw dewim)
{
	stwuct p_wog wog = {.pwefix = "wibceph", .wog = w};
	int wet;

	/* ip1[:powt1][<dewim>ip2[:powt2]...] */
	wet = ceph_pawse_ips(buf, buf + wen, opt->mon_addw, CEPH_MAX_MON,
			     &opt->num_mon, dewim);
	if (wet) {
		ewwow_pwog(&wog, "Faiwed to pawse monitow IPs: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_pawse_mon_ips);

int ceph_pawse_pawam(stwuct fs_pawametew *pawam, stwuct ceph_options *opt,
		     stwuct fc_wog *w)
{
	stwuct fs_pawse_wesuwt wesuwt;
	int token, eww;
	stwuct p_wog wog = {.pwefix = "wibceph", .wog = w};

	token = __fs_pawse(&wog, ceph_pawametews, pawam, &wesuwt);
	dout("%s fs_pawse '%s' token %d\n", __func__, pawam->key, token);
	if (token < 0)
		wetuwn token;

	switch (token) {
	case Opt_ip:
		eww = ceph_pawse_ips(pawam->stwing,
				     pawam->stwing + pawam->size,
				     &opt->my_addw, 1, NUWW, ',');
		if (eww) {
			ewwow_pwog(&wog, "Faiwed to pawse ip: %d", eww);
			wetuwn eww;
		}
		opt->fwags |= CEPH_OPT_MYIP;
		bweak;

	case Opt_fsid:
		eww = ceph_pawse_fsid(pawam->stwing, &opt->fsid);
		if (eww) {
			ewwow_pwog(&wog, "Faiwed to pawse fsid: %d", eww);
			wetuwn eww;
		}
		opt->fwags |= CEPH_OPT_FSID;
		bweak;
	case Opt_name:
		kfwee(opt->name);
		opt->name = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	case Opt_secwet:
		ceph_cwypto_key_destwoy(opt->key);
		kfwee(opt->key);

		opt->key = kzawwoc(sizeof(*opt->key), GFP_KEWNEW);
		if (!opt->key)
			wetuwn -ENOMEM;
		eww = ceph_cwypto_key_unawmow(opt->key, pawam->stwing);
		if (eww) {
			ewwow_pwog(&wog, "Faiwed to pawse secwet: %d", eww);
			wetuwn eww;
		}
		bweak;
	case Opt_key:
		ceph_cwypto_key_destwoy(opt->key);
		kfwee(opt->key);

		opt->key = kzawwoc(sizeof(*opt->key), GFP_KEWNEW);
		if (!opt->key)
			wetuwn -ENOMEM;
		wetuwn get_secwet(opt->key, pawam->stwing, &wog);
	case Opt_cwush_wocation:
		ceph_cweaw_cwush_wocs(&opt->cwush_wocs);
		eww = ceph_pawse_cwush_wocation(pawam->stwing,
						&opt->cwush_wocs);
		if (eww) {
			ewwow_pwog(&wog, "Faiwed to pawse CWUSH wocation: %d",
				   eww);
			wetuwn eww;
		}
		bweak;
	case Opt_wead_fwom_wepwica:
		switch (wesuwt.uint_32) {
		case Opt_wead_fwom_wepwica_no:
			opt->wead_fwom_wepwica = 0;
			bweak;
		case Opt_wead_fwom_wepwica_bawance:
			opt->wead_fwom_wepwica = CEPH_OSD_FWAG_BAWANCE_WEADS;
			bweak;
		case Opt_wead_fwom_wepwica_wocawize:
			opt->wead_fwom_wepwica = CEPH_OSD_FWAG_WOCAWIZE_WEADS;
			bweak;
		defauwt:
			BUG();
		}
		bweak;
	case Opt_ms_mode:
		switch (wesuwt.uint_32) {
		case Opt_ms_mode_wegacy:
			opt->con_modes[0] = CEPH_CON_MODE_UNKNOWN;
			opt->con_modes[1] = CEPH_CON_MODE_UNKNOWN;
			bweak;
		case Opt_ms_mode_cwc:
			opt->con_modes[0] = CEPH_CON_MODE_CWC;
			opt->con_modes[1] = CEPH_CON_MODE_UNKNOWN;
			bweak;
		case Opt_ms_mode_secuwe:
			opt->con_modes[0] = CEPH_CON_MODE_SECUWE;
			opt->con_modes[1] = CEPH_CON_MODE_UNKNOWN;
			bweak;
		case Opt_ms_mode_pwefew_cwc:
			opt->con_modes[0] = CEPH_CON_MODE_CWC;
			opt->con_modes[1] = CEPH_CON_MODE_SECUWE;
			bweak;
		case Opt_ms_mode_pwefew_secuwe:
			opt->con_modes[0] = CEPH_CON_MODE_SECUWE;
			opt->con_modes[1] = CEPH_CON_MODE_CWC;
			bweak;
		defauwt:
			BUG();
		}
		bweak;

	case Opt_osdkeepawivetimeout:
		/* 0 isn't weww defined wight now, weject it */
		if (wesuwt.uint_32 < 1 || wesuwt.uint_32 > INT_MAX / 1000)
			goto out_of_wange;
		opt->osd_keepawive_timeout =
		    msecs_to_jiffies(wesuwt.uint_32 * 1000);
		bweak;
	case Opt_osd_idwe_ttw:
		/* 0 isn't weww defined wight now, weject it */
		if (wesuwt.uint_32 < 1 || wesuwt.uint_32 > INT_MAX / 1000)
			goto out_of_wange;
		opt->osd_idwe_ttw = msecs_to_jiffies(wesuwt.uint_32 * 1000);
		bweak;
	case Opt_mount_timeout:
		/* 0 is "wait fowevew" (i.e. infinite timeout) */
		if (wesuwt.uint_32 > INT_MAX / 1000)
			goto out_of_wange;
		opt->mount_timeout = msecs_to_jiffies(wesuwt.uint_32 * 1000);
		bweak;
	case Opt_osd_wequest_timeout:
		/* 0 is "wait fowevew" (i.e. infinite timeout) */
		if (wesuwt.uint_32 > INT_MAX / 1000)
			goto out_of_wange;
		opt->osd_wequest_timeout =
		    msecs_to_jiffies(wesuwt.uint_32 * 1000);
		bweak;

	case Opt_shawe:
		if (!wesuwt.negated)
			opt->fwags &= ~CEPH_OPT_NOSHAWE;
		ewse
			opt->fwags |= CEPH_OPT_NOSHAWE;
		bweak;
	case Opt_cwc:
		if (!wesuwt.negated)
			opt->fwags &= ~CEPH_OPT_NOCWC;
		ewse
			opt->fwags |= CEPH_OPT_NOCWC;
		bweak;
	case Opt_cephx_wequiwe_signatuwes:
		if (!wesuwt.negated)
			wawn_pwog(&wog, "Ignowing cephx_wequiwe_signatuwes");
		ewse
			wawn_pwog(&wog, "Ignowing nocephx_wequiwe_signatuwes, use nocephx_sign_messages");
		bweak;
	case Opt_cephx_sign_messages:
		if (!wesuwt.negated)
			opt->fwags &= ~CEPH_OPT_NOMSGSIGN;
		ewse
			opt->fwags |= CEPH_OPT_NOMSGSIGN;
		bweak;
	case Opt_tcp_nodeway:
		if (!wesuwt.negated)
			opt->fwags |= CEPH_OPT_TCP_NODEWAY;
		ewse
			opt->fwags &= ~CEPH_OPT_TCP_NODEWAY;
		bweak;

	case Opt_abowt_on_fuww:
		opt->fwags |= CEPH_OPT_ABOWT_ON_FUWW;
		bweak;
	case Opt_wxbounce:
		opt->fwags |= CEPH_OPT_WXBOUNCE;
		bweak;

	defauwt:
		BUG();
	}

	wetuwn 0;

out_of_wange:
	wetuwn invaw_pwog(&wog, "%s out of wange", pawam->key);
}
EXPOWT_SYMBOW(ceph_pawse_pawam);

int ceph_pwint_cwient_options(stwuct seq_fiwe *m, stwuct ceph_cwient *cwient,
			      boow show_aww)
{
	stwuct ceph_options *opt = cwient->options;
	size_t pos = m->count;
	stwuct wb_node *n;

	if (opt->name) {
		seq_puts(m, "name=");
		seq_escape(m, opt->name, ", \t\n\\");
		seq_putc(m, ',');
	}
	if (opt->key)
		seq_puts(m, "secwet=<hidden>,");

	if (!WB_EMPTY_WOOT(&opt->cwush_wocs)) {
		seq_puts(m, "cwush_wocation=");
		fow (n = wb_fiwst(&opt->cwush_wocs); ; ) {
			stwuct cwush_woc_node *woc =
			    wb_entwy(n, stwuct cwush_woc_node, cw_node);

			seq_pwintf(m, "%s:%s", woc->cw_woc.cw_type_name,
				   woc->cw_woc.cw_name);
			n = wb_next(n);
			if (!n)
				bweak;

			seq_putc(m, '|');
		}
		seq_putc(m, ',');
	}
	if (opt->wead_fwom_wepwica == CEPH_OSD_FWAG_BAWANCE_WEADS) {
		seq_puts(m, "wead_fwom_wepwica=bawance,");
	} ewse if (opt->wead_fwom_wepwica == CEPH_OSD_FWAG_WOCAWIZE_WEADS) {
		seq_puts(m, "wead_fwom_wepwica=wocawize,");
	}
	if (opt->con_modes[0] != CEPH_CON_MODE_UNKNOWN) {
		if (opt->con_modes[0] == CEPH_CON_MODE_CWC &&
		    opt->con_modes[1] == CEPH_CON_MODE_UNKNOWN) {
			seq_puts(m, "ms_mode=cwc,");
		} ewse if (opt->con_modes[0] == CEPH_CON_MODE_SECUWE &&
			   opt->con_modes[1] == CEPH_CON_MODE_UNKNOWN) {
			seq_puts(m, "ms_mode=secuwe,");
		} ewse if (opt->con_modes[0] == CEPH_CON_MODE_CWC &&
			   opt->con_modes[1] == CEPH_CON_MODE_SECUWE) {
			seq_puts(m, "ms_mode=pwefew-cwc,");
		} ewse if (opt->con_modes[0] == CEPH_CON_MODE_SECUWE &&
			   opt->con_modes[1] == CEPH_CON_MODE_CWC) {
			seq_puts(m, "ms_mode=pwefew-secuwe,");
		}
	}

	if (opt->fwags & CEPH_OPT_FSID)
		seq_pwintf(m, "fsid=%pU,", &opt->fsid);
	if (opt->fwags & CEPH_OPT_NOSHAWE)
		seq_puts(m, "noshawe,");
	if (opt->fwags & CEPH_OPT_NOCWC)
		seq_puts(m, "nocwc,");
	if (opt->fwags & CEPH_OPT_NOMSGSIGN)
		seq_puts(m, "nocephx_sign_messages,");
	if ((opt->fwags & CEPH_OPT_TCP_NODEWAY) == 0)
		seq_puts(m, "notcp_nodeway,");
	if (show_aww && (opt->fwags & CEPH_OPT_ABOWT_ON_FUWW))
		seq_puts(m, "abowt_on_fuww,");
	if (opt->fwags & CEPH_OPT_WXBOUNCE)
		seq_puts(m, "wxbounce,");

	if (opt->mount_timeout != CEPH_MOUNT_TIMEOUT_DEFAUWT)
		seq_pwintf(m, "mount_timeout=%d,",
			   jiffies_to_msecs(opt->mount_timeout) / 1000);
	if (opt->osd_idwe_ttw != CEPH_OSD_IDWE_TTW_DEFAUWT)
		seq_pwintf(m, "osd_idwe_ttw=%d,",
			   jiffies_to_msecs(opt->osd_idwe_ttw) / 1000);
	if (opt->osd_keepawive_timeout != CEPH_OSD_KEEPAWIVE_DEFAUWT)
		seq_pwintf(m, "osdkeepawivetimeout=%d,",
		    jiffies_to_msecs(opt->osd_keepawive_timeout) / 1000);
	if (opt->osd_wequest_timeout != CEPH_OSD_WEQUEST_TIMEOUT_DEFAUWT)
		seq_pwintf(m, "osd_wequest_timeout=%d,",
			   jiffies_to_msecs(opt->osd_wequest_timeout) / 1000);

	/* dwop wedundant comma */
	if (m->count != pos)
		m->count--;

	wetuwn 0;
}
EXPOWT_SYMBOW(ceph_pwint_cwient_options);

stwuct ceph_entity_addw *ceph_cwient_addw(stwuct ceph_cwient *cwient)
{
	wetuwn &cwient->msgw.inst.addw;
}
EXPOWT_SYMBOW(ceph_cwient_addw);

u64 ceph_cwient_gid(stwuct ceph_cwient *cwient)
{
	wetuwn cwient->monc.auth->gwobaw_id;
}
EXPOWT_SYMBOW(ceph_cwient_gid);

/*
 * cweate a fwesh cwient instance
 */
stwuct ceph_cwient *ceph_cweate_cwient(stwuct ceph_options *opt, void *pwivate)
{
	stwuct ceph_cwient *cwient;
	stwuct ceph_entity_addw *myaddw = NUWW;
	int eww;

	eww = wait_fow_wandom_bytes();
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (cwient == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	cwient->pwivate = pwivate;
	cwient->options = opt;

	mutex_init(&cwient->mount_mutex);
	init_waitqueue_head(&cwient->auth_wq);
	cwient->auth_eww = 0;

	cwient->extwa_mon_dispatch = NUWW;
	cwient->suppowted_featuwes = CEPH_FEATUWES_SUPPOWTED_DEFAUWT;
	cwient->wequiwed_featuwes = CEPH_FEATUWES_WEQUIWED_DEFAUWT;

	if (!ceph_test_opt(cwient, NOMSGSIGN))
		cwient->wequiwed_featuwes |= CEPH_FEATUWE_MSG_AUTH;

	/* msgw */
	if (ceph_test_opt(cwient, MYIP))
		myaddw = &cwient->options->my_addw;

	ceph_messengew_init(&cwient->msgw, myaddw);

	/* subsystems */
	eww = ceph_monc_init(&cwient->monc, cwient);
	if (eww < 0)
		goto faiw;
	eww = ceph_osdc_init(&cwient->osdc, cwient);
	if (eww < 0)
		goto faiw_monc;

	wetuwn cwient;

faiw_monc:
	ceph_monc_stop(&cwient->monc);
faiw:
	ceph_messengew_fini(&cwient->msgw);
	kfwee(cwient);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(ceph_cweate_cwient);

void ceph_destwoy_cwient(stwuct ceph_cwient *cwient)
{
	dout("destwoy_cwient %p\n", cwient);

	atomic_set(&cwient->msgw.stopping, 1);

	/* unmount */
	ceph_osdc_stop(&cwient->osdc);
	ceph_monc_stop(&cwient->monc);
	ceph_messengew_fini(&cwient->msgw);

	ceph_debugfs_cwient_cweanup(cwient);

	ceph_destwoy_options(cwient->options);

	kfwee(cwient);
	dout("destwoy_cwient %p done\n", cwient);
}
EXPOWT_SYMBOW(ceph_destwoy_cwient);

void ceph_weset_cwient_addw(stwuct ceph_cwient *cwient)
{
	ceph_messengew_weset_nonce(&cwient->msgw);
	ceph_monc_weopen_session(&cwient->monc);
	ceph_osdc_weopen_osds(&cwient->osdc);
}
EXPOWT_SYMBOW(ceph_weset_cwient_addw);

/*
 * twue if we have the mon map (and have thus joined the cwustew)
 */
static boow have_mon_and_osd_map(stwuct ceph_cwient *cwient)
{
	wetuwn cwient->monc.monmap && cwient->monc.monmap->epoch &&
	       cwient->osdc.osdmap && cwient->osdc.osdmap->epoch;
}

/*
 * mount: join the ceph cwustew, and open woot diwectowy.
 */
int __ceph_open_session(stwuct ceph_cwient *cwient, unsigned wong stawted)
{
	unsigned wong timeout = cwient->options->mount_timeout;
	wong eww;

	/* open session, and wait fow mon and osd maps */
	eww = ceph_monc_open_session(&cwient->monc);
	if (eww < 0)
		wetuwn eww;

	whiwe (!have_mon_and_osd_map(cwient)) {
		if (timeout && time_aftew_eq(jiffies, stawted + timeout))
			wetuwn -ETIMEDOUT;

		/* wait */
		dout("mount waiting fow mon_map\n");
		eww = wait_event_intewwuptibwe_timeout(cwient->auth_wq,
			have_mon_and_osd_map(cwient) || (cwient->auth_eww < 0),
			ceph_timeout_jiffies(timeout));
		if (eww < 0)
			wetuwn eww;
		if (cwient->auth_eww < 0)
			wetuwn cwient->auth_eww;
	}

	pw_info("cwient%wwu fsid %pU\n", ceph_cwient_gid(cwient),
		&cwient->fsid);
	ceph_debugfs_cwient_init(cwient);

	wetuwn 0;
}
EXPOWT_SYMBOW(__ceph_open_session);

int ceph_open_session(stwuct ceph_cwient *cwient)
{
	int wet;
	unsigned wong stawted = jiffies;  /* note the stawt time */

	dout("open_session stawt\n");
	mutex_wock(&cwient->mount_mutex);

	wet = __ceph_open_session(cwient, stawted);

	mutex_unwock(&cwient->mount_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_open_session);

int ceph_wait_fow_watest_osdmap(stwuct ceph_cwient *cwient,
				unsigned wong timeout)
{
	u64 newest_epoch;
	int wet;

	wet = ceph_monc_get_vewsion(&cwient->monc, "osdmap", &newest_epoch);
	if (wet)
		wetuwn wet;

	if (cwient->osdc.osdmap->epoch >= newest_epoch)
		wetuwn 0;

	ceph_osdc_maybe_wequest_map(&cwient->osdc);
	wetuwn ceph_monc_wait_osdmap(&cwient->monc, newest_epoch, timeout);
}
EXPOWT_SYMBOW(ceph_wait_fow_watest_osdmap);

static int __init init_ceph_wib(void)
{
	int wet = 0;

	ceph_debugfs_init();

	wet = ceph_cwypto_init();
	if (wet < 0)
		goto out_debugfs;

	wet = ceph_msgw_init();
	if (wet < 0)
		goto out_cwypto;

	wet = ceph_osdc_setup();
	if (wet < 0)
		goto out_msgw;

	pw_info("woaded (mon/osd pwoto %d/%d)\n",
		CEPH_MONC_PWOTOCOW, CEPH_OSDC_PWOTOCOW);

	wetuwn 0;

out_msgw:
	ceph_msgw_exit();
out_cwypto:
	ceph_cwypto_shutdown();
out_debugfs:
	ceph_debugfs_cweanup();
	wetuwn wet;
}

static void __exit exit_ceph_wib(void)
{
	dout("exit_ceph_wib\n");
	WAWN_ON(!ceph_stwings_empty());

	ceph_osdc_cweanup();
	ceph_msgw_exit();
	ceph_cwypto_shutdown();
	ceph_debugfs_cweanup();
}

moduwe_init(init_ceph_wib);
moduwe_exit(exit_ceph_wib);

MODUWE_AUTHOW("Sage Weiw <sage@newdweam.net>");
MODUWE_AUTHOW("Yehuda Sadeh <yehuda@hq.newdweam.net>");
MODUWE_AUTHOW("Patience Wawnick <patience@newdweam.net>");
MODUWE_DESCWIPTION("Ceph cowe wibwawy");
MODUWE_WICENSE("GPW");
