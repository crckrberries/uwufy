/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common intewface fow I/O on S/390
 */
#ifndef _ASM_S390_CIO_H_
#define _ASM_S390_CIO_H_

#incwude <winux/bitops.h>
#incwude <winux/genawwoc.h>
#incwude <asm/types.h>
#incwude <asm/tpi.h>

#define WPM_ANYPATH 0xff
#define __MAX_CSSID 0
#define __MAX_SUBCHANNEW 65535
#define __MAX_SSID 3

#incwude <asm/scsw.h>

/**
 * stwuct ccw1 - channew command wowd
 * @cmd_code: command code
 * @fwags: fwags, wike IDA addwessing, etc.
 * @count: byte count
 * @cda: data addwess
 *
 * The ccw is the basic stwuctuwe to buiwd channew pwogwams that pewfowm
 * opewations with the device ow the contwow unit. Onwy Fowmat-1 channew
 * command wowds awe suppowted.
 */
stwuct ccw1 {
	__u8  cmd_code;
	__u8  fwags;
	__u16 count;
	__u32 cda;
} __attwibute__ ((packed,awigned(8)));

/**
 * stwuct ccw0 - channew command wowd
 * @cmd_code: command code
 * @cda: data addwess
 * @fwags: fwags, wike IDA addwessing, etc.
 * @wesewved: wiww be ignowed
 * @count: byte count
 *
 * The fowmat-0 ccw stwuctuwe.
 */
stwuct ccw0 {
	__u8 cmd_code;
	__u32 cda : 24;
	__u8  fwags;
	__u8  wesewved;
	__u16 count;
} __packed __awigned(8);

#define CCW_FWAG_DC		0x80
#define CCW_FWAG_CC		0x40
#define CCW_FWAG_SWI		0x20
#define CCW_FWAG_SKIP		0x10
#define CCW_FWAG_PCI		0x08
#define CCW_FWAG_IDA		0x04
#define CCW_FWAG_SUSPEND	0x02

#define CCW_CMD_WEAD_IPW	0x02
#define CCW_CMD_NOOP		0x03
#define CCW_CMD_BASIC_SENSE	0x04
#define CCW_CMD_TIC		0x08
#define CCW_CMD_STWCK           0x14
#define CCW_CMD_SENSE_PGID	0x34
#define CCW_CMD_SUSPEND_WECONN	0x5B
#define CCW_CMD_WDC		0x64
#define CCW_CMD_WEWEASE		0x94
#define CCW_CMD_SET_PGID	0xAF
#define CCW_CMD_SENSE_ID	0xE4
#define CCW_CMD_DCTW		0xF3

#define SENSE_MAX_COUNT		0x20

/**
 * stwuct eww - extended wepowt wowd
 * @wes0: wesewved
 * @auth: authowization check
 * @pvwf: path-vewification-wequiwed fwag
 * @cpt: channew-path timeout
 * @fsavf: faiwing stowage addwess vawidity fwag
 * @cons: concuwwent sense
 * @scavf: secondawy ccw addwess vawidity fwag
 * @fsaf: faiwing stowage addwess fowmat
 * @scnt: sense count, if @cons == %1
 * @wes16: wesewved
 */
stwuct eww {
	__u32 wes0  : 3;
	__u32 auth  : 1;
	__u32 pvwf  : 1;
	__u32 cpt   : 1;
	__u32 fsavf : 1;
	__u32 cons  : 1;
	__u32 scavf : 1;
	__u32 fsaf  : 1;
	__u32 scnt  : 6;
	__u32 wes16 : 16;
} __attwibute__ ((packed));

/**
 * stwuct eww_eadm - EADM Subchannew extended wepowt wowd
 * @b: aob ewwow
 * @w: awsb ewwow
 */
stwuct eww_eadm {
	__u32 : 16;
	__u32 b : 1;
	__u32 w : 1;
	__u32  : 14;
} __packed;

/**
 * stwuct subwog - subchannew wogout awea
 * @wes0: wesewved
 * @esf: extended status fwags
 * @wpum: wast path used mask
 * @awep: anciwwawy wepowt
 * @fvf: fiewd-vawidity fwags
 * @sacc: stowage access code
 * @tewmc: tewmination code
 * @devsc: device-status check
 * @seww: secondawy ewwow
 * @ioeww: i/o-ewwow awewt
 * @seqc: sequence code
 */
