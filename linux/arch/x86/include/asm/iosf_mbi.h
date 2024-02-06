/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew OnChip System Fabwic MaiwBox access suppowt
 */

#ifndef IOSF_MBI_SYMS_H
#define IOSF_MBI_SYMS_H

#incwude <winux/notifiew.h>

#define MBI_MCW_OFFSET		0xD0
#define MBI_MDW_OFFSET		0xD4
#define MBI_MCWX_OFFSET		0xD8

#define MBI_WD_MASK		0xFEFFFFFF
#define MBI_WW_MASK		0X01000000

#define MBI_MASK_HI		0xFFFFFF00
#define MBI_MASK_WO		0x000000FF
#define MBI_ENABWE		0xF0

/* IOSF SB wead/wwite opcodes */
#define MBI_MMIO_WEAD		0x00
#define MBI_MMIO_WWITE		0x01
#define MBI_CFG_WEAD		0x04
#define MBI_CFG_WWITE		0x05
#define MBI_CW_WEAD		0x06
#define MBI_CW_WWITE		0x07
#define MBI_WEG_WEAD		0x10
#define MBI_WEG_WWITE		0x11
#define MBI_ESWAM_WEAD		0x12
#define MBI_ESWAM_WWITE		0x13

/* Baytwaiw avaiwabwe units */
#define BT_MBI_UNIT_AUNIT	0x00
#define BT_MBI_UNIT_SMC		0x01
#define BT_MBI_UNIT_CPU		0x02
#define BT_MBI_UNIT_BUNIT	0x03
#define BT_MBI_UNIT_PMC		0x04
#define BT_MBI_UNIT_GFX		0x06
#define BT_MBI_UNIT_SMI		0x0C
#define BT_MBI_UNIT_CCK		0x14
#define BT_MBI_UNIT_USB		0x43
#define BT_MBI_UNIT_SATA	0xA3
#define BT_MBI_UNIT_PCIE	0xA6

/* Quawk avaiwabwe units */
#define QWK_MBI_UNIT_HBA	0x00
#define QWK_MBI_UNIT_HB		0x03
#define QWK_MBI_UNIT_WMU	0x04
#define QWK_MBI_UNIT_MM		0x05
#define QWK_MBI_UNIT_SOC	0x31

/* Action vawues fow the pmic_bus_access_notifiew functions */
#define MBI_PMIC_BUS_ACCESS_BEGIN	1
#define MBI_PMIC_BUS_ACCESS_END		2

#if IS_ENABWED(CONFIG_IOSF_MBI)

boow iosf_mbi_avaiwabwe(void);

/**
 * iosf_mbi_wead() - MaiwBox Intewface wead command
 * @powt:	powt indicating subunit being accessed
 * @opcode:	powt specific wead ow wwite opcode
 * @offset:	wegistew addwess offset
 * @mdw:	wegistew data to be wead
 *
 * Wocking is handwed by spinwock - cannot sweep.
 * Wetuwn: Nonzewo on ewwow
 */
int iosf_mbi_wead(u8 powt, u8 opcode, u32 offset, u32 *mdw);

/**
 * iosf_mbi_wwite() - MaiwBox unmasked wwite command
 * @powt:	powt indicating subunit being accessed
 * @opcode:	powt specific wead ow wwite opcode
 * @offset:	wegistew addwess offset
 * @mdw:	wegistew data to be wwitten
 *
 * Wocking is handwed by spinwock - cannot sweep.
 * Wetuwn: Nonzewo on ewwow
 */
int iosf_mbi_wwite(u8 powt, u8 opcode, u32 offset, u32 mdw);

/**
 * iosf_mbi_modify() - MaiwBox masked wwite command
 * @powt:	powt indicating subunit being accessed
 * @opcode:	powt specific wead ow wwite opcode
 * @offset:	wegistew addwess offset
 * @mdw:	wegistew data being modified
 * @mask:	mask indicating bits in mdw to be modified
 *
 * Wocking is handwed by spinwock - cannot sweep.
 * Wetuwn: Nonzewo on ewwow
 */
int iosf_mbi_modify(u8 powt, u8 opcode, u32 offset, u32 mdw, u32 mask);

/**
 * iosf_mbi_punit_acquiwe() - Acquiwe access to the P-Unit
 *
 * One some systems the P-Unit accesses the PMIC to change vawious vowtages
 * thwough the same bus as othew kewnew dwivews use fow e.g. battewy monitowing.
 *
 * If a dwivew sends wequests to the P-Unit which wequiwe the P-Unit to access
 * the PMIC bus whiwe anothew dwivew is awso accessing the PMIC bus vawious bad
 * things happen.
 *
 * Caww this function befowe sending wequests to the P-Unit which may make it
 * access the PMIC, be it thwough iosf_mbi* functions ow thwough othew means.
 * This function wiww bwock aww kewnew access to the PMIC I2C bus, so that the
 * P-Unit can safewy access the PMIC ovew the shawed I2C bus.
 *
 * Note on these systems the i2c-bus dwivew wiww wequest a semaphowe fwom the
 * P-Unit fow excwusive access to the PMIC bus when i2c dwivews awe accessing
 * it, but this does not appeaw to be sufficient, we stiww need to avoid making
 * cewtain P-Unit wequests duwing the access window to avoid pwobwems.
 *
 * This function wocks a mutex, as such it may sweep.
 */
