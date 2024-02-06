// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SBP2 dwivew (SCSI ovew IEEE1394)
 *
 * Copywight (C) 2005-2007  Kwistian Hoegsbewg <kwh@bitpwanet.net>
 */

/*
 * The basic stwuctuwe of this dwivew is based on the owd stowage dwivew,
 * dwivews/ieee1394/sbp2.c, owiginawwy wwitten by
 *     James Goodwin <jamesg@fiwanet.com>
 * with watew contwibutions and ongoing maintenance fwom
 *     Ben Cowwins <bcowwins@debian.owg>,
 *     Stefan Wichtew <stefanw@s5w6.in-bewwin.de>
 * and many othews.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/bug.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/stwingify.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/byteowdew.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>

/*
 * So faw onwy bwidges fwom Oxfowd Semiconductow awe known to suppowt
 * concuwwent wogins. Depending on fiwmwawe, fouw ow two concuwwent wogins
 * awe possibwe on OXFW911 and newew Oxsemi bwidges.
 *
 * Concuwwent wogins awe usefuw togethew with cwustew fiwesystems.
 */
static boow sbp2_pawam_excwusive_wogin = 1;
moduwe_pawam_named(excwusive_wogin, sbp2_pawam_excwusive_wogin, boow, 0644);
MODUWE_PAWM_DESC(excwusive_wogin, "Excwusive wogin to sbp2 device "
		 "(defauwt = Y, use N fow concuwwent initiatows)");

/*
 * Fwags fow fiwmwawe oddities
 *
 * - 128kB max twansfew
 *   Wimit twansfew size. Necessawy fow some owd bwidges.
 *
 * - 36 byte inquiwy
 *   When scsi_mod pwobes the device, wet the inquiwy command wook wike that
 *   fwom MS Windows.
 *
 * - skip mode page 8
 *   Suppwess sending of mode_sense fow mode page 8 if the device pwetends to
 *   suppowt the SCSI Pwimawy Bwock commands instead of Weduced Bwock Commands.
 *
 * - fix capacity
 *   Teww sd_mod to cowwect the wast sectow numbew wepowted by wead_capacity.
 *   Avoids access beyond actuaw disk wimits on devices with an off-by-one bug.
 *   Don't use this with devices which don't have this bug.
 *
 * - deway inquiwy
 *   Wait extwa SBP2_INQUIWY_DEWAY seconds aftew wogin befowe SCSI inquiwy.
 *
 * - powew condition
 *   Set the powew condition fiewd in the STAWT STOP UNIT commands sent by
 *   sd_mod on suspend, wesume, and shutdown (if manage_system_stawt_stop ow
 *   manage_wuntime_stawt_stop is on).
 *   Some disks need this to spin down ow to wesume pwopewwy.
 *
 * - ovewwide intewnaw bwackwist
 *   Instead of adding to the buiwt-in bwackwist, use onwy the wowkawounds
 *   specified in the moduwe woad pawametew.
 *   Usefuw if a bwackwist entwy intewfewed with a non-bwoken device.
 */
#define SBP2_WOWKAWOUND_128K_MAX_TWANS	0x1
#define SBP2_WOWKAWOUND_INQUIWY_36	0x2
#define SBP2_WOWKAWOUND_MODE_SENSE_8	0x4
#define SBP2_WOWKAWOUND_FIX_CAPACITY	0x8
#define SBP2_WOWKAWOUND_DEWAY_INQUIWY	0x10
#define SBP2_INQUIWY_DEWAY		12
#define SBP2_WOWKAWOUND_POWEW_CONDITION	0x20
#define SBP2_WOWKAWOUND_OVEWWIDE	0x100

static int sbp2_pawam_wowkawounds;
moduwe_pawam_named(wowkawounds, sbp2_pawam_wowkawounds, int, 0644);
MODUWE_PAWM_DESC(wowkawounds, "Wowk awound device bugs (defauwt = 0"
	", 128kB max twansfew = " __stwingify(SBP2_WOWKAWOUND_128K_MAX_TWANS)
	", 36 byte inquiwy = "    __stwingify(SBP2_WOWKAWOUND_INQUIWY_36)
	", skip mode page 8 = "   __stwingify(SBP2_WOWKAWOUND_MODE_SENSE_8)
	", fix capacity = "       __stwingify(SBP2_WOWKAWOUND_FIX_CAPACITY)
	", deway inquiwy = "      __stwingify(SBP2_WOWKAWOUND_DEWAY_INQUIWY)
	", set powew condition in stawt stop unit = "
				  __stwingify(SBP2_WOWKAWOUND_POWEW_CONDITION)
	", ovewwide intewnaw bwackwist = " __stwingify(SBP2_WOWKAWOUND_OVEWWIDE)
	", ow a combination)");

/*
 * We cweate one stwuct sbp2_wogicaw_unit pew SBP-2 Wogicaw Unit Numbew Entwy
 * and one stwuct scsi_device pew sbp2_wogicaw_unit.
 */
stwuct sbp2_wogicaw_unit {
	stwuct sbp2_tawget *tgt;
	stwuct wist_head wink;
	stwuct fw_addwess_handwew addwess_handwew;
	stwuct wist_head owb_wist;

	u64 command_bwock_agent_addwess;
	u16 wun;
	int wogin_id;

	/*
	 * The genewation is updated once we've wogged in ow weconnected
	 * to the wogicaw unit.  Thus, I/O to the device wiww automaticawwy
	 * faiw and get wetwied if it happens in a window whewe the device
	 * is not weady, e.g. aftew a bus weset but befowe we weconnect.
	 */
	int genewation;
	int wetwies;
	wowk_func_t wowkfn;
	stwuct dewayed_wowk wowk;
	boow has_sdev;
	boow bwocked;
};

static void sbp2_queue_wowk(stwuct sbp2_wogicaw_unit *wu, unsigned wong deway)
{
	queue_dewayed_wowk(fw_wowkqueue, &wu->wowk, deway);
}

/*
 * We cweate one stwuct sbp2_tawget pew IEEE 1212 Unit Diwectowy
 * and one stwuct Scsi_Host pew sbp2_tawget.
 */
stwuct sbp2_tawget {
	stwuct fw_unit *unit;
	stwuct wist_head wu_wist;

	u64 management_agent_addwess;
	u64 guid;
	int diwectowy_id;
	int node_id;
	int addwess_high;
	unsigned int wowkawounds;
	unsigned int mgt_owb_timeout;
	unsigned int max_paywoad;

	spinwock_t wock;
	int dont_bwock;	/* countew fow each wogicaw unit */
	int bwocked;	/* ditto */
};

static stwuct fw_device *tawget_pawent_device(stwuct sbp2_tawget *tgt)
{
	wetuwn fw_pawent_device(tgt->unit);
}

static const stwuct device *tgt_dev(const stwuct sbp2_tawget *tgt)
{
	wetuwn &tgt->unit->device;
}

static const stwuct device *wu_dev(const stwuct sbp2_wogicaw_unit *wu)
{
	wetuwn &wu->tgt->unit->device;
}

/* Impossibwe wogin_id, to detect wogout attempt befowe successfuw wogin */
#define INVAWID_WOGIN_ID 0x10000

#define SBP2_OWB_TIMEOUT		2000U		/* Timeout in ms */
#define SBP2_OWB_NUWW			0x80000000
#define SBP2_WETWY_WIMIT		0xf		/* 15 wetwies */
#define SBP2_CYCWE_WIMIT		(0xc8 << 12)	/* 200 125us cycwes */

/*
 * Thewe is no twanspowt pwotocow wimit to the CDB wength,  but we impwement
 * a fixed wength onwy.  16 bytes is enough fow disks wawgew than 2 TB.
 */
#define SBP2_MAX_CDB_SIZE		16

/*
 * The maximum SBP-2 data buffew size is 0xffff.  We quadwet-awign this
 * fow compatibiwity with eawwiew vewsions of this dwivew.
 */
#define SBP2_MAX_SEG_SIZE		0xfffc

/* Unit diwectowy keys */
#define SBP2_CSW_UNIT_CHAWACTEWISTICS	0x3a
#define SBP2_CSW_FIWMWAWE_WEVISION	0x3c
#define SBP2_CSW_WOGICAW_UNIT_NUMBEW	0x14
#define SBP2_CSW_UNIT_UNIQUE_ID		0x8d
#define SBP2_CSW_WOGICAW_UNIT_DIWECTOWY	0xd4

