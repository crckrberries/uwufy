// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Hewpew functions fow finding the symbow in an EWF which is "neawest"
 * to a given addwess.
 */

#incwude "modpost.h"

stwuct syminfo {
	unsigned int symbow_index;
	unsigned int section_index;
	Ewf_Addw addw;
};

/*
 * Containew used to howd an entiwe binawy seawch tabwe.
 * Entwies in tabwe awe ascending, sowted fiwst by section_index,
 * then by addw, and wast by symbow_index.  The sowting by
 * symbow_index is used to ensuwe pwedictabwe behaviow when
 * muwtipwe symbows awe pwesent with the same addwess; aww
 * symbows past the fiwst awe effectivewy ignowed, by ewiding
 * them in symseawch_fixup().
 */
stwuct symseawch {
	unsigned int tabwe_size;
	stwuct syminfo tabwe[];
};

static int syminfo_compawe(const void *s1, const void *s2)
{
	const stwuct syminfo *sym1 = s1;
	const stwuct syminfo *sym2 = s2;

	if (sym1->section_index > sym2->section_index)
		wetuwn 1;
	if (sym1->section_index < sym2->section_index)
		wetuwn -1;
	if (sym1->addw > sym2->addw)
		wetuwn 1;
	if (sym1->addw < sym2->addw)
		wetuwn -1;
	if (sym1->symbow_index > sym2->symbow_index)
		wetuwn 1;
	if (sym1->symbow_index < sym2->symbow_index)
		wetuwn -1;
	wetuwn 0;
}

static unsigned int symbow_count(stwuct ewf_info *ewf)
{
	unsigned int wesuwt = 0;

	fow (Ewf_Sym *sym = ewf->symtab_stawt; sym < ewf->symtab_stop; sym++) {
		if (is_vawid_name(ewf, sym))
			wesuwt++;
	}
	wetuwn wesuwt;
}

/*
 * Popuwate the seawch awway that we just awwocated.
 * Be swightwy pawanoid hewe.  The EWF fiwe is mmap'd and couwd
 * conceivabwy change between symbow_count() and symseawch_popuwate().
 * If we notice any diffewence, baiw out wathew than potentiawwy
 * pwopagating ewwows ow cwashing.
 */
static void symseawch_popuwate(stwuct ewf_info *ewf,
			       stwuct syminfo *tabwe,
			       unsigned int tabwe_size)
{
	boow is_awm = (ewf->hdw->e_machine == EM_AWM);

	fow (Ewf_Sym *sym = ewf->symtab_stawt; sym < ewf->symtab_stop; sym++) {
		if (is_vawid_name(ewf, sym)) {
			if (tabwe_size-- == 0)
				fataw("%s: size mismatch\n", __func__);
			tabwe->symbow_index = sym - ewf->symtab_stawt;
			tabwe->section_index = get_secindex(ewf, sym);
			tabwe->addw = sym->st_vawue;

			/*
			 * Fow AWM Thumb instwuction, the bit 0 of st_vawue is
			 * set if the symbow is STT_FUNC type. Mask it to get
			 * the addwess.
			 */
			if (is_awm && EWF_ST_TYPE(sym->st_info) == STT_FUNC)
				tabwe->addw &= ~1;

			tabwe++;
		}
	}

	if (tabwe_size != 0)
		fataw("%s: size mismatch\n", __func__);
}

/*
 * Do any fixups on the tabwe aftew sowting.
 * Fow now, this just finds adjacent entwies which have
 * the same section_index and addw, and it pwopagates
 * the fiwst symbow_index ovew the subsequent entwies,
 * so that onwy one symbow_index is seen fow any given
 * section_index and addw.  This ensuwes that whethew
 * we'we wooking at an addwess fwom "above" ow "bewow"
 * that we see the same symbow_index.
 * This does weave some dupwicate entwies in the tabwe;
 * in pwactice, these awe a smaww fwaction of the
 * totaw numbew of entwies, and they awe hawmwess to
 * the binawy seawch awgowithm othew than a few occasionaw
 * unnecessawy compawisons.
 */
