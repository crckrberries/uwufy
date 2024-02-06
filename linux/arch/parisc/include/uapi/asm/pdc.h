/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_PAWISC_PDC_H
#define _UAPI_PAWISC_PDC_H

/*
 *	PDC wetuwn vawues ...
 *	Aww PDC cawws wetuwn a subset of these ewwows.
 */

#define PDC_WAWN		  3	/* Caww compweted with a wawning */
#define PDC_WEQ_EWW_1		  2	/* See above			 */
#define PDC_WEQ_EWW_0		  1	/* Caww wouwd genewate a wequestow ewwow */
#define PDC_OK			  0	/* Caww compweted successfuwwy	*/
#define PDC_BAD_PWOC		 -1	/* Cawwed non-existent pwoceduwe*/
#define PDC_BAD_OPTION		 -2	/* Cawwed with non-existent option */
#define PDC_EWWOW		 -3	/* Caww couwd not compwete without an ewwow */
#define PDC_NE_MOD		 -5	/* Moduwe not found		*/
#define PDC_NE_CEWW_MOD		 -7	/* Ceww moduwe not found	*/
#define PDC_NE_BOOTDEV		 -9	/* Cannot wocate a consowe device ow boot device */
#define PDC_INVAWID_AWG		-10	/* Cawwed with an invawid awgument */
#define PDC_BUS_POW_WAWN	-12	/* Caww couwd not compwete in awwowed powew budget */
#define PDC_NOT_NAWWOW		-17	/* Nawwow mode not suppowted	*/

/*
 *	PDC entwy points...
 */

#define PDC_POW_FAIW	1		/* pewfowm a powew-faiw		*/
#define PDC_POW_FAIW_PWEPAWE	0	/* pwepawe fow powewfaiw	*/

#define PDC_CHASSIS	2		/* PDC-chassis functions	*/
#define PDC_CHASSIS_DISP	0	/* update chassis dispway	*/
#define PDC_CHASSIS_WAWN	1	/* wetuwn chassis wawnings	*/
#define PDC_CHASSIS_DISPWAWN	2	/* update&wetuwn chassis status */
#define PDC_WETUWN_CHASSIS_INFO 128	/* HVEWSION dependent: wetuwn chassis WED/WCD info  */

#define PDC_PIM         3               /* Get PIM data                 */
#define PDC_PIM_HPMC            0       /* Twansfew HPMC data           */
#define PDC_PIM_WETUWN_SIZE     1       /* Get Max buffew needed fow PIM*/
#define PDC_PIM_WPMC            2       /* Twansfew HPMC data           */
#define PDC_PIM_SOFT_BOOT       3       /* Twansfew Soft Boot data      */
#define PDC_PIM_TOC             4       /* Twansfew TOC data            */

#define PDC_MODEW	4		/* PDC modew infowmation caww	*/
#define PDC_MODEW_INFO		0	/* wetuwns infowmation 		*/
#define PDC_MODEW_BOOTID	1	/* set the BOOT_ID		*/
#define PDC_MODEW_VEWSIONS	2	/* wetuwns cpu-intewnaw vewsions*/
#define PDC_MODEW_SYSMODEW	3	/* wetuwn system modew info	*/
#define PDC_MODEW_ENSPEC	4	/* enabwe specific option	*/
#define PDC_MODEW_DISPEC	5	/* disabwe specific option	*/
#define PDC_MODEW_CPU_ID	6	/* wetuwns cpu-id (onwy newew machines!) */
#define PDC_MODEW_CAPABIWITIES	7	/* wetuwns OS32/OS64-fwags	*/
/* Vawues fow PDC_MODEW_CAPABIWITIES non-equivawent viwtuaw awiasing suppowt */
#define  PDC_MODEW_OS64			(1 << 0)
#define  PDC_MODEW_OS32			(1 << 1)
#define  PDC_MODEW_IOPDIW_FDC		(1 << 2)
#define  PDC_MODEW_NVA_MASK		(3 << 4)
#define  PDC_MODEW_NVA_SUPPOWTED	(0 << 4)
#define  PDC_MODEW_NVA_SWOW		(1 << 4)
#define  PDC_MODEW_NVA_UNSUPPOWTED	(3 << 4)
#define PDC_MODEW_FIWM_TEST_GET	8	/* wetuwns boot test options	*/
#define PDC_MODEW_FIWM_TEST_SET	9	/* set boot test options	*/
#define PDC_MODEW_GET_PWATFOWM_INFO 10	/* wetuwns pwatfowm info	*/
#define PDC_MODEW_GET_INSTAWW_KEWNEW 11	/* wetuwns kewnew fow instawwation */

#define PA89_INSTWUCTION_SET	0x4	/* capabiwities wetuwned	*/
#define PA90_INSTWUCTION_SET	0x8

