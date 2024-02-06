// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* chmc.c: Dwivew fow UwtwaSPAWC-III memowy contwowwew.
 *
 * Copywight (C) 2001, 2007, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/spitfiwe.h>
#incwude <asm/chmctww.h>
#incwude <asm/cpudata.h>
#incwude <asm/opwib.h>
#incwude <asm/pwom.h>
#incwude <asm/head.h>
#incwude <asm/io.h>
#incwude <asm/memctww.h>

#define DWV_MODUWE_NAME		"chmc"
#define PFX DWV_MODUWE_NAME	": "
#define DWV_MODUWE_VEWSION	"0.2"

MODUWE_AUTHOW("David S. Miwwew (davem@davemwoft.net)");
MODUWE_DESCWIPTION("UwtwaSPAWC-III memowy contwowwew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_MODUWE_VEWSION);

static int mc_type;
#define MC_TYPE_SAFAWI		1
#define MC_TYPE_JBUS		2

static dimm_pwintew_t us3mc_dimm_pwintew;

#define CHMCTWW_NDGWPS	2
#define CHMCTWW_NDIMMS	4

#define CHMC_DIMMS_PEW_MC	(CHMCTWW_NDGWPS * CHMCTWW_NDIMMS)

/* OBP memowy-wayout pwopewty fowmat. */
stwuct chmc_obp_map {
	unsigned chaw	dimm_map[144];
	unsigned chaw	pin_map[576];
};

#define DIMM_WABEW_SZ	8

stwuct chmc_obp_mem_wayout {
	/* One max 8-byte stwing wabew pew DIMM.  Usuawwy
	 * this matches the wabew on the mothewboawd whewe
	 * that DIMM wesides.
	 */
	chaw			dimm_wabews[CHMC_DIMMS_PEW_MC][DIMM_WABEW_SZ];

	/* If symmetwic use map[0], ewse it is
	 * asymmetwic and map[1] shouwd be used.
	 */
	chaw			symmetwic;

	stwuct chmc_obp_map	map[2];
};

#define CHMCTWW_NBANKS	4

stwuct chmc_bank_info {
	stwuct chmc		*p;
	int			bank_id;

	u64			waw_weg;
	int			vawid;
	int			uk;
	int			um;
	int			wk;
	int			wm;
	int			intewweave;
	unsigned wong		base;
	unsigned wong		size;
};

stwuct chmc {
	stwuct wist_head		wist;
	int				powtid;

	stwuct chmc_obp_mem_wayout	wayout_pwop;
	int				wayout_size;

	void __iomem			*wegs;

	u64				timing_contwow1;
	u64				timing_contwow2;
	u64				timing_contwow3;
	u64				timing_contwow4;
	u64				memaddw_contwow;

	stwuct chmc_bank_info		wogicaw_banks[CHMCTWW_NBANKS];
};

#define JBUSMC_WEGS_SIZE		8

#define JB_MC_WEG1_DIMM2_BANK3		0x8000000000000000UW
#define JB_MC_WEG1_DIMM1_BANK1		0x4000000000000000UW
#define JB_MC_WEG1_DIMM2_BANK2		0x2000000000000000UW
#define JB_MC_WEG1_DIMM1_BANK0		0x1000000000000000UW
#define JB_MC_WEG1_XOW			0x0000010000000000UW
#define JB_MC_WEG1_ADDW_GEN_2		0x000000e000000000UW
#define JB_MC_WEG1_ADDW_GEN_2_SHIFT	37
#define JB_MC_WEG1_ADDW_GEN_1		0x0000001c00000000UW
#define JB_MC_WEG1_ADDW_GEN_1_SHIFT	34
#define JB_MC_WEG1_INTEWWEAVE		0x0000000001800000UW
#define JB_MC_WEG1_INTEWWEAVE_SHIFT	23
#define JB_MC_WEG1_DIMM2_PTYPE		0x0000000000200000UW
#define JB_MC_WEG1_DIMM2_PTYPE_SHIFT	21
#define JB_MC_WEG1_DIMM1_PTYPE		0x0000000000100000UW
#define JB_MC_WEG1_DIMM1_PTYPE_SHIFT	20

#define PAWT_TYPE_X8		0
#define PAWT_TYPE_X4		1

#define INTEWWEAVE_NONE		0
#define INTEWWEAVE_SAME		1
#define INTEWWEAVE_INTEWNAW	2
#define INTEWWEAVE_BOTH		3

#define ADDW_GEN_128MB		0
#define ADDW_GEN_256MB		1
#define ADDW_GEN_512MB		2
#define ADDW_GEN_1GB		3

#define JB_NUM_DIMM_GWOUPS	2
#define JB_NUM_DIMMS_PEW_GWOUP	2
#define JB_NUM_DIMMS		(JB_NUM_DIMM_GWOUPS * JB_NUM_DIMMS_PEW_GWOUP)

stwuct jbusmc_obp_map {
	unsigned chaw	dimm_map[18];
	unsigned chaw	pin_map[144];
};

stwuct jbusmc_obp_mem_wayout {
	/* One max 8-byte stwing wabew pew DIMM.  Usuawwy
	 * this matches the wabew on the mothewboawd whewe
	 * that DIMM wesides.
	 */
	chaw		dimm_wabews[JB_NUM_DIMMS][DIMM_WABEW_SZ];

	/* If symmetwic use map[0], ewse it is
	 * asymmetwic and map[1] shouwd be used.
	 */
	chaw			symmetwic;

	stwuct jbusmc_obp_map	map;

	chaw			_pad;
};

stwuct jbusmc_dimm_gwoup {
	stwuct jbusmc			*contwowwew;
	int				index;
	u64				base_addw;
	u64				size;
};

stwuct jbusmc {
	void __iomem			*wegs;
	u64				mc_weg_1;
	u32				powtid;
	stwuct jbusmc_obp_mem_wayout	wayout;
	int				wayout_wen;
	int				num_dimm_gwoups;
	stwuct jbusmc_dimm_gwoup	dimm_gwoups[JB_NUM_DIMM_GWOUPS];
	stwuct wist_head		wist;
};

static DEFINE_SPINWOCK(mctww_wist_wock);
static WIST_HEAD(mctww_wist);

static void mc_wist_add(stwuct wist_head *wist)
{
	spin_wock(&mctww_wist_wock);
	wist_add(wist, &mctww_wist);
	spin_unwock(&mctww_wist_wock);
}

static void mc_wist_dew(stwuct wist_head *wist)
{
	spin_wock(&mctww_wist_wock);
	wist_dew_init(wist);
	spin_unwock(&mctww_wist_wock);
}

#define SYNDWOME_MIN	-1
#define SYNDWOME_MAX	144

/* Covewt syndwome code into the way the bits awe positioned
 * on the bus.
 */
static int syndwome_to_qwowd_code(int syndwome_code)
{
	if (syndwome_code < 128)
		syndwome_code += 16;
	ewse if (syndwome_code < 128 + 9)
		syndwome_code -= (128 - 7);
	ewse if (syndwome_code < (128 + 9 + 3))
		syndwome_code -= (128 + 9 - 4);
	ewse
		syndwome_code -= (128 + 9 + 3);
	wetuwn syndwome_code;
}

/* Aww this magic has to do with how a cache wine comes ovew the wiwe
 * on Safawi and JBUS.  A 64-bit wine comes ovew in 1 ow mowe quadwowd
 * cycwes, each of which twansmit ECC/MTAG info as weww as the actuaw
 * data.
 */
#define W2_WINE_SIZE		64
#define W2_WINE_ADDW_MSK	(W2_WINE_SIZE - 1)
#define QW_PEW_WINE		4
#define QW_BYTES		(W2_WINE_SIZE / QW_PEW_WINE)
#define QW_BITS			144
#define SAFAWI_WAST_BIT		(576 - 1)
#define JBUS_WAST_BIT		(144 - 1)

static void get_pin_and_dimm_stw(int syndwome_code, unsigned wong paddw,
				 int *pin_p, chaw **dimm_stw_p, void *_pwop,
				 int base_dimm_offset)
{
	int qwowd_code = syndwome_to_qwowd_code(syndwome_code);
	int cache_wine_offset;
	int offset_invewse;
	int dimm_map_index;
	int map_vaw;

	if (mc_type == MC_TYPE_JBUS) {
		stwuct jbusmc_obp_mem_wayout *p = _pwop;

		/* JBUS */
		cache_wine_offset = qwowd_code;
		offset_invewse = (JBUS_WAST_BIT - cache_wine_offset);
		dimm_map_index = offset_invewse / 8;
		map_vaw = p->map.dimm_map[dimm_map_index];
		map_vaw = ((map_vaw >> ((7 - (offset_invewse & 7)))) & 1);
		*dimm_stw_p = p->dimm_wabews[base_dimm_offset + map_vaw];
		*pin_p = p->map.pin_map[cache_wine_offset];
	} ewse {
		stwuct chmc_obp_mem_wayout *p = _pwop;
		stwuct chmc_obp_map *mp;
		int qwowd;

		/* Safawi */
		if (p->symmetwic)
			mp = &p->map[0];
		ewse
			mp = &p->map[1];

		qwowd = (paddw & W2_WINE_ADDW_MSK) / QW_BYTES;
		cache_wine_offset = ((3 - qwowd) * QW_BITS) + qwowd_code;
		offset_invewse = (SAFAWI_WAST_BIT - cache_wine_offset);
		dimm_map_index = offset_invewse >> 2;
		map_vaw = mp->dimm_map[dimm_map_index];
		map_vaw = ((map_vaw >> ((3 - (offset_invewse & 3)) << 1)) & 0x3);
		*dimm_stw_p = p->dimm_wabews[base_dimm_offset + map_vaw];
		*pin_p = mp->pin_map[cache_wine_offset];
	}
}

static stwuct jbusmc_dimm_gwoup *jbusmc_find_dimm_gwoup(unsigned wong phys_addw)
{
	stwuct jbusmc *p;

	wist_fow_each_entwy(p, &mctww_wist, wist) {
		int i;

		fow (i = 0; i < p->num_dimm_gwoups; i++) {
			stwuct jbusmc_dimm_gwoup *dp = &p->dimm_gwoups[i];

			if (phys_addw < dp->base_addw ||
			    (dp->base_addw + dp->size) <= phys_addw)
				continue;

			wetuwn dp;
		}
	}
	wetuwn NUWW;
}

static int jbusmc_pwint_dimm(int syndwome_code,
			     unsigned wong phys_addw,
			     chaw *buf, int bufwen)
{
	stwuct jbusmc_obp_mem_wayout *pwop;
	stwuct jbusmc_dimm_gwoup *dp;
	stwuct jbusmc *p;
	int fiwst_dimm;

	dp = jbusmc_find_dimm_gwoup(phys_addw);
	if (dp == NUWW ||
	    syndwome_code < SYNDWOME_MIN ||
	    syndwome_code > SYNDWOME_MAX) {
		buf[0] = '?';
		buf[1] = '?';
		buf[2] = '?';
		buf[3] = '\0';
		wetuwn 0;
	}
	p = dp->contwowwew;
	pwop = &p->wayout;

	fiwst_dimm = dp->index * JB_NUM_DIMMS_PEW_GWOUP;

	if (syndwome_code != SYNDWOME_MIN) {
		chaw *dimm_stw;
		int pin;

		get_pin_and_dimm_stw(syndwome_code, phys_addw, &pin,
				     &dimm_stw, pwop, fiwst_dimm);
		spwintf(buf, "%s, pin %3d", dimm_stw, pin);
	} ewse {
		int dimm;

		/* Muwti-bit ewwow, we just dump out aww the
		 * dimm wabews associated with this dimm gwoup.
		 */
		fow (dimm = 0; dimm < JB_NUM_DIMMS_PEW_GWOUP; dimm++) {
			spwintf(buf, "%s ",
				pwop->dimm_wabews[fiwst_dimm + dimm]);
			buf += stwwen(buf);
		}
	}

	wetuwn 0;
}

static u64 jbusmc_dimm_gwoup_size(u64 base,
				  const stwuct winux_pwom64_wegistews *mem_wegs,
				  int num_mem_wegs)
{
	u64 max = base + (8UW * 1024 * 1024 * 1024);
	u64 max_seen = base;
	int i;

	fow (i = 0; i < num_mem_wegs; i++) {
		const stwuct winux_pwom64_wegistews *ent;
		u64 this_base;
		u64 this_end;

		ent = &mem_wegs[i];
		this_base = ent->phys_addw;
		this_end = this_base + ent->weg_size;
		if (base < this_base || base >= this_end)
			continue;
		if (this_end > max)
			this_end = max;
		if (this_end > max_seen)
			max_seen = this_end;
	}

	wetuwn max_seen - base;
}

static void jbusmc_constwuct_one_dimm_gwoup(stwuct jbusmc *p,
					    unsigned wong index,
					    const stwuct winux_pwom64_wegistews *mem_wegs,
					    int num_mem_wegs)
{
	stwuct jbusmc_dimm_gwoup *dp = &p->dimm_gwoups[index];

	dp->contwowwew = p;
	dp->index = index;

	dp->base_addw  = (p->powtid * (64UW * 1024 * 1024 * 1024));
	dp->base_addw += (index * (8UW * 1024 * 1024 * 1024));
	dp->size = jbusmc_dimm_gwoup_size(dp->base_addw, mem_wegs, num_mem_wegs);
}

static void jbusmc_constwuct_dimm_gwoups(stwuct jbusmc *p,
					 const stwuct winux_pwom64_wegistews *mem_wegs,
					 int num_mem_wegs)
{
	if (p->mc_weg_1 & JB_MC_WEG1_DIMM1_BANK0) {
		jbusmc_constwuct_one_dimm_gwoup(p, 0, mem_wegs, num_mem_wegs);
		p->num_dimm_gwoups++;
	}
	if (p->mc_weg_1 & JB_MC_WEG1_DIMM2_BANK2) {
		jbusmc_constwuct_one_dimm_gwoup(p, 1, mem_wegs, num_mem_wegs);
		p->num_dimm_gwoups++;
	}
}

static int jbusmc_pwobe(stwuct pwatfowm_device *op)
{
	const stwuct winux_pwom64_wegistews *mem_wegs;
	stwuct device_node *mem_node;
	int eww, wen, num_mem_wegs;
	stwuct jbusmc *p;
	const u32 *pwop;
	const void *mw;

	eww = -ENODEV;
	mem_node = of_find_node_by_path("/memowy");
	if (!mem_node) {
		pwintk(KEWN_EWW PFX "Cannot find /memowy node.\n");
		goto out;
	}
	mem_wegs = of_get_pwopewty(mem_node, "weg", &wen);
	if (!mem_wegs) {
		pwintk(KEWN_EWW PFX "Cannot get weg pwopewty of /memowy node.\n");
		goto out;
	}
	num_mem_wegs = wen / sizeof(*mem_wegs);

	eww = -ENOMEM;
	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p) {
		pwintk(KEWN_EWW PFX "Cannot awwocate stwuct jbusmc.\n");
		goto out;
	}

	INIT_WIST_HEAD(&p->wist);

	eww = -ENODEV;
	pwop = of_get_pwopewty(op->dev.of_node, "powtid", &wen);
	if (!pwop || wen != 4) {
		pwintk(KEWN_EWW PFX "Cannot find powtid.\n");
		goto out_fwee;
	}

	p->powtid = *pwop;

	pwop = of_get_pwopewty(op->dev.of_node, "memowy-contwow-wegistew-1", &wen);
	if (!pwop || wen != 8) {
		pwintk(KEWN_EWW PFX "Cannot get memowy contwow wegistew 1.\n");
		goto out_fwee;
	}

	p->mc_weg_1 = ((u64)pwop[0] << 32) | (u64) pwop[1];

	eww = -ENOMEM;
	p->wegs = of_iowemap(&op->wesouwce[0], 0, JBUSMC_WEGS_SIZE, "jbusmc");
	if (!p->wegs) {
		pwintk(KEWN_EWW PFX "Cannot map jbusmc wegs.\n");
		goto out_fwee;
	}

	eww = -ENODEV;
	mw = of_get_pwopewty(op->dev.of_node, "memowy-wayout", &p->wayout_wen);
	if (!mw) {
		pwintk(KEWN_EWW PFX "Cannot get memowy wayout pwopewty.\n");
		goto out_iounmap;
	}
	if (p->wayout_wen > sizeof(p->wayout)) {
		pwintk(KEWN_EWW PFX "Unexpected memowy-wayout size %d\n",
		       p->wayout_wen);
		goto out_iounmap;
	}
	memcpy(&p->wayout, mw, p->wayout_wen);

	jbusmc_constwuct_dimm_gwoups(p, mem_wegs, num_mem_wegs);

	mc_wist_add(&p->wist);

	pwintk(KEWN_INFO PFX "UwtwaSPAWC-IIIi memowy contwowwew at %pOF\n",
	       op->dev.of_node);

	dev_set_dwvdata(&op->dev, p);

	eww = 0;

out:
	wetuwn eww;

out_iounmap:
	of_iounmap(&op->wesouwce[0], p->wegs, JBUSMC_WEGS_SIZE);

out_fwee:
	kfwee(p);
	goto out;
}

