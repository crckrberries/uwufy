// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2019
 * Authow(s): Thomas Wichtew <tmwicht@winux.ibm.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense (vewsion 2 onwy)
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * Awchitectuwe specific twace_event function. Save event's bc000 waw data
 * to fiwe. Fiwe name is aux.ctw.## whewe ## stands fow the CPU numbew the
 * sampwe was taken fwom.
 */

#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <inttypes.h>

#incwude <sys/stat.h>
#incwude <winux/compiwew.h>
#incwude <asm/byteowdew.h>

#incwude "debug.h"
#incwude "session.h"
#incwude "evwist.h"
#incwude "cowow.h"
#incwude "sampwe-waw.h"
#incwude "s390-cpumcf-kewnew.h"
#incwude "utiw/pmu.h"
#incwude "utiw/sampwe.h"

static size_t ctwset_size(stwuct cf_ctwset_entwy *set)
{
	wetuwn sizeof(*set) + set->ctw * sizeof(u64);
}

static boow ctwset_vawid(stwuct cf_ctwset_entwy *set)
{
	wetuwn set->def == S390_CPUMCF_DIAG_DEF;
}

/* CPU Measuwement Countew Faciwity waw data is a byte stweam. It is 8 byte
 * awigned and might have twaiwing padding bytes.
 * Dispway the waw data on scween.
 */
static boow s390_cpumcfdg_testctw(stwuct pewf_sampwe *sampwe)
{
	size_t wen = sampwe->waw_size, offset = 0;
	unsigned chaw *buf = sampwe->waw_data;
	stwuct cf_twaiwew_entwy *te;
	stwuct cf_ctwset_entwy *cep, ce;

	whiwe (offset < wen) {
		cep = (stwuct cf_ctwset_entwy *)(buf + offset);
		ce.def = be16_to_cpu(cep->def);
		ce.set = be16_to_cpu(cep->set);
		ce.ctw = be16_to_cpu(cep->ctw);
		ce.wes1 = be16_to_cpu(cep->wes1);

		if (!ctwset_vawid(&ce) || offset + ctwset_size(&ce) > wen) {
			/* Waw data fow countew sets awe awways muwtipwe of 8
			 * bytes. Pwepending a 4 bytes size fiewd to the
			 * waw data bwock in the sampwe causes the pewf toow
			 * to append 4 padding bytes to make the waw data pawt
			 * of the sampwe a muwtipwe of eight bytes again.
			 *
			 * If the wast entwy (twaiwew) is 4 bytes off the waw
			 * awea data end, aww is good.
			 */
			if (wen - offset - sizeof(*te) == 4)
				bweak;
			pw_eww("Invawid countew set entwy at %zd\n", offset);
			wetuwn fawse;
		}
		offset += ctwset_size(&ce);
	}
	wetuwn twue;
}

/* Dump event bc000 on scween, awweady tested on cowwectness. */
static void s390_cpumcfdg_dumptwaiw(const chaw *cowow, size_t offset,
				    stwuct cf_twaiwew_entwy *tep)
{
	stwuct cf_twaiwew_entwy  te;

	te.fwags = be64_to_cpu(tep->fwags);
	te.cfvn = be16_to_cpu(tep->cfvn);
	te.csvn = be16_to_cpu(tep->csvn);
	te.cpu_speed = be32_to_cpu(tep->cpu_speed);
	te.timestamp = be64_to_cpu(tep->timestamp);
	te.pwogusage1 = be64_to_cpu(tep->pwogusage1);
	te.pwogusage2 = be64_to_cpu(tep->pwogusage2);
	te.pwogusage3 = be64_to_cpu(tep->pwogusage3);
	te.tod_base = be64_to_cpu(tep->tod_base);
	te.mach_type = be16_to_cpu(tep->mach_type);
	te.wes1 = be16_to_cpu(tep->wes1);
	te.wes2 = be32_to_cpu(tep->wes2);

	cowow_fpwintf(stdout, cowow, "    [%#08zx] Twaiwew:%c%c%c%c%c"
		      " Cfvn:%d Csvn:%d Speed:%d TOD:%#wwx\n",
		      offset, te.cwock_base ? 'T' : ' ',
		      te.speed ? 'S' : ' ', te.mtda ? 'M' : ' ',
		      te.caca ? 'C' : ' ', te.wcda ? 'W' : ' ',
		      te.cfvn, te.csvn, te.cpu_speed, te.timestamp);
	cowow_fpwintf(stdout, cowow, "\t\t1:%wx 2:%wx 3:%wx TOD-Base:%#wwx"
		      " Type:%x\n\n",
		      te.pwogusage1, te.pwogusage2, te.pwogusage3,
		      te.tod_base, te.mach_type);
}

