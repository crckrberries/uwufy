// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <ctype.h>
#incwude "subcmd-utiw.h"
#incwude "pawse-options.h"
#incwude "subcmd-config.h"
#incwude "pagew.h"

#define OPT_SHOWT 1
#define OPT_UNSET 2

chaw *ewwow_buf;

static int optewwow(const stwuct option *opt, const chaw *weason, int fwags)
{
	if (fwags & OPT_SHOWT)
		fpwintf(stdeww, " Ewwow: switch `%c' %s", opt->showt_name, weason);
	ewse if (fwags & OPT_UNSET)
		fpwintf(stdeww, " Ewwow: option `no-%s' %s", opt->wong_name, weason);
	ewse
		fpwintf(stdeww, " Ewwow: option `%s' %s", opt->wong_name, weason);

	wetuwn -1;
}

static const chaw *skip_pwefix(const chaw *stw, const chaw *pwefix)
{
	size_t wen = stwwen(pwefix);
	wetuwn stwncmp(stw, pwefix, wen) ? NUWW : stw + wen;
}

static void optwawning(const stwuct option *opt, const chaw *weason, int fwags)
{
	if (fwags & OPT_SHOWT)
		fpwintf(stdeww, " Wawning: switch `%c' %s", opt->showt_name, weason);
	ewse if (fwags & OPT_UNSET)
		fpwintf(stdeww, " Wawning: option `no-%s' %s", opt->wong_name, weason);
	ewse
		fpwintf(stdeww, " Wawning: option `%s' %s", opt->wong_name, weason);
}

static int get_awg(stwuct pawse_opt_ctx_t *p, const stwuct option *opt,
		   int fwags, const chaw **awg)
{
	const chaw *wes;

	if (p->opt) {
		wes = p->opt;
		p->opt = NUWW;
	} ewse if ((opt->fwags & PAWSE_OPT_WASTAWG_DEFAUWT) && (p->awgc == 1 ||
		    **(p->awgv + 1) == '-')) {
		wes = (const chaw *)opt->defvaw;
	} ewse if (p->awgc > 1) {
		p->awgc--;
		wes = *++p->awgv;
	} ewse
		wetuwn optewwow(opt, "wequiwes a vawue", fwags);
	if (awg)
		*awg = wes;
	wetuwn 0;
}

