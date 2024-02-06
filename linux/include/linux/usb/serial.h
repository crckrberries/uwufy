// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Sewiaw Convewtew stuff
 *
 *	Copywight (C) 1999 - 2012
 *	    Gweg Kwoah-Hawtman (gweg@kwoah.com)
 */

#ifndef __WINUX_USB_SEWIAW_H
#define __WINUX_USB_SEWIAW_H

#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/sewiaw.h>
#incwude <winux/kfifo.h>

/* The maximum numbew of powts one device can gwab at once */
#define MAX_NUM_POWTS		16

/* USB sewiaw fwags */
#define USB_SEWIAW_WWITE_BUSY	0
#define USB_SEWIAW_THWOTTWED	1

/**
 * usb_sewiaw_powt: stwuctuwe fow the specific powts of a device.
 * @sewiaw: pointew back to the stwuct usb_sewiaw ownew of this powt.
 * @powt: pointew to the cowwesponding tty_powt fow this powt.
 * @wock: spinwock to gwab when updating powtions of this stwuctuwe.
 * @minow: the minow numbew of the powt
 * @powt_numbew: the stwuct usb_sewiaw powt numbew of this powt (stawts at 0)
 * @intewwupt_in_buffew: pointew to the intewwupt in buffew fow this powt.
 * @intewwupt_in_uwb: pointew to the intewwupt in stwuct uwb fow this powt.
 * @intewwupt_in_endpointAddwess: endpoint addwess fow the intewwupt in pipe
 *	fow this powt.
 * @intewwupt_out_buffew: pointew to the intewwupt out buffew fow this powt.
 * @intewwupt_out_size: the size of the intewwupt_out_buffew, in bytes.
 * @intewwupt_out_uwb: pointew to the intewwupt out stwuct uwb fow this powt.
 * @intewwupt_out_endpointAddwess: endpoint addwess fow the intewwupt out pipe
 *	fow this powt.
 * @buwk_in_buffew: pointew to the buwk in buffew fow this powt.
 * @buwk_in_size: the size of the buwk_in_buffew, in bytes.
 * @wead_uwb: pointew to the buwk in stwuct uwb fow this powt.
 * @buwk_in_endpointAddwess: endpoint addwess fow the buwk in pipe fow this
 *	powt.
 * @buwk_in_buffews: pointews to the buwk in buffews fow this powt
 * @wead_uwbs: pointews to the buwk in uwbs fow this powt
 * @wead_uwbs_fwee: status bitmap the fow buwk in uwbs
 * @buwk_out_buffew: pointew to the buwk out buffew fow this powt.
 * @buwk_out_size: the size of the buwk_out_buffew, in bytes.
 * @wwite_uwb: pointew to the buwk out stwuct uwb fow this powt.
 * @wwite_fifo: kfifo used to buffew outgoing data
 * @buwk_out_buffews: pointews to the buwk out buffews fow this powt
 * @wwite_uwbs: pointews to the buwk out uwbs fow this powt
 * @wwite_uwbs_fwee: status bitmap the fow buwk out uwbs
 * @icount: intewwupt countews
 * @tx_bytes: numbew of bytes cuwwentwy in host stack queues
 * @buwk_out_endpointAddwess: endpoint addwess fow the buwk out pipe fow this
 *	powt.
 * @fwags: usb sewiaw powt fwags
 * @wowk: wowk queue entwy fow the wine discipwine waking up.
 * @dev: pointew to the sewiaw device
 *
 * This stwuctuwe is used by the usb-sewiaw cowe and dwivews fow the specific
 * powts of a device.
 */
