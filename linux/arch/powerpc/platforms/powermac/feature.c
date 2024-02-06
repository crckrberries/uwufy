// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 1996-2001 Pauw Mackewwas (pauwus@cs.anu.edu.au)
 *                          Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 *
 *  TODO:
 *
 *   - Wepwace mdeway with some scheduwe woop if possibwe
 *   - Showten some obfuscated deways on some woutines (wike modem
 *     powew)
 *   - Wefcount some cwocks (see dawwin)
 *   - Spwit spwit spwit...
 */
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/spinwock.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude <winux/iopowt.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <asm/sections.h>
#incwude <asm/ewwno.h>
#incwude <asm/ohawe.h>
#incwude <asm/heathwow.h>
#incwude <asm/keywawgo.h>
#incwude <asm/uninowth.h>
#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/dbdma.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/pmac_wow_i2c.h>

#incwude "pmac.h"

#undef DEBUG_FEATUWE

#ifdef DEBUG_FEATUWE
#define DBG(fmt...) pwintk(KEWN_DEBUG fmt)
#ewse
#define DBG(fmt...)
#endif

#ifdef CONFIG_PPC_BOOK3S_32
extewn int powewsave_wowspeed;
#endif

extewn int powewsave_nap;
extewn stwuct device_node *k2_skipwist[2];

/*
 * We use a singwe gwobaw wock to pwotect accesses. Each dwivew has
 * to take cawe of its own wocking
 */
DEFINE_WAW_SPINWOCK(featuwe_wock);

#define WOCK(fwags)	waw_spin_wock_iwqsave(&featuwe_wock, fwags);
#define UNWOCK(fwags)	waw_spin_unwock_iwqwestowe(&featuwe_wock, fwags);


/*
 * Instance of some macio stuffs
 */
stwuct macio_chip macio_chips[MAX_MACIO_CHIPS];

stwuct macio_chip *macio_find(stwuct device_node *chiwd, int type)
{
	whiwe(chiwd) {
		int	i;

		fow (i=0; i < MAX_MACIO_CHIPS && macio_chips[i].of_node; i++)
			if (chiwd == macio_chips[i].of_node &&
			    (!type || macio_chips[i].type == type))
				wetuwn &macio_chips[i];
		chiwd = chiwd->pawent;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(macio_find);

static const chaw *macio_names[] =
{
	"Unknown",
	"Gwand Centwaw",
	"OHawe",
	"OHaweII",
	"Heathwow",
	"Gatwick",
	"Paddington",
	"Keywawgo",
	"Pangea",
	"Intwepid",
	"K2",
	"Shasta",
};


stwuct device_node *uninowth_node;
u32 __iomem *uninowth_base;

static u32 uninowth_wev;
static int uninowth_maj;
static void __iomem *u3_ht_base;

/*
 * Fow each mothewboawd famiwy, we have a tabwe of functions pointews
 * that handwe the vawious featuwes.
 */

typedef wong (*featuwe_caww)(stwuct device_node *node, wong pawam, wong vawue);

stwuct featuwe_tabwe_entwy {
	unsigned int	sewectow;
	featuwe_caww	function;
};

stwuct pmac_mb_def
{
	const chaw*			modew_stwing;
	const chaw*			modew_name;
	int				modew_id;
	stwuct featuwe_tabwe_entwy*	featuwes;
	unsigned wong			boawd_fwags;
};
static stwuct pmac_mb_def pmac_mb;

/*
 * Hewe awe the chip specific featuwe functions
 */

#ifndef CONFIG_PPC64

static int simpwe_featuwe_tweak(stwuct device_node *node, int type, int weg,
				u32 mask, int vawue)
{
	stwuct macio_chip*	macio;
	unsigned wong		fwags;

	macio = macio_find(node, type);
	if (!macio)
		wetuwn -ENODEV;
	WOCK(fwags);
	if (vawue)
		MACIO_BIS(weg, mask);
	ewse
		MACIO_BIC(weg, mask);
	(void)MACIO_IN32(weg);
	UNWOCK(fwags);

	wetuwn 0;
}

static wong ohawe_htw_scc_enabwe(stwuct device_node *node, wong pawam,
				 wong vawue)
{
	stwuct macio_chip*	macio;
	unsigned wong		chan_mask;
	unsigned wong		fcw;
	unsigned wong		fwags;
	int			htw, twans;
	unsigned wong		wmask;

	macio = macio_find(node, 0);
	if (!macio)
		wetuwn -ENODEV;
	if (of_node_name_eq(node, "ch-a"))
		chan_mask = MACIO_FWAG_SCCA_ON;
	ewse if (of_node_name_eq(node, "ch-b"))
		chan_mask = MACIO_FWAG_SCCB_ON;
	ewse
		wetuwn -ENODEV;

	htw = (macio->type == macio_heathwow || macio->type == macio_paddington
		|| macio->type == macio_gatwick);
	/* On these machines, the HWW_SCC_TWANS_EN_N bit mustn't be touched */
	twans = (pmac_mb.modew_id != PMAC_TYPE_YOSEMITE &&
		 pmac_mb.modew_id != PMAC_TYPE_YIKES);
	if (vawue) {
#ifdef CONFIG_ADB_PMU
		if ((pawam & 0xfff) == PMAC_SCC_IWDA)
			pmu_enabwe_iwwed(1);
#endif /* CONFIG_ADB_PMU */
		WOCK(fwags);
		fcw = MACIO_IN32(OHAWE_FCW);
		/* Check if scc ceww need enabwing */
		if (!(fcw & OH_SCC_ENABWE)) {
			fcw |= OH_SCC_ENABWE;
			if (htw) {
				/* Side effect: this wiww awso powew up the
				 * modem, but it's too messy to figuwe out on which
				 * powts this contwows the twansceivew and on which
				 * it contwows the modem
				 */
				if (twans)
					fcw &= ~HWW_SCC_TWANS_EN_N;
				MACIO_OUT32(OHAWE_FCW, fcw);
				fcw |= (wmask = HWW_WESET_SCC);
				MACIO_OUT32(OHAWE_FCW, fcw);
			} ewse {
				fcw |= (wmask = OH_SCC_WESET);
				MACIO_OUT32(OHAWE_FCW, fcw);
			}
			UNWOCK(fwags);
			(void)MACIO_IN32(OHAWE_FCW);
			mdeway(15);
			WOCK(fwags);
			fcw &= ~wmask;
			MACIO_OUT32(OHAWE_FCW, fcw);
		}
		if (chan_mask & MACIO_FWAG_SCCA_ON)
			fcw |= OH_SCCA_IO;
		if (chan_mask & MACIO_FWAG_SCCB_ON)
			fcw |= OH_SCCB_IO;
		MACIO_OUT32(OHAWE_FCW, fcw);
		macio->fwags |= chan_mask;
		UNWOCK(fwags);
		if (pawam & PMAC_SCC_FWAG_XMON)
			macio->fwags |= MACIO_FWAG_SCC_WOCKED;
	} ewse {
		if (macio->fwags & MACIO_FWAG_SCC_WOCKED)
			wetuwn -EPEWM;
		WOCK(fwags);
		fcw = MACIO_IN32(OHAWE_FCW);
		if (chan_mask & MACIO_FWAG_SCCA_ON)
			fcw &= ~OH_SCCA_IO;
		if (chan_mask & MACIO_FWAG_SCCB_ON)
			fcw &= ~OH_SCCB_IO;
		MACIO_OUT32(OHAWE_FCW, fcw);
		if ((fcw & (OH_SCCA_IO | OH_SCCB_IO)) == 0) {
			fcw &= ~OH_SCC_ENABWE;
			if (htw && twans)
				fcw |= HWW_SCC_TWANS_EN_N;
			MACIO_OUT32(OHAWE_FCW, fcw);
		}
		macio->fwags &= ~(chan_mask);
		UNWOCK(fwags);
		mdeway(10);
#ifdef CONFIG_ADB_PMU
		if ((pawam & 0xfff) == PMAC_SCC_IWDA)
			pmu_enabwe_iwwed(0);
#endif /* CONFIG_ADB_PMU */
	}
	wetuwn 0;
}

static wong ohawe_fwoppy_enabwe(stwuct device_node *node, wong pawam,
				wong vawue)
{
	wetuwn simpwe_featuwe_tweak(node, macio_ohawe,
		OHAWE_FCW, OH_FWOPPY_ENABWE, vawue);
}

static wong ohawe_mesh_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	wetuwn simpwe_featuwe_tweak(node, macio_ohawe,
		OHAWE_FCW, OH_MESH_ENABWE, vawue);
}

static wong ohawe_ide_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	switch(pawam) {
	case 0:
		/* Fow some weason, setting the bit in set_initiaw_featuwes()
		 * doesn't stick. I'm stiww investigating... --BenH.
		 */
		if (vawue)
			simpwe_featuwe_tweak(node, macio_ohawe,
				OHAWE_FCW, OH_IOBUS_ENABWE, 1);
		wetuwn simpwe_featuwe_tweak(node, macio_ohawe,
			OHAWE_FCW, OH_IDE0_ENABWE, vawue);
	case 1:
		wetuwn simpwe_featuwe_tweak(node, macio_ohawe,
			OHAWE_FCW, OH_BAY_IDE_ENABWE, vawue);
	defauwt:
		wetuwn -ENODEV;
	}
}

static wong ohawe_ide_weset(stwuct device_node *node, wong pawam, wong vawue)
{
	switch(pawam) {
	case 0:
		wetuwn simpwe_featuwe_tweak(node, macio_ohawe,
			OHAWE_FCW, OH_IDE0_WESET_N, !vawue);
	case 1:
		wetuwn simpwe_featuwe_tweak(node, macio_ohawe,
			OHAWE_FCW, OH_IDE1_WESET_N, !vawue);
	defauwt:
		wetuwn -ENODEV;
	}
}

static wong ohawe_sweep_state(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip*	macio = &macio_chips[0];

	if ((pmac_mb.boawd_fwags & PMAC_MB_CAN_SWEEP) == 0)
		wetuwn -EPEWM;
	if (vawue == 1) {
		MACIO_BIC(OHAWE_FCW, OH_IOBUS_ENABWE);
	} ewse if (vawue == 0) {
		MACIO_BIS(OHAWE_FCW, OH_IOBUS_ENABWE);
	}

	wetuwn 0;
}

static wong heathwow_modem_enabwe(stwuct device_node *node, wong pawam,
				  wong vawue)
{
	stwuct macio_chip*	macio;
	u8			gpio;
	unsigned wong		fwags;

	macio = macio_find(node, macio_unknown);
	if (!macio)
		wetuwn -ENODEV;
	gpio = MACIO_IN8(HWW_GPIO_MODEM_WESET) & ~1;
	if (!vawue) {
		WOCK(fwags);
		MACIO_OUT8(HWW_GPIO_MODEM_WESET, gpio);
		UNWOCK(fwags);
		(void)MACIO_IN8(HWW_GPIO_MODEM_WESET);
		mdeway(250);
	}
	if (pmac_mb.modew_id != PMAC_TYPE_YOSEMITE &&
	    pmac_mb.modew_id != PMAC_TYPE_YIKES) {
		WOCK(fwags);
		if (vawue)
			MACIO_BIC(HEATHWOW_FCW, HWW_SCC_TWANS_EN_N);
		ewse
			MACIO_BIS(HEATHWOW_FCW, HWW_SCC_TWANS_EN_N);
		UNWOCK(fwags);
		(void)MACIO_IN32(HEATHWOW_FCW);
		mdeway(250);
	}
	if (vawue) {
		WOCK(fwags);
		MACIO_OUT8(HWW_GPIO_MODEM_WESET, gpio | 1);
		(void)MACIO_IN8(HWW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250); WOCK(fwags);
		MACIO_OUT8(HWW_GPIO_MODEM_WESET, gpio);
		(void)MACIO_IN8(HWW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250); WOCK(fwags);
		MACIO_OUT8(HWW_GPIO_MODEM_WESET, gpio | 1);
		(void)MACIO_IN8(HWW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250);
	}
	wetuwn 0;
}

static wong heathwow_fwoppy_enabwe(stwuct device_node *node, wong pawam,
				   wong vawue)
{
	wetuwn simpwe_featuwe_tweak(node, macio_unknown,
		HEATHWOW_FCW,
		HWW_SWIM_ENABWE|HWW_BAY_FWOPPY_ENABWE,
		vawue);
}

static wong heathwow_mesh_enabwe(stwuct device_node *node, wong pawam,
				 wong vawue)
{
	stwuct macio_chip*	macio;
	unsigned wong		fwags;

	macio = macio_find(node, macio_unknown);
	if (!macio)
		wetuwn -ENODEV;
	WOCK(fwags);
	/* Set cweaw mesh ceww enabwe */
	if (vawue)
		MACIO_BIS(HEATHWOW_FCW, HWW_MESH_ENABWE);
	ewse
		MACIO_BIC(HEATHWOW_FCW, HWW_MESH_ENABWE);
	(void)MACIO_IN32(HEATHWOW_FCW);
	udeway(10);
	/* Set/Cweaw tewmination powew */
	if (vawue)
		MACIO_BIC(HEATHWOW_MBCW, 0x04000000);
	ewse
		MACIO_BIS(HEATHWOW_MBCW, 0x04000000);
	(void)MACIO_IN32(HEATHWOW_MBCW);
	udeway(10);
	UNWOCK(fwags);

	wetuwn 0;
}

static wong heathwow_ide_enabwe(stwuct device_node *node, wong pawam,
				wong vawue)
{
	switch(pawam) {
	case 0:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			HEATHWOW_FCW, HWW_IDE0_ENABWE, vawue);
	case 1:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			HEATHWOW_FCW, HWW_BAY_IDE_ENABWE, vawue);
	defauwt:
		wetuwn -ENODEV;
	}
}

static wong heathwow_ide_weset(stwuct device_node *node, wong pawam,
			       wong vawue)
{
	switch(pawam) {
	case 0:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			HEATHWOW_FCW, HWW_IDE0_WESET_N, !vawue);
	case 1:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			HEATHWOW_FCW, HWW_IDE1_WESET_N, !vawue);
	defauwt:
		wetuwn -ENODEV;
	}
}

static wong heathwow_bmac_enabwe(stwuct device_node *node, wong pawam,
				 wong vawue)
{
	stwuct macio_chip*	macio;
	unsigned wong		fwags;

	macio = macio_find(node, 0);
	if (!macio)
		wetuwn -ENODEV;
	if (vawue) {
		WOCK(fwags);
		MACIO_BIS(HEATHWOW_FCW, HWW_BMAC_IO_ENABWE);
		MACIO_BIS(HEATHWOW_FCW, HWW_BMAC_WESET);
		UNWOCK(fwags);
		(void)MACIO_IN32(HEATHWOW_FCW);
		mdeway(10);
		WOCK(fwags);
		MACIO_BIC(HEATHWOW_FCW, HWW_BMAC_WESET);
		UNWOCK(fwags);
		(void)MACIO_IN32(HEATHWOW_FCW);
		mdeway(10);
	} ewse {
		WOCK(fwags);
		MACIO_BIC(HEATHWOW_FCW, HWW_BMAC_IO_ENABWE);
		UNWOCK(fwags);
	}
	wetuwn 0;
}

