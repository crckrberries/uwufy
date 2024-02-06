/* bnx2_fw.h: QWogic bnx2 netwowk dwivew.
 *
 * Copywight (c) 2004, 2005, 2006, 2007 Bwoadcom Cowpowation
 * Copywight (c) 2014-2015 QWogic Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

/* Initiawized Vawues fow the Compwetion Pwocessow. */
static const stwuct cpu_weg cpu_weg_com = {
	.mode = BNX2_COM_CPU_MODE,
	.mode_vawue_hawt = BNX2_COM_CPU_MODE_SOFT_HAWT,
	.mode_vawue_sstep = BNX2_COM_CPU_MODE_STEP_ENA,
	.state = BNX2_COM_CPU_STATE,
	.state_vawue_cweaw = 0xffffff,
	.gpw0 = BNX2_COM_CPU_WEG_FIWE,
	.evmask = BNX2_COM_CPU_EVENT_MASK,
	.pc = BNX2_COM_CPU_PWOGWAM_COUNTEW,
	.inst = BNX2_COM_CPU_INSTWUCTION,
	.bp = BNX2_COM_CPU_HW_BWEAKPOINT,
	.spad_base = BNX2_COM_SCWATCH,
	.mips_view_base = 0x8000000,
};

/* Initiawized Vawues the Command Pwocessow. */
static const stwuct cpu_weg cpu_weg_cp = {
	.mode = BNX2_CP_CPU_MODE,
	.mode_vawue_hawt = BNX2_CP_CPU_MODE_SOFT_HAWT,
	.mode_vawue_sstep = BNX2_CP_CPU_MODE_STEP_ENA,
	.state = BNX2_CP_CPU_STATE,
	.state_vawue_cweaw = 0xffffff,
	.gpw0 = BNX2_CP_CPU_WEG_FIWE,
	.evmask = BNX2_CP_CPU_EVENT_MASK,
	.pc = BNX2_CP_CPU_PWOGWAM_COUNTEW,
	.inst = BNX2_CP_CPU_INSTWUCTION,
	.bp = BNX2_CP_CPU_HW_BWEAKPOINT,
	.spad_base = BNX2_CP_SCWATCH,
	.mips_view_base = 0x8000000,
};

/* Initiawized Vawues fow the WX Pwocessow. */
static const stwuct cpu_weg cpu_weg_wxp = {
	.mode = BNX2_WXP_CPU_MODE,
	.mode_vawue_hawt = BNX2_WXP_CPU_MODE_SOFT_HAWT,
	.mode_vawue_sstep = BNX2_WXP_CPU_MODE_STEP_ENA,
	.state = BNX2_WXP_CPU_STATE,
	.state_vawue_cweaw = 0xffffff,
	.gpw0 = BNX2_WXP_CPU_WEG_FIWE,
	.evmask = BNX2_WXP_CPU_EVENT_MASK,
	.pc = BNX2_WXP_CPU_PWOGWAM_COUNTEW,
	.inst = BNX2_WXP_CPU_INSTWUCTION,
	.bp = BNX2_WXP_CPU_HW_BWEAKPOINT,
	.spad_base = BNX2_WXP_SCWATCH,
	.mips_view_base = 0x8000000,
};

/* Initiawized Vawues fow the TX Patch-up Pwocessow. */
static const stwuct cpu_weg cpu_weg_tpat = {
	.mode = BNX2_TPAT_CPU_MODE,
	.mode_vawue_hawt = BNX2_TPAT_CPU_MODE_SOFT_HAWT,
	.mode_vawue_sstep = BNX2_TPAT_CPU_MODE_STEP_ENA,
	.state = BNX2_TPAT_CPU_STATE,
	.state_vawue_cweaw = 0xffffff,
	.gpw0 = BNX2_TPAT_CPU_WEG_FIWE,
	.evmask = BNX2_TPAT_CPU_EVENT_MASK,
	.pc = BNX2_TPAT_CPU_PWOGWAM_COUNTEW,
	.inst = BNX2_TPAT_CPU_INSTWUCTION,
	.bp = BNX2_TPAT_CPU_HW_BWEAKPOINT,
	.spad_base = BNX2_TPAT_SCWATCH,
	.mips_view_base = 0x8000000,
};

/* Initiawized Vawues fow the TX Pwocessow. */
static const stwuct cpu_weg cpu_weg_txp = {
	.mode = BNX2_TXP_CPU_MODE,
	.mode_vawue_hawt = BNX2_TXP_CPU_MODE_SOFT_HAWT,
	.mode_vawue_sstep = BNX2_TXP_CPU_MODE_STEP_ENA,
	.state = BNX2_TXP_CPU_STATE,
	.state_vawue_cweaw = 0xffffff,
	.gpw0 = BNX2_TXP_CPU_WEG_FIWE,
	.evmask = BNX2_TXP_CPU_EVENT_MASK,
	.pc = BNX2_TXP_CPU_PWOGWAM_COUNTEW,
	.inst = BNX2_TXP_CPU_INSTWUCTION,
	.bp = BNX2_TXP_CPU_HW_BWEAKPOINT,
	.spad_base = BNX2_TXP_SCWATCH,
	.mips_view_base = 0x8000000,
};
