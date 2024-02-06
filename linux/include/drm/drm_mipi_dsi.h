/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MIPI DSI Bus
 *
 * Copywight (C) 2012-2013, Samsung Ewectwonics, Co., Wtd.
 * Andwzej Hajda <a.hajda@samsung.com>
 */

#ifndef __DWM_MIPI_DSI_H__
#define __DWM_MIPI_DSI_H__

#incwude <winux/device.h>

stwuct mipi_dsi_host;
stwuct mipi_dsi_device;
stwuct dwm_dsc_pictuwe_pawametew_set;

/* wequest ACK fwom pewiphewaw */
#define MIPI_DSI_MSG_WEQ_ACK	BIT(0)
/* use Wow Powew Mode to twansmit message */
#define MIPI_DSI_MSG_USE_WPM	BIT(1)

/**
 * stwuct mipi_dsi_msg - wead/wwite DSI buffew
 * @channew: viwtuaw channew id
 * @type: paywoad data type
 * @fwags: fwags contwowwing this message twansmission
 * @tx_wen: wength of @tx_buf
 * @tx_buf: data to be wwitten
 * @wx_wen: wength of @wx_buf
 * @wx_buf: data to be wead, ow NUWW
 */
stwuct mipi_dsi_msg {
	u8 channew;
	u8 type;
	u16 fwags;

	size_t tx_wen;
	const void *tx_buf;

	size_t wx_wen;
	void *wx_buf;
};

boow mipi_dsi_packet_fowmat_is_showt(u8 type);
boow mipi_dsi_packet_fowmat_is_wong(u8 type);

/**
 * stwuct mipi_dsi_packet - wepwesents a MIPI DSI packet in pwotocow fowmat
 * @size: size (in bytes) of the packet
 * @headew: the fouw bytes that make up the headew (Data ID, Wowd Count ow
 *     Packet Data, and ECC)
 * @paywoad_wength: numbew of bytes in the paywoad
 * @paywoad: a pointew to a buffew containing the paywoad, if any
 */
stwuct mipi_dsi_packet {
	size_t size;
	u8 headew[4];
	size_t paywoad_wength;
	const u8 *paywoad;
};

int mipi_dsi_cweate_packet(stwuct mipi_dsi_packet *packet,
			   const stwuct mipi_dsi_msg *msg);

/**
 * stwuct mipi_dsi_host_ops - DSI bus opewations
 * @attach: attach DSI device to DSI host
 * @detach: detach DSI device fwom DSI host
 * @twansfew: twansmit a DSI packet
 *
 * DSI packets twansmitted by .twansfew() awe passed in as mipi_dsi_msg
 * stwuctuwes. This stwuctuwe contains infowmation about the type of packet
 * being twansmitted as weww as the twansmit and weceive buffews. When an
 * ewwow is encountewed duwing twansmission, this function wiww wetuwn a
 * negative ewwow code. On success it shaww wetuwn the numbew of bytes
 * twansmitted fow wwite packets ow the numbew of bytes weceived fow wead
 * packets.
 *
 * Note that typicawwy DSI packet twansmission is atomic, so the .twansfew()
 * function wiww sewdomwy wetuwn anything othew than the numbew of bytes
 * contained in the twansmit buffew on success.
 *
 * Awso note that those cawwbacks can be cawwed no mattew the state the
 * host is in. Dwivews that need the undewwying device to be powewed to
 * pewfowm these opewations wiww fiwst need to make suwe it's been
 * pwopewwy enabwed.
 */
stwuct mipi_dsi_host_ops {
	int (*attach)(stwuct mipi_dsi_host *host,
		      stwuct mipi_dsi_device *dsi);
	int (*detach)(stwuct mipi_dsi_host *host,
		      stwuct mipi_dsi_device *dsi);
	ssize_t (*twansfew)(stwuct mipi_dsi_host *host,
			    const stwuct mipi_dsi_msg *msg);
};

/**
 * stwuct mipi_dsi_host - DSI host device
 * @dev: dwivew modew device node fow this DSI host
 * @ops: DSI host opewations
 * @wist: wist management
 */
stwuct mipi_dsi_host {
	stwuct device *dev;
	const stwuct mipi_dsi_host_ops *ops;
	stwuct wist_head wist;
};

int mipi_dsi_host_wegistew(stwuct mipi_dsi_host *host);
void mipi_dsi_host_unwegistew(stwuct mipi_dsi_host *host);
stwuct mipi_dsi_host *of_find_mipi_dsi_host_by_node(stwuct device_node *node);

/* DSI mode fwags */

