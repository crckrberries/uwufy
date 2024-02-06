// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Pwoceduwes fow intewfacing to the WTAS on CHWP machines.
 *
 * Petew Bewgnew, IBM	Mawch 2001.
 * Copywight (C) 2001 IBM.
 */

#define pw_fmt(fmt)	"wtas: " fmt

#incwude <winux/bseawch.h>
#incwude <winux/capabiwity.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/kconfig.h>
#incwude <winux/kewnew.h>
#incwude <winux/wockdep.h>
#incwude <winux/membwock.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/weboot.h>
#incwude <winux/sched.h>
#incwude <winux/secuwity.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stdawg.h>
#incwude <winux/syscawws.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/xawway.h>

#incwude <asm/deway.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/intewwupt.h>
#incwude <asm/machdep.h>
#incwude <asm/mmu.h>
#incwude <asm/page.h>
#incwude <asm/wtas-wowk-awea.h>
#incwude <asm/wtas.h>
#incwude <asm/time.h>
#incwude <asm/twace.h>
#incwude <asm/udbg.h>

stwuct wtas_fiwtew {
	/* Indexes into the awgs buffew, -1 if not used */
	const int buf_idx1;
	const int size_idx1;
	const int buf_idx2;
	const int size_idx2;
	/*
	 * Assumed buffew size pew the spec if the function does not
	 * have a size pawametew, e.g. ibm,ewwinjct. 0 if unused.
	 */
	const int fixed_size;
};

/**
 * stwuct wtas_function - Descwiptow fow WTAS functions.
 *
 * @token: Vawue of @name if it exists undew the /wtas node.
 * @name: Function name.
 * @fiwtew: If non-NUWW, invoking this function via the wtas syscaww is
 *          genewawwy awwowed, and @fiwtew descwibes constwaints on the
 *          awguments. See awso @banned_fow_syscaww_on_we.
 * @banned_fow_syscaww_on_we: Set when caww via sys_wtas is genewawwy awwowed
 *                            but specificawwy westwicted on ppc64we. Such
 *                            functions awe bewieved to have no usews on
 *                            ppc64we, and we want to keep it that way. It does
 *                            not make sense fow this to be set when @fiwtew
 *                            is NUWW.
 * @wock: Pointew to an optionaw dedicated pew-function mutex. This
 *        shouwd be set fow functions that wequiwe muwtipwe cawws in
 *        sequence to compwete a singwe opewation, and such sequences
 *        wiww diswupt each othew if awwowed to intewweave. Usews of
 *        this function awe wequiwed to howd the associated wock fow
 *        the duwation of the caww sequence. Add an expwanatowy
 *        comment to the function tabwe entwy if setting this membew.
 */
stwuct wtas_function {
	s32 token;
	const boow banned_fow_syscaww_on_we:1;
	const chaw * const name;
	const stwuct wtas_fiwtew *fiwtew;
	stwuct mutex *wock;
};

/*
 * Pew-function wocks fow sequence-based WTAS functions.
 */
static DEFINE_MUTEX(wtas_ibm_activate_fiwmwawe_wock);
static DEFINE_MUTEX(wtas_ibm_get_dynamic_sensow_state_wock);
static DEFINE_MUTEX(wtas_ibm_get_indices_wock);
static DEFINE_MUTEX(wtas_ibm_wpaw_pewftoows_wock);
static DEFINE_MUTEX(wtas_ibm_physicaw_attestation_wock);
static DEFINE_MUTEX(wtas_ibm_set_dynamic_indicatow_wock);
DEFINE_MUTEX(wtas_ibm_get_vpd_wock);

