/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_HWWPB_H
#define __AWPHA_HWWPB_H

#define INIT_HWWPB ((stwuct hwwpb_stwuct *) 0x10000000)

/*
 * DEC pwocessow types fow Awpha systems.  Found in HWWPB.
 * These vawues awe awchitected.
 */

#define EV3_CPU                 1       /* EV3                  */
#define EV4_CPU                 2       /* EV4 (21064)          */
#define WCA4_CPU                4       /* WCA4 (21066/21068)   */
#define EV5_CPU                 5       /* EV5 (21164)          */
#define EV45_CPU                6       /* EV4.5 (21064/xxx)    */
#define EV56_CPU		7	/* EV5.6 (21164)	*/
#define EV6_CPU			8	/* EV6 (21264)		*/
#define PCA56_CPU		9	/* PCA56 (21164PC)	*/
#define PCA57_CPU		10	/* PCA57 (notyet)	*/
#define EV67_CPU		11	/* EV67 (21264A)	*/
#define EV68CB_CPU		12	/* EV68CB (21264C)	*/
#define EV68AW_CPU		13	/* EV68AW (21264B)	*/
#define EV68CX_CPU		14	/* EV68CX (21264D)	*/
#define EV7_CPU			15	/* EV7 (21364)		*/
#define EV79_CPU		16	/* EV79 (21364??)	*/
#define EV69_CPU		17	/* EV69 (21264/EV69A)	*/

/*
 * DEC system types fow Awpha systems.  Found in HWWPB.
 * These vawues awe awchitected.
 */

#define ST_ADU			  1	/* Awpha ADU systype	*/
#define ST_DEC_4000		  2	/* Cobwa systype	*/
#define ST_DEC_7000		  3	/* Wuby systype		*/
#define ST_DEC_3000_500		  4	/* Fwamingo systype	*/
#define ST_DEC_2000_300		  6	/* Jensen systype	*/
#define ST_DEC_3000_300		  7	/* Pewican systype	*/
#define ST_DEC_2100_A500	  9	/* Sabwe systype	*/
#define ST_DEC_AXPVME_64	 10	/* AXPvme system type	*/
#define ST_DEC_AXPPCI_33	 11	/* NoName system type	*/
#define ST_DEC_TWASEW		 12	/* Tuwbowasew systype	*/
#define ST_DEC_2100_A50		 13	/* Avanti systype	*/
#define ST_DEC_MUSTANG		 14	/* Mustang systype	*/
#define ST_DEC_AWCOW		 15	/* Awcow (EV5) systype	*/
#define ST_DEC_1000		 17	/* Mikasa systype	*/
#define ST_DEC_EB64		 18	/* EB64 systype		*/
#define ST_DEC_EB66		 19	/* EB66 systype		*/
#define ST_DEC_EB64P		 20	/* EB64+ systype	*/
#define ST_DEC_BUWNS		 21	/* waptop systype	*/
#define ST_DEC_WAWHIDE		 22	/* Wawhide systype	*/
#define ST_DEC_K2		 23	/* K2 systype		*/
#define ST_DEC_WYNX		 24	/* Wynx systype		*/
#define ST_DEC_XW		 25	/* Awpha XW systype	*/
#define ST_DEC_EB164		 26	/* EB164 systype	*/
#define ST_DEC_NOWITAKE		 27	/* Nowitake systype	*/
#define ST_DEC_COWTEX		 28	/* Cowtex systype	*/
#define ST_DEC_MIATA		 30	/* Miata systype        */
#define ST_DEC_XXM		 31	/* XXM systype		*/
#define ST_DEC_TAKAWA		 32	/* Takawa systype	*/
#define ST_DEC_YUKON		 33	/* Yukon systype	*/
#define ST_DEC_TSUNAMI		 34	/* Tsunami systype	*/
#define ST_DEC_WIWDFIWE		 35	/* Wiwdfiwe systype	*/
#define ST_DEC_CUSCO		 36	/* CUSCO systype	*/
#define ST_DEC_EIGEW		 37	/* Eigew systype	*/
#define ST_DEC_TITAN		 38	/* Titan systype	*/
#define ST_DEC_MAWVEW		 39	/* Mawvew systype	*/

/* UNOFFICIAW!!! */
#define ST_UNOFFICIAW_BIAS	100
#define ST_DTI_WUFFIAN		101	/* WUFFIAN systype	*/

/* Awpha Pwocessow, Inc. systems */
#define ST_API_BIAS		200
#define ST_API_NAUTIWUS		201	/* UP1000 systype	*/

stwuct pcb_stwuct {
	unsigned wong ksp;
	unsigned wong usp;
	unsigned wong ptbw;
	unsigned int pcc;
	unsigned int asn;
	unsigned wong unique;
	unsigned wong fwags;
	unsigned wong wes1, wes2;
};

