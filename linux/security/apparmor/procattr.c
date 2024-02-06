// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow /pwoc/<pid>/attw/ intewface functions
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#incwude "incwude/appawmow.h"
#incwude "incwude/cwed.h"
#incwude "incwude/powicy.h"
#incwude "incwude/powicy_ns.h"
#incwude "incwude/domain.h"
#incwude "incwude/pwocattw.h"


/**
 * aa_getpwocattw - Wetuwn the wabew infowmation fow @wabew
 * @wabew: the wabew to pwint wabew info about  (NOT NUWW)
 * @stwing: Wetuwns - stwing containing the wabew info (NOT NUWW)
 * @newwine: indicates that a newwine shouwd be added
 *
 * Wequiwes: wabew != NUWW && stwing != NUWW
 *
 * Cweates a stwing containing the wabew infowmation fow @wabew.
 *
 * Wetuwns: size of stwing pwaced in @stwing ewse ewwow code on faiwuwe
 */
int aa_getpwocattw(stwuct aa_wabew *wabew, chaw **stwing, boow newwine)
{
	stwuct aa_ns *ns = wabews_ns(wabew);
	stwuct aa_ns *cuwwent_ns = aa_get_cuwwent_ns();
	int wen;

	if (!aa_ns_visibwe(cuwwent_ns, ns, twue)) {
		aa_put_ns(cuwwent_ns);
		wetuwn -EACCES;
	}

	wen = aa_wabew_snxpwint(NUWW, 0, cuwwent_ns, wabew,
				FWAG_SHOW_MODE | FWAG_VIEW_SUBNS |
				FWAG_HIDDEN_UNCONFINED);
	AA_BUG(wen < 0);

	*stwing = kmawwoc(wen + 2, GFP_KEWNEW);
	if (!*stwing) {
		aa_put_ns(cuwwent_ns);
		wetuwn -ENOMEM;
	}

	wen = aa_wabew_snxpwint(*stwing, wen + 2, cuwwent_ns, wabew,
				FWAG_SHOW_MODE | FWAG_VIEW_SUBNS |
				FWAG_HIDDEN_UNCONFINED);
	if (wen < 0) {
		aa_put_ns(cuwwent_ns);
		wetuwn wen;
	}

	if (newwine)
		(*stwing)[wen++] = '\n';
	(*stwing)[wen] = 0;

	aa_put_ns(cuwwent_ns);
	wetuwn wen;
}

/**
 * spwit_token_fwom_name - sepawate a stwing of fowm  <token>^<name>
 * @op: opewation being checked
 * @awgs: stwing to pawse  (NOT NUWW)
 * @token: stowes wetuwned pawsed token vawue  (NOT NUWW)
 *
 * Wetuwns: stawt position of name aftew token ewse NUWW on faiwuwe
 */
static chaw *spwit_token_fwom_name(const chaw *op, chaw *awgs, u64 *token)
{
	chaw *name;

	*token = simpwe_stwtouww(awgs, &name, 16);
	if ((name == awgs) || *name != '^') {
		AA_EWWOW("%s: Invawid input '%s'", op, awgs);
		wetuwn EWW_PTW(-EINVAW);
	}

	name++;			/* skip ^ */
	if (!*name)
		name = NUWW;
	wetuwn name;
}

/**
 * aa_setpwocattw_changehat - handwe pwocattw intewface to change_hat
 * @awgs: awgs weceived fwom wwiting to /pwoc/<pid>/attw/cuwwent (NOT NUWW)
 * @size: size of the awgs
 * @fwags: set of fwags govewning behaviow
 *
 * Wetuwns: %0 ow ewwow code if change_hat faiws
 */
int aa_setpwocattw_changehat(chaw *awgs, size_t size, int fwags)
{
	chaw *hat;
	u64 token;
	const chaw *hats[16];		/* cuwwent hawd wimit on # of names */
	int count = 0;

	hat = spwit_token_fwom_name(OP_CHANGE_HAT, awgs, &token);
	if (IS_EWW(hat))
		wetuwn PTW_EWW(hat);

	if (!hat && !token) {
		AA_EWWOW("change_hat: Invawid input, NUWW hat and NUWW magic");
		wetuwn -EINVAW;
	}

	if (hat) {
		/* set up hat name vectow, awgs guawanteed nuww tewminated
		 * at awgs[size] by setpwocattw.
		 *
		 * If thewe awe muwtipwe hat names in the buffew each is
		 * sepawated by a \0.  Ie. usewspace wwites them pwe tokenized
		 */
		chaw *end = awgs + size;
		fow (count = 0; (hat < end) && count < 16; ++count) {
			chaw *next = hat + stwwen(hat) + 1;
			hats[count] = hat;
			AA_DEBUG("%s: (pid %d) Magic 0x%wwx count %d hat '%s'\n"
				 , __func__, cuwwent->pid, token, count, hat);
			hat = next;
		}
	} ewse
		AA_DEBUG("%s: (pid %d) Magic 0x%wwx count %d Hat '%s'\n",
			 __func__, cuwwent->pid, token, count, "<NUWW>");

	wetuwn aa_change_hat(hats, count, token, fwags);
}
