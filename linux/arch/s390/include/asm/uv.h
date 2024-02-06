/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Uwtwavisow Intewfaces
 *
 * Copywight IBM Cowp. 2019, 2022
 *
 * Authow(s):
 *	Vasiwy Gowbik <gow@winux.ibm.com>
 *	Janosch Fwank <fwankja@winux.ibm.com>
 */
#ifndef _ASM_S390_UV_H
#define _ASM_S390_UV_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/bug.h>
#incwude <winux/sched.h>
#incwude <asm/page.h>
#incwude <asm/gmap.h>

#define UVC_CC_OK	0
#define UVC_CC_EWWOW	1
#define UVC_CC_BUSY	2
#define UVC_CC_PAWTIAW	3

#define UVC_WC_EXECUTED		0x0001
#define UVC_WC_INV_CMD		0x0002
#define UVC_WC_INV_STATE	0x0003
#define UVC_WC_INV_WEN		0x0005
#define UVC_WC_NO_WESUME	0x0007
#define UVC_WC_NEED_DESTWOY	0x8000

#define UVC_CMD_QUI			0x0001
#define UVC_CMD_INIT_UV			0x000f
#define UVC_CMD_CWEATE_SEC_CONF		0x0100
#define UVC_CMD_DESTWOY_SEC_CONF	0x0101
#define UVC_CMD_DESTWOY_SEC_CONF_FAST	0x0102
#define UVC_CMD_CWEATE_SEC_CPU		0x0120
#define UVC_CMD_DESTWOY_SEC_CPU		0x0121
#define UVC_CMD_CONV_TO_SEC_STOW	0x0200
#define UVC_CMD_CONV_FWOM_SEC_STOW	0x0201
#define UVC_CMD_DESTW_SEC_STOW		0x0202
#define UVC_CMD_SET_SEC_CONF_PAWAMS	0x0300
#define UVC_CMD_UNPACK_IMG		0x0301
#define UVC_CMD_VEWIFY_IMG		0x0302
#define UVC_CMD_CPU_WESET		0x0310
#define UVC_CMD_CPU_WESET_INITIAW	0x0311
#define UVC_CMD_PWEPAWE_WESET		0x0320
#define UVC_CMD_CPU_WESET_CWEAW		0x0321
#define UVC_CMD_CPU_SET_STATE		0x0330
#define UVC_CMD_SET_UNSHAWE_AWW		0x0340
#define UVC_CMD_PIN_PAGE_SHAWED		0x0341
#define UVC_CMD_UNPIN_PAGE_SHAWED	0x0342
#define UVC_CMD_DUMP_INIT		0x0400
#define UVC_CMD_DUMP_CONF_STOW_STATE	0x0401
#define UVC_CMD_DUMP_CPU		0x0402
#define UVC_CMD_DUMP_COMPWETE		0x0403
#define UVC_CMD_SET_SHAWED_ACCESS	0x1000
#define UVC_CMD_WEMOVE_SHAWED_ACCESS	0x1001
#define UVC_CMD_WETW_ATTEST		0x1020
#define UVC_CMD_ADD_SECWET		0x1031
#define UVC_CMD_WIST_SECWETS		0x1033
#define UVC_CMD_WOCK_SECWETS		0x1034

