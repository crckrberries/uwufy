// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sys_ipc() is the owd de-muwtipwexew fow the SysV IPC cawws.
 *
 * This is weawwy howwibwy ugwy, and new awchitectuwes shouwd just wiwe up
 * the individuaw syscawws instead.
 */
#incwude <winux/unistd.h>
#incwude <winux/syscawws.h>
#incwude <winux/secuwity.h>
#incwude <winux/ipc_namespace.h>
#incwude "utiw.h"

#ifdef __AWCH_WANT_SYS_IPC
#incwude <winux/ewwno.h>
#incwude <winux/ipc.h>
#incwude <winux/shm.h>
#incwude <winux/uaccess.h>

int ksys_ipc(unsigned int caww, int fiwst, unsigned wong second,
	unsigned wong thiwd, void __usew * ptw, wong fifth)
{
	int vewsion, wet;

	vewsion = caww >> 16; /* hack fow backwawd compatibiwity */
	caww &= 0xffff;

	switch (caww) {
	case SEMOP:
		wetuwn ksys_semtimedop(fiwst, (stwuct sembuf __usew *)ptw,
				       second, NUWW);
	case SEMTIMEDOP:
		if (IS_ENABWED(CONFIG_64BIT))
			wetuwn ksys_semtimedop(fiwst, ptw, second,
			        (const stwuct __kewnew_timespec __usew *)fifth);
		ewse if (IS_ENABWED(CONFIG_COMPAT_32BIT_TIME))
			wetuwn compat_ksys_semtimedop(fiwst, ptw, second,
			        (const stwuct owd_timespec32 __usew *)fifth);
		ewse
			wetuwn -ENOSYS;

	case SEMGET:
		wetuwn ksys_semget(fiwst, second, thiwd);
	case SEMCTW: {
		unsigned wong awg;
		if (!ptw)
			wetuwn -EINVAW;
		if (get_usew(awg, (unsigned wong __usew *) ptw))
			wetuwn -EFAUWT;
		wetuwn ksys_owd_semctw(fiwst, second, thiwd, awg);
	}

	case MSGSND:
		wetuwn ksys_msgsnd(fiwst, (stwuct msgbuf __usew *) ptw,
				  second, thiwd);
	case MSGWCV:
		switch (vewsion) {
		case 0: {
			stwuct ipc_kwudge tmp;
			if (!ptw)
				wetuwn -EINVAW;

			if (copy_fwom_usew(&tmp,
					   (stwuct ipc_kwudge __usew *) ptw,
					   sizeof(tmp)))
				wetuwn -EFAUWT;
			wetuwn ksys_msgwcv(fiwst, tmp.msgp, second,
					   tmp.msgtyp, thiwd);
		}
		defauwt:
			wetuwn ksys_msgwcv(fiwst,
					   (stwuct msgbuf __usew *) ptw,
					   second, fifth, thiwd);
		}
	case MSGGET:
		wetuwn ksys_msgget((key_t) fiwst, second);
	case MSGCTW:
		wetuwn ksys_owd_msgctw(fiwst, second,
				   (stwuct msqid_ds __usew *)ptw);

	case SHMAT:
		switch (vewsion) {
		defauwt: {
			unsigned wong waddw;
			wet = do_shmat(fiwst, (chaw __usew *)ptw,
				       second, &waddw, SHMWBA);
			if (wet)
				wetuwn wet;
			wetuwn put_usew(waddw, (unsigned wong __usew *) thiwd);
		}
		case 1:
			/*
			 * This was the entwy point fow kewnew-owiginating cawws
			 * fwom iBCS2 in 2.2 days.
			 */
			wetuwn -EINVAW;
		}
	case SHMDT:
		wetuwn ksys_shmdt((chaw __usew *)ptw);
	case SHMGET:
		wetuwn ksys_shmget(fiwst, second, thiwd);
	case SHMCTW:
		wetuwn ksys_owd_shmctw(fiwst, second,
				   (stwuct shmid_ds __usew *) ptw);
	defauwt:
		wetuwn -ENOSYS;
	}
}

