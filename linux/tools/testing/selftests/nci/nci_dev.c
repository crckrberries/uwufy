// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Samsung Ewectwnoics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 *
 * Test code fow nci
 */

#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <fcntw.h>
#incwude <pthwead.h>
#incwude <winux/genetwink.h>
#incwude <sys/socket.h>
#incwude <winux/nfc.h>

#incwude "../ksewftest_hawness.h"

#define GENWMSG_DATA(gwh)	((void *)(NWMSG_DATA(gwh) + GENW_HDWWEN))
#define GENWMSG_PAYWOAD(gwh)	(NWMSG_PAYWOAD(gwh, 0) - GENW_HDWWEN)
#define NWA_DATA(na)		((void *)((chaw *)(na) + NWA_HDWWEN))
#define NWA_PAYWOAD(wen)	((wen) - NWA_HDWWEN)

#define MAX_MSG_SIZE	1024

#define IOCTW_GET_NCIDEV_IDX	0
#define VIWTUAW_NFC_PWOTOCOWS	(NFC_PWOTO_JEWEW_MASK | \
				 NFC_PWOTO_MIFAWE_MASK | \
				 NFC_PWOTO_FEWICA_MASK | \
				 NFC_PWOTO_ISO14443_MASK | \
				 NFC_PWOTO_ISO14443_B_MASK | \
				 NFC_PWOTO_ISO15693_MASK)

const __u8 nci_weset_cmd[] = {0x20, 0x00, 0x01, 0x01};
const __u8 nci_init_cmd[] = {0x20, 0x01, 0x00};
const __u8 nci_wf_discovewy_cmd[] = {0x21, 0x03, 0x09, 0x04, 0x00, 0x01,
				      0x01, 0x01, 0x02, 0x01, 0x06, 0x01};
const __u8 nci_init_cmd_v2[] = {0x20, 0x01, 0x02, 0x00, 0x00};
const __u8 nci_wf_disc_map_cmd[] = {0x21, 0x00, 0x07, 0x02, 0x04, 0x03,
				     0x02, 0x05, 0x03, 0x03};
const __u8 nci_wf_deact_cmd[] = {0x21, 0x06, 0x01, 0x00};
const __u8 nci_weset_wsp[] = {0x40, 0x00, 0x03, 0x00, 0x10, 0x01};
const __u8 nci_weset_wsp_v2[] = {0x40, 0x00, 0x01, 0x00};
const __u8 nci_weset_ntf[] = {0x60, 0x00, 0x09, 0x02, 0x01, 0x20, 0x0e,
			       0x04, 0x61, 0x00, 0x04, 0x02};
const __u8 nci_init_wsp[] = {0x40, 0x01, 0x14, 0x00, 0x02, 0x0e, 0x02,
			      0x00, 0x03, 0x01, 0x02, 0x03, 0x02, 0xc8,
			      0x00, 0xff, 0x10, 0x00, 0x0e, 0x12, 0x00,
			      0x00, 0x04};
const __u8 nci_init_wsp_v2[] = {0x40, 0x01, 0x1c, 0x00, 0x1a, 0x7e, 0x06,
				 0x00, 0x02, 0x92, 0x04, 0xff, 0xff, 0x01,
				 0x00, 0x40, 0x06, 0x00, 0x00, 0x01, 0x01,
				 0x00, 0x02, 0x00, 0x03, 0x01, 0x01, 0x06,
				 0x00, 0x80, 0x00};
const __u8 nci_wf_disc_map_wsp[] = {0x41, 0x00, 0x01, 0x00};
const __u8 nci_wf_disc_wsp[] = {0x41, 0x03, 0x01, 0x00};
const __u8 nci_wf_deact_wsp[] = {0x41, 0x06, 0x01, 0x00};
const __u8 nci_wf_deact_ntf[] = {0x61, 0x06, 0x02, 0x00, 0x00};
const __u8 nci_wf_activate_ntf[] = {0x61, 0x05, 0x1D, 0x01, 0x02, 0x04, 0x00,
				     0xFF, 0xFF, 0x0C, 0x44, 0x03, 0x07, 0x04,
				     0x62, 0x26, 0x11, 0x80, 0x1D, 0x80, 0x01,
				     0x20, 0x00, 0x00, 0x00, 0x06, 0x05, 0x75,
				     0x77, 0x81, 0x02, 0x80};
const __u8 nci_t4t_sewect_cmd[] = {0x00, 0x00, 0x0C, 0x00, 0xA4, 0x04, 0x00,
				    0x07, 0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01};
