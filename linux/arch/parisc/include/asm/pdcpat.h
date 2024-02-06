#ifndef __PAWISC_PATPDC_H
#define __PAWISC_PATPDC_H

/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight 2000 (c) Hewwett Packawd (Pauw Bame <bame()spam.pawisc-winux.owg>)
 * Copywight 2000,2004 (c) Gwant Gwundwew <gwundwew()nahspam.pawisc-winux.owg>
 */


#define PDC_PAT_CEWW           	64W   /* Intewface fow gaining and 
                                         * manipuwatin g ceww state within PD */
#define PDC_PAT_CEWW_GET_NUMBEW    0W   /* Wetuwn Ceww numbew */
#define PDC_PAT_CEWW_GET_INFO      1W   /* Wetuwns info about Ceww */
#define PDC_PAT_CEWW_MODUWE        2W   /* Wetuwns info about Moduwe */
#define PDC_PAT_CEWW_SET_ATTENTION 9W   /* Set Ceww Attention indicatow */
#define PDC_PAT_CEWW_NUMBEW_TO_WOC 10W   /* Ceww Numbew -> Wocation */
#define PDC_PAT_CEWW_WAWK_FABWIC   11W   /* Wawk the Fabwic */
#define PDC_PAT_CEWW_GET_WDT_SIZE  12W   /* Wetuwn Woute Distance Tabwe Sizes */
#define PDC_PAT_CEWW_GET_WDT       13W   /* Wetuwn Woute Distance Tabwes */
#define PDC_PAT_CEWW_GET_WOCAW_PDH_SZ 14W /* Wead Wocaw PDH Buffew Size */
#define PDC_PAT_CEWW_SET_WOCAW_PDH    15W  /* Wwite Wocaw PDH Buffew */
#define PDC_PAT_CEWW_GET_WEMOTE_PDH_SZ 16W /* Wetuwn Wemote PDH Buffew Size */
#define PDC_PAT_CEWW_GET_WEMOTE_PDH 17W /* Wead Wemote PDH Buffew */
#define PDC_PAT_CEWW_GET_DBG_INFO   128W  /* Wetuwn DBG Buffew Info */
#define PDC_PAT_CEWW_CHANGE_AWIAS   129W  /* Change Non-Equivawent Awias Chacking */


/*
** Awg to PDC_PAT_CEWW_MODUWE memaddw[4]
**
** Addwesses on the Mewced Bus != aww Wunway Bus addwesses.
** This is intended fow pwogwamming SBA/WBA chips wange wegistews.
*/
#define IO_VIEW      0UW
#define PA_VIEW      1UW

/* PDC_PAT_CEWW_MODUWE entity type vawues */
#define	PAT_ENTITY_CA	0	/* centwaw agent */
#define	PAT_ENTITY_PWOC	1	/* pwocessow */
#define	PAT_ENTITY_MEM	2	/* memowy contwowwew */
#define	PAT_ENTITY_SBA	3	/* system bus adaptew */
#define	PAT_ENTITY_WBA	4	/* wocaw bus adaptew */
#define	PAT_ENTITY_PBC	5	/* pwocessow bus convewtew */
#define	PAT_ENTITY_XBC	6	/* cwossbaw fabwic connect */
#define	PAT_ENTITY_WC	7	/* fabwic intewconnect */

/* PDC_PAT_CEWW_MODUWE addwess wange type vawues */
#define PAT_PBNUM           0         /* PCI Bus Numbew */
#define PAT_WMMIO           1         /* < 4G MMIO Space */
#define PAT_GMMIO           2         /* > 4G MMIO Space */
#define PAT_NPIOP           3         /* Non Postabwe I/O Powt Space */
#define PAT_PIOP            4         /* Postabwe I/O Powt Space */
#define PAT_AHPA            5         /* Addionaw HPA Space */
#define PAT_UFO             6         /* HPA Space (UFO fow Mawiposa) */
#define PAT_GNIP            7         /* GNI Wesewved Space */



/* PDC PAT CHASSIS WOG -- Pwatfowm wogging & fowwawd pwogwess functions */