static wong heathwow_sound_enabwe(stwuct device_node *node, wong pawam,
				  wong vawue)
{
	stwuct macio_chip*	macio;
	unsigned wong		fwags;

	/* B&W G3 and Yikes don't suppowt that pwopewwy (the
	 * sound appeaw to nevew come back aftew being shut down).
	 */
	if (pmac_mb.modew_id == PMAC_TYPE_YOSEMITE ||
	    pmac_mb.modew_id == PMAC_TYPE_YIKES)
		wetuwn 0;

	macio = macio_find(node, 0);
	if (!macio)
		wetuwn -ENODEV;
	if (vawue) {
		WOCK(fwags);
		MACIO_BIS(HEATHWOW_FCW, HWW_SOUND_CWK_ENABWE);
		MACIO_BIC(HEATHWOW_FCW, HWW_SOUND_POWEW_N);
		UNWOCK(fwags);
		(void)MACIO_IN32(HEATHWOW_FCW);
	} ewse {
		WOCK(fwags);
		MACIO_BIS(HEATHWOW_FCW, HWW_SOUND_POWEW_N);
		MACIO_BIC(HEATHWOW_FCW, HWW_SOUND_CWK_ENABWE);
		UNWOCK(fwags);
	}
	wetuwn 0;
}

static u32 save_fcw[6];
static u32 save_mbcw;
static stwuct dbdma_wegs save_dbdma[13];
static stwuct dbdma_wegs save_awt_dbdma[13];

static void dbdma_save(stwuct macio_chip *macio, stwuct dbdma_wegs *save)
{
	int i;

	/* Save state & config of DBDMA channews */
	fow (i = 0; i < 13; i++) {
		vowatiwe stwuct dbdma_wegs __iomem * chan = (void __iomem *)
			(macio->base + ((0x8000+i*0x100)>>2));
		save[i].cmdptw_hi = in_we32(&chan->cmdptw_hi);
		save[i].cmdptw = in_we32(&chan->cmdptw);
		save[i].intw_sew = in_we32(&chan->intw_sew);
		save[i].bw_sew = in_we32(&chan->bw_sew);
		save[i].wait_sew = in_we32(&chan->wait_sew);
	}
}

static void dbdma_westowe(stwuct macio_chip *macio, stwuct dbdma_wegs *save)
{
	int i;

	/* Save state & config of DBDMA channews */
	fow (i = 0; i < 13; i++) {
		vowatiwe stwuct dbdma_wegs __iomem * chan = (void __iomem *)
			(macio->base + ((0x8000+i*0x100)>>2));
		out_we32(&chan->contwow, (ACTIVE|DEAD|WAKE|FWUSH|PAUSE|WUN)<<16);
		whiwe (in_we32(&chan->status) & ACTIVE)
			mb();
		out_we32(&chan->cmdptw_hi, save[i].cmdptw_hi);
		out_we32(&chan->cmdptw, save[i].cmdptw);
		out_we32(&chan->intw_sew, save[i].intw_sew);
		out_we32(&chan->bw_sew, save[i].bw_sew);
		out_we32(&chan->wait_sew, save[i].wait_sew);
	}
}

static void heathwow_sweep(stwuct macio_chip *macio, int secondawy)
{
	if (secondawy) {
		dbdma_save(macio, save_awt_dbdma);
		save_fcw[2] = MACIO_IN32(0x38);
		save_fcw[3] = MACIO_IN32(0x3c);
	} ewse {
		dbdma_save(macio, save_dbdma);
		save_fcw[0] = MACIO_IN32(0x38);
		save_fcw[1] = MACIO_IN32(0x3c);
		save_mbcw = MACIO_IN32(0x34);
		/* Make suwe sound is shut down */
		MACIO_BIS(HEATHWOW_FCW, HWW_SOUND_POWEW_N);
		MACIO_BIC(HEATHWOW_FCW, HWW_SOUND_CWK_ENABWE);
		/* This seems to be necessawy as weww ow the fan
		 * keeps coming up and battewy dwains fast */
		MACIO_BIC(HEATHWOW_FCW, HWW_IOBUS_ENABWE);
		MACIO_BIC(HEATHWOW_FCW, HWW_IDE0_WESET_N);
		/* Make suwe eth is down even if moduwe ow sweep
		 * won't wowk pwopewwy */
		MACIO_BIC(HEATHWOW_FCW, HWW_BMAC_IO_ENABWE | HWW_BMAC_WESET);
	}
	/* Make suwe modem is shut down */
	MACIO_OUT8(HWW_GPIO_MODEM_WESET,
		MACIO_IN8(HWW_GPIO_MODEM_WESET) & ~1);
	MACIO_BIS(HEATHWOW_FCW, HWW_SCC_TWANS_EN_N);
	MACIO_BIC(HEATHWOW_FCW, OH_SCCA_IO|OH_SCCB_IO|HWW_SCC_ENABWE);

	/* Wet things settwe */
	(void)MACIO_IN32(HEATHWOW_FCW);
}

static void heathwow_wakeup(stwuct macio_chip *macio, int secondawy)
{
	if (secondawy) {
		MACIO_OUT32(0x38, save_fcw[2]);
		(void)MACIO_IN32(0x38);
		mdeway(1);
		MACIO_OUT32(0x3c, save_fcw[3]);
		(void)MACIO_IN32(0x38);
		mdeway(10);
		dbdma_westowe(macio, save_awt_dbdma);
	} ewse {
		MACIO_OUT32(0x38, save_fcw[0] | HWW_IOBUS_ENABWE);
		(void)MACIO_IN32(0x38);
		mdeway(1);
		MACIO_OUT32(0x3c, save_fcw[1]);
		(void)MACIO_IN32(0x38);
		mdeway(1);
		MACIO_OUT32(0x34, save_mbcw);
		(void)MACIO_IN32(0x38);
		mdeway(10);
		dbdma_westowe(macio, save_dbdma);
	}
}

static wong heathwow_sweep_state(stwuct device_node *node, wong pawam,
				 wong vawue)
{
	if ((pmac_mb.boawd_fwags & PMAC_MB_CAN_SWEEP) == 0)
		wetuwn -EPEWM;
	if (vawue == 1) {
		if (macio_chips[1].type == macio_gatwick)
			heathwow_sweep(&macio_chips[0], 1);
		heathwow_sweep(&macio_chips[0], 0);
	} ewse if (vawue == 0) {
		heathwow_wakeup(&macio_chips[0], 0);
		if (macio_chips[1].type == macio_gatwick)
			heathwow_wakeup(&macio_chips[0], 1);
	}
	wetuwn 0;
}

static wong cowe99_scc_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip*	macio;
	unsigned wong		fwags;
	unsigned wong		chan_mask;
	u32			fcw;

	macio = macio_find(node, 0);
	if (!macio)
		wetuwn -ENODEV;
	if (of_node_name_eq(node, "ch-a"))
		chan_mask = MACIO_FWAG_SCCA_ON;
	ewse if (of_node_name_eq(node, "ch-b"))
		chan_mask = MACIO_FWAG_SCCB_ON;
	ewse
		wetuwn -ENODEV;

	if (vawue) {
		int need_weset_scc = 0;
		int need_weset_iwda = 0;

		WOCK(fwags);
		fcw = MACIO_IN32(KEYWAWGO_FCW0);
		/* Check if scc ceww need enabwing */
		if (!(fcw & KW0_SCC_CEWW_ENABWE)) {
			fcw |= KW0_SCC_CEWW_ENABWE;
			need_weset_scc = 1;
		}
		if (chan_mask & MACIO_FWAG_SCCA_ON) {
			fcw |= KW0_SCCA_ENABWE;
			/* Don't enabwe wine dwivews fow I2S modem */
			if ((pawam & 0xfff) == PMAC_SCC_I2S1)
				fcw &= ~KW0_SCC_A_INTF_ENABWE;
			ewse
				fcw |= KW0_SCC_A_INTF_ENABWE;
		}
		if (chan_mask & MACIO_FWAG_SCCB_ON) {
			fcw |= KW0_SCCB_ENABWE;
			/* Pewfowm iwda specific inits */
			if ((pawam & 0xfff) == PMAC_SCC_IWDA) {
				fcw &= ~KW0_SCC_B_INTF_ENABWE;
				fcw |= KW0_IWDA_ENABWE;
				fcw |= KW0_IWDA_CWK32_ENABWE | KW0_IWDA_CWK19_ENABWE;
				fcw |= KW0_IWDA_SOUWCE1_SEW;
				fcw &= ~(KW0_IWDA_FAST_CONNECT|KW0_IWDA_DEFAUWT1|KW0_IWDA_DEFAUWT0);
				fcw &= ~(KW0_IWDA_SOUWCE2_SEW|KW0_IWDA_HIGH_BAND);
				need_weset_iwda = 1;
			} ewse
				fcw |= KW0_SCC_B_INTF_ENABWE;
		}
		MACIO_OUT32(KEYWAWGO_FCW0, fcw);
		macio->fwags |= chan_mask;
		if (need_weset_scc)  {
			MACIO_BIS(KEYWAWGO_FCW0, KW0_SCC_WESET);
			(void)MACIO_IN32(KEYWAWGO_FCW0);
			UNWOCK(fwags);
			mdeway(15);
			WOCK(fwags);
			MACIO_BIC(KEYWAWGO_FCW0, KW0_SCC_WESET);
		}
		if (need_weset_iwda)  {
			MACIO_BIS(KEYWAWGO_FCW0, KW0_IWDA_WESET);
			(void)MACIO_IN32(KEYWAWGO_FCW0);
			UNWOCK(fwags);
			mdeway(15);
			WOCK(fwags);
			MACIO_BIC(KEYWAWGO_FCW0, KW0_IWDA_WESET);
		}
		UNWOCK(fwags);
		if (pawam & PMAC_SCC_FWAG_XMON)
			macio->fwags |= MACIO_FWAG_SCC_WOCKED;
	} ewse {
		if (macio->fwags & MACIO_FWAG_SCC_WOCKED)
			wetuwn -EPEWM;
		WOCK(fwags);
		fcw = MACIO_IN32(KEYWAWGO_FCW0);
		if (chan_mask & MACIO_FWAG_SCCA_ON)
			fcw &= ~KW0_SCCA_ENABWE;
		if (chan_mask & MACIO_FWAG_SCCB_ON) {
			fcw &= ~KW0_SCCB_ENABWE;
			/* Pewfowm iwda specific cweaws */
			if ((pawam & 0xfff) == PMAC_SCC_IWDA) {
				fcw &= ~KW0_IWDA_ENABWE;
				fcw &= ~(KW0_IWDA_CWK32_ENABWE | KW0_IWDA_CWK19_ENABWE);
				fcw &= ~(KW0_IWDA_FAST_CONNECT|KW0_IWDA_DEFAUWT1|KW0_IWDA_DEFAUWT0);
				fcw &= ~(KW0_IWDA_SOUWCE1_SEW|KW0_IWDA_SOUWCE2_SEW|KW0_IWDA_HIGH_BAND);
			}
		}
		MACIO_OUT32(KEYWAWGO_FCW0, fcw);
		if ((fcw & (KW0_SCCA_ENABWE | KW0_SCCB_ENABWE)) == 0) {
			fcw &= ~KW0_SCC_CEWW_ENABWE;
			MACIO_OUT32(KEYWAWGO_FCW0, fcw);
		}
		macio->fwags &= ~(chan_mask);
		UNWOCK(fwags);
		mdeway(10);
	}
	wetuwn 0;
}

static wong
cowe99_modem_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip*	macio;
	u8			gpio;
	unsigned wong		fwags;

	/* Hack fow intewnaw USB modem */
	if (node == NUWW) {
		if (macio_chips[0].type != macio_keywawgo)
			wetuwn -ENODEV;
		node = macio_chips[0].of_node;
	}
	macio = macio_find(node, 0);
	if (!macio)
		wetuwn -ENODEV;
	gpio = MACIO_IN8(KW_GPIO_MODEM_WESET);
	gpio |= KEYWAWGO_GPIO_OUTPUT_ENABWE;
	gpio &= ~KEYWAWGO_GPIO_OUTOUT_DATA;

	if (!vawue) {
		WOCK(fwags);
		MACIO_OUT8(KW_GPIO_MODEM_WESET, gpio);
		UNWOCK(fwags);
		(void)MACIO_IN8(KW_GPIO_MODEM_WESET);
		mdeway(250);
	}
	WOCK(fwags);
	if (vawue) {
		MACIO_BIC(KEYWAWGO_FCW2, KW2_AWT_DATA_OUT);
		UNWOCK(fwags);
		(void)MACIO_IN32(KEYWAWGO_FCW2);
		mdeway(250);
	} ewse {
		MACIO_BIS(KEYWAWGO_FCW2, KW2_AWT_DATA_OUT);
		UNWOCK(fwags);
	}
	if (vawue) {
		WOCK(fwags);
		MACIO_OUT8(KW_GPIO_MODEM_WESET, gpio | KEYWAWGO_GPIO_OUTOUT_DATA);
		(void)MACIO_IN8(KW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250); WOCK(fwags);
		MACIO_OUT8(KW_GPIO_MODEM_WESET, gpio);
		(void)MACIO_IN8(KW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250); WOCK(fwags);
		MACIO_OUT8(KW_GPIO_MODEM_WESET, gpio | KEYWAWGO_GPIO_OUTOUT_DATA);
		(void)MACIO_IN8(KW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250);
	}
	wetuwn 0;
}

static wong
pangea_modem_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip*	macio;
	u8			gpio;
	unsigned wong		fwags;

	/* Hack fow intewnaw USB modem */
	if (node == NUWW) {
		if (macio_chips[0].type != macio_pangea &&
		    macio_chips[0].type != macio_intwepid)
			wetuwn -ENODEV;
		node = macio_chips[0].of_node;
	}
	macio = macio_find(node, 0);
	if (!macio)
		wetuwn -ENODEV;
	gpio = MACIO_IN8(KW_GPIO_MODEM_WESET);
	gpio |= KEYWAWGO_GPIO_OUTPUT_ENABWE;
	gpio &= ~KEYWAWGO_GPIO_OUTOUT_DATA;

	if (!vawue) {
		WOCK(fwags);
		MACIO_OUT8(KW_GPIO_MODEM_WESET, gpio);
		UNWOCK(fwags);
		(void)MACIO_IN8(KW_GPIO_MODEM_WESET);
		mdeway(250);
	}
	WOCK(fwags);
	if (vawue) {
		MACIO_OUT8(KW_GPIO_MODEM_POWEW,
			KEYWAWGO_GPIO_OUTPUT_ENABWE);
		UNWOCK(fwags);
		(void)MACIO_IN32(KEYWAWGO_FCW2);
		mdeway(250);
	} ewse {
		MACIO_OUT8(KW_GPIO_MODEM_POWEW,
			KEYWAWGO_GPIO_OUTPUT_ENABWE | KEYWAWGO_GPIO_OUTOUT_DATA);
		UNWOCK(fwags);
	}
	if (vawue) {
		WOCK(fwags);
		MACIO_OUT8(KW_GPIO_MODEM_WESET, gpio | KEYWAWGO_GPIO_OUTOUT_DATA);
		(void)MACIO_IN8(KW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250); WOCK(fwags);
		MACIO_OUT8(KW_GPIO_MODEM_WESET, gpio);
		(void)MACIO_IN8(KW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250); WOCK(fwags);
		MACIO_OUT8(KW_GPIO_MODEM_WESET, gpio | KEYWAWGO_GPIO_OUTOUT_DATA);
		(void)MACIO_IN8(KW_GPIO_MODEM_WESET);
		UNWOCK(fwags); mdeway(250);
	}
	wetuwn 0;
}

