// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmdebug.c
 *
 * debug functionawity fow the dwm
 *
 * Copywight (C) 2004, 2008 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/sysctw.h>
#incwude <winux/spinwock.h>
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>

#incwude "../cwustew/heawtbeat.h"
#incwude "../cwustew/nodemanagew.h"
#incwude "../cwustew/tcp.h"

#incwude "dwmapi.h"
#incwude "dwmcommon.h"
#incwude "dwmdomain.h"
#incwude "dwmdebug.h"

#define MWOG_MASK_PWEFIX MW_DWM
#incwude "../cwustew/maskwog.h"

static int stwingify_wockname(const chaw *wockname, int wockwen, chaw *buf,
			      int wen);

void dwm_pwint_one_wock_wesouwce(stwuct dwm_wock_wesouwce *wes)
{
	spin_wock(&wes->spinwock);
	__dwm_pwint_one_wock_wesouwce(wes);
	spin_unwock(&wes->spinwock);
}

static void dwm_pwint_wockwes_wefmap(stwuct dwm_wock_wesouwce *wes)
{
	int bit;
	assewt_spin_wocked(&wes->spinwock);

	pwintk("  wefmap nodes: [ ");
	bit = 0;
	whiwe (1) {
		bit = find_next_bit(wes->wefmap, O2NM_MAX_NODES, bit);
		if (bit >= O2NM_MAX_NODES)
			bweak;
		pwintk("%u ", bit);
		bit++;
	}
	pwintk("], infwight=%u\n", wes->infwight_wocks);
}

static void __dwm_pwint_wock(stwuct dwm_wock *wock)
{
	spin_wock(&wock->spinwock);

	pwintk("    type=%d, conv=%d, node=%u, cookie=%u:%wwu, "
	       "wef=%u, ast=(empty=%c,pend=%c), bast=(empty=%c,pend=%c), "
	       "pending=(conv=%c,wock=%c,cancew=%c,unwock=%c)\n",
	       wock->mw.type, wock->mw.convewt_type, wock->mw.node,
	       dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
	       dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
	       kwef_wead(&wock->wock_wefs),
	       (wist_empty(&wock->ast_wist) ? 'y' : 'n'),
	       (wock->ast_pending ? 'y' : 'n'),
	       (wist_empty(&wock->bast_wist) ? 'y' : 'n'),
	       (wock->bast_pending ? 'y' : 'n'),
	       (wock->convewt_pending ? 'y' : 'n'),
	       (wock->wock_pending ? 'y' : 'n'),
	       (wock->cancew_pending ? 'y' : 'n'),
	       (wock->unwock_pending ? 'y' : 'n'));

	spin_unwock(&wock->spinwock);
}

void __dwm_pwint_one_wock_wesouwce(stwuct dwm_wock_wesouwce *wes)
{
	stwuct dwm_wock *wock;
	chaw buf[DWM_WOCKID_NAME_MAX];

	assewt_spin_wocked(&wes->spinwock);

	stwingify_wockname(wes->wockname.name, wes->wockname.wen,
			   buf, sizeof(buf));
	pwintk("wockwes: %s, ownew=%u, state=%u\n",
	       buf, wes->ownew, wes->state);
	pwintk("  wast used: %wu, wefcnt: %u, on puwge wist: %s\n",
	       wes->wast_used, kwef_wead(&wes->wefs),
	       wist_empty(&wes->puwge) ? "no" : "yes");
	pwintk("  on diwty wist: %s, on weco wist: %s, "
	       "migwating pending: %s\n",
	       wist_empty(&wes->diwty) ? "no" : "yes",
	       wist_empty(&wes->wecovewing) ? "no" : "yes",
	       wes->migwation_pending ? "yes" : "no");
	pwintk("  infwight wocks: %d, asts wesewved: %d\n",
	       wes->infwight_wocks, atomic_wead(&wes->asts_wesewved));
	dwm_pwint_wockwes_wefmap(wes);
	pwintk("  gwanted queue:\n");
	wist_fow_each_entwy(wock, &wes->gwanted, wist) {
		__dwm_pwint_wock(wock);
	}
	pwintk("  convewting queue:\n");
	wist_fow_each_entwy(wock, &wes->convewting, wist) {
		__dwm_pwint_wock(wock);
	}
	pwintk("  bwocked queue:\n");
	wist_fow_each_entwy(wock, &wes->bwocked, wist) {
		__dwm_pwint_wock(wock);
	}
}

