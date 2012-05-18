/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _BOARD_MX6SL_ARM2_H
#define _BOARD_MX6SL_ARM2_H
#include <mach/iomux-mx6sl.h>

static iomux_v3_cfg_t mx6sl_arm2_pads[] = {
	/* UART1 */
	MX6SL_PAD_UART1_RXD__UART1_RXD,
	MX6SL_PAD_UART1_TXD__UART1_TXD,

	/* USBOTG ID pin */
	MX6SL_PAD_EPDC_PWRCOM__ANATOP_USBOTG1_ID,

	/* USBOTG POWER GPIO */
	MX6SL_PAD_KEY_COL4__GPIO_4_0,
	MX6SL_PAD_KEY_COL5__GPIO_4_2,
	/* USB OC pin */
	MX6SL_PAD_KEY_ROW4__USB_USBOTG1_OC,
	MX6SL_PAD_ECSPI2_SCLK__USB_USBOTG2_OC,
	/* USB HSIC pin */
	MX6SL_PAD_HSIC_STROBE__USB_H_STROBE,
	MX6SL_PAD_HSIC_DAT__USB_H_DATA,

	/* SD1 */
	MX6SL_PAD_SD1_CLK__USDHC1_CLK,
	MX6SL_PAD_SD1_CMD__USDHC1_CMD,
	MX6SL_PAD_SD1_DAT0__USDHC1_DAT0,
	MX6SL_PAD_SD1_DAT1__USDHC1_DAT1,
	MX6SL_PAD_SD1_DAT2__USDHC1_DAT2,
	MX6SL_PAD_SD1_DAT3__USDHC1_DAT3,
	MX6SL_PAD_SD1_DAT4__USDHC1_DAT4,
	MX6SL_PAD_SD1_DAT5__USDHC1_DAT5,
	MX6SL_PAD_SD1_DAT6__USDHC1_DAT6,
	MX6SL_PAD_SD1_DAT7__USDHC1_DAT7,
	/* SD1 CD & WP */
	MX6SL_PAD_KEY_ROW7__GPIO_4_7,
	MX6SL_PAD_KEY_COL7__GPIO_4_6,
	/* SD2 */
	MX6SL_PAD_SD2_CLK__USDHC2_CLK,
	MX6SL_PAD_SD2_CMD__USDHC2_CMD,
	MX6SL_PAD_SD2_DAT0__USDHC2_DAT0,
	MX6SL_PAD_SD2_DAT1__USDHC2_DAT1,
	MX6SL_PAD_SD2_DAT2__USDHC2_DAT2,
	MX6SL_PAD_SD2_DAT3__USDHC2_DAT3,
	/* SD2 CD & WP */
	MX6SL_PAD_SD2_DAT7__GPIO_5_0,
	MX6SL_PAD_SD2_DAT6__GPIO_4_29,
	/* SD3 */
	MX6SL_PAD_SD3_CLK__USDHC3_CLK,
	MX6SL_PAD_SD3_CMD__USDHC3_CMD,
	MX6SL_PAD_SD3_DAT0__USDHC3_DAT0,
	MX6SL_PAD_SD3_DAT1__USDHC3_DAT1,
	MX6SL_PAD_SD3_DAT2__USDHC3_DAT2,
	MX6SL_PAD_SD3_DAT3__USDHC3_DAT3,
	/* SD3 CD */
	MX6SL_PAD_REF_CLK_32K__GPIO_3_22,

	/* FEC */
	MX6SL_PAD_FEC_MDC__FEC_MDC,
	MX6SL_PAD_FEC_MDIO__FEC_MDIO,
	MX6SL_PAD_FEC_REF_CLK__FEC_REF_OUT, /* clock from anatop */
	MX6SL_PAD_FEC_RX_ER__GPIO_4_19,
	MX6SL_PAD_FEC_CRS_DV__FEC_RX_DV,
	MX6SL_PAD_FEC_RXD0__FEC_RDATA_0,
	MX6SL_PAD_FEC_RXD1__FEC_RDATA_1,
	MX6SL_PAD_FEC_TX_EN__FEC_TX_EN,
	MX6SL_PAD_FEC_TXD0__FEC_TDATA_0,
	MX6SL_PAD_FEC_TXD1__FEC_TDATA_1,
	MX6SL_PAD_FEC_TX_CLK__GPIO_4_21, /* Phy power enable */

	/* I2C */
	MX6SL_PAD_I2C1_SCL__I2C1_SCL,
	MX6SL_PAD_I2C1_SDA__I2C1_SDA,
	MX6SL_PAD_I2C2_SCL__I2C2_SCL,
	MX6SL_PAD_I2C2_SDA__I2C2_SDA,

	/* ECSPI1 */
	MX6SL_PAD_ECSPI1_MISO__ECSPI1_MISO,
	MX6SL_PAD_ECSPI1_MOSI__ECSPI1_MOSI,
	MX6SL_PAD_ECSPI1_SCLK__ECSPI1_SCLK,
	MX6SL_PAD_ECSPI1_SS0__ECSPI1_SS0,
	MX6SL_PAD_ECSPI1_SS0__GPIO_4_11,	/* SS0 */

	/* LCD */
	MX6SL_PAD_LCD_CLK__LCDIF_CLK,
	MX6SL_PAD_LCD_ENABLE__LCDIF_ENABLE,
	MX6SL_PAD_LCD_HSYNC__LCDIF_HSYNC,
	MX6SL_PAD_LCD_VSYNC__LCDIF_VSYNC,
	MX6SL_PAD_LCD_RESET__LCDIF_RESET,
	MX6SL_PAD_LCD_DAT0__LCDIF_DAT_0,
	MX6SL_PAD_LCD_DAT1__LCDIF_DAT_1,
	MX6SL_PAD_LCD_DAT2__LCDIF_DAT_2,
	MX6SL_PAD_LCD_DAT3__LCDIF_DAT_3,
	MX6SL_PAD_LCD_DAT4__LCDIF_DAT_4,
	MX6SL_PAD_LCD_DAT5__LCDIF_DAT_5,
	MX6SL_PAD_LCD_DAT6__LCDIF_DAT_6,
	MX6SL_PAD_LCD_DAT7__LCDIF_DAT_7,
	MX6SL_PAD_LCD_DAT8__LCDIF_DAT_8,
	MX6SL_PAD_LCD_DAT9__LCDIF_DAT_9,
	MX6SL_PAD_LCD_DAT10__LCDIF_DAT_10,
	MX6SL_PAD_LCD_DAT11__LCDIF_DAT_11,
	MX6SL_PAD_LCD_DAT12__LCDIF_DAT_12,
	MX6SL_PAD_LCD_DAT13__LCDIF_DAT_13,
	MX6SL_PAD_LCD_DAT14__LCDIF_DAT_14,
	MX6SL_PAD_LCD_DAT15__LCDIF_DAT_15,
	MX6SL_PAD_LCD_DAT16__LCDIF_DAT_16,
	MX6SL_PAD_LCD_DAT17__LCDIF_DAT_17,
	MX6SL_PAD_LCD_DAT18__LCDIF_DAT_18,
	MX6SL_PAD_LCD_DAT19__LCDIF_DAT_19,
	MX6SL_PAD_LCD_DAT20__LCDIF_DAT_20,
	MX6SL_PAD_LCD_DAT21__LCDIF_DAT_21,
	MX6SL_PAD_LCD_DAT22__LCDIF_DAT_22,
	MX6SL_PAD_LCD_DAT23__LCDIF_DAT_23,
	/* LCD brightness */
	MX6SL_PAD_PWM1__PWM1_PWMO,
	/* LCD power on */
	MX6SL_PAD_KEY_ROW5__GPIO_4_3,
};

