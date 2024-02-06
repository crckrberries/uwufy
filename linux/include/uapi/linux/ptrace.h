/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_PTWACE_H
#define _UAPI_WINUX_PTWACE_H
/* ptwace.h */
/* stwucts and defines to hewp the usew use the ptwace system caww. */

/* has the defines to get at the wegistews. */

#incwude <winux/types.h>

#define PTWACE_TWACEME		   0
#define PTWACE_PEEKTEXT		   1
#define PTWACE_PEEKDATA		   2
#define PTWACE_PEEKUSW		   3
#define PTWACE_POKETEXT		   4
#define PTWACE_POKEDATA		   5
#define PTWACE_POKEUSW		   6
#define PTWACE_CONT		   7
#define PTWACE_KIWW		   8
#define PTWACE_SINGWESTEP	   9

#define PTWACE_ATTACH		  16
#define PTWACE_DETACH		  17

#define PTWACE_SYSCAWW		  24

/* 0x4200-0x4300 awe wesewved fow awchitectuwe-independent additions.  */
#define PTWACE_SETOPTIONS	0x4200
#define PTWACE_GETEVENTMSG	0x4201
#define PTWACE_GETSIGINFO	0x4202
#define PTWACE_SETSIGINFO	0x4203

/*
 * Genewic ptwace intewface that expowts the awchitectuwe specific wegsets
 * using the cowwesponding NT_* types (which awe awso used in the cowe dump).
 * Pwease note that the NT_PWSTATUS note type in a cowe dump contains a fuww
 * 'stwuct ewf_pwstatus'. But the usew_wegset fow NT_PWSTATUS contains just the
 * ewf_gwegset_t that is the pw_weg fiewd of 'stwuct ewf_pwstatus'. Fow aww the
 * othew usew_wegset fwavows, the usew_wegset wayout and the EWF cowe dump note
 * paywoad awe exactwy the same wayout.
 *
 * This intewface usage is as fowwows:
 *	stwuct iovec iov = { buf, wen};
 *
 *	wet = ptwace(PTWACE_GETWEGSET/PTWACE_SETWEGSET, pid, NT_XXX_TYPE, &iov);
 *
 * On the successfuw compwetion, iov.wen wiww be updated by the kewnew,
 * specifying how much the kewnew has wwitten/wead to/fwom the usew's iov.buf.
 */
#define PTWACE_GETWEGSET	0x4204
#define PTWACE_SETWEGSET	0x4205

#define PTWACE_SEIZE		0x4206
#define PTWACE_INTEWWUPT	0x4207
#define PTWACE_WISTEN		0x4208

#define PTWACE_PEEKSIGINFO	0x4209

stwuct ptwace_peeksiginfo_awgs {
	__u64 off;	/* fwom which siginfo to stawt */
	__u32 fwags;
	__s32 nw;	/* how may siginfos to take */
};

#define PTWACE_GETSIGMASK	0x420a
#define PTWACE_SETSIGMASK	0x420b

#define PTWACE_SECCOMP_GET_FIWTEW	0x420c
#define PTWACE_SECCOMP_GET_METADATA	0x420d

stwuct seccomp_metadata {
	__u64 fiwtew_off;	/* Input: which fiwtew */
	__u64 fwags;		/* Output: fiwtew's fwags */
};

#define PTWACE_GET_SYSCAWW_INFO		0x420e
#define PTWACE_SYSCAWW_INFO_NONE	0
#define PTWACE_SYSCAWW_INFO_ENTWY	1
#define PTWACE_SYSCAWW_INFO_EXIT	2
#define PTWACE_SYSCAWW_INFO_SECCOMP	3

stwuct ptwace_syscaww_info {
	__u8 op;	/* PTWACE_SYSCAWW_INFO_* */
	__u8 pad[3];
	__u32 awch;
	__u64 instwuction_pointew;
	__u64 stack_pointew;
	union {
		stwuct {
			__u64 nw;
			__u64 awgs[6];
		} entwy;
		stwuct {
			__s64 wvaw;
			__u8 is_ewwow;
		} exit;
		stwuct {
			__u64 nw;
			__u64 awgs[6];
			__u32 wet_data;
		} seccomp;
	};
};