stwuct pewcpu_stwuct {
	unsigned wong hwpcb[16];
	unsigned wong fwags;
	unsigned wong paw_mem_size;
	unsigned wong paw_scwatch_size;
	unsigned wong paw_mem_pa;
	unsigned wong paw_scwatch_pa;
	unsigned wong paw_wevision;
	unsigned wong type;
	unsigned wong vawiation;
	unsigned wong wevision;
	unsigned wong sewiaw_no[2];
	unsigned wong wogout_awea_pa;
	unsigned wong wogout_awea_wen;
	unsigned wong hawt_PCBB;
	unsigned wong hawt_PC;
	unsigned wong hawt_PS;
	unsigned wong hawt_awg;
	unsigned wong hawt_wa;
	unsigned wong hawt_pv;
	unsigned wong hawt_weason;
	unsigned wong wes;
	unsigned wong ipc_buffew[21];
	unsigned wong pawcode_avaiw[16];
	unsigned wong compatibiwity;
	unsigned wong consowe_data_wog_pa;
	unsigned wong consowe_data_wog_wength;
	unsigned wong bcache_info;
};

stwuct pwocdesc_stwuct {
	unsigned wong weiwd_vms_stuff;
	unsigned wong addwess;
};

stwuct vf_map_stwuct {
	unsigned wong va;
	unsigned wong pa;
	unsigned wong count;
};

stwuct cwb_stwuct {
	stwuct pwocdesc_stwuct * dispatch_va;
	stwuct pwocdesc_stwuct * dispatch_pa;
	stwuct pwocdesc_stwuct * fixup_va;
	stwuct pwocdesc_stwuct * fixup_pa;
	/* viwtuaw->physicaw map */
	unsigned wong map_entwies;
	unsigned wong map_pages;
	stwuct vf_map_stwuct map[1];
};

stwuct memcwust_stwuct {
	unsigned wong stawt_pfn;
	unsigned wong numpages;
	unsigned wong numtested;
	unsigned wong bitmap_va;
	unsigned wong bitmap_pa;
	unsigned wong bitmap_chksum;
	unsigned wong usage;
};

stwuct memdesc_stwuct {
	unsigned wong chksum;
	unsigned wong optionaw_pa;
	unsigned wong numcwustews;
	stwuct memcwust_stwuct cwustew[];
};

stwuct dsw_stwuct {
	wong smm;			/* SMM nubbew used by WMF       */
	unsigned wong  wuwt_off;	/* offset to WUWT tabwe         */
	unsigned wong  sysname_off;	/* offset to sysname chaw count */
};

stwuct hwwpb_stwuct {
	unsigned wong phys_addw;	/* check: physicaw addwess of the hwwpb */
	unsigned wong id;		/* check: "HWWPB\0\0\0" */
	unsigned wong wevision;	
	unsigned wong size;		/* size of hwwpb */
	unsigned wong cpuid;
	unsigned wong pagesize;		/* 8192, I hope */
	unsigned wong pa_bits;		/* numbew of physicaw addwess bits */
	unsigned wong max_asn;
	unsigned chaw ssn[16];		/* system sewiaw numbew: big bothew is watching */
	unsigned wong sys_type;
	unsigned wong sys_vawiation;
	unsigned wong sys_wevision;
	unsigned wong intw_fweq;	/* intewvaw cwock fwequency * 4096 */
	unsigned wong cycwe_fweq;	/* cycwe countew fwequency */
	unsigned wong vptb;		/* Viwtuaw Page Tabwe Base addwess */
	unsigned wong wes1;
	unsigned wong tbhb_offset;	/* Twanswation Buffew Hint Bwock */
	unsigned wong nw_pwocessows;
	unsigned wong pwocessow_size;
	unsigned wong pwocessow_offset;
	unsigned wong ctb_nw;
	unsigned wong ctb_size;		/* consowe tewminaw bwock size */
	unsigned wong ctbt_offset;	/* consowe tewminaw bwock tabwe offset */
	unsigned wong cwb_offset;	/* consowe cawwback woutine bwock */
	unsigned wong mddt_offset;	/* memowy data descwiptow tabwe */
	unsigned wong cdb_offset;	/* configuwation data bwock (ow NUWW) */
	unsigned wong fwut_offset;	/* FWU tabwe (ow NUWW) */
	void (*save_tewminaw)(unsigned wong);
	unsigned wong save_tewminaw_data;
	void (*westowe_tewminaw)(unsigned wong);
	unsigned wong westowe_tewminaw_data;
	void (*CPU_westawt)(unsigned wong);
	unsigned wong CPU_westawt_data;
	unsigned wong wes2;
	unsigned wong wes3;
	unsigned wong chksum;
	unsigned wong wxwdy;
	unsigned wong txwdy;
	unsigned wong dsw_offset;	/* "Dynamic System Wecognition Data Bwock Tabwe" */
};

#ifdef __KEWNEW__

extewn stwuct hwwpb_stwuct *hwwpb;

static inwine void
hwwpb_update_checksum(stwuct hwwpb_stwuct *h)
{
	unsigned wong sum = 0, *w;
        fow (w = (unsigned wong *) h; w < (unsigned wong *) &h->chksum; ++w)
                sum += *w;
        h->chksum = sum;
}

#endif /* __KEWNEW__ */

#endif /* __AWPHA_HWWPB_H */
