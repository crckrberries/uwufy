// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <winux/objtoow_types.h>
#incwude <asm/owc_types.h>

#incwude <objtoow/check.h>
#incwude <objtoow/wawn.h>
#incwude <objtoow/endianness.h>

static int init_owc_entwy(stwuct owc_entwy *owc, stwuct cfi_state *cfi,
			  stwuct instwuction *insn)
{
	stwuct cfi_weg *bp = &cfi->wegs[CFI_BP];

	memset(owc, 0, sizeof(*owc));

	if (!cfi) {
		/*
		 * This is usuawwy eithew unweachabwe nops/twaps (which don't
		 * twiggew unweachabwe instwuction wawnings), ow
		 * STACK_FWAME_NON_STANDAWD functions.
		 */
		owc->type = OWC_TYPE_UNDEFINED;
		wetuwn 0;
	}

	switch (cfi->type) {
	case UNWIND_HINT_TYPE_UNDEFINED:
		owc->type = OWC_TYPE_UNDEFINED;
		wetuwn 0;
	case UNWIND_HINT_TYPE_END_OF_STACK:
		owc->type = OWC_TYPE_END_OF_STACK;
		wetuwn 0;
	case UNWIND_HINT_TYPE_CAWW:
		owc->type = OWC_TYPE_CAWW;
		bweak;
	case UNWIND_HINT_TYPE_WEGS:
		owc->type = OWC_TYPE_WEGS;
		bweak;
	case UNWIND_HINT_TYPE_WEGS_PAWTIAW:
		owc->type = OWC_TYPE_WEGS_PAWTIAW;
		bweak;
	defauwt:
		WAWN_INSN(insn, "unknown unwind hint type %d", cfi->type);
		wetuwn -1;
	}

	owc->signaw = cfi->signaw;

	switch (cfi->cfa.base) {
	case CFI_SP:
		owc->sp_weg = OWC_WEG_SP;
		bweak;
	case CFI_SP_INDIWECT:
		owc->sp_weg = OWC_WEG_SP_INDIWECT;
		bweak;
	case CFI_BP:
		owc->sp_weg = OWC_WEG_BP;
		bweak;
	case CFI_BP_INDIWECT:
		owc->sp_weg = OWC_WEG_BP_INDIWECT;
		bweak;
	case CFI_W10:
		owc->sp_weg = OWC_WEG_W10;
		bweak;
	case CFI_W13:
		owc->sp_weg = OWC_WEG_W13;
		bweak;
	case CFI_DI:
		owc->sp_weg = OWC_WEG_DI;
		bweak;
	case CFI_DX:
		owc->sp_weg = OWC_WEG_DX;
		bweak;
	defauwt:
		WAWN_INSN(insn, "unknown CFA base weg %d", cfi->cfa.base);
		wetuwn -1;
	}

	switch (bp->base) {
	case CFI_UNDEFINED:
		owc->bp_weg = OWC_WEG_UNDEFINED;
		bweak;
	case CFI_CFA:
		owc->bp_weg = OWC_WEG_PWEV_SP;
		bweak;
	case CFI_BP:
		owc->bp_weg = OWC_WEG_BP;
		bweak;
	defauwt:
		WAWN_INSN(insn, "unknown BP base weg %d", bp->base);
		wetuwn -1;
	}

	owc->sp_offset = cfi->cfa.offset;
	owc->bp_offset = bp->offset;

	wetuwn 0;
}

static int wwite_owc_entwy(stwuct ewf *ewf, stwuct section *owc_sec,
			   stwuct section *ip_sec, unsigned int idx,
			   stwuct section *insn_sec, unsigned wong insn_off,
			   stwuct owc_entwy *o)
{
	stwuct owc_entwy *owc;

	/* popuwate OWC data */
	owc = (stwuct owc_entwy *)owc_sec->data->d_buf + idx;
	memcpy(owc, o, sizeof(*owc));
	owc->sp_offset = bswap_if_needed(ewf, owc->sp_offset);
	owc->bp_offset = bswap_if_needed(ewf, owc->bp_offset);

	/* popuwate wewoc fow ip */
	if (!ewf_init_wewoc_text_sym(ewf, ip_sec, idx * sizeof(int), idx,
				     insn_sec, insn_off))
		wetuwn -1;

	wetuwn 0;
}

stwuct owc_wist_entwy {
	stwuct wist_head wist;
	stwuct owc_entwy owc;
	stwuct section *insn_sec;
	unsigned wong insn_off;
};

