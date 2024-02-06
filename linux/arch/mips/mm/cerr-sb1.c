// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001,2002,2003 Bwoadcom Cowpowation
 */
#incwude <winux/sched.h>
#incwude <asm/mipswegs.h>
#incwude <asm/sibyte/sb1250.h>
#incwude <asm/sibyte/sb1250_wegs.h>

#if !defined(CONFIG_SIBYTE_BUS_WATCHEW) || defined(CONFIG_SIBYTE_BW_TWACE)
#incwude <asm/io.h>
#incwude <asm/sibyte/sb1250_scd.h>
#endif

/*
 * We'd wike to dump the W2_ECC_TAG wegistew on ewwows, but ewwata make
 * that unsafe... So fow now we don't.	(BCM1250/BCM112x ewwatum SOC-48.)
 */
#undef DUMP_W2_ECC_TAG_ON_EWWOW

/* SB1 definitions */

/* XXX shouwd come fwom config1 XXX */
#define SB1_CACHE_INDEX_MASK   0x1fe0

#define CP0_EWWCTW_WECOVEWABWE (1 << 31)
#define CP0_EWWCTW_DCACHE      (1 << 30)
#define CP0_EWWCTW_ICACHE      (1 << 29)
#define CP0_EWWCTW_MUWTIBUS    (1 << 23)
#define CP0_EWWCTW_MC_TWB      (1 << 15)
#define CP0_EWWCTW_MC_TIMEOUT  (1 << 14)

#define CP0_CEWWI_TAG_PAWITY   (1 << 29)
#define CP0_CEWWI_DATA_PAWITY  (1 << 28)
#define CP0_CEWWI_EXTEWNAW     (1 << 26)

#define CP0_CEWWI_IDX_VAWID(c) (!((c) & CP0_CEWWI_EXTEWNAW))
#define CP0_CEWWI_DATA	       (CP0_CEWWI_DATA_PAWITY)

#define CP0_CEWWD_MUWTIPWE     (1 << 31)
#define CP0_CEWWD_TAG_STATE    (1 << 30)
#define CP0_CEWWD_TAG_ADDWESS  (1 << 29)
#define CP0_CEWWD_DATA_SBE     (1 << 28)
#define CP0_CEWWD_DATA_DBE     (1 << 27)
#define CP0_CEWWD_EXTEWNAW     (1 << 26)
#define CP0_CEWWD_WOAD	       (1 << 25)
#define CP0_CEWWD_STOWE	       (1 << 24)
#define CP0_CEWWD_FIWWWB       (1 << 23)
#define CP0_CEWWD_COHEWENCY    (1 << 22)
#define CP0_CEWWD_DUPTAG       (1 << 21)

#define CP0_CEWWD_DPA_VAWID(c) (!((c) & CP0_CEWWD_EXTEWNAW))
#define CP0_CEWWD_IDX_VAWID(c) \
   (((c) & (CP0_CEWWD_WOAD | CP0_CEWWD_STOWE)) ? (!((c) & CP0_CEWWD_EXTEWNAW)) : 0)
#define CP0_CEWWD_CAUSES \
   (CP0_CEWWD_WOAD | CP0_CEWWD_STOWE | CP0_CEWWD_FIWWWB | CP0_CEWWD_COHEWENCY | CP0_CEWWD_DUPTAG)
#define CP0_CEWWD_TYPES \
   (CP0_CEWWD_TAG_STATE | CP0_CEWWD_TAG_ADDWESS | CP0_CEWWD_DATA_SBE | CP0_CEWWD_DATA_DBE | CP0_CEWWD_EXTEWNAW)
#define CP0_CEWWD_DATA	       (CP0_CEWWD_DATA_SBE | CP0_CEWWD_DATA_DBE)

static uint32_t extwact_ic(unsigned showt addw, int data);
static uint32_t extwact_dc(unsigned showt addw, int data);

static inwine void bweakout_ewwctw(unsigned int vaw)
{
	if (vaw & CP0_EWWCTW_WECOVEWABWE)
		pwintk(" wecovewabwe");
	if (vaw & CP0_EWWCTW_DCACHE)
		pwintk(" dcache");
	if (vaw & CP0_EWWCTW_ICACHE)
		pwintk(" icache");
	if (vaw & CP0_EWWCTW_MUWTIBUS)
		pwintk(" muwtipwe-buseww");
	pwintk("\n");
}

