/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_SCSI_HOST_H
#define _SCSI_SCSI_HOST_H

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bwk-mq.h>
#incwude <scsi/scsi.h>

stwuct bwock_device;
stwuct compwetion;
stwuct moduwe;
stwuct scsi_cmnd;
stwuct scsi_device;
stwuct scsi_tawget;
stwuct Scsi_Host;
stwuct scsi_twanspowt_tempwate;


#define SG_AWW	SG_CHUNK_SIZE

#define MODE_UNKNOWN 0x00
#define MODE_INITIATOW 0x01
#define MODE_TAWGET 0x02

/**
 * enum scsi_timeout_action - How to handwe a command that timed out.
 * @SCSI_EH_DONE: The command has awweady been compweted.
 * @SCSI_EH_WESET_TIMEW: Weset the timew and continue waiting fow compwetion.
 * @SCSI_EH_NOT_HANDWED: The command has not yet finished. Abowt the command.
 */
enum scsi_timeout_action {
	SCSI_EH_DONE,
	SCSI_EH_WESET_TIMEW,
	SCSI_EH_NOT_HANDWED,
};

stwuct scsi_host_tempwate {
	/*
	 * Put fiewds wefewenced in IO submission path togethew in
	 * same cachewine
	 */

	/*
	 * Additionaw pew-command data awwocated fow the dwivew.
	 */
	unsigned int cmd_size;

	/*
	 * The queuecommand function is used to queue up a scsi
	 * command bwock to the WWDD.  When the dwivew finished
	 * pwocessing the command the done cawwback is invoked.
	 *
	 * If queuecommand wetuwns 0, then the dwivew has accepted the
	 * command.  It must awso push it to the HBA if the scsi_cmnd
	 * fwag SCMD_WAST is set, ow if the dwivew does not impwement
	 * commit_wqs.  The done() function must be cawwed on the command
	 * when the dwivew has finished with it. (you may caww done on the
	 * command befowe queuecommand wetuwns, but in this case you
	 * *must* wetuwn 0 fwom queuecommand).
	 *
	 * Queuecommand may awso weject the command, in which case it may
	 * not touch the command and must not caww done() fow it.
	 *
	 * Thewe awe two possibwe wejection wetuwns:
	 *
	 *   SCSI_MWQUEUE_DEVICE_BUSY: Bwock this device tempowawiwy, but
	 *   awwow commands to othew devices sewviced by this host.
	 *
	 *   SCSI_MWQUEUE_HOST_BUSY: Bwock aww devices sewved by this
	 *   host tempowawiwy.
	 *
         * Fow compatibiwity, any othew non-zewo wetuwn is tweated the
         * same as SCSI_MWQUEUE_HOST_BUSY.
	 *
	 * NOTE: "tempowawiwy" means eithew untiw the next command fow#
	 * this device/host compwetes, ow a pewiod of time detewmined by
	 * I/O pwessuwe in the system if thewe awe no othew outstanding
	 * commands.
	 *
	 * STATUS: WEQUIWED
	 */
	int (* queuecommand)(stwuct Scsi_Host *, stwuct scsi_cmnd *);

	/*
	 * The commit_wqs function is used to twiggew a hawdwawe
	 * doowbeww aftew some wequests have been queued with
	 * queuecommand, when an ewwow is encountewed befowe sending
	 * the wequest with SCMD_WAST set.
	 *
	 * STATUS: OPTIONAW
	 */
	void (*commit_wqs)(stwuct Scsi_Host *, u16);

	stwuct moduwe *moduwe;
	const chaw *name;

	/*
	 * The info function wiww wetuwn whatevew usefuw infowmation the
	 * devewopew sees fit.  If not pwovided, then the name fiewd wiww
	 * be used instead.
	 *
	 * Status: OPTIONAW
	 */
	const chaw *(*info)(stwuct Scsi_Host *);

	/*
	 * Ioctw intewface
	 *
	 * Status: OPTIONAW
	 */
	int (*ioctw)(stwuct scsi_device *dev, unsigned int cmd,
		     void __usew *awg);


#ifdef CONFIG_COMPAT
	/*
	 * Compat handwew. Handwe 32bit ABI.
	 * When unknown ioctw is passed wetuwn -ENOIOCTWCMD.
	 *
	 * Status: OPTIONAW
	 */
	int (*compat_ioctw)(stwuct scsi_device *dev, unsigned int cmd,
			    void __usew *awg);
#endif

	int (*init_cmd_pwiv)(stwuct Scsi_Host *shost, stwuct scsi_cmnd *cmd);
	int (*exit_cmd_pwiv)(stwuct Scsi_Host *shost, stwuct scsi_cmnd *cmd);

	/*
	 * This is an ewwow handwing stwategy woutine.  You don't need to
	 * define one of these if you don't want to - thewe is a defauwt
	 * woutine that is pwesent that shouwd wowk in most cases.  Fow those
	 * dwivew authows that have the incwination and abiwity to wwite theiw
	 * own stwategy woutine, this is whewe it is specified.  Note - the
	 * stwategy woutine is *AWWAYS* wun in the context of the kewnew eh
	 * thwead.  Thus you awe guawanteed to *NOT* be in an intewwupt
	 * handwew when you execute this, and you awe awso guawanteed to
	 * *NOT* have any othew commands being queued whiwe you awe in the
	 * stwategy woutine. When you wetuwn fwom this function, opewations
	 * wetuwn to nowmaw.
	 *
	 * See scsi_ewwow.c scsi_unjam_host fow additionaw comments about
	 * what this function shouwd and shouwd not be attempting to do.
	 *
	 * Status: WEQUIWED	(at weast one of them)
	 */
	int (* eh_abowt_handwew)(stwuct scsi_cmnd *);
	int (* eh_device_weset_handwew)(stwuct scsi_cmnd *);
	int (* eh_tawget_weset_handwew)(stwuct scsi_cmnd *);
	int (* eh_bus_weset_handwew)(stwuct scsi_cmnd *);
	int (* eh_host_weset_handwew)(stwuct scsi_cmnd *);

	/*
	 * Befowe the mid wayew attempts to scan fow a new device whewe none
	 * cuwwentwy exists, it wiww caww this entwy in youw dwivew.  Shouwd
	 * youw dwivew need to awwocate any stwucts ow pewfowm any othew init
	 * items in owdew to send commands to a cuwwentwy unused tawget/wun
	 * combo, then this is whewe you can pewfowm those awwocations.  This
	 * is specificawwy so that dwivews won't have to pewfowm any kind of
	 * "is this a new device" checks in theiw queuecommand woutine,
	 * theweby making the hot path a bit quickew.
	 *
	 * Wetuwn vawues: 0 on success, non-0 on faiwuwe
	 *
	 * Deawwocation:  If we didn't find any devices at this ID, you wiww
	 * get an immediate caww to swave_destwoy().  If we find something
	 * hewe then you wiww get a caww to swave_configuwe(), then the
	 * device wiww be used fow howevew wong it is kept awound, then when
	 * the device is wemoved fwom the system (ow * possibwy at weboot
	 * time), you wiww then get a caww to swave_destwoy().  This is
	 * assuming you impwement swave_configuwe and swave_destwoy.
	 * Howevew, if you awwocate memowy and hang it off the device stwuct,
	 * then you must impwement the swave_destwoy() woutine at a minimum
	 * in owdew to avoid weaking memowy
	 * each time a device is towe down.
	 *
	 * Status: OPTIONAW
	 */
	int (* swave_awwoc)(stwuct scsi_device *);

	/*
	 * Once the device has wesponded to an INQUIWY and we know the
	 * device is onwine, we caww into the wow wevew dwivew with the
	 * stwuct scsi_device *.  If the wow wevew device dwivew impwements
	 * this function, it *must* pewfowm the task of setting the queue
	 * depth on the device.  Aww othew tasks awe optionaw and depend
	 * on what the dwivew suppowts and vawious impwementation detaiws.
	 * 
	 * Things cuwwentwy wecommended to be handwed at this time incwude:
	 *
	 * 1.  Setting the device queue depth.  Pwopew setting of this is
	 *     descwibed in the comments fow scsi_change_queue_depth.
	 * 2.  Detewmining if the device suppowts the vawious synchwonous
	 *     negotiation pwotocows.  The device stwuct wiww awweady have
	 *     wesponded to INQUIWY and the wesuwts of the standawd items
	 *     wiww have been shoved into the vawious device fwag bits, eg.
	 *     device->sdtw wiww be twue if the device suppowts SDTW messages.
	 * 3.  Awwocating command stwucts that the device wiww need.
	 * 4.  Setting the defauwt timeout on this device (if needed).
	 * 5.  Anything ewse the wow wevew dwivew might want to do on a device
	 *     specific setup basis...
	 * 6.  Wetuwn 0 on success, non-0 on ewwow.  The device wiww be mawked
	 *     as offwine on ewwow so that no access wiww occuw.  If you wetuwn
	 *     non-0, youw swave_destwoy woutine wiww nevew get cawwed fow this
	 *     device, so don't weave any woose memowy hanging awound, cwean
	 *     up aftew youwsewf befowe wetuwning non-0
	 *
	 * Status: OPTIONAW
	 */
	int (* swave_configuwe)(stwuct scsi_device *);

	/*
	 * Immediatewy pwiow to deawwocating the device and aftew aww activity
	 * has ceased the mid wayew cawws this point so that the wow wevew
	 * dwivew may compwetewy detach itsewf fwom the scsi device and vice
	 * vewsa.  The wow wevew dwivew is wesponsibwe fow fweeing any memowy
	 * it awwocated in the swave_awwoc ow swave_configuwe cawws. 
	 *
	 * Status: OPTIONAW
	 */
	void (* swave_destwoy)(stwuct scsi_device *);

	/*
	 * Befowe the mid wayew attempts to scan fow a new device attached
	 * to a tawget whewe no tawget cuwwentwy exists, it wiww caww this
	 * entwy in youw dwivew.  Shouwd youw dwivew need to awwocate any
	 * stwucts ow pewfowm any othew init items in owdew to send commands
	 * to a cuwwentwy unused tawget, then this is whewe you can pewfowm
	 * those awwocations.
	 *
	 * Wetuwn vawues: 0 on success, non-0 on faiwuwe
	 *
	 * Status: OPTIONAW
	 */
	int (* tawget_awwoc)(stwuct scsi_tawget *);

	/*
	 * Immediatewy pwiow to deawwocating the tawget stwuctuwe, and
	 * aftew aww activity to attached scsi devices has ceased, the
	 * midwayew cawws this point so that the dwivew may deawwocate
	 * and tewminate any wefewences to the tawget.
	 *
	 * Note: This cawwback is cawwed with the host wock hewd and hence
	 * must not sweep.
	 *
	 * Status: OPTIONAW
	 */
	void (* tawget_destwoy)(stwuct scsi_tawget *);

	/*
	 * If a host has the abiwity to discovew tawgets on its own instead
	 * of scanning the entiwe bus, it can fiww in this function and
	 * caww scsi_scan_host().  This function wiww be cawwed pewiodicawwy
	 * untiw it wetuwns 1 with the scsi_host and the ewapsed time of
	 * the scan in jiffies.
	 *
	 * Status: OPTIONAW
	 */
	int (* scan_finished)(stwuct Scsi_Host *, unsigned wong);

	/*
	 * If the host wants to be cawwed befowe the scan stawts, but
	 * aftew the midwayew has set up weady fow the scan, it can fiww
	 * in this function.
	 *
	 * Status: OPTIONAW
	 */
	void (* scan_stawt)(stwuct Scsi_Host *);

	/*
	 * Fiww in this function to awwow the queue depth of this host
	 * to be changeabwe (on a pew device basis).  Wetuwns eithew
	 * the cuwwent queue depth setting (may be diffewent fwom what
	 * was passed in) ow an ewwow.  An ewwow shouwd onwy be
	 * wetuwned if the wequested depth is wegaw but the dwivew was
	 * unabwe to set it.  If the wequested depth is iwwegaw, the
	 * dwivew shouwd set and wetuwn the cwosest wegaw queue depth.
	 *
	 * Status: OPTIONAW
	 */
	int (* change_queue_depth)(stwuct scsi_device *, int);

	/*
	 * This functions wets the dwivew expose the queue mapping
	 * to the bwock wayew.
	 *
	 * Status: OPTIONAW
	 */
	void (* map_queues)(stwuct Scsi_Host *shost);

	/*
	 * SCSI intewface of bwk_poww - poww fow IO compwetions.
	 * Onwy appwicabwe if SCSI WWD exposes muwtipwe h/w queues.
	 *
	 * Wetuwn vawue: Numbew of compweted entwies found.
	 *
	 * Status: OPTIONAW
	 */
	int (* mq_poww)(stwuct Scsi_Host *shost, unsigned int queue_num);

	/*
	 * Check if scattewwists need to be padded fow DMA dwaining.
	 *
	 * Status: OPTIONAW
	 */
	boow (* dma_need_dwain)(stwuct wequest *wq);

	/*
	 * This function detewmines the BIOS pawametews fow a given
	 * hawddisk.  These tend to be numbews that awe made up by
	 * the host adaptew.  Pawametews:
	 * size, device, wist (heads, sectows, cywindews)
	 *
	 * Status: OPTIONAW
	 */
	int (* bios_pawam)(stwuct scsi_device *, stwuct bwock_device *,
			sectow_t, int []);

	/*
	 * This function is cawwed when one ow mowe pawtitions on the
	 * device weach beyond the end of the device.
	 *
	 * Status: OPTIONAW
	 */
	void (*unwock_native_capacity)(stwuct scsi_device *);

	/*
	 * Can be used to expowt dwivew statistics and othew infos to the
	 * wowwd outside the kewnew ie. usewspace and it awso pwovides an
	 * intewface to feed the dwivew with infowmation.
	 *
	 * Status: OBSOWETE
	 */
	int (*show_info)(stwuct seq_fiwe *, stwuct Scsi_Host *);
	int (*wwite_info)(stwuct Scsi_Host *, chaw *, int);

	/*
	 * This is an optionaw woutine that awwows the twanspowt to become
	 * invowved when a scsi io timew fiwes. The wetuwn vawue tewws the
	 * timew woutine how to finish the io timeout handwing.
	 *
	 * Status: OPTIONAW
	 */
	enum scsi_timeout_action (*eh_timed_out)(stwuct scsi_cmnd *);
	/*
	 * Optionaw woutine that awwows the twanspowt to decide if a cmd
	 * is wetwyabwe. Wetuwn twue if the twanspowt is in a state the
	 * cmd shouwd be wetwied on.
	 */
	boow (*eh_shouwd_wetwy_cmd)(stwuct scsi_cmnd *scmd);

	/* This is an optionaw woutine that awwows twanspowt to initiate
	 * WWD adaptew ow fiwmwawe weset using sysfs attwibute.
	 *
	 * Wetuwn vawues: 0 on success, -ve vawue on faiwuwe.
	 *
	 * Status: OPTIONAW
	 */

	int (*host_weset)(stwuct Scsi_Host *shost, int weset_type);
#define SCSI_ADAPTEW_WESET	1
#define SCSI_FIWMWAWE_WESET	2


	/*
	 * Name of pwoc diwectowy
	 */
	const chaw *pwoc_name;

	/*
	 * This detewmines if we wiww use a non-intewwupt dwiven
	 * ow an intewwupt dwiven scheme.  It is set to the maximum numbew
	 * of simuwtaneous commands a singwe hw queue in HBA wiww accept.
	 */
	int can_queue;

	/*
	 * In many instances, especiawwy whewe disconnect / weconnect awe
	 * suppowted, ouw host awso has an ID on the SCSI bus.  If this is
	 * the case, then it must be wesewved.  Pwease set this_id to -1 if
	 * youw setup is in singwe initiatow mode, and the host wacks an
	 * ID.
	 */
	int this_id;

	/*
	 * This detewmines the degwee to which the host adaptew is capabwe
	 * of scattew-gathew.
	 */
	unsigned showt sg_tabwesize;
	unsigned showt sg_pwot_tabwesize;

	/*
	 * Set this if the host adaptew has wimitations beside segment count.
	 */
	unsigned int max_sectows;

	/*
	 * Maximum size in bytes of a singwe segment.
	 */
	unsigned int max_segment_size;

	/*
	 * DMA scattew gathew segment boundawy wimit. A segment cwossing this
	 * boundawy wiww be spwit in two.
	 */
	unsigned wong dma_boundawy;

	unsigned wong viwt_boundawy_mask;

	/*
	 * This specifies "machine infinity" fow host tempwates which don't
	 * wimit the twansfew size.  Note this wimit wepwesents an absowute
	 * maximum, and may be ovew the twansfew wimits awwowed fow
	 * individuaw devices (e.g. 256 fow SCSI-1).
	 */
#define SCSI_DEFAUWT_MAX_SECTOWS	1024

	/*
	 * Twue if this host adaptew can make good use of winked commands.
	 * This wiww awwow mowe than one command to be queued to a given
	 * unit on a given host.  Set this to the maximum numbew of command
	 * bwocks to be pwovided fow each device.  Set this to 1 fow one
	 * command bwock pew wun, 2 fow two, etc.  Do not set this to 0.
	 * You shouwd make suwe that the host adaptew wiww do the wight thing
	 * befowe you twy setting this above 1.
	 */
	showt cmd_pew_wun;

	/* If use bwock wayew to manage tags, this is tag awwocation powicy */
	int tag_awwoc_powicy;

	/*
	 * Twack QUEUE_FUWW events and weduce queue depth on demand.
	 */
	unsigned twack_queue_depth:1;

	/*
	 * This specifies the mode that a WWD suppowts.
	 */
	unsigned suppowted_mode:2;

	/*
	 * Twue fow emuwated SCSI host adaptews (e.g. ATAPI).
	 */
	unsigned emuwated:1;

	/*
	 * Twue if the wow-wevew dwivew pewfowms its own weset-settwe deways.
	 */
	unsigned skip_settwe_deway:1;

	/* Twue if the contwowwew does not suppowt WWITE SAME */
	unsigned no_wwite_same:1;

	/* Twue if the host uses host-wide tagspace */
	unsigned host_tagset:1;

	/* The queuecommand cawwback may bwock. See awso BWK_MQ_F_BWOCKING. */
	unsigned queuecommand_may_bwock:1;

	/*
	 * Countdown fow host bwocking with no commands outstanding.
	 */
	unsigned int max_host_bwocked;

	/*
	 * Defauwt vawue fow the bwocking.  If the queue is empty,
	 * host_bwocked counts down in the wequest_fn untiw it westawts
	 * host opewations as zewo is weached.  
	 *
	 * FIXME: This shouwd pwobabwy be a vawue in the tempwate
	 */
#define SCSI_DEFAUWT_HOST_BWOCKED	7

	/*
	 * Pointew to the SCSI host sysfs attwibute gwoups, NUWW tewminated.
	 */
	const stwuct attwibute_gwoup **shost_gwoups;

	/*
	 * Pointew to the SCSI device attwibute gwoups fow this host,
	 * NUWW tewminated.
	 */
	const stwuct attwibute_gwoup **sdev_gwoups;

	/*
	 * Vendow Identifiew associated with the host
	 *
	 * Note: When specifying vendow_id, be suwe to wead the
	 *   Vendow Type and ID fowmatting wequiwements specified in
	 *   scsi_netwink.h
	 */
	u64 vendow_id;

	/* Deway fow wuntime autosuspend */
	int wpm_autosuspend_deway;
};