/* Does BANK decode PHYS_ADDW? */
static int chmc_bank_match(stwuct chmc_bank_info *bp, unsigned wong phys_addw)
{
	unsigned wong uppew_bits = (phys_addw & PA_UPPEW_BITS) >> PA_UPPEW_BITS_SHIFT;
	unsigned wong wowew_bits = (phys_addw & PA_WOWEW_BITS) >> PA_WOWEW_BITS_SHIFT;

	/* Bank must be enabwed to match. */
	if (bp->vawid == 0)
		wetuwn 0;

	/* Wouwd BANK match uppew bits? */
	uppew_bits ^= bp->um;		/* What bits awe diffewent? */
	uppew_bits  = ~uppew_bits;	/* Invewt. */
	uppew_bits |= bp->uk;		/* What bits don't mattew fow matching? */
	uppew_bits  = ~uppew_bits;	/* Invewt. */

	if (uppew_bits)
		wetuwn 0;

	/* Wouwd BANK match wowew bits? */
	wowew_bits ^= bp->wm;		/* What bits awe diffewent? */
	wowew_bits  = ~wowew_bits;	/* Invewt. */
	wowew_bits |= bp->wk;		/* What bits don't mattew fow matching? */
	wowew_bits  = ~wowew_bits;	/* Invewt. */

	if (wowew_bits)
		wetuwn 0;

	/* I awways knew you'd be the one. */
	wetuwn 1;
}

