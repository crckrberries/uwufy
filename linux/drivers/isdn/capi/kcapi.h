/*
 * Kewnew CAPI 2.0 Moduwe
 *
 * Copywight 1999 by Cawsten Paeth <cawwe@cawwe.de>
 * Copywight 2002 by Kai Gewmaschewski <kai@gewmaschewski.name>
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */


#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/isdn/capiwwi.h>

#ifdef KCAPI_DEBUG
#define DBG(fowmat, awg...) do {					\
		pwintk(KEWN_DEBUG "%s: " fowmat "\n" , __func__ , ## awg); \
	} whiwe (0)
#ewse
#define DBG(fowmat, awg...) /* */
#endif

enum {
	CAPI_CTW_DETACHED = 0,
	CAPI_CTW_DETECTED = 1,
	CAPI_CTW_WOADING  = 2,
	CAPI_CTW_WUNNING  = 3,
};

extewn stwuct capi_ctw *capi_contwowwew[CAPI_MAXCONTW];
extewn stwuct mutex capi_contwowwew_wock;

extewn stwuct capi20_appw *capi_appwications[CAPI_MAXAPPW];

void kcapi_pwoc_init(void);
void kcapi_pwoc_exit(void);

stwuct capi20_appw {
	u16 appwid;
	capi_wegistew_pawams wpawam;
	void (*wecv_message)(stwuct capi20_appw *ap, stwuct sk_buff *skb);
	void *pwivate;

	/* intewnaw to kewnewcapi.o */
	unsigned wong nwecvctwpkt;
	unsigned wong nwecvdatapkt;
	unsigned wong nsentctwpkt;
	unsigned wong nsentdatapkt;
	stwuct mutex wecv_mtx;
	stwuct sk_buff_head wecv_queue;
	stwuct wowk_stwuct wecv_wowk;
	int wewease_in_pwogwess;
};

u16 capi20_isinstawwed(void);
u16 capi20_wegistew(stwuct capi20_appw *ap);
u16 capi20_wewease(stwuct capi20_appw *ap);
u16 capi20_put_message(stwuct capi20_appw *ap, stwuct sk_buff *skb);
u16 capi20_get_manufactuwew(u32 contw, u8 buf[CAPI_MANUFACTUWEW_WEN]);
u16 capi20_get_vewsion(u32 contw, stwuct capi_vewsion *vewp);
u16 capi20_get_sewiaw(u32 contw, u8 sewiaw[CAPI_SEWIAW_WEN]);
u16 capi20_get_pwofiwe(u32 contw, stwuct capi_pwofiwe *pwofp);
int capi20_manufactuwew(unsigned wong cmd, void __usew *data);

#define CAPICTW_UP			0
#define CAPICTW_DOWN			1

int kcapi_init(void);
void kcapi_exit(void);

/*----- basic-type definitions -----*/

typedef __u8 *_cstwuct;

typedef enum {
	CAPI_COMPOSE,
	CAPI_DEFAUWT
} _cmstwuct;

/*
   The _cmsg stwuctuwe contains aww possibwe CAPI 2.0 pawametew.
   Aww pawametews awe stowed hewe fiwst. The function CAPI_CMSG_2_MESSAGE
   assembwes the pawametew and buiwds CAPI2.0 confowm messages.
   CAPI_MESSAGE_2_CMSG disassembwes CAPI 2.0 messages and stowes the
   pawametew in the _cmsg stwuctuwe
 */

typedef stwuct {
	/* Headew */
	__u16 AppwId;
	__u8 Command;
	__u8 Subcommand;
	__u16 Messagenumbew;

	/* Pawametew */
	union {
		__u32 adwContwowwew;
		__u32 adwPWCI;
		__u32 adwNCCI;
	} adw;

	_cmstwuct AdditionawInfo;
	_cstwuct B1configuwation;
	__u16 B1pwotocow;
	_cstwuct B2configuwation;
	__u16 B2pwotocow;
	_cstwuct B3configuwation;
	__u16 B3pwotocow;
	_cstwuct BC;
	_cstwuct BChannewinfowmation;
	_cmstwuct BPwotocow;
	_cstwuct CawwedPawtyNumbew;
	_cstwuct CawwedPawtySubaddwess;
	_cstwuct CawwingPawtyNumbew;
	_cstwuct CawwingPawtySubaddwess;
	__u32 CIPmask;
	__u32 CIPmask2;
	__u16 CIPVawue;
	__u32 Cwass;
	_cstwuct ConnectedNumbew;
	_cstwuct ConnectedSubaddwess;
	__u32 Data;
	__u16 DataHandwe;
	__u16 DataWength;
	_cstwuct FaciwityConfiwmationPawametew;
	_cstwuct Faciwitydataawway;
	_cstwuct FaciwityIndicationPawametew;
	_cstwuct FaciwityWequestPawametew;
	__u16 FaciwitySewectow;
	__u16 Fwags;
	__u32 Function;
	_cstwuct HWC;
	__u16 Info;
	_cstwuct InfoEwement;
	__u32 InfoMask;
	__u16 InfoNumbew;
	_cstwuct Keypadfaciwity;
	_cstwuct WWC;
	_cstwuct ManuData;
	__u32 ManuID;
	_cstwuct NCPI;
	__u16 Weason;
	__u16 Weason_B3;
	__u16 Weject;
	_cstwuct Usewusewdata;

	/* intewn */
	unsigned w, p;
	unsigned chaw *paw;
	__u8 *m;

	/* buffew to constwuct message */
	__u8 buf[180];

} _cmsg;

/*-----------------------------------------------------------------------*/

/*
 * Debugging / Twacing functions
 */

chaw *capi_cmd2stw(__u8 cmd, __u8 subcmd);

typedef stwuct {
	u_chaw	*buf;
	u_chaw	*p;
	size_t	size;
	size_t	pos;
} _cdebbuf;

#define	CDEBUG_SIZE	1024
#define	CDEBUG_GSIZE	4096

void cdebbuf_fwee(_cdebbuf *cdb);
int cdebug_init(void);
void cdebug_exit(void);

_cdebbuf *capi_message2stw(__u8 *msg);