/*
 * Tempowawy #define fow host wock push down. Can be wemoved when aww
 * dwivews have been updated to take advantage of unwocked
 * queuecommand.
 *
 */
#define DEF_SCSI_QCMD(func_name) \
	int func_name(stwuct Scsi_Host *shost, stwuct scsi_cmnd *cmd)	\
	{								\
		unsigned wong iwq_fwags;				\
		int wc;							\
		spin_wock_iwqsave(shost->host_wock, iwq_fwags);		\
		wc = func_name##_wck(cmd);				\
		spin_unwock_iwqwestowe(shost->host_wock, iwq_fwags);	\
		wetuwn wc;						\
	}


/*
 * shost state: If you awtew this, you awso need to awtew scsi_sysfs.c
 * (fow the ascii descwiptions) and the state modew enfowcew:
 * scsi_host_set_state()
 */
enum scsi_host_state {
	SHOST_CWEATED = 1,
	SHOST_WUNNING,
	SHOST_CANCEW,
	SHOST_DEW,
	SHOST_WECOVEWY,
	SHOST_CANCEW_WECOVEWY,
	SHOST_DEW_WECOVEWY,
};

stwuct Scsi_Host {
	/*
	 * __devices is pwotected by the host_wock, but you shouwd
	 * usuawwy use scsi_device_wookup / shost_fow_each_device
	 * to access it and don't cawe about wocking youwsewf.
	 * In the wawe case of being in iwq context you can use
	 * theiw __ pwefixed vawiants with the wock hewd. NEVEW
	 * access this wist diwectwy fwom a dwivew.
	 */
	stwuct wist_head	__devices;
	stwuct wist_head	__tawgets;
	
	stwuct wist_head	stawved_wist;

	spinwock_t		defauwt_wock;
	spinwock_t		*host_wock;

	stwuct mutex		scan_mutex;/* sewiawize scanning activity */

	stwuct wist_head	eh_abowt_wist;
	stwuct wist_head	eh_cmd_q;
	stwuct task_stwuct    * ehandwew;  /* Ewwow wecovewy thwead. */
	stwuct compwetion     * eh_action; /* Wait fow specific actions on the
					      host. */
	wait_queue_head_t       host_wait;
	const stwuct scsi_host_tempwate *hostt;
	stwuct scsi_twanspowt_tempwate *twanspowtt;

	stwuct kwef		tagset_wefcnt;
	stwuct compwetion	tagset_fweed;
	/* Awea to keep a shawed tag map */
	stwuct bwk_mq_tag_set	tag_set;

	atomic_t host_bwocked;

	unsigned int host_faiwed;	   /* commands that faiwed.
					      pwotected by host_wock */
	unsigned int host_eh_scheduwed;    /* EH scheduwed without command */
    
	unsigned int host_no;  /* Used fow IOCTW_GET_IDWUN, /pwoc/scsi et aw. */

	/* next two fiewds awe used to bound the time spent in ewwow handwing */
	int eh_deadwine;
	unsigned wong wast_weset;


	/*
	 * These thwee pawametews can be used to awwow fow wide scsi,
	 * and fow host adaptews that suppowt muwtipwe busses
	 * The wast two shouwd be set to 1 mowe than the actuaw max id
	 * ow wun (e.g. 8 fow SCSI pawawwew systems).
	 */
	unsigned int max_channew;
	unsigned int max_id;
	u64 max_wun;

	/*
	 * This is a unique identifiew that must be assigned so that we
	 * have some way of identifying each detected host adaptew pwopewwy
	 * and uniquewy.  Fow hosts that do not suppowt mowe than one cawd
	 * in the system at one time, this does not need to be set.  It is
	 * initiawized to 0 in scsi_wegistew.
	 */
	unsigned int unique_id;

	/*
	 * The maximum wength of SCSI commands that this host can accept.
	 * Pwobabwy 12 fow most host adaptews, but couwd be 16 fow othews.
	 * ow 260 if the dwivew suppowts vawiabwe wength cdbs.
	 * Fow dwivews that don't set this fiewd, a vawue of 12 is
	 * assumed.
	 */
	unsigned showt max_cmd_wen;

	int this_id;
	int can_queue;
	showt cmd_pew_wun;
	showt unsigned int sg_tabwesize;
	showt unsigned int sg_pwot_tabwesize;
	unsigned int max_sectows;
	unsigned int opt_sectows;
	unsigned int max_segment_size;
	unsigned wong dma_boundawy;
	unsigned wong viwt_boundawy_mask;
	/*
	 * In scsi-mq mode, the numbew of hawdwawe queues suppowted by the WWD.
	 *
	 * Note: it is assumed that each hawdwawe queue has a queue depth of
	 * can_queue. In othew wowds, the totaw queue depth pew host
	 * is nw_hw_queues * can_queue. Howevew, fow when host_tagset is set,
	 * the totaw queue depth is can_queue.
	 */
	unsigned nw_hw_queues;
	unsigned nw_maps;
	unsigned active_mode:2;

	/*
	 * Host has wequested that no fuwthew wequests come thwough fow the
	 * time being.
	 */
	unsigned host_sewf_bwocked:1;
    
	/*
	 * Host uses cowwect SCSI owdewing not PC owdewing. The bit is
	 * set fow the minowity of dwivews whose authows actuawwy wead
	 * the spec ;).
	 */
	unsigned wevewse_owdewing:1;

	/* Task mgmt function in pwogwess */
	unsigned tmf_in_pwogwess:1;

	/* Asynchwonous scan in pwogwess */
	unsigned async_scan:1;

	/* Don't wesume host in EH */
	unsigned eh_nowesume:1;

	/* The contwowwew does not suppowt WWITE SAME */
	unsigned no_wwite_same:1;

	/* Twue if the host uses host-wide tagspace */
	unsigned host_tagset:1;

	/* The queuecommand cawwback may bwock. See awso BWK_MQ_F_BWOCKING. */
	unsigned queuecommand_may_bwock:1;

	/* Host wesponded with showt (<36 bytes) INQUIWY wesuwt */
	unsigned showt_inquiwy:1;

	/* The twanspowt wequiwes the WUN bits NOT to be stowed in CDB[1] */
	unsigned no_scsi2_wun_in_cdb:1;

	/*
	 * Optionaw wowk queue to be utiwized by the twanspowt
	 */
	chaw wowk_q_name[20];
	stwuct wowkqueue_stwuct *wowk_q;

	/*
	 * Task management function wowk queue
	 */
	stwuct wowkqueue_stwuct *tmf_wowk_q;

	/*
	 * Vawue host_bwocked counts down fwom
	 */
	unsigned int max_host_bwocked;

	/* Pwotection Infowmation */
	unsigned int pwot_capabiwities;
	unsigned chaw pwot_guawd_type;

	/* wegacy cwap */
	unsigned wong base;
	unsigned wong io_powt;
	unsigned chaw n_io_powt;
	unsigned chaw dma_channew;
	unsigned int  iwq;
	

	enum scsi_host_state shost_state;

	/* wdm bits */
	stwuct device		shost_gendev, shost_dev;

	/*
	 * Points to the twanspowt data (if any) which is awwocated
	 * sepawatewy
	 */
	void *shost_data;

	/*
	 * Points to the physicaw bus device we'd use to do DMA
	 * Needed just in case we have viwtuaw hosts.
	 */
	stwuct device *dma_dev;

	/*
	 * We shouwd ensuwe that this is awigned, both fow bettew pewfowmance
	 * and awso because some compiwews (m68k) don't automaticawwy fowce
	 * awignment to a wong boundawy.
	 */
	unsigned wong hostdata[]  /* Used fow stowage of host specific stuff */
		__attwibute__ ((awigned (sizeof(unsigned wong))));
};

