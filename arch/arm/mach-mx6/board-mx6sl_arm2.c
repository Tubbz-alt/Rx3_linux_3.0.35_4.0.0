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

#include <linux/types.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/nodemask.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include <linux/fsl_devices.h>
#include <linux/smsc911x.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#include <linux/i2c.h>
#include <linux/i2c/pca953x.h>
#include <linux/ata.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/mtd/partitions.h>
#include <linux/pmic_external.h>
#include <linux/pmic_status.h>
#include <linux/mxcfb.h>
#include <linux/pwm_backlight.h>
#include <linux/fec.h>
#include <linux/memblock.h>
#include <linux/gpio.h>
#include <linux/etherdevice.h>
#include <linux/regulator/anatop-regulator.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/fixed.h>
#include <linux/mfd/max17135.h>
#include <sound/wm8962.h>
#include <sound/pcm.h>

#include <mach/common.h>
#include <mach/hardware.h>
#include <mach/mxc_dvfs.h>
#include <mach/memory.h>
#include <mach/iomux-mx6sl.h>
#include <mach/imx-uart.h>
#include <mach/viv_gpu.h>

#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#include "usb.h"
#include "devices-imx6q.h"
#include "crm_regs.h"
#include "cpu_op-mx6.h"
#include "board-mx6sl_arm2.h"

#define MX6_ARM2_USBOTG1_PWR    IMX_GPIO_NR(4, 0)       /* KEY_COL4 */
#define MX6_ARM2_USBOTG2_PWR    IMX_GPIO_NR(4, 2)       /* KEY_COL5 */
#define MX6_ARM2_LCD_PWR_EN	IMX_GPIO_NR(4, 3)	/* KEY_ROW5 */
#define MX6_ARM2_SD1_WP		IMX_GPIO_NR(4, 6)	/* KEY_COL7 */
#define MX6_ARM2_SD1_CD		IMX_GPIO_NR(4, 7)	/* KEY_ROW7 */
#define MX6_ARM2_SD2_WP		IMX_GPIO_NR(4, 29)	/* SD2_DAT6 */
#define MX6_ARM2_SD2_CD		IMX_GPIO_NR(5, 0)	/* SD2_DAT7 */
#define MX6_ARM2_SD3_CD		IMX_GPIO_NR(3, 22)	/* REF_CLK_32K */
#define MX6_ARM2_FEC_PWR_EN	IMX_GPIO_NR(4, 21)	/* FEC_TX_CLK */

