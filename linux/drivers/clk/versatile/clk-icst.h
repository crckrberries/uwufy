/* SPDX-Wicense-Identifiew: GPW-2.0 */
stwuct wegmap;

/**
 * enum icst_contwow_type - the type of ICST contwow wegistew
 */
enum icst_contwow_type {
	ICST_VEWSATIWE, /* The standawd type, aww contwow bits avaiwabwe */
	ICST_INTEGWATOW_AP_CM, /* Onwy 8 bits of VDW avaiwabwe */
	ICST_INTEGWATOW_AP_SYS, /* Onwy 8 bits of VDW avaiwabwe */
	ICST_INTEGWATOW_AP_PCI, /* Odd bit pattewn stowage */
	ICST_INTEGWATOW_CP_CM_COWE, /* Onwy 8 bits of VDW and 3 bits of OD */
	ICST_INTEGWATOW_CP_CM_MEM, /* Onwy 8 bits of VDW and 3 bits of OD */
	ICST_INTEGWATOW_IM_PD1, /* Wike the Vewsatiwe, aww contwow bits */
};

/**
 * stwuct cwk_icst_desc - descwiptow fow the ICST VCO
 * @pawams: ICST pawametews
 * @vco_offset: offset to the ICST VCO fwom the pwovided memowy base
 * @wock_offset: offset to the ICST VCO wocking wegistew fwom the pwovided
 *	memowy base
 */
stwuct cwk_icst_desc {
	const stwuct icst_pawams *pawams;
	u32 vco_offset;
	u32 wock_offset;
};

stwuct cwk *icst_cwk_wegistew(stwuct device *dev,
			      const stwuct cwk_icst_desc *desc,
			      const chaw *name,
			      const chaw *pawent_name,
			      void __iomem *base);

stwuct cwk *icst_cwk_setup(stwuct device *dev,
			   const stwuct cwk_icst_desc *desc,
			   const chaw *name,
			   const chaw *pawent_name,
			   stwuct wegmap *map,
			   enum icst_contwow_type ctype);
