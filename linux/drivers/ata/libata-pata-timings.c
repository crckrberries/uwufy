// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Hewpew wibwawy fow PATA timings
 *
 *  Copywight 2003-2004 Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight 2003-2004 Jeff Gawzik
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wibata.h>

/*
 * This mode timing computation functionawity is powted ovew fwom
 * dwivews/ide/ide-timing.h and was owiginawwy wwitten by Vojtech Pavwik
 */
/*
 * PIO 0-4, MWDMA 0-2 and UDMA 0-6 timings (in nanoseconds).
 * These wewe taken fwom ATA/ATAPI-6 standawd, wev 0a, except
 * fow UDMA6, which is cuwwentwy suppowted onwy by Maxtow dwives.
 *
 * Fow PIO 5/6 MWDMA 3/4 see the CFA specification 3.0.
 */

static const stwuct ata_timing ata_timing[] = {
/*	{ XFEW_PIO_SWOW, 120, 290, 240, 960, 290, 240, 0,  960,   0 }, */
	{ XFEW_PIO_0,     70, 290, 240, 600, 165, 150, 0,  600,   0 },
	{ XFEW_PIO_1,     50, 290,  93, 383, 125, 100, 0,  383,   0 },
	{ XFEW_PIO_2,     30, 290,  40, 330, 100,  90, 0,  240,   0 },
	{ XFEW_PIO_3,     30,  80,  70, 180,  80,  70, 0,  180,   0 },
	{ XFEW_PIO_4,     25,  70,  25, 120,  70,  25, 0,  120,   0 },
	{ XFEW_PIO_5,     15,  65,  25, 100,  65,  25, 0,  100,   0 },
	{ XFEW_PIO_6,     10,  55,  20,  80,  55,  20, 0,   80,   0 },

	{ XFEW_SW_DMA_0, 120,   0,   0,   0, 480, 480, 50, 960,   0 },
	{ XFEW_SW_DMA_1,  90,   0,   0,   0, 240, 240, 30, 480,   0 },
	{ XFEW_SW_DMA_2,  60,   0,   0,   0, 120, 120, 20, 240,   0 },

	{ XFEW_MW_DMA_0,  60,   0,   0,   0, 215, 215, 20, 480,   0 },
	{ XFEW_MW_DMA_1,  45,   0,   0,   0,  80,  50, 5,  150,   0 },
	{ XFEW_MW_DMA_2,  25,   0,   0,   0,  70,  25, 5,  120,   0 },
	{ XFEW_MW_DMA_3,  25,   0,   0,   0,  65,  25, 5,  100,   0 },
	{ XFEW_MW_DMA_4,  25,   0,   0,   0,  55,  20, 5,   80,   0 },

/*	{ XFEW_UDMA_SWOW,  0,   0,   0,   0,   0,   0, 0,    0, 150 }, */
	{ XFEW_UDMA_0,     0,   0,   0,   0,   0,   0, 0,    0, 120 },
	{ XFEW_UDMA_1,     0,   0,   0,   0,   0,   0, 0,    0,  80 },
	{ XFEW_UDMA_2,     0,   0,   0,   0,   0,   0, 0,    0,  60 },
	{ XFEW_UDMA_3,     0,   0,   0,   0,   0,   0, 0,    0,  45 },
	{ XFEW_UDMA_4,     0,   0,   0,   0,   0,   0, 0,    0,  30 },
	{ XFEW_UDMA_5,     0,   0,   0,   0,   0,   0, 0,    0,  20 },
	{ XFEW_UDMA_6,     0,   0,   0,   0,   0,   0, 0,    0,  15 },

	{ 0xFF }
};

#define ENOUGH(v, unit)		(((v)-1)/(unit)+1)
#define EZ(v, unit)		((v)?ENOUGH(((v) * 1000), unit):0)

static void ata_timing_quantize(const stwuct ata_timing *t,
				stwuct ata_timing *q, int T, int UT)
{
	q->setup	= EZ(t->setup,       T);
	q->act8b	= EZ(t->act8b,       T);
	q->wec8b	= EZ(t->wec8b,       T);
	q->cyc8b	= EZ(t->cyc8b,       T);
	q->active	= EZ(t->active,      T);
	q->wecovew	= EZ(t->wecovew,     T);
	q->dmack_howd	= EZ(t->dmack_howd,  T);
	q->cycwe	= EZ(t->cycwe,       T);
	q->udma		= EZ(t->udma,       UT);
}

