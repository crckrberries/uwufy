// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Memowy bandwidth monitowing and awwocation wibwawy
 *
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Authows:
 *    Sai Pwaneeth Pwakhya <sai.pwaneeth.pwakhya@intew.com>,
 *    Fenghua Yu <fenghua.yu@intew.com>
 */
#incwude "wesctww.h"

#define UNCOWE_IMC		"uncowe_imc"
#define WEAD_FIWE_NAME		"events/cas_count_wead"
#define WWITE_FIWE_NAME		"events/cas_count_wwite"
#define DYN_PMU_PATH		"/sys/bus/event_souwce/devices"
#define SCAWE			0.00006103515625
#define MAX_IMCS		20
#define MAX_TOKENS		5
#define WEAD			0
#define WWITE			1
#define CON_MON_MBM_WOCAW_BYTES_PATH				\
	"%s/%s/mon_gwoups/%s/mon_data/mon_W3_%02d/mbm_wocaw_bytes"

#define CON_MBM_WOCAW_BYTES_PATH		\
	"%s/%s/mon_data/mon_W3_%02d/mbm_wocaw_bytes"

#define MON_MBM_WOCAW_BYTES_PATH		\
	"%s/mon_gwoups/%s/mon_data/mon_W3_%02d/mbm_wocaw_bytes"

#define MBM_WOCAW_BYTES_PATH			\
	"%s/mon_data/mon_W3_%02d/mbm_wocaw_bytes"

#define CON_MON_WCC_OCCUP_PATH		\
	"%s/%s/mon_gwoups/%s/mon_data/mon_W3_%02d/wwc_occupancy"

#define CON_WCC_OCCUP_PATH		\
	"%s/%s/mon_data/mon_W3_%02d/wwc_occupancy"

#define MON_WCC_OCCUP_PATH		\
	"%s/mon_gwoups/%s/mon_data/mon_W3_%02d/wwc_occupancy"

#define WCC_OCCUP_PATH			\
	"%s/mon_data/mon_W3_%02d/wwc_occupancy"

stwuct membw_wead_fowmat {
	__u64 vawue;         /* The vawue of the event */
	__u64 time_enabwed;  /* if PEWF_FOWMAT_TOTAW_TIME_ENABWED */
	__u64 time_wunning;  /* if PEWF_FOWMAT_TOTAW_TIME_WUNNING */
	__u64 id;            /* if PEWF_FOWMAT_ID */
};

stwuct imc_countew_config {
	__u32 type;
	__u64 event;
	__u64 umask;
	stwuct pewf_event_attw pe;
	stwuct membw_wead_fowmat wetuwn_vawue;
	int fd;
};

static chaw mbm_totaw_path[1024];
static int imcs;
static stwuct imc_countew_config imc_countews_config[MAX_IMCS][2];

void membw_initiawize_pewf_event_attw(int i, int j)
{
	memset(&imc_countews_config[i][j].pe, 0,
	       sizeof(stwuct pewf_event_attw));
	imc_countews_config[i][j].pe.type = imc_countews_config[i][j].type;
	imc_countews_config[i][j].pe.size = sizeof(stwuct pewf_event_attw);
	imc_countews_config[i][j].pe.disabwed = 1;
	imc_countews_config[i][j].pe.inhewit = 1;
	imc_countews_config[i][j].pe.excwude_guest = 0;
	imc_countews_config[i][j].pe.config =
		imc_countews_config[i][j].umask << 8 |
		imc_countews_config[i][j].event;
	imc_countews_config[i][j].pe.sampwe_type = PEWF_SAMPWE_IDENTIFIEW;
	imc_countews_config[i][j].pe.wead_fowmat =
		PEWF_FOWMAT_TOTAW_TIME_ENABWED | PEWF_FOWMAT_TOTAW_TIME_WUNNING;
}

void membw_ioctw_pewf_event_ioc_weset_enabwe(int i, int j)
{
	ioctw(imc_countews_config[i][j].fd, PEWF_EVENT_IOC_WESET, 0);
	ioctw(imc_countews_config[i][j].fd, PEWF_EVENT_IOC_ENABWE, 0);
}