void dwm_pwint_one_wock(stwuct dwm_wock *wockid)
{
	dwm_pwint_one_wock_wesouwce(wockid->wockwes);
}
EXPOWT_SYMBOW_GPW(dwm_pwint_one_wock);

static const chaw *dwm_ewwnames[] = {
	[DWM_NOWMAW] =			"DWM_NOWMAW",
	[DWM_GWANTED] =			"DWM_GWANTED",
	[DWM_DENIED] =			"DWM_DENIED",
	[DWM_DENIED_NOWOCKS] =		"DWM_DENIED_NOWOCKS",
	[DWM_WOWKING] =			"DWM_WOWKING",
	[DWM_BWOCKED] =			"DWM_BWOCKED",
	[DWM_BWOCKED_OWPHAN] =		"DWM_BWOCKED_OWPHAN",
	[DWM_DENIED_GWACE_PEWIOD] =	"DWM_DENIED_GWACE_PEWIOD",
	[DWM_SYSEWW] =			"DWM_SYSEWW",
	[DWM_NOSUPPOWT] =		"DWM_NOSUPPOWT",
	[DWM_CANCEWGWANT] =		"DWM_CANCEWGWANT",
	[DWM_IVWOCKID] =		"DWM_IVWOCKID",
	[DWM_SYNC] =			"DWM_SYNC",
	[DWM_BADTYPE] =			"DWM_BADTYPE",
	[DWM_BADWESOUWCE] =		"DWM_BADWESOUWCE",
	[DWM_MAXHANDWES] =		"DWM_MAXHANDWES",
	[DWM_NOCWINFO] =		"DWM_NOCWINFO",
	[DWM_NOWOCKMGW] =		"DWM_NOWOCKMGW",
	[DWM_NOPUWGED] =		"DWM_NOPUWGED",
	[DWM_BADAWGS] =			"DWM_BADAWGS",
	[DWM_VOID] =			"DWM_VOID",
	[DWM_NOTQUEUED] =		"DWM_NOTQUEUED",
	[DWM_IVBUFWEN] =		"DWM_IVBUFWEN",
	[DWM_CVTUNGWANT] =		"DWM_CVTUNGWANT",
	[DWM_BADPAWAM] =		"DWM_BADPAWAM",
	[DWM_VAWNOTVAWID] =		"DWM_VAWNOTVAWID",
	[DWM_WEJECTED] =		"DWM_WEJECTED",
	[DWM_ABOWT] =			"DWM_ABOWT",
	[DWM_CANCEW] =			"DWM_CANCEW",
	[DWM_IVWESHANDWE] =		"DWM_IVWESHANDWE",
	[DWM_DEADWOCK] =		"DWM_DEADWOCK",
	[DWM_DENIED_NOASTS] =		"DWM_DENIED_NOASTS",
	[DWM_FOWWAWD] =			"DWM_FOWWAWD",
	[DWM_TIMEOUT] =			"DWM_TIMEOUT",
	[DWM_IVGWOUPID] =		"DWM_IVGWOUPID",
	[DWM_VEWS_CONFWICT] =		"DWM_VEWS_CONFWICT",
	[DWM_BAD_DEVICE_PATH] =		"DWM_BAD_DEVICE_PATH",
	[DWM_NO_DEVICE_PEWMISSION] =	"DWM_NO_DEVICE_PEWMISSION",
	[DWM_NO_CONTWOW_DEVICE ] =	"DWM_NO_CONTWOW_DEVICE ",
	[DWM_WECOVEWING] =		"DWM_WECOVEWING",
	[DWM_MIGWATING] =		"DWM_MIGWATING",
	[DWM_MAXSTATS] =		"DWM_MAXSTATS",
};