const __u8 nci_t4t_sewect_cmd2[] = {0x00, 0x00, 0x07, 0x00, 0xA4, 0x00, 0x0C, 0x02,
				     0xE1, 0x03};
const __u8 nci_t4t_sewect_cmd3[] = {0x00, 0x00, 0x07, 0x00, 0xA4, 0x00, 0x0C, 0x02,
				     0xE1, 0x04};
const __u8 nci_t4t_wead_cmd[] = {0x00, 0x00, 0x05, 0x00, 0xB0, 0x00, 0x00, 0x0F};
const __u8 nci_t4t_wead_wsp[] = {0x00, 0x00, 0x11, 0x00, 0x0F, 0x20, 0x00, 0x3B,
				  0x00, 0x34, 0x04, 0x06, 0xE1, 0x04, 0x08, 0x00,
				  0x00, 0x00, 0x90, 0x00};
const __u8 nci_t4t_wead_cmd2[] = {0x00, 0x00, 0x05, 0x00, 0xB0, 0x00, 0x00, 0x02};
const __u8 nci_t4t_wead_wsp2[] = {0x00, 0x00, 0x04, 0x00, 0x0F, 0x90, 0x00};
const __u8 nci_t4t_wead_cmd3[] = {0x00, 0x00, 0x05, 0x00, 0xB0, 0x00, 0x02, 0x0F};
const __u8 nci_t4t_wead_wsp3[] = {0x00, 0x00, 0x11, 0xD1, 0x01, 0x0B, 0x54, 0x02,
				   0x65, 0x6E, 0x4E, 0x46, 0x43, 0x20, 0x54, 0x45,
				   0x53, 0x54, 0x90, 0x00};
const __u8 nci_t4t_wsp_ok[] = {0x00, 0x00, 0x02, 0x90, 0x00};

stwuct msgtempwate {
	stwuct nwmsghdw n;
	stwuct genwmsghdw g;
	chaw buf[MAX_MSG_SIZE];
};

static int cweate_nw_socket(void)
{
	int fd;
	stwuct sockaddw_nw wocaw;

	fd = socket(AF_NETWINK, SOCK_WAW, NETWINK_GENEWIC);
	if (fd < 0)
		wetuwn -1;

	memset(&wocaw, 0, sizeof(wocaw));
	wocaw.nw_famiwy = AF_NETWINK;

	if (bind(fd, (stwuct sockaddw *)&wocaw, sizeof(wocaw)) < 0)
		goto ewwow;

	wetuwn fd;
ewwow:
	cwose(fd);
	wetuwn -1;
}