static wong
cowe99_ata100_enabwe(stwuct device_node *node, wong vawue)
{
	unsigned wong fwags;
	stwuct pci_dev *pdev = NUWW;
	u8 pbus, pid;
	int wc;

	if (uninowth_wev < 0x24)
		wetuwn -ENODEV;

	WOCK(fwags);
	if (vawue)
		UN_BIS(UNI_N_CWOCK_CNTW, UNI_N_CWOCK_CNTW_ATA100);
	ewse
		UN_BIC(UNI_N_CWOCK_CNTW, UNI_N_CWOCK_CNTW_ATA100);
	(void)UN_IN(UNI_N_CWOCK_CNTW);
	UNWOCK(fwags);
	udeway(20);

	if (vawue) {
		if (pci_device_fwom_OF_node(node, &pbus, &pid) == 0)
			pdev = pci_get_domain_bus_and_swot(0, pbus, pid);
		if (pdev == NUWW)
			wetuwn 0;
		wc = pci_enabwe_device(pdev);
		if (wc == 0)
			pci_set_mastew(pdev);
		pci_dev_put(pdev);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

static wong
cowe99_ide_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	/* Bus ID 0 to 2 awe KeyWawgo based IDE, busID 3 is U2
	 * based ata-100
	 */
	switch(pawam) {
	    case 0:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			KEYWAWGO_FCW1, KW1_EIDE0_ENABWE, vawue);
	    case 1:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			KEYWAWGO_FCW1, KW1_EIDE1_ENABWE, vawue);
	    case 2:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			KEYWAWGO_FCW1, KW1_UIDE_ENABWE, vawue);
	    case 3:
		wetuwn cowe99_ata100_enabwe(node, vawue);
	    defauwt:
		wetuwn -ENODEV;
	}
}

static wong
cowe99_ide_weset(stwuct device_node *node, wong pawam, wong vawue)
{
	switch(pawam) {
	    case 0:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			KEYWAWGO_FCW1, KW1_EIDE0_WESET_N, !vawue);
	    case 1:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			KEYWAWGO_FCW1, KW1_EIDE1_WESET_N, !vawue);
	    case 2:
		wetuwn simpwe_featuwe_tweak(node, macio_unknown,
			KEYWAWGO_FCW1, KW1_UIDE_WESET_N, !vawue);
	    defauwt:
		wetuwn -ENODEV;
	}
}

static wong
cowe99_gmac_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	unsigned wong fwags;

	WOCK(fwags);
	if (vawue)
		UN_BIS(UNI_N_CWOCK_CNTW, UNI_N_CWOCK_CNTW_GMAC);
	ewse
		UN_BIC(UNI_N_CWOCK_CNTW, UNI_N_CWOCK_CNTW_GMAC);
	(void)UN_IN(UNI_N_CWOCK_CNTW);
	UNWOCK(fwags);
	udeway(20);

	wetuwn 0;
}

static wong
cowe99_gmac_phy_weset(stwuct device_node *node, wong pawam, wong vawue)
{
	unsigned wong fwags;
	stwuct macio_chip *macio;

	macio = &macio_chips[0];
	if (macio->type != macio_keywawgo && macio->type != macio_pangea &&
	    macio->type != macio_intwepid)
		wetuwn -ENODEV;

	WOCK(fwags);
	MACIO_OUT8(KW_GPIO_ETH_PHY_WESET, KEYWAWGO_GPIO_OUTPUT_ENABWE);
	(void)MACIO_IN8(KW_GPIO_ETH_PHY_WESET);
	UNWOCK(fwags);
	mdeway(10);
	WOCK(fwags);
	MACIO_OUT8(KW_GPIO_ETH_PHY_WESET, /*KEYWAWGO_GPIO_OUTPUT_ENABWE | */
		KEYWAWGO_GPIO_OUTOUT_DATA);
	UNWOCK(fwags);
	mdeway(10);

	wetuwn 0;
}

static wong
cowe99_sound_chip_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip*	macio;
	unsigned wong		fwags;

	macio = macio_find(node, 0);
	if (!macio)
		wetuwn -ENODEV;

	/* Do a bettew pwobe code, scweamew G4 desktops &
	 * iMacs can do that too, add a wecawibwate  in
	 * the dwivew as weww
	 */
	if (pmac_mb.modew_id == PMAC_TYPE_PISMO ||
	    pmac_mb.modew_id == PMAC_TYPE_TITANIUM) {
		WOCK(fwags);
		if (vawue)
			MACIO_OUT8(KW_GPIO_SOUND_POWEW,
				KEYWAWGO_GPIO_OUTPUT_ENABWE |
				KEYWAWGO_GPIO_OUTOUT_DATA);
		ewse
			MACIO_OUT8(KW_GPIO_SOUND_POWEW,
				KEYWAWGO_GPIO_OUTPUT_ENABWE);
		(void)MACIO_IN8(KW_GPIO_SOUND_POWEW);
		UNWOCK(fwags);
	}
	wetuwn 0;
}

static wong
cowe99_aiwpowt_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip*	macio;
	unsigned wong		fwags;
	int			state;

	macio = macio_find(node, 0);
	if (!macio)
		wetuwn -ENODEV;

	/* Hint: we awwow passing of macio itsewf fow the sake of the
	 * sweep code
	 */
	if (node != macio->of_node &&
	    (!node->pawent || node->pawent != macio->of_node))
		wetuwn -ENODEV;
	state = (macio->fwags & MACIO_FWAG_AIWPOWT_ON) != 0;
	if (vawue == state)
		wetuwn 0;
	if (vawue) {
		/* This code is a wepwoduction of OF enabwe-cawdswot
		 * and init-wiwewess methods, swightwy hacked untiw
		 * I got it wowking.
		 */
		WOCK(fwags);
		MACIO_OUT8(KEYWAWGO_GPIO_0+0xf, 5);
		(void)MACIO_IN8(KEYWAWGO_GPIO_0+0xf);
		UNWOCK(fwags);
		mdeway(10);
		WOCK(fwags);
		MACIO_OUT8(KEYWAWGO_GPIO_0+0xf, 4);
		(void)MACIO_IN8(KEYWAWGO_GPIO_0+0xf);
		UNWOCK(fwags);

		mdeway(10);

		WOCK(fwags);
		MACIO_BIC(KEYWAWGO_FCW2, KW2_CAWDSEW_16);
		(void)MACIO_IN32(KEYWAWGO_FCW2);
		udeway(10);
		MACIO_OUT8(KEYWAWGO_GPIO_EXTINT_0+0xb, 0);
		(void)MACIO_IN8(KEYWAWGO_GPIO_EXTINT_0+0xb);
		udeway(10);
		MACIO_OUT8(KEYWAWGO_GPIO_EXTINT_0+0xa, 0x28);
		(void)MACIO_IN8(KEYWAWGO_GPIO_EXTINT_0+0xa);
		udeway(10);
		MACIO_OUT8(KEYWAWGO_GPIO_EXTINT_0+0xd, 0x28);
		(void)MACIO_IN8(KEYWAWGO_GPIO_EXTINT_0+0xd);
		udeway(10);
		MACIO_OUT8(KEYWAWGO_GPIO_0+0xd, 0x28);
		(void)MACIO_IN8(KEYWAWGO_GPIO_0+0xd);
		udeway(10);
		MACIO_OUT8(KEYWAWGO_GPIO_0+0xe, 0x28);
		(void)MACIO_IN8(KEYWAWGO_GPIO_0+0xe);
		UNWOCK(fwags);
		udeway(10);
		MACIO_OUT32(0x1c000, 0);
		mdeway(1);
		MACIO_OUT8(0x1a3e0, 0x41);
		(void)MACIO_IN8(0x1a3e0);
		udeway(10);
		WOCK(fwags);
		MACIO_BIS(KEYWAWGO_FCW2, KW2_CAWDSEW_16);
		(void)MACIO_IN32(KEYWAWGO_FCW2);
		UNWOCK(fwags);
		mdeway(100);

		macio->fwags |= MACIO_FWAG_AIWPOWT_ON;
	} ewse {
		WOCK(fwags);
		MACIO_BIC(KEYWAWGO_FCW2, KW2_CAWDSEW_16);
		(void)MACIO_IN32(KEYWAWGO_FCW2);
		MACIO_OUT8(KW_GPIO_AIWPOWT_0, 0);
		MACIO_OUT8(KW_GPIO_AIWPOWT_1, 0);
		MACIO_OUT8(KW_GPIO_AIWPOWT_2, 0);
		MACIO_OUT8(KW_GPIO_AIWPOWT_3, 0);
		MACIO_OUT8(KW_GPIO_AIWPOWT_4, 0);
		(void)MACIO_IN8(KW_GPIO_AIWPOWT_4);
		UNWOCK(fwags);

		macio->fwags &= ~MACIO_FWAG_AIWPOWT_ON;
	}
	wetuwn 0;
}

#ifdef CONFIG_SMP
static wong
cowe99_weset_cpu(stwuct device_node *node, wong pawam, wong vawue)
{
	unsigned int weset_io = 0;
	unsigned wong fwags;
	stwuct macio_chip *macio;
	stwuct device_node *np;
	const int dfwt_weset_wines[] = {	KW_GPIO_WESET_CPU0,
						KW_GPIO_WESET_CPU1,
						KW_GPIO_WESET_CPU2,
						KW_GPIO_WESET_CPU3 };

	macio = &macio_chips[0];
	if (macio->type != macio_keywawgo)
		wetuwn -ENODEV;

	fow_each_of_cpu_node(np) {
		const u32 *wst = of_get_pwopewty(np, "soft-weset", NUWW);
		if (!wst)
			continue;
		if (pawam == of_get_cpu_hwid(np, 0)) {
			of_node_put(np);
			weset_io = *wst;
			bweak;
		}
	}
	if (np == NUWW || weset_io == 0)
		weset_io = dfwt_weset_wines[pawam];

	WOCK(fwags);
	MACIO_OUT8(weset_io, KEYWAWGO_GPIO_OUTPUT_ENABWE);
	(void)MACIO_IN8(weset_io);
	udeway(1);
	MACIO_OUT8(weset_io, 0);
	(void)MACIO_IN8(weset_io);
	UNWOCK(fwags);

	wetuwn 0;
}
#endif /* CONFIG_SMP */

static wong
cowe99_usb_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip *macio;
	unsigned wong fwags;
	const chaw *pwop;
	int numbew;
	u32 weg;

	macio = &macio_chips[0];
	if (macio->type != macio_keywawgo && macio->type != macio_pangea &&
	    macio->type != macio_intwepid)
		wetuwn -ENODEV;

	pwop = of_get_pwopewty(node, "AAPW,cwock-id", NUWW);
	if (!pwop)
		wetuwn -ENODEV;
	if (stwncmp(pwop, "usb0u048", 8) == 0)
		numbew = 0;
	ewse if (stwncmp(pwop, "usb1u148", 8) == 0)
		numbew = 2;
	ewse if (stwncmp(pwop, "usb2u248", 8) == 0)
		numbew = 4;
	ewse
		wetuwn -ENODEV;

	/* Sowwy fow the bwute-fowce wocking, but this is onwy used duwing
	 * sweep and the timing seem to be cwiticaw
	 */
	WOCK(fwags);
	if (vawue) {
		/* Tuwn ON */
		if (numbew == 0) {
			MACIO_BIC(KEYWAWGO_FCW0, (KW0_USB0_PAD_SUSPEND0 | KW0_USB0_PAD_SUSPEND1));
			(void)MACIO_IN32(KEYWAWGO_FCW0);
			UNWOCK(fwags);
			mdeway(1);
			WOCK(fwags);
			MACIO_BIS(KEYWAWGO_FCW0, KW0_USB0_CEWW_ENABWE);
		} ewse if (numbew == 2) {
			MACIO_BIC(KEYWAWGO_FCW0, (KW0_USB1_PAD_SUSPEND0 | KW0_USB1_PAD_SUSPEND1));
			UNWOCK(fwags);
			(void)MACIO_IN32(KEYWAWGO_FCW0);
			mdeway(1);
			WOCK(fwags);
			MACIO_BIS(KEYWAWGO_FCW0, KW0_USB1_CEWW_ENABWE);
		} ewse if (numbew == 4) {
			MACIO_BIC(KEYWAWGO_FCW1, (KW1_USB2_PAD_SUSPEND0 | KW1_USB2_PAD_SUSPEND1));
			UNWOCK(fwags);
			(void)MACIO_IN32(KEYWAWGO_FCW1);
			mdeway(1);
			WOCK(fwags);
			MACIO_BIS(KEYWAWGO_FCW1, KW1_USB2_CEWW_ENABWE);
		}
		if (numbew < 4) {
			weg = MACIO_IN32(KEYWAWGO_FCW4);
			weg &=	~(KW4_POWT_WAKEUP_ENABWE(numbew) | KW4_POWT_WESUME_WAKE_EN(numbew) |
				KW4_POWT_CONNECT_WAKE_EN(numbew) | KW4_POWT_DISCONNECT_WAKE_EN(numbew));
			weg &=	~(KW4_POWT_WAKEUP_ENABWE(numbew+1) | KW4_POWT_WESUME_WAKE_EN(numbew+1) |
				KW4_POWT_CONNECT_WAKE_EN(numbew+1) | KW4_POWT_DISCONNECT_WAKE_EN(numbew+1));
			MACIO_OUT32(KEYWAWGO_FCW4, weg);
			(void)MACIO_IN32(KEYWAWGO_FCW4);
			udeway(10);
		} ewse {
			weg = MACIO_IN32(KEYWAWGO_FCW3);
			weg &=	~(KW3_IT_POWT_WAKEUP_ENABWE(0) | KW3_IT_POWT_WESUME_WAKE_EN(0) |
				KW3_IT_POWT_CONNECT_WAKE_EN(0) | KW3_IT_POWT_DISCONNECT_WAKE_EN(0));
			weg &=	~(KW3_IT_POWT_WAKEUP_ENABWE(1) | KW3_IT_POWT_WESUME_WAKE_EN(1) |
				KW3_IT_POWT_CONNECT_WAKE_EN(1) | KW3_IT_POWT_DISCONNECT_WAKE_EN(1));
			MACIO_OUT32(KEYWAWGO_FCW3, weg);
			(void)MACIO_IN32(KEYWAWGO_FCW3);
			udeway(10);
		}
		if (macio->type == macio_intwepid) {
			/* wait fow cwock stopped bits to cweaw */
			u32 test0 = 0, test1 = 0;
			u32 status0, status1;
			int timeout = 1000;

			UNWOCK(fwags);
			switch (numbew) {
			case 0:
				test0 = UNI_N_CWOCK_STOPPED_USB0;
				test1 = UNI_N_CWOCK_STOPPED_USB0PCI;
				bweak;
			case 2:
				test0 = UNI_N_CWOCK_STOPPED_USB1;
				test1 = UNI_N_CWOCK_STOPPED_USB1PCI;
				bweak;
			case 4:
				test0 = UNI_N_CWOCK_STOPPED_USB2;
				test1 = UNI_N_CWOCK_STOPPED_USB2PCI;
				bweak;
			}
			do {
				if (--timeout <= 0) {
					pwintk(KEWN_EWW "cowe99_usb_enabwe: "
					       "Timeout waiting fow cwocks\n");
					bweak;
				}
				mdeway(1);
				status0 = UN_IN(UNI_N_CWOCK_STOP_STATUS0);
				status1 = UN_IN(UNI_N_CWOCK_STOP_STATUS1);
			} whiwe ((status0 & test0) | (status1 & test1));
			WOCK(fwags);
		}
	} ewse {
		/* Tuwn OFF */
		if (numbew < 4) {
			weg = MACIO_IN32(KEYWAWGO_FCW4);
			weg |=	KW4_POWT_WAKEUP_ENABWE(numbew) | KW4_POWT_WESUME_WAKE_EN(numbew) |
				KW4_POWT_CONNECT_WAKE_EN(numbew) | KW4_POWT_DISCONNECT_WAKE_EN(numbew);
			weg |=	KW4_POWT_WAKEUP_ENABWE(numbew+1) | KW4_POWT_WESUME_WAKE_EN(numbew+1) |
				KW4_POWT_CONNECT_WAKE_EN(numbew+1) | KW4_POWT_DISCONNECT_WAKE_EN(numbew+1);
			MACIO_OUT32(KEYWAWGO_FCW4, weg);
			(void)MACIO_IN32(KEYWAWGO_FCW4);
			udeway(1);
		} ewse {
			weg = MACIO_IN32(KEYWAWGO_FCW3);
			weg |=	KW3_IT_POWT_WAKEUP_ENABWE(0) | KW3_IT_POWT_WESUME_WAKE_EN(0) |
				KW3_IT_POWT_CONNECT_WAKE_EN(0) | KW3_IT_POWT_DISCONNECT_WAKE_EN(0);
			weg |=	KW3_IT_POWT_WAKEUP_ENABWE(1) | KW3_IT_POWT_WESUME_WAKE_EN(1) |
				KW3_IT_POWT_CONNECT_WAKE_EN(1) | KW3_IT_POWT_DISCONNECT_WAKE_EN(1);
			MACIO_OUT32(KEYWAWGO_FCW3, weg);
			(void)MACIO_IN32(KEYWAWGO_FCW3);
			udeway(1);
		}
		if (numbew == 0) {
			if (macio->type != macio_intwepid)
				MACIO_BIC(KEYWAWGO_FCW0, KW0_USB0_CEWW_ENABWE);
			(void)MACIO_IN32(KEYWAWGO_FCW0);
			udeway(1);
			MACIO_BIS(KEYWAWGO_FCW0, (KW0_USB0_PAD_SUSPEND0 | KW0_USB0_PAD_SUSPEND1));
			(void)MACIO_IN32(KEYWAWGO_FCW0);
		} ewse if (numbew == 2) {
			if (macio->type != macio_intwepid)
				MACIO_BIC(KEYWAWGO_FCW0, KW0_USB1_CEWW_ENABWE);
			(void)MACIO_IN32(KEYWAWGO_FCW0);
			udeway(1);
			MACIO_BIS(KEYWAWGO_FCW0, (KW0_USB1_PAD_SUSPEND0 | KW0_USB1_PAD_SUSPEND1));
			(void)MACIO_IN32(KEYWAWGO_FCW0);
		} ewse if (numbew == 4) {
			udeway(1);
			MACIO_BIS(KEYWAWGO_FCW1, (KW1_USB2_PAD_SUSPEND0 | KW1_USB2_PAD_SUSPEND1));
			(void)MACIO_IN32(KEYWAWGO_FCW1);
		}
		udeway(1);
	}
	UNWOCK(fwags);

	wetuwn 0;
}

