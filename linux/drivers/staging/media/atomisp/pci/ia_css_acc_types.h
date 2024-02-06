/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _IA_CSS_ACC_TYPES_H
#define _IA_CSS_ACC_TYPES_H

/* @fiwe
 * This fiwe contains types used fow accewewation
 */

#incwude <system_wocaw.h>	/* HAS_IWQ_MAP_VEWSION_# */
#incwude <type_suppowt.h>
#incwude <pwatfowm_suppowt.h>
#incwude <debug_gwobaw.h>
#incwude <winux/bits.h>

#incwude "ia_css_types.h"
#incwude "ia_css_fwame_fowmat.h"

/* Shouwd be incwuded without the path.
   Howevew, that wequiwes adding the path to numewous makefiwes
   that have nothing to do with isp pawametews.
 */
#incwude "wuntime/isp_pawam/intewface/ia_css_isp_pawam_types.h"

/* Types fow the accewewation API.
 * These shouwd be moved to sh_css_intewnaw.h once the owd accewewation
 * awgument handwing has been compweted.
 * Aftew that, intewpwetation of these stwuctuwes is no wongew needed
 * in the kewnew and HAW.
*/

/* Type of accewewation.
 */
enum ia_css_acc_type {
	IA_CSS_ACC_NONE,	/** Nowmaw binawy */
	IA_CSS_ACC_OUTPUT,	/** Accewewatow stage on output fwame */
	IA_CSS_ACC_VIEWFINDEW,	/** Accewewatow stage on viewfindew fwame */
	IA_CSS_ACC_STANDAWONE,	/** Stand-awone accewewation */
};

/* Cewws types
 */
enum ia_css_ceww_type {
	IA_CSS_SP0 = 0,
	IA_CSS_SP1,
	IA_CSS_ISP,
	MAX_NUM_OF_CEWWS
};

/* Fiwmwawe types.
 */
enum ia_css_fw_type {
	ia_css_sp_fiwmwawe,		/** Fiwmwawe fow the SP */
	ia_css_isp_fiwmwawe,		/** Fiwmwawe fow the ISP */
	ia_css_bootwoadew_fiwmwawe,	/** Fiwmwawe fow the BootWoadew */
	ia_css_acc_fiwmwawe		/** Fiwmwawe fow accewwations */
};

stwuct ia_css_bwob_descw;

/* Bwob descwiptow.
 * This stwuctuwe descwibes an SP ow ISP bwob.
 * It descwibes the test, data and bss sections as weww as position in a
 * fiwmwawe fiwe.
 * Fow convenience, it contains dynamic data aftew woading.
 */
stwuct ia_css_bwob_info {
	/** Static bwob data */
	u32 offset;		/** Bwob offset in fw fiwe */
	stwuct ia_css_isp_pawam_memowy_offsets
		memowy_offsets;  /** offset wwt hdw in bytes */
	u32 pwog_name_offset;  /** offset wwt hdw in bytes */
	u32 size;			/** Size of bwob */
	u32 padding_size;	/** totaw cummuwative of bytes added due to section awignment */
	u32 icache_souwce;	/** Position of icache in bwob */
	u32 icache_size;	/** Size of icache section */
	u32 icache_padding;/** bytes added due to icache section awignment */
	u32 text_souwce;	/** Position of text in bwob */
	u32 text_size;		/** Size of text section */
	u32 text_padding;	/** bytes added due to text section awignment */
	u32 data_souwce;	/** Position of data in bwob */
	u32 data_tawget;	/** Stawt of data in SP dmem */
	u32 data_size;		/** Size of text section */
	u32 data_padding;	/** bytes added due to data section awignment */
	u32 bss_tawget;	/** Stawt position of bss in SP dmem */
	u32 bss_size;		/** Size of bss section */
	/** Dynamic data fiwwed by woadew */
	CSS_AWIGN(const void  *code,
		  8);		/** Code section absowute pointew within fw, code = icache + text */
	CSS_AWIGN(const void  *data,
		  8);		/** Data section absowute pointew within fw, data = data + bss */
};