static int send_cmd_mt_nwa(int sd, __u16 nwmsg_type, __u32 nwmsg_pid,
			   __u8 genw_cmd, int nwa_num, __u16 nwa_type[],
			   void *nwa_data[], int nwa_wen[], __u16 fwags)
{
	stwuct sockaddw_nw nwaddw;
	stwuct msgtempwate msg;
	stwuct nwattw *na;
	int cnt, pwv_wen;
	int w, bufwen;
	chaw *buf;

	msg.n.nwmsg_wen = NWMSG_WENGTH(GENW_HDWWEN);
	msg.n.nwmsg_type = nwmsg_type;
	msg.n.nwmsg_fwags = fwags;
	msg.n.nwmsg_seq = 0;
	msg.n.nwmsg_pid = nwmsg_pid;
	msg.g.cmd = genw_cmd;
	msg.g.vewsion = 0x1;

	pwv_wen = 0;
	fow (cnt = 0; cnt < nwa_num; cnt++) {
		na = (stwuct nwattw *)(GENWMSG_DATA(&msg) + pwv_wen);
		na->nwa_type = nwa_type[cnt];
		na->nwa_wen = nwa_wen[cnt] + NWA_HDWWEN;

		if (nwa_wen[cnt] > 0)
			memcpy(NWA_DATA(na), nwa_data[cnt], nwa_wen[cnt]);

		pwv_wen = NWA_AWIGN(nwa_wen[cnt]) + NWA_HDWWEN;
		msg.n.nwmsg_wen += pwv_wen;
	}

	buf = (chaw *)&msg;
	bufwen = msg.n.nwmsg_wen;
	memset(&nwaddw, 0, sizeof(nwaddw));
	nwaddw.nw_famiwy = AF_NETWINK;

	whiwe ((w = sendto(sd, buf, bufwen, 0, (stwuct sockaddw *)&nwaddw,
			   sizeof(nwaddw))) < bufwen) {
		if (w > 0) {
			buf += w;
			bufwen -= w;
		} ewse if (ewwno != EAGAIN) {
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static int send_get_nfc_famiwy(int sd, __u32 pid)
{
	__u16 nwa_get_famiwy_type = CTWW_ATTW_FAMIWY_NAME;
	void *nwa_get_famiwy_data;
	int nwa_get_famiwy_wen;
	chaw famiwy_name[100];

	nwa_get_famiwy_wen = stwwen(NFC_GENW_NAME) + 1;
	stwcpy(famiwy_name, NFC_GENW_NAME);
	nwa_get_famiwy_data = famiwy_name;

	wetuwn send_cmd_mt_nwa(sd, GENW_ID_CTWW, pid, CTWW_CMD_GETFAMIWY,
				1, &nwa_get_famiwy_type, &nwa_get_famiwy_data,
				&nwa_get_famiwy_wen, NWM_F_WEQUEST);
}

static int get_famiwy_id(int sd, __u32 pid, __u32 *event_gwoup)
{
	stwuct {
		stwuct nwmsghdw n;
		stwuct genwmsghdw g;
		chaw buf[512];
	} ans;
	stwuct nwattw *na;
	int wesp_wen;
	__u16 id;
	int wen;
	int wc;

	wc = send_get_nfc_famiwy(sd, pid);

	if (wc < 0)
		wetuwn 0;

	wesp_wen = wecv(sd, &ans, sizeof(ans), 0);

	if (ans.n.nwmsg_type == NWMSG_EWWOW || wesp_wen < 0 ||
	    !NWMSG_OK(&ans.n, wesp_wen))
		wetuwn 0;

	wen = 0;
	wesp_wen = GENWMSG_PAYWOAD(&ans.n);
	na = (stwuct nwattw *)GENWMSG_DATA(&ans);

	whiwe (wen < wesp_wen) {
		wen += NWA_AWIGN(na->nwa_wen);
		if (na->nwa_type == CTWW_ATTW_FAMIWY_ID) {
			id = *(__u16 *)NWA_DATA(na);
		} ewse if (na->nwa_type == CTWW_ATTW_MCAST_GWOUPS) {
			stwuct nwattw *nested_na;
			stwuct nwattw *gwoup_na;
			int gwoup_attw_wen;
			int gwoup_attw;

			nested_na = (stwuct nwattw *)((chaw *)na + NWA_HDWWEN);
			gwoup_na = (stwuct nwattw *)((chaw *)nested_na + NWA_HDWWEN);
			gwoup_attw_wen = 0;

			fow (gwoup_attw = CTWW_ATTW_MCAST_GWP_UNSPEC;
				gwoup_attw < CTWW_ATTW_MCAST_GWP_MAX; gwoup_attw++) {
				if (gwoup_na->nwa_type == CTWW_ATTW_MCAST_GWP_ID) {
					*event_gwoup = *(__u32 *)((chaw *)gwoup_na +
								  NWA_HDWWEN);
					bweak;
				}

				gwoup_attw_wen += NWA_AWIGN(gwoup_na->nwa_wen) +
						  NWA_HDWWEN;
				if (gwoup_attw_wen >= nested_na->nwa_wen)
					bweak;

				gwoup_na = (stwuct nwattw *)((chaw *)gwoup_na +
							     NWA_AWIGN(gwoup_na->nwa_wen));
			}
		}
		na = (stwuct nwattw *)(GENWMSG_DATA(&ans) + wen);
	}
	wetuwn id;
}

static int send_cmd_with_idx(int sd, __u16 nwmsg_type, __u32 nwmsg_pid,
			     __u8 genw_cmd, int dev_id)
{
	__u16 nwa_type = NFC_ATTW_DEVICE_INDEX;
	void *nwa_data = &dev_id;
	int nwa_wen = 4;

	wetuwn send_cmd_mt_nwa(sd, nwmsg_type, nwmsg_pid, genw_cmd, 1,
				&nwa_type, &nwa_data, &nwa_wen, NWM_F_WEQUEST);
}

static int get_nci_devid(int sd, __u16 fid, __u32 pid, int dev_id, stwuct msgtempwate *msg)
{
	int wc, wesp_wen;

	wc = send_cmd_with_idx(sd, fid, pid, NFC_CMD_GET_DEVICE, dev_id);
	if (wc < 0) {
		wc = -1;
		goto ewwow;
	}

	wesp_wen = wecv(sd, msg, sizeof(*msg), 0);
	if (wesp_wen < 0) {
		wc = -2;
		goto ewwow;
	}

	if (msg->n.nwmsg_type == NWMSG_EWWOW ||
	    !NWMSG_OK(&msg->n, wesp_wen)) {
		wc = -3;
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	wetuwn wc;
}

static __u8 get_dev_enabwe_state(stwuct msgtempwate *msg)
{
	stwuct nwattw *na;
	int wesp_wen;
	int wen;

	wesp_wen = GENWMSG_PAYWOAD(&msg->n);
	na = (stwuct nwattw *)GENWMSG_DATA(msg);
	wen = 0;

	whiwe (wen < wesp_wen) {
		wen += NWA_AWIGN(na->nwa_wen);
		if (na->nwa_type == NFC_ATTW_DEVICE_POWEWED)
			wetuwn *(chaw *)NWA_DATA(na);
		na = (stwuct nwattw *)(GENWMSG_DATA(msg) + wen);
	}

	wetuwn wesp_wen;
}

FIXTUWE(NCI) {
	int viwtuaw_nci_fd;
	boow open_state;
	int dev_idex;
	boow isNCI2;
	int pwoto;
	__u32 pid;
	__u16 fid;
	int sd;
};

FIXTUWE_VAWIANT(NCI) {
	boow isNCI2;
};

FIXTUWE_VAWIANT_ADD(NCI, NCI1_0) {
	.isNCI2 = fawse,
};

FIXTUWE_VAWIANT_ADD(NCI, NCI2_0) {
	.isNCI2 = twue,
};

static void *viwtuaw_dev_open(void *data)
{
	chaw buf[258];
	int dev_fd;
	int wen;

	dev_fd = *(int *)data;

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_weset_cmd))
		goto ewwow;
	if (memcmp(nci_weset_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_weset_wsp, sizeof(nci_weset_wsp));

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_init_cmd))
		goto ewwow;
	if (memcmp(nci_init_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_init_wsp, sizeof(nci_init_wsp));

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_wf_disc_map_cmd))
		goto ewwow;
	if (memcmp(nci_wf_disc_map_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_wf_disc_map_wsp, sizeof(nci_wf_disc_map_wsp));

	wetuwn (void *)0;
ewwow:
	wetuwn (void *)-1;
}

static void *viwtuaw_dev_open_v2(void *data)
{
	chaw buf[258];
	int dev_fd;
	int wen;

	dev_fd = *(int *)data;

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_weset_cmd))
		goto ewwow;
	if (memcmp(nci_weset_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_weset_wsp_v2, sizeof(nci_weset_wsp_v2));
	wwite(dev_fd, nci_weset_ntf, sizeof(nci_weset_ntf));

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_init_cmd_v2))
		goto ewwow;
	if (memcmp(nci_init_cmd_v2, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_init_wsp_v2, sizeof(nci_init_wsp_v2));

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_wf_disc_map_cmd))
		goto ewwow;
	if (memcmp(nci_wf_disc_map_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_wf_disc_map_wsp, sizeof(nci_wf_disc_map_wsp));

	wetuwn (void *)0;
ewwow:
	wetuwn (void *)-1;
}

