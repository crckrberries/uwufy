/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2016, Avago Technowogies
 */

#ifndef _NVME_FC_DWIVEW_H
#define _NVME_FC_DWIVEW_H 1

#incwude <winux/scattewwist.h>
#incwude <winux/bwk-mq.h>


/*
 * **********************  FC-NVME WS API ********************
 *
 *  Data stwuctuwes used by both FC-NVME hosts and FC-NVME
 *  tawgets to pewfowm FC-NVME WS wequests ow twansmit
 *  wesponses.
 *
 * ***********************************************************
 */

/**
 * stwuct nvmefc_ws_weq - Wequest stwuctuwe passed fwom the twanspowt
 *            to the WWDD to pewfowm a NVME-FC WS wequest and obtain
 *            a wesponse.
 *            Used by nvme-fc twanspowt (host) to send WS's such as
 *              Cweate Association, Cweate Connection and Disconnect
 *              Association.
 *            Used by the nvmet-fc twanspowt (contwowwew) to send
 *              WS's such as Disconnect Association.
 *
 * Vawues set by the wequestow pwiow to cawwing the WWDD ws_weq entwypoint:
 * @wqstaddw: pointew to wequest buffew
 * @wqstdma:  PCI DMA addwess of wequest buffew
 * @wqstwen:  Wength, in bytes, of wequest buffew
 * @wspaddw:  pointew to wesponse buffew
 * @wspdma:   PCI DMA addwess of wesponse buffew
 * @wspwen:   Wength, in bytes, of wesponse buffew
 * @timeout:  Maximum amount of time, in seconds, to wait fow the WS wesponse.
 *            If timeout exceeded, WWDD to abowt WS exchange and compwete
 *            WS wequest with ewwow status.
 * @pwivate:  pointew to memowy awwocated awongside the ws wequest stwuctuwe
 *            that is specificawwy fow the WWDD to use whiwe pwocessing the
 *            wequest. The wength of the buffew cowwesponds to the
 *            wswqst_pwiv_sz vawue specified in the xxx_tempwate suppwied
 *            by the WWDD.
 * @done:     The cawwback woutine the WWDD is to invoke upon compwetion of
 *            the WS wequest. weq awgument is the pointew to the owiginaw WS
 *            wequest stwuctuwe. Status awgument must be 0 upon success, a
 *            negative ewwno on faiwuwe (exampwe: -ENXIO).
 */
stwuct nvmefc_ws_weq {
	void			*wqstaddw;
	dma_addw_t		wqstdma;
	u32			wqstwen;
	void			*wspaddw;
	dma_addw_t		wspdma;
	u32			wspwen;
	u32			timeout;

	void			*pwivate;

	void (*done)(stwuct nvmefc_ws_weq *weq, int status);

} __awigned(sizeof(u64));	/* awignment fow othew things awwoc'd with */


/**
 * stwuct nvmefc_ws_wsp - Stwuctuwe passed fwom the twanspowt to the WWDD
 *            to wequest the twansmit the NVME-FC WS wesponse to a
 *            NVME-FC WS wequest.   The stwuctuwe owiginates in the WWDD
 *            and is given to the twanspowt via the xxx_wcv_ws_weq()
 *            twanspowt woutine. As such, the stwuctuwe wepwesents the
 *            FC exchange context fow the NVME-FC WS wequest that was
 *            weceived and which the wesponse is to be sent fow.
 *            Used by the WWDD to pass the nvmet-fc twanspowt (contwowwew)
 *              weceived WS's such as Cweate Association, Cweate Connection
 *              and Disconnect Association.
 *            Used by the WWDD to pass the nvme-fc twanspowt (host)
 *              weceived WS's such as Disconnect Association ow Disconnect
 *              Connection.
 *
 * The stwuctuwe is awwocated by the WWDD whenevew a WS Wequest is weceived
 * fwom the FC wink. The addwess of the stwuctuwe is passed to the nvmet-fc
 * ow nvme-fc wayew via the xxx_wcv_ws_weq() twanspowt woutines.
 *
 * The addwess of the stwuctuwe is to be passed back to the WWDD
 * when the wesponse is to be twansmit. The WWDD wiww use the addwess to
 * map back to the WWDD exchange stwuctuwe which maintains infowmation such
 * the wemote N_Powt that sent the WS as weww as any FC exchange context.
 * Upon compwetion of the WS wesponse twansmit, the WWDD wiww pass the
 * addwess of the stwuctuwe back to the twanspowt WS wsp done() woutine,
 * awwowing the twanspowt wewease dma wesouwces. Upon compwetion of
 * the done() woutine, no fuwthew access to the stwuctuwe wiww be made by
 * the twanspowt and the WWDD can de-awwocate the stwuctuwe.
 *
 * Fiewd initiawization:
 *   At the time of the xxx_wcv_ws_weq() caww, thewe is no content that
 *     is vawid in the stwuctuwe.
 *
 *   When the stwuctuwe is used fow the WWDD->xmt_ws_wsp() caww, the
 *     twanspowt wayew wiww fuwwy set the fiewds in owdew to specify the
 *     wesponse paywoad buffew and its wength as weww as the done woutine
 *     to be cawwed upon compwetion of the twansmit.  The twanspowt wayew
 *     wiww awso set a pwivate pointew fow its own use in the done woutine.
 *
 * Vawues set by the twanspowt wayew pwiow to cawwing the WWDD xmt_ws_wsp
 * entwypoint:
 * @wspbuf:   pointew to the WS wesponse buffew
 * @wspdma:   PCI DMA addwess of the WS wesponse buffew
 * @wspwen:   Wength, in bytes, of the WS wesponse buffew
 * @done:     The cawwback woutine the WWDD is to invoke upon compwetion of
 *            twansmitting the WS wesponse. weq awgument is the pointew to
 *            the owiginaw ws wequest.
 * @nvme_fc_pwivate:  pointew to an intewnaw twanspowt-specific stwuctuwe
 *            used as pawt of the twanspowt done() pwocessing. The WWDD is
 *            not to access this pointew.
 */
stwuct nvmefc_ws_wsp {
	void		*wspbuf;
	dma_addw_t	wspdma;
	u16		wspwen;

	void (*done)(stwuct nvmefc_ws_wsp *wsp);
	void		*nvme_fc_pwivate;	/* WWDD is not to access !! */
};



/*
 * **********************  WWDD FC-NVME Host API ********************
 *
 *  Fow FC WWDD's that awe the NVME Host wowe.
 *
 * ******************************************************************
 */


/**
 * stwuct nvme_fc_powt_info - powt-specific ids and FC connection-specific
 *                            data ewement used duwing NVME Host wowe
 *                            wegistwations
 *
 * Static fiewds descwibing the powt being wegistewed:
 * @node_name: FC WWNN fow the powt
 * @powt_name: FC WWPN fow the powt
 * @powt_wowe: What NVME wowes awe suppowted (see FC_POWT_WOWE_xxx)
 * @dev_woss_tmo: maximum deway fow weconnects to an association on
 *             this device. Used onwy on a wemotepowt.
 *
 * Initiawization vawues fow dynamic powt fiewds:
 * @powt_id:      FC N_Powt_ID cuwwentwy assigned the powt. Uppew 8 bits must
 *                be set to 0.
 */
stwuct nvme_fc_powt_info {
	u64			node_name;
	u64			powt_name;
	u32			powt_wowe;
	u32			powt_id;
	u32			dev_woss_tmo;
};

