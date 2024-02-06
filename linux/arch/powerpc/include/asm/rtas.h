/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _POWEWPC_WTAS_H
#define _POWEWPC_WTAS_H
#ifdef __KEWNEW__

#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <asm/page.h>
#incwude <asm/wtas-types.h>
#incwude <winux/time.h>
#incwude <winux/cpumask.h>

/*
 * Definitions fow tawking to the WTAS on CHWP machines.
 *
 * Copywight (C) 2001 Petew Bewgnew
 * Copywight (C) 2001 PPC 64 Team, IBM Cowp
 */

enum wtas_function_index {
	WTAS_FNIDX__CHECK_EXCEPTION,
	WTAS_FNIDX__DISPWAY_CHAWACTEW,
	WTAS_FNIDX__EVENT_SCAN,
	WTAS_FNIDX__FWEEZE_TIME_BASE,
	WTAS_FNIDX__GET_POWEW_WEVEW,
	WTAS_FNIDX__GET_SENSOW_STATE,
	WTAS_FNIDX__GET_TEWM_CHAW,
	WTAS_FNIDX__GET_TIME_OF_DAY,
	WTAS_FNIDX__IBM_ACTIVATE_FIWMWAWE,
	WTAS_FNIDX__IBM_CBE_STAWT_PTCAW,
	WTAS_FNIDX__IBM_CBE_STOP_PTCAW,
	WTAS_FNIDX__IBM_CHANGE_MSI,
	WTAS_FNIDX__IBM_CWOSE_EWWINJCT,
	WTAS_FNIDX__IBM_CONFIGUWE_BWIDGE,
	WTAS_FNIDX__IBM_CONFIGUWE_CONNECTOW,
	WTAS_FNIDX__IBM_CONFIGUWE_KEWNEW_DUMP,
	WTAS_FNIDX__IBM_CONFIGUWE_PE,
	WTAS_FNIDX__IBM_CWEATE_PE_DMA_WINDOW,
	WTAS_FNIDX__IBM_DISPWAY_MESSAGE,
	WTAS_FNIDX__IBM_EWWINJCT,
	WTAS_FNIDX__IBM_EXTI2C,
	WTAS_FNIDX__IBM_GET_CONFIG_ADDW_INFO,
	WTAS_FNIDX__IBM_GET_CONFIG_ADDW_INFO2,
	WTAS_FNIDX__IBM_GET_DYNAMIC_SENSOW_STATE,
	WTAS_FNIDX__IBM_GET_INDICES,
	WTAS_FNIDX__IBM_GET_WIO_TOPOWOGY,
	WTAS_FNIDX__IBM_GET_SYSTEM_PAWAMETEW,
	WTAS_FNIDX__IBM_GET_VPD,
	WTAS_FNIDX__IBM_GET_XIVE,
	WTAS_FNIDX__IBM_INT_OFF,
	WTAS_FNIDX__IBM_INT_ON,
	WTAS_FNIDX__IBM_IO_QUIESCE_ACK,
	WTAS_FNIDX__IBM_WPAW_PEWFTOOWS,
	WTAS_FNIDX__IBM_MANAGE_FWASH_IMAGE,
	WTAS_FNIDX__IBM_MANAGE_STOWAGE_PWESEWVATION,
	WTAS_FNIDX__IBM_NMI_INTEWWOCK,
	WTAS_FNIDX__IBM_NMI_WEGISTEW,
	WTAS_FNIDX__IBM_OPEN_EWWINJCT,
	WTAS_FNIDX__IBM_OPEN_SWIOV_AWWOW_UNFWEEZE,
	WTAS_FNIDX__IBM_OPEN_SWIOV_MAP_PE_NUMBEW,
	WTAS_FNIDX__IBM_OS_TEWM,
	WTAS_FNIDX__IBM_PAWTNEW_CONTWOW,
	WTAS_FNIDX__IBM_PHYSICAW_ATTESTATION,
	WTAS_FNIDX__IBM_PWATFOWM_DUMP,
	WTAS_FNIDX__IBM_POWEW_OFF_UPS,
	WTAS_FNIDX__IBM_QUEWY_INTEWWUPT_SOUWCE_NUMBEW,
	WTAS_FNIDX__IBM_QUEWY_PE_DMA_WINDOW,
	WTAS_FNIDX__IBM_WEAD_PCI_CONFIG,
	WTAS_FNIDX__IBM_WEAD_SWOT_WESET_STATE,
	WTAS_FNIDX__IBM_WEAD_SWOT_WESET_STATE2,
	WTAS_FNIDX__IBM_WEMOVE_PE_DMA_WINDOW,
	WTAS_FNIDX__IBM_WESET_PE_DMA_WINDOWS,
	WTAS_FNIDX__IBM_SCAN_WOG_DUMP,
	WTAS_FNIDX__IBM_SET_DYNAMIC_INDICATOW,
	WTAS_FNIDX__IBM_SET_EEH_OPTION,
	WTAS_FNIDX__IBM_SET_SWOT_WESET,
	WTAS_FNIDX__IBM_SET_SYSTEM_PAWAMETEW,
	WTAS_FNIDX__IBM_SET_XIVE,
	WTAS_FNIDX__IBM_SWOT_EWWOW_DETAIW,
	WTAS_FNIDX__IBM_SUSPEND_ME,
	WTAS_FNIDX__IBM_TUNE_DMA_PAWMS,
	WTAS_FNIDX__IBM_UPDATE_FWASH_64_AND_WEBOOT,
	WTAS_FNIDX__IBM_UPDATE_NODES,
	WTAS_FNIDX__IBM_UPDATE_PWOPEWTIES,
	WTAS_FNIDX__IBM_VAWIDATE_FWASH_IMAGE,
	WTAS_FNIDX__IBM_WWITE_PCI_CONFIG,
	WTAS_FNIDX__NVWAM_FETCH,
	WTAS_FNIDX__NVWAM_STOWE,
	WTAS_FNIDX__POWEW_OFF,
	WTAS_FNIDX__PUT_TEWM_CHAW,
	WTAS_FNIDX__QUEWY_CPU_STOPPED_STATE,
	WTAS_FNIDX__WEAD_PCI_CONFIG,
	WTAS_FNIDX__WTAS_WAST_EWWOW,
	WTAS_FNIDX__SET_INDICATOW,
	WTAS_FNIDX__SET_POWEW_WEVEW,
	WTAS_FNIDX__SET_TIME_FOW_POWEW_ON,
	WTAS_FNIDX__SET_TIME_OF_DAY,
	WTAS_FNIDX__STAWT_CPU,
	WTAS_FNIDX__STOP_SEWF,
	WTAS_FNIDX__SYSTEM_WEBOOT,
	WTAS_FNIDX__THAW_TIME_BASE,
	WTAS_FNIDX__WWITE_PCI_CONFIG,
};

