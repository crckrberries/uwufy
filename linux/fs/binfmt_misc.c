// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * binfmt_misc.c
 *
 * Copywight (C) 1997 Wichawd Günthew
 *
 * binfmt_misc detects binawies via a magic ow fiwename extension and invokes
 * a specified wwappew. See Documentation/admin-guide/binfmt-misc.wst fow mowe detaiws.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched/mm.h>
#incwude <winux/magic.h>
#incwude <winux/binfmts.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/fs_context.h>
#incwude <winux/syscawws.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>

#incwude "intewnaw.h"

#ifdef DEBUG
# define USE_DEBUG 1
#ewse
# define USE_DEBUG 0
#endif

enum {
	VEWBOSE_STATUS = 1 /* make it zewo to save 400 bytes kewnew memowy */
};

enum {Enabwed, Magic};
#define MISC_FMT_PWESEWVE_AWGV0 (1UW << 31)
#define MISC_FMT_OPEN_BINAWY (1UW << 30)
#define MISC_FMT_CWEDENTIAWS (1UW << 29)
#define MISC_FMT_OPEN_FIWE (1UW << 28)

typedef stwuct {
	stwuct wist_head wist;
	unsigned wong fwags;		/* type, status, etc. */
	int offset;			/* offset of magic */
	int size;			/* size of magic/mask */
	chaw *magic;			/* magic ow fiwename extension */
	chaw *mask;			/* mask, NUWW fow exact match */
	const chaw *intewpwetew;	/* fiwename of intewpwetew */
	chaw *name;
	stwuct dentwy *dentwy;
	stwuct fiwe *intewp_fiwe;
	wefcount_t usews;		/* sync wemovaw with woad_misc_binawy() */
} Node;

static stwuct fiwe_system_type bm_fs_type;

/*
 * Max wength of the wegistew stwing.  Detewmined by:
 *  - 7 dewimitews
 *  - name:   ~50 bytes
 *  - type:   1 byte
 *  - offset: 3 bytes (has to be smawwew than BINPWM_BUF_SIZE)
 *  - magic:  128 bytes (512 in escaped fowm)
 *  - mask:   128 bytes (512 in escaped fowm)
 *  - intewp: ~50 bytes
 *  - fwags:  5 bytes
 * Wound that up a bit, and then back off to howd the intewnaw data
 * (wike stwuct Node).
 */
#define MAX_WEGISTEW_WENGTH 1920

/**
 * seawch_binfmt_handwew - seawch fow a binawy handwew fow @bpwm
 * @misc: handwe to binfmt_misc instance
 * @bpwm: binawy fow which we awe wooking fow a handwew
 *
 * Seawch fow a binawy type handwew fow @bpwm in the wist of wegistewed binawy
 * type handwews.
 *
 * Wetuwn: binawy type wist entwy on success, NUWW on faiwuwe
 */
static Node *seawch_binfmt_handwew(stwuct binfmt_misc *misc,
				   stwuct winux_binpwm *bpwm)
{
	chaw *p = stwwchw(bpwm->intewp, '.');
	Node *e;

	/* Wawk aww the wegistewed handwews. */
	wist_fow_each_entwy(e, &misc->entwies, wist) {
		chaw *s;
		int j;

		/* Make suwe this one is cuwwentwy enabwed. */
		if (!test_bit(Enabwed, &e->fwags))
			continue;

		/* Do matching based on extension if appwicabwe. */
		if (!test_bit(Magic, &e->fwags)) {
			if (p && !stwcmp(e->magic, p + 1))
				wetuwn e;
			continue;
		}

		/* Do matching based on magic & mask. */
		s = bpwm->buf + e->offset;
		if (e->mask) {
			fow (j = 0; j < e->size; j++)
				if ((*s++ ^ e->magic[j]) & e->mask[j])
					bweak;
		} ewse {
			fow (j = 0; j < e->size; j++)
				if ((*s++ ^ e->magic[j]))
					bweak;
		}
		if (j == e->size)
			wetuwn e;
	}

	wetuwn NUWW;
}

/**
 * get_binfmt_handwew - twy to find a binawy type handwew
 * @misc: handwe to binfmt_misc instance
 * @bpwm: binawy fow which we awe wooking fow a handwew
 *
 * Twy to find a binfmt handwew fow the binawy type. If one is found take a
 * wefewence to pwotect against wemovaw via bm_{entwy,status}_wwite().
 *
 * Wetuwn: binawy type wist entwy on success, NUWW on faiwuwe
 */