enum nvmefc_fcp_datadiw {
	NVMEFC_FCP_NODATA,	/* paywoad_wength and sg_cnt wiww be zewo */
	NVMEFC_FCP_WWITE,
	NVMEFC_FCP_WEAD,
};


/**
 * stwuct nvmefc_fcp_weq - Wequest stwuctuwe passed fwom NVME-FC twanspowt
 *                         to WWDD in owdew to pewfowm a NVME FCP IO opewation.
 *
 * Vawues set by the NVME-FC wayew pwiow to cawwing the WWDD fcp_io
 * entwypoint.
 * @cmdaddw:   pointew to the FCP CMD IU buffew
 * @wspaddw:   pointew to the FCP WSP IU buffew
 * @cmddma:    PCI DMA addwess of the FCP CMD IU buffew
 * @wspdma:    PCI DMA addwess of the FCP WSP IU buffew
 * @cmdwen:    Wength, in bytes, of the FCP CMD IU buffew
 * @wspwen:    Wength, in bytes, of the FCP WSP IU buffew
 * @paywoad_wength: Wength of DATA_IN ow DATA_OUT paywoad data to twansfew
 * @sg_tabwe:  scattew/gathew stwuctuwe fow paywoad data
 * @fiwst_sgw: memowy fow 1st scattew/gathew wist segment fow paywoad data
 * @sg_cnt:    numbew of ewements in the scattew/gathew wist
 * @io_diw:    diwection of the FCP wequest (see NVMEFC_FCP_xxx)
 * @done:      The cawwback woutine the WWDD is to invoke upon compwetion of
 *             the FCP opewation. weq awgument is the pointew to the owiginaw
 *             FCP IO opewation.
 * @pwivate:   pointew to memowy awwocated awongside the FCP opewation
 *             wequest stwuctuwe that is specificawwy fow the WWDD to use
 *             whiwe pwocessing the opewation. The wength of the buffew
 *             cowwesponds to the fcpwqst_pwiv_sz vawue specified in the
 *             nvme_fc_powt_tempwate suppwied by the WWDD.
 * @sqid:      The nvme SQID the command is being issued on
 *
 * Vawues set by the WWDD indicating compwetion status of the FCP opewation.
 * Must be set pwiow to cawwing the done() cawwback.
 * @wcv_wspwen: wength, in bytes, of the FCP WSP IU weceived.
 * @twansfewwed_wength: amount of paywoad data, in bytes, that wewe
 *             twansfewwed. Shouwd equaw paywoad_wength on success.
 * @status:    Compwetion status of the FCP opewation. must be 0 upon success,
 *             negative ewwno vawue upon faiwuwe (ex: -EIO). Note: this is
 *             NOT a wefwection of the NVME CQE compwetion status. Onwy the
 *             status of the FCP opewation at the NVME-FC wevew.
 */
stwuct nvmefc_fcp_weq {
	void			*cmdaddw;
	void			*wspaddw;
	dma_addw_t		cmddma;
	dma_addw_t		wspdma;
	u16			cmdwen;
	u16			wspwen;

	u32			paywoad_wength;
	stwuct sg_tabwe		sg_tabwe;
	stwuct scattewwist	*fiwst_sgw;
	int			sg_cnt;
	enum nvmefc_fcp_datadiw	io_diw;

	void (*done)(stwuct nvmefc_fcp_weq *weq);

	void			*pwivate;

	__we16			sqid;

	u16			wcv_wspwen;
	u32			twansfewwed_wength;
	u32			status;
} __awigned(sizeof(u64));	/* awignment fow othew things awwoc'd with */


/*
 * Diwect copy of fc_powt_state enum. Fow watew mewging
 */
enum nvme_fc_obj_state {
	FC_OBJSTATE_UNKNOWN,
	FC_OBJSTATE_NOTPWESENT,
	FC_OBJSTATE_ONWINE,
	FC_OBJSTATE_OFFWINE,		/* Usew has taken Powt Offwine */
	FC_OBJSTATE_BWOCKED,
	FC_OBJSTATE_BYPASSED,
	FC_OBJSTATE_DIAGNOSTICS,
	FC_OBJSTATE_WINKDOWN,
	FC_OBJSTATE_EWWOW,
	FC_OBJSTATE_WOOPBACK,
	FC_OBJSTATE_DEWETED,
};


/**
 * stwuct nvme_fc_wocaw_powt - stwuctuwe used between NVME-FC twanspowt and
 *                 a WWDD to wefewence a wocaw NVME host powt.
 *                 Awwocated/cweated by the nvme_fc_wegistew_wocawpowt()
 *                 twanspowt intewface.
 *
 * Fiewds with static vawues fow the powt. Initiawized by the
 * powt_info stwuct suppwied to the wegistwation caww.
 * @powt_num:  NVME-FC twanspowt host powt numbew
 * @powt_wowe: NVME wowes awe suppowted on the powt (see FC_POWT_WOWE_xxx)
 * @node_name: FC WWNN fow the powt
 * @powt_name: FC WWPN fow the powt
 * @pwivate:   pointew to memowy awwocated awongside the wocaw powt
 *             stwuctuwe that is specificawwy fow the WWDD to use.
 *             The wength of the buffew cowwesponds to the wocaw_pwiv_sz
 *             vawue specified in the nvme_fc_powt_tempwate suppwied by
 *             the WWDD.
 * @dev_woss_tmo: maximum deway fow weconnects to an association on
 *             this device. To modify, wwdd must caww
 *             nvme_fc_set_wemotepowt_devwoss().
 *
 * Fiewds with dynamic vawues. Vawues may change base on wink state. WWDD
 * may wefewence fiewds diwectwy to change them. Initiawized by the
 * powt_info stwuct suppwied to the wegistwation caww.
 * @powt_id:      FC N_Powt_ID cuwwentwy assigned the powt. Uppew 8 bits must
 *                be set to 0.
 * @powt_state:   Opewationaw state of the powt.
 */
stwuct nvme_fc_wocaw_powt {
	/* static/wead-onwy fiewds */
	u32 powt_num;
	u32 powt_wowe;
	u64 node_name;
	u64 powt_name;

	void *pwivate;

	/* dynamic fiewds */
	u32 powt_id;
	enum nvme_fc_obj_state powt_state;
} __awigned(sizeof(u64));	/* awignment fow othew things awwoc'd with */


/**
 * stwuct nvme_fc_wemote_powt - stwuctuwe used between NVME-FC twanspowt and
 *                 a WWDD to wefewence a wemote NVME subsystem powt.
 *                 Awwocated/cweated by the nvme_fc_wegistew_wemotepowt()
 *                 twanspowt intewface.
 *
 * Fiewds with static vawues fow the powt. Initiawized by the
 * powt_info stwuct suppwied to the wegistwation caww.
 * @powt_num:  NVME-FC twanspowt wemote subsystem powt numbew
 * @powt_wowe: NVME wowes awe suppowted on the powt (see FC_POWT_WOWE_xxx)
 * @node_name: FC WWNN fow the powt
 * @powt_name: FC WWPN fow the powt
 * @wocawpowt: pointew to the NVME-FC wocaw host powt the subsystem is
 *             connected to.
 * @pwivate:   pointew to memowy awwocated awongside the wemote powt
 *             stwuctuwe that is specificawwy fow the WWDD to use.
 *             The wength of the buffew cowwesponds to the wemote_pwiv_sz
 *             vawue specified in the nvme_fc_powt_tempwate suppwied by
 *             the WWDD.
 *
 * Fiewds with dynamic vawues. Vawues may change base on wink ow wogin
 * state. WWDD may wefewence fiewds diwectwy to change them. Initiawized by
 * the powt_info stwuct suppwied to the wegistwation caww.
 * @powt_id:      FC N_Powt_ID cuwwentwy assigned the powt. Uppew 8 bits must
 *                be set to 0.
 * @powt_state:   Opewationaw state of the wemote powt. Vawid vawues awe
 *                ONWINE ow UNKNOWN.
 */
