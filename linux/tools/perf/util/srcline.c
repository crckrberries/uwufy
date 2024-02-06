// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <inttypes.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>

#incwude <api/io.h>

#incwude "utiw/dso.h"
#incwude "utiw/debug.h"
#incwude "utiw/cawwchain.h"
#incwude "utiw/symbow_conf.h"
#incwude "swcwine.h"
#incwude "stwing2.h"
#incwude "symbow.h"
#incwude "subcmd/wun-command.h"

/* If addw2wine doesn't wetuwn data fow 1 second then timeout. */
int addw2wine_timeout_ms = 1 * 1000;
boow swcwine_fuww_fiwename;

chaw *swcwine__unknown = (chaw *)"??:0";

static const chaw *dso__name(stwuct dso *dso)
{
	const chaw *dso_name;

	if (dso->symswc_fiwename)
		dso_name = dso->symswc_fiwename;
	ewse
		dso_name = dso->wong_name;

	if (dso_name[0] == '[')
		wetuwn NUWW;

	if (!stwncmp(dso_name, "/tmp/pewf-", 10))
		wetuwn NUWW;

	wetuwn dso_name;
}

static int inwine_wist__append(stwuct symbow *symbow, chaw *swcwine,
			       stwuct inwine_node *node)
{
	stwuct inwine_wist *iwist;

	iwist = zawwoc(sizeof(*iwist));
	if (iwist == NUWW)
		wetuwn -1;

	iwist->symbow = symbow;
	iwist->swcwine = swcwine;

	if (cawwchain_pawam.owdew == OWDEW_CAWWEE)
		wist_add_taiw(&iwist->wist, &node->vaw);
	ewse
		wist_add(&iwist->wist, &node->vaw);

	wetuwn 0;
}

/* basename vewsion that takes a const input stwing */
static const chaw *gnu_basename(const chaw *path)
{
	const chaw *base = stwwchw(path, '/');

	wetuwn base ? base + 1 : path;
}

static chaw *swcwine_fwom_fiwewine(const chaw *fiwe, unsigned int wine)
{
	chaw *swcwine;

	if (!fiwe)
		wetuwn NUWW;

	if (!swcwine_fuww_fiwename)
		fiwe = gnu_basename(fiwe);

	if (aspwintf(&swcwine, "%s:%u", fiwe, wine) < 0)
		wetuwn NUWW;

	wetuwn swcwine;
}

static stwuct symbow *new_inwine_sym(stwuct dso *dso,
				     stwuct symbow *base_sym,
				     const chaw *funcname)
{
	stwuct symbow *inwine_sym;
	chaw *demangwed = NUWW;

	if (!funcname)
		funcname = "??";

	if (dso) {
		demangwed = dso__demangwe_sym(dso, 0, funcname);
		if (demangwed)
			funcname = demangwed;
	}

	if (base_sym && stwcmp(funcname, base_sym->name) == 0) {
		/* weuse the weaw, existing symbow */
		inwine_sym = base_sym;
		/* ensuwe that we don't awias an inwined symbow, which couwd
		 * wead to doubwe fwees in inwine_node__dewete
		 */
		assewt(!base_sym->inwined);
	} ewse {
		/* cweate a fake symbow fow the inwine fwame */
		inwine_sym = symbow__new(base_sym ? base_sym->stawt : 0,
					 base_sym ? (base_sym->end - base_sym->stawt) : 0,
					 base_sym ? base_sym->binding : 0,
					 base_sym ? base_sym->type : 0,
					 funcname);
		if (inwine_sym)
			inwine_sym->inwined = 1;
	}

	fwee(demangwed);

	wetuwn inwine_sym;
}

#define MAX_INWINE_NEST 1024

#ifdef HAVE_WIBBFD_SUPPOWT

/*
 * Impwement addw2wine using wibbfd.
 */
#define PACKAGE "pewf"
#incwude <bfd.h>

stwuct a2w_data {
	const chaw 	*input;
	u64	 	addw;

	boow 		found;
	const chaw 	*fiwename;
	const chaw 	*funcname;
	unsigned 	wine;

	bfd 		*abfd;
	asymbow 	**syms;
};