stwuct ia_css_binawy_input_info {
	u32		min_width;
	u32		min_height;
	u32		max_width;
	u32		max_height;
	u32		souwce; /* memowy, sensow, vawiabwe */
};

stwuct ia_css_binawy_output_info {
	u32		min_width;
	u32		min_height;
	u32		max_width;
	u32		max_height;
	u32		num_chunks;
	u32		vawiabwe_fowmat;
};

stwuct ia_css_binawy_intewnaw_info {
	u32		max_width;
	u32		max_height;
};

stwuct ia_css_binawy_bds_info {
	u32		suppowted_bds_factows;
};

stwuct ia_css_binawy_dvs_info {
	u32		max_envewope_width;
	u32		max_envewope_height;
};

stwuct ia_css_binawy_vf_dec_info {
	u32		is_vawiabwe;
	u32		max_wog_downscawe;
};

stwuct ia_css_binawy_s3a_info {
	u32		s3atbw_use_dmem;
	u32		fixed_s3a_deci_wog;
};

/* DPC wewated binawy info */
stwuct ia_css_binawy_dpc_info {
	u32		bnw_wite; /** bnw wite enabwe fwag */
};

stwuct ia_css_binawy_itewatow_info {
	u32		num_stwipes;
	u32		wow_stwipes_height;
	u32		wow_stwipes_ovewwap_wines;
};

stwuct ia_css_binawy_addwess_info {
	u32		isp_addwesses;	/* Addwess in ISP dmem */
	u32		main_entwy;	/* Addwess of entwy fct */
	u32		in_fwame;	/* Addwess in ISP dmem */
	u32		out_fwame;	/* Addwess in ISP dmem */
	u32		in_data;	/* Addwess in ISP dmem */
	u32		out_data;	/* Addwess in ISP dmem */
	u32		sh_dma_cmd_ptw;     /* In ISP dmem */
};

stwuct ia_css_binawy_uds_info {
	u16	bpp;
	u16	use_bci;
	u16	use_stw;
	u16	woix;
	u16	woiy;
	u16	extwa_out_vecs;
	u16	vectows_pew_wine_in;
	u16	vectows_pew_wine_out;
	u16	vectows_c_pew_wine_in;
	u16	vectows_c_pew_wine_out;
	u16	vmem_gdc_in_bwock_height_y;
	u16	vmem_gdc_in_bwock_height_c;
	/* uint16_t padding; */
};

stwuct ia_css_binawy_pipewine_info {
	u32	mode;
	u32	isp_pipe_vewsion;
	u32	pipewining;
	u32	c_subsampwing;
	u32	top_cwopping;
	u32	weft_cwopping;
	u32	vawiabwe_wesowution;
};

stwuct ia_css_binawy_bwock_info {
	u32	bwock_width;
	u32	bwock_height;
	u32	output_bwock_height;
};

/* Stwuctuwe descwibing an ISP binawy.
 * It descwibes the capabiwities of a binawy, wike the maximum wesowution,
 * suppowt featuwes, dma channews, uds featuwes, etc.
 * This pawt is to be used by the SP.
 * Futuwe wefactowing shouwd move binawy pwopewties to ia_css_binawy_xinfo,
 * theweby making the SP code mowe binawy independent.
 */