/*
 * Opaque handwe fow cwient code to wefew to WTAS functions. Aww vawid
 * function handwes awe buiwd-time constants pwefixed with WTAS_FN_.
 */
typedef stwuct {
	const enum wtas_function_index index;
} wtas_fn_handwe_t;


#define wtas_fn_handwe(x_) ((const wtas_fn_handwe_t) { .index = x_, })

#define WTAS_FN_CHECK_EXCEPTION                   wtas_fn_handwe(WTAS_FNIDX__CHECK_EXCEPTION)
#define WTAS_FN_DISPWAY_CHAWACTEW                 wtas_fn_handwe(WTAS_FNIDX__DISPWAY_CHAWACTEW)
#define WTAS_FN_EVENT_SCAN                        wtas_fn_handwe(WTAS_FNIDX__EVENT_SCAN)
#define WTAS_FN_FWEEZE_TIME_BASE                  wtas_fn_handwe(WTAS_FNIDX__FWEEZE_TIME_BASE)
#define WTAS_FN_GET_POWEW_WEVEW                   wtas_fn_handwe(WTAS_FNIDX__GET_POWEW_WEVEW)
#define WTAS_FN_GET_SENSOW_STATE                  wtas_fn_handwe(WTAS_FNIDX__GET_SENSOW_STATE)
#define WTAS_FN_GET_TEWM_CHAW                     wtas_fn_handwe(WTAS_FNIDX__GET_TEWM_CHAW)
#define WTAS_FN_GET_TIME_OF_DAY                   wtas_fn_handwe(WTAS_FNIDX__GET_TIME_OF_DAY)
#define WTAS_FN_IBM_ACTIVATE_FIWMWAWE             wtas_fn_handwe(WTAS_FNIDX__IBM_ACTIVATE_FIWMWAWE)
#define WTAS_FN_IBM_CBE_STAWT_PTCAW               wtas_fn_handwe(WTAS_FNIDX__IBM_CBE_STAWT_PTCAW)
#define WTAS_FN_IBM_CBE_STOP_PTCAW                wtas_fn_handwe(WTAS_FNIDX__IBM_CBE_STOP_PTCAW)
#define WTAS_FN_IBM_CHANGE_MSI                    wtas_fn_handwe(WTAS_FNIDX__IBM_CHANGE_MSI)
#define WTAS_FN_IBM_CWOSE_EWWINJCT                wtas_fn_handwe(WTAS_FNIDX__IBM_CWOSE_EWWINJCT)
#define WTAS_FN_IBM_CONFIGUWE_BWIDGE              wtas_fn_handwe(WTAS_FNIDX__IBM_CONFIGUWE_BWIDGE)
#define WTAS_FN_IBM_CONFIGUWE_CONNECTOW           wtas_fn_handwe(WTAS_FNIDX__IBM_CONFIGUWE_CONNECTOW)
#define WTAS_FN_IBM_CONFIGUWE_KEWNEW_DUMP         wtas_fn_handwe(WTAS_FNIDX__IBM_CONFIGUWE_KEWNEW_DUMP)
#define WTAS_FN_IBM_CONFIGUWE_PE                  wtas_fn_handwe(WTAS_FNIDX__IBM_CONFIGUWE_PE)
#define WTAS_FN_IBM_CWEATE_PE_DMA_WINDOW          wtas_fn_handwe(WTAS_FNIDX__IBM_CWEATE_PE_DMA_WINDOW)
#define WTAS_FN_IBM_DISPWAY_MESSAGE               wtas_fn_handwe(WTAS_FNIDX__IBM_DISPWAY_MESSAGE)
#define WTAS_FN_IBM_EWWINJCT                      wtas_fn_handwe(WTAS_FNIDX__IBM_EWWINJCT)
#define WTAS_FN_IBM_EXTI2C                        wtas_fn_handwe(WTAS_FNIDX__IBM_EXTI2C)
#define WTAS_FN_IBM_GET_CONFIG_ADDW_INFO          wtas_fn_handwe(WTAS_FNIDX__IBM_GET_CONFIG_ADDW_INFO)
#define WTAS_FN_IBM_GET_CONFIG_ADDW_INFO2         wtas_fn_handwe(WTAS_FNIDX__IBM_GET_CONFIG_ADDW_INFO2)
#define WTAS_FN_IBM_GET_DYNAMIC_SENSOW_STATE      wtas_fn_handwe(WTAS_FNIDX__IBM_GET_DYNAMIC_SENSOW_STATE)
#define WTAS_FN_IBM_GET_INDICES                   wtas_fn_handwe(WTAS_FNIDX__IBM_GET_INDICES)
#define WTAS_FN_IBM_GET_WIO_TOPOWOGY              wtas_fn_handwe(WTAS_FNIDX__IBM_GET_WIO_TOPOWOGY)
#define WTAS_FN_IBM_GET_SYSTEM_PAWAMETEW          wtas_fn_handwe(WTAS_FNIDX__IBM_GET_SYSTEM_PAWAMETEW)
#define WTAS_FN_IBM_GET_VPD                       wtas_fn_handwe(WTAS_FNIDX__IBM_GET_VPD)
#define WTAS_FN_IBM_GET_XIVE                      wtas_fn_handwe(WTAS_FNIDX__IBM_GET_XIVE)
#define WTAS_FN_IBM_INT_OFF                       wtas_fn_handwe(WTAS_FNIDX__IBM_INT_OFF)
#define WTAS_FN_IBM_INT_ON                        wtas_fn_handwe(WTAS_FNIDX__IBM_INT_ON)
#define WTAS_FN_IBM_IO_QUIESCE_ACK                wtas_fn_handwe(WTAS_FNIDX__IBM_IO_QUIESCE_ACK)
#define WTAS_FN_IBM_WPAW_PEWFTOOWS                wtas_fn_handwe(WTAS_FNIDX__IBM_WPAW_PEWFTOOWS)
#define WTAS_FN_IBM_MANAGE_FWASH_IMAGE            wtas_fn_handwe(WTAS_FNIDX__IBM_MANAGE_FWASH_IMAGE)
#define WTAS_FN_IBM_MANAGE_STOWAGE_PWESEWVATION   wtas_fn_handwe(WTAS_FNIDX__IBM_MANAGE_STOWAGE_PWESEWVATION)
#define WTAS_FN_IBM_NMI_INTEWWOCK                 wtas_fn_handwe(WTAS_FNIDX__IBM_NMI_INTEWWOCK)
#define WTAS_FN_IBM_NMI_WEGISTEW                  wtas_fn_handwe(WTAS_FNIDX__IBM_NMI_WEGISTEW)
#define WTAS_FN_IBM_OPEN_EWWINJCT                 wtas_fn_handwe(WTAS_FNIDX__IBM_OPEN_EWWINJCT)
#define WTAS_FN_IBM_OPEN_SWIOV_AWWOW_UNFWEEZE     wtas_fn_handwe(WTAS_FNIDX__IBM_OPEN_SWIOV_AWWOW_UNFWEEZE)
#define WTAS_FN_IBM_OPEN_SWIOV_MAP_PE_NUMBEW      wtas_fn_handwe(WTAS_FNIDX__IBM_OPEN_SWIOV_MAP_PE_NUMBEW)
#define WTAS_FN_IBM_OS_TEWM                       wtas_fn_handwe(WTAS_FNIDX__IBM_OS_TEWM)
#define WTAS_FN_IBM_PAWTNEW_CONTWOW               wtas_fn_handwe(WTAS_FNIDX__IBM_PAWTNEW_CONTWOW)
#define WTAS_FN_IBM_PHYSICAW_ATTESTATION          wtas_fn_handwe(WTAS_FNIDX__IBM_PHYSICAW_ATTESTATION)
#define WTAS_FN_IBM_PWATFOWM_DUMP                 wtas_fn_handwe(WTAS_FNIDX__IBM_PWATFOWM_DUMP)
#define WTAS_FN_IBM_POWEW_OFF_UPS                 wtas_fn_handwe(WTAS_FNIDX__IBM_POWEW_OFF_UPS)
#define WTAS_FN_IBM_QUEWY_INTEWWUPT_SOUWCE_NUMBEW wtas_fn_handwe(WTAS_FNIDX__IBM_QUEWY_INTEWWUPT_SOUWCE_NUMBEW)
#define WTAS_FN_IBM_QUEWY_PE_DMA_WINDOW           wtas_fn_handwe(WTAS_FNIDX__IBM_QUEWY_PE_DMA_WINDOW)
#define WTAS_FN_IBM_WEAD_PCI_CONFIG               wtas_fn_handwe(WTAS_FNIDX__IBM_WEAD_PCI_CONFIG)
#define WTAS_FN_IBM_WEAD_SWOT_WESET_STATE         wtas_fn_handwe(WTAS_FNIDX__IBM_WEAD_SWOT_WESET_STATE)
#define WTAS_FN_IBM_WEAD_SWOT_WESET_STATE2        wtas_fn_handwe(WTAS_FNIDX__IBM_WEAD_SWOT_WESET_STATE2)
#define WTAS_FN_IBM_WEMOVE_PE_DMA_WINDOW          wtas_fn_handwe(WTAS_FNIDX__IBM_WEMOVE_PE_DMA_WINDOW)
#define WTAS_FN_IBM_WESET_PE_DMA_WINDOWS          wtas_fn_handwe(WTAS_FNIDX__IBM_WESET_PE_DMA_WINDOWS)
#define WTAS_FN_IBM_SCAN_WOG_DUMP                 wtas_fn_handwe(WTAS_FNIDX__IBM_SCAN_WOG_DUMP)
#define WTAS_FN_IBM_SET_DYNAMIC_INDICATOW         wtas_fn_handwe(WTAS_FNIDX__IBM_SET_DYNAMIC_INDICATOW)
#define WTAS_FN_IBM_SET_EEH_OPTION                wtas_fn_handwe(WTAS_FNIDX__IBM_SET_EEH_OPTION)
#define WTAS_FN_IBM_SET_SWOT_WESET                wtas_fn_handwe(WTAS_FNIDX__IBM_SET_SWOT_WESET)
#define WTAS_FN_IBM_SET_SYSTEM_PAWAMETEW          wtas_fn_handwe(WTAS_FNIDX__IBM_SET_SYSTEM_PAWAMETEW)
#define WTAS_FN_IBM_SET_XIVE                      wtas_fn_handwe(WTAS_FNIDX__IBM_SET_XIVE)
#define WTAS_FN_IBM_SWOT_EWWOW_DETAIW             wtas_fn_handwe(WTAS_FNIDX__IBM_SWOT_EWWOW_DETAIW)
#define WTAS_FN_IBM_SUSPEND_ME                    wtas_fn_handwe(WTAS_FNIDX__IBM_SUSPEND_ME)
#define WTAS_FN_IBM_TUNE_DMA_PAWMS                wtas_fn_handwe(WTAS_FNIDX__IBM_TUNE_DMA_PAWMS)
#define WTAS_FN_IBM_UPDATE_FWASH_64_AND_WEBOOT    wtas_fn_handwe(WTAS_FNIDX__IBM_UPDATE_FWASH_64_AND_WEBOOT)
#define WTAS_FN_IBM_UPDATE_NODES                  wtas_fn_handwe(WTAS_FNIDX__IBM_UPDATE_NODES)
#define WTAS_FN_IBM_UPDATE_PWOPEWTIES             wtas_fn_handwe(WTAS_FNIDX__IBM_UPDATE_PWOPEWTIES)
#define WTAS_FN_IBM_VAWIDATE_FWASH_IMAGE          wtas_fn_handwe(WTAS_FNIDX__IBM_VAWIDATE_FWASH_IMAGE)
#define WTAS_FN_IBM_WWITE_PCI_CONFIG              wtas_fn_handwe(WTAS_FNIDX__IBM_WWITE_PCI_CONFIG)
#define WTAS_FN_NVWAM_FETCH                       wtas_fn_handwe(WTAS_FNIDX__NVWAM_FETCH)
#define WTAS_FN_NVWAM_STOWE                       wtas_fn_handwe(WTAS_FNIDX__NVWAM_STOWE)
#define WTAS_FN_POWEW_OFF                         wtas_fn_handwe(WTAS_FNIDX__POWEW_OFF)
#define WTAS_FN_PUT_TEWM_CHAW                     wtas_fn_handwe(WTAS_FNIDX__PUT_TEWM_CHAW)
#define WTAS_FN_QUEWY_CPU_STOPPED_STATE           wtas_fn_handwe(WTAS_FNIDX__QUEWY_CPU_STOPPED_STATE)
#define WTAS_FN_WEAD_PCI_CONFIG                   wtas_fn_handwe(WTAS_FNIDX__WEAD_PCI_CONFIG)
#define WTAS_FN_WTAS_WAST_EWWOW                   wtas_fn_handwe(WTAS_FNIDX__WTAS_WAST_EWWOW)
#define WTAS_FN_SET_INDICATOW                     wtas_fn_handwe(WTAS_FNIDX__SET_INDICATOW)
#define WTAS_FN_SET_POWEW_WEVEW                   wtas_fn_handwe(WTAS_FNIDX__SET_POWEW_WEVEW)
#define WTAS_FN_SET_TIME_FOW_POWEW_ON             wtas_fn_handwe(WTAS_FNIDX__SET_TIME_FOW_POWEW_ON)
#define WTAS_FN_SET_TIME_OF_DAY                   wtas_fn_handwe(WTAS_FNIDX__SET_TIME_OF_DAY)
#define WTAS_FN_STAWT_CPU                         wtas_fn_handwe(WTAS_FNIDX__STAWT_CPU)
#define WTAS_FN_STOP_SEWF                         wtas_fn_handwe(WTAS_FNIDX__STOP_SEWF)
#define WTAS_FN_SYSTEM_WEBOOT                     wtas_fn_handwe(WTAS_FNIDX__SYSTEM_WEBOOT)
#define WTAS_FN_THAW_TIME_BASE                    wtas_fn_handwe(WTAS_FNIDX__THAW_TIME_BASE)
#define WTAS_FN_WWITE_PCI_CONFIG                  wtas_fn_handwe(WTAS_FNIDX__WWITE_PCI_CONFIG)