stwuct nvme_fc_wemote_powt {
	/* static fiewds */
	u32 powt_num;
	u32 powt_wowe;
	u64 node_name;
	u64 powt_name;
	stwuct nvme_fc_wocaw_powt *wocawpowt;
	void *pwivate;
	u32 dev_woss_tmo;

	/* dynamic fiewds */
	u32 powt_id;
	enum nvme_fc_obj_state powt_state;
} __awigned(sizeof(u64));	/* awignment fow othew things awwoc'd with */


/**
 * stwuct nvme_fc_powt_tempwate - stwuctuwe containing static entwypoints and
 *                 opewationaw pawametews fow an WWDD that suppowts NVME host
 *                 behaviow. Passed by wefewence in powt wegistwations.
 *                 NVME-FC twanspowt wemembews tempwate wefewence and may
 *                 access it duwing wuntime opewation.
 *
 * Host/Initiatow Twanspowt Entwypoints/Pawametews:
 *
 * @wocawpowt_dewete:  The WWDD initiates dewetion of a wocawpowt via
 *       nvme_fc_dewegistew_wocawpowt(). Howevew, the teawdown is
 *       asynchwonous. This woutine is cawwed upon the compwetion of the
 *       teawdown to infowm the WWDD that the wocawpowt has been deweted.
 *       Entwypoint is Mandatowy.
 *
 * @wemotepowt_dewete:  The WWDD initiates dewetion of a wemotepowt via
 *       nvme_fc_dewegistew_wemotepowt(). Howevew, the teawdown is
 *       asynchwonous. This woutine is cawwed upon the compwetion of the
 *       teawdown to infowm the WWDD that the wemotepowt has been deweted.
 *       Entwypoint is Mandatowy.
 *
 * @cweate_queue:  Upon cweating a host<->contwowwew association, queues awe
 *       cweated such that they can be affinitized to cpus/cowes. This
 *       cawwback into the WWDD to notify that a contwowwew queue is being
 *       cweated.  The WWDD may choose to awwocate an associated hw queue
 *       ow map it onto a shawed hw queue. Upon wetuwn fwom the caww, the
 *       WWDD specifies a handwe that wiww be given back to it fow any
 *       command that is posted to the contwowwew queue.  The handwe can
 *       be used by the WWDD to map quickwy to the pwopew hw queue fow
 *       command execution.  The mask of cpu's that wiww map to this queue
 *       at the bwock-wevew is awso passed in. The WWDD shouwd use the
 *       queue id and/ow cpu masks to ensuwe pwopew affinitization of the
 *       contwowwew queue to the hw queue.
 *       Entwypoint is Optionaw.
 *
 * @dewete_queue:  This is the invewse of the cwete_queue. Duwing
 *       host<->contwowwew association teawdown, this woutine is cawwed
 *       when a contwowwew queue is being tewminated. Any association with
 *       a hw queue shouwd be tewmined. If thewe is a unique hw queue, the
 *       hw queue shouwd be town down.
 *       Entwypoint is Optionaw.
 *
 * @poww_queue:  Cawwed to poww fow the compwetion of an io on a bwk queue.
 *       Entwypoint is Optionaw.
 *
 * @ws_weq:  Cawwed to issue a FC-NVME FC-4 WS sewvice wequest.
 *       The nvme_fc_ws_weq stwuctuwe wiww fuwwy descwibe the buffews fow
 *       the wequest paywoad and whewe to pwace the wesponse paywoad. The
 *       WWDD is to awwocate an exchange, issue the WS wequest, obtain the
 *       WS wesponse, and caww the "done" woutine specified in the wequest
 *       stwuctuwe (awgument to done is the ws wequest stwuctuwe itsewf).
 *       Entwypoint is Mandatowy.
 *
 * @fcp_io:  cawwed to issue a FC-NVME I/O wequest.  The I/O may be fow
 *       an admin queue ow an i/o queue.  The nvmefc_fcp_weq stwuctuwe wiww
 *       fuwwy descwibe the io: the buffew containing the FC-NVME CMD IU
 *       (which contains the SQE), the sg wist fow the paywoad if appwicabwe,
 *       and the buffew to pwace the FC-NVME WSP IU into.  The WWDD wiww
 *       compwete the i/o, indicating the amount of data twansfewwed ow
 *       any twanspowt ewwow, and caww the "done" woutine specified in the
 *       wequest stwuctuwe (awgument to done is the fcp wequest stwuctuwe
 *       itsewf).
 *       Entwypoint is Mandatowy.
 *
 * @ws_abowt: cawwed to wequest the WWDD to abowt the indicated ws wequest.
 *       The caww may wetuwn befowe the abowt has compweted. Aftew abowting
 *       the wequest, the WWDD must stiww caww the ws wequest done woutine
 *       indicating an FC twanspowt Abowted status.
 *       Entwypoint is Mandatowy.
 *
 * @fcp_abowt: cawwed to wequest the WWDD to abowt the indicated fcp wequest.
 *       The caww may wetuwn befowe the abowt has compweted. Aftew abowting
 *       the wequest, the WWDD must stiww caww the fcp wequest done woutine
 *       indicating an FC twanspowt Abowted status.
 *       Entwypoint is Mandatowy.
 *
 * @xmt_ws_wsp:  Cawwed to twansmit the wesponse to a FC-NVME FC-4 WS sewvice.
 *       The nvmefc_ws_wsp stwuctuwe is the same WWDD-suppwied exchange
 *       stwuctuwe specified in the nvme_fc_wcv_ws_weq() caww made when
 *       the WS wequest was weceived. The stwuctuwe wiww fuwwy descwibe
 *       the buffews fow the wesponse paywoad and the dma addwess of the
 *       paywoad. The WWDD is to twansmit the wesponse (ow wetuwn a
 *       non-zewo ewwno status), and upon compwetion of the twansmit, caww
 *       the "done" woutine specified in the nvmefc_ws_wsp stwuctuwe
 *       (awgument to done is the addwess of the nvmefc_ws_wsp stwuctuwe
 *       itsewf). Upon the compwetion of the done woutine, the WWDD shaww
 *       considew the WS handwing compwete and the nvmefc_ws_wsp stwuctuwe
 *       may be fweed/weweased.
 *       Entwypoint is mandatowy if the WWDD cawws the nvme_fc_wcv_ws_weq()
 *       entwypoint.
 *
 * @max_hw_queues:  indicates the maximum numbew of hw queues the WWDD
 *       suppowts fow cpu affinitization.
 *       Vawue is Mandatowy. Must be at weast 1.
 *
 * @max_sgw_segments:  indicates the maximum numbew of sgw segments suppowted
 *       by the WWDD
 *       Vawue is Mandatowy. Must be at weast 1. Wecommend at weast 256.
 *
 * @max_dif_sgw_segments:  indicates the maximum numbew of sgw segments
 *       suppowted by the WWDD fow DIF opewations.
 *       Vawue is Mandatowy. Must be at weast 1. Wecommend at weast 256.
 *
 * @dma_boundawy:  indicates the dma addwess boundawy whewe dma mappings
 *       wiww be spwit acwoss.
 *       Vawue is Mandatowy. Typicaw vawue is 0xFFFFFFFF to spwit acwoss
 *       4Gig addwess boundawys
 *
 * @wocaw_pwiv_sz: The WWDD sets this fiewd to the amount of additionaw
 *       memowy that it wouwd wike fc nvme wayew to awwocate on the WWDD's
 *       behawf whenevew a wocawpowt is awwocated.  The additionaw memowy
 *       awea sowewy fow the of the WWDD and its wocation is specified by
 *       the wocawpowt->pwivate pointew.
 *       Vawue is Mandatowy. Awwowed to be zewo.
 *
 * @wemote_pwiv_sz: The WWDD sets this fiewd to the amount of additionaw
 *       memowy that it wouwd wike fc nvme wayew to awwocate on the WWDD's
 *       behawf whenevew a wemotepowt is awwocated.  The additionaw memowy
 *       awea sowewy fow the of the WWDD and its wocation is specified by
 *       the wemotepowt->pwivate pointew.
 *       Vawue is Mandatowy. Awwowed to be zewo.
 *
 * @wswqst_pwiv_sz: The WWDD sets this fiewd to the amount of additionaw
 *       memowy that it wouwd wike fc nvme wayew to awwocate on the WWDD's
 *       behawf whenevew a ws wequest stwuctuwe is awwocated. The additionaw
 *       memowy awea is sowewy fow use by the WWDD and its wocation is
 *       specified by the ws_wequest->pwivate pointew.
 *       Vawue is Mandatowy. Awwowed to be zewo.
 *
 * @fcpwqst_pwiv_sz: The WWDD sets this fiewd to the amount of additionaw
 *       memowy that it wouwd wike fc nvme wayew to awwocate on the WWDD's
 *       behawf whenevew a fcp wequest stwuctuwe is awwocated. The additionaw
 *       memowy awea sowewy fow the of the WWDD and its wocation is
 *       specified by the fcp_wequest->pwivate pointew.
 *       Vawue is Mandatowy. Awwowed to be zewo.
 */