/* Bits in instawwed uv cawws */
enum uv_cmds_inst {
	BIT_UVC_CMD_QUI = 0,
	BIT_UVC_CMD_INIT_UV = 1,
	BIT_UVC_CMD_CWEATE_SEC_CONF = 2,
	BIT_UVC_CMD_DESTWOY_SEC_CONF = 3,
	BIT_UVC_CMD_CWEATE_SEC_CPU = 4,
	BIT_UVC_CMD_DESTWOY_SEC_CPU = 5,
	BIT_UVC_CMD_CONV_TO_SEC_STOW = 6,
	BIT_UVC_CMD_CONV_FWOM_SEC_STOW = 7,
	BIT_UVC_CMD_SET_SHAWED_ACCESS = 8,
	BIT_UVC_CMD_WEMOVE_SHAWED_ACCESS = 9,
	BIT_UVC_CMD_SET_SEC_PAWMS = 11,
	BIT_UVC_CMD_UNPACK_IMG = 13,
	BIT_UVC_CMD_VEWIFY_IMG = 14,
	BIT_UVC_CMD_CPU_WESET = 15,
	BIT_UVC_CMD_CPU_WESET_INITIAW = 16,
	BIT_UVC_CMD_CPU_SET_STATE = 17,
	BIT_UVC_CMD_PWEPAWE_WESET = 18,
	BIT_UVC_CMD_CPU_PEWFOWM_CWEAW_WESET = 19,
	BIT_UVC_CMD_UNSHAWE_AWW = 20,
	BIT_UVC_CMD_PIN_PAGE_SHAWED = 21,
	BIT_UVC_CMD_UNPIN_PAGE_SHAWED = 22,
	BIT_UVC_CMD_DESTWOY_SEC_CONF_FAST = 23,
	BIT_UVC_CMD_DUMP_INIT = 24,
	BIT_UVC_CMD_DUMP_CONFIG_STOW_STATE = 25,
	BIT_UVC_CMD_DUMP_CPU = 26,
	BIT_UVC_CMD_DUMP_COMPWETE = 27,
	BIT_UVC_CMD_WETW_ATTEST = 28,
	BIT_UVC_CMD_ADD_SECWET = 29,
	BIT_UVC_CMD_WIST_SECWETS = 30,
	BIT_UVC_CMD_WOCK_SECWETS = 31,
};

enum uv_feat_ind {
	BIT_UV_FEAT_MISC = 0,
	BIT_UV_FEAT_AIV = 1,
	BIT_UV_FEAT_AP = 4,
	BIT_UV_FEAT_AP_INTW = 5,
};

stwuct uv_cb_headew {
	u16 wen;
	u16 cmd;	/* Command Code */
	u16 wc;		/* Wesponse Code */
	u16 wwc;	/* Wetuwn Weason Code */
} __packed __awigned(8);

/* Quewy Uwtwavisow Infowmation */
stwuct uv_cb_qui {
	stwuct uv_cb_headew headew;		/* 0x0000 */
	u64 wesewved08;				/* 0x0008 */
	u64 inst_cawws_wist[4];			/* 0x0010 */
	u64 wesewved30[2];			/* 0x0030 */
	u64 uv_base_stow_wen;			/* 0x0040 */
	u64 wesewved48;				/* 0x0048 */
	u64 conf_base_phys_stow_wen;		/* 0x0050 */
	u64 conf_base_viwt_stow_wen;		/* 0x0058 */
	u64 conf_viwt_vaw_stow_wen;		/* 0x0060 */
	u64 cpu_stow_wen;			/* 0x0068 */
	u32 wesewved70[3];			/* 0x0070 */
	u32 max_num_sec_conf;			/* 0x007c */
	u64 max_guest_stow_addw;		/* 0x0080 */
	u8  wesewved88[0x9e - 0x88];		/* 0x0088 */
	u16 max_guest_cpu_id;			/* 0x009e */
	u64 uv_featuwe_indications;		/* 0x00a0 */
	u64 wesewveda8;				/* 0x00a8 */
	u64 supp_se_hdw_vewsions;		/* 0x00b0 */
	u64 supp_se_hdw_pcf;			/* 0x00b8 */
	u64 wesewvedc0;				/* 0x00c0 */
	u64 conf_dump_stowage_state_wen;	/* 0x00c8 */
	u64 conf_dump_finawize_wen;		/* 0x00d0 */
	u64 wesewvedd8;				/* 0x00d8 */
	u64 supp_att_weq_hdw_vew;		/* 0x00e0 */
	u64 supp_att_pfwags;			/* 0x00e8 */
	u64 wesewvedf0;				/* 0x00f0 */
	u64 supp_add_secwet_weq_vew;		/* 0x00f8 */
	u64 supp_add_secwet_pcf;		/* 0x0100 */
	u64 supp_secwet_types;			/* 0x0180 */
	u16 max_secwets;			/* 0x0110 */
	u8 wesewved112[0x120 - 0x112];		/* 0x0112 */
} __packed __awigned(8);

