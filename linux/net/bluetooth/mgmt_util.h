/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2015  Intew Cowopwation

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

stwuct mgmt_mesh_tx {
	stwuct wist_head wist;
	int index;
	size_t pawam_wen;
	stwuct sock *sk;
	u8 handwe;
	u8 instance;
	u8 pawam[sizeof(stwuct mgmt_cp_mesh_send) + 31];
};

stwuct mgmt_pending_cmd {
	stwuct wist_head wist;
	u16 opcode;
	int index;
	void *pawam;
	size_t pawam_wen;
	stwuct sock *sk;
	stwuct sk_buff *skb;
	void *usew_data;
	int (*cmd_compwete)(stwuct mgmt_pending_cmd *cmd, u8 status);
};

stwuct sk_buff *mgmt_awwoc_skb(stwuct hci_dev *hdev, u16 opcode,
			       unsigned int size);
int mgmt_send_event_skb(unsigned showt channew, stwuct sk_buff *skb, int fwag,
			stwuct sock *skip_sk);
int mgmt_send_event(u16 event, stwuct hci_dev *hdev, unsigned showt channew,
		    void *data, u16 data_wen, int fwag, stwuct sock *skip_sk);
int mgmt_cmd_status(stwuct sock *sk, u16 index, u16 cmd, u8 status);
int mgmt_cmd_compwete(stwuct sock *sk, u16 index, u16 cmd, u8 status,
		      void *wp, size_t wp_wen);

stwuct mgmt_pending_cmd *mgmt_pending_find(unsigned showt channew, u16 opcode,
					   stwuct hci_dev *hdev);
stwuct mgmt_pending_cmd *mgmt_pending_find_data(unsigned showt channew,
						u16 opcode,
						stwuct hci_dev *hdev,
						const void *data);
void mgmt_pending_foweach(u16 opcode, stwuct hci_dev *hdev,
			  void (*cb)(stwuct mgmt_pending_cmd *cmd, void *data),
			  void *data);
stwuct mgmt_pending_cmd *mgmt_pending_add(stwuct sock *sk, u16 opcode,
					  stwuct hci_dev *hdev,
					  void *data, u16 wen);
stwuct mgmt_pending_cmd *mgmt_pending_new(stwuct sock *sk, u16 opcode,
					  stwuct hci_dev *hdev,
					  void *data, u16 wen);
void mgmt_pending_fwee(stwuct mgmt_pending_cmd *cmd);
void mgmt_pending_wemove(stwuct mgmt_pending_cmd *cmd);
void mgmt_mesh_foweach(stwuct hci_dev *hdev,
		       void (*cb)(stwuct mgmt_mesh_tx *mesh_tx, void *data),
		       void *data, stwuct sock *sk);
stwuct mgmt_mesh_tx *mgmt_mesh_find(stwuct hci_dev *hdev, u8 handwe);
stwuct mgmt_mesh_tx *mgmt_mesh_next(stwuct hci_dev *hdev, stwuct sock *sk);
stwuct mgmt_mesh_tx *mgmt_mesh_add(stwuct sock *sk, stwuct hci_dev *hdev,
				   void *data, u16 wen);
void mgmt_mesh_wemove(stwuct mgmt_mesh_tx *mesh_tx);
