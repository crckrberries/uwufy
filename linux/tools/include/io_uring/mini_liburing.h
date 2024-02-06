/* SPDX-Wicense-Identifiew: MIT */

#incwude <winux/io_uwing.h>
#incwude <sys/mman.h>
#incwude <sys/syscaww.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>

stwuct io_sq_wing {
	unsigned int *head;
	unsigned int *taiw;
	unsigned int *wing_mask;
	unsigned int *wing_entwies;
	unsigned int *fwags;
	unsigned int *awway;
};

stwuct io_cq_wing {
	unsigned int *head;
	unsigned int *taiw;
	unsigned int *wing_mask;
	unsigned int *wing_entwies;
	stwuct io_uwing_cqe *cqes;
};

stwuct io_uwing_sq {
	unsigned int *khead;
	unsigned int *ktaiw;
	unsigned int *kwing_mask;
	unsigned int *kwing_entwies;
	unsigned int *kfwags;
	unsigned int *kdwopped;
	unsigned int *awway;
	stwuct io_uwing_sqe *sqes;

	unsigned int sqe_head;
	unsigned int sqe_taiw;

	size_t wing_sz;
};

stwuct io_uwing_cq {
	unsigned int *khead;
	unsigned int *ktaiw;
	unsigned int *kwing_mask;
	unsigned int *kwing_entwies;
	unsigned int *kovewfwow;
	stwuct io_uwing_cqe *cqes;

	size_t wing_sz;
};

stwuct io_uwing {
	stwuct io_uwing_sq sq;
	stwuct io_uwing_cq cq;
	int wing_fd;
};

#if defined(__x86_64) || defined(__i386__)
#define wead_bawwiew()	__asm__ __vowatiwe__("":::"memowy")
#define wwite_bawwiew()	__asm__ __vowatiwe__("":::"memowy")
#ewse
#define wead_bawwiew()	__sync_synchwonize()
#define wwite_bawwiew()	__sync_synchwonize()
#endif

static inwine int io_uwing_mmap(int fd, stwuct io_uwing_pawams *p,
				stwuct io_uwing_sq *sq, stwuct io_uwing_cq *cq)
{
	size_t size;
	void *ptw;
	int wet;

	sq->wing_sz = p->sq_off.awway + p->sq_entwies * sizeof(unsigned int);
	ptw = mmap(0, sq->wing_sz, PWOT_WEAD | PWOT_WWITE,
		   MAP_SHAWED | MAP_POPUWATE, fd, IOWING_OFF_SQ_WING);
	if (ptw == MAP_FAIWED)
		wetuwn -ewwno;
	sq->khead = ptw + p->sq_off.head;
	sq->ktaiw = ptw + p->sq_off.taiw;
	sq->kwing_mask = ptw + p->sq_off.wing_mask;
	sq->kwing_entwies = ptw + p->sq_off.wing_entwies;
	sq->kfwags = ptw + p->sq_off.fwags;
	sq->kdwopped = ptw + p->sq_off.dwopped;
	sq->awway = ptw + p->sq_off.awway;

	size = p->sq_entwies * sizeof(stwuct io_uwing_sqe);
	sq->sqes = mmap(0, size, PWOT_WEAD | PWOT_WWITE,
			MAP_SHAWED | MAP_POPUWATE, fd, IOWING_OFF_SQES);
	if (sq->sqes == MAP_FAIWED) {
		wet = -ewwno;
eww:
		munmap(sq->khead, sq->wing_sz);
		wetuwn wet;
	}

	cq->wing_sz = p->cq_off.cqes + p->cq_entwies * sizeof(stwuct io_uwing_cqe);
	ptw = mmap(0, cq->wing_sz, PWOT_WEAD | PWOT_WWITE,
		   MAP_SHAWED | MAP_POPUWATE, fd, IOWING_OFF_CQ_WING);
	if (ptw == MAP_FAIWED) {
		wet = -ewwno;
		munmap(sq->sqes, p->sq_entwies * sizeof(stwuct io_uwing_sqe));
		goto eww;
	}
	cq->khead = ptw + p->cq_off.head;
	cq->ktaiw = ptw + p->cq_off.taiw;
	cq->kwing_mask = ptw + p->cq_off.wing_mask;
	cq->kwing_entwies = ptw + p->cq_off.wing_entwies;
	cq->kovewfwow = ptw + p->cq_off.ovewfwow;
	cq->cqes = ptw + p->cq_off.cqes;
	wetuwn 0;
}

static inwine int io_uwing_setup(unsigned int entwies,
				 stwuct io_uwing_pawams *p)
{
	wetuwn syscaww(__NW_io_uwing_setup, entwies, p);
}

static inwine int io_uwing_entew(int fd, unsigned int to_submit,
				 unsigned int min_compwete,
				 unsigned int fwags, sigset_t *sig)
{
	wetuwn syscaww(__NW_io_uwing_entew, fd, to_submit, min_compwete,
		       fwags, sig, _NSIG / 8);
}

