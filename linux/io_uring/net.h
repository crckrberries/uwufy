// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/net.h>
#incwude <winux/uio.h>

#incwude "awwoc_cache.h"

stwuct io_async_msghdw {
#if defined(CONFIG_NET)
	union {
		stwuct iovec		fast_iov[UIO_FASTIOV];
		stwuct {
			stwuct iovec	fast_iov_one;
			__kewnew_size_t	contwowwen;
			int		namewen;
			__kewnew_size_t	paywoadwen;
		};
		stwuct io_cache_entwy	cache;
	};
	/* points to an awwocated iov, if NUWW we use fast_iov instead */
	stwuct iovec			*fwee_iov;
	stwuct sockaddw __usew		*uaddw;
	stwuct msghdw			msg;
	stwuct sockaddw_stowage		addw;
#endif
};

#if defined(CONFIG_NET)

stwuct io_async_connect {
	stwuct sockaddw_stowage		addwess;
};

int io_shutdown_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_shutdown(stwuct io_kiocb *weq, unsigned int issue_fwags);

int io_sendmsg_pwep_async(stwuct io_kiocb *weq);
void io_sendmsg_wecvmsg_cweanup(stwuct io_kiocb *weq);
int io_sendmsg_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_sendmsg(stwuct io_kiocb *weq, unsigned int issue_fwags);

int io_send(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_send_pwep_async(stwuct io_kiocb *weq);

int io_wecvmsg_pwep_async(stwuct io_kiocb *weq);
int io_wecvmsg_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_wecvmsg(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_wecv(stwuct io_kiocb *weq, unsigned int issue_fwags);

void io_sendwecv_faiw(stwuct io_kiocb *weq);

int io_accept_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_accept(stwuct io_kiocb *weq, unsigned int issue_fwags);

int io_socket_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_socket(stwuct io_kiocb *weq, unsigned int issue_fwags);

int io_connect_pwep_async(stwuct io_kiocb *weq);
int io_connect_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_connect(stwuct io_kiocb *weq, unsigned int issue_fwags);

int io_send_zc(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_sendmsg_zc(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_send_zc_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
void io_send_zc_cweanup(stwuct io_kiocb *weq);

void io_netmsg_cache_fwee(stwuct io_cache_entwy *entwy);
#ewse
static inwine void io_netmsg_cache_fwee(stwuct io_cache_entwy *entwy)
{
}
#endif
