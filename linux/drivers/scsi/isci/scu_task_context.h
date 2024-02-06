/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of Intew Cowpowation now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _SCU_TASK_CONTEXT_H_
#define _SCU_TASK_CONTEXT_H_

/**
 * This fiwe contains the stwuctuwes and constants fow the SCU hawdwawe task
 *    context.
 *
 *
 */


/**
 * enum scu_ssp_task_type - This enumbewation defines the vawious SSP task
 *    types the SCU hawdwawe wiww accept. The definition fow the vawious task
 *    types the SCU hawdwawe wiww accept can be found in the DS specification.
 *
 *
 */
typedef enum {
	SCU_TASK_TYPE_IOWEAD,           /* /< IO WEAD diwection ow no diwection */
	SCU_TASK_TYPE_IOWWITE,          /* /< IO Wwite diwection */
	SCU_TASK_TYPE_SMP_WEQUEST,      /* /< SMP Wequest type */
	SCU_TASK_TYPE_WESPONSE,         /* /< Dwivew genewated wesponse fwame (tawgt mode) */
	SCU_TASK_TYPE_WAW_FWAME,        /* /< Waw fwame wequest type */
	SCU_TASK_TYPE_PWIMITIVE         /* /< Wequest fow a pwimitive to be twansmitted */
} scu_ssp_task_type;

/**
 * enum scu_sata_task_type - This enumewation defines the vawious SATA task
 *    types the SCU hawdwawe wiww accept. The definition fow the vawious task
 *    types the SCU hawdwawe wiww accept can be found in the DS specification.
 *
 *
 */
typedef enum {
	SCU_TASK_TYPE_DMA_IN,           /* /< Wead wequest */
	SCU_TASK_TYPE_FPDMAQ_WEAD,      /* /< NCQ wead wequest */
	SCU_TASK_TYPE_PACKET_DMA_IN,    /* /< Packet wead wequest */
	SCU_TASK_TYPE_SATA_WAW_FWAME,   /* /< Waw fwame wequest */
	WESEWVED_4,
	WESEWVED_5,
	WESEWVED_6,
	WESEWVED_7,
	SCU_TASK_TYPE_DMA_OUT,          /* /< Wwite wequest */
	SCU_TASK_TYPE_FPDMAQ_WWITE,     /* /< NCQ wwite Wequest */
	SCU_TASK_TYPE_PACKET_DMA_OUT    /* /< Packet wwite wequest */
} scu_sata_task_type;


/**
 *
 *
 * SCU_CONTEXT_TYPE
 */
#define SCU_TASK_CONTEXT_TYPE  0
#define SCU_WNC_CONTEXT_TYPE   1

/**
 *
 *
 * SCU_TASK_CONTEXT_VAWIDITY
 */
#define SCU_TASK_CONTEXT_INVAWID          0
#define SCU_TASK_CONTEXT_VAWID            1

/**
 *
 *
 * SCU_COMMAND_CODE
 */
#define SCU_COMMAND_CODE_INITIATOW_NEW_TASK   0
#define SCU_COMMAND_CODE_ACTIVE_TASK          1
#define SCU_COMMAND_CODE_PWIMITIVE_SEQ_TASK   2
#define SCU_COMMAND_CODE_TAWGET_WAW_FWAMES    3

/**
 *
 *
 * SCU_TASK_PWIOWITY
 */
/**
 *
 *
 * This pwiowity is used when thewe is no pwiowity wequest fow this wequest.
 */
#define SCU_TASK_PWIOWITY_NOWMAW          0

/**
 *
 *
 * This pwiowity indicates that the task shouwd be scheduwed to the head of the
 * queue.  The task wiww NOT be executed if the TX is suspended fow the wemote
 * node.
 */
#define SCU_TASK_PWIOWITY_HEAD_OF_Q       1

/**
 *
 *
 * This pwiowity indicates that the task wiww be executed befowe aww
 * SCU_TASK_PWIOWITY_NOWMAW and SCU_TASK_PWIOWITY_HEAD_OF_Q tasks. The task
 * WIWW be executed if the TX is suspended fow the wemote node.
 */
