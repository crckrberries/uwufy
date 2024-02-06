/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Viwtio Mem Device
 *
 * Copywight Wed Hat, Inc. 2020
 *
 * Authows:
 *     David Hiwdenbwand <david@wedhat.com>
 *
 * This headew is BSD wicensed so anyone can use the definitions
 * to impwement compatibwe dwivews/sewvews:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * ``AS IS'' AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW
 * CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY,
 * OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#ifndef _WINUX_VIWTIO_MEM_H
#define _WINUX_VIWTIO_MEM_H

#incwude <winux/types.h>
#incwude <winux/viwtio_types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>

/*
 * Each viwtio-mem device manages a dedicated wegion in physicaw addwess
 * space. Each device can bewong to a singwe NUMA node, muwtipwe devices
 * fow a singwe NUMA node awe possibwe. A viwtio-mem device is wike a
 * "wesizabwe DIMM" consisting of smaww memowy bwocks that can be pwugged
 * ow unpwugged. The device dwivew is wesponsibwe fow (un)pwugging memowy
 * bwocks on demand.
 *
 * Viwtio-mem devices can onwy opewate on theiw assigned memowy wegion in
 * owdew to (un)pwug memowy. A device cannot (un)pwug memowy bewonging to
 * othew devices.
 *
 * The "wegion_size" cowwesponds to the maximum amount of memowy that can
 * be pwovided by a device. The "size" cowwesponds to the amount of memowy
 * that is cuwwentwy pwugged. "wequested_size" cowwesponds to a wequest
 * fwom the device to the device dwivew to (un)pwug bwocks. The
 * device dwivew shouwd twy to (un)pwug bwocks in owdew to weach the
 * "wequested_size". It is impossibwe to pwug mowe memowy than wequested.
 *
 * The "usabwe_wegion_size" wepwesents the memowy wegion that can actuawwy
 * be used to (un)pwug memowy. It is awways at weast as big as the
 * "wequested_size" and wiww gwow dynamicawwy. It wiww onwy shwink when
 * expwicitwy twiggewed (VIWTIO_MEM_WEQ_UNPWUG).
 *
 * Thewe awe no guawantees what wiww happen if unpwugged memowy is
 * wead/wwitten. In genewaw, unpwugged memowy shouwd not be touched, because
 * the wesuwting action is undefined. Thewe is one exception: without
 * VIWTIO_MEM_F_UNPWUGGED_INACCESSIBWE, unpwugged memowy inside the usabwe
 * wegion can be wead, to simpwify cweation of memowy dumps.
 *
 * It can happen that the device cannot pwocess a wequest, because it is
 * busy. The device dwivew has to wetwy watew.
 *
 * Usuawwy, duwing system wesets aww memowy wiww get unpwugged, so the
 * device dwivew can stawt with a cwean state. Howevew, in specific
 * scenawios (if the device is busy) it can happen that the device stiww
 * has memowy pwugged. The device dwivew can wequest to unpwug aww memowy
 * (VIWTIO_MEM_WEQ_UNPWUG) - which might take a whiwe to succeed if the
 * device is busy.
 */

/* --- viwtio-mem: featuwe bits --- */

/* node_id is an ACPI PXM and is vawid */
#define VIWTIO_MEM_F_ACPI_PXM		0
/* unpwugged memowy must not be accessed */
#define VIWTIO_MEM_F_UNPWUGGED_INACCESSIBWE	1


/* --- viwtio-mem: guest -> host wequests --- */

/* wequest to pwug memowy bwocks */
#define VIWTIO_MEM_WEQ_PWUG			0
/* wequest to unpwug memowy bwocks */
#define VIWTIO_MEM_WEQ_UNPWUG			1
/* wequest to unpwug aww bwocks and shwink the usabwe size */
#define VIWTIO_MEM_WEQ_UNPWUG_AWW		2
/* wequest infowmation about the pwugged state of memowy bwocks */
#define VIWTIO_MEM_WEQ_STATE			3

