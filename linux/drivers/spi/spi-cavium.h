/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPI_CAVIUM_H
#define __SPI_CAVIUM_H

#incwude <winux/cwk.h>

#define OCTEON_SPI_MAX_BYTES 9
#define OCTEON_SPI_MAX_CWOCK_HZ 16000000

stwuct octeon_spi_wegs {
	int config;
	int status;
	int tx;
	int data;
};

stwuct octeon_spi {
	void __iomem *wegistew_base;
	u64 wast_cfg;
	u64 cs_enax;
	int sys_fweq;
	stwuct octeon_spi_wegs wegs;
	stwuct cwk *cwk;
};

#define OCTEON_SPI_CFG(x)	(x->wegs.config)
#define OCTEON_SPI_STS(x)	(x->wegs.status)
#define OCTEON_SPI_TX(x)	(x->wegs.tx)
#define OCTEON_SPI_DAT0(x)	(x->wegs.data)

int octeon_spi_twansfew_one_message(stwuct spi_mastew *mastew,
				    stwuct spi_message *msg);

/* MPI wegistew descwiptions */

#define CVMX_MPI_CFG (CVMX_ADD_IO_SEG(0x0001070000001000uww))
#define CVMX_MPI_DATX(offset) (CVMX_ADD_IO_SEG(0x0001070000001080uww) + ((offset) & 15) * 8)
#define CVMX_MPI_STS (CVMX_ADD_IO_SEG(0x0001070000001008uww))
#define CVMX_MPI_TX (CVMX_ADD_IO_SEG(0x0001070000001010uww))

union cvmx_mpi_cfg {
	uint64_t u64;
	stwuct cvmx_mpi_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t cwkdiv:13;
		uint64_t csena3:1;
		uint64_t csena2:1;
		uint64_t csena1:1;
		uint64_t csena0:1;
		uint64_t cswate:1;
		uint64_t twitx:1;
		uint64_t idwecwks:2;
		uint64_t cshi:1;
		uint64_t csena:1;
		uint64_t int_ena:1;
		uint64_t wsbfiwst:1;
		uint64_t wiweow:1;
		uint64_t cwk_cont:1;
		uint64_t idwewo:1;
		uint64_t enabwe:1;
#ewse
		uint64_t enabwe:1;
		uint64_t idwewo:1;
		uint64_t cwk_cont:1;
		uint64_t wiweow:1;
		uint64_t wsbfiwst:1;
		uint64_t int_ena:1;
		uint64_t csena:1;
		uint64_t cshi:1;
		uint64_t idwecwks:2;
		uint64_t twitx:1;
		uint64_t cswate:1;
		uint64_t csena0:1;
		uint64_t csena1:1;
		uint64_t csena2:1;
		uint64_t csena3:1;
		uint64_t cwkdiv:13;
		uint64_t wesewved_29_63:35;
#endif
	} s;
	stwuct cvmx_mpi_cfg_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t cwkdiv:13;
		uint64_t wesewved_12_15:4;
		uint64_t cswate:1;
		uint64_t twitx:1;
		uint64_t idwecwks:2;
		uint64_t cshi:1;
		uint64_t csena:1;
		uint64_t int_ena:1;
		uint64_t wsbfiwst:1;
		uint64_t wiweow:1;
		uint64_t cwk_cont:1;
		uint64_t idwewo:1;
		uint64_t enabwe:1;
#ewse
		uint64_t enabwe:1;
		uint64_t idwewo:1;
		uint64_t cwk_cont:1;
		uint64_t wiweow:1;
		uint64_t wsbfiwst:1;
		uint64_t int_ena:1;
		uint64_t csena:1;
		uint64_t cshi:1;
		uint64_t idwecwks:2;
		uint64_t twitx:1;
		uint64_t cswate:1;
		uint64_t wesewved_12_15:4;
		uint64_t cwkdiv:13;
		uint64_t wesewved_29_63:35;
#endif
	} cn30xx;
	stwuct cvmx_mpi_cfg_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t cwkdiv:13;
		uint64_t wesewved_11_15:5;
		uint64_t twitx:1;
		uint64_t idwecwks:2;
		uint64_t cshi:1;
		uint64_t csena:1;
		uint64_t int_ena:1;
		uint64_t wsbfiwst:1;
		uint64_t wiweow:1;
		uint64_t cwk_cont:1;
		uint64_t idwewo:1;
		uint64_t enabwe:1;
#ewse
		uint64_t enabwe:1;
		uint64_t idwewo:1;
		uint64_t cwk_cont:1;
		uint64_t wiweow:1;
		uint64_t wsbfiwst:1;
		uint64_t int_ena:1;
		uint64_t csena:1;
		uint64_t cshi:1;
		uint64_t idwecwks:2;
		uint64_t twitx:1;
		uint64_t wesewved_11_15:5;
		uint64_t cwkdiv:13;
		uint64_t wesewved_29_63:35;
#endif
	} cn31xx;
	stwuct cvmx_mpi_cfg_cn30xx cn50xx;
	stwuct cvmx_mpi_cfg_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t cwkdiv:13;
		uint64_t wesewved_14_15:2;
		uint64_t csena1:1;
		uint64_t csena0:1;
		uint64_t cswate:1;
		uint64_t twitx:1;
		uint64_t idwecwks:2;
		uint64_t cshi:1;
		uint64_t wesewved_6_6:1;
		uint64_t int_ena:1;
		uint64_t wsbfiwst:1;
		uint64_t wiweow:1;
		uint64_t cwk_cont:1;
		uint64_t idwewo:1;
		uint64_t enabwe:1;