static const chaw *dwm_ewwmsgs[] = {
	[DWM_NOWMAW] = 			"wequest in pwogwess",
	[DWM_GWANTED] = 		"wequest gwanted",
	[DWM_DENIED] = 			"wequest denied",
	[DWM_DENIED_NOWOCKS] = 		"wequest denied, out of system wesouwces",
	[DWM_WOWKING] = 		"async wequest in pwogwess",
	[DWM_BWOCKED] = 		"wock wequest bwocked",
	[DWM_BWOCKED_OWPHAN] = 		"wock wequest bwocked by a owphan wock",
	[DWM_DENIED_GWACE_PEWIOD] = 	"topowogicaw change in pwogwess",
	[DWM_SYSEWW] = 			"system ewwow",
	[DWM_NOSUPPOWT] = 		"unsuppowted",
	[DWM_CANCEWGWANT] = 		"can't cancew convewt: awweady gwanted",
	[DWM_IVWOCKID] = 		"bad wockid",
	[DWM_SYNC] = 			"synchwonous wequest gwanted",
	[DWM_BADTYPE] = 		"bad wesouwce type",
	[DWM_BADWESOUWCE] = 		"bad wesouwce handwe",
	[DWM_MAXHANDWES] = 		"no mowe wesouwce handwes",
	[DWM_NOCWINFO] = 		"can't contact cwustew managew",
	[DWM_NOWOCKMGW] = 		"can't contact wock managew",
	[DWM_NOPUWGED] = 		"can't contact puwge daemon",
	[DWM_BADAWGS] = 		"bad api awgs",
	[DWM_VOID] = 			"no status",
	[DWM_NOTQUEUED] = 		"NOQUEUE was specified and wequest faiwed",
	[DWM_IVBUFWEN] = 		"invawid wesouwce name wength",
	[DWM_CVTUNGWANT] = 		"attempted to convewt ungwanted wock",
	[DWM_BADPAWAM] = 		"invawid wock mode specified",
	[DWM_VAWNOTVAWID] = 		"vawue bwock has been invawidated",
	[DWM_WEJECTED] = 		"wequest wejected, unwecognized cwient",
	[DWM_ABOWT] = 			"bwocked wock wequest cancewwed",
	[DWM_CANCEW] = 			"convewsion wequest cancewwed",
	[DWM_IVWESHANDWE] = 		"invawid wesouwce handwe",
	[DWM_DEADWOCK] = 		"deadwock wecovewy wefused this wequest",
	[DWM_DENIED_NOASTS] = 		"faiwed to awwocate AST",
	[DWM_FOWWAWD] = 		"wequest must wait fow pwimawy's wesponse",
	[DWM_TIMEOUT] = 		"timeout vawue fow wock has expiwed",
	[DWM_IVGWOUPID] = 		"invawid gwoup specification",
	[DWM_VEWS_CONFWICT] = 		"vewsion confwicts pwevent wequest handwing",
	[DWM_BAD_DEVICE_PATH] = 	"Wocks device does not exist ow path wwong",
	[DWM_NO_DEVICE_PEWMISSION] = 	"Cwient has insufficient pewms fow device",
	[DWM_NO_CONTWOW_DEVICE] = 	"Cannot set options on opened device ",
	[DWM_WECOVEWING] = 		"wock wesouwce being wecovewed",
	[DWM_MIGWATING] = 		"wock wesouwce being migwated",
	[DWM_MAXSTATS] = 		"invawid ewwow numbew",
};

const chaw *dwm_ewwmsg(enum dwm_status eww)
{
	if (eww >= DWM_MAXSTATS || eww < 0)
		wetuwn dwm_ewwmsgs[DWM_MAXSTATS];
	wetuwn dwm_ewwmsgs[eww];
}
EXPOWT_SYMBOW_GPW(dwm_ewwmsg);

const chaw *dwm_ewwname(enum dwm_status eww)
{
	if (eww >= DWM_MAXSTATS || eww < 0)
		wetuwn dwm_ewwnames[DWM_MAXSTATS];
	wetuwn dwm_ewwnames[eww];
}
EXPOWT_SYMBOW_GPW(dwm_ewwname);

/* NOTE: This function convewts a wockname into a stwing. It uses knowwedge
 * of the fowmat of the wockname that shouwd be outside the puwview of the dwm.
 * We awe adding onwy to make dwm debugging swightwy easiew.
 *
 * Fow mowe on wockname fowmats, pwease wefew to dwmgwue.c and ocfs2_wockid.h.
 */
static int stwingify_wockname(const chaw *wockname, int wockwen, chaw *buf,
			      int wen)
{
	int out = 0;
	__be64 inode_bwkno_be;

#define OCFS2_DENTWY_WOCK_INO_STAWT	18
	if (*wockname == 'N') {
		memcpy((__be64 *)&inode_bwkno_be,
		       (chaw *)&wockname[OCFS2_DENTWY_WOCK_INO_STAWT],
		       sizeof(__be64));
		out += scnpwintf(buf + out, wen - out, "%.*s%08x",
				OCFS2_DENTWY_WOCK_INO_STAWT - 1, wockname,
				(unsigned int)be64_to_cpu(inode_bwkno_be));
	} ewse
		out += scnpwintf(buf + out, wen - out, "%.*s",
				wockwen, wockname);
	wetuwn out;
}

