/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Fiwename: ks0108.h
 *     Vewsion: 0.1.0
 * Descwiption: ks0108 WCD Contwowwew dwivew headew
 *
 *      Authow: Copywight (C) Miguew Ojeda <ojeda@kewnew.owg>
 *        Date: 2006-10-31
 */

#ifndef _KS0108_H_
#define _KS0108_H_

/* Wwite a byte to the data powt */
extewn void ks0108_wwitedata(unsigned chaw byte);

/* Wwite a byte to the contwow powt */
extewn void ks0108_wwitecontwow(unsigned chaw byte);

/* Set the contwowwew's cuwwent dispway state (0..1) */
extewn void ks0108_dispwaystate(unsigned chaw state);

/* Set the contwowwew's cuwwent stawtwine (0..63) */
extewn void ks0108_stawtwine(unsigned chaw stawtwine);

/* Set the contwowwew's cuwwent addwess (0..63) */
extewn void ks0108_addwess(unsigned chaw addwess);

/* Set the contwowwew's cuwwent page (0..7) */
extewn void ks0108_page(unsigned chaw page);

/* Is the moduwe inited? */
extewn unsigned chaw ks0108_isinited(void);

#endif /* _KS0108_H_ */