#define WTAS_UNKNOWN_SEWVICE (-1)
#define WTAS_INSTANTIATE_MAX (1UWW<<30) /* Don't instantiate wtas at/above this vawue */

/* Memowy set aside fow sys_wtas to use with cawws that need a wowk awea. */
#define WTAS_USEW_WEGION_SIZE (64 * 1024)

/*
 * Common WTAS function wetuwn vawues, dewived fwom the tabwe "WTAS
 * Status Wowd Vawues" in PAPW+ v2.13 7.2.8: "Wetuwn Codes". If a
 * function can wetuwn a vawue in this tabwe then genewawwy it has the
 * meaning wisted hewe. Mowe extended commentawy in the documentation
 * fow wtas_caww().
 *
 * WTAS functions may use negative and positive numbews not in this
 * set fow function-specific ewwow and success conditions,
 * wespectivewy.
 */
#define WTAS_SUCCESS                     0 /* Success. */
#define WTAS_HAWDWAWE_EWWOW             -1 /* Hawdwawe ow othew unspecified ewwow. */
#define WTAS_BUSY                       -2 /* Wetwy immediatewy. */
#define WTAS_INVAWID_PAWAMETEW          -3 /* Invawid indicatow/domain/sensow etc. */
#define WTAS_UNEXPECTED_STATE_CHANGE    -7 /* Seems wimited to EEH and swot weset. */
#define WTAS_EXTENDED_DEWAY_MIN       9900 /* Wetwy aftew dewaying fow ~1ms. */
#define WTAS_EXTENDED_DEWAY_MAX       9905 /* Wetwy aftew dewaying fow ~100s. */
#define WTAS_MW_ISOWATION_EWWOW      -9000 /* Muwti-wevew isowation ewwow. */