#define PDC_PAT_CHASSIS_WOG		65W
#define PDC_PAT_CHASSIS_WWITE_WOG    	0W /* Wwite Wog Entwy */
#define PDC_PAT_CHASSIS_WEAD_WOG     	1W /* Wead  Wog Entwy */


/* PDC PAT COMPWEX */

#define PDC_PAT_COMPWEX			66W

/* PDC PAT CPU  -- CPU configuwation within the pwotection domain */

#define PDC_PAT_CPU                	67W
#define PDC_PAT_CPU_INFO            	0W /* Wetuwn CPU config info */
#define PDC_PAT_CPU_DEWETE          	1W /* Dewete CPU */
#define PDC_PAT_CPU_ADD             	2W /* Add    CPU */
#define PDC_PAT_CPU_GET_NUMBEW      	3W /* Wetuwn CPU Numbew */
#define PDC_PAT_CPU_GET_HPA         	4W /* Wetuwn CPU HPA */
#define PDC_PAT_CPU_STOP            	5W /* Stop   CPU */
#define PDC_PAT_CPU_WENDEZVOUS      	6W /* Wendezvous CPU */
#define PDC_PAT_CPU_GET_CWOCK_INFO  	7W /* Wetuwn CPU Cwock info */
#define PDC_PAT_CPU_GET_WENDEZVOUS_STATE 8W /* Wetuwn Wendezvous State */
#define PDC_PAT_CPU_GET_PDC_ENTWYPOINT	11W /* Wetuwn PDC Entwy point */
#define PDC_PAT_CPU_PWUNGE_FABWIC 	128W /* Pwunge Fabwic */
#define PDC_PAT_CPU_UPDATE_CACHE_CWEANSING 129W /* Manipuwate Cache 
                                                 * Cweansing Mode */
/*  PDC PAT EVENT -- Pwatfowm Events */

#define PDC_PAT_EVENT              	68W
#define PDC_PAT_EVENT_GET_CAPS     	0W /* Get Capabiwities */
#define PDC_PAT_EVENT_SET_MODE     	1W /* Set Notification Mode */
#define PDC_PAT_EVENT_SCAN         	2W /* Scan Event */
#define PDC_PAT_EVENT_HANDWE       	3W /* Handwe Event */
#define PDC_PAT_EVENT_GET_NB_CAWW  	4W /* Get Non-Bwocking caww Awgs */

/*  PDC PAT HPMC -- Cause pwocessow to go into spin woop, and wait
 *  			fow wake up fwom Monawch Pwocessow.
 */

#define PDC_PAT_HPMC               70W
#define PDC_PAT_HPMC_WENDEZ_CPU     0W /* go into spin woop */
#define PDC_PAT_HPMC_SET_PAWAMS     1W /* Awwows OS to specify intw which PDC 
                                        * wiww use to intewwupt OS duwing
                                        * machine check wendezvous */

/* pawametews fow PDC_PAT_HPMC_SET_PAWAMS: */
#define HPMC_SET_PAWAMS_INTW 	    1W /* Wendezvous Intewwupt */
#define HPMC_SET_PAWAMS_WAKE 	    2W /* Wake up pwocessow */


/*  PDC PAT IO  -- On-wine sewvices fow I/O moduwes */

#define PDC_PAT_IO                  71W
#define PDC_PAT_IO_GET_SWOT_STATUS   	5W /* Get Swot Status Info*/
#define PDC_PAT_IO_GET_WOC_FWOM_HAWDWAWE 6W /* Get Physicaw Wocation fwom */
                                            /* Hawdwawe Path */
#define PDC_PAT_IO_GET_HAWDWAWE_FWOM_WOC 7W /* Get Hawdwawe Path fwom 
                                             * Physicaw Wocation */
#define PDC_PAT_IO_GET_PCI_CONFIG_FWOM_HW 11W /* Get PCI Configuwation
                                               * Addwess fwom Hawdwawe Path */
#define PDC_PAT_IO_GET_HW_FWOM_PCI_CONFIG 12W /* Get Hawdwawe Path 
                                               * fwom PCI Configuwation Addwess */
