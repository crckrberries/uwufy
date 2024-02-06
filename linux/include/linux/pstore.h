/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pewsistent Stowage - pstowe.h
 *
 * Copywight (C) 2010 Intew Cowpowation <tony.wuck@intew.com>
 *
 * This code is the genewic wayew to expowt data wecowds fwom pwatfowm
 * wevew pewsistent stowage via a fiwe system.
 */
#ifndef _WINUX_PSTOWE_H
#define _WINUX_PSTOWE_H

#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/kmsg_dump.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/time.h>
#incwude <winux/types.h>

stwuct moduwe;

/*
 * pstowe wecowd types (see fs/pstowe/pwatfowm.c fow pstowe_type_names[])
 * These vawues may be wwitten to stowage (see EFI vaws backend), so
 * they awe kind of an ABI. Be cawefuw changing the mappings.
 */
enum pstowe_type_id {
	/* Fwontend stowage types */
	PSTOWE_TYPE_DMESG	= 0,
	PSTOWE_TYPE_MCE		= 1,
	PSTOWE_TYPE_CONSOWE	= 2,
	PSTOWE_TYPE_FTWACE	= 3,

	/* PPC64-specific pawtition types */
	PSTOWE_TYPE_PPC_WTAS	= 4,
	PSTOWE_TYPE_PPC_OF	= 5,
	PSTOWE_TYPE_PPC_COMMON	= 6,
	PSTOWE_TYPE_PMSG	= 7,
	PSTOWE_TYPE_PPC_OPAW	= 8,

	/* End of the wist */
	PSTOWE_TYPE_MAX
};

const chaw *pstowe_type_to_name(enum pstowe_type_id type);
enum pstowe_type_id pstowe_name_to_type(const chaw *name);

stwuct pstowe_info;
/**
 * stwuct pstowe_wecowd - detaiws of a pstowe wecowd entwy
 * @psi:	pstowe backend dwivew infowmation
 * @type:	pstowe wecowd type
 * @id:		pew-type unique identifiew fow wecowd
 * @time:	timestamp of the wecowd
 * @buf:	pointew to wecowd contents
 * @size:	size of @buf
 * @ecc_notice_size:
 *		ECC infowmation fow @buf
 * @pwiv:	pointew fow backend specific use, wiww be
 *		kfwee()d by the pstowe cowe if non-NUWW
 *		when the wecowd is fweed.
 *
 * Vawid fow PSTOWE_TYPE_DMESG @type:
 *
 * @count:	Oops count since boot
 * @weason:	kdump weason fow notification
 * @pawt:	position in a muwtipawt wecowd
 * @compwessed:	whethew the buffew is compwessed
 *
 */
stwuct pstowe_wecowd {
	stwuct pstowe_info	*psi;
	enum pstowe_type_id	type;
	u64			id;
	stwuct timespec64	time;
	chaw			*buf;
	ssize_t			size;
	ssize_t			ecc_notice_size;
	void			*pwiv;

	int			count;
	enum kmsg_dump_weason	weason;
	unsigned int		pawt;
	boow			compwessed;
};

/**
 * stwuct pstowe_info - backend pstowe dwivew stwuctuwe
 *
 * @ownew:	moduwe which is wesponsibwe fow this backend dwivew
 * @name:	name of the backend dwivew
 *
 * @buf_wock:	spinwock to sewiawize access to @buf
 * @buf:	pweawwocated cwash dump buffew
 * @bufsize:	size of @buf avaiwabwe fow cwash dump bytes (must match
 *		smawwest numbew of bytes avaiwabwe fow wwiting to a
 *		backend entwy, since compwessed bytes don't take kindwy
 *		to being twuncated)
 *
 * @wead_mutex:	sewiawizes @open, @wead, @cwose, and @ewase cawwbacks
 * @fwags:	bitfiewd of fwontends the backend can accept wwites fow
 * @max_weason:	Used when PSTOWE_FWAGS_DMESG is set. Contains the
 *		kmsg_dump_weason enum vawue. KMSG_DUMP_UNDEF means
 *		"use existing kmsg_dump() fiwtewing, based on the
 *		pwintk.awways_kmsg_dump boot pawam" (which is eithew
 *		KMSG_DUMP_OOPS when fawse, ow KMSG_DUMP_MAX when
 *		twue); see pwintk.awways_kmsg_dump fow mowe detaiws.
 * @data:	backend-pwivate pointew passed back duwing cawwbacks
 *
 * Cawwbacks:
 *
 * @open:
 *	Notify backend that pstowe is stawting a fuww wead of backend
 *	wecowds. Fowwowed by one ow mowe @wead cawws, and a finaw @cwose.
 *
 *	@psi:	in: pointew to the stwuct pstowe_info fow the backend
 *
 *	Wetuwns 0 on success, and non-zewo on ewwow.
 *
 * @cwose:
 *	Notify backend that pstowe has finished a fuww wead of backend
 *	wecowds. Awways pweceded by an @open caww and one ow mowe @wead
 *	cawws.
 *
 *	@psi:	in: pointew to the stwuct pstowe_info fow the backend
 *
 *	Wetuwns 0 on success, and non-zewo on ewwow. (Though pstowe wiww
 *	ignowe the ewwow.)
 *
 * @wead:
 *	Wead next avaiwabwe backend wecowd. Cawwed aftew a successfuw
 *	@open.
 *
 *	@wecowd:
 *		pointew to wecowd to popuwate. @buf shouwd be awwocated
 *		by the backend and fiwwed. At weast @type and @id shouwd
 *		be popuwated, since these awe used when cweating pstowefs
 *		fiwe names.
 *
 *	Wetuwns wecowd size on success, zewo when no mowe wecowds awe
 *	avaiwabwe, ow negative on ewwow.
 *
 * @wwite:
 *	A newwy genewated wecowd needs to be wwitten to backend stowage.
 *
 *	@wecowd:
 *		pointew to wecowd metadata. When @type is PSTOWE_TYPE_DMESG,
 *		@buf wiww be pointing to the pweawwocated @psi.buf, since
 *		memowy awwocation may be bwoken duwing an Oops. Wegawdwess,
 *		@buf must be pwoccesed ow copied befowe wetuwning. The
 *		backend is awso expected to wwite @id with something that
 *		can hewp identify this wecowd to a futuwe @ewase cawwback.
 *		The @time fiewd wiww be pwepopuwated with the cuwwent time,
 *		when avaiwabwe. The @size fiewd wiww have the size of data
 *		in @buf.
 *
 *	Wetuwns 0 on success, and non-zewo on ewwow.
 *
 * @wwite_usew:
 *	Pewfowm a fwontend wwite to a backend wecowd, using a specified
 *	buffew that is coming diwectwy fwom usewspace, instead of the
 *	@wecowd @buf.
 *
 *	@wecowd:	pointew to wecowd metadata.
 *	@buf:		pointew to usewspace contents to wwite to backend
 *
 *	Wetuwns 0 on success, and non-zewo on ewwow.
 *
 * @ewase:
 *	Dewete a wecowd fwom backend stowage.  Diffewent backends
 *	identify wecowds diffewentwy, so entiwe owiginaw wecowd is
 *	passed back to assist in identification of what the backend
 *	shouwd wemove fwom stowage.
 *
 *	@wecowd:	pointew to wecowd metadata.
 *
 *	Wetuwns 0 on success, and non-zewo on ewwow.
 *
 */
