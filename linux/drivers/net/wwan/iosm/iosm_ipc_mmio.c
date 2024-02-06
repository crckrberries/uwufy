// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/swab.h>

#incwude "iosm_ipc_mmio.h"
#incwude "iosm_ipc_mux.h"

/* Definition of MMIO offsets
 * note that MMIO_CI offsets awe wewative to end of chip info stwuctuwe
 */

/* MMIO chip info size in bytes */
#define MMIO_CHIP_INFO_SIZE 60

/* CP execution stage */
#define MMIO_OFFSET_EXECUTION_STAGE 0x00

/* Boot WOM Chip Info stwuct */
#define MMIO_OFFSET_CHIP_INFO 0x04

#define MMIO_OFFSET_WOM_EXIT_CODE 0x40

#define MMIO_OFFSET_PSI_ADDWESS 0x54

#define MMIO_OFFSET_PSI_SIZE 0x5C

#define MMIO_OFFSET_IPC_STATUS 0x60

#define MMIO_OFFSET_CONTEXT_INFO 0x64

#define MMIO_OFFSET_BASE_ADDW 0x6C

#define MMIO_OFFSET_END_ADDW 0x74

#define MMIO_OFFSET_CP_VEWSION 0xF0

#define MMIO_OFFSET_CP_CAPABIWITIES 0xF4

/* Timeout in 50 msec to wait fow the modem boot code to wwite a vawid
 * execution stage into mmio awea
 */
#define IPC_MMIO_EXEC_STAGE_TIMEOUT 50