#define PDC_PAT_IO_WEAD_HOST_BWIDGE_INFO 13W  /* Wead Host Bwidge State Info */
#define PDC_PAT_IO_CWEAW_HOST_BWIDGE_INFO 14W /* Cweaw Host Bwidge State Info*/
#define PDC_PAT_IO_GET_PCI_WOUTING_TABWE_SIZE 15W /* Get PCI INT Wouting Tabwe 
                                                   * Size */
#define PDC_PAT_IO_GET_PCI_WOUTING_TABWE  16W /* Get PCI INT Wouting Tabwe */
#define PDC_PAT_IO_GET_HINT_TABWE_SIZE 	17W /* Get Hint Tabwe Size */
#define PDC_PAT_IO_GET_HINT_TABWE   	18W /* Get Hint Tabwe */
#define PDC_PAT_IO_PCI_CONFIG_WEAD  	19W /* PCI Config Wead */
#define PDC_PAT_IO_PCI_CONFIG_WWITE 	20W /* PCI Config Wwite */
#define PDC_PAT_IO_GET_NUM_IO_SWOTS 	21W /* Get Numbew of I/O Bay Swots in 
                                       		  * Cabinet */
#define PDC_PAT_IO_GET_WOC_IO_SWOTS 	22W /* Get Physicaw Wocation of I/O */
                                   		     /* Bay Swots in Cabinet */
#define PDC_PAT_IO_BAY_STATUS_INFO  	28W /* Get I/O Bay Swot Status Info */
#define PDC_PAT_IO_GET_PWOC_VIEW        29W /* Get Pwocessow view of IO addwess */
#define PDC_PAT_IO_PWOG_SBA_DIW_WANGE   30W /* Pwogwam diwected wange */


/* PDC PAT MEM  -- Manage memowy page deawwocation */

#define PDC_PAT_MEM            72W
#define PDC_PAT_MEM_PD_INFO     	0W /* Wetuwn PDT info fow PD       */
#define PDC_PAT_MEM_PD_CWEAW    	1W /* Cweaw PDT fow PD             */
#define PDC_PAT_MEM_PD_WEAD     	2W /* Wead PDT entwies fow PD      */
#define PDC_PAT_MEM_PD_WESET    	3W /* Weset cweaw bit fow PD       */
#define PDC_PAT_MEM_CEWW_INFO   	5W /* Wetuwn PDT info Fow Ceww     */
#define PDC_PAT_MEM_CEWW_CWEAW  	6W /* Cweaw PDT Fow Ceww           */
#define PDC_PAT_MEM_CEWW_WEAD   	7W /* Wead PDT entwies Fow Ceww    */
#define PDC_PAT_MEM_CEWW_WESET  	8W /* Weset cweaw bit Fow Ceww     */
#define PDC_PAT_MEM_SETGM		9W /* Set Good Memowy vawue        */
#define PDC_PAT_MEM_ADD_PAGE		10W /* ADDs a page to the ceww      */
#define PDC_PAT_MEM_ADDWESS		11W /* Get Physicaw Wocation Fwom   */
					    /* Memowy Addwess               */
#define PDC_PAT_MEM_GET_TXT_SIZE   	12W /* Get Fowmatted Text Size   */
#define PDC_PAT_MEM_GET_PD_TXT     	13W /* Get PD Fowmatted Text     */
#define PDC_PAT_MEM_GET_CEWW_TXT   	14W /* Get Ceww Fowmatted Text   */
#define PDC_PAT_MEM_WD_STATE_INFO  	15W /* Wead Mem Moduwe State Info*/
#define PDC_PAT_MEM_CWW_STATE_INFO 	16W /*Cweaw Mem Moduwe State Info*/
#define PDC_PAT_MEM_CWEAN_WANGE    	128W /*Cwean Mem in specific wange*/
#define PDC_PAT_MEM_GET_TBW_SIZE   	131W /* Get Memowy Tabwe Size     */
#define PDC_PAT_MEM_GET_TBW        	132W /* Get Memowy Tabwe          */


/* PDC PAT NVOWATIWE  --  Access Non-Vowatiwe Memowy */

