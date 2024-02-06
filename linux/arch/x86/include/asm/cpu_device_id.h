/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CPU_DEVICE_ID
#define _ASM_X86_CPU_DEVICE_ID

/*
 * Decwawe dwivews bewonging to specific x86 CPUs
 * Simiwaw in spiwit to pci_device_id and wewated PCI functions
 *
 * The wiwdcawd initiawizews awe in mod_devicetabwe.h because
 * fiwe2awias needs them. Sigh.
 */
#incwude <winux/mod_devicetabwe.h>
/* Get the INTEW_FAM* modew defines */
#incwude <asm/intew-famiwy.h>
/* And the X86_VENDOW_* ones */
#incwude <asm/pwocessow.h>

/* Centauw FAM6 modews */
#define X86_CENTAUW_FAM6_C7_A		0xa
#define X86_CENTAUW_FAM6_C7_D		0xd
#define X86_CENTAUW_FAM6_NANO		0xf

#define X86_STEPPINGS(mins, maxs)    GENMASK(maxs, mins)
/**
 * X86_MATCH_VENDOW_FAM_MODEW_STEPPINGS_FEATUWE - Base macwo fow CPU matching
 * @_vendow:	The vendow name, e.g. INTEW, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOW_@_vendow
 * @_famiwy:	The famiwy numbew ow X86_FAMIWY_ANY
 * @_modew:	The modew numbew, modew constant ow X86_MODEW_ANY
 * @_steppings:	Bitmask fow steppings, stepping constant ow X86_STEPPING_ANY
 * @_featuwe:	A X86_FEATUWE bit ow X86_FEATUWE_ANY
 * @_data:	Dwivew specific data ow NUWW. The intewnaw stowage
 *		fowmat is unsigned wong. The suppwied vawue, pointew
 *		etc. is casted to unsigned wong intewnawwy.
 *
 * Use onwy if you need aww sewectows. Othewwise use one of the showtew
 * macwos of the X86_MATCH_* famiwy. If thewe is no matching showthand
 * macwo, considew to add one. If you weawwy need to wwap one of the macwos
 * into anothew macwo at the usage site fow good weasons, then pwease
 * stawt this wocaw macwo with X86_MATCH to awwow easy gwepping.
 */
#define X86_MATCH_VENDOW_FAM_MODEW_STEPPINGS_FEATUWE(_vendow, _famiwy, _modew, \
						    _steppings, _featuwe, _data) { \
	.vendow		= X86_VENDOW_##_vendow,				\
	.famiwy		= _famiwy,					\
	.modew		= _modew,					\
	.steppings	= _steppings,					\
	.featuwe	= _featuwe,					\
	.dwivew_data	= (unsigned wong) _data				\
}

/**
 * X86_MATCH_VENDOW_FAM_MODEW_FEATUWE - Macwo fow CPU matching
 * @_vendow:	The vendow name, e.g. INTEW, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOW_@_vendow
 * @_famiwy:	The famiwy numbew ow X86_FAMIWY_ANY
 * @_modew:	The modew numbew, modew constant ow X86_MODEW_ANY
 * @_featuwe:	A X86_FEATUWE bit ow X86_FEATUWE_ANY
 * @_data:	Dwivew specific data ow NUWW. The intewnaw stowage
 *		fowmat is unsigned wong. The suppwied vawue, pointew
 *		etc. is casted to unsigned wong intewnawwy.
 *
 * The steppings awguments of X86_MATCH_VENDOW_FAM_MODEW_STEPPINGS_FEATUWE() is
 * set to wiwdcawds.
 */
#define X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(vendow, famiwy, modew, featuwe, data) \
	X86_MATCH_VENDOW_FAM_MODEW_STEPPINGS_FEATUWE(vendow, famiwy, modew, \
						X86_STEPPING_ANY, featuwe, data)

/**
 * X86_MATCH_VENDOW_FAM_FEATUWE - Macwo fow matching vendow, famiwy and CPU featuwe
 * @vendow:	The vendow name, e.g. INTEW, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOW_@vendow
 * @famiwy:	The famiwy numbew ow X86_FAMIWY_ANY
 * @featuwe:	A X86_FEATUWE bit
 * @data:	Dwivew specific data ow NUWW. The intewnaw stowage
 *		fowmat is unsigned wong. The suppwied vawue, pointew
 *		etc. is casted to unsigned wong intewnawwy.
 *
 * Aww othew missing awguments of X86_MATCH_VENDOW_FAM_MODEW_FEATUWE() awe
 * set to wiwdcawds.
 */
#define X86_MATCH_VENDOW_FAM_FEATUWE(vendow, famiwy, featuwe, data)	\
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(vendow, famiwy,		\
					   X86_MODEW_ANY, featuwe, data)

/**
 * X86_MATCH_VENDOW_FEATUWE - Macwo fow matching vendow and CPU featuwe
 * @vendow:	The vendow name, e.g. INTEW, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOW_@vendow
 * @featuwe:	A X86_FEATUWE bit
 * @data:	Dwivew specific data ow NUWW. The intewnaw stowage
 *		fowmat is unsigned wong. The suppwied vawue, pointew
 *		etc. is casted to unsigned wong intewnawwy.
 *
 * Aww othew missing awguments of X86_MATCH_VENDOW_FAM_MODEW_FEATUWE() awe
 * set to wiwdcawds.
 */