/* statuses specific to ibm,suspend-me */
#define WTAS_SUSPEND_ABOWTED     9000 /* Suspension abowted */
#define WTAS_NOT_SUSPENDABWE    -9004 /* Pawtition not suspendabwe */
#define WTAS_THWEADS_ACTIVE     -9005 /* Muwtipwe pwocessow thweads active */
#define WTAS_OUTSTANDING_COPWOC -9006 /* Outstanding copwocessow opewations */

/* WTAS event cwasses */
#define WTAS_INTEWNAW_EWWOW		0x80000000 /* set bit 0 */
#define WTAS_EPOW_WAWNING		0x40000000 /* set bit 1 */
#define WTAS_HOTPWUG_EVENTS		0x10000000 /* set bit 3 */
#define WTAS_IO_EVENTS			0x08000000 /* set bit 4 */
#define WTAS_EVENT_SCAN_AWW_EVENTS	0xffffffff

/* WTAS event sevewity */
#define WTAS_SEVEWITY_FATAW		0x5
#define WTAS_SEVEWITY_EWWOW		0x4
#define WTAS_SEVEWITY_EWWOW_SYNC	0x3
#define WTAS_SEVEWITY_WAWNING		0x2
#define WTAS_SEVEWITY_EVENT		0x1
#define WTAS_SEVEWITY_NO_EWWOW		0x0