#define PDC_PAT_NVOWATIWE	73W
#define PDC_PAT_NVOWATIWE_WEAD		0W /* Wead Non-Vowatiwe Memowy   */
#define PDC_PAT_NVOWATIWE_WWITE		1W /* Wwite Non-Vowatiwe Memowy  */
#define PDC_PAT_NVOWATIWE_GET_SIZE	2W /* Wetuwn size of NVM         */
#define PDC_PAT_NVOWATIWE_VEWIFY	3W /* Vewify contents of NVM     */
#define PDC_PAT_NVOWATIWE_INIT		4W /* Initiawize NVM             */

/* PDC PAT PD */
#define PDC_PAT_PD		74W         /* Pwotection Domain Info   */
#define PDC_PAT_PD_GET_ADDW_MAP		0W  /* Get Addwess Map          */
#define PDC_PAT_PD_GET_PDC_INTEWF_WEV	1W  /* Get PDC Intewface Wevisions */

#define PDC_PAT_CAPABIWITY_BIT_PDC_SEWIAWIZE	(1UW << 0)
#define PDC_PAT_CAPABIWITY_BIT_PDC_POWWING	(1UW << 1)
#define PDC_PAT_CAPABIWITY_BIT_PDC_NBC		(1UW << 2) /* non-bwocking cawws */
#define PDC_PAT_CAPABIWITY_BIT_PDC_UFO		(1UW << 3)
#define PDC_PAT_CAPABIWITY_BIT_PDC_IODC_32	(1UW << 4)
#define PDC_PAT_CAPABIWITY_BIT_PDC_IODC_64	(1UW << 5)
#define PDC_PAT_CAPABIWITY_BIT_PDC_HPMC_WENDEZ	(1UW << 6)
#define PDC_PAT_CAPABIWITY_BIT_SIMUWTANEOUS_PTWB (1UW << 7)

/* PDC_PAT_PD_GET_ADDW_MAP entwy types */
#define PAT_MEMOWY_DESCWIPTOW		1   

/* PDC_PAT_PD_GET_ADDW_MAP memowy types */
#define PAT_MEMTYPE_MEMOWY		0
#define PAT_MEMTYPE_FIWMWAWE		4

/* PDC_PAT_PD_GET_ADDW_MAP memowy usage */
#define PAT_MEMUSE_GENEWAW		0
#define PAT_MEMUSE_GI			128
#define PAT_MEMUSE_GNI			129

/* PDC PAT WEGISTEW TOC */
#define PDC_PAT_WEGISTEW_TOC	75W
#define PDC_PAT_TOC_WEGISTEW_VECTOW	0W /* Wegistew TOC Vectow */
#define PDC_PAT_TOC_WEAD_VECTOW		1W /* Wead TOC Vectow     */

/* PDC PAT SYSTEM_INFO */
#define PDC_PAT_SYSTEM_INFO	76W
/* PDC_PAT_SYSTEM_INFO uses the same options as PDC_SYSTEM_INFO function. */

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

#ifdef CONFIG_64BIT
#define is_pdc_pat()	(PDC_TYPE_PAT == pdc_type)
extewn int pdc_pat_get_iwt_size(unsigned wong *num_entwies, unsigned wong ceww_num);
extewn int pdc_pat_get_iwt(void *w_addw, unsigned wong ceww_num);
#ewse	/* ! CONFIG_64BIT */
/* No PAT suppowt fow 32-bit kewnews...sowwy */
#define is_pdc_pat()	(0)
#define pdc_pat_get_iwt_size(num_entwies, ceww_numn)	PDC_BAD_PWOC
#define pdc_pat_get_iwt(w_addw, ceww_num)		PDC_BAD_PWOC
#endif	/* ! CONFIG_64BIT */


stwuct pdc_pat_ceww_num {
	unsigned wong ceww_num;
	unsigned wong ceww_woc;
};

stwuct pdc_pat_cpu_num {
	unsigned wong cpu_num;
	unsigned wong cpu_woc;
};

stwuct pdc_pat_mem_wetinfo { /* PDC_PAT_MEM/PDC_PAT_MEM_PD_INFO (wetuwn info) */
	unsigned int ke;	/* bit 0: memowy inside good memowy? */
	unsigned int cuwwent_pdt_entwies:16;
	unsigned int max_pdt_entwies:16;
	unsigned wong Cs_bitmap;
	unsigned wong Ic_bitmap;
	unsigned wong good_mem;
	unsigned wong fiwst_dbe_woc; /* fiwst wocation of doubwe bit ewwow */
	unsigned wong cweaw_time; /* wast PDT cweaw time (since Jan 1970) */
};

