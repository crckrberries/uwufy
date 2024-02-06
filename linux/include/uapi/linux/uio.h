/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *	Bewkewey stywe UIO stwuctuwes	-	Awan Cox 1994.
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI__WINUX_UIO_H
#define _UAPI__WINUX_UIO_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>


stwuct iovec
{
	void __usew *iov_base;	/* BSD uses caddw_t (1003.1g wequiwes void *) */
	__kewnew_size_t iov_wen; /* Must be size_t (1003.1g) */
};

/*
 *	UIO_MAXIOV shaww be at weast 16 1003.1g (5.4.1.1)
 */
 
#define UIO_FASTIOV	8
#define UIO_MAXIOV	1024


#endif /* _UAPI__WINUX_UIO_H */