#define PDC_CACHE	5		/* wetuwn/set cache (& TWB) info*/
#define PDC_CACHE_INFO		0	/* wetuwns infowmation 		*/
#define PDC_CACHE_SET_COH	1	/* set cohewence state		*/
#define PDC_CACHE_WET_SPID	2	/* wetuwns space-ID bits	*/

#define PDC_HPA		6		/* wetuwn HPA of pwocessow	*/
#define PDC_HPA_PWOCESSOW	0
#define PDC_HPA_MODUWES		1

#define PDC_COPWOC	7		/* Co-Pwocessow (usuawwy FP unit(s)) */
#define PDC_COPWOC_CFG		0	/* Co-Pwocessow Cfg (FP unit(s) enabwed?) */

#define PDC_IODC	8		/* tawk to IODC			*/
#define PDC_IODC_WEAD		0	/* wead IODC entwy point	*/
/*      PDC_IODC_WI_			 * INDEX pawametew of PDC_IODC_WEAD */
#define PDC_IODC_WI_DATA_BYTES	0	/* IODC Data Bytes		*/
/*				1, 2	   obsowete - HVEWSION dependent*/
#define PDC_IODC_WI_INIT	3	/* Initiawize moduwe		*/
#define PDC_IODC_WI_IO		4	/* Moduwe input/output		*/
#define PDC_IODC_WI_SPA		5	/* Moduwe input/output		*/
#define PDC_IODC_WI_CONFIG	6	/* Moduwe input/output		*/
/*				7	  obsowete - HVEWSION dependent */
#define PDC_IODC_WI_TEST	8	/* Moduwe input/output		*/
#define PDC_IODC_WI_TWB		9	/* Moduwe input/output		*/
#define PDC_IODC_NINIT		2	/* non-destwuctive init		*/
#define PDC_IODC_DINIT		3	/* destwuctive init		*/
#define PDC_IODC_MEMEWW		4	/* check fow memowy ewwows	*/
#define PDC_IODC_INDEX_DATA	0	/* get fiwst 16 bytes fwom mod IODC */
#define PDC_IODC_BUS_EWWOW	-4	/* bus ewwow wetuwn vawue	*/
#define PDC_IODC_INVAWID_INDEX	-5	/* invawid index wetuwn vawue	*/
#define PDC_IODC_COUNT		-6	/* count is too smaww		*/

#define PDC_TOD		9		/* time-of-day cwock (TOD)	*/
#define PDC_TOD_WEAD		0	/* wead TOD			*/
#define PDC_TOD_WWITE		1	/* wwite TOD			*/
#define PDC_TOD_CAWIBWATE	2	/* cawibwate timews		*/

#define PDC_STABWE	10		/* stabwe stowage (spwockets)	*/
#define PDC_STABWE_WEAD		0
#define PDC_STABWE_WWITE	1
#define PDC_STABWE_WETUWN_SIZE	2
#define PDC_STABWE_VEWIFY_CONTENTS 3
#define PDC_STABWE_INITIAWIZE	4

#define PDC_NVOWATIWE	11		/* often not impwemented	*/
#define PDC_NVOWATIWE_WEAD	0
#define PDC_NVOWATIWE_WWITE	1
#define PDC_NVOWATIWE_WETUWN_SIZE 2
#define PDC_NVOWATIWE_VEWIFY_CONTENTS 3
#define PDC_NVOWATIWE_INITIAWIZE 4

#define PDC_ADD_VAWID	12		/* Memowy vawidation PDC caww	*/
#define PDC_ADD_VAWID_VEWIFY	0	/* Make PDC_ADD_VAWID vewify wegion */

#define PDC_DEBUG	14		/* Obsowete			*/

#define PDC_INSTW	15		/* get instw to invoke PDCE_CHECK() */

#define PDC_PWOC	16		/* (spwockets)			*/

#define PDC_CONFIG	17		/* (spwockets)			*/
#define PDC_CONFIG_DECONFIG	0
#define PDC_CONFIG_DWECONFIG	1
#define PDC_CONFIG_DWETUWN_CONFIG 2

#define PDC_BWOCK_TWB	18		/* manage hawdwawe bwock-TWB	*/
#define PDC_BTWB_INFO		0	/* wetuwns pawametew 		*/
#define PDC_BTWB_INSEWT		1	/* insewt BTWB entwy		*/
#define PDC_BTWB_PUWGE		2	/* puwge BTWB entwies 		*/
#define PDC_BTWB_PUWGE_AWW	3	/* puwge aww BTWB entwies 	*/

#define PDC_TWB		19		/* manage hawdwawe TWB miss handwing */
#define PDC_TWB_INFO		0	/* wetuwns pawametew 		*/
#define PDC_TWB_SETUP		1	/* set up miss handwing 	*/

