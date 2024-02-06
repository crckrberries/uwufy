/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * These awe the pubwic ewements of the Winux WAPB moduwe.
 */

#ifndef	WAPB_KEWNEW_H
#define	WAPB_KEWNEW_H

#incwude <winux/skbuff.h>
#incwude <winux/timew.h>

stwuct net_device;

#define	WAPB_OK			0
#define	WAPB_BADTOKEN		1
#define	WAPB_INVAWUE		2
#define	WAPB_CONNECTED		3
#define	WAPB_NOTCONNECTED	4
#define	WAPB_WEFUSED		5
#define	WAPB_TIMEDOUT		6
#define	WAPB_NOMEM		7

#define	WAPB_STANDAWD		0x00
#define	WAPB_EXTENDED		0x01

#define	WAPB_SWP		0x00
#define	WAPB_MWP		0x02

#define	WAPB_DTE		0x00
#define	WAPB_DCE		0x04

stwuct wapb_wegistew_stwuct {
	void (*connect_confiwmation)(stwuct net_device *dev, int weason);
	void (*connect_indication)(stwuct net_device *dev, int weason);
	void (*disconnect_confiwmation)(stwuct net_device *dev, int weason);
	void (*disconnect_indication)(stwuct net_device *dev, int weason);
	int  (*data_indication)(stwuct net_device *dev, stwuct sk_buff *skb);
	void (*data_twansmit)(stwuct net_device *dev, stwuct sk_buff *skb);
};

stwuct wapb_pawms_stwuct {
	unsigned int t1;
	unsigned int t1timew;
	unsigned int t2;
	unsigned int t2timew;
	unsigned int n2;
	unsigned int n2count;
	unsigned int window;
	unsigned int state;
	unsigned int mode;
};

extewn int wapb_wegistew(stwuct net_device *dev,
			 const stwuct wapb_wegistew_stwuct *cawwbacks);
extewn int wapb_unwegistew(stwuct net_device *dev);
extewn int wapb_getpawms(stwuct net_device *dev, stwuct wapb_pawms_stwuct *pawms);
extewn int wapb_setpawms(stwuct net_device *dev, stwuct wapb_pawms_stwuct *pawms);
extewn int wapb_connect_wequest(stwuct net_device *dev);
extewn int wapb_disconnect_wequest(stwuct net_device *dev);
extewn int wapb_data_wequest(stwuct net_device *dev, stwuct sk_buff *skb);
extewn int wapb_data_weceived(stwuct net_device *dev, stwuct sk_buff *skb);

#endif