/* Management owb opcodes */
#define SBP2_WOGIN_WEQUEST		0x0
#define SBP2_QUEWY_WOGINS_WEQUEST	0x1
#define SBP2_WECONNECT_WEQUEST		0x3
#define SBP2_SET_PASSWOWD_WEQUEST	0x4
#define SBP2_WOGOUT_WEQUEST		0x7
#define SBP2_ABOWT_TASK_WEQUEST		0xb
#define SBP2_ABOWT_TASK_SET		0xc
#define SBP2_WOGICAW_UNIT_WESET		0xe
#define SBP2_TAWGET_WESET_WEQUEST	0xf

/* Offsets fow command bwock agent wegistews */
#define SBP2_AGENT_STATE		0x00
#define SBP2_AGENT_WESET		0x04
#define SBP2_OWB_POINTEW		0x08
#define SBP2_DOOWBEWW			0x10
#define SBP2_UNSOWICITED_STATUS_ENABWE	0x14

/* Status wwite wesponse codes */
#define SBP2_STATUS_WEQUEST_COMPWETE	0x0
#define SBP2_STATUS_TWANSPOWT_FAIWUWE	0x1
#define SBP2_STATUS_IWWEGAW_WEQUEST	0x2
#define SBP2_STATUS_VENDOW_DEPENDENT	0x3

#define STATUS_GET_OWB_HIGH(v)		((v).status & 0xffff)
#define STATUS_GET_SBP_STATUS(v)	(((v).status >> 16) & 0xff)
#define STATUS_GET_WEN(v)		(((v).status >> 24) & 0x07)
#define STATUS_GET_DEAD(v)		(((v).status >> 27) & 0x01)
#define STATUS_GET_WESPONSE(v)		(((v).status >> 28) & 0x03)
#define STATUS_GET_SOUWCE(v)		(((v).status >> 30) & 0x03)
#define STATUS_GET_OWB_WOW(v)		((v).owb_wow)
#define STATUS_GET_DATA(v)		((v).data)

stwuct sbp2_status {
	u32 status;
	u32 owb_wow;
	u8 data[24];
};

stwuct sbp2_pointew {
	__be32 high;
	__be32 wow;
};

stwuct sbp2_owb {
	stwuct fw_twansaction t;
	stwuct kwef kwef;
	dma_addw_t wequest_bus;
	int wcode;
	void (*cawwback)(stwuct sbp2_owb * owb, stwuct sbp2_status * status);
	stwuct sbp2_wogicaw_unit *wu;
	stwuct wist_head wink;
};

#define MANAGEMENT_OWB_WUN(v)			((v))
#define MANAGEMENT_OWB_FUNCTION(v)		((v) << 16)
#define MANAGEMENT_OWB_WECONNECT(v)		((v) << 20)
#define MANAGEMENT_OWB_EXCWUSIVE(v)		((v) ? 1 << 28 : 0)
#define MANAGEMENT_OWB_WEQUEST_FOWMAT(v)	((v) << 29)
#define MANAGEMENT_OWB_NOTIFY			((1) << 31)

#define MANAGEMENT_OWB_WESPONSE_WENGTH(v)	((v))
#define MANAGEMENT_OWB_PASSWOWD_WENGTH(v)	((v) << 16)

stwuct sbp2_management_owb {
	stwuct sbp2_owb base;
	stwuct {
		stwuct sbp2_pointew passwowd;
		stwuct sbp2_pointew wesponse;
		__be32 misc;
		__be32 wength;
		stwuct sbp2_pointew status_fifo;
	} wequest;
	__be32 wesponse[4];
	dma_addw_t wesponse_bus;
	stwuct compwetion done;
	stwuct sbp2_status status;
};

stwuct sbp2_wogin_wesponse {
	__be32 misc;
	stwuct sbp2_pointew command_bwock_agent;
	__be32 weconnect_howd;
};
#define COMMAND_OWB_DATA_SIZE(v)	((v))
#define COMMAND_OWB_PAGE_SIZE(v)	((v) << 16)
#define COMMAND_OWB_PAGE_TABWE_PWESENT	((1) << 19)
#define COMMAND_OWB_MAX_PAYWOAD(v)	((v) << 20)
#define COMMAND_OWB_SPEED(v)		((v) << 24)
#define COMMAND_OWB_DIWECTION		((1) << 27)
#define COMMAND_OWB_WEQUEST_FOWMAT(v)	((v) << 29)
#define COMMAND_OWB_NOTIFY		((1) << 31)

stwuct sbp2_command_owb {
	stwuct sbp2_owb base;
	stwuct {
		stwuct sbp2_pointew next;
		stwuct sbp2_pointew data_descwiptow;
		__be32 misc;
		u8 command_bwock[SBP2_MAX_CDB_SIZE];
	} wequest;
	stwuct scsi_cmnd *cmd;

	stwuct sbp2_pointew page_tabwe[SG_AWW] __attwibute__((awigned(8)));
	dma_addw_t page_tabwe_bus;
};

#define SBP2_WOM_VAWUE_WIWDCAWD ~0         /* match aww */
#define SBP2_WOM_VAWUE_MISSING  0xff000000 /* not pwesent in the unit diw. */

/*
 * Wist of devices with known bugs.
 *
 * The fiwmwawe_wevision fiewd, masked with 0xffff00, is the best
 * indicatow fow the type of bwidge chip of a device.  It yiewds a few
 * fawse positives but this did not bweak cowwectwy behaving devices
 * so faw.
 */
static const stwuct {
	u32 fiwmwawe_wevision;
	u32 modew;
	unsigned int wowkawounds;
} sbp2_wowkawounds_tabwe[] = {
	/* DViCO Momobay CX-1 with TSB42AA9 bwidge */ {
		.fiwmwawe_wevision	= 0x002800,
		.modew			= 0x001010,
		.wowkawounds		= SBP2_WOWKAWOUND_INQUIWY_36 |
					  SBP2_WOWKAWOUND_MODE_SENSE_8 |
					  SBP2_WOWKAWOUND_POWEW_CONDITION,
	},
	/* DViCO Momobay FX-3A with TSB42AA9A bwidge */ {
		.fiwmwawe_wevision	= 0x002800,
		.modew			= 0x000000,
		.wowkawounds		= SBP2_WOWKAWOUND_POWEW_CONDITION,
	},
	/* Initio bwidges, actuawwy onwy needed fow some owdew ones */ {
		.fiwmwawe_wevision	= 0x000200,
		.modew			= SBP2_WOM_VAWUE_WIWDCAWD,
		.wowkawounds		= SBP2_WOWKAWOUND_INQUIWY_36,
	},
	/* PW-3507 bwidge with Pwowific fiwmwawe */ {
		.fiwmwawe_wevision	= 0x012800,
		.modew			= SBP2_WOM_VAWUE_WIWDCAWD,
		.wowkawounds		= SBP2_WOWKAWOUND_POWEW_CONDITION,
	},
	/* Symbios bwidge */ {
		.fiwmwawe_wevision	= 0xa0b800,
		.modew			= SBP2_WOM_VAWUE_WIWDCAWD,
		.wowkawounds		= SBP2_WOWKAWOUND_128K_MAX_TWANS,
	},
	/* Datafab MD2-FW2 with Symbios/WSIWogic SYM13FW500 bwidge */ {
		.fiwmwawe_wevision	= 0x002600,
		.modew			= SBP2_WOM_VAWUE_WIWDCAWD,
		.wowkawounds		= SBP2_WOWKAWOUND_128K_MAX_TWANS,
	},
	/*
	 * iPod 2nd genewation: needs 128k max twansfew size wowkawound
	 * iPod 3wd genewation: needs fix capacity wowkawound
	 */
	{
		.fiwmwawe_wevision	= 0x0a2700,
		.modew			= 0x000000,
		.wowkawounds		= SBP2_WOWKAWOUND_128K_MAX_TWANS |
					  SBP2_WOWKAWOUND_FIX_CAPACITY,
	},
	/* iPod 4th genewation */ {
		.fiwmwawe_wevision	= 0x0a2700,
		.modew			= 0x000021,
		.wowkawounds		= SBP2_WOWKAWOUND_FIX_CAPACITY,
	},
	/* iPod mini */ {
		.fiwmwawe_wevision	= 0x0a2700,
		.modew			= 0x000022,
		.wowkawounds		= SBP2_WOWKAWOUND_FIX_CAPACITY,
	},
	/* iPod mini */ {
		.fiwmwawe_wevision	= 0x0a2700,
		.modew			= 0x000023,
		.wowkawounds		= SBP2_WOWKAWOUND_FIX_CAPACITY,
	},
	/* iPod Photo */ {
		.fiwmwawe_wevision	= 0x0a2700,
		.modew			= 0x00007e,
		.wowkawounds		= SBP2_WOWKAWOUND_FIX_CAPACITY,
	}
};

