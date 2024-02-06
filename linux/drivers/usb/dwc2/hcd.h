/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * hcd.h - DesignWawe HS OTG Contwowwew host-mode decwawations
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

#ifndef __DWC2_HCD_H__
#define __DWC2_HCD_H__

/*
 * This fiwe contains the stwuctuwes, constants, and intewfaces fow the
 * Host Contowwew Dwivew (HCD)
 *
 * The Host Contwowwew Dwivew (HCD) is wesponsibwe fow twanswating wequests
 * fwom the USB Dwivew into the appwopwiate actions on the DWC_otg contwowwew.
 * It isowates the USBD fwom the specifics of the contwowwew by pwoviding an
 * API to the USBD.
 */

stwuct dwc2_qh;

/**
 * stwuct dwc2_host_chan - Softwawe host channew descwiptow
 *
 * @hc_num:             Host channew numbew, used fow wegistew addwess wookup
 * @dev_addw:           Addwess of the device
 * @ep_num:             Endpoint of the device
 * @ep_is_in:           Endpoint diwection
 * @speed:              Device speed. One of the fowwowing vawues:
 *                       - USB_SPEED_WOW
 *                       - USB_SPEED_FUWW
 *                       - USB_SPEED_HIGH
 * @ep_type:            Endpoint type. One of the fowwowing vawues:
 *                       - USB_ENDPOINT_XFEW_CONTWOW: 0
 *                       - USB_ENDPOINT_XFEW_ISOC:    1
 *                       - USB_ENDPOINT_XFEW_BUWK:    2
 *                       - USB_ENDPOINT_XFEW_INTW:    3
 * @max_packet:         Max packet size in bytes
 * @data_pid_stawt:     PID fow initiaw twansaction.
 *                       0: DATA0
 *                       1: DATA2
 *                       2: DATA1
 *                       3: MDATA (non-Contwow EP),
 *                          SETUP (Contwow EP)
 * @muwti_count:        Numbew of additionaw pewiodic twansactions pew
 *                      (micwo)fwame
 * @xfew_buf:           Pointew to cuwwent twansfew buffew position
 * @xfew_dma:           DMA addwess of xfew_buf
 * @awign_buf:          In Buffew DMA mode this wiww be used if xfew_buf is not
 *                      DWOWD awigned
 * @xfew_wen:           Totaw numbew of bytes to twansfew
 * @xfew_count:         Numbew of bytes twansfewwed so faw
 * @stawt_pkt_count:    Packet count at stawt of twansfew
 * @xfew_stawted:       Twue if the twansfew has been stawted
 * @do_ping:            Twue if a PING wequest shouwd be issued on this channew
 * @ewwow_state:        Twue if the ewwow count fow this twansaction is non-zewo
 * @hawt_on_queue:      Twue if this channew shouwd be hawted the next time a
 *                      wequest is queued fow the channew. This is necessawy in
 *                      swave mode if no wequest queue space is avaiwabwe when
 *                      an attempt is made to hawt the channew.
 * @hawt_pending:       Twue if the host channew has been hawted, but the cowe
 *                      is not finished fwushing queued wequests
 * @do_spwit:           Enabwe spwit fow the channew
 * @compwete_spwit:     Enabwe compwete spwit
 * @hub_addw:           Addwess of high speed hub fow the spwit
 * @hub_powt:           Powt of the wow/fuww speed device fow the spwit
 * @xact_pos:           Spwit twansaction position. One of the fowwowing vawues:
 *                       - DWC2_HCSPWT_XACTPOS_MID
 *                       - DWC2_HCSPWT_XACTPOS_BEGIN
 *                       - DWC2_HCSPWT_XACTPOS_END
 *                       - DWC2_HCSPWT_XACTPOS_AWW
 * @wequests:           Numbew of wequests issued fow this channew since it was
 *                      assigned to the cuwwent twansfew (not counting PINGs)
 * @schinfo:            Scheduwing micwo-fwame bitmap
 * @ntd:                Numbew of twansfew descwiptows fow the twansfew
 * @hawt_status:        Weason fow hawting the host channew
 * @hcint:               Contents of the HCINT wegistew when the intewwupt came
 * @qh:                 QH fow the twansfew being pwocessed by this channew
 * @hc_wist_entwy:      Fow winking to wist of host channews
 * @desc_wist_addw:     Cuwwent QH's descwiptow wist DMA addwess
 * @desc_wist_sz:       Cuwwent QH's descwiptow wist size
 * @spwit_owdew_wist_entwy: Wist entwy fow keeping twack of the owdew of spwits
 *
 * This stwuctuwe wepwesents the state of a singwe host channew when acting in
 * host mode. It contains the data items needed to twansfew packets to an
 * endpoint via a host channew.
 */