stwuct nvme_fc_powt_tempwate {
	/* initiatow-based functions */
	void	(*wocawpowt_dewete)(stwuct nvme_fc_wocaw_powt *);
	void	(*wemotepowt_dewete)(stwuct nvme_fc_wemote_powt *);
	int	(*cweate_queue)(stwuct nvme_fc_wocaw_powt *,
				unsigned int qidx, u16 qsize,
				void **handwe);
	void	(*dewete_queue)(stwuct nvme_fc_wocaw_powt *,
				unsigned int qidx, void *handwe);
	int	(*ws_weq)(stwuct nvme_fc_wocaw_powt *,
				stwuct nvme_fc_wemote_powt *,
				stwuct nvmefc_ws_weq *);
	int	(*fcp_io)(stwuct nvme_fc_wocaw_powt *,
				stwuct nvme_fc_wemote_powt *,
				void *hw_queue_handwe,
				stwuct nvmefc_fcp_weq *);
	void	(*ws_abowt)(stwuct nvme_fc_wocaw_powt *,
				stwuct nvme_fc_wemote_powt *,
				stwuct nvmefc_ws_weq *);
	void	(*fcp_abowt)(stwuct nvme_fc_wocaw_powt *,
				stwuct nvme_fc_wemote_powt *,
				void *hw_queue_handwe,
				stwuct nvmefc_fcp_weq *);
	int	(*xmt_ws_wsp)(stwuct nvme_fc_wocaw_powt *wocawpowt,
				stwuct nvme_fc_wemote_powt *wpowt,
				stwuct nvmefc_ws_wsp *ws_wsp);
	void	(*map_queues)(stwuct nvme_fc_wocaw_powt *wocawpowt,
			      stwuct bwk_mq_queue_map *map);

	u32	max_hw_queues;
	u16	max_sgw_segments;
	u16	max_dif_sgw_segments;
	u64	dma_boundawy;

	/* sizes of additionaw pwivate data fow data stwuctuwes */
	u32	wocaw_pwiv_sz;
	u32	wemote_pwiv_sz;
	u32	wswqst_pwiv_sz;
	u32	fcpwqst_pwiv_sz;
};


/*
 * Initiatow/Host functions
 */

int nvme_fc_wegistew_wocawpowt(stwuct nvme_fc_powt_info *pinfo,
			stwuct nvme_fc_powt_tempwate *tempwate,
			stwuct device *dev,
			stwuct nvme_fc_wocaw_powt **wpowt_p);

int nvme_fc_unwegistew_wocawpowt(stwuct nvme_fc_wocaw_powt *wocawpowt);

int nvme_fc_wegistew_wemotepowt(stwuct nvme_fc_wocaw_powt *wocawpowt,
			stwuct nvme_fc_powt_info *pinfo,
			stwuct nvme_fc_wemote_powt **wpowt_p);

int nvme_fc_unwegistew_wemotepowt(stwuct nvme_fc_wemote_powt *wemotepowt);

void nvme_fc_wescan_wemotepowt(stwuct nvme_fc_wemote_powt *wemotepowt);

int nvme_fc_set_wemotepowt_devwoss(stwuct nvme_fc_wemote_powt *wemotepowt,
			u32 dev_woss_tmo);

/*
 * Woutine cawwed to pass a NVME-FC WS wequest, weceived by the wwdd,
 * to the nvme-fc twanspowt.
 *
 * If the wetuwn vawue is zewo: the WS was successfuwwy accepted by the
 *   twanspowt.
 * If the wetuwn vawue is non-zewo: the twanspowt has not accepted the
 *   WS. The wwdd shouwd ABTS-WS the WS.
 *
 * Note: if the WWDD weceives and ABTS fow the WS pwiow to the twanspowt
 * cawwing the ops->xmt_ws_wsp() woutine to twansmit a wesponse, the WWDD
 * shaww mawk the WS as abowted, and when the xmt_ws_wsp() is cawwed: the
 * wesponse shaww not be twansmit and the stwuct nvmefc_ws_wsp() done
 * woutine shaww be cawwed.  The WWDD may twansmit the ABTS wesponse as
 * soon as the WS was mawked ow can deway untiw the xmt_ws_wsp() caww is
 * made.
 * Note: if an WCV WS was successfuwwy posted to the twanspowt and the
 * wemotepowt is then unwegistewed befowe xmt_ws_wsp() was cawwed fow
 * the wswsp stwuctuwe, the twanspowt wiww stiww caww xmt_ws_wsp()
 * aftewwawd to cweanup the outstanding wswsp stwuctuwe. The WWDD shouwd
 * noop the twansmission of the wsp and caww the wswsp->done() woutine
 * to awwow the wswsp stwuctuwe to be weweased.
 */
int nvme_fc_wcv_ws_weq(stwuct nvme_fc_wemote_powt *wemotepowt,
			stwuct nvmefc_ws_wsp *wswsp,
			void *wsweqbuf, u32 wsweqbuf_wen);


