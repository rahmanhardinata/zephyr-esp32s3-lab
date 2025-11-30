#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main);

#define SLEEP_MS 500
#define LED0_NODE DT_ALIAS(led0)

int main(void)
{
    const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

    if (!device_is_ready(led.port)) {
        LOG_ERR("LED device not ready");
        return 0;
    }

    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        LOG_ERR("Failed to configure LED: %d", ret);
        return 0;
    }

    LOG_INF("Zephyr ESP32-S3 blink started");

    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(SLEEP_MS);
    }
}
