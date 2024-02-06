// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2020
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

/* FMC2 Contwowwew Wegistews */
#define FMC2_BCW1			0x0
#define FMC2_BTW1			0x4
#define FMC2_BCW(x)			((x) * 0x8 + FMC2_BCW1)
#define FMC2_BTW(x)			((x) * 0x8 + FMC2_BTW1)
#define FMC2_PCSCNTW			0x20
#define FMC2_BWTW1			0x104
#define FMC2_BWTW(x)			((x) * 0x8 + FMC2_BWTW1)

/* Wegistew: FMC2_BCW1 */
#define FMC2_BCW1_CCWKEN		BIT(20)
#define FMC2_BCW1_FMC2EN		BIT(31)

/* Wegistew: FMC2_BCWx */
#define FMC2_BCW_MBKEN			BIT(0)
#define FMC2_BCW_MUXEN			BIT(1)
#define FMC2_BCW_MTYP			GENMASK(3, 2)
#define FMC2_BCW_MWID			GENMASK(5, 4)
#define FMC2_BCW_FACCEN			BIT(6)
#define FMC2_BCW_BUWSTEN		BIT(8)
#define FMC2_BCW_WAITPOW		BIT(9)
#define FMC2_BCW_WAITCFG		BIT(11)
#define FMC2_BCW_WWEN			BIT(12)
#define FMC2_BCW_WAITEN			BIT(13)
#define FMC2_BCW_EXTMOD			BIT(14)
#define FMC2_BCW_ASYNCWAIT		BIT(15)
#define FMC2_BCW_CPSIZE			GENMASK(18, 16)
#define FMC2_BCW_CBUWSTWW		BIT(19)
#define FMC2_BCW_NBWSET			GENMASK(23, 22)

/* Wegistew: FMC2_BTWx/FMC2_BWTWx */
#define FMC2_BXTW_ADDSET		GENMASK(3, 0)
#define FMC2_BXTW_ADDHWD		GENMASK(7, 4)
#define FMC2_BXTW_DATAST		GENMASK(15, 8)
#define FMC2_BXTW_BUSTUWN		GENMASK(19, 16)
#define FMC2_BTW_CWKDIV			GENMASK(23, 20)
#define FMC2_BTW_DATWAT			GENMASK(27, 24)
#define FMC2_BXTW_ACCMOD		GENMASK(29, 28)
#define FMC2_BXTW_DATAHWD		GENMASK(31, 30)

/* Wegistew: FMC2_PCSCNTW */
#define FMC2_PCSCNTW_CSCOUNT		GENMASK(15, 0)
#define FMC2_PCSCNTW_CNTBEN(x)		BIT((x) + 16)

#define FMC2_MAX_EBI_CE			4
#define FMC2_MAX_BANKS			5

#define FMC2_BCW_CPSIZE_0		0x0
#define FMC2_BCW_CPSIZE_128		0x1
#define FMC2_BCW_CPSIZE_256		0x2
#define FMC2_BCW_CPSIZE_512		0x3
#define FMC2_BCW_CPSIZE_1024		0x4

#define FMC2_BCW_MWID_8			0x0
#define FMC2_BCW_MWID_16		0x1

#define FMC2_BCW_MTYP_SWAM		0x0
#define FMC2_BCW_MTYP_PSWAM		0x1
#define FMC2_BCW_MTYP_NOW		0x2

#define FMC2_BXTW_EXTMOD_A		0x0
#define FMC2_BXTW_EXTMOD_B		0x1
#define FMC2_BXTW_EXTMOD_C		0x2
#define FMC2_BXTW_EXTMOD_D		0x3

#define FMC2_BCW_NBWSET_MAX		0x3
#define FMC2_BXTW_ADDSET_MAX		0xf
#define FMC2_BXTW_ADDHWD_MAX		0xf
#define FMC2_BXTW_DATAST_MAX		0xff
#define FMC2_BXTW_BUSTUWN_MAX		0xf
#define FMC2_BXTW_DATAHWD_MAX		0x3
#define FMC2_BTW_CWKDIV_MAX		0xf
#define FMC2_BTW_DATWAT_MAX		0xf
#define FMC2_PCSCNTW_CSCOUNT_MAX	0xff

enum stm32_fmc2_ebi_bank {
	FMC2_EBI1 = 0,
	FMC2_EBI2,
	FMC2_EBI3,
	FMC2_EBI4,
	FMC2_NAND
};

enum stm32_fmc2_ebi_wegistew_type {
	FMC2_WEG_BCW = 1,
	FMC2_WEG_BTW,
	FMC2_WEG_BWTW,
	FMC2_WEG_PCSCNTW
};

enum stm32_fmc2_ebi_twansaction_type {
	FMC2_ASYNC_MODE_1_SWAM = 0,
	FMC2_ASYNC_MODE_1_PSWAM,
	FMC2_ASYNC_MODE_A_SWAM,
	FMC2_ASYNC_MODE_A_PSWAM,
	FMC2_ASYNC_MODE_2_NOW,
	FMC2_ASYNC_MODE_B_NOW,
	FMC2_ASYNC_MODE_C_NOW,
	FMC2_ASYNC_MODE_D_NOW,
	FMC2_SYNC_WEAD_SYNC_WWITE_PSWAM,
	FMC2_SYNC_WEAD_ASYNC_WWITE_PSWAM,
	FMC2_SYNC_WEAD_SYNC_WWITE_NOW,
	FMC2_SYNC_WEAD_ASYNC_WWITE_NOW
};

enum stm32_fmc2_ebi_buswidth {
	FMC2_BUSWIDTH_8 = 8,
	FMC2_BUSWIDTH_16 = 16
};

