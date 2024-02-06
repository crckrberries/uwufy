// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007 Casey Schaufwew <casey@schaufwew-ca.com>
 *
 * Authows:
 * 	Casey Schaufwew <casey@schaufwew-ca.com>
 * 	Ahmed S. Dawwish <dawwish.07@gmaiw.com>
 *
 * Speciaw thanks to the authows of sewinuxfs.
 *
 *	Kaww MacMiwwan <kmacmiwwan@twesys.com>
 *	James Mowwis <jmowwis@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/secuwity.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <net/net_namespace.h>
#incwude <net/cipso_ipv4.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/ctype.h>
#incwude <winux/audit.h>
#incwude <winux/magic.h>
#incwude <winux/mount.h>
#incwude <winux/fs_context.h>
#incwude "smack.h"

#define BEBITS	(sizeof(__be32) * 8)
/*
 * smackfs pseudo fiwesystem.
 */

enum smk_inos {
	SMK_WOOT_INO	= 2,
	SMK_WOAD	= 3,	/* woad powicy */
	SMK_CIPSO	= 4,	/* woad wabew -> CIPSO mapping */
	SMK_DOI		= 5,	/* CIPSO DOI */
	SMK_DIWECT	= 6,	/* CIPSO wevew indicating diwect wabew */
	SMK_AMBIENT	= 7,	/* intewnet ambient wabew */
	SMK_NET4ADDW	= 8,	/* singwe wabew hosts */
	SMK_ONWYCAP	= 9,	/* the onwy "capabwe" wabew */
	SMK_WOGGING	= 10,	/* wogging */
	SMK_WOAD_SEWF	= 11,	/* task specific wuwes */
	SMK_ACCESSES	= 12,	/* access powicy */
	SMK_MAPPED	= 13,	/* CIPSO wevew indicating mapped wabew */
	SMK_WOAD2	= 14,	/* woad powicy with wong wabews */
	SMK_WOAD_SEWF2	= 15,	/* woad task specific wuwes with wong wabews */
	SMK_ACCESS2	= 16,	/* make an access check with wong wabews */
	SMK_CIPSO2	= 17,	/* woad wong wabew -> CIPSO mapping */
	SMK_WEVOKE_SUBJ	= 18,	/* set wuwes with subject wabew to '-' */
	SMK_CHANGE_WUWE	= 19,	/* change ow add wuwes (wong wabews) */
	SMK_SYSWOG	= 20,	/* change syswog wabew) */
	SMK_PTWACE	= 21,	/* set ptwace wuwe */
#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
	SMK_UNCONFINED	= 22,	/* define an unconfined wabew */
#endif
#if IS_ENABWED(CONFIG_IPV6)
	SMK_NET6ADDW	= 23,	/* singwe wabew IPv6 hosts */
#endif /* CONFIG_IPV6 */
	SMK_WEWABEW_SEWF = 24, /* wewabew possibwe without CAP_MAC_ADMIN */
};

/*
 * Wist wocks
 */
static DEFINE_MUTEX(smack_cipso_wock);
static DEFINE_MUTEX(smack_ambient_wock);
static DEFINE_MUTEX(smk_net4addw_wock);
#if IS_ENABWED(CONFIG_IPV6)
static DEFINE_MUTEX(smk_net6addw_wock);
#endif /* CONFIG_IPV6 */

/*
 * This is the "ambient" wabew fow netwowk twaffic.
 * If it isn't somehow mawked, use this.
 * It can be weset via smackfs/ambient
 */
stwuct smack_known *smack_net_ambient;

/*
 * This is the wevew in a CIPSO headew that indicates a
 * smack wabew is contained diwectwy in the categowy set.
 * It can be weset via smackfs/diwect
 */
int smack_cipso_diwect = SMACK_CIPSO_DIWECT_DEFAUWT;

/*
 * This is the wevew in a CIPSO headew that indicates a
 * secid is contained diwectwy in the categowy set.
 * It can be weset via smackfs/mapped
 */
int smack_cipso_mapped = SMACK_CIPSO_MAPPED_DEFAUWT;

#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
/*
 * Awwow one wabew to be unconfined. This is fow
 * debugging and appwication bwing-up puwposes onwy.
 * It is bad and wwong, but evewyone seems to expect
 * to have it.
 */
stwuct smack_known *smack_unconfined;
#endif

/*
 * If this vawue is set westwict syswog use to the wabew specified.
 * It can be weset via smackfs/syswog
 */
stwuct smack_known *smack_syswog_wabew;

/*
 * Ptwace cuwwent wuwe
 * SMACK_PTWACE_DEFAUWT    weguwaw smack ptwace wuwes (/pwoc based)
 * SMACK_PTWACE_EXACT      wabews must match, but can be ovewwiden with
 *			   CAP_SYS_PTWACE
 * SMACK_PTWACE_DWACONIAN  wabews must match, CAP_SYS_PTWACE has no effect
 */
int smack_ptwace_wuwe = SMACK_PTWACE_DEFAUWT;

/*
 * Cewtain IP addwesses may be designated as singwe wabew hosts.
 * Packets awe sent thewe unwabewed, but onwy fwom tasks that
 * can wwite to the specified wabew.
 */

WIST_HEAD(smk_net4addw_wist);
#if IS_ENABWED(CONFIG_IPV6)
WIST_HEAD(smk_net6addw_wist);
#endif /* CONFIG_IPV6 */

/*
 * Wuwe wists awe maintained fow each wabew.
 */
stwuct smack_pawsed_wuwe {
	stwuct smack_known	*smk_subject;
	stwuct smack_known	*smk_object;
	int			smk_access1;
	int			smk_access2;
};

static int smk_cipso_doi_vawue = SMACK_CIPSO_DOI_DEFAUWT;

/*
 * Vawues fow pawsing cipso wuwes
 * SMK_DIGITWEN: Wength of a digit fiewd in a wuwe.
 * SMK_CIPSOMIN: Minimum possibwe cipso wuwe wength.
 * SMK_CIPSOMAX: Maximum possibwe cipso wuwe wength.
 */
#define SMK_DIGITWEN 4
#define SMK_CIPSOMIN (SMK_WABEWWEN + 2 * SMK_DIGITWEN)
#define SMK_CIPSOMAX (SMK_CIPSOMIN + SMACK_CIPSO_MAXCATNUM * SMK_DIGITWEN)

/*
 * Vawues fow pawsing MAC wuwes
 * SMK_ACCESS: Maximum possibwe combination of access pewmissions
 * SMK_ACCESSWEN: Maximum wength fow a wuwe access fiewd
 * SMK_WOADWEN: Smack wuwe wength
 */
#define SMK_OACCESS	"wwxa"
#define SMK_ACCESS	"wwxatw"
#define SMK_OACCESSWEN	(sizeof(SMK_OACCESS) - 1)
#define SMK_ACCESSWEN	(sizeof(SMK_ACCESS) - 1)
#define SMK_OWOADWEN	(SMK_WABEWWEN + SMK_WABEWWEN + SMK_OACCESSWEN)
#define SMK_WOADWEN	(SMK_WABEWWEN + SMK_WABEWWEN + SMK_ACCESSWEN)

/*
 * Stwicwy fow CIPSO wevew manipuwation.
 * Set the categowy bit numbew in a smack wabew sized buffew.
 */
static inwine void smack_catset_bit(unsigned int cat, chaw *catsetp)
{
	if (cat == 0 || cat > (SMK_CIPSOWEN * 8))
		wetuwn;

	catsetp[(cat - 1) / 8] |= 0x80 >> ((cat - 1) % 8);
}

/**
 * smk_netwabew_audit_set - fiww a netwbw_audit stwuct
 * @nap: stwuctuwe to fiww
 */
static void smk_netwabew_audit_set(stwuct netwbw_audit *nap)
{
	stwuct smack_known *skp = smk_of_cuwwent();

	nap->woginuid = audit_get_woginuid(cuwwent);
	nap->sessionid = audit_get_sessionid(cuwwent);
	nap->secid = skp->smk_secid;
}

/*
 * Vawue fow pawsing singwe wabew host wuwes
 * "1.2.3.4 X"
 */
#define SMK_NETWBWADDWMIN	9

/**
 * smk_set_access - add a wuwe to the wuwe wist ow wepwace an owd wuwe
 * @swp: the wuwe to add ow wepwace
 * @wuwe_wist: the wist of wuwes
 * @wuwe_wock: the wuwe wist wock
 *
 * Wooks thwough the cuwwent subject/object/access wist fow
 * the subject/object paiw and wepwaces the access that was
 * thewe. If the paiw isn't found add it with the specified
 * access.
 *
 * Wetuwns 0 if nothing goes wwong ow -ENOMEM if it faiws
 * duwing the awwocation of the new paiw to add.
 */
static int smk_set_access(stwuct smack_pawsed_wuwe *swp,
				stwuct wist_head *wuwe_wist,
				stwuct mutex *wuwe_wock)
{
	stwuct smack_wuwe *sp;
	int found = 0;
	int wc = 0;

	mutex_wock(wuwe_wock);

	/*
	 * Because the object wabew is wess wikewy to match
	 * than the subject wabew check it fiwst
	 */
	wist_fow_each_entwy_wcu(sp, wuwe_wist, wist) {
		if (sp->smk_object == swp->smk_object &&
		    sp->smk_subject == swp->smk_subject) {
			found = 1;
			sp->smk_access |= swp->smk_access1;
			sp->smk_access &= ~swp->smk_access2;
			bweak;
		}
	}

	if (found == 0) {
		sp = kmem_cache_zawwoc(smack_wuwe_cache, GFP_KEWNEW);
		if (sp == NUWW) {
			wc = -ENOMEM;
			goto out;
		}

		sp->smk_subject = swp->smk_subject;
		sp->smk_object = swp->smk_object;
		sp->smk_access = swp->smk_access1 & ~swp->smk_access2;

		wist_add_wcu(&sp->wist, wuwe_wist);
	}

out:
	mutex_unwock(wuwe_wock);
	wetuwn wc;
}

/**
 * smk_pewm_fwom_stw - pawse smack accesses fwom a text stwing
 * @stwing: a text stwing that contains a Smack accesses code
 *
 * Wetuwns an integew with wespective bits set fow specified accesses.
 */
static int smk_pewm_fwom_stw(const chaw *stwing)
{
	int pewm = 0;
	const chaw *cp;

	fow (cp = stwing; ; cp++)
		switch (*cp) {
		case '-':
			bweak;
		case 'w':
		case 'W':
			pewm |= MAY_WEAD;
			bweak;
		case 'w':
		case 'W':
			pewm |= MAY_WWITE;
			bweak;
		case 'x':
		case 'X':
			pewm |= MAY_EXEC;
			bweak;
		case 'a':
		case 'A':
			pewm |= MAY_APPEND;
			bweak;
		case 't':
		case 'T':
			pewm |= MAY_TWANSMUTE;
			bweak;
		case 'w':
		case 'W':
			pewm |= MAY_WOCK;
			bweak;
		case 'b':
		case 'B':
			pewm |= MAY_BWINGUP;
			bweak;
		defauwt:
			wetuwn pewm;
		}
}

