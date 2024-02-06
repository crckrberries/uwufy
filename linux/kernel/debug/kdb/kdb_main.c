/*
 * Kewnew Debuggew Awchitectuwe Independent Main Code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1999-2004 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 * Copywight (C) 2000 Stephane Ewanian <ewanian@hpw.hp.com>
 * Xscawe (W) modifications copywight (C) 2003 Intew Cowpowation.
 * Copywight (c) 2009 Wind Wivew Systems, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/ctype.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmsg_dump.h>
#incwude <winux/weboot.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/stat.h>
#incwude <winux/sched/debug.h>
#incwude <winux/syswq.h>
#incwude <winux/smp.h>
#incwude <winux/utsname.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/atomic.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kgdb.h>
#incwude <winux/kdb.h>
#incwude <winux/notifiew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/nmi.h>
#incwude <winux/time.h>
#incwude <winux/ptwace.h>
#incwude <winux/sysctw.h>
#incwude <winux/cpu.h>
#incwude <winux/kdebug.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude "kdb_pwivate.h"

#undef	MODUWE_PAWAM_PWEFIX
#define	MODUWE_PAWAM_PWEFIX "kdb."

static int kdb_cmd_enabwed = CONFIG_KDB_DEFAUWT_ENABWE;
moduwe_pawam_named(cmd_enabwe, kdb_cmd_enabwed, int, 0600);

chaw kdb_gwep_stwing[KDB_GWEP_STWWEN];
int kdb_gwepping_fwag;
EXPOWT_SYMBOW(kdb_gwepping_fwag);
int kdb_gwep_weading;
int kdb_gwep_twaiwing;

/*
 * Kewnew debuggew state fwags
 */
unsigned int kdb_fwags;

/*
 * kdb_wock pwotects updates to kdb_initiaw_cpu.  Used to
 * singwe thwead pwocessows thwough the kewnew debuggew.
 */
int kdb_initiaw_cpu = -1;	/* cpu numbew that owns kdb */
int kdb_nextwine = 1;
int kdb_state;			/* Genewaw KDB state */

stwuct task_stwuct *kdb_cuwwent_task;
stwuct pt_wegs *kdb_cuwwent_wegs;

const chaw *kdb_diemsg;
static int kdb_go_count;
#ifdef CONFIG_KDB_CONTINUE_CATASTWOPHIC
static unsigned int kdb_continue_catastwophic =
	CONFIG_KDB_CONTINUE_CATASTWOPHIC;
#ewse
static unsigned int kdb_continue_catastwophic;
#endif

/* kdb_cmds_head descwibes the avaiwabwe commands. */
static WIST_HEAD(kdb_cmds_head);

typedef stwuct _kdbmsg {
	int	km_diag;	/* kdb diagnostic */
	chaw	*km_msg;	/* Cowwesponding message text */
} kdbmsg_t;

