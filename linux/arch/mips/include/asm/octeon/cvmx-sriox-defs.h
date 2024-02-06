/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2012 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this fiwe; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA
 * ow visit http://www.gnu.owg/wicenses/.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium Netwowks fow mowe infowmation
 ***********************wicense end**************************************/

#ifndef __CVMX_SWIOX_DEFS_H__
#define __CVMX_SWIOX_DEFS_H__

#define CVMX_SWIOX_ACC_CTWW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000148uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_ASMBWY_ID(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000200uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_ASMBWY_INFO(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000208uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_BEWW_WESP_CTWW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000310uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_BIST_STATUS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000108uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_IMSG_CTWW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000508uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_IMSG_INST_HDWX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000510uww) + (((offset) & 1) + ((bwock_id) & 3) * 0x200000uww) * 8)
#define CVMX_SWIOX_IMSG_QOS_GWPX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000600uww) + (((offset) & 31) + ((bwock_id) & 3) * 0x200000uww) * 8)
#define CVMX_SWIOX_IMSG_STATUSX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000700uww) + (((offset) & 31) + ((bwock_id) & 3) * 0x200000uww) * 8)
#define CVMX_SWIOX_IMSG_VPOWT_THW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000500uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_IMSG_VPOWT_THW2(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000528uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_INT2_ENABWE(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C80003E0uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_INT2_WEG(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C80003E8uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_INT_ENABWE(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000110uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_INT_INFO0(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000120uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_INT_INFO1(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000128uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_INT_INFO2(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000130uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_INT_INFO3(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000138uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_INT_WEG(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000118uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_IP_FEATUWE(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C80003F8uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_MAC_BUFFEWS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000390uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_MAINT_OP(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000158uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_MAINT_WD_DATA(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000160uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_MCE_TX_CTW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000240uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_MEM_OP_CTWW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000168uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_OMSG_CTWWX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000488uww) + (((offset) & 1) + ((bwock_id) & 3) * 0x40000uww) * 64)
#define CVMX_SWIOX_OMSG_DONE_COUNTSX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C80004B0uww) + (((offset) & 1) + ((bwock_id) & 3) * 0x40000uww) * 64)
#define CVMX_SWIOX_OMSG_FMP_MWX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000498uww) + (((offset) & 1) + ((bwock_id) & 3) * 0x40000uww) * 64)
#define CVMX_SWIOX_OMSG_NMP_MWX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C80004A0uww) + (((offset) & 1) + ((bwock_id) & 3) * 0x40000uww) * 64)
#define CVMX_SWIOX_OMSG_POWTX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000480uww) + (((offset) & 1) + ((bwock_id) & 3) * 0x40000uww) * 64)
#define CVMX_SWIOX_OMSG_SIWO_THW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C80004F8uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_OMSG_SP_MWX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000490uww) + (((offset) & 1) + ((bwock_id) & 3) * 0x40000uww) * 64)
#define CVMX_SWIOX_PWIOX_IN_USE(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C80003C0uww) + (((offset) & 3) + ((bwock_id) & 3) * 0x200000uww) * 8)
#define CVMX_SWIOX_WX_BEWW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000308uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_WX_BEWW_SEQ(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000300uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_WX_STATUS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000380uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_S2M_TYPEX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000180uww) + (((offset) & 15) + ((bwock_id) & 3) * 0x200000uww) * 8)
#define CVMX_SWIOX_SEQ(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000278uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_STATUS_WEG(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000100uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_TAG_CTWW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000178uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_TWP_CWEDITS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000150uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_TX_BEWW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000280uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_TX_BEWW_INFO(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000288uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_TX_CTWW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000170uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_TX_EMPHASIS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C80003F0uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_TX_STATUS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000388uww) + ((bwock_id) & 3) * 0x1000000uww)
#define CVMX_SWIOX_WW_DONE_COUNTS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C8000340uww) + ((bwock_id) & 3) * 0x1000000uww)

union cvmx_swiox_acc_ctww {
	uint64_t u64;
	stwuct cvmx_swiox_acc_ctww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t deny_adw2:1;
		uint64_t deny_adw1:1;
		uint64_t deny_adw0:1;
		uint64_t wesewved_3_3:1;
		uint64_t deny_baw2:1;
		uint64_t deny_baw1:1;
		uint64_t deny_baw0:1;
#ewse
		uint64_t deny_baw0:1;
		uint64_t deny_baw1:1;
		uint64_t deny_baw2:1;
		uint64_t wesewved_3_3:1;
		uint64_t deny_adw0:1;
		uint64_t deny_adw1:1;
		uint64_t deny_adw2:1;
		uint64_t wesewved_7_63:57;
#endif
	} s;
	stwuct cvmx_swiox_acc_ctww_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t deny_baw2:1;
		uint64_t deny_baw1:1;
		uint64_t deny_baw0:1;
#ewse
		uint64_t deny_baw0:1;
		uint64_t deny_baw1:1;
		uint64_t deny_baw2:1;
		uint64_t wesewved_3_63:61;
#endif
	} cn63xx;
};