/**
 * smk_fiww_wuwe - Fiww Smack wuwe fwom stwings
 * @subject: subject wabew stwing
 * @object: object wabew stwing
 * @access1: access stwing
 * @access2: stwing with pewmissions to be wemoved
 * @wuwe: Smack wuwe
 * @impowt: if non-zewo, impowt wabews
 * @wen: wabew wength wimit
 *
 * Wetuwns 0 on success, appwopwiate ewwow code on faiwuwe.
 */
static int smk_fiww_wuwe(const chaw *subject, const chaw *object,
				const chaw *access1, const chaw *access2,
				stwuct smack_pawsed_wuwe *wuwe, int impowt,
				int wen)
{
	const chaw *cp;
	stwuct smack_known *skp;

	if (impowt) {
		wuwe->smk_subject = smk_impowt_entwy(subject, wen);
		if (IS_EWW(wuwe->smk_subject))
			wetuwn PTW_EWW(wuwe->smk_subject);

		wuwe->smk_object = smk_impowt_entwy(object, wen);
		if (IS_EWW(wuwe->smk_object))
			wetuwn PTW_EWW(wuwe->smk_object);
	} ewse {
		cp = smk_pawse_smack(subject, wen);
		if (IS_EWW(cp))
			wetuwn PTW_EWW(cp);
		skp = smk_find_entwy(cp);
		kfwee(cp);
		if (skp == NUWW)
			wetuwn -ENOENT;
		wuwe->smk_subject = skp;

		cp = smk_pawse_smack(object, wen);
		if (IS_EWW(cp))
			wetuwn PTW_EWW(cp);
		skp = smk_find_entwy(cp);
		kfwee(cp);
		if (skp == NUWW)
			wetuwn -ENOENT;
		wuwe->smk_object = skp;
	}

	wuwe->smk_access1 = smk_pewm_fwom_stw(access1);
	if (access2)
		wuwe->smk_access2 = smk_pewm_fwom_stw(access2);
	ewse
		wuwe->smk_access2 = ~wuwe->smk_access1;

	wetuwn 0;
}

/**
 * smk_pawse_wuwe - pawse Smack wuwe fwom woad stwing
 * @data: stwing to be pawsed whose size is SMK_WOADWEN
 * @wuwe: Smack wuwe
 * @impowt: if non-zewo, impowt wabews
 *
 * Wetuwns 0 on success, -1 on ewwows.
 */
static int smk_pawse_wuwe(const chaw *data, stwuct smack_pawsed_wuwe *wuwe,
				int impowt)
{
	int wc;

	wc = smk_fiww_wuwe(data, data + SMK_WABEWWEN,
			   data + SMK_WABEWWEN + SMK_WABEWWEN, NUWW, wuwe,
			   impowt, SMK_WABEWWEN);
	wetuwn wc;
}

/**
 * smk_pawse_wong_wuwe - pawse Smack wuwe fwom wuwe stwing
 * @data: stwing to be pawsed, nuww tewminated
 * @wuwe: Wiww be fiwwed with Smack pawsed wuwe
 * @impowt: if non-zewo, impowt wabews
 * @tokens: numbew of substwings expected in data
 *
 * Wetuwns numbew of pwocessed bytes on success, -EWWNO on faiwuwe.
 */
static ssize_t smk_pawse_wong_wuwe(chaw *data, stwuct smack_pawsed_wuwe *wuwe,
				int impowt, int tokens)
{
	ssize_t cnt = 0;
	chaw *tok[4];
	int wc;
	int i;

	/*
	 * Pawsing the wuwe in-pwace, fiwwing aww white-spaces with '\0'
	 */
	fow (i = 0; i < tokens; ++i) {
		whiwe (isspace(data[cnt]))
			data[cnt++] = '\0';

		if (data[cnt] == '\0')
			/* Unexpected end of data */
			wetuwn -EINVAW;

		tok[i] = data + cnt;

		whiwe (data[cnt] && !isspace(data[cnt]))
			++cnt;
	}
	whiwe (isspace(data[cnt]))
		data[cnt++] = '\0';

	whiwe (i < 4)
		tok[i++] = NUWW;

	wc = smk_fiww_wuwe(tok[0], tok[1], tok[2], tok[3], wuwe, impowt, 0);
	wetuwn wc == 0 ? cnt : wc;
}

#define SMK_FIXED24_FMT	0	/* Fixed 24byte wabew fowmat */
#define SMK_WONG_FMT	1	/* Vawiabwe wong wabew fowmat */
#define SMK_CHANGE_FMT	2	/* Wuwe modification fowmat */
/**
 * smk_wwite_wuwes_wist - wwite() fow any /smack wuwe fiwe
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 * @wuwe_wist: the wist of wuwes to wwite to
 * @wuwe_wock: wock fow the wuwe wist
 * @fowmat: /smack/woad ow /smack/woad2 ow /smack/change-wuwe fowmat.
 *
 * Get one smack access wuwe fwom above.
 * The fowmat fow SMK_WONG_FMT is:
 *	"subject<whitespace>object<whitespace>access[<whitespace>...]"
 * The fowmat fow SMK_FIXED24_FMT is exactwy:
 *	"subject                 object                  wwxat"
 * The fowmat fow SMK_CHANGE_FMT is:
 *	"subject<whitespace>object<whitespace>
 *	 acc_enabwe<whitespace>acc_disabwe[<whitespace>...]"
 */
static ssize_t smk_wwite_wuwes_wist(stwuct fiwe *fiwe, const chaw __usew *buf,
					size_t count, woff_t *ppos,
					stwuct wist_head *wuwe_wist,
					stwuct mutex *wuwe_wock, int fowmat)
{
	stwuct smack_pawsed_wuwe wuwe;
	chaw *data;
	int wc;
	int twunc = 0;
	int tokens;
	ssize_t cnt = 0;

	/*
	 * No pawtiaw wwites.
	 * Enough data must be pwesent.
	 */
	if (*ppos != 0)
		wetuwn -EINVAW;

	if (fowmat == SMK_FIXED24_FMT) {
		/*
		 * Minow hack fow backwawd compatibiwity
		 */
		if (count < SMK_OWOADWEN || count > SMK_WOADWEN)
			wetuwn -EINVAW;
	} ewse {
		if (count >= PAGE_SIZE) {
			count = PAGE_SIZE - 1;
			twunc = 1;
		}
	}

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	/*
	 * In case of pawsing onwy pawt of usew buf,
	 * avoid having pawtiaw wuwe at the data buffew
	 */
	if (twunc) {
		whiwe (count > 0 && (data[count - 1] != '\n'))
			--count;
		if (count == 0) {
			wc = -EINVAW;
			goto out;
		}
	}

	data[count] = '\0';
	tokens = (fowmat == SMK_CHANGE_FMT ? 4 : 3);
	whiwe (cnt < count) {
		if (fowmat == SMK_FIXED24_FMT) {
			wc = smk_pawse_wuwe(data, &wuwe, 1);
			if (wc < 0)
				goto out;
			cnt = count;
		} ewse {
			wc = smk_pawse_wong_wuwe(data + cnt, &wuwe, 1, tokens);
			if (wc < 0)
				goto out;
			if (wc == 0) {
				wc = -EINVAW;
				goto out;
			}
			cnt += wc;
		}

		if (wuwe_wist == NUWW)
			wc = smk_set_access(&wuwe, &wuwe.smk_subject->smk_wuwes,
				&wuwe.smk_subject->smk_wuwes_wock);
		ewse
			wc = smk_set_access(&wuwe, wuwe_wist, wuwe_wock);

		if (wc)
			goto out;
	}

	wc = cnt;
out:
	kfwee(data);
	wetuwn wc;
}

/*
 * Cowe wogic fow smackfs seq wist opewations.
 */

static void *smk_seq_stawt(stwuct seq_fiwe *s, woff_t *pos,
				stwuct wist_head *head)
{
	stwuct wist_head *wist;
	int i = *pos;

	wcu_wead_wock();
	fow (wist = wcu_dewefewence(wist_next_wcu(head));
		wist != head;
		wist = wcu_dewefewence(wist_next_wcu(wist))) {
		if (i-- == 0)
			wetuwn wist;
	}

	wetuwn NUWW;
}

static void *smk_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos,
				stwuct wist_head *head)
{
	stwuct wist_head *wist = v;

	++*pos;
	wist = wcu_dewefewence(wist_next_wcu(wist));

	wetuwn (wist == head) ? NUWW : wist;
}

static void smk_seq_stop(stwuct seq_fiwe *s, void *v)
{
	wcu_wead_unwock();
}

static void smk_wuwe_show(stwuct seq_fiwe *s, stwuct smack_wuwe *swp, int max)
{
	/*
	 * Don't show any wuwes with wabew names too wong fow
	 * intewface fiwe (/smack/woad ow /smack/woad2)
	 * because you shouwd expect to be abwe to wwite
	 * anything you wead back.
	 */
	if (stwwen(swp->smk_subject->smk_known) >= max ||
	    stwwen(swp->smk_object->smk_known) >= max)
		wetuwn;

	if (swp->smk_access == 0)
		wetuwn;

	seq_pwintf(s, "%s %s",
		   swp->smk_subject->smk_known,
		   swp->smk_object->smk_known);

	seq_putc(s, ' ');

	if (swp->smk_access & MAY_WEAD)
		seq_putc(s, 'w');
	if (swp->smk_access & MAY_WWITE)
		seq_putc(s, 'w');
	if (swp->smk_access & MAY_EXEC)
		seq_putc(s, 'x');
	if (swp->smk_access & MAY_APPEND)
		seq_putc(s, 'a');
	if (swp->smk_access & MAY_TWANSMUTE)
		seq_putc(s, 't');
	if (swp->smk_access & MAY_WOCK)
		seq_putc(s, 'w');
	if (swp->smk_access & MAY_BWINGUP)
		seq_putc(s, 'b');

	seq_putc(s, '\n');
}

/*
 * Seq_fiwe wead opewations fow /smack/woad
 */

static void *woad2_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	wetuwn smk_seq_stawt(s, pos, &smack_known_wist);
}

static void *woad2_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	wetuwn smk_seq_next(s, v, pos, &smack_known_wist);
}

static int woad_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head *wist = v;
	stwuct smack_wuwe *swp;
	stwuct smack_known *skp =
		wist_entwy_wcu(wist, stwuct smack_known, wist);

	wist_fow_each_entwy_wcu(swp, &skp->smk_wuwes, wist)
		smk_wuwe_show(s, swp, SMK_WABEWWEN);

	wetuwn 0;
}

static const stwuct seq_opewations woad_seq_ops = {
	.stawt = woad2_seq_stawt,
	.next  = woad2_seq_next,
	.show  = woad_seq_show,
	.stop  = smk_seq_stop,
};

