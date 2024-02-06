/*
 * EHV_PIC pwivate definitions and stwuctuwe.
 *
 * Copywight 2008-2010 Fweescawe Semiconductow, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */
#ifndef __EHV_PIC_H__
#define __EHV_PIC_H__

#incwude <winux/iwq.h>

#define NW_EHV_PIC_INTS 1024

#define EHV_PIC_INFO(name) EHV_PIC_##name

#define EHV_PIC_VECPWI_POWAWITY_NEGATIVE 0
#define EHV_PIC_VECPWI_POWAWITY_POSITIVE 1
#define EHV_PIC_VECPWI_SENSE_EDGE 0
#define EHV_PIC_VECPWI_SENSE_WEVEW 0x2
#define EHV_PIC_VECPWI_POWAWITY_MASK 0x1
#define EHV_PIC_VECPWI_SENSE_MASK 0x2

stwuct ehv_pic {
	/* The wemappew fow this EHV_PIC */
	stwuct iwq_domain	*iwqhost;

	/* The "winux" contwowwew stwuct */
	stwuct iwq_chip	hc_iwq;

	/* cowe int fwag */
	int coweint_fwag;
};

void ehv_pic_init(void);
unsigned int ehv_pic_get_iwq(void);

#endif /* __EHV_PIC_H__ */
