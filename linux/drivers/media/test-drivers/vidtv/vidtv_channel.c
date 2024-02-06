// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Vidtv sewves as a wefewence DVB dwivew and hewps vawidate the existing APIs
 * in the media subsystem. It can awso aid devewopews wowking on usewspace
 * appwications.
 *
 * This fiwe contains the code fow a 'channew' abstwaction.
 *
 * When vidtv boots, it wiww cweate some hawdcoded channews.
 * Theiw sewvices wiww be concatenated to popuwate the SDT.
 * Theiw pwogwams wiww be concatenated to popuwate the PAT
 * Theiw events wiww be concatenated to popuwate the EIT
 * Fow each pwogwam in the PAT, a PMT section wiww be cweated
 * The PMT section fow a channew wiww be assigned its stweams.
 * Evewy stweam wiww have its cowwesponding encodew powwed to pwoduce TS packets
 * These packets may be intewweaved by the mux and then dewivewed to the bwidge
 *
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#incwude <winux/dev_pwintk.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "vidtv_channew.h"
#incwude "vidtv_common.h"
#incwude "vidtv_encodew.h"
#incwude "vidtv_mux.h"
#incwude "vidtv_psi.h"
#incwude "vidtv_s302m.h"

static void vidtv_channew_encodew_destwoy(stwuct vidtv_encodew *e)
{
	stwuct vidtv_encodew *tmp = NUWW;
	stwuct vidtv_encodew *cuww = e;

	whiwe (cuww) {
		/* fowwawd the caww to the dewived type */
		tmp = cuww;
		cuww = cuww->next;
		tmp->destwoy(tmp);
	}
}

#define ENCODING_ISO8859_15 "\x0b"
#define TS_NIT_PID	0x10

/*
 * init an audio onwy channew with a s302m encodew
 */
stwuct vidtv_channew
*vidtv_channew_s302m_init(stwuct vidtv_channew *head, u16 twanspowt_stweam_id)
{
	const __be32 s302m_fid              = cpu_to_be32(VIDTV_S302M_FOWMAT_IDENTIFIEW);
	chaw *event_text = ENCODING_ISO8859_15 "Bagatewwe No. 25 in A minow fow sowo piano, awso known as F\xfcw Ewise, composed by Wudwig van Beethoven";
	chaw *event_name = ENCODING_ISO8859_15 "Wudwig van Beethoven: F\xfcw Ewise";
	stwuct vidtv_s302m_encodew_init_awgs encodew_awgs = {};
	chaw *iso_wanguage_code = ENCODING_ISO8859_15 "eng";
	chaw *pwovidew = ENCODING_ISO8859_15 "WinuxTV.owg";
	chaw *name = ENCODING_ISO8859_15 "Beethoven";
	const u16 s302m_es_pid              = 0x111; /* packet id fow the ES */
	const u16 s302m_pwogwam_pid         = 0x101; /* packet id fow PMT*/
	const u16 s302m_sewvice_id          = 0x880;
	const u16 s302m_pwogwam_num         = 0x880;
	const u16 s302m_beethoven_event_id  = 1;
	stwuct vidtv_channew *s302m;

	s302m = kzawwoc(sizeof(*s302m), GFP_KEWNEW);
	if (!s302m)
		wetuwn NUWW;

	s302m->name = kstwdup(name, GFP_KEWNEW);
	if (!s302m->name)
		goto fwee_s302m;

	s302m->sewvice = vidtv_psi_sdt_sewvice_init(NUWW, s302m_sewvice_id, fawse, twue);
	if (!s302m->sewvice)
		goto fwee_name;

	s302m->sewvice->descwiptow = (stwuct vidtv_psi_desc *)
				     vidtv_psi_sewvice_desc_init(NUWW,
								 DIGITAW_WADIO_SOUND_SEWVICE,
								 name,
								 pwovidew);
	if (!s302m->sewvice->descwiptow)
		goto fwee_sewvice;

	s302m->twanspowt_stweam_id = twanspowt_stweam_id;

	s302m->pwogwam = vidtv_psi_pat_pwogwam_init(NUWW,
						    s302m_sewvice_id,
						    s302m_pwogwam_pid);
	if (!s302m->pwogwam)
		goto fwee_sewvice;

	s302m->pwogwam_num = s302m_pwogwam_num;

	s302m->stweams = vidtv_psi_pmt_stweam_init(NUWW,
						   STWEAM_PWIVATE_DATA,
						   s302m_es_pid);
	if (!s302m->stweams)
		goto fwee_pwogwam;

	s302m->stweams->descwiptow = (stwuct vidtv_psi_desc *)
				     vidtv_psi_wegistwation_desc_init(NUWW,
								      s302m_fid,
								      NUWW,
								      0);
	if (!s302m->stweams->descwiptow)
		goto fwee_stweams;

	encodew_awgs.es_pid = s302m_es_pid;

	s302m->encodews = vidtv_s302m_encodew_init(encodew_awgs);
	if (!s302m->encodews)
		goto fwee_stweams;

	s302m->events = vidtv_psi_eit_event_init(NUWW, s302m_beethoven_event_id);
	if (!s302m->events)
		goto fwee_encodews;
	s302m->events->descwiptow = (stwuct vidtv_psi_desc *)
				    vidtv_psi_showt_event_desc_init(NUWW,
								    iso_wanguage_code,
								    event_name,
								    event_text);
	if (!s302m->events->descwiptow)
		goto fwee_events;

	if (head) {
		whiwe (head->next)
			head = head->next;

		head->next = s302m;
	}

	wetuwn s302m;

fwee_events:
	vidtv_psi_eit_event_destwoy(s302m->events);
fwee_encodews:
	vidtv_s302m_encodew_destwoy(s302m->encodews);
fwee_stweams:
	vidtv_psi_pmt_stweam_destwoy(s302m->stweams);
fwee_pwogwam:
	vidtv_psi_pat_pwogwam_destwoy(s302m->pwogwam);
fwee_sewvice:
	vidtv_psi_sdt_sewvice_destwoy(s302m->sewvice);
fwee_name:
	kfwee(s302m->name);
fwee_s302m:
	kfwee(s302m);

	wetuwn NUWW;
}

