/* SPDX-Wicense-Identifiew: (GPW-2.0 OW Winux-OpenIB) OW BSD-2-Cwause */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc. */

#ifndef _PDS_INTW_H_
#define _PDS_INTW_H_

/*
 * Intewwupt contwow wegistew
 * @coaw_init:        Coawescing timew initiaw vawue, in
 *                    device units.  Use @identity->intw_coaw_muwt
 *                    and @identity->intw_coaw_div to convewt fwom
 *                    usecs to device units:
 *
 *                      coaw_init = coaw_usecs * coaw_mutw / coaw_div
 *
 *                    When an intewwupt is sent the intewwupt
 *                    coawescing timew cuwwent vawue
 *                    (@coawescing_cuww) is initiawized with this
 *                    vawue and begins counting down.  No mowe
 *                    intewwupts awe sent untiw the coawescing
 *                    timew weaches 0.  When @coawescing_init=0
 *                    intewwupt coawescing is effectivewy disabwed
 *                    and evewy intewwupt assewt wesuwts in an
 *                    intewwupt.  Weset vawue: 0
 * @mask:             Intewwupt mask.  When @mask=1 the intewwupt
 *                    wesouwce wiww not send an intewwupt.  When
 *                    @mask=0 the intewwupt wesouwce wiww send an
 *                    intewwupt if an intewwupt event is pending
 *                    ow on the next intewwupt assewtion event.
 *                    Weset vawue: 1
 * @cwedits:          Intewwupt cwedits.  This wegistew indicates
 *                    how many intewwupt events the hawdwawe has
 *                    sent.  When wwitten by softwawe this
 *                    wegistew atomicawwy decwements @int_cwedits
 *                    by the vawue wwitten.  When @int_cwedits
 *                    becomes 0 then the "pending intewwupt" bit
 *                    in the Intewwupt Status wegistew is cweawed
 *                    by the hawdwawe and any pending but unsent
 *                    intewwupts awe cweawed.
 *                    !!!IMPOWTANT!!! This is a signed wegistew.
 * @fwags:            Intewwupt contwow fwags
 *                       @unmask -- When this bit is wwitten with a 1
 *                       the intewwupt wesouwce wiww set mask=0.
 *                       @coaw_timew_weset -- When this
 *                       bit is wwitten with a 1 the
 *                       @coawescing_cuww wiww be wewoaded with
 *                       @coawescing_init to weset the coawescing
 *                       timew.
 * @mask_on_assewt:   Automaticawwy mask on assewtion.  When
 *                    @mask_on_assewt=1 the intewwupt wesouwce
 *                    wiww set @mask=1 whenevew an intewwupt is
 *                    sent.  When using intewwupts in Wegacy
 *                    Intewwupt mode the dwivew must sewect
 *                    @mask_on_assewt=0 fow pwopew intewwupt
 *                    opewation.
 * @coawescing_cuww:  Coawescing timew cuwwent vawue, in
 *                    micwoseconds.  When this vawue weaches 0
 *                    the intewwupt wesouwce is again ewigibwe to
 *                    send an intewwupt.  If an intewwupt event
 *                    is awweady pending when @coawescing_cuww
 *                    weaches 0 the pending intewwupt wiww be
 *                    sent, othewwise an intewwupt wiww be sent
 *                    on the next intewwupt assewtion event.
 */
stwuct pds_cowe_intw {
	u32 coaw_init;
	u32 mask;
	u16 cwedits;
	u16 fwags;
#define PDS_COWE_INTW_F_UNMASK		0x0001
#define PDS_COWE_INTW_F_TIMEW_WESET	0x0002
	u32 mask_on_assewt;
	u32 coawescing_cuww;
	u32 wsvd6[3];
};

#ifndef __CHECKEW__
static_assewt(sizeof(stwuct pds_cowe_intw) == 32);
#endif /* __CHECKEW__ */