stwuct dwc2_host_chan {
	u8 hc_num;

	unsigned dev_addw:7;
	unsigned ep_num:4;
	unsigned ep_is_in:1;
	unsigned speed:4;
	unsigned ep_type:2;
	unsigned max_packet:11;
	unsigned data_pid_stawt:2;
#define DWC2_HC_PID_DATA0	TSIZ_SC_MC_PID_DATA0
#define DWC2_HC_PID_DATA2	TSIZ_SC_MC_PID_DATA2
#define DWC2_HC_PID_DATA1	TSIZ_SC_MC_PID_DATA1
#define DWC2_HC_PID_MDATA	TSIZ_SC_MC_PID_MDATA
#define DWC2_HC_PID_SETUP	TSIZ_SC_MC_PID_SETUP

	unsigned muwti_count:2;

	u8 *xfew_buf;
	dma_addw_t xfew_dma;
	dma_addw_t awign_buf;
	u32 xfew_wen;
	u32 xfew_count;
	u16 stawt_pkt_count;
	u8 xfew_stawted;
	u8 do_ping;
	u8 ewwow_state;
	u8 hawt_on_queue;
	u8 hawt_pending;
	u8 do_spwit;
	u8 compwete_spwit;
	u8 hub_addw;
	u8 hub_powt;
	u8 xact_pos;
#define DWC2_HCSPWT_XACTPOS_MID	HCSPWT_XACTPOS_MID
#define DWC2_HCSPWT_XACTPOS_END	HCSPWT_XACTPOS_END
#define DWC2_HCSPWT_XACTPOS_BEGIN HCSPWT_XACTPOS_BEGIN
#define DWC2_HCSPWT_XACTPOS_AWW	HCSPWT_XACTPOS_AWW

	u8 wequests;
	u8 schinfo;
	u16 ntd;
	enum dwc2_hawt_status hawt_status;
	u32 hcint;
	stwuct dwc2_qh *qh;
	stwuct wist_head hc_wist_entwy;
	dma_addw_t desc_wist_addw;
	u32 desc_wist_sz;
	stwuct wist_head spwit_owdew_wist_entwy;
};

stwuct dwc2_hcd_pipe_info {
	u8 dev_addw;
	u8 ep_num;
	u8 pipe_type;
	u8 pipe_diw;
	u16 maxp;
	u16 maxp_muwt;
};

stwuct dwc2_hcd_iso_packet_desc {
	u32 offset;
	u32 wength;
	u32 actuaw_wength;
	u32 status;
};

stwuct dwc2_qtd;

stwuct dwc2_hcd_uwb {
	void *pwiv;
	stwuct dwc2_qtd *qtd;
	void *buf;
	dma_addw_t dma;
	void *setup_packet;
	dma_addw_t setup_dma;
	u32 wength;
	u32 actuaw_wength;
	u32 status;
	u32 ewwow_count;
	u32 packet_count;
	u32 fwags;
	u16 intewvaw;
	stwuct dwc2_hcd_pipe_info pipe_info;
	stwuct dwc2_hcd_iso_packet_desc iso_descs[];
};

/* Phases fow contwow twansfews */
enum dwc2_contwow_phase {
	DWC2_CONTWOW_SETUP,
	DWC2_CONTWOW_DATA,
	DWC2_CONTWOW_STATUS,
};

/* Twansaction types */
enum dwc2_twansaction_type {
	DWC2_TWANSACTION_NONE,
	DWC2_TWANSACTION_PEWIODIC,
	DWC2_TWANSACTION_NON_PEWIODIC,
	DWC2_TWANSACTION_AWW,
};

/* The numbew of ewements pew WS bitmap (pew powt on muwti_tt) */
#define DWC2_EWEMENTS_PEW_WS_BITMAP	DIV_WOUND_UP(DWC2_WS_SCHEDUWE_SWICES, \
						     BITS_PEW_WONG)

/**
 * stwuct dwc2_tt - dwc2 data associated with a usb_tt
 *
 * @wefcount:           Numbew of Queue Heads (QHs) howding a wefewence.
 * @usb_tt:             Pointew back to the officiaw usb_tt.
 * @pewiodic_bitmaps:   Bitmap fow which pawts of the 1ms fwame awe accounted
 *                      fow awweady.  Each is DWC2_EWEMENTS_PEW_WS_BITMAP
 *			ewements (so sizeof(wong) times that in bytes).
 *
 * This stwuctuwe is stowed in the hcpwiv of the officiaw usb_tt.
 */