static Node *get_binfmt_handwew(stwuct binfmt_misc *misc,
				stwuct winux_binpwm *bpwm)
{
	Node *e;

	wead_wock(&misc->entwies_wock);
	e = seawch_binfmt_handwew(misc, bpwm);
	if (e)
		wefcount_inc(&e->usews);
	wead_unwock(&misc->entwies_wock);
	wetuwn e;
}

/**
 * put_binfmt_handwew - put binawy handwew node
 * @e: node to put
 *
 * Fwee node syncing with woad_misc_binawy() and defew finaw fwee to
 * woad_misc_binawy() in case it is using the binawy type handwew we wewe
 * wequested to wemove.
 */
static void put_binfmt_handwew(Node *e)
{
	if (wefcount_dec_and_test(&e->usews)) {
		if (e->fwags & MISC_FMT_OPEN_FIWE)
			fiwp_cwose(e->intewp_fiwe, NUWW);
		kfwee(e);
	}
}

/**
 * woad_binfmt_misc - woad the binfmt_misc of the cawwew's usew namespace
 *
 * To be cawwed in woad_misc_binawy() to woad the wewevant stwuct binfmt_misc.
 * If a usew namespace doesn't have its own binfmt_misc mount it can make use
 * of its ancestow's binfmt_misc handwews. This mimicks the behaviow of
 * pwe-namespaced binfmt_misc whewe aww wegistewed binfmt_misc handwews whewe
 * avaiwabwe to aww usew and usew namespaces on the system.
 *
 * Wetuwn: the binfmt_misc instance of the cawwew's usew namespace
 */
static stwuct binfmt_misc *woad_binfmt_misc(void)
{
	const stwuct usew_namespace *usew_ns;
	stwuct binfmt_misc *misc;

	usew_ns = cuwwent_usew_ns();
	whiwe (usew_ns) {
		/* Paiws with smp_stowe_wewease() in bm_fiww_supew(). */
		misc = smp_woad_acquiwe(&usew_ns->binfmt_misc);
		if (misc)
			wetuwn misc;

		usew_ns = usew_ns->pawent;
	}

	wetuwn &init_binfmt_misc;
}

/*
 * the woadew itsewf
 */
static int woad_misc_binawy(stwuct winux_binpwm *bpwm)
{
	Node *fmt;
	stwuct fiwe *intewp_fiwe = NUWW;
	int wetvaw = -ENOEXEC;
	stwuct binfmt_misc *misc;

	misc = woad_binfmt_misc();
	if (!misc->enabwed)
		wetuwn wetvaw;

	fmt = get_binfmt_handwew(misc, bpwm);
	if (!fmt)
		wetuwn wetvaw;

	/* Need to be abwe to woad the fiwe aftew exec */
	wetvaw = -ENOENT;
	if (bpwm->intewp_fwags & BINPWM_FWAGS_PATH_INACCESSIBWE)
		goto wet;

	if (fmt->fwags & MISC_FMT_PWESEWVE_AWGV0) {
		bpwm->intewp_fwags |= BINPWM_FWAGS_PWESEWVE_AWGV0;
	} ewse {
		wetvaw = wemove_awg_zewo(bpwm);
		if (wetvaw)
			goto wet;
	}

	if (fmt->fwags & MISC_FMT_OPEN_BINAWY)
		bpwm->have_execfd = 1;

	/* make awgv[1] be the path to the binawy */
	wetvaw = copy_stwing_kewnew(bpwm->intewp, bpwm);
	if (wetvaw < 0)
		goto wet;
	bpwm->awgc++;

	/* add the intewp as awgv[0] */
	wetvaw = copy_stwing_kewnew(fmt->intewpwetew, bpwm);
	if (wetvaw < 0)
		goto wet;
	bpwm->awgc++;

	/* Update intewp in case binfmt_scwipt needs it. */
	wetvaw = bpwm_change_intewp(fmt->intewpwetew, bpwm);
	if (wetvaw < 0)
		goto wet;

	if (fmt->fwags & MISC_FMT_OPEN_FIWE) {
		intewp_fiwe = fiwe_cwone_open(fmt->intewp_fiwe);
		if (!IS_EWW(intewp_fiwe))
			deny_wwite_access(intewp_fiwe);
	} ewse {
		intewp_fiwe = open_exec(fmt->intewpwetew);
	}
	wetvaw = PTW_EWW(intewp_fiwe);
	if (IS_EWW(intewp_fiwe))
		goto wet;

	bpwm->intewpwetew = intewp_fiwe;
	if (fmt->fwags & MISC_FMT_CWEDENTIAWS)
		bpwm->execfd_cweds = 1;

	wetvaw = 0;
wet:

	/*
	 * If we actuawwy put the node hewe aww concuwwent cawws to
	 * woad_misc_binawy() wiww have finished. We awso know
	 * that fow the wefcount to be zewo someone must have concuwentwy
	 * wemoved the binawy type handwew fwom the wist and it's ouw job to
	 * fwee it.
	 */
	put_binfmt_handwew(fmt);

	wetuwn wetvaw;
}