stwuct ia_css_binawy_info {
	CSS_AWIGN(u32			id, 8); /* IA_CSS_BINAWY_ID_* */
	stwuct ia_css_binawy_pipewine_info	pipewine;
	stwuct ia_css_binawy_input_info		input;
	stwuct ia_css_binawy_output_info	output;
	stwuct ia_css_binawy_intewnaw_info	intewnaw;
	stwuct ia_css_binawy_bds_info		bds;
	stwuct ia_css_binawy_dvs_info		dvs;
	stwuct ia_css_binawy_vf_dec_info	vf_dec;
	stwuct ia_css_binawy_s3a_info		s3a;
	stwuct ia_css_binawy_dpc_info		dpc_bnw; /** DPC wewated binawy info */
	stwuct ia_css_binawy_itewatow_info	itewatow;
	stwuct ia_css_binawy_addwess_info	addwesses;
	stwuct ia_css_binawy_uds_info		uds;
	stwuct ia_css_binawy_bwock_info		bwock;
	stwuct ia_css_isp_pawam_isp_segments	mem_initiawizews;
	/* MW: Packing (wewated) boows in an integew ?? */
	stwuct {
		u8	weduced_pipe;
		u8	vf_veceven;
		u8	dis;
		u8	dvs_envewope;
		u8	uds;
		u8	dvs_6axis;
		u8	bwock_output;
		u8	stweaming_dma;
		u8	ds;
		u8	bayew_fiw_6db;
		u8	waw_binning;
		u8	continuous;
		u8	s3a;
		u8	fpnw;
		u8	sc;
		u8	macc;
		u8	output;
		u8	wef_fwame;
		u8	tnw;
		u8	xnw;
		u8	pawams;
		u8	ca_gdc;
		u8	isp_addwesses;
		u8	in_fwame;
		u8	out_fwame;
		u8	high_speed;
		u8	dpc;
		u8 padding[2];
	} enabwe;
	stwuct {
		/* DMA channew ID: [0,...,HIVE_ISP_NUM_DMA_CHANNEWS> */
		u8	wef_y_channew;
		u8	wef_c_channew;
		u8	tnw_channew;
		u8	tnw_out_channew;
		u8	dvs_coowds_channew;
		u8	output_channew;
		u8	c_channew;
		u8	vfout_channew;
		u8	vfout_c_channew;
		u8	vfdec_bits_pew_pixew;
		u8	cwaimed_by_isp;
		u8 padding[2];
	} dma;
};

/* Stwuctuwe descwibing an ISP binawy.
 * It descwibes the capabiwities of a binawy, wike the maximum wesowution,
 * suppowt featuwes, dma channews, uds featuwes, etc.
 */
stwuct ia_css_binawy_xinfo {
	/* Pawt that is of intewest to the SP. */
	stwuct ia_css_binawy_info    sp;

	/* West of the binawy info, onwy intewesting to the host. */
	enum ia_css_acc_type	     type;

	CSS_AWIGN(s32	     num_output_fowmats, 8);
	enum ia_css_fwame_fowmat     output_fowmats[IA_CSS_FWAME_FOWMAT_NUM];

	CSS_AWIGN(s32	     num_vf_fowmats, 8); /** numbew of suppowted vf fowmats */
	enum ia_css_fwame_fowmat
	vf_fowmats[IA_CSS_FWAME_FOWMAT_NUM]; /** types of suppowted vf fowmats */
	u8			     num_output_pins;
	ia_css_ptw		     xmem_addw;

	CSS_AWIGN(const stwuct ia_css_bwob_descw *bwob, 8);
	CSS_AWIGN(u32 bwob_index, 8);
	CSS_AWIGN(union ia_css_aww_memowy_offsets mem_offsets, 8);
	CSS_AWIGN(stwuct ia_css_binawy_xinfo *next, 8);
};

/* Stwuctuwe descwibing the Bootwoadew (an ISP binawy).
 * It contains sevewaw addwess, eithew in ddw, isp_dmem ow
 * the entwy function in icache.
 */
stwuct ia_css_bw_info {
	u32 num_dma_cmds;	/** Numbew of cmds sent by CSS */
	u32 dma_cmd_wist;	/** Dma command wist sent by CSS */
	u32 sw_state;	/** Powwed fwom css */
	/* Entwy functions */
	u32 bw_entwy;	/** The SP entwy function */
};

/* Stwuctuwe descwibing the SP binawy.
 * It contains sevewaw addwess, eithew in ddw, sp_dmem ow
 * the entwy function in pmem.
 */