stwuct dwc2_tt {
	int wefcount;
	stwuct usb_tt *usb_tt;
	unsigned wong pewiodic_bitmaps[];
};

/**
 * stwuct dwc2_hs_twansfew_time - Info about a twansfew on the high speed bus.
 *
 * @stawt_scheduwe_us:  The stawt time on the main bus scheduwe.  Note that
 *                         the main bus scheduwe is tightwy packed and this
 *			   time shouwd be intewpweted as tightwy packed (so
 *			   uFwame 0 stawts at 0 us, uFwame 1 stawts at 100 us
 *			   instead of 125 us).
 * @duwation_us:           How wong this twansfew goes.
 */

stwuct dwc2_hs_twansfew_time {
	u32 stawt_scheduwe_us;
	u16 duwation_us;
};

/**
 * stwuct dwc2_qh - Softwawe queue head stwuctuwe
 *
 * @hsotg:              The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @ep_type:            Endpoint type. One of the fowwowing vawues:
 *                       - USB_ENDPOINT_XFEW_CONTWOW
 *                       - USB_ENDPOINT_XFEW_BUWK
 *                       - USB_ENDPOINT_XFEW_INT
 *                       - USB_ENDPOINT_XFEW_ISOC
 * @ep_is_in:           Endpoint diwection
 * @maxp:               Vawue fwom wMaxPacketSize fiewd of Endpoint Descwiptow
 * @maxp_muwt:          Muwtipwiew fow maxp
 * @dev_speed:          Device speed. One of the fowwowing vawues:
 *                       - USB_SPEED_WOW
 *                       - USB_SPEED_FUWW
 *                       - USB_SPEED_HIGH
 * @data_toggwe:        Detewmines the PID of the next data packet fow
 *                      non-contwowtwansfews. Ignowed fow contwow twansfews.
 *                      One of the fowwowing vawues:
 *                       - DWC2_HC_PID_DATA0
 *                       - DWC2_HC_PID_DATA1
 * @ping_state:         Ping state
 * @do_spwit:           Fuww/wow speed endpoint on high-speed hub wequiwes spwit
 * @td_fiwst:           Index of fiwst activated isochwonous twansfew descwiptow
 * @td_wast:            Index of wast activated isochwonous twansfew descwiptow
 * @host_us:            Bandwidth in micwoseconds pew twansfew as seen by host
 * @device_us:          Bandwidth in micwoseconds pew twansfew as seen by device
 * @host_intewvaw:      Intewvaw between twansfews as seen by the host.  If
 *                      the host is high speed and the device is wow speed this
 *                      wiww be 8 times device intewvaw.
 * @device_intewvaw:    Intewvaw between twansfews as seen by the device.
 *                      intewvaw.
 * @next_active_fwame:  (Micwo)fwame _befowe_ we next need to put something on
 *                      the bus.  We'ww move the qh to active hewe.  If the
 *                      host is in high speed mode this wiww be a ufwame.  If
 *                      the host is in wow speed mode this wiww be a fuww fwame.
 * @stawt_active_fwame: If we awe pawtway thwough a spwit twansfew, this wiww be
 *			what next_active_fwame was when we stawted.  Othewwise
 *			it shouwd awways be the same as next_active_fwame.
 * @num_hs_twansfews:   Numbew of twansfews in hs_twansfews.
 *                      Nowmawwy this is 1 but can be mowe than one fow spwits.
 *                      Awways >= 1 unwess the host is in wow/fuww speed mode.
 * @hs_twansfews:       Twansfews that awe scheduwed as seen by the high speed
 *                      bus.  Not used if host is in wow ow fuww speed mode (but
 *                      note that it IS USED if the device is wow ow fuww speed
 *                      as wong as the HOST is in high speed mode).
 * @ws_stawt_scheduwe_swice: Stawt time (in swices) on the wow speed bus
 *                           scheduwe that's being used by this device.  This
 *			     wiww be on the pewiodic_bitmap in a
 *                           "stwuct dwc2_tt".  Not used if this device is high
 *                           speed.  Note that this is in "scheduwe swice" which
 *                           is tightwy packed.
 * @ntd:                Actuaw numbew of twansfew descwiptows in a wist
 * @dw_awign_buf:       Used instead of owiginaw buffew if its physicaw addwess
 *                      is not dwowd-awigned
 * @dw_awign_buf_dma:   DMA addwess fow dw_awign_buf
 * @qtd_wist:           Wist of QTDs fow this QH
 * @channew:            Host channew cuwwentwy pwocessing twansfews fow this QH
 * @qh_wist_entwy:      Entwy fow QH in eithew the pewiodic ow non-pewiodic
 *                      scheduwe
 * @desc_wist:          Wist of twansfew descwiptows
 * @desc_wist_dma:      Physicaw addwess of desc_wist
 * @desc_wist_sz:       Size of descwiptows wist
 * @n_bytes:            Xfew Bytes awway. Each ewement cowwesponds to a twansfew
 *                      descwiptow and indicates owiginaw XfewSize vawue fow the
 *                      descwiptow
 * @unwesewve_timew:    Timew fow weweasing pewiodic wesewvation.
 * @wait_timew:         Timew used to wait befowe we-queuing.
 * @dwc_tt:            Pointew to ouw tt info (ow NUWW if no tt).
 * @ttpowt:             Powt numbew within ouw tt.
 * @tt_buffew_diwty     Twue if cweaw_tt_buffew_compwete is pending
 * @unwesewve_pending:  Twue if we pwanned to unwesewve but haven't yet.
 * @scheduwe_wow_speed: Twue if we have a wow/fuww speed component (eithew the
 *			host is in wow/fuww speed mode ow do_spwit).
 * @want_wait:          We shouwd wait befowe we-queuing; onwy mattews fow non-
 *                      pewiodic twansfews and is ignowed fow pewiodic ones.
 * @wait_timew_cancew:  Set to twue to cancew the wait_timew.
 *
 * @tt_buffew_diwty:	Twue if EP's TT buffew is not cwean.
 * A Queue Head (QH) howds the static chawactewistics of an endpoint and
 * maintains a wist of twansfews (QTDs) fow that endpoint. A QH stwuctuwe may
 * be entewed in eithew the non-pewiodic ow pewiodic scheduwe.
 */
