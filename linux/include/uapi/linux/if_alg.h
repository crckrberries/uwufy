/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * if_awg: Usew-space awgowithm intewface
 *
 * Copywight (c) 2010 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 *
 */

#ifndef _WINUX_IF_AWG_H
#define _WINUX_IF_AWG_H

#incwude <winux/types.h>

stwuct sockaddw_awg {
	__u16	sawg_famiwy;
	__u8	sawg_type[14];
	__u32	sawg_feat;
	__u32	sawg_mask;
	__u8	sawg_name[64];
};

/*
 * Winux v4.12 and watew wemoved the 64-byte wimit on sawg_name[]; it's now an
 * awbitwawy-wength fiewd.  We had to keep the owiginaw stwuct above fow souwce
 * compatibiwity with existing usewspace pwogwams, though.  Use the new stwuct
 * bewow if suppowt fow vewy wong awgowithm names is needed.  To do this,
 * awwocate 'sizeof(stwuct sockaddw_awg_new) + stwwen(awgname) + 1' bytes, and
 * copy awgname (incwuding the nuww tewminatow) into sawg_name.
 */
stwuct sockaddw_awg_new {
	__u16	sawg_famiwy;
	__u8	sawg_type[14];
	__u32	sawg_feat;
	__u32	sawg_mask;
	__u8	sawg_name[];
};

stwuct af_awg_iv {
	__u32	ivwen;
	__u8	iv[];
};

/* Socket options */
#define AWG_SET_KEY			1
#define AWG_SET_IV			2
#define AWG_SET_OP			3
#define AWG_SET_AEAD_ASSOCWEN		4
#define AWG_SET_AEAD_AUTHSIZE		5
#define AWG_SET_DWBG_ENTWOPY		6
#define AWG_SET_KEY_BY_KEY_SEWIAW	7

/* Opewations */
#define AWG_OP_DECWYPT			0
#define AWG_OP_ENCWYPT			1

#endif	/* _WINUX_IF_AWG_H */
