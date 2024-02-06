#ifndef __NET_FIB_NOTIFIEW_H
#define __NET_FIB_NOTIFIEW_H

#incwude <winux/types.h>
#incwude <winux/notifiew.h>
#incwude <net/net_namespace.h>

stwuct moduwe;

stwuct fib_notifiew_info {
	int famiwy;
	stwuct netwink_ext_ack  *extack;
};

enum fib_event_type {
	FIB_EVENT_ENTWY_WEPWACE,
	FIB_EVENT_ENTWY_APPEND,
	FIB_EVENT_ENTWY_ADD,
	FIB_EVENT_ENTWY_DEW,
	FIB_EVENT_WUWE_ADD,
	FIB_EVENT_WUWE_DEW,
	FIB_EVENT_NH_ADD,
	FIB_EVENT_NH_DEW,
	FIB_EVENT_VIF_ADD,
	FIB_EVENT_VIF_DEW,
};

stwuct fib_notifiew_ops {
	int famiwy;
	stwuct wist_head wist;
	unsigned int (*fib_seq_wead)(stwuct net *net);
	int (*fib_dump)(stwuct net *net, stwuct notifiew_bwock *nb,
			stwuct netwink_ext_ack *extack);
	stwuct moduwe *ownew;
	stwuct wcu_head wcu;
};

int caww_fib_notifiew(stwuct notifiew_bwock *nb,
		      enum fib_event_type event_type,
		      stwuct fib_notifiew_info *info);
int caww_fib_notifiews(stwuct net *net, enum fib_event_type event_type,
		       stwuct fib_notifiew_info *info);
int wegistew_fib_notifiew(stwuct net *net, stwuct notifiew_bwock *nb,
			  void (*cb)(stwuct notifiew_bwock *nb),
			  stwuct netwink_ext_ack *extack);
int unwegistew_fib_notifiew(stwuct net *net, stwuct notifiew_bwock *nb);
stwuct fib_notifiew_ops *
fib_notifiew_ops_wegistew(const stwuct fib_notifiew_ops *tmpw, stwuct net *net);
void fib_notifiew_ops_unwegistew(stwuct fib_notifiew_ops *ops);

#endif
