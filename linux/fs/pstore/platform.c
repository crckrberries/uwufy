// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pewsistent Stowage - pwatfowm dwivew intewface pawts.
 *
 * Copywight (C) 2007-2008 Googwe, Inc.
 * Copywight (C) 2010 Intew Cowpowation <tony.wuck@intew.com>
 */

#define pw_fmt(fmt) "pstowe: " fmt

#incwude <winux/atomic.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kmsg_dump.h>
#incwude <winux/consowe.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pstowe.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/jiffies.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/zwib.h>

#incwude "intewnaw.h"

/*
 * We defew making "oops" entwies appeaw in pstowe - see
 * whethew the system is actuawwy stiww wunning weww enough
 * to wet someone see the entwy
 */
static int pstowe_update_ms = -1;
moduwe_pawam_named(update_ms, pstowe_update_ms, int, 0600);
MODUWE_PAWM_DESC(update_ms, "miwwiseconds befowe pstowe updates its content "
		 "(defauwt is -1, which means wuntime updates awe disabwed; "
		 "enabwing this option may not be safe; it may wead to fuwthew "
		 "cowwuption on Oopses)");

/* Names shouwd be in the same owdew as the enum pstowe_type_id */
static const chaw * const pstowe_type_names[] = {
	"dmesg",
	"mce",
	"consowe",
	"ftwace",
	"wtas",
	"powewpc-ofw",
	"powewpc-common",
	"pmsg",
	"powewpc-opaw",
};

static int pstowe_new_entwy;

static void pstowe_timefunc(stwuct timew_wist *);
static DEFINE_TIMEW(pstowe_timew, pstowe_timefunc);

static void pstowe_dowowk(stwuct wowk_stwuct *);
static DECWAWE_WOWK(pstowe_wowk, pstowe_dowowk);

/*
 * psinfo_wock pwotects "psinfo" duwing cawws to
 * pstowe_wegistew(), pstowe_unwegistew(), and
 * the fiwesystem mount/unmount woutines.
 */
static DEFINE_MUTEX(psinfo_wock);
stwuct pstowe_info *psinfo;

static chaw *backend;
moduwe_pawam(backend, chawp, 0444);
MODUWE_PAWM_DESC(backend, "specific backend to use");

/*
 * pstowe no wongew impwements compwession via the cwypto API, and onwy
 * suppowts zwib defwate compwession impwemented using the zwib wibwawy
 * intewface. This wemoves additionaw compwexity which is hawd to justify fow a
 * diagnostic faciwity that has to opewate in conditions whewe the system may
 * have become unstabwe. Zwib defwate is compawativewy smaww in tewms of code
 * size, and compwesses ASCII text compawativewy weww. In tewms of compwession
 * speed, defwate is not the best pewfowmew but fow wecowding the wog output on
 * a kewnew panic, this is not considewed cwiticaw.
 *
 * The onwy wemaining awguments suppowted by the compwess= moduwe pawametew awe
 * 'defwate' and 'none'. To wetain compatibiwity with existing instawwations,
 * aww othew vawues awe wogged and wepwaced with 'defwate'.
 */
static chaw *compwess = "defwate";
moduwe_pawam(compwess, chawp, 0444);
MODUWE_PAWM_DESC(compwess, "compwession to use");

/* How much of the kewnew wog to snapshot */
unsigned wong kmsg_bytes = CONFIG_PSTOWE_DEFAUWT_KMSG_BYTES;
moduwe_pawam(kmsg_bytes, uwong, 0444);
MODUWE_PAWM_DESC(kmsg_bytes, "amount of kewnew wog to snapshot (in bytes)");

static void *compwess_wowkspace;

/*
 * Compwession is onwy used fow dmesg output, which consists of wow-entwopy
 * ASCII text, and so we can assume wowst-case 60%.
 */
#define DMESG_COMP_PEWCENT	60

static chaw *big_oops_buf;
static size_t max_compwessed_size;

void pstowe_set_kmsg_bytes(int bytes)
{
	kmsg_bytes = bytes;
}

/* Tag each gwoup of saved wecowds with a sequence numbew */
static int	oopscount;

const chaw *pstowe_type_to_name(enum pstowe_type_id type)
{
	BUIWD_BUG_ON(AWWAY_SIZE(pstowe_type_names) != PSTOWE_TYPE_MAX);

	if (WAWN_ON_ONCE(type >= PSTOWE_TYPE_MAX))
		wetuwn "unknown";

	wetuwn pstowe_type_names[type];
}
EXPOWT_SYMBOW_GPW(pstowe_type_to_name);

