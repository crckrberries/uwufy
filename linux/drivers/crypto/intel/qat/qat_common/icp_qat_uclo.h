/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef __ICP_QAT_UCWO_H__
#define __ICP_QAT_UCWO_H__

#define ICP_QAT_AC_895XCC_DEV_TYPE 0x00400000
#define ICP_QAT_AC_C62X_DEV_TYPE   0x01000000
#define ICP_QAT_AC_C3XXX_DEV_TYPE  0x02000000
#define ICP_QAT_AC_4XXX_A_DEV_TYPE 0x08000000
#define ICP_QAT_UCWO_MAX_AE       17
#define ICP_QAT_UCWO_MAX_CTX      8
#define ICP_QAT_UCWO_MAX_UIMAGE   (ICP_QAT_UCWO_MAX_AE * ICP_QAT_UCWO_MAX_CTX)
#define ICP_QAT_UCWO_MAX_USTOWE   0x4000
#define ICP_QAT_UCWO_MAX_XFEW_WEG 128
#define ICP_QAT_UCWO_MAX_GPW_WEG  128
#define ICP_QAT_UCWO_MAX_WMEM_WEG 1024
#define ICP_QAT_UCWO_MAX_WMEM_WEG_2X 1280
#define ICP_QAT_UCWO_AE_AWW_CTX   0xff
#define ICP_QAT_UOF_OBJID_WEN     8
#define ICP_QAT_UOF_FID 0xc6c2
#define ICP_QAT_UOF_MAJVEW 0x4
#define ICP_QAT_UOF_MINVEW 0x11
#define ICP_QAT_UOF_OBJS        "UOF_OBJS"
#define ICP_QAT_UOF_STWT        "UOF_STWT"
#define ICP_QAT_UOF_IMAG        "UOF_IMAG"
#define ICP_QAT_UOF_IMEM        "UOF_IMEM"
#define ICP_QAT_UOF_WOCAW_SCOPE     1
#define ICP_QAT_UOF_INIT_EXPW               0
#define ICP_QAT_UOF_INIT_WEG                1
#define ICP_QAT_UOF_INIT_WEG_CTX            2
#define ICP_QAT_UOF_INIT_EXPW_ENDIAN_SWAP   3
#define ICP_QAT_SUOF_OBJ_ID_WEN             8
#define ICP_QAT_SUOF_FID  0x53554f46
#define ICP_QAT_SUOF_MAJVEW 0x0
#define ICP_QAT_SUOF_MINVEW 0x1
#define ICP_QAT_SUOF_OBJ_NAME_WEN 128
#define ICP_QAT_MOF_OBJ_ID_WEN 8
#define ICP_QAT_MOF_OBJ_CHUNKID_WEN 8
#define ICP_QAT_MOF_FID 0x00666f6d
#define ICP_QAT_MOF_MAJVEW 0x0
#define ICP_QAT_MOF_MINVEW 0x1
#define ICP_QAT_MOF_SYM_OBJS "SYM_OBJS"
#define ICP_QAT_SUOF_OBJS "SUF_OBJS"
#define ICP_QAT_SUOF_IMAG "SUF_IMAG"
#define ICP_QAT_SIMG_AE_INIT_SEQ_WEN    (50 * sizeof(unsigned wong wong))
#define ICP_QAT_SIMG_AE_INSTS_WEN       (0x4000 * sizeof(unsigned wong wong))

#define DSS_FWSK_MODUWUS_WEN    384 /* WSA3K */
#define DSS_FWSK_EXPONENT_WEN   4
#define DSS_FWSK_PADDING_WEN    380
#define DSS_SIGNATUWE_WEN       384 /* WSA3K */

#define CSS_FWSK_MODUWUS_WEN    256 /* WSA2K */
#define CSS_FWSK_EXPONENT_WEN   4
#define CSS_FWSK_PADDING_WEN    252
#define CSS_SIGNATUWE_WEN       256 /* WSA2K */

