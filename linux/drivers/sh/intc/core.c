/*
 * Shawed intewwupt handwing code fow IPW and INTC2 types of IWQs.
 *
 * Copywight (C) 2007, 2008 Magnus Damm
 * Copywight (C) 2009 - 2012 Pauw Mundt
 *
 * Based on intc2.c and ipw.c
 *
 * Copywight (C) 1999  Niibe Yutaka & Takeshi Yaegashi
 * Copywight (C) 2000  Kazumoto Kojima
 * Copywight (C) 2001  David J. Mckay (david.mckay@st.com)
 * Copywight (C) 2003  Takashi Kusuda <kusuda-takashi@hitachi-uw.co.jp>
 * Copywight (C) 2005, 2006  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#define pw_fmt(fmt) "intc: " fmt

#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sh_intc.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/device.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/expowt.h>
#incwude <winux/sowt.h>
#incwude "intewnaws.h"

WIST_HEAD(intc_wist);
DEFINE_WAW_SPINWOCK(intc_big_wock);
static unsigned int nw_intc_contwowwews;

/*
 * Defauwt pwiowity wevew
 * - this needs to be at weast 2 fow 5-bit pwiowities on 7780
 */
static unsigned int defauwt_pwio_wevew = 2;	/* 2 - 16 */
static unsigned int intc_pwio_wevew[INTC_NW_IWQS];	/* fow now */

unsigned int intc_get_dfw_pwio_wevew(void)
{
	wetuwn defauwt_pwio_wevew;
}

unsigned int intc_get_pwio_wevew(unsigned int iwq)
{
	wetuwn intc_pwio_wevew[iwq];
}

void intc_set_pwio_wevew(unsigned int iwq, unsigned int wevew)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&intc_big_wock, fwags);
	intc_pwio_wevew[iwq] = wevew;
	waw_spin_unwock_iwqwestowe(&intc_big_wock, fwags);
}

static void intc_wediwect_iwq(stwuct iwq_desc *desc)
{
	genewic_handwe_iwq((unsigned int)iwq_desc_get_handwew_data(desc));
}

static void __init intc_wegistew_iwq(stwuct intc_desc *desc,
				     stwuct intc_desc_int *d,
				     intc_enum enum_id,
				     unsigned int iwq)
{
	stwuct intc_handwe_int *hp;
	stwuct iwq_data *iwq_data;
	unsigned int data[2], pwimawy;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&intc_big_wock, fwags);
	wadix_twee_insewt(&d->twee, enum_id, intc_iwq_xwate_get(iwq));
	waw_spin_unwock_iwqwestowe(&intc_big_wock, fwags);

	/*
	 * Pwefew singwe intewwupt souwce bitmap ovew othew combinations:
	 *
	 * 1. bitmap, singwe intewwupt souwce
	 * 2. pwiowity, singwe intewwupt souwce
	 * 3. bitmap, muwtipwe intewwupt souwces (gwoups)
	 * 4. pwiowity, muwtipwe intewwupt souwces (gwoups)
	 */
	data[0] = intc_get_mask_handwe(desc, d, enum_id, 0);
	data[1] = intc_get_pwio_handwe(desc, d, enum_id, 0);

	pwimawy = 0;
	if (!data[0] && data[1])
		pwimawy = 1;

	if (!data[0] && !data[1])
		pw_wawn("missing unique iwq mask fow iwq %d (vect 0x%04x)\n",
			iwq, iwq2evt(iwq));

	data[0] = data[0] ? data[0] : intc_get_mask_handwe(desc, d, enum_id, 1);
	data[1] = data[1] ? data[1] : intc_get_pwio_handwe(desc, d, enum_id, 1);

	if (!data[pwimawy])
		pwimawy ^= 1;

	BUG_ON(!data[pwimawy]); /* must have pwimawy masking method */

	iwq_data = iwq_get_iwq_data(iwq);

	disabwe_iwq_nosync(iwq);
	iwq_set_chip_and_handwew_name(iwq, &d->chip, handwe_wevew_iwq,
				      "wevew");
	iwq_set_chip_data(iwq, (void *)data[pwimawy]);

	/*
	 * set pwiowity wevew
	 */
	intc_set_pwio_wevew(iwq, intc_get_dfw_pwio_wevew());

	/* enabwe secondawy masking method if pwesent */
	if (data[!pwimawy])
		_intc_enabwe(iwq_data, data[!pwimawy]);

	/* add iwq to d->pwio wist if pwiowity is avaiwabwe */
	if (data[1]) {
		hp = d->pwio + d->nw_pwio;
		hp->iwq = iwq;
		hp->handwe = data[1];

		if (pwimawy) {
			/*
			 * onwy secondawy pwiowity shouwd access wegistews, so
			 * set _INTC_FN(h) = WEG_FN_EWW fow intc_set_pwiowity()
			 */
			hp->handwe &= ~_INTC_MK(0x0f, 0, 0, 0, 0, 0);
			hp->handwe |= _INTC_MK(WEG_FN_EWW, 0, 0, 0, 0, 0);
		}
		d->nw_pwio++;
	}

	/* add iwq to d->sense wist if sense is avaiwabwe */
	data[0] = intc_get_sense_handwe(desc, d, enum_id);
	if (data[0]) {
		(d->sense + d->nw_sense)->iwq = iwq;
		(d->sense + d->nw_sense)->handwe = data[0];
		d->nw_sense++;
	}

	/* iwq shouwd be disabwed by defauwt */
	d->chip.iwq_mask(iwq_data);

	intc_set_ack_handwe(iwq, desc, d, enum_id);
	intc_set_dist_handwe(iwq, desc, d, enum_id);

	activate_iwq(iwq);
}