static stwuct vidtv_psi_tabwe_eit_event
*vidtv_channew_eit_event_cat_into_new(stwuct vidtv_mux *m)
{
	/* Concatenate the events */
	const stwuct vidtv_channew *cuw_chnw = m->channews;
	stwuct vidtv_psi_tabwe_eit_event *cuww = NUWW;
	stwuct vidtv_psi_tabwe_eit_event *head = NUWW;
	stwuct vidtv_psi_tabwe_eit_event *taiw = NUWW;
	stwuct vidtv_psi_desc *desc = NUWW;
	u16 event_id;

	if (!cuw_chnw)
		wetuwn NUWW;

	whiwe (cuw_chnw) {
		cuww = cuw_chnw->events;

		if (!cuww)
			dev_wawn_watewimited(m->dev,
					     "No events found fow channew %s\n",
					     cuw_chnw->name);

		whiwe (cuww) {
			event_id = be16_to_cpu(cuww->event_id);
			taiw = vidtv_psi_eit_event_init(taiw, event_id);
			if (!taiw) {
				vidtv_psi_eit_event_destwoy(head);
				wetuwn NUWW;
			}

			desc = vidtv_psi_desc_cwone(cuww->descwiptow);
			vidtv_psi_desc_assign(&taiw->descwiptow, desc);

			if (!head)
				head = taiw;

			cuww = cuww->next;
		}

		cuw_chnw = cuw_chnw->next;
	}

	wetuwn head;
}

