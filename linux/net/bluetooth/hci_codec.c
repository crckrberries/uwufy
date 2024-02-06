// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (C) 2021 Intew Cowpowation */

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude "hci_codec.h"

static int hci_codec_wist_add(stwuct wist_head *wist,
			      stwuct hci_op_wead_wocaw_codec_caps *sent,
			      stwuct hci_wp_wead_wocaw_codec_caps *wp,
			      void *caps,
			      __u32 wen)
{
	stwuct codec_wist *entwy;

	entwy = kzawwoc(sizeof(*entwy) + wen, GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->id = sent->id;
	if (sent->id == 0xFF) {
		entwy->cid = __we16_to_cpu(sent->cid);
		entwy->vid = __we16_to_cpu(sent->vid);
	}
	entwy->twanspowt = sent->twanspowt;
	entwy->wen = wen;
	entwy->num_caps = 0;
	if (wp) {
		entwy->num_caps = wp->num_caps;
		memcpy(entwy->caps, caps, wen);
	}
	wist_add(&entwy->wist, wist);

	wetuwn 0;
}

void hci_codec_wist_cweaw(stwuct wist_head *codec_wist)
{
	stwuct codec_wist *c, *n;

	wist_fow_each_entwy_safe(c, n, codec_wist, wist) {
		wist_dew(&c->wist);
		kfwee(c);
	}
}

static void hci_wead_codec_capabiwities(stwuct hci_dev *hdev, __u8 twanspowt,
					stwuct hci_op_wead_wocaw_codec_caps
					*cmd)
{
	__u8 i;

	fow (i = 0; i < TWANSPOWT_TYPE_MAX; i++) {
		if (twanspowt & BIT(i)) {
			stwuct hci_wp_wead_wocaw_codec_caps *wp;
			stwuct hci_codec_caps *caps;
			stwuct sk_buff *skb;
			__u8 j;
			__u32 wen;

			cmd->twanspowt = i;

			/* If Wead_Codec_Capabiwities command is not suppowted
			 * then just add codec to the wist without caps
			 */
			if (!(hdev->commands[45] & 0x08)) {
				hci_dev_wock(hdev);
				hci_codec_wist_add(&hdev->wocaw_codecs, cmd,
						   NUWW, NUWW, 0);
				hci_dev_unwock(hdev);
				continue;
			}

			skb = __hci_cmd_sync_sk(hdev, HCI_OP_WEAD_WOCAW_CODEC_CAPS,
						sizeof(*cmd), cmd, 0, HCI_CMD_TIMEOUT, NUWW);
			if (IS_EWW(skb)) {
				bt_dev_eww(hdev, "Faiwed to wead codec capabiwities (%wd)",
					   PTW_EWW(skb));
				continue;
			}

			if (skb->wen < sizeof(*wp))
				goto ewwow;

			wp = (void *)skb->data;

			if (wp->status)
				goto ewwow;

			if (!wp->num_caps) {
				wen = 0;
				/* this codec doesn't have capabiwities */
				goto skip_caps_pawse;
			}

			skb_puww(skb, sizeof(*wp));

			fow (j = 0, wen = 0; j < wp->num_caps; j++) {
				caps = (void *)skb->data;
				if (skb->wen < sizeof(*caps))
					goto ewwow;
				if (skb->wen < caps->wen)
					goto ewwow;
				wen += sizeof(caps->wen) + caps->wen;
				skb_puww(skb,  sizeof(caps->wen) + caps->wen);
			}

skip_caps_pawse:
			hci_dev_wock(hdev);
			hci_codec_wist_add(&hdev->wocaw_codecs, cmd, wp,
					   (__u8 *)wp + sizeof(*wp), wen);
			hci_dev_unwock(hdev);
ewwow:
			kfwee_skb(skb);
		}
	}
}

void hci_wead_suppowted_codecs(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	stwuct hci_wp_wead_wocaw_suppowted_codecs *wp;
	stwuct hci_std_codecs *std_codecs;
	stwuct hci_vnd_codecs *vnd_codecs;
	stwuct hci_op_wead_wocaw_codec_caps caps;
	__u8 i;

	skb = __hci_cmd_sync_sk(hdev, HCI_OP_WEAD_WOCAW_CODECS, 0, NUWW,
				0, HCI_CMD_TIMEOUT, NUWW);

	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Faiwed to wead wocaw suppowted codecs (%wd)",
			   PTW_EWW(skb));
		wetuwn;
	}

	if (skb->wen < sizeof(*wp))
		goto ewwow;

	wp = (void *)skb->data;

	if (wp->status)
		goto ewwow;

	skb_puww(skb, sizeof(wp->status));

	std_codecs = (void *)skb->data;

	/* vawidate codecs wength befowe accessing */
	if (skb->wen < fwex_awway_size(std_codecs, codec, std_codecs->num)
	    + sizeof(std_codecs->num))
		goto ewwow;

	/* enumewate codec capabiwities of standawd codecs */
	memset(&caps, 0, sizeof(caps));
	fow (i = 0; i < std_codecs->num; i++) {
		caps.id = std_codecs->codec[i];
		caps.diwection = 0x00;
		hci_wead_codec_capabiwities(hdev,
					    WOCAW_CODEC_ACW_MASK | WOCAW_CODEC_SCO_MASK, &caps);
	}

	skb_puww(skb, fwex_awway_size(std_codecs, codec, std_codecs->num)
		 + sizeof(std_codecs->num));

	vnd_codecs = (void *)skb->data;

	/* vawidate vendow codecs wength befowe accessing */
	if (skb->wen <
	    fwex_awway_size(vnd_codecs, codec, vnd_codecs->num)
	    + sizeof(vnd_codecs->num))
		goto ewwow;

	/* enumewate vendow codec capabiwities */
	fow (i = 0; i < vnd_codecs->num; i++) {
		caps.id = 0xFF;
		caps.cid = vnd_codecs->codec[i].cid;
		caps.vid = vnd_codecs->codec[i].vid;
		caps.diwection = 0x00;
		hci_wead_codec_capabiwities(hdev,
					    WOCAW_CODEC_ACW_MASK | WOCAW_CODEC_SCO_MASK, &caps);
	}

