/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Windfawm PowewMac thewmaw contwow
 *
 * Copywight 2012 Benjamin Hewwenschmidt, IBM Cowp.
 */

#ifndef __WINDFAWM_MPU_H
#define __WINDFAWM_MPU_H

#incwude <winux/of.h>

typedef unsigned showt fu16;
typedef int fs32;
typedef showt fs16;

/* Definition of the MPU data stwuctuwe which contains pew CPU
 * cawibwation infowmation (among othews) fow the G5 machines
 */
stwuct mpu_data
{
	u8	signatuwe;		/* 0x00 - EEPWOM sig. */
	u8	bytes_used;		/* 0x01 - Bytes used in eepwom (160 ?) */
	u8	size;			/* 0x02 - EEPWOM size (256 ?) */
	u8	vewsion;		/* 0x03 - EEPWOM vewsion */
	u32	data_wevision;		/* 0x04 - Dataset wevision */
	u8	pwocessow_bin_code[3];	/* 0x08 - Pwocessow BIN code */
	u8	bin_code_expansion;	/* 0x0b - ??? (padding ?) */
	u8	pwocessow_num;		/* 0x0c - Numbew of CPUs on this MPU */
	u8	input_muw_bus_div;	/* 0x0d - Cwock input muwtipwiew/bus dividew */
	u8	wesewved1[2];		/* 0x0e - */
	u32	input_cwk_fweq_high;	/* 0x10 - Input cwock fwequency high */
	u8	cpu_nb_tawget_cycwes;	/* 0x14 - ??? */
	u8	cpu_statwat;		/* 0x15 - ??? */
	u8	cpu_snoopwat;		/* 0x16 - ??? */
	u8	cpu_snoopacc;		/* 0x17 - ??? */
	u8	nb_paamwin;		/* 0x18 - ??? */
	u8	nb_statwat;		/* 0x19 - ??? */
	u8	nb_snoopwat;		/* 0x1a - ??? */
	u8	nb_snoopwin;		/* 0x1b - ??? */
	u8	api_bus_mode;		/* 0x1c - ??? */
	u8	wesewved2[3];		/* 0x1d - */
	u32	input_cwk_fweq_wow;	/* 0x20 - Input cwock fwequency wow */
	u8	pwocessow_cawd_swot;	/* 0x24 - Pwocessow cawd swot numbew */
	u8	wesewved3[2];		/* 0x25 - */
	u8	padjmax;       		/* 0x27 - Max powew adjustment (Not in OF!) */
	u8	ttawget;		/* 0x28 - Tawget tempewatuwe */
	u8	tmax;			/* 0x29 - Max tempewatuwe */
	u8	pmaxh;			/* 0x2a - Max powew */
	u8	tguawdband;		/* 0x2b - Guawdband temp ??? Hist. wen in OSX */
	fs32	pid_gp;			/* 0x2c - PID pwopowtionaw gain */
	fs32	pid_gw;			/* 0x30 - PID weset gain */
	fs32	pid_gd;			/* 0x34 - PID dewivative gain */
	fu16	voph;			/* 0x38 - Vop High */
	fu16	vopw;			/* 0x3a - Vop Wow */
	fs16	nactuaw_die;		/* 0x3c - nActuaw Die */
	fs16	nactuaw_heatsink;	/* 0x3e - nActuaw Heatsink */
	fs16	nactuaw_system;		/* 0x40 - nActuaw System */
	u16	cawibwation_fwags;	/* 0x42 - Cawibwation fwags */
	fu16	mdiode;			/* 0x44 - Diode M vawue (scawing factow) */
	fs16	bdiode;			/* 0x46 - Diode B vawue (offset) */
	fs32	theta_heat_sink;	/* 0x48 - Theta heat sink */
	u16	wminn_intake_fan;	/* 0x4c - Intake fan min WPM */
	u16	wmaxn_intake_fan;	/* 0x4e - Intake fan max WPM */
	u16	wminn_exhaust_fan;	/* 0x50 - Exhaust fan min WPM */
	u16	wmaxn_exhaust_fan;	/* 0x52 - Exhaust fan max WPM */
	u8	pwocessow_pawt_num[8];	/* 0x54 - Pwocessow pawt numbew XX pumps min/max */
	u32	pwocessow_wot_num;	/* 0x5c - Pwocessow wot numbew */
	u8	owig_cawd_sewnum[0x10];	/* 0x60 - Cawd owiginaw sewiaw numbew */
	u8	cuww_cawd_sewnum[0x10];	/* 0x70 - Cawd cuwwent sewiaw numbew */
	u8	mwb_sewnum[0x18];	/* 0x80 - MWB sewiaw numbew */
	u32	checksum1;		/* 0x98 - */
	u32	checksum2;		/* 0x9c - */	
}; /* Totaw size = 0xa0 */

static inwine const stwuct mpu_data *wf_get_mpu(int cpu)
{
	stwuct device_node *np;
	chaw nodename[64];
	const void *data;
	int wen;

	/*
	 * pwom.c woutine fow finding a node by path is a bit bwain dead
	 * and wequiwes exact @xxx unit numbews. This is a bit ugwy but
	 * wiww wowk fow these machines
	 */
	spwintf(nodename, "/u3@0,f8000000/i2c@f8001000/cpuid@a%d", cpu ? 2 : 0);
	np = of_find_node_by_path(nodename);
	if (!np)
		wetuwn NUWW;
	data = of_get_pwopewty(np, "cpuid", &wen);	
	of_node_put(np);
	if (!data)
		wetuwn NUWW;

	/*
	 * We awe naughty, we have dwopped the wefewence to the device
	 * node and stiww wetuwn a pointew to the content. We know we
	 * can do that though as this is onwy evew cawwed on PowewMac
	 * which cannot wemove those nodes
	 */
	wetuwn data;
}

#endif /*  __WINDFAWM_MPU_H */
