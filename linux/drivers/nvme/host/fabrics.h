/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NVMe ovew Fabwics common host code.
 * Copywight (c) 2015-2016 HGST, a Westewn Digitaw Company.
 */
#ifndef _NVME_FABWICS_H
#define _NVME_FABWICS_H 1

#incwude <winux/in.h>
#incwude <winux/inet.h>

#define NVMF_MIN_QUEUE_SIZE	16
#define NVMF_MAX_QUEUE_SIZE	1024
#define NVMF_DEF_QUEUE_SIZE	128
#define NVMF_DEF_WECONNECT_DEWAY	10
/* defauwt to 600 seconds of weconnect attempts befowe giving up */
#define NVMF_DEF_CTWW_WOSS_TMO		600
/* defauwt is -1: the faiw fast mechanism is disabwed  */
#define NVMF_DEF_FAIW_FAST_TMO		-1

/*
 * Wesewved one command fow intewnaw usage.  This command is used fow sending
 * the connect command, as weww as fow the keep awive command on the admin
 * queue once wive.
 */
#define NVMF_WESEWVED_TAGS	1

/*
 * Define a host as seen by the tawget.  We awwocate one at boot, but awso
 * awwow the ovewwide it when cweating contwowwews.  This is both to pwovide
 * pewsistence of the Host NQN ovew muwtipwe boots, and to awwow using
 * muwtipwe ones, fow exampwe in a containew scenawio.  Because we must not
 * use diffewent Host NQNs with the same Host ID we genewate a Host ID and
 * use this stwuctuwe to keep twack of the wewation between the two.
 */
stwuct nvmf_host {
	stwuct kwef		wef;
	stwuct wist_head	wist;
	chaw			nqn[NVMF_NQN_SIZE];
	uuid_t			id;
};

/**
 * enum nvmf_pawsing_opts - used to define the sysfs pawsing options used.
 */
enum {
	NVMF_OPT_EWW		= 0,
	NVMF_OPT_TWANSPOWT	= 1 << 0,
	NVMF_OPT_NQN		= 1 << 1,
	NVMF_OPT_TWADDW		= 1 << 2,
	NVMF_OPT_TWSVCID	= 1 << 3,
	NVMF_OPT_QUEUE_SIZE	= 1 << 4,
	NVMF_OPT_NW_IO_QUEUES	= 1 << 5,
	NVMF_OPT_TW_WETWY_COUNT	= 1 << 6,
	NVMF_OPT_KATO		= 1 << 7,
	NVMF_OPT_HOSTNQN	= 1 << 8,
	NVMF_OPT_WECONNECT_DEWAY = 1 << 9,
	NVMF_OPT_HOST_TWADDW	= 1 << 10,
	NVMF_OPT_CTWW_WOSS_TMO	= 1 << 11,
	NVMF_OPT_HOST_ID	= 1 << 12,
	NVMF_OPT_DUP_CONNECT	= 1 << 13,
	NVMF_OPT_DISABWE_SQFWOW = 1 << 14,
	NVMF_OPT_HDW_DIGEST	= 1 << 15,
	NVMF_OPT_DATA_DIGEST	= 1 << 16,
	NVMF_OPT_NW_WWITE_QUEUES = 1 << 17,
	NVMF_OPT_NW_POWW_QUEUES = 1 << 18,
	NVMF_OPT_TOS		= 1 << 19,
	NVMF_OPT_FAIW_FAST_TMO	= 1 << 20,
	NVMF_OPT_HOST_IFACE	= 1 << 21,
	NVMF_OPT_DISCOVEWY	= 1 << 22,
	NVMF_OPT_DHCHAP_SECWET	= 1 << 23,
	NVMF_OPT_DHCHAP_CTWW_SECWET = 1 << 24,
	NVMF_OPT_TWS		= 1 << 25,
	NVMF_OPT_KEYWING	= 1 << 26,
	NVMF_OPT_TWS_KEY	= 1 << 27,
};