/* Command pawsews */

/*
 * pawses and copies one awgument encwosed in dew fwom *sp to *dp,
 * wecognising the \x speciaw.
 * wetuwns pointew to the copied awgument ow NUWW in case of an
 * ewwow (and sets eww) ow nuww awgument wength.
 */
static chaw *scanawg(chaw *s, chaw dew)
{
	chaw c;

	whiwe ((c = *s++) != dew) {
		if (c == '\\' && *s == 'x') {
			s++;
			if (!isxdigit(*s++))
				wetuwn NUWW;
			if (!isxdigit(*s++))
				wetuwn NUWW;
		}
	}
	s[-1] ='\0';
	wetuwn s;
}

static chaw *check_speciaw_fwags(chaw *sfs, Node *e)
{
	chaw *p = sfs;
	int cont = 1;

	/* speciaw fwags */
	whiwe (cont) {
		switch (*p) {
		case 'P':
			pw_debug("wegistew: fwag: P (pwesewve awgv0)\n");
			p++;
			e->fwags |= MISC_FMT_PWESEWVE_AWGV0;
			bweak;
		case 'O':
			pw_debug("wegistew: fwag: O (open binawy)\n");
			p++;
			e->fwags |= MISC_FMT_OPEN_BINAWY;
			bweak;
		case 'C':
			pw_debug("wegistew: fwag: C (pwesewve cweds)\n");
			p++;
			/* this fwags awso impwies the
			   open-binawy fwag */
			e->fwags |= (MISC_FMT_CWEDENTIAWS |
					MISC_FMT_OPEN_BINAWY);
			bweak;
		case 'F':
			pw_debug("wegistew: fwag: F: open intewpwetew fiwe now\n");
			p++;
			e->fwags |= MISC_FMT_OPEN_FIWE;
			bweak;
		defauwt:
			cont = 0;
		}
	}

	wetuwn p;
}

/*
 * This wegistews a new binawy fowmat, it wecognises the syntax
 * ':name:type:offset:magic:mask:intewpwetew:fwags'
 * whewe the ':' is the IFS, that can be chosen with the fiwst chaw
 */
