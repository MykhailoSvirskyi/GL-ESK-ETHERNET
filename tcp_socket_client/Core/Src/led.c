/*author: Mykhailo Svirskyi 26.03.2023*/

#include "main.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
uint16_t led_num_converter(uint16_t num) //convert number who defined in Led_TypeDef
{
	switch (num) {
	case (3):
		return 1;
		break;

	case (4):
		return 0;
		break;

	case (5):
		return 2;
		break;

	case (6):
		return 3;
		break;
	default:
		Error_Handler();
		break;
	}
}

void comandreader(char *in, char *out) {
	char cmd[64];
	char cmd1[64];
	char cnum[64];
	char sts[64];
	int32_t num = 0;//led number
	memset(cmd1, 0, sizeof(cmd1));//for command sversion
	memset(cmd, 0, sizeof(cmd));//for command led
	memset(cnum, 0, sizeof(cnum));//char num led
	memset(sts, 0, sizeof(sts));//char status after "space" symbol

	sscanf(in, "%s", cmd1);
	if (strcmp(cmd1, "sversion") == 0) {
		sprintf(out, "udp_svr_mykhailo_svirskyi_26032023\nOK\n");   // version
	} else

	{
		sscanf(in, "%3s %s %63s", cmd, cnum, sts); // check comand like "led3 status"

		if (strcmp(cmd, "led") == 0) {
			num = atoi(cnum);
			if (num > 2 && num < 7) {
				sprintf(out, "OK\n"); //print "ok " but if wrong last command overwrite to error
				if (strcmp(sts, "on") == 0) {
					BSP_LED_On(led_num_converter(num));
				} else if (strcmp(sts, "off") == 0) {
					BSP_LED_Off(led_num_converter(num));
				} else if (strcmp(sts, "toggle") == 0) {
					BSP_LED_Toggle(led_num_converter(num));
				}

				else if (strcmp(sts, "status") == 0) {
					uint8_t n = BSP_LED_Read(led_num_converter(num));
					sprintf(out, "LED%d %s\nOK\n", num, (n == 0 ? "OFF" : "ON"));
				} else {
					sprintf(out, "ERROR\n");   //error
				}
			} else {
				sprintf(out, "ERROR\n");   //error
			}

		} else {
			sprintf(out, "ERROR\n");   //error
		}
	}

}