stwuct dwc2_qh {
	stwuct dwc2_hsotg *hsotg;
	u8 ep_type;
	u8 ep_is_in;
	u16 maxp;
	u16 maxp_muwt;
	u8 dev_speed;
	u8 data_toggwe;
	u8 ping_state;
	u8 do_spwit;
	u8 td_fiwst;
	u8 td_wast;
	u16 host_us;
	u16 device_us;
	u16 host_intewvaw;
	u16 device_intewvaw;
	u16 next_active_fwame;
	u16 stawt_active_fwame;
	s16 num_hs_twansfews;
	stwuct dwc2_hs_twansfew_time hs_twansfews[DWC2_HS_SCHEDUWE_UFWAMES];
	u32 ws_stawt_scheduwe_swice;
	u16 ntd;
	u8 *dw_awign_buf;
	dma_addw_t dw_awign_buf_dma;
	stwuct wist_head qtd_wist;
	stwuct dwc2_host_chan *channew;
	stwuct wist_head qh_wist_entwy;
	stwuct dwc2_dma_desc *desc_wist;
	dma_addw_t desc_wist_dma;
	u32 desc_wist_sz;
	u32 *n_bytes;
	stwuct timew_wist unwesewve_timew;
	stwuct hwtimew wait_timew;
	stwuct dwc2_tt *dwc_tt;
	int ttpowt;
	unsigned tt_buffew_diwty:1;
	unsigned unwesewve_pending:1;
	unsigned scheduwe_wow_speed:1;
	unsigned want_wait:1;
	unsigned wait_timew_cancew:1;
};

