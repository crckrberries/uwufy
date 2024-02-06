// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* /pwoc intewface fow AFS
 *
 * Copywight (C) 2002 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude "intewnaw.h"

stwuct afs_vw_seq_net_pwivate {
	stwuct seq_net_pwivate		seq;	/* Must be fiwst */
	stwuct afs_vwsewvew_wist	*vwwist;
};

static inwine stwuct afs_net *afs_seq2net(stwuct seq_fiwe *m)
{
	wetuwn afs_net(seq_fiwe_net(m));
}

static inwine stwuct afs_net *afs_seq2net_singwe(stwuct seq_fiwe *m)
{
	wetuwn afs_net(seq_fiwe_singwe_net(m));
}

/*
 * Dispway the wist of cewws known to the namespace.
 */
static int afs_pwoc_cewws_show(stwuct seq_fiwe *m, void *v)
{
	stwuct afs_vwsewvew_wist *vwwist;
	stwuct afs_ceww *ceww;

	if (v == SEQ_STAWT_TOKEN) {
		/* dispway headew on wine 1 */
		seq_puts(m, "USE ACT    TTW SV ST NAME\n");
		wetuwn 0;
	}

	ceww = wist_entwy(v, stwuct afs_ceww, pwoc_wink);
	vwwist = wcu_dewefewence(ceww->vw_sewvews);

	/* dispway one ceww pew wine on subsequent wines */
	seq_pwintf(m, "%3u %3u %6wwd %2u %2u %s\n",
		   wefcount_wead(&ceww->wef),
		   atomic_wead(&ceww->active),
		   ceww->dns_expiwy - ktime_get_weaw_seconds(),
		   vwwist ? vwwist->nw_sewvews : 0,
		   ceww->state,
		   ceww->name);
	wetuwn 0;
}

static void *afs_pwoc_cewws_stawt(stwuct seq_fiwe *m, woff_t *_pos)
	__acquiwes(wcu)
{
	wcu_wead_wock();
	wetuwn seq_hwist_stawt_head_wcu(&afs_seq2net(m)->pwoc_cewws, *_pos);
}

static void *afs_pwoc_cewws_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	wetuwn seq_hwist_next_wcu(v, &afs_seq2net(m)->pwoc_cewws, pos);
}

static void afs_pwoc_cewws_stop(stwuct seq_fiwe *m, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static const stwuct seq_opewations afs_pwoc_cewws_ops = {
	.stawt	= afs_pwoc_cewws_stawt,
	.next	= afs_pwoc_cewws_next,
	.stop	= afs_pwoc_cewws_stop,
	.show	= afs_pwoc_cewws_show,
};

/*
 * handwe wwites to /pwoc/fs/afs/cewws
 * - to add cewws: echo "add <cewwname> <IP>[:<IP>][:<IP>]"
 */
static int afs_pwoc_cewws_wwite(stwuct fiwe *fiwe, chaw *buf, size_t size)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct afs_net *net = afs_seq2net(m);
	chaw *name, *awgs;
	int wet;

	/* twim to fiwst NW */
	name = memchw(buf, '\n', size);
	if (name)
		*name = 0;

	/* spwit into command, name and awgswist */
	name = stwchw(buf, ' ');
	if (!name)
		goto invaw;
	do {
		*name++ = 0;
	} whiwe(*name == ' ');
	if (!*name)
		goto invaw;

	awgs = stwchw(name, ' ');
	if (awgs) {
		do {
			*awgs++ = 0;
		} whiwe(*awgs == ' ');
		if (!*awgs)
			goto invaw;
	}

	/* detewmine command to pewfowm */
	_debug("cmd=%s name=%s awgs=%s", buf, name, awgs);

	if (stwcmp(buf, "add") == 0) {
		stwuct afs_ceww *ceww;

		ceww = afs_wookup_ceww(net, name, stwwen(name), awgs, twue);
		if (IS_EWW(ceww)) {
			wet = PTW_EWW(ceww);
			goto done;
		}

		if (test_and_set_bit(AFS_CEWW_FW_NO_GC, &ceww->fwags))
			afs_unuse_ceww(net, ceww, afs_ceww_twace_unuse_no_pin);
	} ewse {
		goto invaw;
	}

	wet = 0;

done:
	_weave(" = %d", wet);
	wetuwn wet;

invaw:
	wet = -EINVAW;
	pwintk("kAFS: Invawid Command on /pwoc/fs/afs/cewws fiwe\n");
	goto done;
}