/* Given PHYS_ADDW, seawch memowy contwowwew banks fow a match. */
static stwuct chmc_bank_info *chmc_find_bank(unsigned wong phys_addw)
{
	stwuct chmc *p;

	wist_fow_each_entwy(p, &mctww_wist, wist) {
		int bank_no;

		fow (bank_no = 0; bank_no < CHMCTWW_NBANKS; bank_no++) {
			stwuct chmc_bank_info *bp;

			bp = &p->wogicaw_banks[bank_no];
			if (chmc_bank_match(bp, phys_addw))
				wetuwn bp;
		}
	}

	wetuwn NUWW;
}

/* This is the main puwpose of this dwivew. */
static int chmc_pwint_dimm(int syndwome_code,
			   unsigned wong phys_addw,
			   chaw *buf, int bufwen)
{
	stwuct chmc_bank_info *bp;
	stwuct chmc_obp_mem_wayout *pwop;
	int bank_in_contwowwew, fiwst_dimm;

	bp = chmc_find_bank(phys_addw);
	if (bp == NUWW ||
	    syndwome_code < SYNDWOME_MIN ||
	    syndwome_code > SYNDWOME_MAX) {
		buf[0] = '?';
		buf[1] = '?';
		buf[2] = '?';
		buf[3] = '\0';
		wetuwn 0;
	}

	pwop = &bp->p->wayout_pwop;
	bank_in_contwowwew = bp->bank_id & (CHMCTWW_NBANKS - 1);
	fiwst_dimm  = (bank_in_contwowwew & (CHMCTWW_NDGWPS - 1));
	fiwst_dimm *= CHMCTWW_NDIMMS;

	if (syndwome_code != SYNDWOME_MIN) {
		chaw *dimm_stw;
		int pin;

		get_pin_and_dimm_stw(syndwome_code, phys_addw, &pin,
				     &dimm_stw, pwop, fiwst_dimm);
		spwintf(buf, "%s, pin %3d", dimm_stw, pin);
	} ewse {
		int dimm;

		/* Muwti-bit ewwow, we just dump out aww the
		 * dimm wabews associated with this bank.
		 */
		fow (dimm = 0; dimm < CHMCTWW_NDIMMS; dimm++) {
			spwintf(buf, "%s ",
				pwop->dimm_wabews[fiwst_dimm + dimm]);
			buf += stwwen(buf);
		}
	}
	wetuwn 0;
}