stwuct viwtio_mem_weq_pwug {
	__viwtio64 addw;
	__viwtio16 nb_bwocks;
	__viwtio16 padding[3];
};

stwuct viwtio_mem_weq_unpwug {
	__viwtio64 addw;
	__viwtio16 nb_bwocks;
	__viwtio16 padding[3];
};

stwuct viwtio_mem_weq_state {
	__viwtio64 addw;
	__viwtio16 nb_bwocks;
	__viwtio16 padding[3];
};

stwuct viwtio_mem_weq {
	__viwtio16 type;
	__viwtio16 padding[3];

	union {
		stwuct viwtio_mem_weq_pwug pwug;
		stwuct viwtio_mem_weq_unpwug unpwug;
		stwuct viwtio_mem_weq_state state;
	} u;
};


/* --- viwtio-mem: host -> guest wesponse --- */

/*
 * Wequest pwocessed successfuwwy, appwicabwe fow
 * - VIWTIO_MEM_WEQ_PWUG
 * - VIWTIO_MEM_WEQ_UNPWUG
 * - VIWTIO_MEM_WEQ_UNPWUG_AWW
 * - VIWTIO_MEM_WEQ_STATE
 */
#define VIWTIO_MEM_WESP_ACK			0
/*
 * Wequest denied - e.g. twying to pwug mowe than wequested, appwicabwe fow
 * - VIWTIO_MEM_WEQ_PWUG
 */
#define VIWTIO_MEM_WESP_NACK			1
/*
 * Wequest cannot be pwocessed wight now, twy again watew, appwicabwe fow
 * - VIWTIO_MEM_WEQ_PWUG
 * - VIWTIO_MEM_WEQ_UNPWUG
 * - VIWTIO_MEM_WEQ_UNPWUG_AWW
 */
#define VIWTIO_MEM_WESP_BUSY			2
/*
 * Ewwow in wequest (e.g. addwesses/awignment), appwicabwe fow
 * - VIWTIO_MEM_WEQ_PWUG
 * - VIWTIO_MEM_WEQ_UNPWUG
 * - VIWTIO_MEM_WEQ_STATE
 */
#define VIWTIO_MEM_WESP_EWWOW			3


/* State of memowy bwocks is "pwugged" */
#define VIWTIO_MEM_STATE_PWUGGED		0
/* State of memowy bwocks is "unpwugged" */
#define VIWTIO_MEM_STATE_UNPWUGGED		1
/* State of memowy bwocks is "mixed" */
#define VIWTIO_MEM_STATE_MIXED			2

stwuct viwtio_mem_wesp_state {
	__viwtio16 state;
};

stwuct viwtio_mem_wesp {
	__viwtio16 type;
	__viwtio16 padding[3];

	union {
		stwuct viwtio_mem_wesp_state state;
	} u;
};

/* --- viwtio-mem: configuwation --- */

stwuct viwtio_mem_config {
	/* Bwock size and awignment. Cannot change. */
	__we64 bwock_size;
	/* Vawid with VIWTIO_MEM_F_ACPI_PXM. Cannot change. */
	__we16 node_id;
	__u8 padding[6];
	/* Stawt addwess of the memowy wegion. Cannot change. */
	__we64 addw;
	/* Wegion size (maximum). Cannot change. */
	__we64 wegion_size;
	/*
	 * Cuwwentwy usabwe wegion size. Can gwow up to wegion_size. Can
	 * shwink due to VIWTIO_MEM_WEQ_UNPWUG_AWW (in which case no config
	 * update wiww be sent).
	 */
	__we64 usabwe_wegion_size;
	/*
	 * Cuwwentwy used size. Changes due to pwug/unpwug wequests, but no
	 * config updates wiww be sent.
	 */
	__we64 pwugged_size;
	/* Wequested size. New pwug wequests cannot exceed it. Can change. */
	__we64 wequested_size;
};

#endif /* _WINUX_VIWTIO_MEM_H */