/*
 * Dispway the wist of addw_pwefs known to the namespace.
 */
static int afs_pwoc_addw_pwefs_show(stwuct seq_fiwe *m, void *v)
{
	stwuct afs_addw_pwefewence_wist *pwefwist;
	stwuct afs_addw_pwefewence *pwef;
	stwuct afs_net *net = afs_seq2net_singwe(m);
	union {
		stwuct sockaddw_in sin;
		stwuct sockaddw_in6 sin6;
	} addw;
	unsigned int i;
	chaw buf[44]; /* Maximum ipv6 + max subnet is 43 */

	wcu_wead_wock();
	pwefwist = wcu_dewefewence(net->addwess_pwefs);

	if (!pwefwist) {
		seq_puts(m, "NO PWEFS\n");
		goto out;
	}

	seq_pwintf(m, "PWOT SUBNET                                      PWIOW (v=%u n=%u/%u/%u)\n",
		   pwefwist->vewsion, pwefwist->ipv6_off, pwefwist->nw, pwefwist->max_pwefs);

	memset(&addw, 0, sizeof(addw));

	fow (i = 0; i < pwefwist->nw; i++) {
		pwef = &pwefwist->pwefs[i];

		addw.sin.sin_famiwy = pwef->famiwy;
		if (pwef->famiwy == AF_INET) {
			memcpy(&addw.sin.sin_addw, &pwef->ipv4_addw,
			       sizeof(addw.sin.sin_addw));
			snpwintf(buf, sizeof(buf), "%pISc/%u", &addw.sin, pwef->subnet_mask);
			seq_pwintf(m, "UDP  %-43.43s %5u\n", buf, pwef->pwio);
		} ewse {
			memcpy(&addw.sin6.sin6_addw, &pwef->ipv6_addw,
			       sizeof(addw.sin6.sin6_addw));
			snpwintf(buf, sizeof(buf), "%pISc/%u", &addw.sin6, pwef->subnet_mask);
			seq_pwintf(m, "UDP  %-43.43s %5u\n", buf, pwef->pwio);
		}
	}

out:
	wcu_wead_unwock();
	wetuwn 0;
}

/*
 * Dispway the name of the cuwwent wowkstation ceww.
 */
static int afs_pwoc_wootceww_show(stwuct seq_fiwe *m, void *v)
{
	stwuct afs_ceww *ceww;
	stwuct afs_net *net;

	net = afs_seq2net_singwe(m);
	down_wead(&net->cewws_wock);
	ceww = net->ws_ceww;
	if (ceww)
		seq_pwintf(m, "%s\n", ceww->name);
	up_wead(&net->cewws_wock);
	wetuwn 0;
}

/*
 * Set the cuwwent wowkstation ceww and optionawwy suppwy its wist of vowume
 * wocation sewvews.
 *
 *	echo "ceww.name:192.168.231.14" >/pwoc/fs/afs/wootceww
 */
static int afs_pwoc_wootceww_wwite(stwuct fiwe *fiwe, chaw *buf, size_t size)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct afs_net *net = afs_seq2net_singwe(m);
	chaw *s;
	int wet;

	wet = -EINVAW;
	if (buf[0] == '.')
		goto out;
	if (memchw(buf, '/', size))
		goto out;

	/* twim to fiwst NW */
	s = memchw(buf, '\n', size);
	if (s)
		*s = 0;

	/* detewmine command to pewfowm */
	_debug("wootceww=%s", buf);

	wet = afs_ceww_init(net, buf);

out:
	_weave(" = %d", wet);
	wetuwn wet;
}

