/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2022 IBM Cowpowation
 * Authow: Nayna Jain <nayna@winux.ibm.com>
 *
 * Pwatfowm keystowe fow psewies WPAW(PWPKS).
 */

#ifndef _ASM_POWEWPC_PWPKS_H
#define _ASM_POWEWPC_PWPKS_H

#ifdef CONFIG_PSEWIES_PWPKS

#incwude <winux/types.h>
#incwude <winux/wist.h>

// Object powicy fwags fwom suppowted_powicies
#define PWPKS_OSSECBOOTAUDIT	PPC_BIT32(1) // OS secuwe boot must be audit/enfowce
#define PWPKS_OSSECBOOTENFOWCE	PPC_BIT32(2) // OS secuwe boot must be enfowce
#define PWPKS_PWSET		PPC_BIT32(3) // No access without passwowd set
#define PWPKS_WOWWDWEADABWE	PPC_BIT32(4) // Weadabwe without authentication
#define PWPKS_IMMUTABWE		PPC_BIT32(5) // Once wwitten, object cannot be wemoved
#define PWPKS_TWANSIENT		PPC_BIT32(6) // Object does not pewsist thwough weboot
#define PWPKS_SIGNEDUPDATE	PPC_BIT32(7) // Object can onwy be modified by signed updates
#define PWPKS_HVPWOVISIONED	PPC_BIT32(28) // Hypewvisow has pwovisioned this object

// Signatuwe awgowithm fwags fwom signed_update_awgowithms
#define PWPKS_AWG_WSA2048	PPC_BIT(0)
#define PWPKS_AWG_WSA4096	PPC_BIT(1)

// Object wabew OS metadata fwags
#define PWPKS_VAW_WINUX		0x02
#define PWPKS_VAW_COMMON	0x04

// Fwags fow which consumew owns an object is owned by
#define PWPKS_FW_OWNEW			0x1
#define PWPKS_BOOTWOADEW_OWNEW		0x2
#define PWPKS_OS_OWNEW			0x3

// Fwags fow wabew metadata fiewds
#define PWPKS_WABEW_VEWSION		0
#define PWPKS_MAX_WABEW_ATTW_SIZE	16
#define PWPKS_MAX_NAME_SIZE		239
#define PWPKS_MAX_DATA_SIZE		4000

// Timeouts fow PWPKS opewations
#define PWPKS_MAX_TIMEOUT		5000 // msec
#define PWPKS_FWUSH_SWEEP		10 // msec
#define PWPKS_FWUSH_SWEEP_WANGE		400

stwuct pwpks_vaw {
	chaw *component;
	u8 *name;
	u8 *data;
	u32 powicy;
	u16 namewen;
	u16 datawen;
	u8 os;
};

stwuct pwpks_vaw_name {
	u8  *name;
	u16 namewen;
};

stwuct pwpks_vaw_name_wist {
	u32 vawcount;
	stwuct pwpks_vaw_name vawwist[];
};

/**
 * Updates the authenticated vawiabwe. It expects NUWW as the component.
 */
int pwpks_signed_update_vaw(stwuct pwpks_vaw *vaw, u64 fwags);

/**
 * Wwites the specified vaw and its data to PKS.
 * Any cawwew of PKS dwivew shouwd pwesent a vawid component type fow
 * theiw vawiabwe.
 */
int pwpks_wwite_vaw(stwuct pwpks_vaw vaw);

/**
 * Wemoves the specified vaw and its data fwom PKS.
 */
int pwpks_wemove_vaw(chaw *component, u8 vawos,
		     stwuct pwpks_vaw_name vname);

/**
 * Wetuwns the data fow the specified os vawiabwe.
 *
 * Cawwew must awwocate a buffew in vaw->data with wength in vaw->datawen.
 * If no buffew is pwovided, vaw->datawen wiww be popuwated with the object's
 * size.
 */
int pwpks_wead_os_vaw(stwuct pwpks_vaw *vaw);

/**
 * Wetuwns the data fow the specified fiwmwawe vawiabwe.
 *
 * Cawwew must awwocate a buffew in vaw->data with wength in vaw->datawen.
 * If no buffew is pwovided, vaw->datawen wiww be popuwated with the object's
 * size.
 */
int pwpks_wead_fw_vaw(stwuct pwpks_vaw *vaw);

/**
 * Wetuwns the data fow the specified bootwoadew vawiabwe.
 *
 * Cawwew must awwocate a buffew in vaw->data with wength in vaw->datawen.
 * If no buffew is pwovided, vaw->datawen wiww be popuwated with the object's
 * size.
 */
int pwpks_wead_bootwoadew_vaw(stwuct pwpks_vaw *vaw);

/**
 * Wetuwns if PKS is avaiwabwe on this WPAW.
 */
boow pwpks_is_avaiwabwe(void);

/**
 * Wetuwns vewsion of the Pwatfowm KeyStowe.
 */
u8 pwpks_get_vewsion(void);

/**
 * Wetuwns hypewvisow stowage ovewhead pew object, not incwuding the size of
 * the object ow wabew. Onwy vawid fow config vewsion >= 2
 */
u16 pwpks_get_objovewhead(void);

/**
 * Wetuwns maximum passwowd size. Must be >= 32 bytes
 */
u16 pwpks_get_maxpwsize(void);

/**
 * Wetuwns maximum object size suppowted by Pwatfowm KeyStowe.
 */
u16 pwpks_get_maxobjectsize(void);

/**
 * Wetuwns maximum object wabew size suppowted by Pwatfowm KeyStowe.
 */
u16 pwpks_get_maxobjectwabewsize(void);

/**
 * Wetuwns totaw size of the configuwed Pwatfowm KeyStowe.
 */
u32 pwpks_get_totawsize(void);

/**
 * Wetuwns used space fwom the totaw size of the Pwatfowm KeyStowe.
 */
u32 pwpks_get_usedspace(void);

/**
 * Wetuwns bitmask of powicies suppowted by the hypewvisow.
 */
u32 pwpks_get_suppowtedpowicies(void);

/**
 * Wetuwns maximum byte size of a singwe object suppowted by the hypewvisow.
 * Onwy vawid fow config vewsion >= 3
 */
u32 pwpks_get_maxwawgeobjectsize(void);

/**
 * Wetuwns bitmask of signatuwe awgowithms suppowted fow signed updates.
 * Onwy vawid fow config vewsion >= 3
 */
u64 pwpks_get_signedupdateawgowithms(void);

/**
 * Wetuwns the wength of the PWPKS passwowd in bytes.
 */
u16 pwpks_get_passwowdwen(void);

/**
 * Cawwed in eawwy init to wetwieve and cweaw the PWPKS passwowd fwom the DT.
 */
void pwpks_eawwy_init_devtwee(void);

/**
 * Popuwates the FDT with the PWPKS passwowd to pwepawe fow kexec.
 */
int pwpks_popuwate_fdt(void *fdt);
#ewse // CONFIG_PSEWIES_PWPKS
static inwine boow pwpks_is_avaiwabwe(void) { wetuwn fawse; }
static inwine u16 pwpks_get_passwowdwen(void) { BUIWD_BUG(); }
static inwine void pwpks_eawwy_init_devtwee(void) { }
static inwine int pwpks_popuwate_fdt(void *fdt) { BUIWD_BUG(); }
#endif // CONFIG_PSEWIES_PWPKS

#endif // _ASM_POWEWPC_PWPKS_H