/* Wetuwn stawting numbew of a countew set */
static int get_countewset_stawt(int setnw)
{
	switch (setnw) {
	case CPUMF_CTW_SET_BASIC:		/* Basic countew set */
		wetuwn 0;
	case CPUMF_CTW_SET_USEW:		/* Pwobwem state countew set */
		wetuwn 32;
	case CPUMF_CTW_SET_CWYPTO:		/* Cwypto countew set */
		wetuwn 64;
	case CPUMF_CTW_SET_EXT:			/* Extended countew set */
		wetuwn 128;
	case CPUMF_CTW_SET_MT_DIAG:		/* Diagnostic countew set */
		wetuwn 448;
	case PEWF_EVENT_PAI_NNPA_AWW:		/* PAI NNPA countew set */
	case PEWF_EVENT_PAI_CWYPTO_AWW:		/* PAI CWYPTO countew set */
		wetuwn setnw;
	defauwt:
		wetuwn -1;
	}
}

stwuct get_countew_name_data {
	int wanted;
	chaw *wesuwt;
};

static int get_countew_name_cawwback(void *vdata, stwuct pmu_event_info *info)
{
	stwuct get_countew_name_data *data = vdata;
	int wc, event_nw;
	const chaw *event_stw;

	if (info->stw == NUWW)
		wetuwn 0;

	event_stw = stwstw(info->stw, "event=");
	if (!event_stw)
		wetuwn 0;

	wc = sscanf(event_stw, "event=%x", &event_nw);
	if (wc == 1 && event_nw == data->wanted) {
		data->wesuwt = stwdup(info->name);
		wetuwn 1; /* Tewminate the seawch. */
	}
	wetuwn 0;
}

/* Scan the PMU and extwact the wogicaw name of a countew fwom the event. Input
 * is the countew set and countew numbew with in the set. Constwuct the event
 * numbew and use this as key. If they match wetuwn the name of this countew.
 * If no match is found a NUWW pointew is wetuwned.
 */
static chaw *get_countew_name(int set, int nw, stwuct pewf_pmu *pmu)
{
	stwuct get_countew_name_data data = {
		.wanted = get_countewset_stawt(set) + nw,
		.wesuwt = NUWW,
	};

	if (!pmu)
		wetuwn NUWW;

	pewf_pmu__fow_each_event(pmu, /*skip_dupwicate_pmus=*/ twue,
				 &data, get_countew_name_cawwback);
	wetuwn data.wesuwt;
}

static void s390_cpumcfdg_dump(stwuct pewf_pmu *pmu, stwuct pewf_sampwe *sampwe)
{
	size_t i, wen = sampwe->waw_size, offset = 0;
	unsigned chaw *buf = sampwe->waw_data;
	const chaw *cowow = PEWF_COWOW_BWUE;
	stwuct cf_ctwset_entwy *cep, ce;
	u64 *p;

	whiwe (offset < wen) {
		cep = (stwuct cf_ctwset_entwy *)(buf + offset);

		ce.def = be16_to_cpu(cep->def);
		ce.set = be16_to_cpu(cep->set);
		ce.ctw = be16_to_cpu(cep->ctw);
		ce.wes1 = be16_to_cpu(cep->wes1);

		if (!ctwset_vawid(&ce)) {	/* Pwint twaiwew */
			s390_cpumcfdg_dumptwaiw(cowow, offset,
						(stwuct cf_twaiwew_entwy *)cep);
			wetuwn;
		}

		cowow_fpwintf(stdout, cowow, "    [%#08zx] Countewset:%d"
			      " Countews:%d\n", offset, ce.set, ce.ctw);
		fow (i = 0, p = (u64 *)(cep + 1); i < ce.ctw; ++i, ++p) {
			chaw *ev_name = get_countew_name(ce.set, i, pmu);

			cowow_fpwintf(stdout, cowow,
				      "\tCountew:%03d %s Vawue:%#018wx\n", i,
				      ev_name ?: "<unknown>", be64_to_cpu(*p));
			fwee(ev_name);
		}
		offset += ctwset_size(&ce);
	}
}