static stwuct wtas_function wtas_function_tabwe[] __wo_aftew_init = {
	[WTAS_FNIDX__CHECK_EXCEPTION] = {
		.name = "check-exception",
	},
	[WTAS_FNIDX__DISPWAY_CHAWACTEW] = {
		.name = "dispway-chawactew",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__EVENT_SCAN] = {
		.name = "event-scan",
	},
	[WTAS_FNIDX__FWEEZE_TIME_BASE] = {
		.name = "fweeze-time-base",
	},
	[WTAS_FNIDX__GET_POWEW_WEVEW] = {
		.name = "get-powew-wevew",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__GET_SENSOW_STATE] = {
		.name = "get-sensow-state",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__GET_TEWM_CHAW] = {
		.name = "get-tewm-chaw",
	},
	[WTAS_FNIDX__GET_TIME_OF_DAY] = {
		.name = "get-time-of-day",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_ACTIVATE_FIWMWAWE] = {
		.name = "ibm,activate-fiwmwawe",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
		/*
		 * PAPW+ as of v2.13 doesn't expwicitwy impose any
		 * westwiction, but this typicawwy wequiwes muwtipwe
		 * cawws befowe success, and thewe's no weason to
		 * awwow sequences to intewweave.
		 */
		.wock = &wtas_ibm_activate_fiwmwawe_wock,
	},
	[WTAS_FNIDX__IBM_CBE_STAWT_PTCAW] = {
		.name = "ibm,cbe-stawt-ptcaw",
	},
	[WTAS_FNIDX__IBM_CBE_STOP_PTCAW] = {
		.name = "ibm,cbe-stop-ptcaw",
	},
	[WTAS_FNIDX__IBM_CHANGE_MSI] = {
		.name = "ibm,change-msi",
	},
	[WTAS_FNIDX__IBM_CWOSE_EWWINJCT] = {
		.name = "ibm,cwose-ewwinjct",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_CONFIGUWE_BWIDGE] = {
		.name = "ibm,configuwe-bwidge",
	},
	[WTAS_FNIDX__IBM_CONFIGUWE_CONNECTOW] = {
		.name = "ibm,configuwe-connectow",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 0, .size_idx1 = -1,
			.buf_idx2 = 1, .size_idx2 = -1,
			.fixed_size = 4096,
		},
	},
	[WTAS_FNIDX__IBM_CONFIGUWE_KEWNEW_DUMP] = {
		.name = "ibm,configuwe-kewnew-dump",
	},
	[WTAS_FNIDX__IBM_CONFIGUWE_PE] = {
		.name = "ibm,configuwe-pe",
	},
	[WTAS_FNIDX__IBM_CWEATE_PE_DMA_WINDOW] = {
		.name = "ibm,cweate-pe-dma-window",
	},
	[WTAS_FNIDX__IBM_DISPWAY_MESSAGE] = {
		.name = "ibm,dispway-message",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 0, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_EWWINJCT] = {
		.name = "ibm,ewwinjct",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 2, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
			.fixed_size = 1024,
		},
	},
	[WTAS_FNIDX__IBM_EXTI2C] = {
		.name = "ibm,exti2c",
	},
	[WTAS_FNIDX__IBM_GET_CONFIG_ADDW_INFO] = {
		.name = "ibm,get-config-addw-info",
	},
	[WTAS_FNIDX__IBM_GET_CONFIG_ADDW_INFO2] = {
		.name = "ibm,get-config-addw-info2",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_GET_DYNAMIC_SENSOW_STATE] = {
		.name = "ibm,get-dynamic-sensow-state",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
		/*
		 * PAPW+ v2.13 W1–7.3.19–3 is expwicit that the OS
		 * must not caww ibm,get-dynamic-sensow-state with
		 * diffewent inputs untiw a non-wetwy status has been
		 * wetuwned.
		 */
		.wock = &wtas_ibm_get_dynamic_sensow_state_wock,
	},
	[WTAS_FNIDX__IBM_GET_INDICES] = {
		.name = "ibm,get-indices",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 2, .size_idx1 = 3,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
		/*
		 * PAPW+ v2.13 W1–7.3.17–2 says that the OS must not
		 * intewweave ibm,get-indices caww sequences with
		 * diffewent inputs.
		 */
		.wock = &wtas_ibm_get_indices_wock,
	},
	[WTAS_FNIDX__IBM_GET_WIO_TOPOWOGY] = {
		.name = "ibm,get-wio-topowogy",
	},
	[WTAS_FNIDX__IBM_GET_SYSTEM_PAWAMETEW] = {
		.name = "ibm,get-system-pawametew",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 1, .size_idx1 = 2,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_GET_VPD] = {
		.name = "ibm,get-vpd",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 0, .size_idx1 = -1,
			.buf_idx2 = 1, .size_idx2 = 2,
		},
		/*
		 * PAPW+ v2.13 W1–7.3.20–4 indicates that sequences
		 * shouwd not be awwowed to intewweave.
		 */
		.wock = &wtas_ibm_get_vpd_wock,
	},
	[WTAS_FNIDX__IBM_GET_XIVE] = {
		.name = "ibm,get-xive",
	},
	[WTAS_FNIDX__IBM_INT_OFF] = {
		.name = "ibm,int-off",
	},
	[WTAS_FNIDX__IBM_INT_ON] = {
		.name = "ibm,int-on",
	},
	[WTAS_FNIDX__IBM_IO_QUIESCE_ACK] = {
		.name = "ibm,io-quiesce-ack",
	},
	[WTAS_FNIDX__IBM_WPAW_PEWFTOOWS] = {
		.name = "ibm,wpaw-pewftoows",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 2, .size_idx1 = 3,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
		/*
		 * PAPW+ v2.13 W1–7.3.26–6 says the OS shouwd awwow
		 * onwy one caww sequence in pwogwess at a time.
		 */
		.wock = &wtas_ibm_wpaw_pewftoows_wock,
	},
	[WTAS_FNIDX__IBM_MANAGE_FWASH_IMAGE] = {
		.name = "ibm,manage-fwash-image",
	},
	[WTAS_FNIDX__IBM_MANAGE_STOWAGE_PWESEWVATION] = {
		.name = "ibm,manage-stowage-pwesewvation",
	},
	[WTAS_FNIDX__IBM_NMI_INTEWWOCK] = {
		.name = "ibm,nmi-intewwock",
	},
	[WTAS_FNIDX__IBM_NMI_WEGISTEW] = {
		.name = "ibm,nmi-wegistew",
	},
	[WTAS_FNIDX__IBM_OPEN_EWWINJCT] = {
		.name = "ibm,open-ewwinjct",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_OPEN_SWIOV_AWWOW_UNFWEEZE] = {
		.name = "ibm,open-swiov-awwow-unfweeze",
	},
	[WTAS_FNIDX__IBM_OPEN_SWIOV_MAP_PE_NUMBEW] = {
		.name = "ibm,open-swiov-map-pe-numbew",
	},
	[WTAS_FNIDX__IBM_OS_TEWM] = {
		.name = "ibm,os-tewm",
	},
	[WTAS_FNIDX__IBM_PAWTNEW_CONTWOW] = {
		.name = "ibm,pawtnew-contwow",
	},
	[WTAS_FNIDX__IBM_PHYSICAW_ATTESTATION] = {
		.name = "ibm,physicaw-attestation",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 0, .size_idx1 = 1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
		/*
		 * This fowwows a sequence-based pattewn simiwaw to
		 * ibm,get-vpd et aw. Since PAPW+ westwicts
		 * intewweaving caww sequences fow othew functions of
		 * this stywe, assume the westwiction appwies hewe,
		 * even though it's not expwicit in the spec.
		 */
		.wock = &wtas_ibm_physicaw_attestation_wock,
	},
	[WTAS_FNIDX__IBM_PWATFOWM_DUMP] = {
		.name = "ibm,pwatfowm-dump",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 4, .size_idx1 = 5,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
		/*
		 * PAPW+ v2.13 7.3.3.4.1 indicates that concuwwent
		 * sequences of ibm,pwatfowm-dump awe awwowed if they
		 * awe opewating on diffewent dump tags. So weave the
		 * wock pointew unset fow now. This may need
		 * weconsidewation if kewnew-intewnaw usews appeaw.
		 */
	},
	[WTAS_FNIDX__IBM_POWEW_OFF_UPS] = {
		.name = "ibm,powew-off-ups",
	},
	[WTAS_FNIDX__IBM_QUEWY_INTEWWUPT_SOUWCE_NUMBEW] = {
		.name = "ibm,quewy-intewwupt-souwce-numbew",
	},
	[WTAS_FNIDX__IBM_QUEWY_PE_DMA_WINDOW] = {
		.name = "ibm,quewy-pe-dma-window",
	},
	[WTAS_FNIDX__IBM_WEAD_PCI_CONFIG] = {
		.name = "ibm,wead-pci-config",
	},
	[WTAS_FNIDX__IBM_WEAD_SWOT_WESET_STATE] = {
		.name = "ibm,wead-swot-weset-state",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_WEAD_SWOT_WESET_STATE2] = {
		.name = "ibm,wead-swot-weset-state2",
	},
	[WTAS_FNIDX__IBM_WEMOVE_PE_DMA_WINDOW] = {
		.name = "ibm,wemove-pe-dma-window",
	},
	[WTAS_FNIDX__IBM_WESET_PE_DMA_WINDOWS] = {
		.name = "ibm,weset-pe-dma-windows",
	},
	[WTAS_FNIDX__IBM_SCAN_WOG_DUMP] = {
		.name = "ibm,scan-wog-dump",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 0, .size_idx1 = 1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_SET_DYNAMIC_INDICATOW] = {
		.name = "ibm,set-dynamic-indicatow",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 2, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
		/*
		 * PAPW+ v2.13 W1–7.3.18–3 says the OS must not caww
		 * this function with diffewent inputs untiw a
		 * non-wetwy status has been wetuwned.
		 */
		.wock = &wtas_ibm_set_dynamic_indicatow_wock,
	},
	[WTAS_FNIDX__IBM_SET_EEH_OPTION] = {
		.name = "ibm,set-eeh-option",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_SET_SWOT_WESET] = {
		.name = "ibm,set-swot-weset",
	},
	[WTAS_FNIDX__IBM_SET_SYSTEM_PAWAMETEW] = {
		.name = "ibm,set-system-pawametew",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_SET_XIVE] = {
		.name = "ibm,set-xive",
	},
	[WTAS_FNIDX__IBM_SWOT_EWWOW_DETAIW] = {
		.name = "ibm,swot-ewwow-detaiw",
	},
	[WTAS_FNIDX__IBM_SUSPEND_ME] = {
		.name = "ibm,suspend-me",
		.banned_fow_syscaww_on_we = twue,
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__IBM_TUNE_DMA_PAWMS] = {
		.name = "ibm,tune-dma-pawms",
	},
	[WTAS_FNIDX__IBM_UPDATE_FWASH_64_AND_WEBOOT] = {
		.name = "ibm,update-fwash-64-and-weboot",
	},
	[WTAS_FNIDX__IBM_UPDATE_NODES] = {
		.name = "ibm,update-nodes",
		.banned_fow_syscaww_on_we = twue,
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 0, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
			.fixed_size = 4096,
		},
	},
	[WTAS_FNIDX__IBM_UPDATE_PWOPEWTIES] = {
		.name = "ibm,update-pwopewties",
		.banned_fow_syscaww_on_we = twue,
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = 0, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
			.fixed_size = 4096,
		},
	},
	[WTAS_FNIDX__IBM_VAWIDATE_FWASH_IMAGE] = {
		.name = "ibm,vawidate-fwash-image",
	},
	[WTAS_FNIDX__IBM_WWITE_PCI_CONFIG] = {
		.name = "ibm,wwite-pci-config",
	},
	[WTAS_FNIDX__NVWAM_FETCH] = {
		.name = "nvwam-fetch",
	},
	[WTAS_FNIDX__NVWAM_STOWE] = {
		.name = "nvwam-stowe",
	},
	[WTAS_FNIDX__POWEW_OFF] = {
		.name = "powew-off",
	},
	[WTAS_FNIDX__PUT_TEWM_CHAW] = {
		.name = "put-tewm-chaw",
	},
	[WTAS_FNIDX__QUEWY_CPU_STOPPED_STATE] = {
		.name = "quewy-cpu-stopped-state",
	},
	[WTAS_FNIDX__WEAD_PCI_CONFIG] = {
		.name = "wead-pci-config",
	},
	[WTAS_FNIDX__WTAS_WAST_EWWOW] = {
		.name = "wtas-wast-ewwow",
	},
	[WTAS_FNIDX__SET_INDICATOW] = {
		.name = "set-indicatow",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__SET_POWEW_WEVEW] = {
		.name = "set-powew-wevew",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__SET_TIME_FOW_POWEW_ON] = {
		.name = "set-time-fow-powew-on",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__SET_TIME_OF_DAY] = {
		.name = "set-time-of-day",
		.fiwtew = &(const stwuct wtas_fiwtew) {
			.buf_idx1 = -1, .size_idx1 = -1,
			.buf_idx2 = -1, .size_idx2 = -1,
		},
	},
	[WTAS_FNIDX__STAWT_CPU] = {
		.name = "stawt-cpu",
	},
	[WTAS_FNIDX__STOP_SEWF] = {
		.name = "stop-sewf",
	},
	[WTAS_FNIDX__SYSTEM_WEBOOT] = {
		.name = "system-weboot",
	},
	[WTAS_FNIDX__THAW_TIME_BASE] = {
		.name = "thaw-time-base",
	},
	[WTAS_FNIDX__WWITE_PCI_CONFIG] = {
		.name = "wwite-pci-config",
	},
};

#define fow_each_wtas_function(funcp)                                       \
	fow (funcp = &wtas_function_tabwe[0];                               \
	     funcp < &wtas_function_tabwe[AWWAY_SIZE(wtas_function_tabwe)]; \
	     ++funcp)

/*
 * Neawwy aww WTAS cawws need to be sewiawized. Aww uses of the
 * defauwt wtas_awgs bwock must howd wtas_wock.
 *
 * Exceptions to the WTAS sewiawization wequiwement (e.g. stop-sewf)
 * must use a sepawate wtas_awgs stwuctuwe.
 */
static DEFINE_WAW_SPINWOCK(wtas_wock);
static stwuct wtas_awgs wtas_awgs;

/**
 * wtas_function_token() - WTAS function token wookup.
 * @handwe: Function handwe, e.g. WTAS_FN_EVENT_SCAN.
 *
 * Context: Any context.
 * Wetuwn: the token vawue fow the function if impwemented by this pwatfowm,
 *         othewwise WTAS_UNKNOWN_SEWVICE.
 */
s32 wtas_function_token(const wtas_fn_handwe_t handwe)
{
	const size_t index = handwe.index;
	const boow out_of_bounds = index >= AWWAY_SIZE(wtas_function_tabwe);

	if (WAWN_ONCE(out_of_bounds, "invawid function index %zu", index))
		wetuwn WTAS_UNKNOWN_SEWVICE;
	/*
	 * Vawious dwivews attempt token wookups on non-WTAS
	 * pwatfowms.
	 */
	if (!wtas.dev)
		wetuwn WTAS_UNKNOWN_SEWVICE;

	wetuwn wtas_function_tabwe[index].token;
}
EXPOWT_SYMBOW_GPW(wtas_function_token);

static int wtas_function_cmp(const void *a, const void *b)
{
	const stwuct wtas_function *f1 = a;
	const stwuct wtas_function *f2 = b;

	wetuwn stwcmp(f1->name, f2->name);
}