/* EPDC GPIO pins */
#define MX6SL_ARM2_EPDC_SDDO_0		IMX_GPIO_NR(1, 7)
#define MX6SL_ARM2_EPDC_SDDO_1		IMX_GPIO_NR(1, 8)
#define MX6SL_ARM2_EPDC_SDDO_2		IMX_GPIO_NR(1, 9)
#define MX6SL_ARM2_EPDC_SDDO_3		IMX_GPIO_NR(1, 10)
#define MX6SL_ARM2_EPDC_SDDO_4		IMX_GPIO_NR(1, 11)
#define MX6SL_ARM2_EPDC_SDDO_5		IMX_GPIO_NR(1, 12)
#define MX6SL_ARM2_EPDC_SDDO_6		IMX_GPIO_NR(1, 13)
#define MX6SL_ARM2_EPDC_SDDO_7		IMX_GPIO_NR(1, 14)
#define MX6SL_ARM2_EPDC_SDDO_8		IMX_GPIO_NR(1, 15)
#define MX6SL_ARM2_EPDC_SDDO_9		IMX_GPIO_NR(1, 16)
#define MX6SL_ARM2_EPDC_SDDO_10		IMX_GPIO_NR(1, 17)
#define MX6SL_ARM2_EPDC_SDDO_11		IMX_GPIO_NR(1, 18)
#define MX6SL_ARM2_EPDC_SDDO_12		IMX_GPIO_NR(1, 19)
#define MX6SL_ARM2_EPDC_SDDO_13		IMX_GPIO_NR(1, 20)
#define MX6SL_ARM2_EPDC_SDDO_14		IMX_GPIO_NR(1, 21)
#define MX6SL_ARM2_EPDC_SDDO_15		IMX_GPIO_NR(1, 22)
#define MX6SL_ARM2_EPDC_GDCLK		IMX_GPIO_NR(1, 31)
#define MX6SL_ARM2_EPDC_GDSP		IMX_GPIO_NR(2, 2)
#define MX6SL_ARM2_EPDC_GDOE		IMX_GPIO_NR(2, 0)
#define MX6SL_ARM2_EPDC_GDRL		IMX_GPIO_NR(2, 1)
#define MX6SL_ARM2_EPDC_SDCLK		IMX_GPIO_NR(1, 23)
#define MX6SL_ARM2_EPDC_SDOE		IMX_GPIO_NR(1, 25)
#define MX6SL_ARM2_EPDC_SDLE		IMX_GPIO_NR(1, 24)
#define MX6SL_ARM2_EPDC_SDSHR		IMX_GPIO_NR(1, 26)
#define MX6SL_ARM2_EPDC_PWRCOM		IMX_GPIO_NR(2, 11)
#define MX6SL_ARM2_EPDC_PWRSTAT		IMX_GPIO_NR(2, 13)
#define MX6SL_ARM2_EPDC_PWRCTRL0	IMX_GPIO_NR(2, 7)
#define MX6SL_ARM2_EPDC_PWRCTRL1	IMX_GPIO_NR(2, 8)
#define MX6SL_ARM2_EPDC_PWRCTRL2	IMX_GPIO_NR(2, 9)
#define MX6SL_ARM2_EPDC_PWRCTRL3	IMX_GPIO_NR(2, 10)
#define MX6SL_ARM2_EPDC_BDR0		IMX_GPIO_NR(2, 5)
#define MX6SL_ARM2_EPDC_BDR1		IMX_GPIO_NR(2, 6)
#define MX6SL_ARM2_EPDC_SDCE0		IMX_GPIO_NR(1, 27)
#define MX6SL_ARM2_EPDC_SDCE1		IMX_GPIO_NR(1, 28)
#define MX6SL_ARM2_EPDC_SDCE2		IMX_GPIO_NR(1, 29)
#define MX6SL_ARM2_EPDC_PMIC_WAKE	IMX_GPIO_NR(2, 14) /* EPDC_PWRWAKEUP */
#define MX6SL_ARM2_EPDC_PMIC_INT	IMX_GPIO_NR(2, 12) /* EPDC_PWRINT */
#define MX6SL_ARM2_EPDC_VCOM		IMX_GPIO_NR(2, 3)

static int max17135_regulator_init(struct max17135 *max17135);
extern int __init mx6sl_arm2_init_pfuze100(u32 int_gpio);
static const struct esdhc_platform_data mx6_arm2_sd1_data __initconst = {
	.cd_gpio		= MX6_ARM2_SD1_CD,
	.wp_gpio		= MX6_ARM2_SD1_WP,
	.support_8bit		= 1,
	.keep_power_at_suspend	= 1,
	.delay_line		= 0,
};

static const struct esdhc_platform_data mx6_arm2_sd2_data __initconst = {
	.cd_gpio		= MX6_ARM2_SD2_CD,
	.wp_gpio		= MX6_ARM2_SD2_WP,
	.keep_power_at_suspend	= 1,
	.delay_line		= 0,
};

static const struct esdhc_platform_data mx6_arm2_sd3_data __initconst = {
	.cd_gpio		= MX6_ARM2_SD3_CD,
	.keep_power_at_suspend	= 1,
	.delay_line		= 0,
};

#define mV_to_uV(mV) (mV * 1000)
#define uV_to_mV(uV) (uV / 1000)
#define V_to_uV(V) (mV_to_uV(V * 1000))
#define uV_to_V(uV) (uV_to_mV(uV) / 1000)

static struct regulator_consumer_supply display_consumers[] = {
	{
		/* MAX17135 */
		.supply = "DISPLAY",
	},
};