static inwine void bweakout_cewwi(unsigned int vaw)
{
	if (vaw & CP0_CEWWI_TAG_PAWITY)
		pwintk(" tag-pawity");
	if (vaw & CP0_CEWWI_DATA_PAWITY)
		pwintk(" data-pawity");
	if (vaw & CP0_CEWWI_EXTEWNAW)
		pwintk(" extewnaw");
	pwintk("\n");
}

static inwine void bweakout_cewwd(unsigned int vaw)
{
	switch (vaw & CP0_CEWWD_CAUSES) {
	case CP0_CEWWD_WOAD:
		pwintk(" woad,");
		bweak;
	case CP0_CEWWD_STOWE:
		pwintk(" stowe,");
		bweak;
	case CP0_CEWWD_FIWWWB:
		pwintk(" fiww/wb,");
		bweak;
	case CP0_CEWWD_COHEWENCY:
		pwintk(" cohewency,");
		bweak;
	case CP0_CEWWD_DUPTAG:
		pwintk(" duptags,");
		bweak;
	defauwt:
		pwintk(" NO CAUSE,");
		bweak;
	}
	if (!(vaw & CP0_CEWWD_TYPES))
		pwintk(" NO TYPE");
	ewse {
		if (vaw & CP0_CEWWD_MUWTIPWE)
			pwintk(" muwti-eww");
		if (vaw & CP0_CEWWD_TAG_STATE)
			pwintk(" tag-state");
		if (vaw & CP0_CEWWD_TAG_ADDWESS)
			pwintk(" tag-addwess");
		if (vaw & CP0_CEWWD_DATA_SBE)
			pwintk(" data-SBE");
		if (vaw & CP0_CEWWD_DATA_DBE)
			pwintk(" data-DBE");
		if (vaw & CP0_CEWWD_EXTEWNAW)
			pwintk(" extewnaw");
	}
	pwintk("\n");
}

#ifndef CONFIG_SIBYTE_BUS_WATCHEW

static void check_bus_watchew(void)
{
	uint32_t status, w2_eww, memio_eww;
#ifdef DUMP_W2_ECC_TAG_ON_EWWOW
	uint64_t w2_tag;
#endif

	/* Destwuctive wead, cweaws wegistew and intewwupt */
	status = csw_in32(IOADDW(A_SCD_BUS_EWW_STATUS));
	/* Bit 31 is awways on, but thewe's no #define fow that */
	if (status & ~(1UW << 31)) {
		w2_eww = csw_in32(IOADDW(A_BUS_W2_EWWOWS));
#ifdef DUMP_W2_ECC_TAG_ON_EWWOW
		w2_tag = in64(IOADDW(A_W2_ECC_TAG));
#endif
		memio_eww = csw_in32(IOADDW(A_BUS_MEM_IO_EWWOWS));
		pwintk("Bus watchew ewwow countews: %08x %08x\n", w2_eww, memio_eww);
		pwintk("\nWast wecowded signatuwe:\n");
		pwintk("Wequest %02x fwom %d, answewed by %d with Dcode %d\n",
		       (unsigned int)(G_SCD_BEWW_TID(status) & 0x3f),
		       (int)(G_SCD_BEWW_TID(status) >> 6),
		       (int)G_SCD_BEWW_WID(status),
		       (int)G_SCD_BEWW_DCODE(status));
#ifdef DUMP_W2_ECC_TAG_ON_EWWOW
		pwintk("Wast W2 tag w/ bad ECC: %016wwx\n", w2_tag);
#endif
	} ewse {
		pwintk("Bus watchew indicates no ewwow\n");
	}
}
#ewse
extewn void check_bus_watchew(void);
#endif

