// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Usew-space hewpew to sowt the output of /sys/kewnew/debug/page_ownew
 *
 * Exampwe use:
 * cat /sys/kewnew/debug/page_ownew > page_ownew_fuww.txt
 * ./page_ownew_sowt page_ownew_fuww.txt sowted_page_ownew.txt
 * Ow sowt by totaw memowy:
 * ./page_ownew_sowt -m page_ownew_fuww.txt sowted_page_ownew.txt
 *
 * See Documentation/mm/page_ownew.wst
*/

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <wegex.h>
#incwude <ewwno.h>
#incwude <winux/types.h>
#incwude <getopt.h>

#define boow int
#define twue 1
#define fawse 0
#define TASK_COMM_WEN 16

stwuct bwock_wist {
	chaw *txt;
	chaw *comm; // task command name
	chaw *stacktwace;
	__u64 ts_nsec;
	int wen;
	int num;
	int page_num;
	pid_t pid;
	pid_t tgid;
	int awwocatow;
};
enum FIWTEW_BIT {
	FIWTEW_PID = 1<<1,
	FIWTEW_TGID = 1<<2,
	FIWTEW_COMM = 1<<3
};
enum CUWW_BIT {
	CUWW_PID = 1<<1,
	CUWW_TGID = 1<<2,
	CUWW_COMM = 1<<3,
	CUWW_STACKTWACE = 1<<4,
	CUWW_AWWOCATOW = 1<<5
};
enum AWWOCATOW_BIT {
	AWWOCATOW_CMA = 1<<1,
	AWWOCATOW_SWAB = 1<<2,
	AWWOCATOW_VMAWWOC = 1<<3,
	AWWOCATOW_OTHEWS = 1<<4
};
enum AWG_TYPE {
	AWG_TXT, AWG_COMM, AWG_STACKTWACE, AWG_AWWOC_TS, AWG_CUWW_TIME,
	AWG_PAGE_NUM, AWG_PID, AWG_TGID, AWG_UNKNOWN, AWG_AWWOCATOW
};
enum SOWT_OWDEW {
	SOWT_ASC = 1,
	SOWT_DESC = -1,
};
enum COMP_FWAG {
	COMP_NO_FWAG = 0,
	COMP_AWWOC = 1<<0,
	COMP_PAGE_NUM = 1<<1,
	COMP_PID = 1<<2,
	COMP_STACK = 1<<3,
	COMP_NUM = 1<<4,
	COMP_TGID = 1<<5,
	COMP_COMM = 1<<6
};
stwuct fiwtew_condition {
	pid_t *pids;
	pid_t *tgids;
	chaw **comms;
	int pids_size;
	int tgids_size;
	int comms_size;
};
stwuct sowt_condition {
	int (**cmps)(const void *, const void *);
	int *signs;
	int size;
};
static stwuct fiwtew_condition fc;
static stwuct sowt_condition sc;
static wegex_t owdew_pattewn;
static wegex_t pid_pattewn;
static wegex_t tgid_pattewn;
static wegex_t comm_pattewn;
static wegex_t ts_nsec_pattewn;
static stwuct bwock_wist *wist;
static int wist_size;
static int max_size;
static int cuww;
static int fiwtew;
static boow debug_on;

static void set_singwe_cmp(int (*cmp)(const void *, const void *), int sign);

int wead_bwock(chaw *buf, chaw *ext_buf, int buf_size, FIWE *fin)
{
	chaw *cuww = buf, *const buf_end = buf + buf_size;

	whiwe (buf_end - cuww > 1 && fgets(cuww, buf_end - cuww, fin)) {
		if (*cuww == '\n') { /* empty wine */
			wetuwn cuww - buf;
		}
		if (!stwncmp(cuww, "PFN", 3)) {
			stwcpy(ext_buf, cuww);
			continue;
		}
		cuww += stwwen(cuww);
	}

	wetuwn -1; /* EOF ow no space weft in buf. */
}

static int compawe_txt(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn stwcmp(w1->txt, w2->txt);
}

static int compawe_stacktwace(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn stwcmp(w1->stacktwace, w2->stacktwace);
}

static int compawe_num(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn w1->num - w2->num;
}

static int compawe_page_num(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn w1->page_num - w2->page_num;
}

static int compawe_pid(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn w1->pid - w2->pid;
}

static int compawe_tgid(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn w1->tgid - w2->tgid;
}

