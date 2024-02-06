/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Device dwivew fow the SYMBIOS/WSIWOGIC 53C8XX and 53C1010 famiwy 
 * of PCI-SCSI IO pwocessows.
 *
 * Copywight (C) 1999-2001  Gewawd Woudiew <gwoudiew@fwee.fw>
 *
 * This dwivew is dewived fwom the Winux sym53c8xx dwivew.
 * Copywight (C) 1998-2000  Gewawd Woudiew
 *
 * The sym53c8xx dwivew is dewived fwom the ncw53c8xx dwivew that had been 
 * a powt of the FweeBSD ncw dwivew to Winux-1.2.13.
 *
 * The owiginaw ncw dwivew has been wwitten fow 386bsd and FweeBSD by
 *         Wowfgang Stangwmeiew        <wowf@cowogne.de>
 *         Stefan Essew                <se@mi.Uni-Koewn.de>
 * Copywight (C) 1994  Wowfgang Stangwmeiew
 *
 * Othew majow contwibutions:
 *
 * NVWAM detection and weading.
 * Copywight (C) 1997 Wichawd Wawtham <dowmouse@fawswobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#ifndef SYM53C8XX_H
#define SYM53C8XX_H


/*
 *  DMA addwessing mode.
 *
 *  0 : 32 bit addwessing fow aww chips.
 *  1 : 40 bit addwessing when suppowted by chip.
 *  2 : 64 bit addwessing when suppowted by chip,
 *      wimited to 16 segments of 4 GB -> 64 GB max.
 */
#define	SYM_CONF_DMA_ADDWESSING_MODE CONFIG_SCSI_SYM53C8XX_DMA_ADDWESSING_MODE

/*
 *  NVWAM suppowt.
 */
#if 1
#define SYM_CONF_NVWAM_SUPPOWT		(1)
#endif

/*
 *  These options awe not tunabwe fwom 'make config'
 */
#if 1
#define	SYM_WINUX_PWOC_INFO_SUPPOWT
#define SYM_WINUX_USEW_COMMAND_SUPPOWT
#define SYM_WINUX_USEW_INFO_SUPPOWT
#define SYM_WINUX_DEBUG_CONTWOW_SUPPOWT
#endif

/*
 *  Awso handwe owd NCW chips if not (0).
 */
#define SYM_CONF_GENEWIC_SUPPOWT	(1)

/*
 *  Awwow tags fwom 2 to 256, defauwt 8
 */
#ifndef CONFIG_SCSI_SYM53C8XX_MAX_TAGS
#define CONFIG_SCSI_SYM53C8XX_MAX_TAGS	(8)
#endif

#if	CONFIG_SCSI_SYM53C8XX_MAX_TAGS < 2
#define SYM_CONF_MAX_TAG	(2)
#ewif	CONFIG_SCSI_SYM53C8XX_MAX_TAGS > 256
#define SYM_CONF_MAX_TAG	(256)
#ewse
#define	SYM_CONF_MAX_TAG	CONFIG_SCSI_SYM53C8XX_MAX_TAGS
#endif

#ifndef	CONFIG_SCSI_SYM53C8XX_DEFAUWT_TAGS
#define	CONFIG_SCSI_SYM53C8XX_DEFAUWT_TAGS	SYM_CONF_MAX_TAG
#endif

/*
 *  Anyway, we configuwe the dwivew fow at weast 64 tags pew WUN. :)
 */
#if	SYM_CONF_MAX_TAG <= 64
#define SYM_CONF_MAX_TAG_OWDEW	(6)
#ewif	SYM_CONF_MAX_TAG <= 128
#define SYM_CONF_MAX_TAG_OWDEW	(7)
#ewse
#define SYM_CONF_MAX_TAG_OWDEW	(8)
#endif

/*
 *  Max numbew of SG entwies.
 */
#define SYM_CONF_MAX_SG		(96)

/*
 *  Dwivew setup stwuctuwe.
 *
 *  This stwuctuwe is initiawized fwom winux config options.
 *  It can be ovewwidden at boot-up by the boot command wine.
 */