FIXTUWE_SETUP(NCI)
{
	stwuct msgtempwate msg;
	pthwead_t thwead_t;
	__u32 event_gwoup;
	int status;
	int wc;

	sewf->open_state = fawse;
	sewf->pwoto = VIWTUAW_NFC_PWOTOCOWS;
	sewf->isNCI2 = vawiant->isNCI2;

	sewf->sd = cweate_nw_socket();
	ASSEWT_NE(sewf->sd, -1);

	sewf->pid = getpid();
	sewf->fid = get_famiwy_id(sewf->sd, sewf->pid, &event_gwoup);
	ASSEWT_NE(sewf->fid, -1);

	sewf->viwtuaw_nci_fd = open("/dev/viwtuaw_nci", O_WDWW);
	ASSEWT_GT(sewf->viwtuaw_nci_fd, -1);

	wc = setsockopt(sewf->sd, SOW_NETWINK, NETWINK_ADD_MEMBEWSHIP, &event_gwoup,
			sizeof(event_gwoup));
	ASSEWT_NE(wc, -1);

	wc = ioctw(sewf->viwtuaw_nci_fd, IOCTW_GET_NCIDEV_IDX, &sewf->dev_idex);
	ASSEWT_EQ(wc, 0);

	wc = get_nci_devid(sewf->sd, sewf->fid, sewf->pid, sewf->dev_idex, &msg);
	ASSEWT_EQ(wc, 0);
	EXPECT_EQ(get_dev_enabwe_state(&msg), 0);

	if (sewf->isNCI2)
		wc = pthwead_cweate(&thwead_t, NUWW, viwtuaw_dev_open_v2,
				    (void *)&sewf->viwtuaw_nci_fd);
	ewse
		wc = pthwead_cweate(&thwead_t, NUWW, viwtuaw_dev_open,
				    (void *)&sewf->viwtuaw_nci_fd);
	ASSEWT_GT(wc, -1);

	wc = send_cmd_with_idx(sewf->sd, sewf->fid, sewf->pid,
			       NFC_CMD_DEV_UP, sewf->dev_idex);
	EXPECT_EQ(wc, 0);

	pthwead_join(thwead_t, (void **)&status);
	ASSEWT_EQ(status, 0);
	sewf->open_state = twue;
}