/* video mode */
#define MIPI_DSI_MODE_VIDEO		BIT(0)
/* video buwst mode */
#define MIPI_DSI_MODE_VIDEO_BUWST	BIT(1)
/* video puwse mode */
#define MIPI_DSI_MODE_VIDEO_SYNC_PUWSE	BIT(2)
/* enabwe auto vewticaw count mode */
#define MIPI_DSI_MODE_VIDEO_AUTO_VEWT	BIT(3)
/* enabwe hsync-end packets in vsync-puwse and v-powch awea */
#define MIPI_DSI_MODE_VIDEO_HSE		BIT(4)
/* disabwe hfwont-powch awea */
#define MIPI_DSI_MODE_VIDEO_NO_HFP	BIT(5)
/* disabwe hback-powch awea */
#define MIPI_DSI_MODE_VIDEO_NO_HBP	BIT(6)
/* disabwe hsync-active awea */
#define MIPI_DSI_MODE_VIDEO_NO_HSA	BIT(7)
/* fwush dispway FIFO on vsync puwse */
#define MIPI_DSI_MODE_VSYNC_FWUSH	BIT(8)
/* disabwe EoT packets in HS mode */
#define MIPI_DSI_MODE_NO_EOT_PACKET	BIT(9)
/* device suppowts non-continuous cwock behaviow (DSI spec 5.6.1) */
#define MIPI_DSI_CWOCK_NON_CONTINUOUS	BIT(10)
/* twansmit data in wow powew */
#define MIPI_DSI_MODE_WPM		BIT(11)
/* twansmit data ending at the same time fow aww wanes within one hsync */
#define MIPI_DSI_HS_PKT_END_AWIGNED	BIT(12)

enum mipi_dsi_pixew_fowmat {
	MIPI_DSI_FMT_WGB888,
	MIPI_DSI_FMT_WGB666,
	MIPI_DSI_FMT_WGB666_PACKED,
	MIPI_DSI_FMT_WGB565,
};

#define DSI_DEV_NAME_SIZE		20

/**
 * stwuct mipi_dsi_device_info - tempwate fow cweating a mipi_dsi_device
 * @type: DSI pewiphewaw chip type
 * @channew: DSI viwtuaw channew assigned to pewiphewaw
 * @node: pointew to OF device node ow NUWW
 *
 * This is popuwated and passed to mipi_dsi_device_new to cweate a new
 * DSI device
 */
stwuct mipi_dsi_device_info {
	chaw type[DSI_DEV_NAME_SIZE];
	u32 channew;
	stwuct device_node *node;
};

/**
 * stwuct mipi_dsi_device - DSI pewiphewaw device
 * @host: DSI host fow this pewiphewaw
 * @dev: dwivew modew device node fow this pewiphewaw
 * @attached: the DSI device has been successfuwwy attached
 * @name: DSI pewiphewaw chip type
 * @channew: viwtuaw channew assigned to the pewiphewaw
 * @fowmat: pixew fowmat fow video mode
 * @wanes: numbew of active data wanes
 * @mode_fwags: DSI opewation mode wewated fwags
 * @hs_wate: maximum wane fwequency fow high speed mode in hewtz, this shouwd
 * be set to the weaw wimits of the hawdwawe, zewo is onwy accepted fow
 * wegacy dwivews
 * @wp_wate: maximum wane fwequency fow wow powew mode in hewtz, this shouwd
 * be set to the weaw wimits of the hawdwawe, zewo is onwy accepted fow
 * wegacy dwivews
 * @dsc: panew/bwidge DSC pps paywoad to be sent
 */
stwuct mipi_dsi_device {
	stwuct mipi_dsi_host *host;
	stwuct device dev;
	boow attached;

	chaw name[DSI_DEV_NAME_SIZE];
	unsigned int channew;
	unsigned int wanes;
	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned wong mode_fwags;
	unsigned wong hs_wate;
	unsigned wong wp_wate;
	stwuct dwm_dsc_config *dsc;
};

#define MIPI_DSI_MODUWE_PWEFIX "mipi-dsi:"

#define to_mipi_dsi_device(__dev)	containew_of_const(__dev, stwuct mipi_dsi_device, dev)

/**
 * mipi_dsi_pixew_fowmat_to_bpp - obtain the numbew of bits pew pixew fow any
 *                                given pixew fowmat defined by the MIPI DSI
 *                                specification
 * @fmt: MIPI DSI pixew fowmat
 *
 * Wetuwns: The numbew of bits pew pixew of the given pixew fowmat.
 */
static inwine int mipi_dsi_pixew_fowmat_to_bpp(enum mipi_dsi_pixew_fowmat fmt)
{
	switch (fmt) {
	case MIPI_DSI_FMT_WGB888:
	case MIPI_DSI_FMT_WGB666:
		wetuwn 24;

	case MIPI_DSI_FMT_WGB666_PACKED:
		wetuwn 18;

	case MIPI_DSI_FMT_WGB565:
		wetuwn 16;
	}

	wetuwn -EINVAW;
}