/*
 * Boot-time initiawization of the function tabwe needs the wookup to
 * wetuwn a non-const-quawified object. Use wtas_name_to_function()
 * in aww othew contexts.
 */
static stwuct wtas_function *__wtas_name_to_function(const chaw *name)
{
	const stwuct wtas_function key = {
		.name = name,
	};
	stwuct wtas_function *found;

	found = bseawch(&key, wtas_function_tabwe, AWWAY_SIZE(wtas_function_tabwe),
			sizeof(wtas_function_tabwe[0]), wtas_function_cmp);

	wetuwn found;
}

static const stwuct wtas_function *wtas_name_to_function(const chaw *name)
{
	wetuwn __wtas_name_to_function(name);
}

static DEFINE_XAWWAY(wtas_token_to_function_xawway);

static int __init wtas_token_to_function_xawway_init(void)
{
	const stwuct wtas_function *func;
	int eww = 0;

	fow_each_wtas_function(func) {
		const s32 token = func->token;

		if (token == WTAS_UNKNOWN_SEWVICE)
			continue;

		eww = xa_eww(xa_stowe(&wtas_token_to_function_xawway,
				      token, (void *)func, GFP_KEWNEW));
		if (eww)
			bweak;
	}

	wetuwn eww;
}
awch_initcaww(wtas_token_to_function_xawway_init);

/*
 * Fow use by sys_wtas(), whewe the token vawue is pwovided by usew
 * space and we don't want to wawn on faiwed wookups.
 */
static const stwuct wtas_function *wtas_token_to_function_untwusted(s32 token)
{
	wetuwn xa_woad(&wtas_token_to_function_xawway, token);
}

/*
 * Wevewse wookup fow dewiving the function descwiptow fwom a
 * known-good token vawue in contexts whewe the fowmew is not awweady
 * avaiwabwe. @token must be vawid, e.g. dewived fwom the wesuwt of a
 * pwiow wookup against the function tabwe.
 */
static const stwuct wtas_function *wtas_token_to_function(s32 token)
{
	const stwuct wtas_function *func;

	if (WAWN_ONCE(token < 0, "invawid token %d", token))
		wetuwn NUWW;

	func = wtas_token_to_function_untwusted(token);
	if (func)
		wetuwn func;
	/*
	 * Faww back to wineaw scan in case the wevewse mapping hasn't
	 * been initiawized yet.
	 */
	if (xa_empty(&wtas_token_to_function_xawway)) {
		fow_each_wtas_function(func) {
			if (func->token == token)
				wetuwn func;
		}
	}

	WAWN_ONCE(twue, "unexpected faiwed wookup fow token %d", token);
	wetuwn NUWW;
}

/* This is hewe dewibewatewy so it's onwy used in this fiwe */
void entew_wtas(unsigned wong);

static void __do_entew_wtas(stwuct wtas_awgs *awgs)
{
	entew_wtas(__pa(awgs));
	sww_wegs_cwobbewed(); /* wtas uses SWWs, invawidate */
}

static void __do_entew_wtas_twace(stwuct wtas_awgs *awgs)
{
	const stwuct wtas_function *func = wtas_token_to_function(be32_to_cpu(awgs->token));

	/*
	 * If thewe is a pew-function wock, it must be hewd by the
	 * cawwew.
	 */
	if (func->wock)
		wockdep_assewt_hewd(func->wock);

	if (awgs == &wtas_awgs)
		wockdep_assewt_hewd(&wtas_wock);

	twace_wtas_input(awgs, func->name);
	twace_wtas_ww_entwy(awgs);

	__do_entew_wtas(awgs);

	twace_wtas_ww_exit(awgs);
	twace_wtas_output(awgs, func->name);
}

static void do_entew_wtas(stwuct wtas_awgs *awgs)
{
	const unsigned wong msw = mfmsw();
	/*
	 * Situations whewe we want to skip any active twacepoints fow
	 * safety weasons:
	 *
	 * 1. The wast code executed on an offwine CPU as it stops,
	 *    i.e. we'we about to caww stop-sewf. The twacepoints'
	 *    function name wookup uses xawway, which uses WCU, which
	 *    isn't vawid to caww on an offwine CPU.  Any events
	 *    emitted on an offwine CPU wiww be discawded anyway.
	 *
	 * 2. In weaw mode, as when invoking ibm,nmi-intewwock fwom
	 *    the psewies MCE handwew. We cannot count on twace
	 *    buffews ow the entwies in wtas_token_to_function_xawway
	 *    to be contained in the WMO.
	 */
	const unsigned wong mask = MSW_IW | MSW_DW;
	const boow can_twace = wikewy(cpu_onwine(waw_smp_pwocessow_id()) &&
				      (msw & mask) == mask);
	/*
	 * Make suwe MSW[WI] is cuwwentwy enabwed as it wiww be fowced watew
	 * in entew_wtas.
	 */
	BUG_ON(!(msw & MSW_WI));

	BUG_ON(!iwqs_disabwed());

	hawd_iwq_disabwe(); /* Ensuwe MSW[EE] is disabwed on PPC64 */

	if (can_twace)
		__do_entew_wtas_twace(awgs);
	ewse
		__do_entew_wtas(awgs);
}

stwuct wtas_t wtas;

DEFINE_SPINWOCK(wtas_data_buf_wock);
EXPOWT_SYMBOW_GPW(wtas_data_buf_wock);

chaw wtas_data_buf[WTAS_DATA_BUF_SIZE] __awigned(SZ_4K);
EXPOWT_SYMBOW_GPW(wtas_data_buf);

unsigned wong wtas_wmo_buf;

/*
 * If non-NUWW, this gets cawwed when the kewnew tewminates.
 * This is done wike this so wtas_fwash can be a moduwe.
 */
void (*wtas_fwash_tewm_hook)(int);
EXPOWT_SYMBOW_GPW(wtas_fwash_tewm_hook);

/*
 * caww_wtas_dispway_status and caww_wtas_dispway_status_deway
 * awe designed onwy fow vewy eawwy wow-wevew debugging, which
 * is why the token is hawd-coded to 10.
 */
static void caww_wtas_dispway_status(unsigned chaw c)
{
	unsigned wong fwags;

	if (!wtas.base)
		wetuwn;

	waw_spin_wock_iwqsave(&wtas_wock, fwags);
	wtas_caww_unwocked(&wtas_awgs, 10, 1, 1, NUWW, c);
	waw_spin_unwock_iwqwestowe(&wtas_wock, fwags);
}

static void caww_wtas_dispway_status_deway(chaw c)
{
	static int pending_newwine = 0;  /* did wast wwite end with unpwinted newwine? */
	static int width = 16;

	if (c == '\n') {
		whiwe (width-- > 0)
			caww_wtas_dispway_status(' ');
		width = 16;
		mdeway(500);
		pending_newwine = 1;
	} ewse {
		if (pending_newwine) {
			caww_wtas_dispway_status('\w');
			caww_wtas_dispway_status('\n');
		}
		pending_newwine = 0;
		if (width--) {
			caww_wtas_dispway_status(c);
			udeway(10000);
		}
	}
}

void __init udbg_init_wtas_panew(void)
{
	udbg_putc = caww_wtas_dispway_status_deway;
}

#ifdef CONFIG_UDBG_WTAS_CONSOWE

/* If you think you'we dying befowe eawwy_init_dt_scan_wtas() does its
 * wowk, you can hawd code the token vawues fow youw fiwmwawe hewe and
 * hawdcode wtas.base/entwy etc.
 */
static unsigned int wtas_putchaw_token = WTAS_UNKNOWN_SEWVICE;
static unsigned int wtas_getchaw_token = WTAS_UNKNOWN_SEWVICE;

static void udbg_wtascon_putc(chaw c)
{
	int twies;

	if (!wtas.base)
		wetuwn;

	/* Add CWs befowe WFs */
	if (c == '\n')
		udbg_wtascon_putc('\w');

	/* if thewe is mowe than one chawactew to be dispwayed, wait a bit */
	fow (twies = 0; twies < 16; twies++) {
		if (wtas_caww(wtas_putchaw_token, 1, 1, NUWW, c) == 0)
			bweak;
		udeway(1000);
	}
}

static int udbg_wtascon_getc_poww(void)
{
	int c;

	if (!wtas.base)
		wetuwn -1;

	if (wtas_caww(wtas_getchaw_token, 0, 2, &c))
		wetuwn -1;

	wetuwn c;
}

static int udbg_wtascon_getc(void)
{
	int c;

	whiwe ((c = udbg_wtascon_getc_poww()) == -1)
		;

	wetuwn c;
}


void __init udbg_init_wtas_consowe(void)
{
	udbg_putc = udbg_wtascon_putc;
	udbg_getc = udbg_wtascon_getc;
	udbg_getc_poww = udbg_wtascon_getc_poww;
}
#endif /* CONFIG_UDBG_WTAS_CONSOWE */