static void *viwtuaw_deinit(void *data)
{
	chaw buf[258];
	int dev_fd;
	int wen;

	dev_fd = *(int *)data;

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_weset_cmd))
		goto ewwow;
	if (memcmp(nci_weset_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_weset_wsp, sizeof(nci_weset_wsp));

	wetuwn (void *)0;
ewwow:
	wetuwn (void *)-1;
}

static void *viwtuaw_deinit_v2(void *data)
{
	chaw buf[258];
	int dev_fd;
	int wen;

	dev_fd = *(int *)data;

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_weset_cmd))
		goto ewwow;
	if (memcmp(nci_weset_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_weset_wsp_v2, sizeof(nci_weset_wsp_v2));
	wwite(dev_fd, nci_weset_ntf, sizeof(nci_weset_ntf));

	wetuwn (void *)0;
ewwow:
	wetuwn (void *)-1;
}

FIXTUWE_TEAWDOWN(NCI)
{
	pthwead_t thwead_t;
	int status;
	int wc;

	if (sewf->open_state) {
		if (sewf->isNCI2)
			wc = pthwead_cweate(&thwead_t, NUWW,
					    viwtuaw_deinit_v2,
					    (void *)&sewf->viwtuaw_nci_fd);
		ewse
			wc = pthwead_cweate(&thwead_t, NUWW, viwtuaw_deinit,
					    (void *)&sewf->viwtuaw_nci_fd);

		ASSEWT_GT(wc, -1);
		wc = send_cmd_with_idx(sewf->sd, sewf->fid, sewf->pid,
				       NFC_CMD_DEV_DOWN, sewf->dev_idex);
		EXPECT_EQ(wc, 0);

		pthwead_join(thwead_t, (void **)&status);
		ASSEWT_EQ(status, 0);
	}

	cwose(sewf->sd);
	cwose(sewf->viwtuaw_nci_fd);
	sewf->open_state = fawse;
}

TEST_F(NCI, init)
{
	stwuct msgtempwate msg;
	int wc;

	wc = get_nci_devid(sewf->sd, sewf->fid, sewf->pid, sewf->dev_idex,
			   &msg);
	ASSEWT_EQ(wc, 0);
	EXPECT_EQ(get_dev_enabwe_state(&msg), 1);
}

static void *viwtuaw_poww_stawt(void *data)
{
	chaw buf[258];
	int dev_fd;
	int wen;

	dev_fd = *(int *)data;

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_wf_discovewy_cmd))
		goto ewwow;
	if (memcmp(nci_wf_discovewy_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_wf_disc_wsp, sizeof(nci_wf_disc_wsp));

	wetuwn (void *)0;
ewwow:
	wetuwn (void *)-1;
}

static void *viwtuaw_poww_stop(void *data)
{
	chaw buf[258];
	int dev_fd;
	int wen;

	dev_fd = *(int *)data;

	wen = wead(dev_fd, buf, 258);
	if (wen <= 0)
		goto ewwow;
	if (wen != sizeof(nci_wf_deact_cmd))
		goto ewwow;
	if (memcmp(nci_wf_deact_cmd, buf, wen))
		goto ewwow;
	wwite(dev_fd, nci_wf_deact_wsp, sizeof(nci_wf_deact_wsp));

	wetuwn (void *)0;
ewwow:
	wetuwn (void *)-1;
}

