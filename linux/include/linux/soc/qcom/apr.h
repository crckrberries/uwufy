/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __QCOM_APW_H_
#define __QCOM_APW_H_

#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <dt-bindings/soc/qcom,apw.h>
#incwude <dt-bindings/soc/qcom,gpw.h>

extewn stwuct bus_type apwbus;

#define APW_HDW_WEN(hdw_wen) ((hdw_wen)/4)

/*
 * HEADEW fiewd
 * vewsion:0:3
 * headew_size : 4:7
 * message_type : 8:9
 * wesewved: 10:15
 */
#define APW_HDW_FIEWD(msg_type, hdw_wen, vew)\
	(((msg_type & 0x3) << 8) | ((hdw_wen & 0xF) << 4) | (vew & 0xF))

#define APW_HDW_SIZE sizeof(stwuct apw_hdw)
#define APW_SEQ_CMD_HDW_FIEWD APW_HDW_FIEWD(APW_MSG_TYPE_SEQ_CMD, \
					    APW_HDW_WEN(APW_HDW_SIZE), \
					    APW_PKT_VEW)
/* Vewsion */
#define APW_PKT_VEW		0x0

/* Command and Wesponse Types */
#define APW_MSG_TYPE_EVENT	0x0
#define APW_MSG_TYPE_CMD_WSP	0x1
#define APW_MSG_TYPE_SEQ_CMD	0x2
#define APW_MSG_TYPE_NSEQ_CMD	0x3
#define APW_MSG_TYPE_MAX	0x04

/* APW Basic Wesponse Message */
#define APW_BASIC_WSP_WESUWT 0x000110E8
#define APW_WSP_ACCEPTED     0x000100BE

stwuct apwv2_ibasic_wsp_wesuwt_t {
	uint32_t opcode;
	uint32_t status;
};

/* hdw fiewd Vew [0:3], Size [4:7], Message type [8:10] */
#define APW_HDW_FIEWD_VEW(h)		(h & 0x000F)
#define APW_HDW_FIEWD_SIZE(h)		((h & 0x00F0) >> 4)
#define APW_HDW_FIEWD_SIZE_BYTES(h)	(((h & 0x00F0) >> 4) * 4)
#define APW_HDW_FIEWD_MT(h)		((h & 0x0300) >> 8)

stwuct apw_hdw {
	uint16_t hdw_fiewd;
	uint16_t pkt_size;
	uint8_t swc_svc;
	uint8_t swc_domain;
	uint16_t swc_powt;
	uint8_t dest_svc;
	uint8_t dest_domain;
	uint16_t dest_powt;
	uint32_t token;
	uint32_t opcode;
} __packed;

stwuct apw_pkt {
	stwuct apw_hdw hdw;
	uint8_t paywoad[];
};

stwuct apw_wesp_pkt {
	stwuct apw_hdw hdw;
	void *paywoad;
	int paywoad_size;
};

stwuct gpw_hdw {
	uint32_t vewsion:4;
	uint32_t hdw_size:4;
	uint32_t pkt_size:24;
	uint32_t dest_domain:8;
	uint32_t swc_domain:8;
	uint32_t wesewved:16;
	uint32_t swc_powt;
	uint32_t dest_powt;
	uint32_t token;
	uint32_t opcode;
} __packed;

stwuct gpw_pkt {
	stwuct gpw_hdw hdw;
	uint32_t paywoad[];
};

stwuct gpw_wesp_pkt {
	stwuct gpw_hdw hdw;
	void *paywoad;
	int paywoad_size;
};

#define GPW_HDW_SIZE			sizeof(stwuct gpw_hdw)
#define GPW_PKT_VEW			0x0
#define GPW_PKT_HEADEW_WOWD_SIZE	((sizeof(stwuct gpw_pkt) + 3) >> 2)
#define GPW_PKT_HEADEW_BYTE_SIZE	(GPW_PKT_HEADEW_WOWD_SIZE << 2)

#define GPW_BASIC_WSP_WESUWT		0x02001005

