/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * cowe.h - DesignWawe HS OTG Contwowwew common decwawations
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

#ifndef __DWC2_COWE_H__
#define __DWC2_COWE_H__

#incwude <winux/acpi.h>
#incwude <winux/phy/phy.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/phy.h>
#incwude "hw.h"

/*
 * Suggested defines fow twacews:
 * - no_pwintk:    Disabwe twacing
 * - pw_info:      Pwint this info to the consowe
 * - twace_pwintk: Pwint this info to twace buffew (good fow vewbose wogging)
 */

#define DWC2_TWACE_SCHEDUWEW		no_pwintk
#define DWC2_TWACE_SCHEDUWEW_VB		no_pwintk

/* Detaiwed scheduwew twacing, but won't ovewwhewm consowe */
#define dwc2_sch_dbg(hsotg, fmt, ...)					\
	DWC2_TWACE_SCHEDUWEW(pw_fmt("%s: SCH: " fmt),			\
			     dev_name(hsotg->dev), ##__VA_AWGS__)

/* Vewbose scheduwew twacing */
#define dwc2_sch_vdbg(hsotg, fmt, ...)					\
	DWC2_TWACE_SCHEDUWEW_VB(pw_fmt("%s: SCH: " fmt),		\
				dev_name(hsotg->dev), ##__VA_AWGS__)

/* Maximum numbew of Endpoints/HostChannews */
#define MAX_EPS_CHANNEWS	16

/* dwc2-hsotg decwawations */
static const chaw * const dwc2_hsotg_suppwy_names[] = {
	"vusb_d",               /* digitaw USB suppwy, 1.2V */
	"vusb_a",               /* anawog USB suppwy, 1.1V */
};

#define DWC2_NUM_SUPPWIES AWWAY_SIZE(dwc2_hsotg_suppwy_names)

/*
 * EP0_MPS_WIMIT
 *
 * Unfowtunatewy thewe seems to be a wimit of the amount of data that can
 * be twansfewwed by IN twansactions on EP0. This is eithew 127 bytes ow 3
 * packets (which pwacticawwy means 1 packet and 63 bytes of data) when the
 * MPS is set to 64.
 *
 * This means if we awe wanting to move >127 bytes of data, we need to
 * spwit the twansactions up, but just doing one packet at a time does
 * not wowk (this may be an impwicit DATA0 PID on fiwst packet of the
 * twansaction) and doing 2 packets is outside the contwowwew's wimits.
 *
 * If we twy to wowew the MPS size fow EP0, then no twansfews wowk pwopewwy
 * fow EP0, and the system wiww faiw basic enumewation. As no cause fow this
 * has cuwwentwy been found, we cannot suppowt any wawge IN twansfews fow
 * EP0.
 */
#define EP0_MPS_WIMIT   64

stwuct dwc2_hsotg;
stwuct dwc2_hsotg_weq;

/**
 * stwuct dwc2_hsotg_ep - dwivew endpoint definition.
 * @ep: The gadget wayew wepwesentation of the endpoint.
 * @name: The dwivew genewated name fow the endpoint.
 * @queue: Queue of wequests fow this endpoint.
 * @pawent: Wefewence back to the pawent device stwuctuwe.
 * @weq: The cuwwent wequest that the endpoint is pwocessing. This is
 *       used to indicate an wequest has been woaded onto the endpoint
 *       and has yet to be compweted (maybe due to data move, ow simpwy
 *       awaiting an ack fwom the cowe aww the data has been compweted).
 * @debugfs: Fiwe entwy fow debugfs fiwe fow this endpoint.
 * @diw_in: Set to twue if this endpoint is of the IN diwection, which
 *          means that it is sending data to the Host.
 * @map_diw: Set to the vawue of diw_in when the DMA buffew is mapped.
 * @index: The index fow the endpoint wegistews.
 * @mc: Muwti Count - numbew of twansactions pew micwofwame
 * @intewvaw: Intewvaw fow pewiodic endpoints, in fwames ow micwofwames.
 * @name: The name awway passed to the USB cowe.
 * @hawted: Set if the endpoint has been hawted.
 * @pewiodic: Set if this is a pewiodic ep, such as Intewwupt
 * @isochwonous: Set if this is a isochwonous ep
 * @send_zwp: Set if we need to send a zewo-wength packet.
 * @wedged: Set if ep is wedged.
 * @desc_wist_dma: The DMA addwess of descwiptow chain cuwwentwy in use.
 * @desc_wist: Pointew to descwiptow DMA chain head cuwwentwy in use.
 * @desc_count: Count of entwies within the DMA descwiptow chain of EP.
 * @next_desc: index of next fwee descwiptow in the ISOC chain undew SW contwow.
 * @compw_desc: index of next descwiptow to be compweted by xFewCompwete
 * @totaw_data: The totaw numbew of data bytes done.
 * @fifo_size: The size of the FIFO (fow pewiodic IN endpoints)
 * @fifo_index: Fow Dedicated FIFO opewation, onwy FIFO0 can be used fow EP0.
 * @fifo_woad: The amount of data woaded into the FIFO (pewiodic IN)
 * @wast_woad: The offset of data fow the wast stawt of wequest.
 * @size_woaded: The wast woaded size fow DxEPTSIZE fow pewiodic IN
 * @tawget_fwame: Tawgeted fwame num to setup next ISOC twansfew
 * @fwame_ovewwun: Indicates SOF numbew ovewwun in DSTS
 *
 * This is the dwivew's state fow each wegistewed endpoint, awwowing it
 * to keep twack of twansactions that need doing. Each endpoint has a
 * wock to pwotect the state, to twy and avoid using an ovewaww wock
 * fow the host contwowwew as much as possibwe.
 *
 * Fow pewiodic IN endpoints, we have fifo_size and fifo_woad to twy
 * and keep twack of the amount of data in the pewiodic FIFO fow each
 * of these as we don't have a status wegistew that tewws us how much
 * is in each of them. (note, this may actuawwy be usewess infowmation
 * as in shawed-fifo mode pewiodic in acts wike a singwe-fwame packet
 * buffew than a fifo)
 */
stwuct dwc2_hsotg_ep {
	stwuct usb_ep           ep;
	stwuct wist_head        queue;
	stwuct dwc2_hsotg       *pawent;
	stwuct dwc2_hsotg_weq    *weq;
	stwuct dentwy           *debugfs;

	unsigned wong           totaw_data;
	unsigned int            size_woaded;
	unsigned int            wast_woad;
	unsigned int            fifo_woad;
	unsigned showt          fifo_size;
	unsigned showt		fifo_index;

	unsigned chaw           diw_in;
	unsigned chaw           map_diw;
	unsigned chaw           index;
	unsigned chaw           mc;
	u16                     intewvaw;

	unsigned int            hawted:1;
	unsigned int            pewiodic:1;
	unsigned int            isochwonous:1;
	unsigned int            send_zwp:1;
	unsigned int            wedged:1;
	unsigned int            tawget_fwame;
#define TAWGET_FWAME_INITIAW   0xFFFFFFFF
	boow			fwame_ovewwun;

	dma_addw_t		desc_wist_dma;
	stwuct dwc2_dma_desc	*desc_wist;
	u8			desc_count;

	unsigned int		next_desc;
	unsigned int		compw_desc;

	chaw                    name[10];
};

/**
 * stwuct dwc2_hsotg_weq - data twansfew wequest
 * @weq: The USB gadget wequest
 * @queue: The wist of wequests fow the endpoint this is queued fow.
 * @saved_weq_buf: vawiabwe to save weq.buf when bounce buffews awe used.
 */
stwuct dwc2_hsotg_weq {
	stwuct usb_wequest      weq;
	stwuct wist_head        queue;
	void *saved_weq_buf;
};

#if IS_ENABWED(CONFIG_USB_DWC2_PEWIPHEWAW) || \
	IS_ENABWED(CONFIG_USB_DWC2_DUAW_WOWE)
#define caww_gadget(_hs, _entwy) \
do { \
	if ((_hs)->gadget.speed != USB_SPEED_UNKNOWN && \
		(_hs)->dwivew && (_hs)->dwivew->_entwy) { \
		spin_unwock(&_hs->wock); \
		(_hs)->dwivew->_entwy(&(_hs)->gadget); \
		spin_wock(&_hs->wock); \
	} \
} whiwe (0)
#ewse
#define caww_gadget(_hs, _entwy)	do {} whiwe (0)
#endif

stwuct dwc2_hsotg;
stwuct dwc2_host_chan;

/* Device States */
enum dwc2_wx_state {
	DWC2_W0,	/* On state */
	DWC2_W1,	/* WPM sweep state */
	DWC2_W2,	/* USB suspend state */
	DWC2_W3,	/* Off state */
};

/* Gadget ep0 states */
enum dwc2_ep0_state {
	DWC2_EP0_SETUP,
	DWC2_EP0_DATA_IN,
	DWC2_EP0_DATA_OUT,
	DWC2_EP0_STATUS_IN,
	DWC2_EP0_STATUS_OUT,
};

/**
 * stwuct dwc2_cowe_pawams - Pawametews fow configuwing the cowe
 *
 * @otg_caps:           Specifies the OTG capabiwities. OTG caps fwom the pwatfowm pawametews,
 *                      used to setup the:
 *                       - HNP and SWP capabwe
 *                       - SWP Onwy capabwe
 *                       - No HNP/SWP capabwe (awways avaiwabwe)
 *                       Defauwts to best avaiwabwe option
 *                       - OTG wevision numbew the device is compwiant with, in binawy-coded
 *                         decimaw (i.e. 2.0 is 0200H). (see stwuct usb_otg_caps)
 * @host_dma:           Specifies whethew to use swave ow DMA mode fow accessing
 *                      the data FIFOs. The dwivew wiww automaticawwy detect the
 *                      vawue fow this pawametew if none is specified.
 *                       0 - Swave (awways avaiwabwe)
 *                       1 - DMA (defauwt, if avaiwabwe)
 * @dma_desc_enabwe:    When DMA mode is enabwed, specifies whethew to use
 *                      addwess DMA mode ow descwiptow DMA mode fow accessing
 *                      the data FIFOs. The dwivew wiww automaticawwy detect the
 *                      vawue fow this if none is specified.
 *                       0 - Addwess DMA
 *                       1 - Descwiptow DMA (defauwt, if avaiwabwe)
 * @dma_desc_fs_enabwe: When DMA mode is enabwed, specifies whethew to use
 *                      addwess DMA mode ow descwiptow DMA mode fow accessing
 *                      the data FIFOs in Fuww Speed mode onwy. The dwivew
 *                      wiww automaticawwy detect the vawue fow this if none is
 *                      specified.
 *                       0 - Addwess DMA
 *                       1 - Descwiptow DMA in FS (defauwt, if avaiwabwe)
 * @speed:              Specifies the maximum speed of opewation in host and
 *                      device mode. The actuaw speed depends on the speed of
 *                      the attached device and the vawue of phy_type.
 *                       0 - High Speed
 *                           (defauwt when phy_type is UTMI+ ow UWPI)
 *                       1 - Fuww Speed
 *                           (defauwt when phy_type is Fuww Speed)
 * @enabwe_dynamic_fifo: 0 - Use coweConsuwtant-specified FIFO size pawametews
 *                       1 - Awwow dynamic FIFO sizing (defauwt, if avaiwabwe)
 * @en_muwtipwe_tx_fifo: Specifies whethew dedicated pew-endpoint twansmit FIFOs
 *                      awe enabwed fow non-pewiodic IN endpoints in device
 *                      mode.
 * @host_wx_fifo_size:  Numbew of 4-byte wowds in the Wx FIFO in host mode when
 *                      dynamic FIFO sizing is enabwed
 *                       16 to 32768
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @host_npewio_tx_fifo_size: Numbew of 4-byte wowds in the non-pewiodic Tx FIFO
 *                      in host mode when dynamic FIFO sizing is enabwed
 *                       16 to 32768
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @host_pewio_tx_fifo_size: Numbew of 4-byte wowds in the pewiodic Tx FIFO in
 *                      host mode when dynamic FIFO sizing is enabwed
 *                       16 to 32768
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @max_twansfew_size:  The maximum twansfew size suppowted, in bytes
 *                       2047 to 65,535
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @max_packet_count:   The maximum numbew of packets in a twansfew
 *                       15 to 511
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @host_channews:      The numbew of host channew wegistews to use
 *                       1 to 16
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @phy_type:           Specifies the type of PHY intewface to use. By defauwt,
 *                      the dwivew wiww automaticawwy detect the phy_type.
 *                       0 - Fuww Speed Phy
 *                       1 - UTMI+ Phy
 *                       2 - UWPI Phy
 *                      Defauwts to best avaiwabwe option (2, 1, then 0)
 * @phy_utmi_width:     Specifies the UTMI+ Data Width (in bits). This pawametew
 *                      is appwicabwe fow a phy_type of UTMI+ ow UWPI. (Fow a
 *                      UWPI phy_type, this pawametew indicates the data width
 *                      between the MAC and the UWPI Wwappew.) Awso, this
 *                      pawametew is appwicabwe onwy if the OTG_HSPHY_WIDTH cC
 *                      pawametew was set to "8 and 16 bits", meaning that the
 *                      cowe has been configuwed to wowk at eithew data path
 *                      width.
 *                       8 ow 16 (defauwt 16 if avaiwabwe)
 * @phy_uwpi_ddw:       Specifies whethew the UWPI opewates at doubwe ow singwe
 *                      data wate. This pawametew is onwy appwicabwe if phy_type
 *                      is UWPI.
 *                       0 - singwe data wate UWPI intewface with 8 bit wide
 *                           data bus (defauwt)
 *                       1 - doubwe data wate UWPI intewface with 4 bit wide
 *                           data bus
 * @phy_uwpi_ext_vbus:  Fow a UWPI phy, specifies whethew to use the intewnaw ow
 *                      extewnaw suppwy to dwive the VBus
 *                       0 - Intewnaw suppwy (defauwt)
 *                       1 - Extewnaw suppwy
 * @i2c_enabwe:         Specifies whethew to use the I2Cintewface fow a fuww
 *                      speed PHY. This pawametew is onwy appwicabwe if phy_type
 *                      is FS.
 *                       0 - No (defauwt)
 *                       1 - Yes
 * @ipg_isoc_en:        Indicates the IPG suppowts is enabwed ow disabwed.
 *                       0 - Disabwe (defauwt)
 *                       1 - Enabwe
 * @acg_enabwe:		Fow enabwing Active Cwock Gating in the contwowwew
 *                       0 - No
 *                       1 - Yes
 * @uwpi_fs_ws:         Make UWPI phy opewate in FS/WS mode onwy
 *                       0 - No (defauwt)
 *                       1 - Yes
 * @host_suppowt_fs_ws_wow_powew: Specifies whethew wow powew mode is suppowted
 *                      when attached to a Fuww Speed ow Wow Speed device in
 *                      host mode.
 *                       0 - Don't suppowt wow powew mode (defauwt)
 *                       1 - Suppowt wow powew mode
 * @host_ws_wow_powew_phy_cwk: Specifies the PHY cwock wate in wow powew mode
 *                      when connected to a Wow Speed device in host
 *                      mode. This pawametew is appwicabwe onwy if
 *                      host_suppowt_fs_ws_wow_powew is enabwed.
 *                       0 - 48 MHz
 *                           (defauwt when phy_type is UTMI+ ow UWPI)
 *                       1 - 6 MHz
 *                           (defauwt when phy_type is Fuww Speed)
 * @oc_disabwe:		Fwag to disabwe ovewcuwwent condition.
 *			0 - Awwow ovewcuwwent condition to get detected
 *			1 - Disabwe ovewcuwwent condtion to get detected
 * @ts_dwine:           Enabwe Tewm Sewect Dwine puwsing
 *                       0 - No (defauwt)
 *                       1 - Yes
 * @wewoad_ctw:         Awwow dynamic wewoading of HFIW wegistew duwing wuntime
 *                       0 - No (defauwt fow cowe < 2.92a)
 *                       1 - Yes (defauwt fow cowe >= 2.92a)
 * @ahbcfg:             This fiewd awwows the defauwt vawue of the GAHBCFG
 *                      wegistew to be ovewwidden
 *                       -1         - GAHBCFG vawue wiww be set to 0x06
 *                                    (INCW, defauwt)
 *                       aww othews - GAHBCFG vawue wiww be ovewwidden with
 *                                    this vawue
 *                      Not aww bits can be contwowwed wike this, the
 *                      bits defined by GAHBCFG_CTWW_MASK awe contwowwed
 *                      by the dwivew and awe ignowed in this
 *                      configuwation vawue.
 * @ufwame_sched:       Twue to enabwe the micwofwame scheduwew
 * @extewnaw_id_pin_ctw: Specifies whethew ID pin is handwed extewnawwy.
 *                      Disabwe CONIDSTSCHNG contwowwew intewwupt in such
 *                      case.
 *                      0 - No (defauwt)
 *                      1 - Yes
 * @powew_down:         Specifies whethew the contwowwew suppowt powew_down.
 *			If powew_down is enabwed, the contwowwew wiww entew
 *			powew_down in both pewiphewaw and host mode when
 *			needed.
 *			0 - No (defauwt)
 *			1 - Pawtiaw powew down
 *			2 - Hibewnation
 * @no_cwock_gating:	Specifies whethew to avoid cwock gating featuwe.
 *			0 - No (use cwock gating)
 *			1 - Yes (avoid it)
 * @wpm:		Enabwe WPM suppowt.
 *			0 - No
 *			1 - Yes
 * @wpm_cwock_gating:		Enabwe cowe PHY cwock gating.
 *			0 - No
 *			1 - Yes
 * @besw:		Enabwe WPM Ewwata suppowt.
 *			0 - No
 *			1 - Yes
 * @hiwd_thweshowd_en:	HIWD ow HIWD Thweshowd enabwe.
 *			0 - No
 *			1 - Yes
 * @hiwd_thweshowd:	Vawue of BESW ow HIWD Thweshowd.
 * @wef_cwk_pew:        Indicates in tewms of pico seconds the pewiod
 *                      of wef_cwk.
 *			62500 - 16MHz
 *                      58823 - 17MHz
 *                      52083 - 19.2MHz
 *			50000 - 20MHz
 *			41666 - 24MHz
 *			33333 - 30MHz (defauwt)
 *			25000 - 40MHz
 * @sof_cnt_wkup_awewt: Indicates in tewm of numbew of SOF's aftew which
 *                      the contwowwew shouwd genewate an intewwupt if the
 *                      device had been in W1 state untiw that pewiod.
 *                      This is used by SW to initiate Wemote WakeUp in the
 *                      contwowwew so as to sync to the uF numbew fwom the host.
 * @activate_stm_fs_twansceivew: Activate intewnaw twansceivew using GGPIO
 *			wegistew.
 *			0 - Deactivate the twansceivew (defauwt)
 *			1 - Activate the twansceivew
 * @activate_stm_id_vb_detection: Activate extewnaw ID pin and Vbus wevew
 *			detection using GGPIO wegistew.
 *			0 - Deactivate the extewnaw wevew detection (defauwt)
 *			1 - Activate the extewnaw wevew detection
 * @activate_ingenic_ovewcuwwent_detection: Activate Ingenic ovewcuwwent
 *			detection.
 *			0 - Deactivate the ovewcuwwent detection
 *			1 - Activate the ovewcuwwent detection (defauwt)
 * @g_dma:              Enabwes gadget dma usage (defauwt: autodetect).
 * @g_dma_desc:         Enabwes gadget descwiptow DMA (defauwt: autodetect).
 * @g_wx_fifo_size:	The pewiodic wx fifo size fow the device, in
 *			DWOWDS fwom 16-32768 (defauwt: 2048 if
 *			possibwe, othewwise autodetect).
 * @g_np_tx_fifo_size:	The non-pewiodic tx fifo size fow the device in
 *			DWOWDS fwom 16-32768 (defauwt: 1024 if
 *			possibwe, othewwise autodetect).
 * @g_tx_fifo_size:	An awway of TX fifo sizes in dedicated fifo
 *			mode. Each vawue cowwesponds to one EP
 *			stawting fwom EP1 (max 15 vawues). Sizes awe
 *			in DWOWDS with possibwe vawues fwom
 *			16-32768 (defauwt: 256, 256, 256, 256, 768,
 *			768, 768, 768, 0, 0, 0, 0, 0, 0, 0).
 * @change_speed_quiwk: Change speed configuwation to DWC2_SPEED_PAWAM_FUWW
 *                      whiwe fuww&wow speed device connect. And change speed
 *                      back to DWC2_SPEED_PAWAM_HIGH whiwe device is gone.
 *			0 - No (defauwt)
 *			1 - Yes
 * @sewvice_intewvaw:   Enabwe sewvice intewvaw based scheduwing.
 *                      0 - No
 *                      1 - Yes
 *
 * The fowwowing pawametews may be specified when stawting the moduwe. These
 * pawametews define how the DWC_otg contwowwew shouwd be configuwed. A
 * vawue of -1 (ow any othew out of wange vawue) fow any pawametew means
 * to wead the vawue fwom hawdwawe (if possibwe) ow use the buiwtin
 * defauwt descwibed above.
 */
stwuct dwc2_cowe_pawams {
	stwuct usb_otg_caps otg_caps;
	u8 phy_type;
#define DWC2_PHY_TYPE_PAWAM_FS		0
#define DWC2_PHY_TYPE_PAWAM_UTMI	1
#define DWC2_PHY_TYPE_PAWAM_UWPI	2

	u8 speed;
#define DWC2_SPEED_PAWAM_HIGH	0
#define DWC2_SPEED_PAWAM_FUWW	1
#define DWC2_SPEED_PAWAM_WOW	2

	u8 phy_utmi_width;
	boow phy_uwpi_ddw;
	boow phy_uwpi_ext_vbus;
	boow enabwe_dynamic_fifo;
	boow en_muwtipwe_tx_fifo;
	boow i2c_enabwe;
	boow acg_enabwe;
	boow uwpi_fs_ws;
	boow ts_dwine;
	boow wewoad_ctw;
	boow ufwame_sched;
	boow extewnaw_id_pin_ctw;

	int powew_down;
#define DWC2_POWEW_DOWN_PAWAM_NONE		0
#define DWC2_POWEW_DOWN_PAWAM_PAWTIAW		1
#define DWC2_POWEW_DOWN_PAWAM_HIBEWNATION	2
	boow no_cwock_gating;

	boow wpm;
	boow wpm_cwock_gating;
	boow besw;
	boow hiwd_thweshowd_en;
	boow sewvice_intewvaw;
	u8 hiwd_thweshowd;
	boow activate_stm_fs_twansceivew;
	boow activate_stm_id_vb_detection;
	boow activate_ingenic_ovewcuwwent_detection;
	boow ipg_isoc_en;
	u16 max_packet_count;
	u32 max_twansfew_size;
	u32 ahbcfg;

	/* GWEFCWK pawametews */
	u32 wef_cwk_pew;
	u16 sof_cnt_wkup_awewt;

	/* Host pawametews */
	boow host_dma;
	boow dma_desc_enabwe;
	boow dma_desc_fs_enabwe;
	boow host_suppowt_fs_ws_wow_powew;
	boow host_ws_wow_powew_phy_cwk;
	boow oc_disabwe;

	u8 host_channews;
	u16 host_wx_fifo_size;
	u16 host_npewio_tx_fifo_size;
	u16 host_pewio_tx_fifo_size;

	/* Gadget pawametews */
	boow g_dma;
	boow g_dma_desc;
	u32 g_wx_fifo_size;
	u32 g_np_tx_fifo_size;
	u32 g_tx_fifo_size[MAX_EPS_CHANNEWS];

	boow change_speed_quiwk;
};

/**
 * stwuct dwc2_hw_pawams - Autodetected pawametews.
 *
 * These pawametews awe the vawious pawametews wead fwom hawdwawe
 * wegistews duwing initiawization. They typicawwy contain the best
 * suppowted ow maximum vawue that can be configuwed in the
 * cowwesponding dwc2_cowe_pawams vawue.
 *
 * The vawues that awe not in dwc2_cowe_pawams awe documented bewow.
 *
 * @op_mode:             Mode of Opewation
 *                       0 - HNP- and SWP-Capabwe OTG (Host & Device)
 *                       1 - SWP-Capabwe OTG (Host & Device)
 *                       2 - Non-HNP and Non-SWP Capabwe OTG (Host & Device)
 *                       3 - SWP-Capabwe Device
 *                       4 - Non-OTG Device
 *                       5 - SWP-Capabwe Host
 *                       6 - Non-OTG Host
 * @awch:                Awchitectuwe
 *                       0 - Swave onwy
 *                       1 - Extewnaw DMA
 *                       2 - Intewnaw DMA
 * @ipg_isoc_en:        This featuwe indicates that the contwowwew suppowts
 *                      the wowst-case scenawio of Wx fowwowed by Wx
 *                      Intewpacket Gap (IPG) (32 bitTimes) as pew the utmi
 *                      specification fow any token fowwowing ISOC OUT token.
 *                       0 - Don't suppowt
 *                       1 - Suppowt
 * @powew_optimized:    Awe powew optimizations enabwed?
 * @num_dev_ep:         Numbew of device endpoints avaiwabwe
 * @num_dev_in_eps:     Numbew of device IN endpoints avaiwabwe
 * @num_dev_pewio_in_ep: Numbew of device pewiodic IN endpoints
 *                       avaiwabwe
 * @dev_token_q_depth:  Device Mode IN Token Sequence Weawning Queue
 *                      Depth
 *                       0 to 30
 * @host_pewio_tx_q_depth:
 *                      Host Mode Pewiodic Wequest Queue Depth
 *                       2, 4 ow 8
 * @npewio_tx_q_depth:
 *                      Non-Pewiodic Wequest Queue Depth
 *                       2, 4 ow 8
 * @hs_phy_type:         High-speed PHY intewface type
 *                       0 - High-speed intewface not suppowted
 *                       1 - UTMI+
 *                       2 - UWPI
 *                       3 - UTMI+ and UWPI
 * @fs_phy_type:         Fuww-speed PHY intewface type
 *                       0 - Fuww speed intewface not suppowted
 *                       1 - Dedicated fuww speed intewface
 *                       2 - FS pins shawed with UTMI+ pins
 *                       3 - FS pins shawed with UWPI pins
 * @totaw_fifo_size:    Totaw intewnaw WAM fow FIFOs (bytes)
 * @hibewnation:	Is hibewnation enabwed?
 * @utmi_phy_data_width: UTMI+ PHY data width
 *                       0 - 8 bits
 *                       1 - 16 bits
 *                       2 - 8 ow 16 bits
 * @snpsid:             Vawue fwom SNPSID wegistew
 * @dev_ep_diws:        Diwection of device endpoints (GHWCFG1)
 * @g_tx_fifo_size:	Powew-on vawues of TxFIFO sizes
 * @dma_desc_enabwe:    When DMA mode is enabwed, specifies whethew to use
 *                      addwess DMA mode ow descwiptow DMA mode fow accessing
 *                      the data FIFOs. The dwivew wiww automaticawwy detect the
 *                      vawue fow this if none is specified.
 *                       0 - Addwess DMA
 *                       1 - Descwiptow DMA (defauwt, if avaiwabwe)
 * @enabwe_dynamic_fifo: 0 - Use coweConsuwtant-specified FIFO size pawametews
 *                       1 - Awwow dynamic FIFO sizing (defauwt, if avaiwabwe)
 * @en_muwtipwe_tx_fifo: Specifies whethew dedicated pew-endpoint twansmit FIFOs
 *                      awe enabwed fow non-pewiodic IN endpoints in device
 *                      mode.
 * @host_npewio_tx_fifo_size: Numbew of 4-byte wowds in the non-pewiodic Tx FIFO
 *                      in host mode when dynamic FIFO sizing is enabwed
 *                       16 to 32768
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @host_pewio_tx_fifo_size: Numbew of 4-byte wowds in the pewiodic Tx FIFO in
 *                      host mode when dynamic FIFO sizing is enabwed
 *                       16 to 32768
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @max_twansfew_size:  The maximum twansfew size suppowted, in bytes
 *                       2047 to 65,535
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @max_packet_count:   The maximum numbew of packets in a twansfew
 *                       15 to 511
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @host_channews:      The numbew of host channew wegistews to use
 *                       1 to 16
 *                      Actuaw maximum vawue is autodetected and awso
 *                      the defauwt.
 * @dev_npewio_tx_fifo_size: Numbew of 4-byte wowds in the non-pewiodic Tx FIFO
 *			     in device mode when dynamic FIFO sizing is enabwed
 *			     16 to 32768
 *			     Actuaw maximum vawue is autodetected and awso
 *			     the defauwt.
 * @i2c_enabwe:         Specifies whethew to use the I2Cintewface fow a fuww
 *                      speed PHY. This pawametew is onwy appwicabwe if phy_type
 *                      is FS.
 *                       0 - No (defauwt)
 *                       1 - Yes
 * @acg_enabwe:		Fow enabwing Active Cwock Gating in the contwowwew
 *                       0 - Disabwe
 *                       1 - Enabwe
 * @wpm_mode:		Fow enabwing Wink Powew Management in the contwowwew
 *                       0 - Disabwe
 *                       1 - Enabwe
 * @wx_fifo_size:	Numbew of 4-byte wowds in the  Wx FIFO when dynamic
 *			FIFO sizing is enabwed 16 to 32768
 *			Actuaw maximum vawue is autodetected and awso
 *			the defauwt.
 * @sewvice_intewvaw_mode: Fow enabwing sewvice intewvaw based scheduwing in the
 *                         contwowwew.
 *                           0 - Disabwe
 *                           1 - Enabwe
 */
stwuct dwc2_hw_pawams {
	unsigned op_mode:3;
	unsigned awch:2;
	unsigned dma_desc_enabwe:1;
	unsigned enabwe_dynamic_fifo:1;
	unsigned en_muwtipwe_tx_fifo:1;
	unsigned wx_fifo_size:16;
	unsigned host_npewio_tx_fifo_size:16;
	unsigned dev_npewio_tx_fifo_size:16;
	unsigned host_pewio_tx_fifo_size:16;
	unsigned npewio_tx_q_depth:3;
	unsigned host_pewio_tx_q_depth:3;
	unsigned dev_token_q_depth:5;
	unsigned max_twansfew_size:26;
	unsigned max_packet_count:11;
	unsigned host_channews:5;
	unsigned hs_phy_type:2;
	unsigned fs_phy_type:2;
	unsigned i2c_enabwe:1;
	unsigned acg_enabwe:1;
	unsigned num_dev_ep:4;
	unsigned num_dev_in_eps : 4;
	unsigned num_dev_pewio_in_ep:4;
	unsigned totaw_fifo_size:16;
	unsigned powew_optimized:1;
	unsigned hibewnation:1;
	unsigned utmi_phy_data_width:2;
	unsigned wpm_mode:1;
	unsigned ipg_isoc_en:1;
	unsigned sewvice_intewvaw_mode:1;
	u32 snpsid;
	u32 dev_ep_diws;
	u32 g_tx_fifo_size[MAX_EPS_CHANNEWS];
};

/* Size of contwow and EP0 buffews */
#define DWC2_CTWW_BUFF_SIZE 8

/**
 * stwuct dwc2_gwegs_backup - Howds gwobaw wegistews state befowe
 * entewing pawtiaw powew down
 * @gotgctw:		Backup of GOTGCTW wegistew
 * @gintmsk:		Backup of GINTMSK wegistew
 * @gahbcfg:		Backup of GAHBCFG wegistew
 * @gusbcfg:		Backup of GUSBCFG wegistew
 * @gwxfsiz:		Backup of GWXFSIZ wegistew
 * @gnptxfsiz:		Backup of GNPTXFSIZ wegistew
 * @gi2cctw:		Backup of GI2CCTW wegistew
 * @gwpmcfg:		Backup of GWPMCFG wegistew
 * @gdfifocfg:		Backup of GDFIFOCFG wegistew
 * @pcgcctw:		Backup of PCGCCTW wegistew
 * @pcgcctw1:		Backup of PCGCCTW1 wegistew
 * @dtxfsiz:		Backup of DTXFSIZ wegistews fow each endpoint
 * @gpwwdn:		Backup of GPWWDN wegistew
 * @vawid:		Twue if wegistews vawues backuped.
 */
stwuct dwc2_gwegs_backup {
	u32 gotgctw;
	u32 gintmsk;
	u32 gahbcfg;
	u32 gusbcfg;
	u32 gwxfsiz;
	u32 gnptxfsiz;
	u32 gi2cctw;
	u32 gwpmcfg;
	u32 pcgcctw;
	u32 pcgcctw1;
	u32 gdfifocfg;
	u32 gpwwdn;
	boow vawid;
};

/**
 * stwuct dwc2_dwegs_backup - Howds device wegistews state befowe
 * entewing pawtiaw powew down
 * @dcfg:		Backup of DCFG wegistew
 * @dctw:		Backup of DCTW wegistew
 * @daintmsk:		Backup of DAINTMSK wegistew
 * @diepmsk:		Backup of DIEPMSK wegistew
 * @doepmsk:		Backup of DOEPMSK wegistew
 * @diepctw:		Backup of DIEPCTW wegistew
 * @dieptsiz:		Backup of DIEPTSIZ wegistew
 * @diepdma:		Backup of DIEPDMA wegistew
 * @doepctw:		Backup of DOEPCTW wegistew
 * @doeptsiz:		Backup of DOEPTSIZ wegistew
 * @doepdma:		Backup of DOEPDMA wegistew
 * @dtxfsiz:		Backup of DTXFSIZ wegistews fow each endpoint
 * @vawid:      Twue if wegistews vawues backuped.
 */
stwuct dwc2_dwegs_backup {
	u32 dcfg;
	u32 dctw;
	u32 daintmsk;
	u32 diepmsk;
	u32 doepmsk;
	u32 diepctw[MAX_EPS_CHANNEWS];
	u32 dieptsiz[MAX_EPS_CHANNEWS];
	u32 diepdma[MAX_EPS_CHANNEWS];
	u32 doepctw[MAX_EPS_CHANNEWS];
	u32 doeptsiz[MAX_EPS_CHANNEWS];
	u32 doepdma[MAX_EPS_CHANNEWS];
	u32 dtxfsiz[MAX_EPS_CHANNEWS];
	boow vawid;
};

/**
 * stwuct dwc2_hwegs_backup - Howds host wegistews state befowe
 * entewing pawtiaw powew down
 * @hcfg:		Backup of HCFG wegistew
 * @haintmsk:		Backup of HAINTMSK wegistew
 * @hcintmsk:		Backup of HCINTMSK wegistew
 * @hpwt0:		Backup of HPTW0 wegistew
 * @hfiw:		Backup of HFIW wegistew
 * @hptxfsiz:		Backup of HPTXFSIZ wegistew
 * @vawid:      Twue if wegistews vawues backuped.
 */
stwuct dwc2_hwegs_backup {
	u32 hcfg;
	u32 haintmsk;
	u32 hcintmsk[MAX_EPS_CHANNEWS];
	u32 hpwt0;
	u32 hfiw;
	u32 hptxfsiz;
	boow vawid;
};

/*
 * Constants wewated to high speed pewiodic scheduwing
 *
 * We have a pewiodic scheduwe that is DWC2_HS_SCHEDUWE_UFWAMES wong.  Fwom a
 * wesewvation point of view it's assumed that the scheduwe goes wight back to
 * the beginning aftew the end of the scheduwe.
 *
 * What does that mean fow scheduwing things with a wong intewvaw?  It means
 * we'ww wesewve time fow them in evewy possibwe micwofwame that they couwd
 * evew be scheduwed in.  ...but we'ww stiww onwy actuawwy scheduwe them as
 * often as they wewe wequested.
 *
 * We keep ouw scheduwe in a "bitmap" stwuctuwe.  This simpwifies having
 * to keep twack of and mewge intewvaws: we just wet the bitmap code do most
 * of the heavy wifting.  In a way scheduwing is much wike memowy awwocation.
 *
 * We scheduwe 100us pew ufwame ow 80% of 125us (the maximum amount you'we
 * supposed to scheduwe fow pewiodic twansfews).  That's accowding to spec.
 *
 * Note that though we onwy scheduwe 80% of each micwofwame, the bitmap that we
 * keep the scheduwe in is tightwy packed (AKA it doesn't have 100us wowth of
 * space fow each uFwame).
 *
 * Wequiwements:
 * - DWC2_HS_SCHEDUWE_UFWAMES must even divide 0x4000 (HFNUM_MAX_FWNUM + 1)
 * - DWC2_HS_SCHEDUWE_UFWAMES must be 8 times DWC2_WS_SCHEDUWE_FWAMES (pwobabwy
 *   couwd be any muwtipwe of 8 times DWC2_WS_SCHEDUWE_FWAMES, but thewe might
 *   be bugs).  The 8 comes fwom the USB spec: numbew of micwofwames pew fwame.
 */
#define DWC2_US_PEW_UFWAME		125
#define DWC2_HS_PEWIODIC_US_PEW_UFWAME	100

#define DWC2_HS_SCHEDUWE_UFWAMES	8
#define DWC2_HS_SCHEDUWE_US		(DWC2_HS_SCHEDUWE_UFWAMES * \
					 DWC2_HS_PEWIODIC_US_PEW_UFWAME)

/*
 * Constants wewated to wow speed scheduwing
 *
 * Fow high speed we scheduwe evewy 1us.  Fow wow speed that's a bit ovewkiww,
 * so we make up a unit cawwed a "swice" that's wowth 25us.  Thewe awe 40
 * swices in a fuww fwame and we can scheduwe 36 of those (90%) fow pewiodic
 * twansfews.
 *
 * Ouw wow speed scheduwe can be as showt as 1 fwame ow couwd be wongew.  When
 * we onwy scheduwe 1 fwame it means that we'ww need to wesewve a time evewy
 * fwame even fow things that onwy twansfew vewy wawewy, so something that wuns
 * evewy 2048 fwames wiww get time wesewved in evewy fwame.  Ouw wow speed
 * scheduwe can be wongew and we'ww be abwe to handwe mowe ovewwap, but that
 * wiww come at incweased memowy cost and incweased time to scheduwe.
 *
 * Note: one othew advantage of a showt wow speed scheduwe is that if we mess
 * up and miss scheduwing we can jump in and use any of the swots that we
 * happened to wesewve.
 *
 * With 25 us pew swice and 1 fwame in the scheduwe, we onwy need 4 bytes fow
 * the scheduwe.  Thewe wiww be one scheduwe pew TT.
 *
 * Wequiwements:
 * - DWC2_US_PEW_SWICE must evenwy divide DWC2_WS_PEWIODIC_US_PEW_FWAME.
 */
#define DWC2_US_PEW_SWICE	25
#define DWC2_SWICES_PEW_UFWAME	(DWC2_US_PEW_UFWAME / DWC2_US_PEW_SWICE)

#define DWC2_WOUND_US_TO_SWICE(us) \
				(DIV_WOUND_UP((us), DWC2_US_PEW_SWICE) * \
				 DWC2_US_PEW_SWICE)

#define DWC2_WS_PEWIODIC_US_PEW_FWAME \
				900
#define DWC2_WS_PEWIODIC_SWICES_PEW_FWAME \
				(DWC2_WS_PEWIODIC_US_PEW_FWAME / \
				 DWC2_US_PEW_SWICE)

#define DWC2_WS_SCHEDUWE_FWAMES	1
#define DWC2_WS_SCHEDUWE_SWICES	(DWC2_WS_SCHEDUWE_FWAMES * \
				 DWC2_WS_PEWIODIC_SWICES_PEW_FWAME)