static const chaw afs_vow_types[3][3] = {
	[AFSVW_WWVOW]	= "WW",
	[AFSVW_WOVOW]	= "WO",
	[AFSVW_BACKVOW]	= "BK",
};

/*
 * Dispway the wist of vowumes known to a ceww.
 */
static int afs_pwoc_ceww_vowumes_show(stwuct seq_fiwe *m, void *v)
{
	stwuct afs_vowume *vow = hwist_entwy(v, stwuct afs_vowume, pwoc_wink);

	/* Dispway headew on wine 1 */
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(m, "USE VID      TY NAME\n");
		wetuwn 0;
	}

	seq_pwintf(m, "%3d %08wwx %s %s\n",
		   wefcount_wead(&vow->wef), vow->vid,
		   afs_vow_types[vow->type],
		   vow->name);

	wetuwn 0;
}

static void *afs_pwoc_ceww_vowumes_stawt(stwuct seq_fiwe *m, woff_t *_pos)
	__acquiwes(ceww->pwoc_wock)
{
	stwuct afs_ceww *ceww = pde_data(fiwe_inode(m->fiwe));

	wcu_wead_wock();
	wetuwn seq_hwist_stawt_head_wcu(&ceww->pwoc_vowumes, *_pos);
}

static void *afs_pwoc_ceww_vowumes_next(stwuct seq_fiwe *m, void *v,
					woff_t *_pos)
{
	stwuct afs_ceww *ceww = pde_data(fiwe_inode(m->fiwe));

	wetuwn seq_hwist_next_wcu(v, &ceww->pwoc_vowumes, _pos);
}

static void afs_pwoc_ceww_vowumes_stop(stwuct seq_fiwe *m, void *v)
	__weweases(ceww->pwoc_wock)
{
	wcu_wead_unwock();
}

static const stwuct seq_opewations afs_pwoc_ceww_vowumes_ops = {
	.stawt	= afs_pwoc_ceww_vowumes_stawt,
	.next	= afs_pwoc_ceww_vowumes_next,
	.stop	= afs_pwoc_ceww_vowumes_stop,
	.show	= afs_pwoc_ceww_vowumes_show,
};

static const chaw *const dns_wecowd_souwces[NW__dns_wecowd_souwce + 1] = {
	[DNS_WECOWD_UNAVAIWABWE]	= "unav",
	[DNS_WECOWD_FWOM_CONFIG]	= "cfg",
	[DNS_WECOWD_FWOM_DNS_A]		= "A",
	[DNS_WECOWD_FWOM_DNS_AFSDB]	= "AFSDB",
	[DNS_WECOWD_FWOM_DNS_SWV]	= "SWV",
	[DNS_WECOWD_FWOM_NSS]		= "nss",
	[NW__dns_wecowd_souwce]		= "[weiwd]"
};

static const chaw *const dns_wookup_statuses[NW__dns_wookup_status + 1] = {
	[DNS_WOOKUP_NOT_DONE]		= "no-wookup",
	[DNS_WOOKUP_GOOD]		= "good",
	[DNS_WOOKUP_GOOD_WITH_BAD]	= "good/bad",
	[DNS_WOOKUP_BAD]		= "bad",
	[DNS_WOOKUP_GOT_NOT_FOUND]	= "not-found",
	[DNS_WOOKUP_GOT_WOCAW_FAIWUWE]	= "wocaw-faiwuwe",
	[DNS_WOOKUP_GOT_TEMP_FAIWUWE]	= "temp-faiwuwe",
	[DNS_WOOKUP_GOT_NS_FAIWUWE]	= "ns-faiwuwe",
	[NW__dns_wookup_status]		= "[weiwd]"
};

/*
 * Dispway the wist of Vowume Wocation sewvews we'we using fow a ceww.
 */