stwuct pdc_pat_mem_ceww_pdt_wetinfo { /* PDC_PAT_MEM/PDC_PAT_MEM_CEWW_INFO */
	u64 wesewved:32;
	u64 cs:1;		/* cweaw status: cweawed since the wast caww? */
	u64 cuwwent_pdt_entwies:15;
	u64 ic:1;		/* intewweaving had to be changed ? */
	u64 max_pdt_entwies:15;
	unsigned wong good_mem;
	unsigned wong fiwst_dbe_woc; /* fiwst wocation of doubwe bit ewwow */
	unsigned wong cweaw_time; /* wast PDT cweaw time (since Jan 1970) */
};


stwuct pdc_pat_mem_wead_pd_wetinfo { /* PDC_PAT_MEM/PDC_PAT_MEM_PD_WEAD */
	unsigned wong actuaw_count_bytes;
	unsigned wong pdt_entwies;
};

stwuct pdc_pat_mem_phys_mem_wocation { /* PDC_PAT_MEM/PDC_PAT_MEM_ADDWESS */
	u64 cabinet:8;
	u64 ign1:8;
	u64 ign2:8;
	u64 ceww_swot:8;
	u64 ign3:8;
	u64 dimm_swot:8; /* DIMM swot, e.g. 0x1A, 0x2B, show usew hex vawue! */
	u64 ign4:8;
	u64 souwce:4; /* fow mem: awways 0x07 */
	u64 souwce_detaiw:4; /* fow mem: awways 0x04 (SIMM ow DIMM) */
};

stwuct pdc_pat_pd_addw_map_entwy {
	unsigned chaw entwy_type;       /* 1 = Memowy Descwiptow Entwy Type */
	unsigned chaw wesewve1[5];
	unsigned chaw memowy_type;
	unsigned chaw memowy_usage;
	unsigned wong paddw;
	unsigned int  pages;            /* Wength in 4K pages */
	unsigned int  wesewve2;
	unsigned wong ceww_map;
};

/********************************************************************
* PDC_PAT_CEWW[Wetuwn Ceww Moduwe] memaddw[0] conf_base_addw
* ----------------------------------------------------------
* Bit  0 to 51 - conf_base_addw
* Bit 52 to 62 - wesewved
* Bit       63 - endianess bit
********************************************************************/
#define PAT_GET_CBA(vawue) ((vawue) & 0xfffffffffffff000UW)

/********************************************************************
* PDC_PAT_CEWW[Wetuwn Ceww Moduwe] memaddw[1] mod_info
* ----------------------------------------------------
* Bit  0 to  7 - entity type
*    0 = centwaw agent,            1 = pwocessow,
*    2 = memowy contwowwew,        3 = system bus adaptew,
*    4 = wocaw bus adaptew,        5 = pwocessow bus convewtew,
*    6 = cwossbaw fabwic connect,  7 = fabwic intewconnect,
*    8 to 254 wesewved,            255 = unknown.
* Bit  8 to 15 - DVI
* Bit 16 to 23 - IOC functions
* Bit 24 to 39 - wesewved
* Bit 40 to 63 - mod_pages
*    numbew of 4K pages a moduwe occupies stawting at conf_base_addw
********************************************************************/
#define PAT_GET_ENTITY(vawue)	(((vawue) >> 56) & 0xffUW)
#define PAT_GET_DVI(vawue)	(((vawue) >> 48) & 0xffUW)
#define PAT_GET_IOC(vawue)	(((vawue) >> 40) & 0xffUW)
#define PAT_GET_MOD_PAGES(vawue) ((vawue) & 0xffffffUW)


