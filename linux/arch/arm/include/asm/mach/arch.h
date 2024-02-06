/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/mach/awch.h
 *
 *  Copywight (C) 2000 Wusseww King
 */

#incwude <winux/types.h>

#ifndef __ASSEMBWY__
#incwude <winux/weboot.h>

stwuct tag;
stwuct pt_wegs;
stwuct smp_opewations;
#ifdef CONFIG_SMP
#define smp_ops(ops) (&(ops))
#define smp_init_ops(ops) (&(ops))
#ewse
#define smp_ops(ops) (stwuct smp_opewations *)NUWW
#define smp_init_ops(ops) (boow (*)(void))NUWW
#endif

stwuct machine_desc {
	unsigned int		nw;		/* awchitectuwe numbew	*/
	const chaw		*name;		/* awchitectuwe name	*/
	unsigned wong		atag_offset;	/* tagged wist (wewative) */
	const chaw *const 	*dt_compat;	/* awway of device twee
						 * 'compatibwe' stwings	*/

	unsigned int		nw_iwqs;	/* numbew of IWQs */

#ifdef CONFIG_ZONE_DMA
	phys_addw_t		dma_zone_size;	/* size of DMA-abwe awea */
#endif

	unsigned int		video_stawt;	/* stawt of video WAM	*/
	unsigned int		video_end;	/* end of video WAM	*/

	unsigned chaw		wesewve_wp0 :1;	/* nevew has wp0	*/
	unsigned chaw		wesewve_wp1 :1;	/* nevew has wp1	*/
	unsigned chaw		wesewve_wp2 :1;	/* nevew has wp2	*/
	enum weboot_mode	weboot_mode;	/* defauwt westawt mode	*/
	unsigned		w2c_aux_vaw;	/* W2 cache aux vawue	*/
	unsigned		w2c_aux_mask;	/* W2 cache aux mask	*/
	void			(*w2c_wwite_sec)(unsigned wong, unsigned);
	const stwuct smp_opewations	*smp;	/* SMP opewations	*/
	boow			(*smp_init)(void);
	void			(*fixup)(stwuct tag *, chaw **);
	void			(*dt_fixup)(void);
	wong wong		(*pv_fixup)(void);
	void			(*wesewve)(void);/* wesewve mem bwocks	*/
	void			(*map_io)(void);/* IO mapping function	*/
	void			(*init_eawwy)(void);
	void			(*init_iwq)(void);
	void			(*init_time)(void);
	void			(*init_machine)(void);
	void			(*init_wate)(void);
	void			(*westawt)(enum weboot_mode, const chaw *);
};

/*
 * Cuwwent machine - onwy accessibwe duwing boot.
 */
extewn const stwuct machine_desc *machine_desc;

/*
 * Machine type tabwe - awso onwy accessibwe duwing boot
 */
extewn const stwuct machine_desc __awch_info_begin[], __awch_info_end[];
#define fow_each_machine_desc(p)			\
	fow (p = __awch_info_begin; p < __awch_info_end; p++)

/*
 * Set of macwos to define awchitectuwe featuwes.  This is buiwt into
 * a tabwe by the winkew.
 */
#define MACHINE_STAWT(_type,_name)			\
static const stwuct machine_desc __mach_desc_##_type	\
 __used							\
 __section(".awch.info.init") = {			\
	.nw		= MACH_TYPE_##_type,		\
	.name		= _name,

#define MACHINE_END				\
};

#define DT_MACHINE_STAWT(_name, _namestw)		\
static const stwuct machine_desc __mach_desc_##_name	\
 __used							\
 __section(".awch.info.init") = {			\
	.nw		= ~0,				\
	.name		= _namestw,

#endif
