#include "main.h"
#include "sensor_service.h"
#include "drv_i2c.h"
#include "hci_tl.h"
#include "sensor_service.h"
#include "role_type.h"
#include "bluenrg_utils.h"
#include "bluenrg_gatt_server.h"
#include "bluenrg_gap_aci.h"
#include "bluenrg_gatt_aci.h"
#include "bluenrg_hal_aci.h"
#include "util.h"

void SystemClock_Config(void);


extern volatile int     connected;
extern volatile uint8_t set_connectable;
extern volatile uint8_t notification_enabled;

volatile uint8_t user_button_init_state = 1;
volatile uint8_t user_button_pressed = 0;

#define SERVER_ROLE
#define BDADDR_SIZE 6

uint8_t bnrg_expansion_board = IDB04A1; /* at startup, suppose the X-NUCLEO-IDB04A1 is used */
BLE_RoleTypeDef BLE_Role = SERVER;

void MX_BlueNRG_MS_Init(void);

extern int humidity_subscription ;
extern int temperature_subscription ;
//extern int X_subscription;
//extern int Y_subscription;
extern int TempColor_subscription;

//===================================================================
//						>>> MAIN <<<
//===================================================================
int main(void)
{
	int i;

  HAL_Init();
  SystemClock_Config();
  i2c1_Init();
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
  BSP_LED_Init(LED2);

  BSP_LED_On(LED2);
  BSP_LED_Off(LED2);



  BSP_COM_Init(COM1);

  user_button_init_state = BSP_PB_GetState(BUTTON_KEY);

  MX_BlueNRG_MS_Init();

  while (sht4x_probe() != 0) {
   	printf("\r\nSHT sensor probing failed");
   }

   tcs34725_init();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //				TEST CAPTEURS
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//	  float temperature, humidity;
//	  while(1)
//	  {
//	  	 int8_t ret = sht4x_measure_blocking_read(&temperature, &humidity);
//	  	 if (ret==0) {
//	  		 	 	 	 	 	 int temp_int = (int) temperature;
//	  		                     float temp_frac = temperature - temp_int;
//	  		                     int hum_int = (int) humidity;
//	  		                     float hum_frac = humidity - hum_int;
//
//	  		                     int temp_int_frac = (int)(temp_frac * 1000);
//	  		                     int hum_int_frac = (int)(hum_frac * 1000);
//
//	  		                     printf("\r\ntemperature: %d.%d C", temp_int, temp_int_frac);
//	  		                     //printf("\r\nhumidity: %d.%d", hum_int, hum_int_frac);
//	  	 }
//	  	 else{
//	  		  term_printf("error in read ");
//	  	 }
//	  	 HAL_Delay(1000);
//	  }
//
//	  	uint16_t red, green, blue, clear, color_temp, lux;
//	  	float x, y;
//
//	  	while(1)
//	  	{
//	  		 tcs34725_read_color(&red, &green, &blue, &clear);
//	  		 color_temp = calculateColorTemperature(red, green, blue, &x, &y);
//	  		 lux = calculateLux(red, green, blue);
//
//	  		  int x_int =(int)x;
//	  		  float x_frac = x-x_int;
//	  		  int x_frac_int = (int)(x_frac * 1000);
//	  		  int y_int = (int)y;
//	  		  float y_frac = y-y_int;
//	  		  int y_frac_int= (int)(y_frac*1000);
//	  		  printf("\r\nx = %d.%d , y=%d.%d, illuminance=%d\r\n", x_int, x_frac_int, y_int, y_frac_int,lux);
//	  		  printf("\r\nTemperature en Kelvin: %d\n", color_temp);
//	  		 HAL_Delay(1000);
//	  	}


    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  while (1)
  {
	  if (set_connectable)
	  {
	    Make_Connection();
	    set_connectable = FALSE;
	    user_button_init_state = BSP_PB_GetState(BUTTON_KEY);
	  }

	  if(connected && temperature_subscription && TempColor_subscription )
	  {
		  SendEnvironmentalData();
		  HAL_Delay(100);
	  }

	  hci_user_evt_proc();
  }
}
//=====================================================================================
//			 Send Environmetal Data (Temperature/Pressure/Humidity) to BLE
//=====================================================================================

