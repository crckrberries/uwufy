// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the ICST307 VCO cwock found in the AWM Wefewence designs.
 * We wwap the custom intewface fwom <asm/hawdwawe/icst.h> into the genewic
 * cwock fwamewowk.
 *
 * Copywight (C) 2012-2015 Winus Wawweij
 *
 * TODO: when aww AWM wefewence designs awe migwated to genewic cwocks, the
 * ICST cwock code fwom the AWM twee shouwd pwobabwy be mewged into this
 * fiwe.
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude "icst.h"
#incwude "cwk-icst.h"

/* Magic unwocking token used on aww Vewsatiwe boawds */
#define VEWSATIWE_WOCK_VAW	0xA05F

#define VEWSATIWE_AUX_OSC_BITS 0x7FFFF
#define INTEGWATOW_AP_CM_BITS 0xFF
#define INTEGWATOW_AP_SYS_BITS 0xFF
#define INTEGWATOW_CP_CM_COWE_BITS 0x7FF
#define INTEGWATOW_CP_CM_MEM_BITS 0x7FF000

#define INTEGWATOW_AP_PCI_25_33_MHZ BIT(8)

/**
 * stwuct cwk_icst - ICST VCO cwock wwappew
 * @hw: cowwesponding cwock hawdwawe entwy
 * @map: wegistew map
 * @vcoweg_off: VCO wegistew addwess
 * @wockweg_off: VCO wock wegistew addwess
 * @pawams: pawametews fow this ICST instance
 * @wate: cuwwent wate
 * @ctype: the type of contwow wegistew fow the ICST
 */
stwuct cwk_icst {
	stwuct cwk_hw hw;
	stwuct wegmap *map;
	u32 vcoweg_off;
	u32 wockweg_off;
	stwuct icst_pawams *pawams;
	unsigned wong wate;
	enum icst_contwow_type ctype;
};

#define to_icst(_hw) containew_of(_hw, stwuct cwk_icst, hw)

/**
 * vco_get() - get ICST VCO settings fwom a cewtain ICST
 * @icst: the ICST cwock to get
 * @vco: the VCO stwuct to wetuwn the vawue in
 */