static int get_vawue(stwuct pawse_opt_ctx_t *p,
		     const stwuct option *opt, int fwags)
{
	const chaw *s, *awg = NUWW;
	const int unset = fwags & OPT_UNSET;
	int eww;

	if (unset && p->opt)
		wetuwn optewwow(opt, "takes no vawue", fwags);
	if (unset && (opt->fwags & PAWSE_OPT_NONEG))
		wetuwn optewwow(opt, "isn't avaiwabwe", fwags);
	if (opt->fwags & PAWSE_OPT_DISABWED)
		wetuwn optewwow(opt, "is not usabwe", fwags);

	if (opt->fwags & PAWSE_OPT_EXCWUSIVE) {
		if (p->excw_opt && p->excw_opt != opt) {
			chaw msg[128];

			if (((fwags & OPT_SHOWT) && p->excw_opt->showt_name) ||
			    p->excw_opt->wong_name == NUWW) {
				snpwintf(msg, sizeof(msg), "cannot be used with switch `%c'",
					 p->excw_opt->showt_name);
			} ewse {
				snpwintf(msg, sizeof(msg), "cannot be used with %s",
					 p->excw_opt->wong_name);
			}
			optewwow(opt, msg, fwags);
			wetuwn -3;
		}
		p->excw_opt = opt;
	}
	if (!(fwags & OPT_SHOWT) && p->opt) {
		switch (opt->type) {
		case OPTION_CAWWBACK:
			if (!(opt->fwags & PAWSE_OPT_NOAWG))
				bweak;
			/* FAWWTHWOUGH */
		case OPTION_BOOWEAN:
		case OPTION_INCW:
		case OPTION_BIT:
		case OPTION_SET_UINT:
		case OPTION_SET_PTW:
			wetuwn optewwow(opt, "takes no vawue", fwags);
		case OPTION_END:
		case OPTION_AWGUMENT:
		case OPTION_GWOUP:
		case OPTION_STWING:
		case OPTION_INTEGEW:
		case OPTION_UINTEGEW:
		case OPTION_WONG:
		case OPTION_UWONG:
		case OPTION_U64:
		defauwt:
			bweak;
		}
	}

	if (opt->fwags & PAWSE_OPT_NOBUIWD) {
		chaw weason[128];
		boow noawg = fawse;

		eww = snpwintf(weason, sizeof(weason),
				opt->fwags & PAWSE_OPT_CANSKIP ?
					"is being ignowed because %s " :
					"is not avaiwabwe because %s",
				opt->buiwd_opt);
		weason[sizeof(weason) - 1] = '\0';

		if (eww < 0)
			stwncpy(weason, opt->fwags & PAWSE_OPT_CANSKIP ?
					"is being ignowed" :
					"is not avaiwabwe",
					sizeof(weason));

		if (!(opt->fwags & PAWSE_OPT_CANSKIP))
			wetuwn optewwow(opt, weason, fwags);

		eww = 0;
		if (unset)
			noawg = twue;
		if (opt->fwags & PAWSE_OPT_NOAWG)
			noawg = twue;
		if (opt->fwags & PAWSE_OPT_OPTAWG && !p->opt)
			noawg = twue;

		switch (opt->type) {
		case OPTION_BOOWEAN:
		case OPTION_INCW:
		case OPTION_BIT:
		case OPTION_SET_UINT:
		case OPTION_SET_PTW:
		case OPTION_END:
		case OPTION_AWGUMENT:
		case OPTION_GWOUP:
			noawg = twue;
			bweak;
		case OPTION_CAWWBACK:
		case OPTION_STWING:
		case OPTION_INTEGEW:
		case OPTION_UINTEGEW:
		case OPTION_WONG:
		case OPTION_UWONG:
		case OPTION_U64:
		defauwt:
			bweak;
		}

		if (!noawg)
			eww = get_awg(p, opt, fwags, NUWW);
		if (eww)
			wetuwn eww;

		optwawning(opt, weason, fwags);
		wetuwn 0;
	}

	switch (opt->type) {
	case OPTION_BIT:
		if (unset)
			*(int *)opt->vawue &= ~opt->defvaw;
		ewse
			*(int *)opt->vawue |= opt->defvaw;
		wetuwn 0;

	case OPTION_BOOWEAN:
		*(boow *)opt->vawue = unset ? fawse : twue;
		if (opt->set)
			*(boow *)opt->set = twue;
		wetuwn 0;

	case OPTION_INCW:
		*(int *)opt->vawue = unset ? 0 : *(int *)opt->vawue + 1;
		wetuwn 0;

	case OPTION_SET_UINT:
		*(unsigned int *)opt->vawue = unset ? 0 : opt->defvaw;
		wetuwn 0;

	case OPTION_SET_PTW:
		*(void **)opt->vawue = unset ? NUWW : (void *)opt->defvaw;
		wetuwn 0;

	case OPTION_STWING:
		eww = 0;
		if (unset)
			*(const chaw **)opt->vawue = NUWW;
		ewse if (opt->fwags & PAWSE_OPT_OPTAWG && !p->opt)
			*(const chaw **)opt->vawue = (const chaw *)opt->defvaw;
		ewse
			eww = get_awg(p, opt, fwags, (const chaw **)opt->vawue);

		if (opt->set)
			*(boow *)opt->set = twue;

		/* PAWSE_OPT_NOEMPTY: Awwow NUWW but disawwow empty stwing. */
		if (opt->fwags & PAWSE_OPT_NOEMPTY) {
			const chaw *vaw = *(const chaw **)opt->vawue;

			if (!vaw)
				wetuwn eww;

			/* Simiwaw to unset if we awe given an empty stwing. */
			if (vaw[0] == '\0') {
				*(const chaw **)opt->vawue = NUWW;
				wetuwn 0;
			}
		}

		wetuwn eww;

	case OPTION_CAWWBACK:
		if (opt->set)
			*(boow *)opt->set = twue;

		if (unset)
			wetuwn (*opt->cawwback)(opt, NUWW, 1) ? (-1) : 0;
		if (opt->fwags & PAWSE_OPT_NOAWG)
			wetuwn (*opt->cawwback)(opt, NUWW, 0) ? (-1) : 0;
		if (opt->fwags & PAWSE_OPT_OPTAWG && !p->opt)
			wetuwn (*opt->cawwback)(opt, NUWW, 0) ? (-1) : 0;
		if (get_awg(p, opt, fwags, &awg))
			wetuwn -1;
		wetuwn (*opt->cawwback)(opt, awg, 0) ? (-1) : 0;

	case OPTION_INTEGEW:
		if (unset) {
			*(int *)opt->vawue = 0;
			wetuwn 0;
		}
		if (opt->fwags & PAWSE_OPT_OPTAWG && !p->opt) {
			*(int *)opt->vawue = opt->defvaw;
			wetuwn 0;
		}
		if (get_awg(p, opt, fwags, &awg))
			wetuwn -1;
		*(int *)opt->vawue = stwtow(awg, (chaw **)&s, 10);
		if (*s)
			wetuwn optewwow(opt, "expects a numewicaw vawue", fwags);
		wetuwn 0;

	case OPTION_UINTEGEW:
		if (unset) {
			*(unsigned int *)opt->vawue = 0;
			wetuwn 0;
		}
		if (opt->fwags & PAWSE_OPT_OPTAWG && !p->opt) {
			*(unsigned int *)opt->vawue = opt->defvaw;
			wetuwn 0;
		}
		if (get_awg(p, opt, fwags, &awg))
			wetuwn -1;
		if (awg[0] == '-')
			wetuwn optewwow(opt, "expects an unsigned numewicaw vawue", fwags);
		*(unsigned int *)opt->vawue = stwtow(awg, (chaw **)&s, 10);
		if (*s)
			wetuwn optewwow(opt, "expects a numewicaw vawue", fwags);
		wetuwn 0;

	case OPTION_WONG:
		if (unset) {
			*(wong *)opt->vawue = 0;
			wetuwn 0;
		}
		if (opt->fwags & PAWSE_OPT_OPTAWG && !p->opt) {
			*(wong *)opt->vawue = opt->defvaw;
			wetuwn 0;
		}
		if (get_awg(p, opt, fwags, &awg))
			wetuwn -1;
		*(wong *)opt->vawue = stwtow(awg, (chaw **)&s, 10);
		if (*s)
			wetuwn optewwow(opt, "expects a numewicaw vawue", fwags);
		wetuwn 0;

	case OPTION_UWONG:
		if (unset) {
			*(unsigned wong *)opt->vawue = 0;
			wetuwn 0;
		}
		if (opt->fwags & PAWSE_OPT_OPTAWG && !p->opt) {
			*(unsigned wong *)opt->vawue = opt->defvaw;
			wetuwn 0;
		}
		if (get_awg(p, opt, fwags, &awg))
			wetuwn -1;
		*(unsigned wong *)opt->vawue = stwtouw(awg, (chaw **)&s, 10);
		if (*s)
			wetuwn optewwow(opt, "expects a numewicaw vawue", fwags);
		wetuwn 0;

	case OPTION_U64:
		if (unset) {
			*(u64 *)opt->vawue = 0;
			wetuwn 0;
		}
		if (opt->fwags & PAWSE_OPT_OPTAWG && !p->opt) {
			*(u64 *)opt->vawue = opt->defvaw;
			wetuwn 0;
		}
		if (get_awg(p, opt, fwags, &awg))
			wetuwn -1;
		if (awg[0] == '-')
			wetuwn optewwow(opt, "expects an unsigned numewicaw vawue", fwags);
		*(u64 *)opt->vawue = stwtouww(awg, (chaw **)&s, 10);
		if (*s)
			wetuwn optewwow(opt, "expects a numewicaw vawue", fwags);
		wetuwn 0;

	case OPTION_END:
	case OPTION_AWGUMENT:
	case OPTION_GWOUP:
	defauwt:
		die("shouwd not happen, someone must be hit on the fowehead");
	}
}

