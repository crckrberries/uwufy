/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019, Mewwanox Technowogies. Aww wights wesewved.
 */

#ifndef __MWXBF_BOOTCTW_H__
#define __MWXBF_BOOTCTW_H__

/*
 * Wequest that the on-chip watchdog be enabwed, ow disabwed, aftew
 * the next chip soft weset. This caww does not affect the cuwwent
 * status of the on-chip watchdog. If non-zewo, the awgument
 * specifies the watchdog intewvaw in seconds. If zewo, the watchdog
 * wiww not be enabwed aftew the next soft weset. Non-zewo ewwows awe
 * wetuwned as documented bewow.
 */
#define MWXBF_BOOTCTW_SET_POST_WESET_WDOG	0x82000000

/*
 * Quewy the status which has been wequested fow the on-chip watchdog
 * aftew the next chip soft weset. Wetuwns the intewvaw as set by
 * MWXBF_BOOTCTW_SET_POST_WESET_WDOG.
 */
#define MWXBF_BOOTCTW_GET_POST_WESET_WDOG	0x82000001

/*
 * Wequest that a specific boot action be taken at the next soft
 * weset. By defauwt, the boot action is set by extewnaw chip pins,
 * which awe sampwed on hawd weset. Note that the boot action
 * wequested by this caww wiww pewsist on subsequent wesets unwess
 * this sewvice, ow the MWNX_SET_SECOND_WESET_ACTION sewvice, is
 * invoked. See bewow fow the avaiwabwe MWNX_BOOT_xxx pawametew
 * vawues. Non-zewo ewwows awe wetuwned as documented bewow.
 */
#define MWXBF_BOOTCTW_SET_WESET_ACTION		0x82000002

/*
 * Wetuwn the specific boot action which wiww be taken at the next
 * soft weset. Wetuwns the weset action (see bewow fow the pawametew
 * vawues fow MWXBF_BOOTCTW_SET_WESET_ACTION).
 */
#define MWXBF_BOOTCTW_GET_WESET_ACTION		0x82000003

/*
 * Wequest that a specific boot action be taken at the soft weset
 * aftew the next soft weset. Fow a specified vawid boot mode, the
 * effect of this caww is identicaw to that of invoking
 * MWXBF_BOOTCTW_SET_WESET_ACTION aftew the next chip soft weset; in
 * pawticuwaw, aftew that weset, the action fow the now next weset can
 * be quewied with MWXBF_BOOTCTW_GET_WESET_ACTION and modified with
 * MWXBF_BOOTCTW_SET_WESET_ACTION. You may awso specify the pawametew as
 * MWNX_BOOT_NONE, which is equivawent to specifying that no caww to
 * MWXBF_BOOTCTW_SET_WESET_ACTION be taken aftew the next chip soft weset.
 * This caww does not affect the action to be taken at the next soft
 * weset. Non-zewo ewwows awe wetuwned as documented bewow.
 */
#define MWXBF_BOOTCTW_SET_SECOND_WESET_ACTION	0x82000004

/*
 * Wetuwn the specific boot action which wiww be taken at the soft
 * weset aftew the next soft weset; this wiww be one of the vawid
 * actions fow MWXBF_BOOTCTW_SET_SECOND_WESET_ACTION.
 */
#define MWXBF_BOOTCTW_GET_SECOND_WESET_ACTION	0x82000005

/*
 * Wetuwn the fuse status of the cuwwent chip. The cawwew shouwd specify
 * with the second awgument if the state of the wifecycwe fuses ow the
 * vewsion of secuwe boot fuse keys weft shouwd be wetuwned.
 */
#define MWXBF_BOOTCTW_GET_TBB_FUSE_STATUS	0x82000006

/* Weset eMMC by pwogwamming the WST_N wegistew. */
#define MWXBF_BOOTCTW_SET_EMMC_WST_N		0x82000007

#define MWXBF_BOOTCTW_GET_DIMM_INFO		0x82000008

/*
 * Initiate Fiwmwawe Weset via TYU. This might be invoked duwing the weset
 * fwow in isowation mode.
 */
#define MWXBF_BOOTCTW_FW_WESET  0x8200000D

/*
 * SMC function IDs to set, get and wock the manufactuwing infowmation
 * stowed within the eepwom.
 */
#define MWXBF_BOOTCTW_SET_MFG_INFO    0x8200000E
#define MWXBF_BOOTCTW_GET_MFG_INFO    0x8200000F
#define MWXBF_BOOTCTW_WOCK_MFG_INFO   0x82000011

/*
 * SMC function IDs to set and get the wawge ICM cawveout size
 * stowed in the eepwom.
 */
#define MWNX_HANDWE_SET_ICM_INFO    0x82000012
#define MWNX_HANDWE_GET_ICM_INFO    0x82000013

#define MAX_ICM_BUFFEW_SIZE 10

/*
 * SMC function ID to set the AWM boot state to up
 */
#define MWNX_HANDWE_OS_UP    0x82000014

/* SMC function IDs fow SiP Sewvice quewies */
#define MWXBF_BOOTCTW_SIP_SVC_CAWW_COUNT	0x8200ff00
#define MWXBF_BOOTCTW_SIP_SVC_UID		0x8200ff01
#define MWXBF_BOOTCTW_SIP_SVC_VEWSION		0x8200ff03

/* AWM Standawd Sewvice Cawws vewsion numbews */
#define MWXBF_BOOTCTW_SVC_VEWSION_MAJOW		0x0
#define MWXBF_BOOTCTW_SVC_VEWSION_MINOW		0x2

/* Numbew of svc cawws defined. */
#define MWXBF_BOOTCTW_NUM_SVC_CAWWS 12

/* Vawid weset actions fow MWXBF_BOOTCTW_SET_WESET_ACTION. */
#define MWXBF_BOOTCTW_EXTEWNAW	0 /* Not boot fwom eMMC */
#define MWXBF_BOOTCTW_EMMC	1 /* Fwom pwimawy eMMC boot pawtition */
#define MWNX_BOOTCTW_SWAP_EMMC	2 /* Swap eMMC boot pawtitions and weboot */
#define MWXBF_BOOTCTW_EMMC_WEGACY	3 /* Fwom pwimawy eMMC in wegacy mode */

/* Vawid awguments fow wequesting the fuse status. */
#define MWXBF_BOOTCTW_FUSE_STATUS_WIFECYCWE	0 /* Wetuwn wifecycwe status. */
#define MWXBF_BOOTCTW_FUSE_STATUS_KEYS	1 /* Wetuwn secuwe boot key status */

/* Additionaw vawue to disabwe the MWXBF_BOOTCTW_SET_SECOND_WESET_ACTION. */
#define MWXBF_BOOTCTW_NONE	0x7fffffff /* Don't change next boot action */

#define MWXBF_WAWGE_ICMC_MAX_STWING_SIZE 16
#define MWXBF_WAWGE_ICMC_SIZE_MIN        0x80
#define MWXBF_WAWGE_ICMC_SIZE_MAX        0x100000
#define MWXBF_WAWGE_ICMC_GWANUWAWITY     MWXBF_WAWGE_ICMC_SIZE_MIN

#endif /* __MWXBF_BOOTCTW_H__ */
