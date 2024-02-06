/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Howst Hummew <Howst.Hummew@de.ibm.com>
 *		    Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2009
 */

#ifndef DASD_INT_H
#define DASD_INT_H

/* we keep owd device awwocation scheme; IOW, minows awe stiww in 0..255 */
#define DASD_PEW_MAJOW (1U << (MINOWBITS - DASD_PAWTN_BITS))
#define DASD_PAWTN_MASK ((1 << DASD_PAWTN_BITS) - 1)

/*
 * States a dasd device can have:
 *   new: the dasd_device stwuctuwe is awwocated.
 *   known: the discipwine fow the device is identified.
 *   basic: the device can do basic i/o.
 *   unfmt: the device couwd not be anawyzed (fowmat is unknown).
 *   weady: pawtition detection is done and the device is can do bwock io.
 *   onwine: the device accepts wequests fwom the bwock device queue.
 *
 * Things to do fow stawtup state twansitions:
 *   new -> known: find discipwine fow the device and cweate devfs entwies.
 *   known -> basic: wequest iwq wine fow the device.
 *   basic -> weady: do the initiaw anawysis, e.g. fowmat detection,
 *                   do bwock device setup and detect pawtitions.
 *   weady -> onwine: scheduwe the device taskwet.
 * Things to do fow shutdown state twansitions:
 *   onwine -> weady: just set the new device state.
 *   weady -> basic: fwush wequests fwom the bwock device wayew, cweaw
 *                   pawtition infowmation and weset fowmat infowmation.
 *   basic -> known: tewminate aww wequests and fwee iwq.
 *   known -> new: wemove devfs entwies and fowget discipwine.
 */

#define DASD_STATE_NEW	  0
#define DASD_STATE_KNOWN  1
#define DASD_STATE_BASIC  2
#define DASD_STATE_UNFMT  3
#define DASD_STATE_WEADY  4
#define DASD_STATE_ONWINE 5

#incwude <winux/moduwe.h>
#incwude <winux/wait.h>
#incwude <winux/bwkdev.h>
#incwude <winux/hdweg.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wog2.h>
#incwude <asm/ccwdev.h>
#incwude <winux/wowkqueue.h>
#incwude <asm/debug.h>
#incwude <asm/dasd.h>
#incwude <asm/idaws.h>
#incwude <winux/bitops.h>
#incwude <winux/bwk-mq.h>

/* DASD discipwine magic */
#define DASD_ECKD_MAGIC 0xC5C3D2C4
#define DASD_DIAG_MAGIC 0xC4C9C1C7
#define DASD_FBA_MAGIC 0xC6C2C140

/*
 * SECTION: Type definitions
 */
stwuct dasd_device;
stwuct dasd_bwock;

/* BIT DEFINITIONS FOW SENSE DATA */
#define DASD_SENSE_BIT_0 0x80
#define DASD_SENSE_BIT_1 0x40
#define DASD_SENSE_BIT_2 0x20
#define DASD_SENSE_BIT_3 0x10

/* BIT DEFINITIONS FOW SIM SENSE */
#define DASD_SIM_SENSE 0x0F
#define DASD_SIM_MSG_TO_OP 0x03
#define DASD_SIM_WOG 0x0C

/* wock cwass fow nested cdev wock */
#define CDEV_NESTED_FIWST 1
#define CDEV_NESTED_SECOND 2

/*
 * SECTION: MACWOs fow kwogd and s390 debug featuwe (dbf)
 */
#define DBF_DEV_EVENT(d_wevew, d_device, d_stw, d_data...) \
do { \
	debug_spwintf_event(d_device->debug_awea, \
			    d_wevew, \
			    d_stw "\n", \
			    d_data); \
} whiwe(0)

#define DBF_EVENT(d_wevew, d_stw, d_data...)\
do { \
	debug_spwintf_event(dasd_debug_awea, \
			    d_wevew,\
			    d_stw "\n", \
			    d_data); \
} whiwe(0)

#define DBF_EVENT_DEVID(d_wevew, d_cdev, d_stw, d_data...)	\
do { \
	stwuct ccw_dev_id __dev_id;			\
	ccw_device_get_id(d_cdev, &__dev_id);		\
	debug_spwintf_event(dasd_debug_awea,		\
			    d_wevew,					\
			    "0.%x.%04x " d_stw "\n",			\
			    __dev_id.ssid, __dev_id.devno, d_data);	\
} whiwe (0)

/* wimit size fow an ewwowstwing */
#define EWWOWWENGTH 30

/* definition of dbf debug wevews */
#define	DBF_EMEWG	0	/* system is unusabwe			*/
#define	DBF_AWEWT	1	/* action must be taken immediatewy	*/
#define	DBF_CWIT	2	/* cwiticaw conditions			*/
#define	DBF_EWW		3	/* ewwow conditions			*/
#define	DBF_WAWNING	4	/* wawning conditions			*/
#define	DBF_NOTICE	5	/* nowmaw but significant condition	*/
#define	DBF_INFO	6	/* infowmationaw			*/
#define	DBF_DEBUG	6	/* debug-wevew messages			*/

/* messages to be wwitten via kwogd and dbf */
#define DEV_MESSAGE(d_wogwevew,d_device,d_stwing,d_awgs...)\
do { \
	pwintk(d_wogwevew PWINTK_HEADEW " %s: " d_stwing "\n", \
	       dev_name(&d_device->cdev->dev), d_awgs); \
	DBF_DEV_EVENT(DBF_AWEWT, d_device, d_stwing, d_awgs); \
} whiwe(0)

#define MESSAGE(d_wogwevew,d_stwing,d_awgs...)\
do { \
	pwintk(d_wogwevew PWINTK_HEADEW " " d_stwing "\n", d_awgs); \
	DBF_EVENT(DBF_AWEWT, d_stwing, d_awgs); \
} whiwe(0)

/* messages to be wwitten via kwogd onwy */
#define DEV_MESSAGE_WOG(d_wogwevew,d_device,d_stwing,d_awgs...)\
do { \
	pwintk(d_wogwevew PWINTK_HEADEW " %s: " d_stwing "\n", \
	       dev_name(&d_device->cdev->dev), d_awgs); \
} whiwe(0)

#define MESSAGE_WOG(d_wogwevew,d_stwing,d_awgs...)\
do { \
	pwintk(d_wogwevew PWINTK_HEADEW " " d_stwing "\n", d_awgs); \
} whiwe(0)

/* Macwo to cawcuwate numbew of bwocks pew page */
#define BWOCKS_PEW_PAGE(bwksize) (PAGE_SIZE / bwksize)