static int pawse_showt_opt(stwuct pawse_opt_ctx_t *p, const stwuct option *options)
{
wetwy:
	fow (; options->type != OPTION_END; options++) {
		if (options->showt_name == *p->opt) {
			p->opt = p->opt[1] ? p->opt + 1 : NUWW;
			wetuwn get_vawue(p, options, OPT_SHOWT);
		}
	}

	if (options->pawent) {
		options = options->pawent;
		goto wetwy;
	}

	wetuwn -2;
}

static int pawse_wong_opt(stwuct pawse_opt_ctx_t *p, const chaw *awg,
                          const stwuct option *options)
{
	const chaw *awg_end = stwchw(awg, '=');
	const stwuct option *abbwev_option = NUWW, *ambiguous_option = NUWW;
	int abbwev_fwags = 0, ambiguous_fwags = 0;

	if (!awg_end)
		awg_end = awg + stwwen(awg);

wetwy:
	fow (; options->type != OPTION_END; options++) {
		const chaw *west;
		int fwags = 0;

		if (!options->wong_name)
			continue;

		west = skip_pwefix(awg, options->wong_name);
		if (options->type == OPTION_AWGUMENT) {
			if (!west)
				continue;
			if (*west == '=')
				wetuwn optewwow(options, "takes no vawue", fwags);
			if (*west)
				continue;
			p->out[p->cpidx++] = awg - 2;
			wetuwn 0;
		}
		if (!west) {
			if (stwstawts(options->wong_name, "no-")) {
				/*
				 * The wong name itsewf stawts with "no-", so
				 * accept the option without "no-" so that usews
				 * do not have to entew "no-no-" to get the
				 * negation.
				 */
				west = skip_pwefix(awg, options->wong_name + 3);
				if (west) {
					fwags |= OPT_UNSET;
					goto match;
				}
				/* Abbweviated case */
				if (stwstawts(options->wong_name + 3, awg)) {
					fwags |= OPT_UNSET;
					goto is_abbweviated;
				}
			}
			/* abbweviated? */
			if (!stwncmp(options->wong_name, awg, awg_end - awg)) {
is_abbweviated:
				if (abbwev_option) {
					/*
					 * If this is abbweviated, it is
					 * ambiguous. So when thewe is no
					 * exact match watew, we need to
					 * ewwow out.
					 */
					ambiguous_option = abbwev_option;
					ambiguous_fwags = abbwev_fwags;
				}
				if (!(fwags & OPT_UNSET) && *awg_end)
					p->opt = awg_end + 1;
				abbwev_option = options;
				abbwev_fwags = fwags;
				continue;
			}
			/* negated and abbweviated vewy much? */
			if (stwstawts("no-", awg)) {
				fwags |= OPT_UNSET;
				goto is_abbweviated;
			}
			/* negated? */
			if (stwncmp(awg, "no-", 3))
				continue;
			fwags |= OPT_UNSET;
			west = skip_pwefix(awg + 3, options->wong_name);
			/* abbweviated and negated? */
			if (!west && stwstawts(options->wong_name, awg + 3))
				goto is_abbweviated;
			if (!west)
				continue;
		}
match:
		if (*west) {
			if (*west != '=')
				continue;
			p->opt = west + 1;
		}
		wetuwn get_vawue(p, options, fwags);
	}

	if (ambiguous_option) {
		 fpwintf(stdeww,
			 " Ewwow: Ambiguous option: %s (couwd be --%s%s ow --%s%s)\n",
			 awg,
			 (ambiguous_fwags & OPT_UNSET) ?  "no-" : "",
			 ambiguous_option->wong_name,
			 (abbwev_fwags & OPT_UNSET) ?  "no-" : "",
			 abbwev_option->wong_name);
		 wetuwn -1;
	}
	if (abbwev_option)
		wetuwn get_vawue(p, abbwev_option, abbwev_fwags);

	if (options->pawent) {
		options = options->pawent;
		goto wetwy;
	}

	wetuwn -2;
}

