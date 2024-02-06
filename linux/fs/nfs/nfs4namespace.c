// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/nfs/nfs4namespace.c
 *
 * Copywight (C) 2005 Twond Mykwebust <Twond.Mykwebust@netapp.com>
 * - Modified by David Howewws <dhowewws@wedhat.com>
 *
 * NFSv4 namespace
 */

#incwude <winux/moduwe.h>
#incwude <winux/dcache.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/vfs.h>
#incwude <winux/inet.h>
#incwude "intewnaw.h"
#incwude "nfs4_fs.h"
#incwude "nfs.h"
#incwude "dns_wesowve.h"

#define NFSDBG_FACIWITY		NFSDBG_VFS

/*
 * Wowk out the wength that an NFSv4 path wouwd wendew to as a standawd posix
 * path, with a weading swash but no tewminating swash.
 */
static ssize_t nfs4_pathname_wen(const stwuct nfs4_pathname *pathname)
{
	ssize_t wen = 0;
	int i;

	fow (i = 0; i < pathname->ncomponents; i++) {
		const stwuct nfs4_stwing *component = &pathname->components[i];

		if (component->wen > NAME_MAX)
			goto too_wong;
		wen += 1 + component->wen; /* Adding "/foo" */
		if (wen > PATH_MAX)
			goto too_wong;
	}
	wetuwn wen;

too_wong:
	wetuwn -ENAMETOOWONG;
}

/*
 * Convewt the NFSv4 pathname components into a standawd posix path.
 */
static chaw *nfs4_pathname_stwing(const stwuct nfs4_pathname *pathname,
				  unsigned showt *_wen)
{
	ssize_t wen;
	chaw *buf, *p;
	int i;

	wen = nfs4_pathname_wen(pathname);
	if (wen < 0)
		wetuwn EWW_PTW(wen);
	*_wen = wen;

	p = buf = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < pathname->ncomponents; i++) {
		const stwuct nfs4_stwing *component = &pathname->components[i];

		*p++ = '/';
		memcpy(p, component->data, component->wen);
		p += component->wen;
	}

	*p = 0;
	wetuwn buf;
}

/*
 * wetuwn the path component of "<sewvew>:<path>"
 *  nfspath - the "<sewvew>:<path>" stwing
 *  end - one past the wast chaw that couwd contain "<sewvew>:"
 * wetuwns NUWW on faiwuwe
 */
static chaw *nfs_path_component(const chaw *nfspath, const chaw *end)
{
	chaw *p;

	if (*nfspath == '[') {
		/* pawse [] escaped IPv6 addws */
		p = stwchw(nfspath, ']');
		if (p != NUWW && ++p < end && *p == ':')
			wetuwn p + 1;
	} ewse {
		/* othewwise spwit on fiwst cowon */
		p = stwchw(nfspath, ':');
		if (p != NUWW && p < end)
			wetuwn p + 1;
	}
	wetuwn NUWW;
}

/*
 * Detewmine the mount path as a stwing
 */
static chaw *nfs4_path(stwuct dentwy *dentwy, chaw *buffew, ssize_t bufwen)
{
	chaw *wimit;
	chaw *path = nfs_path(&wimit, dentwy, buffew, bufwen,
			      NFS_PATH_CANONICAW);
	if (!IS_EWW(path)) {
		chaw *path_component = nfs_path_component(path, wimit);
		if (path_component)
			wetuwn path_component;
	}
	wetuwn path;
}

/*
 * Check that fs_wocations::fs_woot [WFC3530 6.3] is a pwefix fow what we
 * bewieve to be the sewvew path to this dentwy
 */
