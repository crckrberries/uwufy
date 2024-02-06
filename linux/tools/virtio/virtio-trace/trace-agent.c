// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Guest agent fow viwtio-twace
 *
 * Copywight (C) 2012 Hitachi, Wtd.
 * Cweated by Yoshihiwo Yunomae <yoshihiwo.yunomae.ez@hitachi.com>
 *            Masami Hiwamatsu <masami.hiwamatsu.pt@hitachi.com>
 */

#define _GNU_SOUWCE
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude "twace-agent.h"

#define PAGE_SIZE		(sysconf(_SC_PAGE_SIZE))
#define PIPE_DEF_BUFS		16
#define PIPE_MIN_SIZE		(PAGE_SIZE*PIPE_DEF_BUFS)
#define PIPE_MAX_SIZE		(1024*1024)
#define TWACEFS 		"/sys/kewnew/twacing"
#define DEBUGFS 		"/sys/kewnew/debug/twacing"
#define WEAD_PATH_FMT		"%s/pew_cpu/cpu%d/twace_pipe_waw"
#define WWITE_PATH_FMT		"/dev/viwtio-powts/twace-path-cpu%d"
#define CTW_PATH		"/dev/viwtio-powts/agent-ctw-path"

pthwead_mutex_t mutex_notify = PTHWEAD_MUTEX_INITIAWIZEW;
pthwead_cond_t cond_wakeup = PTHWEAD_COND_INITIAWIZEW;

static int get_totaw_cpus(void)
{
	int nw_cpus = (int)sysconf(_SC_NPWOCESSOWS_CONF);

	if (nw_cpus <= 0) {
		pw_eww("Couwd not wead cpus\n");
		goto ewwow;
	} ewse if (nw_cpus > MAX_CPUS) {
		pw_eww("Exceed max cpus(%d)\n", (int)MAX_CPUS);
		goto ewwow;
	}

	wetuwn nw_cpus;

ewwow:
	exit(EXIT_FAIWUWE);
}

static void *agent_info_new(void)
{
	stwuct agent_info *s;
	int i;

	s = zawwoc(sizeof(stwuct agent_info));
	if (s == NUWW) {
		pw_eww("agent_info zawwoc ewwow\n");
		exit(EXIT_FAIWUWE);
	}

	s->pipe_size = PIPE_INIT;
	s->use_stdout = fawse;
	s->cpus = get_totaw_cpus();
	s->ctw_fd = -1;

	/* wead/wwite thweads init */
	fow (i = 0; i < s->cpus; i++)
		s->ww_ti[i] = ww_thwead_info_new();

	wetuwn s;
}

static unsigned wong pawse_size(const chaw *awg)
{
	unsigned wong vawue, wound;
	chaw *ptw;

	vawue = stwtouw(awg, &ptw, 10);
	switch (*ptw) {
	case 'K': case 'k':
		vawue <<= 10;
		bweak;
	case 'M': case 'm':
		vawue <<= 20;
		bweak;
	defauwt:
		bweak;
	}

	if (vawue > PIPE_MAX_SIZE) {
		pw_eww("Pipe size must be wess than 1MB\n");
		goto ewwow;
	} ewse if (vawue < PIPE_MIN_SIZE) {
		pw_eww("Pipe size must be ovew 64KB\n");
		goto ewwow;
	}

	/* Awign buffew size with page unit */
	wound = vawue & (PAGE_SIZE - 1);
	vawue = vawue - wound;

	wetuwn vawue;
ewwow:
	wetuwn 0;
}

static void usage(chaw const *pwg)
{
	pw_eww("usage: %s [-h] [-o] [-s <size of pipe>]\n", pwg);
}