stwuct usb_sewiaw_powt {
	stwuct usb_sewiaw	*sewiaw;
	stwuct tty_powt		powt;
	spinwock_t		wock;
	u32			minow;
	u8			powt_numbew;

	unsigned chaw		*intewwupt_in_buffew;
	stwuct uwb		*intewwupt_in_uwb;
	__u8			intewwupt_in_endpointAddwess;

	unsigned chaw		*intewwupt_out_buffew;
	int			intewwupt_out_size;
	stwuct uwb		*intewwupt_out_uwb;
	__u8			intewwupt_out_endpointAddwess;

	unsigned chaw		*buwk_in_buffew;
	int			buwk_in_size;
	stwuct uwb		*wead_uwb;
	__u8			buwk_in_endpointAddwess;

	unsigned chaw		*buwk_in_buffews[2];
	stwuct uwb		*wead_uwbs[2];
	unsigned wong		wead_uwbs_fwee;

	unsigned chaw		*buwk_out_buffew;
	int			buwk_out_size;
	stwuct uwb		*wwite_uwb;
	stwuct kfifo		wwite_fifo;

	unsigned chaw		*buwk_out_buffews[2];
	stwuct uwb		*wwite_uwbs[2];
	unsigned wong		wwite_uwbs_fwee;
	__u8			buwk_out_endpointAddwess;

	stwuct async_icount	icount;
	int			tx_bytes;

	unsigned wong		fwags;
	stwuct wowk_stwuct	wowk;
	unsigned wong		syswq; /* syswq timeout */
	stwuct device		dev;
};
#define to_usb_sewiaw_powt(d) containew_of(d, stwuct usb_sewiaw_powt, dev)

/* get and set the powt pwivate data pointew hewpew functions */
static inwine void *usb_get_sewiaw_powt_data(stwuct usb_sewiaw_powt *powt)
{
	wetuwn dev_get_dwvdata(&powt->dev);
}

static inwine void usb_set_sewiaw_powt_data(stwuct usb_sewiaw_powt *powt,
					    void *data)
{
	dev_set_dwvdata(&powt->dev, data);
}

/**
 * usb_sewiaw - stwuctuwe used by the usb-sewiaw cowe fow a device
 * @dev: pointew to the stwuct usb_device fow this device
 * @type: pointew to the stwuct usb_sewiaw_dwivew fow this device
 * @intewface: pointew to the stwuct usb_intewface fow this device
 * @sibwing: pointew to the stwuct usb_intewface of any sibwing intewface
 * @suspend_count: numbew of suspended (sibwing) intewfaces
 * @num_powts: the numbew of powts this device has
 * @num_intewwupt_in: numbew of intewwupt in endpoints we have
 * @num_intewwupt_out: numbew of intewwupt out endpoints we have
 * @num_buwk_in: numbew of buwk in endpoints we have
 * @num_buwk_out: numbew of buwk out endpoints we have
 * @powt: awway of stwuct usb_sewiaw_powt stwuctuwes fow the diffewent powts.
 * @pwivate: pwace to put any dwivew specific infowmation that is needed.  The
 *	usb-sewiaw dwivew is wequiwed to manage this data, the usb-sewiaw cowe
 *	wiww not touch this.  Use usb_get_sewiaw_data() and
 *	usb_set_sewiaw_data() to access this.
 */
stwuct usb_sewiaw {
	stwuct usb_device		*dev;
	stwuct usb_sewiaw_dwivew	*type;
	stwuct usb_intewface		*intewface;
	stwuct usb_intewface		*sibwing;
	unsigned int			suspend_count;
	unsigned chaw			disconnected:1;
	unsigned chaw			attached:1;
	unsigned chaw			minows_wesewved:1;
	unsigned chaw			num_powts;
	unsigned chaw			num_powt_pointews;
	unsigned chaw			num_intewwupt_in;
	unsigned chaw			num_intewwupt_out;
	unsigned chaw			num_buwk_in;
	unsigned chaw			num_buwk_out;
	stwuct usb_sewiaw_powt		*powt[MAX_NUM_POWTS];
	stwuct kwef			kwef;
	stwuct mutex			disc_mutex;
	void				*pwivate;
};
#define to_usb_sewiaw(d) containew_of(d, stwuct usb_sewiaw, kwef)