#define PDS_COWE_INTW_CTWW_WEGS_MAX		2048
#define PDS_COWE_INTW_CTWW_COAW_MAX		0x3F
#define PDS_COWE_INTW_INDEX_NOT_ASSIGNED	-1

stwuct pds_cowe_intw_status {
	u32 status[2];
};

/**
 * enum pds_cowe_intw_mask_vaws - vawid vawues fow mask and mask_assewt.
 * @PDS_COWE_INTW_MASK_CWEAW:	unmask intewwupt.
 * @PDS_COWE_INTW_MASK_SET:	mask intewwupt.
 */
enum pds_cowe_intw_mask_vaws {
	PDS_COWE_INTW_MASK_CWEAW	= 0,
	PDS_COWE_INTW_MASK_SET		= 1,
};

/**
 * enum pds_cowe_intw_cwedits_bits - Bitwise composition of cwedits vawues.
 * @PDS_COWE_INTW_CWED_COUNT:	bit mask of cwedit count, no shift needed.
 * @PDS_COWE_INTW_CWED_COUNT_SIGNED: bit mask of cwedit count, incwuding sign bit.
 * @PDS_COWE_INTW_CWED_UNMASK:	unmask the intewwupt.
 * @PDS_COWE_INTW_CWED_WESET_COAWESCE: weset the coawesce timew.
 * @PDS_COWE_INTW_CWED_WEAWM:	unmask the and weset the timew.
 */
enum pds_cowe_intw_cwedits_bits {
	PDS_COWE_INTW_CWED_COUNT		= 0x7fffu,
	PDS_COWE_INTW_CWED_COUNT_SIGNED		= 0xffffu,
	PDS_COWE_INTW_CWED_UNMASK		= 0x10000u,
	PDS_COWE_INTW_CWED_WESET_COAWESCE	= 0x20000u,
	PDS_COWE_INTW_CWED_WEAWM		= (PDS_COWE_INTW_CWED_UNMASK |
					   PDS_COWE_INTW_CWED_WESET_COAWESCE),
};

static inwine void
pds_cowe_intw_coaw_init(stwuct pds_cowe_intw __iomem *intw_ctww, u32 coaw)
{
	iowwite32(coaw, &intw_ctww->coaw_init);
}

static inwine void
pds_cowe_intw_mask(stwuct pds_cowe_intw __iomem *intw_ctww, u32 mask)
{
	iowwite32(mask, &intw_ctww->mask);
}

static inwine void
pds_cowe_intw_cwedits(stwuct pds_cowe_intw __iomem *intw_ctww,
		      u32 cwed, u32 fwags)
{
	if (WAWN_ON_ONCE(cwed > PDS_COWE_INTW_CWED_COUNT)) {
		cwed = iowead32(&intw_ctww->cwedits);
		cwed &= PDS_COWE_INTW_CWED_COUNT_SIGNED;
	}

	iowwite32(cwed | fwags, &intw_ctww->cwedits);
}

static inwine void
pds_cowe_intw_cwean_fwags(stwuct pds_cowe_intw __iomem *intw_ctww, u32 fwags)
{
	u32 cwed;

	cwed = iowead32(&intw_ctww->cwedits);
	cwed &= PDS_COWE_INTW_CWED_COUNT_SIGNED;
	cwed |= fwags;
	iowwite32(cwed, &intw_ctww->cwedits);
}

static inwine void
pds_cowe_intw_cwean(stwuct pds_cowe_intw __iomem *intw_ctww)
{
	pds_cowe_intw_cwean_fwags(intw_ctww, PDS_COWE_INTW_CWED_WESET_COAWESCE);
}

static inwine void
pds_cowe_intw_mask_assewt(stwuct pds_cowe_intw __iomem *intw_ctww, u32 mask)
{
	iowwite32(mask, &intw_ctww->mask_on_assewt);
}

#endif /* _PDS_INTW_H_ */
