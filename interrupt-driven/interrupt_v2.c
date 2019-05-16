//#include <stdbool.h>
//#include <stdint.h>
//#include "inc/hw_ints.h"
//#include "inc/hw_nvic.h"
//#include "inc/hw_types.h"
//#include "interrupt_v2.h"

// This is a mapping between priority grouping encodings and the number of preemption priority bits.

static const uint32_t g_pui32Priority[] =
{
    NVIC_APINT_PRIGROUP_0_8, NVIC_APINT_PRIGROUP_1_7, NVIC_APINT_PRIGROUP_2_6,
    NVIC_APINT_PRIGROUP_3_5, NVIC_APINT_PRIGROUP_4_4, NVIC_APINT_PRIGROUP_5_3,
    NVIC_APINT_PRIGROUP_6_2, NVIC_APINT_PRIGROUP_7_1
};

// This is a mapping between interrupt number and the register that contains the priority encoding for that interrupt.

static const uint32_t g_pui32Regs[] =
{
    0, NVIC_SYS_PRI1, NVIC_SYS_PRI2, NVIC_SYS_PRI3, NVIC_PRI0, NVIC_PRI1,
    NVIC_PRI2, NVIC_PRI3, NVIC_PRI4, NVIC_PRI5, NVIC_PRI6, NVIC_PRI7,
    NVIC_PRI8, NVIC_PRI9, NVIC_PRI10, NVIC_PRI11, NVIC_PRI12, NVIC_PRI13,
    NVIC_PRI14, NVIC_PRI15, NVIC_PRI16, NVIC_PRI17, NVIC_PRI18, NVIC_PRI19,
    NVIC_PRI20, NVIC_PRI21, NVIC_PRI22, NVIC_PRI23, NVIC_PRI24, NVIC_PRI25,
    NVIC_PRI26, NVIC_PRI27, NVIC_PRI28, NVIC_PRI29, NVIC_PRI30, NVIC_PRI31,
    NVIC_PRI32, NVIC_PRI33, NVIC_PRI34
};

// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt enable for that interrupt.

static const uint32_t g_pui32EnRegs[] =
{
    NVIC_EN0, NVIC_EN1, NVIC_EN2, NVIC_EN3, NVIC_EN4
};

// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt disable for that interrupt.

static const uint32_t g_pui32Dii16Regs[] =
{
    NVIC_DIS0, NVIC_DIS1, NVIC_DIS2, NVIC_DIS3, NVIC_DIS4
};

// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt pend for that interrupt.

static const uint32_t g_pui32PendRegs[] =
{
    NVIC_PEND0, NVIC_PEND1, NVIC_PEND2, NVIC_PEND3, NVIC_PEND4
};

// This is a mapping between interrupt number (for the peripheral interrupts
// only) and the register that contains the interrupt unpend for that interrupt.

static const uint32_t g_pui32UnpendRegs[] =
{
    NVIC_UNPEND0, NVIC_UNPEND1, NVIC_UNPEND2, NVIC_UNPEND3, NVIC_UNPEND4
};

// The default interrupt handler.

static void
_IntDefaultHandler(void)
{
    while(1)
    {
    }
}

// The processor vector table.
// Set the size of the vector table to the largest number of interrupts of any device

#undef NUM_INTERRUPTS
#define NUM_INTERRUPTS                          155
#if defined(ewarm)
#pragma data_alignment=1024
static __no_init void (*g_pfnRAMVectors[NUM_INTERRUPTS])(void) @ "VTABLE";
#elif defined(sourcerygxx)
static __attribute__((section(".cs3.region-head.ram")))
void (*g_pfnRAMVectors[NUM_INTERRUPTS])(void) __attribute__ ((aligned(1024)));
#elif defined(ccs) || defined(DOXYGEN)
#pragma DATA_ALIGN(g_pfnRAMVectors, 1024)
#pragma DATA_SECTION(g_pfnRAMVectors, ".vtable")
void (*g_pfnRAMVectors[NUM_INTERRUPTS])(void);
#else
static __attribute__((section("vtable")))
void (*g_pfnRAMVectors[NUM_INTERRUPTS])(void) __attribute__((aligned(1024)));
#endif


// Enables the processor interrupt.

bool
IntMasterEnable(void)
{
    // Enable processor interrupts.
    return(CPUcpsie());
}

// Disables the processor interrupt.

bool
IntMasterDisable(void)
{
    //
    // Disable processor interrupts.
    //
    return(CPUcpsid());
}

// Registers a function to be called when an interrupt occurs.

