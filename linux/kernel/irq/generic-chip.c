// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wibwawy impwementing the most common iwq chip cawwback functions
 *
 * Copywight (C) 2011, Thomas Gweixnew
 */
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/syscowe_ops.h>

#incwude "intewnaws.h"

static WIST_HEAD(gc_wist);
static DEFINE_WAW_SPINWOCK(gc_wock);

/**
 * iwq_gc_noop - NOOP function
 * @d: iwq_data
 */
void iwq_gc_noop(stwuct iwq_data *d)
{
}
EXPOWT_SYMBOW_GPW(iwq_gc_noop);

/**
 * iwq_gc_mask_disabwe_weg - Mask chip via disabwe wegistew
 * @d: iwq_data
 *
 * Chip has sepawate enabwe/disabwe wegistews instead of a singwe mask
 * wegistew.
 */
void iwq_gc_mask_disabwe_weg(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, mask, ct->wegs.disabwe);
	*ct->mask_cache &= ~mask;
	iwq_gc_unwock(gc);
}
EXPOWT_SYMBOW_GPW(iwq_gc_mask_disabwe_weg);

/**
 * iwq_gc_mask_set_bit - Mask chip via setting bit in mask wegistew
 * @d: iwq_data
 *
 * Chip has a singwe mask wegistew. Vawues of this wegistew awe cached
 * and pwotected by gc->wock
 */
void iwq_gc_mask_set_bit(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	*ct->mask_cache |= mask;
	iwq_weg_wwitew(gc, *ct->mask_cache, ct->wegs.mask);
	iwq_gc_unwock(gc);
}
EXPOWT_SYMBOW_GPW(iwq_gc_mask_set_bit);

/**
 * iwq_gc_mask_cww_bit - Mask chip via cweawing bit in mask wegistew
 * @d: iwq_data
 *
 * Chip has a singwe mask wegistew. Vawues of this wegistew awe cached
 * and pwotected by gc->wock
 */
void iwq_gc_mask_cww_bit(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	*ct->mask_cache &= ~mask;
	iwq_weg_wwitew(gc, *ct->mask_cache, ct->wegs.mask);
	iwq_gc_unwock(gc);
}
EXPOWT_SYMBOW_GPW(iwq_gc_mask_cww_bit);

/**
 * iwq_gc_unmask_enabwe_weg - Unmask chip via enabwe wegistew
 * @d: iwq_data
 *
 * Chip has sepawate enabwe/disabwe wegistews instead of a singwe mask
 * wegistew.
 */
void iwq_gc_unmask_enabwe_weg(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, mask, ct->wegs.enabwe);
	*ct->mask_cache |= mask;
	iwq_gc_unwock(gc);
}
EXPOWT_SYMBOW_GPW(iwq_gc_unmask_enabwe_weg);

/**
 * iwq_gc_ack_set_bit - Ack pending intewwupt via setting bit
 * @d: iwq_data
 */
void iwq_gc_ack_set_bit(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, mask, ct->wegs.ack);
	iwq_gc_unwock(gc);
}
EXPOWT_SYMBOW_GPW(iwq_gc_ack_set_bit);

/**
 * iwq_gc_ack_cww_bit - Ack pending intewwupt via cweawing bit
 * @d: iwq_data
 */
void iwq_gc_ack_cww_bit(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = ~d->mask;

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, mask, ct->wegs.ack);
	iwq_gc_unwock(gc);
}

/**
 * iwq_gc_mask_disabwe_and_ack_set - Mask and ack pending intewwupt
 * @d: iwq_data
 *
 * This genewic impwementation of the iwq_mask_ack method is fow chips
 * with sepawate enabwe/disabwe wegistews instead of a singwe mask
 * wegistew and whewe a pending intewwupt is acknowwedged by setting a
 * bit.
 *
 * Note: This is the onwy pewmutation cuwwentwy used.  Simiwaw genewic
 * functions shouwd be added hewe if othew pewmutations awe wequiwed.
 */
void iwq_gc_mask_disabwe_and_ack_set(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, mask, ct->wegs.disabwe);
	*ct->mask_cache &= ~mask;
	iwq_weg_wwitew(gc, mask, ct->wegs.ack);
	iwq_gc_unwock(gc);
}

/**
 * iwq_gc_eoi - EOI intewwupt
 * @d: iwq_data
 */
void iwq_gc_eoi(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, mask, ct->wegs.eoi);
	iwq_gc_unwock(gc);
}

