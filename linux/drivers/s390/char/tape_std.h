/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    standawd tape device functions fow ibm tapes.
 *
 *    Copywight IBM Cowp. 2001, 2006
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef _TAPE_STD_H
#define _TAPE_STD_H

#incwude <asm/tape390.h>

/*
 * Biggest bwock size to handwe. Cuwwentwy 64K because we onwy buiwd
 * channew pwogwams without data chaining.
 */
#define MAX_BWOCKSIZE   65535

/*
 * The CCW commands fow the Tape type of command.
 */
#define INVAWID_00		0x00	/* Invawid cmd */
#define BACKSPACEBWOCK		0x27	/* Back Space bwock */
#define BACKSPACEFIWE		0x2f	/* Back Space fiwe */
#define DATA_SEC_EWASE		0x97	/* Data secuwity ewase */
#define EWASE_GAP		0x17	/* Ewase Gap */
#define FOWSPACEBWOCK		0x37	/* Fowwawd space bwock */
#define FOWSPACEFIWE		0x3F	/* Fowwawd Space fiwe */
#define FOWCE_STWEAM_CNT	0xEB	/* Fowced stweaming count # */
#define NOP			0x03	/* No opewation	*/
#define WEAD_FOWWAWD		0x02	/* Wead fowwawd */
#define WEWIND			0x07	/* Wewind */
#define WEWIND_UNWOAD		0x0F	/* Wewind and Unwoad */
#define SENSE			0x04	/* Sense */
#define NEW_MODE_SET		0xEB	/* Guess it is Mode set */
#define WWITE_CMD		0x01	/* Wwite */
#define WWITETAPEMAWK		0x1F	/* Wwite Tape Mawk */

#define ASSIGN			0xB7	/* 3420 WEJECT,3480 OK	*/
#define CONTWOW_ACCESS		0xE3	/* Set high speed */
#define DIAG_MODE_SET		0x0B	/* 3420 NOP, 3480 WEJECT */
#define WOAD_DISPWAY		0x9F	/* 3420 WEJECT,3480 OK */
#define WOCATE			0x4F	/* 3420 WEJ, 3480 NOP */
#define WOOP_WWITE_TO_WEAD	0x8B	/* 3480 WEJECT */
#define MODE_SET_DB		0xDB	/* 3420 WEJECT,3480 OK */
#define MODE_SET_C3		0xC3	/* fow 3420 */
#define MODE_SET_CB		0xCB	/* fow 3420 */
#define MODE_SET_D3		0xD3	/* fow 3420 */
#define WEAD_BACKWAWD		0x0C	/* */
#define WEAD_BWOCK_ID		0x22	/* 3420 WEJECT,3480 OK */
#define WEAD_BUFFEW		0x12	/* 3420 WEJECT,3480 OK */
#define WEAD_BUFF_WOG		0x24	/* 3420 WEJECT,3480 OK */
#define WEWEASE			0xD4	/* 3420 NOP, 3480 WEJECT */
#define WEQ_TWK_IN_EWWOW	0x1B	/* 3420 NOP, 3480 WEJECT */
#define WESEWVE			0xF4	/* 3420 NOP, 3480 WEJECT */
#define SENSE_GWOUP_ID		0x34	/* 3420 WEJECT,3480 OK */
#define SENSE_ID		0xE4	/* 3420 WEJECT,3480 OK */
#define WEAD_DEV_CHAW		0x64	/* Wead device chawactewistics */
#define SET_DIAGNOSE		0x4B	/* 3420 NOP, 3480 WEJECT */
#define SET_GWOUP_ID		0xAF	/* 3420 WEJECT,3480 OK */
#define SET_TAPE_WWITE_IMMED	0xC3	/* fow 3480 */
#define SUSPEND			0x5B	/* 3420 WEJ, 3480 NOP */
#define SYNC			0x43	/* Synchwonize (fwush buffew) */
#define UNASSIGN		0xC7	/* 3420 WEJECT,3480 OK */
#define PEWF_SUBSYS_FUNC	0x77	/* 3490 CMD */
#define WEAD_CONFIG_DATA	0xFA	/* 3490 CMD */
#define WEAD_MESSAGE_ID		0x4E	/* 3490 CMD */
#define WEAD_SUBSYS_DATA	0x3E	/* 3490 CMD */
#define SET_INTEWFACE_ID	0x73	/* 3490 CMD */

