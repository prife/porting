#ifndef __AM33XX_H__
#define __AM33XX_H__

/** Cache Line size in ARM Cortex-A8.                                         */
#define AM33XX_CACHELINE_SIZE                   (64)

/** @brief Base address of AINTC memory mapped registers                      */
#define AM33XX_AINTC_REGS                       (0x48200000)

/** @brief Base addresses of UART memory mapped registers                     */
#define AM33XX_UART_0_REGS                      (0x44E09000)
#define AM33XX_UART_1_REGS                      (0x48022000)
#define AM33XX_UART_2_REGS                      (0x48024000)
#define AM33XX_UART_3_REGS                      (0x481A6000)
#define AM33XX_UART_4_REGS                      (0x481A8000)
#define AM33XX_UART_5_REGS                      (0x481AA000)

/** @brief Base addresses of USB memory mapped registers                     */
#define AM33XX_USB_0_BASE                       (0x47401400)
#define AM33XX_USB_1_BASE                       (0x47401C00)
/** @brief Base addresses of SPI memory mapped registers                      */
#define AM33XX_SPI_0_REGS                       (0x48030000)
#define AM33XX_SPI_1_REGS                       (0x481A0000)

/** @brief Base addresses of GPIO memory mapped registers                     */
#define AM33XX_GPIO_0_REGS                      (0x44E07000)
#define AM33XX_GPIO_1_REGS                      (0x4804C000)
#define AM33XX_GPIO_2_REGS                      (0x481AC000)
#define AM33XX_GPIO_3_REGS                      (0x481AE000)

/** @brief Base addresses of DMTIMER memory mapped registers                  */
#define AM33XX_DMTIMER_0_REGS                   (0x44E05000)
#define AM33XX_DMTIMER_1_REGS                   (0x44E31000)
#define AM33XX_DMTIMER_2_REGS                   (0x48040000)
#define AM33XX_DMTIMER_3_REGS                   (0x48042000)
#define AM33XX_DMTIMER_4_REGS                   (0x48044000)
#define AM33XX_DMTIMER_5_REGS                   (0x48046000)
#define AM33XX_DMTIMER_6_REGS                   (0x48048000)
#define AM33XX_DMTIMER_7_REGS                   (0x4804A000)

/** @brief Base address of MMC memory mapped registers                        */
#define AM33XX_MMCHS_0_REGS                     (0x48060000)
#define AM33XX_MMCHS_1_REGS                     (0x481D8000)
#define AM33XX_MMCHS_2_REGS                     (0x47810000)

/** @brief Base address of GPMC memory mapped registers                       */
#define AM33XX_GPMC_0_REGS                      (0x50000000)

/** @brief Base address of GPMC memory mapped registers                       */
#define AM33XX_ELM_0_REGS                       (0x48080000)

/** @brief Base address of I2C memory mapped registers                        */
#define AM33XX_I2C_0_REGS                       (0x44E0B000)
#define AM33XX_I2C_1_REGS                       (0x4802A000)
#define AM33XX_I2C_2_REGS                       (0x4819C000)

/** @brief Base address of WDT memory mapped registers                        */
#define AM33XX_WDT_0_REGS                       (0x44E33000)
#define AM33XX_WDT_1_REGS                       (0x44E35000)

/** @brief Base address of WDT memory mapped registers                        */
#define AM33XX_CPSW_SS_REGS                     (0x4A100000)
#define AM33XX_CPSW_MDIO_REGS                   (0x4A101000)
#define AM33XX_CPSW_WR_REGS                     (0x4A101200)
#define AM33XX_CPSW_CPDMA_REGS                  (0x4A100800)
#define AM33XX_CPSW_ALE_REGS                    (0x4A100D00)
#define AM33XX_CPSW_STAT_REGS                   (0x4A100900)
#define AM33XX_CPSW_PORT_0_REGS                 (0x4A100100)
#define AM33XX_CPSW_PORT_1_REGS                 (0x4A100200)
#define AM33XX_CPSW_SLIVER_1_REGS               (0x4A100D80)
#define AM33XX_CPSW_PORT_2_REGS                 (0x4A100300)
#define AM33XX_CPSW_SLIVER_2_REGS               (0x4A100DC0)
#define AM33XX_CPSW_CPPI_RAM_REGS               (0x4A102000)

