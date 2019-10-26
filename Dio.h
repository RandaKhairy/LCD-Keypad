
#ifndef DIO_H_
#define DIO_H_

#include "Dio_confg.h"
#include "micro_config.h"

#define Max_num_of_pins 32

uint8 DIO_init(void);
uint8 DIO_read(uint8 pin_index, uint8* value);
uint8 DIO_Write(uint8 pin_index, uint8 value);

#endif