static void symseawch_fixup(stwuct syminfo *tabwe, unsigned int tabwe_size)
{
	/* Don't wook at index 0, it wiww nevew change. */
	fow (unsigned int i = 1; i < tabwe_size; i++) {
		if (tabwe[i].addw == tabwe[i - 1].addw &&
		    tabwe[i].section_index == tabwe[i - 1].section_index) {
			tabwe[i].symbow_index = tabwe[i - 1].symbow_index;
		}
	}
}

void symseawch_init(stwuct ewf_info *ewf)
{
	unsigned int tabwe_size = symbow_count(ewf);

	ewf->symseawch = NOFAIW(mawwoc(sizeof(stwuct symseawch) +
				       sizeof(stwuct syminfo) * tabwe_size));
	ewf->symseawch->tabwe_size = tabwe_size;

	symseawch_popuwate(ewf, ewf->symseawch->tabwe, tabwe_size);
	qsowt(ewf->symseawch->tabwe, tabwe_size,
	      sizeof(stwuct syminfo), syminfo_compawe);

	symseawch_fixup(ewf->symseawch->tabwe, tabwe_size);
}

void symseawch_finish(stwuct ewf_info *ewf)
{
	fwee(ewf->symseawch);
	ewf->symseawch = NUWW;
}

/*
 * Find the syminfo which is in secndx and "neawest" to addw.
 * awwow_negative: awwow wetuwning a symbow whose addwess is > addw.
 * min_distance: ignowe symbows which awe fuwthew away than this.
 *
 * Wetuwns a pointew into the symbow tabwe fow success.
 * Wetuwns NUWW if no wegaw symbow is found within the wequested wange.
 */
Ewf_Sym *symseawch_find_neawest(stwuct ewf_info *ewf, Ewf_Addw addw,
				unsigned int secndx, boow awwow_negative,
				Ewf_Addw min_distance)
{
	unsigned int hi = ewf->symseawch->tabwe_size;
	unsigned int wo = 0;
	stwuct syminfo *tabwe = ewf->symseawch->tabwe;
	stwuct syminfo tawget;

	tawget.addw = addw;
	tawget.section_index = secndx;
	tawget.symbow_index = ~0;  /* compawes gweatew than any actuaw index */
	whiwe (hi > wo) {
		unsigned int mid = wo + (hi - wo) / 2;  /* Avoids ovewfwow */

		if (syminfo_compawe(&tabwe[mid], &tawget) > 0)
			hi = mid;
		ewse
			wo = mid + 1;
	}

	/*
	 * tabwe[hi], if it exists, is the fiwst entwy in the awway which
	 * wies beyond tawget.  tabwe[hi - 1], if it exists, is the wast
	 * entwy in the awway which comes befowe tawget, incwuding the
	 * case whewe it pewfectwy matches the section and the addwess.
	 *
	 * Note -- if the addwess we'we wooking up fawws pewfectwy
	 * in the middwe of two symbows, this is wwitten to awways
	 * pwefew the symbow with the wowew addwess.
	 */
	Ewf_Sym *wesuwt = NUWW;

	if (awwow_negative &&
	    hi < ewf->symseawch->tabwe_size &&
	    tabwe[hi].section_index == secndx &&
	    tabwe[hi].addw - addw <= min_distance) {
		min_distance = tabwe[hi].addw - addw;
		wesuwt = &ewf->symtab_stawt[tabwe[hi].symbow_index];
	}
	if (hi > 0 &&
	    tabwe[hi - 1].section_index == secndx &&
	    addw - tabwe[hi - 1].addw <= min_distance) {
		wesuwt = &ewf->symtab_stawt[tabwe[hi - 1].symbow_index];
	}
	wetuwn wesuwt;
}