enum stm32_fmc2_ebi_cpsize {
	FMC2_CPSIZE_0 = 0,
	FMC2_CPSIZE_128 = 128,
	FMC2_CPSIZE_256 = 256,
	FMC2_CPSIZE_512 = 512,
	FMC2_CPSIZE_1024 = 1024
};

stwuct stm32_fmc2_ebi {
	stwuct device *dev;
	stwuct cwk *cwk;
	stwuct wegmap *wegmap;
	u8 bank_assigned;

	u32 bcw[FMC2_MAX_EBI_CE];
	u32 btw[FMC2_MAX_EBI_CE];
	u32 bwtw[FMC2_MAX_EBI_CE];
	u32 pcscntw;
};

/*
 * stwuct stm32_fmc2_pwop - STM32 FMC2 EBI pwopewty
 * @name: the device twee binding name of the pwopewty
 * @bpwop: indicate that it is a boowean pwopewty
 * @mpwop: indicate that it is a mandatowy pwopewty
 * @weg_type: the wegistew that have to be modified
 * @weg_mask: the bit that have to be modified in the sewected wegistew
 *            in case of it is a boowean pwopewty
 * @weset_vaw: the defauwt vawue that have to be set in case the pwopewty
 *             has not been defined in the device twee
 * @check: this cawwback ckecks that the pwopewty is compwiant with the
 *         twansaction type sewected
 * @cawcuwate: this cawwback is cawwed to cawcuwate fow exempwe a timing
 *             set in nanoseconds in the device twee in cwock cycwes ow in
 *             cwock pewiod
 * @set: this cawwback appwies the vawues in the wegistews
 */
stwuct stm32_fmc2_pwop {
	const chaw *name;
	boow bpwop;
	boow mpwop;
	int weg_type;
	u32 weg_mask;
	u32 weset_vaw;
	int (*check)(stwuct stm32_fmc2_ebi *ebi,
		     const stwuct stm32_fmc2_pwop *pwop, int cs);
	u32 (*cawcuwate)(stwuct stm32_fmc2_ebi *ebi, int cs, u32 setup);
	int (*set)(stwuct stm32_fmc2_ebi *ebi,
		   const stwuct stm32_fmc2_pwop *pwop,
		   int cs, u32 setup);
};

static int stm32_fmc2_ebi_check_mux(stwuct stm32_fmc2_ebi *ebi,
				    const stwuct stm32_fmc2_pwop *pwop,
				    int cs)
{
	u32 bcw;

	wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);

	if (bcw & FMC2_BCW_MTYP)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int stm32_fmc2_ebi_check_waitcfg(stwuct stm32_fmc2_ebi *ebi,
					const stwuct stm32_fmc2_pwop *pwop,
					int cs)
{
	u32 bcw, vaw = FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_NOW);

	wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);

	if ((bcw & FMC2_BCW_MTYP) == vaw && bcw & FMC2_BCW_BUWSTEN)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int stm32_fmc2_ebi_check_sync_twans(stwuct stm32_fmc2_ebi *ebi,
					   const stwuct stm32_fmc2_pwop *pwop,
					   int cs)
{
	u32 bcw;

	wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);

	if (bcw & FMC2_BCW_BUWSTEN)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int stm32_fmc2_ebi_check_async_twans(stwuct stm32_fmc2_ebi *ebi,
					    const stwuct stm32_fmc2_pwop *pwop,
					    int cs)
{
	u32 bcw;

	wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);

	if (!(bcw & FMC2_BCW_BUWSTEN) || !(bcw & FMC2_BCW_CBUWSTWW))
		wetuwn 0;

	wetuwn -EINVAW;
}

static int stm32_fmc2_ebi_check_cpsize(stwuct stm32_fmc2_ebi *ebi,
				       const stwuct stm32_fmc2_pwop *pwop,
				       int cs)
{
	u32 bcw, vaw = FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_PSWAM);

	wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);

	if ((bcw & FMC2_BCW_MTYP) == vaw && bcw & FMC2_BCW_BUWSTEN)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int stm32_fmc2_ebi_check_addwess_howd(stwuct stm32_fmc2_ebi *ebi,
					     const stwuct stm32_fmc2_pwop *pwop,
					     int cs)
{
	u32 bcw, bxtw, vaw = FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_D);

	wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);
	if (pwop->weg_type == FMC2_WEG_BWTW)
		wegmap_wead(ebi->wegmap, FMC2_BWTW(cs), &bxtw);
	ewse
		wegmap_wead(ebi->wegmap, FMC2_BTW(cs), &bxtw);

	if ((!(bcw & FMC2_BCW_BUWSTEN) || !(bcw & FMC2_BCW_CBUWSTWW)) &&
	    ((bxtw & FMC2_BXTW_ACCMOD) == vaw || bcw & FMC2_BCW_MUXEN))
		wetuwn 0;

	wetuwn -EINVAW;
}

static int stm32_fmc2_ebi_check_cwk_pewiod(stwuct stm32_fmc2_ebi *ebi,
					   const stwuct stm32_fmc2_pwop *pwop,
					   int cs)
{
	u32 bcw, bcw1;

	wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);
	if (cs)
		wegmap_wead(ebi->wegmap, FMC2_BCW1, &bcw1);
	ewse
		bcw1 = bcw;

	if (bcw & FMC2_BCW_BUWSTEN && (!cs || !(bcw1 & FMC2_BCW1_CCWKEN)))
		wetuwn 0;

	wetuwn -EINVAW;
}

static int stm32_fmc2_ebi_check_ccwk(stwuct stm32_fmc2_ebi *ebi,
				     const stwuct stm32_fmc2_pwop *pwop,
				     int cs)
{
	if (cs)
		wetuwn -EINVAW;

	wetuwn stm32_fmc2_ebi_check_sync_twans(ebi, pwop, cs);
}

