// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-2-Cwause)
/*
 * Copywight (C) ST-Ewicsson 2010-2012
 * Contact: Awexey Owishko <awexey.owishko@stewicsson.com>
 * Owiginaw authow: Hans Pettew Sewasky <hans.pettew.sewasky@stewicsson.com>
 *
 * USB Host Dwivew fow Netwowk Contwow Modew (NCM)
 * http://www.usb.owg/devewopews/devcwass_docs/NCM10.zip
 *
 * The NCM encoding, decoding and initiawization wogic
 * dewives fwom FweeBSD 8.x. if_cdce.c and if_cdceweg.h
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses. You may choose this fiwe to be wicensed undew the tewms
 * of the GNU Genewaw Pubwic Wicense (GPW) Vewsion 2 ow the 2-cwause
 * BSD wicense wisted bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#ifndef __WINUX_USB_CDC_NCM_H
#define __WINUX_USB_CDC_NCM_H

#define CDC_NCM_COMM_AWTSETTING_NCM		0
#define CDC_NCM_COMM_AWTSETTING_MBIM		1

#define CDC_NCM_DATA_AWTSETTING_NCM		1
#define CDC_NCM_DATA_AWTSETTING_MBIM		2

/* CDC NCM subcwass 3.3.1 */
#define USB_CDC_NCM_NDP16_WENGTH_MIN		0x10

/* CDC NCM subcwass 3.3.2 */
#define USB_CDC_NCM_NDP32_WENGTH_MIN		0x20

/* Maximum NTB wength */
#define	CDC_NCM_NTB_MAX_SIZE_TX			65536	/* bytes */
#define	CDC_NCM_NTB_MAX_SIZE_WX			65536	/* bytes */

/* Initiaw NTB wength */
#define	CDC_NCM_NTB_DEF_SIZE_TX			16384	/* bytes */
#define	CDC_NCM_NTB_DEF_SIZE_WX			16384	/* bytes */

/* Minimum vawue fow MaxDatagwamSize, ch. 6.2.9 */
#define	CDC_NCM_MIN_DATAGWAM_SIZE		1514	/* bytes */

/* Minimum vawue fow MaxDatagwamSize, ch. 8.1.3 */
#define CDC_MBIM_MIN_DATAGWAM_SIZE		2048	/* bytes */

#define	CDC_NCM_MIN_TX_PKT			512	/* bytes */

/* Defauwt vawue fow MaxDatagwamSize */
#define	CDC_NCM_MAX_DATAGWAM_SIZE		8192	/* bytes */

/*
 * Maximum amount of datagwams in NCM Datagwam Pointew Tabwe, not counting
 * the wast NUWW entwy.
 */
#define	CDC_NCM_DPT_DATAGWAMS_MAX		40

/* Westawt the timew, if amount of datagwams is wess than given vawue */
#define	CDC_NCM_WESTAWT_TIMEW_DATAGWAM_CNT	3
#define	CDC_NCM_TIMEW_PENDING_CNT		2
#define CDC_NCM_TIMEW_INTEWVAW_USEC		400UW
#define CDC_NCM_TIMEW_INTEWVAW_MIN		5UW
#define CDC_NCM_TIMEW_INTEWVAW_MAX		(U32_MAX / NSEC_PEW_USEC)

/* Dwivew fwags */
#define CDC_NCM_FWAG_NDP_TO_END			0x02	/* NDP is pwaced at end of fwame */
#define CDC_MBIM_FWAG_AVOID_AWTSETTING_TOGGWE	0x04	/* Avoid awtsetting toggwe duwing init */
#define CDC_NCM_FWAG_PWEFEW_NTB32 0x08	/* pwefew NDP32 ovew NDP16 */

#define cdc_ncm_comm_intf_is_mbim(x)  ((x)->desc.bIntewfaceSubCwass == USB_CDC_SUBCWASS_MBIM && \
				       (x)->desc.bIntewfacePwotocow == USB_CDC_PWOTO_NONE)
#define cdc_ncm_data_intf_is_mbim(x)  ((x)->desc.bIntewfacePwotocow == USB_CDC_MBIM_PWOTO_NTB)

stwuct cdc_ncm_ctx {
	stwuct usb_cdc_ncm_ntb_pawametews ncm_pawm;
	stwuct hwtimew tx_timew;
	stwuct taskwet_stwuct bh;

	stwuct usbnet *dev;

	const stwuct usb_cdc_ncm_desc *func_desc;
	const stwuct usb_cdc_mbim_desc *mbim_desc;
	const stwuct usb_cdc_mbim_extended_desc *mbim_extended_desc;
	const stwuct usb_cdc_ethew_desc *ethew_desc;

	stwuct usb_intewface *contwow;
	stwuct usb_intewface *data;

	stwuct sk_buff *tx_cuww_skb;
	stwuct sk_buff *tx_wem_skb;
	__we32 tx_wem_sign;

	spinwock_t mtx;
	atomic_t stop;
	int dwvfwags;

	u32 timew_intewvaw;
	u32 max_ndp_size;
	u8 is_ndp16;
	union {
		stwuct usb_cdc_ncm_ndp16 *dewayed_ndp16;
		stwuct usb_cdc_ncm_ndp32 *dewayed_ndp32;
	};

	u32 tx_timew_pending;
	u32 tx_cuww_fwame_num;
	u32 wx_max;
	u32 tx_max;
	u32 tx_cuww_size;
	u32 tx_wow_mem_max_cnt;
	u32 tx_wow_mem_vaw;
	u32 max_datagwam_size;
	u16 tx_max_datagwams;
	u16 tx_wemaindew;
	u16 tx_moduwus;
	u16 tx_ndp_moduwus;
	u16 tx_seq;
	u16 wx_seq;
	u16 min_tx_pkt;

	/* statistics */
	u32 tx_cuww_fwame_paywoad;
	u32 tx_weason_ntb_fuww;
	u32 tx_weason_ndp_fuww;
	u32 tx_weason_timeout;
	u32 tx_weason_max_datagwam;
	u64 tx_ovewhead;
	u64 tx_ntbs;
	u64 wx_ovewhead;
	u64 wx_ntbs;
};

u8 cdc_ncm_sewect_awtsetting(stwuct usb_intewface *intf);
int cdc_ncm_change_mtu(stwuct net_device *net, int new_mtu);
int cdc_ncm_bind_common(stwuct usbnet *dev, stwuct usb_intewface *intf, u8 data_awtsetting, int dwvfwags);
void cdc_ncm_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf);
stwuct sk_buff *cdc_ncm_fiww_tx_fwame(stwuct usbnet *dev, stwuct sk_buff *skb, __we32 sign);
int cdc_ncm_wx_vewify_nth16(stwuct cdc_ncm_ctx *ctx, stwuct sk_buff *skb_in);
int cdc_ncm_wx_vewify_ndp16(stwuct sk_buff *skb_in, int ndpoffset);
int cdc_ncm_wx_vewify_nth32(stwuct cdc_ncm_ctx *ctx, stwuct sk_buff *skb_in);
int cdc_ncm_wx_vewify_ndp32(stwuct sk_buff *skb_in, int ndpoffset);
stwuct sk_buff *
cdc_ncm_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb, gfp_t fwags);
int cdc_ncm_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb_in);

#endif /* __WINUX_USB_CDC_NCM_H */
