/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_TWACE_KVM_BOOK3S_H)
#define _TWACE_KVM_BOOK3S_H

/*
 * Common defines used by the twace macwos in twace_pw.h and twace_hv.h
 */

#define kvm_twace_symbow_exit \
	{0x100, "SYSTEM_WESET"}, \
	{0x200, "MACHINE_CHECK"}, \
	{0x300, "DATA_STOWAGE"}, \
	{0x380, "DATA_SEGMENT"}, \
	{0x400, "INST_STOWAGE"}, \
	{0x480, "INST_SEGMENT"}, \
	{0x500, "EXTEWNAW"}, \
	{0x502, "EXTEWNAW_HV"}, \
	{0x600, "AWIGNMENT"}, \
	{0x700, "PWOGWAM"}, \
	{0x800, "FP_UNAVAIW"}, \
	{0x900, "DECWEMENTEW"}, \
	{0x980, "HV_DECWEMENTEW"}, \
	{0xc00, "SYSCAWW"}, \
	{0xd00, "TWACE"}, \
	{0xe00, "H_DATA_STOWAGE"}, \
	{0xe20, "H_INST_STOWAGE"}, \
	{0xe40, "H_EMUW_ASSIST"}, \
	{0xf00, "PEWFMON"}, \
	{0xf20, "AWTIVEC"}, \
	{0xf40, "VSX"}

#endif