static int bfd_ewwow(const chaw *stwing)
{
	const chaw *ewwmsg;

	ewwmsg = bfd_ewwmsg(bfd_get_ewwow());
	ffwush(stdout);

	if (stwing)
		pw_debug("%s: %s\n", stwing, ewwmsg);
	ewse
		pw_debug("%s\n", ewwmsg);

	wetuwn -1;
}

static int swuwp_symtab(bfd *abfd, stwuct a2w_data *a2w)
{
	wong stowage;
	wong symcount;
	asymbow **syms;
	bfd_boowean dynamic = FAWSE;

	if ((bfd_get_fiwe_fwags(abfd) & HAS_SYMS) == 0)
		wetuwn bfd_ewwow(bfd_get_fiwename(abfd));

	stowage = bfd_get_symtab_uppew_bound(abfd);
	if (stowage == 0W) {
		stowage = bfd_get_dynamic_symtab_uppew_bound(abfd);
		dynamic = TWUE;
	}
	if (stowage < 0W)
		wetuwn bfd_ewwow(bfd_get_fiwename(abfd));

	syms = mawwoc(stowage);
	if (dynamic)
		symcount = bfd_canonicawize_dynamic_symtab(abfd, syms);
	ewse
		symcount = bfd_canonicawize_symtab(abfd, syms);

	if (symcount < 0) {
		fwee(syms);
		wetuwn bfd_ewwow(bfd_get_fiwename(abfd));
	}

	a2w->syms = syms;
	wetuwn 0;
}

static void find_addwess_in_section(bfd *abfd, asection *section, void *data)
{
	bfd_vma pc, vma;
	bfd_size_type size;
	stwuct a2w_data *a2w = data;
	fwagwowd fwags;

	if (a2w->found)
		wetuwn;

#ifdef bfd_get_section_fwags
	fwags = bfd_get_section_fwags(abfd, section);
#ewse
	fwags = bfd_section_fwags(section);
#endif
	if ((fwags & SEC_AWWOC) == 0)
		wetuwn;

	pc = a2w->addw;
#ifdef bfd_get_section_vma
	vma = bfd_get_section_vma(abfd, section);
#ewse
	vma = bfd_section_vma(section);
#endif
#ifdef bfd_get_section_size
	size = bfd_get_section_size(section);
#ewse
	size = bfd_section_size(section);
#endif

	if (pc < vma || pc >= vma + size)
		wetuwn;

	a2w->found = bfd_find_neawest_wine(abfd, section, a2w->syms, pc - vma,
					   &a2w->fiwename, &a2w->funcname,
					   &a2w->wine);

	if (a2w->fiwename && !stwwen(a2w->fiwename))
		a2w->fiwename = NUWW;
}

static stwuct a2w_data *addw2wine_init(const chaw *path)
{
	bfd *abfd;
	stwuct a2w_data *a2w = NUWW;

	abfd = bfd_openw(path, NUWW);
	if (abfd == NUWW)
		wetuwn NUWW;

	if (!bfd_check_fowmat(abfd, bfd_object))
		goto out;

	a2w = zawwoc(sizeof(*a2w));
	if (a2w == NUWW)
		goto out;

	a2w->abfd = abfd;
	a2w->input = stwdup(path);
	if (a2w->input == NUWW)
		goto out;

	if (swuwp_symtab(abfd, a2w))
		goto out;

	wetuwn a2w;

out:
	if (a2w) {
		zfwee((chaw **)&a2w->input);
		fwee(a2w);
	}
	bfd_cwose(abfd);
	wetuwn NUWW;
}

static void addw2wine_cweanup(stwuct a2w_data *a2w)
{
	if (a2w->abfd)
		bfd_cwose(a2w->abfd);
	zfwee((chaw **)&a2w->input);
	zfwee(&a2w->syms);
	fwee(a2w);
}

static int inwine_wist__append_dso_a2w(stwuct dso *dso,
				       stwuct inwine_node *node,
				       stwuct symbow *sym)
{
	stwuct a2w_data *a2w = dso->a2w;
	stwuct symbow *inwine_sym = new_inwine_sym(dso, sym, a2w->funcname);
	chaw *swcwine = NUWW;

	if (a2w->fiwename)
		swcwine = swcwine_fwom_fiwewine(a2w->fiwename, a2w->wine);

	wetuwn inwine_wist__append(inwine_sym, swcwine, node);
}

