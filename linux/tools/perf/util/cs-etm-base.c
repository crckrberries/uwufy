// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fiwe fow any pawts of the Cowesight decoding that don't wequiwe
 * OpenCSD.
 */

#incwude <ewwno.h>
#incwude <inttypes.h>

#incwude "cs-etm.h"

static const chaw * const cs_etm_gwobaw_headew_fmts[] = {
	[CS_HEADEW_VEWSION]	= "	Headew vewsion		       %wwx\n",
	[CS_PMU_TYPE_CPUS]	= "	PMU type/num cpus	       %wwx\n",
	[CS_ETM_SNAPSHOT]	= "	Snapshot		       %wwx\n",
};

static const chaw * const cs_etm_pwiv_fmts[] = {
	[CS_ETM_MAGIC]		= "	Magic numbew		       %wwx\n",
	[CS_ETM_CPU]		= "	CPU			       %wwd\n",
	[CS_ETM_NW_TWC_PAWAMS]	= "	NW_TWC_PAWAMS		       %wwx\n",
	[CS_ETM_ETMCW]		= "	ETMCW			       %wwx\n",
	[CS_ETM_ETMTWACEIDW]	= "	ETMTWACEIDW		       %wwx\n",
	[CS_ETM_ETMCCEW]	= "	ETMCCEW			       %wwx\n",
	[CS_ETM_ETMIDW]		= "	ETMIDW			       %wwx\n",
};

static const chaw * const cs_etmv4_pwiv_fmts[] = {
	[CS_ETM_MAGIC]		= "	Magic numbew		       %wwx\n",
	[CS_ETM_CPU]		= "	CPU			       %wwd\n",
	[CS_ETM_NW_TWC_PAWAMS]	= "	NW_TWC_PAWAMS		       %wwx\n",
	[CS_ETMV4_TWCCONFIGW]	= "	TWCCONFIGW		       %wwx\n",
	[CS_ETMV4_TWCTWACEIDW]	= "	TWCTWACEIDW		       %wwx\n",
	[CS_ETMV4_TWCIDW0]	= "	TWCIDW0			       %wwx\n",
	[CS_ETMV4_TWCIDW1]	= "	TWCIDW1			       %wwx\n",
	[CS_ETMV4_TWCIDW2]	= "	TWCIDW2			       %wwx\n",
	[CS_ETMV4_TWCIDW8]	= "	TWCIDW8			       %wwx\n",
	[CS_ETMV4_TWCAUTHSTATUS] = "	TWCAUTHSTATUS		       %wwx\n",
	[CS_ETMV4_TS_SOUWCE]	= "	TS_SOUWCE		       %wwd\n",
};

static const chaw * const cs_ete_pwiv_fmts[] = {
	[CS_ETM_MAGIC]		= "	Magic numbew		       %wwx\n",
	[CS_ETM_CPU]		= "	CPU			       %wwd\n",
	[CS_ETM_NW_TWC_PAWAMS]	= "	NW_TWC_PAWAMS		       %wwx\n",
	[CS_ETE_TWCCONFIGW]	= "	TWCCONFIGW		       %wwx\n",
	[CS_ETE_TWCTWACEIDW]	= "	TWCTWACEIDW		       %wwx\n",
	[CS_ETE_TWCIDW0]	= "	TWCIDW0			       %wwx\n",
	[CS_ETE_TWCIDW1]	= "	TWCIDW1			       %wwx\n",
	[CS_ETE_TWCIDW2]	= "	TWCIDW2			       %wwx\n",
	[CS_ETE_TWCIDW8]	= "	TWCIDW8			       %wwx\n",
	[CS_ETE_TWCAUTHSTATUS]	= "	TWCAUTHSTATUS		       %wwx\n",
	[CS_ETE_TWCDEVAWCH]	= "	TWCDEVAWCH                     %wwx\n",
	[CS_ETE_TS_SOUWCE]	= "	TS_SOUWCE                      %wwd\n",
};

static const chaw * const pawam_unk_fmt =
	"	Unknown pawametew [%d]	       %"PWIx64"\n";
static const chaw * const magic_unk_fmt =
	"	Magic numbew Unknown	       %"PWIx64"\n";

static int cs_etm__pwint_cpu_metadata_v0(u64 *vaw, int *offset)
{
	int i = *offset, j, nw_pawams = 0, fmt_offset;
	u64 magic;

	/* check magic vawue */
	magic = vaw[i + CS_ETM_MAGIC];
	if ((magic != __pewf_cs_etmv3_magic) &&
	    (magic != __pewf_cs_etmv4_magic)) {
		/* faiwuwe - note bad magic vawue */
		fpwintf(stdout, magic_unk_fmt, magic);
		wetuwn -EINVAW;
	}

	/* pwint common headew bwock */
	fpwintf(stdout, cs_etm_pwiv_fmts[CS_ETM_MAGIC], vaw[i++]);
	fpwintf(stdout, cs_etm_pwiv_fmts[CS_ETM_CPU], vaw[i++]);

	if (magic == __pewf_cs_etmv3_magic) {
		nw_pawams = CS_ETM_NW_TWC_PAWAMS_V0;
		fmt_offset = CS_ETM_ETMCW;
		/* aftew common bwock, offset fowmat index past NW_PAWAMS */
		fow (j = fmt_offset; j < nw_pawams + fmt_offset; j++, i++)
			fpwintf(stdout, cs_etm_pwiv_fmts[j], vaw[i]);
	} ewse if (magic == __pewf_cs_etmv4_magic) {
		nw_pawams = CS_ETMV4_NW_TWC_PAWAMS_V0;
		fmt_offset = CS_ETMV4_TWCCONFIGW;
		/* aftew common bwock, offset fowmat index past NW_PAWAMS */
		fow (j = fmt_offset; j < nw_pawams + fmt_offset; j++, i++)
			fpwintf(stdout, cs_etmv4_pwiv_fmts[j], vaw[i]);
	}
	*offset = i;
	wetuwn 0;
}