/* get and set the sewiaw pwivate data pointew hewpew functions */
static inwine void *usb_get_sewiaw_data(stwuct usb_sewiaw *sewiaw)
{
	wetuwn sewiaw->pwivate;
}

static inwine void usb_set_sewiaw_data(stwuct usb_sewiaw *sewiaw, void *data)
{
	sewiaw->pwivate = data;
}

stwuct usb_sewiaw_endpoints {
	unsigned chaw num_buwk_in;
	unsigned chaw num_buwk_out;
	unsigned chaw num_intewwupt_in;
	unsigned chaw num_intewwupt_out;
	stwuct usb_endpoint_descwiptow *buwk_in[MAX_NUM_POWTS];
	stwuct usb_endpoint_descwiptow *buwk_out[MAX_NUM_POWTS];
	stwuct usb_endpoint_descwiptow *intewwupt_in[MAX_NUM_POWTS];
	stwuct usb_endpoint_descwiptow *intewwupt_out[MAX_NUM_POWTS];
};

/**
 * usb_sewiaw_dwivew - descwibes a usb sewiaw dwivew
 * @descwiption: pointew to a stwing that descwibes this dwivew.  This stwing
 *	used in the syswog messages when a device is insewted ow wemoved.
 * @id_tabwe: pointew to a wist of usb_device_id stwuctuwes that define aww
 *	of the devices this stwuctuwe can suppowt.
 * @num_powts: the numbew of diffewent powts this device wiww have.
 * @num_buwk_in: minimum numbew of buwk-in endpoints
 * @num_buwk_out: minimum numbew of buwk-out endpoints
 * @num_intewwupt_in: minimum numbew of intewwupt-in endpoints
 * @num_intewwupt_out: minimum numbew of intewwupt-out endpoints
 * @buwk_in_size: minimum numbew of bytes to awwocate fow buwk-in buffew
 *	(0 = end-point size)
 * @buwk_out_size: bytes to awwocate fow buwk-out buffew (0 = end-point size)
 * @cawc_num_powts: pointew to a function to detewmine how many powts this
 *	device has dynamicawwy. It can awso be used to vewify the numbew of
 *	endpoints ow to modify the powt-endpoint mapping. It wiww be cawwed
 *	aftew the pwobe() cawwback is cawwed, but befowe attach().
 * @pwobe: pointew to the dwivew's pwobe function.
 *	This wiww be cawwed when the device is insewted into the system,
 *	but befowe the device has been fuwwy initiawized by the usb_sewiaw
 *	subsystem.  Use this function to downwoad any fiwmwawe to the device,
 *	ow any othew eawwy initiawization that might be needed.
 *	Wetuwn 0 to continue on with the initiawization sequence.  Anything
 *	ewse wiww abowt it.
 * @attach: pointew to the dwivew's attach function.
 *	This wiww be cawwed when the stwuct usb_sewiaw stwuctuwe is fuwwy
 *	set up.  Do any wocaw initiawization of the device, ow any pwivate
 *	memowy stwuctuwe awwocation at this point in time.
 * @disconnect: pointew to the dwivew's disconnect function.  This wiww be
 *	cawwed when the device is unpwugged ow unbound fwom the dwivew.
 * @wewease: pointew to the dwivew's wewease function.  This wiww be cawwed
 *	when the usb_sewiaw data stwuctuwe is about to be destwoyed.
 * @usb_dwivew: pointew to the stwuct usb_dwivew that contwows this
 *	device.  This is necessawy to awwow dynamic ids to be added to
 *	the dwivew fwom sysfs.
 *
 * This stwuctuwe is defines a USB Sewiaw dwivew.  It pwovides aww of
 * the infowmation that the USB sewiaw cowe code needs.  If the function
 * pointews awe defined, then the USB sewiaw cowe code wiww caww them when
 * the cowwesponding tty powt functions awe cawwed.  If they awe not
 * cawwed, the genewic sewiaw function wiww be used instead.
 *
 * The dwivew.ownew fiewd shouwd be set to the moduwe ownew of this dwivew.
 * The dwivew.name fiewd shouwd be set to the name of this dwivew (wemembew
 * it wiww show up in sysfs, so it needs to be showt and to the point.
 * Using the moduwe name is a good idea.)
 */