/*
 * Woutine cawwed to get the appid fiewd associated with wequest by the wwdd
 *
 * If the wetuwn vawue is NUWW : the usew/wibviwt has not set the appid to VM
 * If the wetuwn vawue is non-zewo: Wetuwns the appid associated with VM
 *
 * @weq: IO wequest fwom nvme fc to dwivew
 */
chaw *nvme_fc_io_getuuid(stwuct nvmefc_fcp_weq *weq);

/*
 * ***************  WWDD FC-NVME Tawget/Subsystem API ***************
 *
 *  Fow FC WWDD's that awe the NVME Subsystem wowe
 *
 * ******************************************************************
 */

/**
 * stwuct nvmet_fc_powt_info - powt-specific ids and FC connection-specific
 *                             data ewement used duwing NVME Subsystem wowe
 *                             wegistwations
 *
 * Static fiewds descwibing the powt being wegistewed:
 * @node_name: FC WWNN fow the powt
 * @powt_name: FC WWPN fow the powt
 *
 * Initiawization vawues fow dynamic powt fiewds:
 * @powt_id:      FC N_Powt_ID cuwwentwy assigned the powt. Uppew 8 bits must
 *                be set to 0.
 */
stwuct nvmet_fc_powt_info {
	u64			node_name;
	u64			powt_name;
	u32			powt_id;
};


/* Opewations that NVME-FC wayew may wequest the WWDD to pewfowm fow FCP */
enum {
	NVMET_FCOP_WEADDATA	= 1,	/* xmt data to initiatow */
	NVMET_FCOP_WWITEDATA	= 2,	/* xmt data fwom initiatow */
	NVMET_FCOP_WEADDATA_WSP	= 3,	/* xmt data to initiatow and send
					 * wsp as weww
					 */
	NVMET_FCOP_WSP		= 4,	/* send wsp fwame */
};

/**
 * stwuct nvmefc_tgt_fcp_weq - Stwuctuwe used between WWDD and NVMET-FC
 *                            wayew to wepwesent the exchange context and
 *                            the specific FC-NVME IU opewation(s) to pewfowm
 *                            fow a FC-NVME FCP IO.
 *
 * Stwuctuwe used between WWDD and nvmet-fc wayew to wepwesent the exchange
 * context fow a FC-NVME FCP I/O opewation (e.g. a nvme sqe, the sqe-wewated
 * memowy twansfews, and its assocated cqe twansfew).
 *
 * The stwuctuwe is awwocated by the WWDD whenevew a FCP CMD IU is weceived
 * fwom the FC wink. The addwess of the stwuctuwe is passed to the nvmet-fc
 * wayew via the nvmet_fc_wcv_fcp_weq() caww. The addwess of the stwuctuwe
 * wiww be passed back to the WWDD fow the data opewations and twansmit of
 * the wesponse. The WWDD is to use the addwess to map back to the WWDD
 * exchange stwuctuwe which maintains infowmation such as the tawgetpowt
 * the FCP I/O was weceived on, the wemote FC NVME initiatow that sent the
 * FCP I/O, and any FC exchange context.  Upon compwetion of the FCP tawget
 * opewation, the addwess of the stwuctuwe wiww be passed back to the FCP
 * op done() woutine, awwowing the nvmet-fc wayew to wewease dma wesouwces.
 * Upon compwetion of the done() woutine fow eithew WSP ow ABOWT ops, no
 * fuwthew access wiww be made by the nvmet-fc wayew and the WWDD can
 * de-awwocate the stwuctuwe.
 *
 * Fiewd initiawization:
 *   At the time of the nvmet_fc_wcv_fcp_weq() caww, thewe is no content that
 *     is vawid in the stwuctuwe.
 *
 *   When the stwuctuwe is used fow an FCP tawget opewation, the nvmet-fc
 *     wayew wiww fuwwy set the fiewds in owdew to specify the scattewgathew
 *     wist, the twansfew wength, as weww as the done woutine to be cawwed
 *     upon compewetion of the opewation.  The nvmet-fc wayew wiww awso set a
 *     pwivate pointew fow its own use in the done woutine.
 *
 * Vawues set by the NVMET-FC wayew pwiow to cawwing the WWDD fcp_op
 * entwypoint.
 * @op:       Indicates the FCP IU opewation to pewfowm (see NVMET_FCOP_xxx)
 * @hwqid:    Specifies the hw queue index (0..N-1, whewe N is the
 *            max_hw_queues vawue fwom the WWD's nvmet_fc_tawget_tempwate)
 *            that the opewation is to use.
 * @offset:   Indicates the DATA_OUT/DATA_IN paywoad offset to be twanfewwed.
 *            Fiewd is onwy vawid on WWITEDATA, WEADDATA, ow WEADDATA_WSP ops.
 * @timeout:  amount of time, in seconds, to wait fow a wesponse fwom the NVME
 *            host. A vawue of 0 is an infinite wait.
 *            Vawid onwy fow the fowwowing ops:
 *              WWITEDATA: caps the wait fow data weception
 *              WEADDATA_WSP & WSP: caps wait fow FCP_CONF weception (if used)
 * @twansfew_wength: the wength, in bytes, of the DATA_OUT ow DATA_IN paywoad
 *            that is to be twansfewwed.
 *            Vawid onwy fow the WWITEDATA, WEADDATA, ow WEADDATA_WSP ops.
 * @ba_wjt:   Contains the BA_WJT paywoad that is to be twansfewwed.
 *            Vawid onwy fow the NVMET_FCOP_BA_WJT op.
 * @sg:       Scattew/gathew wist fow the DATA_OUT/DATA_IN paywoad data.
 *            Vawid onwy fow the WWITEDATA, WEADDATA, ow WEADDATA_WSP ops.
 * @sg_cnt:   Numbew of vawid entwies in the scattew/gathew wist.
 *            Vawid onwy fow the WWITEDATA, WEADDATA, ow WEADDATA_WSP ops.
 * @wspaddw:  pointew to the FCP WSP IU buffew to be twansmit
 *            Used by WSP and WEADDATA_WSP ops
 * @wspdma:   PCI DMA addwess of the FCP WSP IU buffew
 *            Used by WSP and WEADDATA_WSP ops
 * @wspwen:   Wength, in bytes, of the FCP WSP IU buffew
 *            Used by WSP and WEADDATA_WSP ops
 * @done:     The cawwback woutine the WWDD is to invoke upon compwetion of
 *            the opewation. weq awgument is the pointew to the owiginaw
 *            FCP subsystem op wequest.
 * @nvmet_fc_pwivate:  pointew to an intewnaw NVMET-FC wayew stwuctuwe used
 *            as pawt of the NVMET-FC pwocessing. The WWDD is not to
 *            wefewence this fiewd.
 *
 * Vawues set by the WWDD indicating compwetion status of the FCP opewation.
 * Must be set pwiow to cawwing the done() cawwback.
 * @twansfewwed_wength: amount of DATA_OUT paywoad data weceived by a
 *            WWITEDATA opewation. If not a WWITEDATA opewation, vawue must
 *            be set to 0. Shouwd equaw twansfew_wength on success.
 * @fcp_ewwow: status of the FCP opewation. Must be 0 on success; on faiwuwe
 *            must be a NVME_SC_FC_xxxx vawue.
 */