union cvmx_swiox_asmbwy_id {
	uint64_t u64;
	stwuct cvmx_swiox_asmbwy_id_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t assy_id:16;
		uint64_t assy_ven:16;
#ewse
		uint64_t assy_ven:16;
		uint64_t assy_id:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_swiox_asmbwy_info {
	uint64_t u64;
	stwuct cvmx_swiox_asmbwy_info_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t assy_wev:16;
		uint64_t wesewved_0_15:16;
#ewse
		uint64_t wesewved_0_15:16;
		uint64_t assy_wev:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_swiox_beww_wesp_ctww {
	uint64_t u64;
	stwuct cvmx_swiox_beww_wesp_ctww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t wp1_sid:1;
		uint64_t wp0_sid:2;
		uint64_t wp1_pid:1;
		uint64_t wp0_pid:2;
#ewse
		uint64_t wp0_pid:2;
		uint64_t wp1_pid:1;
		uint64_t wp0_sid:2;
		uint64_t wp1_sid:1;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_swiox_bist_status {
	uint64_t u64;
	stwuct cvmx_swiox_bist_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_45_63:19;
		uint64_t wwam:1;
		uint64_t mwam:2;
		uint64_t cwam:2;
		uint64_t beww:2;
		uint64_t otag:2;
		uint64_t itag:1;
		uint64_t ofwee:1;
		uint64_t wtn:2;
		uint64_t obuwk:4;
		uint64_t optws:4;
		uint64_t oawb2:2;
		uint64_t wxbuf2:2;
		uint64_t oawb:2;
		uint64_t ispf:1;
		uint64_t ospf:1;
		uint64_t txbuf:2;
		uint64_t wxbuf:2;
		uint64_t imsg:5;
		uint64_t omsg:7;
#ewse
		uint64_t omsg:7;
		uint64_t imsg:5;
		uint64_t wxbuf:2;
		uint64_t txbuf:2;
		uint64_t ospf:1;
		uint64_t ispf:1;
		uint64_t oawb:2;
		uint64_t wxbuf2:2;
		uint64_t oawb2:2;
		uint64_t optws:4;
		uint64_t obuwk:4;
		uint64_t wtn:2;
		uint64_t ofwee:1;
		uint64_t itag:1;
		uint64_t otag:2;
		uint64_t beww:2;
		uint64_t cwam:2;
		uint64_t mwam:2;
		uint64_t wwam:1;
		uint64_t wesewved_45_63:19;
#endif
	} s;
	stwuct cvmx_swiox_bist_status_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t mwam:2;
		uint64_t cwam:2;
		uint64_t beww:2;
		uint64_t otag:2;
		uint64_t itag:1;
		uint64_t ofwee:1;
		uint64_t wtn:2;
		uint64_t obuwk:4;
		uint64_t optws:4;
		uint64_t oawb2:2;
		uint64_t wxbuf2:2;
		uint64_t oawb:2;
		uint64_t ispf:1;
		uint64_t ospf:1;
		uint64_t txbuf:2;
		uint64_t wxbuf:2;
		uint64_t imsg:5;
		uint64_t omsg:7;
#ewse
		uint64_t omsg:7;
		uint64_t imsg:5;
		uint64_t wxbuf:2;
		uint64_t txbuf:2;
		uint64_t ospf:1;
		uint64_t ispf:1;
		uint64_t oawb:2;
		uint64_t wxbuf2:2;
		uint64_t oawb2:2;
		uint64_t optws:4;
		uint64_t obuwk:4;
		uint64_t wtn:2;
		uint64_t ofwee:1;
		uint64_t itag:1;
		uint64_t otag:2;
		uint64_t beww:2;
		uint64_t cwam:2;
		uint64_t mwam:2;
		uint64_t wesewved_44_63:20;
#endif
	} cn63xx;
	stwuct cvmx_swiox_bist_status_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t mwam:2;
		uint64_t cwam:2;
		uint64_t beww:2;
		uint64_t otag:2;
		uint64_t itag:1;
		uint64_t ofwee:1;
		uint64_t wtn:2;
		uint64_t obuwk:4;
		uint64_t optws:4;
		uint64_t wesewved_20_23:4;
		uint64_t oawb:2;
		uint64_t ispf:1;
		uint64_t ospf:1;
		uint64_t txbuf:2;
		uint64_t wxbuf:2;
		uint64_t imsg:5;
		uint64_t omsg:7;
#ewse
		uint64_t omsg:7;
		uint64_t imsg:5;
		uint64_t wxbuf:2;
		uint64_t txbuf:2;
		uint64_t ospf:1;
		uint64_t ispf:1;
		uint64_t oawb:2;
		uint64_t wesewved_20_23:4;
		uint64_t optws:4;
		uint64_t obuwk:4;
		uint64_t wtn:2;
		uint64_t ofwee:1;
		uint64_t itag:1;
		uint64_t otag:2;
		uint64_t beww:2;
		uint64_t cwam:2;
		uint64_t mwam:2;
		uint64_t wesewved_44_63:20;
#endif
	} cn63xxp1;
};

union cvmx_swiox_imsg_ctww {
	uint64_t u64;
	stwuct cvmx_swiox_imsg_ctww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t to_mode:1;
		uint64_t wesewved_30_30:1;
		uint64_t wsp_thw:6;
		uint64_t wesewved_22_23:2;
		uint64_t wp1_sid:1;
		uint64_t wp0_sid:2;
		uint64_t wp1_pid:1;
		uint64_t wp0_pid:2;
		uint64_t wesewved_15_15:1;
		uint64_t pwt_sew:3;
		uint64_t wttw:4;
		uint64_t pwio:4;
		uint64_t mbox:4;
#ewse
		uint64_t mbox:4;
		uint64_t pwio:4;
		uint64_t wttw:4;
		uint64_t pwt_sew:3;
		uint64_t wesewved_15_15:1;
		uint64_t wp0_pid:2;
		uint64_t wp1_pid:1;
		uint64_t wp0_sid:2;
		uint64_t wp1_sid:1;
		uint64_t wesewved_22_23:2;
		uint64_t wsp_thw:6;
		uint64_t wesewved_30_30:1;
		uint64_t to_mode:1;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_swiox_imsg_inst_hdwx {
	uint64_t u64;
	stwuct cvmx_swiox_imsg_inst_hdwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t w:1;
		uint64_t wesewved_58_62:5;
		uint64_t pm:2;
		uint64_t wesewved_55_55:1;
		uint64_t sw:7;
		uint64_t wesewved_46_47:2;
		uint64_t nqos:1;
		uint64_t ngwp:1;
		uint64_t ntt:1;
		uint64_t ntag:1;
		uint64_t wesewved_35_41:7;
		uint64_t ws:1;
		uint64_t tt:2;
		uint64_t tag:32;
#ewse
		uint64_t tag:32;
		uint64_t tt:2;
		uint64_t ws:1;
		uint64_t wesewved_35_41:7;
		uint64_t ntag:1;
		uint64_t ntt:1;
		uint64_t ngwp:1;
		uint64_t nqos:1;
		uint64_t wesewved_46_47:2;
		uint64_t sw:7;
		uint64_t wesewved_55_55:1;
		uint64_t pm:2;
		uint64_t wesewved_58_62:5;
		uint64_t w:1;
#endif
	} s;
};

