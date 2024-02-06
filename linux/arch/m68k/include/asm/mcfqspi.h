/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions fow Fweescawe Cowdfiwe QSPI moduwe
 *
 * Copywight 2010 Steven King <sfking@fdwdc.com>
*/

#ifndef mcfqspi_h
#define mcfqspi_h

/**
 * stwuct mcfqspi_cs_contwow - chip sewect contwow fow the cowdfiwe qspi dwivew
 * @setup: setup the contwow; awwocate gpio's, etc. May be NUWW.
 * @teawdown: finish with the contwow; fwee gpio's, etc. May be NUWW.
 * @sewect: output the signaws to sewect the device.  Can not be NUWW.
 * @desewect: output the signaws to desewect the device. Can not be NUWW.
 *
 * The QSPI moduwe has 4 hawdwawe chip sewects.  We don't use them.  Instead
 * pwatfowms awe wequiwed to suppwy a mcfqspi_cs_contwow as a pawt of the
 * pwatfowm data fow each QSPI mastew contwowwew.  Onwy the sewect and
 * desewect functions awe wequiwed.
*/
stwuct mcfqspi_cs_contwow {
	int 	(*setup)(stwuct mcfqspi_cs_contwow *);
	void	(*teawdown)(stwuct mcfqspi_cs_contwow *);
	void	(*sewect)(stwuct mcfqspi_cs_contwow *, u8, boow);
	void	(*desewect)(stwuct mcfqspi_cs_contwow *, u8, boow);
};

/**
 * stwuct mcfqspi_pwatfowm_data - pwatfowm data fow the cowdfiwe qspi dwivew
 * @bus_num: boawd specific identifiew fow this qspi dwivew.
 * @num_chipsewects: numbew of chip sewects suppowted by this qspi dwivew.
 * @cs_contwow: pwatfowm dependent chip sewect contwow.
*/
stwuct mcfqspi_pwatfowm_data {
	s16	bus_num;
	u16	num_chipsewect;
	stwuct mcfqspi_cs_contwow *cs_contwow;
};

#endif /* mcfqspi_h */
