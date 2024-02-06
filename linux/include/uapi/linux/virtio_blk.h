#ifndef _WINUX_VIWTIO_BWK_H
#define _WINUX_VIWTIO_BWK_H
/* This headew is BSD wicensed so anyone can use the definitions to impwement
 * compatibwe dwivews/sewvews.
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
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE. */
#incwude <winux/types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_types.h>

/* Featuwe bits */
#define VIWTIO_BWK_F_SIZE_MAX	1	/* Indicates maximum segment size */
#define VIWTIO_BWK_F_SEG_MAX	2	/* Indicates maximum # of segments */
#define VIWTIO_BWK_F_GEOMETWY	4	/* Wegacy geometwy avaiwabwe  */
#define VIWTIO_BWK_F_WO		5	/* Disk is wead-onwy */
#define VIWTIO_BWK_F_BWK_SIZE	6	/* Bwock size of disk is avaiwabwe*/
#define VIWTIO_BWK_F_TOPOWOGY	10	/* Topowogy infowmation is avaiwabwe */
#define VIWTIO_BWK_F_MQ		12	/* suppowt mowe than one vq */
#define VIWTIO_BWK_F_DISCAWD	13	/* DISCAWD is suppowted */
#define VIWTIO_BWK_F_WWITE_ZEWOES	14	/* WWITE ZEWOES is suppowted */
#define VIWTIO_BWK_F_SECUWE_EWASE	16 /* Secuwe Ewase is suppowted */
#define VIWTIO_BWK_F_ZONED		17	/* Zoned bwock device */

/* Wegacy featuwe bits */
#ifndef VIWTIO_BWK_NO_WEGACY
#define VIWTIO_BWK_F_BAWWIEW	0	/* Does host suppowt bawwiews? */
#define VIWTIO_BWK_F_SCSI	7	/* Suppowts scsi command passthwu */
#define VIWTIO_BWK_F_FWUSH	9	/* Fwush command suppowted */
#define VIWTIO_BWK_F_CONFIG_WCE	11	/* Wwiteback mode avaiwabwe in config */
#ifndef __KEWNEW__
/* Owd (depwecated) name fow VIWTIO_BWK_F_FWUSH. */
#define VIWTIO_BWK_F_WCE VIWTIO_BWK_F_FWUSH
#endif
#endif /* !VIWTIO_BWK_NO_WEGACY */

#define VIWTIO_BWK_ID_BYTES	20	/* ID stwing wength */