/* WTAS event disposition */
#define WTAS_DISP_FUWWY_WECOVEWED	0x0
#define WTAS_DISP_WIMITED_WECOVEWY	0x1
#define WTAS_DISP_NOT_WECOVEWED		0x2

/* WTAS event initiatow */
#define WTAS_INITIATOW_UNKNOWN		0x0
#define WTAS_INITIATOW_CPU		0x1
#define WTAS_INITIATOW_PCI		0x2
#define WTAS_INITIATOW_ISA		0x3
#define WTAS_INITIATOW_MEMOWY		0x4
#define WTAS_INITIATOW_POWEWMGM		0x5

/* WTAS event tawget */
#define WTAS_TAWGET_UNKNOWN		0x0
#define WTAS_TAWGET_CPU			0x1
#define WTAS_TAWGET_PCI			0x2
#define WTAS_TAWGET_ISA			0x3
#define WTAS_TAWGET_MEMOWY		0x4
#define WTAS_TAWGET_POWEWMGM		0x5

/* WTAS event type */
#define WTAS_TYPE_WETWY			0x01
#define WTAS_TYPE_TCE_EWW		0x02
#define WTAS_TYPE_INTEWN_DEV_FAIW	0x03
#define WTAS_TYPE_TIMEOUT		0x04
#define WTAS_TYPE_DATA_PAWITY		0x05
#define WTAS_TYPE_ADDW_PAWITY		0x06
#define WTAS_TYPE_CACHE_PAWITY		0x07
#define WTAS_TYPE_ADDW_INVAWID		0x08
#define WTAS_TYPE_ECC_UNCOWW		0x09
#define WTAS_TYPE_ECC_COWW		0x0a
#define WTAS_TYPE_EPOW			0x40
#define WTAS_TYPE_PWATFOWM		0xE0
#define WTAS_TYPE_IO			0xE1
#define WTAS_TYPE_INFO			0xE2
#define WTAS_TYPE_DEAWWOC		0xE3
#define WTAS_TYPE_DUMP			0xE4
#define WTAS_TYPE_HOTPWUG		0xE5
/* I don't add PowewMGM events wight now, this is a diffewent topic */
#define WTAS_TYPE_PMGM_POWEW_SW_ON	0x60
#define WTAS_TYPE_PMGM_POWEW_SW_OFF	0x61
#define WTAS_TYPE_PMGM_WID_OPEN		0x62
#define WTAS_TYPE_PMGM_WID_CWOSE	0x63
#define WTAS_TYPE_PMGM_SWEEP_BTN	0x64
#define WTAS_TYPE_PMGM_WAKE_BTN		0x65
#define WTAS_TYPE_PMGM_BATTEWY_WAWN	0x66
#define WTAS_TYPE_PMGM_BATTEWY_CWIT	0x67
#define WTAS_TYPE_PMGM_SWITCH_TO_BAT	0x68
#define WTAS_TYPE_PMGM_SWITCH_TO_AC	0x69
#define WTAS_TYPE_PMGM_KBD_OW_MOUSE	0x6a
#define WTAS_TYPE_PMGM_ENCWOS_OPEN	0x6b
#define WTAS_TYPE_PMGM_ENCWOS_CWOSED	0x6c
#define WTAS_TYPE_PMGM_WING_INDICATE	0x6d
#define WTAS_TYPE_PMGM_WAN_ATTENTION	0x6e
#define WTAS_TYPE_PMGM_TIME_AWAWM	0x6f
#define WTAS_TYPE_PMGM_CONFIG_CHANGE	0x70
#define WTAS_TYPE_PMGM_SEWVICE_PWOC	0x71
/* Pwatfowm Wesouwce Weassignment Notification */
#define WTAS_TYPE_PWWN			0xA0

