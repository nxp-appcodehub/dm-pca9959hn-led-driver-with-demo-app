/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file pca9959.h
 * @brief This file contains the PCA9959 LED driver register definitions, access macros, and
 * device access functions.
 */

#ifndef PCA9959_H_
#define PCA9959_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * @brief The PCA9959 types
 *
 *
 */

/**
 **
 **  @brief The PCA9959 LED driver Internal Register Map.
 */
enum {
	PCA9959_MODE1 = 0x00,
	PCA9959_MODE2 = 0x01,
	PCA9959_EFLAG0 = 0x02,
	PCA9959_EFLAG1 = 0x03,
	PCA9959_EFLAG2 = 0x04,
	PCA9959_EFLAG3 = 0x05,
	PCA9959_EFLAG4 = 0x06,
	PCA9959_EFLAG5 = 0x07,

	PCA9959_GRID_DUR = 0x08,
	PCA9959_GRD_CTL = 0x09,
	PCA9959_SIDE_CTL = 0x0A,
	PCA9959_PAGE_SEL = 0x0B,

	PCA9959_GRID0 = 0x20,
	PCA9959_GRID1 = 0x21,
	PCA9959_GRID2 = 0x22,
	PCA9959_GRID3 = 0x23,
	PCA9959_GRID4 = 0x24,
	PCA9959_GRID5 = 0x25,
	PCA9959_GRID6 = 0x26,
	PCA9959_GRID7 = 0x27,
	PCA9959_GRID8 = 0x28,
	PCA9959_GRID9 = 0x29,
	PCA9959_GRID10 = 0x2A,
	PCA9959_GRID11 = 0x2B,
	PCA9959_GRID12 = 0x2C,
	PCA9959_GRID13 = 0x2D,
	PCA9959_GRID14 = 0x2E,
	PCA9959_GRID15 = 0x2F,
	PCA9959_GRID16 = 0x30,
	PCA9959_GRID17 = 0x31,
	PCA9959_GRID18 = 0x32,
	PCA9959_GRID19 = 0x33,
	PCA9959_GRID20 = 0x34,
	PCA9959_GRID21 = 0x35,
	PCA9959_GRID22 = 0x36,
	PCA9959_GRID23 = 0x37,
	PCA9959_GRID24 = 0x38,
	PCA9959_GRID25 = 0x39,
	PCA9959_GRID26 = 0x3A,
	PCA9959_GRID27 = 0x3B,
	PCA9959_GRID28 = 0x3C,
	PCA9959_GRID29 = 0x3D,
	PCA9959_GRID30 = 0x3E,
	PCA9959_GRID31 = 0x3F,
	PCA9959_GRID32 = 0x40,
	PCA9959_GRID33 = 0x41,
	PCA9959_GRID34 = 0x42,
	PCA9959_GRID35 = 0x43,
	PCA9959_GRID36 = 0x44,
	PCA9959_GRID37 = 0x45,
	PCA9959_GRID38 = 0x46,
	PCA9959_GRID39 = 0x47,
	PCA9959_GRID40 = 0x48,
	PCA9959_GRID41 = 0x49,
	PCA9959_GRID42 = 0x4A,
	PCA9959_GRID43 = 0x4B,
	PCA9959_GRID44 = 0x4C,
	PCA9959_GRID45 = 0x4D,
	PCA9959_GRID46 = 0x4E,
	PCA9959_GRID47 = 0x4F,
	PCA9959_GRID48 = 0x50,
	PCA9959_GRID49 = 0x51,
	PCA9959_GRID50 = 0x52,
	PCA9959_GRID51 = 0x53,
	PCA9959_GRID52 = 0x54,
	PCA9959_GRID53 = 0x55,
	PCA9959_GRID54 = 0x56,
	PCA9959_GRID55 = 0x57,
	PCA9959_GRID56 = 0x58,
	PCA9959_GRID57 = 0x59,
	PCA9959_GRID58 = 0x5A,
	PCA9959_GRID59 = 0x5B,
	PCA9959_GRID60 = 0x5B,
	PCA9959_GRID61 = 0x5C,
	PCA9959_GRID62 = 0x5D,
	PCA9959_GRID63 = 0x5E,
	PCA9959_GRID64 = 0x5F,