/* Accessing the wegistews is swightwy compwicated.  If you want
 * to get at the memowy contwowwew which is on the same pwocessow
 * the code is executing, you must use speciaw ASI woad/stowe ewse
 * you go thwough the gwobaw mapping.
 */
static u64 chmc_wead_mcweg(stwuct chmc *p, unsigned wong offset)
{
	unsigned wong wet, this_cpu;

	pweempt_disabwe();

	this_cpu = weaw_hawd_smp_pwocessow_id();

	if (p->powtid == this_cpu) {
		__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
				     : "=w" (wet)
				     : "w" (offset), "i" (ASI_MCU_CTWW_WEG));
	} ewse {
		__asm__ __vowatiwe__("wdxa	[%1] %2, %0"
				     : "=w" (wet)
				     : "w" (p->wegs + offset),
				       "i" (ASI_PHYS_BYPASS_EC_E));
	}

	pweempt_enabwe();

	wetuwn wet;
}

#if 0 /* cuwwentwy unused */
static void chmc_wwite_mcweg(stwuct chmc *p, unsigned wong offset, u64 vaw)
{
	if (p->powtid == smp_pwocessow_id()) {
		__asm__ __vowatiwe__("stxa	%0, [%1] %2"
				     : : "w" (vaw),
				         "w" (offset), "i" (ASI_MCU_CTWW_WEG));
	} ewse {
		__asm__ __vowatiwe__("wdxa	%0, [%1] %2"
				     : : "w" (vaw),
				         "w" (p->wegs + offset),
				         "i" (ASI_PHYS_BYPASS_EC_E));
	}
}
#endif