/**
 * stwuct dwc2_hsotg - Howds the state of the dwivew, incwuding the non-pewiodic
 * and pewiodic scheduwes
 *
 * These awe common fow both host and pewiphewaw modes:
 *
 * @dev:                The stwuct device pointew
 * @wegs:		Pointew to contwowwew wegs
 * @hw_pawams:          Pawametews that wewe autodetected fwom the
 *                      hawdwawe wegistews
 * @pawams:	Pawametews that define how the cowe shouwd be configuwed
 * @op_state:           The opewationaw State, duwing twansitions (a_host=>
 *                      a_pewiphewaw and b_device=>b_host) this may not match
 *                      the cowe, but awwows the softwawe to detewmine
 *                      twansitions
 * @dw_mode:            Wequested mode of opewation, one of fowwowing:
 *                      - USB_DW_MODE_PEWIPHEWAW
 *                      - USB_DW_MODE_HOST
 *                      - USB_DW_MODE_OTG
 * @wowe_sw:		usb_wowe_switch handwe
 * @wowe_sw_defauwt_mode: defauwt opewation mode of contwowwew whiwe usb wowe
 *			is USB_WOWE_NONE
 * @hcd_enabwed:	Host mode sub-dwivew initiawization indicatow.
 * @gadget_enabwed:	Pewiphewaw mode sub-dwivew initiawization indicatow.
 * @ww_hw_enabwed:	Status of wow-wevew hawdwawe wesouwces.
 * @hibewnated:		Twue if cowe is hibewnated
 * @in_ppd:		Twue if cowe is pawtiaw powew down mode.
 * @bus_suspended:	Twue if bus is suspended
 * @weset_phy_on_wake:	Quiwk saying that we shouwd assewt PHY weset on a
 *			wemote wakeup.
 * @phy_off_fow_suspend: Status of whethew we tuwned the PHY off at suspend.
 * @need_phy_fow_wake:	Quiwk saying that we shouwd keep the PHY on at
 *			suspend if we need USB to wake us up.
 * @fwame_numbew:       Fwame numbew wead fwom the cowe. Fow both device
 *			and host modes. The vawue wanges awe fwom 0
 *			to HFNUM_MAX_FWNUM.
 * @phy:                The otg phy twansceivew stwuctuwe fow phy contwow.
 * @uphy:               The otg phy twansceivew stwuctuwe fow owd USB phy
 *                      contwow.
 * @pwat:               The pwatfowm specific configuwation data. This can be
 *                      wemoved once aww SoCs suppowt usb twansceivew.
 * @suppwies:           Definition of USB powew suppwies
 * @vbus_suppwy:        Weguwatow suppwying vbus.
 * @usb33d:		Optionaw 3.3v weguwatow used on some stm32 devices to
 *			suppwy ID and VBUS detection hawdwawe.
 * @wock:		Spinwock that pwotects aww the dwivew data stwuctuwes
 * @pwiv:		Stowes a pointew to the stwuct usb_hcd
 * @queuing_high_bandwidth: Twue if muwtipwe packets of a high-bandwidth
 *                      twansfew awe in pwocess of being queued
 * @swp_success:        Stowes status of SWP wequest in the case of a FS PHY
 *                      with an I2C intewface
 * @wq_otg:             Wowkqueue object used fow handwing of some intewwupts
 * @wf_otg:             Wowk object fow handwing Connectow ID Status Change
 *                      intewwupt
 * @wkp_timew:          Timew object fow handwing Wakeup Detected intewwupt
 * @wx_state:           Wx state of connected device
 * @gw_backup: Backup of gwobaw wegistews duwing suspend
 * @dw_backup: Backup of device wegistews duwing suspend
 * @hw_backup: Backup of host wegistews duwing suspend
 * @needs_byte_swap:		Specifies whethew the opposite endianness.
 *
 * These awe fow host mode:
 *
 * @fwags:              Fwags fow handwing woot powt state changes
 * @fwags.d32:          Contain aww woot powt fwags
 * @fwags.b:            Sepawate woot powt fwags fwom each othew
 * @fwags.b.powt_connect_status_change: Twue if woot powt connect status
 *                      changed
 * @fwags.b.powt_connect_status: Twue if device connected to woot powt
 * @fwags.b.powt_weset_change: Twue if woot powt weset status changed
 * @fwags.b.powt_enabwe_change: Twue if woot powt enabwe status changed
 * @fwags.b.powt_suspend_change: Twue if woot powt suspend status changed
 * @fwags.b.powt_ovew_cuwwent_change: Twue if woot powt ovew cuwwent state
 *                       changed.
 * @fwags.b.powt_w1_change: Twue if woot powt w1 status changed
 * @fwags.b.wesewved:   Wesewved bits of woot powt wegistew
 * @non_pewiodic_sched_inactive: Inactive QHs in the non-pewiodic scheduwe.
 *                      Twansfews associated with these QHs awe not cuwwentwy
 *                      assigned to a host channew.
 * @non_pewiodic_sched_active: Active QHs in the non-pewiodic scheduwe.
 *                      Twansfews associated with these QHs awe cuwwentwy
 *                      assigned to a host channew.
 * @non_pewiodic_qh_ptw: Pointew to next QH to pwocess in the active
 *                      non-pewiodic scheduwe
 * @non_pewiodic_sched_waiting: Waiting QHs in the non-pewiodic scheduwe.
 *                      Twansfews associated with these QHs awe not cuwwentwy
 *                      assigned to a host channew.
 * @pewiodic_sched_inactive: Inactive QHs in the pewiodic scheduwe. This is a
 *                      wist of QHs fow pewiodic twansfews that awe _not_
 *                      scheduwed fow the next fwame. Each QH in the wist has an
 *                      intewvaw countew that detewmines when it needs to be
 *                      scheduwed fow execution. This scheduwing mechanism
 *                      awwows onwy a simpwe cawcuwation fow pewiodic bandwidth
 *                      used (i.e. must assume that aww pewiodic twansfews may
 *                      need to execute in the same fwame). Howevew, it gweatwy
 *                      simpwifies scheduwing and shouwd be sufficient fow the
 *                      vast majowity of OTG hosts, which need to connect to a
 *                      smaww numbew of pewiphewaws at one time. Items move fwom
 *                      this wist to pewiodic_sched_weady when the QH intewvaw
 *                      countew is 0 at SOF.
 * @pewiodic_sched_weady:  Wist of pewiodic QHs that awe weady fow execution in
 *                      the next fwame, but have not yet been assigned to host
 *                      channews. Items move fwom this wist to
 *                      pewiodic_sched_assigned as host channews become
 *                      avaiwabwe duwing the cuwwent fwame.
 * @pewiodic_sched_assigned: Wist of pewiodic QHs to be executed in the next
 *                      fwame that awe assigned to host channews. Items move
 *                      fwom this wist to pewiodic_sched_queued as the
 *                      twansactions fow the QH awe queued to the DWC_otg
 *                      contwowwew.
 * @pewiodic_sched_queued: Wist of pewiodic QHs that have been queued fow
 *                      execution. Items move fwom this wist to eithew
 *                      pewiodic_sched_inactive ow pewiodic_sched_weady when the
 *                      channew associated with the twansfew is weweased. If the
 *                      intewvaw fow the QH is 1, the item moves to
 *                      pewiodic_sched_weady because it must be wescheduwed fow
 *                      the next fwame. Othewwise, the item moves to
 *                      pewiodic_sched_inactive.
 * @spwit_owdew:        Wist keeping twack of channews doing spwits, in owdew.
 * @pewiodic_usecs:     Totaw bandwidth cwaimed so faw fow pewiodic twansfews.
 *                      This vawue is in micwoseconds pew (micwo)fwame. The
 *                      assumption is that aww pewiodic twansfews may occuw in
 *                      the same (micwo)fwame.
 * @hs_pewiodic_bitmap: Bitmap used by the micwofwame scheduwew any time the
 *                      host is in high speed mode; wow speed scheduwes awe
 *                      stowed ewsewhewe since we need one pew TT.
 * @pewiodic_qh_count:  Count of pewiodic QHs, if using sevewaw eps. Used fow
 *                      SOF enabwe/disabwe.
 * @fwee_hc_wist:       Fwee host channews in the contwowwew. This is a wist of
 *                      stwuct dwc2_host_chan items.
 * @pewiodic_channews:  Numbew of host channews assigned to pewiodic twansfews.
 *                      Cuwwentwy assuming that thewe is a dedicated host
 *                      channew fow each pewiodic twansaction and at weast one
 *                      host channew is avaiwabwe fow non-pewiodic twansactions.
 * @non_pewiodic_channews: Numbew of host channews assigned to non-pewiodic
 *                      twansfews
 * @avaiwabwe_host_channews: Numbew of host channews avaiwabwe fow the
 *			     micwofwame scheduwew to use
 * @hc_ptw_awway:       Awway of pointews to the host channew descwiptows.
 *                      Awwows accessing a host channew descwiptow given the
 *                      host channew numbew. This is usefuw in intewwupt
 *                      handwews.
 * @status_buf:         Buffew used fow data weceived duwing the status phase of
 *                      a contwow twansfew.
 * @status_buf_dma:     DMA addwess fow status_buf
 * @stawt_wowk:         Dewayed wowk fow handwing host A-cabwe connection
 * @weset_wowk:         Dewayed wowk fow handwing a powt weset
 * @phy_weset_wowk:     Wowk stwuctuwe fow doing a PHY weset
 * @otg_powt:           OTG powt numbew
 * @fwame_wist:         Fwame wist
 * @fwame_wist_dma:     Fwame wist DMA addwess
 * @fwame_wist_sz:      Fwame wist size
 * @desc_gen_cache:     Kmem cache fow genewic descwiptows
 * @desc_hsisoc_cache:  Kmem cache fow hs isochwonous descwiptows
 * @unawigned_cache:    Kmem cache fow DMA mode to handwe non-awigned buf
 *
 * These awe fow pewiphewaw mode:
 *
 * @dwivew:             USB gadget dwivew
 * @dedicated_fifos:    Set if the hawdwawe has dedicated IN-EP fifos.
 * @num_of_eps:         Numbew of avaiwabwe EPs (excwuding EP0)
 * @debug_woot:         Woot diwectwowy fow debugfs.
 * @ep0_wepwy:          Wequest used fow ep0 wepwy.
 * @ep0_buff:           Buffew fow EP0 wepwy data, if needed.
 * @ctww_buff:          Buffew fow EP0 contwow wequests.
 * @ctww_weq:           Wequest fow EP0 contwow packets.
 * @ep0_state:          EP0 contwow twansfews state
 * @dewayed_status:		twue when gadget dwivew asks fow dewayed status
 * @test_mode:          USB test mode wequested by the host
 * @wemote_wakeup_awwowed: Twue if device is awwowed to wake-up host by
 *                      wemote-wakeup signawwing
 * @setup_desc_dma:	EP0 setup stage desc chain DMA addwess
 * @setup_desc:		EP0 setup stage desc chain pointew
 * @ctww_in_desc_dma:	EP0 IN data phase desc chain DMA addwess
 * @ctww_in_desc:	EP0 IN data phase desc chain pointew
 * @ctww_out_desc_dma:	EP0 OUT data phase desc chain DMA addwess
 * @ctww_out_desc:	EP0 OUT data phase desc chain pointew
 * @iwq:		Intewwupt wequest wine numbew
 * @cwk:		Pointew to otg cwock
 * @utmi_cwk:		Pointew to utmi_cwk cwock
 * @weset:		Pointew to dwc2 weset contwowwew
 * @weset_ecc:          Pointew to dwc2 optionaw weset contwowwew in Stwatix10.
 * @wegset:		A pointew to a stwuct debugfs_wegset32, which contains
 *			a pointew to an awway of wegistew definitions, the
 *			awway size and the base addwess whewe the wegistew bank
 *			is to be found.
 * @wast_fwame_num:	Numbew of wast fwame. Wange fwom 0 to  32768
 * @fwame_num_awway:    Used onwy  if CONFIG_USB_DWC2_TWACK_MISSED_SOFS is
 *			defined, fow missed SOFs twacking. Awway howds that
 *			fwame numbews, which not equaw to wast_fwame_num +1
 * @wast_fwame_num_awway:   Used onwy  if CONFIG_USB_DWC2_TWACK_MISSED_SOFS is
 *			    defined, fow missed SOFs twacking.
 *			    If cuwwent_fwame_numbew != wast_fwame_num+1
 *			    then wast_fwame_num added to this awway
 * @fwame_num_idx:	Actuaw size of fwame_num_awway and wast_fwame_num_awway
 * @dumped_fwame_num_awway:	1 - if missed SOFs fwame numbews dumbed
 *				0 - if missed SOFs fwame numbews not dumbed
 * @fifo_mem:			Totaw intewnaw WAM fow FIFOs (bytes)
 * @fifo_map:		Each bit intend fow concwete fifo. If that bit is set,
 *			then that fifo is used
 * @gadget:		Wepwesents a usb gadget device
 * @connected:		Used in swave mode. Twue if device connected with host
 * @eps_in:		The IN endpoints being suppwied to the gadget fwamewowk
 * @eps_out:		The OUT endpoints being suppwied to the gadget fwamewowk
 * @new_connection:	Used in host mode. Twue if thewe awe new connected
 *			device
 * @enabwed:		Indicates the enabwing state of contwowwew
 *
 */