static iomux_v3_cfg_t mx6sl_arm2_epdc_enable_pads[] = {
	/* EPDC */
	MX6SL_PAD_EPDC_D0__EPDC_SDDO_0,
	MX6SL_PAD_EPDC_D1__EPDC_SDDO_1,
	MX6SL_PAD_EPDC_D2__EPDC_SDDO_2,
	MX6SL_PAD_EPDC_D3__EPDC_SDDO_3,
	MX6SL_PAD_EPDC_D4__EPDC_SDDO_4,
	MX6SL_PAD_EPDC_D5__EPDC_SDDO_5,
	MX6SL_PAD_EPDC_D6__EPDC_SDDO_6,
	MX6SL_PAD_EPDC_D7__EPDC_SDDO_7,
	MX6SL_PAD_EPDC_D8__EPDC_SDDO_8,
	MX6SL_PAD_EPDC_D9__EPDC_SDDO_9,
	MX6SL_PAD_EPDC_D10__EPDC_SDDO_10,
	MX6SL_PAD_EPDC_D11__EPDC_SDDO_11,
	MX6SL_PAD_EPDC_D12__EPDC_SDDO_12,
	MX6SL_PAD_EPDC_D13__EPDC_SDDO_13,
	MX6SL_PAD_EPDC_D14__EPDC_SDDO_14,
	MX6SL_PAD_EPDC_D15__EPDC_SDDO_15,

	MX6SL_PAD_EPDC_GDCLK__EPDC_GDCLK,
	MX6SL_PAD_EPDC_GDSP__EPDC_GDSP,
	MX6SL_PAD_EPDC_GDOE__EPDC_GDOE,
	MX6SL_PAD_EPDC_GDRL__EPDC_GDRL,
	MX6SL_PAD_EPDC_SDCLK__EPDC_SDCLK,
	MX6SL_PAD_EPDC_SDOE__EPDC_SDOE,
	MX6SL_PAD_EPDC_SDLE__EPDC_SDLE,
	MX6SL_PAD_EPDC_SDSHR__EPDC_SDSHR,
	MX6SL_PAD_EPDC_BDR0__EPDC_BDR_0,
	MX6SL_PAD_EPDC_SDCE0__EPDC_SDCE_0,
	MX6SL_PAD_EPDC_SDCE1__EPDC_SDCE_1,
	MX6SL_PAD_EPDC_SDCE2__EPDC_SDCE_2,

	/* EPD PMIC (Maxim 17135) pins */
	MX6SL_PAD_EPDC_VCOM0__GPIO_2_3,
	MX6SL_PAD_EPDC_PWRSTAT__GPIO_2_13,
	MX6SL_PAD_EPDC_PWRCTRL0__GPIO_2_7,
	MX6SL_PAD_EPDC_PWRWAKEUP__GPIO_2_14,

	MX6SL_PAD_PWM1__CCM_CLKO,
};