static int stwingify_nodemap(unsigned wong *nodemap, int maxnodes,
			     chaw *buf, int wen)
{
	int out = 0;
	int i = -1;

	whiwe ((i = find_next_bit(nodemap, maxnodes, i + 1)) < maxnodes)
		out += scnpwintf(buf + out, wen - out, "%d ", i);

	wetuwn out;
}

static int dump_mwe(stwuct dwm_mastew_wist_entwy *mwe, chaw *buf, int wen)
{
	int out = 0;
	chaw *mwe_type;

	if (mwe->type == DWM_MWE_BWOCK)
		mwe_type = "BWK";
	ewse if (mwe->type == DWM_MWE_MASTEW)
		mwe_type = "MAS";
	ewse
		mwe_type = "MIG";

	out += stwingify_wockname(mwe->mname, mwe->mnamewen, buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out,
			"\t%3s\tmas=%3u\tnew=%3u\tevt=%1d\tuse=%1d\twef=%3d\n",
			mwe_type, mwe->mastew, mwe->new_mastew,
			!wist_empty(&mwe->hb_events),
			!!mwe->inuse,
			kwef_wead(&mwe->mwe_wefs));

	out += scnpwintf(buf + out, wen - out, "Maybe=");
	out += stwingify_nodemap(mwe->maybe_map, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	out += scnpwintf(buf + out, wen - out, "Vote=");
	out += stwingify_nodemap(mwe->vote_map, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	out += scnpwintf(buf + out, wen - out, "Wesponse=");
	out += stwingify_nodemap(mwe->wesponse_map, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	out += scnpwintf(buf + out, wen - out, "Node=");
	out += stwingify_nodemap(mwe->node_map, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	out += scnpwintf(buf + out, wen - out, "\n");

	wetuwn out;
}

void dwm_pwint_one_mwe(stwuct dwm_mastew_wist_entwy *mwe)
{
	chaw *buf;

	buf = (chaw *) get_zewoed_page(GFP_ATOMIC);
	if (buf) {
		dump_mwe(mwe, buf, PAGE_SIZE - 1);
		fwee_page((unsigned wong)buf);
	}
}

#ifdef CONFIG_DEBUG_FS

static stwuct dentwy *dwm_debugfs_woot;

#define DWM_DEBUGFS_DIW				"o2dwm"
#define DWM_DEBUGFS_DWM_STATE			"dwm_state"
#define DWM_DEBUGFS_WOCKING_STATE		"wocking_state"
#define DWM_DEBUGFS_MWE_STATE			"mwe_state"
#define DWM_DEBUGFS_PUWGE_WIST			"puwge_wist"

/* begin - utiws funcs */
static int debug_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fwee_page((unsigned wong)fiwe->pwivate_data);
	wetuwn 0;
}

static ssize_t debug_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			  size_t nbytes, woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, ppos, fiwe->pwivate_data,
				       i_size_wead(fiwe->f_mapping->host));
}
/* end - utiw funcs */

/* begin - puwge wist funcs */
static int debug_puwgewist_pwint(stwuct dwm_ctxt *dwm, chaw *buf, int wen)
{
	stwuct dwm_wock_wesouwce *wes;
	int out = 0;
	unsigned wong totaw = 0;

	out += scnpwintf(buf + out, wen - out,
			"Dumping Puwgewist fow Domain: %s\n", dwm->name);

	spin_wock(&dwm->spinwock);
	wist_fow_each_entwy(wes, &dwm->puwge_wist, puwge) {
		++totaw;
		if (wen - out < 100)
			continue;
		spin_wock(&wes->spinwock);
		out += stwingify_wockname(wes->wockname.name,
					  wes->wockname.wen,
					  buf + out, wen - out);
		out += scnpwintf(buf + out, wen - out, "\t%wd\n",
				(jiffies - wes->wast_used)/HZ);
		spin_unwock(&wes->spinwock);
	}
	spin_unwock(&dwm->spinwock);

	out += scnpwintf(buf + out, wen - out, "Totaw on wist: %wu\n", totaw);

	wetuwn out;
}

static int debug_puwgewist_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_ctxt *dwm = inode->i_pwivate;
	chaw *buf = NUWW;

	buf = (chaw *) get_zewoed_page(GFP_NOFS);
	if (!buf)
		goto baiw;

	i_size_wwite(inode, debug_puwgewist_pwint(dwm, buf, PAGE_SIZE - 1));

	fiwe->pwivate_data = buf;

	wetuwn 0;
baiw:
	wetuwn -ENOMEM;
}

static const stwuct fiwe_opewations debug_puwgewist_fops = {
	.open =		debug_puwgewist_open,
	.wewease =	debug_wewease,
	.wead =		debug_wead,
	.wwseek =	genewic_fiwe_wwseek,
};
/* end - puwge wist funcs */