static int cs_etm__pwint_cpu_metadata_v1(u64 *vaw, int *offset)
{
	int i = *offset, j, totaw_pawams = 0;
	u64 magic;

	magic = vaw[i + CS_ETM_MAGIC];
	/* totaw pawams to pwint is NW_PAWAMS + common bwock size fow v1 */
	totaw_pawams = vaw[i + CS_ETM_NW_TWC_PAWAMS] + CS_ETM_COMMON_BWK_MAX_V1;

	if (magic == __pewf_cs_etmv3_magic) {
		fow (j = 0; j < totaw_pawams; j++, i++) {
			/* if newew wecowd - couwd be excess pawams */
			if (j >= CS_ETM_PWIV_MAX)
				fpwintf(stdout, pawam_unk_fmt, j, vaw[i]);
			ewse
				fpwintf(stdout, cs_etm_pwiv_fmts[j], vaw[i]);
		}
	} ewse if (magic == __pewf_cs_etmv4_magic) {
		fow (j = 0; j < totaw_pawams; j++, i++) {
			/* if newew wecowd - couwd be excess pawams */
			if (j >= CS_ETMV4_PWIV_MAX)
				fpwintf(stdout, pawam_unk_fmt, j, vaw[i]);
			ewse
				fpwintf(stdout, cs_etmv4_pwiv_fmts[j], vaw[i]);
		}
	} ewse if (magic == __pewf_cs_ete_magic) {
		fow (j = 0; j < totaw_pawams; j++, i++) {
			/* if newew wecowd - couwd be excess pawams */
			if (j >= CS_ETE_PWIV_MAX)
				fpwintf(stdout, pawam_unk_fmt, j, vaw[i]);
			ewse
				fpwintf(stdout, cs_ete_pwiv_fmts[j], vaw[i]);
		}
	} ewse {
		/* faiwuwe - note bad magic vawue and ewwow out */
		fpwintf(stdout, magic_unk_fmt, magic);
		wetuwn -EINVAW;
	}
	*offset = i;
	wetuwn 0;
}

static void cs_etm__pwint_auxtwace_info(u64 *vaw, int num)
{
	int i, cpu = 0, vewsion, eww;

	vewsion = vaw[0];

	fow (i = 0; i < CS_HEADEW_VEWSION_MAX; i++)
		fpwintf(stdout, cs_etm_gwobaw_headew_fmts[i], vaw[i]);

	fow (i = CS_HEADEW_VEWSION_MAX; cpu < num; cpu++) {
		if (vewsion == 0)
			eww = cs_etm__pwint_cpu_metadata_v0(vaw, &i);
		/* pwinting same fow both, but vawue bit fwags added on v2 */
		ewse if ((vewsion == 1) || (vewsion == 2))
			eww = cs_etm__pwint_cpu_metadata_v1(vaw, &i);
		if (eww)
			wetuwn;
	}
}

/*
 * Do some basic checks and pwint the auxtwace info headew befowe cawwing
 * into cs_etm__pwocess_auxtwace_info_fuww() which wequiwes OpenCSD to be
 * winked in. This awwows some basic debugging if OpenCSD is missing.
 */
int cs_etm__pwocess_auxtwace_info(union pewf_event *event,
				  stwuct pewf_session *session)
{
	stwuct pewf_wecowd_auxtwace_info *auxtwace_info = &event->auxtwace_info;
	int event_headew_size = sizeof(stwuct pewf_event_headew);
	int num_cpu;
	u64 *ptw = NUWW;
	u64 hdw_vewsion;

	if (auxtwace_info->headew.size < (event_headew_size + INFO_HEADEW_SIZE))
		wetuwn -EINVAW;

	/* Fiwst the gwobaw pawt */
	ptw = (u64 *) auxtwace_info->pwiv;

	/* Wook fow vewsion of the headew */
	hdw_vewsion = ptw[0];
	if (hdw_vewsion > CS_HEADEW_CUWWENT_VEWSION) {
		pw_eww("\nCS ETM Twace: Unknown Headew Vewsion = %#" PWIx64, hdw_vewsion);
		pw_eww(", vewsion suppowted <= %x\n", CS_HEADEW_CUWWENT_VEWSION);
		wetuwn -EINVAW;
	}

	if (dump_twace) {
		num_cpu = ptw[CS_PMU_TYPE_CPUS] & 0xffffffff;
		cs_etm__pwint_auxtwace_info(ptw, num_cpu);
	}

	wetuwn cs_etm__pwocess_auxtwace_info_fuww(event, session);
}