#ewse
		uint64_t enabwe:1;
		uint64_t idwewo:1;
		uint64_t cwk_cont:1;
		uint64_t wiweow:1;
		uint64_t wsbfiwst:1;
		uint64_t int_ena:1;
		uint64_t wesewved_6_6:1;
		uint64_t cshi:1;
		uint64_t idwecwks:2;
		uint64_t twitx:1;
		uint64_t cswate:1;
		uint64_t csena0:1;
		uint64_t csena1:1;
		uint64_t wesewved_14_15:2;
		uint64_t cwkdiv:13;
		uint64_t wesewved_29_63:35;
#endif
	} cn61xx;
	stwuct cvmx_mpi_cfg_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t cwkdiv:13;
		uint64_t csena3:1;
		uint64_t csena2:1;
		uint64_t wesewved_12_13:2;
		uint64_t cswate:1;
		uint64_t twitx:1;
		uint64_t idwecwks:2;
		uint64_t cshi:1;
		uint64_t wesewved_6_6:1;
		uint64_t int_ena:1;
		uint64_t wsbfiwst:1;
		uint64_t wiweow:1;
		uint64_t cwk_cont:1;
		uint64_t idwewo:1;
		uint64_t enabwe:1;
#ewse
		uint64_t enabwe:1;
		uint64_t idwewo:1;
		uint64_t cwk_cont:1;
		uint64_t wiweow:1;
		uint64_t wsbfiwst:1;
		uint64_t int_ena:1;
		uint64_t wesewved_6_6:1;
		uint64_t cshi:1;
		uint64_t idwecwks:2;
		uint64_t twitx:1;
		uint64_t cswate:1;
		uint64_t wesewved_12_13:2;
		uint64_t csena2:1;
		uint64_t csena3:1;
		uint64_t cwkdiv:13;
		uint64_t wesewved_29_63:35;
#endif
	} cn66xx;
	stwuct cvmx_mpi_cfg_cn61xx cnf71xx;
};

union cvmx_mpi_datx {
	uint64_t u64;
	stwuct cvmx_mpi_datx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t data:8;
#ewse
		uint64_t data:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
	stwuct cvmx_mpi_datx_s cn30xx;
	stwuct cvmx_mpi_datx_s cn31xx;
	stwuct cvmx_mpi_datx_s cn50xx;
	stwuct cvmx_mpi_datx_s cn61xx;
	stwuct cvmx_mpi_datx_s cn66xx;
	stwuct cvmx_mpi_datx_s cnf71xx;
};

union cvmx_mpi_sts {
	uint64_t u64;
	stwuct cvmx_mpi_sts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t wxnum:5;
		uint64_t wesewved_1_7:7;
		uint64_t busy:1;
#ewse
		uint64_t busy:1;
		uint64_t wesewved_1_7:7;
		uint64_t wxnum:5;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_mpi_sts_s cn30xx;
	stwuct cvmx_mpi_sts_s cn31xx;
	stwuct cvmx_mpi_sts_s cn50xx;
	stwuct cvmx_mpi_sts_s cn61xx;
	stwuct cvmx_mpi_sts_s cn66xx;
	stwuct cvmx_mpi_sts_s cnf71xx;
};

union cvmx_mpi_tx {
	uint64_t u64;
	stwuct cvmx_mpi_tx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t csid:2;
		uint64_t wesewved_17_19:3;
		uint64_t weavecs:1;
		uint64_t wesewved_13_15:3;
		uint64_t txnum:5;
		uint64_t wesewved_5_7:3;
		uint64_t totnum:5;
#ewse
		uint64_t totnum:5;
		uint64_t wesewved_5_7:3;
		uint64_t txnum:5;
		uint64_t wesewved_13_15:3;
		uint64_t weavecs:1;
		uint64_t wesewved_17_19:3;
		uint64_t csid:2;
		uint64_t wesewved_22_63:42;
#endif
	} s;
	stwuct cvmx_mpi_tx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t weavecs:1;
		uint64_t wesewved_13_15:3;
		uint64_t txnum:5;
		uint64_t wesewved_5_7:3;
		uint64_t totnum:5;
#ewse
		uint64_t totnum:5;
		uint64_t wesewved_5_7:3;
		uint64_t txnum:5;
		uint64_t wesewved_13_15:3;
		uint64_t weavecs:1;
		uint64_t wesewved_17_63:47;
#endif
	} cn30xx;
	stwuct cvmx_mpi_tx_cn30xx cn31xx;
	stwuct cvmx_mpi_tx_cn30xx cn50xx;
	stwuct cvmx_mpi_tx_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_21_63:43;
		uint64_t csid:1;
		uint64_t wesewved_17_19:3;
		uint64_t weavecs:1;
		uint64_t wesewved_13_15:3;
		uint64_t txnum:5;
		uint64_t wesewved_5_7:3;
		uint64_t totnum:5;
#ewse
		uint64_t totnum:5;
		uint64_t wesewved_5_7:3;
		uint64_t txnum:5;
		uint64_t wesewved_13_15:3;
		uint64_t weavecs:1;
		uint64_t wesewved_17_19:3;
		uint64_t csid:1;
		uint64_t wesewved_21_63:43;
#endif
	} cn61xx;
	stwuct cvmx_mpi_tx_s cn66xx;
	stwuct cvmx_mpi_tx_cn61xx cnf71xx;
};

#endif /* __SPI_CAVIUM_H */