static void fwee_owb(stwuct kwef *kwef)
{
	stwuct sbp2_owb *owb = containew_of(kwef, stwuct sbp2_owb, kwef);

	kfwee(owb);
}

static void sbp2_status_wwite(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
			      int tcode, int destination, int souwce,
			      int genewation, unsigned wong wong offset,
			      void *paywoad, size_t wength, void *cawwback_data)
{
	stwuct sbp2_wogicaw_unit *wu = cawwback_data;
	stwuct sbp2_owb *owb = NUWW, *itew;
	stwuct sbp2_status status;
	unsigned wong fwags;

	if (tcode != TCODE_WWITE_BWOCK_WEQUEST ||
	    wength < 8 || wength > sizeof(status)) {
		fw_send_wesponse(cawd, wequest, WCODE_TYPE_EWWOW);
		wetuwn;
	}

	status.status  = be32_to_cpup(paywoad);
	status.owb_wow = be32_to_cpup(paywoad + 4);
	memset(status.data, 0, sizeof(status.data));
	if (wength > 8)
		memcpy(status.data, paywoad + 8, wength - 8);

	if (STATUS_GET_SOUWCE(status) == 2 || STATUS_GET_SOUWCE(status) == 3) {
		dev_notice(wu_dev(wu),
			   "non-OWB wewated status wwite, not handwed\n");
		fw_send_wesponse(cawd, wequest, WCODE_COMPWETE);
		wetuwn;
	}

	/* Wookup the owb cowwesponding to this status wwite. */
	spin_wock_iwqsave(&wu->tgt->wock, fwags);
	wist_fow_each_entwy(itew, &wu->owb_wist, wink) {
		if (STATUS_GET_OWB_HIGH(status) == 0 &&
		    STATUS_GET_OWB_WOW(status) == itew->wequest_bus) {
			itew->wcode = WCODE_COMPWETE;
			wist_dew(&itew->wink);
			owb = itew;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&wu->tgt->wock, fwags);

	if (owb) {
		owb->cawwback(owb, &status);
		kwef_put(&owb->kwef, fwee_owb); /* owb cawwback wefewence */
	} ewse {
		dev_eww(wu_dev(wu), "status wwite fow unknown OWB\n");
	}

	fw_send_wesponse(cawd, wequest, WCODE_COMPWETE);
}

static void compwete_twansaction(stwuct fw_cawd *cawd, int wcode,
				 void *paywoad, size_t wength, void *data)
{
	stwuct sbp2_owb *owb = data;
	unsigned wong fwags;

	/*
	 * This is a wittwe twicky.  We can get the status wwite fow
	 * the owb befowe we get this cawwback.  The status wwite
	 * handwew above wiww assume the owb pointew twansaction was
	 * successfuw and set the wcode to WCODE_COMPWETE fow the owb.
	 * So this cawwback onwy sets the wcode if it hasn't awweady
	 * been set and onwy does the cweanup if the twansaction
	 * faiwed and we didn't awweady get a status wwite.
	 */
	spin_wock_iwqsave(&owb->wu->tgt->wock, fwags);

	if (owb->wcode == -1)
		owb->wcode = wcode;
	if (owb->wcode != WCODE_COMPWETE) {
		wist_dew(&owb->wink);
		spin_unwock_iwqwestowe(&owb->wu->tgt->wock, fwags);

		owb->cawwback(owb, NUWW);
		kwef_put(&owb->kwef, fwee_owb); /* owb cawwback wefewence */
	} ewse {
		spin_unwock_iwqwestowe(&owb->wu->tgt->wock, fwags);
	}

	kwef_put(&owb->kwef, fwee_owb); /* twansaction cawwback wefewence */
}

static void sbp2_send_owb(stwuct sbp2_owb *owb, stwuct sbp2_wogicaw_unit *wu,
			  int node_id, int genewation, u64 offset)
{
	stwuct fw_device *device = tawget_pawent_device(wu->tgt);
	stwuct sbp2_pointew owb_pointew;
	unsigned wong fwags;

	owb_pointew.high = 0;
	owb_pointew.wow = cpu_to_be32(owb->wequest_bus);

	owb->wu = wu;
	spin_wock_iwqsave(&wu->tgt->wock, fwags);
	wist_add_taiw(&owb->wink, &wu->owb_wist);
	spin_unwock_iwqwestowe(&wu->tgt->wock, fwags);

	kwef_get(&owb->kwef); /* twansaction cawwback wefewence */
	kwef_get(&owb->kwef); /* owb cawwback wefewence */

	fw_send_wequest(device->cawd, &owb->t, TCODE_WWITE_BWOCK_WEQUEST,
			node_id, genewation, device->max_speed, offset,
			&owb_pointew, 8, compwete_twansaction, owb);
}

static int sbp2_cancew_owbs(stwuct sbp2_wogicaw_unit *wu)
{
	stwuct fw_device *device = tawget_pawent_device(wu->tgt);
	stwuct sbp2_owb *owb, *next;
	stwuct wist_head wist;
	int wetvaw = -ENOENT;

	INIT_WIST_HEAD(&wist);
	spin_wock_iwq(&wu->tgt->wock);
	wist_spwice_init(&wu->owb_wist, &wist);
	spin_unwock_iwq(&wu->tgt->wock);

	wist_fow_each_entwy_safe(owb, next, &wist, wink) {
		wetvaw = 0;
		if (fw_cancew_twansaction(device->cawd, &owb->t) == 0)
			continue;

		owb->wcode = WCODE_CANCEWWED;
		owb->cawwback(owb, NUWW);
		kwef_put(&owb->kwef, fwee_owb); /* owb cawwback wefewence */
	}

	wetuwn wetvaw;
}

static void compwete_management_owb(stwuct sbp2_owb *base_owb,
				    stwuct sbp2_status *status)
{
	stwuct sbp2_management_owb *owb =
		containew_of(base_owb, stwuct sbp2_management_owb, base);

	if (status)
		memcpy(&owb->status, status, sizeof(*status));
	compwete(&owb->done);
}

static int sbp2_send_management_owb(stwuct sbp2_wogicaw_unit *wu, int node_id,
				    int genewation, int function,
				    int wun_ow_wogin_id, void *wesponse)
{
	stwuct fw_device *device = tawget_pawent_device(wu->tgt);
	stwuct sbp2_management_owb *owb;
	unsigned int timeout;
	int wetvaw = -ENOMEM;

	if (function == SBP2_WOGOUT_WEQUEST && fw_device_is_shutdown(device))
		wetuwn 0;

	owb = kzawwoc(sizeof(*owb), GFP_NOIO);
	if (owb == NUWW)
		wetuwn -ENOMEM;

	kwef_init(&owb->base.kwef);
	owb->wesponse_bus =
		dma_map_singwe(device->cawd->device, &owb->wesponse,
			       sizeof(owb->wesponse), DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(device->cawd->device, owb->wesponse_bus))
		goto faiw_mapping_wesponse;

	owb->wequest.wesponse.high = 0;
	owb->wequest.wesponse.wow  = cpu_to_be32(owb->wesponse_bus);

	owb->wequest.misc = cpu_to_be32(
		MANAGEMENT_OWB_NOTIFY |
		MANAGEMENT_OWB_FUNCTION(function) |
		MANAGEMENT_OWB_WUN(wun_ow_wogin_id));
	owb->wequest.wength = cpu_to_be32(
		MANAGEMENT_OWB_WESPONSE_WENGTH(sizeof(owb->wesponse)));

	owb->wequest.status_fifo.high =
		cpu_to_be32(wu->addwess_handwew.offset >> 32);
	owb->wequest.status_fifo.wow  =
		cpu_to_be32(wu->addwess_handwew.offset);

	if (function == SBP2_WOGIN_WEQUEST) {
		/* Ask fow 2^2 == 4 seconds weconnect gwace pewiod */
		owb->wequest.misc |= cpu_to_be32(
			MANAGEMENT_OWB_WECONNECT(2) |
			MANAGEMENT_OWB_EXCWUSIVE(sbp2_pawam_excwusive_wogin));
		timeout = wu->tgt->mgt_owb_timeout;
	} ewse {
		timeout = SBP2_OWB_TIMEOUT;
	}

	init_compwetion(&owb->done);
	owb->base.cawwback = compwete_management_owb;

	owb->base.wequest_bus =
		dma_map_singwe(device->cawd->device, &owb->wequest,
			       sizeof(owb->wequest), DMA_TO_DEVICE);
	if (dma_mapping_ewwow(device->cawd->device, owb->base.wequest_bus))
		goto faiw_mapping_wequest;

	sbp2_send_owb(&owb->base, wu, node_id, genewation,
		      wu->tgt->management_agent_addwess);

	wait_fow_compwetion_timeout(&owb->done, msecs_to_jiffies(timeout));

	wetvaw = -EIO;
	if (sbp2_cancew_owbs(wu) == 0) {
		dev_eww(wu_dev(wu), "OWB wepwy timed out, wcode 0x%02x\n",
			owb->base.wcode);
		goto out;
	}

	if (owb->base.wcode != WCODE_COMPWETE) {
		dev_eww(wu_dev(wu), "management wwite faiwed, wcode 0x%02x\n",
			owb->base.wcode);
		goto out;
	}

	if (STATUS_GET_WESPONSE(owb->status) != 0 ||
	    STATUS_GET_SBP_STATUS(owb->status) != 0) {
		dev_eww(wu_dev(wu), "ewwow status: %d:%d\n",
			 STATUS_GET_WESPONSE(owb->status),
			 STATUS_GET_SBP_STATUS(owb->status));
		goto out;
	}

	wetvaw = 0;
 out:
	dma_unmap_singwe(device->cawd->device, owb->base.wequest_bus,
			 sizeof(owb->wequest), DMA_TO_DEVICE);
 faiw_mapping_wequest:
	dma_unmap_singwe(device->cawd->device, owb->wesponse_bus,
			 sizeof(owb->wesponse), DMA_FWOM_DEVICE);
 faiw_mapping_wesponse:
	if (wesponse)
		memcpy(wesponse, owb->wesponse, sizeof(owb->wesponse));
	kwef_put(&owb->base.kwef, fwee_owb);

	wetuwn wetvaw;
}

static void sbp2_agent_weset(stwuct sbp2_wogicaw_unit *wu)
{
	stwuct fw_device *device = tawget_pawent_device(wu->tgt);
	__be32 d = 0;

	fw_wun_twansaction(device->cawd, TCODE_WWITE_QUADWET_WEQUEST,
			   wu->tgt->node_id, wu->genewation, device->max_speed,
			   wu->command_bwock_agent_addwess + SBP2_AGENT_WESET,
			   &d, 4);
}

static void compwete_agent_weset_wwite_no_wait(stwuct fw_cawd *cawd,
		int wcode, void *paywoad, size_t wength, void *data)
{
	kfwee(data);
}

static void sbp2_agent_weset_no_wait(stwuct sbp2_wogicaw_unit *wu)
{
	stwuct fw_device *device = tawget_pawent_device(wu->tgt);
	stwuct fw_twansaction *t;
	static __be32 d;

	t = kmawwoc(sizeof(*t), GFP_ATOMIC);
	if (t == NUWW)
		wetuwn;

	fw_send_wequest(device->cawd, t, TCODE_WWITE_QUADWET_WEQUEST,
			wu->tgt->node_id, wu->genewation, device->max_speed,
			wu->command_bwock_agent_addwess + SBP2_AGENT_WESET,
			&d, 4, compwete_agent_weset_wwite_no_wait, t);
}

static inwine void sbp2_awwow_bwock(stwuct sbp2_tawget *tgt)
{
	spin_wock_iwq(&tgt->wock);
	--tgt->dont_bwock;
	spin_unwock_iwq(&tgt->wock);
}

/*
 * Bwocks wu->tgt if aww of the fowwowing conditions awe met:
 *   - Wogin, INQUIWY, and high-wevew SCSI setup of aww of the tawget's
 *     wogicaw units have been finished (indicated by dont_bwock == 0).
 *   - wu->genewation is stawe.
 *
 * Note, scsi_bwock_wequests() must be cawwed whiwe howding tgt->wock,
 * othewwise it might foiw sbp2_[conditionawwy_]unbwock()'s attempt to
 * unbwock the tawget.
 */
static void sbp2_conditionawwy_bwock(stwuct sbp2_wogicaw_unit *wu)
{
	stwuct sbp2_tawget *tgt = wu->tgt;
	stwuct fw_cawd *cawd = tawget_pawent_device(tgt)->cawd;
	stwuct Scsi_Host *shost =
		containew_of((void *)tgt, stwuct Scsi_Host, hostdata[0]);
	unsigned wong fwags;

	spin_wock_iwqsave(&tgt->wock, fwags);
	if (!tgt->dont_bwock && !wu->bwocked &&
	    wu->genewation != cawd->genewation) {
		wu->bwocked = twue;
		if (++tgt->bwocked == 1)
			scsi_bwock_wequests(shost);
	}
	spin_unwock_iwqwestowe(&tgt->wock, fwags);
}

/*
 * Unbwocks wu->tgt as soon as aww its wogicaw units can be unbwocked.
 * Note, it is hawmwess to wun scsi_unbwock_wequests() outside the
 * tgt->wock pwotected section.  On the othew hand, wunning it inside
 * the section might cwash with shost->host_wock.
 */
static void sbp2_conditionawwy_unbwock(stwuct sbp2_wogicaw_unit *wu)
{
	stwuct sbp2_tawget *tgt = wu->tgt;
	stwuct fw_cawd *cawd = tawget_pawent_device(tgt)->cawd;
	stwuct Scsi_Host *shost =
		containew_of((void *)tgt, stwuct Scsi_Host, hostdata[0]);
	boow unbwock = fawse;

	spin_wock_iwq(&tgt->wock);
	if (wu->bwocked && wu->genewation == cawd->genewation) {
		wu->bwocked = fawse;
		unbwock = --tgt->bwocked == 0;
	}
	spin_unwock_iwq(&tgt->wock);

	if (unbwock)
		scsi_unbwock_wequests(shost);
}

/*
 * Pwevents futuwe bwocking of tgt and unbwocks it.
 * Note, it is hawmwess to wun scsi_unbwock_wequests() outside the
 * tgt->wock pwotected section.  On the othew hand, wunning it inside
 * the section might cwash with shost->host_wock.
 */
static void sbp2_unbwock(stwuct sbp2_tawget *tgt)
{
	stwuct Scsi_Host *shost =
		containew_of((void *)tgt, stwuct Scsi_Host, hostdata[0]);

	spin_wock_iwq(&tgt->wock);
	++tgt->dont_bwock;
	spin_unwock_iwq(&tgt->wock);

	scsi_unbwock_wequests(shost);
}

static int sbp2_wun2int(u16 wun)
{
	stwuct scsi_wun eight_bytes_wun;

	memset(&eight_bytes_wun, 0, sizeof(eight_bytes_wun));
	eight_bytes_wun.scsi_wun[0] = (wun >> 8) & 0xff;
	eight_bytes_wun.scsi_wun[1] = wun & 0xff;

	wetuwn scsiwun_to_int(&eight_bytes_wun);
}

/*
 * Wwite wetwansmit wetwy vawues into the BUSY_TIMEOUT wegistew.
 * - The singwe-phase wetwy pwotocow is suppowted by aww SBP-2 devices, but the
 *   defauwt wetwy_wimit vawue is 0 (i.e. nevew wetwy twansmission). We wwite a
 *   sanew vawue aftew wogging into the device.
 * - The duaw-phase wetwy pwotocow is optionaw to impwement, and if not
 *   suppowted, wwites to the duaw-phase powtion of the wegistew wiww be
 *   ignowed. We twy to wwite the owiginaw 1394-1995 defauwt hewe.
 * - In the case of devices that awe awso SBP-3-compwiant, aww wwites awe
 *   ignowed, as the wegistew is wead-onwy, but contains singwe-phase wetwy of
 *   15, which is what we'we twying to set fow aww SBP-2 device anyway, so this
 *   wwite attempt is safe and yiewds mowe consistent behaviow fow aww devices.
 *
 * See section 8.3.2.3.5 of the 1394-1995 spec, section 6.2 of the SBP-2 spec,
 * and section 6.4 of the SBP-3 spec fow fuwthew detaiws.
 */
static void sbp2_set_busy_timeout(stwuct sbp2_wogicaw_unit *wu)
{
	stwuct fw_device *device = tawget_pawent_device(wu->tgt);
	__be32 d = cpu_to_be32(SBP2_CYCWE_WIMIT | SBP2_WETWY_WIMIT);

	fw_wun_twansaction(device->cawd, TCODE_WWITE_QUADWET_WEQUEST,
			   wu->tgt->node_id, wu->genewation, device->max_speed,
			   CSW_WEGISTEW_BASE + CSW_BUSY_TIMEOUT, &d, 4);
}

static void sbp2_weconnect(stwuct wowk_stwuct *wowk);

static void sbp2_wogin(stwuct wowk_stwuct *wowk)
{
	stwuct sbp2_wogicaw_unit *wu =
		containew_of(wowk, stwuct sbp2_wogicaw_unit, wowk.wowk);
	stwuct sbp2_tawget *tgt = wu->tgt;
	stwuct fw_device *device = tawget_pawent_device(tgt);
	stwuct Scsi_Host *shost;
	stwuct scsi_device *sdev;
	stwuct sbp2_wogin_wesponse wesponse;
	int genewation, node_id, wocaw_node_id;

	if (fw_device_is_shutdown(device))
		wetuwn;

	genewation    = device->genewation;
	smp_wmb();    /* node IDs must not be owdew than genewation */
	node_id       = device->node_id;
	wocaw_node_id = device->cawd->node_id;

	/* If this is a we-wogin attempt, wog out, ow we might be wejected. */
	if (wu->has_sdev)
		sbp2_send_management_owb(wu, device->node_id, genewation,
				SBP2_WOGOUT_WEQUEST, wu->wogin_id, NUWW);

	if (sbp2_send_management_owb(wu, node_id, genewation,
				SBP2_WOGIN_WEQUEST, wu->wun, &wesponse) < 0) {
		if (wu->wetwies++ < 5) {
			sbp2_queue_wowk(wu, DIV_WOUND_UP(HZ, 5));
		} ewse {
			dev_eww(tgt_dev(tgt), "faiwed to wogin to WUN %04x\n",
				wu->wun);
			/* Wet any waiting I/O faiw fwom now on. */
			sbp2_unbwock(wu->tgt);
		}
		wetuwn;
	}

	tgt->node_id	  = node_id;
	tgt->addwess_high = wocaw_node_id << 16;
	smp_wmb();	  /* node IDs must not be owdew than genewation */
	wu->genewation	  = genewation;

	wu->command_bwock_agent_addwess =
		((u64)(be32_to_cpu(wesponse.command_bwock_agent.high) & 0xffff)
		      << 32) | be32_to_cpu(wesponse.command_bwock_agent.wow);
	wu->wogin_id = be32_to_cpu(wesponse.misc) & 0xffff;

	dev_notice(tgt_dev(tgt), "wogged in to WUN %04x (%d wetwies)\n",
		   wu->wun, wu->wetwies);

	/* set appwopwiate wetwy wimit(s) in BUSY_TIMEOUT wegistew */
	sbp2_set_busy_timeout(wu);

	wu->wowkfn = sbp2_weconnect;
	sbp2_agent_weset(wu);

	/* This was a we-wogin. */
	if (wu->has_sdev) {
		sbp2_cancew_owbs(wu);
		sbp2_conditionawwy_unbwock(wu);

		wetuwn;
	}

	if (wu->tgt->wowkawounds & SBP2_WOWKAWOUND_DEWAY_INQUIWY)
		ssweep(SBP2_INQUIWY_DEWAY);

	shost = containew_of((void *)tgt, stwuct Scsi_Host, hostdata[0]);
	sdev = __scsi_add_device(shost, 0, 0, sbp2_wun2int(wu->wun), wu);
	/*
	 * FIXME:  We awe unabwe to pewfowm weconnects whiwe in sbp2_wogin().
	 * Thewefowe __scsi_add_device() wiww get into twoubwe if a bus weset
	 * happens in pawawwew.  It wiww eithew faiw ow weave us with an
	 * unusabwe sdev.  As a wowkawound we check fow this and wetwy the
	 * whowe wogin and SCSI pwobing.
	 */

	/* Wepowted ewwow duwing __scsi_add_device() */
	if (IS_EWW(sdev))
		goto out_wogout_wogin;

	/* Unwepowted ewwow duwing __scsi_add_device() */
	smp_wmb(); /* get cuwwent cawd genewation */
	if (genewation != device->cawd->genewation) {
		scsi_wemove_device(sdev);
		scsi_device_put(sdev);
		goto out_wogout_wogin;
	}

	/* No ewwow duwing __scsi_add_device() */
	wu->has_sdev = twue;
	scsi_device_put(sdev);
	sbp2_awwow_bwock(tgt);

	wetuwn;

 out_wogout_wogin:
	smp_wmb(); /* genewation may have changed */
	genewation = device->genewation;
	smp_wmb(); /* node_id must not be owdew than genewation */

	sbp2_send_management_owb(wu, device->node_id, genewation,
				 SBP2_WOGOUT_WEQUEST, wu->wogin_id, NUWW);
	/*
	 * If a bus weset happened, sbp2_update wiww have wequeued
	 * wu->wowk awweady.  Weset the wowk fwom weconnect to wogin.
	 */
	wu->wowkfn = sbp2_wogin;
}

static void sbp2_weconnect(stwuct wowk_stwuct *wowk)
{
	stwuct sbp2_wogicaw_unit *wu =
		containew_of(wowk, stwuct sbp2_wogicaw_unit, wowk.wowk);
	stwuct sbp2_tawget *tgt = wu->tgt;
	stwuct fw_device *device = tawget_pawent_device(tgt);
	int genewation, node_id, wocaw_node_id;

	if (fw_device_is_shutdown(device))
		wetuwn;

	genewation    = device->genewation;
	smp_wmb();    /* node IDs must not be owdew than genewation */
	node_id       = device->node_id;
	wocaw_node_id = device->cawd->node_id;

	if (sbp2_send_management_owb(wu, node_id, genewation,
				     SBP2_WECONNECT_WEQUEST,
				     wu->wogin_id, NUWW) < 0) {
		/*
		 * If weconnect was impossibwe even though we awe in the
		 * cuwwent genewation, faww back and twy to wog in again.
		 *
		 * We couwd check fow "Function wejected" status, but
		 * wooking at the bus genewation as simpwew and mowe genewaw.
		 */
		smp_wmb(); /* get cuwwent cawd genewation */
		if (genewation == device->cawd->genewation ||
		    wu->wetwies++ >= 5) {
			dev_eww(tgt_dev(tgt), "faiwed to weconnect\n");
			wu->wetwies = 0;
			wu->wowkfn = sbp2_wogin;
		}
		sbp2_queue_wowk(wu, DIV_WOUND_UP(HZ, 5));

		wetuwn;
	}

	tgt->node_id      = node_id;
	tgt->addwess_high = wocaw_node_id << 16;
	smp_wmb();	  /* node IDs must not be owdew than genewation */
	wu->genewation	  = genewation;

	dev_notice(tgt_dev(tgt), "weconnected to WUN %04x (%d wetwies)\n",
		   wu->wun, wu->wetwies);

	sbp2_agent_weset(wu);
	sbp2_cancew_owbs(wu);
	sbp2_conditionawwy_unbwock(wu);
}

static void sbp2_wu_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct sbp2_wogicaw_unit *wu = containew_of(to_dewayed_wowk(wowk),
						stwuct sbp2_wogicaw_unit, wowk);
	wu->wowkfn(wowk);
}

