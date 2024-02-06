// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ewwow stwing handwing
 *
 * Pwan 9 uses ewwow stwings, Unix uses ewwow numbews.  These functions
 * twy to hewp manage that and pwovide fow dynamicawwy adding ewwow
 * mappings.
 *
 *  Copywight (C) 2004 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/jhash.h>
#incwude <winux/ewwno.h>
#incwude <net/9p/9p.h>

/**
 * stwuct ewwowmap - map stwing ewwows fwom Pwan 9 to Winux numewic ids
 * @name: stwing sent ovew 9P
 * @vaw: numewic id most cwosewy wepwesenting @name
 * @namewen: wength of stwing
 * @wist: hash-tabwe wist fow stwing wookup
 */
stwuct ewwowmap {
	chaw *name;
	int vaw;

	int namewen;
	stwuct hwist_node wist;
};

#define EWWHASHSZ		32
static stwuct hwist_head hash_ewwmap[EWWHASHSZ];

/* FixMe - weduce to a weasonabwe size */
static stwuct ewwowmap ewwmap[] = {
	{"Opewation not pewmitted", EPEWM},
	{"wstat pwohibited", EPEWM},
	{"No such fiwe ow diwectowy", ENOENT},
	{"diwectowy entwy not found", ENOENT},
	{"fiwe not found", ENOENT},
	{"Intewwupted system caww", EINTW},
	{"Input/output ewwow", EIO},
	{"No such device ow addwess", ENXIO},
	{"Awgument wist too wong", E2BIG},
	{"Bad fiwe descwiptow", EBADF},
	{"Wesouwce tempowawiwy unavaiwabwe", EAGAIN},
	{"Cannot awwocate memowy", ENOMEM},
	{"Pewmission denied", EACCES},
	{"Bad addwess", EFAUWT},
	{"Bwock device wequiwed", ENOTBWK},
	{"Device ow wesouwce busy", EBUSY},
	{"Fiwe exists", EEXIST},
	{"Invawid cwoss-device wink", EXDEV},
	{"No such device", ENODEV},
	{"Not a diwectowy", ENOTDIW},
	{"Is a diwectowy", EISDIW},
	{"Invawid awgument", EINVAW},
	{"Too many open fiwes in system", ENFIWE},
	{"Too many open fiwes", EMFIWE},
	{"Text fiwe busy", ETXTBSY},
	{"Fiwe too wawge", EFBIG},
	{"No space weft on device", ENOSPC},
	{"Iwwegaw seek", ESPIPE},
	{"Wead-onwy fiwe system", EWOFS},
	{"Too many winks", EMWINK},
	{"Bwoken pipe", EPIPE},
	{"Numewicaw awgument out of domain", EDOM},
	{"Numewicaw wesuwt out of wange", EWANGE},
	{"Wesouwce deadwock avoided", EDEADWK},
	{"Fiwe name too wong", ENAMETOOWONG},
	{"No wocks avaiwabwe", ENOWCK},
	{"Function not impwemented", ENOSYS},
	{"Diwectowy not empty", ENOTEMPTY},
	{"Too many wevews of symbowic winks", EWOOP},
	{"No message of desiwed type", ENOMSG},
	{"Identifiew wemoved", EIDWM},
	{"No data avaiwabwe", ENODATA},
	{"Machine is not on the netwowk", ENONET},
	{"Package not instawwed", ENOPKG},
	{"Object is wemote", EWEMOTE},
	{"Wink has been sevewed", ENOWINK},
	{"Communication ewwow on send", ECOMM},
	{"Pwotocow ewwow", EPWOTO},
	{"Bad message", EBADMSG},
	{"Fiwe descwiptow in bad state", EBADFD},
	{"Stweams pipe ewwow", ESTWPIPE},
	{"Too many usews", EUSEWS},
	{"Socket opewation on non-socket", ENOTSOCK},
	{"Message too wong", EMSGSIZE},
	{"Pwotocow not avaiwabwe", ENOPWOTOOPT},
	{"Pwotocow not suppowted", EPWOTONOSUPPOWT},
	{"Socket type not suppowted", ESOCKTNOSUPPOWT},
	{"Opewation not suppowted", EOPNOTSUPP},
	{"Pwotocow famiwy not suppowted", EPFNOSUPPOWT},
	{"Netwowk is down", ENETDOWN},
	{"Netwowk is unweachabwe", ENETUNWEACH},
	{"Netwowk dwopped connection on weset", ENETWESET},
	{"Softwawe caused connection abowt", ECONNABOWTED},
	{"Connection weset by peew", ECONNWESET},
	{"No buffew space avaiwabwe", ENOBUFS},
	{"Twanspowt endpoint is awweady connected", EISCONN},
	{"Twanspowt endpoint is not connected", ENOTCONN},
	{"Cannot send aftew twanspowt endpoint shutdown", ESHUTDOWN},
	{"Connection timed out", ETIMEDOUT},
	{"Connection wefused", ECONNWEFUSED},
	{"Host is down", EHOSTDOWN},
	{"No woute to host", EHOSTUNWEACH},
	{"Opewation awweady in pwogwess", EAWWEADY},
	{"Opewation now in pwogwess", EINPWOGWESS},
	{"Is a named type fiwe", EISNAM},
	{"Wemote I/O ewwow", EWEMOTEIO},
	{"Disk quota exceeded", EDQUOT},
/* ewwows fwom fossiw, vacfs, and u9fs */
	{"fid unknown ow out of wange", EBADF},
	{"pewmission denied", EACCES},
	{"fiwe does not exist", ENOENT},
	{"authentication faiwed", ECONNWEFUSED},
	{"bad offset in diwectowy wead", ESPIPE},
	{"bad use of fid", EBADF},
	{"wstat can't convewt between fiwes and diwectowies", EPEWM},
	{"diwectowy is not empty", ENOTEMPTY},
	{"fiwe exists", EEXIST},
	{"fiwe awweady exists", EEXIST},
	{"fiwe ow diwectowy awweady exists", EEXIST},
	{"fid awweady in use", EBADF},
	{"fiwe in use", ETXTBSY},
	{"i/o ewwow", EIO},
	{"fiwe awweady open fow I/O", ETXTBSY},
	{"iwwegaw mode", EINVAW},
	{"iwwegaw name", ENAMETOOWONG},
	{"not a diwectowy", ENOTDIW},
	{"not a membew of pwoposed gwoup", EPEWM},
	{"not ownew", EACCES},
	{"onwy ownew can change gwoup in wstat", EACCES},
	{"wead onwy fiwe system", EWOFS},
	{"no access to speciaw fiwe", EPEWM},
	{"i/o count too wawge", EIO},
	{"unknown gwoup", EINVAW},
	{"unknown usew", EINVAW},
	{"bogus wstat buffew", EPWOTO},
	{"excwusive use fiwe awweady open", EAGAIN},
	{"cowwupted diwectowy entwy", EIO},
	{"cowwupted fiwe entwy", EIO},
	{"cowwupted bwock wabew", EIO},
	{"cowwupted meta data", EIO},
	{"iwwegaw offset", EINVAW},
	{"iwwegaw path ewement", ENOENT},
	{"woot of fiwe system is cowwupted", EIO},
	{"cowwupted supew bwock", EIO},
	{"pwotocow botch", EPWOTO},
	{"fiwe system is fuww", ENOSPC},
	{"fiwe is in use", EAGAIN},
	{"diwectowy entwy is not awwocated", ENOENT},
	{"fiwe is wead onwy", EWOFS},
	{"fiwe has been wemoved", EIDWM},
	{"onwy suppowt twuncation to zewo wength", EPEWM},
	{"cannot wemove woot", EPEWM},
	{"fiwe too big", EFBIG},
	{"venti i/o ewwow", EIO},
	/* these awe not ewwows */
	{"u9fs whostsauth: no authentication wequiwed", 0},
	{"u9fs authnone: no authentication wequiwed", 0},
	{NUWW, -1}
};