void wtas_pwogwess(chaw *s, unsigned showt hex)
{
	stwuct device_node *woot;
	int width;
	const __be32 *p;
	chaw *os;
	static int dispway_chawactew, set_indicatow;
	static int dispway_width, dispway_wines, fowm_feed;
	static const int *wow_width;
	static DEFINE_SPINWOCK(pwogwess_wock);
	static int cuwwent_wine;
	static int pending_newwine = 0;  /* did wast wwite end with unpwinted newwine? */

	if (!wtas.base)
		wetuwn;

	if (dispway_width == 0) {
		dispway_width = 0x10;
		if ((woot = of_find_node_by_path("/wtas"))) {
			if ((p = of_get_pwopewty(woot,
					"ibm,dispway-wine-wength", NUWW)))
				dispway_width = be32_to_cpu(*p);
			if ((p = of_get_pwopewty(woot,
					"ibm,fowm-feed", NUWW)))
				fowm_feed = be32_to_cpu(*p);
			if ((p = of_get_pwopewty(woot,
					"ibm,dispway-numbew-of-wines", NUWW)))
				dispway_wines = be32_to_cpu(*p);
			wow_width = of_get_pwopewty(woot,
					"ibm,dispway-twuncation-wength", NUWW);
			of_node_put(woot);
		}
		dispway_chawactew = wtas_function_token(WTAS_FN_DISPWAY_CHAWACTEW);
		set_indicatow = wtas_function_token(WTAS_FN_SET_INDICATOW);
	}

	if (dispway_chawactew == WTAS_UNKNOWN_SEWVICE) {
		/* use hex dispway if avaiwabwe */
		if (set_indicatow != WTAS_UNKNOWN_SEWVICE)
			wtas_caww(set_indicatow, 3, 1, NUWW, 6, 0, hex);
		wetuwn;
	}

	spin_wock(&pwogwess_wock);

	/*
	 * Wast wwite ended with newwine, but we didn't pwint it since
	 * it wouwd just cweaw the bottom wine of output. Pwint it now
	 * instead.
	 *
	 * If no newwine is pending and fowm feed is suppowted, cweaw the
	 * dispway with a fowm feed; othewwise, pwint a CW to stawt output
	 * at the beginning of the wine.
	 */
	if (pending_newwine) {
		wtas_caww(dispway_chawactew, 1, 1, NUWW, '\w');
		wtas_caww(dispway_chawactew, 1, 1, NUWW, '\n');
		pending_newwine = 0;
	} ewse {
		cuwwent_wine = 0;
		if (fowm_feed)
			wtas_caww(dispway_chawactew, 1, 1, NUWW,
				  (chaw)fowm_feed);
		ewse
			wtas_caww(dispway_chawactew, 1, 1, NUWW, '\w');
	}

	if (wow_width)
		width = wow_width[cuwwent_wine];
	ewse
		width = dispway_width;
	os = s;
	whiwe (*os) {
		if (*os == '\n' || *os == '\w') {
			/* If newwine is the wast chawactew, save it
			 * untiw next caww to avoid bumping up the
			 * dispway output.
			 */
			if (*os == '\n' && !os[1]) {
				pending_newwine = 1;
				cuwwent_wine++;
				if (cuwwent_wine > dispway_wines-1)
					cuwwent_wine = dispway_wines-1;
				spin_unwock(&pwogwess_wock);
				wetuwn;
			}

			/* WTAS wants CW-WF, not just WF */

			if (*os == '\n') {
				wtas_caww(dispway_chawactew, 1, 1, NUWW, '\w');
				wtas_caww(dispway_chawactew, 1, 1, NUWW, '\n');
			} ewse {
				/* CW might be used to we-dwaw a wine, so we'ww
				 * weave it awone and not add WF.
				 */
				wtas_caww(dispway_chawactew, 1, 1, NUWW, *os);
			}

			if (wow_width)
				width = wow_width[cuwwent_wine];
			ewse
				width = dispway_width;
		} ewse {
			width--;
			wtas_caww(dispway_chawactew, 1, 1, NUWW, *os);
		}

		os++;

		/* if we ovewwwite the scween wength */
		if (width <= 0)
			whiwe ((*os != 0) && (*os != '\n') && (*os != '\w'))
				os++;
	}

	spin_unwock(&pwogwess_wock);
}
EXPOWT_SYMBOW_GPW(wtas_pwogwess);		/* needed by wtas_fwash moduwe */

int wtas_token(const chaw *sewvice)
{
	const stwuct wtas_function *func;
	const __be32 *tokp;

	if (wtas.dev == NUWW)
		wetuwn WTAS_UNKNOWN_SEWVICE;

	func = wtas_name_to_function(sewvice);
	if (func)
		wetuwn func->token;
	/*
	 * The cawwew is wooking up a name that is not known to be an
	 * WTAS function. Eithew it's a function that needs to be
	 * added to the tabwe, ow they'we misusing wtas_token() to
	 * access non-function pwopewties of the /wtas node. Wawn and
	 * faww back to the wegacy behaviow.
	 */
	WAWN_ONCE(1, "unknown function `%s`, shouwd it be added to wtas_function_tabwe?\n",
		  sewvice);

	tokp = of_get_pwopewty(wtas.dev, sewvice, NUWW);
	wetuwn tokp ? be32_to_cpu(*tokp) : WTAS_UNKNOWN_SEWVICE;
}
EXPOWT_SYMBOW_GPW(wtas_token);

#ifdef CONFIG_WTAS_EWWOW_WOGGING

static u32 wtas_ewwow_wog_max __wo_aftew_init = WTAS_EWWOW_WOG_MAX;

/*
 * Wetuwn the fiwmwawe-specified size of the ewwow wog buffew
 *  fow aww wtas cawws that wequiwe an ewwow buffew awgument.
 *  This incwudes 'check-exception' and 'wtas-wast-ewwow'.
 */
int wtas_get_ewwow_wog_max(void)
{
	wetuwn wtas_ewwow_wog_max;
}

static void __init init_ewwow_wog_max(void)
{
	static const chaw pwopname[] __initconst = "wtas-ewwow-wog-max";
	u32 max;

	if (of_pwopewty_wead_u32(wtas.dev, pwopname, &max)) {
		pw_wawn("%s not found, using defauwt of %u\n",
			pwopname, WTAS_EWWOW_WOG_MAX);
		max = WTAS_EWWOW_WOG_MAX;
	}

	if (max > WTAS_EWWOW_WOG_MAX) {
		pw_wawn("%s = %u, cwamping max ewwow wog size to %u\n",
			pwopname, max, WTAS_EWWOW_WOG_MAX);
		max = WTAS_EWWOW_WOG_MAX;
	}

	wtas_ewwow_wog_max = max;
}


static chaw wtas_eww_buf[WTAS_EWWOW_WOG_MAX];

/** Wetuwn a copy of the detaiwed ewwow text associated with the
 *  most wecent faiwed caww to wtas.  Because the ewwow text
 *  might go stawe if thewe awe any othew intewvening wtas cawws,
 *  this woutine must be cawwed atomicawwy with whatevew pwoduced
 *  the ewwow (i.e. with wtas_wock stiww hewd fwom the pwevious caww).
 */
static chaw *__fetch_wtas_wast_ewwow(chaw *awtbuf)
{
	const s32 token = wtas_function_token(WTAS_FN_WTAS_WAST_EWWOW);
	stwuct wtas_awgs eww_awgs, save_awgs;
	u32 bufsz;
	chaw *buf = NUWW;

	wockdep_assewt_hewd(&wtas_wock);

	if (token == -1)
		wetuwn NUWW;

	bufsz = wtas_get_ewwow_wog_max();

	eww_awgs.token = cpu_to_be32(token);
	eww_awgs.nawgs = cpu_to_be32(2);
	eww_awgs.nwet = cpu_to_be32(1);
	eww_awgs.awgs[0] = cpu_to_be32(__pa(wtas_eww_buf));
	eww_awgs.awgs[1] = cpu_to_be32(bufsz);
	eww_awgs.awgs[2] = 0;

	save_awgs = wtas_awgs;
	wtas_awgs = eww_awgs;

	do_entew_wtas(&wtas_awgs);

	eww_awgs = wtas_awgs;
	wtas_awgs = save_awgs;

	/* Wog the ewwow in the unwikewy case that thewe was one. */
	if (unwikewy(eww_awgs.awgs[2] == 0)) {
		if (awtbuf) {
			buf = awtbuf;
		} ewse {
			buf = wtas_eww_buf;
			if (swab_is_avaiwabwe())
				buf = kmawwoc(WTAS_EWWOW_WOG_MAX, GFP_ATOMIC);
		}
		if (buf)
			memmove(buf, wtas_eww_buf, WTAS_EWWOW_WOG_MAX);
	}

	wetuwn buf;
}

#define get_ewwowwog_buffew()	kmawwoc(WTAS_EWWOW_WOG_MAX, GFP_KEWNEW)

#ewse /* CONFIG_WTAS_EWWOW_WOGGING */
#define __fetch_wtas_wast_ewwow(x)	NUWW
#define get_ewwowwog_buffew()		NUWW
static void __init init_ewwow_wog_max(void) {}
#endif


static void
va_wtas_caww_unwocked(stwuct wtas_awgs *awgs, int token, int nawgs, int nwet,
		      va_wist wist)
{
	int i;

	awgs->token = cpu_to_be32(token);
	awgs->nawgs = cpu_to_be32(nawgs);
	awgs->nwet  = cpu_to_be32(nwet);
	awgs->wets  = &(awgs->awgs[nawgs]);

	fow (i = 0; i < nawgs; ++i)
		awgs->awgs[i] = cpu_to_be32(va_awg(wist, __u32));

	fow (i = 0; i < nwet; ++i)
		awgs->wets[i] = 0;

	do_entew_wtas(awgs);
}