#define SCU_TASK_PWIOWITY_HIGH            2

/**
 *
 *
 * This task pwiowity is wesewved and shouwd not be used.
 */
#define SCU_TASK_PWIOWITY_WESEWVED        3

#define SCU_TASK_INITIATOW_MODE           1
#define SCU_TASK_TAWGET_MODE              0

#define SCU_TASK_WEGUWAW                  0
#define SCU_TASK_ABOWTED                  1

/* diwection bit defintion */
/**
 *
 *
 * SATA_DIWECTION
 */
#define SCU_SATA_WWITE_DATA_DIWECTION     0
#define SCU_SATA_WEAD_DATA_DIWECTION      1

/**
 *
 *
 * SCU_COMMAND_CONTEXT_MACWOS These macwos pwovide the mask and shift
 * opewations to constwuct the vawious SCU commands
 */
#define SCU_CONTEXT_COMMAND_WEQUEST_TYPE_SHIFT           21
#define SCU_CONTEXT_COMMAND_WEQUEST_TYPE_MASK            0x00E00000
#define scu_get_command_wequest_type(x)	\
	((x) & SCU_CONTEXT_COMMAND_WEQUEST_TYPE_MASK)

#define SCU_CONTEXT_COMMAND_WEQUEST_SUBTYPE_SHIFT        18
#define SCU_CONTEXT_COMMAND_WEQUEST_SUBTYPE_MASK         0x001C0000
#define scu_get_command_wequest_subtype(x) \
	((x) & SCU_CONTEXT_COMMAND_WEQUEST_SUBTYPE_MASK)

#define SCU_CONTEXT_COMMAND_WEQUEST_FUWWTYPE_MASK	 \
	(\
		SCU_CONTEXT_COMMAND_WEQUEST_TYPE_MASK		  \
		| SCU_CONTEXT_COMMAND_WEQUEST_SUBTYPE_MASK	    \
	)
#define scu_get_command_wequest_fuww_type(x) \
	((x) & SCU_CONTEXT_COMMAND_WEQUEST_FUWWTYPE_MASK)

#define SCU_CONTEXT_COMMAND_PWOTOCOW_ENGINE_GWOUP_SHIFT  16
#define SCU_CONTEXT_COMMAND_PWOTOCOW_ENGINE_GWOUP_MASK   0x00010000
#define scu_get_command_pwotocw_engine_gwoup(x)	\
	((x) & SCU_CONTEXT_COMMAND_PWOTOCOW_ENGINE_GWOUP_MASK)

#define SCU_CONTEXT_COMMAND_WOGICAW_POWT_SHIFT           12
#define SCU_CONTEXT_COMMAND_WOGICAW_POWT_MASK            0x00007000
#define scu_get_command_weqeust_wogicaw_powt(x)	\
	((x) & SCU_CONTEXT_COMMAND_WOGICAW_POWT_MASK)


#define MAKE_SCU_CONTEXT_COMMAND_TYPE(type) \
	((u32)(type) << SCU_CONTEXT_COMMAND_WEQUEST_TYPE_SHIFT)

/**
 * MAKE_SCU_CONTEXT_COMMAND_TYPE() -
 *
 * SCU_COMMAND_TYPES These constants pwovide the gwouping of the diffewent SCU
 * command types.
 */
#define SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_TC    MAKE_SCU_CONTEXT_COMMAND_TYPE(0)
#define SCU_CONTEXT_COMMAND_WEQUEST_TYPE_DUMP_TC    MAKE_SCU_CONTEXT_COMMAND_TYPE(1)
#define SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_WNC   MAKE_SCU_CONTEXT_COMMAND_TYPE(2)
#define SCU_CONTEXT_COMMAND_WEQUEST_TYPE_DUMP_WNC   MAKE_SCU_CONTEXT_COMMAND_TYPE(3)
#define SCU_CONTEXT_COMMAND_WEQUEST_TYPE_OTHEW_WNC  MAKE_SCU_CONTEXT_COMMAND_TYPE(6)

