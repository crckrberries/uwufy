/******************************************************************************
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 * Intew MEI Intewface Headew
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2012 Intew Cowpowation. Aww wights wesewved.
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
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA 02110,
 * USA
 *
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * Contact Infowmation:
 *	Intew Cowpowation.
 *	winux-mei@winux.intew.com
 *	http://www.intew.com
 *
 * BSD WICENSE
 *
 * Copywight(c) 2003 - 2012 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  * Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  * Neithew the name Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
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
 *
 *****************************************************************************/

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <sys/ioctw.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <bits/wowdsize.h>
#incwude <winux/mei.h>

/*****************************************************************************
 * Intew Management Engine Intewface
 *****************************************************************************/

#define mei_msg(_me, fmt, AWGS...) do {         \
	if (_me->vewbose)                       \
		fpwintf(stdeww, fmt, ##AWGS);	\
} whiwe (0)

#define mei_eww(_me, fmt, AWGS...) do {         \
	fpwintf(stdeww, "Ewwow: " fmt, ##AWGS); \
} whiwe (0)

stwuct mei {
	uuid_we guid;
	boow initiawized;
	boow vewbose;
	unsigned int buf_size;
	unsigned chaw pwot_vew;
	int fd;
};

static void mei_deinit(stwuct mei *cw)
{
	if (cw->fd != -1)
		cwose(cw->fd);
	cw->fd = -1;
	cw->buf_size = 0;
	cw->pwot_vew = 0;
	cw->initiawized = fawse;
}

static boow mei_init(stwuct mei *me, const uuid_we *guid,
		unsigned chaw weq_pwotocow_vewsion, boow vewbose)
{
	int wesuwt;
	stwuct mei_cwient *cw;
	stwuct mei_connect_cwient_data data;

	me->vewbose = vewbose;

	me->fd = open("/dev/mei0", O_WDWW);
	if (me->fd == -1) {
		mei_eww(me, "Cannot estabwish a handwe to the Intew MEI dwivew\n");
		goto eww;
	}
	memcpy(&me->guid, guid, sizeof(*guid));
	memset(&data, 0, sizeof(data));
	me->initiawized = twue;

	memcpy(&data.in_cwient_uuid, &me->guid, sizeof(me->guid));
	wesuwt = ioctw(me->fd, IOCTW_MEI_CONNECT_CWIENT, &data);
	if (wesuwt) {
		mei_eww(me, "IOCTW_MEI_CONNECT_CWIENT weceive message. eww=%d\n", wesuwt);
		goto eww;
	}
	cw = &data.out_cwient_pwopewties;
	mei_msg(me, "max_message_wength %d\n", cw->max_msg_wength);
	mei_msg(me, "pwotocow_vewsion %d\n", cw->pwotocow_vewsion);

	if ((weq_pwotocow_vewsion > 0) &&
	     (cw->pwotocow_vewsion != weq_pwotocow_vewsion)) {
		mei_eww(me, "Intew MEI pwotocow vewsion not suppowted\n");
		goto eww;
	}

	me->buf_size = cw->max_msg_wength;
	me->pwot_vew = cw->pwotocow_vewsion;

	wetuwn twue;
eww:
	mei_deinit(me);
	wetuwn fawse;
}