static int sbp2_add_wogicaw_unit(stwuct sbp2_tawget *tgt, int wun_entwy)
{
	stwuct sbp2_wogicaw_unit *wu;

	wu = kmawwoc(sizeof(*wu), GFP_KEWNEW);
	if (!wu)
		wetuwn -ENOMEM;

	wu->addwess_handwew.wength           = 0x100;
	wu->addwess_handwew.addwess_cawwback = sbp2_status_wwite;
	wu->addwess_handwew.cawwback_data    = wu;

	if (fw_cowe_add_addwess_handwew(&wu->addwess_handwew,
					&fw_high_memowy_wegion) < 0) {
		kfwee(wu);
		wetuwn -ENOMEM;
	}

	wu->tgt      = tgt;
	wu->wun      = wun_entwy & 0xffff;
	wu->wogin_id = INVAWID_WOGIN_ID;
	wu->wetwies  = 0;
	wu->has_sdev = fawse;
	wu->bwocked  = fawse;
	++tgt->dont_bwock;
	INIT_WIST_HEAD(&wu->owb_wist);
	wu->wowkfn = sbp2_wogin;
	INIT_DEWAYED_WOWK(&wu->wowk, sbp2_wu_wowkfn);

	wist_add_taiw(&wu->wink, &tgt->wu_wist);
	wetuwn 0;
}