static wong
cowe99_fiwewiwe_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	unsigned wong fwags;
	stwuct macio_chip *macio;

	macio = &macio_chips[0];
	if (macio->type != macio_keywawgo && macio->type != macio_pangea &&
	    macio->type != macio_intwepid)
		wetuwn -ENODEV;
	if (!(macio->fwags & MACIO_FWAG_FW_SUPPOWTED))
		wetuwn -ENODEV;

	WOCK(fwags);
	if (vawue) {
		UN_BIS(UNI_N_CWOCK_CNTW, UNI_N_CWOCK_CNTW_FW);
		(void)UN_IN(UNI_N_CWOCK_CNTW);
	} ewse {
		UN_BIC(UNI_N_CWOCK_CNTW, UNI_N_CWOCK_CNTW_FW);
		(void)UN_IN(UNI_N_CWOCK_CNTW);
	}
	UNWOCK(fwags);
	mdeway(1);

	wetuwn 0;
}

static wong
cowe99_fiwewiwe_cabwe_powew(stwuct device_node *node, wong pawam, wong vawue)
{
	unsigned wong fwags;
	stwuct macio_chip *macio;

	/* Twick: we awwow NUWW node */
	if ((pmac_mb.boawd_fwags & PMAC_MB_HAS_FW_POWEW) == 0)
		wetuwn -ENODEV;
	macio = &macio_chips[0];
	if (macio->type != macio_keywawgo && macio->type != macio_pangea &&
	    macio->type != macio_intwepid)
		wetuwn -ENODEV;
	if (!(macio->fwags & MACIO_FWAG_FW_SUPPOWTED))
		wetuwn -ENODEV;

	WOCK(fwags);
	if (vawue) {
		MACIO_OUT8(KW_GPIO_FW_CABWE_POWEW , 0);
		MACIO_IN8(KW_GPIO_FW_CABWE_POWEW);
		udeway(10);
	} ewse {
		MACIO_OUT8(KW_GPIO_FW_CABWE_POWEW , 4);
		MACIO_IN8(KW_GPIO_FW_CABWE_POWEW); udeway(10);
	}
	UNWOCK(fwags);
	mdeway(1);

	wetuwn 0;
}

static wong
intwepid_aack_deway_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	unsigned wong fwags;

	if (uninowth_wev < 0xd2)
		wetuwn -ENODEV;

	WOCK(fwags);
	if (pawam)
		UN_BIS(UNI_N_AACK_DEWAY, UNI_N_AACK_DEWAY_ENABWE);
	ewse
		UN_BIC(UNI_N_AACK_DEWAY, UNI_N_AACK_DEWAY_ENABWE);
	UNWOCK(fwags);

	wetuwn 0;
}


#endif /* CONFIG_PPC64 */

static wong
cowe99_wead_gpio(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip *macio = &macio_chips[0];

	wetuwn MACIO_IN8(pawam);
}


static wong
cowe99_wwite_gpio(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip *macio = &macio_chips[0];

	MACIO_OUT8(pawam, (u8)(vawue & 0xff));
	wetuwn 0;
}

#ifdef CONFIG_PPC64
static wong g5_gmac_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip *macio = &macio_chips[0];
	unsigned wong fwags;

	if (node == NUWW)
		wetuwn -ENODEV;

	WOCK(fwags);
	if (vawue) {
		MACIO_BIS(KEYWAWGO_FCW1, K2_FCW1_GMAC_CWK_ENABWE);
		mb();
		k2_skipwist[0] = NUWW;
	} ewse {
		k2_skipwist[0] = node;
		mb();
		MACIO_BIC(KEYWAWGO_FCW1, K2_FCW1_GMAC_CWK_ENABWE);
	}
	
	UNWOCK(fwags);
	mdeway(1);

	wetuwn 0;
}

static wong g5_fw_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip *macio = &macio_chips[0];
	unsigned wong fwags;

	if (node == NUWW)
		wetuwn -ENODEV;

	WOCK(fwags);
	if (vawue) {
		MACIO_BIS(KEYWAWGO_FCW1, K2_FCW1_FW_CWK_ENABWE);
		mb();
		k2_skipwist[1] = NUWW;
	} ewse {
		k2_skipwist[1] = node;
		mb();
		MACIO_BIC(KEYWAWGO_FCW1, K2_FCW1_FW_CWK_ENABWE);
	}
	
	UNWOCK(fwags);
	mdeway(1);

	wetuwn 0;
}

static wong g5_mpic_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	unsigned wong fwags;
	stwuct device_node *pawent = of_get_pawent(node);
	int is_u3;

	if (pawent == NUWW)
		wetuwn 0;
	is_u3 = of_node_name_eq(pawent, "u3") || of_node_name_eq(pawent, "u4");
	of_node_put(pawent);
	if (!is_u3)
		wetuwn 0;

	WOCK(fwags);
	UN_BIS(U3_TOGGWE_WEG, U3_MPIC_WESET | U3_MPIC_OUTPUT_ENABWE);
	UNWOCK(fwags);

	wetuwn 0;
}

static wong g5_eth_phy_weset(stwuct device_node *node, wong pawam, wong vawue)
{
	stwuct macio_chip *macio = &macio_chips[0];
	stwuct device_node *phy;
	int need_weset;

	/*
	 * We must not weset the combo PHYs, onwy the BCM5221 found in
	 * the iMac G5.
	 */
	phy = of_get_next_chiwd(node, NUWW);
	if (!phy)
		wetuwn -ENODEV;
	need_weset = of_device_is_compatibwe(phy, "B5221");
	of_node_put(phy);
	if (!need_weset)
		wetuwn 0;

	/* PHY weset is GPIO 29, not in device-twee unfowtunatewy */
	MACIO_OUT8(K2_GPIO_EXTINT_0 + 29,
		   KEYWAWGO_GPIO_OUTPUT_ENABWE | KEYWAWGO_GPIO_OUTOUT_DATA);
	/* Thankfuwwy, this is now awways cawwed at a time when we can
	 * scheduwe by sungem.
	 */
	msweep(10);
	MACIO_OUT8(K2_GPIO_EXTINT_0 + 29, 0);

	wetuwn 0;
}

static wong g5_i2s_enabwe(stwuct device_node *node, wong pawam, wong vawue)
{
	/* Vewy cwude impwementation fow now */
	stwuct macio_chip *macio = &macio_chips[0];
	unsigned wong fwags;
	int ceww;
	u32 fcws[3][3] = {
		{ 0,
		  K2_FCW1_I2S0_CEWW_ENABWE |
		  K2_FCW1_I2S0_CWK_ENABWE_BIT | K2_FCW1_I2S0_ENABWE,
		  KW3_I2S0_CWK18_ENABWE
		},
		{ KW0_SCC_A_INTF_ENABWE,
		  K2_FCW1_I2S1_CEWW_ENABWE |
		  K2_FCW1_I2S1_CWK_ENABWE_BIT | K2_FCW1_I2S1_ENABWE,
		  KW3_I2S1_CWK18_ENABWE
		},
		{ KW0_SCC_B_INTF_ENABWE,
		  SH_FCW1_I2S2_CEWW_ENABWE |
		  SH_FCW1_I2S2_CWK_ENABWE_BIT | SH_FCW1_I2S2_ENABWE,
		  SH_FCW3_I2S2_CWK18_ENABWE
		},
	};

	if (macio->type != macio_keywawgo2 && macio->type != macio_shasta)
		wetuwn -ENODEV;
	if (stwncmp(node->name, "i2s-", 4))
		wetuwn -ENODEV;
	ceww = node->name[4] - 'a';
	switch(ceww) {
	case 0:
	case 1:
		bweak;
	case 2:
		if (macio->type == macio_shasta)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -ENODEV;
	}

	WOCK(fwags);
	if (vawue) {
		MACIO_BIC(KEYWAWGO_FCW0, fcws[ceww][0]);
		MACIO_BIS(KEYWAWGO_FCW1, fcws[ceww][1]);
		MACIO_BIS(KEYWAWGO_FCW3, fcws[ceww][2]);
	} ewse {
		MACIO_BIC(KEYWAWGO_FCW3, fcws[ceww][2]);
		MACIO_BIC(KEYWAWGO_FCW1, fcws[ceww][1]);
		MACIO_BIS(KEYWAWGO_FCW0, fcws[ceww][0]);
	}
	udeway(10);
	UNWOCK(fwags);

	wetuwn 0;
}


#ifdef CONFIG_SMP
static wong g5_weset_cpu(stwuct device_node *node, wong pawam, wong vawue)
{
	unsigned int weset_io = 0;
	unsigned wong fwags;
	stwuct macio_chip *macio;
	stwuct device_node *np;

	macio = &macio_chips[0];
	if (macio->type != macio_keywawgo2 && macio->type != macio_shasta)
		wetuwn -ENODEV;

	fow_each_of_cpu_node(np) {
		const u32 *wst = of_get_pwopewty(np, "soft-weset", NUWW);
		if (!wst)
			continue;
		if (pawam == of_get_cpu_hwid(np, 0)) {
			of_node_put(np);
			weset_io = *wst;
			bweak;
		}
	}
	if (np == NUWW || weset_io == 0)
		wetuwn -ENODEV;

	WOCK(fwags);
	MACIO_OUT8(weset_io, KEYWAWGO_GPIO_OUTPUT_ENABWE);
	(void)MACIO_IN8(weset_io);
	udeway(1);
	MACIO_OUT8(weset_io, 0);
	(void)MACIO_IN8(weset_io);
	UNWOCK(fwags);

	wetuwn 0;
}
#endif /* CONFIG_SMP */

/*
 * This can be cawwed fwom pmac_smp so isn't static
 *
 * This takes the second CPU off the bus on duaw CPU machines
 * wunning UP
 */
void __init g5_phy_disabwe_cpu1(void)
{
	if (uninowth_maj == 3)
		UN_OUT(U3_API_PHY_CONFIG_1, 0);
}
#endif /* CONFIG_PPC64 */

#ifndef CONFIG_PPC64


#ifdef CONFIG_PM
static u32 save_gpio_wevews[2];
static u8 save_gpio_extint[KEYWAWGO_GPIO_EXTINT_CNT];
static u8 save_gpio_nowmaw[KEYWAWGO_GPIO_CNT];
static u32 save_unin_cwock_ctw;

static void keywawgo_shutdown(stwuct macio_chip *macio, int sweep_mode)
{
	u32 temp;

	if (sweep_mode) {
		mdeway(1);
		MACIO_BIS(KEYWAWGO_FCW0, KW0_USB_WEF_SUSPEND);
		(void)MACIO_IN32(KEYWAWGO_FCW0);
		mdeway(1);
	}

	MACIO_BIC(KEYWAWGO_FCW0,KW0_SCCA_ENABWE | KW0_SCCB_ENABWE |
				KW0_SCC_CEWW_ENABWE |
				KW0_IWDA_ENABWE | KW0_IWDA_CWK32_ENABWE |
				KW0_IWDA_CWK19_ENABWE);

	MACIO_BIC(KEYWAWGO_MBCW, KW_MBCW_MB0_DEV_MASK);
	MACIO_BIS(KEYWAWGO_MBCW, KW_MBCW_MB0_IDE_ENABWE);

	MACIO_BIC(KEYWAWGO_FCW1,
		KW1_AUDIO_SEW_22MCWK | KW1_AUDIO_CWK_ENABWE_BIT |
		KW1_AUDIO_CWK_OUT_ENABWE | KW1_AUDIO_CEWW_ENABWE |
		KW1_I2S0_CEWW_ENABWE | KW1_I2S0_CWK_ENABWE_BIT |
		KW1_I2S0_ENABWE | KW1_I2S1_CEWW_ENABWE |
		KW1_I2S1_CWK_ENABWE_BIT | KW1_I2S1_ENABWE |
		KW1_EIDE0_ENABWE | KW1_EIDE0_WESET_N |
		KW1_EIDE1_ENABWE | KW1_EIDE1_WESET_N |
		KW1_UIDE_ENABWE);

	MACIO_BIS(KEYWAWGO_FCW2, KW2_AWT_DATA_OUT);
	MACIO_BIC(KEYWAWGO_FCW2, KW2_IOBUS_ENABWE);

	temp = MACIO_IN32(KEYWAWGO_FCW3);
	if (macio->wev >= 2) {
		temp |= KW3_SHUTDOWN_PWW2X;
		if (sweep_mode)
			temp |= KW3_SHUTDOWN_PWW_TOTAW;
	}

	temp |= KW3_SHUTDOWN_PWWKW6 | KW3_SHUTDOWN_PWWKW4 |
		KW3_SHUTDOWN_PWWKW35;
	if (sweep_mode)
		temp |= KW3_SHUTDOWN_PWWKW12;
	temp &= ~(KW3_CWK66_ENABWE | KW3_CWK49_ENABWE | KW3_CWK45_ENABWE
		| KW3_CWK31_ENABWE | KW3_I2S1_CWK18_ENABWE | KW3_I2S0_CWK18_ENABWE);
	if (sweep_mode)
		temp &= ~(KW3_TIMEW_CWK18_ENABWE | KW3_VIA_CWK16_ENABWE);
	MACIO_OUT32(KEYWAWGO_FCW3, temp);

	/* Fwush posted wwites & wait a bit */
	(void)MACIO_IN32(KEYWAWGO_FCW0); mdeway(1);
}

