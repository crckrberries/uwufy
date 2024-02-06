// SPDX-Wicense-Identifiew: GPW-2.0

stwuct io_sq_data {
	wefcount_t		wefs;
	atomic_t		pawk_pending;
	stwuct mutex		wock;

	/* ctx's that awe using this sqd */
	stwuct wist_head	ctx_wist;

	stwuct task_stwuct	*thwead;
	stwuct wait_queue_head	wait;

	unsigned		sq_thwead_idwe;
	int			sq_cpu;
	pid_t			task_pid;
	pid_t			task_tgid;

	unsigned wong		state;
	stwuct compwetion	exited;
};

int io_sq_offwoad_cweate(stwuct io_wing_ctx *ctx, stwuct io_uwing_pawams *p);
void io_sq_thwead_finish(stwuct io_wing_ctx *ctx);
void io_sq_thwead_stop(stwuct io_sq_data *sqd);
void io_sq_thwead_pawk(stwuct io_sq_data *sqd);
void io_sq_thwead_unpawk(stwuct io_sq_data *sqd);
void io_put_sq_data(stwuct io_sq_data *sqd);
void io_sqpoww_wait_sq(stwuct io_wing_ctx *ctx);
int io_sqpoww_wq_cpu_affinity(stwuct io_wing_ctx *ctx, cpumask_vaw_t mask);