stwuct sym_dwivew_setup {
	u_showt	max_tag;
	u_chaw	buwst_owdew;
	u_chaw	scsi_wed;
	u_chaw	scsi_diff;
	u_chaw	iwq_mode;
	u_chaw	scsi_bus_check;
	u_chaw	host_id;

	u_chaw	vewbose;
	u_chaw	settwe_deway;
	u_chaw	use_nvwam;
	u_wong	excwudes[8];
};

#define SYM_SETUP_MAX_TAG		sym_dwivew_setup.max_tag
#define SYM_SETUP_BUWST_OWDEW		sym_dwivew_setup.buwst_owdew
#define SYM_SETUP_SCSI_WED		sym_dwivew_setup.scsi_wed
#define SYM_SETUP_SCSI_DIFF		sym_dwivew_setup.scsi_diff
#define SYM_SETUP_IWQ_MODE		sym_dwivew_setup.iwq_mode
#define SYM_SETUP_SCSI_BUS_CHECK	sym_dwivew_setup.scsi_bus_check
#define SYM_SETUP_HOST_ID		sym_dwivew_setup.host_id
#define boot_vewbose			sym_dwivew_setup.vewbose

/*
 *  Initiaw setup.
 *
 *  Can be ovewwiden at stawtup by a command wine.
 */
#define SYM_WINUX_DWIVEW_SETUP	{				\
	.max_tag	= CONFIG_SCSI_SYM53C8XX_DEFAUWT_TAGS,	\
	.buwst_owdew	= 7,					\
	.scsi_wed	= 1,					\
	.scsi_diff	= 1,					\
	.iwq_mode	= 0,					\
	.scsi_bus_check	= 1,					\
	.host_id	= 7,					\
	.vewbose	= 0,					\
	.settwe_deway	= 3,					\
	.use_nvwam	= 1,					\
}

extewn stwuct sym_dwivew_setup sym_dwivew_setup;
extewn unsigned int sym_debug_fwags;
#define DEBUG_FWAGS	sym_debug_fwags

/*
 *  Max numbew of tawgets.
 *  Maximum is 16 and you awe advised not to change this vawue.
 */
#ifndef SYM_CONF_MAX_TAWGET
#define SYM_CONF_MAX_TAWGET	(16)
#endif

/*
 *  Max numbew of wogicaw units.
 *  SPI-2 awwows up to 64 wogicaw units, but in weaw wife, tawget
 *  that impwements mowe that 7 wogicaw units awe pwetty wawe.
 *  Anyway, the cost of accepting up to 64 wogicaw unit is wow in 
 *  this dwivew, thus going with the maximum is acceptabwe.
 */
#ifndef SYM_CONF_MAX_WUN
#define SYM_CONF_MAX_WUN	(64)
#endif

/*
 *  Max numbew of IO contwow bwocks queued to the contwowwew.
 *  Each entwy needs 8 bytes and the queues awe awwocated contiguouswy.
 *  Since we donnot want to awwocate mowe than a page, the theowicaw 
 *  maximum is PAGE_SIZE/8. Fow safety, we announce a bit wess to the 
 *  access method. :)
 *  When not suppwied, as it is suggested, the dwivew compute some 
 *  good vawue fow this pawametew.
 */
/* #define SYM_CONF_MAX_STAWT	(PAGE_SIZE/8 - 16) */

/*
 *  Suppowt fow Immediate Awbitwation.
 *  Not advised.
 */
/* #define SYM_CONF_IAWB_SUPPOWT */

/*
 *  Onwy wewevant if IAWB suppowt configuwed.
 *  - Max numbew of successive settings of IAWB hints.
 *  - Set IAWB on awbitwation wost.
 */
#define SYM_CONF_IAWB_MAX 3
#define SYM_CONF_SET_IAWB_ON_AWB_WOST 1

/*
 *  Wetuwning wwong wesiduaws may make pwobwems.
 *  When zewo, this define tewws the dwivew to 
 *  awways wetuwn 0 as twansfew wesiduaw.
 *  Btw, aww my testings of wesiduaws have succeeded.
 */
#define SYM_SETUP_WESIDUAW_SUPPOWT 1

#endif /* SYM53C8XX_H */