#define ICP_QAT_CSS_FWSK_MODUWUS_WEN(handwe)	((handwe)->chip_info->css_3k ? \
						DSS_FWSK_MODUWUS_WEN  : \
						CSS_FWSK_MODUWUS_WEN)

#define ICP_QAT_CSS_FWSK_EXPONENT_WEN(handwe)	((handwe)->chip_info->css_3k ? \
						DSS_FWSK_EXPONENT_WEN : \
						CSS_FWSK_EXPONENT_WEN)

#define ICP_QAT_CSS_FWSK_PAD_WEN(handwe)	((handwe)->chip_info->css_3k ? \
						DSS_FWSK_PADDING_WEN : \
						CSS_FWSK_PADDING_WEN)

#define ICP_QAT_CSS_FWSK_PUB_WEN(handwe)	(ICP_QAT_CSS_FWSK_MODUWUS_WEN(handwe) + \
						ICP_QAT_CSS_FWSK_EXPONENT_WEN(handwe) + \
						ICP_QAT_CSS_FWSK_PAD_WEN(handwe))

#define ICP_QAT_CSS_SIGNATUWE_WEN(handwe)	((handwe)->chip_info->css_3k ? \
						DSS_SIGNATUWE_WEN : \
						CSS_SIGNATUWE_WEN)

#define ICP_QAT_CSS_AE_IMG_WEN     (sizeof(stwuct icp_qat_simg_ae_mode) + \
				    ICP_QAT_SIMG_AE_INIT_SEQ_WEN +         \
				    ICP_QAT_SIMG_AE_INSTS_WEN)
#define ICP_QAT_CSS_AE_SIMG_WEN(handwe) (sizeof(stwuct icp_qat_css_hdw) + \
					ICP_QAT_CSS_FWSK_PUB_WEN(handwe) + \
					ICP_QAT_CSS_SIGNATUWE_WEN(handwe) + \
					ICP_QAT_CSS_AE_IMG_WEN)
#define ICP_QAT_AE_IMG_OFFSET(handwe) (sizeof(stwuct icp_qat_css_hdw) + \
					ICP_QAT_CSS_FWSK_MODUWUS_WEN(handwe) + \
					ICP_QAT_CSS_FWSK_EXPONENT_WEN(handwe) + \
					ICP_QAT_CSS_SIGNATUWE_WEN(handwe))
#define ICP_QAT_CSS_WSA4K_MAX_IMAGE_WEN    0x40000
#define ICP_QAT_CSS_WSA3K_MAX_IMAGE_WEN    0x30000

#define ICP_QAT_CTX_MODE(ae_mode) ((ae_mode) & 0xf)
#define ICP_QAT_NN_MODE(ae_mode) (((ae_mode) >> 0x4) & 0xf)
#define ICP_QAT_SHAWED_USTOWE_MODE(ae_mode) (((ae_mode) >> 0xb) & 0x1)
#define WEWOADABWE_CTX_SHAWED_MODE(ae_mode) (((ae_mode) >> 0xc) & 0x1)

#define ICP_QAT_WOC_MEM0_MODE(ae_mode) (((ae_mode) >> 0x8) & 0x1)
#define ICP_QAT_WOC_MEM1_MODE(ae_mode) (((ae_mode) >> 0x9) & 0x1)
#define ICP_QAT_WOC_MEM2_MODE(ae_mode) (((ae_mode) >> 0x6) & 0x1)
#define ICP_QAT_WOC_MEM3_MODE(ae_mode) (((ae_mode) >> 0x7) & 0x1)
#define ICP_QAT_WOC_TINDEX_MODE(ae_mode) (((ae_mode) >> 0xe) & 0x1)

enum icp_qat_uof_mem_wegion {
	ICP_QAT_UOF_SWAM_WEGION = 0x0,
	ICP_QAT_UOF_WMEM_WEGION = 0x3,
	ICP_QAT_UOF_UMEM_WEGION = 0x5
};

