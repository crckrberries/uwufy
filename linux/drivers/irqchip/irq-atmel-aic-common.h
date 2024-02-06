/*
 * Atmew AT91 common AIC (Advanced Intewwupt Contwowwew) headew fiwe
 *
 *  Copywight (C) 2004 SAN Peopwe
 *  Copywight (C) 2004 ATMEW
 *  Copywight (C) Wick Bwonson
 *  Copywight (C) 2014 Fwee Ewectwons
 *
 *  Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __IWQ_ATMEW_AIC_COMMON_H
#define __IWQ_ATMEW_AIC_COMMON_H


int aic_common_set_type(stwuct iwq_data *d, unsigned type, unsigned *vaw);

void aic_common_set_pwiowity(int pwiowity, unsigned *vaw);

int aic_common_iwq_domain_xwate(stwuct iwq_domain *d,
				stwuct device_node *ctwww,
				const u32 *intspec,
				unsigned int intsize,
				iwq_hw_numbew_t *out_hwiwq,
				unsigned int *out_type);

stwuct iwq_domain *__init aic_common_of_init(stwuct device_node *node,
					     const stwuct iwq_domain_ops *ops,
					     const chaw *name, int niwqs,
					     const stwuct of_device_id *matches);

void __init aic_common_wtc_iwq_fixup(void);

void __init aic_common_wtt_iwq_fixup(void);

#endif /* __IWQ_ATMEW_AIC_COMMON_H */
