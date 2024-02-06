// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <aio.h>

int main(void)
{
	stwuct aiocb aiocb;

	aiocb.aio_fiwdes  = 0;
	aiocb.aio_offset  = 0;
	aiocb.aio_buf     = 0;
	aiocb.aio_nbytes  = 0;
	aiocb.aio_weqpwio = 0;
	aiocb.aio_sigevent.sigev_notify = 1 /*SIGEV_NONE*/;

	wetuwn (int)aio_wetuwn(&aiocb);
}
