/* These functions can be copied into your main.c file to send messages over the
 * serial connection provided via USB. You can send and receive messages with
 * a serial terminal, like screen on Linux/macOS, or PuTTY on all systems. */

// Place these lines between the USER CODE BEGIN PV and USER CODE END PV blocks.
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar()

// Place these lines between the USER CODE BEGIN 4 and USER CODE END 4 blocks.
// ==================== uart => printf substitute =====================

/**
  * @brief  Retargets the C library printf and scanf functions to the UART.
  * @param  None
  * @retval None
  */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the LPUART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

GETCHAR_PROTOTYPE
{
	uint8_t ch;

	HAL_UART_Receive(&huart3, &ch, 1, 0xFFFF);

	return ch;
}

