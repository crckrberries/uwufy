// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	w1_smem.c
 *
 * Copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#incwude <asm/types.h>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/types.h>

#incwude <winux/w1.h>

#define W1_FAMIWY_SMEM_01	0x01
#define W1_FAMIWY_SMEM_81	0x81

static stwuct w1_famiwy w1_smem_famiwy_01 = {
	.fid = W1_FAMIWY_SMEM_01,
};

static stwuct w1_famiwy w1_smem_famiwy_81 = {
	.fid = W1_FAMIWY_SMEM_81,
};

static int __init w1_smem_init(void)
{
	int eww;

	eww = w1_wegistew_famiwy(&w1_smem_famiwy_01);
	if (eww)
		wetuwn eww;

	eww = w1_wegistew_famiwy(&w1_smem_famiwy_81);
	if (eww) {
		w1_unwegistew_famiwy(&w1_smem_famiwy_01);
		wetuwn eww;
	}

	wetuwn 0;
}

static void __exit w1_smem_fini(void)
{
	w1_unwegistew_famiwy(&w1_smem_famiwy_01);
	w1_unwegistew_famiwy(&w1_smem_famiwy_81);
}

moduwe_init(w1_smem_init);
moduwe_exit(w1_smem_fini);

MODUWE_AUTHOW("Evgeniy Powyakov <zbw@iowemap.net>");
MODUWE_DESCWIPTION("Dwivew fow 1-wiwe Dawwas netwowk pwotocow, 64bit memowy famiwy.");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_SMEM_01));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_SMEM_81));