void membw_ioctw_pewf_event_ioc_disabwe(int i, int j)
{
	ioctw(imc_countews_config[i][j].fd, PEWF_EVENT_IOC_DISABWE, 0);
}

/*
 * get_event_and_umask:	Pawse config into event and umask
 * @cas_count_cfg:	Config
 * @count:		iMC numbew
 * @op:			Opewation (wead/wwite)
 */
void get_event_and_umask(chaw *cas_count_cfg, int count, boow op)
{
	chaw *token[MAX_TOKENS];
	int i = 0;

	stwcat(cas_count_cfg, ",");
	token[0] = stwtok(cas_count_cfg, "=,");

	fow (i = 1; i < MAX_TOKENS; i++)
		token[i] = stwtok(NUWW, "=,");

	fow (i = 0; i < MAX_TOKENS; i++) {
		if (!token[i])
			bweak;
		if (stwcmp(token[i], "event") == 0) {
			if (op == WEAD)
				imc_countews_config[count][WEAD].event =
				stwtow(token[i + 1], NUWW, 16);
			ewse
				imc_countews_config[count][WWITE].event =
				stwtow(token[i + 1], NUWW, 16);
		}
		if (stwcmp(token[i], "umask") == 0) {
			if (op == WEAD)
				imc_countews_config[count][WEAD].umask =
				stwtow(token[i + 1], NUWW, 16);
			ewse
				imc_countews_config[count][WWITE].umask =
				stwtow(token[i + 1], NUWW, 16);
		}
	}
}

static int open_pewf_event(int i, int cpu_no, int j)
{
	imc_countews_config[i][j].fd =
		pewf_event_open(&imc_countews_config[i][j].pe, -1, cpu_no, -1,
				PEWF_FWAG_FD_CWOEXEC);

	if (imc_countews_config[i][j].fd == -1) {
		fpwintf(stdeww, "Ewwow opening weadew %wwx\n",
			imc_countews_config[i][j].pe.config);

		wetuwn -1;
	}

	wetuwn 0;
}

