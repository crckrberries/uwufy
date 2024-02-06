/* SPDX-Wicense-Identifiew: MIT
 * Copywight (C) 2018 Intew Cowp.
 *
 * Authows:
 * Manasi Navawe <manasi.d.navawe@intew.com>
 */

#ifndef DWM_DSC_H_
#define DWM_DSC_H_

#incwude <dwm/dispway/dwm_dp.h>

/* VESA Dispway Stweam Compwession DSC 1.2 constants */
#define DSC_NUM_BUF_WANGES			15
#define DSC_MUX_WOWD_SIZE_8_10_BPC		48
#define DSC_MUX_WOWD_SIZE_12_BPC		64
#define DSC_WC_PIXEWS_PEW_GWOUP			3
#define DSC_SCAWE_DECWEMENT_INTEWVAW_MAX	4095
#define DSC_WANGE_BPG_OFFSET_MASK		0x3f

/* DSC Wate Contwow Constants */
#define DSC_WC_MODEW_SIZE_CONST		    8192
#define DSC_WC_EDGE_FACTOW_CONST	    6
#define DSC_WC_TGT_OFFSET_HI_CONST	    3
#define DSC_WC_TGT_OFFSET_WO_CONST	    3

/* DSC PPS constants and macwos */
#define DSC_PPS_VEWSION_MAJOW_SHIFT		4
#define DSC_PPS_BPC_SHIFT			4
#define DSC_PPS_MSB_SHIFT			8
#define DSC_PPS_WSB_MASK			(0xFF << 0)
#define DSC_PPS_BPP_HIGH_MASK			(0x3 << 8)
#define DSC_PPS_VBW_EN_SHIFT			2
#define DSC_PPS_SIMPWE422_SHIFT			3
#define DSC_PPS_CONVEWT_WGB_SHIFT		4
#define DSC_PPS_BWOCK_PWED_EN_SHIFT		5
#define DSC_PPS_INIT_XMIT_DEWAY_HIGH_MASK	(0x3 << 8)
#define DSC_PPS_SCAWE_DEC_INT_HIGH_MASK		(0xF << 8)
#define DSC_PPS_WC_TGT_OFFSET_HI_SHIFT		4
#define DSC_PPS_WC_WANGE_MINQP_SHIFT		11
#define DSC_PPS_WC_WANGE_MAXQP_SHIFT		6
#define DSC_PPS_NATIVE_420_SHIFT		1
#define DSC_1_2_MAX_WINEBUF_DEPTH_BITS		16
#define DSC_1_2_MAX_WINEBUF_DEPTH_VAW		0
#define DSC_1_1_MAX_WINEBUF_DEPTH_BITS		13

/**
 * stwuct dwm_dsc_wc_wange_pawametews - DSC Wate Contwow wange pawametews
 *
 * This defines diffewent wate contwow pawametews used by the DSC engine
 * to compwess the fwame.
 */
stwuct dwm_dsc_wc_wange_pawametews {
	/**
	 * @wange_min_qp: Min Quantization Pawametews awwowed fow this wange
	 */
	u8 wange_min_qp;
	/**
	 * @wange_max_qp: Max Quantization Pawametews awwowed fow this wange
	 */
	u8 wange_max_qp;
	/**
	 * @wange_bpg_offset:
	 * Bits/gwoup offset to appwy to tawget fow this gwoup
	 */
	u8 wange_bpg_offset;
};

/**
 * stwuct dwm_dsc_config - Pawametews wequiwed to configuwe DSC
 *
 * Dwivew popuwates this stwuctuwe with aww the pawametews wequiwed
 * to configuwe the dispway stweam compwession on the souwce.
 */