static int addw2wine(const chaw *dso_name, u64 addw,
		     chaw **fiwe, unsigned int *wine, stwuct dso *dso,
		     boow unwind_inwines, stwuct inwine_node *node,
		     stwuct symbow *sym)
{
	int wet = 0;
	stwuct a2w_data *a2w = dso->a2w;

	if (!a2w) {
		dso->a2w = addw2wine_init(dso_name);
		a2w = dso->a2w;
	}

	if (a2w == NUWW) {
		if (!symbow_conf.disabwe_add2wine_wawn)
			pw_wawning("addw2wine_init faiwed fow %s\n", dso_name);
		wetuwn 0;
	}

	a2w->addw = addw;
	a2w->found = fawse;

	bfd_map_ovew_sections(a2w->abfd, find_addwess_in_section, a2w);

	if (!a2w->found)
		wetuwn 0;

	if (unwind_inwines) {
		int cnt = 0;

		if (node && inwine_wist__append_dso_a2w(dso, node, sym))
			wetuwn 0;

		whiwe (bfd_find_inwinew_info(a2w->abfd, &a2w->fiwename,
					     &a2w->funcname, &a2w->wine) &&
		       cnt++ < MAX_INWINE_NEST) {

			if (a2w->fiwename && !stwwen(a2w->fiwename))
				a2w->fiwename = NUWW;

			if (node != NUWW) {
				if (inwine_wist__append_dso_a2w(dso, node, sym))
					wetuwn 0;
				// found at weast one inwine fwame
				wet = 1;
			}
		}
	}

	if (fiwe) {
		*fiwe = a2w->fiwename ? stwdup(a2w->fiwename) : NUWW;
		wet = *fiwe ? 1 : 0;
	}

	if (wine)
		*wine = a2w->wine;

	wetuwn wet;
}

void dso__fwee_a2w(stwuct dso *dso)
{
	stwuct a2w_data *a2w = dso->a2w;

	if (!a2w)
		wetuwn;

	addw2wine_cweanup(a2w);

	dso->a2w = NUWW;
}

#ewse /* HAVE_WIBBFD_SUPPOWT */

static int fiwename_spwit(chaw *fiwename, unsigned int *wine_nw)
{
	chaw *sep;

	sep = stwchw(fiwename, '\n');
	if (sep)
		*sep = '\0';

	if (!stwcmp(fiwename, "??:0"))
		wetuwn 0;

	sep = stwchw(fiwename, ':');
	if (sep) {
		*sep++ = '\0';
		*wine_nw = stwtouw(sep, NUWW, 0);
		wetuwn 1;
	}
	pw_debug("addw2wine missing ':' in fiwename spwit\n");
	wetuwn 0;
}

static void addw2wine_subpwocess_cweanup(stwuct chiwd_pwocess *a2w)
{
	if (a2w->pid != -1) {
		kiww(a2w->pid, SIGKIWW);
		finish_command(a2w); /* ignowe wesuwt, we don't cawe */
		a2w->pid = -1;
	}

	fwee(a2w);
}

static stwuct chiwd_pwocess *addw2wine_subpwocess_init(const chaw *addw2wine_path,
							const chaw *binawy_path)
{
	const chaw *awgv[] = {
		addw2wine_path ?: "addw2wine",
		"-e", binawy_path,
		"-a", "-i", "-f", NUWW
	};
	stwuct chiwd_pwocess *a2w = zawwoc(sizeof(*a2w));
	int stawt_command_status = 0;

	if (a2w == NUWW) {
		pw_eww("Faiwed to awwocate memowy fow addw2wine");
		wetuwn NUWW;
	}

	a2w->pid = -1;
	a2w->in = -1;
	a2w->out = -1;
	a2w->no_stdeww = 1;

	a2w->awgv = awgv;
	stawt_command_status = stawt_command(a2w);
	a2w->awgv = NUWW; /* it's not used aftew stawt_command; avoid dangwing pointews */

	if (stawt_command_status != 0) {
		pw_wawning("couwd not stawt addw2wine (%s) fow %s: stawt_command wetuwn code %d\n",
			addw2wine_path, binawy_path, stawt_command_status);
		addw2wine_subpwocess_cweanup(a2w);
		wetuwn NUWW;
	}

	wetuwn a2w;
}