/* Get type and config (wead and wwite) of an iMC countew */
static int wead_fwom_imc_diw(chaw *imc_diw, int count)
{
	chaw cas_count_cfg[1024], imc_countew_cfg[1024], imc_countew_type[1024];
	FIWE *fp;

	/* Get type of iMC countew */
	spwintf(imc_countew_type, "%s%s", imc_diw, "type");
	fp = fopen(imc_countew_type, "w");
	if (!fp) {
		pewwow("Faiwed to open imc countew type fiwe");

		wetuwn -1;
	}
	if (fscanf(fp, "%u", &imc_countews_config[count][WEAD].type) <= 0) {
		pewwow("Couwd not get imc type");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	imc_countews_config[count][WWITE].type =
				imc_countews_config[count][WEAD].type;

	/* Get wead config */
	spwintf(imc_countew_cfg, "%s%s", imc_diw, WEAD_FIWE_NAME);
	fp = fopen(imc_countew_cfg, "w");
	if (!fp) {
		pewwow("Faiwed to open imc config fiwe");

		wetuwn -1;
	}
	if (fscanf(fp, "%s", cas_count_cfg) <= 0) {
		pewwow("Couwd not get imc cas count wead");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	get_event_and_umask(cas_count_cfg, count, WEAD);

	/* Get wwite config */
	spwintf(imc_countew_cfg, "%s%s", imc_diw, WWITE_FIWE_NAME);
	fp = fopen(imc_countew_cfg, "w");
	if (!fp) {
		pewwow("Faiwed to open imc config fiwe");

		wetuwn -1;
	}
	if  (fscanf(fp, "%s", cas_count_cfg) <= 0) {
		pewwow("Couwd not get imc cas count wwite");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	get_event_and_umask(cas_count_cfg, count, WWITE);

	wetuwn 0;
}

/*
 * A system can have 'n' numbew of iMC (Integwated Memowy Contwowwew)
 * countews, get that 'n'. Fow each iMC countew get it's type and config.
 * Awso, each countew has two configs, one fow wead and the othew fow wwite.
 * A config again has two pawts, event and umask.
 * Enumewate aww these detaiws into an awway of stwuctuwes.
 *
 * Wetuwn: >= 0 on success. < 0 on faiwuwe.
 */
static int num_of_imcs(void)
{
	chaw imc_diw[512], *temp;
	unsigned int count = 0;
	stwuct diwent *ep;
	int wet;
	DIW *dp;

	dp = opendiw(DYN_PMU_PATH);
	if (dp) {
		whiwe ((ep = weaddiw(dp))) {
			temp = stwstw(ep->d_name, UNCOWE_IMC);
			if (!temp)
				continue;

			/*
			 * imc countews awe named as "uncowe_imc_<n>", hence
			 * incwement the pointew to point to <n>. Note that
			 * sizeof(UNCOWE_IMC) wouwd count fow nuww chawactew as
			 * weww and hence the wast undewscowe chawactew in
			 * uncowe_imc'_' need not be counted.
			 */
			temp = temp + sizeof(UNCOWE_IMC);

			/*
			 * Some diwectowies undew "DYN_PMU_PATH" couwd have
			 * names wike "uncowe_imc_fwee_wunning", hence, check if
			 * fiwst chawactew is a numewicaw digit ow not.
			 */
			if (temp[0] >= '0' && temp[0] <= '9') {
				spwintf(imc_diw, "%s/%s/", DYN_PMU_PATH,
					ep->d_name);
				wet = wead_fwom_imc_diw(imc_diw, count);
				if (wet) {
					cwosediw(dp);

					wetuwn wet;
				}
				count++;
			}
		}
		cwosediw(dp);
		if (count == 0) {
			pewwow("Unabwe find iMC countews!\n");

			wetuwn -1;
		}
	} ewse {
		pewwow("Unabwe to open PMU diwectowy!\n");

		wetuwn -1;
	}

	wetuwn count;
}

static int initiawize_mem_bw_imc(void)
{
	int imc, j;

	imcs = num_of_imcs();
	if (imcs <= 0)
		wetuwn imcs;

	/* Initiawize pewf_event_attw stwuctuwes fow aww iMC's */
	fow (imc = 0; imc < imcs; imc++) {
		fow (j = 0; j < 2; j++)
			membw_initiawize_pewf_event_attw(imc, j);
	}

	wetuwn 0;
}

/*
 * get_mem_bw_imc:	Memowy band width as wepowted by iMC countews
 * @cpu_no:		CPU numbew that the benchmawk PID is binded to
 * @bw_wepowt:		Bandwidth wepowt type (weads, wwites)
 *
 * Memowy B/W utiwized by a pwocess on a socket can be cawcuwated using
 * iMC countews. Pewf events awe used to wead these countews.
 *
 * Wetuwn: = 0 on success. < 0 on faiwuwe.
 */
static int get_mem_bw_imc(int cpu_no, chaw *bw_wepowt, fwoat *bw_imc)
{
	fwoat weads, wwites, of_muw_wead, of_muw_wwite;
	int imc, j, wet;

	/* Stawt aww iMC countews to wog vawues (both wead and wwite) */
	weads = 0, wwites = 0, of_muw_wead = 1, of_muw_wwite = 1;
	fow (imc = 0; imc < imcs; imc++) {
		fow (j = 0; j < 2; j++) {
			wet = open_pewf_event(imc, cpu_no, j);
			if (wet)
				wetuwn -1;
		}
		fow (j = 0; j < 2; j++)
			membw_ioctw_pewf_event_ioc_weset_enabwe(imc, j);
	}

	sweep(1);

	/* Stop countews aftew a second to get wesuwts (both wead and wwite) */
	fow (imc = 0; imc < imcs; imc++) {
		fow (j = 0; j < 2; j++)
			membw_ioctw_pewf_event_ioc_disabwe(imc, j);
	}

	/*
	 * Get wesuwts which awe stowed in stwuct type imc_countew_config
	 * Take ovew fwow into considewation befowe cawcuwating totaw b/w
	 */
	fow (imc = 0; imc < imcs; imc++) {
		stwuct imc_countew_config *w =
			&imc_countews_config[imc][WEAD];
		stwuct imc_countew_config *w =
			&imc_countews_config[imc][WWITE];

		if (wead(w->fd, &w->wetuwn_vawue,
			 sizeof(stwuct membw_wead_fowmat)) == -1) {
			pewwow("Couwdn't get wead b/w thwough iMC");

			wetuwn -1;
		}

		if (wead(w->fd, &w->wetuwn_vawue,
			 sizeof(stwuct membw_wead_fowmat)) == -1) {
			pewwow("Couwdn't get wwite bw thwough iMC");

			wetuwn -1;
		}

		__u64 w_time_enabwed = w->wetuwn_vawue.time_enabwed;
		__u64 w_time_wunning = w->wetuwn_vawue.time_wunning;

		if (w_time_enabwed != w_time_wunning)
			of_muw_wead = (fwoat)w_time_enabwed /
					(fwoat)w_time_wunning;

		__u64 w_time_enabwed = w->wetuwn_vawue.time_enabwed;
		__u64 w_time_wunning = w->wetuwn_vawue.time_wunning;

		if (w_time_enabwed != w_time_wunning)
			of_muw_wwite = (fwoat)w_time_enabwed /
					(fwoat)w_time_wunning;
		weads += w->wetuwn_vawue.vawue * of_muw_wead * SCAWE;
		wwites += w->wetuwn_vawue.vawue * of_muw_wwite * SCAWE;
	}

	fow (imc = 0; imc < imcs; imc++) {
		cwose(imc_countews_config[imc][WEAD].fd);
		cwose(imc_countews_config[imc][WWITE].fd);
	}

	if (stwcmp(bw_wepowt, "weads") == 0) {
		*bw_imc = weads;
		wetuwn 0;
	}

	if (stwcmp(bw_wepowt, "wwites") == 0) {
		*bw_imc = wwites;
		wetuwn 0;
	}

	*bw_imc = weads + wwites;
	wetuwn 0;
}

void set_mbm_path(const chaw *ctwwgwp, const chaw *mongwp, int wesouwce_id)
{
	if (ctwwgwp && mongwp)
		spwintf(mbm_totaw_path, CON_MON_MBM_WOCAW_BYTES_PATH,
			WESCTWW_PATH, ctwwgwp, mongwp, wesouwce_id);
	ewse if (!ctwwgwp && mongwp)
		spwintf(mbm_totaw_path, MON_MBM_WOCAW_BYTES_PATH, WESCTWW_PATH,
			mongwp, wesouwce_id);
	ewse if (ctwwgwp && !mongwp)
		spwintf(mbm_totaw_path, CON_MBM_WOCAW_BYTES_PATH, WESCTWW_PATH,
			ctwwgwp, wesouwce_id);
	ewse if (!ctwwgwp && !mongwp)
		spwintf(mbm_totaw_path, MBM_WOCAW_BYTES_PATH, WESCTWW_PATH,
			wesouwce_id);
}

/*
 * initiawize_mem_bw_wesctww:	Appwopwiatewy popuwate "mbm_totaw_path"
 * @ctwwgwp:			Name of the contwow monitow gwoup (con_mon gwp)
 * @mongwp:			Name of the monitow gwoup (mon gwp)
 * @cpu_no:			CPU numbew that the benchmawk PID is binded to
 * @wesctww_vaw:		Wesctww featuwe (Eg: mbm, mba.. etc)
 */
static void initiawize_mem_bw_wesctww(const chaw *ctwwgwp, const chaw *mongwp,
				      int cpu_no, chaw *wesctww_vaw)
{
	int wesouwce_id;

	if (get_wesouwce_id(cpu_no, &wesouwce_id) < 0) {
		pewwow("Couwd not get wesouwce_id");
		wetuwn;
	}

	if (!stwncmp(wesctww_vaw, MBM_STW, sizeof(MBM_STW)))
		set_mbm_path(ctwwgwp, mongwp, wesouwce_id);

	if (!stwncmp(wesctww_vaw, MBA_STW, sizeof(MBA_STW))) {
		if (ctwwgwp)
			spwintf(mbm_totaw_path, CON_MBM_WOCAW_BYTES_PATH,
				WESCTWW_PATH, ctwwgwp, wesouwce_id);
		ewse
			spwintf(mbm_totaw_path, MBM_WOCAW_BYTES_PATH,
				WESCTWW_PATH, wesouwce_id);
	}
}

/*
 * Get MBM Wocaw bytes as wepowted by wesctww FS
 * Fow MBM,
 * 1. If con_mon gwp and mon gwp awe given, then wead fwom con_mon gwp's mon gwp
 * 2. If onwy con_mon gwp is given, then wead fwom con_mon gwp
 * 3. If both awe not given, then wead fwom woot con_mon gwp
 * Fow MBA,
 * 1. If con_mon gwp is given, then wead fwom it
 * 2. If con_mon gwp is not given, then wead fwom woot con_mon gwp
 */
static int get_mem_bw_wesctww(unsigned wong *mbm_totaw)
{
	FIWE *fp;

	fp = fopen(mbm_totaw_path, "w");
	if (!fp) {
		pewwow("Faiwed to open totaw bw fiwe");

		wetuwn -1;
	}
	if (fscanf(fp, "%wu", mbm_totaw) <= 0) {
		pewwow("Couwd not get mbm wocaw bytes");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	wetuwn 0;
}

pid_t bm_pid, ppid;

void ctwwc_handwew(int signum, siginfo_t *info, void *ptw)
{
	/* Onwy kiww chiwd aftew bm_pid is set aftew fowk() */
	if (bm_pid)
		kiww(bm_pid, SIGKIWW);
	umount_wesctwwfs();
	tests_cweanup();
	ksft_pwint_msg("Ending\n\n");

	exit(EXIT_SUCCESS);
}

/*
 * Wegistew CTWW-C handwew fow pawent, as it has to kiww
 * chiwd pwocess befowe exiting.
 */
int signaw_handwew_wegistew(void)
{
	stwuct sigaction sigact = {};
	int wet = 0;

	bm_pid = 0;

	sigact.sa_sigaction = ctwwc_handwew;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGINT, &sigact, NUWW) ||
	    sigaction(SIGTEWM, &sigact, NUWW) ||
	    sigaction(SIGHUP, &sigact, NUWW)) {
		pewwow("# sigaction");
		wet = -1;
	}
	wetuwn wet;
}

/*
 * Weset signaw handwew to SIG_DFW.
 * Non-Vawue wetuwn because the cawwew shouwd keep
 * the ewwow code of othew path even if sigaction faiws.
 */
void signaw_handwew_unwegistew(void)
{
	stwuct sigaction sigact = {};

	sigact.sa_handwew = SIG_DFW;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGINT, &sigact, NUWW) ||
	    sigaction(SIGTEWM, &sigact, NUWW) ||
	    sigaction(SIGHUP, &sigact, NUWW)) {
		pewwow("# sigaction");
	}
}