/** @brief Base address of McASP memory mapped registers                      */
#define AM33XX_MCASP_1_CTRL_REGS                (0x4803C000)
#define AM33XX_MCASP_1_FIFO_REGS                (AM33XX_MCASP_1_CTRL_REGS + 0x1000)
#define AM33XX_MCASP_1_DATA_REGS                (0x46400000)

/** @brief Base address of EMIF memory mapped registers                       */
#define AM33XX_EMIF_0_REGS                      (0x4C000000)

/** @brief Base addresses of RTC memory mapped registers                      */
#define AM33XX_RTC_0_REGS                       (0x44E3E000)

/** @brief Base addresses of PRCM memory mapped registers                     */
#define AM33XX_PRCM_REGS                        (0x44E00000)
#define AM33XX_CM_PER_REGS                      (AM33XX_PRCM_REGS + 0)
#define AM33XX_CM_WKUP_REGS                     (AM33XX_PRCM_REGS + 0x400)
#define AM33XX_CM_DPLL_REGS                     (AM33XX_PRCM_REGS + 0x500)
#define AM33XX_CM_MPU_REGS                      (AM33XX_PRCM_REGS + 0x600)
#define AM33XX_CM_DEVICE_REGS                   (AM33XX_PRCM_REGS + 0x700)
#define AM33XX_CM_RTC_REGS                      (AM33XX_PRCM_REGS + 0x800)
#define AM33XX_CM_GFX_REGS                      (AM33XX_PRCM_REGS + 0x900)
#define AM33XX_CM_CEFUSE_REGS                   (AM33XX_PRCM_REGS + 0xA00)
#define AM33XX_OCP_AM33XXKET_RAM_REGS           (AM33XX_PRCM_REGS + 0xB00)
#define AM33XX_PRM_PER_REGS                     (AM33XX_PRCM_REGS + 0xC00)
#define AM33XX_PRM_WKUP_REGS                    (AM33XX_PRCM_REGS + 0xD00)
#define AM33XX_PRM_MPU_REGS                     (AM33XX_PRCM_REGS + 0xE00)
#define AM33XX_PRM_DEVICE_REGS                  (AM33XX_PRCM_REGS + 0xF00)
#define AM33XX_PRM_RTC_REGS                     (AM33XX_PRCM_REGS + 0x1000)
#define AM33XX_PRM_GFX_REGS                     (AM33XX_PRCM_REGS + 0x1100)
#define AM33XX_PRM_CEFUSE_REGS                  (AM33XX_PRCM_REGS + 0x1200)

/** @brief Base address of control module memory mapped registers             */
#define AM33XX_CONTROL_REGS                     (0x44E10000)


/** @brief Base address of Channel controller  memory mapped registers        */
#define AM33XX_EDMA30CC_0_REGS                  (0x49000000)

/** @brief Base address of DCAN module memory mapped registers                */
#define AM33XX_DCAN_0_REGS                      (0x481CC000) 
#define AM33XX_DCAN_1_REGS                      (0x481D0000) 

/******************************************************************************\
*  Parameterizable Configuration:- These are fed directly from the RTL
*  parameters for the given AM33XX
\******************************************************************************/
#define TPCC_MUX(n)                             0xF90 + ((n) * 4)


#define AM33XX_LCDC_0_REGS                     0x4830E000

#define AM33XX_ADC_TSC_0_REGS                  0x44E0D000

/** @brief Base addresses of PWMSS memory mapped registers.                   */

#define AM33XX_PWMSS0_REGS                     (0x48300000)
#define AM33XX_PWMSS1_REGS                     (0x48302000)
#define AM33XX_PWMSS2_REGS                     (0x48304000)