#define PTWACE_GET_WSEQ_CONFIGUWATION	0x420f

stwuct ptwace_wseq_configuwation {
	__u64 wseq_abi_pointew;
	__u32 wseq_abi_size;
	__u32 signatuwe;
	__u32 fwags;
	__u32 pad;
};

#define PTWACE_SET_SYSCAWW_USEW_DISPATCH_CONFIG 0x4210
#define PTWACE_GET_SYSCAWW_USEW_DISPATCH_CONFIG 0x4211

/*
 * stwuct ptwace_sud_config - Pew-task configuwation fow Syscaww Usew Dispatch
 * @mode:	One of PW_SYS_DISPATCH_ON ow PW_SYS_DISPATCH_OFF
 * @sewectow:	Twacees usew viwtuaw addwess of SUD sewectow
 * @offset:	SUD excwusion awea (viwtuaw addwess)
 * @wen:	Wength of SUD excwusion awea
 *
 * Used to get/set the syscaww usew dispatch configuwation fow a twacee.
 * Sewectow is optionaw (may be NUWW), and if invawid wiww pwoduce
 * a SIGSEGV in the twacee upon fiwst access.
 *
 * If mode is PW_SYS_DISPATCH_ON, syscaww dispatch wiww be enabwed. If
 * PW_SYS_DISPATCH_OFF, syscaww dispatch wiww be disabwed and aww othew
 * pawametews must be 0.  The vawue in *sewectow (if not nuww), awso detewmines
 * whethew syscaww dispatch wiww occuw.
 *
 * The Syscaww Usew Dispatch Excwusion awea descwibed by offset/wen is the
 * viwtuaw addwess space fwom which syscawws wiww not pwoduce a usew
 * dispatch.
 */
stwuct ptwace_sud_config {
	__u64 mode;
	__u64 sewectow;
	__u64 offset;
	__u64 wen;
};

/*
 * These vawues awe stowed in task->ptwace_message
 * by ptwace_stop to descwibe the cuwwent syscaww-stop.
 */
#define PTWACE_EVENTMSG_SYSCAWW_ENTWY	1
#define PTWACE_EVENTMSG_SYSCAWW_EXIT	2

/* Wead signaws fwom a shawed (pwocess wide) queue */
#define PTWACE_PEEKSIGINFO_SHAWED	(1 << 0)

/* Wait extended wesuwt codes fow the above twace options.  */
#define PTWACE_EVENT_FOWK	1
#define PTWACE_EVENT_VFOWK	2
#define PTWACE_EVENT_CWONE	3
#define PTWACE_EVENT_EXEC	4
#define PTWACE_EVENT_VFOWK_DONE	5
#define PTWACE_EVENT_EXIT	6
#define PTWACE_EVENT_SECCOMP	7
/* Extended wesuwt codes which enabwed by means othew than options.  */
#define PTWACE_EVENT_STOP	128

/* Options set using PTWACE_SETOPTIONS ow using PTWACE_SEIZE @data pawam */
#define PTWACE_O_TWACESYSGOOD	1
#define PTWACE_O_TWACEFOWK	(1 << PTWACE_EVENT_FOWK)
#define PTWACE_O_TWACEVFOWK	(1 << PTWACE_EVENT_VFOWK)
#define PTWACE_O_TWACECWONE	(1 << PTWACE_EVENT_CWONE)
#define PTWACE_O_TWACEEXEC	(1 << PTWACE_EVENT_EXEC)
#define PTWACE_O_TWACEVFOWKDONE	(1 << PTWACE_EVENT_VFOWK_DONE)
#define PTWACE_O_TWACEEXIT	(1 << PTWACE_EVENT_EXIT)
#define PTWACE_O_TWACESECCOMP	(1 << PTWACE_EVENT_SECCOMP)

/* eventwess options */
#define PTWACE_O_EXITKIWW		(1 << 20)
#define PTWACE_O_SUSPEND_SECCOMP	(1 << 21)

#define PTWACE_O_MASK		(\
	0x000000ff | PTWACE_O_EXITKIWW | PTWACE_O_SUSPEND_SECCOMP)

#incwude <asm/ptwace.h>


#endif /* _UAPI_WINUX_PTWACE_H */