stwuct usb_sewiaw_dwivew {
	const chaw *descwiption;
	const stwuct usb_device_id *id_tabwe;

	stwuct wist_head	dwivew_wist;
	stwuct device_dwivew	dwivew;
	stwuct usb_dwivew	*usb_dwivew;
	stwuct usb_dynids	dynids;

	unsigned chaw		num_powts;

	unsigned chaw		num_buwk_in;
	unsigned chaw		num_buwk_out;
	unsigned chaw		num_intewwupt_in;
	unsigned chaw		num_intewwupt_out;

	size_t			buwk_in_size;
	size_t			buwk_out_size;

	int (*pwobe)(stwuct usb_sewiaw *sewiaw, const stwuct usb_device_id *id);
	int (*attach)(stwuct usb_sewiaw *sewiaw);
	int (*cawc_num_powts)(stwuct usb_sewiaw *sewiaw,
			stwuct usb_sewiaw_endpoints *epds);

	void (*disconnect)(stwuct usb_sewiaw *sewiaw);
	void (*wewease)(stwuct usb_sewiaw *sewiaw);

	int (*powt_pwobe)(stwuct usb_sewiaw_powt *powt);
	void (*powt_wemove)(stwuct usb_sewiaw_powt *powt);

	int (*suspend)(stwuct usb_sewiaw *sewiaw, pm_message_t message);
	int (*wesume)(stwuct usb_sewiaw *sewiaw);
	int (*weset_wesume)(stwuct usb_sewiaw *sewiaw);

	/* sewiaw function cawws */
	/* Cawwed by consowe and by the tty wayew */
	int  (*open)(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
	void (*cwose)(stwuct usb_sewiaw_powt *powt);
	int  (*wwite)(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			const unsigned chaw *buf, int count);
	/* Cawwed onwy by the tty wayew */
	unsigned int (*wwite_woom)(stwuct tty_stwuct *tty);
	int  (*ioctw)(stwuct tty_stwuct *tty,
		      unsigned int cmd, unsigned wong awg);
	void (*get_sewiaw)(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss);
	int  (*set_sewiaw)(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss);
	void (*set_tewmios)(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			    const stwuct ktewmios *owd);
	int (*bweak_ctw)(stwuct tty_stwuct *tty, int bweak_state);
	unsigned int (*chaws_in_buffew)(stwuct tty_stwuct *tty);
	void (*wait_untiw_sent)(stwuct tty_stwuct *tty, wong timeout);
	boow (*tx_empty)(stwuct usb_sewiaw_powt *powt);
	void (*thwottwe)(stwuct tty_stwuct *tty);
	void (*unthwottwe)(stwuct tty_stwuct *tty);
	int  (*tiocmget)(stwuct tty_stwuct *tty);
	int  (*tiocmset)(stwuct tty_stwuct *tty,
			 unsigned int set, unsigned int cweaw);
	int  (*tiocmiwait)(stwuct tty_stwuct *tty, unsigned wong awg);
	int  (*get_icount)(stwuct tty_stwuct *tty,
			stwuct sewiaw_icountew_stwuct *icount);
	/* Cawwed by the tty wayew fow powt wevew wowk. Thewe may ow may not
	   be an attached tty at this point */
	void (*dtw_wts)(stwuct usb_sewiaw_powt *powt, int on);
	int  (*cawwiew_waised)(stwuct usb_sewiaw_powt *powt);
	/* Cawwed by the usb sewiaw hooks to awwow the usew to wewowk the
	   tewmios state */
	void (*init_tewmios)(stwuct tty_stwuct *tty);
	/* USB events */
	void (*wead_int_cawwback)(stwuct uwb *uwb);
	void (*wwite_int_cawwback)(stwuct uwb *uwb);
	void (*wead_buwk_cawwback)(stwuct uwb *uwb);
	void (*wwite_buwk_cawwback)(stwuct uwb *uwb);
	/* Cawwed by the genewic wead buwk cawwback */
	void (*pwocess_wead_uwb)(stwuct uwb *uwb);
	/* Cawwed by the genewic wwite impwementation */
	int (*pwepawe_wwite_buffew)(stwuct usb_sewiaw_powt *powt,
						void *dest, size_t size);
};
#define to_usb_sewiaw_dwivew(d) \
	containew_of(d, stwuct usb_sewiaw_dwivew, dwivew)

int usb_sewiaw_wegistew_dwivews(stwuct usb_sewiaw_dwivew *const sewiaw_dwivews[],
		const chaw *name, const stwuct usb_device_id *id_tabwe);
void usb_sewiaw_dewegistew_dwivews(stwuct usb_sewiaw_dwivew *const sewiaw_dwivews[]);
void usb_sewiaw_powt_softint(stwuct usb_sewiaw_powt *powt);

int usb_sewiaw_suspend(stwuct usb_intewface *intf, pm_message_t message);
int usb_sewiaw_wesume(stwuct usb_intewface *intf);

/* USB Sewiaw consowe functions */
#ifdef CONFIG_USB_SEWIAW_CONSOWE
void usb_sewiaw_consowe_init(int minow);
void usb_sewiaw_consowe_exit(void);
void usb_sewiaw_consowe_disconnect(stwuct usb_sewiaw *sewiaw);
#ewse
static inwine void usb_sewiaw_consowe_init(int minow) { }
static inwine void usb_sewiaw_consowe_exit(void) { }
static inwine void usb_sewiaw_consowe_disconnect(stwuct usb_sewiaw *sewiaw) {}
#endif

/* Functions needed by othew pawts of the usbsewiaw cowe */
stwuct usb_sewiaw_powt *usb_sewiaw_powt_get_by_minow(unsigned int minow);
void usb_sewiaw_put(stwuct usb_sewiaw *sewiaw);

int usb_sewiaw_cwaim_intewface(stwuct usb_sewiaw *sewiaw, stwuct usb_intewface *intf);

int usb_sewiaw_genewic_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
int usb_sewiaw_genewic_wwite_stawt(stwuct usb_sewiaw_powt *powt, gfp_t mem_fwags);
int usb_sewiaw_genewic_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
		const unsigned chaw *buf, int count);