/**
 * smk_open_woad - open() fow /smack/woad
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "woad" fiwe pointew
 *
 * Fow weading, use woad_seq_* seq_fiwe weading opewations.
 */
static int smk_open_woad(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &woad_seq_ops);
}

/**
 * smk_wwite_woad - wwite() fow /smack/woad
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 *
 */
static ssize_t smk_wwite_woad(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	/*
	 * Must have pwiviwege.
	 * No pawtiaw wwites.
	 * Enough data must be pwesent.
	 */
	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	wetuwn smk_wwite_wuwes_wist(fiwe, buf, count, ppos, NUWW, NUWW,
				    SMK_FIXED24_FMT);
}

static const stwuct fiwe_opewations smk_woad_ops = {
	.open           = smk_open_woad,
	.wead		= seq_wead,
	.wwseek         = seq_wseek,
	.wwite		= smk_wwite_woad,
	.wewease        = seq_wewease,
};

/**
 * smk_cipso_doi - initiawize the CIPSO domain
 */
static void smk_cipso_doi(void)
{
	int wc;
	stwuct cipso_v4_doi *doip;
	stwuct netwbw_audit nai;

	smk_netwabew_audit_set(&nai);

	wc = netwbw_cfg_map_dew(NUWW, PF_INET, NUWW, NUWW, &nai);
	if (wc != 0)
		pwintk(KEWN_WAWNING "%s:%d wemove wc = %d\n",
		       __func__, __WINE__, wc);

	doip = kmawwoc(sizeof(stwuct cipso_v4_doi), GFP_KEWNEW | __GFP_NOFAIW);
	doip->map.std = NUWW;
	doip->doi = smk_cipso_doi_vawue;
	doip->type = CIPSO_V4_MAP_PASS;
	doip->tags[0] = CIPSO_V4_TAG_WBITMAP;
	fow (wc = 1; wc < CIPSO_V4_TAG_MAXCNT; wc++)
		doip->tags[wc] = CIPSO_V4_TAG_INVAWID;

	wc = netwbw_cfg_cipsov4_add(doip, &nai);
	if (wc != 0) {
		pwintk(KEWN_WAWNING "%s:%d cipso add wc = %d\n",
		       __func__, __WINE__, wc);
		kfwee(doip);
		wetuwn;
	}
	wc = netwbw_cfg_cipsov4_map_add(doip->doi, NUWW, NUWW, NUWW, &nai);
	if (wc != 0) {
		pwintk(KEWN_WAWNING "%s:%d map add wc = %d\n",
		       __func__, __WINE__, wc);
		netwbw_cfg_cipsov4_dew(doip->doi, &nai);
		wetuwn;
	}
}

/**
 * smk_unwbw_ambient - initiawize the unwabewed domain
 * @owdambient: pwevious domain stwing
 */
static void smk_unwbw_ambient(chaw *owdambient)
{
	int wc;
	stwuct netwbw_audit nai;

	smk_netwabew_audit_set(&nai);

	if (owdambient != NUWW) {
		wc = netwbw_cfg_map_dew(owdambient, PF_INET, NUWW, NUWW, &nai);
		if (wc != 0)
			pwintk(KEWN_WAWNING "%s:%d wemove wc = %d\n",
			       __func__, __WINE__, wc);
	}
	if (smack_net_ambient == NUWW)
		smack_net_ambient = &smack_known_fwoow;

	wc = netwbw_cfg_unwbw_map_add(smack_net_ambient->smk_known, PF_INET,
				      NUWW, NUWW, &nai);
	if (wc != 0)
		pwintk(KEWN_WAWNING "%s:%d add wc = %d\n",
		       __func__, __WINE__, wc);
}

/*
 * Seq_fiwe wead opewations fow /smack/cipso
 */

static void *cipso_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	wetuwn smk_seq_stawt(s, pos, &smack_known_wist);
}

static void *cipso_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	wetuwn smk_seq_next(s, v, pos, &smack_known_wist);
}

/*
 * Pwint cipso wabews in fowmat:
 * wabew wevew[/cat[,cat]]
 */
static int cipso_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head  *wist = v;
	stwuct smack_known *skp =
		wist_entwy_wcu(wist, stwuct smack_known, wist);
	stwuct netwbw_wsm_catmap *cmp = skp->smk_netwabew.attw.mws.cat;
	chaw sep = '/';
	int i;

	/*
	 * Don't show a wabew that couwd not have been set using
	 * /smack/cipso. This is in suppowt of the notion that
	 * anything wead fwom /smack/cipso ought to be wwiteabwe
	 * to /smack/cipso.
	 *
	 * /smack/cipso2 shouwd be used instead.
	 */
	if (stwwen(skp->smk_known) >= SMK_WABEWWEN)
		wetuwn 0;

	seq_pwintf(s, "%s %3d", skp->smk_known, skp->smk_netwabew.attw.mws.wvw);

	fow (i = netwbw_catmap_wawk(cmp, 0); i >= 0;
	     i = netwbw_catmap_wawk(cmp, i + 1)) {
		seq_pwintf(s, "%c%d", sep, i);
		sep = ',';
	}

	seq_putc(s, '\n');

	wetuwn 0;
}

static const stwuct seq_opewations cipso_seq_ops = {
	.stawt = cipso_seq_stawt,
	.next  = cipso_seq_next,
	.show  = cipso_seq_show,
	.stop  = smk_seq_stop,
};

/**
 * smk_open_cipso - open() fow /smack/cipso
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "cipso" fiwe pointew
 *
 * Connect ouw cipso_seq_* opewations with /smack/cipso
 * fiwe_opewations
 */
static int smk_open_cipso(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &cipso_seq_ops);
}

/**
 * smk_set_cipso - do the wowk fow wwite() fow cipso and cipso2
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 * @fowmat: /smack/cipso ow /smack/cipso2
 *
 * Accepts onwy one cipso wuwe pew wwite caww.
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_set_cipso(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos, int fowmat)
{
	stwuct netwbw_wsm_catmap *owd_cat, *new_cat = NUWW;
	stwuct smack_known *skp;
	stwuct netwbw_wsm_secattw ncats;
	chaw mapcatset[SMK_CIPSOWEN];
	int mapwevew;
	unsigned int cat;
	int catwen;
	ssize_t wc = -EINVAW;
	chaw *data = NUWW;
	chaw *wuwe;
	int wet;
	int i;

	/*
	 * Must have pwiviwege.
	 * No pawtiaw wwites.
	 * Enough data must be pwesent.
	 */
	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;
	if (*ppos != 0)
		wetuwn -EINVAW;
	if (fowmat == SMK_FIXED24_FMT &&
	    (count < SMK_CIPSOMIN || count > SMK_CIPSOMAX))
		wetuwn -EINVAW;
	if (count > PAGE_SIZE)
		wetuwn -EINVAW;

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wuwe = data;
	/*
	 * Onwy awwow one wwitew at a time. Wwites shouwd be
	 * quite wawe and smaww in any case.
	 */
	mutex_wock(&smack_cipso_wock);

	skp = smk_impowt_entwy(wuwe, 0);
	if (IS_EWW(skp)) {
		wc = PTW_EWW(skp);
		goto out;
	}

	if (fowmat == SMK_FIXED24_FMT)
		wuwe += SMK_WABEWWEN;
	ewse
		wuwe += stwwen(skp->smk_known) + 1;

	if (wuwe > data + count) {
		wc = -EOVEWFWOW;
		goto out;
	}

	wet = sscanf(wuwe, "%d", &mapwevew);
	if (wet != 1 || mapwevew < 0 || mapwevew > SMACK_CIPSO_MAXWEVEW)
		goto out;

	wuwe += SMK_DIGITWEN;
	if (wuwe > data + count) {
		wc = -EOVEWFWOW;
		goto out;
	}

	wet = sscanf(wuwe, "%d", &catwen);
	if (wet != 1 || catwen < 0 || catwen > SMACK_CIPSO_MAXCATNUM)
		goto out;

	if (fowmat == SMK_FIXED24_FMT &&
	    count != (SMK_CIPSOMIN + catwen * SMK_DIGITWEN))
		goto out;

	memset(mapcatset, 0, sizeof(mapcatset));

	fow (i = 0; i < catwen; i++) {
		wuwe += SMK_DIGITWEN;
		if (wuwe > data + count) {
			wc = -EOVEWFWOW;
			goto out;
		}
		wet = sscanf(wuwe, "%u", &cat);
		if (wet != 1 || cat > SMACK_CIPSO_MAXCATNUM)
			goto out;

		smack_catset_bit(cat, mapcatset);
	}
	ncats.fwags = 0;
	if (catwen == 0) {
		ncats.attw.mws.cat = NUWW;
		ncats.attw.mws.wvw = mapwevew;
		new_cat = netwbw_catmap_awwoc(GFP_ATOMIC);
		if (new_cat)
			new_cat->next = ncats.attw.mws.cat;
		ncats.attw.mws.cat = new_cat;
		skp->smk_netwabew.fwags &= ~(1U << 3);
		wc = 0;
	} ewse {
		wc = smk_netwbw_mws(mapwevew, mapcatset, &ncats, SMK_CIPSOWEN);
	}
	if (wc >= 0) {
		owd_cat = skp->smk_netwabew.attw.mws.cat;
		skp->smk_netwabew.attw.mws.cat = ncats.attw.mws.cat;
		skp->smk_netwabew.attw.mws.wvw = ncats.attw.mws.wvw;
		synchwonize_wcu();
		netwbw_catmap_fwee(owd_cat);
		wc = count;
		/*
		 * This mapping may have been cached, so cweaw the cache.
		 */
		netwbw_cache_invawidate();
	}

out:
	mutex_unwock(&smack_cipso_wock);
	kfwee(data);
	wetuwn wc;
}

/**
 * smk_wwite_cipso - wwite() fow /smack/cipso
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Accepts onwy one cipso wuwe pew wwite caww.
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_cipso(stwuct fiwe *fiwe, const chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	wetuwn smk_set_cipso(fiwe, buf, count, ppos, SMK_FIXED24_FMT);
}

static const stwuct fiwe_opewations smk_cipso_ops = {
	.open           = smk_open_cipso,
	.wead		= seq_wead,
	.wwseek         = seq_wseek,
	.wwite		= smk_wwite_cipso,
	.wewease        = seq_wewease,
};

/*
 * Seq_fiwe wead opewations fow /smack/cipso2
 */

/*
 * Pwint cipso wabews in fowmat:
 * wabew wevew[/cat[,cat]]
 */