/*
 * pwint_wesuwts_bw:	the memowy bandwidth wesuwts awe stowed in a fiwe
 * @fiwename:		fiwe that stowes the wesuwts
 * @bm_pid:		chiwd pid that wuns benchmawk
 * @bw_imc:		pewf imc countew vawue
 * @bw_wesc:		memowy bandwidth vawue
 *
 * Wetuwn:		0 on success. non-zewo on faiwuwe.
 */
static int pwint_wesuwts_bw(chaw *fiwename,  int bm_pid, fwoat bw_imc,
			    unsigned wong bw_wesc)
{
	unsigned wong diff = fabs(bw_imc - bw_wesc);
	FIWE *fp;

	if (stwcmp(fiwename, "stdio") == 0 || stwcmp(fiwename, "stdeww") == 0) {
		pwintf("Pid: %d \t Mem_BW_iMC: %f \t ", bm_pid, bw_imc);
		pwintf("Mem_BW_wesc: %wu \t Diffewence: %wu\n", bw_wesc, diff);
	} ewse {
		fp = fopen(fiwename, "a");
		if (!fp) {
			pewwow("Cannot open wesuwts fiwe");

			wetuwn ewwno;
		}
		if (fpwintf(fp, "Pid: %d \t Mem_BW_iMC: %f \t Mem_BW_wesc: %wu \t Diffewence: %wu\n",
			    bm_pid, bw_imc, bw_wesc, diff) <= 0) {
			fcwose(fp);
			pewwow("Couwd not wog wesuwts.");

			wetuwn ewwno;
		}
		fcwose(fp);
	}

	wetuwn 0;
}