static struct regulator_consumer_supply vcom_consumers[] = {
	{
		/* MAX17135 */
		.supply = "VCOM",
	},
};

static struct regulator_consumer_supply v3p3_consumers[] = {
	{
		/* MAX17135 */
		.supply = "V3P3",
	},
};

static struct regulator_init_data max17135_init_data[] = {
	{
		.constraints = {
			.name = "DISPLAY",
			.valid_ops_mask =  REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(display_consumers),
		.consumer_supplies = display_consumers,
	}, {
		.constraints = {
			.name = "GVDD",
			.min_uV = V_to_uV(20),
			.max_uV = V_to_uV(20),
		},
	}, {
		.constraints = {
			.name = "GVEE",
			.min_uV = V_to_uV(-22),
			.max_uV = V_to_uV(-22),
		},
	}, {
		.constraints = {
			.name = "HVINN",
			.min_uV = V_to_uV(-22),
			.max_uV = V_to_uV(-22),
		},
	}, {
		.constraints = {
			.name = "HVINP",
			.min_uV = V_to_uV(20),
			.max_uV = V_to_uV(20),
		},
	}, {
		.constraints = {
			.name = "VCOM",
			.min_uV = mV_to_uV(-4325),
			.max_uV = mV_to_uV(-500),
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
			REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(vcom_consumers),
		.consumer_supplies = vcom_consumers,
	}, {
		.constraints = {
			.name = "VNEG",
			.min_uV = V_to_uV(-15),
			.max_uV = V_to_uV(-15),
		},
	}, {
		.constraints = {
			.name = "VPOS",
			.min_uV = V_to_uV(15),
			.max_uV = V_to_uV(15),
		},
	}, {
		.constraints = {
			.name = "V3P3",
			.valid_ops_mask =  REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(v3p3_consumers),
		.consumer_supplies = v3p3_consumers,
	},
};

static struct platform_device max17135_sensor_device = {
	.name = "max17135_sensor",
	.id = 0,
};

static struct max17135_platform_data max17135_pdata __initdata = {
	.vneg_pwrup = 1,
	.gvee_pwrup = 1,
	.vpos_pwrup = 2,
	.gvdd_pwrup = 1,
	.gvdd_pwrdn = 1,
	.vpos_pwrdn = 2,
	.gvee_pwrdn = 1,
	.vneg_pwrdn = 1,
	.gpio_pmic_pwrgood = MX6SL_ARM2_EPDC_PWRSTAT,
	.gpio_pmic_vcom_ctrl = MX6SL_ARM2_EPDC_VCOM,
	.gpio_pmic_wakeup = MX6SL_ARM2_EPDC_PMIC_WAKE,
	.gpio_pmic_v3p3 = MX6SL_ARM2_EPDC_PWRCTRL0,
	.gpio_pmic_intr = MX6SL_ARM2_EPDC_PMIC_INT,
	.regulator_init = max17135_init_data,
	.init = max17135_regulator_init,
};

static int __init max17135_regulator_init(struct max17135 *max17135)
{
	struct max17135_platform_data *pdata = &max17135_pdata;
	int i, ret;

	max17135->gvee_pwrup = pdata->gvee_pwrup;
	max17135->vneg_pwrup = pdata->vneg_pwrup;
	max17135->vpos_pwrup = pdata->vpos_pwrup;
	max17135->gvdd_pwrup = pdata->gvdd_pwrup;
	max17135->gvdd_pwrdn = pdata->gvdd_pwrdn;
	max17135->vpos_pwrdn = pdata->vpos_pwrdn;
	max17135->vneg_pwrdn = pdata->vneg_pwrdn;
	max17135->gvee_pwrdn = pdata->gvee_pwrdn;

	max17135->max_wait = pdata->vpos_pwrup + pdata->vneg_pwrup +
		pdata->gvdd_pwrup + pdata->gvee_pwrup;

	max17135->gpio_pmic_pwrgood = pdata->gpio_pmic_pwrgood;
	max17135->gpio_pmic_vcom_ctrl = pdata->gpio_pmic_vcom_ctrl;
	max17135->gpio_pmic_wakeup = pdata->gpio_pmic_wakeup;
	max17135->gpio_pmic_v3p3 = pdata->gpio_pmic_v3p3;
	max17135->gpio_pmic_intr = pdata->gpio_pmic_intr;

	gpio_request(max17135->gpio_pmic_wakeup, "epdc-pmic-wake");
	gpio_direction_output(max17135->gpio_pmic_wakeup, 0);

	gpio_request(max17135->gpio_pmic_vcom_ctrl, "epdc-vcom");
	gpio_direction_output(max17135->gpio_pmic_vcom_ctrl, 0);

	gpio_request(max17135->gpio_pmic_v3p3, "epdc-v3p3");
	gpio_direction_output(max17135->gpio_pmic_v3p3, 0);

	gpio_request(max17135->gpio_pmic_intr, "epdc-pmic-int");
	gpio_direction_input(max17135->gpio_pmic_intr);

	gpio_request(max17135->gpio_pmic_pwrgood, "epdc-pwrstat");
	gpio_direction_input(max17135->gpio_pmic_pwrgood);

	max17135->vcom_setup = false;
	max17135->init_done = false;

	for (i = 0; i < MAX17135_NUM_REGULATORS; i++) {
		ret = max17135_register_regulator(max17135, i,
			&pdata->regulator_init[i]);
		if (ret != 0) {
			printk(KERN_ERR"max17135 regulator init failed: %d\n",
				ret);
			return ret;
		}
	}

	regulator_has_full_constraints();

	return 0;
}

static struct imxi2c_platform_data mx6_arm2_i2c0_data = {
	.bitrate = 100000,
};

static struct imxi2c_platform_data mx6_arm2_i2c1_data = {
	.bitrate = 100000,
};

static struct imxi2c_platform_data mx6_arm2_i2c2_data = {
	.bitrate = 400000,
};

static struct i2c_board_info mxc_i2c0_board_info[] __initdata = {
	{
		I2C_BOARD_INFO("max17135", 0x48),
		.platform_data = &max17135_pdata,
	},
};

static struct i2c_board_info mxc_i2c1_board_info[] __initdata = {
	{
		I2C_BOARD_INFO("wm8962", 0x1a),
		/*.platform_data = &wm8962_config_data,*/
	},
};

static struct i2c_board_info mxc_i2c2_board_info[] __initdata = {
	{
	},
};

void __init early_console_setup(unsigned long base, struct clk *clk);

static inline void mx6_arm2_init_uart(void)
{
	imx6q_add_imx_uart(0, NULL); /* DEBUG UART1 */

	imx6q_add_sdhci_usdhc_imx(0, &mx6_arm2_sd1_data);
	imx6q_add_sdhci_usdhc_imx(1, &mx6_arm2_sd2_data);
	imx6q_add_sdhci_usdhc_imx(2, &mx6_arm2_sd3_data);
}

static struct fec_platform_data fec_data __initdata = {
	.phy = PHY_INTERFACE_MODE_RMII,
};

static int epdc_get_pins(void)
{
	int ret = 0;

	/* Claim GPIOs for EPDC pins - used during power up/down */
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDDO_0, "epdc_d0");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDDO_1, "epdc_d1");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDDO_2, "epdc_d2");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDDO_3, "epdc_d3");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDDO_4, "epdc_d4");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDDO_5, "epdc_d5");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDDO_6, "epdc_d6");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDDO_7, "epdc_d7");
	ret |= gpio_request(MX6SL_ARM2_EPDC_GDCLK, "epdc_gdclk");
	ret |= gpio_request(MX6SL_ARM2_EPDC_GDSP, "epdc_gdsp");
	ret |= gpio_request(MX6SL_ARM2_EPDC_GDOE, "epdc_gdoe");
	ret |= gpio_request(MX6SL_ARM2_EPDC_GDRL, "epdc_gdrl");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDCLK, "epdc_sdclk");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDOE, "epdc_sdoe");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDLE, "epdc_sdle");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDSHR, "epdc_sdshr");
	ret |= gpio_request(MX6SL_ARM2_EPDC_BDR0, "epdc_bdr0");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDCE0, "epdc_sdce0");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDCE1, "epdc_sdce1");
	ret |= gpio_request(MX6SL_ARM2_EPDC_SDCE2, "epdc_sdce2");

	return ret;
}