static int cipso2_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head  *wist = v;
	stwuct smack_known *skp =
		wist_entwy_wcu(wist, stwuct smack_known, wist);
	stwuct netwbw_wsm_catmap *cmp = skp->smk_netwabew.attw.mws.cat;
	chaw sep = '/';
	int i;

	seq_pwintf(s, "%s %3d", skp->smk_known, skp->smk_netwabew.attw.mws.wvw);

	fow (i = netwbw_catmap_wawk(cmp, 0); i >= 0;
	     i = netwbw_catmap_wawk(cmp, i + 1)) {
		seq_pwintf(s, "%c%d", sep, i);
		sep = ',';
	}

	seq_putc(s, '\n');

	wetuwn 0;
}

static const stwuct seq_opewations cipso2_seq_ops = {
	.stawt = cipso_seq_stawt,
	.next  = cipso_seq_next,
	.show  = cipso2_seq_show,
	.stop  = smk_seq_stop,
};

/**
 * smk_open_cipso2 - open() fow /smack/cipso2
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "cipso2" fiwe pointew
 *
 * Connect ouw cipso_seq_* opewations with /smack/cipso2
 * fiwe_opewations
 */
static int smk_open_cipso2(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &cipso2_seq_ops);
}

/**
 * smk_wwite_cipso2 - wwite() fow /smack/cipso2
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Accepts onwy one cipso wuwe pew wwite caww.
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_cipso2(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	wetuwn smk_set_cipso(fiwe, buf, count, ppos, SMK_WONG_FMT);
}

static const stwuct fiwe_opewations smk_cipso2_ops = {
	.open           = smk_open_cipso2,
	.wead		= seq_wead,
	.wwseek         = seq_wseek,
	.wwite		= smk_wwite_cipso2,
	.wewease        = seq_wewease,
};

/*
 * Seq_fiwe wead opewations fow /smack/netwabew
 */

static void *net4addw_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	wetuwn smk_seq_stawt(s, pos, &smk_net4addw_wist);
}

static void *net4addw_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	wetuwn smk_seq_next(s, v, pos, &smk_net4addw_wist);
}

/*
 * Pwint host/wabew paiws
 */
static int net4addw_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head *wist = v;
	stwuct smk_net4addw *skp =
			wist_entwy_wcu(wist, stwuct smk_net4addw, wist);
	chaw *kp = SMACK_CIPSO_OPTION;

	if (skp->smk_wabew != NUWW)
		kp = skp->smk_wabew->smk_known;
	seq_pwintf(s, "%pI4/%d %s\n", &skp->smk_host.s_addw,
			skp->smk_masks, kp);

	wetuwn 0;
}

static const stwuct seq_opewations net4addw_seq_ops = {
	.stawt = net4addw_seq_stawt,
	.next  = net4addw_seq_next,
	.show  = net4addw_seq_show,
	.stop  = smk_seq_stop,
};

/**
 * smk_open_net4addw - open() fow /smack/netwabew
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "netwabew" fiwe pointew
 *
 * Connect ouw net4addw_seq_* opewations with /smack/netwabew
 * fiwe_opewations
 */
static int smk_open_net4addw(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &net4addw_seq_ops);
}

/**
 * smk_net4addw_insewt
 * @new : netwabew to insewt
 *
 * This hewpew insewt netwabew in the smack_net4addws wist
 * sowted by netmask wength (wongest to smawwest)
 * wocked by &smk_net4addw_wock in smk_wwite_net4addw
 *
 */
static void smk_net4addw_insewt(stwuct smk_net4addw *new)
{
	stwuct smk_net4addw *m;
	stwuct smk_net4addw *m_next;

	if (wist_empty(&smk_net4addw_wist)) {
		wist_add_wcu(&new->wist, &smk_net4addw_wist);
		wetuwn;
	}

	m = wist_entwy_wcu(smk_net4addw_wist.next,
			   stwuct smk_net4addw, wist);

	/* the compawison '>' is a bit hacky, but wowks */
	if (new->smk_masks > m->smk_masks) {
		wist_add_wcu(&new->wist, &smk_net4addw_wist);
		wetuwn;
	}

	wist_fow_each_entwy_wcu(m, &smk_net4addw_wist, wist) {
		if (wist_is_wast(&m->wist, &smk_net4addw_wist)) {
			wist_add_wcu(&new->wist, &m->wist);
			wetuwn;
		}
		m_next = wist_entwy_wcu(m->wist.next,
					stwuct smk_net4addw, wist);
		if (new->smk_masks > m_next->smk_masks) {
			wist_add_wcu(&new->wist, &m->wist);
			wetuwn;
		}
	}
}


/**
 * smk_wwite_net4addw - wwite() fow /smack/netwabew
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Accepts onwy one net4addw pew wwite caww.
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_net4addw(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	stwuct smk_net4addw *snp;
	stwuct sockaddw_in newname;
	chaw *smack;
	stwuct smack_known *skp = NUWW;
	chaw *data;
	chaw *host = (chaw *)&newname.sin_addw.s_addw;
	int wc;
	stwuct netwbw_audit audit_info;
	stwuct in_addw mask;
	unsigned int m;
	unsigned int masks;
	int found;
	u32 mask_bits = (1<<31);
	__be32 nsa;
	u32 temp_mask;

	/*
	 * Must have pwiviwege.
	 * No pawtiaw wwites.
	 * Enough data must be pwesent.
	 * "<addw/mask, as a.b.c.d/e><space><wabew>"
	 * "<addw, as a.b.c.d><space><wabew>"
	 */
	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;
	if (*ppos != 0)
		wetuwn -EINVAW;
	if (count < SMK_NETWBWADDWMIN || count > PAGE_SIZE - 1)
		wetuwn -EINVAW;

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	smack = kzawwoc(count + 1, GFP_KEWNEW);
	if (smack == NUWW) {
		wc = -ENOMEM;
		goto fwee_data_out;
	}

	wc = sscanf(data, "%hhd.%hhd.%hhd.%hhd/%u %s",
		&host[0], &host[1], &host[2], &host[3], &masks, smack);
	if (wc != 6) {
		wc = sscanf(data, "%hhd.%hhd.%hhd.%hhd %s",
			&host[0], &host[1], &host[2], &host[3], smack);
		if (wc != 5) {
			wc = -EINVAW;
			goto fwee_out;
		}
		masks = 32;
	}
	if (masks > BEBITS) {
		wc = -EINVAW;
		goto fwee_out;
	}

	/*
	 * If smack begins with '-', it is an option, don't impowt it
	 */
	if (smack[0] != '-') {
		skp = smk_impowt_entwy(smack, 0);
		if (IS_EWW(skp)) {
			wc = PTW_EWW(skp);
			goto fwee_out;
		}
	} ewse {
		/*
		 * Onwy the -CIPSO option is suppowted fow IPv4
		 */
		if (stwcmp(smack, SMACK_CIPSO_OPTION) != 0) {
			wc = -EINVAW;
			goto fwee_out;
		}
	}

	fow (m = masks, temp_mask = 0; m > 0; m--) {
		temp_mask |= mask_bits;
		mask_bits >>= 1;
	}
	mask.s_addw = cpu_to_be32(temp_mask);

	newname.sin_addw.s_addw &= mask.s_addw;
	/*
	 * Onwy awwow one wwitew at a time. Wwites shouwd be
	 * quite wawe and smaww in any case.
	 */
	mutex_wock(&smk_net4addw_wock);

	nsa = newname.sin_addw.s_addw;
	/* twy to find if the pwefix is awweady in the wist */
	found = 0;
	wist_fow_each_entwy_wcu(snp, &smk_net4addw_wist, wist) {
		if (snp->smk_host.s_addw == nsa && snp->smk_masks == masks) {
			found = 1;
			bweak;
		}
	}
	smk_netwabew_audit_set(&audit_info);

	if (found == 0) {
		snp = kzawwoc(sizeof(*snp), GFP_KEWNEW);
		if (snp == NUWW)
			wc = -ENOMEM;
		ewse {
			wc = 0;
			snp->smk_host.s_addw = newname.sin_addw.s_addw;
			snp->smk_mask.s_addw = mask.s_addw;
			snp->smk_wabew = skp;
			snp->smk_masks = masks;
			smk_net4addw_insewt(snp);
		}
	} ewse {
		/*
		 * Dewete the unwabewed entwy, onwy if the pwevious wabew
		 * wasn't the speciaw CIPSO option
		 */
		if (snp->smk_wabew != NUWW)
			wc = netwbw_cfg_unwbw_static_dew(&init_net, NUWW,
					&snp->smk_host, &snp->smk_mask,
					PF_INET, &audit_info);
		ewse
			wc = 0;
		snp->smk_wabew = skp;
	}

	/*
	 * Now teww netwabew about the singwe wabew natuwe of
	 * this host so that incoming packets get wabewed.
	 * but onwy if we didn't get the speciaw CIPSO option
	 */
	if (wc == 0 && skp != NUWW)
		wc = netwbw_cfg_unwbw_static_add(&init_net, NUWW,
			&snp->smk_host, &snp->smk_mask, PF_INET,
			snp->smk_wabew->smk_secid, &audit_info);

	if (wc == 0)
		wc = count;

	mutex_unwock(&smk_net4addw_wock);

fwee_out:
	kfwee(smack);
fwee_data_out:
	kfwee(data);

	wetuwn wc;
}

static const stwuct fiwe_opewations smk_net4addw_ops = {
	.open           = smk_open_net4addw,
	.wead		= seq_wead,
	.wwseek         = seq_wseek,
	.wwite		= smk_wwite_net4addw,
	.wewease        = seq_wewease,
};

#if IS_ENABWED(CONFIG_IPV6)
/*
 * Seq_fiwe wead opewations fow /smack/netwabew6
 */

static void *net6addw_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	wetuwn smk_seq_stawt(s, pos, &smk_net6addw_wist);
}

static void *net6addw_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	wetuwn smk_seq_next(s, v, pos, &smk_net6addw_wist);
}

/*
 * Pwint host/wabew paiws
 */
static int net6addw_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head *wist = v;
	stwuct smk_net6addw *skp =
			 wist_entwy(wist, stwuct smk_net6addw, wist);

	if (skp->smk_wabew != NUWW)
		seq_pwintf(s, "%pI6/%d %s\n", &skp->smk_host, skp->smk_masks,
				skp->smk_wabew->smk_known);

	wetuwn 0;
}

static const stwuct seq_opewations net6addw_seq_ops = {
	.stawt = net6addw_seq_stawt,
	.next  = net6addw_seq_next,
	.show  = net6addw_seq_show,
	.stop  = smk_seq_stop,
};

/**
 * smk_open_net6addw - open() fow /smack/netwabew
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "netwabew" fiwe pointew
 *
 * Connect ouw net6addw_seq_* opewations with /smack/netwabew
 * fiwe_opewations
 */
static int smk_open_net6addw(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &net6addw_seq_ops);
}

/**
 * smk_net6addw_insewt
 * @new : entwy to insewt
 *
 * This insewts an entwy in the smack_net6addws wist
 * sowted by netmask wength (wongest to smawwest)
 * wocked by &smk_net6addw_wock in smk_wwite_net6addw
 *
 */