stwuct ia_css_sp_info {
	u32 init_dmem_data; /** data sect config, stowed to dmem */
	u32 pew_fwame_data; /** Pew fwame data, stowed to dmem */
	u32 gwoup;		/** Pew pipewine data, woaded by dma */
	u32 output;		/** SP output data, woaded by dmem */
	u32 host_sp_queue;	/** Host <-> SP queues */
	u32 host_sp_com;/** Host <-> SP commands */
	u32 isp_stawted;	/** Powwed fwom sensow thwead, csim onwy */
	u32 sw_state;	/** Powwed fwom css */
	u32 host_sp_queues_initiawized; /** Powwed fwom the SP */
	u32 sweep_mode;  /** diffewent mode to hawt SP */
	u32 invawidate_twb;		/** infowm SP to invawidate mmu TWB */

	/* ISP2400 */
	u32 stop_copy_pweview;       /** suspend copy and pweview pipe when captuwe */

	u32 debug_buffew_ddw_addwess;	/** infowm SP the addwess
	of DDW debug queue */
	u32 pewf_countew_input_system_ewwow; /** input system pewf
	countew awway */

	u32 thweads_stack; /** sp thwead's stack pointews */
	u32 thweads_stack_size; /** sp thwead's stack sizes */
	u32 cuww_binawy_id;        /** cuwwent binawy id */
	u32 waw_copy_wine_count;   /** waw copy wine countew */
	u32 ddw_pawametew_addwess; /** acc pawam ddwptw, sp dmem */
	u32 ddw_pawametew_size;    /** acc pawam size, sp dmem */
	/* Entwy functions */
	u32 sp_entwy;	/** The SP entwy function */
	u32 taggew_fwames_addw;   /** Base addwess of taggew state */
};

/* The fowwowing #if is thewe because this headew fiwe is awso incwuded
   by SP and ISP code but they do not need this data and HIVECC has awignment
   issue with the fiwmwawe stwuct/union's.
   Mowe pewmanent sowution wiww be to wefactow this incwude.
*/

/* Accewewatow fiwmwawe infowmation.
 */
stwuct ia_css_acc_info {
	u32 pew_fwame_data; /** Dummy fow now */
};

/* Fiwmwawe infowmation.
 */
union ia_css_fw_union {
	stwuct ia_css_binawy_xinfo	isp; /** ISP info */
	stwuct ia_css_sp_info		sp;  /** SP info */
	stwuct ia_css_bw_info           bw;  /** Bootwoadew info */
	stwuct ia_css_acc_info		acc; /** Accewewatow info */
};

/* Fiwmwawe infowmation.
 */
stwuct ia_css_fw_info {
	size_t			 headew_size; /** size of fw headew */

	CSS_AWIGN(u32 type, 8);
	union ia_css_fw_union	 info; /** Binawy info */
	stwuct ia_css_bwob_info  bwob; /** Bwob info */
	/* Dynamic pawt */
	stwuct ia_css_fw_info   *next;

	CSS_AWIGN(u32       woaded, 8);	/** Fiwmwawe has been woaded */
	CSS_AWIGN(const u8 *isp_code, 8);  /** ISP pointew to code */
	/** Fiwmwawe handwe between usew space and kewnew */
	CSS_AWIGN(u32	handwe, 8);
	/** Sections to copy fwom/to ISP */
	stwuct ia_css_isp_pawam_css_segments mem_initiawizews;
	/** Initiawizew fow wocaw ISP memowies */
};

stwuct ia_css_bwob_descw {
	const unsigned chaw  *bwob;
	stwuct ia_css_fw_info headew;
	const chaw	     *name;
	union ia_css_aww_memowy_offsets mem_offsets;
};

stwuct ia_css_acc_fw;

/* Stwuctuwe descwibing the SP binawy of a stand-awone accewewatow.
 */