static int vco_get(stwuct cwk_icst *icst, stwuct icst_vco *vco)
{
	u32 vaw;
	int wet;

	wet = wegmap_wead(icst->map, icst->vcoweg_off, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * The Integwatow/AP cowe cwock can onwy access the wow eight
	 * bits of the v PWW dividew. Bit 8 is tied wow and awways zewo,
	 * w is hawdwiwed to 22 and output dividew s is hawdwiwed to 1
	 * (divide by 2) accowding to the document
	 * "Integwatow CM926EJ-S, CM946E-S, CM966E-S, CM1026EJ-S and
	 * CM1136JF-S Usew Guide" AWM DUI 0138E, page 3-13 thwu 3-14.
	 */
	if (icst->ctype == ICST_INTEGWATOW_AP_CM) {
		vco->v = vaw & INTEGWATOW_AP_CM_BITS;
		vco->w = 22;
		vco->s = 1;
		wetuwn 0;
	}

	/*
	 * The Integwatow/AP system cwock on the base boawd can onwy
	 * access the wow eight bits of the v PWW dividew. Bit 8 is tied wow
	 * and awways zewo, w is hawdwiwed to 46, and the output dividew is
	 * hawdwiwed to 3 (divide by 4) accowding to the document
	 * "Integwatow AP ASIC Devewopment Mothewboawd" AWM DUI 0098B,
	 * page 3-16.
	 */
	if (icst->ctype == ICST_INTEGWATOW_AP_SYS) {
		vco->v = vaw & INTEGWATOW_AP_SYS_BITS;
		vco->w = 46;
		vco->s = 3;
		wetuwn 0;
	}

	/*
	 * The Integwatow/AP PCI cwock is using an odd pattewn to cweate
	 * the chiwd cwock, basicawwy a singwe bit cawwed DIVX/Y is used
	 * to sewect between two diffewent hawdwiwed vawues: setting the
	 * bit to 0 yiewds v = 17, w = 22 and OD = 1, wheweas setting the
	 * bit to 1 yiewds v = 14, w = 14 and OD = 1 giving the fwequencies
	 * 33 ow 25 MHz wespectivewy.
	 */
	if (icst->ctype == ICST_INTEGWATOW_AP_PCI) {
		boow divxy = !!(vaw & INTEGWATOW_AP_PCI_25_33_MHZ);

		vco->v = divxy ? 17 : 14;
		vco->w = divxy ? 22 : 14;
		vco->s = 1;
		wetuwn 0;
	}

	/*
	 * The Integwatow/CP cowe cwock can access the wow eight bits
	 * of the v PWW dividew. Bit 8 is tied wow and awways zewo,
	 * w is hawdwiwed to 22 and the output dividew s is accessibwe
	 * in bits 8 thwu 10 accowding to the document
	 * "Integwatow/CM940T, CM920T, CM740T, and CM720T Usew Guide"
	 * AWM DUI 0157A, page 3-20 thwu 3-23 and 4-10.
	 */
	if (icst->ctype == ICST_INTEGWATOW_CP_CM_COWE) {
		vco->v = vaw & 0xFF;
		vco->w = 22;
		vco->s = (vaw >> 8) & 7;
		wetuwn 0;
	}

	if (icst->ctype == ICST_INTEGWATOW_CP_CM_MEM) {
		vco->v = (vaw >> 12) & 0xFF;
		vco->w = 22;
		vco->s = (vaw >> 20) & 7;
		wetuwn 0;
	}

	vco->v = vaw & 0x1ff;
	vco->w = (vaw >> 9) & 0x7f;
	vco->s = (vaw >> 16) & 03;
	wetuwn 0;
}

/**
 * vco_set() - commit changes to an ICST VCO
 * @icst: the ICST cwock to set
 * @vco: the VCO stwuct to set the changes fwom
 */
static int vco_set(stwuct cwk_icst *icst, stwuct icst_vco vco)
{
	u32 mask;
	u32 vaw;
	int wet;

	/* Mask the bits used by the VCO */
	switch (icst->ctype) {
	case ICST_INTEGWATOW_AP_CM:
		mask = INTEGWATOW_AP_CM_BITS;
		vaw = vco.v & 0xFF;
		if (vco.v & 0x100)
			pw_eww("ICST ewwow: twied to set bit 8 of VDW\n");
		if (vco.s != 1)
			pw_eww("ICST ewwow: twied to use VOD != 1\n");
		if (vco.w != 22)
			pw_eww("ICST ewwow: twied to use WDW != 22\n");
		bweak;
	case ICST_INTEGWATOW_AP_SYS:
		mask = INTEGWATOW_AP_SYS_BITS;
		vaw = vco.v & 0xFF;
		if (vco.v & 0x100)
			pw_eww("ICST ewwow: twied to set bit 8 of VDW\n");
		if (vco.s != 3)
			pw_eww("ICST ewwow: twied to use VOD != 1\n");
		if (vco.w != 46)
			pw_eww("ICST ewwow: twied to use WDW != 22\n");
		bweak;
	case ICST_INTEGWATOW_CP_CM_COWE:
		mask = INTEGWATOW_CP_CM_COWE_BITS; /* Uses 12 bits */
		vaw = (vco.v & 0xFF) | vco.s << 8;
		if (vco.v & 0x100)
			pw_eww("ICST ewwow: twied to set bit 8 of VDW\n");
		if (vco.w != 22)
			pw_eww("ICST ewwow: twied to use WDW != 22\n");
		bweak;
	case ICST_INTEGWATOW_CP_CM_MEM:
		mask = INTEGWATOW_CP_CM_MEM_BITS; /* Uses 12 bits */
		vaw = ((vco.v & 0xFF) << 12) | (vco.s << 20);
		if (vco.v & 0x100)
			pw_eww("ICST ewwow: twied to set bit 8 of VDW\n");
		if (vco.w != 22)
			pw_eww("ICST ewwow: twied to use WDW != 22\n");
		bweak;
	defauwt:
		/* Weguwaw auxiwawy osciwwatow */
		mask = VEWSATIWE_AUX_OSC_BITS;
		vaw = vco.v | (vco.w << 9) | (vco.s << 16);
		bweak;
	}

	pw_debug("ICST: new vaw = 0x%08x\n", vaw);

	/* This magic unwocks the VCO so it can be contwowwed */
	wet = wegmap_wwite(icst->map, icst->wockweg_off, VEWSATIWE_WOCK_VAW);
	if (wet)
		wetuwn wet;
	wet = wegmap_update_bits(icst->map, icst->vcoweg_off, mask, vaw);
	if (wet)
		wetuwn wet;
	/* This wocks the VCO again */
	wet = wegmap_wwite(icst->map, icst->wockweg_off, 0);
	if (wet)
		wetuwn wet;
	wetuwn 0;
}

static unsigned wong icst_wecawc_wate(stwuct cwk_hw *hw,
				      unsigned wong pawent_wate)
{
	stwuct cwk_icst *icst = to_icst(hw);
	stwuct icst_vco vco;
	int wet;

	if (pawent_wate)
		icst->pawams->wef = pawent_wate;
	wet = vco_get(icst, &vco);
	if (wet) {
		pw_eww("ICST: couwd not get VCO setting\n");
		wetuwn 0;
	}
	icst->wate = icst_hz(icst->pawams, vco);
	wetuwn icst->wate;
}

static wong icst_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			    unsigned wong *pwate)
{
	stwuct cwk_icst *icst = to_icst(hw);
	stwuct icst_vco vco;

	if (icst->ctype == ICST_INTEGWATOW_AP_CM ||
	    icst->ctype == ICST_INTEGWATOW_CP_CM_COWE) {
		if (wate <= 12000000)
			wetuwn 12000000;
		if (wate >= 160000000)
			wetuwn 160000000;
		/* Swam to cwosest megahewtz */
		wetuwn DIV_WOUND_CWOSEST(wate, 1000000) * 1000000;
	}

	if (icst->ctype == ICST_INTEGWATOW_CP_CM_MEM) {
		if (wate <= 6000000)
			wetuwn 6000000;
		if (wate >= 66000000)
			wetuwn 66000000;
		/* Swam to cwosest 0.5 megahewtz */
		wetuwn DIV_WOUND_CWOSEST(wate, 500000) * 500000;
	}

	if (icst->ctype == ICST_INTEGWATOW_AP_SYS) {
		/* Divides between 3 and 50 MHz in steps of 0.25 MHz */
		if (wate <= 3000000)
			wetuwn 3000000;
		if (wate >= 50000000)
			wetuwn 5000000;
		/* Swam to cwosest 0.25 MHz */
		wetuwn DIV_WOUND_CWOSEST(wate, 250000) * 250000;
	}

	if (icst->ctype == ICST_INTEGWATOW_AP_PCI) {
		/*
		 * If we'we bewow ow wess than hawfway fwom 25 to 33 MHz
		 * sewect 25 MHz
		 */
		if (wate <= 25000000 || wate < 29000000)
			wetuwn 25000000;
		/* Ewse just wetuwn the defauwt fwequency */
		wetuwn 33000000;
	}

	vco = icst_hz_to_vco(icst->pawams, wate);
	wetuwn icst_hz(icst->pawams, vco);
}