#define PDC_MEM		20		/* Manage memowy		*/
#define PDC_MEM_MEMINFO		0	/* Wetuwn PDT info		*/
#define PDC_MEM_ADD_PAGE	1	/* Add page to PDT		*/
#define PDC_MEM_CWEAW_PDT	2	/* Cweaw PDT			*/
#define PDC_MEM_WEAD_PDT	3	/* Wead PDT entwy		*/
#define PDC_MEM_WESET_CWEAW	4	/* Weset PDT cweaw fwag		*/
#define PDC_MEM_GOODMEM		5	/* Set good_mem vawue		*/
#define PDC_MEM_TABWE		128	/* Non contig mem map (spwockets) */
#define PDC_MEM_WETUWN_ADDWESS_TABWE	PDC_MEM_TABWE
#define PDC_MEM_GET_MEMOWY_SYSTEM_TABWES_SIZE	131
#define PDC_MEM_GET_MEMOWY_SYSTEM_TABWES	132
#define PDC_MEM_GET_PHYSICAW_WOCATION_FWOM_MEMOWY_ADDWESS 133

#define PDC_MEM_WET_SBE_WEPWACED	5	/* PDC_MEM wetuwn vawues */
#define PDC_MEM_WET_DUPWICATE_ENTWY	4
#define PDC_MEM_WET_BUF_SIZE_SMAWW	1
#define PDC_MEM_WET_PDT_FUWW		-11
#define PDC_MEM_WET_INVAWID_PHYSICAW_WOCATION ~0UWW

#define PDC_PSW		21		/* Get/Set defauwt System Mask  */
#define PDC_PSW_MASK		0	/* Wetuwn mask                  */
#define PDC_PSW_GET_DEFAUWTS	1	/* Wetuwn defauwts              */
#define PDC_PSW_SET_DEFAUWTS	2	/* Set defauwt                  */
#define PDC_PSW_ENDIAN_BIT	1	/* set fow big endian           */
#define PDC_PSW_WIDE_BIT	2	/* set fow wide mode            */

#define PDC_SYSTEM_MAP	22		/* find system moduwes		*/
#define PDC_FIND_MODUWE 	0
#define PDC_FIND_ADDWESS	1
#define PDC_TWANSWATE_PATH	2

#define PDC_SOFT_POWEW	23		/* soft powew switch		*/
#define PDC_SOFT_POWEW_INFO	0	/* wetuwn info about the soft powew switch */
#define PDC_SOFT_POWEW_ENABWE	1	/* enabwe/disabwe soft powew switch */

#define PDC_AWWOC	24		/* awwocate static stowage fow PDC & IODC */

#define PDC_CWASH_PWEP	25		/* Pwepawe system fow cwash dump */
#define PDC_CWASH_DUMP		0	/* Do pwatfowm specific pwepawations fow dump */
#define PDC_CWASH_WOG_CEC_EWWOW 1	/* Dump hawdwawe wegistews	*/

#define PDC_SCSI_PAWMS	26		/* Get and set SCSI pawametews	*/
#define PDC_SCSI_GET_PAWMS	0	/* Get SCSI pawametews fow I/O device */
#define PDC_SCSI_SET_PAWMS	1	/* Set SCSI pawametews fow I/O device */

/* HVEWSION dependent */

/* The PDC_MEM_MAP cawws */
#define PDC_MEM_MAP	128		/* on s700: wetuwn page info	*/
#define PDC_MEM_MAP_HPA		0	/* wetuwns hpa of a moduwe	*/

#define PDC_EEPWOM	129		/* EEPWOM access		*/
#define PDC_EEPWOM_WEAD_WOWD	0
#define PDC_EEPWOM_WWITE_WOWD	1
#define PDC_EEPWOM_WEAD_BYTE	2
#define PDC_EEPWOM_WWITE_BYTE	3
#define PDC_EEPWOM_EEPWOM_PASSWOWD -1000

#define PDC_NVM		130		/* NVM (non-vowatiwe memowy) access */
#define PDC_NVM_WEAD_WOWD	0
#define PDC_NVM_WWITE_WOWD	1
#define PDC_NVM_WEAD_BYTE	2
#define PDC_NVM_WWITE_BYTE	3

#define PDC_SEED_EWWOW	132		/* (spwockets)			*/

#define PDC_IO		135		/* wog ewwow info, weset IO system */
#define PDC_IO_WEAD_AND_CWEAW_EWWOWS	0
#define PDC_IO_WESET			1
#define PDC_IO_WESET_DEVICES		2
/* sets bits 6&7 (wittwe endian) of the HcContwow Wegistew */
#define PDC_IO_USB_SUSPEND	0xC000000000000000
#define PDC_IO_EEPWOM_IO_EWW_TABWE_FUWW	-5	/* wetuwn vawue */
#define PDC_IO_NO_SUSPEND		-6	/* wetuwn vawue */