#define AM33XX_ECAP_REGS                       (0x00000100)
#define AM33XX_EQEP_REGS                       (0x00000180)
#define AM33XX_EPWM_REGS                       (0x00000200)

#define AM33XX_ECAP_0_REGS                     (AM33XX_PWMSS0_REGS + AM33XX_ECAP_REGS)
#define AM33XX_ECAP_1_REGS                     (AM33XX_PWMSS1_REGS + AM33XX_ECAP_REGS)
#define AM33XX_ECAP_2_REGS                     (AM33XX_PWMSS2_REGS + AM33XX_ECAP_REGS)

#define AM33XX_EQEP_0_REGS                     (AM33XX_PWMSS0_REGS + AM33XX_EQEP_REGS)
#define AM33XX_EQEP_1_REGS                     (AM33XX_PWMSS1_REGS + AM33XX_EQEP_REGS)
#define AM33XX_EQEP_2_REGS                     (AM33XX_PWMSS2_REGS + AM33XX_EQEP_REGS) 

#define AM33XX_EPWM_0_REGS                     (AM33XX_PWMSS0_REGS + AM33XX_EPWM_REGS)
#define AM33XX_EPWM_1_REGS                     (AM33XX_PWMSS1_REGS + AM33XX_EPWM_REGS)
#define AM33XX_EPWM_2_REGS                     (AM33XX_PWMSS2_REGS + AM33XX_EPWM_REGS)

#define AM33XX_EPWM_MODULE_FREQ                 100 

#define MMCSD_INT0            16				
#define MMCSD_INT1            17		
		
#define T64P0_INT12           21
#define T64P0_INT34           22
#define T64P1_INT12           23
#define T64P1_INT34           24
#define UART0_INT             25
#define EDMA3_0_TC1_ERRINT    32
#define EMAC_C0RXTHRESH       33
#define EMAC_C0RX             34
#define EMAC_C0TX             35
#define EMAC_C0MISC           36
#define EMAC_C1RXTHRESH       37
#define EMAC_C1RX             38
#define EMAC_C1TX             39
#define EMAC_C1MISC           40
#define DDR2_MEMBERR		  41
#define GPIO_B0INT			  42
#define GPIO_B1INT			  43
#define GPIO_B2INT			  44
#define GPIO_B3INT			  45
#define GPIO_B4INT			  46
#define GPIO_B5INT			  47
#define GPIO_B6INT			  48
#define GPIO_B7INT			  49
#define GPIO_B8INT			  50
#define IIC1_INT			  51
#define LCDC_INT			  52
#define UART1_INT             53
#define UART2_INT             61
#define USB0_INT              58
#define USB1_INT              59
#define T64P2_CMPINT0         74
#define T64P2_CMPINT1         75
#define T64P2_CMPINT2         76
#define T64P2_CMPINT3         77
#define T64P2_CMPINT4         78
#define T64P2_CMPINT5         79
#define T64P2_CMPINT6         80
#define T64P2_CMPINT7         81
#define T64P3_CMPINT0         82
#define T64P3_CMPINT1         83
#define T64P3_CMPINT2         84
#define T64P3_CMPINT3         85
#define T64P3_CMPINT4         86
#define T64P3_CMPINT5         87
#define T64P3_CMPINT6         88
#define T64P3_CMPINT7         89
#define T64P3_ALL             96

struct rt_hw_register
{
	unsigned long r0;
	unsigned long r1;
	unsigned long r2;
	unsigned long r3;
	unsigned long r4;
	unsigned long r5;
	unsigned long r6;
	unsigned long r7;
	unsigned long r8;
	unsigned long r9;
	unsigned long r10;
	unsigned long fp;
	unsigned long ip;
	unsigned long sp;
	unsigned long lr;
	unsigned long pc;
	unsigned long cpsr;
	unsigned long ORIG_r0;
};

#endif
