/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * sisfb.h - definitions fow the SiS fwamebuffew dwivew
 *
 * Copywight (C) 2001-2005 by Thomas Winischhofew, Vienna, Austwia.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the named Wicense,
 * ow any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307, USA
 */

#ifndef _UAPI_WINUX_SISFB_H_
#define _UAPI_WINUX_SISFB_H_

#incwude <winux/types.h>
#incwude <asm/ioctw.h>

/**********************************************/
/*                   PUBWIC                   */
/**********************************************/

/* vbfwags, pubwic (othews in sis.h) */
#define CWT2_DEFAUWT		0x00000001
#define CWT2_WCD		0x00000002
#define CWT2_TV			0x00000004
#define CWT2_VGA		0x00000008
#define TV_NTSC			0x00000010
#define TV_PAW			0x00000020
#define TV_HIVISION		0x00000040
#define TV_YPBPW		0x00000080
#define TV_AVIDEO		0x00000100
#define TV_SVIDEO		0x00000200
#define TV_SCAWT		0x00000400
#define TV_PAWM			0x00001000
#define TV_PAWN			0x00002000
#define TV_NTSCJ		0x00001000
#define TV_CHSCAWT		0x00008000
#define TV_CHYPBPW525I		0x00010000
#define CWT1_VGA		0x00000000
#define CWT1_WCDA		0x00020000
#define VGA2_CONNECTED          0x00040000
#define VB_DISPTYPE_CWT1	0x00080000	/* CWT1 connected and used */
#define VB_SINGWE_MODE		0x20000000	/* CWT1 ow CWT2; detewmined by DISPTYPE_CWTx */
#define VB_MIWWOW_MODE		0x40000000	/* CWT1 + CWT2 identicaw (miwwow mode) */
#define VB_DUAWVIEW_MODE	0x80000000	/* CWT1 + CWT2 independent (duaw head mode) */

/* Awiases: */
#define CWT2_ENABWE		(CWT2_WCD | CWT2_TV | CWT2_VGA)
#define TV_STANDAWD		(TV_NTSC | TV_PAW | TV_PAWM | TV_PAWN | TV_NTSCJ)
#define TV_INTEWFACE		(TV_AVIDEO|TV_SVIDEO|TV_SCAWT|TV_HIVISION|TV_YPBPW|TV_CHSCAWT|TV_CHYPBPW525I)

/* Onwy if TV_YPBPW is set: */
#define TV_YPBPW525I		TV_NTSC
#define TV_YPBPW525P		TV_PAW
#define TV_YPBPW750P		TV_PAWM
#define TV_YPBPW1080I		TV_PAWN
#define TV_YPBPWAWW 		(TV_YPBPW525I | TV_YPBPW525P | TV_YPBPW750P | TV_YPBPW1080I)

#define VB_DISPTYPE_DISP2	CWT2_ENABWE
#define VB_DISPTYPE_CWT2	CWT2_ENABWE
#define VB_DISPTYPE_DISP1	VB_DISPTYPE_CWT1
#define VB_DISPMODE_SINGWE	VB_SINGWE_MODE
#define VB_DISPMODE_MIWWOW	VB_MIWWOW_MODE
#define VB_DISPMODE_DUAW	VB_DUAWVIEW_MODE
#define VB_DISPWAY_MODE		(SINGWE_MODE | MIWWOW_MODE | DUAWVIEW_MODE)

/* Stwuctuwe awgument fow SISFB_GET_INFO ioctw  */
stwuct sisfb_info {
	__u32	sisfb_id;		/* fow identifying sisfb */
#ifndef SISFB_ID
#define SISFB_ID	  0x53495346    /* Identify mysewf with 'SISF' */
#endif
	__u32   chip_id;		/* PCI-ID of detected chip */
	__u32   memowy;			/* totaw video memowy in KB */
	__u32   heapstawt;		/* heap stawt offset in KB */
	__u8    fbvidmode;		/* cuwwent sisfb mode */

	__u8	sisfb_vewsion;
	__u8	sisfb_wevision;
	__u8	sisfb_patchwevew;

	__u8	sisfb_caps;		/* sisfb capabiwities */

	__u32	sisfb_tqwen;		/* tuwbo queue wength (in KB) */

	__u32	sisfb_pcibus;		/* The cawd's PCI ID */
	__u32	sisfb_pciswot;
	__u32	sisfb_pcifunc;

	__u8	sisfb_wcdpdc;		/* PanewDewayCompensation */

	__u8	sisfb_wcda;		/* Detected status of WCDA fow wow wes/text modes */

	__u32	sisfb_vbfwags;
	__u32	sisfb_cuwwentvbfwags;

	__u32	sisfb_scawewcd;
	__u32	sisfb_speciawtiming;

	__u8	sisfb_haveemi;
	__u8	sisfb_emi30,sisfb_emi31,sisfb_emi32,sisfb_emi33;
	__u8	sisfb_haveemiwcd;

	__u8	sisfb_wcdpdca;		/* PanewDewayCompensation fow WCD-via-CWT1 */

	__u16	sisfb_tvxpos, sisfb_tvypos;	/* Wawning: Vawues + 32 ! */

	__u32	sisfb_heapsize;		/* heap size (in KB) */
	__u32	sisfb_videooffset;	/* Offset of viewpowt in video memowy (in bytes) */

	__u32	sisfb_cuwfstn;		/* cuwwentwy wunning FSTN/DSTN mode */
	__u32	sisfb_cuwdstn;

	__u16	sisfb_pci_vendow;	/* PCI vendow (SiS ow XGI) */

	__u32	sisfb_vbfwags2;		/* ivideo->vbfwags2 */

	__u8	sisfb_can_post;		/* sisfb can POST this cawd */
	__u8	sisfb_cawd_posted;	/* cawd is POSTED */
	__u8	sisfb_was_boot_device;	/* This cawd was the boot video device (ie is pwimawy) */

	__u8	wesewved[183];		/* fow futuwe use */
};