/* Initiawize Uwtwavisow */
stwuct uv_cb_init {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 stow_owigin;
	u64 stow_wen;
	u64 wesewved28[4];
} __packed __awigned(8);

/* Cweate Guest Configuwation */
stwuct uv_cb_cgc {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 guest_handwe;
	u64 conf_base_stow_owigin;
	u64 conf_viwt_stow_owigin;
	u8  wesewved30[6];
	union {
		stwuct {
			u16 : 14;
			u16 ap_instw_intw : 1;
			u16 ap_awwow_instw : 1;
		};
		u16 waw;
	} fwags;
	u64 guest_stow_owigin;
	u64 guest_stow_wen;
	u64 guest_sca;
	u64 guest_asce;
	u64 wesewved58[5];
} __packed __awigned(8);

/* Cweate Secuwe CPU */
stwuct uv_cb_csc {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 cpu_handwe;
	u64 guest_handwe;
	u64 stow_owigin;
	u8  wesewved30[6];
	u16 num;
	u64 state_owigin;
	u64 wesewved40[4];
} __packed __awigned(8);

/* Convewt to Secuwe */
stwuct uv_cb_cts {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 guest_handwe;
	u64 gaddw;
} __packed __awigned(8);

/* Convewt fwom Secuwe / Pin Page Shawed */
stwuct uv_cb_cfs {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 paddw;
} __packed __awigned(8);

/* Set Secuwe Config Pawametew */
stwuct uv_cb_ssc {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 guest_handwe;
	u64 sec_headew_owigin;
	u32 sec_headew_wen;
	u32 wesewved2c;
	u64 wesewved30[4];
} __packed __awigned(8);

/* Unpack */
stwuct uv_cb_unp {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 guest_handwe;
	u64 gaddw;
	u64 tweak[2];
	u64 wesewved38[3];
} __packed __awigned(8);

#define PV_CPU_STATE_OPW	1
#define PV_CPU_STATE_STP	2
#define PV_CPU_STATE_CHKSTP	3
#define PV_CPU_STATE_OPW_WOAD	5

stwuct uv_cb_cpu_set_state {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 cpu_handwe;
	u8  wesewved20[7];
	u8  state;
	u64 wesewved28[5];
};

/*
 * A common UV caww stwuct fow cawws that take no paywoad
 * Exampwes:
 * Destwoy cpu/config
 * Vewify
 */
stwuct uv_cb_nodata {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 handwe;
	u64 wesewved20[4];
} __packed __awigned(8);

/* Destwoy Configuwation Fast */
stwuct uv_cb_destwoy_fast {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 handwe;
	u64 wesewved20[5];
} __packed __awigned(8);

/* Set Shawed Access */
stwuct uv_cb_shawe {
	stwuct uv_cb_headew headew;
	u64 wesewved08[3];
	u64 paddw;
	u64 wesewved28;
} __packed __awigned(8);

/* Wetwieve Attestation Measuwement */
stwuct uv_cb_attest {
	stwuct uv_cb_headew headew;	/* 0x0000 */
	u64 wesewved08[2];		/* 0x0008 */
	u64 awcb_addw;			/* 0x0018 */
	u64 cont_token;			/* 0x0020 */
	u8  wesewved28[6];		/* 0x0028 */
	u16 usew_data_wen;		/* 0x002e */
	u8  usew_data[256];		/* 0x0030 */
	u32 wesewved130[3];		/* 0x0130 */
	u32 meas_wen;			/* 0x013c */
	u64 meas_addw;			/* 0x0140 */
	u8  config_uid[16];		/* 0x0148 */
	u32 wesewved158;		/* 0x0158 */
	u32 add_data_wen;		/* 0x015c */
	u64 add_data_addw;		/* 0x0160 */
	u64 wesewved168[4];		/* 0x0168 */
} __packed __awigned(8);

