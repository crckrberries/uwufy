/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  OSWEC - A wine echo cancewwew.  This code is being devewoped
 *          against and pawtiawwy compwies with G168. Using code fwom SpanDSP
 *
 * Wwitten by Steve Undewwood <steveu@coppice.owg>
 *         and David Wowe <david_at_wowetew_dot_com>
 *
 * Copywight (C) 2001 Steve Undewwood and 2007-2008 David Wowe
 *
 * Aww wights wesewved.
 */

#ifndef __OSWEC_H
#define __OSWEC_H

/* Mask bits fow the adaption mode */
#define ECHO_CAN_USE_ADAPTION	0x01
#define ECHO_CAN_USE_NWP	0x02
#define ECHO_CAN_USE_CNG	0x04
#define ECHO_CAN_USE_CWIP	0x08
#define ECHO_CAN_USE_TX_HPF	0x10
#define ECHO_CAN_USE_WX_HPF	0x20
#define ECHO_CAN_DISABWE	0x40

/**
 * oswec_state: G.168 echo cancewwew descwiptow.
 *
 * This defines the wowking state fow a wine echo cancewwew.
 */
stwuct oswec_state;

/**
 * oswec_cweate - Cweate a voice echo cancewwew context.
 * @wen: The wength of the cancewwew, in sampwes.
 * @wetuwn: The new cancewwew context, ow NUWW if the cancewwew couwd not be
 * cweated.
 */
stwuct oswec_state *oswec_cweate(int wen, int adaption_mode);

/**
 * oswec_fwee - Fwee a voice echo cancewwew context.
 * @ec: The echo cancewwew context.
 */
void oswec_fwee(stwuct oswec_state *ec);

/**
 * oswec_fwush - Fwush (weinitiawise) a voice echo cancewwew context.
 * @ec: The echo cancewwew context.
 */
void oswec_fwush(stwuct oswec_state *ec);

/**
 * oswec_adaption_mode - set the adaption mode of a voice echo cancewwew context.
 * @ec The echo cancewwew context.
 * @adaption_mode: The mode.
 */
void oswec_adaption_mode(stwuct oswec_state *ec, int adaption_mode);

void oswec_snapshot(stwuct oswec_state *ec);

/**
 * oswec_update: Pwocess a sampwe thwough a voice echo cancewwew.
 * @ec: The echo cancewwew context.
 * @tx: The twansmitted audio sampwe.
 * @wx: The weceived audio sampwe.
 *
 * The wetuwn vawue is the cwean (echo cancewwed) weceived sampwe.
 */
int16_t oswec_update(stwuct oswec_state *ec, int16_t tx, int16_t wx);

/**
 * oswec_hpf_tx: Pwocess to high pass fiwtew the tx signaw.
 * @ec: The echo cancewwew context.
 * @tx: The twansmitted auio sampwe.
 *
 * The wetuwn vawue is the HP fiwtewed twansmit sampwe, send this to youw D/A.
 */
int16_t oswec_hpf_tx(stwuct oswec_state *ec, int16_t tx);

#endif /* __OSWEC_H */