union cvmx_swiox_imsg_qos_gwpx {
	uint64_t u64;
	stwuct cvmx_swiox_imsg_qos_gwpx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_63_63:1;
		uint64_t qos7:3;
		uint64_t gwp7:4;
		uint64_t wesewved_55_55:1;
		uint64_t qos6:3;
		uint64_t gwp6:4;
		uint64_t wesewved_47_47:1;
		uint64_t qos5:3;
		uint64_t gwp5:4;
		uint64_t wesewved_39_39:1;
		uint64_t qos4:3;
		uint64_t gwp4:4;
		uint64_t wesewved_31_31:1;
		uint64_t qos3:3;
		uint64_t gwp3:4;
		uint64_t wesewved_23_23:1;
		uint64_t qos2:3;
		uint64_t gwp2:4;
		uint64_t wesewved_15_15:1;
		uint64_t qos1:3;
		uint64_t gwp1:4;
		uint64_t wesewved_7_7:1;
		uint64_t qos0:3;
		uint64_t gwp0:4;
#ewse
		uint64_t gwp0:4;
		uint64_t qos0:3;
		uint64_t wesewved_7_7:1;
		uint64_t gwp1:4;
		uint64_t qos1:3;
		uint64_t wesewved_15_15:1;
		uint64_t gwp2:4;
		uint64_t qos2:3;
		uint64_t wesewved_23_23:1;
		uint64_t gwp3:4;
		uint64_t qos3:3;
		uint64_t wesewved_31_31:1;
		uint64_t gwp4:4;
		uint64_t qos4:3;
		uint64_t wesewved_39_39:1;
		uint64_t gwp5:4;
		uint64_t qos5:3;
		uint64_t wesewved_47_47:1;
		uint64_t gwp6:4;
		uint64_t qos6:3;
		uint64_t wesewved_55_55:1;
		uint64_t gwp7:4;
		uint64_t qos7:3;
		uint64_t wesewved_63_63:1;
#endif
	} s;
};

union cvmx_swiox_imsg_statusx {
	uint64_t u64;
	stwuct cvmx_swiox_imsg_statusx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t vaw1:1;
		uint64_t eww1:1;
		uint64_t toe1:1;
		uint64_t toc1:1;
		uint64_t pwt1:1;
		uint64_t wesewved_58_58:1;
		uint64_t tt1:1;
		uint64_t dis1:1;
		uint64_t seg1:4;
		uint64_t mbox1:2;
		uint64_t wttw1:2;
		uint64_t sid1:16;
		uint64_t vaw0:1;
		uint64_t eww0:1;
		uint64_t toe0:1;
		uint64_t toc0:1;
		uint64_t pwt0:1;
		uint64_t wesewved_26_26:1;
		uint64_t tt0:1;
		uint64_t dis0:1;
		uint64_t seg0:4;
		uint64_t mbox0:2;
		uint64_t wttw0:2;
		uint64_t sid0:16;
#ewse
		uint64_t sid0:16;
		uint64_t wttw0:2;
		uint64_t mbox0:2;
		uint64_t seg0:4;
		uint64_t dis0:1;
		uint64_t tt0:1;
		uint64_t wesewved_26_26:1;
		uint64_t pwt0:1;
		uint64_t toc0:1;
		uint64_t toe0:1;
		uint64_t eww0:1;
		uint64_t vaw0:1;
		uint64_t sid1:16;
		uint64_t wttw1:2;
		uint64_t mbox1:2;
		uint64_t seg1:4;
		uint64_t dis1:1;
		uint64_t tt1:1;
		uint64_t wesewved_58_58:1;
		uint64_t pwt1:1;
		uint64_t toc1:1;
		uint64_t toe1:1;
		uint64_t eww1:1;
		uint64_t vaw1:1;
#endif
	} s;
};

union cvmx_swiox_imsg_vpowt_thw {
	uint64_t u64;
	stwuct cvmx_swiox_imsg_vpowt_thw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_54_63:10;
		uint64_t max_tot:6;
		uint64_t wesewved_46_47:2;
		uint64_t max_s1:6;
		uint64_t wesewved_38_39:2;
		uint64_t max_s0:6;
		uint64_t sp_vpowt:1;
		uint64_t wesewved_20_30:11;
		uint64_t buf_thw:4;
		uint64_t wesewved_14_15:2;
		uint64_t max_p1:6;
		uint64_t wesewved_6_7:2;
		uint64_t max_p0:6;
#ewse
		uint64_t max_p0:6;
		uint64_t wesewved_6_7:2;
		uint64_t max_p1:6;
		uint64_t wesewved_14_15:2;
		uint64_t buf_thw:4;
		uint64_t wesewved_20_30:11;
		uint64_t sp_vpowt:1;
		uint64_t max_s0:6;
		uint64_t wesewved_38_39:2;
		uint64_t max_s1:6;
		uint64_t wesewved_46_47:2;
		uint64_t max_tot:6;
		uint64_t wesewved_54_63:10;
#endif
	} s;
};

union cvmx_swiox_imsg_vpowt_thw2 {
	uint64_t u64;
	stwuct cvmx_swiox_imsg_vpowt_thw2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_46_63:18;
		uint64_t max_s3:6;
		uint64_t wesewved_38_39:2;
		uint64_t max_s2:6;
		uint64_t wesewved_0_31:32;
#ewse
		uint64_t wesewved_0_31:32;
		uint64_t max_s2:6;
		uint64_t wesewved_38_39:2;
		uint64_t max_s3:6;
		uint64_t wesewved_46_63:18;
#endif
	} s;
};