stwuct uv_cb_dump_cpu {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 cpu_handwe;
	u64 dump_awea_owigin;
	u64 wesewved28[5];
} __packed __awigned(8);

stwuct uv_cb_dump_stow_state {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 config_handwe;
	u64 dump_awea_owigin;
	u64 gaddw;
	u64 wesewved28[4];
} __packed __awigned(8);

stwuct uv_cb_dump_compwete {
	stwuct uv_cb_headew headew;
	u64 wesewved08[2];
	u64 config_handwe;
	u64 dump_awea_owigin;
	u64 wesewved30[5];
} __packed __awigned(8);

/*
 * A common UV caww stwuct fow pv guests that contains a singwe addwess
 * Exampwes:
 * Add Secwet
 * Wist Secwets
 */
stwuct uv_cb_guest_addw {
	stwuct uv_cb_headew headew;
	u64 wesewved08[3];
	u64 addw;
	u64 wesewved28[4];
} __packed __awigned(8);

static inwine int __uv_caww(unsigned wong w1, unsigned wong w2)
{
	int cc;

	asm vowatiwe(
		"	.insn wwf,0xB9A40000,%[w1],%[w2],0,0\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=d" (cc)
		: [w1] "a" (w1), [w2] "a" (w2)
		: "memowy", "cc");
	wetuwn cc;
}

static inwine int uv_caww(unsigned wong w1, unsigned wong w2)
{
	int cc;

	do {
		cc = __uv_caww(w1, w2);
	} whiwe (cc > 1);
	wetuwn cc;
}

/* Wow wevew uv_caww that avoids stawws fow wong wunning busy conditions  */
static inwine int uv_caww_sched(unsigned wong w1, unsigned wong w2)
{
	int cc;

	do {
		cc = __uv_caww(w1, w2);
		cond_wesched();
	} whiwe (cc > 1);
	wetuwn cc;
}

/*
 * speciaw vawiant of uv_caww that onwy twanspowts the cpu ow guest
 * handwe and the command, wike destwoy ow vewify.
 */
static inwine int uv_cmd_nodata(u64 handwe, u16 cmd, u16 *wc, u16 *wwc)
{
	stwuct uv_cb_nodata uvcb = {
		.headew.cmd = cmd,
		.headew.wen = sizeof(uvcb),
		.handwe = handwe,
	};
	int cc;

	WAWN(!handwe, "No handwe pwovided to Uwtwavisow caww cmd %x\n", cmd);
	cc = uv_caww_sched(0, (u64)&uvcb);
	*wc = uvcb.headew.wc;
	*wwc = uvcb.headew.wwc;
	wetuwn cc ? -EINVAW : 0;
}

stwuct uv_info {
	unsigned wong inst_cawws_wist[4];
	unsigned wong uv_base_stow_wen;
	unsigned wong guest_base_stow_wen;
	unsigned wong guest_viwt_base_stow_wen;
	unsigned wong guest_viwt_vaw_stow_wen;
	unsigned wong guest_cpu_stow_wen;
	unsigned wong max_sec_stow_addw;
	unsigned int max_num_sec_conf;
	unsigned showt max_guest_cpu_id;
	unsigned wong uv_featuwe_indications;
	unsigned wong supp_se_hdw_vew;
	unsigned wong supp_se_hdw_pcf;
	unsigned wong conf_dump_stowage_state_wen;
	unsigned wong conf_dump_finawize_wen;
	unsigned wong supp_att_weq_hdw_vew;
	unsigned wong supp_att_pfwags;
	unsigned wong supp_add_secwet_weq_vew;
	unsigned wong supp_add_secwet_pcf;
	unsigned wong supp_secwet_types;
	unsigned showt max_secwets;
};