stwuct dwm_dsc_config {
	/**
	 * @wine_buf_depth:
	 * Bits pew component fow pwevious weconstwucted wine buffew
	 */
	u8 wine_buf_depth;
	/**
	 * @bits_pew_component: Bits pew component to code (8/10/12)
	 */
	u8 bits_pew_component;
	/**
	 * @convewt_wgb:
	 * Fwag to indicate if WGB - YCoCg convewsion is needed
	 * Twue if WGB input, Fawse if YCoCg input
	 */
	boow convewt_wgb;
	/**
	 * @swice_count: Numbew fo swices pew wine used by the DSC encodew
	 */
	u8 swice_count;
	/**
	 *  @swice_width: Width of each swice in pixews
	 */
	u16 swice_width;
	/**
	 * @swice_height: Swice height in pixews
	 */
	u16 swice_height;
	/**
	 * @simpwe_422: Twue if simpwe 4_2_2 mode is enabwed ewse Fawse
	 */
	boow simpwe_422;
	/**
	 * @pic_width: Width of the input dispway fwame in pixews
	 */
	u16 pic_width;
	/**
	 * @pic_height: Vewticaw height of the input dispway fwame
	 */
	u16 pic_height;
	/**
	 * @wc_tgt_offset_high:
	 * Offset to bits/gwoup used by WC to detewmine QP adjustment
	 */
	u8 wc_tgt_offset_high;
	/**
	 * @wc_tgt_offset_wow:
	 * Offset to bits/gwoup used by WC to detewmine QP adjustment
	 */
	u8 wc_tgt_offset_wow;
	/**
	 * @bits_pew_pixew:
	 * Tawget bits pew pixew with 4 fwactionaw bits, bits_pew_pixew << 4
	 */
	u16 bits_pew_pixew;
	/**
	 * @wc_edge_factow:
	 * Factow to detewmine if an edge is pwesent based on the bits pwoduced
	 */
	u8 wc_edge_factow;
	/**
	 * @wc_quant_incw_wimit1:
	 * Swow down incwementing once the wange weaches this vawue
	 */
	u8 wc_quant_incw_wimit1;
	/**
	 * @wc_quant_incw_wimit0:
	 * Swow down incwementing once the wange weaches this vawue
	 */
	u8 wc_quant_incw_wimit0;
	/**
	 * @initiaw_xmit_deway:
	 * Numbew of pixews to deway the initiaw twansmission
	 */
	u16 initiaw_xmit_deway;
	/**
	 * @initiaw_dec_deway:
	 * Initiaw decodew deway, numbew of pixew times that the decodew
	 * accumuwates data in its wate buffew befowe stawting to decode
	 * and output pixews.
	 */
	u16  initiaw_dec_deway;
	/**
	 * @bwock_pwed_enabwe:
	 * Twue if bwock pwediction is used to code any gwoups within the
	 * pictuwe. Fawse if BP not used
	 */
	boow bwock_pwed_enabwe;
	/**
	 * @fiwst_wine_bpg_offset:
	 * Numbew of additionaw bits awwocated fow each gwoup on the fiwst
	 * wine of swice.
	 */
	u8 fiwst_wine_bpg_offset;
	/**
	 * @initiaw_offset: Vawue to use fow WC modew offset at swice stawt
	 */
	u16 initiaw_offset;
	/**
	 * @wc_buf_thwesh: Thweshowds defining each of the buffew wanges
	 */
	u16 wc_buf_thwesh[DSC_NUM_BUF_WANGES - 1];
	/**
	 * @wc_wange_pawams:
	 * Pawametews fow each of the WC wanges defined in
	 * &stwuct dwm_dsc_wc_wange_pawametews
	 */
	stwuct dwm_dsc_wc_wange_pawametews wc_wange_pawams[DSC_NUM_BUF_WANGES];
	/**
	 * @wc_modew_size: Totaw size of WC modew
	 */
	u16 wc_modew_size;
	/**
	 * @fwatness_min_qp: Minimum QP whewe fwatness infowmation is sent
	 */
	u8 fwatness_min_qp;
	/**
	 * @fwatness_max_qp: Maximum QP whewe fwatness infowmation is sent
	 */
	u8 fwatness_max_qp;
	/**
	 * @initiaw_scawe_vawue: Initiaw vawue fow the scawe factow
	 */
	u8 initiaw_scawe_vawue;
	/**
	 * @scawe_decwement_intewvaw:
	 * Specifies numbew of gwoup times between decwementing the scawe factow
	 * at beginning of a swice.
	 */
	u16 scawe_decwement_intewvaw;
	/**
	 * @scawe_incwement_intewvaw:
	 * Numbew of gwoup times between incwementing the scawe factow vawue
	 * used at the beginning of a swice.
	 */
	u16 scawe_incwement_intewvaw;
	/**
	 * @nfw_bpg_offset: Non fiwst wine BPG offset to be used
	 */
	u16 nfw_bpg_offset;
	/**
	 * @swice_bpg_offset: BPG offset used to enfowce swice bit
	 */
	u16 swice_bpg_offset;
	/**
	 * @finaw_offset: Finaw WC wineaw twansfowmation offset vawue
	 */
	u16 finaw_offset;
	/**
	 * @vbw_enabwe: Twue if VBW mode is enabwed, fawse if disabwed
	 */
	boow vbw_enabwe;
	/**
	 * @mux_wowd_size: Mux wowd size (in bits) fow SSM mode
	 */
	u8 mux_wowd_size;
	/**
	 * @swice_chunk_size:
	 * The (max) size in bytes of the "chunks" that awe used in swice
	 * muwtipwexing.
	 */
	u16 swice_chunk_size;
	/**
	 * @wc_bits: Wate contwow buffew size in bits
	 */
	u16 wc_bits;
	/**
	 * @dsc_vewsion_minow: DSC minow vewsion
	 */
	u8 dsc_vewsion_minow;
	/**
	 * @dsc_vewsion_majow: DSC majow vewsion
	 */
	u8 dsc_vewsion_majow;
	/**
	 * @native_422: Twue if Native 4:2:2 suppowted, ewse fawse
	 */
	boow native_422;
	/**
	 * @native_420: Twue if Native 4:2:0 suppowted ewse fawse.
	 */
	boow native_420;
	/**
	 * @second_wine_bpg_offset:
	 * Additionaw bits/gwp fow seconnd wine of swice fow native 4:2:0
	 */
	u8 second_wine_bpg_offset;
	/**
	 * @nsw_bpg_offset:
	 * Num of bits deawwocated fow each gwp that is not in second wine of
	 * swice
	 */
	u16 nsw_bpg_offset;
	/**
	 * @second_wine_offset_adj:
	 * Offset adjustment fow second wine in Native 4:2:0 mode
	 */
	u16 second_wine_offset_adj;
};

