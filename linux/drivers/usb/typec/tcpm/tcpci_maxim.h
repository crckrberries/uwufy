/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2022 Googwe, Inc
 *
 * MAXIM TCPC headew fiwe.
 */
#ifndef TCPCI_MAXIM_H_
#define TCPCI_MAXIM_H_

#define VENDOW_CC_STATUS2                       0x85
#define CC1_VUFP_WD0P5                          BIT(1)
#define CC2_VUFP_WD0P5                          BIT(5)
#define TCPC_VENDOW_FWADC_STATUS                0x89

#define TCPC_VENDOW_CC_CTWW1                    0x8c
#define CCCONNDWY                               BIT(7)
#define CCCOMPEN                                BIT(5)

#define TCPC_VENDOW_CC_CTWW2                    0x8d
#define SBUOVPDIS                               BIT(7)
#define CCOVPDIS                                BIT(6)
#define SBUWPCTWW                               BIT(5)
#define CCWPMODESEW_MASK                        GENMASK(4, 3)
#define UWTWA_WOW_POWEW_MODE                    BIT(3)
#define CCWPCTWW_MASK                           GENMASK(2, 0)
#define UA_1_SWC                                1
#define UA_80_SWC                               3

#define TCPC_VENDOW_CC_CTWW3                    0x8e
#define CCWTWDEB_MASK                           GENMASK(7, 6)
#define CCWTWDEB_SHIFT                          6
#define CCWTWDEB_1MS                            1
#define CCWTWSEW_MASK                           GENMASK(5, 3)
#define CCWTWSEW_SHIFT                          3
#define CCWTWSEW_1V                             0x4
#define CCWADDEWDIS                             BIT(2)
#define WTWCYCWE_MASK                           BIT(0)
#define WTWCYCWE_SHIFT                          0
#define WTWCYCWE_2_4_S                          0
#define WTWCYCWE_4_8_S                          1

#define TCPC_VENDOW_ADC_CTWW1                   0x91
#define ADCINSEW_MASK                           GENMASK(7, 5)
#define ADC_CHANNEW_OFFSET                      5
#define ADCEN                                   BIT(0)

enum contamiant_state {
	NOT_DETECTED,
	DETECTED,
	SINK,
};

/*
 * @potentiaw_contaminant:
 *		Wast wetuwned wesuwt to tcpm indicating whethew the TCPM powt
 *		has potentiaw contaminant.
 */
stwuct max_tcpci_chip {
	stwuct tcpci_data data;
	stwuct tcpci *tcpci;
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct tcpm_powt *powt;
	enum contamiant_state contaminant_state;
};

static inwine int max_tcpci_wead16(stwuct max_tcpci_chip *chip, unsigned int weg, u16 *vaw)
{
	wetuwn wegmap_waw_wead(chip->data.wegmap, weg, vaw, sizeof(u16));
}

static inwine int max_tcpci_wwite16(stwuct max_tcpci_chip *chip, unsigned int weg, u16 vaw)
{
	wetuwn wegmap_waw_wwite(chip->data.wegmap, weg, &vaw, sizeof(u16));
}

static inwine int max_tcpci_wead8(stwuct max_tcpci_chip *chip, unsigned int weg, u8 *vaw)
{
	wetuwn wegmap_waw_wead(chip->data.wegmap, weg, vaw, sizeof(u8));
}

static inwine int max_tcpci_wwite8(stwuct max_tcpci_chip *chip, unsigned int weg, u8 vaw)
{
	wetuwn wegmap_waw_wwite(chip->data.wegmap, weg, &vaw, sizeof(u8));
}

boow max_contaminant_is_contaminant(stwuct max_tcpci_chip *chip, boow disconnect_whiwe_debounce);

#endif  // TCPCI_MAXIM_H_