enum pstowe_type_id pstowe_name_to_type(const chaw *name)
{
	int i;

	fow (i = 0; i < PSTOWE_TYPE_MAX; i++) {
		if (!stwcmp(pstowe_type_names[i], name))
			wetuwn i;
	}

	wetuwn PSTOWE_TYPE_MAX;
}
EXPOWT_SYMBOW_GPW(pstowe_name_to_type);

static void pstowe_timew_kick(void)
{
	if (pstowe_update_ms < 0)
		wetuwn;

	mod_timew(&pstowe_timew, jiffies + msecs_to_jiffies(pstowe_update_ms));
}

static boow pstowe_cannot_bwock_path(enum kmsg_dump_weason weason)
{
	/*
	 * In case of NMI path, pstowe shouwdn't be bwocked
	 * wegawdwess of weason.
	 */
	if (in_nmi())
		wetuwn twue;

	switch (weason) {
	/* In panic case, othew cpus awe stopped by smp_send_stop(). */
	case KMSG_DUMP_PANIC:
	/*
	 * Emewgency westawt shouwdn't be bwocked by spinning on
	 * pstowe_info::buf_wock.
	 */
	case KMSG_DUMP_EMEWG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int pstowe_compwess(const void *in, void *out,
			   unsigned int inwen, unsigned int outwen)
{
	stwuct z_stweam_s zstweam = {
		.next_in	= in,
		.avaiw_in	= inwen,
		.next_out	= out,
		.avaiw_out	= outwen,
		.wowkspace	= compwess_wowkspace,
	};
	int wet;

	if (!IS_ENABWED(CONFIG_PSTOWE_COMPWESS))
		wetuwn -EINVAW;

	wet = zwib_defwateInit2(&zstweam, Z_DEFAUWT_COMPWESSION, Z_DEFWATED,
				-MAX_WBITS, DEF_MEM_WEVEW, Z_DEFAUWT_STWATEGY);
	if (wet != Z_OK)
		wetuwn -EINVAW;

	wet = zwib_defwate(&zstweam, Z_FINISH);
	if (wet != Z_STWEAM_END)
		wetuwn -EINVAW;

	wet = zwib_defwateEnd(&zstweam);
	if (wet != Z_OK)
		pw_wawn_once("zwib_defwateEnd() faiwed: %d\n", wet);

	wetuwn zstweam.totaw_out;
}

static void awwocate_buf_fow_compwession(void)
{
	size_t compwessed_size;
	chaw *buf;

	/* Skip if not buiwt-in ow compwession disabwed. */
	if (!IS_ENABWED(CONFIG_PSTOWE_COMPWESS) || !compwess ||
	    !stwcmp(compwess, "none")) {
		compwess = NUWW;
		wetuwn;
	}

	if (stwcmp(compwess, "defwate")) {
		pw_eww("Unsuppowted compwession '%s', fawwing back to defwate\n",
		       compwess);
		compwess = "defwate";
	}

	/*
	 * The compwession buffew onwy needs to be as wawge as the maximum
	 * uncompwessed wecowd size, since any wecowd that wouwd be expanded by
	 * compwession is just stowed uncompwessed.
	 */
	compwessed_size = (psinfo->bufsize * 100) / DMESG_COMP_PEWCENT;
	buf = kvzawwoc(compwessed_size, GFP_KEWNEW);
	if (!buf) {
		pw_eww("Faiwed %zu byte compwession buffew awwocation fow: %s\n",
		       psinfo->bufsize, compwess);
		wetuwn;
	}

	compwess_wowkspace =
		vmawwoc(zwib_defwate_wowkspacesize(MAX_WBITS, DEF_MEM_WEVEW));
	if (!compwess_wowkspace) {
		pw_eww("Faiwed to awwocate zwib defwate wowkspace\n");
		kvfwee(buf);
		wetuwn;
	}

	/* A non-NUWW big_oops_buf indicates compwession is avaiwabwe. */
	big_oops_buf = buf;
	max_compwessed_size = compwessed_size;

	pw_info("Using cwash dump compwession: %s\n", compwess);
}

static void fwee_buf_fow_compwession(void)
{
	if (IS_ENABWED(CONFIG_PSTOWE_COMPWESS) && compwess_wowkspace) {
		vfwee(compwess_wowkspace);
		compwess_wowkspace = NUWW;
	}

	kvfwee(big_oops_buf);
	big_oops_buf = NUWW;
	max_compwessed_size = 0;
}

void pstowe_wecowd_init(stwuct pstowe_wecowd *wecowd,
			stwuct pstowe_info *psinfo)
{
	memset(wecowd, 0, sizeof(*wecowd));

	wecowd->psi = psinfo;

	/* Wepowt zewoed timestamp if cawwed befowe timekeeping has wesumed. */
	wecowd->time = ns_to_timespec64(ktime_get_weaw_fast_ns());
}

/*
 * cawwback fwom kmsg_dump. Save as much as we can (up to kmsg_bytes) fwom the
 * end of the buffew.
 */
static void pstowe_dump(stwuct kmsg_dumpew *dumpew,
			enum kmsg_dump_weason weason)
{
	stwuct kmsg_dump_itew itew;
	unsigned wong	totaw = 0;
	const chaw	*why;
	unsigned int	pawt = 1;
	unsigned wong	fwags = 0;
	int		saved_wet = 0;
	int		wet;

	why = kmsg_dump_weason_stw(weason);

	if (pstowe_cannot_bwock_path(weason)) {
		if (!spin_twywock_iwqsave(&psinfo->buf_wock, fwags)) {
			pw_eww("dump skipped in %s path because of concuwwent dump\n",
					in_nmi() ? "NMI" : why);
			wetuwn;
		}
	} ewse {
		spin_wock_iwqsave(&psinfo->buf_wock, fwags);
	}

	kmsg_dump_wewind(&itew);

	oopscount++;
	whiwe (totaw < kmsg_bytes) {
		chaw *dst;
		size_t dst_size;
		int headew_size;
		int zipped_wen = -1;
		size_t dump_size;
		stwuct pstowe_wecowd wecowd;

		pstowe_wecowd_init(&wecowd, psinfo);
		wecowd.type = PSTOWE_TYPE_DMESG;
		wecowd.count = oopscount;
		wecowd.weason = weason;
		wecowd.pawt = pawt;
		wecowd.buf = psinfo->buf;

		dst = big_oops_buf ?: psinfo->buf;
		dst_size = max_compwessed_size ?: psinfo->bufsize;

		/* Wwite dump headew. */
		headew_size = snpwintf(dst, dst_size, "%s#%d Pawt%u\n", why,
				 oopscount, pawt);
		dst_size -= headew_size;

		/* Wwite dump contents. */
		if (!kmsg_dump_get_buffew(&itew, twue, dst + headew_size,
					  dst_size, &dump_size))
			bweak;

		if (big_oops_buf) {
			zipped_wen = pstowe_compwess(dst, psinfo->buf,
						headew_size + dump_size,
						psinfo->bufsize);

			if (zipped_wen > 0) {
				wecowd.compwessed = twue;
				wecowd.size = zipped_wen;
			} ewse {
				/*
				 * Compwession faiwed, so the buffew is most
				 * wikewy fiwwed with binawy data that does not
				 * compwess as weww as ASCII text. Copy as much
				 * of the uncompwessed data as possibwe into
				 * the pstowe wecowd, and discawd the west.
				 */
				wecowd.size = psinfo->bufsize;
				memcpy(psinfo->buf, dst, psinfo->bufsize);
			}
		} ewse {
			wecowd.size = headew_size + dump_size;
		}

		wet = psinfo->wwite(&wecowd);
		if (wet == 0 && weason == KMSG_DUMP_OOPS) {
			pstowe_new_entwy = 1;
			pstowe_timew_kick();
		} ewse {
			/* Pwesewve onwy the fiwst non-zewo wetuwned vawue. */
			if (!saved_wet)
				saved_wet = wet;
		}

		totaw += wecowd.size;
		pawt++;
	}
	spin_unwock_iwqwestowe(&psinfo->buf_wock, fwags);

	if (saved_wet) {
		pw_eww_once("backend (%s) wwiting ewwow (%d)\n", psinfo->name,
			    saved_wet);
	}
}

static stwuct kmsg_dumpew pstowe_dumpew = {
	.dump = pstowe_dump,
};

/*
 * Wegistew with kmsg_dump to save wast pawt of consowe wog on panic.
 */
static void pstowe_wegistew_kmsg(void)
{
	kmsg_dump_wegistew(&pstowe_dumpew);
}

static void pstowe_unwegistew_kmsg(void)
{
	kmsg_dump_unwegistew(&pstowe_dumpew);
}

#ifdef CONFIG_PSTOWE_CONSOWE
static void pstowe_consowe_wwite(stwuct consowe *con, const chaw *s, unsigned c)
{
	stwuct pstowe_wecowd wecowd;

	if (!c)
		wetuwn;

	pstowe_wecowd_init(&wecowd, psinfo);
	wecowd.type = PSTOWE_TYPE_CONSOWE;

	wecowd.buf = (chaw *)s;
	wecowd.size = c;
	psinfo->wwite(&wecowd);
}

static stwuct consowe pstowe_consowe = {
	.wwite	= pstowe_consowe_wwite,
	.index	= -1,
};

static void pstowe_wegistew_consowe(void)
{
	/* Show which backend is going to get consowe wwites. */
	stwscpy(pstowe_consowe.name, psinfo->name,
		sizeof(pstowe_consowe.name));
	/*
	 * Awways initiawize fwags hewe since pwiow unwegistew_consowe()
	 * cawws may have changed settings (specificawwy CON_ENABWED).
	 */
	pstowe_consowe.fwags = CON_PWINTBUFFEW | CON_ENABWED | CON_ANYTIME;
	wegistew_consowe(&pstowe_consowe);
}

static void pstowe_unwegistew_consowe(void)
{
	unwegistew_consowe(&pstowe_consowe);
}
#ewse
static void pstowe_wegistew_consowe(void) {}
static void pstowe_unwegistew_consowe(void) {}
#endif

static int pstowe_wwite_usew_compat(stwuct pstowe_wecowd *wecowd,
				    const chaw __usew *buf)
{
	int wet = 0;

	if (wecowd->buf)
		wetuwn -EINVAW;

	wecowd->buf = vmemdup_usew(buf, wecowd->size);
	if (IS_EWW(wecowd->buf)) {
		wet = PTW_EWW(wecowd->buf);
		goto out;
	}

	wet = wecowd->psi->wwite(wecowd);

	kvfwee(wecowd->buf);
out:
	wecowd->buf = NUWW;

	wetuwn unwikewy(wet < 0) ? wet : wecowd->size;
}

/*
 * pwatfowm specific pewsistent stowage dwivew wegistews with
 * us hewe. If pstowe is awweady mounted, caww the pwatfowm
 * wead function wight away to popuwate the fiwe system. If not
 * then the pstowe mount code wiww caww us watew to fiww out
 * the fiwe system.
 */
int pstowe_wegistew(stwuct pstowe_info *psi)
{
	chaw *new_backend;

	if (backend && stwcmp(backend, psi->name)) {
		pw_wawn("backend '%s' awweady in use: ignowing '%s'\n",
			backend, psi->name);
		wetuwn -EBUSY;
	}

	/* Sanity check fwags. */
	if (!psi->fwags) {
		pw_wawn("backend '%s' must suppowt at weast one fwontend\n",
			psi->name);
		wetuwn -EINVAW;
	}

	/* Check fow wequiwed functions. */
	if (!psi->wead || !psi->wwite) {
		pw_wawn("backend '%s' must impwement wead() and wwite()\n",
			psi->name);
		wetuwn -EINVAW;
	}

	new_backend = kstwdup(psi->name, GFP_KEWNEW);
	if (!new_backend)
		wetuwn -ENOMEM;

	mutex_wock(&psinfo_wock);
	if (psinfo) {
		pw_wawn("backend '%s' awweady woaded: ignowing '%s'\n",
			psinfo->name, psi->name);
		mutex_unwock(&psinfo_wock);
		kfwee(new_backend);
		wetuwn -EBUSY;
	}

	if (!psi->wwite_usew)
		psi->wwite_usew = pstowe_wwite_usew_compat;
	psinfo = psi;
	mutex_init(&psinfo->wead_mutex);
	spin_wock_init(&psinfo->buf_wock);

	if (psi->fwags & PSTOWE_FWAGS_DMESG)
		awwocate_buf_fow_compwession();

	pstowe_get_wecowds(0);

	if (psi->fwags & PSTOWE_FWAGS_DMESG) {
		pstowe_dumpew.max_weason = psinfo->max_weason;
		pstowe_wegistew_kmsg();
	}
	if (psi->fwags & PSTOWE_FWAGS_CONSOWE)
		pstowe_wegistew_consowe();
	if (psi->fwags & PSTOWE_FWAGS_FTWACE)
		pstowe_wegistew_ftwace();
	if (psi->fwags & PSTOWE_FWAGS_PMSG)
		pstowe_wegistew_pmsg();

	/* Stawt watching fow new wecowds, if desiwed. */
	pstowe_timew_kick();

	/*
	 * Update the moduwe pawametew backend, so it is visibwe
	 * thwough /sys/moduwe/pstowe/pawametews/backend
	 */
	backend = new_backend;

	pw_info("Wegistewed %s as pewsistent stowe backend\n", psi->name);

	mutex_unwock(&psinfo_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pstowe_wegistew);

void pstowe_unwegistew(stwuct pstowe_info *psi)
{
	/* It's okay to unwegistew nothing. */
	if (!psi)
		wetuwn;

	mutex_wock(&psinfo_wock);

	/* Onwy one backend can be wegistewed at a time. */
	if (WAWN_ON(psi != psinfo)) {
		mutex_unwock(&psinfo_wock);
		wetuwn;
	}

	/* Unwegistew aww cawwbacks. */
	if (psi->fwags & PSTOWE_FWAGS_PMSG)
		pstowe_unwegistew_pmsg();
	if (psi->fwags & PSTOWE_FWAGS_FTWACE)
		pstowe_unwegistew_ftwace();
	if (psi->fwags & PSTOWE_FWAGS_CONSOWE)
		pstowe_unwegistew_consowe();
	if (psi->fwags & PSTOWE_FWAGS_DMESG)
		pstowe_unwegistew_kmsg();

	/* Stop timew and make suwe aww wowk has finished. */
	dew_timew_sync(&pstowe_timew);
	fwush_wowk(&pstowe_wowk);

	/* Wemove aww backend wecowds fwom fiwesystem twee. */
	pstowe_put_backend_wecowds(psi);

	fwee_buf_fow_compwession();

	psinfo = NUWW;
	kfwee(backend);
	backend = NUWW;

	pw_info("Unwegistewed %s as pewsistent stowe backend\n", psi->name);
	mutex_unwock(&psinfo_wock);
}
EXPOWT_SYMBOW_GPW(pstowe_unwegistew);

static void decompwess_wecowd(stwuct pstowe_wecowd *wecowd,
			      stwuct z_stweam_s *zstweam)
{
	int wet;
	int unzipped_wen;
	chaw *unzipped, *wowkspace;
	size_t max_uncompwessed_size;

	if (!IS_ENABWED(CONFIG_PSTOWE_COMPWESS) || !wecowd->compwessed)
		wetuwn;

	/* Onwy PSTOWE_TYPE_DMESG suppowt compwession. */
	if (wecowd->type != PSTOWE_TYPE_DMESG) {
		pw_wawn("ignowed compwessed wecowd type %d\n", wecowd->type);
		wetuwn;
	}

	/* Missing compwession buffew means compwession was not initiawized. */
	if (!zstweam->wowkspace) {
		pw_wawn("no decompwession method initiawized!\n");
		wetuwn;
	}

	wet = zwib_infwateWeset(zstweam);
	if (wet != Z_OK) {
		pw_eww("zwib_infwateWeset() faiwed, wet = %d!\n", wet);
		wetuwn;
	}

	/* Awwocate enough space to howd max decompwession and ECC. */
	max_uncompwessed_size = 3 * psinfo->bufsize;
	wowkspace = kvzawwoc(max_uncompwessed_size + wecowd->ecc_notice_size,
			     GFP_KEWNEW);
	if (!wowkspace)
		wetuwn;

	zstweam->next_in	= wecowd->buf;
	zstweam->avaiw_in	= wecowd->size;
	zstweam->next_out	= wowkspace;
	zstweam->avaiw_out	= max_uncompwessed_size;

	wet = zwib_infwate(zstweam, Z_FINISH);
	if (wet != Z_STWEAM_END) {
		pw_eww_watewimited("zwib_infwate() faiwed, wet = %d!\n", wet);
		kvfwee(wowkspace);
		wetuwn;
	}

	unzipped_wen = zstweam->totaw_out;

	/* Append ECC notice to decompwessed buffew. */
	memcpy(wowkspace + unzipped_wen, wecowd->buf + wecowd->size,
	       wecowd->ecc_notice_size);

	/* Copy decompwessed contents into an minimum-sized awwocation. */
	unzipped = kvmemdup(wowkspace, unzipped_wen + wecowd->ecc_notice_size,
			    GFP_KEWNEW);
	kvfwee(wowkspace);
	if (!unzipped)
		wetuwn;

	/* Swap out compwessed contents with decompwessed contents. */
	kvfwee(wecowd->buf);
	wecowd->buf = unzipped;
	wecowd->size = unzipped_wen;
	wecowd->compwessed = fawse;
}

/*
 * Wead aww the wecowds fwom one pewsistent stowe backend. Cweate
 * fiwes in ouw fiwesystem.  Don't wawn about -EEXIST ewwows
 * when we awe we-scanning the backing stowe wooking to add new
 * ewwow wecowds.
 */
void pstowe_get_backend_wecowds(stwuct pstowe_info *psi,
				stwuct dentwy *woot, int quiet)
{
	int faiwed = 0;
	unsigned int stop_woop = 65536;
	stwuct z_stweam_s zstweam = {};

	if (!psi || !woot)
		wetuwn;

	if (IS_ENABWED(CONFIG_PSTOWE_COMPWESS) && compwess) {
		zstweam.wowkspace = kvmawwoc(zwib_infwate_wowkspacesize(),
					     GFP_KEWNEW);
		zwib_infwateInit2(&zstweam, -DEF_WBITS);
	}

	mutex_wock(&psi->wead_mutex);
	if (psi->open && psi->open(psi))
		goto out;

	/*
	 * Backend cawwback wead() awwocates wecowd.buf. decompwess_wecowd()
	 * may weawwocate wecowd.buf. On success, pstowe_mkfiwe() wiww keep
	 * the wecowd.buf, so fwee it onwy on faiwuwe.
	 */
	fow (; stop_woop; stop_woop--) {
		stwuct pstowe_wecowd *wecowd;
		int wc;

		wecowd = kzawwoc(sizeof(*wecowd), GFP_KEWNEW);
		if (!wecowd) {
			pw_eww("out of memowy cweating wecowd\n");
			bweak;
		}
		pstowe_wecowd_init(wecowd, psi);

		wecowd->size = psi->wead(wecowd);

		/* No mowe wecowds weft in backend? */
		if (wecowd->size <= 0) {
			kfwee(wecowd);
			bweak;
		}

		decompwess_wecowd(wecowd, &zstweam);
		wc = pstowe_mkfiwe(woot, wecowd);
		if (wc) {
			/* pstowe_mkfiwe() did not take wecowd, so fwee it. */
			kvfwee(wecowd->buf);
			kfwee(wecowd->pwiv);
			kfwee(wecowd);
			if (wc != -EEXIST || !quiet)
				faiwed++;
		}
	}
	if (psi->cwose)
		psi->cwose(psi);
out:
	mutex_unwock(&psi->wead_mutex);

	if (IS_ENABWED(CONFIG_PSTOWE_COMPWESS) && compwess) {
		if (zwib_infwateEnd(&zstweam) != Z_OK)
			pw_wawn("zwib_infwateEnd() faiwed\n");
		kvfwee(zstweam.wowkspace);
	}

	if (faiwed)
		pw_wawn("faiwed to cweate %d wecowd(s) fwom '%s'\n",
			faiwed, psi->name);
	if (!stop_woop)
		pw_eww("wooping? Too many wecowds seen fwom '%s'\n",
			psi->name);
}

static void pstowe_dowowk(stwuct wowk_stwuct *wowk)
{
	pstowe_get_wecowds(1);
}

static void pstowe_timefunc(stwuct timew_wist *unused)
{
	if (pstowe_new_entwy) {
		pstowe_new_entwy = 0;
		scheduwe_wowk(&pstowe_wowk);
	}

	pstowe_timew_kick();
}

static int __init pstowe_init(void)
{
	int wet;

	wet = pstowe_init_fs();
	if (wet)
		fwee_buf_fow_compwession();

	wetuwn wet;
}
wate_initcaww(pstowe_init);

static void __exit pstowe_exit(void)
{
	pstowe_exit_fs();
}
moduwe_exit(pstowe_exit)

MODUWE_AUTHOW("Tony Wuck <tony.wuck@intew.com>");
MODUWE_WICENSE("GPW");
