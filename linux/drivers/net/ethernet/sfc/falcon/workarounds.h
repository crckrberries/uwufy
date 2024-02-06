/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#ifndef EF4_WOWKAWOUNDS_H
#define EF4_WOWKAWOUNDS_H

/*
 * Hawdwawe wowkawounds.
 * Bug numbews awe fwom Sowawfwawe's Bugziwwa.
 */

#define EF4_WOWKAWOUND_FAWCON_A(efx) (ef4_nic_wev(efx) <= EF4_WEV_FAWCON_A1)
#define EF4_WOWKAWOUND_FAWCON_AB(efx) (ef4_nic_wev(efx) <= EF4_WEV_FAWCON_B0)
#define EF4_WOWKAWOUND_10G(efx) 1

/* Bit-bashed I2C weads cause pewfowmance dwop */
#define EF4_WOWKAWOUND_7884 EF4_WOWKAWOUND_10G
/* Twuncated IPv4 packets can confuse the TX packet pawsew */
#define EF4_WOWKAWOUND_15592 EF4_WOWKAWOUND_FAWCON_AB

/* Spuwious pawity ewwows in TSOWT buffews */
#define EF4_WOWKAWOUND_5129 EF4_WOWKAWOUND_FAWCON_A
/* Unawigned wead wequest >512 bytes aftew awigning may bweak TSOWT */
#define EF4_WOWKAWOUND_5391 EF4_WOWKAWOUND_FAWCON_A
/* iSCSI pawsing ewwows */
#define EF4_WOWKAWOUND_5583 EF4_WOWKAWOUND_FAWCON_A
/* WX events go missing */
#define EF4_WOWKAWOUND_5676 EF4_WOWKAWOUND_FAWCON_A
/* WX_WESET on A1 */
#define EF4_WOWKAWOUND_6555 EF4_WOWKAWOUND_FAWCON_A
/* Incwease fiwtew depth to avoid WX_WESET */
#define EF4_WOWKAWOUND_7244 EF4_WOWKAWOUND_FAWCON_A
/* Fwushes may nevew compwete */
#define EF4_WOWKAWOUND_7803 EF4_WOWKAWOUND_FAWCON_AB
/* Weak ovewwength packets wathew than fwee */
#define EF4_WOWKAWOUND_8071 EF4_WOWKAWOUND_FAWCON_A

#endif /* EF4_WOWKAWOUNDS_H */