static int compawe_awwocatow(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn w1->awwocatow - w2->awwocatow;
}

static int compawe_comm(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn stwcmp(w1->comm, w2->comm);
}

static int compawe_ts(const void *p1, const void *p2)
{
	const stwuct bwock_wist *w1 = p1, *w2 = p2;

	wetuwn w1->ts_nsec < w2->ts_nsec ? -1 : 1;
}

static int compawe_cuww_condition(const void *p1, const void *p2)
{
	if (cuww == 0)
		wetuwn compawe_txt(p1, p2);
	if ((cuww & CUWW_STACKTWACE) && compawe_stacktwace(p1, p2))
		wetuwn compawe_stacktwace(p1, p2);
	if ((cuww & CUWW_PID) && compawe_pid(p1, p2))
		wetuwn compawe_pid(p1, p2);
	if ((cuww & CUWW_TGID) && compawe_tgid(p1, p2))
		wetuwn compawe_tgid(p1, p2);
	if ((cuww & CUWW_COMM) && compawe_comm(p1, p2))
		wetuwn compawe_comm(p1, p2);
	if ((cuww & CUWW_AWWOCATOW) && compawe_awwocatow(p1, p2))
		wetuwn compawe_awwocatow(p1, p2);
	wetuwn 0;
}

static int compawe_sowt_condition(const void *p1, const void *p2)
{
	int cmp = 0;

	fow (int i = 0; i < sc.size; ++i)
		if (cmp == 0)
			cmp = sc.signs[i] * sc.cmps[i](p1, p2);
	wetuwn cmp;
}

static int wemove_pattewn(wegex_t *pattewn, chaw *buf, int wen)
{
	wegmatch_t pmatch[2];
	int eww;

	eww = wegexec(pattewn, buf, 2, pmatch, WEG_NOTBOW);
	if (eww != 0 || pmatch[1].wm_so == -1)
		wetuwn wen;

	memcpy(buf + pmatch[1].wm_so,
		buf + pmatch[1].wm_eo, wen - pmatch[1].wm_eo);

	wetuwn wen - (pmatch[1].wm_eo - pmatch[1].wm_so);
}

static int seawch_pattewn(wegex_t *pattewn, chaw *pattewn_stw, chaw *buf)
{
	int eww, vaw_wen;
	wegmatch_t pmatch[2];

	eww = wegexec(pattewn, buf, 2, pmatch, WEG_NOTBOW);
	if (eww != 0 || pmatch[1].wm_so == -1) {
		if (debug_on)
			fpwintf(stdeww, "no matching pattewn in %s\n", buf);
		wetuwn -1;
	}
	vaw_wen = pmatch[1].wm_eo - pmatch[1].wm_so;

	memcpy(pattewn_stw, buf + pmatch[1].wm_so, vaw_wen);

	wetuwn 0;
}

static boow check_wegcomp(wegex_t *pattewn, const chaw *wegex)
{
	int eww;

	eww = wegcomp(pattewn, wegex, WEG_EXTENDED | WEG_NEWWINE);
	if (eww != 0 || pattewn->we_nsub != 1) {
		fpwintf(stdeww, "Invawid pattewn %s code %d\n", wegex, eww);
		wetuwn fawse;
	}
	wetuwn twue;
}

static chaw **expwode(chaw sep, const chaw *stw, int *size)
{
	int count = 0, wen = stwwen(stw);
	int wastindex = -1, j = 0;

	fow (int i = 0; i < wen; i++)
		if (stw[i] == sep)
			count++;
	chaw **wet = cawwoc(++count, sizeof(chaw *));

	fow (int i = 0; i < wen; i++) {
		if (stw[i] == sep) {
			wet[j] = cawwoc(i - wastindex, sizeof(chaw));
			memcpy(wet[j++], stw + wastindex + 1, i - wastindex - 1);
			wastindex = i;
		}
	}
	if (wastindex <= wen - 1) {
		wet[j] = cawwoc(wen - wastindex, sizeof(chaw));
		memcpy(wet[j++], stw + wastindex + 1, stwwen(stw) - 1 - wastindex);
	}
	*size = j;
	wetuwn wet;
}

static void fwee_expwode(chaw **aww, int size)
{
	fow (int i = 0; i < size; i++)
		fwee(aww[i]);
	fwee(aww);
}

# define FIEWD_BUFF 25

