/** @page TIM2_PWM_DutyCycleConfiguration Generate three different signals with three different duty cycles 

  @verbatim
  ******************** (C)COPYRIGHT 2014 STMicroelectronics *******************
  * @file    TIM2/TIM2_PWM_DutyCycleConfiguration/readme.txt
  * @author  MCD Application Team
  * @version V2.0.4
  * @date    26-April-2018
  * @brief   Description of the TIM2 PWM duty cycle configuration mode Example.
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim
   
  @par Example description

  This example shows how to configure the TIM2 peripheral in Pulse Width Modulation
  mode(PWM).
  The TIM2CLK frequency is 2MHz, the Prescaler is 1 so the TIM2 counter clock is 2MHz. 

  The TIM2 is running at 2 KHz: TIM2 Frequency = TIM2 counter clock/(ARR + 1) 
	
	So TIM2 frequency is 2KHz.


  The TIM2 CCR1 register value is equal to 500, so the TIM2 Channel 1 generates a 
  PWM signal with a frequency equal to 2KHz and a duty cycle equal to 50%:
  TIM2 Channel1 duty cycle = [TIM2_CCR1/(TIM2_ARR + 1)] * 100 = 50%

  The TIM2 CCR2 register value is equal to 375, so the TIM2 Channel 2 generates a 
  PWM signal with a frequency equal to 2KHz and a duty cycle equal to 25%:
  TIM2 Channel2 duty cycle = [TIM2_CCR2/ (TIM2_ARR + 1)] * 100 = 25%

  The TIM2 CCR3 register value is equal to 250, so the TIM2 Channel 3 generates a 
  PWM signal with a frequency equal to 2KHz and a duty cycle equal to 12.5%:
  TIM2 Channel3 duty cycle = [TIM2_CCR3/ (TIM2_ARR + 1)] * 100 = 12.5%


  The PWM waveform can be displayed using an oscilloscope.


  @par Directory contents

  - TIM2\TIM2_PWM_DutyCycleConfiguration\main.c                   Main file containing the "main" function
  - TIM2\TIM2_PWM_DutyCycleConfiguration\stm8s_conf.h             Library Configuration file
  - TIM2\TIM2_PWM_DutyCycleConfiguration\stm8s_it.c               Interrupt routines source
  - TIM2\TIM2_PWM_DutyCycleConfiguration\stm8s_it.h               Interrupt routines declaration
  

 @par Hardware and Software environment

  - This example runs on STM8S and STM8A High density, Medium density devices and
    STM8S103x Low density devices.
    
  
  - This example has been tested with STMicroelectronics STM8/128-EVAL evaluation 
    board and can be easily tailored to any other development board.

  - STM8/128-EVAL Set-up
    - Connect TIM2 pins to an oscilloscope:
	     - TIM2_CH1  pin (PD.4)  
	     - TIM2_CH2  pin (PD.3)  
	     - TIM2_CH3  pin (PA.3)  


  @par How to use it ?

  In order to make the program work, you must do the following :

  - Copy all source files from this example folder to the template folder under
    Project\Template
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
  - Connect the TIM2 pins to an oscilloscope 
  
  @note
  - High-Density STM8A devices are the STM8AF52xx STM8AF6269/8x/Ax,
    STM8AF51xx, and STM8AF6169/7x/8x/9x/Ax microcontrollers where the Flash memory
    density ranges between 32 to 128 Kbytes
  - Medium-Density STM8A devices are the STM8AF622x/4x, STM8AF6266/68,
    STM8AF612x/4x, and STM8AF6166/68 microcontrollers where the Flash memory 
    density ranges between 8 to 32 Kbytes
  - High-Density STM8S devices are the STM8S207xx, STM8S007 and STM8S208xx microcontrollers
    where the Flash memory density ranges between 32 to 128 Kbytes.
  - Medium-Density STM8S devices are the STM8S105x and STM8S005 microcontrollers
    where the Flash memory density ranges between 16 to 32-Kbytes.
  - Low-Density STM8S devices are the STM8S103xx, STM8S003, STM8S001 and STM8S903xx microcontrollers
    where the Flash density is 8 Kbytes.
      
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