static iomux_v3_cfg_t mx6sl_arm2_epdc_disable_pads[] = {
	/* EPDC */
	MX6SL_PAD_EPDC_D0__GPIO_1_7,
	MX6SL_PAD_EPDC_D1__GPIO_1_8,
	MX6SL_PAD_EPDC_D2__GPIO_1_9,
	MX6SL_PAD_EPDC_D3__GPIO_1_10,
	MX6SL_PAD_EPDC_D4__GPIO_1_11,
	MX6SL_PAD_EPDC_D5__GPIO_1_12,
	MX6SL_PAD_EPDC_D6__GPIO_1_13,
	MX6SL_PAD_EPDC_D7__GPIO_1_14,
	MX6SL_PAD_EPDC_D8__GPIO_1_15,
	MX6SL_PAD_EPDC_D9__GPIO_1_16,
	MX6SL_PAD_EPDC_D10__GPIO_1_17,
	MX6SL_PAD_EPDC_D11__GPIO_1_18,
	MX6SL_PAD_EPDC_D12__GPIO_1_19,
	MX6SL_PAD_EPDC_D13__GPIO_1_20,
	MX6SL_PAD_EPDC_D14__GPIO_1_21,
	MX6SL_PAD_EPDC_D15__GPIO_1_22,

	MX6SL_PAD_EPDC_GDCLK__GPIO_1_31,
	MX6SL_PAD_EPDC_GDSP__GPIO_2_2,
	MX6SL_PAD_EPDC_GDOE__GPIO_2_0,
	MX6SL_PAD_EPDC_GDRL__GPIO_2_1,
	MX6SL_PAD_EPDC_SDCLK__GPIO_1_23,
	MX6SL_PAD_EPDC_SDOE__GPIO_1_25,
	MX6SL_PAD_EPDC_SDLE__GPIO_1_24,
	MX6SL_PAD_EPDC_SDSHR__GPIO_1_26,
	MX6SL_PAD_EPDC_BDR0__GPIO_2_5,
	MX6SL_PAD_EPDC_SDCE0__GPIO_1_27,
	MX6SL_PAD_EPDC_SDCE1__GPIO_1_28,
	MX6SL_PAD_EPDC_SDCE2__GPIO_1_29,

	/* EPD PMIC (Maxim 17135) pins */
	MX6SL_PAD_EPDC_VCOM0__GPIO_2_3,
	MX6SL_PAD_EPDC_PWRSTAT__GPIO_2_13,
	MX6SL_PAD_EPDC_PWRCTRL0__GPIO_2_7,
	MX6SL_PAD_EPDC_PWRWAKEUP__GPIO_2_14,
};

#endif