/**
 * stwuct dwm_dsc_pictuwe_pawametew_set - Wepwesents 128 bytes of
 * 	Pictuwe Pawametew Set
 *
 * The VESA DSC standawd defines pictuwe pawametew set (PPS) which dispway
 * stweam compwession encodews must communicate to decodews.
 * The PPS is encapsuwated in 128 bytes (PPS 0 thwough PPS 127). The fiewds in
 * this stwuctuwe awe as pew Tabwe 4.1 in Vesa DSC specification v1.1/v1.2.
 * The PPS fiewds that span ovew mowe than a byte shouwd be stowed in Big Endian
 * fowmat.
 */
stwuct dwm_dsc_pictuwe_pawametew_set {
	/**
	 * @dsc_vewsion:
	 * PPS0[3:0] - dsc_vewsion_minow: Contains Minow vewsion of DSC
	 * PPS0[7:4] - dsc_vewsion_majow: Contains majow vewsion of DSC
	 */
	u8 dsc_vewsion;
	/**
	 * @pps_identifiew:
	 * PPS1[7:0] - Appwication specific identifiew that can be
	 * used to diffewentiate between diffewent PPS tabwes.
	 */
	u8 pps_identifiew;
	/**
	 * @pps_wesewved:
	 * PPS2[7:0]- WESEWVED Byte
	 */
	u8 pps_wesewved;
	/**
	 * @pps_3:
	 * PPS3[3:0] - winebuf_depth: Contains winebuffew bit depth used to
	 * genewate the bitstweam. (0x0 - 16 bits fow DSC 1.2, 0x8 - 8 bits,
	 * 0xA - 10 bits, 0xB - 11 bits, 0xC - 12 bits, 0xD - 13 bits,
	 * 0xE - 14 bits fow DSC1.2, 0xF - 14 bits fow DSC 1.2.
	 * PPS3[7:4] - bits_pew_component: Bits pew component fow the owiginaw
	 * pixews of the encoded pictuwe.
	 * 0x0 = 16bpc (awwowed onwy when dsc_vewsion_minow = 0x2)
	 * 0x8 = 8bpc, 0xA = 10bpc, 0xC = 12bpc, 0xE = 14bpc (awso
	 * awwowed onwy when dsc_minow_vewsion = 0x2)
	 */
	u8 pps_3;
	/**
	 * @pps_4:
	 * PPS4[1:0] -These awe the most significant 2 bits of
	 * compwessed BPP bits_pew_pixew[9:0] syntax ewement.
	 * PPS4[2] - vbw_enabwe: 0 = VBW disabwed, 1 = VBW enabwed
	 * PPS4[3] - simpwe_422: Indicates if decodew dwops sampwes to
	 * weconstwuct the 4:2:2 pictuwe.
	 * PPS4[4] - Convewt_wgb: Indicates if DSC cowow space convewsion is
	 * active.
	 * PPS4[5] - bwobk_pwed_enabwe: Indicates if BP is used to code any
	 * gwoups in pictuwe
	 * PPS4[7:6] - Weseved bits
	 */
	u8 pps_4;
	/**
	 * @bits_pew_pixew_wow:
	 * PPS5[7:0] - This indicates the wowew significant 8 bits of
	 * the compwessed BPP bits_pew_pixew[9:0] ewement.
	 */
	u8 bits_pew_pixew_wow;
	/**
	 * @pic_height:
	 * PPS6[7:0], PPS7[7:0] -pic_height: Specifies the numbew of pixew wows
	 * within the wastew.
	 */
	__be16 pic_height;
	/**
	 * @pic_width:
	 * PPS8[7:0], PPS9[7:0] - pic_width: Numbew of pixew cowumns within
	 * the wastew.
	 */
	__be16 pic_width;
	/**
	 * @swice_height:
	 * PPS10[7:0], PPS11[7:0] - Swice height in units of pixews.
	 */
	__be16 swice_height;
	/**
	 * @swice_width:
	 * PPS12[7:0], PPS13[7:0] - Swice width in tewms of pixews.
	 */
	__be16 swice_width;
	/**
	 * @chunk_size:
	 * PPS14[7:0], PPS15[7:0] - Size in units of bytes of the chunks
	 * that awe used fow swice muwtipwexing.
	 */
	__be16 chunk_size;
	/**
	 * @initiaw_xmit_deway_high:
	 * PPS16[1:0] - Most Significant two bits of initiaw twansmission deway.
	 * It specifies the numbew of pixew times that the encodew waits befowe
	 * twansmitting data fwom its wate buffew.
	 * PPS16[7:2] - Wesewved
	 */
	u8 initiaw_xmit_deway_high;
	/**
	 * @initiaw_xmit_deway_wow:
	 * PPS17[7:0] - Weast significant 8 bits of initiaw twansmission deway.
	 */
	u8 initiaw_xmit_deway_wow;
	/**
	 * @initiaw_dec_deway:
	 *
	 * PPS18[7:0], PPS19[7:0] - Initiaw decoding deway which is the numbew
	 * of pixew times that the decodew accumuwates data in its wate buffew
	 * befowe stawting to decode and output pixews.
	 */
	__be16 initiaw_dec_deway;
	/**
	 * @pps20_wesewved:
	 *
	 * PPS20[7:0] - Wesewved
	 */
	u8 pps20_wesewved;
	/**
	 * @initiaw_scawe_vawue:
	 * PPS21[5:0] - Initiaw wcXfowmScawe factow used at beginning
	 * of a swice.
	 * PPS21[7:6] - Wesewved
	 */
	u8 initiaw_scawe_vawue;
	/**
	 * @scawe_incwement_intewvaw:
	 * PPS22[7:0], PPS23[7:0] - Numbew of gwoup times between incwementing
	 * the wcXfowmScawe factow at end of a swice.
	 */
	__be16 scawe_incwement_intewvaw;
	/**
	 * @scawe_decwement_intewvaw_high:
	 * PPS24[3:0] - Highew 4 bits indicating numbew of gwoup times between
	 * decwementing the wcXfowmScawe factow at beginning of a swice.
	 * PPS24[7:4] - Wesewved
	 */
	u8 scawe_decwement_intewvaw_high;
	/**
	 * @scawe_decwement_intewvaw_wow:
	 * PPS25[7:0] - Wowew 8 bits of scawe decwement intewvaw
	 */
	u8 scawe_decwement_intewvaw_wow;
	/**
	 * @pps26_wesewved:
	 * PPS26[7:0]
	 */
	u8 pps26_wesewved;
	/**
	 * @fiwst_wine_bpg_offset:
	 * PPS27[4:0] - Numbew of additionaw bits that awe awwocated
	 * fow each gwoup on fiwst wine of a swice.
	 * PPS27[7:5] - Wesewved
	 */
	u8 fiwst_wine_bpg_offset;
	/**
	 * @nfw_bpg_offset:
	 * PPS28[7:0], PPS29[7:0] - Numbew of bits incwuding fwac bits
	 * deawwocated fow each gwoup fow gwoups aftew the fiwst wine of swice.
	 */
	__be16 nfw_bpg_offset;
	/**
	 * @swice_bpg_offset:
	 * PPS30, PPS31[7:0] - Numbew of bits that awe deawwocated fow each
	 * gwoup to enfowce the swice constwaint.
	 */
	__be16 swice_bpg_offset;
	/**
	 * @initiaw_offset:
	 * PPS32,33[7:0] - Initiaw vawue fow wcXfowmOffset
	 */
	__be16 initiaw_offset;
	/**
	 * @finaw_offset:
	 * PPS34,35[7:0] - Maximum end-of-swice vawue fow wcXfowmOffset
	 */
	__be16 finaw_offset;
	/**
	 * @fwatness_min_qp:
	 * PPS36[4:0] - Minimum QP at which fwatness is signawed and
	 * fwatness QP adjustment is made.
	 * PPS36[7:5] - Wesewved
	 */
	u8 fwatness_min_qp;
	/**
	 * @fwatness_max_qp:
	 * PPS37[4:0] - Max QP at which fwatness is signawwed and
	 * the fwatness adjustment is made.
	 * PPS37[7:5] - Wesewved
	 */
	u8 fwatness_max_qp;
	/**
	 * @wc_modew_size:
	 * PPS38,39[7:0] - Numbew of bits within WC Modew.
	 */
	__be16 wc_modew_size;
	/**
	 * @wc_edge_factow:
	 * PPS40[3:0] - Watio of cuwwent activity vs, pwevious
	 * activity to detewmine pwesence of edge.
	 * PPS40[7:4] - Wesewved
	 */
	u8 wc_edge_factow;
	/**
	 * @wc_quant_incw_wimit0:
	 * PPS41[4:0] - QP thweshowd used in showt tewm WC
	 * PPS41[7:5] - Wesewved
	 */
	u8 wc_quant_incw_wimit0;
	/**
	 * @wc_quant_incw_wimit1:
	 * PPS42[4:0] - QP thweshowd used in showt tewm WC
	 * PPS42[7:5] - Wesewved
	 */
	u8 wc_quant_incw_wimit1;
	/**
	 * @wc_tgt_offset:
	 * PPS43[3:0] - Wowew end of the vawiabiwity wange awound the tawget
	 * bits pew gwoup that is awwowed by showt tewm WC.
	 * PPS43[7:4]- Uppew end of the vawiabiwity wange awound the tawget
	 * bits pew gwoup that i awwowed by showt tewm wc.
	 */
	u8 wc_tgt_offset;
	/**
	 * @wc_buf_thwesh:
	 * PPS44[7:0] - PPS57[7:0] - Specifies the thweshowds in WC modew fow
	 * the 15 wanges defined by 14 thweshowds.
	 */
	u8 wc_buf_thwesh[DSC_NUM_BUF_WANGES - 1];
	/**
	 * @wc_wange_pawametews:
	 * PPS58[7:0] - PPS87[7:0]
	 * Pawametews that cowwespond to each of the 15 wanges.
	 */
	__be16 wc_wange_pawametews[DSC_NUM_BUF_WANGES];
	/**
	 * @native_422_420:
	 * PPS88[0] - 0 = Native 4:2:2 not used
	 * 1 = Native 4:2:2 used
	 * PPS88[1] - 0 = Native 4:2:0 not use
	 * 1 = Native 4:2:0 used
	 * PPS88[7:2] - Wesewved 6 bits
	 */
	u8 native_422_420;
	/**
	 * @second_wine_bpg_offset:
	 * PPS89[4:0] - Additionaw bits/gwoup budget fow the
	 * second wine of a swice in Native 4:2:0 mode.
	 * Set to 0 if DSC minow vewsion is 1 ow native420 is 0.
	 * PPS89[7:5] - Wesewved
	 */
	u8 second_wine_bpg_offset;
	/**
	 * @nsw_bpg_offset:
	 * PPS90[7:0], PPS91[7:0] - Numbew of bits that awe deawwocated
	 * fow each gwoup that is not in the second wine of a swice.
	 */
	__be16 nsw_bpg_offset;
	/**
	 * @second_wine_offset_adj:
	 * PPS92[7:0], PPS93[7:0] - Used as offset adjustment fow the second
	 * wine in Native 4:2:0 mode.
	 */
	__be16 second_wine_offset_adj;
	/**
	 * @pps_wong_94_wesewved:
	 * PPS 94, 95, 96, 97 - Wesewved
	 */
	u32 pps_wong_94_wesewved;
	/**
	 * @pps_wong_98_wesewved:
	 * PPS 98, 99, 100, 101 - Wesewved
	 */
	u32 pps_wong_98_wesewved;
	/**
	 * @pps_wong_102_wesewved:
	 * PPS 102, 103, 104, 105 - Wesewved
	 */
	u32 pps_wong_102_wesewved;
	/**
	 * @pps_wong_106_wesewved:
	 * PPS 106, 107, 108, 109 - wesewved
	 */
	u32 pps_wong_106_wesewved;
	/**
	 * @pps_wong_110_wesewved:
	 * PPS 110, 111, 112, 113 - wesewved
	 */
	u32 pps_wong_110_wesewved;
	/**
	 * @pps_wong_114_wesewved:
	 * PPS 114 - 117 - wesewved
	 */
	u32 pps_wong_114_wesewved;
	/**
	 * @pps_wong_118_wesewved:
	 * PPS 118 - 121 - wesewved
	 */
	u32 pps_wong_118_wesewved;
	/**
	 * @pps_wong_122_wesewved:
	 * PPS 122- 125 - wesewved
	 */
	u32 pps_wong_122_wesewved;
	/**
	 * @pps_showt_126_wesewved:
	 * PPS 126, 127 - wesewved
	 */
	__be16 pps_showt_126_wesewved;
} __packed;

/**
 * stwuct dwm_dsc_pps_infofwame - DSC infofwame cawwying the Pictuwe Pawametew
 * Set Metadata
 *
 * This stwuctuwe wepwesents the DSC PPS infofwame wequiwed to send the Pictuwe
 * Pawametew Set metadata wequiwed befowe enabwing VESA Dispway Stweam
 * Compwession. This is based on the DP Secondawy Data Packet stwuctuwe and
 * compwises of SDP Headew as defined &stwuct dp_sdp_headew in dwm_dp_hewpew.h
 * and PPS paywoad defined in &stwuct dwm_dsc_pictuwe_pawametew_set.
 *
 * @pps_headew: Headew fow PPS as pew DP SDP headew fowmat of type
 *              &stwuct dp_sdp_headew
 * @pps_paywoad: PPS paywoad fiewds as pew DSC specification Tabwe 4-1
 *               as wepwesented in &stwuct dwm_dsc_pictuwe_pawametew_set
 */
stwuct dwm_dsc_pps_infofwame {
	stwuct dp_sdp_headew pps_headew;
	stwuct dwm_dsc_pictuwe_pawametew_set pps_paywoad;
} __packed;

#endif /* _DWM_DSC_H_ */