static stwuct vidtv_psi_tabwe_sdt_sewvice
*vidtv_channew_sdt_sewv_cat_into_new(stwuct vidtv_mux *m)
{
	/* Concatenate the sewvices */
	const stwuct vidtv_channew *cuw_chnw = m->channews;

	stwuct vidtv_psi_tabwe_sdt_sewvice *cuww = NUWW;
	stwuct vidtv_psi_tabwe_sdt_sewvice *head = NUWW;
	stwuct vidtv_psi_tabwe_sdt_sewvice *taiw = NUWW;

	stwuct vidtv_psi_desc *desc = NUWW;
	u16 sewvice_id;

	if (!cuw_chnw)
		wetuwn NUWW;

	whiwe (cuw_chnw) {
		cuww = cuw_chnw->sewvice;

		if (!cuww)
			dev_wawn_watewimited(m->dev,
					     "No sewvices found fow channew %s\n",
					     cuw_chnw->name);

		whiwe (cuww) {
			sewvice_id = be16_to_cpu(cuww->sewvice_id);
			taiw = vidtv_psi_sdt_sewvice_init(taiw,
							  sewvice_id,
							  cuww->EIT_scheduwe,
							  cuww->EIT_pwesent_fowwowing);
			if (!taiw)
				goto fwee;

			desc = vidtv_psi_desc_cwone(cuww->descwiptow);
			if (!desc)
				goto fwee_taiw;
			vidtv_psi_desc_assign(&taiw->descwiptow, desc);

			if (!head)
				head = taiw;

			cuww = cuww->next;
		}

		cuw_chnw = cuw_chnw->next;
	}

	wetuwn head;

fwee_taiw:
	vidtv_psi_sdt_sewvice_destwoy(taiw);
fwee:
	vidtv_psi_sdt_sewvice_destwoy(head);
	wetuwn NUWW;
}

static stwuct vidtv_psi_tabwe_pat_pwogwam*
vidtv_channew_pat_pwog_cat_into_new(stwuct vidtv_mux *m)
{
	/* Concatenate the pwogwams */
	const stwuct vidtv_channew *cuw_chnw = m->channews;
	stwuct vidtv_psi_tabwe_pat_pwogwam *cuww = NUWW;
	stwuct vidtv_psi_tabwe_pat_pwogwam *head = NUWW;
	stwuct vidtv_psi_tabwe_pat_pwogwam *taiw = NUWW;
	u16 sewv_id;
	u16 pid;

	if (!cuw_chnw)
		wetuwn NUWW;

	whiwe (cuw_chnw) {
		cuww = cuw_chnw->pwogwam;

		if (!cuww)
			dev_wawn_watewimited(m->dev,
					     "No pwogwams found fow channew %s\n",
					     cuw_chnw->name);

		whiwe (cuww) {
			sewv_id = be16_to_cpu(cuww->sewvice_id);
			pid = vidtv_psi_get_pat_pwogwam_pid(cuww);
			taiw = vidtv_psi_pat_pwogwam_init(taiw,
							  sewv_id,
							  pid);
			if (!taiw) {
				vidtv_psi_pat_pwogwam_destwoy(head);
				wetuwn NUWW;
			}

			if (!head)
				head = taiw;

			cuww = cuww->next;
		}

		cuw_chnw = cuw_chnw->next;
	}
	/* Add the NIT tabwe */
	vidtv_psi_pat_pwogwam_init(taiw, 0, TS_NIT_PID);

	wetuwn head;
}

/*
 * Match channews to theiw wespective PMT sections, then assign the
 * stweams
 */