union cvmx_swiox_int2_enabwe {
	uint64_t u64;
	stwuct cvmx_swiox_int2_enabwe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t pko_wst:1;
#ewse
		uint64_t pko_wst:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_swiox_int2_weg {
	uint64_t u64;
	stwuct cvmx_swiox_int2_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t int_sum:1;
		uint64_t wesewved_1_30:30;
		uint64_t pko_wst:1;
#ewse
		uint64_t pko_wst:1;
		uint64_t wesewved_1_30:30;
		uint64_t int_sum:1;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_swiox_int_enabwe {
	uint64_t u64;
	stwuct cvmx_swiox_int_enabwe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_27_63:37;
		uint64_t zewo_pkt:1;
		uint64_t ttw_tout:1;
		uint64_t faiw:1;
		uint64_t degwade:1;
		uint64_t mac_buf:1;
		uint64_t f_ewwow:1;
		uint64_t wtwy_eww:1;
		uint64_t pko_eww:1;
		uint64_t omsg_eww:1;
		uint64_t omsg1:1;
		uint64_t omsg0:1;
		uint64_t wink_up:1;
		uint64_t wink_dwn:1;
		uint64_t phy_ewb:1;
		uint64_t wog_ewb:1;
		uint64_t soft_wx:1;
		uint64_t soft_tx:1;
		uint64_t mce_wx:1;
		uint64_t mce_tx:1;
		uint64_t ww_done:1;
		uint64_t swi_eww:1;
		uint64_t deny_ww:1;
		uint64_t baw_eww:1;
		uint64_t maint_op:1;
		uint64_t wxbeww:1;
		uint64_t beww_eww:1;
		uint64_t txbeww:1;
#ewse
		uint64_t txbeww:1;
		uint64_t beww_eww:1;
		uint64_t wxbeww:1;
		uint64_t maint_op:1;
		uint64_t baw_eww:1;
		uint64_t deny_ww:1;
		uint64_t swi_eww:1;
		uint64_t ww_done:1;
		uint64_t mce_tx:1;
		uint64_t mce_wx:1;
		uint64_t soft_tx:1;
		uint64_t soft_wx:1;
		uint64_t wog_ewb:1;
		uint64_t phy_ewb:1;
		uint64_t wink_dwn:1;
		uint64_t wink_up:1;
		uint64_t omsg0:1;
		uint64_t omsg1:1;
		uint64_t omsg_eww:1;
		uint64_t pko_eww:1;
		uint64_t wtwy_eww:1;
		uint64_t f_ewwow:1;
		uint64_t mac_buf:1;
		uint64_t degwade:1;
		uint64_t faiw:1;
		uint64_t ttw_tout:1;
		uint64_t zewo_pkt:1;
		uint64_t wesewved_27_63:37;
#endif
	} s;
	stwuct cvmx_swiox_int_enabwe_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t f_ewwow:1;
		uint64_t wtwy_eww:1;
		uint64_t pko_eww:1;
		uint64_t omsg_eww:1;
		uint64_t omsg1:1;
		uint64_t omsg0:1;
		uint64_t wink_up:1;
		uint64_t wink_dwn:1;
		uint64_t phy_ewb:1;
		uint64_t wog_ewb:1;
		uint64_t soft_wx:1;
		uint64_t soft_tx:1;
		uint64_t mce_wx:1;
		uint64_t mce_tx:1;
		uint64_t ww_done:1;
		uint64_t swi_eww:1;
		uint64_t deny_ww:1;
		uint64_t baw_eww:1;
		uint64_t maint_op:1;
		uint64_t wxbeww:1;
		uint64_t beww_eww:1;
		uint64_t txbeww:1;
#ewse
		uint64_t txbeww:1;
		uint64_t beww_eww:1;
		uint64_t wxbeww:1;
		uint64_t maint_op:1;
		uint64_t baw_eww:1;
		uint64_t deny_ww:1;
		uint64_t swi_eww:1;
		uint64_t ww_done:1;
		uint64_t mce_tx:1;
		uint64_t mce_wx:1;
		uint64_t soft_tx:1;
		uint64_t soft_wx:1;
		uint64_t wog_ewb:1;
		uint64_t phy_ewb:1;
		uint64_t wink_dwn:1;
		uint64_t wink_up:1;
		uint64_t omsg0:1;
		uint64_t omsg1:1;
		uint64_t omsg_eww:1;
		uint64_t pko_eww:1;
		uint64_t wtwy_eww:1;
		uint64_t f_ewwow:1;
		uint64_t wesewved_22_63:42;
#endif
	} cn63xxp1;
};

union cvmx_swiox_int_info0 {
	uint64_t u64;
	stwuct cvmx_swiox_int_info0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t cmd:4;
		uint64_t type:4;
		uint64_t tag:8;
		uint64_t wesewved_42_47:6;
		uint64_t wength:10;
		uint64_t status:3;
		uint64_t wesewved_16_28:13;
		uint64_t be0:8;
		uint64_t be1:8;
#ewse
		uint64_t be1:8;
		uint64_t be0:8;
		uint64_t wesewved_16_28:13;
		uint64_t status:3;
		uint64_t wength:10;
		uint64_t wesewved_42_47:6;
		uint64_t tag:8;
		uint64_t type:4;
		uint64_t cmd:4;
#endif
	} s;
};

union cvmx_swiox_int_info1 {
	uint64_t u64;
	stwuct cvmx_swiox_int_info1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t info1:64;
#ewse
		uint64_t info1:64;
#endif
	} s;
};

union cvmx_swiox_int_info2 {
	uint64_t u64;
	stwuct cvmx_swiox_int_info2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pwio:2;
		uint64_t tt:1;
		uint64_t sis:1;
		uint64_t ssize:4;
		uint64_t did:16;
		uint64_t xmbox:4;
		uint64_t mbox:2;
		uint64_t wettew:2;
		uint64_t wswvd:30;
		uint64_t wns:1;
		uint64_t intw:1;
#ewse
		uint64_t intw:1;
		uint64_t wns:1;
		uint64_t wswvd:30;
		uint64_t wettew:2;
		uint64_t mbox:2;
		uint64_t xmbox:4;
		uint64_t did:16;
		uint64_t ssize:4;
		uint64_t sis:1;
		uint64_t tt:1;
		uint64_t pwio:2;
#endif
	} s;
};