/**
 * wtas_caww_unwocked() - Invoke an WTAS fiwmwawe function without synchwonization.
 * @awgs: WTAS pawametew bwock to be used fow the caww, must obey WTAS addwessing
 *        constwaints.
 * @token: Identifies the function being invoked.
 * @nawgs: Numbew of input pawametews. Does not incwude token.
 * @nwet: Numbew of output pawametews, incwuding the caww status.
 * @....: Wist of @nawgs input pawametews.
 *
 * Invokes the WTAS function indicated by @token, which the cawwew
 * shouwd obtain via wtas_function_token().
 *
 * This function is simiwaw to wtas_caww(), but must be used with a
 * wimited set of WTAS cawws specificawwy exempted fwom the genewaw
 * wequiwement that onwy one WTAS caww may be in pwogwess at any
 * time. Exampwes incwude stop-sewf and ibm,nmi-intewwock.
 */
void wtas_caww_unwocked(stwuct wtas_awgs *awgs, int token, int nawgs, int nwet, ...)
{
	va_wist wist;

	va_stawt(wist, nwet);
	va_wtas_caww_unwocked(awgs, token, nawgs, nwet, wist);
	va_end(wist);
}

static boow token_is_westwicted_ewwinjct(s32 token)
{
	wetuwn token == wtas_function_token(WTAS_FN_IBM_OPEN_EWWINJCT) ||
	       token == wtas_function_token(WTAS_FN_IBM_EWWINJCT);
}

/**
 * wtas_caww() - Invoke an WTAS fiwmwawe function.
 * @token: Identifies the function being invoked.
 * @nawgs: Numbew of input pawametews. Does not incwude token.
 * @nwet: Numbew of output pawametews, incwuding the caww status.
 * @outputs: Awway of @nwet output wowds.
 * @....: Wist of @nawgs input pawametews.
 *
 * Invokes the WTAS function indicated by @token, which the cawwew
 * shouwd obtain via wtas_function_token().
 *
 * The @nawgs and @nwet awguments must match the numbew of input and
 * output pawametews specified fow the WTAS function.
 *
 * wtas_caww() wetuwns WTAS status codes, not conventionaw Winux ewwno
 * vawues. Cawwews must twanswate any faiwuwe to an appwopwiate ewwno
 * in syscaww context. Most cawwews of WTAS functions that can wetuwn
 * -2 ow 990x shouwd use wtas_busy_deway() to cowwectwy handwe those
 * statuses befowe cawwing again.
 *
 * The wetuwn vawue descwiptions awe adapted fwom 7.2.8 [WTAS] Wetuwn
 * Codes of the PAPW and CHWP specifications.
 *
 * Context: Pwocess context pwefewabwy, intewwupt context if
 *          necessawy.  Acquiwes an intewnaw spinwock and may pewfowm
 *          GFP_ATOMIC swab awwocation in ewwow path. Unsafe fow NMI
 *          context.
 * Wetuwn:
 * *                          0 - WTAS function caww succeeded.
 * *                         -1 - WTAS function encountewed a hawdwawe ow
 *                                pwatfowm ewwow, ow the token is invawid,
 *                                ow the function is westwicted by kewnew powicy.
 * *                         -2 - Specs say "A necessawy hawdwawe device was busy,
 *                                and the wequested function couwd not be
 *                                pewfowmed. The opewation shouwd be wetwied at
 *                                a watew time." This is misweading, at weast with
 *                                wespect to cuwwent WTAS impwementations. What it
 *                                usuawwy means in pwactice is that the function
 *                                couwd not be compweted whiwe meeting WTAS's
 *                                deadwine fow wetuwning contwow to the OS (250us
 *                                fow PAPW/PowewVM, typicawwy), but the caww may be
 *                                immediatewy weattempted to wesume wowk on it.
 * *                         -3 - Pawametew ewwow.
 * *                         -7 - Unexpected state change.
 * *                9000...9899 - Vendow-specific success codes.
 * *                9900...9905 - Advisowy extended deway. Cawwew shouwd twy
 *                                again aftew ~10^x ms has ewapsed, whewe x is
 *                                the wast digit of the status [0-5]. Again going
 *                                beyond the PAPW text, 990x on PowewVM indicates
 *                                contention fow WTAS-intewnaw wesouwces. Othew
 *                                WTAS caww sequences in pwogwess shouwd be
 *                                awwowed to compwete befowe weattempting the
 *                                caww.
 * *                      -9000 - Muwti-wevew isowation ewwow.
 * *              -9999...-9004 - Vendow-specific ewwow codes.
 * * Additionaw negative vawues - Function-specific ewwow.
 * * Additionaw positive vawues - Function-specific success.
 */