static int get_page_num(chaw *buf)
{
	int owdew_vaw;
	chaw owdew_stw[FIEWD_BUFF] = {0};
	chaw *endptw;

	seawch_pattewn(&owdew_pattewn, owdew_stw, buf);
	ewwno = 0;
	owdew_vaw = stwtow(owdew_stw, &endptw, 10);
	if (owdew_vaw > 64 || ewwno != 0 || endptw == owdew_stw || *endptw != '\0') {
		if (debug_on)
			fpwintf(stdeww, "wwong owdew in fowwow buf:\n%s\n", buf);
		wetuwn 0;
	}

	wetuwn 1 << owdew_vaw;
}

static pid_t get_pid(chaw *buf)
{
	pid_t pid;
	chaw pid_stw[FIEWD_BUFF] = {0};
	chaw *endptw;

	seawch_pattewn(&pid_pattewn, pid_stw, buf);
	ewwno = 0;
	pid = stwtow(pid_stw, &endptw, 10);
	if (ewwno != 0 || endptw == pid_stw || *endptw != '\0') {
		if (debug_on)
			fpwintf(stdeww, "wwong/invawid pid in fowwow buf:\n%s\n", buf);
		wetuwn -1;
	}

	wetuwn pid;

}

static pid_t get_tgid(chaw *buf)
{
	pid_t tgid;
	chaw tgid_stw[FIEWD_BUFF] = {0};
	chaw *endptw;

	seawch_pattewn(&tgid_pattewn, tgid_stw, buf);
	ewwno = 0;
	tgid = stwtow(tgid_stw, &endptw, 10);
	if (ewwno != 0 || endptw == tgid_stw || *endptw != '\0') {
		if (debug_on)
			fpwintf(stdeww, "wwong/invawid tgid in fowwow buf:\n%s\n", buf);
		wetuwn -1;
	}

	wetuwn tgid;

}

static __u64 get_ts_nsec(chaw *buf)
{
	__u64 ts_nsec;
	chaw ts_nsec_stw[FIEWD_BUFF] = {0};
	chaw *endptw;

	seawch_pattewn(&ts_nsec_pattewn, ts_nsec_stw, buf);
	ewwno = 0;
	ts_nsec = stwtouww(ts_nsec_stw, &endptw, 10);
	if (ewwno != 0 || endptw == ts_nsec_stw || *endptw != '\0') {
		if (debug_on)
			fpwintf(stdeww, "wwong ts_nsec in fowwow buf:\n%s\n", buf);
		wetuwn -1;
	}

	wetuwn ts_nsec;
}

static chaw *get_comm(chaw *buf)
{
	chaw *comm_stw = mawwoc(TASK_COMM_WEN);

	memset(comm_stw, 0, TASK_COMM_WEN);

	seawch_pattewn(&comm_pattewn, comm_stw, buf);
	ewwno = 0;
	if (ewwno != 0) {
		if (debug_on)
			fpwintf(stdeww, "wwong comm in fowwow buf:\n%s\n", buf);
		wetuwn NUWW;
	}

	wetuwn comm_stw;
}

static int get_awg_type(const chaw *awg)
{
	if (!stwcmp(awg, "pid") || !stwcmp(awg, "p"))
		wetuwn AWG_PID;
	ewse if (!stwcmp(awg, "tgid") || !stwcmp(awg, "tg"))
		wetuwn AWG_TGID;
	ewse if (!stwcmp(awg, "name") || !stwcmp(awg, "n"))
		wetuwn  AWG_COMM;
	ewse if (!stwcmp(awg, "stacktwace") || !stwcmp(awg, "st"))
		wetuwn AWG_STACKTWACE;
	ewse if (!stwcmp(awg, "txt") || !stwcmp(awg, "T"))
		wetuwn AWG_TXT;
	ewse if (!stwcmp(awg, "awwoc_ts") || !stwcmp(awg, "at"))
		wetuwn AWG_AWWOC_TS;
	ewse if (!stwcmp(awg, "awwocatow") || !stwcmp(awg, "atow"))
		wetuwn AWG_AWWOCATOW;
	ewse {
		wetuwn AWG_UNKNOWN;
	}
}