static void epdc_put_pins(void)
{
	gpio_free(MX6SL_ARM2_EPDC_SDDO_0);
	gpio_free(MX6SL_ARM2_EPDC_SDDO_1);
	gpio_free(MX6SL_ARM2_EPDC_SDDO_2);
	gpio_free(MX6SL_ARM2_EPDC_SDDO_3);
	gpio_free(MX6SL_ARM2_EPDC_SDDO_4);
	gpio_free(MX6SL_ARM2_EPDC_SDDO_5);
	gpio_free(MX6SL_ARM2_EPDC_SDDO_6);
	gpio_free(MX6SL_ARM2_EPDC_SDDO_7);
	gpio_free(MX6SL_ARM2_EPDC_GDCLK);
	gpio_free(MX6SL_ARM2_EPDC_GDSP);
	gpio_free(MX6SL_ARM2_EPDC_GDOE);
	gpio_free(MX6SL_ARM2_EPDC_GDRL);
	gpio_free(MX6SL_ARM2_EPDC_SDCLK);
	gpio_free(MX6SL_ARM2_EPDC_SDOE);
	gpio_free(MX6SL_ARM2_EPDC_SDLE);
	gpio_free(MX6SL_ARM2_EPDC_SDSHR);
	gpio_free(MX6SL_ARM2_EPDC_BDR0);
	gpio_free(MX6SL_ARM2_EPDC_SDCE0);
	gpio_free(MX6SL_ARM2_EPDC_SDCE1);
	gpio_free(MX6SL_ARM2_EPDC_SDCE2);
}

