/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! File: frdm_stbi_pca9959_shield.h
* @brief The frdm_stbi_pca9959_shield.h file declares arduino pin mapping for frdm_stbi_pca9959_shield expansion board.
*/

#ifndef _FRDM_STBI_PCA9959_SHIELD_H_
#define _FRDM_STBI_PCA9959_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBI-PCA9959"

/* Enable PCA9959 SPI Read */
#define PCA9959_ARD    1

#define PCA9959_CS        D10
#define PCA9959_MOSI      D11
#define PCA9959_MISO      D12
#define PCA9959_SCLK      D13

#define PCA9959_OE        D9
#define PCA9959_RESET     D8
#define PCA9959_SW_EN     D2

#endif /* _FRDM_STBI_PCA9959_SHIELD_H_ */
