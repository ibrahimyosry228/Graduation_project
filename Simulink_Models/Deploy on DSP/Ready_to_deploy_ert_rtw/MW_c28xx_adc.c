#include "c2000BoardSupport.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include "F2837xD_GlobalPrototypes.h"
#include "rtwtypes.h"
#include "Ready_to_deploy.h"
#include "Ready_to_deploy_private.h"

void config_ADCA_SOC0()
{
  EALLOW;
  AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3;   /* Set SOC0 channel select to ADCIN3*/
  AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0;
  AdcaRegs.ADCSOC0CTL.bit.ACQPS = 14.0;
                               /* Set SOC0 S/H Window to 15.0 ADC Clock Cycles*/
  AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = 0;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = AdcaRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correctino Value*/
  AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
                                /* Late interrupt pulse trips AdcResults latch*/
  AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0;/* All in round robin mode SOC Priority*/
  EDIS;
}

void config_ADCC_SOC0()
{
  EALLOW;
  AdccRegs.ADCSOC0CTL.bit.CHSEL = 2;   /* Set SOC0 channel select to ADCIN2*/
  AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0;
  AdccRegs.ADCSOC0CTL.bit.ACQPS = 14.0;
                               /* Set SOC0 S/H Window to 15.0 ADC Clock Cycles*/
  AdccRegs.ADCINTSOCSEL1.bit.SOC0 = 0;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdccRegs.ADCOFFTRIM.bit.OFFTRIM = AdccRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correctino Value*/
  AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
                                /* Late interrupt pulse trips AdcResults latch*/
  AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0;/* All in round robin mode SOC Priority*/
  EDIS;
}

void InitAdcA()
{
  EALLOW;
  CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
  AdcaRegs.ADCCTL2.bit.PRESCALE = 8;
  AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

  //power up the ADC
  AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

  //delay for 1ms to allow ADC time to power up
  DELAY_US(1000);
  EDIS;
}

void InitAdcC()
{
  EALLOW;
  CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
  AdccRegs.ADCCTL2.bit.PRESCALE = 8;
  AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

  //power up the ADC
  AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

  //delay for 1ms to allow ADC time to power up
  DELAY_US(1000);
  EDIS;
}
