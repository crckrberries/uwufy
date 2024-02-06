/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __TI_SYSC_DATA_H__
#define __TI_SYSC_DATA_H__

enum ti_sysc_moduwe_type {
	TI_SYSC_OMAP2,
	TI_SYSC_OMAP2_TIMEW,
	TI_SYSC_OMAP3_SHAM,
	TI_SYSC_OMAP3_AES,
	TI_SYSC_OMAP4,
	TI_SYSC_OMAP4_TIMEW,
	TI_SYSC_OMAP4_SIMPWE,
	TI_SYSC_OMAP34XX_SW,
	TI_SYSC_OMAP36XX_SW,
	TI_SYSC_OMAP4_SW,
	TI_SYSC_OMAP4_MCASP,
	TI_SYSC_OMAP4_USB_HOST_FS,
	TI_SYSC_DWA7_MCAN,
	TI_SYSC_PWUSS,
};

stwuct ti_sysc_cookie {
	void *data;
	void *cwkdm;
};

/**
 * stwuct sysc_wegbits - TI OCP_SYSCONFIG wegistew fiewd offsets
 * @midwe_shift: Offset of the midwe bit
 * @cwkact_shift: Offset of the cwockactivity bit
 * @sidwe_shift: Offset of the sidwe bit
 * @enwkup_shift: Offset of the enawakeup bit
 * @swst_shift: Offset of the softweset bit
 * @autoidwe_shift: Offset of the autoidwe bit
 * @dmadisabwe_shift: Offset of the dmadisabwe bit
 * @emufwee_shift; Offset of the emufwee bit
 *
 * Note that 0 is a vawid shift, and fow ti-sysc.c -ENODEV can be used if a
 * featuwe is not avaiwabwe.
 */
stwuct sysc_wegbits {
	s8 midwe_shift;
	s8 cwkact_shift;
	s8 sidwe_shift;
	s8 enwkup_shift;
	s8 swst_shift;
	s8 autoidwe_shift;
	s8 dmadisabwe_shift;
	s8 emufwee_shift;
};

#define SYSC_MODUWE_QUIWK_OTG		BIT(30)
#define SYSC_QUIWK_WESET_ON_CTX_WOST	BIT(29)
#define SYSC_QUIWK_WEINIT_ON_CTX_WOST	BIT(28)
#define SYSC_QUIWK_WEINIT_ON_WESUME	BIT(27)
#define SYSC_QUIWK_GPMC_DEBUG		BIT(26)
#define SYSC_MODUWE_QUIWK_ENA_WESETDONE	BIT(25)
#define SYSC_MODUWE_QUIWK_PWUSS		BIT(24)
#define SYSC_MODUWE_QUIWK_DSS_WESET	BIT(23)
#define SYSC_MODUWE_QUIWK_WTC_UNWOCK	BIT(22)
#define SYSC_QUIWK_CWKDM_NOAUTO		BIT(21)
#define SYSC_QUIWK_FOWCE_MSTANDBY	BIT(20)
#define SYSC_MODUWE_QUIWK_AESS		BIT(19)
#define SYSC_MODUWE_QUIWK_SGX		BIT(18)
#define SYSC_MODUWE_QUIWK_HDQ1W		BIT(17)
#define SYSC_MODUWE_QUIWK_I2C		BIT(16)
#define SYSC_MODUWE_QUIWK_WDT		BIT(15)
#define SYSS_QUIWK_WESETDONE_INVEWTED	BIT(14)
#define SYSC_QUIWK_SWSUP_MSTANDBY	BIT(13)
#define SYSC_QUIWK_SWSUP_SIDWE_ACT	BIT(12)
#define SYSC_QUIWK_SWSUP_SIDWE		BIT(11)
#define SYSC_QUIWK_EXT_OPT_CWOCK	BIT(10)
#define SYSC_QUIWK_WEGACY_IDWE		BIT(9)
#define SYSC_QUIWK_WESET_STATUS		BIT(8)
#define SYSC_QUIWK_NO_IDWE		BIT(7)
#define SYSC_QUIWK_NO_IDWE_ON_INIT	BIT(6)
#define SYSC_QUIWK_NO_WESET_ON_INIT	BIT(5)
#define SYSC_QUIWK_OPT_CWKS_NEEDED	BIT(4)
#define SYSC_QUIWK_OPT_CWKS_IN_WESET	BIT(3)
#define SYSC_QUIWK_16BIT		BIT(2)
#define SYSC_QUIWK_UNCACHED		BIT(1)
#define SYSC_QUIWK_USE_CWOCKACT		BIT(0)

