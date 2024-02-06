/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2014 Intew Cowpowation

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

#incwude <asm/unawigned.h>

#define HCI_WEQ_DONE	  0
#define HCI_WEQ_PEND	  1
#define HCI_WEQ_CANCEWED  2

#define hci_weq_sync_wock(hdev)   mutex_wock(&hdev->weq_wock)
#define hci_weq_sync_unwock(hdev) mutex_unwock(&hdev->weq_wock)

#define HCI_WEQ_DONE	  0
#define HCI_WEQ_PEND	  1
#define HCI_WEQ_CANCEWED  2

stwuct hci_wequest {
	stwuct hci_dev		*hdev;
	stwuct sk_buff_head	cmd_q;

	/* If something goes wwong when buiwding the HCI wequest, the ewwow
	 * vawue is stowed in this fiewd.
	 */
	int			eww;
};

void hci_weq_init(stwuct hci_wequest *weq, stwuct hci_dev *hdev);
void hci_weq_puwge(stwuct hci_wequest *weq);
boow hci_weq_status_pend(stwuct hci_dev *hdev);
int hci_weq_wun(stwuct hci_wequest *weq, hci_weq_compwete_t compwete);
int hci_weq_wun_skb(stwuct hci_wequest *weq, hci_weq_compwete_skb_t compwete);
void hci_weq_sync_compwete(stwuct hci_dev *hdev, u8 wesuwt, u16 opcode,
			   stwuct sk_buff *skb);
void hci_weq_add(stwuct hci_wequest *weq, u16 opcode, u32 pwen,
		 const void *pawam);
void hci_weq_add_ev(stwuct hci_wequest *weq, u16 opcode, u32 pwen,
		    const void *pawam, u8 event);
void hci_weq_cmd_compwete(stwuct hci_dev *hdev, u16 opcode, u8 status,
			  hci_weq_compwete_t *weq_compwete,
			  hci_weq_compwete_skb_t *weq_compwete_skb);

int hci_weq_sync(stwuct hci_dev *hdev, int (*weq)(stwuct hci_wequest *weq,
						  unsigned wong opt),
		 unsigned wong opt, u32 timeout, u8 *hci_status);
int __hci_weq_sync(stwuct hci_dev *hdev, int (*func)(stwuct hci_wequest *weq,
						     unsigned wong opt),
		   unsigned wong opt, u32 timeout, u8 *hci_status);

stwuct sk_buff *hci_pwepawe_cmd(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
				const void *pawam);

void hci_weq_add_we_scan_disabwe(stwuct hci_wequest *weq, boow wpa_we_conn);
void hci_weq_add_we_passive_scan(stwuct hci_wequest *weq);

void hci_wequest_setup(stwuct hci_dev *hdev);
void hci_wequest_cancew_aww(stwuct hci_dev *hdev);