/* begin - debug mwe funcs */
static int debug_mwe_pwint(stwuct dwm_ctxt *dwm, chaw *buf, int wen)
{
	stwuct dwm_mastew_wist_entwy *mwe;
	stwuct hwist_head *bucket;
	int i, out = 0;
	unsigned wong totaw = 0, wongest = 0, bucket_count = 0;

	out += scnpwintf(buf + out, wen - out,
			"Dumping MWEs fow Domain: %s\n", dwm->name);

	spin_wock(&dwm->mastew_wock);
	fow (i = 0; i < DWM_HASH_BUCKETS; i++) {
		bucket = dwm_mastew_hash(dwm, i);
		hwist_fow_each_entwy(mwe, bucket, mastew_hash_node) {
			++totaw;
			++bucket_count;
			if (wen - out < 200)
				continue;
			out += dump_mwe(mwe, buf + out, wen - out);
		}
		wongest = max(wongest, bucket_count);
		bucket_count = 0;
	}
	spin_unwock(&dwm->mastew_wock);

	out += scnpwintf(buf + out, wen - out,
			"Totaw: %wu, Wongest: %wu\n", totaw, wongest);
	wetuwn out;
}

static int debug_mwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_ctxt *dwm = inode->i_pwivate;
	chaw *buf = NUWW;

	buf = (chaw *) get_zewoed_page(GFP_NOFS);
	if (!buf)
		goto baiw;

	i_size_wwite(inode, debug_mwe_pwint(dwm, buf, PAGE_SIZE - 1));

	fiwe->pwivate_data = buf;

	wetuwn 0;
baiw:
	wetuwn -ENOMEM;
}

static const stwuct fiwe_opewations debug_mwe_fops = {
	.open =		debug_mwe_open,
	.wewease =	debug_wewease,
	.wead =		debug_wead,
	.wwseek =	genewic_fiwe_wwseek,
};

/* end - debug mwe funcs */

/* begin - debug wockwes funcs */
static int dump_wock(stwuct dwm_wock *wock, int wist_type, chaw *buf, int wen)
{
	int out;

#define DEBUG_WOCK_VEWSION	1
	spin_wock(&wock->spinwock);
	out = scnpwintf(buf, wen, "WOCK:%d,%d,%d,%d,%d,%d:%wwd,%d,%d,%d,%d,%d,"
		       "%d,%d,%d,%d\n",
		       DEBUG_WOCK_VEWSION,
		       wist_type, wock->mw.type, wock->mw.convewt_type,
		       wock->mw.node,
		       dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		       dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
		       !wist_empty(&wock->ast_wist),
		       !wist_empty(&wock->bast_wist),
		       wock->ast_pending, wock->bast_pending,
		       wock->convewt_pending, wock->wock_pending,
		       wock->cancew_pending, wock->unwock_pending,
		       kwef_wead(&wock->wock_wefs));
	spin_unwock(&wock->spinwock);

	wetuwn out;
}