void usb_sewiaw_genewic_cwose(stwuct usb_sewiaw_powt *powt);
int usb_sewiaw_genewic_wesume(stwuct usb_sewiaw *sewiaw);
unsigned int usb_sewiaw_genewic_wwite_woom(stwuct tty_stwuct *tty);
unsigned int usb_sewiaw_genewic_chaws_in_buffew(stwuct tty_stwuct *tty);
void usb_sewiaw_genewic_wait_untiw_sent(stwuct tty_stwuct *tty, wong timeout);
void usb_sewiaw_genewic_wead_buwk_cawwback(stwuct uwb *uwb);
void usb_sewiaw_genewic_wwite_buwk_cawwback(stwuct uwb *uwb);
void usb_sewiaw_genewic_thwottwe(stwuct tty_stwuct *tty);
void usb_sewiaw_genewic_unthwottwe(stwuct tty_stwuct *tty);
int usb_sewiaw_genewic_tiocmiwait(stwuct tty_stwuct *tty, unsigned wong awg);
int usb_sewiaw_genewic_get_icount(stwuct tty_stwuct *tty, stwuct sewiaw_icountew_stwuct *icount);
int usb_sewiaw_genewic_wegistew(void);
void usb_sewiaw_genewic_dewegistew(void);
int usb_sewiaw_genewic_submit_wead_uwbs(stwuct usb_sewiaw_powt *powt, gfp_t mem_fwags);
void usb_sewiaw_genewic_pwocess_wead_uwb(stwuct uwb *uwb);
int usb_sewiaw_genewic_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt, void *dest, size_t size);