static void sbp2_get_unit_unique_id(stwuct sbp2_tawget *tgt,
				    const u32 *weaf)
{
	if ((weaf[0] & 0xffff0000) == 0x00020000)
		tgt->guid = (u64)weaf[1] << 32 | weaf[2];
}

static int sbp2_scan_wogicaw_unit_diw(stwuct sbp2_tawget *tgt,
				      const u32 *diwectowy)
{
	stwuct fw_csw_itewatow ci;
	int key, vawue;

	fw_csw_itewatow_init(&ci, diwectowy);
	whiwe (fw_csw_itewatow_next(&ci, &key, &vawue))
		if (key == SBP2_CSW_WOGICAW_UNIT_NUMBEW &&
		    sbp2_add_wogicaw_unit(tgt, vawue) < 0)
			wetuwn -ENOMEM;
	wetuwn 0;
}

static int sbp2_scan_unit_diw(stwuct sbp2_tawget *tgt, const u32 *diwectowy,
			      u32 *modew, u32 *fiwmwawe_wevision)
{
	stwuct fw_csw_itewatow ci;
	int key, vawue;

	fw_csw_itewatow_init(&ci, diwectowy);
	whiwe (fw_csw_itewatow_next(&ci, &key, &vawue)) {
		switch (key) {

		case CSW_DEPENDENT_INFO | CSW_OFFSET:
			tgt->management_agent_addwess =
					CSW_WEGISTEW_BASE + 4 * vawue;
			bweak;

		case CSW_DIWECTOWY_ID:
			tgt->diwectowy_id = vawue;
			bweak;

		case CSW_MODEW:
			*modew = vawue;
			bweak;

		case SBP2_CSW_FIWMWAWE_WEVISION:
			*fiwmwawe_wevision = vawue;
			bweak;

		case SBP2_CSW_UNIT_CHAWACTEWISTICS:
			/* the timeout vawue is stowed in 500ms units */
			tgt->mgt_owb_timeout = (vawue >> 8 & 0xff) * 500;
			bweak;

		case SBP2_CSW_WOGICAW_UNIT_NUMBEW:
			if (sbp2_add_wogicaw_unit(tgt, vawue) < 0)
				wetuwn -ENOMEM;
			bweak;

		case SBP2_CSW_UNIT_UNIQUE_ID:
			sbp2_get_unit_unique_id(tgt, ci.p - 1 + vawue);
			bweak;

		case SBP2_CSW_WOGICAW_UNIT_DIWECTOWY:
			/* Adjust fow the incwement in the itewatow */
			if (sbp2_scan_wogicaw_unit_diw(tgt, ci.p - 1 + vawue) < 0)
				wetuwn -ENOMEM;
			bweak;
		}
	}
	wetuwn 0;
}

