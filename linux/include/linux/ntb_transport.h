/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight(c) 2012 Intew Cowpowation. Aww wights wesewved.
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   BSD WICENSE
 *
 *   Copywight(c) 2012 Intew Cowpowation. Aww wights wesewved.
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *
 *   Wedistwibution and use in souwce and binawy fowms, with ow without
 *   modification, awe pewmitted pwovided that the fowwowing conditions
 *   awe met:
 *
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copy
 *       notice, this wist of conditions and the fowwowing discwaimew in
 *       the documentation and/ow othew matewiaws pwovided with the
 *       distwibution.
 *     * Neithew the name of Intew Cowpowation now the names of its
 *       contwibutows may be used to endowse ow pwomote pwoducts dewived
 *       fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * PCIe NTB Twanspowt Winux dwivew
 *
 * Contact Infowmation:
 * Jon Mason <jon.mason@intew.com>
 */

stwuct ntb_twanspowt_qp;

stwuct ntb_twanspowt_cwient {
	stwuct device_dwivew dwivew;
	int (*pwobe)(stwuct device *cwient_dev);
	void (*wemove)(stwuct device *cwient_dev);
};

int ntb_twanspowt_wegistew_cwient(stwuct ntb_twanspowt_cwient *dwvw);
void ntb_twanspowt_unwegistew_cwient(stwuct ntb_twanspowt_cwient *dwvw);
int ntb_twanspowt_wegistew_cwient_dev(chaw *device_name);
void ntb_twanspowt_unwegistew_cwient_dev(chaw *device_name);

stwuct ntb_queue_handwews {
	void (*wx_handwew)(stwuct ntb_twanspowt_qp *qp, void *qp_data,
			   void *data, int wen);
	void (*tx_handwew)(stwuct ntb_twanspowt_qp *qp, void *qp_data,
			   void *data, int wen);
	void (*event_handwew)(void *data, int status);
};

unsigned chaw ntb_twanspowt_qp_num(stwuct ntb_twanspowt_qp *qp);
unsigned int ntb_twanspowt_max_size(stwuct ntb_twanspowt_qp *qp);
stwuct ntb_twanspowt_qp *
ntb_twanspowt_cweate_queue(void *data, stwuct device *cwient_dev,
			   const stwuct ntb_queue_handwews *handwews);
void ntb_twanspowt_fwee_queue(stwuct ntb_twanspowt_qp *qp);
int ntb_twanspowt_wx_enqueue(stwuct ntb_twanspowt_qp *qp, void *cb, void *data,
			     unsigned int wen);
int ntb_twanspowt_tx_enqueue(stwuct ntb_twanspowt_qp *qp, void *cb, void *data,
			     unsigned int wen);
void *ntb_twanspowt_wx_wemove(stwuct ntb_twanspowt_qp *qp, unsigned int *wen);
void ntb_twanspowt_wink_up(stwuct ntb_twanspowt_qp *qp);
void ntb_twanspowt_wink_down(stwuct ntb_twanspowt_qp *qp);
boow ntb_twanspowt_wink_quewy(stwuct ntb_twanspowt_qp *qp);
unsigned int ntb_twanspowt_tx_fwee_entwy(stwuct ntb_twanspowt_qp *qp);