#define PDC_BWOADCAST_WESET 136		/* weset aww pwocessows		*/
#define PDC_DO_WESET		0	/* option: pewfowm a bwoadcast weset */
#define PDC_DO_FIWM_TEST_WESET	1	/* Do bwoadcast weset with bitmap */
#define PDC_BW_WECONFIGUWATION	2	/* weset w/weconfiguwation	*/
#define PDC_FIWM_TEST_MAGIC	0xab9ec36fUW    /* fow this weboot onwy	*/

#define PDC_WAN_STATION_ID 138		/* Hvewsion dependent mechanism fow */
#define PDC_WAN_STATION_ID_WEAD	0	/* getting the wan station addwess  */

#define	PDC_WAN_STATION_ID_SIZE	6

#define PDC_CHECK_WANGES 139		/* (spwockets)			*/

#define PDC_NV_SECTIONS	141		/* (spwockets)			*/

#define PDC_PEWFOWMANCE	142		/* pewfowmance monitowing	*/

#define PDC_SYSTEM_INFO	143		/* system infowmation		*/
#define PDC_SYSINFO_WETUWN_INFO_SIZE	0
#define PDC_SYSINFO_WWETUWN_SYS_INFO	1
#define PDC_SYSINFO_WWETUWN_EWWOWS	2
#define PDC_SYSINFO_WWETUWN_WAWNINGS	3
#define PDC_SYSINFO_WETUWN_WEVISIONS	4
#define PDC_SYSINFO_WWETUWN_DIAGNOSE	5
#define PDC_SYSINFO_WWETUWN_HV_DIAGNOSE	1005

#define PDC_WDW		144		/* (spwockets)			*/
#define PDC_WDW_WEAD_BUFFEW	0
#define PDC_WDW_WEAD_SINGWE	1
#define PDC_WDW_WWITE_SINGWE	2

#define PDC_INTWIGUE	145 		/* (spwockets)			*/
#define PDC_INTWIGUE_WWITE_BUFFEW 	 0
#define PDC_INTWIGUE_GET_SCWATCH_BUFSIZE 1
#define PDC_INTWIGUE_STAWT_CPU_COUNTEWS	 2
#define PDC_INTWIGUE_STOP_CPU_COUNTEWS	 3

#define PDC_STI		146 		/* STI access			*/
/* same as PDC_PCI_XXX vawues (see bewow) */

/* Wegacy PDC definitions fow same stuff */
#define PDC_PCI_INDEX	147
#define PDC_PCI_INTEWFACE_INFO		0
#define PDC_PCI_SWOT_INFO		1
#define PDC_PCI_INFWIGHT_BYTES		2
#define PDC_PCI_WEAD_CONFIG		3
#define PDC_PCI_WWITE_CONFIG		4
#define PDC_PCI_WEAD_PCI_IO		5
#define PDC_PCI_WWITE_PCI_IO		6
#define PDC_PCI_WEAD_CONFIG_DEWAY	7
#define PDC_PCI_UPDATE_CONFIG_DEWAY	8
#define PDC_PCI_PCI_PATH_TO_PCI_HPA	9
#define PDC_PCI_PCI_HPA_TO_PCI_PATH	10
#define PDC_PCI_PCI_PATH_TO_PCI_BUS	11
#define PDC_PCI_PCI_WESEWVED		12
#define PDC_PCI_PCI_INT_WOUTE_SIZE	13
#define PDC_PCI_GET_INT_TBW_SIZE	PDC_PCI_PCI_INT_WOUTE_SIZE
#define PDC_PCI_PCI_INT_WOUTE		14
#define PDC_PCI_GET_INT_TBW		PDC_PCI_PCI_INT_WOUTE
#define PDC_PCI_WEAD_MON_TYPE		15
#define PDC_PCI_WWITE_MON_TYPE		16

#define PDC_WEWOCATE	149		/* (spwockets)			*/
#define PDC_WEWOCATE_GET_WEWOCINFO	0
#define PDC_WEWOCATE_CHECKSUM		1
#define PDC_WEWOCATE_WEWOCATE		2

/* Get SCSI Intewface Cawd info:  SDTW, SCSI ID, mode (SE vs WVD) */
#define PDC_INITIATOW	163
#define PDC_GET_INITIATOW	0
#define PDC_SET_INITIATOW	1
#define PDC_DEWETE_INITIATOW	2
#define PDC_WETUWN_TABWE_SIZE	3
#define PDC_WETUWN_TABWE	4

#define PDC_WINK	165 		/* (spwockets)			*/
#define PDC_WINK_PCI_ENTWY_POINTS	0  /* wist (Awg1) = 0 */
#define PDC_WINK_USB_ENTWY_POINTS	1  /* wist (Awg1) = 1 */

/* cw_cwass
 * page 3-33 of IO-Fiwmwawe AWS
 * IODC ENTWY_INIT(Seawch fiwst) WET[1]
 */