void
IntRegister(uint32_t ui32Interrupt, void (*pfnHandler)(void))
{
    uint32_t ui32Idx, ui32Value;
	
    // Check the arguments.
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    // Make sure that the RAM vector table is correctly aligned.
   
    ASSERT(((uint32_t)g_pfnRAMVectors & 0x000003ff) == 0);

    // See if the RAM vector table has been initialized.
	
    if(HWREG(NVIC_VTABLE) != (uint32_t)g_pfnRAMVectors)
    {
        // Copy the vector table from the beginning of FLASH to the RAM vector table.

        ui32Value = HWREG(NVIC_VTABLE);
        for(ui32Idx = 0; ui32Idx < NUM_INTERRUPTS; ui32Idx++)
        {
            g_pfnRAMVectors[ui32Idx] = (void (*)(void))HWREG((ui32Idx * 4) +
                                                             ui32Value);
        }

        // Point the NVIC at the RAM vector table.
        HWREG(NVIC_VTABLE) = (uint32_t)g_pfnRAMVectors;
    }

    // Save the interrupt handler.
    g_pfnRAMVectors[ui32Interrupt] = pfnHandler;
}

// Unregisters the function to be called when an interrupt occurs.

void IntUnregister(uint32_t ui32Interrupt)
{

    // Check the arguments.
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    // Reset the interrupt handler.
    g_pfnRAMVectors[ui32Interrupt] = _IntDefaultHandler;
}

// Sets the priority grouping of the interrupt controller.
//!
//! \param ui32Bits specifies the number of bits of preemptable priority.
//!
//! This function specifies the split between preemptable priority levels and
//! sub-priority levels in the interrupt priority specification.  The range of
//! the grouping values are dependent upon the hardware implementation; on
//! the Tiva C and E Series family, three bits are available for hardware
//! interrupt prioritization and therefore priority grouping values of three
//! through seven have the same effect.
//!
//! \b Example: Set the priority grouping for the interrupt controller.
//!
//! \verbatim
//! //
//! // Set the priority grouping for the interrupt controller to 2 bits.
//! //
//! IntPriorityGroupingSet(2);
//!
//! \endverbatim
//!
//! \return None.
//
//*****************************************************************************
void
IntPriorityGroupingSet(uint32_t ui32Bits)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Bits < NUM_PRIORITY);

    //
    // Set the priority grouping.
    //
    HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | g_pui32Priority[ui32Bits];
}

// Gets the priority grouping of the interrupt controller.

uint32_t IntPriorityGroupingGet(void)
{
    uint32_t ui32Loop, ui32Value;

    // Read the priority grouping.
	
    ui32Value = HWREG(NVIC_APINT) & NVIC_APINT_PRIGROUP_M;
	
    // Loop through the priority grouping values.
  
    for(ui32Loop = 0; ui32Loop < NUM_PRIORITY; ui32Loop++)
    {
      
        // Stop looping if this value matches.
   
        if(ui32Value == g_pui32Priority[ui32Loop])
        {
            break;
        }
    }

    // Return the number of priority bits.
    return(ui32Loop);
}

// Sets the priority of an interrupt.

void IntPrioritySet(uint32_t ui32Interrupt, uint8_t ui8Priority)
{
    uint32_t ui32Temp;

    // Check the arguments.

    ASSERT((ui32Interrupt >= 4) && (ui32Interrupt < NUM_INTERRUPTS));

    // Set the interrupt priority.
  
    ui32Temp = HWREG(g_pui32Regs[ui32Interrupt >> 2]);
    ui32Temp &= ~(0xFF << (8 * (ui32Interrupt & 3)));
    ui32Temp |= ui8Priority << (8 * (ui32Interrupt & 3));
    HWREG(g_pui32Regs[ui32Interrupt >> 2]) = ui32Temp;
}

// Gets the priority of an interrupt.

int32_t IntPriorityGet(uint32_t ui32Interrupt)
{

    // Check the arguments.
    
    ASSERT((ui32Interrupt >= 4) && (ui32Interrupt < NUM_INTERRUPTS));

    // Return the interrupt priority.

    return((HWREG(g_pui32Regs[ui32Interrupt >> 2]) >>
            (8 * (ui32Interrupt & 3))) & 0xFF);
}

// Enables an interrupt.