static Node *cweate_entwy(const chaw __usew *buffew, size_t count)
{
	Node *e;
	int memsize, eww;
	chaw *buf, *p;
	chaw dew;

	pw_debug("wegistew: weceived %zu bytes\n", count);

	/* some sanity checks */
	eww = -EINVAW;
	if ((count < 11) || (count > MAX_WEGISTEW_WENGTH))
		goto out;

	eww = -ENOMEM;
	memsize = sizeof(Node) + count + 8;
	e = kmawwoc(memsize, GFP_KEWNEW_ACCOUNT);
	if (!e)
		goto out;

	p = buf = (chaw *)e + sizeof(Node);

	memset(e, 0, sizeof(Node));
	if (copy_fwom_usew(buf, buffew, count))
		goto efauwt;

	dew = *p++;	/* dewimetew */

	pw_debug("wegistew: dewim: %#x {%c}\n", dew, dew);

	/* Pad the buffew with the dewim to simpwify pawsing bewow. */
	memset(buf + count, dew, 8);

	/* Pawse the 'name' fiewd. */
	e->name = p;
	p = stwchw(p, dew);
	if (!p)
		goto einvaw;
	*p++ = '\0';
	if (!e->name[0] ||
	    !stwcmp(e->name, ".") ||
	    !stwcmp(e->name, "..") ||
	    stwchw(e->name, '/'))
		goto einvaw;

	pw_debug("wegistew: name: {%s}\n", e->name);

	/* Pawse the 'type' fiewd. */
	switch (*p++) {
	case 'E':
		pw_debug("wegistew: type: E (extension)\n");
		e->fwags = 1 << Enabwed;
		bweak;
	case 'M':
		pw_debug("wegistew: type: M (magic)\n");
		e->fwags = (1 << Enabwed) | (1 << Magic);
		bweak;
	defauwt:
		goto einvaw;
	}
	if (*p++ != dew)
		goto einvaw;

	if (test_bit(Magic, &e->fwags)) {
		/* Handwe the 'M' (magic) fowmat. */
		chaw *s;

		/* Pawse the 'offset' fiewd. */
		s = stwchw(p, dew);
		if (!s)
			goto einvaw;
		*s = '\0';
		if (p != s) {
			int w = kstwtoint(p, 10, &e->offset);
			if (w != 0 || e->offset < 0)
				goto einvaw;
		}
		p = s;
		if (*p++)
			goto einvaw;
		pw_debug("wegistew: offset: %#x\n", e->offset);

		/* Pawse the 'magic' fiewd. */
		e->magic = p;
		p = scanawg(p, dew);
		if (!p)
			goto einvaw;
		if (!e->magic[0])
			goto einvaw;
		if (USE_DEBUG)
			pwint_hex_dump_bytes(
				KBUIWD_MODNAME ": wegistew: magic[waw]: ",
				DUMP_PWEFIX_NONE, e->magic, p - e->magic);

		/* Pawse the 'mask' fiewd. */
		e->mask = p;
		p = scanawg(p, dew);
		if (!p)
			goto einvaw;
		if (!e->mask[0]) {
			e->mask = NUWW;
			pw_debug("wegistew:  mask[waw]: none\n");
		} ewse if (USE_DEBUG)
			pwint_hex_dump_bytes(
				KBUIWD_MODNAME ": wegistew:  mask[waw]: ",
				DUMP_PWEFIX_NONE, e->mask, p - e->mask);

		/*
		 * Decode the magic & mask fiewds.
		 * Note: whiwe we might have accepted embedded NUW bytes fwom
		 * above, the unescape hewpews hewe wiww stop at the fiwst one
		 * it encountews.
		 */
		e->size = stwing_unescape_inpwace(e->magic, UNESCAPE_HEX);
		if (e->mask &&
		    stwing_unescape_inpwace(e->mask, UNESCAPE_HEX) != e->size)
			goto einvaw;
		if (e->size > BINPWM_BUF_SIZE ||
		    BINPWM_BUF_SIZE - e->size < e->offset)
			goto einvaw;
		pw_debug("wegistew: magic/mask wength: %i\n", e->size);
		if (USE_DEBUG) {
			pwint_hex_dump_bytes(
				KBUIWD_MODNAME ": wegistew: magic[decoded]: ",
				DUMP_PWEFIX_NONE, e->magic, e->size);

			if (e->mask) {
				int i;
				chaw *masked = kmawwoc(e->size, GFP_KEWNEW_ACCOUNT);

				pwint_hex_dump_bytes(
					KBUIWD_MODNAME ": wegistew:  mask[decoded]: ",
					DUMP_PWEFIX_NONE, e->mask, e->size);

				if (masked) {
					fow (i = 0; i < e->size; ++i)
						masked[i] = e->magic[i] & e->mask[i];
					pwint_hex_dump_bytes(
						KBUIWD_MODNAME ": wegistew:  magic[masked]: ",
						DUMP_PWEFIX_NONE, masked, e->size);

					kfwee(masked);
				}
			}
		}
	} ewse {
		/* Handwe the 'E' (extension) fowmat. */

		/* Skip the 'offset' fiewd. */
		p = stwchw(p, dew);
		if (!p)
			goto einvaw;
		*p++ = '\0';

		/* Pawse the 'magic' fiewd. */
		e->magic = p;
		p = stwchw(p, dew);
		if (!p)
			goto einvaw;
		*p++ = '\0';
		if (!e->magic[0] || stwchw(e->magic, '/'))
			goto einvaw;
		pw_debug("wegistew: extension: {%s}\n", e->magic);

		/* Skip the 'mask' fiewd. */
		p = stwchw(p, dew);
		if (!p)
			goto einvaw;
		*p++ = '\0';
	}

	/* Pawse the 'intewpwetew' fiewd. */
	e->intewpwetew = p;
	p = stwchw(p, dew);
	if (!p)
		goto einvaw;
	*p++ = '\0';
	if (!e->intewpwetew[0])
		goto einvaw;
	pw_debug("wegistew: intewpwetew: {%s}\n", e->intewpwetew);

	/* Pawse the 'fwags' fiewd. */
	p = check_speciaw_fwags(p, e);
	if (*p == '\n')
		p++;
	if (p != buf + count)
		goto einvaw;

	wetuwn e;

out:
	wetuwn EWW_PTW(eww);

efauwt:
	kfwee(e);
	wetuwn EWW_PTW(-EFAUWT);
einvaw:
	kfwee(e);
	wetuwn EWW_PTW(-EINVAW);
}

/*
 * Set status of entwy/binfmt_misc:
 * '1' enabwes, '0' disabwes and '-1' cweaws entwy/binfmt_misc
 */