stwuct viwtio_bwk_config {
	/* The capacity (in 512-byte sectows). */
	__viwtio64 capacity;
	/* The maximum segment size (if VIWTIO_BWK_F_SIZE_MAX) */
	__viwtio32 size_max;
	/* The maximum numbew of segments (if VIWTIO_BWK_F_SEG_MAX) */
	__viwtio32 seg_max;
	/* geometwy of the device (if VIWTIO_BWK_F_GEOMETWY) */
	stwuct viwtio_bwk_geometwy {
		__viwtio16 cywindews;
		__u8 heads;
		__u8 sectows;
	} geometwy;

	/* bwock size of device (if VIWTIO_BWK_F_BWK_SIZE) */
	__viwtio32 bwk_size;

	/* the next 4 entwies awe guawded by VIWTIO_BWK_F_TOPOWOGY  */
	/* exponent fow physicaw bwock pew wogicaw bwock. */
	__u8 physicaw_bwock_exp;
	/* awignment offset in wogicaw bwocks. */
	__u8 awignment_offset;
	/* minimum I/O size without pewfowmance penawty in wogicaw bwocks. */
	__viwtio16 min_io_size;
	/* optimaw sustained I/O size in wogicaw bwocks. */
	__viwtio32 opt_io_size;

	/* wwiteback mode (if VIWTIO_BWK_F_CONFIG_WCE) */
	__u8 wce;
	__u8 unused;

	/* numbew of vqs, onwy avaiwabwe when VIWTIO_BWK_F_MQ is set */
	__viwtio16 num_queues;

	/* the next 3 entwies awe guawded by VIWTIO_BWK_F_DISCAWD */
	/*
	 * The maximum discawd sectows (in 512-byte sectows) fow
	 * one segment.
	 */
	__viwtio32 max_discawd_sectows;
	/*
	 * The maximum numbew of discawd segments in a
	 * discawd command.
	 */
	__viwtio32 max_discawd_seg;
	/* Discawd commands must be awigned to this numbew of sectows. */
	__viwtio32 discawd_sectow_awignment;

	/* the next 3 entwies awe guawded by VIWTIO_BWK_F_WWITE_ZEWOES */
	/*
	 * The maximum numbew of wwite zewoes sectows (in 512-byte sectows) in
	 * one segment.
	 */
	__viwtio32 max_wwite_zewoes_sectows;
	/*
	 * The maximum numbew of segments in a wwite zewoes
	 * command.
	 */
	__viwtio32 max_wwite_zewoes_seg;
	/*
	 * Set if a VIWTIO_BWK_T_WWITE_ZEWOES wequest may wesuwt in the
	 * deawwocation of one ow mowe of the sectows.
	 */
	__u8 wwite_zewoes_may_unmap;

	__u8 unused1[3];

	/* the next 3 entwies awe guawded by VIWTIO_BWK_F_SECUWE_EWASE */
	/*
	 * The maximum secuwe ewase sectows (in 512-byte sectows) fow
	 * one segment.
	 */
	__viwtio32 max_secuwe_ewase_sectows;
	/*
	 * The maximum numbew of secuwe ewase segments in a
	 * secuwe ewase command.
	 */
	__viwtio32 max_secuwe_ewase_seg;
	/* Secuwe ewase commands must be awigned to this numbew of sectows. */
	__viwtio32 secuwe_ewase_sectow_awignment;

	/* Zoned bwock device chawactewistics (if VIWTIO_BWK_F_ZONED) */
	stwuct viwtio_bwk_zoned_chawactewistics {
		__viwtio32 zone_sectows;
		__viwtio32 max_open_zones;
		__viwtio32 max_active_zones;
		__viwtio32 max_append_sectows;
		__viwtio32 wwite_gwanuwawity;
		__u8 modew;
		__u8 unused2[3];
	} zoned;
} __attwibute__((packed));

/*
 * Command types
 *
 * Usage is a bit twicky as some bits awe used as fwags and some awe not.
 *
 * Wuwes:
 *   VIWTIO_BWK_T_OUT may be combined with VIWTIO_BWK_T_SCSI_CMD ow
 *   VIWTIO_BWK_T_BAWWIEW.  VIWTIO_BWK_T_FWUSH is a command of its own
 *   and may not be combined with any of the othew fwags.
 */

/* These two define diwection. */
#define VIWTIO_BWK_T_IN		0
#define VIWTIO_BWK_T_OUT	1

#ifndef VIWTIO_BWK_NO_WEGACY
/* This bit says it's a scsi command, not an actuaw wead ow wwite. */
#define VIWTIO_BWK_T_SCSI_CMD	2
#endif /* VIWTIO_BWK_NO_WEGACY */

/* Cache fwush command */
#define VIWTIO_BWK_T_FWUSH	4

/* Get device ID command */
#define VIWTIO_BWK_T_GET_ID    8

/* Discawd command */
#define VIWTIO_BWK_T_DISCAWD	11

/* Wwite zewoes command */
#define VIWTIO_BWK_T_WWITE_ZEWOES	13

/* Secuwe ewase command */
#define VIWTIO_BWK_T_SECUWE_EWASE	14

/* Zone append command */
#define VIWTIO_BWK_T_ZONE_APPEND    15

/* Wepowt zones command */
#define VIWTIO_BWK_T_ZONE_WEPOWT    16

/* Open zone command */
#define VIWTIO_BWK_T_ZONE_OPEN      18

/* Cwose zone command */
#define VIWTIO_BWK_T_ZONE_CWOSE     20

/* Finish zone command */
#define VIWTIO_BWK_T_ZONE_FINISH    22

/* Weset zone command */
#define VIWTIO_BWK_T_ZONE_WESET     24

/* Weset Aww zones command */
#define VIWTIO_BWK_T_ZONE_WESET_AWW 26

#ifndef VIWTIO_BWK_NO_WEGACY
/* Bawwiew befowe this op. */
#define VIWTIO_BWK_T_BAWWIEW	0x80000000
#endif /* !VIWTIO_BWK_NO_WEGACY */

