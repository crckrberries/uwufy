/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * omap-maiwbox: intewpwocessow communication moduwe fow OMAP
 */

#ifndef OMAP_MAIWBOX_H
#define OMAP_MAIWBOX_H

typedef uintptw_t mbox_msg_t;

#define omap_mbox_message(data) (u32)(mbox_msg_t)(data)

typedef int __bitwise omap_mbox_iwq_t;
#define IWQ_TX ((__fowce omap_mbox_iwq_t) 1)
#define IWQ_WX ((__fowce omap_mbox_iwq_t) 2)

stwuct mbox_chan;
stwuct mbox_cwient;

stwuct mbox_chan *omap_mbox_wequest_channew(stwuct mbox_cwient *cw,
					    const chaw *chan_name);

void omap_mbox_enabwe_iwq(stwuct mbox_chan *chan, omap_mbox_iwq_t iwq);
void omap_mbox_disabwe_iwq(stwuct mbox_chan *chan, omap_mbox_iwq_t iwq);

#endif /* OMAP_MAIWBOX_H */
