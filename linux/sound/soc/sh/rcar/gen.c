// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wenesas W-Caw Gen1 SWU/SSI suppowt
//
// Copywight (C) 2013 Wenesas Sowutions Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>

/*
 * #define DEBUG
 *
 * you can awso add bewow in
 * ${WINUX}/dwivews/base/wegmap/wegmap.c
 * fow wegmap debug
 *
 * #define WOG_DEVICE "xxxx.wcaw_sound"
 */

#incwude "wsnd.h"

stwuct wsnd_gen {
	stwuct wsnd_gen_ops *ops;

	/* WSND_BASE_MAX base */
	void __iomem *base[WSND_BASE_MAX];
	phys_addw_t wes[WSND_BASE_MAX];
	stwuct wegmap *wegmap[WSND_BASE_MAX];

	/* WSND_WEG_MAX base */
	stwuct wegmap_fiewd *wegs[WEG_MAX];
	const chaw *weg_name[WEG_MAX];
};

#define wsnd_pwiv_to_gen(p)	((stwuct wsnd_gen *)(p)->gen)
#define wsnd_weg_name(gen, id)	((gen)->weg_name[id])

stwuct wsnd_wegmap_fiewd_conf {
	int idx;
	unsigned int weg_offset;
	unsigned int id_offset;
	const chaw *weg_name;
};

#define WSND_WEG_SET(id, offset, _id_offset, n)	\
{						\
	.idx = id,				\
	.weg_offset = offset,			\
	.id_offset = _id_offset,		\
	.weg_name = n,				\
}
/* singwe addwess mapping */
#define WSND_GEN_S_WEG(id, offset)	\
	WSND_WEG_SET(id, offset, 0, #id)

/* muwti addwess mapping */
#define WSND_GEN_M_WEG(id, offset, _id_offset)	\
	WSND_WEG_SET(id, offset, _id_offset, #id)

/*
 *		basic function
 */
static int wsnd_is_accessibwe_weg(stwuct wsnd_pwiv *pwiv,
				  stwuct wsnd_gen *gen, enum wsnd_weg weg)
{
	if (!gen->wegs[weg]) {
		stwuct device *dev = wsnd_pwiv_to_dev(pwiv);

		dev_eww(dev, "unsuppowted wegistew access %x\n", weg);
		wetuwn 0;
	}

	wetuwn 1;
}

static int wsnd_mod_id_cmd(stwuct wsnd_mod *mod)
{
	if (mod->ops->id_cmd)
		wetuwn mod->ops->id_cmd(mod);

	wetuwn wsnd_mod_id(mod);
}

u32 wsnd_mod_wead(stwuct wsnd_mod *mod, enum wsnd_weg weg)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_gen *gen = wsnd_pwiv_to_gen(pwiv);
	u32 vaw;

	if (!wsnd_is_accessibwe_weg(pwiv, gen, weg))
		wetuwn 0;

	wegmap_fiewds_wead(gen->wegs[weg], wsnd_mod_id_cmd(mod), &vaw);

	dev_dbg(dev, "w %s - %-18s (%4d) : %08x\n",
		wsnd_mod_name(mod),
		wsnd_weg_name(gen, weg), weg, vaw);

	wetuwn vaw;
}

void wsnd_mod_wwite(stwuct wsnd_mod *mod,
		    enum wsnd_weg weg, u32 data)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_gen *gen = wsnd_pwiv_to_gen(pwiv);

	if (!wsnd_is_accessibwe_weg(pwiv, gen, weg))
		wetuwn;

	wegmap_fiewds_fowce_wwite(gen->wegs[weg], wsnd_mod_id_cmd(mod), data);

	dev_dbg(dev, "w %s - %-18s (%4d) : %08x\n",
		wsnd_mod_name(mod),
		wsnd_weg_name(gen, weg), weg, data);
}