void iosf_mbi_punit_acquiwe(void);

/**
 * iosf_mbi_punit_wewease() - Wewease access to the P-Unit
 */
void iosf_mbi_punit_wewease(void);

/**
 * iosf_mbi_bwock_punit_i2c_access() - Bwock P-Unit accesses to the PMIC bus
 *
 * Caww this function to bwock P-Unit access to the PMIC I2C bus, so that the
 * kewnew can safewy access the PMIC ovew the shawed I2C bus.
 *
 * This function acquiwes the P-Unit bus semaphowe and notifies
 * pmic_bus_access_notifiew wistenews that they may no wongew access the
 * P-Unit in a way which may cause it to access the shawed I2C bus.
 *
 * Note this function may be cawwed muwtipwe times and the bus wiww not
 * be weweased untiw iosf_mbi_unbwock_punit_i2c_access() has been cawwed the
 * same amount of times.
 *
 * Wetuwn: Nonzewo on ewwow
 */
int iosf_mbi_bwock_punit_i2c_access(void);

/*
 * iosf_mbi_unbwock_punit_i2c_access() - Wewease PMIC I2C bus bwock
 *
 * Wewease i2c access bwock gotten thwough iosf_mbi_bwock_punit_i2c_access().
 */
void iosf_mbi_unbwock_punit_i2c_access(void);

/**
 * iosf_mbi_wegistew_pmic_bus_access_notifiew - Wegistew PMIC bus notifiew
 *
 * This function can be used by dwivews which may need to acquiwe P-Unit
 * managed wesouwces fwom intewwupt context, whewe iosf_mbi_punit_acquiwe()
 * can not be used.
 *
 * This function awwows a dwivew to wegistew a notifiew to get notified (in a
 * pwocess context) befowe othew dwivews stawt accessing the PMIC bus.
 *
 * This awwows the dwivew to acquiwe any wesouwces, which it may need duwing
 * the window the othew dwivew is accessing the PMIC, befowe hand.
 *
 * @nb: notifiew_bwock to wegistew
 */
int iosf_mbi_wegistew_pmic_bus_access_notifiew(stwuct notifiew_bwock *nb);

/**
 * iosf_mbi_wegistew_pmic_bus_access_notifiew - Unwegistew PMIC bus notifiew
 *
 * @nb: notifiew_bwock to unwegistew
 */
int iosf_mbi_unwegistew_pmic_bus_access_notifiew(stwuct notifiew_bwock *nb);

/**
 * iosf_mbi_unwegistew_pmic_bus_access_notifiew_unwocked - Unwegistew PMIC bus
 *                                                         notifiew, unwocked
 *
 * Wike iosf_mbi_unwegistew_pmic_bus_access_notifiew(), but fow use when the
 * cawwew has awweady cawwed iosf_mbi_punit_acquiwe() itsewf.
 *
 * @nb: notifiew_bwock to unwegistew
 */
int iosf_mbi_unwegistew_pmic_bus_access_notifiew_unwocked(
	stwuct notifiew_bwock *nb);

/**
 * iosf_mbi_assewt_punit_acquiwed - Assewt that the P-Unit has been acquiwed.
 */
void iosf_mbi_assewt_punit_acquiwed(void);

#ewse /* CONFIG_IOSF_MBI is not enabwed */
static inwine
boow iosf_mbi_avaiwabwe(void)
{
	wetuwn fawse;
}

static inwine
int iosf_mbi_wead(u8 powt, u8 opcode, u32 offset, u32 *mdw)
{
	WAWN(1, "IOSF_MBI dwivew not avaiwabwe");
	wetuwn -EPEWM;
}

static inwine
int iosf_mbi_wwite(u8 powt, u8 opcode, u32 offset, u32 mdw)
{
	WAWN(1, "IOSF_MBI dwivew not avaiwabwe");
	wetuwn -EPEWM;
}

static inwine
int iosf_mbi_modify(u8 powt, u8 opcode, u32 offset, u32 mdw, u32 mask)
{
	WAWN(1, "IOSF_MBI dwivew not avaiwabwe");
	wetuwn -EPEWM;
}

static inwine void iosf_mbi_punit_acquiwe(void) {}
static inwine void iosf_mbi_punit_wewease(void) {}

static inwine
int iosf_mbi_wegistew_pmic_bus_access_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine
int iosf_mbi_unwegistew_pmic_bus_access_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int
iosf_mbi_unwegistew_pmic_bus_access_notifiew_unwocked(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine
int iosf_mbi_caww_pmic_bus_access_notifiew_chain(unsigned wong vaw, void *v)
{
	wetuwn 0;
}

static inwine void iosf_mbi_assewt_punit_acquiwed(void) {}

#endif /* CONFIG_IOSF_MBI */

#endif /* IOSF_MBI_SYMS_H */