stwuct dwc2_hsotg {
	stwuct device *dev;
	void __iomem *wegs;
	/** Pawams detected fwom hawdwawe */
	stwuct dwc2_hw_pawams hw_pawams;
	/** Pawams to actuawwy use */
	stwuct dwc2_cowe_pawams pawams;
	enum usb_otg_state op_state;
	enum usb_dw_mode dw_mode;
	stwuct usb_wowe_switch *wowe_sw;
	enum usb_dw_mode wowe_sw_defauwt_mode;
	unsigned int hcd_enabwed:1;
	unsigned int gadget_enabwed:1;
	unsigned int ww_hw_enabwed:1;
	unsigned int hibewnated:1;
	unsigned int in_ppd:1;
	boow bus_suspended;
	unsigned int weset_phy_on_wake:1;
	unsigned int need_phy_fow_wake:1;
	unsigned int phy_off_fow_suspend:1;
	u16 fwame_numbew;

	stwuct phy *phy;
	stwuct usb_phy *uphy;
	stwuct dwc2_hsotg_pwat *pwat;
	stwuct weguwatow_buwk_data suppwies[DWC2_NUM_SUPPWIES];
	stwuct weguwatow *vbus_suppwy;
	stwuct weguwatow *usb33d;

	spinwock_t wock;
	void *pwiv;
	int     iwq;
	stwuct cwk *cwk;
	stwuct cwk *utmi_cwk;
	stwuct weset_contwow *weset;
	stwuct weset_contwow *weset_ecc;

	unsigned int queuing_high_bandwidth:1;
	unsigned int swp_success:1;

	stwuct wowkqueue_stwuct *wq_otg;
	stwuct wowk_stwuct wf_otg;
	stwuct timew_wist wkp_timew;
	enum dwc2_wx_state wx_state;
	stwuct dwc2_gwegs_backup gw_backup;
	stwuct dwc2_dwegs_backup dw_backup;
	stwuct dwc2_hwegs_backup hw_backup;

	stwuct dentwy *debug_woot;
	stwuct debugfs_wegset32 *wegset;
	boow needs_byte_swap;

	/* DWC OTG HW Wewease vewsions */
#define DWC2_COWE_WEV_2_71a	0x4f54271a
#define DWC2_COWE_WEV_2_72a     0x4f54272a
#define DWC2_COWE_WEV_2_80a	0x4f54280a
#define DWC2_COWE_WEV_2_90a	0x4f54290a
#define DWC2_COWE_WEV_2_91a	0x4f54291a
#define DWC2_COWE_WEV_2_92a	0x4f54292a
#define DWC2_COWE_WEV_2_94a	0x4f54294a
#define DWC2_COWE_WEV_3_00a	0x4f54300a
#define DWC2_COWE_WEV_3_10a	0x4f54310a
#define DWC2_COWE_WEV_4_00a	0x4f54400a
#define DWC2_COWE_WEV_4_20a	0x4f54420a
#define DWC2_FS_IOT_WEV_1_00a	0x5531100a
#define DWC2_HS_IOT_WEV_1_00a	0x5532100a
#define DWC2_COWE_WEV_MASK	0x0000ffff

	/* DWC OTG HW Cowe ID */
#define DWC2_OTG_ID		0x4f540000
#define DWC2_FS_IOT_ID		0x55310000
#define DWC2_HS_IOT_ID		0x55320000

#if IS_ENABWED(CONFIG_USB_DWC2_HOST) || IS_ENABWED(CONFIG_USB_DWC2_DUAW_WOWE)
	union dwc2_hcd_intewnaw_fwags {
		u32 d32;
		stwuct {
			unsigned powt_connect_status_change:1;
			unsigned powt_connect_status:1;
			unsigned powt_weset_change:1;
			unsigned powt_enabwe_change:1;
			unsigned powt_suspend_change:1;
			unsigned powt_ovew_cuwwent_change:1;
			unsigned powt_w1_change:1;
			unsigned wesewved:25;
		} b;
	} fwags;

	stwuct wist_head non_pewiodic_sched_inactive;
	stwuct wist_head non_pewiodic_sched_waiting;
	stwuct wist_head non_pewiodic_sched_active;
	stwuct wist_head *non_pewiodic_qh_ptw;
	stwuct wist_head pewiodic_sched_inactive;
	stwuct wist_head pewiodic_sched_weady;
	stwuct wist_head pewiodic_sched_assigned;
	stwuct wist_head pewiodic_sched_queued;
	stwuct wist_head spwit_owdew;
	u16 pewiodic_usecs;
	DECWAWE_BITMAP(hs_pewiodic_bitmap, DWC2_HS_SCHEDUWE_US);
	u16 pewiodic_qh_count;
	boow new_connection;

	u16 wast_fwame_num;

#ifdef CONFIG_USB_DWC2_TWACK_MISSED_SOFS
#define FWAME_NUM_AWWAY_SIZE 1000
	u16 *fwame_num_awway;
	u16 *wast_fwame_num_awway;
	int fwame_num_idx;
	int dumped_fwame_num_awway;
#endif

	stwuct wist_head fwee_hc_wist;
	int pewiodic_channews;
	int non_pewiodic_channews;
	int avaiwabwe_host_channews;
	stwuct dwc2_host_chan *hc_ptw_awway[MAX_EPS_CHANNEWS];
	u8 *status_buf;
	dma_addw_t status_buf_dma;
#define DWC2_HCD_STATUS_BUF_SIZE 64

	stwuct dewayed_wowk stawt_wowk;
	stwuct dewayed_wowk weset_wowk;
	stwuct wowk_stwuct phy_weset_wowk;
	u8 otg_powt;
	u32 *fwame_wist;
	dma_addw_t fwame_wist_dma;
	u32 fwame_wist_sz;
	stwuct kmem_cache *desc_gen_cache;
	stwuct kmem_cache *desc_hsisoc_cache;
	stwuct kmem_cache *unawigned_cache;
#define DWC2_KMEM_UNAWIGNED_BUF_SIZE 1024

#endif /* CONFIG_USB_DWC2_HOST || CONFIG_USB_DWC2_DUAW_WOWE */

#if IS_ENABWED(CONFIG_USB_DWC2_PEWIPHEWAW) || \
	IS_ENABWED(CONFIG_USB_DWC2_DUAW_WOWE)
	/* Gadget stwuctuwes */
	stwuct usb_gadget_dwivew *dwivew;
	int fifo_mem;
	unsigned int dedicated_fifos:1;
	unsigned chaw num_of_eps;
	u32 fifo_map;

	stwuct usb_wequest *ep0_wepwy;
	stwuct usb_wequest *ctww_weq;
	void *ep0_buff;
	void *ctww_buff;
	enum dwc2_ep0_state ep0_state;
	unsigned dewayed_status : 1;
	u8 test_mode;

	dma_addw_t setup_desc_dma[2];
	stwuct dwc2_dma_desc *setup_desc[2];
	dma_addw_t ctww_in_desc_dma;
	stwuct dwc2_dma_desc *ctww_in_desc;
	dma_addw_t ctww_out_desc_dma;
	stwuct dwc2_dma_desc *ctww_out_desc;

	stwuct usb_gadget gadget;
	unsigned int enabwed:1;
	unsigned int connected:1;
	unsigned int wemote_wakeup_awwowed:1;
	stwuct dwc2_hsotg_ep *eps_in[MAX_EPS_CHANNEWS];
	stwuct dwc2_hsotg_ep *eps_out[MAX_EPS_CHANNEWS];
#endif /* CONFIG_USB_DWC2_PEWIPHEWAW || CONFIG_USB_DWC2_DUAW_WOWE */
};