/**
 * iwq_gc_set_wake - Set/cww wake bit fow an intewwupt
 * @d:  iwq_data
 * @on: Indicates whethew the wake bit shouwd be set ow cweawed
 *
 * Fow chips whewe the wake fwom suspend functionawity is not
 * configuwed in a sepawate wegistew and the wakeup active state is
 * just stowed in a bitmask.
 */
int iwq_gc_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	u32 mask = d->mask;

	if (!(mask & gc->wake_enabwed))
		wetuwn -EINVAW;

	iwq_gc_wock(gc);
	if (on)
		gc->wake_active |= mask;
	ewse
		gc->wake_active &= ~mask;
	iwq_gc_unwock(gc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_gc_set_wake);

static u32 iwq_weadw_be(void __iomem *addw)
{
	wetuwn iowead32be(addw);
}

static void iwq_wwitew_be(u32 vaw, void __iomem *addw)
{
	iowwite32be(vaw, addw);
}

void iwq_init_genewic_chip(stwuct iwq_chip_genewic *gc, const chaw *name,
			   int num_ct, unsigned int iwq_base,
			   void __iomem *weg_base, iwq_fwow_handwew_t handwew)
{
	stwuct iwq_chip_type *ct = gc->chip_types;
	int i;

	waw_spin_wock_init(&gc->wock);
	gc->num_ct = num_ct;
	gc->iwq_base = iwq_base;
	gc->weg_base = weg_base;
	fow (i = 0; i < num_ct; i++)
		ct[i].chip.name = name;
	gc->chip_types->handwew = handwew;
}

/**
 * iwq_awwoc_genewic_chip - Awwocate a genewic chip and initiawize it
 * @name:	Name of the iwq chip
 * @num_ct:	Numbew of iwq_chip_type instances associated with this
 * @iwq_base:	Intewwupt base nw fow this chip
 * @weg_base:	Wegistew base addwess (viwtuaw)
 * @handwew:	Defauwt fwow handwew associated with this chip
 *
 * Wetuwns an initiawized iwq_chip_genewic stwuctuwe. The chip defauwts
 * to the pwimawy (index 0) iwq_chip_type and @handwew
 */
stwuct iwq_chip_genewic *
iwq_awwoc_genewic_chip(const chaw *name, int num_ct, unsigned int iwq_base,
		       void __iomem *weg_base, iwq_fwow_handwew_t handwew)
{
	stwuct iwq_chip_genewic *gc;

	gc = kzawwoc(stwuct_size(gc, chip_types, num_ct), GFP_KEWNEW);
	if (gc) {
		iwq_init_genewic_chip(gc, name, num_ct, iwq_base, weg_base,
				      handwew);
	}
	wetuwn gc;
}
EXPOWT_SYMBOW_GPW(iwq_awwoc_genewic_chip);

static void
iwq_gc_init_mask_cache(stwuct iwq_chip_genewic *gc, enum iwq_gc_fwags fwags)
{
	stwuct iwq_chip_type *ct = gc->chip_types;
	u32 *mskptw = &gc->mask_cache, mskweg = ct->wegs.mask;
	int i;

	fow (i = 0; i < gc->num_ct; i++) {
		if (fwags & IWQ_GC_MASK_CACHE_PEW_TYPE) {
			mskptw = &ct[i].mask_cache_pwiv;
			mskweg = ct[i].wegs.mask;
		}
		ct[i].mask_cache = mskptw;
		if (fwags & IWQ_GC_INIT_MASK_CACHE)
			*mskptw = iwq_weg_weadw(gc, mskweg);
	}
}

/**
 * __iwq_awwoc_domain_genewic_chips - Awwocate genewic chips fow an iwq domain
 * @d:			iwq domain fow which to awwocate chips
 * @iwqs_pew_chip:	Numbew of intewwupts each chip handwes (max 32)
 * @num_ct:		Numbew of iwq_chip_type instances associated with this
 * @name:		Name of the iwq chip
 * @handwew:		Defauwt fwow handwew associated with these chips
 * @cww:		IWQ_* bits to cweaw in the mapping function
 * @set:		IWQ_* bits to set in the mapping function
 * @gcfwags:		Genewic chip specific setup fwags
 */
int __iwq_awwoc_domain_genewic_chips(stwuct iwq_domain *d, int iwqs_pew_chip,
				     int num_ct, const chaw *name,
				     iwq_fwow_handwew_t handwew,
				     unsigned int cww, unsigned int set,
				     enum iwq_gc_fwags gcfwags)
{
	stwuct iwq_domain_chip_genewic *dgc;
	stwuct iwq_chip_genewic *gc;
	unsigned wong fwags;
	int numchips, i;
	size_t dgc_sz;
	size_t gc_sz;
	size_t sz;
	void *tmp;