void IntEnable(uint32_t ui32Interrupt)
{
    
    // Check the arguments.
    
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    
    // Determine the interrupt to enable.
    
    if(ui32Interrupt == FAULT_MPU)
    {
    
        // Enable the MemManage interrupt.
        
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_MEM;
    }
    else if(ui32Interrupt == FAULT_BUS)
    {
       
        // Enable the bus fault interrupt.
        
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_BUS;
    }
    else if(ui32Interrupt == FAULT_USAGE)
    {
        
        // Enable the usage fault interrupt.
        
        HWREG(NVIC_SYS_HND_CTRL) |= NVIC_SYS_HND_CTRL_USAGE;
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        
        // Enable the System Tick interrupt.
       
        HWREG(NVIC_ST_CTRL) |= NVIC_ST_CTRL_INTEN;
    }
    else if(ui32Interrupt >= 16)
    {
        
        // Enable the general interrupt.
        
        HWREG(g_pui32EnRegs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}


// Disables an interrupt.

void IntDisable(uint32_t ui32Interrupt)
{
    // Check the arguments.
   
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    // Determine the interrupt to disable.
   
    if(ui32Interrupt == FAULT_MPU)
    {
        // Disable the MemManage interrupt.
       
        HWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_MEM);
    }
    else if(ui32Interrupt == FAULT_BUS)
    {
       
        // Disable the bus fault interrupt.
       
        HWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_BUS);
    }
    else if(ui32Interrupt == FAULT_USAGE)
    {
       
        // Disable the usage fault interrupt.
       
        HWREG(NVIC_SYS_HND_CTRL) &= ~(NVIC_SYS_HND_CTRL_USAGE);
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
       
        // Disable the System Tick interrupt.
        HWREG(NVIC_ST_CTRL) &= ~(NVIC_ST_CTRL_INTEN);
    }
    else if(ui32Interrupt >= 16)
    {
        
        Disable the general interrupt.
        HWREG(g_pui32Dii16Regs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}

uint32_t IntIsEnabled(uint32_t ui32Interrupt)
{
    uint32_t ui32Ret;

    
    // Check the arguments.
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    
    // Initialize the return value.
    ui32Ret = 0;

    
    // Determine the interrupt to disable.
    if(ui32Interrupt == FAULT_MPU)
    {
        
        // Check the MemManage interrupt.
        ui32Ret = HWREG(NVIC_SYS_HND_CTRL) & NVIC_SYS_HND_CTRL_MEM;
    }
    else if(ui32Interrupt == FAULT_BUS)
    {
       
        // Check the bus fault interrupt.
        ui32Ret = HWREG(NVIC_SYS_HND_CTRL) & NVIC_SYS_HND_CTRL_BUS;
    }
    else if(ui32Interrupt == FAULT_USAGE)
    {
        
        // Check the usage fault interrupt.
        ui32Ret = HWREG(NVIC_SYS_HND_CTRL) & NVIC_SYS_HND_CTRL_USAGE;
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        
        // Check the System Tick interrupt.
        ui32Ret = HWREG(NVIC_ST_CTRL) & NVIC_ST_CTRL_INTEN;
    }
    else if(ui32Interrupt >= 16)
    {
      
        // Check the general interrupt.
        ui32Ret = HWREG(g_pui32EnRegs[(ui32Interrupt - 16) / 32]) &
                  (1 << ((ui32Interrupt - 16) & 31));
    }
    return(ui32Ret);
}

void IntPendSet(uint32_t ui32Interrupt)
{
    
    // Check the arguments.
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

   
    // Determine the interrupt to pend.
    if(ui32Interrupt == FAULT_NMI)
    {
        
        // Pend the NMI interrupt.
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_NMI_SET;
    }
    else if(ui32Interrupt == FAULT_PENDSV)
    {
       
        // Pend the PendSV interrupt.
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PEND_SV;
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        
        // Pend the SysTick interrupt.
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PENDSTSET;
    }
    else if(ui32Interrupt >= 16)
    {
        
        // Pend the general interrupt.
        HWREG(g_pui32PendRegs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}

void IntPendClear(uint32_t ui32Interrupt)
{
    
    // Check the arguments.
    ASSERT(ui32Interrupt < NUM_INTERRUPTS);

    
    // Determine the interrupt to unpend.
    if(ui32Interrupt == FAULT_PENDSV)
    {
        
        // Unpend the PendSV interrupt.
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_UNPEND_SV;
    }
    else if(ui32Interrupt == FAULT_SYSTICK)
    {
        
        // Unpend the SysTick interrupt.
        HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PENDSTCLR;
    }
    else if(ui32Interrupt >= 16)
    {
     
        // Unpend the general interrupt.
        HWREG(g_pui32UnpendRegs[(ui32Interrupt - 16) / 32]) =
            1 << ((ui32Interrupt - 16) & 31);
    }
}

void IntPriorityMaskSet(uint32_t ui32PriorityMask)
{
    // Set the priority mask.
    CPUbasepriSet(ui32PriorityMask);
}

uint32_t IntPriorityMaskGet(void)
{
    // Return the current priority mask.
    return(CPUbasepriGet());
}

void IntTrigger(uint32_t ui32Interrupt)
{
    // Check the arguments.
    ASSERT((ui32Interrupt >= 16) && (ui32Interrupt < NUM_INTERRUPTS));

    // Trigger this interrupt.
    HWREG(NVIC_SW_TRIG) = ui32Interrupt - 16;
}