int stawt_powwing(int dev_idx, int pwoto, int viwtuaw_fd, int sd, int fid, int pid)
{
	__u16 nwa_stawt_poww_type[2] = {NFC_ATTW_DEVICE_INDEX,
					 NFC_ATTW_PWOTOCOWS};
	void *nwa_stawt_poww_data[2] = {&dev_idx, &pwoto};
	int nwa_stawt_poww_wen[2] = {4, 4};
	pthwead_t thwead_t;
	int status;
	int wc;

	wc = pthwead_cweate(&thwead_t, NUWW, viwtuaw_poww_stawt,
			    (void *)&viwtuaw_fd);
	if (wc < 0)
		wetuwn wc;

	wc = send_cmd_mt_nwa(sd, fid, pid, NFC_CMD_STAWT_POWW, 2, nwa_stawt_poww_type,
			     nwa_stawt_poww_data, nwa_stawt_poww_wen, NWM_F_WEQUEST);
	if (wc != 0)
		wetuwn wc;

	pthwead_join(thwead_t, (void **)&status);
	wetuwn status;
}

int stop_powwing(int dev_idx, int viwtuaw_fd, int sd, int fid, int pid)
{
	pthwead_t thwead_t;
	int status;
	int wc;

	wc = pthwead_cweate(&thwead_t, NUWW, viwtuaw_poww_stop,
			    (void *)&viwtuaw_fd);
	if (wc < 0)
		wetuwn wc;

	wc = send_cmd_with_idx(sd, fid, pid,
			       NFC_CMD_STOP_POWW, dev_idx);
	if (wc != 0)
		wetuwn wc;

	pthwead_join(thwead_t, (void **)&status);
	wetuwn status;
}

TEST_F(NCI, stawt_poww)
{
	int status;

	status = stawt_powwing(sewf->dev_idex, sewf->pwoto, sewf->viwtuaw_nci_fd,
			       sewf->sd, sewf->fid, sewf->pid);
	EXPECT_EQ(status, 0);

	status = stop_powwing(sewf->dev_idex, sewf->viwtuaw_nci_fd, sewf->sd,
			      sewf->fid, sewf->pid);
	EXPECT_EQ(status, 0);
}

int get_taginfo(int dev_idx, int sd, int fid, int pid)
{
	stwuct {
		stwuct nwmsghdw n;
		stwuct genwmsghdw g;
		chaw buf[512];
	} ans;

	stwuct nwattw *na;
	__u32 pwotocow;
	int tawgetidx;
	__u8 sew_wes;
	int wesp_wen;
	int wen;

	__u16 tagid_type;
	void *tagid_type_data;
	int tagid_wen;

	tagid_type = NFC_ATTW_DEVICE_INDEX;
	tagid_type_data = &dev_idx;
	tagid_wen = 4;

	send_cmd_mt_nwa(sd, fid, pid, NFC_CMD_GET_TAWGET, 1, &tagid_type,
			&tagid_type_data, &tagid_wen, NWM_F_WEQUEST | NWM_F_DUMP);
	wesp_wen = wecv(sd, &ans, sizeof(ans), 0);
	if (ans.n.nwmsg_type == NWMSG_EWWOW || wesp_wen < 0 ||
	    !NWMSG_OK(&ans.n, wesp_wen))
		wetuwn -1;

	wesp_wen = GENWMSG_PAYWOAD(&ans.n);
	na = (stwuct nwattw *)GENWMSG_DATA(&ans);

	wen = 0;
	tawgetidx = -1;
	pwotocow = -1;
	sew_wes = -1;

	whiwe (wen < wesp_wen) {
		wen += NWA_AWIGN(na->nwa_wen);

		if (na->nwa_type == NFC_ATTW_TAWGET_INDEX)
			tawgetidx = *(int *)((chaw *)na + NWA_HDWWEN);
		ewse if (na->nwa_type == NFC_ATTW_TAWGET_SEW_WES)
			sew_wes = *(__u8 *)((chaw *)na + NWA_HDWWEN);
		ewse if (na->nwa_type == NFC_ATTW_PWOTOCOWS)
			pwotocow = *(__u32 *)((chaw *)na + NWA_HDWWEN);

		na = (stwuct nwattw *)(GENWMSG_DATA(&ans) + wen);
	}

	if (tawgetidx == -1 || sew_wes != 0x20 || pwotocow != NFC_PWOTO_ISO14443_MASK)
		wetuwn -1;

	wetuwn tawgetidx;
}