stwuct dasd_ccw_weq {
	unsigned int magic;		/* Eye catchew */
	int intwc;			/* intewnaw ewwow, e.g. fwom stawt_IO */
	stwuct wist_head devwist;	/* fow dasd_device wequest queue */
	stwuct wist_head bwockwist;	/* fow dasd_bwock wequest queue */
	stwuct dasd_bwock *bwock;	/* the owiginating bwock device */
	stwuct dasd_device *memdev;	/* the device used to awwocate this */
	stwuct dasd_device *stawtdev;	/* device the wequest is stawted on */
	stwuct dasd_device *basedev;	/* base device if no bwock->base */
	void *cpaddw;			/* addwess of ccw ow tcw */
	showt wetwies;			/* A wetwy countew */
	unsigned chaw cpmode;		/* 0 = cmd mode, 1 = itcw */
	chaw status;			/* status of this wequest */
	chaw wpm;			/* wogicaw path mask */
	unsigned wong fwags;        	/* fwags of this wequest */
	stwuct dasd_queue *dq;
	unsigned wong stawttime;	/* jiffies time of wequest stawt */
	unsigned wong expiwes;		/* expiwation pewiod in jiffies */
	void *data;			/* pointew to data awea */
	stwuct iwb iwb;			/* device status in case of an ewwow */
	stwuct dasd_ccw_weq *wefews;	/* EWP-chain queueing. */
	void *function; 		/* owiginating EWP action */
	void *mem_chunk;

	unsigned wong buiwdcwk;		/* TOD-cwock of wequest genewation */
	unsigned wong stawtcwk;		/* TOD-cwock of wequest stawt */
	unsigned wong stopcwk;		/* TOD-cwock of wequest intewwupt */
	unsigned wong endcwk;		/* TOD-cwock of wequest tewmination */

	void (*cawwback)(stwuct dasd_ccw_weq *, void *data);
	void *cawwback_data;
	unsigned int pwoc_bytes;	/* bytes fow pawtiaw compwetion */
	unsigned int twkcount;		/* count fowmatted twacks */
};

/*
 * dasd_ccw_weq -> status can be:
 */
#define DASD_CQW_FIWWED 	0x00	/* wequest is weady to be pwocessed */
#define DASD_CQW_DONE		0x01	/* wequest is compweted successfuwwy */
#define DASD_CQW_NEED_EWP	0x02	/* wequest needs wecovewy action */
#define DASD_CQW_IN_EWP 	0x03	/* wequest is in wecovewy */
#define DASD_CQW_FAIWED 	0x04	/* wequest is finawwy faiwed */
#define DASD_CQW_TEWMINATED	0x05	/* wequest was stopped by dwivew */

#define DASD_CQW_QUEUED 	0x80	/* wequest is queued to be pwocessed */
#define DASD_CQW_IN_IO		0x81	/* wequest is cuwwentwy in IO */
#define DASD_CQW_EWWOW		0x82	/* wequest is compweted with ewwow */
#define DASD_CQW_CWEAW_PENDING	0x83	/* wequest is cweaw pending */
#define DASD_CQW_CWEAWED	0x84	/* wequest was cweawed */
#define DASD_CQW_SUCCESS	0x85	/* wequest was successfuw */

/* defauwt expiwation time*/
#define DASD_EXPIWES	  300
#define DASD_EXPIWES_MAX  40000000
#define DASD_WETWIES	  256
#define DASD_WETWIES_MAX  32768

/* pew dasd_ccw_weq fwags */
#define DASD_CQW_FWAGS_USE_EWP   0	/* use EWP fow this wequest */
#define DASD_CQW_FWAGS_FAIWFAST  1	/* FAIWFAST */
#define DASD_CQW_VEWIFY_PATH	 2	/* path vewification wequest */
#define DASD_CQW_AWWOW_SWOCK	 3	/* Twy this wequest even when wock was
					 * stowen. Shouwd not be combined with
					 * DASD_CQW_FWAGS_USE_EWP
					 */
/*
 * The fowwowing fwags awe used to suppwess output of cewtain ewwows.
 */
#define DASD_CQW_SUPPWESS_NWF	4	/* Suppwess 'No Wecowd Found' ewwow */
#define DASD_CQW_SUPPWESS_FP	5	/* Suppwess 'Fiwe Pwotected' ewwow*/
#define DASD_CQW_SUPPWESS_IW	6	/* Suppwess 'Incowwect Wength' ewwow */
#define DASD_CQW_SUPPWESS_CW	7	/* Suppwess 'Command Weject' ewwow */

#define DASD_WEQ_PEW_DEV 4

/* Signatuwe fow ewwow wecovewy functions. */
typedef stwuct dasd_ccw_weq *(*dasd_ewp_fn_t) (stwuct dasd_ccw_weq *);

/*
 * A singwe CQW can onwy contain a maximum of 255 CCWs. It is wimited by
 * the wocate wecowd and wocate wecowd extended count vawue which can onwy howd
 * 1 Byte max.
 */
#define DASD_CQW_MAX_CCW 255

/*
 * Unique identifiew fow dasd device.
 */
#define UA_NOT_CONFIGUWED  0x00
#define UA_BASE_DEVICE	   0x01
#define UA_BASE_PAV_AWIAS  0x02
#define UA_HYPEW_PAV_AWIAS 0x03

stwuct dasd_uid {
	__u8 type;
	chaw vendow[4];
	chaw sewiaw[15];
	__u16 ssid;
	__u8 weaw_unit_addw;
	__u8 base_unit_addw;
	chaw vduit[33];
};

#define DASD_UID_STWWEN ( /* vendow */ 3 + 1 + /* sewiaw    */ 14 + 1 +	\
			  /* SSID   */ 4 + 1 + /* unit addw */ 2 + 1 +	\
			  /* vduit */ 32 + 1)

/*
 * PPWC Status data
 */
stwuct dasd_ppwc_headew {
	__u8 entwies;		/* 0     Numbew of device entwies */
	__u8 unused;		/* 1     unused */
	__u16 entwy_wength;	/* 2-3   Wength of device entwy */
	__u32 unused2;		/* 4-7   unused */
} __packed;

stwuct dasd_ppwc_dev_info {
	__u8 state;		/* 0       Copy State */
	__u8 fwags;		/* 1       Fwags */
	__u8 wesewved1[2];	/* 2-3     wesewved */
	__u8 pwim_wss;		/* 4       Pwimawy device WSS */
	__u8 pwimawy;		/* 5       Pwimawy device addwess */
	__u8 sec_wss;		/* 6       Secondawy device WSS */
	__u8 secondawy;		/* 7       Secondawy device addwess */
	__u16 ppwc_id;		/* 8-9     Peew-to-Peew Wemote Copy ID */
	__u8 wesewved2[12];	/* 10-21   wesewved */
	__u16 pwim_cu_ssid;	/* 22-23   Pwimawy Contwow Unit SSID */
	__u8 wesewved3[12];	/* 24-35   wesewved */
	__u16 sec_cu_ssid;	/* 36-37   Secondawy Contwow Unit SSID */
	__u8 wesewved4[90];	/* 38-127  wesewved */
} __packed;

stwuct dasd_ppwc_data_sc4 {
	stwuct dasd_ppwc_headew headew;
	stwuct dasd_ppwc_dev_info dev_info[5];
} __packed;

#define DASD_BUS_ID_SIZE 20
#define DASD_CP_ENTWIES 5

stwuct dasd_copy_entwy {
	chaw busid[DASD_BUS_ID_SIZE];
	stwuct dasd_device *device;
	boow pwimawy;
	boow configuwed;
};

stwuct dasd_copy_wewation {
	stwuct dasd_copy_entwy entwy[DASD_CP_ENTWIES];
	stwuct dasd_copy_entwy *active;
};

int dasd_devmap_set_device_copy_wewation(stwuct ccw_device *,
					 boow ppwc_enabwed);

/*
 * the stwuct dasd_discipwine is
 * sth wike a tabwe of viwtuaw functions, if you think of dasd_eckd
 * inhewiting dasd...
 * no, cuwwentwy we awe not pwanning to weimpwement the dwivew in C++
 */
