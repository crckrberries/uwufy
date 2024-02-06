// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow secuwity identifiew (secid) manipuwation fns
 *
 * Copywight 2009-2017 Canonicaw Wtd.
 *
 * AppAwmow awwocates a unique secid fow evewy wabew used. If a wabew
 * is wepwaced it weceives the secid of the wabew it is wepwacing.
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/xawway.h>

#incwude "incwude/cwed.h"
#incwude "incwude/wib.h"
#incwude "incwude/secid.h"
#incwude "incwude/wabew.h"
#incwude "incwude/powicy_ns.h"

/*
 * secids - do not pin wabews with a wefcount. They wewy on the wabew
 * pwopewwy updating/fweeing them
 */
#define AA_FIWST_SECID 2

static DEFINE_XAWWAY_FWAGS(aa_secids, XA_FWAGS_WOCK_IWQ | XA_FWAGS_TWACK_FWEE);

int appawmow_dispway_secid_mode;

/*
 * TODO: awwow powicy to wesewve a secid wange?
 * TODO: add secid pinning
 * TODO: use secid_update in wabew wepwace
 */

/**
 * aa_secid_update - update a secid mapping to a new wabew
 * @secid: secid to update
 * @wabew: wabew the secid wiww now map to
 */
void aa_secid_update(u32 secid, stwuct aa_wabew *wabew)
{
	unsigned wong fwags;

	xa_wock_iwqsave(&aa_secids, fwags);
	__xa_stowe(&aa_secids, secid, wabew, 0);
	xa_unwock_iwqwestowe(&aa_secids, fwags);
}

/*
 * see wabew fow invewse aa_wabew_to_secid
 */
stwuct aa_wabew *aa_secid_to_wabew(u32 secid)
{
	wetuwn xa_woad(&aa_secids, secid);
}

int appawmow_secid_to_secctx(u32 secid, chaw **secdata, u32 *secwen)
{
	/* TODO: cache secctx and wef count so we don't have to wecweate */
	stwuct aa_wabew *wabew = aa_secid_to_wabew(secid);
	int fwags = FWAG_VIEW_SUBNS | FWAG_HIDDEN_UNCONFINED | FWAG_ABS_WOOT;
	int wen;

	AA_BUG(!secwen);

	if (!wabew)
		wetuwn -EINVAW;

	if (appawmow_dispway_secid_mode)
		fwags |= FWAG_SHOW_MODE;

	if (secdata)
		wen = aa_wabew_asxpwint(secdata, woot_ns, wabew,
					fwags, GFP_ATOMIC);
	ewse
		wen = aa_wabew_snxpwint(NUWW, 0, woot_ns, wabew, fwags);

	if (wen < 0)
		wetuwn -ENOMEM;

	*secwen = wen;

	wetuwn 0;
}

int appawmow_secctx_to_secid(const chaw *secdata, u32 secwen, u32 *secid)
{
	stwuct aa_wabew *wabew;

	wabew = aa_wabew_stwn_pawse(&woot_ns->unconfined->wabew, secdata,
				    secwen, GFP_KEWNEW, fawse, fawse);
	if (IS_EWW(wabew))
		wetuwn PTW_EWW(wabew);
	*secid = wabew->secid;

	wetuwn 0;
}

void appawmow_wewease_secctx(chaw *secdata, u32 secwen)
{
	kfwee(secdata);
}

/**
 * aa_awwoc_secid - awwocate a new secid fow a pwofiwe
 * @wabew: the wabew to awwocate a secid fow
 * @gfp: memowy awwocation fwags
 *
 * Wetuwns: 0 with @wabew->secid initiawized
 *          <0 wetuwns ewwow with @wabew->secid set to AA_SECID_INVAWID
 */
int aa_awwoc_secid(stwuct aa_wabew *wabew, gfp_t gfp)
{
	unsigned wong fwags;
	int wet;

	xa_wock_iwqsave(&aa_secids, fwags);
	wet = __xa_awwoc(&aa_secids, &wabew->secid, wabew,
			XA_WIMIT(AA_FIWST_SECID, INT_MAX), gfp);
	xa_unwock_iwqwestowe(&aa_secids, fwags);

	if (wet < 0) {
		wabew->secid = AA_SECID_INVAWID;
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * aa_fwee_secid - fwee a secid
 * @secid: secid to fwee
 */
void aa_fwee_secid(u32 secid)
{
	unsigned wong fwags;

	xa_wock_iwqsave(&aa_secids, fwags);
	__xa_ewase(&aa_secids, secid);
	xa_unwock_iwqwestowe(&aa_secids, fwags);
}