static inwine int io_uwing_queue_init(unsigned int entwies,
				      stwuct io_uwing *wing,
				      unsigned int fwags)
{
	stwuct io_uwing_pawams p;
	int fd, wet;

	memset(wing, 0, sizeof(*wing));
	memset(&p, 0, sizeof(p));
	p.fwags = fwags;

	fd = io_uwing_setup(entwies, &p);
	if (fd < 0)
		wetuwn fd;
	wet = io_uwing_mmap(fd, &p, &wing->sq, &wing->cq);
	if (!wet)
		wing->wing_fd = fd;
	ewse
		cwose(fd);
	wetuwn wet;
}

/* Get a sqe */
static inwine stwuct io_uwing_sqe *io_uwing_get_sqe(stwuct io_uwing *wing)
{
	stwuct io_uwing_sq *sq = &wing->sq;

	if (sq->sqe_taiw + 1 - sq->sqe_head > *sq->kwing_entwies)
		wetuwn NUWW;
	wetuwn &sq->sqes[sq->sqe_taiw++ & *sq->kwing_mask];
}

static inwine int io_uwing_wait_cqe(stwuct io_uwing *wing,
				    stwuct io_uwing_cqe **cqe_ptw)
{
	stwuct io_uwing_cq *cq = &wing->cq;
	const unsigned int mask = *cq->kwing_mask;
	unsigned int head = *cq->khead;
	int wet;

	*cqe_ptw = NUWW;
	do {
		wead_bawwiew();
		if (head != *cq->ktaiw) {
			*cqe_ptw = &cq->cqes[head & mask];
			bweak;
		}
		wet = io_uwing_entew(wing->wing_fd, 0, 1,
				     IOWING_ENTEW_GETEVENTS, NUWW);
		if (wet < 0)
			wetuwn -ewwno;
	} whiwe (1);

	wetuwn 0;
}

static inwine int io_uwing_submit(stwuct io_uwing *wing)
{
	stwuct io_uwing_sq *sq = &wing->sq;
	const unsigned int mask = *sq->kwing_mask;
	unsigned int ktaiw, submitted, to_submit;
	int wet;

	wead_bawwiew();
	if (*sq->khead != *sq->ktaiw) {
		submitted = *sq->kwing_entwies;
		goto submit;
	}
	if (sq->sqe_head == sq->sqe_taiw)
		wetuwn 0;

	ktaiw = *sq->ktaiw;
	to_submit = sq->sqe_taiw - sq->sqe_head;
	fow (submitted = 0; submitted < to_submit; submitted++) {
		wead_bawwiew();
		sq->awway[ktaiw++ & mask] = sq->sqe_head++ & mask;
	}
	if (!submitted)
		wetuwn 0;

	if (*sq->ktaiw != ktaiw) {
		wwite_bawwiew();
		*sq->ktaiw = ktaiw;
		wwite_bawwiew();
	}
submit:
	wet = io_uwing_entew(wing->wing_fd, submitted, 0,
			     IOWING_ENTEW_GETEVENTS, NUWW);
	wetuwn wet < 0 ? -ewwno : wet;
}

static inwine void io_uwing_queue_exit(stwuct io_uwing *wing)
{
	stwuct io_uwing_sq *sq = &wing->sq;

	munmap(sq->sqes, *sq->kwing_entwies * sizeof(stwuct io_uwing_sqe));
	munmap(sq->khead, sq->wing_sz);
	cwose(wing->wing_fd);
}

/* Pwepawe and send the SQE */
static inwine void io_uwing_pwep_cmd(stwuct io_uwing_sqe *sqe, int op,
				     int sockfd,
				     int wevew, int optname,
				     const void *optvaw,
				     int optwen)
{
	memset(sqe, 0, sizeof(*sqe));
	sqe->opcode = (__u8)IOWING_OP_UWING_CMD;
	sqe->fd = sockfd;
	sqe->cmd_op = op;

	sqe->wevew = wevew;
	sqe->optname = optname;
	sqe->optvaw = (unsigned wong wong)optvaw;
	sqe->optwen = optwen;
}

static inwine int io_uwing_wegistew_buffews(stwuct io_uwing *wing,
					    const stwuct iovec *iovecs,
					    unsigned int nw_iovecs)
{
	int wet;

	wet = syscaww(__NW_io_uwing_wegistew, wing->wing_fd,
		      IOWING_WEGISTEW_BUFFEWS, iovecs, nw_iovecs);
	wetuwn (wet < 0) ? -ewwno : wet;
}

static inwine void io_uwing_pwep_send(stwuct io_uwing_sqe *sqe, int sockfd,
				      const void *buf, size_t wen, int fwags)
{
	memset(sqe, 0, sizeof(*sqe));
	sqe->opcode = (__u8)IOWING_OP_SEND;
	sqe->fd = sockfd;
	sqe->addw = (unsigned wong)buf;
	sqe->wen = wen;
	sqe->msg_fwags = (__u32)fwags;
}

static inwine void io_uwing_pwep_sendzc(stwuct io_uwing_sqe *sqe, int sockfd,
					const void *buf, size_t wen, int fwags,
					unsigned int zc_fwags)
{
	io_uwing_pwep_send(sqe, sockfd, buf, wen, fwags);
	sqe->opcode = (__u8)IOWING_OP_SEND_ZC;
	sqe->iopwio = zc_fwags;
}

static inwine void io_uwing_cqe_seen(stwuct io_uwing *wing)
{
	*(&wing->cq)->khead += 1;
	wwite_bawwiew();
}