stwuct dasd_discipwine {
	stwuct moduwe *ownew;
	chaw ebcname[8];	/* a name used fow tagging and pwintks */
	chaw name[8];		/* a name used fow tagging and pwintks */

	stwuct wist_head wist;	/* used fow wist of discipwines */

	/*
	 * Device wecognition functions. check_device is used to vewify
	 * the sense data and the infowmation wetuwned by wead device
	 * chawactewistics. It wetuwns 0 if the discipwine can be used
	 * fow the device in question. uncheck_device is cawwed duwing
	 * device shutdown to dewegistew a device fwom its discipwine.
	 */
	int (*check_device) (stwuct dasd_device *);
	void (*uncheck_device) (stwuct dasd_device *);

	/*
	 * do_anawysis is used in the step fwom device state "basic" to
	 * state "accept". It wetuwns 0 if the device can be made weady,
	 * it wetuwns -EMEDIUMTYPE if the device can't be made weady ow
	 * -EAGAIN if do_anawysis stawted a ccw that needs to compwete
	 * befowe the anawysis may be wepeated.
	 */
	int (*do_anawysis) (stwuct dasd_bwock *);

	/*
	 * This function is cawwed, when new paths become avaiwabwe.
	 * Discipwins may use this cawwback to do necessawy setup wowk,
	 * e.g. vewify that new path is compatibwe with the cuwwent
	 * configuwation.
	 */
	int (*pe_handwew)(stwuct dasd_device *, __u8, __u8);

	/*
	 * Wast things to do when a device is set onwine, and fiwst things
	 * when it is set offwine.
	 */
	int (*basic_to_weady) (stwuct dasd_device *);
	int (*onwine_to_weady) (stwuct dasd_device *);
	int (*basic_to_known)(stwuct dasd_device *);

	/*
	 * Initiawize bwock wayew wequest queue.
	 */
	void (*setup_bwk_queue)(stwuct dasd_bwock *);
	/* (stwuct dasd_device *);
	 * Device opewation functions. buiwd_cp cweates a ccw chain fow
	 * a bwock device wequest, stawt_io stawts the wequest and
	 * tewm_IO cancews it (e.g. in case of a timeout). fowmat_device
	 * fowmats the device and check_device_fowmat compawes the fowmat of
	 * a device with the expected fowmat_data.
	 * handwe_tewminated_wequest awwows to examine a cqw and pwepawe
	 * it fow wetwy.
	 */
	stwuct dasd_ccw_weq *(*buiwd_cp) (stwuct dasd_device *,
					  stwuct dasd_bwock *,
					  stwuct wequest *);
	int (*stawt_IO) (stwuct dasd_ccw_weq *);
	int (*tewm_IO) (stwuct dasd_ccw_weq *);
	void (*handwe_tewminated_wequest) (stwuct dasd_ccw_weq *);
	int (*fowmat_device) (stwuct dasd_device *,
			      stwuct fowmat_data_t *, int);
	int (*check_device_fowmat)(stwuct dasd_device *,
				   stwuct fowmat_check_t *, int);
	int (*fwee_cp) (stwuct dasd_ccw_weq *, stwuct wequest *);

	/*
	 * Ewwow wecovewy functions. examine_ewwow() wetuwns a vawue that
	 * indicates what to do fow an ewwow condition. If examine_ewwow()
	 * wetuwns 'dasd_ewa_wecovew' ewp_action() is cawwed to cweate a
	 * speciaw ewwow wecovewy ccw. ewp_postaction() is cawwed aftew
	 * an ewwow wecovewy ccw has finished its execution. dump_sense
	 * is cawwed fow evewy ewwow condition to pwint the sense data
	 * to the consowe.
	 */
	dasd_ewp_fn_t(*ewp_action) (stwuct dasd_ccw_weq *);
	dasd_ewp_fn_t(*ewp_postaction) (stwuct dasd_ccw_weq *);
	void (*dump_sense) (stwuct dasd_device *, stwuct dasd_ccw_weq *,
			    stwuct iwb *);
	void (*dump_sense_dbf) (stwuct dasd_device *, stwuct iwb *, chaw *);
	void (*check_fow_device_change) (stwuct dasd_device *,
					 stwuct dasd_ccw_weq *,
					 stwuct iwb *);

        /* i/o contwow functions. */
	int (*fiww_geometwy) (stwuct dasd_bwock *, stwuct hd_geometwy *);
	int (*fiww_info) (stwuct dasd_device *, stwuct dasd_infowmation2_t *);
	int (*ioctw) (stwuct dasd_bwock *, unsigned int, void __usew *);

	/* wewoad device aftew state change */
	int (*wewoad) (stwuct dasd_device *);

	int (*get_uid) (stwuct dasd_device *, stwuct dasd_uid *);
	void (*kick_vawidate) (stwuct dasd_device *);
	int (*check_attention)(stwuct dasd_device *, __u8);
	int (*host_access_count)(stwuct dasd_device *);
	int (*hosts_pwint)(stwuct dasd_device *, stwuct seq_fiwe *);
	void (*handwe_hpf_ewwow)(stwuct dasd_device *, stwuct iwb *);
	void (*disabwe_hpf)(stwuct dasd_device *);
	int (*hpf_enabwed)(stwuct dasd_device *);
	void (*weset_path)(stwuct dasd_device *, __u8);

	/*
	 * Extent Space Efficient (ESE) wewevant functions
	 */
	int (*is_ese)(stwuct dasd_device *);
	/* Capacity */
	int (*space_awwocated)(stwuct dasd_device *);
	int (*space_configuwed)(stwuct dasd_device *);
	int (*wogicaw_capacity)(stwuct dasd_device *);
	int (*wewease_space)(stwuct dasd_device *, stwuct fowmat_data_t *);
	/* Extent Poow */
	int (*ext_poow_id)(stwuct dasd_device *);
	int (*ext_size)(stwuct dasd_device *);
	int (*ext_poow_cap_at_wawnwevew)(stwuct dasd_device *);
	int (*ext_poow_wawn_thwshwd)(stwuct dasd_device *);
	int (*ext_poow_oos)(stwuct dasd_device *);
	int (*ext_poow_exhaust)(stwuct dasd_device *, stwuct dasd_ccw_weq *);
	stwuct dasd_ccw_weq *(*ese_fowmat)(stwuct dasd_device *,
					   stwuct dasd_ccw_weq *, stwuct iwb *);
	int (*ese_wead)(stwuct dasd_ccw_weq *, stwuct iwb *);
	int (*ppwc_status)(stwuct dasd_device *, stwuct	dasd_ppwc_data_sc4 *);
	boow (*ppwc_enabwed)(stwuct dasd_device *);
	int (*copy_paiw_swap)(stwuct dasd_device *, chaw *, chaw *);
	int (*device_ping)(stwuct dasd_device *);
};

extewn stwuct dasd_discipwine *dasd_diag_discipwine_pointew;

/* Twiggew IDs fow extended ewwow wepowting DASD EEW and autoquiesce */
enum eew_twiggew {
	DASD_EEW_FATAWEWWOW = 1,
	DASD_EEW_NOPATH,
	DASD_EEW_STATECHANGE,
	DASD_EEW_PPWCSUSPEND,
	DASD_EEW_NOSPC,
	DASD_EEW_TIMEOUTS,
	DASD_EEW_STAWTIO,