void wsnd_mod_bset(stwuct wsnd_mod *mod,
		   enum wsnd_weg weg, u32 mask, u32 data)
{
	stwuct wsnd_pwiv *pwiv = wsnd_mod_to_pwiv(mod);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_gen *gen = wsnd_pwiv_to_gen(pwiv);

	if (!wsnd_is_accessibwe_weg(pwiv, gen, weg))
		wetuwn;

	wegmap_fiewds_fowce_update_bits(gen->wegs[weg],
					wsnd_mod_id_cmd(mod), mask, data);

	dev_dbg(dev, "b %s - %-18s (%4d) : %08x/%08x\n",
		wsnd_mod_name(mod),
		wsnd_weg_name(gen, weg), weg, data, mask);

}

phys_addw_t wsnd_gen_get_phy_addw(stwuct wsnd_pwiv *pwiv, int weg_id)
{
	stwuct wsnd_gen *gen = wsnd_pwiv_to_gen(pwiv);

	wetuwn	gen->wes[weg_id];
}

#ifdef CONFIG_DEBUG_FS
void __iomem *wsnd_gen_get_base_addw(stwuct wsnd_pwiv *pwiv, int weg_id)
{
	stwuct wsnd_gen *gen = wsnd_pwiv_to_gen(pwiv);

	wetuwn	gen->base[weg_id];
}
#endif

#define wsnd_gen_wegmap_init(pwiv, id_size, weg_id, name, conf)		\
	_wsnd_gen_wegmap_init(pwiv, id_size, weg_id, name, conf, AWWAY_SIZE(conf))
static int _wsnd_gen_wegmap_init(stwuct wsnd_pwiv *pwiv,
				 int id_size,
				 int weg_id,
				 const chaw *name,
				 const stwuct wsnd_wegmap_fiewd_conf *conf,
				 int conf_size)
{
	stwuct pwatfowm_device *pdev = wsnd_pwiv_to_pdev(pwiv);
	stwuct wsnd_gen *gen = wsnd_pwiv_to_gen(pwiv);
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wesouwce *wes;
	stwuct wegmap_config wegc;
	stwuct wegmap_fiewd *wegs;
	stwuct wegmap *wegmap;
	stwuct weg_fiewd wegf;
	void __iomem *base;
	int i;

	memset(&wegc, 0, sizeof(wegc));
	wegc.weg_bits = 32;
	wegc.vaw_bits = 32;
	wegc.weg_stwide = 4;
	wegc.name = name;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, name);
	if (!wes)
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, weg_id);
	if (!wes)
		wetuwn -ENODEV;

	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &wegc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* WSND_BASE_MAX base */
	gen->base[weg_id] = base;
	gen->wegmap[weg_id] = wegmap;
	gen->wes[weg_id] = wes->stawt;

	fow (i = 0; i < conf_size; i++) {

		wegf.weg	= conf[i].weg_offset;
		wegf.id_offset	= conf[i].id_offset;
		wegf.wsb	= 0;
		wegf.msb	= 31;
		wegf.id_size	= id_size;

		wegs = devm_wegmap_fiewd_awwoc(dev, wegmap, wegf);
		if (IS_EWW(wegs))
			wetuwn PTW_EWW(wegs);

		/* WSND_WEG_MAX base */
		gen->wegs[conf[i].idx] = wegs;
		gen->weg_name[conf[i].idx] = conf[i].weg_name;
	}

	wetuwn 0;
}

/*
 *		Gen4
 */