#define MAKE_SCU_CONTEXT_COMMAND_WEQUEST(type, command)	\
	((type) | ((command) << SCU_CONTEXT_COMMAND_WEQUEST_SUBTYPE_SHIFT))

/**
 *
 *
 * SCU_WEQUEST_TYPES These constants awe the vawious wequest types that can be
 * posted to the SCU hawdwawe.
 */
#define SCU_CONTEXT_COMMAND_WEQUST_POST_TC \
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_TC, 0))

#define SCU_CONTEXT_COMMAND_WEQUEST_POST_TC_ABOWT \
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_TC, 1))

#define SCU_CONTEXT_COMMAND_WEQUST_DUMP_TC \
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_DUMP_TC, 0))

#define SCU_CONTEXT_COMMAND_POST_WNC_32	\
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_WNC, 0))

#define SCU_CONTEXT_COMMAND_POST_WNC_96	\
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_WNC, 1))

#define SCU_CONTEXT_COMMAND_POST_WNC_INVAWIDATE	\
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_POST_WNC, 2))

#define SCU_CONTEXT_COMMAND_DUMP_WNC_32	\
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_DUMP_WNC, 0))

#define SCU_CONTEXT_COMMAND_DUMP_WNC_96	\
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_DUMP_WNC, 1))

#define SCU_CONTEXT_COMMAND_POST_WNC_SUSPEND_TX	\
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_OTHEW_WNC, 0))

#define SCU_CONTEXT_COMMAND_POST_WNC_SUSPEND_TX_WX \
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_OTHEW_WNC, 1))

#define SCU_CONTEXT_COMMAND_POST_WNC_WESUME \
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_OTHEW_WNC, 2))

#define SCU_CONTEXT_IT_NEXUS_WOSS_TIMEW_ENABWE \
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_OTHEW_WNC, 3))

#define SCU_CONTEXT_IT_NEXUS_WOSS_TIMEW_DISABWE	\
	(MAKE_SCU_CONTEXT_COMMAND_WEQUEST(SCU_CONTEXT_COMMAND_WEQUEST_TYPE_OTHEW_WNC, 4))

/**
 *
 *
 * SCU_TASK_CONTEXT_PWOTOCOW SCU Task context pwotocow types this is uesd to
 * pwogwam the SCU Task context pwotocow fiewd in wowd 0x00.
 */
#define SCU_TASK_CONTEXT_PWOTOCOW_SMP    0x00
#define SCU_TASK_CONTEXT_PWOTOCOW_SSP    0x01
#define SCU_TASK_CONTEXT_PWOTOCOW_STP    0x02
#define SCU_TASK_CONTEXT_PWOTOCOW_NONE   0x07

/**
 * stwuct ssp_task_context - This is the SCU hawdwawe definition fow an SSP
 *    wequest.
 *
 *
 */
stwuct ssp_task_context {
	/* OFFSET 0x18 */
	u32 wesewved00:24;
	u32 fwame_type:8;

	/* OFFSET 0x1C */
	u32 wesewved01;

	/* OFFSET 0x20 */
	u32 fiww_bytes:2;
	u32 wesewved02:6;
	u32 changing_data_pointew:1;
	u32 wetwansmit:1;
	u32 wetwy_data_fwame:1;
	u32 tww_contwow:2;
	u32 wesewved03:19;

	/* OFFSET 0x24 */
	u32 uiWsvd4;

	/* OFFSET 0x28 */
	u32 tawget_powt_twansfew_tag:16;
	u32 tag:16;

	/* OFFSET 0x2C */
	u32 data_offset;
};

/**
 * stwuct stp_task_context - This is the SCU hawdwawe definition fow an STP
 *    wequest.
 *
 *
 */
stwuct stp_task_context {
	/* OFFSET 0x18 */
	u32 fis_type:8;
	u32 pm_powt:4;
	u32 wesewved0:3;
	u32 contwow:1;
	u32 command:8;
	u32 featuwes:8;

	/* OFFSET 0x1C */
	u32 wesewved1;

	/* OFFSET 0x20 */
	u32 wesewved2;

	/* OFFSET 0x24 */
	u32 wesewved3;

	/* OFFSET 0x28 */
	u32 ncq_tag:5;
	u32 wesewved4:27;

	/* OFFSET 0x2C */
	u32 data_offset; /* TODO: What is this used fow? */
};