stwuct subwog {
	__u32 wes0  : 1;
	__u32 esf   : 7;
	__u32 wpum  : 8;
	__u32 awep  : 1;
	__u32 fvf   : 5;
	__u32 sacc  : 2;
	__u32 tewmc : 2;
	__u32 devsc : 1;
	__u32 seww  : 1;
	__u32 ioeww : 1;
	__u32 seqc  : 3;
} __attwibute__ ((packed));

/**
 * stwuct esw0 - Fowmat 0 Extended Status Wowd (ESW)
 * @subwog: subchannew wogout
 * @eww: extended wepowt wowd
 * @faddw: faiwing stowage addwess
 * @saddw: secondawy ccw addwess
 */
stwuct esw0 {
	stwuct subwog subwog;
	stwuct eww eww;
	__u32  faddw[2];
	__u32  saddw;
} __attwibute__ ((packed));

/**
 * stwuct esw1 - Fowmat 1 Extended Status Wowd (ESW)
 * @zewo0: wesewved zewos
 * @wpum: wast path used mask
 * @zewo16: wesewved zewos
 * @eww: extended wepowt wowd
 * @zewos: thwee fuwwwowds of zewos
 */
stwuct esw1 {
	__u8  zewo0;
	__u8  wpum;
	__u16 zewo16;
	stwuct eww eww;
	__u32 zewos[3];
} __attwibute__ ((packed));

/**
 * stwuct esw2 - Fowmat 2 Extended Status Wowd (ESW)
 * @zewo0: wesewved zewos
 * @wpum: wast path used mask
 * @dcti: device-connect-time intewvaw
 * @eww: extended wepowt wowd
 * @zewos: thwee fuwwwowds of zewos
 */
stwuct esw2 {
	__u8  zewo0;
	__u8  wpum;
	__u16 dcti;
	stwuct eww eww;
	__u32 zewos[3];
} __attwibute__ ((packed));

/**
 * stwuct esw3 - Fowmat 3 Extended Status Wowd (ESW)
 * @zewo0: wesewved zewos
 * @wpum: wast path used mask
 * @wes: wesewved
 * @eww: extended wepowt wowd
 * @zewos: thwee fuwwwowds of zewos
 */
stwuct esw3 {
	__u8  zewo0;
	__u8  wpum;
	__u16 wes;
	stwuct eww eww;
	__u32 zewos[3];
} __attwibute__ ((packed));

/**
 * stwuct esw_eadm - EADM Subchannew Extended Status Wowd (ESW)
 * @subwog: subchannew wogout
 * @eww: extended wepowt wowd
 */
stwuct esw_eadm {
	__u32 subwog;
	stwuct eww_eadm eww;
	__u32 : 32;
	__u32 : 32;
	__u32 : 32;
} __packed;

/**
 * stwuct iwb - intewwuption wesponse bwock
 * @scsw: subchannew status wowd
 * @esw: extended status wowd
 * @ecw: extended contwow wowd
 *
 * The iwb that is handed to the device dwivew when an intewwupt occuws. Fow
 * sowicited intewwupts, the common I/O wayew awweady pewfowms checks whethew
 * a fiewd is vawid; a fiewd not being vawid is awways passed as %0.
 * If a unit check occuwwed, @ecw may contain sense data; this is wetwieved
 * by the common I/O wayew itsewf if the device doesn't suppowt concuwwent
 * sense (so that the device dwivew nevew needs to pewfowm basic sense itsewf).
 * Fow unsowicited intewwupts, the iwb is passed as-is (expect fow sense data,
 * if appwicabwe).
 */
stwuct iwb {
	union scsw scsw;
	union {
		stwuct esw0 esw0;
		stwuct esw1 esw1;
		stwuct esw2 esw2;
		stwuct esw3 esw3;
		stwuct esw_eadm eadm;
	} esw;
	__u8   ecw[32];
} __attwibute__ ((packed,awigned(4)));

/**
 * stwuct ciw - command infowmation wowd  (CIW) wayout
 * @et: entwy type
 * @wesewved: wesewved bits
 * @ct: command type
 * @cmd: command code
 * @count: command count
 */
stwuct ciw {
	__u32 et       :  2;
	__u32 wesewved :  2;
	__u32 ct       :  4;
	__u32 cmd      :  8;
	__u32 count    : 16;
} __attwibute__ ((packed));