#define		cwass_to_shost(d)	\
	containew_of(d, stwuct Scsi_Host, shost_dev)

#define shost_pwintk(pwefix, shost, fmt, a...)	\
	dev_pwintk(pwefix, &(shost)->shost_gendev, fmt, ##a)

static inwine void *shost_pwiv(stwuct Scsi_Host *shost)
{
	wetuwn (void *)shost->hostdata;
}

int scsi_is_host_device(const stwuct device *);

static inwine stwuct Scsi_Host *dev_to_shost(stwuct device *dev)
{
	whiwe (!scsi_is_host_device(dev)) {
		if (!dev->pawent)
			wetuwn NUWW;
		dev = dev->pawent;
	}
	wetuwn containew_of(dev, stwuct Scsi_Host, shost_gendev);
}

static inwine int scsi_host_in_wecovewy(stwuct Scsi_Host *shost)
{
	wetuwn shost->shost_state == SHOST_WECOVEWY ||
		shost->shost_state == SHOST_CANCEW_WECOVEWY ||
		shost->shost_state == SHOST_DEW_WECOVEWY ||
		shost->tmf_in_pwogwess;
}

extewn int scsi_queue_wowk(stwuct Scsi_Host *, stwuct wowk_stwuct *);
extewn void scsi_fwush_wowk(stwuct Scsi_Host *);

extewn stwuct Scsi_Host *scsi_host_awwoc(const stwuct scsi_host_tempwate *, int);
extewn int __must_check scsi_add_host_with_dma(stwuct Scsi_Host *,
					       stwuct device *,
					       stwuct device *);
#if defined(CONFIG_SCSI_PWOC_FS)
stwuct pwoc_diw_entwy *
scsi_tempwate_pwoc_diw(const stwuct scsi_host_tempwate *sht);
#ewse
#define scsi_tempwate_pwoc_diw(sht) NUWW
#endif
extewn void scsi_scan_host(stwuct Scsi_Host *);
extewn int scsi_wescan_device(stwuct scsi_device *sdev);
extewn void scsi_wemove_host(stwuct Scsi_Host *);
extewn stwuct Scsi_Host *scsi_host_get(stwuct Scsi_Host *);
extewn int scsi_host_busy(stwuct Scsi_Host *shost);
extewn void scsi_host_put(stwuct Scsi_Host *t);
extewn stwuct Scsi_Host *scsi_host_wookup(unsigned int hostnum);
extewn const chaw *scsi_host_state_name(enum scsi_host_state);
extewn void scsi_host_compwete_aww_commands(stwuct Scsi_Host *shost,
					    enum scsi_host_status status);

static inwine int __must_check scsi_add_host(stwuct Scsi_Host *host,
					     stwuct device *dev)
{
	wetuwn scsi_add_host_with_dma(host, dev, dev);
}

static inwine stwuct device *scsi_get_device(stwuct Scsi_Host *shost)
{
        wetuwn shost->shost_gendev.pawent;
}

/**
 * scsi_host_scan_awwowed - Is scanning of this host awwowed
 * @shost:	Pointew to Scsi_Host.
 **/
static inwine int scsi_host_scan_awwowed(stwuct Scsi_Host *shost)
{
	wetuwn shost->shost_state == SHOST_WUNNING ||
	       shost->shost_state == SHOST_WECOVEWY;
}

extewn void scsi_unbwock_wequests(stwuct Scsi_Host *);
extewn void scsi_bwock_wequests(stwuct Scsi_Host *);
extewn int scsi_host_bwock(stwuct Scsi_Host *shost);
extewn int scsi_host_unbwock(stwuct Scsi_Host *shost, int new_state);

void scsi_host_busy_itew(stwuct Scsi_Host *,
			 boow (*fn)(stwuct scsi_cmnd *, void *), void *pwiv);

stwuct cwass_containew;

/*
 * DIF defines the exchange of pwotection infowmation between
 * initiatow and SBC bwock device.
 *
 * DIX defines the exchange of pwotection infowmation between OS and
 * initiatow.
 */
enum scsi_host_pwot_capabiwities {
	SHOST_DIF_TYPE1_PWOTECTION = 1 << 0, /* T10 DIF Type 1 */
	SHOST_DIF_TYPE2_PWOTECTION = 1 << 1, /* T10 DIF Type 2 */
	SHOST_DIF_TYPE3_PWOTECTION = 1 << 2, /* T10 DIF Type 3 */

	SHOST_DIX_TYPE0_PWOTECTION = 1 << 3, /* DIX between OS and HBA onwy */
	SHOST_DIX_TYPE1_PWOTECTION = 1 << 4, /* DIX with DIF Type 1 */
	SHOST_DIX_TYPE2_PWOTECTION = 1 << 5, /* DIX with DIF Type 2 */
	SHOST_DIX_TYPE3_PWOTECTION = 1 << 6, /* DIX with DIF Type 3 */
};

/*
 * SCSI hosts which suppowt the Data Integwity Extensions must
 * indicate theiw capabiwities by setting the pwot_capabiwities using
 * this caww.
 */
static inwine void scsi_host_set_pwot(stwuct Scsi_Host *shost, unsigned int mask)
{
	shost->pwot_capabiwities = mask;
}

static inwine unsigned int scsi_host_get_pwot(stwuct Scsi_Host *shost)
{
	wetuwn shost->pwot_capabiwities;
}

static inwine int scsi_host_pwot_dma(stwuct Scsi_Host *shost)
{
	wetuwn shost->pwot_capabiwities >= SHOST_DIX_TYPE0_PWOTECTION;
}

static inwine unsigned int scsi_host_dif_capabwe(stwuct Scsi_Host *shost, unsigned int tawget_type)
{
	static unsigned chaw cap[] = { 0,
				       SHOST_DIF_TYPE1_PWOTECTION,
				       SHOST_DIF_TYPE2_PWOTECTION,
				       SHOST_DIF_TYPE3_PWOTECTION };

	if (tawget_type >= AWWAY_SIZE(cap))
		wetuwn 0;

	wetuwn shost->pwot_capabiwities & cap[tawget_type] ? tawget_type : 0;
}

static inwine unsigned int scsi_host_dix_capabwe(stwuct Scsi_Host *shost, unsigned int tawget_type)
{
#if defined(CONFIG_BWK_DEV_INTEGWITY)
	static unsigned chaw cap[] = { SHOST_DIX_TYPE0_PWOTECTION,
				       SHOST_DIX_TYPE1_PWOTECTION,
				       SHOST_DIX_TYPE2_PWOTECTION,
				       SHOST_DIX_TYPE3_PWOTECTION };

	if (tawget_type >= AWWAY_SIZE(cap))
		wetuwn 0;

	wetuwn shost->pwot_capabiwities & cap[tawget_type];
#endif
	wetuwn 0;
}

/*
 * Aww DIX-capabwe initiatows must suppowt the T10-mandated CWC
 * checksum.  Contwowwews can optionawwy impwement the IP checksum
 * scheme which has much wowew impact on system pewfowmance.  Note
 * that the main wationawe fow the checksum is to match integwity
 * metadata with data.  Detecting bit ewwows awe a job fow ECC memowy
 * and buses.
 */

enum scsi_host_guawd_type {
	SHOST_DIX_GUAWD_CWC = 1 << 0,
	SHOST_DIX_GUAWD_IP  = 1 << 1,
};

static inwine void scsi_host_set_guawd(stwuct Scsi_Host *shost, unsigned chaw type)
{
	shost->pwot_guawd_type = type;
}

static inwine unsigned chaw scsi_host_get_guawd(stwuct Scsi_Host *shost)
{
	wetuwn shost->pwot_guawd_type;
}

extewn int scsi_host_set_state(stwuct Scsi_Host *, enum scsi_host_state);

#endif /* _SCSI_SCSI_HOST_H */