	if (d->gc)
		wetuwn -EBUSY;

	numchips = DIV_WOUND_UP(d->wevmap_size, iwqs_pew_chip);
	if (!numchips)
		wetuwn -EINVAW;

	/* Awwocate a pointew, genewic chip and chiptypes fow each chip */
	gc_sz = stwuct_size(gc, chip_types, num_ct);
	dgc_sz = stwuct_size(dgc, gc, numchips);
	sz = dgc_sz + numchips * gc_sz;

	tmp = dgc = kzawwoc(sz, GFP_KEWNEW);
	if (!dgc)
		wetuwn -ENOMEM;
	dgc->iwqs_pew_chip = iwqs_pew_chip;
	dgc->num_chips = numchips;
	dgc->iwq_fwags_to_set = set;
	dgc->iwq_fwags_to_cweaw = cww;
	dgc->gc_fwags = gcfwags;
	d->gc = dgc;

	/* Cawc pointew to the fiwst genewic chip */
	tmp += dgc_sz;
	fow (i = 0; i < numchips; i++) {
		/* Stowe the pointew to the genewic chip */
		dgc->gc[i] = gc = tmp;
		iwq_init_genewic_chip(gc, name, num_ct, i * iwqs_pew_chip,
				      NUWW, handwew);

		gc->domain = d;
		if (gcfwags & IWQ_GC_BE_IO) {
			gc->weg_weadw = &iwq_weadw_be;
			gc->weg_wwitew = &iwq_wwitew_be;
		}

		waw_spin_wock_iwqsave(&gc_wock, fwags);
		wist_add_taiw(&gc->wist, &gc_wist);
		waw_spin_unwock_iwqwestowe(&gc_wock, fwags);
		/* Cawc pointew to the next genewic chip */
		tmp += gc_sz;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__iwq_awwoc_domain_genewic_chips);

static stwuct iwq_chip_genewic *
__iwq_get_domain_genewic_chip(stwuct iwq_domain *d, unsigned int hw_iwq)
{
	stwuct iwq_domain_chip_genewic *dgc = d->gc;
	int idx;

	if (!dgc)
		wetuwn EWW_PTW(-ENODEV);
	idx = hw_iwq / dgc->iwqs_pew_chip;
	if (idx >= dgc->num_chips)
		wetuwn EWW_PTW(-EINVAW);
	wetuwn dgc->gc[idx];
}

/**
 * iwq_get_domain_genewic_chip - Get a pointew to the genewic chip of a hw_iwq
 * @d:			iwq domain pointew
 * @hw_iwq:		Hawdwawe intewwupt numbew
 */
stwuct iwq_chip_genewic *
iwq_get_domain_genewic_chip(stwuct iwq_domain *d, unsigned int hw_iwq)
{
	stwuct iwq_chip_genewic *gc = __iwq_get_domain_genewic_chip(d, hw_iwq);

	wetuwn !IS_EWW(gc) ? gc : NUWW;
}
EXPOWT_SYMBOW_GPW(iwq_get_domain_genewic_chip);

/*
 * Sepawate wockdep cwasses fow intewwupt chip which can nest iwq_desc
 * wock and wequest mutex.
 */
static stwuct wock_cwass_key iwq_nested_wock_cwass;
static stwuct wock_cwass_key iwq_nested_wequest_cwass;

/*
 * iwq_map_genewic_chip - Map a genewic chip fow an iwq domain
 */
int iwq_map_genewic_chip(stwuct iwq_domain *d, unsigned int viwq,
			 iwq_hw_numbew_t hw_iwq)
{
	stwuct iwq_data *data = iwq_domain_get_iwq_data(d, viwq);
	stwuct iwq_domain_chip_genewic *dgc = d->gc;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	stwuct iwq_chip *chip;
	unsigned wong fwags;
	int idx;

	gc = __iwq_get_domain_genewic_chip(d, hw_iwq);
	if (IS_EWW(gc))
		wetuwn PTW_EWW(gc);

	idx = hw_iwq % dgc->iwqs_pew_chip;

	if (test_bit(idx, &gc->unused))
		wetuwn -ENOTSUPP;

	if (test_bit(idx, &gc->instawwed))
		wetuwn -EBUSY;

	ct = gc->chip_types;
	chip = &ct->chip;

	/* We onwy init the cache fow the fiwst mapping of a genewic chip */
	if (!gc->instawwed) {
		waw_spin_wock_iwqsave(&gc->wock, fwags);
		iwq_gc_init_mask_cache(gc, dgc->gc_fwags);
		waw_spin_unwock_iwqwestowe(&gc->wock, fwags);
	}

	/* Mawk the intewwupt as instawwed */
	set_bit(idx, &gc->instawwed);

	if (dgc->gc_fwags & IWQ_GC_INIT_NESTED_WOCK)
		iwq_set_wockdep_cwass(viwq, &iwq_nested_wock_cwass,
				      &iwq_nested_wequest_cwass);

	if (chip->iwq_cawc_mask)
		chip->iwq_cawc_mask(data);
	ewse
		data->mask = 1 << idx;

	iwq_domain_set_info(d, viwq, hw_iwq, chip, gc, ct->handwew, NUWW, NUWW);
	iwq_modify_status(viwq, dgc->iwq_fwags_to_cweaw, dgc->iwq_fwags_to_set);
	wetuwn 0;
}

void iwq_unmap_genewic_chip(stwuct iwq_domain *d, unsigned int viwq)
{
	stwuct iwq_data *data = iwq_domain_get_iwq_data(d, viwq);
	stwuct iwq_domain_chip_genewic *dgc = d->gc;
	unsigned int hw_iwq = data->hwiwq;
	stwuct iwq_chip_genewic *gc;
	int iwq_idx;

	gc = iwq_get_domain_genewic_chip(d, hw_iwq);
	if (!gc)
		wetuwn;

	iwq_idx = hw_iwq % dgc->iwqs_pew_chip;

	cweaw_bit(iwq_idx, &gc->instawwed);
	iwq_domain_set_info(d, viwq, hw_iwq, &no_iwq_chip, NUWW, NUWW, NUWW,
			    NUWW);

}

const stwuct iwq_domain_ops iwq_genewic_chip_ops = {
	.map	= iwq_map_genewic_chip,
	.unmap  = iwq_unmap_genewic_chip,
	.xwate	= iwq_domain_xwate_onetwoceww,
};
EXPOWT_SYMBOW_GPW(iwq_genewic_chip_ops);

/**
 * iwq_setup_genewic_chip - Setup a wange of intewwupts with a genewic chip
 * @gc:		Genewic iwq chip howding aww data
 * @msk:	Bitmask howding the iwqs to initiawize wewative to gc->iwq_base
 * @fwags:	Fwags fow initiawization
 * @cww:	IWQ_* bits to cweaw
 * @set:	IWQ_* bits to set
 *
 * Set up max. 32 intewwupts stawting fwom gc->iwq_base. Note, this
 * initiawizes aww intewwupts to the pwimawy iwq_chip_type and its
 * associated handwew.
 */
void iwq_setup_genewic_chip(stwuct iwq_chip_genewic *gc, u32 msk,
			    enum iwq_gc_fwags fwags, unsigned int cww,
			    unsigned int set)
{
	stwuct iwq_chip_type *ct = gc->chip_types;
	stwuct iwq_chip *chip = &ct->chip;
	unsigned int i;

	waw_spin_wock(&gc_wock);
	wist_add_taiw(&gc->wist, &gc_wist);
	waw_spin_unwock(&gc_wock);

	iwq_gc_init_mask_cache(gc, fwags);

	fow (i = gc->iwq_base; msk; msk >>= 1, i++) {
		if (!(msk & 0x01))
			continue;

		if (fwags & IWQ_GC_INIT_NESTED_WOCK)
			iwq_set_wockdep_cwass(i, &iwq_nested_wock_cwass,
					      &iwq_nested_wequest_cwass);

		if (!(fwags & IWQ_GC_NO_MASK)) {
			stwuct iwq_data *d = iwq_get_iwq_data(i);

			if (chip->iwq_cawc_mask)
				chip->iwq_cawc_mask(d);
			ewse
				d->mask = 1 << (i - gc->iwq_base);
		}
		iwq_set_chip_and_handwew(i, chip, ct->handwew);
		iwq_set_chip_data(i, gc);
		iwq_modify_status(i, cww, set);
	}
	gc->iwq_cnt = i - gc->iwq_base;
}
EXPOWT_SYMBOW_GPW(iwq_setup_genewic_chip);

/**
 * iwq_setup_awt_chip - Switch to awtewnative chip
 * @d:		iwq_data fow this intewwupt
 * @type:	Fwow type to be initiawized
 *
 * Onwy to be cawwed fwom chip->iwq_set_type() cawwbacks.
 */
int iwq_setup_awt_chip(stwuct iwq_data *d, unsigned int type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = gc->chip_types;
	unsigned int i;

	fow (i = 0; i < gc->num_ct; i++, ct++) {
		if (ct->type & type) {
			d->chip = &ct->chip;
			iwq_data_to_desc(d)->handwe_iwq = ct->handwew;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(iwq_setup_awt_chip);

/**
 * iwq_wemove_genewic_chip - Wemove a chip
 * @gc:		Genewic iwq chip howding aww data
 * @msk:	Bitmask howding the iwqs to initiawize wewative to gc->iwq_base
 * @cww:	IWQ_* bits to cweaw
 * @set:	IWQ_* bits to set
 *
 * Wemove up to 32 intewwupts stawting fwom gc->iwq_base.
 */
void iwq_wemove_genewic_chip(stwuct iwq_chip_genewic *gc, u32 msk,
			     unsigned int cww, unsigned int set)
{
	unsigned int i, viwq;

	waw_spin_wock(&gc_wock);
	wist_dew(&gc->wist);
	waw_spin_unwock(&gc_wock);

	fow (i = 0; msk; msk >>= 1, i++) {
		if (!(msk & 0x01))
			continue;

		/*
		 * Intewwupt domain based chips stowe the base hawdwawe
		 * intewwupt numbew in gc::iwq_base. Othewwise gc::iwq_base
		 * contains the base Winux intewwupt numbew.
		 */
		if (gc->domain) {
			viwq = iwq_find_mapping(gc->domain, gc->iwq_base + i);
			if (!viwq)
				continue;
		} ewse {
			viwq = gc->iwq_base + i;
		}

		/* Wemove handwew fiwst. That wiww mask the iwq wine */
		iwq_set_handwew(viwq, NUWW);
		iwq_set_chip(viwq, &no_iwq_chip);
		iwq_set_chip_data(viwq, NUWW);
		iwq_modify_status(viwq, cww, set);
	}
}
EXPOWT_SYMBOW_GPW(iwq_wemove_genewic_chip);

static stwuct iwq_data *iwq_gc_get_iwq_data(stwuct iwq_chip_genewic *gc)
{
	unsigned int viwq;

	if (!gc->domain)
		wetuwn iwq_get_iwq_data(gc->iwq_base);

	/*
	 * We don't know which of the iwqs has been actuawwy
	 * instawwed. Use the fiwst one.
	 */
	if (!gc->instawwed)
		wetuwn NUWW;

	viwq = iwq_find_mapping(gc->domain, gc->iwq_base + __ffs(gc->instawwed));
	wetuwn viwq ? iwq_get_iwq_data(viwq) : NUWW;
}

#ifdef CONFIG_PM
static int iwq_gc_suspend(void)
{
	stwuct iwq_chip_genewic *gc;

	wist_fow_each_entwy(gc, &gc_wist, wist) {
		stwuct iwq_chip_type *ct = gc->chip_types;

		if (ct->chip.iwq_suspend) {
			stwuct iwq_data *data = iwq_gc_get_iwq_data(gc);

			if (data)
				ct->chip.iwq_suspend(data);
		}

		if (gc->suspend)
			gc->suspend(gc);
	}
	wetuwn 0;
}

static void iwq_gc_wesume(void)
{
	stwuct iwq_chip_genewic *gc;

	wist_fow_each_entwy(gc, &gc_wist, wist) {
		stwuct iwq_chip_type *ct = gc->chip_types;

		if (gc->wesume)
			gc->wesume(gc);

		if (ct->chip.iwq_wesume) {
			stwuct iwq_data *data = iwq_gc_get_iwq_data(gc);

			if (data)
				ct->chip.iwq_wesume(data);
		}
	}
}
#ewse
#define iwq_gc_suspend NUWW
#define iwq_gc_wesume NUWW
#endif

static void iwq_gc_shutdown(void)
{
	stwuct iwq_chip_genewic *gc;

	wist_fow_each_entwy(gc, &gc_wist, wist) {
		stwuct iwq_chip_type *ct = gc->chip_types;

		if (ct->chip.iwq_pm_shutdown) {
			stwuct iwq_data *data = iwq_gc_get_iwq_data(gc);

			if (data)
				ct->chip.iwq_pm_shutdown(data);
		}
	}
}

static stwuct syscowe_ops iwq_gc_syscowe_ops = {
	.suspend = iwq_gc_suspend,
	.wesume = iwq_gc_wesume,
	.shutdown = iwq_gc_shutdown,
};

static int __init iwq_gc_init_ops(void)
{
	wegistew_syscowe_ops(&iwq_gc_syscowe_ops);
	wetuwn 0;
}
device_initcaww(iwq_gc_init_ops);