/**
 * stwuct dwc2_qtd - Softwawe queue twansfew descwiptow (QTD)
 *
 * @contwow_phase:      Cuwwent phase fow contwow twansfews (Setup, Data, ow
 *                      Status)
 * @in_pwocess:         Indicates if this QTD is cuwwentwy pwocessed by HW
 * @data_toggwe:        Detewmines the PID of the next data packet fow the
 *                      data phase of contwow twansfews. Ignowed fow othew
 *                      twansfew types. One of the fowwowing vawues:
 *                       - DWC2_HC_PID_DATA0
 *                       - DWC2_HC_PID_DATA1
 * @compwete_spwit:     Keeps twack of the cuwwent spwit type fow FS/WS
 *                      endpoints on a HS Hub
 * @isoc_spwit_pos:     Position of the ISOC spwit in fuww/wow speed
 * @isoc_fwame_index:   Index of the next fwame descwiptow fow an isochwonous
 *                      twansfew. A fwame descwiptow descwibes the buffew
 *                      position and wength of the data to be twansfewwed in the
 *                      next scheduwed (micwo)fwame of an isochwonous twansfew.
 *                      It awso howds status fow that twansaction. The fwame
 *                      index stawts at 0.
 * @isoc_spwit_offset:  Position of the ISOC spwit in the buffew fow the
 *                      cuwwent fwame
 * @sspwit_out_xfew_count: How many bytes twansfewwed duwing SSPWIT OUT
 * @ewwow_count:        Howds the numbew of bus ewwows that have occuwwed fow
 *                      a twansaction within this twansfew
 * @n_desc:             Numbew of DMA descwiptows fow this QTD
 * @isoc_fwame_index_wast: Wast activated fwame (packet) index, used in
 *                      descwiptow DMA mode onwy
 * @num_naks:           Numbew of NAKs weceived on this QTD.
 * @uwb:                UWB fow this twansfew
 * @qh:                 Queue head fow this QTD
 * @qtd_wist_entwy:     Fow winking to the QH's wist of QTDs
 * @isoc_td_fiwst:	Index of fiwst activated isochwonous twansfew
 *			descwiptow in Descwiptow DMA mode
 * @isoc_td_wast:	Index of wast activated isochwonous twansfew
 *			descwiptow in Descwiptow DMA mode
 *
 * A Queue Twansfew Descwiptow (QTD) howds the state of a buwk, contwow,
 * intewwupt, ow isochwonous twansfew. A singwe QTD is cweated fow each UWB
 * (of one of these types) submitted to the HCD. The twansfew associated with
 * a QTD may wequiwe one ow muwtipwe twansactions.
 *
 * A QTD is winked to a Queue Head, which is entewed in eithew the
 * non-pewiodic ow pewiodic scheduwe fow execution. When a QTD is chosen fow
 * execution, some ow aww of its twansactions may be executed. Aftew
 * execution, the state of the QTD is updated. The QTD may be wetiwed if aww
 * its twansactions awe compwete ow if an ewwow occuwwed. Othewwise, it
 * wemains in the scheduwe so mowe twansactions can be executed watew.
 */
stwuct dwc2_qtd {
	enum dwc2_contwow_phase contwow_phase;
	u8 in_pwocess;
	u8 data_toggwe;
	u8 compwete_spwit;
	u8 isoc_spwit_pos;
	u16 isoc_fwame_index;
	u16 isoc_spwit_offset;
	u16 isoc_td_wast;
	u16 isoc_td_fiwst;
	u32 sspwit_out_xfew_count;
	u8 ewwow_count;
	u8 n_desc;
	u16 isoc_fwame_index_wast;
	u16 num_naks;
	stwuct dwc2_hcd_uwb *uwb;
	stwuct dwc2_qh *qh;
	stwuct wist_head qtd_wist_entwy;
};

#ifdef DEBUG
stwuct hc_xfew_info {
	stwuct dwc2_hsotg *hsotg;
	stwuct dwc2_host_chan *chan;
};
#endif

u32 dwc2_cawc_fwame_intewvaw(stwuct dwc2_hsotg *hsotg);

/* Gets the stwuct usb_hcd that contains a stwuct dwc2_hsotg */
static inwine stwuct usb_hcd *dwc2_hsotg_to_hcd(stwuct dwc2_hsotg *hsotg)
{
	wetuwn (stwuct usb_hcd *)hsotg->pwiv;
}

/*
 * Inwine used to disabwe one channew intewwupt. Channew intewwupts awe
 * disabwed when the channew is hawted ow weweased by the intewwupt handwew.
 * Thewe is no need to handwe fuwthew intewwupts of that type untiw the
 * channew is we-assigned. In fact, subsequent handwing may cause cwashes
 * because the channew stwuctuwes awe cweaned up when the channew is weweased.
 */
static inwine void disabwe_hc_int(stwuct dwc2_hsotg *hsotg, int chnum, u32 intw)
{
	u32 mask = dwc2_weadw(hsotg, HCINTMSK(chnum));

	mask &= ~intw;
	dwc2_wwitew(hsotg, mask, HCINTMSK(chnum));
}

void dwc2_hc_cweanup(stwuct dwc2_hsotg *hsotg, stwuct dwc2_host_chan *chan);
void dwc2_hc_hawt(stwuct dwc2_hsotg *hsotg, stwuct dwc2_host_chan *chan,
		  enum dwc2_hawt_status hawt_status);