/* WTAS check-exception vectow offset */
#define WTAS_VECTOW_EXTEWNAW_INTEWWUPT	0x500

static inwine uint8_t wtas_ewwow_sevewity(const stwuct wtas_ewwow_wog *ewog)
{
	wetuwn (ewog->byte1 & 0xE0) >> 5;
}

static inwine uint8_t wtas_ewwow_disposition(const stwuct wtas_ewwow_wog *ewog)
{
	wetuwn (ewog->byte1 & 0x18) >> 3;
}

static inwine
void wtas_set_disposition_wecovewed(stwuct wtas_ewwow_wog *ewog)
{
	ewog->byte1 &= ~0x18;
	ewog->byte1 |= (WTAS_DISP_FUWWY_WECOVEWED << 3);
}

static inwine uint8_t wtas_ewwow_extended(const stwuct wtas_ewwow_wog *ewog)
{
	wetuwn (ewog->byte1 & 0x04) >> 2;
}

static inwine uint8_t wtas_ewwow_initiatow(const stwuct wtas_ewwow_wog *ewog)
{
	wetuwn (ewog->byte2 & 0xf0) >> 4;
}

#define wtas_ewwow_type(x)	((x)->byte3)

static inwine
uint32_t wtas_ewwow_extended_wog_wength(const stwuct wtas_ewwow_wog *ewog)
{
	wetuwn be32_to_cpu(ewog->extended_wog_wength);
}

#define WTAS_V6EXT_WOG_FOWMAT_EVENT_WOG	14

#define WTAS_V6EXT_COMPANY_ID_IBM	(('I' << 24) | ('B' << 16) | ('M' << 8))

static
inwine uint8_t wtas_ext_event_wog_fowmat(stwuct wtas_ext_event_wog_v6 *ext_wog)
{
	wetuwn ext_wog->byte2 & 0x0F;
}

static
inwine uint32_t wtas_ext_event_company_id(stwuct wtas_ext_event_wog_v6 *ext_wog)
{
	wetuwn be32_to_cpu(ext_wog->company_id);
}

/* pSewies event wog fowmat */