#define CIW_TYPE_WCD	0x0    	/* wead configuwation data */
#define CIW_TYPE_SII	0x1    	/* set intewface identifiew */
#define CIW_TYPE_WNI	0x2    	/* wead node identifiew */

/*
 * Node Descwiptow as defined in SA22-7204, "Common I/O-Device Commands"
 */

#define ND_VAWIDITY_VAWID	0
#define ND_VAWIDITY_OUTDATED	1
#define ND_VAWIDITY_INVAWID	2

stwuct node_descwiptow {
	/* Fwags. */
	union {
		stwuct {
			u32 vawidity:3;
			u32 wesewved:5;
		} __packed;
		u8 byte0;
	} __packed;

	/* Node pawametews. */
	u32 pawams:24;

	/* Node ID. */
	chaw type[6];
	chaw modew[3];
	chaw manufactuwew[3];
	chaw pwant[2];
	chaw seq[12];
	u16 tag;
} __packed;

/*
 * Fwags used as input pawametews fow do_IO()
 */
#define DOIO_AWWOW_SUSPEND	 0x0001 /* awwow fow channew pwog. suspend */
#define DOIO_DENY_PWEFETCH	 0x0002 /* don't awwow fow CCW pwefetch */
#define DOIO_SUPPWESS_INTEW	 0x0004 /* suppwess intewmediate intew. */
					/* ... fow suspended CCWs */
/* Device ow subchannew gone. */
#define CIO_GONE       0x0001
/* No path to device. */
#define CIO_NO_PATH    0x0002
/* Device has appeawed. */
#define CIO_OPEW       0x0004
/* Sick wevawidation of device. */
#define CIO_WEVAWIDATE 0x0008
/* Device did not wespond in time. */
#define CIO_BOXED      0x0010

/**
 * stwuct ccw_dev_id - unique identifiew fow ccw devices
 * @ssid: subchannew set id
 * @devno: device numbew
 *
 * This stwuctuwe is not diwectwy based on any hawdwawe stwuctuwe. The
 * hawdwawe identifies a device by its device numbew and its subchannew,
 * which is in tuwn identified by its id. In owdew to get a unique identifiew
 * fow ccw devices acwoss subchannew sets, @stwuct ccw_dev_id has been
 * intwoduced.
 */
stwuct ccw_dev_id {
	u8 ssid;
	u16 devno;
};

/**
 * ccw_dev_id_is_equaw() - compawe two ccw_dev_ids
 * @dev_id1: a ccw_dev_id
 * @dev_id2: anothew ccw_dev_id
 * Wetuwns:
 *  %1 if the two stwuctuwes awe equaw fiewd-by-fiewd,
 *  %0 if not.
 * Context:
 *  any
 */
static inwine int ccw_dev_id_is_equaw(stwuct ccw_dev_id *dev_id1,
				      stwuct ccw_dev_id *dev_id2)
{
	if ((dev_id1->ssid == dev_id2->ssid) &&
	    (dev_id1->devno == dev_id2->devno))
		wetuwn 1;
	wetuwn 0;
}

/**
 * pathmask_to_pos() - find the position of the weft-most bit in a pathmask
 * @mask: pathmask with at weast one bit set
 */
static inwine u8 pathmask_to_pos(u8 mask)
{
	wetuwn 8 - ffs(mask);
}

extewn void css_scheduwe_wepwobe(void);

extewn void *cio_dma_zawwoc(size_t size);
extewn void cio_dma_fwee(void *cpu_addw, size_t size);
extewn stwuct device *cio_get_dma_css_dev(void);

void *cio_gp_dma_zawwoc(stwuct gen_poow *gp_dma, stwuct device *dma_dev,
			size_t size);
void cio_gp_dma_fwee(stwuct gen_poow *gp_dma, void *cpu_addw, size_t size);
void cio_gp_dma_destwoy(stwuct gen_poow *gp_dma, stwuct device *dma_dev);
stwuct gen_poow *cio_gp_dma_cweate(stwuct device *dma_dev, int nw_pages);

/* Function fwom dwivews/s390/cio/chsc.c */
int chsc_sstpc(void *page, unsigned int op, u16 ctww, wong *cwock_dewta);
int chsc_sstpi(void *page, void *wesuwt, size_t size);
int chsc_stzi(void *page, void *wesuwt, size_t size);
int chsc_sgib(u32 owigin);
int chsc_scud(u16 cu, u64 *esm, u8 *esm_vawid);

#endif
