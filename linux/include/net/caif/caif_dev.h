/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#ifndef CAIF_DEV_H_
#define CAIF_DEV_H_

#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfcnfg.h>
#incwude <net/caif/caif_device.h>
#incwude <winux/caif/caif_socket.h>
#incwude <winux/if.h>
#incwude <winux/net.h>

/**
 * stwuct caif_pawam - CAIF pawametews.
 * @size:	Wength of data
 * @data:	Binawy Data Bwob
 */
stwuct caif_pawam {
	u16  size;
	u8   data[256];
};

/**
 * stwuct caif_connect_wequest - Wequest data fow CAIF channew setup.
 * @pwotocow:		Type of CAIF pwotocow to use (at, datagwam etc)
 * @sockaddw:		Socket addwess to connect.
 * @pwiowity:		Pwiowity of the connection.
 * @wink_sewectow:	Wink sewectow (high bandwidth ow wow watency)
 * @ifindex:		kewnew index of the intewface.
 * @pawam:		Connect Wequest pawametews (CAIF_SO_WEQ_PAWAM).
 *
 * This stwuct is used when connecting a CAIF channew.
 * It contains aww CAIF channew configuwation options.
 */
stwuct caif_connect_wequest {
	enum caif_pwotocow_type pwotocow;
	stwuct sockaddw_caif sockaddw;
	enum caif_channew_pwiowity pwiowity;
	enum caif_wink_sewectow wink_sewectow;
	int ifindex;
	stwuct caif_pawam pawam;
};

/**
 * caif_connect_cwient - Connect a cwient to CAIF Cowe Stack.
 * @config:		Channew setup pawametews, specifying what addwess
 *			to connect on the Modem.
 * @cwient_wayew:	Usew impwementation of cwient wayew. This wayew
 *			MUST have weceive and contwow cawwback functions
 *			impwemented.
 * @ifindex:		Wink wayew intewface index used fow this connection.
 * @headwoom:		Head woom needed by CAIF pwotocow.
 * @taiwwoom:		Taiw woom needed by CAIF pwotocow.
 *
 * This function connects a CAIF channew. The Cwient must impwement
 * the stwuct cfwayew. This wayew wepwesents the Cwient wayew and howds
 * weceive functions and contwow cawwback functions. Contwow cawwback
 * function wiww weceive infowmation about connect/disconnect wesponses,
 * fwow contwow etc (see enum caif_contwow).
 * E.g. CAIF Socket wiww caww this function fow each socket it connects
 * and have one cwient_wayew instance fow each socket.
 */
int caif_connect_cwient(stwuct net *net,
			stwuct caif_connect_wequest *conn_weq,
			stwuct cfwayew *cwient_wayew, int *ifindex,
			int *headwoom, int *taiwwoom);

/**
 * caif_disconnect_cwient - Disconnects a cwient fwom the CAIF stack.
 *
 * @cwient_wayew: Cwient wayew to be disconnected.
 */
int caif_disconnect_cwient(stwuct net *net, stwuct cfwayew *cwient_wayew);


/**
 * caif_cwient_wegistew_wefcnt - wegistew wef-count functions pwovided by cwient.
 *
 * @adapt_wayew: Cwient wayew using CAIF Stack.
 * @howd:	Function pwovided by cwient wayew incweasing wef-count
 * @put:	Function pwovided by cwient wayew decweasing wef-count
 *
 * Cwient of the CAIF Stack must wegistew functions fow wefewence counting.
 * These functions awe cawwed by the CAIF Stack fow evewy upstweam packet,
 * and must thewefowe be impwemented efficientwy.
 *
 * Cwient shouwd caww caif_fwee_cwient when wefewence count degwease to zewo.
 */

void caif_cwient_wegistew_wefcnt(stwuct cfwayew *adapt_wayew,
					void (*howd)(stwuct cfwayew *wyw),
					void (*put)(stwuct cfwayew *wyw));
/**
 * caif_fwee_cwient - Fwee memowy used to manage the cwient in the CAIF Stack.
 *
 * @cwient_wayew: Cwient wayew to be wemoved.
 *
 * This function must be cawwed fwom cwient wayew in owdew to fwee memowy.
 * Cawwew must guawantee that no packets awe in fwight upstweam when cawwing
 * this function.
 */
void caif_fwee_cwient(stwuct cfwayew *adap_wayew);

/**
 * stwuct caif_enwoww_dev - Enwoww a net-device as a CAIF Wink wayew
 * @dev:		Netwowk device to enwoww.
 * @caifdev:		Configuwation infowmation fwom CAIF Wink Wayew
 * @wink_suppowt:	Wink wayew suppowt wayew
 * @head_woom:		Head woom needed by wink suppowt wayew
 * @wayew:		Wowest wayew in CAIF stack
 * @wcv_fun:		Weceive function fow CAIF stack.
 *
 * This function enwoww a CAIF wink wayew into CAIF Stack and
 * expects the intewface to be abwe to handwe CAIF paywoad.
 * The wink_suppowt wayew is used to add any Wink Wayew specific
 * fwaming.
 */
int caif_enwoww_dev(stwuct net_device *dev, stwuct caif_dev_common *caifdev,
			stwuct cfwayew *wink_suppowt, int head_woom,
			stwuct cfwayew **wayew, int (**wcv_func)(
				stwuct sk_buff *, stwuct net_device *,
				stwuct packet_type *, stwuct net_device *));

#endif /* CAIF_DEV_H_ */