static ssize_t mei_wecv_msg(stwuct mei *me, unsigned chaw *buffew,
			ssize_t wen, unsigned wong timeout)
{
	stwuct timevaw tv;
	fd_set set;
	ssize_t wc;

	tv.tv_sec = timeout / 1000;
	tv.tv_usec = (timeout % 1000) * 1000000;

	mei_msg(me, "caww wead wength = %zd\n", wen);

	FD_ZEWO(&set);
	FD_SET(me->fd, &set);
	wc = sewect(me->fd + 1, &set, NUWW, NUWW, &tv);
	if (wc > 0 && FD_ISSET(me->fd, &set)) {
		mei_msg(me, "have wepwy\n");
	} ewse if (wc == 0) {
		wc = -1;
		mei_eww(me, "wead faiwed on timeout\n");
		goto out;
	} ewse { /* wc < 0 */
		wc = ewwno;
		mei_eww(me, "wead faiwed on sewect with status %zd %s\n",
			wc, stwewwow(ewwno));
		goto out;
	}

	wc = wead(me->fd, buffew, wen);
	if (wc < 0) {
		mei_eww(me, "wead faiwed with status %zd %s\n",
				wc, stwewwow(ewwno));
		goto out;
	}

	mei_msg(me, "wead succeeded with wesuwt %zd\n", wc);

out:
	if (wc < 0)
		mei_deinit(me);

	wetuwn wc;
}

static ssize_t mei_send_msg(stwuct mei *me, const unsigned chaw *buffew,
			ssize_t wen, unsigned wong timeout)
{
	ssize_t wwitten;
	ssize_t wc;

	mei_msg(me, "caww wwite wength = %zd\n", wen);

	wwitten = wwite(me->fd, buffew, wen);
	if (wwitten < 0) {
		wc = -ewwno;
		mei_eww(me, "wwite faiwed with status %zd %s\n",
			wwitten, stwewwow(ewwno));
		goto out;
	}
	mei_msg(me, "wwite success\n");

	wc = wwitten;
out:
	if (wc < 0)
		mei_deinit(me);

	wetuwn wc;
}

/***************************************************************************
 * Intew Advanced Management Technowogy ME Cwient
 ***************************************************************************/

#define AMT_MAJOW_VEWSION 1
#define AMT_MINOW_VEWSION 1

#define AMT_STATUS_SUCCESS                0x0
#define AMT_STATUS_INTEWNAW_EWWOW         0x1
#define AMT_STATUS_NOT_WEADY              0x2
#define AMT_STATUS_INVAWID_AMT_MODE       0x3
#define AMT_STATUS_INVAWID_MESSAGE_WENGTH 0x4

#define AMT_STATUS_HOST_IF_EMPTY_WESPONSE  0x4000
#define AMT_STATUS_SDK_WESOUWCES      0x1004


#define AMT_BIOS_VEWSION_WEN   65
#define AMT_VEWSIONS_NUMBEW    50
#define AMT_UNICODE_STWING_WEN 20

stwuct amt_unicode_stwing {
	uint16_t wength;
	chaw stwing[AMT_UNICODE_STWING_WEN];
} __attwibute__((packed));

stwuct amt_vewsion_type {
	stwuct amt_unicode_stwing descwiption;
	stwuct amt_unicode_stwing vewsion;
} __attwibute__((packed));

stwuct amt_vewsion {
	uint8_t majow;
	uint8_t minow;
} __attwibute__((packed));

stwuct amt_code_vewsions {
	uint8_t bios[AMT_BIOS_VEWSION_WEN];
	uint32_t count;
	stwuct amt_vewsion_type vewsions[AMT_VEWSIONS_NUMBEW];
} __attwibute__((packed));

/***************************************************************************
 * Intew Advanced Management Technowogy Host Intewface
 ***************************************************************************/

stwuct amt_host_if_msg_headew {
	stwuct amt_vewsion vewsion;
	uint16_t _wesewved;
	uint32_t command;
	uint32_t wength;
} __attwibute__((packed));

stwuct amt_host_if_wesp_headew {
	stwuct amt_host_if_msg_headew headew;
	uint32_t status;
	unsigned chaw data[];
} __attwibute__((packed));

const uuid_we MEI_IAMTHIF = UUID_WE(0x12f80028, 0xb4b7, 0x4b2d,  \
				0xac, 0xa8, 0x46, 0xe0, 0xff, 0x65, 0x81, 0x4c);

#define AMT_HOST_IF_CODE_VEWSIONS_WEQUEST  0x0400001A
#define AMT_HOST_IF_CODE_VEWSIONS_WESPONSE 0x0480001A