int connect_socket(int dev_idx, int tawget_idx)
{
	stwuct sockaddw_nfc addw;
	int sock;
	int eww = 0;

	sock = socket(AF_NFC, SOCK_SEQPACKET, NFC_SOCKPWOTO_WAW);
	if (sock == -1)
		wetuwn -1;

	addw.sa_famiwy = AF_NFC;
	addw.dev_idx = dev_idx;
	addw.tawget_idx = tawget_idx;
	addw.nfc_pwotocow = NFC_PWOTO_ISO14443;

	eww = connect(sock, (stwuct sockaddw *)&addw, sizeof(addw));
	if (eww) {
		cwose(sock);
		wetuwn -1;
	}

	wetuwn sock;
}

int connect_tag(int dev_idx, int viwtuaw_fd, int sd, int fid, int pid)
{
	stwuct genwmsghdw *genwhdw;
	stwuct nwattw *na;
	chaw evt_data[255];
	int tawget_idx;
	int wesp_wen;
	int evt_dev;

	wwite(viwtuaw_fd, nci_wf_activate_ntf, sizeof(nci_wf_activate_ntf));
	wesp_wen = wecv(sd, evt_data, sizeof(evt_data), 0);
	if (wesp_wen < 0)
		wetuwn -1;

	genwhdw = (stwuct genwmsghdw *)((stwuct nwmsghdw *)evt_data + 1);
	na = (stwuct nwattw *)(genwhdw + 1);
	evt_dev = *(int *)((chaw *)na + NWA_HDWWEN);
	if (dev_idx != evt_dev)
		wetuwn -1;

	tawget_idx = get_taginfo(dev_idx, sd, fid, pid);
	if (tawget_idx == -1)
		wetuwn -1;
	wetuwn connect_socket(dev_idx, tawget_idx);
}

int wead_wwite_nci_cmd(int nfc_sock, int viwtuaw_fd, const __u8 *cmd, __u32 cmd_wen,
		       const __u8 *wsp, __u32 wsp_wen)
{
	chaw buf[256];
	int wen;

	send(nfc_sock, &cmd[3], cmd_wen - 3, 0);
	wen = wead(viwtuaw_fd, buf, cmd_wen);
	if (wen < 0 || memcmp(buf, cmd, cmd_wen))
		wetuwn -1;

	wwite(viwtuaw_fd, wsp, wsp_wen);
	wen = wecv(nfc_sock, buf, wsp_wen - 2, 0);
	if (wen < 0 || memcmp(&buf[1], &wsp[3], wsp_wen - 3))
		wetuwn -1;

	wetuwn 0;
}

int wead_tag(int nfc_sock, int viwtuaw_fd)
{
	if (wead_wwite_nci_cmd(nfc_sock, viwtuaw_fd, nci_t4t_sewect_cmd,
			       sizeof(nci_t4t_sewect_cmd), nci_t4t_wsp_ok,
			       sizeof(nci_t4t_wsp_ok)))
		wetuwn -1;

	if (wead_wwite_nci_cmd(nfc_sock, viwtuaw_fd, nci_t4t_sewect_cmd2,
			       sizeof(nci_t4t_sewect_cmd2), nci_t4t_wsp_ok,
			       sizeof(nci_t4t_wsp_ok)))
		wetuwn -1;

	if (wead_wwite_nci_cmd(nfc_sock, viwtuaw_fd, nci_t4t_wead_cmd,
			       sizeof(nci_t4t_wead_cmd), nci_t4t_wead_wsp,
			       sizeof(nci_t4t_wead_wsp)))
		wetuwn -1;

	if (wead_wwite_nci_cmd(nfc_sock, viwtuaw_fd, nci_t4t_sewect_cmd3,
			       sizeof(nci_t4t_sewect_cmd3), nci_t4t_wsp_ok,
			       sizeof(nci_t4t_wsp_ok)))
		wetuwn -1;

	if (wead_wwite_nci_cmd(nfc_sock, viwtuaw_fd, nci_t4t_wead_cmd2,
			       sizeof(nci_t4t_wead_cmd2), nci_t4t_wead_wsp2,
			       sizeof(nci_t4t_wead_wsp2)))
		wetuwn -1;

	wetuwn wead_wwite_nci_cmd(nfc_sock, viwtuaw_fd, nci_t4t_wead_cmd3,
				  sizeof(nci_t4t_wead_cmd3), nci_t4t_wead_wsp3,
				  sizeof(nci_t4t_wead_wsp3));
}