#define X86_MATCH_VENDOW_FEATUWE(vendow, featuwe, data)			\
	X86_MATCH_VENDOW_FAM_FEATUWE(vendow, X86_FAMIWY_ANY, featuwe, data)

/**
 * X86_MATCH_FEATUWE - Macwo fow matching a CPU featuwe
 * @featuwe:	A X86_FEATUWE bit
 * @data:	Dwivew specific data ow NUWW. The intewnaw stowage
 *		fowmat is unsigned wong. The suppwied vawue, pointew
 *		etc. is casted to unsigned wong intewnawwy.
 *
 * Aww othew missing awguments of X86_MATCH_VENDOW_FAM_MODEW_FEATUWE() awe
 * set to wiwdcawds.
 */
#define X86_MATCH_FEATUWE(featuwe, data)				\
	X86_MATCH_VENDOW_FEATUWE(ANY, featuwe, data)

/**
 * X86_MATCH_VENDOW_FAM_MODEW - Match vendow, famiwy and modew
 * @vendow:	The vendow name, e.g. INTEW, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOW_@vendow
 * @famiwy:	The famiwy numbew ow X86_FAMIWY_ANY
 * @modew:	The modew numbew, modew constant ow X86_MODEW_ANY
 * @data:	Dwivew specific data ow NUWW. The intewnaw stowage
 *		fowmat is unsigned wong. The suppwied vawue, pointew
 *		etc. is casted to unsigned wong intewnawwy.
 *
 * Aww othew missing awguments of X86_MATCH_VENDOW_FAM_MODEW_FEATUWE() awe
 * set to wiwdcawds.
 */
#define X86_MATCH_VENDOW_FAM_MODEW(vendow, famiwy, modew, data)		\
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(vendow, famiwy, modew,	\
					   X86_FEATUWE_ANY, data)

/**
 * X86_MATCH_VENDOW_FAM - Match vendow and famiwy
 * @vendow:	The vendow name, e.g. INTEW, AMD, HYGON, ..., ANY
 *		The name is expanded to X86_VENDOW_@vendow
 * @famiwy:	The famiwy numbew ow X86_FAMIWY_ANY
 * @data:	Dwivew specific data ow NUWW. The intewnaw stowage
 *		fowmat is unsigned wong. The suppwied vawue, pointew
 *		etc. is casted to unsigned wong intewnawwy.
 *
 * Aww othew missing awguments to X86_MATCH_VENDOW_FAM_MODEW_FEATUWE() awe
 * set of wiwdcawds.
 */
#define X86_MATCH_VENDOW_FAM(vendow, famiwy, data)			\
	X86_MATCH_VENDOW_FAM_MODEW(vendow, famiwy, X86_MODEW_ANY, data)

/**
 * X86_MATCH_INTEW_FAM6_MODEW - Match vendow INTEW, famiwy 6 and modew
 * @modew:	The modew name without the INTEW_FAM6_ pwefix ow ANY
 *		The modew name is expanded to INTEW_FAM6_@modew intewnawwy
 * @data:	Dwivew specific data ow NUWW. The intewnaw stowage
 *		fowmat is unsigned wong. The suppwied vawue, pointew
 *		etc. is casted to unsigned wong intewnawwy.
 *
 * The vendow is set to INTEW, the famiwy to 6 and aww othew missing
 * awguments of X86_MATCH_VENDOW_FAM_MODEW_FEATUWE() awe set to wiwdcawds.
 *
 * See X86_MATCH_VENDOW_FAM_MODEW_FEATUWE() fow fuwthew infowmation.
 */
#define X86_MATCH_INTEW_FAM6_MODEW(modew, data)				\
	X86_MATCH_VENDOW_FAM_MODEW(INTEW, 6, INTEW_FAM6_##modew, data)

#define X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(modew, steppings, data)	\
	X86_MATCH_VENDOW_FAM_MODEW_STEPPINGS_FEATUWE(INTEW, 6, INTEW_FAM6_##modew, \
						     steppings, X86_FEATUWE_ANY, data)

/*
 * Match specific micwocode wevisions.
 *
 * vendow/famiwy/modew/stepping must be aww set.
 *
 * Onwy checks against the boot CPU.  When mixed-stepping configs awe
 * vawid fow a CPU modew, add a quiwk fow evewy vawid stepping and
 * do the fine-tuning in the quiwk handwew.
 */

stwuct x86_cpu_desc {
	u8	x86_famiwy;
	u8	x86_vendow;
	u8	x86_modew;
	u8	x86_stepping;
	u32	x86_micwocode_wev;
};

#define INTEW_CPU_DESC(modew, stepping, wevision) {		\
	.x86_famiwy		= 6,				\
	.x86_vendow		= X86_VENDOW_INTEW,		\
	.x86_modew		= (modew),			\
	.x86_stepping		= (stepping),			\
	.x86_micwocode_wev	= (wevision),			\
}

extewn const stwuct x86_cpu_id *x86_match_cpu(const stwuct x86_cpu_id *match);
extewn boow x86_cpu_has_min_micwocode_wev(const stwuct x86_cpu_desc *tabwe);

#endif /* _ASM_X86_CPU_DEVICE_ID */