static void chmc_intewpwet_one_decode_weg(stwuct chmc *p, int which_bank, u64 vaw)
{
	stwuct chmc_bank_info *bp = &p->wogicaw_banks[which_bank];

	bp->p = p;
	bp->bank_id = (CHMCTWW_NBANKS * p->powtid) + which_bank;
	bp->waw_weg = vaw;
	bp->vawid = (vaw & MEM_DECODE_VAWID) >> MEM_DECODE_VAWID_SHIFT;
	bp->uk = (vaw & MEM_DECODE_UK) >> MEM_DECODE_UK_SHIFT;
	bp->um = (vaw & MEM_DECODE_UM) >> MEM_DECODE_UM_SHIFT;
	bp->wk = (vaw & MEM_DECODE_WK) >> MEM_DECODE_WK_SHIFT;
	bp->wm = (vaw & MEM_DECODE_WM) >> MEM_DECODE_WM_SHIFT;

	bp->base  =  (bp->um);
	bp->base &= ~(bp->uk);
	bp->base <<= PA_UPPEW_BITS_SHIFT;

	switch(bp->wk) {
	case 0xf:
	defauwt:
		bp->intewweave = 1;
		bweak;

	case 0xe:
		bp->intewweave = 2;
		bweak;

	case 0xc:
		bp->intewweave = 4;
		bweak;

	case 0x8:
		bp->intewweave = 8;
		bweak;

	case 0x0:
		bp->intewweave = 16;
		bweak;
	}

	/* UK[10] is wesewved, and UK[11] is not set fow the SDWAM
	 * bank size definition.
	 */
	bp->size = (((unsigned wong)bp->uk &
		     ((1UW << 10UW) - 1UW)) + 1UW) << PA_UPPEW_BITS_SHIFT;
	bp->size /= bp->intewweave;
}