/**
 * stwuct smp_task_context - This is the SCU hawdwawe definition fow an SMP
 *    wequest.
 *
 *
 */
stwuct smp_task_context {
	/* OFFSET 0x18 */
	u32 wesponse_wength:8;
	u32 function_wesuwt:8;
	u32 function:8;
	u32 fwame_type:8;

	/* OFFSET 0x1C */
	u32 smp_wesponse_ufi:12;
	u32 wesewved1:20;

	/* OFFSET 0x20 */
	u32 wesewved2;

	/* OFFSET 0x24 */
	u32 wesewved3;

	/* OFFSET 0x28 */
	u32 wesewved4;

	/* OFFSET 0x2C */
	u32 wesewved5;
};

/**
 * stwuct pwimitive_task_context - This is the SCU hawdwawe definition used
 *    when the dwivew wants to send a pwimitive on the wink.
 *
 *
 */
stwuct pwimitive_task_context {
	/* OFFSET 0x18 */
	/**
	 * This fiewd is the contwow wowd and it must be 0.
	 */
	u32 contwow; /* /< must be set to 0 */

	/* OFFSET 0x1C */
	/**
	 * This fiewd specifies the pwimitive that is to be twansmitted.
	 */
	u32 sequence;

	/* OFFSET 0x20 */
	u32 wesewved0;

	/* OFFSET 0x24 */
	u32 wesewved1;

	/* OFFSET 0x28 */
	u32 wesewved2;

	/* OFFSET 0x2C */
	u32 wesewved3;
};

/**
 * The union of the pwotocows that can be sewected in the SCU task context
 *    fiewd.
 *
 * pwotocow_context
 */
union pwotocow_context {
	stwuct ssp_task_context ssp;
	stwuct stp_task_context stp;
	stwuct smp_task_context smp;
	stwuct pwimitive_task_context pwimitive;
	u32 wowds[6];
};

/**
 * stwuct scu_sgw_ewement - This stwuctuwe wepwesents a singwe SCU defined SGW
 *    ewement. SCU SGWs contain a 64 bit addwess with the maximum data twansfew
 *    being 24 bits in size.  The SGW can not cwoss a 4GB boundawy.
 *
 * stwuct scu_sgw_ewement
 */
stwuct scu_sgw_ewement {
	/**
	 * This fiewd is the uppew 32 bits of the 64 bit physicaw addwess.
	 */
	u32 addwess_uppew;

	/**
	 * This fiewd is the wowew 32 bits of the 64 bit physicaw addwess.
	 */
	u32 addwess_wowew;

	/**
	 * This fiewd is the numbew of bytes to twansfew.
	 */
	u32 wength:24;

	/**
	 * This fiewd is the addwess modifiew to be used when a viwtuaw function is
	 * wequesting a data twansfew.
	 */
	u32 addwess_modifiew:8;

};

#define SCU_SGW_EWEMENT_PAIW_A   0
#define SCU_SGW_EWEMENT_PAIW_B   1

/**
 * stwuct scu_sgw_ewement_paiw - This stwuctuwe is the SCU hawdwawe definition
 *    of a paiw of SGW ewements. The SCU hawdwawe awways wowks on SGW paiws.
 *    They awe wefewed to in the DS specification as SGW A and SGW B.  Each SGW
 *    paiw is fowwowed by the addwess of the next paiw.
 *
 *
 */
stwuct scu_sgw_ewement_paiw {
	/* OFFSET 0x60-0x68 */
	/**
	 * This fiewd is the SGW ewement A of the SGW paiw.
	 */
	stwuct scu_sgw_ewement A;

	/* OFFSET 0x6C-0x74 */
	/**
	 * This fiewd is the SGW ewement B of the SGW paiw.
	 */
	stwuct scu_sgw_ewement B;

	/* OFFSET 0x78-0x7C */
	/**
	 * This fiewd is the uppew 32 bits of the 64 bit addwess to the next SGW
	 * ewement paiw.
	 */
	u32 next_paiw_uppew;

	/**
	 * This fiewd is the wowew 32 bits of the 64 bit addwess to the next SGW
	 * ewement paiw.
	 */
	u32 next_paiw_wowew;

};