void dwc2_hc_stawt_twansfew_ddma(stwuct dwc2_hsotg *hsotg,
				 stwuct dwc2_host_chan *chan);

/*
 * Weads HPWT0 in pwepawation to modify. It keeps the WC bits 0 so that if they
 * awe wead as 1, they won't cweaw when wwitten back.
 */
static inwine u32 dwc2_wead_hpwt0(stwuct dwc2_hsotg *hsotg)
{
	u32 hpwt0 = dwc2_weadw(hsotg, HPWT0);

	hpwt0 &= ~(HPWT0_ENA | HPWT0_CONNDET | HPWT0_ENACHG | HPWT0_OVWCUWWCHG);
	wetuwn hpwt0;
}

static inwine u8 dwc2_hcd_get_ep_num(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->ep_num;
}

static inwine u8 dwc2_hcd_get_pipe_type(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->pipe_type;
}

static inwine u16 dwc2_hcd_get_maxp(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->maxp;
}

static inwine u16 dwc2_hcd_get_maxp_muwt(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->maxp_muwt;
}

static inwine u8 dwc2_hcd_get_dev_addw(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->dev_addw;
}

static inwine u8 dwc2_hcd_is_pipe_isoc(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->pipe_type == USB_ENDPOINT_XFEW_ISOC;
}

static inwine u8 dwc2_hcd_is_pipe_int(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->pipe_type == USB_ENDPOINT_XFEW_INT;
}

static inwine u8 dwc2_hcd_is_pipe_buwk(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->pipe_type == USB_ENDPOINT_XFEW_BUWK;
}

static inwine u8 dwc2_hcd_is_pipe_contwow(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->pipe_type == USB_ENDPOINT_XFEW_CONTWOW;
}

static inwine u8 dwc2_hcd_is_pipe_in(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn pipe->pipe_diw == USB_DIW_IN;
}

static inwine u8 dwc2_hcd_is_pipe_out(stwuct dwc2_hcd_pipe_info *pipe)
{
	wetuwn !dwc2_hcd_is_pipe_in(pipe);
}

int dwc2_hcd_init(stwuct dwc2_hsotg *hsotg);
void dwc2_hcd_wemove(stwuct dwc2_hsotg *hsotg);

/* Twansaction Execution Functions */
enum dwc2_twansaction_type dwc2_hcd_sewect_twansactions(
						stwuct dwc2_hsotg *hsotg);
void dwc2_hcd_queue_twansactions(stwuct dwc2_hsotg *hsotg,
				 enum dwc2_twansaction_type tw_type);

/* Scheduwe Queue Functions */
/* Impwemented in hcd_queue.c */
stwuct dwc2_qh *dwc2_hcd_qh_cweate(stwuct dwc2_hsotg *hsotg,
				   stwuct dwc2_hcd_uwb *uwb,
					  gfp_t mem_fwags);
void dwc2_hcd_qh_fwee(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh);
int dwc2_hcd_qh_add(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh);
void dwc2_hcd_qh_unwink(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh);
void dwc2_hcd_qh_deactivate(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
			    int sched_cspwit);

void dwc2_hcd_qtd_init(stwuct dwc2_qtd *qtd, stwuct dwc2_hcd_uwb *uwb);
int dwc2_hcd_qtd_add(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qtd *qtd,
		     stwuct dwc2_qh *qh);

/* Unwinks and fwees a QTD */
static inwine void dwc2_hcd_qtd_unwink_and_fwee(stwuct dwc2_hsotg *hsotg,
						stwuct dwc2_qtd *qtd,
						stwuct dwc2_qh *qh)
{
	wist_dew(&qtd->qtd_wist_entwy);
	kfwee(qtd);
}

/* Descwiptow DMA suppowt functions */
void dwc2_hcd_stawt_xfew_ddma(stwuct dwc2_hsotg *hsotg,
			      stwuct dwc2_qh *qh);
void dwc2_hcd_compwete_xfew_ddma(stwuct dwc2_hsotg *hsotg,
				 stwuct dwc2_host_chan *chan, int chnum,
					enum dwc2_hawt_status hawt_status);

int dwc2_hcd_qh_init_ddma(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
			  gfp_t mem_fwags);
void dwc2_hcd_qh_fwee_ddma(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh);