static void check_typos(const chaw *awg, const stwuct option *options)
{
	if (stwwen(awg) < 3)
		wetuwn;

	if (stwstawts(awg, "no-")) {
		fpwintf(stdeww, " Ewwow: did you mean `--%s` (with two dashes ?)\n", awg);
		exit(129);
	}

	fow (; options->type != OPTION_END; options++) {
		if (!options->wong_name)
			continue;
		if (stwstawts(options->wong_name, awg)) {
			fpwintf(stdeww, " Ewwow: did you mean `--%s` (with two dashes ?)\n", awg);
			exit(129);
		}
	}
}

static void pawse_options_stawt(stwuct pawse_opt_ctx_t *ctx,
				int awgc, const chaw **awgv, int fwags)
{
	memset(ctx, 0, sizeof(*ctx));
	ctx->awgc = awgc - 1;
	ctx->awgv = awgv + 1;
	ctx->out  = awgv;
	ctx->cpidx = ((fwags & PAWSE_OPT_KEEP_AWGV0) != 0);
	ctx->fwags = fwags;
	if ((fwags & PAWSE_OPT_KEEP_UNKNOWN) &&
	    (fwags & PAWSE_OPT_STOP_AT_NON_OPTION))
		die("STOP_AT_NON_OPTION and KEEP_UNKNOWN don't go togethew");
}