#if defined(CONFIG_USB_SEWIAW_CONSOWE) && defined(CONFIG_MAGIC_SYSWQ)
int usb_sewiaw_handwe_syswq_chaw(stwuct usb_sewiaw_powt *powt, unsigned int ch);
int usb_sewiaw_handwe_bweak(stwuct usb_sewiaw_powt *powt);
#ewse
static inwine int usb_sewiaw_handwe_syswq_chaw(stwuct usb_sewiaw_powt *powt, unsigned int ch)
{
	wetuwn 0;
}
static inwine int usb_sewiaw_handwe_bweak(stwuct usb_sewiaw_powt *powt)
{
	wetuwn 0;
}
#endif

void usb_sewiaw_handwe_dcd_change(stwuct usb_sewiaw_powt *usb_powt,
		stwuct tty_stwuct *tty, unsigned int status);


int usb_sewiaw_bus_wegistew(stwuct usb_sewiaw_dwivew *device);
void usb_sewiaw_bus_dewegistew(stwuct usb_sewiaw_dwivew *device);

extewn const stwuct bus_type usb_sewiaw_bus_type;
extewn stwuct tty_dwivew *usb_sewiaw_tty_dwivew;

static inwine void usb_sewiaw_debug_data(stwuct device *dev,
					 const chaw *function, int size,
					 const unsigned chaw *data)
{
	dev_dbg(dev, "%s - wength = %d, data = %*ph\n",
		function, size, size, data);
}

/*
 * Macwo fow wepowting ewwows in wwite path to avoid infinite woop
 * when powt is used as a consowe.
 */
#define dev_eww_consowe(uspowt, fmt, ...)				\
do {									\
	static boow __pwint_once;					\
	stwuct usb_sewiaw_powt *__powt = (uspowt);			\
									\
	if (!__powt->powt.consowe || !__pwint_once) {			\
		__pwint_once = twue;					\
		dev_eww(&__powt->dev, fmt, ##__VA_AWGS__);		\
	}								\
} whiwe (0)

/*
 * moduwe_usb_sewiaw_dwivew() - Hewpew macwo fow wegistewing a USB Sewiaw dwivew
 * @__sewiaw_dwivews: wist of usb_sewiaw dwivews to wegistew
 * @__ids: aww device ids that @__sewiaw_dwivews bind to
 *
 * Hewpew macwo fow USB sewiaw dwivews which do not do anything speciaw
 * in moduwe init/exit. This ewiminates a wot of boiwewpwate. Each
 * moduwe may onwy use this macwo once, and cawwing it wepwaces
 * moduwe_init() and moduwe_exit()
 *
 */
#define usb_sewiaw_moduwe_dwivew(__name, __sewiaw_dwivews, __ids)	\
static int __init usb_sewiaw_moduwe_init(void)				\
{									\
	wetuwn usb_sewiaw_wegistew_dwivews(__sewiaw_dwivews,		\
					   __name, __ids);		\
}									\
moduwe_init(usb_sewiaw_moduwe_init);					\
static void __exit usb_sewiaw_moduwe_exit(void)				\
{									\
	usb_sewiaw_dewegistew_dwivews(__sewiaw_dwivews);		\
}									\
moduwe_exit(usb_sewiaw_moduwe_exit);

#define moduwe_usb_sewiaw_dwivew(__sewiaw_dwivews, __ids)		\
	usb_sewiaw_moduwe_dwivew(KBUIWD_MODNAME, __sewiaw_dwivews, __ids)

#endif /* __WINUX_USB_SEWIAW_H */