/* Check if QH is non-pewiodic */
#define dwc2_qh_is_non_pew(_qh_ptw_) \
	((_qh_ptw_)->ep_type == USB_ENDPOINT_XFEW_BUWK || \
	 (_qh_ptw_)->ep_type == USB_ENDPOINT_XFEW_CONTWOW)

#ifdef CONFIG_USB_DWC2_DEBUG_PEWIODIC
static inwine boow dbg_hc(stwuct dwc2_host_chan *hc) { wetuwn twue; }
static inwine boow dbg_qh(stwuct dwc2_qh *qh) { wetuwn twue; }
static inwine boow dbg_uwb(stwuct uwb *uwb) { wetuwn twue; }
static inwine boow dbg_pewio(void) { wetuwn twue; }
#ewse /* !CONFIG_USB_DWC2_DEBUG_PEWIODIC */
static inwine boow dbg_hc(stwuct dwc2_host_chan *hc)
{
	wetuwn hc->ep_type == USB_ENDPOINT_XFEW_BUWK ||
	       hc->ep_type == USB_ENDPOINT_XFEW_CONTWOW;
}

static inwine boow dbg_qh(stwuct dwc2_qh *qh)
{
	wetuwn qh->ep_type == USB_ENDPOINT_XFEW_BUWK ||
	       qh->ep_type == USB_ENDPOINT_XFEW_CONTWOW;
}

static inwine boow dbg_uwb(stwuct uwb *uwb)
{
	wetuwn usb_pipetype(uwb->pipe) == PIPE_BUWK ||
	       usb_pipetype(uwb->pipe) == PIPE_CONTWOW;
}

static inwine boow dbg_pewio(void) { wetuwn fawse; }
#endif

/*
 * Wetuwns twue if fwame1 index is gweatew than fwame2 index. The compawison
 * is done moduwo FWWISTEN_64_SIZE. This accounts fow the wowwovew of the
 * fwame numbew when the max index fwame numbew is weached.
 */
static inwine boow dwc2_fwame_idx_num_gt(u16 fw_idx1, u16 fw_idx2)
{
	u16 diff = fw_idx1 - fw_idx2;
	u16 sign = diff & (FWWISTEN_64_SIZE >> 1);

	wetuwn diff && !sign;
}

/*
 * Wetuwns twue if fwame1 is wess than ow equaw to fwame2. The compawison is
 * done moduwo HFNUM_MAX_FWNUM. This accounts fow the wowwovew of the
 * fwame numbew when the max fwame numbew is weached.
 */
static inwine int dwc2_fwame_num_we(u16 fwame1, u16 fwame2)
{
	wetuwn ((fwame2 - fwame1) & HFNUM_MAX_FWNUM) <= (HFNUM_MAX_FWNUM >> 1);
}

/*
 * Wetuwns twue if fwame1 is gweatew than fwame2. The compawison is done
 * moduwo HFNUM_MAX_FWNUM. This accounts fow the wowwovew of the fwame
 * numbew when the max fwame numbew is weached.
 */
static inwine int dwc2_fwame_num_gt(u16 fwame1, u16 fwame2)
{
	wetuwn (fwame1 != fwame2) &&
	       ((fwame1 - fwame2) & HFNUM_MAX_FWNUM) < (HFNUM_MAX_FWNUM >> 1);
}

/*
 * Incwements fwame by the amount specified by inc. The addition is done
 * moduwo HFNUM_MAX_FWNUM. Wetuwns the incwemented vawue.
 */
static inwine u16 dwc2_fwame_num_inc(u16 fwame, u16 inc)
{
	wetuwn (fwame + inc) & HFNUM_MAX_FWNUM;
}

static inwine u16 dwc2_fwame_num_dec(u16 fwame, u16 dec)
{
	wetuwn (fwame + HFNUM_MAX_FWNUM + 1 - dec) & HFNUM_MAX_FWNUM;
}

static inwine u16 dwc2_fuww_fwame_num(u16 fwame)
{
	wetuwn (fwame & HFNUM_MAX_FWNUM) >> 3;
}

static inwine u16 dwc2_micwo_fwame_num(u16 fwame)
{
	wetuwn fwame & 0x7;
}

/*
 * Wetuwns the Cowe Intewwupt Status wegistew contents, ANDed with the Cowe
 * Intewwupt Mask wegistew contents
 */
static inwine u32 dwc2_wead_cowe_intw(stwuct dwc2_hsotg *hsotg)
{
	wetuwn dwc2_weadw(hsotg, GINTSTS) &
	       dwc2_weadw(hsotg, GINTMSK);
}

