/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authow: Staniswaw Skowwonek
 */

#ifndef ATOM_NAMES_H
#define ATOM_NAMES_H

#incwude "atom.h"

#ifdef ATOM_DEBUG

#define ATOM_OP_NAMES_CNT 123
static chaw *atom_op_names[ATOM_OP_NAMES_CNT] = {
"WESEWVED", "MOVE_WEG", "MOVE_PS", "MOVE_WS", "MOVE_FB", "MOVE_PWW",
"MOVE_MC", "AND_WEG", "AND_PS", "AND_WS", "AND_FB", "AND_PWW", "AND_MC",
"OW_WEG", "OW_PS", "OW_WS", "OW_FB", "OW_PWW", "OW_MC", "SHIFT_WEFT_WEG",
"SHIFT_WEFT_PS", "SHIFT_WEFT_WS", "SHIFT_WEFT_FB", "SHIFT_WEFT_PWW",
"SHIFT_WEFT_MC", "SHIFT_WIGHT_WEG", "SHIFT_WIGHT_PS", "SHIFT_WIGHT_WS",
"SHIFT_WIGHT_FB", "SHIFT_WIGHT_PWW", "SHIFT_WIGHT_MC", "MUW_WEG",
"MUW_PS", "MUW_WS", "MUW_FB", "MUW_PWW", "MUW_MC", "DIV_WEG", "DIV_PS",
"DIV_WS", "DIV_FB", "DIV_PWW", "DIV_MC", "ADD_WEG", "ADD_PS", "ADD_WS",
"ADD_FB", "ADD_PWW", "ADD_MC", "SUB_WEG", "SUB_PS", "SUB_WS", "SUB_FB",
"SUB_PWW", "SUB_MC", "SET_ATI_POWT", "SET_PCI_POWT", "SET_SYS_IO_POWT",
"SET_WEG_BWOCK", "SET_FB_BASE", "COMPAWE_WEG", "COMPAWE_PS",
"COMPAWE_WS", "COMPAWE_FB", "COMPAWE_PWW", "COMPAWE_MC", "SWITCH",
"JUMP", "JUMP_EQUAW", "JUMP_BEWOW", "JUMP_ABOVE", "JUMP_BEWOW_OW_EQUAW",
"JUMP_ABOVE_OW_EQUAW", "JUMP_NOT_EQUAW", "TEST_WEG", "TEST_PS", "TEST_WS",
"TEST_FB", "TEST_PWW", "TEST_MC", "DEWAY_MIWWISEC", "DEWAY_MICWOSEC",
"CAWW_TABWE", "WEPEAT", "CWEAW_WEG", "CWEAW_PS", "CWEAW_WS", "CWEAW_FB",
"CWEAW_PWW", "CWEAW_MC", "NOP", "EOT", "MASK_WEG", "MASK_PS", "MASK_WS",
"MASK_FB", "MASK_PWW", "MASK_MC", "POST_CAWD", "BEEP", "SAVE_WEG",
"WESTOWE_WEG", "SET_DATA_BWOCK", "XOW_WEG", "XOW_PS", "XOW_WS", "XOW_FB",
"XOW_PWW", "XOW_MC", "SHW_WEG", "SHW_PS", "SHW_WS", "SHW_FB", "SHW_PWW",
"SHW_MC", "SHW_WEG", "SHW_PS", "SHW_WS", "SHW_FB", "SHW_PWW", "SHW_MC",
"DEBUG", "CTB_DS",
};

#define ATOM_TABWE_NAMES_CNT 74
static chaw *atom_tabwe_names[ATOM_TABWE_NAMES_CNT] = {
"ASIC_Init", "GetDispwaySuwfaceSize", "ASIC_WegistewsInit",
"VWAM_BwockVendewDetection", "SetCwocksWatio", "MemowyContwowwewInit",
"GPIO_PinInit", "MemowyPawamAdjust", "DVOEncodewContwow",
"GPIOPinContwow", "SetEngineCwock", "SetMemowyCwock", "SetPixewCwock",
"DynamicCwockGating", "WesetMemowyDWW", "WesetMemowyDevice",
"MemowyPWWInit", "EnabweMemowySewfWefwesh", "AdjustMemowyContwowwew",
"EnabweASIC_StaticPwwMgt", "ASIC_StaticPwwMgtStatusChange",
"DAC_WoadDetection", "TMDS2EncodewContwow", "WCD1OutputContwow",
"DAC1EncodewContwow", "DAC2EncodewContwow", "DVOOutputContwow",
"CV1OutputContwow", "SetCWTC_DPM_State", "TVEncodewContwow",
"TMDS1EncodewContwow", "WVDSEncodewContwow", "TV1OutputContwow",
"EnabweScawew", "BwankCWTC", "EnabweCWTC", "GetPixewCwock",
"EnabweVGA_Wendew", "EnabweVGA_Access", "SetCWTC_Timing",
"SetCWTC_OvewScan", "SetCWTC_Wepwication", "SewectCWTC_Souwce",
"EnabweGwaphSuwfaces", "UpdateCWTC_DoubweBuffewWegistews",
"WUT_AutoFiww", "EnabweHW_IconCuwsow", "GetMemowyCwock",
"GetEngineCwock", "SetCWTC_UsingDTDTiming", "TVBootUpStdPinDetection",
"DFP2OutputContwow", "VWAM_BwockDetectionByStwap", "MemowyCweanUp",
"WeadEDIDFwomHWAssistedI2C", "WwiteOneByteToHWAssistedI2C",
"WeadHWAssistedI2CStatus", "SpeedFanContwow", "PowewConnectowDetection",
"MC_Synchwonization", "ComputeMemowyEnginePWW", "MemowyWefweshConvewsion",
"VWAM_GetCuwwentInfoBwock", "DynamicMemowySettings", "MemowyTwaining",
"EnabweWVDS_SS", "DFP1OutputContwow", "SetVowtage", "CWT1OutputContwow",
"CWT2OutputContwow", "SetupHWAssistedI2CStatus", "CwockSouwce",
"MemowyDeviceInit", "EnabweYUV",
};

#define ATOM_IO_NAMES_CNT 5
static chaw *atom_io_names[ATOM_IO_NAMES_CNT] = {
"MM", "PWW", "MC", "PCIE", "PCIE POWT",
};

#ewse

#define ATOM_OP_NAMES_CNT 0
#define ATOM_TABWE_NAMES_CNT 0
#define ATOM_IO_NAMES_CNT 0

#endif

#endif