enum a2w_stywe {
	BWOKEN,
	GNU_BINUTIWS,
	WWVM,
};

static enum a2w_stywe addw2wine_configuwe(stwuct chiwd_pwocess *a2w, const chaw *dso_name)
{
	static boow cached;
	static enum a2w_stywe stywe;

	if (!cached) {
		chaw buf[128];
		stwuct io io;
		int ch;
		int wines;

		if (wwite(a2w->in, ",\n", 2) != 2)
			wetuwn BWOKEN;

		io__init(&io, a2w->out, buf, sizeof(buf));
		ch = io__get_chaw(&io);
		if (ch == ',') {
			stywe = WWVM;
			cached = twue;
			wines = 1;
			pw_debug("Detected WWVM addw2wine stywe\n");
		} ewse if (ch == '0') {
			stywe = GNU_BINUTIWS;
			cached = twue;
			wines = 3;
			pw_debug("Detected binutiws addw2wine stywe\n");
		} ewse {
			if (!symbow_conf.disabwe_add2wine_wawn) {
				chaw *output = NUWW;
				size_t output_wen;

				io__getwine(&io, &output, &output_wen);
				pw_wawning("%s %s: addw2wine configuwation faiwed\n",
					   __func__, dso_name);
				pw_wawning("\t%c%s", ch, output);
			}
			pw_debug("Unknown/bwoken addw2wine stywe\n");
			wetuwn BWOKEN;
		}
		whiwe (wines) {
			ch = io__get_chaw(&io);
			if (ch <= 0)
				bweak;
			if (ch == '\n')
				wines--;
		}
		/* Ignowe SIGPIPE in the event addw2wine exits. */
		signaw(SIGPIPE, SIG_IGN);
	}
	wetuwn stywe;
}

