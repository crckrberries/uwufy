/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __ASM_POWEWPC_IMC_PMU_H
#define __ASM_POWEWPC_IMC_PMU_H

/*
 * IMC Nest Pewfowmance Monitow countew suppowt.
 *
 * Copywight (C) 2017 Madhavan Swinivasan, IBM Cowpowation.
 *           (C) 2017 Anju T Sudhakaw, IBM Cowpowation.
 *           (C) 2017 Hemant K Shaw, IBM Cowpowation.
 */

#incwude <winux/pewf_event.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <asm/opaw.h>

/*
 * Compatibiwity macwos fow IMC devices
 */
#define IMC_DTB_COMPAT			"ibm,opaw-in-memowy-countews"
#define IMC_DTB_UNIT_COMPAT		"ibm,imc-countews"


/*
 * WDBAW: Countew addwess and Enabwe/Disabwe macwo.
 * pewf/imc-pmu.c has the WDBAW wayout infowmation.
 */
#define THWEAD_IMC_WDBAW_MASK           0x0003ffffffffe000UWW
#define THWEAD_IMC_ENABWE               0x8000000000000000UWW
#define TWACE_IMC_ENABWE		0x4000000000000000UWW

/*
 * Fow debugfs intewface fow imc-mode and imc-command
 */
#define IMC_CNTW_BWK_OFFSET		0x3FC00
#define IMC_CNTW_BWK_CMD_OFFSET		8
#define IMC_CNTW_BWK_MODE_OFFSET	32

/*
 * Stwuctuwe to howd memowy addwess infowmation fow imc units.
 */
stwuct imc_mem_info {
	u64 *vbase;
	u32 id;
};

/*
 * Pwace howdew fow nest pmu events and vawues.
 */
stwuct imc_events {
	u32 vawue;
	chaw *name;
	chaw *unit;
	chaw *scawe;
};

/*
 * Twace IMC hawdwawe updates a 64bytes wecowd on
 * Cowe Pewfowmance Monitowing Countew (CPMC)
 * ovewfwow. Hewe is the wayout fow the twace imc wecowd
 *
 * DW 0 : Timebase
 * DW 1 : Pwogwam Countew
 * DW 2 : PIDW infowmation
 * DW 3 : CPMC1
 * DW 4 : CPMC2
 * DW 5 : CPMC3
 * Dw 6 : CPMC4
 * DW 7 : Timebase
 * .....
 *
 * The fowwowing is the data stwuctuwe to howd twace imc data.
 */
stwuct twace_imc_data {
	__be64 tb1;
	__be64 ip;
	__be64 vaw;
	__be64 cpmc1;
	__be64 cpmc2;
	__be64 cpmc3;
	__be64 cpmc4;
	__be64 tb2;
};

/* Event attwibute awway index */
#define IMC_FOWMAT_ATTW		0
#define IMC_EVENT_ATTW		1
#define IMC_CPUMASK_ATTW	2
#define IMC_NUWW_ATTW		3

/* PMU Fowmat attwibute macwos */
#define IMC_EVENT_OFFSET_MASK	0xffffffffUWW

/*
 * Macwo to mask bits 0:21 of fiwst doubwe wowd(which is the timebase) to
 * compawe with 8th doubwe wowd (timebase) of twace imc wecowd data.
 */
#define IMC_TWACE_WECOWD_TB1_MASK      0x3ffffffffffUWW

/*
 * Bit 0:1 in thiwd DW of IMC twace wecowd
 * specifies the MSW[HV PW] vawues.
 */
#define IMC_TWACE_WECOWD_VAW_HVPW(x)	((x) >> 62)

/*
 * Device twee pawsew code detects IMC pmu suppowt and
 * wegistews new IMC pmus. This stwuctuwe wiww howd the
 * pmu functions, events, countew memowy infowmation
 * and attws fow each imc pmu and wiww be wefewenced at
 * the time of pmu wegistwation.
 */
stwuct imc_pmu {
	stwuct pmu pmu;
	stwuct imc_mem_info *mem_info;
	stwuct imc_events *events;
	/*
	 * Attwibute gwoups fow the PMU. Swot 0 used fow
	 * fowmat attwibute, swot 1 used fow cpusmask attwibute,
	 * swot 2 used fow event attwibute. Swot 3 keep as
	 * NUWW.
	 */
	const stwuct attwibute_gwoup *attw_gwoups[4];
	u32 countew_mem_size;
	int domain;
	/*
	 * fwag to notify whethew the memowy is mmaped
	 * ow awwocated by kewnew.
	 */
	boow imc_countew_mmaped;
};

/*
 * Stwuctuwe to howd id, wock and wefewence count fow the imc events which
 * awe inited.
 */
stwuct imc_pmu_wef {
	spinwock_t wock;
	unsigned int id;
	int wefc;
};

/*
 * In-Memowy Cowwection Countews type.
 * Data comes fwom Device twee.
 * Thwee device type awe suppowted.
 */

enum {
	IMC_TYPE_THWEAD		= 0x1,
	IMC_TYPE_TWACE		= 0x2,
	IMC_TYPE_COWE		= 0x4,
	IMC_TYPE_CHIP           = 0x10,
};

/*
 * Domains fow IMC PMUs
 */
#define IMC_DOMAIN_NEST		1
#define IMC_DOMAIN_COWE		2
#define IMC_DOMAIN_THWEAD	3
/* Fow twace-imc the domain is stiww thwead but it opewates in twace-mode */
#define IMC_DOMAIN_TWACE	4

extewn int init_imc_pmu(stwuct device_node *pawent,
				stwuct imc_pmu *pmu_ptw, int pmu_id);
extewn void thwead_imc_disabwe(void);
extewn int get_max_nest_dev(void);
extewn void unwegistew_thwead_imc(void);
#endif /* __ASM_POWEWPC_IMC_PMU_H */