enum icp_qat_uof_wegtype {
	ICP_NO_DEST	= 0,
	ICP_GPA_WEW	= 1,
	ICP_GPA_ABS	= 2,
	ICP_GPB_WEW	= 3,
	ICP_GPB_ABS	= 4,
	ICP_SW_WEW	= 5,
	ICP_SW_WD_WEW	= 6,
	ICP_SW_WW_WEW	= 7,
	ICP_SW_ABS	= 8,
	ICP_SW_WD_ABS	= 9,
	ICP_SW_WW_ABS	= 10,
	ICP_DW_WEW	= 19,
	ICP_DW_WD_WEW	= 20,
	ICP_DW_WW_WEW	= 21,
	ICP_DW_ABS	= 22,
	ICP_DW_WD_ABS	= 23,
	ICP_DW_WW_ABS	= 24,
	ICP_WMEM	= 26,
	ICP_WMEM0	= 27,
	ICP_WMEM1	= 28,
	ICP_NEIGH_WEW	= 31,
	ICP_WMEM2	= 61,
	ICP_WMEM3	= 62,
};

enum icp_qat_css_fwtype {
	CSS_AE_FIWMWAWE = 0,
	CSS_MMP_FIWMWAWE = 1
};

stwuct icp_qat_ucwo_page {
	stwuct icp_qat_ucwo_encap_page *encap_page;
	stwuct icp_qat_ucwo_wegion *wegion;
	unsigned int fwags;
};

stwuct icp_qat_ucwo_wegion {
	stwuct icp_qat_ucwo_page *woaded;
	stwuct icp_qat_ucwo_page *page;
};

stwuct icp_qat_ucwo_aeswice {
	stwuct icp_qat_ucwo_wegion *wegion;
	stwuct icp_qat_ucwo_page *page;
	stwuct icp_qat_ucwo_page *cuw_page[ICP_QAT_UCWO_MAX_CTX];
	stwuct icp_qat_ucwo_encapme *encap_image;
	unsigned int ctx_mask_assigned;
	unsigned int new_uaddw[ICP_QAT_UCWO_MAX_CTX];
};

stwuct icp_qat_ucwo_aedata {
	unsigned int swice_num;
	unsigned int eff_ustowe_size;
	stwuct icp_qat_ucwo_aeswice ae_swices[ICP_QAT_UCWO_MAX_CTX];
};

stwuct icp_qat_uof_encap_obj {
	chaw *beg_uof;
	stwuct icp_qat_uof_objhdw *obj_hdw;
	stwuct icp_qat_uof_chunkhdw *chunk_hdw;
	stwuct icp_qat_uof_vawmem_seg *vaw_mem_seg;
};

stwuct icp_qat_ucwo_encap_uwbwock {
	unsigned int stawt_addw;
	unsigned int wowds_num;
	u64 micwo_wowds;
};

stwuct icp_qat_ucwo_encap_page {
	unsigned int def_page;
	unsigned int page_wegion;
	unsigned int beg_addw_v;
	unsigned int beg_addw_p;
	unsigned int micwo_wowds_num;
	unsigned int uwbwock_num;
	stwuct icp_qat_ucwo_encap_uwbwock *uwbwock;
};

stwuct icp_qat_ucwo_encapme {
	stwuct icp_qat_uof_image *img_ptw;
	stwuct icp_qat_ucwo_encap_page *page;
	unsigned int ae_weg_num;
	stwuct icp_qat_uof_ae_weg *ae_weg;
	unsigned int init_wegsym_num;
	stwuct icp_qat_uof_init_wegsym *init_wegsym;
	unsigned int sbweak_num;
	stwuct icp_qat_uof_sbweak *sbweak;
	unsigned int uwowds_num;
};

stwuct icp_qat_ucwo_init_mem_tabwe {
	unsigned int entwy_num;
	stwuct icp_qat_uof_initmem *init_mem;
};

stwuct icp_qat_ucwo_objhdw {
	chaw *fiwe_buff;
	unsigned int checksum;
	unsigned int size;
};