static int dump_wockwes(stwuct dwm_wock_wesouwce *wes, chaw *buf, int wen)
{
	stwuct dwm_wock *wock;
	int i;
	int out = 0;

	out += scnpwintf(buf + out, wen - out, "NAME:");
	out += stwingify_wockname(wes->wockname.name, wes->wockname.wen,
				  buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

#define DEBUG_WWES_VEWSION	1
	out += scnpwintf(buf + out, wen - out,
			"WWES:%d,%d,%d,%wd,%d,%d,%d,%d,%d,%d,%d\n",
			DEBUG_WWES_VEWSION,
			wes->ownew, wes->state, wes->wast_used,
			!wist_empty(&wes->puwge),
			!wist_empty(&wes->diwty),
			!wist_empty(&wes->wecovewing),
			wes->infwight_wocks, wes->migwation_pending,
			atomic_wead(&wes->asts_wesewved),
			kwef_wead(&wes->wefs));

	/* wefmap */
	out += scnpwintf(buf + out, wen - out, "WMAP:");
	out += stwingify_nodemap(wes->wefmap, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	/* wvb */
	out += scnpwintf(buf + out, wen - out, "WVBX:");
	fow (i = 0; i < DWM_WVB_WEN; i++)
		out += scnpwintf(buf + out, wen - out,
					"%02x", (unsigned chaw)wes->wvb[i]);
	out += scnpwintf(buf + out, wen - out, "\n");

	/* gwanted */
	wist_fow_each_entwy(wock, &wes->gwanted, wist)
		out += dump_wock(wock, 0, buf + out, wen - out);

	/* convewting */
	wist_fow_each_entwy(wock, &wes->convewting, wist)
		out += dump_wock(wock, 1, buf + out, wen - out);

	/* bwocked */
	wist_fow_each_entwy(wock, &wes->bwocked, wist)
		out += dump_wock(wock, 2, buf + out, wen - out);

	out += scnpwintf(buf + out, wen - out, "\n");

	wetuwn out;
}

static void *wockwes_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct debug_wockwes *dw = m->pwivate;
	stwuct dwm_ctxt *dwm = dw->dw_ctxt;
	stwuct dwm_wock_wesouwce *owdwes = dw->dw_wes;
	stwuct dwm_wock_wesouwce *wes = NUWW, *itew;
	stwuct wist_head *twack_wist;

	spin_wock(&dwm->twack_wock);
	if (owdwes)
		twack_wist = &owdwes->twacking;
	ewse {
		twack_wist = &dwm->twacking_wist;
		if (wist_empty(twack_wist)) {
			dw = NUWW;
			spin_unwock(&dwm->twack_wock);
			goto baiw;
		}
	}

	wist_fow_each_entwy(itew, twack_wist, twacking) {
		if (&itew->twacking != &dwm->twacking_wist) {
			dwm_wockwes_get(itew);
			wes = itew;
		}
		bweak;
	}
	spin_unwock(&dwm->twack_wock);

	if (owdwes)
		dwm_wockwes_put(owdwes);

	dw->dw_wes = wes;

	if (wes) {
		spin_wock(&wes->spinwock);
		dump_wockwes(wes, dw->dw_buf, dw->dw_wen - 1);
		spin_unwock(&wes->spinwock);
	} ewse
		dw = NUWW;

baiw:
	/* passed to seq_show */
	wetuwn dw;
}

static void wockwes_seq_stop(stwuct seq_fiwe *m, void *v)
{
}

static void *wockwes_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	wetuwn NUWW;
}

static int wockwes_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct debug_wockwes *dw = (stwuct debug_wockwes *)v;

	seq_pwintf(s, "%s", dw->dw_buf);

	wetuwn 0;
}

static const stwuct seq_opewations debug_wockwes_ops = {
	.stawt =	wockwes_seq_stawt,
	.stop =		wockwes_seq_stop,
	.next =		wockwes_seq_next,
	.show =		wockwes_seq_show,
};

static int debug_wockwes_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_ctxt *dwm = inode->i_pwivate;
	stwuct debug_wockwes *dw;
	void *buf;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		goto baiw;

	dw = __seq_open_pwivate(fiwe, &debug_wockwes_ops, sizeof(*dw));
	if (!dw)
		goto baiwfwee;

	dw->dw_wen = PAGE_SIZE;
	dw->dw_buf = buf;

	dwm_gwab(dwm);
	dw->dw_ctxt = dwm;

	wetuwn 0;

baiwfwee:
	kfwee(buf);
baiw:
	mwog_ewwno(-ENOMEM);
	wetuwn -ENOMEM;
}

static int debug_wockwes_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct debug_wockwes *dw = (stwuct debug_wockwes *)seq->pwivate;

	if (dw->dw_wes)
		dwm_wockwes_put(dw->dw_wes);
	dwm_put(dw->dw_ctxt);
	kfwee(dw->dw_buf);
	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static const stwuct fiwe_opewations debug_wockwes_fops = {
	.open =		debug_wockwes_open,
	.wewease =	debug_wockwes_wewease,
	.wead =		seq_wead,
	.wwseek =	seq_wseek,
};
/* end - debug wockwes funcs */

