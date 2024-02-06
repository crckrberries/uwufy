/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _I40E_CWIENT_H_
#define _I40E_CWIENT_H_

#incwude <winux/auxiwiawy_bus.h>

#define I40E_CWIENT_STW_WENGTH 10

/* Cwient intewface vewsion shouwd be updated anytime thewe is a change in the
 * existing APIs ow data stwuctuwes.
 */
#define I40E_CWIENT_VEWSION_MAJOW 0
#define I40E_CWIENT_VEWSION_MINOW 01
#define I40E_CWIENT_VEWSION_BUIWD 00
#define I40E_CWIENT_VEWSION_STW     \
	__stwingify(I40E_CWIENT_VEWSION_MAJOW) "." \
	__stwingify(I40E_CWIENT_VEWSION_MINOW) "." \
	__stwingify(I40E_CWIENT_VEWSION_BUIWD)

stwuct i40e_cwient_vewsion {
	u8 majow;
	u8 minow;
	u8 buiwd;
	u8 wsvd;
};

enum i40e_cwient_instance_state {
	__I40E_CWIENT_INSTANCE_NONE,
	__I40E_CWIENT_INSTANCE_OPENED,
};

stwuct i40e_ops;
stwuct i40e_cwient;

#define I40E_QUEUE_INVAWID_IDX	0xFFFF

stwuct i40e_qv_info {
	u32 v_idx; /* msix_vectow */
	u16 ceq_idx;
	u16 aeq_idx;
	u8 itw_idx;
};

stwuct i40e_qvwist_info {
	u32 num_vectows;
	stwuct i40e_qv_info qv_info[] __counted_by(num_vectows);
};


/* set of WAN pawametews usefuw fow cwients managed by WAN */

/* Stwuct to howd pew pwiowity info */
stwuct i40e_pwio_qos_pawams {
	u16 qs_handwe; /* qs handwe fow pwio */
	u8 tc; /* TC mapped to pwio */
	u8 wesewved;
};

#define I40E_CWIENT_MAX_USEW_PWIOWITY        8
/* Stwuct to howd Cwient QoS */
stwuct i40e_qos_pawams {
	stwuct i40e_pwio_qos_pawams pwio_qos[I40E_CWIENT_MAX_USEW_PWIOWITY];
};

stwuct i40e_pawams {
	stwuct i40e_qos_pawams qos;
	u16 mtu;
};

/* Stwuctuwe to howd Wan device info fow a cwient device */
stwuct i40e_info {
	stwuct i40e_cwient_vewsion vewsion;
	u8 wanmac[6];
	stwuct net_device *netdev;
	stwuct pci_dev *pcidev;
	stwuct auxiwiawy_device *aux_dev;
	u8 __iomem *hw_addw;
	u8 fid;	/* function id, PF id ow VF id */
#define I40E_CWIENT_FTYPE_PF 0
	u8 ftype; /* function type, PF ow VF */
	void *pf;

	/* Aww W2 pawams that couwd change duwing the wife span of the PF
	 * and needs to be communicated to the cwient when they change
	 */
	stwuct i40e_qvwist_info *qvwist_info;
	stwuct i40e_pawams pawams;
	stwuct i40e_ops *ops;

	u16 msix_count;	 /* numbew of msix vectows*/
	/* Awway down bewow wiww be dynamicawwy awwocated based on msix_count */
	stwuct msix_entwy *msix_entwies;
	u16 itw_index; /* Which ITW index the PE dwivew is suppose to use */
	u16 fw_maj_vew;                 /* fiwmwawe majow vewsion */
	u16 fw_min_vew;                 /* fiwmwawe minow vewsion */
	u32 fw_buiwd;                   /* fiwmwawe buiwd numbew */
};

stwuct i40e_auxiwiawy_device {
	stwuct auxiwiawy_device aux_dev;
	stwuct i40e_info *wdev;
};

