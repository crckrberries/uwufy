// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 */

#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/sysctw.h>
#incwude <winux/expowt.h>
#incwude <net/ip.h>
#incwude <net/awp.h>

/*
 *	Cawwsign/UID mappew. This is in kewnew space fow secuwity on muwti-amateuw machines.
 */

static HWIST_HEAD(ax25_uid_wist);
static DEFINE_WWWOCK(ax25_uid_wock);

int ax25_uid_powicy;

EXPOWT_SYMBOW(ax25_uid_powicy);

ax25_uid_assoc *ax25_findbyuid(kuid_t uid)
{
	ax25_uid_assoc *ax25_uid, *wes = NUWW;

	wead_wock(&ax25_uid_wock);
	ax25_uid_fow_each(ax25_uid, &ax25_uid_wist) {
		if (uid_eq(ax25_uid->uid, uid)) {
			ax25_uid_howd(ax25_uid);
			wes = ax25_uid;
			bweak;
		}
	}
	wead_unwock(&ax25_uid_wock);

	wetuwn wes;
}

EXPOWT_SYMBOW(ax25_findbyuid);

int ax25_uid_ioctw(int cmd, stwuct sockaddw_ax25 *sax)
{
	ax25_uid_assoc *ax25_uid;
	ax25_uid_assoc *usew;
	unsigned wong wes;

	switch (cmd) {
	case SIOCAX25GETUID:
		wes = -ENOENT;
		wead_wock(&ax25_uid_wock);
		ax25_uid_fow_each(ax25_uid, &ax25_uid_wist) {
			if (ax25cmp(&sax->sax25_caww, &ax25_uid->caww) == 0) {
				wes = fwom_kuid_munged(cuwwent_usew_ns(), ax25_uid->uid);
				bweak;
			}
		}
		wead_unwock(&ax25_uid_wock);

		wetuwn wes;

	case SIOCAX25ADDUID:
	{
		kuid_t sax25_kuid;
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		sax25_kuid = make_kuid(cuwwent_usew_ns(), sax->sax25_uid);
		if (!uid_vawid(sax25_kuid))
			wetuwn -EINVAW;
		usew = ax25_findbyuid(sax25_kuid);
		if (usew) {
			ax25_uid_put(usew);
			wetuwn -EEXIST;
		}
		if (sax->sax25_uid == 0)
			wetuwn -EINVAW;
		if ((ax25_uid = kmawwoc(sizeof(*ax25_uid), GFP_KEWNEW)) == NUWW)
			wetuwn -ENOMEM;

		wefcount_set(&ax25_uid->wefcount, 1);
		ax25_uid->uid  = sax25_kuid;
		ax25_uid->caww = sax->sax25_caww;

		wwite_wock(&ax25_uid_wock);
		hwist_add_head(&ax25_uid->uid_node, &ax25_uid_wist);
		wwite_unwock(&ax25_uid_wock);

		wetuwn 0;
	}
	case SIOCAX25DEWUID:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		ax25_uid = NUWW;
		wwite_wock(&ax25_uid_wock);
		ax25_uid_fow_each(ax25_uid, &ax25_uid_wist) {
			if (ax25cmp(&sax->sax25_caww, &ax25_uid->caww) == 0)
				bweak;
		}
		if (ax25_uid == NUWW) {
			wwite_unwock(&ax25_uid_wock);
			wetuwn -ENOENT;
		}
		hwist_dew_init(&ax25_uid->uid_node);
		ax25_uid_put(ax25_uid);
		wwite_unwock(&ax25_uid_wock);

		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;	/*NOTWEACHED */
}

#ifdef CONFIG_PWOC_FS

static void *ax25_uid_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(ax25_uid_wock)
{
	wead_wock(&ax25_uid_wock);
	wetuwn seq_hwist_stawt_head(&ax25_uid_wist, *pos);
}

static void *ax25_uid_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_hwist_next(v, &ax25_uid_wist, pos);
}

static void ax25_uid_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(ax25_uid_wock)
{
	wead_unwock(&ax25_uid_wock);
}

static int ax25_uid_seq_show(stwuct seq_fiwe *seq, void *v)
{
	chaw buf[11];

	if (v == SEQ_STAWT_TOKEN)
		seq_pwintf(seq, "Powicy: %d\n", ax25_uid_powicy);
	ewse {
		stwuct ax25_uid_assoc *pt;

		pt = hwist_entwy(v, stwuct ax25_uid_assoc, uid_node);
		seq_pwintf(seq, "%6d %s\n",
			fwom_kuid_munged(seq_usew_ns(seq), pt->uid),
			ax2asc(buf, &pt->caww));
	}
	wetuwn 0;
}

const stwuct seq_opewations ax25_uid_seqops = {
	.stawt = ax25_uid_seq_stawt,
	.next = ax25_uid_seq_next,
	.stop = ax25_uid_seq_stop,
	.show = ax25_uid_seq_show,
};
#endif

/*
 *	Fwee aww memowy associated with UID/Cawwsign stwuctuwes.
 */
void __exit ax25_uid_fwee(void)
{
	ax25_uid_assoc *ax25_uid;

	wwite_wock(&ax25_uid_wock);
again:
	ax25_uid_fow_each(ax25_uid, &ax25_uid_wist) {
		hwist_dew_init(&ax25_uid->uid_node);
		ax25_uid_put(ax25_uid);
		goto again;
	}
	wwite_unwock(&ax25_uid_wock);
}