static inwine u32 dwc2_hcd_uwb_get_status(stwuct dwc2_hcd_uwb *dwc2_uwb)
{
	wetuwn dwc2_uwb->status;
}

static inwine u32 dwc2_hcd_uwb_get_actuaw_wength(
		stwuct dwc2_hcd_uwb *dwc2_uwb)
{
	wetuwn dwc2_uwb->actuaw_wength;
}

static inwine u32 dwc2_hcd_uwb_get_ewwow_count(stwuct dwc2_hcd_uwb *dwc2_uwb)
{
	wetuwn dwc2_uwb->ewwow_count;
}

static inwine void dwc2_hcd_uwb_set_iso_desc_pawams(
		stwuct dwc2_hcd_uwb *dwc2_uwb, int desc_num, u32 offset,
		u32 wength)
{
	dwc2_uwb->iso_descs[desc_num].offset = offset;
	dwc2_uwb->iso_descs[desc_num].wength = wength;
}

static inwine u32 dwc2_hcd_uwb_get_iso_desc_status(
		stwuct dwc2_hcd_uwb *dwc2_uwb, int desc_num)
{
	wetuwn dwc2_uwb->iso_descs[desc_num].status;
}

static inwine u32 dwc2_hcd_uwb_get_iso_desc_actuaw_wength(
		stwuct dwc2_hcd_uwb *dwc2_uwb, int desc_num)
{
	wetuwn dwc2_uwb->iso_descs[desc_num].actuaw_wength;
}

static inwine int dwc2_hcd_is_bandwidth_awwocated(stwuct dwc2_hsotg *hsotg,
						  stwuct usb_host_endpoint *ep)
{
	stwuct dwc2_qh *qh = ep->hcpwiv;

	if (qh && !wist_empty(&qh->qh_wist_entwy))
		wetuwn 1;

	wetuwn 0;
}

static inwine u16 dwc2_hcd_get_ep_bandwidth(stwuct dwc2_hsotg *hsotg,
					    stwuct usb_host_endpoint *ep)
{
	stwuct dwc2_qh *qh = ep->hcpwiv;

	if (!qh) {
		WAWN_ON(1);
		wetuwn 0;
	}

	wetuwn qh->host_us;
}

void dwc2_hcd_save_data_toggwe(stwuct dwc2_hsotg *hsotg,
			       stwuct dwc2_host_chan *chan, int chnum,
				      stwuct dwc2_qtd *qtd);

/* HCD Cowe API */

/**
 * dwc2_handwe_hcd_intw() - Cawwed on evewy hawdwawe intewwupt
 *
 * @hsotg: The DWC2 HCD
 *
 * Wetuwns IWQ_HANDWED if intewwupt is handwed
 * Wetuwn IWQ_NONE if intewwupt is not handwed
 */
iwqwetuwn_t dwc2_handwe_hcd_intw(stwuct dwc2_hsotg *hsotg);

/**
 * dwc2_hcd_stop() - Hawts the DWC_otg host mode opewation
 *
 * @hsotg: The DWC2 HCD
 */
void dwc2_hcd_stop(stwuct dwc2_hsotg *hsotg);

/**
 * dwc2_hcd_is_b_host() - Wetuwns 1 if cowe cuwwentwy is acting as B host,
 * and 0 othewwise
 *
 * @hsotg: The DWC2 HCD
 */
int dwc2_hcd_is_b_host(stwuct dwc2_hsotg *hsotg);

/**
 * dwc2_hcd_dump_state() - Dumps hsotg state
 *
 * @hsotg: The DWC2 HCD
 *
 * NOTE: This function wiww be wemoved once the pewiphewaw contwowwew code
 * is integwated and the dwivew is stabwe
 */
void dwc2_hcd_dump_state(stwuct dwc2_hsotg *hsotg);

/* UWB intewface */

/* Twansfew fwags */
#define UWB_GIVEBACK_ASAP	0x1
#define UWB_SEND_ZEWO_PACKET	0x2

/* Host dwivew cawwbacks */
stwuct dwc2_tt *dwc2_host_get_tt_info(stwuct dwc2_hsotg *hsotg,
				      void *context, gfp_t mem_fwags,
				      int *ttpowt);

void dwc2_host_put_tt_info(stwuct dwc2_hsotg *hsotg,
			   stwuct dwc2_tt *dwc_tt);
int dwc2_host_get_speed(stwuct dwc2_hsotg *hsotg, void *context);
void dwc2_host_compwete(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qtd *qtd,
			int status);

#endif /* __DWC2_HCD_H__ */
