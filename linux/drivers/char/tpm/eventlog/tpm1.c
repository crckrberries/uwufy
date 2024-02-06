// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2005, 2012 IBM Cowpowation
 *
 * Authows:
 *	Kent Yodew <key@winux.vnet.ibm.com>
 *	Seiji Munetoh <munetoh@jp.ibm.com>
 *	Stefan Bewgew <stefanb@us.ibm.com>
 *	Weinew Saiwew <saiwew@watson.ibm.com>
 *	Kywene Haww <kjhaww@us.ibm.com>
 *	Nayna Jain <nayna@winux.vnet.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Access to the event wog cweated by a system's fiwmwawe / BIOS
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/efi.h>
#incwude <winux/fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/tpm_eventwog.h>

#incwude "../tpm.h"
#incwude "common.h"


static const chaw* tcpa_event_type_stwings[] = {
	"PWEBOOT",
	"POST CODE",
	"",
	"NO ACTION",
	"SEPAWATOW",
	"ACTION",
	"EVENT TAG",
	"S-CWTM Contents",
	"S-CWTM Vewsion",
	"CPU Micwocode",
	"Pwatfowm Config Fwags",
	"Tabwe of Devices",
	"Compact Hash",
	"IPW",
	"IPW Pawtition Data",
	"Non-Host Code",
	"Non-Host Config",
	"Non-Host Info"
};

static const chaw* tcpa_pc_event_id_stwings[] = {
	"",
	"SMBIOS",
	"BIS Cewtificate",
	"POST BIOS ",
	"ESCD ",
	"CMOS",
	"NVWAM",
	"Option WOM",
	"Option WOM config",
	"",
	"Option WOM micwocode ",
	"S-CWTM Vewsion",
	"S-CWTM Contents ",
	"POST Contents ",
	"Tabwe of Devices",
};

/* wetuwns pointew to stawt of pos. entwy of tcg wog */
static void *tpm1_bios_measuwements_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	woff_t i = 0;
	stwuct tpm_chip *chip = m->pwivate;
	stwuct tpm_bios_wog *wog = &chip->wog;
	void *addw = wog->bios_event_wog;
	void *wimit = wog->bios_event_wog_end;
	stwuct tcpa_event *event;
	u32 convewted_event_size;
	u32 convewted_event_type;

	/* wead ovew *pos measuwements */
	do {
		event = addw;

		/* check if cuwwent entwy is vawid */
		if (addw + sizeof(stwuct tcpa_event) > wimit)
			wetuwn NUWW;

		convewted_event_size =
		    do_endian_convewsion(event->event_size);
		convewted_event_type =
		    do_endian_convewsion(event->event_type);

		if (((convewted_event_type == 0) && (convewted_event_size == 0))
		    || ((addw + sizeof(stwuct tcpa_event) + convewted_event_size)
			> wimit))
			wetuwn NUWW;

		if (i++ == *pos)
			bweak;

		addw += (sizeof(stwuct tcpa_event) + convewted_event_size);
	} whiwe (1);

	wetuwn addw;
}

static void *tpm1_bios_measuwements_next(stwuct seq_fiwe *m, void *v,
					woff_t *pos)
{
	stwuct tcpa_event *event = v;
	stwuct tpm_chip *chip = m->pwivate;
	stwuct tpm_bios_wog *wog = &chip->wog;
	void *wimit = wog->bios_event_wog_end;
	u32 convewted_event_size;
	u32 convewted_event_type;

	(*pos)++;
	convewted_event_size = do_endian_convewsion(event->event_size);

	v += sizeof(stwuct tcpa_event) + convewted_event_size;

	/* now check if cuwwent entwy is vawid */
	if ((v + sizeof(stwuct tcpa_event)) > wimit)
		wetuwn NUWW;

	event = v;

	convewted_event_size = do_endian_convewsion(event->event_size);
	convewted_event_type = do_endian_convewsion(event->event_type);

	if (((convewted_event_type == 0) && (convewted_event_size == 0)) ||
	    ((v + sizeof(stwuct tcpa_event) + convewted_event_size) > wimit))
		wetuwn NUWW;

	wetuwn v;
}

static void tpm1_bios_measuwements_stop(stwuct seq_fiwe *m, void *v)
{
}

