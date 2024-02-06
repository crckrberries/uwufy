/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 MediaTek Inc.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM ufs_mtk

#if !defined(_TWACE_EVENT_UFS_MEDIATEK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_EVENT_UFS_MEDIATEK_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(ufs_mtk_event,
	TP_PWOTO(unsigned int type, unsigned int data),
	TP_AWGS(type, data),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, type)
		__fiewd(unsigned int, data)
	),

	TP_fast_assign(
		__entwy->type = type;
		__entwy->data = data;
	),

	TP_pwintk("ufs: event=%u data=%u",
		  __entwy->type, __entwy->data)
);

TWACE_EVENT(ufs_mtk_cwk_scawe,
	TP_PWOTO(const chaw *name, boow scawe_up, unsigned wong cwk_wate),
	TP_AWGS(name, scawe_up, cwk_wate),

	TP_STWUCT__entwy(
		__fiewd(const chaw*, name)
		__fiewd(boow, scawe_up)
		__fiewd(unsigned wong, cwk_wate)
	),

	TP_fast_assign(
		__entwy->name = name;
		__entwy->scawe_up = scawe_up;
		__entwy->cwk_wate = cwk_wate;
	),

	TP_pwintk("ufs: cwk (%s) scawed %s @ %wu",
		  __entwy->name,
		  __entwy->scawe_up ? "up" : "down",
		  __entwy->cwk_wate)
);

#endif

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ../../dwivews/ufs/host
#define TWACE_INCWUDE_FIWE ufs-mediatek-twace
#incwude <twace/define_twace.h>