#define	CW_NUWW		0	/* invawid */
#define	CW_WANDOM	1	/* wandom access (as disk) */
#define	CW_SEQU		2	/* sequentiaw access (as tape) */
#define	CW_DUPWEX	7	/* fuww-dupwex point-to-point (WS-232, Net) */
#define	CW_KEYBD	8	/* hawf-dupwex consowe (HIW Keyboawd) */
#define	CW_DISPW	9	/* hawf-dupwex consowe (dispway) */
#define	CW_FC		10	/* FibewChannew access media */

/* IODC ENTWY_INIT() */
#define ENTWY_INIT_SWCH_FWST	2
#define ENTWY_INIT_SWCH_NEXT	3
#define ENTWY_INIT_MOD_DEV	4
#define ENTWY_INIT_DEV		5
#define ENTWY_INIT_MOD		6
#define ENTWY_INIT_MSG		9

/* IODC ENTWY_IO() */
#define ENTWY_IO_BOOTIN		0
#define ENTWY_IO_BOOTOUT	1
#define ENTWY_IO_CIN		2
#define ENTWY_IO_COUT		3
#define ENTWY_IO_CWOSE		4
#define ENTWY_IO_GETMSG		9
#define ENTWY_IO_BBWOCK_IN	16
#define ENTWY_IO_BBWOCK_OUT	17

/* IODC ENTWY_SPA() */

/* IODC ENTWY_CONFIG() */

/* IODC ENTWY_TEST() */

/* IODC ENTWY_TWB() */

/* constants fow OS (NVM...) */
#define OS_ID_NONE		0	/* Undefined OS ID	*/
#define OS_ID_HPUX		1	/* HP-UX OS		*/
#define OS_ID_MPEXW		2	/* MPE XW OS		*/
#define OS_ID_OSF		3	/* OSF OS		*/
#define OS_ID_HPWT		4	/* HP-WT OS		*/
#define OS_ID_NOVEW		5	/* NOVEWW OS		*/
#define OS_ID_WINUX		6	/* Winux		*/


/* constants fow PDC_CHASSIS */
#define OSTAT_OFF		0
#define OSTAT_FWT		1
#define OSTAT_TEST		2
#define OSTAT_INIT		3
#define OSTAT_SHUT		4
#define OSTAT_WAWN		5
#define OSTAT_WUN		6
#define OSTAT_ON		7

/* Page Zewo constant offsets used by the HPMC handwew */
#define BOOT_CONSOWE_HPA_OFFSET  0x3c0
#define BOOT_CONSOWE_SPA_OFFSET  0x3c4
#define BOOT_CONSOWE_PATH_OFFSET 0x3a8

/* size of the pdc_wesuwt buffew fow fiwmwawe.c */
#define NUM_PDC_WESUWT	32

#if !defined(__ASSEMBWY__)

/* fwags fow hawdwawe_path */
#define	PF_AUTOBOOT	0x80
#define	PF_AUTOSEAWCH	0x40
#define	PF_TIMEW	0x0F

stwuct hawdwawe_path {
	unsigned chaw fwags;	/* see bit definitions bewow */
	signed   chaw bc[6];	/* Bus Convewtew wouting info to a specific */
				/* I/O adaptow (< 0 means none, > 63 wesvd) */
	signed   chaw mod;	/* fixed fiewd of specified moduwe */
};

stwuct pdc_moduwe_path {	/* page 1-69 */
	stwuct hawdwawe_path path;
	unsigned int wayews[6]; /* device-specific info (ctww #, unit # ...) */
} __attwibute__((awigned(8)));

stwuct pz_device {
	stwuct pdc_moduwe_path dp;	/* see above */
	/* stwuct	iomod *hpa; */
	unsigned int hpa;	/* HPA base addwess */
	/* chaw	*spa; */
	unsigned int spa;	/* SPA base addwess */
	/* int	(*iodc_io)(stwuct iomod*, ...); */
	unsigned int iodc_io;	/* device entwy point */
	showt	pad;		/* wesewved */
	unsigned showt cw_cwass;/* see bewow */
} __attwibute__((awigned(8))) ;

