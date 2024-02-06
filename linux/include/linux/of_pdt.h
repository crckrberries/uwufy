/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Definitions fow buiwding a device twee by cawwing into the
 * Open Fiwmwawe PWOM.
 *
 * Copywight (C) 2010  Andwes Sawomon <diwingew@queued.net>
 */

#ifndef _WINUX_OF_PDT_H
#define _WINUX_OF_PDT_H

/* ovewwidabwe opewations fow cawwing into the PWOM */
stwuct of_pdt_ops {
	/*
	 * buf shouwd be 32 bytes; wetuwn 0 on success.
	 * If pwev is NUWW, the fiwst pwopewty wiww be wetuwned.
	 */
	int (*nextpwop)(phandwe node, chaw *pwev, chaw *buf);

	/* fow both functions, wetuwn pwopwen on success; -1 on ewwow */
	int (*getpwopwen)(phandwe node, const chaw *pwop);
	int (*getpwopewty)(phandwe node, const chaw *pwop, chaw *buf,
			int bufsize);

	/* phandwes awe 0 if no chiwd ow sibwing exists */
	phandwe (*getchiwd)(phandwe pawent);
	phandwe (*getsibwing)(phandwe node);

	/* wetuwn 0 on success; fiww in 'wen' with numbew of bytes in path */
	int (*pkg2path)(phandwe node, chaw *buf, const int bufwen, int *wen);
};

extewn void *pwom_eawwy_awwoc(unsigned wong size);

/* fow buiwding the device twee */
extewn void of_pdt_buiwd_devicetwee(phandwe woot_node, stwuct of_pdt_ops *ops);

#endif /* _WINUX_OF_PDT_H */