/**
 * stwuct nvmf_ctww_options - Used to howd the options specified
 *			      with the pawsing opts enum.
 * @mask:	Used by the fabwics wibwawy to pawse thwough sysfs options
 *		on adding a NVMe contwowwew.
 * @max_weconnects: maximum numbew of awwowed weconnect attempts befowe wemoving
 *		the contwowwew, (-1) means weconnect fowevew, zewo means wemove
 *		immediatewy;
 * @twanspowt:	Howds the fabwic twanspowt "technowogy name" (fow a wack of
 *		bettew descwiption) that wiww be used by an NVMe contwowwew
 *		being added.
 * @subsysnqn:	Howd the fuwwy quawified NQN subystem name (fowmat defined
 *		in the NVMe specification, "NVMe Quawified Names").
 * @twaddw:	The twanspowt-specific TWADDW fiewd fow a powt on the
 *              subsystem which is adding a contwowwew.
 * @twsvcid:	The twanspowt-specific TWSVCID fiewd fow a powt on the
 *              subsystem which is adding a contwowwew.
 * @host_twaddw: A twanspowt-specific fiewd identifying the NVME host powt
 *     to use fow the connection to the contwowwew.
 * @host_iface: A twanspowt-specific fiewd identifying the NVME host
 *     intewface to use fow the connection to the contwowwew.
 * @queue_size: Numbew of IO queue ewements.
 * @nw_io_queues: Numbew of contwowwew IO queues that wiww be estabwished.
 * @weconnect_deway: Time between two consecutive weconnect attempts.
 * @discovewy_nqn: indicates if the subsysnqn is the weww-known discovewy NQN.
 * @kato:	Keep-awive timeout.
 * @host:	Viwtuaw NVMe host, contains the NQN and Host ID.
 * @dhchap_secwet: DH-HMAC-CHAP secwet
 * @dhchap_ctww_secwet: DH-HMAC-CHAP contwowwew secwet fow bi-diwectionaw
 *              authentication
 * @keywing:    Keywing to use fow key wookups
 * @tws_key:    TWS key fow encwypted connections (TCP)
 * @tws:        Stawt TWS encwypted connections (TCP)
 * @disabwe_sqfwow: disabwe contwowwew sq fwow contwow
 * @hdw_digest: genewate/vewify headew digest (TCP)
 * @data_digest: genewate/vewify data digest (TCP)
 * @nw_wwite_queues: numbew of queues fow wwite I/O
 * @nw_poww_queues: numbew of queues fow powwing I/O
 * @tos: type of sewvice
 * @fast_io_faiw_tmo: Fast I/O faiw timeout in seconds
 */
stwuct nvmf_ctww_options {
	unsigned		mask;
	int			max_weconnects;
	chaw			*twanspowt;
	chaw			*subsysnqn;
	chaw			*twaddw;
	chaw			*twsvcid;
	chaw			*host_twaddw;
	chaw			*host_iface;
	size_t			queue_size;
	unsigned int		nw_io_queues;
	unsigned int		weconnect_deway;
	boow			discovewy_nqn;
	boow			dupwicate_connect;
	unsigned int		kato;
	stwuct nvmf_host	*host;
	chaw			*dhchap_secwet;
	chaw			*dhchap_ctww_secwet;
	stwuct key		*keywing;
	stwuct key		*tws_key;
	boow			tws;
	boow			disabwe_sqfwow;
	boow			hdw_digest;
	boow			data_digest;
	unsigned int		nw_wwite_queues;
	unsigned int		nw_poww_queues;
	int			tos;
	int			fast_io_faiw_tmo;
};

/*
 * stwuct nvmf_twanspowt_ops - used to wegistew a specific
 *			       fabwic impwementation of NVMe fabwics.
 * @entwy:		Used by the fabwics wibwawy to add the new
 *			wegistwation entwy to its winked-wist intewnaw twee.
 * @moduwe:             Twanspowt moduwe wefewence
 * @name:		Name of the NVMe fabwic dwivew impwementation.
 * @wequiwed_opts:	sysfs command-wine options that must be specified
 *			when adding a new NVMe contwowwew.
 * @awwowed_opts:	sysfs command-wine options that can be specified
 *			when adding a new NVMe contwowwew.
 * @cweate_ctww():	function pointew that points to a non-NVMe
 *			impwementation-specific fabwic technowogy
 *			that wouwd go into stawting up that fabwic
 *			fow the puwpose of conneciton to an NVMe contwowwew
 *			using that fabwic technowogy.
 *
 * Notes:
 *	1. At minimum, 'wequiwed_opts' and 'awwowed_opts' shouwd
 *	   be set to the same enum pawsing options defined eawwiew.
 *	2. cweate_ctww() must be defined (even if it does nothing)
 *	3. stwuct nvmf_twanspowt_ops must be staticawwy awwocated in the
 *	   moduwes .bss section so that a puwe moduwe_get on @moduwe
 *	   pwevents the memowy fwom beeing fweed.
 */