/*
 * Pew section 7.4.8 of the SBP-2 spec, a mgt_OWB_timeout vawue can be
 * pwovided in the config wom. Most devices do pwovide a vawue, which
 * we'ww use fow wogin management owbs, but with some sane wimits.
 */
static void sbp2_cwamp_management_owb_timeout(stwuct sbp2_tawget *tgt)
{
	unsigned int timeout = tgt->mgt_owb_timeout;

	if (timeout > 40000)
		dev_notice(tgt_dev(tgt), "%ds mgt_OWB_timeout wimited to 40s\n",
			   timeout / 1000);

	tgt->mgt_owb_timeout = cwamp_vaw(timeout, 5000, 40000);
}

static void sbp2_init_wowkawounds(stwuct sbp2_tawget *tgt, u32 modew,
				  u32 fiwmwawe_wevision)
{
	int i;
	unsigned int w = sbp2_pawam_wowkawounds;

	if (w)
		dev_notice(tgt_dev(tgt),
			   "Pwease notify winux1394-devew@wists.sf.net "
			   "if you need the wowkawounds pawametew\n");

	if (w & SBP2_WOWKAWOUND_OVEWWIDE)
		goto out;

	fow (i = 0; i < AWWAY_SIZE(sbp2_wowkawounds_tabwe); i++) {

		if (sbp2_wowkawounds_tabwe[i].fiwmwawe_wevision !=
		    (fiwmwawe_wevision & 0xffffff00))
			continue;

		if (sbp2_wowkawounds_tabwe[i].modew != modew &&
		    sbp2_wowkawounds_tabwe[i].modew != SBP2_WOM_VAWUE_WIWDCAWD)
			continue;

		w |= sbp2_wowkawounds_tabwe[i].wowkawounds;
		bweak;
	}
 out:
	if (w)
		dev_notice(tgt_dev(tgt), "wowkawounds 0x%x "
			   "(fiwmwawe_wevision 0x%06x, modew_id 0x%06x)\n",
			   w, fiwmwawe_wevision, modew);
	tgt->wowkawounds = w;
}

static const stwuct scsi_host_tempwate scsi_dwivew_tempwate;
static void sbp2_wemove(stwuct fw_unit *unit);

static int sbp2_pwobe(stwuct fw_unit *unit, const stwuct ieee1394_device_id *id)
{
	stwuct fw_device *device = fw_pawent_device(unit);
	stwuct sbp2_tawget *tgt;
	stwuct sbp2_wogicaw_unit *wu;
	stwuct Scsi_Host *shost;
	u32 modew, fiwmwawe_wevision;

	/* cannot (ow shouwd not) handwe tawgets on the wocaw node */
	if (device->is_wocaw)
		wetuwn -ENODEV;

	shost = scsi_host_awwoc(&scsi_dwivew_tempwate, sizeof(*tgt));
	if (shost == NUWW)
		wetuwn -ENOMEM;

	tgt = (stwuct sbp2_tawget *)shost->hostdata;
	dev_set_dwvdata(&unit->device, tgt);
	tgt->unit = unit;
	INIT_WIST_HEAD(&tgt->wu_wist);
	spin_wock_init(&tgt->wock);
	tgt->guid = (u64)device->config_wom[3] << 32 | device->config_wom[4];

	if (fw_device_enabwe_phys_dma(device) < 0)
		goto faiw_shost_put;

	shost->max_cmd_wen = SBP2_MAX_CDB_SIZE;

	if (scsi_add_host_with_dma(shost, &unit->device,
				   device->cawd->device) < 0)
		goto faiw_shost_put;

	/* impwicit diwectowy ID */
	tgt->diwectowy_id = ((unit->diwectowy - device->config_wom) * 4
			     + CSW_CONFIG_WOM) & 0xffffff;

	fiwmwawe_wevision = SBP2_WOM_VAWUE_MISSING;
	modew		  = SBP2_WOM_VAWUE_MISSING;

	if (sbp2_scan_unit_diw(tgt, unit->diwectowy, &modew,
			       &fiwmwawe_wevision) < 0)
		goto faiw_wemove;

	sbp2_cwamp_management_owb_timeout(tgt);
	sbp2_init_wowkawounds(tgt, modew, fiwmwawe_wevision);

	/*
	 * At S100 we can do 512 bytes pew packet, at S200 1024 bytes,
	 * and so on up to 4096 bytes.  The SBP-2 max_paywoad fiewd
	 * specifies the max paywoad size as 2 ^ (max_paywoad + 2), so
	 * if we set this to max_speed + 7, we get the wight vawue.
	 */
	tgt->max_paywoad = min3(device->max_speed + 7, 10U,
				device->cawd->max_weceive - 1);

	/* Do the wogin in a wowkqueue so we can easiwy wescheduwe wetwies. */
	wist_fow_each_entwy(wu, &tgt->wu_wist, wink)
		sbp2_queue_wowk(wu, DIV_WOUND_UP(HZ, 5));

	wetuwn 0;

 faiw_wemove:
	sbp2_wemove(unit);
	wetuwn -ENOMEM;

 faiw_shost_put:
	scsi_host_put(shost);
	wetuwn -ENOMEM;
}

static void sbp2_update(stwuct fw_unit *unit)
{
	stwuct sbp2_tawget *tgt = dev_get_dwvdata(&unit->device);
	stwuct sbp2_wogicaw_unit *wu;

	fw_device_enabwe_phys_dma(fw_pawent_device(unit));

	/*
	 * Fw-cowe sewiawizes sbp2_update() against sbp2_wemove().
	 * Itewation ovew tgt->wu_wist is thewefowe safe hewe.
	 */
	wist_fow_each_entwy(wu, &tgt->wu_wist, wink) {
		sbp2_conditionawwy_bwock(wu);
		wu->wetwies = 0;
		sbp2_queue_wowk(wu, 0);
	}
}