void SendEnvironmentalData(void)
{
	static float temperature, humidity;
	uint16_t red, green, blue, clear, color_temp, lux;
	float x, y;
	int32_t TempToSend=0;
	int32_t decPart, intPart;
	int16_t ret ;
	ret = sht4x_measure_blocking_read(&temperature, &humidity);
    tcs34725_read_color(&red, &green, &blue, &clear);
	color_temp = calculateColorTemperature(red, green, blue, &x, &y);
    int temp_int = (int) temperature;
	float temp_frac = temperature - temp_int;
	int temp_int_frac = (int)(temp_frac * 1000);
	printf("\r\ntemperature en kelvin: %d K", color_temp);
	printf("\r\ntemperature: %d.%d C", temp_int, temp_int_frac);
	MCR_BLUEMS_F2I_1D(temperature, intPart, decPart);
	TempToSend = intPart*10+decPart;
   	Environmental_Update(TempToSend,color_temp);
   	HAL_Delay(1000);
}
//===========================================================================
void MX_BlueNRG_MS_Init(void)
{

  uint8_t SERVER_BDADDR[] = {0xab, 0x00, 0x00, 0xE1, 0x80, 0x02};
  uint8_t bdaddr[BDADDR_SIZE];
  uint16_t service_handle, dev_name_char_handle, appearance_char_handle;

  uint8_t  hwVersion;
  uint16_t fwVersion;
  int ret;

  hci_init(user_notify, NULL);

  /* get the BlueNRG HW and FW versions */
  getBlueNRGVersion(&hwVersion, &fwVersion);

  /*
   * Reset BlueNRG again otherwise we won't
   * be able to change its MAC address.
   * aci_hal_write_config_data() must be the first
   * command after reset otherwise it will fail.
   */
  hci_reset();

  HAL_Delay(100);

  printf("HWver %d, FWver %d\n\r", hwVersion, fwVersion);

  if (hwVersion > 0x30) { /* X-NUCLEO-IDB05A1 expansion board is used */
    bnrg_expansion_board = IDB05A1;
  }

  BLUENRG_memcpy(bdaddr, SERVER_BDADDR, sizeof(SERVER_BDADDR));

  ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET,
                                  CONFIG_DATA_PUBADDR_LEN,
                                  bdaddr);
  	  	  	  	  	  if (ret) {    printf("Setting BD_ADDR failed 0x%02x.\n\r", ret);  }

  ret = aci_gatt_init();
  	  	  	  	  	  if (ret) {    printf("GATT_Init failed.\n\r");  }


  ret = aci_gap_init_IDB05A1(GAP_PERIPHERAL_ROLE_IDB05A1, 0, 0x07, &service_handle, &dev_name_char_handle, &appearance_char_handle);

  	  	  	  	  	  if (ret != BLE_STATUS_SUCCESS) {	printf("GAP_Init failed.\n\r");}

  ret = aci_gap_set_auth_requirement(MITM_PROTECTION_REQUIRED,
                                     OOB_AUTH_DATA_ABSENT,
                                     NULL,
                                     7,
                                     16,
                                     USE_FIXED_PIN_FOR_PAIRING,
                                     123456,
                                     BONDING);
  	  	  	  	  	  if (ret == BLE_STATUS_SUCCESS) { printf("BLE Stack Initialized.\n\r"); }


    printf("SERVER: BLE Stack Initialized\n\r");

    ret = Add_HWServW2ST_Service();		// HARDWARE SERVICE
						if (ret == BLE_STATUS_SUCCESS)
						  printf("Service added successfully.\n\r");
						else
						  printf("Error while adding service.\n\r");

  /* Set output power level */
  ret = aci_hal_set_tx_power_level(1,4);

}
//===================================================================
//				CALLBACK FUNCTIONS
//===================================================================
void BSP_PB_Callback(Button_TypeDef Button)
{
  user_button_pressed = 1;
}
//===================================================================
//				SYS CLOCK CONFIG
//===================================================================
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

//===================================================================
void Error_Handler(void)
{
}
//===================================================================
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

//===================================================================