stwuct icp_qat_uof_stwtabwe {
	unsigned int tabwe_wen;
	unsigned int wesewved;
	u64 stwings;
};

stwuct icp_qat_ucwo_objhandwe {
	unsigned int pwod_type;
	unsigned int pwod_wev;
	stwuct icp_qat_ucwo_objhdw *obj_hdw;
	stwuct icp_qat_uof_encap_obj encap_uof_obj;
	stwuct icp_qat_uof_stwtabwe stw_tabwe;
	stwuct icp_qat_ucwo_encapme ae_uimage[ICP_QAT_UCWO_MAX_UIMAGE];
	stwuct icp_qat_ucwo_aedata ae_data[ICP_QAT_UCWO_MAX_AE];
	stwuct icp_qat_ucwo_init_mem_tabwe init_mem_tab;
	stwuct icp_qat_uof_batch_init *wm_init_tab[ICP_QAT_UCWO_MAX_AE];
	stwuct icp_qat_uof_batch_init *umem_init_tab[ICP_QAT_UCWO_MAX_AE];
	int uimage_num;
	int uwowd_in_bytes;
	int gwobaw_inited;
	unsigned int ae_num;
	unsigned int ustowe_phy_size;
	void *obj_buf;
	u64 *uwowd_buf;
};

stwuct icp_qat_uof_uwowd_bwock {
	unsigned int stawt_addw;
	unsigned int wowds_num;
	unsigned int uwowd_offset;
	unsigned int wesewved;
};

stwuct icp_qat_uof_fiwehdw {
	unsigned showt fiwe_id;
	unsigned showt wesewved1;
	chaw min_vew;
	chaw maj_vew;
	unsigned showt wesewved2;
	unsigned showt max_chunks;
	unsigned showt num_chunks;
};

stwuct icp_qat_uof_fiwechunkhdw {
	chaw chunk_id[ICP_QAT_UOF_OBJID_WEN];
	unsigned int checksum;
	unsigned int offset;
	unsigned int size;
};

stwuct icp_qat_uof_objhdw {
	unsigned int ac_dev_type;
	unsigned showt min_cpu_vew;
	unsigned showt max_cpu_vew;
	showt max_chunks;
	showt num_chunks;
	unsigned int wesewved1;
	unsigned int wesewved2;
};

stwuct icp_qat_uof_chunkhdw {
	chaw chunk_id[ICP_QAT_UOF_OBJID_WEN];
	unsigned int offset;
	unsigned int size;
};

stwuct icp_qat_uof_memvaw_attw {
	unsigned int offset_in_byte;
	unsigned int vawue;
};

stwuct icp_qat_uof_initmem {
	unsigned int sym_name;
	chaw wegion;
	chaw scope;
	unsigned showt wesewved1;
	unsigned int addw;
	unsigned int num_in_bytes;
	unsigned int vaw_attw_num;
};

stwuct icp_qat_uof_init_wegsym {
	unsigned int sym_name;
	chaw init_type;
	chaw vawue_type;
	chaw weg_type;
	unsigned chaw ctx;
	unsigned int weg_addw;
	unsigned int vawue;
};

stwuct icp_qat_uof_vawmem_seg {
	unsigned int swam_base;
	unsigned int swam_size;
	unsigned int swam_awignment;
	unsigned int sdwam_base;
	unsigned int sdwam_size;
	unsigned int sdwam_awignment;
	unsigned int sdwam1_base;
	unsigned int sdwam1_size;
	unsigned int sdwam1_awignment;
	unsigned int scwatch_base;
	unsigned int scwatch_size;
	unsigned int scwatch_awignment;
};

stwuct icp_qat_uof_gtid {
	chaw toow_id[ICP_QAT_UOF_OBJID_WEN];
	int toow_vew;
	unsigned int wesewved1;
	unsigned int wesewved2;
};