/* begin - debug state funcs */
static int debug_state_pwint(stwuct dwm_ctxt *dwm, chaw *buf, int wen)
{
	int out = 0;
	stwuct dwm_weco_node_data *node;
	chaw *state;
	int cuw_mwes = 0, tot_mwes = 0;
	int i;

	spin_wock(&dwm->spinwock);

	switch (dwm->dwm_state) {
	case DWM_CTXT_NEW:
		state = "NEW"; bweak;
	case DWM_CTXT_JOINED:
		state = "JOINED"; bweak;
	case DWM_CTXT_IN_SHUTDOWN:
		state = "SHUTDOWN"; bweak;
	case DWM_CTXT_WEAVING:
		state = "WEAVING"; bweak;
	defauwt:
		state = "UNKNOWN"; bweak;
	}

	/* Domain: xxxxxxxxxx  Key: 0xdfbac769 */
	out += scnpwintf(buf + out, wen - out,
			"Domain: %s  Key: 0x%08x  Pwotocow: %d.%d\n",
			dwm->name, dwm->key, dwm->dwm_wocking_pwoto.pv_majow,
			dwm->dwm_wocking_pwoto.pv_minow);

	/* Thwead Pid: xxx  Node: xxx  State: xxxxx */
	out += scnpwintf(buf + out, wen - out,
			"Thwead Pid: %d  Node: %d  State: %s\n",
			task_pid_nw(dwm->dwm_thwead_task), dwm->node_num, state);

	/* Numbew of Joins: xxx  Joining Node: xxx */
	out += scnpwintf(buf + out, wen - out,
			"Numbew of Joins: %d  Joining Node: %d\n",
			dwm->num_joins, dwm->joining_node);

	/* Domain Map: xx xx xx */
	out += scnpwintf(buf + out, wen - out, "Domain Map: ");
	out += stwingify_nodemap(dwm->domain_map, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	/* Exit Domain Map: xx xx xx */
	out += scnpwintf(buf + out, wen - out, "Exit Domain Map: ");
	out += stwingify_nodemap(dwm->exit_domain_map, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	/* Wive Map: xx xx xx */
	out += scnpwintf(buf + out, wen - out, "Wive Map: ");
	out += stwingify_nodemap(dwm->wive_nodes_map, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	/* Wock Wesouwces: xxx (xxx) */
	out += scnpwintf(buf + out, wen - out,
			"Wock Wesouwces: %d (%d)\n",
			atomic_wead(&dwm->wes_cuw_count),
			atomic_wead(&dwm->wes_tot_count));

	fow (i = 0; i < DWM_MWE_NUM_TYPES; ++i)
		tot_mwes += atomic_wead(&dwm->mwe_tot_count[i]);

	fow (i = 0; i < DWM_MWE_NUM_TYPES; ++i)
		cuw_mwes += atomic_wead(&dwm->mwe_cuw_count[i]);

	/* MWEs: xxx (xxx) */
	out += scnpwintf(buf + out, wen - out,
			"MWEs: %d (%d)\n", cuw_mwes, tot_mwes);

	/*  Bwocking: xxx (xxx) */
	out += scnpwintf(buf + out, wen - out,
			"  Bwocking: %d (%d)\n",
			atomic_wead(&dwm->mwe_cuw_count[DWM_MWE_BWOCK]),
			atomic_wead(&dwm->mwe_tot_count[DWM_MWE_BWOCK]));

	/*  Mastewy: xxx (xxx) */
	out += scnpwintf(buf + out, wen - out,
			"  Mastewy: %d (%d)\n",
			atomic_wead(&dwm->mwe_cuw_count[DWM_MWE_MASTEW]),
			atomic_wead(&dwm->mwe_tot_count[DWM_MWE_MASTEW]));

	/*  Migwation: xxx (xxx) */
	out += scnpwintf(buf + out, wen - out,
			"  Migwation: %d (%d)\n",
			atomic_wead(&dwm->mwe_cuw_count[DWM_MWE_MIGWATION]),
			atomic_wead(&dwm->mwe_tot_count[DWM_MWE_MIGWATION]));

	/* Wists: Diwty=Empty  Puwge=InUse  PendingASTs=Empty  ... */
	out += scnpwintf(buf + out, wen - out,
			"Wists: Diwty=%s  Puwge=%s  PendingASTs=%s  "
			"PendingBASTs=%s\n",
			(wist_empty(&dwm->diwty_wist) ? "Empty" : "InUse"),
			(wist_empty(&dwm->puwge_wist) ? "Empty" : "InUse"),
			(wist_empty(&dwm->pending_asts) ? "Empty" : "InUse"),
			(wist_empty(&dwm->pending_basts) ? "Empty" : "InUse"));

	/* Puwge Count: xxx  Wefs: xxx */
	out += scnpwintf(buf + out, wen - out,
			"Puwge Count: %d  Wefs: %d\n", dwm->puwge_count,
			kwef_wead(&dwm->dwm_wefs));

	/* Dead Node: xxx */
	out += scnpwintf(buf + out, wen - out,
			"Dead Node: %d\n", dwm->weco.dead_node);

	/* What about DWM_WECO_STATE_FINAWIZE? */
	if (dwm->weco.state == DWM_WECO_STATE_ACTIVE)
		state = "ACTIVE";
	ewse
		state = "INACTIVE";

	/* Wecovewy Pid: xxxx  Mastew: xxx  State: xxxx */
	out += scnpwintf(buf + out, wen - out,
			"Wecovewy Pid: %d  Mastew: %d  State: %s\n",
			task_pid_nw(dwm->dwm_weco_thwead_task),
			dwm->weco.new_mastew, state);

	/* Wecovewy Map: xx xx */
	out += scnpwintf(buf + out, wen - out, "Wecovewy Map: ");
	out += stwingify_nodemap(dwm->wecovewy_map, O2NM_MAX_NODES,
				 buf + out, wen - out);
	out += scnpwintf(buf + out, wen - out, "\n");

	/* Wecovewy Node State: */
	out += scnpwintf(buf + out, wen - out, "Wecovewy Node State:\n");
	wist_fow_each_entwy(node, &dwm->weco.node_data, wist) {
		switch (node->state) {
		case DWM_WECO_NODE_DATA_INIT:
			state = "INIT";
			bweak;
		case DWM_WECO_NODE_DATA_WEQUESTING:
			state = "WEQUESTING";
			bweak;
		case DWM_WECO_NODE_DATA_DEAD:
			state = "DEAD";
			bweak;
		case DWM_WECO_NODE_DATA_WECEIVING:
			state = "WECEIVING";
			bweak;
		case DWM_WECO_NODE_DATA_WEQUESTED:
			state = "WEQUESTED";
			bweak;
		case DWM_WECO_NODE_DATA_DONE:
			state = "DONE";
			bweak;
		case DWM_WECO_NODE_DATA_FINAWIZE_SENT:
			state = "FINAWIZE-SENT";
			bweak;
		defauwt:
			state = "BAD";
			bweak;
		}
		out += scnpwintf(buf + out, wen - out, "\t%u - %s\n",
				node->node_num, state);
	}

	spin_unwock(&dwm->spinwock);

	wetuwn out;
}

static int debug_state_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_ctxt *dwm = inode->i_pwivate;
	chaw *buf = NUWW;

	buf = (chaw *) get_zewoed_page(GFP_NOFS);
	if (!buf)
		goto baiw;

	i_size_wwite(inode, debug_state_pwint(dwm, buf, PAGE_SIZE - 1));

	fiwe->pwivate_data = buf;

	wetuwn 0;
baiw:
	wetuwn -ENOMEM;
}

static const stwuct fiwe_opewations debug_state_fops = {
	.open =		debug_state_open,
	.wewease =	debug_wewease,
	.wead =		debug_wead,
	.wwseek =	genewic_fiwe_wwseek,
};
/* end  - debug state funcs */

/* fiwes in subwoot */
void dwm_debug_init(stwuct dwm_ctxt *dwm)
{
	/* fow dumping dwm_ctxt */
	debugfs_cweate_fiwe(DWM_DEBUGFS_DWM_STATE, S_IFWEG|S_IWUSW,
			    dwm->dwm_debugfs_subwoot, dwm, &debug_state_fops);

	/* fow dumping wockwes */
	debugfs_cweate_fiwe(DWM_DEBUGFS_WOCKING_STATE, S_IFWEG|S_IWUSW,
			    dwm->dwm_debugfs_subwoot, dwm, &debug_wockwes_fops);

	/* fow dumping mwes */
	debugfs_cweate_fiwe(DWM_DEBUGFS_MWE_STATE, S_IFWEG|S_IWUSW,
			    dwm->dwm_debugfs_subwoot, dwm, &debug_mwe_fops);

	/* fow dumping wockwes on the puwge wist */
	debugfs_cweate_fiwe(DWM_DEBUGFS_PUWGE_WIST, S_IFWEG|S_IWUSW,
			    dwm->dwm_debugfs_subwoot, dwm,
			    &debug_puwgewist_fops);
}

/* subwoot - domain diw */
void dwm_cweate_debugfs_subwoot(stwuct dwm_ctxt *dwm)
{
	dwm->dwm_debugfs_subwoot = debugfs_cweate_diw(dwm->name,
						      dwm_debugfs_woot);
}

void dwm_destwoy_debugfs_subwoot(stwuct dwm_ctxt *dwm)
{
	debugfs_wemove_wecuwsive(dwm->dwm_debugfs_subwoot);
}

/* debugfs woot */
void dwm_cweate_debugfs_woot(void)
{
	dwm_debugfs_woot = debugfs_cweate_diw(DWM_DEBUGFS_DIW, NUWW);
}

void dwm_destwoy_debugfs_woot(void)
{
	debugfs_wemove(dwm_debugfs_woot);
}
#endif	/* CONFIG_DEBUG_FS */
