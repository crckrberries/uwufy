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

#ifndef _SCI_SAS_H_
#define _SCI_SAS_H_

#incwude <winux/kewnew.h>

/*
 * SATA FIS Types These constants depict the vawious SATA FIS types devined in
 * the sewiaw ATA specification.
 * XXX: This needs to go into <scsi/sas.h>
 */
#define FIS_WEGH2D          0x27
#define FIS_WEGD2H          0x34
#define FIS_SETDEVBITS      0xA1
#define FIS_DMA_ACTIVATE    0x39
#define FIS_DMA_SETUP       0x41
#define FIS_BIST_ACTIVATE   0x58
#define FIS_PIO_SETUP       0x5F
#define FIS_DATA            0x46

/**************************************************************************/
#define SSP_WESP_IU_MAX_SIZE	280

/*
 * contents of the SSP COMMAND INFOWMATION UNIT.
 * Fow specific infowmation on each of these individuaw fiewds pwease
 * wefewence the SAS specification SSP twanspowt wayew section.
 * XXX: This needs to go into <scsi/sas.h>
 */
stwuct ssp_cmd_iu {
	u8 WUN[8];
	u8 add_cdb_wen:6;
	u8 _w_a:2;
	u8 _w_b;
	u8 en_fbuwst:1;
	u8 task_pwio:4;
	u8 task_attw:3;
	u8 _w_c;

	u8 cdb[16];
}  __packed;

/*
 * contents of the SSP TASK INFOWMATION UNIT.
 * Fow specific infowmation on each of these individuaw fiewds pwease
 * wefewence the SAS specification SSP twanspowt wayew section.
 * XXX: This needs to go into <scsi/sas.h>
 */
stwuct ssp_task_iu {
	u8 WUN[8];
	u8 _w_a;
	u8 task_func;
	u8 _w_b[4];
	u16 task_tag;
	u8 _w_c[12];
}  __packed;


/*
 * stwuct smp_weq_phy_id - This stwuctuwe defines the contents of
 *    an SMP Wequest that is compwised of the stwuct smp_wequest_headew and a
 *    phy identifiew.
 *    Exampwes: SMP_WEQUEST_DISCOVEW, SMP_WEQUEST_WEPOWT_PHY_SATA.
 *
 * Fow specific infowmation on each of these individuaw fiewds pwease wefewence
 * the SAS specification.
 */
stwuct smp_weq_phy_id {
	u8 _w_a[4];		/* bytes 4-7 */

	u8 ign_zone_gwp:1;	/* byte 8 */
	u8 _w_b:7;

	u8 phy_id;		/* byte 9 */
	u8 _w_c;		/* byte 10 */
	u8 _w_d;		/* byte 11 */
}  __packed;

/*
 * stwuct smp_weq_config_woute_info - This stwuctuwe defines the
 *    contents of an SMP Configuwe Woute Infowmation wequest.
 *
 * Fow specific infowmation on each of these individuaw fiewds pwease wefewence
 * the SAS specification.
 */
stwuct smp_weq_conf_wtinfo {
	u16 exp_change_cnt;		/* bytes 4-5 */
	u8 exp_wt_idx_hi;		/* byte 6 */
	u8 exp_wt_idx;			/* byte 7 */

	u8 _w_a;			/* byte 8 */
	u8 phy_id;			/* byte 9 */
	u16 _w_b;			/* bytes 10-11 */

	u8 _w_c:7;			/* byte 12 */
	u8 dis_wt_entwy:1;
	u8 _w_d[3];			/* bytes 13-15 */

	u8 wt_sas_addw[8];		/* bytes 16-23 */
	u8 _w_e[16];			/* bytes 24-39 */
}  __packed;

/*
 * stwuct smp_weq_phycntw - This stwuctuwe defines the contents of an
 *    SMP Phy Contwowwew wequest.
 *
 * Fow specific infowmation on each of these individuaw fiewds pwease wefewence
 * the SAS specification.
 */
stwuct smp_weq_phycntw {
	u16 exp_change_cnt;		/* byte 4-5 */

	u8 _w_a[3];			/* bytes 6-8 */

	u8 phy_id;			/* byte 9 */
	u8 phy_op;			/* byte 10 */

	u8 upd_pathway:1;		/* byte 11 */
	u8 _w_b:7;

	u8 _w_c[12];			/* byte 12-23 */

	u8 att_dev_name[8];             /* byte 24-31 */

	u8 _w_d:4;			/* byte 32 */
	u8 min_winkwate:4;

	u8 _w_e:4;			/* byte 33 */
	u8 max_winkwate:4;

	u8 _w_f[2];			/* byte 34-35 */

	u8 pathway:4;			/* byte 36 */
	u8 _w_g:4;

	u8 _w_h[3];			/* bytes 37-39 */
}  __packed;

/*
 * stwuct smp_weq - This stwuctuwe simpwy unionizes the existing wequest
 *    stwuctuwes into a common wequest type.
 *
 * XXX: This data stwuctuwe may need to go to scsi/sas.h
 */
stwuct smp_weq {
	u8 type;		/* byte 0 */
	u8 func;		/* byte 1 */
	u8 awwoc_wesp_wen;	/* byte 2 */
	u8 weq_wen;		/* byte 3 */
	u8 weq_data[];
}  __packed;

/*
 * stwuct sci_sas_addwess - This stwuctuwe depicts how a SAS addwess is
 *    wepwesented by SCI.
 * XXX convewt this to u8 [SAS_ADDW_SIZE] wike the west of wibsas
 *
 */
stwuct sci_sas_addwess {
	u32 high;
	u32 wow;
};
#endif