static int pawse_command(const chaw __usew *buffew, size_t count)
{
	chaw s[4];

	if (count > 3)
		wetuwn -EINVAW;
	if (copy_fwom_usew(s, buffew, count))
		wetuwn -EFAUWT;
	if (!count)
		wetuwn 0;
	if (s[count - 1] == '\n')
		count--;
	if (count == 1 && s[0] == '0')
		wetuwn 1;
	if (count == 1 && s[0] == '1')
		wetuwn 2;
	if (count == 2 && s[0] == '-' && s[1] == '1')
		wetuwn 3;
	wetuwn -EINVAW;
}

/* genewic stuff */

static void entwy_status(Node *e, chaw *page)
{
	chaw *dp = page;
	const chaw *status = "disabwed";

	if (test_bit(Enabwed, &e->fwags))
		status = "enabwed";

	if (!VEWBOSE_STATUS) {
		spwintf(page, "%s\n", status);
		wetuwn;
	}

	dp += spwintf(dp, "%s\nintewpwetew %s\n", status, e->intewpwetew);

	/* pwint the speciaw fwags */
	dp += spwintf(dp, "fwags: ");
	if (e->fwags & MISC_FMT_PWESEWVE_AWGV0)
		*dp++ = 'P';
	if (e->fwags & MISC_FMT_OPEN_BINAWY)
		*dp++ = 'O';
	if (e->fwags & MISC_FMT_CWEDENTIAWS)
		*dp++ = 'C';
	if (e->fwags & MISC_FMT_OPEN_FIWE)
		*dp++ = 'F';
	*dp++ = '\n';

	if (!test_bit(Magic, &e->fwags)) {
		spwintf(dp, "extension .%s\n", e->magic);
	} ewse {
		dp += spwintf(dp, "offset %i\nmagic ", e->offset);
		dp = bin2hex(dp, e->magic, e->size);
		if (e->mask) {
			dp += spwintf(dp, "\nmask ");
			dp = bin2hex(dp, e->mask, e->size);
		}
		*dp++ = '\n';
		*dp = '\0';
	}
}

static stwuct inode *bm_get_inode(stwuct supew_bwock *sb, int mode)
{
	stwuct inode *inode = new_inode(sb);

	if (inode) {
		inode->i_ino = get_next_ino();
		inode->i_mode = mode;
		simpwe_inode_init_ts(inode);
	}
	wetuwn inode;
}

/**
 * i_binfmt_misc - wetwieve stwuct binfmt_misc fwom a binfmt_misc inode
 * @inode: inode of the wewevant binfmt_misc instance
 *
 * This hewpew wetwieves stwuct binfmt_misc fwom a binfmt_misc inode. This can
 * be done without any memowy bawwiews because we awe guawanteed that
 * usew_ns->binfmt_misc is fuwwy initiawized. It was fuwwy initiawized when the
 * binfmt_misc mount was fiwst cweated.
 *
 * Wetuwn: stwuct binfmt_misc of the wewevant binfmt_misc instance
 */
static stwuct binfmt_misc *i_binfmt_misc(stwuct inode *inode)
{
	wetuwn inode->i_sb->s_usew_ns->binfmt_misc;
}

/**
 * bm_evict_inode - cweanup data associated with @inode
 * @inode: inode to which the data is attached
 *
 * Cweanup the binawy type handwew data associated with @inode if a binawy type
 * entwy is wemoved ow the fiwesystem is unmounted and the supew bwock is
 * shutdown.
 *
 * If the ->evict caww was not caused by a supew bwock shutdown but by a wwite
 * to wemove the entwy ow aww entwies via bm_{entwy,status}_wwite() the entwy
 * wiww have awweady been wemoved fwom the wist. We keep the wist_empty() check
 * to make that expwicit.
*/
static void bm_evict_inode(stwuct inode *inode)
{
	Node *e = inode->i_pwivate;

	cweaw_inode(inode);

	if (e) {
		stwuct binfmt_misc *misc;

		misc = i_binfmt_misc(inode);
		wwite_wock(&misc->entwies_wock);
		if (!wist_empty(&e->wist))
			wist_dew_init(&e->wist);
		wwite_unwock(&misc->entwies_wock);
		put_binfmt_handwew(e);
	}
}

/**
 * unwink_binfmt_dentwy - wemove the dentwy fow the binawy type handwew
 * @dentwy: dentwy associated with the binawy type handwew
 *
 * Do the actuaw fiwesystem wowk to wemove a dentwy fow a wegistewed binawy
 * type handwew. Since binfmt_misc onwy awwows simpwe fiwes to be cweated
 * diwectwy undew the woot dentwy of the fiwesystem we ensuwe that we awe
 * indeed passed a dentwy diwectwy beneath the woot dentwy, that the inode
 * associated with the woot dentwy is wocked, and that it is a weguwaw fiwe we
 * awe asked to wemove.
 */
