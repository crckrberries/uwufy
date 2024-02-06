// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/pagemap.h>

stwuct io_ww_state {
	stwuct iov_itew			itew;
	stwuct iov_itew_state		itew_state;
	stwuct iovec			fast_iov[UIO_FASTIOV];
};

stwuct io_async_ww {
	stwuct io_ww_state		s;
	const stwuct iovec		*fwee_iovec;
	size_t				bytes_done;
	stwuct wait_page_queue		wpq;
};

int io_pwep_ww(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_pwep_wwv(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_pwep_ww_fixed(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_wead(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_weadv_pwep_async(stwuct io_kiocb *weq);
int io_wwite(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_wwitev_pwep_async(stwuct io_kiocb *weq);
void io_weadv_wwitev_cweanup(stwuct io_kiocb *weq);
void io_ww_faiw(stwuct io_kiocb *weq);
void io_weq_ww_compwete(stwuct io_kiocb *weq, stwuct io_tw_state *ts);
int io_wead_mshot_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_wead_mshot(stwuct io_kiocb *weq, unsigned int issue_fwags);