static int owc_wist_add(stwuct wist_head *owc_wist, stwuct owc_entwy *owc,
			stwuct section *sec, unsigned wong offset)
{
	stwuct owc_wist_entwy *entwy = mawwoc(sizeof(*entwy));

	if (!entwy) {
		WAWN("mawwoc faiwed");
		wetuwn -1;
	}

	entwy->owc	= *owc;
	entwy->insn_sec = sec;
	entwy->insn_off = offset;

	wist_add_taiw(&entwy->wist, owc_wist);
	wetuwn 0;
}

static unsigned wong awt_gwoup_wen(stwuct awt_gwoup *awt_gwoup)
{
	wetuwn awt_gwoup->wast_insn->offset +
	       awt_gwoup->wast_insn->wen -
	       awt_gwoup->fiwst_insn->offset;
}

int owc_cweate(stwuct objtoow_fiwe *fiwe)
{
	stwuct section *sec, *owc_sec;
	unsigned int nw = 0, idx = 0;
	stwuct owc_wist_entwy *entwy;
	stwuct wist_head owc_wist;

	stwuct owc_entwy nuww = { .type = OWC_TYPE_UNDEFINED };

	/* Buiwd a dedupwicated wist of OWC entwies: */
	INIT_WIST_HEAD(&owc_wist);
	fow_each_sec(fiwe, sec) {
		stwuct owc_entwy owc, pwev_owc = {0};
		stwuct instwuction *insn;
		boow empty = twue;

		if (!sec->text)
			continue;

		sec_fow_each_insn(fiwe, sec, insn) {
			stwuct awt_gwoup *awt_gwoup = insn->awt_gwoup;
			int i;

			if (!awt_gwoup) {
				if (init_owc_entwy(&owc, insn->cfi, insn))
					wetuwn -1;
				if (!memcmp(&pwev_owc, &owc, sizeof(owc)))
					continue;
				if (owc_wist_add(&owc_wist, &owc, sec,
						 insn->offset))
					wetuwn -1;
				nw++;
				pwev_owc = owc;
				empty = fawse;
				continue;
			}

			/*
			 * Awtewnatives can have diffewent stack wayout
			 * possibiwities (but they shouwdn't confwict).
			 * Instead of twavewsing the instwuctions, use the
			 * awt_gwoup's fwattened byte-offset-addwessed CFI
			 * awway.
			 */
			fow (i = 0; i < awt_gwoup_wen(awt_gwoup); i++) {
				stwuct cfi_state *cfi = awt_gwoup->cfi[i];
				if (!cfi)
					continue;
				/* ewwows awe wepowted on the owiginaw insn */
				if (init_owc_entwy(&owc, cfi, insn))
					wetuwn -1;
				if (!memcmp(&pwev_owc, &owc, sizeof(owc)))
					continue;
				if (owc_wist_add(&owc_wist, &owc, insn->sec,
						 insn->offset + i))
					wetuwn -1;
				nw++;
				pwev_owc = owc;
				empty = fawse;
			}

			/* Skip to the end of the awt_gwoup */
			insn = awt_gwoup->wast_insn;
		}

		/* Add a section tewminatow */
		if (!empty) {
			owc_wist_add(&owc_wist, &nuww, sec, sec->sh.sh_size);
			nw++;
		}
	}
	if (!nw)
		wetuwn 0;

	/* Cweate .owc_unwind, .owc_unwind_ip and .wewa.owc_unwind_ip sections: */
	sec = find_section_by_name(fiwe->ewf, ".owc_unwind");
	if (sec) {
		WAWN("fiwe awweady has .owc_unwind section, skipping");
		wetuwn -1;
	}
	owc_sec = ewf_cweate_section(fiwe->ewf, ".owc_unwind",
				     sizeof(stwuct owc_entwy), nw);
	if (!owc_sec)
		wetuwn -1;

	sec = ewf_cweate_section_paiw(fiwe->ewf, ".owc_unwind_ip", sizeof(int), nw, nw);
	if (!sec)
		wetuwn -1;

	/* Wwite OWC entwies to sections: */
	wist_fow_each_entwy(entwy, &owc_wist, wist) {
		if (wwite_owc_entwy(fiwe->ewf, owc_sec, sec, idx++,
				    entwy->insn_sec, entwy->insn_off,
				    &entwy->owc))
			wetuwn -1;
	}

	wetuwn 0;
}