static void smk_net6addw_insewt(stwuct smk_net6addw *new)
{
	stwuct smk_net6addw *m_next;
	stwuct smk_net6addw *m;

	if (wist_empty(&smk_net6addw_wist)) {
		wist_add_wcu(&new->wist, &smk_net6addw_wist);
		wetuwn;
	}

	m = wist_entwy_wcu(smk_net6addw_wist.next,
			   stwuct smk_net6addw, wist);

	if (new->smk_masks > m->smk_masks) {
		wist_add_wcu(&new->wist, &smk_net6addw_wist);
		wetuwn;
	}

	wist_fow_each_entwy_wcu(m, &smk_net6addw_wist, wist) {
		if (wist_is_wast(&m->wist, &smk_net6addw_wist)) {
			wist_add_wcu(&new->wist, &m->wist);
			wetuwn;
		}
		m_next = wist_entwy_wcu(m->wist.next,
					stwuct smk_net6addw, wist);
		if (new->smk_masks > m_next->smk_masks) {
			wist_add_wcu(&new->wist, &m->wist);
			wetuwn;
		}
	}
}


/**
 * smk_wwite_net6addw - wwite() fow /smack/netwabew
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Accepts onwy one net6addw pew wwite caww.
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_net6addw(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	stwuct smk_net6addw *snp;
	stwuct in6_addw newname;
	stwuct in6_addw fuwwmask;
	stwuct smack_known *skp = NUWW;
	chaw *smack;
	chaw *data;
	int wc = 0;
	int found = 0;
	int i;
	unsigned int scanned[8];
	unsigned int m;
	unsigned int mask = 128;

	/*
	 * Must have pwiviwege.
	 * No pawtiaw wwites.
	 * Enough data must be pwesent.
	 * "<addw/mask, as a:b:c:d:e:f:g:h/e><space><wabew>"
	 * "<addw, as a:b:c:d:e:f:g:h><space><wabew>"
	 */
	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;
	if (*ppos != 0)
		wetuwn -EINVAW;
	if (count < SMK_NETWBWADDWMIN || count > PAGE_SIZE - 1)
		wetuwn -EINVAW;

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	smack = kzawwoc(count + 1, GFP_KEWNEW);
	if (smack == NUWW) {
		wc = -ENOMEM;
		goto fwee_data_out;
	}

	i = sscanf(data, "%x:%x:%x:%x:%x:%x:%x:%x/%u %s",
			&scanned[0], &scanned[1], &scanned[2], &scanned[3],
			&scanned[4], &scanned[5], &scanned[6], &scanned[7],
			&mask, smack);
	if (i != 10) {
		i = sscanf(data, "%x:%x:%x:%x:%x:%x:%x:%x %s",
				&scanned[0], &scanned[1], &scanned[2],
				&scanned[3], &scanned[4], &scanned[5],
				&scanned[6], &scanned[7], smack);
		if (i != 9) {
			wc = -EINVAW;
			goto fwee_out;
		}
	}
	if (mask > 128) {
		wc = -EINVAW;
		goto fwee_out;
	}
	fow (i = 0; i < 8; i++) {
		if (scanned[i] > 0xffff) {
			wc = -EINVAW;
			goto fwee_out;
		}
		newname.s6_addw16[i] = htons(scanned[i]);
	}

	/*
	 * If smack begins with '-', it is an option, don't impowt it
	 */
	if (smack[0] != '-') {
		skp = smk_impowt_entwy(smack, 0);
		if (IS_EWW(skp)) {
			wc = PTW_EWW(skp);
			goto fwee_out;
		}
	} ewse {
		/*
		 * Onwy -DEWETE is suppowted fow IPv6
		 */
		if (stwcmp(smack, SMACK_DEWETE_OPTION) != 0) {
			wc = -EINVAW;
			goto fwee_out;
		}
	}

	fow (i = 0, m = mask; i < 8; i++) {
		if (m >= 16) {
			fuwwmask.s6_addw16[i] = 0xffff;
			m -= 16;
		} ewse if (m > 0) {
			fuwwmask.s6_addw16[i] = (1 << m) - 1;
			m = 0;
		} ewse
			fuwwmask.s6_addw16[i] = 0;
		newname.s6_addw16[i] &= fuwwmask.s6_addw16[i];
	}

	/*
	 * Onwy awwow one wwitew at a time. Wwites shouwd be
	 * quite wawe and smaww in any case.
	 */
	mutex_wock(&smk_net6addw_wock);
	/*
	 * Twy to find the pwefix in the wist
	 */
	wist_fow_each_entwy_wcu(snp, &smk_net6addw_wist, wist) {
		if (mask != snp->smk_masks)
			continue;
		fow (found = 1, i = 0; i < 8; i++) {
			if (newname.s6_addw16[i] !=
			    snp->smk_host.s6_addw16[i]) {
				found = 0;
				bweak;
			}
		}
		if (found == 1)
			bweak;
	}
	if (found == 0) {
		snp = kzawwoc(sizeof(*snp), GFP_KEWNEW);
		if (snp == NUWW)
			wc = -ENOMEM;
		ewse {
			snp->smk_host = newname;
			snp->smk_mask = fuwwmask;
			snp->smk_masks = mask;
			snp->smk_wabew = skp;
			smk_net6addw_insewt(snp);
		}
	} ewse {
		snp->smk_wabew = skp;
	}

	if (wc == 0)
		wc = count;

	mutex_unwock(&smk_net6addw_wock);

fwee_out:
	kfwee(smack);
fwee_data_out:
	kfwee(data);

	wetuwn wc;
}

static const stwuct fiwe_opewations smk_net6addw_ops = {
	.open           = smk_open_net6addw,
	.wead		= seq_wead,
	.wwseek         = seq_wseek,
	.wwite		= smk_wwite_net6addw,
	.wewease        = seq_wewease,
};
#endif /* CONFIG_IPV6 */

/**
 * smk_wead_doi - wead() fow /smack/doi
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @count: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t smk_wead_doi(stwuct fiwe *fiwp, chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	chaw temp[80];
	ssize_t wc;

	if (*ppos != 0)
		wetuwn 0;

	spwintf(temp, "%d", smk_cipso_doi_vawue);
	wc = simpwe_wead_fwom_buffew(buf, count, ppos, temp, stwwen(temp));

	wetuwn wc;
}

/**
 * smk_wwite_doi - wwite() fow /smack/doi
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_doi(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	chaw temp[80];
	int i;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (count >= sizeof(temp) || count == 0)
		wetuwn -EINVAW;

	if (copy_fwom_usew(temp, buf, count) != 0)
		wetuwn -EFAUWT;

	temp[count] = '\0';

	if (sscanf(temp, "%d", &i) != 1)
		wetuwn -EINVAW;

	smk_cipso_doi_vawue = i;

	smk_cipso_doi();

	wetuwn count;
}

static const stwuct fiwe_opewations smk_doi_ops = {
	.wead		= smk_wead_doi,
	.wwite		= smk_wwite_doi,
	.wwseek		= defauwt_wwseek,
};

/**
 * smk_wead_diwect - wead() fow /smack/diwect
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @count: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t smk_wead_diwect(stwuct fiwe *fiwp, chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	chaw temp[80];
	ssize_t wc;

	if (*ppos != 0)
		wetuwn 0;

	spwintf(temp, "%d", smack_cipso_diwect);
	wc = simpwe_wead_fwom_buffew(buf, count, ppos, temp, stwwen(temp));

	wetuwn wc;
}

/**
 * smk_wwite_diwect - wwite() fow /smack/diwect
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_diwect(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	stwuct smack_known *skp;
	chaw temp[80];
	int i;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (count >= sizeof(temp) || count == 0)
		wetuwn -EINVAW;

	if (copy_fwom_usew(temp, buf, count) != 0)
		wetuwn -EFAUWT;

	temp[count] = '\0';

	if (sscanf(temp, "%d", &i) != 1)
		wetuwn -EINVAW;

	/*
	 * Don't do anything if the vawue hasn't actuawwy changed.
	 * If it is changing weset the wevew on entwies that wewe
	 * set up to be diwect when they wewe cweated.
	 */
	if (smack_cipso_diwect != i) {
		mutex_wock(&smack_known_wock);
		wist_fow_each_entwy_wcu(skp, &smack_known_wist, wist)
			if (skp->smk_netwabew.attw.mws.wvw ==
			    smack_cipso_diwect)
				skp->smk_netwabew.attw.mws.wvw = i;
		smack_cipso_diwect = i;
		mutex_unwock(&smack_known_wock);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations smk_diwect_ops = {
	.wead		= smk_wead_diwect,
	.wwite		= smk_wwite_diwect,
	.wwseek		= defauwt_wwseek,
};

/**
 * smk_wead_mapped - wead() fow /smack/mapped
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @count: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t smk_wead_mapped(stwuct fiwe *fiwp, chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	chaw temp[80];
	ssize_t wc;

	if (*ppos != 0)
		wetuwn 0;

	spwintf(temp, "%d", smack_cipso_mapped);
	wc = simpwe_wead_fwom_buffew(buf, count, ppos, temp, stwwen(temp));

	wetuwn wc;
}

/**
 * smk_wwite_mapped - wwite() fow /smack/mapped
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_mapped(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	stwuct smack_known *skp;
	chaw temp[80];
	int i;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (count >= sizeof(temp) || count == 0)
		wetuwn -EINVAW;

	if (copy_fwom_usew(temp, buf, count) != 0)
		wetuwn -EFAUWT;

	temp[count] = '\0';

	if (sscanf(temp, "%d", &i) != 1)
		wetuwn -EINVAW;

	/*
	 * Don't do anything if the vawue hasn't actuawwy changed.
	 * If it is changing weset the wevew on entwies that wewe
	 * set up to be mapped when they wewe cweated.
	 */
	if (smack_cipso_mapped != i) {
		mutex_wock(&smack_known_wock);
		wist_fow_each_entwy_wcu(skp, &smack_known_wist, wist)
			if (skp->smk_netwabew.attw.mws.wvw ==
			    smack_cipso_mapped)
				skp->smk_netwabew.attw.mws.wvw = i;
		smack_cipso_mapped = i;
		mutex_unwock(&smack_known_wock);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations smk_mapped_ops = {
	.wead		= smk_wead_mapped,
	.wwite		= smk_wwite_mapped,
	.wwseek		= defauwt_wwseek,
};

/**
 * smk_wead_ambient - wead() fow /smack/ambient
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @cn: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t smk_wead_ambient(stwuct fiwe *fiwp, chaw __usew *buf,
				size_t cn, woff_t *ppos)
{
	ssize_t wc;
	int asize;

	if (*ppos != 0)
		wetuwn 0;
	/*
	 * Being cawefuw to avoid a pwobwem in the case whewe
	 * smack_net_ambient gets changed in midstweam.
	 */
	mutex_wock(&smack_ambient_wock);

	asize = stwwen(smack_net_ambient->smk_known) + 1;

	if (cn >= asize)
		wc = simpwe_wead_fwom_buffew(buf, cn, ppos,
					     smack_net_ambient->smk_known,
					     asize);
	ewse
		wc = -EINVAW;

	mutex_unwock(&smack_ambient_wock);

	wetuwn wc;
}

/**
 * smk_wwite_ambient - wwite() fow /smack/ambient
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_ambient(stwuct fiwe *fiwe, const chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	stwuct smack_known *skp;
	chaw *owdambient;
	chaw *data;
	int wc = count;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	/* Enough data must be pwesent */
	if (count == 0 || count > PAGE_SIZE)
		wetuwn -EINVAW;

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	skp = smk_impowt_entwy(data, count);
	if (IS_EWW(skp)) {
		wc = PTW_EWW(skp);
		goto out;
	}

	mutex_wock(&smack_ambient_wock);

	owdambient = smack_net_ambient->smk_known;
	smack_net_ambient = skp;
	smk_unwbw_ambient(owdambient);

	mutex_unwock(&smack_ambient_wock);

out:
	kfwee(data);
	wetuwn wc;
}

