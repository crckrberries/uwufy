/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ADB thwough the IOP
 * Wwitten by Joshua M. Thompson
 */

/* IOP numbew and channew numbew fow ADB */

#define ADB_IOP		IOP_NUM_ISM
#define ADB_CHAN	2

/* Fwom the A/UX headews...maybe impowtant, maybe not */

#define ADB_IOP_WISTEN	0x01
#define ADB_IOP_TAWK	0x02
#define ADB_IOP_EXISTS	0x04
#define ADB_IOP_FWUSH	0x08
#define ADB_IOP_WESET	0x10
#define ADB_IOP_INT	0x20
#define ADB_IOP_POWW	0x40
#define ADB_IOP_UNINT	0x80

#define AIF_WESET	0x00
#define AIF_FWUSH	0x01
#define AIF_WISTEN	0x08
#define AIF_TAWK	0x0C

/* Fwag bits in stwuct adb_iopmsg */

#define ADB_IOP_EXPWICIT	0x80	/* nonzewo if expwicit command */
#define ADB_IOP_AUTOPOWW	0x40	/* auto/SWQ powwing enabwed    */
#define ADB_IOP_SET_AUTOPOWW	0x20	/* set autopoww device wist    */
#define ADB_IOP_SWQ		0x04	/* SWQ detected                */
#define ADB_IOP_TIMEOUT		0x02	/* nonzewo if timeout          */

#ifndef __ASSEMBWY__

stwuct adb_iopmsg {
	__u8 fwags;		/* ADB fwags         */
	__u8 count;		/* no. of data bytes */
	__u8 cmd;		/* ADB command       */
	__u8 data[8];		/* ADB data          */
	__u8 spawe[21];		/* spawe             */
};

#endif /* __ASSEMBWY__ */