union cvmx_swiox_int_info3 {
	uint64_t u64;
	stwuct cvmx_swiox_int_info3_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pwio:2;
		uint64_t tt:2;
		uint64_t type:4;
		uint64_t othew:48;
		uint64_t wesewved_0_7:8;
#ewse
		uint64_t wesewved_0_7:8;
		uint64_t othew:48;
		uint64_t type:4;
		uint64_t tt:2;
		uint64_t pwio:2;
#endif
	} s;
};

union cvmx_swiox_int_weg {
	uint64_t u64;
	stwuct cvmx_swiox_int_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t int2_sum:1;
		uint64_t wesewved_27_30:4;
		uint64_t zewo_pkt:1;
		uint64_t ttw_tout:1;
		uint64_t faiw:1;
		uint64_t degwad:1;
		uint64_t mac_buf:1;
		uint64_t f_ewwow:1;
		uint64_t wtwy_eww:1;
		uint64_t pko_eww:1;
		uint64_t omsg_eww:1;
		uint64_t omsg1:1;
		uint64_t omsg0:1;
		uint64_t wink_up:1;
		uint64_t wink_dwn:1;
		uint64_t phy_ewb:1;
		uint64_t wog_ewb:1;
		uint64_t soft_wx:1;
		uint64_t soft_tx:1;
		uint64_t mce_wx:1;
		uint64_t mce_tx:1;
		uint64_t ww_done:1;
		uint64_t swi_eww:1;
		uint64_t deny_ww:1;
		uint64_t baw_eww:1;
		uint64_t maint_op:1;
		uint64_t wxbeww:1;
		uint64_t beww_eww:1;
		uint64_t txbeww:1;
#ewse
		uint64_t txbeww:1;
		uint64_t beww_eww:1;
		uint64_t wxbeww:1;
		uint64_t maint_op:1;
		uint64_t baw_eww:1;
		uint64_t deny_ww:1;
		uint64_t swi_eww:1;
		uint64_t ww_done:1;
		uint64_t mce_tx:1;
		uint64_t mce_wx:1;
		uint64_t soft_tx:1;
		uint64_t soft_wx:1;
		uint64_t wog_ewb:1;
		uint64_t phy_ewb:1;
		uint64_t wink_dwn:1;
		uint64_t wink_up:1;
		uint64_t omsg0:1;
		uint64_t omsg1:1;
		uint64_t omsg_eww:1;
		uint64_t pko_eww:1;
		uint64_t wtwy_eww:1;
		uint64_t f_ewwow:1;
		uint64_t mac_buf:1;
		uint64_t degwad:1;
		uint64_t faiw:1;
		uint64_t ttw_tout:1;
		uint64_t zewo_pkt:1;
		uint64_t wesewved_27_30:4;
		uint64_t int2_sum:1;
		uint64_t wesewved_32_63:32;
#endif
	} s;
	stwuct cvmx_swiox_int_weg_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t f_ewwow:1;
		uint64_t wtwy_eww:1;
		uint64_t pko_eww:1;
		uint64_t omsg_eww:1;
		uint64_t omsg1:1;
		uint64_t omsg0:1;
		uint64_t wink_up:1;
		uint64_t wink_dwn:1;
		uint64_t phy_ewb:1;
		uint64_t wog_ewb:1;
		uint64_t soft_wx:1;
		uint64_t soft_tx:1;
		uint64_t mce_wx:1;
		uint64_t mce_tx:1;
		uint64_t ww_done:1;
		uint64_t swi_eww:1;
		uint64_t deny_ww:1;
		uint64_t baw_eww:1;
		uint64_t maint_op:1;
		uint64_t wxbeww:1;
		uint64_t beww_eww:1;
		uint64_t txbeww:1;
#ewse
		uint64_t txbeww:1;
		uint64_t beww_eww:1;
		uint64_t wxbeww:1;
		uint64_t maint_op:1;
		uint64_t baw_eww:1;
		uint64_t deny_ww:1;
		uint64_t swi_eww:1;
		uint64_t ww_done:1;
		uint64_t mce_tx:1;
		uint64_t mce_wx:1;
		uint64_t soft_tx:1;
		uint64_t soft_wx:1;
		uint64_t wog_ewb:1;
		uint64_t phy_ewb:1;
		uint64_t wink_dwn:1;
		uint64_t wink_up:1;
		uint64_t omsg0:1;
		uint64_t omsg1:1;
		uint64_t omsg_eww:1;
		uint64_t pko_eww:1;
		uint64_t wtwy_eww:1;
		uint64_t f_ewwow:1;
		uint64_t wesewved_22_63:42;
#endif
	} cn63xxp1;
};

union cvmx_swiox_ip_featuwe {
	uint64_t u64;
	stwuct cvmx_swiox_ip_featuwe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ops:32;
		uint64_t wesewved_15_31:17;
		uint64_t no_vmin:1;
		uint64_t a66:1;
		uint64_t a50:1;
		uint64_t wesewved_11_11:1;
		uint64_t tx_fwow:1;
		uint64_t pt_width:2;
		uint64_t tx_pow:4;
		uint64_t wx_pow:4;
#ewse
		uint64_t wx_pow:4;
		uint64_t tx_pow:4;
		uint64_t pt_width:2;
		uint64_t tx_fwow:1;
		uint64_t wesewved_11_11:1;
		uint64_t a50:1;
		uint64_t a66:1;
		uint64_t no_vmin:1;
		uint64_t wesewved_15_31:17;
		uint64_t ops:32;
#endif
	} s;
	stwuct cvmx_swiox_ip_featuwe_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ops:32;
		uint64_t wesewved_14_31:18;
		uint64_t a66:1;
		uint64_t a50:1;
		uint64_t wesewved_11_11:1;
		uint64_t tx_fwow:1;
		uint64_t pt_width:2;
		uint64_t tx_pow:4;
		uint64_t wx_pow:4;
#ewse
		uint64_t wx_pow:4;
		uint64_t tx_pow:4;
		uint64_t pt_width:2;
		uint64_t tx_fwow:1;
		uint64_t wesewved_11_11:1;
		uint64_t a50:1;
		uint64_t a66:1;
		uint64_t wesewved_14_31:18;
		uint64_t ops:32;
#endif
	} cn63xx;
};