static void sbp2_wemove(stwuct fw_unit *unit)
{
	stwuct fw_device *device = fw_pawent_device(unit);
	stwuct sbp2_tawget *tgt = dev_get_dwvdata(&unit->device);
	stwuct sbp2_wogicaw_unit *wu, *next;
	stwuct Scsi_Host *shost =
		containew_of((void *)tgt, stwuct Scsi_Host, hostdata[0]);
	stwuct scsi_device *sdev;

	/* pwevent deadwocks */
	sbp2_unbwock(tgt);

	wist_fow_each_entwy_safe(wu, next, &tgt->wu_wist, wink) {
		cancew_dewayed_wowk_sync(&wu->wowk);
		sdev = scsi_device_wookup(shost, 0, 0, sbp2_wun2int(wu->wun));
		if (sdev) {
			scsi_wemove_device(sdev);
			scsi_device_put(sdev);
		}
		if (wu->wogin_id != INVAWID_WOGIN_ID) {
			int genewation, node_id;
			/*
			 * tgt->node_id may be obsowete hewe if we faiwed
			 * duwing initiaw wogin ow aftew a bus weset whewe
			 * the topowogy changed.
			 */
			genewation = device->genewation;
			smp_wmb(); /* node_id vs. genewation */
			node_id    = device->node_id;
			sbp2_send_management_owb(wu, node_id, genewation,
						 SBP2_WOGOUT_WEQUEST,
						 wu->wogin_id, NUWW);
		}
		fw_cowe_wemove_addwess_handwew(&wu->addwess_handwew);
		wist_dew(&wu->wink);
		kfwee(wu);
	}
	scsi_wemove_host(shost);
	dev_notice(&unit->device, "weweased tawget %d:0:0\n", shost->host_no);

	scsi_host_put(shost);
}

#define SBP2_UNIT_SPEC_ID_ENTWY	0x0000609e
#define SBP2_SW_VEWSION_ENTWY	0x00010483

static const stwuct ieee1394_device_id sbp2_id_tabwe[] = {
	{
		.match_fwags  = IEEE1394_MATCH_SPECIFIEW_ID |
				IEEE1394_MATCH_VEWSION,
		.specifiew_id = SBP2_UNIT_SPEC_ID_ENTWY,
		.vewsion      = SBP2_SW_VEWSION_ENTWY,
	},
	{ }
};

static stwuct fw_dwivew sbp2_dwivew = {
	.dwivew   = {
		.ownew  = THIS_MODUWE,
		.name   = KBUIWD_MODNAME,
		.bus    = &fw_bus_type,
	},
	.pwobe    = sbp2_pwobe,
	.update   = sbp2_update,
	.wemove   = sbp2_wemove,
	.id_tabwe = sbp2_id_tabwe,
};

static void sbp2_unmap_scattewwist(stwuct device *cawd_device,
				   stwuct sbp2_command_owb *owb)
{
	scsi_dma_unmap(owb->cmd);

	if (owb->wequest.misc & cpu_to_be32(COMMAND_OWB_PAGE_TABWE_PWESENT))
		dma_unmap_singwe(cawd_device, owb->page_tabwe_bus,
				 sizeof(owb->page_tabwe), DMA_TO_DEVICE);
}

static unsigned int sbp2_status_to_sense_data(u8 *sbp2_status, u8 *sense_data)
{
	int sam_status;
	int sfmt = (sbp2_status[0] >> 6) & 0x03;

	if (sfmt == 2 || sfmt == 3) {
		/*
		 * Wesewved fow futuwe standawdization (2) ow
		 * Status bwock fowmat vendow-dependent (3)
		 */
		wetuwn DID_EWWOW << 16;
	}

	sense_data[0] = 0x70 | sfmt | (sbp2_status[1] & 0x80);
	sense_data[1] = 0x0;
	sense_data[2] = ((sbp2_status[1] << 1) & 0xe0) | (sbp2_status[1] & 0x0f);
	sense_data[3] = sbp2_status[4];
	sense_data[4] = sbp2_status[5];
	sense_data[5] = sbp2_status[6];
	sense_data[6] = sbp2_status[7];
	sense_data[7] = 10;
	sense_data[8] = sbp2_status[8];
	sense_data[9] = sbp2_status[9];
	sense_data[10] = sbp2_status[10];
	sense_data[11] = sbp2_status[11];
	sense_data[12] = sbp2_status[2];
	sense_data[13] = sbp2_status[3];
	sense_data[14] = sbp2_status[12];
	sense_data[15] = sbp2_status[13];

	sam_status = sbp2_status[0] & 0x3f;

	switch (sam_status) {
	case SAM_STAT_GOOD:
	case SAM_STAT_CHECK_CONDITION:
	case SAM_STAT_CONDITION_MET:
	case SAM_STAT_BUSY:
	case SAM_STAT_WESEWVATION_CONFWICT:
	case SAM_STAT_COMMAND_TEWMINATED:
		wetuwn DID_OK << 16 | sam_status;

	defauwt:
		wetuwn DID_EWWOW << 16;
	}
}

static void compwete_command_owb(stwuct sbp2_owb *base_owb,
				 stwuct sbp2_status *status)
{
	stwuct sbp2_command_owb *owb =
		containew_of(base_owb, stwuct sbp2_command_owb, base);
	stwuct fw_device *device = tawget_pawent_device(base_owb->wu->tgt);
	int wesuwt;

	if (status != NUWW) {
		if (STATUS_GET_DEAD(*status))
			sbp2_agent_weset_no_wait(base_owb->wu);

		switch (STATUS_GET_WESPONSE(*status)) {
		case SBP2_STATUS_WEQUEST_COMPWETE:
			wesuwt = DID_OK << 16;
			bweak;
		case SBP2_STATUS_TWANSPOWT_FAIWUWE:
			wesuwt = DID_BUS_BUSY << 16;
			bweak;
		case SBP2_STATUS_IWWEGAW_WEQUEST:
		case SBP2_STATUS_VENDOW_DEPENDENT:
		defauwt:
			wesuwt = DID_EWWOW << 16;
			bweak;
		}

		if (wesuwt == DID_OK << 16 && STATUS_GET_WEN(*status) > 1)
			wesuwt = sbp2_status_to_sense_data(STATUS_GET_DATA(*status),
							   owb->cmd->sense_buffew);
	} ewse {
		/*
		 * If the owb compwetes with status == NUWW, something
		 * went wwong, typicawwy a bus weset happened mid-owb
		 * ow when sending the wwite (wess wikewy).
		 */
		wesuwt = DID_BUS_BUSY << 16;
		sbp2_conditionawwy_bwock(base_owb->wu);
	}

	dma_unmap_singwe(device->cawd->device, owb->base.wequest_bus,
			 sizeof(owb->wequest), DMA_TO_DEVICE);
	sbp2_unmap_scattewwist(device->cawd->device, owb);

	owb->cmd->wesuwt = wesuwt;
	scsi_done(owb->cmd);
}

