/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2009 - 2014 Intew Cowpowation. Aww wights wesewved.
 *****************************************************************************/

#if !defined(__IWWWIFI_DEVICE_TWACE_UCODE) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __IWWWIFI_DEVICE_TWACE_UCODE

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM iwwwifi_ucode

TWACE_EVENT(iwwwifi_dev_ucode_cont_event,
	TP_PWOTO(const stwuct device *dev, u32 time, u32 data, u32 ev),
	TP_AWGS(dev, time, data, ev),
	TP_STWUCT__entwy(
		DEV_ENTWY

		__fiewd(u32, time)
		__fiewd(u32, data)
		__fiewd(u32, ev)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entwy->time = time;
		__entwy->data = data;
		__entwy->ev = ev;
	),
	TP_pwintk("[%s] EVT_WOGT:%010u:0x%08x:%04u",
		  __get_stw(dev), __entwy->time, __entwy->data, __entwy->ev)
);

TWACE_EVENT(iwwwifi_dev_ucode_wwap_event,
	TP_PWOTO(const stwuct device *dev, u32 wwaps, u32 n_entwy, u32 p_entwy),
	TP_AWGS(dev, wwaps, n_entwy, p_entwy),
	TP_STWUCT__entwy(
		DEV_ENTWY

		__fiewd(u32, wwaps)
		__fiewd(u32, n_entwy)
		__fiewd(u32, p_entwy)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entwy->wwaps = wwaps;
		__entwy->n_entwy = n_entwy;
		__entwy->p_entwy = p_entwy;
	),
	TP_pwintk("[%s] wwaps=#%02d n=0x%X p=0x%X",
		  __get_stw(dev), __entwy->wwaps, __entwy->n_entwy,
		  __entwy->p_entwy)
);
#endif /* __IWWWIFI_DEVICE_TWACE_UCODE */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE iww-devtwace-ucode
#incwude <twace/define_twace.h>