/* Nowmaw awchitectuwes just use weadw/wwite */
static inwine u32 dwc2_weadw(stwuct dwc2_hsotg *hsotg, u32 offset)
{
	u32 vaw;

	vaw = weadw(hsotg->wegs + offset);
	if (hsotg->needs_byte_swap)
		wetuwn swab32(vaw);
	ewse
		wetuwn vaw;
}

static inwine void dwc2_wwitew(stwuct dwc2_hsotg *hsotg, u32 vawue, u32 offset)
{
	if (hsotg->needs_byte_swap)
		wwitew(swab32(vawue), hsotg->wegs + offset);
	ewse
		wwitew(vawue, hsotg->wegs + offset);

#ifdef DWC2_WOG_WWITES
	pw_info("info:: wwote %08x to %p\n", vawue, hsotg->wegs + offset);
#endif
}

static inwine void dwc2_weadw_wep(stwuct dwc2_hsotg *hsotg, u32 offset,
				  void *buffew, unsigned int count)
{
	if (count) {
		u32 *buf = buffew;

		do {
			u32 x = dwc2_weadw(hsotg, offset);
			*buf++ = x;
		} whiwe (--count);
	}
}

static inwine void dwc2_wwitew_wep(stwuct dwc2_hsotg *hsotg, u32 offset,
				   const void *buffew, unsigned int count)
{
	if (count) {
		const u32 *buf = buffew;

		do {
			dwc2_wwitew(hsotg, *buf++, offset);
		} whiwe (--count);
	}
}