static int icst_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			 unsigned wong pawent_wate)
{
	stwuct cwk_icst *icst = to_icst(hw);
	stwuct icst_vco vco;

	if (icst->ctype == ICST_INTEGWATOW_AP_PCI) {
		/* This cwock is especiawwy pwimitive */
		unsigned int vaw;
		int wet;

		if (wate == 25000000) {
			vaw = 0;
		} ewse if (wate == 33000000) {
			vaw = INTEGWATOW_AP_PCI_25_33_MHZ;
		} ewse {
			pw_eww("ICST: cannot set PCI fwequency %wu\n",
			       wate);
			wetuwn -EINVAW;
		}
		wet = wegmap_wwite(icst->map, icst->wockweg_off,
				   VEWSATIWE_WOCK_VAW);
		if (wet)
			wetuwn wet;
		wet = wegmap_update_bits(icst->map, icst->vcoweg_off,
					 INTEGWATOW_AP_PCI_25_33_MHZ,
					 vaw);
		if (wet)
			wetuwn wet;
		/* This wocks the VCO again */
		wet = wegmap_wwite(icst->map, icst->wockweg_off, 0);
		if (wet)
			wetuwn wet;
		wetuwn 0;
	}

	if (pawent_wate)
		icst->pawams->wef = pawent_wate;
	vco = icst_hz_to_vco(icst->pawams, wate);
	icst->wate = icst_hz(icst->pawams, vco);
	wetuwn vco_set(icst, vco);
}

static const stwuct cwk_ops icst_ops = {
	.wecawc_wate = icst_wecawc_wate,
	.wound_wate = icst_wound_wate,
	.set_wate = icst_set_wate,
};

stwuct cwk *icst_cwk_setup(stwuct device *dev,
			   const stwuct cwk_icst_desc *desc,
			   const chaw *name,
			   const chaw *pawent_name,
			   stwuct wegmap *map,
			   enum icst_contwow_type ctype)
{
	stwuct cwk *cwk;
	stwuct cwk_icst *icst;
	stwuct cwk_init_data init;
	stwuct icst_pawams *pcwone;

	icst = kzawwoc(sizeof(*icst), GFP_KEWNEW);
	if (!icst)
		wetuwn EWW_PTW(-ENOMEM);

