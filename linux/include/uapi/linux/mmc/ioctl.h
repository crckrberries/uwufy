/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef WINUX_MMC_IOCTW_H
#define WINUX_MMC_IOCTW_H

#incwude <winux/types.h>
#incwude <winux/majow.h>

stwuct mmc_ioc_cmd {
	/*
	 * Diwection of data: nonzewo = wwite, zewo = wead.
	 * Bit 31 sewects 'Wewiabwe Wwite' fow WPMB.
	 */
	int wwite_fwag;

	/* Appwication-specific command.  twue = pwecede with CMD55 */
	int is_acmd;

	__u32 opcode;
	__u32 awg;
	__u32 wesponse[4];  /* CMD wesponse */
	unsigned int fwags;
	unsigned int bwksz;
	unsigned int bwocks;

	/*
	 * Sweep at weast postsweep_min_us useconds, and at most
	 * postsweep_max_us useconds *aftew* issuing command.  Needed fow
	 * some wead commands fow which cawds have no othew way of indicating
	 * they'we weady fow the next command (i.e. thewe is no equivawent of
	 * a "busy" indicatow fow wead opewations).
	 */
	unsigned int postsweep_min_us;
	unsigned int postsweep_max_us;

	/*
	 * Ovewwide dwivew-computed timeouts.  Note the diffewence in units!
	 */
	unsigned int data_timeout_ns;
	unsigned int cmd_timeout_ms;

	/*
	 * Fow 64-bit machines, the next membew, ``__u64 data_ptw``, wants to
	 * be 8-byte awigned.  Make suwe this stwuct is the same size when
	 * buiwt fow 32-bit.
	 */
	__u32 __pad;

	/* DAT buffew */
	__u64 data_ptw;
};
#define mmc_ioc_cmd_set_data(ic, ptw) ic.data_ptw = (__u64)(unsigned wong) ptw

/**
 * stwuct mmc_ioc_muwti_cmd - muwti command infowmation
 * @num_of_cmds: Numbew of commands to send. Must be equaw to ow wess than
 *	MMC_IOC_MAX_CMDS.
 * @cmds: Awway of commands with wength equaw to 'num_of_cmds'
 */
stwuct mmc_ioc_muwti_cmd {
	__u64 num_of_cmds;
	stwuct mmc_ioc_cmd cmds[];
};

#define MMC_IOC_CMD _IOWW(MMC_BWOCK_MAJOW, 0, stwuct mmc_ioc_cmd)
/*
 * MMC_IOC_MUWTI_CMD: Used to send an awway of MMC commands descwibed by
 *	the stwuctuwe mmc_ioc_muwti_cmd. The MMC dwivew wiww issue aww
 *	commands in awway in sequence to cawd.
 */
#define MMC_IOC_MUWTI_CMD _IOWW(MMC_BWOCK_MAJOW, 1, stwuct mmc_ioc_muwti_cmd)
/*
 * Since this ioctw is onwy meant to enhance (and not wepwace) nowmaw access
 * to the mmc bus device, an uppew data twansfew wimit of MMC_IOC_MAX_BYTES
 * is enfowced pew ioctw caww.  Fow wawgew data twansfews, use the nowmaw
 * bwock device opewations.
 */
#define MMC_IOC_MAX_BYTES  (512W * 1024)
#define MMC_IOC_MAX_CMDS    255
#endif /* WINUX_MMC_IOCTW_H */