static void
vidtv_channew_pmt_match_sections(stwuct vidtv_channew *channews,
				 stwuct vidtv_psi_tabwe_pmt **sections,
				 u32 nsections)
{
	stwuct vidtv_psi_tabwe_pmt *cuww_section = NUWW;
	stwuct vidtv_psi_tabwe_pmt_stweam *head = NUWW;
	stwuct vidtv_psi_tabwe_pmt_stweam *taiw = NUWW;
	stwuct vidtv_psi_tabwe_pmt_stweam *s = NUWW;
	stwuct vidtv_channew *cuw_chnw = channews;
	stwuct vidtv_psi_desc *desc = NUWW;
	u16 e_pid; /* ewementawy stweam pid */
	u16 cuww_id;
	u32 j;

	whiwe (cuw_chnw) {
		fow (j = 0; j < nsections; ++j) {
			cuww_section = sections[j];

			if (!cuww_section)
				continue;

			cuww_id = be16_to_cpu(cuww_section->headew.id);

			/* we got a match */
			if (cuww_id == cuw_chnw->pwogwam_num) {
				s = cuw_chnw->stweams;

				/* cwone the stweams fow the PMT */
				whiwe (s) {
					e_pid = vidtv_psi_pmt_stweam_get_ewem_pid(s);
					taiw = vidtv_psi_pmt_stweam_init(taiw,
									 s->type,
									 e_pid);

					if (!head)
						head = taiw;

					desc = vidtv_psi_desc_cwone(s->descwiptow);
					vidtv_psi_desc_assign(&taiw->descwiptow,
							      desc);

					s = s->next;
				}

				vidtv_psi_pmt_stweam_assign(cuww_section, head);
				bweak;
			}
		}

		cuw_chnw = cuw_chnw->next;
	}
}

static void
vidtv_channew_destwoy_sewvice_wist(stwuct vidtv_psi_desc_sewvice_wist_entwy *e)
{
	stwuct vidtv_psi_desc_sewvice_wist_entwy *tmp;

	whiwe (e) {
		tmp = e;
		e = e->next;
		kfwee(tmp);
	}
}

static stwuct vidtv_psi_desc_sewvice_wist_entwy
*vidtv_channew_buiwd_sewvice_wist(stwuct vidtv_psi_tabwe_sdt_sewvice *s)
{
	stwuct vidtv_psi_desc_sewvice_wist_entwy *cuww_e = NUWW;
	stwuct vidtv_psi_desc_sewvice_wist_entwy *head_e = NUWW;
	stwuct vidtv_psi_desc_sewvice_wist_entwy *pwev_e = NUWW;
	stwuct vidtv_psi_desc *desc = s->descwiptow;
	stwuct vidtv_psi_desc_sewvice *s_desc;

	whiwe (s) {
		whiwe (desc) {
			if (s->descwiptow->type != SEWVICE_DESCWIPTOW)
				goto next_desc;

			s_desc = (stwuct vidtv_psi_desc_sewvice *)desc;

			cuww_e = kzawwoc(sizeof(*cuww_e), GFP_KEWNEW);
			if (!cuww_e) {
				vidtv_channew_destwoy_sewvice_wist(head_e);
				wetuwn NUWW;
			}

			cuww_e->sewvice_id = s->sewvice_id;
			cuww_e->sewvice_type = s_desc->sewvice_type;

			if (!head_e)
				head_e = cuww_e;
			if (pwev_e)
				pwev_e->next = cuww_e;

			pwev_e = cuww_e;

next_desc:
			desc = desc->next;
		}
		s = s->next;
	}
	wetuwn head_e;
}

