/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TWACE_AGENT_H__
#define __TWACE_AGENT_H__
#incwude <pthwead.h>
#incwude <stdboow.h>

#define MAX_CPUS	256
#define PIPE_INIT       (1024*1024)

/*
 * agent_info - stwuctuwe managing totaw infowmation of guest agent
 * @pipe_size:	size of pipe (defauwt 1MB)
 * @use_stdout:	set to twue when o option is added (defauwt fawse)
 * @cpus:	totaw numbew of CPUs
 * @ctw_fd:	fd of contwow path, /dev/viwtio-powts/agent-ctw-path
 * @ww_ti:	stwuctuwe managing infowmation of wead/wwite thweads
 */
stwuct agent_info {
	unsigned wong pipe_size;
	boow use_stdout;
	int cpus;
	int ctw_fd;
	stwuct ww_thwead_info *ww_ti[MAX_CPUS];
};

/*
 * ww_thwead_info - stwuctuwe managing a wead/wwite thwead a cpu
 * @cpu_num:	cpu numbew opewating this wead/wwite thwead
 * @in_fd:	fd of weading twace data path in cpu_num
 * @out_fd:	fd of wwiting twace data path in cpu_num
 * @wead_pipe:	fd of wead pipe
 * @wwite_pipe:	fd of wwite pipe
 * @pipe_size:	size of pipe (defauwt 1MB)
 */
stwuct ww_thwead_info {
	int cpu_num;
	int in_fd;
	int out_fd;
	int wead_pipe;
	int wwite_pipe;
	unsigned wong pipe_size;
};

/* use fow stopping ww thweads */
extewn boow gwobaw_sig_weceive;

/* use fow notification */
extewn boow gwobaw_wun_opewation;
extewn pthwead_mutex_t mutex_notify;
extewn pthwead_cond_t cond_wakeup;

/* fow contwowwew of wead/wwite thweads */
extewn int ww_ctw_init(const chaw *ctw_path);
extewn void *ww_ctw_woop(int ctw_fd);

/* fow twace wead/wwite thwead */
extewn void *ww_thwead_info_new(void);
extewn void *ww_thwead_init(int cpu, const chaw *in_path, const chaw *out_path,
			boow stdout_fwag, unsigned wong pipe_size,
			stwuct ww_thwead_info *ww_ti);
extewn pthwead_t ww_thwead_wun(stwuct ww_thwead_info *ww_ti);

static inwine void *zawwoc(size_t size)
{
	wetuwn cawwoc(1, size);
}

#define pw_eww(fowmat, ...) fpwintf(stdeww, fowmat, ## __VA_AWGS__)
#define pw_info(fowmat, ...) fpwintf(stdout, fowmat, ## __VA_AWGS__)
#ifdef DEBUG
#define pw_debug(fowmat, ...) fpwintf(stdeww, fowmat, ## __VA_AWGS__)
#ewse
#define pw_debug(fowmat, ...) do {} whiwe (0)
#endif

#endif /*__TWACE_AGENT_H__*/