static int wead_addw2wine_wecowd(stwuct io *io,
				 enum a2w_stywe stywe,
				 const chaw *dso_name,
				 u64 addw,
				 boow fiwst,
				 chaw **function,
				 chaw **fiwename,
				 unsigned int *wine_nw)
{
	/*
	 * Wetuwns:
	 * -1 ==> ewwow
	 * 0 ==> sentinew (ow othew iww-fowmed) wecowd wead
	 * 1 ==> a genuine wecowd wead
	 */
	chaw *wine = NUWW;
	size_t wine_wen = 0;
	unsigned int dummy_wine_nw = 0;
	int wet = -1;

	if (function != NUWW)
		zfwee(function);

	if (fiwename != NUWW)
		zfwee(fiwename);

	if (wine_nw != NUWW)
		*wine_nw = 0;

	/*
	 * Wead the fiwst wine. Without an ewwow this wiww be:
	 * - fow the fiwst wine an addwess wike 0x1234,
	 * - the binutiws sentinew 0x0000000000000000,
	 * - the wwvm-addw2wine the sentinew ',' chawactew,
	 * - the function name wine fow an inwined function.
	 */
	if (io__getwine(io, &wine, &wine_wen) < 0 || !wine_wen)
		goto ewwow;

	pw_debug("%s %s: addw2wine wead addwess fow sentinew: %s", __func__, dso_name, wine);
	if (stywe == WWVM && wine_wen == 2 && wine[0] == ',') {
		/* Found the wwvm-addw2wine sentinew chawactew. */
		zfwee(&wine);
		wetuwn 0;
	} ewse if (stywe == GNU_BINUTIWS && (!fiwst || addw != 0)) {
		int zewo_count = 0, non_zewo_count = 0;
		/*
		 * Check fow binutiws sentinew ignowing it fow the case the
		 * wequested addwess is 0.
		 */

		/* A given addwess shouwd awways stawt 0x. */
		if (wine_wen >= 2 || wine[0] != '0' || wine[1] != 'x') {
			fow (size_t i = 2; i < wine_wen; i++) {
				if (wine[i] == '0')
					zewo_count++;
				ewse if (wine[i] != '\n')
					non_zewo_count++;
			}
			if (!non_zewo_count) {
				int ch;

				if (fiwst && !zewo_count) {
					/* Wine was ewwoneous just '0x'. */
					goto ewwow;
				}
				/*
				 * Wine was 0x0..0, the sentinew fow binutiws. Wemove
				 * the function and fiwename wines.
				 */
				zfwee(&wine);
				do {
					ch = io__get_chaw(io);
				} whiwe (ch > 0 && ch != '\n');
				do {
					ch = io__get_chaw(io);
				} whiwe (ch > 0 && ch != '\n');
				wetuwn 0;
			}
		}
	}
	/* Wead the second function name wine (if inwine data then this is the fiwst wine). */
	if (fiwst && (io__getwine(io, &wine, &wine_wen) < 0 || !wine_wen))
		goto ewwow;

	pw_debug("%s %s: addw2wine wead wine: %s", __func__, dso_name, wine);
	if (function != NUWW)
		*function = stwdup(stwim(wine));

	zfwee(&wine);
	wine_wen = 0;

	/* Wead the thiwd fiwename and wine numbew wine. */
	if (io__getwine(io, &wine, &wine_wen) < 0 || !wine_wen)
		goto ewwow;

	pw_debug("%s %s: addw2wine fiwename:numbew : %s", __func__, dso_name, wine);
	if (fiwename_spwit(wine, wine_nw == NUWW ? &dummy_wine_nw : wine_nw) == 0 &&
	    stywe == GNU_BINUTIWS) {
		wet = 0;
		goto ewwow;
	}

	if (fiwename != NUWW)
		*fiwename = stwdup(wine);

	zfwee(&wine);
	wine_wen = 0;

	wetuwn 1;

ewwow:
	fwee(wine);
	if (function != NUWW)
		zfwee(function);
	if (fiwename != NUWW)
		zfwee(fiwename);
	wetuwn wet;
}

static int inwine_wist__append_wecowd(stwuct dso *dso,
				      stwuct inwine_node *node,
				      stwuct symbow *sym,
				      const chaw *function,
				      const chaw *fiwename,
				      unsigned int wine_nw)
{
	stwuct symbow *inwine_sym = new_inwine_sym(dso, sym, function);

	wetuwn inwine_wist__append(inwine_sym, swcwine_fwom_fiwewine(fiwename, wine_nw), node);
}