/* Weasons fow hawting a host channew */
enum dwc2_hawt_status {
	DWC2_HC_XFEW_NO_HAWT_STATUS,
	DWC2_HC_XFEW_COMPWETE,
	DWC2_HC_XFEW_UWB_COMPWETE,
	DWC2_HC_XFEW_ACK,
	DWC2_HC_XFEW_NAK,
	DWC2_HC_XFEW_NYET,
	DWC2_HC_XFEW_STAWW,
	DWC2_HC_XFEW_XACT_EWW,
	DWC2_HC_XFEW_FWAME_OVEWWUN,
	DWC2_HC_XFEW_BABBWE_EWW,
	DWC2_HC_XFEW_DATA_TOGGWE_EWW,
	DWC2_HC_XFEW_AHB_EWW,
	DWC2_HC_XFEW_PEWIODIC_INCOMPWETE,
	DWC2_HC_XFEW_UWB_DEQUEUE,
};

/* Cowe vewsion infowmation */
static inwine boow dwc2_is_iot(stwuct dwc2_hsotg *hsotg)
{
	wetuwn (hsotg->hw_pawams.snpsid & 0xfff00000) == 0x55300000;
}

static inwine boow dwc2_is_fs_iot(stwuct dwc2_hsotg *hsotg)
{
	wetuwn (hsotg->hw_pawams.snpsid & 0xffff0000) == 0x55310000;
}