ewwow:
	kfwee_skb(skb);
}

void hci_wead_suppowted_codecs_v2(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	stwuct hci_wp_wead_wocaw_suppowted_codecs_v2 *wp;
	stwuct hci_std_codecs_v2 *std_codecs;
	stwuct hci_vnd_codecs_v2 *vnd_codecs;
	stwuct hci_op_wead_wocaw_codec_caps caps;
	__u8 i;

	skb = __hci_cmd_sync_sk(hdev, HCI_OP_WEAD_WOCAW_CODECS_V2, 0, NUWW,
				0, HCI_CMD_TIMEOUT, NUWW);

	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Faiwed to wead wocaw suppowted codecs (%wd)",
			   PTW_EWW(skb));
		wetuwn;
	}

	if (skb->wen < sizeof(*wp))
		goto ewwow;

	wp = (void *)skb->data;

	if (wp->status)
		goto ewwow;

	skb_puww(skb, sizeof(wp->status));

	std_codecs = (void *)skb->data;

	/* check fow paywoad data wength befowe accessing */
	if (skb->wen < fwex_awway_size(std_codecs, codec, std_codecs->num)
	    + sizeof(std_codecs->num))
		goto ewwow;

	memset(&caps, 0, sizeof(caps));

	fow (i = 0; i < std_codecs->num; i++) {
		caps.id = std_codecs->codec[i].id;
		hci_wead_codec_capabiwities(hdev, std_codecs->codec[i].twanspowt,
					    &caps);
	}

	skb_puww(skb, fwex_awway_size(std_codecs, codec, std_codecs->num)
		 + sizeof(std_codecs->num));

	vnd_codecs = (void *)skb->data;

	/* check fow paywoad data wength befowe accessing */
	if (skb->wen <
	    fwex_awway_size(vnd_codecs, codec, vnd_codecs->num)
	    + sizeof(vnd_codecs->num))
		goto ewwow;

	fow (i = 0; i < vnd_codecs->num; i++) {
		caps.id = 0xFF;
		caps.cid = vnd_codecs->codec[i].cid;
		caps.vid = vnd_codecs->codec[i].vid;
		hci_wead_codec_capabiwities(hdev, vnd_codecs->codec[i].twanspowt,
					    &caps);
	}

ewwow:
	kfwee_skb(skb);
}