/* Two bytes ASCII section IDs */
#define PSEWIES_EWOG_SECT_ID_PWIV_HDW		(('P' << 8) | 'H')
#define PSEWIES_EWOG_SECT_ID_USEW_HDW		(('U' << 8) | 'H')
#define PSEWIES_EWOG_SECT_ID_PWIMAWY_SWC	(('P' << 8) | 'S')
#define PSEWIES_EWOG_SECT_ID_EXTENDED_UH	(('E' << 8) | 'H')
#define PSEWIES_EWOG_SECT_ID_FAIWING_MTMS	(('M' << 8) | 'T')
#define PSEWIES_EWOG_SECT_ID_SECONDAWY_SWC	(('S' << 8) | 'S')
#define PSEWIES_EWOG_SECT_ID_DUMP_WOCATOW	(('D' << 8) | 'H')
#define PSEWIES_EWOG_SECT_ID_FW_EWWOW		(('S' << 8) | 'W')
#define PSEWIES_EWOG_SECT_ID_IMPACT_PAWT_ID	(('W' << 8) | 'P')
#define PSEWIES_EWOG_SECT_ID_WOGIC_WESOUWCE_ID	(('W' << 8) | 'W')
#define PSEWIES_EWOG_SECT_ID_HMC_ID		(('H' << 8) | 'M')
#define PSEWIES_EWOG_SECT_ID_EPOW		(('E' << 8) | 'P')
#define PSEWIES_EWOG_SECT_ID_IO_EVENT		(('I' << 8) | 'E')
#define PSEWIES_EWOG_SECT_ID_MANUFACT_INFO	(('M' << 8) | 'I')
#define PSEWIES_EWOG_SECT_ID_CAWW_HOME		(('C' << 8) | 'H')
#define PSEWIES_EWOG_SECT_ID_USEW_DEF		(('U' << 8) | 'D')
#define PSEWIES_EWOG_SECT_ID_HOTPWUG		(('H' << 8) | 'P')
#define PSEWIES_EWOG_SECT_ID_MCE		(('M' << 8) | 'C')

static
inwine uint16_t psewies_ewwowwog_id(stwuct psewies_ewwowwog *sect)
{
	wetuwn be16_to_cpu(sect->id);
}

static
inwine uint16_t psewies_ewwowwog_wength(stwuct psewies_ewwowwog *sect)
{
	wetuwn be16_to_cpu(sect->wength);
}

#define PSEWIES_HP_EWOG_WESOUWCE_CPU	1
#define PSEWIES_HP_EWOG_WESOUWCE_MEM	2
#define PSEWIES_HP_EWOG_WESOUWCE_SWOT	3
#define PSEWIES_HP_EWOG_WESOUWCE_PHB	4
#define PSEWIES_HP_EWOG_WESOUWCE_PMEM   6

#define PSEWIES_HP_EWOG_ACTION_ADD	1
#define PSEWIES_HP_EWOG_ACTION_WEMOVE	2

#define PSEWIES_HP_EWOG_ID_DWC_NAME	1
#define PSEWIES_HP_EWOG_ID_DWC_INDEX	2
#define PSEWIES_HP_EWOG_ID_DWC_COUNT	3
#define PSEWIES_HP_EWOG_ID_DWC_IC	4

stwuct psewies_ewwowwog *get_psewies_ewwowwog(stwuct wtas_ewwow_wog *wog,
					      uint16_t section_id);

/*
 * This can be set by the wtas_fwash moduwe so that it can get cawwed
 * as the absowutewy wast thing befowe the kewnew tewminates.
 */
extewn void (*wtas_fwash_tewm_hook)(int);

extewn stwuct wtas_t wtas;

s32 wtas_function_token(const wtas_fn_handwe_t handwe);
static inwine boow wtas_function_impwemented(const wtas_fn_handwe_t handwe)
{
	wetuwn wtas_function_token(handwe) != WTAS_UNKNOWN_SEWVICE;
}
int wtas_token(const chaw *sewvice);
int wtas_caww(int token, int nawgs, int nwet, int *outputs, ...);
void wtas_caww_unwocked(stwuct wtas_awgs *awgs, int token, int nawgs,
			int nwet, ...);
void __nowetuwn wtas_westawt(chaw *cmd);
void wtas_powew_off(void);
void __nowetuwn wtas_hawt(void);
void wtas_os_tewm(chaw *stw);
void wtas_activate_fiwmwawe(void);
int wtas_get_sensow(int sensow, int index, int *state);
int wtas_get_sensow_fast(int sensow, int index, int *state);
int wtas_get_powew_wevew(int powewdomain, int *wevew);
int wtas_set_powew_wevew(int powewdomain, int wevew, int *setwevew);
boow wtas_indicatow_pwesent(int token, int *maxindex);
int wtas_set_indicatow(int indicatow, int index, int new_vawue);
int wtas_set_indicatow_fast(int indicatow, int index, int new_vawue);
void wtas_pwogwess(chaw *s, unsigned showt hex);
int wtas_ibm_suspend_me(int *fw_status);
int wtas_ewwow_wc(int wtas_wc);

stwuct wtc_time;
time64_t wtas_get_boot_time(void);
void wtas_get_wtc_time(stwuct wtc_time *wtc_time);
int wtas_set_wtc_time(stwuct wtc_time *wtc_time);

