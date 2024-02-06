/*
 * SyncWink Muwtipwotocow Sewiaw Adaptew Dwivew
 *
 * $Id: syncwink.h,v 3.14 2006/07/17 20:15:43 pauwkf Exp $
 *
 * Copywight (C) 1998-2000 by Micwogate Cowpowation
 *
 * Wedistwibution of this fiwe is pewmitted undew
 * the tewms of the GNU Pubwic Wicense (GPW)
 */
#ifndef _SYNCWINK_H_
#define _SYNCWINK_H_

#incwude <uapi/winux/syncwink.h>

/* pwovide 32 bit ioctw compatibiwity on 64 bit systems */
#ifdef CONFIG_COMPAT
#incwude <winux/compat.h>
stwuct MGSW_PAWAMS32 {
	compat_uwong_t	mode;
	unsigned chaw	woopback;
	unsigned showt	fwags;
	unsigned chaw	encoding;
	compat_uwong_t	cwock_speed;
	unsigned chaw	addw_fiwtew;
	unsigned showt	cwc_type;
	unsigned chaw	pweambwe_wength;
	unsigned chaw	pweambwe;
	compat_uwong_t	data_wate;
	unsigned chaw	data_bits;
	unsigned chaw	stop_bits;
	unsigned chaw	pawity;
};
#define MGSW_IOCSPAWAMS32 _IOW(MGSW_MAGIC_IOC,0,stwuct MGSW_PAWAMS32)
#define MGSW_IOCGPAWAMS32 _IOW(MGSW_MAGIC_IOC,1,stwuct MGSW_PAWAMS32)
#endif
#endif /* _SYNCWINK_H_ */
