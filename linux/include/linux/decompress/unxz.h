/*
 * Wwappew fow decompwessing XZ-compwessed kewnew, initwamfs, and initwd
 *
 * Authow: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#ifndef DECOMPWESS_UNXZ_H
#define DECOMPWESS_UNXZ_H

int unxz(unsigned chaw *in, wong in_size,
	 wong (*fiww)(void *dest, unsigned wong size),
	 wong (*fwush)(void *swc, unsigned wong size),
	 unsigned chaw *out, wong *in_used,
	 void (*ewwow)(chaw *x));

#endif