static void epdc_enable_pins(void)
{
	/* Configure MUX settings to enable EPDC use */
	mxc_iomux_v3_setup_multiple_pads(mx6sl_arm2_epdc_enable_pads, \
				ARRAY_SIZE(mx6sl_arm2_epdc_enable_pads));

	gpio_direction_input(MX6SL_ARM2_EPDC_SDDO_0);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDDO_1);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDDO_2);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDDO_3);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDDO_4);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDDO_5);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDDO_6);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDDO_7);
	gpio_direction_input(MX6SL_ARM2_EPDC_GDCLK);
	gpio_direction_input(MX6SL_ARM2_EPDC_GDSP);
	gpio_direction_input(MX6SL_ARM2_EPDC_GDOE);
	gpio_direction_input(MX6SL_ARM2_EPDC_GDRL);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDCLK);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDOE);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDLE);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDSHR);
	gpio_direction_input(MX6SL_ARM2_EPDC_BDR0);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDCE0);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDCE1);
	gpio_direction_input(MX6SL_ARM2_EPDC_SDCE2);
}

static void epdc_disable_pins(void)
{
	/* Configure MUX settings for EPDC pins to
	 * GPIO and drive to 0. */
	mxc_iomux_v3_setup_multiple_pads(mx6sl_arm2_epdc_disable_pads, \
				ARRAY_SIZE(mx6sl_arm2_epdc_disable_pads));

	gpio_direction_output(MX6SL_ARM2_EPDC_SDDO_0, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDDO_1, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDDO_2, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDDO_3, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDDO_4, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDDO_5, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDDO_6, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDDO_7, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_GDCLK, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_GDSP, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_GDOE, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_GDRL, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDCLK, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDOE, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDLE, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDSHR, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_BDR0, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDCE0, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDCE1, 0);
	gpio_direction_output(MX6SL_ARM2_EPDC_SDCE2, 0);
}

static struct fb_videomode e60_v110_mode = {
	.name = "E60_V110",
	.refresh = 50,
	.xres = 800,
	.yres = 600,
	.pixclock = 18604700,
	.left_margin = 8,
	.right_margin = 178,
	.upper_margin = 4,
	.lower_margin = 10,
	.hsync_len = 20,
	.vsync_len = 4,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};