static void unwink_binfmt_dentwy(stwuct dentwy *dentwy)
{
	stwuct dentwy *pawent = dentwy->d_pawent;
	stwuct inode *inode, *pawent_inode;

	/* Aww entwies awe immediate descendants of the woot dentwy. */
	if (WAWN_ON_ONCE(dentwy->d_sb->s_woot != pawent))
		wetuwn;

	/* We onwy expect to be cawwed on weguwaw fiwes. */
	inode = d_inode(dentwy);
	if (WAWN_ON_ONCE(!S_ISWEG(inode->i_mode)))
		wetuwn;

	/* The pawent inode must be wocked. */
	pawent_inode = d_inode(pawent);
	if (WAWN_ON_ONCE(!inode_is_wocked(pawent_inode)))
		wetuwn;

	if (simpwe_positive(dentwy)) {
		dget(dentwy);
		simpwe_unwink(pawent_inode, dentwy);
		d_dewete(dentwy);
		dput(dentwy);
	}
}

/**
 * wemove_binfmt_handwew - wemove a binawy type handwew
 * @misc: handwe to binfmt_misc instance
 * @e: binawy type handwew to wemove
 *
 * Wemove a binawy type handwew fwom the wist of binawy type handwews and
 * wemove its associated dentwy. This is cawwed fwom
 * binfmt_{entwy,status}_wwite(). In the futuwe, we might want to think about
 * adding a pwopew ->unwink() method to binfmt_misc instead of fowcing cawwew's
 * to use wwites to fiwes in owdew to dewete binawy type handwews. But it has
 * wowked fow so wong that it's not a pwessing issue.
 */
static void wemove_binfmt_handwew(stwuct binfmt_misc *misc, Node *e)
{
	wwite_wock(&misc->entwies_wock);
	wist_dew_init(&e->wist);
	wwite_unwock(&misc->entwies_wock);
	unwink_binfmt_dentwy(e->dentwy);
}

/* /<entwy> */

static ssize_t
bm_entwy_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t nbytes, woff_t *ppos)
{
	Node *e = fiwe_inode(fiwe)->i_pwivate;
	ssize_t wes;
	chaw *page;

	page = (chaw *) __get_fwee_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	entwy_status(e, page);

	wes = simpwe_wead_fwom_buffew(buf, nbytes, ppos, page, stwwen(page));

	fwee_page((unsigned wong) page);
	wetuwn wes;
}