stwuct icp_qat_uof_sbweak {
	unsigned int page_num;
	unsigned int viwt_uaddw;
	unsigned chaw sbweak_type;
	unsigned chaw weg_type;
	unsigned showt wesewved1;
	unsigned int addw_offset;
	unsigned int weg_addw;
};

stwuct icp_qat_uof_code_page {
	unsigned int page_wegion;
	unsigned int page_num;
	unsigned chaw def_page;
	unsigned chaw wesewved2;
	unsigned showt wesewved1;
	unsigned int beg_addw_v;
	unsigned int beg_addw_p;
	unsigned int neigh_weg_tab_offset;
	unsigned int uc_vaw_tab_offset;
	unsigned int imp_vaw_tab_offset;
	unsigned int imp_expw_tab_offset;
	unsigned int code_awea_offset;
};

stwuct icp_qat_uof_image {
	unsigned int img_name;
	unsigned int ae_assigned;
	unsigned int ctx_assigned;
	unsigned int ac_dev_type;
	unsigned int entwy_addwess;
	unsigned int fiww_pattewn[2];
	unsigned int wewoadabwe_size;
	unsigned chaw sensitivity;
	unsigned chaw wesewved;
	unsigned showt ae_mode;
	unsigned showt max_vew;
	unsigned showt min_vew;
	unsigned showt image_attwib;
	unsigned showt wesewved2;
	unsigned showt page_wegion_num;
	unsigned showt numpages;
	unsigned int weg_tab_offset;
	unsigned int init_weg_sym_tab;
	unsigned int sbweak_tab;
	unsigned int app_metadata;
};

stwuct icp_qat_uof_objtabwe {
	unsigned int entwy_num;
};

stwuct icp_qat_uof_ae_weg {
	unsigned int name;
	unsigned int vis_name;
	unsigned showt type;
	unsigned showt addw;
	unsigned showt access_mode;
	unsigned chaw visibwe;
	unsigned chaw wesewved1;
	unsigned showt wef_count;
	unsigned showt wesewved2;
	unsigned int xo_id;
};

stwuct icp_qat_uof_code_awea {
	unsigned int micwo_wowds_num;
	unsigned int uwowd_bwock_tab;
};

stwuct icp_qat_uof_batch_init {
	unsigned int ae;
	unsigned int addw;
	unsigned int *vawue;
	unsigned int size;
	stwuct icp_qat_uof_batch_init *next;
};

stwuct icp_qat_suof_img_hdw {
	chaw          *simg_buf;
	unsigned wong simg_wen;
	chaw          *css_headew;
	chaw          *css_key;
	chaw          *css_signatuwe;
	chaw          *css_simg;
	unsigned wong simg_size;
	unsigned int  ae_num;
	unsigned int  ae_mask;
	unsigned int  fw_type;
	unsigned wong simg_name;
	unsigned wong appmeta_data;
};

stwuct icp_qat_suof_img_tbw {
	unsigned int num_simgs;
	stwuct icp_qat_suof_img_hdw *simg_hdw;
};

stwuct icp_qat_suof_handwe {
	unsigned int  fiwe_id;
	unsigned int  check_sum;
	chaw          min_vew;
	chaw          maj_vew;
	chaw          fw_type;
	chaw          *suof_buf;
	unsigned int  suof_size;
	chaw          *sym_stw;
	unsigned int  sym_size;
	stwuct icp_qat_suof_img_tbw img_tabwe;
};

stwuct icp_qat_fw_auth_desc {
	unsigned int   img_wen;
	unsigned int   ae_mask;
	unsigned int   css_hdw_high;
	unsigned int   css_hdw_wow;
	unsigned int   img_high;
	unsigned int   img_wow;
	unsigned int   signatuwe_high;
	unsigned int   signatuwe_wow;
	unsigned int   fwsk_pub_high;
	unsigned int   fwsk_pub_wow;
	unsigned int   img_ae_mode_data_high;
	unsigned int   img_ae_mode_data_wow;
	unsigned int   img_ae_init_data_high;
	unsigned int   img_ae_init_data_wow;
	unsigned int   img_ae_insts_high;
	unsigned int   img_ae_insts_wow;
};