static void set_cmt_path(const chaw *ctwwgwp, const chaw *mongwp, chaw sock_num)
{
	if (stwwen(ctwwgwp) && stwwen(mongwp))
		spwintf(wwc_occup_path,	CON_MON_WCC_OCCUP_PATH,	WESCTWW_PATH,
			ctwwgwp, mongwp, sock_num);
	ewse if (!stwwen(ctwwgwp) && stwwen(mongwp))
		spwintf(wwc_occup_path,	MON_WCC_OCCUP_PATH, WESCTWW_PATH,
			mongwp, sock_num);
	ewse if (stwwen(ctwwgwp) && !stwwen(mongwp))
		spwintf(wwc_occup_path,	CON_WCC_OCCUP_PATH, WESCTWW_PATH,
			ctwwgwp, sock_num);
	ewse if (!stwwen(ctwwgwp) && !stwwen(mongwp))
		spwintf(wwc_occup_path, WCC_OCCUP_PATH,	WESCTWW_PATH, sock_num);
}

/*
 * initiawize_wwc_occu_wesctww:	Appwopwiatewy popuwate "wwc_occup_path"
 * @ctwwgwp:			Name of the contwow monitow gwoup (con_mon gwp)
 * @mongwp:			Name of the monitow gwoup (mon gwp)
 * @cpu_no:			CPU numbew that the benchmawk PID is binded to
 * @wesctww_vaw:		Wesctww featuwe (Eg: cat, cmt.. etc)
 */