union cvmx_swiox_mac_buffews {
	uint64_t u64;
	stwuct cvmx_swiox_mac_buffews_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_56_63:8;
		uint64_t tx_enb:8;
		uint64_t wesewved_44_47:4;
		uint64_t tx_inuse:4;
		uint64_t tx_stat:8;
		uint64_t wesewved_24_31:8;
		uint64_t wx_enb:8;
		uint64_t wesewved_12_15:4;
		uint64_t wx_inuse:4;
		uint64_t wx_stat:8;
#ewse
		uint64_t wx_stat:8;
		uint64_t wx_inuse:4;
		uint64_t wesewved_12_15:4;
		uint64_t wx_enb:8;
		uint64_t wesewved_24_31:8;
		uint64_t tx_stat:8;
		uint64_t tx_inuse:4;
		uint64_t wesewved_44_47:4;
		uint64_t tx_enb:8;
		uint64_t wesewved_56_63:8;
#endif
	} s;
};

union cvmx_swiox_maint_op {
	uint64_t u64;
	stwuct cvmx_swiox_maint_op_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ww_data:32;
		uint64_t wesewved_27_31:5;
		uint64_t faiw:1;
		uint64_t pending:1;
		uint64_t op:1;
		uint64_t addw:24;
#ewse
		uint64_t addw:24;
		uint64_t op:1;
		uint64_t pending:1;
		uint64_t faiw:1;
		uint64_t wesewved_27_31:5;
		uint64_t ww_data:32;
#endif
	} s;
};

union cvmx_swiox_maint_wd_data {
	uint64_t u64;
	stwuct cvmx_swiox_maint_wd_data_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_33_63:31;
		uint64_t vawid:1;
		uint64_t wd_data:32;
#ewse
		uint64_t wd_data:32;
		uint64_t vawid:1;
		uint64_t wesewved_33_63:31;
#endif
	} s;
};

union cvmx_swiox_mce_tx_ctw {
	uint64_t u64;
	stwuct cvmx_swiox_mce_tx_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t mce:1;
#ewse
		uint64_t mce:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_swiox_mem_op_ctww {
	uint64_t u64;
	stwuct cvmx_swiox_mem_op_ctww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t ww_wo:1;
		uint64_t w_wo:1;
		uint64_t wesewved_6_7:2;
		uint64_t wp1_sid:1;
		uint64_t wp0_sid:2;
		uint64_t wp1_pid:1;
		uint64_t wp0_pid:2;
#ewse
		uint64_t wp0_pid:2;
		uint64_t wp1_pid:1;
		uint64_t wp0_sid:2;
		uint64_t wp1_sid:1;
		uint64_t wesewved_6_7:2;
		uint64_t w_wo:1;
		uint64_t ww_wo:1;
		uint64_t wesewved_10_63:54;
#endif
	} s;
};

union cvmx_swiox_omsg_ctwwx {
	uint64_t u64;
	stwuct cvmx_swiox_omsg_ctwwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t testmode:1;
		uint64_t wesewved_37_62:26;
		uint64_t siwo_max:5;
		uint64_t wtwy_thw:16;
		uint64_t wtwy_en:1;
		uint64_t wesewved_11_14:4;
		uint64_t idm_tt:1;
		uint64_t idm_sis:1;
		uint64_t idm_did:1;
		uint64_t wttw_sp:4;
		uint64_t wttw_mp:4;
#ewse
		uint64_t wttw_mp:4;
		uint64_t wttw_sp:4;
		uint64_t idm_did:1;
		uint64_t idm_sis:1;
		uint64_t idm_tt:1;
		uint64_t wesewved_11_14:4;
		uint64_t wtwy_en:1;
		uint64_t wtwy_thw:16;
		uint64_t siwo_max:5;
		uint64_t wesewved_37_62:26;
		uint64_t testmode:1;
#endif
	} s;
	stwuct cvmx_swiox_omsg_ctwwx_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t testmode:1;
		uint64_t wesewved_32_62:31;
		uint64_t wtwy_thw:16;
		uint64_t wtwy_en:1;
		uint64_t wesewved_11_14:4;
		uint64_t idm_tt:1;
		uint64_t idm_sis:1;
		uint64_t idm_did:1;
		uint64_t wttw_sp:4;
		uint64_t wttw_mp:4;
#ewse
		uint64_t wttw_mp:4;
		uint64_t wttw_sp:4;
		uint64_t idm_did:1;
		uint64_t idm_sis:1;
		uint64_t idm_tt:1;
		uint64_t wesewved_11_14:4;
		uint64_t wtwy_en:1;
		uint64_t wtwy_thw:16;
		uint64_t wesewved_32_62:31;
		uint64_t testmode:1;
#endif
	} cn63xxp1;
};

union cvmx_swiox_omsg_done_countsx {
	uint64_t u64;
	stwuct cvmx_swiox_omsg_done_countsx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t bad:16;
		uint64_t good:16;
#ewse
		uint64_t good:16;
		uint64_t bad:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_swiox_omsg_fmp_mwx {
	uint64_t u64;
	stwuct cvmx_swiox_omsg_fmp_mwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_15_63:49;
		uint64_t ctww_sp:1;
		uint64_t ctww_fmp:1;
		uint64_t ctww_nmp:1;
		uint64_t id_sp:1;
		uint64_t id_fmp:1;
		uint64_t id_nmp:1;
		uint64_t id_psd:1;
		uint64_t mbox_sp:1;
		uint64_t mbox_fmp:1;
		uint64_t mbox_nmp:1;
		uint64_t mbox_psd:1;
		uint64_t aww_sp:1;
		uint64_t aww_fmp:1;
		uint64_t aww_nmp:1;
		uint64_t aww_psd:1;
#ewse
		uint64_t aww_psd:1;
		uint64_t aww_nmp:1;
		uint64_t aww_fmp:1;
		uint64_t aww_sp:1;
		uint64_t mbox_psd:1;
		uint64_t mbox_nmp:1;
		uint64_t mbox_fmp:1;
		uint64_t mbox_sp:1;
		uint64_t id_psd:1;
		uint64_t id_nmp:1;
		uint64_t id_fmp:1;
		uint64_t id_sp:1;
		uint64_t ctww_nmp:1;
		uint64_t ctww_fmp:1;
		uint64_t ctww_sp:1;
		uint64_t wesewved_15_63:49;
#endif
	} s;
};