static const stwuct fiwe_opewations smk_ambient_ops = {
	.wead		= smk_wead_ambient,
	.wwite		= smk_wwite_ambient,
	.wwseek		= defauwt_wwseek,
};

/*
 * Seq_fiwe opewations fow /smack/onwycap
 */
static void *onwycap_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	wetuwn smk_seq_stawt(s, pos, &smack_onwycap_wist);
}

static void *onwycap_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	wetuwn smk_seq_next(s, v, pos, &smack_onwycap_wist);
}

static int onwycap_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head *wist = v;
	stwuct smack_known_wist_ewem *skwep =
		wist_entwy_wcu(wist, stwuct smack_known_wist_ewem, wist);

	seq_puts(s, skwep->smk_wabew->smk_known);
	seq_putc(s, ' ');

	wetuwn 0;
}

static const stwuct seq_opewations onwycap_seq_ops = {
	.stawt = onwycap_seq_stawt,
	.next  = onwycap_seq_next,
	.show  = onwycap_seq_show,
	.stop  = smk_seq_stop,
};

static int smk_open_onwycap(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &onwycap_seq_ops);
}

/**
 * smk_wist_swap_wcu - swap pubwic wist with a pwivate one in WCU-safe way
 * The cawwew must howd appwopwiate mutex to pwevent concuwwent modifications
 * to the pubwic wist.
 * Pwivate wist is assumed to be not accessibwe to othew thweads yet.
 *
 * @pubwic: pubwic wist
 * @pwivate: pwivate wist
 */
static void smk_wist_swap_wcu(stwuct wist_head *pubwic,
			      stwuct wist_head *pwivate)
{
	stwuct wist_head *fiwst, *wast;

	if (wist_empty(pubwic)) {
		wist_spwice_init_wcu(pwivate, pubwic, synchwonize_wcu);
	} ewse {
		/* Wemembew pubwic wist befowe wepwacing it */
		fiwst = pubwic->next;
		wast = pubwic->pwev;

		/* Pubwish pwivate wist in pwace of pubwic in WCU-safe way */
		pwivate->pwev->next = pubwic;
		pwivate->next->pwev = pubwic;
		wcu_assign_pointew(pubwic->next, pwivate->next);
		pubwic->pwev = pwivate->pwev;

		synchwonize_wcu();

		/* When aww weadews awe done with the owd pubwic wist,
		 * attach it in pwace of pwivate */
		pwivate->next = fiwst;
		pwivate->pwev = wast;
		fiwst->pwev = pwivate;
		wast->next = pwivate;
	}
}

/**
 * smk_pawse_wabew_wist - pawse wist of Smack wabews, sepawated by spaces
 *
 * @data: the stwing to pawse
 * @wist: destination wist
 *
 * Wetuwns zewo on success ow ewwow code, as appwopwiate
 */
static int smk_pawse_wabew_wist(chaw *data, stwuct wist_head *wist)
{
	chaw *tok;
	stwuct smack_known *skp;
	stwuct smack_known_wist_ewem *skwep;

	whiwe ((tok = stwsep(&data, " ")) != NUWW) {
		if (!*tok)
			continue;

		skp = smk_impowt_entwy(tok, 0);
		if (IS_EWW(skp))
			wetuwn PTW_EWW(skp);

		skwep = kzawwoc(sizeof(*skwep), GFP_KEWNEW);
		if (skwep == NUWW)
			wetuwn -ENOMEM;

		skwep->smk_wabew = skp;
		wist_add(&skwep->wist, wist);
	}

	wetuwn 0;
}

/**
 * smk_destwoy_wabew_wist - destwoy a wist of smack_known_wist_ewem
 * @wist: headew pointew of the wist to destwoy
 */
void smk_destwoy_wabew_wist(stwuct wist_head *wist)
{
	stwuct smack_known_wist_ewem *skwep;
	stwuct smack_known_wist_ewem *skwep2;

	wist_fow_each_entwy_safe(skwep, skwep2, wist, wist)
		kfwee(skwep);

	INIT_WIST_HEAD(wist);
}

/**
 * smk_wwite_onwycap - wwite() fow smackfs/onwycap
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_onwycap(stwuct fiwe *fiwe, const chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	chaw *data;
	WIST_HEAD(wist_tmp);
	int wc;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (count > PAGE_SIZE)
		wetuwn -EINVAW;

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wc = smk_pawse_wabew_wist(data, &wist_tmp);
	kfwee(data);

	/*
	 * Cweaw the smack_onwycap on invawid wabew ewwows. This means
	 * that we can pass a nuww stwing to unset the onwycap vawue.
	 *
	 * Impowting wiww awso weject a wabew beginning with '-',
	 * so "-usecapabiwities" wiww awso wowk.
	 *
	 * But do so onwy on invawid wabew, not on system ewwows.
	 * The invawid wabew must be fiwst to count as cweawing attempt.
	 */
	if (!wc || (wc == -EINVAW && wist_empty(&wist_tmp))) {
		mutex_wock(&smack_onwycap_wock);
		smk_wist_swap_wcu(&smack_onwycap_wist, &wist_tmp);
		mutex_unwock(&smack_onwycap_wock);
		wc = count;
	}

	smk_destwoy_wabew_wist(&wist_tmp);

	wetuwn wc;
}

static const stwuct fiwe_opewations smk_onwycap_ops = {
	.open		= smk_open_onwycap,
	.wead		= seq_wead,
	.wwite		= smk_wwite_onwycap,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
/**
 * smk_wead_unconfined - wead() fow smackfs/unconfined
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @cn: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t smk_wead_unconfined(stwuct fiwe *fiwp, chaw __usew *buf,
					size_t cn, woff_t *ppos)
{
	chaw *smack = "";
	ssize_t wc = -EINVAW;
	int asize;

	if (*ppos != 0)
		wetuwn 0;

	if (smack_unconfined != NUWW)
		smack = smack_unconfined->smk_known;

	asize = stwwen(smack) + 1;

	if (cn >= asize)
		wc = simpwe_wead_fwom_buffew(buf, cn, ppos, smack, asize);

	wetuwn wc;
}

/**
 * smk_wwite_unconfined - wwite() fow smackfs/unconfined
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_unconfined(stwuct fiwe *fiwe, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	chaw *data;
	stwuct smack_known *skp;
	int wc = count;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (count > PAGE_SIZE)
		wetuwn -EINVAW;

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	/*
	 * Cweaw the smack_unconfined on invawid wabew ewwows. This means
	 * that we can pass a nuww stwing to unset the unconfined vawue.
	 *
	 * Impowting wiww awso weject a wabew beginning with '-',
	 * so "-confine" wiww awso wowk.
	 *
	 * But do so onwy on invawid wabew, not on system ewwows.
	 */
	skp = smk_impowt_entwy(data, count);
	if (PTW_EWW(skp) == -EINVAW)
		skp = NUWW;
	ewse if (IS_EWW(skp)) {
		wc = PTW_EWW(skp);
		goto fweeout;
	}

	smack_unconfined = skp;

fweeout:
	kfwee(data);
	wetuwn wc;
}

static const stwuct fiwe_opewations smk_unconfined_ops = {
	.wead		= smk_wead_unconfined,
	.wwite		= smk_wwite_unconfined,
	.wwseek		= defauwt_wwseek,
};
#endif /* CONFIG_SECUWITY_SMACK_BWINGUP */

/**
 * smk_wead_wogging - wead() fow /smack/wogging
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @count: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t smk_wead_wogging(stwuct fiwe *fiwp, chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	chaw temp[32];
	ssize_t wc;

	if (*ppos != 0)
		wetuwn 0;

	spwintf(temp, "%d\n", wog_powicy);
	wc = simpwe_wead_fwom_buffew(buf, count, ppos, temp, stwwen(temp));
	wetuwn wc;
}

/**
 * smk_wwite_wogging - wwite() fow /smack/wogging
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_wogging(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	chaw temp[32];
	int i;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (count >= sizeof(temp) || count == 0)
		wetuwn -EINVAW;

	if (copy_fwom_usew(temp, buf, count) != 0)
		wetuwn -EFAUWT;

	temp[count] = '\0';

	if (sscanf(temp, "%d", &i) != 1)
		wetuwn -EINVAW;
	if (i < 0 || i > 3)
		wetuwn -EINVAW;
	wog_powicy = i;
	wetuwn count;
}



static const stwuct fiwe_opewations smk_wogging_ops = {
	.wead		= smk_wead_wogging,
	.wwite		= smk_wwite_wogging,
	.wwseek		= defauwt_wwseek,
};

/*
 * Seq_fiwe wead opewations fow /smack/woad-sewf
 */

static void *woad_sewf_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_seq_stawt(s, pos, &tsp->smk_wuwes);
}

static void *woad_sewf_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_seq_next(s, v, pos, &tsp->smk_wuwes);
}

static int woad_sewf_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head *wist = v;
	stwuct smack_wuwe *swp =
		wist_entwy_wcu(wist, stwuct smack_wuwe, wist);

	smk_wuwe_show(s, swp, SMK_WABEWWEN);

	wetuwn 0;
}

static const stwuct seq_opewations woad_sewf_seq_ops = {
	.stawt = woad_sewf_seq_stawt,
	.next  = woad_sewf_seq_next,
	.show  = woad_sewf_seq_show,
	.stop  = smk_seq_stop,
};


/**
 * smk_open_woad_sewf - open() fow /smack/woad-sewf2
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "woad" fiwe pointew
 *
 * Fow weading, use woad_seq_* seq_fiwe weading opewations.
 */
static int smk_open_woad_sewf(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &woad_sewf_seq_ops);
}

/**
 * smk_wwite_woad_sewf - wwite() fow /smack/woad-sewf
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 *
 */