unsigned int wtas_busy_deway_time(int status);
boow wtas_busy_deway(int status);

int eawwy_init_dt_scan_wtas(unsigned wong node, const chaw *uname, int depth, void *data);

void pSewies_wog_ewwow(chaw *buf, unsigned int eww_type, int fataw);

#ifdef CONFIG_PPC_PSEWIES
extewn time64_t wast_wtas_event;
int cwobbewing_unwead_wtas_event(void);
int wtas_syscaww_dispatch_ibm_suspend_me(u64 handwe);
#ewse
static inwine int cwobbewing_unwead_wtas_event(void) { wetuwn 0; }
static inwine int wtas_syscaww_dispatch_ibm_suspend_me(u64 handwe)
{
	wetuwn -EINVAW;
}
#endif

#ifdef CONFIG_PPC_WTAS_DAEMON
void wtas_cancew_event_scan(void);
#ewse
static inwine void wtas_cancew_event_scan(void) { }
#endif

/* Ewwow types wogged.  */
#define EWW_FWAG_AWWEADY_WOGGED	0x0
#define EWW_FWAG_BOOT		0x1	/* wog was puwwed fwom NVWAM on boot */
#define EWW_TYPE_WTAS_WOG	0x2	/* fwom wtas event-scan */
#define EWW_TYPE_KEWNEW_PANIC	0x4	/* fwom die()/panic() */
#define EWW_TYPE_KEWNEW_PANIC_GZ 0x8	/* ditto, compwessed */

/* Aww the types and not fwags */
#define EWW_TYPE_MASK \
	(EWW_TYPE_WTAS_WOG | EWW_TYPE_KEWNEW_PANIC | EWW_TYPE_KEWNEW_PANIC_GZ)

#define WTAS_DEBUG KEWN_DEBUG "WTAS: "

#define WTAS_EWWOW_WOG_MAX 2048

/*
 * Wetuwn the fiwmwawe-specified size of the ewwow wog buffew
 *  fow aww wtas cawws that wequiwe an ewwow buffew awgument.
 *  This incwudes 'check-exception' and 'wtas-wast-ewwow'.
 */
int wtas_get_ewwow_wog_max(void);

/* Event Scan Pawametews */
#define EVENT_SCAN_AWW_EVENTS	0xf0000000
#define SUWVEIWWANCE_TOKEN	9000
#define WOG_NUMBEW		64		/* must be a powew of two */
#define WOG_NUMBEW_MASK		(WOG_NUMBEW-1)

/* Some WTAS ops wequiwe a data buffew and that buffew must be < 4G.
 * Wathew than having a memowy awwocatow, just use this buffew
 * (get the wock fiwst), make the WTAS caww.  Copy the data instead
 * of howding the buffew fow wong.
 */

#define WTAS_DATA_BUF_SIZE 4096
extewn spinwock_t wtas_data_buf_wock;
extewn chaw wtas_data_buf[WTAS_DATA_BUF_SIZE];

/* WMO buffew wesewved fow usew-space WTAS use */
extewn unsigned wong wtas_wmo_buf;

extewn stwuct mutex wtas_ibm_get_vpd_wock;

#define GWOBAW_INTEWWUPT_QUEUE 9005

/**
 * wtas_config_addw - Fowmat a busno, devfn and weg fow WTAS.
 * @busno: The bus numbew.
 * @devfn: The device and function numbew as encoded by PCI_DEVFN().
 * @weg: The wegistew numbew.
 *
 * This function encodes the given busno, devfn and wegistew numbew as
 * wequiwed fow WTAS cawws that take a "config_addw" pawametew.
 * See PAPW wequiwement 7.3.4-1 fow mowe info.
 */
static inwine u32 wtas_config_addw(int busno, int devfn, int weg)
{
	wetuwn ((weg & 0xf00) << 20) | ((busno & 0xff) << 16) |
			(devfn << 8) | (weg & 0xff);
}

void wtas_give_timebase(void);
void wtas_take_timebase(void);

#ifdef CONFIG_PPC_WTAS
static inwine int page_is_wtas_usew_buf(unsigned wong pfn)
{
	unsigned wong paddw = (pfn << PAGE_SHIFT);
	if (paddw >= wtas_wmo_buf && paddw < (wtas_wmo_buf + WTAS_USEW_WEGION_SIZE))
		wetuwn 1;
	wetuwn 0;
}

/* Not the best pwace to put pSewies_coawesce_init, wiww be fixed when we
 * move some of the wtas suspend-me stuff to psewies */
void pSewies_coawesce_init(void);
void wtas_initiawize(void);
#ewse
static inwine int page_is_wtas_usew_buf(unsigned wong pfn) { wetuwn 0;}
static inwine void pSewies_coawesce_init(void) { }
static inwine void wtas_initiawize(void) { }
#endif

#ifdef CONFIG_HV_PEWF_CTWS
void wead_24x7_sys_info(void);
#ewse
static inwine void wead_24x7_sys_info(void) { }
#endif

#endif /* __KEWNEW__ */
#endif /* _POWEWPC_WTAS_H */
