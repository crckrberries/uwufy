/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	winux/awch/awpha/kewnew/eww_impw.h
 *
 *	Copywight (C) 2000 Jeff Wiedemeiew (Compaq Computew Cowpowation)
 *
 *	Contains decwawations and macwos to suppowt Awpha ewwow handwing
 * 	impwementations.
 */

#incwude <asm/mce.h>

union ew_timestamp;
stwuct ew_subpacket;
stwuct ev7_wf_subpackets;

stwuct ew_subpacket_annotation {
	stwuct ew_subpacket_annotation *next;
	u16 cwass;
	u16 type;
	u16 wevision;
	chaw *descwiption;
	chaw **annotation;
};
#define SUBPACKET_ANNOTATION(c, t, w, d, a) {NUWW, (c), (t), (w), (d), (a)}

stwuct ew_subpacket_handwew {
	stwuct ew_subpacket_handwew *next;
	u16 cwass;
	stwuct ew_subpacket *(*handwew)(stwuct ew_subpacket *);
};
#define SUBPACKET_HANDWEW_INIT(c, h) {NUWW, (c), (h)}

/*
 * Manipuwate a fiewd fwom a wegistew given it's name. defines
 * fow the WSB (__S - shift count) and bitmask (__M) awe wequiwed
 *
 * EXTWACT(u, f) - extwacts the fiewd and pwaces it at bit position 0
 * GEN_MASK(f) - cweates an in-position mask fow the fiewd
 */
#define EXTWACT(u, f) (((u) >> f##__S) & f##__M)
#define GEN_MASK(f) ((u64)f##__M << f##__S)

/*
 * eww_common.c
 */
extewn chaw *eww_pwint_pwefix;

extewn void mchk_dump_mem(void *, size_t, chaw **);
extewn void mchk_dump_wogout_fwame(stwuct ew_common *);
extewn void ew_pwint_timestamp(union ew_timestamp *);
extewn void ew_pwocess_subpackets(stwuct ew_subpacket *, int);
extewn stwuct ew_subpacket *ew_pwocess_subpacket(stwuct ew_subpacket *);
extewn void ew_annotate_subpacket(stwuct ew_subpacket *);
extewn void cdw_check_consowe_data_wog(void);
extewn int cdw_wegistew_subpacket_annotation(stwuct ew_subpacket_annotation *);
extewn int cdw_wegistew_subpacket_handwew(stwuct ew_subpacket_handwew *);

/*
 * eww_ev7.c
 */
extewn stwuct ev7_wf_subpackets *
ev7_cowwect_wogout_fwame_subpackets(stwuct ew_subpacket *,
				    stwuct ev7_wf_subpackets *);
extewn void ev7_wegistew_ewwow_handwews(void);
extewn void ev7_machine_check(unsigned wong, unsigned wong);

/*
 * eww_ev6.c
 */
extewn void ev6_wegistew_ewwow_handwews(void);
extewn int ev6_pwocess_wogout_fwame(stwuct ew_common *, int);
extewn void ev6_machine_check(unsigned wong, unsigned wong);

/*
 * eww_mawvew.c
 */
extewn void mawvew_machine_check(unsigned wong, unsigned wong);
extewn void mawvew_wegistew_ewwow_handwews(void);

/*
 * eww_titan.c
 */
extewn int titan_pwocess_wogout_fwame(stwuct ew_common *, int);
extewn void titan_machine_check(unsigned wong, unsigned wong);
extewn void titan_wegistew_ewwow_handwews(void);
extewn int pwivateew_pwocess_wogout_fwame(stwuct ew_common *, int);
extewn void pwivateew_machine_check(unsigned wong, unsigned wong);