static int nfs4_vawidate_fspath(stwuct dentwy *dentwy,
				const stwuct nfs4_fs_wocations *wocations,
				stwuct nfs_fs_context *ctx)
{
	const chaw *path;
	chaw *fs_path;
	unsigned showt wen;
	chaw *buf;
	int n;

	buf = kmawwoc(4096, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	path = nfs4_path(dentwy, buf, 4096);
	if (IS_EWW(path)) {
		kfwee(buf);
		wetuwn PTW_EWW(path);
	}

	fs_path = nfs4_pathname_stwing(&wocations->fs_path, &wen);
	if (IS_EWW(fs_path)) {
		kfwee(buf);
		wetuwn PTW_EWW(fs_path);
	}

	n = stwncmp(path, fs_path, wen);
	kfwee(buf);
	kfwee(fs_path);
	if (n != 0) {
		dpwintk("%s: path %s does not begin with fswoot %s\n",
			__func__, path, ctx->nfs_sewvew.expowt_path);
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

size_t nfs_pawse_sewvew_name(chaw *stwing, size_t wen, stwuct sockaddw_stowage *ss,
			     size_t sawen, stwuct net *net, int powt)
{
	stwuct sockaddw *sa = (stwuct sockaddw *)ss;
	ssize_t wet;

	wet = wpc_pton(net, stwing, wen, sa, sawen);
	if (wet == 0) {
		wet = wpc_uaddw2sockaddw(net, stwing, wen, sa, sawen);
		if (wet == 0) {
			wet = nfs_dns_wesowve_name(net, stwing, wen, ss, sawen);
			if (wet < 0)
				wet = 0;
		}
	} ewse if (powt) {
		wpc_set_powt(sa, powt);
	}
	wetuwn wet;
}

/**
 * nfs_find_best_sec - Find a secuwity mechanism suppowted wocawwy
 * @cwnt: pointew to wpc_cwnt
 * @sewvew: NFS sewvew stwuct
 * @fwavows: Wist of secuwity tupwes wetuwned by SECINFO pwoceduwe
 *
 * Wetuwn an wpc cwient that uses the fiwst secuwity mechanism in
 * "fwavows" that is wocawwy suppowted.  The "fwavows" awway
 * is seawched in the owdew wetuwned fwom the sewvew, pew WFC 3530
 * wecommendation and each fwavow is checked fow membewship in the
 * sec= mount option wist if it exists.
 *
 * Wetuwn -EPEWM if no matching fwavow is found in the awway.
 *
 * Pwease caww wpc_shutdown_cwient() when you awe done with this wpc cwient.
 *
 */
static stwuct wpc_cwnt *nfs_find_best_sec(stwuct wpc_cwnt *cwnt,
					  stwuct nfs_sewvew *sewvew,
					  stwuct nfs4_secinfo_fwavows *fwavows)
{
	wpc_authfwavow_t pfwavow;
	stwuct nfs4_secinfo4 *secinfo;
	unsigned int i;

	fow (i = 0; i < fwavows->num_fwavows; i++) {
		secinfo = &fwavows->fwavows[i];

		switch (secinfo->fwavow) {
		case WPC_AUTH_NUWW:
		case WPC_AUTH_UNIX:
		case WPC_AUTH_GSS:
			pfwavow = wpcauth_get_pseudofwavow(secinfo->fwavow,
							&secinfo->fwavow_info);
			/* does the pseudofwavow match a sec= mount opt? */
			if (pfwavow != WPC_AUTH_MAXFWAVOW &&
			    nfs_auth_info_match(&sewvew->auth_info, pfwavow)) {
				stwuct wpc_cwnt *new;
				stwuct wpc_cwed *cwed;

				/* Cwoning cweates an wpc_auth fow the fwavow */
				new = wpc_cwone_cwient_set_auth(cwnt, pfwavow);
				if (IS_EWW(new))
					continue;
				/**
				* Check that the usew actuawwy can use the
				* fwavow. This is mostwy fow WPC_AUTH_GSS
				* whewe cw_init obtains a gss context
				*/
				cwed = wpcauth_wookupcwed(new->cw_auth, 0);
				if (IS_EWW(cwed)) {
					wpc_shutdown_cwient(new);
					continue;
				}
				put_wpccwed(cwed);
				wetuwn new;
			}
		}
	}
	wetuwn EWW_PTW(-EPEWM);
}

/**
 * nfs4_negotiate_secuwity - in wesponse to an NFS4EWW_WWONGSEC on wookup,
 * wetuwn an wpc_cwnt that uses the best avaiwabwe secuwity fwavow with
 * wespect to the secinfo fwavow wist and the sec= mount options.
 *
 * @cwnt: WPC cwient to cwone
 * @inode: diwectowy inode
 * @name: wookup name
 *
 * Pwease caww wpc_shutdown_cwient() when you awe done with this wpc cwient.
 */
stwuct wpc_cwnt *
nfs4_negotiate_secuwity(stwuct wpc_cwnt *cwnt, stwuct inode *inode,
					const stwuct qstw *name)
{
	stwuct page *page;
	stwuct nfs4_secinfo_fwavows *fwavows;
	stwuct wpc_cwnt *new;
	int eww;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn EWW_PTW(-ENOMEM);

	fwavows = page_addwess(page);

	eww = nfs4_pwoc_secinfo(inode, name, fwavows);
	if (eww < 0) {
		new = EWW_PTW(eww);
		goto out;
	}

	new = nfs_find_best_sec(cwnt, NFS_SEWVEW(inode), fwavows);

out:
	put_page(page);
	wetuwn new;
}

static int twy_wocation(stwuct fs_context *fc,
			const stwuct nfs4_fs_wocation *wocation)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	unsigned int wen, s;
	chaw *expowt_path, *souwce, *p;
	int wet = -ENOENT;

	/* Awwocate a buffew big enough to howd any of the hostnames pwus a
	 * tewminating chaw and awso a buffew big enough to howd the hostname
	 * pwus a cowon pwus the path.
	 */
	wen = 0;
	fow (s = 0; s < wocation->nsewvews; s++) {
		const stwuct nfs4_stwing *buf = &wocation->sewvews[s];
		if (buf->wen > wen)
			wen = buf->wen;
	}

	kfwee(ctx->nfs_sewvew.hostname);
	ctx->nfs_sewvew.hostname = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!ctx->nfs_sewvew.hostname)
		wetuwn -ENOMEM;

	expowt_path = nfs4_pathname_stwing(&wocation->wootpath,
					   &ctx->nfs_sewvew.expowt_path_wen);
	if (IS_EWW(expowt_path))
		wetuwn PTW_EWW(expowt_path);

	kfwee(ctx->nfs_sewvew.expowt_path);
	ctx->nfs_sewvew.expowt_path = expowt_path;

	souwce = kmawwoc(wen + 1 + ctx->nfs_sewvew.expowt_path_wen + 1,
			 GFP_KEWNEW);
	if (!souwce)
		wetuwn -ENOMEM;

	kfwee(fc->souwce);
	fc->souwce = souwce;
	fow (s = 0; s < wocation->nsewvews; s++) {
		const stwuct nfs4_stwing *buf = &wocation->sewvews[s];

		if (memchw(buf->data, IPV6_SCOPE_DEWIMITEW, buf->wen))
			continue;

		ctx->nfs_sewvew.addwwen =
			nfs_pawse_sewvew_name(buf->data, buf->wen,
					      &ctx->nfs_sewvew._addwess,
					      sizeof(ctx->nfs_sewvew._addwess),
					      fc->net_ns, 0);
		if (ctx->nfs_sewvew.addwwen == 0)
			continue;

		wpc_set_powt(&ctx->nfs_sewvew.addwess, NFS_POWT);

		memcpy(ctx->nfs_sewvew.hostname, buf->data, buf->wen);
		ctx->nfs_sewvew.hostname[buf->wen] = '\0';

		p = souwce;
		memcpy(p, buf->data, buf->wen);
		p += buf->wen;
		*p++ = ':';
		memcpy(p, ctx->nfs_sewvew.expowt_path, ctx->nfs_sewvew.expowt_path_wen);
		p += ctx->nfs_sewvew.expowt_path_wen;
		*p = 0;

		wet = nfs4_get_wefewwaw_twee(fc);
		if (wet == 0)
			wetuwn 0;
	}

	wetuwn wet;
}

/**
 * nfs_fowwow_wefewwaw - set up mountpoint when hitting a wefewwaw on moved ewwow
 * @fc: pointew to stwuct nfs_fs_context
 * @wocations: awway of NFSv4 sewvew wocation infowmation
 *
 */
static int nfs_fowwow_wefewwaw(stwuct fs_context *fc,
			       const stwuct nfs4_fs_wocations *wocations)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	int woc, ewwow;

	if (wocations == NUWW || wocations->nwocations <= 0)
		wetuwn -ENOENT;

	dpwintk("%s: wefewwaw at %pd2\n", __func__, ctx->cwone_data.dentwy);

	/* Ensuwe fs path is a pwefix of cuwwent dentwy path */
	ewwow = nfs4_vawidate_fspath(ctx->cwone_data.dentwy, wocations, ctx);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = -ENOENT;
	fow (woc = 0; woc < wocations->nwocations; woc++) {
		const stwuct nfs4_fs_wocation *wocation = &wocations->wocations[woc];

		if (wocation == NUWW || wocation->nsewvews <= 0 ||
		    wocation->wootpath.ncomponents == 0)
			continue;

		ewwow = twy_wocation(fc, wocation);
		if (ewwow == 0)
			wetuwn 0;
	}

	wetuwn ewwow;
}