static struct fb_videomode e60_v220_mode = {
	.name = "E60_V220",
	.refresh = 85,
	.xres = 800,
	.yres = 600,
	.pixclock = 30000000,
	.left_margin = 8,
	.right_margin = 164,
	.upper_margin = 4,
	.lower_margin = 8,
	.hsync_len = 4,
	.vsync_len = 1,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
	.refresh = 85,
	.xres = 800,
	.yres = 600,
};
static struct fb_videomode e060scm_mode = {
	.name = "E060SCM",
	.refresh = 85,
	.xres = 800,
	.yres = 600,
	.pixclock = 26666667,
	.left_margin = 8,
	.right_margin = 100,
	.upper_margin = 4,
	.lower_margin = 8,
	.hsync_len = 4,
	.vsync_len = 1,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};
static struct fb_videomode e97_v110_mode = {
	.name = "E97_V110",
	.refresh = 50,
	.xres = 1200,
	.yres = 825,
	.pixclock = 32000000,
	.left_margin = 12,
	.right_margin = 128,
	.upper_margin = 4,
	.lower_margin = 10,
	.hsync_len = 20,
	.vsync_len = 4,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};

static struct imx_epdc_fb_mode panel_modes[] = {
	{
		&e60_v110_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		428,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		1,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e60_v220_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		465,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		9,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e060scm_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		419,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		5,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e97_v110_mode,
		8,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		632,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		1,      /* gdclk_offs */
		3,      /* num_ce */
	}
};

static struct imx_epdc_fb_platform_data epdc_data = {
	.epdc_mode = panel_modes,
	.num_modes = ARRAY_SIZE(panel_modes),
	.get_pins = epdc_get_pins,
	.put_pins = epdc_put_pins,
	.enable_pins = epdc_enable_pins,
	.disable_pins = epdc_disable_pins,
};

static void imx6_arm2_usbotg_vbus(bool on)
{
	if (on)
		gpio_set_value(MX6_ARM2_USBOTG1_PWR, 1);
	else
		gpio_set_value(MX6_ARM2_USBOTG1_PWR, 0);
}

static void __init mx6_arm2_init_usb(void)
{
	int ret = 0;

	imx_otg_base = MX6_IO_ADDRESS(MX6Q_USB_OTG_BASE_ADDR);

	/* disable external charger detect,
	 * or it will affect signal quality at dp.
	 */

	ret = gpio_request(MX6_ARM2_USBOTG1_PWR, "usbotg-pwr");
	if (ret) {
		pr_err("failed to get GPIO MX6_ARM2_USBOTG1_PWR:%d\n", ret);
		return;
	}
	gpio_direction_output(MX6_ARM2_USBOTG1_PWR, 0);

	ret = gpio_request(MX6_ARM2_USBOTG2_PWR, "usbh1-pwr");
	if (ret) {
		pr_err("failed to get GPIO MX6_ARM2_USBOTG2_PWR:%d\n", ret);
		return;
	}
	gpio_direction_output(MX6_ARM2_USBOTG2_PWR, 1);

	mx6_set_otghost_vbus_func(imx6_arm2_usbotg_vbus);
	mx6_usb_dr_init();
	mx6_usb_h1_init();
#ifdef CONFIG_USB_EHCI_ARC_HSIC
	mx6_usb_h2_init();
#endif
}

static struct platform_pwm_backlight_data mx6_arm2_pwm_backlight_data = {
	.pwm_id		= 0,
	.max_brightness	= 255,
	.dft_brightness	= 128,
	.pwm_period_ns	= 50000,
};
static struct fb_videomode video_modes[] = {
	{
	 /* 800x480 @ 57 Hz , pixel clk @ 32MHz */
	 "SEIKO-WVGA", 60, 800, 480, 29850, 99, 164, 33, 10, 10, 10,
	 FB_SYNC_CLK_LAT_FALL,
	 FB_VMODE_NONINTERLACED,
	 0,},
};