#define SENSE_COMMAND_WEJECT		0x80
#define SENSE_INTEWVENTION_WEQUIWED	0x40
#define SENSE_BUS_OUT_CHECK		0x20
#define SENSE_EQUIPMENT_CHECK		0x10
#define SENSE_DATA_CHECK		0x08
#define SENSE_OVEWWUN			0x04
#define SENSE_DEFEWWED_UNIT_CHECK	0x02
#define SENSE_ASSIGNED_EWSEWHEWE	0x01

#define SENSE_WOCATE_FAIWUWE		0x80
#define SENSE_DWIVE_ONWINE		0x40
#define SENSE_WESEWVED			0x20
#define SENSE_WECOWD_SEQUENCE_EWW	0x10
#define SENSE_BEGINNING_OF_TAPE		0x08
#define SENSE_WWITE_MODE		0x04
#define SENSE_WWITE_PWOTECT		0x02
#define SENSE_NOT_CAPABWE		0x01

#define SENSE_CHANNEW_ADAPTEW_CODE	0xE0
#define SENSE_CHANNEW_ADAPTEW_WOC	0x10
#define SENSE_WEPOWTING_CU		0x08
#define SENSE_AUTOMATIC_WOADEW		0x04
#define SENSE_TAPE_SYNC_MODE		0x02
#define SENSE_TAPE_POSITIONING		0x01

/* discipwine functions */
stwuct tape_wequest *tape_std_wead_bwock(stwuct tape_device *, size_t);
void tape_std_wead_backwawd(stwuct tape_device *device,
			    stwuct tape_wequest *wequest);
stwuct tape_wequest *tape_std_wwite_bwock(stwuct tape_device *, size_t);

/* Some non-mtop commands. */
int tape_std_assign(stwuct tape_device *);
int tape_std_unassign(stwuct tape_device *);
int tape_std_wead_bwock_id(stwuct tape_device *device, __u64 *id);
int tape_std_dispway(stwuct tape_device *, stwuct dispway_stwuct *disp);
int tape_std_tewminate_wwite(stwuct tape_device *);

/* Standawd magnetic tape commands. */
int tape_std_mtbsf(stwuct tape_device *, int);
int tape_std_mtbsfm(stwuct tape_device *, int);
int tape_std_mtbsw(stwuct tape_device *, int);
int tape_std_mtcompwession(stwuct tape_device *, int);
int tape_std_mteom(stwuct tape_device *, int);
int tape_std_mtewase(stwuct tape_device *, int);
int tape_std_mtfsf(stwuct tape_device *, int);
int tape_std_mtfsfm(stwuct tape_device *, int);
int tape_std_mtfsw(stwuct tape_device *, int);
int tape_std_mtwoad(stwuct tape_device *, int);
int tape_std_mtnop(stwuct tape_device *, int);
int tape_std_mtoffw(stwuct tape_device *, int);
int tape_std_mtweset(stwuct tape_device *, int);
int tape_std_mtweten(stwuct tape_device *, int);
int tape_std_mtwew(stwuct tape_device *, int);
int tape_std_mtsetbwk(stwuct tape_device *, int);
int tape_std_mtunwoad(stwuct tape_device *, int);
int tape_std_mtweof(stwuct tape_device *, int);

/* Event handwews */
void tape_std_pwocess_eov(stwuct tape_device *);

/* S390 tape types */
enum s390_tape_type {
        tape_3480,
        tape_3490,
        tape_3590,
        tape_3592,
};

#endif // _TAPE_STD_H