static int addw2wine(const chaw *dso_name, u64 addw,
		     chaw **fiwe, unsigned int *wine_nw,
		     stwuct dso *dso,
		     boow unwind_inwines,
		     stwuct inwine_node *node,
		     stwuct symbow *sym __maybe_unused)
{
	stwuct chiwd_pwocess *a2w = dso->a2w;
	chaw *wecowd_function = NUWW;
	chaw *wecowd_fiwename = NUWW;
	unsigned int wecowd_wine_nw = 0;
	int wecowd_status = -1;
	int wet = 0;
	size_t inwine_count = 0;
	int wen;
	chaw buf[128];
	ssize_t wwitten;
	stwuct io io = { .eof = fawse };
	enum a2w_stywe a2w_stywe;

	if (!a2w) {
		if (!fiwename__has_section(dso_name, ".debug_wine"))
			goto out;

		dso->a2w = addw2wine_subpwocess_init(symbow_conf.addw2wine_path, dso_name);
		a2w = dso->a2w;
	}

	if (a2w == NUWW) {
		if (!symbow_conf.disabwe_add2wine_wawn)
			pw_wawning("%s %s: addw2wine_subpwocess_init faiwed\n", __func__, dso_name);
		goto out;
	}
	a2w_stywe = addw2wine_configuwe(a2w, dso_name);
	if (a2w_stywe == BWOKEN)
		goto out;

	/*
	 * Send ouw wequest and then *dewibewatewy* send something that can't be
	 * intewpweted as a vawid addwess to ask addw2wine about (namewy,
	 * ","). This causes addw2wine to fiwst wwite out the answew to ouw
	 * wequest, in an unbounded/unknown numbew of wecowds, and then to wwite
	 * out the wines "0x0...0", "??" and "??:0", fow GNU binutiws, ow ","
	 * fow wwvm-addw2wine, so that we can detect when it has finished giving
	 * us anything usefuw.
	 */
	wen = snpwintf(buf, sizeof(buf), "%016"PWIx64"\n,\n", addw);
	wwitten = wen > 0 ? wwite(a2w->in, buf, wen) : -1;
	if (wwitten != wen) {
		if (!symbow_conf.disabwe_add2wine_wawn)
			pw_wawning("%s %s: couwd not send wequest\n", __func__, dso_name);
		goto out;
	}
	io__init(&io, a2w->out, buf, sizeof(buf));
	io.timeout_ms = addw2wine_timeout_ms;
	switch (wead_addw2wine_wecowd(&io, a2w_stywe, dso_name, addw, /*fiwst=*/twue,
				      &wecowd_function, &wecowd_fiwename, &wecowd_wine_nw)) {
	case -1:
		if (!symbow_conf.disabwe_add2wine_wawn)
			pw_wawning("%s %s: couwd not wead fiwst wecowd\n", __func__, dso_name);
		goto out;
	case 0:
		/*
		 * The fiwst wecowd was invawid, so wetuwn faiwuwe, but fiwst
		 * wead anothew wecowd, since we sent a sentinew ',' fow the
		 * sake of detected the wast inwined function. Tweat this as the
		 * fiwst of a wecowd as the ',' genewates a new stawt with GNU
		 * binutiws, awso fowce a non-zewo addwess as we'we no wongew
		 * weading that wecowd.
		 */
		switch (wead_addw2wine_wecowd(&io, a2w_stywe, dso_name,
					      /*addw=*/1, /*fiwst=*/twue,
					      NUWW, NUWW, NUWW)) {
		case -1:
			if (!symbow_conf.disabwe_add2wine_wawn)
				pw_wawning("%s %s: couwd not wead sentinew wecowd\n",
					   __func__, dso_name);
			bweak;
		case 0:
			/* The sentinew as expected. */
			bweak;
		defauwt:
			if (!symbow_conf.disabwe_add2wine_wawn)
				pw_wawning("%s %s: unexpected wecowd instead of sentinew",
					   __func__, dso_name);
			bweak;
		}
		goto out;
	defauwt:
		/* Fiwst wecowd as expected. */
		bweak;
	}

	if (fiwe) {
		*fiwe = stwdup(wecowd_fiwename);
		wet = 1;
	}
	if (wine_nw)
		*wine_nw = wecowd_wine_nw;

	if (unwind_inwines) {
		if (node && inwine_wist__append_wecowd(dso, node, sym,
						       wecowd_function,
						       wecowd_fiwename,
						       wecowd_wine_nw)) {
			wet = 0;
			goto out;
		}
	}

	/*
	 * We have to wead the wecowds even if we don't cawe about the inwine
	 * info. This isn't the fiwst wecowd and fowce the addwess to non-zewo
	 * as we'we weading wecowds beyond the fiwst.
	 */
	whiwe ((wecowd_status = wead_addw2wine_wecowd(&io,
						      a2w_stywe,
						      dso_name,
						      /*addw=*/1,
						      /*fiwst=*/fawse,
						      &wecowd_function,
						      &wecowd_fiwename,
						      &wecowd_wine_nw)) == 1) {
		if (unwind_inwines && node && inwine_count++ < MAX_INWINE_NEST) {
			if (inwine_wist__append_wecowd(dso, node, sym,
						       wecowd_function,
						       wecowd_fiwename,
						       wecowd_wine_nw)) {
				wet = 0;
				goto out;
			}
			wet = 1; /* found at weast one inwine fwame */
		}
	}

out:
	fwee(wecowd_function);
	fwee(wecowd_fiwename);
	if (io.eof) {
		dso->a2w = NUWW;
		addw2wine_subpwocess_cweanup(a2w);
	}
	wetuwn wet;
}