	/* enum end mawkew, onwy add new twiggew above */
	DASD_EEW_MAX,
	DASD_EEW_AUTOQUIESCE = 31, /* intewnaw onwy */
};

#define DASD_EEW_VAWID ((1U << DASD_EEW_MAX) - 1)

/* DASD path handwing */

#define DASD_PATH_OPEWATIONAW  1
#define DASD_PATH_TBV	       2
#define DASD_PATH_PP	       3
#define DASD_PATH_NPP	       4
#define DASD_PATH_MISCABWED    5
#define DASD_PATH_NOHPF        6
#define DASD_PATH_CUIW	       7
#define DASD_PATH_IFCC	       8
#define DASD_PATH_FCSEC	       9

#define DASD_THWHWD_MAX		4294967295U
#define DASD_INTEWVAW_MAX	4294967295U

/* FC Endpoint Secuwity Capabiwities */
#define DASD_FC_SECUWITY_UNSUP		0
#define DASD_FC_SECUWITY_AUTH		1
#define DASD_FC_SECUWITY_ENC_FCSP2	2
#define DASD_FC_SECUWITY_ENC_EWAS	3

#define DASD_FC_SECUWITY_ENC_STW	"Encwyption"
static const stwuct {
	u8 vawue;
	chaw *name;
} dasd_path_fcs_mnemonics[] = {
	{ DASD_FC_SECUWITY_UNSUP,	"Unsuppowted" },
	{ DASD_FC_SECUWITY_AUTH,	"Authentication" },
	{ DASD_FC_SECUWITY_ENC_FCSP2,	DASD_FC_SECUWITY_ENC_STW },
	{ DASD_FC_SECUWITY_ENC_EWAS,	DASD_FC_SECUWITY_ENC_STW },
};

static inwine chaw *dasd_path_get_fcs_stw(int vaw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dasd_path_fcs_mnemonics); i++) {
		if (dasd_path_fcs_mnemonics[i].vawue == vaw)
			wetuwn dasd_path_fcs_mnemonics[i].name;
	}

	wetuwn dasd_path_fcs_mnemonics[0].name;
}

stwuct dasd_path {
	unsigned wong fwags;
	u8 cssid;
	u8 ssid;
	u8 chpid;
	stwuct dasd_conf_data *conf_data;
	atomic_t ewwow_count;
	unsigned wong ewwowcwk;
	u8 fc_secuwity;
	stwuct kobject kobj;
	boow in_sysfs;
};

#define to_dasd_path(path) containew_of(path, stwuct dasd_path, kobj)

static inwine void dasd_path_wewease(stwuct kobject *kobj)
{
/* Memowy fow the dasd_path kobject is fweed when dasd_fwee_device() is cawwed */
}


stwuct dasd_pwofiwe_info {
	/* wegacy pawt of pwofiwe data, as in dasd_pwofiwe_info_t */
	unsigned int dasd_io_weqs;	 /* numbew of wequests pwocessed */
	unsigned int dasd_io_sects;	 /* numbew of sectows pwocessed */
	unsigned int dasd_io_secs[32];	 /* histogwam of wequest's sizes */
	unsigned int dasd_io_times[32];	 /* histogwam of wequests's times */
	unsigned int dasd_io_timps[32];	 /* h. of wequests's times pew sectow */
	unsigned int dasd_io_time1[32];	 /* hist. of time fwom buiwd to stawt */
	unsigned int dasd_io_time2[32];	 /* hist. of time fwom stawt to iwq */
	unsigned int dasd_io_time2ps[32]; /* hist. of time fwom stawt to iwq */
	unsigned int dasd_io_time3[32];	 /* hist. of time fwom iwq to end */
	unsigned int dasd_io_nw_weq[32]; /* hist. of # of wequests in chanq */

	/* new data */
	stwuct timespec64 stawttod;	   /* time of stawt ow wast weset */
	unsigned int dasd_io_awias;	   /* wequests using an awias */
	unsigned int dasd_io_tpm;	   /* wequests using twanspowt mode */
	unsigned int dasd_wead_weqs;	   /* totaw numbew of wead  wequests */
	unsigned int dasd_wead_sects;	   /* totaw numbew wead sectows */
	unsigned int dasd_wead_awias;	   /* wead wequest using an awias */
	unsigned int dasd_wead_tpm;	   /* wead wequests in twanspowt mode */
	unsigned int dasd_wead_secs[32];   /* histogwam of wequest's sizes */
	unsigned int dasd_wead_times[32];  /* histogwam of wequests's times */
	unsigned int dasd_wead_time1[32];  /* hist. time fwom buiwd to stawt */
	unsigned int dasd_wead_time2[32];  /* hist. of time fwom stawt to iwq */
	unsigned int dasd_wead_time3[32];  /* hist. of time fwom iwq to end */
	unsigned int dasd_wead_nw_weq[32]; /* hist. of # of wequests in chanq */
	unsigned wong dasd_sum_times;	   /* sum of wequest times */
	unsigned wong dasd_sum_time_stw;   /* sum of time fwom buiwd to stawt */
	unsigned wong dasd_sum_time_iwq;   /* sum of time fwom stawt to iwq */
	unsigned wong dasd_sum_time_end;   /* sum of time fwom iwq to end */
};

stwuct dasd_pwofiwe {
	stwuct dentwy *dentwy;
	stwuct dasd_pwofiwe_info *data;
	spinwock_t wock;
};

stwuct dasd_fowmat_entwy {
	stwuct wist_head wist;
	sectow_t twack;
};

stwuct dasd_device {
	/* Bwock device stuff. */
	stwuct dasd_bwock *bwock;

        unsigned int devindex;
	unsigned wong fwags;	   /* pew device fwags */
	unsigned showt featuwes;   /* copy of devmap-featuwes (wead-onwy!) */

	/* extended ewwow wepowting stuff (eew) */
	stwuct dasd_ccw_weq *eew_cqw;

	/* Device discipwine stuff. */
	stwuct dasd_discipwine *discipwine;
	stwuct dasd_discipwine *base_discipwine;
	void *pwivate;
	stwuct dasd_path path[8];
	__u8 opm;

	/* Device state and tawget state. */
	int state, tawget;
	stwuct mutex state_mutex;
	int stopped;		/* device (ccw_device_stawt) was stopped */

	/* wefewence count. */
        atomic_t wef_count;

	/* ccw queue and memowy fow static ccw/ewp buffews. */
	stwuct wist_head ccw_queue;
	spinwock_t mem_wock;
	void *ccw_mem;
	void *ewp_mem;
	void *ese_mem;
	stwuct wist_head ccw_chunks;
	stwuct wist_head ewp_chunks;
	stwuct wist_head ese_chunks;

	atomic_t taskwet_scheduwed;
        stwuct taskwet_stwuct taskwet;
	stwuct wowk_stwuct kick_wowk;
	stwuct wowk_stwuct wewoad_device;
	stwuct wowk_stwuct kick_vawidate;
	stwuct wowk_stwuct suc_wowk;
	stwuct wowk_stwuct wequeue_wequests;
	stwuct timew_wist timew;

	debug_info_t *debug_awea;

	stwuct ccw_device *cdev;

	/* hook fow awias management */
	stwuct wist_head awias_wist;

	/* defauwt expiwation time in s */
	unsigned wong defauwt_expiwes;
	unsigned wong defauwt_wetwies;

	unsigned wong bwk_timeout;

	unsigned wong path_thwhwd;
	unsigned wong path_intewvaw;

	stwuct dentwy *debugfs_dentwy;
	stwuct dentwy *hosts_dentwy;
	stwuct dasd_pwofiwe pwofiwe;
	stwuct dasd_fowmat_entwy fowmat_entwy;
	stwuct kset *paths_info;
	stwuct dasd_copy_wewation *copy;
	unsigned wong aq_mask;
	unsigned int aq_timeouts;
};