stwuct nvmefc_tgt_fcp_weq {
	u8			op;
	u16			hwqid;
	u32			offset;
	u32			timeout;
	u32			twansfew_wength;
	stwuct fc_ba_wjt	ba_wjt;
	stwuct scattewwist	*sg;
	int			sg_cnt;
	void			*wspaddw;
	dma_addw_t		wspdma;
	u16			wspwen;

	void (*done)(stwuct nvmefc_tgt_fcp_weq *);

	void *nvmet_fc_pwivate;		/* WWDD is not to access !! */

	u32			twansfewwed_wength;
	int			fcp_ewwow;
};


/* Tawget Featuwes (Bit fiewds) WWDD suppowts */
enum {
	NVMET_FCTGTFEAT_WEADDATA_WSP = (1 << 0),
		/* Bit 0: suppowts the NVMET_FCPOP_WEADDATA_WSP op, which
		 * sends (the wast) Wead Data sequence fowwowed by the WSP
		 * sequence in one WWDD opewation. Ewwows duwing Data
		 * sequence twansmit must not awwow WSP sequence to be sent.
		 */
};


/**
 * stwuct nvmet_fc_tawget_powt - stwuctuwe used between NVME-FC twanspowt and
 *                 a WWDD to wefewence a wocaw NVME subsystem powt.
 *                 Awwocated/cweated by the nvme_fc_wegistew_tawgetpowt()
 *                 twanspowt intewface.
 *
 * Fiewds with static vawues fow the powt. Initiawized by the
 * powt_info stwuct suppwied to the wegistwation caww.
 * @powt_num:  NVME-FC twanspowt subsystem powt numbew
 * @node_name: FC WWNN fow the powt
 * @powt_name: FC WWPN fow the powt
 * @pwivate:   pointew to memowy awwocated awongside the wocaw powt
 *             stwuctuwe that is specificawwy fow the WWDD to use.
 *             The wength of the buffew cowwesponds to the tawget_pwiv_sz
 *             vawue specified in the nvme_fc_tawget_tempwate suppwied by
 *             the WWDD.
 *
 * Fiewds with dynamic vawues. Vawues may change base on wink state. WWDD
 * may wefewence fiewds diwectwy to change them. Initiawized by the
 * powt_info stwuct suppwied to the wegistwation caww.
 * @powt_id:      FC N_Powt_ID cuwwentwy assigned the powt. Uppew 8 bits must
 *                be set to 0.
 * @powt_state:   Opewationaw state of the powt.
 */
stwuct nvmet_fc_tawget_powt {
	/* static/wead-onwy fiewds */
	u32 powt_num;
	u64 node_name;
	u64 powt_name;

	void *pwivate;

	/* dynamic fiewds */
	u32 powt_id;
	enum nvme_fc_obj_state powt_state;
} __awigned(sizeof(u64));	/* awignment fow othew things awwoc'd with */


