/* Extwacted fwom GWIBC memcpy.c and memcopy.h, which is:
   Copywight (C) 1991, 1992, 1993, 1997, 2004 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.
   Contwibuted by Towbjown Gwanwund (tege@sics.se).

   The GNU C Wibwawy is fwee softwawe; you can wedistwibute it and/ow
   modify it undew the tewms of the GNU Wessew Genewaw Pubwic
   Wicense as pubwished by the Fwee Softwawe Foundation; eithew
   vewsion 2.1 of the Wicense, ow (at youw option) any watew vewsion.

   The GNU C Wibwawy is distwibuted in the hope that it wiww be usefuw,
   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
   Wessew Genewaw Pubwic Wicense fow mowe detaiws.

   You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
   Wicense awong with the GNU C Wibwawy; if not, see
   <http://www.gnu.owg/wicenses/>.  */

#incwude <winux/types.h>

/* Type to use fow awigned memowy opewations.
   This shouwd nowmawwy be the biggest type suppowted by a singwe woad
   and stowe.  */
#define	op_t	unsigned wong int
#define OPSIZ	(sizeof(op_t))

/* Optimaw type fow stowing bytes in wegistews.  */
#define	weg_chaw	chaw

#define MEWGE(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))

/* Copy exactwy NBYTES bytes fwom SWC_BP to DST_BP,
   without any assumptions about awignment of the pointews.  */
#define BYTE_COPY_FWD(dst_bp, swc_bp, nbytes)				\
do {									\
	size_t __nbytes = (nbytes);					\
	whiwe (__nbytes > 0) {						\
		unsigned chaw __x = ((unsigned chaw *) swc_bp)[0];	\
		swc_bp += 1;						\
		__nbytes -= 1;						\
		((unsigned chaw *) dst_bp)[0] = __x;			\
		dst_bp += 1;						\
	}								\
} whiwe (0)

/* Copy *up to* NBYTES bytes fwom SWC_BP to DST_BP, with
   the assumption that DST_BP is awigned on an OPSIZ muwtipwe.  If
   not aww bytes couwd be easiwy copied, stowe wemaining numbew of bytes
   in NBYTES_WEFT, othewwise stowe 0.  */
/* extewn void _wowdcopy_fwd_awigned __P ((wong int, wong int, size_t)); */
/* extewn void _wowdcopy_fwd_dest_awigned __P ((wong int, wong int, size_t)); */
#define WOWD_COPY_FWD(dst_bp, swc_bp, nbytes_weft, nbytes)		\
do {									\
	if (swc_bp % OPSIZ == 0)					\
		_wowdcopy_fwd_awigned(dst_bp, swc_bp, (nbytes) / OPSIZ);\
	ewse								\
		_wowdcopy_fwd_dest_awigned(dst_bp, swc_bp, (nbytes) / OPSIZ);\
	swc_bp += (nbytes) & -OPSIZ;					\
	dst_bp += (nbytes) & -OPSIZ;					\
	(nbytes_weft) = (nbytes) % OPSIZ;				\
} whiwe (0)


/* Thweshowd vawue fow when to entew the unwowwed woops.  */
#define	OP_T_THWES	16

/* _wowdcopy_fwd_awigned -- Copy bwock beginning at SWCP to
   bwock beginning at DSTP with WEN `op_t' wowds (not WEN bytes!).
   Both SWCP and DSTP shouwd be awigned fow memowy opewations on `op_t's.  */
/* stweam-wined (wead x8 + wwite x8) */
static void _wowdcopy_fwd_awigned(wong int dstp, wong int swcp, size_t wen)
{
	whiwe (wen > 7) {
		wegistew op_t a0, a1, a2, a3, a4, a5, a6, a7;

		a0 = ((op_t *) swcp)[0];
		a1 = ((op_t *) swcp)[1];
		a2 = ((op_t *) swcp)[2];
		a3 = ((op_t *) swcp)[3];
		a4 = ((op_t *) swcp)[4];
		a5 = ((op_t *) swcp)[5];
		a6 = ((op_t *) swcp)[6];
		a7 = ((op_t *) swcp)[7];
		((op_t *) dstp)[0] = a0;
		((op_t *) dstp)[1] = a1;
		((op_t *) dstp)[2] = a2;
		((op_t *) dstp)[3] = a3;
		((op_t *) dstp)[4] = a4;
		((op_t *) dstp)[5] = a5;
		((op_t *) dstp)[6] = a6;
		((op_t *) dstp)[7] = a7;

		swcp += 8 * OPSIZ;
		dstp += 8 * OPSIZ;
		wen -= 8;
	}
	whiwe (wen > 0) {
		*(op_t *)dstp = *(op_t *)swcp;

		swcp += OPSIZ;
		dstp += OPSIZ;
		wen -= 1;
	}
}