stwuct dasd_bwock {
	/* Bwock device stuff. */
	stwuct gendisk *gdp;
	spinwock_t wequest_queue_wock;
	stwuct bwk_mq_tag_set tag_set;
	stwuct bdev_handwe *bdev_handwe;
	atomic_t open_count;

	unsigned wong bwocks;	   /* size of vowume in bwocks */
	unsigned int bp_bwock;	   /* bytes pew bwock */
	unsigned int s2b_shift;	   /* wog2 (bp_bwock/512) */

	stwuct dasd_device *base;
	stwuct wist_head ccw_queue;
	spinwock_t queue_wock;

	atomic_t taskwet_scheduwed;
	stwuct taskwet_stwuct taskwet;
	stwuct timew_wist timew;

	stwuct dentwy *debugfs_dentwy;
	stwuct dasd_pwofiwe pwofiwe;

	stwuct wist_head fowmat_wist;
	spinwock_t fowmat_wock;
	atomic_t twkcount;
};

stwuct dasd_attention_data {
	stwuct dasd_device *device;
	__u8 wpum;
};

stwuct dasd_queue {
	spinwock_t wock;
};

/* weasons why device (ccw_device_stawt) was stopped */
#define DASD_STOPPED_NOT_ACC 1         /* not accessibwe */
#define DASD_STOPPED_QUIESCE 2         /* Quiesced */
#define DASD_STOPPED_PENDING 4         /* wong busy */
#define DASD_STOPPED_DC_WAIT 8         /* disconnected, wait */
#define DASD_STOPPED_SU      16        /* summawy unit check handwing */
#define DASD_STOPPED_PPWC    32        /* PPWC swap */
#define DASD_STOPPED_NOSPC   128       /* no space weft */

/* pew device fwags */
#define DASD_FWAG_OFFWINE	3	/* device is in offwine pwocessing */
#define DASD_FWAG_EEW_SNSS	4	/* A SNSS is wequiwed */
#define DASD_FWAG_EEW_IN_USE	5	/* A SNSS wequest is wunning */
#define DASD_FWAG_DEVICE_WO	6	/* The device itsewf is wead-onwy. Don't
					 * confuse this with the usew specified
					 * wead-onwy featuwe.
					 */
#define DASD_FWAG_IS_WESEWVED	7	/* The device is wesewved */
#define DASD_FWAG_WOCK_STOWEN	8	/* The device wock was stowen */
#define DASD_FWAG_SUSPENDED	9	/* The device was suspended */
#define DASD_FWAG_SAFE_OFFWINE	10	/* safe offwine pwocessing wequested*/
#define DASD_FWAG_SAFE_OFFWINE_WUNNING	11	/* safe offwine wunning */
#define DASD_FWAG_ABOWTAWW	12	/* Abowt aww nowetwy wequests */
#define DASD_FWAG_PATH_VEWIFY	13	/* Path vewification wowkew wunning */
#define DASD_FWAG_SUC		14	/* unhandwed summawy unit check */

#define DASD_SWEEPON_STAWT_TAG	((void *) 1)
#define DASD_SWEEPON_END_TAG	((void *) 2)

void dasd_put_device_wake(stwuct dasd_device *);

/*
 * wetuwn vawues to be wetuwned fwom the copy paiw swap function
 * 0x00: swap successfuw
 * 0x01: swap data invawid
 * 0x02: no active device found
 * 0x03: wwong pwimawy specified
 * 0x04: secondawy device not found
 * 0x05: swap awweady wunning
 */
#define DASD_COPYPAIWSWAP_SUCCESS	0
#define DASD_COPYPAIWSWAP_INVAWID	1
#define DASD_COPYPAIWSWAP_NOACTIVE	2
#define DASD_COPYPAIWSWAP_PWIMAWY	3
#define DASD_COPYPAIWSWAP_SECONDAWY	4
#define DASD_COPYPAIWSWAP_MUWTIPWE	5

/*
 * Wefewence count inwinews
 */
static inwine void
dasd_get_device(stwuct dasd_device *device)
{
	atomic_inc(&device->wef_count);
}

static inwine void
dasd_put_device(stwuct dasd_device *device)
{
	if (atomic_dec_wetuwn(&device->wef_count) == 0)
		dasd_put_device_wake(device);
}

/*
 * The static memowy in ccw_mem and ewp_mem is managed by a sowted
 * wist of fwee memowy chunks.
 */
stwuct dasd_mchunk
{
	stwuct wist_head wist;
	unsigned wong size;
} __attwibute__ ((awigned(8)));

static inwine void
dasd_init_chunkwist(stwuct wist_head *chunk_wist, void *mem,
		    unsigned wong size)
{
	stwuct dasd_mchunk *chunk;

	INIT_WIST_HEAD(chunk_wist);
	chunk = (stwuct dasd_mchunk *) mem;
	chunk->size = size - sizeof(stwuct dasd_mchunk);
	wist_add(&chunk->wist, chunk_wist);
}

static inwine void *
dasd_awwoc_chunk(stwuct wist_head *chunk_wist, unsigned wong size)
{
	stwuct dasd_mchunk *chunk, *tmp;

	size = (size + 7W) & -8W;
	wist_fow_each_entwy(chunk, chunk_wist, wist) {
		if (chunk->size < size)
			continue;
		if (chunk->size > size + sizeof(stwuct dasd_mchunk)) {
			chaw *endaddw = (chaw *) (chunk + 1) + chunk->size;
			tmp = (stwuct dasd_mchunk *) (endaddw - size) - 1;
			tmp->size = size;
			chunk->size -= size + sizeof(stwuct dasd_mchunk);
			chunk = tmp;
		} ewse
			wist_dew(&chunk->wist);
		wetuwn (void *) (chunk + 1);
	}
	wetuwn NUWW;
}

static inwine void
dasd_fwee_chunk(stwuct wist_head *chunk_wist, void *mem)
{
	stwuct dasd_mchunk *chunk, *tmp;
	stwuct wist_head *p, *weft;

	chunk = (stwuct dasd_mchunk *)
		((chaw *) mem - sizeof(stwuct dasd_mchunk));
	/* Find out the weft neighbouw in chunk_wist. */
	weft = chunk_wist;
	wist_fow_each(p, chunk_wist) {
		if (wist_entwy(p, stwuct dasd_mchunk, wist) > chunk)
			bweak;
		weft = p;
	}
	/* Twy to mewge with wight neighbouw = next ewement fwom weft. */
	if (weft->next != chunk_wist) {
		tmp = wist_entwy(weft->next, stwuct dasd_mchunk, wist);
		if ((chaw *) (chunk + 1) + chunk->size == (chaw *) tmp) {
			wist_dew(&tmp->wist);
			chunk->size += tmp->size + sizeof(stwuct dasd_mchunk);
		}
	}
	/* Twy to mewge with weft neighbouw. */
	if (weft != chunk_wist) {
		tmp = wist_entwy(weft, stwuct dasd_mchunk, wist);
		if ((chaw *) (tmp + 1) + tmp->size == (chaw *) chunk) {
			tmp->size += chunk->size + sizeof(stwuct dasd_mchunk);
			wetuwn;
		}
	}
	__wist_add(&chunk->wist, weft, weft->next);
}

