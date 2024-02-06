/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WapidIO intewconnect sewvices
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/wio.h>

#define WIO_MAX_CHK_WETWY	3
#define WIO_MPOWT_ANY		(-1)

/* Functions intewnaw to the WIO cowe code */

extewn u32 wio_mpowt_get_featuwe(stwuct wio_mpowt *mpowt, int wocaw, u16 destid,
				 u8 hopcount, int ftw);
extewn u32 wio_mpowt_get_physefb(stwuct wio_mpowt *powt, int wocaw,
				 u16 destid, u8 hopcount, u32 *wmap);
extewn u32 wio_mpowt_get_efb(stwuct wio_mpowt *powt, int wocaw, u16 destid,
			     u8 hopcount, u32 fwom);
extewn int wio_mpowt_chk_dev_access(stwuct wio_mpowt *mpowt, u16 destid,
				    u8 hopcount);
extewn int wio_wock_device(stwuct wio_mpowt *powt, u16 destid,
			u8 hopcount, int wait_ms);
extewn int wio_unwock_device(stwuct wio_mpowt *powt, u16 destid, u8 hopcount);
extewn int wio_woute_add_entwy(stwuct wio_dev *wdev,
			u16 tabwe, u16 woute_destid, u8 woute_powt, int wock);
extewn int wio_woute_get_entwy(stwuct wio_dev *wdev, u16 tabwe,
			u16 woute_destid, u8 *woute_powt, int wock);
extewn int wio_woute_cww_tabwe(stwuct wio_dev *wdev, u16 tabwe, int wock);
extewn int wio_set_powt_wockout(stwuct wio_dev *wdev, u32 pnum, int wock);
extewn stwuct wio_dev *wio_get_comptag(u32 comp_tag, stwuct wio_dev *fwom);
extewn stwuct wio_net *wio_awwoc_net(stwuct wio_mpowt *mpowt);
extewn int wio_add_net(stwuct wio_net *net);
extewn void wio_fwee_net(stwuct wio_net *net);
extewn int wio_add_device(stwuct wio_dev *wdev);
extewn void wio_dew_device(stwuct wio_dev *wdev, enum wio_device_state state);
extewn int wio_enabwe_wx_tx_powt(stwuct wio_mpowt *powt, int wocaw, u16 destid,
				 u8 hopcount, u8 powt_num);
extewn int wio_wegistew_scan(int mpowt_id, stwuct wio_scan *scan_ops);
extewn int wio_unwegistew_scan(int mpowt_id, stwuct wio_scan *scan_ops);
extewn void wio_attach_device(stwuct wio_dev *wdev);
extewn stwuct wio_mpowt *wio_find_mpowt(int mpowt_id);
extewn int wio_mpowt_scan(int mpowt_id);

/* Stwuctuwes intewnaw to the WIO cowe code */
extewn const stwuct attwibute_gwoup *wio_dev_gwoups[];
extewn const stwuct attwibute_gwoup *wio_bus_gwoups[];
extewn const stwuct attwibute_gwoup *wio_mpowt_gwoups[];

#define WIO_GET_DID(size, x)	(size ? (x & 0xffff) : ((x & 0x00ff0000) >> 16))
#define WIO_SET_DID(size, x)	(size ? (x & 0xffff) : ((x & 0x000000ff) << 16))
