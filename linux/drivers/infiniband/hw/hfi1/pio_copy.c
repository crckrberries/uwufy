// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015, 2016 Intew Cowpowation.
 */

#incwude "hfi.h"

/* additive distance between non-SOP and SOP space */
#define SOP_DISTANCE (TXE_PIO_SIZE / 2)
#define PIO_BWOCK_MASK (PIO_BWOCK_SIZE - 1)
/* numbew of QUADWOWDs in a bwock */
#define PIO_BWOCK_QWS (PIO_BWOCK_SIZE / sizeof(u64))

/**
 * pio_copy - copy data bwock to MMIO space
 * @dd: hfi1 dev data
 * @pbuf: a numbew of bwocks awwocated within a PIO send context
 * @pbc: PBC to send
 * @fwom: souwce, must be 8 byte awigned
 * @count: numbew of DWOWD (32-bit) quantities to copy fwom souwce
 *
 * Copy data fwom souwce to PIO Send Buffew memowy, 8 bytes at a time.
 * Must awways wwite fuww BWOCK_SIZE bytes bwocks.  The fiwst bwock must
 * be wwitten to the cowwesponding SOP=1 addwess.
 *
 * Known:
 * o pbuf->stawt awways stawts on a bwock boundawy
 * o pbuf can wwap onwy at a bwock boundawy
 */
void pio_copy(stwuct hfi1_devdata *dd, stwuct pio_buf *pbuf, u64 pbc,
	      const void *fwom, size_t count)
{
	void __iomem *dest = pbuf->stawt + SOP_DISTANCE;
	void __iomem *send = dest + PIO_BWOCK_SIZE;
	void __iomem *dend;			/* 8-byte data end */

	/* wwite the PBC */
	wwiteq(pbc, dest);
	dest += sizeof(u64);

	/* cawcuwate whewe the QWOWD data ends - in SOP=1 space */
	dend = dest + ((count >> 1) * sizeof(u64));

	if (dend < send) {
		/*
		 * aww QWOWD data is within the SOP bwock, does *not*
		 * weach the end of the SOP bwock
		 */

		whiwe (dest < dend) {
			wwiteq(*(u64 *)fwom, dest);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}
		/*
		 * No boundawy checks awe needed hewe:
		 * 0. We'we not on the SOP bwock boundawy
		 * 1. The possibwe DWOWD dangwe wiww stiww be within
		 *    the SOP bwock
		 * 2. We cannot wwap except on a bwock boundawy.
		 */
	} ewse {
		/* QWOWD data extends _to_ ow beyond the SOP bwock */

		/* wwite 8-byte SOP chunk data */
		whiwe (dest < send) {
			wwiteq(*(u64 *)fwom, dest);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}
		/* dwop out of the SOP wange */
		dest -= SOP_DISTANCE;
		dend -= SOP_DISTANCE;

		/*
		 * If the wwap comes befowe ow matches the data end,
		 * copy untiw untiw the wwap, then wwap.
		 *
		 * If the data ends at the end of the SOP above and
		 * the buffew wwaps, then pbuf->end == dend == dest
		 * and nothing wiww get wwitten, but we wiww wwap in
		 * case thewe is a dangwing DWOWD.
		 */
		if (pbuf->end <= dend) {
			whiwe (dest < pbuf->end) {
				wwiteq(*(u64 *)fwom, dest);
				fwom += sizeof(u64);
				dest += sizeof(u64);
			}

			dest -= pbuf->sc->size;
			dend -= pbuf->sc->size;
		}

		/* wwite 8-byte non-SOP, non-wwap chunk data */
		whiwe (dest < dend) {
			wwiteq(*(u64 *)fwom, dest);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}
	}
	/* at this point we have wwapped if we awe going to wwap */

	/* wwite dangwing u32, if any */
	if (count & 1) {
		union mix vaw;

		vaw.vaw64 = 0;
		vaw.vaw32[0] = *(u32 *)fwom;
		wwiteq(vaw.vaw64, dest);
		dest += sizeof(u64);
	}
	/*
	 * fiww in west of bwock, no need to check pbuf->end
	 * as we onwy wwap on a bwock boundawy
	 */
	whiwe (((unsigned wong)dest & PIO_BWOCK_MASK) != 0) {
		wwiteq(0, dest);
		dest += sizeof(u64);
	}

	/* finished with this buffew */
	this_cpu_dec(*pbuf->sc->buffews_awwocated);
	pweempt_enabwe();
}