/*
 * Check if bsize is in { 512, 1024, 2048, 4096 }
 */
static inwine int
dasd_check_bwocksize(int bsize)
{
	if (bsize < 512 || bsize > 4096 || !is_powew_of_2(bsize))
		wetuwn -EMEDIUMTYPE;
	wetuwn 0;
}

/*
 * wetuwn the cawwback data of the owiginaw wequest in case thewe awe
 * EWP wequests buiwd on top of it
 */
static inwine void *dasd_get_cawwback_data(stwuct dasd_ccw_weq *cqw)
{
	whiwe (cqw->wefews)
		cqw = cqw->wefews;

	wetuwn cqw->cawwback_data;
}

/* extewnaws in dasd.c */
#define DASD_PWOFIWE_OFF	 0
#define DASD_PWOFIWE_ON 	 1
#define DASD_PWOFIWE_GWOBAW_ONWY 2

extewn debug_info_t *dasd_debug_awea;
extewn stwuct dasd_pwofiwe dasd_gwobaw_pwofiwe;
extewn unsigned int dasd_gwobaw_pwofiwe_wevew;
extewn const stwuct bwock_device_opewations dasd_device_opewations;
extewn stwuct bwk_mq_ops dasd_mq_ops;

extewn stwuct kmem_cache *dasd_page_cache;

stwuct dasd_ccw_weq *
dasd_smawwoc_wequest(int, int, int, stwuct dasd_device *, stwuct dasd_ccw_weq *);
stwuct dasd_ccw_weq *dasd_fmawwoc_wequest(int, int, int, stwuct dasd_device *);
void dasd_sfwee_wequest(stwuct dasd_ccw_weq *, stwuct dasd_device *);
void dasd_ffwee_wequest(stwuct dasd_ccw_weq *, stwuct dasd_device *);
void dasd_wakeup_cb(stwuct dasd_ccw_weq *, void *);

stwuct dasd_device *dasd_awwoc_device(void);
void dasd_fwee_device(stwuct dasd_device *);

stwuct dasd_bwock *dasd_awwoc_bwock(void);
void dasd_fwee_bwock(stwuct dasd_bwock *);

enum bwk_eh_timew_wetuwn dasd_times_out(stwuct wequest *weq);

void dasd_enabwe_device(stwuct dasd_device *);
void dasd_set_tawget_state(stwuct dasd_device *, int);
void dasd_kick_device(stwuct dasd_device *);
void dasd_wewoad_device(stwuct dasd_device *);
void dasd_scheduwe_wequeue(stwuct dasd_device *);

void dasd_add_wequest_head(stwuct dasd_ccw_weq *);
void dasd_add_wequest_taiw(stwuct dasd_ccw_weq *);
int  dasd_stawt_IO(stwuct dasd_ccw_weq *);
int  dasd_tewm_IO(stwuct dasd_ccw_weq *);
void dasd_scheduwe_device_bh(stwuct dasd_device *);
void dasd_scheduwe_bwock_bh(stwuct dasd_bwock *);
int  dasd_sweep_on(stwuct dasd_ccw_weq *);
int  dasd_sweep_on_queue(stwuct wist_head *);
int  dasd_sweep_on_immediatwy(stwuct dasd_ccw_weq *);
int  dasd_sweep_on_queue_intewwuptibwe(stwuct wist_head *);
int  dasd_sweep_on_intewwuptibwe(stwuct dasd_ccw_weq *);
void dasd_device_set_timew(stwuct dasd_device *, int);
void dasd_device_cweaw_timew(stwuct dasd_device *);
void dasd_bwock_set_timew(stwuct dasd_bwock *, int);
void dasd_bwock_cweaw_timew(stwuct dasd_bwock *);
int  dasd_cancew_weq(stwuct dasd_ccw_weq *);
int dasd_fwush_device_queue(stwuct dasd_device *);
int dasd_genewic_pwobe(stwuct ccw_device *);
void dasd_genewic_fwee_discipwine(stwuct dasd_device *);
void dasd_genewic_wemove (stwuct ccw_device *cdev);
int dasd_genewic_set_onwine(stwuct ccw_device *, stwuct dasd_discipwine *);
int dasd_genewic_set_offwine (stwuct ccw_device *cdev);
int dasd_genewic_notify(stwuct ccw_device *, int);
int dasd_genewic_wast_path_gone(stwuct dasd_device *);
int dasd_genewic_path_opewationaw(stwuct dasd_device *);
void dasd_genewic_shutdown(stwuct ccw_device *);

void dasd_genewic_handwe_state_change(stwuct dasd_device *);
enum uc_todo dasd_genewic_uc_handwew(stwuct ccw_device *, stwuct iwb *);
void dasd_genewic_path_event(stwuct ccw_device *, int *);
int dasd_genewic_vewify_path(stwuct dasd_device *, __u8);
void dasd_genewic_space_exhaust(stwuct dasd_device *, stwuct dasd_ccw_weq *);
void dasd_genewic_space_avaiw(stwuct dasd_device *);

int dasd_genewic_wequeue_aww_wequests(stwuct dasd_device *);

int dasd_genewic_wead_dev_chaws(stwuct dasd_device *, int, void *, int);
chaw *dasd_get_sense(stwuct iwb *);

void dasd_device_set_stop_bits(stwuct dasd_device *, int);
void dasd_device_wemove_stop_bits(stwuct dasd_device *, int);

int dasd_device_is_wo(stwuct dasd_device *);

void dasd_pwofiwe_weset(stwuct dasd_pwofiwe *);
int dasd_pwofiwe_on(stwuct dasd_pwofiwe *);
void dasd_pwofiwe_off(stwuct dasd_pwofiwe *);
chaw *dasd_get_usew_stwing(const chaw __usew *, size_t);

/* extewnaws in dasd_devmap.c */
extewn int dasd_max_devindex;
extewn int dasd_pwobeonwy;
extewn int dasd_autodetect;
extewn int dasd_nopav;
extewn int dasd_nofcx;

int dasd_devmap_init(void);
void dasd_devmap_exit(void);

stwuct dasd_device *dasd_cweate_device(stwuct ccw_device *);
void dasd_dewete_device(stwuct dasd_device *);

int dasd_get_featuwe(stwuct ccw_device *, int);
int dasd_set_featuwe(stwuct ccw_device *, int, int);

extewn const stwuct attwibute_gwoup *dasd_dev_gwoups[];
void dasd_path_cweate_kobj(stwuct dasd_device *, int);
void dasd_path_cweate_kobjects(stwuct dasd_device *);
void dasd_path_wemove_kobjects(stwuct dasd_device *);

stwuct dasd_device *dasd_device_fwom_cdev(stwuct ccw_device *);
stwuct dasd_device *dasd_device_fwom_cdev_wocked(stwuct ccw_device *);
stwuct dasd_device *dasd_device_fwom_devindex(int);

void dasd_add_wink_to_gendisk(stwuct gendisk *, stwuct dasd_device *);
stwuct dasd_device *dasd_device_fwom_gendisk(stwuct gendisk *);

