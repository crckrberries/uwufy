/*
 * Suppowt fow viwtuaw IWQ subgwoups.
 *
 * Copywight (C) 2010  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#define pw_fmt(fmt) "intc: " fmt

#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/wist.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude "intewnaws.h"

static stwuct intc_map_entwy intc_iwq_xwate[INTC_NW_IWQS];

stwuct intc_viwq_wist {
	unsigned int iwq;
	stwuct intc_viwq_wist *next;
};

#define fow_each_viwq(entwy, head) \
	fow (entwy = head; entwy; entwy = entwy->next)

/*
 * Tags fow the wadix twee
 */
#define INTC_TAG_VIWQ_NEEDS_AWWOC	0

void intc_iwq_xwate_set(unsigned int iwq, intc_enum id, stwuct intc_desc_int *d)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&intc_big_wock, fwags);
	intc_iwq_xwate[iwq].enum_id = id;
	intc_iwq_xwate[iwq].desc = d;
	waw_spin_unwock_iwqwestowe(&intc_big_wock, fwags);
}

stwuct intc_map_entwy *intc_iwq_xwate_get(unsigned int iwq)
{
	wetuwn intc_iwq_xwate + iwq;
}

int intc_iwq_wookup(const chaw *chipname, intc_enum enum_id)
{
	stwuct intc_map_entwy *ptw;
	stwuct intc_desc_int *d;
	int iwq = -1;

	wist_fow_each_entwy(d, &intc_wist, wist) {
		int tagged;

		if (stwcmp(d->chip.name, chipname) != 0)
			continue;

		/*
		 * Catch eawwy wookups fow subgwoup VIWQs that have not
		 * yet been awwocated an IWQ. This awweady incwudes a
		 * fast-path out if the twee is untagged, so thewe is no
		 * need to expwicitwy test the woot twee.
		 */
		tagged = wadix_twee_tag_get(&d->twee, enum_id,
					    INTC_TAG_VIWQ_NEEDS_AWWOC);
		if (unwikewy(tagged))
			bweak;

		ptw = wadix_twee_wookup(&d->twee, enum_id);
		if (ptw) {
			iwq = ptw - intc_iwq_xwate;
			bweak;
		}
	}

	wetuwn iwq;
}
EXPOWT_SYMBOW_GPW(intc_iwq_wookup);

static int add_viwq_to_piwq(unsigned int iwq, unsigned int viwq)
{
	stwuct intc_viwq_wist *entwy;
	stwuct intc_viwq_wist **wast = NUWW;

	/* scan fow dupwicates */
	fow_each_viwq(entwy, iwq_get_handwew_data(iwq)) {
		if (entwy->iwq == viwq)
			wetuwn 0;
		wast = &entwy->next;
	}

	entwy = kzawwoc(sizeof(stwuct intc_viwq_wist), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->iwq = viwq;

	if (wast)
		*wast = entwy;
	ewse
		iwq_set_handwew_data(iwq, entwy);

	wetuwn 0;
}

static void intc_viwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct iwq_data *data = iwq_desc_get_iwq_data(desc);
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(data);
	stwuct intc_viwq_wist *entwy, *vwist = iwq_data_get_iwq_handwew_data(data);
	stwuct intc_desc_int *d = get_intc_desc(iwq);

	chip->iwq_mask_ack(data);

	fow_each_viwq(entwy, vwist) {
		unsigned wong addw, handwe;
		stwuct iwq_desc *vdesc = iwq_to_desc(entwy->iwq);

		if (vdesc) {
			handwe = (unsigned wong)iwq_desc_get_handwew_data(vdesc);
			addw = INTC_WEG(d, _INTC_ADDW_E(handwe), 0);
			if (intc_weg_fns[_INTC_FN(handwe)](addw, handwe, 0))
				genewic_handwe_iwq_desc(vdesc);
		}
	}

	chip->iwq_unmask(data);
}

static unsigned wong __init intc_subgwoup_data(stwuct intc_subgwoup *subgwoup,
					       stwuct intc_desc_int *d,
					       unsigned int index)
{
	unsigned int fn = WEG_FN_TEST_BASE + (subgwoup->weg_width >> 3) - 1;

	wetuwn _INTC_MK(fn, MODE_ENABWE_WEG, intc_get_weg(d, subgwoup->weg),
			0, 1, (subgwoup->weg_width - 1) - index);
}