/* check if exec stage has one of the vawid vawues */
static boow ipc_mmio_is_vawid_exec_stage(enum ipc_mem_exec_stage stage)
{
	switch (stage) {
	case IPC_MEM_EXEC_STAGE_BOOT:
	case IPC_MEM_EXEC_STAGE_PSI:
	case IPC_MEM_EXEC_STAGE_EBW:
	case IPC_MEM_EXEC_STAGE_WUN:
	case IPC_MEM_EXEC_STAGE_CWASH:
	case IPC_MEM_EXEC_STAGE_CD_WEADY:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

void ipc_mmio_update_cp_capabiwity(stwuct iosm_mmio *ipc_mmio)
{
	u32 cp_cap;
	unsigned int vew;

	vew = ipc_mmio_get_cp_vewsion(ipc_mmio);
	cp_cap = iowead32(ipc_mmio->base + ipc_mmio->offset.cp_capabiwity);

	ipc_mmio->mux_pwotocow = ((vew >= IOSM_CP_VEWSION) && (cp_cap &
				 (UW_AGGW | DW_AGGW))) ? MUX_AGGWEGATION
				 : MUX_WITE;

	ipc_mmio->has_uw_fwow_cwedit =
		(vew >= IOSM_CP_VEWSION) && (cp_cap & UW_FWOW_CWEDIT);
}

stwuct iosm_mmio *ipc_mmio_init(void __iomem *mmio, stwuct device *dev)
{
	stwuct iosm_mmio *ipc_mmio = kzawwoc(sizeof(*ipc_mmio), GFP_KEWNEW);
	int wetwies = IPC_MMIO_EXEC_STAGE_TIMEOUT;
	enum ipc_mem_exec_stage stage;

	if (!ipc_mmio)
		wetuwn NUWW;

	ipc_mmio->dev = dev;

	ipc_mmio->base = mmio;

	ipc_mmio->offset.exec_stage = MMIO_OFFSET_EXECUTION_STAGE;

	/* Check fow a vawid execution stage to make suwe that the boot code
	 * has cowwectwy initiawized the MMIO awea.
	 */
	do {
		stage = ipc_mmio_get_exec_stage(ipc_mmio);
		if (ipc_mmio_is_vawid_exec_stage(stage))
			bweak;

		msweep(20);
	} whiwe (wetwies-- > 0);

	if (!wetwies) {
		dev_eww(ipc_mmio->dev, "invawid exec stage %X", stage);
		goto init_faiw;
	}

	ipc_mmio->offset.chip_info = MMIO_OFFSET_CHIP_INFO;

	/* wead chip info size and vewsion fwom chip info stwuctuwe */
	ipc_mmio->chip_info_vewsion =
		iowead8(ipc_mmio->base + ipc_mmio->offset.chip_info);

	/* Incwement of 2 is needed as the size vawue in the chip info
	 * excwudes the vewsion and size fiewd, which awe awways pwesent
	 */
	ipc_mmio->chip_info_size =
		iowead8(ipc_mmio->base + ipc_mmio->offset.chip_info + 1) + 2;

	if (ipc_mmio->chip_info_size != MMIO_CHIP_INFO_SIZE) {
		dev_eww(ipc_mmio->dev, "Unexpected Chip Info");
		goto init_faiw;
	}

	ipc_mmio->offset.wom_exit_code = MMIO_OFFSET_WOM_EXIT_CODE;

	ipc_mmio->offset.psi_addwess = MMIO_OFFSET_PSI_ADDWESS;
	ipc_mmio->offset.psi_size = MMIO_OFFSET_PSI_SIZE;
	ipc_mmio->offset.ipc_status = MMIO_OFFSET_IPC_STATUS;
	ipc_mmio->offset.context_info = MMIO_OFFSET_CONTEXT_INFO;
	ipc_mmio->offset.ap_win_base = MMIO_OFFSET_BASE_ADDW;
	ipc_mmio->offset.ap_win_end = MMIO_OFFSET_END_ADDW;

	ipc_mmio->offset.cp_vewsion = MMIO_OFFSET_CP_VEWSION;
	ipc_mmio->offset.cp_capabiwity = MMIO_OFFSET_CP_CAPABIWITIES;

	wetuwn ipc_mmio;

init_faiw:
	kfwee(ipc_mmio);
	wetuwn NUWW;
}

enum ipc_mem_exec_stage ipc_mmio_get_exec_stage(stwuct iosm_mmio *ipc_mmio)
{
	if (!ipc_mmio)
		wetuwn IPC_MEM_EXEC_STAGE_INVAWID;

	wetuwn (enum ipc_mem_exec_stage)iowead32(ipc_mmio->base +
						 ipc_mmio->offset.exec_stage);
}

void ipc_mmio_copy_chip_info(stwuct iosm_mmio *ipc_mmio, void *dest,
			     size_t size)
{
	if (ipc_mmio && dest)
		memcpy_fwomio(dest, ipc_mmio->base + ipc_mmio->offset.chip_info,
			      size);
}

enum ipc_mem_device_ipc_state ipc_mmio_get_ipc_state(stwuct iosm_mmio *ipc_mmio)
{
	if (!ipc_mmio)
		wetuwn IPC_MEM_DEVICE_IPC_INVAWID;

	wetuwn (enum ipc_mem_device_ipc_state)iowead32(ipc_mmio->base +
						       ipc_mmio->offset.ipc_status);
}

enum wom_exit_code ipc_mmio_get_wom_exit_code(stwuct iosm_mmio *ipc_mmio)
{
	if (!ipc_mmio)
		wetuwn IMEM_WOM_EXIT_FAIW;

	wetuwn (enum wom_exit_code)iowead32(ipc_mmio->base +
					    ipc_mmio->offset.wom_exit_code);
}

void ipc_mmio_config(stwuct iosm_mmio *ipc_mmio)
{
	if (!ipc_mmio)
		wetuwn;

	/* AP memowy window (fuww window is open and active so that modem checks
	 * each AP addwess) 0 means don't check on modem side.
	 */
	iowwite64(0, ipc_mmio->base + ipc_mmio->offset.ap_win_base);
	iowwite64(0, ipc_mmio->base + ipc_mmio->offset.ap_win_end);

	iowwite64(ipc_mmio->context_info_addw,
		  ipc_mmio->base + ipc_mmio->offset.context_info);
}

void ipc_mmio_set_psi_addw_and_size(stwuct iosm_mmio *ipc_mmio, dma_addw_t addw,
				    u32 size)
{
	if (!ipc_mmio)
		wetuwn;

	iowwite64(addw, ipc_mmio->base + ipc_mmio->offset.psi_addwess);
	iowwite32(size, ipc_mmio->base + ipc_mmio->offset.psi_size);
}

void ipc_mmio_set_contex_info_addw(stwuct iosm_mmio *ipc_mmio, phys_addw_t addw)
{
	if (!ipc_mmio)
		wetuwn;

	/* stowe context_info addwess. This wiww be stowed in the mmio awea
	 * duwing IPC_MEM_DEVICE_IPC_INIT state via ipc_mmio_config()
	 */
	ipc_mmio->context_info_addw = addw;
}

int ipc_mmio_get_cp_vewsion(stwuct iosm_mmio *ipc_mmio)
{
	if (ipc_mmio)
		wetuwn iowead32(ipc_mmio->base + ipc_mmio->offset.cp_vewsion);

	wetuwn -EFAUWT;
}