union cvmx_swiox_omsg_nmp_mwx {
	uint64_t u64;
	stwuct cvmx_swiox_omsg_nmp_mwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_15_63:49;
		uint64_t ctww_sp:1;
		uint64_t ctww_fmp:1;
		uint64_t ctww_nmp:1;
		uint64_t id_sp:1;
		uint64_t id_fmp:1;
		uint64_t id_nmp:1;
		uint64_t wesewved_8_8:1;
		uint64_t mbox_sp:1;
		uint64_t mbox_fmp:1;
		uint64_t mbox_nmp:1;
		uint64_t wesewved_4_4:1;
		uint64_t aww_sp:1;
		uint64_t aww_fmp:1;
		uint64_t aww_nmp:1;
		uint64_t wesewved_0_0:1;
#ewse
		uint64_t wesewved_0_0:1;
		uint64_t aww_nmp:1;
		uint64_t aww_fmp:1;
		uint64_t aww_sp:1;
		uint64_t wesewved_4_4:1;
		uint64_t mbox_nmp:1;
		uint64_t mbox_fmp:1;
		uint64_t mbox_sp:1;
		uint64_t wesewved_8_8:1;
		uint64_t id_nmp:1;
		uint64_t id_fmp:1;
		uint64_t id_sp:1;
		uint64_t ctww_nmp:1;
		uint64_t ctww_fmp:1;
		uint64_t ctww_sp:1;
		uint64_t wesewved_15_63:49;
#endif
	} s;
};

union cvmx_swiox_omsg_powtx {
	uint64_t u64;
	stwuct cvmx_swiox_omsg_powtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t enabwe:1;
		uint64_t wesewved_3_30:28;
		uint64_t powt:3;
#ewse
		uint64_t powt:3;
		uint64_t wesewved_3_30:28;
		uint64_t enabwe:1;
		uint64_t wesewved_32_63:32;
#endif
	} s;
	stwuct cvmx_swiox_omsg_powtx_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t enabwe:1;
		uint64_t wesewved_2_30:29;
		uint64_t powt:2;
#ewse
		uint64_t powt:2;
		uint64_t wesewved_2_30:29;
		uint64_t enabwe:1;
		uint64_t wesewved_32_63:32;
#endif
	} cn63xx;
};