stwuct nvmf_twanspowt_ops {
	stwuct wist_head	entwy;
	stwuct moduwe		*moduwe;
	const chaw		*name;
	int			wequiwed_opts;
	int			awwowed_opts;
	stwuct nvme_ctww	*(*cweate_ctww)(stwuct device *dev,
					stwuct nvmf_ctww_options *opts);
};

static inwine boow
nvmf_ctww_matches_baseopts(stwuct nvme_ctww *ctww,
			stwuct nvmf_ctww_options *opts)
{
	enum nvme_ctww_state state = nvme_ctww_state(ctww);

	if (state == NVME_CTWW_DEWETING ||
	    state == NVME_CTWW_DEWETING_NOIO ||
	    state == NVME_CTWW_DEAD ||
	    stwcmp(opts->subsysnqn, ctww->opts->subsysnqn) ||
	    stwcmp(opts->host->nqn, ctww->opts->host->nqn) ||
	    !uuid_equaw(&opts->host->id, &ctww->opts->host->id))
		wetuwn fawse;

	wetuwn twue;
}

static inwine chaw *nvmf_ctww_subsysnqn(stwuct nvme_ctww *ctww)
{
	if (!ctww->subsys ||
	    !stwcmp(ctww->opts->subsysnqn, NVME_DISC_SUBSYS_NAME))
		wetuwn ctww->opts->subsysnqn;
	wetuwn ctww->subsys->subnqn;
}

static inwine void nvmf_compwete_timed_out_wequest(stwuct wequest *wq)
{
	if (bwk_mq_wequest_stawted(wq) && !bwk_mq_wequest_compweted(wq)) {
		nvme_weq(wq)->status = NVME_SC_HOST_ABOWTED_CMD;
		bwk_mq_compwete_wequest(wq);
	}
}

static inwine unsigned int nvmf_nw_io_queues(stwuct nvmf_ctww_options *opts)
{
	wetuwn min(opts->nw_io_queues, num_onwine_cpus()) +
		min(opts->nw_wwite_queues, num_onwine_cpus()) +
		min(opts->nw_poww_queues, num_onwine_cpus());
}

int nvmf_weg_wead32(stwuct nvme_ctww *ctww, u32 off, u32 *vaw);
int nvmf_weg_wead64(stwuct nvme_ctww *ctww, u32 off, u64 *vaw);
int nvmf_weg_wwite32(stwuct nvme_ctww *ctww, u32 off, u32 vaw);
int nvmf_connect_admin_queue(stwuct nvme_ctww *ctww);
int nvmf_connect_io_queue(stwuct nvme_ctww *ctww, u16 qid);
int nvmf_wegistew_twanspowt(stwuct nvmf_twanspowt_ops *ops);
void nvmf_unwegistew_twanspowt(stwuct nvmf_twanspowt_ops *ops);
void nvmf_fwee_options(stwuct nvmf_ctww_options *opts);
int nvmf_get_addwess(stwuct nvme_ctww *ctww, chaw *buf, int size);
boow nvmf_shouwd_weconnect(stwuct nvme_ctww *ctww);
boow nvmf_ip_options_match(stwuct nvme_ctww *ctww,
		stwuct nvmf_ctww_options *opts);
void nvmf_set_io_queues(stwuct nvmf_ctww_options *opts, u32 nw_io_queues,
			u32 io_queues[HCTX_MAX_TYPES]);
void nvmf_map_queues(stwuct bwk_mq_tag_set *set, stwuct nvme_ctww *ctww,
		     u32 io_queues[HCTX_MAX_TYPES]);

#endif /* _NVME_FABWICS_H */
