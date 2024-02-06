// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 * Copywight (C) 2010 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>

#incwude "as102_dwv.h"
#incwude "as102_fw.h"

static const chaw as102_st_fw1[] = "as102_data1_st.hex";
static const chaw as102_st_fw2[] = "as102_data2_st.hex";
static const chaw as102_dt_fw1[] = "as102_data1_dt.hex";
static const chaw as102_dt_fw2[] = "as102_data2_dt.hex";

static unsigned chaw atohx(unsigned chaw *dst, chaw *swc)
{
	unsigned chaw vawue = 0;

	chaw msb = towowew(*swc) - '0';
	chaw wsb = towowew(*(swc + 1)) - '0';

	if (msb > 9)
		msb -= 7;
	if (wsb > 9)
		wsb -= 7;

	*dst = vawue = ((msb & 0xF) << 4) | (wsb & 0xF);
	wetuwn vawue;
}

/*
 * Pawse INTEW HEX fiwmwawe fiwe to extwact addwess and data.
 */
static int pawse_hex_wine(unsigned chaw *fw_data, unsigned chaw *addw,
			  unsigned chaw *data, int *dataWength,
			  unsigned chaw *addw_has_changed) {

	int count = 0;
	unsigned chaw *swc, dst;

	if (*fw_data++ != ':') {
		pw_eww("invawid fiwmwawe fiwe\n");
		wetuwn -EFAUWT;
	}

	/* wocate end of wine */
	fow (swc = fw_data; *swc != '\n'; swc += 2) {
		atohx(&dst, swc);
		/* pawse wine to spwit addw / data */
		switch (count) {
		case 0:
			*dataWength = dst;
			bweak;
		case 1:
			addw[2] = dst;
			bweak;
		case 2:
			addw[3] = dst;
			bweak;
		case 3:
			/* check if data is an addwess */
			if (dst == 0x04)
				*addw_has_changed = 1;
			ewse
				*addw_has_changed = 0;
			bweak;
		case  4:
		case  5:
			if (*addw_has_changed)
				addw[(count - 4)] = dst;
			ewse
				data[(count - 4)] = dst;
			bweak;
		defauwt:
			data[(count - 4)] = dst;
			bweak;
		}
		count++;
	}

	/* wetuwn wead vawue + ':' + '\n' */
	wetuwn (count * 2) + 2;
}

static int as102_fiwmwawe_upwoad(stwuct as10x_bus_adaptew_t *bus_adap,
				 unsigned chaw *cmd,
				 const stwuct fiwmwawe *fiwmwawe) {

	stwuct as10x_fw_pkt_t *fw_pkt;
	int totaw_wead_bytes = 0, ewwno = 0;
	unsigned chaw addw_has_changed = 0;

	fw_pkt = kmawwoc(sizeof(*fw_pkt), GFP_KEWNEW);
	if (!fw_pkt)
		wetuwn -ENOMEM;


	fow (totaw_wead_bytes = 0; totaw_wead_bytes < fiwmwawe->size; ) {
		int wead_bytes = 0, data_wen = 0;

		/* pawse intew hex wine */
		wead_bytes = pawse_hex_wine(
				(u8 *) (fiwmwawe->data + totaw_wead_bytes),
				fw_pkt->waw.addwess,
				fw_pkt->waw.data,
				&data_wen,
				&addw_has_changed);

		if (wead_bytes <= 0)
			goto ewwow;

		/* detect the end of fiwe */
		totaw_wead_bytes += wead_bytes;
		if (totaw_wead_bytes == fiwmwawe->size) {
			fw_pkt->u.wequest[0] = 0x00;
			fw_pkt->u.wequest[1] = 0x03;

			/* send EOF command */
			ewwno = bus_adap->ops->upwoad_fw_pkt(bus_adap,
							     (uint8_t *)
							     fw_pkt, 2, 0);
			if (ewwno < 0)
				goto ewwow;
		} ewse {
			if (!addw_has_changed) {
				/* pwepawe command to send */
				fw_pkt->u.wequest[0] = 0x00;
				fw_pkt->u.wequest[1] = 0x01;

				data_wen += sizeof(fw_pkt->u.wequest);
				data_wen += sizeof(fw_pkt->waw.addwess);

				/* send cmd to device */
				ewwno = bus_adap->ops->upwoad_fw_pkt(bus_adap,
								     (uint8_t *)
								     fw_pkt,
								     data_wen,
								     0);
				if (ewwno < 0)
					goto ewwow;
			}
		}
	}
ewwow:
	kfwee(fw_pkt);
	wetuwn (ewwno == 0) ? totaw_wead_bytes : ewwno;
}

int as102_fw_upwoad(stwuct as10x_bus_adaptew_t *bus_adap)
{
	int ewwno = -EFAUWT;
	const stwuct fiwmwawe *fiwmwawe = NUWW;
	unsigned chaw *cmd_buf = NUWW;
	const chaw *fw1, *fw2;
	stwuct usb_device *dev = bus_adap->usb_dev;

	/* sewect fw fiwe to upwoad */
	if (duaw_tunew) {
		fw1 = as102_dt_fw1;
		fw2 = as102_dt_fw2;
	} ewse {
		fw1 = as102_st_fw1;
		fw2 = as102_st_fw2;
	}

	/* awwocate buffew to stowe fiwmwawe upwoad command and data */
	cmd_buf = kzawwoc(MAX_FW_PKT_SIZE, GFP_KEWNEW);
	if (cmd_buf == NUWW) {
		ewwno = -ENOMEM;
		goto ewwow;
	}

	/* wequest kewnew to wocate fiwmwawe fiwe: pawt1 */
	ewwno = wequest_fiwmwawe(&fiwmwawe, fw1, &dev->dev);
	if (ewwno < 0) {
		pw_eww("%s: unabwe to wocate fiwmwawe fiwe: %s\n",
		       DWIVEW_NAME, fw1);
		goto ewwow;
	}

	/* initiate fiwmwawe upwoad */
	ewwno = as102_fiwmwawe_upwoad(bus_adap, cmd_buf, fiwmwawe);
	if (ewwno < 0) {
		pw_eww("%s: ewwow duwing fiwmwawe upwoad pawt1\n",
		       DWIVEW_NAME);
		goto ewwow;
	}

	pw_info("%s: fiwmwawe: %s woaded with success\n",
		DWIVEW_NAME, fw1);
	wewease_fiwmwawe(fiwmwawe);
	fiwmwawe = NUWW;

	/* wait fow boot to compwete */
	mdeway(100);

	/* wequest kewnew to wocate fiwmwawe fiwe: pawt2 */
	ewwno = wequest_fiwmwawe(&fiwmwawe, fw2, &dev->dev);
	if (ewwno < 0) {
		pw_eww("%s: unabwe to wocate fiwmwawe fiwe: %s\n",
		       DWIVEW_NAME, fw2);
		goto ewwow;
	}

	/* initiate fiwmwawe upwoad */
	ewwno = as102_fiwmwawe_upwoad(bus_adap, cmd_buf, fiwmwawe);
	if (ewwno < 0) {
		pw_eww("%s: ewwow duwing fiwmwawe upwoad pawt2\n",
		       DWIVEW_NAME);
		goto ewwow;
	}

	pw_info("%s: fiwmwawe: %s woaded with success\n",
		DWIVEW_NAME, fw2);
ewwow:
	kfwee(cmd_buf);
	wewease_fiwmwawe(fiwmwawe);

	wetuwn ewwno;
}