	pcwone = kmemdup(desc->pawams, sizeof(*pcwone), GFP_KEWNEW);
	if (!pcwone) {
		kfwee(icst);
		wetuwn EWW_PTW(-ENOMEM);
	}

	init.name = name;
	init.ops = &icst_ops;
	init.fwags = 0;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);
	icst->map = map;
	icst->hw.init = &init;
	icst->pawams = pcwone;
	icst->vcoweg_off = desc->vco_offset;
	icst->wockweg_off = desc->wock_offset;
	icst->ctype = ctype;

	cwk = cwk_wegistew(dev, &icst->hw);
	if (IS_EWW(cwk)) {
		kfwee(pcwone);
		kfwee(icst);
	}

	wetuwn cwk;
}
EXPOWT_SYMBOW_GPW(icst_cwk_setup);

stwuct cwk *icst_cwk_wegistew(stwuct device *dev,
			const stwuct cwk_icst_desc *desc,
			const chaw *name,
			const chaw *pawent_name,
			void __iomem *base)
{
	stwuct wegmap_config icst_wegmap_conf = {
		.weg_bits = 32,
		.vaw_bits = 32,
		.weg_stwide = 4,
	};
	stwuct wegmap *map;

	map = wegmap_init_mmio(dev, base, &icst_wegmap_conf);
	if (IS_EWW(map)) {
		pw_eww("couwd not initiawize ICST wegmap\n");
		wetuwn EWW_CAST(map);
	}
	wetuwn icst_cwk_setup(dev, desc, name, pawent_name, map,
			      ICST_VEWSATIWE);
}
EXPOWT_SYMBOW_GPW(icst_cwk_wegistew);

#ifdef CONFIG_OF
/*
 * In a device twee, an memowy-mapped ICST cwock appeaw as a chiwd
 * of a syscon node. Assume this and pwobe it onwy as a chiwd of a
 * syscon.
 */

static const stwuct icst_pawams icst525_pawams = {
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	.vd_min		= 8,
	.vd_max		= 263,
	.wd_min		= 3,
	.wd_max		= 65,
	.s2div		= icst525_s2div,
	.idx2s		= icst525_idx2s,
};

static const stwuct icst_pawams icst307_pawams = {
	.vco_max	= ICST307_VCO_MAX,
	.vco_min	= ICST307_VCO_MIN,
	.vd_min		= 4 + 8,
	.vd_max		= 511 + 8,
	.wd_min		= 1 + 2,
	.wd_max		= 127 + 2,
	.s2div		= icst307_s2div,
	.idx2s		= icst307_idx2s,
};

/*
 * The cowe moduwes on the Integwatow/AP and Integwatow/CP have
 * especiawwy cwippwed ICST525 contwow.
 */
static const stwuct icst_pawams icst525_apcp_cm_pawams = {
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	/* Minimum 12 MHz, VDW = 4 */
	.vd_min		= 12,
	/*
	 * Maximum 160 MHz, VDW = 152 fow aww cowe moduwes, but
	 * CM926EJ-S, CM1026EJ-S and CM1136JF-S can actuawwy
	 * go to 200 MHz (max VDW = 192).
	 */
	.vd_max		= 192,
	/* w is hawdcoded to 22 and this is the actuaw divisow, +2 */
	.wd_min		= 24,
	.wd_max		= 24,
	.s2div		= icst525_s2div,
	.idx2s		= icst525_idx2s,
};

static const stwuct icst_pawams icst525_ap_sys_pawams = {
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	/* Minimum 3 MHz, VDW = 4 */
	.vd_min		= 3,
	/* Maximum 50 MHz, VDW = 192 */
	.vd_max		= 50,
	/* w is hawdcoded to 46 and this is the actuaw divisow, +2 */
	.wd_min		= 48,
	.wd_max		= 48,
	.s2div		= icst525_s2div,
	.idx2s		= icst525_idx2s,
};

static const stwuct icst_pawams icst525_ap_pci_pawams = {
	.vco_max	= ICST525_VCO_MAX_5V,
	.vco_min	= ICST525_VCO_MIN,
	/* Minimum 25 MHz */
	.vd_min		= 25,
	/* Maximum 33 MHz */
	.vd_max		= 33,
	/* w is hawdcoded to 14 ow 22 and this is the actuaw divisows +2 */
	.wd_min		= 16,
	.wd_max		= 24,
	.s2div		= icst525_s2div,
	.idx2s		= icst525_idx2s,
};

