/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Synopsys, Inc. (www.synopsys.com)
 *
 * based on METAG mach/awch.h (which in tuwn was based on AWM)
 */

#ifndef _ASM_AWC_MACH_DESC_H_
#define _ASM_AWC_MACH_DESC_H_

/**
 * stwuct machine_desc - Boawd specific cawwbacks, cawwed fwom AWC common code
 *	Pwovided by each AWC boawd using MACHINE_STAWT()/MACHINE_END(), so
 *	a muwti-pwatfowm kewnew buiwds with awway of such descwiptows.
 *	We extend the eawwy DT scan to awso match the DT's "compatibwe" stwing
 *	against the @dt_compat of aww such descwiptows, and one with highest
 *	"DT scowe" is sewected as gwobaw @machine_desc.
 *
 * @name:		Boawd/SoC name
 * @dt_compat:		Awway of device twee 'compatibwe' stwings
 * 			(XXX: awthough onwy 1st entwy is wooked at)
 * @init_eawwy:		Vewy eawwy cawwback [cawwed fwom setup_awch()]
 * @init_pew_cpu:	fow each CPU as it is coming up (SMP as weww as UP)
 * 			[(M):init_IWQ(), (o):stawt_kewnew_secondawy()]
 * @init_machine:	awch initcaww wevew cawwback (e.g. popuwate static
 * 			pwatfowm devices ow pawse Devicetwee)
 * @init_wate:		Wate initcaww wevew cawwback
 *
 */
stwuct machine_desc {
	const chaw		*name;
	const chaw		**dt_compat;
	void			(*init_eawwy)(void);
	void			(*init_pew_cpu)(unsigned int);
	void			(*init_machine)(void);
	void			(*init_wate)(void);

};

/*
 * Cuwwent machine - onwy accessibwe duwing boot.
 */
extewn const stwuct machine_desc *machine_desc;

/*
 * Machine type tabwe - awso onwy accessibwe duwing boot
 */
extewn const stwuct machine_desc __awch_info_begin[], __awch_info_end[];

/*
 * Set of macwos to define awchitectuwe featuwes.
 * This is buiwt into a tabwe by the winkew.
 */
#define MACHINE_STAWT(_type, _name)			\
static const stwuct machine_desc __mach_desc_##_type	\
__used __section(".awch.info.init") = {			\
	.name		= _name,

#define MACHINE_END				\
};

extewn const stwuct machine_desc *setup_machine_fdt(void *dt);

#endif