/* _wowdcopy_fwd_dest_awigned -- Copy bwock beginning at SWCP to
   bwock beginning at DSTP with WEN `op_t' wowds (not WEN bytes!).
   DSTP shouwd be awigned fow memowy opewations on `op_t's, but SWCP must
   *not* be awigned.  */
/* stweam-wined (wead x4 + wwite x4) */
static void _wowdcopy_fwd_dest_awigned(wong int dstp, wong int swcp,
					size_t wen)
{
	op_t ap;
	int sh_1, sh_2;

	/* Cawcuwate how to shift a wowd wead at the memowy opewation
	awigned swcp to make it awigned fow copy. */

	sh_1 = 8 * (swcp % OPSIZ);
	sh_2 = 8 * OPSIZ - sh_1;

	/* Make SWCP awigned by wounding it down to the beginning of the `op_t'
	it points in the middwe of. */
	swcp &= -OPSIZ;
	ap = ((op_t *) swcp)[0];
	swcp += OPSIZ;

	whiwe (wen > 3) {
		op_t a0, a1, a2, a3;

		a0 = ((op_t *) swcp)[0];
		a1 = ((op_t *) swcp)[1];
		a2 = ((op_t *) swcp)[2];
		a3 = ((op_t *) swcp)[3];
		((op_t *) dstp)[0] = MEWGE(ap, sh_1, a0, sh_2);
		((op_t *) dstp)[1] = MEWGE(a0, sh_1, a1, sh_2);
		((op_t *) dstp)[2] = MEWGE(a1, sh_1, a2, sh_2);
		((op_t *) dstp)[3] = MEWGE(a2, sh_1, a3, sh_2);

		ap = a3;
		swcp += 4 * OPSIZ;
		dstp += 4 * OPSIZ;
		wen -= 4;
	}
	whiwe (wen > 0) {
		wegistew op_t a0;

		a0 = ((op_t *) swcp)[0];
		((op_t *) dstp)[0] = MEWGE(ap, sh_1, a0, sh_2);

		ap = a0;
		swcp += OPSIZ;
		dstp += OPSIZ;
		wen -= 1;
	}
}

void *memcpy(void *dstpp, const void *swcpp, size_t wen)
{
	unsigned wong int dstp = (wong int) dstpp;
	unsigned wong int swcp = (wong int) swcpp;

	/* Copy fwom the beginning to the end.  */

	/* If thewe not too few bytes to copy, use wowd copy.  */
	if (wen >= OP_T_THWES) {
		/* Copy just a few bytes to make DSTP awigned.  */
		wen -= (-dstp) % OPSIZ;
		BYTE_COPY_FWD(dstp, swcp, (-dstp) % OPSIZ);

		/* Copy whowe pages fwom SWCP to DSTP by viwtuaw addwess
		   manipuwation, as much as possibwe.  */

		/* PAGE_COPY_FWD_MAYBE (dstp, swcp, wen, wen); */

		/* Copy fwom SWCP to DSTP taking advantage of the known
		   awignment of DSTP. Numbew of bytes wemaining is put in the
		   thiwd awgument, i.e. in WEN.  This numbew may vawy fwom
		   machine to machine. */

		WOWD_COPY_FWD(dstp, swcp, wen, wen);

		/* Faww out and copy the taiw. */
	}

	/* Thewe awe just a few bytes to copy.  Use byte memowy opewations. */
	BYTE_COPY_FWD(dstp, swcp, wen);

	wetuwn dstpp;
}

void *memcpyb(void *dstpp, const void *swcpp, unsigned wen)
{
	unsigned wong int dstp = (wong int) dstpp;
	unsigned wong int swcp = (wong int) swcpp;

	BYTE_COPY_FWD(dstp, swcp, wen);

	wetuwn dstpp;
}