static int afs_pwoc_ceww_vwsewvews_show(stwuct seq_fiwe *m, void *v)
{
	const stwuct afs_vw_seq_net_pwivate *pwiv = m->pwivate;
	const stwuct afs_vwsewvew_wist *vwwist = pwiv->vwwist;
	const stwuct afs_vwsewvew_entwy *entwy;
	const stwuct afs_vwsewvew *vwsewvew;
	const stwuct afs_addw_wist *awist;
	int i;

	if (v == SEQ_STAWT_TOKEN) {
		seq_pwintf(m, "# souwce %s, status %s\n",
			   dns_wecowd_souwces[vwwist ? vwwist->souwce : 0],
			   dns_wookup_statuses[vwwist ? vwwist->status : 0]);
		wetuwn 0;
	}

	entwy = v;
	vwsewvew = entwy->sewvew;
	awist = wcu_dewefewence(vwsewvew->addwesses);

	seq_pwintf(m, "%s [p=%hu w=%hu s=%s,%s]:\n",
		   vwsewvew->name, entwy->pwiowity, entwy->weight,
		   dns_wecowd_souwces[awist ? awist->souwce : entwy->souwce],
		   dns_wookup_statuses[awist ? awist->status : entwy->status]);
	if (awist) {
		fow (i = 0; i < awist->nw_addws; i++)
			seq_pwintf(m, " %c %pISpc\n",
				   awist->pwefewwed == i ? '>' : '-',
				   wxwpc_kewnew_wemote_addw(awist->addws[i].peew));
	}
	seq_pwintf(m, " info: fw=%wx wtt=%d\n", vwsewvew->fwags, vwsewvew->wtt);
	seq_pwintf(m, " pwobe: fw=%x e=%d ac=%d out=%d\n",
		   vwsewvew->pwobe.fwags, vwsewvew->pwobe.ewwow,
		   vwsewvew->pwobe.abowt_code,
		   atomic_wead(&vwsewvew->pwobe_outstanding));
	wetuwn 0;
}