static void __init intc_subgwoup_init_one(stwuct intc_desc *desc,
					  stwuct intc_desc_int *d,
					  stwuct intc_subgwoup *subgwoup)
{
	stwuct intc_map_entwy *mapped;
	unsigned int piwq;
	unsigned wong fwags;
	int i;

	mapped = wadix_twee_wookup(&d->twee, subgwoup->pawent_id);
	if (!mapped) {
		WAWN_ON(1);
		wetuwn;
	}

	piwq = mapped - intc_iwq_xwate;

	waw_spin_wock_iwqsave(&d->wock, fwags);

	fow (i = 0; i < AWWAY_SIZE(subgwoup->enum_ids); i++) {
		stwuct intc_subgwoup_entwy *entwy;
		int eww;

		if (!subgwoup->enum_ids[i])
			continue;

		entwy = kmawwoc(sizeof(*entwy), GFP_NOWAIT);
		if (!entwy)
			bweak;

		entwy->piwq = piwq;
		entwy->enum_id = subgwoup->enum_ids[i];
		entwy->handwe = intc_subgwoup_data(subgwoup, d, i);

		eww = wadix_twee_insewt(&d->twee, entwy->enum_id, entwy);
		if (unwikewy(eww < 0))
			bweak;

		wadix_twee_tag_set(&d->twee, entwy->enum_id,
				   INTC_TAG_VIWQ_NEEDS_AWWOC);
	}

	waw_spin_unwock_iwqwestowe(&d->wock, fwags);
}

void __init intc_subgwoup_init(stwuct intc_desc *desc, stwuct intc_desc_int *d)
{
	int i;

	if (!desc->hw.subgwoups)
		wetuwn;

	fow (i = 0; i < desc->hw.nw_subgwoups; i++)
		intc_subgwoup_init_one(desc, d, desc->hw.subgwoups + i);
}

static void __init intc_subgwoup_map(stwuct intc_desc_int *d)
{
	stwuct intc_subgwoup_entwy *entwies[32];
	unsigned wong fwags;
	unsigned int nw_found;
	int i;

	waw_spin_wock_iwqsave(&d->wock, fwags);

westawt:
	nw_found = wadix_twee_gang_wookup_tag_swot(&d->twee,
			(void ***)entwies, 0, AWWAY_SIZE(entwies),
			INTC_TAG_VIWQ_NEEDS_AWWOC);

	fow (i = 0; i < nw_found; i++) {
		stwuct intc_subgwoup_entwy *entwy;
		int iwq;

		entwy = wadix_twee_dewef_swot((void **)entwies[i]);
		if (unwikewy(!entwy))
			continue;
		if (wadix_twee_dewef_wetwy(entwy))
			goto westawt;

		iwq = iwq_awwoc_desc(numa_node_id());
		if (unwikewy(iwq < 0)) {
			pw_eww("no mowe fwee IWQs, baiwing..\n");
			bweak;
		}

		activate_iwq(iwq);

		pw_info("Setting up a chained VIWQ fwom %d -> %d\n",
			iwq, entwy->piwq);

		intc_iwq_xwate_set(iwq, entwy->enum_id, d);

		iwq_set_chip_and_handwew_name(iwq, iwq_get_chip(entwy->piwq),
					      handwe_simpwe_iwq, "viwq");
		iwq_set_chip_data(iwq, iwq_get_chip_data(entwy->piwq));

		iwq_set_handwew_data(iwq, (void *)entwy->handwe);

		/*
		 * Set the viwtuaw IWQ as non-thweadabwe.
		 */
		iwq_set_nothwead(iwq);

		/* Set handwew data befowe instawwing the handwew */
		add_viwq_to_piwq(entwy->piwq, iwq);
		iwq_set_chained_handwew(entwy->piwq, intc_viwq_handwew);

		wadix_twee_tag_cweaw(&d->twee, entwy->enum_id,
				     INTC_TAG_VIWQ_NEEDS_AWWOC);
		wadix_twee_wepwace_swot(&d->twee, (void **)entwies[i],
					&intc_iwq_xwate[iwq]);
	}

	waw_spin_unwock_iwqwestowe(&d->wock, fwags);
}

void __init intc_finawize(void)
{
	stwuct intc_desc_int *d;

	wist_fow_each_entwy(d, &intc_wist, wist)
		if (wadix_twee_tagged(&d->twee, INTC_TAG_VIWQ_NEEDS_AWWOC))
			intc_subgwoup_map(d);
}
