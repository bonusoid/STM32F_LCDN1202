/* USER CODE BEGIN Header */
/**
 * 2022-04-11
 * Created by : bonusoid
 * LCD Nokia 1202 Demo
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_n1202.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
unsigned char dsine[10] = {0x18,0x06,0x01,0x01,0x06,0x18,0x60,0x80,0x80,0x60}; //Sinewave pattern
unsigned char dtri[14] = {0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x40,0x20,0x10}; //Trianglewave pattern
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
//LCD Test Functions
void drawInt();	//Draw Integer demo
void drawAlphanum(); //Draw Letter & Number demo
void drawPunct(); //Draw Punctuation demo
void drawFrame(); //Draw Frame demo
void drawArrow(); //Draw Arrow demo
void drawBytes(); //Draw Pattern demo

void drawLoadingBar(); //Draw Loading Bar animation
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  lcdn1202_init();
  /* USER CODE BEGIN 2 */
  drawLoadingBar();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  	  	drawBytes();
	  		HAL_Delay(1000);
	        LCD_clearblock(3,5,84); //Finish column = 5 + 8*10 - 1
	     	HAL_Delay(500);
	  		LCD_clearblock(5,3,86); //Finish column = 3 + 6*14 - 1
	     	HAL_Delay(500);

	  		drawInt();
	  		HAL_Delay(1000);
	  		LCD_clear();

	  		drawAlphanum();
	  		HAL_Delay(1000);
	  		LCD_reverse();
	  		HAL_Delay(1000);
	  		LCD_clear();
	  		LCD_normal();
	  		drawPunct();
	  		HAL_Delay(1000);
	  		LCD_reverse();
	  		HAL_Delay(1000);
	  		LCD_clear();
	  		LCD_normal();

	  		drawFrame();
	  		HAL_Delay(700);
	  		LCD_clearblock(3,36,43); //Finish column = 36 + 8 - 1
	  		HAL_Delay(700);
	  		LCD_clear();
	  		drawArrow();
	  		HAL_Delay(700);
	  		LCD_clearblock(3,36,43); //Finish column = 36 + 8 - 1
	  		HAL_Delay(700);
	  		LCD_clear();
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void drawInt()
{
	LCD_drawint(64, 0, 8);
	LCD_drawint(-64, 2, 8);	//Negative number is not supported
	 	 	 	 	 	 	//Its 2's complement will be displayed

	LCD_drawint(100, 3, 8);
	LCD_drawchar(SYM_DEGREE, 3, 32);
	LCD_drawchar('C', 3, 40);

	LCD_drawint(65535, 5, 8);
	LCD_drawint(4294967295, 7, 8); //Max. is 4294967295

	LCD_drawint(064, 3, 70);  //Octal displayed as Decimal
	LCD_drawint(0x64, 5, 70); //Hexadecimal displayed as Decimal
}

void drawAlphanum()
{
	LCD_drawtext("ABCDEFGHIJKL",0,0);
	LCD_drawtext("MNOPQRSTUVWX",1,0);
	LCD_drawtext("YZ",2,0);
	LCD_drawtext("abcdefghijkl",3,0);
	LCD_drawtext("mnopqrstuvwxyz",4,0);
	LCD_drawtext("yz",5,0);
	LCD_drawtext("0123456789",6,0);
}

void drawPunct()
{
	LCD_drawtext("<{([+_-=])}>",0,0);
	LCD_drawtext("!@#$%^&*`|~?",2,0);
	LCD_drawtext(".,\"\'\\/ :;",4,0);
}

void drawFrame()
{
	unsigned char startcol=20;

	LCD_drawchar(FRAME_TOP_LEFT,1,startcol);
	LCD_drawchar(FRAME_LINE_HOR,1,startcol+8);
	LCD_drawchar(FRAME_TOP,1,startcol+16);
	LCD_drawchar(FRAME_LINE_HOR,1,startcol+24);
	LCD_drawchar(FRAME_TOP_RIGHT,1,startcol+32);

	LCD_drawchar(FRAME_LINE_VER,2,startcol);
	LCD_drawchar(FRAME_LINE_VER,2,startcol+16);
	LCD_drawchar(FRAME_LINE_VER,2,startcol+32);

	LCD_drawchar(FRAME_MID_LEFT,3,startcol);
	LCD_drawchar(FRAME_LINE_HOR,3,startcol+8);
	LCD_drawchar(FRAME_CENTER,3,startcol+16);
	LCD_drawchar(FRAME_LINE_HOR,3,startcol+24);
	LCD_drawchar(FRAME_MID_RIGHT,3,startcol+32);

	LCD_drawchar(FRAME_LINE_VER,4,startcol);
	LCD_drawchar(FRAME_LINE_VER,4,startcol+16);
	LCD_drawchar(FRAME_LINE_VER,4,startcol+32);

	LCD_drawchar(FRAME_BOT_LEFT,5,startcol);
	LCD_drawchar(FRAME_LINE_HOR,5,startcol+8);
	LCD_drawchar(FRAME_BOT,5,startcol+16);
	LCD_drawchar(FRAME_LINE_HOR,5,startcol+24);
	LCD_drawchar(FRAME_BOT_RIGHT,5,startcol+32);
}
void drawArrow()
{
	unsigned char startcol=20;

	LCD_drawchar(ARROW_UP_LEFT,1,startcol);
	LCD_drawchar(ARROW_UP,1,startcol+16);
	LCD_drawchar(ARROW_UP_RIGHT,1,startcol+32);

	LCD_drawchar(ARROW_LEFT,3,startcol);
	LCD_drawchar(ARROW_POINT,3,startcol+16);
	LCD_drawchar(ARROW_RIGHT,3,startcol+32);

	LCD_drawchar(ARROW_DOWN_LEFT,5,startcol);
	LCD_drawchar(ARROW_DOWN,5,startcol+16);
	LCD_drawchar(ARROW_DOWN_RIGHT,5,startcol+32);
}

void drawBytes()
{
	unsigned char Ts,ds;

	LCD_setpos(3,5);
	for(Ts=0;Ts<8;Ts++) //Draw pattern 8 times
	{
		for(ds=0;ds<10;ds++)
		{
			LCD_drawbyte(dsine[ds]);
		}
	}

	LCD_setpos(5,3);
	for(Ts=0;Ts<6;Ts++) //Draw pattern 6 times
	{
		for(ds=0;ds<14;ds++)
		{
			LCD_drawbyte(dtri[ds]);
		}
	}
}

void drawLoadingBar()
{
	unsigned char lb;

	LCD_setpos(4,5);

	for(lb=5;lb<91;lb++)
	{
		LCD_drawbyte(0xFF);
		HAL_Delay(10);
	}
	HAL_Delay(1000);
	LCD_clearblock(4,5,90); //Start & finish column = start & finish lb
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

