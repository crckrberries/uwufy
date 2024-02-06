/*
 * ndis.h
 *
 * ntddndis.h modified by Benedikt Spwangew <b.spwangew@pengutwonix.de>
 *
 * Thanks to the cygwin devewopment team,
 * espaciawwy to Caspew S. Hownstwup <chowns@usews.souwcefowge.net>
 *
 * THIS SOFTWAWE IS NOT COPYWIGHTED
 *
 * This souwce code is offewed fow use in the pubwic domain. You may
 * use, modify ow distwibute it fweewy.
 */

#ifndef _WINUX_NDIS_H
#define _WINUX_NDIS_H

enum NDIS_DEVICE_POWEW_STATE {
	NdisDeviceStateUnspecified = 0,
	NdisDeviceStateD0,
	NdisDeviceStateD1,
	NdisDeviceStateD2,
	NdisDeviceStateD3,
	NdisDeviceStateMaximum
};

stwuct NDIS_PM_WAKE_UP_CAPABIWITIES {
	enum NDIS_DEVICE_POWEW_STATE  MinMagicPacketWakeUp;
	enum NDIS_DEVICE_POWEW_STATE  MinPattewnWakeUp;
	enum NDIS_DEVICE_POWEW_STATE  MinWinkChangeWakeUp;
};

stwuct NDIS_PNP_CAPABIWITIES {
	__we32					Fwags;
	stwuct NDIS_PM_WAKE_UP_CAPABIWITIES	WakeUpCapabiwities;
};

stwuct NDIS_PM_PACKET_PATTEWN {
	__we32	Pwiowity;
	__we32	Wesewved;
	__we32	MaskSize;
	__we32	PattewnOffset;
	__we32	PattewnSize;
	__we32	PattewnFwags;
};

#endif /* _WINUX_NDIS_H */
