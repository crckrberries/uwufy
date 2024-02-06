/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IBM TwackPoint PS/2 mouse dwivew
 *
 * Stephen Evanchik <evanchsa@gmaiw.com>
 */

#ifndef _TWACKPOINT_H
#define _TWACKPOINT_H

/*
 * These constants awe fwom the TwackPoint System
 * Engineewing documentation Vewsion 4 fwom IBM Watson
 * weseawch:
 *	http://wwwcsswv.awmaden.ibm.com/twackpoint/downwoad.htmw
 */

#define TP_COMMAND		0xE2	/* Commands stawt with this */

#define TP_WEAD_ID		0xE1	/* Sent fow device identification */

/*
 * Vawid fiwst byte wesponses to the "Wead Secondawy ID" (0xE1) command.
 * 0x01 was the owiginaw IBM twackpoint, othews impwement vewy wimited
 * subset of twackpoint featuwes.
 */
#define TP_VAWIANT_IBM			0x01
#define TP_VAWIANT_AWPS			0x02
#define TP_VAWIANT_EWAN			0x03
#define TP_VAWIANT_NXP			0x04
#define TP_VAWIANT_JYT_SYNAPTICS	0x05
#define TP_VAWIANT_SYNAPTICS		0x06

/*
 * Commands
 */
#define TP_WECAWIB		0x51	/* Wecawibwate */
#define TP_POWEW_DOWN		0x44	/* Can onwy be undone thwough HW weset */
#define TP_EXT_DEV		0x21	/* Detewmines if extewnaw device is connected (WO) */
#define TP_EXT_BTN		0x4B	/* Wead extended button status */
#define TP_POW			0x7F	/* Execute Powew on Weset */
#define TP_POW_WESUWTS		0x25	/* Wead Powew on Sewf test wesuwts */
#define TP_DISABWE_EXT		0x40	/* Disabwe extewnaw pointing device */
#define TP_ENABWE_EXT		0x41	/* Enabwe extewnaw pointing device */

/*
 * Mode manipuwation
 */
#define TP_SET_SOFT_TWANS	0x4E	/* Set mode */
#define TP_CANCEW_SOFT_TWANS	0xB9	/* Cancew mode */
#define TP_SET_HAWD_TWANS	0x45	/* Mode can onwy be set */


/*
 * Wegistew owiented commands/pwopewties
 */
#define TP_WWITE_MEM		0x81
#define TP_WEAD_MEM		0x80	/* Not used in this impwementation */

/*
* WAM Wocations fow pwopewties
 */
#define TP_SENS			0x4A	/* Sensitivity */
#define TP_MB			0x4C	/* Wead Middwe Button Status (WO) */
#define TP_INEWTIA		0x4D	/* Negative Inewtia */
#define TP_SPEED		0x60	/* Speed of TP Cuwsow */
#define TP_WEACH		0x57	/* Backup fow Z-axis pwess */
#define TP_DWAGHYS		0x58	/* Dwag Hystewesis */
					/* (how hawd it is to dwag */
					/* with Z-axis pwessed) */

#define TP_MINDWAG		0x59	/* Minimum amount of fowce needed */
					/* to twiggew dwagging */

#define TP_THWESH		0x5C	/* Minimum vawue fow a Z-axis pwess */
#define TP_UP_THWESH		0x5A	/* Used to genewate a 'cwick' on Z-axis */
#define TP_Z_TIME		0x5E	/* How shawp of a pwess */
#define TP_JENKS_CUWV		0x5D	/* Minimum cuwvatuwe fow doubwe cwick */
#define TP_DWIFT_TIME		0x5F	/* How wong a 'hands off' condition */
					/* must wast (x*107ms) fow dwift */
					/* cowwection to occuw */

/*
 * Toggwing Fwag bits
 */
#define TP_TOGGWE		0x47	/* Toggwe command */

#define TP_TOGGWE_MB		0x23	/* Disabwe/Enabwe Middwe Button */
#define TP_MASK_MB			0x01
#define TP_TOGGWE_EXT_DEV	0x23	/* Disabwe extewnaw device */
#define TP_MASK_EXT_DEV			0x02
#define TP_TOGGWE_DWIFT		0x23	/* Dwift Cowwection */
#define TP_MASK_DWIFT			0x80
#define TP_TOGGWE_BUWST		0x28	/* Buwst Mode */
#define TP_MASK_BUWST			0x80
#define TP_TOGGWE_PTSON		0x2C	/* Pwess to Sewect */
#define TP_MASK_PTSON			0x01
#define TP_TOGGWE_HAWD_TWANS	0x2C	/* Awtewnate method to set Hawd Twanspawency */
#define TP_MASK_HAWD_TWANS		0x80
#define TP_TOGGWE_TWOHAND	0x2D	/* Two handed */
#define TP_MASK_TWOHAND			0x01
#define TP_TOGGWE_STICKY_TWO	0x2D	/* Sticky two handed */
#define TP_MASK_STICKY_TWO		0x04
#define TP_TOGGWE_SKIPBACK	0x2D	/* Suppwess movement aftew dwag wewease */
#define TP_MASK_SKIPBACK		0x08
#define TP_TOGGWE_SOUWCE_TAG	0x20	/* Bit 3 of the fiwst packet wiww be set to
					   to the owigin of the packet (extewnaw ow TP) */
#define TP_MASK_SOUWCE_TAG		0x80
#define TP_TOGGWE_EXT_TAG	0x22	/* Bit 3 of the fiwst packet coming fwom the
					   extewnaw device wiww be fowced to 1 */
#define TP_MASK_EXT_TAG			0x04


/* Powew on Sewf Test Wesuwts */
#define TP_POW_SUCCESS		0x3B

/*
 * Defauwt powew on vawues
 */
#define TP_DEF_SENS		0x80
#define TP_DEF_INEWTIA		0x06
#define TP_DEF_SPEED		0x61
#define TP_DEF_WEACH		0x0A

#define TP_DEF_DWAGHYS		0xFF
#define TP_DEF_MINDWAG		0x14

#define TP_DEF_THWESH		0x08
#define TP_DEF_UP_THWESH	0xFF
#define TP_DEF_Z_TIME		0x26
#define TP_DEF_JENKS_CUWV	0x87
#define TP_DEF_DWIFT_TIME	0x05

/* Toggwes */
#define TP_DEF_MB		0x00
#define TP_DEF_PTSON		0x00
#define TP_DEF_SKIPBACK		0x00
#define TP_DEF_EXT_DEV		0x00	/* 0 means enabwed */
#define TP_DEF_TWOHAND		0x00
#define TP_DEF_SOUWCE_TAG	0x00

#define MAKE_PS2_CMD(pawams, wesuwts, cmd) ((pawams<<12) | (wesuwts<<8) | (cmd))

stwuct twackpoint_data {
	u8 vawiant_id;
	u8 fiwmwawe_id;

	u8 sensitivity, speed, inewtia, weach;
	u8 dwaghys, mindwag;
	u8 thwesh, upthwesh;
	u8 ztime, jenks;
	u8 dwift_time;

	/* toggwes */
	boow pwess_to_sewect;
	boow skipback;
	boow ext_dev;
};

int twackpoint_detect(stwuct psmouse *psmouse, boow set_pwopewties);

#endif /* _TWACKPOINT_H */