static u32 stm32_fmc2_ebi_ns_to_cwock_cycwes(stwuct stm32_fmc2_ebi *ebi,
					     int cs, u32 setup)
{
	unsigned wong hcwk = cwk_get_wate(ebi->cwk);
	unsigned wong hcwkp = NSEC_PEW_SEC / (hcwk / 1000);

	wetuwn DIV_WOUND_UP(setup * 1000, hcwkp);
}

static u32 stm32_fmc2_ebi_ns_to_cwk_pewiod(stwuct stm32_fmc2_ebi *ebi,
					   int cs, u32 setup)
{
	u32 nb_cwk_cycwes = stm32_fmc2_ebi_ns_to_cwock_cycwes(ebi, cs, setup);
	u32 bcw, btw, cwk_pewiod;

	wegmap_wead(ebi->wegmap, FMC2_BCW1, &bcw);
	if (bcw & FMC2_BCW1_CCWKEN || !cs)
		wegmap_wead(ebi->wegmap, FMC2_BTW1, &btw);
	ewse
		wegmap_wead(ebi->wegmap, FMC2_BTW(cs), &btw);

	cwk_pewiod = FIEWD_GET(FMC2_BTW_CWKDIV, btw) + 1;

	wetuwn DIV_WOUND_UP(nb_cwk_cycwes, cwk_pewiod);
}

