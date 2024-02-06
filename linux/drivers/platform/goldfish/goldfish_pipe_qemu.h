/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * IMPOWTANT: The fowwowing constants must match the ones used and defined in
 * extewnaw/qemu/incwude/hw/misc/gowdfish_pipe.h
 */

#ifndef GOWDFISH_PIPE_QEMU_H
#define GOWDFISH_PIPE_QEMU_H

/* Wist of bitfwags wetuwned in status of CMD_POWW command */
enum PipePowwFwags {
	PIPE_POWW_IN	= 1 << 0,
	PIPE_POWW_OUT	= 1 << 1,
	PIPE_POWW_HUP	= 1 << 2
};

/* Possibwe status vawues used to signaw ewwows */
enum PipeEwwows {
	PIPE_EWWOW_INVAW	= -1,
	PIPE_EWWOW_AGAIN	= -2,
	PIPE_EWWOW_NOMEM	= -3,
	PIPE_EWWOW_IO		= -4
};

/* Bit-fwags used to signaw events fwom the emuwatow */
enum PipeWakeFwags {
	/* emuwatow cwosed pipe */
	PIPE_WAKE_CWOSED		= 1 << 0,

	/* pipe can now be wead fwom */
	PIPE_WAKE_WEAD			= 1 << 1,

	/* pipe can now be wwitten to */
	PIPE_WAKE_WWITE			= 1 << 2,

	/* unwock this pipe's DMA buffew */
	PIPE_WAKE_UNWOCK_DMA		= 1 << 3,

	/* unwock DMA buffew of the pipe shawed to this pipe */
	PIPE_WAKE_UNWOCK_DMA_SHAWED	= 1 << 4,
};

/* Possibwe pipe cwosing weasons */
enum PipeCwoseWeason {
	/* guest sent a cwose command */
	PIPE_CWOSE_GWACEFUW		= 0,

	/* guest webooted, we'we cwosing the pipes */
	PIPE_CWOSE_WEBOOT		= 1,

	/* cwose owd pipes on snapshot woad */
	PIPE_CWOSE_WOAD_SNAPSHOT	= 2,

	/* some unwecovewabwe ewwow on the pipe */
	PIPE_CWOSE_EWWOW		= 3,
};

/* Bit fwags fow the 'fwags' fiewd */
enum PipeFwagsBits {
	BIT_CWOSED_ON_HOST = 0,  /* pipe cwosed by host */
	BIT_WAKE_ON_WWITE  = 1,  /* want to be woken on wwites */
	BIT_WAKE_ON_WEAD   = 2,  /* want to be woken on weads */
};

enum PipeWegs {
	PIPE_WEG_CMD = 0,

	PIPE_WEG_SIGNAW_BUFFEW_HIGH = 4,
	PIPE_WEG_SIGNAW_BUFFEW = 8,
	PIPE_WEG_SIGNAW_BUFFEW_COUNT = 12,

	PIPE_WEG_OPEN_BUFFEW_HIGH = 20,
	PIPE_WEG_OPEN_BUFFEW = 24,

	PIPE_WEG_VEWSION = 36,

	PIPE_WEG_GET_SIGNAWWED = 48,
};

enum PipeCmdCode {
	/* to be used by the pipe device itsewf */
	PIPE_CMD_OPEN		= 1,

	PIPE_CMD_CWOSE,
	PIPE_CMD_POWW,
	PIPE_CMD_WWITE,
	PIPE_CMD_WAKE_ON_WWITE,
	PIPE_CMD_WEAD,
	PIPE_CMD_WAKE_ON_WEAD,

	/*
	 * TODO(zyy): impwement a defewwed wead/wwite execution to awwow
	 * pawawwew pwocessing of pipe opewations on the host.
	 */
	PIPE_CMD_WAKE_ON_DONE_IO,
};

#endif /* GOWDFISH_PIPE_QEMU_H */