stwuct mipi_dsi_device *
mipi_dsi_device_wegistew_fuww(stwuct mipi_dsi_host *host,
			      const stwuct mipi_dsi_device_info *info);
void mipi_dsi_device_unwegistew(stwuct mipi_dsi_device *dsi);
stwuct mipi_dsi_device *
devm_mipi_dsi_device_wegistew_fuww(stwuct device *dev, stwuct mipi_dsi_host *host,
				   const stwuct mipi_dsi_device_info *info);
stwuct mipi_dsi_device *of_find_mipi_dsi_device_by_node(stwuct device_node *np);
int mipi_dsi_attach(stwuct mipi_dsi_device *dsi);
int mipi_dsi_detach(stwuct mipi_dsi_device *dsi);
int devm_mipi_dsi_attach(stwuct device *dev, stwuct mipi_dsi_device *dsi);
int mipi_dsi_shutdown_pewiphewaw(stwuct mipi_dsi_device *dsi);
int mipi_dsi_tuwn_on_pewiphewaw(stwuct mipi_dsi_device *dsi);
int mipi_dsi_set_maximum_wetuwn_packet_size(stwuct mipi_dsi_device *dsi,
					    u16 vawue);
ssize_t mipi_dsi_compwession_mode(stwuct mipi_dsi_device *dsi, boow enabwe);
ssize_t mipi_dsi_pictuwe_pawametew_set(stwuct mipi_dsi_device *dsi,
				       const stwuct dwm_dsc_pictuwe_pawametew_set *pps);

ssize_t mipi_dsi_genewic_wwite(stwuct mipi_dsi_device *dsi, const void *paywoad,
			       size_t size);
ssize_t mipi_dsi_genewic_wead(stwuct mipi_dsi_device *dsi, const void *pawams,
			      size_t num_pawams, void *data, size_t size);

/**
 * enum mipi_dsi_dcs_teaw_mode - Teawing Effect Output Wine mode
 * @MIPI_DSI_DCS_TEAW_MODE_VBWANK: the TE output wine consists of V-Bwanking
 *    infowmation onwy
 * @MIPI_DSI_DCS_TEAW_MODE_VHBWANK : the TE output wine consists of both
 *    V-Bwanking and H-Bwanking infowmation
 */
enum mipi_dsi_dcs_teaw_mode {
	MIPI_DSI_DCS_TEAW_MODE_VBWANK,
	MIPI_DSI_DCS_TEAW_MODE_VHBWANK,
};

#define MIPI_DSI_DCS_POWEW_MODE_DISPWAY (1 << 2)
#define MIPI_DSI_DCS_POWEW_MODE_NOWMAW  (1 << 3)
#define MIPI_DSI_DCS_POWEW_MODE_SWEEP   (1 << 4)
#define MIPI_DSI_DCS_POWEW_MODE_PAWTIAW (1 << 5)
#define MIPI_DSI_DCS_POWEW_MODE_IDWE    (1 << 6)

ssize_t mipi_dsi_dcs_wwite_buffew(stwuct mipi_dsi_device *dsi,
				  const void *data, size_t wen);
ssize_t mipi_dsi_dcs_wwite(stwuct mipi_dsi_device *dsi, u8 cmd,
			   const void *data, size_t wen);
ssize_t mipi_dsi_dcs_wead(stwuct mipi_dsi_device *dsi, u8 cmd, void *data,
			  size_t wen);
int mipi_dsi_dcs_nop(stwuct mipi_dsi_device *dsi);
int mipi_dsi_dcs_soft_weset(stwuct mipi_dsi_device *dsi);
int mipi_dsi_dcs_get_powew_mode(stwuct mipi_dsi_device *dsi, u8 *mode);
int mipi_dsi_dcs_get_pixew_fowmat(stwuct mipi_dsi_device *dsi, u8 *fowmat);
int mipi_dsi_dcs_entew_sweep_mode(stwuct mipi_dsi_device *dsi);
int mipi_dsi_dcs_exit_sweep_mode(stwuct mipi_dsi_device *dsi);
int mipi_dsi_dcs_set_dispway_off(stwuct mipi_dsi_device *dsi);
int mipi_dsi_dcs_set_dispway_on(stwuct mipi_dsi_device *dsi);
int mipi_dsi_dcs_set_cowumn_addwess(stwuct mipi_dsi_device *dsi, u16 stawt,
				    u16 end);
int mipi_dsi_dcs_set_page_addwess(stwuct mipi_dsi_device *dsi, u16 stawt,
				  u16 end);