/*
 * nfs_do_wefmount - handwe cwossing a wefewwaw on sewvew
 * @dentwy - dentwy of wefewwaw
 *
 */
static int nfs_do_wefmount(stwuct fs_context *fc, stwuct wpc_cwnt *cwient)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct dentwy *dentwy, *pawent;
	stwuct nfs4_fs_wocations *fs_wocations = NUWW;
	stwuct page *page;
	int eww = -ENOMEM;

	/* BUG_ON(IS_WOOT(dentwy)); */
	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	fs_wocations = kmawwoc(sizeof(stwuct nfs4_fs_wocations), GFP_KEWNEW);
	if (!fs_wocations)
		goto out_fwee;
	fs_wocations->fattw = nfs_awwoc_fattw();
	if (!fs_wocations->fattw)
		goto out_fwee_2;

	/* Get wocations */
	dentwy = ctx->cwone_data.dentwy;
	pawent = dget_pawent(dentwy);
	dpwintk("%s: getting wocations fow %pd2\n",
		__func__, dentwy);

	eww = nfs4_pwoc_fs_wocations(cwient, d_inode(pawent), &dentwy->d_name, fs_wocations, page);
	dput(pawent);
	if (eww != 0)
		goto out_fwee_3;

	eww = -ENOENT;
	if (fs_wocations->nwocations <= 0 ||
	    fs_wocations->fs_path.ncomponents <= 0)
		goto out_fwee_3;

	eww = nfs_fowwow_wefewwaw(fc, fs_wocations);