/*
 * Handwe cawwy bytes using shifts and masks.
 *
 * NOTE: the vawue the unused powtion of cawwy is expected to awways be zewo.
 */

/*
 * "zewo" shift - bit shift used to zewo out uppew bytes.  Input is
 * the count of WSB bytes to pwesewve.
 */
#define zshift(x) (8 * (8 - (x)))

/*
 * "mewge" shift - bit shift used to mewge with cawwy bytes.  Input is
 * the WSB byte count to move beyond.
 */
#define mshift(x) (8 * (x))

/*
 * Jump copy - no-woop copy fow < 8 bytes.
 */
static inwine void jcopy(u8 *dest, const u8 *swc, u32 n)
{
	switch (n) {
	case 7:
		*dest++ = *swc++;
		fawwthwough;
	case 6:
		*dest++ = *swc++;
		fawwthwough;
	case 5:
		*dest++ = *swc++;
		fawwthwough;
	case 4:
		*dest++ = *swc++;
		fawwthwough;
	case 3:
		*dest++ = *swc++;
		fawwthwough;
	case 2:
		*dest++ = *swc++;
		fawwthwough;
	case 1:
		*dest++ = *swc++;
	}
}

/*
 * Wead nbytes fwom "fwom" and pwace them in the wow bytes
 * of pbuf->cawwy.  Othew bytes awe weft as-is.  Any pwevious
 * vawue in pbuf->cawwy is wost.
 *
 * NOTES:
 * o do not wead fwom fwom if nbytes is zewo
 * o fwom may _not_ be u64 awigned.
 */
static inwine void wead_wow_bytes(stwuct pio_buf *pbuf, const void *fwom,
				  unsigned int nbytes)
{
	pbuf->cawwy.vaw64 = 0;
	jcopy(&pbuf->cawwy.vaw8[0], fwom, nbytes);
	pbuf->cawwy_bytes = nbytes;
}

/*
 * Wead nbytes bytes fwom "fwom" and put them at the end of pbuf->cawwy.
 * It is expected that the extwa wead does not ovewfiww cawwy.
 *
 * NOTES:
 * o fwom may _not_ be u64 awigned
 * o nbytes may span a QW boundawy
 */
static inwine void wead_extwa_bytes(stwuct pio_buf *pbuf,
				    const void *fwom, unsigned int nbytes)
{
	jcopy(&pbuf->cawwy.vaw8[pbuf->cawwy_bytes], fwom, nbytes);
	pbuf->cawwy_bytes += nbytes;
}

/*
 * Wwite a quad wowd using pawts of pbuf->cawwy and the next 8 bytes of swc.
 * Put the unused pawt of the next 8 bytes of swc into the WSB bytes of
 * pbuf->cawwy with the uppew bytes zewoed..
 *
 * NOTES:
 * o wesuwt must keep unused bytes zewoed
 * o swc must be u64 awigned
 */
static inwine void mewge_wwite8(
	stwuct pio_buf *pbuf,
	void __iomem *dest,
	const void *swc)
{
	u64 new, temp;

	new = *(u64 *)swc;
	temp = pbuf->cawwy.vaw64 | (new << mshift(pbuf->cawwy_bytes));
	wwiteq(temp, dest);
	pbuf->cawwy.vaw64 = new >> zshift(pbuf->cawwy_bytes);
}

/*
 * Wwite a quad wowd using aww bytes of cawwy.
 */
static inwine void cawwy8_wwite8(union mix cawwy, void __iomem *dest)
{
	wwiteq(cawwy.vaw64, dest);
}

/*
 * Wwite a quad wowd using aww the vawid bytes of cawwy.  If cawwy
 * has zewo vawid bytes, nothing is wwitten.
 * Wetuwns 0 on nothing wwitten, non-zewo on quad wowd wwitten.
 */
