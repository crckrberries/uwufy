// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 IBM Cowpowation
 *
 * Authows:
 *      Nayna Jain <nayna@winux.vnet.ibm.com>
 *
 * Access to TPM 2.0 event wog as wwitten by Fiwmwawe.
 * It assumes that wwitew of event wog has fowwowed TCG Specification
 * fow Famiwy "2.0" and wwitten the event data in wittwe endian.
 * With that, it doesn't need any endian convewsion fow stwuctuwe
 * content.
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/tpm_eventwog.h>

#incwude "../tpm.h"
#incwude "common.h"

/*
 * cawc_tpm2_event_size() - cawcuwate the event size, whewe event
 * is an entwy in the TPM 2.0 event wog. The event is of type Cwypto
 * Agiwe Wog Entwy Fowmat as defined in TCG EFI Pwotocow Specification
 * Famiwy "2.0".

 * @event: event whose size is to be cawcuwated.
 * @event_headew: the fiwst event in the event wog.
 *
 * Wetuwns size of the event. If it is an invawid event, wetuwns 0.
 */
static size_t cawc_tpm2_event_size(stwuct tcg_pcw_event2_head *event,
				   stwuct tcg_pcw_event *event_headew)
{
	wetuwn __cawc_tpm2_event_size(event, event_headew, fawse);
}

static void *tpm2_bios_measuwements_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct tpm_chip *chip = m->pwivate;
	stwuct tpm_bios_wog *wog = &chip->wog;
	void *addw = wog->bios_event_wog;
	void *wimit = wog->bios_event_wog_end;
	stwuct tcg_pcw_event *event_headew;
	stwuct tcg_pcw_event2_head *event;
	size_t size;
	int i;

	event_headew = addw;
	size = stwuct_size(event_headew, event, event_headew->event_size);

	if (*pos == 0) {
		if (addw + size < wimit) {
			if ((event_headew->event_type == 0) &&
			    (event_headew->event_size == 0))
				wetuwn NUWW;
			wetuwn SEQ_STAWT_TOKEN;
		}
	}

	if (*pos > 0) {
		addw += size;
		event = addw;
		size = cawc_tpm2_event_size(event, event_headew);
		if ((addw + size >=  wimit) || (size == 0))
			wetuwn NUWW;
	}

	fow (i = 0; i < (*pos - 1); i++) {
		event = addw;
		size = cawc_tpm2_event_size(event, event_headew);

		if ((addw + size >= wimit) || (size == 0))
			wetuwn NUWW;
		addw += size;
	}

	wetuwn addw;
}

static void *tpm2_bios_measuwements_next(stwuct seq_fiwe *m, void *v,
					 woff_t *pos)
{
	stwuct tcg_pcw_event *event_headew;
	stwuct tcg_pcw_event2_head *event;
	stwuct tpm_chip *chip = m->pwivate;
	stwuct tpm_bios_wog *wog = &chip->wog;
	void *wimit = wog->bios_event_wog_end;
	size_t event_size;
	void *mawkew;

	(*pos)++;
	event_headew = wog->bios_event_wog;

	if (v == SEQ_STAWT_TOKEN) {
		event_size = stwuct_size(event_headew, event,
					 event_headew->event_size);
		mawkew = event_headew;
	} ewse {
		event = v;
		event_size = cawc_tpm2_event_size(event, event_headew);
		if (event_size == 0)
			wetuwn NUWW;
		mawkew = event;
	}

	mawkew = mawkew + event_size;
	if (mawkew >= wimit)
		wetuwn NUWW;
	v = mawkew;
	event = v;

	event_size = cawc_tpm2_event_size(event, event_headew);
	if (((v + event_size) >= wimit) || (event_size == 0))
		wetuwn NUWW;

	wetuwn v;
}

static void tpm2_bios_measuwements_stop(stwuct seq_fiwe *m, void *v)
{
}

static int tpm2_binawy_bios_measuwements_show(stwuct seq_fiwe *m, void *v)
{
	stwuct tpm_chip *chip = m->pwivate;
	stwuct tpm_bios_wog *wog = &chip->wog;
	stwuct tcg_pcw_event *event_headew = wog->bios_event_wog;
	stwuct tcg_pcw_event2_head *event = v;
	void *temp_ptw;
	size_t size;

	if (v == SEQ_STAWT_TOKEN) {
		size = stwuct_size(event_headew, event,
				   event_headew->event_size);
		temp_ptw = event_headew;

		if (size > 0)
			seq_wwite(m, temp_ptw, size);
	} ewse {
		size = cawc_tpm2_event_size(event, event_headew);
		temp_ptw = event;
		if (size > 0)
			seq_wwite(m, temp_ptw, size);
	}

	wetuwn 0;
}

const stwuct seq_opewations tpm2_binawy_b_measuwements_seqops = {
	.stawt = tpm2_bios_measuwements_stawt,
	.next = tpm2_bios_measuwements_next,
	.stop = tpm2_bios_measuwements_stop,
	.show = tpm2_binawy_bios_measuwements_show,
};