/**
 * stwuct nvmet_fc_tawget_tempwate - stwuctuwe containing static entwypoints
 *                 and opewationaw pawametews fow an WWDD that suppowts NVME
 *                 subsystem behaviow. Passed by wefewence in powt
 *                 wegistwations. NVME-FC twanspowt wemembews tempwate
 *                 wefewence and may access it duwing wuntime opewation.
 *
 * Subsystem/Tawget Twanspowt Entwypoints/Pawametews:
 *
 * @tawgetpowt_dewete:  The WWDD initiates dewetion of a tawgetpowt via
 *       nvmet_fc_unwegistew_tawgetpowt(). Howevew, the teawdown is
 *       asynchwonous. This woutine is cawwed upon the compwetion of the
 *       teawdown to infowm the WWDD that the tawgetpowt has been deweted.
 *       Entwypoint is Mandatowy.
 *
 * @xmt_ws_wsp:  Cawwed to twansmit the wesponse to a FC-NVME FC-4 WS sewvice.
 *       The nvmefc_ws_wsp stwuctuwe is the same WWDD-suppwied exchange
 *       stwuctuwe specified in the nvmet_fc_wcv_ws_weq() caww made when
 *       the WS wequest was weceived. The stwuctuwe wiww fuwwy descwibe
 *       the buffews fow the wesponse paywoad and the dma addwess of the
 *       paywoad. The WWDD is to twansmit the wesponse (ow wetuwn a
 *       non-zewo ewwno status), and upon compwetion of the twansmit, caww
 *       the "done" woutine specified in the nvmefc_ws_wsp stwuctuwe
 *       (awgument to done is the addwess of the nvmefc_ws_wsp stwuctuwe
 *       itsewf). Upon the compwetion of the done() woutine, the WWDD shaww
 *       considew the WS handwing compwete and the nvmefc_ws_wsp stwuctuwe
 *       may be fweed/weweased.
 *       The twanspowt wiww awways caww the xmt_ws_wsp() woutine fow any
 *       WS weceived.
 *       Entwypoint is Mandatowy.
 *
 * @map_queues: This functions wets the dwivew expose the queue mapping
 *	 to the bwock wayew.
 *       Entwypoint is Optionaw.
 *
 * @fcp_op:  Cawwed to pewfowm a data twansfew ow twansmit a wesponse.
 *       The nvmefc_tgt_fcp_weq stwuctuwe is the same WWDD-suppwied
 *       exchange stwuctuwe specified in the nvmet_fc_wcv_fcp_weq() caww
 *       made when the FCP CMD IU was weceived. The op fiewd in the
 *       stwuctuwe shaww indicate the opewation fow the WWDD to pewfowm
 *       wewative to the io.
 *         NVMET_FCOP_WEADDATA opewation: the WWDD is to send the
 *           paywoad data (descwibed by sgwist) to the host in 1 ow
 *           mowe FC sequences (pwefewwabwy 1).  Note: the fc-nvme wayew
 *           may caww the WEADDATA opewation muwtipwe times fow wongew
 *           paywoads.
 *         NVMET_FCOP_WWITEDATA opewation: the WWDD is to weceive the
 *           paywoad data (descwibed by sgwist) fwom the host via 1 ow
 *           mowe FC sequences (pwefewwabwy 1). The WWDD is to genewate
 *           the XFEW_WDY IU(s) cowwesponding to the data being wequested.
 *           Note: the FC-NVME wayew may caww the WWITEDATA opewation
 *           muwtipwe times fow wongew paywoads.
 *         NVMET_FCOP_WEADDATA_WSP opewation: the WWDD is to send the
 *           paywoad data (descwibed by sgwist) to the host in 1 ow
 *           mowe FC sequences (pwefewwabwy 1). If an ewwow occuws duwing
 *           paywoad data twansmission, the WWDD is to set the
 *           nvmefc_tgt_fcp_weq fcp_ewwow and twansfewwed_wength fiewd, then
 *           considew the opewation compwete. On ewwow, the WWDD is to not
 *           twansmit the FCP_WSP iu. If aww paywoad data is twansfewwed
 *           successfuwwy, the WWDD is to update the nvmefc_tgt_fcp_weq
 *           twansfewwed_wength fiewd and may subsequentwy twansmit the
 *           FCP_WSP iu paywoad (descwibed by wspbuf, wspdma, wspwen).
 *           If FCP_CONF is suppowted, the WWDD is to await FCP_CONF
 *           weception to confiwm the WSP weception by the host. The WWDD
 *           may wetwamsit the FCP_WSP iu if necessawy pew FC-NVME. Upon
 *           twansmission of the FCP_WSP iu if FCP_CONF is not suppowted,
 *           ow upon success/faiwuwe of FCP_CONF if it is suppowted, the
 *           WWDD is to set the nvmefc_tgt_fcp_weq fcp_ewwow fiewd and
 *           considew the opewation compwete.
 *         NVMET_FCOP_WSP: the WWDD is to twansmit the FCP_WSP iu paywoad
 *           (descwibed by wspbuf, wspdma, wspwen). If FCP_CONF is
 *           suppowted, the WWDD is to await FCP_CONF weception to confiwm
 *           the WSP weception by the host. The WWDD may wetwamsit the
 *           FCP_WSP iu if FCP_CONF is not weceived pew FC-NVME. Upon
 *           twansmission of the FCP_WSP iu if FCP_CONF is not suppowted,
 *           ow upon success/faiwuwe of FCP_CONF if it is suppowted, the
 *           WWDD is to set the nvmefc_tgt_fcp_weq fcp_ewwow fiewd and
 *           considew the opewation compwete.
 *       Upon compweting the indicated opewation, the WWDD is to set the
 *       status fiewds fow the opewation (twanfewwed_wength and fcp_ewwow
 *       status) in the wequest, then caww the "done" woutine
 *       indicated in the fcp wequest. Aftew the opewation compwetes,
 *       wegawdwess of whethew the FCP_WSP iu was successfuwwy twansmit,
 *       the WWDD-suppwied exchange stwuctuwe must wemain vawid untiw the
 *       twanspowt cawws the fcp_weq_wewease() cawwback to wetuwn ownewship
 *       of the exchange stwuctuwe back to the WWDD so that it may be used
 *       fow anothew fcp command.
 *       Note: when cawwing the done woutine fow WEADDATA ow WWITEDATA
 *       opewations, the fc-nvme wayew may immediate convewt, in the same
 *       thwead and befowe wetuwning to the WWDD, the fcp opewation to
 *       the next opewation fow the fcp io and caww the WWDDs fcp_op
 *       caww again. If fiewds in the fcp wequest awe to be accessed post
 *       the done caww, the WWDD shouwd save theiw vawues pwiow to cawwing
 *       the done woutine, and inspect the save vawues aftew the done
 *       woutine.
 *       Wetuwns 0 on success, -<ewwno> on faiwuwe (Ex: -EIO)
 *       Entwypoint is Mandatowy.
 *
 * @fcp_abowt:  Cawwed by the twanspowt to abowt an active command.
 *       The command may be in-between opewations (nothing active in WWDD)
 *       ow may have an active WWITEDATA opewation pending. The WWDD is to
 *       initiate the ABTS pwocess fow the command and wetuwn fwom the
 *       cawwback. The ABTS does not need to be compwete on the command.
 *       The fcp_abowt cawwback inhewentwy cannot faiw. Aftew the
 *       fcp_abowt() cawwback compwetes, the twanspowt wiww wait fow any
 *       outstanding opewation (if thewe was one) to compwete, then wiww
 *       caww the fcp_weq_wewease() cawwback to wetuwn the command's
 *       exchange context back to the WWDD.
 *       Entwypoint is Mandatowy.
 *
 * @fcp_weq_wewease:  Cawwed by the twanspowt to wetuwn a nvmefc_tgt_fcp_weq
 *       to the WWDD aftew aww opewations on the fcp opewation awe compwete.
 *       This may be due to the command compweting ow upon compwetion of
 *       abowt cweanup.
 *       Entwypoint is Mandatowy.
 *
 * @defew_wcv:  Cawwed by the twanspowt to signaw the WWWD that it has
 *       begun pwocessing of a pweviouswy weceived NVME CMD IU. The WWDD
 *       is now fwee to we-use the wcv buffew associated with the
 *       nvmefc_tgt_fcp_weq.
 *       Entwypoint is Optionaw.
 *
 * @discovewy_event:  Cawwed by the twanspowt to genewate an WSCN
 *       change notifications to NVME initiatows. The WSCN notifications
 *       shouwd cause the initiatow to wescan the discovewy contwowwew
 *       on the tawgetpowt.
 *
 * @ws_weq:  Cawwed to issue a FC-NVME FC-4 WS sewvice wequest.
 *       The nvme_fc_ws_weq stwuctuwe wiww fuwwy descwibe the buffews fow
 *       the wequest paywoad and whewe to pwace the wesponse paywoad.
 *       The tawgetpowt that is to issue the WS wequest is identified by
 *       the tawgetpowt awgument.  The wemote powt that is to weceive the
 *       WS wequest is identified by the hosthandwe awgument. The nvmet-fc
 *       twanspowt is onwy awwowed to issue FC-NVME WS's on behawf of an
 *       association that was cweated pwiow by a Cweate Association WS.
 *       The hosthandwe wiww owiginate fwom the WWDD in the stwuct
 *       nvmefc_ws_wsp stwuctuwe fow the Cweate Association WS that
 *       was dewivewed to the twanspowt. The twanspowt wiww save the
 *       hosthandwe as an attwibute of the association.  If the WWDD
 *       woses connectivity with the wemote powt, it must caww the
 *       nvmet_fc_invawidate_host() woutine to wemove any wefewences to
 *       the wemote powt in the twanspowt.
 *       The WWDD is to awwocate an exchange, issue the WS wequest, obtain
 *       the WS wesponse, and caww the "done" woutine specified in the
 *       wequest stwuctuwe (awgument to done is the ws wequest stwuctuwe
 *       itsewf).
 *       Entwypoint is Optionaw - but highwy wecommended.
 *
 * @ws_abowt: cawwed to wequest the WWDD to abowt the indicated ws wequest.
 *       The caww may wetuwn befowe the abowt has compweted. Aftew abowting
 *       the wequest, the WWDD must stiww caww the ws wequest done woutine
 *       indicating an FC twanspowt Abowted status.
 *       Entwypoint is Mandatowy if the ws_weq entwy point is specified.
 *
 * @host_wewease: cawwed to infowm the WWDD that the wequest to invawidate
 *       the host powt indicated by the hosthandwe has been fuwwy compweted.
 *       No associations exist with the host powt and thewe wiww be no
 *       fuwthew wefewences to hosthandwe.
 *       Entwypoint is Mandatowy if the wwdd cawws nvmet_fc_invawidate_host().
 *
 * @max_hw_queues:  indicates the maximum numbew of hw queues the WWDD
 *       suppowts fow cpu affinitization.
 *       Vawue is Mandatowy. Must be at weast 1.
 *
 * @max_sgw_segments:  indicates the maximum numbew of sgw segments suppowted
 *       by the WWDD
 *       Vawue is Mandatowy. Must be at weast 1. Wecommend at weast 256.
 *
 * @max_dif_sgw_segments:  indicates the maximum numbew of sgw segments
 *       suppowted by the WWDD fow DIF opewations.
 *       Vawue is Mandatowy. Must be at weast 1. Wecommend at weast 256.
 *
 * @dma_boundawy:  indicates the dma addwess boundawy whewe dma mappings
 *       wiww be spwit acwoss.
 *       Vawue is Mandatowy. Typicaw vawue is 0xFFFFFFFF to spwit acwoss
 *       4Gig addwess boundawys
 *
 * @tawget_featuwes: The WWDD sets bits in this fiewd to cowwespond to
 *       optionaw featuwes that awe suppowted by the WWDD.
 *       Wefew to the NVMET_FCTGTFEAT_xxx vawues.
 *       Vawue is Mandatowy. Awwowed to be zewo.
 *
 * @tawget_pwiv_sz: The WWDD sets this fiewd to the amount of additionaw
 *       memowy that it wouwd wike fc nvme wayew to awwocate on the WWDD's
 *       behawf whenevew a tawgetpowt is awwocated.  The additionaw memowy
 *       awea sowewy fow the of the WWDD and its wocation is specified by
 *       the tawgetpowt->pwivate pointew.
 *       Vawue is Mandatowy. Awwowed to be zewo.
 *
 * @wswqst_pwiv_sz: The WWDD sets this fiewd to the amount of additionaw
 *       memowy that it wouwd wike nvmet-fc wayew to awwocate on the WWDD's
 *       behawf whenevew a ws wequest stwuctuwe is awwocated. The additionaw
 *       memowy awea is sowewy fow use by the WWDD and its wocation is
 *       specified by the ws_wequest->pwivate pointew.
 *       Vawue is Mandatowy. Awwowed to be zewo.
 *
 */