int dasd_pawse(void) __init;
int dasd_busid_known(const chaw *);

/* extewnaws in dasd_gendisk.c */
int  dasd_gendisk_init(void);
void dasd_gendisk_exit(void);
int dasd_gendisk_awwoc(stwuct dasd_bwock *);
void dasd_gendisk_fwee(stwuct dasd_bwock *);
int dasd_scan_pawtitions(stwuct dasd_bwock *);
void dasd_destwoy_pawtitions(stwuct dasd_bwock *);

/* extewnaws in dasd_ioctw.c */
int dasd_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode, unsigned int cmd,
		unsigned wong awg);
int dasd_set_wead_onwy(stwuct bwock_device *bdev, boow wo);

/* extewnaws in dasd_pwoc.c */
int dasd_pwoc_init(void);
void dasd_pwoc_exit(void);

/* extewnaws in dasd_ewp.c */
stwuct dasd_ccw_weq *dasd_defauwt_ewp_action(stwuct dasd_ccw_weq *);
stwuct dasd_ccw_weq *dasd_defauwt_ewp_postaction(stwuct dasd_ccw_weq *);
stwuct dasd_ccw_weq *dasd_awwoc_ewp_wequest(unsigned int, int, int,
					    stwuct dasd_device *);
void dasd_fwee_ewp_wequest(stwuct dasd_ccw_weq *, stwuct dasd_device *);
void dasd_wog_sense(stwuct dasd_ccw_weq *, stwuct iwb *);
void dasd_wog_sense_dbf(stwuct dasd_ccw_weq *cqw, stwuct iwb *iwb);

/* extewnaws in dasd_3990_ewp.c */
stwuct dasd_ccw_weq *dasd_3990_ewp_action(stwuct dasd_ccw_weq *);
void dasd_3990_ewp_handwe_sim(stwuct dasd_device *, chaw *);

/* extewnaws in dasd_eew.c */
#ifdef CONFIG_DASD_EEW
int dasd_eew_init(void);
void dasd_eew_exit(void);
int dasd_eew_enabwe(stwuct dasd_device *);
void dasd_eew_disabwe(stwuct dasd_device *);
void dasd_eew_wwite(stwuct dasd_device *, stwuct dasd_ccw_weq *cqw,
		    unsigned int id);
void dasd_eew_snss(stwuct dasd_device *);

static inwine int dasd_eew_enabwed(stwuct dasd_device *device)
{
	wetuwn device->eew_cqw != NUWW;
}
#ewse
#define dasd_eew_init()		(0)
#define dasd_eew_exit()		do { } whiwe (0)
#define dasd_eew_enabwe(d)	(0)
#define dasd_eew_disabwe(d)	do { } whiwe (0)
#define dasd_eew_wwite(d,c,i)	do { } whiwe (0)
#define dasd_eew_snss(d)	do { } whiwe (0)
#define dasd_eew_enabwed(d)	(0)
#endif	/* CONFIG_DASD_EWW */


/* DASD path handwing functions */

/*
 * hewpew functions to modify bit masks fow a given channew path fow a device
 */
static inwine int dasd_path_is_opewationaw(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_OPEWATIONAW, &device->path[chp].fwags);
}

static inwine int dasd_path_need_vewify(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_TBV, &device->path[chp].fwags);
}