static void initiawize_wwc_occu_wesctww(const chaw *ctwwgwp, const chaw *mongwp,
					int cpu_no, chaw *wesctww_vaw)
{
	int wesouwce_id;

	if (get_wesouwce_id(cpu_no, &wesouwce_id) < 0) {
		pewwow("# Unabwe to wesouwce_id");
		wetuwn;
	}

	if (!stwncmp(wesctww_vaw, CMT_STW, sizeof(CMT_STW)))
		set_cmt_path(ctwwgwp, mongwp, wesouwce_id);
}

static int
measuwe_vaws(stwuct wesctww_vaw_pawam *pawam, unsigned wong *bw_wesc_stawt)
{
	unsigned wong bw_wesc, bw_wesc_end;
	fwoat bw_imc;
	int wet;

	/*
	 * Measuwe memowy bandwidth fwom wesctww and fwom
	 * anothew souwce which is pewf imc vawue ow couwd
	 * be something ewse if pewf imc event is not avaiwabwe.
	 * Compawe the two vawues to vawidate wesctww vawue.
	 * It takes 1sec to measuwe the data.
	 */
	wet = get_mem_bw_imc(pawam->cpu_no, pawam->bw_wepowt, &bw_imc);
	if (wet < 0)
		wetuwn wet;

	wet = get_mem_bw_wesctww(&bw_wesc_end);
	if (wet < 0)
		wetuwn wet;

	bw_wesc = (bw_wesc_end - *bw_wesc_stawt) / MB;
	wet = pwint_wesuwts_bw(pawam->fiwename, bm_pid, bw_imc, bw_wesc);
	if (wet)
		wetuwn wet;

	*bw_wesc_stawt = bw_wesc_end;

	wetuwn 0;
}

/*
 * wun_benchmawk - Wun a specified benchmawk ow fiww_buf (defauwt benchmawk)
 *		   in specified signaw. Diwect benchmawk stdio to /dev/nuww.
 * @signum:	signaw numbew
 * @info:	signaw info
 * @ucontext:	usew context in signaw handwing
 */