static struct mxc_fb_platform_data fb_data[] = {
	{
	 .interface_pix_fmt = V4L2_PIX_FMT_RGB24,
	 .mode_str = "SEIKO-WVGA",
	 .mode = video_modes,
	 .num_modes = ARRAY_SIZE(video_modes),
	 },
};

static struct platform_device lcd_wvga_device = {
	.name = "lcd_seiko",
};
/*!
 * Board specific initialization.
 */
static void __init mx6_arm2_init(void)
{
	mxc_iomux_v3_setup_multiple_pads(mx6sl_arm2_pads, ARRAY_SIZE(mx6sl_arm2_pads));

	gp_reg_id = "cpu_vddgp";
	mx6_cpu_regulator_init();

	imx6q_add_imx_i2c(0, &mx6_arm2_i2c0_data);
	imx6q_add_imx_i2c(1, &mx6_arm2_i2c1_data);
	i2c_register_board_info(0, mxc_i2c0_board_info,
			ARRAY_SIZE(mxc_i2c0_board_info));
	i2c_register_board_info(1, mxc_i2c1_board_info,
			ARRAY_SIZE(mxc_i2c1_board_info));
	imx6q_add_imx_i2c(2, &mx6_arm2_i2c2_data);
	i2c_register_board_info(2, mxc_i2c2_board_info,
			ARRAY_SIZE(mxc_i2c2_board_info));
	mx6sl_arm2_init_pfuze100(0);

	mx6_arm2_init_uart();
	/* get enet tx reference clk from FEC_REF_CLK pad.
	 * GPR1[14] = 0, GPR1[18:17] = 00
	 */
	mxc_iomux_set_gpr_register(1, 14, 1, 0);
	mxc_iomux_set_gpr_register(1, 17, 2, 0);

	/* power on FEC phy and reset phy */
	gpio_request(MX6_ARM2_FEC_PWR_EN, "fec-pwr");
	gpio_direction_output(MX6_ARM2_FEC_PWR_EN, 1);
	/* wait RC ms for hw reset */
	udelay(500);

	imx6_init_fec(fec_data);

	mx6_arm2_init_usb();

	imx6dl_add_imx_pxp();
	imx6dl_add_imx_pxp_client();

	imx6q_add_mxc_pwm(0);
	imx6q_add_mxc_pwm_backlight(0, &mx6_arm2_pwm_backlight_data);
	imx6dl_add_imx_elcdif(&fb_data[0]);

	gpio_request(MX6_ARM2_LCD_PWR_EN, "elcdif-power-on");
	gpio_direction_output(MX6_ARM2_LCD_PWR_EN, 1);
	mxc_register_device(&lcd_wvga_device, NULL);

	imx6dl_add_imx_pxp();
	imx6dl_add_imx_pxp_client();
	mxc_register_device(&max17135_sensor_device, NULL);
	imx6dl_add_imx_epdc(&epdc_data);
}

extern void __iomem *twd_base;
static void __init mx6_timer_init(void)
{
	struct clk *uart_clk;
#ifdef CONFIG_LOCAL_TIMERS
	twd_base = ioremap(LOCAL_TWD_ADDR, SZ_256);
	BUG_ON(!twd_base);
#endif
	mx6sl_clocks_init(32768, 24000000, 0, 0);

	uart_clk = clk_get_sys("imx-uart.0", NULL);
	early_console_setup(UART1_BASE_ADDR, uart_clk);
}

static struct sys_timer mxc_timer = {
	.init   = mx6_timer_init,
};

static void __init mx6_arm2_reserve(void)
{

}

MACHINE_START(MX6SL_ARM2, "Freescale i.MX 6SoloLite Armadillo2 Board")
	.boot_params	= MX6SL_PHYS_OFFSET + 0x100,
	.map_io		= mx6_map_io,
	.init_irq	= mx6_init_irq,
	.init_machine	= mx6_arm2_init,
	.timer		= &mxc_timer,
	.reserve	= mx6_arm2_reserve,
MACHINE_END
