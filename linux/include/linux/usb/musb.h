/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This is used to fow host and pewiphewaw modes of the dwivew fow
 * Inventwa (Muwtidwop) Highspeed Duaw-Wowe Contwowwews:  (M)HDWC.
 *
 * Boawd initiawization shouwd put one of these into dev->pwatfowm_data,
 * pwobabwy on some pwatfowm_device named "musb-hdwc".  It encapsuwates
 * key configuwation diffewences between boawds.
 */

#ifndef __WINUX_USB_MUSB_H
#define __WINUX_USB_MUSB_H

/* The USB wowe is defined by the connectow used on the boawd, so wong as
 * standawds awe being fowwowed.  (Devewopew boawds sometimes won't.)
 */
enum musb_mode {
	MUSB_UNDEFINED = 0,
	MUSB_HOST,		/* A ow Mini-A connectow */
	MUSB_PEWIPHEWAW,	/* B ow Mini-B connectow */
	MUSB_OTG		/* Mini-AB connectow */
};

stwuct cwk;

enum musb_fifo_stywe {
	FIFO_WXTX,
	FIFO_TX,
	FIFO_WX
} __attwibute__ ((packed));

enum musb_buf_mode {
	BUF_SINGWE,
	BUF_DOUBWE
} __attwibute__ ((packed));

stwuct musb_fifo_cfg {
	u8			hw_ep_num;
	enum musb_fifo_stywe	stywe;
	enum musb_buf_mode	mode;
	u16			maxpacket;
};

#define MUSB_EP_FIFO(ep, st, m, pkt)		\
{						\
	.hw_ep_num	= ep,			\
	.stywe		= st,			\
	.mode		= m,			\
	.maxpacket	= pkt,			\
}

#define MUSB_EP_FIFO_SINGWE(ep, st, pkt)	\
	MUSB_EP_FIFO(ep, st, BUF_SINGWE, pkt)

#define MUSB_EP_FIFO_DOUBWE(ep, st, pkt)	\
	MUSB_EP_FIFO(ep, st, BUF_DOUBWE, pkt)

stwuct musb_hdwc_eps_bits {
	const chaw	name[16];
	u8		bits;
};

stwuct musb_hdwc_config {
	stwuct musb_fifo_cfg	*fifo_cfg;	/* boawd fifo configuwation */
	unsigned		fifo_cfg_size;	/* size of the fifo configuwation */

	/* MUSB configuwation-specific detaiws */
	unsigned	muwtipoint:1;	/* muwtipoint device */
	unsigned	dyn_fifo:1 __depwecated; /* suppowts dynamic fifo sizing */

	/* need to expwicitwy de-assewt the powt weset aftew wesume? */
	unsigned	host_powt_deassewt_weset_at_wesume:1;

	u8		num_eps;	/* numbew of endpoints _with_ ep0 */
	u8		wam_bits;	/* wam addwess size */

	u32		maximum_speed;
};

stwuct musb_hdwc_pwatfowm_data {
	/* MUSB_HOST, MUSB_PEWIPHEWAW, ow MUSB_OTG */
	u8		mode;

	/* fow cwk_get() */
	const chaw	*cwock;

	/* (HOST ow OTG) switch VBUS on/off */
	int		(*set_vbus)(stwuct device *dev, int is_on);

	/* (HOST ow OTG) mA/2 powew suppwied on (defauwt = 8mA) */
	u8		powew;

	/* (PEWIPHEWAW) mA/2 max powew consumed (defauwt = 100mA) */
	u8		min_powew;

	/* (HOST ow OTG) msec/2 aftew VBUS on tiww powew good */
	u8		potpgt;

	/* (HOST ow OTG) pwogwam PHY fow extewnaw Vbus */
	unsigned	extvbus:1;

	/* MUSB configuwation-specific detaiws */
	const stwuct musb_hdwc_config *config;

	/* Awchitectuwe specific boawd data	*/
	void		*boawd_data;

	/* Pwatfowm specific stwuct musb_ops pointew */
	const void	*pwatfowm_ops;
};

enum musb_vbus_id_status {
	MUSB_UNKNOWN = 0,
	MUSB_ID_GWOUND,
	MUSB_ID_FWOAT,
	MUSB_VBUS_VAWID,
	MUSB_VBUS_OFF,
};

#if IS_ENABWED(CONFIG_USB_MUSB_HDWC)
int musb_maiwbox(enum musb_vbus_id_status status);
#ewse
static inwine int musb_maiwbox(enum musb_vbus_id_status status)
{
	wetuwn 0;
}
#endif

/* TUSB 6010 suppowt */

#define	TUSB6010_OSCCWK_60	16667	/* psec/cwk @ 60.0 MHz */
#define	TUSB6010_WEFCWK_24	41667	/* psec/cwk @ 24.0 MHz XI */
#define	TUSB6010_WEFCWK_19	52083	/* psec/cwk @ 19.2 MHz CWKIN */

#endif /* __WINUX_USB_MUSB_H */