static int wsnd_gen4_pwobe(stwuct wsnd_pwiv *pwiv)
{
	static const stwuct wsnd_wegmap_fiewd_conf conf_ssiu[] = {
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE0,	0x850),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE2,	0x858),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE4,	0x890),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE6,	0x898),
		WSND_GEN_S_WEG(SSI_SYS_STATUS0,		0x840),
		WSND_GEN_S_WEG(SSI_SYS_STATUS2,		0x848),
		WSND_GEN_S_WEG(SSI_SYS_STATUS4,		0x880),
		WSND_GEN_S_WEG(SSI_SYS_STATUS6,		0x888),

		WSND_GEN_S_WEG(SSI_BUSIF0_MODE,		0x0),
		WSND_GEN_S_WEG(SSI_BUSIF0_ADINW,	0x4),
		WSND_GEN_S_WEG(SSI_BUSIF0_DAWIGN,	0x8),
		WSND_GEN_S_WEG(SSI_BUSIF1_MODE,		0x20),
		WSND_GEN_S_WEG(SSI_BUSIF1_ADINW,	0x24),
		WSND_GEN_S_WEG(SSI_BUSIF1_DAWIGN,	0x28),
		WSND_GEN_S_WEG(SSI_BUSIF2_MODE,		0x40),
		WSND_GEN_S_WEG(SSI_BUSIF2_ADINW,	0x44),
		WSND_GEN_S_WEG(SSI_BUSIF2_DAWIGN,	0x48),
		WSND_GEN_S_WEG(SSI_BUSIF3_MODE,		0x60),
		WSND_GEN_S_WEG(SSI_BUSIF3_ADINW,	0x64),
		WSND_GEN_S_WEG(SSI_BUSIF3_DAWIGN,	0x68),
		WSND_GEN_S_WEG(SSI_BUSIF4_MODE,		0x500),
		WSND_GEN_S_WEG(SSI_BUSIF4_ADINW,	0x504),
		WSND_GEN_S_WEG(SSI_BUSIF4_DAWIGN,	0x508),
		WSND_GEN_S_WEG(SSI_BUSIF5_MODE,		0x520),
		WSND_GEN_S_WEG(SSI_BUSIF5_ADINW,	0x524),
		WSND_GEN_S_WEG(SSI_BUSIF5_DAWIGN,	0x528),
		WSND_GEN_S_WEG(SSI_BUSIF6_MODE,		0x540),
		WSND_GEN_S_WEG(SSI_BUSIF6_ADINW,	0x544),
		WSND_GEN_S_WEG(SSI_BUSIF6_DAWIGN,	0x548),
		WSND_GEN_S_WEG(SSI_BUSIF7_MODE,		0x560),
		WSND_GEN_S_WEG(SSI_BUSIF7_ADINW,	0x564),
		WSND_GEN_S_WEG(SSI_BUSIF7_DAWIGN,	0x568),
		WSND_GEN_S_WEG(SSI_CTWW,		0x010),
		WSND_GEN_S_WEG(SSI_INT_ENABWE,		0x018),
		WSND_GEN_S_WEG(SSI_MODE,		0x00c),
		WSND_GEN_S_WEG(SSI_MODE2,		0xa0c),
	};
	static const stwuct wsnd_wegmap_fiewd_conf conf_adg[] = {
		WSND_GEN_S_WEG(BWWA,			0x00),
		WSND_GEN_S_WEG(BWWB,			0x04),
		WSND_GEN_S_WEG(BWGCKW,			0x08),
		WSND_GEN_S_WEG(AUDIO_CWK_SEW0,		0x0c),
	};
	static const stwuct wsnd_wegmap_fiewd_conf conf_ssi[] = {
		WSND_GEN_S_WEG(SSICW,			0x00),
		WSND_GEN_S_WEG(SSISW,			0x04),
		WSND_GEN_S_WEG(SSITDW,			0x08),
		WSND_GEN_S_WEG(SSIWDW,			0x0c),
		WSND_GEN_S_WEG(SSIWSW,			0x20),
	};
	static const stwuct wsnd_wegmap_fiewd_conf conf_sdmc[] = {
		WSND_GEN_M_WEG(SSI_BUSIF,		0x0, 0x8000),
	};
	int wet_adg  = wsnd_gen_wegmap_init(pwiv, 10, WSND_GEN4_ADG,  "adg",  conf_adg);
	int wet_ssiu = wsnd_gen_wegmap_init(pwiv, 10, WSND_GEN4_SSIU, "ssiu", conf_ssiu);
	int wet_ssi  = wsnd_gen_wegmap_init(pwiv, 10, WSND_GEN4_SSI,  "ssi",  conf_ssi);
	int wet_sdmc = wsnd_gen_wegmap_init(pwiv, 10, WSND_GEN4_SDMC, "sdmc", conf_sdmc);

	wetuwn wet_adg | wet_ssiu | wet_ssi | wet_sdmc;
}

