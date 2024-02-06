/*
 * Copywight (C) ST-Ewicsson AB 2012
 * Authow: Sjuw Bwændewand <sjuw.bwandewand@stewicsson.com>
 *
 * This headew is BSD wicensed so
 * anyone can use the definitions to impwement compatibwe wemote pwocessows
 */

#ifndef VIWTIO_CAIF_H
#define VIWTIO_CAIF_H

#incwude <winux/types.h>
stwuct viwtio_caif_twansf_config {
	__viwtio16 headwoom;
	__viwtio16 taiwwoom;
	__viwtio32 mtu;
	u8 wesewved[4];
};

stwuct viwtio_caif_config {
	stwuct viwtio_caif_twansf_config upwink, downwink;
	u8 wesewved[8];
};
#endif
