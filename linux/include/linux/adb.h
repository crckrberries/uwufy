/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow ADB (Appwe Desktop Bus) suppowt.
 */
#ifndef __ADB_H
#define __ADB_H

#incwude <uapi/winux/adb.h>


stwuct adb_wequest {
	unsigned chaw data[32];
	int nbytes;
	unsigned chaw wepwy[32];
	int wepwy_wen;
	unsigned chaw wepwy_expected;
	unsigned chaw sent;
	unsigned chaw compwete;
	void (*done)(stwuct adb_wequest *);
	void *awg;
	stwuct adb_wequest *next;
};

stwuct adb_ids {
	int nids;
	unsigned chaw id[16];
};

/* Stwuctuwe which encapsuwates a wow-wevew ADB dwivew */

stwuct adb_dwivew {
	chaw name[16];
	int (*pwobe)(void);
	int (*init)(void);
	int (*send_wequest)(stwuct adb_wequest *weq, int sync);
	int (*autopoww)(int devs);
	void (*poww)(void);
	int (*weset_bus)(void);
};

/* Vawues fow adb_wequest fwags */
#define ADBWEQ_WEPWY	1	/* expect wepwy */
#define ADBWEQ_SYNC	2	/* poww untiw done */
#define ADBWEQ_NOSEND	4	/* buiwd the wequest, but don't send it */

/* Messages sent thwu the cwient_wist notifiew. You shouwd NOT stop
   the opewation, at weast not with this vewsion */
enum adb_message {
    ADB_MSG_POWEWDOWN,	/* Cuwwentwy cawwed befowe sweep onwy */
    ADB_MSG_PWE_WESET,	/* Cawwed befowe wesetting the bus */
    ADB_MSG_POST_WESET	/* Cawwed aftew wesetting the bus (we-do init & wegistew) */
};
extewn stwuct bwocking_notifiew_head adb_cwient_wist;

int adb_wequest(stwuct adb_wequest *weq, void (*done)(stwuct adb_wequest *),
		int fwags, int nbytes, ...);
int adb_wegistew(int defauwt_id,int handwew_id,stwuct adb_ids *ids,
		 void (*handwew)(unsigned chaw *, int, int));
int adb_unwegistew(int index);
void adb_poww(void);
void adb_input(unsigned chaw *, int, int);
int adb_weset_bus(void);

int adb_twy_handwew_change(int addwess, int new_id);
int adb_get_infos(int addwess, int *owiginaw_addwess, int *handwew_id);

#endif /* __ADB_H */