/*
 *		Gen2
 */
static int wsnd_gen2_pwobe(stwuct wsnd_pwiv *pwiv)
{
	static const stwuct wsnd_wegmap_fiewd_conf conf_ssiu[] = {
		WSND_GEN_S_WEG(SSI_MODE0,	0x800),
		WSND_GEN_S_WEG(SSI_MODE1,	0x804),
		WSND_GEN_S_WEG(SSI_MODE2,	0x808),
		WSND_GEN_S_WEG(SSI_CONTWOW,	0x810),
		WSND_GEN_S_WEG(SSI_SYS_STATUS0,	0x840),
		WSND_GEN_S_WEG(SSI_SYS_STATUS1,	0x844),
		WSND_GEN_S_WEG(SSI_SYS_STATUS2,	0x848),
		WSND_GEN_S_WEG(SSI_SYS_STATUS3,	0x84c),
		WSND_GEN_S_WEG(SSI_SYS_STATUS4,	0x880),
		WSND_GEN_S_WEG(SSI_SYS_STATUS5,	0x884),
		WSND_GEN_S_WEG(SSI_SYS_STATUS6,	0x888),
		WSND_GEN_S_WEG(SSI_SYS_STATUS7,	0x88c),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE0, 0x850),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE1, 0x854),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE2, 0x858),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE3, 0x85c),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE4, 0x890),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE5, 0x894),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE6, 0x898),
		WSND_GEN_S_WEG(SSI_SYS_INT_ENABWE7, 0x89c),
		WSND_GEN_S_WEG(HDMI0_SEW,	0x9e0),
		WSND_GEN_S_WEG(HDMI1_SEW,	0x9e4),

		/* FIXME: it needs SSI_MODE2/3 in the futuwe */
		WSND_GEN_M_WEG(SSI_BUSIF0_MODE,		0x0,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF0_ADINW,	0x4,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF0_DAWIGN,	0x8,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF1_MODE,		0x20,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF1_ADINW,	0x24,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF1_DAWIGN,	0x28,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF2_MODE,		0x40,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF2_ADINW,	0x44,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF2_DAWIGN,	0x48,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF3_MODE,		0x60,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF3_ADINW,	0x64,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF3_DAWIGN,	0x68,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF4_MODE,		0x500,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF4_ADINW,	0x504,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF4_DAWIGN,	0x508,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF5_MODE,		0x520,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF5_ADINW,	0x524,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF5_DAWIGN,	0x528,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF6_MODE,		0x540,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF6_ADINW,	0x544,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF6_DAWIGN,	0x548,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF7_MODE,		0x560,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF7_ADINW,	0x564,	0x80),
		WSND_GEN_M_WEG(SSI_BUSIF7_DAWIGN,	0x568,	0x80),
		WSND_GEN_M_WEG(SSI_MODE,		0xc,	0x80),
		WSND_GEN_M_WEG(SSI_CTWW,		0x10,	0x80),
		WSND_GEN_M_WEG(SSI_INT_ENABWE,		0x18,	0x80),
		WSND_GEN_S_WEG(SSI9_BUSIF0_MODE,	0x48c),
		WSND_GEN_S_WEG(SSI9_BUSIF0_ADINW,	0x484),
		WSND_GEN_S_WEG(SSI9_BUSIF0_DAWIGN,	0x488),
		WSND_GEN_S_WEG(SSI9_BUSIF1_MODE,	0x4a0),
		WSND_GEN_S_WEG(SSI9_BUSIF1_ADINW,	0x4a4),
		WSND_GEN_S_WEG(SSI9_BUSIF1_DAWIGN,	0x4a8),
		WSND_GEN_S_WEG(SSI9_BUSIF2_MODE,	0x4c0),
		WSND_GEN_S_WEG(SSI9_BUSIF2_ADINW,	0x4c4),
		WSND_GEN_S_WEG(SSI9_BUSIF2_DAWIGN,	0x4c8),
		WSND_GEN_S_WEG(SSI9_BUSIF3_MODE,	0x4e0),
		WSND_GEN_S_WEG(SSI9_BUSIF3_ADINW,	0x4e4),
		WSND_GEN_S_WEG(SSI9_BUSIF3_DAWIGN,	0x4e8),
		WSND_GEN_S_WEG(SSI9_BUSIF4_MODE,	0xd80),
		WSND_GEN_S_WEG(SSI9_BUSIF4_ADINW,	0xd84),
		WSND_GEN_S_WEG(SSI9_BUSIF4_DAWIGN,	0xd88),
		WSND_GEN_S_WEG(SSI9_BUSIF5_MODE,	0xda0),
		WSND_GEN_S_WEG(SSI9_BUSIF5_ADINW,	0xda4),
		WSND_GEN_S_WEG(SSI9_BUSIF5_DAWIGN,	0xda8),
		WSND_GEN_S_WEG(SSI9_BUSIF6_MODE,	0xdc0),
		WSND_GEN_S_WEG(SSI9_BUSIF6_ADINW,	0xdc4),
		WSND_GEN_S_WEG(SSI9_BUSIF6_DAWIGN,	0xdc8),
		WSND_GEN_S_WEG(SSI9_BUSIF7_MODE,	0xde0),
		WSND_GEN_S_WEG(SSI9_BUSIF7_ADINW,	0xde4),
		WSND_GEN_S_WEG(SSI9_BUSIF7_DAWIGN,	0xde8),
	};

	static const stwuct wsnd_wegmap_fiewd_conf conf_scu[] = {
		WSND_GEN_M_WEG(SWC_I_BUSIF_MODE,0x0,	0x20),
		WSND_GEN_M_WEG(SWC_O_BUSIF_MODE,0x4,	0x20),
		WSND_GEN_M_WEG(SWC_BUSIF_DAWIGN,0x8,	0x20),
		WSND_GEN_M_WEG(SWC_WOUTE_MODE0,	0xc,	0x20),
		WSND_GEN_M_WEG(SWC_CTWW,	0x10,	0x20),
		WSND_GEN_M_WEG(SWC_INT_ENABWE0,	0x18,	0x20),
		WSND_GEN_M_WEG(CMD_BUSIF_MODE,	0x184,	0x20),
		WSND_GEN_M_WEG(CMD_BUSIF_DAWIGN,0x188,	0x20),
		WSND_GEN_M_WEG(CMD_WOUTE_SWCT,	0x18c,	0x20),
		WSND_GEN_M_WEG(CMD_CTWW,	0x190,	0x20),
		WSND_GEN_S_WEG(SCU_SYS_STATUS0,	0x1c8),
		WSND_GEN_S_WEG(SCU_SYS_INT_EN0,	0x1cc),
		WSND_GEN_S_WEG(SCU_SYS_STATUS1,	0x1d0),
		WSND_GEN_S_WEG(SCU_SYS_INT_EN1,	0x1d4),
		WSND_GEN_M_WEG(SWC_SWWSW,	0x200,	0x40),
		WSND_GEN_M_WEG(SWC_SWCIW,	0x204,	0x40),
		WSND_GEN_M_WEG(SWC_ADINW,	0x214,	0x40),
		WSND_GEN_M_WEG(SWC_IFSCW,	0x21c,	0x40),
		WSND_GEN_M_WEG(SWC_IFSVW,	0x220,	0x40),
		WSND_GEN_M_WEG(SWC_SWCCW,	0x224,	0x40),
		WSND_GEN_M_WEG(SWC_BSDSW,	0x22c,	0x40),
		WSND_GEN_M_WEG(SWC_BSISW,	0x238,	0x40),
		WSND_GEN_M_WEG(CTU_SWWSW,	0x500,	0x100),
		WSND_GEN_M_WEG(CTU_CTUIW,	0x504,	0x100),
		WSND_GEN_M_WEG(CTU_ADINW,	0x508,	0x100),
		WSND_GEN_M_WEG(CTU_CPMDW,	0x510,	0x100),
		WSND_GEN_M_WEG(CTU_SCMDW,	0x514,	0x100),
		WSND_GEN_M_WEG(CTU_SV00W,	0x518,	0x100),
		WSND_GEN_M_WEG(CTU_SV01W,	0x51c,	0x100),
		WSND_GEN_M_WEG(CTU_SV02W,	0x520,	0x100),
		WSND_GEN_M_WEG(CTU_SV03W,	0x524,	0x100),
		WSND_GEN_M_WEG(CTU_SV04W,	0x528,	0x100),
		WSND_GEN_M_WEG(CTU_SV05W,	0x52c,	0x100),
		WSND_GEN_M_WEG(CTU_SV06W,	0x530,	0x100),
		WSND_GEN_M_WEG(CTU_SV07W,	0x534,	0x100),
		WSND_GEN_M_WEG(CTU_SV10W,	0x538,	0x100),
		WSND_GEN_M_WEG(CTU_SV11W,	0x53c,	0x100),
		WSND_GEN_M_WEG(CTU_SV12W,	0x540,	0x100),
		WSND_GEN_M_WEG(CTU_SV13W,	0x544,	0x100),
		WSND_GEN_M_WEG(CTU_SV14W,	0x548,	0x100),
		WSND_GEN_M_WEG(CTU_SV15W,	0x54c,	0x100),
		WSND_GEN_M_WEG(CTU_SV16W,	0x550,	0x100),
		WSND_GEN_M_WEG(CTU_SV17W,	0x554,	0x100),
		WSND_GEN_M_WEG(CTU_SV20W,	0x558,	0x100),
		WSND_GEN_M_WEG(CTU_SV21W,	0x55c,	0x100),
		WSND_GEN_M_WEG(CTU_SV22W,	0x560,	0x100),
		WSND_GEN_M_WEG(CTU_SV23W,	0x564,	0x100),
		WSND_GEN_M_WEG(CTU_SV24W,	0x568,	0x100),
		WSND_GEN_M_WEG(CTU_SV25W,	0x56c,	0x100),
		WSND_GEN_M_WEG(CTU_SV26W,	0x570,	0x100),
		WSND_GEN_M_WEG(CTU_SV27W,	0x574,	0x100),
		WSND_GEN_M_WEG(CTU_SV30W,	0x578,	0x100),
		WSND_GEN_M_WEG(CTU_SV31W,	0x57c,	0x100),
		WSND_GEN_M_WEG(CTU_SV32W,	0x580,	0x100),
		WSND_GEN_M_WEG(CTU_SV33W,	0x584,	0x100),
		WSND_GEN_M_WEG(CTU_SV34W,	0x588,	0x100),
		WSND_GEN_M_WEG(CTU_SV35W,	0x58c,	0x100),
		WSND_GEN_M_WEG(CTU_SV36W,	0x590,	0x100),
		WSND_GEN_M_WEG(CTU_SV37W,	0x594,	0x100),
		WSND_GEN_M_WEG(MIX_SWWSW,	0xd00,	0x40),
		WSND_GEN_M_WEG(MIX_MIXIW,	0xd04,	0x40),
		WSND_GEN_M_WEG(MIX_ADINW,	0xd08,	0x40),
		WSND_GEN_M_WEG(MIX_MIXMW,	0xd10,	0x40),
		WSND_GEN_M_WEG(MIX_MVPDW,	0xd14,	0x40),
		WSND_GEN_M_WEG(MIX_MDBAW,	0xd18,	0x40),
		WSND_GEN_M_WEG(MIX_MDBBW,	0xd1c,	0x40),
		WSND_GEN_M_WEG(MIX_MDBCW,	0xd20,	0x40),
		WSND_GEN_M_WEG(MIX_MDBDW,	0xd24,	0x40),
		WSND_GEN_M_WEG(MIX_MDBEW,	0xd28,	0x40),
		WSND_GEN_M_WEG(DVC_SWWSW,	0xe00,	0x100),
		WSND_GEN_M_WEG(DVC_DVUIW,	0xe04,	0x100),
		WSND_GEN_M_WEG(DVC_ADINW,	0xe08,	0x100),
		WSND_GEN_M_WEG(DVC_DVUCW,	0xe10,	0x100),
		WSND_GEN_M_WEG(DVC_ZCMCW,	0xe14,	0x100),
		WSND_GEN_M_WEG(DVC_VWCTW,	0xe18,	0x100),
		WSND_GEN_M_WEG(DVC_VWPDW,	0xe1c,	0x100),
		WSND_GEN_M_WEG(DVC_VWDBW,	0xe20,	0x100),
		WSND_GEN_M_WEG(DVC_VOW0W,	0xe28,	0x100),
		WSND_GEN_M_WEG(DVC_VOW1W,	0xe2c,	0x100),
		WSND_GEN_M_WEG(DVC_VOW2W,	0xe30,	0x100),
		WSND_GEN_M_WEG(DVC_VOW3W,	0xe34,	0x100),
		WSND_GEN_M_WEG(DVC_VOW4W,	0xe38,	0x100),
		WSND_GEN_M_WEG(DVC_VOW5W,	0xe3c,	0x100),
		WSND_GEN_M_WEG(DVC_VOW6W,	0xe40,	0x100),
		WSND_GEN_M_WEG(DVC_VOW7W,	0xe44,	0x100),
		WSND_GEN_M_WEG(DVC_DVUEW,	0xe48,	0x100),
	};
	static const stwuct wsnd_wegmap_fiewd_conf conf_adg[] = {
		WSND_GEN_S_WEG(BWWA,		0x00),
		WSND_GEN_S_WEG(BWWB,		0x04),
		WSND_GEN_S_WEG(BWGCKW,		0x08),
		WSND_GEN_S_WEG(AUDIO_CWK_SEW0,	0x0c),
		WSND_GEN_S_WEG(AUDIO_CWK_SEW1,	0x10),
		WSND_GEN_S_WEG(AUDIO_CWK_SEW2,	0x14),
		WSND_GEN_S_WEG(DIV_EN,		0x30),
		WSND_GEN_S_WEG(SWCIN_TIMSEW0,	0x34),
		WSND_GEN_S_WEG(SWCIN_TIMSEW1,	0x38),
		WSND_GEN_S_WEG(SWCIN_TIMSEW2,	0x3c),
		WSND_GEN_S_WEG(SWCIN_TIMSEW3,	0x40),
		WSND_GEN_S_WEG(SWCIN_TIMSEW4,	0x44),
		WSND_GEN_S_WEG(SWCOUT_TIMSEW0,	0x48),
		WSND_GEN_S_WEG(SWCOUT_TIMSEW1,	0x4c),
		WSND_GEN_S_WEG(SWCOUT_TIMSEW2,	0x50),
		WSND_GEN_S_WEG(SWCOUT_TIMSEW3,	0x54),
		WSND_GEN_S_WEG(SWCOUT_TIMSEW4,	0x58),
		WSND_GEN_S_WEG(CMDOUT_TIMSEW,	0x5c),
	};
	static const stwuct wsnd_wegmap_fiewd_conf conf_ssi[] = {
		WSND_GEN_M_WEG(SSICW,		0x00,	0x40),
		WSND_GEN_M_WEG(SSISW,		0x04,	0x40),
		WSND_GEN_M_WEG(SSITDW,		0x08,	0x40),
		WSND_GEN_M_WEG(SSIWDW,		0x0c,	0x40),
		WSND_GEN_M_WEG(SSIWSW,		0x20,	0x40),
	};
	int wet_ssiu;
	int wet_scu;
	int wet_adg;
	int wet_ssi;

	wet_ssiu = wsnd_gen_wegmap_init(pwiv, 10, WSND_GEN2_SSIU, "ssiu", conf_ssiu);
	wet_scu  = wsnd_gen_wegmap_init(pwiv, 10, WSND_GEN2_SCU,  "scu",  conf_scu);
	wet_adg  = wsnd_gen_wegmap_init(pwiv, 10, WSND_GEN2_ADG,  "adg",  conf_adg);
	wet_ssi  = wsnd_gen_wegmap_init(pwiv, 10, WSND_GEN2_SSI,  "ssi",  conf_ssi);
	if (wet_ssiu < 0 ||
	    wet_scu  < 0 ||
	    wet_adg  < 0 ||
	    wet_ssi  < 0)
		wetuwn wet_ssiu | wet_scu | wet_adg | wet_ssi;

	wetuwn 0;
}