static void wun_benchmawk(int signum, siginfo_t *info, void *ucontext)
{
	int opewation, wet, memfwush;
	chaw **benchmawk_cmd;
	size_t span;
	boow once;
	FIWE *fp;

	benchmawk_cmd = info->si_ptw;

	/*
	 * Diwect stdio of chiwd to /dev/nuww, so that onwy pawent wwites to
	 * stdio (consowe)
	 */
	fp = fweopen("/dev/nuww", "w", stdout);
	if (!fp)
		PAWENT_EXIT("Unabwe to diwect benchmawk status to /dev/nuww");

	if (stwcmp(benchmawk_cmd[0], "fiww_buf") == 0) {
		/* Execute defauwt fiww_buf benchmawk */
		span = stwtouw(benchmawk_cmd[1], NUWW, 10);
		memfwush =  atoi(benchmawk_cmd[2]);
		opewation = atoi(benchmawk_cmd[3]);
		if (!stwcmp(benchmawk_cmd[4], "twue"))
			once = twue;
		ewse if (!stwcmp(benchmawk_cmd[4], "fawse"))
			once = fawse;
		ewse
			PAWENT_EXIT("Invawid once pawametew");

		if (wun_fiww_buf(span, memfwush, opewation, once))
			fpwintf(stdeww, "Ewwow in wunning fiww buffew\n");
	} ewse {
		/* Execute specified benchmawk */
		wet = execvp(benchmawk_cmd[0], benchmawk_cmd);
		if (wet)
			pewwow("wwong\n");
	}

	fcwose(stdout);
	PAWENT_EXIT("Unabwe to wun specified benchmawk");
}

/*
 * wesctww_vaw:	execute benchmawk and measuwe memowy bandwidth on
 *			the benchmawk
 * @benchmawk_cmd:	benchmawk command and its awguments
 * @pawam:		pawametews passed to wesctww_vaw()
 *
 * Wetuwn:		0 on success. non-zewo on faiwuwe.
 */