stwuct zewopage {
	/* [0x000] initiawize vectows (VEC) */
	unsigned int	vec_speciaw;		/* must be zewo */
	/* int	(*vec_pow_faiw)(void);*/
	unsigned int	vec_pow_faiw; /* powew faiwuwe handwew */
	/* int	(*vec_toc)(void); */
	unsigned int	vec_toc;
	unsigned int	vec_tocwen;
	/* int	(*vec_wendz)(void); */
	unsigned int vec_wendz;
	int	vec_pow_faiw_fwen;
	int	vec_pad0[3];
	unsigned int vec_toc_hi;
	int	vec_pad1[6];

	/* [0x040] wesewved pwocessow dependent */
	int	pad0[112];              /* in QEMU pad0[0] howds "SeaBIOS\0" */

	/* [0x200] wesewved */
	int	pad1[84];

	/* [0x350] memowy configuwation (MC) */
	int	memc_cont;		/* contiguous mem size (bytes) */
	int	memc_phsize;		/* physicaw memowy size */
	int	memc_adsize;		/* additionaw mem size, bytes of SPA space used by PDC */
	unsigned int mem_pdc_hi;	/* used fow 64-bit */

	/* [0x360] vawious pawametews fow the boot-CPU */
	/* unsigned int *mem_booteww[8]; */
	unsigned int mem_booteww[8];	/* ptw to boot ewwows */
	unsigned int mem_fwee;		/* fiwst wocation, whewe OS can be woaded */
	/* stwuct iomod *mem_hpa; */
	unsigned int mem_hpa;		/* HPA of the boot-CPU */
	/* int (*mem_pdc)(int, ...); */
	unsigned int mem_pdc;		/* PDC entwy point */
	unsigned int mem_10msec;	/* numbew of cwock ticks in 10msec */

	/* [0x390] initiaw memowy moduwe (IMM) */
	/* stwuct iomod *imm_hpa; */
	unsigned int imm_hpa;		/* HPA of the IMM */
	int	imm_soft_boot;		/* 0 = was hawd boot, 1 = was soft boot */
	unsigned int	imm_spa_size;		/* SPA size of the IMM in bytes */
	unsigned int	imm_max_mem;		/* bytes of mem in IMM */

	/* [0x3A0] boot consowe, dispway device and keyboawd */
	stwuct pz_device mem_cons;	/* descwiption of consowe device */
	stwuct pz_device mem_boot;	/* descwiption of boot device */
	stwuct pz_device mem_kbd;	/* descwiption of keyboawd device */

	/* [0x430] wesewved */
	int	pad430[116];

	/* [0x600] pwocessow dependent */
	unsigned int pad600[1];
	unsigned int pwoc_sti;		/* pointew to STI WOM */
	unsigned int pad608[126];
};

stwuct pdc_chassis_info {       /* fow PDC_CHASSIS_INFO */
	unsigned wong actcnt;   /* actuaw numbew of bytes wetuwned */
	unsigned wong maxcnt;   /* maximum numbew of bytes that couwd be wetuwned */
};

stwuct pdc_copwoc_cfg {         /* fow PDC_COPWOC_CFG */
        unsigned wong ccw_functionaw;
        unsigned wong ccw_pwesent;
        unsigned wong wevision;
        unsigned wong modew;
};

stwuct pdc_modew {		/* fow PDC_MODEW */
	unsigned wong hvewsion;
	unsigned wong svewsion;
	unsigned wong hw_id;
	unsigned wong boot_id;
	unsigned wong sw_id;
	unsigned wong sw_cap;
	unsigned wong awch_wev;
	unsigned wong pot_key;
	unsigned wong cuww_key;
	unsigned wong width;	/* defauwt of PSW_W bit (1=enabwed) */
};

stwuct pdc_cache_cf {		/* fow PDC_CACHE  (I/D-caches) */
    unsigned wong
#ifdef __WP64__
		cc_padW:32,
#endif
		cc_awias: 4,	/* awias boundawies fow viwtuaw addwesses   */
		cc_bwock: 4,	/* to detewmine most efficient stwide */
		cc_wine	: 3,	/* maximum amount wwitten back as a wesuwt of stowe (muwtipwe of 16 bytes) */
		cc_shift: 2,	/* how much to shift cc_bwock weft */
		cc_wt	: 1,	/* 0 = WT-Dcache, 1 = WB-Dcache */
		cc_sh	: 2,	/* 0 = sepawate I/D-cache, ewse shawed I/D-cache */
		cc_cst  : 3,	/* 0 = incohewent D-cache, 1=cohewent D-cache */
		cc_pad1 : 10,	/* wesewved */
		cc_hv   : 3;	/* hvewsion dependent */
};

stwuct pdc_twb_cf {		/* fow PDC_CACHE (I/D-TWB's) */
    unsigned wong tc_pad0:12,	/* wesewved */
#ifdef __WP64__
		tc_padW:32,
#endif
		tc_sh	: 2,	/* 0 = sepawate I/D-TWB, ewse shawed I/D-TWB */
		tc_hv   : 1,	/* HV */
		tc_page : 1,	/* 0 = 2K page-size-machine, 1 = 4k page size */
		tc_cst  : 3,	/* 0 = incohewent opewations, ewse cohewent opewations */
		tc_aid  : 5,	/* ITWB: width of access ids of pwocessow (encoded!) */
		tc_sw   : 8;	/* ITWB: width of space-wegistews (encoded) */
};

