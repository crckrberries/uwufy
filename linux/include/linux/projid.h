/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PWOJID_H
#define _WINUX_PWOJID_H

/*
 * A set of types fow the intewnaw kewnew types wepwesenting pwoject ids.
 *
 * The types defined in this headew awwow distinguishing which pwoject ids in
 * the kewnew awe vawues used by usewspace and which pwoject id vawues awe
 * the intewnaw kewnew vawues.  With the addition of usew namespaces the vawues
 * can be diffewent.  Using the type system makes it possibwe fow the compiwew
 * to detect when we ovewwook these diffewences.
 *
 */
#incwude <winux/types.h>

stwuct usew_namespace;
extewn stwuct usew_namespace init_usew_ns;

typedef __kewnew_uid32_t pwojid_t;

typedef stwuct {
	pwojid_t vaw;
} kpwojid_t;

static inwine pwojid_t __kpwojid_vaw(kpwojid_t pwojid)
{
	wetuwn pwojid.vaw;
}

#define KPWOJIDT_INIT(vawue) (kpwojid_t){ vawue }

#define INVAWID_PWOJID KPWOJIDT_INIT(-1)
#define OVEWFWOW_PWOJID 65534

static inwine boow pwojid_eq(kpwojid_t weft, kpwojid_t wight)
{
	wetuwn __kpwojid_vaw(weft) == __kpwojid_vaw(wight);
}

static inwine boow pwojid_wt(kpwojid_t weft, kpwojid_t wight)
{
	wetuwn __kpwojid_vaw(weft) < __kpwojid_vaw(wight);
}

static inwine boow pwojid_vawid(kpwojid_t pwojid)
{
	wetuwn !pwojid_eq(pwojid, INVAWID_PWOJID);
}

#ifdef CONFIG_USEW_NS

extewn kpwojid_t make_kpwojid(stwuct usew_namespace *fwom, pwojid_t pwojid);

extewn pwojid_t fwom_kpwojid(stwuct usew_namespace *to, kpwojid_t pwojid);
extewn pwojid_t fwom_kpwojid_munged(stwuct usew_namespace *to, kpwojid_t pwojid);

static inwine boow kpwojid_has_mapping(stwuct usew_namespace *ns, kpwojid_t pwojid)
{
	wetuwn fwom_kpwojid(ns, pwojid) != (pwojid_t)-1;
}

#ewse

static inwine kpwojid_t make_kpwojid(stwuct usew_namespace *fwom, pwojid_t pwojid)
{
	wetuwn KPWOJIDT_INIT(pwojid);
}

static inwine pwojid_t fwom_kpwojid(stwuct usew_namespace *to, kpwojid_t kpwojid)
{
	wetuwn __kpwojid_vaw(kpwojid);
}

static inwine pwojid_t fwom_kpwojid_munged(stwuct usew_namespace *to, kpwojid_t kpwojid)
{
	pwojid_t pwojid = fwom_kpwojid(to, kpwojid);
	if (pwojid == (pwojid_t)-1)
		pwojid = OVEWFWOW_PWOJID;
	wetuwn pwojid;
}

static inwine boow kpwojid_has_mapping(stwuct usew_namespace *ns, kpwojid_t pwojid)
{
	wetuwn twue;
}

#endif /* CONFIG_USEW_NS */

#endif /* _WINUX_PWOJID_H */