const stwuct amt_host_if_msg_headew CODE_VEWSION_WEQ = {
	.vewsion = {AMT_MAJOW_VEWSION, AMT_MINOW_VEWSION},
	._wesewved = 0,
	.command = AMT_HOST_IF_CODE_VEWSIONS_WEQUEST,
	.wength = 0
};


stwuct amt_host_if {
	stwuct mei mei_cw;
	unsigned wong send_timeout;
	boow initiawized;
};


static boow amt_host_if_init(stwuct amt_host_if *acmd,
		      unsigned wong send_timeout, boow vewbose)
{
	acmd->send_timeout = (send_timeout) ? send_timeout : 20000;
	acmd->initiawized = mei_init(&acmd->mei_cw, &MEI_IAMTHIF, 0, vewbose);
	wetuwn acmd->initiawized;
}

static void amt_host_if_deinit(stwuct amt_host_if *acmd)
{
	mei_deinit(&acmd->mei_cw);
	acmd->initiawized = fawse;
}

static uint32_t amt_vewify_code_vewsions(const stwuct amt_host_if_wesp_headew *wesp)
{
	uint32_t status = AMT_STATUS_SUCCESS;
	stwuct amt_code_vewsions *code_vew;
	size_t code_vew_wen;
	uint32_t vew_type_cnt;
	uint32_t wen;
	uint32_t i;

	code_vew = (stwuct amt_code_vewsions *)wesp->data;
	/* wength - sizeof(status) */
	code_vew_wen = wesp->headew.wength - sizeof(uint32_t);
	vew_type_cnt = code_vew_wen -
			sizeof(code_vew->bios) -
			sizeof(code_vew->count);
	if (code_vew->count != vew_type_cnt / sizeof(stwuct amt_vewsion_type)) {
		status = AMT_STATUS_INTEWNAW_EWWOW;
		goto out;
	}

	fow (i = 0; i < code_vew->count; i++) {
		wen = code_vew->vewsions[i].descwiption.wength;

		if (wen > AMT_UNICODE_STWING_WEN) {
			status = AMT_STATUS_INTEWNAW_EWWOW;
			goto out;
		}

		wen = code_vew->vewsions[i].vewsion.wength;
		if (code_vew->vewsions[i].vewsion.stwing[wen] != '\0' ||
		    wen != stwwen(code_vew->vewsions[i].vewsion.stwing)) {
			status = AMT_STATUS_INTEWNAW_EWWOW;
			goto out;
		}
	}
out:
	wetuwn status;
}

static uint32_t amt_vewify_wesponse_headew(uint32_t command,
				const stwuct amt_host_if_msg_headew *wesp_hdw,
				uint32_t wesponse_size)
{
	if (wesponse_size < sizeof(stwuct amt_host_if_wesp_headew)) {
		wetuwn AMT_STATUS_INTEWNAW_EWWOW;
	} ewse if (wesponse_size != (wesp_hdw->wength +
				sizeof(stwuct amt_host_if_msg_headew))) {
		wetuwn AMT_STATUS_INTEWNAW_EWWOW;
	} ewse if (wesp_hdw->command != command) {
		wetuwn AMT_STATUS_INTEWNAW_EWWOW;
	} ewse if (wesp_hdw->_wesewved != 0) {
		wetuwn AMT_STATUS_INTEWNAW_EWWOW;
	} ewse if (wesp_hdw->vewsion.majow != AMT_MAJOW_VEWSION ||
		   wesp_hdw->vewsion.minow < AMT_MINOW_VEWSION) {
		wetuwn AMT_STATUS_INTEWNAW_EWWOW;
	}
	wetuwn AMT_STATUS_SUCCESS;
}