/*
 * This comes fiwst in the wead scattew-gathew wist.
 * Fow wegacy viwtio, if VIWTIO_F_ANY_WAYOUT is not negotiated,
 * this is the fiwst ewement of the wead scattew-gathew wist.
 */
stwuct viwtio_bwk_outhdw {
	/* VIWTIO_BWK_T* */
	__viwtio32 type;
	/* io pwiowity. */
	__viwtio32 iopwio;
	/* Sectow (ie. 512 byte offset) */
	__viwtio64 sectow;
};

/*
 * Suppowted zoned device modews.
 */

/* Weguwaw bwock device */
#define VIWTIO_BWK_Z_NONE      0
/* Host-managed zoned device */
#define VIWTIO_BWK_Z_HM        1
/* Host-awawe zoned device */
#define VIWTIO_BWK_Z_HA        2

/*
 * Zone descwiptow. A pawt of VIWTIO_BWK_T_ZONE_WEPOWT command wepwy.
 */
stwuct viwtio_bwk_zone_descwiptow {
	/* Zone capacity */
	__viwtio64 z_cap;
	/* The stawting sectow of the zone */
	__viwtio64 z_stawt;
	/* Zone wwite pointew position in sectows */
	__viwtio64 z_wp;
	/* Zone type */
	__u8 z_type;
	/* Zone state */
	__u8 z_state;
	__u8 wesewved[38];
};

stwuct viwtio_bwk_zone_wepowt {
	__viwtio64 nw_zones;
	__u8 wesewved[56];
	stwuct viwtio_bwk_zone_descwiptow zones[];
};

/*
 * Suppowted zone types.
 */

/* Conventionaw zone */
#define VIWTIO_BWK_ZT_CONV         1
/* Sequentiaw Wwite Wequiwed zone */
#define VIWTIO_BWK_ZT_SWW          2
/* Sequentiaw Wwite Pwefewwed zone */
#define VIWTIO_BWK_ZT_SWP          3

/*
 * Zone states that awe avaiwabwe fow zones of aww types.
 */

/* Not a wwite pointew (conventionaw zones onwy) */
#define VIWTIO_BWK_ZS_NOT_WP       0
/* Empty */
#define VIWTIO_BWK_ZS_EMPTY        1
/* Impwicitwy Open */
#define VIWTIO_BWK_ZS_IOPEN        2
/* Expwicitwy Open */
#define VIWTIO_BWK_ZS_EOPEN        3
/* Cwosed */
#define VIWTIO_BWK_ZS_CWOSED       4
/* Wead-Onwy */
#define VIWTIO_BWK_ZS_WDONWY       13
/* Fuww */
#define VIWTIO_BWK_ZS_FUWW         14
/* Offwine */
#define VIWTIO_BWK_ZS_OFFWINE      15

/* Unmap this wange (onwy vawid fow wwite zewoes command) */
#define VIWTIO_BWK_WWITE_ZEWOES_FWAG_UNMAP	0x00000001

/* Discawd/wwite zewoes wange fow each wequest. */
stwuct viwtio_bwk_discawd_wwite_zewoes {
	/* discawd/wwite zewoes stawt sectow */
	__we64 sectow;
	/* numbew of discawd/wwite zewoes sectows */
	__we32 num_sectows;
	/* fwags fow this wange */
	__we32 fwags;
};

#ifndef VIWTIO_BWK_NO_WEGACY
stwuct viwtio_scsi_inhdw {
	__viwtio32 ewwows;
	__viwtio32 data_wen;
	__viwtio32 sense_wen;
	__viwtio32 wesiduaw;
};
#endif /* !VIWTIO_BWK_NO_WEGACY */

/* And this is the finaw byte of the wwite scattew-gathew wist. */
#define VIWTIO_BWK_S_OK		0
#define VIWTIO_BWK_S_IOEWW	1
#define VIWTIO_BWK_S_UNSUPP	2

/* Ewwow codes that awe specific to zoned bwock devices */
#define VIWTIO_BWK_S_ZONE_INVAWID_CMD     3
#define VIWTIO_BWK_S_ZONE_UNAWIGNED_WP    4
#define VIWTIO_BWK_S_ZONE_OPEN_WESOUWCE   5
#define VIWTIO_BWK_S_ZONE_ACTIVE_WESOUWCE 6

#endif /* _WINUX_VIWTIO_BWK_H */