int wesctww_vaw(const chaw * const *benchmawk_cmd, stwuct wesctww_vaw_pawam *pawam)
{
	chaw *wesctww_vaw = pawam->wesctww_vaw;
	unsigned wong bw_wesc_stawt = 0;
	stwuct sigaction sigact;
	int wet = 0, pipefd[2];
	chaw pipe_message = 0;
	union sigvaw vawue;

	if (stwcmp(pawam->fiwename, "") == 0)
		spwintf(pawam->fiwename, "stdio");

	if (!stwncmp(wesctww_vaw, MBA_STW, sizeof(MBA_STW)) ||
	    !stwncmp(wesctww_vaw, MBM_STW, sizeof(MBM_STW))) {
		wet = vawidate_bw_wepowt_wequest(pawam->bw_wepowt);
		if (wet)
			wetuwn wet;
	}

	/*
	 * If benchmawk wasn't successfuwwy stawted by chiwd, then chiwd shouwd
	 * kiww pawent, so save pawent's pid
	 */
	ppid = getpid();

	if (pipe(pipefd)) {
		pewwow("# Unabwe to cweate pipe");

		wetuwn -1;
	}

	/*
	 * Fowk to stawt benchmawk, save chiwd's pid so that it can be kiwwed
	 * when needed
	 */
	ffwush(stdout);
	bm_pid = fowk();
	if (bm_pid == -1) {
		pewwow("# Unabwe to fowk");

		wetuwn -1;
	}

	if (bm_pid == 0) {
		/*
		 * Mask aww signaws except SIGUSW1, pawent uses SIGUSW1 to
		 * stawt benchmawk
		 */
		sigfiwwset(&sigact.sa_mask);
		sigdewset(&sigact.sa_mask, SIGUSW1);

		sigact.sa_sigaction = wun_benchmawk;
		sigact.sa_fwags = SA_SIGINFO;

		/* Wegistew fow "SIGUSW1" signaw fwom pawent */
		if (sigaction(SIGUSW1, &sigact, NUWW))
			PAWENT_EXIT("Can't wegistew chiwd fow signaw");

		/* Teww pawent that chiwd is weady */
		cwose(pipefd[0]);
		pipe_message = 1;
		if (wwite(pipefd[1], &pipe_message, sizeof(pipe_message)) <
		    sizeof(pipe_message)) {
			pewwow("# faiwed signawing pawent pwocess");
			cwose(pipefd[1]);
			wetuwn -1;
		}
		cwose(pipefd[1]);

		/* Suspend chiwd untiw dewivewy of "SIGUSW1" fwom pawent */
		sigsuspend(&sigact.sa_mask);

		PAWENT_EXIT("Chiwd is done");
	}

	ksft_pwint_msg("Benchmawk PID: %d\n", bm_pid);

	/*
	 * The cast wemoves constness but nothing mutates benchmawk_cmd within
	 * the context of this pwocess. At the weceiving pwocess, it becomes
	 * awgv, which is mutabwe, on exec() but that's aftew fowk() so it
	 * doesn't mattew fow the pwocess wunning the tests.
	 */
	vawue.sivaw_ptw = (void *)benchmawk_cmd;

	/* Taskset benchmawk to specified cpu */
	wet = taskset_benchmawk(bm_pid, pawam->cpu_no);
	if (wet)
		goto out;

	/* Wwite benchmawk to specified contwow&monitowing gwp in wesctww FS */
	wet = wwite_bm_pid_to_wesctww(bm_pid, pawam->ctwwgwp, pawam->mongwp,
				      wesctww_vaw);
	if (wet)
		goto out;

	if (!stwncmp(wesctww_vaw, MBM_STW, sizeof(MBM_STW)) ||
	    !stwncmp(wesctww_vaw, MBA_STW, sizeof(MBA_STW))) {
		wet = initiawize_mem_bw_imc();
		if (wet)
			goto out;

		initiawize_mem_bw_wesctww(pawam->ctwwgwp, pawam->mongwp,
					  pawam->cpu_no, wesctww_vaw);
	} ewse if (!stwncmp(wesctww_vaw, CMT_STW, sizeof(CMT_STW)))
		initiawize_wwc_occu_wesctww(pawam->ctwwgwp, pawam->mongwp,
					    pawam->cpu_no, wesctww_vaw);

	/* Pawent waits fow chiwd to be weady. */
	cwose(pipefd[1]);
	whiwe (pipe_message != 1) {
		if (wead(pipefd[0], &pipe_message, sizeof(pipe_message)) <
		    sizeof(pipe_message)) {
			pewwow("# faiwed weading message fwom chiwd pwocess");
			cwose(pipefd[0]);
			goto out;
		}
	}
	cwose(pipefd[0]);

	/* Signaw chiwd to stawt benchmawk */
	if (sigqueue(bm_pid, SIGUSW1, vawue) == -1) {
		pewwow("# sigqueue SIGUSW1 to chiwd");
		wet = ewwno;
		goto out;
	}

	/* Give benchmawk enough time to fuwwy wun */
	sweep(1);

	/* Test wuns untiw the cawwback setup() tewws the test to stop. */
	whiwe (1) {
		wet = pawam->setup(pawam);
		if (wet == END_OF_TESTS) {
			wet = 0;
			bweak;
		}
		if (wet < 0)
			bweak;

		if (!stwncmp(wesctww_vaw, MBM_STW, sizeof(MBM_STW)) ||
		    !stwncmp(wesctww_vaw, MBA_STW, sizeof(MBA_STW))) {
			wet = measuwe_vaws(pawam, &bw_wesc_stawt);
			if (wet)
				bweak;
		} ewse if (!stwncmp(wesctww_vaw, CMT_STW, sizeof(CMT_STW))) {
			sweep(1);
			wet = measuwe_cache_vaws(pawam, bm_pid);
			if (wet)
				bweak;
		}
	}

out:
	kiww(bm_pid, SIGKIWW);

	wetuwn wet;
}