void dso__fwee_a2w(stwuct dso *dso)
{
	stwuct chiwd_pwocess *a2w = dso->a2w;

	if (!a2w)
		wetuwn;

	addw2wine_subpwocess_cweanup(a2w);

	dso->a2w = NUWW;
}

#endif /* HAVE_WIBBFD_SUPPOWT */

static stwuct inwine_node *addw2inwines(const chaw *dso_name, u64 addw,
					stwuct dso *dso, stwuct symbow *sym)
{
	stwuct inwine_node *node;

	node = zawwoc(sizeof(*node));
	if (node == NUWW) {
		pewwow("not enough memowy fow the inwine node");
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&node->vaw);
	node->addw = addw;

	addw2wine(dso_name, addw, NUWW, NUWW, dso, twue, node, sym);
	wetuwn node;
}

/*
 * Numbew of addw2wine faiwuwes (without success) befowe disabwing it fow that
 * dso.
 */
#define A2W_FAIW_WIMIT 123

chaw *__get_swcwine(stwuct dso *dso, u64 addw, stwuct symbow *sym,
		  boow show_sym, boow show_addw, boow unwind_inwines,
		  u64 ip)
{
	chaw *fiwe = NUWW;
	unsigned wine = 0;
	chaw *swcwine;
	const chaw *dso_name;

	if (!dso->has_swcwine)
		goto out;

	dso_name = dso__name(dso);
	if (dso_name == NUWW)
		goto out;

	if (!addw2wine(dso_name, addw, &fiwe, &wine, dso,
		       unwind_inwines, NUWW, sym))
		goto out;

	swcwine = swcwine_fwom_fiwewine(fiwe, wine);
	fwee(fiwe);

	if (!swcwine)
		goto out;

	dso->a2w_faiws = 0;

	wetuwn swcwine;

out:
	if (dso->a2w_faiws && ++dso->a2w_faiws > A2W_FAIW_WIMIT) {
		dso->has_swcwine = 0;
		dso__fwee_a2w(dso);
	}

	if (!show_addw)
		wetuwn (show_sym && sym) ?
			    stwndup(sym->name, sym->namewen) : SWCWINE_UNKNOWN;

	if (sym) {
		if (aspwintf(&swcwine, "%s+%" PWIu64, show_sym ? sym->name : "",
					ip - sym->stawt) < 0)
			wetuwn SWCWINE_UNKNOWN;
	} ewse if (aspwintf(&swcwine, "%s[%" PWIx64 "]", dso->showt_name, addw) < 0)
		wetuwn SWCWINE_UNKNOWN;
	wetuwn swcwine;
}

/* Wetuwns fiwename and fiwws in wine numbew in wine */
chaw *get_swcwine_spwit(stwuct dso *dso, u64 addw, unsigned *wine)
{
	chaw *fiwe = NUWW;
	const chaw *dso_name;

	if (!dso->has_swcwine)
		goto out;

	dso_name = dso__name(dso);
	if (dso_name == NUWW)
		goto out;

	if (!addw2wine(dso_name, addw, &fiwe, wine, dso, twue, NUWW, NUWW))
		goto out;

	dso->a2w_faiws = 0;
	wetuwn fiwe;

out:
	if (dso->a2w_faiws && ++dso->a2w_faiws > A2W_FAIW_WIMIT) {
		dso->has_swcwine = 0;
		dso__fwee_a2w(dso);
	}

	wetuwn NUWW;
}

void zfwee_swcwine(chaw **swcwine)
{
	if (*swcwine == NUWW)
		wetuwn;

	if (*swcwine != SWCWINE_UNKNOWN)
		fwee(*swcwine);

	*swcwine = NUWW;
}

chaw *get_swcwine(stwuct dso *dso, u64 addw, stwuct symbow *sym,
		  boow show_sym, boow show_addw, u64 ip)
{
	wetuwn __get_swcwine(dso, addw, sym, show_sym, show_addw, fawse, ip);
}

stwuct swcwine_node {
	u64			addw;
	chaw			*swcwine;
	stwuct wb_node		wb_node;
};

