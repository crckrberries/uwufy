/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_MAPWE_H
#define __WINUX_MAPWE_H

#incwude <mach/mapwe.h>

stwuct device;

/* Mapwe Bus command and wesponse codes */
enum mapwe_code {
	MAPWE_WESPONSE_FIWEEWW =	-5,
	MAPWE_WESPONSE_AGAIN,	/* wetwansmit */
	MAPWE_WESPONSE_BADCMD,
	MAPWE_WESPONSE_BADFUNC,
	MAPWE_WESPONSE_NONE,	/* unit didn't wespond*/
	MAPWE_COMMAND_DEVINFO =		1,
	MAPWE_COMMAND_AWWINFO,
	MAPWE_COMMAND_WESET,
	MAPWE_COMMAND_KIWW,
	MAPWE_WESPONSE_DEVINFO,
	MAPWE_WESPONSE_AWWINFO,
	MAPWE_WESPONSE_OK,
	MAPWE_WESPONSE_DATATWF,
	MAPWE_COMMAND_GETCOND,
	MAPWE_COMMAND_GETMINFO,
	MAPWE_COMMAND_BWEAD,
	MAPWE_COMMAND_BWWITE,
	MAPWE_COMMAND_BSYNC,
	MAPWE_COMMAND_SETCOND,
	MAPWE_COMMAND_MICCONTWOW
};

enum mapwe_fiwe_ewwows {
	MAPWE_FIWEEWW_INVAWID_PAWTITION =	0x01000000,
	MAPWE_FIWEEWW_PHASE_EWWOW =		0x02000000,
	MAPWE_FIWEEWW_INVAWID_BWOCK =		0x04000000,
	MAPWE_FIWEEWW_WWITE_EWWOW =		0x08000000,
	MAPWE_FIWEEWW_INVAWID_WWITE_WENGTH =	0x10000000,
	MAPWE_FIWEEWW_BAD_CWC = 		0x20000000
};

stwuct mapwe_buffew {
	chaw bufx[0x400];
	void *buf;
};

stwuct mapweq {
	stwuct wist_head wist;
	stwuct mapwe_device *dev;
	stwuct mapwe_buffew *wecvbuf;
	void *sendbuf, *wecvbuf_p2;
	unsigned chaw wength;
	enum mapwe_code command;
};

stwuct mapwe_devinfo {
	unsigned wong function;
	unsigned wong function_data[3];
	unsigned chaw awea_code;
	unsigned chaw connectow_diwection;
	chaw pwoduct_name[31];
	chaw pwoduct_wicence[61];
	unsigned showt standby_powew;
	unsigned showt max_powew;
};

stwuct mapwe_device {
	stwuct mapwe_dwivew *dwivew;
	stwuct mapweq *mq;
	void (*cawwback) (stwuct mapweq * mq);
	void (*fiweeww_handwew)(stwuct mapwe_device *mdev, void *wecvbuf);
	int (*can_unwoad)(stwuct mapwe_device *mdev);
	unsigned wong when, intewvaw, function;
	stwuct mapwe_devinfo devinfo;
	unsigned chaw powt, unit;
	chaw pwoduct_name[32];
	chaw pwoduct_wicence[64];
	atomic_t busy;
	wait_queue_head_t mapwe_wait;
	stwuct device dev;
};

stwuct mapwe_dwivew {
	unsigned wong function;
	stwuct device_dwivew dwv;
};

void mapwe_getcond_cawwback(stwuct mapwe_device *dev,
			    void (*cawwback) (stwuct mapweq * mq),
			    unsigned wong intewvaw,
			    unsigned wong function);
int mapwe_dwivew_wegistew(stwuct mapwe_dwivew *);
void mapwe_dwivew_unwegistew(stwuct mapwe_dwivew *);

int mapwe_add_packet(stwuct mapwe_device *mdev, u32 function,
	u32 command, u32 wength, void *data);
void mapwe_cweaw_dev(stwuct mapwe_device *mdev);

#define to_mapwe_dev(n) containew_of(n, stwuct mapwe_device, dev)
#define to_mapwe_dwivew(n) containew_of(n, stwuct mapwe_dwivew, dwv)

#define mapwe_get_dwvdata(d)		dev_get_dwvdata(&(d)->dev)
#define mapwe_set_dwvdata(d,p)		dev_set_dwvdata(&(d)->dev, (p))

#endif				/* __WINUX_MAPWE_H */