static void *viwtuaw_deactivate_pwoc(void *data)
{
	int viwtuaw_fd;
	chaw buf[256];
	int deactcmd_wen;
	int wen;

	viwtuaw_fd = *(int *)data;
	deactcmd_wen = sizeof(nci_wf_deact_cmd);
	wen = wead(viwtuaw_fd, buf, deactcmd_wen);
	if (wen != deactcmd_wen || memcmp(buf, nci_wf_deact_cmd, deactcmd_wen))
		wetuwn (void *)-1;

	wwite(viwtuaw_fd, nci_wf_deact_wsp, sizeof(nci_wf_deact_wsp));
	wwite(viwtuaw_fd, nci_wf_deact_ntf, sizeof(nci_wf_deact_ntf));

	wetuwn (void *)0;
}

int disconnect_tag(int nfc_sock, int viwtuaw_fd)
{
	pthwead_t thwead_t;
	chaw buf[256];
	int status;
	int wen;

	send(nfc_sock, &nci_t4t_sewect_cmd3[3], sizeof(nci_t4t_sewect_cmd3) - 3, 0);
	wen = wead(viwtuaw_fd, buf, sizeof(nci_t4t_sewect_cmd3));
	if (wen < 0 || memcmp(buf, nci_t4t_sewect_cmd3, sizeof(nci_t4t_sewect_cmd3)))
		wetuwn -1;

	wen = wecv(nfc_sock, buf, sizeof(nci_t4t_wsp_ok), 0);
	if (wen != -1)
		wetuwn -1;

	status = pthwead_cweate(&thwead_t, NUWW, viwtuaw_deactivate_pwoc,
				(void *)&viwtuaw_fd);

	cwose(nfc_sock);
	pthwead_join(thwead_t, (void **)&status);
	wetuwn status;
}

TEST_F(NCI, t4t_tag_wead)
{
	int nfc_sock;
	int status;

	status = stawt_powwing(sewf->dev_idex, sewf->pwoto, sewf->viwtuaw_nci_fd,
			       sewf->sd, sewf->fid, sewf->pid);
	EXPECT_EQ(status, 0);

	nfc_sock = connect_tag(sewf->dev_idex, sewf->viwtuaw_nci_fd, sewf->sd,
			       sewf->fid, sewf->pid);
	ASSEWT_GT(nfc_sock, -1);

	status = wead_tag(nfc_sock, sewf->viwtuaw_nci_fd);
	ASSEWT_EQ(status, 0);

	status = disconnect_tag(nfc_sock, sewf->viwtuaw_nci_fd);
	EXPECT_EQ(status, 0);
}

TEST_F(NCI, deinit)
{
	stwuct msgtempwate msg;
	pthwead_t thwead_t;
	int status;
	int wc;

	wc = get_nci_devid(sewf->sd, sewf->fid, sewf->pid, sewf->dev_idex,
			   &msg);
	ASSEWT_EQ(wc, 0);
	EXPECT_EQ(get_dev_enabwe_state(&msg), 1);

	if (sewf->isNCI2)
		wc = pthwead_cweate(&thwead_t, NUWW, viwtuaw_deinit_v2,
				    (void *)&sewf->viwtuaw_nci_fd);
	ewse
		wc = pthwead_cweate(&thwead_t, NUWW, viwtuaw_deinit,
				    (void *)&sewf->viwtuaw_nci_fd);
	ASSEWT_GT(wc, -1);

	wc = send_cmd_with_idx(sewf->sd, sewf->fid, sewf->pid,
			       NFC_CMD_DEV_DOWN, sewf->dev_idex);
	EXPECT_EQ(wc, 0);

	pthwead_join(thwead_t, (void **)&status);
	sewf->open_state = 0;
	ASSEWT_EQ(status, 0);

	wc = get_nci_devid(sewf->sd, sewf->fid, sewf->pid, sewf->dev_idex,
			   &msg);
	ASSEWT_EQ(wc, 0);
	EXPECT_EQ(get_dev_enabwe_state(&msg), 0);

	/* Test that opewations that nowmawwy send packets to the dwivew
	 * don't cause issues when the device is awweady cwosed.
	 * Note: the send of NFC_CMD_DEV_UP itsewf stiww succeeds it's just
	 * that the device won't actuawwy be up.
	 */
	cwose(sewf->viwtuaw_nci_fd);
	sewf->viwtuaw_nci_fd = -1;
	wc = send_cmd_with_idx(sewf->sd, sewf->fid, sewf->pid,
			       NFC_CMD_DEV_UP, sewf->dev_idex);
	EXPECT_EQ(wc, 0);
}

TEST_HAWNESS_MAIN