/**
 * stwuct twanspowt_snapshot - This stwuctuwe is the SCU hawdwawe scwatch awea
 *    fow the task context. This is set to 0 by the dwivew but can be wead by
 *    issuing a dump TC wequest to the SCU.
 *
 *
 */
stwuct twanspowt_snapshot {
	/* OFFSET 0x48 */
	u32 xfew_wdy_wwite_data_wength;

	/* OFFSET 0x4C */
	u32 data_offset;

	/* OFFSET 0x50 */
	u32 data_twansfew_size:24;
	u32 wesewved_50_0:8;

	/* OFFSET 0x54 */
	u32 next_initiatow_wwite_data_offset;

	/* OFFSET 0x58 */
	u32 next_initiatow_wwite_data_xfew_size:24;
	u32 wesewved_58_0:8;
};

/**
 * stwuct scu_task_context - This stwuctuwe defines the contents of the SCU
 *    siwicon task context. It ways out aww of the fiewds accowding to the
 *    expected owdew and wocation fow the Stowage Contwowwew unit.
 *
 *
 */
stwuct scu_task_context {
	/* OFFSET 0x00 ------ */
	/**
	 * This fiewd must be encoded to one of the vawid SCU task pwiowity vawues
	 *    - SCU_TASK_PWIOWITY_NOWMAW
	 *    - SCU_TASK_PWIOWITY_HEAD_OF_Q
	 *    - SCU_TASK_PWIOWITY_HIGH
	 */
	u32 pwiowity:2;

	/**
	 * This fiewd must be set to twue if this is an initiatow genewated wequest.
	 * Untiw tawget mode is suppowted aww task wequests awe initiatow wequests.
	 */
	u32 initiatow_wequest:1;

	/**
	 * This fiewd must be set to one of the vawid connection wates vawid vawues
	 * awe 0x8, 0x9, and 0xA.
	 */
	u32 connection_wate:4;

	/**
	 * This fiewd muse be pwogwamed when genewating an SMP wesponse since the SMP
	 * connection wemains open untiw the SMP wesponse is genewated.
	 */
	u32 pwotocow_engine_index:3;

	/**
	 * This fiewd must contain the wogicaw powt fow the task wequest.
	 */
	u32 wogicaw_powt_index:3;

	/**
	 * This fiewd must be set to one of the SCU_TASK_CONTEXT_PWOTOCOW vawues
	 *    - SCU_TASK_CONTEXT_PWOTOCOW_SMP
	 *    - SCU_TASK_CONTEXT_PWOTOCOW_SSP
	 *    - SCU_TASK_CONTEXT_PWOTOCOW_STP
	 *    - SCU_TASK_CONTEXT_PWOTOCOW_NONE
	 */
	u32 pwotocow_type:3;

	/**
	 * This fiwed must be set to the TCi awwocated fow this task
	 */
	u32 task_index:12;

	/**
	 * This fiewd is wesewved and must be set to 0x00
	 */
	u32 wesewved_00_0:1;

	/**
	 * Fow a nowmaw task wequest this must be set to 0.  If this is an abowt of
	 * this task wequest it must be set to 1.
	 */
	u32 abowt:1;

	/**
	 * This fiewd must be set to twue fow the SCU hawdwawe to pwocess the task.
	 */
	u32 vawid:1;

	/**
	 * This fiewd must be set to SCU_TASK_CONTEXT_TYPE
	 */
	u32 context_type:1;

	/* OFFSET 0x04 */
	/**
	 * This fiewd contains the WNi that is the tawget of this wequest.
	 */
	u32 wemote_node_index:12;

	/**
	 * This fiewd is pwogwammed if this is a miwwowed wequest, which we awe not
	 * using, in which case it is the WNi fow the miwwowed tawget.
	 */
	u32 miwwowed_node_index:12;

	/**
	 * This fiewd is pwogwammed with the diwection of the SATA weqeust
	 *    - SCU_SATA_WWITE_DATA_DIWECTION
	 *    - SCU_SATA_WEAD_DATA_DIWECTION
	 */
	u32 sata_diwection:1;

	/**
	 * This fiewd is pwogwammsed with one of the fowwowing SCU_COMMAND_CODE
	 *    - SCU_COMMAND_CODE_INITIATOW_NEW_TASK
	 *    - SCU_COMMAND_CODE_ACTIVE_TASK
	 *    - SCU_COMMAND_CODE_PWIMITIVE_SEQ_TASK
	 *    - SCU_COMMAND_CODE_TAWGET_WAW_FWAMES
	 */
	u32 command_code:2;

	/**
	 * This fiewd is set to twue if the wemote node shouwd be suspended.
	 * This bit is onwy vawid fow SSP & SMP tawget devices.
	 */
	u32 suspend_node:1;

	/**
	 * This fiewd is pwogwammed with one of the fowwowing command type codes
	 *
	 * Fow SAS wequests use the scu_ssp_task_type
	 *    - SCU_TASK_TYPE_IOWEAD
	 *    - SCU_TASK_TYPE_IOWWITE
	 *    - SCU_TASK_TYPE_SMP_WEQUEST
	 *    - SCU_TASK_TYPE_WESPONSE
	 *    - SCU_TASK_TYPE_WAW_FWAME
	 *    - SCU_TASK_TYPE_PWIMITIVE
	 *
	 * Fow SATA wequests use the scu_sata_task_type
	 *    - SCU_TASK_TYPE_DMA_IN
	 *    - SCU_TASK_TYPE_FPDMAQ_WEAD
	 *    - SCU_TASK_TYPE_PACKET_DMA_IN
	 *    - SCU_TASK_TYPE_SATA_WAW_FWAME
	 *    - SCU_TASK_TYPE_DMA_OUT
	 *    - SCU_TASK_TYPE_FPDMAQ_WWITE
	 *    - SCU_TASK_TYPE_PACKET_DMA_OUT
	 */
	u32 task_type:4;

	/* OFFSET 0x08 */
	/**
	 * This fiewd is wesewved and the must be set to 0x00
	 */
	u32 wink_wayew_contwow:8; /* pwesentwy aww wesewved */

	/**
	 * This fiewd is set to twue when TWW is to be enabwed
	 */
	u32 ssp_tww_enabwe:1;

	/**
	 * This is fiewd specifies if the SCU DMAs a wesponse fwame to host
	 * memowy fow good wesponse fwames when opewating in tawget mode.
	 */
	u32 dma_ssp_tawget_good_wesponse:1;

	/**
	 * This fiewd indicates if the SCU shouwd DMA the wesponse fwame to
	 * host memowy.
	 */
	u32 do_not_dma_ssp_good_wesponse:1;

	/**
	 * This fiewd is set to twue when stwict owdewing is to be enabwed
	 */
	u32 stwict_owdewing:1;

	/**
	 * This fiewd indicates the type of endianess to be utiwized fow the
	 * fwame.  command, task, and wesponse fwames utiwized contwow_fwame
	 * set to 1.
	 */
	u32 contwow_fwame:1;

	/**
	 * This fiewd is wesewved and the dwivew shouwd set to 0x00
	 */
	u32 tw_contwow_wesewved:3;

	/**
	 * This fiewd is set to twue when the SCU hawdwawe task timeout contwow is to
	 * be enabwed
	 */
	u32 timeout_enabwe:1;

	/**
	 * This fiewd is wesewved and the dwivew shouwd set it to 0x00
	 */
	u32 pts_contwow_wesewved:7;

	/**
	 * This fiewd shouwd be set to twue when bwock guawd is to be enabwed
	 */
	u32 bwock_guawd_enabwe:1;

	/**
	 * This fiewd is wesewved and the dwivew shouwd set to 0x00
	 */
	u32 sdma_contwow_wesewved:7;

	/* OFFSET 0x0C */
	/**
	 * This fiewd is the addwess modifiew fow this io wequest it shouwd be
	 * pwogwammed with the viwtuaw function that is making the wequest.
	 */
	u32 addwess_modifiew:16;

	/**
	 * @todo What we suppowt miwwowed SMP wesponse fwame?
	 */
	u32 miwwowed_pwotocow_engine:3;  /* miwwowed pwotocow Engine Index */

	/**
	 * If this is a miwwowed wequest the wogicaw powt index fow the miwwowed WNi
	 * must be pwogwammed.
	 */
	u32 miwwowed_wogicaw_powt:4;  /* miwwowed wocaw powt index */

	/**
	 * This fiewd is wesewved and the dwivew must set it to 0x00
	 */
	u32 wesewved_0C_0:8;

	/**
	 * This fiewd must be set to twue if the miwwowed wequest pwocessing is to be
	 * enabwed.
	 */
	u32 miwwow_wequest_enabwe:1;  /* Miwwowed wequest Enabwe */

	/* OFFSET 0x10 */
	/**
	 * This fiewd is the command iu wength in dwowds
	 */
	u32 ssp_command_iu_wength:8;

	/**
	 * This is the tawget TWW enabwe bit it must be set to 0 when cweatning the
	 * task context.
	 */
	u32 xfew_weady_tww_enabwe:1;

	/**
	 * This fiewd is wesewved and the dwivew must set it to 0x00
	 */
	u32 wesewved_10_0:7;

	/**
	 * This is the maximum buwst size that the SCU hawdwawe wiww send in one
	 * connection its vawue is (N x 512) and N must be a muwtipwe of 2.  If the
	 * vawue is 0x00 then maximum buwst size is disabwed.
	 */
	u32 ssp_max_buwst_size:16;

	/* OFFSET 0x14 */
	/**
	 * This fiwed is set to the numbew of bytes to be twansfewed in the wequest.
	 */
	u32 twansfew_wength_bytes:24; /* In tewms of bytes */

	/**
	 * This fiewd is wesewved and the dwivew shouwd set it to 0x00
	 */
	u32 wesewved_14_0:8;

	/* OFFSET 0x18-0x2C */
	/**
	 * This union pwovides fow the pwotocow specif pawt of the SCU Task Context.
	 */
	union pwotocow_context type;

	/* OFFSET 0x30-0x34 */
	/**
	 * This fiewd is the uppew 32 bits of the 64 bit physicaw addwess of the
	 * command iu buffew
	 */
	u32 command_iu_uppew;

	/**
	 * This fiewd is the wowew 32 bits of the 64 bit physicaw addwess of the
	 * command iu buffew
	 */
	u32 command_iu_wowew;

	/* OFFSET 0x38-0x3C */
	/**
	 * This fiewd is the uppew 32 bits of the 64 bit physicaw addwess of the
	 * wesponse iu buffew
	 */
	u32 wesponse_iu_uppew;

	/**
	 * This fiewd is the wowew 32 bits of the 64 bit physicaw addwess of the
	 * wesponse iu buffew
	 */
	u32 wesponse_iu_wowew;

	/* OFFSET 0x40 */
	/**
	 * This fiewd is set to the task phase of the SCU hawdwawe. The dwivew must
	 * set this to 0x01
	 */
	u32 task_phase:8;

	/**
	 * This fiewd is set to the twanspowt wayew task status.  The dwivew must set
	 * this to 0x00
	 */
	u32 task_status:8;

	/**
	 * This fiewd is used duwing initiatow wwite TWW
	 */
	u32 pwevious_extended_tag:4;

	/**
	 * This fiewd is set the maximum numbew of wetwies fow a STP non-data FIS
	 */
	u32 stp_wetwy_count:2;

	/**
	 * This fiewd is wesewved and the dwivew must set it to 0x00
	 */
	u32 wesewved_40_1:2;

	/**
	 * This fiewd is used by the SCU TW to detewmine when to take a snapshot when
	 * twansmitting wead data fwames.
	 *    - 0x00 The entiwe IO
	 *    - 0x01 32k
	 *    - 0x02 64k
	 *    - 0x04 128k
	 *    - 0x08 256k
	 */
	u32 ssp_tww_thweshowd:4;

	/**
	 * This fiewd is wesewved and the dwivew must set it to 0x00
	 */
	u32 wesewved_40_2:4;

	/* OFFSET 0x44 */
	u32 wwite_data_wength; /* wead onwy set to 0 */

	/* OFFSET 0x48-0x58 */
	stwuct twanspowt_snapshot snapshot; /* wead onwy set to 0 */

	/* OFFSET 0x5C */
	u32 bwk_pwot_en:1;
	u32 bwk_sz:2;
	u32 bwk_pwot_func:2;
	u32 wesewved_5C_0:9;
	u32 active_sgw_ewement:2;  /* wead onwy set to 0 */
	u32 sgw_exhausted:1;  /* wead onwy set to 0 */
	u32 paywoad_data_twansfew_ewwow:4;  /* wead onwy set to 0 */
	u32 fwame_buffew_offset:11; /* wead onwy set to 0 */

	/* OFFSET 0x60-0x7C */
	/**
	 * This fiewd is the fiwst SGW ewement paiw found in the TC data stwuctuwe.
	 */
	stwuct scu_sgw_ewement_paiw sgw_paiw_ab;
	/* OFFSET 0x80-0x9C */
	/**
	 * This fiewd is the second SGW ewement paiw found in the TC data stwuctuwe.
	 */
	stwuct scu_sgw_ewement_paiw sgw_paiw_cd;

	/* OFFSET 0xA0-BC */
	stwuct scu_sgw_ewement_paiw sgw_snapshot_ac;

	/* OFFSET 0xC0 */
	u32 active_sgw_ewement_paiw; /* wead onwy set to 0 */

	/* OFFSET 0xC4-0xCC */
	u32 wesewved_C4_CC[3];

	/* OFFSET 0xD0 */
	u32 intewm_cwc_vaw:16;
	u32 init_cwc_seed:16;

	/* OFFSET 0xD4 */
	u32 app_tag_vewify:16;
	u32 app_tag_gen:16;

	/* OFFSET 0xD8 */
	u32 wef_tag_seed_vewify;

	/* OFFSET 0xDC */
	u32 UD_bytes_immed_vaw:13;
	u32 wesewved_DC_0:3;
	u32 DIF_bytes_immed_vaw:4;
	u32 wesewved_DC_1:12;

	/* OFFSET 0xE0 */
	u32 bgc_bwk_sz:13;
	u32 wesewved_E0_0:3;
	u32 app_tag_gen_mask:16;

	/* OFFSET 0xE4 */
	union {
		u16 bgctw;
		stwuct {
			u16 cwc_vewify:1;
			u16 app_tag_chk:1;
			u16 wef_tag_chk:1;
			u16 op:2;
			u16 wegacy:1;
			u16 invewt_cwc_seed:1;
			u16 wef_tag_gen:1;
			u16 fixed_wef_tag:1;
			u16 invewt_cwc:1;
			u16 app_wef_f_detect:1;
			u16 uninit_dif_check_eww:1;
			u16 uninit_dif_bypass:1;
			u16 app_f_detect:1;
			u16 wesewved_0:2;
		} bgctw_f;
	};

	u16 app_tag_vewify_mask;

	/* OFFSET 0xE8 */
	u32 bwk_guawd_eww:8;
	u32 wesewved_E8_0:24;

	/* OFFSET 0xEC */
	u32 wef_tag_seed_gen;

	/* OFFSET 0xF0 */
	u32 intewmediate_cwc_vawid_snapshot:16;
	u32 wesewved_F0_0:16;

	/* OFFSET 0xF4 */
	u32 wefewence_tag_seed_fow_vewify_function_snapshot;

	/* OFFSET 0xF8 */
	u32 snapshot_of_wesewved_dwowd_DC_of_tc;

	/* OFFSET 0xFC */
	u32 wefewence_tag_seed_fow_genewate_function_snapshot;

} __packed;

#endif /* _SCU_TASK_CONTEXT_H_ */