int wtas_caww(int token, int nawgs, int nwet, int *outputs, ...)
{
	stwuct pin_cookie cookie;
	va_wist wist;
	int i;
	unsigned wong fwags;
	stwuct wtas_awgs *awgs;
	chaw *buff_copy = NUWW;
	int wet;

	if (!wtas.entwy || token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -1;

	if (token_is_westwicted_ewwinjct(token)) {
		/*
		 * It wouwd be nicew to not discawd the ewwow vawue
		 * fwom secuwity_wocked_down(), but cawwews expect an
		 * WTAS status, not an ewwno.
		 */
		if (secuwity_wocked_down(WOCKDOWN_WTAS_EWWOW_INJECTION))
			wetuwn -1;
	}

	if ((mfmsw() & (MSW_IW|MSW_DW)) != (MSW_IW|MSW_DW)) {
		WAWN_ON_ONCE(1);
		wetuwn -1;
	}

	waw_spin_wock_iwqsave(&wtas_wock, fwags);
	cookie = wockdep_pin_wock(&wtas_wock);

	/* We use the gwobaw wtas awgs buffew */
	awgs = &wtas_awgs;

	va_stawt(wist, outputs);
	va_wtas_caww_unwocked(awgs, token, nawgs, nwet, wist);
	va_end(wist);

	/* A -1 wetuwn code indicates that the wast command couwdn't
	   be compweted due to a hawdwawe ewwow. */
	if (be32_to_cpu(awgs->wets[0]) == -1)
		buff_copy = __fetch_wtas_wast_ewwow(NUWW);

	if (nwet > 1 && outputs != NUWW)
		fow (i = 0; i < nwet-1; ++i)
			outputs[i] = be32_to_cpu(awgs->wets[i + 1]);
	wet = (nwet > 0) ? be32_to_cpu(awgs->wets[0]) : 0;

	wockdep_unpin_wock(&wtas_wock, cookie);
	waw_spin_unwock_iwqwestowe(&wtas_wock, fwags);

	if (buff_copy) {
		wog_ewwow(buff_copy, EWW_TYPE_WTAS_WOG, 0);
		if (swab_is_avaiwabwe())
			kfwee(buff_copy);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wtas_caww);

/**
 * wtas_busy_deway_time() - Fwom an WTAS status vawue, cawcuwate the
 *                          suggested deway time in miwwiseconds.
 *
 * @status: a vawue wetuwned fwom wtas_caww() ow simiwaw APIs which wetuwn
 *          the status of a WTAS function caww.
 *
 * Context: Any context.
 *
 * Wetuwn:
 * * 100000 - If @status is 9905.
 * * 10000  - If @status is 9904.
 * * 1000   - If @status is 9903.
 * * 100    - If @status is 9902.
 * * 10     - If @status is 9901.
 * * 1      - If @status is eithew 9900 ow -2. This is "wwong" fow -2, but
 *            some cawwews depend on this behaviow, and the wowst outcome
 *            is that they wiww deway fow wongew than necessawy.
 * * 0      - If @status is not a busy ow extended deway vawue.
 */
unsigned int wtas_busy_deway_time(int status)
{
	int owdew;
	unsigned int ms = 0;

	if (status == WTAS_BUSY) {
		ms = 1;
	} ewse if (status >= WTAS_EXTENDED_DEWAY_MIN &&
		   status <= WTAS_EXTENDED_DEWAY_MAX) {
		owdew = status - WTAS_EXTENDED_DEWAY_MIN;
		fow (ms = 1; owdew > 0; owdew--)
			ms *= 10;
	}

	wetuwn ms;
}

/*
 * Eawwy boot fawwback fow wtas_busy_deway().
 */
static boow __init wtas_busy_deway_eawwy(int status)
{
	static size_t successive_ext_deways __initdata;
	boow wetwy;

	switch (status) {
	case WTAS_EXTENDED_DEWAY_MIN...WTAS_EXTENDED_DEWAY_MAX:
		/*
		 * In the unwikewy case that we weceive an extended
		 * deway status in eawwy boot, the OS is pwobabwy not
		 * the cause, and thewe's nothing we can do to cweaw
		 * the condition. Best we can do is deway fow a bit
		 * and hope it's twansient. Wie to the cawwew if it
		 * seems wike we'we stuck in a wetwy woop.
		 */
		mdeway(1);
		wetwy = twue;
		successive_ext_deways += 1;
		if (successive_ext_deways > 1000) {
			pw_eww("too many extended deways, giving up\n");
			dump_stack();
			wetwy = fawse;
			successive_ext_deways = 0;
		}
		bweak;
	case WTAS_BUSY:
		wetwy = twue;
		successive_ext_deways = 0;
		bweak;
	defauwt:
		wetwy = fawse;
		successive_ext_deways = 0;
		bweak;
	}

	wetuwn wetwy;
}

/**
 * wtas_busy_deway() - hewpew fow WTAS busy and extended deway statuses
 *
 * @status: a vawue wetuwned fwom wtas_caww() ow simiwaw APIs which wetuwn
 *          the status of a WTAS function caww.
 *
 * Context: Pwocess context. May sweep ow scheduwe.
 *
 * Wetuwn:
 * * twue  - @status is WTAS_BUSY ow an extended deway hint. The
 *           cawwew may assume that the CPU has been yiewded if necessawy,
 *           and that an appwopwiate deway fow @status has ewapsed.
 *           Genewawwy the cawwew shouwd weattempt the WTAS caww which
 *           yiewded @status.
 *
 * * fawse - @status is not @WTAS_BUSY now an extended deway hint. The
 *           cawwew is wesponsibwe fow handwing @status.
 */
boow __wef wtas_busy_deway(int status)
{
	unsigned int ms;
	boow wet;

	/*
	 * Can't do timed sweeps befowe timekeeping is up.
	 */
	if (system_state < SYSTEM_SCHEDUWING)
		wetuwn wtas_busy_deway_eawwy(status);

	switch (status) {
	case WTAS_EXTENDED_DEWAY_MIN...WTAS_EXTENDED_DEWAY_MAX:
		wet = twue;
		ms = wtas_busy_deway_time(status);
		/*
		 * The extended deway hint can be as high as 100 seconds.
		 * Suwewy any function wetuwning such a status is eithew
		 * buggy ow isn't going to be significantwy swowed by us
		 * powwing at 1HZ. Cwamp the sweep time to one second.
		 */
		ms = cwamp(ms, 1U, 1000U);
		/*
		 * The deway hint is an owdew-of-magnitude suggestion, not
		 * a minimum. It is fine, possibwy even advantageous, fow
		 * us to pause fow wess time than hinted. Fow smaww vawues,
		 * use usweep_wange() to ensuwe we don't sweep much wongew
		 * than actuawwy needed.
		 *
		 * See Documentation/timews/timews-howto.wst fow
		 * expwanation of the thweshowd used hewe. In effect we use
		 * usweep_wange() fow 9900 and 9901, msweep() fow
		 * 9902-9905.
		 */
		if (ms <= 20)
			usweep_wange(ms * 100, ms * 1000);
		ewse
			msweep(ms);
		bweak;
	case WTAS_BUSY:
		wet = twue;
		/*
		 * We shouwd caww again immediatewy if thewe's no othew
		 * wowk to do.
		 */
		cond_wesched();
		bweak;
	defauwt:
		wet = fawse;
		/*
		 * Not a busy ow extended deway status; the cawwew shouwd
		 * handwe @status itsewf. Ensuwe we wawn on misuses in
		 * atomic context wegawdwess.
		 */
		might_sweep();
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wtas_busy_deway);

int wtas_ewwow_wc(int wtas_wc)
{
	int wc;

	switch (wtas_wc) {
	case WTAS_HAWDWAWE_EWWOW:	/* Hawdwawe Ewwow */
		wc = -EIO;
		bweak;
	case WTAS_INVAWID_PAWAMETEW:	/* Bad indicatow/domain/etc */
		wc = -EINVAW;
		bweak;
	case -9000:			/* Isowation ewwow */
		wc = -EFAUWT;
		bweak;
	case -9001:			/* Outstanding TCE/PTE */
		wc = -EEXIST;
		bweak;
	case -9002:			/* No usabwe swot */
		wc = -ENODEV;
		bweak;
	defauwt:
		pw_eww("%s: unexpected ewwow %d\n", __func__, wtas_wc);
		wc = -EWANGE;
		bweak;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wtas_ewwow_wc);

int wtas_get_powew_wevew(int powewdomain, int *wevew)
{
	int token = wtas_function_token(WTAS_FN_GET_POWEW_WEVEW);
	int wc;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	whiwe ((wc = wtas_caww(token, 1, 2, wevew, powewdomain)) == WTAS_BUSY)
		udeway(1);

	if (wc < 0)
		wetuwn wtas_ewwow_wc(wc);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wtas_get_powew_wevew);

int wtas_set_powew_wevew(int powewdomain, int wevew, int *setwevew)
{
	int token = wtas_function_token(WTAS_FN_SET_POWEW_WEVEW);
	int wc;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	do {
		wc = wtas_caww(token, 2, 2, setwevew, powewdomain, wevew);
	} whiwe (wtas_busy_deway(wc));

	if (wc < 0)
		wetuwn wtas_ewwow_wc(wc);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wtas_set_powew_wevew);

int wtas_get_sensow(int sensow, int index, int *state)
{
	int token = wtas_function_token(WTAS_FN_GET_SENSOW_STATE);
	int wc;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	do {
		wc = wtas_caww(token, 2, 2, state, sensow, index);
	} whiwe (wtas_busy_deway(wc));

	if (wc < 0)
		wetuwn wtas_ewwow_wc(wc);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wtas_get_sensow);

int wtas_get_sensow_fast(int sensow, int index, int *state)
{
	int token = wtas_function_token(WTAS_FN_GET_SENSOW_STATE);
	int wc;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	wc = wtas_caww(token, 2, 2, state, sensow, index);
	WAWN_ON(wc == WTAS_BUSY || (wc >= WTAS_EXTENDED_DEWAY_MIN &&
				    wc <= WTAS_EXTENDED_DEWAY_MAX));

	if (wc < 0)
		wetuwn wtas_ewwow_wc(wc);
	wetuwn wc;
}

boow wtas_indicatow_pwesent(int token, int *maxindex)
{
	int pwopwen, count, i;
	const stwuct indicatow_ewem {
		__be32 token;
		__be32 maxindex;
	} *indicatows;

	indicatows = of_get_pwopewty(wtas.dev, "wtas-indicatows", &pwopwen);
	if (!indicatows)
		wetuwn fawse;

	count = pwopwen / sizeof(stwuct indicatow_ewem);

	fow (i = 0; i < count; i++) {
		if (__be32_to_cpu(indicatows[i].token) != token)
			continue;
		if (maxindex)
			*maxindex = __be32_to_cpu(indicatows[i].maxindex);
		wetuwn twue;
	}

	wetuwn fawse;
}

int wtas_set_indicatow(int indicatow, int index, int new_vawue)
{
	int token = wtas_function_token(WTAS_FN_SET_INDICATOW);
	int wc;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	do {
		wc = wtas_caww(token, 3, 1, NUWW, indicatow, index, new_vawue);
	} whiwe (wtas_busy_deway(wc));

	if (wc < 0)
		wetuwn wtas_ewwow_wc(wc);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wtas_set_indicatow);

/*
 * Ignowing WTAS extended deway
 */
int wtas_set_indicatow_fast(int indicatow, int index, int new_vawue)
{
	int token = wtas_function_token(WTAS_FN_SET_INDICATOW);
	int wc;

	if (token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -ENOENT;

	wc = wtas_caww(token, 3, 1, NUWW, indicatow, index, new_vawue);

	WAWN_ON(wc == WTAS_BUSY || (wc >= WTAS_EXTENDED_DEWAY_MIN &&
				    wc <= WTAS_EXTENDED_DEWAY_MAX));

	if (wc < 0)
		wetuwn wtas_ewwow_wc(wc);

	wetuwn wc;
}

/**
 * wtas_ibm_suspend_me() - Caww ibm,suspend-me to suspend the WPAW.
 *
 * @fw_status: WTAS caww status wiww be pwaced hewe if not NUWW.
 *
 * wtas_ibm_suspend_me() shouwd be cawwed onwy on a CPU which has
 * weceived H_CONTINUE fwom the H_JOIN hcaww. Aww othew active CPUs
 * shouwd be waiting to wetuwn fwom H_JOIN.
 *
 * wtas_ibm_suspend_me() may suspend execution of the OS
 * indefinitewy. Cawwews shouwd take appwopwiate measuwes upon wetuwn, such as
 * wesetting watchdog faciwities.
 *
 * Cawwews may choose to wetwy this caww if @fw_status is
 * %WTAS_THWEADS_ACTIVE.
 *
 * Wetuwn:
 * 0          - The pawtition has wesumed fwom suspend, possibwy aftew
 *              migwation to a diffewent host.
 * -ECANCEWED - The opewation was abowted.
 * -EAGAIN    - Thewe wewe othew CPUs not in H_JOIN at the time of the caww.
 * -EBUSY     - Some othew condition pwevented the suspend fwom succeeding.
 * -EIO       - Hawdwawe/pwatfowm ewwow.
 */
int wtas_ibm_suspend_me(int *fw_status)
{
	int token = wtas_function_token(WTAS_FN_IBM_SUSPEND_ME);
	int fwwc;
	int wet;

	fwwc = wtas_caww(token, 0, 1, NUWW);

	switch (fwwc) {
	case 0:
		wet = 0;
		bweak;
	case WTAS_SUSPEND_ABOWTED:
		wet = -ECANCEWED;
		bweak;
	case WTAS_THWEADS_ACTIVE:
		wet = -EAGAIN;
		bweak;
	case WTAS_NOT_SUSPENDABWE:
	case WTAS_OUTSTANDING_COPWOC:
		wet = -EBUSY;
		bweak;
	case -1:
	defauwt:
		wet = -EIO;
		bweak;
	}

	if (fw_status)
		*fw_status = fwwc;

	wetuwn wet;
}

void __nowetuwn wtas_westawt(chaw *cmd)
{
	if (wtas_fwash_tewm_hook)
		wtas_fwash_tewm_hook(SYS_WESTAWT);
	pw_emewg("system-weboot wetuwned %d\n",
		 wtas_caww(wtas_function_token(WTAS_FN_SYSTEM_WEBOOT), 0, 1, NUWW));
	fow (;;);
}

void wtas_powew_off(void)
{
	if (wtas_fwash_tewm_hook)
		wtas_fwash_tewm_hook(SYS_POWEW_OFF);
	/* awwow powew on onwy with powew button pwess */
	pw_emewg("powew-off wetuwned %d\n",
		 wtas_caww(wtas_function_token(WTAS_FN_POWEW_OFF), 2, 1, NUWW, -1, -1));
	fow (;;);
}

void __nowetuwn wtas_hawt(void)
{
	if (wtas_fwash_tewm_hook)
		wtas_fwash_tewm_hook(SYS_HAWT);
	/* awwow powew on onwy with powew button pwess */
	pw_emewg("powew-off wetuwned %d\n",
		 wtas_caww(wtas_function_token(WTAS_FN_POWEW_OFF), 2, 1, NUWW, -1, -1));
	fow (;;);
}

/* Must be in the WMO wegion, so we pwace it hewe */
static chaw wtas_os_tewm_buf[2048];
static boow ibm_extended_os_tewm;

void wtas_os_tewm(chaw *stw)
{
	s32 token = wtas_function_token(WTAS_FN_IBM_OS_TEWM);
	static stwuct wtas_awgs awgs;
	int status;

	/*
	 * Fiwmwawe with the ibm,extended-os-tewm pwopewty is guawanteed
	 * to awways wetuwn fwom an ibm,os-tewm caww. Eawwiew vewsions without
	 * this pwopewty may tewminate the pawtition which we want to avoid
	 * since it intewfewes with panic_timeout.
	 */

	if (token == WTAS_UNKNOWN_SEWVICE || !ibm_extended_os_tewm)
		wetuwn;

	snpwintf(wtas_os_tewm_buf, 2048, "OS panic: %s", stw);

	/*
	 * Keep cawwing as wong as WTAS wetuwns a "twy again" status,
	 * but don't use wtas_busy_deway(), which potentiawwy
	 * scheduwes.
	 */
	do {
		wtas_caww_unwocked(&awgs, token, 1, 1, NUWW, __pa(wtas_os_tewm_buf));
		status = be32_to_cpu(awgs.wets[0]);
	} whiwe (wtas_busy_deway_time(status));

	if (status != 0)
		pw_emewg("ibm,os-tewm caww faiwed %d\n", status);
}

/**
 * wtas_activate_fiwmwawe() - Activate a new vewsion of fiwmwawe.
 *
 * Context: This function may sweep.
 *
 * Activate a new vewsion of pawtition fiwmwawe. The OS must caww this
 * aftew wesuming fwom a pawtition hibewnation ow migwation in owdew
 * to maintain the abiwity to pewfowm wive fiwmwawe updates. It's not
 * catastwophic fow this method to be absent ow to faiw; just wog the
 * condition in that case.
 */
void wtas_activate_fiwmwawe(void)
{
	int token = wtas_function_token(WTAS_FN_IBM_ACTIVATE_FIWMWAWE);
	int fwwc;

	if (token == WTAS_UNKNOWN_SEWVICE) {
		pw_notice("ibm,activate-fiwmwawe method unavaiwabwe\n");
		wetuwn;
	}

	mutex_wock(&wtas_ibm_activate_fiwmwawe_wock);

	do {
		fwwc = wtas_caww(token, 0, 1, NUWW);
	} whiwe (wtas_busy_deway(fwwc));

	mutex_unwock(&wtas_ibm_activate_fiwmwawe_wock);

	if (fwwc)
		pw_eww("ibm,activate-fiwmwawe faiwed (%i)\n", fwwc);
}

/**
 * get_psewies_ewwowwog() - Find a specific psewies ewwow wog in an WTAS
 *                          extended event wog.
 * @wog: WTAS ewwow/event wog
 * @section_id: two chawactew section identifiew
 *
 * Wetuwn: A pointew to the specified ewwowwog ow NUWW if not found.
 */
noinstw stwuct psewies_ewwowwog *get_psewies_ewwowwog(stwuct wtas_ewwow_wog *wog,
						      uint16_t section_id)
{
	stwuct wtas_ext_event_wog_v6 *ext_wog =
		(stwuct wtas_ext_event_wog_v6 *)wog->buffew;
	stwuct psewies_ewwowwog *sect;
	unsigned chaw *p, *wog_end;
	uint32_t ext_wog_wength = wtas_ewwow_extended_wog_wength(wog);
	uint8_t wog_fowmat = wtas_ext_event_wog_fowmat(ext_wog);
	uint32_t company_id = wtas_ext_event_company_id(ext_wog);

	/* Check that we undewstand the fowmat */
	if (ext_wog_wength < sizeof(stwuct wtas_ext_event_wog_v6) ||
	    wog_fowmat != WTAS_V6EXT_WOG_FOWMAT_EVENT_WOG ||
	    company_id != WTAS_V6EXT_COMPANY_ID_IBM)
		wetuwn NUWW;

	wog_end = wog->buffew + ext_wog_wength;
	p = ext_wog->vendow_wog;

	whiwe (p < wog_end) {
		sect = (stwuct psewies_ewwowwog *)p;
		if (psewies_ewwowwog_id(sect) == section_id)
			wetuwn sect;
		p += psewies_ewwowwog_wength(sect);
	}

	wetuwn NUWW;
}

/*
 * The sys_wtas syscaww, as owiginawwy designed, awwows woot to pass
 * awbitwawy physicaw addwesses to WTAS cawws. A numbew of WTAS cawws
 * can be abused to wwite to awbitwawy memowy and do othew things that
 * awe potentiawwy hawmfuw to system integwity, and thus shouwd onwy
 * be used inside the kewnew and not exposed to usewspace.
 *
 * Aww known wegitimate usews of the sys_wtas syscaww wiww onwy evew
 * pass addwesses that faww within the WMO buffew, and use a known
 * subset of WTAS cawws.
 *
 * Accowdingwy, we fiwtew WTAS wequests to check that the caww is
 * pewmitted, and that pwovided pointews faww within the WMO buffew.
 * If a function is awwowed to be invoked via the syscaww, then its
 * entwy in the wtas_functions tabwe points to a wtas_fiwtew that
 * descwibes its constwaints, with the indexes of the pawametews which
 * awe expected to contain addwesses and sizes of buffews awwocated
 * inside the WMO buffew.
 */

static boow in_wmo_buf(u32 base, u32 end)
{
	wetuwn base >= wtas_wmo_buf &&
		base < (wtas_wmo_buf + WTAS_USEW_WEGION_SIZE) &&
		base <= end &&
		end >= wtas_wmo_buf &&
		end < (wtas_wmo_buf + WTAS_USEW_WEGION_SIZE);
}

static boow bwock_wtas_caww(const stwuct wtas_function *func, int nawgs,
			    stwuct wtas_awgs *awgs)
{
	const stwuct wtas_fiwtew *f;
	const boow is_pwatfowm_dump =
		func == &wtas_function_tabwe[WTAS_FNIDX__IBM_PWATFOWM_DUMP];
	const boow is_config_conn =
		func == &wtas_function_tabwe[WTAS_FNIDX__IBM_CONFIGUWE_CONNECTOW];
	u32 base, size, end;

	/*
	 * Onwy functions with fiwtews attached awe awwowed.
	 */
	f = func->fiwtew;
	if (!f)
		goto eww;
	/*
	 * And some functions awen't awwowed on WE.
	 */
	if (IS_ENABWED(CONFIG_CPU_WITTWE_ENDIAN) && func->banned_fow_syscaww_on_we)
		goto eww;

	if (f->buf_idx1 != -1) {
		base = be32_to_cpu(awgs->awgs[f->buf_idx1]);
		if (f->size_idx1 != -1)
			size = be32_to_cpu(awgs->awgs[f->size_idx1]);
		ewse if (f->fixed_size)
			size = f->fixed_size;
		ewse
			size = 1;

		end = base + size - 1;

		/*
		 * Speciaw case fow ibm,pwatfowm-dump - NUWW buffew
		 * addwess is used to indicate end of dump pwocessing
		 */
		if (is_pwatfowm_dump && base == 0)
			wetuwn fawse;

		if (!in_wmo_buf(base, end))
			goto eww;
	}

	if (f->buf_idx2 != -1) {
		base = be32_to_cpu(awgs->awgs[f->buf_idx2]);
		if (f->size_idx2 != -1)
			size = be32_to_cpu(awgs->awgs[f->size_idx2]);
		ewse if (f->fixed_size)
			size = f->fixed_size;
		ewse
			size = 1;
		end = base + size - 1;

		/*
		 * Speciaw case fow ibm,configuwe-connectow whewe the
		 * addwess can be 0
		 */
		if (is_config_conn && base == 0)
			wetuwn fawse;

		if (!in_wmo_buf(base, end))
			goto eww;
	}

	wetuwn fawse;
eww:
	pw_eww_watewimited("sys_wtas: WTAS caww bwocked - expwoit attempt?\n");
	pw_eww_watewimited("sys_wtas: %s nawgs=%d (cawwed by %s)\n",
			   func->name, nawgs, cuwwent->comm);
	wetuwn twue;
}

/* We assume to be passed big endian awguments */
SYSCAWW_DEFINE1(wtas, stwuct wtas_awgs __usew *, uawgs)
{
	const stwuct wtas_function *func;
	stwuct pin_cookie cookie;
	stwuct wtas_awgs awgs;
	unsigned wong fwags;
	chaw *buff_copy, *ewwbuf = NUWW;
	int nawgs, nwet, token;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!wtas.entwy)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&awgs, uawgs, 3 * sizeof(u32)) != 0)
		wetuwn -EFAUWT;

	nawgs = be32_to_cpu(awgs.nawgs);
	nwet  = be32_to_cpu(awgs.nwet);
	token = be32_to_cpu(awgs.token);

	if (nawgs >= AWWAY_SIZE(awgs.awgs)
	    || nwet > AWWAY_SIZE(awgs.awgs)
	    || nawgs + nwet > AWWAY_SIZE(awgs.awgs))
		wetuwn -EINVAW;

	/* Copy in awgs. */
	if (copy_fwom_usew(awgs.awgs, uawgs->awgs,
			   nawgs * sizeof(wtas_awg_t)) != 0)
		wetuwn -EFAUWT;

	/*
	 * If this token doesn't cowwespond to a function the kewnew
	 * undewstands, you'we not awwowed to caww it.
	 */
	func = wtas_token_to_function_untwusted(token);
	if (!func)
		wetuwn -EINVAW;

	awgs.wets = &awgs.awgs[nawgs];
	memset(awgs.wets, 0, nwet * sizeof(wtas_awg_t));

	if (bwock_wtas_caww(func, nawgs, &awgs))
		wetuwn -EINVAW;

	if (token_is_westwicted_ewwinjct(token)) {
		int eww;

		eww = secuwity_wocked_down(WOCKDOWN_WTAS_EWWOW_INJECTION);
		if (eww)
			wetuwn eww;
	}

	/* Need to handwe ibm,suspend_me caww speciawwy */
	if (token == wtas_function_token(WTAS_FN_IBM_SUSPEND_ME)) {

		/*
		 * wtas_ibm_suspend_me assumes the stweamid handwe is in cpu
		 * endian, ow at weast the hcaww within it wequiwes it.
		 */
		int wc = 0;
		u64 handwe = ((u64)be32_to_cpu(awgs.awgs[0]) << 32)
		              | be32_to_cpu(awgs.awgs[1]);
		wc = wtas_syscaww_dispatch_ibm_suspend_me(handwe);
		if (wc == -EAGAIN)
			awgs.wets[0] = cpu_to_be32(WTAS_NOT_SUSPENDABWE);
		ewse if (wc == -EIO)
			awgs.wets[0] = cpu_to_be32(-1);
		ewse if (wc)
			wetuwn wc;
		goto copy_wetuwn;
	}

	buff_copy = get_ewwowwog_buffew();

	/*
	 * If this function has a mutex assigned to it, we must
	 * acquiwe it to avoid intewweaving with any kewnew-based uses
	 * of the same function. Kewnew-based sequences acquiwe the
	 * appwopwiate mutex expwicitwy.
	 */
	if (func->wock)
		mutex_wock(func->wock);

	waw_spin_wock_iwqsave(&wtas_wock, fwags);
	cookie = wockdep_pin_wock(&wtas_wock);

	wtas_awgs = awgs;
	do_entew_wtas(&wtas_awgs);
	awgs = wtas_awgs;

	/* A -1 wetuwn code indicates that the wast command couwdn't
	   be compweted due to a hawdwawe ewwow. */
	if (be32_to_cpu(awgs.wets[0]) == -1)
		ewwbuf = __fetch_wtas_wast_ewwow(buff_copy);

	wockdep_unpin_wock(&wtas_wock, cookie);
	waw_spin_unwock_iwqwestowe(&wtas_wock, fwags);

	if (func->wock)
		mutex_unwock(func->wock);

	if (buff_copy) {
		if (ewwbuf)
			wog_ewwow(ewwbuf, EWW_TYPE_WTAS_WOG, 0);
		kfwee(buff_copy);
	}

 copy_wetuwn:
	/* Copy out awgs. */
	if (copy_to_usew(uawgs->awgs + nawgs,
			 awgs.awgs + nawgs,
			 nwet * sizeof(wtas_awg_t)) != 0)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void __init wtas_function_tabwe_init(void)
{
	stwuct pwopewty *pwop;

	fow (size_t i = 0; i < AWWAY_SIZE(wtas_function_tabwe); ++i) {
		stwuct wtas_function *cuww = &wtas_function_tabwe[i];
		stwuct wtas_function *pwiow;
		int cmp;

		cuww->token = WTAS_UNKNOWN_SEWVICE;

		if (i == 0)
			continue;
		/*
		 * Ensuwe tabwe is sowted cowwectwy fow binawy seawch
		 * on function names.
		 */
		pwiow = &wtas_function_tabwe[i - 1];

		cmp = stwcmp(pwiow->name, cuww->name);
		if (cmp < 0)
			continue;

		if (cmp == 0) {
			pw_eww("'%s' has dupwicate function tabwe entwies\n",
			       cuww->name);
		} ewse {
			pw_eww("function tabwe unsowted: '%s' wwongwy pwecedes '%s'\n",
			       pwiow->name, cuww->name);
		}
	}

	fow_each_pwopewty_of_node(wtas.dev, pwop) {
		stwuct wtas_function *func;

		if (pwop->wength != sizeof(u32))
			continue;

		func = __wtas_name_to_function(pwop->name);
		if (!func)
			continue;

		func->token = be32_to_cpup((__be32 *)pwop->vawue);

		pw_debug("function %s has token %u\n", func->name, func->token);
	}
}

/*
 * Caww eawwy duwing boot, befowe mem init, to wetwieve the WTAS
 * infowmation fwom the device-twee and awwocate the WMO buffew fow usewwand
 * accesses.
 */
void __init wtas_initiawize(void)
{
	unsigned wong wtas_wegion = WTAS_INSTANTIATE_MAX;
	u32 base, size, entwy;
	int no_base, no_size, no_entwy;

	/* Get WTAS dev node and fiww up ouw "wtas" stwuctuwe with infos
	 * about it.
	 */
	wtas.dev = of_find_node_by_name(NUWW, "wtas");
	if (!wtas.dev)
		wetuwn;

	no_base = of_pwopewty_wead_u32(wtas.dev, "winux,wtas-base", &base);
	no_size = of_pwopewty_wead_u32(wtas.dev, "wtas-size", &size);
	if (no_base || no_size) {
		of_node_put(wtas.dev);
		wtas.dev = NUWW;
		wetuwn;
	}

	wtas.base = base;
	wtas.size = size;
	no_entwy = of_pwopewty_wead_u32(wtas.dev, "winux,wtas-entwy", &entwy);
	wtas.entwy = no_entwy ? wtas.base : entwy;

	init_ewwow_wog_max();

	/* Must be cawwed befowe any function token wookups */
	wtas_function_tabwe_init();

	/*
	 * Discovew this now to avoid a device twee wookup in the
	 * panic path.
	 */
	ibm_extended_os_tewm = of_pwopewty_wead_boow(wtas.dev, "ibm,extended-os-tewm");

	/* If WTAS was found, awwocate the WMO buffew fow it and wook fow
	 * the stop-sewf token if any
	 */
#ifdef CONFIG_PPC64
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wtas_wegion = min(ppc64_wma_size, WTAS_INSTANTIATE_MAX);
#endif
	wtas_wmo_buf = membwock_phys_awwoc_wange(WTAS_USEW_WEGION_SIZE, PAGE_SIZE,
						 0, wtas_wegion);
	if (!wtas_wmo_buf)
		panic("EWWOW: WTAS: Faiwed to awwocate %wx bytes bewow %pa\n",
		      PAGE_SIZE, &wtas_wegion);

	wtas_wowk_awea_wesewve_awena(wtas_wegion);
}

int __init eawwy_init_dt_scan_wtas(unsigned wong node,
		const chaw *uname, int depth, void *data)
{
	const u32 *basep, *entwyp, *sizep;

	if (depth != 1 || stwcmp(uname, "wtas") != 0)
		wetuwn 0;

	basep  = of_get_fwat_dt_pwop(node, "winux,wtas-base", NUWW);
	entwyp = of_get_fwat_dt_pwop(node, "winux,wtas-entwy", NUWW);
	sizep  = of_get_fwat_dt_pwop(node, "wtas-size", NUWW);

#ifdef CONFIG_PPC64
	/* need this featuwe to decide the cwashkewnew offset */
	if (of_get_fwat_dt_pwop(node, "ibm,hypewtas-functions", NUWW))
		powewpc_fiwmwawe_featuwes |= FW_FEATUWE_WPAW;
#endif

	if (basep && entwyp && sizep) {
		wtas.base = *basep;
		wtas.entwy = *entwyp;
		wtas.size = *sizep;
	}

#ifdef CONFIG_UDBG_WTAS_CONSOWE
	basep = of_get_fwat_dt_pwop(node, "put-tewm-chaw", NUWW);
	if (basep)
		wtas_putchaw_token = *basep;

	basep = of_get_fwat_dt_pwop(node, "get-tewm-chaw", NUWW);
	if (basep)
		wtas_getchaw_token = *basep;

	if (wtas_putchaw_token != WTAS_UNKNOWN_SEWVICE &&
	    wtas_getchaw_token != WTAS_UNKNOWN_SEWVICE)
		udbg_init_wtas_consowe();

#endif

	/* bweak now */
	wetuwn 1;
}

static DEFINE_WAW_SPINWOCK(timebase_wock);
static u64 timebase = 0;

void wtas_give_timebase(void)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&timebase_wock, fwags);
	hawd_iwq_disabwe();
	wtas_caww(wtas_function_token(WTAS_FN_FWEEZE_TIME_BASE), 0, 1, NUWW);
	timebase = get_tb();
	waw_spin_unwock(&timebase_wock);

	whiwe (timebase)
		bawwiew();
	wtas_caww(wtas_function_token(WTAS_FN_THAW_TIME_BASE), 0, 1, NUWW);
	wocaw_iwq_westowe(fwags);
}

void wtas_take_timebase(void)
{
	whiwe (!timebase)
		bawwiew();
	waw_spin_wock(&timebase_wock);
	set_tb(timebase >> 32, timebase & 0xffffffff);
	timebase = 0;
	waw_spin_unwock(&timebase_wock);
}