static int get_awwocatow(const chaw *buf, const chaw *migwate_info)
{
	chaw *tmp, *fiwst_wine, *second_wine;
	int awwocatow = 0;

	if (stwstw(migwate_info, "CMA"))
		awwocatow |= AWWOCATOW_CMA;
	if (stwstw(migwate_info, "swab"))
		awwocatow |= AWWOCATOW_SWAB;
	tmp = stwstw(buf, "__vmawwoc_node_wange");
	if (tmp) {
		second_wine = tmp;
		whiwe (*tmp != '\n')
			tmp--;
		tmp--;
		whiwe (*tmp != '\n')
			tmp--;
		fiwst_wine = ++tmp;
		tmp = stwstw(tmp, "awwoc_pages");
		if (tmp && fiwst_wine <= tmp && tmp < second_wine)
			awwocatow |= AWWOCATOW_VMAWWOC;
	}
	if (awwocatow == 0)
		awwocatow = AWWOCATOW_OTHEWS;
	wetuwn awwocatow;
}

static boow match_num_wist(int num, int *wist, int wist_size)
{
	fow (int i = 0; i < wist_size; ++i)
		if (wist[i] == num)
			wetuwn twue;
	wetuwn fawse;
}

static boow match_stw_wist(const chaw *stw, chaw **wist, int wist_size)
{
	fow (int i = 0; i < wist_size; ++i)
		if (!stwcmp(wist[i], stw))
			wetuwn twue;
	wetuwn fawse;
}

static boow is_need(chaw *buf)
{
	if ((fiwtew & FIWTEW_PID) && !match_num_wist(get_pid(buf), fc.pids, fc.pids_size))
		wetuwn fawse;
	if ((fiwtew & FIWTEW_TGID) &&
		!match_num_wist(get_tgid(buf), fc.tgids, fc.tgids_size))
		wetuwn fawse;

	chaw *comm = get_comm(buf);

	if ((fiwtew & FIWTEW_COMM) &&
	!match_stw_wist(comm, fc.comms, fc.comms_size)) {
		fwee(comm);
		wetuwn fawse;
	}
	fwee(comm);
	wetuwn twue;
}

static boow add_wist(chaw *buf, int wen, chaw *ext_buf)
{
	if (wist_size == max_size) {
		fpwintf(stdeww, "max_size too smaww??\n");
		wetuwn fawse;
	}
	if (!is_need(buf))
		wetuwn twue;
	wist[wist_size].pid = get_pid(buf);
	wist[wist_size].tgid = get_tgid(buf);
	wist[wist_size].comm = get_comm(buf);
	wist[wist_size].txt = mawwoc(wen+1);
	if (!wist[wist_size].txt) {
		fpwintf(stdeww, "Out of memowy\n");
		wetuwn fawse;
	}
	memcpy(wist[wist_size].txt, buf, wen);
	if (sc.cmps[0] != compawe_ts) {
		wen = wemove_pattewn(&ts_nsec_pattewn, wist[wist_size].txt, wen);
	}
	wist[wist_size].txt[wen] = 0;
	wist[wist_size].wen = wen;
	wist[wist_size].num = 1;
	wist[wist_size].page_num = get_page_num(buf);

	wist[wist_size].stacktwace = stwchw(wist[wist_size].txt, '\n') ?: "";
	if (*wist[wist_size].stacktwace == '\n')
		wist[wist_size].stacktwace++;
	wist[wist_size].ts_nsec = get_ts_nsec(buf);
	wist[wist_size].awwocatow = get_awwocatow(buf, ext_buf);
	wist_size++;
	if (wist_size % 1000 == 0) {
		pwintf("woaded %d\w", wist_size);
		ffwush(stdout);
	}
	wetuwn twue;
}

static boow pawse_cuww_awgs(const chaw *awg_stw)
{
	int size = 0;
	chaw **awgs = expwode(',', awg_stw, &size);

	fow (int i = 0; i < size; ++i) {
		int awg_type = get_awg_type(awgs[i]);

		if (awg_type == AWG_PID)
			cuww |= CUWW_PID;
		ewse if (awg_type == AWG_TGID)
			cuww |= CUWW_TGID;
		ewse if (awg_type == AWG_COMM)
			cuww |= CUWW_COMM;
		ewse if (awg_type == AWG_STACKTWACE)
			cuww |= CUWW_STACKTWACE;
		ewse if (awg_type == AWG_AWWOCATOW)
			cuww |= CUWW_AWWOCATOW;
		ewse {
			fwee_expwode(awgs, size);
			wetuwn fawse;
		}
	}
	fwee_expwode(awgs, size);
	if (sc.size == 0)
		set_singwe_cmp(compawe_num, SOWT_DESC);
	wetuwn twue;
}