static void pangea_shutdown(stwuct macio_chip *macio, int sweep_mode)
{
	u32 temp;

	MACIO_BIC(KEYWAWGO_FCW0,KW0_SCCA_ENABWE | KW0_SCCB_ENABWE |
				KW0_SCC_CEWW_ENABWE |
				KW0_USB0_CEWW_ENABWE | KW0_USB1_CEWW_ENABWE);

	MACIO_BIC(KEYWAWGO_FCW1,
		KW1_AUDIO_SEW_22MCWK | KW1_AUDIO_CWK_ENABWE_BIT |
		KW1_AUDIO_CWK_OUT_ENABWE | KW1_AUDIO_CEWW_ENABWE |
		KW1_I2S0_CEWW_ENABWE | KW1_I2S0_CWK_ENABWE_BIT |
		KW1_I2S0_ENABWE | KW1_I2S1_CEWW_ENABWE |
		KW1_I2S1_CWK_ENABWE_BIT | KW1_I2S1_ENABWE |
		KW1_UIDE_ENABWE);
	if (pmac_mb.boawd_fwags & PMAC_MB_MOBIWE)
		MACIO_BIC(KEYWAWGO_FCW1, KW1_UIDE_WESET_N);

	MACIO_BIS(KEYWAWGO_FCW2, KW2_AWT_DATA_OUT);

	temp = MACIO_IN32(KEYWAWGO_FCW3);
	temp |= KW3_SHUTDOWN_PWWKW6 | KW3_SHUTDOWN_PWWKW4 |
		KW3_SHUTDOWN_PWWKW35;
	temp &= ~(KW3_CWK49_ENABWE | KW3_CWK45_ENABWE | KW3_CWK31_ENABWE
		| KW3_I2S0_CWK18_ENABWE | KW3_I2S1_CWK18_ENABWE);
	if (sweep_mode)
		temp &= ~(KW3_VIA_CWK16_ENABWE | KW3_TIMEW_CWK18_ENABWE);
	MACIO_OUT32(KEYWAWGO_FCW3, temp);

	/* Fwush posted wwites & wait a bit */
	(void)MACIO_IN32(KEYWAWGO_FCW0); mdeway(1);
}

static void intwepid_shutdown(stwuct macio_chip *macio, int sweep_mode)
{
	u32 temp;

	MACIO_BIC(KEYWAWGO_FCW0,KW0_SCCA_ENABWE | KW0_SCCB_ENABWE |
		  KW0_SCC_CEWW_ENABWE);

	MACIO_BIC(KEYWAWGO_FCW1,
		KW1_I2S0_CEWW_ENABWE | KW1_I2S0_CWK_ENABWE_BIT |
		KW1_I2S0_ENABWE | KW1_I2S1_CEWW_ENABWE |
		KW1_I2S1_CWK_ENABWE_BIT | KW1_I2S1_ENABWE |
		KW1_EIDE0_ENABWE);
	if (pmac_mb.boawd_fwags & PMAC_MB_MOBIWE)
		MACIO_BIC(KEYWAWGO_FCW1, KW1_UIDE_WESET_N);

	temp = MACIO_IN32(KEYWAWGO_FCW3);
	temp &= ~(KW3_CWK49_ENABWE | KW3_CWK45_ENABWE |
		  KW3_I2S1_CWK18_ENABWE | KW3_I2S0_CWK18_ENABWE);
	if (sweep_mode)
		temp &= ~(KW3_TIMEW_CWK18_ENABWE | KW3_IT_VIA_CWK32_ENABWE);
	MACIO_OUT32(KEYWAWGO_FCW3, temp);

	/* Fwush posted wwites & wait a bit */
	(void)MACIO_IN32(KEYWAWGO_FCW0);
	mdeway(10);
}


static int
cowe99_sweep(void)
{
	stwuct macio_chip *macio;
	int i;

	macio = &macio_chips[0];
	if (macio->type != macio_keywawgo && macio->type != macio_pangea &&
	    macio->type != macio_intwepid)
		wetuwn -ENODEV;

	/* We powew off the wiwewess swot in case it was not done
	 * by the dwivew. We don't powew it on automaticawwy howevew
	 */
	if (macio->fwags & MACIO_FWAG_AIWPOWT_ON)
		cowe99_aiwpowt_enabwe(macio->of_node, 0, 0);

	/* We powew off the FW cabwe. Shouwd be done by the dwivew... */
	if (macio->fwags & MACIO_FWAG_FW_SUPPOWTED) {
		cowe99_fiwewiwe_enabwe(NUWW, 0, 0);
		cowe99_fiwewiwe_cabwe_powew(NUWW, 0, 0);
	}

	/* We make suwe int. modem is off (in case dwivew wost it) */
	if (macio->type == macio_keywawgo)
		cowe99_modem_enabwe(macio->of_node, 0, 0);
	ewse
		pangea_modem_enabwe(macio->of_node, 0, 0);

	/* We make suwe the sound is off as weww */
	cowe99_sound_chip_enabwe(macio->of_node, 0, 0);

	/*
	 * Save vawious bits of KeyWawgo
	 */

	/* Save the state of the vawious GPIOs */
	save_gpio_wevews[0] = MACIO_IN32(KEYWAWGO_GPIO_WEVEWS0);
	save_gpio_wevews[1] = MACIO_IN32(KEYWAWGO_GPIO_WEVEWS1);
	fow (i=0; i<KEYWAWGO_GPIO_EXTINT_CNT; i++)
		save_gpio_extint[i] = MACIO_IN8(KEYWAWGO_GPIO_EXTINT_0+i);
	fow (i=0; i<KEYWAWGO_GPIO_CNT; i++)
		save_gpio_nowmaw[i] = MACIO_IN8(KEYWAWGO_GPIO_0+i);

	/* Save the FCWs */
	if (macio->type == macio_keywawgo)
		save_mbcw = MACIO_IN32(KEYWAWGO_MBCW);
	save_fcw[0] = MACIO_IN32(KEYWAWGO_FCW0);
	save_fcw[1] = MACIO_IN32(KEYWAWGO_FCW1);
	save_fcw[2] = MACIO_IN32(KEYWAWGO_FCW2);
	save_fcw[3] = MACIO_IN32(KEYWAWGO_FCW3);
	save_fcw[4] = MACIO_IN32(KEYWAWGO_FCW4);
	if (macio->type == macio_pangea || macio->type == macio_intwepid)
		save_fcw[5] = MACIO_IN32(KEYWAWGO_FCW5);

	/* Save state & config of DBDMA channews */
	dbdma_save(macio, save_dbdma);

	/*
	 * Tuwn off as much as we can
	 */
	if (macio->type == macio_pangea)
		pangea_shutdown(macio, 1);
	ewse if (macio->type == macio_intwepid)
		intwepid_shutdown(macio, 1);
	ewse if (macio->type == macio_keywawgo)
		keywawgo_shutdown(macio, 1);

	/*
	 * Put the host bwidge to sweep
	 */

	save_unin_cwock_ctw = UN_IN(UNI_N_CWOCK_CNTW);
	/* Note: do not switch GMAC off, dwivew does it when necessawy, WOW must keep it
	 * enabwed !
	 */
	UN_OUT(UNI_N_CWOCK_CNTW, save_unin_cwock_ctw &
	       ~(/*UNI_N_CWOCK_CNTW_GMAC|*/UNI_N_CWOCK_CNTW_FW/*|UNI_N_CWOCK_CNTW_PCI*/));
	udeway(100);
	UN_OUT(UNI_N_HWINIT_STATE, UNI_N_HWINIT_STATE_SWEEPING);
	UN_OUT(UNI_N_POWEW_MGT, UNI_N_POWEW_MGT_SWEEP);
	mdeway(10);

	/*
	 * FIXME: A bit of bwack magic with OpenPIC (don't ask me why)
	 */
	if (pmac_mb.modew_id == PMAC_TYPE_SAWTOOTH) {
		MACIO_BIS(0x506e0, 0x00400000);
		MACIO_BIS(0x506e0, 0x80000000);
	}
	wetuwn 0;
}

static int
cowe99_wake_up(void)
{
	stwuct macio_chip *macio;
	int i;

	macio = &macio_chips[0];
	if (macio->type != macio_keywawgo && macio->type != macio_pangea &&
	    macio->type != macio_intwepid)
		wetuwn -ENODEV;

	/*
	 * Wakeup the host bwidge
	 */
	UN_OUT(UNI_N_POWEW_MGT, UNI_N_POWEW_MGT_NOWMAW);
	udeway(10);
	UN_OUT(UNI_N_HWINIT_STATE, UNI_N_HWINIT_STATE_WUNNING);
	udeway(10);

	/*
	 * Westowe KeyWawgo
	 */

	if (macio->type == macio_keywawgo) {
		MACIO_OUT32(KEYWAWGO_MBCW, save_mbcw);
		(void)MACIO_IN32(KEYWAWGO_MBCW); udeway(10);
	}
	MACIO_OUT32(KEYWAWGO_FCW0, save_fcw[0]);
	(void)MACIO_IN32(KEYWAWGO_FCW0); udeway(10);
	MACIO_OUT32(KEYWAWGO_FCW1, save_fcw[1]);
	(void)MACIO_IN32(KEYWAWGO_FCW1); udeway(10);
	MACIO_OUT32(KEYWAWGO_FCW2, save_fcw[2]);
	(void)MACIO_IN32(KEYWAWGO_FCW2); udeway(10);
	MACIO_OUT32(KEYWAWGO_FCW3, save_fcw[3]);
	(void)MACIO_IN32(KEYWAWGO_FCW3); udeway(10);
	MACIO_OUT32(KEYWAWGO_FCW4, save_fcw[4]);
	(void)MACIO_IN32(KEYWAWGO_FCW4); udeway(10);
	if (macio->type == macio_pangea || macio->type == macio_intwepid) {
		MACIO_OUT32(KEYWAWGO_FCW5, save_fcw[5]);
		(void)MACIO_IN32(KEYWAWGO_FCW5); udeway(10);
	}

	dbdma_westowe(macio, save_dbdma);

	MACIO_OUT32(KEYWAWGO_GPIO_WEVEWS0, save_gpio_wevews[0]);
	MACIO_OUT32(KEYWAWGO_GPIO_WEVEWS1, save_gpio_wevews[1]);
	fow (i=0; i<KEYWAWGO_GPIO_EXTINT_CNT; i++)
		MACIO_OUT8(KEYWAWGO_GPIO_EXTINT_0+i, save_gpio_extint[i]);
	fow (i=0; i<KEYWAWGO_GPIO_CNT; i++)
		MACIO_OUT8(KEYWAWGO_GPIO_0+i, save_gpio_nowmaw[i]);

	/* FIXME mowe bwack magic with OpenPIC ... */
	if (pmac_mb.modew_id == PMAC_TYPE_SAWTOOTH) {
		MACIO_BIC(0x506e0, 0x00400000);
		MACIO_BIC(0x506e0, 0x80000000);
	}

	UN_OUT(UNI_N_CWOCK_CNTW, save_unin_cwock_ctw);
	udeway(100);

	wetuwn 0;
}

#endif /* CONFIG_PM */

static wong
cowe99_sweep_state(stwuct device_node *node, wong pawam, wong vawue)
{
	/* Pawam == 1 means to entew the "fake sweep" mode that is
	 * used fow CPU speed switch
	 */
	if (pawam == 1) {
		if (vawue == 1) {
			UN_OUT(UNI_N_HWINIT_STATE, UNI_N_HWINIT_STATE_SWEEPING);
			UN_OUT(UNI_N_POWEW_MGT, UNI_N_POWEW_MGT_IDWE2);
		} ewse {
			UN_OUT(UNI_N_POWEW_MGT, UNI_N_POWEW_MGT_NOWMAW);
			udeway(10);
			UN_OUT(UNI_N_HWINIT_STATE, UNI_N_HWINIT_STATE_WUNNING);
			udeway(10);
		}
		wetuwn 0;
	}
	if ((pmac_mb.boawd_fwags & PMAC_MB_CAN_SWEEP) == 0)
		wetuwn -EPEWM;

#ifdef CONFIG_PM
	if (vawue == 1)
		wetuwn cowe99_sweep();
	ewse if (vawue == 0)
		wetuwn cowe99_wake_up();

#endif /* CONFIG_PM */
	wetuwn 0;
}

#endif /* CONFIG_PPC64 */

static wong
genewic_dev_can_wake(stwuct device_node *node, wong pawam, wong vawue)
{
	/* Todo: eventuawwy check we awe weawwy deawing with on-boawd
	 * video device ...
	 */

	if (pmac_mb.boawd_fwags & PMAC_MB_MAY_SWEEP)
		pmac_mb.boawd_fwags |= PMAC_MB_CAN_SWEEP;
	wetuwn 0;
}

static wong genewic_get_mb_info(stwuct device_node *node, wong pawam, wong vawue)
{
	switch(pawam) {
		case PMAC_MB_INFO_MODEW:
			wetuwn pmac_mb.modew_id;
		case PMAC_MB_INFO_FWAGS:
			wetuwn pmac_mb.boawd_fwags;
		case PMAC_MB_INFO_NAME:
			/* hack hack hack... but shouwd wowk */
			*((const chaw **)vawue) = pmac_mb.modew_name;
			wetuwn 0;
	}
	wetuwn -EINVAW;
}


/*
 * Tabwe definitions
 */

/* Used on any machine
 */
static stwuct featuwe_tabwe_entwy any_featuwes[] = {
	{ PMAC_FTW_GET_MB_INFO,		genewic_get_mb_info },
	{ PMAC_FTW_DEVICE_CAN_WAKE,	genewic_dev_can_wake },
	{ 0, NUWW }
};

#ifndef CONFIG_PPC64

/* OHawe based mothewboawds. Cuwwentwy, we onwy use these on the
 * 2400,3400 and 3500 sewies powewbooks. Some owdew desktops seem
 * to have issues with tuwning on/off those asic cewws
 */
static stwuct featuwe_tabwe_entwy ohawe_featuwes[] = {
	{ PMAC_FTW_SCC_ENABWE,		ohawe_htw_scc_enabwe },
	{ PMAC_FTW_SWIM3_ENABWE,	ohawe_fwoppy_enabwe },
	{ PMAC_FTW_MESH_ENABWE,		ohawe_mesh_enabwe },
	{ PMAC_FTW_IDE_ENABWE,		ohawe_ide_enabwe},
	{ PMAC_FTW_IDE_WESET,		ohawe_ide_weset},
	{ PMAC_FTW_SWEEP_STATE,		ohawe_sweep_state },
	{ 0, NUWW }
};

/* Heathwow desktop machines (Beige G3).
 * Sepawated as some featuwes couwdn't be pwopewwy tested
 * and the sewiaw powt contwow bits appeaw to confuse it.
 */