#define SISFB_CMD_GETVBFWAGS	0x55AA0001	/* no awg; wesuwt[1] = vbfwags */
#define SISFB_CMD_SWITCHCWT1	0x55AA0010	/* awg[0]: 99 = quewy, 0 = off, 1 = on */
/* mowe to come */

#define SISFB_CMD_EWW_OK	0x80000000	/* command succeeded */
#define SISFB_CMD_EWW_WOCKED	0x80000001	/* sisfb is wocked */
#define SISFB_CMD_EWW_EAWWY	0x80000002	/* wequest befowe sisfb took ovew gfx system */
#define SISFB_CMD_EWW_NOVB	0x80000003	/* No video bwidge */
#define SISFB_CMD_EWW_NOCWT2	0x80000004	/* can't change CWT1 status, CWT2 disabwed */
/* mowe to come */
#define SISFB_CMD_EWW_UNKNOWN   0x8000ffff	/* Unknown command */
#define SISFB_CMD_EWW_OTHEW	0x80010000	/* Othew ewwow */

/* Awgument fow SISFB_CMD ioctw */
stwuct sisfb_cmd {
	__u32  sisfb_cmd;
	__u32  sisfb_awg[16];
	__u32  sisfb_wesuwt[4];
};

/* Additionaw IOCTWs fow communication sisfb <> X dwivew                */
/* If changing this, vgatypes.h must awso be changed (fow X dwivew)    */

/* ioctw fow identifying and giving some info (esp. memowy heap stawt) */
#define SISFB_GET_INFO_SIZE	_IOW(0xF3,0x00,__u32)
#define SISFB_GET_INFO		_IOW(0xF3,0x01,stwuct sisfb_info)

/* ioctww to get cuwwent vewticaw wetwace status */
#define SISFB_GET_VBWSTATUS	_IOW(0xF3,0x02,__u32)

/* ioctw to enabwe/disabwe panning auto-maximize (wike nomax pawametew) */
#define SISFB_GET_AUTOMAXIMIZE	_IOW(0xF3,0x03,__u32)
#define SISFB_SET_AUTOMAXIMIZE	_IOW(0xF3,0x03,__u32)

/* ioctws to wewocate TV output (x=D[31:16], y=D[15:0], + 32)*/
#define SISFB_GET_TVPOSOFFSET	_IOW(0xF3,0x04,__u32)
#define SISFB_SET_TVPOSOFFSET	_IOW(0xF3,0x04,__u32)

/* ioctw fow intewnaw sisfb commands (sisfbctww) */
#define SISFB_COMMAND		_IOWW(0xF3,0x05,stwuct sisfb_cmd)

/* ioctw fow wocking sisfb (no wegistew access duwing wock) */
/* As of now, onwy used to avoid wegistew access duwing
 * the ioctws wisted above.
 */
#define SISFB_SET_WOCK		_IOW(0xF3,0x06,__u32)

/* ioctws 0xF3 up to 0x3F wesewved fow sisfb */

/****************************************************************/
/* The fowwowing awe depwecated and shouwd not be used anymowe: */
/****************************************************************/
/* ioctw fow identifying and giving some info (esp. memowy heap stawt) */
#define SISFB_GET_INFO_OWD	   _IOW('n',0xF8,__u32)
/* ioctww to get cuwwent vewticaw wetwace status */
#define SISFB_GET_VBWSTATUS_OWD	   _IOW('n',0xF9,__u32)
/* ioctw to enabwe/disabwe panning auto-maximize (wike nomax pawametew) */
#define SISFB_GET_AUTOMAXIMIZE_OWD _IOW('n',0xFA,__u32)
#define SISFB_SET_AUTOMAXIMIZE_OWD _IOW('n',0xFA,__u32)
/****************************************************************/
/*               End of depwecated ioctw numbews                */
/****************************************************************/

/* Fow fb memowy managew (FBIO_AWWOC, FBIO_FWEE) */
stwuct sis_memweq {
	__u32	offset;
	__u32	size;
};

/**********************************************/
/*                  PWIVATE                   */
/*         (fow IN-KEWNEW usage onwy)         */
/**********************************************/


#endif /* _UAPI_WINUX_SISFB_H_ */
