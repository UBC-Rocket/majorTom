#ifndef CAN_HW_STM32F446_H
#define CAN_HW_STM32F446_H

#define CAN_WRITE_TIMEOUT			100

#define CAN_1                      CAN1
#define CAN_CLK                    RCC_APB1Periph_CAN1
#define CAN_RX_PIN                 GPIO_Pin_0
#define CAN_TX_PIN                 GPIO_Pin_1
#define CAN_GPIO_PORT              GPIOD
#define CAN_GPIO_CLK               RCC_AHB1Periph_GPIOD
#define CAN_AF_PORT                GPIO_AF_CAN1
#define CAN_RX_SOURCE              GPIO_PinSource0
#define CAN_TX_SOURCE              GPIO_PinSource1

  /* CAN Master Control Register bits */
#define MCR_DBF           ((uint32_t)0x00010000) /* software master reset */

/* CAN Mailbox Transmit Request */
#define TMIDxR_TXRQ       ((uint32_t)0x00000001) /* Transmit mailbox request */

/* CAN Filter Master Register bits */
#define FMR_FINIT         ((uint32_t)0x00000001) /* Filter init mode */

/* Time out for INAK bit */
#define INAK_TIMEOUT      ((uint32_t)0x0000FFFF)
/* Time out for SLAK bit */
#define SLAK_TIMEOUT      ((uint32_t)0x0000FFFF)

/* Flags in TSR register */
#define CAN_FLAGS_TSR     ((uint32_t)0x08000000)
/* Flags in RF1R register */
#define CAN_FLAGS_RF1R    ((uint32_t)0x04000000)
/* Flags in RF0R register */
#define CAN_FLAGS_RF0R    ((uint32_t)0x02000000)
/* Flags in MSR register */
#define CAN_FLAGS_MSR     ((uint32_t)0x01000000)
/* Flags in ESR register */
#define CAN_FLAGS_ESR     ((uint32_t)0x00F00000)

/* Mailboxes definition */
#define CAN_TXMAILBOX_0   ((uint8_t)0x00)
#define CAN_TXMAILBOX_1   ((uint8_t)0x01)
#define CAN_TXMAILBOX_2   ((uint8_t)0x02)

#define CAN_MODE_MASK     ((uint32_t) 0x00000003)

#endif // CAN_HW_STM32F446_H