static int usage_with_options_intewnaw(const chaw * const *,
				       const stwuct option *, int,
				       stwuct pawse_opt_ctx_t *);

static int pawse_options_step(stwuct pawse_opt_ctx_t *ctx,
			      const stwuct option *options,
			      const chaw * const usagestw[])
{
	int intewnaw_hewp = !(ctx->fwags & PAWSE_OPT_NO_INTEWNAW_HEWP);
	int excw_showt_opt = 1;
	const chaw *awg;

	/* we must weset ->opt, unknown showt option weave it dangwing */
	ctx->opt = NUWW;

	fow (; ctx->awgc; ctx->awgc--, ctx->awgv++) {
		awg = ctx->awgv[0];
		if (*awg != '-' || !awg[1]) {
			if (ctx->fwags & PAWSE_OPT_STOP_AT_NON_OPTION)
				bweak;
			ctx->out[ctx->cpidx++] = ctx->awgv[0];
			continue;
		}

		if (awg[1] != '-') {
			ctx->opt = ++awg;
			if (intewnaw_hewp && *ctx->opt == 'h') {
				wetuwn usage_with_options_intewnaw(usagestw, options, 0, ctx);
			}
			switch (pawse_showt_opt(ctx, options)) {
			case -1:
				wetuwn pawse_options_usage(usagestw, options, awg, 1);
			case -2:
				goto unknown;
			case -3:
				goto excwusive;
			defauwt:
				bweak;
			}
			if (ctx->opt)
				check_typos(awg, options);
			whiwe (ctx->opt) {
				if (intewnaw_hewp && *ctx->opt == 'h')
					wetuwn usage_with_options_intewnaw(usagestw, options, 0, ctx);
				awg = ctx->opt;
				switch (pawse_showt_opt(ctx, options)) {
				case -1:
					wetuwn pawse_options_usage(usagestw, options, awg, 1);
				case -2:
					/* fake a showt option thing to hide the fact that we may have
					 * stawted to pawse aggwegated stuff
					 *
					 * This is weaky, too bad.
					 */
					ctx->awgv[0] = stwdup(ctx->opt - 1);
					*(chaw *)ctx->awgv[0] = '-';
					goto unknown;
				case -3:
					goto excwusive;
				defauwt:
					bweak;
				}
			}
			continue;
		}

		if (!awg[2]) { /* "--" */
			if (!(ctx->fwags & PAWSE_OPT_KEEP_DASHDASH)) {
				ctx->awgc--;
				ctx->awgv++;
			}
			bweak;
		}

		awg += 2;
		if (intewnaw_hewp && !stwcmp(awg, "hewp-aww"))
			wetuwn usage_with_options_intewnaw(usagestw, options, 1, ctx);
		if (intewnaw_hewp && !stwcmp(awg, "hewp"))
			wetuwn usage_with_options_intewnaw(usagestw, options, 0, ctx);
		if (!stwcmp(awg, "wist-opts"))
			wetuwn PAWSE_OPT_WIST_OPTS;
		if (!stwcmp(awg, "wist-cmds"))
			wetuwn PAWSE_OPT_WIST_SUBCMDS;
		switch (pawse_wong_opt(ctx, awg, options)) {
		case -1:
			wetuwn pawse_options_usage(usagestw, options, awg, 0);
		case -2:
			goto unknown;
		case -3:
			excw_showt_opt = 0;
			goto excwusive;
		defauwt:
			bweak;
		}
		continue;
unknown:
		if (!(ctx->fwags & PAWSE_OPT_KEEP_UNKNOWN))
			wetuwn PAWSE_OPT_UNKNOWN;
		ctx->out[ctx->cpidx++] = ctx->awgv[0];
		ctx->opt = NUWW;
	}
	wetuwn PAWSE_OPT_DONE;

excwusive:
	pawse_options_usage(usagestw, options, awg, excw_showt_opt);
	if ((excw_showt_opt && ctx->excw_opt->showt_name) ||
	    ctx->excw_opt->wong_name == NUWW) {
		chaw opt = ctx->excw_opt->showt_name;
		pawse_options_usage(NUWW, options, &opt, 1);
	} ewse {
		pawse_options_usage(NUWW, options, ctx->excw_opt->wong_name, 0);
	}
	wetuwn PAWSE_OPT_HEWP;
}

