#ifndef __ROM_MAP_H__
#define __ROM_MAP_H__


#ifdef ROM_ADCSequenceDataGet
#define MAP_ADCSequenceDataGet                                                
        ROM_ADCSequenceDataGet
#else
#define MAP_ADCSequenceDataGet                                                
        ADCSequenceDataGet
#endif
#ifdef ROM_ADCIntDisable
#define MAP_ADCIntDisable                                                     
        ROM_ADCIntDisable
#else
#define MAP_ADCIntDisable                                                     
        ADCIntDisable
#endif
#ifdef ROM_ADCIntEnable
#define MAP_ADCIntEnable                                                      
        ROM_ADCIntEnable
#else
#define MAP_ADCIntEnable                                                      
        ADCIntEnable
#endif
#ifdef ROM_ADCIntStatus
#define MAP_ADCIntStatus                                                      
        ROM_ADCIntStatus
#else
#define MAP_ADCIntStatus                                                      
        ADCIntStatus
#endif
#ifdef ROM_ADCIntClear
#define MAP_ADCIntClear                                                       
        ROM_ADCIntClear
#else
#define MAP_ADCIntClear                                                       
        ADCIntClear
#endif
#ifdef ROM_ADCSequenceEnable
#define MAP_ADCSequenceEnable                                                 
        ROM_ADCSequenceEnable
#else
#define MAP_ADCSequenceEnable                                                 
        ADCSequenceEnable
#endif
#ifdef ROM_ADCSequenceDisable
#define MAP_ADCSequenceDisable                                                
        ROM_ADCSequenceDisable
#else
#define MAP_ADCSequenceDisable                                                
        ADCSequenceDisable
#endif
#ifdef ROM_ADCSequenceConfigure
#define MAP_ADCSequenceConfigure                                              
        ROM_ADCSequenceConfigure
#else
#define MAP_ADCSequenceConfigure                                              
        ADCSequenceConfigure
#endif
#ifdef ROM_ADCSequenceStepConfigure
#define MAP_ADCSequenceStepConfigure                                          
        ROM_ADCSequenceStepConfigure
#else
#define MAP_ADCSequenceStepConfigure                                          
        ADCSequenceStepConfigure
#endif
#ifdef ROM_ADCSequenceOverflow
#define MAP_ADCSequenceOverflow                                               
        ROM_ADCSequenceOverflow
#else
#define MAP_ADCSequenceOverflow                                               
        ADCSequenceOverflow
#endif
#ifdef ROM_ADCSequenceOverflowClear
#define MAP_ADCSequenceOverflowClear                                          
        ROM_ADCSequenceOverflowClear
#else
#define MAP_ADCSequenceOverflowClear                                          
        ADCSequenceOverflowClear
#endif
#ifdef ROM_ADCSequenceUnderflow
#define MAP_ADCSequenceUnderflow                                              
        ROM_ADCSequenceUnderflow
#else
#define MAP_ADCSequenceUnderflow                                              
        ADCSequenceUnderflow
#endif
#ifdef ROM_ADCSequenceUnderflowClear
#define MAP_ADCSequenceUnderflowClear                                         
        ROM_ADCSequenceUnderflowClear
#else
#define MAP_ADCSequenceUnderflowClear                                         
        ADCSequenceUnderflowClear
#endif
#ifdef ROM_ADCProcessorTrigger
#define MAP_ADCProcessorTrigger                                               
        ROM_ADCProcessorTrigger
#else
#define MAP_ADCProcessorTrigger                                               
        ADCProcessorTrigger
#endif
#ifdef ROM_ADCHardwareOversampleConfigure
#define MAP_ADCHardwareOversampleConfigure                                    
        ROM_ADCHardwareOversampleConfigure
#else
#define MAP_ADCHardwareOversampleConfigure                                    
        ADCHardwareOversampleConfigure
#endif
#ifdef ROM_ADCComparatorConfigure
#define MAP_ADCComparatorConfigure                                            
        ROM_ADCComparatorConfigure
#else
#define MAP_ADCComparatorConfigure                                            
        ADCComparatorConfigure