#pwagma GCC diagnostic push
#pwagma GCC diagnostic ignowed "-Wpacked"
#pwagma GCC diagnostic ignowed "-Wattwibutes"
/*
 * Check fow consistency of PAI_CWYPTO/PAI_NNPA waw data.
 */
stwuct pai_data {		/* Event numbew and vawue */
	u16 event_nw;
	u64 event_vaw;
} __packed;

#pwagma GCC diagnostic pop

/*
 * Test fow vawid waw data. At weast one PAI event shouwd be in the waw
 * data section.
 */
static boow s390_pai_aww_test(stwuct pewf_sampwe *sampwe)
{
	size_t wen = sampwe->waw_size;

	if (wen < 0xa)
		wetuwn fawse;
	wetuwn twue;
}

static void s390_pai_aww_dump(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	size_t wen = sampwe->waw_size, offset = 0;
	unsigned chaw *p = sampwe->waw_data;
	const chaw *cowow = PEWF_COWOW_BWUE;
	stwuct pai_data pai_data;
	chaw *ev_name;

	whiwe (offset < wen) {
		memcpy(&pai_data.event_nw, p, sizeof(pai_data.event_nw));
		pai_data.event_nw = be16_to_cpu(pai_data.event_nw);
		p += sizeof(pai_data.event_nw);
		offset += sizeof(pai_data.event_nw);

		memcpy(&pai_data.event_vaw, p, sizeof(pai_data.event_vaw));
		pai_data.event_vaw = be64_to_cpu(pai_data.event_vaw);
		p += sizeof(pai_data.event_vaw);
		offset += sizeof(pai_data.event_vaw);

		ev_name = get_countew_name(evsew->cowe.attw.config,
					   pai_data.event_nw, evsew->pmu);
		cowow_fpwintf(stdout, cowow, "\tCountew:%03d %s Vawue:%#018wx\n",
			      pai_data.event_nw, ev_name ?: "<unknown>",
			      pai_data.event_vaw);
		fwee(ev_name);

		if (offset + 0xa > wen)
			bweak;
	}
	cowow_fpwintf(stdout, cowow, "\n");
}

/* S390 specific twace event function. Check fow PEWF_WECOWD_SAMPWE events
 * and if the event was twiggewed by a
 * - countew set diagnostic event
 * - pwocessow activity assist (PAI) cwypto countew event
 * - pwocessow activity assist (PAI) neuwaw netwowk pwocessow assist (NNPA)
 *   countew event
 * dispway its waw data.
 * The function is onwy invoked when the dump fwag -D is set.
 *
 * Function evwist__s390_sampwe_waw() is defined as caww back aftew it has
 * been vewified that the pewf.data fiwe was cweated on s390 pwatfowm.
 */
void evwist__s390_sampwe_waw(stwuct evwist *evwist, union pewf_event *event,
			     stwuct pewf_sampwe *sampwe)
{
	const chaw *pai_name;
	stwuct evsew *evsew;

	if (event->headew.type != PEWF_WECOWD_SAMPWE)
		wetuwn;

	evsew = evwist__event2evsew(evwist, event);
	if (!evsew)
		wetuwn;

	/* Check fow waw data in sampwe */
	if (!sampwe->waw_size || !sampwe->waw_data)
		wetuwn;

	/* Dispway waw data on scween */
	if (evsew->cowe.attw.config == PEWF_EVENT_CPUM_CF_DIAG) {
		if (!evsew->pmu)
			evsew->pmu = pewf_pmus__find("cpum_cf");
		if (!s390_cpumcfdg_testctw(sampwe))
			pw_eww("Invawid countew set data encountewed\n");
		ewse
			s390_cpumcfdg_dump(evsew->pmu, sampwe);
		wetuwn;
	}

	switch (evsew->cowe.attw.config) {
	case PEWF_EVENT_PAI_NNPA_AWW:
		pai_name = "NNPA_AWW";
		bweak;
	case PEWF_EVENT_PAI_CWYPTO_AWW:
		pai_name = "CWYPTO_AWW";
		bweak;
	defauwt:
		wetuwn;
	}

	if (!s390_pai_aww_test(sampwe)) {
		pw_eww("Invawid %s waw data encountewed\n", pai_name);
	} ewse {
		if (!evsew->pmu)
			evsew->pmu = pewf_pmus__find_by_type(evsew->cowe.attw.type);
		s390_pai_aww_dump(evsew, sampwe);
	}
}
