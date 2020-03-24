int main(void){ 
    
//the BEGIN of address – GPIOc is 0x4001 1000- the END of address  0x4001 13FF ;
//the BEGIN of address – GPIOb is 0x4001 0C00- the END of address  0x4001 0FFF ;
//the BEGIN of address – GPIOa is 0x4001 0800- the END of address  0x4001 0BFF .

  // 0. Pointers init. NO OS!!!
        //The BEGIN of address  GPIOc is 0x40011000
				//Address offset: 0x00 for (GPIO_C_CRL)
        //int *GPIO_C_CRL=(int*)(0x40011000);
        //Address offset for CRH: 0x04 (GPIO_C_CRH)
        int *GPIO_C_CRH = (int*)(0x40011004);
        //Port output data register (GPIOx_ODR) (x=A..G)
        //Address offset for ODR: 0x0C
        //Bits 31:16 Reserved // Bits 13-15 actual for  ODRy
        int *GPIO_C_ODR = (int*)(0x4001100C);
        
				//APB2ENR register for clock selection
        int *apb2enr = (int*)0x40021018;
        //delay counter variable
   
				int i;
  // I. Enable PORTC Clock
        *apb2enr|=0x00018;     // Init fast bus 1100 for C and A
  // II. Enable  GPIO_Pin_13 for output push-pool Mode
				*GPIO_C_CRH=0x00300000;//Set all PC13 ports as output

        for(;;){
                // 300ms
                for(i=0;i<0x40000;i++){                }//delay
                 *GPIO_C_ODR=0x00002000;// for C 13         10 0000 0000 0000
                for(i=0;i<0x40000;i++){                }//delay
                *GPIO_C_ODR=0x00000000;
      }
    }