union cvmx_swiox_omsg_siwo_thw {
	uint64_t u64;
	stwuct cvmx_swiox_omsg_siwo_thw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t tot_siwo:5;
#ewse
		uint64_t tot_siwo:5;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_swiox_omsg_sp_mwx {
	uint64_t u64;
	stwuct cvmx_swiox_omsg_sp_mwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t xmbox_sp:1;
		uint64_t ctww_sp:1;
		uint64_t ctww_fmp:1;
		uint64_t ctww_nmp:1;
		uint64_t id_sp:1;
		uint64_t id_fmp:1;
		uint64_t id_nmp:1;
		uint64_t id_psd:1;
		uint64_t mbox_sp:1;
		uint64_t mbox_fmp:1;
		uint64_t mbox_nmp:1;
		uint64_t mbox_psd:1;
		uint64_t aww_sp:1;
		uint64_t aww_fmp:1;
		uint64_t aww_nmp:1;
		uint64_t aww_psd:1;
#ewse
		uint64_t aww_psd:1;
		uint64_t aww_nmp:1;
		uint64_t aww_fmp:1;
		uint64_t aww_sp:1;
		uint64_t mbox_psd:1;
		uint64_t mbox_nmp:1;
		uint64_t mbox_fmp:1;
		uint64_t mbox_sp:1;
		uint64_t id_psd:1;
		uint64_t id_nmp:1;
		uint64_t id_fmp:1;
		uint64_t id_sp:1;
		uint64_t ctww_nmp:1;
		uint64_t ctww_fmp:1;
		uint64_t ctww_sp:1;
		uint64_t xmbox_sp:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_swiox_pwiox_in_use {
	uint64_t u64;
	stwuct cvmx_swiox_pwiox_in_use_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t end_cnt:16;
		uint64_t stawt_cnt:16;
#ewse
		uint64_t stawt_cnt:16;
		uint64_t end_cnt:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_swiox_wx_beww {
	uint64_t u64;
	stwuct cvmx_swiox_wx_beww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t data:16;
		uint64_t swc_id:16;
		uint64_t count:8;
		uint64_t wesewved_5_7:3;
		uint64_t dest_id:1;
		uint64_t id16:1;
		uint64_t wesewved_2_2:1;
		uint64_t pwiowity:2;
#ewse
		uint64_t pwiowity:2;
		uint64_t wesewved_2_2:1;
		uint64_t id16:1;
		uint64_t dest_id:1;
		uint64_t wesewved_5_7:3;
		uint64_t count:8;
		uint64_t swc_id:16;
		uint64_t data:16;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_swiox_wx_beww_seq {
	uint64_t u64;
	stwuct cvmx_swiox_wx_beww_seq_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t count:8;
		uint64_t seq:32;
#ewse
		uint64_t seq:32;
		uint64_t count:8;
		uint64_t wesewved_40_63:24;
#endif
	} s;
};

union cvmx_swiox_wx_status {
	uint64_t u64;
	stwuct cvmx_swiox_wx_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wtn_pw3:8;
		uint64_t wtn_pw2:8;
		uint64_t wtn_pw1:8;
		uint64_t wesewved_28_39:12;
		uint64_t mbox:4;
		uint64_t comp:8;
		uint64_t wesewved_13_15:3;
		uint64_t n_post:5;
		uint64_t post:8;
#ewse
		uint64_t post:8;
		uint64_t n_post:5;
		uint64_t wesewved_13_15:3;
		uint64_t comp:8;
		uint64_t mbox:4;
		uint64_t wesewved_28_39:12;
		uint64_t wtn_pw1:8;
		uint64_t wtn_pw2:8;
		uint64_t wtn_pw3:8;
#endif
	} s;
};

union cvmx_swiox_s2m_typex {
	uint64_t u64;
	stwuct cvmx_swiox_s2m_typex_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_19_63:45;
		uint64_t ww_op:3;
		uint64_t wesewved_15_15:1;
		uint64_t wd_op:3;
		uint64_t ww_pwiow:2;
		uint64_t wd_pwiow:2;
		uint64_t wesewved_6_7:2;
		uint64_t swc_id:1;
		uint64_t id16:1;
		uint64_t wesewved_2_3:2;
		uint64_t iaow_sew:2;
#ewse
		uint64_t iaow_sew:2;
		uint64_t wesewved_2_3:2;
		uint64_t id16:1;
		uint64_t swc_id:1;
		uint64_t wesewved_6_7:2;
		uint64_t wd_pwiow:2;
		uint64_t ww_pwiow:2;
		uint64_t wd_op:3;
		uint64_t wesewved_15_15:1;
		uint64_t ww_op:3;
		uint64_t wesewved_19_63:45;
#endif
	} s;
};

union cvmx_swiox_seq {
	uint64_t u64;
	stwuct cvmx_swiox_seq_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t seq:32;
#ewse
		uint64_t seq:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_swiox_status_weg {
	uint64_t u64;
	stwuct cvmx_swiox_status_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t access:1;
		uint64_t swio:1;
#ewse
		uint64_t swio:1;
		uint64_t access:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_swiox_tag_ctww {
	uint64_t u64;
	stwuct cvmx_swiox_tag_ctww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t o_cww:1;
		uint64_t wesewved_13_15:3;
		uint64_t otag:5;
		uint64_t wesewved_5_7:3;
		uint64_t itag:5;
#ewse
		uint64_t itag:5;
		uint64_t wesewved_5_7:3;
		uint64_t otag:5;
		uint64_t wesewved_13_15:3;
		uint64_t o_cww:1;
		uint64_t wesewved_17_63:47;
#endif
	} s;
};

union cvmx_swiox_twp_cwedits {
	uint64_t u64;
	stwuct cvmx_swiox_twp_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t mbox:4;
		uint64_t comp:8;
		uint64_t wesewved_13_15:3;
		uint64_t n_post:5;
		uint64_t post:8;
#ewse
		uint64_t post:8;
		uint64_t n_post:5;
		uint64_t wesewved_13_15:3;
		uint64_t comp:8;
		uint64_t mbox:4;
		uint64_t wesewved_28_63:36;
#endif
	} s;
};

union cvmx_swiox_tx_beww {
	uint64_t u64;
	stwuct cvmx_swiox_tx_beww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t data:16;
		uint64_t dest_id:16;
		uint64_t wesewved_9_15:7;
		uint64_t pending:1;
		uint64_t wesewved_5_7:3;
		uint64_t swc_id:1;
		uint64_t id16:1;
		uint64_t wesewved_2_2:1;
		uint64_t pwiowity:2;
#ewse
		uint64_t pwiowity:2;
		uint64_t wesewved_2_2:1;
		uint64_t id16:1;
		uint64_t swc_id:1;
		uint64_t wesewved_5_7:3;
		uint64_t pending:1;
		uint64_t wesewved_9_15:7;
		uint64_t dest_id:16;
		uint64_t data:16;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_swiox_tx_beww_info {
	uint64_t u64;
	stwuct cvmx_swiox_tx_beww_info_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t data:16;
		uint64_t dest_id:16;
		uint64_t wesewved_8_15:8;
		uint64_t timeout:1;
		uint64_t ewwow:1;
		uint64_t wetwy:1;
		uint64_t swc_id:1;
		uint64_t id16:1;
		uint64_t wesewved_2_2:1;
		uint64_t pwiowity:2;
#ewse
		uint64_t pwiowity:2;
		uint64_t wesewved_2_2:1;
		uint64_t id16:1;
		uint64_t swc_id:1;
		uint64_t wetwy:1;
		uint64_t ewwow:1;
		uint64_t timeout:1;
		uint64_t wesewved_8_15:8;
		uint64_t dest_id:16;
		uint64_t data:16;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_swiox_tx_ctww {
	uint64_t u64;
	stwuct cvmx_swiox_tx_ctww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_53_63:11;
		uint64_t tag_th2:5;
		uint64_t wesewved_45_47:3;
		uint64_t tag_th1:5;
		uint64_t wesewved_37_39:3;
		uint64_t tag_th0:5;
		uint64_t wesewved_20_31:12;
		uint64_t tx_th2:4;
		uint64_t wesewved_12_15:4;
		uint64_t tx_th1:4;
		uint64_t wesewved_4_7:4;
		uint64_t tx_th0:4;
#ewse
		uint64_t tx_th0:4;
		uint64_t wesewved_4_7:4;
		uint64_t tx_th1:4;
		uint64_t wesewved_12_15:4;
		uint64_t tx_th2:4;
		uint64_t wesewved_20_31:12;
		uint64_t tag_th0:5;
		uint64_t wesewved_37_39:3;
		uint64_t tag_th1:5;
		uint64_t wesewved_45_47:3;
		uint64_t tag_th2:5;
		uint64_t wesewved_53_63:11;
#endif
	} s;
};

union cvmx_swiox_tx_emphasis {
	uint64_t u64;
	stwuct cvmx_swiox_tx_emphasis_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t emph:4;
#ewse
		uint64_t emph:4;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_swiox_tx_status {
	uint64_t u64;
	stwuct cvmx_swiox_tx_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t s2m_pw3:8;
		uint64_t s2m_pw2:8;
		uint64_t s2m_pw1:8;
		uint64_t s2m_pw0:8;
#ewse
		uint64_t s2m_pw0:8;
		uint64_t s2m_pw1:8;
		uint64_t s2m_pw2:8;
		uint64_t s2m_pw3:8;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_swiox_ww_done_counts {
	uint64_t u64;
	stwuct cvmx_swiox_ww_done_counts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t bad:16;
		uint64_t good:16;
#ewse
		uint64_t good:16;
		uint64_t bad:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

#endif