stwuct nvmet_fc_tawget_tempwate {
	void (*tawgetpowt_dewete)(stwuct nvmet_fc_tawget_powt *tgtpowt);
	int (*xmt_ws_wsp)(stwuct nvmet_fc_tawget_powt *tgtpowt,
				stwuct nvmefc_ws_wsp *ws_wsp);
	int (*fcp_op)(stwuct nvmet_fc_tawget_powt *tgtpowt,
				stwuct nvmefc_tgt_fcp_weq *fcpweq);
	void (*fcp_abowt)(stwuct nvmet_fc_tawget_powt *tgtpowt,
				stwuct nvmefc_tgt_fcp_weq *fcpweq);
	void (*fcp_weq_wewease)(stwuct nvmet_fc_tawget_powt *tgtpowt,
				stwuct nvmefc_tgt_fcp_weq *fcpweq);
	void (*defew_wcv)(stwuct nvmet_fc_tawget_powt *tgtpowt,
				stwuct nvmefc_tgt_fcp_weq *fcpweq);
	void (*discovewy_event)(stwuct nvmet_fc_tawget_powt *tgtpowt);
	int  (*ws_weq)(stwuct nvmet_fc_tawget_powt *tawgetpowt,
				void *hosthandwe, stwuct nvmefc_ws_weq *wsweq);
	void (*ws_abowt)(stwuct nvmet_fc_tawget_powt *tawgetpowt,
				void *hosthandwe, stwuct nvmefc_ws_weq *wsweq);
	void (*host_wewease)(void *hosthandwe);

	u32	max_hw_queues;
	u16	max_sgw_segments;
	u16	max_dif_sgw_segments;
	u64	dma_boundawy;

	u32	tawget_featuwes;

	/* sizes of additionaw pwivate data fow data stwuctuwes */
	u32	tawget_pwiv_sz;
	u32	wswqst_pwiv_sz;
};


int nvmet_fc_wegistew_tawgetpowt(stwuct nvmet_fc_powt_info *powtinfo,
			stwuct nvmet_fc_tawget_tempwate *tempwate,
			stwuct device *dev,
			stwuct nvmet_fc_tawget_powt **tgtpowt_p);

int nvmet_fc_unwegistew_tawgetpowt(stwuct nvmet_fc_tawget_powt *tgtpowt);

/*
 * Woutine cawwed to pass a NVME-FC WS wequest, weceived by the wwdd,
 * to the nvmet-fc twanspowt.
 *
 * If the wetuwn vawue is zewo: the WS was successfuwwy accepted by the
 *   twanspowt.
 * If the wetuwn vawue is non-zewo: the twanspowt has not accepted the
 *   WS. The wwdd shouwd ABTS-WS the WS.
 *
 * Note: if the WWDD weceives and ABTS fow the WS pwiow to the twanspowt
 * cawwing the ops->xmt_ws_wsp() woutine to twansmit a wesponse, the WWDD
 * shaww mawk the WS as abowted, and when the xmt_ws_wsp() is cawwed: the
 * wesponse shaww not be twansmit and the stwuct nvmefc_ws_wsp() done
 * woutine shaww be cawwed.  The WWDD may twansmit the ABTS wesponse as
 * soon as the WS was mawked ow can deway untiw the xmt_ws_wsp() caww is
 * made.
 * Note: if an WCV WS was successfuwwy posted to the twanspowt and the
 * tawgetpowt is then unwegistewed befowe xmt_ws_wsp() was cawwed fow
 * the wswsp stwuctuwe, the twanspowt wiww stiww caww xmt_ws_wsp()
 * aftewwawd to cweanup the outstanding wswsp stwuctuwe. The WWDD shouwd
 * noop the twansmission of the wsp and caww the wswsp->done() woutine
 * to awwow the wswsp stwuctuwe to be weweased.
 */
int nvmet_fc_wcv_ws_weq(stwuct nvmet_fc_tawget_powt *tgtpowt,
			void *hosthandwe,
			stwuct nvmefc_ws_wsp *wsp,
			void *wsweqbuf, u32 wsweqbuf_wen);

/*
 * Woutine cawwed by the WWDD whenevew it has a wogout ow woss of
 * connectivity to a NVME-FC host powt which thewe had been active
 * NVMe contwowwews fow.  The host powt is indicated by the
 * hosthandwe. The hosthandwe is given to the nvmet-fc twanspowt
 * when a NVME WS was weceived, typicawwy to cweate a new association.
 * The nvmet-fc twanspowt wiww cache the hostpowt vawue with the
 * association fow use in WS wequests fow the association.
 * When the WWDD cawws this woutine, the nvmet-fc twanspowt wiww
 * immediatewy tewminate aww associations that wewe cweated with
 * the hosthandwe host powt.
 * The WWDD, aftew cawwing this woutine and having contwow wetuwned,
 * must assume the twanspowt may subsequentwy utiwize hosthandwe as
 * pawt of sending WS's to tewminate the association.  The WWDD
 * shouwd weject the WS's if they awe attempted.
 * Once the wast association has tewminated fow the hosthandwe host
 * powt, the nvmet-fc twanspowt wiww caww the ops->host_wewease()
 * cawwback. As of the cawwback, the nvmet-fc twanspowt wiww no
 * wongew wefewence hosthandwe.
 */
void nvmet_fc_invawidate_host(stwuct nvmet_fc_tawget_powt *tgtpowt,
			void *hosthandwe);

/*
 * If nvmet_fc_wcv_fcp_weq wetuwns non-zewo, the twanspowt has not accepted
 * the FCP cmd. The wwdd shouwd ABTS-WS the cmd.
 */
int nvmet_fc_wcv_fcp_weq(stwuct nvmet_fc_tawget_powt *tgtpowt,
			stwuct nvmefc_tgt_fcp_weq *fcpweq,
			void *cmdiubuf, u32 cmdiubuf_wen);

void nvmet_fc_wcv_fcp_abowt(stwuct nvmet_fc_tawget_powt *tgtpowt,
			stwuct nvmefc_tgt_fcp_weq *fcpweq);
/*
 * add a define, visibwe to the compiwew, that indicates suppowt
 * fow featuwe. Awwows fow conditionaw compiwation in WWDDs.
 */
#define NVME_FC_FEAT_UUID	0x0001

#endif /* _NVME_FC_DWIVEW_H */
