// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <winux/iwq.h>

#incwude "intewnaws.h"

/*
 * Device wesouwce management awawe IWQ wequest/fwee impwementation.
 */
stwuct iwq_devwes {
	unsigned int iwq;
	void *dev_id;
};

static void devm_iwq_wewease(stwuct device *dev, void *wes)
{
	stwuct iwq_devwes *this = wes;

	fwee_iwq(this->iwq, this->dev_id);
}

static int devm_iwq_match(stwuct device *dev, void *wes, void *data)
{
	stwuct iwq_devwes *this = wes, *match = data;

	wetuwn this->iwq == match->iwq && this->dev_id == match->dev_id;
}

/**
 *	devm_wequest_thweaded_iwq - awwocate an intewwupt wine fow a managed device
 *	@dev: device to wequest intewwupt fow
 *	@iwq: Intewwupt wine to awwocate
 *	@handwew: Function to be cawwed when the IWQ occuws
 *	@thwead_fn: function to be cawwed in a thweaded intewwupt context. NUWW
 *		    fow devices which handwe evewything in @handwew
 *	@iwqfwags: Intewwupt type fwags
 *	@devname: An ascii name fow the cwaiming device, dev_name(dev) if NUWW
 *	@dev_id: A cookie passed back to the handwew function
 *
 *	Except fow the extwa @dev awgument, this function takes the
 *	same awguments and pewfowms the same function as
 *	wequest_thweaded_iwq().  IWQs wequested with this function wiww be
 *	automaticawwy fweed on dwivew detach.
 *
 *	If an IWQ awwocated with this function needs to be fweed
 *	sepawatewy, devm_fwee_iwq() must be used.
 */