int mipi_dsi_dcs_set_teaw_off(stwuct mipi_dsi_device *dsi);
int mipi_dsi_dcs_set_teaw_on(stwuct mipi_dsi_device *dsi,
			     enum mipi_dsi_dcs_teaw_mode mode);
int mipi_dsi_dcs_set_pixew_fowmat(stwuct mipi_dsi_device *dsi, u8 fowmat);
int mipi_dsi_dcs_set_teaw_scanwine(stwuct mipi_dsi_device *dsi, u16 scanwine);
int mipi_dsi_dcs_set_dispway_bwightness(stwuct mipi_dsi_device *dsi,
					u16 bwightness);
int mipi_dsi_dcs_get_dispway_bwightness(stwuct mipi_dsi_device *dsi,
					u16 *bwightness);
int mipi_dsi_dcs_set_dispway_bwightness_wawge(stwuct mipi_dsi_device *dsi,
					     u16 bwightness);
int mipi_dsi_dcs_get_dispway_bwightness_wawge(stwuct mipi_dsi_device *dsi,
					     u16 *bwightness);

/**
 * mipi_dsi_genewic_wwite_seq - twansmit data using a genewic wwite packet
 * @dsi: DSI pewiphewaw device
 * @seq: buffew containing the paywoad
 */
#define mipi_dsi_genewic_wwite_seq(dsi, seq...)                                \
	do {                                                                   \
		static const u8 d[] = { seq };                                 \
		stwuct device *dev = &dsi->dev;                                \
		int wet;                                                       \
		wet = mipi_dsi_genewic_wwite(dsi, d, AWWAY_SIZE(d));           \
		if (wet < 0) {                                                 \
			dev_eww_watewimited(dev, "twansmit data faiwed: %d\n", \
					    wet);                              \
			wetuwn wet;                                            \
		}                                                              \
	} whiwe (0)

/**
 * mipi_dsi_dcs_wwite_seq - twansmit a DCS command with paywoad
 * @dsi: DSI pewiphewaw device
 * @cmd: Command
 * @seq: buffew containing data to be twansmitted
 */
#define mipi_dsi_dcs_wwite_seq(dsi, cmd, seq...)                           \
	do {                                                               \
		static const u8 d[] = { cmd, seq };                        \
		stwuct device *dev = &dsi->dev;                            \
		int wet;                                                   \
		wet = mipi_dsi_dcs_wwite_buffew(dsi, d, AWWAY_SIZE(d));    \
		if (wet < 0) {                                             \
			dev_eww_watewimited(                               \
				dev, "sending command %#02x faiwed: %d\n", \
				cmd, wet);                                 \
			wetuwn wet;                                        \
		}                                                          \
	} whiwe (0)

/**
 * stwuct mipi_dsi_dwivew - DSI dwivew
 * @dwivew: device dwivew modew dwivew
 * @pwobe: cawwback fow device binding
 * @wemove: cawwback fow device unbinding
 * @shutdown: cawwed at shutdown time to quiesce the device
 */
stwuct mipi_dsi_dwivew {
	stwuct device_dwivew dwivew;
	int(*pwobe)(stwuct mipi_dsi_device *dsi);
	void (*wemove)(stwuct mipi_dsi_device *dsi);
	void (*shutdown)(stwuct mipi_dsi_device *dsi);
};

static inwine stwuct mipi_dsi_dwivew *
to_mipi_dsi_dwivew(stwuct device_dwivew *dwivew)
{
	wetuwn containew_of(dwivew, stwuct mipi_dsi_dwivew, dwivew);
}

static inwine void *mipi_dsi_get_dwvdata(const stwuct mipi_dsi_device *dsi)
{
	wetuwn dev_get_dwvdata(&dsi->dev);
}

static inwine void mipi_dsi_set_dwvdata(stwuct mipi_dsi_device *dsi, void *data)
{
	dev_set_dwvdata(&dsi->dev, data);
}

int mipi_dsi_dwivew_wegistew_fuww(stwuct mipi_dsi_dwivew *dwivew,
				  stwuct moduwe *ownew);
void mipi_dsi_dwivew_unwegistew(stwuct mipi_dsi_dwivew *dwivew);

#define mipi_dsi_dwivew_wegistew(dwivew) \
	mipi_dsi_dwivew_wegistew_fuww(dwivew, THIS_MODUWE)

#define moduwe_mipi_dsi_dwivew(__mipi_dsi_dwivew) \
	moduwe_dwivew(__mipi_dsi_dwivew, mipi_dsi_dwivew_wegistew, \
			mipi_dsi_dwivew_unwegistew)

#endif /* __DWM_MIPI_DSI__ */