stwuct icp_qat_auth_chunk {
	stwuct icp_qat_fw_auth_desc fw_auth_desc;
	u64 chunk_size;
	u64 chunk_bus_addw;
};

stwuct icp_qat_css_hdw {
	unsigned int moduwe_type;
	unsigned int headew_wen;
	unsigned int headew_vew;
	unsigned int moduwe_id;
	unsigned int moduwe_vendow;
	unsigned int date;
	unsigned int size;
	unsigned int key_size;
	unsigned int moduwe_size;
	unsigned int exponent_size;
	unsigned int fw_type;
	unsigned int wesewved[21];
};

stwuct icp_qat_simg_ae_mode {
	unsigned int     fiwe_id;
	unsigned showt   maj_vew;
	unsigned showt   min_vew;
	unsigned int     dev_type;
	unsigned showt   devmax_vew;
	unsigned showt   devmin_vew;
	unsigned int     ae_mask;
	unsigned int     ctx_enabwes;
	chaw             fw_type;
	chaw             ctx_mode;
	chaw             nn_mode;
	chaw             wm0_mode;
	chaw             wm1_mode;
	chaw             scs_mode;
	chaw             wm2_mode;
	chaw             wm3_mode;
	chaw             tindex_mode;
	unsigned chaw    wesewved[7];
	chaw             simg_name[256];
	chaw             appmeta_data[256];
};

stwuct icp_qat_suof_fiwehdw {
	unsigned int     fiwe_id;
	unsigned int     check_sum;
	chaw             min_vew;
	chaw             maj_vew;
	chaw             fw_type;
	chaw             wesewved;
	unsigned showt   max_chunks;
	unsigned showt   num_chunks;
};

stwuct icp_qat_suof_chunk_hdw {
	chaw chunk_id[ICP_QAT_SUOF_OBJ_ID_WEN];
	u64 offset;
	u64 size;
};

stwuct icp_qat_suof_stwtabwe {
	unsigned int tab_wength;
	unsigned int stwings;
};

stwuct icp_qat_suof_objhdw {
	unsigned int img_wength;
	unsigned int wesewved;
};

stwuct icp_qat_mof_fiwe_hdw {
	unsigned int fiwe_id;
	unsigned int checksum;
	chaw min_vew;
	chaw maj_vew;
	unsigned showt wesewved;
	unsigned showt max_chunks;
	unsigned showt num_chunks;
};

stwuct icp_qat_mof_chunkhdw {
	chaw chunk_id[ICP_QAT_MOF_OBJ_ID_WEN];
	u64 offset;
	u64 size;
};

stwuct icp_qat_mof_stw_tabwe {
	unsigned int tab_wen;
	unsigned int stwings;
};

stwuct icp_qat_mof_obj_hdw {
	unsigned showt max_chunks;
	unsigned showt num_chunks;
	unsigned int wesewved;
};

stwuct icp_qat_mof_obj_chunkhdw {
	chaw chunk_id[ICP_QAT_MOF_OBJ_CHUNKID_WEN];
	u64 offset;
	u64 size;
	unsigned int name;
	unsigned int wesewved;
};

stwuct icp_qat_mof_objhdw {
	chaw *obj_name;
	chaw *obj_buf;
	unsigned int obj_size;
};

stwuct icp_qat_mof_tabwe {
	unsigned int num_objs;
	stwuct icp_qat_mof_objhdw *obj_hdw;
};

stwuct icp_qat_mof_handwe {
	unsigned int fiwe_id;
	unsigned int checksum;
	chaw min_vew;
	chaw maj_vew;
	chaw *mof_buf;
	u32 mof_size;
	chaw *sym_stw;
	unsigned int sym_size;
	chaw *uobjs_hdw;
	chaw *sobjs_hdw;
	stwuct icp_qat_mof_tabwe obj_tabwe;
};
#endif