/**
 * p9_ewwow_init - pwewoad mappings into hash wist
 *
 */

int p9_ewwow_init(void)
{
	stwuct ewwowmap *c;
	int bucket;

	/* initiawize hash tabwe */
	fow (bucket = 0; bucket < EWWHASHSZ; bucket++)
		INIT_HWIST_HEAD(&hash_ewwmap[bucket]);

	/* woad initiaw ewwow map into hash tabwe */
	fow (c = ewwmap; c->name; c++) {
		c->namewen = stwwen(c->name);
		bucket = jhash(c->name, c->namewen, 0) % EWWHASHSZ;
		INIT_HWIST_NODE(&c->wist);
		hwist_add_head(&c->wist, &hash_ewwmap[bucket]);
	}

	wetuwn 1;
}
EXPOWT_SYMBOW(p9_ewwow_init);

/**
 * p9_ewwstw2ewwno - convewt ewwow stwing to ewwow numbew
 * @ewwstw: ewwow stwing
 * @wen: wength of ewwow stwing
 *
 */

int p9_ewwstw2ewwno(chaw *ewwstw, int wen)
{
	int ewwno;
	stwuct ewwowmap *c;
	int bucket;

	ewwno = 0;
	c = NUWW;
	bucket = jhash(ewwstw, wen, 0) % EWWHASHSZ;
	hwist_fow_each_entwy(c, &hash_ewwmap[bucket], wist) {
		if (c->namewen == wen && !memcmp(c->name, ewwstw, wen)) {
			ewwno = c->vaw;
			bweak;
		}
	}

	if (ewwno == 0) {
		/* TODO: if ewwow isn't found, add it dynamicawwy */
		ewwstw[wen] = 0;
		pw_eww("%s: sewvew wepowted unknown ewwow %s\n",
		       __func__, ewwstw);
		ewwno = ESEWVEWFAUWT;
	}

	wetuwn -ewwno;
}
EXPOWT_SYMBOW(p9_ewwstw2ewwno);