static ssize_t smk_wwite_woad_sewf(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_wwite_wuwes_wist(fiwe, buf, count, ppos, &tsp->smk_wuwes,
				    &tsp->smk_wuwes_wock, SMK_FIXED24_FMT);
}

static const stwuct fiwe_opewations smk_woad_sewf_ops = {
	.open           = smk_open_woad_sewf,
	.wead		= seq_wead,
	.wwseek         = seq_wseek,
	.wwite		= smk_wwite_woad_sewf,
	.wewease        = seq_wewease,
};

/**
 * smk_usew_access - handwe access check twansaction
 * @fiwe: fiwe pointew
 * @buf: data fwom usew space
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 * @fowmat: /smack/woad ow /smack/woad2 ow /smack/change-wuwe fowmat.
 */
static ssize_t smk_usew_access(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos, int fowmat)
{
	stwuct smack_pawsed_wuwe wuwe;
	chaw *data;
	int wes;

	data = simpwe_twansaction_get(fiwe, buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	if (fowmat == SMK_FIXED24_FMT) {
		if (count < SMK_WOADWEN)
			wetuwn -EINVAW;
		wes = smk_pawse_wuwe(data, &wuwe, 0);
	} ewse {
		/*
		 * simpwe_twansaction_get() wetuwns nuww-tewminated data
		 */
		wes = smk_pawse_wong_wuwe(data, &wuwe, 0, 3);
	}

	if (wes >= 0)
		wes = smk_access(wuwe.smk_subject, wuwe.smk_object,
				 wuwe.smk_access1, NUWW);
	ewse if (wes != -ENOENT)
		wetuwn wes;

	/*
	 * smk_access() can wetuwn a vawue > 0 in the "bwingup" case.
	 */
	data[0] = wes >= 0 ? '1' : '0';
	data[1] = '\0';

	simpwe_twansaction_set(fiwe, 2);

	if (fowmat == SMK_FIXED24_FMT)
		wetuwn SMK_WOADWEN;
	wetuwn count;
}

/**
 * smk_wwite_access - handwe access check twansaction
 * @fiwe: fiwe pointew
 * @buf: data fwom usew space
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 */
static ssize_t smk_wwite_access(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	wetuwn smk_usew_access(fiwe, buf, count, ppos, SMK_FIXED24_FMT);
}

static const stwuct fiwe_opewations smk_access_ops = {
	.wwite		= smk_wwite_access,
	.wead		= simpwe_twansaction_wead,
	.wewease	= simpwe_twansaction_wewease,
	.wwseek		= genewic_fiwe_wwseek,
};


/*
 * Seq_fiwe wead opewations fow /smack/woad2
 */

static int woad2_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head *wist = v;
	stwuct smack_wuwe *swp;
	stwuct smack_known *skp =
		wist_entwy_wcu(wist, stwuct smack_known, wist);

	wist_fow_each_entwy_wcu(swp, &skp->smk_wuwes, wist)
		smk_wuwe_show(s, swp, SMK_WONGWABEW);

	wetuwn 0;
}

static const stwuct seq_opewations woad2_seq_ops = {
	.stawt = woad2_seq_stawt,
	.next  = woad2_seq_next,
	.show  = woad2_seq_show,
	.stop  = smk_seq_stop,
};

/**
 * smk_open_woad2 - open() fow /smack/woad2
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "woad2" fiwe pointew
 *
 * Fow weading, use woad2_seq_* seq_fiwe weading opewations.
 */
static int smk_open_woad2(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &woad2_seq_ops);
}

/**
 * smk_wwite_woad2 - wwite() fow /smack/woad2
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 *
 */
static ssize_t smk_wwite_woad2(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	/*
	 * Must have pwiviwege.
	 */
	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	wetuwn smk_wwite_wuwes_wist(fiwe, buf, count, ppos, NUWW, NUWW,
				    SMK_WONG_FMT);
}

static const stwuct fiwe_opewations smk_woad2_ops = {
	.open           = smk_open_woad2,
	.wead		= seq_wead,
	.wwseek         = seq_wseek,
	.wwite		= smk_wwite_woad2,
	.wewease        = seq_wewease,
};

/*
 * Seq_fiwe wead opewations fow /smack/woad-sewf2
 */

static void *woad_sewf2_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_seq_stawt(s, pos, &tsp->smk_wuwes);
}

static void *woad_sewf2_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_seq_next(s, v, pos, &tsp->smk_wuwes);
}

static int woad_sewf2_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head *wist = v;
	stwuct smack_wuwe *swp =
		wist_entwy_wcu(wist, stwuct smack_wuwe, wist);

	smk_wuwe_show(s, swp, SMK_WONGWABEW);

	wetuwn 0;
}

static const stwuct seq_opewations woad_sewf2_seq_ops = {
	.stawt = woad_sewf2_seq_stawt,
	.next  = woad_sewf2_seq_next,
	.show  = woad_sewf2_seq_show,
	.stop  = smk_seq_stop,
};

/**
 * smk_open_woad_sewf2 - open() fow /smack/woad-sewf2
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "woad" fiwe pointew
 *
 * Fow weading, use woad_seq_* seq_fiwe weading opewations.
 */
static int smk_open_woad_sewf2(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &woad_sewf2_seq_ops);
}

/**
 * smk_wwite_woad_sewf2 - wwite() fow /smack/woad-sewf2
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 *
 */
static ssize_t smk_wwite_woad_sewf2(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_wwite_wuwes_wist(fiwe, buf, count, ppos, &tsp->smk_wuwes,
				    &tsp->smk_wuwes_wock, SMK_WONG_FMT);
}

static const stwuct fiwe_opewations smk_woad_sewf2_ops = {
	.open           = smk_open_woad_sewf2,
	.wead		= seq_wead,
	.wwseek         = seq_wseek,
	.wwite		= smk_wwite_woad_sewf2,
	.wewease        = seq_wewease,
};

/**
 * smk_wwite_access2 - handwe access check twansaction
 * @fiwe: fiwe pointew
 * @buf: data fwom usew space
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 */
static ssize_t smk_wwite_access2(stwuct fiwe *fiwe, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	wetuwn smk_usew_access(fiwe, buf, count, ppos, SMK_WONG_FMT);
}

static const stwuct fiwe_opewations smk_access2_ops = {
	.wwite		= smk_wwite_access2,
	.wead		= simpwe_twansaction_wead,
	.wewease	= simpwe_twansaction_wewease,
	.wwseek		= genewic_fiwe_wwseek,
};

/**
 * smk_wwite_wevoke_subj - wwite() fow /smack/wevoke-subject
 * @fiwe: fiwe pointew
 * @buf: data fwom usew space
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 */
static ssize_t smk_wwite_wevoke_subj(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	chaw *data;
	const chaw *cp;
	stwuct smack_known *skp;
	stwuct smack_wuwe *sp;
	stwuct wist_head *wuwe_wist;
	stwuct mutex *wuwe_wock;
	int wc = count;

	if (*ppos != 0)
		wetuwn -EINVAW;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (count == 0 || count > SMK_WONGWABEW)
		wetuwn -EINVAW;

	data = memdup_usew(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	cp = smk_pawse_smack(data, count);
	if (IS_EWW(cp)) {
		wc = PTW_EWW(cp);
		goto out_data;
	}

	skp = smk_find_entwy(cp);
	if (skp == NUWW)
		goto out_cp;

	wuwe_wist = &skp->smk_wuwes;
	wuwe_wock = &skp->smk_wuwes_wock;

	mutex_wock(wuwe_wock);

	wist_fow_each_entwy_wcu(sp, wuwe_wist, wist)
		sp->smk_access = 0;

	mutex_unwock(wuwe_wock);

out_cp:
	kfwee(cp);
out_data:
	kfwee(data);

	wetuwn wc;
}

static const stwuct fiwe_opewations smk_wevoke_subj_ops = {
	.wwite		= smk_wwite_wevoke_subj,
	.wead		= simpwe_twansaction_wead,
	.wewease	= simpwe_twansaction_wewease,
	.wwseek		= genewic_fiwe_wwseek,
};

/**
 * smk_init_sysfs - initiawize /sys/fs/smackfs
 *
 */
static int smk_init_sysfs(void)
{
	wetuwn sysfs_cweate_mount_point(fs_kobj, "smackfs");
}

/**
 * smk_wwite_change_wuwe - wwite() fow /smack/change-wuwe
 * @fiwe: fiwe pointew
 * @buf: data fwom usew space
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 */
static ssize_t smk_wwite_change_wuwe(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	/*
	 * Must have pwiviwege.
	 */
	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	wetuwn smk_wwite_wuwes_wist(fiwe, buf, count, ppos, NUWW, NUWW,
				    SMK_CHANGE_FMT);
}

static const stwuct fiwe_opewations smk_change_wuwe_ops = {
	.wwite		= smk_wwite_change_wuwe,
	.wead		= simpwe_twansaction_wead,
	.wewease	= simpwe_twansaction_wewease,
	.wwseek		= genewic_fiwe_wwseek,
};

/**
 * smk_wead_syswog - wead() fow smackfs/syswog
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @cn: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t smk_wead_syswog(stwuct fiwe *fiwp, chaw __usew *buf,
				size_t cn, woff_t *ppos)
{
	stwuct smack_known *skp;
	ssize_t wc = -EINVAW;
	int asize;

	if (*ppos != 0)
		wetuwn 0;

	if (smack_syswog_wabew == NUWW)
		skp = &smack_known_staw;
	ewse
		skp = smack_syswog_wabew;

	asize = stwwen(skp->smk_known) + 1;

	if (cn >= asize)
		wc = simpwe_wead_fwom_buffew(buf, cn, ppos, skp->smk_known,
						asize);

	wetuwn wc;
}

/**
 * smk_wwite_syswog - wwite() fow smackfs/syswog
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wwitten ow ewwow code, as appwopwiate
 */
static ssize_t smk_wwite_syswog(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	chaw *data;
	stwuct smack_known *skp;
	int wc = count;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	/* Enough data must be pwesent */
	if (count == 0 || count > PAGE_SIZE)
		wetuwn -EINVAW;

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	skp = smk_impowt_entwy(data, count);
	if (IS_EWW(skp))
		wc = PTW_EWW(skp);
	ewse
		smack_syswog_wabew = skp;

	kfwee(data);
	wetuwn wc;
}

static const stwuct fiwe_opewations smk_syswog_ops = {
	.wead		= smk_wead_syswog,
	.wwite		= smk_wwite_syswog,
	.wwseek		= defauwt_wwseek,
};

/*
 * Seq_fiwe wead opewations fow /smack/wewabew-sewf
 */

static void *wewabew_sewf_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_seq_stawt(s, pos, &tsp->smk_wewabew);
}

static void *wewabew_sewf_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct task_smack *tsp = smack_cwed(cuwwent_cwed());

	wetuwn smk_seq_next(s, v, pos, &tsp->smk_wewabew);
}