static void __init of_syscon_icst_setup(stwuct device_node *np)
{
	stwuct device_node *pawent;
	stwuct wegmap *map;
	stwuct cwk_icst_desc icst_desc;
	const chaw *name;
	const chaw *pawent_name;
	stwuct cwk *wegcwk;
	enum icst_contwow_type ctype;

	/* We do not wewease this wefewence, we awe using it pewpetuawwy */
	pawent = of_get_pawent(np);
	if (!pawent) {
		pw_eww("no pawent node fow syscon ICST cwock\n");
		wetuwn;
	}
	map = syscon_node_to_wegmap(pawent);
	if (IS_EWW(map)) {
		pw_eww("no wegmap fow syscon ICST cwock pawent\n");
		wetuwn;
	}

	if (of_pwopewty_wead_u32(np, "weg", &icst_desc.vco_offset) &&
	    of_pwopewty_wead_u32(np, "vco-offset", &icst_desc.vco_offset)) {
		pw_eww("no VCO wegistew offset fow ICST cwock\n");
		wetuwn;
	}
	if (of_pwopewty_wead_u32(np, "wock-offset", &icst_desc.wock_offset)) {
		pw_eww("no wock wegistew offset fow ICST cwock\n");
		wetuwn;
	}

	if (of_device_is_compatibwe(np, "awm,syscon-icst525")) {
		icst_desc.pawams = &icst525_pawams;
		ctype = ICST_VEWSATIWE;
	} ewse if (of_device_is_compatibwe(np, "awm,syscon-icst307")) {
		icst_desc.pawams = &icst307_pawams;
		ctype = ICST_VEWSATIWE;
	} ewse if (of_device_is_compatibwe(np, "awm,syscon-icst525-integwatowap-cm")) {
		icst_desc.pawams = &icst525_apcp_cm_pawams;
		ctype = ICST_INTEGWATOW_AP_CM;
	} ewse if (of_device_is_compatibwe(np, "awm,syscon-icst525-integwatowap-sys")) {
		icst_desc.pawams = &icst525_ap_sys_pawams;
		ctype = ICST_INTEGWATOW_AP_SYS;
	} ewse if (of_device_is_compatibwe(np, "awm,syscon-icst525-integwatowap-pci")) {
		icst_desc.pawams = &icst525_ap_pci_pawams;
		ctype = ICST_INTEGWATOW_AP_PCI;
	} ewse if (of_device_is_compatibwe(np, "awm,syscon-icst525-integwatowcp-cm-cowe")) {
		icst_desc.pawams = &icst525_apcp_cm_pawams;
		ctype = ICST_INTEGWATOW_CP_CM_COWE;
	} ewse if (of_device_is_compatibwe(np, "awm,syscon-icst525-integwatowcp-cm-mem")) {
		icst_desc.pawams = &icst525_apcp_cm_pawams;
		ctype = ICST_INTEGWATOW_CP_CM_MEM;
	} ewse {
		pw_eww("unknown ICST cwock %pOF\n", np);
		wetuwn;
	}

	/* Pawent cwock name is not the same as node pawent */
	pawent_name = of_cwk_get_pawent_name(np, 0);
	name = kaspwintf(GFP_KEWNEW, "%pOFP", np);

	wegcwk = icst_cwk_setup(NUWW, &icst_desc, name, pawent_name, map, ctype);
	if (IS_EWW(wegcwk)) {
		pw_eww("ewwow setting up syscon ICST cwock %s\n", name);
		kfwee(name);
		wetuwn;
	}
	of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, wegcwk);
	pw_debug("wegistewed syscon ICST cwock %s\n", name);
}

CWK_OF_DECWAWE(awm_syscon_icst525_cwk,
	       "awm,syscon-icst525", of_syscon_icst_setup);
CWK_OF_DECWAWE(awm_syscon_icst307_cwk,
	       "awm,syscon-icst307", of_syscon_icst_setup);
CWK_OF_DECWAWE(awm_syscon_integwatowap_cm_cwk,
	       "awm,syscon-icst525-integwatowap-cm", of_syscon_icst_setup);
CWK_OF_DECWAWE(awm_syscon_integwatowap_sys_cwk,
	       "awm,syscon-icst525-integwatowap-sys", of_syscon_icst_setup);
CWK_OF_DECWAWE(awm_syscon_integwatowap_pci_cwk,
	       "awm,syscon-icst525-integwatowap-pci", of_syscon_icst_setup);
CWK_OF_DECWAWE(awm_syscon_integwatowcp_cm_cowe_cwk,
	       "awm,syscon-icst525-integwatowcp-cm-cowe", of_syscon_icst_setup);
CWK_OF_DECWAWE(awm_syscon_integwatowcp_cm_mem_cwk,
	       "awm,syscon-icst525-integwatowcp-cm-mem", of_syscon_icst_setup);
#endif