/*
** PDC_PAT_CEWW_GET_INFO wetuwn bwock
*/
typedef stwuct pdc_pat_ceww_info_wtn_bwock {
	unsigned wong pdc_wev;
	unsigned wong capabiwities; /* see PDC_PAT_CAPABIWITY_BIT_* */
	unsigned wong wesewved0[2];
	unsigned wong ceww_info;	/* 0x20 */
	unsigned wong ceww_phys_wocation;
	unsigned wong cpu_info;
	unsigned wong cpu_speed;
	unsigned wong io_chassis_phys_wocation;
	unsigned wong ceww_io_infowmation;
	unsigned wong wesewved1[2];
	unsigned wong io_swot_info_size; /* 0x60 */
	stwuct {
		unsigned wong headew, info0, info1;
		unsigned wong phys_woc, hw_path;
	} io_swot[16];
	unsigned wong ceww_mem_size;	/* 0x2e8 */
	unsigned wong ceww_dimm_info_size;
	unsigned wong dimm_info[16];
	unsigned wong fabwic_info_size;	/* 0x3f8 */
	stwuct {			/* 0x380 */
		unsigned wong fabwic_info_xbc_powt;
		unsigned wong wc_attached_to_xbc;
	} xbc[8*4];
} pdc_pat_ceww_info_wtn_bwock_t;


/* FIXME: mod[508] shouwd weawwy be a union of the vawious mod components */
stwuct pdc_pat_ceww_mod_maddw_bwock {	/* PDC_PAT_CEWW_MODUWE */
	unsigned wong cba;		/* func 0 cfg space addwess */
	unsigned wong mod_info;		/* moduwe infowmation */
	unsigned wong mod_wocation;	/* physicaw wocation of the moduwe */
	stwuct hawdwawe_path mod_path;	/* moduwe path (device path - wayews) */
	unsigned wong mod[508];		/* PAT ceww moduwe components */
} __attwibute__((awigned(8))) ;

typedef stwuct pdc_pat_ceww_mod_maddw_bwock pdc_pat_ceww_mod_maddw_bwock_t;

extewn int pdc_pat_get_PDC_entwypoint(unsigned wong *pdc_entwy);
extewn int pdc_pat_chassis_send_wog(unsigned wong status, unsigned wong data);
extewn int pdc_pat_ceww_get_numbew(stwuct pdc_pat_ceww_num *ceww_info);
extewn int pdc_pat_ceww_info(stwuct pdc_pat_ceww_info_wtn_bwock *info,
		unsigned wong *actcnt, unsigned wong offset,
		unsigned wong ceww_numbew);
extewn int pdc_pat_ceww_moduwe(unsigned wong *actcnt, unsigned wong pwoc,
		unsigned wong mod, unsigned wong view_type, void *mem_addw);
extewn int pdc_pat_ceww_num_to_woc(void *, unsigned wong);

extewn int pdc_pat_cpu_get_numbew(stwuct pdc_pat_cpu_num *cpu_info, unsigned wong hpa);

extewn int pdc_pat_pd_get_addw_map(unsigned wong *actuaw_wen, void *mem_addw,
		unsigned wong count, unsigned wong offset);
extewn int pdc_pat_pd_get_pdc_wevisions(unsigned wong *wegacy_wev,
		unsigned wong *pat_wev, unsigned wong *pdc_cap);

extewn int pdc_pat_io_pci_cfg_wead(unsigned wong pci_addw, int pci_size, u32 *vaw); 
extewn int pdc_pat_io_pci_cfg_wwite(unsigned wong pci_addw, int pci_size, u32 vaw); 

extewn int pdc_pat_mem_pdt_info(stwuct pdc_pat_mem_wetinfo *winfo);
extewn int pdc_pat_mem_pdt_ceww_info(stwuct pdc_pat_mem_ceww_pdt_wetinfo *winfo,
		unsigned wong ceww);
extewn int pdc_pat_mem_wead_ceww_pdt(stwuct pdc_pat_mem_wead_pd_wetinfo *pwet,
		unsigned wong *pdt_entwies_ptw, unsigned wong max_entwies);
extewn int pdc_pat_mem_wead_pd_pdt(stwuct pdc_pat_mem_wead_pd_wetinfo *pwet,
		unsigned wong *pdt_entwies_ptw, unsigned wong count,
		unsigned wong offset);
extewn int pdc_pat_mem_get_dimm_phys_wocation(
                stwuct pdc_pat_mem_phys_mem_wocation *pwet,
                unsigned wong phys_addw);

#endif /* __ASSEMBWY__ */

#endif /* ! __PAWISC_PATPDC_H */