	PCA9959_CH0_CFG1 = 0x20,
	PCA9959_CH0_CFG2 = 0x21,
	PCA9959_CH0_CFG3 = 0x22,
	PCA9959_CH0_CFG4 = 0x23,

	PCA9959_CH1_CFG1 = 0x24,
	PCA9959_CH1_CFG2 = 0x25,
	PCA9959_CH1_CFG3 = 0x26,
	PCA9959_CH1_CFG4 = 0x27,

	PCA9959_CH2_CFG1 = 0x28,
	PCA9959_CH2_CFG2 = 0x29,
	PCA9959_CH2_CFG3 = 0x2A,
	PCA9959_CH2_CFG4 = 0x2B,

	PCA9959_CH3_CFG1 = 0x2C,
	PCA9959_CH3_CFG2 = 0x2D,
	PCA9959_CH3_CFG3 = 0x2E,
	PCA9959_CH3_CFG4 = 0x2F,

	PCA9959_CH4_CFG1 = 0x30,
	PCA9959_CH4_CFG2 = 0x31,
	PCA9959_CH4_CFG3 = 0x32,
	PCA9959_CH4_CFG4 = 0x33,

	PCA9959_CH5_CFG1 = 0x34,
	PCA9959_CH5_CFG2 = 0x35,
	PCA9959_CH5_CFG3 = 0x36,
	PCA9959_CH5_CFG4 = 0x37,

	PCA9959_CH6_CFG1 = 0x38,
	PCA9959_CH6_CFG2 = 0x39,
	PCA9959_CH6_CFG3 = 0x3A,
	PCA9959_CH6_CFG4 = 0x3B,

	PCA9959_CH7_CFG1 = 0x3C,
	PCA9959_CH7_CFG2 = 0x3D,
	PCA9959_CH7_CFG3 = 0x3E,
	PCA9959_CH7_CFG4 = 0x3F,

	PCA9959_CH8_CFG1 = 0x40,
	PCA9959_CH8_CFG2 = 0x41,
	PCA9959_CH8_CFG3 = 0x42,
	PCA9959_CH8_CFG4 = 0x43,

	PCA9959_CH9_CFG1 = 0x44,
	PCA9959_CH9_CFG2 = 0x45,
	PCA9959_CH9_CFG3 = 0x46,
	PCA9959_CH9_CFG4 = 0x47,

	PCA9959_CH10_CFG1 = 0x48,
	PCA9959_CH10_CFG2 = 0x49,
	PCA9959_CH10_CFG3 = 0x4A,
	PCA9959_CH10_CFG4 = 0x4B,

	PCA9959_CH11_CFG1 = 0x4C,
	PCA9959_CH11_CFG2 = 0x4D,
	PCA9959_CH11_CFG3 = 0x4E,
	PCA9959_CH11_CFG4 = 0x4F,

	PCA9959_CH12_CFG1 = 0x50,
	PCA9959_CH12_CFG2 = 0x51,
	PCA9959_CH12_CFG3 = 0x52,
	PCA9959_CH12_CFG4 = 0x53,

	PCA9959_CH13_CFG1 = 0x54,
	PCA9959_CH13_CFG2 = 0x55,
	PCA9959_CH13_CFG3 = 0x56,
	PCA9959_CH13_CFG4 = 0x57,

	PCA9959_CH14_CFG1 = 0x58,
	PCA9959_CH14_CFG2 = 0x59,
	PCA9959_CH14_CFG3 = 0x5A,
	PCA9959_CH14_CFG4 = 0x5B,

	PCA9959_CH15_CFG1 = 0x5C,
	PCA9959_CH15_CFG2 = 0x5D,
	PCA9959_CH15_CFG3 = 0x5E,
	PCA9959_CH15_CFG4 = 0x5F,

	PCA9959_CH16_CFG1 = 0x60,
	PCA9959_CH16_CFG2 = 0x61,
	PCA9959_CH16_CFG3 = 0x62,
	PCA9959_CH16_CFG4 = 0x63,

	PCA9959_CH17_CFG1 = 0x64,
	PCA9959_CH17_CFG2 = 0x65,
	PCA9959_CH17_CFG3 = 0x66,
	PCA9959_CH17_CFG4 = 0x67,