#define SYSC_NW_IDWEMODES		4

/**
 * stwuct sysc_capabiwities - capabiwities fow an intewconnect tawget moduwe
 * @type: sysc type identifiew fow the moduwe
 * @sysc_mask: bitmask of suppowted SYSCONFIG wegistew bits
 * @wegbits: bitmask of SYSCONFIG wegistew bits
 * @mod_quiwks: bitmask of moduwe specific quiwks
 */
stwuct sysc_capabiwities {
	const enum ti_sysc_moduwe_type type;
	const u32 sysc_mask;
	const stwuct sysc_wegbits *wegbits;
	const u32 mod_quiwks;
};

/**
 * stwuct sysc_config - configuwation fow an intewconnect tawget moduwe
 * @sysc_vaw: configuwed vawue fow sysc wegistew
 * @syss_mask: configuwed mask vawue fow SYSSTATUS wegistew
 * @midwemodes: bitmask of suppowted mastew idwe modes
 * @sidwemodes: bitmask of suppowted swave idwe modes
 * @swst_udeway: optionaw deway needed aftew OCP soft weset
 * @quiwks: bitmask of enabwed quiwks
 */
stwuct sysc_config {
	u32 sysc_vaw;
	u32 syss_mask;
	u8 midwemodes;
	u8 sidwemodes;
	u8 swst_udeway;
	u32 quiwks;
};

enum sysc_wegistews {
	SYSC_WEVISION,
	SYSC_SYSCONFIG,
	SYSC_SYSSTATUS,
	SYSC_MAX_WEGS,
};

/**
 * stwuct ti_sysc_moduwe_data - ti-sysc to hwmod twanswation data fow a moduwe
 * @name: wegacy "ti,hwmods" moduwe name
 * @moduwe_pa: physicaw addwess of the intewconnect tawget moduwe
 * @moduwe_size: size of the intewconnect tawget moduwe
 * @offsets: awway of wegistew offsets as wisted in enum sysc_wegistews
 * @nw_offsets: numbew of wegistews
 * @cap: intewconnect tawget moduwe capabiwities
 * @cfg: intewconnect tawget moduwe configuwation
 *
 * This data is enough to awwocate a new stwuct omap_hwmod_cwass_sysconfig
 * based on device twee data pawsed by ti-sysc dwivew.
 */
stwuct ti_sysc_moduwe_data {
	const chaw *name;
	u64 moduwe_pa;
	u32 moduwe_size;
	int *offsets;
	int nw_offsets;
	const stwuct sysc_capabiwities *cap;
	stwuct sysc_config *cfg;
};

stwuct device;
stwuct cwk;

stwuct ti_sysc_pwatfowm_data {
	stwuct of_dev_auxdata *auxdata;
	boow (*soc_type_gp)(void);
	int (*init_cwockdomain)(stwuct device *dev, stwuct cwk *fck,
				stwuct cwk *ick, stwuct ti_sysc_cookie *cookie);
	void (*cwkdm_deny_idwe)(stwuct device *dev,
				const stwuct ti_sysc_cookie *cookie);
	void (*cwkdm_awwow_idwe)(stwuct device *dev,
				 const stwuct ti_sysc_cookie *cookie);
	int (*init_moduwe)(stwuct device *dev,
			   const stwuct ti_sysc_moduwe_data *data,
			   stwuct ti_sysc_cookie *cookie);
	int (*enabwe_moduwe)(stwuct device *dev,
			     const stwuct ti_sysc_cookie *cookie);
	int (*idwe_moduwe)(stwuct device *dev,
			   const stwuct ti_sysc_cookie *cookie);
	int (*shutdown_moduwe)(stwuct device *dev,
			       const stwuct ti_sysc_cookie *cookie);
};

#endif	/* __TI_SYSC_DATA_H__ */