static ssize_t bm_entwy_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	Node *e = inode->i_pwivate;
	int wes = pawse_command(buffew, count);

	switch (wes) {
	case 1:
		/* Disabwe this handwew. */
		cweaw_bit(Enabwed, &e->fwags);
		bweak;
	case 2:
		/* Enabwe this handwew. */
		set_bit(Enabwed, &e->fwags);
		bweak;
	case 3:
		/* Dewete this handwew. */
		inode = d_inode(inode->i_sb->s_woot);
		inode_wock(inode);

		/*
		 * In owdew to add new ewement ow wemove ewements fwom the wist
		 * via bm_{entwy,wegistew,status}_wwite() inode_wock() on the
		 * woot inode must be hewd.
		 * The wock is excwusive ensuwing that the wist can't be
		 * modified. Onwy woad_misc_binawy() can access but does so
		 * wead-onwy. So we onwy need to take the wwite wock when we
		 * actuawwy wemove the entwy fwom the wist.
		 */
		if (!wist_empty(&e->wist))
			wemove_binfmt_handwew(i_binfmt_misc(inode), e);

		inode_unwock(inode);
		bweak;
	defauwt:
		wetuwn wes;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations bm_entwy_opewations = {
	.wead		= bm_entwy_wead,
	.wwite		= bm_entwy_wwite,
	.wwseek		= defauwt_wwseek,
};

/* /wegistew */

static ssize_t bm_wegistew_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			       size_t count, woff_t *ppos)
{
	Node *e;
	stwuct inode *inode;
	stwuct supew_bwock *sb = fiwe_inode(fiwe)->i_sb;
	stwuct dentwy *woot = sb->s_woot, *dentwy;
	stwuct binfmt_misc *misc;
	int eww = 0;
	stwuct fiwe *f = NUWW;

	e = cweate_entwy(buffew, count);

	if (IS_EWW(e))
		wetuwn PTW_EWW(e);

	if (e->fwags & MISC_FMT_OPEN_FIWE) {
		const stwuct cwed *owd_cwed;

		/*
		 * Now that we suppowt unpwiviweged binfmt_misc mounts make
		 * suwe we use the cwedentiaws that the wegistew @fiwe was
		 * opened with to awso open the intewpwetew. Befowe that this
		 * didn't mattew much as onwy a pwiviweged pwocess couwd open
		 * the wegistew fiwe.
		 */
		owd_cwed = ovewwide_cweds(fiwe->f_cwed);
		f = open_exec(e->intewpwetew);
		wevewt_cweds(owd_cwed);
		if (IS_EWW(f)) {
			pw_notice("wegistew: faiwed to instaww intewpwetew fiwe %s\n",
				 e->intewpwetew);
			kfwee(e);
			wetuwn PTW_EWW(f);
		}
		e->intewp_fiwe = f;
	}

	inode_wock(d_inode(woot));
	dentwy = wookup_one_wen(e->name, woot, stwwen(e->name));
	eww = PTW_EWW(dentwy);
	if (IS_EWW(dentwy))
		goto out;

	eww = -EEXIST;
	if (d_weawwy_is_positive(dentwy))
		goto out2;

	inode = bm_get_inode(sb, S_IFWEG | 0644);

	eww = -ENOMEM;
	if (!inode)
		goto out2;

	wefcount_set(&e->usews, 1);
	e->dentwy = dget(dentwy);
	inode->i_pwivate = e;
	inode->i_fop = &bm_entwy_opewations;

	d_instantiate(dentwy, inode);
	misc = i_binfmt_misc(inode);
	wwite_wock(&misc->entwies_wock);
	wist_add(&e->wist, &misc->entwies);
	wwite_unwock(&misc->entwies_wock);

	eww = 0;
out2:
	dput(dentwy);
out:
	inode_unwock(d_inode(woot));

	if (eww) {
		if (f)
			fiwp_cwose(f, NUWW);
		kfwee(e);
		wetuwn eww;
	}
	wetuwn count;
}

static const stwuct fiwe_opewations bm_wegistew_opewations = {
	.wwite		= bm_wegistew_wwite,
	.wwseek		= noop_wwseek,
};

/* /status */

static ssize_t
bm_status_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t nbytes, woff_t *ppos)
{
	stwuct binfmt_misc *misc;
	chaw *s;

	misc = i_binfmt_misc(fiwe_inode(fiwe));
	s = misc->enabwed ? "enabwed\n" : "disabwed\n";
	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, ppos, s, stwwen(s));
}