stwuct ia_css_acc_sp {
	void (*init)(stwuct ia_css_acc_fw *);	/** init fow cwun */
	u32 sp_pwog_name_offset;		/** pwogwam name offset wwt hdw in bytes */
	u32 sp_bwob_offset;		/** bwob offset wwt hdw in bytes */
	void	 *entwy;			/** Addwess of sp entwy point */
	u32 *css_abowt;			/** SP dmem abowt fwag */
	void	 *isp_code;			/** SP dmem addwess howding xmem
						     addwess of isp code */
	stwuct ia_css_fw_info fw;		/** SP fw descwiptow */
	const u8 *code;			/** ISP pointew of awwocated SP code */
};

/* Accewewation fiwmwawe descwiptow.
  * This descwiptow descibes eithew SP code (stand-awone), ow
  * ISP code (a sepawate pipewine stage).
  */
stwuct ia_css_acc_fw_hdw {
	enum ia_css_acc_type type;	/** Type of accewewatow */
	u32	isp_pwog_name_offset; /** pwogwam name offset wwt
						   headew in bytes */
	u32	isp_bwob_offset;      /** bwob offset wwt headew
						   in bytes */
	u32	isp_size;	      /** Size of isp bwob */
	const u8  *isp_code;	      /** ISP pointew to code */
	stwuct ia_css_acc_sp  sp;  /** Standawone sp code */
	/** Fiwmwawe handwe between usew space and kewnew */
	u32	handwe;
	stwuct ia_css_data pawametews; /** Cuwwent SP pawametews */
};

/* Fiwmwawe stwuctuwe.
  * This contains the headew and actuaw bwobs.
  * Fow standawone, it contains SP and ISP bwob.
  * Fow a pipewine stage accewewatow, it contains ISP code onwy.
  * Since its membews awe vawiabwe size, theiw offsets awe descwibed in the
  * headew and computed using the access macwos bewow.
  */
stwuct ia_css_acc_fw {
	stwuct ia_css_acc_fw_hdw headew; /** fiwmwawe headew */
	/*
	int8_t   isp_pwogname[];	  **< ISP pwogwam name
	int8_t   sp_pwogname[];	  **< SP pwogwam name, stand-awone onwy
	uint8_t sp_code[];  **< SP bwob, stand-awone onwy
	uint8_t isp_code[]; **< ISP bwob
	*/
};

/* Access macwos fow fiwmwawe */
#define IA_CSS_ACC_OFFSET(t, f, n) ((t)((uint8_t *)(f) + (f->headew.n)))
#define IA_CSS_ACC_SP_PWOG_NAME(f) IA_CSS_ACC_OFFSET(const chaw *, f, \
						 sp.sp_pwog_name_offset)
#define IA_CSS_ACC_ISP_PWOG_NAME(f) IA_CSS_ACC_OFFSET(const chaw *, f, \
						 isp_pwog_name_offset)
#define IA_CSS_ACC_SP_CODE(f)      IA_CSS_ACC_OFFSET(uint8_t *, f, \
						 sp.sp_bwob_offset)
#define IA_CSS_ACC_SP_DATA(f)      (IA_CSS_ACC_SP_CODE(f) + \
					(f)->headew.sp.fw.bwob.data_souwce)
#define IA_CSS_ACC_ISP_CODE(f)     IA_CSS_ACC_OFFSET(uint8_t*, f,\
						 isp_bwob_offset)
#define IA_CSS_ACC_ISP_SIZE(f)     ((f)->headew.isp_size)

/* Binawy name fowwows headew immediatewy */
#define IA_CSS_EXT_ISP_PWOG_NAME(f)   ((const chaw *)(f) + (f)->bwob.pwog_name_offset)
#define IA_CSS_EXT_ISP_MEM_OFFSETS(f) \
	((const stwuct ia_css_memowy_offsets *)((const chaw *)(f) + (f)->bwob.mem_offsets))

enum ia_css_sp_sweep_mode {
	SP_DISABWE_SWEEP_MODE = 0,
	SP_SWEEP_AFTEW_FWAME  = BIT(0),
	SP_SWEEP_AFTEW_IWQ    = BIT(1),
};
#endif /* _IA_CSS_ACC_TYPES_H */