	PCA9959_CH18_CFG1 = 0x68,
	PCA9959_CH18_CFG2 = 0x69,
	PCA9959_CH18_CFG3 = 0x6A,
	PCA9959_CH18_CFG4 = 0x6B,

	PCA9959_CH19_CFG1 = 0x6C,
	PCA9959_CH19_CFG2 = 0x6D,
	PCA9959_CH19_CFG3 = 0x6E,
	PCA9959_CH19_CFG4 = 0x6F,

	PCA9959_CH20_CFG1 = 0x70,
	PCA9959_CH20_CFG2 = 0x71,
	PCA9959_CH20_CFG3 = 0x72,
	PCA9959_CH20_CFG4 = 0x73,

	PCA9959_CH21_CFG1 = 0x74,
	PCA9959_CH21_CFG2 = 0x75,
	PCA9959_CH21_CFG3 = 0x76,
	PCA9959_CH21_CFG4 = 0x77,

	PCA9959_CH22_CFG1 = 0x78,
	PCA9959_CH22_CFG2 = 0x79,
	PCA9959_CH22_CFG3 = 0x7A,
	PCA9959_CH22_CFG4 = 0x7B,

	PCA9959_CH23_CFG1 = 0x7C,
	PCA9959_CH23_CFG2 = 0x7D,
	PCA9959_CH23_CFG3 = 0x7E,
	PCA9959_CH23_CFG4 = 0x7F,

};

/*--------------------------------
 ** Register: MODE1
 ** Enum: PCA9959_MODE1
 ** --
 ** Offset : 0x00 Mode register 1.
 ** ------------------------------*/
typedef union {
	struct {
		uint8_t _reserved_0 :1; /*  Reserved Bit (Unused)  */

		uint8_t _reserved_1 :1; /*  Reserved Bit (Unused)  */

		uint8_t clk20m_type :1; /*  clock for gradation control  */

		uint8_t offset_dis :1; /*  50ns delay offset between channel(x) and channel(x+1)  */

		uint8_t sleep :1; /*   Low-power/Normal mode  */

		uint8_t _reserved_2 :1; /*  Reserved Bit (Unused)  */

		uint8_t _reserved_3 :1; /*  Reserved Bit (Unused)  */

		uint8_t _reserved_4 :1; /*  Reserved Bit (Unused)  */
	} b;
	uint8_t w;
} PCA9959_MODE_1;

/*
 * MODE1 - Bit field mask definitions
 *
 */

#define PCA9959_CLK20M_TYP_SHIFT                            ((uint8_t)0x02)
#define PCA9959_CLK20M_TYP_MASK                             ((uint8_t)0x04)

#define PCA9959_OFFSET_DIS_SHIFT                            ((uint8_t)0x03)
#define PCA9959_OFFSET_DIS_MASK                             ((uint8_t)0x08)

#define PCA9959_SLEEP_SHIFT                                 ((uint8_t)0x04)
#define PCA9959_SLEEP_MASK                                  ((uint8_t)0x10)

/*---------------------------------
 ** Register: MODE2
 ** Enum: PCA9959_MODE2
 ** --
 ** Offset : 0x01 Mode register 2.
 ** ------------------------------*/
typedef union {
	struct {
		uint8_t _reserved_0 :1; /*  Reserved Bit (Unused)  */

		uint8_t _reserved_1 :1; /*  Reserved Bit (Unused)  */

		uint8_t _reserved_2 :1; /* Reserved Bit (Unused)  */

		uint8_t auto_switchoff :1; /*  auto switch off disable */

		uint8_t clrerr :1; /*  clear all error status bits  */

		uint8_t exclkprs :1; /*  external clock detection */

		uint8_t error :1; /*  open or short-circuit detection */

		uint8_t overtemp :1; /* over temperature condition. */
	} b;
	uint8_t w;
} PCA9959_MODE_2;

/*
 * MODE2 - Bit field mask definitions
 *
 */

#define PCA9959_AUTO_SWITCH_OFF_DIS_SHIFT         	        ((uint8_t)0x03)
#define PCA9959_AUTO_SWITCH_OFF_DIS_MASK                    ((uint8_t)0x08)

