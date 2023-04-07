# UDP server example
## Changes
+ Added in [stm32f4_discovery.c](https://github.com/MykhailoSvirskyi/GL-ESK-ETHERNET/blob/main/tcp_socket_client/Drivers/BSP/Src/stm32f4_discovery.c)
read pin status function.
```
GPIO_PinState BSP_LED_Read(Led_TypeDef Led)
{
	return (HAL_GPIO_ReadPin(GPIO_PORT[Led], GPIO_PIN[Led]));
}
```
+ Add simple example UDP senver [upd_server.c](https://github.com/MykhailoSvirskyi/GL-ESK-ETHERNET/blob/main/tcp_socket_client/Core/Src/upd_server.c)
+ Add parser and led driver in [led.c](https://github.com/MykhailoSvirskyi/GL-ESK-ETHERNET/blob/main/tcp_socket_client/Core/Src/led.c)

## Start example
To start exaple you can use ncat:
```
 ncat -u 210.10.10.2 5678
```
![test ncat](https://github.com/MykhailoSvirskyi/GL-ESK-ETHERNET/blob/main/work%20example.png)

If used this test [GL-ESK-TEST-SUIT](https://github.com/PetroShevchenko/GL-ESK-TEST-SUIT) 
Change the following line 'udp_server_ttcn_test_suit->src->PCOType.cc:109' with board's IP address:
```
std::string ip = "210.10.10.2";
```
## Video test work
https://user-images.githubusercontent.com/90723683/230672186-c602402e-42a9-4949-936a-777a7087f297.mp4