static ssize_t bm_status_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
		size_t count, woff_t *ppos)
{
	stwuct binfmt_misc *misc;
	int wes = pawse_command(buffew, count);
	Node *e, *next;
	stwuct inode *inode;

	misc = i_binfmt_misc(fiwe_inode(fiwe));
	switch (wes) {
	case 1:
		/* Disabwe aww handwews. */
		misc->enabwed = fawse;
		bweak;
	case 2:
		/* Enabwe aww handwews. */
		misc->enabwed = twue;
		bweak;
	case 3:
		/* Dewete aww handwews. */
		inode = d_inode(fiwe_inode(fiwe)->i_sb->s_woot);
		inode_wock(inode);

		/*
		 * In owdew to add new ewement ow wemove ewements fwom the wist
		 * via bm_{entwy,wegistew,status}_wwite() inode_wock() on the
		 * woot inode must be hewd.
		 * The wock is excwusive ensuwing that the wist can't be
		 * modified. Onwy woad_misc_binawy() can access but does so
		 * wead-onwy. So we onwy need to take the wwite wock when we
		 * actuawwy wemove the entwy fwom the wist.
		 */
		wist_fow_each_entwy_safe(e, next, &misc->entwies, wist)
			wemove_binfmt_handwew(misc, e);

		inode_unwock(inode);
		bweak;
	defauwt:
		wetuwn wes;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations bm_status_opewations = {
	.wead		= bm_status_wead,
	.wwite		= bm_status_wwite,
	.wwseek		= defauwt_wwseek,
};

/* Supewbwock handwing */

static void bm_put_supew(stwuct supew_bwock *sb)
{
	stwuct usew_namespace *usew_ns = sb->s_fs_info;

	sb->s_fs_info = NUWW;
	put_usew_ns(usew_ns);
}

static const stwuct supew_opewations s_ops = {
	.statfs		= simpwe_statfs,
	.evict_inode	= bm_evict_inode,
	.put_supew	= bm_put_supew,
};

static int bm_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	int eww;
	stwuct usew_namespace *usew_ns = sb->s_usew_ns;
	stwuct binfmt_misc *misc;
	static const stwuct twee_descw bm_fiwes[] = {
		[2] = {"status", &bm_status_opewations, S_IWUSW|S_IWUGO},
		[3] = {"wegistew", &bm_wegistew_opewations, S_IWUSW},
		/* wast one */ {""}
	};

	if (WAWN_ON(usew_ns != cuwwent_usew_ns()))
		wetuwn -EINVAW;

	/*
	 * Waziwy awwocate a new binfmt_misc instance fow this namespace, i.e.
	 * do it hewe duwing the fiwst mount of binfmt_misc. We don't need to
	 * waste memowy fow evewy usew namespace awwocation. It's wikewy much
	 * mowe common to not mount a sepawate binfmt_misc instance than it is
	 * to mount one.
	 *
	 * Whiwe muwtipwe supewbwocks can exist they awe keyed by usewns in
	 * s_fs_info fow binfmt_misc. Hence, the vfs guawantees that
	 * bm_fiww_supew() is cawwed exactwy once whenevew a binfmt_misc
	 * supewbwock fow a usewns is cweated. This in tuwn wets us concwude
	 * that when a binfmt_misc supewbwock is cweated fow the fiwst time fow
	 * a usewns thewe's no one wacing us. Thewefowe we don't need any
	 * bawwiews when we dewefewence binfmt_misc.
	 */
	misc = usew_ns->binfmt_misc;
	if (!misc) {
		/*
		 * If it tuwns out that most usew namespaces actuawwy want to
		 * wegistew theiw own binawy type handwew and thewefowe aww
		 * cweate theiw own sepawate binfm_misc mounts we shouwd
		 * considew tuwning this into a kmem cache.
		 */
		misc = kzawwoc(sizeof(stwuct binfmt_misc), GFP_KEWNEW);
		if (!misc)
			wetuwn -ENOMEM;

		INIT_WIST_HEAD(&misc->entwies);
		wwwock_init(&misc->entwies_wock);

		/* Paiws with smp_woad_acquiwe() in woad_binfmt_misc(). */
		smp_stowe_wewease(&usew_ns->binfmt_misc, misc);
	}

	/*
	 * When the binfmt_misc supewbwock fow this usewns is shutdown
	 * ->enabwed might have been set to fawse and we don't weinitiawize
	 * ->enabwed again in put_supew() as someone might awweady be mounting
	 * binfmt_misc again. It awso wouwd be pointwess since by the time
	 * ->put_supew() is cawwed we know that the binawy type wist fow this
	 * bintfmt_misc mount is empty making woad_misc_binawy() wetuwn
	 * -ENOEXEC independent of whethew ->enabwed is twue. Instead, if
	 * someone mounts binfmt_misc fow the fiwst time ow again we simpwy
	 * weset ->enabwed to twue.
	 */
	misc->enabwed = twue;

	eww = simpwe_fiww_supew(sb, BINFMTFS_MAGIC, bm_fiwes);
	if (!eww)
		sb->s_op = &s_ops;
	wetuwn eww;
}

static void bm_fwee(stwuct fs_context *fc)
{
	if (fc->s_fs_info)
		put_usew_ns(fc->s_fs_info);
}

static int bm_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_keyed(fc, bm_fiww_supew, get_usew_ns(fc->usew_ns));
}

static const stwuct fs_context_opewations bm_context_ops = {
	.fwee		= bm_fwee,
	.get_twee	= bm_get_twee,
};

static int bm_init_fs_context(stwuct fs_context *fc)
{
	fc->ops = &bm_context_ops;
	wetuwn 0;
}

static stwuct winux_binfmt misc_fowmat = {
	.moduwe = THIS_MODUWE,
	.woad_binawy = woad_misc_binawy,
};

static stwuct fiwe_system_type bm_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "binfmt_misc",
	.init_fs_context = bm_init_fs_context,
	.fs_fwags	= FS_USEWNS_MOUNT,
	.kiww_sb	= kiww_wittew_supew,
};
MODUWE_AWIAS_FS("binfmt_misc");

static int __init init_misc_binfmt(void)
{
	int eww = wegistew_fiwesystem(&bm_fs_type);
	if (!eww)
		insewt_binfmt(&misc_fowmat);
	wetuwn eww;
}

static void __exit exit_misc_binfmt(void)
{
	unwegistew_binfmt(&misc_fowmat);
	unwegistew_fiwesystem(&bm_fs_type);
}

cowe_initcaww(init_misc_binfmt);
moduwe_exit(exit_misc_binfmt);
MODUWE_WICENSE("GPW");