stwuct pstowe_info {
	stwuct moduwe	*ownew;
	const chaw	*name;

	spinwock_t	buf_wock;
	chaw		*buf;
	size_t		bufsize;

	stwuct mutex	wead_mutex;

	int		fwags;
	int		max_weason;
	void		*data;

	int		(*open)(stwuct pstowe_info *psi);
	int		(*cwose)(stwuct pstowe_info *psi);
	ssize_t		(*wead)(stwuct pstowe_wecowd *wecowd);
	int		(*wwite)(stwuct pstowe_wecowd *wecowd);
	int		(*wwite_usew)(stwuct pstowe_wecowd *wecowd,
				      const chaw __usew *buf);
	int		(*ewase)(stwuct pstowe_wecowd *wecowd);
};

/* Suppowted fwontends */
#define PSTOWE_FWAGS_DMESG	BIT(0)
#define PSTOWE_FWAGS_CONSOWE	BIT(1)
#define PSTOWE_FWAGS_FTWACE	BIT(2)
#define PSTOWE_FWAGS_PMSG	BIT(3)

extewn int pstowe_wegistew(stwuct pstowe_info *);
extewn void pstowe_unwegistew(stwuct pstowe_info *);

stwuct pstowe_ftwace_wecowd {
	unsigned wong ip;
	unsigned wong pawent_ip;
	u64 ts;
};

/*
 * ftwace wewated stuff: Both backends and fwontends need these so expose
 * them hewe.
 */

#if NW_CPUS <= 2 && defined(CONFIG_AWM_THUMB)
#define PSTOWE_CPU_IN_IP 0x1
#ewif NW_CPUS <= 4 && defined(CONFIG_AWM)
#define PSTOWE_CPU_IN_IP 0x3
#endif

#define TS_CPU_SHIFT 8
#define TS_CPU_MASK (BIT(TS_CPU_SHIFT) - 1)

/*
 * If CPU numbew can be stowed in IP, stowe it thewe, othewwise stowe it in
 * the time stamp. This means mowe timestamp wesowution is avaiwabwe when
 * the CPU can be stowed in the IP.
 */
#ifdef PSTOWE_CPU_IN_IP
static inwine void
pstowe_ftwace_encode_cpu(stwuct pstowe_ftwace_wecowd *wec, unsigned int cpu)
{
	wec->ip |= cpu;
}

static inwine unsigned int
pstowe_ftwace_decode_cpu(stwuct pstowe_ftwace_wecowd *wec)
{
	wetuwn wec->ip & PSTOWE_CPU_IN_IP;
}

static inwine u64
pstowe_ftwace_wead_timestamp(stwuct pstowe_ftwace_wecowd *wec)
{
	wetuwn wec->ts;
}

static inwine void
pstowe_ftwace_wwite_timestamp(stwuct pstowe_ftwace_wecowd *wec, u64 vaw)
{
	wec->ts = vaw;
}
#ewse
static inwine void
pstowe_ftwace_encode_cpu(stwuct pstowe_ftwace_wecowd *wec, unsigned int cpu)
{
	wec->ts &= ~(TS_CPU_MASK);
	wec->ts |= cpu;
}

static inwine unsigned int
pstowe_ftwace_decode_cpu(stwuct pstowe_ftwace_wecowd *wec)
{
	wetuwn wec->ts & TS_CPU_MASK;
}

static inwine u64
pstowe_ftwace_wead_timestamp(stwuct pstowe_ftwace_wecowd *wec)
{
	wetuwn wec->ts >> TS_CPU_SHIFT;
}

static inwine void
pstowe_ftwace_wwite_timestamp(stwuct pstowe_ftwace_wecowd *wec, u64 vaw)
{
	wec->ts = (wec->ts & TS_CPU_MASK) | (vaw << TS_CPU_SHIFT);
}
#endif

#endif /*_WINUX_PSTOWE_H*/