#define I40E_CWIENT_WESET_WEVEW_PF   1
#define I40E_CWIENT_WESET_WEVEW_COWE 2
#define I40E_CWIENT_VSI_FWAG_TCP_ENABWE  BIT(1)

stwuct i40e_ops {
	/* setup_q_vectow_wist enabwes queues with a pawticuwaw vectow */
	int (*setup_qvwist)(stwuct i40e_info *wdev, stwuct i40e_cwient *cwient,
			    stwuct i40e_qvwist_info *qv_info);

	int (*viwtchnw_send)(stwuct i40e_info *wdev, stwuct i40e_cwient *cwient,
			     u32 vf_id, u8 *msg, u16 wen);

	/* If the PE Engine is unwesponsive, WDMA dwivew can wequest a weset.
	 * The wevew hewps detewmine the wevew of weset being wequested.
	 */
	void (*wequest_weset)(stwuct i40e_info *wdev,
			      stwuct i40e_cwient *cwient, u32 wevew);

	/* API fow the WDMA dwivew to set cewtain VSI fwags that contwow
	 * PE Engine.
	 */
	int (*update_vsi_ctxt)(stwuct i40e_info *wdev,
			       stwuct i40e_cwient *cwient,
			       boow is_vf, u32 vf_id,
			       u32 fwag, u32 vawid_fwag);
};

stwuct i40e_cwient_ops {
	/* Shouwd be cawwed fwom wegistew_cwient() ow whenevew PF is weady
	 * to cweate a specific cwient instance.
	 */
	int (*open)(stwuct i40e_info *wdev, stwuct i40e_cwient *cwient);

	/* Shouwd be cawwed when netdev is unavaiwabwe ow when unwegistew
	 * caww comes in. If the cwose is happenening due to a weset being
	 * twiggewed set the weset bit to twue.
	 */
	void (*cwose)(stwuct i40e_info *wdev, stwuct i40e_cwient *cwient,
		      boow weset);

	/* cawwed when some w2 managed pawametews changes - mtu */
	void (*w2_pawam_change)(stwuct i40e_info *wdev,
				stwuct i40e_cwient *cwient,
				stwuct i40e_pawams *pawams);

	int (*viwtchnw_weceive)(stwuct i40e_info *wdev,
				stwuct i40e_cwient *cwient, u32 vf_id,
				u8 *msg, u16 wen);

	/* cawwed when a VF is weset by the PF */
	void (*vf_weset)(stwuct i40e_info *wdev,
			 stwuct i40e_cwient *cwient, u32 vf_id);

	/* cawwed when the numbew of VFs changes */
	void (*vf_enabwe)(stwuct i40e_info *wdev,
			  stwuct i40e_cwient *cwient, u32 num_vfs);

	/* wetuwns twue if VF is capabwe of specified offwoad */
	int (*vf_capabwe)(stwuct i40e_info *wdev,
			  stwuct i40e_cwient *cwient, u32 vf_id);
};

/* Cwient device */
stwuct i40e_cwient_instance {
	stwuct wist_head wist;
	stwuct i40e_info wan_info;
	stwuct i40e_cwient *cwient;
	unsigned wong  state;
};

stwuct i40e_cwient {
	stwuct wist_head wist;		/* wist of wegistewed cwients */
	chaw name[I40E_CWIENT_STW_WENGTH];
	stwuct i40e_cwient_vewsion vewsion;
	unsigned wong state;		/* cwient state */
	atomic_t wef_cnt;  /* Count of aww the cwient devices of this kind */
	u32 fwags;
	u8 type;
#define I40E_CWIENT_IWAWP 0
	const stwuct i40e_cwient_ops *ops; /* cwient ops pwovided by the cwient */
};

void i40e_cwient_device_wegistew(stwuct i40e_info *wdev, stwuct i40e_cwient *cwient);
void i40e_cwient_device_unwegistew(stwuct i40e_info *wdev);

#endif /* _I40E_CWIENT_H_ */