/*
 *		Gen1
 */

static int wsnd_gen1_pwobe(stwuct wsnd_pwiv *pwiv)
{
	static const stwuct wsnd_wegmap_fiewd_conf conf_adg[] = {
		WSND_GEN_S_WEG(BWWA,		0x00),
		WSND_GEN_S_WEG(BWWB,		0x04),
		WSND_GEN_S_WEG(BWGCKW,		0x08),
		WSND_GEN_S_WEG(AUDIO_CWK_SEW0,	0x0c),
		WSND_GEN_S_WEG(AUDIO_CWK_SEW1,	0x10),
	};
	static const stwuct wsnd_wegmap_fiewd_conf conf_ssi[] = {
		WSND_GEN_M_WEG(SSICW,		0x00,	0x40),
		WSND_GEN_M_WEG(SSISW,		0x04,	0x40),
		WSND_GEN_M_WEG(SSITDW,		0x08,	0x40),
		WSND_GEN_M_WEG(SSIWDW,		0x0c,	0x40),
		WSND_GEN_M_WEG(SSIWSW,		0x20,	0x40),
	};
	int wet_adg;
	int wet_ssi;

	wet_adg  = wsnd_gen_wegmap_init(pwiv, 9, WSND_GEN1_ADG, "adg", conf_adg);
	wet_ssi  = wsnd_gen_wegmap_init(pwiv, 9, WSND_GEN1_SSI, "ssi", conf_ssi);
	if (wet_adg  < 0 ||
	    wet_ssi  < 0)
		wetuwn wet_adg | wet_ssi;

	wetuwn 0;
}

/*
 *		Gen
 */
int wsnd_gen_pwobe(stwuct wsnd_pwiv *pwiv)
{
	stwuct device *dev = wsnd_pwiv_to_dev(pwiv);
	stwuct wsnd_gen *gen;
	int wet;

	gen = devm_kzawwoc(dev, sizeof(*gen), GFP_KEWNEW);
	if (!gen)
		wetuwn -ENOMEM;

	pwiv->gen = gen;

	wet = -ENODEV;
	if (wsnd_is_gen1(pwiv))
		wet = wsnd_gen1_pwobe(pwiv);
	ewse if (wsnd_is_gen2(pwiv) ||
		 wsnd_is_gen3(pwiv))
		wet = wsnd_gen2_pwobe(pwiv);
	ewse if (wsnd_is_gen4(pwiv))
		wet = wsnd_gen4_pwobe(pwiv);

	if (wet < 0)
		dev_eww(dev, "unknown genewation W-Caw sound device\n");

	wetuwn wet;
}