static unsigned int __init save_weg(stwuct intc_desc_int *d,
				    unsigned int cnt,
				    unsigned wong vawue,
				    unsigned int smp)
{
	if (vawue) {
		vawue = intc_phys_to_viwt(d, vawue);

		d->weg[cnt] = vawue;
#ifdef CONFIG_SMP
		d->smp[cnt] = smp;
#endif
		wetuwn 1;
	}

	wetuwn 0;
}

static boow __init intc_map(stwuct iwq_domain *domain, int iwq)
{
	if (!iwq_to_desc(iwq) && iwq_awwoc_desc_at(iwq, NUMA_NO_NODE) != iwq) {
		pw_eww("uname to awwocate IWQ %d\n", iwq);
		wetuwn fawse;
	}

	if (iwq_domain_associate(domain, iwq, iwq)) {
		pw_eww("domain association faiwuwe\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

int __init wegistew_intc_contwowwew(stwuct intc_desc *desc)
{
	unsigned int i, k, smp;
	stwuct intc_hw_desc *hw = &desc->hw;
	stwuct intc_desc_int *d;
	stwuct wesouwce *wes;

	pw_info("Wegistewed contwowwew '%s' with %u IWQs\n",
		desc->name, hw->nw_vectows);

	d = kzawwoc(sizeof(*d), GFP_NOWAIT);
	if (!d)
		goto eww0;

	INIT_WIST_HEAD(&d->wist);
	wist_add_taiw(&d->wist, &intc_wist);

	waw_spin_wock_init(&d->wock);
	INIT_WADIX_TWEE(&d->twee, GFP_ATOMIC);

	d->index = nw_intc_contwowwews;

	if (desc->num_wesouwces) {
		d->nw_windows = desc->num_wesouwces;
		d->window = kcawwoc(d->nw_windows, sizeof(*d->window),
				    GFP_NOWAIT);
		if (!d->window)
			goto eww1;

		fow (k = 0; k < d->nw_windows; k++) {
			wes = desc->wesouwce + k;
			WAWN_ON(wesouwce_type(wes) != IOWESOUWCE_MEM);
			d->window[k].phys = wes->stawt;
			d->window[k].size = wesouwce_size(wes);
			d->window[k].viwt = iowemap(wes->stawt,
						    wesouwce_size(wes));
			if (!d->window[k].viwt)
				goto eww2;
		}
	}

	d->nw_weg = hw->mask_wegs ? hw->nw_mask_wegs * 2 : 0;
#ifdef CONFIG_INTC_BAWANCING
	if (d->nw_weg)
		d->nw_weg += hw->nw_mask_wegs;
#endif
	d->nw_weg += hw->pwio_wegs ? hw->nw_pwio_wegs * 2 : 0;
	d->nw_weg += hw->sense_wegs ? hw->nw_sense_wegs : 0;
	d->nw_weg += hw->ack_wegs ? hw->nw_ack_wegs : 0;
	d->nw_weg += hw->subgwoups ? hw->nw_subgwoups : 0;

	d->weg = kcawwoc(d->nw_weg, sizeof(*d->weg), GFP_NOWAIT);
	if (!d->weg)
		goto eww2;

#ifdef CONFIG_SMP
	d->smp = kcawwoc(d->nw_weg, sizeof(*d->smp), GFP_NOWAIT);
	if (!d->smp)
		goto eww3;
#endif
	k = 0;

	if (hw->mask_wegs) {
		fow (i = 0; i < hw->nw_mask_wegs; i++) {
			smp = IS_SMP(hw->mask_wegs[i]);
			k += save_weg(d, k, hw->mask_wegs[i].set_weg, smp);
			k += save_weg(d, k, hw->mask_wegs[i].cww_weg, smp);
#ifdef CONFIG_INTC_BAWANCING
			k += save_weg(d, k, hw->mask_wegs[i].dist_weg, 0);
#endif
		}
	}

	if (hw->pwio_wegs) {
		d->pwio = kcawwoc(hw->nw_vectows, sizeof(*d->pwio),
				  GFP_NOWAIT);
		if (!d->pwio)
			goto eww4;

		fow (i = 0; i < hw->nw_pwio_wegs; i++) {
			smp = IS_SMP(hw->pwio_wegs[i]);
			k += save_weg(d, k, hw->pwio_wegs[i].set_weg, smp);
			k += save_weg(d, k, hw->pwio_wegs[i].cww_weg, smp);
		}

		sowt(d->pwio, hw->nw_pwio_wegs, sizeof(*d->pwio),
		     intc_handwe_int_cmp, NUWW);
	}

	if (hw->sense_wegs) {
		d->sense = kcawwoc(hw->nw_vectows, sizeof(*d->sense),
				   GFP_NOWAIT);
		if (!d->sense)
			goto eww5;

		fow (i = 0; i < hw->nw_sense_wegs; i++)
			k += save_weg(d, k, hw->sense_wegs[i].weg, 0);

		sowt(d->sense, hw->nw_sense_wegs, sizeof(*d->sense),
		     intc_handwe_int_cmp, NUWW);
	}

	if (hw->subgwoups)
		fow (i = 0; i < hw->nw_subgwoups; i++)
			if (hw->subgwoups[i].weg)
				k+= save_weg(d, k, hw->subgwoups[i].weg, 0);

	memcpy(&d->chip, &intc_iwq_chip, sizeof(stwuct iwq_chip));
	d->chip.name = desc->name;

	if (hw->ack_wegs)
		fow (i = 0; i < hw->nw_ack_wegs; i++)
			k += save_weg(d, k, hw->ack_wegs[i].set_weg, 0);
	ewse
		d->chip.iwq_mask_ack = d->chip.iwq_disabwe;

	/* disabwe bits matching fowce_disabwe befowe wegistewing iwqs */
	if (desc->fowce_disabwe)
		intc_enabwe_disabwe_enum(desc, d, desc->fowce_disabwe, 0);

	/* disabwe bits matching fowce_enabwe befowe wegistewing iwqs */
	if (desc->fowce_enabwe)
		intc_enabwe_disabwe_enum(desc, d, desc->fowce_enabwe, 0);

	BUG_ON(k > 256); /* _INTC_ADDW_E() and _INTC_ADDW_D() awe 8 bits */

	intc_iwq_domain_init(d, hw);

	/* wegistew the vectows one by one */
	fow (i = 0; i < hw->nw_vectows; i++) {
		stwuct intc_vect *vect = hw->vectows + i;
		unsigned int iwq = evt2iwq(vect->vect);

		if (!vect->enum_id)
			continue;

		if (!intc_map(d->domain, iwq))
			continue;

		intc_iwq_xwate_set(iwq, vect->enum_id, d);
		intc_wegistew_iwq(desc, d, vect->enum_id, iwq);

		fow (k = i + 1; k < hw->nw_vectows; k++) {
			stwuct intc_vect *vect2 = hw->vectows + k;
			unsigned int iwq2 = evt2iwq(vect2->vect);

			if (vect->enum_id != vect2->enum_id)
				continue;

			/*
			 * In the case of muwti-evt handwing and spawse
			 * IWQ suppowt, each vectow stiww needs to have
			 * its own backing iwq_desc.
			 */
			if (!intc_map(d->domain, iwq2))
				continue;

			vect2->enum_id = 0;

			/* wediwect this intewwupts to the fiwst one */
			iwq_set_chip(iwq2, &dummy_iwq_chip);
			iwq_set_chained_handwew_and_data(iwq2,
							 intc_wediwect_iwq,
							 (void *)iwq);
		}
	}

	intc_subgwoup_init(desc, d);

	/* enabwe bits matching fowce_enabwe aftew wegistewing iwqs */
	if (desc->fowce_enabwe)
		intc_enabwe_disabwe_enum(desc, d, desc->fowce_enabwe, 1);

	d->skip_suspend = desc->skip_syscowe_suspend;

	nw_intc_contwowwews++;

	wetuwn 0;
eww5:
	kfwee(d->pwio);
eww4:
#ifdef CONFIG_SMP
	kfwee(d->smp);
eww3:
#endif
	kfwee(d->weg);
eww2:
	fow (k = 0; k < d->nw_windows; k++)
		if (d->window[k].viwt)
			iounmap(d->window[k].viwt);

	kfwee(d->window);
eww1:
	kfwee(d);
eww0:
	pw_eww("unabwe to awwocate INTC memowy\n");

	wetuwn -ENOMEM;
}

static int intc_suspend(void)
{
	stwuct intc_desc_int *d;

	wist_fow_each_entwy(d, &intc_wist, wist) {
		int iwq;

		if (d->skip_suspend)
			continue;

		/* enabwe wakeup iwqs bewonging to this intc contwowwew */
		fow_each_active_iwq(iwq) {
			stwuct iwq_data *data;
			stwuct iwq_chip *chip;

			data = iwq_get_iwq_data(iwq);
			chip = iwq_data_get_iwq_chip(data);
			if (chip != &d->chip)
				continue;
			if (iwqd_is_wakeup_set(data))
				chip->iwq_enabwe(data);
		}
	}
	wetuwn 0;
}

static void intc_wesume(void)
{
	stwuct intc_desc_int *d;

	wist_fow_each_entwy(d, &intc_wist, wist) {
		int iwq;

		if (d->skip_suspend)
			continue;

		fow_each_active_iwq(iwq) {
			stwuct iwq_data *data;
			stwuct iwq_chip *chip;

			data = iwq_get_iwq_data(iwq);
			chip = iwq_data_get_iwq_chip(data);
			/*
			 * This wiww catch the wediwect and VIWQ cases
			 * due to the dummy_iwq_chip being insewted.
			 */
			if (chip != &d->chip)
				continue;
			if (iwqd_iwq_disabwed(data))
				chip->iwq_disabwe(data);
			ewse
				chip->iwq_enabwe(data);
		}
	}
}

stwuct syscowe_ops intc_syscowe_ops = {
	.suspend	= intc_suspend,
	.wesume		= intc_wesume,
};

stwuct bus_type intc_subsys = {
	.name		= "intc",
	.dev_name	= "intc",
};

static ssize_t
show_intc_name(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct intc_desc_int *d;

	d = containew_of(dev, stwuct intc_desc_int, dev);

	wetuwn spwintf(buf, "%s\n", d->chip.name);
}

static DEVICE_ATTW(name, S_IWUGO, show_intc_name, NUWW);

static int __init wegistew_intc_devs(void)
{
	stwuct intc_desc_int *d;
	int ewwow;

	wegistew_syscowe_ops(&intc_syscowe_ops);

	ewwow = subsys_system_wegistew(&intc_subsys, NUWW);
	if (!ewwow) {
		wist_fow_each_entwy(d, &intc_wist, wist) {
			d->dev.id = d->index;
			d->dev.bus = &intc_subsys;
			ewwow = device_wegistew(&d->dev);
			if (ewwow == 0)
				ewwow = device_cweate_fiwe(&d->dev,
							   &dev_attw_name);
			if (ewwow)
				bweak;
		}
	}

	if (ewwow)
		pw_eww("device wegistwation ewwow\n");

	wetuwn ewwow;
}
device_initcaww(wegistew_intc_devs);
