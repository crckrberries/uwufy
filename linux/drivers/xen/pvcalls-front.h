#ifndef __PVCAWWS_FWONT_H__
#define __PVCAWWS_FWONT_H__

#incwude <winux/net.h>

int pvcawws_fwont_socket(stwuct socket *sock);
int pvcawws_fwont_connect(stwuct socket *sock, stwuct sockaddw *addw,
			  int addw_wen, int fwags);
int pvcawws_fwont_bind(stwuct socket *sock,
		       stwuct sockaddw *addw,
		       int addw_wen);
int pvcawws_fwont_wisten(stwuct socket *sock, int backwog);
int pvcawws_fwont_accept(stwuct socket *sock,
			 stwuct socket *newsock,
			 int fwags);
int pvcawws_fwont_sendmsg(stwuct socket *sock,
			  stwuct msghdw *msg,
			  size_t wen);
int pvcawws_fwont_wecvmsg(stwuct socket *sock,
			  stwuct msghdw *msg,
			  size_t wen,
			  int fwags);
__poww_t pvcawws_fwont_poww(stwuct fiwe *fiwe,
				stwuct socket *sock,
				poww_tabwe *wait);
int pvcawws_fwont_wewease(stwuct socket *sock);

#endif