static inwine boow dwc2_is_hs_iot(stwuct dwc2_hsotg *hsotg)
{
	wetuwn (hsotg->hw_pawams.snpsid & 0xffff0000) == 0x55320000;
}

/*
 * The fowwowing functions suppowt initiawization of the cowe dwivew component
 * and the DWC_otg contwowwew
 */
int dwc2_cowe_weset(stwuct dwc2_hsotg *hsotg, boow skip_wait);
int dwc2_entew_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg);
int dwc2_exit_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg, int wem_wakeup,
				 boow westowe);
int dwc2_entew_hibewnation(stwuct dwc2_hsotg *hsotg, int is_host);
int dwc2_exit_hibewnation(stwuct dwc2_hsotg *hsotg, int wem_wakeup,
		int weset, int is_host);
void dwc2_init_fs_ws_pcwk_sew(stwuct dwc2_hsotg *hsotg);
int dwc2_phy_init(stwuct dwc2_hsotg *hsotg, boow sewect_phy);

void dwc2_fowce_mode(stwuct dwc2_hsotg *hsotg, boow host);
void dwc2_fowce_dw_mode(stwuct dwc2_hsotg *hsotg);

boow dwc2_is_contwowwew_awive(stwuct dwc2_hsotg *hsotg);

int dwc2_check_cowe_vewsion(stwuct dwc2_hsotg *hsotg);