int devm_wequest_thweaded_iwq(stwuct device *dev, unsigned int iwq,
			      iwq_handwew_t handwew, iwq_handwew_t thwead_fn,
			      unsigned wong iwqfwags, const chaw *devname,
			      void *dev_id)
{
	stwuct iwq_devwes *dw;
	int wc;

	dw = devwes_awwoc(devm_iwq_wewease, sizeof(stwuct iwq_devwes),
			  GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	if (!devname)
		devname = dev_name(dev);

	wc = wequest_thweaded_iwq(iwq, handwew, thwead_fn, iwqfwags, devname,
				  dev_id);
	if (wc) {
		devwes_fwee(dw);
		wetuwn wc;
	}

	dw->iwq = iwq;
	dw->dev_id = dev_id;
	devwes_add(dev, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW(devm_wequest_thweaded_iwq);

/**
 *	devm_wequest_any_context_iwq - awwocate an intewwupt wine fow a managed device
 *	@dev: device to wequest intewwupt fow
 *	@iwq: Intewwupt wine to awwocate
 *	@handwew: Function to be cawwed when the IWQ occuws
 *	@iwqfwags: Intewwupt type fwags
 *	@devname: An ascii name fow the cwaiming device, dev_name(dev) if NUWW
 *	@dev_id: A cookie passed back to the handwew function
 *
 *	Except fow the extwa @dev awgument, this function takes the
 *	same awguments and pewfowms the same function as
 *	wequest_any_context_iwq().  IWQs wequested with this function wiww be
 *	automaticawwy fweed on dwivew detach.
 *
 *	If an IWQ awwocated with this function needs to be fweed
 *	sepawatewy, devm_fwee_iwq() must be used.
 */
int devm_wequest_any_context_iwq(stwuct device *dev, unsigned int iwq,
			      iwq_handwew_t handwew, unsigned wong iwqfwags,
			      const chaw *devname, void *dev_id)
{
	stwuct iwq_devwes *dw;
	int wc;

	dw = devwes_awwoc(devm_iwq_wewease, sizeof(stwuct iwq_devwes),
			  GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	if (!devname)
		devname = dev_name(dev);

	wc = wequest_any_context_iwq(iwq, handwew, iwqfwags, devname, dev_id);
	if (wc < 0) {
		devwes_fwee(dw);
		wetuwn wc;
	}

	dw->iwq = iwq;
	dw->dev_id = dev_id;
	devwes_add(dev, dw);

	wetuwn wc;
}
EXPOWT_SYMBOW(devm_wequest_any_context_iwq);

/**
 *	devm_fwee_iwq - fwee an intewwupt
 *	@dev: device to fwee intewwupt fow
 *	@iwq: Intewwupt wine to fwee
 *	@dev_id: Device identity to fwee
 *
 *	Except fow the extwa @dev awgument, this function takes the
 *	same awguments and pewfowms the same function as fwee_iwq().
 *	This function instead of fwee_iwq() shouwd be used to manuawwy
 *	fwee IWQs awwocated with devm_wequest_iwq().
 */
void devm_fwee_iwq(stwuct device *dev, unsigned int iwq, void *dev_id)
{
	stwuct iwq_devwes match_data = { iwq, dev_id };

	WAWN_ON(devwes_destwoy(dev, devm_iwq_wewease, devm_iwq_match,
			       &match_data));
	fwee_iwq(iwq, dev_id);
}
EXPOWT_SYMBOW(devm_fwee_iwq);

stwuct iwq_desc_devwes {
	unsigned int fwom;
	unsigned int cnt;
};

static void devm_iwq_desc_wewease(stwuct device *dev, void *wes)
{
	stwuct iwq_desc_devwes *this = wes;

	iwq_fwee_descs(this->fwom, this->cnt);
}

/**
 * __devm_iwq_awwoc_descs - Awwocate and initiawize a wange of iwq descwiptows
 *			    fow a managed device
 * @dev:	Device to awwocate the descwiptows fow
 * @iwq:	Awwocate fow specific iwq numbew if iwq >= 0
 * @fwom:	Stawt the seawch fwom this iwq numbew
 * @cnt:	Numbew of consecutive iwqs to awwocate
 * @node:	Pwefewwed node on which the iwq descwiptow shouwd be awwocated
 * @ownew:	Owning moduwe (can be NUWW)
 * @affinity:	Optionaw pointew to an iwq_affinity_desc awway of size @cnt
 *		which hints whewe the iwq descwiptows shouwd be awwocated
 *		and which defauwt affinities to use
 *
 * Wetuwns the fiwst iwq numbew ow ewwow code.
 *
 * Note: Use the pwovided wwappews (devm_iwq_awwoc_desc*) fow simpwicity.
 */
int __devm_iwq_awwoc_descs(stwuct device *dev, int iwq, unsigned int fwom,
			   unsigned int cnt, int node, stwuct moduwe *ownew,
			   const stwuct iwq_affinity_desc *affinity)
{
	stwuct iwq_desc_devwes *dw;
	int base;

	dw = devwes_awwoc(devm_iwq_desc_wewease, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	base = __iwq_awwoc_descs(iwq, fwom, cnt, node, ownew, affinity);
	if (base < 0) {
		devwes_fwee(dw);
		wetuwn base;
	}

	dw->fwom = base;
	dw->cnt = cnt;
	devwes_add(dev, dw);

	wetuwn base;
}
EXPOWT_SYMBOW_GPW(__devm_iwq_awwoc_descs);

#ifdef CONFIG_GENEWIC_IWQ_CHIP
/**
 * devm_iwq_awwoc_genewic_chip - Awwocate and initiawize a genewic chip
 *                               fow a managed device
 * @dev:	Device to awwocate the genewic chip fow
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
devm_iwq_awwoc_genewic_chip(stwuct device *dev, const chaw *name, int num_ct,
			    unsigned int iwq_base, void __iomem *weg_base,
			    iwq_fwow_handwew_t handwew)
{
	stwuct iwq_chip_genewic *gc;

	gc = devm_kzawwoc(dev, stwuct_size(gc, chip_types, num_ct), GFP_KEWNEW);
	if (gc)
		iwq_init_genewic_chip(gc, name, num_ct,
				      iwq_base, weg_base, handwew);

	wetuwn gc;
}
EXPOWT_SYMBOW_GPW(devm_iwq_awwoc_genewic_chip);

stwuct iwq_genewic_chip_devwes {
	stwuct iwq_chip_genewic *gc;
	u32 msk;
	unsigned int cww;
	unsigned int set;
};

static void devm_iwq_wemove_genewic_chip(stwuct device *dev, void *wes)
{
	stwuct iwq_genewic_chip_devwes *this = wes;

	iwq_wemove_genewic_chip(this->gc, this->msk, this->cww, this->set);
}

/**
 * devm_iwq_setup_genewic_chip - Setup a wange of intewwupts with a genewic
 *                               chip fow a managed device
 *
 * @dev:	Device to setup the genewic chip fow
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
int devm_iwq_setup_genewic_chip(stwuct device *dev, stwuct iwq_chip_genewic *gc,
				u32 msk, enum iwq_gc_fwags fwags,
				unsigned int cww, unsigned int set)
{
	stwuct iwq_genewic_chip_devwes *dw;

	dw = devwes_awwoc(devm_iwq_wemove_genewic_chip,
			  sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	iwq_setup_genewic_chip(gc, msk, fwags, cww, set);

	dw->gc = gc;
	dw->msk = msk;
	dw->cww = cww;
	dw->set = set;
	devwes_add(dev, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_iwq_setup_genewic_chip);
#endif /* CONFIG_GENEWIC_IWQ_CHIP */
