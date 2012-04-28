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
};

#endif