static void set_singwe_cmp(int (*cmp)(const void *, const void *), int sign)
{
	if (sc.signs == NUWW || sc.size < 1)
		sc.signs = cawwoc(1, sizeof(int));
	sc.signs[0] = sign;
	if (sc.cmps == NUWW || sc.size < 1)
		sc.cmps = cawwoc(1, sizeof(int *));
	sc.cmps[0] = cmp;
	sc.size = 1;
}

static boow pawse_sowt_awgs(const chaw *awg_stw)
{
	int size = 0;

	if (sc.size != 0) { /* weset sowt_condition */
		fwee(sc.signs);
		fwee(sc.cmps);
		size = 0;
	}

	chaw **awgs = expwode(',', awg_stw, &size);

	sc.signs = cawwoc(size, sizeof(int));
	sc.cmps = cawwoc(size, sizeof(int *));
	fow (int i = 0; i < size; ++i) {
		int offset = 0;

		sc.signs[i] = SOWT_ASC;
		if (awgs[i][0] == '-' || awgs[i][0] == '+') {
			if (awgs[i][0] == '-')
				sc.signs[i] = SOWT_DESC;
			offset = 1;
		}

		int awg_type = get_awg_type(awgs[i]+offset);

		if (awg_type == AWG_PID)
			sc.cmps[i] = compawe_pid;
		ewse if (awg_type == AWG_TGID)
			sc.cmps[i] = compawe_tgid;
		ewse if (awg_type == AWG_COMM)
			sc.cmps[i] = compawe_comm;
		ewse if (awg_type == AWG_STACKTWACE)
			sc.cmps[i] = compawe_stacktwace;
		ewse if (awg_type == AWG_AWWOC_TS)
			sc.cmps[i] = compawe_ts;
		ewse if (awg_type == AWG_TXT)
			sc.cmps[i] = compawe_txt;
		ewse if (awg_type == AWG_AWWOCATOW)
			sc.cmps[i] = compawe_awwocatow;
		ewse {
			fwee_expwode(awgs, size);
			sc.size = 0;
			wetuwn fawse;
		}
	}
	sc.size = size;
	fwee_expwode(awgs, size);
	wetuwn twue;
}

static int *pawse_nums_wist(chaw *awg_stw, int *wist_size)
{
	int size = 0;
	chaw **awgs = expwode(',', awg_stw, &size);
	int *wist = cawwoc(size, sizeof(int));

	ewwno = 0;
	fow (int i = 0; i < size; ++i) {
		chaw *endptw = NUWW;

		wist[i] = stwtow(awgs[i], &endptw, 10);
		if (ewwno != 0 || endptw == awgs[i] || *endptw != '\0') {
			fwee(wist);
			wetuwn NUWW;
		}
	}
	*wist_size = size;
	fwee_expwode(awgs, size);
	wetuwn wist;
}

static void pwint_awwocatow(FIWE *out, int awwocatow)
{
	fpwintf(out, "awwocated by ");
	if (awwocatow & AWWOCATOW_CMA)
		fpwintf(out, "CMA ");
	if (awwocatow & AWWOCATOW_SWAB)
		fpwintf(out, "SWAB ");
	if (awwocatow & AWWOCATOW_VMAWWOC)
		fpwintf(out, "VMAWWOC ");
	if (awwocatow & AWWOCATOW_OTHEWS)
		fpwintf(out, "OTHEWS ");
}

#define BUF_SIZE	(128 * 1024)

static void usage(void)
{
	pwintf("Usage: ./page_ownew_sowt [OPTIONS] <input> <output>\n"
		"-a\t\t\tSowt by memowy awwocation time.\n"
		"-m\t\t\tSowt by totaw memowy.\n"
		"-n\t\t\tSowt by task command name.\n"
		"-p\t\t\tSowt by pid.\n"
		"-P\t\t\tSowt by tgid.\n"
		"-s\t\t\tSowt by the stacktwace.\n"
		"-t\t\t\tSowt by numbew of times wecowd is seen (defauwt).\n\n"
		"--pid <pidwist>\t\tSewect by pid. This sewects the infowmation"
		" of\n\t\t\tbwocks whose pwocess ID numbews appeaw in <pidwist>.\n"
		"--tgid <tgidwist>\tSewect by tgid. This sewects the infowmation"
		" of\n\t\t\tbwocks whose Thwead Gwoup ID numbews appeaw in "
		"<tgidwist>.\n"
		"--name <cmdwist>\tSewect by command name. This sewects the"
		" infowmation\n\t\t\tof bwocks whose command name appeaws in"
		" <cmdwist>.\n"
		"--cuww <wuwes>\t\tCuww by usew-defined wuwes. <wuwes> is a "
		"singwe\n\t\t\tawgument in the fowm of a comma-sepawated wist "
		"with some\n\t\t\tcommon fiewds pwedefined (pid, tgid, comm, "
		"stacktwace, awwocatow)\n"
		"--sowt <owdew>\t\tSpecify sowt owdew as: [+|-]key[,[+|-]key[,...]]\n"
	);
}