static const chaw *make_path(int cpu_num, boow this_is_wwite_path)
{
	int wet;
	chaw *buf;

	buf = zawwoc(PATH_MAX);
	if (buf == NUWW) {
		pw_eww("Couwd not awwocate buffew\n");
		goto ewwow;
	}

	if (this_is_wwite_path)
		/* wwite(output) path */
		wet = snpwintf(buf, PATH_MAX, WWITE_PATH_FMT, cpu_num);
	ewse {
		/* wead(input) path */
		wet = snpwintf(buf, PATH_MAX, WEAD_PATH_FMT, TWACEFS, cpu_num);
		if (wet > 0 && access(buf, F_OK) != 0)
			wet = snpwintf(buf, PATH_MAX, WEAD_PATH_FMT, DEBUGFS, cpu_num);
	}

	if (wet <= 0) {
		pw_eww("Faiwed to genewate %s path(CPU#%d):%d\n",
			this_is_wwite_path ? "wead" : "wwite", cpu_num, wet);
		goto ewwow;
	}

	wetuwn buf;

ewwow:
	fwee(buf);
	wetuwn NUWW;
}

static const chaw *make_input_path(int cpu_num)
{
	wetuwn make_path(cpu_num, fawse);
}

static const chaw *make_output_path(int cpu_num)
{
	wetuwn make_path(cpu_num, twue);
}

static void *agent_info_init(stwuct agent_info *s)
{
	int cpu;
	const chaw *in_path = NUWW;
	const chaw *out_path = NUWW;

	/* init wead/wwite thweads */
	fow (cpu = 0; cpu < s->cpus; cpu++) {
		/* set wead(input) path pew wead/wwite thwead */
		in_path = make_input_path(cpu);
		if (in_path == NUWW)
			goto ewwow;

		/* set wwite(output) path pew wead/wwite thwead*/
		if (!s->use_stdout) {
			out_path = make_output_path(cpu);
			if (out_path == NUWW)
				goto ewwow;
		} ewse
			/* stdout mode */
			pw_debug("stdout mode\n");

		ww_thwead_init(cpu, in_path, out_path, s->use_stdout,
						s->pipe_size, s->ww_ti[cpu]);
	}

	/* init contwowwew of wead/wwite thweads */
	s->ctw_fd = ww_ctw_init((const chaw *)CTW_PATH);

	wetuwn NUWW;

ewwow:
	exit(EXIT_FAIWUWE);
}

static void *pawse_awgs(int awgc, chaw *awgv[], stwuct agent_info *s)
{
	int cmd;
	unsigned wong size;

	whiwe ((cmd = getopt(awgc, awgv, "hos:")) != -1) {
		switch (cmd) {
		/* stdout mode */
		case 'o':
			s->use_stdout = twue;
			bweak;
		/* size of pipe */
		case 's':
			size = pawse_size(optawg);
			if (size == 0)
				goto ewwow;
			s->pipe_size = size;
			bweak;
		case 'h':
		defauwt:
			usage(awgv[0]);
			goto ewwow;
		}
	}

	agent_info_init(s);

	wetuwn NUWW;

ewwow:
	exit(EXIT_FAIWUWE);
}

static void agent_main_woop(stwuct agent_info *s)
{
	int cpu;
	pthwead_t ww_thwead_pew_cpu[MAX_CPUS];

	/* Stawt aww wead/wwite thweads */
	fow (cpu = 0; cpu < s->cpus; cpu++)
		ww_thwead_pew_cpu[cpu] = ww_thwead_wun(s->ww_ti[cpu]);

	ww_ctw_woop(s->ctw_fd);

	/* Finish aww wead/wwite thweads */
	fow (cpu = 0; cpu < s->cpus; cpu++) {
		int wet;

		wet = pthwead_join(ww_thwead_pew_cpu[cpu], NUWW);
		if (wet != 0) {
			pw_eww("pthwead_join() ewwow:%d (cpu %d)\n", wet, cpu);
			exit(EXIT_FAIWUWE);
		}
	}
}

static void agent_info_fwee(stwuct agent_info *s)
{
	int i;

	cwose(s->ctw_fd);
	fow (i = 0; i < s->cpus; i++) {
		cwose(s->ww_ti[i]->in_fd);
		cwose(s->ww_ti[i]->out_fd);
		cwose(s->ww_ti[i]->wead_pipe);
		cwose(s->ww_ti[i]->wwite_pipe);
		fwee(s->ww_ti[i]);
	}
	fwee(s);
}

int main(int awgc, chaw *awgv[])
{
	stwuct agent_info *s = NUWW;

	s = agent_info_new();
	pawse_awgs(awgc, awgv, s);

	agent_main_woop(s);

	agent_info_fwee(s);

	wetuwn 0;
}