#endif
#ifdef ROM_ADCComparatorRegionSet
#define MAP_ADCComparatorRegionSet                                            
        ROM_ADCComparatorRegionSet
#els
#define MAP_ADCComparatorRegionSet                                            
        ADCComparatorRegionSet
#endif
#ifdef ROM_ADCComparatorReset
#define MAP_ADCComparatorReset                                                
        ROM_ADCComparatorReset
#else
#define MAP_ADCComparatorReset                                                
        ADCComparatorReset
#endif
#ifdef ROM_ADCComparatorIntDisable
#define MAP_ADCComparatorIntDisable                                           
        ROM_ADCComparatorIntDisable
#else
#define MAP_ADCComparatorIntDisable                                           
        ADCComparatorIntDisable
#endif
#ifdef ROM_ADCComparatorIntEnable
#define MAP_ADCComparatorIntEnable                                            
        ROM_ADCComparatorIntEnable
#else
#define MAP_ADCComparatorIntEnable                                            
        ADCComparatorIntEnable
#endif
#ifdef ROM_ADCComparatorIntStatus
#define MAP_ADCComparatorIntStatus                                            
        ROM_ADCComparatorIntStatus
#else
#define MAP_ADCComparatorIntStatus                                            
        ADCComparatorIntStatus
#endif
#ifdef ROM_ADCComparatorIntClear
#define MAP_ADCComparatorIntClear                                             
        ROM_ADCComparatorIntClear
#else
#define MAP_ADCComparatorIntClear                                             
        ADCComparatorIntClear
#endif
#ifdef ROM_ADCReferenceSet
#define MAP_ADCReferenceSet                                                   
        ROM_ADCReferenceSet
#else
#define MAP_ADCReferenceSet                                                   
        ADCReferenceSet
#endif
#ifdef ROM_ADCReferenceGet
#define MAP_ADCReferenceGet                                                   
        ROM_ADCReferenceGet
#else
#define MAP_ADCReferenceGet                                                   
        ADCReferenceGet
#endif
#ifdef ROM_ADCPhaseDelaySet
#define MAP_ADCPhaseDelaySet                                                  
        ROM_ADCPhaseDelaySet
#else
#define MAP_ADCPhaseDelaySet                                                  
        ADCPhaseDelaySet
#endif
#ifdef ROM_ADCPhaseDelayGet
#define MAP_ADCPhaseDelayGet                                                  
        ROM_ADCPhaseDelayGet
#else
#define MAP_ADCPhaseDelayGet                                                  
        ADCPhaseDelayGet
#endif
#ifdef ROM_ADCIntClearEx
#define MAP_ADCIntClearEx                                                     
        ROM_ADCIntClearEx
#els
#define MAP_ADCIntClearEx                                                     
        ADCIntClearEx
#endif
#ifdef ROM_ADCIntDisableEx
#define MAP_ADCIntDisableEx                                                   
        ROM_ADCIntDisableEx
#else
#define MAP_ADCIntDisableEx                                                   
        ADCIntDisableEx
#endif
#ifdef ROM_ADCIntEnableEx
#define MAP_ADCIntEnableEx                                                    
        ROM_ADCIntEnableEx
#else
#define MAP_ADCIntEnableEx                                                    
        ADCIntEnableEx
#endif
#ifdef ROM_ADCIntStatusEx
#define MAP_ADCIntStatusEx                                                    
        ROM_ADCIntStatusEx
#else
#define MAP_ADCIntStatusEx                                                    
        ADCIntStatusEx
#endif
#ifdef ROM_ADCSequenceDMAEnable
#define MAP_ADCSequenceDMAEnable                                              
        ROM_ADCSequenceDMAEnable
#else
#define MAP_ADCSequenceDMAEnable                                              
        ADCSequenceDMAEnable
#endif
#ifdef ROM_ADCSequenceDMADisable
#define MAP_ADCSequenceDMADisable                                             
        ROM_ADCSequenceDMADisable
#else
#define MAP_ADCSequenceDMADisable                                             
        ADCSequenceDMADisable
#endif
#ifdef ROM_ADCBusy
#define MAP_ADCBusy                                                           
        ROM_ADCBusy
#else
#define MAP_ADCBusy                                                           
        ADCBusy
#endif