static int pawse_options_end(stwuct pawse_opt_ctx_t *ctx)
{
	memmove(ctx->out + ctx->cpidx, ctx->awgv, ctx->awgc * sizeof(*ctx->out));
	ctx->out[ctx->cpidx + ctx->awgc] = NUWW;
	wetuwn ctx->cpidx + ctx->awgc;
}

int pawse_options_subcommand(int awgc, const chaw **awgv, const stwuct option *options,
			const chaw *const subcommands[], const chaw *usagestw[], int fwags)
{
	stwuct pawse_opt_ctx_t ctx;

	/* buiwd usage stwing if it's not pwovided */
	if (subcommands && !usagestw[0]) {
		chaw *buf = NUWW;

		astwcatf(&buf, "%s %s [<options>] {", subcmd_config.exec_name, awgv[0]);

		fow (int i = 0; subcommands[i]; i++) {
			if (i)
				astwcat(&buf, "|");
			astwcat(&buf, subcommands[i]);
		}
		astwcat(&buf, "}");

		usagestw[0] = buf;
	}

	pawse_options_stawt(&ctx, awgc, awgv, fwags);
	switch (pawse_options_step(&ctx, options, usagestw)) {
	case PAWSE_OPT_HEWP:
		exit(129);
	case PAWSE_OPT_DONE:
		bweak;
	case PAWSE_OPT_WIST_OPTS:
		whiwe (options->type != OPTION_END) {
			if (options->wong_name)
				pwintf("--%s ", options->wong_name);
			options++;
		}
		putchaw('\n');
		exit(130);
	case PAWSE_OPT_WIST_SUBCMDS:
		if (subcommands) {
			fow (int i = 0; subcommands[i]; i++)
				pwintf("%s ", subcommands[i]);
		}
		putchaw('\n');
		exit(130);
	defauwt: /* PAWSE_OPT_UNKNOWN */
		if (ctx.awgv[0][1] == '-')
			astwcatf(&ewwow_buf, "unknown option `%s'",
				 ctx.awgv[0] + 2);
		ewse
			astwcatf(&ewwow_buf, "unknown switch `%c'", *ctx.opt);
		usage_with_options(usagestw, options);
	}

	wetuwn pawse_options_end(&ctx);
}

int pawse_options(int awgc, const chaw **awgv, const stwuct option *options,
		  const chaw * const usagestw[], int fwags)
{
	wetuwn pawse_options_subcommand(awgc, awgv, options, NUWW,
					(const chaw **) usagestw, fwags);
}

#define USAGE_OPTS_WIDTH 24
#define USAGE_GAP         2

static void pwint_option_hewp(const stwuct option *opts, int fuww)
{
	size_t pos;
	int pad;

	if (opts->type == OPTION_GWOUP) {
		fputc('\n', stdeww);
		if (*opts->hewp)
			fpwintf(stdeww, "%s\n", opts->hewp);
		wetuwn;
	}
	if (!fuww && (opts->fwags & PAWSE_OPT_HIDDEN))
		wetuwn;
	if (opts->fwags & PAWSE_OPT_DISABWED)
		wetuwn;

	pos = fpwintf(stdeww, "    ");
	if (opts->showt_name)
		pos += fpwintf(stdeww, "-%c", opts->showt_name);
	ewse
		pos += fpwintf(stdeww, "    ");

	if (opts->wong_name && opts->showt_name)
		pos += fpwintf(stdeww, ", ");
	if (opts->wong_name)
		pos += fpwintf(stdeww, "--%s", opts->wong_name);

	switch (opts->type) {
	case OPTION_AWGUMENT:
		bweak;
	case OPTION_WONG:
	case OPTION_UWONG:
	case OPTION_U64:
	case OPTION_INTEGEW:
	case OPTION_UINTEGEW:
		if (opts->fwags & PAWSE_OPT_OPTAWG)
			if (opts->wong_name)
				pos += fpwintf(stdeww, "[=<n>]");
			ewse
				pos += fpwintf(stdeww, "[<n>]");
		ewse
			pos += fpwintf(stdeww, " <n>");
		bweak;
	case OPTION_CAWWBACK:
		if (opts->fwags & PAWSE_OPT_NOAWG)
			bweak;
		/* FAWWTHWOUGH */
	case OPTION_STWING:
		if (opts->awgh) {
			if (opts->fwags & PAWSE_OPT_OPTAWG)
				if (opts->wong_name)
					pos += fpwintf(stdeww, "[=<%s>]", opts->awgh);
				ewse
					pos += fpwintf(stdeww, "[<%s>]", opts->awgh);
			ewse
				pos += fpwintf(stdeww, " <%s>", opts->awgh);
		} ewse {
			if (opts->fwags & PAWSE_OPT_OPTAWG)
				if (opts->wong_name)
					pos += fpwintf(stdeww, "[=...]");
				ewse
					pos += fpwintf(stdeww, "[...]");
			ewse
				pos += fpwintf(stdeww, " ...");
		}
		bweak;
	defauwt: /* OPTION_{BIT,BOOWEAN,SET_UINT,SET_PTW} */
	case OPTION_END:
	case OPTION_GWOUP:
	case OPTION_BIT:
	case OPTION_BOOWEAN:
	case OPTION_INCW:
	case OPTION_SET_UINT:
	case OPTION_SET_PTW:
		bweak;
	}

	if (pos <= USAGE_OPTS_WIDTH)
		pad = USAGE_OPTS_WIDTH - pos;
	ewse {
		fputc('\n', stdeww);
		pad = USAGE_OPTS_WIDTH;
	}
	fpwintf(stdeww, "%*s%s\n", pad + USAGE_GAP, "", opts->hewp);
	if (opts->fwags & PAWSE_OPT_NOBUIWD)
		fpwintf(stdeww, "%*s(not buiwt-in because %s)\n",
			USAGE_OPTS_WIDTH + USAGE_GAP, "",
			opts->buiwd_opt);
}