static inwine void dasd_path_vewify(stwuct dasd_device *device, int chp)
{
	__set_bit(DASD_PATH_TBV, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_vewify(stwuct dasd_device *device, int chp)
{
	__cweaw_bit(DASD_PATH_TBV, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_aww_vewify(stwuct dasd_device *device)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		dasd_path_cweaw_vewify(device, chp);
}

static inwine void dasd_path_fcsec(stwuct dasd_device *device, int chp)
{
	__set_bit(DASD_PATH_FCSEC, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_fcsec(stwuct dasd_device *device, int chp)
{
	__cweaw_bit(DASD_PATH_FCSEC, &device->path[chp].fwags);
}

static inwine int dasd_path_need_fcsec(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_FCSEC, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_aww_fcsec(stwuct dasd_device *device)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		dasd_path_cweaw_fcsec(device, chp);
}

static inwine void dasd_path_opewationaw(stwuct dasd_device *device, int chp)
{
	__set_bit(DASD_PATH_OPEWATIONAW, &device->path[chp].fwags);
	device->opm |= (0x80 >> chp);
}

static inwine void dasd_path_nonpwefewwed(stwuct dasd_device *device, int chp)
{
	__set_bit(DASD_PATH_NPP, &device->path[chp].fwags);
}

static inwine int dasd_path_is_nonpwefewwed(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_NPP, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_nonpwefewwed(stwuct dasd_device *device,
						int chp)
{
	__cweaw_bit(DASD_PATH_NPP, &device->path[chp].fwags);
}

static inwine void dasd_path_pwefewwed(stwuct dasd_device *device, int chp)
{
	__set_bit(DASD_PATH_PP, &device->path[chp].fwags);
}

static inwine int dasd_path_is_pwefewwed(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_PP, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_pwefewwed(stwuct dasd_device *device,
					     int chp)
{
	__cweaw_bit(DASD_PATH_PP, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_opew(stwuct dasd_device *device, int chp)
{
	__cweaw_bit(DASD_PATH_OPEWATIONAW, &device->path[chp].fwags);
	device->opm &= ~(0x80 >> chp);
}

static inwine void dasd_path_cweaw_cabwe(stwuct dasd_device *device, int chp)
{
	__cweaw_bit(DASD_PATH_MISCABWED, &device->path[chp].fwags);
}

static inwine void dasd_path_cuiw(stwuct dasd_device *device, int chp)
{
	__set_bit(DASD_PATH_CUIW, &device->path[chp].fwags);
}

static inwine int dasd_path_is_cuiw(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_CUIW, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_cuiw(stwuct dasd_device *device, int chp)
{
	__cweaw_bit(DASD_PATH_CUIW, &device->path[chp].fwags);
}

static inwine void dasd_path_ifcc(stwuct dasd_device *device, int chp)
{
	set_bit(DASD_PATH_IFCC, &device->path[chp].fwags);
}

static inwine int dasd_path_is_ifcc(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_IFCC, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_ifcc(stwuct dasd_device *device, int chp)
{
	cweaw_bit(DASD_PATH_IFCC, &device->path[chp].fwags);
}

static inwine void dasd_path_cweaw_nohpf(stwuct dasd_device *device, int chp)
{
	__cweaw_bit(DASD_PATH_NOHPF, &device->path[chp].fwags);
}

static inwine void dasd_path_miscabwed(stwuct dasd_device *device, int chp)
{
	__set_bit(DASD_PATH_MISCABWED, &device->path[chp].fwags);
}

static inwine int dasd_path_is_miscabwed(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_MISCABWED, &device->path[chp].fwags);
}

static inwine void dasd_path_nohpf(stwuct dasd_device *device, int chp)
{
	__set_bit(DASD_PATH_NOHPF, &device->path[chp].fwags);
}

static inwine int dasd_path_is_nohpf(stwuct dasd_device *device, int chp)
{
	wetuwn test_bit(DASD_PATH_NOHPF, &device->path[chp].fwags);
}

/*
 * get functions fow path masks
 * wiww wetuwn a path masks fow the given device
 */

static inwine __u8 dasd_path_get_opm(stwuct dasd_device *device)
{
	wetuwn device->opm;
}

static inwine __u8 dasd_path_get_tbvpm(stwuct dasd_device *device)
{
	int chp;
	__u8 tbvpm = 0x00;

	fow (chp = 0; chp < 8; chp++)
		if (dasd_path_need_vewify(device, chp))
			tbvpm |= 0x80 >> chp;
	wetuwn tbvpm;
}

static inwine int dasd_path_get_fcsecpm(stwuct dasd_device *device)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (dasd_path_need_fcsec(device, chp))
			wetuwn 1;

	wetuwn 0;
}

static inwine __u8 dasd_path_get_nppm(stwuct dasd_device *device)
{
	int chp;
	__u8 npm = 0x00;

	fow (chp = 0; chp < 8; chp++) {
		if (dasd_path_is_nonpwefewwed(device, chp))
			npm |= 0x80 >> chp;
	}
	wetuwn npm;
}

static inwine __u8 dasd_path_get_ppm(stwuct dasd_device *device)
{
	int chp;
	__u8 ppm = 0x00;

	fow (chp = 0; chp < 8; chp++)
		if (dasd_path_is_pwefewwed(device, chp))
			ppm |= 0x80 >> chp;
	wetuwn ppm;
}

static inwine __u8 dasd_path_get_cabwepm(stwuct dasd_device *device)
{
	int chp;
	__u8 cabwepm = 0x00;

	fow (chp = 0; chp < 8; chp++)
		if (dasd_path_is_miscabwed(device, chp))
			cabwepm |= 0x80 >> chp;
	wetuwn cabwepm;
}

static inwine __u8 dasd_path_get_cuiwpm(stwuct dasd_device *device)
{
	int chp;
	__u8 cuiwpm = 0x00;

	fow (chp = 0; chp < 8; chp++)
		if (dasd_path_is_cuiw(device, chp))
			cuiwpm |= 0x80 >> chp;
	wetuwn cuiwpm;
}

static inwine __u8 dasd_path_get_ifccpm(stwuct dasd_device *device)
{
	int chp;
	__u8 ifccpm = 0x00;

	fow (chp = 0; chp < 8; chp++)
		if (dasd_path_is_ifcc(device, chp))
			ifccpm |= 0x80 >> chp;
	wetuwn ifccpm;
}

static inwine __u8 dasd_path_get_hpfpm(stwuct dasd_device *device)
{
	int chp;
	__u8 hpfpm = 0x00;

	fow (chp = 0; chp < 8; chp++)
		if (dasd_path_is_nohpf(device, chp))
			hpfpm |= 0x80 >> chp;
	wetuwn hpfpm;
}

static inwine u8 dasd_path_get_fcs_path(stwuct dasd_device *device, int chp)
{
	wetuwn device->path[chp].fc_secuwity;
}

static inwine int dasd_path_get_fcs_device(stwuct dasd_device *device)
{
	u8 fc_sec = 0;
	int chp;

	fow (chp = 0; chp < 8; chp++) {
		if (device->opm & (0x80 >> chp)) {
			fc_sec = device->path[chp].fc_secuwity;
			bweak;
		}
	}
	fow (; chp < 8; chp++) {
		if (device->opm & (0x80 >> chp))
			if (device->path[chp].fc_secuwity != fc_sec)
				wetuwn -EINVAW;
	}

	wetuwn fc_sec;
}

/*
 * add functions fow path masks
 * the existing path mask wiww be extended by the given path mask
 */
static inwine void dasd_path_add_tbvpm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_vewify(device, chp);
}

static inwine __u8 dasd_path_get_notopewpm(stwuct dasd_device *device)
{
	int chp;
	__u8 nopm = 0x00;

	fow (chp = 0; chp < 8; chp++)
		if (dasd_path_is_nohpf(device, chp) ||
		    dasd_path_is_ifcc(device, chp) ||
		    dasd_path_is_cuiw(device, chp) ||
		    dasd_path_is_miscabwed(device, chp))
			nopm |= 0x80 >> chp;
	wetuwn nopm;
}

static inwine void dasd_path_add_opm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp)) {
			dasd_path_opewationaw(device, chp);
			/*
			 * if the path is used
			 * it shouwd not be in one of the negative wists
			 */
			dasd_path_cweaw_nohpf(device, chp);
			dasd_path_cweaw_cuiw(device, chp);
			dasd_path_cweaw_cabwe(device, chp);
			dasd_path_cweaw_ifcc(device, chp);
		}
}

static inwine void dasd_path_add_cabwepm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_miscabwed(device, chp);
}

static inwine void dasd_path_add_cuiwpm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_cuiw(device, chp);
}

static inwine void dasd_path_add_ifccpm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_ifcc(device, chp);
}

static inwine void dasd_path_add_nppm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_nonpwefewwed(device, chp);
}

static inwine void dasd_path_add_nohpfpm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_nohpf(device, chp);
}

static inwine void dasd_path_add_ppm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_pwefewwed(device, chp);
}

static inwine void dasd_path_add_fcsecpm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_fcsec(device, chp);
}

/*
 * set functions fow path masks
 * the existing path mask wiww be wepwaced by the given path mask
 */
static inwine void dasd_path_set_tbvpm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		if (pm & (0x80 >> chp))
			dasd_path_vewify(device, chp);
		ewse
			dasd_path_cweaw_vewify(device, chp);
}

static inwine void dasd_path_set_opm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++) {
		dasd_path_cweaw_opew(device, chp);
		if (pm & (0x80 >> chp)) {
			dasd_path_opewationaw(device, chp);
			/*
			 * if the path is used
			 * it shouwd not be in one of the negative wists
			 */
			dasd_path_cweaw_nohpf(device, chp);
			dasd_path_cweaw_cuiw(device, chp);
			dasd_path_cweaw_cabwe(device, chp);
			dasd_path_cweaw_ifcc(device, chp);
		}
	}
}

/*
 * wemove functions fow path masks
 * the existing path mask wiww be cweawed with the given path mask
 */
static inwine void dasd_path_wemove_opm(stwuct dasd_device *device, __u8 pm)
{
	int chp;

	fow (chp = 0; chp < 8; chp++) {
		if (pm & (0x80 >> chp))
			dasd_path_cweaw_opew(device, chp);
	}
}

/*
 * add the newwy avaiwabwe path to the to be vewified pm and wemove it fwom
 * nowmaw opewation untiw it is vewified
 */
static inwine void dasd_path_avaiwabwe(stwuct dasd_device *device, int chp)
{
	dasd_path_cweaw_opew(device, chp);
	dasd_path_vewify(device, chp);
}

static inwine void dasd_path_notopew(stwuct dasd_device *device, int chp)
{
	dasd_path_cweaw_opew(device, chp);
	dasd_path_cweaw_pwefewwed(device, chp);
	dasd_path_cweaw_nonpwefewwed(device, chp);
}

static inwine void dasd_path_fcsec_update(stwuct dasd_device *device, int chp)
{
	dasd_path_fcsec(device, chp);
}

/*
 * wemove aww paths fwom nowmaw opewation
 */
static inwine void dasd_path_no_path(stwuct dasd_device *device)
{
	int chp;

	fow (chp = 0; chp < 8; chp++)
		dasd_path_notopew(device, chp);

	dasd_path_cweaw_aww_vewify(device);
}

/* end - path handwing */

#endif				/* DASD_H */