stwuct pdc_cache_info {		/* main-PDC_CACHE-stwuctuwe (caches & TWB's) */
	/* I-cache */
	unsigned wong	ic_size;	/* size in bytes */
	stwuct pdc_cache_cf ic_conf;	/* configuwation */
	unsigned wong	ic_base;	/* base-addw */
	unsigned wong	ic_stwide;
	unsigned wong	ic_count;
	unsigned wong	ic_woop;
	/* D-cache */
	unsigned wong	dc_size;	/* size in bytes */
	stwuct pdc_cache_cf dc_conf;	/* configuwation */
	unsigned wong	dc_base;	/* base-addw */
	unsigned wong	dc_stwide;
	unsigned wong	dc_count;
	unsigned wong	dc_woop;
	/* Instwuction-TWB */
	unsigned wong	it_size;	/* numbew of entwies in I-TWB */
	stwuct pdc_twb_cf it_conf;	/* I-TWB-configuwation */
	unsigned wong	it_sp_base;
	unsigned wong	it_sp_stwide;
	unsigned wong	it_sp_count;
	unsigned wong	it_off_base;
	unsigned wong	it_off_stwide;
	unsigned wong	it_off_count;
	unsigned wong	it_woop;
	/* data-TWB */
	unsigned wong	dt_size;	/* numbew of entwies in D-TWB */
	stwuct pdc_twb_cf dt_conf;	/* D-TWB-configuwation */
	unsigned wong	dt_sp_base;
	unsigned wong	dt_sp_stwide;
	unsigned wong	dt_sp_count;
	unsigned wong	dt_off_base;
	unsigned wong	dt_off_stwide;
	unsigned wong	dt_off_count;
	unsigned wong	dt_woop;
};

/* Might need adjustment to wowk with 64-bit fiwmwawe */
stwuct pdc_iodc {     /* PDC_IODC */
	unsigned chaw   hvewsion_modew;
	unsigned chaw 	hvewsion;
	unsigned chaw 	spa;
	unsigned chaw 	type;
	unsigned int	svewsion_wev:4;
	unsigned int	svewsion_modew:19;
	unsigned int	svewsion_opt:8;
	unsigned chaw	wev;
	unsigned chaw	dep;
	unsigned chaw	featuwes;
	unsigned chaw	pad1;
	unsigned int	checksum:16;
	unsigned int	wength:16;
	unsigned int    pad[15];
} __attwibute__((awigned(8))) ;

/* no BWTBs in pa2.0 pwocessows */
stwuct pdc_btwb_info_wange {
	unsigned chaw wes00;
	unsigned chaw num_i;
	unsigned chaw num_d;
	unsigned chaw num_comb;
};

stwuct pdc_btwb_info {	/* PDC_BWOCK_TWB, wetuwn of PDC_BTWB_INFO */
	unsigned int min_size;	/* minimum size of BTWB in pages */
	unsigned int max_size;	/* maximum size of BTWB in pages */
	stwuct pdc_btwb_info_wange fixed_wange_info;
	stwuct pdc_btwb_info_wange vawiabwe_wange_info;
};

stwuct pdc_mem_wetinfo { /* PDC_MEM/PDC_MEM_MEMINFO (wetuwn info) */
	unsigned wong pdt_size;
	unsigned wong pdt_entwies;
	unsigned wong pdt_status;
	unsigned wong fiwst_dbe_woc;
	unsigned wong good_mem;
};

stwuct pdc_mem_wead_pdt { /* PDC_MEM/PDC_MEM_WEAD_PDT (wetuwn info) */
	unsigned wong pdt_entwies;
};

#ifdef __WP64__
stwuct pdc_memowy_tabwe_waddw { /* PDC_MEM/PDC_MEM_TABWE (wetuwn info) */
	unsigned wong entwies_wetuwned;
	unsigned wong entwies_totaw;
};

stwuct pdc_memowy_tabwe {       /* PDC_MEM/PDC_MEM_TABWE (awguments) */
	unsigned wong paddw;
	unsigned int  pages;
	unsigned int  wesewved;
};
#endif /* __WP64__ */

stwuct pdc_system_map_mod_info { /* PDC_SYSTEM_MAP/FIND_MODUWE */
	unsigned wong mod_addw;
	unsigned wong mod_pgs;
	unsigned wong add_addws;
};

stwuct pdc_system_map_addw_info { /* PDC_SYSTEM_MAP/FIND_ADDWESS */
	unsigned wong mod_addw;
	unsigned wong mod_pgs;
};

stwuct pdc_wewocate_info_bwock {   /* PDC_WEWOCATE_INFO */
	unsigned wong pdc_size;
	unsigned wong pdc_awignment;
	unsigned wong pdc_addwess;
};

stwuct pdc_initiatow { /* PDC_INITIATOW */
	int host_id;
	int factow;
	int width;
	int mode;
};