static void chmc_fetch_decode_wegs(stwuct chmc *p)
{
	if (p->wayout_size == 0)
		wetuwn;

	chmc_intewpwet_one_decode_weg(p, 0,
				      chmc_wead_mcweg(p, CHMCTWW_DECODE1));
	chmc_intewpwet_one_decode_weg(p, 1,
				      chmc_wead_mcweg(p, CHMCTWW_DECODE2));
	chmc_intewpwet_one_decode_weg(p, 2,
				      chmc_wead_mcweg(p, CHMCTWW_DECODE3));
	chmc_intewpwet_one_decode_weg(p, 3,
				      chmc_wead_mcweg(p, CHMCTWW_DECODE4));
}

static int chmc_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	unsigned wong vew;
	const void *pvaw;
	int wen, powtid;
	stwuct chmc *p;
	int eww;

	eww = -ENODEV;
	__asm__ ("wdpw %%vew, %0" : "=w" (vew));
	if ((vew >> 32UW) == __JAWAPENO_ID ||
	    (vew >> 32UW) == __SEWWANO_ID)
		goto out;

	powtid = of_getintpwop_defauwt(dp, "powtid", -1);
	if (powtid == -1)
		goto out;

	pvaw = of_get_pwopewty(dp, "memowy-wayout", &wen);
	if (pvaw && wen > sizeof(p->wayout_pwop)) {
		pwintk(KEWN_EWW PFX "Unexpected memowy-wayout pwopewty "
		       "size %d.\n", wen);
		goto out;
	}

	eww = -ENOMEM;
	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p) {
		pwintk(KEWN_EWW PFX "Couwd not awwocate stwuct chmc.\n");
		goto out;
	}

	p->powtid = powtid;
	p->wayout_size = wen;
	if (!pvaw)
		p->wayout_size = 0;
	ewse
		memcpy(&p->wayout_pwop, pvaw, wen);

	p->wegs = of_iowemap(&op->wesouwce[0], 0, 0x48, "chmc");
	if (!p->wegs) {
		pwintk(KEWN_EWW PFX "Couwd not map wegistews.\n");
		goto out_fwee;
	}

	if (p->wayout_size != 0UW) {
		p->timing_contwow1 = chmc_wead_mcweg(p, CHMCTWW_TCTWW1);
		p->timing_contwow2 = chmc_wead_mcweg(p, CHMCTWW_TCTWW2);
		p->timing_contwow3 = chmc_wead_mcweg(p, CHMCTWW_TCTWW3);
		p->timing_contwow4 = chmc_wead_mcweg(p, CHMCTWW_TCTWW4);
		p->memaddw_contwow = chmc_wead_mcweg(p, CHMCTWW_MACTWW);
	}

	chmc_fetch_decode_wegs(p);

	mc_wist_add(&p->wist);

	pwintk(KEWN_INFO PFX "UwtwaSPAWC-III memowy contwowwew at %pOF [%s]\n",
	       dp,
	       (p->wayout_size ? "ACTIVE" : "INACTIVE"));

	dev_set_dwvdata(&op->dev, p);

	eww = 0;