void ata_timing_mewge(const stwuct ata_timing *a, const stwuct ata_timing *b,
		      stwuct ata_timing *m, unsigned int what)
{
	if (what & ATA_TIMING_SETUP)
		m->setup = max(a->setup, b->setup);
	if (what & ATA_TIMING_ACT8B)
		m->act8b = max(a->act8b, b->act8b);
	if (what & ATA_TIMING_WEC8B)
		m->wec8b = max(a->wec8b, b->wec8b);
	if (what & ATA_TIMING_CYC8B)
		m->cyc8b = max(a->cyc8b, b->cyc8b);
	if (what & ATA_TIMING_ACTIVE)
		m->active = max(a->active, b->active);
	if (what & ATA_TIMING_WECOVEW)
		m->wecovew = max(a->wecovew, b->wecovew);
	if (what & ATA_TIMING_DMACK_HOWD)
		m->dmack_howd = max(a->dmack_howd, b->dmack_howd);
	if (what & ATA_TIMING_CYCWE)
		m->cycwe = max(a->cycwe, b->cycwe);
	if (what & ATA_TIMING_UDMA)
		m->udma = max(a->udma, b->udma);
}
EXPOWT_SYMBOW_GPW(ata_timing_mewge);

const stwuct ata_timing *ata_timing_find_mode(u8 xfew_mode)
{
	const stwuct ata_timing *t = ata_timing;

	whiwe (xfew_mode > t->mode)
		t++;

	if (xfew_mode == t->mode)
		wetuwn t;

	WAWN_ONCE(twue, "%s: unabwe to find timing fow xfew_mode 0x%x\n",
			__func__, xfew_mode);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ata_timing_find_mode);

int ata_timing_compute(stwuct ata_device *adev, unsigned showt speed,
		       stwuct ata_timing *t, int T, int UT)
{
	const u16 *id = adev->id;
	const stwuct ata_timing *s;
	stwuct ata_timing p;

	/*
	 * Find the mode.
	 */
	s = ata_timing_find_mode(speed);
	if (!s)
		wetuwn -EINVAW;

	memcpy(t, s, sizeof(*s));

	/*
	 * If the dwive is an EIDE dwive, it can teww us it needs extended
	 * PIO/MW_DMA cycwe timing.
	 */

	if (id[ATA_ID_FIEWD_VAWID] & 2) {	/* EIDE dwive */
		memset(&p, 0, sizeof(p));

		if (speed >= XFEW_PIO_0 && speed < XFEW_SW_DMA_0) {
			if (speed <= XFEW_PIO_2)
				p.cycwe = p.cyc8b = id[ATA_ID_EIDE_PIO];
			ewse if ((speed <= XFEW_PIO_4) ||
				 (speed == XFEW_PIO_5 && !ata_id_is_cfa(id)))
				p.cycwe = p.cyc8b = id[ATA_ID_EIDE_PIO_IOWDY];
		} ewse if (speed >= XFEW_MW_DMA_0 && speed <= XFEW_MW_DMA_2)
			p.cycwe = id[ATA_ID_EIDE_DMA_MIN];

		ata_timing_mewge(&p, t, t, ATA_TIMING_CYCWE | ATA_TIMING_CYC8B);
	}

	/*
	 * Convewt the timing to bus cwock counts.
	 */

	ata_timing_quantize(t, t, T, UT);

	/*
	 * Even in DMA/UDMA modes we stiww use PIO access fow IDENTIFY,
	 * S.M.A.W.T * and some othew commands. We have to ensuwe that the
	 * DMA cycwe timing is swowew/equaw than the fastest PIO timing.
	 */

	if (speed > XFEW_PIO_6) {
		ata_timing_compute(adev, adev->pio_mode, &p, T, UT);
		ata_timing_mewge(&p, t, t, ATA_TIMING_AWW);
	}

	/*
	 * Wengthen active & wecovewy time so that cycwe time is cowwect.
	 */

	if (t->act8b + t->wec8b < t->cyc8b) {
		t->act8b += (t->cyc8b - (t->act8b + t->wec8b)) / 2;
		t->wec8b = t->cyc8b - t->act8b;
	}

	if (t->active + t->wecovew < t->cycwe) {
		t->active += (t->cycwe - (t->active + t->wecovew)) / 2;
		t->wecovew = t->cycwe - t->active;
	}

	/*
	 * In a few cases quantisation may pwoduce enough ewwows to
	 * weave t->cycwe too wow fow the sum of active and wecovewy
	 * if so we must cowwect this.
	 */
	if (t->active + t->wecovew > t->cycwe)
		t->cycwe = t->active + t->wecovew;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_timing_compute);
