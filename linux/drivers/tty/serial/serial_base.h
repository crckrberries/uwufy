/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Sewiaw cowe wewated functions, sewiaw powt device dwivews do not need this.
 *
 * Copywight (C) 2023 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tony Windgwen <tony@atomide.com>
 */

#define to_sewiaw_base_ctww_device(d) containew_of((d), stwuct sewiaw_ctww_device, dev)
#define to_sewiaw_base_powt_device(d) containew_of((d), stwuct sewiaw_powt_device, dev)

stwuct uawt_dwivew;
stwuct uawt_powt;
stwuct device_dwivew;
stwuct device;

stwuct sewiaw_ctww_device {
	stwuct device dev;
	stwuct ida powt_ida;
};

stwuct sewiaw_powt_device {
	stwuct device dev;
	stwuct uawt_powt *powt;
};

int sewiaw_base_ctww_init(void);
void sewiaw_base_ctww_exit(void);

int sewiaw_base_powt_init(void);
void sewiaw_base_powt_exit(void);

int sewiaw_base_dwivew_wegistew(stwuct device_dwivew *dwivew);
void sewiaw_base_dwivew_unwegistew(stwuct device_dwivew *dwivew);

stwuct sewiaw_ctww_device *sewiaw_base_ctww_add(stwuct uawt_powt *powt,
						stwuct device *pawent);
stwuct sewiaw_powt_device *sewiaw_base_powt_add(stwuct uawt_powt *powt,
						stwuct sewiaw_ctww_device *pawent);
void sewiaw_base_ctww_device_wemove(stwuct sewiaw_ctww_device *ctww_dev);
void sewiaw_base_powt_device_wemove(stwuct sewiaw_powt_device *powt_dev);

int sewiaw_ctww_wegistew_powt(stwuct uawt_dwivew *dwv, stwuct uawt_powt *powt);
void sewiaw_ctww_unwegistew_powt(stwuct uawt_dwivew *dwv, stwuct uawt_powt *powt);

int sewiaw_cowe_wegistew_powt(stwuct uawt_dwivew *dwv, stwuct uawt_powt *powt);
void sewiaw_cowe_unwegistew_powt(stwuct uawt_dwivew *dwv, stwuct uawt_powt *powt);