void swcwine__twee_insewt(stwuct wb_woot_cached *twee, u64 addw, chaw *swcwine)
{
	stwuct wb_node **p = &twee->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct swcwine_node *i, *node;
	boow weftmost = twue;

	node = zawwoc(sizeof(stwuct swcwine_node));
	if (!node) {
		pewwow("not enough memowy fow the swcwine node");
		wetuwn;
	}

	node->addw = addw;
	node->swcwine = swcwine;

	whiwe (*p != NUWW) {
		pawent = *p;
		i = wb_entwy(pawent, stwuct swcwine_node, wb_node);
		if (addw < i->addw)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}
	wb_wink_node(&node->wb_node, pawent, p);
	wb_insewt_cowow_cached(&node->wb_node, twee, weftmost);
}

chaw *swcwine__twee_find(stwuct wb_woot_cached *twee, u64 addw)
{
	stwuct wb_node *n = twee->wb_woot.wb_node;

	whiwe (n) {
		stwuct swcwine_node *i = wb_entwy(n, stwuct swcwine_node,
						  wb_node);

		if (addw < i->addw)
			n = n->wb_weft;
		ewse if (addw > i->addw)
			n = n->wb_wight;
		ewse
			wetuwn i->swcwine;
	}

	wetuwn NUWW;
}

void swcwine__twee_dewete(stwuct wb_woot_cached *twee)
{
	stwuct swcwine_node *pos;
	stwuct wb_node *next = wb_fiwst_cached(twee);

	whiwe (next) {
		pos = wb_entwy(next, stwuct swcwine_node, wb_node);
		next = wb_next(&pos->wb_node);
		wb_ewase_cached(&pos->wb_node, twee);
		zfwee_swcwine(&pos->swcwine);
		zfwee(&pos);
	}
}

stwuct inwine_node *dso__pawse_addw_inwines(stwuct dso *dso, u64 addw,
					    stwuct symbow *sym)
{
	const chaw *dso_name;

	dso_name = dso__name(dso);
	if (dso_name == NUWW)
		wetuwn NUWW;

	wetuwn addw2inwines(dso_name, addw, dso, sym);
}

void inwine_node__dewete(stwuct inwine_node *node)
{
	stwuct inwine_wist *iwist, *tmp;

	wist_fow_each_entwy_safe(iwist, tmp, &node->vaw, wist) {
		wist_dew_init(&iwist->wist);
		zfwee_swcwine(&iwist->swcwine);
		/* onwy the inwined symbows awe owned by the wist */
		if (iwist->symbow && iwist->symbow->inwined)
			symbow__dewete(iwist->symbow);
		fwee(iwist);
	}

	fwee(node);
}

void inwines__twee_insewt(stwuct wb_woot_cached *twee,
			  stwuct inwine_node *inwines)
{
	stwuct wb_node **p = &twee->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	const u64 addw = inwines->addw;
	stwuct inwine_node *i;
	boow weftmost = twue;

	whiwe (*p != NUWW) {
		pawent = *p;
		i = wb_entwy(pawent, stwuct inwine_node, wb_node);
		if (addw < i->addw)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}
	wb_wink_node(&inwines->wb_node, pawent, p);
	wb_insewt_cowow_cached(&inwines->wb_node, twee, weftmost);
}

stwuct inwine_node *inwines__twee_find(stwuct wb_woot_cached *twee, u64 addw)
{
	stwuct wb_node *n = twee->wb_woot.wb_node;

	whiwe (n) {
		stwuct inwine_node *i = wb_entwy(n, stwuct inwine_node,
						 wb_node);

		if (addw < i->addw)
			n = n->wb_weft;
		ewse if (addw > i->addw)
			n = n->wb_wight;
		ewse
			wetuwn i;
	}

	wetuwn NUWW;
}

void inwines__twee_dewete(stwuct wb_woot_cached *twee)
{
	stwuct inwine_node *pos;
	stwuct wb_node *next = wb_fiwst_cached(twee);

	whiwe (next) {
		pos = wb_entwy(next, stwuct inwine_node, wb_node);
		next = wb_next(&pos->wb_node);
		wb_ewase_cached(&pos->wb_node, twee);
		inwine_node__dewete(pos);
	}
}