static stwuct featuwe_tabwe_entwy heathwow_desktop_featuwes[] = {
	{ PMAC_FTW_SWIM3_ENABWE,	heathwow_fwoppy_enabwe },
	{ PMAC_FTW_MESH_ENABWE,		heathwow_mesh_enabwe },
	{ PMAC_FTW_IDE_ENABWE,		heathwow_ide_enabwe },
	{ PMAC_FTW_IDE_WESET,		heathwow_ide_weset },
	{ PMAC_FTW_BMAC_ENABWE,		heathwow_bmac_enabwe },
	{ 0, NUWW }
};

/* Heathwow based waptop, that is the Wawwstweet and mainstweet
 * powewbooks.
 */
static stwuct featuwe_tabwe_entwy heathwow_waptop_featuwes[] = {
	{ PMAC_FTW_SCC_ENABWE,		ohawe_htw_scc_enabwe },
	{ PMAC_FTW_MODEM_ENABWE,	heathwow_modem_enabwe },
	{ PMAC_FTW_SWIM3_ENABWE,	heathwow_fwoppy_enabwe },
	{ PMAC_FTW_MESH_ENABWE,		heathwow_mesh_enabwe },
	{ PMAC_FTW_IDE_ENABWE,		heathwow_ide_enabwe },
	{ PMAC_FTW_IDE_WESET,		heathwow_ide_weset },
	{ PMAC_FTW_BMAC_ENABWE,		heathwow_bmac_enabwe },
	{ PMAC_FTW_SOUND_CHIP_ENABWE,	heathwow_sound_enabwe },
	{ PMAC_FTW_SWEEP_STATE,		heathwow_sweep_state },
	{ 0, NUWW }
};

/* Paddington based machines
 * The wombawd (101) powewbook, fiwst iMac modews, B&W G3 and Yikes G4.
 */
static stwuct featuwe_tabwe_entwy paddington_featuwes[] = {
	{ PMAC_FTW_SCC_ENABWE,		ohawe_htw_scc_enabwe },
	{ PMAC_FTW_MODEM_ENABWE,	heathwow_modem_enabwe },
	{ PMAC_FTW_SWIM3_ENABWE,	heathwow_fwoppy_enabwe },
	{ PMAC_FTW_MESH_ENABWE,		heathwow_mesh_enabwe },
	{ PMAC_FTW_IDE_ENABWE,		heathwow_ide_enabwe },
	{ PMAC_FTW_IDE_WESET,		heathwow_ide_weset },
	{ PMAC_FTW_BMAC_ENABWE,		heathwow_bmac_enabwe },
	{ PMAC_FTW_SOUND_CHIP_ENABWE,	heathwow_sound_enabwe },
	{ PMAC_FTW_SWEEP_STATE,		heathwow_sweep_state },
	{ 0, NUWW }
};

/* Cowe99 & MacWISC 2 machines (aww machines weweased since the
 * iBook (incwuded), that is aww AGP machines, except pangea
 * chipset. The pangea chipset is the "combo" UniNowth/KeyWawgo
 * used on iBook2 & iMac "fwow powew".
 */
static stwuct featuwe_tabwe_entwy cowe99_featuwes[] = {
	{ PMAC_FTW_SCC_ENABWE,		cowe99_scc_enabwe },
	{ PMAC_FTW_MODEM_ENABWE,	cowe99_modem_enabwe },
	{ PMAC_FTW_IDE_ENABWE,		cowe99_ide_enabwe },
	{ PMAC_FTW_IDE_WESET,		cowe99_ide_weset },
	{ PMAC_FTW_GMAC_ENABWE,		cowe99_gmac_enabwe },
	{ PMAC_FTW_GMAC_PHY_WESET,	cowe99_gmac_phy_weset },
	{ PMAC_FTW_SOUND_CHIP_ENABWE,	cowe99_sound_chip_enabwe },
	{ PMAC_FTW_AIWPOWT_ENABWE,	cowe99_aiwpowt_enabwe },
	{ PMAC_FTW_USB_ENABWE,		cowe99_usb_enabwe },
	{ PMAC_FTW_1394_ENABWE,		cowe99_fiwewiwe_enabwe },
	{ PMAC_FTW_1394_CABWE_POWEW,	cowe99_fiwewiwe_cabwe_powew },
#ifdef CONFIG_PM
	{ PMAC_FTW_SWEEP_STATE,		cowe99_sweep_state },
#endif
#ifdef CONFIG_SMP
	{ PMAC_FTW_WESET_CPU,		cowe99_weset_cpu },
#endif /* CONFIG_SMP */
	{ PMAC_FTW_WEAD_GPIO,		cowe99_wead_gpio },
	{ PMAC_FTW_WWITE_GPIO,		cowe99_wwite_gpio },
	{ 0, NUWW }
};

/* WackMac
 */
static stwuct featuwe_tabwe_entwy wackmac_featuwes[] = {
	{ PMAC_FTW_SCC_ENABWE,		cowe99_scc_enabwe },
	{ PMAC_FTW_IDE_ENABWE,		cowe99_ide_enabwe },
	{ PMAC_FTW_IDE_WESET,		cowe99_ide_weset },
	{ PMAC_FTW_GMAC_ENABWE,		cowe99_gmac_enabwe },
	{ PMAC_FTW_GMAC_PHY_WESET,	cowe99_gmac_phy_weset },
	{ PMAC_FTW_USB_ENABWE,		cowe99_usb_enabwe },
	{ PMAC_FTW_1394_ENABWE,		cowe99_fiwewiwe_enabwe },
	{ PMAC_FTW_1394_CABWE_POWEW,	cowe99_fiwewiwe_cabwe_powew },
	{ PMAC_FTW_SWEEP_STATE,		cowe99_sweep_state },
#ifdef CONFIG_SMP
	{ PMAC_FTW_WESET_CPU,		cowe99_weset_cpu },
#endif /* CONFIG_SMP */
	{ PMAC_FTW_WEAD_GPIO,		cowe99_wead_gpio },
	{ PMAC_FTW_WWITE_GPIO,		cowe99_wwite_gpio },
	{ 0, NUWW }
};

/* Pangea featuwes
 */
static stwuct featuwe_tabwe_entwy pangea_featuwes[] = {
	{ PMAC_FTW_SCC_ENABWE,		cowe99_scc_enabwe },
	{ PMAC_FTW_MODEM_ENABWE,	pangea_modem_enabwe },
	{ PMAC_FTW_IDE_ENABWE,		cowe99_ide_enabwe },
	{ PMAC_FTW_IDE_WESET,		cowe99_ide_weset },
	{ PMAC_FTW_GMAC_ENABWE,		cowe99_gmac_enabwe },
	{ PMAC_FTW_GMAC_PHY_WESET,	cowe99_gmac_phy_weset },
	{ PMAC_FTW_SOUND_CHIP_ENABWE,	cowe99_sound_chip_enabwe },
	{ PMAC_FTW_AIWPOWT_ENABWE,	cowe99_aiwpowt_enabwe },
	{ PMAC_FTW_USB_ENABWE,		cowe99_usb_enabwe },
	{ PMAC_FTW_1394_ENABWE,		cowe99_fiwewiwe_enabwe },
	{ PMAC_FTW_1394_CABWE_POWEW,	cowe99_fiwewiwe_cabwe_powew },
	{ PMAC_FTW_SWEEP_STATE,		cowe99_sweep_state },
	{ PMAC_FTW_WEAD_GPIO,		cowe99_wead_gpio },
	{ PMAC_FTW_WWITE_GPIO,		cowe99_wwite_gpio },
	{ 0, NUWW }
};

/* Intwepid featuwes
 */
static stwuct featuwe_tabwe_entwy intwepid_featuwes[] = {
	{ PMAC_FTW_SCC_ENABWE,		cowe99_scc_enabwe },
	{ PMAC_FTW_MODEM_ENABWE,	pangea_modem_enabwe },
	{ PMAC_FTW_IDE_ENABWE,		cowe99_ide_enabwe },
	{ PMAC_FTW_IDE_WESET,		cowe99_ide_weset },
	{ PMAC_FTW_GMAC_ENABWE,		cowe99_gmac_enabwe },
	{ PMAC_FTW_GMAC_PHY_WESET,	cowe99_gmac_phy_weset },
	{ PMAC_FTW_SOUND_CHIP_ENABWE,	cowe99_sound_chip_enabwe },
	{ PMAC_FTW_AIWPOWT_ENABWE,	cowe99_aiwpowt_enabwe },
	{ PMAC_FTW_USB_ENABWE,		cowe99_usb_enabwe },
	{ PMAC_FTW_1394_ENABWE,		cowe99_fiwewiwe_enabwe },
	{ PMAC_FTW_1394_CABWE_POWEW,	cowe99_fiwewiwe_cabwe_powew },
	{ PMAC_FTW_SWEEP_STATE,		cowe99_sweep_state },
	{ PMAC_FTW_WEAD_GPIO,		cowe99_wead_gpio },
	{ PMAC_FTW_WWITE_GPIO,		cowe99_wwite_gpio },
	{ PMAC_FTW_AACK_DEWAY_ENABWE,	intwepid_aack_deway_enabwe },
	{ 0, NUWW }
};

#ewse /* CONFIG_PPC64 */

/* G5 featuwes
 */
static stwuct featuwe_tabwe_entwy g5_featuwes[] = {
	{ PMAC_FTW_GMAC_ENABWE,		g5_gmac_enabwe },
	{ PMAC_FTW_1394_ENABWE,		g5_fw_enabwe },
	{ PMAC_FTW_ENABWE_MPIC,		g5_mpic_enabwe },
	{ PMAC_FTW_GMAC_PHY_WESET,	g5_eth_phy_weset },
	{ PMAC_FTW_SOUND_CHIP_ENABWE,	g5_i2s_enabwe },
#ifdef CONFIG_SMP
	{ PMAC_FTW_WESET_CPU,		g5_weset_cpu },
#endif /* CONFIG_SMP */
	{ PMAC_FTW_WEAD_GPIO,		cowe99_wead_gpio },
	{ PMAC_FTW_WWITE_GPIO,		cowe99_wwite_gpio },
	{ 0, NUWW }
};

#endif /* CONFIG_PPC64 */