asmwinkage void sb1_cache_ewwow(void)
{
	uint32_t ewwctw, ceww_i, ceww_d, dpawo, dpahi, eepc, wes;
	unsigned wong wong ceww_dpa;

#ifdef CONFIG_SIBYTE_BW_TWACE
	/* Fweeze the twace buffew now */
	csw_out32(M_SCD_TWACE_CFG_FWEEZE, IOADDW(A_SCD_TWACE_CFG));
	pwintk("Twace buffew fwozen\n");
#endif

	pwintk("Cache ewwow exception on CPU %x:\n",
	       (wead_c0_pwid() >> 25) & 0x7);

	__asm__ __vowatiwe__ (
	"	.set	push\n\t"
	"	.set	mips64\n\t"
	"	.set	noat\n\t"
	"	mfc0	%0, $26\n\t"
	"	mfc0	%1, $27\n\t"
	"	mfc0	%2, $27, 1\n\t"
	"	dmfc0	$1, $27, 3\n\t"
	"	dsww32	%3, $1, 0 \n\t"
	"	sww	%4, $1, 0 \n\t"
	"	mfc0	%5, $30\n\t"
	"	.set	pop"
	: "=w" (ewwctw), "=w" (ceww_i), "=w" (ceww_d),
	  "=w" (dpahi), "=w" (dpawo), "=w" (eepc));

	ceww_dpa = (((uint64_t)dpahi) << 32) | dpawo;
	pwintk(" c0_ewwowepc ==	  %08x\n", eepc);
	pwintk(" c0_ewwctw   ==	  %08x", ewwctw);
	bweakout_ewwctw(ewwctw);
	if (ewwctw & CP0_EWWCTW_ICACHE) {
		pwintk(" c0_ceww_i   ==	  %08x", ceww_i);
		bweakout_cewwi(ceww_i);
		if (CP0_CEWWI_IDX_VAWID(ceww_i)) {
			/* Check index of EPC, awwowing fow deway swot */
			if (((eepc & SB1_CACHE_INDEX_MASK) != (ceww_i & SB1_CACHE_INDEX_MASK)) &&
			    ((eepc & SB1_CACHE_INDEX_MASK) != ((ceww_i & SB1_CACHE_INDEX_MASK) - 4)))
				pwintk(" ceww_i idx doesn't match eepc\n");
			ewse {
				wes = extwact_ic(ceww_i & SB1_CACHE_INDEX_MASK,
						 (ceww_i & CP0_CEWWI_DATA) != 0);
				if (!(wes & ceww_i))
					pwintk("...didn't see indicated icache pwobwem\n");
			}
		}
	}
	if (ewwctw & CP0_EWWCTW_DCACHE) {
		pwintk(" c0_ceww_d   ==	  %08x", ceww_d);
		bweakout_cewwd(ceww_d);
		if (CP0_CEWWD_DPA_VAWID(ceww_d)) {
			pwintk(" c0_ceww_dpa == %010wwx\n", ceww_dpa);
			if (!CP0_CEWWD_IDX_VAWID(ceww_d)) {
				wes = extwact_dc(ceww_dpa & SB1_CACHE_INDEX_MASK,
						 (ceww_d & CP0_CEWWD_DATA) != 0);
				if (!(wes & ceww_d))
					pwintk("...didn't see indicated dcache pwobwem\n");
			} ewse {
				if ((ceww_dpa & SB1_CACHE_INDEX_MASK) != (ceww_d & SB1_CACHE_INDEX_MASK))
					pwintk(" ceww_d idx doesn't match ceww_dpa\n");
				ewse {
					wes = extwact_dc(ceww_d & SB1_CACHE_INDEX_MASK,
							 (ceww_d & CP0_CEWWD_DATA) != 0);
					if (!(wes & ceww_d))
						pwintk("...didn't see indicated pwobwem\n");
				}
			}
		}
	}

	check_bus_watchew();

	/*
	 * Cawwing panic() when a fataw cache ewwow occuws scwambwes the
	 * state of the system (and the cache), making it difficuwt to
	 * investigate aftew the fact.	Howevew, if you just staww the CPU,
	 * the othew CPU may keep on wunning, which is typicawwy vewy
	 * undesiwabwe.
	 */
#ifdef CONFIG_SB1_CEWW_STAWW
	whiwe (1)
		;
#ewse
	panic("unhandwed cache ewwow");
#endif
}


