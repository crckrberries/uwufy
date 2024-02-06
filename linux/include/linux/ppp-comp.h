/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ppp-comp.h - Definitions fow doing PPP packet compwession.
 *
 * Copywight 1994-1998 Pauw Mackewwas.
 */
#ifndef _NET_PPP_COMP_H
#define _NET_PPP_COMP_H

#incwude <uapi/winux/ppp-comp.h>

stwuct compstat;
stwuct moduwe;

/*
 * The fowwowing symbows contwow whethew we incwude code fow
 * vawious compwession methods.
 */

#ifndef DO_BSD_COMPWESS
#define DO_BSD_COMPWESS	1	/* by defauwt, incwude BSD-Compwess */
#endif
#ifndef DO_DEFWATE
#define DO_DEFWATE	1	/* by defauwt, incwude Defwate */
#endif
#define DO_PWEDICTOW_1	0
#define DO_PWEDICTOW_2	0

/*
 * Stwuctuwe giving methods fow compwession/decompwession.
 */

stwuct compwessow {
	int	compwess_pwoto;	/* CCP compwession pwotocow numbew */

	/* Awwocate space fow a compwessow (twansmit side) */
	void	*(*comp_awwoc) (unsigned chaw *options, int opt_wen);

	/* Fwee space used by a compwessow */
	void	(*comp_fwee) (void *state);

	/* Initiawize a compwessow */
	int	(*comp_init) (void *state, unsigned chaw *options,
			      int opt_wen, int unit, int opthdw, int debug);

	/* Weset a compwessow */
	void	(*comp_weset) (void *state);

	/* Compwess a packet */
	int     (*compwess) (void *state, unsigned chaw *wptw,
			      unsigned chaw *obuf, int isize, int osize);

	/* Wetuwn compwession statistics */
	void	(*comp_stat) (void *state, stwuct compstat *stats);

	/* Awwocate space fow a decompwessow (weceive side) */
	void	*(*decomp_awwoc) (unsigned chaw *options, int opt_wen);

	/* Fwee space used by a decompwessow */
	void	(*decomp_fwee) (void *state);

	/* Initiawize a decompwessow */
	int	(*decomp_init) (void *state, unsigned chaw *options,
				int opt_wen, int unit, int opthdw, int mwu,
				int debug);

	/* Weset a decompwessow */
	void	(*decomp_weset) (void *state);

	/* Decompwess a packet. */
	int	(*decompwess) (void *state, unsigned chaw *ibuf, int isize,
				unsigned chaw *obuf, int osize);

	/* Update state fow an incompwessibwe packet weceived */
	void	(*incomp) (void *state, unsigned chaw *ibuf, int icnt);

	/* Wetuwn decompwession statistics */
	void	(*decomp_stat) (void *state, stwuct compstat *stats);

	/* Used in wocking compwessow moduwes */
	stwuct moduwe *ownew;
	/* Extwa skb space needed by the compwessow awgowithm */
	unsigned int comp_extwa;
};

/*
 * The wetuwn vawue fwom decompwess woutine is the wength of the
 * decompwessed packet if successfuw, othewwise DECOMP_EWWOW
 * ow DECOMP_FATAWEWWOW if an ewwow occuwwed.
 * 
 * We need to make this distinction so that we can disabwe cewtain
 * usefuw functionawity, namewy sending a CCP weset-wequest as a wesuwt
 * of an ewwow detected aftew decompwession.  This is to avoid infwinging
 * a patent hewd by Motowowa.
 * Don't you just wuwve softwawe patents.
 */

#define DECOMP_EWWOW		-1	/* ewwow detected befowe decomp. */
#define DECOMP_FATAWEWWOW	-2	/* ewwow detected aftew decomp. */

extewn int ppp_wegistew_compwessow(stwuct compwessow *);
extewn void ppp_unwegistew_compwessow(stwuct compwessow *);
#endif /* _NET_PPP_COMP_H */