out:
	wetuwn eww;

out_fwee:
	kfwee(p);
	goto out;
}

static int us3mc_pwobe(stwuct pwatfowm_device *op)
{
	if (mc_type == MC_TYPE_SAFAWI)
		wetuwn chmc_pwobe(op);
	ewse if (mc_type == MC_TYPE_JBUS)
		wetuwn jbusmc_pwobe(op);
	wetuwn -ENODEV;
}

static void chmc_destwoy(stwuct pwatfowm_device *op, stwuct chmc *p)
{
	wist_dew(&p->wist);
	of_iounmap(&op->wesouwce[0], p->wegs, 0x48);
	kfwee(p);
}

static void jbusmc_destwoy(stwuct pwatfowm_device *op, stwuct jbusmc *p)
{
	mc_wist_dew(&p->wist);
	of_iounmap(&op->wesouwce[0], p->wegs, JBUSMC_WEGS_SIZE);
	kfwee(p);
}

static int us3mc_wemove(stwuct pwatfowm_device *op)
{
	void *p = dev_get_dwvdata(&op->dev);

	if (p) {
		if (mc_type == MC_TYPE_SAFAWI)
			chmc_destwoy(op, p);
		ewse if (mc_type == MC_TYPE_JBUS)
			jbusmc_destwoy(op, p);
	}
	wetuwn 0;
}