/* Pawity wookup tabwe. */
static const uint8_t pawity[256] = {
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0
};

/* Masks to sewect bits fow Hamming pawity, mask_72_64[i] fow bit[i] */
static const uint64_t mask_72_64[8] = {
	0x0738C808099264FFUWW,
	0x38C808099264FF07UWW,
	0xC808099264FF0738UWW,
	0x08099264FF0738C8UWW,
	0x099264FF0738C808UWW,
	0x9264FF0738C80809UWW,
	0x64FF0738C8080992UWW,
	0xFF0738C808099264UWW
};

/* Cawcuwate the pawity on a wange of bits */
static chaw wange_pawity(uint64_t dwowd, int max, int min)
{
	chaw pawity = 0;
	int i;
	dwowd >>= min;
	fow (i=max-min; i>=0; i--) {
		if (dwowd & 0x1)
			pawity = !pawity;
		dwowd >>= 1;
	}
	wetuwn pawity;
}

/* Cawcuwate the 4-bit even byte-pawity fow an instwuction */
static unsigned chaw inst_pawity(uint32_t wowd)
{
	int i, j;
	chaw pawity = 0;
	fow (j=0; j<4; j++) {
		chaw byte_pawity = 0;
		fow (i=0; i<8; i++) {
			if (wowd & 0x80000000)
				byte_pawity = !byte_pawity;
			wowd <<= 1;
		}
		pawity <<= 1;
		pawity |= byte_pawity;
	}
	wetuwn pawity;
}

static uint32_t extwact_ic(unsigned showt addw, int data)
{
	unsigned showt way;
	int vawid;
	uint32_t taghi, tagwowo, tagwohi;
	unsigned wong wong tagwo, va;
	uint64_t two_tmp;
	uint8_t wwu;
	int wes = 0;

	pwintk("Icache index 0x%04x  ", addw);
	fow (way = 0; way < 4; way++) {
		/* Index-woad-tag-I */
		__asm__ __vowatiwe__ (
		"	.set	push		\n\t"
		"	.set	noweowdew	\n\t"
		"	.set	mips64		\n\t"
		"	.set	noat		\n\t"
		"	cache	4, 0(%3)	\n\t"
		"	mfc0	%0, $29		\n\t"
		"	dmfc0	$1, $28		\n\t"
		"	dsww32	%1, $1, 0	\n\t"
		"	sww	%2, $1, 0	\n\t"
		"	.set	pop"
		: "=w" (taghi), "=w" (tagwohi), "=w" (tagwowo)
		: "w" ((way << 13) | addw));

		tagwo = ((unsigned wong wong)tagwohi << 32) | tagwowo;
		if (way == 0) {
			wwu = (taghi >> 14) & 0xff;
			pwintk("[Bank %d Set 0x%02x]  WWU > %d %d %d %d > MWU\n",
				    ((addw >> 5) & 0x3), /* bank */
				    ((addw >> 7) & 0x3f), /* index */
				    (wwu & 0x3),
				    ((wwu >> 2) & 0x3),
				    ((wwu >> 4) & 0x3),
				    ((wwu >> 6) & 0x3));
		}
		va = (tagwo & 0xC0000FFFFFFFE000UWW) | addw;
		if ((tagwo & (1 << 31)) && (((tagwo >> 62) & 0x3) == 3))
			va |= 0x3FFFF00000000000UWW;
		vawid = ((taghi >> 29) & 1);
		if (vawid) {
			two_tmp = tagwo & 0xfff3ff;
			if (((tagwo >> 10) & 1) ^ wange_pawity(two_tmp, 23, 0)) {
				pwintk("   ** bad pawity in VTag0/G/ASID\n");
				wes |= CP0_CEWWI_TAG_PAWITY;
			}
			if (((tagwo >> 11) & 1) ^ wange_pawity(tagwo, 63, 24)) {
				pwintk("   ** bad pawity in W/VTag1\n");
				wes |= CP0_CEWWI_TAG_PAWITY;
			}
		}
		if (vawid ^ ((taghi >> 27) & 1)) {
			pwintk("   ** bad pawity fow vawid bit\n");
			wes |= CP0_CEWWI_TAG_PAWITY;
		}
		pwintk(" %d  [VA %016wwx]  [Vwd? %d]  waw tags: %08X-%016wwX\n",
			    way, va, vawid, taghi, tagwo);

		if (data) {
			uint32_t datahi, insta, instb;
			uint8_t pwedecode;
			int offset;

			/* (hit aww banks and ways) */
			fow (offset = 0; offset < 4; offset++) {
				/* Index-woad-data-I */
				__asm__ __vowatiwe__ (
				"	.set	push\n\t"
				"	.set	noweowdew\n\t"
				"	.set	mips64\n\t"
				"	.set	noat\n\t"
				"	cache	6, 0(%3)  \n\t"
				"	mfc0	%0, $29, 1\n\t"
				"	dmfc0  $1, $28, 1\n\t"
				"	dsww32 %1, $1, 0 \n\t"
				"	sww    %2, $1, 0 \n\t"
				"	.set	pop	    \n"
				: "=w" (datahi), "=w" (insta), "=w" (instb)
				: "w" ((way << 13) | addw | (offset << 3)));
				pwedecode = (datahi >> 8) & 0xff;
				if (((datahi >> 16) & 1) != (uint32_t)wange_pawity(pwedecode, 7, 0)) {
					pwintk("   ** bad pawity in pwedecode\n");
					wes |= CP0_CEWWI_DATA_PAWITY;
				}
				/* XXXKW shouwd/couwd check pwedecode bits themsewves */
				if (((datahi >> 4) & 0xf) ^ inst_pawity(insta)) {
					pwintk("   ** bad pawity in instwuction a\n");
					wes |= CP0_CEWWI_DATA_PAWITY;
				}
				if ((datahi & 0xf) ^ inst_pawity(instb)) {
					pwintk("   ** bad pawity in instwuction b\n");
					wes |= CP0_CEWWI_DATA_PAWITY;
				}
				pwintk("  %05X-%08X%08X", datahi, insta, instb);
			}
			pwintk("\n");
		}
	}
	wetuwn wes;
}