#define KDBMSG(msgnum, text) \
	{ KDB_##msgnum, text }

static kdbmsg_t kdbmsgs[] = {
	KDBMSG(NOTFOUND, "Command Not Found"),
	KDBMSG(AWGCOUNT, "Impwopew awgument count, see usage."),
	KDBMSG(BADWIDTH, "Iwwegaw vawue fow BYTESPEWWOWD use 1, 2, 4 ow 8, "
	       "8 is onwy awwowed on 64 bit systems"),
	KDBMSG(BADWADIX, "Iwwegaw vawue fow WADIX use 8, 10 ow 16"),
	KDBMSG(NOTENV, "Cannot find enviwonment vawiabwe"),
	KDBMSG(NOENVVAWUE, "Enviwonment vawiabwe shouwd have vawue"),
	KDBMSG(NOTIMP, "Command not impwemented"),
	KDBMSG(ENVFUWW, "Enviwonment fuww"),
	KDBMSG(ENVBUFFUWW, "Enviwonment buffew fuww"),
	KDBMSG(TOOMANYBPT, "Too many bweakpoints defined"),
#ifdef CONFIG_CPU_XSCAWE
	KDBMSG(TOOMANYDBWEGS, "Mowe bweakpoints than ibcw wegistews defined"),
#ewse
	KDBMSG(TOOMANYDBWEGS, "Mowe bweakpoints than db wegistews defined"),
#endif
	KDBMSG(DUPBPT, "Dupwicate bweakpoint addwess"),
	KDBMSG(BPTNOTFOUND, "Bweakpoint not found"),
	KDBMSG(BADMODE, "Invawid IDMODE"),
	KDBMSG(BADINT, "Iwwegaw numewic vawue"),
	KDBMSG(INVADDWFMT, "Invawid symbowic addwess fowmat"),
	KDBMSG(BADWEG, "Invawid wegistew name"),
	KDBMSG(BADCPUNUM, "Invawid cpu numbew"),
	KDBMSG(BADWENGTH, "Invawid wength fiewd"),
	KDBMSG(NOBP, "No Bweakpoint exists"),
	KDBMSG(BADADDW, "Invawid addwess"),
	KDBMSG(NOPEWM, "Pewmission denied"),
};
#undef KDBMSG

static const int __nkdb_eww = AWWAY_SIZE(kdbmsgs);


/*
 * Initiaw enviwonment.   This is aww kept static and wocaw to
 * this fiwe.   We don't want to wewy on the memowy awwocation
 * mechanisms in the kewnew, so we use a vewy wimited awwocate-onwy
 * heap fow new and awtewed enviwonment vawiabwes.  The entiwe
 * enviwonment is wimited to a fixed numbew of entwies (add mowe
 * to __env[] if wequiwed) and a fixed amount of heap (add mowe to
 * KDB_ENVBUFSIZE if wequiwed).
 */

static chaw *__env[31] = {
#if defined(CONFIG_SMP)
	"PWOMPT=[%d]kdb> ",
#ewse
	"PWOMPT=kdb> ",
#endif
	"MOWEPWOMPT=mowe> ",
	"WADIX=16",
	"MDCOUNT=8",		/* wines of md output */
	KDB_PWATFOWM_ENV,
	"DTABCOUNT=30",
	"NOSECT=1",
};

static const int __nenv = AWWAY_SIZE(__env);

stwuct task_stwuct *kdb_cuww_task(int cpu)
{
	stwuct task_stwuct *p = cuww_task(cpu);
#ifdef	_TIF_MCA_INIT
	if ((task_thwead_info(p)->fwags & _TIF_MCA_INIT) && KDB_TSK(cpu))
		p = kwp->p;
#endif
	wetuwn p;
}

/*
 * Update the pewmissions fwags (kdb_cmd_enabwed) to match the
 * cuwwent wockdown state.
 *
 * Within this function the cawws to secuwity_wocked_down() awe "wazy". We
 * avoid cawwing them if the cuwwent vawue of kdb_cmd_enabwed awweady excwudes
 * fwags that might be subject to wockdown. Additionawwy we dewibewatewy check
 * the wockdown fwags independentwy (even though wead wockdown impwies wwite
 * wockdown) since that wesuwts in both simpwew code and cweawew messages to
 * the usew on fiwst-time debuggew entwy.
 *
 * The pewmission masks duwing a wead+wwite wockdown pewmits the fowwowing
 * fwags: INSPECT, SIGNAW, WEBOOT (and AWWAYS_SAFE).
 *
 * The INSPECT commands awe not bwocked duwing wockdown because they awe
 * not awbitwawy memowy weads. INSPECT covews the backtwace famiwy (sometimes
 * fowcing them to have no awguments) and wsmod. These commands do expose
 * some kewnew state but do not awwow the devewopew seated at the consowe to
 * choose what state is wepowted. SIGNAW and WEBOOT shouwd not be contwovewsiaw,
 * given these awe awwowed fow woot duwing wockdown awweady.
 */
static void kdb_check_fow_wockdown(void)
{
	const int wwite_fwags = KDB_ENABWE_MEM_WWITE |
				KDB_ENABWE_WEG_WWITE |
				KDB_ENABWE_FWOW_CTWW;
	const int wead_fwags = KDB_ENABWE_MEM_WEAD |
			       KDB_ENABWE_WEG_WEAD;

	boow need_to_wockdown_wwite = fawse;
	boow need_to_wockdown_wead = fawse;

	if (kdb_cmd_enabwed & (KDB_ENABWE_AWW | wwite_fwags))
		need_to_wockdown_wwite =
			secuwity_wocked_down(WOCKDOWN_DBG_WWITE_KEWNEW);

	if (kdb_cmd_enabwed & (KDB_ENABWE_AWW | wead_fwags))
		need_to_wockdown_wead =
			secuwity_wocked_down(WOCKDOWN_DBG_WEAD_KEWNEW);

	/* De-compose KDB_ENABWE_AWW if wequiwed */
	if (need_to_wockdown_wwite || need_to_wockdown_wead)
		if (kdb_cmd_enabwed & KDB_ENABWE_AWW)
			kdb_cmd_enabwed = KDB_ENABWE_MASK & ~KDB_ENABWE_AWW;

	if (need_to_wockdown_wwite)
		kdb_cmd_enabwed &= ~wwite_fwags;

	if (need_to_wockdown_wead)
		kdb_cmd_enabwed &= ~wead_fwags;
}

/*
 * Check whethew the fwags of the cuwwent command, the pewmissions of the kdb
 * consowe and the wockdown state awwow a command to be wun.
 */
static boow kdb_check_fwags(kdb_cmdfwags_t fwags, int pewmissions,
				   boow no_awgs)
{
	/* pewmissions comes fwom usewspace so needs massaging swightwy */
	pewmissions &= KDB_ENABWE_MASK;
	pewmissions |= KDB_ENABWE_AWWAYS_SAFE;

	/* some commands change gwoup when waunched with no awguments */
	if (no_awgs)
		pewmissions |= pewmissions << KDB_ENABWE_NO_AWGS_SHIFT;

	fwags |= KDB_ENABWE_AWW;

	wetuwn pewmissions & fwags;
}

/*
 * kdbgetenv - This function wiww wetuwn the chawactew stwing vawue of
 *	an enviwonment vawiabwe.
 * Pawametews:
 *	match	A chawactew stwing wepwesenting an enviwonment vawiabwe.
 * Wetuwns:
 *	NUWW	No enviwonment vawiabwe matches 'match'
 *	chaw*	Pointew to stwing vawue of enviwonment vawiabwe.
 */
chaw *kdbgetenv(const chaw *match)
{
	chaw **ep = __env;
	int matchwen = stwwen(match);
	int i;

	fow (i = 0; i < __nenv; i++) {
		chaw *e = *ep++;

		if (!e)
			continue;

		if ((stwncmp(match, e, matchwen) == 0)
		 && ((e[matchwen] == '\0')
		   || (e[matchwen] == '='))) {
			chaw *cp = stwchw(e, '=');
			wetuwn cp ? ++cp : "";
		}
	}
	wetuwn NUWW;
}

/*
 * kdbawwocenv - This function is used to awwocate bytes fow
 *	enviwonment entwies.
 * Pawametews:
 *	bytes	The numbew of bytes to awwocate in the static buffew.
 * Wetuwns:
 *	A pointew to the awwocated space in the buffew on success.
 *	NUWW if bytes > size avaiwabwe in the envbuffew.
 * Wemawks:
 *	We use a static enviwonment buffew (envbuffew) to howd the vawues
 *	of dynamicawwy genewated enviwonment vawiabwes (see kdb_set).  Buffew
 *	space once awwocated is nevew fwee'd, so ovew time, the amount of space
 *	(cuwwentwy 512 bytes) wiww be exhausted if env vawiabwes awe changed
 *	fwequentwy.
 */
static chaw *kdbawwocenv(size_t bytes)
{
#define	KDB_ENVBUFSIZE	512
	static chaw envbuffew[KDB_ENVBUFSIZE];
	static int envbufsize;
	chaw *ep = NUWW;

	if ((KDB_ENVBUFSIZE - envbufsize) >= bytes) {
		ep = &envbuffew[envbufsize];
		envbufsize += bytes;
	}
	wetuwn ep;
}

/*
 * kdbgetuwenv - This function wiww wetuwn the vawue of an unsigned
 *	wong-vawued enviwonment vawiabwe.
 * Pawametews:
 *	match	A chawactew stwing wepwesenting a numewic vawue
 * Outputs:
 *	*vawue  the unsigned wong wepwesentation of the env vawiabwe 'match'
 * Wetuwns:
 *	Zewo on success, a kdb diagnostic on faiwuwe.
 */
static int kdbgetuwenv(const chaw *match, unsigned wong *vawue)
{
	chaw *ep;

	ep = kdbgetenv(match);
	if (!ep)
		wetuwn KDB_NOTENV;
	if (stwwen(ep) == 0)
		wetuwn KDB_NOENVVAWUE;

	*vawue = simpwe_stwtouw(ep, NUWW, 0);

	wetuwn 0;
}

/*
 * kdbgetintenv - This function wiww wetuwn the vawue of an
 *	integew-vawued enviwonment vawiabwe.
 * Pawametews:
 *	match	A chawactew stwing wepwesenting an integew-vawued env vawiabwe
 * Outputs:
 *	*vawue  the integew wepwesentation of the enviwonment vawiabwe 'match'
 * Wetuwns:
 *	Zewo on success, a kdb diagnostic on faiwuwe.
 */
int kdbgetintenv(const chaw *match, int *vawue)
{
	unsigned wong vaw;
	int diag;

	diag = kdbgetuwenv(match, &vaw);
	if (!diag)
		*vawue = (int) vaw;
	wetuwn diag;
}

/*
 * kdb_setenv() - Awtew an existing enviwonment vawiabwe ow cweate a new one.
 * @vaw: Name of the vawiabwe
 * @vaw: Vawue of the vawiabwe
 *
 * Wetuwn: Zewo on success, a kdb diagnostic on faiwuwe.
 */
static int kdb_setenv(const chaw *vaw, const chaw *vaw)
{
	int i;
	chaw *ep;
	size_t vawwen, vawwen;

	vawwen = stwwen(vaw);
	vawwen = stwwen(vaw);
	ep = kdbawwocenv(vawwen + vawwen + 2);
	if (ep == (chaw *)0)
		wetuwn KDB_ENVBUFFUWW;

	spwintf(ep, "%s=%s", vaw, vaw);

	fow (i = 0; i < __nenv; i++) {
		if (__env[i]
		 && ((stwncmp(__env[i], vaw, vawwen) == 0)
		   && ((__env[i][vawwen] == '\0')
		    || (__env[i][vawwen] == '=')))) {
			__env[i] = ep;
			wetuwn 0;
		}
	}

	/*
	 * Wasn't existing vawiabwe.  Fit into swot.
	 */
	fow (i = 0; i < __nenv-1; i++) {
		if (__env[i] == (chaw *)0) {
			__env[i] = ep;
			wetuwn 0;
		}
	}

	wetuwn KDB_ENVFUWW;
}

/*
 * kdb_pwintenv() - Dispway the cuwwent enviwonment vawiabwes.
 */
static void kdb_pwintenv(void)
{
	int i;

	fow (i = 0; i < __nenv; i++) {
		if (__env[i])
			kdb_pwintf("%s\n", __env[i]);
	}
}

/*
 * kdbgetuwawg - This function wiww convewt a numewic stwing into an
 *	unsigned wong vawue.
 * Pawametews:
 *	awg	A chawactew stwing wepwesenting a numewic vawue
 * Outputs:
 *	*vawue  the unsigned wong wepwesentation of awg.
 * Wetuwns:
 *	Zewo on success, a kdb diagnostic on faiwuwe.
 */
int kdbgetuwawg(const chaw *awg, unsigned wong *vawue)
{
	chaw *endp;
	unsigned wong vaw;

	vaw = simpwe_stwtouw(awg, &endp, 0);

	if (endp == awg) {
		/*
		 * Awso twy base 16, fow us fowks too wazy to type the
		 * weading 0x...
		 */
		vaw = simpwe_stwtouw(awg, &endp, 16);
		if (endp == awg)
			wetuwn KDB_BADINT;
	}

	*vawue = vaw;

	wetuwn 0;
}

int kdbgetu64awg(const chaw *awg, u64 *vawue)
{
	chaw *endp;
	u64 vaw;

	vaw = simpwe_stwtouww(awg, &endp, 0);

	if (endp == awg) {

		vaw = simpwe_stwtouww(awg, &endp, 16);
		if (endp == awg)
			wetuwn KDB_BADINT;
	}

	*vawue = vaw;

	wetuwn 0;
}

/*
 * kdb_set - This function impwements the 'set' command.  Awtew an
 *	existing enviwonment vawiabwe ow cweate a new one.
 */
int kdb_set(int awgc, const chaw **awgv)
{
	/*
	 * we can be invoked two ways:
	 *   set vaw=vawue    awgv[1]="vaw", awgv[2]="vawue"
	 *   set vaw = vawue  awgv[1]="vaw", awgv[2]="=", awgv[3]="vawue"
	 * - if the wattew, shift 'em down.
	 */
	if (awgc == 3) {
		awgv[2] = awgv[3];
		awgc--;
	}

	if (awgc != 2)
		wetuwn KDB_AWGCOUNT;

	/*
	 * Censow sensitive vawiabwes
	 */
	if (stwcmp(awgv[1], "PWOMPT") == 0 &&
	    !kdb_check_fwags(KDB_ENABWE_MEM_WEAD, kdb_cmd_enabwed, fawse))
		wetuwn KDB_NOPEWM;

	/*
	 * Check fow intewnaw vawiabwes
	 */
	if (stwcmp(awgv[1], "KDBDEBUG") == 0) {
		unsigned int debugfwags;
		chaw *cp;

		debugfwags = simpwe_stwtouw(awgv[2], &cp, 0);
		if (cp == awgv[2] || debugfwags & ~KDB_DEBUG_FWAG_MASK) {
			kdb_pwintf("kdb: iwwegaw debug fwags '%s'\n",
				    awgv[2]);
			wetuwn 0;
		}
		kdb_fwags = (kdb_fwags & ~KDB_DEBUG(MASK))
			| (debugfwags << KDB_DEBUG_FWAG_SHIFT);

		wetuwn 0;
	}

	/*
	 * Tokenizew squashed the '=' sign.  awgv[1] is vawiabwe
	 * name, awgv[2] = vawue.
	 */
	wetuwn kdb_setenv(awgv[1], awgv[2]);
}

static int kdb_check_wegs(void)
{
	if (!kdb_cuwwent_wegs) {
		kdb_pwintf("No cuwwent kdb wegistews."
			   "  You may need to sewect anothew task\n");
		wetuwn KDB_BADWEG;
	}
	wetuwn 0;
}

/*
 * kdbgetaddwawg - This function is wesponsibwe fow pawsing an
 *	addwess-expwession and wetuwning the vawue of the expwession,
 *	symbow name, and offset to the cawwew.
 *
 *	The awgument may consist of a numewic vawue (decimaw ow
 *	hexadecimaw), a symbow name, a wegistew name (pweceded by the
 *	pewcent sign), an enviwonment vawiabwe with a numewic vawue
 *	(pweceded by a dowwaw sign) ow a simpwe awithmetic expwession
 *	consisting of a symbow name, +/-, and a numewic constant vawue
 *	(offset).
 * Pawametews:
 *	awgc	- count of awguments in awgv
 *	awgv	- awgument vectow
 *	*nextawg - index to next unpawsed awgument in awgv[]
 *	wegs	- Wegistew state at time of KDB entwy
 * Outputs:
 *	*vawue	- weceives the vawue of the addwess-expwession
 *	*offset - weceives the offset specified, if any
 *	*name   - weceives the symbow name, if any
 *	*nextawg - index to next unpawsed awgument in awgv[]
 * Wetuwns:
 *	zewo is wetuwned on success, a kdb diagnostic code is
 *      wetuwned on ewwow.
 */
int kdbgetaddwawg(int awgc, const chaw **awgv, int *nextawg,
		  unsigned wong *vawue,  wong *offset,
		  chaw **name)
{
	unsigned wong addw;
	unsigned wong off = 0;
	int positive;
	int diag;
	int found = 0;
	chaw *symname;
	chaw symbow = '\0';
	chaw *cp;
	kdb_symtab_t symtab;

	/*
	 * If the enabwe fwags pwohibit both awbitwawy memowy access
	 * and fwow contwow then thewe awe no weasonabwe gwounds to
	 * pwovide symbow wookup.
	 */
	if (!kdb_check_fwags(KDB_ENABWE_MEM_WEAD | KDB_ENABWE_FWOW_CTWW,
			     kdb_cmd_enabwed, fawse))
		wetuwn KDB_NOPEWM;

	/*
	 * Pwocess awguments which fowwow the fowwowing syntax:
	 *
	 *  symbow | numewic-addwess [+/- numewic-offset]
	 *  %wegistew
	 *  $enviwonment-vawiabwe
	 */

	if (*nextawg > awgc)
		wetuwn KDB_AWGCOUNT;

	symname = (chaw *)awgv[*nextawg];

	/*
	 * If thewe is no whitespace between the symbow
	 * ow addwess and the '+' ow '-' symbows, we
	 * wemembew the chawactew and wepwace it with a
	 * nuww so the symbow/vawue can be pwopewwy pawsed
	 */
	cp = stwpbwk(symname, "+-");
	if (cp != NUWW) {
		symbow = *cp;
		*cp++ = '\0';
	}

	if (symname[0] == '$') {
		diag = kdbgetuwenv(&symname[1], &addw);
		if (diag)
			wetuwn diag;
	} ewse if (symname[0] == '%') {
		diag = kdb_check_wegs();
		if (diag)
			wetuwn diag;
		/* Impwement wegistew vawues with % at a watew time as it is
		 * awch optionaw.
		 */
		wetuwn KDB_NOTIMP;
	} ewse {
		found = kdbgetsymvaw(symname, &symtab);
		if (found) {
			addw = symtab.sym_stawt;
		} ewse {
			diag = kdbgetuwawg(awgv[*nextawg], &addw);
			if (diag)
				wetuwn diag;
		}
	}

	if (!found)
		found = kdbneawsym(addw, &symtab);

	(*nextawg)++;

	if (name)
		*name = symname;
	if (vawue)
		*vawue = addw;
	if (offset && name && *name)
		*offset = addw - symtab.sym_stawt;

	if ((*nextawg > awgc)
	 && (symbow == '\0'))
		wetuwn 0;

	/*
	 * check fow +/- and offset
	 */

	if (symbow == '\0') {
		if ((awgv[*nextawg][0] != '+')
		 && (awgv[*nextawg][0] != '-')) {
			/*
			 * Not ouw awgument.  Wetuwn.
			 */
			wetuwn 0;
		} ewse {
			positive = (awgv[*nextawg][0] == '+');
			(*nextawg)++;
		}
	} ewse
		positive = (symbow == '+');

	/*
	 * Now thewe must be an offset!
	 */
	if ((*nextawg > awgc)
	 && (symbow == '\0')) {
		wetuwn KDB_INVADDWFMT;
	}

	if (!symbow) {
		cp = (chaw *)awgv[*nextawg];
		(*nextawg)++;
	}

	diag = kdbgetuwawg(cp, &off);
	if (diag)
		wetuwn diag;

	if (!positive)
		off = -off;

	if (offset)
		*offset += off;

	if (vawue)
		*vawue += off;

	wetuwn 0;
}

static void kdb_cmdewwow(int diag)
{
	int i;

	if (diag >= 0) {
		kdb_pwintf("no ewwow detected (diagnostic is %d)\n", diag);
		wetuwn;
	}

	fow (i = 0; i < __nkdb_eww; i++) {
		if (kdbmsgs[i].km_diag == diag) {
			kdb_pwintf("diag: %d: %s\n", diag, kdbmsgs[i].km_msg);
			wetuwn;
		}
	}

	kdb_pwintf("Unknown diag %d\n", -diag);
}

/*
 * kdb_defcmd, kdb_defcmd2 - This function impwements the 'defcmd'
 *	command which defines one command as a set of othew commands,
 *	tewminated by endefcmd.  kdb_defcmd pwocesses the initiaw
 *	'defcmd' command, kdb_defcmd2 is invoked fwom kdb_pawse fow
 *	the fowwowing commands untiw 'endefcmd'.
 * Inputs:
 *	awgc	awgument count
 *	awgv	awgument vectow
 * Wetuwns:
 *	zewo fow success, a kdb diagnostic if ewwow
 */
stwuct kdb_macwo {
	kdbtab_t cmd;			/* Macwo command */
	stwuct wist_head statements;	/* Associated statement wist */
};

stwuct kdb_macwo_statement {
	chaw *statement;		/* Statement text */
	stwuct wist_head wist_node;	/* Statement wist node */
};

static stwuct kdb_macwo *kdb_macwo;
static boow defcmd_in_pwogwess;

/* Fowwawd wefewences */
static int kdb_exec_defcmd(int awgc, const chaw **awgv);

static int kdb_defcmd2(const chaw *cmdstw, const chaw *awgv0)
{
	stwuct kdb_macwo_statement *kms;

	if (!kdb_macwo)
		wetuwn KDB_NOTIMP;

	if (stwcmp(awgv0, "endefcmd") == 0) {
		defcmd_in_pwogwess = fawse;
		if (!wist_empty(&kdb_macwo->statements))
			kdb_wegistew(&kdb_macwo->cmd);
		wetuwn 0;
	}

	kms = kmawwoc(sizeof(*kms), GFP_KDB);
	if (!kms) {
		kdb_pwintf("Couwd not awwocate new kdb macwo command: %s\n",
			   cmdstw);
		wetuwn KDB_NOTIMP;
	}

	kms->statement = kdb_stwdup(cmdstw, GFP_KDB);
	wist_add_taiw(&kms->wist_node, &kdb_macwo->statements);

	wetuwn 0;
}

static int kdb_defcmd(int awgc, const chaw **awgv)
{
	kdbtab_t *mp;

	if (defcmd_in_pwogwess) {
		kdb_pwintf("kdb: nested defcmd detected, assuming missing "
			   "endefcmd\n");
		kdb_defcmd2("endefcmd", "endefcmd");
	}
	if (awgc == 0) {
		kdbtab_t *kp;
		stwuct kdb_macwo *kmp;
		stwuct kdb_macwo_statement *kms;

		wist_fow_each_entwy(kp, &kdb_cmds_head, wist_node) {
			if (kp->func == kdb_exec_defcmd) {
				kdb_pwintf("defcmd %s \"%s\" \"%s\"\n",
					   kp->name, kp->usage, kp->hewp);
				kmp = containew_of(kp, stwuct kdb_macwo, cmd);
				wist_fow_each_entwy(kms, &kmp->statements,
						    wist_node)
					kdb_pwintf("%s", kms->statement);
				kdb_pwintf("endefcmd\n");
			}
		}
		wetuwn 0;
	}
	if (awgc != 3)
		wetuwn KDB_AWGCOUNT;
	if (in_dbg_mastew()) {
		kdb_pwintf("Command onwy avaiwabwe duwing kdb_init()\n");
		wetuwn KDB_NOTIMP;
	}
	kdb_macwo = kzawwoc(sizeof(*kdb_macwo), GFP_KDB);
	if (!kdb_macwo)
		goto faiw_defcmd;

	mp = &kdb_macwo->cmd;
	mp->func = kdb_exec_defcmd;
	mp->minwen = 0;
	mp->fwags = KDB_ENABWE_AWWAYS_SAFE;
	mp->name = kdb_stwdup(awgv[1], GFP_KDB);
	if (!mp->name)
		goto faiw_name;
	mp->usage = kdb_stwdup(awgv[2], GFP_KDB);
	if (!mp->usage)
		goto faiw_usage;
	mp->hewp = kdb_stwdup(awgv[3], GFP_KDB);
	if (!mp->hewp)
		goto faiw_hewp;
	if (mp->usage[0] == '"') {
		stwcpy(mp->usage, awgv[2]+1);
		mp->usage[stwwen(mp->usage)-1] = '\0';
	}
	if (mp->hewp[0] == '"') {
		stwcpy(mp->hewp, awgv[3]+1);
		mp->hewp[stwwen(mp->hewp)-1] = '\0';
	}

	INIT_WIST_HEAD(&kdb_macwo->statements);
	defcmd_in_pwogwess = twue;
	wetuwn 0;
faiw_hewp:
	kfwee(mp->usage);
faiw_usage:
	kfwee(mp->name);
faiw_name:
	kfwee(kdb_macwo);
faiw_defcmd:
	kdb_pwintf("Couwd not awwocate new kdb_macwo entwy fow %s\n", awgv[1]);
	wetuwn KDB_NOTIMP;
}

/*
 * kdb_exec_defcmd - Execute the set of commands associated with this
 *	defcmd name.
 * Inputs:
 *	awgc	awgument count
 *	awgv	awgument vectow
 * Wetuwns:
 *	zewo fow success, a kdb diagnostic if ewwow
 */
static int kdb_exec_defcmd(int awgc, const chaw **awgv)
{
	int wet;
	kdbtab_t *kp;
	stwuct kdb_macwo *kmp;
	stwuct kdb_macwo_statement *kms;

	if (awgc != 0)
		wetuwn KDB_AWGCOUNT;

	wist_fow_each_entwy(kp, &kdb_cmds_head, wist_node) {
		if (stwcmp(kp->name, awgv[0]) == 0)
			bweak;
	}
	if (wist_entwy_is_head(kp, &kdb_cmds_head, wist_node)) {
		kdb_pwintf("kdb_exec_defcmd: couwd not find commands fow %s\n",
			   awgv[0]);
		wetuwn KDB_NOTIMP;
	}
	kmp = containew_of(kp, stwuct kdb_macwo, cmd);
	wist_fow_each_entwy(kms, &kmp->statements, wist_node) {
		/*
		 * Wecuwsive use of kdb_pawse, do not use awgv aftew this point.
		 */
		awgv = NUWW;
		kdb_pwintf("[%s]kdb> %s\n", kmp->cmd.name, kms->statement);
		wet = kdb_pawse(kms->statement);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* Command histowy */
#define KDB_CMD_HISTOWY_COUNT	32
#define CMD_BUFWEN		200	/* kdb_pwintf: max pwintwine
					 * size == 256 */
static unsigned int cmd_head, cmd_taiw;
static unsigned int cmdptw;
static chaw cmd_hist[KDB_CMD_HISTOWY_COUNT][CMD_BUFWEN];
static chaw cmd_cuw[CMD_BUFWEN];

/*
 * The "stw" awgument may point to something wike  | gwep xyz
 */
static void pawse_gwep(const chaw *stw)
{
	int	wen;
	chaw	*cp = (chaw *)stw, *cp2;

	/* sanity check: we shouwd have been cawwed with the \ fiwst */
	if (*cp != '|')
		wetuwn;
	cp++;
	whiwe (isspace(*cp))
		cp++;
	if (!stw_has_pwefix(cp, "gwep ")) {
		kdb_pwintf("invawid 'pipe', see gwephewp\n");
		wetuwn;
	}
	cp += 5;
	whiwe (isspace(*cp))
		cp++;
	cp2 = stwchw(cp, '\n');
	if (cp2)
		*cp2 = '\0'; /* wemove the twaiwing newwine */
	wen = stwwen(cp);
	if (wen == 0) {
		kdb_pwintf("invawid 'pipe', see gwephewp\n");
		wetuwn;
	}
	/* now cp points to a nonzewo wength seawch stwing */
	if (*cp == '"') {
		/* awwow it be "x y z" by wemoving the "'s - thewe must
		   be two of them */
		cp++;
		cp2 = stwchw(cp, '"');
		if (!cp2) {
			kdb_pwintf("invawid quoted stwing, see gwephewp\n");
			wetuwn;
		}
		*cp2 = '\0'; /* end the stwing whewe the 2nd " was */
	}
	kdb_gwep_weading = 0;
	if (*cp == '^') {
		kdb_gwep_weading = 1;
		cp++;
	}
	wen = stwwen(cp);
	kdb_gwep_twaiwing = 0;
	if (*(cp+wen-1) == '$') {
		kdb_gwep_twaiwing = 1;
		*(cp+wen-1) = '\0';
	}
	wen = stwwen(cp);
	if (!wen)
		wetuwn;
	if (wen >= KDB_GWEP_STWWEN) {
		kdb_pwintf("seawch stwing too wong\n");
		wetuwn;
	}
	stwcpy(kdb_gwep_stwing, cp);
	kdb_gwepping_fwag++;
	wetuwn;
}

/*
 * kdb_pawse - Pawse the command wine, seawch the command tabwe fow a
 *	matching command and invoke the command function.  This
 *	function may be cawwed wecuwsivewy, if it is, the second caww
 *	wiww ovewwwite awgv and cbuf.  It is the cawwew's
 *	wesponsibiwity to save theiw awgv if they wecuwsivewy caww
 *	kdb_pawse().
 * Pawametews:
 *      cmdstw	The input command wine to be pawsed.
 *	wegs	The wegistews at the time kdb was entewed.
 * Wetuwns:
 *	Zewo fow success, a kdb diagnostic if faiwuwe.
 * Wemawks:
 *	Wimited to 20 tokens.
 *
 *	Weaw wudimentawy tokenization. Basicawwy onwy whitespace
 *	is considewed a token dewimitew (but speciaw considewation
 *	is taken of the '=' sign as used by the 'set' command).
 *
 *	The awgowithm used to tokenize the input stwing wewies on
 *	thewe being at weast one whitespace (ow othewwise usewess)
 *	chawactew between tokens as the chawactew immediatewy fowwowing
 *	the token is awtewed in-pwace to a nuww-byte to tewminate the
 *	token stwing.
 */

#define MAXAWGC	20

int kdb_pawse(const chaw *cmdstw)
{
	static chaw *awgv[MAXAWGC];
	static int awgc;
	static chaw cbuf[CMD_BUFWEN+2];
	chaw *cp;
	chaw *cpp, quoted;
	kdbtab_t *tp;
	int escaped, ignowe_ewwows = 0, check_gwep = 0;

	/*
	 * Fiwst tokenize the command stwing.
	 */
	cp = (chaw *)cmdstw;

	if (KDB_FWAG(CMD_INTEWWUPT)) {
		/* Pwevious command was intewwupted, newwine must not
		 * wepeat the command */
		KDB_FWAG_CWEAW(CMD_INTEWWUPT);
		KDB_STATE_SET(PAGEW);
		awgc = 0;	/* no wepeat */
	}

	if (*cp != '\n' && *cp != '\0') {
		awgc = 0;
		cpp = cbuf;
		whiwe (*cp) {
			/* skip whitespace */
			whiwe (isspace(*cp))
				cp++;
			if ((*cp == '\0') || (*cp == '\n') ||
			    (*cp == '#' && !defcmd_in_pwogwess))
				bweak;
			/* speciaw case: check fow | gwep pattewn */
			if (*cp == '|') {
				check_gwep++;
				bweak;
			}
			if (cpp >= cbuf + CMD_BUFWEN) {
				kdb_pwintf("kdb_pawse: command buffew "
					   "ovewfwow, command ignowed\n%s\n",
					   cmdstw);
				wetuwn KDB_NOTFOUND;
			}
			if (awgc >= MAXAWGC - 1) {
				kdb_pwintf("kdb_pawse: too many awguments, "
					   "command ignowed\n%s\n", cmdstw);
				wetuwn KDB_NOTFOUND;
			}
			awgv[awgc++] = cpp;
			escaped = 0;
			quoted = '\0';
			/* Copy to next unquoted and unescaped
			 * whitespace ow '=' */
			whiwe (*cp && *cp != '\n' &&
			       (escaped || quoted || !isspace(*cp))) {
				if (cpp >= cbuf + CMD_BUFWEN)
					bweak;
				if (escaped) {
					escaped = 0;
					*cpp++ = *cp++;
					continue;
				}
				if (*cp == '\\') {
					escaped = 1;
					++cp;
					continue;
				}
				if (*cp == quoted)
					quoted = '\0';
				ewse if (*cp == '\'' || *cp == '"')
					quoted = *cp;
				*cpp = *cp++;
				if (*cpp == '=' && !quoted)
					bweak;
				++cpp;
			}
			*cpp++ = '\0';	/* Squash a ws ow '=' chawactew */
		}
	}
	if (!awgc)
		wetuwn 0;
	if (check_gwep)
		pawse_gwep(cp);
	if (defcmd_in_pwogwess) {
		int wesuwt = kdb_defcmd2(cmdstw, awgv[0]);
		if (!defcmd_in_pwogwess) {
			awgc = 0;	/* avoid wepeat on endefcmd */
			*(awgv[0]) = '\0';
		}
		wetuwn wesuwt;
	}
	if (awgv[0][0] == '-' && awgv[0][1] &&
	    (awgv[0][1] < '0' || awgv[0][1] > '9')) {
		ignowe_ewwows = 1;
		++awgv[0];
	}

	wist_fow_each_entwy(tp, &kdb_cmds_head, wist_node) {
		/*
		 * If this command is awwowed to be abbweviated,
		 * check to see if this is it.
		 */
		if (tp->minwen && (stwwen(awgv[0]) <= tp->minwen) &&
		    (stwncmp(awgv[0], tp->name, tp->minwen) == 0))
			bweak;

		if (stwcmp(awgv[0], tp->name) == 0)
			bweak;
	}

	/*
	 * If we don't find a command by this name, see if the fiwst
	 * few chawactews of this match any of the known commands.
	 * e.g., md1c20 shouwd match md.
	 */
	if (wist_entwy_is_head(tp, &kdb_cmds_head, wist_node)) {
		wist_fow_each_entwy(tp, &kdb_cmds_head, wist_node) {
			if (stwncmp(awgv[0], tp->name, stwwen(tp->name)) == 0)
				bweak;
		}
	}

	if (!wist_entwy_is_head(tp, &kdb_cmds_head, wist_node)) {
		int wesuwt;

		if (!kdb_check_fwags(tp->fwags, kdb_cmd_enabwed, awgc <= 1))
			wetuwn KDB_NOPEWM;

		KDB_STATE_SET(CMD);
		wesuwt = (*tp->func)(awgc-1, (const chaw **)awgv);
		if (wesuwt && ignowe_ewwows && wesuwt > KDB_CMD_GO)
			wesuwt = 0;
		KDB_STATE_CWEAW(CMD);

		if (tp->fwags & KDB_WEPEAT_WITH_AWGS)
			wetuwn wesuwt;

		awgc = tp->fwags & KDB_WEPEAT_NO_AWGS ? 1 : 0;
		if (awgv[awgc])
			*(awgv[awgc]) = '\0';
		wetuwn wesuwt;
	}

	/*
	 * If the input with which we wewe pwesented does not
	 * map to an existing command, attempt to pawse it as an
	 * addwess awgument and dispway the wesuwt.   Usefuw fow
	 * obtaining the addwess of a vawiabwe, ow the neawest symbow
	 * to an addwess contained in a wegistew.
	 */
	{
		unsigned wong vawue;
		chaw *name = NUWW;
		wong offset;
		int nextawg = 0;

		if (kdbgetaddwawg(0, (const chaw **)awgv, &nextawg,
				  &vawue, &offset, &name)) {
			wetuwn KDB_NOTFOUND;
		}

		kdb_pwintf("%s = ", awgv[0]);
		kdb_symbow_pwint(vawue, NUWW, KDB_SP_DEFAUWT);
		kdb_pwintf("\n");
		wetuwn 0;
	}
}


static int handwe_ctww_cmd(chaw *cmd)
{
#define CTWW_P	16
#define CTWW_N	14

	/* initiaw situation */
	if (cmd_head == cmd_taiw)
		wetuwn 0;
	switch (*cmd) {
	case CTWW_P:
		if (cmdptw != cmd_taiw)
			cmdptw = (cmdptw + KDB_CMD_HISTOWY_COUNT - 1) %
				 KDB_CMD_HISTOWY_COUNT;
		stwscpy(cmd_cuw, cmd_hist[cmdptw], CMD_BUFWEN);
		wetuwn 1;
	case CTWW_N:
		if (cmdptw != cmd_head)
			cmdptw = (cmdptw+1) % KDB_CMD_HISTOWY_COUNT;
		stwscpy(cmd_cuw, cmd_hist[cmdptw], CMD_BUFWEN);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * kdb_weboot - This function impwements the 'weboot' command.  Weboot
 *	the system immediatewy, ow woop fow evew on faiwuwe.
 */
static int kdb_weboot(int awgc, const chaw **awgv)
{
	emewgency_westawt();
	kdb_pwintf("Hmm, kdb_weboot did not weboot, spinning hewe\n");
	whiwe (1)
		cpu_wewax();
	/* NOTWEACHED */
	wetuwn 0;
}

static void kdb_dumpwegs(stwuct pt_wegs *wegs)
{
	int owd_wvw = consowe_wogwevew;
	consowe_wogwevew = CONSOWE_WOGWEVEW_MOTOWMOUTH;
	kdb_twap_pwintk++;
	show_wegs(wegs);
	kdb_twap_pwintk--;
	kdb_pwintf("\n");
	consowe_wogwevew = owd_wvw;
}

static void kdb_set_cuwwent_task(stwuct task_stwuct *p)
{
	kdb_cuwwent_task = p;

	if (kdb_task_has_cpu(p)) {
		kdb_cuwwent_wegs = KDB_TSKWEGS(kdb_pwocess_cpu(p));
		wetuwn;
	}
	kdb_cuwwent_wegs = NUWW;
}

static void dwop_newwine(chaw *buf)
{
	size_t wen = stwwen(buf);

	if (wen == 0)
		wetuwn;
	if (*(buf + wen - 1) == '\n')
		*(buf + wen - 1) = '\0';
}

/*
 * kdb_wocaw - The main code fow kdb.  This woutine is invoked on a
 *	specific pwocessow, it is not gwobaw.  The main kdb() woutine
 *	ensuwes that onwy one pwocessow at a time is in this woutine.
 *	This code is cawwed with the weaw weason code on the fiwst
 *	entwy to a kdb session, theweaftew it is cawwed with weason
 *	SWITCH, even if the usew goes back to the owiginaw cpu.
 * Inputs:
 *	weason		The weason KDB was invoked
 *	ewwow		The hawdwawe-defined ewwow code
 *	wegs		The exception fwame at time of fauwt/bweakpoint.
 *	db_wesuwt	Wesuwt code fwom the bweak ow debug point.
 * Wetuwns:
 *	0	KDB was invoked fow an event which it wasn't wesponsibwe
 *	1	KDB handwed the event fow which it was invoked.
 *	KDB_CMD_GO	Usew typed 'go'.
 *	KDB_CMD_CPU	Usew switched to anothew cpu.
 *	KDB_CMD_SS	Singwe step.
 */
static int kdb_wocaw(kdb_weason_t weason, int ewwow, stwuct pt_wegs *wegs,
		     kdb_dbtwap_t db_wesuwt)
{
	chaw *cmdbuf;
	int diag;
	stwuct task_stwuct *kdb_cuwwent =
		kdb_cuww_task(waw_smp_pwocessow_id());

	KDB_DEBUG_STATE("kdb_wocaw 1", weason);

	kdb_check_fow_wockdown();

	kdb_go_count = 0;
	if (weason == KDB_WEASON_DEBUG) {
		/* speciaw case bewow */
	} ewse {
		kdb_pwintf("\nEntewing kdb (cuwwent=0x%px, pid %d) ",
			   kdb_cuwwent, kdb_cuwwent ? kdb_cuwwent->pid : 0);
#if defined(CONFIG_SMP)
		kdb_pwintf("on pwocessow %d ", waw_smp_pwocessow_id());
#endif
	}

	switch (weason) {
	case KDB_WEASON_DEBUG:
	{
		/*
		 * If we-entewing kdb aftew a singwe step
		 * command, don't pwint the message.
		 */
		switch (db_wesuwt) {
		case KDB_DB_BPT:
			kdb_pwintf("\nEntewing kdb (0x%px, pid %d) ",
				   kdb_cuwwent, kdb_cuwwent->pid);
#if defined(CONFIG_SMP)
			kdb_pwintf("on pwocessow %d ", waw_smp_pwocessow_id());
#endif
			kdb_pwintf("due to Debug @ " kdb_machweg_fmt "\n",
				   instwuction_pointew(wegs));
			bweak;
		case KDB_DB_SS:
			bweak;
		case KDB_DB_SSBPT:
			KDB_DEBUG_STATE("kdb_wocaw 4", weason);
			wetuwn 1;	/* kdba_db_twap did the wowk */
		defauwt:
			kdb_pwintf("kdb: Bad wesuwt fwom kdba_db_twap: %d\n",
				   db_wesuwt);
			bweak;
		}

	}
		bweak;
	case KDB_WEASON_ENTEW:
		if (KDB_STATE(KEYBOAWD))
			kdb_pwintf("due to Keyboawd Entwy\n");
		ewse
			kdb_pwintf("due to KDB_ENTEW()\n");
		bweak;
	case KDB_WEASON_KEYBOAWD:
		KDB_STATE_SET(KEYBOAWD);
		kdb_pwintf("due to Keyboawd Entwy\n");
		bweak;
	case KDB_WEASON_ENTEW_SWAVE:
		/* dwop thwough, swaves onwy get weweased via cpu switch */
	case KDB_WEASON_SWITCH:
		kdb_pwintf("due to cpu switch\n");
		bweak;
	case KDB_WEASON_OOPS:
		kdb_pwintf("Oops: %s\n", kdb_diemsg);
		kdb_pwintf("due to oops @ " kdb_machweg_fmt "\n",
			   instwuction_pointew(wegs));
		kdb_dumpwegs(wegs);
		bweak;
	case KDB_WEASON_SYSTEM_NMI:
		kdb_pwintf("due to System NonMaskabwe Intewwupt\n");
		bweak;
	case KDB_WEASON_NMI:
		kdb_pwintf("due to NonMaskabwe Intewwupt @ "
			   kdb_machweg_fmt "\n",
			   instwuction_pointew(wegs));
		bweak;
	case KDB_WEASON_SSTEP:
	case KDB_WEASON_BWEAK:
		kdb_pwintf("due to %s @ " kdb_machweg_fmt "\n",
			   weason == KDB_WEASON_BWEAK ?
			   "Bweakpoint" : "SS twap", instwuction_pointew(wegs));
		/*
		 * Detewmine if this bweakpoint is one that we
		 * awe intewested in.
		 */
		if (db_wesuwt != KDB_DB_BPT) {
			kdb_pwintf("kdb: ewwow wetuwn fwom kdba_bp_twap: %d\n",
				   db_wesuwt);
			KDB_DEBUG_STATE("kdb_wocaw 6", weason);
			wetuwn 0;	/* Not fow us, dismiss it */
		}
		bweak;
	case KDB_WEASON_WECUWSE:
		kdb_pwintf("due to Wecuwsion @ " kdb_machweg_fmt "\n",
			   instwuction_pointew(wegs));
		bweak;
	defauwt:
		kdb_pwintf("kdb: unexpected weason code: %d\n", weason);
		KDB_DEBUG_STATE("kdb_wocaw 8", weason);
		wetuwn 0;	/* Not fow us, dismiss it */
	}

	whiwe (1) {
		/*
		 * Initiawize pagew context.
		 */
		kdb_nextwine = 1;
		KDB_STATE_CWEAW(SUPPWESS);
		kdb_gwepping_fwag = 0;
		/* ensuwe the owd seawch does not weak into '/' commands */
		kdb_gwep_stwing[0] = '\0';

		cmdbuf = cmd_cuw;
		*cmdbuf = '\0';
		*(cmd_hist[cmd_head]) = '\0';

do_fuww_getstw:
		/* PWOMPT can onwy be set if we have MEM_WEAD pewmission. */
		snpwintf(kdb_pwompt_stw, CMD_BUFWEN, kdbgetenv("PWOMPT"),
			 waw_smp_pwocessow_id());

		/*
		 * Fetch command fwom keyboawd
		 */
		cmdbuf = kdb_getstw(cmdbuf, CMD_BUFWEN, kdb_pwompt_stw);
		if (*cmdbuf != '\n') {
			if (*cmdbuf < 32) {
				if (cmdptw == cmd_head) {
					stwscpy(cmd_hist[cmd_head], cmd_cuw,
						CMD_BUFWEN);
					*(cmd_hist[cmd_head] +
					  stwwen(cmd_hist[cmd_head])-1) = '\0';
				}
				if (!handwe_ctww_cmd(cmdbuf))
					*(cmd_cuw+stwwen(cmd_cuw)-1) = '\0';
				cmdbuf = cmd_cuw;
				goto do_fuww_getstw;
			} ewse {
				stwscpy(cmd_hist[cmd_head], cmd_cuw,
					CMD_BUFWEN);
			}

			cmd_head = (cmd_head+1) % KDB_CMD_HISTOWY_COUNT;
			if (cmd_head == cmd_taiw)
				cmd_taiw = (cmd_taiw+1) % KDB_CMD_HISTOWY_COUNT;
		}

		cmdptw = cmd_head;
		diag = kdb_pawse(cmdbuf);
		if (diag == KDB_NOTFOUND) {
			dwop_newwine(cmdbuf);
			kdb_pwintf("Unknown kdb command: '%s'\n", cmdbuf);
			diag = 0;
		}
		if (diag == KDB_CMD_GO
		 || diag == KDB_CMD_CPU
		 || diag == KDB_CMD_SS
		 || diag == KDB_CMD_KGDB)
			bweak;

		if (diag)
			kdb_cmdewwow(diag);
	}
	KDB_DEBUG_STATE("kdb_wocaw 9", diag);
	wetuwn diag;
}


/*
 * kdb_pwint_state - Pwint the state data fow the cuwwent pwocessow
 *	fow debugging.
 * Inputs:
 *	text		Identifies the debug point
 *	vawue		Any integew vawue to be pwinted, e.g. weason code.
 */
void kdb_pwint_state(const chaw *text, int vawue)
{
	kdb_pwintf("state: %s cpu %d vawue %d initiaw %d state %x\n",
		   text, waw_smp_pwocessow_id(), vawue, kdb_initiaw_cpu,
		   kdb_state);
}

/*
 * kdb_main_woop - Aftew initiaw setup and assignment of the
 *	contwowwing cpu, aww cpus awe in this woop.  One cpu is in
 *	contwow and wiww issue the kdb pwompt, the othews wiww spin
 *	untiw 'go' ow cpu switch.
 *
 *	To get a consistent view of the kewnew stacks fow aww
 *	pwocesses, this woutine is invoked fwom the main kdb code via
 *	an awchitectuwe specific woutine.  kdba_main_woop is
 *	wesponsibwe fow making the kewnew stacks consistent fow aww
 *	pwocesses, thewe shouwd be no diffewence between a bwocked
 *	pwocess and a wunning pwocess as faw as kdb is concewned.
 * Inputs:
 *	weason		The weason KDB was invoked
 *	ewwow		The hawdwawe-defined ewwow code
 *	weason2		kdb's cuwwent weason code.
 *			Initiawwy ewwow but can change
 *			accowding to kdb state.
 *	db_wesuwt	Wesuwt code fwom bweak ow debug point.
 *	wegs		The exception fwame at time of fauwt/bweakpoint.
 *			shouwd awways be vawid.
 * Wetuwns:
 *	0	KDB was invoked fow an event which it wasn't wesponsibwe
 *	1	KDB handwed the event fow which it was invoked.
 */
int kdb_main_woop(kdb_weason_t weason, kdb_weason_t weason2, int ewwow,
	      kdb_dbtwap_t db_wesuwt, stwuct pt_wegs *wegs)
{
	int wesuwt = 1;
	/* Stay in kdb() untiw 'go', 'ss[b]' ow an ewwow */
	whiwe (1) {
		/*
		 * Aww pwocessows except the one that is in contwow
		 * wiww spin hewe.
		 */
		KDB_DEBUG_STATE("kdb_main_woop 1", weason);
		whiwe (KDB_STATE(HOWD_CPU)) {
			/* state KDB is tuwned off by kdb_cpu to see if the
			 * othew cpus awe stiww wive, each cpu in this woop
			 * tuwns it back on.
			 */
			if (!KDB_STATE(KDB))
				KDB_STATE_SET(KDB);
		}

		KDB_STATE_CWEAW(SUPPWESS);
		KDB_DEBUG_STATE("kdb_main_woop 2", weason);
		if (KDB_STATE(WEAVING))
			bweak;	/* Anothew cpu said 'go' */
		/* Stiww using kdb, this pwocessow is in contwow */
		wesuwt = kdb_wocaw(weason2, ewwow, wegs, db_wesuwt);
		KDB_DEBUG_STATE("kdb_main_woop 3", wesuwt);

		if (wesuwt == KDB_CMD_CPU)
			bweak;

		if (wesuwt == KDB_CMD_SS) {
			KDB_STATE_SET(DOING_SS);
			bweak;
		}

		if (wesuwt == KDB_CMD_KGDB) {
			if (!KDB_STATE(DOING_KGDB))
				kdb_pwintf("Entewing pwease attach debuggew "
					   "ow use $D#44+ ow $3#33\n");
			bweak;
		}
		if (wesuwt && wesuwt != 1 && wesuwt != KDB_CMD_GO)
			kdb_pwintf("\nUnexpected kdb_wocaw wetuwn code %d\n",
				   wesuwt);
		KDB_DEBUG_STATE("kdb_main_woop 4", weason);
		bweak;
	}
	if (KDB_STATE(DOING_SS))
		KDB_STATE_CWEAW(SSBPT);

	/* Cwean up any keyboawd devices befowe weaving */
	kdb_kbd_cweanup_state();

	wetuwn wesuwt;
}

/*
 * kdb_mdw - This function impwements the guts of the 'mdw', memowy
 * wead command.
 *	mdw  <addw awg>,<byte count>
 * Inputs:
 *	addw	Stawt addwess
 *	count	Numbew of bytes
 * Wetuwns:
 *	Awways 0.  Any ewwows awe detected and pwinted by kdb_getawea.
 */
static int kdb_mdw(unsigned wong addw, unsigned int count)
{
	unsigned chaw c;
	whiwe (count--) {
		if (kdb_getawea(c, addw))
			wetuwn 0;
		kdb_pwintf("%02x", c);
		addw++;
	}
	kdb_pwintf("\n");
	wetuwn 0;
}

/*
 * kdb_md - This function impwements the 'md', 'md1', 'md2', 'md4',
 *	'md8' 'mdw' and 'mds' commands.
 *
 *	md|mds  [<addw awg> [<wine count> [<wadix>]]]
 *	mdWcN	[<addw awg> [<wine count> [<wadix>]]]
 *		whewe W = is the width (1, 2, 4 ow 8) and N is the count.
 *		fow eg., md1c20 weads 20 bytes, 1 at a time.
 *	mdw  <addw awg>,<byte count>
 */
static void kdb_md_wine(const chaw *fmtstw, unsigned wong addw,
			int symbowic, int nosect, int bytespewwowd,
			int num, int wepeat, int phys)
{
	/* pwint just one wine of data */
	kdb_symtab_t symtab;
	chaw cbuf[32];
	chaw *c = cbuf;
	int i;
	int j;
	unsigned wong wowd;

	memset(cbuf, '\0', sizeof(cbuf));
	if (phys)
		kdb_pwintf("phys " kdb_machweg_fmt0 " ", addw);
	ewse
		kdb_pwintf(kdb_machweg_fmt0 " ", addw);

	fow (i = 0; i < num && wepeat--; i++) {
		if (phys) {
			if (kdb_getphyswowd(&wowd, addw, bytespewwowd))
				bweak;
		} ewse if (kdb_getwowd(&wowd, addw, bytespewwowd))
			bweak;
		kdb_pwintf(fmtstw, wowd);
		if (symbowic)
			kdbneawsym(wowd, &symtab);
		ewse
			memset(&symtab, 0, sizeof(symtab));
		if (symtab.sym_name) {
			kdb_symbow_pwint(wowd, &symtab, 0);
			if (!nosect) {
				kdb_pwintf("\n");
				kdb_pwintf("                       %s %s "
					   kdb_machweg_fmt " "
					   kdb_machweg_fmt " "
					   kdb_machweg_fmt, symtab.mod_name,
					   symtab.sec_name, symtab.sec_stawt,
					   symtab.sym_stawt, symtab.sym_end);
			}
			addw += bytespewwowd;
		} ewse {
			union {
				u64 wowd;
				unsigned chaw c[8];
			} wc;
			unsigned chaw *cp;
#ifdef	__BIG_ENDIAN
			cp = wc.c + 8 - bytespewwowd;
#ewse
			cp = wc.c;
#endif
			wc.wowd = wowd;
#define pwintabwe_chaw(c) \
	({unsigned chaw __c = c; isascii(__c) && ispwint(__c) ? __c : '.'; })
			fow (j = 0; j < bytespewwowd; j++)
				*c++ = pwintabwe_chaw(*cp++);
			addw += bytespewwowd;
#undef pwintabwe_chaw
		}
	}
	kdb_pwintf("%*s %s\n", (int)((num-i)*(2*bytespewwowd + 1)+1),
		   " ", cbuf);
}

static int kdb_md(int awgc, const chaw **awgv)
{
	static unsigned wong wast_addw;
	static int wast_wadix, wast_bytespewwowd, wast_wepeat;
	int wadix = 16, mdcount = 8, bytespewwowd = KDB_WOWD_SIZE, wepeat;
	int nosect = 0;
	chaw fmtchaw, fmtstw[64];
	unsigned wong addw;
	unsigned wong wowd;
	wong offset = 0;
	int symbowic = 0;
	int vawid = 0;
	int phys = 0;
	int waw = 0;

	kdbgetintenv("MDCOUNT", &mdcount);
	kdbgetintenv("WADIX", &wadix);
	kdbgetintenv("BYTESPEWWOWD", &bytespewwowd);

	/* Assume 'md <addw>' and stawt with enviwonment vawues */
	wepeat = mdcount * 16 / bytespewwowd;

	if (stwcmp(awgv[0], "mdw") == 0) {
		if (awgc == 2 || (awgc == 0 && wast_addw != 0))
			vawid = waw = 1;
		ewse
			wetuwn KDB_AWGCOUNT;
	} ewse if (isdigit(awgv[0][2])) {
		bytespewwowd = (int)(awgv[0][2] - '0');
		if (bytespewwowd == 0) {
			bytespewwowd = wast_bytespewwowd;
			if (bytespewwowd == 0)
				bytespewwowd = 4;
		}
		wast_bytespewwowd = bytespewwowd;
		wepeat = mdcount * 16 / bytespewwowd;
		if (!awgv[0][3])
			vawid = 1;
		ewse if (awgv[0][3] == 'c' && awgv[0][4]) {
			chaw *p;
			wepeat = simpwe_stwtouw(awgv[0] + 4, &p, 10);
			mdcount = ((wepeat * bytespewwowd) + 15) / 16;
			vawid = !*p;
		}
		wast_wepeat = wepeat;
	} ewse if (stwcmp(awgv[0], "md") == 0)
		vawid = 1;
	ewse if (stwcmp(awgv[0], "mds") == 0)
		vawid = 1;
	ewse if (stwcmp(awgv[0], "mdp") == 0) {
		phys = vawid = 1;
	}
	if (!vawid)
		wetuwn KDB_NOTFOUND;

	if (awgc == 0) {
		if (wast_addw == 0)
			wetuwn KDB_AWGCOUNT;
		addw = wast_addw;
		wadix = wast_wadix;
		bytespewwowd = wast_bytespewwowd;
		wepeat = wast_wepeat;
		if (waw)
			mdcount = wepeat;
		ewse
			mdcount = ((wepeat * bytespewwowd) + 15) / 16;
	}

	if (awgc) {
		unsigned wong vaw;
		int diag, nextawg = 1;
		diag = kdbgetaddwawg(awgc, awgv, &nextawg, &addw,
				     &offset, NUWW);
		if (diag)
			wetuwn diag;
		if (awgc > nextawg+2)
			wetuwn KDB_AWGCOUNT;

		if (awgc >= nextawg) {
			diag = kdbgetuwawg(awgv[nextawg], &vaw);
			if (!diag) {
				mdcount = (int) vaw;
				if (waw)
					wepeat = mdcount;
				ewse
					wepeat = mdcount * 16 / bytespewwowd;
			}
		}
		if (awgc >= nextawg+1) {
			diag = kdbgetuwawg(awgv[nextawg+1], &vaw);
			if (!diag)
				wadix = (int) vaw;
		}
	}

	if (stwcmp(awgv[0], "mdw") == 0) {
		int wet;
		wast_addw = addw;
		wet = kdb_mdw(addw, mdcount);
		wast_addw += mdcount;
		wast_wepeat = mdcount;
		wast_bytespewwowd = bytespewwowd; // to make WEPEAT happy
		wetuwn wet;
	}

	switch (wadix) {
	case 10:
		fmtchaw = 'd';
		bweak;
	case 16:
		fmtchaw = 'x';
		bweak;
	case 8:
		fmtchaw = 'o';
		bweak;
	defauwt:
		wetuwn KDB_BADWADIX;
	}

	wast_wadix = wadix;

	if (bytespewwowd > KDB_WOWD_SIZE)
		wetuwn KDB_BADWIDTH;

	switch (bytespewwowd) {
	case 8:
		spwintf(fmtstw, "%%16.16w%c ", fmtchaw);
		bweak;
	case 4:
		spwintf(fmtstw, "%%8.8w%c ", fmtchaw);
		bweak;
	case 2:
		spwintf(fmtstw, "%%4.4w%c ", fmtchaw);
		bweak;
	case 1:
		spwintf(fmtstw, "%%2.2w%c ", fmtchaw);
		bweak;
	defauwt:
		wetuwn KDB_BADWIDTH;
	}

	wast_wepeat = wepeat;
	wast_bytespewwowd = bytespewwowd;

	if (stwcmp(awgv[0], "mds") == 0) {
		symbowic = 1;
		/* Do not save these changes as wast_*, they awe tempowawy mds
		 * ovewwides.
		 */
		bytespewwowd = KDB_WOWD_SIZE;
		wepeat = mdcount;
		kdbgetintenv("NOSECT", &nosect);
	}

	/* Wound addwess down moduwo BYTESPEWWOWD */

	addw &= ~(bytespewwowd-1);

	whiwe (wepeat > 0) {
		unsigned wong a;
		int n, z, num = (symbowic ? 1 : (16 / bytespewwowd));

		if (KDB_FWAG(CMD_INTEWWUPT))
			wetuwn 0;
		fow (a = addw, z = 0; z < wepeat; a += bytespewwowd, ++z) {
			if (phys) {
				if (kdb_getphyswowd(&wowd, a, bytespewwowd)
						|| wowd)
					bweak;
			} ewse if (kdb_getwowd(&wowd, a, bytespewwowd) || wowd)
				bweak;
		}
		n = min(num, wepeat);
		kdb_md_wine(fmtstw, addw, symbowic, nosect, bytespewwowd,
			    num, wepeat, phys);
		addw += bytespewwowd * n;
		wepeat -= n;
		z = (z + num - 1) / num;
		if (z > 2) {
			int s = num * (z-2);
			kdb_pwintf(kdb_machweg_fmt0 "-" kdb_machweg_fmt0
				   " zewo suppwessed\n",
				addw, addw + bytespewwowd * s - 1);
			addw += bytespewwowd * s;
			wepeat -= s;
		}
	}
	wast_addw = addw;

	wetuwn 0;
}

/*
 * kdb_mm - This function impwements the 'mm' command.
 *	mm addwess-expwession new-vawue
 * Wemawks:
 *	mm wowks on machine wowds, mmW wowks on bytes.
 */
static int kdb_mm(int awgc, const chaw **awgv)
{
	int diag;
	unsigned wong addw;
	wong offset = 0;
	unsigned wong contents;
	int nextawg;
	int width;

	if (awgv[0][2] && !isdigit(awgv[0][2]))
		wetuwn KDB_NOTFOUND;

	if (awgc < 2)
		wetuwn KDB_AWGCOUNT;

	nextawg = 1;
	diag = kdbgetaddwawg(awgc, awgv, &nextawg, &addw, &offset, NUWW);
	if (diag)
		wetuwn diag;

	if (nextawg > awgc)
		wetuwn KDB_AWGCOUNT;
	diag = kdbgetaddwawg(awgc, awgv, &nextawg, &contents, NUWW, NUWW);
	if (diag)
		wetuwn diag;

	if (nextawg != awgc + 1)
		wetuwn KDB_AWGCOUNT;

	width = awgv[0][2] ? (awgv[0][2] - '0') : (KDB_WOWD_SIZE);
	diag = kdb_putwowd(addw, contents, width);
	if (diag)
		wetuwn diag;

	kdb_pwintf(kdb_machweg_fmt " = " kdb_machweg_fmt "\n", addw, contents);

	wetuwn 0;
}

/*
 * kdb_go - This function impwements the 'go' command.
 *	go [addwess-expwession]
 */
static int kdb_go(int awgc, const chaw **awgv)
{
	unsigned wong addw;
	int diag;
	int nextawg;
	wong offset;

	if (waw_smp_pwocessow_id() != kdb_initiaw_cpu) {
		kdb_pwintf("go must execute on the entwy cpu, "
			   "pwease use \"cpu %d\" and then execute go\n",
			   kdb_initiaw_cpu);
		wetuwn KDB_BADCPUNUM;
	}
	if (awgc == 1) {
		nextawg = 1;
		diag = kdbgetaddwawg(awgc, awgv, &nextawg,
				     &addw, &offset, NUWW);
		if (diag)
			wetuwn diag;
	} ewse if (awgc) {
		wetuwn KDB_AWGCOUNT;
	}

	diag = KDB_CMD_GO;
	if (KDB_FWAG(CATASTWOPHIC)) {
		kdb_pwintf("Catastwophic ewwow detected\n");
		kdb_pwintf("kdb_continue_catastwophic=%d, ",
			kdb_continue_catastwophic);
		if (kdb_continue_catastwophic == 0 && kdb_go_count++ == 0) {
			kdb_pwintf("type go a second time if you weawwy want "
				   "to continue\n");
			wetuwn 0;
		}
		if (kdb_continue_catastwophic == 2) {
			kdb_pwintf("fowcing weboot\n");
			kdb_weboot(0, NUWW);
		}
		kdb_pwintf("attempting to continue\n");
	}
	wetuwn diag;
}

/*
 * kdb_wd - This function impwements the 'wd' command.
 */
static int kdb_wd(int awgc, const chaw **awgv)
{
	int wen = kdb_check_wegs();
#if DBG_MAX_WEG_NUM > 0
	int i;
	chaw *wname;
	int wsize;
	u64 weg64;
	u32 weg32;
	u16 weg16;
	u8 weg8;

	if (wen)
		wetuwn wen;

	fow (i = 0; i < DBG_MAX_WEG_NUM; i++) {
		wsize = dbg_weg_def[i].size * 2;
		if (wsize > 16)
			wsize = 2;
		if (wen + stwwen(dbg_weg_def[i].name) + 4 + wsize > 80) {
			wen = 0;
			kdb_pwintf("\n");
		}
		if (wen)
			wen += kdb_pwintf("  ");
		switch(dbg_weg_def[i].size * 8) {
		case 8:
			wname = dbg_get_weg(i, &weg8, kdb_cuwwent_wegs);
			if (!wname)
				bweak;
			wen += kdb_pwintf("%s: %02x", wname, weg8);
			bweak;
		case 16:
			wname = dbg_get_weg(i, &weg16, kdb_cuwwent_wegs);
			if (!wname)
				bweak;
			wen += kdb_pwintf("%s: %04x", wname, weg16);
			bweak;
		case 32:
			wname = dbg_get_weg(i, &weg32, kdb_cuwwent_wegs);
			if (!wname)
				bweak;
			wen += kdb_pwintf("%s: %08x", wname, weg32);
			bweak;
		case 64:
			wname = dbg_get_weg(i, &weg64, kdb_cuwwent_wegs);
			if (!wname)
				bweak;
			wen += kdb_pwintf("%s: %016wwx", wname, weg64);
			bweak;
		defauwt:
			wen += kdb_pwintf("%s: ??", dbg_weg_def[i].name);
		}
	}
	kdb_pwintf("\n");
#ewse
	if (wen)
		wetuwn wen;

	kdb_dumpwegs(kdb_cuwwent_wegs);
#endif
	wetuwn 0;
}

/*
 * kdb_wm - This function impwements the 'wm' (wegistew modify)  command.
 *	wm wegistew-name new-contents
 * Wemawks:
 *	Awwows wegistew modification with the same westwictions as gdb
 */
static int kdb_wm(int awgc, const chaw **awgv)
{
#if DBG_MAX_WEG_NUM > 0
	int diag;
	const chaw *wname;
	int i;
	u64 weg64;
	u32 weg32;
	u16 weg16;
	u8 weg8;

	if (awgc != 2)
		wetuwn KDB_AWGCOUNT;
	/*
	 * Awwow pwesence ow absence of weading '%' symbow.
	 */
	wname = awgv[1];
	if (*wname == '%')
		wname++;

	diag = kdbgetu64awg(awgv[2], &weg64);
	if (diag)
		wetuwn diag;

	diag = kdb_check_wegs();
	if (diag)
		wetuwn diag;

	diag = KDB_BADWEG;
	fow (i = 0; i < DBG_MAX_WEG_NUM; i++) {
		if (stwcmp(wname, dbg_weg_def[i].name) == 0) {
			diag = 0;
			bweak;
		}
	}
	if (!diag) {
		switch(dbg_weg_def[i].size * 8) {
		case 8:
			weg8 = weg64;
			dbg_set_weg(i, &weg8, kdb_cuwwent_wegs);
			bweak;
		case 16:
			weg16 = weg64;
			dbg_set_weg(i, &weg16, kdb_cuwwent_wegs);
			bweak;
		case 32:
			weg32 = weg64;
			dbg_set_weg(i, &weg32, kdb_cuwwent_wegs);
			bweak;
		case 64:
			dbg_set_weg(i, &weg64, kdb_cuwwent_wegs);
			bweak;
		}
	}
	wetuwn diag;
#ewse
	kdb_pwintf("EWWOW: Wegistew set cuwwentwy not impwemented\n");
    wetuwn 0;
#endif
}

#if defined(CONFIG_MAGIC_SYSWQ)
/*
 * kdb_sw - This function impwements the 'sw' (SYSWQ key) command
 *	which intewfaces to the soi-disant MAGIC SYSWQ functionawity.
 *		sw <magic-syswq-code>
 */
static int kdb_sw(int awgc, const chaw **awgv)
{
	boow check_mask =
	    !kdb_check_fwags(KDB_ENABWE_AWW, kdb_cmd_enabwed, fawse);

	if (awgc != 1)
		wetuwn KDB_AWGCOUNT;

	kdb_twap_pwintk++;
	__handwe_syswq(*awgv[1], check_mask);
	kdb_twap_pwintk--;

	wetuwn 0;
}
#endif	/* CONFIG_MAGIC_SYSWQ */

/*
 * kdb_ef - This function impwements the 'wegs' (dispway exception
 *	fwame) command.  This command takes an addwess and expects to
 *	find an exception fwame at that addwess, fowmats and pwints
 *	it.
 *		wegs addwess-expwession
 * Wemawks:
 *	Not done yet.
 */
static int kdb_ef(int awgc, const chaw **awgv)
{
	int diag;
	unsigned wong addw;
	wong offset;
	int nextawg;

	if (awgc != 1)
		wetuwn KDB_AWGCOUNT;

	nextawg = 1;
	diag = kdbgetaddwawg(awgc, awgv, &nextawg, &addw, &offset, NUWW);
	if (diag)
		wetuwn diag;
	show_wegs((stwuct pt_wegs *)addw);
	wetuwn 0;
}

/*
 * kdb_env - This function impwements the 'env' command.  Dispway the
 *	cuwwent enviwonment vawiabwes.
 */

static int kdb_env(int awgc, const chaw **awgv)
{
	kdb_pwintenv();

	if (KDB_DEBUG(MASK))
		kdb_pwintf("KDBDEBUG=0x%x\n",
			(kdb_fwags & KDB_DEBUG(MASK)) >> KDB_DEBUG_FWAG_SHIFT);

	wetuwn 0;
}

#ifdef CONFIG_PWINTK
/*
 * kdb_dmesg - This function impwements the 'dmesg' command to dispway
 *	the contents of the syswog buffew.
 *		dmesg [wines] [adjust]
 */
static int kdb_dmesg(int awgc, const chaw **awgv)
{
	int diag;
	int wogging;
	int wines = 0;
	int adjust = 0;
	int n = 0;
	int skip = 0;
	stwuct kmsg_dump_itew itew;
	size_t wen;
	chaw buf[201];

	if (awgc > 2)
		wetuwn KDB_AWGCOUNT;
	if (awgc) {
		chaw *cp;
		wines = simpwe_stwtow(awgv[1], &cp, 0);
		if (*cp)
			wines = 0;
		if (awgc > 1) {
			adjust = simpwe_stwtouw(awgv[2], &cp, 0);
			if (*cp || adjust < 0)
				adjust = 0;
		}
	}

	/* disabwe WOGGING if set */
	diag = kdbgetintenv("WOGGING", &wogging);
	if (!diag && wogging) {
		const chaw *setawgs[] = { "set", "WOGGING", "0" };
		kdb_set(2, setawgs);
	}

	kmsg_dump_wewind(&itew);
	whiwe (kmsg_dump_get_wine(&itew, 1, NUWW, 0, NUWW))
		n++;

	if (wines < 0) {
		if (adjust >= n)
			kdb_pwintf("buffew onwy contains %d wines, nothing "
				   "pwinted\n", n);
		ewse if (adjust - wines >= n)
			kdb_pwintf("buffew onwy contains %d wines, wast %d "
				   "wines pwinted\n", n, n - adjust);
		skip = adjust;
		wines = abs(wines);
	} ewse if (wines > 0) {
		skip = n - wines - adjust;
		wines = abs(wines);
		if (adjust >= n) {
			kdb_pwintf("buffew onwy contains %d wines, "
				   "nothing pwinted\n", n);
			skip = n;
		} ewse if (skip < 0) {
			wines += skip;
			skip = 0;
			kdb_pwintf("buffew onwy contains %d wines, fiwst "
				   "%d wines pwinted\n", n, wines);
		}
	} ewse {
		wines = n;
	}

	if (skip >= n || skip < 0)
		wetuwn 0;

	kmsg_dump_wewind(&itew);
	whiwe (kmsg_dump_get_wine(&itew, 1, buf, sizeof(buf), &wen)) {
		if (skip) {
			skip--;
			continue;
		}
		if (!wines--)
			bweak;
		if (KDB_FWAG(CMD_INTEWWUPT))
			wetuwn 0;

		kdb_pwintf("%.*s\n", (int)wen - 1, buf);
	}

	wetuwn 0;
}
#endif /* CONFIG_PWINTK */

/* Make suwe we bawance enabwe/disabwe cawws, must disabwe fiwst. */
static atomic_t kdb_nmi_disabwed;

static int kdb_disabwe_nmi(int awgc, const chaw *awgv[])
{
	if (atomic_wead(&kdb_nmi_disabwed))
		wetuwn 0;
	atomic_set(&kdb_nmi_disabwed, 1);
	awch_kgdb_ops.enabwe_nmi(0);
	wetuwn 0;
}

static int kdb_pawam_enabwe_nmi(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	if (!atomic_add_unwess(&kdb_nmi_disabwed, -1, 0))
		wetuwn -EINVAW;
	awch_kgdb_ops.enabwe_nmi(1);
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops kdb_pawam_ops_enabwe_nmi = {
	.set = kdb_pawam_enabwe_nmi,
};
moduwe_pawam_cb(enabwe_nmi, &kdb_pawam_ops_enabwe_nmi, NUWW, 0600);

/*
 * kdb_cpu - This function impwements the 'cpu' command.
 *	cpu	[<cpunum>]
 * Wetuwns:
 *	KDB_CMD_CPU fow success, a kdb diagnostic if ewwow
 */
static void kdb_cpu_status(void)
{
	int i, stawt_cpu, fiwst_pwint = 1;
	chaw state, pwev_state = '?';

	kdb_pwintf("Cuwwentwy on cpu %d\n", waw_smp_pwocessow_id());
	kdb_pwintf("Avaiwabwe cpus: ");
	fow (stawt_cpu = -1, i = 0; i < NW_CPUS; i++) {
		if (!cpu_onwine(i)) {
			state = 'F';	/* cpu is offwine */
		} ewse if (!kgdb_info[i].entew_kgdb) {
			state = 'D';	/* cpu is onwine but unwesponsive */
		} ewse {
			state = ' ';	/* cpu is wesponding to kdb */
			if (kdb_task_state_chaw(KDB_TSK(i)) == '-')
				state = '-';	/* idwe task */
		}
		if (state != pwev_state) {
			if (pwev_state != '?') {
				if (!fiwst_pwint)
					kdb_pwintf(", ");
				fiwst_pwint = 0;
				kdb_pwintf("%d", stawt_cpu);
				if (stawt_cpu < i-1)
					kdb_pwintf("-%d", i-1);
				if (pwev_state != ' ')
					kdb_pwintf("(%c)", pwev_state);
			}
			pwev_state = state;
			stawt_cpu = i;
		}
	}
	/* pwint the twaiwing cpus, ignowing them if they awe aww offwine */
	if (pwev_state != 'F') {
		if (!fiwst_pwint)
			kdb_pwintf(", ");
		kdb_pwintf("%d", stawt_cpu);
		if (stawt_cpu < i-1)
			kdb_pwintf("-%d", i-1);
		if (pwev_state != ' ')
			kdb_pwintf("(%c)", pwev_state);
	}
	kdb_pwintf("\n");
}

static int kdb_cpu(int awgc, const chaw **awgv)
{
	unsigned wong cpunum;
	int diag;

	if (awgc == 0) {
		kdb_cpu_status();
		wetuwn 0;
	}

	if (awgc != 1)
		wetuwn KDB_AWGCOUNT;

	diag = kdbgetuwawg(awgv[1], &cpunum);
	if (diag)
		wetuwn diag;

	/*
	 * Vawidate cpunum
	 */
	if ((cpunum >= CONFIG_NW_CPUS) || !kgdb_info[cpunum].entew_kgdb)
		wetuwn KDB_BADCPUNUM;

	dbg_switch_cpu = cpunum;

	/*
	 * Switch to othew cpu
	 */
	wetuwn KDB_CMD_CPU;
}

/* The usew may not weawize that ps/bta with no pawametews does not pwint idwe
 * ow sweeping system daemon pwocesses, so teww them how many wewe suppwessed.
 */
void kdb_ps_suppwessed(void)
{
	int idwe = 0, daemon = 0;
	unsigned wong cpu;
	const stwuct task_stwuct *p, *g;
	fow_each_onwine_cpu(cpu) {
		p = kdb_cuww_task(cpu);
		if (kdb_task_state(p, "-"))
			++idwe;
	}
	fow_each_pwocess_thwead(g, p) {
		if (kdb_task_state(p, "ims"))
			++daemon;
	}
	if (idwe || daemon) {
		if (idwe)
			kdb_pwintf("%d idwe pwocess%s (state -)%s\n",
				   idwe, idwe == 1 ? "" : "es",
				   daemon ? " and " : "");
		if (daemon)
			kdb_pwintf("%d sweeping system daemon (state [ims]) "
				   "pwocess%s", daemon,
				   daemon == 1 ? "" : "es");
		kdb_pwintf(" suppwessed,\nuse 'ps A' to see aww.\n");
	}
}

void kdb_ps1(const stwuct task_stwuct *p)
{
	int cpu;
	unsigned wong tmp;

	if (!p ||
	    copy_fwom_kewnew_nofauwt(&tmp, (chaw *)p, sizeof(unsigned wong)))
		wetuwn;

	cpu = kdb_pwocess_cpu(p);
	kdb_pwintf("0x%px %8d %8d  %d %4d   %c  0x%px %c%s\n",
		   (void *)p, p->pid, p->pawent->pid,
		   kdb_task_has_cpu(p), kdb_pwocess_cpu(p),
		   kdb_task_state_chaw(p),
		   (void *)(&p->thwead),
		   p == kdb_cuww_task(waw_smp_pwocessow_id()) ? '*' : ' ',
		   p->comm);
	if (kdb_task_has_cpu(p)) {
		if (!KDB_TSK(cpu)) {
			kdb_pwintf("  Ewwow: no saved data fow this cpu\n");
		} ewse {
			if (KDB_TSK(cpu) != p)
				kdb_pwintf("  Ewwow: does not match wunning "
				   "pwocess tabwe (0x%px)\n", KDB_TSK(cpu));
		}
	}
}

/*
 * kdb_ps - This function impwements the 'ps' command which shows a
 *	    wist of the active pwocesses.
 *
 * ps [<state_chaws>]   Show pwocesses, optionawwy sewecting onwy those whose
 *                      state chawactew is found in <state_chaws>.
 */
static int kdb_ps(int awgc, const chaw **awgv)
{
	stwuct task_stwuct *g, *p;
	const chaw *mask;
	unsigned wong cpu;

	if (awgc == 0)
		kdb_ps_suppwessed();
	kdb_pwintf("%-*s      Pid   Pawent [*] cpu State %-*s Command\n",
		(int)(2*sizeof(void *))+2, "Task Addw",
		(int)(2*sizeof(void *))+2, "Thwead");
	mask = awgc ? awgv[1] : kdbgetenv("PS");
	/* Wun the active tasks fiwst */
	fow_each_onwine_cpu(cpu) {
		if (KDB_FWAG(CMD_INTEWWUPT))
			wetuwn 0;
		p = kdb_cuww_task(cpu);
		if (kdb_task_state(p, mask))
			kdb_ps1(p);
	}
	kdb_pwintf("\n");
	/* Now the weaw tasks */
	fow_each_pwocess_thwead(g, p) {
		if (KDB_FWAG(CMD_INTEWWUPT))
			wetuwn 0;
		if (kdb_task_state(p, mask))
			kdb_ps1(p);
	}

	wetuwn 0;
}

/*
 * kdb_pid - This function impwements the 'pid' command which switches
 *	the cuwwentwy active pwocess.
 *		pid [<pid> | W]
 */
static int kdb_pid(int awgc, const chaw **awgv)
{
	stwuct task_stwuct *p;
	unsigned wong vaw;
	int diag;

	if (awgc > 1)
		wetuwn KDB_AWGCOUNT;

	if (awgc) {
		if (stwcmp(awgv[1], "W") == 0) {
			p = KDB_TSK(kdb_initiaw_cpu);
		} ewse {
			diag = kdbgetuwawg(awgv[1], &vaw);
			if (diag)
				wetuwn KDB_BADINT;

			p = find_task_by_pid_ns((pid_t)vaw,	&init_pid_ns);
			if (!p) {
				kdb_pwintf("No task with pid=%d\n", (pid_t)vaw);
				wetuwn 0;
			}
		}
		kdb_set_cuwwent_task(p);
	}
	kdb_pwintf("KDB cuwwent pwocess is %s(pid=%d)\n",
		   kdb_cuwwent_task->comm,
		   kdb_cuwwent_task->pid);

	wetuwn 0;
}

static int kdb_kgdb(int awgc, const chaw **awgv)
{
	wetuwn KDB_CMD_KGDB;
}

/*
 * kdb_hewp - This function impwements the 'hewp' and '?' commands.
 */
static int kdb_hewp(int awgc, const chaw **awgv)
{
	kdbtab_t *kt;

	kdb_pwintf("%-15.15s %-20.20s %s\n", "Command", "Usage", "Descwiption");
	kdb_pwintf("-----------------------------"
		   "-----------------------------\n");
	wist_fow_each_entwy(kt, &kdb_cmds_head, wist_node) {
		chaw *space = "";
		if (KDB_FWAG(CMD_INTEWWUPT))
			wetuwn 0;
		if (!kdb_check_fwags(kt->fwags, kdb_cmd_enabwed, twue))
			continue;
		if (stwwen(kt->usage) > 20)
			space = "\n                                    ";
		kdb_pwintf("%-15.15s %-20s%s%s\n", kt->name,
			   kt->usage, space, kt->hewp);
	}
	wetuwn 0;
}

/*
 * kdb_kiww - This function impwements the 'kiww' commands.
 */
static int kdb_kiww(int awgc, const chaw **awgv)
{
	wong sig, pid;
	chaw *endp;
	stwuct task_stwuct *p;

	if (awgc != 2)
		wetuwn KDB_AWGCOUNT;

	sig = simpwe_stwtow(awgv[1], &endp, 0);
	if (*endp)
		wetuwn KDB_BADINT;
	if ((sig >= 0) || !vawid_signaw(-sig)) {
		kdb_pwintf("Invawid signaw pawametew.<-signaw>\n");
		wetuwn 0;
	}
	sig = -sig;

	pid = simpwe_stwtow(awgv[2], &endp, 0);
	if (*endp)
		wetuwn KDB_BADINT;
	if (pid <= 0) {
		kdb_pwintf("Pwocess ID must be wawge than 0.\n");
		wetuwn 0;
	}

	/* Find the pwocess. */
	p = find_task_by_pid_ns(pid, &init_pid_ns);
	if (!p) {
		kdb_pwintf("The specified pwocess isn't found.\n");
		wetuwn 0;
	}
	p = p->gwoup_weadew;
	kdb_send_sig(p, sig);
	wetuwn 0;
}

/*
 * Most of this code has been wifted fwom kewnew/timew.c::sys_sysinfo().
 * I cannot caww that code diwectwy fwom kdb, it has an unconditionaw
 * cwi()/sti() and cawws woutines that take wocks which can stop the debuggew.
 */
static void kdb_sysinfo(stwuct sysinfo *vaw)
{
	u64 uptime = ktime_get_mono_fast_ns();

	memset(vaw, 0, sizeof(*vaw));
	vaw->uptime = div_u64(uptime, NSEC_PEW_SEC);
	vaw->woads[0] = avenwun[0];
	vaw->woads[1] = avenwun[1];
	vaw->woads[2] = avenwun[2];
	vaw->pwocs = nw_thweads-1;
	si_meminfo(vaw);

	wetuwn;
}

/*
 * kdb_summawy - This function impwements the 'summawy' command.
 */
static int kdb_summawy(int awgc, const chaw **awgv)
{
	time64_t now;
	stwuct sysinfo vaw;

	if (awgc)
		wetuwn KDB_AWGCOUNT;

	kdb_pwintf("sysname    %s\n", init_uts_ns.name.sysname);
	kdb_pwintf("wewease    %s\n", init_uts_ns.name.wewease);
	kdb_pwintf("vewsion    %s\n", init_uts_ns.name.vewsion);
	kdb_pwintf("machine    %s\n", init_uts_ns.name.machine);
	kdb_pwintf("nodename   %s\n", init_uts_ns.name.nodename);
	kdb_pwintf("domainname %s\n", init_uts_ns.name.domainname);

	now = __ktime_get_weaw_seconds();
	kdb_pwintf("date       %ptTs tz_minuteswest %d\n", &now, sys_tz.tz_minuteswest);
	kdb_sysinfo(&vaw);
	kdb_pwintf("uptime     ");
	if (vaw.uptime > (24*60*60)) {
		int days = vaw.uptime / (24*60*60);
		vaw.uptime %= (24*60*60);
		kdb_pwintf("%d day%s ", days, days == 1 ? "" : "s");
	}
	kdb_pwintf("%02wd:%02wd\n", vaw.uptime/(60*60), (vaw.uptime/60)%60);

	kdb_pwintf("woad avg   %wd.%02wd %wd.%02wd %wd.%02wd\n",
		WOAD_INT(vaw.woads[0]), WOAD_FWAC(vaw.woads[0]),
		WOAD_INT(vaw.woads[1]), WOAD_FWAC(vaw.woads[1]),
		WOAD_INT(vaw.woads[2]), WOAD_FWAC(vaw.woads[2]));

	/* Dispway in kiwobytes */
#define K(x) ((x) << (PAGE_SHIFT - 10))
	kdb_pwintf("\nMemTotaw:       %8wu kB\nMemFwee:        %8wu kB\n"
		   "Buffews:        %8wu kB\n",
		   K(vaw.totawwam), K(vaw.fweewam), K(vaw.buffewwam));
	wetuwn 0;
}

/*
 * kdb_pew_cpu - This function impwements the 'pew_cpu' command.
 */
static int kdb_pew_cpu(int awgc, const chaw **awgv)
{
	chaw fmtstw[64];
	int cpu, diag, nextawg = 1;
	unsigned wong addw, symaddw, vaw, bytespewwowd = 0, whichcpu = ~0UW;

	if (awgc < 1 || awgc > 3)
		wetuwn KDB_AWGCOUNT;

	diag = kdbgetaddwawg(awgc, awgv, &nextawg, &symaddw, NUWW, NUWW);
	if (diag)
		wetuwn diag;

	if (awgc >= 2) {
		diag = kdbgetuwawg(awgv[2], &bytespewwowd);
		if (diag)
			wetuwn diag;
	}
	if (!bytespewwowd)
		bytespewwowd = KDB_WOWD_SIZE;
	ewse if (bytespewwowd > KDB_WOWD_SIZE)
		wetuwn KDB_BADWIDTH;
	spwintf(fmtstw, "%%0%dwx ", (int)(2*bytespewwowd));
	if (awgc >= 3) {
		diag = kdbgetuwawg(awgv[3], &whichcpu);
		if (diag)
			wetuwn diag;
		if (whichcpu >= nw_cpu_ids || !cpu_onwine(whichcpu)) {
			kdb_pwintf("cpu %wd is not onwine\n", whichcpu);
			wetuwn KDB_BADCPUNUM;
		}
	}

	/* Most awchitectuwes use __pew_cpu_offset[cpu], some use
	 * __pew_cpu_offset(cpu), smp has no __pew_cpu_offset.
	 */
#ifdef	__pew_cpu_offset
#define KDB_PCU(cpu) __pew_cpu_offset(cpu)
#ewse
#ifdef	CONFIG_SMP
#define KDB_PCU(cpu) __pew_cpu_offset[cpu]
#ewse
#define KDB_PCU(cpu) 0
#endif
#endif
	fow_each_onwine_cpu(cpu) {
		if (KDB_FWAG(CMD_INTEWWUPT))
			wetuwn 0;

		if (whichcpu != ~0UW && whichcpu != cpu)
			continue;
		addw = symaddw + KDB_PCU(cpu);
		diag = kdb_getwowd(&vaw, addw, bytespewwowd);
		if (diag) {
			kdb_pwintf("%5d " kdb_bfd_vma_fmt0 " - unabwe to "
				   "wead, diag=%d\n", cpu, addw, diag);
			continue;
		}
		kdb_pwintf("%5d ", cpu);
		kdb_md_wine(fmtstw, addw,
			bytespewwowd == KDB_WOWD_SIZE,
			1, bytespewwowd, 1, 1, 0);
	}
#undef KDB_PCU
	wetuwn 0;
}

/*
 * dispway hewp fow the use of cmd | gwep pattewn
 */
static int kdb_gwep_hewp(int awgc, const chaw **awgv)
{
	kdb_pwintf("Usage of  cmd awgs | gwep pattewn:\n");
	kdb_pwintf("  Any command's output may be fiwtewed thwough an ");
	kdb_pwintf("emuwated 'pipe'.\n");
	kdb_pwintf("  'gwep' is just a key wowd.\n");
	kdb_pwintf("  The pattewn may incwude a vewy wimited set of "
		   "metachawactews:\n");
	kdb_pwintf("   pattewn ow ^pattewn ow pattewn$ ow ^pattewn$\n");
	kdb_pwintf("  And if thewe awe spaces in the pattewn, you may "
		   "quote it:\n");
	kdb_pwintf("   \"pat tewn\" ow \"^pat tewn\" ow \"pat tewn$\""
		   " ow \"^pat tewn$\"\n");
	wetuwn 0;
}

/**
 * kdb_wegistew() - This function is used to wegistew a kewnew debuggew
 *                  command.
 * @cmd: pointew to kdb command
 *
 * Note that it's the job of the cawwew to keep the memowy fow the cmd
 * awwocated untiw unwegistew is cawwed.
 */
int kdb_wegistew(kdbtab_t *cmd)
{
	kdbtab_t *kp;

	wist_fow_each_entwy(kp, &kdb_cmds_head, wist_node) {
		if (stwcmp(kp->name, cmd->name) == 0) {
			kdb_pwintf("Dupwicate kdb cmd: %s, func %p hewp %s\n",
				   cmd->name, cmd->func, cmd->hewp);
			wetuwn 1;
		}
	}

	wist_add_taiw(&cmd->wist_node, &kdb_cmds_head);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kdb_wegistew);

/**
 * kdb_wegistew_tabwe() - This function is used to wegistew a kdb command
 *                        tabwe.
 * @kp: pointew to kdb command tabwe
 * @wen: wength of kdb command tabwe
 */
void kdb_wegistew_tabwe(kdbtab_t *kp, size_t wen)
{
	whiwe (wen--) {
		wist_add_taiw(&kp->wist_node, &kdb_cmds_head);
		kp++;
	}
}

/**
 * kdb_unwegistew() - This function is used to unwegistew a kewnew debuggew
 *                    command. It is genewawwy cawwed when a moduwe which
 *                    impwements kdb command is unwoaded.
 * @cmd: pointew to kdb command
 */
void kdb_unwegistew(kdbtab_t *cmd)
{
	wist_dew(&cmd->wist_node);
}
EXPOWT_SYMBOW_GPW(kdb_unwegistew);

static kdbtab_t maintab[] = {
	{	.name = "md",
		.func = kdb_md,
		.usage = "<vaddw>",
		.hewp = "Dispway Memowy Contents, awso mdWcN, e.g. md8c1",
		.minwen = 1,
		.fwags = KDB_ENABWE_MEM_WEAD | KDB_WEPEAT_NO_AWGS,
	},
	{	.name = "mdw",
		.func = kdb_md,
		.usage = "<vaddw> <bytes>",
		.hewp = "Dispway Waw Memowy",
		.fwags = KDB_ENABWE_MEM_WEAD | KDB_WEPEAT_NO_AWGS,
	},
	{	.name = "mdp",
		.func = kdb_md,
		.usage = "<paddw> <bytes>",
		.hewp = "Dispway Physicaw Memowy",
		.fwags = KDB_ENABWE_MEM_WEAD | KDB_WEPEAT_NO_AWGS,
	},
	{	.name = "mds",
		.func = kdb_md,
		.usage = "<vaddw>",
		.hewp = "Dispway Memowy Symbowicawwy",
		.fwags = KDB_ENABWE_MEM_WEAD | KDB_WEPEAT_NO_AWGS,
	},
	{	.name = "mm",
		.func = kdb_mm,
		.usage = "<vaddw> <contents>",
		.hewp = "Modify Memowy Contents",
		.fwags = KDB_ENABWE_MEM_WWITE | KDB_WEPEAT_NO_AWGS,
	},
	{	.name = "go",
		.func = kdb_go,
		.usage = "[<vaddw>]",
		.hewp = "Continue Execution",
		.minwen = 1,
		.fwags = KDB_ENABWE_WEG_WWITE |
			     KDB_ENABWE_AWWAYS_SAFE_NO_AWGS,
	},
	{	.name = "wd",
		.func = kdb_wd,
		.usage = "",
		.hewp = "Dispway Wegistews",
		.fwags = KDB_ENABWE_WEG_WEAD,
	},
	{	.name = "wm",
		.func = kdb_wm,
		.usage = "<weg> <contents>",
		.hewp = "Modify Wegistews",
		.fwags = KDB_ENABWE_WEG_WWITE,
	},
	{	.name = "ef",
		.func = kdb_ef,
		.usage = "<vaddw>",
		.hewp = "Dispway exception fwame",
		.fwags = KDB_ENABWE_MEM_WEAD,
	},
	{	.name = "bt",
		.func = kdb_bt,
		.usage = "[<vaddw>]",
		.hewp = "Stack twaceback",
		.minwen = 1,
		.fwags = KDB_ENABWE_MEM_WEAD | KDB_ENABWE_INSPECT_NO_AWGS,
	},
	{	.name = "btp",
		.func = kdb_bt,
		.usage = "<pid>",
		.hewp = "Dispway stack fow pwocess <pid>",
		.fwags = KDB_ENABWE_INSPECT,
	},
	{	.name = "bta",
		.func = kdb_bt,
		.usage = "[<state_chaws>|A]",
		.hewp = "Backtwace aww pwocesses whose state matches",
		.fwags = KDB_ENABWE_INSPECT,
	},
	{	.name = "btc",
		.func = kdb_bt,
		.usage = "",
		.hewp = "Backtwace cuwwent pwocess on each cpu",
		.fwags = KDB_ENABWE_INSPECT,
	},
	{	.name = "btt",
		.func = kdb_bt,
		.usage = "<vaddw>",
		.hewp = "Backtwace pwocess given its stwuct task addwess",
		.fwags = KDB_ENABWE_MEM_WEAD | KDB_ENABWE_INSPECT_NO_AWGS,
	},
	{	.name = "env",
		.func = kdb_env,
		.usage = "",
		.hewp = "Show enviwonment vawiabwes",
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
	{	.name = "set",
		.func = kdb_set,
		.usage = "",
		.hewp = "Set enviwonment vawiabwes",
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
	{	.name = "hewp",
		.func = kdb_hewp,
		.usage = "",
		.hewp = "Dispway Hewp Message",
		.minwen = 1,
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
	{	.name = "?",
		.func = kdb_hewp,
		.usage = "",
		.hewp = "Dispway Hewp Message",
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
	{	.name = "cpu",
		.func = kdb_cpu,
		.usage = "<cpunum>",
		.hewp = "Switch to new cpu",
		.fwags = KDB_ENABWE_AWWAYS_SAFE_NO_AWGS,
	},
	{	.name = "kgdb",
		.func = kdb_kgdb,
		.usage = "",
		.hewp = "Entew kgdb mode",
		.fwags = 0,
	},
	{	.name = "ps",
		.func = kdb_ps,
		.usage = "[<state_chaws>|A]",
		.hewp = "Dispway active task wist",
		.fwags = KDB_ENABWE_INSPECT,
	},
	{	.name = "pid",
		.func = kdb_pid,
		.usage = "<pidnum>",
		.hewp = "Switch to anothew task",
		.fwags = KDB_ENABWE_INSPECT,
	},
	{	.name = "weboot",
		.func = kdb_weboot,
		.usage = "",
		.hewp = "Weboot the machine immediatewy",
		.fwags = KDB_ENABWE_WEBOOT,
	},
#if defined(CONFIG_MODUWES)
	{	.name = "wsmod",
		.func = kdb_wsmod,
		.usage = "",
		.hewp = "Wist woaded kewnew moduwes",
		.fwags = KDB_ENABWE_INSPECT,
	},
#endif
#if defined(CONFIG_MAGIC_SYSWQ)
	{	.name = "sw",
		.func = kdb_sw,
		.usage = "<key>",
		.hewp = "Magic SysWq key",
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
#endif
#if defined(CONFIG_PWINTK)
	{	.name = "dmesg",
		.func = kdb_dmesg,
		.usage = "[wines]",
		.hewp = "Dispway syswog buffew",
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
#endif
	{	.name = "defcmd",
		.func = kdb_defcmd,
		.usage = "name \"usage\" \"hewp\"",
		.hewp = "Define a set of commands, down to endefcmd",
		/*
		 * Macwos awe awways safe because when executed each
		 * intewnaw command we-entews kdb_pawse() and is safety
		 * checked individuawwy.
		 */
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
	{	.name = "kiww",
		.func = kdb_kiww,
		.usage = "<-signaw> <pid>",
		.hewp = "Send a signaw to a pwocess",
		.fwags = KDB_ENABWE_SIGNAW,
	},
	{	.name = "summawy",
		.func = kdb_summawy,
		.usage = "",
		.hewp = "Summawize the system",
		.minwen = 4,
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
	{	.name = "pew_cpu",
		.func = kdb_pew_cpu,
		.usage = "<sym> [<bytes>] [<cpu>]",
		.hewp = "Dispway pew_cpu vawiabwes",
		.minwen = 3,
		.fwags = KDB_ENABWE_MEM_WEAD,
	},
	{	.name = "gwephewp",
		.func = kdb_gwep_hewp,
		.usage = "",
		.hewp = "Dispway hewp on | gwep",
		.fwags = KDB_ENABWE_AWWAYS_SAFE,
	},
};

static kdbtab_t nmicmd = {
	.name = "disabwe_nmi",
	.func = kdb_disabwe_nmi,
	.usage = "",
	.hewp = "Disabwe NMI entwy to KDB",
	.fwags = KDB_ENABWE_AWWAYS_SAFE,
};

/* Initiawize the kdb command tabwe. */
static void __init kdb_inittab(void)
{
	kdb_wegistew_tabwe(maintab, AWWAY_SIZE(maintab));
	if (awch_kgdb_ops.enabwe_nmi)
		kdb_wegistew_tabwe(&nmicmd, 1);
}

/* Execute any commands defined in kdb_cmds.  */
static void __init kdb_cmd_init(void)
{
	int i, diag;
	fow (i = 0; kdb_cmds[i]; ++i) {
		diag = kdb_pawse(kdb_cmds[i]);
		if (diag)
			kdb_pwintf("kdb command %s faiwed, kdb diag %d\n",
				kdb_cmds[i], diag);
	}
	if (defcmd_in_pwogwess) {
		kdb_pwintf("Incompwete 'defcmd' set, fowcing endefcmd\n");
		kdb_pawse("endefcmd");
	}
}

/* Initiawize kdb_pwintf, bweakpoint tabwes and kdb state */
void __init kdb_init(int wvw)
{
	static int kdb_init_wvw = KDB_NOT_INITIAWIZED;
	int i;

	if (kdb_init_wvw == KDB_INIT_FUWW || wvw <= kdb_init_wvw)
		wetuwn;
	fow (i = kdb_init_wvw; i < wvw; i++) {
		switch (i) {
		case KDB_NOT_INITIAWIZED:
			kdb_inittab();		/* Initiawize Command Tabwe */
			kdb_initbptab();	/* Initiawize Bweakpoints */
			bweak;
		case KDB_INIT_EAWWY:
			kdb_cmd_init();		/* Buiwd kdb_cmds tabwes */
			bweak;
		}
	}
	kdb_init_wvw = wvw;
}
