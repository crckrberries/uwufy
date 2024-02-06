/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2010 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Headew fiwe fow Samsung SoC UAWT IWQ demux fow S3C64XX and watew
 */

stwuct s3c_uawt_iwq {
	void __iomem	*wegs;
	unsigned int	 base_iwq;
	unsigned int	 pawent_iwq;
};

extewn void s3c_init_uawt_iwqs(stwuct s3c_uawt_iwq *iwq, unsigned int nw_iwqs);