#define PCA9959_CLRERR_SHIFT                                ((uint8_t)0x04)
#define PCA9959_CLRERR_MASK                                 ((uint8_t)0x10)

#define PCA9959_EX_CLK_PRS_SHIFT                            ((uint8_t)0x05)
#define PCA9959_EX_CLK_PRS_MASK                             ((uint8_t)0x20)

#define PCA9959_ERROR_SHIFT                                 ((uint8_t)0x06)
#define PCA9959_ERROR_MASK                                  ((uint8_t)0x40)

#define PCA9959_OVERTEMP_SHIFT                              ((uint8_t)0x07)
#define PCA9959_OVERTEMP_MASK                               ((uint8_t)0x80)

#define PCA9959_GRID_DUR_TSTEP_SHIFT                        ((uint8_t)0x06)
#define PCA9959_GRID_DUR_TSTEP_MASK                         ((uint8_t)0xC0)

#define PCA9959_GRID_DUR_DURCNT_SHIFT                       ((uint8_t)0x00)
#define PCA9959_GRID_DUR_DURCNT_MASK                        ((uint8_t)0x3F)

#define PCA9959_GRID_CTL_GRD_MODE_SHIFT                     ((uint8_t)0x06)
#define PCA9959_GRID_CTL_GRD_MODE_MASK                      ((uint8_t)0x40)

#define PCA9959_GRID_CTL_GRD_EN_SHIFT                       ((uint8_t)0x07)
#define PCA9959_GRID_CTL_GRD_EN_MASK                        ((uint8_t)0x80)

#define PCA9959_GRID_CTL_GRD_DIS_SHIFT                      ((uint8_t)0x07)
#define PCA9959_GRID_CTL_GRD_DIS_MASK                       ((uint8_t)0x80)

#define PCA9959_SIDE_CTL_SIDE_EXE_SHIFT                     ((uint8_t)0x06)
#define PCA9959_SIDE_CTL_SIDE_EXE_MASK                      ((uint8_t)0x40)

#define PCA9959_SIDE_CTL_SIDE_CFG_SHIFT                     ((uint8_t)0x07)
#define PCA9959_SIDE_CTL_SIDE_CFG_MASK                      ((uint8_t)0x80)

#define PCA9959_PAGE_SEL_SHIFT                              ((uint8_t)0x07)
#define PCA9959_PAGE_SEL_MASK                               ((uint8_t)0x80)

#define PCA9959_GROUP0_SHIFT                                ((uint8_t)0x00)
#define PCA9959_GROUP0_MASK                                 ((uint8_t)0x03)

#define PCA9959_GROUP1_SHIFT                                ((uint8_t)0x02)
#define PCA9959_GROUP1_MASK                                 ((uint8_t)0x0C)

#define PCA9959_GROUP2_SHIFT                                ((uint8_t)0x04)
#define PCA9959_GROUP2_MASK                                 ((uint8_t)0x30)

#define PCA9959_GROUP3_SHIFT                                ((uint8_t)0x06)
#define PCA9959_GROUP3_MASK                                 ((uint8_t)0xC0)

#define CHX_CFG1_CHX_EN_SHIFT                               ((uint8_t)0x00)
#define CHX_CFG1_CHX_EN_MASK                                ((uint8_t)0x01)

#define CHX_CFG1_CHX_DIS_SHIFT                              ((uint8_t)0x00)
#define CHX_CFG1_CHX_DIS_MASK                               ((uint8_t)0x01)

#define CHX_CFG1_CHX_GRP_ASSIGN_SHIFT                       ((uint8_t)0x01)
#define CHX_CFG1_CHX_GRP_ASSIGN_MASK                        ((uint8_t)0x06)

#define CHX_CFG2_SHIFT                                      ((uint8_t)0x00)
#define CHX_CFG2_MASK                                       ((uint8_t)0xFF)

#define CHX_CFG3_SHIFT                                      ((uint8_t)0x01)
#define CHX_CFG3_MASK                                       ((uint8_t)0xFF)

#define CHX_CFG4_SHIFT                                      ((uint8_t)0x01)
#define CHX_CFG4_MASK                                       ((uint8_t)0xFF)


#endif /* PCA9959_H_ */