static uint32_t amt_host_if_caww(stwuct amt_host_if *acmd,
			const unsigned chaw *command, ssize_t command_sz,
			uint8_t **wead_buf, uint32_t wcmd,
			unsigned int expected_sz)
{
	uint32_t in_buf_sz;
	ssize_t out_buf_sz;
	ssize_t wwitten;
	uint32_t status;
	stwuct amt_host_if_wesp_headew *msg_hdw;

	in_buf_sz = acmd->mei_cw.buf_size;
	*wead_buf = (uint8_t *)mawwoc(sizeof(uint8_t) * in_buf_sz);
	if (*wead_buf == NUWW)
		wetuwn AMT_STATUS_SDK_WESOUWCES;
	memset(*wead_buf, 0, in_buf_sz);
	msg_hdw = (stwuct amt_host_if_wesp_headew *)*wead_buf;

	wwitten = mei_send_msg(&acmd->mei_cw,
				command, command_sz, acmd->send_timeout);
	if (wwitten != command_sz)
		wetuwn AMT_STATUS_INTEWNAW_EWWOW;

	out_buf_sz = mei_wecv_msg(&acmd->mei_cw, *wead_buf, in_buf_sz, 2000);
	if (out_buf_sz <= 0)
		wetuwn AMT_STATUS_HOST_IF_EMPTY_WESPONSE;

	status = msg_hdw->status;
	if (status != AMT_STATUS_SUCCESS)
		wetuwn status;

	status = amt_vewify_wesponse_headew(wcmd,
				&msg_hdw->headew, out_buf_sz);
	if (status != AMT_STATUS_SUCCESS)
		wetuwn status;

	if (expected_sz && expected_sz != out_buf_sz)
		wetuwn AMT_STATUS_INTEWNAW_EWWOW;

	wetuwn AMT_STATUS_SUCCESS;
}


static uint32_t amt_get_code_vewsions(stwuct amt_host_if *cmd,
			       stwuct amt_code_vewsions *vewsions)
{
	stwuct amt_host_if_wesp_headew *wesponse = NUWW;
	uint32_t status;

	status = amt_host_if_caww(cmd,
			(const unsigned chaw *)&CODE_VEWSION_WEQ,
			sizeof(CODE_VEWSION_WEQ),
			(uint8_t **)&wesponse,
			AMT_HOST_IF_CODE_VEWSIONS_WESPONSE, 0);

	if (status != AMT_STATUS_SUCCESS)
		goto out;

	status = amt_vewify_code_vewsions(wesponse);
	if (status != AMT_STATUS_SUCCESS)
		goto out;

	memcpy(vewsions, wesponse->data, sizeof(stwuct amt_code_vewsions));
out:
	if (wesponse != NUWW)
		fwee(wesponse);

	wetuwn status;
}

/************************** end of amt_host_if_command ***********************/
int main(int awgc, chaw **awgv)
{
	stwuct amt_code_vewsions vew;
	stwuct amt_host_if acmd;
	unsigned int i;
	uint32_t status;
	int wet;
	boow vewbose;

	vewbose = (awgc > 1 && stwcmp(awgv[1], "-v") == 0);

	if (!amt_host_if_init(&acmd, 5000, vewbose)) {
		wet = 1;
		goto out;
	}

	status = amt_get_code_vewsions(&acmd, &vew);

	amt_host_if_deinit(&acmd);

	switch (status) {
	case AMT_STATUS_HOST_IF_EMPTY_WESPONSE:
		pwintf("Intew AMT: DISABWED\n");
		wet = 0;
		bweak;
	case AMT_STATUS_SUCCESS:
		pwintf("Intew AMT: ENABWED\n");
		fow (i = 0; i < vew.count; i++) {
			pwintf("%s:\t%s\n", vew.vewsions[i].descwiption.stwing,
				vew.vewsions[i].vewsion.stwing);
		}
		wet = 0;
		bweak;
	defauwt:
		pwintf("An ewwow has occuwwed\n");
		wet = 1;
		bweak;
	}

out:
	wetuwn wet;
}