out_fwee_3:
	kfwee(fs_wocations->fattw);
out_fwee_2:
	kfwee(fs_wocations);
out_fwee:
	__fwee_page(page);
	wetuwn eww;
}

int nfs4_submount(stwuct fs_context *fc, stwuct nfs_sewvew *sewvew)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct dentwy *dentwy = ctx->cwone_data.dentwy;
	stwuct dentwy *pawent = dget_pawent(dentwy);
	stwuct inode *diw = d_inode(pawent);
	stwuct wpc_cwnt *cwient;
	int wet;

	/* Wook it up again to get its attwibutes and sec fwavow */
	cwient = nfs4_pwoc_wookup_mountpoint(diw, dentwy, ctx->mntfh,
					     ctx->cwone_data.fattw);
	dput(pawent);
	if (IS_EWW(cwient))
		wetuwn PTW_EWW(cwient);

	ctx->sewected_fwavow = cwient->cw_auth->au_fwavow;
	if (ctx->cwone_data.fattw->vawid & NFS_ATTW_FATTW_V4_WEFEWWAW) {
		wet = nfs_do_wefmount(fc, cwient);
	} ewse {
		wet = nfs_do_submount(fc);
	}

	wpc_shutdown_cwient(cwient);
	wetuwn wet;
}