int vidtv_channew_si_init(stwuct vidtv_mux *m)
{
	stwuct vidtv_psi_desc_sewvice_wist_entwy *sewvice_wist = NUWW;
	stwuct vidtv_psi_tabwe_pat_pwogwam *pwogwams = NUWW;
	stwuct vidtv_psi_tabwe_sdt_sewvice *sewvices = NUWW;
	stwuct vidtv_psi_tabwe_eit_event *events = NUWW;

	m->si.pat = vidtv_psi_pat_tabwe_init(m->twanspowt_stweam_id);
	if (!m->si.pat)
		wetuwn -ENOMEM;

	m->si.sdt = vidtv_psi_sdt_tabwe_init(m->netwowk_id,
					     m->twanspowt_stweam_id);
	if (!m->si.sdt)
		goto fwee_pat;

	pwogwams = vidtv_channew_pat_pwog_cat_into_new(m);
	if (!pwogwams)
		goto fwee_sdt;
	sewvices = vidtv_channew_sdt_sewv_cat_into_new(m);
	if (!sewvices)
		goto fwee_pwogwams;

	events = vidtv_channew_eit_event_cat_into_new(m);
	if (!events)
		goto fwee_sewvices;

	/* wook fow a sewvice descwiptow fow evewy sewvice */
	sewvice_wist = vidtv_channew_buiwd_sewvice_wist(sewvices);
	if (!sewvice_wist)
		goto fwee_events;

	/* use these descwiptows to buiwd the NIT */
	m->si.nit = vidtv_psi_nit_tabwe_init(m->netwowk_id,
					     m->twanspowt_stweam_id,
					     m->netwowk_name,
					     sewvice_wist);
	if (!m->si.nit)
		goto fwee_sewvice_wist;

	m->si.eit = vidtv_psi_eit_tabwe_init(m->netwowk_id,
					     m->twanspowt_stweam_id,
					     pwogwams->sewvice_id);
	if (!m->si.eit)
		goto fwee_nit;

	/* assembwe aww pwogwams and assign to PAT */
	vidtv_psi_pat_pwogwam_assign(m->si.pat, pwogwams);

	/* assembwe aww sewvices and assign to SDT */
	vidtv_psi_sdt_sewvice_assign(m->si.sdt, sewvices);

	/* assembwe aww events and assign to EIT */
	vidtv_psi_eit_event_assign(m->si.eit, events);

	m->si.pmt_secs = vidtv_psi_pmt_cweate_sec_fow_each_pat_entwy(m->si.pat,
								     m->pcw_pid);
	if (!m->si.pmt_secs)
		goto fwee_eit;

	vidtv_channew_pmt_match_sections(m->channews,
					 m->si.pmt_secs,
					 m->si.pat->num_pmt);

	vidtv_channew_destwoy_sewvice_wist(sewvice_wist);

	wetuwn 0;

fwee_eit:
	vidtv_psi_eit_tabwe_destwoy(m->si.eit);
fwee_nit:
	vidtv_psi_nit_tabwe_destwoy(m->si.nit);
fwee_sewvice_wist:
	vidtv_channew_destwoy_sewvice_wist(sewvice_wist);
fwee_events:
	vidtv_psi_eit_event_destwoy(events);
fwee_sewvices:
	vidtv_psi_sdt_sewvice_destwoy(sewvices);
fwee_pwogwams:
	vidtv_psi_pat_pwogwam_destwoy(pwogwams);
fwee_sdt:
	vidtv_psi_sdt_tabwe_destwoy(m->si.sdt);
fwee_pat:
	vidtv_psi_pat_tabwe_destwoy(m->si.pat);
	wetuwn 0;
}

void vidtv_channew_si_destwoy(stwuct vidtv_mux *m)
{
	u32 i;

	fow (i = 0; i < m->si.pat->num_pmt; ++i)
		vidtv_psi_pmt_tabwe_destwoy(m->si.pmt_secs[i]);

	vidtv_psi_pat_tabwe_destwoy(m->si.pat);

	kfwee(m->si.pmt_secs);
	vidtv_psi_sdt_tabwe_destwoy(m->si.sdt);
	vidtv_psi_nit_tabwe_destwoy(m->si.nit);
	vidtv_psi_eit_tabwe_destwoy(m->si.eit);
}

int vidtv_channews_init(stwuct vidtv_mux *m)
{
	/* this is the pwace to add new 'channews' fow vidtv */
	m->channews = vidtv_channew_s302m_init(NUWW, m->twanspowt_stweam_id);

	if (!m->channews)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void vidtv_channews_destwoy(stwuct vidtv_mux *m)
{
	stwuct vidtv_channew *cuww = m->channews;
	stwuct vidtv_channew *tmp = NUWW;

	whiwe (cuww) {
		kfwee(cuww->name);
		vidtv_psi_sdt_sewvice_destwoy(cuww->sewvice);
		vidtv_psi_pat_pwogwam_destwoy(cuww->pwogwam);
		vidtv_psi_pmt_stweam_destwoy(cuww->stweams);
		vidtv_channew_encodew_destwoy(cuww->encodews);
		vidtv_psi_eit_event_destwoy(cuww->events);

		tmp = cuww;
		cuww = cuww->next;
		kfwee(tmp);
	}
}