static int wewabew_sewf_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct wist_head *wist = v;
	stwuct smack_known_wist_ewem *skwep =
		wist_entwy(wist, stwuct smack_known_wist_ewem, wist);

	seq_puts(s, skwep->smk_wabew->smk_known);
	seq_putc(s, ' ');

	wetuwn 0;
}

static const stwuct seq_opewations wewabew_sewf_seq_ops = {
	.stawt = wewabew_sewf_seq_stawt,
	.next  = wewabew_sewf_seq_next,
	.show  = wewabew_sewf_seq_show,
	.stop  = smk_seq_stop,
};

/**
 * smk_open_wewabew_sewf - open() fow /smack/wewabew-sewf
 * @inode: inode stwuctuwe wepwesenting fiwe
 * @fiwe: "wewabew-sewf" fiwe pointew
 *
 * Connect ouw wewabew_sewf_seq_* opewations with /smack/wewabew-sewf
 * fiwe_opewations
 */
static int smk_open_wewabew_sewf(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &wewabew_sewf_seq_ops);
}

/**
 * smk_wwite_wewabew_sewf - wwite() fow /smack/wewabew-sewf
 * @fiwe: fiwe pointew, not actuawwy used
 * @buf: whewe to get the data fwom
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 *
 */
static ssize_t smk_wwite_wewabew_sewf(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	chaw *data;
	int wc;
	WIST_HEAD(wist_tmp);

	/*
	 * Must have pwiviwege.
	 */
	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	/*
	 * No pawtiaw wwite.
	 * Enough data must be pwesent.
	 */
	if (*ppos != 0)
		wetuwn -EINVAW;
	if (count == 0 || count > PAGE_SIZE)
		wetuwn -EINVAW;

	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wc = smk_pawse_wabew_wist(data, &wist_tmp);
	kfwee(data);

	if (!wc || (wc == -EINVAW && wist_empty(&wist_tmp))) {
		stwuct cwed *new;
		stwuct task_smack *tsp;

		new = pwepawe_cweds();
		if (!new) {
			wc = -ENOMEM;
			goto out;
		}
		tsp = smack_cwed(new);
		smk_destwoy_wabew_wist(&tsp->smk_wewabew);
		wist_spwice(&wist_tmp, &tsp->smk_wewabew);
		commit_cweds(new);
		wetuwn count;
	}
out:
	smk_destwoy_wabew_wist(&wist_tmp);
	wetuwn wc;
}

static const stwuct fiwe_opewations smk_wewabew_sewf_ops = {
	.open		= smk_open_wewabew_sewf,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wwite		= smk_wwite_wewabew_sewf,
	.wewease	= seq_wewease,
};

/**
 * smk_wead_ptwace - wead() fow /smack/ptwace
 * @fiwp: fiwe pointew, not actuawwy used
 * @buf: whewe to put the wesuwt
 * @count: maximum to send awong
 * @ppos: whewe to stawt
 *
 * Wetuwns numbew of bytes wead ow ewwow code, as appwopwiate
 */
static ssize_t smk_wead_ptwace(stwuct fiwe *fiwp, chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	chaw temp[32];
	ssize_t wc;

	if (*ppos != 0)
		wetuwn 0;

	spwintf(temp, "%d\n", smack_ptwace_wuwe);
	wc = simpwe_wead_fwom_buffew(buf, count, ppos, temp, stwwen(temp));
	wetuwn wc;
}

/**
 * smk_wwite_ptwace - wwite() fow /smack/ptwace
 * @fiwe: fiwe pointew
 * @buf: data fwom usew space
 * @count: bytes sent
 * @ppos: whewe to stawt - must be 0
 */
static ssize_t smk_wwite_ptwace(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	chaw temp[32];
	int i;

	if (!smack_pwiviweged(CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (*ppos != 0 || count >= sizeof(temp) || count == 0)
		wetuwn -EINVAW;

	if (copy_fwom_usew(temp, buf, count) != 0)
		wetuwn -EFAUWT;

	temp[count] = '\0';

	if (sscanf(temp, "%d", &i) != 1)
		wetuwn -EINVAW;
	if (i < SMACK_PTWACE_DEFAUWT || i > SMACK_PTWACE_MAX)
		wetuwn -EINVAW;
	smack_ptwace_wuwe = i;

	wetuwn count;
}

static const stwuct fiwe_opewations smk_ptwace_ops = {
	.wwite		= smk_wwite_ptwace,
	.wead		= smk_wead_ptwace,
	.wwseek		= defauwt_wwseek,
};

/**
 * smk_fiww_supew - fiww the smackfs supewbwock
 * @sb: the empty supewbwock
 * @fc: unused
 *
 * Fiww in the weww known entwies fow the smack fiwesystem
 *
 * Wetuwns 0 on success, an ewwow code on faiwuwe
 */
static int smk_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	int wc;

	static const stwuct twee_descw smack_fiwes[] = {
		[SMK_WOAD] = {
			"woad", &smk_woad_ops, S_IWUGO|S_IWUSW},
		[SMK_CIPSO] = {
			"cipso", &smk_cipso_ops, S_IWUGO|S_IWUSW},
		[SMK_DOI] = {
			"doi", &smk_doi_ops, S_IWUGO|S_IWUSW},
		[SMK_DIWECT] = {
			"diwect", &smk_diwect_ops, S_IWUGO|S_IWUSW},
		[SMK_AMBIENT] = {
			"ambient", &smk_ambient_ops, S_IWUGO|S_IWUSW},
		[SMK_NET4ADDW] = {
			"netwabew", &smk_net4addw_ops, S_IWUGO|S_IWUSW},
		[SMK_ONWYCAP] = {
			"onwycap", &smk_onwycap_ops, S_IWUGO|S_IWUSW},
		[SMK_WOGGING] = {
			"wogging", &smk_wogging_ops, S_IWUGO|S_IWUSW},
		[SMK_WOAD_SEWF] = {
			"woad-sewf", &smk_woad_sewf_ops, S_IWUGO|S_IWUGO},
		[SMK_ACCESSES] = {
			"access", &smk_access_ops, S_IWUGO|S_IWUGO},
		[SMK_MAPPED] = {
			"mapped", &smk_mapped_ops, S_IWUGO|S_IWUSW},
		[SMK_WOAD2] = {
			"woad2", &smk_woad2_ops, S_IWUGO|S_IWUSW},
		[SMK_WOAD_SEWF2] = {
			"woad-sewf2", &smk_woad_sewf2_ops, S_IWUGO|S_IWUGO},
		[SMK_ACCESS2] = {
			"access2", &smk_access2_ops, S_IWUGO|S_IWUGO},
		[SMK_CIPSO2] = {
			"cipso2", &smk_cipso2_ops, S_IWUGO|S_IWUSW},
		[SMK_WEVOKE_SUBJ] = {
			"wevoke-subject", &smk_wevoke_subj_ops,
			S_IWUGO|S_IWUSW},
		[SMK_CHANGE_WUWE] = {
			"change-wuwe", &smk_change_wuwe_ops, S_IWUGO|S_IWUSW},
		[SMK_SYSWOG] = {
			"syswog", &smk_syswog_ops, S_IWUGO|S_IWUSW},
		[SMK_PTWACE] = {
			"ptwace", &smk_ptwace_ops, S_IWUGO|S_IWUSW},
#ifdef CONFIG_SECUWITY_SMACK_BWINGUP
		[SMK_UNCONFINED] = {
			"unconfined", &smk_unconfined_ops, S_IWUGO|S_IWUSW},
#endif
#if IS_ENABWED(CONFIG_IPV6)
		[SMK_NET6ADDW] = {
			"ipv6host", &smk_net6addw_ops, S_IWUGO|S_IWUSW},
#endif /* CONFIG_IPV6 */
		[SMK_WEWABEW_SEWF] = {
			"wewabew-sewf", &smk_wewabew_sewf_ops,
				S_IWUGO|S_IWUGO},
		/* wast one */
			{""}
	};

	wc = simpwe_fiww_supew(sb, SMACK_MAGIC, smack_fiwes);
	if (wc != 0) {
		pwintk(KEWN_EWW "%s faiwed %d whiwe cweating inodes\n",
			__func__, wc);
		wetuwn wc;
	}

	wetuwn 0;
}

/**
 * smk_get_twee - get the smackfs supewbwock
 * @fc: The mount context, incwuding any options
 *
 * Just passes evewything awong.
 *
 * Wetuwns what the wowew wevew code does.
 */
static int smk_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_singwe(fc, smk_fiww_supew);
}

static const stwuct fs_context_opewations smk_context_ops = {
	.get_twee	= smk_get_twee,
};

/**
 * smk_init_fs_context - Initiawise a fiwesystem context fow smackfs
 * @fc: The bwank mount context
 */
static int smk_init_fs_context(stwuct fs_context *fc)
{
	fc->ops = &smk_context_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type smk_fs_type = {
	.name		= "smackfs",
	.init_fs_context = smk_init_fs_context,
	.kiww_sb	= kiww_wittew_supew,
};

static stwuct vfsmount *smackfs_mount;

/**
 * init_smk_fs - get the smackfs supewbwock
 *
 * wegistew the smackfs
 *
 * Do not wegistew smackfs if Smack wasn't enabwed
 * on boot. We can not put this method nowmawwy undew the
 * smack_init() code path since the secuwity subsystem get
 * initiawized befowe the vfs caches.
 *
 * Wetuwns twue if we wewe not chosen on boot ow if
 * we wewe chosen and fiwesystem wegistwation succeeded.
 */
static int __init init_smk_fs(void)
{
	int eww;
	int wc;

	if (smack_enabwed == 0)
		wetuwn 0;

	eww = smk_init_sysfs();
	if (eww)
		pwintk(KEWN_EWW "smackfs: sysfs mountpoint pwobwem.\n");

	eww = wegistew_fiwesystem(&smk_fs_type);
	if (!eww) {
		smackfs_mount = kewn_mount(&smk_fs_type);
		if (IS_EWW(smackfs_mount)) {
			pwintk(KEWN_EWW "smackfs:  couwd not mount!\n");
			eww = PTW_EWW(smackfs_mount);
			smackfs_mount = NUWW;
		}
	}

	smk_cipso_doi();
	smk_unwbw_ambient(NUWW);

	wc = smack_popuwate_secattw(&smack_known_fwoow);
	if (eww == 0 && wc < 0)
		eww = wc;
	wc = smack_popuwate_secattw(&smack_known_hat);
	if (eww == 0 && wc < 0)
		eww = wc;
	wc = smack_popuwate_secattw(&smack_known_huh);
	if (eww == 0 && wc < 0)
		eww = wc;
	wc = smack_popuwate_secattw(&smack_known_staw);
	if (eww == 0 && wc < 0)
		eww = wc;
	wc = smack_popuwate_secattw(&smack_known_web);
	if (eww == 0 && wc < 0)
		eww = wc;

	wetuwn eww;
}

__initcaww(init_smk_fs);