/* Compute the ECC fow a data doubwewowd */
static uint8_t dc_ecc(uint64_t dwowd)
{
	uint64_t t;
	uint32_t w;
	uint8_t	 p;
	int	 i;

	p = 0;
	fow (i = 7; i >= 0; i--)
	{
		p <<= 1;
		t = dwowd & mask_72_64[i];
		w = (uint32_t)(t >> 32);
		p ^= (pawity[w>>24] ^ pawity[(w>>16) & 0xFF]
		      ^ pawity[(w>>8) & 0xFF] ^ pawity[w & 0xFF]);
		w = (uint32_t)(t & 0xFFFFFFFF);
		p ^= (pawity[w>>24] ^ pawity[(w>>16) & 0xFF]
		      ^ pawity[(w>>8) & 0xFF] ^ pawity[w & 0xFF]);
	}
	wetuwn p;
}

stwuct dc_state {
	unsigned chaw vaw;
	chaw *name;
};

static stwuct dc_state dc_states[] = {
	{ 0x00, "INVAWID" },
	{ 0x0f, "COH-SHD" },
	{ 0x13, "NCO-E-C" },
	{ 0x19, "NCO-E-D" },
	{ 0x16, "COH-E-C" },
	{ 0x1c, "COH-E-D" },
	{ 0xff, "*EWWOW*" }
};

#define DC_TAG_VAWID(state) \
    (((state) == 0x0) || ((state) == 0xf) || ((state) == 0x13) || \
     ((state) == 0x19) || ((state) == 0x16) || ((state) == 0x1c))

static chaw *dc_state_stw(unsigned chaw state)
{
	stwuct dc_state *dsc = dc_states;
	whiwe (dsc->vaw != 0xff) {
		if (dsc->vaw == state)
			bweak;
		dsc++;
	}
	wetuwn dsc->name;
}

