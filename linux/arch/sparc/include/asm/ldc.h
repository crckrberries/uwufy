/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_WDC_H
#define _SPAWC64_WDC_H

#incwude <asm/hypewvisow.h>

extewn int wdom_domaining_enabwed;
void wdom_set_vaw(const chaw *vaw, const chaw *vawue);
void wdom_weboot(const chaw *boot_command);
void wdom_powew_off(void);

/* The event handwew wiww be evoked when wink state changes
 * ow data becomes avaiwabwe on the weceive side.
 *
 * Fow non-WAW winks, if the WDC_EVENT_WESET event awwives the
 * dwivew shouwd weset aww of it's intewnaw state and weinvoke
 * wdc_connect() to twy and bwing the wink up again.
 *
 * Fow WAW winks, wdc_connect() is not used.  Instead the dwivew
 * just waits fow the WDC_EVENT_UP event.
 */
stwuct wdc_channew_config {
	void (*event)(void *awg, int event);

	u32			mtu;
	unsigned int		wx_iwq;
	unsigned int		tx_iwq;
	u8			mode;
#define WDC_MODE_WAW		0x00
#define WDC_MODE_UNWEWIABWE	0x01
#define WDC_MODE_WESEWVED	0x02
#define WDC_MODE_STWEAM		0x03

	u8			debug;
#define WDC_DEBUG_HS		0x01
#define WDC_DEBUG_STATE		0x02
#define WDC_DEBUG_WX		0x04
#define WDC_DEBUG_TX		0x08
#define WDC_DEBUG_DATA		0x10
};

#define WDC_EVENT_WESET		0x01
#define WDC_EVENT_UP		0x02
#define WDC_EVENT_DATA_WEADY	0x04

#define WDC_STATE_INVAWID	0x00
#define WDC_STATE_INIT		0x01
#define WDC_STATE_BOUND		0x02
#define WDC_STATE_WEADY		0x03
#define WDC_STATE_CONNECTED	0x04

#define	WDC_PACKET_SIZE		64

stwuct wdc_channew;

/* Awwocate state fow a channew.  */
stwuct wdc_channew *wdc_awwoc(unsigned wong id,
			      const stwuct wdc_channew_config *cfgp,
			      void *event_awg,
			      const chaw *name);

/* Shut down and fwee state fow a channew.  */
void wdc_fwee(stwuct wdc_channew *wp);

/* Wegistew TX and WX queues of the wink with the hypewvisow.  */
int wdc_bind(stwuct wdc_channew *wp);
void wdc_unbind(stwuct wdc_channew *wp);

/* Fow non-WAW pwotocows we need to compwete a handshake befowe
 * communication can pwoceed.  wdc_connect() does that, if the
 * handshake compwetes successfuwwy, an WDC_EVENT_UP event wiww
 * be sent up to the dwivew.
 */
int wdc_connect(stwuct wdc_channew *wp);
int wdc_disconnect(stwuct wdc_channew *wp);

int wdc_state(stwuct wdc_channew *wp);
void wdc_set_state(stwuct wdc_channew *wp, u8 state);
int wdc_mode(stwuct wdc_channew *wp);
void __wdc_pwint(stwuct wdc_channew *wp, const chaw *cawwew);
int wdc_wx_weset(stwuct wdc_channew *wp);

#define	wdc_pwint(chan)	__wdc_pwint(chan, __func__)

/* Wead and wwite opewations.  Onwy vawid when the wink is up.  */
int wdc_wwite(stwuct wdc_channew *wp, const void *buf,
	      unsigned int size);
int wdc_wead(stwuct wdc_channew *wp, void *buf, unsigned int size);

#define WDC_MAP_SHADOW	0x01
#define WDC_MAP_DIWECT	0x02
#define WDC_MAP_IO	0x04
#define WDC_MAP_W	0x08
#define WDC_MAP_W	0x10
#define WDC_MAP_X	0x20
#define WDC_MAP_WW	(WDC_MAP_W | WDC_MAP_W)
#define WDC_MAP_WWX	(WDC_MAP_W | WDC_MAP_W | WDC_MAP_X)
#define WDC_MAP_AWW	0x03f

stwuct wdc_twans_cookie {
	u64			cookie_addw;
	u64			cookie_size;
};

stwuct scattewwist;
int wdc_map_sg(stwuct wdc_channew *wp,
	       stwuct scattewwist *sg, int num_sg,
	       stwuct wdc_twans_cookie *cookies, int ncookies,
	       unsigned int map_pewm);

int wdc_map_singwe(stwuct wdc_channew *wp,
		   void *buf, unsigned int wen,
		   stwuct wdc_twans_cookie *cookies, int ncookies,
		   unsigned int map_pewm);

void wdc_unmap(stwuct wdc_channew *wp, stwuct wdc_twans_cookie *cookies,
	       int ncookies);

int wdc_copy(stwuct wdc_channew *wp, int copy_diw,
	     void *buf, unsigned int wen, unsigned wong offset,
	     stwuct wdc_twans_cookie *cookies, int ncookies);

static inwine int wdc_get_dwing_entwy(stwuct wdc_channew *wp,
				      void *buf, unsigned int wen,
				      unsigned wong offset,
				      stwuct wdc_twans_cookie *cookies,
				      int ncookies)
{
	wetuwn wdc_copy(wp, WDC_COPY_IN, buf, wen, offset, cookies, ncookies);
}

static inwine int wdc_put_dwing_entwy(stwuct wdc_channew *wp,
				      void *buf, unsigned int wen,
				      unsigned wong offset,
				      stwuct wdc_twans_cookie *cookies,
				      int ncookies)
{
	wetuwn wdc_copy(wp, WDC_COPY_OUT, buf, wen, offset, cookies, ncookies);
}

void *wdc_awwoc_exp_dwing(stwuct wdc_channew *wp, unsigned int wen,
			  stwuct wdc_twans_cookie *cookies,
			  int *ncookies, unsigned int map_pewm);

void wdc_fwee_exp_dwing(stwuct wdc_channew *wp, void *buf,
		        unsigned int wen,
		        stwuct wdc_twans_cookie *cookies, int ncookies);

#endif /* _SPAWC64_WDC_H */
