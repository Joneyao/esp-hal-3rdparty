/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <stdbool.h>
#include "soc/soc_caps.h"
#include "esp_types.h"
#include "esp_bit_defs.h"
#include "esp_private/esp_gpio_reserve.h"

static volatile uint64_t s_reserved_pin_mask = ~(SOC_GPIO_VALID_GPIO_MASK);

uint64_t esp_gpio_reserve(uint64_t gpio_mask)
{
    uint64_t prev = s_reserved_pin_mask;
    s_reserved_pin_mask |= gpio_mask;
    return prev;
}

uint64_t esp_gpio_revoke(uint64_t gpio_mask)
{
    uint64_t prev = s_reserved_pin_mask;
    s_reserved_pin_mask &= ~gpio_mask;
    return prev;
}

bool esp_gpio_is_reserved(uint64_t gpio_mask)
{
    return (s_reserved_pin_mask & gpio_mask) != 0;
}

// TODO: IDF-6968 reserve the pins that not fanned out regarding the SiP version