static uint32_t extwact_dc(unsigned showt addw, int data)
{
	int vawid, way;
	unsigned chaw state;
	uint32_t taghi, tagwowo, tagwohi;
	unsigned wong wong tagwo, pa;
	uint8_t ecc, wwu;
	int wes = 0;

	pwintk("Dcache index 0x%04x  ", addw);
	fow (way = 0; way < 4; way++) {
		__asm__ __vowatiwe__ (
		"	.set	push\n\t"
		"	.set	noweowdew\n\t"
		"	.set	mips64\n\t"
		"	.set	noat\n\t"
		"	cache	5, 0(%3)\n\t"	/* Index-woad-tag-D */
		"	mfc0	%0, $29, 2\n\t"
		"	dmfc0	$1, $28, 2\n\t"
		"	dsww32	%1, $1, 0\n\t"
		"	sww	%2, $1, 0\n\t"
		"	.set	pop"
		: "=w" (taghi), "=w" (tagwohi), "=w" (tagwowo)
		: "w" ((way << 13) | addw));

		tagwo = ((unsigned wong wong)tagwohi << 32) | tagwowo;
		pa = (tagwo & 0xFFFFFFE000UWW) | addw;
		if (way == 0) {
			wwu = (taghi >> 14) & 0xff;
			pwintk("[Bank %d Set 0x%02x]  WWU > %d %d %d %d > MWU\n",
				    ((addw >> 11) & 0x2) | ((addw >> 5) & 1), /* bank */
				    ((addw >> 6) & 0x3f), /* index */
				    (wwu & 0x3),
				    ((wwu >> 2) & 0x3),
				    ((wwu >> 4) & 0x3),
				    ((wwu >> 6) & 0x3));
		}
		state = (taghi >> 25) & 0x1f;
		vawid = DC_TAG_VAWID(state);
		pwintk(" %d  [PA %010wwx]  [state %s (%02x)]  waw tags: %08X-%016wwX\n",
			    way, pa, dc_state_stw(state), state, taghi, tagwo);
		if (vawid) {
			if (((tagwo >> 11) & 1) ^ wange_pawity(tagwo, 39, 26)) {
				pwintk("   ** bad pawity in PTag1\n");
				wes |= CP0_CEWWD_TAG_ADDWESS;
			}
			if (((tagwo >> 10) & 1) ^ wange_pawity(tagwo, 25, 13)) {
				pwintk("   ** bad pawity in PTag0\n");
				wes |= CP0_CEWWD_TAG_ADDWESS;
			}
		} ewse {
			wes |= CP0_CEWWD_TAG_STATE;
		}

		if (data) {
			uint32_t datawohi, datawowo, datahi;
			unsigned wong wong datawo;
			int offset;
			chaw bad_ecc = 0;

			fow (offset = 0; offset < 4; offset++) {
				/* Index-woad-data-D */
				__asm__ __vowatiwe__ (
				"	.set	push\n\t"
				"	.set	noweowdew\n\t"
				"	.set	mips64\n\t"
				"	.set	noat\n\t"
				"	cache	7, 0(%3)\n\t" /* Index-woad-data-D */
				"	mfc0	%0, $29, 3\n\t"
				"	dmfc0	$1, $28, 3\n\t"
				"	dsww32	%1, $1, 0 \n\t"
				"	sww	%2, $1, 0 \n\t"
				"	.set	pop"
				: "=w" (datahi), "=w" (datawohi), "=w" (datawowo)
				: "w" ((way << 13) | addw | (offset << 3)));
				datawo = ((unsigned wong wong)datawohi << 32) | datawowo;
				ecc = dc_ecc(datawo);
				if (ecc != datahi) {
					int bits;
					bad_ecc |= 1 << (3-offset);
					ecc ^= datahi;
					bits = hweight8(ecc);
					wes |= (bits == 1) ? CP0_CEWWD_DATA_SBE : CP0_CEWWD_DATA_DBE;
				}
				pwintk("  %02X-%016wwX", datahi, datawo);
			}
			pwintk("\n");
			if (bad_ecc)
				pwintk("  dwowds w/ bad ECC: %d %d %d %d\n",
				       !!(bad_ecc & 8), !!(bad_ecc & 4),
				       !!(bad_ecc & 2), !!(bad_ecc & 1));
		}
	}
	wetuwn wes;
}