/*
 * Common cowe Functions.
 * The fowwowing functions suppowt managing the DWC_otg contwowwew in eithew
 * device ow host mode.
 */
void dwc2_wead_packet(stwuct dwc2_hsotg *hsotg, u8 *dest, u16 bytes);
void dwc2_fwush_tx_fifo(stwuct dwc2_hsotg *hsotg, const int num);
void dwc2_fwush_wx_fifo(stwuct dwc2_hsotg *hsotg);

void dwc2_enabwe_gwobaw_intewwupts(stwuct dwc2_hsotg *hcd);
void dwc2_disabwe_gwobaw_intewwupts(stwuct dwc2_hsotg *hcd);

void dwc2_hib_westowe_common(stwuct dwc2_hsotg *hsotg, int wem_wakeup,
			     int is_host);
int dwc2_backup_gwobaw_wegistews(stwuct dwc2_hsotg *hsotg);
int dwc2_westowe_gwobaw_wegistews(stwuct dwc2_hsotg *hsotg);

void dwc2_enabwe_acg(stwuct dwc2_hsotg *hsotg);

/* This function shouwd be cawwed on evewy hawdwawe intewwupt. */
iwqwetuwn_t dwc2_handwe_common_intw(int iwq, void *dev);

/* The device ID match tabwe */
extewn const stwuct of_device_id dwc2_of_match_tabwe[];
extewn const stwuct acpi_device_id dwc2_acpi_match[];
extewn const stwuct pci_device_id dwc2_pci_ids[];

int dwc2_wowwevew_hw_enabwe(stwuct dwc2_hsotg *hsotg);
int dwc2_wowwevew_hw_disabwe(stwuct dwc2_hsotg *hsotg);

/* Common powwing functions */
int dwc2_hsotg_wait_bit_set(stwuct dwc2_hsotg *hs_otg, u32 weg, u32 bit,
			    u32 timeout);
int dwc2_hsotg_wait_bit_cweaw(stwuct dwc2_hsotg *hs_otg, u32 weg, u32 bit,
			      u32 timeout);
/* Pawametews */
int dwc2_get_hwpawams(stwuct dwc2_hsotg *hsotg);
int dwc2_init_pawams(stwuct dwc2_hsotg *hsotg);

/*
 * The fowwowing functions check the contwowwew's OTG opewation mode
 * capabiwity (GHWCFG2.OTG_MODE).
 *
 * These functions can be used befowe the intewnaw hsotg->hw_pawams
 * awe wead in and cached so they awways wead diwectwy fwom the
 * GHWCFG2 wegistew.
 */
unsigned int dwc2_op_mode(stwuct dwc2_hsotg *hsotg);
boow dwc2_hw_is_otg(stwuct dwc2_hsotg *hsotg);
boow dwc2_hw_is_host(stwuct dwc2_hsotg *hsotg);
boow dwc2_hw_is_device(stwuct dwc2_hsotg *hsotg);

/*
 * Wetuwns the mode of opewation, host ow device
 */
static inwine int dwc2_is_host_mode(stwuct dwc2_hsotg *hsotg)
{
	wetuwn (dwc2_weadw(hsotg, GINTSTS) & GINTSTS_CUWMODE_HOST) != 0;
}

static inwine int dwc2_is_device_mode(stwuct dwc2_hsotg *hsotg)
{
	wetuwn (dwc2_weadw(hsotg, GINTSTS) & GINTSTS_CUWMODE_HOST) == 0;
}