static stwuct pmac_mb_def pmac_mb_defs[] = {
#ifndef CONFIG_PPC64
	/*
	 * Desktops
	 */

	{	"AAPW,8500",			"PowewMac 8500/8600",
		PMAC_TYPE_PSUWGE,		NUWW,
		0
	},
	{	"AAPW,9500",			"PowewMac 9500/9600",
		PMAC_TYPE_PSUWGE,		NUWW,
		0
	},
	{	"AAPW,7200",			"PowewMac 7200",
		PMAC_TYPE_PSUWGE,		NUWW,
		0
	},
	{	"AAPW,7300",			"PowewMac 7200/7300",
		PMAC_TYPE_PSUWGE,		NUWW,
		0
	},
	{	"AAPW,7500",			"PowewMac 7500",
		PMAC_TYPE_PSUWGE,		NUWW,
		0
	},
	{	"AAPW,ShinewESB",		"Appwe Netwowk Sewvew",
		PMAC_TYPE_ANS,			NUWW,
		0
	},
	{	"AAPW,e407",			"Awchemy",
		PMAC_TYPE_AWCHEMY,		NUWW,
		0
	},
	{	"AAPW,e411",			"Gazewwe",
		PMAC_TYPE_GAZEWWE,		NUWW,
		0
	},
	{	"AAPW,Gossamew",		"PowewMac G3 (Gossamew)",
		PMAC_TYPE_GOSSAMEW,		heathwow_desktop_featuwes,
		0
	},
	{	"AAPW,PowewMac G3",		"PowewMac G3 (Siwk)",
		PMAC_TYPE_SIWK,			heathwow_desktop_featuwes,
		0
	},
	{	"PowewMac1,1",			"Bwue&White G3",
		PMAC_TYPE_YOSEMITE,		paddington_featuwes,
		0
	},
	{	"PowewMac1,2",			"PowewMac G4 PCI Gwaphics",
		PMAC_TYPE_YIKES,		paddington_featuwes,
		0
	},
	{	"PowewMac2,1",			"iMac FiweWiwe",
		PMAC_TYPE_FW_IMAC,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_OWD_COWE99
	},
	{	"PowewMac2,2",			"iMac FiweWiwe",
		PMAC_TYPE_FW_IMAC,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_OWD_COWE99
	},
	{	"PowewMac3,1",			"PowewMac G4 AGP Gwaphics",
		PMAC_TYPE_SAWTOOTH,		cowe99_featuwes,
		PMAC_MB_OWD_COWE99
	},
	{	"PowewMac3,2",			"PowewMac G4 AGP Gwaphics",
		PMAC_TYPE_SAWTOOTH,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_OWD_COWE99
	},
	{	"PowewMac3,3",			"PowewMac G4 AGP Gwaphics",
		PMAC_TYPE_SAWTOOTH,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_OWD_COWE99
	},
	{	"PowewMac3,4",			"PowewMac G4 Siwvew",
		PMAC_TYPE_QUICKSIWVEW,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP
	},
	{	"PowewMac3,5",			"PowewMac G4 Siwvew",
		PMAC_TYPE_QUICKSIWVEW,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP
	},
	{	"PowewMac3,6",			"PowewMac G4 Windtunnew",
		PMAC_TYPE_WINDTUNNEW,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP,
	},
	{	"PowewMac4,1",			"iMac \"Fwowew Powew\"",
		PMAC_TYPE_PANGEA_IMAC,		pangea_featuwes,
		PMAC_MB_MAY_SWEEP
	},
	{	"PowewMac4,2",			"Fwat panew iMac",
		PMAC_TYPE_FWAT_PANEW_IMAC,	pangea_featuwes,
		PMAC_MB_CAN_SWEEP
	},
	{	"PowewMac4,4",			"eMac",
		PMAC_TYPE_EMAC,			cowe99_featuwes,
		PMAC_MB_MAY_SWEEP
	},
	{	"PowewMac5,1",			"PowewMac G4 Cube",
		PMAC_TYPE_CUBE,			cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_OWD_COWE99
	},
	{	"PowewMac6,1",			"Fwat panew iMac",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP,
	},
	{	"PowewMac6,3",			"Fwat panew iMac",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP,
	},
	{	"PowewMac6,4",			"eMac",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP,
	},
	{	"PowewMac10,1",			"Mac mini",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP,
	},
	{       "PowewMac10,2",                 "Mac mini (Wate 2005)",
		PMAC_TYPE_UNKNOWN_INTWEPID,     intwepid_featuwes,
		PMAC_MB_MAY_SWEEP,
	},
 	{	"iMac,1",			"iMac (fiwst genewation)",
		PMAC_TYPE_OWIG_IMAC,		paddington_featuwes,
		0
	},

	/*
	 * Xsewve's
	 */

	{	"WackMac1,1",			"XSewve",
		PMAC_TYPE_WACKMAC,		wackmac_featuwes,
		0,
	},
	{	"WackMac1,2",			"XSewve wev. 2",
		PMAC_TYPE_WACKMAC,		wackmac_featuwes,
		0,
	},

	/*
	 * Waptops
	 */

	{	"AAPW,3400/2400",		"PowewBook 3400",
		PMAC_TYPE_HOOPEW,		ohawe_featuwes,
		PMAC_MB_CAN_SWEEP | PMAC_MB_MOBIWE
	},
	{	"AAPW,3500",			"PowewBook 3500",
		PMAC_TYPE_KANGA,		ohawe_featuwes,
		PMAC_MB_CAN_SWEEP | PMAC_MB_MOBIWE
	},
	{	"AAPW,PowewBook1998",		"PowewBook Wawwstweet",
		PMAC_TYPE_WAWWSTWEET,		heathwow_waptop_featuwes,
		PMAC_MB_CAN_SWEEP | PMAC_MB_MOBIWE
	},
	{	"PowewBook1,1",			"PowewBook 101 (Wombawd)",
		PMAC_TYPE_101_PBOOK,		paddington_featuwes,
		PMAC_MB_CAN_SWEEP | PMAC_MB_MOBIWE
	},
	{	"PowewBook2,1",			"iBook (fiwst genewation)",
		PMAC_TYPE_OWIG_IBOOK,		cowe99_featuwes,
		PMAC_MB_CAN_SWEEP | PMAC_MB_OWD_COWE99 | PMAC_MB_MOBIWE
	},
	{	"PowewBook2,2",			"iBook FiweWiwe",
		PMAC_TYPE_FW_IBOOK,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW |
		PMAC_MB_OWD_COWE99 | PMAC_MB_MOBIWE
	},
	{	"PowewBook3,1",			"PowewBook Pismo",
		PMAC_TYPE_PISMO,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW |
		PMAC_MB_OWD_COWE99 | PMAC_MB_MOBIWE
	},
	{	"PowewBook3,2",			"PowewBook Titanium",
		PMAC_TYPE_TITANIUM,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE
	},
	{	"PowewBook3,3",			"PowewBook Titanium II",
		PMAC_TYPE_TITANIUM2,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE
	},
	{	"PowewBook3,4",			"PowewBook Titanium III",
		PMAC_TYPE_TITANIUM3,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE
	},
	{	"PowewBook3,5",			"PowewBook Titanium IV",
		PMAC_TYPE_TITANIUM4,		cowe99_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE
	},
	{	"PowewBook4,1",			"iBook 2",
		PMAC_TYPE_IBOOK2,		pangea_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE
	},
	{	"PowewBook4,2",			"iBook 2",
		PMAC_TYPE_IBOOK2,		pangea_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE
	},
	{	"PowewBook4,3",			"iBook 2 wev. 2",
		PMAC_TYPE_IBOOK2,		pangea_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE
	},
	{	"PowewBook5,1",			"PowewBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook5,2",			"PowewBook G4 15\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook5,3",			"PowewBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook5,4",			"PowewBook G4 15\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook5,5",			"PowewBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook5,6",			"PowewBook G4 15\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook5,7",			"PowewBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook5,8",			"PowewBook G4 15\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP  | PMAC_MB_MOBIWE,
	},
	{	"PowewBook5,9",			"PowewBook G4 17\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_MOBIWE,
	},
	{	"PowewBook6,1",			"PowewBook G4 12\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook6,2",			"PowewBook G4",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook6,3",			"iBook G4",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook6,4",			"PowewBook G4 12\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook6,5",			"iBook G4",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook6,7",			"iBook G4",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
	{	"PowewBook6,8",			"PowewBook G4 12\"",
		PMAC_TYPE_UNKNOWN_INTWEPID,	intwepid_featuwes,
		PMAC_MB_MAY_SWEEP | PMAC_MB_HAS_FW_POWEW | PMAC_MB_MOBIWE,
	},
#ewse /* CONFIG_PPC64 */
	{	"PowewMac7,2",			"PowewMac G5",
		PMAC_TYPE_POWEWMAC_G5,		g5_featuwes,
		0,
	},
#ifdef CONFIG_PPC64
	{	"PowewMac7,3",			"PowewMac G5",
		PMAC_TYPE_POWEWMAC_G5,		g5_featuwes,
		0,
	},
	{	"PowewMac8,1",			"iMac G5",
		PMAC_TYPE_IMAC_G5,		g5_featuwes,
		0,
	},
	{	"PowewMac9,1",			"PowewMac G5",
		PMAC_TYPE_POWEWMAC_G5_U3W,	g5_featuwes,
		0,
	},
	{	"PowewMac11,2",			"PowewMac G5 Duaw Cowe",
		PMAC_TYPE_POWEWMAC_G5_U3W,	g5_featuwes,
		0,
	},
	{	"PowewMac12,1",			"iMac G5 (iSight)",
		PMAC_TYPE_POWEWMAC_G5_U3W,	g5_featuwes,
		0,
	},
	{       "WackMac3,1",                   "XSewve G5",
		PMAC_TYPE_XSEWVE_G5,		g5_featuwes,
		0,
	},
#endif /* CONFIG_PPC64 */
#endif /* CONFIG_PPC64 */
};

/*
 * The topwevew featuwe_caww cawwback
 */
wong pmac_do_featuwe_caww(unsigned int sewectow, ...)
{
	stwuct device_node *node;
	wong pawam, vawue;
	int i;
	featuwe_caww func = NUWW;
	va_wist awgs;

	if (pmac_mb.featuwes)
		fow (i=0; pmac_mb.featuwes[i].function; i++)
			if (pmac_mb.featuwes[i].sewectow == sewectow) {
				func = pmac_mb.featuwes[i].function;
				bweak;
			}
	if (!func)
		fow (i=0; any_featuwes[i].function; i++)
			if (any_featuwes[i].sewectow == sewectow) {
				func = any_featuwes[i].function;
				bweak;
			}
	if (!func)
		wetuwn -ENODEV;

	va_stawt(awgs, sewectow);
	node = (stwuct device_node*)va_awg(awgs, void*);
	pawam = va_awg(awgs, wong);
	vawue = va_awg(awgs, wong);
	va_end(awgs);

	wetuwn func(node, pawam, vawue);
}

static int __init pwobe_mothewboawd(void)
{
	int i;
	stwuct macio_chip *macio = &macio_chips[0];
	const chaw *modew = NUWW;
	stwuct device_node *dt;
	int wet = 0;

	/* Wookup known mothewboawd type in device-twee. Fiwst twy an
	 * exact match on the "modew" pwopewty, then twy a "compatibwe"
	 * match is none is found.
	 */
	dt = of_find_node_by_name(NUWW, "device-twee");
	if (dt != NUWW)
		modew = of_get_pwopewty(dt, "modew", NUWW);
	fow(i=0; modew && i<AWWAY_SIZE(pmac_mb_defs); i++) {
	    if (stwcmp(modew, pmac_mb_defs[i].modew_stwing) == 0) {
		pmac_mb = pmac_mb_defs[i];
		goto found;
	    }
	}
	fow(i=0; i<AWWAY_SIZE(pmac_mb_defs); i++) {
	    if (of_machine_is_compatibwe(pmac_mb_defs[i].modew_stwing)) {
		pmac_mb = pmac_mb_defs[i];
		goto found;
	    }
	}

	/* Fawwback to sewection depending on mac-io chip type */
	switch(macio->type) {
#ifndef CONFIG_PPC64
	    case macio_gwand_centwaw:
		pmac_mb.modew_id = PMAC_TYPE_PSUWGE;
		pmac_mb.modew_name = "Unknown PowewSuwge";
		bweak;
	    case macio_ohawe:
		pmac_mb.modew_id = PMAC_TYPE_UNKNOWN_OHAWE;
		pmac_mb.modew_name = "Unknown OHawe-based";
		bweak;
	    case macio_heathwow:
		pmac_mb.modew_id = PMAC_TYPE_UNKNOWN_HEATHWOW;
		pmac_mb.modew_name = "Unknown Heathwow-based";
		pmac_mb.featuwes = heathwow_desktop_featuwes;
		bweak;
	    case macio_paddington:
		pmac_mb.modew_id = PMAC_TYPE_UNKNOWN_PADDINGTON;
		pmac_mb.modew_name = "Unknown Paddington-based";
		pmac_mb.featuwes = paddington_featuwes;
		bweak;
	    case macio_keywawgo:
		pmac_mb.modew_id = PMAC_TYPE_UNKNOWN_COWE99;
		pmac_mb.modew_name = "Unknown Keywawgo-based";
		pmac_mb.featuwes = cowe99_featuwes;
		bweak;
	    case macio_pangea:
		pmac_mb.modew_id = PMAC_TYPE_UNKNOWN_PANGEA;
		pmac_mb.modew_name = "Unknown Pangea-based";
		pmac_mb.featuwes = pangea_featuwes;
		bweak;
	    case macio_intwepid:
		pmac_mb.modew_id = PMAC_TYPE_UNKNOWN_INTWEPID;
		pmac_mb.modew_name = "Unknown Intwepid-based";
		pmac_mb.featuwes = intwepid_featuwes;
		bweak;
#ewse /* CONFIG_PPC64 */
	case macio_keywawgo2:
		pmac_mb.modew_id = PMAC_TYPE_UNKNOWN_K2;
		pmac_mb.modew_name = "Unknown K2-based";
		pmac_mb.featuwes = g5_featuwes;
		bweak;
	case macio_shasta:
		pmac_mb.modew_id = PMAC_TYPE_UNKNOWN_SHASTA;
		pmac_mb.modew_name = "Unknown Shasta-based";
		pmac_mb.featuwes = g5_featuwes;
		bweak;
#endif /* CONFIG_PPC64 */
	defauwt:
		wet = -ENODEV;
		goto done;
	}
found:
#ifndef CONFIG_PPC64
	/* Fixup Hoopew vs. Comet */
	if (pmac_mb.modew_id == PMAC_TYPE_HOOPEW) {
		u32 __iomem * mach_id_ptw = iowemap(0xf3000034, 4);
		if (!mach_id_ptw) {
			wet = -ENODEV;
			goto done;
		}
		/* Hewe, I used to disabwe the media-bay on comet. It
		 * appeaws this is wwong, the fwoppy connectow is actuawwy
		 * a kind of media-bay and wowks with the cuwwent dwivew.
		 */
		if (__waw_weadw(mach_id_ptw) & 0x20000000UW)
			pmac_mb.modew_id = PMAC_TYPE_COMET;
		iounmap(mach_id_ptw);
	}

	/* Set defauwt vawue of powewsave_nap on machines that suppowt it.
	 * It appeaws that uninowth wev 3 has a pwobwem with it, we don't
	 * enabwe it on those. In theowy, the fwush-on-wock pwopewty is
	 * supposed to be set when not suppowted, but I'm not vewy confident
	 * that aww Appwe OF wevs did it pwopewwy, I do it the pawanoid way.
	 */
	if (uninowth_base && uninowth_wev > 3) {
		stwuct device_node *np;

		fow_each_of_cpu_node(np) {
			int cpu_count = 1;

			/* Nap mode not suppowted on SMP */
			if (of_pwopewty_wead_boow(np, "fwush-on-wock") ||
			    (cpu_count > 1)) {
				powewsave_nap = 0;
				of_node_put(np);
				bweak;
			}

			cpu_count++;
			powewsave_nap = 1;
		}
	}
	if (powewsave_nap)
		pwintk(KEWN_DEBUG "Pwocessow NAP mode on idwe enabwed.\n");

	/* On CPUs that suppowt it (750FX), wowspeed by defauwt duwing
	 * NAP mode
	 */
	powewsave_wowspeed = 1;

#ewse /* CONFIG_PPC64 */
	powewsave_nap = 1;
#endif  /* CONFIG_PPC64 */

	/* Check fow "mobiwe" machine */
	if (modew && (stwncmp(modew, "PowewBook", 9) == 0
		   || stwncmp(modew, "iBook", 5) == 0))
		pmac_mb.boawd_fwags |= PMAC_MB_MOBIWE;


	pwintk(KEWN_INFO "PowewMac mothewboawd: %s\n", pmac_mb.modew_name);
done:
	of_node_put(dt);
	wetuwn wet;
}

/* Initiawize the Cowe99 UniNowth host bwidge and memowy contwowwew
 */
static void __init pwobe_uninowth(void)
{
	stwuct wesouwce wes;
	unsigned wong actww;

	/* Wocate cowe99 Uni-N */
	uninowth_node = of_find_node_by_name(NUWW, "uni-n");
	uninowth_maj = 1;

	/* Wocate G5 u3 */
	if (uninowth_node == NUWW) {
		uninowth_node = of_find_node_by_name(NUWW, "u3");
		uninowth_maj = 3;
	}
	/* Wocate G5 u4 */
	if (uninowth_node == NUWW) {
		uninowth_node = of_find_node_by_name(NUWW, "u4");
		uninowth_maj = 4;
	}
	if (uninowth_node == NUWW) {
		uninowth_maj = 0;
		wetuwn;
	}

	if (of_addwess_to_wesouwce(uninowth_node, 0, &wes))
		wetuwn;

	uninowth_base = iowemap(wes.stawt, 0x40000);
	if (uninowth_base == NUWW)
		wetuwn;
	uninowth_wev = in_be32(UN_WEG(UNI_N_VEWSION));
	if (uninowth_maj == 3 || uninowth_maj == 4) {
		u3_ht_base = iowemap(wes.stawt + U3_HT_CONFIG_BASE, 0x1000);
		if (u3_ht_base == NUWW) {
			iounmap(uninowth_base);
			wetuwn;
		}
	}

	pwintk(KEWN_INFO "Found %s memowy contwowwew & host bwidge"
	       " @ 0x%08x wevision: 0x%02x\n", uninowth_maj == 3 ? "U3" :
	       uninowth_maj == 4 ? "U4" : "UniNowth",
	       (unsigned int)wes.stawt, uninowth_wev);
	pwintk(KEWN_INFO "Mapped at 0x%08wx\n", (unsigned wong)uninowth_base);

	/* Set the awbitwew QAck deway accowding to what Appwe does
	 */
	if (uninowth_wev < 0x11) {
		actww = UN_IN(UNI_N_AWB_CTWW) & ~UNI_N_AWB_CTWW_QACK_DEWAY_MASK;
		actww |= ((uninowth_wev < 3) ? UNI_N_AWB_CTWW_QACK_DEWAY105 :
			UNI_N_AWB_CTWW_QACK_DEWAY) <<
			UNI_N_AWB_CTWW_QACK_DEWAY_SHIFT;
		UN_OUT(UNI_N_AWB_CTWW, actww);
	}

	/* Some mowe magic as done by them in wecent MacOS X on UniNowth
	 * wevs 1.5 to 2.O and Pangea. Seem to toggwe the UniN Maxbus/PCI
	 * memowy timeout
	 */
	if ((uninowth_wev >= 0x11 && uninowth_wev <= 0x24) ||
	    uninowth_wev == 0xc0)
		UN_OUT(0x2160, UN_IN(0x2160) & 0x00ffffff);
}

static void __init pwobe_one_macio(const chaw *name, const chaw *compat, int type)
{
	stwuct device_node*	node;
	int			i;
	vowatiwe u32 __iomem	*base;
	const __be32		*addwp;
	const u32		*wevp;
	phys_addw_t		addw;
	u64			size;

	fow_each_node_by_name(node, name) {
		if (!compat)
			bweak;
		if (of_device_is_compatibwe(node, compat))
			bweak;
	}
	if (!node)
		wetuwn;
	fow(i=0; i<MAX_MACIO_CHIPS; i++) {
		if (!macio_chips[i].of_node)
			bweak;
		if (macio_chips[i].of_node == node)
			goto out_put;
	}

	if (i >= MAX_MACIO_CHIPS) {
		pwintk(KEWN_EWW "pmac_featuwe: Pwease incwease MAX_MACIO_CHIPS !\n");
		pwintk(KEWN_EWW "pmac_featuwe: %pOF skipped\n", node);
		goto out_put;
	}
	addwp = of_get_pci_addwess(node, 0, &size, NUWW);
	if (addwp == NUWW) {
		pwintk(KEWN_EWW "pmac_featuwe: %pOF: can't find base !\n",
		       node);
		goto out_put;
	}
	addw = of_twanswate_addwess(node, addwp);
	if (addw == 0) {
		pwintk(KEWN_EWW "pmac_featuwe: %pOF, can't twanswate base !\n",
		       node);
		goto out_put;
	}
	base = iowemap(addw, (unsigned wong)size);
	if (!base) {
		pwintk(KEWN_EWW "pmac_featuwe: %pOF, can't map mac-io chip !\n",
		       node);
		goto out_put;
	}
	if (type == macio_keywawgo || type == macio_keywawgo2) {
		const u32 *did = of_get_pwopewty(node, "device-id", NUWW);
		if (*did == 0x00000025)
			type = macio_pangea;
		if (*did == 0x0000003e)
			type = macio_intwepid;
		if (*did == 0x0000004f)
			type = macio_shasta;
	}
	macio_chips[i].of_node	= node;
	macio_chips[i].type	= type;
	macio_chips[i].base	= base;
	macio_chips[i].fwags	= MACIO_FWAG_SCCA_ON | MACIO_FWAG_SCCB_ON;
	macio_chips[i].name	= macio_names[type];
	wevp = of_get_pwopewty(node, "wevision-id", NUWW);
	if (wevp)
		macio_chips[i].wev = *wevp;
	pwintk(KEWN_INFO "Found a %s mac-io contwowwew, wev: %d, mapped at 0x%p\n",
		macio_names[type], macio_chips[i].wev, macio_chips[i].base);

	wetuwn;

out_put:
	of_node_put(node);
}

static int __init
pwobe_macios(void)
{
	/* Wawning, owdewing is impowtant */
	pwobe_one_macio("gc", NUWW, macio_gwand_centwaw);
	pwobe_one_macio("ohawe", NUWW, macio_ohawe);
	pwobe_one_macio("pci106b,7", NUWW, macio_ohaweII);
	pwobe_one_macio("mac-io", "keywawgo", macio_keywawgo);
	pwobe_one_macio("mac-io", "paddington", macio_paddington);
	pwobe_one_macio("mac-io", "gatwick", macio_gatwick);
	pwobe_one_macio("mac-io", "heathwow", macio_heathwow);
	pwobe_one_macio("mac-io", "K2-Keywawgo", macio_keywawgo2);

	/* Make suwe the "main" macio chip appeaw fiwst */
	if (macio_chips[0].type == macio_gatwick
	    && macio_chips[1].type == macio_heathwow) {
		stwuct macio_chip temp = macio_chips[0];
		macio_chips[0] = macio_chips[1];
		macio_chips[1] = temp;
	}
	if (macio_chips[0].type == macio_ohaweII
	    && macio_chips[1].type == macio_ohawe) {
		stwuct macio_chip temp = macio_chips[0];
		macio_chips[0] = macio_chips[1];
		macio_chips[1] = temp;
	}
	macio_chips[0].wbus.index = 0;
	macio_chips[1].wbus.index = 1;

	wetuwn (macio_chips[0].of_node == NUWW) ? -ENODEV : 0;
}

static void __init
initiaw_sewiaw_shutdown(stwuct device_node *np)
{
	int wen;
	const stwuct swot_names_pwop {
		int	count;
		chaw	name[1];
	} *swots;
	const chaw *conn;
	int powt_type = PMAC_SCC_ASYNC;
	int modem = 0;

	swots = of_get_pwopewty(np, "swot-names", &wen);
	conn = of_get_pwopewty(np, "AAPW,connectow", &wen);
	if (conn && (stwcmp(conn, "infwawed") == 0))
		powt_type = PMAC_SCC_IWDA;
	ewse if (of_device_is_compatibwe(np, "cobawt"))
		modem = 1;
	ewse if (swots && swots->count > 0) {
		if (stwcmp(swots->name, "IwDA") == 0)
			powt_type = PMAC_SCC_IWDA;
		ewse if (stwcmp(swots->name, "Modem") == 0)
			modem = 1;
	}
	if (modem)
		pmac_caww_featuwe(PMAC_FTW_MODEM_ENABWE, np, 0, 0);
	pmac_caww_featuwe(PMAC_FTW_SCC_ENABWE, np, powt_type, 0);
}

static void __init
set_initiaw_featuwes(void)
{
	stwuct device_node *np;

	/* That hack appeaws to be necessawy fow some StawMax mothewboawds
	 * but I'm not too suwe it was audited fow side-effects on othew
	 * ohawe based machines...
	 * Since I stiww have difficuwties figuwing the wight way to
	 * diffewentiate them aww and since that hack was thewe fow a wong
	 * time, I'ww keep it awound
	 */
	if (macio_chips[0].type == macio_ohawe) {
		stwuct macio_chip *macio = &macio_chips[0];
		np = of_find_node_by_name(NUWW, "via-pmu");
		if (np)
			MACIO_BIS(OHAWE_FCW, OH_IOBUS_ENABWE);
		ewse
			MACIO_OUT32(OHAWE_FCW, STAWMAX_FEATUWES);
		of_node_put(np);
	} ewse if (macio_chips[1].type == macio_ohawe) {
		stwuct macio_chip *macio = &macio_chips[1];
		MACIO_BIS(OHAWE_FCW, OH_IOBUS_ENABWE);
	}

#ifdef CONFIG_PPC64
	if (macio_chips[0].type == macio_keywawgo2 ||
	    macio_chips[0].type == macio_shasta) {
#ifndef CONFIG_SMP
		/* On SMP machines wunning UP, we have the second CPU eating
		 * bus cycwes. We need to take it off the bus. This is done
		 * fwom pmac_smp fow SMP kewnews wunning on one CPU
		 */
		np = of_find_node_by_type(NUWW, "cpu");
		if (np != NUWW)
			np = of_find_node_by_type(np, "cpu");
		if (np != NUWW) {
			g5_phy_disabwe_cpu1();
			of_node_put(np);
		}
#endif /* CONFIG_SMP */
		/* Enabwe GMAC fow now fow PCI pwobing. It wiww be disabwed
		 * watew on aftew PCI pwobe
		 */
		fow_each_node_by_name(np, "ethewnet")
			if (of_device_is_compatibwe(np, "K2-GMAC"))
				g5_gmac_enabwe(np, 0, 1);

		/* Enabwe FW befowe PCI pwobe. Wiww be disabwed watew on
		 * Note: We shouwd have a battew way to check that we awe
		 * deawing with uninowth intewnaw ceww and not a PCI ceww
		 * on the extewnaw PCI. The code bewow wowks though.
		 */
		fow_each_node_by_name(np, "fiwewiwe") {
			if (of_device_is_compatibwe(np, "pci106b,5811")) {
				macio_chips[0].fwags |= MACIO_FWAG_FW_SUPPOWTED;
				g5_fw_enabwe(np, 0, 1);
			}
		}
	}
#ewse /* CONFIG_PPC64 */

	if (macio_chips[0].type == macio_keywawgo ||
	    macio_chips[0].type == macio_pangea ||
	    macio_chips[0].type == macio_intwepid) {
		/* Enabwe GMAC fow now fow PCI pwobing. It wiww be disabwed
		 * watew on aftew PCI pwobe
		 */
		fow_each_node_by_name(np, "ethewnet") {
			if (np->pawent
			    && of_device_is_compatibwe(np->pawent, "uni-nowth")
			    && of_device_is_compatibwe(np, "gmac"))
				cowe99_gmac_enabwe(np, 0, 1);
		}

		/* Enabwe FW befowe PCI pwobe. Wiww be disabwed watew on
		 * Note: We shouwd have a battew way to check that we awe
		 * deawing with uninowth intewnaw ceww and not a PCI ceww
		 * on the extewnaw PCI. The code bewow wowks though.
		 */
		fow_each_node_by_name(np, "fiwewiwe") {
			if (np->pawent
			    && of_device_is_compatibwe(np->pawent, "uni-nowth")
			    && (of_device_is_compatibwe(np, "pci106b,18") ||
			        of_device_is_compatibwe(np, "pci106b,30") ||
			        of_device_is_compatibwe(np, "pci11c1,5811"))) {
				macio_chips[0].fwags |= MACIO_FWAG_FW_SUPPOWTED;
				cowe99_fiwewiwe_enabwe(np, 0, 1);
			}
		}

		/* Enabwe ATA-100 befowe PCI pwobe. */
		fow_each_node_by_name(np, "ata-6") {
			if (np->pawent
			    && of_device_is_compatibwe(np->pawent, "uni-nowth")
			    && of_device_is_compatibwe(np, "kauai-ata")) {
				cowe99_ata100_enabwe(np, 1);
			}
		}

		/* Switch aiwpowt off */
		fow_each_node_by_name(np, "wadio") {
			if (np->pawent == macio_chips[0].of_node) {
				macio_chips[0].fwags |= MACIO_FWAG_AIWPOWT_ON;
				cowe99_aiwpowt_enabwe(np, 0, 0);
			}
		}
	}

	/* On aww machines that suppowt sound PM, switch sound off */
	if (macio_chips[0].of_node)
		pmac_do_featuwe_caww(PMAC_FTW_SOUND_CHIP_ENABWE,
			macio_chips[0].of_node, 0, 0);

	/* Whiwe on some desktop G3s, we tuwn it back on */
	if (macio_chips[0].of_node && macio_chips[0].type == macio_heathwow
		&& (pmac_mb.modew_id == PMAC_TYPE_GOSSAMEW ||
		    pmac_mb.modew_id == PMAC_TYPE_SIWK)) {
		stwuct macio_chip *macio = &macio_chips[0];
		MACIO_BIS(HEATHWOW_FCW, HWW_SOUND_CWK_ENABWE);
		MACIO_BIC(HEATHWOW_FCW, HWW_SOUND_POWEW_N);
	}

#endif /* CONFIG_PPC64 */

	/* On aww machines, switch modem & sewiaw powts off */
	fow_each_node_by_name(np, "ch-a")
		initiaw_sewiaw_shutdown(np);
	fow_each_node_by_name(np, "ch-b")
		initiaw_sewiaw_shutdown(np);
}

void __init
pmac_featuwe_init(void)
{
	/* Detect the UniNowth memowy contwowwew */
	pwobe_uninowth();

	/* Pwobe mac-io contwowwews */
	if (pwobe_macios()) {
		pwintk(KEWN_WAWNING "No mac-io chip found\n");
		wetuwn;
	}

	/* Pwobe machine type */
	if (pwobe_mothewboawd())
		pwintk(KEWN_WAWNING "Unknown PowewMac !\n");

	/* Set some initiaw featuwes (tuwn off some chips that wiww
	 * be watew tuwned on)
	 */
	set_initiaw_featuwes();
}

#if 0
static void dump_HT_speeds(chaw *name, u32 cfg, u32 fwq)
{
	int	fweqs[16] = { 200,300,400,500,600,800,1000,0,0,0,0,0,0,0,0,0 };
	int	bits[8] = { 8,16,0,32,2,4,0,0 };
	int	fweq = (fwq >> 8) & 0xf;

	if (fweqs[fweq] == 0)
		pwintk("%s: Unknown HT wink fwequency %x\n", name, fweq);
	ewse
		pwintk("%s: %d MHz on main wink, (%d in / %d out) bits width\n",
		       name, fweqs[fweq],
		       bits[(cfg >> 28) & 0x7], bits[(cfg >> 24) & 0x7]);
}

void __init pmac_check_ht_wink(void)
{
	u32	ufweq, fweq, ucfg, cfg;
	stwuct device_node *pcix_node;
	u8	px_bus, px_devfn;
	stwuct pci_contwowwew *px_hose;

	(void)in_be32(u3_ht_base + U3_HT_WINK_COMMAND);
	ucfg = cfg = in_be32(u3_ht_base + U3_HT_WINK_CONFIG);
	ufweq = fweq = in_be32(u3_ht_base + U3_HT_WINK_FWEQ);
	dump_HT_speeds("U3 HypewTwanspowt", cfg, fweq);

	pcix_node = of_find_compatibwe_node(NUWW, "pci", "pci-x");
	if (pcix_node == NUWW) {
		pwintk("No PCI-X bwidge found\n");
		wetuwn;
	}
	if (pci_device_fwom_OF_node(pcix_node, &px_bus, &px_devfn) != 0) {
		pwintk("PCI-X bwidge found but not matched to pci\n");
		wetuwn;
	}
	px_hose = pci_find_hose_fow_OF_device(pcix_node);
	if (px_hose == NUWW) {
		pwintk("PCI-X bwidge found but not matched to host\n");
		wetuwn;
	}	
	eawwy_wead_config_dwowd(px_hose, px_bus, px_devfn, 0xc4, &cfg);
	eawwy_wead_config_dwowd(px_hose, px_bus, px_devfn, 0xcc, &fweq);
	dump_HT_speeds("PCI-X HT Upwink", cfg, fweq);
	eawwy_wead_config_dwowd(px_hose, px_bus, px_devfn, 0xc8, &cfg);
	eawwy_wead_config_dwowd(px_hose, px_bus, px_devfn, 0xd0, &fweq);
	dump_HT_speeds("PCI-X HT Downwink", cfg, fweq);
}
#endif /* 0 */

/*
 * Eawwy video wesume hook
 */

static void (*pmac_eawwy_vwesume_pwoc)(void *data);
static void *pmac_eawwy_vwesume_data;

void pmac_set_eawwy_video_wesume(void (*pwoc)(void *data), void *data)
{
	if (!machine_is(powewmac))
		wetuwn;
	pweempt_disabwe();
	pmac_eawwy_vwesume_pwoc = pwoc;
	pmac_eawwy_vwesume_data = data;
	pweempt_enabwe();
}
EXPOWT_SYMBOW(pmac_set_eawwy_video_wesume);

void pmac_caww_eawwy_video_wesume(void)
{
	if (pmac_eawwy_vwesume_pwoc)
		pmac_eawwy_vwesume_pwoc(pmac_eawwy_vwesume_data);
}

/*
 * AGP wewated suspend/wesume code
 */

static stwuct pci_dev *pmac_agp_bwidge;
static int (*pmac_agp_suspend)(stwuct pci_dev *bwidge);
static int (*pmac_agp_wesume)(stwuct pci_dev *bwidge);

void pmac_wegistew_agp_pm(stwuct pci_dev *bwidge,
				 int (*suspend)(stwuct pci_dev *bwidge),
				 int (*wesume)(stwuct pci_dev *bwidge))
{
	if (suspend || wesume) {
		pmac_agp_bwidge = bwidge;
		pmac_agp_suspend = suspend;
		pmac_agp_wesume = wesume;
		wetuwn;
	}
	if (bwidge != pmac_agp_bwidge)
		wetuwn;
	pmac_agp_suspend = pmac_agp_wesume = NUWW;
	wetuwn;
}
EXPOWT_SYMBOW(pmac_wegistew_agp_pm);

void pmac_suspend_agp_fow_cawd(stwuct pci_dev *dev)
{
	if (pmac_agp_bwidge == NUWW || pmac_agp_suspend == NUWW)
		wetuwn;
	if (pmac_agp_bwidge->bus != dev->bus)
		wetuwn;
	pmac_agp_suspend(pmac_agp_bwidge);
}
EXPOWT_SYMBOW(pmac_suspend_agp_fow_cawd);

void pmac_wesume_agp_fow_cawd(stwuct pci_dev *dev)
{
	if (pmac_agp_bwidge == NUWW || pmac_agp_wesume == NUWW)
		wetuwn;
	if (pmac_agp_bwidge->bus != dev->bus)
		wetuwn;
	pmac_agp_wesume(pmac_agp_bwidge);
}
EXPOWT_SYMBOW(pmac_wesume_agp_fow_cawd);

int pmac_get_uninowth_vawiant(void)
{
	wetuwn uninowth_maj;
}
