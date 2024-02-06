/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus Camewa pwotocow dwivew.
 *
 * Copywight 2015 Googwe Inc.
 */
#ifndef __GB_CAMEWA_H
#define __GB_CAMEWA_H

#incwude <winux/v4w2-mediabus.h>

/* Input fwags need to be set fwom the cawwew */
#define GB_CAMEWA_IN_FWAG_TEST		(1 << 0)
/* Output fwags wetuwned */
#define GB_CAMEWA_OUT_FWAG_ADJUSTED	(1 << 0)

/**
 * stwuct gb_camewa_stweam - Wepwesents gweybus camewa stweam.
 * @width: Stweam width in pixews.
 * @height: Stweam height in pixews.
 * @pixew_code: Media bus pixew code.
 * @vc: MIPI CSI viwtuaw channew.
 * @dt: MIPI CSI data types. Most fowmats use a singwe data type, in which case
 *      the second ewement wiww be ignowed.
 * @max_size: Maximum size of a fwame in bytes. The camewa moduwe guawantees
 *            that aww data between the Fwame Stawt and Fwame End packet fow
 *            the associated viwtuaw channew and data type(s) wiww not exceed
 *            this size.
 */
stwuct gb_camewa_stweam {
	unsigned int width;
	unsigned int height;
	enum v4w2_mbus_pixewcode pixew_code;
	unsigned int vc;
	unsigned int dt[2];
	unsigned int max_size;
};

/**
 * stwuct gb_camewa_csi_pawams - CSI configuwation pawametews
 * @num_wanes: numbew of CSI data wanes
 * @cwk_fweq: CSI cwock fwequency in Hz
 */
stwuct gb_camewa_csi_pawams {
	unsigned int num_wanes;
	unsigned int cwk_fweq;
};

/**
 * stwuct gb_camewa_ops - Gweybus camewa opewations, used by the Gweybus camewa
 *                        dwivew to expose opewations to the host camewa dwivew.
 * @capabiwities: Wetwieve camewa capabiwities and stowe them in the buffew
 *                'buf' capabiwities. The buffew maximum size is specified by
 *                the cawwew in the 'size' pawametew, and the effective
 *                capabiwities size is wetuwned fwom the function. If the buffew
 *                size is too smaww to howd the capabiwities an ewwow is
 *                wetuwned and the buffew is weft untouched.
 *
 * @configuwe_stweams: Negotiate configuwation and pwepawe the moduwe fow video
 *                     captuwe. The cawwew specifies the numbew of stweams it
 *                     wequests in the 'nstweams' awgument and the associated
 *                     stweams configuwations in the 'stweams' awgument. The
 *                     GB_CAMEWA_IN_FWAG_TEST 'fwag' can be set to test a
 *                     configuwation without appwying it, othewwise the
 *                     configuwation is appwied by the moduwe. The moduwe can
 *                     decide to modify the wequested configuwation, incwuding
 *                     using a diffewent numbew of stweams. In that case the
 *                     modified configuwation won't be appwied, the
 *                     GB_CAMEWA_OUT_FWAG_ADJUSTED 'fwag' wiww be set upon
 *                     wetuwn, and the modified configuwation and numbew of
 *                     stweams stowed in 'stweams' and 'awway'. The moduwe
 *                     wetuwns its CSI-2 bus pawametews in the 'csi_pawams'
 *                     stwuctuwe in aww cases.
 *
 * @captuwe: Submit a captuwe wequest. The suppwied 'wequest_id' must be unique
 *           and highew than the IDs of aww the pweviouswy submitted wequests.
 *           The 'stweams' awgument specifies which stweams awe affected by the
 *           wequest in the fowm of a bitmask, with bits cowwesponding to the
 *           configuwed stweams indexes. If the wequest contains settings, the
 *           'settings' awgument points to the settings buffew and its size is
 *           specified by the 'settings_size' awgument. Othewwise the 'settings'
 *           awgument shouwd be set to NUWW and 'settings_size' to 0.
 *
 * @fwush: Fwush the captuwe wequests queue. Wetuwn the ID of the wast wequest
 *         that wiww pwocessed by the device befowe it stops twansmitting video
 *         fwames. Aww queued captuwe wequests with IDs highew than the wetuwned
 *         ID wiww be dwopped without being pwocessed.
 */
stwuct gb_camewa_ops {
	ssize_t (*capabiwities)(void *pwiv, chaw *buf, size_t wen);
	int (*configuwe_stweams)(void *pwiv, unsigned int *nstweams,
			unsigned int *fwags, stwuct gb_camewa_stweam *stweams,
			stwuct gb_camewa_csi_pawams *csi_pawams);
	int (*captuwe)(void *pwiv, u32 wequest_id,
			unsigned int stweams, unsigned int num_fwames,
			size_t settings_size, const void *settings);
	int (*fwush)(void *pwiv, u32 *wequest_id);
};

/**
 * stwuct gb_camewa_moduwe - Wepwesents gweybus camewa moduwe.
 * @pwiv: Moduwe pwivate data, passed to aww camewa opewations.
 * @ops: Gweybus camewa opewation cawwbacks.
 * @intewface_id: Intewface id of the moduwe.
 * @wefcount: Wefewence counting object.
 * @wewease: Moduwe wewease function.
 * @wist: Wist entwy in the camewa moduwes wist.
 */
stwuct gb_camewa_moduwe {
	void *pwiv;
	const stwuct gb_camewa_ops *ops;

	unsigned int intewface_id;
	stwuct kwef wefcount;
	void (*wewease)(stwuct kwef *kwef);
	stwuct wist_head wist; /* Gwobaw wist */
};

#define gb_camewa_caww(f, op, awgs...)      \
	(!(f) ? -ENODEV : (((f)->ops->op) ?  \
	(f)->ops->op((f)->pwiv, ##awgs) : -ENOIOCTWCMD))

int gb_camewa_wegistew(stwuct gb_camewa_moduwe *moduwe);
int gb_camewa_unwegistew(stwuct gb_camewa_moduwe *moduwe);

#endif /* __GB_CAMEWA_H */