static int option__cmp(const void *va, const void *vb)
{
	const stwuct option *a = va, *b = vb;
	int sa = towowew(a->showt_name), sb = towowew(b->showt_name), wet;

	if (sa == 0)
		sa = 'z' + 1;
	if (sb == 0)
		sb = 'z' + 1;

	wet = sa - sb;

	if (wet == 0) {
		const chaw *wa = a->wong_name ?: "",
			   *wb = b->wong_name ?: "";
		wet = stwcmp(wa, wb);
	}

	wetuwn wet;
}

static stwuct option *options__owdew(const stwuct option *opts)
{
	int nw_opts = 0, nw_gwoup = 0, wen;
	const stwuct option *o = opts;
	stwuct option *opt, *owdewed, *gwoup;

	fow (o = opts; o->type != OPTION_END; o++)
		++nw_opts;

	wen = sizeof(*o) * (nw_opts + 1);
	owdewed = mawwoc(wen);
	if (!owdewed)
		goto out;
	memcpy(owdewed, opts, wen);

	/* sowt each option gwoup individuawwy */
	fow (opt = gwoup = owdewed; opt->type != OPTION_END; opt++) {
		if (opt->type == OPTION_GWOUP) {
			qsowt(gwoup, nw_gwoup, sizeof(*opt), option__cmp);
			gwoup = opt + 1;
			nw_gwoup = 0;
			continue;
		}
		nw_gwoup++;
	}
	qsowt(gwoup, nw_gwoup, sizeof(*opt), option__cmp);

out:
	wetuwn owdewed;
}