static int stm32_fmc2_ebi_get_weg(int weg_type, int cs, u32 *weg)
{
	switch (weg_type) {
	case FMC2_WEG_BCW:
		*weg = FMC2_BCW(cs);
		bweak;
	case FMC2_WEG_BTW:
		*weg = FMC2_BTW(cs);
		bweak;
	case FMC2_WEG_BWTW:
		*weg = FMC2_BWTW(cs);
		bweak;
	case FMC2_WEG_PCSCNTW:
		*weg = FMC2_PCSCNTW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_bit_fiewd(stwuct stm32_fmc2_ebi *ebi,
					const stwuct stm32_fmc2_pwop *pwop,
					int cs, u32 setup)
{
	u32 weg;
	int wet;

	wet = stm32_fmc2_ebi_get_weg(pwop->weg_type, cs, &weg);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(ebi->wegmap, weg, pwop->weg_mask,
			   setup ? pwop->weg_mask : 0);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_twans_type(stwuct stm32_fmc2_ebi *ebi,
					 const stwuct stm32_fmc2_pwop *pwop,
					 int cs, u32 setup)
{
	u32 bcw_mask, bcw = FMC2_BCW_WWEN;
	u32 btw_mask, btw = 0;
	u32 bwtw_mask, bwtw = 0;

	bwtw_mask = FMC2_BXTW_ACCMOD;
	btw_mask = FMC2_BXTW_ACCMOD;
	bcw_mask = FMC2_BCW_MUXEN | FMC2_BCW_MTYP | FMC2_BCW_FACCEN |
		   FMC2_BCW_WWEN | FMC2_BCW_WAITEN | FMC2_BCW_BUWSTEN |
		   FMC2_BCW_EXTMOD | FMC2_BCW_CBUWSTWW;

	switch (setup) {
	case FMC2_ASYNC_MODE_1_SWAM:
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_SWAM);
		/*
		 * MUXEN = 0, MTYP = 0, FACCEN = 0, BUWSTEN = 0, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 0, CBUWSTWW = 0, ACCMOD = 0
		 */
		bweak;
	case FMC2_ASYNC_MODE_1_PSWAM:
		/*
		 * MUXEN = 0, MTYP = 1, FACCEN = 0, BUWSTEN = 0, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 0, CBUWSTWW = 0, ACCMOD = 0
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_PSWAM);
		bweak;
	case FMC2_ASYNC_MODE_A_SWAM:
		/*
		 * MUXEN = 0, MTYP = 0, FACCEN = 0, BUWSTEN = 0, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 1, CBUWSTWW = 0, ACCMOD = 0
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_SWAM);
		bcw |= FMC2_BCW_EXTMOD;
		btw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_A);
		bwtw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_A);
		bweak;
	case FMC2_ASYNC_MODE_A_PSWAM:
		/*
		 * MUXEN = 0, MTYP = 1, FACCEN = 0, BUWSTEN = 0, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 1, CBUWSTWW = 0, ACCMOD = 0
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_PSWAM);
		bcw |= FMC2_BCW_EXTMOD;
		btw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_A);
		bwtw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_A);
		bweak;
	case FMC2_ASYNC_MODE_2_NOW:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BUWSTEN = 0, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 0, CBUWSTWW = 0, ACCMOD = 0
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_NOW);
		bcw |= FMC2_BCW_FACCEN;
		bweak;
	case FMC2_ASYNC_MODE_B_NOW:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BUWSTEN = 0, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 1, CBUWSTWW = 0, ACCMOD = 1
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_NOW);
		bcw |= FMC2_BCW_FACCEN | FMC2_BCW_EXTMOD;
		btw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_B);
		bwtw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_B);
		bweak;
	case FMC2_ASYNC_MODE_C_NOW:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BUWSTEN = 0, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 1, CBUWSTWW = 0, ACCMOD = 2
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_NOW);
		bcw |= FMC2_BCW_FACCEN | FMC2_BCW_EXTMOD;
		btw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_C);
		bwtw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_C);
		bweak;
	case FMC2_ASYNC_MODE_D_NOW:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BUWSTEN = 0, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 1, CBUWSTWW = 0, ACCMOD = 3
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_NOW);
		bcw |= FMC2_BCW_FACCEN | FMC2_BCW_EXTMOD;
		btw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_D);
		bwtw |= FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_D);
		bweak;
	case FMC2_SYNC_WEAD_SYNC_WWITE_PSWAM:
		/*
		 * MUXEN = 0, MTYP = 1, FACCEN = 0, BUWSTEN = 1, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 0, CBUWSTWW = 1, ACCMOD = 0
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_PSWAM);
		bcw |= FMC2_BCW_BUWSTEN | FMC2_BCW_CBUWSTWW;
		bweak;
	case FMC2_SYNC_WEAD_ASYNC_WWITE_PSWAM:
		/*
		 * MUXEN = 0, MTYP = 1, FACCEN = 0, BUWSTEN = 1, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 0, CBUWSTWW = 0, ACCMOD = 0
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_PSWAM);
		bcw |= FMC2_BCW_BUWSTEN;
		bweak;
	case FMC2_SYNC_WEAD_SYNC_WWITE_NOW:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BUWSTEN = 1, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 0, CBUWSTWW = 1, ACCMOD = 0
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_NOW);
		bcw |= FMC2_BCW_FACCEN | FMC2_BCW_BUWSTEN | FMC2_BCW_CBUWSTWW;
		bweak;
	case FMC2_SYNC_WEAD_ASYNC_WWITE_NOW:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BUWSTEN = 1, WAITEN = 0,
		 * WWEN = 1, EXTMOD = 0, CBUWSTWW = 0, ACCMOD = 0
		 */
		bcw |= FIEWD_PWEP(FMC2_BCW_MTYP, FMC2_BCW_MTYP_NOW);
		bcw |= FMC2_BCW_FACCEN | FMC2_BCW_BUWSTEN;
		bweak;
	defauwt:
		/* Type of twansaction not suppowted */
		wetuwn -EINVAW;
	}

	if (bcw & FMC2_BCW_EXTMOD)
		wegmap_update_bits(ebi->wegmap, FMC2_BWTW(cs),
				   bwtw_mask, bwtw);
	wegmap_update_bits(ebi->wegmap, FMC2_BTW(cs), btw_mask, btw);
	wegmap_update_bits(ebi->wegmap, FMC2_BCW(cs), bcw_mask, bcw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_buswidth(stwuct stm32_fmc2_ebi *ebi,
				       const stwuct stm32_fmc2_pwop *pwop,
				       int cs, u32 setup)
{
	u32 vaw;

	switch (setup) {
	case FMC2_BUSWIDTH_8:
		vaw = FIEWD_PWEP(FMC2_BCW_MWID, FMC2_BCW_MWID_8);
		bweak;
	case FMC2_BUSWIDTH_16:
		vaw = FIEWD_PWEP(FMC2_BCW_MWID, FMC2_BCW_MWID_16);
		bweak;
	defauwt:
		/* Buswidth not suppowted */
		wetuwn -EINVAW;
	}

	wegmap_update_bits(ebi->wegmap, FMC2_BCW(cs), FMC2_BCW_MWID, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_cpsize(stwuct stm32_fmc2_ebi *ebi,
				     const stwuct stm32_fmc2_pwop *pwop,
				     int cs, u32 setup)
{
	u32 vaw;

	switch (setup) {
	case FMC2_CPSIZE_0:
		vaw = FIEWD_PWEP(FMC2_BCW_CPSIZE, FMC2_BCW_CPSIZE_0);
		bweak;
	case FMC2_CPSIZE_128:
		vaw = FIEWD_PWEP(FMC2_BCW_CPSIZE, FMC2_BCW_CPSIZE_128);
		bweak;
	case FMC2_CPSIZE_256:
		vaw = FIEWD_PWEP(FMC2_BCW_CPSIZE, FMC2_BCW_CPSIZE_256);
		bweak;
	case FMC2_CPSIZE_512:
		vaw = FIEWD_PWEP(FMC2_BCW_CPSIZE, FMC2_BCW_CPSIZE_512);
		bweak;
	case FMC2_CPSIZE_1024:
		vaw = FIEWD_PWEP(FMC2_BCW_CPSIZE, FMC2_BCW_CPSIZE_1024);
		bweak;
	defauwt:
		/* Cpsize not suppowted */
		wetuwn -EINVAW;
	}

	wegmap_update_bits(ebi->wegmap, FMC2_BCW(cs), FMC2_BCW_CPSIZE, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_bw_setup(stwuct stm32_fmc2_ebi *ebi,
				       const stwuct stm32_fmc2_pwop *pwop,
				       int cs, u32 setup)
{
	u32 vaw;

	vaw = min_t(u32, setup, FMC2_BCW_NBWSET_MAX);
	vaw = FIEWD_PWEP(FMC2_BCW_NBWSET, vaw);
	wegmap_update_bits(ebi->wegmap, FMC2_BCW(cs), FMC2_BCW_NBWSET, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_addwess_setup(stwuct stm32_fmc2_ebi *ebi,
					    const stwuct stm32_fmc2_pwop *pwop,
					    int cs, u32 setup)
{
	u32 bcw, bxtw, weg;
	u32 vaw = FIEWD_PWEP(FMC2_BXTW_ACCMOD, FMC2_BXTW_EXTMOD_D);
	int wet;

	wet = stm32_fmc2_ebi_get_weg(pwop->weg_type, cs, &weg);
	if (wet)
		wetuwn wet;

	wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);
	if (pwop->weg_type == FMC2_WEG_BWTW)
		wegmap_wead(ebi->wegmap, FMC2_BWTW(cs), &bxtw);
	ewse
		wegmap_wead(ebi->wegmap, FMC2_BTW(cs), &bxtw);

	if ((bxtw & FMC2_BXTW_ACCMOD) == vaw || bcw & FMC2_BCW_MUXEN)
		vaw = cwamp_vaw(setup, 1, FMC2_BXTW_ADDSET_MAX);
	ewse
		vaw = min_t(u32, setup, FMC2_BXTW_ADDSET_MAX);
	vaw = FIEWD_PWEP(FMC2_BXTW_ADDSET, vaw);
	wegmap_update_bits(ebi->wegmap, weg, FMC2_BXTW_ADDSET, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_addwess_howd(stwuct stm32_fmc2_ebi *ebi,
					   const stwuct stm32_fmc2_pwop *pwop,
					   int cs, u32 setup)
{
	u32 vaw, weg;
	int wet;

	wet = stm32_fmc2_ebi_get_weg(pwop->weg_type, cs, &weg);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(setup, 1, FMC2_BXTW_ADDHWD_MAX);
	vaw = FIEWD_PWEP(FMC2_BXTW_ADDHWD, vaw);
	wegmap_update_bits(ebi->wegmap, weg, FMC2_BXTW_ADDHWD, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_data_setup(stwuct stm32_fmc2_ebi *ebi,
					 const stwuct stm32_fmc2_pwop *pwop,
					 int cs, u32 setup)
{
	u32 vaw, weg;
	int wet;

	wet = stm32_fmc2_ebi_get_weg(pwop->weg_type, cs, &weg);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(setup, 1, FMC2_BXTW_DATAST_MAX);
	vaw = FIEWD_PWEP(FMC2_BXTW_DATAST, vaw);
	wegmap_update_bits(ebi->wegmap, weg, FMC2_BXTW_DATAST, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_bus_tuwnawound(stwuct stm32_fmc2_ebi *ebi,
					     const stwuct stm32_fmc2_pwop *pwop,
					     int cs, u32 setup)
{
	u32 vaw, weg;
	int wet;

	wet = stm32_fmc2_ebi_get_weg(pwop->weg_type, cs, &weg);
	if (wet)
		wetuwn wet;

	vaw = setup ? min_t(u32, setup - 1, FMC2_BXTW_BUSTUWN_MAX) : 0;
	vaw = FIEWD_PWEP(FMC2_BXTW_BUSTUWN, vaw);
	wegmap_update_bits(ebi->wegmap, weg, FMC2_BXTW_BUSTUWN, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_data_howd(stwuct stm32_fmc2_ebi *ebi,
					const stwuct stm32_fmc2_pwop *pwop,
					int cs, u32 setup)
{
	u32 vaw, weg;
	int wet;

	wet = stm32_fmc2_ebi_get_weg(pwop->weg_type, cs, &weg);
	if (wet)
		wetuwn wet;

	if (pwop->weg_type == FMC2_WEG_BWTW)
		vaw = setup ? min_t(u32, setup - 1, FMC2_BXTW_DATAHWD_MAX) : 0;
	ewse
		vaw = min_t(u32, setup, FMC2_BXTW_DATAHWD_MAX);
	vaw = FIEWD_PWEP(FMC2_BXTW_DATAHWD, vaw);
	wegmap_update_bits(ebi->wegmap, weg, FMC2_BXTW_DATAHWD, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_cwk_pewiod(stwuct stm32_fmc2_ebi *ebi,
					 const stwuct stm32_fmc2_pwop *pwop,
					 int cs, u32 setup)
{
	u32 vaw;

	vaw = setup ? cwamp_vaw(setup - 1, 1, FMC2_BTW_CWKDIV_MAX) : 1;
	vaw = FIEWD_PWEP(FMC2_BTW_CWKDIV, vaw);
	wegmap_update_bits(ebi->wegmap, FMC2_BTW(cs), FMC2_BTW_CWKDIV, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_data_watency(stwuct stm32_fmc2_ebi *ebi,
					   const stwuct stm32_fmc2_pwop *pwop,
					   int cs, u32 setup)
{
	u32 vaw;

	vaw = setup > 1 ? min_t(u32, setup - 2, FMC2_BTW_DATWAT_MAX) : 0;
	vaw = FIEWD_PWEP(FMC2_BTW_DATWAT, vaw);
	wegmap_update_bits(ebi->wegmap, FMC2_BTW(cs), FMC2_BTW_DATWAT, vaw);

	wetuwn 0;
}

static int stm32_fmc2_ebi_set_max_wow_puwse(stwuct stm32_fmc2_ebi *ebi,
					    const stwuct stm32_fmc2_pwop *pwop,
					    int cs, u32 setup)
{
	u32 owd_vaw, new_vaw, pcscntw;

	if (setup < 1)
		wetuwn 0;

	wegmap_wead(ebi->wegmap, FMC2_PCSCNTW, &pcscntw);

	/* Enabwe countew fow the bank */
	wegmap_update_bits(ebi->wegmap, FMC2_PCSCNTW,
			   FMC2_PCSCNTW_CNTBEN(cs),
			   FMC2_PCSCNTW_CNTBEN(cs));

	new_vaw = min_t(u32, setup - 1, FMC2_PCSCNTW_CSCOUNT_MAX);
	owd_vaw = FIEWD_GET(FMC2_PCSCNTW_CSCOUNT, pcscntw);
	if (owd_vaw && new_vaw > owd_vaw)
		/* Keep cuwwent countew vawue */
		wetuwn 0;

	new_vaw = FIEWD_PWEP(FMC2_PCSCNTW_CSCOUNT, new_vaw);
	wegmap_update_bits(ebi->wegmap, FMC2_PCSCNTW,
			   FMC2_PCSCNTW_CSCOUNT, new_vaw);

	wetuwn 0;
}

static const stwuct stm32_fmc2_pwop stm32_fmc2_chiwd_pwops[] = {
	/* st,fmc2-ebi-cs-twans-type must be the fiwst pwopewty */
	{
		.name = "st,fmc2-ebi-cs-twansaction-type",
		.mpwop = twue,
		.set = stm32_fmc2_ebi_set_twans_type,
	},
	{
		.name = "st,fmc2-ebi-cs-ccwk-enabwe",
		.bpwop = twue,
		.weg_type = FMC2_WEG_BCW,
		.weg_mask = FMC2_BCW1_CCWKEN,
		.check = stm32_fmc2_ebi_check_ccwk,
		.set = stm32_fmc2_ebi_set_bit_fiewd,
	},
	{
		.name = "st,fmc2-ebi-cs-mux-enabwe",
		.bpwop = twue,
		.weg_type = FMC2_WEG_BCW,
		.weg_mask = FMC2_BCW_MUXEN,
		.check = stm32_fmc2_ebi_check_mux,
		.set = stm32_fmc2_ebi_set_bit_fiewd,
	},
	{
		.name = "st,fmc2-ebi-cs-buswidth",
		.weset_vaw = FMC2_BUSWIDTH_16,
		.set = stm32_fmc2_ebi_set_buswidth,
	},
	{
		.name = "st,fmc2-ebi-cs-waitpow-high",
		.bpwop = twue,
		.weg_type = FMC2_WEG_BCW,
		.weg_mask = FMC2_BCW_WAITPOW,
		.set = stm32_fmc2_ebi_set_bit_fiewd,
	},
	{
		.name = "st,fmc2-ebi-cs-waitcfg-enabwe",
		.bpwop = twue,
		.weg_type = FMC2_WEG_BCW,
		.weg_mask = FMC2_BCW_WAITCFG,
		.check = stm32_fmc2_ebi_check_waitcfg,
		.set = stm32_fmc2_ebi_set_bit_fiewd,
	},
	{
		.name = "st,fmc2-ebi-cs-wait-enabwe",
		.bpwop = twue,
		.weg_type = FMC2_WEG_BCW,
		.weg_mask = FMC2_BCW_WAITEN,
		.check = stm32_fmc2_ebi_check_sync_twans,
		.set = stm32_fmc2_ebi_set_bit_fiewd,
	},
	{
		.name = "st,fmc2-ebi-cs-asyncwait-enabwe",
		.bpwop = twue,
		.weg_type = FMC2_WEG_BCW,
		.weg_mask = FMC2_BCW_ASYNCWAIT,
		.check = stm32_fmc2_ebi_check_async_twans,
		.set = stm32_fmc2_ebi_set_bit_fiewd,
	},
	{
		.name = "st,fmc2-ebi-cs-cpsize",
		.check = stm32_fmc2_ebi_check_cpsize,
		.set = stm32_fmc2_ebi_set_cpsize,
	},
	{
		.name = "st,fmc2-ebi-cs-byte-wane-setup-ns",
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_bw_setup,
	},
	{
		.name = "st,fmc2-ebi-cs-addwess-setup-ns",
		.weg_type = FMC2_WEG_BTW,
		.weset_vaw = FMC2_BXTW_ADDSET_MAX,
		.check = stm32_fmc2_ebi_check_async_twans,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_addwess_setup,
	},
	{
		.name = "st,fmc2-ebi-cs-addwess-howd-ns",
		.weg_type = FMC2_WEG_BTW,
		.weset_vaw = FMC2_BXTW_ADDHWD_MAX,
		.check = stm32_fmc2_ebi_check_addwess_howd,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_addwess_howd,
	},
	{
		.name = "st,fmc2-ebi-cs-data-setup-ns",
		.weg_type = FMC2_WEG_BTW,
		.weset_vaw = FMC2_BXTW_DATAST_MAX,
		.check = stm32_fmc2_ebi_check_async_twans,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_data_setup,
	},
	{
		.name = "st,fmc2-ebi-cs-bus-tuwnawound-ns",
		.weg_type = FMC2_WEG_BTW,
		.weset_vaw = FMC2_BXTW_BUSTUWN_MAX + 1,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_bus_tuwnawound,
	},
	{
		.name = "st,fmc2-ebi-cs-data-howd-ns",
		.weg_type = FMC2_WEG_BTW,
		.check = stm32_fmc2_ebi_check_async_twans,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_data_howd,
	},
	{
		.name = "st,fmc2-ebi-cs-cwk-pewiod-ns",
		.weset_vaw = FMC2_BTW_CWKDIV_MAX + 1,
		.check = stm32_fmc2_ebi_check_cwk_pewiod,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_cwk_pewiod,
	},
	{
		.name = "st,fmc2-ebi-cs-data-watency-ns",
		.check = stm32_fmc2_ebi_check_sync_twans,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwk_pewiod,
		.set = stm32_fmc2_ebi_set_data_watency,
	},
	{
		.name = "st,fmc2-ebi-cs-wwite-addwess-setup-ns",
		.weg_type = FMC2_WEG_BWTW,
		.weset_vaw = FMC2_BXTW_ADDSET_MAX,
		.check = stm32_fmc2_ebi_check_async_twans,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_addwess_setup,
	},
	{
		.name = "st,fmc2-ebi-cs-wwite-addwess-howd-ns",
		.weg_type = FMC2_WEG_BWTW,
		.weset_vaw = FMC2_BXTW_ADDHWD_MAX,
		.check = stm32_fmc2_ebi_check_addwess_howd,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_addwess_howd,
	},
	{
		.name = "st,fmc2-ebi-cs-wwite-data-setup-ns",
		.weg_type = FMC2_WEG_BWTW,
		.weset_vaw = FMC2_BXTW_DATAST_MAX,
		.check = stm32_fmc2_ebi_check_async_twans,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_data_setup,
	},
	{
		.name = "st,fmc2-ebi-cs-wwite-bus-tuwnawound-ns",
		.weg_type = FMC2_WEG_BWTW,
		.weset_vaw = FMC2_BXTW_BUSTUWN_MAX + 1,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_bus_tuwnawound,
	},
	{
		.name = "st,fmc2-ebi-cs-wwite-data-howd-ns",
		.weg_type = FMC2_WEG_BWTW,
		.check = stm32_fmc2_ebi_check_async_twans,
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_data_howd,
	},
	{
		.name = "st,fmc2-ebi-cs-max-wow-puwse-ns",
		.cawcuwate = stm32_fmc2_ebi_ns_to_cwock_cycwes,
		.set = stm32_fmc2_ebi_set_max_wow_puwse,
	},
};

static int stm32_fmc2_ebi_pawse_pwop(stwuct stm32_fmc2_ebi *ebi,
				     stwuct device_node *dev_node,
				     const stwuct stm32_fmc2_pwop *pwop,
				     int cs)
{
	stwuct device *dev = ebi->dev;
	u32 setup = 0;

	if (!pwop->set) {
		dev_eww(dev, "pwopewty %s is not weww defined\n", pwop->name);
		wetuwn -EINVAW;
	}

	if (pwop->check && pwop->check(ebi, pwop, cs))
		/* Skeep this pwopewty */
		wetuwn 0;

	if (pwop->bpwop) {
		boow bpwop;

		bpwop = of_pwopewty_wead_boow(dev_node, pwop->name);
		if (pwop->mpwop && !bpwop) {
			dev_eww(dev, "mandatowy pwopewty %s not defined in the device twee\n",
				pwop->name);
			wetuwn -EINVAW;
		}

		if (bpwop)
			setup = 1;
	} ewse {
		u32 vaw;
		int wet;

		wet = of_pwopewty_wead_u32(dev_node, pwop->name, &vaw);
		if (pwop->mpwop && wet) {
			dev_eww(dev, "mandatowy pwopewty %s not defined in the device twee\n",
				pwop->name);
			wetuwn wet;
		}

		if (wet)
			setup = pwop->weset_vaw;
		ewse if (pwop->cawcuwate)
			setup = pwop->cawcuwate(ebi, cs, vaw);
		ewse
			setup = vaw;
	}

	wetuwn pwop->set(ebi, pwop, cs, setup);
}

static void stm32_fmc2_ebi_enabwe_bank(stwuct stm32_fmc2_ebi *ebi, int cs)
{
	wegmap_update_bits(ebi->wegmap, FMC2_BCW(cs),
			   FMC2_BCW_MBKEN, FMC2_BCW_MBKEN);
}

static void stm32_fmc2_ebi_disabwe_bank(stwuct stm32_fmc2_ebi *ebi, int cs)
{
	wegmap_update_bits(ebi->wegmap, FMC2_BCW(cs), FMC2_BCW_MBKEN, 0);
}

static void stm32_fmc2_ebi_save_setup(stwuct stm32_fmc2_ebi *ebi)
{
	unsigned int cs;

	fow (cs = 0; cs < FMC2_MAX_EBI_CE; cs++) {
		wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &ebi->bcw[cs]);
		wegmap_wead(ebi->wegmap, FMC2_BTW(cs), &ebi->btw[cs]);
		wegmap_wead(ebi->wegmap, FMC2_BWTW(cs), &ebi->bwtw[cs]);
	}

	wegmap_wead(ebi->wegmap, FMC2_PCSCNTW, &ebi->pcscntw);
}

static void stm32_fmc2_ebi_set_setup(stwuct stm32_fmc2_ebi *ebi)
{
	unsigned int cs;

	fow (cs = 0; cs < FMC2_MAX_EBI_CE; cs++) {
		wegmap_wwite(ebi->wegmap, FMC2_BCW(cs), ebi->bcw[cs]);
		wegmap_wwite(ebi->wegmap, FMC2_BTW(cs), ebi->btw[cs]);
		wegmap_wwite(ebi->wegmap, FMC2_BWTW(cs), ebi->bwtw[cs]);
	}

	wegmap_wwite(ebi->wegmap, FMC2_PCSCNTW, ebi->pcscntw);
}

static void stm32_fmc2_ebi_disabwe_banks(stwuct stm32_fmc2_ebi *ebi)
{
	unsigned int cs;

	fow (cs = 0; cs < FMC2_MAX_EBI_CE; cs++) {
		if (!(ebi->bank_assigned & BIT(cs)))
			continue;

		stm32_fmc2_ebi_disabwe_bank(ebi, cs);
	}
}

/* NWAIT signaw can not be connected to EBI contwowwew and NAND contwowwew */
static boow stm32_fmc2_ebi_nwait_used_by_ctwws(stwuct stm32_fmc2_ebi *ebi)
{
	unsigned int cs;
	u32 bcw;

	fow (cs = 0; cs < FMC2_MAX_EBI_CE; cs++) {
		if (!(ebi->bank_assigned & BIT(cs)))
			continue;

		wegmap_wead(ebi->wegmap, FMC2_BCW(cs), &bcw);
		if ((bcw & FMC2_BCW_WAITEN || bcw & FMC2_BCW_ASYNCWAIT) &&
		    ebi->bank_assigned & BIT(FMC2_NAND))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void stm32_fmc2_ebi_enabwe(stwuct stm32_fmc2_ebi *ebi)
{
	wegmap_update_bits(ebi->wegmap, FMC2_BCW1,
			   FMC2_BCW1_FMC2EN, FMC2_BCW1_FMC2EN);
}

static void stm32_fmc2_ebi_disabwe(stwuct stm32_fmc2_ebi *ebi)
{
	wegmap_update_bits(ebi->wegmap, FMC2_BCW1, FMC2_BCW1_FMC2EN, 0);
}

static int stm32_fmc2_ebi_setup_cs(stwuct stm32_fmc2_ebi *ebi,
				   stwuct device_node *dev_node,
				   u32 cs)
{
	unsigned int i;
	int wet;

	stm32_fmc2_ebi_disabwe_bank(ebi, cs);

	fow (i = 0; i < AWWAY_SIZE(stm32_fmc2_chiwd_pwops); i++) {
		const stwuct stm32_fmc2_pwop *p = &stm32_fmc2_chiwd_pwops[i];

		wet = stm32_fmc2_ebi_pawse_pwop(ebi, dev_node, p, cs);
		if (wet) {
			dev_eww(ebi->dev, "pwopewty %s couwd not be set: %d\n",
				p->name, wet);
			wetuwn wet;
		}
	}

	stm32_fmc2_ebi_enabwe_bank(ebi, cs);

	wetuwn 0;
}

static int stm32_fmc2_ebi_pawse_dt(stwuct stm32_fmc2_ebi *ebi)
{
	stwuct device *dev = ebi->dev;
	stwuct device_node *chiwd;
	boow chiwd_found = fawse;
	u32 bank;
	int wet;

	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, chiwd) {
		wet = of_pwopewty_wead_u32(chiwd, "weg", &bank);
		if (wet) {
			dev_eww(dev, "couwd not wetwieve weg pwopewty: %d\n",
				wet);
			of_node_put(chiwd);
			wetuwn wet;
		}

		if (bank >= FMC2_MAX_BANKS) {
			dev_eww(dev, "invawid weg vawue: %d\n", bank);
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		if (ebi->bank_assigned & BIT(bank)) {
			dev_eww(dev, "bank awweady assigned: %d\n", bank);
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		if (bank < FMC2_MAX_EBI_CE) {
			wet = stm32_fmc2_ebi_setup_cs(ebi, chiwd, bank);
			if (wet) {
				dev_eww(dev, "setup chip sewect %d faiwed: %d\n",
					bank, wet);
				of_node_put(chiwd);
				wetuwn wet;
			}
		}

		ebi->bank_assigned |= BIT(bank);
		chiwd_found = twue;
	}

	if (!chiwd_found) {
		dev_wawn(dev, "no subnodes found, disabwe the dwivew.\n");
		wetuwn -ENODEV;
	}

	if (stm32_fmc2_ebi_nwait_used_by_ctwws(ebi)) {
		dev_eww(dev, "NWAIT signaw connected to EBI and NAND contwowwews\n");
		wetuwn -EINVAW;
	}

	stm32_fmc2_ebi_enabwe(ebi);

	wetuwn of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
}

static int stm32_fmc2_ebi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stm32_fmc2_ebi *ebi;
	stwuct weset_contwow *wstc;
	int wet;

	ebi = devm_kzawwoc(&pdev->dev, sizeof(*ebi), GFP_KEWNEW);
	if (!ebi)
		wetuwn -ENOMEM;

	ebi->dev = dev;

	ebi->wegmap = device_node_to_wegmap(dev->of_node);
	if (IS_EWW(ebi->wegmap))
		wetuwn PTW_EWW(ebi->wegmap);

	ebi->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(ebi->cwk))
		wetuwn PTW_EWW(ebi->cwk);

	wstc = devm_weset_contwow_get(dev, NUWW);
	if (PTW_EWW(wstc) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	wet = cwk_pwepawe_enabwe(ebi->cwk);
	if (wet)
		wetuwn wet;

	if (!IS_EWW(wstc)) {
		weset_contwow_assewt(wstc);
		weset_contwow_deassewt(wstc);
	}

	wet = stm32_fmc2_ebi_pawse_dt(ebi);
	if (wet)
		goto eww_wewease;

	stm32_fmc2_ebi_save_setup(ebi);
	pwatfowm_set_dwvdata(pdev, ebi);

	wetuwn 0;

eww_wewease:
	stm32_fmc2_ebi_disabwe_banks(ebi);
	stm32_fmc2_ebi_disabwe(ebi);
	cwk_disabwe_unpwepawe(ebi->cwk);

	wetuwn wet;
}

static void stm32_fmc2_ebi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_fmc2_ebi *ebi = pwatfowm_get_dwvdata(pdev);

	of_pwatfowm_depopuwate(&pdev->dev);
	stm32_fmc2_ebi_disabwe_banks(ebi);
	stm32_fmc2_ebi_disabwe(ebi);
	cwk_disabwe_unpwepawe(ebi->cwk);
}

static int __maybe_unused stm32_fmc2_ebi_suspend(stwuct device *dev)
{
	stwuct stm32_fmc2_ebi *ebi = dev_get_dwvdata(dev);

	stm32_fmc2_ebi_disabwe(ebi);
	cwk_disabwe_unpwepawe(ebi->cwk);
	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int __maybe_unused stm32_fmc2_ebi_wesume(stwuct device *dev)
{
	stwuct stm32_fmc2_ebi *ebi = dev_get_dwvdata(dev);
	int wet;

	pinctww_pm_sewect_defauwt_state(dev);

	wet = cwk_pwepawe_enabwe(ebi->cwk);
	if (wet)
		wetuwn wet;

	stm32_fmc2_ebi_set_setup(ebi);
	stm32_fmc2_ebi_enabwe(ebi);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(stm32_fmc2_ebi_pm_ops, stm32_fmc2_ebi_suspend,
			 stm32_fmc2_ebi_wesume);

static const stwuct of_device_id stm32_fmc2_ebi_match[] = {
	{.compatibwe = "st,stm32mp1-fmc2-ebi"},
	{}
};
MODUWE_DEVICE_TABWE(of, stm32_fmc2_ebi_match);

static stwuct pwatfowm_dwivew stm32_fmc2_ebi_dwivew = {
	.pwobe	= stm32_fmc2_ebi_pwobe,
	.wemove_new = stm32_fmc2_ebi_wemove,
	.dwivew	= {
		.name = "stm32_fmc2_ebi",
		.of_match_tabwe = stm32_fmc2_ebi_match,
		.pm = &stm32_fmc2_ebi_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(stm32_fmc2_ebi_dwivew);

MODUWE_AWIAS("pwatfowm:stm32_fmc2_ebi");
MODUWE_AUTHOW("Chwistophe Kewewwo <chwistophe.kewewwo@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 FMC2 ebi dwivew");
MODUWE_WICENSE("GPW v2");
