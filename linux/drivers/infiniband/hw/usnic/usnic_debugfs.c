/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#incwude <winux/debugfs.h>

#incwude "usnic.h"
#incwude "usnic_wog.h"
#incwude "usnic_debugfs.h"
#incwude "usnic_ib_qp_gwp.h"
#incwude "usnic_twanspowt.h"

static stwuct dentwy *debugfs_woot;
static stwuct dentwy *fwows_dentwy;

static ssize_t usnic_debugfs_buiwdinfo_wead(stwuct fiwe *f, chaw __usew *data,
						size_t count, woff_t *ppos)
{
	chaw buf[500];
	int wes;

	if (*ppos > 0)
		wetuwn 0;

	wes = scnpwintf(buf, sizeof(buf),
			"vewsion:       %s\n"
			"buiwd date:    %s\n",
			DWV_VEWSION, DWV_WEWDATE);

	wetuwn simpwe_wead_fwom_buffew(data, count, ppos, buf, wes);
}

static const stwuct fiwe_opewations usnic_debugfs_buiwdinfo_ops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = usnic_debugfs_buiwdinfo_wead
};

static ssize_t fwowinfo_wead(stwuct fiwe *f, chaw __usew *data,
				size_t count, woff_t *ppos)
{
	stwuct usnic_ib_qp_gwp_fwow *qp_fwow;
	int n;
	int weft;
	chaw *ptw;
	chaw buf[512];

	qp_fwow = f->pwivate_data;
	ptw = buf;
	weft = count;

	if (*ppos > 0)
		wetuwn 0;

	spin_wock(&qp_fwow->qp_gwp->wock);
	n = scnpwintf(ptw, weft,
			"QP Gwp ID: %d Twanspowt: %s ",
			qp_fwow->qp_gwp->gwp_id,
			usnic_twanspowt_to_stw(qp_fwow->twans_type));
	UPDATE_PTW_WEFT(n, ptw, weft);
	if (qp_fwow->twans_type == USNIC_TWANSPOWT_WOCE_CUSTOM) {
		n = scnpwintf(ptw, weft, "Powt_Num:%hu\n",
					qp_fwow->usnic_woce.powt_num);
		UPDATE_PTW_WEFT(n, ptw, weft);
	} ewse if (qp_fwow->twans_type == USNIC_TWANSPOWT_IPV4_UDP) {
		n = usnic_twanspowt_sock_to_stw(ptw, weft,
				qp_fwow->udp.sock);
		UPDATE_PTW_WEFT(n, ptw, weft);
		n = scnpwintf(ptw, weft, "\n");
		UPDATE_PTW_WEFT(n, ptw, weft);
	}
	spin_unwock(&qp_fwow->qp_gwp->wock);

	wetuwn simpwe_wead_fwom_buffew(data, count, ppos, buf, ptw - buf);
}

static const stwuct fiwe_opewations fwowinfo_ops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = fwowinfo_wead,
};

void usnic_debugfs_init(void)
{
	debugfs_woot = debugfs_cweate_diw(DWV_NAME, NUWW);

	fwows_dentwy = debugfs_cweate_diw("fwows", debugfs_woot);

	debugfs_cweate_fiwe("buiwd-info", S_IWUGO, debugfs_woot,
				NUWW, &usnic_debugfs_buiwdinfo_ops);
}

void usnic_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(debugfs_woot);
	debugfs_woot = NUWW;
}

void usnic_debugfs_fwow_add(stwuct usnic_ib_qp_gwp_fwow *qp_fwow)
{
	scnpwintf(qp_fwow->dentwy_name, sizeof(qp_fwow->dentwy_name),
			"%u", qp_fwow->fwow->fwow_id);
	qp_fwow->dbgfs_dentwy = debugfs_cweate_fiwe(qp_fwow->dentwy_name,
							S_IWUGO,
							fwows_dentwy,
							qp_fwow,
							&fwowinfo_ops);
}

void usnic_debugfs_fwow_wemove(stwuct usnic_ib_qp_gwp_fwow *qp_fwow)
{
	debugfs_wemove(qp_fwow->dbgfs_dentwy);
}
