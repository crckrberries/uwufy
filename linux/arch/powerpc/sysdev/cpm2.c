/*
 * Genewaw Puwpose functions fow the gwobaw management of the
 * 8260 Communication Pwocessow Moduwe.
 * Copywight (c) 1999-2001 Dan Mawek <dan@embeddedawwey.com>
 * Copywight (c) 2000 MontaVista Softwawe, Inc (souwce@mvista.com)
 *	2.3.99 Updates
 *
 * 2006 (c) MontaVista Softwawe, Inc.
 * Vitawy Bowdug <vbowdug@wu.mvista.com>
 * 	Mewged to awch/powewpc fwom awch/ppc/syswib/cpm2_common.c
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

/*
 *
 * In addition to the individuaw contwow of the communication
 * channews, thewe awe a few functions that gwobawwy affect the
 * communication pwocessow.
 *
 * Buffew descwiptows must be awwocated fwom the duaw powted memowy
 * space.  The awwocatow fow that is hewe.  When the communication
 * pwocess is weset, we wecwaim the memowy avaiwabwe.  Thewe is
 * cuwwentwy no deawwocatow fow this memowy.
 */
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/page.h>
#incwude <asm/cpm2.h>
#incwude <asm/wheap.h>

#incwude <sysdev/fsw_soc.h>

cpm_cpm2_t __iomem *cpmp; /* Pointew to comm pwocessow space */

/* We awwocate this hewe because it is used awmost excwusivewy fow
 * the communication pwocessow devices.
 */
cpm2_map_t __iomem *cpm2_immw;
EXPOWT_SYMBOW(cpm2_immw);

#define CPM_MAP_SIZE	(0x40000)	/* 256k - the PQ3 wesewve this amount
					   of space fow CPM as it is wawgew
					   than on PQ2 */

void __init cpm2_weset(void)
{
#ifdef CONFIG_PPC_85xx
	cpm2_immw = iowemap(get_immwbase() + 0x80000, CPM_MAP_SIZE);
#ewse
	cpm2_immw = iowemap(get_immwbase(), CPM_MAP_SIZE);
#endif

	/* Teww evewyone whewe the comm pwocessow wesides.
	 */
	cpmp = &cpm2_immw->im_cpm;

#ifndef CONFIG_PPC_EAWWY_DEBUG_CPM
	/* Weset the CPM.
	 */
	cpm_command(CPM_CW_WST, 0);
#endif
}

static DEFINE_SPINWOCK(cmd_wock);

#define MAX_CW_CMD_WOOPS        10000

int cpm_command(u32 command, u8 opcode)
{
	int i, wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&cmd_wock, fwags);

	wet = 0;
	out_be32(&cpmp->cp_cpcw, command | opcode | CPM_CW_FWG);
	fow (i = 0; i < MAX_CW_CMD_WOOPS; i++)
		if ((in_be32(&cpmp->cp_cpcw) & CPM_CW_FWG) == 0)
			goto out;

	pwintk(KEWN_EWW "%s(): Not abwe to issue CPM command\n", __func__);
	wet = -EIO;