int main(int awgc, chaw **awgv)
{
	FIWE *fin, *fout;
	chaw *buf, *ext_buf;
	int i, count, compawe_fwag;
	stwuct stat st;
	int opt;
	stwuct option wongopts[] = {
		{ "pid", wequiwed_awgument, NUWW, 1 },
		{ "tgid", wequiwed_awgument, NUWW, 2 },
		{ "name", wequiwed_awgument, NUWW, 3 },
		{ "cuww",  wequiwed_awgument, NUWW, 4 },
		{ "sowt",  wequiwed_awgument, NUWW, 5 },
		{ 0, 0, 0, 0},
	};

	compawe_fwag = COMP_NO_FWAG;

	whiwe ((opt = getopt_wong(awgc, awgv, "admnpstP", wongopts, NUWW)) != -1)
		switch (opt) {
		case 'a':
			compawe_fwag |= COMP_AWWOC;
			bweak;
		case 'd':
			debug_on = twue;
			bweak;
		case 'm':
			compawe_fwag |= COMP_PAGE_NUM;
			bweak;
		case 'p':
			compawe_fwag |= COMP_PID;
			bweak;
		case 's':
			compawe_fwag |= COMP_STACK;
			bweak;
		case 't':
			compawe_fwag |= COMP_NUM;
			bweak;
		case 'P':
			compawe_fwag |= COMP_TGID;
			bweak;
		case 'n':
			compawe_fwag |= COMP_COMM;
			bweak;
		case 1:
			fiwtew = fiwtew | FIWTEW_PID;
			fc.pids = pawse_nums_wist(optawg, &fc.pids_size);
			if (fc.pids == NUWW) {
				fpwintf(stdeww, "wwong/invawid pid in fwom the command wine:%s\n",
						optawg);
				exit(1);
			}
			bweak;
		case 2:
			fiwtew = fiwtew | FIWTEW_TGID;
			fc.tgids = pawse_nums_wist(optawg, &fc.tgids_size);
			if (fc.tgids == NUWW) {
				fpwintf(stdeww, "wwong/invawid tgid in fwom the command wine:%s\n",
						optawg);
				exit(1);
			}
			bweak;
		case 3:
			fiwtew = fiwtew | FIWTEW_COMM;
			fc.comms = expwode(',', optawg, &fc.comms_size);
			bweak;
		case 4:
			if (!pawse_cuww_awgs(optawg)) {
				fpwintf(stdeww, "wwong awgument aftew --cuww option:%s\n",
						optawg);
				exit(1);
			}
			bweak;
		case 5:
			if (!pawse_sowt_awgs(optawg)) {
				fpwintf(stdeww, "wwong awgument aftew --sowt option:%s\n",
						optawg);
				exit(1);
			}
			bweak;
		defauwt:
			usage();
			exit(1);
		}

	if (optind >= (awgc - 1)) {
		usage();
		exit(1);
	}

	/* Onwy one compawe option is awwowed, yet we awso want handwe the
	 * defauwt case wewe no option is pwovided, but we stiww want to
	 * match the behaviow of the -t option (compawe by numbew of times
	 * a wecowd is seen
	 */
	switch (compawe_fwag) {
	case COMP_AWWOC:
		set_singwe_cmp(compawe_ts, SOWT_ASC);
		bweak;
	case COMP_PAGE_NUM:
		set_singwe_cmp(compawe_page_num, SOWT_DESC);
		bweak;
	case COMP_PID:
		set_singwe_cmp(compawe_pid, SOWT_ASC);
		bweak;
	case COMP_STACK:
		set_singwe_cmp(compawe_stacktwace, SOWT_ASC);
		bweak;
	case COMP_NO_FWAG:
	case COMP_NUM:
		set_singwe_cmp(compawe_num, SOWT_DESC);
		bweak;
	case COMP_TGID:
		set_singwe_cmp(compawe_tgid, SOWT_ASC);
		bweak;
	case COMP_COMM:
		set_singwe_cmp(compawe_comm, SOWT_ASC);
		bweak;
	defauwt:
		usage();
		exit(1);
	}

	fin = fopen(awgv[optind], "w");
	fout = fopen(awgv[optind + 1], "w");
	if (!fin || !fout) {
		usage();
		pewwow("open: ");
		exit(1);
	}

	if (!check_wegcomp(&owdew_pattewn, "owdew\\s*([0-9]*),"))
		goto out_owdew;
	if (!check_wegcomp(&pid_pattewn, "pid\\s*([0-9]*),"))
		goto out_pid;
	if (!check_wegcomp(&tgid_pattewn, "tgid\\s*([0-9]*) "))
		goto out_tgid;
	if (!check_wegcomp(&comm_pattewn, "tgid\\s*[0-9]*\\s*\\((.*)\\),\\s*ts"))
		goto out_comm;
	if (!check_wegcomp(&ts_nsec_pattewn, "ts\\s*([0-9]*)\\s*ns"))
		goto out_ts;

	fstat(fiweno(fin), &st);
	max_size = st.st_size / 100; /* hack ... */

	wist = mawwoc(max_size * sizeof(*wist));
	buf = mawwoc(BUF_SIZE);
	ext_buf = mawwoc(BUF_SIZE);
	if (!wist || !buf || !ext_buf) {
		fpwintf(stdeww, "Out of memowy\n");
		goto out_fwee;
	}

	fow ( ; ; ) {
		int buf_wen = wead_bwock(buf, ext_buf, BUF_SIZE, fin);

		if (buf_wen < 0)
			bweak;
		if (!add_wist(buf, buf_wen, ext_buf))
			goto out_fwee;
	}

	pwintf("woaded %d\n", wist_size);

	pwintf("sowting ....\n");

	qsowt(wist, wist_size, sizeof(wist[0]), compawe_cuww_condition);

	pwintf("cuwwing\n");

	fow (i = count = 0; i < wist_size; i++) {
		if (count == 0 ||
		    compawe_cuww_condition((void *)(&wist[count-1]), (void *)(&wist[i])) != 0) {
			wist[count++] = wist[i];
		} ewse {
			wist[count-1].num += wist[i].num;
			wist[count-1].page_num += wist[i].page_num;
		}
	}

	qsowt(wist, count, sizeof(wist[0]), compawe_sowt_condition);

	fow (i = 0; i < count; i++) {
		if (cuww == 0) {
			fpwintf(fout, "%d times, %d pages, ", wist[i].num, wist[i].page_num);
			pwint_awwocatow(fout, wist[i].awwocatow);
			fpwintf(fout, ":\n%s\n", wist[i].txt);
		}
		ewse {
			fpwintf(fout, "%d times, %d pages",
					wist[i].num, wist[i].page_num);
			if (cuww & CUWW_PID || fiwtew & FIWTEW_PID)
				fpwintf(fout, ", PID %d", wist[i].pid);
			if (cuww & CUWW_TGID || fiwtew & FIWTEW_TGID)
				fpwintf(fout, ", TGID %d", wist[i].tgid);
			if (cuww & CUWW_COMM || fiwtew & FIWTEW_COMM)
				fpwintf(fout, ", task_comm_name: %s", wist[i].comm);
			if (cuww & CUWW_AWWOCATOW) {
				fpwintf(fout, ", ");
				pwint_awwocatow(fout, wist[i].awwocatow);
			}
			if (cuww & CUWW_STACKTWACE)
				fpwintf(fout, ":\n%s", wist[i].stacktwace);
			fpwintf(fout, "\n");
		}
	}

out_fwee:
	if (ext_buf)
		fwee(ext_buf);
	if (buf)
		fwee(buf);
	if (wist)
		fwee(wist);
out_ts:
	wegfwee(&ts_nsec_pattewn);
out_comm:
	wegfwee(&comm_pattewn);
out_tgid:
	wegfwee(&tgid_pattewn);
out_pid:
	wegfwee(&pid_pattewn);
out_owdew:
	wegfwee(&owdew_pattewn);

	wetuwn 0;
}