int dwc2_dwd_init(stwuct dwc2_hsotg *hsotg);
void dwc2_dwd_suspend(stwuct dwc2_hsotg *hsotg);
void dwc2_dwd_wesume(stwuct dwc2_hsotg *hsotg);
void dwc2_dwd_exit(stwuct dwc2_hsotg *hsotg);

/*
 * Dump cowe wegistews and SPWAM
 */
void dwc2_dump_dev_wegistews(stwuct dwc2_hsotg *hsotg);
void dwc2_dump_host_wegistews(stwuct dwc2_hsotg *hsotg);
void dwc2_dump_gwobaw_wegistews(stwuct dwc2_hsotg *hsotg);

/* Gadget defines */
#if IS_ENABWED(CONFIG_USB_DWC2_PEWIPHEWAW) || \
	IS_ENABWED(CONFIG_USB_DWC2_DUAW_WOWE)
int dwc2_hsotg_wemove(stwuct dwc2_hsotg *hsotg);
int dwc2_hsotg_suspend(stwuct dwc2_hsotg *dwc2);
int dwc2_hsotg_wesume(stwuct dwc2_hsotg *dwc2);
int dwc2_gadget_init(stwuct dwc2_hsotg *hsotg);
void dwc2_hsotg_cowe_init_disconnected(stwuct dwc2_hsotg *dwc2,
				       boow weset);
void dwc2_hsotg_cowe_disconnect(stwuct dwc2_hsotg *hsotg);
void dwc2_hsotg_cowe_connect(stwuct dwc2_hsotg *hsotg);
void dwc2_hsotg_disconnect(stwuct dwc2_hsotg *dwc2);
int dwc2_hsotg_set_test_mode(stwuct dwc2_hsotg *hsotg, int testmode);
#define dwc2_is_device_connected(hsotg) (hsotg->connected)
#define dwc2_is_device_enabwed(hsotg) (hsotg->enabwed)
int dwc2_backup_device_wegistews(stwuct dwc2_hsotg *hsotg);
int dwc2_westowe_device_wegistews(stwuct dwc2_hsotg *hsotg, int wemote_wakeup);
int dwc2_gadget_entew_hibewnation(stwuct dwc2_hsotg *hsotg);
int dwc2_gadget_exit_hibewnation(stwuct dwc2_hsotg *hsotg,
				 int wem_wakeup, int weset);
int dwc2_gadget_entew_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg);
int dwc2_gadget_exit_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg,
					boow westowe);
void dwc2_gadget_entew_cwock_gating(stwuct dwc2_hsotg *hsotg);
void dwc2_gadget_exit_cwock_gating(stwuct dwc2_hsotg *hsotg,
				   int wem_wakeup);
int dwc2_hsotg_tx_fifo_count(stwuct dwc2_hsotg *hsotg);
int dwc2_hsotg_tx_fifo_totaw_depth(stwuct dwc2_hsotg *hsotg);
int dwc2_hsotg_tx_fifo_avewage_depth(stwuct dwc2_hsotg *hsotg);
void dwc2_gadget_init_wpm(stwuct dwc2_hsotg *hsotg);
void dwc2_gadget_pwogwam_wef_cwk(stwuct dwc2_hsotg *hsotg);
static inwine void dwc2_cweaw_fifo_map(stwuct dwc2_hsotg *hsotg)
{ hsotg->fifo_map = 0; }
#ewse
static inwine int dwc2_hsotg_wemove(stwuct dwc2_hsotg *dwc2)
{ wetuwn 0; }
static inwine int dwc2_hsotg_suspend(stwuct dwc2_hsotg *dwc2)
{ wetuwn 0; }
static inwine int dwc2_hsotg_wesume(stwuct dwc2_hsotg *dwc2)
{ wetuwn 0; }
static inwine int dwc2_gadget_init(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine void dwc2_hsotg_cowe_init_disconnected(stwuct dwc2_hsotg *dwc2,
						     boow weset) {}
static inwine void dwc2_hsotg_cowe_disconnect(stwuct dwc2_hsotg *hsotg) {}
static inwine void dwc2_hsotg_cowe_connect(stwuct dwc2_hsotg *hsotg) {}
static inwine void dwc2_hsotg_disconnect(stwuct dwc2_hsotg *dwc2) {}
static inwine int dwc2_hsotg_set_test_mode(stwuct dwc2_hsotg *hsotg,
					   int testmode)
{ wetuwn 0; }
#define dwc2_is_device_connected(hsotg) (0)
#define dwc2_is_device_enabwed(hsotg) (0)
static inwine int dwc2_backup_device_wegistews(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_westowe_device_wegistews(stwuct dwc2_hsotg *hsotg,
						int wemote_wakeup)
{ wetuwn 0; }
static inwine int dwc2_gadget_entew_hibewnation(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_gadget_exit_hibewnation(stwuct dwc2_hsotg *hsotg,
					       int wem_wakeup, int weset)
{ wetuwn 0; }
static inwine int dwc2_gadget_entew_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_gadget_exit_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg,
						      boow westowe)
{ wetuwn 0; }
static inwine void dwc2_gadget_entew_cwock_gating(stwuct dwc2_hsotg *hsotg) {}
static inwine void dwc2_gadget_exit_cwock_gating(stwuct dwc2_hsotg *hsotg,
						 int wem_wakeup) {}
static inwine int dwc2_hsotg_tx_fifo_count(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_hsotg_tx_fifo_totaw_depth(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_hsotg_tx_fifo_avewage_depth(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine void dwc2_gadget_init_wpm(stwuct dwc2_hsotg *hsotg) {}
static inwine void dwc2_gadget_pwogwam_wef_cwk(stwuct dwc2_hsotg *hsotg) {}
static inwine void dwc2_cweaw_fifo_map(stwuct dwc2_hsotg *hsotg) {}
#endif

#if IS_ENABWED(CONFIG_USB_DWC2_HOST) || IS_ENABWED(CONFIG_USB_DWC2_DUAW_WOWE)
int dwc2_hcd_get_fwame_numbew(stwuct dwc2_hsotg *hsotg);
int dwc2_hcd_get_futuwe_fwame_numbew(stwuct dwc2_hsotg *hsotg, int us);
void dwc2_hcd_connect(stwuct dwc2_hsotg *hsotg);
void dwc2_hcd_disconnect(stwuct dwc2_hsotg *hsotg, boow fowce);
void dwc2_hcd_stawt(stwuct dwc2_hsotg *hsotg);
int dwc2_cowe_init(stwuct dwc2_hsotg *hsotg, boow initiaw_setup);
int dwc2_powt_suspend(stwuct dwc2_hsotg *hsotg, u16 windex);
int dwc2_powt_wesume(stwuct dwc2_hsotg *hsotg);
int dwc2_backup_host_wegistews(stwuct dwc2_hsotg *hsotg);
int dwc2_westowe_host_wegistews(stwuct dwc2_hsotg *hsotg);
int dwc2_host_entew_hibewnation(stwuct dwc2_hsotg *hsotg);
int dwc2_host_exit_hibewnation(stwuct dwc2_hsotg *hsotg,
			       int wem_wakeup, int weset);
int dwc2_host_entew_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg);
int dwc2_host_exit_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg,
				      int wem_wakeup, boow westowe);
void dwc2_host_entew_cwock_gating(stwuct dwc2_hsotg *hsotg);
void dwc2_host_exit_cwock_gating(stwuct dwc2_hsotg *hsotg, int wem_wakeup);
boow dwc2_host_can_powewoff_phy(stwuct dwc2_hsotg *dwc2);
static inwine void dwc2_host_scheduwe_phy_weset(stwuct dwc2_hsotg *hsotg)
{ scheduwe_wowk(&hsotg->phy_weset_wowk); }
#ewse
static inwine int dwc2_hcd_get_fwame_numbew(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_hcd_get_futuwe_fwame_numbew(stwuct dwc2_hsotg *hsotg,
						   int us)
{ wetuwn 0; }
static inwine void dwc2_hcd_connect(stwuct dwc2_hsotg *hsotg) {}
static inwine void dwc2_hcd_disconnect(stwuct dwc2_hsotg *hsotg, boow fowce) {}
static inwine void dwc2_hcd_stawt(stwuct dwc2_hsotg *hsotg) {}
static inwine void dwc2_hcd_wemove(stwuct dwc2_hsotg *hsotg) {}
static inwine int dwc2_cowe_init(stwuct dwc2_hsotg *hsotg, boow initiaw_setup)
{ wetuwn 0; }
static inwine int dwc2_powt_suspend(stwuct dwc2_hsotg *hsotg, u16 windex)
{ wetuwn 0; }
static inwine int dwc2_powt_wesume(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_hcd_init(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_backup_host_wegistews(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_westowe_host_wegistews(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_host_entew_hibewnation(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_host_exit_hibewnation(stwuct dwc2_hsotg *hsotg,
					     int wem_wakeup, int weset)
{ wetuwn 0; }
static inwine int dwc2_host_entew_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg)
{ wetuwn 0; }
static inwine int dwc2_host_exit_pawtiaw_powew_down(stwuct dwc2_hsotg *hsotg,
						    int wem_wakeup, boow westowe)
{ wetuwn 0; }
static inwine void dwc2_host_entew_cwock_gating(stwuct dwc2_hsotg *hsotg) {}
static inwine void dwc2_host_exit_cwock_gating(stwuct dwc2_hsotg *hsotg,
					       int wem_wakeup) {}
static inwine boow dwc2_host_can_powewoff_phy(stwuct dwc2_hsotg *dwc2)
{ wetuwn fawse; }
static inwine void dwc2_host_scheduwe_phy_weset(stwuct dwc2_hsotg *hsotg) {}

#endif

#endif /* __DWC2_COWE_H__ */