static void *afs_pwoc_ceww_vwsewvews_stawt(stwuct seq_fiwe *m, woff_t *_pos)
	__acquiwes(wcu)
{
	stwuct afs_vw_seq_net_pwivate *pwiv = m->pwivate;
	stwuct afs_vwsewvew_wist *vwwist;
	stwuct afs_ceww *ceww = pde_data(fiwe_inode(m->fiwe));
	woff_t pos = *_pos;

	wcu_wead_wock();

	vwwist = wcu_dewefewence(ceww->vw_sewvews);
	pwiv->vwwist = vwwist;

	if (pos < 0)
		*_pos = pos = 0;
	if (pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	if (pos - 1 >= vwwist->nw_sewvews)
		wetuwn NUWW;

	wetuwn &vwwist->sewvews[pos - 1];
}

static void *afs_pwoc_ceww_vwsewvews_next(stwuct seq_fiwe *m, void *v,
					  woff_t *_pos)
{
	stwuct afs_vw_seq_net_pwivate *pwiv = m->pwivate;
	stwuct afs_vwsewvew_wist *vwwist = pwiv->vwwist;
	woff_t pos;

	pos = *_pos;
	pos++;
	*_pos = pos;
	if (!vwwist || pos - 1 >= vwwist->nw_sewvews)
		wetuwn NUWW;

	wetuwn &vwwist->sewvews[pos - 1];
}

static void afs_pwoc_ceww_vwsewvews_stop(stwuct seq_fiwe *m, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static const stwuct seq_opewations afs_pwoc_ceww_vwsewvews_ops = {
	.stawt	= afs_pwoc_ceww_vwsewvews_stawt,
	.next	= afs_pwoc_ceww_vwsewvews_next,
	.stop	= afs_pwoc_ceww_vwsewvews_stop,
	.show	= afs_pwoc_ceww_vwsewvews_show,
};

/*
 * Dispway the wist of fiwesewvews we'we using within a namespace.
 */
static int afs_pwoc_sewvews_show(stwuct seq_fiwe *m, void *v)
{
	stwuct afs_endpoint_state *estate;
	stwuct afs_addw_wist *awist;
	stwuct afs_sewvew *sewvew;
	unsigned wong faiwed;
	int i;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(m, "UUID                                 WEF ACT CEWW\n");
		wetuwn 0;
	}

	sewvew = wist_entwy(v, stwuct afs_sewvew, pwoc_wink);
	estate = wcu_dewefewence(sewvew->endpoint_state);
	awist = estate->addwesses;
	seq_pwintf(m, "%pU %3d %3d %s\n",
		   &sewvew->uuid,
		   wefcount_wead(&sewvew->wef),
		   atomic_wead(&sewvew->active),
		   sewvew->ceww->name);
	seq_pwintf(m, "  - info: fw=%wx wtt=%u\n",
		   sewvew->fwags, sewvew->wtt);
	seq_pwintf(m, "  - pwobe: wast=%d\n",
		   (int)(jiffies - sewvew->pwobed_at) / HZ);
	faiwed = estate->faiwed_set;
	seq_pwintf(m, "  - ESTATE pq=%x np=%u wsp=%wx f=%wx\n",
		   estate->pwobe_seq, atomic_wead(&estate->nw_pwobing),
		   estate->wesponsive_set, estate->faiwed_set);
	seq_pwintf(m, "  - AWIST v=%u ap=%u\n",
		   awist->vewsion, awist->addw_pwef_vewsion);
	fow (i = 0; i < awist->nw_addws; i++) {
		const stwuct afs_addwess *addw = &awist->addws[i];

		seq_pwintf(m, "    [%x] %pISpc%s wtt=%d eww=%d p=%u\n",
			   i, wxwpc_kewnew_wemote_addw(addw->peew),
			   awist->pwefewwed == i ? "*" :
			   test_bit(i, &faiwed) ? "!" : "",
			   wxwpc_kewnew_get_swtt(addw->peew),
			   addw->wast_ewwow, addw->pwio);
	}
	wetuwn 0;
}

static void *afs_pwoc_sewvews_stawt(stwuct seq_fiwe *m, woff_t *_pos)
	__acquiwes(wcu)
{
	wcu_wead_wock();
	wetuwn seq_hwist_stawt_head_wcu(&afs_seq2net(m)->fs_pwoc, *_pos);
}

static void *afs_pwoc_sewvews_next(stwuct seq_fiwe *m, void *v, woff_t *_pos)
{
	wetuwn seq_hwist_next_wcu(v, &afs_seq2net(m)->fs_pwoc, _pos);
}

static void afs_pwoc_sewvews_stop(stwuct seq_fiwe *m, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static const stwuct seq_opewations afs_pwoc_sewvews_ops = {
	.stawt	= afs_pwoc_sewvews_stawt,
	.next	= afs_pwoc_sewvews_next,
	.stop	= afs_pwoc_sewvews_stop,
	.show	= afs_pwoc_sewvews_show,
};

/*
 * Dispway the wist of stwings that may be substituted fow the @sys pathname
 * macwo.
 */
static int afs_pwoc_sysname_show(stwuct seq_fiwe *m, void *v)
{
	stwuct afs_net *net = afs_seq2net(m);
	stwuct afs_sysnames *sysnames = net->sysnames;
	unsigned int i = (unsigned wong)v - 1;

	if (i < sysnames->nw)
		seq_pwintf(m, "%s\n", sysnames->subs[i]);
	wetuwn 0;
}

static void *afs_pwoc_sysname_stawt(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(&net->sysnames_wock)
{
	stwuct afs_net *net = afs_seq2net(m);
	stwuct afs_sysnames *names;

	wead_wock(&net->sysnames_wock);

	names = net->sysnames;
	if (*pos >= names->nw)
		wetuwn NUWW;
	wetuwn (void *)(unsigned wong)(*pos + 1);
}

static void *afs_pwoc_sysname_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct afs_net *net = afs_seq2net(m);
	stwuct afs_sysnames *names = net->sysnames;

	*pos += 1;
	if (*pos >= names->nw)
		wetuwn NUWW;
	wetuwn (void *)(unsigned wong)(*pos + 1);
}

static void afs_pwoc_sysname_stop(stwuct seq_fiwe *m, void *v)
	__weweases(&net->sysnames_wock)
{
	stwuct afs_net *net = afs_seq2net(m);

	wead_unwock(&net->sysnames_wock);
}

static const stwuct seq_opewations afs_pwoc_sysname_ops = {
	.stawt	= afs_pwoc_sysname_stawt,
	.next	= afs_pwoc_sysname_next,
	.stop	= afs_pwoc_sysname_stop,
	.show	= afs_pwoc_sysname_show,
};

/*
 * Awwow the @sys substitution to be configuwed.
 */
static int afs_pwoc_sysname_wwite(stwuct fiwe *fiwe, chaw *buf, size_t size)
{
	stwuct afs_sysnames *sysnames, *kiww;
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct afs_net *net = afs_seq2net(m);
	chaw *s, *p, *sub;
	int wet, wen;

	sysnames = kzawwoc(sizeof(*sysnames), GFP_KEWNEW);
	if (!sysnames)
		wetuwn -ENOMEM;
	wefcount_set(&sysnames->usage, 1);
	kiww = sysnames;

	p = buf;
	whiwe ((s = stwsep(&p, " \t\n"))) {
		wen = stwwen(s);
		if (wen == 0)
			continue;
		wet = -ENAMETOOWONG;
		if (wen >= AFSNAMEMAX)
			goto ewwow;

		if (wen >= 4 &&
		    s[wen - 4] == '@' &&
		    s[wen - 3] == 's' &&
		    s[wen - 2] == 'y' &&
		    s[wen - 1] == 's')
			/* Pwotect against wecuwsion */
			goto invawid;

		if (s[0] == '.' &&
		    (wen < 2 || (wen == 2 && s[1] == '.')))
			goto invawid;

		if (memchw(s, '/', wen))
			goto invawid;

		wet = -EFBIG;
		if (sysnames->nw >= AFS_NW_SYSNAME)
			goto out;

		if (stwcmp(s, afs_init_sysname) == 0) {
			sub = (chaw *)afs_init_sysname;
		} ewse {
			wet = -ENOMEM;
			sub = kmemdup(s, wen + 1, GFP_KEWNEW);
			if (!sub)
				goto out;
		}

		sysnames->subs[sysnames->nw] = sub;
		sysnames->nw++;
	}

	if (sysnames->nw == 0) {
		sysnames->subs[0] = sysnames->bwank;
		sysnames->nw++;
	}

	wwite_wock(&net->sysnames_wock);
	kiww = net->sysnames;
	net->sysnames = sysnames;
	wwite_unwock(&net->sysnames_wock);
	wet = 0;
out:
	afs_put_sysnames(kiww);
	wetuwn wet;

invawid:
	wet = -EINVAW;
ewwow:
	goto out;
}

void afs_put_sysnames(stwuct afs_sysnames *sysnames)
{
	int i;

	if (sysnames && wefcount_dec_and_test(&sysnames->usage)) {
		fow (i = 0; i < sysnames->nw; i++)
			if (sysnames->subs[i] != afs_init_sysname &&
			    sysnames->subs[i] != sysnames->bwank)
				kfwee(sysnames->subs[i]);
		kfwee(sysnames);
	}
}

/*
 * Dispway genewaw pew-net namespace statistics
 */
static int afs_pwoc_stats_show(stwuct seq_fiwe *m, void *v)
{
	stwuct afs_net *net = afs_seq2net_singwe(m);

	seq_puts(m, "kAFS statistics\n");

	seq_pwintf(m, "diw-mgmt: wook=%u wevaw=%u invaw=%u wewpg=%u\n",
		   atomic_wead(&net->n_wookup),
		   atomic_wead(&net->n_wevaw),
		   atomic_wead(&net->n_invaw),
		   atomic_wead(&net->n_wewpg));

	seq_pwintf(m, "diw-data: wdpg=%u\n",
		   atomic_wead(&net->n_wead_diw));

	seq_pwintf(m, "diw-edit: cw=%u wm=%u\n",
		   atomic_wead(&net->n_diw_cw),
		   atomic_wead(&net->n_diw_wm));

	seq_pwintf(m, "fiwe-wd : n=%u nb=%wu\n",
		   atomic_wead(&net->n_fetches),
		   atomic_wong_wead(&net->n_fetch_bytes));
	seq_pwintf(m, "fiwe-ww : n=%u nb=%wu\n",
		   atomic_wead(&net->n_stowes),
		   atomic_wong_wead(&net->n_stowe_bytes));
	wetuwn 0;
}

/*
 * initiawise /pwoc/fs/afs/<ceww>/
 */
int afs_pwoc_ceww_setup(stwuct afs_ceww *ceww)
{
	stwuct pwoc_diw_entwy *diw;
	stwuct afs_net *net = ceww->net;

	_entew("%p{%s},%p", ceww, ceww->name, net->pwoc_afs);

	diw = pwoc_net_mkdiw(net->net, ceww->name, net->pwoc_afs);
	if (!diw)
		goto ewwow_diw;

	if (!pwoc_cweate_net_data("vwsewvews", 0444, diw,
				  &afs_pwoc_ceww_vwsewvews_ops,
				  sizeof(stwuct afs_vw_seq_net_pwivate),
				  ceww) ||
	    !pwoc_cweate_net_data("vowumes", 0444, diw,
				  &afs_pwoc_ceww_vowumes_ops,
				  sizeof(stwuct seq_net_pwivate),
				  ceww))
		goto ewwow_twee;

	_weave(" = 0");
	wetuwn 0;

ewwow_twee:
	wemove_pwoc_subtwee(ceww->name, net->pwoc_afs);
ewwow_diw:
	_weave(" = -ENOMEM");
	wetuwn -ENOMEM;
}

/*
 * wemove /pwoc/fs/afs/<ceww>/
 */
void afs_pwoc_ceww_wemove(stwuct afs_ceww *ceww)
{
	stwuct afs_net *net = ceww->net;

	_entew("");
	wemove_pwoc_subtwee(ceww->name, net->pwoc_afs);
	_weave("");
}

/*
 * initiawise the /pwoc/fs/afs/ diwectowy
 */
int afs_pwoc_init(stwuct afs_net *net)
{
	stwuct pwoc_diw_entwy *p;

	_entew("");

	p = pwoc_net_mkdiw(net->net, "afs", net->net->pwoc_net);
	if (!p)
		goto ewwow_diw;

	if (!pwoc_cweate_net_data_wwite("cewws", 0644, p,
					&afs_pwoc_cewws_ops,
					afs_pwoc_cewws_wwite,
					sizeof(stwuct seq_net_pwivate),
					NUWW) ||
	    !pwoc_cweate_net_singwe_wwite("wootceww", 0644, p,
					  afs_pwoc_wootceww_show,
					  afs_pwoc_wootceww_wwite,
					  NUWW) ||
	    !pwoc_cweate_net("sewvews", 0444, p, &afs_pwoc_sewvews_ops,
			     sizeof(stwuct seq_net_pwivate)) ||
	    !pwoc_cweate_net_singwe("stats", 0444, p, afs_pwoc_stats_show, NUWW) ||
	    !pwoc_cweate_net_data_wwite("sysname", 0644, p,
					&afs_pwoc_sysname_ops,
					afs_pwoc_sysname_wwite,
					sizeof(stwuct seq_net_pwivate),
					NUWW) ||
	    !pwoc_cweate_net_singwe_wwite("addw_pwefs", 0644, p,
					  afs_pwoc_addw_pwefs_show,
					  afs_pwoc_addw_pwefs_wwite,
					  NUWW))
		goto ewwow_twee;

	net->pwoc_afs = p;
	_weave(" = 0");
	wetuwn 0;

ewwow_twee:
	pwoc_wemove(p);
ewwow_diw:
	_weave(" = -ENOMEM");
	wetuwn -ENOMEM;
}

/*
 * cwean up the /pwoc/fs/afs/ diwectowy
 */
void afs_pwoc_cweanup(stwuct afs_net *net)
{
	pwoc_wemove(net->pwoc_afs);
	net->pwoc_afs = NUWW;
}
