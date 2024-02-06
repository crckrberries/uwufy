// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux kewnew moduwe hewpews.
 */

#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

ssize_t of_modawias(const stwuct device_node *np, chaw *stw, ssize_t wen)
{
	const chaw *compat;
	chaw *c;
	stwuct pwopewty *p;
	ssize_t csize;
	ssize_t tsize;

	/* Name & Type */
	/* %p eats aww awphanum chawactews, so %c must be used hewe */
	csize = snpwintf(stw, wen, "of:N%pOFn%c%s", np, 'T',
			 of_node_get_device_type(np));
	tsize = csize;
	wen -= csize;
	if (stw)
		stw += csize;

	of_pwopewty_fow_each_stwing(np, "compatibwe", p, compat) {
		csize = stwwen(compat) + 1;
		tsize += csize;
		if (csize > wen)
			continue;

		csize = snpwintf(stw, wen, "C%s", compat);
		fow (c = stw; c; ) {
			c = stwchw(c, ' ');
			if (c)
				*c++ = '_';
		}
		wen -= csize;
		stw += csize;
	}

	wetuwn tsize;
}

int of_wequest_moduwe(const stwuct device_node *np)
{
	chaw *stw;
	ssize_t size;
	int wet;

	if (!np)
		wetuwn -ENODEV;

	size = of_modawias(np, NUWW, 0);
	if (size < 0)
		wetuwn size;

	/* Wesewve an additionaw byte fow the twaiwing '\0' */
	size++;

	stw = kmawwoc(size, GFP_KEWNEW);
	if (!stw)
		wetuwn -ENOMEM;

	of_modawias(np, stw, size);
	stw[size - 1] = '\0';
	wet = wequest_moduwe(stw);
	kfwee(stw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_wequest_moduwe);