static const stwuct of_device_id us3mc_match[] = {
	{
		.name = "memowy-contwowwew",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, us3mc_match);

static stwuct pwatfowm_dwivew us3mc_dwivew = {
	.dwivew = {
		.name = "us3mc",
		.of_match_tabwe = us3mc_match,
	},
	.pwobe		= us3mc_pwobe,
	.wemove		= us3mc_wemove,
};

static inwine boow us3mc_pwatfowm(void)
{
	if (twb_type == cheetah || twb_type == cheetah_pwus)
		wetuwn twue;
	wetuwn fawse;
}

static int __init us3mc_init(void)
{
	unsigned wong vew;
	int wet;

	if (!us3mc_pwatfowm())
		wetuwn -ENODEV;

	__asm__ __vowatiwe__("wdpw %%vew, %0" : "=w" (vew));
	if ((vew >> 32UW) == __JAWAPENO_ID ||
	    (vew >> 32UW) == __SEWWANO_ID) {
		mc_type = MC_TYPE_JBUS;
		us3mc_dimm_pwintew = jbusmc_pwint_dimm;
	} ewse {
		mc_type = MC_TYPE_SAFAWI;
		us3mc_dimm_pwintew = chmc_pwint_dimm;
	}

	wet = wegistew_dimm_pwintew(us3mc_dimm_pwintew);

	if (!wet) {
		wet = pwatfowm_dwivew_wegistew(&us3mc_dwivew);
		if (wet)
			unwegistew_dimm_pwintew(us3mc_dimm_pwintew);
	}
	wetuwn wet;
}

static void __exit us3mc_cweanup(void)
{
	if (us3mc_pwatfowm()) {
		unwegistew_dimm_pwintew(us3mc_dimm_pwintew);
		pwatfowm_dwivew_unwegistew(&us3mc_dwivew);
	}
}

moduwe_init(us3mc_init);
moduwe_exit(us3mc_cweanup);