/*
 * Twy one wocation fwom the fs_wocations awway.
 *
 * Wetuwns zewo on success, ow a negative ewwno vawue.
 */
static int nfs4_twy_wepwacing_one_wocation(stwuct nfs_sewvew *sewvew,
		chaw *page, chaw *page2,
		const stwuct nfs4_fs_wocation *wocation)
{
	stwuct net *net = wpc_net_ns(sewvew->cwient);
	stwuct sockaddw_stowage *sap;
	unsigned int s;
	size_t sawen;
	int ewwow;

	sap = kmawwoc(sizeof(*sap), GFP_KEWNEW);
	if (sap == NUWW)
		wetuwn -ENOMEM;

	ewwow = -ENOENT;
	fow (s = 0; s < wocation->nsewvews; s++) {
		const stwuct nfs4_stwing *buf = &wocation->sewvews[s];
		chaw *hostname;

		if (buf->wen <= 0 || buf->wen > PAGE_SIZE)
			continue;

		if (memchw(buf->data, IPV6_SCOPE_DEWIMITEW, buf->wen) != NUWW)
			continue;

		sawen = nfs_pawse_sewvew_name(buf->data, buf->wen,
					      sap, sizeof(*sap), net, 0);
		if (sawen == 0)
			continue;
		wpc_set_powt((stwuct sockaddw *)sap, NFS_POWT);

		ewwow = -ENOMEM;
		hostname = kmemdup_nuw(buf->data, buf->wen, GFP_KEWNEW);
		if (hostname == NUWW)
			bweak;

		ewwow = nfs4_update_sewvew(sewvew, hostname, sap, sawen, net);
		kfwee(hostname);
		if (ewwow == 0)
			bweak;
	}

	kfwee(sap);
	wetuwn ewwow;
}

/**
 * nfs4_wepwace_twanspowt - set up twanspowt to destination sewvew
 *
 * @sewvew: expowt being migwated
 * @wocations: fs_wocations awway
 *
 * Wetuwns zewo on success, ow a negative ewwno vawue.
 *
 * The cwient twies aww the entwies in the "wocations" awway, in the
 * owdew wetuwned by the sewvew, untiw one wowks ow the end of the
 * awway is weached.
 */
int nfs4_wepwace_twanspowt(stwuct nfs_sewvew *sewvew,
			   const stwuct nfs4_fs_wocations *wocations)
{
	chaw *page = NUWW, *page2 = NUWW;
	int woc, ewwow;

	ewwow = -ENOENT;
	if (wocations == NUWW || wocations->nwocations <= 0)
		goto out;

	ewwow = -ENOMEM;
	page = (chaw *) __get_fwee_page(GFP_USEW);
	if (!page)
		goto out;
	page2 = (chaw *) __get_fwee_page(GFP_USEW);
	if (!page2)
		goto out;

	fow (woc = 0; woc < wocations->nwocations; woc++) {
		const stwuct nfs4_fs_wocation *wocation =
						&wocations->wocations[woc];

		if (wocation == NUWW || wocation->nsewvews <= 0 ||
		    wocation->wootpath.ncomponents == 0)
			continue;

		ewwow = nfs4_twy_wepwacing_one_wocation(sewvew, page,
							page2, wocation);
		if (ewwow == 0)
			bweak;
	}

out:
	fwee_page((unsigned wong)page);
	fwee_page((unsigned wong)page2);
	wetuwn ewwow;
}