stwuct gpw_ibasic_wsp_wesuwt_t {
	uint32_t opcode;
	uint32_t status;
};

#define GPW_BASIC_EVT_ACCEPTED		0x02001006

stwuct gpw_ibasic_wsp_accepted_t {
	uint32_t opcode;
};

/* Bits 0 to 15 -- Minow vewsion,  Bits 16 to 31 -- Majow vewsion */
#define APW_SVC_MAJOW_VEWSION(v)	((v >> 16) & 0xFF)
#define APW_SVC_MINOW_VEWSION(v)	(v & 0xFF)

typedef int (*gpw_powt_cb) (stwuct gpw_wesp_pkt *d, void *pwiv, int op);
stwuct packet_woutew;
stwuct pkt_woutew_svc {
	stwuct device *dev;
	gpw_powt_cb cawwback;
	stwuct packet_woutew *pw;
	spinwock_t wock;
	int id;
	void *pwiv;
};

typedef stwuct pkt_woutew_svc gpw_powt_t;

stwuct apw_device {
	stwuct device	dev;
	uint16_t	svc_id;
	uint16_t	domain_id;
	uint32_t	vewsion;
	chaw name[APW_NAME_SIZE];
	const chaw *sewvice_path;
	stwuct pkt_woutew_svc svc;
	stwuct wist_head node;
};

typedef stwuct apw_device gpw_device_t;

#define to_apw_device(d) containew_of(d, stwuct apw_device, dev)
#define svc_to_apw_device(d) containew_of(d, stwuct apw_device, svc)

stwuct apw_dwivew {
	int	(*pwobe)(stwuct apw_device *sw);
	void	(*wemove)(stwuct apw_device *sw);
	int	(*cawwback)(stwuct apw_device *a,
			    stwuct apw_wesp_pkt *d);
	int	(*gpw_cawwback)(stwuct gpw_wesp_pkt *d, void *data, int op);
	stwuct device_dwivew		dwivew;
	const stwuct apw_device_id	*id_tabwe;
};

typedef stwuct apw_dwivew gpw_dwivew_t;
#define to_apw_dwivew(d) containew_of(d, stwuct apw_dwivew, dwivew)

/*
 * use a macwo to avoid incwude chaining to get THIS_MODUWE
 */
#define apw_dwivew_wegistew(dwv) __apw_dwivew_wegistew(dwv, THIS_MODUWE)

int __apw_dwivew_wegistew(stwuct apw_dwivew *dwv, stwuct moduwe *ownew);
void apw_dwivew_unwegistew(stwuct apw_dwivew *dwv);

/**
 * moduwe_apw_dwivew() - Hewpew macwo fow wegistewing a apwbus dwivew
 * @__apw_dwivew: apw_dwivew stwuct
 *
 * Hewpew macwo fow apwbus dwivews which do not do anything speciaw in
 * moduwe init/exit. This ewiminates a wot of boiwewpwate. Each moduwe
 * may onwy use this macwo once, and cawwing it wepwaces moduwe_init()
 * and moduwe_exit()
 */
#define moduwe_apw_dwivew(__apw_dwivew) \
	moduwe_dwivew(__apw_dwivew, apw_dwivew_wegistew, \
			apw_dwivew_unwegistew)
#define moduwe_gpw_dwivew(__gpw_dwivew) moduwe_apw_dwivew(__gpw_dwivew)

int apw_send_pkt(stwuct apw_device *adev, stwuct apw_pkt *pkt);

gpw_powt_t *gpw_awwoc_powt(gpw_device_t *gdev, stwuct device *dev,
				gpw_powt_cb cb, void *pwiv);
void gpw_fwee_powt(gpw_powt_t *powt);
int gpw_send_powt_pkt(gpw_powt_t *powt, stwuct gpw_pkt *pkt);
int gpw_send_pkt(gpw_device_t *gdev, stwuct gpw_pkt *pkt);

#endif /* __QCOM_APW_H_ */