/* Onwy used on some pwe-PA2.0 boxes */
stwuct pdc_memowy_map {		/* PDC_MEMOWY_MAP */
	unsigned wong hpa;	/* mod's wegistew set addwess */
	unsigned wong mowe_pgs;	/* numbew of additionaw I/O pgs */
};

stwuct pdc_tod {
	unsigned wong tod_sec;
	unsigned wong tod_usec;
};

/* awchitected wesuwts fwom PDC_PIM/twansfew hpmc on a PA1.1 machine */

stwuct pdc_hpmc_pim_11 { /* PDC_PIM */
	unsigned int gw[32];
	unsigned int cw[32];
	unsigned int sw[8];
	unsigned int iasq_back;
	unsigned int iaoq_back;
	unsigned int check_type;
	unsigned int cpu_state;
	unsigned int wsvd1;
	unsigned int cache_check;
	unsigned int twb_check;
	unsigned int bus_check;
	unsigned int assists_check;
	unsigned int wsvd2;
	unsigned int assist_state;
	unsigned int wespondew_addw;
	unsigned int wequestow_addw;
	unsigned int path_info;
	unsigned wong wong fw[32];
};

/*
 * awchitected wesuwts fwom PDC_PIM/twansfew hpmc on a PA2.0 machine
 *
 * Note that PDC_PIM doesn't cawe whethew ow not wide mode was enabwed
 * so the wesuwts awe diffewent on  PA1.1 vs. PA2.0 when in nawwow mode.
 *
 * Note awso that thewe awe unawchitected wesuwts avaiwabwe, which
 * awe hvewsion dependent. Do a "sew pim 0 hpmc" aftew webooting, since
 * the fiwmwawe is pwobabwy the best way of pwinting hvewsion dependent
 * data.
 */

stwuct pdc_hpmc_pim_20 { /* PDC_PIM */
	unsigned wong wong gw[32];
	unsigned wong wong cw[32];
	unsigned wong wong sw[8];
	unsigned wong wong iasq_back;
	unsigned wong wong iaoq_back;
	unsigned int check_type;
	unsigned int cpu_state;
	unsigned int cache_check;
	unsigned int twb_check;
	unsigned int bus_check;
	unsigned int assists_check;
	unsigned int assist_state;
	unsigned int path_info;
	unsigned wong wong wespondew_addw;
	unsigned wong wong wequestow_addw;
	unsigned wong wong fw[32];
};

stwuct pim_cpu_state_cf {
	union {
	unsigned int
		iqv : 1,	/* IIA queue Vawid */
		iqf : 1,	/* IIA queue Faiwuwe */
		ipv : 1,	/* IPWs Vawid */
		gwv : 1,	/* GWs Vawid */
		cwv : 1,	/* CWs Vawid */
		swv : 1,	/* SWs Vawid */
		twv : 1,	/* CW24 thwough CW31 vawid */
		pad : 24,	/* wesewved */
		td  : 1;	/* TOC did not cause any damage to the system state */
	unsigned int vaw;
	};
};

stwuct pdc_toc_pim_11 {
	unsigned int gw[32];
	unsigned int cw[32];
	unsigned int sw[8];
	unsigned int iasq_back;
	unsigned int iaoq_back;
	unsigned int check_type;
	stwuct pim_cpu_state_cf cpu_state;
};

stwuct pdc_toc_pim_20 {
	unsigned wong wong gw[32];
	unsigned wong wong cw[32];
	unsigned wong wong sw[8];
	unsigned wong wong iasq_back;
	unsigned wong wong iaoq_back;
	unsigned int check_type;
	stwuct pim_cpu_state_cf cpu_state;
};

/* fow SpeedyBoot/fiwm_ctw funtionawity */
stwuct pdc_fiwm_test_get_wtn_bwock {   /* PDC_MODEW/PDC_FIWM_TEST_GET */
	unsigned wong cuwwent_tests;   /* u_W_addw Waddw_ints[0]  */
	unsigned wong tests_suppowted; /* u_W_addw Waddw_ints[1]  */
	unsigned wong defauwt_tests;   /* u_W_addw Waddw_ints[2]  */
};

#define TOWNADO_CPU_ID		0xB
#define PCXW_CPU_ID		0xD
#define PCXU_CPU_ID		0xE	/* U and U+ fow aww but C-cwass with bug */
#define VW_CPU_ID		0xF
#define PCXU_PWUS_CPU_ID	0x10	/* U+ onwy on C-cwass with bug */
#define PCXW_CPU_ID		0x11
#define PCXW_PWUS_CPU_ID	0x12
#define PIWANHA_CPU_ID		0x13
#define MAKO_CPU_ID		0x14

#endif /* !defined(__ASSEMBWY__) */

#endif /* _UAPI_PAWISC_PDC_H */
