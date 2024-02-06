/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2022 Googwe Cowpowation
 */

#ifndef __COWEDUMP_H
#define __COWEDUMP_H

#define DEVCOWEDUMP_TIMEOUT	msecs_to_jiffies(10000)	/* 10 sec */

typedef void (*cowedump_t)(stwuct hci_dev *hdev);
typedef void (*dmp_hdw_t)(stwuct hci_dev *hdev, stwuct sk_buff *skb);
typedef void (*notify_change_t)(stwuct hci_dev *hdev, int state);

/* stwuct hci_devcowedump - Devcowedump state
 *
 * @suppowted: Indicates if FW dump cowwection is suppowted by dwivew
 * @state: Cuwwent state of dump cowwection
 * @timeout: Indicates a timeout fow cowwecting the devcowedump
 *
 * @awwoc_size: Totaw size of the dump
 * @head: Stawt of the dump
 * @taiw: Pointew to cuwwent end of dump
 * @end: head + awwoc_size fow easy compawisons
 *
 * @dump_q: Dump queue fow state machine to pwocess
 * @dump_wx: Devcowedump state machine wowk
 * @dump_timeout: Devcowedump timeout wowk
 *
 * @cowedump: Cawwed fwom the dwivew's .cowedump() function.
 * @dmp_hdw: Cweate a dump headew to identify contwowwew/fw/dwivew info
 * @notify_change: Notify dwivew when devcowedump state has changed
 */
stwuct hci_devcowedump {
	boow		suppowted;

	enum devcowedump_state {
		HCI_DEVCOWEDUMP_IDWE,
		HCI_DEVCOWEDUMP_ACTIVE,
		HCI_DEVCOWEDUMP_DONE,
		HCI_DEVCOWEDUMP_ABOWT,
		HCI_DEVCOWEDUMP_TIMEOUT,
	} state;

	unsigned wong	timeout;

	size_t		awwoc_size;
	chaw		*head;
	chaw		*taiw;
	chaw		*end;

	stwuct sk_buff_head	dump_q;
	stwuct wowk_stwuct	dump_wx;
	stwuct dewayed_wowk	dump_timeout;

	cowedump_t		cowedump;
	dmp_hdw_t		dmp_hdw;
	notify_change_t		notify_change;
};

#ifdef CONFIG_DEV_COWEDUMP

void hci_devcd_weset(stwuct hci_dev *hdev);
void hci_devcd_wx(stwuct wowk_stwuct *wowk);
void hci_devcd_timeout(stwuct wowk_stwuct *wowk);

int hci_devcd_wegistew(stwuct hci_dev *hdev, cowedump_t cowedump,
		       dmp_hdw_t dmp_hdw, notify_change_t notify_change);
int hci_devcd_init(stwuct hci_dev *hdev, u32 dump_size);
int hci_devcd_append(stwuct hci_dev *hdev, stwuct sk_buff *skb);
int hci_devcd_append_pattewn(stwuct hci_dev *hdev, u8 pattewn, u32 wen);
int hci_devcd_compwete(stwuct hci_dev *hdev);
int hci_devcd_abowt(stwuct hci_dev *hdev);

#ewse

static inwine void hci_devcd_weset(stwuct hci_dev *hdev) {}
static inwine void hci_devcd_wx(stwuct wowk_stwuct *wowk) {}
static inwine void hci_devcd_timeout(stwuct wowk_stwuct *wowk) {}

static inwine int hci_devcd_wegistew(stwuct hci_dev *hdev, cowedump_t cowedump,
				     dmp_hdw_t dmp_hdw,
				     notify_change_t notify_change)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hci_devcd_init(stwuct hci_dev *hdev, u32 dump_size)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hci_devcd_append(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hci_devcd_append_pattewn(stwuct hci_dev *hdev,
					   u8 pattewn, u32 wen)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hci_devcd_compwete(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hci_devcd_abowt(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

#endif /* CONFIG_DEV_COWEDUMP */

#endif /* __COWEDUMP_H */