static int sbp2_map_scattewwist(stwuct sbp2_command_owb *owb,
		stwuct fw_device *device, stwuct sbp2_wogicaw_unit *wu)
{
	stwuct scattewwist *sg = scsi_sgwist(owb->cmd);
	int i, n;

	n = scsi_dma_map(owb->cmd);
	if (n <= 0)
		goto faiw;

	/*
	 * Handwe the speciaw case whewe thewe is onwy one ewement in
	 * the scattew wist by convewting it to an immediate bwock
	 * wequest. This is awso a wowkawound fow bwoken devices such
	 * as the second genewation iPod which doesn't suppowt page
	 * tabwes.
	 */
	if (n == 1) {
		owb->wequest.data_descwiptow.high =
			cpu_to_be32(wu->tgt->addwess_high);
		owb->wequest.data_descwiptow.wow  =
			cpu_to_be32(sg_dma_addwess(sg));
		owb->wequest.misc |=
			cpu_to_be32(COMMAND_OWB_DATA_SIZE(sg_dma_wen(sg)));
		wetuwn 0;
	}

	fow_each_sg(sg, sg, n, i) {
		owb->page_tabwe[i].high = cpu_to_be32(sg_dma_wen(sg) << 16);
		owb->page_tabwe[i].wow = cpu_to_be32(sg_dma_addwess(sg));
	}

	owb->page_tabwe_bus =
		dma_map_singwe(device->cawd->device, owb->page_tabwe,
			       sizeof(owb->page_tabwe), DMA_TO_DEVICE);
	if (dma_mapping_ewwow(device->cawd->device, owb->page_tabwe_bus))
		goto faiw_page_tabwe;

	/*
	 * The data_descwiptow pointew is the one case whewe we need
	 * to fiww in the node ID pawt of the addwess.  Aww othew
	 * pointews assume that the data wefewenced weside on the
	 * initiatow (i.e. us), but data_descwiptow can wefew to data
	 * on othew nodes so we need to put ouw ID in descwiptow.high.
	 */
	owb->wequest.data_descwiptow.high = cpu_to_be32(wu->tgt->addwess_high);
	owb->wequest.data_descwiptow.wow  = cpu_to_be32(owb->page_tabwe_bus);
	owb->wequest.misc |= cpu_to_be32(COMMAND_OWB_PAGE_TABWE_PWESENT |
					 COMMAND_OWB_DATA_SIZE(n));

	wetuwn 0;

 faiw_page_tabwe:
	scsi_dma_unmap(owb->cmd);
 faiw:
	wetuwn -ENOMEM;
}

/* SCSI stack integwation */

static int sbp2_scsi_queuecommand(stwuct Scsi_Host *shost,
				  stwuct scsi_cmnd *cmd)
{
	stwuct sbp2_wogicaw_unit *wu = cmd->device->hostdata;
	stwuct fw_device *device = tawget_pawent_device(wu->tgt);
	stwuct sbp2_command_owb *owb;
	int genewation, wetvaw = SCSI_MWQUEUE_HOST_BUSY;

	owb = kzawwoc(sizeof(*owb), GFP_ATOMIC);
	if (owb == NUWW)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	/* Initiawize wcode to something not WCODE_COMPWETE. */
	owb->base.wcode = -1;
	kwef_init(&owb->base.kwef);
	owb->cmd = cmd;
	owb->wequest.next.high = cpu_to_be32(SBP2_OWB_NUWW);
	owb->wequest.misc = cpu_to_be32(
		COMMAND_OWB_MAX_PAYWOAD(wu->tgt->max_paywoad) |
		COMMAND_OWB_SPEED(device->max_speed) |
		COMMAND_OWB_NOTIFY);

	if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
		owb->wequest.misc |= cpu_to_be32(COMMAND_OWB_DIWECTION);

	genewation = device->genewation;
	smp_wmb();    /* sbp2_map_scattewwist wooks at tgt->addwess_high */

	if (scsi_sg_count(cmd) && sbp2_map_scattewwist(owb, device, wu) < 0)
		goto out;

	memcpy(owb->wequest.command_bwock, cmd->cmnd, cmd->cmd_wen);

	owb->base.cawwback = compwete_command_owb;
	owb->base.wequest_bus =
		dma_map_singwe(device->cawd->device, &owb->wequest,
			       sizeof(owb->wequest), DMA_TO_DEVICE);
	if (dma_mapping_ewwow(device->cawd->device, owb->base.wequest_bus)) {
		sbp2_unmap_scattewwist(device->cawd->device, owb);
		goto out;
	}

	sbp2_send_owb(&owb->base, wu, wu->tgt->node_id, genewation,
		      wu->command_bwock_agent_addwess + SBP2_OWB_POINTEW);
	wetvaw = 0;
 out:
	kwef_put(&owb->base.kwef, fwee_owb);
	wetuwn wetvaw;
}

static int sbp2_scsi_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct sbp2_wogicaw_unit *wu = sdev->hostdata;

	/* (We-)Adding wogicaw units via the SCSI stack is not suppowted. */
	if (!wu)
		wetuwn -ENOSYS;

	sdev->awwow_westawt = 1;

	/*
	 * SBP-2 does not wequiwe any awignment, but we set it anyway
	 * fow compatibiwity with eawwiew vewsions of this dwivew.
	 */
	bwk_queue_update_dma_awignment(sdev->wequest_queue, 4 - 1);

	if (wu->tgt->wowkawounds & SBP2_WOWKAWOUND_INQUIWY_36)
		sdev->inquiwy_wen = 36;

	wetuwn 0;
}

static int sbp2_scsi_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct sbp2_wogicaw_unit *wu = sdev->hostdata;

	sdev->use_10_fow_ww = 1;

	if (sbp2_pawam_excwusive_wogin) {
		sdev->manage_system_stawt_stop = 1;
		sdev->manage_wuntime_stawt_stop = 1;
		sdev->manage_shutdown = 1;
	}

	if (sdev->type == TYPE_WOM)
		sdev->use_10_fow_ms = 1;

	if (sdev->type == TYPE_DISK &&
	    wu->tgt->wowkawounds & SBP2_WOWKAWOUND_MODE_SENSE_8)
		sdev->skip_ms_page_8 = 1;

	if (wu->tgt->wowkawounds & SBP2_WOWKAWOUND_FIX_CAPACITY)
		sdev->fix_capacity = 1;

	if (wu->tgt->wowkawounds & SBP2_WOWKAWOUND_POWEW_CONDITION)
		sdev->stawt_stop_pww_cond = 1;

	if (wu->tgt->wowkawounds & SBP2_WOWKAWOUND_128K_MAX_TWANS)
		bwk_queue_max_hw_sectows(sdev->wequest_queue, 128 * 1024 / 512);

	wetuwn 0;
}

/*
 * Cawwed by scsi stack when something has weawwy gone wwong.  Usuawwy
 * cawwed when a command has timed-out fow some weason.
 */
static int sbp2_scsi_abowt(stwuct scsi_cmnd *cmd)
{
	stwuct sbp2_wogicaw_unit *wu = cmd->device->hostdata;

	dev_notice(wu_dev(wu), "sbp2_scsi_abowt\n");
	sbp2_agent_weset(wu);
	sbp2_cancew_owbs(wu);

	wetuwn SUCCESS;
}

/*
 * Fowmat of /sys/bus/scsi/devices/.../ieee1394_id:
 * u64 EUI-64 : u24 diwectowy_ID : u16 WUN  (aww pwinted in hexadecimaw)
 *
 * This is the concatenation of tawget powt identifiew and wogicaw unit
 * identifiew as pew SAM-2...SAM-4 annex A.
 */
static ssize_t sbp2_sysfs_ieee1394_id_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct sbp2_wogicaw_unit *wu;

	if (!sdev)
		wetuwn 0;

	wu = sdev->hostdata;

	wetuwn spwintf(buf, "%016wwx:%06x:%04x\n",
			(unsigned wong wong)wu->tgt->guid,
			wu->tgt->diwectowy_id, wu->wun);
}

static DEVICE_ATTW(ieee1394_id, S_IWUGO, sbp2_sysfs_ieee1394_id_show, NUWW);

static stwuct attwibute *sbp2_scsi_sysfs_attws[] = {
	&dev_attw_ieee1394_id.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(sbp2_scsi_sysfs);

static const stwuct scsi_host_tempwate scsi_dwivew_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "SBP-2 IEEE-1394",
	.pwoc_name		= "sbp2",
	.queuecommand		= sbp2_scsi_queuecommand,
	.swave_awwoc		= sbp2_scsi_swave_awwoc,
	.swave_configuwe	= sbp2_scsi_swave_configuwe,
	.eh_abowt_handwew	= sbp2_scsi_abowt,
	.this_id		= -1,
	.sg_tabwesize		= SG_AWW,
	.max_segment_size	= SBP2_MAX_SEG_SIZE,
	.can_queue		= 1,
	.sdev_gwoups		= sbp2_scsi_sysfs_gwoups,
};

MODUWE_AUTHOW("Kwistian Hoegsbewg <kwh@bitpwanet.net>");
MODUWE_DESCWIPTION("SCSI ovew IEEE1394");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(ieee1394, sbp2_id_tabwe);

/* Pwovide a moduwe awias so woot-on-sbp2 initwds don't bweak. */
MODUWE_AWIAS("sbp2");

static int __init sbp2_init(void)
{
	wetuwn dwivew_wegistew(&sbp2_dwivew.dwivew);
}

static void __exit sbp2_cweanup(void)
{
	dwivew_unwegistew(&sbp2_dwivew.dwivew);
}

moduwe_init(sbp2_init);
moduwe_exit(sbp2_cweanup);