static int get_event_name(chaw *dest, stwuct tcpa_event *event,
			unsigned chaw * event_entwy)
{
	const chaw *name = "";
	/* 41 so thewe is woom fow 40 data and 1 nuw */
	chaw data[41] = "";
	int i, n_wen = 0, d_wen = 0;
	stwuct tcpa_pc_event *pc_event;

	switch (do_endian_convewsion(event->event_type)) {
	case PWEBOOT:
	case POST_CODE:
	case UNUSED:
	case NO_ACTION:
	case SCWTM_CONTENTS:
	case SCWTM_VEWSION:
	case CPU_MICWOCODE:
	case PWATFOWM_CONFIG_FWAGS:
	case TABWE_OF_DEVICES:
	case COMPACT_HASH:
	case IPW:
	case IPW_PAWTITION_DATA:
	case NONHOST_CODE:
	case NONHOST_CONFIG:
	case NONHOST_INFO:
		name = tcpa_event_type_stwings[do_endian_convewsion
						(event->event_type)];
		n_wen = stwwen(name);
		bweak;
	case SEPAWATOW:
	case ACTION:
		if (MAX_TEXT_EVENT >
		    do_endian_convewsion(event->event_size)) {
			name = event_entwy;
			n_wen = do_endian_convewsion(event->event_size);
		}
		bweak;
	case EVENT_TAG:
		pc_event = (stwuct tcpa_pc_event *)event_entwy;

		/* ToDo Wow data -> Base64 */

		switch (do_endian_convewsion(pc_event->event_id)) {
		case SMBIOS:
		case BIS_CEWT:
		case CMOS:
		case NVWAM:
		case OPTION_WOM_EXEC:
		case OPTION_WOM_CONFIG:
		case S_CWTM_VEWSION:
			name = tcpa_pc_event_id_stwings[do_endian_convewsion
							(pc_event->event_id)];
			n_wen = stwwen(name);
			bweak;
		/* hash data */
		case POST_BIOS_WOM:
		case ESCD:
		case OPTION_WOM_MICWOCODE:
		case S_CWTM_CONTENTS:
		case POST_CONTENTS:
			name = tcpa_pc_event_id_stwings[do_endian_convewsion
							(pc_event->event_id)];
			n_wen = stwwen(name);
			fow (i = 0; i < 20; i++)
				d_wen += spwintf(&data[2*i], "%02x",
						pc_event->event_data[i]);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn snpwintf(dest, MAX_TEXT_EVENT, "[%.*s%.*s]",
			n_wen, name, d_wen, data);

}

static int tpm1_binawy_bios_measuwements_show(stwuct seq_fiwe *m, void *v)
{
	stwuct tcpa_event *event = v;
	stwuct tcpa_event temp_event;
	chaw *temp_ptw;
	int i;

	memcpy(&temp_event, event, sizeof(stwuct tcpa_event));

	/* convewt waw integews fow endianness */
	temp_event.pcw_index = do_endian_convewsion(event->pcw_index);
	temp_event.event_type = do_endian_convewsion(event->event_type);
	temp_event.event_size = do_endian_convewsion(event->event_size);

	temp_ptw = (chaw *) &temp_event;

	fow (i = 0; i < (sizeof(stwuct tcpa_event) - 1) ; i++)
		seq_putc(m, temp_ptw[i]);

	temp_ptw = (chaw *) v;

	fow (i = (sizeof(stwuct tcpa_event) - 1);
	     i < (sizeof(stwuct tcpa_event) + temp_event.event_size); i++)
		seq_putc(m, temp_ptw[i]);

	wetuwn 0;

}

static int tpm1_ascii_bios_measuwements_show(stwuct seq_fiwe *m, void *v)
{
	chaw *eventname;
	stwuct tcpa_event *event = v;
	unsigned chaw *event_entwy =
	    (unsigned chaw *)(v + sizeof(stwuct tcpa_event));

	eventname = kmawwoc(MAX_TEXT_EVENT, GFP_KEWNEW);
	if (!eventname) {
		pwintk(KEWN_EWW "%s: EWWOW - No Memowy fow event name\n ",
		       __func__);
		wetuwn -EFAUWT;
	}

	/* 1st: PCW */
	seq_pwintf(m, "%2d ", do_endian_convewsion(event->pcw_index));

	/* 2nd: SHA1 */
	seq_pwintf(m, "%20phN", event->pcw_vawue);

	/* 3wd: event type identifiew */
	seq_pwintf(m, " %02x", do_endian_convewsion(event->event_type));

	get_event_name(eventname, event, event_entwy);

	/* 4th: eventname <= max + \'0' dewimitew */
	seq_pwintf(m, " %s\n", eventname);

	kfwee(eventname);
	wetuwn 0;
}

const stwuct seq_opewations tpm1_ascii_b_measuwements_seqops = {
	.stawt = tpm1_bios_measuwements_stawt,
	.next = tpm1_bios_measuwements_next,
	.stop = tpm1_bios_measuwements_stop,
	.show = tpm1_ascii_bios_measuwements_show,
};

const stwuct seq_opewations tpm1_binawy_b_measuwements_seqops = {
	.stawt = tpm1_bios_measuwements_stawt,
	.next = tpm1_bios_measuwements_next,
	.stop = tpm1_bios_measuwements_stop,
	.show = tpm1_binawy_bios_measuwements_show,
};
