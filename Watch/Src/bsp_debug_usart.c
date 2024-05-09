/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  fire
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   ʹ�ô���1���ض���c��printf������usart�˿ڣ��жϽ���ģʽ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F746 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "bsp_debug_usart.h"

extern DSI_HandleTypeDef hdsi_discovery;

UART_HandleTypeDef UartHandle;
extern uint8_t ucTemp;  
 /**
  * @brief  DEBUG_USART GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */  
void DEBUG_USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;
        
    DEBUG_USART_RX_GPIO_CLK_ENABLE();
    DEBUG_USART_TX_GPIO_CLK_ENABLE();
    
    /* ���ô���1ʱ��Դ*/
    RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    RCC_PeriphClkInit.Usart1ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
    HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);
    /* ʹ�� UART ʱ�� */
    DEBUG_USART_CLK_ENABLE();

    /**USART1 GPIO Configuration    
    PA9     ------> USART2_TX
    PA10    ------> USART2_RX 
    */
    /* ����Tx����Ϊ���ù���  */
    GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = DEBUG_USART_TX_AF;
    HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);
    
    /* ����Rx����Ϊ���ù��� */
    GPIO_InitStruct.Pin = DEBUG_USART_RX_PIN;
    GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;
    HAL_GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct); 
    
    /* ���ô�DEBUG_USART ģʽ */
    UartHandle.Instance = DEBUG_USART;
    UartHandle.Init.BaudRate = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits = UART_STOPBITS_1;
    UartHandle.Init.Parity = UART_PARITY_NONE;
    UartHandle.Init.Mode = UART_MODE_TX_RX;
    UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    UartHandle.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
    UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&UartHandle);

    /*����1�жϳ�ʼ�� */
    HAL_NVIC_SetPriority(DEBUG_USART_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ);
    /*���ô��ڽ����ж� */
    __HAL_UART_ENABLE_IT(&UartHandle,UART_IT_RXNE);  
}

void DEBUG_USART_IRQHandler(void)
{
    uint8_t Res;
  if(__HAL_UART_GET_FLAG(&UartHandle,UART_FLAG_RXNE)!=RESET)
  {
    HAL_UART_Receive(&UartHandle,&Res,1,0Xffff); 
   switch(Res) 
   {
     case 0x5E:
//      HAL_DSI_LongWrite(&hdsi_discovery, 0, DSI_DCS_LONG_PKT_WRITE, 4, SH8601B_CMD_CASET, pCols[idx]);
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_HS_CK_EN");
     break;
     
     case 0x5F:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_HS_RX_EN0");
     break;
     
     case 0x60:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_HS_CK_TERM");
     break;
     
     case 0x61:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_HS_RX_TERM0");
     break;
     
      case 0x62:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_LP_RX_MODE_EN");
     break;
      
     case 0x63:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_LP_CK_SCHMITT_EN");
     break;
     
     case 0x64:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_LP_RX_SCHMITT_EN0");
     break;
     
     case 0x65:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_LP_CK_COMP_EN");
     break;
     
      case 0x66:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_LP_RX_COMP_EN0");
     break;
      
     case 0x67:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_ULPS_CK");
     break;
     
     case 0x68:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_ULPS_RX0");
     break;
     
      case 0x69:
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
      printf("MIPI_ULPS");
     break;
      
     default:
     HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFC, Res);
     printf("FCh write: %d",Res);
     break;

   }
  }
  else if(__HAL_UART_GET_FLAG(&UartHandle,UART_FLAG_IDLE)!=RESET)
  {
    printf("Receive a frame data.");
    __HAL_UART_CLEAR_IDLEFLAG(&UartHandle);
  }
}
/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit( &UartHandle,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
  
}
///�ض���c�⺯��printf������DEBUG_USART���ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
	/* ����һ���ֽ����ݵ�����DEBUG_USART */
	HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}

///�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		
	int ch;
	HAL_UART_Receive(&UartHandle, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}
/*********************************************END OF FILE**********************/