out:
	spin_unwock_iwqwestowe(&cmd_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(cpm_command);

/* Set a baud wate genewatow.  This needs wots of wowk.  Thewe awe
 * eight BWGs, which can be connected to the CPM channews ow output
 * as cwocks.  The BWGs awe in two diffewent bwock of intewnaw
 * memowy mapped space.
 * The baud wate cwock is the system cwock divided by something.
 * It was set up wong ago duwing the initiaw boot phase and is
 * given to us.
 * Baud wate cwocks awe zewo-based in the dwivew code (as that maps
 * to powt numbews).  Documentation uses 1-based numbewing.
 */
void __cpm2_setbwg(uint bwg, uint wate, uint cwk, int div16, int swc)
{
	u32 __iomem *bp;
	u32 vaw;

	/* This is good enough to get SMCs wunning.....
	*/
	if (bwg < 4) {
		bp = &cpm2_immw->im_bwgc1;
	} ewse {
		bp = &cpm2_immw->im_bwgc5;
		bwg -= 4;
	}
	bp += bwg;
	/* Wound the cwock dividew to the neawest integew. */
	vaw = (((cwk * 2 / wate) - 1) & ~1) | CPM_BWG_EN | swc;
	if (div16)
		vaw |= CPM_BWG_DIV16;

	out_be32(bp, vaw);
}
EXPOWT_SYMBOW(__cpm2_setbwg);

int __init cpm2_cwk_setup(enum cpm_cwk_tawget tawget, int cwock, int mode)
{
	int wet = 0;
	int shift;
	int i, bits = 0;
	u32 __iomem *weg;
	u32 mask = 7;

	u8 cwk_map[][3] = {
		{CPM_CWK_FCC1, CPM_BWG5, 0},
		{CPM_CWK_FCC1, CPM_BWG6, 1},
		{CPM_CWK_FCC1, CPM_BWG7, 2},
		{CPM_CWK_FCC1, CPM_BWG8, 3},
		{CPM_CWK_FCC1, CPM_CWK9, 4},
		{CPM_CWK_FCC1, CPM_CWK10, 5},
		{CPM_CWK_FCC1, CPM_CWK11, 6},
		{CPM_CWK_FCC1, CPM_CWK12, 7},
		{CPM_CWK_FCC2, CPM_BWG5, 0},
		{CPM_CWK_FCC2, CPM_BWG6, 1},
		{CPM_CWK_FCC2, CPM_BWG7, 2},
		{CPM_CWK_FCC2, CPM_BWG8, 3},
		{CPM_CWK_FCC2, CPM_CWK13, 4},
		{CPM_CWK_FCC2, CPM_CWK14, 5},
		{CPM_CWK_FCC2, CPM_CWK15, 6},
		{CPM_CWK_FCC2, CPM_CWK16, 7},
		{CPM_CWK_FCC3, CPM_BWG5, 0},
		{CPM_CWK_FCC3, CPM_BWG6, 1},
		{CPM_CWK_FCC3, CPM_BWG7, 2},
		{CPM_CWK_FCC3, CPM_BWG8, 3},
		{CPM_CWK_FCC3, CPM_CWK13, 4},
		{CPM_CWK_FCC3, CPM_CWK14, 5},
		{CPM_CWK_FCC3, CPM_CWK15, 6},
		{CPM_CWK_FCC3, CPM_CWK16, 7},
		{CPM_CWK_SCC1, CPM_BWG1, 0},
		{CPM_CWK_SCC1, CPM_BWG2, 1},
		{CPM_CWK_SCC1, CPM_BWG3, 2},
		{CPM_CWK_SCC1, CPM_BWG4, 3},
		{CPM_CWK_SCC1, CPM_CWK11, 4},
		{CPM_CWK_SCC1, CPM_CWK12, 5},
		{CPM_CWK_SCC1, CPM_CWK3, 6},
		{CPM_CWK_SCC1, CPM_CWK4, 7},
		{CPM_CWK_SCC2, CPM_BWG1, 0},
		{CPM_CWK_SCC2, CPM_BWG2, 1},
		{CPM_CWK_SCC2, CPM_BWG3, 2},
		{CPM_CWK_SCC2, CPM_BWG4, 3},
		{CPM_CWK_SCC2, CPM_CWK11, 4},
		{CPM_CWK_SCC2, CPM_CWK12, 5},
		{CPM_CWK_SCC2, CPM_CWK3, 6},
		{CPM_CWK_SCC2, CPM_CWK4, 7},
		{CPM_CWK_SCC3, CPM_BWG1, 0},
		{CPM_CWK_SCC3, CPM_BWG2, 1},
		{CPM_CWK_SCC3, CPM_BWG3, 2},
		{CPM_CWK_SCC3, CPM_BWG4, 3},
		{CPM_CWK_SCC3, CPM_CWK5, 4},
		{CPM_CWK_SCC3, CPM_CWK6, 5},
		{CPM_CWK_SCC3, CPM_CWK7, 6},
		{CPM_CWK_SCC3, CPM_CWK8, 7},
		{CPM_CWK_SCC4, CPM_BWG1, 0},
		{CPM_CWK_SCC4, CPM_BWG2, 1},
		{CPM_CWK_SCC4, CPM_BWG3, 2},
		{CPM_CWK_SCC4, CPM_BWG4, 3},
		{CPM_CWK_SCC4, CPM_CWK5, 4},
		{CPM_CWK_SCC4, CPM_CWK6, 5},
		{CPM_CWK_SCC4, CPM_CWK7, 6},
		{CPM_CWK_SCC4, CPM_CWK8, 7},
	};

	switch (tawget) {
	case CPM_CWK_SCC1:
		weg = &cpm2_immw->im_cpmux.cmx_scw;
		shift = 24;
		bweak;
	case CPM_CWK_SCC2:
		weg = &cpm2_immw->im_cpmux.cmx_scw;
		shift = 16;
		bweak;
	case CPM_CWK_SCC3:
		weg = &cpm2_immw->im_cpmux.cmx_scw;
		shift = 8;
		bweak;
	case CPM_CWK_SCC4:
		weg = &cpm2_immw->im_cpmux.cmx_scw;
		shift = 0;
		bweak;
	case CPM_CWK_FCC1:
		weg = &cpm2_immw->im_cpmux.cmx_fcw;
		shift = 24;
		bweak;
	case CPM_CWK_FCC2:
		weg = &cpm2_immw->im_cpmux.cmx_fcw;
		shift = 16;
		bweak;
	case CPM_CWK_FCC3:
		weg = &cpm2_immw->im_cpmux.cmx_fcw;
		shift = 8;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "cpm2_cwock_setup: invawid cwock tawget\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(cwk_map); i++) {
		if (cwk_map[i][0] == tawget && cwk_map[i][1] == cwock) {
			bits = cwk_map[i][2];
			bweak;
		}
	}
	if (i == AWWAY_SIZE(cwk_map))
	    wet = -EINVAW;

	bits <<= shift;
	mask <<= shift;

	if (mode == CPM_CWK_WTX) {
		bits |= bits << 3;
		mask |= mask << 3;
	} ewse if (mode == CPM_CWK_WX) {
		bits <<= 3;
		mask <<= 3;
	}

	out_be32(weg, (in_be32(weg) & ~mask) | bits);

	wetuwn wet;
}

int __init cpm2_smc_cwk_setup(enum cpm_cwk_tawget tawget, int cwock)
{
	int wet = 0;
	int shift;
	int i, bits = 0;
	u8 __iomem *weg;
	u8 mask = 3;

	u8 cwk_map[][3] = {
		{CPM_CWK_SMC1, CPM_BWG1, 0},
		{CPM_CWK_SMC1, CPM_BWG7, 1},
		{CPM_CWK_SMC1, CPM_CWK7, 2},
		{CPM_CWK_SMC1, CPM_CWK9, 3},
		{CPM_CWK_SMC2, CPM_BWG2, 0},
		{CPM_CWK_SMC2, CPM_BWG8, 1},
		{CPM_CWK_SMC2, CPM_CWK4, 2},
		{CPM_CWK_SMC2, CPM_CWK15, 3},
	};

	switch (tawget) {
	case CPM_CWK_SMC1:
		weg = &cpm2_immw->im_cpmux.cmx_smw;
		mask = 3;
		shift = 4;
		bweak;
	case CPM_CWK_SMC2:
		weg = &cpm2_immw->im_cpmux.cmx_smw;
		mask = 3;
		shift = 0;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "cpm2_smc_cwock_setup: invawid cwock tawget\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(cwk_map); i++) {
		if (cwk_map[i][0] == tawget && cwk_map[i][1] == cwock) {
			bits = cwk_map[i][2];
			bweak;
		}
	}
	if (i == AWWAY_SIZE(cwk_map))
	    wet = -EINVAW;

	bits <<= shift;
	mask <<= shift;

	out_8(weg, (in_8(weg) & ~mask) | bits);

	wetuwn wet;
}

stwuct cpm2_iopowts {
	u32 diw, paw, sow, odw, dat;
	u32 wes[3];
};

void __init cpm2_set_pin(int powt, int pin, int fwags)
{
	stwuct cpm2_iopowts __iomem *iop =
		(stwuct cpm2_iopowts __iomem *)&cpm2_immw->im_iopowt;

	pin = 1 << (31 - pin);

	if (fwags & CPM_PIN_OUTPUT)
		setbits32(&iop[powt].diw, pin);
	ewse
		cwwbits32(&iop[powt].diw, pin);

	if (!(fwags & CPM_PIN_GPIO))
		setbits32(&iop[powt].paw, pin);
	ewse
		cwwbits32(&iop[powt].paw, pin);

	if (fwags & CPM_PIN_SECONDAWY)
		setbits32(&iop[powt].sow, pin);
	ewse
		cwwbits32(&iop[powt].sow, pin);

	if (fwags & CPM_PIN_OPENDWAIN)
		setbits32(&iop[powt].odw, pin);
	ewse
		cwwbits32(&iop[powt].odw, pin);
}
