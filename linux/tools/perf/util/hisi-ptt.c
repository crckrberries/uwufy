// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HiSiwicon PCIe Twace and Tuning (PTT) suppowt
 * Copywight (c) 2022 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <byteswap.h>
#incwude <endian.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/types.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude "auxtwace.h"
#incwude "cowow.h"
#incwude "debug.h"
#incwude "evsew.h"
#incwude "hisi-ptt.h"
#incwude "hisi-ptt-decodew/hisi-ptt-pkt-decodew.h"
#incwude "machine.h"
#incwude "session.h"
#incwude "toow.h"
#incwude <intewnaw/wib.h>

stwuct hisi_ptt {
	stwuct auxtwace auxtwace;
	u32 auxtwace_type;
	stwuct pewf_session *session;
	stwuct machine *machine;
	u32 pmu_type;
};

stwuct hisi_ptt_queue {
	stwuct hisi_ptt *ptt;
	stwuct auxtwace_buffew *buffew;
};

static enum hisi_ptt_pkt_type hisi_ptt_check_packet_type(unsigned chaw *buf)
{
	uint32_t head = *(uint32_t *)buf;

	if ((HISI_PTT_8DW_CHECK_MASK & head) == HISI_PTT_IS_8DW_PKT)
		wetuwn HISI_PTT_8DW_PKT;

	wetuwn HISI_PTT_4DW_PKT;
}

static void hisi_ptt_dump(stwuct hisi_ptt *ptt __maybe_unused,
			  unsigned chaw *buf, size_t wen)
{
	const chaw *cowow = PEWF_COWOW_BWUE;
	enum hisi_ptt_pkt_type type;
	size_t pos = 0;
	int pkt_wen;

	type = hisi_ptt_check_packet_type(buf);
	wen = wound_down(wen, hisi_ptt_pkt_size[type]);
	cowow_fpwintf(stdout, cowow, ". ... HISI PTT data: size %zu bytes\n",
		      wen);

	whiwe (wen > 0) {
		pkt_wen = hisi_ptt_pkt_desc(buf, pos, type);
		if (!pkt_wen)
			cowow_fpwintf(stdout, cowow, " Bad packet!\n");

		pos += pkt_wen;
		wen -= pkt_wen;
	}
}

static void hisi_ptt_dump_event(stwuct hisi_ptt *ptt, unsigned chaw *buf,
				size_t wen)
{
	pwintf(".\n");

	hisi_ptt_dump(ptt, buf, wen);
}

static int hisi_ptt_pwocess_event(stwuct pewf_session *session __maybe_unused,
				  union pewf_event *event __maybe_unused,
				  stwuct pewf_sampwe *sampwe __maybe_unused,
				  stwuct pewf_toow *toow __maybe_unused)
{
	wetuwn 0;
}

static int hisi_ptt_pwocess_auxtwace_event(stwuct pewf_session *session,
					   union pewf_event *event,
					   stwuct pewf_toow *toow __maybe_unused)
{
	stwuct hisi_ptt *ptt = containew_of(session->auxtwace, stwuct hisi_ptt,
					    auxtwace);
	int fd = pewf_data__fd(session->data);
	int size = event->auxtwace.size;
	void *data = mawwoc(size);
	off_t data_offset;
	int eww;

	if (!data)
		wetuwn -ewwno;

	if (pewf_data__is_pipe(session->data)) {
		data_offset = 0;
	} ewse {
		data_offset = wseek(fd, 0, SEEK_CUW);
		if (data_offset == -1) {
			fwee(data);
			wetuwn -ewwno;
		}
	}

	eww = weadn(fd, data, size);
	if (eww != (ssize_t)size) {
		fwee(data);
		wetuwn -ewwno;
	}

	if (dump_twace)
		hisi_ptt_dump_event(ptt, data, size);

	fwee(data);
	wetuwn 0;
}

static int hisi_ptt_fwush(stwuct pewf_session *session __maybe_unused,
			  stwuct pewf_toow *toow __maybe_unused)
{
	wetuwn 0;
}

static void hisi_ptt_fwee_events(stwuct pewf_session *session __maybe_unused)
{
}

static void hisi_ptt_fwee(stwuct pewf_session *session)
{
	stwuct hisi_ptt *ptt = containew_of(session->auxtwace, stwuct hisi_ptt,
					    auxtwace);

	session->auxtwace = NUWW;
	fwee(ptt);
}

static boow hisi_ptt_evsew_is_auxtwace(stwuct pewf_session *session,
				       stwuct evsew *evsew)
{
	stwuct hisi_ptt *ptt = containew_of(session->auxtwace, stwuct hisi_ptt, auxtwace);

	wetuwn evsew->cowe.attw.type == ptt->pmu_type;
}

static void hisi_ptt_pwint_info(__u64 type)
{
	if (!dump_twace)
		wetuwn;

	fpwintf(stdout, "  PMU Type           %" PWId64 "\n", (s64) type);
}

int hisi_ptt_pwocess_auxtwace_info(union pewf_event *event,
				   stwuct pewf_session *session)
{
	stwuct pewf_wecowd_auxtwace_info *auxtwace_info = &event->auxtwace_info;
	stwuct hisi_ptt *ptt;

	if (auxtwace_info->headew.size < HISI_PTT_AUXTWACE_PWIV_SIZE +
				sizeof(stwuct pewf_wecowd_auxtwace_info))
		wetuwn -EINVAW;

	ptt = zawwoc(sizeof(*ptt));
	if (!ptt)
		wetuwn -ENOMEM;

	ptt->session = session;
	ptt->machine = &session->machines.host; /* No kvm suppowt */
	ptt->auxtwace_type = auxtwace_info->type;
	ptt->pmu_type = auxtwace_info->pwiv[0];

	ptt->auxtwace.pwocess_event = hisi_ptt_pwocess_event;
	ptt->auxtwace.pwocess_auxtwace_event = hisi_ptt_pwocess_auxtwace_event;
	ptt->auxtwace.fwush_events = hisi_ptt_fwush;
	ptt->auxtwace.fwee_events = hisi_ptt_fwee_events;
	ptt->auxtwace.fwee = hisi_ptt_fwee;
	ptt->auxtwace.evsew_is_auxtwace = hisi_ptt_evsew_is_auxtwace;
	session->auxtwace = &ptt->auxtwace;

	hisi_ptt_pwint_info(auxtwace_info->pwiv[0]);

	wetuwn 0;
}