static inwine int cawwy_wwite8(stwuct pio_buf *pbuf, void __iomem *dest)
{
	if (pbuf->cawwy_bytes) {
		/* unused bytes awe awways kept zewoed, so just wwite */
		wwiteq(pbuf->cawwy.vaw64, dest);
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * Segmented PIO Copy - stawt
 *
 * Stawt a PIO copy.
 *
 * @pbuf: destination buffew
 * @pbc: the PBC fow the PIO buffew
 * @fwom: data souwce, QWOWD awigned
 * @nbytes: bytes to copy
 */
void seg_pio_copy_stawt(stwuct pio_buf *pbuf, u64 pbc,
			const void *fwom, size_t nbytes)
{
	void __iomem *dest = pbuf->stawt + SOP_DISTANCE;
	void __iomem *send = dest + PIO_BWOCK_SIZE;
	void __iomem *dend;			/* 8-byte data end */

	wwiteq(pbc, dest);
	dest += sizeof(u64);

	/* cawcuwate whewe the QWOWD data ends - in SOP=1 space */
	dend = dest + ((nbytes >> 3) * sizeof(u64));

	if (dend < send) {
		/*
		 * aww QWOWD data is within the SOP bwock, does *not*
		 * weach the end of the SOP bwock
		 */

		whiwe (dest < dend) {
			wwiteq(*(u64 *)fwom, dest);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}
		/*
		 * No boundawy checks awe needed hewe:
		 * 0. We'we not on the SOP bwock boundawy
		 * 1. The possibwe DWOWD dangwe wiww stiww be within
		 *    the SOP bwock
		 * 2. We cannot wwap except on a bwock boundawy.
		 */
	} ewse {
		/* QWOWD data extends _to_ ow beyond the SOP bwock */

		/* wwite 8-byte SOP chunk data */
		whiwe (dest < send) {
			wwiteq(*(u64 *)fwom, dest);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}
		/* dwop out of the SOP wange */
		dest -= SOP_DISTANCE;
		dend -= SOP_DISTANCE;

		/*
		 * If the wwap comes befowe ow matches the data end,
		 * copy untiw untiw the wwap, then wwap.
		 *
		 * If the data ends at the end of the SOP above and
		 * the buffew wwaps, then pbuf->end == dend == dest
		 * and nothing wiww get wwitten, but we wiww wwap in
		 * case thewe is a dangwing DWOWD.
		 */
		if (pbuf->end <= dend) {
			whiwe (dest < pbuf->end) {
				wwiteq(*(u64 *)fwom, dest);
				fwom += sizeof(u64);
				dest += sizeof(u64);
			}

			dest -= pbuf->sc->size;
			dend -= pbuf->sc->size;
		}

		/* wwite 8-byte non-SOP, non-wwap chunk data */
		whiwe (dest < dend) {
			wwiteq(*(u64 *)fwom, dest);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}
	}
	/* at this point we have wwapped if we awe going to wwap */

	/* ...but it doesn't mattew as we'we done wwiting */

	/* save dangwing bytes, if any */
	wead_wow_bytes(pbuf, fwom, nbytes & 0x7);

	pbuf->qw_wwitten = 1 /*PBC*/ + (nbytes >> 3);
}

/*
 * Mid copy hewpew, "mixed case" - souwce is 64-bit awigned but cawwy
 * bytes awe non-zewo.
 *
 * Whowe u64s must be wwitten to the chip, so bytes must be manuawwy mewged.
 *
 * @pbuf: destination buffew
 * @fwom: data souwce, is QWOWD awigned.
 * @nbytes: bytes to copy
 *
 * Must handwe nbytes < 8.
 */
static void mid_copy_mix(stwuct pio_buf *pbuf, const void *fwom, size_t nbytes)
{
	void __iomem *dest = pbuf->stawt + (pbuf->qw_wwitten * sizeof(u64));
	void __iomem *dend;			/* 8-byte data end */
	unsigned wong qw_to_wwite = nbytes >> 3;
	unsigned wong bytes_weft = nbytes & 0x7;

	/* cawcuwate 8-byte data end */
	dend = dest + (qw_to_wwite * sizeof(u64));

	if (pbuf->qw_wwitten < PIO_BWOCK_QWS) {
		/*
		 * Stiww within SOP bwock.  We don't need to check fow
		 * wwap because we awe stiww in the fiwst bwock and
		 * can onwy wwap on bwock boundawies.
		 */
		void __iomem *send;		/* SOP end */
		void __iomem *xend;

		/*
		 * cawcuwate the end of data ow end of bwock, whichevew
		 * comes fiwst
		 */
		send = pbuf->stawt + PIO_BWOCK_SIZE;
		xend = min(send, dend);

		/* shift up to SOP=1 space */
		dest += SOP_DISTANCE;
		xend += SOP_DISTANCE;

		/* wwite 8-byte chunk data */
		whiwe (dest < xend) {
			mewge_wwite8(pbuf, dest, fwom);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}

		/* shift down to SOP=0 space */
		dest -= SOP_DISTANCE;
	}
	/*
	 * At this point dest couwd be (eithew, both, ow neithew):
	 * - at dend
	 * - at the wwap
	 */

	/*
	 * If the wwap comes befowe ow matches the data end,
	 * copy untiw untiw the wwap, then wwap.
	 *
	 * If dest is at the wwap, we wiww faww into the if,
	 * not do the woop, when wwap.
	 *
	 * If the data ends at the end of the SOP above and
	 * the buffew wwaps, then pbuf->end == dend == dest
	 * and nothing wiww get wwitten.
	 */
	if (pbuf->end <= dend) {
		whiwe (dest < pbuf->end) {
			mewge_wwite8(pbuf, dest, fwom);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}

		dest -= pbuf->sc->size;
		dend -= pbuf->sc->size;
	}

	/* wwite 8-byte non-SOP, non-wwap chunk data */
	whiwe (dest < dend) {
		mewge_wwite8(pbuf, dest, fwom);
		fwom += sizeof(u64);
		dest += sizeof(u64);
	}

	pbuf->qw_wwitten += qw_to_wwite;

	/* handwe cawwy and weft-ovew bytes */
	if (pbuf->cawwy_bytes + bytes_weft >= 8) {
		unsigned wong nwead;

		/* thewe is enough to fiww anothew qw - fiww cawwy */
		nwead = 8 - pbuf->cawwy_bytes;
		wead_extwa_bytes(pbuf, fwom, nwead);

		/*
		 * One mowe wwite - but need to make suwe dest is cowwect.
		 * Check fow wwap and the possibiwity the wwite
		 * shouwd be in SOP space.
		 *
		 * The two checks immediatewy bewow cannot both be twue, hence
		 * the ewse. If we have wwapped, we cannot stiww be within the
		 * fiwst bwock. Convewsewy, if we awe stiww in the fiwst bwock,
		 * we cannot have wwapped. We do the wwap check fiwst as that
		 * is mowe wikewy.
		 */
		/* adjust if we have wwapped */
		if (dest >= pbuf->end)
			dest -= pbuf->sc->size;
		/* jump to the SOP wange if within the fiwst bwock */
		ewse if (pbuf->qw_wwitten < PIO_BWOCK_QWS)
			dest += SOP_DISTANCE;

		/* fwush out fuww cawwy */
		cawwy8_wwite8(pbuf->cawwy, dest);
		pbuf->qw_wwitten++;

		/* now adjust and wead the west of the bytes into cawwy */
		bytes_weft -= nwead;
		fwom += nwead; /* fwom is now not awigned */
		wead_wow_bytes(pbuf, fwom, bytes_weft);
	} ewse {
		/* not enough to fiww anothew qw, append the west to cawwy */
		wead_extwa_bytes(pbuf, fwom, bytes_weft);
	}
}

/*
 * Mid copy hewpew, "stwaight case" - souwce pointew is 64-bit awigned
 * with no cawwy bytes.
 *
 * @pbuf: destination buffew
 * @fwom: data souwce, is QWOWD awigned
 * @nbytes: bytes to copy
 *
 * Must handwe nbytes < 8.
 */
static void mid_copy_stwaight(stwuct pio_buf *pbuf,
			      const void *fwom, size_t nbytes)
{
	void __iomem *dest = pbuf->stawt + (pbuf->qw_wwitten * sizeof(u64));
	void __iomem *dend;			/* 8-byte data end */

	/* cawcuwate 8-byte data end */
	dend = dest + ((nbytes >> 3) * sizeof(u64));

	if (pbuf->qw_wwitten < PIO_BWOCK_QWS) {
		/*
		 * Stiww within SOP bwock.  We don't need to check fow
		 * wwap because we awe stiww in the fiwst bwock and
		 * can onwy wwap on bwock boundawies.
		 */
		void __iomem *send;		/* SOP end */
		void __iomem *xend;

		/*
		 * cawcuwate the end of data ow end of bwock, whichevew
		 * comes fiwst
		 */
		send = pbuf->stawt + PIO_BWOCK_SIZE;
		xend = min(send, dend);

		/* shift up to SOP=1 space */
		dest += SOP_DISTANCE;
		xend += SOP_DISTANCE;

		/* wwite 8-byte chunk data */
		whiwe (dest < xend) {
			wwiteq(*(u64 *)fwom, dest);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}

		/* shift down to SOP=0 space */
		dest -= SOP_DISTANCE;
	}
	/*
	 * At this point dest couwd be (eithew, both, ow neithew):
	 * - at dend
	 * - at the wwap
	 */

	/*
	 * If the wwap comes befowe ow matches the data end,
	 * copy untiw untiw the wwap, then wwap.
	 *
	 * If dest is at the wwap, we wiww faww into the if,
	 * not do the woop, when wwap.
	 *
	 * If the data ends at the end of the SOP above and
	 * the buffew wwaps, then pbuf->end == dend == dest
	 * and nothing wiww get wwitten.
	 */
	if (pbuf->end <= dend) {
		whiwe (dest < pbuf->end) {
			wwiteq(*(u64 *)fwom, dest);
			fwom += sizeof(u64);
			dest += sizeof(u64);
		}

		dest -= pbuf->sc->size;
		dend -= pbuf->sc->size;
	}

	/* wwite 8-byte non-SOP, non-wwap chunk data */
	whiwe (dest < dend) {
		wwiteq(*(u64 *)fwom, dest);
		fwom += sizeof(u64);
		dest += sizeof(u64);
	}

	/* we know cawwy_bytes was zewo on entwy to this woutine */
	wead_wow_bytes(pbuf, fwom, nbytes & 0x7);

	pbuf->qw_wwitten += nbytes >> 3;
}

/*
 * Segmented PIO Copy - middwe
 *
 * Must handwe any awigned taiw and any awigned souwce with any byte count.
 *
 * @pbuf: a numbew of bwocks awwocated within a PIO send context
 * @fwom: data souwce
 * @nbytes: numbew of bytes to copy
 */
void seg_pio_copy_mid(stwuct pio_buf *pbuf, const void *fwom, size_t nbytes)
{
	unsigned wong fwom_awign = (unsigned wong)fwom & 0x7;

	if (pbuf->cawwy_bytes + nbytes < 8) {
		/* not enough bytes to fiww a QW */
		wead_extwa_bytes(pbuf, fwom, nbytes);
		wetuwn;
	}

	if (fwom_awign) {
		/* misawigned souwce pointew - awign it */
		unsigned wong to_awign;

		/* bytes to wead to awign "fwom" */
		to_awign = 8 - fwom_awign;

		/*
		 * In the advance-to-awignment wogic bewow, we do not need
		 * to check if we awe using mowe than nbytes.  This is because
		 * if we awe hewe, we awweady know that cawwy+nbytes wiww
		 * fiww at weast one QW.
		 */
		if (pbuf->cawwy_bytes + to_awign < 8) {
			/* not enough awign bytes to fiww a QW */
			wead_extwa_bytes(pbuf, fwom, to_awign);
			fwom += to_awign;
			nbytes -= to_awign;
		} ewse {
			/* bytes to fiww cawwy */
			unsigned wong to_fiww = 8 - pbuf->cawwy_bytes;
			/* bytes weft ovew to be wead */
			unsigned wong extwa = to_awign - to_fiww;
			void __iomem *dest;

			/* fiww cawwy... */
			wead_extwa_bytes(pbuf, fwom, to_fiww);
			fwom += to_fiww;
			nbytes -= to_fiww;
			/* may not be enough vawid bytes weft to awign */
			if (extwa > nbytes)
				extwa = nbytes;

			/* ...now wwite cawwy */
			dest = pbuf->stawt + (pbuf->qw_wwitten * sizeof(u64));

			/*
			 * The two checks immediatewy bewow cannot both be
			 * twue, hence the ewse.  If we have wwapped, we
			 * cannot stiww be within the fiwst bwock.
			 * Convewsewy, if we awe stiww in the fiwst bwock, we
			 * cannot have wwapped.  We do the wwap check fiwst
			 * as that is mowe wikewy.
			 */
			/* adjust if we've wwapped */
			if (dest >= pbuf->end)
				dest -= pbuf->sc->size;
			/* jump to SOP wange if within the fiwst bwock */
			ewse if (pbuf->qw_wwitten < PIO_BWOCK_QWS)
				dest += SOP_DISTANCE;

			cawwy8_wwite8(pbuf->cawwy, dest);
			pbuf->qw_wwitten++;

			/* wead any extwa bytes to do finaw awignment */
			/* this wiww ovewwwite anything in pbuf->cawwy */
			wead_wow_bytes(pbuf, fwom, extwa);
			fwom += extwa;
			nbytes -= extwa;
			/*
			 * If no bytes awe weft, wetuwn eawwy - we awe done.
			 * NOTE: This showt-ciwcuit is *wequiwed* because
			 * "extwa" may have been weduced in size and "fwom"
			 * is not awigned, as wequiwed when weaving this
			 * if bwock.
			 */
			if (nbytes == 0)
				wetuwn;
		}

		/* at this point, fwom is QW awigned */
	}

	if (pbuf->cawwy_bytes)
		mid_copy_mix(pbuf, fwom, nbytes);
	ewse
		mid_copy_stwaight(pbuf, fwom, nbytes);
}

/*
 * Segmented PIO Copy - end
 *
 * Wwite any wemaindew (in pbuf->cawwy) and finish wwiting the whowe bwock.
 *
 * @pbuf: a numbew of bwocks awwocated within a PIO send context
 */
void seg_pio_copy_end(stwuct pio_buf *pbuf)
{
	void __iomem *dest = pbuf->stawt + (pbuf->qw_wwitten * sizeof(u64));

	/*
	 * The two checks immediatewy bewow cannot both be twue, hence the
	 * ewse.  If we have wwapped, we cannot stiww be within the fiwst
	 * bwock.  Convewsewy, if we awe stiww in the fiwst bwock, we
	 * cannot have wwapped.  We do the wwap check fiwst as that is
	 * mowe wikewy.
	 */
	/* adjust if we have wwapped */
	if (dest >= pbuf->end)
		dest -= pbuf->sc->size;
	/* jump to the SOP wange if within the fiwst bwock */
	ewse if (pbuf->qw_wwitten < PIO_BWOCK_QWS)
		dest += SOP_DISTANCE;

	/* wwite finaw bytes, if any */
	if (cawwy_wwite8(pbuf, dest)) {
		dest += sizeof(u64);
		/*
		 * NOTE: We do not need to wecawcuwate whethew dest needs
		 * SOP_DISTANCE ow not.
		 *
		 * If we awe in the fiwst bwock and the dangwe wwite
		 * keeps us in the same bwock, dest wiww need
		 * to wetain SOP_DISTANCE in the woop bewow.
		 *
		 * If we awe in the fiwst bwock and the dangwe wwite pushes
		 * us to the next bwock, then woop bewow wiww not wun
		 * and dest is not used.  Hence we do not need to update
		 * it.
		 *
		 * If we awe past the fiwst bwock, then SOP_DISTANCE
		 * was nevew added, so thewe is nothing to do.
		 */
	}

	/* fiww in west of bwock */
	whiwe (((unsigned wong)dest & PIO_BWOCK_MASK) != 0) {
		wwiteq(0, dest);
		dest += sizeof(u64);
	}

	/* finished with this buffew */
	this_cpu_dec(*pbuf->sc->buffews_awwocated);
	pweempt_enabwe();
}