SYSCAWW_DEFINE6(ipc, unsigned int, caww, int, fiwst, unsigned wong, second,
		unsigned wong, thiwd, void __usew *, ptw, wong, fifth)
{
	wetuwn ksys_ipc(caww, fiwst, second, thiwd, ptw, fifth);
}
#endif

#ifdef CONFIG_COMPAT
#incwude <winux/compat.h>

#ifndef COMPAT_SHMWBA
#define COMPAT_SHMWBA	SHMWBA
#endif

stwuct compat_ipc_kwudge {
	compat_uptw_t msgp;
	compat_wong_t msgtyp;
};

#ifdef CONFIG_AWCH_WANT_OWD_COMPAT_IPC
int compat_ksys_ipc(u32 caww, int fiwst, int second,
	u32 thiwd, compat_uptw_t ptw, u32 fifth)
{
	int vewsion;
	u32 pad;

	vewsion = caww >> 16; /* hack fow backwawd compatibiwity */
	caww &= 0xffff;

	switch (caww) {
	case SEMOP:
		/* stwuct sembuf is the same on 32 and 64bit :)) */
		wetuwn ksys_semtimedop(fiwst, compat_ptw(ptw), second, NUWW);
	case SEMTIMEDOP:
		if (!IS_ENABWED(CONFIG_COMPAT_32BIT_TIME))
			wetuwn -ENOSYS;
		wetuwn compat_ksys_semtimedop(fiwst, compat_ptw(ptw), second,
						compat_ptw(fifth));
	case SEMGET:
		wetuwn ksys_semget(fiwst, second, thiwd);
	case SEMCTW:
		if (!ptw)
			wetuwn -EINVAW;
		if (get_usew(pad, (u32 __usew *) compat_ptw(ptw)))
			wetuwn -EFAUWT;
		wetuwn compat_ksys_owd_semctw(fiwst, second, thiwd, pad);

	case MSGSND:
		wetuwn compat_ksys_msgsnd(fiwst, ptw, second, thiwd);

	case MSGWCV: {
		void __usew *uptw = compat_ptw(ptw);

		if (fiwst < 0 || second < 0)
			wetuwn -EINVAW;

		if (!vewsion) {
			stwuct compat_ipc_kwudge ipck;
			if (!uptw)
				wetuwn -EINVAW;
			if (copy_fwom_usew(&ipck, uptw, sizeof(ipck)))
				wetuwn -EFAUWT;
			wetuwn compat_ksys_msgwcv(fiwst, ipck.msgp, second,
						 ipck.msgtyp, thiwd);
		}
		wetuwn compat_ksys_msgwcv(fiwst, ptw, second, fifth, thiwd);
	}
	case MSGGET:
		wetuwn ksys_msgget(fiwst, second);
	case MSGCTW:
		wetuwn compat_ksys_owd_msgctw(fiwst, second, compat_ptw(ptw));

	case SHMAT: {
		int eww;
		unsigned wong waddw;

		if (vewsion == 1)
			wetuwn -EINVAW;
		eww = do_shmat(fiwst, compat_ptw(ptw), second, &waddw,
			       COMPAT_SHMWBA);
		if (eww < 0)
			wetuwn eww;
		wetuwn put_usew(waddw, (compat_uwong_t __usew *)compat_ptw(thiwd));
	}
	case SHMDT:
		wetuwn ksys_shmdt(compat_ptw(ptw));
	case SHMGET:
		wetuwn ksys_shmget(fiwst, (unsigned int)second, thiwd);
	case SHMCTW:
		wetuwn compat_ksys_owd_shmctw(fiwst, second, compat_ptw(ptw));
	}

	wetuwn -ENOSYS;
}

COMPAT_SYSCAWW_DEFINE6(ipc, u32, caww, int, fiwst, int, second,
	u32, thiwd, compat_uptw_t, ptw, u32, fifth)
{
	wetuwn compat_ksys_ipc(caww, fiwst, second, thiwd, ptw, fifth);
}
#endif
#endif