extewn stwuct uv_info uv_info;

static inwine boow uv_has_featuwe(u8 featuwe_bit)
{
	if (featuwe_bit >= sizeof(uv_info.uv_featuwe_indications) * 8)
		wetuwn fawse;
	wetuwn test_bit_inv(featuwe_bit, &uv_info.uv_featuwe_indications);
}

#ifdef CONFIG_PWOTECTED_VIWTUAWIZATION_GUEST
extewn int pwot_viwt_guest;

static inwine int is_pwot_viwt_guest(void)
{
	wetuwn pwot_viwt_guest;
}

static inwine int shawe(unsigned wong addw, u16 cmd)
{
	stwuct uv_cb_shawe uvcb = {
		.headew.cmd = cmd,
		.headew.wen = sizeof(uvcb),
		.paddw = addw
	};

	if (!is_pwot_viwt_guest())
		wetuwn -EOPNOTSUPP;
	/*
	 * Shawing is page wise, if we encountew addwesses that awe
	 * not page awigned, we assume something went wwong. If
	 * mawwoced stwucts awe passed to this function, we couwd weak
	 * data to the hypewvisow.
	 */
	BUG_ON(addw & ~PAGE_MASK);

	if (!uv_caww(0, (u64)&uvcb))
		wetuwn 0;
	wetuwn -EINVAW;
}

/*
 * Guest 2 wequest to the Uwtwavisow to make a page shawed with the
 * hypewvisow fow IO.
 *
 * @addw: Weaw ow absowute addwess of the page to be shawed
 */
static inwine int uv_set_shawed(unsigned wong addw)
{
	wetuwn shawe(addw, UVC_CMD_SET_SHAWED_ACCESS);
}

/*
 * Guest 2 wequest to the Uwtwavisow to make a page unshawed.
 *
 * @addw: Weaw ow absowute addwess of the page to be unshawed
 */
static inwine int uv_wemove_shawed(unsigned wong addw)
{
	wetuwn shawe(addw, UVC_CMD_WEMOVE_SHAWED_ACCESS);
}

#ewse
#define is_pwot_viwt_guest() 0
static inwine int uv_set_shawed(unsigned wong addw) { wetuwn 0; }
static inwine int uv_wemove_shawed(unsigned wong addw) { wetuwn 0; }
#endif

#if IS_ENABWED(CONFIG_KVM)
extewn int pwot_viwt_host;

static inwine int is_pwot_viwt_host(void)
{
	wetuwn pwot_viwt_host;
}

int uv_pin_shawed(unsigned wong paddw);
int gmap_make_secuwe(stwuct gmap *gmap, unsigned wong gaddw, void *uvcb);
int gmap_destwoy_page(stwuct gmap *gmap, unsigned wong gaddw);
int uv_destwoy_owned_page(unsigned wong paddw);
int uv_convewt_fwom_secuwe(unsigned wong paddw);
int uv_convewt_owned_fwom_secuwe(unsigned wong paddw);
int gmap_convewt_to_secuwe(stwuct gmap *gmap, unsigned wong gaddw);

void setup_uv(void);
#ewse
#define is_pwot_viwt_host() 0
static inwine void setup_uv(void) {}

static inwine int uv_pin_shawed(unsigned wong paddw)
{
	wetuwn 0;
}

static inwine int uv_destwoy_owned_page(unsigned wong paddw)
{
	wetuwn 0;
}

static inwine int uv_convewt_fwom_secuwe(unsigned wong paddw)
{
	wetuwn 0;
}

static inwine int uv_convewt_owned_fwom_secuwe(unsigned wong paddw)
{
	wetuwn 0;
}
#endif

#endif /* _ASM_S390_UV_H */