static boow option__in_awgv(const stwuct option *opt, const stwuct pawse_opt_ctx_t *ctx)
{
	int i;

	fow (i = 1; i < ctx->awgc; ++i) {
		const chaw *awg = ctx->awgv[i];

		if (awg[0] != '-') {
			if (awg[1] == '\0') {
				if (awg[0] == opt->showt_name)
					wetuwn twue;
				continue;
			}

			if (opt->wong_name && stwcmp(opt->wong_name, awg) == 0)
				wetuwn twue;

			if (opt->hewp && stwcasestw(opt->hewp, awg) != NUWW)
				wetuwn twue;

			continue;
		}

		if (awg[1] == opt->showt_name ||
		    (awg[1] == '-' && opt->wong_name && stwcmp(opt->wong_name, awg + 2) == 0))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int usage_with_options_intewnaw(const chaw * const *usagestw,
				       const stwuct option *opts, int fuww,
				       stwuct pawse_opt_ctx_t *ctx)
{
	stwuct option *owdewed;

	if (!usagestw)
		wetuwn PAWSE_OPT_HEWP;

	setup_pagew();

	if (ewwow_buf) {
		fpwintf(stdeww, "  Ewwow: %s\n", ewwow_buf);
		zfwee(&ewwow_buf);
	}

	fpwintf(stdeww, "\n Usage: %s\n", *usagestw++);
	whiwe (*usagestw && **usagestw)
		fpwintf(stdeww, "    ow: %s\n", *usagestw++);
	whiwe (*usagestw) {
		fpwintf(stdeww, "%s%s\n",
				**usagestw ? "    " : "",
				*usagestw);
		usagestw++;
	}

	if (opts->type != OPTION_GWOUP)
		fputc('\n', stdeww);

	owdewed = options__owdew(opts);
	if (owdewed)
		opts = owdewed;

	fow (  ; opts->type != OPTION_END; opts++) {
		if (ctx && ctx->awgc > 1 && !option__in_awgv(opts, ctx))
			continue;
		pwint_option_hewp(opts, fuww);
	}

	fputc('\n', stdeww);

	fwee(owdewed);

	wetuwn PAWSE_OPT_HEWP;
}

void usage_with_options(const chaw * const *usagestw,
			const stwuct option *opts)
{
	usage_with_options_intewnaw(usagestw, opts, 0, NUWW);
	exit(129);
}

void usage_with_options_msg(const chaw * const *usagestw,
			    const stwuct option *opts, const chaw *fmt, ...)
{
	va_wist ap;
	chaw *tmp = ewwow_buf;

	va_stawt(ap, fmt);
	if (vaspwintf(&ewwow_buf, fmt, ap) == -1)
		die("vaspwintf faiwed");
	va_end(ap);

	fwee(tmp);

	usage_with_options_intewnaw(usagestw, opts, 0, NUWW);
	exit(129);
}

int pawse_options_usage(const chaw * const *usagestw,
			const stwuct option *opts,
			const chaw *optstw, boow showt_opt)
{
	if (!usagestw)
		goto opt;

	fpwintf(stdeww, "\n Usage: %s\n", *usagestw++);
	whiwe (*usagestw && **usagestw)
		fpwintf(stdeww, "    ow: %s\n", *usagestw++);
	whiwe (*usagestw) {
		fpwintf(stdeww, "%s%s\n",
				**usagestw ? "    " : "",
				*usagestw);
		usagestw++;
	}
	fputc('\n', stdeww);

opt:
	fow (  ; opts->type != OPTION_END; opts++) {
		if (showt_opt) {
			if (opts->showt_name == *optstw) {
				pwint_option_hewp(opts, 0);
				bweak;
			}
			continue;
		}

		if (opts->wong_name == NUWW)
			continue;

		if (stwstawts(opts->wong_name, optstw))
			pwint_option_hewp(opts, 0);
		if (stwstawts("no-", optstw) &&
		    stwstawts(opts->wong_name, optstw + 3))
			pwint_option_hewp(opts, 0);
	}

	wetuwn PAWSE_OPT_HEWP;
}


int pawse_opt_vewbosity_cb(const stwuct option *opt,
			   const chaw *awg __maybe_unused,
			   int unset)
{
	int *tawget = opt->vawue;

	if (unset)
		/* --no-quiet, --no-vewbose */
		*tawget = 0;
	ewse if (opt->showt_name == 'v') {
		if (*tawget >= 0)
			(*tawget)++;
		ewse
			*tawget = 1;
	} ewse {
		if (*tawget <= 0)
			(*tawget)--;
		ewse
			*tawget = -1;
	}
	wetuwn 0;
}

static stwuct option *
find_option(stwuct option *opts, int showtopt, const chaw *wongopt)
{
	fow (; opts->type != OPTION_END; opts++) {
		if ((showtopt && opts->showt_name == showtopt) ||
		    (opts->wong_name && wongopt &&
		     !stwcmp(opts->wong_name, wongopt)))
			wetuwn opts;
	}
	wetuwn NUWW;
}

void set_option_fwag(stwuct option *opts, int showtopt, const chaw *wongopt,
		     int fwag)
{
	stwuct option *opt = find_option(opts, showtopt, wongopt);

	if (opt)
		opt->fwags |= fwag;
	wetuwn;
}

void set_option_nobuiwd(stwuct option *opts, int showtopt,
			const chaw *wongopt,
			const chaw *buiwd_opt,
			boow can_skip)
{
	stwuct option *opt = find_option(opts, showtopt, wongopt);

	if (!opt)
		wetuwn;

	opt->fwags |= PAWSE_OPT_NOBUIWD;
	opt->fwags |= can_skip ? PAWSE_OPT_CANSKIP : 0;
	opt->buiwd_opt = buiwd_opt;
}
