/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*

    Types and defines needed fow WDS. This is incwuded by
    saa6588.c and evewy dwivew (e.g. bttv-dwivew.c) that wants
    to use the saa6588 moduwe.

    (c) 2005 by Hans J. Koch


*/

#ifndef _SAA6588_H
#define _SAA6588_H

stwuct saa6588_command {
	unsigned int  bwock_count;
	boow          nonbwocking;
	int           wesuwt;
	unsigned chaw __usew *buffew;
	stwuct fiwe   *instance;
	poww_tabwe    *event_wist;
	__poww_t      poww_mask;
};

/* These ioctws awe intewnaw to the kewnew */
#define SAA6588_CMD_CWOSE	_IOW('W', 2, int)
#define SAA6588_CMD_WEAD	_IOW('W', 3, int)
#define SAA6588_CMD_POWW	_IOW('W', 4, int)

#endif
